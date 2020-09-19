#include <limits>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>

#include "StNpeCuts.h"

#include "StLorentzVectorF.hh"
#include "StThreeVectorF.hh"
#include "StPhysicalHelixD.hh"
#include "phys_constants.h"
#include "SystemOfUnits.h"
#include "StBTofUtil/tofPathLength.hh"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "TMVA/MethodCuts.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "TFile.h"

ClassImp(StNpeCuts)

// _________________________________________________________
StNpeCuts::StNpeCuts() : StPicoCutsBase("NpeCutsBase"), mPicoDst2(NULL),
mElectronPairDcaDaughtersMax(std::numeric_limits<float>::max()),
mElectronJPsiDcaDaughtersMax(std::numeric_limits<float>::max()),
mElectronPairDecayLengthMin(std::numeric_limits<float>::min()), mElectronPairDecayLengthMax(std::numeric_limits<float>::max()),
mElectronPairCosThetaMin(std::numeric_limits<float>::min()),
mElectronPairAngle(std::numeric_limits<float>::min()),
mElectronPairThetaAngle(std::numeric_limits<float>::min()),
mElectronPairPhi(std::numeric_limits<float>::min()),
mElectronPairMassMin(std::numeric_limits<float>::min()), mElectronPairMassMax(std::numeric_limits<float>::max()),
mElectronJPsiMassMin(std::numeric_limits<float>::min()), mElectronJPsiMassMax(std::numeric_limits<float>::max()),
mElectronJPsiEta(std::numeric_limits<float>::max()),
mElectronJPsiDecayR(std::numeric_limits<float>::max()),
mElectronNHitsFitMax(std::numeric_limits<int>::max()),
mElectronNHitsRatio(std::numeric_limits<int>::max()),
mElectronNHitsdEdxMax(std::numeric_limits<int>::max()),
mElectronBsmdNEta(std::numeric_limits<int>::min()),
mElectronPtMin(std::numeric_limits<float>::min()),
mElectronBsmdNPhi(std::numeric_limits<int>::min()),
mElectronTofBeta(std::numeric_limits<float>::max()),
mElectronTofYLocal(std::numeric_limits<float>::max()),
mElectronTofFlag(std::numeric_limits<int>::max()),
mElectronPtMax(std::numeric_limits<float>::max()),
mElectronEtaMin(std::numeric_limits<float>::min()),
mElectronRequireHFT(false),
mElectronEtaMax(std::numeric_limits<float>::max()),
mElectronDca(std::numeric_limits<float>::max()),
mElectronDcaXY(std::numeric_limits<float>::max()),
mElectronTPCNSigmaElectronMin(std::numeric_limits<float>::min()),
mElectronTPCNSigmaElectronMax(std::numeric_limits<float>::max()),
mElectronBemcEoverPMin(std::numeric_limits<float>::min()),
mElectronBemcEoverPMax(std::numeric_limits<float>::max()),
mElectronBemcPhiDistMax(std::numeric_limits<float>::max()),
mElectronBemcZDistMax(std::numeric_limits<float>::max()),
mElectronBemcAssDistMax(std::numeric_limits<float>::max()),
mPartnerElectronNHitsFitMax(std::numeric_limits<int>::min()),
mPartnerElectronNHitsdEdxMax(std::numeric_limits<int>::min()),
mPartnerElectronPtMin(std::numeric_limits<float>::min()),
mPartnerElectronPtMax(std::numeric_limits<float>::max()),
mPartnerElectronEtaMin(std::numeric_limits<float>::min()),
mPartnerElectronEtaMax(std::numeric_limits<float>::max()),
mPartnerElectronRequireHFT(false),
mPartnerTPCNSigmaElectronMin(std::numeric_limits<float>::min()),
mPartnerTPCNSigmaElectronMax(std::numeric_limits<float>::max()),
mElectronPIDCutLow(std::numeric_limits<float>::min()),
mElectronPIDCutHigh(std::numeric_limits<float>::max()),
mElectronBemcPid(false),mElectronBsmdPid(false),mElectronTofPid(false),
mMVACut(std::numeric_limits<float>::min()),
mHTMVACut(std::numeric_limits<float>::min()),
mreader(NULL),
    mreader2(NULL),
    mMyHist(std::numeric_limits<bool>::min()),
    mPhoEHist(std::numeric_limits<bool>::min()),
    mSignalTree(std::numeric_limits<bool>::min()),
    mPhoETree(std::numeric_limits<bool>::min()),
    mBKGTree(std::numeric_limits<bool>::min()),
    mKsTree(std::numeric_limits<bool>::min()),
    mPhiTree(std::numeric_limits<bool>::min()),
    mEPTree(std::numeric_limits<bool>::min())
{  
    // -- default constructor
}

// _________________________________________________________
StNpeCuts::StNpeCuts(const Char_t *name) : StPicoCutsBase(name), mPicoDst2(NULL),
mElectronPairDcaDaughtersMax(std::numeric_limits<float>::max()),
mElectronJPsiDcaDaughtersMax(std::numeric_limits<float>::max()),
mElectronPairDecayLengthMin(std::numeric_limits<float>::min()), mElectronPairDecayLengthMax(std::numeric_limits<float>::max()),
mElectronPairCosThetaMin(std::numeric_limits<float>::min()),
mElectronPairAngle(std::numeric_limits<float>::min()),
mElectronPairThetaAngle(std::numeric_limits<float>::min()),
mElectronPairPhi(std::numeric_limits<float>::min()),
mElectronPairMassMin(std::numeric_limits<float>::min()), mElectronPairMassMax(std::numeric_limits<float>::max()),
mElectronJPsiMassMin(std::numeric_limits<float>::min()), mElectronJPsiMassMax(std::numeric_limits<float>::max()),
mElectronJPsiEta(std::numeric_limits<float>::max()),
mElectronJPsiDecayR(std::numeric_limits<float>::max()),
mElectronNHitsFitMax(std::numeric_limits<int>::max()),
mElectronNHitsRatio(std::numeric_limits<int>::max()),
mElectronNHitsdEdxMax(std::numeric_limits<int>::max()),
mElectronBsmdNEta(std::numeric_limits<int>::min()),
mElectronPtMin(std::numeric_limits<float>::min()),
mElectronBsmdNPhi(std::numeric_limits<int>::min()),
mElectronTofBeta(std::numeric_limits<float>::max()),
mElectronTofYLocal(std::numeric_limits<float>::max()),
mElectronTofFlag(std::numeric_limits<int>::max()),
mElectronPtMax(std::numeric_limits<float>::max()),
mElectronEtaMin(std::numeric_limits<float>::min()),
mElectronRequireHFT(false),
mElectronEtaMax(std::numeric_limits<float>::max()),
mElectronDca(std::numeric_limits<float>::max()),
mElectronDcaXY(std::numeric_limits<float>::max()),
mElectronTPCNSigmaElectronMin(std::numeric_limits<float>::min()),
mElectronTPCNSigmaElectronMax(std::numeric_limits<float>::max()),
mElectronBemcEoverPMin(std::numeric_limits<float>::min()),
mElectronBemcEoverPMax(std::numeric_limits<float>::max()),
mElectronBemcPhiDistMax(std::numeric_limits<float>::max()),
mElectronBemcZDistMax(std::numeric_limits<float>::max()),
mElectronBemcAssDistMax(std::numeric_limits<float>::max()),
mPartnerElectronNHitsFitMax(std::numeric_limits<int>::min()),
mPartnerElectronNHitsdEdxMax(std::numeric_limits<int>::min()),
mPartnerElectronPtMin(std::numeric_limits<float>::min()),
mPartnerElectronPtMax(std::numeric_limits<float>::max()),
mPartnerElectronEtaMin(std::numeric_limits<float>::min()),
mPartnerElectronEtaMax(std::numeric_limits<float>::max()),
mPartnerElectronRequireHFT(false),
mPartnerTPCNSigmaElectronMin(std::numeric_limits<float>::min()),
mPartnerTPCNSigmaElectronMax(std::numeric_limits<float>::max()),
mElectronPIDCutLow(std::numeric_limits<float>::min()),
mElectronPIDCutHigh(std::numeric_limits<float>::max()),
mElectronBemcPid(false),mElectronBsmdPid(false),mElectronTofPid(false),
mMVACut(std::numeric_limits<float>::min()),
mHTMVACut(std::numeric_limits<float>::min()),
mreader(NULL),
    mreader2(NULL),
    mMyHist(std::numeric_limits<bool>::min()),
    mPhoEHist(std::numeric_limits<bool>::min()),
    mSignalTree(std::numeric_limits<bool>::min()),
    mPhoETree(std::numeric_limits<bool>::min()),
    mBKGTree(std::numeric_limits<bool>::min()),
    mKsTree(std::numeric_limits<bool>::min()),
    mPhiTree(std::numeric_limits<bool>::min()),
    mEPTree(std::numeric_limits<bool>::min())
{
   
    // -- constructor
}

