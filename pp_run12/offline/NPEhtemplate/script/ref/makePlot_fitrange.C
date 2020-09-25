void drawtext();
void makePlot_fitrange(const char* FileName="fitrange"){
  
//  gROOT->ProcessLine(".x ~/myStyle.C");
//  gROOT->SetBatch(kTRUE);
  //auto fyj = new TFile("../../offYJ/fit/tmpfit/Fit_B_fraction.root", "READ");
  //auto fyj = new TFile("../../offYJ/fit/tmpfit_sumw/Fit_B_fraction.root", "READ");
//  gStyle->SetOptFit(1111);

  auto fyjd = new TFile(Form("FFOutput_tmp/sysChange_fitrange_May5_FIT.root", FileName),"READ"); // gpt
  auto hd = (TGraphAsymmErrors *)fyjd->Get("sys");
  auto hnorm = (TGraphAsymmErrors *)fyjd->Get("normsmall");
  
  auto fyj = new TFile(Form("FFOutput_tmp/sysChange_fitrangeL_May5_FIT.root", FileName), "READ");
  auto hbyj = (TGraphAsymmErrors *)fyj->Get("sys");
  auto hdef = (TGraphErrors*)fyj->Get("normsmall");

  //========================================================================
  
  char name[1200];
  sprintf(name,"FFOutput/gpt/sysChange_fitNormPlus_Mar3_1_FIT.root");
  auto fyjUp = new TFile(name,"READ");
  auto hbyjUp = (TGraphAsymmErrors *) fyjUp->Get("sys");
  auto hdefUp = (TGraphErrors*)fyjUp->Get("sysChange");

  sprintf(name,"FFOutput/gpt/sysChange_fitNormMinus_Mar3_1_FIT.root");
  auto fyjDw = new TFile(name,"READ");
  auto hbyjDw = (TGraphAsymmErrors *) fyjDw->Get("sys");
  auto hdefDw = (TGraphErrors*)fyjDw->Get("sysChange");

  
  //  sprintf(name,"../");
  
//  gStyle->SetOptStat(0);
  float ypT[9], yRb[9], ydyU[9], ydyD[9], ydysU[9], ydysD[9]; // from yj
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
    pT[i] = x1-0.3;
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
    ypT[i] = pT[i]-0.3;
    double ty, tx;
    hd->GetPoint(i, tx, ty);
    yRb[i] = ty;
    ydysU[i] = dysU[i];
    ydysD[i] = dysD[i];
    ydyD[i] = hd->GetErrorYlow(i);
    ydyU[i] = hd->GetErrorYhigh(i);
    
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
  
  TGraphAsymmErrors* hdf = new TGraphAsymmErrors(9,ypT,yRb,dx,dx,ydyD,ydyU); // zyj
  //  TGraphAsymmErrors* hbyjDw = new TGraphAsymmErrors(9,ypT,yRb,dx2,dx2,ydysD,ydysU);
  
  TGraphAsymmErrors* stat = new TGraphAsymmErrors(9,pT,Rb,dx,dx,dyD,dyU);
  TGraphAsymmErrors* syst = new TGraphAsymmErrors(9,pT,Rb,dx2,dx2,dysD,dysU);
  TGraphErrors* stat6 = new TGraphErrors(7,pT6,Rb6,dx,dy6);
  TGraphAsymmErrors* syst6 = new TGraphAsymmErrors(7,pT6,Rb6,dx2,dx2,dysD6,dysU6);
  TLegend* leg = new TLegend(0.18,0.72,0.52,0.89);

  Double_t Graph0_fx1201[99] = {0.121,
    0.202,
    0.303,
    0.404,
    0.5051,
    0.6061,
    0.7071,
    0.8081,
    0.9091,
    1.0101,
    1.1111,
    1.2121,
    1.3131,
    1.4141,
    1.5151,
    1.6162,
    1.7172,
    1.8182,
    1.9192,
    2.0202,
    2.1212,
    2.2222,
    2.3232,
    2.4242,
    2.5252,
    2.6263,
    2.7273,
    2.8283,
    2.9293,
    3.0303,
    3.1313,
    3.2323,
    3.3333,
    3.4343,
    3.5354,
    3.6364,
    3.7374,
    3.8384,
    3.928278,
    4.0404,
    4.1414,
    4.2424,
    4.3434,
    4.4444,
    4.5454,
    4.6465,
    4.7475,
    4.8485,
    4.9495,
    5.0505,
    5.1515,
    5.2525,
    5.3535,
    5.4546,
    5.5556,
    5.6566,
    5.7576,
    5.8586,
    5.9596,
    6.0606,
    6.1616,
    6.2626,
    6.3636,
    6.4646,
    6.5657,
    6.6667,
    6.7677,
    6.8687,
    6.9697,
    7.0707,
    7.1717,
    7.2727,
    7.3737,
    7.4748,
    7.5758,
    7.6768,
    7.7778,
    7.8788,
    7.9798,
    8.0808,
    8.1818,
    8.2828,
    8.3838,
    8.4848,
    8.5859,
    8.6869,
    8.7879,
    8.8889,
    8.9899,
    9.0909,
    9.1919,
    9.2929,
    9.3939,
    9.4949,
    9.596,
    9.697,
    9.798,
    9.899,
    10};
  Double_t Graph0_fy1201[99] = {0.0002157487,
    0.0006701205,
    0.001142921,
    0.001860684,
    0.002967843,
    0.00464543,
    0.007151315,
    0.01081023,
    0.01583555,
    0.02250377,
    0.03105067,
    0.04170598,
    0.05436157,
    0.06906901,
    0.0856345,
    0.103641,
    0.123014,
    0.143373,
    0.1643714,
    0.1855542,
    0.2066991,
    0.227445,
    0.2478147,
    0.2675238,
    0.2863677,
    0.3044559,
    0.3217666,
    0.3380942,
    0.3533731,
    0.3678674,
    0.3816963,
    0.3944309,
    0.4066002,
    0.417999,
    0.4287498,
    0.4389604,
    0.4486786,
    0.4576232,
    0.468439,
    0.47433,
    0.4822119,
    0.489415,
    0.4966418,
    0.5032611,
    0.5096177,
    0.5157564,
    0.5215858,
    0.5272161,
    0.5327155,
    0.5378175,
    0.5429145,
    0.5477484,
    0.5524398,
    0.5569227,
    0.5613725,
    0.5655629,
    0.5697577,
    0.5736638,
    0.5775213,
    0.5814537,
    0.5850663,
    0.5887076,
    0.592345,
    0.5956383,
    0.5990272,
    0.6023273,
    0.6055186,
    0.6086593,
    0.6116868,
    0.614716,
    0.6176296,
    0.6204948,
    0.6234068,
    0.6261045,
    0.6288355,
    0.6315031,
    0.6340331,
    0.6365819,
    0.6390586,
    0.6415495,
    0.6440217,
    0.6462751,
    0.6487198,
    0.6508495,
    0.6532281,
    0.655332,
    0.657531,
    0.6596438,
    0.6617635,
    0.6637141,
    0.6657618,
    0.6677515,
    0.6696993,
    0.6716243,
    0.6735384,
    0.6753587,
    0.6771645,
    0.6790332,
    0.680747};
  TGraph *FONLL[3];
  FONLL[0] = new TGraph("FONLL_BAND_UP.dat");
  FONLL[1] = new TGraph("FONLL_BAND_DW.dat");
  FONLL[2] = new TGraph(99, Graph0_fx1201, Graph0_fy1201);
  //FONLL[2]->SetLineStyle(2);
  FONLL[0]->SetLineStyle(2);
  FONLL[1]->SetLineStyle(2);
  
  TCanvas* c1 = new TCanvas("c1","test");
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
  
  syst->GetYaxis()->SetRangeUser(-0.1,1.2);
  syst->GetXaxis()->SetRangeUser(0,12);
  
  // zyj
  hbyjDw->SetMarkerStyle(20+4);
  hbyjDw->SetLineColor(kGreen);
  hbyjDw->SetMarkerColor(kGreen);
  hbyjDw->SetFillStyle(0);
  hbyjDw->SetMarkerSize(1.5);

//  hbyjDw->SetLineWidth(2);
  
  hbyjUp->SetMarkerStyle(20+4);
//  hbyjUp->SetLineWidth(2);
  hbyjUp->SetMarkerSize(1.5);
  hbyjUp->SetMarkerColor(kMagenta);
  hbyjUp->SetLineColor(kMagenta);
  
  
  stat->GetXaxis()->SetLimits(0, 12);
  syst->GetXaxis()->SetLimits(0, 12);
  syst6->GetXaxis()->SetLimits(0, 12);
  stat6->GetXaxis()->SetLimits(0, 12);
  FONLL[0]->GetXaxis()->SetLimits(0, 12);
  FONLL[1]->GetXaxis()->SetLimits(0, 12);
  FONLL[2]->GetXaxis()->SetLimits(0, 12);
  
  
  hbyj->GetXaxis()->SetRangeUser(0,12);
  hbyj->GetYaxis()->SetRangeUser(-0.1,1.2);
//  hbyj->SetLineWidth(2);
  hbyj->SetMarkerSize(1.5);
  hbyj->SetMarkerStyle(20);
  hbyj->SetMarkerColor(kBlue);
  hbyj->SetLineColor(kBlue);
  
  hdf->GetXaxis()->SetRangeUser(0,12);
  hdf->GetYaxis()->SetRangeUser(-0.1,1.2);
  //  hbyj->SetLineWidth(2);
  hdf->SetMarkerSize(1.5);
  hdf->SetMarkerStyle(20);
  hdf->SetMarkerColor(kBlack);
  hdf->SetLineColor(kBlack);
  

  TLine *ll = new TLine(0, 0, 12, 0);
  syst->SetTitle(" ");
  syst->Draw("ape2");
  stat->Draw("same pe");
  
//  hbyjDw->Draw("same pe");
//  hbyjUp->Draw("same pe");
  hbyj->Draw("same pe");
  hdf->Draw("same pe");
  
  FONLL[0]->Draw("same");
  FONLL[1]->Draw("same");
  FONLL[2]->Draw("same");
  
  syst6->SetLineColor(kBlack);
  syst6->SetMarkerColor(kBlack);
  syst6->SetFillStyle(0);
  syst6->SetLineWidth(2);
  stat6->SetLineWidth(2);
  stat6->SetMarkerStyle(29);
  stat6->SetMarkerSize(1.8);
  stat6->SetMarkerColor(kBlack);
  stat6->SetLineColor(kBlack);
//  syst6->Draw("same pe2");
//  stat6->Draw("same pe");
  
  leg->SetBorderSize(0);
  leg->AddEntry(stat,"Run 12 p+p 200 GeV","pe");
//  leg->AddEntry(stat6,"Run 5/6 p+p 200 GeV","pe");
  leg->AddEntry(FONLL[2],"FONLL","l");
  leg->AddEntry(hdf,"gpt(2para. fit)","pe");
//  leg->AddEntry(hbyjUp,"Norm.(central+err)","pe");
  leg->AddEntry(hbyj,"ppt(2para. fit)","pe");
//  leg->AddEntry(hbyjDw,"Norm.(central-err)","pe");
  //leg->AddEntry(hbyjUp,"YJ","pe");
  leg->Draw("same");
  ll->Draw("same");
  
  
  //c1->SaveAs("final_bf_afterSym_v2.pdf");
  
  TLegend* leg2 = new TLegend(0.24,0.72,0.58,0.89);
  TLine *ll2 = new TLine(2, 0, 15, 0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(hbyjUp,"Norm.(central+err)","pe");
  leg2->AddEntry(hbyj,"Norm.(central)","pe");
  leg2->AddEntry(hbyjDw,"Norm.(central-err)","pe");

  auto csys = new TCanvas("csys", "");
  csys->cd();
  hdef->SetLineColor(kBlue);
  hdef->SetMarkerColor(kBlue);
  hdefDw->SetLineColor(kGreen);
  hdefDw->SetMarkerColor(kGreen);
  hdefUp->SetLineColor(kMagenta);
  hdefUp->SetMarkerColor(kMagenta);
  hdef->SetMarkerSize(1.5);
  hdefUp->SetMarkerSize(1.5);
  hdefDw->SetMarkerSize(1.5);

  
  hdef->Draw("");
  hdefUp->Draw("same lpe");
  hdefDw->Draw("same lpe");
  leg2->Draw("same pe");
  ll2->Draw("same");
  //==================================================
  auto cnorm = new TCanvas("cnorm", "");
  hnorm->Draw();
  TExec *ex = new TExec("ex","drawtext();");
  hnorm->GetListOfFunctions()->Add(ex);
  TF1* fitResA = hnorm->GetFunction("pol0");
  fitResA->Draw("same");
  //==================================================
  
  // Make PDF with output canvases
  TCanvas* temp = new TCanvas("temp","");
  sprintf(name, "bFraction_%s.pdf[", FileName);
  temp->Print(name);
//  temp = cnorm;
//  temp->Print(name);
  temp = c1;
  temp->Print(name);
//  temp = csys;
//  temp->Print(name);
  sprintf(name, "bFraction_%s.pdf]", FileName);
  temp->Print(name);
  //============================================================================================
  
  
  

  //  TFile* fOut = new TFile("run12NPEh_rBPoints.root","RECREATE");
  //  stat->Write("StatError");
  //  syst->Write("systError");
  //  stat6->Write("StatError_Run6");
  //  syst6->Write("systError_Run6");
  //  FONLL[0]->Write("FONLL_UPPER");
  //  FONLL[1]->Write("FONLL_LOWER");
  //  fOut->Close();
}

void drawtext()
{
  Int_t i,n;
  Double_t x,y;
  TLatex l;

  l.SetTextSize(0.025);
  l.SetTextFont(42);
  l.SetTextAlign(21);
  l.SetTextColor(kBlue);

  TGraphAsymmErrors *g = (TGraphAsymmErrors*)gPad->GetListOfPrimitives()->FindObject("grA");
  n = g->GetN();

  for (i=0; i<n; i++) {
    g->GetPoint(i,x,y);
    auto yh = (Float_t)g->GetErrorYhigh(i);
    auto yl = (Float_t)g->GetErrorYlow(i);

//    l.PaintText(x,y+0.2,Form("(%4.3f+%4.3f-%4.3f)",y,yh,yl));
    l.PaintText(x,y+0.2,Form("%4.3f",y));

  }
}
