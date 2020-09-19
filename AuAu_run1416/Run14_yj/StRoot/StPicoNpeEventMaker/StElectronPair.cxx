#include <limits>
#include <cmath>

#ifdef __ROOT__
#define Melectron 0.00051099907
#define Mpion 0.13957018
#define Mkaon 0.493677
#define Mproton 0.938272
#include "TLorentzVector.h"
#include "StPicoEvent/StPicoPhysicalHelix.h"
#include "phys_constants.h"
#include "SystemOfUnits.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StElectronPair.h"

ClassImp(StElectronPair)


StElectronPair::StElectronPair():
mElectronIdx(std::numeric_limits<unsigned short>::quiet_NaN()), 
mPartnerIdx(std::numeric_limits<unsigned short>::quiet_NaN()),
mEta(std::numeric_limits<unsigned short>::quiet_NaN()),
mMass(std::numeric_limits<float>::quiet_NaN()),
    mMassPion(std::numeric_limits<float>::quiet_NaN()),
    mMassKaon(std::numeric_limits<float>::quiet_NaN()),
    mMassProtonPion(std::numeric_limits<float>::quiet_NaN()),
mPairDca(std::numeric_limits<float>::quiet_NaN()),
    mDca(std::numeric_limits<float>::quiet_NaN()),
mPairDecayR(std::numeric_limits<float>::quiet_NaN()),
mPairDecayL(std::numeric_limits<float>::quiet_NaN()),
mPairAngle(std::numeric_limits<float>::quiet_NaN()),
    mPairDipAngle(std::numeric_limits<float>::quiet_NaN()),
mPairThetaAngle(std::numeric_limits<float>::quiet_NaN()),
mPairPhi(std::numeric_limits<float>::quiet_NaN()),
mPositionX(std::numeric_limits<float>::quiet_NaN()),
mPositionY(std::numeric_limits<float>::quiet_NaN()),
mPositionZ(std::numeric_limits<float>::quiet_NaN())
{
}
//------------------------------------
StElectronPair::StElectronPair(StElectronPair const * t) :
mElectronIdx(t->mElectronIdx), mPartnerIdx(t->mPartnerIdx),
mEta(t->mEta),
mMass(t->mMass),
mMassPion(t->mMassPion),
mMassKaon(t->mMassKaon),
mMassProtonPion(t->mMassProtonPion),
mPairDca(t->mPairDca),
mDca(t->mDca),
mPairDecayR(t->mPairDecayR),
mPairDecayL(t->mPairDecayL),
mPairAngle(t->mPairAngle),
mPairDipAngle(t->mPairDipAngle),
mPairThetaAngle(t->mPairThetaAngle),
mPairPhi(t->mPairPhi),
mPositionX(t->mPositionX),
mPositionY(t->mPositionY),
mPositionZ(t->mPositionZ)
{
}
//------------------------------------
StElectronPair::StElectronPair(StPicoTrack const * const electron, StPicoTrack const * const partner,
                               unsigned short const electronIdx, unsigned short const partnerIdx, float const bField, TVector3 pVtx) :
