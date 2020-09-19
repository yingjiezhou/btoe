#include "prettycanvasAll.C"
gSystem->Load("libRooFit.so");

using namespace RooFit;

void fitdata1D(TH1F *data,TH1F *data_e,TH1F *data_pi, TH1F *data_2pi,TH1F *data_k,TH1F *data_p,TH1F* data_,int daughter,int mag, int save, 
                 char outputfile[],char datfile[],char datc[],char dir1[],char dir2[],char dir3[],char dir4[],char dir5[],char dir6[],
	       int pt,int eta, int rs,float cutLow,float cutHigh,double ptLow ,double ptHigh)
{
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
/////Minuit Options
    bool hesse = true;
    bool minos = false;

    if(pt>0)const double _start = 0.;  
    if(pt>0)const double _end = 1;//13;
    if(pt==0)const double _start = 0;
    if(pt==0)const double _end = 1;    
    RooRealVar *PID = new RooRealVar("PID","PID",_start,_end);
    RooDataHist *dataHist = new RooDataHist("dataHist","dataHist",RooArgList(*PID),data);
    RooDataHist *dataHist1 = new RooDataHist("dataHist1","dataHist1",RooArgList(*PID),data_);
    RooDataHist *dataHist_pi = new RooDataHist("dataHist_pi","dataHist_pi",RooArgList(*PID),data_pi);
    RooDataHist *dataHist_2pi = new RooDataHist("dataHist_2pi","dataHist_2pi",RooArgList(*PID),data_2pi);
    RooDataHist *dataHist_k = new RooDataHist("dataHist_k","dataHist_k",RooArgList(*PID),data_k);
    RooDataHist *dataHist_e = new RooDataHist("dataHist_e","dataHist_e",RooArgList(*PID),data_e);
    RooDataHist *dataHist_p = new RooDataHist("dataHist_p","dataHist_p",RooArgList(*PID),data_p);
//Signals
 
    RooRealVar mean1("mean1","mean1",0.7,0.,4);
    RooRealVar mean11("mean11","mean11",0.9,0.,0.5);
    RooRealVar sigma1("sigma1","sigma1",0.3,0.01,1);
    RooRealVar sigma11("sigma11","sigma11",0.3,0.01,2.2);  
    RooGaussian g1_2("g1_2","g1_2",*PID,mean11,sigma11);
    RooGaussian g1_1("g1_1","g1_1",*PID,mean1,sigma1);
    RooRealVar frac1("frac1","frac1",0.3,0.0,1);
    
    if(pt==1)RooAddPdf g1("g1","g1",g1_1,g1_2,frac1);
    //if(pt>3)RooGaussian g1("g1","g1",*PID,mean1,sigma1);
    if(1)RooBifurGauss g1("g1","g1",*PID,mean1,sigma1,sigma11);//,sigma11
    RooRealVar mean2("mean2","mean2",-0.000001,-1,4);
    RooRealVar sigma2("sigma2","sigma2",0.2,0.01,2.);  
    RooRealVar mean2_2("mean2_2","mean2_2",0,-2,1);
    RooRealVar sigma2_2("sigma2_2","sigma_2",0.4,0.01,2.);   
    RooRealVar sigma2_22("sigma2_22","sigma2_22",1,0.1,1.);
   
    RooRealVar frac2("frac2","frac2",0.3,0.0,2);
    RooRealVar frac22("frac22","frac22",0.3,0.,2);
    RooGaussian g2_1("g2_1","g2_1",*PID,mean2,sigma2);
    if(1)RooGaussian g2_2("g2_2","g2_2",*PID,mean2_2,sigma2_2);
    //if(pt<3)RooBifurGauss g2_2("g2_2","g2_2",*PID,mean2_2,sigma2_2,sigma2_22);
    if(1)RooBifurGauss g2("g2","g2",*PID,mean2,sigma2,sigma2_2);
    //RooAddPdf g2("g2","g2",g2_1,g2_2,frac2);
   
    RooRealVar mean3("mean3","mean3",-2,-3,-1);
    RooRealVar sigma3("sigma3","sigma3",0.2,0.,1.);  
    RooRealVar sigma33("sigma33","sigma33",0.2,0.0,2.);    
    RooGaussian g3("g3","g3",*PID,mean3,sigma3);  
    //RooBifurGauss g3("g3","g3",*PID,mean3,sigma3,sigma33);  
    RooRealVar mean4("mean4","mean4",-4,-7,-0.5);
    RooRealVar sigma4("sigma4","sigma4",1,0,5.); 
    RooRealVar sigma44("sigma44","sigma44",1,0,3.);    
    RooGaussian g4("g4","g4",*PID,mean4,sigma4); 

    RooRealVar mean5("mean5","mean5",4,3,5);
    RooRealVar sigma5("sigma5","sigma5",1,0.2,2.);  
    RooRealVar sigma55("sigma55","sigma55",1,0.2,2);  
    RooGaussian g5("g5","g5",*PID,mean5,sigma5); 

//Background
    RooRealVar bg1 ("bg1","bg1",-4.29529e-01,-3,.3);
    RooRealVar bg2("bg2","bg2",-9e-3,-1,.3);
    RooChebychev bgMass("bgMass","bgMass",*PID,RooArgList(bg1));
 
    RooProdPdf e_signal("e_signal","e_signal",g1);
    RooProdPdf pi_signal("pi_signal","pi_signal",g2);
    RooProdPdf pi2_signal("pi2_signal","pi2_signal",g5);
    RooProdPdf k_signal("k_signal","k_signal",g3);
    RooProdPdf p_signal("p_signal","p_signal",g4);

  
    RooRealVar e_signal_yield("e_signal_yield","e_signal_yield",100,1,1000000000);
    RooRealVar pi_signal_yield("pi_signal_yield","pi_signal_yield",100,1,1000000000);
    RooRealVar pi_signal_yield_2("pi_signal_yield_2","pi_signal_yield_2",010,010,1000000000);
    RooRealVar pi2_signal_yield("pi2_signal_yield","pi2_signal_yield",10,0,1000000000);

    RooRealVar k_signal_yield("k_signal_yield","k_signal_yield",0000,000,1000000000);
    RooRealVar p_signal_yield("p_signal_yield","p_signal_yield",000,0,1000000000);

    RooRealVar e_signal_yield_cont("e_signal_yield_cont","e_signal_yield_cont",1000,0,1000000000);
    RooRealVar pi_signal_yield_cont("pi_signal_yield_cont","pi_signal_yield_cont",1000,0,1000000000);
    RooRealVar pi_signal_yield_cont_2("pi_signal_yield_cont_2","pi_signal_yield_cont_2",1000,0,1000000000);
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
    //if(pt!=7)shapeList.add(g2_2);
    //if(pt<6)shapeList.add(pi2_signal);
    //if(pt<8 && pt>2)shapeList.add(k_signal);
    //if(0)shapeList.add(p_signal);
   
    yieldList.add(e_signal_yield);
    yieldList.add(pi_signal_yield);
    //if(pt!=7)yieldList.add(pi_signal_yield_2);
    //if(pt<6)yieldList.add(pi2_signal_yield);
    //if(pt<8 && pt>2)yieldList.add(k_signal_yield);
    //if(0)yieldList.add(p_signal_yield);

    shapeList_pi.add(pi_signal);
    yieldList_pi.add(pi_signal_yield_cont);
    //shapeList_pi.add(g2_2);
    //yieldList_pi.add(pi_signal_yield_cont_2);
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
    //PID->setRange("range_e",-1.7,1.5);
    PID->setRange("range_e",-3,3);
    RooAbsReal *nllData_e  = completePDF_e.createNLL(*dataHist_e,Extended(kTRUE),Range("range_e"));
    RooAddition * nll_e = new RooAddition("nll_e","nll_e",RooArgSet(*nllData_e));  
    RooMinuit m_e (*nll_e);
    m_e.setVerbose(kFALSE);
    m_e.migrad();

    //mean1.setConstant();
    //sigma1.setConstant();
    sigma1.setRange(sigma1.getVal()-sigma1.getError(),sigma1.getVal()+sigma1.getError());
    sigma11.setRange(sigma11.getVal()-sigma11.getError(),sigma11.getVal()+sigma11.getError());
    mean1.setRange(mean1.getVal()-mean1.getError(),mean1.getVal()+mean1.getError());
    mean11.setRange(mean11.getVal()-mean11.getError(),mean11.getVal()+mean11.getError());
    frac1.setRange(frac1.getVal()-frac1.getError(),frac1.getVal()+frac1.getError());  
    //PID->setRange("range_pi",-3,-0.1);
    //if(pt<3)PID->setRange("range_pi",-2.5,1.5); 
    //if(pt>7)PID->setRange("range_pi",-2.5,0); 
        
    RooAbsReal *nllData_pi  = completePDF_pi.createNLL(*dataHist_pi,Extended(kTRUE));
    RooAddition * nll_pi = new RooAddition("nll_pi","nll_pi",RooArgSet(*nllData_pi));  
    RooMinuit m_pi (*nll_pi);
    m_pi.setVerbose(kFALSE);
    m_pi.migrad();


    //mean2.setConstant();
    //sigma2.setConstant();
    //if(pt!=0){
    sigma2.setRange(sigma2.getVal()-sigma2.getError(),sigma2.getVal()+sigma2.getError());
    sigma2_22.setRange(sigma2_22.getVal()-sigma2_22.getError(),sigma2_22.getVal()+sigma2_22.getError());
    mean2.setRange(mean2.getVal()-mean2.getError(),mean2.getVal()+mean2.getError());
    sigma2_2.setRange(sigma2_2.getVal()-sigma2_2.getError(),sigma2_2.getVal()+sigma2_2.getError());
    mean2_2.setRange(mean2_2.getVal()-mean2_2.getError(),mean2_2.getVal()+mean2_2.getError());    
/*
    PID->setRange("range_2pi",2.5,7);  
    RooAbsReal *nllData_2pi  = completePDF_2pi.createNLL(*dataHist_2pi,Extended(kTRUE),Range("range_2pi"));
    RooAddition * nll_2pi = new RooAddition("nll_2pi","nll_2pi",RooArgSet(*nllData_2pi));  
    RooMinuit m_2pi (*nll_2pi);
    m_2pi.setVerbose(kFALSE);
    //m_2pi.migrad();

    //mean5.setConstant();
    //sigma5.setConstant();

    PID->setRange("range_k",-4,0);
    //if(pt<8)PID->setRange("range_k",-13,-6);
    RooAbsReal *nllData_k  = completePDF_k.createNLL(*dataHist_k,Extended(kTRUE),Range("range_k"));
    RooAddition * nll_k = new RooAddition("nll_k","nll_k",RooArgSet(*nllData_k));  
    RooMinuit m_k (*nll_k);
    m_k.setVerbose(kFALSE);
    m_k.migrad();

    //sigma3.setConstant();
    //mean3.setConstant();
    //if(pt!=9)sigma3.setRange(sigma3.getVal()-sigma3.getError(),sigma3.getVal()+sigma3.getError());
    //mean3.setRange(mean3.getVal()-mean3.getError(),mean3.getVal()+mean3.getError());
    PID->setRange("range_p",-4,0); 

    RooAbsReal *nllData_p  = completePDF_p.createNLL(*dataHist_p,Extended(kTRUE),Range("range_p"));
    RooAddition * nll_p = new RooAddition("nll_p","nll_p",RooArgSet(*nllData_p));  
    RooMinuit m_p (*nll_p);
    m_p.setVerbose(kFALSE);
    m_p.migrad();

    //mean4.setConstant();
    //sigma4.setConstant();
    sigma4.setRange(sigma4.getVal()-sigma4.getError()*2,sigma4.getVal()+sigma4.getError()*2);
    mean4.setRange(mean4.getVal()-mean4.getError()*2,mean4.getVal()+mean4.getError()*2);

    if(data_p->GetEntries()<5){
	p_signal_yield.setVal(0);
	p_signal_yield.setConstant(1);
    }
    if(data_k->GetEntries()<10){
	k_signal_yield.setVal(0);
	k_signal_yield.setConstant(1);
      
	}
    if(0){//data_2pi->GetEntries()<5){
	pi2_signal_yield.setVal(0);
	if(pt<5)pi2_signal_yield.setConstant(1);
	mean5.setConstant(0);
	sigma5.setConstant(0);
    }
//Now fit All Data
*/
    PID->setRange("range",0.,2);
    //if(pt<4)PID->setRange("range",-4.5,5); 
    //if(pt>6)PID->setRange("range",-3.5,5); 
    //if(pt>7)PID->setRange("range",-2.,5); 
    //if(pt==0)PID->setRange("range",-13,5);    
    RooAbsReal *nllData = completePDF.createNLL(*dataHist,Extended(kTRUE),Range("range"));
    RooAddition * nll = new RooAddition("nll","nll",RooArgSet(*nllData));  
    RooMinuit m (*nll);
    m.setVerbose(kFALSE);
    m.migrad();
    if(hesse)m.hesse();
    if(minos)m.minos();
    // Construct plotables // Don't change anything from hear on unless you want to change how a plot looks or what is output below
    RooPlot *PIDFrame_e = PID->frame();
    dataHist_e->plotOn(PIDFrame_e,Name("HistM1"));
    completePDF_e.plotOn(PIDFrame_e,Name("e_Curve"));
    RooPlot *PIDFrame_pi = PID->frame();
    dataHist_pi->plotOn(PIDFrame_pi,Name("HistM2"));
    completePDF_pi.plotOn(PIDFrame_pi,Name("pi_Curve"));
    //completePDF_pi.plotOn(PIDFrame_pi,Components(RooArgSet(pi_signal)),LineStyle(6),LineColor(kRed),FillColor(kGreen-2));
    //completePDF_pi.plotOn(PIDFrame_pi,Components(RooArgSet(g2_2)),LineStyle(6),LineColor(kRed),FillColor(kGreen-2));
    /*RooPlot *PIDFrame_2pi = PID->frame();
    dataHist_2pi->plotOn(PIDFrame_2pi,Name("HistM"));
    completePDF_2pi.plotOn(PIDFrame_2pi,Name("pi2_Curve"));
    RooPlot *PIDFrame_k = PID->frame();
    dataHist_k->plotOn(PIDFrame_k,Name("HistM"));
    completePDF_k.plotOn(PIDFrame_k,Name("k_Curve"));
    if(pt>3)completePDF_k.plotOn(PIDFrame_k,Components(RooArgSet(k_signal)),LineStyle(6),LineColor(kRed),FillColor(kGreen-2));
    //if(pt>3)completePDF_k.plotOn(PIDFrame_k,Components(RooArgSet(p_signal)),LineStyle(6),LineColor(kMagenta),FillColor(kGreen-2));
    RooPlot *PIDFrame_p = PID->frame();
    dataHist_p->plotOn(PIDFrame_p,Name("HistM"));
    completePDF_p.plotOn(PIDFrame_p,Name("p_Curve"));
   */
    RooPlot *PIDFrame = PID->frame();
    dataHist->plotOn(PIDFrame,Name("HistM"));
    //dataHistws->plotOn(PIDFrame,Name("HistMws"),LineStyle(1),LineColor(15),FillColor(17),FillStyle(1000));
    completePDF.plotOn(PIDFrame,Name("PID_Curve"));
    completePDF.plotOn(PIDFrame,Components(RooArgSet(e_signal)),LineStyle(7),LineColor(kGreen-2),FillColor(kGreen-2),FillStyle(3007));
    completePDF.plotOn(PIDFrame,Components(RooArgSet(pi_signal)),LineStyle(6),LineColor(kRed),FillColor(kGreen-2));
    dataHist->plotOn(PIDFrame,Name("HistM"));
    RooHist* pullHisto = PIDFrame->pullHist("HistM","PID_Curve");
    RooPlot* pullPlot = PID->frame();
    pullHisto->SetFillColor(1);
    pullHisto->SetLineColor(0);
    pullPlot->addPlotable(pullHisto,"B");
    RooArgSet *freeparam = completePDF.getParameters(dataHist);
    int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
    TPaveText* txt = new TPaveText(0.65,0.67,0.87,0.85,"BRNDC");
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
    double yields_errors[5];
    yields[0]=(int)e_signal_yield.getVal();
    yields[1]=(int)pi_signal_yield.getVal();

    yields_errors[0]=(int)TMath::Max(fabs(e_signal_yield.getErrorLo()),e_signal_yield.getErrorHi());
    yields_errors[1]=(int)TMath::Max(fabs(pi_signal_yield.getErrorLo()),pi_signal_yield.getErrorHi());
 
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
            output << yields[0] <<" "<< yields_errors[0] << " "<< yields[1] <<" "<< yields_errors[1] << " ";
            output << "\n";
            output <<"MassChi2"<< chi2 <<"\n";
            output.close();
        }else(cout << "Error Opening Output File!");
    }

    PID->setRange("range1",0.45,2);
    RooAbsReal* e1_1 = g1.createIntegral(*PID,*PID,"range1");
    RooAbsReal* had1_1 = g2.createIntegral(*PID,*PID,"range1");


    double pur1 = e1_1->getVal()*yields[0] / (e1_1->getVal()*yields[0]  + had1_1->getVal()*yields[1]) ;
    double eff =  e1_1->getVal() ; 
    cout << endl;
    cout << "Purity of main cuts " << pur1 << endl;


    cout << endl;
    if (save==1){
        ofstream output1 (datfile,ios::app);
        if(output1.is_open()){
            output1 <<  pt <<" " <<  yields[0] <<" "<< yields_errors[0] << " " << pur1  << " " << eff << "\n";
            output1.close();
        }else(cout << "Error Opening Output Dat File!");    
    }
    cout << "Chi2 of Mass Fit: " << chi2 << endl;
    cout<< "Yields: \n";
    //cout<<"electrons: "<< yields[0] <<" +/- " << yields_errors[0] << " " << e1_1->getVal() <<endl;
    //cout<<"pions: "<< yields[1] <<" +/- " << yields_errors[1] << " " << had1_1->getVal() << endl;
   
  


    data->GetXaxis()->SetRangeUser(-5,5);
    //PIDFrame->SetMaximum(data->GetMaximum()*1.4);
    TCanvas *c1 = new TCanvas("c1","full fit");
    prettycanvasAll2_r(c1,PIDFrame,pullPlot,0); 
    TCanvas *c2 = new TCanvas("c2","e fit");
    prettycanvasAll2_r(c2,PIDFrame_e,pullPlot,0); 
    TCanvas *c3 = new TCanvas("c3","pi fit");
    prettycanvasAll2_r(c3,PIDFrame_pi,pullPlot,0);  
    //if(pt==0)prettycanvasAll_r(c1,PIDFrame,pullPlot,1);    
 
   
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


