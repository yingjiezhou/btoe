#ifndef StNpeCuts_H
#define StNpeCuts_H

/* **************************************************
 *  Cut class for HF analysis
 *  - Based on PicoCuts class
 *
 *  Initial Authors:
 *            Xin Dong        (xdong@lbl.gov)
 *            Mustafa Mustafa (mmustafa@lbl.gov)
 *            Jochen Thaeder  (jmthader@lbl.gov)
 *
 *  Contributing Authors
 *            Michael Lomnitz (mrlomnitz@lbl.gov)
 *            Guannan Xie     (guannanxie@lbl.gov)
 *          **Kunsu OH        (kunsuoh@gmail.com)
 *
 *  ** Code Maintainer
 *
 * **************************************************
 */

#include "StPicoNpeEventMaker/StElectronPair.h"
#include "StPicoCutsBase/StPicoCutsBase.h"
#include "StPicoEvent/StPicoBEmcPidTraits.h"
#include "StThreeVectorF.hh"
#include "TVector3.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "TMVA/MethodCuts.h"
class StPicoTrack;
class StPicoEvent;
class StPicoDst;

class StNpeCuts : public StPicoCutsBase
{
public:
    
    StNpeCuts();
    StNpeCuts(const Char_t *name);
    ~StNpeCuts();
    
    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    
    virtual void init() { initBase(); }
    
    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    
    
    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    // -- SETTER for CUTS
    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    void setCutElectronPair(float dcaDaughtersMax, float massMin, float massMax, float angle, float thetaangle, float phi);
    void setCutJPsi(float dca, float eta, float dr,float massMin, float massMax);
    void setCutElectronNHitsFitMax(int i);
    void setCutElectronNHitsRatio(float min);
    void setCutElectronNHitsdEdxMax(int i);
    void setElectronPID(float low, float high);
    void setCutPt(float fmin, float fmax);
    void setCutEta(float fmin, float fmax);
    void setCutDca(float f);
    void setCutDcaXY(float f);
    void setCutElectronRequireHFT(bool b);
    
    void setCutPartnerElectronNHitsFitMax(int i);
    void setCutPartnerElectronNHitsdEdxMax(int i);
    void setCutPartnerPt(float fmin, float fmax);
    void setCutPartnerEta(float fmin, float fmax);
    void setCutPartnerElectronRequireHFT(bool b);

    void setCutTPCNSigmaElectron(float fmin, float fmax);
    void setCutPartnerTPCNSigmaElectron(float fmin, float fmax);
    void setCutBemcPid(bool pid, float epmin, float epmax, float phi, float z, float ass);
    void setCutBsmdPid(bool pid, int eta, int phi);
    void setCutTofPid(bool pid, float beta, float y, int f);
    void setMVACut(float c);
    void setHTMVACut(float c);
    void setMethod(char m[]);
    void setDLLweights(TFile *f1 , TFile*f2); 
    void setDLLweights_HT(TFile *f1 , TFile*f2); 
    void setDLLweights_highPt(TFile *f1 , TFile*f2); 
    void bookMVA(char[],char[]);  
    void bookMVA2(char[],char[]);      
    void setMyHist(bool a);
    void setPhoEHist(bool a);
    void setSignalTree(bool a);
    void setPhoETree(bool a);
    void setBKGTree(bool a);
    void setKsTree(bool a);
    void setPhiTree(bool a);
    void setEPTree(bool a);    
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    // -- GETTER for single CUTS
    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
    StPicoBEmcPidTraits * hasEmcPid(StPicoTrack const * const trk) const;
    
    void setPicoDst(StPicoDst const * picoDst);
    void setReader(TMVA::Reader * reader);
    void setReader2(TMVA::Reader * reader);
    bool isTPCElectron(StPicoTrack const *trk, float min, float max) const;
    bool isTOFElectron(StPicoTrack const *trk) const;
    bool isTOFPion(StPicoTrack const *trk) const;
    bool isTOFKaon(StPicoTrack const *trk) const;
    bool isTOFProton(StPicoTrack const *trk) const;
    bool isBEMCElectron(StPicoTrack const *trk) const;
    bool isBSMDElectron(StPicoTrack const *trk) const;
    bool isElectron(StPicoTrack const *trk) const;
    bool isNotTPCHadron(StPicoTrack const *trk) const;
    bool isTPCHadron(StPicoTrack const *trk) const;
    bool isGoodElectronPair(StElectronPair const* epair) const;
    bool isGoodElectronPairLoose(StElectronPair const* epair) const;
    bool isGoodPionPair(StElectronPair const* epair) const;
    bool isGoodKaonPair(StElectronPair const* epair) const;
    bool isGoodProtonPionPair(StElectronPair const* epair) const;
    bool isGoodJPsi(StElectronPair const* epair) const;
    bool isGoodInclusiveElectronTPC(StPicoTrack const *trk) const;
    float getTofBeta(StPicoTrack const * const trk, TVector3 const kfVtx) const;

