void plotDirectJpsi_HQ_comp_web(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  
  double xzebo[] = {1.013, 1.924, 2.685, 3.181, 3.982, 4.631, 5.278, 6.194, 6.993};
  double yzebo[] = {2.628, 1.138, 0.473, 0.243, 0.072, 0.027, 0.013, 0.003, 0.001};
  
//  for(auto i = 0; i<10; i++){
//    yzebo[i] *= 1e-6;
//  }
  TGraph* gr = new TGraph(9,xzebo, yzebo);

//  double xs[8] = {2.55, 3.14, 4.01, 6.06, 7.53, 8.94, 10.2, 11.9};
//  double ys[8] = {5.13e-7, 2.07e-7, 6.35e-8, 4.15e-9, 7.39e-10, 1.58e-10, 4.83e-11, 1.24e-11};
//  double es[8] = {0};
//  TGraph* gs = new TGraph(8, xs, ys); // from shenghui, jpsi->e cross section


  auto f = new TFile("rootfile/directJpsi.root", "READ");
  auto h1 = (TH1D*) f->Get("hjeptN"); // jpsi pt spectrum
  h1->Rebin(10);

  for(int i = 0; i< h1->GetNbinsX(); i++){
    double pt = h1->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* h1->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp/5996. * 0.059*1e6; // number of root file
    h1->SetBinContent(i+1, h1->GetBinContent(i+1) * tmpp);
    h1->SetBinError(i+1, h1->GetBinError(i+1)*tmpp);

  }
  
//  h1->Scale(1./10.);
//
  h1->SetMarkerColor(kGreen+2);
  h1->SetLineColor(kGreen+2);
  //=====================
  
 
  auto leg = new TLegend(0.45,0.75,0.9,0.9);
  leg->AddEntry(gr,"J/#psi#rightarrow#it{e^{+}e^{-}}(from zebo, with K = 0.4356)","l");
//  leg->AddEntry(gs,"J/#psi#rightrrow#it{e^{+}e^{-}}(from shenghui*Br)","l");
  leg->AddEntry(h1,"direct J/#psi#rightarrow#it{e^{+}e^{-}}(from STAR HF tune v1.1 *10)","p");

  leg->SetFillStyle (0);
  leg->SetFillColor (0);
  leg->SetBorderSize(0);
  
  auto c = new TCanvas("c", "c");
  c->SetLogy();
  c->SetGridx();
  c->SetGridy();
  
//  gr->GetYaxis()->SetRangeUser(1e-15, 1e-3);
  gr->GetYaxis()->SetRangeUser(5e-7, 12);

//  gr->GetXaxis()->SetRangeUser(2.5, 8);
  gr->GetXaxis()->SetRangeUser(0, 16);

  gr->SetLineColor(2);
  gr->GetXaxis()->SetTitle("p_{T}(J/#psi)");
  gr->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(nb/GeV^{2})");
  gr->GetXaxis()->SetNdivisions(515, "X");
  gr->Draw("al");
//  gs->Draw("same l");
  h1->Draw("same p");
  leg->Draw("same");
  c->SaveAs("plotDirectJpsi_HQ_comp_web.pdf");
  return;
}
