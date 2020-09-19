#include "StMyAnalysisMaker.h"
#include "StRoot/StPicoDstMaker/StPicoDst.h"
#include "StRoot/StPicoDstMaker/StPicoEvent.h"
#include "StRoot/StPicoDstMaker/StPicoTrack.h"
#include "StRoot/StPicoDstMaker/StPicoBTofPidTraits.h"
#include "StRoot/StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StRefMultCorr/StRefMultCorr.h"
#include "StRoot/StRefMultCorr/CentralityMaker.h"
#include "StBTofUtil/tofPathLength.hh"
#include "StThreeVectorF.hh"
#include "StLorentzVector.hh"
#include "StEvent/StDcaGeometry.h"
#include "StCuts.h"
#include "StEventPlaneConstants.h"
#include "PhysicalConstants.h"
#include "phys_constants.h"
#include "KFParticle.h"
#include "TLorentzVector.h"
#include "TEfficiency.h"
#include "TVector3.h"
#include "TProfile.h"
#include "TRVector.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THn.h"
#include "MVertex.h"
#include "MTrack.h"
ClassImp(StMyAnalysisMaker)

#define M_PHI    1.019461
#define M_KSTAR  0.89581
const Int_t StMyAnalysisMaker::PDGID[NFLAG][3] = {{321, -321, 211},
   {321, -321, -211}
};
const Float_t StMyAnalysisMaker::CenEdg[NCENBINS + 1] = {0, 8, 12, 16}; // [0-7],[8-11],[12-15]
const Double_t StMyAnalysisMaker::ParMass[NFLAG][3] = {{M_KAON_PLUS, M_KAON_MINUS, M_PION_PLUS},
   {M_KAON_PLUS, M_KAON_MINUS, M_PION_MINUS}
};

//-----------------------------------------------------------------------------
StMyAnalysisMaker::StMyAnalysisMaker(const char *name, StPicoDstMaker *picoMaker,  StRefMultCorr *grefmultCorrUtil, const char *outName)
  : StMaker(name), mPicoDstMaker(picoMaker), mPicoDst(NULL), mPicoEvent(NULL), mGRefMultCorrUtil(grefmultCorrUtil), mFailedRunnumber(0), mOutName(outName),  
     mAcceptEvent(false), mAcceptQvectorFile(false), mAcceptQvectorFiletmp(true), mCent(-1), mRunNumber(0), mBField(-999.), mVertexPos(-999, -999, -999),
     mEventPlane(0), mEventPlane1(0), mEventPlane2(0), mEventPlaneEtaPlus(0), mEventPlaneEtaMinus(0), mResolutionRandom(0), mResolutionEta(0),
     mQ(-999, -999), mQ1(-999, -999), mQ2(-999, -999), mQEtaPlus(-999, -999), mQEtaMinus(-999, -999),
     prfQxCentEtaPlus(NULL), prfQyCentEtaPlus(NULL), prfQxCentEtaMinus(NULL), prfQyCentEtaMinus(NULL)
{
   mOutputFile = new TFile(mOutName.Data(), "RECREATE");
}

//-----------------------------------------------------------------------------
StMyAnalysisMaker::~StMyAnalysisMaker()
{ /*  */ }

//-----------------------------------------------------------------------------
Int_t StMyAnalysisMaker::Init()
{
   mOutputFile->cd();
   DeclareHistograms();
   DeclareEPHistograms();
   return kStOK;
}

//-----------------------------------------------------------------------------
Int_t StMyAnalysisMaker::Finish()
{
   cout << "StMyAnalysisMaker::Finish()" << endl;

   if (mOutName != "") {
      mOutputFile->cd();
       WriteHistograms();
      //mOutputFile->Write();
      mOutputFile->Close();
   }

   return kStOK;
}

