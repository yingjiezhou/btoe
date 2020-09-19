#include "StPicoQAMaker.h"
#include "StRoot/StPicoDstMaker/StPicoDst.h"
#include "StRoot/StPicoDstMaker/StPicoTrack.h"
#include "StRoot/StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StPicoDstMaker/StPicoEvent.h"
#include "StRoot/StPicoDstMaker/StPicoMtdHit.h"
#include "StRoot/StPicoDstMaker/StPicoConstants.h"
#include "StRoot/StPicoDstMaker/StPicoMtdPidTraits.h"
#include "StRoot/StPicoDstMaker/StPicoBTofPidTraits.h"
#include "StRoot/StPicoDstMaker/StPicoEmcPidTraits.h"
#include "StDcaGeometry.h"

#include "StThreeVectorF.hh"
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include <map>
#include <iostream>
#include <fstream>
#include "mBadRunList.h"

Bool_t fillhistflag=1;
ofstream runidfiles;
Int_t runIndex;
Int_t randomId;


ClassImp(StPicoQAMaker)
//-----------------------------------------------------------------------------
StPicoQAMaker::StPicoQAMaker(const char* name, StPicoDstMaker *picoMaker, const char* outName)
: StMaker(name)
{
  mPicoDstMaker = picoMaker;
  mPicoDst = NULL;
  TH1F:: SetDefaultSumw2();//zaochen add
  mOutName = outName;
  
  mNBadRuns = sizeof(mBadRuns)/sizeof(int);
  
}

