
void TrigCompSys(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  auto f = new TFile("TriggereffforYingjie.root", "READ");
  auto he0 = (TH1F*)f->Get("hTriggereffforYingjieSysHT0");
  auto he2 = (TH1F*)f->Get("hTriggereffforYingjieSysHT2");

  auto fht1 = new TF1("fht1", "TMath::Erf(x - 2.41589)", 2, 20);
  auto fht2 = new TF1("fht2", "TMath::Exp(-16.0543+3.3662*x)", 0, 4.5);
  auto fht3 = new TF1("fht3", "TMath::Erf(0.651713*x-2.6212)", 4.5, 20);
  
//  auto fpht1 = new TF1("fht1", "TMath::Erf(x - 2.73552e+00)", 2, 20);
//  auto fpht2 = new TF1("fht2", "TMath::Exp(-1.15025e+01+2.20626e+00*x)", 0, 5);
//  auto fpht3 = new TF1("fht3", "TMath::Erf(x-4.44533e+00)", 5, 20);
  
  
  auto fpht1 = new TF1("fht1", "TMath::Erf(x - 2.52823e+00)-5.56216e-03", 2, 20);
  auto fpht2 = new TF1("fht2", "TMath::Exp(-8.13024e+00+1.53156e+00*x)-2.17967e-02", 0, 5.1);
  auto fpht3 = new TF1("fht3", "TMath::Erf(6.83595e-01*x-2.80986e+00)-8.49065e-03", 5, 20);
  
  cout<<fpht1->Eval(2.6)<<"  "<<fpht1->Eval(3)<<endl;

  fpht1->SetLineColor(kRed);
  fpht2->SetLineColor(kRed);
  fpht3->SetLineColor(kRed);
  
  
  fht1->SetLineColor(kBlue);
  fht2->SetLineColor(kBlue);
  fht3->SetLineColor(kBlue);
  
  he0->SetLineColor(kRed);
  he2->SetLineColor(kRed);
  he0->SetMarkerColor(kRed);
  he2->SetMarkerColor(kRed);
  
  
  TH1F* changeHist = he0;
  TAxis* ax = changeHist->GetXaxis();
  for(int chn = ax->GetFirst(); chn <= ax->GetLast(); chn++)
  {
    double current = changeHist->GetBinContent(chn);
    double error = changeHist->GetBinError(chn);
    changeHist->SetBinContent(chn, current+error);
    changeHist->SetBinError(chn, 1e-8);

  }
  changeHist->SetLineColor(kGreen);
  changeHist->SetMarkerColor(kGreen);
  
  TH1F* changeHist2 = he2;
  ax = changeHist2->GetXaxis();
  for(int chn = ax->GetFirst(); chn <= ax->GetLast(); chn++)
  {
    double current = changeHist2->GetBinContent(chn);
    double error = changeHist2->GetBinError(chn);
    changeHist2->SetBinContent(chn, current+error);
    changeHist2->SetBinError(chn, 1e-8);
  }
  changeHist2->SetLineColor(kGreen);
  changeHist2->SetMarkerColor(kGreen);
  

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
  fpht1->Draw("same");
  fpht2->Draw("same");
  fpht3->Draw("same");
  he0->Draw("same");
  he2->Draw("same");

  leg->Draw("same");
  c->SaveAs("trigg_eff_gpt_ppt_sys.pdf");
  
}

