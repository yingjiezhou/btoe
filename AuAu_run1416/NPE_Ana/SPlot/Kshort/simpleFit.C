/////////////////////////////////////////////////////////////////////////
// SPlot for NPE analysis
// author: Matthew Kelsey
// date Aug. 7 
/////////////////////////////////////////////////////////////////////////

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "TCanvas.h"
#include "RooAbsPdf.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
// use this order for safety on library loading
using namespace RooFit ;
void simpleFit()
{

    char dFile[500];
    sprintf(dFile,"../../production/NPE.root");
    TFile *f_D = new TFile(dFile);
    TChain *t = f_D->Get("JPsi"); 

    // set range of observable
    Double_t lowRange = 2.6, highRange = 3.5;
    // make a RooRealVar for the observables
    RooRealVar *JPsi_M = new RooRealVar("JPsi_M", "M_{ee}", lowRange, highRange,"GeV");

    TH1F *h1 = new TH1F("h1","h1",30,lowRange, highRange);
    t->Project("h1","JPsi_M","probe_charge*tag_charge<0 && probe_mva>0.12 && tag_mva>0.12 && pair_dca<0.005");
    //t->Project("h1","JPsi_M","probe_charge*tag_charge<0 && pair_dca<0.005&& probe_nsige<2 && probe_nsige>-1 && abs(1/probe_beta-1)<0.025 && abs(1/tag_beta-1)<0.025  &&  probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
    RooDataHist* data = new RooDataHist("data","data",RooArgList(*JPsi_M),h1);

    RooRealVar m1("m1", "JPsi Mass", 3.1, 3.0, 3.15);
    RooRealVar sigma1("sigma1", "sigma1", 0.05,0.001,0.08,"GeV");
    RooGaussian myModel("myModel", "g1", *JPsi_M, m1, sigma1);
    RooRealVar sigma2("sigma2", "sigma2", 0.01,0.001,0.06,"GeV");
    RooRealVar frac1("frac1","frac1",0.3,0,1);
    RooGaussian g2("g2", "g2", *JPsi_M, m1, sigma2);
    //RooAddPdf myModel("myModel", "myModel",g1,g2,frac1);
    RooRealVar bg1 ("bg1","bg1",-4.29529e-01,-10,.3);
    RooRealVar bg2("bg2","bg2",-9e-3,-1,.3);
    RooRealVar bg3("bg3","bg3",-9e-6,-0.1,.001);
    //RooExponential bkgModel("bkgModel","bkgModel",*JPsi_M,bg1);
    //RooPolynomial bkgModel("bkgModel","bkgModel",*JPsi_M,RooArgList(bg1));
    RooChebychev bkgModel("bkgModel","bkgModel",*JPsi_M,RooArgList(bg1,bg2,bg3));
    RooRealVar Yield("Yield","fitted yield",50 ,10.,100000) ;
    RooRealVar bkgYield("bkgYield","bkg fitted yield",50 ,0.,100000) ;
    // now make the combined model
    std::cout << "make full model" << std::endl;
    RooAddPdf model("model","model",
		    RooArgList(myModel,bkgModel), 
		    RooArgList(Yield,bkgYield));

    model.fitTo(*data, Extended() );

    gROOT->ProcessLine(".x ~/myStyle.C");
  
    TCanvas* c1 = new TCanvas("c1","");
  
    RooPlot* frame = JPsi_M->frame(); 
    data->plotOn(frame ) ; 
    //data_WS->plotOn(frame,Bins(50),Name("Histws"),LineStyle(1),LineColor(15),FillColor(17),FillStyle(3007));       
    model.plotOn(frame) ;   
    model.plotOn(frame,Components(myModel),LineStyle(kDashed), LineColor(kGreen-2),Normalization(1.0,RooAbsReal::RelativeExpected)) ;   
    model.plotOn(frame,Components(bkgModel),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;   
    frame->Draw() ;
}
