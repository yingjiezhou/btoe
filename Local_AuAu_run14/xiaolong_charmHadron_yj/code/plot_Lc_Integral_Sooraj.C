#include "myFunction.h"
TF1* fD0;
TGraphErrors* gD0;
TGraph* gLcOverD0;
double fun(double* x, double* par) {
    if(!fD0) return -1;
    if(!gLcOverD0) return -1;
    double N = par[0];
    double pt = x[0];
    return N * fD0->Eval(pt) * gLcOverD0->Eval(pt) * 2.* TMath::Pi() * pt;
    //return N * fD0->Eval(pt) * gLcOverD0->Eval(pt) * 2.* TMath::Pi() * pt;
}

void plot_Lc_Integral_Sooraj() {
    globalSetting();
    char buf[250];
    char dir[250];
    char name[250];
    char CMD[250];
    char title[250];
    TLegend* legend;
    TH1F* h0;
    TFile* fin = NULL;
    TCanvas* c1 = new TCanvas("c1", "A Canvas",10,10,1000,1000);
    setPad(c1);
    
    sprintf(dir,"pic");
    sprintf(CMD,"[ -d %s ] || mkdir -p %s",dir,dir);
    gSystem->Exec(CMD);
    
    const int ncent = 1;
    const char nameCent[ncent][250] = {""};
    const char nameCent1[ncent][250] = {"10-80%"};
    const char nameCent2[ncent][250] = {"10_80"};
    const float Nbin[ncent] = {198.};
    
    const char namePar[250] = "#Lambda_{c}^{+}";
    const char namePar1[250] = "Lc";
    const char namePrint[250] = "AuAu 200 GeV";
    
    const int npt = 3;
    const double ptbin[npt+1] = {2.5, 3.5, 5.0, 8.0};
    const float xmin = 0;
    const float xmax = 8;
    const float twoPI = 2.*TMath::Pi();
    
    const int nModel = 4;
    const char nameModel[nModel][100] = {"Ko_TwoQuark", "Ko_ThreeQuark", "Greco_CoalAndFrag", "Tshingua"};
    const char nameModel1[nModel][100] = {"Ko: di-quark", "Ko: three-quark", "Greco", "Tshingua"};
    const int modelColor[nModel] = {kRed, kBlue, kGray+2, kMagenta+2};
    
    float ratio[nModel], ratio_err[nModel], chi2[nModel], ndf[nModel];
    float x_value[50], y_value[50]; // 0-6 GeV
    
    // read model
    TGraph* gModel[nModel];
    TGraph* gModel_Fit[nModel];
    fin = TFile::Open("data/LcD0_model.root");
    for(int iModel=0; iModel<nModel; iModel++) {
        gModel[iModel] = (TGraph*)fin->Get(Form("%s",nameModel[iModel]));
        gModel_Fit[iModel] = (TGraph*)fin->Get(Form("%s",nameModel[iModel]));
        gModel_Fit[iModel]->SetName(Form("%s_Fitted",gModel_Fit[iModel]->GetName()));
        cout << gModel[iModel]->GetName() << "\t" << gModel[iModel]->GetTitle() << endl;
        //cout << gModel[iModel]->Eval(4) << endl;
    }
    fin->Close();
    
    const int nPtSave = 200;
    float PtEdgeSave[nPtSave+1];
    for(int i=0; i<nPtSave+1; i++) {
        PtEdgeSave[i] = 10./nPtSave*i;
    }
    float PtMean[nPtSave], PtError[nPtSave];
    for(int i=0; i<nPtSave; i++) {
        PtMean[i] = 0.5*(PtEdgeSave[i]+PtEdgeSave[i+1]);
        PtError[i] = 0.5*(-PtEdgeSave[i]+PtEdgeSave[i+1]);
    }
    
    TH1F* hPtBase = new TH1F("hPtBase","hPtBase",npt,ptbin);
    
    // read Lc spectra
    TGraphErrors* gSpectraSys[ncent];
    TGraphErrors* gSpectraErr[ncent];
    //TGraphErrors* gBand[ncent];
    TF1* fSpectra[ncent];
    if(false) {  // read spectra
        fin = TFile::Open("data/LcPt_10t80_sysfix.root");
        for(int icent=0; icent<ncent; icent++) {
            gSpectraErr[icent] = (TGraphErrors*)fin->Get(Form("gLc%s",nameCent[icent]));
            gSpectraSys[icent] = (TGraphErrors*)fin->Get(Form("gLcSys%s",nameCent[icent]));
            //gBand[icent] = (TGraphErrors*)fin->Get(Form("flevy_err_band_%s",nameCent[icent]));
            //fSpectra[icent] = (TF1*)fin->Get(Form("flevy_%s",nameCent[icent]));
        }
        fin->Close();
    }
    else { // calculate
        const int nn = 3;
        const double xx[nn] = {PtMean[0], PtMean[1], PtMean[2]};
        const double yy[ncent][nn] = {{8.3e-04, 6.2e-05, 1.9e-06}};
        const double yyerr[ncent][nn] = {{1.5e-04, 7.8e-06, 3.1e-07}};
        const double yysys[ncent][nn] = {{1.7e-04, 1.09e-05, 4.3e-07}};
        for(int icent=0; icent<ncent; icent++) {
            gSpectraErr[icent] = new TGraphErrors(nn,xx,yy[icent],0,yyerr[icent]);
            gSpectraSys[icent] = new TGraphErrors(nn,xx,yy[icent],0,yysys[icent]);
        }
    }
    
    TH1F* hSpectraErr[ncent];
    for(int icent=0; icent<ncent; icent++) {
        hSpectraErr[icent] = new TH1F(Form("hSpectraErr_%i",icent),"hSpectraErr",npt,ptbin);
        for(int ipt=0; ipt<npt; ipt++) {
            float ptValue = 0.5*(ptbin[ipt]+ptbin[ipt+1]);//gSpectraErr[icent]->GetX()[ipt]; //
            gSpectraErr[icent]->GetY()[ipt] *= (twoPI*ptValue);
            gSpectraErr[icent]->GetEY()[ipt] *= (twoPI*ptValue);
            gSpectraSys[icent]->GetY()[ipt] *= (twoPI*ptValue);
            gSpectraSys[icent]->GetEY()[ipt] *= (twoPI*ptValue);
            
            //cout << nameCent[icent] << "\t" << gSpectraErr[icent]->GetY()[ipt] << "\t" << gSpectraErr[icent]->GetEY()[ipt] << endl;
            
            hSpectraErr[icent]->SetBinContent(ipt+1,gSpectraErr[icent]->GetY()[ipt]);
            hSpectraErr[icent]->SetBinError(ipt+1,gSpectraErr[icent]->GetEY()[ipt]);
        }
    }
    for(int icent=0; icent<ncent; icent++) {
        cout << nameCent1[icent] << endl;
        for(int ipoint=0; ipoint<gSpectraSys[icent]->GetN(); ipoint++) {
            gSpectraSys[icent]->GetX()[ipoint] = hSpectraErr[icent]->GetBinCenter(ipoint+1);
            cout << ipoint+1 << "\t" << hSpectraErr[icent]->GetBinCenter(ipoint+1) << endl;
        }
    }
    
    // read D0 spectra
    TF1* fSpectraD0[ncent];
    TGraphErrors* gSpectraD0[ncent];
    fin = TFile::Open("data/D0_Spectra_Run14HFT.0401.root");
    for(int icent=0; icent<ncent; icent++) {
        fSpectraD0[icent] = (TF1*)fin->Get(Form("flevy_%s",nameCent2[icent]));
        gSpectraD0[icent] = (TGraphErrors*)fin->Get(Form("gD0_err_%s",nameCent2[icent]));
    }
    fin->Close();
    
    
    // calc. stat and sys error from data point
    //float xcCount[ncent], xcCountStat[ncent], xcCountSys[ncent], xcCountSys1[ncent];
    float xcCountSys2[ncent]={0};
    float xcCountSys[ncent]={0};
    float xcCount[ncent]={0};
    float xcCountStat[ncent]={0};
    float xcCountSys1[ncent]={0};
    const float factor = 42.*1000; // ub
    for(int icent=0; icent<ncent; icent++) {
        xcCount[icent] = 0; xcCountStat[icent] = 0; xcCountSys[icent] = 0;
        for(int ipoint=0; ipoint<npt; ipoint++) {
            float ptCenter = hSpectraErr[icent]->GetBinCenter(ipoint+1);
            float ptw = ptbin[ipoint+1] - ptbin[ipoint];
            float ymeanData = hSpectraErr[icent]->GetBinContent(ipoint+1);
            float statErr = gSpectraErr[icent]->GetEY()[ipoint]/gSpectraErr[icent]->GetY()[ipoint];
            float sysErr = gSpectraSys[icent]->GetEY()[ipoint]/gSpectraSys[icent]->GetY()[ipoint];
            cout<<"sysErr is "<<sysErr<<endl;
            //float err = mean*sqrt(pow(statErr,2) + pow(sysErr,2) + pow(sysFit,2));
            
            float xcCount0 = ymeanData*ptw*factor / Nbin[icent];
            xcCount[icent] += xcCount0;
            xcCountStat[icent] += pow(xcCount0*statErr,2);
            // xcCountSys += pow(xcCount0*sysErr,2); // no correlation
            // xcCountSys[icent] += xcCount0*sysErr; // fully correlation
            xcCountSys1[icent] += xcCount0 * 0.18; // correlated part
            //xcCountSys2[icent] += (pow(xcCount0*sysErr,2) - pow(xcCount0*0.18,2)); // uncorrelated part
            xcCountSys2[icent] += xcCount0*sysErr*xcCount0*sysErr-xcCount0*0.18*xcCount0*0.18; // uncorrelated part
            cout<<"xcCount0*sysErr,2 is "<<xcCount0*sysErr*xcCount0*sysErr-xcCount0*0.18*xcCount0*0.18<<endl;
            cout<<"xcCountSys2[icent] is "<<xcCountSys2[icent]<<endl;
        }
        xcCountStat[icent] = sqrt(xcCountStat[icent])/xcCount[icent];
        //xcCountSys[icent] = xcCountSys[icent]/xcCount[icent];
        xcCountSys1[icent] = xcCountSys1[icent]/xcCount[icent];  // correlated part
        xcCountSys2[icent] = sqrt(xcCountSys2[icent])/xcCount[icent]; // uncorrelated part
        cout<<"xcCountSys1[icent] is "<<xcCountSys1[icent]<<"xcCountSys2[icent] is "<<xcCountSys2[icent]<<endl;
        xcCountSys[icent] = sqrt(pow(xcCountSys1[icent],2) + pow(xcCountSys2[icent],2));
        
        cout << nameCent1[icent] << endl;
        cout << "from data: mean = " << xcCount[icent] << ",\t stat.err(%) = " << xcCountStat[icent] << ",\t sys.err(%) = " << xcCountSys[icent] << endl;
    }
    
    
    // fit
    float fitR_lw = ptbin[0];
    float fitR_up = ptbin[npt];
    const char fitOpt[100] = "IQENOR";
    TH1F* hLcMean[ncent];
    TGraphErrors* gBand[ncent];
    //ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(1000000); // Fit ERROR: cannot reach tolerance because of roundoff error
    //ROOT::Math::MinimizerOptions::SetDefaultMinimizer("GSLMultiFit", "");
    //ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(3);
    //ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
    //ROOT::Math::MinimizerOptions::SetDefaultTolerance(0.00001);
    //ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(100000);
    ROOT::Math::IntegratorOneDimOptions::SetDefaultRelTolerance(5.E-6);
    TF1* fModel[ncent][nModel];
    for(int icent=0; icent<ncent; icent++) {
        hLcMean[icent] = new TH1F(Form("hLcMean%i",icent),"",nPtSave,PtEdgeSave);
        
        // fit
        for(int iModel=0; iModel<nModel; iModel++) {
            fD0 = (TF1*)fSpectraD0[icent]->Clone(Form("fD0_%i_%i",icent,iModel));
            gD0 = (TGraphErrors*)gSpectraD0[icent]->Clone(Form("gD0_%i_%i",icent,iModel));
            gLcOverD0 = (TGraph*)gModel[iModel]->Clone(Form("gLcOverD0_%i_%i",icent,iModel));
            sprintf(name,"fTmpFit_%i_%i",icent,iModel);
            TF1* fTmptFit = new TF1(name,fun,0,10,1); // model ratio * real D0 spectrum = model Lc spectrum zyj
            fTmptFit->SetParameter(0,1);
            float N = gSpectraErr[icent]->Eval(3)/fTmptFit->Eval(3);//  get model and real diff zyj
            fTmptFit->SetParameter(0,N); // multiply so that model is similar with data
            
            hSpectraErr[icent]->Fit(fTmptFit, "EQNOR", "", fitR_lw, fitR_up);
            hSpectraErr[icent]->Fit(fTmptFit, "EQNOR", "", fitR_lw, fitR_up);
            hSpectraErr[icent]->Fit(fTmptFit, fitOpt, "", fitR_lw, fitR_up);
            hSpectraErr[icent]->Fit(fTmptFit, fitOpt, "", fitR_lw, fitR_up);
            
            fModel[icent][iModel] = (TF1*)fTmptFit->Clone(Form("fModel_%i_%i",icent,iModel));
            fModel[icent][iModel]->SetParNames("N");
            fModel[icent][iModel]->SetLineColor(modelColor[iModel]);
            fModel[icent][iModel]->SetLineStyle(7);
            fModel[icent][iModel]->SetLineWidth(2);
            
            ratio[iModel] = fTmptFit->GetParameter(0);
            ratio_err[iModel] = fTmptFit->GetParError(0);
            chi2[iModel] = fTmptFit->GetChisquare();
            ndf[iModel] = fTmptFit->GetNDF();
        }
    
        // calc. error band
        float meanLc[nPtSave], errLc[nPtSave];
        for(int ipoint=0; ipoint<nPtSave; ipoint++) {
            float pt = PtMean[ipoint];
            float modelValue[nModel];
            meanLc[ipoint] = 0;
            errLc[ipoint] = 0;
            for(int iModel=0; iModel<nModel; iModel++) {
                modelValue[iModel] = fModel[icent][iModel]->Eval(pt);
                meanLc[ipoint] += modelValue[iModel];
            }
            meanLc[ipoint] /= nModel;
            float maxDiff = 0;
            for(int iModel=0; iModel<nModel; iModel++) {
                float tmpDiff = fabs(modelValue[iModel] - meanLc[ipoint]);
                if(tmpDiff>maxDiff) maxDiff = tmpDiff;
            }
            errLc[ipoint] = sqrt(pow(meanLc[ipoint]*xcCountStat[icent],2)+pow(meanLc[ipoint]*xcCountSys[icent],2)+pow(maxDiff,2));
            hLcMean[icent]->SetBinContent(ipoint+1,meanLc[ipoint]);
            hLcMean[icent]->SetBinError(ipoint+1,errLc[ipoint]);
        }
        gBand[icent] = new TGraphErrors(nPtSave,PtMean,meanLc,0,errLc);
    }
    
    // calc. full pT range cross section
    float xcModel[ncent][nModel], xcErrorModel[ncent][nModel];
    float xcMean[ncent], xcError[ncent], xcMeanStatErr[ncent], xcMeanSysErr[ncent];
    for(int icent=0; icent<ncent; icent++) {
        // mean
        xcMean[icent] = 0; xcError[icent] = 0;
        for(int ipoint=0; ipoint<nPtSave; ipoint++) {
            float ptw = hLcMean[icent]->GetBinWidth(ipoint+1);
            float ymean = hLcMean[icent]->GetBinContent(ipoint+1);
            float yerr = hLcMean[icent]->GetBinError(ipoint+1);
            xcMean[icent] += ymean*ptw*factor / Nbin[icent];
            xcError[icent] += (ymean+yerr)*ptw*factor / Nbin[icent];
        }
        xcError[icent] = xcError[icent] - xcMean[icent];
        
        // in different model
        float maxDiff = 0;
        for(int iModel=0; iModel<nModel; iModel++) {
            xcModel[icent][iModel] = 0; xcErrorModel[icent][iModel] = 0;
            for(int ipoint=0; ipoint<nPtSave; ipoint++) {
                float pt = hLcMean[icent]->GetBinCenter(ipoint+1);
                float ptw = hLcMean[icent]->GetBinWidth(ipoint+1);
                float ymean = fModel[icent][iModel]->Eval(pt);
                xcModel[icent][iModel] += ymean*ptw*factor / Nbin[icent];
            }
            xcErrorModel[icent][iModel] = xcModel[icent][iModel]*sqrt(pow(xcCountSys[icent],2)+pow(xcCountStat[icent],2));
            
            if(fabs(xcModel[icent][iModel] - xcMean[icent])>maxDiff) {
                maxDiff = fabs(xcModel[icent][iModel] - xcMean[icent]);
            }
        }
        
        cout << maxDiff << "\t" << xcMean[icent] << "\t" << xcCountSys[icent] << "\t" << maxDiff/xcMean[icent] << endl;
        xcMeanStatErr[icent] = xcMean[icent]*xcCountStat[icent];
        xcMeanSysErr[icent] = xcMean[icent]*sqrt(pow(xcCountSys[icent],2)+pow(maxDiff/xcMean[icent],2));
        
    }
    
    // plot
    for(int icent=0; icent<ncent; icent++) {
        float ymin = 0.5*hLcMean[icent]->GetBinContent(hLcMean[icent]->FindBin(8));
        float ymax = 50000.*hLcMean[icent]->GetBinContent(hLcMean[icent]->FindBin(1));
        h0 = new TH1F("","",1,xmin,xmax);
        h0->GetYaxis()->SetRangeUser(ymin,ymax);
        setHisto(h0,"","p_{T} (GeV/c)", "d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-2}");
        h0->Draw();
        
        gBand[icent]->SetFillStyle(3001);
        //gBand[icent]->SetFillColor(kGreen+2);
        gBand[icent]->SetFillColorAlpha(kGreen,0.5);
        gBand[icent]->Draw("e3same");
        
        //hLcMean[icent]->SetFillColorAlpha(kGreen,0.4);
        //hLcMean[icent]->Draw("e3same");
        
        hLcMean[icent]->Draw("chistsame");
        hLcMean[icent]->SetLineColor(kBlack);
        hLcMean[icent]->SetLineWidth(2);
        
        for(int iModel=0; iModel<nModel; iModel++) fModel[icent][iModel]->Draw("same");
        
        hSpectraErr[icent]->SetMarkerStyle(kFullCircle);
        hSpectraErr[icent]->SetMarkerSize(1.5);
        hSpectraErr[icent]->SetMarkerColor(kBlack);
        hSpectraErr[icent]->SetLineColor(kBlack);
        hSpectraErr[icent]->SetLineWidth(2);
        hSpectraErr[icent]->Draw("esame");
        
        //draw systematic error
        const float sysw = 0.15;
        for(int i=0; i<gSpectraSys[icent]->GetN(); i++) {
            const float sysl = gSpectraSys[icent]->GetY()[i] * 0.05;
            TLine *llw = new TLine(hSpectraErr[icent]->GetBinCenter(i+1)-sysw,gSpectraSys[icent]->GetY()[i]-gSpectraSys[icent]->GetEY()[i],hSpectraErr[icent]->GetBinCenter(i+1)+sysw,gSpectraSys[icent]->GetY()[i]-gSpectraSys[icent]->GetEY()[i]);
            llw->SetLineWidth(2);
            llw->SetLineColor(kBlack);
            llw->Draw("same");
            TLine *lhi = new TLine(hSpectraErr[icent]->GetBinCenter(i+1)-sysw,gSpectraSys[icent]->GetY()[i]+gSpectraSys[icent]->GetEY()[i],hSpectraErr[icent]->GetBinCenter(i+1)+sysw,gSpectraSys[icent]->GetY()[i]+gSpectraSys[icent]->GetEY()[i]);
            lhi->SetLineWidth(2);
            lhi->SetLineColor(kBlack);
            lhi->Draw("same");
            TLine *lv1 = new TLine(gSpectraSys[icent]->GetX()[i]-sysw,gSpectraSys[icent]->GetY()[i]-gSpectraSys[icent]->GetEY()[i],gSpectraSys[icent]->GetX()[i]-sysw,gSpectraSys[icent]->GetY()[i]-gSpectraSys[icent]->GetEY()[i]+sysl);
            lv1->SetLineWidth(2);
            lv1->SetLineColor(kBlack);
            lv1->Draw("same");
            TLine *lv2 = new TLine(gSpectraSys[icent]->GetX()[i]+sysw,gSpectraSys[icent]->GetY()[i]-gSpectraSys[icent]->GetEY()[i],gSpectraSys[icent]->GetX()[i]+sysw,gSpectraSys[icent]->GetY()[i]-gSpectraSys[icent]->GetEY()[i]+sysl);
            lv2->SetLineWidth(2);
            lv2->SetLineColor(kBlack);
            lv2->Draw("same");
            TLine *lv3 = new TLine(gSpectraSys[icent]->GetX()[i]-sysw,gSpectraSys[icent]->GetY()[i]+gSpectraSys[icent]->GetEY()[i],gSpectraSys[icent]->GetX()[i]-sysw,gSpectraSys[icent]->GetY()[i]+gSpectraSys[icent]->GetEY()[i]-sysl);
            lv3->SetLineWidth(2);
            lv3->SetLineColor(kBlack);
            lv3->Draw("same");
            TLine *lv4 = new TLine(gSpectraSys[icent]->GetX()[i]+sysw,gSpectraSys[icent]->GetY()[i]+gSpectraSys[icent]->GetEY()[i],gSpectraSys[icent]->GetX()[i]+sysw,gSpectraSys[icent]->GetY()[i]+gSpectraSys[icent]->GetEY()[i]-sysl);
            lv4->SetLineWidth(2);
            lv4->SetLineColor(kBlack);
            lv4->Draw("same");
        }
        
        sprintf(name,"%s, %s",namePrint,nameCent1[icent]);
        drawLatex(0.52,0.905,name,132,0.04,1);
        sprintf(name,"%s cross section (#mub)",namePar);
        drawLatex(0.52,0.855,name,132,0.04,4);
        sprintf(name,"mean = %.1f #pm %.1f #pm %.1f",xcMean[icent],xcMeanStatErr[icent],xcMeanSysErr[icent]);
        drawLatex(0.52,0.805,name,132,0.04,4);
        float yposition = 0.805 - 0.05;
        for(int iModel=0; iModel<nModel; iModel++) {
            sprintf(name,"%s: %.1f", nameModel1[iModel],xcModel[icent][iModel]);
            drawLatex(0.52,yposition,name,132,0.04,4);
            yposition = yposition - 0.05;
        }
        cout<<"zyjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj"<<xcCountSys[icent]<<"and "<<xcCount[icent]<<endl;
        sprintf(name,"data: %.1f #pm %.1f (stat.) #pm %.1f (sys.) (#mub)", xcCount[icent],xcCountStat[icent]*xcCount[icent], xcCountSys[icent]*xcCount[icent]);
        drawLatex(0.2,0.15,name,132,0.04,4);
        
        //sprintf(name,"Sys. Error from extrapolation: %.1f", xcSysFit[icent]);
        //drawLatex(0.2,0.15,name,132,0.04,4);
        
        //const float legy_lw = 0.9 - 0.05*nMod;
        float leg_up = 0.94;
        float leg_lw = leg_up - 0.05*(2+nModel);
        legend = new TLegend(0.2,leg_lw,0.5,leg_up);
        legend->SetFillStyle(0);
        legend->SetFillColor(10);
        legend->SetBorderSize(0);
        legend->SetTextSize(0.04);
        legend->SetTextFont(132);
        legend->AddEntry(hSpectraErr[icent],"Data","lp");
        legend->AddEntry(hLcMean[icent],"Fit: mean","l");
        for(int iModel=0; iModel<nModel; iModel++) legend->AddEntry(fModel[icent][iModel],nameModel1[iModel],"l");
        legend->Draw();
        
        c1->SetLogy();
        sprintf(name,"%s/%s_%s_Integral_new.gif",dir,namePar1,nameCent2[icent]);
        c1->SaveAs(name);
    }
    
    // print
    for(int icent=0; icent<ncent; icent++) {
        cout << nameCent1[icent] << endl;
        cout << "pt \t data \t\t stat. \t\t sys. \t\t di-quark \t three-quark \t Greco \t\t Tshingua \t mean \t\t diff(nSigma)" << endl;
        for(int ipt=0; ipt<npt; ipt++) {
            float num = gSpectraErr[icent]->GetY()[ipt];
            float err = gSpectraErr[icent]->GetEY()[ipt];
            float sys = gSpectraSys[icent]->GetEY()[ipt];
            cout << ptbin[ipt] << "-" << ptbin[ipt+1] << "\t";
            cout << num << "\t" << err << "\t";
            cout << sys << "\t";
            float sum = 0;
            for(int iModel=0; iModel<nModel; iModel++) {
                cout << fModel[icent][iModel]->Integral(ptbin[ipt],ptbin[ipt+1]) / (ptbin[ipt+1] - ptbin[ipt]) << "\t";
                sum += fModel[icent][iModel]->Integral(ptbin[ipt],ptbin[ipt+1]) / (ptbin[ipt+1] - ptbin[ipt]);
            }
            float nSigma = fabs(sum/nModel - num) / sqrt(pow(err,2)+pow(sys,2));
            cout << sum/nModel << "\t" << nSigma << endl;
        }
    }
    
    // write
    TFile* fout = new TFile(Form("out/%s_Integral.root",namePar1), "RECREATE");
    for(int icent=0; icent<ncent; icent++) {
        hLcMean[icent]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
        hLcMean[icent]->GetYaxis()->SetTitle("d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-1}");
        hLcMean[icent]->SetTitle("mean from all model");
        sprintf(name, "h%s_spectra_%s_mean", namePar1, nameCent2[icent]);
        hLcMean[icent]->SetName(name);
        hLcMean[icent]->Write();
        for(int iModel=0; iModel<nModel; iModel++) {
            sprintf(title,"%s, %s",nameCent1[icent],nameModel1[iModel]);
            fModel[icent][iModel]->SetTitle(title);
            sprintf(name,"fModel_cent%i_model%i",icent,iModel);
            fModel[icent][iModel]->Write(name);
        }
        //sprintf(name, "g%s_spectra_%s_mean", namePar1, nameCent[icent]);
        //gLcMean[icent]->Write(name);
    }
    fout->Close();
    
    for(int icent=0; icent<ncent; icent++) {
        cout << nameCent1[icent] <<  ", Lc mean pt: " << endl;
        for(int iModel=0; iModel<nModel; iModel++) {
            cout << nameModel1[iModel] << ": " << getMean(fModel[icent][iModel], 0, 8) << endl;
        }
        cout << "Mean: " << getMean(hLcMean[icent]) << endl;
    }
    
    
    // write original model
    TFile* fout_model = new TFile("Ratio_Lc2D0_Fitted.root","RECREATE");
    for(int iModel=0; iModel<nModel; iModel++) {
        gModel[iModel]->Write();
    }
    
    // re-set fitted model
    for(int iModel=0; iModel<nModel; iModel++) {
        for(int iP=0; iP<gModel_Fit[iModel]->GetN(); iP++) {
            gModel_Fit[iModel]->GetY()[iP] *= ratio[iModel];
        }
        sprintf(title, "scale = %.2f #pm %.2f, Chi2/NDF = %.1f/%.0f", ratio[iModel], ratio_err[iModel], chi2[iModel], ndf[iModel]);
        gModel_Fit[iModel]->SetTitle(title);
        gModel_Fit[iModel]->Write();
    }
    
    // mean
    for(int i=0; i<50; i++) {
        x_value[i] = 6.0 / 50 * (i + 0.5);
        y_value[i] = 0;
        for(int iModel=0; iModel<nModel; iModel++) y_value[i] += gModel_Fit[iModel]->Eval(x_value[i]);
        y_value[i] /= nModel;
    }
    TGraph* gModel_mean = new TGraph(50, x_value, y_value);
    gModel_mean->Write("Mean_Fitted");
    
    fout_model->Close();
    
    // test efficiency
    
}
