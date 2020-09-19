#ifndef StPicoNpeAnaMaker_h
#define StPicoNpeAnaMaker_h

/* **************************************************
 *  A Maker to read a StPicoEvent and StPicoNpeEvent
 *  simultaneously and do analysis. 
 *
 *  Please write your analysis in the ::Make() function.
 *
 *  Authors:  Xin Dong        (xdong@lbl.gov)
 *            Michael Lomnitz (mrlomnitz@lbl.gov)
 *            Mustafa Mustafa (mmustafa@lbl.gov)
 *            Jochen Thaeder  (jmthader@lbl.gov)   
 *          **Kunsu OH        (kunsuoh@gmail.com)
 *
 *  ** Code Maintainer
 *
 * **************************************************
 */

#include "TChain.h"
#include "StMaker.h"
#include "TH2F.h"
#include "TF1.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TNtuple.h"
#include "StThreeVectorF.hh"
#include "THnSparse.h"
#include "TLorentzVector.h"
#include "StLorentzVectorF.hh"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "TMVA/MethodCuts.h"
class TString;
class TFile;
class TNtuple;
class StPicoNpeEvent;
class StElectronTrack;
class StElectronPair;
class StPicoDstMaker;
class StPicoTrack;
class StPicoDst;
class StPicoPrescales;
class TTree;
class StRefMultCorr;
class StNpeCuts;
class CentralityMaker;
class StPicoNpeAnaMaker : public StMaker
{
  public:
    StPicoNpeAnaMaker(char const * name, char const * inputFilesList, 
        char const * outName,StPicoDstMaker* picoDstMaker);
    virtual ~StPicoNpeAnaMaker();

    virtual Int_t Init();
    virtual Int_t Make();
    virtual Int_t Finish();

    int getEntries() const;

    void setNpeCuts(StNpeCuts* cuts);
    void phiCalculation(StLorentzVectorF ,StLorentzVectorF , double , Float_t &, Float_t &);

    StRefMultCorr* mRefMultCorr;    
    int centrality;    
    int nType;
  private:
    StPicoNpeAnaMaker() {}
    void readNextEvent();
    void fillHistogram(StPicoTrack*, StThreeVectorF, int, int, TString);
    void fillMyHistogram(StPicoTrack*, StThreeVectorF, bool, bool, bool, bool, bool, double);
    void fillPairHistogram(StPicoTrack*, StThreeVectorF,  bool, bool, bool, bool, int,double);
    void fillEventTree(float, float, float, float, float, float, float);
    void fillTree(StPicoTrack*, StThreeVectorF,  bool, bool, bool, bool,double,float, float, float, float, float, float, float);
    void fillEHTree(StPicoTrack*, StPicoTrack*,StThreeVectorF, bool, bool, bool, bool, float, float, float, float, float, float, float, int, double);

    void fillJPsiTree(StElectronPair *,StPicoTrack*,StPicoTrack*, StThreeVectorF,  bool, bool, bool, bool, int, int, double);
    void fillKShortTree(StElectronPair *,StPicoTrack*,StPicoTrack*, StThreeVectorF,  bool, bool, bool, bool, int, int, double);
    void fillPhiTree(StElectronPair *,StPicoTrack*,StPicoTrack*, StThreeVectorF,  bool, bool, bool, bool, int, int, double);
    void fillLambdaTree(StElectronPair *,StPicoTrack*,StPicoTrack*, StThreeVectorF,  bool, bool, bool, bool, int, int, double);
    void fillPhoETree(StElectronPair *,StPicoTrack*,StPicoTrack*, StThreeVectorF,  bool, bool, bool, bool, int, int, double,float,float,float,float,float,float,float);
    void fillBKGTree(StPicoTrack*, StThreeVectorF,  bool, bool, bool, bool, double,float, float, float, float, float, float, float);
    bool isGoodPair(StElectronPair const*) const;
    bool checkHadronDca(StPicoTrack*, StThreeVectorF, double, double); 
    bool isIso(StPicoTrack const *);
    StPicoDstMaker* mPicoDstMaker;
    StPicoNpeEvent* mPicoNpeEvent;

