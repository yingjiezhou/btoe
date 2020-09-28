void plotPrompJpsiVsNPE_py8frompy6(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  auto f = new TFile("rootfile/promptJPsiVsNPE.root", "READ");
  auto h1 = (TH1D*) f->Get("hbept");
  auto h2 = (TH1D*) f->Get("hcept");
  auto h3 = (TH1D*) f->Get("hept"); //b+c
  auto htmp = (TH1D*) f->Get("hbcept");
  auto hpjpsi =(TH1D*) f->Get("hpjpsi");
  
  hpjpsi->Rebin(10);
  h3->Rebin(10);
  hpjpsi->Divide(h3);
  hpjpsi->Scale(1./3.);
  hpjpsi->GetXaxis()->SetRangeUser(2.5, 9);
  hpjpsi->Draw();
//  c->SaveAs("plotPrompJpsiVsNPE_py8frompy6.pdf");
  return;
}
