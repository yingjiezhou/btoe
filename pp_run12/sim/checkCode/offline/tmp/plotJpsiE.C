void plotJpsi(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  double xzebo[10] = {0.883, 1.37, 1.91, 2.68, 3.36, 4.07, 4.90, 5.64, 6.64, 7.12};
  double yzebo[10] = {0.00131, 0.000215, 0.0000354, 0.00000491, 0.00000107, 2.46e-7, 7.93e-8, 2.29e-8, 7.80e-9, 3.74e-9};
  double ezebo[10] = {0};
  
  double xs[] = {1.60, 2.36, 2.82, 3.33, 3.65, 4.62, 5.07, 5.87, 6.64, 7.12};
  double ys[] = {0.0000122, 0.00000313, 0.00000159, 6.81e-7, 4.33e-7, 8.89e-8, 4.03e-8, 1.46e-8, 5.89e-9, 3.16e-9};
  double es[10] = {0};

  float pT[14], Rb[14], dyU[14], dyD[14], dysU[14], dysD[14];
   float pully[14], pullye[14];
   float pully2[14], pullye2[14];
   float x1, x2, x3, x4;
   float dx[14] = {0.};
   //  float dx2[14] = {0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18};
   float dx2[14] = {0.};
  ifstream infile("Star_data.txt");
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
  stat->SetMarkerStyle(20);
  //  stat->SetMarkerSize(1.5);
  stat->SetMarkerColor(kRed);
  stat->SetLineColor(kRed);
  
//  for(auto i = 0; i<10; i++){
//    yzebo[i] = yzebo[i]/3.;
//    ys[i] = ys[i]/3.;
//  }
  auto gs = new TGraph(10, xs, ys);
  TGraph* gr = new TGraph(10,xzebo, yzebo);

  
  auto f = new TFile("readTreeSecJpsi_v1.root", "READ"); // old
  
  auto h1 = (TH1D*) f->Get("hjeptN");

  auto hh1 = (TH1D*) f->Get("heptN");
  auto hh2 = (TH1D*) f->Get("hceptN");
  auto hh3 = (TH1D*) f->Get("hbeptN");
  
  for(int i = 0; i< 2000; i++){
    double pt = h1->GetBinCenter(i+1);
//    cout<<"  bin center is :  "<<pt<<endl;
    double tmpp = 1./(2* TMath::Pi() * pt* h1->GetBinWidth(i)); ////!!!!! notice here divide by dpT
    tmpp = tmpp / 120. / 1.4 ;
    
    tmpp = tmpp/900.;
    hh1->SetBinContent(i+1, hh1->GetBinContent(i+1) * tmpp ); // because of the normalization
    hh2->SetBinContent(i+1, hh2->GetBinContent(i+1) * tmpp );
    hh3->SetBinContent(i+1, hh3->GetBinContent(i+1) * tmpp );
    hh1->SetBinError(i+1, hh1->GetBinError(i+1)*tmpp);
    hh2->SetBinError(i+1, hh2->GetBinError(i+1)*tmpp);
    hh3->SetBinError(i+1, hh3->GetBinError(i+1)*tmpp);
    
    h1->SetBinContent(i+1, h1->GetBinContent(i+1) * tmpp/2.);
    h1->SetBinError(i+1, h1->GetBinError(i+1)*tmpp/2.);
  }
  
  h1->SetMarkerColor(kRed);
  h1->SetLineColor(kRed);

  hh1->SetMarkerColor(kBlue);
  hh2->SetMarkerColor(kGreen+2);
  hh3->SetMarkerColor(kMagenta+2);
  
  hh1->SetLineColor(kBlue);
  hh2->SetLineColor(kGreen+2);
  hh3->SetLineColor(kMagenta+2);
  
  gr->SetMarkerColor(kBlue);
//  gr->SetMarkerstyle(20+4);
  
  gs->SetMarkerColor(kMagenta+2);
//  gs->SetMarkerstyle(20+4);

  f = new TFile("BackgroundSpectrum.root", "READ");
  auto hjpsiShenghui  = (TH1F*)f->Get("JpsiElectron");
  hjpsiShenghui->GetXaxis()->SetRangeUser(2.5, 10);
//  cout<<h1->GetBinContent(h1->FindBin(2.5))<<endl;
//  cout<<hjpsiShenghui->GetBinContent(hjpsiShenghui->FindBin(2.5))<<endl;
//
//  cout<<h1->GetBinContent(h1->FindBin(2.5))/hjpsiShenghui->GetBinContent(hjpsiShenghui->FindBin(2.5))<<endl;
//  hjpsiShenghui->Scale(h1->GetBinContent(h1->FindBin(2.5))/hjpsiShenghui->GetBinContent(hjpsiShenghui->FindBin(2.5)));

//  hjpsiShenghui->Rebin(10);
//  hjpsiShenghui->Scale(1./10.);
  
//  h1->Scale(0.1);
  auto h1r = (TH1D*)h1->Clone("hjpsiShenghuir"); // ration to shenghui/ NPE

  auto cr = new TCanvas("cr", "cr");
  const int nPtBins = 10;
  const double ptbin[nPtBins+1]={0.,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5};
//  h1r->Rebin(10);
//  h1r->Scale(1./10.);

  auto hh1r = (TH1D*)hh2->Clone("hh1r"); // NPE
//  hh1r->Rebin(10);
//  hh1r->Scale(1./10.);
  
//  hjpsiShenghui->Rebin(10);
//  hjpsiShenghui->Scale(1./10.);

//  auto hh1rbin1r =(TH1D*)h1r->Clone("hh1rbin1r");
  auto hh1rbin1r = (TH1D*)h1r->Rebin(10, "hh1rbin1r", ptbin);
  auto hjpsiShenghuir =(TH1D*)hjpsiShenghui->Rebin(10, "hjpsiShenghuir", ptbin);
  auto hh1rbin =(TH1D*)hh1r->Rebin(10, "hh1rbin", ptbin);

//  hh1rbin1r->Divide(hjpsiShenghuir);
  hh1rbin1r->Divide(hh1rbin);
  for(auto i=0; i<10; i++) cout<<hh1rbin1r->GetBinContent(i+1)<<", ";

//  for(auto i = 0; i<11; i++){
//    hh1rbin1r->SetBinContent(i+1, hh1rbin1r->GetBinContent(i+1)/hh1rbin1r->GetBinWidth(i+1));
//  }
  hh1rbin1r->GetXaxis()->SetRangeUser(2.5, 10);
  hh1rbin1r->GetYaxis()->SetRangeUser(0., 0.3);
  hh1rbin1r->GetXaxis()->SetTitle("p_{T}");
//  hh1rbin1r->GetYaxis()->SetTitle("Yj/SH");
  hh1rbin1r->GetYaxis()->SetTitle("Jpsi/NPE");

  hh1rbin1r->Draw();
  cr->SaveAs("cr_raw_rebin_NPE_yj.pdf");
  
  auto cc = new TCanvas("cc", "cc");
  cc->SetLogy();
  h1->SetTitle("");
  h1->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
  h1->GetYaxis()->SetRangeUser(5e-13, 1e-4);
  h1->GetXaxis()->SetRangeUser(2.5, 10);
  h1->GetXaxis()->SetNdivisions(505);
  h1->Draw();
  hjpsiShenghui->Draw("same");
  cc->SaveAs("jpsie_comp.pdf");
  
//  hjpsiShenghui->Scale(h1->GetBinContent(h1->FindBin(2.5))/hjpsiShenghui->GetBinContent(hjpsiShenghui->FindBin(2.5)));

  TLegend *leg = new TLegend(0.55,0.7,0.9,0.85);
  leg->SetFillStyle ( 0);
  leg->SetFillColor ( 0);
  leg->SetBorderSize( 0);

  leg->AddEntry(h1,"J/#psi#rightarrow#it{e}^{+}#it{e}^{-} /2 (old Tune) ","p");
  leg->AddEntry(hjpsiShenghui,"J/#psi#rightarrow#it{e}^{+}#it{e}^{-} /2 (shenghui) ","p");

  leg->AddEntry(hh2,"#it{c}#rightarrow#it{e} (old Tune) ","p");
  leg->AddEntry(hh3,"#it{b}#rightarrow#it{e} (old Tune) ","p");
  leg->AddEntry(hh1,"#it{c+b}#rightarrow#it{e} (old Tune)","p");
  leg->AddEntry(gr,"#it{c+b}#rightarrow#it{e} (from zebo)","p");
  leg->AddEntry(gs,"#it{b}#rightarrow#it{e} (from zebo)","p");
  leg->AddEntry(stat,"STAR(published) ","p");


  hh1->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
  hh1->GetXaxis()->SetTitle("p_{T}(GeV/#it{c})");
  hh2->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
  hh2->GetXaxis()->SetTitle("p_{T}(GeV/#it{c})");

  auto c = new TCanvas("c", "c");
  auto pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
  auto pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
  pad1->SetBottomMargin(0.02);
  pad1->SetTopMargin(0.08);
  pad2->SetTopMargin(0.08);
  pad2->SetBottomMargin(0.5);
  pad2->SetBorderMode(0);
  pad1->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  pad1->SetLogy();
  pad1->SetTickx();
  pad1->SetTicky();
  pad1->SetGridx();
  pad1->SetGridy();

  h1->SetTitle("");
  h1->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
  h1->GetYaxis()->SetRangeUser(5e-13, 1e-4);
  h1->GetXaxis()->SetRangeUser(2.5, 10);
  h1->GetXaxis()->SetNdivisions(505);
  h1->Draw("p");
  hh1->Draw("same p");
  hh2->Draw("same p");
  hh3->Draw("same p");
  hjpsiShenghui->Draw("same p");
  gr->Draw("same p");
  gs->Draw("same p");
  stat->Draw("same pe");
  leg->Draw("same");

  pad2->cd();
  pad2->SetGridx();
  pad2->SetGridy();
  auto hjpsir = (TH1D*)h1->Clone("hjpsir");
  hjpsir->Divide(hh1);
  hjpsir->GetXaxis()->SetTitle("p_{T} GeV/c");
  hjpsir->GetYaxis()->SetTitle("#frac{J/#psi#rightarrow #it{e}^{+}#it{e}^{-}}{NPE#rightarrow e}");
  hjpsir->SetTitle(0);
  hjpsir->GetYaxis()->SetTitleSize(0.15);
  hjpsir->GetYaxis()->SetLabelSize(0.1);
  hjpsir->GetYaxis()->CenterTitle();
  hjpsir->GetYaxis()->SetTitleOffset(0.4);
  hjpsir->GetYaxis()->SetNdivisions(306);
  hjpsir->GetXaxis()->SetNdivisions(505);
  hjpsir->GetYaxis()->SetRangeUser(0, 0.3);
  hjpsir->GetXaxis()->SetTitleSize(0.2);
  hjpsir->GetXaxis()->SetLabelSize(0.15);
  hjpsir->GetXaxis()->SetTitleOffset(0.63);
  hjpsir->Draw();

  c->SaveAs("jpsi.pdf");
//
}