//-----------------------------------------------------------------------------
void StMyAnalysisMaker::DeclareHistograms()
{
   mEventCounter      = new TH1D("EventCounter", "", 5, 0, 5);
   mPairCounter       = new TH1D("PairCounter", "", 10, 0, 10);
   mTrkCounter        = new TH1D("TrkCounter", "", 10, 0, 10);
   mVzCorr  	      = new TH2F("VzCorr", "", 200, -100, 100, 200, -100, 100);
   mVzDiff  	      = new TH1F("VzDiff", "", 200, -100, 100);
   mVzDiffZoom        = new TH1F("VzDiffZoom", "", 200, -10, 10);
   mVxy               = new TH2F("Vxy", "", 500, -1, 1, 500, -1, 1);
   // mNEventsPerTrigger = new TH1F("NEventsPerTrigger", "", 50, 0, 50);
   mRefMult  	      = new TH2F("RefMult", "", 100, -50, 50, 1000, 0, 1000);
   mGRefMult 	      = new TH2F("GRefMult", "", 100, -50, 50, 1000, 0, 1000);
   mGRefMultCen       = new TH2F("GRefMultCen", "grefmult vs Centrality", 16, 0, 16, 1000, 0, 1000);
   mGRefMultCorCen    = new TH2F("GRefMultCorCen", "grefmultcor vs Centrality", 16, 0, 16, 1000, 0, 1000);

   mDcaZ_Pt_Pi 	      = new TH2F("DcaZ_Pt_Pi", "", 200, 0., 5., 500, -0.25, 0.25);
   mDcaZ_Pt_K 	      = new TH2F("DcaZ_Pt_K", "", 200, 0., 5., 500, -0.25, 0.25);
   mDcaZ_Pt_P 	      = new TH2F("DcaZ_Pt_P", "", 200, 0., 5., 500, -0.25, 0.25);
   mDca_Pt_Pi 	      = new TH2F("Dca_Pt_Pi", "", 200, 0., 5., 500, -0.25, 0.25);
   mDca_Pt_K  	      = new TH2F("Dca_Pt_K", "", 200, 0., 5., 500, -0.25, 0.25);
   mDca_Pt_P  	      = new TH2F("Dca_Pt_P", "", 200, 0., 5., 500, -0.25, 0.25);

   mNHFTHitsPattern   = new TH2F("NHFTHitsPattern", "", 50, 0, 50, 10, 0, 10); // xxx IST-PXL2-PXL1

   mNKPi       	      = new TH2F("NKPi", "", 1000, 0, 1000, 1000, 0, 1000);

   mEP_wo_recenter_wo_Eta_Gap = new TH1F("EP_wo_recenter_wo_eta_gap", "Event Plane without recenter and Eta Gap;#Psi;Counts", 60, 0, TMath::Pi());
   mEP_w_recenter_wo_Eta_Gap = new TH1F("EP_w_recenter_wo_eta_gap", "Event Plane with recenter and Eta Gap;#Psi;Counts", 60, 0, TMath::Pi());
   mEP_w_recenter_w_Eta_Gap = new TH1F("EP_w_recenter_w_eta_gap", "Event Plane with recenter and Eta Gap;#Psi;Counts", 60, 0, TMath::Pi());

   // TOF Match Efficiency
   TString centrality = "";

   for (int i = 0; i < 4; i++) {
      if (i == 0) centrality = "40_80";
      else if (i == 1) centrality = "20_40";
      else if (i == 2) centrality = "0_20";
      else centrality = "0_80";

      // TOF Matching with HFT Match and lose cut
      mHFTTofMatchEff[0][i]   = new TEfficiency(Form("HFTTofMatchEff_K_%s", centrality.Data()), Form("Kaon Tof Match Efficiency @ %s;p_{T} [GeV/c];#epsilon", centrality.Data()), 100, 0, 10);
      mHFTTofMatchEff[1][i]   = new TEfficiency(Form("HFTTofMatchEff_Pi_%s", centrality.Data()), Form("Pion Tof Match Efficiency @ %s;p_{T} [GeV/c];#epsilon", centrality.Data()), 100, 0, 10);
      mHFTTofBetaEff[0][i]    = new TEfficiency(Form("HFTTofBetaEff_K_%s", centrality.Data()), Form("Kaon Tof Match Efficiency (beta>0) @ %s;p_{T} [GeV/c];#epsilon", centrality.Data()), 100, 0, 10);
      mHFTTofBetaEff[1][i]    = new TEfficiency(Form("HFTTofBetaEff_Pi_%s", centrality.Data()), Form("Pion Tof Match Efficiency (beta>0) @ %s;p_{T} [GeV/c];#epsilon", centrality.Data()), 100, 0, 10);

      // TOF Matching with HFT and Tight Cuts
      mHFTTightTofMatchEff[0][i] = new TEfficiency(Form("HFTTightTofMatchEff_K_%s", centrality.Data()), Form("Kaon Tof Match Efficiency @ %s;p_{T} [GeV/c];#epsilon", centrality.Data()), 100, 0, 10);
      mHFTTightTofMatchEff[1][i] = new TEfficiency(Form("HFTTightTofMatchEff_Pi_%s", centrality.Data()), Form("Pion Tof Match Efficiency @ %s;p_{T} [GeV/c];#epsilon", centrality.Data()), 100, 0, 10);
      mHFTTightTofBetaEff[0][i]  = new TEfficiency(Form("HFTTightTofBetaEff_K_%s", centrality.Data()), Form("Kaon Tof Match Efficiency (beta>0) @ %s;p_{T} [GeV/c];#epsilon", centrality.Data()), 100, 0, 10);
      mHFTTightTofBetaEff[1][i]  = new TEfficiency(Form("HFTTightTofBetaEff_Pi_%s", centrality.Data()), Form("Pion Tof Match Efficiency (beta>0) @ %s;p_{T} [GeV/c];#epsilon", centrality.Data()), 100, 0, 10);
   }

#if RUNALL == 1
   mTree = new TTree("mTree", "V0 Tree");
   mTree->Branch("mRunId", &v0Tree.mRunId, "mRunId/I");
   mTree->Branch("mEvtId", &v0Tree.mEvtId, "mEvtId/I");
   mTree->Branch("mVx", &v0Tree.mVx, "mVx/F");
   mTree->Branch("mVy", &v0Tree.mVy, "mVy/F");
   mTree->Branch("mVz", &v0Tree.mVz, "mVz/F");
   mTree->Branch("mRefMult", &v0Tree.mRefMult, "mRefMult/S");
   mTree->Branch("mGRefMult", &v0Tree.mGRefMult, "mGRefMult/S");
   mTree->Branch("mZdcX", &v0Tree.mZdcX, "mZdcX/F");
   mTree->Branch("mBbcX", &v0Tree.mBbcX, "mBbcX/F");
   mTree->Branch("mReWeight", &v0Tree.mReWeight, "mReWeight/F");
   mTree->Branch("mGRefMultCor", &v0Tree.mGRefMultCor, "mGRefMultCor/F");
   mTree->Branch("mCen16", &v0Tree.mCen16, "mCen16/I");
   mTree->Branch("mCen9", &v0Tree.mCen9, "mCen9/I");
   // mTree->Branch("mQx_west",&v0Tree.mQx_west,"mQx_west/F");
   // mTree->Branch("mQy_west",&v0Tree.mQy_west,"mQy_west/F");
   // mTree->Branch("mQx_east",&v0Tree.mQx_east,"mQx_east/F");
   // mTree->Branch("mQy_east",&v0Tree.mQy_east,"mQy_east/F");
   mTree->Branch("mNV0", &v0Tree.mNV0, "mNV0/I");
   mTree->Branch("mFlag", v0Tree.mFlag, "mFlag[mNV0]/b");
   mTree->Branch("mDca1", v0Tree.mDca1, "mDca1[mNV0]/F");
   mTree->Branch("mDca2", v0Tree.mDca2, "mDca2[mNV0]/F");
   mTree->Branch("mDca3", v0Tree.mDca3, "mDca3[mNV0]/F");
   mTree->Branch("mPt1", v0Tree.mPt1, "mPt1[mNV0]/F");
   mTree->Branch("mPt2", v0Tree.mPt2, "mPt2[mNV0]/F");
   mTree->Branch("mPt3", v0Tree.mPt3, "mPt3[mNV0]/F");
   mTree->Branch("mPhi1", v0Tree.mPhi1, "mPhi1[mNV0]/F");
   mTree->Branch("mPhi2", v0Tree.mPhi2, "mPhi2[mNV0]/F");
   mTree->Branch("mPhi3", v0Tree.mPhi3, "mPhi3[mNV0]/F");
   mTree->Branch("mTofFlag", v0Tree.mTofFlag, "mTofFlag[mNV0]/I");
   mTree->Branch("mDcaDaughters", v0Tree.mDcaDaughters, "mDcaDaughters[mNV0]/F");
   mTree->Branch("mSecSigma", v0Tree.mSecSigma, "mSecSigma[mNV0]/F");
   mTree->Branch("mV0x_HS", v0Tree.mV0x_HS, "mV0x_HS[mNV0]/F");
   mTree->Branch("mV0y_HS", v0Tree.mV0y_HS, "mV0y_HS[mNV0]/F");
   mTree->Branch("mV0z_HS", v0Tree.mV0z_HS, "mV0z_HS[mNV0]/F");
   mTree->Branch("mPt_HS", v0Tree.mPt_HS, "mPt_HS[mNV0]/F");
   mTree->Branch("mEta_HS", v0Tree.mEta_HS, "mEta_HS[mNV0]/F");
   mTree->Branch("mPhi_HS", v0Tree.mPhi_HS, "mPhi_HS[mNV0]/F");
   mTree->Branch("mMass_HS", v0Tree.mMass_HS, "mMass_HS[mNV0]/F");
   mTree->Branch("mTheta_HS", v0Tree.mTheta_HS, "mTheta_HS[mNV0]/F");
   mTree->Branch("mCosThetaKK_HS", v0Tree.mCosThetaKK_HS, "mCosThetaKK_HS[mNV0]/F");
   mTree->Branch("mCosThetaStarPion_HS", v0Tree.mCosThetaStarPion_HS, "mCosThetaStarPion_HS[mNV0]/F");
   mTree->Branch("mCosThetaPriKaon_HS", v0Tree.mCosThetaPriKaon_HS, "mCosThetaPriKaon_HS[mNV0]/F");
   mTree->Branch("mDca2Vtx_HS", v0Tree.mDca2Vtx_HS, "mDca2Vtx_HS[mNV0]/F");
   mTree->Branch("mDecayL_HS", v0Tree.mDecayL_HS, "mDecayL_HS[mNV0]/F");
   mTree->Branch("mMassKK_HS", v0Tree.mMassKK_HS, "mMassKK_HS[mNV0]/F");
   mTree->Branch("mPtKK_HS", v0Tree.mPtKK_HS, "mPtKK_HS[mNV0]/F");
   mTree->Branch("mDPhiEtaGap", v0Tree.mDPhiEtaGap, "mDPhiEtaGap[mNV0]/F");
#endif
}

void StMyAnalysisMaker::DeclareEPHistograms()
{
   // track level QA
   hNHitsFit = new TH1I("hNHitsFit", "hNHitsFit", 50, 0, 50);
   hDca = new TH1F("hDca", "hDca", 20000, -10, 10);
   hEta = new TH1F("hEta", "hEta", 30, -1.5, 1.5);
   hPt = new TH1F("hPt", "hPt", 200, 0, 10);

   // event plane and Q vector
   float PI = TMath::Pi();

   hPhiCentEtaPlusZPlus = new TH2F("hPhiCentEtaPlusZPlus", "hPhiCentEtaPlusZPlus", 9, 0, 9, 120, -PI, PI);
   hPhiCentEtaPlusZMinus = new TH2F("hPhiCentEtaPlusZMinus", "hPhiCentEtaPlusZMinus", 9, 0, 9, 120, -PI, PI);
   hPhiCentEtaMinusZPlus = new TH2F("hPhiCentEtaMinusZPlus", "hPhiCentEtaMinusZPlus", 9, 0, 9, 120, -PI, PI);
   hPhiCentEtaMinusZMinus = new TH2F("hPhiCentEtaMinusZMinus", "hPhiCentEtaMinusZMinus", 9, 0, 9, 120, -PI, PI);

   hEventPlaneCent = new TH2F("hEventPlaneCent", "hEventPlaneCent", 9, 0, 9, 60, 0, PI);
   hEventPlane1Cent = new TH2F("hEventPlane1Cent", "hEventPlane1Cent", 9, 0, 9, 60, 0, PI);
   hEventPlane2Cent = new TH2F("hEventPlane2Cent", "hEventPlane2Cent", 9, 0, 9, 60, 0, PI);
   hEventPlaneEtaPlusCent = new TH2F("hEventPlaneEtaPlusCent", "hEventPlaneEtaPlusCent", 9, 0, 9, 60, 0, PI);
   hEventPlaneEtaMinusCent = new TH2F("hEventPlaneEtaMinusCent", "hEventPlaneEtaMinusCent", 9, 0, 9, 60, 0, PI);
   // hQyQxCent = new TH3F("hQyQxCent", "hQyQxCent", 9, 0, 9, 1000, -50, 50, 1000, -50, 50);
   // hQyQx1Cent = new TH3F("hQyQx1Cent", "hQyQx1Cent", 9, 0, 9, 1000, -50, 50, 1000, -50, 50);
   // hQyQx2Cent = new TH3F("hQyQx2Cent", "hQyQx2Cent", 9, 0, 9, 1000, -50, 50, 1000, -50, 50);
   // hQyQxEtaPlusCent = new TH3F("hQyQxEtaPlusCent", "hQyQxEtaPlusCent", 9, 0, 9, 1000, -50, 50, 1000, -50, 50);
   // hQyQxEtaMinusCent = new TH3F("hQyQxEtaMinusCent", "hQyQxEtaMinusCent", 9, 0, 9, 1000, -50, 50, 1000, -50, 50);
   prfCosResolutionRandomCent = new TProfile("prfCosResolutionRandomCent", "prfCosResolutionRandomCent", 9, 0, 9);
   prfCosResolutionEtaCent = new TProfile("prfCosResolutionEtaCent", "prfCosResolutionEtaCent", 9, 0, 9);

   // hHadronV2PtCent = new TH3F("hHadronV2PtCent", "hHadronV2PtCent", 100, 0., 5., 9, 0, 9, 200, -1., 1.);
   // hHadronHftV2PtCent = new TH3F("hHadronHftV2PtCent", "hHadronHftV2PtCent", 100, 0., 5., 9, 0, 9, 200, -1., 1.);
   hHadronPrimaryV2PtCent = new TH3F("hHadronPrimaryV2PtCent", "hHadronPrimaryV2PtCent", 100, 0., 5., 9, 0, 9, 200, -1., 1.);
   // hHadronHftPrimaryV2PtCent = new TH3F("hHadronHftPrimaryV2PtCent", "hHadronHftPrimaryV2PtCent", 100, 0., 5., 9, 0, 9, 200, -1., 1.);

   const int nDim = 4;
   int nBins[nDim] = {100, 9, 200, 8};//pt, cent, v2, etaGap
   double xMin[nDim] = {0, 0, -1, 0};
   double xMax[nDim] = {5, 9, 1, 0.8};
   hHadronV2PtCentEtaGap = new THnF("hHadronV2PtCentEtaGap", "hHadronV2PtCentEtaGap", nDim, nBins, xMin, xMax);
}