    TString mOutFileName;
    TString mInputFileList;
    TFile* mOutputFile;
    TChain* mChain;
    int mEventCounter;
    std::vector<int> mIsoEs;
    StNpeCuts* mNpeCuts;

    
    // -------------- USER variables -------------------------
    // add your member variables here. 
    // Remember that ntuples size can be really big, use histograms where appropriate
    //TH1F * hEoverP_h;   
    TH1I * h1dEvent;
    TH1I * h1dEventRefMult;
    TH1I * h1dEventTrigger;
    TH1I * h1dEventCentrality; 
    TH1I * h1dTrack; 
    //TH1F * hBTOWId;
    //TH1F * hRunID;
    //TH1F * hBAdc;
    //TH2F * hDsmAdc;
    //TH1F * hBnPhi;
    //TH1F * hBnEta;
    //TH1F * hBPhiDist;
    //TH1F * hBZDist;
    //TH1F * hEoverP_all;
    //TH1F * hQaPt;
    //TH1F * hQaEta;
    //TH2F * hQaDca;
    TH1F * hQaVxZ;
    TH1F * hQaVxY;
    TH1F * hQaVxX;
    TH2F * hQaDcaXY8;
    TH2F * hQaDcaXY7;
    TH2F * hQaDcaXY6;
    TH2F * hQaDcaXY5;
    TH2F * hQaDcaXY4;
    TH2F * hQaDcaXY3;
    TH2F * hQaDcaXY2;
    TH2F * hQaDcaXY1;
    TH2F * hQaDcaZ8;
    TH2F * hQaDcaZ7;
    TH2F * hQaDcaZ6;
    TH2F * hQaDcaZ5;
    TH2F * hQaDcaZ4;
    TH2F * hQaDcaZ3;
    TH2F * hQaDcaZ2;
    TH2F * hQaDcaZ1;
    TH2F * hQaLogDca;
    TH2F * hQaLogDcaTOF;
    TH1F * hQaNHitFit;
    TH1F * hQaNHitDedx; 
    //TH2F * hBeta;
    //TH1F * hMVA;
    //TH2F * hnSigma;
    TH1F * M2;				
    TH2F * hFit[10];
    TH2F * hFit_e[10];
    //TH2F * hFit_EH[10];
    //TH2F * hFit_MVA[10];
    TH2F * hFit_e_WS[10];
    TH2F * hFit_p[10];
    TH2F * hFit_pi[10];
    TH2F * hFit_2pi[10];
    TH2F * hFit_k[10];

    TH2F * hDca[8];
    TH2F * hDca_e[8];
    TH2F * hDca_e_WS[8];
    TH2F * hDca_p[8];
    TH2F * hDca_pi[8];
    TH2F * hDca_2pi[8];
    TH2F * hDca_k[8];

    TH2F * hDcaLog3D[8];
    TH2F * hDcaLog3D_e[8];
    TH2F * hDcaLog3D_e_WS[8];
    TH2F * hDcaLog3D_p[8];
    TH2F * hDcaLog3D_pi[8];
    TH2F * hDcaLog3D_2pi[8];
    TH2F * hDcaLog3D_k[8];

    TH2F * hDca3D[8];
    TH2F * hDca3D_e[8];
    TH2F * hDca3D_e_WS[8];
    TH2F * hDca3D_p[8];
    TH2F * hDca3D_pi[8];
    TH2F * hDca3D_2pi[8];
    TH2F * hDca3D_k[8];

    TH2F * hDcaz[8];
    TH2F * hDcaz_e[8];
    TH2F * hDcaz_e_WS[8];
    TH2F * hDcaz_p[8];
    TH2F * hDcaz_pi[8];
    TH2F * hDcaz_2pi[8];
    TH2F * hDcaz_k[8];

    TH2F * hFit2D[8];
    TH2F * hFit2D_e[8];
    TH2F * hFit2D_e_WS[8];
    //TH2F * hFit2D_p[10];
    TH2F * hFit2D_pi[8];
    //TH2F * hFit2D_2pi[10];
    //TH2F * hFit2D_k[10];