// _________________________________________________________
StNpeCuts::~StNpeCuts() {
    // destructor
    
}


// _________________________________________________________
bool StNpeCuts::isGoodElectronPair(StElectronPair const* epair) const {
    // -- check for good electron pairs
    //StPicoTrack const* electron = mPicoDst2->track(epair->electronIdx());
    //StPicoTrack const* partner = mPicoDst2->track(epair->partnerIdx());
    return
	//isGoodTaggedElectron(electron) &&
	//isGoodPartnerElectron(partner) &&
	epair->pairMass() > mElectronPairMassMin && epair->pairMass() < mElectronPairMassMax &&
	epair->pairDca() < mElectronPairDcaDaughtersMax ;//&& epair->pairAngle()
	//&& epair->pairThetaAngle() < mElectronPairThetaAngle && epair->pairPhi() < mElectronPairPhi
	;
}
bool StNpeCuts::isGoodElectronPairLoose(StElectronPair const* epair) const {
    // -- check for good electron pairs                                                                                                                                                                                                                             
    //StPicoTrack const* electron = mPicoDst2->track(epair->electronIdx());                                                                                                                                                                                        
    //StPicoTrack const* partner = mPicoDst2->track(epair->partnerIdx());                                                                                                                                                                                           
    return
        //isGoodTaggedElectron(electron) &&                                                                                                                                                                                                                                  //isGoodPartnerElectron(partner) &&                                                                                                                                                                                                                        
        epair->pairMass() > mElectronPairMassMin && epair->pairMass() < 0.15 &&
        epair->pairDca() < mElectronPairDcaDaughtersMax //&& epair->pairAngle() < mElectronPairAngle                                                                                                                                                                
        //&& epair->pairThetaAngle() < mElectronPairThetaAngle && epair->pairPhi() < mElectronPairPhi                                                                                                                                                               
        ;
}
bool StNpeCuts::isGoodPionPair(StElectronPair const* epair) const {
    // -- check for good electron pairs
    //StPicoTrack const* electron = mPicoDst2->track(epair->electronIdx());
    //StPicoTrack const* partner = mPicoDst2->track(epair->partnerIdx());
    return
	//isGoodTaggedElectron(electron) &&
	//isGoodPartnerElectron(partner) &&
	epair->pairMassPion() > 0.400 && epair->pairMassPion() < 0.600 &&
	epair->Dca() < 0.9 && epair->pairDca() < 0.1 && TMath::Cos(epair->pairAngle()) >0.7 && epair->pairDecayL()>0.5 && epair->pairDecayL()<5//&& epair->pairAngle() < mElectronPairAngle
	//&& epair->pairThetaAngle() < mElectronPairThetaAngle && epair->pairPhi() < mElectronPairPhi
	;
}
bool StNpeCuts::isGoodKaonPair(StElectronPair const* epair) const {
    // -- check for good electron pairs
    //StPicoTrack const* electron = mPicoDst2->track(epair->electronIdx());
    //StPicoTrack const* partner = mPicoDst2->track(epair->partnerIdx());
    return
	//isGoodTaggedElectron(electron) &&
	//isGoodPartnerElectron(partner) &&
	epair->pairMassKaon() > 0.8 && epair->pairMassKaon() < 1.4 &&
	epair->Dca() < 0.9 && epair->pairDca() < 0.1 && epair->pairDipAngle() >0.04 && epair->pairDecayL()>0. && epair->pairDecayL()<25.//&& epair->pairAngle() < mElectronPairAngle
	//&& epair->pairThetaAngle() < mElectronPairThetaAngle && epair->pairPhi() < mElectronPairPhi
	;//TMath::Cos(epair->pairAngle()) >0.85
}
bool StNpeCuts::isGoodProtonPionPair(StElectronPair const* epair) const {
    // -- check for good electron pairs
    //StPicoTrack const* electron = mPicoDst2->track(epair->electronIdx());
    //StPicoTrack const* partner = mPicoDst2->track(epair->partnerIdx());
    return
	//isGoodTaggedElectron(electron) &&
	//isGoodPartnerElectron(partner) &&
	epair->pairMassProtonPion() > 0.9 && epair->pairMassProtonPion() < 1.4 &&
	epair->Dca() < 0.5 && epair->pairDca() < 0.5 && TMath::Cos(epair->pairAngle()) >0.7 && epair->pairDecayL()>5 && epair->pairDecayL()<25//&& epair->pairAngle() < mElectronPairAngle
	//&& epair->pairThetaAngle() < mElectronPairThetaAngle && epair->pairPhi() < mElectronPairPhi
	;
}


