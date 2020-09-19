#ifndef StPicoMcNpeAnaMaker_h
#define StPicoMcNpeAnaMaker_h

/* **************************************************
 *  A Maker that reads StPicoEvents and creates
 *  StLowPtNpeAnas and stores them.
 *
 *  Authors:  **Kunsu OH        (kunsuoh@gmail.com)
 *
 *  **Code Maintainer
 * **************************************************
 */
#include "TChain.h"
#include "StMaker.h"
#include "TNtuple.h"
#include "TH2F.h"
#include "TH1F.h"
#include "StarClassLibrary/StThreeVectorF.hh"
#include "StEvent/StDcaGeometry.h"
#include "THnSparse.h"
#include "StPicoDstMaker/StPicoEvent.h"
#include "StPicoDstMaker/StPicoTrack.h"
#include "StPicoDstMaker/StPicoMcTrack.h"

class TTree;
class TFile;
class TString;
class TNtuple;
class StPicoDst;
class StPicoDstMaker;
class StPicoEvent;
class StPicoTrack;
class StPicoMcTrack;
class TString;
class StDcaGeometry;
class StElectronPair;
class StRefMultCorr;
class CentralityMaker;
class StPicoMcNpeAnaMaker : public StMaker
{
public:
    StPicoMcNpeAnaMaker(char const* makerName, StPicoDstMaker* picoMaker, char const* fileBaseName);
    virtual ~StPicoMcNpeAnaMaker();
    
    virtual Int_t Init();
    virtual Int_t Make();
    virtual void  Clear(Option_t *opt="");
    virtual Int_t Finish();
    float getDLL(StPicoTrack const *trk);
    StRefMultCorr* mRefMultCorr; 
    int centrality;
    TH1F* mranMass;
    TH1F* mranDca;
    TH1F* mranDR;
    TH1F* mranDP;
private:
    bool  isGoodEvent();
    bool  isGoodTrack(StPicoTrack const*) const;
    bool  isElectron(StPicoTrack const*) const;
    bool  isTaggedElectron(StPicoTrack const*) const;
    bool  isPartnerElectron(StPicoTrack const*) const;
    bool  isGoodElectronPair(StElectronPair const &, float) const;
    bool  isRcTrack(StPicoMcTrack const * const trk ,StPicoDst const * const PicoDst, int & id, int arr[]);
    bool  isMcTrack(StPicoTrack const * const trk ,StPicoDst const * const PicoDst);
    bool  isMcSibling(StPicoMcTrack const * const mctrk ,StPicoMcTrack const * const trk ,StPicoDst const * const PicoDst);
    bool  isHftTrack(StPicoTrack const * const trk) const;
    void  getParent(StPicoDst const * const picoDst, StPicoMcTrack const * const mcTrk, int & parentid, int & parentGid, float & parentMcPt, bool isMore);
    bool isMCElectron(StPicoMcTrack const *trk);
    int findParent(StPicoDst const * const picoDst, int id);
    int  isRecoTrack(StPicoMcTrack const * const trk ,StPicoDst const * const PicoDst);
    bool isPass(StPicoTrack const *trk, StThreeVectorF pVtx);
    void fillTree(StPicoTrack*, StPicoMcTrack*, StThreeVectorF,bool, bool, bool, bool,double,double,double,double,double,double,double);
    void fillGenTree(StPicoMcTrack*, StThreeVectorF,double,double,double,double,double,double);
    void fillEHTree(StPicoTrack*, StPicoMcTrack*, StPicoTrack*,StPicoMcTrack*,StThreeVectorF,bool, bool, bool, bool,double,double,double,double,double,double);
    void fillRanHist(StPicoTrack*, StPicoMcTrack*, StPicoTrack*,StPicoMcTrack*,StThreeVectorF,bool, bool, bool, bool,double,double,double,double,double,double);
    StPicoDstMaker* mPicoDstMaker;
    StPicoEvent*    mPicoEvent;
    TFile* mOutputFile;
    TH1F * hMcIds;
    TTree *Signal_tree;
    TTree *Gen_tree;
    TTree *EH_tree;
    Float_t distHits;
    UChar_t nHits1_pxl1, nHits1_pxl2, nHits1_ist, nHits1_ssd;
    UChar_t nHits2_pxl1, nHits2_pxl2, nHits2_ist, nHits2_ssd;
    UChar_t nHits_pxl1, nHits_pxl2, nHits_ist, nHits_ssd;
    TH1F* mElectronWeights[5];
    TH1F* mPionWeights[5];    
    UChar_t truth1_pxl1, truth1_pxl2, truth1_ist, truth1_ssd;
    UChar_t truth2_pxl1, truth2_pxl2, truth2_ist, truth2_ssd;
    UChar_t truth_pxl1, truth_pxl2, truth_ist, truth_ssd;
    