//-----------------------------------------------------------------------------
void StMyAnalysisMaker::WriteHistograms()
{
/*   mEventCounter->Write();
   mTrkCounter->Write();
   mPairCounter->Write();
   mVzCorr->Write();
   mVzDiff->Write();
   mVzDiffZoom->Write();
   mVxy->Write();
   mRefMult->Write();
   mGRefMult->Write();
   mGRefMultCen->Write();
   mGRefMultCorCen->Write();
   // mNEventsPerTrigger->Write();
   mDcaZ_Pt_Pi->Write();
   mDcaZ_Pt_K->Write();
   mDcaZ_Pt_P->Write();
   mDca_Pt_Pi->Write();
   mDca_Pt_K->Write();
   mDca_Pt_P->Write();
   mNHFTHitsPattern->Write();
   mNKPi->Write();

   mEP_wo_recenter_wo_Eta_Gap->Write();
   mEP_w_recenter_wo_Eta_Gap->Write();
   mEP_w_recenter_w_Eta_Gap->Write();

   for (int i = 0; i < 4; i++) {
      mHFTTofMatchEff[0][i]->Write();
      mHFTTofMatchEff[1][i]->Write();
      mHFTTofBetaEff[0][i]->Write();
      mHFTTofBetaEff[1][i]->Write();

      mHFTTightTofMatchEff[0][i]->Write();
      mHFTTightTofMatchEff[1][i]->Write();
      mHFTTightTofBetaEff[0][i]->Write();
      mHFTTightTofBetaEff[1][i]->Write();
   }
*/
#if RUNALL == 1
   mTree->Write();
#endif
}

//-----------------------------------------------------------------------------
void StMyAnalysisMaker::Clear(Option_t *opt)
{
}

