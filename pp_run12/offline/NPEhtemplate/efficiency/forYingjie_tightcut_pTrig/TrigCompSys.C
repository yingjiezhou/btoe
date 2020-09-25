void TrigCompSys(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  auto f = new TFile("TriggereffforYingjie.root", "READ");
  auto he0 = (TH1F*)f->Get("hTriggereffforYingjieSysHT0");
  auto he2 = (TH1F*)f->Get("hTriggereffforYingjieSysHT2");

  auto fht1 = new TF1("fht1", "TMath::Erf(x - 2.41589)", 2, 20);
  auto fht2 = new TF1("fht2", "TMath::Exp(-16.0543+3.3662*x)", 0, 4.5);
  auto fht3 = new TF1("fht3", "TMath::Erf(0.651713*x-2.6212)", 4.5, 20);
  
//  auto fpht1 = new TF1("fht1", "TMath::Erf(x - 2.55666e+00)-6.00096e-03", 2, 20);
//  auto fpht2 = new TF1("fht2", "TMath::Exp(1.97128e+00*x-1.04456e+01)", 0, 5.04);
//  auto fpht3 = new TF1("fht3", "TMath::Erf(6.48257e-01*x - 2.70569e+00)-8.95634e-03", 5.0, 20);
  
//  auto fpht1 = new TF1("fht1", "TMath::Erf(9.85567e-01*x - 2.51355e+00)-5.73728e-03", 2, 20);
//  auto fpht2 = new TF1("fht2", "TMath::Exp(-16.0543+3.3662*x)", 0, 4.5);
//  auto fpht3 = new TF1("fht3", "TMath::Erf(6.48257e-01*x - 2.70569e+00)-8.95563e-03", 4.5, 20);
  
  auto fpht1 = new TF1("fpht1", "TMath::Erf(2.96925e-02*x*x*x-2.69714e-01)", 2, 20);
  auto fpht2 = new TF1("fpht2", "TMath::Exp(-1.63854e+01+3.38602*x)-6.24438e-06", 0, 4.5);
  auto fpht3 = new TF1("fpht3", "TMath::Erf(5.83780e-01*x-2.38107)", 4.5, 20);
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

  he0->SetMarkerSize(0.2);
  he2->SetMarkerSize(0.2);

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
  c->SaveAs("trigg_eff_gpt_ppt_Sys.pdf");
  
}

