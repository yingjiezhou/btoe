#include "StMyAnalysisMaker.h"
#include "StRoot/StPicoEvent/StPicoDst.h"
#include "StRoot/StPicoEvent/StPicoTrack.h"
#include "StRoot/StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StPicoEvent/StPicoEvent.h"
#include "StRoot/StPicoEvent/StPicoBEmcPidTraits.h"
#include "StRoot/StPicoEvent/StPicoEmcTrigger.h"
#include "StRoot/StPicoDstMaker/StPicoUtilities.h"
#include "StRoot/StPicoEvent/StPicoPhysicalHelix.h"
#include "StDcaGeometry.h"

#include "TVector3.h"
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include <map>
#include <iostream>
#include <fstream>
#include "mBadRunList.h"
#include "mHotTowerList.h"
Bool_t fillhistflag=1;
ofstream runidfiles;
Int_t runIndex;
Int_t randomId;
map<Int_t,Int_t> mTotalRunId;
Int_t mTotalRun = 848;//603


ClassImp(StMyAnalysisMaker)

//-----------------------------------------------------------------------------
StMyAnalysisMaker::StMyAnalysisMaker(const char* name, StPicoDstMaker *picoMaker, const char* outName,int trigSelect)
: StMaker(name)
{
  mPicoDstMaker = picoMaker;
  mPicoDst = 0;
  TH1F:: SetDefaultSumw2();
  TH2F:: SetDefaultSumw2();
  mOutName = outName;
  mTrigSelect = trigSelect;
  mTriggerIDs.clear();
  mTriggerIDs.push_back(370542);     // bht0 -bbcmb -tof0
  mTriggerIDs.push_back(370522);     // bht2 -bbcmb
  
  //mNBadRuns = sizeof(mBadRuns)/sizeof(int);
  mNBadRuns_HT0 = sizeof(mBadRuns_HT0)/sizeof(int);
  mNBadRuns_HT2 = sizeof(mBadRuns_HT2)/sizeof(int);
  
  MassE = 0.000511;
  VzCut = 35.;
  VzDiff = 6.;
  mHTth = 0;
  mHTAdc0th = 250;
  mHTAdc0thSys = 250;
  mEmcPtth = 2.5;
  nFPtsCutPart = 15.;
  nFPtsCut = 20.;    // >=20 require TPC track quality at least 20 out of 45
  nFPtsCutSys = 25;    // >=20 require TPC track quality at least 20 out of 45
  ndEdxPtsCut = 15;    //10 ensure dEdx resolution is good
  ndEdxPtsCutSys = 18;    //10 ensure dEdx resolution is good
  PtsRMin = 0.52;  // >0.52 reject splitting tracks
  PtsRMax = 1.20;  // <1.20
  minPtCut = 1.5; // >0.2 pt below 0.2 efficiency is too low, acceptance limit
  dcaCut = 1.5;  // <2. ensure primary track for tag electron
  dcaCutSys = 1.0;  // <2. ensure primary track for tag electron
  TPCFR = 73.;
  EtaCut = 0.7;    // |<1.
  PoeMin = 0.3;
  PoeMinSys = 0.6;
  PoeMax = 1.5;
  DistZ = 3.0;
  DistPhi = 0.015;
  NEta = 2;
  NPhi = 2;
  PairDiffMax = 1.;   // <2cm ensure partner track is attached to tag electron
  PairDiffMin = 0.;
}

//----------------------------------------------------------------------------- 
StMyAnalysisMaker::~StMyAnalysisMaker()
{ 
  //delete mPrescales;
}
//----------------------------------------------------------------------------- 
Int_t StMyAnalysisMaker::Init() {
  if(mOutName!="") {
    fout = new TFile(mOutName.Data(),"RECREATE");
  }else{
    fout = new TFile("picoQA_test.root","RECREATE");
  }
  DeclareHistograms();
  return kStOK;
}

//----------------------------------------------------------------------------- 
Int_t StMyAnalysisMaker::Finish() {
  fout->cd();
  fout->Write();
  fout->Close();
  return kStOK;
}

