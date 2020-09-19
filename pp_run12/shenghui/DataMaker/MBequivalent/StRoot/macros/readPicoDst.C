#include <TSystem>
class StMaker;
class StChain;
class StPicoDstMaker;


StChain *chain;
//void readPicoDst(const Char_t *inputFile="filelist.list", const Char_t *outputFile="filelist.root", int trigSelect = 2)
void readPicoDst(const Char_t *inputFile="filelist.list", const Char_t *outputFile="filelist.root")
{
	Int_t nEvents = 20000000;
	//  Int_t nEvents = 1000;	
	//Load all the System libraries

	gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();

	gSystem->Load("StIOMaker");
	/*gSystem->Load("StTpcDb");
	gSystem->Load("StEvent");
	gSystem->Load("StMcEvent");
	gSystem->Load("StMcEventMaker");
	gSystem->Load("StDaqLib");
	gSystem->Load("libgen_Tables");
	gSystem->Load("libsim_Tables");
	gSystem->Load("libglobal_Tables");
	gSystem->Load("StMagF");

	gSystem->Load("St_g2t.so");
	gSystem->Load("St_geant_Maker.so");
	gSystem->Load("StAssociationMaker");
	gSystem->Load("StMcAnalysisMaker");
	gSystem->Load("libgeometry_Tables");   
	gSystem->Load("StTriggerUtilities");

	gSystem->Load("StEmcUtil");
	gSystem->Load("StEmcRawMaker");
	gSystem->Load("StEmcADCtoEMaker");
	gSystem->Load("StPreEclMaker");
	gSystem->Load("StEpcMaker");
	gSystem->Load("StEmcSimulatorMaker");

	gSystem->Load("StDbLib");
	gSystem->Load("StDbUtilities");
	gSystem->Load("StDbBroker");
	gSystem->Load("StDetectorDbMaker");
	gSystem->Load("St_db_Maker");

	gSystem->Load("StMtdHitMaker");
	gSystem->Load("StMtdUtil");
	gSystem->Load("StMtdMatchMaker");
	gSystem->Load("StMtdCalibMaker");
	gSystem->Load("StBTofUtil");
	gSystem->Load("StVpdCalibMaker");*/
	
	gSystem->Load("StPicoDstMaker");
	gSystem->Load("StPicoPrescales");
	gSystem->Load("StMyAnalysisMaker");

	chain = new StChain();
	StPicoDstMaker *picoMaker = new StPicoDstMaker(0,inputFile,"picoDst");

//	StPicoMtdCalibMaker *calibMaker = new StPicoMtdCalibMaker();
//	calibMaker->setInitFromFile(kTRUE);
//	calibMaker->setApplyT0(kTRUE);
//	calibMaker->setCalibFileT0("StRoot/StPicoDstMaker/Run14_AuAu200_CalibDtof.offline.dat");


	//StMyAnalysisMaker *anaMaker = new StMyAnalysisMaker("ana",picoMaker,outputFile,trigSelect);
	StMyAnalysisMaker *anaMaker = new StMyAnalysisMaker("ana",picoMaker,outputFile);
	chain->Init();
	cout<<"chain->Init();"<<endl;
	int total = picoMaker->chain()->GetEntries();
	cout << " Total entries = " << total << endl;
	if(nEvents>total) nEvents = total;


	for (Int_t i=0; i<nEvents; i++){
		if(i%100000==0)
			cout << "Working on eventNumber " << i << endl;

		chain->Clear();
		int iret = chain->Make(i);

		if (iret) { cout << "Bad return code!" << iret << endl; break;}

		total++;

	}

	cout << "****************************************** " << endl;
	cout << "Work done... now its time to close up shop!"<< endl;
	cout << "****************************************** " << endl;
	chain->Finish();
	cout << "****************************************** " << endl;
	cout << "total number of events  " << nEvents  << endl;
	cout << "****************************************** " << endl;

	delete chain;


}