    TH2F * hHadronV2;
    TH2F * hHadronV22060;
    TH2F * hHadronV2gweight;
    TH2F * hHadronV2gweight2060;
    TH2F * hInvRes;
    TH2F * hInvRes2060;
    TH2F * hInvResgweight;
    TH2F * hInvResgweight2060;
    TH2F * hHftRatio_d;
    TH2F * hHftRatio_n;
    TH2F * hHftRatio_eta_d;
    TH2F * hHftRatio_eta_n;
    TH2F * hHftRatio_phi_d;
    TH2F * hHftRatio_phi_n;
    TH2F * hHftRatio_z_d;
    TH2F * hHftRatio_z_n;
    TH2F * hEventPlane_Res;
    TH1F * hEventPlane;
    TH1F * hEventPlane_Corr1;
    TH1F * hEventPlane_Corr2;
    TTree *Event_tree;
    TTree *Signal_tree;
    TTree *EH_tree;
    TTree *JPsi_tree;
    TTree *Ks_tree;
    TTree *Lambda_tree;
    TTree *Phi_tree;
    TTree *PhoE_tree;
    TTree *BKG_tree;
    //Tree Variables  
    float ep_run_id,ep_event_centrality, ep_event_qy,ep_event_qy1, ep_event_qy2, ep_event_qx,ep_event_qx1, ep_event_qx2, ep_event_cen;
    float run_id,event_centrality, event_qy,event_qy1, event_qy2, event_qx,event_qx1, event_qx2,sig_chi2,sig_mva,sig_mva_ht,sig_dca,sig_dcaz,sig_p,sig_pt,sig_eta,sig_phi,sig_nsige,sig_nsigpi,sig_nsigk,sig_nsigp,sig_dcaxy,sig_beta,sig_emc0,sig_neta,sig_nphi,sig_charge,sig_phidist, sig_phi2,sig_zdist, sig_yloc, sig_triggercat, event_cen, event_g_qy,event_g_qy1, event_g_qy2, event_g_qx,event_g_qx1, event_g_qx2, sig_isiso, event_gweight;

    float eh_ncan,eh_run_id,eh_event_centrality,eh_event_qy,eh_event_qy1, eh_event_qy2, eh_event_qx,eh_event_qx1, eh_event_qx2,eh_pair_dca,eh_eta,eh_phi,eh_dcaxy,eh_dca,eh_pair_decayr,eh_pair_decaypos,eh_e_charge,eh_h_charge,eh_triggercat,eh_pair_angle, eh_pair_thetaangle,eh_pair_phi,eh_mass,eh_endvertex_x,eh_endvertex_y,eh_endvertex_z,eh_vertex_x,eh_vertex_y,eh_e_dcaz,eh_h_dcaz,eh_e_dcaxy,eh_e_dca,eh_h_dcaxy,eh_h_dca,eh_vertex_z,eh_e_px,eh_e_mva,eh_e_pz,eh_e_py,eh_h_px,eh_h_pz,eh_h_py,eh_h_nsigpi,eh_h_nsigk,eh_h_nsige,eh_e_nsige,eh_h_beta,eh_h_isprimary,eh_e_isprimary,eh_event_g_qy,eh_event_g_qy1, eh_event_g_qy2, eh_event_g_qx,eh_event_g_qx1, eh_event_g_qx2, eh_event_gweight;

    float JPsi_M,probe_mva,probe_p,probe_pt,probe_ncan,probe_dcaxy,probe_dca,probe_nsige,probe_nsigpi,probe_nsigk,probe_nsigp,probe_beta,probe_emc0,probe_neta,probe_nphi, probe_charge, tag_charge,tag_trigger, tag_beta,tag_mva,pair_theta, pair_dca, probe_phidist, probe_zdist, probe_yloc;

    float Ks_M,Ks_probe_mva,Ks_probe_p,Ks_probe_phi,Ks_tag_p,Ks_probe_pt,Ks_probe_ncan,Ks_probe_dcaxy,Ks_probe_dca,Ks_probe_nsige,Ks_probe_nsigpi,Ks_probe_nsigk,Ks_probe_nsigp,Ks_probe_beta,Ks_probe_emc0,Ks_probe_neta,Ks_probe_nphi, Ks_probe_charge, Ks_tag_charge,Ks_tag_trigger, Ks_tag_beta,Ks_tag_mva,Ks_pair_theta, Ks_pair_dca, Ks_probe_phidist, Ks_probe_zdist, Ks_probe_yloc,Ks_triggercat;

