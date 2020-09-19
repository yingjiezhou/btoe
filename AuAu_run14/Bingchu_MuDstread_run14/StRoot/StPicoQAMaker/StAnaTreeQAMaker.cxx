#include "StAnaTreeQAMaker.h"
#include "StRoot/StPicoAnaTreeMaker/StAnaTree.h"
#include "StRoot/StPicoAnaTreeMaker/StPicoAnaTreeMaker.h"
#include "StRoot/StPicoAnaTreeMaker/StEventHeader.h"
#include "StRoot/StPicoAnaTreeMaker/StElectronTrack.h"
#include "StRoot/StPicoAnaTreeMaker/StPartElectronTrack.h"
#include "StRoot/StPicoAnaTreeMaker/StPhoEEPair.h"
#include "StRoot/StPicoAnaTreeMaker/StMuonTrack.h"
#include "StRoot/StPicoAnaTreeMaker/StEEPair.h"
#include "StRoot/StPicoAnaTreeMaker/StEMuPair.h"
#include "StRoot/StPicoAnaTreeMaker/StMuMuPair.h"
#include "StRoot/StPicoAnaTreeMaker/StEmcTrigger.h"
#include "StRoot/StPicoAnaTreeMaker/StHadronTrack.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StThreeVectorF.hh"
//#include "StLorentzVectorF.hh"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TF1.h"
#include "TFile.h""
#include "TRandom3.h"
#include "TLorentzVector.h"
#include "mBadRunList.h"
#include <map>
#include <iostream>
#include <fstream>

Bool_t fillhistflag=1;
ofstream runidfiles;
Int_t runIndex;
Int_t randomId;


ClassImp(StAnaTreeQAMaker)
  //-----------------------------------------------------------------------------
  StAnaTreeQAMaker::StAnaTreeQAMaker(const char* name, StPicoAnaTreeMaker *treeMaker, const char* outName)
: StMaker(name)
{
  mPicoAnaTreeMaker = treeMaker;
  mAnaTree = 0;
  TH1F:: SetDefaultSumw2();//zaochen add
  mOutName = outName;
  mTotalRun = 1000;

  mNBadRuns = sizeof(mBadRuns_HT)/sizeof(int);
  mRunFileName = "StRoot/StAnaTreeQAMaker/mTotalRunList.dat";

}

//----------------------------------------------------------------------------- 
Int_t StAnaTreeQAMaker::Init() {
  if(mOutName!="") {
    fout = new TFile(mOutName.Data(),"RECREATE");
  }else{
    fout = new TFile("picoQA_test.root","RECREATE");
  }
  LOG_INFO<<"StAnaTreeQAMaker::Init  mOutName = "<<mOutName.Data()<<endm;
  DeclareHistograms();

  if(fillhistflag){
    //read in the runlist.dat
    ifstream indata;
    indata.open(mRunFileName);
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

    for(int q=0; q<mTotalRun; q++)
    {
      avgZDC.push_back(0);
      avgRefMult.push_back(0);
      avgZDCCount.push_back(0);
      avgRefMultCount.push_back(0);
    }  

    refMvsZDCFit = new TF1("refMvsZDCFit","pol2",0,40000);
    double par[3] = {12.13, 0.0002893, -5.567e-09};
    refMvsZDCFit->SetParameters(par);
  }//

  return kStOK;
}

//----------------------------------------------------------------------------- 
Int_t StAnaTreeQAMaker::Finish() {

  for(int rI=0; rI < mTotalRun; rI++)
  {
    float zdcAv = avgZDC[rI]/avgZDCCount[rI];
    float grefMultAv = avgRefMult[rI]/avgRefMultCount[rI];
    float grefDivZdc = (grefMultAv/zdcAv)*1e3;
    hgRefMultvsZDCx->Fill(zdcAv,grefMultAv);
    double fval = refMvsZDCFit->Eval(zdcAv);
    hgRefMultZDCvsRunIndex->Fill(rI,grefMultAv-fval);
  }
  
  fout->cd();
  fout->Write();
  fout->Close();
  LOG_INFO<<"Histogram saved"<<endm;
  return kStOK;

}

