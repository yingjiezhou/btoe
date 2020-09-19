#ifdef __ROOT__
#include "StKaonKaon.h"

#include "TMath.h"

#include "StLorentzVectorF.hh"
#include "StThreeVectorF.hh"
#include "StPicoDstMaker/StPicoTrack.h"
#include "StPicoDstMaker/StPicoConstants.h"

ClassImp(StKaonKaon)

////////////////////////////////////////////////////////////////////
StKaonKaon::StKaonKaon() {
  clear();
}
////////////////////////////////////////////////////////////////////
StKaonKaon::StKaonKaon(StKaonKaon* t) 
{
  clear();
  mKaon1Id = t->mKaon1Id;
  mKaon2Id = t->mKaon2Id;
  mM    = t->mM;
  mPt = t->mPt;
  mEta = t->mEta;
  mPhi = t->mPhi;
  mOpenAngle = t->mOpenAngle;
}

////////////////////////////////////////////////////////////////////
StKaonKaon::StKaonKaon(StPicoTrack* kaon1, StPicoTrack* kaon2,Int_t k1Id,Int_t k2Id)
{
  clear();
  if (!kaon1 || !kaon2) return;

  StLorentzVectorF k1FourMom(kaon1->pMom(),kaon1->pMom().massHypothesis(.493677));
  StLorentzVectorF k2FourMom(kaon2->pMom(),kaon2->pMom().massHypothesis(.493677));
  StLorentzVectorF kkFourMom = k1FourMom + k2FourMom;

  mKaon1Id = k1Id;
  mKaon2Id = k2Id;

  mM = (10000.*kkFourMom.m())>Pico::USHORTMAX ? Pico::USHORTMAX : (UShort_t)(TMath::Nint(kkFourMom.m()*10000.));
  mPt = (1000.*kkFourMom.perp())>Pico::USHORTMAX ? Pico::USHORTMAX : (UShort_t)(TMath::Nint(kkFourMom.perp()*1000.));
  mEta = (Short_t)(TMath::Nint(kkFourMom.pseudoRapidity()*1000.));
  mPhi = (Short_t)(TMath::Nint(kkFourMom.phi()*1000.));
  mOpenAngle = (Short_t)(TMath::Nint(kaon1->pMom().angle(kaon2->pMom()) * 1000.));
}
//////////////////////////
StLorentzVectorF StKaonKaon::lorentzVector()
{
  Float_t px = pt()*TMath::Cos(phi());
  Float_t py = pt()*TMath::Sin(phi());
  Float_t pz = pt()*TMath::SinH(eta());
  Float_t e = TMath::Sqrt(px*px+py*py+pz*pz+m()*m());

  StLorentzVectorF kkFourMom(px,py,pz,e);

  return kkFourMom;
}
////////////////////////////////////////////////////////////////////
StKaonKaon::~StKaonKaon() {
}

////////////////////////////////////////////////////////////////////
void StKaonKaon::clear() 
{
  mKaon1Id=Pico::USHORTMAX;
  mKaon2Id=Pico::USHORTMAX;

  mM=Pico::USHORTMAX;
  mPt=0;
  mEta=0.;
  mPhi=0.;
  mOpenAngle=0.;
};
#endif // __ROOT__
