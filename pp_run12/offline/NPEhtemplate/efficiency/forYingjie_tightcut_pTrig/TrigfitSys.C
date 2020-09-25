
void TrigfitSys(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  auto f = new TFile("TriggereffforYingjie.root", "READ");
  auto he0 = (TH1F*)f->Get("hTriggereffforYingjieSysHT0");
  auto he2 = (TH1F*)f->Get("hTriggereffforYingjieSysHT2");
  
  he0->Rebin(2);
  he2->Rebin(2);
  he0->Scale(1./2);
  he2->Scale(1./2);
  
  
  //    auto fht1 = new TF1("fht1", "TMath::Erf(x - 2.41589)", 2, 20);
  //  auto fht2 = new TF1("fht2", "TMath::Exp(-16.0543+3.3662*x)", 0, 4.5);
  //  auto fht3 = new TF1("fht3", "TMath::Erf(0.651713*x-2.6212)", 4.5, 20);
  
  //  auto fht1 = new TF1("fht1", "TMath::Erf(x - [0])-[1]", 2., 20);
  //  auto fht2 = new TF1("fht2", "TMath::Exp([0]+[1]*x)-[2]", 2.5, 5.1);
  //  auto fht3 = new TF1("fht3", "TMath::Erf([0]*x-[1])-[2]", 5, 20);
  
  auto fht1 = new TF1("fht1", "TMath::Erf([0]*x*x*x-[1])", 2., 20);
  
  //  auto fht1 = new TF1("fht1", "TMath::Erf([0]*x*x-[1])", 2., 20);
  auto fht2 = new TF1("fht2", "TMath::Exp([0]+[1]*x)-[2]", 0, 4.5);
  auto fht3 = new TF1("fht3", "TMath::Erf([0]*x-[1])", 4.5, 20);
  
  //  auto fht1 = new TF1("fht1", "TMath::Erf(x - [0])-[1]", 2, 20);
  //  auto fht2 = new TF1("fht2", "TMath::Exp([0]+[1]*x)-[2]", 2.5, 5.1);
  //  auto fht3 = new TF1("fht3", "TMath::Erf([0]*x-[1])-[2]", 5, 20);
  fht1->SetLineColor(kBlue);
  fht2->SetLineColor(kBlue);
  fht3->SetLineColor(kBlue);
  
  he0->SetLineColor(kRed);
  he2->SetLineColor(kRed);
  he0->SetMarkerColor(kRed);
  he2->SetMarkerColor(kRed);
  
  fht1->SetParameter(0, 6.30939e-01);
  
  //  fht1->SetParameters(1.29830e-01, 5.71108e-01);
  fht2->SetParameters(-1.69902e+01, 3.58296e+00, 4.56344e-06);
  fht3->SetParameters(6.30939e-01, 2.54356e+00);
  
  he0->Fit(fht1, "R");
  he2->Fit(fht2, "R");
  he2->Fit(fht3, "R");
  
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
  TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
  TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
  pad1->SetBottomMargin(0.02);
  pad1->SetTopMargin(0.08);
  pad2->SetTopMargin(0.015);
  pad2->SetBottomMargin(0.5);
  pad2->SetBorderMode(0);
  pad1->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  fht1->Draw();
  fht2->Draw("same");
  fht3->Draw("same");
  he0->Draw("same");
  he2->Draw("same");
  leg->Draw("same");
  pad2->cd();
  auto hr0 = (TH1F*)he0->Clone("HT0Ratio");
  auto hr2 = (TH1F*)he2->Clone("HT0Ratio");
  
  for(auto i=0; i<he2->GetXaxis()->GetLast(); i++ ){
    hr0->SetBinContent(i+1, 0);
    hr2->SetBinContent(i+1, 0);
  }
  for(auto i=he0->FindBin(2.5); i<he2->GetXaxis()->GetLast(); i++){
    hr0->SetBinContent(i+1, fht1->Eval(he0->GetBinCenter(i+1))/he0->GetBinContent(i+1) );
    //    cout<<fht1->Eval(he0->GetBinCenter(i+1))<<"      "<<he0->GetBinContent(i+1)<<"   "<<fht1->Eval(he0->GetBinCenter(i+1))/he0->GetBinContent(i+1)<<endl;
    //    if(i<he2->FindBin(4.5))hr2->SetBinContent(i+1, fht2->Eval(he2->GetBinCenter(i+1))/he2->GetBinContent(i+1) );
    //    else hr2->SetBinContent(i+1, fht3->Eval(he2->GetBinCenter(i+1))/he2->GetBinContent(i+1) );
    if(i>he0->FindBin(4.5))hr2->SetBinContent(i+1, fht3->Eval(he2->GetBinCenter(i+1))/he2->GetBinContent(i+1) );
  }
  hr0->GetXaxis()->SetTitle("p_{T} [GeV]");
  hr0->GetYaxis()->SetTitle("Fit/Data");
  hr0->SetTitle(0);
  hr0->GetYaxis()->SetTitleSize(0.15);
  hr0->GetYaxis()->SetLabelSize(0.1);
  hr0->GetYaxis()->CenterTitle();
  hr0->GetYaxis()->SetTitleOffset(0.3);
  hr0->GetYaxis()->SetNdivisions(505);
  //  hr0->GetXaxis()->SetNdivisions(020);
  hr0->GetYaxis()->SetRangeUser(0, 2.);
  hr0->GetXaxis()->SetTitleSize(0.3);
  hr0->GetXaxis()->SetLabelSize(0.15);
  hr0->GetXaxis()->SetTitleOffset(0.63);
  hr0->GetXaxis()->SetRangeUser(2, 20);
  
  //  hr0->SetMarkerStyle(22);
  hr0->SetMarkerSize(0.5);
  //  hr2->SetMarkerStyle(22);
  hr2->SetMarkerSize(0.5);
  
  hr0->Draw();
  hr2->SetLineColor(kBlue);
  hr2->SetMarkerColor(kBlue);
  
  hr2->Draw("same");
  c->SaveAs("trigg_eff_fit_Sys.pdf");
  
}

