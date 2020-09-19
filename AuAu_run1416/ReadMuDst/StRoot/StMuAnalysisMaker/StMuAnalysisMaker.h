/*!
 * \class  StMuAnalysisMaker
 * \brief  A typical Analysis Class for MuDst 
 * \author Wei-Ming Zhang, KSU, Mar 2004
 *
 * This is an example of a maker to perform analysis using MuDst.
 *
 * $Id: StMuAnalysisMaker.h,v 1.2 2014/08/06 11:43:31 jeromel Exp $
 *
 * -------------------------------------------------------------------------
 * $Log: StMuAnalysisMaker.h,v $
 * Revision 1.2  2014/08/06 11:43:31  jeromel
 * Suffix on literals need to be space (later gcc compiler makes it an error) - first wave of fixes
 *
 * Revision 1.1  2004/08/10 16:09:11  perev
 * new GridCollector stuff
 *
 * -------------------------------------------------------------------------
 */
#ifndef StMuAnalysisMaker_hh     
#define StMuAnalysisMaker_hh
//
//  Include files
#include "StMaker.h"
#include <string>
#include "StThreeVectorF.hh"
//
//  Forward declarations
class StMuTrack;
class StMuMcTrack;
class TFile;
class TH1D;
class TTree;

#ifndef ST_NO_NAMESPACES
using std::string;
#endif
//
//  The class declaration. It innherits from StMaker.
class StMuAnalysisMaker : public StMaker {
public:

    StMuAnalysisMaker(const Char_t *name, char const * outfile);   // constructor
    ~StMuAnalysisMaker();                                 // destructor
    
    void Clear(Option_t *option=""); // called after every event to cleanup 
    Int_t  Init();                   // called once at the beginning of your job
    Int_t  Make();                   // invoked for every event
    Int_t  Finish();                 // called once at the end

    virtual const char *GetCVS() const {
      static const char cvs[]="Tag $Name: SL19b $ $Id: StMuAnalysisMaker.h,v 1.2 2014/08/06 11:43:31 jeromel Exp $ built " __DATE__ " " __TIME__ ; 
      return cvs;
    }

private:

// data member  
    int        mEventCounter;  //!
    TString     mFileName;      //!
    TFile      *mFile;         //!

    TH1D *mGlobalPt;           //!
    TH1D *mPrimaryPt;          //!
    TH1D *mL3Pt;               //!
    TH1D *mRefMult;            //!
    TTree *Signal_tree;
    TTree *Gen_tree;
    void fillGenTree(StMuMcTrack* track,StThreeVectorF pVtx);
    void fillTree(StMuTrack* tp,StMuMcTrack *tmc,StThreeVectorF pVtx, int centrality);
    float  sig_chi2,sig_IstTruth ,sig_SsdTruth,sig_Pxl1Truth,sig_Pxl2Truth,sig_isiso,sig_hft,sig_head,run_id,event_centrality, event_qy,event_qy1, event_qy2, event_qx,event_qx1, event_qx2,sig_mva,sig_dca,sig_dcaz,sig_p,sig_pt,sig_eta,sig_phi,sig_nsige,sig_nsigpi,sig_nsigk,sig_nsigp,sig_dcaxy,sig_beta,sig_emc0,sig_id,sig_neta,sig_nphi,sig_charge,sig_phidist, sig_phi2,sig_zdist, sig_yloc, sig_triggercat, sig_parentid, sig_gparentid,sig_ggparentid,sig_parentpt, sig_gparentpt,sig_ggparentpt,sig_parentphi,sig_gparentphi,sig_vz,sig_vy,sig_vx;
    float  gen_ox,gen_oy,gen_orig, gen_origxy,gen_head,gen_run_id,gen_event_centrality,gen_dca,gen_p,gen_pt,gen_eta,gen_phi,gen_nsige,gen_nsigpi,gen_nsigk,gen_nsigp,gen_dcaxy,gen_id,gen_charge, gen_phi2, gen_parentid, gen_gparentid,gen_ggparentid,gen_vz,gen_vy,gen_vx,gen_refmult,gen_grefmult,gen_parentpt, gen_gparentpt,gen_ggparentpt;
    int get_centrality(float mul);




// method (a simple track filter)
    bool accept(StMuTrack*);            // and this is used to select tracks

    ClassDef(StMuAnalysisMaker,0)
};
#endif
