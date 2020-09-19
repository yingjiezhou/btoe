void combine(){
  gStyle->SetOptStat(0);
  
  auto fyj = new TFile("pythia_npe_tree_Jan14_v2_yj.root", "READ");
  auto hsum = new TH1D("hsum", "", 16, 0, 16);
  
  const int numPtBins = 14;
  TH1D *hsec[numPtBins];
  int tmp = 0;
  for(int i=0; i< numPtBins; i++){
    hsec[i] = (TH1D*)fyj->Get(Form("hept_%i",i));
    cout<< "in pt bin, total e is : " << hsec[i]->Integral()<<endl;
    hsum->SetBinContent(i+1, hsec[i]->Integral());
    tmp += hsec[i]->Integral();
  }
  hsum->GetYaxis()->SetTitle("number of electrons");
  hsum->GetXaxis()->SetTitle("p_{T} bin");

  hsum->SetBinContent(15, tmp);
  hsum->Draw("text00 H");
  
  
}