//-----------------------------------------------------------------------------
Int_t StMyAnalysisMaker::Make()
{
   if (!mPicoDstMaker) {
      LOG_WARN << " No PicoDstMaker! Skip! " << endm;
      return kStWarn;
   }

   mPicoDst = mPicoDstMaker->picoDst();

   if (!mPicoDst) {
      LOG_WARN << " No PicoDst! Skip! " << endm;
      return kStWarn;
   }

   // StPicoEvent *event = (StPicoEvent *)mPicoDst->event();
   mPicoEvent = (StPicoEvent *)mPicoDst->event();
   StThreeVectorF pVtx(-999., -999., -999.);
   StThreeVectorF pVtxErr(0., 0., 0.);

   if (mPicoEvent) {
      pVtx = mPicoEvent->primaryVertex();
      pVtxErr = mPicoEvent->primaryVertexError();
   }

   mEventCounter->Fill("All Pico", 1);

   if (!isGoodTrigger() || !isGoodEvent()) return kStOK;

   Float_t vzVpd    = mPicoEvent->vzVpd();
   Int_t   refMult  = mPicoEvent->refMult();
   Int_t   grefMult = mPicoEvent->grefMult();
   Int_t   runId    = mPicoEvent->runId();
   Int_t   eventId  = mPicoEvent->eventId();
   Float_t ZDCx     = mPicoEvent->ZDCx();
   Float_t BBCx     = mPicoEvent->BBCx();
   mRefMult->Fill(pVtx.z(), refMult);
   mGRefMult->Fill(pVtx.z(), grefMult);
   mVzCorr->Fill(pVtx.z(), vzVpd);
   mVzDiff->Fill(pVtx.z() - vzVpd);
   mVzDiffZoom->Fill(pVtx.z() - vzVpd);
   mVxy->Fill(pVtx.x(), pVtx.y());

   mEventCounter->Fill("|Vz|<6&VzDiff<3", 1);

   Float_t B = mPicoEvent->bField();
   // Get Centrality
   mGRefMultCorrUtil->init(runId);
   mGRefMultCorrUtil->initEvent(grefMult, pVtx.z(), ZDCx);

   Int_t   cen16       = mGRefMultCorrUtil->getCentralityBin16();
   Int_t   cen9        = mGRefMultCorrUtil->getCentralityBin9();
   Float_t reweight    = mGRefMultCorrUtil->getWeight() ;
   Float_t grefmultCor = mGRefMultCorrUtil->getRefMultCorr() ;
   mGRefMultCen->Fill(cen16, mPicoEvent->grefMult());
   mGRefMultCorCen->Fill(cen16, grefmultCor,reweight); // Calculate number of events 

   Int_t cenbin = 3;

   for (int i = 0; i < NCENBINS; i++) {
      if (cen16 >= CenEdg[i] && cen16 < CenEdg[i + 1])
         cenbin = i;
   }

   // --------------------------------------------------------------------
   // event plane information 
   /*if (mRunNumber != mPicoEvent->runId()) getRunInfo(mPicoEvent->runId()); // Load Qvector files
   else mAcceptQvectorFile = true;

   getEventInfo();//get event info

   if (mAcceptQvectorFile && mAcceptQvectorFiletmp)
     {
       mEventPlaneStatus = calculateEventPlane();
       if (!mEventPlaneStatus && mAcceptEvent)
	 {
	   calculateHadronV2();
	 }
     }

   if (mFailedRunnumber != mPicoEvent->runId()) {
      if (!loadEventPlaneCorr()) {
         LOG_WARN << "Event plane calculations unavalable! Skipping" << endm;
         mFailedRunnumber = mPicoDst->event()->runId();
         return kStOK;
      }
   }
   else  return kStOK;
*/
   // no recenter correction with eta gap
   // recenter with Eta gap
   // event plane resolution with different eta gap

   // TVector2 QSub = mEventPlaneMaker->Q() - mEventPlaneMaker.q();


   // // ***********need re-consideration. reject auto-correction.*****
   // float const eventPlane = mEventPlaneMaker->getEventPlane();
   // if (mEventPlaneMaker->eventPlaneStatus()) return kStOk;

   // TVector2 QSub = mEvents[0]->Q() - mEvents[0]->pionAt(iTrk1).q();
   // if (iEvt2 == 0) QSub -= mEvents[iEvt2]->kaonAt(iTrk2).q();
   // float dPhi = pair.phi() - QSub.Phi() / 2;
   // while (dPhi < 0) dPhi += TMath::Pi();
   // while (dPhi >= TMath::Pi()) dPhi -= TMath::Pi();

   // int iEta = (int)(pair.eta() * 10 + 10);
   // for (int nEtaGaps = 3; nEtaGaps < 4; ++nEtaGaps) // eta gap is 3 (from Hao's D0 v2 analysis.)
   //   {
   //     TVector2 QSubEtaGap = mEvents[0]->QEtaGap(iEta, nEtaGaps);
   //     int iEta_ = iEta;
   //     if (iEta_ < nEtaGaps) iEta_ = nEtaGaps - 1;
   //     if (iEta_ > 20 - nEtaGaps) iEta_ = 20 - nEtaGaps;
   //     int iEtaPion = (int)(mEvents[0]->pionAt(iTrk1).gMom().pseudoRapidity() * 10 + 10);
   //     if (fabs(iEtaPion - iEta_) >= nEtaGaps)
   // 	 QSubEtaGap -= mEvents[0]->pionAt(iTrk1).q();
   //     if (iEvt2 == 0)
   // 	 {
   // 	   int iEtaKaon = (int)(mEvents[iEvt2]->kaonAt(iTrk2).gMom().pseudoRapidity() * 10 + 10);
   // 	   if (fabs(iEtaKaon - iEta_) >= nEtaGaps)
   // 	     QSubEtaGap -= mEvents[iEvt2]->kaonAt(iTrk2).q();
   // 	 }
   //     if (QSubEtaGap.Mod() == 0)
   // 	 {
   // 	   cout << "QSubEtaGap.Mod()==0  nEtaGaps: " << nEtaGaps << endl;
   // 	   continue;
   // 	 }
   //     float dPhiEtaGap = pair.phi() - QSubEtaGap.Phi() / 2;
   //     while (dPhiEtaGap < 0) dPhiEtaGap += TMath::Pi();
   //     while (dPhiEtaGap >= TMath::Pi()) dPhiEtaGap -= TMath::Pi();
   //     double toFill[5] = {mCentBin + 0.5, pair.pt(), pair.m(), dPhiEtaGap, 0.1 * nEtaGaps + 0.05};
   //   }


#if RUNALL == 1
   //  mPicoDst->Print();
   //  mPicoDst->printTracks();
   vector<Int_t> c_kaons;
   vector<Int_t> c_pions;   // charm decay pions/kaons
   vector<Int_t> s_pions;   // strange particle decay pions (Ks, Lammbda)
   c_kaons.clear();
   c_pions.clear();
   s_pions.clear();

   memset(mBetaCorr, 0, sizeof(mBetaCorr));
   memset(mBetaCorr2, 0, sizeof(mBetaCorr2));
   memset(mDcaPosX, 0, sizeof(mDcaPosX));
   memset(mDcaPosY, 0, sizeof(mDcaPosY));
   memset(mDcaPosZ, 0, sizeof(mDcaPosZ));
   memset(mMomX, 0, sizeof(mMomX));
   memset(mMomY, 0, sizeof(mMomY));
   memset(mMomZ, 0, sizeof(mMomZ));
   memset(&v0Tree, 0, sizeof(v0Tree));

   float Qx = 0;
   float Qy = 0;
   int nTracks = mPicoDst->numberOfTracks();

   for (int i = 0; i < nTracks; i++) {
      StPicoTrack *t = (StPicoTrack *)mPicoDst->track(i);

      if (!t) continue; mTrkCounter->Fill("All Trks", 1);

      //tpc info for event plane cal, Primary track 
      double eta = t->pMom().pseudoRapidity();
      double pt  = t->pMom().perp();
      double phi = t->pMom().phi();

      if (phi < 0.0)  phi += cuts::twoPi;
      StDcaGeometry    dcaG  = t->dcaGeometry();
      StPhysicalHelixD helix = dcaG.helix();
//cout << "2222222222222222222222222" << endl;

      THelixTrack thelix =  dcaG.thelix();
      Double_t    vtx[3] = {pVtx.x(), pVtx.y(), pVtx.z()};
      thelix.Move(thelix.Path(vtx));
      const Double_t *pos = thelix.Pos();
      const Double_t *dir = thelix.Dir();
      StThreeVectorF dcaGlobal = StThreeVectorF(pos[0], pos[1], pos[2]) - pVtx;
      StThreeVectorF p = StThreeVectorF(dir[0], dir[1], dir[2]);
      double ptot = dcaG.momentum().mag();
      p *= ptot;

      float dca       = dcaGlobal.mag();
      float nsigma_pi = t->nSigmaPion();
      float nsigma_k  = t->nSigmaKaon();

      Bool_t bPassTof;
      Bool_t bPassBeta;

      if (pt > EventPlaneConstants::ptMinEventPlane 
	  && pt <= EventPlaneConstants::ptMaxEventPlane 
	  && fabs(dca) < EventPlaneConstants::dcaMaxEventPlane 
	  && fabs(eta) <= EventPlaneConstants::etaMaxEventPlane 
	  && t->nHitsFit() > EventPlaneConstants::nHitsFitMin
	  && 1.0*t->nHitsFit()/t->nHitsMax() >= EventPlaneConstants::nHitsFitRatio ) {
         float qx = cos(2 * phi) * pt;
         float qy = sin(2 * phi) * pt;
         Qx += qx;
         Qy += qy;
      }

      if (!isGoodTrack(t)) continue; mTrkCounter->Fill("TrackQuality", 1);

      mDcaPosX[i] = pos[0];
      mDcaPosY[i] = pos[1];
      mDcaPosZ[i] = pos[2];
      mMomX[i] 	  = p.x();
      mMomY[i] 	  = p.y();
      mMomZ[i] 	  = p.z();

      int index2tof = t->bTofPidTraitsIndex();
      float beta = 0.;

      if (index2tof >= 0) {
         StPicoBTofPidTraits *tofPid = mPicoDst->btofPidTraits(index2tof);

         if (tofPid) {
            beta = tofPid->btofBeta();

            if (beta < 1e-4 && fabs(dca) < 3.) {
               mTrkCounter->Fill("ReCaLBeta", 1);
               StThreeVectorF btofHitPos = tofPid->btofHitPos();

               float L = tofPathLength(&pVtx, &btofHitPos, helix.curvature());
               float tof = tofPid->btof();

               if (tof > 0) beta = L / (tof * (C_C_LIGHT / 1.e9));
            }
         }
      }

      float beta_pi = ptot / sqrt(ptot * ptot + M_PION_PLUS * M_PION_PLUS);
      float beta_k  = ptot / sqrt(ptot * ptot + M_KAON_PLUS * M_KAON_PLUS);

      // HFT hit map
      Int_t hitMapHFT = t->nHitsMapHFT();
      Int_t nPxl1Hit  = hitMapHFT & 0x1;
      Int_t nPxl2Hit  = ((hitMapHFT >> 1) & 0x1) + ((hitMapHFT >> 2) & 0x1);
      Int_t nIstHit   = ((hitMapHFT >> 3) & 0x1) + ((hitMapHFT >> 4) & 0x1);
      Int_t hftPattern = 0;

      if (nPxl1Hit > 0) hftPattern |= 0x1;

      if (nPxl2Hit > 0) hftPattern |= 1 << 1;

      if (nIstHit > 0)  hftPattern |= 1 << 2;

      mNHFTHitsPattern->Fill(abs(t->nHitsFit()), hftPattern);

      if (hftPattern != 0x7) continue; // select tracks with hits in all three layers

      mTrkCounter->Fill("RequireHFT", 1);

      if(fabs(eta)>cuts::eta) continue; //|Eta| <1 good detector respond.
      mTrkCounter->Fill("|eta|<1", 1);

      // +++++++++++++++++++++++++++++++
      // Fill TOF Match Efficiency
      // +++++++++++++++++++++++++++++++
      if (fabs(nsigma_k) < cuts::nSigmaCut) {
         bPassTof  = index2tof >= 0;
         bPassBeta = beta > 0;
         mHFTTofMatchEff[0][cenbin]->Fill(bPassTof, p.perp());
         mHFTTofMatchEff[0][3]->Fill(bPassTof, p.perp());
         mHFTTofBetaEff[0][cenbin]->Fill(bPassBeta, p.perp());
         mHFTTofBetaEff[0][3]->Fill(bPassBeta, p.perp());

         if (fabs(nsigma_k) < cuts::nSigCutTight) {
            bPassTof  = index2tof >= 0;
            bPassBeta = beta > 0;
            mHFTTightTofMatchEff[0][cenbin]->Fill(bPassTof, p.perp());
            mHFTTightTofMatchEff[0][3]->Fill(bPassTof, p.perp());
            mHFTTightTofBetaEff[0][cenbin]->Fill(bPassBeta, p.perp());
            mHFTTightTofBetaEff[0][3]->Fill(bPassBeta, p.perp());
         }
      }

      if (fabs(nsigma_pi) < cuts::nSigmaCut) {
         bPassTof  = index2tof >= 0;
         bPassBeta = beta > 0;
         mHFTTofMatchEff[1][cenbin]->Fill(bPassTof, p.perp());
         mHFTTofMatchEff[1][3]->Fill(bPassTof, p.perp()); // 0-80%
         mHFTTofBetaEff[1][cenbin]->Fill(bPassBeta, p.perp());
         mHFTTofBetaEff[1][3]->Fill(bPassBeta, p.perp());

         if (fabs(nsigma_pi) < cuts::nSigCutTight) {
            bPassTof  = index2tof >= 0;
            bPassBeta = beta > 0;
            mHFTTightTofMatchEff[1][cenbin]->Fill(bPassTof, p.perp());
            mHFTTightTofMatchEff[1][3]->Fill(bPassTof, p.perp()); // 0-80%
            mHFTTightTofBetaEff[1][cenbin]->Fill(bPassBeta, p.perp());
            mHFTTightTofBetaEff[1][3]->Fill(bPassBeta, p.perp());
         }
      }

      // ++++++++++++END FILL TOF MATCH EFF+++++++++++++++++

      Bool_t c_decay = false;

      if ( fabs(dca) > cuts::trkDca && p.perp() > cuts::trkPt) c_decay = true; // dca>0.005 && pt>0.3

      Bool_t isPion   = false;
      Bool_t isKaon   = false;

      if (beta > 0) {
         if (fabs(1 / beta - 1 / beta_pi) < 0.04) isPion   = true;

         if (fabs(1 / beta - 1 / beta_k) < 0.04)  isKaon   = true;

         mBetaCorr[i]  = 1 / beta - 1 / beta_k;
         mBetaCorr2[i] = 1 / beta - 1 / beta_pi;
      }
      else {
         if (fabs(nsigma_pi) < cuts::nSigmaPion)  isPion   = true; // nsigma_pi = 3.0

         if (fabs(nsigma_k) < cuts::nSigmaKaon)   isKaon   = true; // nsigma_k = 2.0

         mBetaCorr[i]  = -999.;
         mBetaCorr2[i] = -999.;
      }

      if (c_decay && isKaon) {c_kaons.push_back(i); mTrkCounter->Fill("Kaon", 1);}

      if (c_decay && isPion) {c_pions.push_back(i); mTrkCounter->Fill("Pion", 1);}

   }

   TVector2 Q_before_recenter;
   Q_before_recenter.Set(Qx, Qy);
   Float_t  psi_before_recenter = Q_before_recenter.Phi() / 2;
   TVector2 Q_with_recenter     = Q();
   Float_t  psi_with_recenter   = Q_with_recenter.Phi() / 2;

   mEP_wo_recenter_wo_Eta_Gap->Fill(psi_before_recenter);
   mEP_w_recenter_wo_Eta_Gap->Fill(psi_with_recenter);

   mNKPi->Fill(c_pions.size(), c_kaons.size());

   v0Tree.mRunId       = mPicoEvent->runId();
   v0Tree.mEvtId       = mPicoEvent->eventId();
   v0Tree.mVx 	       = pVtx.x();
   v0Tree.mVy 	       = pVtx.y();
   v0Tree.mVz 	       = pVtx.z();
   v0Tree.mRefMult     = mPicoEvent->refMult();
   v0Tree.mGRefMult    = mPicoEvent->grefMult();
   v0Tree.mVzVpd       = vzVpd;
   // v0Tree.mQx_west     = cossum_etawest;
   // v0Tree.mQy_west     = sinsum_etawest;
   // v0Tree.mQx_east     = cossum_etaeast;
   // v0Tree.mQy_east     = sinsum_etaeast;
   v0Tree.mZdcX        = mPicoEvent->ZDCx();
   v0Tree.mBbcX        = mPicoEvent->BBCx();
   v0Tree.mReWeight    = reweight;
   v0Tree.mGRefMultCor = grefmultCor;
   v0Tree.mCen16       = cen16;
   v0Tree.mCen9        = cen9;

   int nV0 = 0;

   for (size_t i = 0; i < c_kaons.size(); i++) { // Kaon +
      for (size_t j = i + 1; j < c_kaons.size(); j++) { // Kaon -
         for (size_t k = 0; k < c_pions.size(); k++) { // Pion
            Int_t pair_flag = makePair(mPicoDst, c_kaons[i], c_kaons[j], c_pions[k], pVtx, B, 0, nV0); // 0 - nothing, 1-bad phi candidate ,2-good candidate

            if (pair_flag == 2) nV0++;
            else if (pair_flag == 1) break;
         }
      }
   }

   v0Tree.mNV0 = nV0;
   mTree->Fill();
#endif
   return kStOK;
}

