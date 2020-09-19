#ifndef ST_MCDMESONSACCPMAKER_H
#define ST_MCDMESONSACCPMAKER_H

#include <vector>

class TFile;
class TNtuple;

class StMcTrack;
class StTrack;
class StGlobalTrack;
class StPrimaryTrack;
class StAssociationMaker;
class StEvent;
class StMcEvent;
class StMcPixelHit;
class StMcTpcHit;
class StEmcCollection;
class StEmcPosition;
class StEmcGeom;
class StTriggerSimuMaker;

class StEmcRawHit;
class StEmcCluster;
class StSPtrVecEmcCluster;
class StEmcCollection;
class StDedxPidTraits;

#include "StMaker.h"
#include "StThreeVectorD.hh"
#include "StLorentzVectorF.hh"


class StMcDmesonsAccpMaker : public StMaker
{
  private:
    char* outfile;
    std::vector<unsigned int> interesting_triggers;
    std::vector<float> firedTriggersIndices;
    TFile* mFile;

    TNtuple* mD; 
    TNtuple* mEventCount; //.. For counting purposes

    StAssociationMaker* mAssoc;
    StMcEvent* mMcEvent;
    StEvent* mEvent;
    StTriggerSimuMaker* mTrgSimMaker;
    const StTrack* findPartner(StMcTrack* mcTrack, int& maxCommonTpcHits);
    const StMcTrack* findPartner(StGlobalTrack* rcTrack, int& maxCommonTpcHits);
    StDedxPidTraits* findDedxPidTraits(const StTrack* track);
    int get_ndedx(const StTrack* t);

    StEmcCollection* mEmcCollection;
    StEmcPosition*   mEmcPosition;
    StEmcGeom*       mEmcGeom[4];
    StEmcRawHit*     mEmcIndex[4800];
    double mField; //.. magnetic field

    void initEmc();
    void buildEmcIndex();
    bool getBEMC(const StTrack *t, int *id, int *adc, float *ene, int *id0,float *d, int *nep, int *towid);
    bool getBtowDSMAdc(int btowId,int btowId0,int* adc,int* id1);

    bool pass_trigger();
    int fill_eventCount(float nRTracks=-1,float nMcTracks=-1);
    int fill_mTuple_MC(int& nRTracks,int& nMcTracks);
    bool getDaughters(StMcTrack* pTrk,StMcTrack** piTrk,StMcTrack** kTrk);
    StLorentzVectorF* getRecoDzero(StPrimaryTrack* piTrk,StPrimaryTrack* kTrk);
    StLorentzVectorF* getRecoDstar(StLorentzVectorF* kpFourMom,StPrimaryTrack* piTrk);
    void fill_rcTrack(float* array,int& idx,const StTrack* gTrk,StPrimaryTrack* pTrk,int ncom);

  public:
    StMcDmesonsAccpMaker(StTriggerSimuMaker* trgSim, char* outFileName,const std::vector<unsigned int> triggers);
    int Init();
    int Make();
    int Finish();

  ClassDef(StMcDmesonsAccpMaker, 1)
};

#endif
