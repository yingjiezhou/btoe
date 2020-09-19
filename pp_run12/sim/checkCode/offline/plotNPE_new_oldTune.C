void plotNPE_new_oldTune(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  gStyle->SetOptStat(0000);
  
  //=============================================
  float pT[14], Rb[14], dyU[14], dyD[14], dysU[14], dysD[14];
  float pully[14], pullye[14];
  float pully2[14], pullye2[14];
  float x1, x2, x3, x4;
  float dx[14] = {0.};
  float dx2[14] = {0.};
  
  
  ifstream infile("starDataNPE.txt");
  int i = 0;
  string line;
  while(getline(infile,line)){
    sscanf(line.c_str(),"%f %f %f %f",&x1, &x2, &x3, &x4);
    pT[i] = x1;
    Rb[i] = x2;
    dyU[i] = x3;
    dyD[i] = x3;
    dysU[i] = x4;
    dysD[i] = x4;
    i++;
  }
  
  TGraphAsymmErrors* stat = new TGraphAsymmErrors(14,pT,Rb,dx,dx,dyD,dyU);
  TGraphAsymmErrors* syst = new TGraphAsymmErrors(14,pT,Rb,dx2,dx2,dysD,dysU);
  syst->SetLineColor(kRed);
  syst->SetMarkerColor(kRed);
  syst->SetFillStyle(0);
  stat->SetMarkerStyle(20);
  stat->SetMarkerColor(kRed);
  stat->SetLineColor(kRed);
  //=============================================
  
  auto f = new TFile("rootfile/rootfile_fromSim/output_v5.root", "READ"); // old zach
  auto fyj = new TFile("rootfile/rootfile_fromSim/output_v6.root", "READ"); // yj
  
  auto h1 = (TH1D*) fyj->Get("heptN")->Clone("heptN_yj");
  auto h2 = (TH1D*) fyj->Get("hceptN")->Clone("hceptN_yj");
  auto h3 = (TH1D*) fyj->Get("hbeptN")->Clone("hbeptN_yj");
  auto hLc = (TH1D*)fyj->Get("hLceN")->Clone("hLceN_yj");
  auto hD0 = (TH1D*)fyj->Get("hD0eN")->Clone("hD0eN_yj");
  auto hRes = (TH1D*)fyj->Get("hReseN")->Clone("hReseN_yj");
  //=============================================
  
  auto hh1 = (TH1D*) f->Get("heptN");
  auto hh2 = (TH1D*) f->Get("hceptN");
  auto hh3 = (TH1D*) f->Get("hbeptN");
  
  auto hhLc = (TH1D*)f->Get("hLceN");
  auto hhD0 = (TH1D*)f->Get("hD0eN");
  auto hhRes = (TH1D*)f->Get("hReseN");
  //=============================================
  
  auto htmp = new TH1D("htmp", "htmp", 200., 0., 20.);
  for(int i = 0; i< 200; i++){
    double pt = htmp->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt * 0.1); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 600. / 1.4 ;
    
    tmpp = tmpp/14.;
    h1->SetBinContent(i+1, h1->GetBinContent(i+1) * tmpp ); // because of the normalization
    h2->SetBinContent(i+1, h2->GetBinContent(i+1) * tmpp );
    h3->SetBinContent(i+1, h3->GetBinContent(i+1) * tmpp );
    hLc->SetBinContent(i+1, hLc->GetBinContent(i+1) * tmpp );
    hD0->SetBinContent(i+1, hD0->GetBinContent(i+1) * tmpp );
    hRes->SetBinContent(i+1, hRes->GetBinContent(i+1) * tmpp );
    
    h1->SetBinError(i+1, h1->GetBinError(i+1)*tmpp);
    h2->SetBinError(i+1, h2->GetBinError(i+1)*tmpp);
    h3->SetBinError(i+1, h3->GetBinError(i+1)*tmpp);
    hLc->SetBinError(i+1, hLc->GetBinError(i+1) * tmpp );
    hD0->SetBinError(i+1, hD0->GetBinError(i+1) * tmpp );
    hRes->SetBinError(i+1, hRes->GetBinError(i+1) * tmpp );
    
    
    tmpp = tmpp * 14./27.;
    hh1->SetBinContent(i+1, hh1->GetBinContent(i+1) * tmpp );
    hh2->SetBinContent(i+1, hh2->GetBinContent(i+1) * tmpp );
    hh3->SetBinContent(i+1, hh3->GetBinContent(i+1) * tmpp );
    hhLc->SetBinContent(i+1, hhLc->GetBinContent(i+1) * tmpp );
    hhD0->SetBinContent(i+1, hhD0->GetBinContent(i+1) * tmpp );
    hhRes->SetBinContent(i+1, hhRes->GetBinContent(i+1) * tmpp );
    
    hh1->SetBinError(i+1, hh1->GetBinError(i+1)*tmpp);
    hh2->SetBinError(i+1, hh2->GetBinError(i+1)*tmpp);
    hh3->SetBinError(i+1, hh3->GetBinError(i+1)*tmpp);
    hhLc->SetBinError(i+1, hhLc->GetBinError(i+1) * tmpp );
    hhD0->SetBinError(i+1, hhD0->GetBinError(i+1) * tmpp );
    hhRes->SetBinError(i+1, hhRes->GetBinError(i+1) * tmpp );
    
  }
  
  h1->SetMarkerStyle(24);
  h2->SetMarkerStyle(24);
  h3->SetMarkerStyle(24);
  hLc->SetMarkerStyle(24);
  hD0->SetMarkerStyle(24);
  hRes->SetMarkerStyle(21+4);
  
  hhLc->SetMarkerStyle(20);
  hhD0->SetMarkerStyle(20);
  hhRes->SetMarkerStyle(21);
  
  hhRes->SetMarkerColor(kRed);
  hRes->SetMarkerColor(kRed);
  
  hLc->SetMarkerColor(kRed+2);
  hD0->SetMarkerColor(kBlack);
  hhLc->SetMarkerColor(kRed+2);
  hhD0->SetMarkerColor(kBlack);
  
  h1->SetMarkerColor(kBlue);
  h2->SetMarkerColor(kGreen+2);
  h3->SetMarkerColor(kMagenta+2);
  
  
  h1->SetLineColor(kBlue);
  h2->SetLineColor(kGreen+2);
  h3->SetLineColor(kMagenta+2);
  
  
  hh1->SetMarkerStyle(20);
  hh2->SetMarkerStyle(20);
  hh3->SetMarkerStyle(20);
  
  hh1->SetMarkerColor(kBlue);
  hh2->SetMarkerColor(kGreen+2);
  hh3->SetMarkerColor(kMagenta+2);
  
  hh1->SetLineColor(kBlue);
  hh2->SetLineColor(kGreen+2);
  hh3->SetLineColor(kMagenta+2);
  //=============================================
  auto cnpe = new TCanvas("cnpe", "cnpe");
  TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
  TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
  TLegend *leg = new TLegend(0.45,0.7,0.9,0.85);
  leg->SetNColumns(2);
  leg->AddEntry(hh1,"#it{c+b}#rightarrow#it{e} (old Tune)","p");
  leg->AddEntry(h1,"#it{c+b}#rightarrow#it{e} (new mode)","p");
  leg->AddEntry(stat,"STAR(published) ","p");
  
  leg->SetFillStyle ( 0);
  leg->SetFillColor ( 0);
  leg->SetBorderSize( 0);
  
  pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
  pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
  pad1->SetBottomMargin(0.02);
  pad1->SetTopMargin(0.08);
  pad2->SetTopMargin(0.015);
  pad2->SetBottomMargin(0.5);
  pad2->SetBorderMode(0);
  pad1->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  pad1->SetLogy();
  //  c->SetLogy();
  pad1->SetTickx();
  pad1->SetTicky();
  hh1->SetTitle("");
  hh1->GetYaxis()->SetRangeUser(1e-12, 1e-1);
  hh1->Draw("p");
  
  syst->Draw("same pe2");
  stat->Draw("same pe");
  h1->Draw("same p");
  leg->Draw("same");
  pad2->cd();
  
  auto fline = new TF1("fline","1",0,20);
  fline->SetLineStyle(7);
  for(auto i=0; i<14; i++){
    pully[i] = (h1->GetBinContent(h1->FindBin(pT[i]))/Rb[i]);
    pully2[i] = (hh1->GetBinContent(hh1->FindBin(pT[i]))/Rb[i]);
    
    pullye[i] = (h1->GetBinContent(h1->FindBin(pT[i]))/Rb[i])*sqrt((h1->GetBinError(h1->FindBin(pT[i])))/dyU[i]);
    pullye2[i] = (hh1->GetBinContent(hh1->FindBin(pT[i]))/Rb[i])*sqrt((hh1->GetBinError(hh1->FindBin(pT[i])))/dyU[i]);
  }
  
  TGraphErrors *gh1 = new TGraphErrors(14,pT,pully,dx,pullye);
  TGraphErrors *ghh1 = new TGraphErrors(14,pT,pully2,dx,pullye2);
  
  gh1->SetMarkerColor(kBlue);
  ghh1->SetMarkerColor(kBlue);
  gh1->SetMarkerStyle(24);
  gh1->SetLineColor(kBlue);
  ghh1->SetLineColor(kBlue);
  
  htmp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  htmp->GetYaxis()->SetTitle("Sim/Data");
  htmp->SetTitle(0);
  htmp->GetYaxis()->SetTitleSize(0.12);
  htmp->GetYaxis()->SetLabelSize(0.1);
  htmp->GetYaxis()->CenterTitle();
  htmp->GetYaxis()->SetTitleOffset(0.25);
  htmp->GetYaxis()->SetNdivisions(505);
  htmp->GetYaxis()->SetRangeUser(0,5);
  htmp->GetXaxis()->SetTitleSize(0.2);
  htmp->GetXaxis()->SetLabelSize(0.15);
  htmp->GetXaxis()->SetTitleOffset(0.63);
  
  htmp->Draw();
  gh1->Draw("same PE");
  ghh1->Draw("same PE");
  fline->Draw("same");
  cnpe->SaveAs("plotNPE_new_oldTune.pdf");
  //=============================================
  
  return 0;
}
