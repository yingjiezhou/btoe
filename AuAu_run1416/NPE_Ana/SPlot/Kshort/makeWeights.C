/////////////////////////////////////////////////////////////////////////
// SPlot for NPE analysis
// author: Matthew Kelsey
// date Jan. 2 2019 
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
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
    char dFile[500];


    sprintf(dFile,"../../production/NPE_Tuples_TuneB10.root");//B4
    //sprintf(dFile,"../Ks.root");
    TFile *f_D = new TFile(dFile);
    TTree *t = f_D->Get("Ks");
   
 
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
  Double_t lowRange = 0.45, highRange = 0.55;
  // make a RooRealVar for the observables
  RooRealVar Ks_M("Ks_M", "M_{#pi#pi}", lowRange, highRange,"GeV");
  /////////////////////////////////////////////
  std::cout << "make model" << std::endl;
  // mass model for Z
  RooRealVar m1("m1", "Ks Mass", 0.5, 0.4, 0.6);
  RooRealVar sigma1("sigma1", "sigma1",1.79168e-03 ,0.0005,0.01,"GeV");
  RooGaussian g1("g1", "g1", Ks_M, m1, sigma1);
  RooRealVar sigma2("sigma2", "sigma2", 3.45766e-03,0.0005,0.01,"GeV");
  RooRealVar frac1("frac1","frac1",2.16494e-01,0,1);
  RooGaussian g2("g2", "g2", Ks_M, m1, sigma2);
  // make the combined model
  RooAddPdf myModel("myModel", "myModel",g1,g2,frac1);
  RooRealVar bg1 ("bg1","bg1",0,-100,100);
  RooRealVar bg2("bg2","bg2",-9e-3,-100,100);
  RooRealVar bg3("bg3","bg3",-9e-6,-10,10);
  //RooExponential bkgModel("bkgModel","bkgModel",Ks_M,bg1);
  RooPolynomial bkgModel("bkgModel","bkgModel",Ks_M,RooArgList(bg1,bg2,bg3));
  //RooChebychev bkgModel("bkgModel","bkgModel",Ks_M,RooArgList(bg1,bg2));

  RooRealVar Yield("Yield","fitted yield",50 ,10.,10000000) ;
  RooRealVar bkgYield("bkgYield","bkg fitted yield",50 ,0.,10000000) ;
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
    RooRealVar* Ks_M = ws->var("Ks_M");  
    RooRealVar probe_p("probe_p", "probe_p", -1e10, 1e10);
    RooRealVar probe_pt("probe_pt", "probe_pt", -1e10, 1e10);
    RooRealVar probe_emc0("probe_emc0", "probe_emoc0", -1e10, 1e10);
    RooRealVar probe_beta("probe_beta", "probe_beta", -1e10, 1e10);
    RooRealVar probe_neta("probe_neta", "probe_neta", -1e10, 1e10);
    RooRealVar probe_nphi("probe_nphi", "probe_nphi", -1e10, 1e10);
    RooRealVar probe_zdist("probe_zdist", "probe_zdist", -1e10, 1e10);
    RooRealVar probe_phidist("probe_phidist", "probe_phidist", -1e10, 1e10);
    RooRealVar probe_nsige("probe_nsige", "probe_nsige", -13, 13);
    RooRealVar probe_nsigpi("probe_nsigpi", "probe_nsigpi", -13, 13);
    RooRealVar probe_charge("probe_charge", "probe_charge", -1,1);
    RooRealVar tag_charge("tag_charge", "tag_charge", -1,1); 
    RooRealVar tag_trigger("tag_trigger", "tag_trigger", -1,1);  
    RooRealVar Ks_triggercat("Ks_triggercat", "Ks_triggercat", 0,10); 
    RooRealVar tag_mva("tag_mva", "tag_mva", -1,1);  
    RooRealVar tag_p("tag_p", "tag_p", -1,1);  
    RooRealVar probe_mva("probe_mva", "probe_mva", -1,1);  
    RooRealVar pair_dca("pair_dca", "pair_dca", -1,1);  

    RooArgSet* variables = new RooArgSet();
    variables->add(*Ks_M);
    variables->add(probe_p);
    variables->add(probe_pt);
    variables->add(probe_emc0);
    variables->add(probe_beta);
    variables->add(probe_neta);
    variables->add(probe_nphi);
    variables->add(probe_zdist);
    variables->add(probe_phidist);
    variables->add(probe_nsige);
    variables->add(probe_nsigpi);
    variables->add(probe_charge);
    variables->add(tag_charge);
    variables->add(tag_p);
    variables->add(Ks_triggercat);
    //variables->add(tag_trigger);
    //variables->add(tag_mva);
    //variables->add(probe_mva);
    //variables->add(pair_dca);
    RooDataSet* data = new RooDataSet("data","data",*variables,Import(*t),Cut("probe_charge*tag_charge<0")) ; // && Ks_M>0.45 && Ks_M<0.55
    //RooDataSet* data_WS = new RooDataSet("data_WS","data_WS",*variables,Import(*t),Cut("probe_charge*tag_charge>0")) ; 
    // import data into workspace
    ws->import(*data, Rename("data"));
    //ws->import(*data_WS, Rename("data_WS"));
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
  RooRealVar* sigma2 = ws->var("sigma2"); 
  RooRealVar* m1 = ws->var("m1"); 
  RooRealVar* frac1 = ws->var("frac1"); 
  RooRealVar* bg1 = ws->var("bg1"); 
  RooRealVar* bg2 = ws->var("bg2"); 
  RooRealVar* bg3 = ws->var("bg3"); 
  sigma1->setConstant();
  sigma2->setConstant();
  m1->setConstant();
  frac1->setConstant();
  bg1->setConstant();
  bg2->setConstant();
  bg3->setConstant();
  RooMsgService::instance().setSilentMode(true);

  // Now we use the SPlot class to add SWeights to our data set
  // based on our model and our yield variables
  RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot",
		            *data, model, RooArgList(*Yield,*bkgYield) );

  // Check that our weights have the desired properties

  std::cout << "Check SWeights:" << std::endl;


  std::cout << std::endl <<  "Yield of Ks is " 
	    << Yield->getVal() << ".  From sWeights it is "
	    << sData->GetYieldFromSWeight("Yield") << std::endl;


  std::cout << "Yield of BKG is " 
	    << bkgYield->getVal() << ".  From sWeights it is "
	    << sData->GetYieldFromSWeight("bkgYield") << std::endl
	    << std::endl;

  for(Int_t i=0; i < 10; i++)
    {
      std::cout << "Ks Weight   " << sData->GetSWeight(i,"Yield") 
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
    RooRealVar* Ks_M = ws->var("Ks_M");

    // note, we get the dataset with sWeights
    RooDataSet* data = (RooDataSet*) ws->data("dataWithSWeights");
    //RooDataSet* data_WS = (RooDataSet*) ws->data("data_WS");
    model->fitTo(*data, Extended() );

    TCanvas* cdata = new TCanvas("sPlot","sPlot");
    //cdata->Divide(1,3); 
    cdata->cd(1);
    RooPlot* frame = Ks_M->frame(Bins(100)) ; 
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
    TTree* Ks_tree_sw = new TTree("Ks_tree_sw","Ks_tree_sw");//tree->CloneTree(0);
    float weight;
    float bkgweight;
    float mass;
    float pt;
    float p;
    float emc0;
    float nphi;
    float neta;
    float p_tag;
    float charge;
    float beta;
    float nsige;
    float nsigpi;
    float zdist;
    float phidist;
    float trig;
    Ks_tree_sw->Branch("Ks_M",&mass,"Ks_M/F") ;
    Ks_tree_sw->Branch("Ks_triggercat",&trig,"Ks_triggercat/F") ;
    Ks_tree_sw->Branch("sWeight",&weight,"sWeight/F") ;
    Ks_tree_sw->Branch("sWeight_bkg",&bkgweight,"sWeight_bkg/F") ;
    Ks_tree_sw->Branch("probe_pt",&pt,"probe_pt/F") ;
    Ks_tree_sw->Branch("probe_p",&p,"probe_p/F") ;
    Ks_tree_sw->Branch("tag_p",&p_tag,"tag_p/F") ;
    Ks_tree_sw->Branch("probe_emc0",&emc0,"probe_emc0/F") ;
    Ks_tree_sw->Branch("probe_nphi",&nphi,"probe_nphi/F") ;
    Ks_tree_sw->Branch("probe_neta",&neta,"probe_neta/F") ;
    Ks_tree_sw->Branch("probe_charge",&charge,"probe_charge/F") ;
    Ks_tree_sw->Branch("probe_beta",&beta,"probe_beta/F") ;
    Ks_tree_sw->Branch("probe_nsige",&nsige,"probe_nsige/F") ;
    Ks_tree_sw->Branch("probe_nsigpi",&nsigpi,"probe_nsigpi/F") ;
    Ks_tree_sw->Branch("probe_zdist",&zdist,"probe_zdist/F") ;
    Ks_tree_sw->Branch("probe_phidist",&phidist,"probe_phidist/F") ;
    data->get()->Print();
    RooRealVar* Yield_sw = ws->var("Yield_sw");
    RooRealVar* bkgYield_sw = ws->var("bkgYield_sw");
    RooRealVar* Ks_M = ws->var("Ks_M");
    RooRealVar* Ks_triggercat = ws->var("Ks_triggercat");
    RooRealVar* probe_pt = ws->var("probe_pt");
    RooRealVar* probe_p = ws->var("probe_p");
    RooRealVar* tag_p = ws->var("tag_p");
    RooRealVar* probe_zdist = ws->var("probe_zdist");
    RooRealVar* probe_phidist = ws->var("probe_phidist");
    RooRealVar* probe_emc0 = ws->var("probe_emc0");
    RooRealVar* probe_nphi = ws->var("probe_nphi");
    RooRealVar* probe_neta = ws->var("probe_neta");
    RooRealVar* probe_charge = ws->var("probe_charge");
    RooRealVar* probe_beta = ws->var("probe_beta");
    RooRealVar* probe_nsige = ws->var("probe_nsige");
    RooRealVar* probe_nsigpi = ws->var("probe_nsigpi");
    RooArgSet* set;
    for (int i=0 ; i< data->sumEntries() ; i++) {
	row = (RooArgSet*)data->get(i);	
	Yield_sw = (RooRealVar*)row->find(Yield_sw->GetName());	
	weight = Yield_sw->getVal();
	bkgYield_sw = (RooRealVar*)row->find(bkgYield_sw->GetName());	
	bkgweight = bkgYield_sw->getVal();
	Ks_M = (RooRealVar*)row->find(Ks_M->GetName());	
	mass = Ks_M->getVal();
	Ks_triggercat = (RooRealVar*)row->find(Ks_triggercat->GetName());	
	trig = Ks_triggercat->getVal();
	probe_pt = (RooRealVar*)row->find(probe_pt->GetName());
	pt = probe_pt->getVal();
	probe_p = (RooRealVar*)row->find(probe_p->GetName());
	p = probe_p->getVal();
	tag_p = (RooRealVar*)row->find(tag_p->GetName());
	p_tag = tag_p->getVal();
	probe_emc0 = (RooRealVar*)row->find(probe_emc0->GetName());
	emc0 = probe_emc0->getVal();
        probe_zdist = (RooRealVar*)row->find(probe_zdist->GetName());
        zdist = probe_zdist->getVal();
        probe_phidist = (RooRealVar*)row->find(probe_phidist->GetName());
        phidist = probe_phidist->getVal();
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
	probe_nsigpi = (RooRealVar*)row->find(probe_nsigpi->GetName());
	nsigpi = probe_nsigpi->getVal();
	//cout << weight <<  " " <<  Yield_sw->getVal() << endl;
	//if(weight>0)
	Ks_tree_sw->Fill();
    }

    Ks_tree_sw->Write();
    out.Close();
    out.Delete(); 
}