bool StNpeCuts::isGoodJPsi(StElectronPair const* epair) const {
    return
	epair->pairMass() > mElectronJPsiMassMin && epair->pairMass() < mElectronJPsiMassMax &&
	epair->pairDca() < mElectronJPsiDcaDaughtersMax &&  fabs(epair->pairEta()) < mElectronJPsiEta && 
        epair->pairDecayR()<mElectronJPsiDecayR
	;
}
// _________________________________________________________
bool StNpeCuts::isGoodInclusiveElectronTPC(StPicoTrack const *trk) const {
    float temp1 = trk->nHitsFit();
    float temp2 = trk->nHitsMax();
    bool taggedElectronCut =
	trk->nHitsFit() >= mElectronNHitsFitMax && (temp1/temp2) >= mElectronNHitsRatio &&
	trk->nHitsDedx() >= mElectronNHitsdEdxMax &&
	trk->gPt() >= mElectronPtMin && trk->gPt() < mElectronPtMax &&
	getEta(trk) > mElectronEtaMin && getEta(trk) < mElectronEtaMax &&
	fabs(getDca(trk)) < mElectronDca && fabs(getDcaXY(trk)) < mElectronDcaXY;

    return taggedElectronCut;

}

float StNpeCuts::getTofBeta(StPicoTrack const * const trk, TVector3 const kfVtx) const
{
   int index2tof = trk->bTofPidTraitsIndex();

   float beta = std::numeric_limits<float>::quiet_NaN();

   if (index2tof >= 0)
   {
      StPicoBTofPidTraits *tofPid = mPicoDst2->btofPidTraits(index2tof);

      if (tofPid)
      {
         beta = tofPid->btofBeta();

         if (beta < 1e-4)
         {
	     TVector3 temp = tofPid->btofHitPos();
             StThreeVectorF const btofHitPos(temp.x(),temp.y(),temp.z());
             StPicoPhysicalHelix helix = trk->helix(mPicoDst2->event()->bField());
             //StThreeVectorD const temp1 (getpVtx().x(),getpVtx().y(),getpVtx().z());
             StThreeVectorD const temp1 (kfVtx.x(),kfVtx.y(),kfVtx.z());
             float pathLength = tofPathLength(&temp1, &btofHitPos, helix.curvature());
             float tof = tofPid->btof();
             beta = (tof > 0) ? pathLength / (tof * (C_C_LIGHT / 1.e9)) : std::numeric_limits<float>::quiet_NaN();

         }
      }
   }

   return beta;
}
// _________________________________________________________                                                                                                             
bool StNpeCuts::isNotTPCHadron(StPicoTrack const *trk) const {
    // -- check if hadron in tpc
    float nSigma_k = trk->nSigmaKaon();
    float nSigma_pi = trk->nSigmaPion();
    float nSigma_p = trk->nSigmaProton();
    return fabs(nSigma_k)>3 && fabs(nSigma_pi)>3 && fabs(nSigma_p)>3;
}
bool StNpeCuts::isTPCHadron(StPicoTrack const *trk) const {
    // -- check if hadron in tpc                                                                                                                                                                             
    float nSigma_k = trk->nSigmaKaon();
    float nSigma_pi = trk->nSigmaPion();
    float nSigma_p = trk->nSigmaProton();
    return (fabs(nSigma_k)<2 || fabs(nSigma_pi)<2 || fabs(nSigma_p)<2 || fabs(nSigma_pi)>7);
}
// _________________________________________________________
bool StNpeCuts::isGoodInclusiveElectron(StPicoTrack const *trk) const {
    // -- check for good tagged electron for electron pairs
    return isGoodInclusiveElectronTPC(trk)
    && isTPCElectron(trk, -13, 13) && (!mElectronRequireHFT || trk->isHFTTrack());
}
// _________________________________________________________
bool StNpeCuts::isGoodTaggedElectron(StPicoTrack const *trk) const {
    // -- check for good tagged electron for electron pairs
    return isGoodInclusiveElectron(trk)
	&& isTPCElectron(trk, -1, 3)
//	&& isNotTPCHadron(trk)
	&& isBEMCElectron(trk)
	// && isTOFElectron(trk)
	// && isBSMDElectron(trk)
	;
}
bool StNpeCuts::isGoodTaggedElectronLoose(StPicoTrack const *trk) const {
    // -- check for good tagged electron for electron pairs                                                                                                                                      
    return isGoodInclusiveElectron(trk)
        && isTPCElectron(trk, -4, 4)
        //&& isNotTPCHadron(trk)
        && isBEMCElectron(trk)
        // && isTOFElectron(trk)                                                                                                                                                                
        // && isBSMDElectron(trk)                                                                                                                                                               
        ;
}

// _________________________________________________________
bool StNpeCuts::isGoodPartnerElectron(StPicoTrack const *trk) const {
    // -- check for good partner electron for electron pairs

    bool partnerElectronCut =
    trk->nHitsFit() >= mPartnerElectronNHitsFitMax &&
    trk->gPt() >= mPartnerElectronPtMin && trk->gPt() < mPartnerElectronPtMax &&
    getEta(trk) > mPartnerElectronEtaMin && getEta(trk) < mPartnerElectronEtaMax &&
    (!mPartnerElectronRequireHFT || trk->isHFTTrack());
    
    return partnerElectronCut
	&& isTPCElectron(trk, mPartnerTPCNSigmaElectronMin, mPartnerTPCNSigmaElectronMax)//Removed all these
	//&& isBEMCElectron(trk)
	//&& isTOFElectron(trk)
    ;
}
bool StNpeCuts::isUnbiasedTrack(StPicoTrack const *trk) const {
    // -- check for good PID-unbiased track for training

    bool partnerElectronCut =
    trk->nHitsFit() >= mPartnerElectronNHitsFitMax &&
    trk->gPt() >= mPartnerElectronPtMin && trk->gPt() < mPartnerElectronPtMax &&
    getEta(trk) > mPartnerElectronEtaMin && getEta(trk) < mPartnerElectronEtaMax &&
    fabs(getDca(trk)) < mElectronDca && (!mPartnerElectronRequireHFT || trk->isHFTTrack());
    
    return partnerElectronCut;
}
bool StNpeCuts::isUnbiasedDisplTrack(StPicoTrack const *trk) const {
    // -- check for good PID-unbiased track for training

    bool partnerElectronCut =
    trk->nHitsFit() >= mPartnerElectronNHitsFitMax &&
    trk->gPt() >= mPartnerElectronPtMin && trk->gPt() < mPartnerElectronPtMax &&
    getEta(trk) > mPartnerElectronEtaMin && getEta(trk) < mPartnerElectronEtaMax &&
    fabs(getDca(trk)) > 0.08 && (!mPartnerElectronRequireHFT || trk->isHFTTrack());
    
    return partnerElectronCut;
}
bool StNpeCuts::isUnbiasedTrackNoHft(StPicoTrack const *trk) const {
    // -- check for good PID-unbiased track for training                                                                                                                 

    bool partnerElectronCut =
	trk->nHitsFit() >= mPartnerElectronNHitsFitMax &&
	trk->gPt() >= mPartnerElectronPtMin && trk->gPt() < mPartnerElectronPtMax &&
	getEta(trk) > mPartnerElectronEtaMin && getEta(trk) < mPartnerElectronEtaMax &&
	fabs(getDca(trk)) < mElectronDca;

    return partnerElectronCut;
}
// _________________________________________________________
bool StNpeCuts::isTPCElectron(StPicoTrack const *trk, float min, float max) const {
    // -- check for good TPC electrons
    float nSigma = trk->nSigmaElectron();
    return
    nSigma > min && nSigma < max;
}
bool StNpeCuts::isElectron(StPicoTrack const *trk) const {
    // -- Final PID cut
    float nSigma = trk->nSigmaElectron();
    return
    nSigma > mElectronPIDCutLow && nSigma < mElectronPIDCutHigh;
}

