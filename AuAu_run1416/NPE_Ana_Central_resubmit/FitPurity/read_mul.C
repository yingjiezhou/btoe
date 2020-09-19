{
  TFile f("/Volumes/YJMAC/Matt_production/NPE_Tuples_Central5.root");
  TFile f2("/Volumes/YJMAC/Matt_production/NPE_Tuples_TuneB10.root");//MB
  TH1I *hh = (TH1I *)f.Get("h1dEventRefMult");
  TH1I *hh2 = (TH1I *)f2.Get("h1dEventRefMult");
  gStyle->SetOptStat(0000);

  TH1F *h = new TH1F("h1RefMult1", "", 1000, 0, 1000);
  TH1F *h2 = new TH1F("h1RefMult2", "", 1000, 0, 1000);

  for(auto i=0; i<1000; i++){
    h->SetBinContent(i+1, hh->GetBinContent(i+1));
    h2->SetBinContent(i+1, hh2->GetBinContent(i+1));
  }

  h2->Scale(1./h2->Integral(290,900));
  h->Scale(1./h->Integral(290,900));
  h2->GetYaxis()->SetRangeUser(1e-5, 6e-2);
  h2->GetXaxis()->SetRangeUser(0, 800);
  h2->GetXaxis()->SetTitle("refMult");
  h2->GetYaxis()->SetTitle("");
  h2->SetLineColor(kBlue);
  h->SetLineColor(kRed);
  h2->SetLineWidth(3);
  h->SetLineWidth(3);
  
  TCanvas *canv2 = new TCanvas ("canv2","weights",1500,800);
  //canv2->SetLogy();
  TLegend *leg_V2 = new TLegend(0.7,0.7,0.9,0.9);
  //leg_V2->SetBorderSize(0);
  //leg_V2->SetHeader("Run14 Au+Au@200 GeV");
  leg_V2->AddEntry(h2,"MB","LP");
  leg_V2->AddEntry(h,"central5","LP");
  
  h2->Draw();
  h->Draw("same");
  leg_V2->Draw("same");
  canv2->SaveAs("refMul.pdf");
  /*
  TString paveLabel_system = "Run14 Au+Au@200 GeV";

  TPaveLabel *pl_system = new TPaveLabel(0.45, 0.68, 0.85, 0.88, paveLabel_system, "brNDC");
  pl_system->SetBorderSize(0);
  pl_system->SetShadowColor(0);
  pl_system->SetTextSize(0.2);
  pl_system->SetTextColor(kBlack);
  pl_system->SetFillStyle(0);
  pl_system->Draw("same");
*/

  
}
