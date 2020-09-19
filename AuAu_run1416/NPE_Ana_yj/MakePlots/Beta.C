void Beta(){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
gStyle->SetPalette(56);

    TGaxis::SetMaxDigits(3); 
    char dFile[500];
    sprintf(dFile,"../production/NPE_Tuples2.root");
    TFile *f_D = new TFile(dFile);
    ch1 = (TChain*)f_D->Get("Signal");
    TH2F *h2d = new TH2F("h2d","h2d",1000,-0.05,0.05,200,-13,13);
    TH2F *h2d1 = new TH2F("h2d1","h2d1",1000,-0.05,0.05,200,-13,13);
    ch1->Project("h2d","sig_nsige:(1/sig_beta  - sig_p / sqrt(sig_p*sig_p+0.00051099907*0.00051099907))/ (1/sig_beta)","sig_mva>0.1 && sig_beta>0")  ;
    ch1->Project("h2d1","sig_nsige:(1/sig_beta  - sig_p / sqrt(sig_p*sig_p+0.00051099907*0.00051099907))/ (1/sig_beta)","sig_mva>0.15 && sig_beta>0")  ;
    TCanvas *c1 = new TCanvas ("c1","c1",1000,500);
    c1->Divide(2,1);
    c1->cd(1);
    h2d->Draw("COLZ");
    c1->cd(2);
    h2d1->Draw("COLZ");

    h1= (TH1F*)h2d->ProjectionX();
    h2= (TH1F*)h2d->ProjectionY();
    h11= (TH1F*)h2d1->ProjectionX();
    h22= (TH1F*)h2d1->ProjectionY();
    h11->SetLineColor(kRed);
    h22->SetLineColor(kRed);
    TCanvas *c2 = new TCanvas ("c2","c2",1000,500);
    c2->Divide(2,1);
    c2->cd(1);
    h2->Draw();
    h22->Draw("same");
    c2->cd(2);
    h1->Draw();
    h11->Draw("same");
}//End

void norm(TH1F *h){
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1);
	h->SetBinError(i,err/norm1);
    }
}
