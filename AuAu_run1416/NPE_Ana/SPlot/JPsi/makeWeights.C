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
using namespace RooStats ;

// see below for implementation
void AddModel(RooWorkspace*);
void AddData(RooWorkspace*, TTree*);
void DoSPlot(RooWorkspace*);
void MakePlots(RooWorkspace*);
void Write(RooWorkspace*, TTree*);
void makeWeights()
{

    char dFile[500];
    sprintf(dFile,"../../production/NPE.root");
    TFile *f_D = new TFile(dFile);
    TTree *t = f_D->Get("JPsi");

    // Create a new workspace to manage the project.
    RooWorkspace* wspace = new RooWorkspace("myWS");

    // add the signal and background models to the workspace.
    // Inside this function you will find a discription our model.
    AddModel(wspace);

    // add some toy data to the workspace
    AddData(wspace,t);

    // inspect the workspace if you wish
    //  wspace->Print();

    // do sPlot.  
    //This wil make a new dataset with sWeights added for every event.
    DoSPlot(wspace,t);

    // Make some plots showing the discriminating variable and 
    // the control variable after unfolding.
    MakePlots(wspace);
    Write(wspace,t);
    // cleanup
    delete wspace;
  
}

 
//____________________________________
void AddModel(RooWorkspace* ws){

  // set range of observable
  Double_t lowRange = 2.5, highRange = 3.5;

  // make a RooRealVar for the observables
  RooRealVar JPsi_M("JPsi_M", "M_{ee}", lowRange, highRange,"GeV");

  //RooRealVar isolation("isolation", "isolation", 0., 20., "GeV");

  /////////////////////////////////////////////
  // make 2-d model for Z including the invariant mass 
  // distribution  and an isolation distribution which we want to
  // unfold from QCD.
  std::cout << "make model" << std::endl;
  // mass model for Z
  RooRealVar m1("m1", "JPsi Mass", 3.1, 3.0, 3.15);
  RooRealVar sigma1("sigma1", "sigma1", 0.05,0.001,0.08,"GeV");
  RooGaussian myModel("myModel", "g1", JPsi_M, m1, sigma1);
  RooRealVar sigma2("sigma2", "sigma2", 0.01,0.001,0.06,"GeV");
  RooRealVar frac1("frac1","frac1",0.3,0,1);
  RooGaussian g2("g2", "g2", JPsi_M, m1, sigma2);
  // make the combined model
  //RooAddPdf myModel("myModel", "myModel",g1,g2,frac1);
  RooRealVar bg1 ("bg1","bg1",-4.29529e-01,-10,.3);
  RooRealVar bg1 ("bg1","bg1",-4.29529e-01,-10,.3);
  RooRealVar bg2("bg2","bg2",-9e-3,-1,.3);
  RooRealVar bg3("bg3","bg3",-9e-6,-0.001,.001);
  //RooExponential bkgModel("bkgModel","bkgModel",JPsi_M,bg1);
  RooPolynomial bkgModel("bkgModel","bkgModel",JPsi_M,RooArgList(bg1));

  RooRealVar Yield("Yield","fitted yield",50 ,10.,100000) ;
  RooRealVar bkgYield("bkgYield","bkg fitted yield",50 ,0.,100000) ;
  // now make the combined model
  std::cout << "make full model" << std::endl;
  RooAddPdf model("model","model",
		  RooArgList(myModel,bkgModel), 
		  RooArgList(Yield,bkgYield));


  std::cout << "import model" << std::endl;

  ws->import(model);
}

