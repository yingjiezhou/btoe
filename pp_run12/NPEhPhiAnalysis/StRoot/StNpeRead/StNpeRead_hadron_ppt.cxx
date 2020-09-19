#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <map>
#include <set>
#include "StNpeRead.h"
#include "StCuts.h"
//#include "StDmesonEvent.h"
//#include "StTRIGGERS.h"
//#include "StNpeMaker/StDmesonEvent.h"
//#include "prescales.h"
#include "StRoot/StPicoPrescales/prescales.h"
#include "StRoot/StPicoPrescales/StTRIGGERS.h"
#include "StDmesonMaker/StDmesonTrack.h"

#include "StDmesonMaker/StElectronPair.h"
#include "StDmesonMaker/StKaonKaon.h"

#include "StLorentzVectorF.hh"

#include "TH1D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TF1.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TClonesArray.h"
#include "TRandom.h"
#include "TRandom3.h"

//Float_t KAONMASS2 = 0.49367 * 0.49367;
//Float_t PHIMASS = 1.01945; // GeV/c/c

using namespace std;

ClassImp(StNpeRead)
//-----------------------------------------------------------------------------
StNpeRead::StNpeRead(const char* outName)
{
  numPtBins = 14; maxBufferSize = 15;
  writeXiaozhiHists = kFALSE; writeDataQA = kFALSE; writeRunQA = kFALSE; // Set flags for QA writing (to minimize file size when QA unnecessary)
  pi = 3.1415826;
  // Initialize the hadron weighting function (if can't find, exit)
  if(!readEff())
    exit(1);
  
  mOutputFile = new TFile(outName, "RECREATE");
  TH1F::SetDefaultSumw2();
  mPrescales=prescales::Instance();
  file_runNumber.open("/star/data01/pwg/yjzhou19/Local/zamiller/NPEhPhiAnalysis2015_v10/StRoot/StNpeRead/runIDPicoSet.txt");
  SetRunID_VPD();
}
void  StNpeRead::SetRunID_VPD( )
{
  
  //runID_VPDMB
  Int_t run_index;
  
  if(!file_runNumber.is_open()){
    cout<< "  Error open file ";
    exit(1);
  }
  
  if(file_runNumber.is_open())
  {
    // std::string line;
    // start from beginning
    
    //  file_runNumber.clear() ;
    // file_runNumber.seekg(0, ios::beg) ;
    
    runID_List.clear();
    
    // std::istringstream iss(line);
    int runID;
    int runindex=0;
    // while (std::getline(file_runNumber, line))
    while(file_runNumber>>runID)
    {
      // iss>>runID;
      // cout << runID << endl;
      runID_List[runID]=runindex;
      runindex++;
    }
    cout<<"The file has been opened."<<endl;
  }
  
  //  cout << runID_List.size() << endl;;
  
  for(map<int,int>::iterator iter=runID_List.begin();iter!=runID_List.end();iter++)
  {
    // std::cout<< iter->second<<"   \t"<<"  "<<iter->first<<std::endl;
  }
  
  
}
/*
 
 int runIndex=-1, runID=-999;
 
 std::string line;
 // start from beginning
 file_runNumber.clear() ;
 file_runNumber.seekg(0, ios::beg) ;
 
 while (std::getline(file_runNumber, line)) {
 // while(!file_runNumber.eof()) {
 //file_runNumber>>runIndex>>runID;
 std::istringstream iss(line);
 iss >> runIndex >> runID;
 // std::cout<< runIndex<<"  "<<runID<<"  "<<run_ID<<std::endl;
 
 if(runID==run_ID) {
 run_index=runIndex;
 // std::cout<< runIndex<<"  "<<runID<<"  "<< run_ID<<std::endl;
 
 }
 
 }
 return run_index;
 
 }*/
//runID_List();

//-----------------------------------------------------------------------------
StNpeRead::~StNpeRead()
{
  /*  */
}

