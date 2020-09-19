TGraphAsymmErrors *getPrelimnaryStat();
TGraphAsymmErrors *getPrelimnarySys();
TGraph *getFonll();

void DrawSysStat(const char* FileName="Sep16_09172020"){
  gROOT->ProcessLine(".x ~/myStyle.C");
  const char* fname="TotalSys"; //totalSys
  
  const int numPtBins = 9;
  auto fyj = new TFile("FFOutput/sysChange_default_Sep16_FIT.root","READ");
  auto gr0 = (TGraphAsymmErrors *)fyj->Get("HT0");
  
  Double_t Rb0[numPtBins];
  Double_t p00[numPtBins],p01[numPtBins], p10[numPtBins], p11[numPtBins];
  Double_t dx[numPtBins] = {0.};
  
  for(int ii = 0; ii < numPtBins; ii++)
  {
    
    gr0->GetPoint(ii,p00[ii],p01[ii]); // get point ii (from array), store in x,y
    p10[ii] = gr0->GetErrorYlow(ii);
    p11[ii] = gr0->GetErrorYhigh(ii);
    Rb0[ii] = p01[ii];
  }
  
  gr0 = new TGraphAsymmErrors(7,p00,p01,dx,dx,p10,p11); // zyj
  TFile* fSys;
  TString fileList[20] = {
    "FFOutput/sysChange_pileup_Sep16_FIT.root",
    "FFOutput/sysChange_purity_Sep16_FIT.root",
    "FFOutput/sysChange_rec_Sep16_FIT.root",
    "FFOutput/sysChange_gpt_Sep16_FIT.root",
    "FFOutput/sysChange_masscut_Sep16_FIT.root",
    "FFOutput/sysChange_nsigmae_Sep16_FIT.root",
    "FFOutput/sysChange_poe_Sep16_FIT.root",
    "FFOutput/sysChange_trig_Sep16_FIT.root",
    "FFOutput/sysChange_fitrange_Sep16_FIT.root",
    "FFOutput/sysChange_pythia_Sep16_FIT.root",
    //    "FFOutput/sysChange_jpsi_Sep16_FIT.root"
  };
  
  TCanvas* fp[20];
  TLegend* leg[20];
  TPaveText* lbl[20];
  
  TString filename[20] = { "pileup", "purity", "rec", "gpt", "masscut", "nsigmae", "poe",  "trigEff", "fitrange", "pythia"};//, "jpsi"};
  int nSys;
  double x[20][numPtBins],y[20][numPtBins];
  double sysP[numPtBins]={0.}, sysM[numPtBins]={0.}, pTSys[numPtBins]={0.}, dxSys[numPtBins]={0};
  double sysEP[numPtBins]={0.}, sysEM[numPtBins]={0.};
  //  auto newArray = new TGraphErrors[20];
  TGraphErrors *grc[20];
  TGraphErrors *gr[20];
  
  int sysNum = 0;
  for(int i = 0; i < 20; i++)
  {
    fSys = new TFile(fileList[i]);
    if(!fSys->IsOpen())
      continue;
    sysNum++;
    
    cout << "Opened " << fileList[i]<< endl;
    
    TGraphErrors* grcTemp = (TGraphErrors*)fSys->Get("sysChange");
    grc[i] = (TGraphErrors*)grcTemp->Clone(Form("sysChange_%d", i));
    
    TGraphErrors* grTemp = (TGraphErrors*)fSys->Get("sysChange_stat");
    gr[i] = (TGraphErrors*)grTemp->Clone(Form("sysChange_stat_%d", i));
    nSys = grTemp->GetN(); // Get plot array dimension
    for(int ii = 0; ii < nSys; ii++)
    {
      grTemp->GetPoint(ii,x[i][ii],y[i][ii]); // get point ii (from array), store in x,y
      pTSys[ii] = x[i][ii];
      sysEP[ii] = grTemp->GetErrorYhigh(ii);;
      sysEM[ii] = grTemp->GetErrorYlow(ii);
      
      if(i<3){
        if(y[i][ii] > -0.5 && y[i][ii] < 0.5){
          sysP[ii] += y[i][ii]*y[i][ii];
          sysM[ii] += y[i][ii]*y[i][ii];
          cout << "pT: " << pTSys[ii] << " Sys%(+/-): %" << TMath::Sqrt(y[i][ii]*y[i][ii])*100<< endl;
        }
        grc[i]->SetPoint(ii, pTSys[ii], TMath::Sqrt(y[i][ii]*y[i][ii]));
      }
      else {
        if(y[i][ii] > -0.5 && y[i][ii] < 0.5) // Add up the squares of all positive contrib in each pt
        {
          if(y[i][ii]>sysEP[ii] && y[i][ii]>sysEM[ii]){
            //            cout<<y[i][ii]<<"  "<<sysEP[ii]<<"  "<<sysEM[ii]<<"xxxx";
            sysP[ii] += (y[i][ii]*y[i][ii]-sysEP[ii]*sysEP[ii]);
            sysM[ii] += (y[i][ii]*y[i][ii]-sysEM[ii]*sysEM[ii]);
            cout << "pT: " << pTSys[ii] << " Sys%(+/-): %" << TMath::Sqrt(y[i][ii]*y[i][ii]-sysEP[ii]*sysEP[ii])*100 << " / %" << TMath::Sqrt(y[i][ii]*y[i][ii]-sysEM[ii]*sysEM[ii])*100 << endl;
            grc[i]->SetPoint(ii, pTSys[ii], TMath::Sqrt(y[i][ii]*y[i][ii]-sysEP[ii]*sysEP[ii]));
          }
          else {
            sysP[ii] +=0;
            sysM[ii] +=0;
            grc[i]->SetPoint(ii, pTSys[ii], 0.);
          }
        }
      }
    }
    cout<<"end of file ======================================"<<endl;
    fSys->Close();
  }
  
  cout<<" total sysmatics: ============================================"<<endl;
  for(int ii = 0; ii < nSys; ii++) // After all runs, loop through pT, to square root
  {
    sysP[ii] = sqrt(sysP[ii]); // sqrt(x*x + y*y + ...)*Rb
    sysM[ii] = sqrt(sysM[ii]); // sqrt(x*x + y*y + ...)*Rb
    if((sysP[ii]+Rb0[ii])>1.)sysP[ii] = 1. -Rb0[ii];
    dxSys[ii] = 0.15;
    cout << "pT: " << pTSys[ii] << " Sys%(+/-): %" << sysP[ii]*100 << " / %" << sysM[ii]*100 << endl;
  }
  
  
  char textLabel[100];
  char text2Label[100];
  
  lbl[0] = new TPaveText(.17,.8,.35,.9,Form("NB NDC%i",sysNum));
  sprintf(textLabel,"central value: |r_{B}-r_{B}^{sys}|");
  lbl[0]->AddText(textLabel);
  lbl[0]->SetFillColor(kWhite);
  lbl[1] = new TPaveText(.17,.7,.40,.8,Form("NB NDC%i",sysNum));
  sprintf(textLabel,"error: #sqrt{|stat(r_{B})^{2} - stat(r_{B}^{sys})^{2}|}");
  lbl[1]->AddText(textLabel);
  lbl[1]->SetFillColor(kWhite);
  
  TLine *llu = new TLine(0, 0, 12, 0);
  
  for(int i = 0; i < sysNum; i++){
    
    leg[i] = new TLegend(.5,0.8,0.93,0.89);
    leg[i]->SetFillStyle (0);
    leg[i]->SetFillColor (0);
    leg[i]->SetBorderSize(0);
    fp[i] = new TCanvas(Form("fp_%d", i),Form("fp_%d", i));
    fp[i]->cd();
    gPad->SetBottomMargin(0.15);
    gPad->SetLeftMargin(0.12);
    gr[i]->SetTitle(" ");
    gr[i]->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
    gr[i]->GetYaxis()->SetTitle("Difference to defalt");
    gr[i]->GetXaxis()->SetTitleSize(0.06);
    gr[i]->GetYaxis()->SetTitleSize(0.06);
    gr[i]->GetXaxis()->SetTitleOffset(0.95);
    gr[i]->GetYaxis()->SetTitleOffset(0.77);
    gr[i]->GetXaxis()->SetLabelSize(0.05);
    gr[i]->GetYaxis()->SetLabelSize(0.05);
    //    gr[i]->GetXaxis()->SetLimits(2,9.8);
    gr[i]->GetXaxis()->SetLimits(0, 12);
    gr[i]->GetYaxis()->SetRangeUser(-0.1,0.4);
    if(i >7)gr[i]->GetYaxis()->SetRangeUser(-0.1,0.8);
    
    
    gr[i]->SetLineColor(i);
    gr[i]->SetMarkerColor(i);
    if(i==5){gr[i]->SetMarkerColor(kGreen+2);gr[i]->SetLineColor(kGreen+2);}
    if(i==2){gr[i]->SetMarkerColor(kRed+1);gr[i]->SetLineColor(kRed+1);}
    if(i==7){gr[i]->SetMarkerColor(46);gr[i]->SetLineColor(46);}
    if(i==0){gr[i]->SetMarkerColor(kRed);gr[i]->SetLineColor(kRed);}
    if(i==10){gr[i]->SetMarkerColor(kGreen+2);gr[i]->SetLineColor(kGreen+2);}
    
    
    gr[i]->SetMarkerStyle(i+20);
    gr[i]->SetMarkerSize(1.);
    leg[i]->AddEntry(gr[i],filename[i],"p");
    gr[i]->Draw("ap");
    leg[i]->Draw("same");
  }
  //============================================================================
  // sqrt(a^2-b^2)
  auto pchange = new TCanvas("pchange", "");
  pchange->cd();
  gPad->SetBottomMargin(0.15);
  gPad->SetLeftMargin(0.12);
  
  auto legc = new TLegend(.3,0.8,0.9,0.89);
//  auto legc = new TLegend(.3,0.8,0.6,0.84); // for preliminary
  legc->SetFillStyle (0);
  legc->SetFillColor (0);
  legc->SetBorderSize(0);
  
  grc[0]->SetTitle(" ");
  grc[0]->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
//  grc[0]->GetYaxis()->SetTitle("#it{r_{B}}-#it{r_{B}^{sys}}");
//  grc[0]->GetYaxis()->SetTitle("#sqrt{|#it{r_{B}} - #it{r_{B}^{sys}}|^{2}-|stat_{#it{r_{B}}}^{2} - stat_{#it{r_{B}^{sys}}}^{2}|}");
  grc[0]->GetYaxis()->SetTitle("Systematic error");

  grc[0]->GetXaxis()->SetTitleSize(0.06);
  grc[0]->GetYaxis()->SetTitleSize(0.06);
  grc[0]->GetXaxis()->SetTitleOffset(0.95);
  grc[0]->GetYaxis()->SetTitleOffset(0.77);
  grc[0]->GetXaxis()->SetLabelSize(0.05);
  grc[0]->GetYaxis()->SetLabelSize(0.05);
  grc[0]->SetLineColor(kRed);
  grc[0]->SetMarkerColor(kRed);
  grc[0]->GetXaxis()->SetLimits(0, 12);
  grc[0]->GetYaxis()->SetRangeUser(-0.01, 0.4);
//  grc[0]->GetYaxis()->SetRangeUser(-0.01, 0.2); //pre
  legc->AddEntry(grc[0],filename[0],"p");
  //grc[0]->GetYaxis()->SetRangeUser(-100, 100);
  
  grc[0]->GetYaxis()->SetNdivisions(505);
//  grc[0]->GetYaxis()->SetTitleOffset(0.9);
  grc[0]->Draw("ape");
  for(int i = 1; i < sysNum; i++){
    grc[i]->SetTitle(" ");
    grc[i]->SetLineColor(i);
    grc[i]->SetMarkerColor(i);
    if(i >7)grc[i]->GetYaxis()->SetRangeUser(-0.1,0.8);
    if(i==5){grc[i]->SetMarkerColor(kGreen+2);grc[i]->SetLineColor(kGreen+2);}
    if(i==2){grc[i]->SetMarkerColor(kRed+1);  grc[i]->SetLineColor(kRed+1);}
    if(i==7){grc[i]->SetMarkerColor(46);      grc[i]->SetLineColor(46);}
    if(i==0){grc[i]->SetMarkerColor(kRed);    grc[i]->SetLineColor(kRed);}
    if(i==10){grc[i]->SetMarkerColor(kGreen+2);grc[i]->SetLineColor(kGreen+2);}
    grc[i]->SetMarkerStyle(i+20);
    grc[i]->SetMarkerSize(1.);
    legc->AddEntry(grc[i],filename[i],"p");
    grc[i]->Draw("p same");
  }

  legc->SetNColumns(4);
  legc->Draw("same");
  pchange->SaveAs(Form("pic/allPercentChange_%s.pdf", FileName));
//  pchange->SaveAs(Form("pic/PrelimSys_%s.pdf", FileName));
  
  // Place canvases in order
  char name[1000];
  TCanvas* temp = new TCanvas();
  sprintf(name, "pic/sysChange_%s_stat.pdf[", FileName);
  temp->Print(name);
  sprintf(name, "pic/sysChange_%s_stat.pdf", FileName);
  for(int i = 0; i < sysNum; i++){
    temp=fp[i];
    temp->Print(name);
  }
  sprintf(name, "pic/sysChange_%s_stat.pdf]", FileName);
  temp->Print(name);
  //============================================================================
  TGraphAsymmErrors *pstat = getPrelimnaryStat();
  TGraphAsymmErrors *psyst = getPrelimnarySys();
  psyst->SetLineColor(kRed);
  psyst->SetMarkerColor(kRed);
  psyst->SetFillStyle(0);
  psyst->SetLineWidth(2);
  psyst->SetMarkerSize(1.5);
  pstat->SetLineWidth(2);
  pstat->SetMarkerStyle(20);
  pstat->SetMarkerSize(1.5);
  pstat->SetMarkerColor(kRed);
  pstat->SetLineColor(kRed);
  pstat->GetYaxis()->SetRangeUser(-0.2,1.2);
  pstat->GetXaxis()->SetRangeUser(0,12);
  
  psyst->GetYaxis()->SetRangeUser(-0.1,1.2);
  psyst->GetXaxis()->SetRangeUser(0,12);
  
  // Get Previous Analysis
  Int_t p=0;
  Float_t xP[100],yP[100],dyP[100],dyPSL[100],dyPSH[100],dxPS[100];
  ifstream fp1("/Users/zhouyingjie/Local/PWG/btoe/pp_run12/offline/plotforpaper/Run6Result.txt",ios::in);
  char line[1000];
  while (!fp1.eof()){
    fp1.getline(line,1000);
    sscanf(line,"%f %f %f %f %f",&xP[p],&yP[p],&dyP[p],&dyPSL[p],&dyPSH[p]);
    // printf("L: %f %f\n",xF[l],yF[l]);
    dyPSL[p] = yP[p]-dyPSL[p];   // convert from max/min of error bar to value of
    dyPSH[p] = dyPSH[p] - yP[p]; // error bar for plotting
    dxPS[p] = 0.15;
    xP[p] +=0.2;
    p++;
  }
  fp1.close();
  
  TGraphErrors *grP     = new TGraphErrors(p-1,xP,yP,0,dyP);
  TGraphAsymmErrors *grPS = new TGraphAsymmErrors(p-1,xP,yP,dxPS,dxPS,dyPSL,dyPSH);
  
  grP->SetMarkerSize(1.5);
  grP->SetMarkerStyle(29);
  grP->SetMarkerColor(kBlack);
  grP->SetLineColor(kBlack);
  
  grPS->SetMarkerColor(kBlack);
  grPS->SetLineColor(kBlack);
  grPS->SetLineWidth(2);
  grPS->SetFillColor(kBlack);
  grPS->SetFillStyle(1);
  grPS->SetMarkerStyle(29);
  grPS->SetMarkerSize(1.5);
  //============================================================================
  
  TCanvas* fpp = new TCanvas("fpp","sys");
  
  gr0->SetMarkerStyle(20);
  gr0->SetMarkerSize(1.5);
  gr0->SetLineColor(kBlue);
  gr0->SetMarkerColor(kBlue);
  gr0->SetTitle("");
  gr0->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  gr0->GetYaxis()->SetTitle("B#rightarrowNPE / Inclusive#rightarrowNPE");
  gr0->GetYaxis()->SetRangeUser(-0.1, 1.2);
  
  TGraphAsymmErrors* grSys = new TGraphAsymmErrors(nSys,pTSys,Rb0,dxSys,dxSys,sysM,sysP);
  
  grSys->SetFillColor(kBlue);
  grSys->SetFillStyle(1);
  grSys->SetLineColor(kBlue);
  grSys->SetLineWidth(2);
  grSys->SetMarkerColor(kBlue);
  grSys->SetMarkerStyle(20);
  grSys->SetMarkerSize(1.5);
  
  
  TGraph *FONLL[3];
  FONLL[0] = new TGraph("input/FONLL_BAND_UP.dat");
  FONLL[1] = new TGraph("input/FONLL_BAND_DW.dat");
  FONLL[2] = getFonll();
  FONLL[0]->SetLineStyle(2);
  FONLL[1]->SetLineStyle(2);
  FONLL[0]->GetXaxis()->SetLimits(2, 12);
  FONLL[1]->GetXaxis()->SetLimits(2, 12);
  FONLL[2]->GetXaxis()->SetLimits(2, 12);
  //============================================================
  TLegend* leg2 = new TLegend(0.15,0.7,0.52,0.88);
  //  leg2->SetTextSize(.05);
  leg2->SetFillStyle (0);
  leg2->SetFillColor (0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(grP,"STAR Run 6","pe");
  leg2->AddEntry(pstat,"STAR Run 12(Prelimary)","pe");
  leg2->AddEntry(gr0,"STAR Run 12(Yingjie)","pe");
  leg2->AddEntry(FONLL[2],"FONLL","l");
  
  TLine *ll = new TLine(0, 0, 12, 0);
  
  gr0->GetXaxis()->SetLimits(0, 12);
  gr0->Draw("ape");
  grSys->Draw("same pe2");
  
  grP->Draw("same pe"); // run6
  grPS->Draw("same pe2");
  
  pstat->Draw("same pe");
  psyst->Draw("same pe2");
  
  FONLL[0]->Draw("same");
  FONLL[1]->Draw("same");
  FONLL[2]->Draw("same");
  ll->Draw("same");
  
  leg2->Draw("same");
  
  fpp->SaveAs(Form("pic/%s_%s.pdf",fname, FileName));
  //  auto sf = new TFile("run12NPEh_rBPoints.root", "RECREATE");
  //  sf->cd();
  //  gr0->Write("StatError");
  //  grSys->Write("systError");
  //  sf->Close();
  return ;
}

//=====================================================
TGraphAsymmErrors *getPrelimnaryStat(){
  float pT[9], Rb[9], dyU[9], dyD[9], dysU[9], dysD[9];
  float dx[9] = {0.};
  float dx2[9] = {0.};
  float x1, x2, x3, x4, x5, x6;
  ifstream infile("input/plotPoints.txt");
  int i = 0;
  string line;
  cout << "Run 12 Points" << endl;
  while(getline(infile,line))
  {
    sscanf(line.c_str(),"%f %f %f %f %f %f",&x1, &x2, &x3, &x4, &x5, &x6);
    pT[i] = x1-0.3;
    Rb[i] = x2;
    dx2[i] = 0.15;
    dyU[i] = x3-x2;
    dyD[i] = x2-x4;
    dysU[i] = x5-x2;
    dysD[i] = x2-x6;
    i++;
  }
  TGraphAsymmErrors* pstat = new TGraphAsymmErrors(9,pT,Rb,dx,dx,dyD,dyU);
  return pstat;
  
}
TGraphAsymmErrors *getPrelimnarySys(){
  
  float pT[9], Rb[9], dyU[9], dyD[9], dysU[9], dysD[9];
  float dx[9] = {0.};
  float dx2[9]= {0.};
  float x1, x2, x3, x4, x5, x6;
  ifstream infile("input/plotPoints.txt");
  int i = 0;
  string line;
  cout << "Run 12 Points" << endl;
  while(getline(infile,line))
  {
    sscanf(line.c_str(),"%f %f %f %f %f %f",&x1, &x2, &x3, &x4, &x5, &x6);
    pT[i] = x1-0.3;
    Rb[i] = x2;
    dx2[i] = 0.15;
    dyU[i] = x3-x2;
    dyD[i] = x2-x4;
    dysU[i] = x5-x2;
    dysD[i] = x2-x6;
    i++;
  }
  TGraphAsymmErrors* psyst = new TGraphAsymmErrors(9,pT,Rb,dx2,dx2,dysD,dysU);
  //  psyst->Draw();
  return psyst;
}

TGraph *getFonll(){
  Double_t Graph0_fx1201[99] = {
    //     0.121,
    //     0.202,
    //     0.303,
    //     0.404,
    //     0.5051,
    //     0.6061,
    //     0.7071,
    //     0.8081,
    //     0.9091,
    //     1.0101,
    //     1.1111,
    //     1.2121,
    //     1.3131,
    //     1.4141,
    //     1.5151,
    //     1.6162,
    //     1.7172,
    //     1.8182,
    //     1.9192,
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
  Double_t Graph0_fy1201[99] = {
    //     0.0002157487,
    //     0.0006701205,
    //     0.001142921,
    //     0.001860684,
    //     0.002967843,
    //     0.00464543,
    //     0.007151315,
    //     0.01081023,
    //     0.01583555,
    //     0.02250377,
    //     0.03105067,
    //     0.04170598,
    //     0.05436157,
    //     0.06906901,
    //     0.0856345,
    //     0.103641,
    //     0.123014,
    //     0.143373,
    //     0.1643714,
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
  
  auto gFonll = new TGraph(80, Graph0_fx1201, Graph0_fy1201);
  
  return gFonll;
}
