//===============================
//Version: 1.0
//Time: Thu Jun  4 12:41:53 EDT 2015
//Author: Long Zhou
//Discribe: First version for Physics2 picoDst analysis

#ifndef StMyAnalysisMaker_h
#define StMyAnalysisMaker_h

#include "StMaker.h"
#include "StarClassLibrary/StThreeVectorF.hh"
#include "StEvent/StDcaGeometry.h"
#include "TVector2.h"
#include "TVector3.h"
#include "StThreeVectorF.hh"
#include "TNtuple.h"
class StPicoDst;
class StPicoDstMaker;
class StPicoEvent;
class StPicoTrack;
class TString;
class TH1F;
class TH1I;
class TH2F;
class TH3F;
class THn;
class TProfile;
class TTree;
class TNtuple;
class TFile;
class TEfficiency;
class StDcaGeometry;
class StRefMultCorr;

const int maxNTracks = 20000;

#define RUNALL 1
class StMyAnalysisMaker : public StMaker
{
public:
   StMyAnalysisMaker(const char *name, StPicoDstMaker *picoMaker, StRefMultCorr *grefmultCorrUtil, const char *outName);
   virtual ~StMyAnalysisMaker();

   virtual Int_t Init();
   virtual Int_t Make();
   virtual void  Clear(Option_t *opt = "");
   virtual Int_t Finish();

   Bool_t  isGoodEvent() const;
   Bool_t  isGoodTrigger() const;
   Bool_t  isGoodTrack(StPicoTrack *track);
   void    DeclareHistograms();
   void    DeclareEPHistograms();
   void    WriteHistograms();
   bool    loadEventPlaneCorr();

   Int_t  makePair(StPicoDst *picoDst, int i1, int i2, int i3, TVector3 vtx, Double_t B, int in_flag, int iV0);

   /* --------------------- */
   /* event plane relateed  */
   /* --------------------- */
   int   getCentrality() const;
   float getEventPlane(int nTracksToExclude = 0, int *indexTracksToExclude = 0) const;
   float getEventPlane1() const;
   float getEventPlane2() const;
   float getEventPlaneEtaPlus() const;
   float getEventPlaneEtaMinus() const;
   float getResolutionRandom() const;
   float getResolutionEta() const;
   void calculateHadronV2() const;
   int eventPlaneStatus() const;
   TVector2 Q() const;
   TVector2 QEtaPlusGap005() const;
   TVector2 QEtaMinusGap005() const;
   TVector2 QEtaGap(int iEta, int nEtaGaps) const;
   TVector2 QEta(int iEta) const;
   TVector2 q(int iTrack) const;

   int   getRunId() const;
   bool getAcceptEvent() const;

private:
   void getEventInfo();
   void getRunInfo(int runNumber);
   int calculateEventPlane();

   StPicoDstMaker *mPicoDstMaker;
   StPicoDst      *mPicoDst;
   StPicoEvent    *mPicoEvent;
   StRefMultCorr  *mGRefMultCorrUtil;

   Int_t      mFailedRunnumber;
   /* Int_t      mEventCounter; */
   TString    mOutName;
   TFile      *mOutputFile;
   double     sinsum_etaeast;
   double     cossum_etaeast;
   double     sinsum_etawest;
   double     cossum_etawest;
   TH1F* mh1Vz_EbyE = nullptr;
   TH1F* mh1EventID_EbyE = nullptr;
   TH1F* mh1Ntracks_EbyE = nullptr;
   TH1F* mh1Vz = nullptr;
   TH1F* mh1Cent = nullptr;
   TH1F* mh1CentWg = nullptr;
   TH1F* mh1gRefmultCor = nullptr;
   TH1F* mh1gRefmultCorWg = nullptr;
   TH2F* mh2CentVz = nullptr;
   TH2F* mh2CentVzWg = nullptr;
int nTracks_all = 0;
int event_num = 0;


   TH2F      *phiinvmass;
   TH1D      *mEventCounter;
   TH1D      *mPairCounter;
   TH1D      *mTrkCounter;

   TH2F      *mVzCorr;
   TH1F      *mVzDiff;
   TH1F      *mVzDiffZoom;
   TH2F      *mVxy;
   TH2F      *mRefMult;
   TH2F      *mGRefMult;
   TH2F      *mGRefMultCen;
   TH2F      *mGRefMultCorCen;
   TH1F      *mNEventsPerTrigger;

   TH2F      *mDcaXY_Pt_Pi;
   TH2F      *mDcaXY_Pt_K;
   TH2F      *mDcaXY_Pt_P;
   TH2F      *mDcaZ_Pt_Pi;
   TH2F      *mDcaZ_Pt_K;
   TH2F      *mDcaZ_Pt_P;