//-----------------------------------------------------------------------------
void StMyAnalysisMaker::DeclareHistograms() {
  
  fout->cd();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  
  hnEvent       = new TH1F("nEvent","nEvent",10,0.,10.);
  hVpdVz        = new TH2F("vpdVz","vpdVz",400,-200.,200.,400,-200.,200.);
  hVpdVzcut     = new TH2F("vpdVzcut","vpdVzcut",200,-100.,100.,200,-100.,100.);
  hVzDiff       = new TH1F("VzDiff","",200,-20.,20.);
  //hVzDiffGood = new TH1F("VzDiffGood","",200,-20.,20.);
  //hBTOWERid   = new TH2F("BTOWERid","",35000,13.038000,13.073000,10000,0,10000.);
  hBTOWERid     = new TH1F("BTOWERid","",10000,0,10000.);
  hAdc0         = new TH2F("Adc0","",1000,0,20,1000,0,2000);
  hdsmAdc       = new TH2F("dsmAdc","",1000,0,20,100,0,100);
  hAdc0vsdsmAdc = new TH2F("Adc0vsdsmAdc","",1000,0,2000,100,0,100);
  hNSigE            = new TH2F("nSigE","",1000,0.,20.,400,-20.,20.);
  hNSigEPt          = new TH2F("nSigEPt","",1000,0.,20.,400,-20.,20.);
  hNSigEPtAdc0      = new TH2F("nSigEPtAdc0","",1000,0.,20.,400,-20.,20.);
  hNSigEPtnHitsFit  = new TH2F("nSigEPtnHitsFit","",1000,0.,20.,400,-20.,20.);
  hNSigEPtnHitsDedx = new TH2F("nSigEPtnHitsDedx","",1000,0.,20.,400,-20.,20.);
  hNSigEPtDca       = new TH2F("nSigEPtDca","",1000,0.,20.,400,-20.,20.);
  hNSigEPtEMCpovere = new TH2F("nSigEPtEMCpovere","",1000,0.,20.,400,-20.,20.);
  hNSigESMD         = new TH2F("nSigESMD","",1000,0.,20.,400,-20.,20.);
  hNSigEPtSMD       = new TH2F("nSigEPtSMD","",1000,0.,20.,400,-20.,20.);
  hNSigEPtAdc0SMD      = new TH2F("nSigEPtAdc0SMD","",1000,0.,20.,400,-20.,20.);
  hNSigEPtnHitsFitSMD  = new TH2F("nSigEPtnHitsFitSMD","",1000,0.,20.,400,-20.,20.);
  hNSigEPtnHitsDedxSMD = new TH2F("nSigEPtnHitsDedxSMD","",1000,0.,20.,400,-20.,20.);
  hNSigEPtDcaSMD       = new TH2F("nSigEPtDcaSMD","",1000,0.,20.,400,-20.,20.);
  hNSigEPtEMCpovereSMD = new TH2F("nSigEPtEMCpovereSMD","",1000,0.,20.,400,-20.,20.);
  hAdc0Cut             = new TH2F("Adc0Cut","",1000,0,20,1000,0,2000);
  hdsmAdcCut           = new TH2F("dsmAdcCut","",1000,0,20,100,0,100);
  hAdc0vsdsmAdcCut     = new TH2F("Adc0vsdsmAdcCut","",1000,0,2000,100,0,100);
  hAdc0CutSMD          = new TH2F("Adc0CutSMD","",1000,0,20,1000,0,2000);
  hdsmAdcCutSMD        = new TH2F("dsmAdcCutSMD","",1000,0,20,100,0,100);
  hAdc0vsdsmAdcCutSMD  = new TH2F("Adc0vsdsmAdcCutSMD","",1000,0,2000,100,0,100);
  hnE                   = new TH2F("hnE","nE",10,0,10,10,0,10);
  hmvspt                = new TH2F("mvspt","",1000,0.,20.,500,0.,0.5);
  hmvsptlike            = new TH2F("mvsptlike","",1000,0.,20.,500,0.,0.5);
  hmvsptAdc0            = new TH2F("mvsptAdc0","",1000,0.,20.,500,0.,0.5);
  hmvsptAdc0like        = new TH2F("mvsptAdc0like","",1000,0.,20.,500,0.,0.5);
  hmvsptnHitsFit        = new TH2F("mvsptnHitsFit","",1000,0.,20.,500,0.,0.5);
  hmvsptnHitsFitlike    = new TH2F("mvsptnHitsFitlike","",1000,0.,20.,500,0.,0.5);
  hmvsptnHitsDedx       = new TH2F("mvsptnHitsDedx","",1000,0.,20.,500,0.,0.5);
  hmvsptnHitsDedxlike   = new TH2F("mvsptnHitsDedxlike","",1000,0.,20.,500,0.,0.5);
  hmvsptDca             = new TH2F("mvsptDca","",1000,0.,20.,500,0.,0.5);
  hmvsptDcalike         = new TH2F("mvsptDcalike","",1000,0.,20.,500,0.,0.5);
  hmvsptEMCpovere       = new TH2F("mvsptEMCpovere","",1000,0.,20.,500,0.,0.5);
  hmvsptEMCpoverelike   = new TH2F("mvsptEMCpoverelike","",1000,0.,20.,500,0.,0.5);
  hmvsptSMD             = new TH2F("mvsptSMD","",1000,0.,20.,500,0.,0.5);
  hmvsptSMDlike         = new TH2F("mvsptSMDlike","",1000,0.,20.,500,0.,0.5);
  hmvsptAdc0SMD         = new TH2F("mvsptAdc0SMD","",1000,0.,20.,500,0.,0.5);
  hmvsptAdc0SMDlike     = new TH2F("mvsptAdc0SMDlike","",1000,0.,20.,500,0.,0.5);
  hmvsptnHitsFitSMD     = new TH2F("mvsptnHitsFitSMD","",1000,0.,20.,500,0.,0.5);
  hmvsptnHitsFitSMDlike = new TH2F("mvsptnHitsFitSMDlike","",1000,0.,20.,500,0.,0.5);
  hmvsptnHitsDedxSMD    = new TH2F("mvsptnHitsDedxSMD","",1000,0.,20.,500,0.,0.5);
  hmvsptnHitsDedxSMDlike= new TH2F("mvsptnHitsDedxSMDlike","",1000,0.,20.,500,0.,0.5);
  hmvsptDcaSMD          = new TH2F("mvsptDcaSMD","",1000,0.,20.,500,0.,0.5);
  hmvsptDcaSMDlike      = new TH2F("mvsptDcaSMDlike","",1000,0.,20.,500,0.,0.5);
  hmvsptEMCpovereSMD    = new TH2F("mvsptEMCpovereSMD","",1000,0.,20.,500,0.,0.5);
  hmvsptEMCpovereSMDlike= new TH2F("mvsptEMCpovereSMDlike","",1000,0.,20.,500,0.,0.5);
  hAdc0PHE          = new TH2F("Adc0PHE","",1000,0.,20.,1000,0,2000);
  hAdc0PHElike      = new TH2F("Adc0PHElike","",1000,0.,20.,1000,0,2000);
  hnHitsFit         = new TH2F("nHitsFit","",1000,0.,20.,50,0,50);
  hnHitsFitlike     = new TH2F("nHitsFitlike","",1000,0.,20.,50,0,50);
  hnHitsDedx        = new TH2F("nHitsDedx","",1000,0.,20.,50,0,50);
  hnHitsDedxlike    = new TH2F("nHitsDedxlike","",1000,0.,20.,50,0,50);
  hDca              = new TH2F("Dca","",1000,0.,20.,30,0,3);
  hDcalike          = new TH2F("Dcalike","",1000,0.,20.,30,0,3);
  hAdc0PHESMD       = new TH2F("Adc0PHESMD","",1000,0.,20.,1000,0,2000);
  hAdc0PHESMDlike   = new TH2F("Adc0PHESMDlike","",1000,0.,20.,1000,0,2000);
  hnHitsFitSMD      = new TH2F("nHitsFitSMD","",1000,0.,20.,50,0,50);
  hnHitsFitSMDlike  = new TH2F("nHitsFitSMDlike","",1000,0.,20.,50,0,50);
  hnHitsDedxSMD     = new TH2F("nHitsDedxSMD","",1000,0.,20.,50,0,50);
  hnHitsDedxSMDlike = new TH2F("nHitsDedxSMDlike","",1000,0.,20.,50,0,50);
  hDcaSMD           = new TH2F("DcaSMD","",1000,0.,20.,30,0,3);
  hDcaSMDlike       = new TH2F("DcaSMDlike","",1000,0.,20.,30,0,3);
  hNSigEeff         = new TH2F("nSigEeff","",1000,0.,20.,400,-20.,20.);
  hNSigEefflike     = new TH2F("nSigEefflike","",1000,0.,20.,400,-20.,20.);
  hNSigEeffSMD      = new TH2F("nSigEeffSMD","",1000,0.,20.,400,-20.,20.);
  hNSigEeffSMDlike  = new TH2F("nSigEeffSMDlike","",1000,0.,20.,400,-20.,20.);
  hTPCtracksTag          = new TH1F("TPCtracksTag","",1000,0.,20.);
  hTPCtracksTaglike      = new TH1F("TPCtracksTaglike","",1000,0.,20.);
  hSMDtracksTag          = new TH1F("SMDtracksTag","",1000,0.,20.);
  hSMDtracksTaglike      = new TH1F("SMDtracksTaglike","",1000,0.,20.);
  hTPCtracks             = new TH1F("TPCtracks","",1000,0.,20.);
  hTPCtrackslike         = new TH1F("TPCtrackslike","",1000,0.,20.);
  hEMCmatchingtracks     = new TH1F("EMCmatchingtracks","",1000,0.,20.);
  hEMCmatchingtrackslike = new TH1F("EMCmatchingtrackslike","",1000,0.,20.);
  hEMCtracks             = new TH1F("EMCtracks","",1000,0.,20.);
  hEMCtrackslike         = new TH1F("EMCtrackslike","",1000,0.,20.);
  hSMDmatchingtracks     = new TH1F("SMDmatchingtracks","",1000,0.,20.);
  hSMDmatchingtrackslike = new TH1F("SMDmatchingtrackslike","",1000,0.,20.);
  hSMDtracks             = new TH1F("SMDtracks","",1000,0.,20.);
  hSMDtrackslike         = new TH1F("SMDtrackslike","",1000,0.,20.);
  hTPCtracksSMD             = new TH1F("TPCtracksSMD","",1000,0.,20.);
  hTPCtracksSMDlike         = new TH1F("TPCtracksSMDlike","",1000,0.,20.);
  hEMCmatchingtracksSMD     = new TH1F("EMCmatchingtracksSMD","",1000,0.,20.);
  hEMCmatchingtracksSMDlike = new TH1F("EMCmatchingtracksSMDlike","",1000,0.,20.);
  hEMCtracksSMD             = new TH1F("EMCtracksSMD","",1000,0.,20.);
  hEMCtracksSMDlike         = new TH1F("EMCtracksSMDlike","",1000,0.,20.);
  hSMDmatchingtracksSMD     = new TH1F("SMDmatchingtracksSMD","",1000,0.,20.);
  hSMDmatchingtracksSMDlike = new TH1F("SMDmatchingtracksSMDlike","",1000,0.,20.);
  hSMDtracksSMD             = new TH1F("SMDtracksSMD","",1000,0.,20.);
  hSMDtracksSMDlike         = new TH1F("SMDtracksSMDlike","",1000,0.,20.);
}

