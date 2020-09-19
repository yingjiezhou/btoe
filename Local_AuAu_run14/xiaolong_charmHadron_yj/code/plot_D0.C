#include "./myFunction.h"
void plot_D0() {
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
    
    const int ncent = 9;
    const char nameCent[ncent][250] = {"0_10", "10_20", "20_40", "40_60", "60_80", "10_40", "40_80", "0_80", "10_80"};
    const char nameCent1[ncent][250] = {"0-10%", "10-20%", "20-40%", "40-60%", "60-80%", "10-40%", "40-80%", "0-80%", "10-80%"};
    const float Nbin[ncent] = {938.80170, 579.89409, 288.35051, 91.37100, 21.37396, 386.08527, 56.99229, 301.05848, 198.};
    
    const char namePar[250] = "D^{0}";
    const char namePar1[250] = "D0";
    const char namePrint[250] = "AuAu 200 GeV";
    
    const int npt = 11;
    const float ptbin[npt+1] = {0, 0.5, 1, 1.5, 2, 2.5, 3, 4, 5, 6, 8, 10};
    const float xmin = 0;
    const float xmax = 20.;
    
    TH1F* hPtBase = new TH1F("hPtBase","hPtBase",npt,ptbin);
    
    // read
    TGraphErrors* gSpectraUp[ncent];
    TGraphErrors* gSpectraSys[ncent];
    TGraphErrors* gSpectraErr[ncent];
    TGraphErrors* gBand[ncent];
    TF1* fSpectra[ncent];
    TFile* fin = new TFile("./data/D0_Spectra_Run14HFT.0401.root");
    for(int icent=0; icent<ncent; icent++) {
        gSpectraUp[icent] = (TGraphErrors*)fin->Get(Form("gD0_err_%s",nameCent[icent]));
        gSpectraErr[icent] = (TGraphErrors*)fin->Get(Form("gD0_err_%s",nameCent[icent]));
        gSpectraSys[icent] = (TGraphErrors*)fin->Get(Form("gD0_sys_%s",nameCent[icent]));
        //gBand[icent] = (TGraphErrors*)fin->Get(Form("flevy_err_band_%s",nameCent[icent]));
        //fSpectra[icent] = (TF1*)fin->Get(Form("flevy_%s",nameCent[icent]));
    }
    fin->Close();
    
    // shift sys. err
    for(int icent=0; icent<ncent; icent++) {
        for(int ipt=0; ipt<gSpectraUp[icent]->GetN(); ipt++) {
            //float err = gSpectraErr[icent]->GetEY()[ipt];
            float sys = gSpectraSys[icent]->GetEY()[ipt];
            float mean = gSpectraErr[icent]->GetY()[ipt];
            gSpectraUp[icent]->GetY()[ipt] = mean+sys; // zyj move each data points up to mean + sys and fit again
        }
    }
    
    // test
    for(int icent=0; icent<ncent; icent++) {
        for(int ipt=0; ipt<gSpectraUp[icent]->GetN(); ipt++) {
            //gSpectraErr[icent]->GetEY()[ipt] = gSpectraErr[icent]->GetY()[ipt]*0.1;
        }
    }
    
    // fit
    //define fit function, now use levy function
    char funcString[200];
    char funcString_time_pt[200];
    double m0 = 1.8645;//D0-1.8645, D+/- - 1.8693;
    sprintf(funcString,"(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+%f*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+%f*%f)-%f)/([2]*[1]),-[2])",m0,m0,m0,m0); // dN/pTdpTdy
    sprintf(funcString_time_pt,"(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+%f*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+%f*%f)-%f)/([2]*[1]),-[2])*x[0]",m0,m0,m0,m0); // dN/dpTdy
    const float fitR_lw = ptbin[0];
    const float fitR_up = ptbin[npt];
    const float fitR_lw_powlaw = 2.5;
    const char fitOpt[100] = "ENOR";
    TF1* flevyUp[ncent];
    TF1* fpowLaw[ncent];
    
    const float factor = 42.*1000; // ub
    const float twoPI = 2.*TMath::Pi();
    float xc[ncent], xc_up[ncent], xcErr[ncent], xcStatErr[ncent], xcSysErr[ncent];
    float xc_check[ncent], xcErr_check[ncent], xcStatErr_check[ncent], xcSysErr_check[ncent];
    // init
    for(int icent=0; icent<ncent; icent++) {
        xc[icent] = 0; xc_up[icent] = 0; xcErr[icent] = 0; xcErr[icent] = 0; xcStatErr[icent] = 0; xcSysErr[icent] = 0;
        xc_check[icent] = 0; xcErr_check[icent] = 0; xcStatErr_check[icent] = 0; xcSysErr_check[icent] = 0;
    }
    for(int icent=0; icent<ncent; icent++) {
        fSpectra[icent] = new TF1("fSpectra",funcString,0,20);
        fSpectra[icent]->SetParameters(6.25342e-01,3.34550e-01,1.86042e+01);
        gSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        gSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        gSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        
        const Int_t NCL = 400;
        gBand[icent] = new TGraphErrors(NCL);
        gBand[icent]->SetTitle("Fitted line with .68 conf. band");
        for (int i=0; i<NCL; i++) gBand[icent]->SetPoint(i, 0.025 + i*0.05, 0);
        (TVirtualFitter::GetFitter())->GetConfidenceIntervals(gBand[icent],0.68);
        gBand[icent]->SetName(Form("flevy_err_band_%s",nameCent[0]));
        float chidf = TMath::Sqrt(fSpectra[icent]->GetChisquare()/fSpectra[icent]->GetNDF());
        for(int ipoint=0; ipoint<gBand[icent]->GetN(); ipoint++) {
            gBand[icent]->GetEY()[ipoint] = gBand[icent]->GetEY()[ipoint]/chidf; // zyj 1σ error from Levy fit
        }
        
        fpowLaw[icent] = new TF1("fpow-law",PowLaw,fitR_lw_powlaw,20,3);
        fpowLaw[icent]->SetParameters(1.80265e-01,3.90637e+01,1.16876e+00);
        gSpectraErr[icent]->Fit(fpowLaw[icent], fitOpt, "", fitR_lw_powlaw, fitR_up);
        gSpectraErr[icent]->Fit(fpowLaw[icent], fitOpt, "", fitR_lw_powlaw, fitR_up);
        gSpectraErr[icent]->Fit(fpowLaw[icent], fitOpt, "", fitR_lw_powlaw, fitR_up);
        gSpectraErr[icent]->Fit(fpowLaw[icent], fitOpt, "", fitR_lw_powlaw, fitR_up);
        
        xc[icent] = 0; xc_up[icent] = 0;
        for(int i=0; i<gBand[icent]->GetN()-1; i++) {
            float ptw = gBand[icent]->GetX()[2] - gBand[icent]->GetX()[1];
            float pt = gBand[icent]->GetX()[i]+0.5*ptw;
            float ymean = 0.5*(gBand[icent]->GetY()[i]+gBand[icent]->GetY()[i+1]);
            float yup = ymean + 0.5*(gBand[icent]->GetEY()[i]+gBand[icent]->GetEY()[i+1]);
            xc[icent] += ymean*twoPI*pt*ptw*factor / Nbin[icent];
            xc_up[icent] += yup*twoPI*pt*ptw*factor / Nbin[icent];
            xcStatErr[icent] = fabs(xc_up[icent] - xc[icent]);
        }
        
        flevyUp[icent] = new TF1("flevy",funcString,0,10);
        flevyUp[icent]->SetParameters(6.25342e-01,3.34550e-01,1.86042e+01);
        gSpectraUp[icent]->Fit(flevyUp[icent], fitOpt, "", fitR_lw, fitR_up);
        gSpectraUp[icent]->Fit(flevyUp[icent], fitOpt, "", fitR_lw, fitR_up);
        gSpectraUp[icent]->Fit(flevyUp[icent], fitOpt, "", fitR_lw, fitR_up);
        
        // calculate band
        for(int ipt=0; ipt<gBand[icent]->GetN(); ipt++) {
            float pt = gBand[icent]->GetX()[ipt];
            float sys = fabs(flevyUp[icent]->Eval(pt) - fSpectra[icent]->Eval(pt));
            float err = gBand[icent]->GetEY()[ipt];
            //cout << err << "\t" << sys << "\t" << pt << "\t" << gBand[icent]->GetY()[ipt] << "\t" << sqrt(pow(err,2)+pow(sys,2)) << endl;
            gBand[icent]->GetEY()[ipt] = sqrt(pow(err,2)+pow(sys,2)); // zyj here we will get the final gBand error
        }
        
        xc[icent] = 0; xc_up[icent] = 0;
        for(int i=0; i<gBand[icent]->GetN()-1; i++) {
            float ptw = gBand[icent]->GetX()[2] - gBand[icent]->GetX()[1];
            float pt = gBand[icent]->GetX()[i]+0.5*ptw;
            float ymean = 0.5*(gBand[icent]->GetY()[i]+gBand[icent]->GetY()[i+1]);
            float yup = ymean + 0.5*(gBand[icent]->GetEY()[i]+gBand[icent]->GetEY()[i+1]);
            xc[icent] += ymean*twoPI*pt*ptw*factor / Nbin[icent];
            xc_up[icent] += yup*twoPI*pt*ptw*factor / Nbin[icent];
            xcSysErr[icent] = fabs(xc_up[icent] - xc[icent]);
            xcSysErr[icent] = sqrt(pow(xcSysErr[icent],2) - pow(xcStatErr[icent],2));
        }
    }
    
    
    // calculte
    for(int icent=0; icent<ncent; icent++) {
        xc[icent] = 0; xc_up[icent] = 0;
        for(int i=0; i<gBand[icent]->GetN()-1; i++) {
            float ptw = gBand[icent]->GetX()[2] - gBand[icent]->GetX()[1];
            float pt = gBand[icent]->GetX()[i]+0.5*ptw;
            float ymean = 0.5*(gBand[icent]->GetY()[i]+gBand[icent]->GetY()[i+1]);
            float yup = ymean + 0.5*(gBand[icent]->GetEY()[i]+gBand[icent]->GetEY()[i+1]);
            //cout << pt << "\t" << ptw << "\t" << ymean << "\t" << yup << endl;
            //cout << gBand[icent]->GetN() << endl;
            xc[icent] += ymean*twoPI*pt*ptw*factor / Nbin[icent];
            xc_up[icent] += yup*twoPI*pt*ptw*factor / Nbin[icent];
            xcErr[icent] = fabs(xc_up[icent] - xc[icent]);
            //xcSysErr[icent] = fabs(xc_up[icent] - xc[icent]);
        }
        cout << nameCent1[icent] << endl;
        cout << "from fit: xc = " << xc[icent] << ",\t stat. err = " << xcStatErr[icent] << ",\t sys. err = " << xcSysErr[icent] << ",\t total err = " << xcErr[icent] << endl;
        
        for(int i=0; i<npt; i++) {
            float pt = (ptbin[i] + ptbin[i+1])*0.5;
            float ptw = ptbin[i+1] - ptbin[i];
            float ymean = gSpectraErr[icent]->GetY()[i];
            float yerr = gSpectraErr[icent]->GetEY()[i];
            //if(pt<1.5) continue; 
            xc_check[icent] += ymean*twoPI*pt*ptw*factor / Nbin[icent];
            xcStatErr_check[icent] += pow(yerr*twoPI*pt*ptw*factor / Nbin[icent],2);
        }
        xcStatErr_check[icent] = sqrt(xcStatErr_check[icent]);
        xc_check[icent] = 0;
        for(int i=0; i<npt; i++) {
            float pt = (ptbin[i] + ptbin[i+1])*0.5;
            float ptw = ptbin[i+1] - ptbin[i];
            float ymean = gSpectraSys[icent]->GetY()[i];
            float yerr = gSpectraSys[icent]->GetEY()[i];
            //if(pt<1.5) continue;
            xc_check[icent] += ymean*twoPI*pt*ptw*factor / Nbin[icent];
            // xcSysErr_check[icent] += pow(yerr*twoPI*pt*ptw*factor / Nbin[icent],2);  // no correlation
            xcSysErr_check[icent] += yerr*twoPI*pt*ptw*factor / Nbin[icent]; // fully correlation
        }
        //xcSysErr_check[icent] = sqrt(xcSysErr_check[icent]);
        xcErr_check[icent] = sqrt(pow(xcStatErr_check[icent],2) + pow(xcSysErr_check[icent],2));
        cout << "from data point: xc = " << xc_check[icent] << ",\t stat. err = " << xcStatErr_check[icent] << ",\t sys. err = " << xcSysErr_check[icent] << ",\t total err = " << xcErr_check[icent] << endl;
    }
    
    // calculate mean D0 and its total error band -- gBand
    TH1F* hSpectra[ncent];
    for(int icent=0; icent<ncent; icent++) {
        for(int i=0; i<gBand[icent]->GetN(); i++) {
            float pt = gBand[icent]->GetX()[i];
            float y_levy = fSpectra[icent]->Eval(pt);
            float yerr_levy = gBand[icent]->GetEY()[i]/gBand[icent]->GetY()[i];
            float y_powl = pt>fitR_lw_powlaw ? fpowLaw[icent]->Eval(pt) : y_levy;
            float ymean = 0.5 * (y_levy + y_powl);
            float yerr_powl = 0.5 * fabs(y_levy - y_powl)/ymean;
            float yerr = sqrt(pow(yerr_levy,2) + pow(yerr_powl,2));
            gBand[icent]->GetY()[i] = ymean;
            gBand[icent]->GetEY()[i] = ymean * yerr;
            
            //if(icent==0) cout << i << "\t" << pt << endl;
            //if(icent==7) cout << i << "\t" << yerr_levy << "\t" << yerr_powl << "\t" << yerr << endl;
            //if(icent==7) cout << i << "\t" << nameCent[icent] << "\t" << pt << "\t" << gBand[icent]->GetY()[i] << "\t" << gBand[icent]->GetEY()[i] << endl;
        }
        
        sprintf(name, "h%s_spectra_%s", namePar1, nameCent[icent]);
        sprintf(title, ";p_{T} (GeV/c);d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-1}");
        const int nBins = gBand[icent]->GetN();
        hSpectra[icent] = new TH1F(name,title,nBins,0,20);
        for(int ibin=0; ibin<nBins; ibin++) {
            hSpectra[icent]->SetBinContent(ibin+1,gBand[icent]->GetY()[ibin]); // zyj here is what we will use in weight
            hSpectra[icent]->SetBinError(ibin+1,gBand[icent]->GetEY()[ibin]);
            //if(icent==7) cout << ibin << "\t" << hSpectra[icent]->GetBinContent(ibin+1) << "\t" << hSpectra[icent]->GetBinError(ibin+1) << "\t" << gBand[icent]->GetY()[ibin] << "\t" << gBand[icent]->GetEY()[ibin] << endl;
        }
    }
    
    // plot
    for(int icent=0; icent<ncent; icent++) {
        float ymin = 0.5*fSpectra[icent]->Eval(xmax);
        float ymax = 10.*fSpectra[icent]->Eval(xmin);
        h0 = new TH1F("","",1,xmin,xmax);
        h0->GetYaxis()->SetRangeUser(ymin,ymax);
        setHisto(h0,"","p_{T} (GeV/c)", "d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");
        h0->Draw();
        
        gBand[icent]->SetFillStyle(3001);
        gBand[icent]->SetFillColor(kGreen);
        gBand[icent]->SetFillColorAlpha(kGreen,0.4);
        //gBand[icent]->Draw("e3same");
        
        TH1F* hSpectraCopy = (TH1F*)hSpectra[icent]->Clone(Form("tmp_%i",icent));
        hSpectra[icent]->SetLineColor(1);
        hSpectra[icent]->SetLineWidth(2);
        hSpectra[icent]->SetFillColorAlpha(kGreen,0.4);
        hSpectra[icent]->Draw("e3same");
        hSpectraCopy->SetLineColor(1);
        hSpectraCopy->SetLineWidth(2);
        hSpectraCopy->Draw("chistSame");
        
        fSpectra[icent]->SetLineColor(kRed);
        fSpectra[icent]->SetLineWidth(2);
        fSpectra[icent]->SetLineStyle(7);
        fSpectra[icent]->Draw("same");
        
        fpowLaw[icent]->SetLineColor(kBlue);
        fpowLaw[icent]->SetLineWidth(2);
        fpowLaw[icent]->SetLineStyle(7);
        fpowLaw[icent]->Draw("same");
        
        /*flevyUp[icent]->SetLineColor(kBlue);
        flevyUp[icent]->SetLineWidth(2);
        flevyUp[icent]->SetLineStyle(7);
        flevyUp[icent]->Draw("same");*/
        
        gSpectraErr[icent]->SetMarkerStyle(kFullCircle);
        gSpectraErr[icent]->SetMarkerSize(1.5);
        gSpectraErr[icent]->SetMarkerColor(kBlack);
        gSpectraErr[icent]->SetLineColor(kBlack);
        gSpectraErr[icent]->SetLineWidth(2);
        gSpectraErr[icent]->Draw("psame");
        
        //draw systematic error
        const float sysw = 0.15;
        for(int i=0; i<gSpectraSys[icent]->GetN(); i++) {
            const float sysl = gSpectraSys[icent]->GetY()[i] * 0.05;
            TLine *llw = new TLine(gSpectraSys[icent]->GetX()[i]-sysw,gSpectraSys[icent]->GetY()[i]-gSpectraSys[icent]->GetEY()[i],gSpectraSys[icent]->GetX()[i]+sysw,gSpectraSys[icent]->GetY()[i]-gSpectraSys[icent]->GetEY()[i]);
            llw->SetLineWidth(2);
            llw->SetLineColor(kBlack);
            llw->Draw("same");
            TLine *lhi = new TLine(gSpectraSys[icent]->GetX()[i]-sysw,gSpectraSys[icent]->GetY()[i]+gSpectraSys[icent]->GetEY()[i],gSpectraSys[icent]->GetX()[i]+sysw,gSpectraSys[icent]->GetY()[i]+gSpectraSys[icent]->GetEY()[i]);
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
        drawLatex(0.52,0.89,name,132,0.04,1);
        sprintf(name,"%s cross section (#mub)",namePar);
        drawLatex(0.52,0.82,name,132,0.04,4);
        sprintf(name,"Fit: %.1f #pm %.1f(stat.) #pm %.1f(sys.)",xc[icent],xcStatErr[icent],xcSysErr[icent]);
        drawLatex(0.47,0.77,name,132,0.04,4);
        sprintf(name,"Count: %.1f #pm %.1f(stat.) #pm %.1f(sys.)",xc_check[icent],xcStatErr_check[icent],xcSysErr_check[icent]);
        drawLatex(0.422,0.72,name,132,0.04,4);
        
        //const float legy_lw = 0.9 - 0.05*nMod;
        legend = new TLegend(0.5,0.55,0.85,0.7);
        legend->SetFillStyle(0);
        legend->SetFillColor(10);
        legend->SetBorderSize(0);
        legend->SetTextSize(0.04);
        legend->SetTextFont(132);
        legend->AddEntry(fSpectra[icent],"Levy","l");
        legend->AddEntry(fpowLaw[icent],Form("Power-law (p_{T} > %.1f)",fitR_lw_powlaw),"l");
        legend->AddEntry(hSpectra[icent],"Total error","lf");
        legend->Draw();
        
        c1->SetLogy();
        sprintf(name,"%s/%s_%s.gif",dir,namePar1,nameCent[icent]);
        c1->SaveAs(name);
    }
    
    // write
    for(int icent=0; icent<ncent; icent++) {
        for(int ibin=0; ibin<hSpectra[icent]->GetNbinsX(); ibin++) {
            float ptCenter = hSpectra[icent]->GetBinCenter(ibin+1);
            float mean = hSpectra[icent]->GetBinContent(ibin+1);
            float err = hSpectra[icent]->GetBinError(ibin+1);
            hSpectra[icent]->SetBinContent(ibin+1,mean*twoPI*ptCenter);
            hSpectra[icent]->SetBinError(ibin+1,err*twoPI*ptCenter);
        }
    }
    TFile* fout = new TFile(Form("out/%s.root",namePar1), "RECREATE");
    for(int icent=0; icent<ncent; icent++) {
        gSpectraErr[icent]->SetTitle(";p_{T} (GeV/c);d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");
        sprintf(name, "%s_%s_err", namePar1, nameCent[icent]);
        gSpectraErr[icent]->SetName(name);
        gSpectraErr[icent]->Write();
        gSpectraSys[icent]->SetTitle(";p_{T} (GeV/c);d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");
        sprintf(name, "%s_%s_sys", namePar1, nameCent[icent]);
        gSpectraSys[icent]->SetName(name);
        gSpectraSys[icent]->Write();
        sprintf(name, "%s_%s_levy", namePar1, nameCent[icent]);
        fSpectra[icent]->SetName(name);
        fSpectra[icent]->Write();
        sprintf(name, "%s_%s_powerLaw", namePar1, nameCent[icent]);
        fpowLaw[icent]->SetName(name);
        fpowLaw[icent]->Write();
        hSpectra[icent]->Write();
    }
    fout->Close();
}
