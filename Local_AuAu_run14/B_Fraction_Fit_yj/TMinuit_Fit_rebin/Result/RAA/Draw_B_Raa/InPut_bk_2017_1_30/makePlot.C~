void makePlot(){
  float pT[9], Rb[9], dyU[9], dyD[9], dysU[9], dysD[9];
  float pT6[6], Rb6[6], dy6[6], dysU6[6], dysD6[6];
  float dx[9] = {0.};
  float dx2[9] = {0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18};
  float x1, x2, x3, x4, x5, x6;
  ifstream infile("plotPoints.txt");
  ifstream infile2("Run6Result.txt");
  int i = 0;
  string line;
  cout << "Run 12 Points" << endl;
  while(getline(infile,line))
  {  
    sscanf(line.c_str(),"%f %f %f %f %f %f",&x1, &x2, &x3, &x4, &x5, &x6);
    pT[i] = x1;
    Rb[i] = x2;
    dyU[i] = x3-x2;
    dyD[i] = x2-x4;
    dysU[i] = x5-x2;
    dysD[i] = x2-x6;
    cout << pT[i] << " ";
    cout << Rb[i] << " ";
    cout << dyD[i] << " ";
    cout << dyU[i] << " ";
    cout << dysD[i] << " ";
    cout << dysU[i] << endl;
    i++;
  }

  int k=0;
  
  cout << "Run 5/6 Points (Extracted from AnaNote)" << endl;
  while(getline(infile2,line))
  {  
    sscanf(line.c_str(),"%f %f %f %f %f",&x1, &x2, &x3, &x4, &x5);
    pT6[k] = x1;
    Rb6[k] = x2;
    dy6[k] = x3;
    dysD6[k] = x2-x4;
    dysU6[k] = x5-x2;
    cout << pT6[k] << " ";
    cout << Rb6[k] << " ";
    cout << dy6[k] << " ";
    cout << dysD6[k] << " ";
    cout << dysU6[k] << endl;
    k++;
  }

  TGraphAsymmErrors* stat = new TGraphAsymmErrors(9,pT,Rb,dx,dx,dyD,dyU); 
  TGraphAsymmErrors* syst = new TGraphAsymmErrors(9,pT,Rb,dx2,dx2,dysD,dysU);
  TGraphErrors* stat6 = new TGraphErrors(7,pT6,Rb6,dx,dy6);
  TGraphAsymmErrors* syst6 = new TGraphAsymmErrors(7,pT6,Rb6,dx2,dx2,dysD6,dysU6);
  TLegend* leg = new TLegend(0.11,0.72,0.5,0.89);

  TGraph *FONLL[2];
  FONLL[0] = new TGraph("FONLL_BAND_UP.dat");
  FONLL[1] = new TGraph("FONLL_BAND_DW.dat");
  FONLL[0]->SetLineStyle(2);
  FONLL[1]->SetLineStyle(2);

  TCanvas* c1 = new TCanvas("c1","test",50,50,1000,1000);
  c1->cd();
  syst->SetLineColor(kRed);
  syst->SetMarkerColor(kRed);
  syst->SetFillStyle(0);
  syst->SetLineWidth(2);
  stat->SetLineWidth(2);
  stat->SetMarkerStyle(20);
  stat->SetMarkerSize(1.5);
  stat->SetMarkerColor(kRed);
  stat->SetLineColor(kRed);
  stat->GetYaxis()->SetRangeUser(-0.2,1.2);
  stat->GetXaxis()->SetRangeUser(0,12);
  syst->GetYaxis()->SetRangeUser(-0.2,1.2);
  syst->GetXaxis()->SetRangeUser(0,12);
  syst->Draw("ape2");
  stat->Draw("same pe");

  FONLL[0]->Draw("same");
  FONLL[1]->Draw("same");

  syst6->SetLineColor(kBlack);
  syst6->SetMarkerColor(kBlack);
  syst6->SetFillStyle(0);
  syst6->SetLineWidth(2);
  stat6->SetLineWidth(2);
  stat6->SetMarkerStyle(29);
  stat6->SetMarkerSize(1.8);
  stat6->SetMarkerColor(kBlack);
  stat6->SetLineColor(kBlack);
  syst6->Draw("same pe2");
  stat6->Draw("same pe");

  leg->AddEntry(stat,"Run 12 p+p 200 GeV","pe");
  leg->AddEntry(stat6,"Run 5/6 p+p 200 GeV","pe");
  leg->AddEntry(FONLL[0],"FONLL","l");
  leg->Draw("same");


  TFile* fOut = new TFile("run12NPEh_rBPoints.root","RECREATE");
  stat->Write("StatError");
  syst->Write("systError");
  stat6->Write("StatError_Run6");
  syst6->Write("systError_Run6");
  FONLL[0]->Write("FONLL_UPPER");
  FONLL[1]->Write("FONLL_LOWER");
  fOut->Close();
}

