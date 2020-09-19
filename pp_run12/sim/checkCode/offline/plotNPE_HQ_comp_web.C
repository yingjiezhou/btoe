void plotNPE_HQ_comp_web(){
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
  
  //  double xs[8] = {2.55, 3.14, 4.01, 6.06, 7.53, 8.94, 10.2, 11.9};
  //  double ys[8] = {5.13e-7, 2.07e-7, 6.35e-8, 4.15e-9, 7.39e-10, 1.58e-10, 4.83e-11, 1.24e-11};
  //  double es[8] = {0};
  //  TGraph* gs = new TGraph(8, xs, ys); // from shenghui, jpsi->e cross section
  
  
  auto f = new TFile("rootfile/crossSectionE.root", "READ");
  auto h1 = (TH1D*) f->Get("hbept");
  auto h2 = (TH1D*) f->Get("hcept");
  auto h3 = (TH1D*) f->Get("hept"); //b+c
  auto htmp = (TH1D*) f->Get("hbcept");

  
  const int binn = 20;
  h1->Rebin(binn);
  h2->Rebin(binn);
  h3->Rebin(binn);
  htmp->Rebin(binn);
  auto hbce = (TH1D*)h1->Clone("hbce");
  hbce->Add(htmp, -1.);
  
  for(int i = 0; i< h1->GetNbinsX(); i++){
    double pt = h1->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt* h1->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 1. ; // rapidy
    tmpp = tmpp/100. ; // number of root file
    h1->SetBinContent(i+1, h1->GetBinContent(i+1) * tmpp);
    h1->SetBinError(i+1, h1->GetBinError(i+1)*tmpp);
    h2->SetBinContent(i+1, h2->GetBinContent(i+1) * tmpp);
    hbce->SetBinContent(i+1, hbce->GetBinContent(i+1) * tmpp);

    h2->SetBinError(i+1, h2->GetBinError(i+1)*tmpp);
    h3->SetBinContent(i+1, h3->GetBinContent(i+1) * tmpp);
    h3->SetBinError(i+1, h3->GetBinError(i+1)*tmpp);
    hbce->SetBinError(i+1, hbce->GetBinError(i+1) * tmpp);

  }
  //
  //  h1->SetMarkerColor(kGreen+2);
  //  h1->SetLineColor(kGreen+2);
  h1->SetMarkerStyle(24);
  h2->SetMarkerStyle(25);
  h3->SetMarkerStyle(23);
  hbce->SetMarkerStyle(24);
  hbce->SetMarkerColor(kBlue);

  //=====================
  
  
  auto leg = new TLegend(0.6,0.7,0.88,0.9);
  leg->AddEntry(stat, "STAR (published)", "lp");
  leg->AddEntry(h1, "HQ(b,c), all b #rightarrow e", "lp");
  leg->AddEntry(hbce, "HQ(b,c), prompt b #rightarrow e", "lp");
  leg->AddEntry(h2, "HQ(b,c), prompt c #rightarrow e", "lp");
  leg->AddEntry(h3, "HQ(b,c), b+c #rightarrow e", "lp");

  //
  leg->SetFillStyle (0);
  leg->SetFillColor (0);
  leg->SetBorderSize(0);
  
  auto c = new TCanvas("c", "c");
  c->SetLogy();
  c->SetGridx();
  c->SetGridy();
//  c->SetNdivisions();
  
  //  gr->GetYaxis()->SetRangeUser(1e-15, 1e-3);
  //  gr->GetYaxis()->SetRangeUser(5e-7, 12);
  
  //  gr->GetXaxis()->SetRangeUser(2.5, 8);
  //  gr->GetXaxis()->SetRangeUser(0, 16);
  h1->GetXaxis()->SetRangeUser(0, 12);
  h1->GetYaxis()->SetRangeUser(1e-11, 1e-1);
  
  //  gr->SetLineColor(2);
  h1->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  h1->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
  h1->GetXaxis()->SetNdivisions(510, "X");
  //  gr->Draw("al");
  //  gs->Draw("same l");
  h1->Draw("p");
  hbce->Draw("same p");
  h2->Draw("same p");
  h3->Draw("same p");
  stat->Draw("same pe");
  leg->Draw("same");
  
  //  leg->Draw("same");
  c->SaveAs("plotNPE_HQ_comp_web.pdf");
  return;
}
