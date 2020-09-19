void CompareEffCorrDca(int cor=1){
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};   
    TFile *f = new TFile("./root/DCA_plots.root");
    h1 =(TH2F*)f->Get("h1");
    h1->SetName("h1");
    h2 =(TH2F*)f->Get("dcapt_eh_all");
    h2->SetName("h2");
    h3 =(TH2F*)f->Get("dcapt_all");
    h3->SetName("h3");

    h2->SetLineColor(kRed);
    h2->SetMarkerColor(kRed);   
    h3->SetLineColor(kRed);
    h3->SetMarkerColor(kRed);   

    if(cor){
	h1->GetXaxis()->SetRangeUser(-3.5,-1.25);
	h2->GetXaxis()->SetRangeUser(-3.5,-1.25);
	h3->GetXaxis()->SetRangeUser(-3.5,-1.25);
    }else{
        h1->GetXaxis()->SetRangeUser(-4,-1);
        h2->GetXaxis()->SetRangeUser(-4,-1);
        h3->GetXaxis()->SetRangeUser(-4,-1);
    }
    h1->GetYaxis()->SetRangeUser(binning[0],binning[1]);
    h1_1 =(TH1F*) h1->ProjectionX();
    h1_1->SetName("h1_1");
    h1->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    h1_2 =(TH1F*) h1->ProjectionX();
    h1_2->SetName("h1_2");
    h1->GetYaxis()->SetRangeUser(binning[2],binning[3]);
    h1_3 =(TH1F*) h1->ProjectionX();
    h1_3->SetName("h1_3");
    h1->GetYaxis()->SetRangeUser(binning[3],binning[4]);
    h1_4 =(TH1F*) h1->ProjectionX();
    h1_4->SetName("h1_4");
    h1->GetYaxis()->SetRangeUser(binning[4],binning[5]);
    h1_5 =(TH1F*) h1->ProjectionX();
    h1_5->SetName("h1_5");
    h1->GetYaxis()->SetRangeUser(binning[5],binning[6]);
    h1_6 =(TH1F*) h1->ProjectionX();
    h1_6->SetName("h1_6");
    h1->GetYaxis()->SetRangeUser(binning[6],binning[7]);
    h1_7 =(TH1F*) h1->ProjectionX();
    h1_7->SetName("h1_7");
    h1->GetYaxis()->SetRangeUser(binning[7],binning[8]);
    h1_8 =(TH1F*) h1->ProjectionX();
    h1_8->SetName("h1_8");
    h1->GetYaxis()->SetRangeUser(binning[8],binning[9]);
    h1_9 =(TH1F*) h1->ProjectionX();
    h1_9->SetName("h1_9");
    h2->GetYaxis()->SetRangeUser(binning[0],binning[1]);
    h2_1 =(TH1F*) h2->ProjectionX();
    h2_1->SetName("h2_1");
    h2->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    h2_2 =(TH1F*) h2->ProjectionX();
    h2_2->SetName("h2_2");
    h2->GetYaxis()->SetRangeUser(binning[2],binning[3]);
    h2_3 =(TH1F*) h2->ProjectionX();
    h2_3->SetName("h2_3");
    h2->GetYaxis()->SetRangeUser(binning[3],binning[4]);
    h2_4 =(TH1F*) h2->ProjectionX();
    h2_4->SetName("h2_4");
    h2->GetYaxis()->SetRangeUser(binning[4],binning[5]);
    h2_5 =(TH1F*) h2->ProjectionX();
    h2_5->SetName("h2_5");
    h2->GetYaxis()->SetRangeUser(binning[5],binning[6]);
    h2_6 =(TH1F*) h2->ProjectionX();
    h2_6->SetName("h2_6");
    h2->GetYaxis()->SetRangeUser(binning[6],binning[7]);
    h2_7 =(TH1F*) h2->ProjectionX();
    h2_7->SetName("h2_7");
    h2->GetYaxis()->SetRangeUser(binning[7],binning[8]);
    h2_8 =(TH1F*) h2->ProjectionX();
    h2_8->SetName("h2_8");
    h2->GetYaxis()->SetRangeUser(binning[8],binning[9]);
    h2_9 =(TH1F*) h2->ProjectionX();
    h2_9->SetName("h2_9");
    h3->GetYaxis()->SetRangeUser(binning[0],binning[1]);
    h3_1 =(TH1F*) h3->ProjectionX();
    h3_1->SetName("h3_1");
    h3->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    h3_2 =(TH1F*) h3->ProjectionX();
    h3_2->SetName("h3_2");
    h3->GetYaxis()->SetRangeUser(binning[2],binning[3]);
    h3_3 =(TH1F*) h3->ProjectionX();
    h3_3->SetName("h3_3");
    h3->GetYaxis()->SetRangeUser(binning[3],binning[4]);
    h3_4 =(TH1F*) h3->ProjectionX();
    h3_4->SetName("h3_4");
    h3->GetYaxis()->SetRangeUser(binning[4],binning[5]);
    h3_5 =(TH1F*) h3->ProjectionX();
    h3_5->SetName("h3_5");
    h3->GetYaxis()->SetRangeUser(binning[5],binning[6]);
    h3_6 =(TH1F*) h3->ProjectionX();
    h3_6->SetName("h3_6");
    h3->GetYaxis()->SetRangeUser(binning[6],binning[7]);
    h3_7 =(TH1F*) h3->ProjectionX();
    h3_7->SetName("h3_7");
    h3->GetYaxis()->SetRangeUser(binning[7],binning[8]);
    h3_8 =(TH1F*) h3->ProjectionX();
    h3_8->SetName("h3_8");
    h3->GetYaxis()->SetRangeUser(binning[8],binning[9]);
    h3_9 =(TH1F*) h3->ProjectionX();
    h3_9->SetName("h3_9");
 
    if(cor){
	calcEff(h2_1,h3_1,h1_1);
	calcEff(h2_2,h3_2,h1_2);
	calcEff(h2_3,h3_3,h1_3);
	calcEff(h2_4,h3_4,h1_4);
	calcEff(h2_5,h3_5,h1_5);
	calcEff(h2_6,h3_6,h1_6);
	calcEff(h2_7,h3_7,h1_7);
	calcEff(h2_8,h3_8,h1_8);
	calcEff(h2_9,h3_9,h1_9);
        norm5(h1_1);
	norm5(h1_2);
	norm5(h1_3);
	norm5(h1_4);
	norm5(h1_5);
	norm5(h1_6);
	norm5(h1_7);
	norm5(h1_8);
	norm5(h1_9);
	norm5(h2_1);
	norm5(h2_2);
	norm5(h2_3);
	norm5(h2_4);
	norm5(h2_5);
	norm5(h2_6);
	norm5(h2_7);
	norm5(h2_8);
	norm5(h2_9);
	norm5(h3_1);
	norm5(h3_2);
	norm5(h3_3);
	norm5(h3_4);
	norm5(h3_5);
	norm5(h3_6);
	norm5(h3_7);
	norm5(h3_8);
	norm5(h3_9);
    }else{
	norm(h1_1);
	norm(h1_2);
	norm(h1_3);
	norm(h1_4);
	norm(h1_5);
	norm(h1_6);
	norm(h1_7);  
	norm(h1_8);
	norm(h1_9);
	norm(h2_1);
	norm(h2_2);
	norm(h2_3);
	norm(h2_4);
	norm(h2_5);
	norm(h2_6);
	norm(h2_7);  
	norm(h2_8);
	norm(h2_9);
	norm(h3_1);
	norm(h3_2);
	norm(h3_3);
	norm(h3_4);
	norm(h3_5);
	norm(h3_6);
	norm(h3_7);  
	norm(h3_8);
	norm(h3_9);
    }
	
    TLegend *leg = new TLegend(0.1,0.1,0.9,0.9);
    leg->AddEntry(h1,"Data","PEL");
    //leg->AddEntry(h2,"Single e","l");   
    leg->AddEntry(h3,"Embedding","PLE");
    TLatex lat;

    TCanvas *c1 = new TCanvas ("c1","",1800,800);
    c1->Divide(5,2);
    c1->cd(1);
    h1_1->Draw("PE");
    if(!cor)h2_1->Draw("pe same");
    if(cor)h3_1->Draw("pe same");
    lat.DrawLatex(-2.5.,h1_1->GetMaximum()*0.9,"#it{p}_{T}#in[0.6,1.0] GeV");
    c1->cd(2);
    h1_2->Draw("PE");
    if(!cor)h2_2->Draw("pe same");
    if(cor)h3_2->Draw("pe same");
    lat.DrawLatex(-2.5.,h1_1->GetMaximum()*0.9,"#it{p}_{T}#in[1.0,1.2] GeV");
    c1->cd(3);
    h1_3->Draw("PE");
    if(!cor)h2_3->Draw("pe same");
    if(cor)h3_3->Draw("pe same");
    lat.DrawLatex(-2.5.,h1_1->GetMaximum()*0.9,"#it{p}_{T}#in[1.2,1.5] GeV");
    c1->cd(4);
    h1_4->Draw("PE");
    if(!cor)h2_4->Draw("pe same");
    if(cor)h3_4->Draw("pe same");
    lat.DrawLatex(-2.5.,h1_1->GetMaximum()*0.9,"#it{p}_{T}#in[1.5,2.0] GeV");
    c1->cd(5);
    h1_5->Draw("PE");
    if(!cor)h2_5->Draw("pe same");
    if(cor)h3_5->Draw("pe same");
    lat.DrawLatex(-2.5.,h1_1->GetMaximum()*0.9,"#it{p}_{T}#in[2.0,2.5] GeV");
    c1->cd(6);
    h1_6->Draw("PE");
    if(!cor)h2_6->Draw("pe same");
    if(cor)h3_6->Draw("pe same");
    lat.DrawLatex(-2.5.,h1_1->GetMaximum()*0.9,"#it{p}_{T}#in[2.5,3.5] GeV");
    c1->cd(7);
    h1_7->Draw("PE");
    if(!cor)h2_7->Draw("pe same");  
    if(cor)h3_7->Draw("pe same");
    lat.DrawLatex(-2.5.,h1_1->GetMaximum()*0.9,"#it{p}_{T}#in[3.5,4.5] GeV");
    c1->cd(8);
    h1_8->Draw("PE");
    if(!cor)h2_8->Draw("pe same");
    if(cor)h3_8->Draw("pe same");
    lat.DrawLatex(-2.5.,h1_1->GetMaximum()*0.9,"#it{p}_{T}#in[4.5,5.5] GeV");
    c1->cd(9);
    h1_9->Draw("PE");
    if(!cor)h2_9->Draw("pe same"); 
    if(cor)h3_9->Draw("pe same");
    lat.DrawLatex(-2.5.,h1_1->GetMaximum()*0.9,"#it{p}_{T}#in[5.5,8.5] GeV");
    c1->cd(10);
    leg->Draw("same");
}
void norm5(TH1F *h){
    h->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    h->GetYaxis()->SetTitle("Arb. Units");
    h->GetYaxis()->SetRangeUser(0.0,0.5);
    //h->Rebin(10);
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
void norm(TH1F *h){
    h->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    h->GetYaxis()->SetTitle("Arb. Units");
    h->GetYaxis()->SetRangeUser(0.0,0.3);
    h->Rebin(20);
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
void calcEff(TH1F *h,TH1F *g,TH1F *d){
    h->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    h->GetYaxis()->SetTitle("Arb. Units");

    h->Rebin(18);
    g->Rebin(18);
    d->Rebin(18);

    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double err = h->GetBinError(i);
	double temp1 = g->GetBinContent(i);
	double err1 = g->GetBinError(i);
	if(temp1>0 && temp>0){
	    double eff = temp/temp1;
	    double eff_er = temp/temp1*sqrt(1/temp1);   
	    double temp2 = d->GetBinContent(i);
	    double err2 = d->GetBinError(i);
	    d->SetBinContent(i,temp2/eff);
	    if(temp2>0)d->SetBinError(i,temp2/eff*sqrt(eff_er*eff_er/eff/eff + err2*err2/temp2/temp2));
	}
	else{
	    d->SetBinContent(i,0);
	    d->SetBinError(i,0);
	}
    }
}