// _________________________________________________________
bool StNpeCuts::isTOFElectron(StPicoTrack const *trk) const {
    // -- check for good TOF electrons
    if (!mElectronTofPid) return true;
    StPicoBTofPidTraits *tofPid = hasTofPid(trk); 
    float beta;
    if (tofPid) {
        beta = tofPid->btofBeta();
        if (beta < 1e-4) {
	    TVector3 temp = tofPid->btofHitPos();
            StThreeVectorF const btofHitPos(temp.x(),temp.y(),temp.z());
            StPicoPhysicalHelix helix = trk->helix(mPicoDst2->event()->bField());
            StThreeVectorD const temp1 (getpVtx().x(),getpVtx().y(),getpVtx().z());
            float pathLength = tofPathLength(&temp1, &btofHitPos, helix.curvature());
            float tof = tofPid->btof();
            beta = (tof > 0) ? pathLength / (tof * (C_C_LIGHT / 1.e9)) : std::numeric_limits<float>::quiet_NaN();

	}
    }
    else beta=999;
    
    if (fabs(1/beta -1) < mElectronTofBeta &&
        TMath::Abs(tofPid->btofYLocal()) < mElectronTofYLocal &&
        tofPid->btofMatchFlag() > mElectronTofFlag
        ) return true;
    else return false;
}
bool StNpeCuts::isTOFPion(StPicoTrack const *trk) const {
    if (!mElectronTofPid) return true;
    StPicoBTofPidTraits *tofPid = hasTofPid(trk);

    float beta;
    if (tofPid) {
        beta = tofPid->btofBeta();
        if (beta < 1e-4) {
	    TVector3 temp = tofPid->btofHitPos();
            StThreeVectorF const btofHitPos(temp.x(),temp.y(),temp.z());
            StPicoPhysicalHelix helix = trk->helix(mPicoDst2->event()->bField());
            StThreeVectorD const temp1 (getpVtx().x(),getpVtx().y(),getpVtx().z());
            float pathLength = tofPathLength(&temp1, &btofHitPos, helix.curvature());
            float tof = tofPid->btof();
            beta = (tof > 0) ? pathLength / (tof * (C_C_LIGHT / 1.e9)) : std::numeric_limits<float>::quiet_NaN();
        }
    }
    else beta=999;
	double mom = trk->pMom().Mag();
	double m2 = mom*mom*( 1.0/(beta*beta)-1.0);
    if (fabs(m2-0.0193)<0.02) return true;
    else return false;
}
bool StNpeCuts::isTOFKaon(StPicoTrack const *trk) const {
    if (!mElectronTofPid) return true;
    StPicoBTofPidTraits *tofPid = hasTofPid(trk);
    
    float beta;
    if (tofPid) {
        beta = tofPid->btofBeta();
        if (beta < 1e-4) {
            TVector3 temp = tofPid->btofHitPos();
            StThreeVectorF const btofHitPos(temp.x(),temp.y(),temp.z());
            StPicoPhysicalHelix helix = trk->helix(mPicoDst2->event()->bField());
            StThreeVectorD const temp1 (getpVtx().x(),getpVtx().y(),getpVtx().z());
            float pathLength = tofPathLength(&temp1, &btofHitPos, helix.curvature());
            float tof = tofPid->btof();
            beta = (tof > 0) ? pathLength / (tof * (C_C_LIGHT / 1.e9)) : std::numeric_limits<float>::quiet_NaN();
        }
    }
    else beta=999;

        double mom = trk->pMom().Mag();
        double m2 = mom*mom*( 1.0/(beta*beta)-1.0);
    if (fabs(m2-0.243)<0.1) return true;
    else return false;
}
bool StNpeCuts::isTOFProton(StPicoTrack const *trk) const {
    if (!mElectronTofPid) return true;
    StPicoBTofPidTraits *tofPid = hasTofPid(trk);
    
    float beta;
    if (tofPid) {
        beta = tofPid->btofBeta();
        if (beta < 1e-4) {
	    TVector3 temp = tofPid->btofHitPos();
            StThreeVectorF const btofHitPos(temp.x(),temp.y(),temp.z());
            StPicoPhysicalHelix helix = trk->helix(mPicoDst2->event()->bField());
            StThreeVectorD const temp1 (getpVtx().x(),getpVtx().y(),getpVtx().z());
            float pathLength = tofPathLength(&temp1, &btofHitPos, helix.curvature());
            float tof = tofPid->btof();
            beta = (tof > 0) ? pathLength / (tof * (C_C_LIGHT / 1.e9)) : std::numeric_limits<float>::quiet_NaN();
        }
    }
    else beta=999;

        double mom = trk->pMom().Mag();
        double m2 = mom*mom*( 1.0/(beta*beta)-1.0);
    if (fabs(m2-0.867)<0.2) return true;
    else return false;
}

// _________________________________________________________
bool StNpeCuts::isBEMCElectron(StPicoTrack const *trk) const {
    // -- check for good BEMC electrons
    if (!mElectronBemcPid) return true;
    if (trk->bemcPidTraitsIndex() < 0) return false;
    StPicoBEmcPidTraits * Emc =  mPicoDst2->bemcPidTraits(trk->bemcPidTraitsIndex());
    //float eoverp = Emc->e0()/trk->gPt()/TMath::CosH(getEta(trk));                                                                                                                                                                             
    float eoverp = trk->gMom(getpVtx(), mPicoDst2->event()->bField()).Mag()/Emc->bemcE0();
    float phiDist = Emc->bemcPhiDist();
    float zDist = Emc->bemcZDist();
    float phiTowDist = Emc->btowPhiDist();
    float etaTowDist = Emc->btowPhiDist();
    return eoverp > mElectronBemcEoverPMin && eoverp < mElectronBemcEoverPMax
    //&& phiDist < mElectronBemcPhiDistMax && zDist < mElectronBemcZDistMax &&
    //&& TMath::Sqrt(phiTowDist*phiTowDist + etaTowDist*etaTowDist) < mElectronBemcAssDistMax
    ;
}