   TH2F      *mDca_Pt_Pi;
   TH2F      *mDca_Pt_K;
   TH2F      *mDca_Pt_P;

   TH2F      *mNHFTHitsPattern;

   TH2F      *mNTotalKPi;  // total Npi vs Nk
   TH2F      *mNPiPi;  // unlike-sign Npi vs Npi
   TH2F      *mNKPi;   // unlike-sign Nk vs Npi

   TH2F      *mInvBetavsP_Prim;
   TH2F      *mInvBetavsP_Add;

   TH2F      *mBTofPID_Pi;
   TH2F      *mBTofPID_K;
   TH2F      *mBTofPID_P;

   TH2F      *mPtEta_TPC_Pi;
   TH2F      *mPtEta_TPC_K;
   TH2F      *mPtEta_TPC_P;

   TH2F      *mPtEta_TofMatch_Pi;
   TH2F      *mPtEta_TofMatch_K;
   TH2F      *mPtEta_TofMatch_P;

   TH2F      *mPtEta_TofBeta_Pi;
   TH2F      *mPtEta_TofBeta_K;
   TH2F      *mPtEta_TofBeta_P;

   TH1F      *mEP_wo_recenter_wo_Eta_Gap;
   TH1F      *mEP_w_recenter_wo_Eta_Gap;
   TH1F      *mEP_w_recenter_w_Eta_Gap;

   TEfficiency *mHFTTofMatchEff[2][4];
   TEfficiency *mHFTTofBetaEff[2][4];
   TEfficiency *mHFTTightTofMatchEff[2][4];
   TEfficiency *mHFTTightTofBetaEff[2][4];
TNtuple *ntuple_track;
   TTree     *mTree; // tree

   struct   V0TREE {
      Int_t   mTrigger;
      Int_t   mRunId;
      Int_t   mEvtId;
      Float_t mVx;
      Float_t mVy;
      Float_t mVz;
      Float_t mVzVpd;
      Short_t mRefMult;
      Short_t mGRefMult;
      Float_t mZdcX;
      Float_t mBbcX;
      Float_t mQx_west;
      Float_t mQy_west;
      Float_t mQx_east;
      Float_t mQy_east;
      Float_t mReWeight;
      Float_t mGRefMultCor;
      Int_t   mCen16;
      Int_t   mCen9;
      Int_t   mNV0;
      UChar_t mFlag[maxNTracks];        //
      Float_t mDca1[maxNTracks];	    /* K+ */
      Float_t mDca2[maxNTracks];	    /* K- */
      Float_t mDca3[maxNTracks];	    /* pi */
      Float_t mPt1[maxNTracks];	    /* k+ pt */
      Float_t mPt2[maxNTracks];	    /* k- pt */
      Float_t mPt3[maxNTracks];	    /* pi pt */
      Float_t mPhi1[maxNTracks];	/* k+ phi */
      Float_t mPhi2[maxNTracks];	/* k- phi */
      Float_t mPhi3[maxNTracks];	/* pi phi */
      Int_t   mTofFlag[maxNTracks];
      Float_t mDcaDaughters[maxNTracks];
      //Float_t mSecSigma[maxNTracks];
      Float_t mV0x_HS[maxNTracks];
      Float_t mV0y_HS[maxNTracks];
      Float_t mV0z_HS[maxNTracks];
      Float_t mPt_HS[maxNTracks];
      Float_t mEta_HS[maxNTracks];
      Float_t rY_HS[maxNTracks];
      Float_t mPhi_HS[maxNTracks];
      Float_t mMass_HS[maxNTracks];
      Float_t mTheta_HS[maxNTracks];
     // Float_t mCosThetaKK_HS[maxNTracks];
      //Float_t mCosThetaPriKaon_HS[maxNTracks];
     // Float_t mCosThetaStarPion_HS[maxNTracks];
      Float_t mDca2Vtx_HS[maxNTracks];
      Float_t mDecayL_HS[maxNTracks];
      Float_t mPtKK_HS[maxNTracks];
      Float_t mMassKK_HS[maxNTracks];
      Float_t NhitsFit_Kaon1[maxNTracks];
      Float_t NhitsFit_Kaon2[maxNTracks];
      Float_t NhitsFit_Pion[maxNTracks];
 //     Float_t mDPhiEtaGap[maxNTracks];
   };
   V0TREE v0Tree;

   Float_t  mBetaCorr[maxNTracks];
   Float_t  mBetaCorr2[maxNTracks];
   Float_t  mDcaPosX[maxNTracks];
   Float_t  mDcaPosY[maxNTracks];
   Float_t  mDcaPosZ[maxNTracks];
   Float_t  mMomX[maxNTracks];
   Float_t  mMomY[maxNTracks];
   Float_t  mMomZ[maxNTracks];

