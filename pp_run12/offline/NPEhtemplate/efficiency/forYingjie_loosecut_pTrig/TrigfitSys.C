
void TrigfitSys(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  auto f = new TFile("TriggereffforYingjie.root", "READ");
  auto he0 = (TH1F*)f->Get("hTriggereffforYingjieSysHT0");
  auto he2 = (TH1F*)f->Get("hTriggereffforYingjieSysHT2");

//  auto fht1 = new TF1("fht1", "TMath::Erf(x - 2.41589)", 2, 20);
//  auto fht2 = new TF1("fht2", "TMath::Exp(-16.0543+3.3662*x)", 0, 4.5);
//  auto fht3 = new TF1("fht3", "TMath::Erf(0.651713*x-2.6212)", 4.5, 20);
  
//  
//  auto fht1 = new TF1("fht1", "TMath::Erf(x - [0])", 2, 20);
//  auto fht2 = new TF1("fht2", "TMath::Exp([0]+[1]*x)", 0, 4.5);
//  auto fht3 = new TF1("fht3", "TMath::Erf([0]*x-[1])", 4.5, 20);
  
  auto fht1 = new TF1("fht1", "TMath::Erf(x - [0])-[1]", 2, 20);
  auto fht2 = new TF1("fht2", "TMath::Exp([0]+[1]*x)-[2]", 2.5, 5.1);
  auto fht3 = new TF1("fht3", "TMath::Erf([0]*x-[1])-[2]", 5, 20);
  
//  auto fht1 = new TF1("fht1", "TMath::Erf([0]*x - [1])-[2]", 2, 20);
//  auto fht2 = new TF1("fht2", "TMath::Exp([0]*x-[1])", 0, 5.04);
//  auto fht3 = new TF1("fht3", "TMath::Erf([0]*x - [1])-[2]", 5., 20);
//  
  
  fht1->SetLineColor(kBlue);
  fht2->SetLineColor(kBlue);
  fht3->SetLineColor(kBlue);
  
  he0->SetLineColor(kRed);
  he2->SetLineColor(kRed);
  he0->SetMarkerColor(kRed);
  he2->SetMarkerColor(kRed);
  
  fht1->SetParameter(0, 2.41589);
  fht2->SetParameters(-16.0543, 3.3662);
  fht3->SetParameters(0.651713, 2.6212);
  
//  fht1->SetParameters(8.82630e-01, 2.20735e+00, 1.62601e-02);
//  fht2->SetParameters(2.62796e+00, 1.29190e+01);
//  fht3->SetParameters(5.85750e-01, 2.35000e+00, 5.88702e-02);

  TH1F* changeHist = he0;
  TAxis* ax = changeHist->GetXaxis();
  for(int chn = ax->GetFirst(); chn <= ax->GetLast(); chn++)
  {
    double current = changeHist->GetBinContent(chn);
    double error = changeHist->GetBinError(chn);
    changeHist->SetBinContent(chn, current+error);
    changeHist->SetBinError(chn, 1e-8);

  }
  changeHist->SetLineColor(kRed);
  changeHist->SetMarkerColor(kRed);
  
  TH1F* changeHist2 = he2;
  ax = changeHist2->GetXaxis();
  for(int chn = ax->GetFirst(); chn <= ax->GetLast(); chn++)
  {
    double current = changeHist2->GetBinContent(chn);
    double error = changeHist2->GetBinError(chn);
    changeHist2->SetBinContent(chn, current+error);
    changeHist2->SetBinError(chn, 1e-8);
  }
  changeHist2->SetLineColor(kRed);
  changeHist2->SetMarkerColor(kRed);
  
  he0->Fit(fht1);
  he2->Fit(fht2, "R");
  he2->Fit(fht3, "R+");
  
  
  fht1->GetYaxis()->SetRangeUser(0, 1.4);
  auto leg = new TLegend(0.6,0.4,0.85,0.6);
  leg->SetNColumns(2);
  leg->AddEntry(fht1,"HT0, gpt","l");
  leg->AddEntry(fht2,"HT2, gpt","l");
  leg->AddEntry(he0,"HT0, ppt","lp");
  leg->AddEntry(he2,"HT2, ppt","lp");

  
  leg->SetFillStyle ( 0);
  leg->SetFillColor ( 0);
  leg->SetBorderSize( 0);
  fht1->SetTitle("");
  fht1->GetYaxis()->SetTitle("Trigger efficiency");
  fht1->GetXaxis()->SetTitle("p_{T} GeV/c");

  fht1->GetXaxis()->SetRangeUser(2, 20);
  auto c = new TCanvas("c");
  c->cd();
  fht1->Draw();
  fht2->Draw("same");
  fht3->Draw("same");
  he0->Draw("same");
  he2->Draw("same");

  leg->Draw("same");
  c->SaveAs("trigg_eff_fitSys.pdf");
  
}

