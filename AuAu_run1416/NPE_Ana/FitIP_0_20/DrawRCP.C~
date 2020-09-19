void DrawRCP()
{//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    TH1F *hrat = new TH1F("hrat","hrat",numPtBins,binning);  

    TFile *f1 = new TFile("../FitIP/root/FracB.root");
    fb= (TH1F*)f1->Get("fb");
    fb_sys= (TH1F*)f1->Get("fb_sys");
    FONLL= (TH1F*)f1->Get("FONLL");
    pp= (TH1F*)f1->Get("pp");
    pp_sys= (TH1F*)f1->Get("pp_sys");
    fb_sys->SetFillColor(kGray);

    TFile *f1 = new TFile("./root/FracB_0_20.root");
    fb_0_20= (TH1F*)f1->Get("fb_0_20");
    fb_sys_0_20= (TH1F*)f1->Get("fb_sys_0_20");
    fb_0_20->SetLineColor(kRed);
    fb_0_20->SetMarkerColor(kRed); 
    fb_0_20->SetMarkerStyle(26);    
    fb_sys_0_20->SetFillColor(kGray);
    TFile *f2 = new TFile("../FitIP_20_80/root/FracB_20_80.root");
    fb_20_80= (TH1F*)f2->Get("fb_20_80");
    fb_sys_20_80= (TH1F*)f2->Get("fb_sys_20_80");
    fb_20_80->SetLineColor(kGreen-2);
    fb_20_80->SetMarkerColor(kGreen-2); 
    fb_20_80->SetMarkerStyle(27);     
    fb_sys_20_80->SetFillColor(kGreen-2);
    TFile *f3 = new TFile("../FitIP_40_80/root/FracB_40_80.root");
    fb_40_80= (TH1F*)f3->Get("fb_40_80");
    fb_sys_40_80= (TH1F*)f3->Get("fb_sys_40_80");
    fb_40_80->SetLineColor(kMagenta);
    fb_40_80->SetMarkerColor(kMagenta); 
    fb_40_80->SetMarkerStyle(25);     
    fb_sys_40_80->SetFillColor(kMagenta);
	
   
    for(int i = 1; i<numPtBins+1; i++){
	double temp1 = fb_0_20->GetBinContent(i);
	double temp2 = fb_20_80->GetBinContent(i);	
	double temp11 = fb_0_20->GetBinError(i);
	double temp22 = fb_20_80->GetBinError(i);
	if(temp1>0 && temp2>0){
	    hrat->SetBinContent(i,temp1/temp2);
	    hrat->SetBinError(i,temp1/temp2*sqrt(temp11*temp11/temp1/temp1+temp22*temp22/temp2/temp2));	    
	}

    }
    FONLL->SetLineStyle(7);
    pp->SetLineColor(kBlue);
    pp->SetMarkerColor(kBlue); 
    pp->SetMarkerStyle(23);     
    pp_sys->SetFillColor(kBlue);
    pp_sys->SetFillStyle(3004);
    TLegend *leg = new TLegend(0.2,0.57,0.47,0.9);
    leg->AddEntry(fb,"Min. Bias","PLE");
    leg->AddEntry(fb_0_20,"0-20%","PLE");
    leg->AddEntry(fb_20_80,"20-80%","PLE");
    leg->AddEntry(fb_40_80,"40-80%","PLE");
    leg->AddEntry(pp,"#it{p+p} #sqrt{s}=200 GeV","PLE");
    leg->AddEntry(FONLL,"FONLL","L");

    TCanvas *c1 = new TCanvas ("c1","fbs");
    fb->Draw("E1");
    fb_sys->Draw("E2 same");
    pp_sys->Draw("E2 same");
    pp->Draw("same PE");
    fb_0_20->Draw("E1 same");
    fb->Draw("E1 same");
    fb_40_80->Draw("E1 same");
    fb_20_80->Draw("E1 same");
  
    FONLL->Draw("l same");
    leg->Draw("same");
    gPad->RedrawAxis();
    TCanvas *c11 = new TCanvas ("c11","RCP/RCP");
    TF1 *fit = new TF1("fit","[0]",1,10);
    fit->SetLineColor(kBlue);
    fit->SetLineStyle(5);  
    TF1 *line = new TF1("line","[0]",-1,10);
    line->SetLineStyle(7); 
    line->SetParameter(0,1); 
    TLegend *legg = new TLegend(0.2,0.6,0.5,0.8);
    hrat->Fit("fit");
    char label[100];
    double vall = fit->GetParameter(0);
    double errr = fit->GetParError(0); 
    sprintf(label,"%1.2f #pm% 1.2f",vall,errr);
    legg->AddEntry(fit,label,"l");
    hrat->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    hrat->GetYaxis()->SetTitle("R_{CP}(#it{b}#rightarrow#it{e})/R_{CP}(#it{c}#rightarrow#it{e})");    
    hrat->GetXaxis()->SetRangeUser(0,8.5);
    hrat->GetYaxis()->SetRangeUser(0.5,2.5);  
    hrat->Draw("E1");
    line->Draw("same");
    legg->Draw("same");
    TPaveText *Name = new TPaveText(0.182,0.75,0.722,0.89,"BRNDC");
    Name->AddText("STAR Au+Au #sqrt{s_{NN}} = 200 GeV");
    Name->SetFillColorAlpha(0, 0);
    Name->SetTextAlign(12);
    Name->SetBorderSize(0);
    Name->Draw("same");
    gPad->RedrawAxis(); 

}//End
void norm(TH1F *h){
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
        double temp = h->GetBinContent(i);
        double width = h->GetBinWidth(i);
        double err = h->GetBinError(i);
        h->SetBinContent(i,temp/norm1);
        h->SetBinError(i,err/norm1);
    }
}