//-----------------------------------------------------------------------------
Int_t StPicoQAMaker::Init() {
  if(mOutName!="") {
    fout = new TFile(mOutName.Data(),"RECREATE");
  }else{
    fout = new TFile("picoQA_test.root","RECREATE");
  }
  LOG_INFO<<"StPicoQAMaker::Init  mOutName = "<<mOutName.Data()<<endm;
  DeclareHistograms();
  
  if(fillhistflag){
    //read in the runlist.dat
    ifstream indata;
    indata.open("StRoot/StPicoQAMaker/mTotalRunList.dat");
    mTotalRunId.clear();
    if(indata.is_open()){
      cout<<"read in total run number list and record run number ...";
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
  }
  
  return kStOK;
}

//-----------------------------------------------------------------------------
Int_t StPicoQAMaker::Finish() {
  fout->cd();
  fout->Write();
  fout->Close();
  LOG_INFO<<"Histogram saved"<<endm;
  return kStOK;
}

//-----------------------------------------------------------------------------
void StPicoQAMaker::DeclareHistograms() {
  
  fout->cd();
  hNEvents   = new TH1F("hNEvents","number of events: 0 for total and 2 for MBs events", 10, 0, 10 );
  
  mNptracks    = new TH1F("Nptracks","#primary tracks",200,0,2000);
  mNgtracks    = new TH1F("Ngtracks","# global tracks ",200,0,5000);
  
  mtrketaphi  = new TH2F("trketaphi","the eta vs phi; phi; eta;",200,-0.5,6.5,200,-2,2);
  mtrketa_pt  = new TH2F("trketa_pt", "trketa_pt; pt; eta;", 200,0,20,200,-2,2);
  mtrkphi_pt  = new TH2F("trkphi_pt","trkphi_pt; pt; phi;",200,0,20,200,0,6.3);
  mtrketa_phiPos = new TH2F("trketa_phiPos","trketa_phi(Positive); phi; eta;",200,0,6.3,200,-2,2);
  mtrketa_phiNeg = new TH2F("trketa_phiNeg","trketa_phi(Negative); Phi; eta;",200,0,6.3,200,-2,2);
  // all hadron DCA, pt
  mtrkdca_pt     = new TH2F("trkdca_pt","trkdca_pt",200,0,20,250,0,10);
  mtrkdcaXY_pt     = new TH2F("trkdcaXY_pt","the dcaXY_PT; pt; dcaXY;",200,0,20,250,-10,10);
  mtrkdcaZ_pt      = new TH2F("trkdcaZ_pt","the dcaZ_PT; pt; dcaZ;",200,0,20,250,-10,10);
  
  mtrkdcawHFT_pt     = new TH2F("trkdcawHFT_pt","trkdcawHFT_pt",200,0,20,250,0,10);
  mtrkdcaXYwHFT_pt     = new TH2F("trkdcaXYwHFT_pt","dcaXYwHFT_PT; pt; dcaXY;",200,0,20,250,-10,10);
  mtrkdcaZwHFT_pt      = new TH2F("trkdcaZwHFT_pt","dcaZwHFT_PT; pt; dcaZ;",200,0,20,250,-10,10);
  // all pi,k,p, without PID
  mnsigmaPI_P   = new TH2F("nsigmaPI_P", "nsigmapion vs P of all tracks; P; nsigmaPI;",200,0,20,100,-20,20);
  mnsigmaP_P   = new TH2F("nsigmaP_P", "nsigmaproton vs P of all tracks; P; nsigmaP;",200,0,20,100,-20,20);
  mnsigmaK_P   = new TH2F("nsigmaK_P", "nsigmaK vs P of all tracks; P; nsigmaK;",200,0,20,100,-20,20);
  mnsigmaE_P   = new TH2F("nsigmaE_P", "nsigmaE vs P of all tracks; P; nsigmaE;",200,0,20,100,-20,20);
  
  minvsBeta_P  = new TH2F("invsBeta_P","1/Beta VS momentum; P; 1/beta;",300,0,6,200,0.90,1.12);
  
  //after pid QA , we can get pi,k,p, zyj need to change
  htofPiondcavsPT = new TH2F("htofPiondcavsPT","tofPiondca vs PT;pt(GeV/c); Piondca(cm);",200,0,20,250,0,10);
  htofKaondcavsPT = new TH2F("htofKaondcavsPT","tofKaondca vs PT;pt(GeV/c); Kaondca(cm);",200,0,20,250,0,10);
  htofProtondcavsPT  = new TH2F("htofProtondcavsPT","tofProtondca vs PT;pt(GeV/c); Protondca(cm);",200,0,20,250,0,10);
  
  //after pid QA pi,k,p-----wHFT----
  htofPiondcawHFTvsPT = new TH2F("htofPiondcawHFTvsPT","tofPiondcawHFT vs PT;pt(GeV/c); Piondca(cm);",200,0,20,250,0,3);
  htofKaondcawHFTvsPT = new TH2F("htofKaondcawHFTvsPT","tofKaondcawHFT vs PT;pt(GeV/c); Kaondca(cm);",200,0,20,250,0,3);
  htofProtondcawHFTvsPT  = new TH2F("htofProtondcawHFTvsPT","tofProtondcawHFTvsPT;pt(GeV/c); Protondca(cm);",200,0,20,250,0,3);
  
  //---only tpc pid----pi/k/p----------
  htpcPiondcavsPT = new TH2F("htpcPiondcavsPT","Piondca vs PT (|n#sigma_{#pi}|<2);pt(GeV/c); Piondca(cm);",200,0,20,250,0,3);
  htpcKaondcavsPT = new TH2F("htpcKaondcavsPT","Kaondca vs PT (|n#sigma_{k}|<2);pt(GeV/c); Kaondca(cm);",200,0,20,250,0,3);
  htpcProtondcavsPT = new TH2F("htpcProtondcavsPT","Protondca vs PT (|n#sigma_{p}|<2);pt(GeV/c); Protondca(cm);",200,0,20,250,0,3);
  
  //--- tpc pid + tof----pi/k/p------pt<2----
  htpctofPiondcavsPT = new TH2F("htpctofPiondcavsPT","PiondcavsPT (|n#sigma_{#pi}|<2&tofm2);pt(GeV/c); Piondca(cm);",200,0,20,250,0,10);
  htpctofKaondcavsPT = new TH2F("htpctofKaondcavsPT","KdcavsPT (|n#sigma_{k}|<2&tofm2);pt(GeV/c); Kaondca(cm);",200,0,20,250,0,10);
  htpctofProtondcavsPT = new TH2F("htpctofProtondcavsPT","PdcavsPT (|n#sigma_{p}|<2&tofm2);pt(GeV/c); Protondca(cm);",200,0,20,250,0,10);
  
  //---only tpc pid----pi/k/p---wHFT-------
  htpcPiondcawHFTvsPT = new TH2F("htpcPiondcawHFTvsPT","PiondcawHFT vs PT (|n#sigma_{#pi}|<2);pt(GeV/c); PiondcawHFT(cm);",200,0,20,250,0,10);
  htpcKaondcawHFTvsPT = new TH2F("htpcKaondcawHFTvsPT","KaondcawHFT vs PT (|n#sigma_{k}|<2);pt(GeV/c); KaondcawHFT(cm);",200,0,20,250,0,10);
  htpcProtondcawHFTvsPT = new TH2F("htpcProtondcawHFTvsPT","ProtondcawHFT vs PT (|n#sigma_{p}|<2);pt(GeV/c); Protondca(cm);",200,0,20,250,0,10);
  
  //--- tpc pid + tof----pi/k/p----wHFT--pt<2----
  htpctofPiondcawHFTvsPT = new TH2F("htpctofPiondcawHFTvsPT","PiondcawHFTvsPT (|n#sigma_{#pi}|<2&tofm2);pt(GeV/c); Piondca(cm);",200,0,20,250,0,3);
  htpctofKaondcawHFTvsPT = new TH2F("htpctofKaondcawHFTvsPT","KdcawHFTvsPT (|n#sigma_{k}|<2&tofm2);pt(GeV/c); Kaondca(cm);",200,0,20,250,0,3);
  htpctofProtondcawHFTvsPT = new TH2F("htpctofProtondcawHFTvsPT","PdcawHFTvsPT (|n#sigma_{p}|<2&tofm2);pt(GeV/c); Protondca(cm);",200,0,20,250,0,3);
}// er chen

//-----------------------------------------------------------------------------
void StPicoQAMaker::Clear(Option_t *opt) {
  
  return StMaker::Clear(opt);
}

//-----------------------------------------------------------------------------
Int_t StPicoQAMaker::Make() {
  
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
  //=================zaochen add====================
  hNEvents->Fill(0);
  if(!event) return kStOK;
  //=================event selection================
  int runId = mPicoDst->event()->runId();
  for(int i=0;i<mNBadRuns;i++){
    if(runId==mBadRuns[i]) return kStOK;
  }

  hNEvents->Fill(2);

  if(fillhistflag){
    Int_t RUNID = mPicoDst->event()->runId();
    map<Int_t, Int_t>::iterator iter = mTotalRunId.find(RUNID);
    if(iter != mTotalRunId.end())
      runIndex = iter->second;
    else{
      runIndex = -1;
      cout<<"sorry, no runNumber in runNumber list"<<endl;
      cout<<"the RUNID:="<<RUNID<<endl;
    }

    if(runIndex<0)return kStOK;

  }

  //---------------event information----------------------------

  Double_t vzvpd=mPicoDst->event()->vzVpd();
  Double_t vztpc=mPicoDst->event()->primaryVertex().z();
  Double_t vxtpc=mPicoDst->event()->primaryVertex().x();
  Double_t vytpc=mPicoDst->event()->primaryVertex().y();
  Double_t dvz=vztpc-vzvpd;
  Double_t vr=sqrt(vxtpc*vxtpc+vytpc*vytpc);
  if(fabs(vxtpc)<1.0e-5)return kStOK;
  if(fabs(vytpc)<1.0e-5)return kStOK;
  if(fabs(vztpc)<1.0e-5)return kStOK;
  
  Int_t Ntofmatch = mPicoDst->event()->nBTOFMatch();
  //----------track information------------------------
  
  Int_t numberoftracks = mPicoDst->numberOfTracks();
  
  StThreeVectorF vertexPos;
  vertexPos = mPicoDst->event()->primaryVertex();
  
  Int_t Nprimarytracks=0;
  Int_t ntofmatchcount=0;
  Int_t nmtdmatchcount=0;
  Int_t nbemcmatchcount=0;
  Int_t nhftmatchcount=0;
  Int_t nmuons=0;
  Int_t ntofelecton=0;
  Int_t nbemcelectron=0;
  Float_t particleM[3]={0.938,0.140,0.494};
  for(int i=0; i<numberoftracks; i++){
    StPicoTrack* track=(StPicoTrack*) mPicoDst->track(i);
    StPhysicalHelixD helix = track->helix();
    
    StThreeVectorF dcaPoint = helix.at( helix.pathLength(vertexPos.x(), vertexPos.y())  );
    double dcamag= (dcaPoint-vertexPos).mag();
    StThreeVectorF dcaP = helix.momentumAt( vertexPos.x(),vertexPos.y() );
    double dcaXY= ( (dcaPoint-vertexPos).x()*dcaP.y()-(dcaPoint-vertexPos).y()*dcaP.x() )/dcaP.perp();
    double dcaZ= dcaPoint.z() - vertexPos.z();
    
    Double_t meta,mpt,mphi,mcharge,mdedx;
    //change to global track
    meta=track->pMom().pseudoRapidity();
    if(track->pMom().mag()!=0) Nprimarytracks++;
    mphi=RotatePhi(track->pMom().phi());
    mpt=track->pMom().perp();
    mcharge=track->charge();
    mdedx=track->dEdx();
    if(mcharge==0||meta==0||mphi==0||mdedx==0)continue;
    if(track->isHFTTrack()){
      nhftmatchcount++;
    }
    
    Float_t mmomentum=track->pMom().mag();
    Double_t rationhits = 0.00;
    rationhits=(double)track->nHitsFit()/track->nHitsMax();
    
    Double_t nsigpi=track->nSigmaPion();
    Double_t nsigk=track->nSigmaKaon();
    Double_t nsigp=track->nSigmaProton();
    mtrketaphi->Fill( mphi,meta );
    
    if(fillhistflag){
      
      //tpc pid on pi, k, p
      if(fabs(nsigpi)<2.0) htpcPiondcavsPT->Fill(mpt,dcamag);
      if(fabs(nsigk)<2.0)  htpcKaondcavsPT->Fill(mpt,dcamag);
      if(fabs(nsigp)<2.0)  htpcProtondcavsPT->Fill(mpt,dcamag);
      //tpc pid on pi, k, p---wHFT
      if(track->isHFTTrack()){ // I will use this infromation zyj
        if(fabs(nsigpi)<2.0) htpcPiondcawHFTvsPT->Fill(mpt,dcamag);
        if(fabs(nsigk)<2.0)  htpcKaondcawHFTvsPT->Fill(mpt,dcamag);
        if(fabs(nsigp)<2.0)  htpcProtondcawHFTvsPT->Fill(mpt,dcamag);
      }
      
      // zyj for all hadron
      mtrketa_pt->Fill(mpt*mcharge,meta);
      mtrkphi_pt->Fill(mpt*mcharge,mphi);
      if(mcharge>0)mtrketa_phiPos->Fill(mphi,meta);
      if(mcharge<0)mtrketa_phiNeg->Fill(mphi,meta);
      
      mtrkdca_pt->Fill(mpt, dcamag);
      mtrkdcaZ_pt->Fill(mpt,dcaZ);
      mtrkdcaXY_pt->Fill(mpt,dcaXY);
      
      if(track->isHFTTrack()){
        mtrkdcawHFT_pt->Fill(mpt, dcamag);
        mtrkdcaZwHFT_pt->Fill(mpt,dcaZ);
        mtrkdcaXYwHFT_pt->Fill(mpt,dcaXY);
      }
      mdedx_P->Fill(mmomentum*mcharge,track->dEdx());
      
      mnsigmaPI_P->Fill(mmomentum,track->nSigmaPion());
      mnsigmaP_P->Fill(mmomentum,track->nSigmaProton());
      mnsigmaE_P->Fill(mmomentum,track->nSigmaElectron());
      mnsigmaK_P->Fill(mmomentum,track->nSigmaKaon());
    }//
    
    Int_t tofpidid=track->bTofPidTraitsIndex();
    if(tofpidid>0){
      ntofmatchcount++;
      StPicoBTofPidTraits* btofpidtrait=(StPicoBTofPidTraits*) mPicoDst->btofPidTraits(tofpidid);
      
      //------tof information start----------
      Float_t tofbeta=btofpidtrait->btofBeta();
      
      Int_t tofcellid=   btofpidtrait->btofCellId();
      Int_t toftray= (int)tofcellid/192 + 1;
      Int_t tofmodule= (int)((tofcellid%192)/6.)+1;
      
      Float_t toflocaly = btofpidtrait->btofYLocal();
      Float_t toflocalz = btofpidtrait->btofZLocal();
      
      double mnsigE=track->nSigmaElectron();
      
      if(fillhistflag){
        //mpt>0.2&&mpt<2
        if( mpt>0.2){
          
          //pi----k----p----
          if(tofbeta>0){
            double tofm2=mmomentum*mmomentum*( 1.0/(tofbeta*tofbeta)-1.0);
            
            if( fabs(tofm2-particleM[0]*particleM[0])<0.05 ){
              htofProtondcavsPT->Fill(mpt,dcamag);
              if(track->isHFTTrack()){
                htofProtondcawHFTvsPT->Fill(mpt,dcamag);
              }
              
              if(abs(nsigp)<2.0){
                htpctofProtondcavsPT->Fill(mpt,dcamag);
                if(track->isHFTTrack()) {
                  htpctofProtondcawHFTvsPT->Fill(mpt,dcamag);
                }
              }
            }//p
            
            if( fabs(tofm2-particleM[1]*particleM[1])<0.01 ){
              htofPiondcavsPT->Fill(mpt, dcamag);
              
              if(track->isHFTTrack()){
                htofPiondcawHFTvsPT->Fill(mpt,dcamag);
              }
              
              if(fabs(nsigpi)<2.0){
                htpctofPiondcavsPT->Fill(mpt,dcamag);
                if(track->isHFTTrack()){
                  htpctofPiondcawHFTvsPT->Fill(mpt,dcamag);
                }
              }
            }//pion
            
            if( fabs(tofm2-particleM[2]*particleM[2])<0.02 ){
              htofKaondcavsPT->Fill(mpt, dcamag);
              
              if(track->isHFTTrack()){
                htofKaondcawHFTvsPT->Fill(mpt,dcamag);
              }
              
              if( fabs(nsigk)<2.0 ) {
                htpctofKaondcavsPT->Fill(mpt, dcamag);
                if(track->isHFTTrack()){
                  htpctofKaondcawHFTvsPT->Fill(mpt,dcamag);
                }
                
              }
            }//kaon
            
          }
          
        }
        
      }//if fill hist
      
    }//-------tof information end
    
  }//loop of all tracks
  return kStOK;
}//end of main fucntion


//-------------------------------------------------------------

Bool_t StPicoQAMaker::Isgoodtrack(StPicoTrack* track)
{
  double pt,eta,fithitsfrac=0.,chargeq;
  pt=track->pMom().perp();
  eta=track->pMom().pseudoRapidity();
  fithitsfrac=(track->nHitsFit())/45.0;
  chargeq=track->charge();
  if(pt>0.2&&fabs(eta)<1.0&&track->nHitsFit()>=15&&track->nHitsDedx()>=10&&fithitsfrac>0.52&&fabs(chargeq)>0 ) return true;
  else return false;
  
}
//-------------------------------------------------------------
Bool_t StPicoQAMaker::Ismuontrack(StPicoTrack* track)
{
  double pt;
  pt=track->pMom().perp();
  Int_t mtdpid=track->mtdPidTraitsIndex();
  if(mtdpid<=0)return false;
  StPicoMtdPidTraits* mtdpidtrait=(StPicoMtdPidTraits*) mPicoDst->mtdPidTraits(mtdpid);
  double mtddz=mtdpidtrait->deltaZ();
  double mtddt=mtdpidtrait->deltaTimeOfFlight();
  if(track->nSigmaPion()<3.0&&track->nSigmaPion()>-1.0&&pt>1.0&&fabs(mtddz)<20.0&&mtddt>-1.0&&mtddt<1.0) return true;
  else return false;
  
}

//----------------------------------------------------------------
Bool_t StPicoQAMaker::Ispasseventcuts(StPicoEvent* event)
{
  double vzTPC=event->primaryVertex().z();
  if(fabs(vzTPC)<40)return true;
  else return false;
}

//---------------------------------------------------------------
Double_t StPicoQAMaker::RotatePhi(Double_t phi) const
{
  Double_t outPhi = phi;
  Double_t pi=TMath::Pi();
  while(outPhi<0) outPhi += 2*pi;
  while(outPhi>2*pi) outPhi -= 2*pi;
  return outPhi;
}

