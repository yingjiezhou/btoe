#include "StPicoHadrDCAMaker.h"
#include "StRoot/StPicoDstMaker/StPicoDst.h"
#include "StRoot/StPicoDstMaker/StPicoTrack.h"
#include "StRoot/StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StPicoDstMaker/StPicoEvent.h"
#include "StRoot/StPicoDstMaker/StPicoMtdHit.h"
#include "StRoot/StPicoDstMaker/StPicoConstants.h"
#include "StRoot/StPicoDstMaker/StPicoMtdPidTraits.h"
#include "StRoot/StPicoDstMaker/StPicoBTofPidTraits.h"
#include "StRoot/StPicoDstMaker/StPicoEmcPidTraits.h"
#include "StRoot/StPicoDstMaker/StPicoEmcTrigger.h"
#include "StRoot/StRefMultCorr/StRefMultCorr.h"
#include "StRoot/StRefMultCorr/CentralityMaker.h"
#include "StDcaGeometry.h"

#include "StThreeVectorF.hh"
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "THnSparse.h"
#include "TFile.h"
#include <map>
#include<iostream>
#include<fstream>
#include "mBadRunList.h"
#include "mHotTowerList.h"
#include "StBTofUtil/tofPathLength.hh"
#define USHRT_MAX 65535

Bool_t fillhistflag=1;
ofstream runidfiles;
Int_t runIndex;
Int_t randomId;
Int_t mTotalRun = 599;//603
Bool_t DEBUG = kFALSE;

ClassImp(StPicoHadrDCAMaker)

//-----------------------------------------------------------------------------
StPicoHadrDCAMaker::StPicoHadrDCAMaker(const char* name, StPicoDstMaker *picoMaker, const char* outName)
: StMaker(name)
{
  mPicoDstMaker = picoMaker;
  mPicoDst = 0;
  runMode = 0;
  TH3F:: SetDefaultSumw2();//zaochen add
  TH2F:: SetDefaultSumw2();//zaochen add
  TH1F:: SetDefaultSumw2();//zaochen add
  
  mOutName = outName;
  
  mNBadRuns = sizeof(mBadRuns)/sizeof(int);
  mNHotTower1 = sizeof(mHotTower1)/sizeof(int);
  mNHotTower2 = sizeof(mHotTower2)/sizeof(int);
  mNHotTower3 = sizeof(mHotTower3)/sizeof(int);
  
  // ZWM Add (declare default cut values, can change in Ana with same function)
  SetDefaultCuts();
}

//-----------------------------------------------------------------------------
StPicoHadrDCAMaker::~StPicoHadrDCAMaker()
{ /*  */ }

//-----------------------------------------------------------------------------
Int_t StPicoHadrDCAMaker::Init() {
  cout << " --------------------------------------------------- in purity init ------------------------------------------------------- " << endl;
  cout << " mOutName = " << mOutName.Data() << endl;
  if(mOutName!="") {
    fout = new TFile(mOutName.Data(),"RECREATE");
  }else{
    fout = new TFile("picoQA_test.root","RECREATE");
  }
  DeclareHistograms();
  
  //runidfiles.open("/star/u/zye20/zye20/zaochen/analysis/run14picoQA/runnumber.txt", ios::out|ios::app);
  TString modeDescription = "p+p (no Centrality)";
  if(runMode == AuAu) modeDescription = "Au+Au (Centrality On)";
  cout << "StElecPurityMaker running in " << modeDescription << " mode." << endl;
  
  if(fillhistflag){
    //read in the runlist.dat
    ifstream indata;
    indata.open("StRoot/StPicoHadrDCAMaker/mTotalRunList.dat");
    //indata.open("StRoot/StPicoHadrDCAMaker/mTotalRunList15.dat");
    mTotalRunId.clear();
    if(indata.is_open()){
      cout<<"read in total run number list and recode run number ...";
      Int_t oldId;
      Int_t newId=0;
      while(indata>>oldId){
        mTotalRunId[oldId] = newId;
        newId++;
      }
      cout<<" [OK]"<<endl;
      
    }else{
      cout<<"Failed to load the total run number list !!!"<<endl;
      return kFALSE;
    }
    
    indata.close();
    
    for(map<Int_t,Int_t>::iterator iter=mTotalRunId.begin();iter!=mTotalRunId.end();iter++)
      cout<<iter->second<<" \t"<<iter->first<<endl;
    cout<<endl;
    //
    //read in the runidlist
    
    
  }//
  
  
  return kStOK;
}

