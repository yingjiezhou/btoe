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
#include <map>
#include "TF1.h"
//
//  Forward declarations
class StMuTrack;
class TFile;
class TH1D;
class TH2F;
class StMuDst;
class StRefMultCorr;

#ifndef ST_NO_NAMESPACES
using std::string;
#endif
//
//  The class declaration. It innherits from StMaker.
class StMuAnalysisMaker : public StMaker {
public:

    StMuAnalysisMaker(const Char_t *name="muAnalysis", std::string jobid="0");   // constructor
    ~StMuAnalysisMaker();                                 // destructor
    
    void Clear(Option_t *option=""); // called after every event to cleanup 
    Int_t  Init();                   // called once at the beginning of your job
    Int_t  Make();                   // invoked for every event
    Int_t  Finish();                 // called once at the end
    void muEventInfo(const StMuDst &mu);
    int get_phibin(float phi); 
    int get_phibin2(float phi); 

    virtual const char *GetCVS() const {
      static const char cvs[]="Tag $Name:  $ $Id: StMuAnalysisMaker.h,v 1.2 2014/08/06 11:43:31 jeromel Exp $ built " __DATE__ " " __TIME__ ; 
      return cvs;
    }

private:

// data member  
    enum {
       NCENT = 9,
       NQUAL = 6,
       NPID  = 6,
       NCUT  = 6,
       NVZ   = 6
    };

    int        mEventCounter;  //!
    string     mFileName;      //!
    TFile      *mFile;         //!

    StRefMultCorr* mRefMultCorr;

    void fillGenTree(const StMuTrack* track,StThreeVectorF pVtx,TClonesArray *mcTracks);
    void getParent(TClonesArray *mcTracks, StMuMcTrack const * const mcTrk, int & parentid, int & parentGid, float & parentMcPt, bool isMore = true);
    void fillTree(StMuTrack* tp,StMuMcTrack *tmc,StThreeVectorF pVtx);
    float  sig_chi2,sig_IstTruth ,sig_SsdTruth,sig_Pxl1Truth,sig_Pxl2Truth,sig_isiso,sig_hft,sig_head,run_id,event_centrality, event_qy,event_qy1, event_qy2, event_qx,event_qx1, event_qx2,sig_mva,sig_dca,sig_dcaz,sig_p,sig_pt,sig_eta,sig_phi,sig_nsige,sig_nsigpi,sig_nsigk,sig_nsigp,sig_dcaxy,sig_beta,sig_emc0,sig_id,sig_neta,sig_nphi,sig_charge,sig_phidist, sig_phi2,sig_zdist, sig_yloc, sig_triggercat, sig_parentid, sig_gparentid,sig_ggparentid,sig_parentpt, sig_gparentpt,sig_ggparentpt,sig_parentphi,sig_gparentphi,sig_vz,sig_vy,sig_vx,sig_ox,sig_oy,sig_oz,sig_refmult,sig_grefmult;
    float  gen_ox,gen_oy,gen_orig, gen_origxy,gen_head,gen_run_id,gen_event_centrality, gen_event_qy,gen_event_qy1, gen_event_qy2, gen_event_qx,gen_event_qx1, gen_event_qx2,gen_mva,gen_dca,gen_p,gen_pt,gen_eta,gen_phi,gen_nsige,gen_nsigpi,gen_nsigk,gen_nsigp,gen_dcaxy,gen_beta,gen_emc0,gen_id,gen_neta,gen_nphi,gen_charge,gen_phidist, gen_phi2,gen_zdist, gen_yloc, gen_triggercat, gen_parentid, gen_gparentid,gen_ggparentid,gen_vz,gen_vy,gen_vx,gen_refmult,gen_grefmult,gen_parentpt, gen_gparentpt,gen_ggparentpt;


    TH1F* hEventId;
    TH2F *hVxVy[2];
    TH2F *hVzCorr;   // VzVpd vs. VzTpc
    TH2F *hRefCorr;  // gRefMult vs. refMult
    TH2F *hRcTPCPtEta;
    TH2F *hMcTPCPtEta;
    TH2F *hRcHFTPtEta;
    TH2F *hMcHFTPtEta;
    TH2F *hMcHFTGoodPtEta;
    TH2F *hPtCorr;                    
    TH2F *hNHitsPxl1Ist;
    TH2F *hNHitsPxl2Ist;
    TH2F *hNHitsPxl1Ssd;
    TH2F *hNHitsPxl2Ssd;
    
    TH1D *hGlobalPt;           //!
    TH1D *hPrimaryPt;          //!
    TH1D *hPrimaryPtHft;          //!
    TH1D *hL3Pt;               //!
    TH1D *hRefMult;            //!

    TH2F* hMcPtEta [NCENT][NPID];
    TH2F* hMcPtPhi [NCENT][NPID];
    TH2F* hMc2PtEta[NCENT][NPID];
    TH2F* hMc2PtPhi[NCENT][NPID];

    TH2F* hRcPtEta [NCENT][NPID][NCUT];
    TH2F* hRcPtPhi [NCENT][NPID][NCUT];
    TH2F* hRc2PtEta[NCENT][NPID][NCUT];
    TH2F* hRc2PtPhi[NCENT][NPID][NCUT];

   
    TH2F* hPrimCorr2;

    // method (a simple track filter)
    bool accept(StMuTrack*);            // and this is used to select tracks
    bool accept_pion(StMuTrack*);            // and this is used to select tracks
    bool accept2(StMuTrack*);            // and this is used to select tracks
    bool acceptb(const StMuTrack*);            // and this is used to select tracks
    bool accept2b(const StMuTrack*);            // and this is used to select tracks

    int get_centrality(float mul);

     unsigned int triggers[6];
     int NTRIG;
     int NRUNS;
     int cntbad;
     std::string mId;

     std::map<int,std::string> runMap;
     float Verror;

     TH1F* hPtBinsDca;

     TF1* funSpec;

     std::vector<float> dcasigma;

    ClassDef(StMuAnalysisMaker,0)
};
#endif