Bool_t StMyAnalysisMaker::isGoodTrack(StPicoTrack *t)
{
   if (!t) return kFALSE;

   if (t->nHitsFit() <= 20) return kFALSE;

   if ((1.0 * t->nHitsFit()) / t->nHitsMax() < 0.51) return kFALSE;

   return kTRUE;
}

bool StMyAnalysisMaker::isGoodEvent() const
{
   return fabs(mPicoEvent->primaryVertex().z()) < cuts::vz &&
          fabs(mPicoEvent->primaryVertex().z() - mPicoEvent->vzVpd()) < cuts::vzVpdVz;
}

bool StMyAnalysisMaker::isGoodTrigger() const
{
   for (auto trg : cuts::triggers) {
      if (mPicoEvent->isTrigger(trg)) return true;
   }

   return false;
}

// Method should load Q vector stuff from Hao, needs fixing
// _________________________________________________________
bool StMyAnalysisMaker::loadEventPlaneCorr()
{
   if (!getAcceptEvent()) {
      LOG_WARN << "StMyAnalysisMaker::THistograms and TProiles NOT found! shoudl check the input Qvector files From HaoQiu ! Skipping this run! " << endm;
      return kFALSE;
   }

   return kTRUE;
}


Int_t StMyAnalysisMaker::makePair(StPicoDst *picoDst, int i1, int i2, int i3, StThreeVectorF vtx, Double_t B, int in_flag, int iV0)
{
   if (!picoDst) return 0; mPairCounter->Fill("AllPair", 1);

   StPicoTrack *t1 = (StPicoTrack *)picoDst->track(i1);
   StPicoTrack *t2 = (StPicoTrack *)picoDst->track(i2);
   StPicoTrack *t3 = (StPicoTrack *)picoDst->track(i3);

   if (!t1 || !t2 || !t3) return 0;

   int q1 = t1->charge();
   int q2 = t2->charge();
   int q3 = t3->charge();

   int flag = in_flag;		// 0

   if (q1 * q2 == -1 && q3 == 1 ) 	    flag = 1; //+-+ Ds+

   if (q1 * q2 == -1 && q3 == -1) 	    flag = 2; //+-- Ds-

   if (q1 == 1 && q2 == 1 && q3 == -1)   flag = 3; //++- for bkg

   if (q1 == -1 && q2 == -1 && q3 == -1) flag = 4; //--- for bkg

   if (q1 == 1 && q2 == 1 && q3 == 1)     flag = 5; //+++ for bkg

   if (q1 == -1 && q2 == -1 && q3 == 1)  flag = 6; //--+ for bkg

   if (flag == 0) return 0;

   if ((t1->id() == t2->id()) || (t1->id() == t3->id()) || (t2->id() == t3->id())) return 0; mPairCounter->Fill("UniId", 1);

   StThreeVectorF p1(mMomX[i1], mMomY[i1], mMomZ[i1]);
   StThreeVectorF p2(mMomX[i2], mMomY[i2], mMomZ[i2]);
   StThreeVectorF p3(mMomX[i3], mMomY[i3], mMomZ[i3]);

   StThreeVectorF o1(mDcaPosX[i1], mDcaPosY[i1], mDcaPosZ[i1]);
   StThreeVectorF o2(mDcaPosX[i2], mDcaPosY[i2], mDcaPosZ[i2]);
   StThreeVectorF o3(mDcaPosX[i3], mDcaPosY[i3], mDcaPosZ[i3]);

   StPhysicalHelixD h1(p1, o1, B * kilogauss, q1);
   StPhysicalHelixD h2(p2, o2, B * kilogauss, q2);
   StPhysicalHelixD h3(p3, o3, B * kilogauss, q3);

   StPhysicalHelixD h1_s(p1, o1, 0, q1);// straight line method.
   StPhysicalHelixD h2_s(p2, o2, 0, q2);
   StPhysicalHelixD h3_s(p3, o3, 0, q3);

   pair<double, double> s12 = h1_s.pathLengths(h2_s);
   StThreeVectorF dcaP1_12 = h1_s.at(s12.first);
   StThreeVectorF dcaP2_12 = h2_s.at(s12.second);
   float dcaDaughters_12 = (dcaP1_12 - dcaP2_12).mag();

   pair<double, double> s13 = h1_s.pathLengths(h3_s);
   StThreeVectorF dcaP1_13 = h1_s.at(s13.first);
   StThreeVectorF dcaP3_13 = h3_s.at(s13.second);
   float dcaDaughters_13 = (dcaP1_13 - dcaP3_13).mag();

   pair<double, double> s23 = h2_s.pathLengths(h3_s);
   StThreeVectorF dcaP2_23 = h2_s.at(s23.first);
   StThreeVectorF dcaP3_23 = h3_s.at(s23.second);
   float dcaDaughters_23 = (dcaP2_23 - dcaP3_23).mag();

   Float_t dcaDaughtersArr[3] = {dcaDaughters_12, dcaDaughters_13, dcaDaughters_23};
   float dcaDaughters = TMath::MaxElement(3, dcaDaughtersArr);

   if (dcaDaughters > cuts::dcaDaughters) return 0;

   StThreeVectorF v0   = (dcaP1_12 + dcaP2_12 + dcaP1_13 + dcaP3_13 + dcaP2_23 + dcaP3_23) * 0.1666667;

   double pathLength1 = h1.pathLength(v0);
   double pathLength2 = h2.pathLength(v0);
   double pathLength3 = h3.pathLength(v0);

   StThreeVectorF dcaP1 = h1.at(pathLength1);
   StThreeVectorF dcaP2 = h2.at(pathLength2);
   StThreeVectorF dcaP3 = h3.at(pathLength3);

   double secsigma = sqrt((dcaP1 - v0).mag2() + (dcaP2 - v0).mag2() + (dcaP3 - v0).mag2());

   // if (secsigma > cuts::secSigma) return 0; // require secsigma<300 um, this one is correlated with dcaDaughters cuts. see fast simulation.

   StThreeVectorF mom1 = h1.momentumAt(pathLength1, B * kilogauss);
   StThreeVectorF mom2 = h2.momentumAt(pathLength2, B * kilogauss);
   StThreeVectorF mom3 = h3.momentumAt(pathLength3, B * kilogauss);

   float e1 = TMath::Sqrt(mom1.mag2() + ParMass[0][0] * ParMass[0][0]);
   float e2 = TMath::Sqrt(mom2.mag2() + ParMass[0][1] * ParMass[0][1]);
   float e3 = TMath::Sqrt(mom3.mag2() + ParMass[0][2] * ParMass[0][2]);

   StLorentzVector<Float_t> fourMom1(mom1, e1);
   StLorentzVector<Float_t> fourMom2(mom2, e2);
   StLorentzVector<Float_t> fourMom3(mom3, e3);

   StLorentzVector<Float_t> fourMom_v0  = fourMom1 + fourMom2 + fourMom3;
   StLorentzVector<Float_t> fourMom_phi = fourMom1 + fourMom2; // K+, K-
   // float decayL_phi;

   // phi meson pair cuts
   if (fabs(fourMom_phi.m() - M_PHI) > cuts::absKKMass) return 1; // |Mass-M_PHI|<0.02GeV/c2

   StThreeVectorF mom_v0 = mom1 + mom2 + mom3;
   float angle   = TMath::ACos((v0 - vtx).dot(mom_v0) / (v0 - vtx).mag() / mom_v0.mag());
   float dca2vtx = (v0 - vtx).mag() * TMath::Sin(angle);
   float decayL  = (v0 - vtx).mag();

   // 3-body pair cuts
   if ( fourMom_v0.m() < cuts::minMass || fourMom_v0.m() > cuts::maxMass ) return 0; mPairCounter->Fill("DsMassCut", 1); // 1.8<Mass<2.2 GeV/c2

   if (fabs(fourMom_v0.rapidity()) > cuts::absEta)                         return 0; // |y|<1

   if ( decayL < cuts::decayLength )        	      			   return 0; // DecayLength > 50 um

   if (TMath::Cos(angle) < cuts::cosTheta ) 	      			   return 0; // cos(theta)>0.9

   StThreeVectorF dca2Vtx1(mDcaPosX[i1] - vtx.x(), mDcaPosY[i1] - vtx.y(), mDcaPosZ[i1] - vtx.z());
   StThreeVectorF dca2Vtx2(mDcaPosX[i2] - vtx.x(), mDcaPosY[i2] - vtx.y(), mDcaPosZ[i2] - vtx.z());
   StThreeVectorF dca2Vtx3(mDcaPosX[i3] - vtx.x(), mDcaPosY[i3] - vtx.y(), mDcaPosZ[i3] - vtx.z());

   Int_t TofFlag = 0;

   if (fabs(mBetaCorr[i1]) < 0.04)  TofFlag |= (1 << 0);

   if (fabs(mBetaCorr[i2]) < 0.04)  TofFlag |= (1 << 1);

   if (fabs(mBetaCorr2[i3]) < 0.04) TofFlag |= (1 << 2);

   StLorentzVector<Float_t> fourMom_rev(-fourMom_v0.px(), -fourMom_v0.py(), -fourMom_v0.pz(), fourMom_v0.e());
   StLorentzVector<Float_t> pionMomStar = fourMom3.boost(fourMom_rev);
   Float_t costhetastarpion = TMath::Cos(pionMomStar.vect().angle(fourMom_v0.vect()));
   Float_t cos_openangle_kk = TMath::Cos(fourMom1.vect().angle(fourMom2.vect()));

   StLorentzVector<Float_t> fourMom_kk_rev(-fourMom_phi.px(), -fourMom_phi.py(), -fourMom_phi.pz(), fourMom_phi.e());
   StLorentzVector<Float_t> kaonMomStarkk  = fourMom1.boost(fourMom_kk_rev);
   StLorentzVector<Float_t> pionMomStarkk = fourMom3.boost(fourMom_kk_rev);
   Float_t costhetaprikaon = TMath::Cos(kaonMomStarkk.vect().angle(pionMomStarkk.vect()));

   v0Tree.mFlag[iV0] 	      	    = flag;
   v0Tree.mDca1[iV0] 	      	    = dca2Vtx1.mag();
   v0Tree.mDca2[iV0] 	      	    = dca2Vtx2.mag();
   v0Tree.mDca3[iV0] 	      	    = dca2Vtx3.mag();
   v0Tree.mPt1[iV0]  	      	    = mom1.perp();
   v0Tree.mPt2[iV0]  	      	    = mom2.perp();
   v0Tree.mPt3[iV0]  	      	    = mom3.perp();
   v0Tree.mPhi1[iV0] 		    = mom1.phi();
   v0Tree.mPhi2[iV0] 		    = mom2.phi();
   v0Tree.mPhi3[iV0] 		    = mom3.phi();
   v0Tree.mTofFlag[iV0]        	    = TofFlag;
   v0Tree.mDcaDaughters[iV0]        = dcaDaughters;
   v0Tree.mSecSigma[iV0]       	    = secsigma;
   v0Tree.mV0x_HS[iV0] 	      	    = v0.x();
   v0Tree.mV0y_HS[iV0] 	      	    = v0.y();
   v0Tree.mV0z_HS[iV0] 	      	    = v0.z();
   v0Tree.mPt_HS[iV0]  	      	    = fourMom_v0.perp();
   v0Tree.mEta_HS[iV0] 	      	    = fourMom_v0.pseudoRapidity();
   v0Tree.mPhi_HS[iV0] 	      	    = fourMom_v0.phi();
   v0Tree.mMass_HS[iV0]        	    = fourMom_v0.m();
   v0Tree.mTheta_HS[iV0]       	    = angle;
   v0Tree.mDca2Vtx_HS[iV0]     	    = dca2vtx;
   v0Tree.mDecayL_HS[iV0]      	    = decayL;
   v0Tree.mMassKK_HS[iV0]      	    = fourMom_phi.m();
   v0Tree.mPtKK_HS[iV0]        	    = fourMom_phi.perp();
   v0Tree.mCosThetaKK_HS[iV0]       = cos_openangle_kk; // Angle between kk
   v0Tree.mCosThetaPriKaon_HS[iV0]  = costhetaprikaon;  // Angle between kaon and pion in kk rest frame.
   v0Tree.mCosThetaStarPion_HS[iV0] = costhetastarpion; // Angle between pion in Ds rest frame and Ds momentum in lab frame.


   // Eta Gap  + auto-correction rejection
   int iEta = (int)(v0Tree.mEta_HS[iV0] * 10 + 10); // eta bin
   int nEtaGaps = 3; // eta gap is 3 (from Hao's D0 v2 analysis.)
   TVector2 QSubEtaGap = QEtaGap(iEta, nEtaGaps);
   int iEta_ = iEta;

   if (iEta_ < nEtaGaps) iEta_ = nEtaGaps - 1;

   if (iEta_ > 20 - nEtaGaps) iEta_ = 20 - nEtaGaps;

   int iEtaKaon1 = (int)(mom1.pseudoRapidity() * 10 + 10);
   int iEtaKaon2 = (int)(mom2.pseudoRapidity() * 10 + 10);
   int iEtaPion  = (int)(mom3.pseudoRapidity() * 10 + 10);

   if (fabs(iEtaPion - iEta_) >= nEtaGaps)
      QSubEtaGap -= q(i3);

   if (fabs(iEtaKaon1 - iEta_) >= nEtaGaps)
      QSubEtaGap -= q(i1);

   if (fabs(iEtaKaon2 - iEta_) >= nEtaGaps)
      QSubEtaGap -= q(i2);

   if (QSubEtaGap.Mod() == 0) {
//      cout << "QSubEtaGap.Mod()==0  nEtaGaps: " << nEtaGaps << endl;
      return 0;		// normal return
   }

   float dPhiEtaGap = v0Tree.mPhi_HS[iV0] - QSubEtaGap.Phi() / 2;

   while (dPhiEtaGap < 0) dPhiEtaGap += TMath::Pi();

   while (dPhiEtaGap >= TMath::Pi()) dPhiEtaGap -= TMath::Pi();

   v0Tree.mDPhiEtaGap[iV0] = dPhiEtaGap;
   mEP_w_recenter_w_Eta_Gap->Fill(QSubEtaGap.Phi() / 2.);
   return 2;
}

