#include <limits>
#include <cmath>

#ifdef __ROOT__

#include "StLorentzVectorF.hh"
#include "StThreeVectorF.hh"
#include "StPhysicalHelixD.hh"
#include "phys_constants.h"
#include "SystemOfUnits.h"
#include "StPicoDstMaker/StPicoTrack.h"

#include "StElectronPair.h"

ClassImp(StElectronPair)


StElectronPair::StElectronPair():
mElectronIdx(std::numeric_limits<unsigned short>::quiet_NaN()), 
mPartnerIdx(std::numeric_limits<unsigned short>::quiet_NaN()),
mMass(std::numeric_limits<unsigned short>::quiet_NaN()),
mPairDca(std::numeric_limits<float>::quiet_NaN()),
mPairDecayR(std::numeric_limits<float>::quiet_NaN()),
mPairAngle(std::numeric_limits<float>::quiet_NaN()),
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
mMass(t->mMass),
mPairDca(t->mPairDca),
mPairDecayR(t->mPairDecayR),
mPairAngle(t->mPairAngle),
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
mMass(std::numeric_limits<unsigned short>::quiet_NaN()),
mPairDca(std::numeric_limits<float>::quiet_NaN()),
mPairDecayR(std::numeric_limits<float>::quiet_NaN()),
mPairAngle(std::numeric_limits<float>::quiet_NaN()),
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
    StThreeVectorD DecayPoint = (kAtDcaToPartner/2 + pAtDcaToElectron/2) - pVtx;
    mPairDecayR = static_cast<float>(DecayPoint.mag());
    mPairDca = static_cast<float>(VectorDca.mag());
    
    // calculate Lorentz vector of electron-partner pair
    StThreeVectorF const electronMomAtDca = electronHelix.momentumAt(ss.first, bField * kilogauss);
    StThreeVectorF const partnerMomAtDca = partnerHelix.momentumAt(ss.second, bField * kilogauss);

    StThreeVectorF temp1 (electronMomAtDca.x(),electronMomAtDca.y(),0);
    StThreeVectorF temp2 (partnerMomAtDca.x(),partnerMomAtDca.y(),0);
    StThreeVectorF temp3 (0,electronMomAtDca.y(),electronMomAtDca.z());
    StThreeVectorF temp4 (0,partnerMomAtDca.y(),partnerMomAtDca.z());

    mPairAngle = electronMomAtDca.angle(partnerMomAtDca);
    mPairThetaAngle=temp1.angle(temp2);
    mPairPhi=temp3.angle(temp4);

    StLorentzVectorF const electronFourMom(electronMomAtDca, electronMomAtDca.massHypothesis(M_ELECTRON));
    StLorentzVectorF const partnerFourMom(partnerMomAtDca, partnerMomAtDca.massHypothesis(M_ELECTRON));
    StLorentzVectorF const epairFourMom = electronFourMom + partnerFourMom;

    mMass = static_cast<unsigned int>(epairFourMom.m()*1000) < std::numeric_limits<unsigned short>::max() ?
	static_cast<unsigned short>(epairFourMom.m()*1000) : std::numeric_limits<unsigned short>::quiet_NaN();
    
    StThreeVectorD Position = (kAtDcaToPartner + pAtDcaToElectron)/2.0;

    mPositionX = Position.x();

    mPositionY = Position.y();

    mPositionZ = Position.z();
}
#endif // __ROOT__
