TGraphAsymmErrors *getPrelimnaryStat();
TGraphAsymmErrors *getPrelimnarySys();

void DrawsysStat(const char* FileName="result_allSys_10defaultd_stat_04"){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  const int numPtBins = 9;
  auto fyj = new TFile("FFOutput/sysChange_default_May5_FIT.root","READ");
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
    "FFOutput/sysChange_pileup_May5_FIT.root",
    "FFOutput/sysChange_purity_May5_FIT.root",
    "FFOutput/sysChange_rec_May5_FIT.root",
    "FFOutput/sysChange_gpt04_May5_FIT.root",
    "FFOutput/sysChange_masscut_May5_FIT.root",
    "FFOutput/sysChange_nsigmae_May5_FIT.root",
    "FFOutput/sysChange_poe_May5_FIT.root",
    "FFOutput/sysChange_trig_May5_FIT.root",
    "FFOutput/sysChange_fitrange_May5_FIT.root",
    "FFOutput/sysChange_pythia_May5_FIT.root",
    "FFOutput/sysChange_jpsi_May5_FIT.root"
  };
  
  TCanvas* fp[20];
  TLegend* leg[20];
  TPaveText* lbl[20];
  
  TString filename[20] = { "pileup", "purity", "rec", "gpt", "masscut", "nsigmae", "poe",  "trigEff", "fitrange", "pythia", "jpsi"};
  int nSys;
  double x[20][numPtBins],y[20][numPtBins];
  double sysP[numPtBins]={0.}, sysM[numPtBins]={0.}, pTSys[numPtBins]={0.}, dxSys[numPtBins]={0};
  double sysEP[numPtBins]={0.}, sysEM[numPtBins]={0.};
  //  auto newArray = new TGraphErrors[20];
  TGraphErrors *gr[20];
  int sysNum = 0;
  for(int i = 0; i < 20; i++)
  {
    fSys = new TFile(fileList[i]);
    if(!fSys->IsOpen())
      continue;
    sysNum++;
    
    cout << "Opened " << fileList[i] << endl;
    
    TGraphErrors* grTemp = (TGraphErrors*)fSys->Get("sysChange");
    gr[i] = (TGraphErrors*)grTemp->Clone(Form("sysChange_stat_%d", i));
    
    nSys = grTemp->GetN(); // Get plot array dimension
    for(int ii = 0; ii < nSys; ii++)
    {
      grTemp->GetPoint(ii,x[i][ii],y[i][ii]); // get point ii (from array), store in x,y
      pTSys[ii] = x[i][ii];
      //      y[i][ii] = abs(y[i][ii]/100.*Rb0[ii]); // for syschange
      sysEP[ii] = grTemp->GetErrorYhigh(ii);;
      sysEM[ii] = grTemp->GetErrorYlow(ii);
      //       cout << "pt: " << x[i][ii] << " %: " << y[i][ii]<< " %: "<<sysEP[ii] << " %: " << sysEM[ii]<< endl;
      if(i<3){
        if(y[i][ii] > -50 && y[i][ii] < 50){
          sysP[ii] += y[i][ii]*y[i][ii];
          sysM[ii] += y[i][ii]*y[i][ii];
          cout << "pT: " << pTSys[ii] << " Sys%(+/-): " << sysP[ii] << " / " << sysM[ii] << endl;
        }
      }
      else {
        if(y[i][ii] > -50 && y[i][ii] < 50) // Add up the squares of all positive contrib in each pt
        {
          if(y[i][ii]>sysEP[ii] && y[i][ii]>sysEM[ii]){
            //            cout<<y[i][ii]<<"  "<<sysEP[ii]<<"  "<<sysEM[ii]<<"xxxx";
            sysP[ii] += (y[i][ii]*y[i][ii]-sysEP[ii]*sysEP[ii]);
            sysM[ii] += (y[i][ii]*y[i][ii]-sysEM[ii]*sysEM[ii]);
          }
          else {
            sysP[ii] +=0;
            sysM[ii] +=0;
          }
          cout << "pT: " << pTSys[ii] << " Sys%(+/-): " << sysP[ii] << " / " << sysM[ii] << endl;        }
      }
    }
    fSys->Close();
  }
  
  for(int ii = 0; ii < nSys; ii++) // After all runs, loop through pT, to square root
  {
    sysP[ii] = sqrt(sysP[ii]); // sqrt(x*x + y*y + ...)*Rb
    sysM[ii] = sqrt(sysM[ii]); // sqrt(x*x + y*y + ...)*Rb
    dxSys[ii] = 0.15;
    cout << "pT: " << pTSys[ii] << " Sys%(+/-): " << sysP[ii] << " / " << sysM[ii] << endl;
  }
  
  //  TLegend* leg = new TLegend(.5,0.8,0.93,0.89);
  //  leg->SetFillStyle (0);
  //  leg->SetFillColor (0);
  //  leg->SetBorderSize(0);
  //==================================================
  // draw all sys source percent
  
  //  TCanvas* fp = new TCanvas("fp","Front Page");
  //  fp->cd();
  //  gPad->SetBottomMargin(0.15);
  //  gPad->SetLeftMargin(0.12);
  //  gr[0]->SetTitle(" ");
  //  gr[0]->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  //  gr[0]->GetYaxis()->SetTitle("Difference to defalt");
  //  gr[0]->GetXaxis()->SetTitleSize(0.06);
  //  gr[0]->GetYaxis()->SetTitleSize(0.06);
  //  gr[0]->GetXaxis()->SetTitleOffset(0.95);
  //  gr[0]->GetYaxis()->SetTitleOffset(0.77);
  //  gr[0]->GetXaxis()->SetLabelSize(0.05);
  //  gr[0]->GetYaxis()->SetLabelSize(0.05);
  //  gr[0]->GetXaxis()->SetLimits(2,9.8);
  //  gr[0]->GetYaxis()->SetRangeUser(-0.3,0.3);
  //  gr[0]->SetMarkerStyle(20);
  //  gr[0]->SetMarkerSize(1.);
  //
  //  gr[0]->SetLineColor(kRed);
  //  gr[0]->SetMarkerColor(kRed);
  
  //  leg->AddEntry(gr[0],filename[0],"p");
  
  //  gr[0]->Draw("AP");
  char textLabel[100];
  char text2Label[100];
  
  lbl[0] = new TPaveText(.17,.3,.35,.4,Form("NB NDC%i",sysNum));
  sprintf(textLabel,"central value: |r_{B}-r_{B}^{sys}|");
  lbl[0]->AddText(textLabel);
  lbl[0]->SetFillColor(kWhite);
  lbl[1] = new TPaveText(.17,.2,.40,.3,Form("NB NDC%i",sysNum));
  sprintf(textLabel,"error: #sqrt{|stat(r_{B})^{2} - stat(r_{B}^{sys})^{2}|}");
  lbl[1]->AddText(textLabel);
  lbl[1]->SetFillColor(kWhite);
  
  TLine *llu = new TLine(2, 0, 9.8, 0);
  for(int i = 0; i < sysNum; i++){
    
    
    //    sprintf(text2Label,"stat(r_{B})-stat(r_{B}^{sys})");
    //    lbl[ptbin]->AddText(text2Label);
    
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
    gr[i]->GetXaxis()->SetLimits(2,9.8);
    //    gr[i]->GetYaxis()->SetRangeUser(-0.3,0.3);
    gr[i]->GetYaxis()->SetRangeUser(-100,100);
    
    //    gr[i]->SetMarkerStyle(20);
    //    gr[i]->SetMarkerSize(1.);
    
    gr[i]->SetLineColor(i);
    gr[i]->SetMarkerColor(i);
    if(i==5){gr[i]->SetMarkerColor(kGreen+2);gr[i]->SetLineColor(kGreen+2);}
    if(i==2){gr[i]->SetMarkerColor(kRed+1);gr[i]->SetLineColor(kRed+1);}
    if(i==7){gr[i]->SetMarkerColor(46);gr[i]->SetLineColor(46);}
    if(i==0){gr[i]->SetMarkerColor(kRed);gr[i]->SetLineColor(kRed);}
    if(i==10){gr[i]->SetMarkerColor(kGreen+2);gr[i]->SetLineColor(kGreen+2);}
    
    
    //    gr[i]->SetMarkerStyle(i+20);
    gr[i]->SetMarkerSize(1.);
    leg[i]->AddEntry(gr[i],filename[i],"p");
    gr[i]->Draw("ap");
    leg[i]->Draw("same");
    llu->SetLineStyle(2);
    llu->Draw("same");
    lbl[0]->Draw("same");
    lbl[1]->Draw("same");
    
  }
  //  leg->SetNColumns(4);
  //  leg->Draw("same");
  TLine *ll = new TLine(2, 10, 9.8, 10);
  TLine *lln = new TLine(2, -10, 9.8, -10);
  
  ll->SetLineStyle(2);
  lln->SetLineStyle(2);
  
  ll->SetLineColor(kBlue);
  lln->SetLineColor(kBlue);
  //  ll->Draw("same");
  //  lln->Draw("same");
  //  fp->SaveAs(Form("Plots/sys_percentage_%s.pdf", FileName));
  // Place canvases in order
  char name[1000];
  TCanvas* temp = new TCanvas();
  sprintf(name, "Plots/sysChange_%s_stat.pdf[", FileName);
  temp->Print(name);
  sprintf(name, "Plots/sysChange_%s_stat.pdf", FileName);
  for(int i = 0; i < sysNum; i++){
    temp=fp[i];
    temp->Print(name);
  }
  sprintf(name, "Plots/sysChange_%s_stat.pdf]", FileName);
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
  
  //  TGraphAsymmErrors* grSys = new TGraphAsymmErrors(nSys,pTSys,Rb0,dxSys,dxSys,sysP,sysP);
  TGraphAsymmErrors* grSys = new TGraphAsymmErrors(nSys-2,pTSys,Rb0,dxSys,dxSys,sysM,sysP);
  
  grSys->SetFillColor(kBlue);
  grSys->SetFillStyle(1);
  grSys->SetLineColor(kBlue);
  grSys->SetLineWidth(2);
  grSys->SetMarkerColor(kBlue);
  grSys->SetMarkerStyle(20);
  grSys->SetMarkerSize(1.5);
  
  TLegend* leg2 = new TLegend(0.15,0.7,0.52,0.88);
  //  leg2->SetTextSize(.05);
  leg2->SetFillStyle (0);
  leg2->SetFillColor (0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(grP,"STAR Run 6","pe");
  leg2->AddEntry(pstat,"STAR Run 12(Prelimary)","pe");
  leg2->AddEntry(gr0,"STAR Run 12(Yingjie)","pe");
  
  gr0->Draw("ape");
  grSys->Draw("same pe2");
  grP->Draw("same pe");
  grPS->Draw("same pe2");
  pstat->Draw("same pe");
  psyst->Draw("same pe2");
  leg2->Draw("same");
  
  fpp->SaveAs(Form("Plots/%s.pdf", FileName));
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
  float dx2[9] = {0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15};
  float x1, x2, x3, x4, x5, x6;
  ifstream infile("plotPoints.txt");
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
    i++;
  }
  TGraphAsymmErrors* pstat = new TGraphAsymmErrors(7,pT,Rb,dx,dx,dyD,dyU);
  return pstat;
  
}
TGraphAsymmErrors *getPrelimnarySys(){
  
  float pT[9], Rb[9], dyU[9], dyD[9], dysU[9], dysD[9];
  float dx[9] = {0.};
  float dx2[9] = {0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15};
  float x1, x2, x3, x4, x5, x6;
  ifstream infile("plotPoints.txt");
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
    i++;
  }
  TGraphAsymmErrors* psyst = new TGraphAsymmErrors(7,pT,Rb,dx2,dx2,dysD,dysU);
  //  psyst->Draw();
  return psyst;
}
