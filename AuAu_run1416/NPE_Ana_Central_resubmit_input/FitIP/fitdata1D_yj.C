#include "prettycanvasAll.C"

using namespace RooFit;

void fitdata1D_yj(TH1F *data,TH1F *data_e,TH1F* data_emis,TH1F *data_pi,TH1F* data_D,TH1F* data_jpsi,TH1F* data_B,int daughter,int mag, int save,
//void fitdata1D(TH1F *data,TH1F *data_e,TH1F* data_emis,TH1F *data_pi, TH1F *data_2pi,TH1F *data_k,TH1F *data_p,TH1F* data_D,TH1F* data_jpsi,TH1F* data_B,int daughter,int mag, int save,
               char outputfile[],char datfile[],char datc[],char dir1[],char dir2[],char dir3[],char dir4[],char dir5[],char dir6[],
               int pt,int eta, int rs,float cutLow,float cutHigh,double ptLow ,double ptHigh,double eff_b, int pur_dir, int HT, double e_const)
{
  
  //return ;
  gSystem->Load("libRooFit.so");
  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
  char file_purity[50];
  sprintf(file_purity,"../FitPurity/%i/yields.dat",pur_dir);
  ifstream purData(file_purity);
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  
  TH1F *hp1 = new TH1F("hp1","",numPtBins,binning);
  if(purData.is_open()){
    while(!purData.eof()){
      char out[50];
      double y=0;
      double y_e=0;
      double pT=0;
      double p1 = 0;
      double eff=0;
      double a1 = 0;
      double a2=0;
      double a3=0;
      purData >> pT >> y >> y_e >> p1 >> eff >> a1 >> a2 >>a3;
      if(y<.0001)y=0;
      int a=y;
      int b=y_e;
      if(pT!=0){
        hp1->SetBinContent(pT,p1-0.15); // zyj purity
        hp1->SetBinError(pT,p1*b/a);
      }
    }
    
  } else {
    cout <<"Nope \n";
  }
  double re_binning[numPtBins]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,8.5};
  TH1F *hnew = dynamic_cast<TH1F*>(hp1->Rebin(8,"hnew", re_binning));
  hp1->Draw();
  hnew->Draw("same");
  return ;
  double purity = hnew->GetBinContent(pt);
  double puritye = hnew->GetBinError(pt);
  cout << "Using hadron purity of "<< purity << endl;
  
  /////Minuit Options
  bool hesse = true;
  bool minos = false;
  
  const double _start = -4;
  const double _end = -1;
  bool roodatahist = 1;
  RooRealVar *DCA = new RooRealVar("DCA","DCA",_start,_end);
  RooDataHist *dataHist = new RooDataHist("dataHist","dataHist",RooArgList(*DCA),data);
  RooDataHist *dataHist_D = new RooDataHist("dataHist_D","dataHist_D",RooArgList(*DCA),data_D);
  RooDataHist *dataHist_B = new RooDataHist("dataHist_B","dataHist_B",RooArgList(*DCA),data_B);
  RooDataHist *dataHist_pi = new RooDataHist("dataHist_pi","dataHist_pi",RooArgList(*DCA),data_pi);
  RooDataHist *dataHist_e = new RooDataHist("dataHist_e","dataHist_e",RooArgList(*DCA),data_e);
  //Signals
  //if(roodatahist){ // zyj comment this, because of definition problem
  
  RooRealVar mean1("mean1","mean1",-2,-3,-1);
  RooRealVar mean11("mean11","mean11",-2,-3,-1);
  RooRealVar sigma1("sigma1","sigma1",1,0.1,15);
  RooRealVar sigma11("sigma11","sigma11",1,0.1,15);
  RooRealVar sigma111("sigma111","sigma111",10,0.1,15);
  RooRealVar frac1("frac1","frac1",0.3,0.0,1);
  RooAbsPdf *g11_2; // zyj
  RooAbsPdf *g11_1;
  if(pt<9){
    g11_2 = new RooBifurGauss("g11_2","g11_2",*DCA,mean1,sigma1,sigma11);
    g11_1 = new RooGaussian("g11_1","g11_1",*DCA,mean11,sigma111);
  }
  else if(pt==9){
    g11_2 = new RooBifurGauss("g11_2","g11_2",*DCA,mean1,sigma1,sigma11);
    g11_1 = new RooGaussian("g11_1","g11_1",*DCA,mean1,sigma111);
  }
  //========================
  //e
  RooAddPdf g11("g11","g11",*g11_1,*g11_2,frac1);
  RooProdPdf e1_signal("e1_signal","e1_signal",g11);
  RooRealVar e_signal_yield_cont("e_signal_yield_cont","e_signal_yield_cont",1000,0,1000000000);
  RooArgList shapeList_e;
  RooArgList yieldList_e;
  shapeList_e.add(e1_signal);
  yieldList_e.add(e_signal_yield_cont);
  RooAddPdf completePDF_e("completePDF_e","completePDF_e",shapeList_e,yieldList_e);
  RooAbsReal *nllData_e  = completePDF_e.createNLL(*dataHist_e,Extended(kTRUE));
  RooAddition * nll_e = new RooAddition("nll_e","nll_e",RooArgSet(*nllData_e));
  RooMinuit m_e (*nll_e);
  m_e.setVerbose(kFALSE);
  m_e.migrad();
  
  // below is not used, why
  RooDataSet *d1e = (RooDataSet*)g11.generate(*DCA,100000);
  TH1F* h1e = (TH1F*)d1e->createHistogram("h1e",*DCA,Binning(data->GetNbinsX(),data->GetBinLowEdge(1),data->GetBinLowEdge(data->GetNbinsX())+data->GetBinWidth(5)));
  RooDataHist *dataHist_e1 = new RooDataHist("dataHist_e1","dataHist_e1",RooArgList(*DCA),h1e);
  //RooDataHist *dataHist_e1 =d1e->binnedClone();
  //RooHistPdf g1("g1","g1",RooArgSet(*DCA),*dataHist_e1);
  
  RooHistPdf g1("g1","g1",RooArgSet(*DCA),*dataHist_e);
  RooHistPdf gb("gb","gb",RooArgSet(*DCA),*dataHist_B);
  RooHistPdf gc("gc","gc",RooArgSet(*DCA),*dataHist_D);
  RooHistPdf g2("g2","g2",RooArgSet(*DCA),*dataHist_pi);
  //}
  RooProdPdf b_signal("b_signal","b_signal",gb);
  RooProdPdf c_signal("c_signal","c_signal",gc);
  RooProdPdf e_signal("e_signal","e_signal",g1);
  RooProdPdf pi_signal("pi_signal","pi_signal",g2);
  
  RooRealVar signal_yield("signal_yield","signal_yield",10000,0,4e9);
  signal_yield.setVal(data->GetEntries());
  signal_yield.setConstant(1);
  
  RooRealVar npe_ratio("npe_ratio","npe_ratio",0.7,0,1); // zyj !!! npe ratio, fb+fc
  RooRealVar b_ratio("b_ratio","b_ratio",0.6,0,1); // zyj fb/(fb+fc)
  RooRealVar bkg_ratio("bkg_ratio","bkg_ratio",0.3,0,0.8); // not used here, zyj
  RooRealVar e_ratio("e_ratio","e_ratio",0.3,0,0.8); // for
  e_ratio.setVal(e_const); //
  //if(!HT&&pt==7)e_ratio.setRange(0,1);
  //else
  e_ratio.setRange(e_const-0.01,e_const+0.01);
  //e_ratio.setRange(e_const-0.05,e_const+0.05);
  // zyj yield 之间存在关系,之前purity 的时候是各自没关系，直接就是各自的yield
  RooFormulaVar b_signal_yield("b_signal_yield","@0*@1*@2",RooArgList(b_ratio,signal_yield,npe_ratio));
  RooFormulaVar c_signal_yield("c_signal_yield","(1-@0)*@1*@2",RooArgList(b_ratio,signal_yield,npe_ratio));
  //RooFormulaVar pi_signal_yield("pi_signal_yield","@0*@1*(1-@2)",RooArgList(bkg_ratio,signal_yield,npe_ratio));
  RooFormulaVar e_signal_yield("e_signal_yield","@0*@1",RooArgList(e_ratio,signal_yield));
  
  RooRealVar PurVal("PurVal","PurVal",0.6,-1,1);
  PurVal.setVal(purity);
  //PurVal.setRange(0.2,1);
  //PurVal.setConstant(1);
  //RooFormulaVar pi_signal_yield("pi_signal_yield","(1-@0)*(@1+@2+@3)",RooArgList(PurVal,b_signal_yield,c_signal_yield,e_signal_yield));
  RooFormulaVar pi_signal_yield("pi_signal_yield","(1-@0)*(@1)",RooArgList(PurVal,signal_yield));
  //RooRealVar b_signal_yield("pi_signal_yield","pi_signal_yield",1000,0,1e6);
  
  RooArgList shapeList;
  RooArgList yieldList;
  
  shapeList.add(b_signal);
  shapeList.add(c_signal);
  shapeList.add(e_signal);
  shapeList.add(pi_signal);
  
  yieldList.add(b_signal_yield);
  yieldList.add(c_signal_yield);
  yieldList.add(e_signal_yield);
  yieldList.add(pi_signal_yield);
  
  //All together now
  RooAddPdf completePDF("completePDF","completePDF",shapeList,yieldList);
  
  //Now fit All Data
  RooAbsReal *nllData = completePDF.createNLL(*dataHist,Extended(kTRUE));
  RooAddition * nll = new RooAddition("nll","nll",RooArgSet(*nllData));
  RooMinuit m (*nll);
  m.setVerbose(kFALSE);
  m.migrad();
  if(hesse)m.hesse();
  if(minos)m.minos();
  // Construct plotables // Don't change anything from hear on unless you want to change how a plot looks or what is output below
  //if(1){//!roodatahist){
  RooPlot *DCAFrame_e = DCA->frame();
  dataHist_e->plotOn(DCAFrame_e,Name("HistM_e"));
  completePDF_e.plotOn(DCAFrame_e,Name("e_Curve_e")); // zyj 这个是为了看自己对e 的拟合效果怎么样？？
  //}
  //==============================================================
  
  //if(1){//!roodatahist){
  RooHist* pullHisto_e = DCAFrame_e->pullHist("HistM_e","e_Curve_e"); // zyj draw pull(for e only) in this frame
  RooPlot* pullPlot_e = DCA->frame();
  pullHisto_e->SetFillColor(1);
  pullHisto_e->SetLineColor(0);
  pullPlot_e->addPlotable(pullHisto_e,"B");
  //}
  //==============================================================
  
  RooPlot *DCAFrame = DCA->frame();
  dataHist->plotOn(DCAFrame,Name("HistM"));
  completePDF.plotOn(DCAFrame,Name("DCA_Curve")); // zyj draw all in this frame
  completePDF.plotOn(DCAFrame,Components(RooArgSet(e_signal)),LineStyle(6),LineColor(kOrange-3),Name("pe"));
  completePDF.plotOn(DCAFrame,Components(RooArgSet(pi_signal)),LineStyle(8),LineColor(kRed),Name("pi"));
  completePDF.plotOn(DCAFrame,Components(RooArgSet(b_signal)),LineStyle(7),LineColor(kGreen-2),FillStyle(1000),FillColor(kGreen-1),Name("b"));
  completePDF.plotOn(DCAFrame,Components(RooArgSet(c_signal)),LineStyle(9),LineColor(kMagenta),FillColor(kGreen-2),Name("c"));
  
  dataHist->plotOn(DCAFrame,Name("HistM"));
  //==============================================================
  
  RooPlot *DCAFrame11 = DCA->frame();
  dataHist->plotOn(DCAFrame11,Name("HistMM"));
  completePDF.plotOn(DCAFrame,Name("DCA_Curve"));  // only draw total and fit here zyj
  RooHist* pullHisto = DCAFrame->pullHist("HistM","DCA_Curve"); //zyj draw pull(for all) in this frame
  RooPlot* pullPlot = DCA->frame();
  pullHisto->SetFillColor(1);
  pullHisto->SetLineColor(0);
  pullPlot->addPlotable(pullHisto,"B"); // ?????
  
  //==============================================================
  
  RooArgSet *freeparam = completePDF.getParameters(dataHist);
  int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
  TPaveText* txt = new TPaveText(0.2,0.75,0.47,0.85,"BRNDC");
  txt->SetTextSize(0.07);
  txt->SetTextColor(1);
  txt->SetBorderSize(0.1);
  txt->SetFillColor(0);
  txt->SetFillStyle(0);
  TPaveText* txt1 = new TPaveText(0.56,0.55,0.9,0.71,"BRNDC");
  txt1->SetTextSize(0.07);
  txt1->SetTextColor(1);
  txt1->SetBorderSize(0.1);
  txt1->SetFillColor(0);
  txt1->SetFillStyle(0);
  char chi2[50];
  char entr[50];
  char ptbin[50];
  sprintf(chi2,"#chi^{2}/NDF=%1.2f",DCAFrame->chiSquare("DCA_Curve","HistM",numfreeparam));
  //sprintf(entr,"Signal Yield: %i #pm %i",(int)e_signal_yield.getVal(),(int)TMath::Max(fabs(e_signal_yield.getErrorLo()),e_signal_yield.getErrorHi()));
  if(1){
    sprintf(ptbin,"#it{p}_{T} #in [%1.1f,%1.1f] GeV",ptLow,ptHigh);
    if(HT)sprintf(entr,"High Tower");
    //if(!HT)sprintf(entr,"Min. Bias");
    if(!HT)sprintf(entr,"Central-5");
    txt->AddText(ptbin);
    txt1->AddText(entr);
    txt1->AddText(chi2);
    
    DCAFrame->addObject(txt1);
    DCAFrame->addObject(txt);
    DCAFrame11->addObject(txt);
  }
  //Objects for saving yields and so forth
  double yields[5];
  double yields_errors[5];
  yields[0]=(int)e_signal_yield.getVal();
  yields[1]=(int)pi_signal_yield.getVal();
  yields[2]=(int)b_signal_yield.getVal();
  yields[3]=(int)c_signal_yield.getVal();
  yields_errors[0]=yields[0]*sqrt(e_ratio.getError()*e_ratio.getError()/e_ratio.getVal()/e_ratio.getVal());//(int)TMath::Max(fabs(e_signal_yield.getErrorLo()),e_signal_yield.getErrorHi());
  yields_errors[1]=yields[1]*sqrt(PurVal.getError()*PurVal.getError()/PurVal.getVal()/PurVal.getVal());
  yields_errors[2]=yields[2]*sqrt(npe_ratio.getError()*npe_ratio.getError()/npe_ratio.getVal()/npe_ratio.getVal()+b_ratio.getError()*b_ratio.getError()/b_ratio.getVal()/b_ratio.getVal());
  yields_errors[3]=yields[3]*sqrt(npe_ratio.getError()*npe_ratio.getError()/npe_ratio.getVal()/npe_ratio.getVal()+b_ratio.getError()*b_ratio.getError()/b_ratio.getVal()/b_ratio.getVal());
  yields_errors[4]=0;//(int)TMath::Max(fabs(c_signal_yield.getErrorLo()),c_signal_yield.getErrorHi())/yields[3] * yields[4];
  
  DCA->setRange("range1",-1.5,-1);
  RooAbsReal* e1_1 = g1.createIntegral(*DCA,*DCA,"range1");
  RooAbsReal* had1_1 = g2.createIntegral(*DCA,*DCA,"range1");
  RooAbsReal* b_1 = gb.createIntegral(*DCA,*DCA,"range1");
  RooAbsReal* c_1 = gc.createIntegral(*DCA,*DCA,"range1");
  double b_int = b_1->getVal();
  double c_int = c_1->getVal();
  double e_int = e1_1->getVal();
  double h_int = had1_1->getVal();
  
  double pur1 = b_int*yields[2] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
  double pur2 = c_int*yields[3] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
  double pur3 = e_int*yields[0] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
  double pur4 = h_int*yields[1] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
  //================================================================================
  
  DCA->setRange("range3",-2,-1);
  RooAbsReal* e1_3 = g1.createIntegral(*DCA,*DCA,"range3");
  RooAbsReal* had1_3 = g2.createIntegral(*DCA,*DCA,"range3");
  RooAbsReal* b_3 = gb.createIntegral(*DCA,*DCA,"range3");
  RooAbsReal* c_3 = gc.createIntegral(*DCA,*DCA,"range3");
  double b_int1 = b_3->getVal();
  double c_int1 = c_3->getVal();
  double e_int1 = e1_3->getVal();
  double h_int1 = had1_3->getVal();
  
  /*
   double pur1 = b_int*yields[2] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
   double pur2 = c_int*yields[3] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
   double pur3 = e_int*yields[0] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
   double pur4 = h_int*yields[1] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);*/
  double pur11 = b_int1*yields[2] / (e_int1*yields[0]+ h_int1*yields[1] + b_int1*yields[2] + c_int1*yields[3]);
  double pur22 = c_int1*yields[3] / (e_int1*yields[0]+ h_int1*yields[1] + b_int1*yields[2] + c_int1*yields[3]);
  double pur33 = e_int1*yields[0] / (e_int1*yields[0]+ h_int1*yields[1] + b_int1*yields[2] + c_int1*yields[3]);
  double pur44 = h_int1*yields[1] / (e_int1*yields[0]+ h_int1*yields[1] + b_int1*yields[2] + c_int1*yields[3]);
  
  if (save==1){
    //cout<<datfile<<"zyj jjjjjjjjjjjjjjjjjjjjjjjjjjjjdddddddddddddddd"<<endl;
    ofstream output1 (datfile,ios::app);
    if(output1.is_open()){
      output1 <<  pt <<" " <<  yields[2] << " " << yields_errors[2] << " " << pur1 << " " << pur11 << " " <<
      yields[3] << " " << yields_errors[3] << " " << pur2 << " " << pur22 << " " <<
      yields[0] << " " << yields_errors[0] << " " << pur3 << " " << pur33 << " " <<
      yields[1] << " " << yields_errors[1] << " " << pur4 << " " << pur44 << " " <<
      b_ratio.getVal()  << " " <<  b_ratio.getError()<< " " <<
      PurVal.getVal()<< " " <<  PurVal.getError()<< " " <<
      npe_ratio.getVal()  << " " <<  npe_ratio.getError() << " " << e_ratio.getVal()  << " " <<  e_ratio.getError() << " " << purity << " " << puritye <<   "\n";
      output1.close();
    }else(cout << "Error Opening Output Dat File!");
  }
  cout << "====================" << endl;
  cout << "Chi2 of Mass Fit: " << chi2 << endl;
  cout << "====================" << endl;
  cout<< "Yields: \n";
  cout << "====================" << endl;
  cout<<"photonic electrons: "<< yields[0] <<" +/- " << yields_errors[0] << " " << endl;
  cout<<"pions: "    << yields[1] <<" +/- " << yields_errors[1] << " " << endl;
  cout<<"b->e: "     << yields[2] <<" +/- " << yields_errors[2] << " " << endl;
  cout<<"D->e: "     << yields[3] <<" +/- " << yields_errors[3] << " " << endl;
  cout<<"Purity: "     <<  purity << endl;
  cout<<"Purity in fit: "     << (yields[2]+ yields[3]+ yields[4]+yields[0])/(yields[4]+yields[1]+ yields[2]+ yields[3]+ yields[0])  << endl;
  cout << "====================" << endl;
  cout<< "Ratio of b/c: \n";
  cout << "====================" << endl;
  double temp1 = (yields[3])/(yields[3]+yields[2])/(yields[3]+yields[2])*yields_errors[2]; // zyj not used here
  double temp2 = (yields[2])/(yields[3]+yields[2])/(yields[3]+yields[2])*yields_errors[3];
  
  
  cout<<  b_ratio.getVal() << " #pm " << b_ratio.getError()  <<  endl;
  cout << "====================" << endl;
  cout<< "Fraction in b-rich region (-1.5,-1): \n";
  cout << "====================" << endl;
  cout<<"photonic electrons: "<< pur3 << endl;
  cout<<"pions: "    << pur4 << endl;
  cout<<"b->e: "     << pur1 << endl;
  cout<<"c->e: "     << pur2 << endl;
  cout << "====================" << endl;
  cout<< "Fraction in c-rich region (-2,-1.5): \n";
  cout << "====================" << endl;
  cout<<"photonic electrons: "<< pur33 <<endl;
  cout<<"pions: "    << pur44 << endl;
  cout<<"b->e: "     << pur11 <<endl;
  cout<<"c->e: "     << pur22 <<endl;
  cout << "====================" << endl;
  
  
  TCanvas *c1 = new TCanvas("c1","full fit");
  prettycanvasAllleg(c1,DCAFrame,pullPlot,0,data->GetMaximum()/7);
  TCanvas *c5 = new TCanvas("c5","electron");
  prettycanvasAll(c5,DCAFrame_e,pullPlot_e,0,data_e->GetMaximum()/7);
  /*
   if(!roodatahist){
   TCanvas *c2 = new TCanvas("c2","pion");
   prettycanvasAll(c2,DCAFrame_pi,pullPlot_pi,0,data_pi->GetMaximum()/7);
   TCanvas *c7 = new TCanvas("c7","D");
   prettycanvasAll(c7,DCAFrame_D,pullPlot_D,0,data_D->GetMaximum()/7);
   TCanvas *c8 = new TCanvas("c8","B");
   prettycanvasAll(c8,DCAFrame_B,pullPlot_B,0,data_B->GetMaximum()/7);
   }
   */
  if(save==1){
    char mass_c[150];
    char mass_pdf[150];
    char mass_png[150];
    char mass_eps[150];
    sprintf(mass_c,"%s.C",dir1);
    sprintf(mass_pdf,"%s.pdf",dir1);
    sprintf(mass_png,"%s.png",dir1);
    sprintf(mass_eps,"%s.eps",dir1);
    //c1->SaveAs(Form(mass_c));
    c1->SaveAs(Form(mass_pdf));
    //c5->SaveAs(Form("%s_e.pdf",dir1));
    //c1->SaveAs(Form(mass_png));
    //c1->SaveAs(Form(mass_eps));
  }
}