   /* -------------------- */
   /* Event Plane related  */
   /* -------------------- */
   TH1I      *hNHitsFit;
   TH1F      *hDca;
   TH1F      *hEta;
   TH1F      *hPt;

   TH2F      *hOneOverBetaDiffKaonP;
   TH2F      *hOneOverBetaDiffPionP;

   //event plane and Q vector
   TH2F      *hPhiCentEtaPlusZPlus;
   TH2F      *hPhiCentEtaPlusZMinus;
   TH2F      *hPhiCentEtaMinusZPlus;
   TH2F      *hPhiCentEtaMinusZMinus;

   TH2F      *hEventPlaneCent;
   TH2F      *hEventPlane1Cent;
   TH2F      *hEventPlane2Cent;
   TH2F      *hEventPlaneEtaPlusCent;
   TH2F      *hEventPlaneEtaMinusCent;
   TH3F      *hQyQxCent;
   TH3F      *hQyQx1Cent;
   TH3F      *hQyQx2Cent;
   TH3F      *hQyQxEtaPlusCent;
   TH3F      *hQyQxEtaMinusCent;
   TProfile  *prfCosResolutionRandomCent;
   TProfile  *prfCosResolutionEtaCent;

   TH3F      *hHadronV2PtCent;
   TH3F      *hHadronHftV2PtCent;
   TH3F      *hHadronPrimaryV2PtCent;
   TH3F      *hHadronHftPrimaryV2PtCent;
   THn       *hHadronV2PtCentEtaGap;

   bool   mAcceptEvent;
   bool   mAcceptQvectorFile;
   bool   mAcceptQvectorFiletmp;

   int         mCent;
   int         mRunNumber;
   float       mBField;
   StThreeVectorF mVertexPos;
   int mEventPlaneStatus;
   float       mEventPlane, mEventPlane1, mEventPlane2, mEventPlaneEtaPlus, mEventPlaneEtaMinus;
   float       mResolutionRandom, mResolutionEta;
   TVector2    mQ, mQ1, mQ2, mQEtaPlus, mQEtaMinus, mQEtaPlusGap005, mQEtaMinusGap005;
   TVector2 mQEta[20];
   TProfile  *prfQxCentEtaPlus;
   TProfile  *prfQyCentEtaPlus;
   TProfile  *prfQxCentEtaMinus;
   TProfile  *prfQyCentEtaMinus;

   float      qxTracks[maxNTracks];
   float      qyTracks[maxNTracks];

   /////////////////////////////////////
   // Flag of different combinations
   // 0 - K- pi+ pi+   (D+ decay)
   // 1 - K+ pi- pi-   (D- decay)
   /////////////////////////////////////
   static const Int_t NFLAG = 2;
   static const Int_t PDGID[NFLAG][3];
   static const Double_t ParMass[NFLAG][3];
   static const Int_t NCENBINS = 3;
   static const Float_t CenEdg[NCENBINS + 1]; /* ={0,8,12,16} */
   ClassDef(StMyAnalysisMaker, 1)
};

inline int   StMyAnalysisMaker::getCentrality() const
{
   return mCent;
}
inline float StMyAnalysisMaker::getEventPlane1() const
{
   return mEventPlane1;
}
inline float StMyAnalysisMaker::getEventPlane2() const
{
   return mEventPlane2;
}
inline float StMyAnalysisMaker::getEventPlaneEtaPlus() const
{
   return mEventPlaneEtaPlus;
}
inline float StMyAnalysisMaker::getEventPlaneEtaMinus() const
{
   return mEventPlaneEtaMinus;
}
inline float StMyAnalysisMaker::getResolutionRandom() const
{
   return mResolutionRandom;
}
inline float StMyAnalysisMaker::getResolutionEta() const
{
   return mResolutionEta;
}
inline int   StMyAnalysisMaker::getRunId() const
{
   return mRunNumber;
}
inline bool  StMyAnalysisMaker::getAcceptEvent() const
{
   return mAcceptQvectorFile && mAcceptQvectorFiletmp;
}
inline int StMyAnalysisMaker::eventPlaneStatus() const
{
   return mEventPlaneStatus;
}
inline TVector2 StMyAnalysisMaker::Q() const
{
   return mQ;
}
inline TVector2 StMyAnalysisMaker::QEtaPlusGap005() const
{
   return mQEtaPlusGap005;
}
inline TVector2 StMyAnalysisMaker::QEtaMinusGap005() const
{
   return mQEtaMinusGap005;
}
inline TVector2 StMyAnalysisMaker::QEta(int iEta) const
{
   return mQEta[iEta];
}
inline TVector2 StMyAnalysisMaker::q(int iTrack) const
{
   TVector2 q_(qxTracks[iTrack], qyTracks[iTrack]);
   return q_;
}
#endif
