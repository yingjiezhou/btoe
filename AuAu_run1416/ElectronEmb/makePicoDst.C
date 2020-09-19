#include <TSystem>
class StMaker;
class StChain;
class StPicoDstMaker;
class StMuDstMaker;

StChain *chain;
//void makePicoDst(const Int_t runnumber=11037016, const Char_t *inputFile="st_physics_11037016_raw_5010002.MuDst.root", const bool creatingPhiWgt = kFALSE, const int prodMod = 0)
void makePicoDst(TString runnumber = "ABC123_7",TString mylist="myList.list"){

    const bool creatingPhiWgt = kFALSE;
    const int prodMod = 0; 
    const int emcMode= 0;
    const bool createMcBranch = kTRUE;
    Int_t nEvents = 1000000;
    std::ifstream listOfFiles(mylist.Data());
    std::string file;
    if (listOfFiles.is_open())
    {
	getline(listOfFiles, file);	
	cout << "StPicoDstMaker - Adding :" << file << endl;
      
    }else
    {
	cout << "StPicoDstMaker - Could not open list of files. ABORT!" << endl;
    }
    const Char_t *inputFile = file.c_str();
    TString MCList = inputFile;
    MCList.ReplaceAll("MuDst.root","McEvent.root");
    const Char_t *inputGeant = MCList;
    cout << inputFile <<endl;
    cout << inputGeant << endl;
//Load all the System libraries
    gSystem->Load("libTable");
    gSystem->Load("libPhysics");
    gSystem->Load("St_base");
    gSystem->Load("StChain");
    gSystem->Load("St_Tables");
    gSystem->Load("StUtilities");        // new addition 22jul99
    gSystem->Load("StTreeMaker");
    gSystem->Load("StIOMaker");
    gSystem->Load("StarClassLibrary");
    gSystem->Load("StTriggerDataMaker"); // new starting from April 2003
    gSystem->Load("StBichsel");
    gSystem->Load("StEvent");
    gSystem->Load("StEventUtilities");
    gSystem->Load("StDbLib");
    gSystem->Load("StEmcUtil");
    gSystem->Load("StTofUtil");
    gSystem->Load("StPmdUtil");
    gSystem->Load("StPreEclMaker");
    gSystem->Load("StStrangeMuDstMaker");
    gSystem->Load("StMuDSTMaker");
    if(createMcBranch){
	gSystem->Load("StMcEvent");
	gSystem->Load("StAssociationMaker");
    }
    if(1){//!creatingPhiWgt&&emcMode) {
	gSystem->Load("StTpcDb");
	gSystem->Load("StMcEvent");
	gSystem->Load("StMcEventMaker");
	gSystem->Load("StDaqLib");
	gSystem->Load("libgen_Tables");
	gSystem->Load("libsim_Tables");
	gSystem->Load("libglobal_Tables");
	gSystem->Load("StEmcTriggerMaker");
	gSystem->Load("StEmcUtil");//mine
	gSystem->Load("StEmcRawMaker");
	gSystem->Load("StEmcADCtoEMaker");
	gSystem->Load("StPreEclMaker");
	gSystem->Load("StEpcMaker");
	gSystem->Load("StEmcSimulatorMaker");
	gSystem->Load("StEmcUtil");
	gSystem->Load("StDbBroker");
	gSystem->Load("StDetectorDbMaker");
	gSystem->Load("StDbUtilities");
	gSystem->Load("StEEmcUtil");
	gSystem->Load("StEEmcDbMaker");
	gSystem->Load("St_db_Maker");
	gSystem->Load("StTriggerUtilities");
    }

    gSystem->Load("StPicoDstMaker");

    chain = new StChain();
    if( createMcBranch ){
	StIOMaker* ioMaker = new StIOMaker("IO","r",inputGeant,"bfcTree");
	ioMaker->SetDebug();
	ioMaker->SetIOMode("r");
	ioMaker->SetBranch("*",0,"0");                 //deactivate all branches
	ioMaker->SetBranch("geantBranch",0,"r"); //activate geant Branch
	ioMaker->SetBranch("McEventBranch",0,"r"); //activate geant Branch
	ioMaker->SetBranch("eventBranch",0,"r"); //activate geant Branch
	StAssociationMaker* associator    = new StAssociationMaker;
	cout<<"created new StAssociationMaker"<<endl;
	associator->useInTracker();
    }




    StMuDstMaker *MuDstMaker = new StMuDstMaker(0,0,"",inputFile,"MuDst",100);
    MuDstMaker->SetStatus("*",0);
    MuDstMaker->SetStatus("MuEvent",1);
    MuDstMaker->SetStatus("PrimaryVertices",1);
    MuDstMaker->SetStatus("PrimaryTracks",1);
    MuDstMaker->SetStatus("GlobalTracks",1);
    MuDstMaker->SetStatus("CovGlobTrack",1);
    MuDstMaker->SetStatus("BTof*",1);
    MuDstMaker->SetStatus("Emc*",1);

    // Need St_db_Maker for Emc calibration                                                                                                                                                                 
    St_db_Maker *db1 = new St_db_Maker("db","$HOME/StarDb","MySQL:StarDb","$STAR/StarDb");

    // Maker to apply calibration                                                                                                                                                                           
    StEmcADCtoEMaker *adc_to_e=new StEmcADCtoEMaker();
    adc_to_e->setPrint(kFALSE);
    adc_to_e->saveAllStEvent(true);    
    // Makers for clusterfinding                                                                                                                                                                            
    StPreEclMaker *pre_ecl=new StPreEclMaker();
    pre_ecl->setPrint(kFALSE);
    StEpcMaker *epc=new StEpcMaker();
    epc->setPrint(kFALSE);
    
/*    if(!creatingPhiWgt&&emcMode) {
        St_db_Maker *dbMk = new St_db_Maker("db","MySQL:StarDb","$STAR/StarDb","StarDb");
	//dbMk->SetDateTime(20050506,214129);
	// Endcap database
	//StEEmcDbMaker* eemcDb = new StEEmcDbMaker;

	StEmcADCtoEMaker *adc2e = new StEmcADCtoEMaker();
	adc2e->saveAllStEvent(true);
	//StDetectorDbMaker* detDbMk = new StDetectorDbMaker();
	//StEmcSimulatorMaker* emcSim = (StEmcSimulatorMaker*)chain->GetMaker("EmcSimulator");                                                                 
	//emcSim->setCheckStatus(kBarrelEmcTowerId,false);                                                                                         
	//emcSim->setMakeFullDetector(kBarrelEmcTowerId,true);                                                                                 
	//emcSim->setDoZeroSuppression(kBarrelEmcTowerId,false);

	StPreEclMaker *pre_ecl=new StPreEclMaker();
	pre_ecl->setPrint(kFALSE);
	StEpcMaker *epc=new StEpcMaker();
	epc->setPrint(kFALSE);
#if 0
	// Trigger simulator
	StTriggerSimuMaker* trigSimu = new StTriggerSimuMaker;
	trigSimu->setMC(false);
	trigSimu->useBemc();
	//trigSimu->useEemc();
	trigSimu->useOfflineDB();
	trigSimu->bemc->setConfig(StBemcTriggerSimu::kOffline); 
#endif
}*/
	
    //StPicoDstMaker *picoMaker = new StPicoDstMaker(1,inputFile,"picoDst");
    StPicoDstMaker *picoMaker = new StPicoDstMaker(1,inputFile,"picoDst");
    picoMaker->setRunNumber(15107005);
    //picoMaker->setProdMode(prodMod); // 0-mb, 1-central, 2-ht
    picoMaker->setEmcMode(emcMode); // 0-No EMC, 1-EMC ON
//        picoMaker->SetDebug(1);
    picoMaker->setMcMode(createMcBranch);
       
    chain->Init();
    cout<<"chain->Init();"<<endl;
    int total = 0;
    cout<<MuDstMaker->chain()->GetEntries()<<endl;
    if( nEvents > MuDstMaker->chain()->GetEntries() )
	nEvents=MuDstMaker->chain()->GetEntries();
    for (Int_t i=0; i<nEvents; i++){
	if(i%100==0)
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
    cout << "total number of events  " << total << endl;
    cout << "****************************************** " << endl;
	
    delete chain;
	
	
}