//----------------------------------------------------------------------------- 
void StMyAnalysisMaker::Clear(Option_t *opt) {
  
}

//----------------------------------------------------------------------------- 
Int_t StMyAnalysisMaker::Make() {
  
  if(!mPicoDstMaker) {
    LOG_WARN << " No PicoDstMaker! Skip! " << endm;
    return kStWarn;
  }
  
  mPicoDst = mPicoDstMaker->picoDst();
  if(!mPicoDst) {
    LOG_WARN << " No PicoDst! Skip! " << endm;
    return kStWarn;
  }
  
  event=mPicoDst->event();
  if(!event) {
    LOG_WARN << " No mEvent! Skip! " << endm;
    return kStWarn;
  }
  
  hnEvent->Fill(0);
  
  TVector3 pVtx = event->primaryVertex();
  if(fabs(pVtx.X())<1e-5 && fabs(pVtx.Y())<1e-5 && fabs(pVtx.Z())<1e-5) return kStOK;
  hnEvent->Fill(1);
  float Vr = sqrt(pow(pVtx.X(),2.)+pow(pVtx.Y(),2.));
  if(Vr>=2)return kStOK;
  hnEvent->Fill(2);
  int RUNID = event->runId();
  //cout<<"mTrigSelect"<<mTrigSelect<<endl;
  if(mTrigSelect==0){
    for(int i=0;i<mNBadRuns_HT0;i++){ if(RUNID==mBadRuns_HT0[i]) return kStOK; }
  }
  else if(mTrigSelect==2){
    for(int i=0;i<mNBadRuns_HT2;i++){ if(RUNID==mBadRuns_HT2[i]) return kStOK; }
  }
  hnEvent->Fill(3);
  int eventPass = 0;
  if(mTrigSelect==0&&isHT0_BBCMB_TOF0(event, mTriggerIDs)){eventPass = 1; mHTth = 11; mHTAdc0th = 180; mHTAdc0thSys=196; mEmcPtth = 2.5;}//HT0 180  Et>2.6
  else if(mTrigSelect==2&&isHT2_BBCMB(event, mTriggerIDs)) {eventPass = 1; mHTth = 18; mHTAdc0th = 304; mHTAdc0thSys=320; mEmcPtth = 4.0;}//HT2 300 Et>4.2
  if(eventPass==0) return kStOK;
  hnEvent->Fill(4);
  
  float ranking=event->ranking();
  if( ranking<=0. ) return kStOK;
  hnEvent->Fill(5);
  float vpdVz = event->vzVpd();
  hVpdVz->Fill(vpdVz,pVtx.Z());
  if(fabs(pVtx.Z()) > VzCut) return kStOK;
  hnEvent->Fill(6);
  hVpdVzcut->Fill(vpdVz,pVtx.Z());
  hVzDiff->Fill(vpdVz - pVtx.Z());
  //hmVxy->Fill(pVtx.Y(), pVtx.Y());
  //hmVzx->Fill(pVtx.Z(), pVtx.Y());
  //if(fabs(vpdVz - pVtx.Z()) > VzDiff) continue; //????
  if(fabs(vpdVz - pVtx.Z()) < VzDiff) hnEvent->Fill(7);
  
  CurrentEvent_bField =event->bField()*kilogauss;
  CurrentEvent_nEs   = 0;
  CurrentEvent_nEMCE = 0;
  
  loopTrack();
  
  hnE->Fill(CurrentEvent_nEMCE,CurrentEvent_nEs);
  if(CurrentEvent_nEMCE < 1 || CurrentEvent_nEs < 1) return kStOK;; //at least find 1 pair candidate
  hnEvent->Fill(8);
  
  makerealevent();
  return kStOK;
}
//----------------------------------------------------------------------------- 
Int_t StMyAnalysisMaker::loopTrack() {
  TVector3 pVtx = event->primaryVertex();
  int nE = mPicoDst->numberOfTracks();
  //cout<<"CurrentEvent_nEs"<<CurrentEvent_nEs<<endl;
  for(int i=0;i<nE;i++){
    StPicoTrack* eTrk = (StPicoTrack*)mPicoDst->track(i);
    if(!eTrk) continue;
    if(!isGoodPartner(eTrk)) continue;
    
    TVector3 gmom = eTrk->gMom();
    TVector3 origin = eTrk->origin();
    TVector3 pmom = eTrk->pMom();
    float pp    = pmom.Mag();
    float ppt   = pmom.Perp(); // ?? gpt or ppt?
    float eta   = pmom.PseudoRapidity();
    float dca = eTrk->gDCA(pVtx).Mag(); //??
    int nHitsFit = eTrk->nHitsFit();
    int nHitsDedx = eTrk->nHitsDedx();
    //
    int TOWId = -999;
    float EMCE = -999;
    float EMCpovere = -999.;
    int nEta = -999;
    int nPhi = -999;
    float ZDist = -999;
    float PhiDist = -999;
    int adc0 = -999.;
    Int_t bemcPidTraitsIndex = eTrk->bemcPidTraitsIndex();
    if(bemcPidTraitsIndex>=0){
      StPicoBEmcPidTraits *bemcPidTraits   =  mPicoDst->bemcPidTraits(bemcPidTraitsIndex);
      TOWId = bemcPidTraits->btowId();
      EMCE     = bemcPidTraits->bemcE();
      EMCpovere = (EMCE>0) ? gmom.Mag()/EMCE : -999.;
      ZDist    = bemcPidTraits->bemcZDist();
      PhiDist  = bemcPidTraits->bemcPhiDist();
      nEta  = bemcPidTraits->bemcSmdNEta();
      nPhi  = bemcPidTraits->bemcSmdNPhi();
      adc0  = bemcPidTraits->bemcAdc0();
    }
    if(checkHotTower(TOWId)) continue;
    //
    if(fabs(gmom.PseudoRapidity())<1.0&&nHitsFit>nFPtsCutPart){
      CurrentEvent_EId[CurrentEvent_nEs]       = i;
      CurrentEvent_ECharge[CurrentEvent_nEs]   = eTrk->charge();
      CurrentEvent_EPt[CurrentEvent_nEs]       = ppt;
      CurrentEvent_EEta[CurrentEvent_nEs]      = eta;
      CurrentEvent_EHelixPx[CurrentEvent_nEs]  = gmom.X();
      CurrentEvent_EHelixPy[CurrentEvent_nEs]  = gmom.Y();
      CurrentEvent_EHelixPz[CurrentEvent_nEs]  = gmom.Z();
      CurrentEvent_EHelixX[CurrentEvent_nEs]   = origin.X();
      CurrentEvent_EHelixY[CurrentEvent_nEs]   = origin.Y();
      CurrentEvent_EHelixZ[CurrentEvent_nEs]   = origin.Z();
      CurrentEvent_ENhitsFit[CurrentEvent_nEs] = nHitsFit;
      CurrentEvent_ENhitsDedx[CurrentEvent_nEs]= nHitsDedx;
      CurrentEvent_EDca[CurrentEvent_nEs]      = dca;
      CurrentEvent_ETOWE[CurrentEvent_nEs]     = EMCE;
      CurrentEvent_ETOWpovere[CurrentEvent_nEs]= EMCpovere;
      CurrentEvent_EDistZ[CurrentEvent_nEs]    = ZDist;
      CurrentEvent_EDistPhi[CurrentEvent_nEs]  = PhiDist;
      CurrentEvent_ESMDNEta[CurrentEvent_nEs]  = nEta;
      CurrentEvent_ESMDNPhi[CurrentEvent_nEs]  = nPhi;
      CurrentEvent_nEs ++;
    }
    if(!isGoodTrack(eTrk)) continue; // for triggerd e??
    if(bemcPidTraitsIndex<0) continue;
    StPicoBEmcPidTraits *bemcPidTraitsP   =  mPicoDst->bemcPidTraits(bemcPidTraitsIndex);
    hBTOWERid->Fill(TOWId);
    float nSigE = eTrk->nSigmaElectron();
    int dsmadc   = -999.;
    hAdc0->Fill(ppt, adc0);
    int nEmcTrigger = mPicoDst->numberOfEmcTriggers();
    for(int nEmc=0;nEmc<nEmcTrigger;nEmc++){
      StPicoEmcTrigger *emcTrg = (StPicoEmcTrigger*)mPicoDst->emcTrigger(nEmc);
      int emcTrgID=emcTrg->id();
      if(emcTrgID==TOWId){ // trigger Id = bemc tow id
        dsmadc = emcTrg->adc();
        hdsmAdc->Fill(ppt, dsmadc);
        hAdc0vsdsmAdc->Fill(adc0, dsmadc);
        break;
      }
    } // zyj
    int  isTriggered = 0;
    if(dsmadc>mHTth && adc0>mHTAdc0th) isTriggered = 1;
    int  isTrackQ = 0;
    if(nHitsFit>=nFPtsCut&&nHitsDedx>=ndEdxPtsCut&&dca<dcaCut) isTrackQ = 1;
    if(isTriggered&&isTrackQ&&isEMCTrack(eTrk,bemcPidTraitsP)){
      hNSigE->Fill(pp, nSigE);
      hNSigEPt->Fill(ppt, nSigE);
      if(adc0>mHTAdc0thSys) hNSigEPtAdc0->Fill(ppt,nSigE);
      if(nHitsFit>=nFPtsCutSys) hNSigEPtnHitsFit->Fill(ppt,nSigE);
      if(nHitsDedx>=ndEdxPtsCutSys) hNSigEPtnHitsDedx->Fill(ppt,nSigE);
      if(dca<dcaCutSys) hNSigEPtDca->Fill(ppt,nSigE);
      if(EMCpovere>PoeMinSys) hNSigEPtEMCpovere->Fill(ppt,nSigE);
      if(isSMDTrack(eTrk,bemcPidTraitsP)){
        hNSigESMD->Fill(pp, nSigE);
        hNSigEPtSMD->Fill(ppt, nSigE);
        if(adc0>mHTAdc0thSys) hNSigEPtAdc0SMD->Fill(ppt,nSigE);
        if(nHitsFit>=nFPtsCutSys) hNSigEPtnHitsFitSMD->Fill(ppt,nSigE);
        if(nHitsDedx>=ndEdxPtsCutSys) hNSigEPtnHitsDedxSMD->Fill(ppt,nSigE);
        if(dca<dcaCutSys) hNSigEPtDcaSMD->Fill(ppt,nSigE);
        if(EMCpovere>PoeMinSys) hNSigEPtEMCpovereSMD->Fill(ppt,nSigE);
      }
      if(nSigE>-1.&&nSigE<3.){
        hAdc0Cut->Fill(ppt, adc0);
        hdsmAdcCut->Fill(ppt, dsmadc);
        hAdc0vsdsmAdcCut->Fill(adc0, dsmadc);
        if(isSMDTrack(eTrk,bemcPidTraitsP)){
          hAdc0CutSMD->Fill(ppt, adc0);
          hdsmAdcCutSMD->Fill(ppt, dsmadc);
          hAdc0vsdsmAdcCutSMD->Fill(adc0, dsmadc);
        }
      }
    }
    CurrentEvent_EMCEId[CurrentEvent_nEMCE]       = i;
    CurrentEvent_EMCECharge[CurrentEvent_nEMCE]   = eTrk->charge();
    CurrentEvent_EMCEPt[CurrentEvent_nEMCE]       = ppt;
    //CurrentEvent_EMCEEta[CurrentEvent_nEMCE]      = peta;
    //CurrentEvent_EMCEPhi[CurrentEvent_nEMCE]      = pphi;
    CurrentEvent_EMCEHelixPx[CurrentEvent_nEMCE]  = gmom.X();
    CurrentEvent_EMCEHelixPy[CurrentEvent_nEMCE]  = gmom.Y();
    CurrentEvent_EMCEHelixPz[CurrentEvent_nEMCE]  = gmom.Z();
    CurrentEvent_EMCEHelixX[CurrentEvent_nEMCE]   = origin.X();
    CurrentEvent_EMCEHelixY[CurrentEvent_nEMCE]   = origin.Y();
    CurrentEvent_EMCEHelixZ[CurrentEvent_nEMCE]   = origin.Z();
    //CurrentEvent_EMCETOWE[CurrentEvent_nEMCE]     = EMCE;
    CurrentEvent_EMCENhitsFit[CurrentEvent_nEMCE] = nHitsFit;
    CurrentEvent_EMCENhitsDedx[CurrentEvent_nEMCE]= nHitsDedx;
    CurrentEvent_EMCEDca[CurrentEvent_nEMCE]      = dca;
    CurrentEvent_EMCETOWpovere[CurrentEvent_nEMCE]= EMCpovere;
    CurrentEvent_EMCEDistZ[CurrentEvent_nEMCE]    = ZDist;
    CurrentEvent_EMCEDistPhi[CurrentEvent_nEMCE]  = PhiDist;
    CurrentEvent_EMCESMDNEta[CurrentEvent_nEMCE]  = nEta;
    CurrentEvent_EMCESMDNPhi[CurrentEvent_nEMCE]  = nPhi;
    CurrentEvent_EMCEDsmADC[CurrentEvent_nEMCE]   = dsmadc;
    CurrentEvent_EMCEADC0[CurrentEvent_nEMCE]     = adc0;
    CurrentEvent_EMCENSigE[CurrentEvent_nEMCE]    = nSigE;
    CurrentEvent_nEMCE ++;
  }
  return kStOK;
}//end of main fucntion