// -------------------------------
// event plane related function 
// -------------------------------

void StMyAnalysisMaker::getEventInfo()
{

  //Remove bad vertices
  mVertexPos = mPicoEvent->primaryVertex();

  mCent  = mGRefMultCorrUtil->getCentralityBin9();

  mAcceptEvent = false;

  mBField = mPicoEvent->bField();

  bool isVPDMB5 = kFALSE;
  for (auto trg : cuts::triggers) {
    if (mPicoEvent->isTrigger(trg)) isVPDMB5 = kTRUE;
  }

  if (!(isVPDMB5))
    {
      return;
    }

  if (TMath::Abs(mVertexPos.z()) > EventPlaneConstants::vzMax) return;
  if (TMath::Abs(mVertexPos.z() - mPicoEvent->vzVpd()) > EventPlaneConstants::deltaVzMax) return;
  if (mCent < 0 || mCent > 9) return;

  mAcceptEvent = true;
}

void StMyAnalysisMaker::getRunInfo(int const runNumber)
{
  mRunNumber = runNumber;

  char fileName[256];
  sprintf(fileName, "%s/%i.qVector.root", EventPlaneConstants::qVectorRunDir.Data(), mRunNumber);
  TFile* fQVector = new TFile(fileName);
  if(fQVector->IsZombie())
    {
      int dayNumber = mRunNumber%1000000/1000;
      sprintf(fileName, "%s/%03d.qVector.root", EventPlaneConstants::qVectorDayDir.Data(), dayNumber);
      delete fQVector;
      fQVector = new TFile(fileName);
      if(fQVector->IsZombie())
	{
	  cout<<"can not load run or day qVector file: "<<mRunNumber<<endl;
	  return;
	}
    }
  cout << "load qVector file: " << fileName << endl;

  fQVector->GetObject("prfQxCentEtaPlus", prfQxCentEtaPlus);
  if (!prfQxCentEtaPlus)
    {
      LOG_INFO << "StMyAnalysisMaker::THistograms and TProiles NOT found! shoudl check the files From HaoQiu" << endm;
      mAcceptQvectorFile = false;
      mAcceptQvectorFiletmp = false;
      return;
    }
  else
    {
      mAcceptQvectorFile = true;
      mAcceptQvectorFiletmp = true;
    }

  prfQxCentEtaPlus = (TProfile*)fQVector->Get("prfQxCentEtaPlus")->Clone("prfQxCentEtaPlus");
  prfQyCentEtaPlus = (TProfile*)fQVector->Get("prfQyCentEtaPlus")->Clone("prfQyCentEtaPlus");
  prfQxCentEtaMinus = (TProfile*)fQVector->Get("prfQxCentEtaMinus")->Clone("prfQxCentEtaMinus");
  prfQyCentEtaMinus = (TProfile*)fQVector->Get("prfQyCentEtaMinus")->Clone("prfQyCentEtaMinus");

  prfQxCentEtaPlus->SetDirectory(0);
  prfQyCentEtaPlus->SetDirectory(0);
  prfQxCentEtaMinus->SetDirectory(0);
  prfQyCentEtaMinus->SetDirectory(0);

  fQVector->Close();
  delete fQVector;
}