//-----------------------------------------------------------------------------
Int_t StPicoHadrDCAMaker::Finish() {
  fout->cd();
  for(int tr=0; tr<4; tr++){
    cout << "Writing out purity Hists trig: " << tr << endl;
    hNEvents[tr]->Write();
    hNTracks[tr]->Write();
    HadronDcaXy_Pt[tr][0]->Write();
    HadronDcaXy_Pt[tr][1]->Write();
    HadronDcaZ_Pt[tr][0]->Write();
    HadronDcaZ_Pt[tr][1]->Write();
    PiDcaXy_Pt[tr][0]->Write();
    PiDcaXy_Pt[tr][1]->Write();
    PiDcaZ_Pt[tr][0]->Write();
    PiDcaZ_Pt[tr][1]->Write();
    KaonDcaXy_Pt[tr][0]->Write();
    KaonDcaXy_Pt[tr][1]->Write();
    KaonDcaZ_Pt[tr][0]->Write();
    KaonDcaZ_Pt[tr][1]->Write();

    mnsigmaE_pT_all[tr][0]->Write();
    mnsigmaE_pT_all[tr][1]->Write();
    TOF_beta_p_all[tr][0]->Write();
    TOF_beta_p_all[tr][1]->Write();
  }
  fout->Close();
  return kStOK;
}

