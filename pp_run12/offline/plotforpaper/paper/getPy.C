void norm(TH1F *h,double n);

void getPy(){
  char name[100];
//  gROOT->ProcessLine(".x ~/myStyle.C");
  gStyle->SetPalette(51);

  TFile *f = new TFile("out.root","READ");
  int const nbin =7;
  double binning[nbin+1]={2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5};
  
  auto hHFB = (TH2F*) f->Get("hHFB");
  auto hHFC = (TH2F*) f->Get("hHFC");
  auto hHFB_PT = (TH1F*) f->Get("hHFB_PT");
  auto hHFC_PT = (TH1F*) f->Get("hHFC_PT");
  auto hHF_PT = (TH1F*) f->Get("hHF_PT");

  
  int bin1, bin2;
  
  TFile *file2 = TFile::Open("PYTHIA_dndphi_ppy06.root");
  TH1D *Pythia_De[4];
  TH1D *Pythia_Be[4];
  for(int i=0;i<4; i++)
  {
    char name1[100];
    sprintf(name1,"phy_pyhia_D_%d",i);
    Pythia_De[i] = (TH1D*)file2->Get(name1);

    char name2[100];
    sprintf(name2,"phy_pyhia_B_%d",i);
    Pythia_Be[i] = (TH1D*)file2->Get(name2);

    Pythia_De[i]->SetLineColor(kMagenta);
    Pythia_Be[i]->SetLineColor(kCyan);
  }
  
  auto outf = new TFile("PYTHIA_dndphi_ppy06_matt.root", "RECREATE");

  TH1F *hHFC_Corr[nbin];
  TH1F *hHFB_Corr[nbin];
  
//  auto c = new TCanvas();
//  c->Divide(2, 2);
  for(int i = 1; i< nbin+1; i++){
//    c->cd(i-3);
    bin1= hHF_PT->GetXaxis()->FindBin(binning[i-1]);
    bin2= hHF_PT->GetXaxis()->FindBin(binning[i]);
    
    hHFB->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    sprintf(name,"phy_pyhia_B_%i",i-1);
    hHFB_Corr[i-1] = (TH1F*)hHFB->ProjectionY();hHFB_Corr[i-1]->SetName(name);
    norm(hHFB_Corr[i-1],hHFB_PT->Integral(bin1,bin2));
    hHFB_Corr[i-1]->SetLineColor(kBlue);
    hHFB_Corr[i-1]->SetMarkerColor(kBlue);
    
    hHFC->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    sprintf(name,"phy_pyhia_D_%i",i-1);
    hHFC_Corr[i-1] = (TH1F*)hHFC->ProjectionY();hHFC_Corr[i-1]->SetName(name);
    norm(hHFC_Corr[i-1],hHFC_PT->Integral(bin1,bin2));
    hHFC_Corr[i-1]->SetLineColor(kRed);
    hHFC_Corr[i-1]->SetMarkerColor(kRed);
    
//    Pythia_Be[i-4]->GetYaxis()->SetRangeUser(0, Pythia_Be[i-4]->GetMaximum()*1.5);
//    Pythia_Be[i-4]->GetXaxis()->SetTitle("#Delta#phi");
//    Pythia_Be[i-4]->GetYaxis()->SetTitle("(1/N) dN/d#Delta#phi");

//    Pythia_Be[i-4]->Draw();
//    Pythia_De[i-4]->Draw("same");
    hHFC_Corr[i-1]->Rebin(4);
    hHFB_Corr[i-1]->Rebin(4);
//    hHFC_Corr[i-1]->Draw("same hist");
//    hHFB_Corr[i-1]->Draw("hist same");
  }
//  c->SaveAs("Matt_comp_py6.pdf");
  outf->cd();
  outf->Write();
  outf->Close();
}

void norm(TH1F *h,double n){
  //h->Rebin();
  for(int i = 1; i <h->GetNbinsX()+1;i++){
    double val = h->GetBinContent(i);
    h->SetBinContent(i,val/n);
    h->SetBinError(i,sqrt(val)/n);
  }
}