    UChar_t rcHftHit1_pxl1, rcHftHit1_pxl2, rcHftHit1_ist, rcHftHit1_ssd;
    UChar_t rcHftHit2_pxl1, rcHftHit2_pxl2, rcHftHit2_ist, rcHftHit2_ssd;
    UChar_t rcHftHit_pxl1, rcHftHit_pxl2, rcHftHit_ist, rcHftHit_ssd;
    float  sig_hft,sig_head,run_id,event_centrality, event_qy,event_qy1, event_qy2, event_qx,event_qx1, event_qx2,sig_mva,sig_dca,sig_p,sig_pt,sig_eta,sig_phi,sig_nsige,sig_nsigpi,sig_nsigk,sig_nsigp,sig_dcaxy,sig_beta,sig_emc0,sig_id,sig_neta,sig_nphi,sig_charge,sig_phidist, sig_phi2,sig_zdist, sig_yloc, sig_triggercat, sig_parentid, sig_gparentid,sig_ggparentid,sig_parentpt, sig_gparentpt,sig_ggparentpt,sig_parentphi,sig_vz,sig_vy,sig_vx,sig_ox,sig_oy,sig_oz,sig_refmult,sig_grefmult; 

    float  gen_orig, gen_origxy,gen_head,gen_run_id,gen_event_centrality, gen_event_qy,gen_event_qy1, gen_event_qy2, gen_event_qx,gen_event_qx1, gen_event_qx2,gen_mva,gen_dca,gen_p,gen_pt,gen_eta,gen_phi,gen_nsige,gen_nsigpi,gen_nsigk,gen_nsigp,gen_dcaxy,gen_beta,gen_emc0,gen_id,gen_neta,gen_nphi,gen_charge,gen_phidist, gen_phi2,gen_zdist, gen_yloc, gen_triggercat, gen_parentid, gen_gparentid,gen_ggparentid,gen_vz,gen_vy,gen_vx,gen_refmult,gen_grefmult; 
  
    float eh_h_charge,eh_head,eh_id,eh_run_id,eh_event_centrality, eh_event_qy,eh_event_qy1, eh_event_qy2, eh_event_qx,eh_event_qx1, eh_event_qx2,eh_mva,eh_dca,eh_p,eh_pt,eh_h_p,eh_h_pt,eh_eta,eh_phi,eh_nsige,eh_nsigpi,eh_nsigk,eh_nsigp,eh_dcaxy,eh_beta,eh_emc0,eh_neta,eh_nphi,eh_charge,eh_phidist, eh_phi2,eh_zdist, eh_yloc, eh_triggercat, eh_parentid, eh_gparentid,eh_ggparentid,eh_parentpt, eh_gparentpt,eh_ggparentpt,eh_vz,eh_vy,eh_vx,eh_refmult,eh_grefmult,eh_pair_dca,eh_h_dca,eh_h_dcaxy,eh_comb_eta,eh_comb_phi,eh_comb_mass,eh_comb_dcaxy,eh_comb_dca,eh_h_nsige,eh_h_nsigpi,eh_h_nsigk,eh_h_nsigp,eh_h_ismc,eh_pair_sib,eh_pair_decayr,eh_pair_decaypos,eh_pair_angle,eh_pair_thetaangle,eh_pair_phi;    
    ClassDef(StPicoMcNpeAnaMaker, 0)
};


#endif