//____________________________________
void AddData(RooWorkspace* ws, TTree* t){
    std::cout << "make data set and import to workspace" << std::endl;
    RooRealVar* JPsi_M = ws->var("JPsi_M");  
    RooRealVar probe_p("probe_p", "probe_p", -1e10, 1e10);
    RooRealVar probe_pt("probe_pt", "probe_pt", -1e10, 1e10);
    RooRealVar probe_emc0("probe_emc0", "probe_emoc0", -1e10, 1e10);
    RooRealVar probe_beta("probe_beta", "probe_beta", -1e10, 1e10);
    RooRealVar probe_neta("probe_neta", "probe_neta", -1e10, 1e10);
    RooRealVar probe_nphi("probe_nphi", "probe_nphi", -1e10, 1e10);
    RooRealVar probe_nsige("probe_nsige", "probe_nsige", -13, 13);
    RooRealVar probe_charge("probe_charge", "probe_charge", -1,1);
    RooRealVar tag_charge("tag_charge", "tag_charge", -1,1); 
    RooRealVar tag_trigger("tag_trigger", "tag_trigger", -1,1);  

    RooRealVar tag_mva("tag_mva", "tag_mva", -1,1);  
    RooRealVar probe_mva("probe_mva", "probe_mva", -1,1);  
    RooRealVar pair_dca("pair_dca", "pair_dca", -1,1);  

    RooArgSet* variables = new RooArgSet();
    variables->add(*JPsi_M);
    variables->add(probe_p);
    variables->add(probe_pt);
    variables->add(probe_emc0);
    variables->add(probe_beta);
    variables->add(probe_neta);
    variables->add(probe_nphi);
    variables->add(probe_nsige);
    variables->add(probe_charge);
    variables->add(tag_charge);
    variables->add(tag_trigger);
    variables->add(tag_mva);
    variables->add(probe_mva);
    variables->add(pair_dca);
    RooDataSet* data = new RooDataSet("data","data",*variables,Import(*t),Cut("tag_trigger>0 && probe_charge*tag_charge<0 && probe_mva>0.15 && tag_mva>0.15 && pair_dca<0.005")) ; 
    RooDataSet* data_WS = new RooDataSet("data_WS","data_WS",*variables,Import(*t),Cut("probe_charge*tag_charge>0&& probe_mva>0.15 && tag_mva>0.15 && pair_dca<0.005")) ; 
    // import data into workspace
    ws->import(*data, Rename("data"));
    ws->import(*data_WS, Rename("data_WS"));
}

//____________________________________
void DoSPlot(RooWorkspace* ws,TTree *tree){
  std::cout << "Calculate sWeights" << std::endl;

  // get what we need out of the workspace to do the fit
  RooAbsPdf* model = ws->pdf("model");
  RooRealVar* Yield = ws->var("Yield");
  RooRealVar* bkgYield = ws->var("bkgYield");
  RooDataSet* data = (RooDataSet*) ws->data("data");

  // fit the model to the data.
  model->fitTo(*data, Extended() );

  // The sPlot technique requires that we fix the parameters
  // of the model that are not yields after doing the fit.
  RooRealVar* sigma1 = ws->var("sigma1"); 
  //RooRealVar* sigma2 = ws->var("sigma2"); 
  RooRealVar* m1 = ws->var("m1"); 
  //RooRealVar* frac1 = ws->var("frac1"); 
  RooRealVar* bg1 = ws->var("bg1"); 
  //RooRealVar* bg2 = ws->var("bg2"); 
  //RooRealVar* bg3 = ws->var("bg3"); 
  sigma1->setConstant();
  //sigma2->setConstant();
  m1->setConstant();
  //frac1->setConstant();
  bg1->setConstant();
  //bg2->setConstant();
  //bg3->setConstant();
  RooMsgService::instance().setSilentMode(true);

  // Now we use the SPlot class to add SWeights to our data set
  // based on our model and our yield variables
  RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot",
		            *data, model, RooArgList(*Yield,*bkgYield) );

  // Check that our weights have the desired properties

  std::cout << "Check SWeights:" << std::endl;


  std::cout << std::endl <<  "Yield of JPsi is " 
	    << Yield->getVal() << ".  From sWeights it is "
	    << sData->GetYieldFromSWeight("Yield") << std::endl;


  std::cout << "Yield of BKG is " 
	    << bkgYield->getVal() << ".  From sWeights it is "
	    << sData->GetYieldFromSWeight("bkgYield") << std::endl
	    << std::endl;

  for(Int_t i=0; i < 10; i++)
    {
      std::cout << "JPsi Weight   " << sData->GetSWeight(i,"Yield") 
		<< "   bkg Weight   " << sData->GetSWeight(i,"bkgYield") 
	<< "  Total Weight   " << sData->GetSumOfEventSWeight(i) 
		<< std::endl;
    }

  std::cout << std::endl;

  // import this new dataset with sWeights
  std::cout << "import new dataset with sWeights" << std::endl;
  ws->import(*data, Rename("dataWithSWeights"));



 
}

