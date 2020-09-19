#include <TSystem>
#include "TStopwatch.h"
#include "TDatime.h"
# ifndef __CINT__

#include "StMaker.h"
#include "StChain.h"

#include "StMuDSTMaker/COMMON/macros/loadSharedLibraries.C"
#include "macros/Load.C"
#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StRefMultCorr/StRefMultCorr.h"
#include "StRoot/StRefMultCorr/CentralityMaker.h"
// #include "StPicoHFMaker/StPicoHFEvent.h"
// #include "StRoot/StEventPlane/StEventPlane.h"
#include "StMemStat.h"

#else
class StChain;
#endif

class StMaker;
class StChain;
class StPicoDstMaker;
class StEventPlane;

StChain *chain;
void readPicoDst(const Char_t *inputFile="test.list", const Char_t *outputFile="test.root")
{
  TStopwatch SW;
  SW.Start();
  TDatime tBegin,tNow;
  tBegin.Set();
  tBegin.Print();

 // Int_t nEvents = 1e9;
  Int_t nEvents = 200; //test mode	
  //Load all the System libraries
	
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  gSystem->Load("StPicoDstMaker");
  gSystem->Load("StRefMultCorr");
  gSystem->Load("StMyAnalysisMaker");
  // gSystem->Load("StEventPlane");
  chain = new StChain();

  StPicoDstMaker *picoMaker = new StPicoDstMaker(2,inputFile,"PicoDst");
cout << "flag1" << endl;
  StRefMultCorr* grefmultCorrUtil  = CentralityMaker::instance()->getgRefMultCorr_P16id();
  cout<<"here"<<endl;
   grefmultCorrUtil->setVzForWeight(6, -6.0, 6.0);
   grefmultCorrUtil->readScaleForWeight("StRoot/StRefMultCorr/macros/weight_grefmult_VpdnoVtx_Vpd5_Run16.txt");
  StMyAnalysisMaker *anaMaker = new StMyAnalysisMaker("ana",picoMaker,grefmultCorrUtil,outputFile);

  chain->Init();
  cout<<"chain->Init();"<<endl;
  int total = picoMaker->chain()->GetEntries();
  cout << " Total entries = " << total << endl;
  if(nEvents>total) nEvents = total;
  Int_t per = 0;
  if(nEvents<100) per = 1;
  else per = nEvents/100;

  for (Int_t i=0; i<nEvents; i++){
    if(i%per==0)
      cout << "PROCESSING "<<(int)((float)i/nEvents*100.+0.5)<<"%...."<< endl;
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
  cout << "total number of events  " << nEvents << endl;
  cout << "****************************************** " << endl;
	
  delete chain;
	
  SW.Stop();
  SW.Print();

  tNow.Set();tNow.Print();
  cout << "++++++++++++++++++++++++++++++++++++++++++ " << endl;
  cout << "+           Statistic Information        + " << endl;
  cout << "+ Number of Event : "<<nEvents<<" Events"<<endl;
  cout << "+ Elapsed time    : "<<tNow.Convert()-tBegin.Convert()<<" Seconds"<<endl;
  cout << "+ Rate            : "<<float(nEvents)/(tNow.Convert()-tBegin.Convert())<<" Events/Sec"<<endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++ " << endl;	
}