//-----------------------------------------------------------------------------
void StAnaTreeQAMaker::DeclareHistograms() {

  fout->cd();
  hNEvents   = new TH1F("hNEvents","number of events: 0 for total and 2 for HT events", 10, 0, 10 );
  //htriggerindex =new TH1F("htriggerindex","triggerindex", 64,0,64);
  mVz_vpd     = new TH1F("vz_vpd", "VZ_VPD distribution (cm)",400,-200,200);
  mVz_tpc     = new TH1F("vz_tpc","the Vz_TPC distribution (cm) ",400,-200,200);
  mVz_vpdtpc  = new TH2F("Vz_vpdtpc","VertexZ: VPD VS TPC;TPC;VPD;", 400,-200,200,400,-200,200);
  mdVz        = new TH1F("dVz", "VertexZ 'TPC-VPD' (cm)", 400,-200,200);
  mdVz_tpcVz  = new TH2F("dVz_tpcVz","VertexZ 'TPC-VPD vs TPC' (cm);VZtpc; VZ(tpc-vpd)",400,-200,200,200,-100,100);
  mVxy        = new TH2F("vxy","Vertex: Vy Vs Vx distribution (cm);vx;vy; ",200,-10,10,200,-10,10);
  mVRvsVZ    = new TH2F("VRvsVZ","Vertex: VR vs VZ  (cm);VZ;VR; ", 400, -200, 200,200,0,20);

  mRanking_nPtrks=new TH2F("Ranking_nPtrks","Ranking Vs nPrimaryTracks;nprimarytrks; ranking;",200,0,2000,100,-10,10);
  mnPtrks_nGtrks=new TH2F("nPtrks_nGtrks","nPrimarytrks_nGlobaltrks;nglobaltrks;nprimarytrks;",500,0,5000,200,0,2000);

  mnRefMult_nGRefMult=new TH2F("nRefMult_nGRefMult","nRefMult_nGRefMult;nGRefMult;nRefmult;",200,0,1000,200,0,1000);
  mnRefMult_nPtrks=new TH2F("nRefMult_nPtrks","nRefMult_nPrimarytrks;nprimarytrks;nRefmult;",200,0,2000,200,0,1000);
  mnRefMult_nGtrks=new TH2F("nRefMult_nGtrks","nRefMult_nGlobaltrks;nglobaltrks;nRefmult;",250,0,5000,200,0,1000);

  mnGRefMult_nPtrks=new TH2F("nGRefMult_nPtrks","nGRefMult_nPrimarytrks;nprimarytrks;nGRefmult;",200,0,2000,200,0,1000);
  mnGRefMult_nGtrks=new TH2F("nGRefMult_nGtrks","nGRefMult_nGlobaltrks;nglobaltrks;nGRefmult;",250,0,5000,200,0,1000);

  mnPtrks_nTofHits=new TH2F("nPtrks_nTofHits","nPrimarytrks_nTofHits;ntofhits;nprimarytrks;",250,0,2000,200,0,2000);
  mnPtrks_nMtdHits=new TH2F("nPtrks_nMtdHits","nPrimarytrks_nMtdHits;nmtdhits;nprimarytrks;",50,0,50,500,0,2000);
  mnTofHits_nMtdHits=new TH2F("nTofHits_nMtdHits","nTofHits_nMtdHits;nmtdhits;ntofhits;",50,0,50,200,0,2000);
  mnTofMatch_nTofHits=new TH2F("nTofMatch_nTofHits","nTofMatch_nTofHits;ntofhits;ntofmatch;",300,0,1500,300,0,1500);

  mnhitsfit_pt   = new TH2F("nhitsfit_pt","nhitsfit_pt; pt; nhitsfit;",200,0,20,50,0,50);
  mnhitsRatio_pt = new TH2F("nhitsRatio_pt","nhitsRatio_pt; pt; nhitsRatio;",200,0,20,100,0,1.2);
  mnhitsdedx_pt  = new TH2F("nhitsdedx_pt","nhitsdedx_pt; pt; nhitsdedx;",200,0,20,50,0,50);

  mnhitsfit   = new TH1F("nhitsfit", "nhitsfit ",50,0,50);
  mnhitsfitRatio   = new TH1F("nhitsfitRatio", "nhitsfitRatio ",100,0,1.0);
  mnhitsdedx  = new TH1F("nhitsdedx", "nhitsfitdedx",50,0,50);

  mtrketaphi  = new TH2F("trketaphi","the eta vs phi; phi; eta;",200,-0.5,6.5,200,-2,2);     
  mtrketa_pt  = new TH2F("trketa_pt", "trketa_pt; pt; eta;", 200,0,20,200,-2,2);
  mtrkphi_pt  = new TH2F("trkphi_pt","trkphi_pt; pt; phi;",200,0,20,200,0,6.3);
  mtrketa_phiPos = new TH2F("trketa_phiPos","trketa_phi(Positive); phi; eta;",200,0,6.3,200,-2,2);
  mtrketa_phiNeg = new TH2F("trketa_phiNeg","trketa_phi(Negative); Phi; eta;",200,0,6.3,200,-2,2);

  mtrkpt      = new TH1F("trkpt","the pt distribution of all tracks",200,0,20);
  mtrketa     = new TH1F("trketa","eta ",200,-2,2);
  mtrkphi     = new TH1F("trkphi","the phi distribution of all tracks",200,0,6.3);

  mtrkdca_pt     = new TH2F("trkdca_pt","trkdca_pt",200,0,20,250,0,10);
  mtrkdcaXY_pt     = new TH2F("trkdcaXY_pt","the dcaXY_PT; pt; dcaXY;",200,0,20,250,-10,10);
  mtrkdcaZ_pt      = new TH2F("trkdcaZ_pt","the dcaZ_PT; pt; dcaZ;",200,0,20,250,-10,10);

  mtrkdca     = new TH1F("trkdca","the dca of all tracks",500,0,10);
  mtrkdcaXY     = new TH1F("trkdcaXY","the dcaXY of all tracks",500,-10,10);
  mtrkdcaZ     = new TH1F("trkdcaZ","the dcaZ of all tracks",500,-10,10);

  mnsigmaPI_P   = new TH2F("nsigmaPI_P", "nsigmapion vs P of all tracks; P; nsigmaPI;",200,0,20,100,-20,20);
  mnsigmaK_P   = new TH2F("nsigmaK_P", "nsigmaK vs P of all tracks; P; nsigmaK;",200,0,20,100,-20,20);
  mnsigmaE_P   = new TH2F("nsigmaE_P", "nsigmaE vs P of all tracks; P; nsigmaE;",200,0,20,100,-20,20);

  mnsigmaPI   = new TH1F("nsigmaPI", "nsigmapion of all tracks",50,-15,15);
  mnsigmaK    = new TH1F("nsigmaK", "nsigmaKaon of all tracks",50,-15,15);
  mnsigmaE    = new TH1F("nsigmaE", "nsigmaElectron of all tracks",50,-15,15);

  minvsBeta_P  = new TH2F("invsBeta_P","1/Beta VS momentum; P; 1/beta;",300,0,6,200,0.90,1.12);
  mtofM2_P     = new TH2F("tofM2_P", "tofM2 VS momentum; P; tofM2;",200,0,20,200,-0.5,4.5);

  //--bemc-----
  mbTowId_P= new TH2F("bTowId_P","bTowId_P; p (GeV/c); BEMC btowId;",200,0,20,200,-100,5000);
  mBEMCadc0_P= new TH2F("BEMCadc0_P","BEMCadc0_P; p (GeV/c); BEMCadc0;",200,0,20,200,0,2000);
  mBEMCzdist_P= new TH2F("BEMCzdist_P","BEMCzdist_P; p (GeV/c); BEMCzdist (cm);",200,0,20,200,-30,30);
  mBEMCphidist_P= new TH2F("BEMCphidist_P","BEMCphidist_P;p (GeV/c); phidist;",200,0,20,200,-0.2,0.2);
  mBEMCneta_P= new TH2F("BEMCneta_P","BEMCneta_P;p (GeV/c); neta;",200,0,20,10,0,10);
  mBEMCnphi_P= new TH2F("BEMCnphi_P","BEMCnphi_P;p (GeV/c); nphi;",200,0,20,10,0,10);
  mBEMCneta_nphi= new TH2F("BEMCneta_nphi","BEMCneta_nphi;neta;nphi;",10,0,4,10,0,4);

  //run by run QA
  hTPCVxvsRunIndex = new TH2F("hTPCVxvsRunIndex","hTPCVxvsRunIndex;runIndex;TPC Vx (cm)",mTotalRun,0,mTotalRun,100,-10,10);
  hTPCVyvsRunIndex = new TH2F("hTPCVYvsRunIndex","hTPCVYvsRunIndex;runIndex;TPC VY (cm)",mTotalRun,0,mTotalRun,100,-10,10);
  hTPCVzvsRunIndex = new TH2F("hTPCVzvsRunIndex","hTPCVzvsRunIndex;runIndex;TPC Vz (cm)",mTotalRun,0,mTotalRun,400,-50,50);
  hVPDVzvsRunIndex = new TH2F("hVPDVzvsRunIndex","hVPDVzvsRunIndex;runIndex;VPD Vz (cm)",mTotalRun,0,mTotalRun,400,-50,50);
  hDeltaZvsRunIndex = new TH2F("hDeltaZvsRunIndex","hDeltaZvsRunIndex;runIndex; Vz_{TPC} - Vz_{VPD} (cm)",mTotalRun,0,mTotalRun,200,-10,10);     

  hRefMultvsRunIndex = new TH2F("hRefMultvsRunIndex","hRefMultvsRunIndex;runIndex; refMult",mTotalRun,0,mTotalRun,200,0,500);
  hGRefMultvsRunIndex = new TH2F("hGRefMultvsRunIndex","hGRefMultvsRunIndex;runIndex; GrefMult",mTotalRun,0,mTotalRun,200,0,500);
  //  hRefMultCorrvsRunIndex = new TH2F("hRefMultCorrvsRunIndex","hRefMultCorrvsRunIndex;runIndex; refMultCorr",mTotalRun,0,mTotalRun,200,0,1000);
  hnPrimaryvsRunIndex = new TH2F("hnPrimaryvsRunIndex","hnPrimaryvsRunIndex;runIndex; nPrimary",mTotalRun,0,mTotalRun,300,0,1200);
  hnGlobalvsRunIndex = new TH2F("hnGlobalvsRunIndex","hnGlobalvsRunIndex;runIndex; nGlobal",mTotalRun,0,mTotalRun,400,0,4000);

  hZDCXvsRunIndex = new TH2F("hZDCXvsRunIndex","hZDCXvsRunIndex;runIndex;zdcRate (KHz)",mTotalRun,0,mTotalRun,200,0.,60);
  hBBCXvsRunIndex = new TH2F("hBBCXvsRunIndex","hBBCXvsRunIndex;runIndex;bbcRate (KHz)",mTotalRun,0,mTotalRun,200,0,60);

  hnhitsfitvsRunIndex = new TH2F("hnhitsfitvsRunIndex","hhitsfitvsRunIndex;runIndex;nhitsfit",mTotalRun,0,mTotalRun,50,0,50);
  hnhitsdedxvsRunIndex = new TH2F("hnhitsdedxvsRunIndex","hhitsdedxvsRunIndex;runIndex;nhitsdedx",mTotalRun,0,mTotalRun,50,0,50);

  hPtvsRunIndex = new TH2F("hPtvsRunIndex","hPtvsRunIndex;runIndex;p_{T} (GeV/c)",mTotalRun,0,mTotalRun,100,0,10);
  hEtavsRunIndex = new TH2F("hEtavsRunIndex","hEtavsRunIndex;runIndex;#eta",mTotalRun,0,mTotalRun,200,-2,2);
  hPhivsRunIndex = new TH2F("hPhivsRunIndex","hPhivsRunIndex;runIndex;#phi",mTotalRun,0,mTotalRun,360,0,2*TMath::Pi());     
  hDedxvsRunIndex = new TH2F("hDedxvsRunIndex","hDedxvsRunIndex;runIndex;dE/dx (KeV/cm)",mTotalRun,0,mTotalRun,200,0,10);  

  hNSigmaEvsRunIndex = new TH2F("hNSigmaEvsRunIndex","hNSigmaEvsRunIndex;runIndex;n#sigma_{e}",mTotalRun,0,mTotalRun,600,-30-1.e-6,30-1.e-6);
  hNSigmaPivsRunIndex = new TH2F("hNSigmaPivsRunIndex","hNSigmaPivsRunIndex;runIndex;n#sigma_{#pi}",mTotalRun,0,mTotalRun,600,-30-1.e-6,30-1.e-6);
  hNSigmaKvsRunIndex = new TH2F("hNSigmaKvsRunIndex","hNSigmaKvsRunIndex;runIndex;n#sigma_{k}",mTotalRun,0,mTotalRun,600,-30-1.e-6,30-1.e-6);
  hNSigmaPvsRunIndex = new TH2F("hNSigmaPvsRunIndex","hNSigmaPvsRunIndex;runIndex;n#sigma_{p}",mTotalRun,0,mTotalRun,600,-30-1.e-6,30-1.e-6);

  hntofmatchvsRunIndex = new TH2F("hntofmatchvsRunIndex","hntofmatchvsRunIndex;runIndex; ntofmatch",mTotalRun,0,mTotalRun,200,0,1000);
  hnmtdmatchvsRunIndex = new TH2F("hnmtdmatchvsRunIndex","hnmtdmatchvsRunIndex;runIndex; nmtdmatch",mTotalRun,0,mTotalRun,20,0,20);
  hnmtdhitsvsRunIndex = new TH2F("hnmtdhitsvsRunIndex","hnmtdhitsvsRunIndex;runIndex; nmtdhits",mTotalRun,0,mTotalRun,50,0,50);
  hnhftmatchvsRunIndex = new TH2F("hnhftmatchvsRunIndex","hnhftmatchvsRunIndex;runIndex; nhftmatch",mTotalRun,0,mTotalRun,200,0,500);

  hntofmatchOVnGRvsRunIndex = new TH2F("hntofmatchOVnGRvsRunIndex","hntofmatchOVnGRvsRunIndex;runIndex; ntofmatch/nGreff",mTotalRun,0,mTotalRun,200,0,1);
  hnbemcmatchOVnGRvsRunIndex = new TH2F("hnbemcmatchOVnGRvsRunIndex","hnbemcmatchOVnGRvsRunIndex;runIndex; nbemcmatch/nGreff",mTotalRun,0,mTotalRun,200,0,1);
  hnmtdhitsOVnGRvsRunIndex = new TH2F("hnmtdhitsOVnGRvsRunIndex","hnmtdhits/NGtrks vsRunIndex;runIndex; nmtdhits/nGreff",mTotalRun,0,mTotalRun,100,0,1);
  hnmtdmatchOVnGRvsRunIndex = new TH2F("hnmtdmatchOVnGRvsRunIndex","hnmtdmatchOVnGRvsRunIndex;runIndex; nmtdmatch/nGreff",mTotalRun,0,mTotalRun,100,0,1);
  hnhftmatchOVnGRvsRunIndex = new TH2F("hnhftmatchOVnGRvsRunIndex","hnhftmatchOVnGRvsRunIndex;runIndex; nhftmatch/nGreff",mTotalRun,0,mTotalRun,200,0,1);

  hntofmatchOVnRvsRunIndex = new TH2F("hntofmatchOVnRvsRunIndex","hntofmatchOVnRvsRunIndex;runIndex; ntofmatch/nReff",mTotalRun,0,mTotalRun,200,0,1);
  hnmtdhitsOVnRvsRunIndex = new TH2F("hnmtdhitsOVnRvsRunIndex","hnmtdhits/NPtrks vsRunIndex;runIndex; nmtdhits/nReffs",mTotalRun,0,mTotalRun,100,0,1);
  hnmtdmatchOVnRvsRunIndex = new TH2F("hnmtdmatchOVnRvsRunIndex","hnmtdmatchOVnRvsRunIndex;runIndex; nmtdmatch/nReff",mTotalRun,0,mTotalRun,100,0,1);
  hnhftmatchOVnRvsRunIndex = new TH2F("hnhftmatchOVnRvsRunIndex","hnhftmatchOVnRvsRunIndex;runIndex; nhftmatch/nReff",mTotalRun,0,mTotalRun,100,0,1);

  hNtofElectronvsRunIndex = new TH2F("hNtofElectronvsRunIndex","hNtofElectronvsRunIndex;runIndex; Ntofelectron",mTotalRun,0,mTotalRun,100,0,30);
  hNbemcElectronvsRunIndex = new TH2F("hNbemcElectronvsRunIndex","hNbemcElectronvsRunIndex;runIndex; Nbemcelectron",mTotalRun,0,mTotalRun,100,0,30);
  hNmuonvsRunIndex = new TH2F("hNmuonvsRunIndex","hNmuonvsRunIndex;runIndex; n#muon",mTotalRun,0,mTotalRun,10,0,10);
  hNtofElectronOVnGRvsRunIndex = new TH2F("hNtofElectronOVnGRvsRunIndex","hNtofElectronOVnGRvsRunIndex;runIndex; Ntofelectron/nGreff",mTotalRun,0,mTotalRun,100,0,1);
  hNbemcElectronOVnGRvsRunIndex = new TH2F("hNbemcElectronOVnGRvsRunIndex","hNbemcElectronOVnGRvsRunIndex;runIndex; Nbemcelectron/nGreff",mTotalRun,0,mTotalRun,100,0,1);
  hNmuonOVnGRvsRunIndex = new TH2F("hNmuonOVnGRvsRunIndex","hNmuonOVnGRvsRunIndex;runIndex; n#muon/nGreff",mTotalRun,0,mTotalRun,10,0,1);

  hNtofElectronOVnRvsRunIndex = new TH2F("hNtofElectronOVnRvsRunIndex","hNtofElectronOVnRvsRunIndex;runIndex; Ntofelectron/nReff",mTotalRun,0,mTotalRun,100,0,1);
  hNbemcElectronOVnRvsRunIndex = new TH2F("hNbemcElectronOVnRvsRunIndex","hNbemcElectronOVnRvsRunIndex;runIndex; Nbemcelectron/nReff",mTotalRun,0,mTotalRun,100,0,1);
  hNmuonOVnRvsRunIndex = new TH2F("hNmuonOVnRvsRunIndex","hNmuonOVnRvsRunIndex;runIndex; n#muon/nReff",mTotalRun,0,mTotalRun,10,0,1);

  hDcavsRunIndex = new TH2F("hDcavsRunIndex","hDcavsRunIndex;runIndex;dca (cm)",mTotalRun,0,mTotalRun,300,0,10);
  hDcaXYvsRunIndex = new TH2F("hDcaXYvsRunIndex","hDcaXYvsRunIndex;runIndex;dcaXY (cm)",mTotalRun,0,mTotalRun,300,-10,10);
  hDcaZvsRunIndex = new TH2F("hDcaZvsRunIndex","hDcaZvsRunIndex;runIndex;dcaZ (cm)",mTotalRun,0,mTotalRun,300,-10,10);

  hnEtavsRunIndex= new TH2F("hnEtavsRunIndex","hnEtavsRunIndex;Run Index; nEta;",mTotalRun,0,mTotalRun,10,0,10);
  hnPhivsRunIndex= new TH2F("hnPhivsRunIndex","hnPhivsRunIndex;Run Index; nPhi;",mTotalRun,0,mTotalRun,10,0,10);
  hzDistvsRunIndex= new TH2F("hzDistvsRunIndex","hzDistvsRunIndex;Run Index; zDist;",mTotalRun,0,mTotalRun,1000,-10,10);
  hphiDistvsRunIndex= new TH2F("hphiDistvsRunIndex","hphiDistvsRunIndex;Run Index; phiDist;",mTotalRun,0,mTotalRun,1000,-0.2,0.2);
  hPvEvsRunIndex= new TH2F("hPvEvsRunIndex","hPvEvsRunIndex;Run Index; PvE;",mTotalRun,0,mTotalRun,500,0,10);
  hadc0vsRunIndex= new TH2F("hadc0vsRunIndex","hadc0vsRunIndex;Run Index; adc0;",mTotalRun,0,mTotalRun,1000,0,1000);
  hbetavsRunIndex= new TH2F("hbetavsRunIndex","hbetavsRunIndex;Run Index; 1/beta;",mTotalRun,0,mTotalRun,2000,0,4);
  hgRefMultZDCvsRunIndex = new TH2F("hgRefMultZDCvsRunIndex","(gRefMult/ZDCx)*10^{3} vs RunIndex; Run Index; gRefMult/ZDCx;",mTotalRun,0,mTotalRun,1000,0,15);

  // Other QA Hists
  hgRefMultvsZDCx = new TH2F("hgRefMultvsZDCx","gRefMult vs ZDCx; <ZDCx>; <gRefMult>;",400,0,40000,300,0,30);

}// er chen

