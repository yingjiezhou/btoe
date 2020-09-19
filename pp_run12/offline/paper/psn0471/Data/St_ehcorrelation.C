#include "./StEmcPointMakerPar.h" 

void St_ehcorrelation(Int_t nEvents, Int_t nFiles, TString InputFileList, TString OutputDir, TString JobIdName ) 
{
 
  // Load libraries
  gROOT   -> Macro("loadMuDst.C");

  gSystem->Load("StDbBroker");		//needed before St_db_Maker
  gSystem->Load("St_db_Maker");
  gSystem->Load("StDetectorDbMaker");
  //gSystem->Load("StDaqLib");

  //gSystem->Load("StEmcUtil");
  gSystem->Load("StEmcRawMaker");
  gSystem->Load("StEmcADCtoEMaker");
  gSystem->Load("StEpcMaker");
  gSystem->Load("StPreEclMaker");
  gSystem -> Load("StEmcPointMaker") ;

  gSystem->Load("StDaqLib");
  //gSystem->Load("StDbLib");
  //gSystem->Load("StDbBroker");
  //gSystem->Load("St_db_Maker");

  gSystem -> Load("St_ehcorrelationMaker.so") ;

  cout <<"============ Load lib. done ===============" << endl;

  // List of member links in the chain
  StChain*                    chain  =  new StChain ;
  StMuDstMaker*          muDstMaker  =  new StMuDstMaker(0,0,"",InputFileList,"MuDst",nFiles) ;

  StMuDbReader *db = StMuDbReader::instance();
  St_db_Maker *dbMk = new St_db_Maker("StarDb", "MySQL:StarDb");

  //StDetectorDbMaker *detDbMk = new StDetectorDbMaker();

  StEmcADCtoEMaker *adc2e = new StEmcADCtoEMaker("ADC2E");
  StEmcPointMaker *ptmkr = new StEmcPointMaker("ptmkr");
  St_ehcorrelationMaker* AnalysisCode  =  new St_ehcorrelationMaker(muDstMaker) ;

    emcPtMakerPar_st* pp = new emcPtMakerPar_st;
    float slow[4]	=	{	0.4,	0.1,	0.05,	0.05	};
    float alow[4] 	=	{	0.05,	0.05,	0.04,	0.04	};
    float shigh[4]	=	{	0.7,	0.1,	0.1,	0.1	};
    float ahigh[4]	=	{	0.05,	0.05,	0.05,	0.05	};
    float t[4]		=	{	1.0,	0.05,	0.1,	0.1	};

  cout <<"============ link  done ===============" << endl;

  // Turn off everything but Primary tracks in order to speed up the analysis and eliminate IO
  //muDstMaker -> SetStatus("*",1) ;                // Turn on all branches
  //muDstMaker -> SetStatus("MuEvent",1) ;          // Turn on the Event data (esp. Event number)
  //muDstMaker -> SetStatus("PrimaryTracks",1) ;    // Turn on the primary track data

  muDstMaker -> SetStatus("*",0) ;                // Turn off all branches
  muDstMaker->SetStatus("MuEventAll",1);	
  muDstMaker->SetStatus("EmcAll",1);


  cout <<"============ Set Primary track done ===============" << endl;

  // Miscellaneous things we need before starting the chain
  TString Name = JobIdName ;
  Name.Append(".histograms.root") ;
  cout <<"============ Set out file name done ===============" << endl;

  AnalysisCode -> SetOutputFileName(Name) ;       // Name the output file for histograms
  cout <<"============ Regist file name done ===============" << endl;
  if ( nEvents == 0 )  nEvents = 10000000 ;       // Take all events in nFiles if nEvents = 0
  cout <<"------------------- init start -------------------- " << endl;
  // Loop over the links in the chain
  chain -> Init() ;

  cout <<"============ Set pp files ===============" << endl;
  
    for(int i = 0; i < 4; i++){
	if(i!=1){
		cout << slow[i] << endl;  
		pp->seedlow = slow[i];
		pp->seedhigh = shigh[i];
		pp->addlow = alow[i];
		pp->addhigh = ahigh[i];
		pp->total = t[i];
		ptmkr->setParameters(pp,i);
	}
    }

  delete pp;

  cout <<"============ Init done ===============" << endl;
  chain -> EventLoop(1,nEvents) ;
  cout <<"============ Loop done ===============" << endl;
  chain -> Finish() ;
  cout << endl;

  // Cleanup

  cout << endl;
  //delete chain ;

  cout <<"============ Clean up chain ===============" << endl;
  cout << endl;

  cout <<"============ code done ===============" << endl;
  cout << endl;

}


// For run
//.x St_ehcorrelation.C (1000,1,"st_physics_sample_data.MuDst.root","./","test") 
// 
