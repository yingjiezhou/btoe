#include "./myFunction.h"
void plot_Ds_Integral() {
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
    
    /*const int ncent = 4;
     const char nameCent[ncent][250] = {"0_10", "10_40", "40_80", "0_80"};
     const char nameCent1[ncent][250] = {"0-10%", "10-40%", "40-80%", "0-80%"};
     const float Nbin[ncent] = {938.80170, 386.08527, 56.99229, 301.05848};*/
    const int ncent = 3;
    const char nameCent[ncent][250] = {"0", "1", "2"};
    const char nameCent1[ncent][250] = {"0-10%", "10-40%", "40-80%"};
    const float Nbin[ncent] = {938.80170, 386.08527};
    
    const char namePar[250] = "D_{s}^{+}";
    const char namePar1[250] = "Ds";
    const char namePrint[250] = "AuAu 200 GeV";
    
    const int npt = 3;
    const double ptbin[npt+1] = {2.5, 3.5, 5.0, 8.0};
    const float xmin = 0;
    const float xmax = 8;
    const float twoPI = 2.*TMath::Pi();
    
    TH1F* hPtBase = new TH1F("hPtBase","hPtBase",npt,ptbin);
    
    // read
    TGraphErrors* gSpectraSys[ncent];
    TGraphErrors* gSpectraErr[ncent];
    TGraphErrors* gBand[ncent];
    TF1* fSpectra[ncent];
    //TFile* fin = new TFile("./data/Run14_Ds_spectra_w_sys.root");
    TFile* fin = new TFile("./data/DsoverD0_AndSpectrum_new_test.root");
    for(int icent=0; icent<ncent; icent++) {
        gSpectraErr[icent] = (TGraphErrors*)fin->Get(Form("Ds_pTSepctrum_Combined_stat%s",nameCent[icent]));
        gSpectraSys[icent] = (TGraphErrors*)fin->Get(Form("Ds_pTSepctrum_Combined_sys%s",nameCent[icent]));
        //gBand[icent] = (TGraphErrors*)fin->Get(Form("flevy_err_band_%s",nameCent[icent]));
        //fSpectra[icent] = (TF1*)fin->Get(Form("flevy_%s",nameCent[icent]));
    }
    fin->Close();
    TH1F* hSpectraErr[ncent];
    for(int icent=0; icent<ncent; icent++) {
        hSpectraErr[icent] = new TH1F(Form("hSpectraErr_%i",icent),"hSpectraErr",npt,ptbin);
        for(int ipt=0; ipt<npt; ipt++) {
            float ptValue = 0.5*(ptbin[ipt]+ptbin[ipt+1]);//gSpectraErr[icent]->GetX()[ipt];
            //gSpectraErr[icent]->GetY()[ipt] *= (twoPI*ptValue);
            //gSpectraErr[icent]->GetEY()[ipt] *= (twoPI*ptValue);
            //gSpectraSys[icent]->GetY()[ipt] *= (twoPI*ptValue);
            //gSpectraSys[icent]->GetEY()[ipt] *= (twoPI*ptValue);
            
            //cout << nameCent[icent] << "\t" << gSpectraErr[icent]->GetY()[ipt] << "\t" << gSpectraErr[icent]->GetEY()[ipt] << endl;
            
            hSpectraErr[icent]->SetBinContent(ipt+1,gSpectraErr[icent]->GetY()[ipt]);
            hSpectraErr[icent]->SetBinError(ipt+1,gSpectraErr[icent]->GetEY()[ipt]);
        }
    }
    
    
    return ;
    // fit
    //define fit function, now use levy function
    char funcString[200];
    char funcString_time_pt[200];
    double m0 = 1.969;//D0-1.8645, D+/- - 1.8693;
    sprintf(funcString,"(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+%f*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+%f*%f)-%f)/([2]*[1]),-[2])",m0,m0,m0,m0); // dN/pTdpTdy
    sprintf(funcString_time_pt,"(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+%f*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+%f*%f)-%f)/([2]*[1]),-[2])*2.0*TMath::Pi()*x[0]",m0,m0,m0,m0); // dN/dpTdy
    float fitR_lw = ptbin[0];
    float fitR_up = ptbin[npt];
    const char fitOpt[100] = "INOR";
    TF1* flevyUp[ncent];
    TF1* fpowLaw[ncent];
    for(int icent=0; icent<ncent; icent++) {
        //fSpectra[icent] = new TF1("flevy",funcString,0,10);
        fSpectra[icent] = new TF1("flevy",funcString_time_pt,0,20);
        fSpectra[icent]->SetParameters(1.06664e-01,4.34012e-01,4.21147e+01);
        hSpectraErr[icent]->Fit(fSpectra[icent], "NOR", "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fSpectra[icent], "NOR", "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        //hSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        //hSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        //hSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        //hSpectraErr[icent]->Fit(fSpectra[icent], fitOpt, "", fitR_lw, fitR_up);
        
        // ==== Create a TGraphErrors to hold the confidence intervals
        const Int_t NCL = 200;
        //TGraphErrors *grint;
        gBand[icent] = new TGraphErrors(NCL);
        gBand[icent]->SetTitle("Fitted line with .68 conf. band");
        for (int i=0; i<NCL; i++) gBand[icent]->SetPoint(i, 0.05 + i*0.1, 0);
        (TVirtualFitter::GetFitter())->GetConfidenceIntervals(gBand[icent],0.68);
        gBand[icent]->SetName(Form("flevy_err_band_%s",nameCent1[0]));
        //float chidf = TMath::Sqrt(fSpectra[icent]->GetChisquare()/fSpectra[icent]->GetNDF());
        //for(int ipoint=0; ipoint<gBand[icent]->GetN(); ipoint++) {
        //    gBand[icent]->GetEY()[ipoint] = gBand[icent]->GetEY()[ipoint]/chidf;
        //}
        
        fpowLaw[icent] = new TF1("fpow-law",PowLaw_time_pt,0,20,3);
        fpowLaw[icent]->SetParameters(1.80265e-01,3.90637e+01,1.16876e+00);
        hSpectraErr[icent]->Fit(fpowLaw[icent], "NOR", "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fpowLaw[icent], "NOR", "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fpowLaw[icent], fitOpt, "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fpowLaw[icent], fitOpt, "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fpowLaw[icent], fitOpt, "", fitR_lw, fitR_up);
        hSpectraErr[icent]->Fit(fpowLaw[icent], fitOpt, "", fitR_lw, fitR_up);
    }
    
    
    // calculte
	const int nBins = 400;
    TH1F* hSpectra[ncent];
    for(int icent=0; icent<ncent; icent++) {
        sprintf(name, "h%s_spectra_%s", namePar1, nameCent[icent]);
        sprintf(title, ";p_{T} (GeV/c);d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-1}");
        
        hSpectra[icent] = new TH1F(name,title,nBins,0,20);
    }
    const float factor = 42.*1000; // ub
    float xc[ncent], xc_up[ncent], xcErr[ncent], xcStatErr[ncent], xcSysErr[ncent], xcSysFit[ncent];
    float xc_check[ncent], xcErr_check[ncent], xcStatErr_check[ncent], xcSysErr_check[ncent];
    // init
    for(int icent=0; icent<ncent; icent++) {
        xc[icent] = 0; xc_up[icent] = 0; xcErr[icent] = 0; xcStatErr[icent] = 0; xcSysErr[icent] = 0; xcSysFit[icent] = 0;
        xc_check[icent] = 0; xcErr_check[icent] = 0; xcStatErr_check[icent] = 0; xcSysErr_check[icent] = 0;
    }
    
    for(int icent=0; icent<ncent; icent++) {
        // calculate the err band in the region with data points
        float xcCount=0, xcLevy=0, xcPowl=0, xcMean=0, xcLevyAll=0, xcPowlAll=0, xcMeanAll=0;
        float xcCountStat=0, xcCountSys=0;
        // from fit
        for(int ibin=0; ibin<hSpectra[icent]->GetNbinsX(); ibin++) {
            float ptCenter = hSpectra[icent]->GetBinCenter(ibin+1);
            float ptw = hSpectra[icent]->GetBinWidth(ibin+1);
            float ymeanLevy = fSpectra[icent]->Eval(ptCenter);
            float ymeanPowL = fpowLaw[icent]->Eval(ptCenter);
            float ymean = (ymeanLevy + ymeanPowL)/2.;
            float ymeanData = gSpectraErr[icent]->Eval(ptCenter);
            float sysFit = fabs(ymeanLevy - ymeanPowL)/2./ymean;
            //int ipoint = hPtBase->FindBin(ptCenter) - 1;
            //float statErr = gSpectraErr[icent]->GetEY()[ipoint]/gSpectraErr[icent]->GetY()[ipoint];
            //float sysErr = gSpectraSys[icent]->GetEY()[ipoint]/gSpectraSys[icent]->GetY()[ipoint];
            //float err = ymean*sqrt(pow(statErr,2) + pow(sysErr,2) + pow(sysFit,2));
            
            if(ptCenter>ptbin[0] && ptCenter<ptbin[npt]) {
                xcLevy += ymeanLevy*ptw*factor / Nbin[icent];
                xcPowl += ymeanPowL*ptw*factor / Nbin[icent];
                xcMean += ymean*ptw*factor / Nbin[icent];
            }
            xcLevyAll += ymeanLevy*ptw*factor / Nbin[icent];
            xcPowlAll += ymeanPowL*ptw*factor / Nbin[icent];
            xcMeanAll += ymean*ptw*factor / Nbin[icent];
        }
        // from count
        for(int ipoint=0; ipoint<npt; ipoint++) {
            float ptCenter = gSpectraErr[icent]->GetX()[ipoint];
            float ptw = ptbin[ipoint+1] - ptbin[ipoint];
            float ymeanData = gSpectraErr[icent]->Eval(ptCenter);
            float statErr = gSpectraErr[icent]->GetEY()[ipoint]/gSpectraErr[icent]->GetY()[ipoint];
            float sysErr = gSpectraSys[icent]->GetEY()[ipoint]/gSpectraSys[icent]->GetY()[ipoint];
            //float err = mean*sqrt(pow(statErr,2) + pow(sysErr,2) + pow(sysFit,2));
            
            float xcCount0 = ymeanData*ptw*factor / Nbin[icent];
            xcCount += xcCount0;
            xcCountStat += pow(xcCount0*statErr,2);
            // xcCountSys += pow(xcCount0*sysErr,2); // no correlation
            xcCountSys += xcCount0*sysErr; // fully correlation
        }
        xcCountStat = sqrt(xcCountStat)/xcCount;
        //xcCountSys = sqrt(xcCountSys)/xcCount;
        xcCountSys = xcCountSys/xcCount;
        
        xc[icent] = xcMeanAll;
        xcSysFit[icent] = fabs(xcLevyAll - xcPowlAll)/2.;
        xcStatErr[icent] = xc[icent]*xcCountStat;
        xcSysErr[icent] = xc[icent]*sqrt(pow(xcCountSys,2)+pow(xcSysFit[icent]/xc[icent],2));
        
        cout << nameCent1[icent] << endl;
        cout << "from fit: Levy = " << xcLevy << ",\t PowerLaw = " << xcPowl << ",\t mean = " << xcMean << endl;
        cout << "from fit: Levy = " << xcLevyAll << ",\t PowerLaw = " << xcPowlAll << ",\t mean = " << xcMeanAll << endl;
        cout << "from data: mean = " << xcCount << ",\t stat.err(%) = " << xcCountStat << ",\t sys.err(%) = " << xcCountSys << endl;
        
        for(int ibin=0; ibin<nBins; ibin++) {
            float ptCenter = hSpectra[icent]->GetBinCenter(ibin+1);
            int ipoint = hPtBase->FindBin(ptCenter) - 1;
            float meanLevy = fSpectra[icent]->Eval(ptCenter);
            float meanPowL = fpowLaw[icent]->Eval(ptCenter);
            float mean = (meanLevy + meanPowL)/2.;
            float sysFit = fabs(meanLevy - meanPowL)/2./mean;
            float statErr = gSpectraErr[icent]->GetEY()[ipoint]/gSpectraErr[icent]->GetY()[ipoint];
            float sysErr = gSpectraSys[icent]->GetEY()[ipoint]/gSpectraSys[icent]->GetY()[ipoint];
            if(ptCenter<ptbin[0] || ptCenter>ptbin[npt]) {
                statErr = xcCountStat;
                sysErr = xcCountSys;
            }
            float err = mean*sqrt(pow(statErr,2) + pow(sysErr,2) + pow(sysFit,2));
            hSpectra[icent]->SetBinContent(ibin+1,mean);
            hSpectra[icent]->SetBinError(ibin+1,err);
            //if(ptCenter>1.5 && ptCenter<8) cout << ptCenter << "\t" << err/mean << endl;
        }
    }
    
    // plot
    for(int icent=0; icent<ncent; icent++) {
        float ymin = 0.5*fSpectra[icent]->Eval(19);
        float ymax = 10.*fSpectra[icent]->Eval(1);
        h0 = new TH1F("","",1,0,20);
        h0->GetYaxis()->SetRangeUser(ymin,ymax);
        setHisto(h0,"","p_{T} (GeV/c)", "d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-2}");
        h0->Draw();
        
        gBand[icent]->SetFillStyle(3001);
        gBand[icent]->SetFillColor(kOrange+2);
        gBand[icent]->SetFillColorAlpha(kOrange,0.4);
        //gBand[icent]->Draw("e3same");
        
        hSpectra[icent]->SetFillColorAlpha(kGreen,0.4);
        hSpectra[icent]->Draw("e3same");
        
        fSpectra[icent]->SetLineColor(kRed);
        fSpectra[icent]->SetLineWidth(2);
        fSpectra[icent]->SetLineStyle(7);
        fSpectra[icent]->Draw("same");
        
        fpowLaw[icent]->SetLineColor(kBlue);
        fpowLaw[icent]->SetLineWidth(2);
        fpowLaw[icent]->SetLineStyle(7);
        fpowLaw[icent]->Draw("same");
        
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
        drawLatex(0.52,0.89,name,132,0.04,1);
        sprintf(name,"%s cross section (#mub)",namePar);
        drawLatex(0.52,0.82,name,132,0.04,4);
        //sprintf(name,"Fit: %.1f #pm %.1f(stat.) #pm %.1f(sys.)",xc[icent],xcStatErr[icent],xcSysErr[icent]);
        //drawLatex(0.47,0.77,name,132,0.04,4);
        //sprintf(name,"Count: %.1f #pm %.1f(stat.) #pm %.1f(sys.)",xc_check[icent],xcStatErr_check[icent],xcSysErr_check[icent]);
        //drawLatex(0.422,0.72,name,132,0.04,4);
        sprintf(name,"Count: %.1f #pm %.1f(stat.) #pm %.1f(sys.)",xc[icent],xcStatErr[icent],xcSysErr[icent]);
        drawLatex(0.422,0.77,name,132,0.04,4);
        sprintf(name,"Sys. Error from extrapolation: %.1f", xcSysFit[icent]);
        drawLatex(0.2,0.15,name,132,0.04,4);
        
        //const float legy_lw = 0.9 - 0.05*nMod;
        legend = new TLegend(0.52,0.6,0.9,0.7);
        legend->SetFillStyle(0);
        legend->SetFillColor(10);
        legend->SetBorderSize(0);
        legend->SetTextSize(0.04);
        legend->SetTextFont(132);
        legend->AddEntry(fSpectra[icent],"Levy","l");
        legend->AddEntry(fpowLaw[icent],"Power-law","l");
        //legend->AddEntry(gModel[2],nameMod[2],"f");
        legend->Draw();
        
        c1->SetLogy();
        sprintf(name,"%s/%s_%s_Integral.gif",dir,namePar1,nameCent[icent]);
        c1->SaveAs(name);
    }
    
    // write
    /*for(int icent=0; icent<ncent; icent++) {
        for(int ibin=0; ibin<hSpectra[icent]->GetNbinsX(); ibin++) {
            float ptCenter = hSpectra[icent]->GetBinCenter(ibin+1);
            float mean = hSpectra[icent]->GetBinContent(ibin+1);
            float err = hSpectra[icent]->GetBinError(ibin+1);
            hSpectra[icent]->SetBinContent(ibin+1,mean*twoPI*ptCenter);
            hSpectra[icent]->SetBinError(ibin+1,err*twoPI*ptCenter);
        }
    }*/
    TFile* fout = new TFile(Form("out/%s_Integral.root",namePar1), "RECREATE");
    for(int icent=0; icent<ncent; icent++) {
        gSpectraErr[icent]->SetTitle(";p_{T} (GeV/c);d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-2}");
        sprintf(name, "%s_%s_err", namePar1, nameCent[icent]);
        gSpectraErr[icent]->SetName(name);
        gSpectraErr[icent]->Write();
        gSpectraSys[icent]->SetTitle(";p_{T} (GeV/c);d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-2}");
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
