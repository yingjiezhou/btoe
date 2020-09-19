#include "myFunction.h"
void plot_Dpm_Ratio() {
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
    
    /*const int ncent = 4;
    const char nameCent[ncent][250] = {"0_10", "10_40", "40_80", "0_80"};
    const char nameCent1[ncent][250] = {"0-10%", "10-40%", "40-80%", "0-80%"};
    const float Nbin[ncent] = {938.80170, 386.08527, 56.99229, 301.05848};*/
    const int ncent = 1;
    const char nameCent[ncent][250] = {"0-10%"};
    const char nameCent1[ncent][250] = {"010"};
    const char nameCent2[ncent][250] = {"0_10"};
    const float Nbin[ncent] = {938.80170};
    const float scale[ncent] = {0.246/0.565};
    
    const char namePar[250] = "D^{#pm}";
    const char namePar1[250] = "Dpm";
    const char namePrint[250] = "AuAu 200 GeV";
    
    //const int npt = 4;
    //const double ptbin[npt+1] = {1.5, 2.5, 3.5, 5.0, 8.0};
    const int npt = 10;
    const double ptbin[npt + 1] =  {2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 7.0, 8.0};
    const float xmin = 1.5;
    const float xmax = 8.5;
    
    const float tpcSys[ncent] = {0.0646246};
    const int firstD0PointId[ncent] = {3}; // 0-1, 1-2, ...
    
    // read D+/-
    TGraphErrors* gSpectraSys[ncent];
    TGraphErrors* gSpectraErr[ncent];
    fin = new TFile("data/DpmYieldRaaRun14.root");
    for(int icent=0; icent<ncent; icent++) {
        gSpectraErr[icent] = (TGraphErrors*)fin->Get(Form("Yield_stat_%s",nameCent1[icent]));
        gSpectraSys[icent] = (TGraphErrors*)fin->Get(Form("Yield_sys_%s",nameCent1[icent]));
        
        cout << gSpectraErr[icent]->Eval(4) << endl;
    }
    fin->Close();
    
    // read D0
    TGraphErrors* gSpectraSysD0[ncent];
    TGraphErrors* gSpectraErrD0[ncent];
    fin = new TFile("data/D0_Spectra_Run14HFT.forxlchen.0512.root");
    for(int icent=0; icent<ncent; icent++) {
        gSpectraErrD0[icent] = (TGraphErrors*)fin->Get(Form("gD0_err_%s",nameCent2[icent]));
        gSpectraSysD0[icent] = (TGraphErrors*)fin->Get(Form("gD0_sys_%s",nameCent2[icent]));
    }
    fin->Close();
    
    // scale
    for(int icent=0; icent<ncent; icent++) {
        for(int ipt=0; ipt<gSpectraErr[icent]->GetN(); ipt++) {
            gSpectraErr[icent]->GetY()[ipt] *= scale[icent];
            gSpectraErr[icent]->GetEY()[ipt] *= scale[icent];
            
            gSpectraSys[icent]->GetY()[ipt] *= scale[icent];
            gSpectraSys[icent]->GetEY()[ipt] *= scale[icent];
        }
    }
    
        
    // calculate ratio
    TH1F* hRatio[ncent];
    for(int icent=0; icent<ncent; icent++) {
        hRatio[icent] = new TH1F(Form("hRatio_%s",nameCent1[icent]),"",npt,ptbin);
        for(int ipt=0; ipt<npt; ipt++) {
            float numD0 = gSpectraErrD0[icent]->GetY()[firstD0PointId[icent]+ipt];
            float errD0 = gSpectraErrD0[icent]->GetEY()[firstD0PointId[icent]+ipt];
            float sysD0 = gSpectraSysD0[icent]->GetEY()[firstD0PointId[icent]+ipt];
            
            float numDpm = gSpectraErr[icent]->GetY()[ipt];
            float errDpm = gSpectraErr[icent]->GetEY()[ipt];
            float sysDpm = gSpectraSys[icent]->GetEY()[ipt];
            
            //cout << numDpm/numD0 << endl;
            
            // remove TPC sys error (D0 part --> Kpi)
            sysD0 = sqrt(sysD0*sysD0 - pow(numD0*tpcSys[icent],2));
            sysDpm = sqrt(sysDpm*sysDpm - pow(numDpm*tpcSys[icent],2));
            cout << sysD0/numD0 << "\t" << sysDpm/numDpm << endl;
            
            float ratio = numDpm/numD0;
            float ratioErr = ratio*sqrt(pow(errD0/numD0,2)+pow(errDpm/numDpm,2));
            float ratioSys = ratio*sqrt(pow(sysD0/numD0,2)+pow(sysDpm/numDpm,2));
            float errAll = sqrt(pow(ratioErr,2) + pow(ratioSys,2));
            hRatio[icent]->SetBinContent(ipt+1,ratio);
            hRatio[icent]->SetBinError(ipt+1,errAll);
        }
    }
    
    for(int icent=0; icent<ncent; icent++) {
        // fit
        TF1* fline = new TF1("line","[0]",ptbin[0],ptbin[npt]);
        fline->SetParameter(0,hRatio[icent]->GetBinContent(1));
        hRatio[icent]->Fit(fline,"NOR","",ptbin[0],ptbin[npt]);
        hRatio[icent]->Fit(fline,"NOR","",ptbin[0],ptbin[npt]);
        
        // set
        setHisto(hRatio[icent],"","p_{T} (GeV/c)", "D^{+} / D^{0}");
        hRatio[icent]->GetYaxis()->SetRangeUser(0,1);
        hRatio[icent]->SetMarkerStyle(kFullCircle);
        hRatio[icent]->SetMarkerSize(2.0);
        hRatio[icent]->SetMarkerColor(kBlack);
        hRatio[icent]->SetLineColor(kBlack);
        hRatio[icent]->SetLineWidth(2);
        hRatio[icent]->Draw("e");
        
        fline->Draw("same");
        fline->SetLineColor(2);
        fline->SetLineWidth(2);
        fline->SetLineStyle(5);
        
        sprintf(name,"%s, %s",namePrint,nameCent[icent]);
        drawLatex(0.52,0.89,name,132,0.04,1);
        sprintf(name,"D^{+}/D^{0} = %.3f #pm %.3f",fline->GetParameter(0), fline->GetParError(0));
        drawLatex(0.52,0.82,name,132,0.04,1);
        drawLatex(0.52,0.75,Form("#chi^{2}/ndf = %0.1f/%d",fline->GetChisquare(),fline->GetNDF()),132,0.04,kBlack);
        
        sprintf(name,"%s/%s_%s_Ratio.gif",dir,namePar1,nameCent2[icent]);
        c1->SaveAs(name);
    }
    
    
}