//-----------------------------------------------------------------------------
void StNpeRead::bookObjects()
{
  mNpeEvent = new StDmesonEvent;
  
  /// Z. Histos
  for(Int_t trg=0; trg<4; trg+=2)
  {
    //cout << trg << endl;
    mh1PtAllTracks[trg]      = new TH1F(Form("mh1PtAllTracks_%i",trg),"",400,0,20);
    mh1PtETracks[trg]        = new TH1F(Form("mh1PtETracks_%i",trg),"",400,0,20);
    // mh2nSigmaEPt[trg]        = new TH2F(Form("mh2nSigmaEPt_%i",trg),"",600,-30,30,400,0,20);
    //mh2nSigmaEPt_eID[trg]    = new TH2F(Form("mh2nSigmaEPt_eID_%i",trg),"",600,-30,30,400,0,20);
    //mh2PoePt[trg]            = new TH2F(Form("mh2PoePt_%i",trg),"",600,-30,30,400,0,20);
    //mh2nPhiPt[trg]           = new TH2F(Form("mh2nPhiPt_%i",trg),"",20,0,20,400,0,20);
    //mh2nEtaPt[trg]           = new TH2F(Form("mh2nEtaPt_%i",trg),"",20,0,20,400,0,20);
    //mh2PhiDistPt[trg]        = new TH2F(Form("mh2PhiDistPt_%i",trg),"",200,-10,10,400,0,20);
    //mh2ZDistPt[trg]          = new TH2F(Form("mh2ZDistPt_%i",trg),"",400,-20,20,400,0,20);
    // mh2PhiQPt[trg]           = new TH2F(Form("mh2PhiQPt_%i",trg),"",200,-10,10,800,-20,20);
    //mh2TofPtAll[trg]         = new TH2F(Form("mh2TofPtAll_%i",trg),"",400,-20,20,400,0,20);
    //mh2TofPtE[trg]           = new TH2F(Form("mh2TofPtE_%i",trg),"",400,-20,20,400,0,20);
    mh2InvMassPtAll[trg]     = new TH2F(Form("mh2InvMassPtAll_%i",trg),"",1000,0,10,1000,0,10);
    mh2InvMassPtE[trg]       = new TH2F(Form("mh2InvMassPtE_%i",trg),"",1000,0,10,1000,0,10);
    mh2InvMassPtLS[trg]      = new TH2F(Form("mh2InvMassPtLS_%i",trg),"",1000,0,10,1000,0,10);
    mh2InvMassPtUS[trg]      = new TH2F(Form("mh2InvMassPtUS_%i",trg),"",1000,0,10,1000,0,10);
    mh2InvMassPtUS[trg]->Sumw2(); mh2InvMassPtLS[trg]->Sumw2(); mh1PtETracks[trg]->Sumw2();
    
    mh2nSigmaPionPt[trg]       = new TH2F(Form("mh2nSigmaPionPt_%i",trg),"",1000,-10,10,1000,0,10);
    
    //cout << "at delPhi" << endl;
    mh3DelPhiIncl[trg]       = new TH3F(Form("mh3DelPhiIncl_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiPhotLS[trg]     = new TH3F(Form("mh3DelPhiPhotLS_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiPhotUS[trg]     = new TH3F(Form("mh3DelPhiPhotUS_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiPhotUSNP[trg]   = new TH3F(Form("mh3DelPhiPhotUSNP_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiPhotLSNP[trg]   = new TH3F(Form("mh3DelPhiPhotLSNP_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiPhotInclNP[trg] = new TH3F(Form("mh3DelPhiPhotInclNP_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiIncl[trg]->Sumw2();mh3DelPhiPhotLS[trg]->Sumw2();mh3DelPhiPhotUS[trg]->Sumw2();
    mh3DelPhiPhotInclNP[trg]->Sumw2();mh3DelPhiPhotLSNP[trg]->Sumw2();mh3DelPhiPhotUSNP[trg]->Sumw2();
    
    mh3DelPhiInclWt[trg]     = new TH3F(Form("mh3DelPhiInclWt_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiPhotLSWt[trg]   = new TH3F(Form("mh3DelPhiPhotLSWt_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiPhotUSWt[trg]   = new TH3F(Form("mh3DelPhiPhotUSWt_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiInclWt[trg]->Sumw2();mh3DelPhiPhotLSWt[trg]->Sumw2();mh3DelPhiPhotUSWt[trg]->Sumw2();
    
    mh3DelPhiHadHad[trg]     = new TH3F(Form("mh3DelPhiHadHad_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh3DelPhiHadHadWt[trg]   = new TH3F(Form("mh3DelPhiHadHadWt_%i",trg),"",200,-10,10,200,0,20,100,0.,10.);
    mh1PtHadTracks[trg]      = new TH1F(Form("mh1PtHadTracks_%i",trg),"",200,0.,20.);
    mh1PtHadTracks[trg]->Sumw2(); mh3DelPhiHadHad[trg]->Sumw2(); mh3DelPhiHadHadWt[trg]->Sumw2();
    
    //cout << "at pileup" << endl;
    // Pileup Hists
    for(Int_t q=0;q<1;q++)
    {
      //  cout << "pileup count: " << q << endl;
      mh3nTracksZdcx[trg][q]    = new TH3F(Form("mh3nTracksZdcx_%i_%i",trg,q),"",200,0,20,100,0.,10.,200,0,20000);
      mh3nTracksZdcxUS[trg][q]  = new TH3F(Form("mh3nTracksZdcxUS_%i_%i",trg,q),"",200,0,20,100,0.,10.,200,0,20000);
      mh3nTracksZdcxLS[trg][q]  = new TH3F(Form("mh3nTracksZdcxLS_%i_%i",trg,q),"",200,0,20,100,0.,10.,200,0,20000);
      mh3nTracksZdcxHad[trg][q] = new TH3F(Form("mh3nTracksZdcxHad_%i_%i",trg,q),"",200,0,20,100,0.,10.,200,0,20000);
      mh3nTracksZdcx[trg][q]->Sumw2(); mh3nTracksZdcxUS[trg][q]->Sumw2(); mh3nTracksZdcxLS[trg][q]->Sumw2();mh3nTracksZdcxHad[trg][q]->Sumw2();
    }
    mh2PtEZdcx[trg]          = new TH2F(Form("mh2PtEZdcx_%i",trg),"",200,0,20,200,0,20000);
    mh2PtEZdcxUS[trg]        = new TH2F(Form("mh2PtEZdcxUS_%i",trg),"",200,0,20,200,0,20000);
    mh2PtEZdcxLS[trg]        = new TH2F(Form("mh2PtEZdcxLS_%i",trg),"",200,0,20,200,0,20000);
    mh2PtEZdcxHad[trg]       = new TH2F(Form("mh2PtEZdcxHad_%i",trg),"",200,0,20,200,0,20000);
    mh2PtEZdcx[trg]->Sumw2(); mh2PtEZdcxUS[trg]->Sumw2(); mh2PtEZdcxLS[trg]->Sumw2(); mh2PtEZdcxHad[trg]->Sumw2();
    //cout << "end " << trg << endl;
  }
  
  
  /// Mixed Events
  mh3MixedDelPhi          = new TH3F("mh3MixedDelPhi","",200,-10,10,200,0,20,100,0.,10.);
  mh3MixedDelEta          = new TH3F("mh3MixedDelEta","",200,-10,10,200,0,20,100,0.,10.);
  mh3MixedEtaPhi          = new TH3F("mh3MixedEtaPhi","",200,-10,10,200,-5,5,100,0.,10.);
  mh3MixedDelPhiWt        = new TH3F("mh3MixedDelPhiWt","",200,-10,10,200,0,20,100,0.,10.);
  mh3MixedDelEtaWt        = new TH3F("mh3MixedDelEtaWt","",200,-10,10,200,0,20,100,0.,10.);
  mh3MixedEtaPhiWt        = new TH3F("mh3MixedEtaPhiWt","",200,-10,10,200,-5,5,100,0.,10.);
  
  // 1D histos for 2.5 to 3.5 GeV epT bin, HT0, hPt>0.3 GeV, For comparison with previous analysis
  mh1delPhiIncl         = new TH1F("mh1delPhiIncl","",200,-10,10);  // TrigCount bin 1
  mh1delPhiUS           = new TH1F("mh1delPhiUS","",200,-10,10);    // TrigCount bin 2
  mh1delPhiLS           = new TH1F("mh1delPhiLS","",200,-10,10);    // TrigCount bin 3
  mh1delPhiHad          = new TH1F("mh1delPhiHad","",200,-10,10);   // TrigCount bin 4
  mh1TrigCount          = new TH1F("mh1TrigCount","",10,0,10);      // use AddBinContent(bin) to count number of trigs
  
}

//-----------------------------------------------------------------------------
void StNpeRead::writeObjects()
{
  mOutputFile->cd();
  
  //cout << "writeObjects Top." << endl;
  /// Z. Histos
  for(Int_t trg=0; trg<4; trg+=2)
  {
    // cout<< "writeObjects Trg. " << trg << endl;
    mh1PtAllTracks[trg]     -> Write();
    mh1PtETracks[trg]       -> Write();
    // mh2nSigmaEPt[trg]       -> Write();
    //mh2nSigmaEPt_eID[trg]   -> Write();
    //mh2PoePt[trg]           -> Write();
    //mh2nPhiPt[trg]          -> Write();
    //mh2nEtaPt[trg]          -> Write();
    //mh2PhiDistPt[trg]       -> Write();
    //mh2ZDistPt[trg]         -> Write();
    //mh2PhiQPt[trg]          -> Write();
    //mh2TofPtAll[trg]        -> Write();
    //mh2TofPtE[trg]          -> Write();
    mh2InvMassPtAll[trg]    -> Write();
    mh2InvMassPtE[trg]      -> Write();
    mh2InvMassPtUS[trg]     -> Write();
    mh2InvMassPtLS[trg]     -> Write();
    mh2nSigmaPionPt[trg]    -> Write();
    mh3DelPhiIncl[trg]      -> Write();
    mh3DelPhiPhotLS[trg]    -> Write();
    mh3DelPhiPhotUS[trg]    -> Write();
    mh3DelPhiPhotUSNP[trg]  -> Write();
    mh3DelPhiPhotLSNP[trg]  -> Write();
    mh3DelPhiPhotInclNP[trg]-> Write();
    mh3DelPhiInclWt[trg]    -> Write();
    mh3DelPhiPhotLSWt[trg]  -> Write();
    mh3DelPhiPhotUSWt[trg]  -> Write();
    mh3DelPhiHadHad[trg]    -> Write();
    mh3DelPhiHadHadWt[trg]  -> Write();
    mh1PtHadTracks[trg]     -> Write();
    
    // Pileup Histos
    mh2PtEZdcx[trg]         -> Write();
    mh2PtEZdcxUS[trg]       -> Write();
    mh2PtEZdcxLS[trg]       -> Write();
    mh2PtEZdcxHad[trg]      -> Write();
    for(Int_t q = 0; q < 1; q++){
      cout << "q: " << q << endl;
      mh3nTracksZdcx[trg][q]    -> Write();
      mh3nTracksZdcxUS[trg][q]  -> Write();
      mh3nTracksZdcxLS[trg][q]  -> Write();
      mh3nTracksZdcxHad[trg][q] -> Write();
    }
  }
  
  // Mixed Events
  mh3MixedDelPhi          -> Write();
  mh3MixedDelEta          -> Write();
  mh3MixedEtaPhi          -> Write();
  mh3MixedDelPhiWt        -> Write();
  mh3MixedDelEtaWt        -> Write();
  mh3MixedEtaPhiWt        -> Write();
  
  
  // 1D Hists for comparison to old analysis 2.5-3.5 GeV epT bin
  mh1delPhiIncl  -> Write();
  mh1delPhiUS    -> Write();
  mh1delPhiLS    -> Write();
  mh1delPhiHad   -> Write();
  mh1TrigCount   -> Write();
  
  
  mOutputFile->Close();
}

//-----------------------------------------------------------------------------
void StNpeRead::read(TString fileName)
{  
  // Read Input File and Grab the Tree, setting Events to NpeEvent
  cout<<"input filename = "<<fileName.Data()<<endl;
  TFile* inFile = new TFile(fileName.Data(),"READ");
  TTree* tree = (TTree*)inFile->Get("T");
  
  tree->GetBranch("dEvent")->SetAutoDelete(kFALSE);
  tree->SetBranchAddress("dEvent", &mNpeEvent);
  
  TClonesArray* aTracks = 0;
  TClonesArray* aPairs = 0;
  
  // events loop
  cout<<"Event"<<tree->GetEntriesFast()<<endl;
  for (UInt_t i = 0; i < tree->GetEntriesFast(); i++)
  {
    tree->GetEntry(i);
    
    //  Do_run_QA(mNpeEvent);
    
    if(isBadRun(mNpeEvent)) continue;
    
    Int_t bTrg=999;
    if(!isGoodEvent(mNpeEvent,bTrg)) continue;
    TH1F::SetDefaultSumw2();
    // cout<< "pass Good Event"<<endl;
    
    // Do_run_QA(mNpeEvent);
    
    aPairs=mNpeEvent->electronPair();
    aTracks=mNpeEvent->tracks();
    
    // Sort based on trigger type (High Tower #, Beam-Beam Min Bias, Time of Flight, Vertex Position Min Bias)
    if(mNpeEvent->isHT0_BBCMB_TOF0())
    {
      bTrg=0;
      
      Double_t  ps=mPrescales->GetPrescale(mNpeEvent->runId(),HT0BBCMBTOF0);
      if(ps<0) continue;
      if(mPrescales->GetLivetime(mNpeEvent->runId(), HT0BBCMBTOF0) < 0) continue;
      zFillHists( bTrg, mNpeEvent, ps);
      /* Fill_RunQA(bTrg,mNpeEvent);
       Fill_PhotonicE_hist ( bTrg, mNpeEvent , ps );
       Fill_Inclusive_hist ( bTrg, mNpeEvent , ps );
       Fill_event_hist(mNpeEvent,bTrg,ps);*/
    }
    if(mNpeEvent->isHT1_BBCMB_TOF0())
    {
      bTrg=1;
      
      Double_t  ps=mPrescales->GetPrescale(mNpeEvent->runId(),HT1BBCMBTOF0);
      if(ps<0) continue;
      // zFillHists( bTrg, mNpeEvent, ps);
      // Fill_RunQA(bTrg,mNpeEvent);
    }
    if(mNpeEvent->isHT2_BBCMB())
      
    {
      bTrg=2;
      
      Double_t  ps=mPrescales->GetPrescale(mNpeEvent->runId(),HT2BBCMB);
      if(ps<0) continue;
      if(mPrescales->GetLivetime(mNpeEvent->runId(), HT2BBCMB) < 0) continue;
      zFillHists( bTrg, mNpeEvent, ps);
      
      /* Fill_RunQA(bTrg,mNpeEvent);
       Fill_PhotonicE_hist ( bTrg, mNpeEvent , ps );
       Fill_Inclusive_hist ( bTrg, mNpeEvent , ps );
       Fill_event_hist(mNpeEvent,bTrg,ps);	*/
    }
    if(mNpeEvent->isVPDMB())
    {
      bTrg=3;
      
      Double_t ps=mPrescales->GetPrescale(mNpeEvent->runId(),VPDMB);
      if(ps<0) continue;
      //zFillHists( bTrg, mNpeEvent, ps);
      /* Fill_RunQA(bTrg,mNpeEvent);
       Fill_PhotonicE_hist ( bTrg, mNpeEvent , ps );
       Fill_Inclusive_hist ( bTrg, mNpeEvent , ps );
       Fill_event_hist(mNpeEvent,bTrg,ps);
       Fill_Kaon_Kaon(mNpeEvent,bTrg);*/
    }
    // </ end trigger sort >
    
    if(i%10000==0) cout<< " Working on event: "<<i<<endl;
    
  } // ... end event loop
  
  inFile->Close();
  //zFillProjections();
}

/// ZACH for quick search

void StNpeRead::zFillHists (Int_t bTrg,StDmesonEvent * mNpeEvent ,Double_t ps ) // Zach Analysis Loops, only for HT triggers to match Dunkleberger Analysis (comparison)
{
  zFill_Inclusive(bTrg, mNpeEvent, ps);
  zFill_Photonic (bTrg, mNpeEvent, ps);
}

void StNpeRead::zFill_Inclusive (Int_t trg,StDmesonEvent * mNpeEvent ,Double_t ps ) // Fill histograms for events that are non-paired electrons                             
{
  Float_t hptCut[4]={0.3,0.5,1.0,1.5};
  
  TClonesArray* aTracks = 0;
  aTracks=mNpeEvent->tracks();
  TClonesArray* aPairs = 0;
  aPairs=mNpeEvent->electronPair();
  isAddedToBuffer = kFALSE;
  Double_t vz = mNpeEvent->primaryVertex().z();
  for(Int_t it=0;it<mNpeEvent->nTracks();it++)
  {
    Bool_t isInPair = kFALSE;
    Bool_t isAddedToNorm = kFALSE;
    StDmesonTrack* trk = (StDmesonTrack*)aTracks->At(it);
    int  Run_ID=-1;
    map <int,int>::iterator iter=runID_List.find(mNpeEvent->runId());
    if(iter!=runID_List.end())
      Run_ID=iter->second;
    
    Float_t Phi  = trk->pMom().phi();
    Float_t nSig = trk->nSigmaElectron();
    Float_t pT   = trk->pMom().perp();
    Float_t q    = trk->charge();
    Float_t beta = trk->btofBeta();
    Float_t p    = trk->pMom().mag();
    Float_t m_m  = p*p*(1/(beta*beta)-1);
    
    mh1PtAllTracks[trg]  -> Fill(pT);
    //mh2nSigmaEPt[trg]    -> Fill(nSig,pT);
    //mh2TofPtAll[trg]     -> Fill(1/beta -1, pT);
    mh2InvMassPtAll[trg] -> Fill(m_m,pT);
    mh2nSigmaPionPt[trg] -> Fill(trk->nSigmaPion(),pT);
    if(isHotTower(trk,trg)) // If in a hot tower, don't do any other checks, skip track
      continue;
    if(pass_cut_GoodTrack(trk) && pass_cut_nsigmaE(trk) && pass_cut_Pt_Eta(trk) && pass_cut_ADC(trg,trk) &&
       pass_cut_Match_EMC_Dz(trk) && pass_cut_Match_EMC_Dphi(trk) && pass_cut_poe(trk) && pass_cut_EMC(trk)) // Is track an electron and the ADC0 big enough to be the trigger?
    {
      // if(!(trk->trgTowDsmAdc() < 0.1*trk->adc0())) // This matches the data analysis with embedding, according to Xiaozhi who did the embedding
      //  continue;
      // DEBUG cout << "!!There is NPE!!" << endl;
      
      for(Int_t ip=0;ip<mNpeEvent->nElectronPair();ip++) // loop over pair branch to check if singleTrack also in Pair
      {
        StElectronPair* pair = (StElectronPair*)aPairs->At(ip);
        StDmesonTrack*  etrk = (StDmesonTrack*)aTracks->At(pair->electronId());
        StDmesonTrack*  ptrk = (StDmesonTrack*)aTracks->At(pair->partnerId());
        
        if(ptrk->gMom().perp()< cuts::partnerElecGlobalPt) continue;
        if((trk == etrk || trk == ptrk) && pair->pairDca() < cuts::pairDCA && pair->m() < cuts::massDCA && etrk->charge()!=ptrk->charge()) // pair cuts + check for track id match
        {
          // DEBUG cout << "Tracks are linked." << endl;
          isInPair = kTRUE;
        }
      }
      // Mixed Event
      if(!isAddedToBuffer) // Only compute it once per event, to avoid calculating with possibly correlated tracks
      {
        computeMixedEvents(trk,vz);
        isAddedToBuffer=kTRUE;
      }
      
      Float_t ePhi = Phi;
      Float_t eEta = trk->pMom().pseudoRapidity();
      Float_t poe  = trk->pMom().mag()/trk->e0();
      Float_t nPhi = trk->nPhi();
      Float_t nEta = trk->nEta();
      Float_t phiDist = trk->phiDist();
      Float_t zDist   = trk->zDist();
      Float_t epT  = pT;
      Float_t eq   = q;
      Float_t weight = getTrgEff(trg,pT); // Trigger Electron
      Float_t zdc = mNpeEvent->ZDCx();
      // Calculate weight from
      
      if(!isInPair){
        mh1PtETracks[trg] -> Fill(epT,weight);        // Inclusive Norm
        mh2PtEZdcx[trg]   -> Fill(epT,zdc,weight);    // To normalize ZDC bins by hadrons/trigger in pileup
        if(epT > 2.5 && epT < 3.5 && trg == 0)
          mh1TrigCount->Fill(0.5,weight); // bin 1 = Inclusive
      }
      /* mh2PhiDistPt[trg] -> Fill(phiDist,epT);
       mh2ZDistPt[trg]   -> Fill(zDist,epT);
       mh2nPhiPt[trg]    -> Fill(nPhi,epT);
       mh2nEtaPt[trg]    -> Fill(nEta,epT);
       mh2PoePt[trg]     -> Fill(poe,epT);
       mh2nSigmaEPt_eID[trg] -> Fill(nSig,epT);
       mh2TofPtE[trg]    -> Fill(1/beta -1, pT);*/
      mh2InvMassPtE[trg]-> Fill(m_m,pT);
      
      Int_t printCheck = 0;
      for(Int_t ih = 0; ih < mNpeEvent->nTracks(); ih++) // Want to loop over all tracks looking for hads. Not going to double count, since there's only 1 NPE-e/evt on average (in events with NPE, which are rare)
      {
        StDmesonTrack* htrk = (StDmesonTrack*)aTracks->At(ih);
        Float_t hpT   = htrk->pMom().perp();
        
        if(trk != htrk && pass_cut_hTrack(htrk)) // Is this track pass as hadron track quality AND not the same track
        {
          
          // Make mixed events buffer
          addToHadBuffer(htrk,vz);
          
          Float_t hp    = htrk->pMom().mag();
          Float_t hbeta = htrk->btofBeta();
          Float_t hm_m  = p*p*(1/(beta*beta)-1);
          Float_t hPhi  = htrk->pMom().phi();
          Float_t hpoe  = htrk->pMom().mag()/trk->e0();
          Float_t hq    = htrk->charge();
          Float_t dPhi  = ePhi-hPhi;
          Float_t hEta  = htrk->gMom().pseudoRapidity();
          Float_t hpEta = htrk->pMom().pseudoRapidity(); //zyj
          //          Float_t dEta  = eEta - hEta;
          Float_t dEta  = eEta - hpEta; // zyj
          
          Float_t wt    = getHadronWt(hpT,hEta)*weight; // Trigger Electron and Hadron
          
          dPhi = correct_dPhi(dPhi);
          if(!isInPair && pass_dEta(dEta)) // Not interested in any events part of pairs for semi-inclusive distrib
          {
            mh3DelPhiIncl[trg] -> Fill(dPhi,epT,hpT,weight); // This weight only for electron trigger eff
            mh3DelPhiInclWt[trg] -> Fill(dPhi,epT,hpT,wt);
            mh3DelPhiPhotInclNP[trg] -> Fill(dPhi,epT,hpT,wt);
            
            if(epT > 2.5 && epT < 3.5 && trg == 0 && hpT > 0.3)
              mh1delPhiIncl -> Fill(dPhi,wt);
            
            // For Pileup
            for(Int_t q = 0; q < 1; q++)
            {
              if(hpT >= hptCut[q])
                mh3nTracksZdcx[trg][q]->Fill(epT,hpT,zdc,wt);
            }
          }
        }
      }
    }
    
    if(pass_cut_GoodTrack(trk) && pass_cut_nsigmaPi(trk) && pass_cut_Pt_Eta(trk)) // Is this track part of pure pion sample
    {
      Float_t phi = trk->pMom().phi();
      //Float_t pT  = trk->gMom().perp();
      Float_t pT  = trk->pMom().perp(); // zyj changed, this is the triggered hadron, need to same as e cut
      //      Float_t eta = trk->gMom().pseudoRapidity();
      Float_t eta = trk->pMom().pseudoRapidity(); //zyj, this is the triggered hadron, need to same as e cut
      
      Float_t zdc = mNpeEvent->ZDCx();
      mh1PtHadTracks[trg] -> Fill(pT);
      mh2PtEZdcxHad[trg]  -> Fill(pT,zdc);
      if(pT > 2.5 && pT < 3.5 && trg == 0)
        mh1TrigCount->Fill(3.5); // bin 4 = hadron trigs
      
      for(Int_t ih = 0; ih < mNpeEvent->nTracks(); ih++) // Want to loop over all tracks looking for hads. Not going to double count, since there's only 1 NPE-e/evt on average (in events with NPE, which are rare)
      {
        StDmesonTrack* htrk = (StDmesonTrack*)aTracks->At(ih);
        Float_t hpT   = htrk->pMom().perp();
        
        if(trk != htrk && pass_cut_hTrack(htrk)) // Is this track pass as hadron track quality AND not the same track
        {
          Float_t hp    = htrk->pMom().mag();
          Float_t hPhi  = htrk->pMom().phi();
          Float_t dPhi  = phi-hPhi;
          Float_t hEta  = htrk->gMom().pseudoRapidity();
          Float_t hpEta  = htrk->pMom().pseudoRapidity(); // zyj
          //          Float_t dEta  = eta - hEta;
          Float_t dEta  = eta - hpEta; //zyj
          
          Float_t wt    = getHadronWt(hpT,hEta);
          //Float_t zdc = mNpeEvent->ZDCx();
          /* DEBUG if(printCheck < 20){
           cout << "WEIGHT: " << wt << endl;
           printCheck++;}*/
          dPhi = correct_dPhi(dPhi);
          //if(dPhi > (3.*pi)/2.) dPhi = dPhi-2*pi;
          //if(dPhi < (-1*pi)/2.) dPhi = dPhi+2*pi;
          if(pass_dEta(dEta))
          {
            mh3DelPhiHadHad[trg] -> Fill(dPhi,pT,hpT);
            mh3DelPhiHadHadWt[trg] -> Fill(dPhi,pT,hpT,wt);
            if(pT > 2.5 && pT < 3.5 && trg == 0 && hpT > 0.3)
              mh1delPhiHad -> Fill(dPhi,wt);
            for(Int_t q = 0; q < 1; q++)
            {
              if(hpT >= hptCut[q] && pass_dEta(dEta))
                mh3nTracksZdcxHad[trg][q]->Fill(pT,hpT,zdc,wt);
            }
          }
        }
      }
    }
  }
}

void StNpeRead::zFill_Photonic (Int_t bTrg,StDmesonEvent * mNpeEvent ,Double_t ps )
{
  Float_t hptCut[4]={0.3,0.5,1.0,1.5};
  
  TClonesArray* aTracks = 0;
  TClonesArray* aPairs = 0;
  aPairs=mNpeEvent->electronPair();
  aTracks=mNpeEvent->tracks();
  
  for(Int_t ip=0;ip<mNpeEvent->nElectronPair();ip++)
  {
    StElectronPair* pair = (StElectronPair*)aPairs->At(ip);
    StDmesonTrack*  etrk = (StDmesonTrack*)aTracks->At(pair->electronId());
    StDmesonTrack*  ptrk = (StDmesonTrack*)aTracks->At(pair->partnerId());
    if(ptrk->gMom().perp()< cuts::partnerElecGlobalPt) continue;
    if(pair->pairDca() < cuts::pairDCA && pair->m() < cuts::massDCA) // Pair Conditions
    {
      // if(pass_cut_Pt_Eta(etrk) && pass_cut_nsigmaE(etrk) && pass_cut_GoodTrack(etrk) && pass_cut_ADC(bTrg,etrk)) // Primary Track Conditions
      // {
      if(isHotTower(etrk,bTrg)) // If in a hot tower, don't do any other checks, skip track
        continue;
      if(pass_cut_GoodTrack(etrk) && pass_cut_nsigmaE(etrk) && pass_cut_Pt_Eta(etrk) && pass_cut_ADC(bTrg,etrk) &&
         pass_cut_Match_EMC_Dz(etrk) && pass_cut_Match_EMC_Dphi(etrk) && pass_cut_poe(etrk) && pass_cut_EMC(etrk)) // Is track an electron and the ADC0 big enough to be the trigger?
      {
        // if(!(etrk->trgTowDsmAdc() < 0.1*etrk->adc0())) // This matches the data analysis with embedding, according to Xiaozhi who did the embedding
        //	continue;
        Float_t ep = etrk->pMom().mag();
        Float_t ebeta = etrk->btofBeta();
        Float_t em_m = ep*ep*(1/(ebeta*ebeta)-1);
        Float_t ePhi = etrk->pMom().phi();
        Float_t eEta = etrk->pMom().pseudoRapidity();
        Float_t epoe = etrk->pMom().mag()/etrk->e0();
        Float_t eq = etrk->charge();
        Float_t epT = etrk->pMom().perp();
        
        //        Float_t pp = ptrk->gMom().mag(); //partner e
        //        Float_t pbeta = ptrk->btofBeta();
        //        Float_t pm_m = pp*pp*(1/(pbeta*pbeta)-1);
        //        Float_t pPhi = ptrk->gMom().phi();
        //        Float_t ppoe = ptrk->gMom().mag()/ptrk->e0(); // zyj comment all this not used variables
        Float_t pq = ptrk->charge();
        Float_t zdc = mNpeEvent->ZDCx();
        
        Float_t weight = getTrgEff(bTrg,epT); // Trigger Electron
        
        /// For Pair information sorting w/o Hadrons
        if(eq == pq)
        {
          mh2InvMassPtLS[bTrg]  -> Fill(pair->m(),epT,weight); // add prescale to compare counts with XB
          mh2PtEZdcxLS[bTrg]    -> Fill(epT,zdc,weight);
          if(epT > 2.5 && epT < 3.5 && bTrg == 0)
            mh1TrigCount->Fill(2.5,weight); // bin 3 = Like Sign
        }
        if(eq != pq)
        {
          mh2InvMassPtUS[bTrg]  -> Fill(pair->m(),epT,weight); // Same as previous comment
          mh2PtEZdcxUS[bTrg]    -> Fill(epT,zdc,weight);
          if(epT > 2.5 && epT < 3.5 && bTrg == 0)
            mh1TrigCount->Fill(1.5,weight); // bin 2 = Unlike Sign
        }
        
        for(Int_t ih = ip; ih < mNpeEvent->nTracks(); ih++) // loop over all tracks in the event
        {
          StDmesonTrack* htrk = (StDmesonTrack*)aTracks->At(ih);
          Float_t hpT = htrk->pMom().perp();
          if(etrk != htrk && pass_cut_hTrack(htrk)) // Is this track a hadron and not the same track or e-?
          {
            Float_t hPhi = htrk->pMom().phi();
            Float_t dPhi  = ePhi-hPhi;
            Float_t hEta  = htrk->gMom().pseudoRapidity();
            Float_t hpEta  = htrk->pMom().pseudoRapidity();
            
            //            Float_t dEta  = eEta - hEta;
            Float_t dEta  = eEta - hpEta;
            
            Float_t wt = weight*getHadronWt(hpT,hEta); // Electron and Hadron
            dPhi = correct_dPhi(dPhi);
            //if(dPhi > (3.*pi)/2.) dPhi = dPhi-2*pi;
            //if(dPhi < -1*pi/2.) dPhi = dPhi+2*pi;
            if(eq == pq && ptrk != htrk && pass_dEta(dEta))
            {
              mh3DelPhiPhotLS[bTrg] -> Fill(dPhi,epT,hpT,weight); // weight for elect trig eff
              mh3DelPhiPhotLSWt[bTrg] -> Fill(dPhi,epT,hpT,wt);
              mh3DelPhiPhotLSNP[bTrg] -> Fill(dPhi,epT,hpT,wt);
              if(epT > 2.5 && epT < 3.5 && bTrg == 0 && hpT > 0.3)
                mh1delPhiLS -> Fill(dPhi,wt);
            }
            if(eq != pq && ptrk != htrk && pass_dEta(dEta))
            {
              mh3DelPhiPhotUS[bTrg] -> Fill(dPhi,epT,hpT,weight); // weight for elect trig eff
              mh3DelPhiPhotUSWt[bTrg] -> Fill(dPhi,epT,hpT,wt);
              mh3DelPhiPhotUSNP[bTrg] -> Fill(dPhi,epT,hpT,wt);
              if(epT > 2.5 && epT < 3.5 && bTrg == 0 && hpT > 0.3)
                mh1delPhiUS -> Fill(dPhi,wt);
            }
            // For Pileup
            for(Int_t q = 0; q < 1; q++)
            {
              if(hpT >= hptCut[q]){
                if(eq == pq && ptrk != htrk && pass_dEta(dEta))
                  mh3nTracksZdcxLS[bTrg][q]->Fill(epT,hpT,zdc,wt);
                if(eq != pq && ptrk != htrk && pass_dEta(dEta))
                  mh3nTracksZdcxUS[bTrg][q]->Fill(epT,hpT,zdc,wt);
              }
            }
          }
        }
      }
    }
  }
}

//eID cuts
Bool_t StNpeRead::pass_cut_nsigmaE(StDmesonTrack* trk)
{
  if(!trk) return kFALSE;
  Float_t nSigmaE=trk->nSigmaElectron();
  
  if(nSigmaE>cuts::nsigmae_low && nSigmaE<cuts::nsigmae_high)
    return kTRUE;
  else return kFALSE;
}

//Select pure pion sample
Bool_t StNpeRead::pass_cut_nsigmaPi(StDmesonTrack* trk)
{
  if(!trk) return kFALSE;
  Float_t nSigmaP=trk->nSigmaPion();
  
  if(nSigmaP>cuts::nsigmap_low && nSigmaP<cuts::nsigmap_high)
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeRead::pass_cut_ADC(Int_t trg, StDmesonTrack* trk)
{
  // Different cuts for different trigs (not in StCuts, since not constant)
//  Float_t adc0Cuts[4] = {180.,180.,300.,0.};
  Float_t adc0Cuts[4] = {196.,180.,316.,0.}; //sys
  Float_t dsmAdcCuts[4] = {11.,11.,18.,0.};
  if(trg == 3) // ADC cuts not for MB events
    return kTRUE;
  
  if(trk->adc0() > adc0Cuts[trg] && trk->trgTowDsmAdc() > dsmAdcCuts[trg])
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeRead::pass_cut_poe(StDmesonTrack * trk)
{
  Float_t P=trk->pMom().mag();
  Float_t E=trk->e0();
  //cout<<""
  if(P/E>cuts::poe_low && P/E<cuts::poe_high && cuts::Pt_cut<P)
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeRead::pass_cut_hTrack(StDmesonTrack * trk)
{
  Float_t Pt=trk->pMom().perp();
  Float_t eta=trk->pMom().pseudoRapidity();
  Int_t nhitDedx=trk->nHitsDedx();
  Int_t nhitsFit=trk->nHitsFit();
  Int_t nhitsMax=trk->nHitsMax();
  Float_t dca = trk->dca();
  //cout<<""
  if(Pt > cuts::hadPtMin && fabs(eta) < cuts::hadEta && nhitDedx >= cuts::hadDedx && nhitsFit >= cuts::hadHitsFit && dca < cuts::hadDCA && dca > 0)
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeRead::pass_loose_track_qaulity( StDmesonTrack *trk, Int_t bTrg)
{
  Float_t Pt=trk->pMom().perp();
  Float_t eTa=trk->pMom().pseudoRapidity();
  Int_t nhitDedx=trk->nHitsDedx();
  Int_t nhitsFit=trk->nHitsFit();
  Int_t nhitsMax=trk->nHitsMax();
  Float_t gDca=trk->dca();
  
  if(gDca<3 && fabs(eTa)<1 && 0.2<Pt && fabs(trk->charge())==1 && (bTrg!=0 || ((bTrg==0) &&  trk->btofMatchFlag()>0)))
    return kTRUE;
  
  else return kFALSE;
}
Bool_t StNpeRead::pass_cut_GoodTrack(StDmesonTrack * trk)
{
  
  Float_t Pt=trk->pMom().perp();
  Float_t eTa=trk->pMom().pseudoRapidity();
  Int_t nhitDedx=trk->nHitsDedx();
  Int_t nhitsFit=trk->nHitsFit();
  Int_t nhitsMax=trk->nHitsMax();
  Float_t gDca=trk->dca();
  Float_t first_point= trk->firstTpcPointR();
  //cout<<"first"<<Ds_fst<<endl;
  if(gDca<cuts::gDca && cuts::nhitDedx<nhitDedx &&  nhitsFit>cuts::nhitsFit && (Float_t) nhitsFit/nhitsMax>cuts::nhit_Possmax  &&  first_point<cuts::first_point_cut)
    
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeRead::pass_cut_GoodTrack_Hadron(StDmesonTrack * trk)
{
  
  Float_t Pt=trk->gMom().perp();
  Float_t eTa=trk->gMom().pseudoRapidity();
  Int_t nhitDedx=trk->nHitsDedx();
  Int_t nhitsFit=trk->nHitsFit();
  Int_t nhitsMax=trk->nHitsMax();
  Float_t gDca=trk->dca();
  Float_t first_point= trk->firstTpcPointR();
  //cout<<"first"<<Ds_fst<<endl;
  if(gDca<cuts::gDca && cuts::nhitDedx<nhitDedx &&  nhitsFit>cuts::nhitsFit && (Float_t) nhitsFit/nhitsMax>cuts::nhit_Possmax  &&  first_point<cuts::first_point_cut)
    
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeRead::pass_cut_Pt_Eta(StDmesonTrack *trk)
{
  Float_t Pt=trk->pMom().perp();
  Float_t eTa=trk->pMom().pseudoRapidity();
  if(fabs(eTa)<cuts::eta_low && Pt>cuts::pt)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeRead::pass_cut_Pt_Eta_Hadron(StDmesonTrack *trk)
{
  Float_t Pt=trk->gMom().perp();
  Float_t eTa=trk->gMom().pseudoRapidity();
  if(fabs(eTa)<cuts::eta_low && Pt>cuts::pt)
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeRead::pass_cut_EMC(StDmesonTrack *trk)
{
  Int_t nEta=trk->nEta();
  Int_t nPhi=trk->nPhi();
  if(nEta>cuts::NEta && nPhi>cuts::NPhi && cuts::Pt_cut<=trk->pMom().perp())
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeRead::is_EMC_Track(StDmesonTrack *trk)
{
  Int_t nEta=trk->nEta();
  Int_t nPhi=trk->nPhi();
  if(nEta > 0 && nPhi > 0 && cuts::Pt_cut<=trk->pMom().perp())
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeRead::pass_cut_Match_EMC_Dz(StDmesonTrack * trk){
  
  //  fabs(eTrk->zDist())<cuts::Dz_cut && fabs(eTrk->phiDist())<cuts::Dphi_cut
  //m/
  if(cuts::Dz_cut>fabs(trk->zDist()) && cuts::Pt_cut<=trk->pMom().perp())
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeRead::pass_cut_Match_EMC_Dphi(StDmesonTrack * trk){
  
  //
  if(cuts::Dphi_cut>fabs(trk->phiDist()) && cuts::Pt_cut<=trk->pMom().perp())
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeRead::pass_cut_Tof_Match( StDmesonTrack *trk){
  
  //
  Float_t tof_YTlocal=trk->btofYLocal();
  // trk->btofBeta()>0
  if(fabs(tof_YTlocal)<cuts::tof_Ylocal &&  trk->btofMatchFlag()>0 && trk->btofBeta()>0)
    return kTRUE;
  else  return kFALSE;
}
Bool_t StNpeRead:: pass_cut_Tof( StDmesonTrack *trk){
  //
  
  Float_t tofbeta=trk->btofBeta();
  if(fabs(1/tofbeta-1)<cuts::tofbeta)
    
    return kTRUE;
  
  else return kFALSE;
}

//-----------------------------------------------------------------------------

Bool_t StNpeRead::isHotTower(StDmesonTrack *trk,Int_t bTrg)
{
  
  // Int_t  HT0_Hot_towerlist[] ={32,52,115,246,268,276,294,386,510,562,682,750,773,894,987,994,1043,1064,1143,1233,1264,1285,1307,1487,1593,1710,1733,1823,1824,1851,1946,2022,2044,2064,2110,2146,2163,2165,2203,2291,2314,2522,2530,2634,2653,2835,2864,2866,2973,3006,3062,3533,3545,3727,3862,3949,4051,4131,4170,4263,4431,4459,4684,4685,4686,4705,4767};
  
  // Int_t HT2_Hot_towerlist[]={32,52,115,268,276,294,295,510,562,682,750,987,994,1064,1143,1233,1264,1285,1307,1487,1593,1733,1824,1851,1946,2044,2163,2203,2634,2653,2835,2864,2866,2973,3006,3727,3862,4131,4170,4263,4431,4459,4684,4685,4686,4705,4767};
  
  
  //ht0 hot tower
  //  if(bTrg==0)
  // cout<<sizeof(HT0_Hot_towerlist)/sizeof(HT0_Hot_towerlist[0])<<endl;
  // cout<<sizeof(HT2_Hot_towerlist)/sizeof(HT2_Hot_towerlist[0])<<endl;
  
  //  Int_t  Hot_towerlist[] ={32,52,115,246,268,276,294,295,386,510,562,682,750,773,894,987,994,1043,1064,1143,1233,1264,1285,1307,1487,1593,1710,1733,1823,1824,1851,1946,2022,2044,2064,2110,2146,2163,2165,2203,2291,2314,2522,2530,2634,2653,2835,2864,2866,2973,3006,3062,3533,3545,3691,3727,3862,3949,4051,4131,4170,4263,4431,4459,4684,4685,4686,4705,4767};
  
  
  //  Int_t  Hot_towerlist[]={22,30,31,114,251,275,308,509,552,555,681,682,691,749,772,1063,1263,1268,1284,1304,1306,1329,1486,1592,1709,1768,1770,1823,1882,1904,1909,1945,2022,2042,2043,2048,2051,2067,2145,2146,2162,2171,2190,2202,2272,2288,2290,2493,2504,2522,2529,2549,2706,2723,2712,2750,2863,2865,2868,2874,2952,3061,3007,3061,3092,3112,3154,3264,3166,3269,3271,3307,3326,3330,3331,3349,3365,3373,3532,3544,3626,3692,3821,3861,3932,3964,4130,4169,4226,4232,4249,4252,4262,4353,4430,4546,4749,4727,4766}; // zach's hot tower list
  
  Int_t  Hot_towerlist[]={31, 51, 114, 275, 293, 479, 509, 533, 555, 561, 639, 681, 740, 743, 749, 772, 779, 799, 840, 860,  880, 893, 897, 982, 986, 993, 1063, 1142, 1160, 1200, 1224, 1232, 1237, 1241, 1256, 1263, 1280, 1284, 1306, 1313, 1318, 1337, 1438, 1486, 1537, 1592, 1709, 1713, 1732, 1823, 1850, 1856, 1879, 1945, 1976, 1984, 2043, 2145, 2162, 2164, 2190, 2202, 2290, 2299, 2300, 2313, 2339, 2414, 2439, 2459, 2529, 2580, 2633, 2652, 2834, 2863, 2865, 2874, 3005, 3020, 3061, 3137, 3154, 3420, 3515, 3532, 3692, 3720, 3737, 3838, 3861, 3925, 3948, 4013, 4130, 4169, 4262, 4316, 4430, 4458, 4534, 4560, 4595, 4684, 4766, 4781,50,245,251,385,405,682,691,775,1042,1304,1422,1443,1892,1906,2021,2022,2047,2051,2063,2083,2109,2146,2171,2267,2303,2368,2445,2493,2504,2521,2750,2861,3063,3171,3241,3292,3451, 3453,3544,3726,3749,4050,4122,4230,4232,4353,4453,4469,4546,4646,4722,4727};
  // from shenghui's newest hot tower list
  
  
  for(Int_t i=0;i<sizeof(Hot_towerlist)/sizeof(Hot_towerlist[0]);i++ )
  {
    if(Hot_towerlist[i]==trk->btowId())
      
      return kTRUE;
  }
  return kFALSE;
}

Bool_t StNpeRead::isBadRun(StDmesonEvent * evt)
{
  Int_t bTrg=-999;
  if(evt->isVPDMB())
  { bTrg=3; if(badruns::is_bad_run(evt->runId(),bTrg))
    
    
    return kTRUE;}
  if(evt->isHT0_BBCMB_TOF0())
  { bTrg=0;if(badruns::is_bad_run(evt->runId(),bTrg)) return kTRUE;}
  if(evt->isHT1_BBCMB_TOF0())
  { bTrg=1;if(badruns::is_bad_run(evt->runId(),bTrg)) return kTRUE;}
  if(evt->isHT2_BBCMB())
  { bTrg=2;if(badruns::is_bad_run(evt->runId(),bTrg)) return kTRUE;}
  // if(badruns::is_bad_run(evt->runId(),bTrg)) return kTRUE;
  else return kFALSE;
  
}
Bool_t StNpeRead::isGoodEvent(StDmesonEvent* evt,Int_t bTrg)
{
  if(!evt) return kFALSE;
  // if(badruns::is_bad_run(evt->runId(),bTrg)) return kFALSE;
  //  outfile<<evt->runId()<<endl;
  // runIDPico.insert(evt->runId());
  // cuts
  Float_t vz = evt->primaryVertex().z();
  if (!(evt->ranking() >0 )) return kFALSE;
  if(fabs(vz) > cuts::vz) return kFALSE;
  if(evt->isVPDMB() && fabs(vz-evt->vzVpd())>6) return kFALSE;
  
  
  
  if(evt->isVPDMB())
  {
    
    Double_t ps_VPDMB=mPrescales->GetPrescale(evt->runId(),VPDMB);
    
    if(ps_VPDMB>0)
    {
      //mh1Vz_VPDVz->Fill(vz-evt->vzVpd());
      //mh1Vz_VPD->Fill(vz);
      //mh1Vz_VPDPS->Fill(vz,ps_VPDMB);
    }
    
  }
  
  if(evt->isBBCMB() ||evt->isHT2_BBCMB())
  {
    
    Double_t ps_BBCMB=mPrescales->GetPrescale(evt->runId(),BBCMB);
    Double_t ps_HT2BBCMB=mPrescales->GetPrescale(evt->runId(),HT2BBCMB);
    if( ps_BBCMB>0 && ps_HT2BBCMB>0)
    {
      if(evt->isBBCMB())
      {
        //mh1Vz_BBCMB->Fill(vz);
        //mh1VPDVz_BBCMB->Fill(evt->vzVpd());
        //mh1Vz_BBCMBPS->Fill(vz,ps_BBCMB);
      }
    }
    
  }
  
  
  if(evt->isBBCMB_TOF0() ||evt->isHT0_BBCMB_TOF0())
  {
    
    Double_t ps_HT0_BBCMB_TOF0=mPrescales->GetPrescale(evt->runId(),HT0BBCMBTOF0);
    Double_t ps_BBCMB_TOF0=mPrescales->GetPrescale(evt->runId(),BBCMBTOF0);
    if( ps_BBCMB_TOF0>0 && ps_HT0_BBCMB_TOF0>0)
    {
      if( evt->isBBCMB_TOF0())
      {
        //mh1Vz_BBCMBTOF0->Fill(vz);
        //mh1VPDVz_BBCMBTOF0->Fill(evt->vzVpd());
        //mh1Vz_BBCMBTOF0PS->Fill(vz,ps_BBCMB_TOF0);
      }
      
    }
  }
  
  // if(evt->isHT1_BBCMB_TOF0())
  //   std::cout<<" HT1"<<std::endl;
  if(evt->isHT0_BBCMB_TOF0() || evt->isHT2_BBCMB() || evt->isVPDMB() || evt->isHT1_BBCMB_TOF0())
    // if(evt->isVPDMB())
    // if( evt->isBBCMB_TOF0()||evt->isBBCMB())
    
    
    return kTRUE;
  else
    return kFALSE;
}

Double_t StNpeRead::getHadronWt(Double_t pt, Double_t eta){
  Int_t etabin = floor((eta+1)/0.1);
  if(etabin<0||etabin>=20) return 0.;
  fEff->SetParameters(effPars[etabin]);
  Double_t wt = fEff->Eval(pt);
  if(wt>0) return 1./wt;
  else return 0.;
}

//Double_t StNpeRead::getTrgEff(Int_t trg, Double_t pt)  // old zach used gpt efficiency
//{
//  Double_t eff = 1;
//  if(trg == 0)
//  {
//    eff = TMath::Erf(pt - 2.41589); // from fitting XB Trig Eff
//  }
//
//  if(trg == 2)
//  {
//    if(pt < 4.5)
//      eff = TMath::Exp(-16.0543+3.3662*pt);
//    if(pt > 4.5)
//      eff = TMath::Erf(0.651713*pt-2.6212);
//  }
//
//  if(eff > 0)
//    return 1./eff;
//  else
//    return 0.;
//}

//Double_t StNpeRead::getTrgEff(Int_t trg, Double_t pt) // from shenghui's ppt trig. effi, fit func3
//{
//  Double_t eff = 1;
//  if(trg == 0)
//  {
//    eff = TMath::Erf(3.10569e-02*pt*pt*pt-2.77537e-01);
//  }
//
//  if(trg == 2)
//  {
//    if(pt < 4.5)
//      eff = TMath::Exp(-1.62885e+01+3.41456*pt)-7.13951e-06;
//    if(pt >= 4.5)
//      eff = TMath::Erf(5.99703e-01*pt-2.38876);
//  }
//
//  if(eff > 0)
//    return 1./eff;
//  else
//    return 0.;
//}

Double_t StNpeRead::getTrgEff(Int_t trg, Double_t pt) // from shenghui's ppt trig. effi, fit func3, sys
{
  Double_t eff = 1;
  if(trg == 0)
  {
    eff = TMath::Erf(2.96925e-02*pt*pt*pt-2.69714e-01);
  }

  if(trg == 2)
  {
    if(pt < 4.5)
      eff = TMath::Exp(-1.63854e+01+3.38602*pt)-6.24438e-06;
    if(pt >= 4.5)
      eff = TMath::Erf(5.83780e-01*pt-2.38107);
  }

  if(eff > 0)
    return 1./eff;
  else
    return 0.;
}

//Double_t StNpeRead::getTrgEff(Int_t trg, Double_t pt) // from shenghui's ppt trig. effi, fit func2
//{
//  Double_t eff = 1;
//  if(trg == 0)
//  {
//    eff = TMath::Erf(pt - 2.55666e+00)-6.00096e-03;
//  }
//
//  if(trg == 2)
//  {
//    if(pt <= 5)
//      eff = TMath::Exp(-8.80280e+00+1.64328e+00*pt)-1.41027e-02;
//    if(pt > 5)
//      eff = TMath::Erf(6.48257e-01*pt-2.70569e+00)-8.95634e-03;
//  }
//
//  if(eff > 0)
//    return 1./eff;
//  else
//    return 0.;
//}

//Double_t StNpeRead::getTrgEff(Int_t trg, Double_t pt) // from shenghui's ppt trig. effi, fit func2, sys
//{
//  Double_t eff = 1;
//  if(trg == 0)
//  {
//    eff = TMath::Erf(pt - 2.52823e+00)-5.56216e-03;
//  }
//
//  if(trg == 2)
//  {
//    if(pt <= 5)
//      eff = TMath::Exp(-8.13024e+00+1.53156e+00*pt)-2.17967e-02;
//    if(pt > 5)
//      eff = TMath::Erf(6.83595e-01*pt-2.80986e+00)-8.49065e-03;
//  }
//
//  if(eff > 0)
//    return 1./eff;
//  else
//    return 0.;
//}

//Double_t StNpeRead::getTrgEff(Int_t trg, Double_t pt) // from shenghui's ppt trig. effi
//{
//  Double_t eff = 1;
//  if(trg == 0)
//  {
//    eff = TMath::Erf(9.85567e-01*pt - 2.51355e+00)-5.73728e-03;
//  }
//
//  if(trg == 2)
//  {
//    if(pt < 4.5)
//      eff = TMath::Exp(2.63633e+00*pt - 1.29155e+01);
//    if(pt > 4.5)
//      eff = TMath::Erf(6.48257e-01*pt - 2.70569e+00)-8.95563e-03;
//  }
//
//  if(eff > 0)
//    return 1./eff;
//  else
//    return 0.;
//}

//Double_t StNpeRead::getTrgEff(Int_t trg, Double_t pt) // from shenghui's ppt trig. effi, sys
//{
//  Double_t eff = 1;
//  if(trg == 0)
//  {
//    eff = TMath::Erf(pt - 2.73552e+00);
//  }
//
//  if(trg == 2)
//  {
//    if(pt < 5)
//      eff = TMath::Exp(-1.15025e+01+2.20626e+00*pt);
//    if(pt > 5)
//      eff = TMath::Erf(pt-4.44533e+00);
//  }
//
//  if(eff > 0)
//    return 1./eff;
//  else
//    return 0.;
//}


Int_t StNpeRead::readEff()
{
  ifstream inf("/gpfs01/star/pwg/dongx/zmiller/pdsfhome/zamiller/NPEhPhiAnalysis2015/collabCode/bingchu_comb_eff_fit.txt",std::ifstream::in);
  if(!inf.good()){
    cout<<"No input efficiency tables!"<<endl;
    return -1;
  }
  for(int i=0;i<20;i++){
    for(int j=0;j<3;j++) inf>>effPars[i][j];
  }
  inf.close();
  fEff = new TF1("fEff","[0]*exp(-pow([1]/x,[2]))",0.2,15);
  return 1;
}

void StNpeRead::addToHadBuffer(StDmesonTrack *trk, Double_t vz)
{
  Int_t vzbin = (Int_t)vz+35; // add 35 since there are 70 bins for -35,35. makes -35 = 0.
  Float_t Phi = trk->pMom().phi();
  Float_t pT  = trk->pMom().perp();
  Float_t Eta = trk->pMom().pseudoRapidity();
  
  if(vzbin<0 || vzbin >70){
    cout << "VZ OUT OF RANGE" << endl;
    return;
  }
  //cout << "Vz: " << vzbin << " size: " << hadVec[vzbin].size() << endl;
  if(hadPhi[vzbin].size() < maxBufferSize)
  {
    hadPhi[vzbin].push_back(Phi); // Stores the event itself, not the pointer
    hadEta[vzbin].push_back(Eta);
    hadPt[vzbin].push_back(pT);
  }
  else
  {
    TRandom3* gRand = new TRandom3();
    Int_t eventPoint = (int) gRand->Uniform(0,maxBufferSize-1e-6);
    hadPhi[vzbin][eventPoint] = Phi;
    hadEta[vzbin][eventPoint] = Eta;
    hadPt[vzbin][eventPoint] = pT;
    delete gRand;
  }
  //cout << "Vz(after add): " << vzbin << " size: " << hadVec[vzbin].size() << endl;
}

void StNpeRead::computeMixedEvents(StDmesonTrack* trk, Double_t vz)
{
  //DEBUG  cout << "in compute" << endl;
  Float_t Phi = trk->pMom().phi();
  Float_t pT  = trk->pMom().perp();
  Float_t Eta = trk->pMom().pseudoRapidity();
  Int_t vzbin = (Int_t)vz+35;
  if(vzbin<0 || vzbin>70)
    return;
  
  if(hadPhi[vzbin].size()<=0)
    return;
  
  //cout << "at hadVec for" << endl;
  for(Int_t it=0; it < hadPhi[vzbin].size(); it++)
  {
    Float_t hPhi = hadPhi[vzbin][it];
    Float_t hEta = hadEta[vzbin][it];
    Float_t hpT  = hadPt[vzbin][it];
    Float_t wt = getHadronWt(hpT,hEta);
    
    if((hPhi != Phi) || (hEta != Eta) || (hpT != pT)) // if not the exact same track
    {
      //cout << "actually have mixed had track" << endl;
      Float_t dPhi = Phi-hPhi;
      dPhi = correct_dPhi(dPhi);
      Float_t dEta = Eta - hEta;
      mh3MixedDelPhi -> Fill(dPhi, pT, hpT);
      mh3MixedDelEta -> Fill(dEta, pT, hpT);
      mh3MixedEtaPhi -> Fill(dPhi, dEta, pT);
      mh3MixedDelPhiWt -> Fill(dPhi, pT, hpT ,wt);
      mh3MixedDelEtaWt -> Fill(dEta, pT, hpT ,wt);
      mh3MixedEtaPhiWt -> Fill(dPhi, dEta, pT ,wt);
    }
  }
}

Float_t StNpeRead::correct_dPhi(Float_t dP)
{
  if(dP > pi) dP = dP - 2*pi;
  if(dP < -pi) dP = dP + 2*pi;
  return dP;
}

Bool_t StNpeRead::pass_dEta(Float_t dE)
{
  if(abs(dE) < cuts::dEtaCut)
    return kTRUE;
  else
    return kFALSE;
}
