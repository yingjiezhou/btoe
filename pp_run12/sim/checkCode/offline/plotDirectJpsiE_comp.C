void plotDirectJpsiE_comp(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  double xzebo[] = {1.013, 1.924, 2.685, 3.181, 3.982, 4.631, 5.278, 6.194, 6.993};
  double yzebo[] = {2.628, 1.138, 0.473, 0.243, 0.072, 0.027, 0.013, 0.003, 0.001};
  
  for(auto i = 0; i<10; i++){
    yzebo[i] *= 1e-6;
  }
  TGraph* gr = new TGraph(9,xzebo, yzebo);
  
  
  TFile* file = new TFile("rootfile/rootfile_NPESec_fromData/BackgroundSpectrum.root","READ");
  auto GJpsi = (TH1F*) file->Get("JpsiElectron");
  GJpsi->SetMarkerColor(kBlue);
  GJpsi->SetLineColor(kBlue);
  
  auto fa = new TFile("rootfile/QAJpsiPureSec.root", "READ"); // read jpsi tree, code from web, with MB tune(old tune), get all jpsi
  auto ha = (TH1D*) fa->Get("heptN");
  ha->Rebin(25);
  for(int i = 0; i< ha->GetNbinsX(); i++){
    double pt = ha->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* ha->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp/6221. * 0.059 *2; // number of root file
    ha->SetBinContent(i+1, ha->GetBinContent(i+1) * tmpp);
    ha->SetBinError(i+1, ha->GetBinError(i+1)*tmpp);
  }
  
  ha->SetMarkerColor(kYellow+2);
  ha->SetLineColor(kYellow+2);
  
  auto f = new TFile("rootfile/directJpsi_MB.root", "READ");
  auto h1 = (TH1D*) f->Get("heptN"); // jpsi pt spectrum
  h1->Rebin(10);
  
  for(int i = 0; i< h1->GetNbinsX(); i++){
    double pt = h1->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* h1->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp/5996. * 0.059 *2; // number of root file
    h1->SetBinContent(i+1, h1->GetBinContent(i+1) * tmpp);
    h1->SetBinError(i+1, h1->GetBinError(i+1)*tmpp);
  }
  
  //  h1->Scale(1./10.);
  //
  h1->SetMarkerColor(kGreen+2);
  h1->SetLineColor(kGreen+2);
  
  //=====================
  auto fbc = new TFile("rootfile/directJpsi_HQbc.root", "READ");
  auto hbc = (TH1D*) fbc->Get("heptN"); // jpsi pt spectrum
  hbc->Rebin(10);
  
  for(int i = 0; i< hbc->GetNbinsX(); i++){
    double pt = hbc->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* hbc->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp/2554. * 0.059 *2; // number of root file
    hbc->SetBinContent(i+1, hbc->GetBinContent(i+1) * tmpp);
    hbc->SetBinError(i+1, hbc->GetBinError(i+1)*tmpp);
  }
  
  //  h1->Scale(1./10.);
  //
  hbc->SetMarkerColor(kGreen+2);
  hbc->SetLineColor(kGreen+2);
  hbc->SetMarkerStyle(24);
  //=====================
  
  
  auto leg = new TLegend(0.15,0.2,0.55,0.46);
  leg->AddEntry(GJpsi,"Data, J/#psi#rightarrow#it{e^{+}e^{-}}(from shenghui)","p");
  leg->AddEntry(hbc,"PYTHIA,STAR HF tune v1.0 HQbc, direct J/#psi#rightarrow#it{e^{+}e^{-}}","p");
  leg->AddEntry(h1,"PYTHIA,STAR HF tune v1.1 MB, direct J/#psi#rightarrow#it{e^{+}e^{-}}","p");
  leg->AddEntry(ha,"PYTHIA,STAR HF tune v1.1 MB, all J/#psi#rightarrow#it{e^{+}e^{-}}","p");
  
  leg->SetFillStyle (0);
  leg->SetFillColor (0);
  leg->SetBorderSize(0);
  
  auto c = new TCanvas("c", "c");
  c->SetLogy();
  c->SetGridx();
  c->SetGridy();
  
  GJpsi->GetYaxis()->SetRangeUser(1e-15, 1e-3);
  GJpsi->GetXaxis()->SetRangeUser(0, 16);
  
  GJpsi->GetXaxis()->SetTitle("J/#psi decayed e p_{T} (GeV/c)");
  GJpsi->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
  GJpsi->GetXaxis()->SetNdivisions(515, "X");
  GJpsi->Draw("pe");
  h1->Draw("same p");
  hbc->Draw("same p");
  ha->Draw("same p");
  leg->Draw("same");
  c->SaveAs("plotDirectJpsiE_comp.pdf");
  return;
}
