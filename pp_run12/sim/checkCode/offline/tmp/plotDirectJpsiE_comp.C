void plotDirectJpsiE_comp(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  
  auto f = new TFile("MBSet_hist.root", "READ");
  auto h1 = (TH1D*) f->Get("hjeptN"); // jpsi pt spectrum
//  h1->Rebin(10);
  
  for(int i = 0; i< h1->GetNbinsX(); i++){
    double pt = h1->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* h1->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp * 0.059 ; // number of root file
    h1->SetBinContent(i+1, h1->GetBinContent(i+1) * tmpp);
    h1->SetBinError(i+1, h1->GetBinError(i+1)*tmpp);
  }
  
  //  h1->Scale(1./10.);
  //
  h1->SetMarkerColor(kGreen+2);
  h1->SetLineColor(kGreen+2);
  
  //=====================
  auto fbc = new TFile("HQbcSet_hist.root", "READ");
  auto hbc = (TH1D*) fbc->Get("hjeptN"); // jpsi pt spectrum
//  hbc->Rebin(10);
  
  for(int i = 0; i< hbc->GetNbinsX(); i++){
    double pt = hbc->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* hbc->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp * 0.059 ; // number of root file
    hbc->SetBinContent(i+1, hbc->GetBinContent(i+1) * tmpp);
    hbc->SetBinError(i+1, hbc->GetBinError(i+1)*tmpp);
  }
  
  hbc->SetMarkerColor(kGreen+2);
  hbc->SetLineColor(kGreen+2);
  hbc->SetMarkerStyle(24);
  //=====================
  
  
  auto leg = new TLegend(0.15,0.2,0.55,0.46);
//  leg->AddEntry(GJpsi,"Data, J/#psi#rightarrow#it{e^{+}e^{-}}(from shenghui)","p");
  leg->AddEntry(hbc,"PYTHIA,STAR HF tune v1.0 HQbc, direct J/#psi#rightarrow#it{e^{+}e^{-}}","p");
  leg->AddEntry(h1,"PYTHIA,STAR HF tune v1.1 MB, direct J/#psi#rightarrow#it{e^{+}e^{-}}","p");
//  leg->AddEntry(ha,"PYTHIA,STAR HF tune v1.1 MB, all J/#psi#rightarrow#it{e^{+}e^{-}}","p");
  
  leg->SetFillStyle (0);
  leg->SetFillColor (0);
  leg->SetBorderSize(0);
  
  auto c = new TCanvas("c", "c");
//  c->SetLogy();
//  c->SetGridx();
//  c->SetGridy();
  
//  h1->GetYaxis()->SetRangeUser(1e-15, 1e-3);
  h1->GetXaxis()->SetRangeUser(0, 16);
  
  h1->GetXaxis()->SetTitle("J/#psi decayed e p_{T} (GeV/c)");
  h1->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
  h1->GetXaxis()->SetNdivisions(515, "X");
  h1->Draw("pe");
//  h1->Draw("same p");
  hbc->Draw("same p");
//  ha->Draw("same p");
  leg->Draw("same");
//  c->SaveAs("plotDirectJpsiE_comp.pdf");
  return;
}