/*----------------------------------------------------------------------------------------------------------------------*/
int StMyAnalysisMaker::calculateEventPlane()
{
  memset(qxTracks, 0, maxNTracks * sizeof(float));
  memset(qyTracks, 0, maxNTracks * sizeof(float));

  // pre-loop to count tracks for event plane, prepare for shuffle
  int nTracksForEventPlane = 0;
  for (unsigned short iTrack = 0; iTrack < mPicoDst->numberOfTracks(); ++iTrack)
    {
      StPicoTrack* picoTrack = (StPicoTrack*) mPicoDst->track(iTrack);
      if (!picoTrack)
	{
	  break;
	}

      if (picoTrack->nHitsFit() < EventPlaneConstants::nHitsFitMin) continue;
      if (1.0*picoTrack->nHitsFit()/picoTrack->nHitsMax() < EventPlaneConstants::nHitsFitRatio) continue;

      StPhysicalHelix helix = picoTrack->dcaGeometry().helix();
      float dca = helix.geometricSignedDistance(mVertexPos);
      if (TMath::Abs(dca) > EventPlaneConstants::dcaMaxEventPlane) continue;

      float pathLengthToPrimaryVertex = helix.pathLength(mVertexPos.x(), mVertexPos.y());
      // StThreeVectorF momentum = helix.momentumAt(pathLengthToPrimaryVertex, mBField * kilogauss);
      StThreeVectorF momentum = picoTrack->pMom(); // Use primary track 
      float pt = momentum.perp();
      float eta = momentum.pseudoRapidity();
      if (fabs(eta) > EventPlaneConstants::etaMaxEventPlane) continue;
      if (pt < EventPlaneConstants::ptMinEventPlane || pt > EventPlaneConstants::ptMaxEventPlane) continue;

      nTracksForEventPlane++;
    }

  int indexTrack[nTracksForEventPlane];
  int Scount = nTracksForEventPlane / 2;
  for (int q = 0; q < nTracksForEventPlane; ++q) indexTrack[q] = q;
  random_shuffle(indexTrack, indexTrack + nTracksForEventPlane); // Used to calculate event plane resolution.,
  int iTrackForEventPlane = 0;

  // track loop
  float Qx = 0., Qy = 0.;
  float Qx1 = 0., Qy1 = 0., Qx2 = 0., Qy2 = 0.;
  float QxEtaPlus = 0., QyEtaPlus = 0., QxEtaMinus = 0., QyEtaMinus = 0.;
  float QxEtaPlusGap005 = 0., QyEtaPlusGap005 = 0., QxEtaMinusGap005 = 0., QyEtaMinusGap005 = 0.;
  float QxEta[20], QyEta[20];
  memset(QxEta, 0, 20*sizeof(float));
  memset(QyEta, 0, 20*sizeof(float));
  float vertexZ = mVertexPos.z();
  for (unsigned short iTrack = 0; iTrack < mPicoDst->numberOfTracks(); ++iTrack)
    {
      StPicoTrack* picoTrack = (StPicoTrack*) mPicoDst->track(iTrack);
      if (!picoTrack)
	{
	  break;
	}

      if (mAcceptEvent) hNHitsFit->Fill(picoTrack->nHitsFit());
      if (picoTrack->nHitsFit() < EventPlaneConstants::nHitsFitMin) continue;
      if (1.0*picoTrack->nHitsFit()/picoTrack->nHitsMax() < EventPlaneConstants::nHitsFitRatio) continue;

      StPhysicalHelix helix = picoTrack->dcaGeometry().helix();
      float dca = helix.geometricSignedDistance(mVertexPos);
      if (mAcceptEvent) hDca->Fill(dca);
      if (TMath::Abs(dca) > EventPlaneConstants::dcaMaxEventPlane) continue;

      float pathLengthToPrimaryVertex = helix.pathLength(mVertexPos.x(), mVertexPos.y());
      // StThreeVectorF momentum = helix.momentumAt(pathLengthToPrimaryVertex, mBField * kilogauss);
      StThreeVectorF momentum = picoTrack->pMom();
      float pt = momentum.perp();
      float eta = momentum.pseudoRapidity();
      float phi = momentum.phi();
      if (mAcceptEvent) hEta->Fill(eta);
      if (mAcceptEvent) hPt->Fill(pt);
      if (fabs(eta) > EventPlaneConstants::etaMaxEventPlane) continue;
      if (pt < EventPlaneConstants::ptMinEventPlane || pt > EventPlaneConstants::ptMaxEventPlane) continue;

      if (mAcceptEvent && eta > 0 && vertexZ > 0) hPhiCentEtaPlusZPlus->Fill(mCent, phi);
      if (mAcceptEvent && eta > 0 && vertexZ < 0) hPhiCentEtaPlusZMinus->Fill(mCent, phi);
      if (mAcceptEvent && eta < 0 && vertexZ > 0) hPhiCentEtaMinusZPlus->Fill(mCent, phi);
      if (mAcceptEvent && eta < 0 && vertexZ < 0) hPhiCentEtaMinusZMinus->Fill(mCent, phi);

      float qx = cos(2 * phi) * pt;
      float qy = sin(2 * phi) * pt;

      // Recentering
      if (eta > 0)
	{
	  qx -= prfQxCentEtaPlus->GetBinContent(mCent + 1);//minus mean QX 
	  qy -= prfQyCentEtaPlus->GetBinContent(mCent + 1); // Qy - <Qy>
	}
      else
	{
	  qx -= prfQxCentEtaMinus->GetBinContent(mCent + 1);
	  qy -= prfQyCentEtaMinus->GetBinContent(mCent + 1);
	}
      
      Qx += qx;			// sum(qx), Used for event plane calculation, already did recentering.
      Qy += qy;			// sum(qy)

      // used for event plance resolution calculation.
      if (indexTrack[iTrackForEventPlane] >= Scount)
	{
	  Qx1 += qx;
	  Qy1 += qy;
	}
      else
	{
	  Qx2 += qx;
	  Qy2 += qy;
	}
      
      if (eta > 0)
	{
	  QxEtaPlus += qx;
	  QyEtaPlus += qy;
	  if(eta > 0.05)
	    {
	      QxEtaPlusGap005 += qx;
	      QyEtaPlusGap005 += qy;
	    }
	}
      else
	{
	  QxEtaMinus += qx;
	  QyEtaMinus += qy;
	  if(eta < -0.05)
	    {
	      QxEtaMinusGap005 += qx;
	      QyEtaMinusGap005 += qy;
	    }
	}

      int iEta = int(eta*10+10);
      QxEta[iEta] += qx;
      QyEta[iEta] += qy;

      qxTracks[iTrack] = qx;	// already with recenter correction .
      qyTracks[iTrack] = qy;

      iTrackForEventPlane++;
    }//loop thru picoTracks

  assert(iTrackForEventPlane == nTracksForEventPlane);

  mQ.Set(Qx, Qy);		// sum all Qx,Qy
  mQ1.Set(Qx1, Qy1);		// sum half Qx,Qy
  mQ2.Set(Qx2, Qy2);
  mQEtaPlus.Set(QxEtaPlus, QyEtaPlus); // sum of eta>0 
  mQEtaMinus.Set(QxEtaMinus, QyEtaMinus); // sum of eta<0
  mQEtaPlusGap005.Set(QxEtaPlusGap005, QyEtaPlusGap005); // sum of eta>0.05
  mQEtaMinusGap005.Set(QxEtaMinusGap005,QyEtaMinusGap005); // sum of eta<-0.05
  for(int i=0; i<20; i++)
    mQEta[i].Set(QxEta[i], QyEta[i]); // Q vector in eta bin.

  if (mQ.Mod2() == 0 || mQ1.Mod2() == 0 || mQ2.Mod2() == 0 || mQEtaPlus.Mod2() == 0 || mQEtaMinus.Mod2() == 0)
    {
      // cout << "0 Q: mQ " << ", mQ1" << ", mQ2" << ", mQEtaPlus" << ", mQEtaMinus" << ", mCent" << ", nTracksForEventPlane"<< ", refMult" << ", grefMult" << ", numberOfTracks" << ", eventId"<< ", pvz" << ", vzVpd"<< ", ZDCx" << endl;
      // cout << "0 Q: " << mQ.Mod2() << " " << mQ1.Mod2() << " " << mQ2.Mod2() << " " << mQEtaPlus.Mod2() << " " << mQEtaMinus.Mod2() << " " << mCent << " " << nTracksForEventPlane << " " << mPicoEvent->refMult() << " " << mPicoEvent->grefMult() << " " << mPicoDst->numberOfTracks() << " " << mPicoEvent->eventId() << " " << mPicoDst->event()->primaryVertex().z() << " " << mPicoDst->event()->vzVpd() << " " << mPicoDst->event()->ZDCx() / 1.0e3 << endl;
      return 1;
    }

  mEventPlane = mQ.Phi() * 0.5;
  mEventPlane1 = mQ1.Phi() * 0.5;
  mEventPlane2 = mQ2.Phi() * 0.5;
  mEventPlaneEtaPlus = mQEtaPlus.Phi() * 0.5;
  mEventPlaneEtaMinus = mQEtaMinus.Phi() * 0.5;
  mResolutionRandom = cos(2.*(mEventPlane1 - mEventPlane2)); // correlation, similar with two particle correlation
  mResolutionEta = cos(2.*(mEventPlaneEtaPlus - mEventPlaneEtaMinus)); // in Eta direction, should be a flat distribution.

  if (mAcceptEvent)
    {
      // hQyQxCent->Fill(mCent, Qx, Qy);
      hEventPlaneCent->Fill(mCent, getEventPlane());

      // hQyQx1Cent->Fill(mCent, Qx1, Qy1);
      hEventPlane1Cent->Fill(mCent, mEventPlane1);

      // hQyQx2Cent->Fill(mCent, Qx2, Qy2);
      hEventPlane2Cent->Fill(mCent, mEventPlane2);

      // hQyQxEtaPlusCent->Fill(mCent, QxEtaPlus, QyEtaPlus);
      hEventPlaneEtaPlusCent->Fill(mCent, mEventPlaneEtaPlus);

      // hQyQxEtaMinusCent->Fill(mCent, QxEtaMinus, QyEtaMinus);
      hEventPlaneEtaMinusCent->Fill(mCent, mEventPlaneEtaMinus);

      prfCosResolutionRandomCent->Fill(mCent, mResolutionRandom);
      prfCosResolutionEtaCent->Fill(mCent, mResolutionEta);
    }
  return 0;
}