//------------------------------------------------------------------
bool StMyAnalysisMaker::isHT0_BBCMB_TOF0(StPicoEvent *event, IntVec mTriggerIDs)
{
  if(event->isTrigger(mTriggerIDs[0])) return true;
  else return false;
}
//-----------------------------------------                                              
bool StMyAnalysisMaker::isHT2_BBCMB(StPicoEvent *event, IntVec mTriggerIDs)
{
  if(event->isTrigger(mTriggerIDs[1])) return true;
  else return false;
}
bool StMyAnalysisMaker::isGoodPartner(StPicoTrack* PeTrk)
{
  TVector3 gmom = PeTrk->gMom();
  float pt = gmom.Perp();
  if(pt <= 0.3) return false;
  //float eta = gmom.PseudoRapidity();
  //if(fabs(eta)>1.0) return false;
  float nhits = 1.*PeTrk->nHitsFit();
  float nhitmax = 1.*PeTrk->nHitsMax();
  float ratio = fabs(nhits)/nhitmax;
  //if(fabs(nhits)<nFPtsCutPart) return false;
  if(ratio<PtsRMin || ratio>PtsRMax) return false;
  
  return true;
}
//-----------------------------------------                                              
bool StMyAnalysisMaker::isGoodTrack(StPicoTrack* TeTrk)
{
  TVector3 pmom = TeTrk->pMom();
  float pt = pmom.Perp();
  if(pt<minPtCut) return false;
  float eta = pmom.PseudoRapidity();
  if(fabs(eta)>EtaCut) return false;
  float nhits = 1.*TeTrk->nHitsFit();
  float nhitmax = 1.*TeTrk->nHitsMax();
  //int nhitsdEdx = TeTrk->nHitsDedx();
  float ratio = fabs(nhits)/nhitmax;
  //if(fabs(nhits)<nFPtsCut) return false;
  if(ratio<PtsRMin || ratio>PtsRMax) return false;
  //if(nhitsdEdx<ndEdxPtsCut) return false;
  
  float Rx = TeTrk->origin().X();
  float Ry = TeTrk->origin().Y();
  float FirstTPCR = sqrt(Rx*Rx+Ry*Ry);
  if(FirstTPCR>=TPCFR) return false;
  
  return true;
}
bool StMyAnalysisMaker::isEMCTrack(StPicoTrack* TeTrk, StPicoBEmcPidTraits *TbemcPidTraits)
{
  TVector3 gmom = TeTrk->gMom();
  float gp      = gmom.Mag();
  float EMCE    = TbemcPidTraits->bemcE();
  float EMCpovere  = (EMCE>0) ? gp/EMCE : -999.; //???p/E0, wrong
  if(EMCE<0) return false;
  if(EMCpovere<PoeMin || EMCpovere>PoeMax) return false;
  
  return true;
}
bool StMyAnalysisMaker::isSMDTrack(StPicoTrack* TeTrk, StPicoBEmcPidTraits *TbemcPidTraits)
{
  float EMCDistZ   = TbemcPidTraits->bemcZDist();
  float EMCDistPhi = TbemcPidTraits->bemcPhiDist();
  int SMDNEta      = TbemcPidTraits->bemcSmdNEta();
  int SMDNPhi  = TbemcPidTraits->bemcSmdNPhi();
  if(fabs(EMCDistZ)>DistZ) return false;
  if(fabs(EMCDistPhi)>DistPhi) return false;
  if(SMDNEta<NEta) return false;
  if(SMDNPhi<NPhi) return false;
  
  return true;
}
//-----------------------------------------------------------------------
bool StMyAnalysisMaker::checkHotTower(int towId)
{
  Int_t   mNHotTower;
  mNHotTower = sizeof(mHotTower)/sizeof(int);
  
  for(int i=0; i < mNHotTower; i++)
  {
    if(towId == mHotTower[i])
      return true;
  }
  return false;
}
//---------------------------------------------------------------------------------------
void StMyAnalysisMaker::makerealevent()
{
  TLorentzVector FourMom1(0,0,0,0);
  TLorentzVector FourMom2(0,0,0,0);
  TLorentzVector FourMomR(0,0,0,0);
  
  for(int i=0; i<CurrentEvent_nEMCE; i++) {
    TVector3 Helix1P(CurrentEvent_EMCEHelixPx[i],CurrentEvent_EMCEHelixPy[i],CurrentEvent_EMCEHelixPz[i]);
    TVector3 Helix1O(CurrentEvent_EMCEHelixX[i],CurrentEvent_EMCEHelixY[i],CurrentEvent_EMCEHelixZ[i]);
    int   charge1  = CurrentEvent_EMCECharge[i];
    StPicoPhysicalHelix Helix1(Helix1P,Helix1O,CurrentEvent_bField,charge1);
    
    for(int j=0; j<CurrentEvent_nEs; j++) { // partner
      if(CurrentEvent_EMCEId[i] == CurrentEvent_EId[j]) continue;
      
      TVector3 Helix2P(CurrentEvent_EHelixPx[j],CurrentEvent_EHelixPy[j],CurrentEvent_EHelixPz[j]);
      TVector3 Helix2O(CurrentEvent_EHelixX[j],CurrentEvent_EHelixY[j],CurrentEvent_EHelixZ[j]);
      int   charge2  = CurrentEvent_ECharge[j];
      float PtPart       = CurrentEvent_EPt[j];
      float EtaPart      = CurrentEvent_EEta[j];
      int   ENhitsFit    = CurrentEvent_ENhitsFit[j];
      int   ENhitsDedx   = CurrentEvent_ENhitsDedx[j];
      float EDca         = CurrentEvent_EDca[j];
      float ETOWE        = CurrentEvent_ETOWE[j];
      float ETOWpovere   = CurrentEvent_ETOWpovere[j];
      float EDistZ       = CurrentEvent_EDistZ[j];
      float EDistPhi     = CurrentEvent_EDistPhi[j];
      int   ESMDNEta     = CurrentEvent_ESMDNEta[j];
      int   ESMDNPhi     = CurrentEvent_ESMDNPhi[j];
      StPicoPhysicalHelix Helix2(Helix2P,Helix2O,CurrentEvent_bField,charge2);
      
      double aPathLength = (Helix2.pathLengths(Helix1)).first;
      double ePathLength = (Helix2.pathLengths(Helix1)).second;
      
      TVector3 aOrigin   = Helix2.at(aPathLength);
      TVector3 eOrigin   = Helix1.at(ePathLength);
      TVector3 V0Origin  = (aOrigin+eOrigin)*0.5;
      TVector3 diff      = aOrigin-eOrigin;
      
      if(diff.Mag()<PairDiffMin || diff.Mag()>PairDiffMax) continue;
      
      TVector3 V0Mom1 = Helix1.momentumAt(ePathLength,CurrentEvent_bField);
      FourMom1.SetVectM(V0Mom1,MassE);
      
      TVector3 V0Mom2 = Helix2.momentumAt(aPathLength,CurrentEvent_bField);
      FourMom2.SetVectM(V0Mom2,MassE);
      FourMomR.SetVectM(-V0Mom2,MassE);
      
      TLorentzVector dieFourMom = FourMom1 + FourMom2;
      
      float M    = dieFourMom.M();
      TLorentzVector dieRFourMom = FourMom1 + FourMomR;
      
      if(M>0.3)continue;
      float PtTag           = CurrentEvent_EMCEPt[i];
      //float EMCETOWE        = CurrentEvent_EMCETOWE[i];
      int   EMCENhitsFit    = CurrentEvent_EMCENhitsFit[i];
      int   EMCENhitsDedx   = CurrentEvent_EMCENhitsDedx[i];
      float EMCEDca         = CurrentEvent_EMCEDca[i];
      float EMCETOWpovere   = CurrentEvent_EMCETOWpovere[i];
      float EMCEDistZ       = CurrentEvent_EMCEDistZ[i];
      float EMCEDistPhi     = CurrentEvent_EMCEDistPhi[i];
      int   EMCESMDNEta     = CurrentEvent_EMCESMDNEta[i];
      int   EMCESMDNPhi     = CurrentEvent_EMCESMDNPhi[i];
      int   EMCEDsmADC      = CurrentEvent_EMCEDsmADC[i];
      int   EMCEADC0        = CurrentEvent_EMCEADC0[i];
      float EMCENSigE       = CurrentEvent_EMCENSigE[i];
      //float ETOWE           = CurrentEvent_ETOWE[j];
      int  isTriggered = 0;
      int  isTrackQ = 0;
      int  isTrackQPart = 0;
      int  isEMC = 0;
      int  isSMD = 0;
      if(EMCEDsmADC>mHTth && EMCEADC0>mHTAdc0th) isTriggered = 1;
      if(EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut) isTrackQ = 1;
      if(fabs(EtaPart)<0.7&&ENhitsFit>=nFPtsCut&&ENhitsDedx>=ndEdxPtsCut&&EDca<dcaCut) isTrackQPart = 1;
      if(EMCETOWpovere>PoeMin && EMCETOWpovere<PoeMax) isEMC = 1;
      if(fabs(EMCEDistZ)<DistZ && fabs(EMCEDistPhi)<DistPhi && EMCESMDNEta>=NEta && EMCESMDNPhi>=NPhi) isSMD = 1;
      if(charge1*charge2 == -1) {
        /////////////////////////////////////////////////////
        //PHE
        /////////////////////////////////////////////////////
        if(isTriggered&&isTrackQ&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.) {
          hmvspt->Fill(PtTag,M);
          if(EMCEADC0>mHTAdc0thSys) hmvsptAdc0->Fill(PtTag,M);
          if(EMCENhitsFit>=nFPtsCutSys) hmvsptnHitsFit->Fill(PtTag,M);
          if(EMCENhitsDedx>=ndEdxPtsCutSys) hmvsptnHitsDedx->Fill(PtTag,M);
          if(EMCEDca<dcaCutSys) hmvsptDca->Fill(PtTag,M);
          if(EMCETOWpovere>PoeMinSys) hmvsptEMCpovere->Fill(PtTag,M);
          if(isSMD){
            hmvsptSMD->Fill(PtTag,M);
            if(EMCEADC0>mHTAdc0thSys) hmvsptAdc0SMD->Fill(PtTag,M);
            if(EMCENhitsFit>=nFPtsCutSys) hmvsptnHitsFitSMD->Fill(PtTag,M);
            if(EMCENhitsDedx>=ndEdxPtsCutSys) hmvsptnHitsDedxSMD->Fill(PtTag,M);
            if(EMCEDca<dcaCutSys) hmvsptDcaSMD->Fill(PtTag,M);
            if(EMCETOWpovere>PoeMinSys) hmvsptEMCpovereSMD->Fill(PtTag,M);
          }
        }
        if(M>0.1) continue;
        /////////////////////////////////////////////////////
        //Distribution
        /////////////////////////////////////////////////////
        if(isEMC&&EMCENSigE>-1.&&EMCENSigE<3.){
          if(isTrackQ) hAdc0PHE->Fill(PtTag,EMCEADC0);
          if(isTriggered&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut)
            hnHitsFit->Fill(PtTag,EMCENhitsFit);
          if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCEDca<dcaCut)
            hnHitsDedx->Fill(PtTag,EMCENhitsDedx);
          if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut)
            hDca->Fill(PtTag,EMCEDca);
          if(isSMD){
            if(isTrackQ) hAdc0PHESMD->Fill(PtTag,EMCEADC0);
            if(isTriggered&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut)
              hnHitsFitSMD->Fill(PtTag,EMCENhitsFit);
            if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCEDca<dcaCut)
              hnHitsDedxSMD->Fill(PtTag,EMCENhitsDedx);
            if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut)
              hDcaSMD->Fill(PtTag,EMCEDca);
          }
        }
        /////////////////////////////////////////////////////
        //nsigmae eff
        /////////////////////////////////////////////////////
        if(isTriggered&&isTrackQ&&isEMC){
          hNSigEeff->Fill(PtTag,EMCENSigE);
          if(isSMD) hNSigEeffSMD->Fill(PtTag,EMCENSigE);
          ////////////////////////////////////////////////////
          //SMD eff
          ///////////////////////////////////////////////////
          if(EMCENSigE>-1.&&EMCENSigE<3.){
            hTPCtracksTag->Fill(PtTag);
            if(isSMD) hSMDtracksTag->Fill(PtTag);
          }
        }
        /////////////////////////////////////////////////////
        //EMC eff
        /////////////////////////////////////////////////////
        if(isTriggered&&isTrackQ&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.&&isTrackQPart){
          hTPCtracks->Fill(PtPart);
          if(ETOWE>0.){//&&(fabs(dEta)>0.1||fabs(dPhi)>0.105))
            hEMCmatchingtracks->Fill(PtPart);
            if(ETOWpovere>PoeMin&&ETOWpovere<PoeMax){
              hEMCtracks->Fill(PtPart);
              if(ESMDNEta>0.&&ESMDNPhi>0.){
                hSMDmatchingtracks->Fill(PtPart);
                if(ESMDNEta>=NEta&&ESMDNPhi>=NPhi&&fabs(EDistPhi)<DistPhi&&fabs(EDistZ)<DistZ)
                  hSMDtracks->Fill(PtPart);
              }
            }
          }
          if(isSMD){
            hTPCtracksSMD->Fill(PtPart);
            if(ETOWE>0.){//&&(fabs(dEta)>0.1||fabs(dPhi)>0.PoeMax))
              hEMCmatchingtracksSMD->Fill(PtPart);
              if(ETOWpovere>PoeMin&&ETOWpovere<PoeMax){
                hEMCtracksSMD->Fill(PtPart);
                if(ESMDNEta>0.&&ESMDNPhi>0.){
                  hSMDmatchingtracksSMD->Fill(PtPart);
                  if(ESMDNEta>=NEta&&ESMDNPhi>=NPhi&&fabs(EDistPhi)<DistPhi&&fabs(EDistZ)<DistZ)
                    hSMDtracksSMD->Fill(PtPart);
                }
              }
            }
          }
        }
      }
      else{
        /////////////////////////////////////////////////////
        //PHE
        /////////////////////////////////////////////////////
        if(isTriggered&&isTrackQ&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.) {
          hmvsptlike->Fill(PtTag,M);
          if(EMCEADC0>mHTAdc0thSys) hmvsptAdc0like->Fill(PtTag,M);
          if(EMCENhitsFit>=nFPtsCutSys) hmvsptnHitsFitlike->Fill(PtTag,M);
          if(EMCENhitsDedx>=ndEdxPtsCutSys) hmvsptnHitsDedxlike->Fill(PtTag,M);
          if(EMCEDca<dcaCutSys) hmvsptDcalike->Fill(PtTag,M);
          if(EMCETOWpovere>PoeMinSys) hmvsptEMCpoverelike->Fill(PtTag,M);
          if(isSMD){
            hmvsptSMDlike->Fill(PtTag,M);
            if(EMCEADC0>mHTAdc0thSys) hmvsptAdc0SMDlike->Fill(PtTag,M);
            if(EMCENhitsFit>=nFPtsCutSys) hmvsptnHitsFitSMDlike->Fill(PtTag,M);
            if(EMCENhitsDedx>=ndEdxPtsCutSys) hmvsptnHitsDedxSMDlike->Fill(PtTag,M);
            if(EMCEDca<dcaCutSys) hmvsptDcaSMDlike->Fill(PtTag,M);
            if(EMCETOWpovere>PoeMinSys) hmvsptEMCpovereSMDlike->Fill(PtTag,M);
          }
        }
        if(M>0.1) continue;
        /////////////////////////////////////////////////////
        //Distribution
        /////////////////////////////////////////////////////
        if(isEMC&&EMCENSigE>-1.&&EMCENSigE<3.){
          if(isTrackQ) hAdc0PHElike->Fill(PtTag,EMCEADC0);
          if(isTriggered&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut)
            hnHitsFitlike->Fill(PtTag,EMCENhitsFit);
          if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCEDca<dcaCut)
            hnHitsDedxlike->Fill(PtTag,EMCENhitsDedx);
          if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut)
            hDcalike->Fill(PtTag,EMCEDca);
          if(isSMD){
            if(isTrackQ) hAdc0PHESMDlike->Fill(PtTag,EMCEADC0);
            if(isTriggered&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut)
              hnHitsFitSMDlike->Fill(PtTag,EMCENhitsFit);
            if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCEDca<dcaCut)
              hnHitsDedxSMDlike->Fill(PtTag,EMCENhitsDedx);
            if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut)
              hDcaSMDlike->Fill(PtTag,EMCEDca);
          }
        }
        /////////////////////////////////////////////////////
        //nsigmae eff
        /////////////////////////////////////////////////////
        if(isTriggered&&isTrackQ&&isEMC){
          hNSigEefflike->Fill(PtTag,EMCENSigE);
          if(isSMD) hNSigEeffSMDlike->Fill(PtTag,EMCENSigE);
          ////////////////////////////////////////////////////
          //SMD eff
          ///////////////////////////////////////////////////
          if(EMCENSigE>-1.&&EMCENSigE<3.){
            hTPCtracksTaglike->Fill(PtTag);
            if(isSMD) hSMDtracksTaglike->Fill(PtTag);
          }
        }
        /////////////////////////////////////////////////////
        //EMC eff
        /////////////////////////////////////////////////////
        if(isTriggered&&isTrackQ&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.&&isTrackQPart){
          hTPCtrackslike->Fill(PtPart);
          if(ETOWE>0.){//&&(fabs(dEta)>0.1||fabs(dPhi)>0.PoeMax))
            hEMCmatchingtrackslike->Fill(PtPart);
            if(ETOWpovere>PoeMin&&ETOWpovere<PoeMax){
              hEMCtrackslike->Fill(PtPart);
              if(ESMDNEta>0.&&ESMDNPhi>0.){
                hSMDmatchingtrackslike->Fill(PtPart);
                if(ESMDNEta>=NEta&&ESMDNPhi>=NPhi&&fabs(EDistPhi)<DistPhi&&fabs(EDistZ)<DistZ)
                  hSMDtrackslike->Fill(PtPart);
              }
            }
          }
          if(isSMD){
            hTPCtracksSMDlike->Fill(PtPart);
            if(ETOWE>0.){//&&(fabs(dEta)>0.1||fabs(dPhi)>0.PoeMax))
              hEMCmatchingtracksSMDlike->Fill(PtPart);
              if(ETOWpovere>PoeMin&&ETOWpovere<PoeMax){
                hEMCtracksSMDlike->Fill(PtPart);
                if(ESMDNEta>0.&&ESMDNPhi>0.){
                  hSMDmatchingtracksSMDlike->Fill(PtPart);
                  if(ESMDNEta>=NEta&&ESMDNPhi>=NPhi&&fabs(EDistPhi)<DistPhi&&fabs(EDistZ)<DistZ)
                    hSMDtracksSMDlike->Fill(PtPart);
                }
              }
            }
          }
        }
      }
    }//e2
  }//e1
}
