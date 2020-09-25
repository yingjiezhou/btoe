void compTrack(){
//  gStyle->SetOptFit(1111);

  gROOT->ProcessLine(".x ~/myStyle.C");
  
  auto f2 = new TFile("npe_tree_Mar3_1.root", "READ"); // zach,
  auto f = new TFile("npe_tree_Mar16_1.root" , "READ"); // Me, new run list
  
  auto hf = (TH1F*) f->Get("mh1PtAllTracks_2")->Clone("yj");
  auto hf2 = (TH1F*) f2->Get("mh1PtAllTracks_2");
  
  auto hhf = (TH1F*) f->Get("mh1PtAllTracks_0")->Clone("yjh");
  auto hhf2 = (TH1F*) f2->Get("mh1PtAllTracks_0");
  
  hf->Sumw2(0);
  hf2->Sumw2(0);
  hhf->Sumw2(0);
  hhf2->Sumw2(0);
    
  hf->SetMarkerColor(kRed);
  hf->SetLineColor(kRed);
  hf->SetMarkerStyle(22);
  
 
  hhf->SetMarkerColor(kBlue);
  hhf->SetLineColor(kBlue);
  hhf->SetMarkerStyle(21);

  hhf->Divide(hhf2);
  hf->Divide(hf2);
//  hf->Sumw2(0);
  hf->GetYaxis()->SetRangeUser(0.8, 1.2);
  hf->GetXaxis()->SetTitle("p_{T} GeV/c");

  hf->GetYaxis()->SetTitle("all tracks number ratio Shenghui/Zach");
  
  auto fc = new TF1("fc", "pol0", 0, 5);
  fc->SetLineColor(kBlack);
  fc->SetLineStyle(2);
  hf->Fit("fc");

  
  auto fhc = new TF1("fhc", "pol0", 0, 5);
  fhc->SetLineColor(kBlack);
  fhc->SetLineStyle(2);
  hhf->Fit("fhc");
  
  auto c = new TCanvas("c", "");
  
  auto tl = new TLegend(0.5,0.6,0.9,0.94);
  tl->AddEntry(hhf, Form("HT0, pol0 = %.3f #pm %.3f", fhc->GetParameter(0), fhc->GetParError(0)), "lp");
  tl->AddEntry(hf, Form("HT2, pol0 = %.3f #pm %.3f", fc->GetParameter(0), fc->GetParError(0)), "lp");

//  tl->AddEntry(hf, "new/old", "lp");

  tl->SetFillStyle ( 0);
  tl->SetFillColor ( 0);
  tl->SetBorderSize( 0);
  
  
  
  hf->Draw("p");
  hhf->Draw("same p");

  fc->Draw("same");
  fhc->Draw("same");

//  hf->Draw("same P text00");
  
  //hf2->Draw("same");
  tl->Draw("same");
  
  c->SaveAs("new_old_runlist_comp.pdf");
  return ;
}
