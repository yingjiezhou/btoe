/*!
 * \class  StMuAnalysisMaker
 * \brief  A typical Analysis Class for MuDst
 * \author Wei-Ming Zhang, KSU, Mar 2004 
 *
 * This is an example of a maker to perform analysis using MuDst.
 *
 * $Id: StMuAnalysisMaker.cxx,v 1.1 2004/08/10 16:09:11 perev Exp $
 * -------------------------------------------------------------------------
 * $Log: StMuAnalysisMaker.cxx,v $
 * Revision 1.1  2004/08/10 16:09:11  perev
 * new GridCollector stuff
 *
 * -------------------------------------------------------------------------
 */
//
//  Include header files. 
#include "TFile.h"
#include "StMessMgr.h"
#include "TH1.h"
#include "TH2.h"

#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuMcTrack.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuDebug.h"
#include "StBTofHeader.h"
#include "StMuAnalysisMaker.h"

ClassImp(StMuAnalysisMaker)

// The constructor. Initialize data members here.
StMuAnalysisMaker::StMuAnalysisMaker(const Char_t *name) : StMaker(name)
{ mEventCounter = 0; mFile = 0; }

StMuAnalysisMaker::~StMuAnalysisMaker() { /* noop */ }
//
//  Called once at the beginning.
Int_t StMuAnalysisMaker::Init()
{
    //  Output file and histogram booking
    mFileName = "muAnalysis.root";

    mVxVy = new TH2F("VxVy","",200,-1.,1.,200,-1.,1.);
    mVzCorr = new TH2F("VzCorr","",600,-30.,30.,600,-30.,30.);   // VzVpd vs. VzTpc
    mRefCorr = new TH2F("RefCorr","",1000,0,1000,1000,0,1000);  // gRefMult vs. refMult
    mRcTPCPtEta = new TH2F("RcTPCPtEta","",500,0.,10.,100,-1.,1.);
    mMcTPCPtEta = new TH2F("McTPCPtEta","",500,0.,10.,100,-1.,1.);
    mRcHFTPtEta = new TH2F("RcHFTPtEta","",500,0.,10.,100,-1.,1.);
    mMcHFTPtEta = new TH2F("McHFTPtEta","",500,0.,10.,100,-1.,1.);
    mMcHFTGoodPtEta = new TH2F("McHFTGoodPtEta","",500,0.,10.,100,-1.,1.);
    mPtCorr = new TH2F("PtCorr","",500,0.,10.,500,-1.,1.);
    mNHitsPxl1Ist = new TH2F("NHitsPxl1Ist","",1000,0,1000,1000,0,20000);
    mNHitsPxl2Ist = new TH2F("NHitsPxl2Ist","",1000,0,1000,1000,0,5000);
                        
            
    mGlobalPt = new TH1D("globalPt","globalPt",100,0.,3.);
    mPrimaryPt = new TH1D("primaryPt","primaryPt",100,0.,3.);
    mL3Pt = new TH1D("l3Pt","l3Pt",100,0.,3.);
    mRefMult = new TH1D("refMult","refMult",100,0.,100.);
    
    return StMaker::Init();
}
//
//  Called every event after Make(). 
void StMuAnalysisMaker::Clear(Option_t *opt)
{
    StMaker::Clear();
}
//
//  Called once at the end.
Int_t StMuAnalysisMaker::Finish()
{
//  Summarize the run.
    cout << "StMuAnalysisMaker::Finish()\n";
    cout << "\tProcessed " << mEventCounter << " events." << endl;
//
//  Output histograms
    mFile =  new TFile(mFileName.c_str(), "RECREATE");
    cout << "\tHistograms will be stored in file '"
	 <<  mFileName.c_str() << "'" << endl;

    mVxVy->Write();
    mVzCorr->Write();
    mRefCorr->Write();
    mGlobalPt->Write();
    mPrimaryPt->Write();
    mL3Pt->Write();
    mRefMult->Write();
    mPtCorr->Write();
    mRcTPCPtEta->Write();
    mMcTPCPtEta->Write();
    mRcHFTPtEta->Write();
    mMcHFTPtEta->Write();
    mMcHFTGoodPtEta->Write();
    mNHitsPxl1Ist->Write();
    mNHitsPxl2Ist->Write();                    
//
//  Write histos to file and close it.
    if( mFile){
      mFile->Write();  
      mFile->Close();
    }

    return kStOK;
}
//
//  This method is called every event.
Int_t StMuAnalysisMaker::Make()
{
    mEventCounter++;  // increase counter

//    DEBUGVALUE2(mEventCounter);
//  Get MuDst
    StMuDst* mu; 
    mu =  (StMuDst*) GetInputDS("MuDst"); 
//    DEBUGVALUE2(mu);

    if (!mu){
	  gMessMgr->Warning() << "StMuAnalysisMaker::Make : No MuDst" << endm;
          return kStOK;        // if no event, we're done
    }
//
//  Check StMuEvent branch
    StMuEvent* muEvent;
    muEvent = (StMuEvent*) mu->event();
    if(muEvent) {
      int refMult = muEvent->refMult();
      mRefMult->Fill(refMult);
    }

//
//  Printout information of StMuEvent 
    muEventInfo(*mu); 

//
//  MC track information, fix the mapping
    TClonesArray *mcTracks = mu->mcArray(MCTrack);
    int nMcTracks = mcTracks->GetEntriesFast();

    int index2McTrack[10000];
    for(int i=0;i<10000;i++) index2McTrack[i] = -1;
    
    printf("Mc track # = %d\n",nMcTracks);
    for(int i=0;i<nMcTracks;i++) {
      StMuMcTrack *mcT = (StMuMcTrack *)mcTracks->UncheckedAt(i);
      if(!mcT) continue;
      int id = mcT->Id();
      int gId = mcT->GePid();
      //if(gId!=8) continue; // not a pion
      int idVtx = mcT->IdVx();
      //if(idVtx!=1) continue;  // not from primary vertex
      cout << "idVtx = " << idVtx << endl;
      index2McTrack[id] = i;
    }

// 
//  Check track branches
    StMuTrack* muTrack; 
    int nTracks;
    nTracks= mu->globalTracks()->GetEntries();
    printf("Global track # = %d\n",nTracks);
    for (int l=0; l<nTracks; l++) { 
      muTrack =  (StMuTrack*) mu->globalTracks(l); 
      if(!muTrack) continue;
      if(!accept(muTrack)) continue;
      mGlobalPt->Fill(muTrack->pt());
      const StThreeVectorF mom = muTrack->momentum();
      const float pt = mom.perp();
      const float eta = mom.pseudoRapidity();
      if(pt<0.2 || fabs(eta)>1.0) continue;
      
      int nHft = muTrack->nHft();
      int nGoodHft = muTrack->nGoodHft();
      unsigned int map0 = muTrack->topologyMap().data(0);
      bool isHFT = ((map0>>1) & 0x1) && ((map0>>2) & 0x3) && ((map0>>4) & 0x3);
      
      int idTruth = muTrack->idTruth();
      if(idTruth<0) continue;
      if(idTruth>10000) { // reconstructed tracks
        mRcTPCPtEta->Fill(pt, eta);
        if(nHft>=3) mRcHFTPtEta->Fill(pt, eta);
//        cout << " real data tracks: nHft = " << nHft << "\t isHFT = " << isHFT << endl;
 
      } else {      
//        cout << " MC data tracks: nHft = " << nHft << "\t isHFT = " << isHFT << endl;
        int index2Mc = index2McTrack[idTruth];
        if(index2Mc>=0) {
          StMuMcTrack *mcT = (StMuMcTrack *)mcTracks->UncheckedAt(index2Mc);
          if(mcT) {
            float pt_mc = mcT->pT();
            mPtCorr->Fill(pt_mc, pt-pt_mc);
            mMcTPCPtEta->Fill(pt, eta);
            if(nHft>=3) mMcHFTPtEta->Fill(pt, eta);
            if(nHft>=3 && nGoodHft>=3) mMcHFTGoodPtEta->Fill(pt, eta);
          }
        } // end if (index2Mc)
      }
    }
    nTracks= mu->primaryTracks()->GetEntries();
    printf("Primary track # = %d\n",nTracks);
    for (int l=0; l<nTracks; l++) { 
      muTrack =  (StMuTrack*) mu->primaryTracks(l); 
      if(!muTrack) continue;
      if(!accept(muTrack)) continue;
      mPrimaryPt->Fill(muTrack->pt());
/*      
      int idTruth = muTrack->idTruth();
      if(idTruth>10000) continue; // reconstructed tracks
      
      int index2Mc = index2McTrack[idTruth];
      StMuMcTrack *mcT = (StMuMcTrack *)mcTracks->UncheckedAt(index2Mc);
*/            
    }


    return kStOK;
}
//
//  A simple track filter
bool StMuAnalysisMaker::accept(StMuTrack* track)
{
//  check for positive flags.
    return track && track->flag() >= 0 && track->dcaGlobal().mag()<1.5 && (int)track->nHitsFit()>20;// && fabs(track->nSigmaPion())<2.0;
}
//
//  Prototype 
void StMuAnalysisMaker::muEventInfo(const StMuDst& mu)
{
  StMuEvent* ev = mu.event();
  if(!ev) return;
  
  StThreeVectorF pVtx = ev->primaryVertexPosition();
  float vzVpd = -999.;
  if (StBTofHeader* header = mu.btofHeader()) {
    vzVpd = header->vpdVz();
  }
  if(fabs(vzVpd)<100.) {
    mVzCorr->Fill(pVtx.z(), vzVpd);
  }
  
  int gRefMult = ev->grefmult();
  int refMult = ev->refMultNeg()+ev->refMultPos();
  mRefCorr->Fill(refMult, gRefMult);
  
  int nPxl1 = ev->numberOfPxlInnerHits();
  int nPxl2 = ev->numberOfPxlOuterHits();
  int nIst = ev->numberOfIstHits();
  int nSsd = ev->numberOfSsdHits();
  mNHitsPxl1Ist->Fill(nIst, nPxl1);
  mNHitsPxl2Ist->Fill(nIst, nPxl2);
                
}