void MakePlots(RooWorkspace* ws){

    gROOT->ProcessLine(".x ~/myStyle.C");
    std::cout << "make plots" << std::endl;

    RooAbsPdf* model = ws->pdf("model");
    RooAbsPdf* myModel = ws->pdf("myModel");
    RooAbsPdf* bkgModel = ws->pdf("bkgModel");
    RooRealVar* JPsi_M = ws->var("JPsi_M");

    // note, we get the dataset with sWeights
    RooDataSet* data = (RooDataSet*) ws->data("dataWithSWeights");
    RooDataSet* data_WS = (RooDataSet*) ws->data("data_WS");
    model->fitTo(*data, Extended() );

    TCanvas* cdata = new TCanvas("sPlot","sPlot");
    //cdata->Divide(1,3); 
    cdata->cd(1);
    RooPlot* frame = JPsi_M->frame(Bins(100)) ; 
    data->plotOn(frame ) ; 
    //data_WS->plotOn(frame,Bins(50),Name("Histws"),LineStyle(1),LineColor(15),FillColor(17),FillStyle(3007));       
    model->plotOn(frame) ;   
    model->plotOn(frame,Components(*model),LineStyle(kDashed), LineColor(kGreen-2),Normalization(1.0,RooAbsReal::RelativeExpected)) ;   
    model->plotOn(frame,Components(*bkgModel),LineStyle(kDashed),LineColor(kRed),Normalization(1.0,RooAbsReal::RelativeExpected)) ;   
    frame->SetTitle("Fit of model to discriminating variable");
    frame->Draw() ;
}
void Write(RooWorkspace* ws, TTree* tree){
    TFile out("out.root","RECREATE");
    RooDataSet* data = (RooDataSet*) ws->data("dataWithSWeights");
    TTree* JPsi_tree_sw = new TTree("JPsi_tree_sw","JPsi_tree_sw");//tree->CloneTree(0);
    float weight;
    float bkgweight;
    float mass;
    float pt;
    float p;
    float emc0;
    float nphi;
    float neta;
    float charge;
    float beta;
    float nsige;
    JPsi_tree_sw->Branch("JPsi_M",&mass,"JPsi_M/F") ;
    JPsi_tree_sw->Branch("sWeight",&weight,"sWeight/F") ;
    JPsi_tree_sw->Branch("sWeight_bkg",&bkgweight,"sWeight_bkg/F") ;
    JPsi_tree_sw->Branch("probe_pt",&pt,"probe_pt/F") ;
    JPsi_tree_sw->Branch("probe_p",&p,"probe_p/F") ;
    JPsi_tree_sw->Branch("probe_emc0",&emc0,"probe_emc0/F") ;
    JPsi_tree_sw->Branch("probe_nphi",&nphi,"probe_nphi/F") ;
    JPsi_tree_sw->Branch("probe_neta",&neta,"probe_neta/F") ;
    JPsi_tree_sw->Branch("probe_charge",&charge,"probe_charge/F") ;
    JPsi_tree_sw->Branch("probe_beta",&beta,"probe_beta/F") ;
    JPsi_tree_sw->Branch("probe_nsige",&nsige,"probe_nsige/F") ;

    data->get()->Print();
    RooRealVar* Yield_sw = ws->var("Yield_sw");
    RooRealVar* bkgYield_sw = ws->var("Yield_sw");
    RooRealVar* JPsi_M = ws->var("JPsi_M");
    RooRealVar* probe_pt = ws->var("probe_pt");
    RooRealVar* probe_p = ws->var("probe_p");
    RooRealVar* probe_emc0 = ws->var("probe_emc0");
    RooRealVar* probe_nphi = ws->var("probe_nphi");
    RooRealVar* probe_neta = ws->var("probe_neta");
    RooRealVar* probe_charge = ws->var("probe_charge");
    RooRealVar* probe_beta = ws->var("probe_beta");
    RooRealVar* probe_nsige = ws->var("probe_nsige");
    RooArgSet* set;
    for (int i=0 ; i< data->sumEntries() ; i++) {
	row = (RooArgSet*)data->get(i);	
	Yield_sw = (RooRealVar*)row->find(Yield_sw->GetName());	
	weight = Yield_sw->getVal();
	bkgYield_sw = (RooRealVar*)row->find(bkgYield_sw->GetName());	
	bkgweight = Yield_sw->getVal();
	JPsi_M = (RooRealVar*)row->find(JPsi_M->GetName());	
	mass = JPsi_M->getVal();
	probe_pt = (RooRealVar*)row->find(probe_pt->GetName());
	pt = probe_pt->getVal();
	probe_p = (RooRealVar*)row->find(probe_p->GetName());
	p = probe_p->getVal();
	probe_emc0 = (RooRealVar*)row->find(probe_emc0->GetName());
	emc0 = probe_emc0->getVal();
	probe_nphi = (RooRealVar*)row->find(probe_nphi->GetName());
	nphi = probe_nphi->getVal();
	probe_neta = (RooRealVar*)row->find(probe_neta->GetName());
	neta = probe_neta->getVal();
	probe_charge = (RooRealVar*)row->find(probe_charge->GetName());
	charge = probe_charge->getVal();
	probe_beta = (RooRealVar*)row->find(probe_beta->GetName());
	beta = probe_beta->getVal();
	probe_nsige = (RooRealVar*)row->find(probe_nsige->GetName());
	nsige = probe_nsige->getVal();
	//cout << weight <<  " " <<  Yield_sw->getVal() << endl;
	if(weight>0)JPsi_tree_sw->Fill();
    }

    JPsi_tree_sw->Write();
    out.Close();
    out.Delete(); 
}



