{
  TFile f("/Volumes/YJMAC/Matt_production/NPE_Tuples_Central5.root");
  TH1D *h = (TH1D *)f.Get("h1dEventRefMult");
  gStyle->SetOptStat(0000);
  //h->Rebin(2);
  h->Scale(1./500);
  h->GetXaxis()->SetRangeUser(0, 50);
  h->GetXaxis()->SetTitle("N_{h}");
  h->GetYaxis()->SetTitle("dN/N_{h}");
  h->SetMarkerSize(1.);
  h->SetMarkerStyle(20);
  TLegend *leg_V2 = new TLegend(0.48,0.58,0.88,0.68);
  leg_V2->SetBorderSize(0);
  leg_V2->SetHeader("0.2< p^{h}_{T}<2.0 GeV/c,|#eta_{h}|<1.0");
  leg_V2->AddEntry(h,"c,b->e,p^{e}_{T}>0 GeV/c, <N_{h}>=9.16","LP");
  TString paveLabel_system = "PYTHIA8 MB p+p@200 GeV, STAR HF tuning";

  TPaveLabel *pl_system = new TPaveLabel(0.45, 0.68, 0.85, 0.88, paveLabel_system, "brNDC");
  pl_system->SetBorderSize(0);
  pl_system->SetShadowColor(0);
  pl_system->SetTextSize(0.2);
  pl_system->SetTextColor(kBlack);
  pl_system->SetFillStyle(0);

  h->Draw("HIST");
  pl_system->Draw("same");
  leg_V2->Draw("same");
}
