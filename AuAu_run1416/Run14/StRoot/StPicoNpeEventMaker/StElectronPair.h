#ifndef StElectronPair_hh
#define StElectronPair_hh
#ifdef __ROOT__

/* **************************************************
 *  A specialized pair class for calculating electron pair
 *  lorentz vector and topological decay parameters
 *  and storing them.
 *
 *  Authors:  **Kunsu OH        (kunsuoh@gmail.com)
 *            Mustafa Mustafa (mmustafa@lbl.gov)
 *
 *  **Code Maintainer
 * **************************************************
 */

#include "TObject.h"
#include "TVector3.h"

class StPicoTrack;
class StPicoEvent;

class StElectronPair : public TObject
{
public:
    StElectronPair();
    StElectronPair(StElectronPair const *);
    StElectronPair(StPicoTrack const * Electron, StPicoTrack const * Partner,
                   unsigned short electronIdx,unsigned short partnerIdx, float bField,TVector3 pVtx);
    ~StElectronPair() {}// please keep this non-virtual and NEVER inherit from this class
    
    unsigned short   electronIdx() const;	// tagged electron idx
    unsigned short   partnerIdx() const;	// partner electron idx
    float pairMass()    const;                     // electron pair mass
    float pairMassPion()    const;                     // electron pair mass 
    float pairMassKaon()    const;                     // electron pair mass  
    float pairMassProtonPion()    const;                     // electron pair mass  
    float pairEta()    const;                     // electron pair mass
    float pairDca() const;                  // DCA between tagged and partner
    float Dca() const;                  // DCA between tagged and partner 
    float pairDecayR() const;                  // Conversion radius
    float pairDecayL() const;                  // Conversion radius
    float positionX() const;                // conversion position X
    float positionY() const;                // conversion position Y
    float positionZ() const;                // conversion position Z
    float pairAngle() const;                // angle between electron pair
    float pairDipAngle() const;                // angle between electron pair                                                                                                                                                                                  
    float pairThetaAngle() const;                // thetaangle between electron pair  
    float pairPhi() const;                // phi between electron pair      
    
private:
    // disable copy constructor and assignment operator by making them private (once C++11 is available in STAR you can use delete specifier instead)
    StElectronPair(StElectronPair const &);
    StElectronPair& operator=(StElectronPair const &);
    
    unsigned short mElectronIdx;    // index of electron track in StPicoDstEvent (2 Bytes)
    unsigned short mPartnerIdx;     // index of partner track in StPicoDstEvent (2 Bytes)
    float mEta;           // Eta
    float mMass;
    float mMassPion;// mass * 1000 (2 Bytes)
    float mMassKaon;// mass * 1000 (2 Bytes)
    float mMassProtonPion;// mass * 1000 (2 Bytes)
    float mPairDca;
    float mDca;// pair dca (4 Bytes)
    float mPairDecayR;                 // pair conv R (4 Bytes)
    float mPairDecayL;
    float mPairAngle;
    float mPairDipAngle;
    float mPairThetaAngle;
    float mPairPhi;
    float mPositionX;               // conversion position x (4 Bytes)
    float mPositionY;               // conversion position y (4 Bytes)
    float mPositionZ;               // conversion position z (4 Bytes)
            
    ClassDef(StElectronPair,2)
};
inline unsigned short   StElectronPair::electronIdx() const     { return mElectronIdx;                        }
inline unsigned short   StElectronPair::partnerIdx() const      { return mPartnerIdx;                         }
inline float StElectronPair::pairEta() const                    { return mEta;  }
inline float StElectronPair::pairMass()    const                { return mMass;     }
inline float StElectronPair::pairMassPion()    const                { return mMassPion;     }
inline float StElectronPair::pairMassKaon()    const                { return mMassKaon;     }
inline float StElectronPair::pairMassProtonPion()    const                { return mMassProtonPion;     }
inline float StElectronPair::pairDca() const                    { return mPairDca;  }
inline float StElectronPair::Dca() const                    { return mDca;  }
inline float StElectronPair::pairDecayR() const                    { return mPairDecayR;  }
inline float StElectronPair::pairDecayL() const                    { return mPairDecayL;  }
inline float StElectronPair::positionX() const                  { return mPositionX;}
inline float StElectronPair::positionY() const                  { return mPositionY;}
inline float StElectronPair::positionZ() const                  { return mPositionZ;}
inline float StElectronPair::pairAngle() const                  { return mPairAngle;}
inline float StElectronPair::pairDipAngle() const                  { return mPairDipAngle;}
inline float StElectronPair::pairThetaAngle() const             { return mPairThetaAngle;}
inline float StElectronPair::pairPhi() const                    { return mPairPhi;}
#endif
#endif