bool StNpeCuts::isBSMDElectron(StPicoTrack const *trk) const {
    // -- check for good BSMD electrons
    if (!mElectronBsmdPid) return true;
    if (trk->bemcPidTraitsIndex() < 0) return false;
    StPicoBEmcPidTraits * Emc =  mPicoDst2->bemcPidTraits(trk->bemcPidTraitsIndex());
    int nphi = Emc->bemcSmdNPhi();
    int neta = Emc->bemcSmdNEta();
    return neta >= mElectronBsmdNEta && nphi >= mElectronBsmdNPhi ;
}
// _________________________________________________________                                                                                                                                                                         
float StNpeCuts::getEta(StPicoTrack const *trk) const {
    return trk->gMom(getpVtx(), mPicoDst2->event()->bField()).PseudoRapidity();
}
// _________________________________________________________                                                                                                                                                                                   
float StNpeCuts::getDca(StPicoTrack const *trk) const {
    return trk->gDCA(getpVtx().x(),getpVtx().y(),getpVtx().z());
}
// _________________________________________________________                                                                                                                                                                                    
float StNpeCuts::getDcaXY(StPicoTrack const *trk) const {
    return trk->gDCAxy(getpVtx().x(),getpVtx().y());
}
// _________________________________________________________
TVector3 StNpeCuts::getpVtx() const {
    return mPicoDst2->event()->primaryVertex();
}
void StNpeCuts::bookMVA(char method[], char path[]){
    
    mreader->AddVariable( "probe_p/probe_emc0",&mArray[0]);
    mreader->AddVariable( "probe_nphi*probe_neta",&mArray[1]);
    //mreader->AddVariable( "probe_neta",&mArray[2]);
    mreader->AddVariable( "TMath::Sqrt(probe_zdist*probe_zdist + probe_phidist*probe_phidist)", &mArray[2]);
    //mreader->AddVariable( "probe_phidist", &mArray[4]);
    mreader->AddVariable( "(1/probe_beta - probe_p / TMath::Sqrt(probe_p*probe_p+0.00051099907*0.00051099907))/ (1/probe_beta)", &mArray[3]);
    mreader->AddVariable( "probe_nsige", &mArray[4]); 
    mreader->AddSpectator( "probe_pt",  &mArray[5]);
    char m[150];
    char dir[150];
    sprintf(m,"%s",method);
    sprintf(dir,"%s",path);
    mreader->BookMVA(m,dir); 
}
float StNpeCuts::getMVADec(StPicoTrack const *track){
    float pt = track->gPt();
    float nsige = track->nSigmaElectron();
    TVector3 const pMom = track->gMom(mPicoDst2->event()->primaryVertex(), mPicoDst2->event()->bField());   
    float ptot = pMom.Mag();
    float eoverp = 0;
    float phiDist = 0;
    float zDist = 0;
    float emc0=0;
    float beta = 0;
    float adc0 = 0;
    float mass = 0;
    float nPhi = 0;
    float nEta = 0;
    int index2tof = track->bTofPidTraitsIndex();
    if(index2tof>=0) {
	StPicoBTofPidTraits *tofPid = mPicoDst2->btofPidTraits(index2tof);
	if(tofPid){
	    beta = tofPid->btofBeta();
	}
    }
    if (track->bemcPidTraitsIndex() >= 0) {
	StPicoBEmcPidTraits * Emc = mPicoDst2->bemcPidTraits(track->bemcPidTraitsIndex());
	eoverp = track->gMom(getpVtx(), mPicoDst2->event()->bField()).Mag()/Emc->bemcE0();
	phiDist = Emc->bemcPhiDist();
	zDist = Emc->bemcZDist();
	nPhi = Emc->bemcSmdNPhi();
	nEta = Emc->bemcSmdNEta();
    }
    mArray[0] = eoverp;
    mArray[1] = nPhi*nEta;
    mArray[2] = TMath::Sqrt(zDist*zDist+phiDist*phiDist);
    if(beta!=0)mArray[3] = (1/beta - ptot / TMath::Sqrt(ptot*ptot+0.00051099907*0.00051099907))/ (1/beta);
    if(beta==0)mArray[3] = 0;
    mArray[4] = nsige;
    mArray[5] = pt;  
    return mreader->EvaluateMVA( mMethod );
}
void StNpeCuts::bookMVA2(char method[], char path[]){
    
    mreader2->AddVariable( "probe_p/probe_emc0",&mArray2[0]);
    mreader2->AddVariable( "probe_nphi*probe_neta",&mArray2[1]);
    //mreader->AddVariable( "probe_neta",&mArray[2]);
    mreader2->AddVariable( "TMath::Sqrt(probe_zdist*probe_zdist + probe_phidist*probe_phidist)", &mArray2[2]);
    //mreader->AddVariable( "probe_phidist", &mArray[4]);
    mreader2->AddVariable( "(1/probe_beta - probe_p / TMath::Sqrt(probe_p*probe_p+0.13957018*0.13957018))/ (1/probe_beta)", &mArray2[3]);
    mreader2->AddVariable( "probe_nsigpi", &mArray2[4]); 
    mreader2->AddSpectator( "probe_pt",  &mArray2[5]);
    char m[150];
    char dir[150];
    sprintf(m,"%s",method);
    sprintf(dir,"%s",path);
    mreader2->BookMVA(m,dir); 
	    //mreader->BookMVA( "Fisher","./MVA/LowPT/weights/TMVAClassification_Fisher.weights.xml" ); 
}
float StNpeCuts::getMVADec2(StPicoTrack const *track){
    float pt = track->gPt();
    float nsige = track->nSigmaPion();
    TVector3 const pMom = track->gMom(mPicoDst2->event()->primaryVertex(), mPicoDst2->event()->bField());
    float ptot = pMom.Mag();
    float eoverp = 0;
    float phiDist = 0;
    float zDist = 0;
    float emc0=0;
    float beta = 0;
    float adc0 = 0;
    float mass = 0;
    float nPhi = 0;
    float nEta = 0;
    int index2tof = track->bTofPidTraitsIndex();
    if(index2tof>=0) {
	StPicoBTofPidTraits *tofPid = mPicoDst2->btofPidTraits(index2tof);
	if(tofPid){
	    beta = tofPid->btofBeta();
	}
    }
    if (track->bemcPidTraitsIndex() >= 0) {
	StPicoBEmcPidTraits * Emc = mPicoDst2->bemcPidTraits(track->bemcPidTraitsIndex());
        eoverp = track->gMom(getpVtx(), mPicoDst2->event()->bField()).Mag()/Emc->bemcE0();
        phiDist = Emc->bemcPhiDist();
        zDist = Emc->bemcZDist();
	nPhi = Emc->bemcSmdNPhi();
        nEta = Emc->bemcSmdNEta();
    }
    mArray2[0] = eoverp;
    mArray2[1] = nPhi*nEta;
    mArray2[2] = TMath::Sqrt(zDist*zDist+phiDist*phiDist);
    if(beta!=0)mArray2[3] = (1/beta - ptot / TMath::Sqrt(ptot*ptot+0.13957018*0.13957018))/ (1/beta);
    if(beta==0)mArray2[3] = 0;
    mArray2[4] = nsige;
    mArray2[5] = pt;  
    return mreader2->EvaluateMVA( mMethod );
}
void StNpeCuts::setDLLweights(TFile *f1, TFile *f2){
    if(!(f1->IsOpen()&&f2->IsOpen())){
	cout << "\n\n\n\n\nError in opening DLL weights!!!! \n\n\n\n\n " << endl;
	return;
    }
    mElectronWeights[0] = (TH1F*)f1->Get("electron_weight_povere");
    mElectronWeights[1] = (TH1F*)f1->Get("electron_weight_nsige");
    mElectronWeights[2] = (TH1F*)f1->Get("electron_weight_deltabeta");
    mElectronWeights[3] = (TH1F*)f1->Get("electron_weight_zdist");
    mElectronWeights[4] = (TH1F*)f1->Get("electron_weight_phidist");
    mPionWeights[0] = (TH1F*)f2->Get("pion_weight_povere");
    mPionWeights[1] = (TH1F*)f2->Get("pion_weight_nsigpi");
    mPionWeights[2] = (TH1F*)f2->Get("pion_weight_deltabeta");
    mPionWeights[3] = (TH1F*)f2->Get("pion_weight_zdist");
    mPionWeights[4] = (TH1F*)f2->Get("pion_weight_phidist"); 
}
void StNpeCuts::setDLLweights_highPt(TFile *f1, TFile *f2){
    if(!(f1->IsOpen()&&f2->IsOpen())){
	cout << "\n\n\n\n\nError in opening DLL weights!!!! \n\n\n\n\n " << endl;
	return;
    }
    mElectronWeights_highPt[0] = (TH1F*)f1->Get("electron_weight_povere");
    mElectronWeights_highPt[1] = (TH1F*)f1->Get("electron_weight_nsige");
    mElectronWeights_highPt[2] = (TH1F*)f1->Get("electron_weight_deltabeta");
    mElectronWeights_highPt[3] = (TH1F*)f1->Get("electron_weight_zdist");
    mElectronWeights_highPt[4] = (TH1F*)f1->Get("electron_weight_phidist");
    mPionWeights_highPt[0] = (TH1F*)f2->Get("pion_weight_povere");
    mPionWeights_highPt[1] = (TH1F*)f2->Get("pion_weight_nsigpi");
    mPionWeights_highPt[2] = (TH1F*)f2->Get("pion_weight_deltabeta");
    mPionWeights_highPt[3] = (TH1F*)f2->Get("pion_weight_zdist");
    mPionWeights_highPt[4] = (TH1F*)f2->Get("pion_weight_phidist"); 

    mElectronWeights_highPt[0]->SetName("electron_weight_povere_highpt");
    mElectronWeights_highPt[1]->SetName("electron_weight_nsige_highpt");
    mElectronWeights_highPt[2]->SetName("electron_weight_deltabeta_highpt");
    mElectronWeights_highPt[3]->SetName("electron_weight_zdist_highpt");
    mElectronWeights_highPt[4]->SetName("electron_weight_phidist_highpt");
    mPionWeights_highPt[0]->SetName("pion_weight_povere_highpt");
    mPionWeights_highPt[1]->SetName("pion_weight_nsigpi_highpt");
    mPionWeights_highPt[2]->SetName("pion_weight_deltabeta_highpt");
    mPionWeights_highPt[3]->SetName("pion_weight_zdist_highpt");
    mPionWeights_highPt[4]->SetName("pion_weight_phidist_highpt"); 

}
void StNpeCuts::setDLLweights_HT(TFile *f1, TFile *f2){
    if(!(f1->IsOpen()&&f2->IsOpen())){
	cout << "\n\n\n\n\nError in opening DLL weights!!!! \n\n\n\n\n " << endl;
	return;
    }
    mElectronWeights_HT[0] = (TH1F*)f1->Get("electron_weight_povere");
    mElectronWeights_HT[1] = (TH1F*)f1->Get("electron_weight_nsige");
    mElectronWeights_HT[2] = (TH1F*)f1->Get("electron_weight_deltabeta");
    mElectronWeights_HT[3] = (TH1F*)f1->Get("electron_weight_zdist");
    mElectronWeights_HT[4] = (TH1F*)f1->Get("electron_weight_phidist");
    mElectronWeights_HT[5] = (TH1F*)f1->Get("electron_weight_smdhits");
    mPionWeights_HT[0] = (TH1F*)f2->Get("pion_weight_povere");
    mPionWeights_HT[1] = (TH1F*)f2->Get("pion_weight_nsigpi");
    mPionWeights_HT[2] = (TH1F*)f2->Get("pion_weight_deltabeta");
    mPionWeights_HT[3] = (TH1F*)f2->Get("pion_weight_zdist");
    mPionWeights_HT[4] = (TH1F*)f2->Get("pion_weight_phidist"); 
    mPionWeights_HT[5] = (TH1F*)f2->Get("pion_weight_smdhits"); 
    mElectronWeights_HT[0]->SetName("electron_weight_povere_ht");
    mElectronWeights_HT[1]->SetName("electron_weight_nsige_ht");
    mElectronWeights_HT[2]->SetName("electron_weight_deltabeta_ht");
    mElectronWeights_HT[3]->SetName("electron_weight_zdist_ht");
    mElectronWeights_HT[4]->SetName("electron_weight_phidist_ht");
    mElectronWeights_HT[5]->SetName("electron_weight_smdhits_ht");
    mPionWeights_HT[0]->SetName("pion_weight_povere_ht");
    mPionWeights_HT[1]->SetName("pion_weight_nsigpi_ht");
    mPionWeights_HT[2]->SetName("pion_weight_deltabeta_ht");
    mPionWeights_HT[3]->SetName("pion_weight_zdist_ht");
    mPionWeights_HT[4]->SetName("pion_weight_phidist_ht"); 
    mPionWeights_HT[5]->SetName("pion_weight_smdhits_ht"); 
}
float StNpeCuts::getDLL(StPicoTrack const *track){
    float pt = track->gPt();
    float nsige = track->nSigmaElectron();
    float nsigpi = track->nSigmaPion();
    TVector3 const pMom = track->gMom(mPicoDst2->event()->primaryVertex(), mPicoDst2->event()->bField());
    float ptot = pMom.Mag();
    float eoverp = 0;
    float phiDist = 0;
    float zDist = 0;
    float emc0=0;
    float beta = 0;
    float adc0 = 0;
    float mass = 0;
    float nPhi = 0;
    float nEta = 0;
    int index2tof = track->bTofPidTraitsIndex();
    if(index2tof>=0) {
	StPicoBTofPidTraits *tofPid = mPicoDst2->btofPidTraits(index2tof);
	if(tofPid){
	    beta = tofPid->btofBeta();
	}
    }
    if (track->bemcPidTraitsIndex() >= 0) {
	StPicoBEmcPidTraits * Emc = mPicoDst2->bemcPidTraits(track->bemcPidTraitsIndex());
        eoverp = track->gMom(getpVtx(), mPicoDst2->event()->bField()).Mag()/Emc->bemcE0();
        phiDist = Emc->bemcPhiDist();
        zDist = Emc->bemcZDist();
	emc0 = Emc->bemcE0();
	nPhi = Emc->bemcSmdNPhi();
        nEta = Emc->bemcSmdNEta();
    }
    int bin1 = mElectronWeights[0]->FindBin(ptot/emc0);
    int bin2 = mElectronWeights[1]->FindBin(nsige);
    int bin3 = mElectronWeights[2]->FindBin((1/beta - 1/(ptot / TMath::Sqrt(ptot*ptot+0.00051099907*0.00051099907)))/ (1/beta));
    int bin4 = mElectronWeights[3]->FindBin(zDist);
    int bin5 = mElectronWeights[4]->FindBin(phiDist);
    int bin11 = mPionWeights[0]->FindBin(ptot/emc0);
    int bin22 = mPionWeights[1]->FindBin(nsige);//Changed from pi
    int bin33 = mPionWeights[2]->FindBin((1/beta - 1/(ptot / TMath::Sqrt(ptot*ptot+0.00051099907*0.00051099907)))/ (1/beta));//Changed from pion
    int bin44 = mPionWeights[3]->FindBin(zDist);
    int bin55 = mPionWeights[4]->FindBin(phiDist);
    double weight1 = mElectronWeights[0]->GetBinContent(bin1);
    double weight2 = mElectronWeights[1]->GetBinContent(bin2);
    double weight3 = mElectronWeights[2]->GetBinContent(bin3);
    double weight4 = mElectronWeights[3]->GetBinContent(bin4);
    double weight5 = mElectronWeights[4]->GetBinContent(bin5);
    double weight11 = mPionWeights[0]->GetBinContent(bin11);
    double weight22 = mPionWeights[1]->GetBinContent(bin22);
    double weight33 = mPionWeights[2]->GetBinContent(bin33);
    double weight44 = mPionWeights[3]->GetBinContent(bin44);
    double weight55 = mPionWeights[4]->GetBinContent(bin55);
    //if(weight2==0)weight2=1e-7;
    //if(weight22==0)weight22=1e-7;
    //if((TMath::Log(0.8*weight1+2.1*weight2+5.3*weight3+0.3*weight4+0.5*weight5) - TMath::Log(0.8*weight11+2.1*weight22+5.3*weight33+0.3*weight44+0.5*weight55))>3000)return 3;
    //if((TMath::Log(0.8*weight1+2.1*weight2+5.3*weight3+0.3*weight4+0.5*weight5) - TMath::Log(0.8*weight11+2.1*weight22+5.3*weight33+0.3*weight44+0.5*weight55))<-3000)return -3;
    //return TMath::Log(0.7*weight1+3.4*weight2+1.3*weight3+0.8*weight4+1.3*weight5) - TMath::Log(0.7*weight11+3.4*weight22+1.3*weight33+0.8*weight44+1.3*weight55);
    if(weight1<1e-10)weight1+=1e-10;
    if(weight2<1e-10)weight2+=1e-10;
    if(weight3<1e-10)weight3+=1e-10;
    if(weight4<1e-10)weight4+=1e-10;
    if(weight5<1e-10)weight5+=1e-10;
    if(weight11<1e-10)weight11+=1e-10;
    if(weight22<1e-10)weight22+=1e-10;
    if(weight33<1e-10)weight33+=1e-10;
    if(weight44<1e-10)weight44+=1e-10;
    if(weight55<1e-10)weight55+=1e-10;
    double rati=1000;
    if(beta!=0)rati =weight1*weight2*weight3*weight4*weight5 / (weight1*weight2*weight3*weight4*weight5+weight11*weight22*weight33*weight44*weight55);
    if(beta==0)rati =weight1*weight2*weight4*weight5 / (weight1*weight2*weight4*weight5+weight11*weight22*weight44*weight55);                                                                                                                              
    double response =  -TMath::Log(1./rati -1)/15;  
    if(response>300)response=2;
    if(response<-300)response=-2;
    return response;
}
float StNpeCuts::getDLL_highPt(StPicoTrack const *track){
    float pt = track->gPt();
    float nsige = track->nSigmaElectron();
    float nsigpi = track->nSigmaPion();
    TVector3 const pMom = track->gMom(mPicoDst2->event()->primaryVertex(), mPicoDst2->event()->bField());
    float ptot = pMom.Mag();
    float eoverp = 0;
    float phiDist = 0;
    float zDist = 0;
    float emc0=0;
    float beta = 0;
    float adc0 = 0;
    float mass = 0;
    float nPhi = 0;
    float nEta = 0;
    int index2tof = track->bTofPidTraitsIndex();
    if(index2tof>=0) {
	StPicoBTofPidTraits *tofPid = mPicoDst2->btofPidTraits(index2tof);
	if(tofPid){
	    beta = tofPid->btofBeta();
	}
    }
    if (track->bemcPidTraitsIndex() >= 0) {
	StPicoBEmcPidTraits * Emc = mPicoDst2->bemcPidTraits(track->bemcPidTraitsIndex());
        eoverp = track->gMom(getpVtx(), mPicoDst2->event()->bField()).Mag()/Emc->bemcE0();
        emc0 = Emc->bemcE0();
	phiDist = Emc->bemcPhiDist();
        zDist = Emc->bemcZDist();
	nPhi = Emc->bemcSmdNPhi();
        nEta = Emc->bemcSmdNEta();
    }
    int bin1 = mElectronWeights_highPt[0]->FindBin(ptot/emc0);
    int bin2 = mElectronWeights_highPt[1]->FindBin(nsige);
    int bin3 = mElectronWeights_highPt[2]->FindBin((1/beta - 1/(ptot / TMath::Sqrt(ptot*ptot+0.00051099907*0.00051099907)))/ (1/beta));
    int bin4 = mElectronWeights_highPt[3]->FindBin(zDist);
    int bin5 = mElectronWeights_highPt[4]->FindBin(phiDist);
    int bin11 = mPionWeights_highPt[0]->FindBin(ptot/emc0);
    int bin22 = mPionWeights_highPt[1]->FindBin(nsigpi);
    int bin33 = mPionWeights_highPt[2]->FindBin((1/beta - 1/(ptot / TMath::Sqrt(ptot*ptot+0.13957018*0.13957018)))/ (1/beta));
    int bin44 = mPionWeights_highPt[3]->FindBin(zDist);
    int bin55 = mPionWeights_highPt[4]->FindBin(phiDist);
    double weight1 = 2.*mElectronWeights_highPt[0]->GetBinContent(bin1);
    double weight2 = 3.1*mElectronWeights_highPt[1]->GetBinContent(bin2);
    double weight3 = 4.*mElectronWeights_highPt[2]->GetBinContent(bin3);
    double weight4 = 0.4*mElectronWeights_highPt[3]->GetBinContent(bin4);
    double weight5 = 0.2*mElectronWeights_highPt[4]->GetBinContent(bin5);
    double weight11 = 2.*mPionWeights_highPt[0]->GetBinContent(bin11);
    double weight22 = 3.1*mPionWeights_highPt[1]->GetBinContent(bin22);
    double weight33 = 4.*mPionWeights_highPt[2]->GetBinContent(bin33);
    double weight44 = 0.4*mPionWeights_highPt[3]->GetBinContent(bin44);
    double weight55 = 0.2*mPionWeights_highPt[4]->GetBinContent(bin55);
    //if(weight2==0)weight2=1e-7;
    //if(weight22==0)weight22=1e-7;
    if((TMath::Log(weight1+weight2+weight3+weight4+weight5) - TMath::Log(weight11+weight22+weight33+weight44+weight55))>3000)return 3;
    if((TMath::Log(weight1+weight2+weight3+weight4+weight5) - TMath::Log(weight11+weight22+weight33+weight44+weight55))<-3000)return -3;
    //return TMath::Log(weight1+weight2+weight3+weight4+weight5) - TMath::Log(weight11+weight22+weight33+weight44+weight55);
    return TMath::Log(0.7*weight1+3.4*weight2+1.3*weight3+0.8*weight4+1.3*weight5) - TMath::Log(0.7*weight11+3.4*weight22+1.3*weight33+0.8*weight44+1.3*weight55);
}
float StNpeCuts::getDLL_HT(StPicoTrack const *track){
    float pt = track->gPt();
    float nsige = track->nSigmaElectron();
    float nsigpi = track->nSigmaPion();
    TVector3 const pMom = track->gMom(mPicoDst2->event()->primaryVertex(), mPicoDst2->event()->bField());
    float ptot = pMom.Mag();
    float eoverp = 0;
    float phiDist = 0;
    float zDist = 0;
    float emc0=0;
    float beta = 0;
    float adc0 = 0;
    float mass = 0;
    float nPhi = 0;
    float nEta = 0;
    int index2tof = track->bTofPidTraitsIndex();
    if(index2tof>=0) {
	StPicoBTofPidTraits *tofPid = mPicoDst2->btofPidTraits(index2tof);
	if(tofPid){
	    beta = tofPid->btofBeta();
	}
    }
    if (track->bemcPidTraitsIndex() >= 0) {
	StPicoBEmcPidTraits * Emc = mPicoDst2->bemcPidTraits(track->bemcPidTraitsIndex());
        eoverp = track->gMom(getpVtx(), mPicoDst2->event()->bField()).Mag()/Emc->bemcE0();
        emc0 = Emc->bemcE0();
        phiDist = Emc->bemcPhiDist();
        zDist = Emc->bemcZDist();
	nPhi = Emc->bemcSmdNPhi();
        nEta = Emc->bemcSmdNEta();
    }
    int bin1 = mElectronWeights_HT[0]->FindBin(ptot/emc0);
    int bin2 = mElectronWeights_HT[1]->FindBin(nsige);
    int bin3 = mElectronWeights_HT[2]->FindBin((1/beta - 1/(ptot / TMath::Sqrt(ptot*ptot+0.00051099907*0.00051099907)))/ (1/beta));
    int bin4 = mElectronWeights_HT[3]->FindBin(zDist);
    int bin5 = mElectronWeights_HT[4]->FindBin(phiDist);
    int bin6 = mElectronWeights_HT[5]->FindBin(nPhi+nEta);
    int bin11 = mPionWeights_HT[0]->FindBin(ptot/emc0);
    int bin22 = mPionWeights_HT[1]->FindBin(nsige);//changed from pi
    int bin33 = mPionWeights_HT[2]->FindBin((1/beta - 1/(ptot / TMath::Sqrt(ptot*ptot+0.00051099907*0.00051099907)))/ (1/beta));//0.13957018*0.13957018
    int bin44 = mPionWeights_HT[3]->FindBin(zDist);
    int bin55 = mPionWeights_HT[4]->FindBin(phiDist);
    int bin66 = mPionWeights_HT[5]->FindBin(nPhi+nEta);
    double weight1 = mElectronWeights_HT[0]->GetBinContent(bin1);
    double weight2 = mElectronWeights_HT[1]->GetBinContent(bin2);
    double weight3 = mElectronWeights_HT[2]->GetBinContent(bin3);
    double weight4 = mElectronWeights_HT[3]->GetBinContent(bin4);
    double weight5 = mElectronWeights_HT[4]->GetBinContent(bin5);
    double weight6 = mElectronWeights_HT[5]->GetBinContent(bin6);
    double weight11 = mPionWeights_HT[0]->GetBinContent(bin11);
    double weight22 = mPionWeights_HT[1]->GetBinContent(bin22);
    double weight33 = mPionWeights_HT[2]->GetBinContent(bin33);
    double weight44 = mPionWeights_HT[3]->GetBinContent(bin44);
    double weight55 = mPionWeights_HT[4]->GetBinContent(bin55);
    double weight66 = mPionWeights_HT[5]->GetBinContent(bin66);
    //if(weight2==0)weight2=1e-7;
    //if(weight22==0)weight22=1e-7;
    //if((TMath::Log(weight1+weight2+weight3+weight4+weight5) - TMath::Log(weight11+weight22+weight33+weight44+weight55))>3000)return 3;
    //if((TMath::Log(weight1+weight2+weight3+weight4+weight5) - TMath::Log(weight11+weight22+weight33+weight44+weight55))<-3000)return -3;
    //return TMath::Log(weight1+weight2+weight3+weight4+weight5+weight6) - TMath::Log(weight11+weight22+weight33+weight44+weight55+weight66);
    //return TMath::Log(0.7*weight1+3.4*weight2+1.3*weight3+0.8*weight4+1.3*weight5+2.*weight6) - TMath::Log(0.7*weight11+3.4*weight22+1.3*weight33+0.8*weight44+1.3*weight55+2.*weight66);
     if(weight1<1e-10)weight1+=1e-10;
    if(weight2<1e-10)weight2+=1e-10;
    if(weight3<1e-10)weight3+=1e-10;
    if(weight4<1e-10)weight4+=1e-10;
    if(weight5<1e-10)weight5+=1e-10;
    if(weight6<1e-10)weight6+=1e-10;
    if(weight11<1e-10)weight11+=1e-10;
    if(weight22<1e-10)weight22+=1e-10;
    if(weight33<1e-10)weight33+=1e-10;
    if(weight44<1e-10)weight44+=1e-10;
    if(weight55<1e-10)weight55+=1e-10;
    if(weight66<1e-10)weight66+=1e-10;
    double rati=1000;
    if(beta!=0)rati =weight1*weight2*weight3*weight4*weight5*weight6 / (weight1*weight2*weight3*weight4*weight5*weight6+weight11*weight22*weight33*weight44*weight55*weight66);
    if(beta==0)rati =weight1*weight2*weight4*weight5*weight6 / (weight1*weight2*weight4*weight5*weight6+weight11*weight22*weight44*weight55*weight66);                                                                                                                              
    double response =  -TMath::Log(1./rati -1)/15;  
    if(response>300)response=2;
    if(response<-300)response=-2;
    return response;

}
