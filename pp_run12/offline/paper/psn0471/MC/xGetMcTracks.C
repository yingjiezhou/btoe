#include "./StEmcPointMakerPar.h"

void xGetMcTracks(/* 
                  int nevents=99999,
		  const char* infile="sched36CA8B62502FA21F81E8A42140C44FD8_595.list",
		  const char* dir = "",
		  const char *filter = ".root",
		  const char *runnum = "",
		  const char *mix = "",
		  const char *jobindex = "test100607"
                  */
                  Int_t nevents, TString infile, char JobIdName[100]
                  )
{
	cout<<"pwd: "<<gSystem->WorkingDirectory()<<endl;

    cout <<"File list:\t"<<infile<<endl;
    //abort();
    cout <<"Loading libraries .....\n";
    if (gClassTable->GetID("TTable") < 0) {
	gSystem->Load("libStar");
	gSystem->Load("libPhysics");
    }
    gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
    loadSharedLibraries();
    gSystem->Load("StDbUtilities");
//    gSystem->Load("StDbLib");			//needed before StDbBroker
/*
    gSystem->Load("libTable");
    gSystem->Load("libPhysics");
    gSystem->Load("St_base");
    gSystem->Load("StChain");
    gSystem->Load("St_Tables");
    gSystem->Load("StUtilities");
    gSystem->Load("StTreeMaker");
    gSystem->Load("StIOMaker");
    gSystem->Load("StarClassLibrary");
    gSystem->Load("StTriggerDataMaker");
    gSystem->Load("StBichsel");
    gSystem->Load("StEvent");
    gSystem->Load("StEventUtilities");
    gSystem->Load("StDbLib");
    gSystem->Load("StEmcUtil");
    gSystem->Load("StTofUtil");
    gSystem->Load("StPmdUtil");
    gSystem->Load("StStrangeMuDstMaker");
    gSystem->Load("StMuDSTMaker");
*/
    gSystem->Load("StMcEvent");
    gSystem->Load("StMcEventMaker");
    gSystem->Load("StEmcSimulatorMaker");
    gSystem->Load("StEEmcSimulatorMaker");
    gSystem->Load("StEEmcUtil");
    gSystem->Load("StDaqLib");
    gSystem->Load("StEmcTriggerMaker");
    gSystem->Load("StAssociationMaker");
//    gSystem->Load("StMcAnalysisMaker");

    gSystem->Load("StDbBroker");		//needed before St_db_Maker
    gSystem->Load("St_db_Maker");
    gSystem->Load("StDetectorDbMaker");
    //gSystem->Load("StSpinDbMaker");
//    gSystem->Load("StDaqLib");
//    gSystem->Load("StEmcRawMaker");		//needed before StEmcADCtoEMaker
//    gSystem->Load("StEmcADCtoEMaker");
    //gSystem->Load("StPreEclMaker");
    //gSystem->Load("StEpcMaker");
    //gSystem->Load("StJetMaker");
    gSystem->Load("StEmcPointMaker");
    gSystem -> Load("PhorecoMaker.so") ;
    //gSystem->Load("PkMcNtupleMaker");

    cout << " Loading done! " << endl;
   
    //string filelistn = strstr(jobid,"_");

    //string infile(filepath);
    //infile.append(".list");

    //string runlist = strstr(filepath,"RUN");
    //string ntuplefile("Tracks/");
    //ntuplefile.append(runlist);
    //string ntuplefile(scratch);
    //ntuplefile.append("/");
    //ntuplefile.append(runnum);
    //ntuplefile.append("_");
    //ntuplefile.append(mix);
    //ntuplefile.append("_");
    //ntuplefile.append(jobindex); 
    //ntuplefile.append(filelistn);
    //ntuplefile.append(".McTracks.root");
    //cout<<" ntuplefile = "<< ntuplefile << endl;

    //string tallyfile(scratch);
    //tallyfile.append("/");
    //tallyfile.append(runnum);
    //tallyfile.append("_");
    //tallyfile.append(mix);
    //tallyfile.append("_");
    //tallyfile.append(jobindex); 
    //tallyfile.append(filelistn);
    //tallyfile.append(".mctally.root");

    StFile *setfile = new StFile();

    TString inputstring(infile);
    if(inputstring.Contains(".list")){
        ifstream from(infile);
        if(from.bad()){
            cout<<"Can't open file list ---"<<infile<<"---\n";
            return;
        }
	string file,temp;
        //while(from>>file>>temp){
        while(from>>file){
            setfile->AddFile(file.c_str());
            cout<<"Adding file "<<file.c_str()<<endl;
        }
    }else{
        if(inputstring.Contains("event.root")){
            setfile->AddFile(inputstring.Data());
            cout<<"Adding file "<<inputstring<<endl;
        }
    }

    //TFile fTally(tallyfile.c_str(),"RECREATE");
/*
    TH1D *hTally = new TH1D("Tally","Points & Tracks Tally for PPY6",20,0,20);
    hTally->SetBit(TH1::kCanRebin);
    hTally->LabelsOption("v");
    hTally->GetXaxis()->SetLabelOffset(-0.25);
*/
    //TH1D *hPtTally = new TH1D("PtTally","StEmcPointMaker Tally for PPY6",20,0,20);
    //hPtTally->SetBit(TH1::kCanRebin);

    //TH1F *hTimeTally = new TH1F("TimeTally","Time to setup makers",10,0,10);
    //hTimeTally->SetBit(TH1::kCanRebin);

    TTime start, end;

	cout<<"Chain\n";
    start = gSystem->Now();
    StChain *chain= new StChain("StChain"); 
    chain->SetDebug(1);
    gMessMgr->SwitchOff("D");
    gMessMgr->SwitchOff("I");
    end = gSystem->Now();
    //hTimeTally->Fill("StChain",(long)(end-start));

	cout<<"IOMaker\n";
    start = gSystem->Now();
    StIOMaker *iomkr = new StIOMaker("StIO","r",setfile);
    iomkr->SetIOMode("r");
    iomkr->SetBranch("*",0,"0");
    iomkr->SetBranch("geantBranch",0,"r");
    iomkr->SetBranch("eventBranch",0,"r");
    end = gSystem->Now();
    //hTimeTally->Fill("StIOMaker",(long)(end-start));

	cout<<"McEventMaker\n";
    start = gSystem->Now();
    StMcEventMaker* mcEventReader = new StMcEventMaker;
    end = gSystem->Now();
    //hTimeTally->Fill("StMcEventMaker",(long)(end-start));
    //Instantiate the MuDstReader
//    StMuDebug::setLevel(1); 
//    StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,dir,infile,filter,10,"MuDst");
//    StMuDbReader *db = StMuDbReader::instance();


    start = gSystem->Now();
    St_db_Maker *dbMk = new St_db_Maker("StarDb", "MySQL:StarDb","$STAR/StarDb");
//    dbMk->SetDateTime(20040101,0);
//    dbMk->SetDateTime(20050430,171445);
    dbMk->SetDateTime(20050515,012313);
    end = gSystem->Now();
    //hTimeTally->Fill("St_db_Maker",(long)(end-start));
//    dbMk->SetFlavor("pi0","bemcStatus");
/*
//    StSpinDbMaker *spinDb = new StSpinDbMaker("spinDb");
    //St_db_Maker *dbMk = new St_db_Maker("StarDb","/star/u/kurnadi/StarDb", "MySQL:StarDb");
    start = gSystem->Now();
    StDetectorDbMaker *detDbMk = new StDetectorDbMaker();
    end = gSystem->Now();
    hTimeTally->Fill("StDetectorDbMaker",(long)(end-start));
*/
/*
	cout<<"EmcADCtoEMaker\n";
    StEmcADCtoEMaker *adc2e = new StEmcADCtoEMaker("ADC2E");
    adc2e->setPrint(kFALSE);
    adc2e->setEmbeddingMode(kTRUE);
*/
	cout<<"EmcSimulatorMaker\n";
    start = gSystem->Now();
    StEmcSimulatorMaker *emcSim = new StEmcSimulatorMaker();
//    emcSim->setMakeFullDetector(kBarrelEmcTowerId,true);
//    emcSim->setMakeFullDetector(kBarrelSmdEtaStripId,true);
//    emcSim->setMakeFullDetector(kBarrelSmdPhiStripId,true);
//    emcSim->setPedestalCut(kBarrelSmdEtaStripId,1.5);
//    emcSim->setPedestalCut(kBarrelSmdPhiStripId,1.5);
    end = gSystem->Now();
    //hTimeTally->Fill("StEmcSimulatorMaker",(long)(end-start));
    
	cout<<"EmcTriggerMaker"<<endl;
    start = gSystem->Now();
    StEmcTriggerMaker *trigEmc = new StEmcTriggerMaker("bemctrigger");
    trigEmc->setDbMaker(dbMk);
    end = gSystem->Now();
    //hTimeTally->Fill("StEmcTriggerMaker",(long)(end-start));

	cout<<"EmcPointMaker\n";
    start = gSystem->Now();
    StEmcPointMaker *ptmkr = new StEmcPointMaker("ptmkr");
    //ptmkr->setTallyHist(hPtTally);
    ptmkr->setPrint(kFALSE);
    ptmkr->setPrintDetail(kFALSE);
    end = gSystem->Now();
    //hTimeTally->Fill("StEmcPointMaker",(long)(end-start));

	cout<<"AssociationMaker\n";
    start = gSystem->Now();
    StAssociationMaker* associator = new StAssociationMaker;
    associator->useInTracker();
    associator->useDistanceAssoc();
    end = gSystem->Now();
    //hTimeTally->Fill("StAssociationMaker",(long)(end-start));

	cout<<"EmcAssociationMaker"<<endl;
    start = gSystem->Now();
    StEmcAssociationMaker *emcassoc = new StEmcAssociationMaker();
    end = gSystem->Now();
    //hTimeTally->Fill("StEmcAssociationMaker",(long)(end-start));
    
    emcPtMakerPar_st* pp=new emcPtMakerPar_st;
    float slow[4]   =       {       0.4,    0.1,    0.05,   0.05    };
    float alow[4]   =       {       0.05,   0.05,   0.04,   0.04    };
    float shigh[4]  =       {       0.7,    0.1,    0.1,    0.1     };
    float ahigh[4]  =       {       0.05,   0.05,   0.05,   0.05    };
    float t[4]      =       {       1.0,    0.05,   0.1,    0.1     };

/*
    StPreEclMaker *pecl = new StPreEclMaker("ecl");
    pecl->setPrint(kFALSE);

    //Setting clustering parameters: detector, max tower/strip, seed, add, total, CheckClustersOk(?)
    pecl->SetClusterConditions("bemc",4,0.4,0.05,0.7,kFALSE);
    pecl->SetClusterConditions("bsmde",5,0.05,0.02,0.05,kFALSE);
    pecl->SetClusterConditions("bsmdp",5,0.05,0.02,0.05,kFALSE);

    StEpcMaker *epc = new StEpcMaker("epc");
    epc->setPrint(kFALSE);
*/

	//cout<<"McNtupleMaker\n";
    start = gSystem->Now();
    //PkMcNtupleMaker *pk = new PkMcNtupleMaker("PkMcNtuple");
    //pk->setNtupleFile(ntuplefile.c_str());
    PhorecoMaker* AnalysisCode  =  new PhorecoMaker("Phoreco");
    //AnalysisCode->setNtupleFile("test.root");  
    char Outfile[100];  
    cout << "JobID = " << JobIdName << endl;
    sprintf(Outfile,"Phoreco_%s.root",JobIdName);
    //AnalysisCode->SetOutFile("Pho_sim.root");  
    AnalysisCode->SetOutFile(Outfile);  
//    pk->setTallyHist(hTally);
    end = gSystem->Now();
    //hTimeTally->Fill("McNtupleMaker",(long)(end-start));

	cout<<"Init\n";
    start = gSystem->Now();
    chain->Init();
    end = gSystem->Now();
    //hTimeTally->Fill("Init",(long)(end-start));

    start = gSystem->Now();
    controlEmcSimulatorMaker_st* simControl = emcSim->getControlSimulator()->GetTable();
    simControl->keyDB[0] = 2;
    simControl->keyDB[1] = 0;
    simControl->keyDB[2] = 2;
    simControl->keyDB[3] = 2;
    simControl->makeFullDet[0] = 1;
    simControl->makeFullDet[1] = 0;
    simControl->makeFullDet[2] = 1;
    simControl->makeFullDet[3] = 1;
    simControl->pedCutOff[2] = 1.5;
    simControl->pedCutOff[3] = 1.5;
    end = gSystem->Now();
    //hTimeTally->Fill("controlEmcSimulatorMaker_st",(long)(end-start));

	cout<<"setParameters\n";
    start = gSystem->Now();
    //overwrite default clustering parameters, have to be done after Init()
    for(int i=0;i<4;i++)
    {
	if(i!=1)
	{
		pp->seedlow=slow[i];
		pp->seedhigh=shigh[i];
		pp->addlow=alow[i];
		pp->addhigh=ahigh[i];
		pp->total=t[i];
		ptmkr->setParameters(pp,i);
	}
    }
    delete pp;
    end = gSystem->Now();
    //hTimeTally->Fill("emcPtMakerPar_st",(long)(end-start));

	cout<<"PrintInfo\n";
    chain->PrintInfo();

    int total=0;
    
    for (Int_t iev=0;iev<nevents; iev++) {
    //for (Int_t iev=0;iev<10; iev++) {
    start = gSystem->Now();
	cout << "****************************************** " << endl;
	cout << "Working on eventNumber " << iev << endl;
	cout << "******************************************* " << endl;
	chain->Clear();
          
	int iret = chain->Make(iev); 
        cout << iret << endl; 
	total++;
	if (iret) {
	    cout << "Bad return code!" << endl;
	    break;
	}
    end = gSystem->Now();
    //hTimeTally->Fill("Event",(long)(end-start));
	//Here's where you can do your analysis, for an example look in this method
    } 

  
  /*
  cout <<"============ Init done ===============" << endl;
  chain -> EventLoop(1,100) ;
  cout <<"============ Loop done ===============" << endl;
  chain -> Finish() ;
  cout << endl;
  */
    chain->Finish(); 
    //fTally.cd();
//    hTally->Write();
    //hPtTally->Write();
    //hTimeTally->Write();
    //fTally.Close();

    /*
    cout << "****************************************** " << endl;
    cout << "total number of events  " << total << endl;
    cout << "****************************************** " << endl;     
    */
    return;

}







