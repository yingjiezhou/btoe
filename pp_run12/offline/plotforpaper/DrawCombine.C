void DrawCombine(){
  
  // Get Previous Analysis
  char line[1000];
  Int_t p=0;
  Float_t xP[100],yP[100],dyP[100],dyPSL[100],dyPSH[100],dxPS[100];
  Float_t yy2[100], ee12[100],ee2l2[100], ee2h2[100];
  ifstream fp1("/Users/zhouyingjie/Local/PWG/NPE/1_pp_zamiller/ppRun12Ana/NPEhPhiAnalysis2015/run12NPEhResults/getPointsFromImage/Run6Result.txt",ios::in);
  while (!fp1.eof()){
    fp1.getline(line,1000);
    sscanf(line,"%f %f %f %f %f",&xP[p],&yP[p],&dyP[p],&dyPSL[p],&dyPSH[p]);
    printf("Run6 data: %f %f\n",xP[p],yP[p]);
    dyPSL[p] = yP[p]-dyPSL[p];   // convert from max/min of error bar to value of
    dyPSH[p] = dyPSH[p] - yP[p]; // error bar for plotting
    dxPS[p] = 0.15;
    xP[p] +=0.2;
    p++;
  }
  fp1.close();
  TGraphErrors *grP = new TGraphErrors(p,xP,yP,0,dyP);
  TGraphAsymmErrors *grPS = new TGraphAsymmErrors(p,xP,yP,dxPS,dxPS,dyPSL,dyPSH);
  //===========
  // run12
  
  TFile *run12 = new TFile("run12NPEh_rBPoints.root");
  auto StatError = (TGraphAsymmErrors*)run12->Get("StatError");
  auto SystError =(TGraphAsymmErrors*)run12->Get("systError");
  for(int i = 0;i<6;i++){
    double _x;double _y;
    StatError->GetPoint(i,_x,_y);
    double e1 = StatError->GetErrorYlow(i);
    double e2 = StatError->GetErrorYhigh(i);
    double e3 = SystError->GetErrorYlow(i);
    double e4 = SystError->GetErrorYhigh(i);
    cout << "Run12 data " <<  _x << " " << _y << " " << e1 << " " << e2 << " " << e3 << " " << e4 << endl;
    double t1 = yP[i];
    double t2 = dyP[i];
    double t3 = dyPSL[i];
    double t4 = dyPSL[i];
    double ny = (t1/t2/t2 + _y/e1/e1) / (1/t2/t2 + 1/e1/e1);
    
    
    yy2[i] = ny;
    ee12[i] = 1/sqrt(1/t2/t2 + 1/e1/e1);
    ee2l2[i] = (t3/t2/t2 + e3/e1/e1) / (1/t2/t2 + 1/e1/e1);
    ee2h2[i] = (t4/t2/t2 + e4/e1/e1) / (1/t2/t2 + 1/e1/e1);
  }
  
  double xx2[6] ={3,4,5,6,7,8};
  double xxe2[6] =   {0,0,0,0,0,0};
  double xxe22[6] =   {0.2,0.2,0.2,0.2,0.2,0.2};
  TGraphAsymmErrors *gpp = new TGraphAsymmErrors(6,xP,yy2,dxPS,dxPS,ee12,ee12);
  TGraphAsymmErrors *gpp_sys = new TGraphAsymmErrors(6,xP,yy2,dxPS,dxPS,ee2l2,ee2h2);
  
  double yy3[6] = {0.278118,0.375476,0.516407,0.582562,0.592705,0.559055};
  double ee13[6] = {0.0490242,0.0514371,0.0464319,0.0439163,0.0541009,0.0814724};
  double ee1l3[6] = {0.0191004,0.0260739,0.0199185,0.0281,0.0313544,0.0566835};
  double ee1h3[6] = {0.0191004,0.0260739,0.0199185,0.0281,0.0313544,0.0566835};

  TGraphAsymmErrors *Mattgpp = new TGraphAsymmErrors(6,xx2,yy3,xxe2,xxe2,ee13,ee13);
  TGraphAsymmErrors *Mattgpp_sys = new TGraphAsymmErrors(6,xx2,yy3,xxe22,xxe22,ee1l3,ee1h3);
  
  TLegend* leg2 = new TLegend(0.15,0.7,0.52,0.88);
  //  leg2->SetTextSize(.05);
  leg2->SetFillStyle (0);
  leg2->SetFillColor (0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(grP,"STAR Run 6","pe");
  leg2->AddEntry(StatError,"STAR Run 12(Yingjie)","pe");
  leg2->AddEntry(gpp,"Combined","pe");
  
  grPS->SetFillStyle(0);
  grPS->SetLineWidth(2);
  grP->SetMarkerStyle(24);
  grP->SetMarkerSize(1.4);

  StatError->SetMarkerStyle(20);
  StatError->SetMarkerSize(1.4);
  StatError->SetLineColor(kBlue);
  StatError->SetMarkerColor(kBlue);
  SystError->SetFillStyle(0);
  SystError->SetLineWidth(2);
  SystError->SetLineColor(kBlue);
  SystError->SetMarkerColor(kBlue);
  
  gpp->SetMarkerStyle(21);
  gpp->SetMarkerSize(1.4);
  gpp->SetLineColor(kGreen+2);
  gpp->SetMarkerColor(kGreen+2);
  gpp_sys->SetFillStyle(0);
  gpp_sys->SetLineWidth(2);
  gpp_sys->SetLineColor(kGreen+2);
  gpp_sys->SetMarkerColor(kGreen+2);
  
  
  Mattgpp->SetMarkerStyle(22);
  Mattgpp->SetMarkerSize(1.4);
  Mattgpp->SetLineColor(kRed+2);
  Mattgpp->SetMarkerColor(kRed+2);
  Mattgpp_sys->SetFillStyle(0);
  Mattgpp_sys->SetLineWidth(2);
  Mattgpp_sys->SetLineColor(kRed+2);
  Mattgpp_sys->SetMarkerColor(kRed+2);
  
  TCanvas *c3 = new TCanvas("c3","Weighted Ave");
  grPS->SetTitle("");
  grPS->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  grPS->GetYaxis()->SetTitle("B#rightarrowNPE / Inclusive#rightarrowNPE");
  grPS->GetXaxis()->SetTitleSize(0.06);
  grPS->GetYaxis()->SetTitleSize(0.06);
  grPS->GetXaxis()->SetTitleOffset(0.95);
  grPS->GetYaxis()->SetTitleOffset(0.8);
  grPS->GetXaxis()->SetLabelSize(0.06);
  grPS->GetYaxis()->SetLabelSize(0.06);
  grPS->GetXaxis()->SetLimits(0,12);
  grPS->GetYaxis()->SetRangeUser(-0.1,1.2);
  grPS->Draw("a pe2");
  grP->Draw("same pe");
  StatError->Draw("same pe");
  SystError->Draw("same pe2");
  gpp->Draw("same pe");
  gpp_sys->Draw("same pe2");
  Mattgpp->Draw("same pe");
  Mattgpp_sys->Draw("same pe2");
  leg2->Draw("same");
  c3->SaveAs("drawCombine.pdf");
  
  
}
