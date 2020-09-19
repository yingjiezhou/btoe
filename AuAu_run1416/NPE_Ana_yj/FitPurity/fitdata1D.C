#include "prettycanvasAll.C"
#include "prettycanvasOne.C"

using namespace RooFit;

void fitdata1D(TH1F *data,TH1F *data_e,TH1F *data_pi, TH1F *data_2pi,TH1F *data_k,TH1F *data_p,TH1F* data_,int daughter,int mag, int save,
               char outputfile[],char datfile[],char datc[],char dir1[],char dir2[],char dir3[],char dir4[],char dir5[],char dir6[],
               int pt,int eta, int rs,float cutLow,float cutHigh,double ptLow ,double ptHigh)
{
  gSystem->Load("libRooFit.so");
  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
  /////Minuit Options
  bool hesse = true;
  bool minos = false;
  if(pt==6)minos= true;
  if(pt==3)minos= true;
  if(pt==2||pt==1)minos= true;
  const double _start = -10;
  const double _end = 5;//13;
  RooRealVar *PID = new RooRealVar("PID","PID",_start,_end);
  RooDataHist *dataHist = new RooDataHist("dataHist","dataHist",RooArgList(*PID),data);
  RooDataHist *dataHist1 = new RooDataHist("dataHist1","dataHist1",RooArgList(*PID),data_);
  RooDataHist *dataHist_pi = new RooDataHist("dataHist_pi","dataHist_pi",RooArgList(*PID),data_pi);
  RooDataHist *dataHist_2pi = new RooDataHist("dataHist_2pi","dataHist_2pi",RooArgList(*PID),data_2pi);
  RooDataHist *dataHist_k = new RooDataHist("dataHist_k","dataHist_k",RooArgList(*PID),data_k);
  RooDataHist *dataHist_e = new RooDataHist("dataHist_e","dataHist_e",RooArgList(*PID),data_e);
  RooDataHist *dataHist_p = new RooDataHist("dataHist_p","dataHist_p",RooArgList(*PID),data_p);
  //Signals

  RooRealVar mean1("mean1","mean1",0,-2,2);
  RooRealVar sigma1("sigma1","sigma1",1,0,1.2);
  RooRealVar sigma11("sigma11","sigma11",1,0,1.2);
  RooBifurGauss g1("g1","g1",*PID,mean1,sigma1,sigma1);

  RooRealVar mean2("mean2","mean2",-5,-7,2);
  RooRealVar mean22("mean22","mean22",-5,-7,2);
  RooRealVar sigma2("sigma2","sigma2",1.,0.1,2.5); //0814
  RooRealVar sigma22("sigma22","sigma22",1.,0.1,2.);
  RooRealVar sigma222("sigma222","sigma222",1.,0.1,5.);
  RooRealVar frac2("frac2","frac2",0.5,0.1,1); //0.5,0.1,1
  RooRealVar n2("n2","n2",1);
  RooRealVar alpha2("alpha2","alpha2",-2,-5,5);
  
  RooBifurGauss g2_1("g2_1","g2_1",*PID,mean2,sigma2,sigma22);
  RooGaussian g2_2("g2_2","g2_2",*PID,mean2,sigma222);
  
  // RooCBShape g2("g2","g2",*PID,mean2,sigma2,alpha2,n2);
  RooAbsPdf *g2;
  if(pt==8)sigma22.setRange(2.0,2.5);
  //if(pt==6)frac2.setVal(0.6);
  if(pt<6 || pt==7) g2 = new RooAddPdf("g2","g2",g2_1,g2_2,frac2); //0814 pion
  else g2 = new RooBifurGauss("g2","g2",*PID,mean2,sigma2,sigma22);
  
  RooRealVar mean3("mean3","mean3",-5,-7,2);
  RooRealVar mean33("mean33","mean33",-5,-7,2);
  RooRealVar sigma3("sigma3","sigma3",1.0, 0.1,2.5);
  RooRealVar sigma33("sigma33","sigma33",1.,0.1,2.);
  RooRealVar sigma333("sigma333","sigma333",1.,0.1,5.);
  RooRealVar frac3("frac3","frac3",0.8,0.01,1);
  RooBifurGauss g3_1("g3_1","g3_1",*PID,mean3,sigma3,sigma33);
  RooGaussian g3_2("g3_2","g3_2",*PID,mean33,sigma333);
  RooAbsPdf *g3;
  if(pt>5 && pt<7) g3 = new RooAddPdf("g3","g3",g3_1,g3_2,frac3);//0814 kaon
  else  g3 = new RooBifurGauss("g3","g3",*PID,mean3,sigma3,sigma33);
  
  RooRealVar mean4("mean4","mean4",-5,-7,2);
  RooRealVar mean44("mean44","mean44",-5,-7,2);
  RooRealVar sigma4("sigma4","sigma4",1.0, 0.1,2.5);
  RooRealVar sigma44("sigma44","sigma44",1.,0.1,2.);
  RooRealVar sigma444("sigma444","sigma444",1.,0.1,5.);
  RooRealVar frac4("frac4","frac4",0.8,0.,1); // 0814 proton
  RooBifurGauss g4_1("g4_1","g4_1",*PID,mean4,sigma4,sigma44);
  RooGaussian g4_2("g4_2","g4_2",*PID,mean44,sigma444);
  RooAbsPdf *g4;
  if(pt>5 && pt<8) frac4.setVal(0.3); //0814
  if(pt<8) g4 = new RooAddPdf("g4","g4",g4_1,g4_2,frac4);
  else g4 = new RooBifurGauss("g4","g4",*PID,mean4,sigma4,sigma44);
  
  
  RooRealVar mean5("mean5","mean5",5,3,10);
  RooRealVar sigma5("sigma5","sigma5",1,0,5.);
  RooRealVar sigma55("sigma55","sigma55",1,0,5.);
  RooGaussian g5("g5","g5",*PID,mean5,sigma5);
  
  //Background
  RooRealVar bg1 ("bg1","bg1",-4.29529e-01,-3,.3);
  RooRealVar bg2("bg2","bg2",-9e-3,-1,.3);
  RooChebychev bgMass("bgMass","bgMass",*PID,RooArgList(bg1));
  
  RooProdPdf e_signal("e_signal","e_signal",g1);
  RooProdPdf pi_signal("pi_signal","pi_signal",*g2); // 0814 pion
  RooProdPdf pi2_signal("pi2_signal","pi2_signal",g5);
  RooProdPdf k_signal("k_signal","k_signal",*g3); // 0814 kaon
  RooProdPdf p_signal("p_signal","p_signal",*g4); // 0814 proton
  
  
  RooRealVar e_signal_yield("e_signal_yield","e_signal_yield",10000,0,4e7);
  RooRealVar pi_signal_yield("pi_signal_yield","pi_signal_yield",1000,100,10000000000);
  RooRealVar pi2_signal_yield("pi2_signal_yield","pi2_signal_yield",100,0,1000000000);
  RooRealVar k_signal_yield("k_signal_yield","k_signal_yield",10000,0,1000000000);
  RooRealVar p_signal_yield("p_signal_yield","p_signal_yield",0,0,1000000000);
  
  RooRealVar e_signal_yield_cont("e_signal_yield_cont","e_signal_yield_cont",1000,0,1000000000);
  RooRealVar pi_signal_yield_cont("pi_signal_yield_cont","pi_signal_yield_cont",1000,0,10000000000);
  RooRealVar pi2_signal_yield_cont("pi2_signal_yield_cont","pi2_signal_yield_cont",1000,0,1000000000);
  RooRealVar k_signal_yield_cont("k_signal_yield_cont","k_signal_yield_cont",1000,0,1000000000);
  RooRealVar p_signal_yield_cont("p_signal_yield_cont","p_signal_yield_cont",1000,0,1000000000);
  
  RooArgList shapeList;
  RooArgList yieldList;
  
  RooArgList shapeList_pi;
  RooArgList yieldList_pi;
  RooArgList shapeList_2pi;
  RooArgList yieldList_2pi;
  RooArgList shapeList_e;
  RooArgList yieldList_e;
  RooArgList shapeList_k;
  RooArgList yieldList_k;
  RooArgList shapeList_p;
  RooArgList yieldList_p;
  
  shapeList.add(e_signal);
  shapeList.add(pi_signal);
  if(pt<7)shapeList.add(pi2_signal);
  if((pt>3||pt==0) && pt!=7)shapeList.add(k_signal);
  if(pt>5||pt==0)shapeList.add(p_signal);
  
  yieldList.add(e_signal_yield);
  yieldList.add(pi_signal_yield);
  if(pt<7)yieldList.add(pi2_signal_yield);
  if((pt>3||pt==0) && pt!=7)yieldList.add(k_signal_yield);
  if(pt>5||pt==0)yieldList.add(p_signal_yield);
  
  shapeList_pi.add(pi_signal);
  yieldList_pi.add(pi_signal_yield_cont);
  shapeList_2pi.add(pi2_signal);
  yieldList_2pi.add(pi2_signal_yield_cont);
  shapeList_e.add(e_signal);
  yieldList_e.add(e_signal_yield_cont);
  shapeList_k.add(k_signal);
  yieldList_k.add(k_signal_yield_cont);
  shapeList_p.add(p_signal);
  yieldList_p.add(p_signal_yield_cont);
  //All together now
  RooAddPdf completePDF("completePDF","completePDF",shapeList,yieldList);
  RooAddPdf completePDF_e("completePDF_e","completePDF_e",shapeList_e,yieldList_e);
  RooAddPdf completePDF_pi("completePDF_pi","completePDF_pi",shapeList_pi,yieldList_pi);
  RooAddPdf completePDF_2pi("completePDF_2pi","completePDF_2pi",shapeList_2pi,yieldList_2pi);
  RooAddPdf completePDF_k("completePDF_k","completePDF_k",shapeList_k,yieldList_k);
  RooAddPdf completePDF_p("completePDF_p","completePDF_p",shapeList_p,yieldList_p);
  
  //Now fit Data
  PID->setRange("range_e",-3,3);
  RooAbsReal *nllData_e  = completePDF_e.createNLL(*dataHist_e,Extended(kTRUE),Range("range_e"));
  RooAddition * nll_e = new RooAddition("nll_e","nll_e",RooArgSet(*nllData_e));
  RooMinuit m_e (*nll_e);
  m_e.setVerbose(kFALSE);
  m_e.migrad();
  //mean2.setConstant();
  //sigma2.setConstant();
  //mean22.setConstant();
  //sigma22.setConstant();
  sigma1.setRange(sigma1.getVal()-sigma1.getError(),sigma1.getVal()+sigma1.getError());
  sigma11.setRange(sigma11.getVal()-sigma11.getError(),sigma11.getVal()+sigma11.getError());
  mean1.setRange(mean1.getVal()-mean1.getError(),mean1.getVal()+mean1.getError());
  
  //PID->setRange("range_pi",-10,1);
  if(pt==1) PID->setRange("range_pi",-10,0);
  if(pt==2) PID->setRange("range_pi",-10,3);
  if(pt==3) PID->setRange("range_pi",-8,3);
  if(pt==4) PID->setRange("range_pi",-9,3);
  if(pt==5) PID->setRange("range_pi",-9,3);
  if(pt==6) PID->setRange("range_pi",-8,-2); // 0814 add one
  if(pt>6) PID->setRange("range_pi",-5,3);// zyj (-5,3) , pt ==7
  RooAbsReal *nllData_pi  = completePDF_pi.createNLL(*dataHist_pi,Extended(kTRUE),Range("range_pi"));
  RooAddition * nll_pi = new RooAddition("nll_pi","nll_pi",RooArgSet(*nllData_pi));
  RooMinuit m_pi (*nll_pi);
  m_pi.setVerbose(kFALSE);
  m_pi.migrad();
  //mean2.setConstant();
  //sigma2.setConstant();
  //mean22.setConstant();
  //sigma22.setConstant();
  //frac2.setConstant();
  
  if(pt!=7) sigma2.setRange(sigma2.getVal()-sigma2.getError(),sigma2.getVal()+sigma2.getError());
  if(pt!=7)sigma22.setRange(sigma22.getVal()-sigma22.getError(),sigma22.getVal()+sigma22.getError());
  sigma222.setRange(sigma222.getVal()-sigma222.getError(),sigma222.getVal()+sigma222.getError());
  if(pt!=7)mean2.setRange(mean2.getVal()-mean2.getError(),mean2.getVal()+mean2.getError());
  frac2.setRange(frac2.getVal()-frac2.getError(),frac2.getVal()+frac2.getError());
  mean22.setRange(mean22.getVal()-mean22.getError(),mean22.getVal()+mean22.getError());
  alpha2.setConstant(1);//Range(alpha2.getVal()-alpha2.getError(),alpha2.getVal()+alpha2.getError());
  n2.setConstant(1);//Range(n2.getVal()-n2.getError(),n2.getVal()+n2.getError());
  PID->setRange("range_2pi",2,7);
  RooAbsReal *nllData_2pi  = completePDF_2pi.createNLL(*dataHist_2pi,Extended(kTRUE),Range("range_2pi"));
  RooAddition * nll_2pi = new RooAddition("nll_2pi","nll_2pi",RooArgSet(*nllData_2pi));
  RooMinuit m_2pi (*nll_2pi);
  m_2pi.setVerbose(kFALSE);
  m_2pi.migrad();
  
  if(1)sigma5.setRange(sigma5.getVal()-sigma5.getError(),sigma5.getVal()+sigma5.getError());
  if(1)mean5.setRange(mean5.getVal()-mean5.getError(),mean5.getVal()+mean5.getError());
  if(1)sigma55.setRange(sigma55.getVal()-sigma55.getError(),sigma55.getVal()+sigma55.getError());
  PID->setRange("range_k",-10,2);
  if(pt==8) PID->setRange("range_k",-5,2); //0814 kaon range
  RooAbsReal *nllData_k  = completePDF_k.createNLL(*dataHist_k,Extended(kTRUE),Range("range_k"));
  RooAddition * nll_k = new RooAddition("nll_k","nll_k",RooArgSet(*nllData_k));
  RooMinuit m_k (*nll_k);
  m_k.setVerbose(kFALSE);
  m_k.migrad();
  sigma3.setRange(sigma3.getVal()-sigma3.getError(),sigma3.getVal()+sigma3.getError());
  sigma33.setRange(sigma33.getVal()-sigma33.getError(),sigma33.getVal()+sigma33.getError());
  sigma333.setRange(sigma333.getVal()-sigma333.getError(),sigma333.getVal()+sigma333.getError());
  mean3.setRange(mean3.getVal()-mean3.getError(),mean3.getVal()+mean3.getError());
  frac3.setRange(frac3.getVal()-frac3.getError(),frac3.getVal()+frac3.getError());
  mean33.setRange(mean33.getVal()-mean33.getError(),mean33.getVal()+mean33.getError());
  //mean3.setConstant();
  //sigma3.setConstant();
  //sigma33.setConstant();
  PID->setRange("range_p",-13,0);
  RooAbsReal *nllData_p  = completePDF_p.createNLL(*dataHist_p,Extended(kTRUE),Range("range_p"));
  RooAddition * nll_p = new RooAddition("nll_p","nll_p",RooArgSet(*nllData_p));
  RooMinuit m_p (*nll_p);
  m_p.setVerbose(kFALSE);
  m_p.migrad();
  
  sigma4.setRange(sigma4.getVal()-sigma4.getError(),sigma4.getVal()+sigma4.getError());
  sigma44.setRange(sigma44.getVal()-sigma44.getError(),sigma44.getVal()+sigma44.getError());
  sigma444.setRange(sigma444.getVal()-sigma444.getError(),sigma444.getVal()+sigma444.getError());
  mean4.setRange(mean4.getVal()-mean4.getError(),mean4.getVal()+mean4.getError());
  frac4.setRange(frac4.getVal()-frac4.getError(),frac4.getVal()+frac4.getError());
  mean44.setRange(mean44.getVal()-mean44.getError(),mean44.getVal()+mean44.getError());
  if(data_p->GetEntries()<5){
    p_signal_yield.setVal(0);
    p_signal_yield.setConstant(1);
  }
  if(data_k->GetEntries()<10){
    //k_signal_yield.setVal(0);
    //k_signal_yield.setConstant(1);
    
  }
  if(data_2pi->GetEntries()<1){
    //pi2_signal_yield.setVal(0);
    //if(pt<5)pi2_signal_yield.setConstant(1);
    //mean5.setConstant(0);
    //sigma5.setConstant(0);
  }
  //Now fit All Data
  PID->setRange("range",-10,5);
  RooAbsReal *nllData = completePDF.createNLL(*dataHist,Extended(kTRUE),Range("range"));
  RooAddition * nll = new RooAddition("nll","nll",RooArgSet(*nllData));
  RooMinuit m (*nll);
  m.setVerbose(kFALSE);
  m.migrad();
  if(hesse)m.hesse();
  if(minos)m.minos();
  // Construct plotables // Don't change anything from hear on unless you want to change how a plot looks or what is output below
  RooPlot *PIDFrame_e = PID->frame();
  dataHist_e->plotOn(PIDFrame_e,Name("HistM"));
  completePDF_e.plotOn(PIDFrame_e,Name("e_Curve"));
  RooPlot *PIDFrame_pi = PID->frame();
  dataHist_pi->plotOn(PIDFrame_pi,Name("HistM"));
  completePDF_pi.plotOn(PIDFrame_pi,Name("pi_Curve"));
  RooPlot *PIDFrame_2pi = PID->frame();
  dataHist_2pi->plotOn(PIDFrame_2pi,Name("HistM"));
  completePDF_2pi.plotOn(PIDFrame_2pi,Name("pi2_Curve"));
  RooPlot *PIDFrame_k = PID->frame();
  dataHist_k->plotOn(PIDFrame_k,Name("HistM"));
  completePDF_k.plotOn(PIDFrame_k,Name("k_Curve"));
  RooPlot *PIDFrame_p = PID->frame();
  dataHist_p->plotOn(PIDFrame_p,Name("HistM"));
  completePDF_p.plotOn(PIDFrame_p,Name("p_Curve"));
  RooPlot *PIDFrame = PID->frame();
  dataHist->plotOn(PIDFrame,Name("HistM"));
  //dataHistws->plotOn(PIDFrame,Name("HistMws"),LineStyle(1),LineColor(15),FillColor(17),FillStyle(1000));
  completePDF.plotOn(PIDFrame,Name("PID_Curve"));
  completePDF.plotOn(PIDFrame,Name("e_signal"),Components(RooArgSet(e_signal)),LineStyle(7),LineColor(kGreen-2),FillColor(kGreen-2));
  completePDF.plotOn(PIDFrame,Name("pi_signal"),Components(RooArgSet(pi_signal)),LineStyle(6),LineColor(kRed),FillColor(kGreen-2));
  completePDF.plotOn(PIDFrame,Name("pi2_signal"),Components(RooArgSet(pi2_signal)),LineStyle(6),LineColor(6),FillColor(kGreen-2));
  completePDF.plotOn(PIDFrame,Name("k_signal"),Components(RooArgSet(k_signal)),LineStyle(6),LineColor(kYellow-2),FillColor(kGreen-2));
  completePDF.plotOn(PIDFrame,Name("p_signal"),Components(RooArgSet(p_signal)),LineStyle(6),LineColor(7),FillColor(kGreen-2));
  //==========================================================================
  
  dataHist1->plotOn(PIDFrame,Name("HistM1"),MarkerColor(kGray),LineColor(kGray));
  dataHist->plotOn(PIDFrame,Name("HistM"));
  //leg->AddEntry("HistM1","IncE", "LP");
  //leg->AddEntry("HistM","IncE_MVA", "LP");
  //==========================================================================
  
  /*
  TLegend *leg = new TLegend(0.18,0.65,0.35,0.9); // 这个只是设置框框的大小，只要框框比文字大，缩小框框的时候字不会变
  leg->AddEntry("PID_Curve","PID_Curve", "L");
  leg->AddEntry("e_signal","e_signal", "L");
  leg->AddEntry("pi_signal","pi_signal", "L");
  leg->AddEntry("pi2_signal","pi2_signal", "L");
  leg->AddEntry("k_signal","k_signal", "L");
  leg->AddEntry("p_signal","p_signal", "L");
  leg->AddEntry("HistM1","IncE", "LP");
  leg->AddEntry("HistM","IncE_MVA", "LP");
  */
  //==========================================================================
  
  
  RooHist* pullHisto = PIDFrame->pullHist("HistM","PID_Curve");
  RooPlot* pullPlot = PID->frame();
  pullHisto->SetFillColor(1);
  pullHisto->SetLineColor(0);
  pullPlot->addPlotable(pullHisto,"B");
  RooArgSet *freeparam = completePDF.getParameters(dataHist);
  int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
  TPaveText* txt = new TPaveText(0.62,0.70,0.88,0.88,"BRNDC");
  txt->SetTextSize(0.07);
  txt->SetTextColor(1);
  txt->SetBorderSize(0.1);
  txt->SetFillColor(0);
  txt->SetFillStyle(0);
  char chi2[50];
  char entr[50];
  char ptbin[50];
  sprintf(chi2,"%3.4f",PIDFrame->chiSquare("PID_Curve","HistM",numfreeparam));
  sprintf(entr,"Signal Yield: %i #pm %i",(int)e_signal_yield.getVal(),(int)TMath::Max(fabs(e_signal_yield.getErrorLo()),e_signal_yield.getErrorHi()));
  if(1){
    sprintf(ptbin,"#it{p}_{T} #in [%1.1f,%1.1f] GeV",ptLow,ptHigh);
    txt->AddText(ptbin);
    PIDFrame->addObject(txt);
  }
  //Objects for saving yields and so forth
  double yields[6];
  double yields_errors[6];
  yields[0]=(int)e_signal_yield.getVal();
  yields[1]=(int)pi_signal_yield.getVal();
  yields[2]=(int)k_signal_yield.getVal();
  yields[3]=(int)p_signal_yield.getVal();
  yields[4]=(int)pi2_signal_yield.getVal();
  yields[5]=(int)pi_signal_yield_cont.getVal();
  yields_errors[0]=(int)TMath::Max(fabs(e_signal_yield.getErrorLo()),e_signal_yield.getErrorHi());
  yields_errors[1]=(int)TMath::Max(fabs(pi_signal_yield.getErrorLo()),pi_signal_yield.getErrorHi());
  yields_errors[2]=(int)TMath::Max(fabs(k_signal_yield.getErrorLo()),k_signal_yield.getErrorHi());
  yields_errors[3]=(int)TMath::Max(fabs(p_signal_yield.getErrorLo()),p_signal_yield.getErrorHi());
  yields_errors[4]=(int)TMath::Max(fabs(pi2_signal_yield.getErrorLo()),pi2_signal_yield.getErrorHi());
  if (save==1){
    ofstream output (outputfile,ios::app);
    if(output.is_open()){
      time_t sec;
      sec = time(NULL);
      output <<"Date: " << ctime(&sec) << "\n";
      if(rs==1)output <<"RS Fit\n";
      if(rs==1)output <<"WS Fit\n";
      output <<"DaughterPtbinEtabin:"<< pt << eta << "\n";
      output <<"SigPMBKGPM:"<<"\n";
      output << yields[0] <<" "<< yields_errors[0] << " "<< yields[1] <<" "<< yields_errors[1] << " "; // will use this Ne to get purity zyj
      output << "\n";
      output <<"MassChi2"<< chi2 <<"\n";
      output.close();
    }else(cout << "Error Opening Output File!");
  }
  
  
  
  PID->setRange("range1",cutLow,cutHigh);
  RooAbsReal* e1_1 = g1.createIntegral(*PID,*PID,"range1");
  RooAbsReal* had1_1 = g2->createIntegral(*PID,*PID,"range1");
  RooAbsReal* had2_1 = g3->createIntegral(*PID,*PID,"range1");
  RooAbsReal* had3_1 = g4->createIntegral(*PID,*PID,"range1");
  RooAbsReal* had4_1 = g5.createIntegral(*PID,*PID,"range1");
  double pur1 = e1_1->getVal()*yields[0] / (e1_1->getVal()*yields[0]+had1_1->getVal()*yields[1] + had2_1->getVal()*yields[2] + had3_1->getVal()*yields[3]  + had4_1->getVal()*yields[4]) ;
  double eff =  e1_1->getVal() ;
  if (save==1){
    ofstream output1 (datfile,ios::app);
    if(output1.is_open()){
      output1 <<"pt: " << pt <<" " <<" e yield: "<<  yields[0] <<" "<< yields_errors[0] << " " << pur1  << " " << eff << " " << yields[1] << " " << yields_errors[1] <<" " << had1_1->getVal()<< "\n";
      output1.close();
    }else(cout << "Error Opening Output Dat File!");
  }
  cout << "Chi2 of Mass Fit: " << chi2 << endl;
  cout<< "Yields: \n";
  cout<<"electrons: "<< yields[0] <<" +/- " << yields_errors[0] << " " << e1_1->getVal() <<endl;
  cout<<"pions: "<< yields[1] <<" +/- " << yields_errors[1] << " " << had1_1->getVal() << " " << yields[5]/yields[1]<< endl;
  cout<<"kaons: "<< yields[2] <<" +/- " << yields_errors[2] << " " << had2_1->getVal() <<endl;
  cout<<"protons: "<< yields[3] <<" +/- " << yields_errors[3] << " " << had3_1->getVal() <<endl;
  cout<<"merged pi: "<< yields[4] <<" +/- " << yields_errors[4] << " " << had4_1->getVal() <<endl;
  cout << "====================" << endl;
  cout << "Checking purity cuts" << endl;
  cout << "====================" << endl;
  for(double i=0; i<30; i++){
    PID->setRange("range1",-3+3*i/30,3);
    RooAbsReal *e1 = g1.createIntegral(*PID,*PID,"range1");
    RooAbsReal *had1 = g2->createIntegral(*PID,*PID,"range1");
    RooAbsReal *had2 = g3->createIntegral(*PID,*PID,"range1");
    RooAbsReal *had3 = g4->createIntegral(*PID,*PID,"range1");
    RooAbsReal *had4 = g5.createIntegral(*PID,*PID,"range1");
    double pur1 = e1_1->getVal()*yields[0] / (e1_1->getVal()*yields[0]+had1_1->getVal()*yields[1] + had2_1->getVal()*yields[2] + had3_1->getVal()*yields[3]  + had4_1->getVal()*yields[4] ) ;
    double eff =  e1_1->getVal() ;
    cout << "Ranges " << -3+3*i/30 << " " << 3 << " Purity " << pur1 << " eff. " << eff << endl;
  }
  
  
  
  //==========================================================================
  
  TCanvas *c1 = new TCanvas("c1","full fit");
  PIDFrame->GetYaxis()->SetRangeUser(1,data->GetMaximum()*10);
  //prettycanvasAll(c1,PIDFrame,leg,pullPlot,1);
  prettycanvasAll(c1,PIDFrame,pullPlot,1);
 
  
  TCanvas *c2 = new TCanvas("c2","pion");
  PIDFrame_pi->GetYaxis()->SetRangeUser(1,data_pi->GetMaximum()*10);
  prettycanvasOne(c2,PIDFrame_pi,pullPlot,1);
  TCanvas *c3 = new TCanvas("c3","kaon");
  PIDFrame_k->GetYaxis()->SetRangeUser(1,data_k->GetMaximum()*10);
  prettycanvasOne(c3,PIDFrame_k,pullPlot,1);
  TCanvas *c4 = new TCanvas("c4","proton");
  PIDFrame_p->GetYaxis()->SetRangeUser(1,data_p->GetMaximum()*10);
  prettycanvasOne(c4,PIDFrame_p,pullPlot,1);
  TCanvas *c5 = new TCanvas("c5","electron");
  PIDFrame_e->GetYaxis()->SetRangeUser(1,data_e->GetMaximum()*10);
  prettycanvasOne(c5,PIDFrame_e,pullPlot,1);
  PIDFrame_2pi->GetYaxis()->SetRangeUser(1,data_2pi->GetMaximum()*10);
  TCanvas *c6 = new TCanvas("c6","merged pi");
  prettycanvasOne(c5,PIDFrame_2pi,pullPlot,1);
  
  if(save==1){
    char mass_c[150];
    char mass_pdf[150];
    char mass_png[150];
    char mass_eps[150];
    sprintf(mass_c,"%s.C",dir1);
    sprintf(mass_pdf,"%s.pdf",dir1);
    sprintf(mass_png,"%s.png",dir1);
    sprintf(mass_eps,"%s.eps",dir1);
    c1->SaveAs(Form(mass_c));
    c1->SaveAs(Form(mass_pdf));
    c1->SaveAs(Form(mass_png));
    c1->SaveAs(Form(mass_eps));
  }
}