    float Phi_M,Phi_probe_mva,Phi_probe_p,Phi_probe_pt,Phi_probe_ncan,Phi_probe_dcaxy,Phi_probe_dca,Phi_probe_nsige,Phi_probe_nsigpi,Phi_probe_nsigk,Phi_probe_nsigp,Phi_probe_beta,Phi_probe_emc0,Phi_probe_neta,Phi_probe_nphi, Phi_probe_charge, Phi_tag_charge,Phi_tag_trigger, Phi_tag_beta,Phi_tag_mva,Phi_pair_theta, Phi_pair_dca, Phi_probe_phidist, Phi_probe_zdist, Phi_probe_yloc,Phi_triggercat;

    float Lambda_M,Lambda_probe_mva,Lambda_probe_p,Lambda_probe_pt,Lambda_probe_ncan,Lambda_probe_dcaxy,Lambda_probe_dca,Lambda_probe_nsige,Lambda_probe_nsigpi,Lambda_probe_nsigk,Lambda_probe_nsigp,Lambda_probe_beta,Lambda_probe_emc0,Lambda_probe_neta,Lambda_probe_nphi, Lambda_probe_charge, Lambda_tag_charge,Lambda_tag_trigger, Lambda_tag_beta,Lambda_tag_mva,Lambda_pair_theta, Lambda_pair_dca, Lambda_probe_phidist, Lambda_probe_zdist, Lambda_probe_yloc,Lambda_triggercat;

    float phoe_event_gweight,phoe_event_centrality,phoe_event_qy,phoe_event_qy1, phoe_event_qy2, phoe_event_qx,phoe_event_qx1,phoe_probe_chi2,phoe_tag_chi2, phoe_event_qx2,phoe_run_id,PhoE_M,phoe_probe_ncan,phoe_probe_phi,phoe_probe_mva,phoe_pair_decayradius, phoe_pair_dca,phoe_pair_theta,phoe_pair_phi,phoe_pair_costheta,phoe_probe_p,phoe_probe_pt,phoe_probe_nsige,phoe_probe_nsigpi,phoe_probe_nsigk,phoe_probe_nsigp,phoe_probe_dcaxy,phoe_probe_dca,phoe_probe_beta,phoe_probe_emc0,phoe_probe_neta,phoe_probe_nphi,phoe_probe_charge, phoe_tag_charge,phoe_tag_mva,phoe_tag_beta, phoe_probe_phidist, phoe_probe_zdist, phoe_probe_yloc,phoe_triggercat, phoe_isiso, phoe_probe_dcaz;

    float bkg_event_centrality,  bkg_probe_eta,bkg_probe_phi,bkg_probe_phi2,bkg_event_qy,bkg_event_qy1, bkg_event_qy2, bkg_event_qx,bkg_event_qx1, bkg_event_qx2,bkg_run_id,bkg_probe_p,bkg_probe_pt,bkg_probe_nsige,bkg_probe_mva,bkg_probe_nsigpi,bkg_probe_nsigk,bkg_probe_nsigp,bkg_probe_dcaxy,bkg_probe_dca,bkg_probe_beta,bkg_probe_emc0,bkg_probe_neta,bkg_probe_nphi,bkg_probe_charge, bkg_probe_phidist,bkg_probe_zdist,bkg_probe_bkgcat,bkg_probe_yloc,bkg_triggercat, bkg_isiso, bkg_probe_dcaz;

    Int_t refmult;
    Float_t gweight;
    TH2F * run_centrality_corrx;
    TH2F * run_centrality_corry;
    TH2F * run_centrality_corrx1;
    TH2F * run_centrality_corry1;
    TH2F * run_centrality_corrx2;
    TH2F * run_centrality_corry2; 
    TH2F * centrality_resolution;
    ClassDef(StPicoNpeAnaMaker, 0)
};

inline int StPicoNpeAnaMaker::getEntries() const 
{
  return mChain? mChain->GetEntries() : 0;
}

inline void StPicoNpeAnaMaker::readNextEvent()
{
  mChain->GetEntry(mEventCounter++);
}
inline void StPicoNpeAnaMaker::setNpeCuts(StNpeCuts* cuts)
{
    mNpeCuts = cuts;
}


#endif