    bool isGoodInclusiveElectron(StPicoTrack const *trk) const;
    bool isGoodTaggedElectron(StPicoTrack const *trk) const;
    bool isGoodTaggedElectronLoose(StPicoTrack const *trk) const;
    bool isGoodPartnerElectron(StPicoTrack const *trk) const;
    bool isUnbiasedTrack(StPicoTrack const *trk) const;
    bool isUnbiasedTrackNoHft(StPicoTrack const *trk) const;
    bool isUnbiasedDisplTrack(StPicoTrack const *trk) const;

    float getDLL(StPicoTrack const *trk);
    float getDLL_highPt(StPicoTrack const *trk);
    float getDLL_HT(StPicoTrack const *trk);
    float getMVADec(StPicoTrack const *trk);
    float getMVADec2(StPicoTrack const *trk);
    float getEta(StPicoTrack const *trk)         const;
    float getDca(StPicoTrack const *trk)         const;
    float getDcaXY(StPicoTrack const *trk)         const;
    TVector3 getpVtx()                     const;
    
    const float&    cutElectronPairDcaDaughtersMax()       const;
    const float&    cutElectronPairDecayLengthMin()        const;
    const float&    cutElectronPairDecayLengthMax()        const;
    const float&    cutElectronPairCosThetaMin()           const;
    const float&    cutElectronPairMassMin()               const;
    const float&    cutElectronPairMassMax()               const;
    const float&    cutElectronJPsiMassMin()               const;
    const float&    cutElectronJPsiMassMax()               const;
    const float&    cutMVA()                               const;
    const float&    cutHTMVA()                               const;    
    const float&    myHist()                               const;
    const float&    phoeHist()                               const;
    const float&    signalTree()                               const;
    const float&    phoeTree()                               const;
    const float&    bkgTree()                               const;
    const float&    ksTree()                               const;
    const float&    phiTree()                               const;
    const float&    epTree()                               const;
private:


    StNpeCuts(StNpeCuts const &);
    StNpeCuts& operator=(StNpeCuts const &);

    const StPicoDst*  mPicoDst2;   //! ptr to picoDst
    
    //
    // Final Electron PID 
    //
    float mElectronPIDCutLow;
    float mElectronPIDCutHigh;
    // ------------------------------------------
    // -- Pair cuts for electron pair
    // ------------------------------------------
    float mElectronPairDcaDaughtersMax;
    float mElectronJPsiDcaDaughtersMax;
    float mElectronPairDecayLengthMin;
    float mElectronPairDecayLengthMax;
    float mElectronPairCosThetaMin;
    float mElectronPairMassMin;
    float mElectronPairMassMax;
    float mElectronJPsiMassMin;
    float mElectronJPsiMassMax;
    float mElectronJPsiEta;
    float mElectronJPsiDecayR;
    float mElectronPairAngle;   
    float mElectronPairThetaAngle;
    float mElectronPairPhi;
    // ------------------------------------------
    // -- Track cuts for tagged electron
    // ------------------------------------------
    int mElectronNHitsdEdxMax;
    int mElectronNHitsFitMax;
    float mElectronNHitsRatio;
    float mElectronPtMin;
    float mElectronPtMax;
    float mElectronEtaMin;
    float mElectronEtaMax;
    float mElectronDca;
    float mElectronDcaXY;
    int mElectronBsmdNEta;
    int mElectronBsmdNPhi;
    bool mElectronRequireHFT;
    float mElectronTPCNSigmaElectronMin;
    float mElectronTPCNSigmaElectronMax;
    float mElectronBemcEoverPMin;
    float mElectronBemcEoverPMax;
    float mElectronBemcPhiDistMax;
    float mElectronBemcZDistMax;
    float mElectronBemcAssDistMax;
    bool mElectronBemcPid;
    bool mElectronBsmdPid;
    bool mElectronTofPid;
    float mElectronTofBeta;
    float mElectronTofYLocal;
    int mElectronTofFlag;
    
