
#include <TSystem>

class StMaker;
class StChain;
class StPicoDstMaker;


StChain *chain;
void readAll(const Char_t *inputFile="test.list", TString outputFile="anaTree.root")
{
  Int_t nEvents = 10000000;
  //	Int_t nEvents = 10;
  //Load all the System libraries
  
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  
  //gSystem->Load("StPicoEvent");
  gSystem->Load("StPicoDstMaker");
  gSystem->Load("StDmesonMaker");
  gSystem->Load("StPicoPrescales");
  gSystem->Load("StNpeRead");
  
  chain = new StChain();
  
  StPicoDstMaker *picoMaker = new StPicoDstMaker(0,inputFile,"picoDst");
//  TString inputFileName = inputFile;
//  Int_t index = inputFileName.Index("st_");
//  TString mInputFileName="";
//  for(int i=index;i<(int)inputFileName.Length();i++) {
//    mInputFileName.Append(inputFileName(i));
//  }
//
//  outputFile=mInputFileName;
//  outputFile.ReplaceAll("FemtoDst.root","anaTree.root");

  StDmesonMaker *anaMaker = new StDmesonMaker("ana",picoMaker,outputFile);
  
  TString outFileName;
  outFileName=outputFile;
  outFileName.ReplaceAll("anaTree.root","ana.root");
  StNpeRead* dMesonRead = new StNpeRead(outFileName.Data());
  
  chain->Init();
  cout<<"chain->Init();"<<endl;
  int total = picoMaker->chain()->GetEntries();
  cout << " Total entries = " << total << endl;
  if(nEvents>total) nEvents = total;
  for (Int_t i=0; i<nEvents; i++){
  //for (Int_t i=0; i<200; i++){
    if(i%50000==0)
      cout << "Working on eventNumber " << i << endl;
    
    chain->Clear();
    int iret = chain->Make(i);
    
    if (iret) { cout << "Bad return code!" << iret << endl; break;}
    total++;
  }
  chain->Finish();
  delete chain;
  
  dMesonRead->bookObjects();
  dMesonRead->read(outputFile);
  dMesonRead->writeObjects();

  
  cout << "****************************************** " << endl;
  cout << "Work done... now its time to close up shop!"<< endl;
  cout << "****************************************** " << endl;
  
}
