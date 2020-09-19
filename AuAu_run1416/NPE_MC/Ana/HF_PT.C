int const numPtBins=8;
double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,8.5};   
void HF_PT(){
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    gStyle->SetPadLeftMargin(0.16);
    gStyle->SetOptLogz(1);
    TH1F *d0 = new TH1F("d0","d0",numPtBins,binning);
    TH1F *dp = new TH1F("dp","dp",numPtBins,binning); 
    TH1F *ds = new TH1F("ds","ds",numPtBins,binning);
    TH1F *lc = new TH1F("lc","lc",numPtBins,binning);  
    TH1F *b0 = new TH1F("b0","b0",numPtBins,binning);
    TH1F *bp = new TH1F("bp","bp",numPtBins,binning); 
    TH1F *bs = new TH1F("bs","bs",numPtBins,binning);
    TH1F *lb = new TH1F("lb","lb",numPtBins,binning);  

    TFile *f = new TFile("./root/HF_plots.root");
    pt2D_d0 =(TH2F*)f->Get("pt2D_d0");
    pt2D_dp =(TH2F*)f->Get("pt2D_dp");
    pt2D_ds =(TH2F*)f->Get("pt2D_ds");
    pt2D_lc =(TH2F*)f->Get("pt2D_lc"); 
    pt2D_b0 =(TH2F*)f->Get("pt2D_b0");
    pt2D_bp =(TH2F*)f->Get("pt2D_bp");
    pt2D_bs =(TH2F*)f->Get("pt2D_bs");
    pt2D_lb =(TH2F*)f->Get("pt2D_lb"); 

    getMeans(d0,pt2D_d0);
    getMeans(dp,pt2D_dp);
    getMeans(ds,pt2D_ds);
    getMeans(lc,pt2D_lc);
    getMeans(b0,pt2D_b0);
    getMeans(bp,pt2D_bp);
    getMeans(bs,pt2D_bs);
    getMeans(lb,pt2D_lb);
    TLatex lat;
    TCanvas *c1 = new TCanvas("c1","c1",2000,500);
    c1->Divide(4,1);

    c1->cd(1);
    pt2D_d0->Draw("colz");
    d0->DrawClone("PE same");
    lat.DrawLatex(6,2,"D^{0}#rightarrow#it{e}X");
    c1->cd(2);
    pt2D_dp->Draw("colz");
    dp->DrawClone("PE same");
    lat.DrawLatex(6,2,"D^{+}#rightarrow#it{e}X");
    c1->cd(3);
    pt2D_ds->Draw("colz");
    ds->DrawClone("PE same");
    lat.DrawLatex(6,2,"D_{s}#rightarrow#it{e}X");
    c1->cd(4);
    pt2D_lc->Draw("colz");
    lc->DrawClone("PE same");
    lat.DrawLatex(6,2,"#Lambda_{c}#rightarrow#it{e}X");

    TCanvas *c2 = new TCanvas("c2","c2",2000,500);
    c2->Divide(4,1);

    c2->cd(1);
    pt2D_b0->Draw("colz");
    b0->DrawClone("PE same");
    lat.DrawLatex(6,2,"B^{0}#rightarrow#it{e}X");
    c2->cd(2);
    pt2D_bp->Draw("colz");
    bp->DrawClone("PE same");
    lat.DrawLatex(6,2,"B^{+}#rightarrow#it{e}X");
    c2->cd(3);
    pt2D_bs->Draw("colz");
    bs->DrawClone("PE same");
    lat.DrawLatex(6,2,"B_{s}#rightarrow#it{e}X");
    c2->cd(4);
    pt2D_lb->Draw("colz");
    lb->DrawClone("PE same");
    lat.DrawLatex(6,2,"#Lambda_{b}#rightarrow#it{e}X");
  
    d0->SetMarkerColor(kRed);
    d0->SetLineColor(kRed);	
    dp->SetMarkerColor(kBlue);
    dp->SetLineColor(kBlue);
    ds->SetMarkerColor(kGreen-2);
    ds->SetLineColor(kGreen-2);
    lc->SetMarkerColor(kMagenta);
    lc->SetLineColor(kMagenta);

    b0->SetMarkerColor(kRed);
    b0->SetLineColor(kRed);	
    bp->SetMarkerColor(kBlue);
    bp->SetLineColor(kBlue);
    bs->SetMarkerColor(kGreen-2);
    bs->SetLineColor(kGreen-2);
    lb->SetMarkerColor(kMagenta);
    lb->SetLineColor(kMagenta);
    TLegend * leg = new TLegend(0.6,0.2,0.9,0.6);
    leg->AddEntry(d0,"D^{0}#rightarrow eX","PEL");
    leg->AddEntry(dp,"D^{+}#rightarrow eX","PEL");
    leg->AddEntry(ds,"D_{s}#rightarrow eX","PEL");
    leg->AddEntry(lc,"#Lambda_{c}#rightarrow eX","PEL");
    TLegend * leg1 = new TLegend(0.6,0.2,0.9,0.6);
    leg1->AddEntry(b0,"B^{0}#rightarrow eX","PEL");
    leg1->AddEntry(bp,"B^{+}#rightarrow eX","PEL");
    leg1->AddEntry(bs,"B_{s}#rightarrow eX","PEL");
    leg1->AddEntry(lb,"#Lambda_{b}#rightarrow eX","PEL");
   
    TCanvas *c3 = new TCanvas("c3","c3",1000,500);
    c3->Divide(2,1);
    c3->cd(1);
    d0->Draw();
    dp->Draw("same");
    ds->Draw("same");
    lc->Draw("same");
    leg->Draw("same");
    c3->cd(2);
    b0->Draw();
    bp->Draw("same");
    bs->Draw("same");
    lb->Draw("same");
    leg1->Draw("same");
    cout << "Charm averages" << endl;

    for(int i = 1 ;i<9;i++){
	cout << (d0->GetBinContent(i)+dp->GetBinContent(i))/2<< endl;
    }
    cout << "Bottom averages" << endl;

    for(int i = 1 ;i<9;i++){
	cout << (b0->GetBinContent(i)+bp->GetBinContent(i))/2<< endl;
    }
    //TFile f1("./root/HF_2D.root","RECREATE");
    //d0->Write();
    //dp->Write();
    //ds->Write();
    //lc->Write();
    //b0->Write();
    //bp->Write();
    //bs->Write();
    //lb->Write();

}
void getMeans(TH1F *h1,TH2F* h2){
    for(int i=1;i<h1->GetNbinsX()+1;i++){
	h2->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
	temp = (TH1F*)h2->ProjectionY();
	double mean = temp->GetMean();
	double rms = temp->GetRMS();
	h1->SetBinContent(i,mean);
	h1->SetBinError(i,rms*0.577);	
    }
    h2->GetXaxis()->SetRangeUser(0.6,10);
    h2->GetYaxis()->SetRangeUser(0,10);
    h2->GetXaxis()->SetTitle("Electron #it{p}_{T} [GeV]");
    h2->GetYaxis()->SetTitle("Parent #it{p}_{T} [GeV]");
    h1->SetMarkerColor(kGray+1);
    h1->SetLineColor(kGray+1);  
    h1->GetXaxis()->SetTitle("Electron #it{p}_{T} [GeV]");
    h1->GetYaxis()->SetTitle("Parent #it{p}_{T} [GeV]");
    h1->GetYaxis()->SetRangeUser(0,10);
}



void norm5(TH1F *h){
    h->GetXaxis()->SetTitle("Decay Radius [cm]");
    h->GetYaxis()->SetTitle("A. U.");
    h->GetYaxis()->SetRangeUser(0.00001,0.4);
    h->Rebin();
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