    // ------------------------------------------
    // -- Track cuts for partner electron
    // ------------------------------------------
    int mPartnerElectronNHitsdEdxMax;
    int mPartnerElectronNHitsFitMax;

    float mPartnerElectronPtMin;
    float mPartnerElectronPtMax;
    float mPartnerElectronEtaMin;
    float mPartnerElectronEtaMax;
    float mPartnerTPCNSigmaElectronMin;
    float mPartnerTPCNSigmaElectronMax;
    bool mPartnerElectronRequireHFT;

    float mArray[8];
    float mArray2[8];
    float mMVACut;
    float mHTMVACut;
    char mMethod[15];
    bool mMyHist;
    bool mPhoEHist;
    bool mSignalTree;
    bool mPhoETree;
    bool mBKGTree;
    bool mKsTree;
    bool mPhiTree;
    bool mEPTree;
    TMVA::Reader *mreader;
    TMVA::Reader *mreader2;  
    TH1F* mElectronWeights[5];
    TH1F* mPionWeights[5];
    TH1F* mElectronWeights_HT[6];
    TH1F* mPionWeights_HT[6];
    TH1F* mElectronWeights_highPt[5];
    TH1F* mPionWeights_highPt[5];
    ClassDef(StNpeCuts,1)
};

inline void StNpeCuts::setCutElectronPair(float dcaDaughtersMax, float massMin, float massMax, float angle, float thetaangle, float phi)  {
    mElectronPairDcaDaughtersMax = dcaDaughtersMax;
    mElectronPairMassMin = massMin;
    mElectronPairMassMax = massMax;
    mElectronPairAngle = angle;
    mElectronPairThetaAngle = thetaangle;
    mElectronPairPhi = phi;
}
inline void StNpeCuts::setCutJPsi(float dca, float eta, float dr , float massMin, float massMax)  {
    mElectronJPsiDcaDaughtersMax = dca;
    mElectronJPsiMassMin = massMin;
    mElectronJPsiMassMax = massMax;
    mElectronJPsiEta = eta;
    mElectronJPsiDecayR = dr;
}
inline void StNpeCuts::setCutElectronNHitsdEdxMax(int i)  {
    mElectronNHitsdEdxMax = i;
}
inline void StNpeCuts::setCutElectronNHitsFitMax(int i)  {
    mElectronNHitsFitMax = i;
}
inline void StNpeCuts::setCutElectronNHitsRatio(float i)  {
    mElectronNHitsRatio = i;
}
inline void StNpeCuts::setCutPt(float fmin, float fmax)  {
    mElectronPtMin = fmin;
    mElectronPtMax = fmax;
}
inline void StNpeCuts::setCutEta(float fmin, float fmax)  {
    mElectronEtaMin = fmin;
    mElectronEtaMax = fmax;
}
inline void StNpeCuts::setCutDca(float f)  {
    mElectronDca = f;
}
inline void StNpeCuts::setCutDcaXY(float f)  {
    mElectronDcaXY = f;
}
inline void StNpeCuts::setCutElectronRequireHFT(bool b)  {
    mElectronRequireHFT = b;
}
inline void StNpeCuts::setCutPartnerElectronNHitsdEdxMax(int i)  {
    mPartnerElectronNHitsdEdxMax = i;
}
inline void StNpeCuts::setCutPartnerElectronNHitsFitMax(int i)  {
    mPartnerElectronNHitsFitMax = i;
}
inline void StNpeCuts::setCutPartnerPt(float fmin, float fmax)  {
    mPartnerElectronPtMin = fmin;
    mPartnerElectronPtMax = fmax;

}
inline void StNpeCuts::setCutPartnerEta(float fmin, float fmax)  {
    mPartnerElectronEtaMin = fmin;
    mPartnerElectronEtaMax = fmax;

}
inline void StNpeCuts::setElectronPID(float fmin, float fmax)  {
    mElectronPIDCutLow = fmin;
    mElectronPIDCutHigh = fmax;

}
inline void StNpeCuts::setCutPartnerElectronRequireHFT(bool b)  {
    mPartnerElectronRequireHFT = b;
}

