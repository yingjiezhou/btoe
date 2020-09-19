#include <limits>
#include <cmath>

#ifdef __ROOT__
#define Melectron 0.00051099907
#define Mpion 0.13957018
#define Mkaon 0.493677
#define Mproton 0.938272
#include "StLorentzVectorF.hh"
#include "StLorentzVectorD.hh"
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"
#include "StPhysicalHelixD.hh"
#include "phys_constants.h"
#include "SystemOfUnits.h"
#include "StPicoDstMaker/StPicoTrack.h"

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
                               unsigned short const electronIdx, unsigned short const partnerIdx, float const bField, StThreeVectorF pVtx) :
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
    
    StPhysicalHelixD electronHelix = electron->dcaGeometry().helix();
    StPhysicalHelixD partnerHelix = partner->dcaGeometry().helix();
    
    // normal method
    pair<double,double> ss = electronHelix.pathLengths(partnerHelix);
    StThreeVectorD kAtDcaToPartner = electronHelix.at(ss.first);
    StThreeVectorD pAtDcaToElectron = partnerHelix.at(ss.second);
    
    // calculate DCA of partner to electron at their DCA
    StThreeVectorD VectorDca = kAtDcaToPartner - pAtDcaToElectron;
    StThreeVectorD DecayPoint = (kAtDcaToPartner/2 + pAtDcaToElectron/2);// - pVtx;
    StThreeVectorD DecayL = (kAtDcaToPartner/2 + pAtDcaToElectron/2) - pVtx;
    //mPairDecayR = static_cast<float>(DecayPoint.mag());
    mPairDecayR = static_cast<float>(sqrt(DecayPoint.x()*DecayPoint.x()+DecayPoint.y()*DecayPoint.y()));     
    mPairDecayL = static_cast<float>(sqrt(DecayL.x()*DecayL.x()+DecayL.y()*DecayL.y()+DecayL.z()*DecayL.z()));     
    mPairDca = static_cast<float>(VectorDca.mag());
    
    // calculate Lorentz vector of electron-partner pair
    StThreeVectorD const electronMomAtDca = electronHelix.momentumAt(ss.first, bField * kilogauss);
    StThreeVectorD const partnerMomAtDca = partnerHelix.momentumAt(ss.second, bField * kilogauss);

    StThreeVectorF temp1 (electronMomAtDca.x(),electronMomAtDca.y(),0);
    StThreeVectorF temp2 (partnerMomAtDca.x(),partnerMomAtDca.y(),0);
    StThreeVectorF temp3 (0,electronMomAtDca.y(),electronMomAtDca.z());
    StThreeVectorF temp4 (0,partnerMomAtDca.y(),partnerMomAtDca.z());



    mPairDipAngle = TMath::ACos((electronMomAtDca.perp()*partnerMomAtDca.perp()+electronMomAtDca.z()*partnerMomAtDca.z())/(electronMomAtDca.mag()*partnerMomAtDca.mag()));
    mPairAngle = electronMomAtDca.angle(partnerMomAtDca);
    mPairThetaAngle=temp1.angle(temp2);
    mPairPhi=temp3.angle(temp4);
    
    //StLorentzVectorF const electronFourMom(electronMomAtDca, electronMomAtDca.massHypothesis(Melectron));
    //StLorentzVectorF const partnerFourMom(partnerMomAtDca, partnerMomAtDca.massHypothesis(Melectron));

    StLorentzVectorD electronFourMom(0,0,0,0);
    StLorentzVectorD partnerFourMom(0,0,0,0);

    electronFourMom.setPx(electronMomAtDca.x());
    electronFourMom.setPy(electronMomAtDca.y());
    electronFourMom.setPz(electronMomAtDca.z());
    electronFourMom.setE(sqrt(electronMomAtDca.x()*electronMomAtDca.x()
			      + electronMomAtDca.y()*electronMomAtDca.y()
			      + electronMomAtDca.z()*electronMomAtDca.z() + Melectron*Melectron));

    partnerFourMom.setPx(partnerMomAtDca.x());
    partnerFourMom.setPy(partnerMomAtDca.y());
    partnerFourMom.setPz(partnerMomAtDca.z());
    partnerFourMom.setE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
			     + partnerMomAtDca.y()*partnerMomAtDca.y()
			     + partnerMomAtDca.z()*partnerMomAtDca.z()
			     + Melectron*Melectron));
    StLorentzVectorD electronFourMom1(0,0,0,0);
    StLorentzVectorD electronFourMom2(0,0,0,0);
    StLorentzVectorD partnerFourMom1(0,0,0,0);
    StLorentzVectorD partnerFourMom2(0,0,0,0);
    StLorentzVectorD partnerFourMom3(0,0,0,0);
    electronFourMom1.setPx(electronMomAtDca.x());
    electronFourMom1.setPy(electronMomAtDca.y());
    electronFourMom1.setPz(electronMomAtDca.z());
    electronFourMom1.setE(sqrt(electronMomAtDca.x()*electronMomAtDca.x()
                              + electronMomAtDca.y()*electronMomAtDca.y()
                              + electronMomAtDca.z()*electronMomAtDca.z() + Mpion*Mpion));
    electronFourMom2.setPx(electronMomAtDca.x());
    electronFourMom2.setPy(electronMomAtDca.y());
    electronFourMom2.setPz(electronMomAtDca.z());
    electronFourMom2.setE(sqrt(electronMomAtDca.x()*electronMomAtDca.x()
                              + electronMomAtDca.y()*electronMomAtDca.y()
                              + electronMomAtDca.z()*electronMomAtDca.z() + Mkaon*Mkaon));

    partnerFourMom1.setPx(partnerMomAtDca.x());
    partnerFourMom1.setPy(partnerMomAtDca.y());
    partnerFourMom1.setPz(partnerMomAtDca.z());
    partnerFourMom1.setE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
                             + partnerMomAtDca.y()*partnerMomAtDca.y()
                             + partnerMomAtDca.z()*partnerMomAtDca.z()
                             + Mpion*Mpion));
    partnerFourMom2.setPx(partnerMomAtDca.x());
    partnerFourMom2.setPy(partnerMomAtDca.y());
    partnerFourMom2.setPz(partnerMomAtDca.z());
    partnerFourMom2.setE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
                             + partnerMomAtDca.y()*partnerMomAtDca.y()
                             + partnerMomAtDca.z()*partnerMomAtDca.z()
                             + Mkaon*Mkaon));
    partnerFourMom3.setPx(partnerMomAtDca.x());
    partnerFourMom3.setPy(partnerMomAtDca.y());
    partnerFourMom3.setPz(partnerMomAtDca.z());
    partnerFourMom3.setE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
                             + partnerMomAtDca.y()*partnerMomAtDca.y()
                             + partnerMomAtDca.z()*partnerMomAtDca.z()
                             + Mproton*Mproton));

    StLorentzVectorF const epairFourMom = electronFourMom + partnerFourMom;
    StLorentzVectorF const epairFourMom1 = electronFourMom1 + partnerFourMom1;
    StLorentzVectorF const epairFourMom2 = electronFourMom2 + partnerFourMom2;
    StLorentzVectorF const epairFourMom3 = electronFourMom1 + partnerFourMom3;
    StThreeVectorD pair_mom(epairFourMom.x(),epairFourMom.y(),epairFourMom.z());
    StPhysicalHelixD eHelix(pair_mom,DecayPoint,0,0);

    //eh_dcaxy = eHelix.geometricSignedDistance(pVtx.x(),pVtx.y());
    mDca = eHelix.geometricSignedDistance(pVtx);


    mEta = epairFourMom.pseudoRapidity();
    mMass = epairFourMom.m();
    mMassPion = epairFourMom1.m();
    mMassKaon = epairFourMom2.m(); 
    mMassProtonPion = epairFourMom3.m();   
    StThreeVectorD Position = (kAtDcaToPartner + pAtDcaToElectron)/2.0;
    mPositionX = Position.x();
    mPositionY = Position.y();
    mPositionZ = Position.z();
}
#endif // __ROOT__