//----------------------------------------------------------------------------- 
void StAnaTreeQAMaker::Clear(Option_t *opt) {

  return StMaker::Clear(opt);
}

//----------------------------------------------------------------------------- 
Int_t StAnaTreeQAMaker::Make() {

  if(!mPicoAnaTreeMaker) {
    LOG_WARN << " No PicoDstMaker! Skip! " << endm;
    return kStWarn;
  }

  mAnaTree = mPicoAnaTreeMaker->anaTree();

  if(!mAnaTree) {
    LOG_WARN << " No PicoDst! Skip! " << endm;
    return kStWarn;
  }

  //=================zaochen add====================
  hNEvents->Fill(0);
  if(!mAnaTree->event()) return kStOK;
  //=================event selection================
  int runId = mAnaTree->event()->runId();
  for(int i=0;i<mNBadRuns;i++){
    if(runId==mBadRuns_HT[i]) return kStOK;
  }
  
  //=================event selection================

  hNEvents->Fill(2);
  if(fillhistflag){
    Int_t RUNID = mAnaTree->event()->runId();
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

  //======================ALL QA PLOTS ===============
 //---------------event information----------------------------

  Double_t vzvpd=mAnaTree->event()->vzVpd();
  Double_t vztpc=mAnaTree->event()->primaryVertex().z();
  Double_t vxtpc=mAnaTree->event()->primaryVertex().x();
  Double_t vytpc=mAnaTree->event()->primaryVertex().y();
  Double_t dvz=vztpc-vzvpd;
  Double_t vr=sqrt(vxtpc*vxtpc+vytpc*vytpc);
  Double_t vz = vztpc;
  if(fabs(vxtpc)<1.0e-5)return kStOK;
  if(fabs(vytpc)<1.0e-5)return kStOK;
  if(fabs(vztpc)<1.0e-5)return kStOK;

  if(fillhistflag){
    mVz_tpc->Fill(vztpc);
    mVz_vpd->Fill(vzvpd);
    mdVz->Fill(dvz);  
    mVz_vpdtpc->Fill(vztpc,vzvpd);
    mdVz_tpcVz->Fill(vztpc,dvz);
    mVxy->Fill( mAnaTree->event()->primaryVertex().x(), mAnaTree->event()->primaryVertex().y() );
    mVRvsVZ->Fill(vztpc, vr);
  }

  Float_t Ranking = mAnaTree->event()->ranking();
  Float_t zdcx = mAnaTree->event()->ZDCx();
  Float_t bbcx = mAnaTree->event()->BBCx();
  zdcx=zdcx/1000.;
  bbcx=bbcx/1000.;
  Int_t NRefmultPos=mAnaTree->event()->refMultPos();
  Int_t NRefmultNeg=mAnaTree->event()->refMultNeg();
  Int_t NGnremult=mAnaTree->event()->grefMult();
  Int_t NRefmult=mAnaTree->event()->refMult();
  Int_t NGtrks = mAnaTree->event()->numberOfGlobalTracks();
  Int_t Ntofmatch = mAnaTree->event()->nBTOFMatch();
  Int_t Nbemcmatch = mAnaTree->event()->nBEMCMatch();
  if(fillhistflag){
    //run by run
    if( Ispasseventcuts(vz) ){
      hTPCVzvsRunIndex->Fill(runIndex, vztpc);
      hTPCVxvsRunIndex->Fill(runIndex, vxtpc);
      hTPCVyvsRunIndex->Fill(runIndex, vytpc);
      hVPDVzvsRunIndex->Fill(runIndex, vzvpd);
      hDeltaZvsRunIndex->Fill(runIndex, dvz);
      hZDCXvsRunIndex->Fill(runIndex,  zdcx);
      hBBCXvsRunIndex->Fill(runIndex,  bbcx);
      hRefMultvsRunIndex->Fill(runIndex, NRefmult);
      hGRefMultvsRunIndex->Fill(runIndex, NGnremult);
      hnGlobalvsRunIndex->Fill(runIndex, NGtrks);
    }//
  }
  //----------track information------------------------
  //==============================================================================================
  // Loop Electron Tracks with full eID info
  
  int nE = mAnaTree->numberOfETracks();
  for(int i=0;i<nE;i++){
    StElectronTrack *eTrk = (StElectronTrack*)mAnaTree->eTrack(i);
    Double_t eeta,ept,ephi,echarge,ededx;
    //change to global eTrk
    eeta=eTrk->pMom().pseudoRapidity();
    ephi=RotatePhi(eTrk->pMom().phi());
    ept=eTrk->pMom().perp();
    echarge=eTrk->charge();
    if(echarge==0||eeta==0||ephi==0||ededx==0)continue;
    
    hPvEvsRunIndex     -> Fill(runIndex,eTrk->pve());
    hnEtavsRunIndex    -> Fill(runIndex,eTrk->nEta());
    hnPhivsRunIndex    -> Fill(runIndex,eTrk->nPhi());
    hzDistvsRunIndex   -> Fill(runIndex,eTrk->zDist());
    hphiDistvsRunIndex -> Fill(runIndex,eTrk->phiDist());
    hadc0vsRunIndex    -> Fill(runIndex,eTrk->adc0());
    hbetavsRunIndex    -> Fill(runIndex,(eTrk->beta()!=0)?1./eTrk->beta():0);
    mnsigmaE->Fill( eTrk->nSigmaElectron() );
    mnsigmaE_P->Fill(eTrk->pMom().mag(),eTrk->nSigmaElectron());
    hNSigmaEvsRunIndex->Fill(runIndex, eTrk->nSigmaElectron());
    
    mtrkdcaXY    -> Fill(eTrk->dcaXY());
    mtrkdcaXY_pt -> Fill(ept,eTrk->dcaXY());
    mtrkdcaZ     -> Fill(eTrk->dcaZ());
    mtrkdcaZ_pt  -> Fill(ept,eTrk->dcaZ());
    
    hDcaXYvsRunIndex -> Fill(runIndex,eTrk->dcaXY());
    hDcaZvsRunIndex  -> Fill(runIndex,eTrk->dcaZ());
    
    avgRefMult[runIndex]+=mAnaTree->event()->grefMult();
    avgZDC[runIndex]+=mAnaTree->event()->ZDCx();
    avgZDCCount[runIndex]+=1.;
    avgRefMultCount[runIndex]+=1.;
  }
  //==============================================================================================
  // hadron track
  
  StThreeVectorF vertexPos;
  vertexPos = mAnaTree->event()->primaryVertex();
  Int_t Nprimarytracks=0;
  Int_t Nmtdhits = 0;
  Int_t ntofmatchcount=0;
  Int_t nmtdmatchcount=0;
  Int_t nhftmatchcount=0;
  Int_t nmuons=0;
  Int_t ntofelecton=0;
  Int_t nbemcelectron=0;
  
  Int_t numberoftracks = mAnaTree->numberOfHTracks();
  for(int i=0; i<numberoftracks; i++){
    StHadronTrack* track=(StHadronTrack*) mAnaTree->hTrack(i);
    Double_t dca = track->dca();
    Double_t meta,mpt,mphi,mcharge,mdedx;
    //change to global track
    meta=track->gMom().pseudoRapidity();
    if(track->gMom().mag()!=0) Nprimarytracks++;
    mphi=RotatePhi(track->gMom().phi());
    mpt=track->gMom().perp();
    mcharge=track->charge();
    if(mcharge==0||meta==0||mphi==0||mdedx==0)continue;
    if(track->isHFTTrack()){
      nhftmatchcount++;
    }

    Float_t mmomentum=track->gMom().mag();
    Double_t nsigpi=track->nSigmaPion();
    Double_t nsigk=track->nSigmaKaon();
    if(fillhistflag){
      mtrkpt->Fill( mpt );
      mtrketa->Fill( meta );
      mtrkphi->Fill( mphi );
      mtrketaphi->Fill( mphi,meta );
      mtrkdca->Fill( dca );

      mnhitsfit->Fill( track->nHitsFit() );   
      mnhitsdedx->Fill( track->nHitsDedx() );
      mnsigmaPI->Fill( track->nSigmaPion() );
      mnsigmaK->Fill( track->nSigmaKaon() );

      mtrketa_pt->Fill(mpt*mcharge,meta);
      mtrkphi_pt->Fill(mpt*mcharge,mphi);
      if(mcharge>0)mtrketa_phiPos->Fill(mphi,meta);
      if(mcharge<0)mtrketa_phiNeg->Fill(mphi,meta);

      mtrkdca_pt->Fill(mpt, dca);
      mnhitsfit_pt->Fill(mpt,track->nHitsFit());
      mnhitsdedx_pt->Fill(mpt,track->nHitsDedx());

      mnsigmaPI_P->Fill(mmomentum,nsigpi);
      mnsigmaK_P->Fill(mmomentum,nsigk);

      //------tpc information end-----
      //run by run QA
      if( Ispasseventcuts(vz) ){
        hPtvsRunIndex->Fill(runIndex,mpt);
        hEtavsRunIndex->Fill(runIndex,meta);
        hPhivsRunIndex ->Fill(runIndex,mphi);
        hnhitsfitvsRunIndex ->Fill(runIndex,track->nHitsFit());
        hnhitsdedxvsRunIndex ->Fill(runIndex,track->nHitsDedx());
        hDcavsRunIndex->Fill(runIndex,dca);
        hNSigmaPivsRunIndex->Fill(runIndex,nsigpi);
        hNSigmaKvsRunIndex->Fill(runIndex,nsigk);
      }
    }//

    //------tof information start----------
    Float_t tofbeta=track->beta();
    if(tofbeta > 0)
      ntofmatchcount++;

    if(fillhistflag){		   
      minvsBeta_P->Fill(mmomentum,(tofbeta>0)?1/tofbeta:999);
      if(tofbeta>0){
        Double_t tofm2=mmomentum*mmomentum*( 1.0/(tofbeta*tofbeta)-1.0);
        mtofM2_P->Fill(mmomentum,tofm2);
      }
    }//

  }//loop of all hadron tracks
  //==============================================================================================
  
  Int_t Nptrks=Nprimarytracks;
  if(fillhistflag){
    //event information QA
    mRanking_nPtrks->Fill(Nptrks,Ranking);
    mnPtrks_nGtrks->Fill(NGtrks,Nptrks);
    mnRefMult_nPtrks->Fill(Nptrks,NRefmultPos+NRefmultNeg);
    mnRefMult_nGtrks->Fill(NGtrks,NRefmultPos+NRefmultNeg);
    mnGRefMult_nPtrks->Fill(Nptrks, NGnremult);
    mnGRefMult_nGtrks->Fill(NGtrks, NGnremult);	   

    mnRefMult_nGRefMult->Fill(NGnremult,NRefmultPos+NRefmultNeg);
    mnPtrks_nMtdHits->Fill(Nmtdhits,Nptrks);
    mnPtrks_nTofHits->Fill(ntofmatchcount,Nptrks);
    mnTofHits_nMtdHits->Fill(Nmtdhits,ntofmatchcount);                
    mnTofMatch_nTofHits->Fill(ntofmatchcount,Ntofmatch);  	

    //------------------------------------------------------//
    //---------- make run by run QA of ---------------------//
    //------------------------------------------------------//
    if( Ispasseventcuts(vz) ){
      hnPrimaryvsRunIndex->Fill(runIndex,Nptrks);

      hntofmatchvsRunIndex->Fill(runIndex,ntofmatchcount);
      hnmtdmatchvsRunIndex->Fill(runIndex,nmtdmatchcount);
      hnhftmatchvsRunIndex->Fill(runIndex,nhftmatchcount);
      hnmtdhitsvsRunIndex->Fill(runIndex,Nmtdhits);
      hNmuonvsRunIndex->Fill(runIndex,nmuons);
      hNtofElectronvsRunIndex->Fill(runIndex,ntofelecton);
      hNbemcElectronvsRunIndex->Fill(runIndex,nbemcelectron);

      float tofmatchratio= (float)ntofmatchcount/NGnremult;
      float mtdmatchratio=(float)nmtdmatchcount/NGnremult;
      float hftmatchratio=(float)nhftmatchcount/NGnremult;
      float mtdratio=(float)Nmtdhits/NGnremult;		
      float muonratio=(float)nmuons/NGnremult;
      float toferatio=(float)ntofelecton/NGnremult;
      float bemceratio=(float)nbemcelectron/NGnremult;
      hntofmatchOVnGRvsRunIndex->Fill(runIndex,tofmatchratio);
      hnmtdmatchOVnGRvsRunIndex->Fill(runIndex, mtdmatchratio);
      hnhftmatchOVnGRvsRunIndex->Fill(runIndex,hftmatchratio);
      hnmtdhitsOVnGRvsRunIndex->Fill(runIndex,mtdratio);
      hNmuonOVnGRvsRunIndex->Fill(runIndex, muonratio);
      hNtofElectronOVnGRvsRunIndex->Fill(runIndex,toferatio);
      hNbemcElectronOVnGRvsRunIndex->Fill(runIndex,bemceratio);

      float tofmatchratio2= (float)ntofmatchcount/NRefmult;
      float mtdmatchratio2=(float)nmtdmatchcount/NRefmult;
      float hftmatchratio2=(float)nhftmatchcount/NRefmult;
      float mtdratio2=(float)Nmtdhits/NRefmult;		
      float muonratio2=(float)nmuons/NRefmult;
      float toferatio2=(float)ntofelecton/NRefmult;
      float bemceratio2=(float)nbemcelectron/NRefmult;
      hntofmatchOVnRvsRunIndex->Fill(runIndex,tofmatchratio2);
      hnmtdmatchOVnRvsRunIndex->Fill(runIndex, mtdmatchratio2);
      hnhftmatchOVnRvsRunIndex->Fill(runIndex,hftmatchratio2);
      hnmtdhitsOVnRvsRunIndex->Fill(runIndex,mtdratio2);
      hNmuonOVnRvsRunIndex->Fill(runIndex, muonratio2);
      hNtofElectronOVnRvsRunIndex->Fill(runIndex,toferatio2);
      hNbemcElectronOVnRvsRunIndex->Fill(runIndex,bemceratio2);
    }
  }//
  return kStOK;
}//end of main fucntion

//----------------------------------------------------------------
Bool_t StAnaTreeQAMaker::Ispasseventcuts(double vz)
{
  if(fabs(vz)<40.)return true;
  else return false;
}

//---------------------------------------------------------------
Double_t StAnaTreeQAMaker::RotatePhi(Double_t phi) const
{
  Double_t outPhi = phi;
  Double_t pi=TMath::Pi();
  while(outPhi<0) outPhi += 2*pi;
  while(outPhi>2*pi) outPhi -= 2*pi;
  return outPhi;
}