inline void StNpeCuts::setCutTPCNSigmaElectron(float fmin, float fmax)  {
    mElectronTPCNSigmaElectronMin = fmin;
    mElectronTPCNSigmaElectronMax = fmax;
}
inline void StNpeCuts::setCutPartnerTPCNSigmaElectron(float fmin, float fmax)  {
    mPartnerTPCNSigmaElectronMin = fmin;
    mPartnerTPCNSigmaElectronMax = fmax;

}
inline void StNpeCuts::setCutBemcPid(bool pid, float epmin, float epmax, float phi, float z, float ass)  {
    mElectronBemcPid = pid;
    mElectronBemcEoverPMin = epmin;
    mElectronBemcEoverPMax = epmax;
    mElectronBemcPhiDistMax = phi;
    mElectronBemcZDistMax = z;
    mElectronBemcAssDistMax = ass;
    
}
inline void StNpeCuts::setCutBsmdPid(bool pid, int eta, int phi)  {
    mElectronBsmdPid = pid;
    mElectronBsmdNEta = eta;
    mElectronBsmdNPhi = phi;
}
inline void StNpeCuts::setCutTofPid(bool pid, float beta, float y, int f)  {
    mElectronTofPid = pid;
    mElectronTofBeta = beta;
    mElectronTofYLocal = y;
    mElectronTofFlag = f;

}
inline void StNpeCuts::setPicoDst(StPicoDst const * picoDst)  {
    mPicoDst2=picoDst;
}
inline void StNpeCuts::setReader(TMVA::Reader * reader)  {
    mreader=reader;
}
inline void StNpeCuts::setReader2(TMVA::Reader * reader)  {
    mreader2=reader;
}
inline void StNpeCuts::setMVACut(float cut)  {
    mMVACut = cut;
}
inline void StNpeCuts::setHTMVACut(float cut)  {
    mHTMVACut = cut;
}
inline void StNpeCuts::setMethod(char method[])  {
    sprintf(mMethod,"%s",method);
}
inline void StNpeCuts::setMyHist(bool a)  {
    mMyHist = a;
}
inline void StNpeCuts::setPhoEHist(bool a)  {
    mPhoEHist = a;
}
inline void StNpeCuts::setSignalTree(bool a)  {
    mSignalTree = a;
}
inline void StNpeCuts::setPhoETree(bool a)  {
    mPhoETree = a;
}
inline void StNpeCuts::setBKGTree(bool a)  {
    mBKGTree = a;
}
inline void StNpeCuts::setKsTree(bool a)  {
    mKsTree = a;
}
inline void StNpeCuts::setPhiTree(bool a)  {
    mPhiTree = a;
}
inline void StNpeCuts::setEPTree(bool a)  {
    mEPTree = a;
}
inline const float&    StNpeCuts::cutElectronPairDcaDaughtersMax()       const { return mElectronPairDcaDaughtersMax; }
inline const float&    StNpeCuts::cutElectronPairDecayLengthMin()        const { return mElectronPairDecayLengthMin; }
inline const float&    StNpeCuts::cutElectronPairDecayLengthMax()        const { return mElectronPairDecayLengthMax; }
inline const float&    StNpeCuts::cutElectronPairCosThetaMin()           const { return mElectronPairCosThetaMin; }
inline const float&    StNpeCuts::cutElectronPairMassMin()               const { return mElectronPairMassMin; }
inline const float&    StNpeCuts::cutElectronPairMassMax()               const { return mElectronPairMassMax; }
inline const float&    StNpeCuts::cutElectronJPsiMassMin()               const { return mElectronJPsiMassMin; }
inline const float&    StNpeCuts::cutElectronJPsiMassMax()               const { return mElectronJPsiMassMax; }
inline const float&    StNpeCuts::cutMVA()                               const { return mMVACut; }
inline const float&    StNpeCuts::cutHTMVA()                               const { return mHTMVACut; }
inline const float&    StNpeCuts::myHist()                               const { return mMyHist; }
inline const float&    StNpeCuts::phoeHist()                               const { return mPhoEHist; }
inline const float&    StNpeCuts::signalTree()                               const { return mSignalTree; }
inline const float&    StNpeCuts::phoeTree()                               const { return mPhoETree; }
inline const float&    StNpeCuts::bkgTree()                               const { return mBKGTree; }
inline const float&    StNpeCuts::ksTree()                               const { return mKsTree; }
inline const float&    StNpeCuts::phiTree()                               const { return mPhiTree; }
inline const float&    StNpeCuts::epTree()                               const { return mEPTree; }
#endif
