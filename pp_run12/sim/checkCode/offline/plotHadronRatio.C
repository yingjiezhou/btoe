void plotHadronRatio(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  auto f = new TFile("rootfile/readTreeHadron.root", "READ");
  auto hLc = (TH1D*) f->Get("hLc");
  auto hD0 = (TH1D*) f->Get("hD0");
  auto hLb = (TH1D*) f->Get("hLb");
  auto hB0 = (TH1D*) f->Get("hB0");
  auto h2Lb = (TH1D*) f->Get("h2Lb");
  auto h2B0 = (TH1D*) f->Get("h2B0");

  hLc->Divide(hD0);
//  hLc->GetXaxis()->SetRangeUser(2.5, 9);
  hLc->Draw();
//  c->SaveAs("plotPrompJpsiVsNPE_py8frompy6.pdf");
  return;
}