//-----------------------------------------------------------------------------
void StPicoHadrDCAMaker::DeclareHistograms() {
  
  // Define parameters for histo definitions that change often
  Float_t DcaLim_h = 0.1; // To fix bin undulation
  Float_t DcaLim_l = -0.1; // To fix bin undulation
  
  Float_t betaLow = 0.8;
  Float_t betaHigh = 1.8;
  fout->cd();
  
  trigType = new TH1F("trigType","1:MB,2:HT1,4:HT2,8:HT3. Sum all triggers in hist",40,0,20);
  for(int tr=0; tr<numTrigs; tr++)
  {
    hNEvents[tr] = new TH1F(Form("hNEvents_%i",tr),"number of events: 0 for total and 2 for MBs events and 4 for Vz<6cm", 10, 0, 10 );
    mNptracks[tr] = new TH1F(Form("Nptracks_%i",tr),"#primary tracks",200,0,2000);
    mNgtracks[tr] = new TH1F(Form("Ngtracks_%i",tr),"# global tracks ",200,0,5000);
    
    hNTracks[tr] = new TH1F(Form("hNTracks_%i",tr),"Number of Tracks before (0) and after cuts (2);",10,0,10);
    
    //===zyj===
    HadronDcaXy_Pt[tr][0] = new TH2F(Form("HadronDcaXy_Pt_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);
    HadronDcaXy_Pt[tr][1] = new TH2F(Form("HadronDcaXy_Pt_HFT_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);
    HadronDcaZ_Pt[tr][0] = new TH2F(Form("HadronDcaZ_Pt_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);
    HadronDcaZ_Pt[tr][1] = new TH2F(Form("HadronDcaZ_Pt_HFT_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);

    PiDcaXy_Pt[tr][0] = new TH2F(Form("PiDcaXy_Pt_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);
    PiDcaXy_Pt[tr][1] = new TH2F(Form("PiDcaXy_Pt_HFT_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);
    PiDcaZ_Pt[tr][0] = new TH2F(Form("PiDcaZ_Pt_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);
    PiDcaZ_Pt[tr][1] = new TH2F(Form("PiDcaZ_Pt_HFT_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);

    KaonDcaXy_Pt[tr][0] = new TH2F(Form("KaonDcaXy_Pt_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);
    KaonDcaXy_Pt[tr][1] = new TH2F(Form("KaonDcaXy_Pt_HFT_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);
    KaonDcaZ_Pt[tr][0] = new TH2F(Form("KaonDcaZ_Pt_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);
    KaonDcaZ_Pt[tr][1] = new TH2F(Form("KaonDcaZ_Pt_HFT_%i",tr),"",400,0,20,400,DcaLim_l,DcaLim_h);

    mnsigmaE_pT_all[tr][0] = new TH2F(Form("mnsigmaE_pT_all%i",tr),"",400,0,20,3000,-10,8);
    mnsigmaE_pT_all[tr][1] = new TH2F(Form("mnsigmaE_pT_all_HFT_%i",tr),"",400,0,20,3000,-10,8);
    TOF_beta_p_all[tr][0] = new TH2F(Form("TOF_beta_p_all%i", tr), "",400,0,20,600,0,3);
    TOF_beta_p_all[tr][1] = new TH2F(Form("TOF_beta_p_all_HFT_%i", tr), "",400,0,20,600,0,3);
    
    //===zyj===
    HadronDcaXy_Pt[tr][0]->Sumw2();
    HadronDcaXy_Pt[tr][1]->Sumw2();
    HadronDcaZ_Pt[tr][0]->Sumw2();
    HadronDcaZ_Pt[tr][1]->Sumw2();
    PiDcaXy_Pt[tr][0]->Sumw2();
    PiDcaXy_Pt[tr][1]->Sumw2();
    PiDcaZ_Pt[tr][0]->Sumw2();
    PiDcaZ_Pt[tr][1]->Sumw2();
    KaonDcaXy_Pt[tr][0]->Sumw2();
    KaonDcaXy_Pt[tr][1]->Sumw2();
    KaonDcaZ_Pt[tr][0]->Sumw2();
    KaonDcaZ_Pt[tr][1]->Sumw2();
    
    mnsigmaE_pT_all[tr][0]->Sumw2();
    mnsigmaE_pT_all[tr][1]->Sumw2();
    TOF_beta_p_all[tr][0]->Sumw2();
    TOF_beta_p_all[tr][1]->Sumw2();
  }// er chen
}
//-----------------------------------------------------------------------------
void StPicoHadrDCAMaker::Clear(Option_t *opt) {
  
}

//-----------------------------------------------------------------------------
Int_t StPicoHadrDCAMaker::Make() {
  if(!mPicoDstMaker) {
    LOG_WARN << " No PicoDstMaker! Skip! " << endm;
    return kStWarn;
  }
  
  mPicoDst = mPicoDstMaker->picoDst();
  
  if(!mPicoDst) {
    LOG_WARN << " No PicoDst! Skip! " << endm;
    return kStWarn;
  }
  
  StPicoEvent* event=mPicoDst->event();
  if(DEBUG)std::cout << "Zach Out: Before Bad Run" << endl;
  //=================zaochen add====================
  if(!event) return kStOK;
  //=================event selection================
  int runId = event->runId();
  for(int i=0;i<mNBadRuns;i++){
    if(runId==mBadRuns[i]) return kStOK;
  }
  if(DEBUG)std::cout << "Zach Out: After Bad Run" << endl;
  trig = 99;
  trigCounter=0.; // Used to find overlaps in samples. Modified after checking event cuts. Re-zero each event.
  if( isMB  ( event ) )   {FillHistograms(0,event);} // Decide what type of trigger you have, use to select what histos to fill
  if( isBHT1( event ) )   {FillHistograms(1,event);}
  if( isBHT2( event ) )   {FillHistograms(2,event);}
  if( isBHT3( event ) )   {FillHistograms(3,event);}
  if(trigCounter == 0)
    trigCounter = -99;
  trigType->Fill(trigCounter); // Use to detect sample overlaps
  if( trig == 99 ) return kStOK; // if no trigger match, throw out event
  
  return kStOK;
}

Int_t StPicoHadrDCAMaker::FillHistograms(Int_t trig, StPicoEvent* event)
{
  
  Bool_t bPassGoodEvents_Cuts=false;
  Bool_t bPass_HFT_GoodEvents_Cuts=false;
  
  if(DEBUG)std::cout << "Zach Out: In Fill Histograms trig" << trig << endl;
  //=================event selection================
  hNEvents[trig]->Fill(0);
  if(!passEventCuts(event,trig) )  return kStOK;
  bPassGoodEvents_Cuts=true;
  if(pass_HFT_EventCuts(event,trig))
    bPass_HFT_GoodEvents_Cuts=true;
  
  if(DEBUG)std::cout << "Zach Out: After Event Cut" << endl;
  hNEvents[trig]->Fill(2);
  
  
  // For sample overlap
  if(trig == 0) trigCounter += 1;
  if(trig == 1) trigCounter += 2;
  if(trig == 2) trigCounter += 4;
  if(trig == 3) trigCounter += 8;
  
  //----------track information------------------------
  Int_t NGtrks = event->numberOfGlobalTracks();
  Int_t numberoftracks = mPicoDst->numberOfTracks();
  if(fillhistflag){
    mNptracks[trig]->Fill(numberoftracks);
    mNgtracks[trig]->Fill(NGtrks);
  }//
  
  StThreeVectorF vertexPos;
  vertexPos = event->primaryVertex();
  
  Int_t Nprimarytracks=0;
  
  // TRACK LOOP
  if(DEBUG)std::cout << "Zach Out: At Track Loop" << endl;
  for(int i=0; i<numberoftracks; i++){
    int    trkHFTflag = 0;
    StPicoTrack* track=(StPicoTrack*) mPicoDst->track(i);
    Bool_t HFT_trackflag=false;
    Bool_t isGoodTrack=false;
    Bool_t isGoodTrack_NoEta =false;
    
    if(track->isHFTTrack()) { trkHFTflag=1;HFT_trackflag=true;}
    if(passGoodTrack(event,track,trig))  isGoodTrack=true;
    if(passGoodTrack_NoEta(event,track,trig)) isGoodTrack_NoEta=true;
    
    if(isGoodTrack_NoEta)
      hNTracks[trig]->Fill(2);
    
    if(isGoodTrack)
      hNTracks[trig]->Fill(3);
    
    if(isGoodTrack&&bPass_HFT_GoodEvents_Cuts)
      hNTracks[trig]->Fill(4);
    
    if(isGoodTrack&&bPass_HFT_GoodEvents_Cuts&&HFT_trackflag)
      hNTracks[trig]->Fill(5);
    
    if(!isGoodTrack) continue;
    
    Double_t meta,mpt;
    //change to global track
    meta=track->gMom(event->primaryVertex(),event->bField()).pseudoRapidity();
    if(track->pMom().mag()!=0) Nprimarytracks++;
    mpt=track->gMom(event->primaryVertex(),event->bField()).perp();
    
    StPhysicalHelixD helix = track->helix();
    StThreeVectorF dcaPoint = helix.at(helix.pathLength(vertexPos.x(), vertexPos.y()));
    float dcaZ = (dcaPoint.z() - vertexPos.z());
    float dcaXY = (helix.geometricSignedDistance(vertexPos.x(),vertexPos.y()));
    
    Double_t nsigpi=track->nSigmaPion();
    Double_t nsigk=track->nSigmaKaon();
    Double_t nsige=track->nSigmaElectron();
    
    // track dca info
    //tpc pid on pi, k, p,
    HadronDcaXy_Pt[trig][0]->Fill(mpt,dcaXY);
    HadronDcaZ_Pt[trig][0]->Fill(mpt,dcaZ);
    
    if(fabs(nsigpi)<2.0) {
      PiDcaXy_Pt[trig][0]->Fill(mpt,dcaXY);
      PiDcaZ_Pt[trig][0]->Fill(mpt,dcaZ);
    }
    if(fabs(nsigk)<2.0){
      KaonDcaXy_Pt[trig][0]->Fill(mpt,dcaXY);
      KaonDcaZ_Pt[trig][0]->Fill(mpt,dcaZ);
    }
    
    //tpc pid on pi, k, p---wHFT
    if(HFT_trackflag&&bPass_HFT_GoodEvents_Cuts){ // I will use this infromation zyj
      HadronDcaXy_Pt[trig][1]->Fill(mpt,dcaXY);
      HadronDcaZ_Pt[trig][1]->Fill(mpt,dcaZ);
      if(fabs(nsigpi)<2.0) {
        PiDcaXy_Pt[trig][1]->Fill(mpt,dcaXY);
        PiDcaZ_Pt[trig][1]->Fill(mpt,dcaZ);
      }
      if(fabs(nsigk)<2.0){
        KaonDcaXy_Pt[trig][1]->Fill(mpt,dcaXY);
        KaonDcaZ_Pt[trig][1]->Fill(mpt,dcaZ);
      }
    }
    
    mnsigmaE_pT_all[trig][0]->Fill(mpt, nsige );
    if(HFT_trackflag&&bPass_HFT_GoodEvents_Cuts)
    {
      mnsigmaE_pT_all[trig][1]->Fill(mpt, nsige );
    }
    if(trig==0&&passTOFCuts(event, track,trig)&&passBEMCCuts_noTrigger(event,track,trig))
    {
      Int_t tofpidid=track->bTofPidTraitsIndex();
      if(tofpidid>=0){
        StPicoBTofPidTraits* btofpidtrait=(StPicoBTofPidTraits*) mPicoDst->btofPidTraits(tofpidid);
        Float_t beta=btofpidtrait->btofBeta();
        StPhysicalHelixD helix = track->helix();
        if(beta<1e-4||beta>=(USHRT_MAX-1)/20000){
          Float_t tof = btofpidtrait->btof();
          StThreeVectorF btofHitPos = btofpidtrait->btofHitPos();
          float L = tofPathLength(&vertexPos, &btofHitPos, helix.curvature());
          if(tof>0) beta = L/(tof*(c_light/1.0e9));
        }
        Float_t tofbeta = beta;
        
        TOF_beta_p_all[trig][0]->Fill(mpt,tofbeta);
        if(HFT_trackflag&&bPass_HFT_GoodEvents_Cuts)
        {
          TOF_beta_p_all[trig][1]->Fill(mpt,tofbeta);
        }
      }
    }
    
  }//loop of all tracks
  return kStOK;
}//end of main filling fucntion

//=====================ZAOCHEN'S FUNCTION=======================================

Bool_t StPicoHadrDCAMaker::checkTriggers(StPicoEvent *ev, int trigType)
{
  for(auto trg = triggers[trigType].begin(); trg < triggers[trigType].end(); ++trg)
  {
    if(ev->isTrigger(*trg))
      return true;
  }
  return false;
}


Bool_t StPicoHadrDCAMaker::isBHT0(StPicoEvent *event)
{
  return checkTriggers(event,0);
}


Bool_t StPicoHadrDCAMaker::isBHT1(StPicoEvent *event)
{
  return checkTriggers(event,1);
}

//-----------------------------------------
Bool_t StPicoHadrDCAMaker::isBHT2(StPicoEvent *event)
{
  return checkTriggers(event,2);
}

//---------------------------------------------------
Bool_t StPicoHadrDCAMaker::isBHT3(StPicoEvent *event)
{
  return checkTriggers(event,3);
}

Bool_t StPicoHadrDCAMaker::isMB(StPicoEvent *event)
{
  return checkTriggers(event,4);
}

//-------------------------------------------------------------

Bool_t StPicoHadrDCAMaker::passGoodTrack(StPicoEvent* event, StPicoTrack* track, int trig)
{
  
  double fithitfrac, chargeq, fhitsdEdx, fhitsFit,feta;
  double pt = track->gMom(event->primaryVertex(),event->bField()).perp();
  feta=track->gMom(event->primaryVertex(),event->bField()).pseudoRapidity();
  fhitsFit = track->nHitsFit();
  fithitfrac=fhitsFit/track->nHitsMax();
  fhitsdEdx = track->nHitsDedx();
  chargeq=track->charge();
  double PtCut = 0.2;
  
  // if(pt>=0.2&&fabs(feta)<=0.7)
  //   return true;
  
  // else return false;
  
  double mdca;
  // Get DCA info
  StThreeVectorF vertexPos;
  vertexPos = event->primaryVertex();
  StDcaGeometry *dcaG = new StDcaGeometry();
  dcaG->set(track->params(),track->errMatrix());
  StPhysicalHelixD helix = dcaG->helix();
  delete dcaG;
  StThreeVectorF dcaPoint = helix.at( helix.pathLength(vertexPos.x(), vertexPos.y())  );
  // StThreeVectorF dcaPoint = helix.at(vertexPos);
  double thePath = helix.pathLength(vertexPos);
  StThreeVectorF dcaPos = helix.at(thePath);
  
  double dcamag= (dcaPos-vertexPos).mag();
  
  StThreeVectorF dcaP = helix.momentumAt( vertexPos.x(),vertexPos.y() );
  mdca = dcamag;
  
  if(pt>PtCut && fhitsFit > nhitsFitCut && fhitsdEdx > nhitsdEdxCut && fithitfrac >= nhitsRatioCut && fithitfrac<=1.02   && fabs(feta) < etaCut && fabs(mdca) < dcaCut )
    
    return true;
  
  return kFALSE;
}

// ----------------------------------------------------------
Bool_t StPicoHadrDCAMaker::passGoodTrack_NoEta(StPicoEvent* event, StPicoTrack* track, int trig)
{
  if(DEBUG)std::cout << "Zach Out: passGoodTrack_NoEta" << endl;
  double fithitfrac, chargeq, fhitsdEdx, fhitsFit,feta;
  double pt = track->gMom(event->primaryVertex(),event->bField()).perp();
  feta=track->gMom(event->primaryVertex(),event->bField()).pseudoRapidity();
  fhitsFit = track->nHitsFit();
  fithitfrac=fhitsFit/track->nHitsMax();
  fhitsdEdx = track->nHitsDedx();
  chargeq=track->charge();
  double PtCut = 0.2;
  
  double mdca;
  // Get DCA info
  StThreeVectorF vertexPos;
  vertexPos = event->primaryVertex();
  StDcaGeometry *dcaG = new StDcaGeometry();
  dcaG->set(track->params(),track->errMatrix());
  StPhysicalHelixD helix = dcaG->helix();
  delete dcaG;
  StThreeVectorF dcaPoint = helix.at( helix.pathLength(vertexPos.x(), vertexPos.y())  );
  double dcamag= (dcaPoint-vertexPos).mag();
  StThreeVectorF dcaP = helix.momentumAt( vertexPos.x(),vertexPos.y() );
  double dcaXY= ( (dcaPoint-vertexPos).x()*dcaP.y()-(dcaPoint-vertexPos).y()*dcaP.x() )/dcaP.perp();
  double dcaZ= dcaPoint.z() - vertexPos.z();
  mdca = dcamag;
  
  if(pt> PtCut && fhitsFit >= nhitsFitCut && fhitsdEdx >= nhitsdEdxCut && fithitfrac >= nhitsRatioCut && fabs(chargeq)>0 && mdca < dcaCut && mdca > 0.) return true;
  else return false;
}

//-------------------------------------------------------------

Int_t StPicoHadrDCAMaker::passSMDCuts(StPicoEvent* event, StPicoTrack* track, int trig)
{
  // Get SMD info
  
  // Get BEMC info
  Int_t emcpidtraitsid=track->emcPidTraitsIndex();
  double mpoe;
  int dsmadc = 1;
  int bemcId, btowId, nPhi,nEta;
  float zDist, phiDist,e0,adc0;
  if(emcpidtraitsid>=0){
    StPicoEmcPidTraits* emcpidtraits=(StPicoEmcPidTraits*) mPicoDst->emcPidTraits(emcpidtraitsid);
    
    bemcId = emcpidtraits->bemcId();
    adc0   = emcpidtraits->adc0();
    e0     = emcpidtraits->e0();
    btowId = emcpidtraits->btowId();
    zDist = emcpidtraits->zDist();
    phiDist = emcpidtraits->phiDist();
    nEta = emcpidtraits->nEta();
    nPhi = emcpidtraits->nPhi();
    mpoe = track->gMom(event->primaryVertex(),event->bField()).mag()/emcpidtraits->e();
    // get DSM Adc by finding the tower with same id as trk, then getting that ADC
    int nTrgs = mPicoDst->numberOfEmcTriggers();
    for(int j=0;j<nTrgs;j++){
      StPicoEmcTrigger *trg = (StPicoEmcTrigger*)mPicoDst->emcTrigger(j);
      if((trg->flag() & 0xf)){
        int trgId = trg->id();
        if(btowId == trgId){
          if(DEBUG)cout << "bTowId: " << btowId << " ";
          if(DEBUG)cout << "trgID: " << trgId << " ";
          dsmadc = trg->adc();
          if(DEBUG)cout << "trg->adc(): " << dsmadc << endl;
          break;
        }
      }
    }
  }
  else
  {
    mpoe = 0.0; // if no BEMC, set value = 0
    nPhi = -999;
  }
  double mpt  = track->gMom(event->primaryVertex(),event->bField()).perp();
  
  if(mpt > bemcPtCut && fabs(zDist) < zDistCut2 && fabs(phiDist) < phiDistCut2 && nEta >= nEtaCut2 && nPhi >= nPhiCut2)
    return 2;
  else if(mpt > bemcPtCut && fabs(zDist) < zDistCut && fabs(phiDist) < phiDistCut && nEta >= nEtaCut && nPhi >= nPhiCut)
    return 1;
  else
    return 0;
}

Bool_t StPicoHadrDCAMaker::passBEMCCuts(StPicoEvent* event, StPicoTrack* track, int trig)
{
  // Get BEMC info
  Int_t emcpidtraitsid=track->emcPidTraitsIndex();
  double mpoe;
  int dsmadc = 1;
  int bemcId, btowId, nPhi,nEta;
  float zDist, phiDist,e0,adc0;
  double mpt  = track->gMom(event->primaryVertex(),event->bField()).perp();
  if(emcpidtraitsid>=0){
    StPicoEmcPidTraits* emcpidtraits=(StPicoEmcPidTraits*) mPicoDst->emcPidTraits(emcpidtraitsid);
    
    bemcId = emcpidtraits->bemcId();
    adc0   = emcpidtraits->adc0();
    e0     = emcpidtraits->e0();
    btowId = emcpidtraits->btowId();
    zDist = emcpidtraits->zDist();
    phiDist = emcpidtraits->phiDist();
    nEta = emcpidtraits->nEta();
    nPhi = emcpidtraits->nPhi();
    mpoe = track->gMom(event->primaryVertex(),event->bField()).mag()/emcpidtraits->e0();
    // Check if hot tower. If so, return BEMC failure
    int runId = event->runId();
    // if(checkHotTower(runId,btowId))
    //   return false;
    
    // get DSM Adc by finding the tower with same id as trk, then getting that ADC
    int nTrgs = mPicoDst->numberOfEmcTriggers();
    for(int j=0;j<nTrgs;j++){
      StPicoEmcTrigger *trg = (StPicoEmcTrigger*)mPicoDst->emcTrigger(j);
      if(mpt<1) continue;
      if(btowId<1||btowId>4800 ) continue;
      if((trg->flag() & 0xf)){
        int trgId = trg->id();
        if(btowId == trgId){
          if(DEBUG)cout << "bTowId: " << btowId << " ";
          if(DEBUG)cout << "trgID: " << trgId << " ";
          dsmadc = trg->adc();
          if(DEBUG)cout << "trg->adc(): " << dsmadc << endl;
          break;
        }
      }
    }
  }
  else {
    return false;
  }
  
  //cout << "pT: " << mpt << " p/E: " << mpoe << " e0: " << e0 << " dsmadc: " << dsmadc << endl;
  if(mpt<=bemcPtCut) return true;
  if( mpt > bemcPtCut && mpoe > poeCutLow && mpoe < poeCutHigh&&adc0>getadc0Cut(trig)&&dsmadc > getDsmAdcCut(trig) )
    //     if( mpt > bemcPtCut && mpoe > poeCutLow && mpoe < poeCutHigh && dsmadc > getDsmAdcCut(trig) )
    return true;
  else
    return false;
}

Bool_t StPicoHadrDCAMaker::passBEMCCuts_noTrigger(StPicoEvent* event, StPicoTrack* track, int trig)
{
  // Get BEMC info
  Int_t emcpidtraitsid=track->emcPidTraitsIndex();
  double mpoe;
  int dsmadc = 1;
  int bemcId, btowId, nPhi,nEta;
  float zDist, phiDist,e0,adc0;
  if(emcpidtraitsid>=0){
    StPicoEmcPidTraits* emcpidtraits=(StPicoEmcPidTraits*) mPicoDst->emcPidTraits(emcpidtraitsid);
    
    bemcId = emcpidtraits->bemcId();
    adc0   = emcpidtraits->adc0();
    e0     = emcpidtraits->e0();
    btowId = emcpidtraits->btowId();
    zDist = emcpidtraits->zDist();
    phiDist = emcpidtraits->phiDist();
    nEta = emcpidtraits->nEta();
    nPhi = emcpidtraits->nPhi();
    mpoe = track->gMom(event->primaryVertex(),event->bField()).mag()/emcpidtraits->e0();
    // Check if hot tower. If so, return BEMC failure
    int runId = event->runId();
    // if(checkHotTower(runId,btowId))
    //   return false;
    
    // get DSM Adc by finding the tower with same id as trk, then getting that ADC
    int nTrgs = mPicoDst->numberOfEmcTriggers();
    for(int j=0;j<nTrgs;j++){
      StPicoEmcTrigger *trg = (StPicoEmcTrigger*)mPicoDst->emcTrigger(j);
      if((trg->flag() & 0xf)){
        int trgId = trg->id();
        
        if(btowId == trgId){
          if(DEBUG)cout << "bTowId: " << btowId << " ";
          if(DEBUG)cout << "trgID: " << trgId << " ";
          dsmadc = trg->adc();
          if(DEBUG)cout << "trg->adc(): " << dsmadc << endl;
          break;
        }
      }
    }
  }
  else {
    return false;
  }
  double mpt  = track->gMom(event->primaryVertex(),event->bField()).perp();
  //cout << "pT: " << mpt << " p/E: " << mpoe << " e0: " << e0 << " dsmadc: " << dsmadc << endl;
  if(mpt<=bemcPtCut) return true;
  if( mpt > bemcPtCut && mpoe > poeCutLow && mpoe < poeCutHigh )
    //     if( mpt > bemcPtCut && mpoe > poeCutLow && mpoe < poeCutHigh && dsmadc > getDsmAdcCut(trig) )
    return true;
  else
    return false;
}



Bool_t StPicoHadrDCAMaker::checkHotTower(int runId, int towId)
{
  if(DEBUG)std::cout << "Zach Out: checkHotTower" << endl;
  if(runId >= 15071020 && runId <= 15086063) // range 1 of hot tower ist
  {
    for(int i=0; i < mNHotTower1; i++)
    {
      if(towId == mHotTower1[i])
        return true;
    }
  }
  
  if(runId >= 15086064 && runId <= 15128024) // range 2 of hot tower ist
  {
    for(int i=0; i < mNHotTower2; i++)
    {
      if(towId == mHotTower2[i])
        return true;
    }
  }
  
  if(runId >= 15128025 && runId <= 15167014) // range 3 of hot tower ist
  {
    for(int i=0; i < mNHotTower3; i++)
    {
      if(towId == mHotTower3[i])
        return true;
    }
  }
  return false;
}

Bool_t StPicoHadrDCAMaker::passTOFCuts(StPicoEvent* event, StPicoTrack* track, int trig)
{
  // Get TOF Infor
  Float_t invBeta=9999;
  Float_t toflocaly=9999;
  Float_t tofMatchFlag = -1;
  StThreeVectorF vertexPos;
  vertexPos = event->primaryVertex();
  Int_t tofpidid=track->bTofPidTraitsIndex();
  if(tofpidid>=0){
    StPicoBTofPidTraits* btofpidtrait=(StPicoBTofPidTraits*) mPicoDst->btofPidTraits(tofpidid);
    
    //------tof information start----------
    //Float_t tofbeta=btofpidtrait->btofBeta();
    Float_t beta=btofpidtrait->btofBeta();
    StPhysicalHelixD helix = track->helix();
    if(beta<1e-4||beta>=(USHRT_MAX-1)/20000){
      Float_t tof = btofpidtrait->btof();
      StThreeVectorF btofHitPos = btofpidtrait->btofHitPos();
      float L = tofPathLength(&vertexPos, &btofHitPos, helix.curvature());
      if(tof>0) beta = L/(tof*(c_light/1.0e9));
    }
    Float_t tofbeta = beta;
    invBeta = (1./tofbeta) - 1.0;
    toflocaly = btofpidtrait->btofYLocal();
    tofMatchFlag = btofpidtrait->btofMatchFlag();
  }
  double mpt  = track->gMom(event->primaryVertex(),event->bField()).perp();
  if( fabs(invBeta) < tofInvBetaCut  && fabs(toflocaly) < toflocalyCut && tofMatchFlag>0)
    return true;
  else return false;
}

//-------------------------------------------------------------

Bool_t StPicoHadrDCAMaker::Ismuontrack(StPicoEvent* event, StPicoTrack* track)
{
  double pt;
  pt=track->gMom(event->primaryVertex(),event->bField()).perp();
  Int_t mtdpid=track->mtdPidTraitsIndex();
  if(mtdpid<=0)return false;
  StPicoMtdPidTraits* mtdpidtrait=(StPicoMtdPidTraits*) mPicoDst->mtdPidTraits(mtdpid);
  double mtddz=mtdpidtrait->deltaZ();
  double mtddt=mtdpidtrait->deltaTimeOfFlight();
  if(track->nSigmaPion()<3.0&&track->nSigmaPion()>-1.0&&pt>1.0&&fabs(mtddz)<20.0&&mtddt>-1.0&&mtddt<1.0) return true;
  else return false;
  
}

//----------------------------------------------------------------
Bool_t StPicoHadrDCAMaker::passEventCuts(StPicoEvent* event, int trig)
{
  Double_t vzvpd = event->vzVpd();
  Double_t vztpc = event->primaryVertex().z();
  Double_t dvz = vzvpd - vztpc;
  if(trig!=3&&fabs(vztpc) < vZcut[trig] && fabs(dvz) < dvZcut[trig]) return true;
  if(trig==3&&fabs(vztpc) < vZcut[trig] ) return true;
  else return false;
}
Bool_t StPicoHadrDCAMaker::pass_HFT_EventCuts(StPicoEvent* event, int trig)
{
  Double_t vzvpd = event->vzVpd();
  Double_t vztpc = event->primaryVertex().z();
  Double_t dvz = vzvpd - vztpc;
  if(trig!=3&&fabs(vztpc) < vZcutHFT[trig] && fabs(dvz) < dvZcutHFT[trig]) return true;
  if(trig==3&&fabs(vztpc) < vZcutHFT[trig] ) return true;
  else return false;
}


//----------------------------------------------------------------
Bool_t StPicoHadrDCAMaker::passEventCuts_NodVz(StPicoEvent* event, int trig)
{
  Double_t vzvpd = event->vzVpd();
  Double_t vztpc = event->primaryVertex().z();
  Double_t dvz = vzvpd - vztpc;
  if(fabs(vztpc) < vZcut[trig]) return true;
  else return false;
}

//---------------------------------------------------------------
Double_t StPicoHadrDCAMaker::RotatePhi(Double_t phi) const
{
  Double_t outPhi = phi;
  Double_t pi=TMath::Pi();
  while(outPhi<0) outPhi += 2*pi;
  while(outPhi>2*pi) outPhi -= 2*pi;
  return outPhi;
}

//===================================================================

void StPicoHadrDCAMaker::SetDefaultCuts()
{
  numTrigs = 4;
  setNSigECuts(-1.5,3.0);
  setNSigPCuts(-20,20);
  setNSigKCuts(-20,20);
  setNSigPiCuts(-20,20);
  setvZCuts(0,6.0 ,3);  // (vZ, delVz)
  setvZCuts(1,30.0,3.0); // (vZ, delVz)
  setvZCuts(2,30.0,3.0); // (vZ, delVz)
  setvZCuts(3,30.0,30.0); // (vZ, delVz)
  
  setvZCutsHFT(0,6.0,3.0);  // (vZ, delVz)
  setvZCutsHFT(1,6.0,3.0); // (vZ, delVz)
  setvZCutsHFT(2,6.0,3.0); // (vZ, delVz)
  setvZCutsHFT(3,6.0,30.0); // (vZ, delVz)
  setPrimaryPtCut(3.0, 1.5); // pT < 3 (TOF), pT >1.5 (BEMC)
  setPrimaryEtaCut(0.7); // |eta| < 1.0
  setPrimaryDCACut(1.5); // eDCA < 1.5 cm
  setNhitsCuts(15.,20.,0.52); // nHitsdEdx >= 15, nHitsFit >= 20, nHitsRatio >= 0.52
  setPoECut(0.3, 1.5); // 0.3 < p/E < 1.5
  setToFBetaCut(0.03); // |1/B -1| < 0.03
  setToFLocalyCut(1.8); // |tof_localy| < 1.8
  setKaonEnhCut(0.9,1.1); // 0.9<1/B<1.1 Kaon Species Select
  setPionEnhCut(0.9,1.1); // 0.9<1/B<1.1 Pion Species Select
  setProtonEnhCut(0.9,1.1); // 0.9<1/B<1.1 Proton Species Select
  setDsmAdcCut(0,0); // dsmADC cut sets (not in MB): Use getDsmAdcCut(trig) to return value
  setDsmAdcCut(1,15); // dsmADC cut sets ()
  setDsmAdcCut(2,18); // dsmADC cut sets ()
  setDsmAdcCut(3,25); // dsmADC cut sets ()
  setadc0Cut(0,0); // dsmADC cut sets (not in MB): Use getDsmAdcCut(trig) to return value
  setadc0Cut(1,15); // dsmADC cut sets ()
  setadc0Cut(2,18); // dsmADC cut sets ()
  setadc0Cut(3,25); // dsmADC cut sets ()
  setSMDCuts(0,0,3.,0.8); // nEta>=, nPhi>=, zDist<, phiDist<
  setSMDCuts2(1,1,3.,0.08); // nEta>=, nPhi>=, zDist<, phiDist<
}