mElectronIdx(electronIdx), mPartnerIdx(partnerIdx),
mEta(std::numeric_limits<unsigned short>::quiet_NaN()),
mMass(std::numeric_limits<float>::quiet_NaN()),
mMassPion(std::numeric_limits<float>::quiet_NaN()),
mMassKaon(std::numeric_limits<float>::quiet_NaN()),
mMassProtonPion(std::numeric_limits<float>::quiet_NaN()),
mPairDca(std::numeric_limits<float>::quiet_NaN()),
mDca(std::numeric_limits<float>::quiet_NaN()),
mPairDecayR(std::numeric_limits<float>::quiet_NaN()),
mPairDecayL(std::numeric_limits<float>::quiet_NaN()),
mPairAngle(std::numeric_limits<float>::quiet_NaN()),
mPairDipAngle(std::numeric_limits<float>::quiet_NaN()),
mPairThetaAngle(std::numeric_limits<float>::quiet_NaN()),
mPairPhi(std::numeric_limits<float>::quiet_NaN()),
mPositionX(std::numeric_limits<float>::quiet_NaN()),
mPositionY(std::numeric_limits<float>::quiet_NaN()),
mPositionZ(std::numeric_limits<float>::quiet_NaN())
{
    if ((!electron || !partner) || (electron->id() == partner->id()))
    {
        mElectronIdx = std::numeric_limits<unsigned short>::quiet_NaN();
        mPartnerIdx = std::numeric_limits<unsigned short>::quiet_NaN();
        return;
    }    

    StPicoPhysicalHelix electronHelix = electron->helix(bField);
    StPicoPhysicalHelix partnerHelix = partner->helix(bField);


    pair<double,double> ss = electronHelix.pathLengths(partnerHelix);
    TVector3 kAtDcaToPartner = electronHelix.at(ss.first);
    TVector3 pAtDcaToElectron = partnerHelix.at(ss.second);

    // calculate DCA of partner to electron at their DCA
    TVector3 VectorDca = kAtDcaToPartner - pAtDcaToElectron;
    TVector3 DecayPoint = (kAtDcaToPartner + pAtDcaToElectron)*0.5;// - pVtx;
    TVector3 DecayL = (kAtDcaToPartner + pAtDcaToElectron)*0.5 - pVtx;
    mPairDecayR = static_cast<float>(sqrt(DecayPoint.x()*DecayPoint.x()+DecayPoint.y()*DecayPoint.y()));     
    mPairDecayL = static_cast<float>(sqrt(DecayL.x()*DecayL.x()+DecayL.y()*DecayL.y()+DecayL.z()*DecayL.z()));     
    mPairDca = static_cast<float>(VectorDca.Mag());
    // calculate Lorentz vector of electron-partner pair
    TVector3 const electronMomAtDca = electronHelix.momentumAt(ss.first, bField * kilogauss);
    TVector3 const partnerMomAtDca = partnerHelix.momentumAt(ss.second, bField * kilogauss);

    TVector3 temp1 (electronMomAtDca.x(),electronMomAtDca.y(),0);
    TVector3 temp2 (partnerMomAtDca.x(),partnerMomAtDca.y(),0);
    TVector3 temp3 (0,electronMomAtDca.y(),electronMomAtDca.z());
    TVector3 temp4 (0,partnerMomAtDca.y(),partnerMomAtDca.z());

    mPairDipAngle = TMath::ACos((electronMomAtDca.Perp()*partnerMomAtDca.Perp()+electronMomAtDca.z()*partnerMomAtDca.z())/(electronMomAtDca.Mag()*partnerMomAtDca.Mag()));
    mPairAngle = electronMomAtDca.Angle(partnerMomAtDca);
    mPairThetaAngle=temp1.Angle(temp2);
    mPairPhi=temp3.Angle(temp4);
    
    TLorentzVector electronFourMom(0,0,0,0);
    TLorentzVector partnerFourMom(0,0,0,0);

    electronFourMom.SetPx(electronMomAtDca.x());
    electronFourMom.SetPy(electronMomAtDca.y());
    electronFourMom.SetPz(electronMomAtDca.z());
    electronFourMom.SetE(sqrt(electronMomAtDca.x()*electronMomAtDca.x()
			      + electronMomAtDca.y()*electronMomAtDca.y()
			      + electronMomAtDca.z()*electronMomAtDca.z() + Melectron*Melectron));
    partnerFourMom.SetPx(partnerMomAtDca.x());
    partnerFourMom.SetPy(partnerMomAtDca.y());
    partnerFourMom.SetPz(partnerMomAtDca.z());
    partnerFourMom.SetE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
			     + partnerMomAtDca.y()*partnerMomAtDca.y()
			     + partnerMomAtDca.z()*partnerMomAtDca.z()
			     + Melectron*Melectron));
    TLorentzVector electronFourMom1(0,0,0,0);
    TLorentzVector electronFourMom2(0,0,0,0);
    TLorentzVector partnerFourMom1(0,0,0,0);
    TLorentzVector partnerFourMom2(0,0,0,0);
    TLorentzVector partnerFourMom3(0,0,0,0);
    electronFourMom1.SetPx(electronMomAtDca.x());
    electronFourMom1.SetPy(electronMomAtDca.y());
    electronFourMom1.SetPz(electronMomAtDca.z());
    electronFourMom1.SetE(sqrt(electronMomAtDca.x()*electronMomAtDca.x()
                              + electronMomAtDca.y()*electronMomAtDca.y()
                              + electronMomAtDca.z()*electronMomAtDca.z() + Mpion*Mpion));
    electronFourMom2.SetPx(electronMomAtDca.x());
    electronFourMom2.SetPy(electronMomAtDca.y());
    electronFourMom2.SetPz(electronMomAtDca.z());
    electronFourMom2.SetE(sqrt(electronMomAtDca.x()*electronMomAtDca.x()
                              + electronMomAtDca.y()*electronMomAtDca.y()
                              + electronMomAtDca.z()*electronMomAtDca.z() + Mkaon*Mkaon));

    partnerFourMom1.SetPx(partnerMomAtDca.x());
    partnerFourMom1.SetPy(partnerMomAtDca.y());
    partnerFourMom1.SetPz(partnerMomAtDca.z());
    partnerFourMom1.SetE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
			      + partnerMomAtDca.y()*partnerMomAtDca.y()
			      + partnerMomAtDca.z()*partnerMomAtDca.z()
			      + Mpion*Mpion));
    partnerFourMom2.SetPx(partnerMomAtDca.x());
    partnerFourMom2.SetPy(partnerMomAtDca.y());
    partnerFourMom2.SetPz(partnerMomAtDca.z());
    partnerFourMom2.SetE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
			      + partnerMomAtDca.y()*partnerMomAtDca.y()
			      + partnerMomAtDca.z()*partnerMomAtDca.z()
			      + Mkaon*Mkaon));
    partnerFourMom3.SetPx(partnerMomAtDca.x());
    partnerFourMom3.SetPy(partnerMomAtDca.y());
    partnerFourMom3.SetPz(partnerMomAtDca.z());
    partnerFourMom3.SetE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
			      + partnerMomAtDca.y()*partnerMomAtDca.y()
			      + partnerMomAtDca.z()*partnerMomAtDca.z()
			      + Mproton*Mproton));
    TLorentzVector const epairFourMom = electronFourMom + partnerFourMom;
    TLorentzVector const epairFourMom1 = electronFourMom1 + partnerFourMom1;
    TLorentzVector const epairFourMom2 = electronFourMom2 + partnerFourMom2;
    TLorentzVector const epairFourMom3 = electronFourMom1 + partnerFourMom3;
    TVector3 pair_mom(epairFourMom.X(),epairFourMom.Y(),epairFourMom.Z());
    StPicoPhysicalHelix eHelix(pair_mom,DecayPoint,0,0);
    mDca = eHelix.geometricSignedDistance(pVtx);
    mEta = epairFourMom.PseudoRapidity();
    mMass = epairFourMom.M();
    mMassPion = epairFourMom1.M();
    mMassKaon = epairFourMom2.M(); 
    mMassProtonPion = epairFourMom3.M();   
    TVector3 Position = (kAtDcaToPartner + pAtDcaToElectron)*0.5;
    mPositionX = Position.x();
    mPositionY = Position.y();
    mPositionZ = Position.z();
}
#endif // __ROOT__
