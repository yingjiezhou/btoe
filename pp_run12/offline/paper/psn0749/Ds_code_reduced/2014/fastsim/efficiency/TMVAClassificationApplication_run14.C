/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include <algorithm>
#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

#define M_PHI    1.019461
#define M_KSTAR  0.89581
#define M_DS     1.96830

using namespace TMVA;

void TMVAClassificationApplication_run14(TString fname = "Lc.root", TString myMethodList = "BDT" ) 
{   
#ifdef __CINT__
	gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

	//---------------------------------------------------------------

	// This loads the library
	TMVA::Tools::Instance();

	// Default MVA methods to be trained + tested
	std::map<std::string,int> Use;

	// --- Cut optimisation
	Use["Cuts"]            = 1;
	Use["CutsD"]           = 1;
	Use["CutsPCA"]         = 0;
	Use["CutsGA"]          = 0;
	Use["CutsSA"]          = 0;
	// 
	// --- 1-dimensional likelihood ("naive Bayes estimator")
	Use["Likelihood"]      = 1;
	Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
	Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
	Use["LikelihoodKDE"]   = 0;
	Use["LikelihoodMIX"]   = 0;
	//
	// --- Mutidimensional likelihood and Nearest-Neighbour methods
	Use["PDERS"]           = 1;
	Use["PDERSD"]          = 0;
	Use["PDERSPCA"]        = 0;
	Use["PDEFoam"]         = 1;
	Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
	Use["KNN"]             = 1; // k-nearest neighbour method
	//
	// --- Linear Discriminant Analysis
	Use["LD"]              = 1; // Linear Discriminant identical to Fisher
	Use["Fisher"]          = 0;
	Use["FisherG"]         = 0;
	Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
	Use["HMatrix"]         = 0;
	//
	// --- Function Discriminant analysis
	Use["FDA_GA"]          = 1; // minimisation of user-defined function using Genetics Algorithm
	Use["FDA_SA"]          = 0;
	Use["FDA_MC"]          = 0;
	Use["FDA_MT"]          = 0;
	Use["FDA_GAMT"]        = 0;
	Use["FDA_MCMT"]        = 0;
	//
	// --- Neural Networks (all are feed-forward Multilayer Perceptrons)
	Use["MLP"]             = 0; // Recommended ANN
	Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
	Use["MLPBNN"]          = 1; // Recommended ANN with BFGS training method and bayesian regulator
	Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
	Use["TMlpANN"]         = 0; // ROOT's own ANN
	//
	// --- Support Vector Machine 
	Use["SVM"]             = 1;
	// 
	// --- Boosted Decision Trees
	Use["BDT"]             = 0; // uses Adaptive Boost
	Use["BDTG"]            = 0; // uses Gradient Boost
	Use["BDTB"]            = 0; // uses Bagging
	Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
	// 
	// --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
	Use["RuleFit"]         = 1;
	// ---------------------------------------------------------------
	Use["Plugin"]          = 0;
	Use["Category"]        = 0;
	Use["SVM_Gauss"]       = 0;
	Use["SVM_Poly"]        = 0;
	Use["SVM_Lin"]         = 0;

	std::cout << std::endl;
	std::cout << "==> Start TMVAClassificationApplication" << std::endl;

	// Select methods (don't look at this code - not of interest)
	if (myMethodList != "") {
		for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
		std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
		for (UInt_t i=0; i<mlist.size(); i++) {
			std::string regMethod(mlist[i]);

			if (Use.find(regMethod) == Use.end()) {
				std::cout << "Method \"" << regMethod 
					<< "\" not known in TMVA under this name. Choose among the following:" << std::endl;
				for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
					std::cout << it->first << " ";
				}
				std::cout << std::endl;
				return;
			}
			Use[regMethod] = 1;
		}
	}

	// --------------------------------------------------------------------------------------------------

	// --- Create the Reader object

	TMVA::Reader *reader_1525_010 = new TMVA::Reader( "!Color:!Silent" );    
	TMVA::Reader *reader_258_010 = new TMVA::Reader( "!Color:!Silent" );    
	TMVA::Reader *reader_125_1020 = new TMVA::Reader( "!Color:!Silent" );    
	TMVA::Reader *reader_258_1020 = new TMVA::Reader( "!Color:!Silent" );    
	TMVA::Reader *reader_125_2040 = new TMVA::Reader( "!Color:!Silent" );    
	TMVA::Reader *reader_258_2040 = new TMVA::Reader( "!Color:!Silent" );    
	TMVA::Reader *reader_158_4080 = new TMVA::Reader( "!Color:!Silent" );    

	Float_t dcaDaughters, rEta, piRDca, RDca12, dcaLcToPv, rPtpi, rPt12, rPt, massDiff, decayLength, cosTheta, k1RDca, k2RDca, rM, rY, cent, flag ;
	reader_1525_010->AddVariable( "dcaDaughters",                 &dcaDaughters );
	reader_1525_010->AddVariable( "piRDca",                &piRDca );
	reader_1525_010->AddVariable( "RDca12",             &RDca12 );
	reader_1525_010->AddVariable( "dcaLcToPv",             &dcaLcToPv );
	reader_1525_010->AddVariable( "rPtpi",             &rPtpi );
	reader_1525_010->AddVariable( "rPt12",             &rPt12 );
	reader_1525_010->AddSpectator( "rPt",   &rPt ); 
	reader_1525_010->AddSpectator( "cent",   &cent );
	reader_1525_010->AddSpectator( "rM",    &rM );
	//	reader_1525_010->AddSpectator( "rY",    &rY );
	reader_1525_010->AddSpectator( "flag",    &flag );


	reader_258_010->AddVariable( "dcaDaughters",                 &dcaDaughters );
	reader_258_010->AddVariable( "piRDca",                &piRDca );
	reader_258_010->AddVariable( "RDca12",             &RDca12 );
	reader_258_010->AddVariable( "dcaLcToPv",             &dcaLcToPv );
	reader_258_010->AddVariable( "rPtpi",             &rPtpi );
	reader_258_010->AddVariable( "rPt12",             &rPt12 );
	reader_258_010->AddSpectator( "rPt",   &rPt ); 
	reader_258_010->AddSpectator( "cent",   &cent );
	reader_258_010->AddSpectator( "rM",    &rM );
	//	reader_258_010->AddSpectator( "rY",    &rY );
	reader_258_010->AddSpectator( "flag",    &flag );


	reader_125_1020->AddVariable( "dcaDaughters",                 &dcaDaughters );
	reader_125_1020->AddVariable( "piRDca",                &piRDca );
	reader_125_1020->AddVariable( "RDca12",             &RDca12 );
	reader_125_1020->AddVariable( "dcaLcToPv",             &dcaLcToPv );
	reader_125_1020->AddVariable( "rPtpi",             &rPtpi );
	reader_125_1020->AddVariable( "rPt12",             &rPt12 );
	reader_125_1020->AddSpectator( "rPt",   &rPt ); 
	reader_125_1020->AddSpectator( "cent",   &cent );
	reader_125_1020->AddSpectator( "rM",    &rM );
	//	reader_125_1020->AddSpectator( "rY",    &rY );
	reader_125_1020->AddSpectator( "flag",    &flag );


	reader_258_1020->AddVariable( "dcaDaughters",                 &dcaDaughters );
	reader_258_1020->AddVariable( "piRDca",                &piRDca );
	reader_258_1020->AddVariable( "RDca12",             &RDca12 );
	reader_258_1020->AddVariable( "dcaLcToPv",             &dcaLcToPv );
	reader_258_1020->AddVariable( "rPtpi",             &rPtpi );
	reader_258_1020->AddVariable( "rPt12",             &rPt12 );
	reader_258_1020->AddSpectator( "rPt",   &rPt ); 
	reader_258_1020->AddSpectator( "cent",   &cent );
	reader_258_1020->AddSpectator( "rM",    &rM );
	//	reader_258_1020->AddSpectator( "rY",    &rY );
	reader_258_1020->AddSpectator( "flag",    &flag );


	reader_125_2040->AddVariable( "dcaDaughters",                 &dcaDaughters );
	reader_125_2040->AddVariable( "piRDca",                &piRDca );
	reader_125_2040->AddVariable( "RDca12",             &RDca12 );
	reader_125_2040->AddVariable( "dcaLcToPv",             &dcaLcToPv );
	reader_125_2040->AddVariable( "rPtpi",             &rPtpi );
	reader_125_2040->AddVariable( "rPt12",             &rPt12 );
	reader_125_2040->AddSpectator( "rPt",   &rPt ); 
	reader_125_2040->AddSpectator( "cent",   &cent );
	reader_125_2040->AddSpectator( "rM",    &rM );
	//	reader_125_2040->AddSpectator( "rY",    &rY );
	reader_125_2040->AddSpectator( "flag",    &flag );


	reader_258_2040->AddVariable( "dcaDaughters",                 &dcaDaughters );
	reader_258_2040->AddVariable( "piRDca",                &piRDca );
	reader_258_2040->AddVariable( "RDca12",             &RDca12 );
	reader_258_2040->AddVariable( "dcaLcToPv",             &dcaLcToPv );
	reader_258_2040->AddVariable( "rPtpi",             &rPtpi );
	reader_258_2040->AddVariable( "rPt12",             &rPt12 );
	reader_258_2040->AddSpectator( "rPt",   &rPt ); 
	reader_258_2040->AddSpectator( "cent",   &cent );
	reader_258_2040->AddSpectator( "rM",    &rM );
	//	reader_258_2040->AddSpectator( "rY",    &rY );
	reader_258_2040->AddSpectator( "flag",    &flag );

	reader_158_4080->AddVariable( "dcaDaughters",                 &dcaDaughters );
	reader_158_4080->AddVariable( "piRDca",                &piRDca );
	reader_158_4080->AddVariable( "RDca12",             &RDca12 );
	reader_158_4080->AddVariable( "dcaLcToPv",             &dcaLcToPv );
	reader_158_4080->AddVariable( "rPtpi",             &rPtpi );
	reader_158_4080->AddVariable( "rPt12",             &rPt12 );
	reader_158_4080->AddSpectator( "rPt",   &rPt ); 
	reader_158_4080->AddSpectator( "cent",   &cent );
	reader_158_4080->AddSpectator( "rM",    &rM );
	//	reader_158_4080->AddSpectator( "rY",    &rY );
	reader_158_4080->AddSpectator( "flag",    &flag );

	// --- Book the MVA methods

	TString methodName = "BDT method";
	TString weightfile_1525_010 = "/star/u/fuchuan/data02/Ds/Ds_code_GPC/BDT/Train/010_1525/run14/weights_phy_run14/TMVAClassification_BDT.weights.xml";
	reader_1525_010->BookMVA( methodName, weightfile_1525_010 ); 

	TString weightfile_258_010 = "/star/u/fuchuan/data02/Ds/Ds_code_GPC/BDT/Train/010_258/run14/weights_phy_run14/TMVAClassification_BDT.weights.xml";
	reader_258_010->BookMVA( methodName, weightfile_258_010 ); 

	TString weightfile_125_1020 = "/star/u/fuchuan/data02/Ds/Ds_code_GPC/BDT/Train/1020_125/run14/weights_phy_run14/TMVAClassification_BDT.weights.xml";
	reader_125_1020->BookMVA( methodName, weightfile_125_1020 ); 

	TString weightfile_258_1020 = "/star/u/fuchuan/data02/Ds/Ds_code_GPC/BDT/Train/1020_258/run14/weights_phy_run14/TMVAClassification_BDT.weights.xml";
	reader_258_1020->BookMVA( methodName, weightfile_258_1020 ); 

	TString weightfile_125_2040 = "/star/u/fuchuan/data02/Ds/Ds_code_GPC/BDT/Train/2040_125/run14/weights_phy_run14/TMVAClassification_BDT.weights.xml";
	//TString weightfile_125_2040 = "/star/u/fuchuan/data02/Ds/Ds_code_GPC/BDT/TrainingandApp_Ds_18_1080_long/1_2.5/weights_run14_phy_WideMass_more/TMVAClassification_BDT.weights.xml";
	reader_125_2040->BookMVA( methodName, weightfile_125_2040 ); 

	TString weightfile_258_2040 = "/star/u/fuchuan/data02/Ds/Ds_code_GPC/BDT/Train/2040_258/run14/weights_phy_run14/TMVAClassification_BDT.weights.xml";
	reader_258_2040->BookMVA( methodName, weightfile_258_2040 ); 

	TString weightfile_158_4080 = "/star/u/fuchuan/data02/Ds/Ds_code_GPC/BDT/Train/4080_158/run14/weights_phy_run14/TMVAClassification_BDT.weights.xml";
	reader_158_4080->BookMVA( methodName, weightfile_158_4080 ); 

	// Book output histograms
	UInt_t nbin = 100;
	TH1F *histBdt(0);

	if (Use["BDT"])           histBdt     = new TH1F( "MVA_BDT",           "MVA_BDT",           nbin, -0.8, 0.8 );



	// Prepare input tree (this must be replaced by your data source)
	// in this example, there is a toy tree with signal and one with background events
	// we'll later on use only the "signal" events for the test in this example.
	//   
	TFile *input(0);
	// TString fname = "./TMVAClassification.root";   
	if (!gSystem->AccessPathName( fname )) 
		input = TFile::Open( fname ); // check if file in local directory exists
	else    
		input = TFile::Open( "http://root.cern.ch/files/tmva_class_example.root" ); // if not: download from ROOT server

	if (!input) {
		std::cout << "ERROR: could not open data file" << std::endl;
		exit(1);
	}
	std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

	// --- Event loop

	// Prepare the event tree
	// - here the variable names have to corresponds to your tree
	// - you can use the same variables as above which is slightly faster,
	//   but of course you can use different ones and copy the values inside the event loop
	//fabs(Mass_phi-M_PHI)<0.008 && fabs(pow(cosThetaPri,3))>0.1
	std::cout << "--- Select signal sample" << std::endl;
	TTree* theNtuple = (TTree*)input->Get("nt");
	theNtuple->SetBranchStatus("*",1);

	Float_t cosThetaPri;
	Int_t   Trigger,Cen16,Flag;
	theNtuple->SetBranchAddress( "decayLength",        &decayLength );
	theNtuple->SetBranchAddress( "cosTheta",         &cosTheta );
	theNtuple->SetBranchAddress( "dcaDaughters",         &dcaDaughters );
	theNtuple->SetBranchAddress( "RDca12",         &RDca12 );
	theNtuple->SetBranchAddress( "dcaLcToPv",         &dcaLcToPv );
	theNtuple->SetBranchAddress( "k1RDca",          &k1RDca );
	theNtuple->SetBranchAddress( "piRDca", &piRDca );
	theNtuple->SetBranchAddress( "k2RDca",     &k2RDca );
	theNtuple->SetBranchAddress( "rPtpi",  &rPtpi );
	theNtuple->SetBranchAddress( "rPt12",      &rPt12 );
	theNtuple->SetBranchAddress( "massDiff",     &massDiff );
	theNtuple->SetBranchAddress( "flag",     &flag );
	//	theNtuple->SetBranchAddress( "rY",     &rY );
	theNtuple->SetBranchAddress( "rM",     &rM );
	theNtuple->SetBranchAddress( "rEta",     &rEta );
	theNtuple->SetBranchAddress( "cent",     &cent );
	theNtuple->SetBranchAddress( "rPt",     &rPt );

	// Save All variable and TMVA method.
	TString foutname = fname;
	foutname.ReplaceAll(".root",".tmvaBDT.root");
	TFile   *newfile   = new TFile(foutname.Data(),"recreate");
	TNtuple   *newNtuple   = (TNtuple*)theNtuple->CloneTree();
	Float_t mBdt(0);


	TBranch *Ttmva_Bdt(0);

	// =============================
	// BOOK Branchs for the new tree
	if (Use["BDT"          ])  { Ttmva_Bdt     = newNtuple->Branch( "mva_BDT"          ,&mBdt    ,"mBdt    /F" );}

	// Efficiency calculator for cut method
	Int_t    nSelCutsGA = 0;
	Double_t effS       = 0.7;


	std::cout << "--- Processing: " << theNtuple->GetEntries() << " events" << std::endl;
	TStopwatch sw;
	sw.Start();

	int eventnumber = theNtuple->GetEntries();
	// int eventnumber = 1000000;
	int per = 0;
	if(eventnumber<100) per = 1;
	else per = eventnumber/100;
	cout<<"per = "<<per<<endl;

	for (Long64_t ievt=0; ievt<theNtuple->GetEntries();ievt++) {

		if(ievt%per==0) cout<<"=== Macro        : ... processing event: "<<int(float(ievt)/eventnumber*100+0.5)<<"%...."<<endl;
		theNtuple->GetEntry(ievt);
		//if (rPtpi>0.6 && rPt12>0.5 && k1RDca>0.006 && piRDca>0.006 && k2RDca>0.006 && dcaDaughters<0.01 && rPt>=2.5 && rPt<3.5 && decayLength>0.012 && cosTheta>0.98 && cosTheta<1 && massDiff<0.008 && rM>=1.8 && rM<=2.1 && cent>=7 && cent<=8 && fabs(rY)<1)
		if (rPtpi<=0.6 || rPt12<=0.5 || k1RDca<=0.006 || piRDca<=0.006 || k2RDca<=0.006 || dcaDaughters>=0.01 || decayLength<=0.012 || cosTheta<=0.98 || cosTheta>=1 || massDiff>=0.008 || rM<=1.8 || rM>=2.1 || rPt<1 || rPt >8)	
		{
			if (Use["BDT"          ]) { mBdt    = -99;  Ttmva_Bdt    ->Fill();}
			//			continue;
		}

		else if (cent >=7 && cent <=8 && rPt>=1.5 && rPt<=2.5)
		{

			if (Use["BDT"          ]) { mBdt    = reader_1525_010->EvaluateMVA( "BDT method"           ); Ttmva_Bdt    ->Fill();  histBdt    ->Fill(mBdt    ); }

		}

		else if (cent >=7 && cent <=8 && rPt>=2.5 && rPt<=8)
		{

			if (Use["BDT"          ]) { mBdt    = reader_258_010->EvaluateMVA( "BDT method"           ); Ttmva_Bdt    ->Fill();  histBdt    ->Fill(mBdt    ); }

		}
		else if (cent >=6 && cent <=6 && rPt>=1 && rPt<=2.5 )
		{

			if (Use["BDT"          ]) { mBdt    = reader_125_1020->EvaluateMVA( "BDT method"           ); Ttmva_Bdt    ->Fill();  histBdt    ->Fill(mBdt    ); }

		}

		else if(cent >=6 && cent <=6 && rPt>=2.5 && rPt<=8 )
		{
			if (Use["BDT"          ]) { mBdt    = reader_258_1020->EvaluateMVA( "BDT method"           ); Ttmva_Bdt    ->Fill();  histBdt    ->Fill(mBdt    ); }

		}

		else if(cent >=4 && cent <=5 && rPt>=1 && rPt<=2.5 )
		{
			if (Use["BDT"          ]) { mBdt    = reader_125_2040->EvaluateMVA( "BDT method"           ); Ttmva_Bdt    ->Fill();  histBdt    ->Fill(mBdt    ); }

		}

		else if(cent >=4 && cent <=5 && rPt>=2.5 && rPt<=8 )
		{
			if (Use["BDT"          ]) { mBdt    = reader_258_2040->EvaluateMVA( "BDT method"           ); Ttmva_Bdt    ->Fill();  histBdt    ->Fill(mBdt    ); }

		}

		else if(cent >=0 && cent <=3 && rPt>=1.5 && rPt<=8 )
		{
			if (Use["BDT"          ]) { mBdt    = reader_158_4080->EvaluateMVA( "BDT method"           ); Ttmva_Bdt    ->Fill();  histBdt    ->Fill(mBdt    ); }

		}

		else
		{
			if (Use["BDT"          ]) { mBdt    = -99;  Ttmva_Bdt    ->Fill();}
			//			continue;
		}

	}
	// Get elapsed time
	sw.Stop();
	std::cout << "--- End of event loop: "; sw.Print();


	// --- Write histograms

	// TFile *target  = new TFile( "TMVApp.root","RECREATE" );
	newfile->cd();

	if (Use["BDT"          ])   histBdt    ->Write();


	newNtuple->Write();
	newfile->Close();

	std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;


	std::cout << "==> TMVAClassificationApplication is done!" << endl << std::endl;
} 
