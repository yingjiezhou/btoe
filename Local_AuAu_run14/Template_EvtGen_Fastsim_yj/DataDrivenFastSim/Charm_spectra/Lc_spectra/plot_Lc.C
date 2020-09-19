#include "myFunction.h"
TH1F* hmodel;
double fun(double* x, double* par) {
    if(!hmodel) return -1;
    float N = par[0];
    float pt = x[0];
    int bin = hmodel->FindBin(pt+1e-6);
    return N*hmodel->GetBinContent(bin);
}
void plot_Lc() {
    globalSetting();
    char buf[250];
    char dir[250];
    char name[250];
    char CMD[250];
    char title[250];
    TLegend* legend;
    TH1F* h0;
    TCanvas* c1 = new TCanvas("c1", "A Canvas",10,10,1000,1000);
    setPad(c1);
    
    sprintf(dir,"pic");
    sprintf(CMD,"[ -d %s ] || mkdir -p %s",dir,dir);
    gSystem->Exec(CMD);
    
    const int ncent = 1;
    const char nameCent[ncent][250] = {"10_60"};
    const char nameCent1[ncent][250] = {"10-60%"};
    const float Nbin[ncent] = {209.952}; // 10-60%: 267.869
    //const float scale[ncent] = {1., 1.};
    
    const char namePar[250] = "#Lambda_{c}^{+}";
    const char namePar1[250] = "Lc";
    const char namePrint[250] = "AuAu 200 GeV";
    
    const int npt = 3;
    const double ptbin[npt+1] = {2.5, 3.5, 5.0, 8.0};
    const float pt_mean[npt] = {2.86, 3.97, 5.68};
    const float pt_err[npt] = {0.1, 0.1, 0.1};
    const float ratio[npt] = {1.6824414, 1.1307010, 0.83343855};
    const float ratioErr[npt] = {0.32328900, 0.15644299, 0.12574200};
    const float ratioSys[npt] = {0.41158023, 0.26342620, 0.16741144};
    const float xmin = 0;
    const float xmax = 9.;
    
    // Lc ratio data point
    TGraphErrors* gRatio[ncent]; // 后面plots 的时候用到了
    TGraphErrors* gRatioSys[ncent];
    TH1F* hRatio[ncent];
    for(int icent=0; icent<ncent; icent++) {
        gRatio[icent] = new TGraphErrors(npt,pt_mean,ratio,pt_err,ratioErr); // 所以，这里只是给出来，到时候和模型对比而已，真实对Lc的预言当中没有用到这个
        gRatioSys[icent] = new TGraphErrors(npt,pt_mean,ratio,pt_err,ratioSys);
        
        hRatio[icent] = new TH1F(Form("hRatio%i",icent),"hRatio",npt,ptbin);
        for(int i=0; i<npt; i++) {
            hRatio[icent]->SetBinContent(i+1,ratio[i]); // from data point, Lc/D0 ratio, 没用到这里
            hRatio[icent]->SetBinError(i+1,ratioErr[i]);
        }
    }
    
    // read model
    const int nMod = 3;
    const char nameMod[nMod][250] = {"Ko: di-quark", "Ko: three-quark", "Greco"};
    TGraphErrors* gModel[nMod];
    ifstream in;
    in.open("data/LcD0_Ko_0901.1382.txt");
    const int npoint = 12;
    float pt[npoint], tmp, ratio1[npoint], ratio2[npoint];
    for(int ipoint=0; ipoint<npoint && (!in.eof()); ipoint++) {
        in >> pt[ipoint] >> tmp >> ratio2[ipoint] >> ratio1[ipoint];
    }
    in.close();
    gModel[0] = new TGraphErrors(npoint, pt, ratio1, 0, 0); // txt into TgraphError
    gModel[1] = new TGraphErrors(npoint, pt, ratio2, 0, 0);
    
    hmodel = new TH1F("hmodel","hmodel", 200, 0, 10);
    for(int i=0; i<200; i++) {
        float ptx = 10./200*(i+0.5);
        //cout << ptx << endl;
        hmodel->SetBinContent(i+1,gModel[0]->Eval(ptx)); //Tgraph into TH1F
        hmodel->SetBinError(i+1,0);
    }
    
    
    
    
    
    // add another model -- Greco
    const int npoint1 = 14;
    float pt1[npoint1], ratio_lw[npoint1], ratio_up[npoint1], ratio3[npoint1], ratio3Err[npoint1];
    in.open("data/LcD0_Greco_1407.5069.txt");
    for(int ipoint=0; ipoint<npoint1 && (!in.eof()); ipoint++) {
        in >> pt1[ipoint] >> ratio_lw[ipoint] >> ratio_up[ipoint];
        ratio3[ipoint] = 0.5*(ratio_lw[ipoint]+ratio_up[ipoint]);
        ratio3Err[ipoint] = 0.5*(-ratio_lw[ipoint]+ratio_up[ipoint]);
        //cout << ipoint << "\t" << pt1[ipoint] << "\t" << ratio3[ipoint] << "\t" << ratio3Err[ipoint] << endl;
    }
    in.close();
    gModel[2] = new TGraphErrors(npoint1, pt1, ratio3, 0, ratio3Err);
    
    // read D0 spectra
    TGraphErrors* gSpectraSys[ncent];
    TGraphErrors* gSpectraErr[ncent];
    TGraphErrors* gBand[ncent];
    TGraphErrors* gLc[nMod][ncent]; // nMod=3, 3 diff model
    //TF1* fSpectra[ncent];
    TFile* fin = new TFile("data/D0_Spectra_Run14HFT.root");
    for(int icent=0; icent<ncent; icent++) {
        gSpectraErr[icent] = (TGraphErrors*)fin->Get(Form("gD0_err_%s",nameCent[icent]));
        gSpectraSys[icent] = (TGraphErrors*)fin->Get(Form("gD0_sys_%s",nameCent[icent])); //这里是直接用D0的数据点
        gBand[icent] = (TGraphErrors*)fin->Get(Form("flevy_err_band_%s",nameCent[icent])); // 这是data得到的D0进行拟合得到，取其值
        for(int imod=0; imod<nMod; imod++) gLc[imod][icent] = (TGraphErrors*)fin->Get(Form("flevy_err_band_%s",nameCent[icent]));
        //fSpectra[icent] = (TF1*)fin->Get(Form("flevy_%s",nameCent[icent]));
    }
    fin->Close();
    cout << "CHECK " << endl;

    // calculte Lc spectra, multiply ratio
    for(int imod=0; imod<nMod; imod++) {
        for(int icent=0; icent<ncent; icent++) {
            for(int ipt=0; ipt<gBand[icent]->GetN(); ipt++) {
                float ptw = gBand[icent]->GetX()[2] - gBand[icent]->GetX()[1]; // dpt
                float xpt = gBand[icent]->GetX()[ipt] + 0.5*ptw; // pt
                gLc[imod][icent]->GetY()[ipt] *= gModel[imod]->Eval(xpt); // zyj 这里就是将模型预测的ratio与gLc相乘
            }
            cout << imod << "\t" << gLc[imod][icent]->Eval(0.2) << "\t" << gLc[imod][icent]->Eval(1) << "\t" << gLc[imod][icent]->Eval(2) << endl; // zyj ??
        }
    }
    
    // calculte Lc spectra scale number
    const float factor = 42.*1000; // ub
    const float twoPI = 2.*TMath::Pi();
    float xcD0[ncent], xcLc[nMod][ncent];
    float scale[nMod][ncent];
    for(int imod=0; imod<nMod; imod++) {
        for(int icent=0; icent<ncent; icent++) {
            // init
            xcD0[icent] = 0; xcLc[imod][icent] = 0;
            
            // D0
            for(int i=0; i<gBand[icent]->GetN()-1; i++) {
                float ptw = gBand[icent]->GetX()[2] - gBand[icent]->GetX()[1];
                float ptx = gBand[icent]->GetX()[i]+0.5*ptw;
                if(ptx<3 || ptx>6) continue;
                float ymean = 0.5*(gBand[icent]->GetY()[i]+gBand[icent]->GetY()[i+1]);
                //cout << gBand[icent]->GetX()[i] << endl;
                //float yup = ymean + 0.5*(gBand[icent]->GetEY()[i]+gBand[icent]->GetEY()[i+1]);
                //cout << pt << "\t" << ptw << "\t" << ymean << "\t" << yup << endl;
                //cout << gBand[icent]->GetN() << endl;
                xcD0[icent] += ymean*twoPI*ptx*ptw*factor / Nbin[icent];
            }
            
            // Lc
            for(int i=0; i<gBand[icent]->GetN()-1; i++) {
                float ptw = gLc[imod][icent]->GetX()[2] - gLc[imod][icent]->GetX()[1];
                float ptx = gLc[imod][icent]->GetX()[i]+0.5*ptw;
                if(ptx<3 || ptx>6) continue;
                float ymean = 0.5*(gLc[imod][icent]->GetY()[i]+gLc[imod][icent]->GetY()[i+1]);
                if(ymean<0) continue;
                //float yup = ymean + 0.5*(gBand[icent]->GetEY()[i]+gBand[icent]->GetEY()[i+1]);
                //cout << pt << "\t" << ptw << "\t" << ymean << "\t" << yup << endl;
                //cout << gBand[icent]->GetN() << endl;
                xcLc[imod][icent] += ymean*twoPI*ptx*ptw*factor / Nbin[icent];
            }
            
            // scale number
            scale[imod][icent] = ratio[0] / (xcLc[imod][icent]/xcD0[icent]); //用实验室第一个pt 区间的比值，除以后面所有模型给出的产额比值
            cout << "scale number: " << scale[imod][icent] << endl;
        }
    }
    
    // reset Lc spectra 显示Lc乘上预言的pt谱，得到Lc的pt谱，然后再乘以 第一个pt 区间的比值除以Lc与D0整个区间相除的比值
    const float scaleErr = sqrt(pow(ratioErr[0]/ratio[0],2) + pow(ratioSys[0]/ratio[0],2));
    for(int imod=0; imod<nMod; imod++) {
        for(int icent=0; icent<ncent; icent++) {
            for(int ipt=0; ipt<gBand[icent]->GetN(); ipt++) {
                float y = gLc[imod][icent]->GetY()[ipt]*scale[imod][icent];
                if(y<0) y=0;
                gLc[imod][icent]->GetY()[ipt] = y;
                gLc[imod][icent]->GetEY()[ipt] = y*scaleErr;
            }
        }
    }
    
    // calculte mean of diff model
    int nn = gLc[0][0]->GetN();
    const int NN = nn;
    float LcY[NN], LcX[NN], LcYerr[NN];
    TGraphErrors* gLcMean[ncent];
    for(int icent=0; icent<ncent; icent++) {
        for(int ii=0; ii<NN; ii++) {
            float ymean = 0, yerr = 0, ymaxdiff = 0, imax=-1;
            for(int imod=0; imod<nMod; imod++) ymean += gLc[imod][icent]->GetY()[ii];
            ymean /= nMod;
            for(int imod=0; imod<nMod; imod++) {
                float diff = fabs(gLc[imod][icent]->GetY()[ii] - ymean);
                if(diff>ymaxdiff) {ymaxdiff = diff; imax=imod;}
                //cout << gLc[imod][icent]->GetY()[ii] << "\t" << ymean << endl;
            }
            //cout << ii << "\t" << imax << "\t" << ymaxdiff << endl;
            LcY[ii] = ymean;
            LcYerr[ii] = ymean*sqrt(pow(ymaxdiff/ymean,2) + pow(scaleErr,2));
            LcX[ii] = gLc[0][icent]->GetX()[ii];
        }
        gLcMean[icent] = new TGraphErrors(NN, LcX, LcY, 0, LcYerr);
    }
    
    gLcMean[0]->Draw();


    // calculate Lc and D0 cross section
    for(int imod=0; imod<nMod; imod++) {
        for(int icent=0; icent<ncent; icent++) {
            // init
            xcD0[icent] = 0; xcLc[imod][icent] = 0;
            
            // D0
            for(int i=0; i<gBand[icent]->GetN()-1; i++) {
                float ptw = gBand[icent]->GetX()[2] - gBand[icent]->GetX()[1];
                float ptx = gBand[icent]->GetX()[i]+0.5*ptw;
                //if(ptx<3 || ptx>6) continue;
                float ymean = 0.5*(gBand[icent]->GetY()[i]+gBand[icent]->GetY()[i+1]);
                //cout << gBand[icent]->GetX()[i] << endl;
                //float yup = ymean + 0.5*(gBand[icent]->GetEY()[i]+gBand[icent]->GetEY()[i+1]);
                //cout << pt << "\t" << ptw << "\t" << ymean << "\t" << yup << endl;
                //cout << gBand[icent]->GetN() << endl;
                xcD0[icent] += ymean*twoPI*ptx*ptw*factor / Nbin[icent];
            }
            
            // Lc
            for(int i=0; i<gBand[icent]->GetN()-1; i++) {
                float ptw = gLc[imod][icent]->GetX()[2] - gLc[imod][icent]->GetX()[1]; // zyj reset 之后的Lc的谱
                float ptx = gLc[imod][icent]->GetX()[i]+0.5*ptw;
                //if(ptx<3 || ptx>6) continue;
                float ymean = 0.5*(gLc[imod][icent]->GetY()[i]+gLc[imod][icent]->GetY()[i+1]);
                if(ymean<0) continue;
                //float yup = ymean + 0.5*(gBand[icent]->GetEY()[i]+gBand[icent]->GetEY()[i+1]);
                //cout << pt << "\t" << ptw << "\t" << ymean << "\t" << yup << endl;
                //cout << gBand[icent]->GetN() << endl;
                xcLc[imod][icent] += ymean*twoPI*ptx*ptw*factor / Nbin[icent];
            }
            
            //cout << imod << "\t" << gLc[imod][icent]->Eval(0.2) << "\t" << gLc[imod][icent]->Eval(1) << "\t" << gLc[imod][icent]->Eval(2) << endl;
            cout << "D0 cross section: " << xcD0[icent] << endl;
            cout << "Lc cross section: " << xcLc[imod][icent] << endl;
        }
    }


    // calculate Lc cross-section  mean and error
    float LcCS[ncent], LcCSerr[ncent];
    for(int icent=0; icent<ncent; icent++) {
        // init
        LcCS[icent] = 0; LcCSerr[icent] = 0;
        
        // Lc
        for(int i=0; i<gBand[icent]->GetN()-1; i++) {
            float ptw = gLcMean[icent]->GetX()[2] - gLcMean[icent]->GetX()[1];
            float ptx = gLcMean[icent]->GetX()[i]+0.5*ptw;
            //if(ptx<3 || ptx>6) continue;
            float ymean = 0.5*(gLcMean[icent]->GetY()[i]+gLcMean[icent]->GetY()[i+1]);
            if(ymean<0) continue;
            float yup = ymean + 0.5*(gLcMean[icent]->GetEY()[i]+gLcMean[icent]->GetEY()[i+1]);
            //cout << pt << "\t" << ptw << "\t" << ymean << "\t" << yup << endl;
            //cout << gBand[icent]->GetN() << endl;
            //cout << ymean << "\t" << yup << endl;
            LcCS[icent] += ymean*twoPI*ptx*ptw*factor / Nbin[icent];
            LcCSerr[icent] += yup*twoPI*ptx*ptw*factor / Nbin[icent];
        }
        LcCSerr[icent] -= LcCS[icent];
        
        //cout << imod << "\t" << gLc[imod][icent]->Eval(0.2) << "\t" << gLc[imod][icent]->Eval(1) << "\t" << gLc[imod][icent]->Eval(2) << endl;
        //cout << "D0 cross section: " << xcD0[icent] << endl;
        cout << "Lc cross section: " << LcCS[icent] << "\t" << LcCSerr[icent] << endl;
    }
    /*for(int icent=0; icent<ncent; icent++) {
     LcCS[icent] = 0; LcCSerr[icent] = 0;
     for(int imod=0; imod<nMod; imod++) LcCS[icent] += xcLc[imod][icent];
     LcCS[icent] /= 3.0;
     float maxDiff = 0;
     for(int imod=0; imod<nMod; imod++) {
     float diff = fabs(LcCS[icent] - xcLc[imod][icent]);
     if(diff > maxDiff) maxDiff = diff;
     }
     LcCSerr[icent] = sqrt(pow(maxDiff/LcCS[icent],2) + pow(scaleErr,2))*LcCS[icent];
     cout << "Lc cross section: " << LcCS[icent] << "\t" << LcCSerr[icent] << endl;
     }*/
  
  //==========================================================================================

    
    // plot
    for(int icent=0; icent<ncent; icent++) {
        float ymin = 0.5*gModel[0]->Eval(xmax);
        float ymax = 10.*gModel[0]->Eval(2);
        h0 = new TH1F("","",1,xmin,xmax);
        h0->GetYaxis()->SetRangeUser(1e-1,ymax);
        setHisto(h0,"","p_{T} (GeV/c)", "(#Lambda_{c}^{+} + #Lambda_{c}^{-}) / (D^{0} + #bar{D^{0}})");
        h0->Draw();
        
        //gBand[icent]->SetFillStyle(3001);
        //gBand[icent]->SetFillColor(kGreen+2);
        //gBand1[icent]->SetFillColorAlpha(kGreen,0.4);
        //gBand1[icent]->Draw("e3same");
        
        gRatio[icent]->SetMarkerStyle(kFullCircle);
        gRatio[icent]->SetMarkerSize(1.5);
        gRatio[icent]->SetMarkerColor(kBlack);
        gRatio[icent]->SetLineColor(kBlack);
        gRatio[icent]->SetLineWidth(2);
        gRatio[icent]->Draw("psame");
        
        /*funFit[icent]->SetLineColor(kBlack);
        funFit[icent]->SetLineWidth(2);
        funFit[icent]->SetLineStyle(7);
        funFit[icent]->Draw("same");*/
        
        //draw systematic error
        const float sysw = 0.15;
        // for data ratio, draw error bar line?
        for(int i=0; i<gRatioSys[icent]->GetN(); i++) {
            const float sysl = gRatioSys[icent]->GetY()[i] * 0.05;
            TLine *llw = new TLine(gRatioSys[icent]->GetX()[i]-sysw,gRatioSys[icent]->GetY()[i]-gRatioSys[icent]->GetEY()[i],gRatioSys[icent]->GetX()[i]+sysw,gRatioSys[icent]->GetY()[i]-gRatioSys[icent]->GetEY()[i]);
            llw->SetLineWidth(2);
            llw->SetLineColor(kBlack);
            llw->Draw("same");
            TLine *lhi = new TLine(gRatioSys[icent]->GetX()[i]-sysw,gRatioSys[icent]->GetY()[i]+gRatioSys[icent]->GetEY()[i],gRatioSys[icent]->GetX()[i]+sysw,gRatioSys[icent]->GetY()[i]+gRatioSys[icent]->GetEY()[i]);
            lhi->SetLineWidth(2);
            lhi->SetLineColor(kBlack);
            lhi->Draw("same");
            TLine *lv1 = new TLine(gRatioSys[icent]->GetX()[i]-sysw,gRatioSys[icent]->GetY()[i]-gRatioSys[icent]->GetEY()[i],gRatioSys[icent]->GetX()[i]-sysw,gRatioSys[icent]->GetY()[i]-gRatioSys[icent]->GetEY()[i]+sysl);
            lv1->SetLineWidth(2);
            lv1->SetLineColor(kBlack);
            lv1->Draw("same");
            TLine *lv2 = new TLine(gRatioSys[icent]->GetX()[i]+sysw,gRatioSys[icent]->GetY()[i]-gRatioSys[icent]->GetEY()[i],gRatioSys[icent]->GetX()[i]+sysw,gRatioSys[icent]->GetY()[i]-gRatioSys[icent]->GetEY()[i]+sysl);
            lv2->SetLineWidth(2);
            lv2->SetLineColor(kBlack);
            lv2->Draw("same");
            TLine *lv3 = new TLine(gRatioSys[icent]->GetX()[i]-sysw,gRatioSys[icent]->GetY()[i]+gRatioSys[icent]->GetEY()[i],gRatioSys[icent]->GetX()[i]-sysw,gRatioSys[icent]->GetY()[i]+gRatioSys[icent]->GetEY()[i]-sysl);
            lv3->SetLineWidth(2);
            lv3->SetLineColor(kBlack);
            lv3->Draw("same");
            TLine *lv = new TLine(gRatioSys[icent]->GetX()[i]+sysw,gRatioSys[icent]->GetY()[i]+gRatioSys[icent]->GetEY()[i],gRatioSys[icent]->GetX()[i]+sysw,gRatioSys[icent]->GetY()[i]+gRatioSys[icent]->GetEY()[i]-sysl);
            lv->SetLineWidth(2);
            lv->SetLineColor(kBlack);
            lv->Draw("same");
        }
        
        gModel[0]->SetLineColor(kRed);
        gModel[0]->SetLineWidth(2);
        gModel[0]->SetLineStyle(7);
        gModel[0]->Draw("same");
        
        gModel[1]->SetLineColor(kBlue);
        gModel[1]->SetLineWidth(2);
        gModel[1]->SetLineStyle(5);
        gModel[1]->Draw("same");
        
        //gModel[2]->SetFillStyle(3001);
        //gModel[2]->SetFillColor(kGreen+2);
        gModel[2]->SetFillColorAlpha(kGray,0.4);
        gModel[2]->Draw("e3same");
        
        sprintf(name,"%s, %s",namePrint,nameCent1[icent]);
        drawLatex(0.18,0.89,name,132,0.04,1);
        
        float ypos = 0.88;
        sprintf(name,"%s cross section", namePar);
        drawLatex(0.58,ypos,name,132,0.03,1);
        for(int imod=0; imod<nMod; imod++) {
            ypos -= 0.04;
            sprintf(name,"%s: \t%.0f #pm %.0f #mub", nameMod[imod], xcLc[imod][icent], xcLc[imod][icent]*scaleErr);
            drawLatex(0.58,ypos,name,132,0.03,1);
        }
        ypos -= 0.04;
        sprintf(name,"mean: \t%.0f #pm %.0f #mub", LcCS[icent], LcCSerr[icent]);
        drawLatex(0.58,ypos,name,132,0.03,1);
        
        sprintf(name,"%.3f #pm %.3f(stat.) #pm %.3f(sys.)", ratio[0], ratioErr[0], ratioSys[0]);
        drawLatex(0.56,0.62,name,132,0.03,1);
        
        const float legy_lw = 0.9 - 0.05*nMod;
        legend = new TLegend(0.18,legy_lw,0.7,0.88);
        legend->SetFillStyle(0);
        legend->SetFillColor(10);
        legend->SetBorderSize(0);
        legend->SetTextSize(0.04);
        legend->SetTextFont(132);
        legend->AddEntry(gModel[0],nameMod[0],"l");
        legend->AddEntry(gModel[1],nameMod[1],"l");
        legend->AddEntry(gModel[2],nameMod[2],"f");
        legend->Draw();
        
        c1->SetLogy();
        sprintf(name,"%s/%s_%s.gif",dir,namePar1,nameCent[icent]); // dir=pic
        c1->SaveAs(name);
    }
//==========================================================================================
    
    // write spectra
    //const int N = gLc[0][0]->GetN()-1 ;

    const int N = gLc[0][0]->GetN() ; // chaged by xiaozhi
    
    const float binWidth = gLc[0][0]->GetX()[2] - gLc[0][0]->GetX()[1];
    const float y_lw = 0;
    const float y_up = binWidth*N;
  
  //gLc to hLc,?? zyj???
    TH1F* hLc[nMod][ncent];
    for(int imod=0; imod<nMod; imod++) {
        for(int icent=0; icent<ncent; icent++) {
            // Lc
            sprintf(name, "h%s_spectra_%s_model%i", namePar1, nameCent[icent], imod+1);
            sprintf(title, "%s;p_{T} (GeV/c);d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-1}",nameMod[imod]);
            hLc[imod][icent] = new TH1F(name,title,N,y_lw,y_up);
            for(int i=0; i<gBand[icent]->GetN()-1; i++) {
                float ptw = gLc[imod][icent]->GetX()[2] - gLc[imod][icent]->GetX()[1];
                float ptx = gLc[imod][icent]->GetX()[i]+0.5*ptw;
                //if(ptx<3 || ptx>6) continue;
                float ymean = 0.5*(gLc[imod][icent]->GetY()[i]+gLc[imod][icent]->GetY()[i+1]);
                float yerr = 0.5*(gLc[imod][icent]->GetEY()[i]+gLc[imod][icent]->GetEY()[i+1]);
                //float ymean = gLc[imod][icent]->GetY()[i];
                //float yerr = gLc[imod][icent]->GetEY()[i];
                if(ymean<0 || yerr<0) {ymean=0; yerr=0;}
                hLc[imod][icent]->SetBinContent(i+1,ymean*twoPI*ptx); // 这就是最后存下来的hLc_spectra_10_60_mean
                hLc[imod][icent]->SetBinError(i+1,yerr*twoPI*ptx);
            }
        }
    }
    
    TFile* fout = new TFile(Form("out/%s_10_80.root",namePar1), "RECREATE");
    for(int icent=0; icent<ncent; icent++) {
        sprintf(name,"Lc/D0, %s", nameCent1[icent]); // ratio from data?
        gRatio[icent]->SetTitle(name);
        sprintf(name,"%s_%s_err",namePar1, nameCent[icent]);
        gRatio[icent]->SetName(name);
        gRatio[icent]->Write();
        sprintf(name,"%s_%s_sys",namePar1, nameCent[icent]);
        gRatioSys[icent]->SetName(name);
        gRatioSys[icent]->Write();
        
        if(icent==0) {
            for(int imod=0; imod<nMod; imod++) {
                gModel[imod]->SetTitle(nameMod[imod]);
                sprintf(name,"%s_model%i",namePar1,imod+1);
                gModel[imod]->SetName(name); // ration from model? zyj
                gModel[imod]->Write();
            }
        }

	// model and model mean get
        for(int imod=0; imod<nMod; imod++) {
            hLc[imod][icent]->Write();
        }
        
        TH1F* hLcMean = (TH1F*)hLc[0][icent]->Clone(Form("hLcMean%i",icent));
        //hLcMeam->SetTitle("mean;p_{T} (GeV/c);d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-1}");
        for(int imod=1; imod<nMod; imod++) {
            hLcMean->Add(hLc[imod][icent],1.0);
        }
        hLcMean->Scale(1./nMod);
        for(int ipoint=1; ipoint<=hLcMean->GetNbinsX(); ipoint++) {
            float maxDiff = 0;
            float ymean = hLcMean->GetBinContent(ipoint);
            float imax = -1;
            for(int imod=0; imod<nMod; imod++) {
                float diff = fabs(hLc[imod][icent]->GetBinContent(ipoint) - ymean);
                if(diff>maxDiff) {maxDiff = diff; imax=imod;}
                //cout << hLc[imod][icent]->GetBinContent(ipoint) << "\t" << ymean << endl;
            }
            //cout << ipoint << "\t" << imax << "\t" << maxDiff << endl;
	    float yerr = sqrt(pow(maxDiff/ymean,2.) + pow(scaleErr,2.)) * ymean;
	    


	    hLcMean->SetBinError(ipoint, yerr);
        }
        
        hLcMean->GetXaxis()->SetTitle("p_{T} (GeV/c)");
        hLcMean->GetYaxis()->SetTitle("d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-1}");
        hLcMean->SetTitle("mean from all model");
        sprintf(name, "h%s_spectra_%s_mean", namePar1, nameCent[icent]);
        hLcMean->SetName(name);
        hLcMean->Write();
        sprintf(name, "g%s_spectra_%s_mean", namePar1, nameCent[icent]);

	fout->Close();

    }

}
