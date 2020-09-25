void comp(){
  gStyle->SetOptStat(0);
  //gROOT->ProcessLine(".x ~/myStyle.C");
  
  auto f2 = new TFile("npe_tree_Mar16_1.root", "READ"); // zach
  auto f = new TFile("npe_tree_Mar17_1.root" , "READ"); // Me
  
  auto hf = (TH1F*) f->Get("mh1TrigCount")->Clone("yj");
  auto hf2 = (TH1F*) f2->Get("mh1TrigCount");
  auto hnew  = new TH1F("fNentries", "Bin1=Semi * Bin2=UL * Bin3=LS * Bin4=Had", 10, 0, 10);
  
  hf->SetLineColor(kRed);
  hf->SetMarkerStyle(22);
  hf2->SetMarkerStyle(21);
  
  hf->SetMarkerColor(kRed);
  hnew->GetXaxis()->SetBinLabel(1, "Semi");
  hnew->GetXaxis()->SetBinLabel(2, "UL");
  hnew->GetXaxis()->SetBinLabel(3, "LS");
  hnew->GetXaxis()->SetBinLabel(4, "Hadron");
  hnew->GetYaxis()->SetRangeUser(0.9, 1.1);
  hnew->GetYaxis()->SetTitle("Triggered particle counts ratio");
  auto c = new TCanvas("c", "");
  
  auto tl = new TLegend(0.5,0.6,0.8,0.9);
  tl->AddEntry(hf, "Using PDSF Pico: YJ/Zach", "lp");
  //tl->AddEntry(hf2, "Zach", "lp");
  tl->SetFillStyle ( 0);
  tl->SetFillColor ( 0);
  tl->SetBorderSize( 0);
  hf->Divide(hf2);
  hf->Sumw2(0);
  auto fc = new TF1("fc", "pol0", 0, 5);
  fc->SetLineColor(kBlue);
  fc->SetLineStyle(2);
  
  hf->Fit("fc");
  hnew->Draw("");
  fc->Draw("same");
  hf->Draw("same P text00");
  
  //hf2->Draw("same");
  tl->Draw("same");
  //
  //  cout<<hf->GetBinContent(1)<<"    "<<hf2->GetBinContent(1)<<endl;
  //  cout<<hf->GetBinContent(2)<<"    "<<hf2->GetBinContent(2)<<endl;
  //  cout<<hf->GetBinContent(3)<<"    "<<hf2->GetBinContent(3)<<endl;
  //  cout<<hf->GetBinContent(4)<<"    "<<hf2->GetBinContent(4)<<endl;
  //  cout<<"semi ratio is yj/zach: "<<hf->GetBinContent(1)/hf2->GetBinContent(1)<<endl;
  //  cout<<"UL ratio is yj/zach: "<<hf->GetBinContent(2)/hf2->GetBinContent(2)<<endl;
  //  cout<<"LS ratio is yj/zach: "<<hf->GetBinContent(3)/hf2->GetBinContent(3)<<endl;
  //  cout<<"Had ratio is yj/zach: "<<hf->GetBinContent(4)/hf2->GetBinContent(4)<<endl;
  //
  //  //=============
  //  auto hf = (TH1F*) f->Get("mh1PtAllTracks_0")->Clone("yj");
  //  auto hf2 = (TH1F*) f2->Get("mh1PtAllTracks_0");
  //
  //  cout<<"track before cut ratio is yj/zach: "<<hf->Integral()/hf2->Integral()<<endl;
  c->SaveAs("badrun_comp.pdf");
  return ;
}