float StMyAnalysisMaker::getEventPlane(int nTracksToExclude, int* indexTracksToExclude) const
{
  TVector2 Qsub = mQ;
  for (int i = 0; i < nTracksToExclude; i++)
    {
      TVector2 qTrack(qxTracks[indexTracksToExclude[i]], qyTracks[indexTracksToExclude[i]]);
      Qsub -= qTrack;
    }
  return Qsub.Phi() * 0.5;
}

TVector2 StMyAnalysisMaker::QEtaGap(int iEta, int nEtaGaps) const
{
  TVector2 QEtaGap_(0, 0);
  int iEta_ = iEta;
  if(iEta_ < nEtaGaps-1) iEta_ = nEtaGaps-1;
  if(iEta_ > 20-nEtaGaps) iEta_= 20-nEtaGaps;
  for(int i=0; i<20; i++)
    {
      if(fabs(i-iEta_) >= nEtaGaps) QEtaGap_ += mQEta[i];
    }
  return QEtaGap_;
}

void StMyAnalysisMaker::calculateHadronV2() const
{
  for (unsigned short iTrack = 0; iTrack < mPicoDst->numberOfTracks(); iTrack++)
    {
      StPicoTrack* picoTrack = (StPicoTrack*) mPicoDst->track(iTrack);
      if (!picoTrack)
	{
	  break;
	}

      if (picoTrack->nHitsFit() < EventPlaneConstants::nHitsFitMin) continue;
      if (1.0*picoTrack->nHitsFit()/picoTrack->nHitsMax() < EventPlaneConstants::nHitsFitRatio) continue;

      StPhysicalHelix helix = picoTrack->dcaGeometry().helix();
      float dca = helix.geometricSignedDistance(mVertexPos);
      if (TMath::Abs(dca) > EventPlaneConstants::dcaMaxEventPlane) continue;

      float pathLengthToPrimaryVertex = helix.pathLength(mVertexPos.x(), mVertexPos.y());
      // StThreeVectorF momentum = helix.momentumAt(pathLengthToPrimaryVertex, mBField * kilogauss);
      StThreeVectorF momentum = picoTrack->pMom();
      float pt = momentum.perp();
      float eta = momentum.pseudoRapidity();
      float phi = momentum.phi();
      if (fabs(eta) > EventPlaneConstants::etaMaxEventPlane) continue;
      if (pt < EventPlaneConstants::ptMinEventPlane || pt > EventPlaneConstants::ptMaxEventPlane) continue;

      float qx = qxTracks[iTrack];
      float qy = qyTracks[iTrack];
      TVector2 qTrack(qx, qy);
      TVector2 QSub = mQ - qTrack;
      float psi = QSub.Phi() / 2;

      float weight = mGRefMultCorrUtil->getWeight();

      // hHadronV2PtCent->Fill(pt, mCent, cos(2.*(phi - psi)), weight);

      // if (picoTrack->isHFTTrack())
      // hHadronHftV2PtCent->Fill(pt, mCent, cos(2.*(phi - psi)), weight);

      if (picoTrack->pMom().mag() > 0)
	hHadronPrimaryV2PtCent->Fill(pt, mCent, cos(2.*(phi - psi)), weight);

      // if (picoTrack->isHFTTrack() && picoTrack->pMom().mag() > 0)
      //    hHadronHftPrimaryV2PtCent->Fill(pt, mCent, cos(2.*(phi - psi)), weight);

      int iEta = (int)(eta*10+10);
      for(int nEtaGaps=0; nEtaGaps<8; nEtaGaps++)
	{
	  TVector2 QSubEtaGap = QEtaGap(iEta, nEtaGaps);
	  int iEta_ = iEta;
	  if(iEta_ < nEtaGaps) iEta_ = nEtaGaps-1;
	  if(iEta_ > 20-nEtaGaps) iEta_= 20-nEtaGaps;
	  if(fabs(iEta-iEta_) >= nEtaGaps)
	    QSubEtaGap -= qTrack;
	  if(QSubEtaGap.Mod()==0) {cout<<"QSubEtaGap.Mod()==0  nEtaGaps: "<<nEtaGaps<<"  cent: "<<mCent<<endl; continue;}
	  float dPhiEtaGap = phi-QSubEtaGap.Phi()/2;
	  double toFill[4] = {pt, mCent+0.5, cos(2.*dPhiEtaGap), 0.1*nEtaGaps+0.05};
	  hHadronV2PtCentEtaGap->Fill(toFill, weight);

	}
    }
}

