TH1D* npeFromDataOld();
TH1D* npeFromDataNew();

void plotNPE_comp(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  float pT[14], Rb[14], dyU[14], dyD[14], dysU[14], dysD[14];
  float pully[14], pullye[14];
  float pully2[14], pullye2[14];
  float x1, x2, x3, x4;
  float dx[14] = {0.};
  //  float dx2[14] = {0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18};
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
  //  syst->SetLineWidth(2);
  //  stat->SetLineWidth(2);
  stat->SetMarkerStyle(20);
  //  stat->SetMarkerSize(1.5);
  stat->SetMarkerColor(kRed);
  stat->SetLineColor(kRed);
  
  stat->SetMarkerStyle(20);
  //  stat->SetMarkerSize(1.5);
  stat->SetMarkerColor(kRed);
  stat->SetLineColor(kRed);
  
  double xzebo[] = {1.013, 1.924, 2.685, 3.181, 3.982, 4.631, 5.278, 6.194, 6.993};
  double yzebo[] = {2.628, 1.138, 0.473, 0.243, 0.072, 0.027, 0.013, 0.003, 0.001};
  
  //  for(auto i = 0; i<10; i++){
  //    yzebo[i] *= 1e-6;
  //  }
  TGraph* gr = new TGraph(9,xzebo, yzebo);
  
  
  TH1D *holdNPE = npeFromDataOld();
  TH1D *hnewNPE = npeFromDataNew();
  
  
  auto f = new TFile("rootfile/crossSectionE.root", "READ");
  auto h1 = (TH1D*) f->Get("hbept");
  auto h2 = (TH1D*) f->Get("hcept");
  auto h3 = (TH1D*) f->Get("hept"); //b+c
  
  h1->Rebin(10);
  h2->Rebin(10);
  h3->Rebin(10);
  
  for(int i = 0; i< h1->GetNbinsX(); i++){
    double pt = h1->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* h1->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp/100. ; // number of root file
    h1->SetBinContent(i+1, h1->GetBinContent(i+1) * tmpp);
    h1->SetBinError(i+1, h1->GetBinError(i+1)*tmpp);
    h2->SetBinContent(i+1, h2->GetBinContent(i+1) * tmpp);
    h2->SetBinError(i+1, h2->GetBinError(i+1)*tmpp);
    h3->SetBinContent(i+1, h3->GetBinContent(i+1) * tmpp);
    h3->SetBinError(i+1, h3->GetBinError(i+1)*tmpp);
    
  }
  
  h1->SetMarkerStyle(24);
  h2->SetMarkerStyle(25);
  h3->SetMarkerStyle(23);

  //=====================
  
  
  auto leg = new TLegend(0.4,0.65,0.9,0.9);
  leg->AddEntry(stat, "STAR (published)", "p");
  //  leg->AddEntry(h1, "HQ(b,c), b #rightarrow e", "lp");
  //  leg->AddEntry(h1, "HQ(b,c), c #rightarrow e", "lp");
  leg->AddEntry(h3, "PYTHIA,STAR HF tune v1.0 HQbc, b+c #rightarrow e", "p");
  leg->AddEntry(holdNPE, "PYTHIA,STAR HF tune v1.1 MB, b+c #rightarrow e, old", "p");
  leg->AddEntry(hnewNPE, "PYTHIA,STAR HF tune v1.1 MB, b+c #rightarrow e, new", "p");
  
  //
  leg->SetFillStyle (0);
  leg->SetFillColor (0);
  leg->SetBorderSize(0);
  
  auto c = new TCanvas("c", "c");
  c->SetLogy();
  c->SetGridx();
  c->SetGridy();
  
  h3->GetXaxis()->SetRangeUser(0, 12);
  h3->GetYaxis()->SetRangeUser(1e-11, 1e-1);
  
  //  gr->SetLineColor(2);
  h3->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  h3->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
  h3->GetXaxis()->SetNdivisions(510, "X");
  //  gr->Draw("al");
  //  gs->Draw("same l");
  h3->Draw("p");
  holdNPE->Draw("same p");
  hnewNPE->Draw("same p");
  stat->Draw("same pe");
  leg->Draw("same");
  
  c->SaveAs("plotNPE_comp.pdf");
  return;
}

//==========================
TH1D* npeFromDataOld(){
  auto f = new TFile("rootfile/rootfile_fromSim/output_v5.root", "READ"); // old pythia tune
  auto fyj = new TFile("rootfile/rootfile_fromSim/output_v6.root", "READ"); // new pythia tune
  
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
  
  h1->SetMarkerStyle(33);
  h2->SetMarkerStyle(33);
  h3->SetMarkerStyle(33);
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
  
  
  hh1->SetMarkerStyle(27);
  hh2->SetMarkerStyle(27);
  hh3->SetMarkerStyle(27);
  
  hh1->SetMarkerColor(kBlue);
  hh2->SetMarkerColor(kGreen+2);
  hh3->SetMarkerColor(kMagenta+2);
  
  hh1->SetLineColor(kBlue);
  hh2->SetLineColor(kGreen+2);
  hh3->SetLineColor(kMagenta+2);
  
  return hh1;
}
TH1D* npeFromDataNew(){
  auto f = new TFile("rootfile/rootfile_fromSim/output_v5.root", "READ"); // old pythia tune
  auto fyj = new TFile("rootfile/rootfile_fromSim/output_v6.root", "READ"); // new pythia tune
  
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
  
  h1->SetMarkerStyle(33);
  h2->SetMarkerStyle(33);
  h3->SetMarkerStyle(33);
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
  
  
  hh1->SetMarkerStyle(27);
  hh2->SetMarkerStyle(27);
  hh3->SetMarkerStyle(27);
  
  hh1->SetMarkerColor(kBlue);
  hh2->SetMarkerColor(kGreen+2);
  hh3->SetMarkerColor(kMagenta+2);
  
  hh1->SetLineColor(kBlue);
  hh2->SetLineColor(kGreen+2);
  hh3->SetLineColor(kMagenta+2);
  
  return h1;
}
