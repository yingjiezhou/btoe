void plotDirectJpsi_comp(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  double xzebo[] = {1.013, 1.924, 2.685, 3.181, 3.982, 4.631, 5.278, 6.194, 6.993};
  double yzebo[] = {2.628, 1.138, 0.473, 0.243, 0.072, 0.027, 0.013, 0.003, 0.001};
  
  for(auto i = 0; i<10; i++){
    yzebo[i] *= 1e-6;
  }
  TGraph* gr = new TGraph(9,xzebo, yzebo);
  
  
  TFile* file = new TFile("JpsidNdydpTSpectrumpp.root","READ");
  auto GJpsi = (TGraphErrors*) file->Get("Jpsi");
  GJpsi->SetMarkerColor(kBlue);
  
  //  double xs[] = {1.60, 2.36, 2.82, 3.33, 3.65, 4.62, 5.07, 5.87, 6.64, 7.12};
  //  double ys[] = {0.0000122, 0.00000313, 0.00000159, 6.81e-7, 4.33e-7, 8.89e-8, 4.03e-8, 1.46e-8, 5.89e-9, 3.16e-9};
  //  auto gs = new TGraph(10, xs, ys); // shenghui, jpsi decayed e cross section
  
//  double xs[8] = {2.55, 3.14, 4.01, 6.06, 7.53, 8.94, 10.2, 11.9};
//  double ys[8] = {5.13e-7, 2.07e-7, 6.35e-8, 4.15e-9, 7.39e-10, 1.58e-10, 4.83e-11, 1.24e-11};
//  double es[8] = {0};
//  TGraph* gs = new TGraph(8, xs, ys); // from shenghui, jpsi cross section
  
  auto fa = new TFile("QAJpsiPureSec.root", "READ"); // read jpsi tree, code from web, with MB tune(old tune), get all jpsi
  auto ha = (TH1D*) fa->Get("hjeptN");
  ha->Rebin(25);
  for(int i = 0; i< ha->GetNbinsX(); i++){
    double pt = ha->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* ha->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp/6221. * 0.059; // number of root file
    ha->SetBinContent(i+1, ha->GetBinContent(i+1) * tmpp);
    ha->SetBinError(i+1, ha->GetBinError(i+1)*tmpp);
  }
  
  ha->SetMarkerColor(kYellow+2);
  ha->SetLineColor(kYellow+2);
  //=====================

  auto f = new TFile("directJpsi_MB.root", "READ");
  auto h1 = (TH1D*) f->Get("hjeptN"); // jpsi pt spectrum
  h1->Rebin(10);
  
  for(int i = 0; i< h1->GetNbinsX(); i++){
    double pt = h1->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* h1->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp/5996. * 0.059; // number of root file
    h1->SetBinContent(i+1, h1->GetBinContent(i+1) * tmpp);
    h1->SetBinError(i+1, h1->GetBinError(i+1)*tmpp);
  }
  
  //  h1->Scale(1./10.);
  //
  h1->SetMarkerColor(kGreen+2);
  h1->SetLineColor(kGreen+2);
  //=====================

  auto fbc = new TFile("directJpsi_HQbc.root", "READ");
  auto hbc = (TH1D*) fbc->Get("hjeptN"); // jpsi pt spectrum
  hbc->Rebin(10);
  for(int i = 0; i< hbc->GetNbinsX(); i++){
    double pt = hbc->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* hbc->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp/2554.* 0.059; // number of root file
    hbc->SetBinContent(i+1, hbc->GetBinContent(i+1) * tmpp);
    hbc->SetBinError(i+1, hbc->GetBinError(i+1)*tmpp);
  }
  
  hbc->SetMarkerColor(kGreen+2);
  hbc->SetLineColor(kGreen+2);
  hbc->SetMarkerStyle(24);
  //=====================
  
  
  auto leg = new TLegend(0.15,0.2,0.55,0.46);
  leg->AddEntry(gr,"PYTHIA, Direct J/#psi#rightarrow#it{e^{+}e^{-}}(from web, K=0.4356)","l");
//  leg->AddEntry(gs,"Data, J/#psi#rightarrow#it{e^{+}e^{-}}(from shenghui)","l");
  leg->AddEntry(GJpsi,"Data, J/#psi#rightarrow#it{e^{+}e^{-}}(from shenghui)","p");
  
  leg->AddEntry(hbc,"PYTHIA,STAR HF tune v1.0 HQbc, direct J/#psi#rightarrow#it{e^{+}e^{-}}, ","p"); // use tune from web, direct jpsi

  leg->AddEntry(h1,"PYTHIA,STAR HF tune v1.1 MB, direct J/#psi#rightarrow#it{e^{+}e^{-}}, MB","p"); // use my old tune, to get direct jpsi
  leg->AddEntry(ha,"PYTHIA,STAR HF tune v1.1 MB, all J/#psi#rightarrow#it{e^{+}e^{-}}, MB","p"); // use my old tune, I didn't know we need to use direct, so I get all jpsi
  leg->SetFillStyle (0);
  leg->SetFillColor (0);
  leg->SetBorderSize(0);
  
  
  
  
  auto c = new TCanvas("c", "c");
  c->SetLogy();
//  c->SetGridx();
//  c->SetGridy();
  
  gr->GetYaxis()->SetRangeUser(1e-15, 1e-3);
  
  //  gr->GetXaxis()->SetRangeUser(2.5, 8);
  gr->GetXaxis()->SetRangeUser(0, 16);
  
  gr->SetLineColor(2);
  gr->GetXaxis()->SetTitle("J/#psi p_{T} (GeV/c)");
  gr->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
  gr->GetXaxis()->SetNdivisions(515, "X");
  gr->Draw("al");
//  gs->Draw("same l");
  GJpsi->Draw("pe");
  hbc->Draw("same p");
  h1->Draw("same p");
  ha->Draw("same p");
  leg->Draw("same");
  
  TLatex tx;
  tx.SetTextSize(0.04);
  tx.SetTextFont(42);
  tx.DrawLatex(4.,1e-4,"J/#Psi#rightarrowe^{+}e^{-}, |y|(J/#Psi)<0.5");
  tx.DrawLatex(4.,1e-5,"J/#Psi#rightarrowe^{+}e^{-}, |#eta|(e)<1");
  
  c->SaveAs("plotDirectJpsi_comp.pdf");
  return;
}
