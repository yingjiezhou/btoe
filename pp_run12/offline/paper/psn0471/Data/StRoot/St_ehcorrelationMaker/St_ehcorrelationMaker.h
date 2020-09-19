// Based on the MuDST tools written by Frank Laue.
// Based on the DST Tutorial by Dan Magestro on the STAR Computing/Tutorials page.
// Updated 9/4/2006 by Jim Thomas to include the latest DST format, and Scheduler techniques.

#ifndef St_ehcorrelationMaker_def
#define St_ehcorrelationMaker_def

#include "StMaker.h"
#include "TString.h"
#include "StMuDSTMaker/COMMON/StMuTypes.hh"

class StMuDstMaker ;
//class StEmcCollection;
class StEmcPosition;
class StEmcGeom;
//class StSPtrVecEmcPoint;

class TFile        ;
class TH1F         ;
class TH2F         ;

#define MaxNumberOfTH1F     20

class St_ehcorrelationMaker : public StMaker
{
  
 private:

  StMuDstMaker*  mMuDstMaker ;                      //  Make MuDst pointer available to member functions
  StEmcPosition* mEmcPosition ;
  StEmcGeom*     mEmcGeom[4]; 
  //StEmcCollection* mEmcCol;

  // Define Histograms

  //TH1F*         histogram[MaxNumberOfTH1F] ;         1D Histograms
  //TH2F*         histogram_2D[MaxNumberOfTH1F] ;      2D Histograms

  TH1F* HVertex[2];
  TH1F* HpT[4];
  TH1F* Heop[2];
  TH1F* Htrig[2];
  TH1F* Hover;
  TH1F* Hseltrk;
  TH2F* Hinvmass[2];
  TH2F* Hinvmass_wocut[3];
  TH1F* Hopenphi[2];
  TH1F* Hopentheta[2];
  TH1F* HDCA[2];
  TH1F* Hopenangle[2];
  TH1F* HpT_pho[5];
  TH1F* Hele_Z;
  TH1F* Hpho_Z;
  TH2F* Hinvmass_pT_Opp;
  TH2F* Hinvmass_pT_Same;
  TH2F* Hinvmass_notreco[2];

  TH2F* HpT_dEdx[4];
  TH2F* HpT_dEdx_trig;
  TH2F* Hep_corr;
  TH2F* Hnhit_corr;
  TH2F* Heta_phi_corr;
  TH2F* Hmatch[2];
  TH2F* Heop_dEdx;
  TH2F* Hphi_corr[3][4];
  TH2F* Hphi_corr_we[3][8];
  TH2F* Hphi_corr_rc[3][5];
  TH2F* Hphi_corr_hadron[3];

  TH2F* Hopenphi_pT[2];
  TH2F* Hopentheta_pT[2];
  TH2F* HDCA_pT[2];
  TH2F* Hopenangle_pT[2];

  TH2F* H_dis_phi;
  TH2F* H_dis_eta;
  TH2F* H_dis_phi_TPC;
  TH2F* H_dis_eta_TPC;
  TH2F* H_dis_phi_TPC_org;
  TH2F* H_dis_eta_TPC_org;
  TH2F* H_phi_TPC_EMC;
  TH2F* H_eta_TPC_EMC;
  TH1F* H_TPC_EMC_match;

  TH2F* HdEdx_semi;
 
  TH2F* HpID[3];
  TH2F* HpID_check_pair;
  TH2F* HnSig[3];
 
  TH1F* HpT_pho_insemi[2];

 // check

  TH1F*  HdcaGlobal_check;
  TH1F*  HnHits_check;
  TH1F*  HnHitsdEdx_check;
  TH1F*  Hchi_check;
  TH1F*  Hflag_check;   
  TH1F*  HnfitOverMax_check;   
  TH1F*  Heta_check[3];

  TH1F*  HdcaGlobal_check_pair;
  TH1F*  HnHits_check_pair;
  TH1F*  HnHitsdEdx_check_pair;
  TH1F*  Hchi_check_pair;
  TH1F*  Hflag_check_pair;   
  TH1F*  Heta_check_pair;
  TH1F* HpT_check[4];
  TH2F* Hnsig_e[3];
  
  TH2F *Hcheck_pair;

  TH1F *Hpair[2];
  TH1F *Hetag_check;

  TH2F *HdEdx_had;

  TH1F* Hhad_trig;
  
  TH1F* Hass_pT;

  TH1F* hPointEta;
  TH1F* hPointPhi;
  TH1F* hPointZ;
  
  TH2F* Hphi_eta_opp[4]; 
  TH2F* Hphi_eta_same[4]; 
  TH2F* Hphi_eta_semi[3]; 
  TH2F* Hphi_eta_had; 
  
  TH2F* Hsame_pTcorr[2];
  TH2F* Hsame_delpT[2];
  TH2F* Hemc_phi_corr[2];
  TH2F* Hemc_eta_corr[2];
  TH2F* Hemc_eta_phi[3];
  TH2F* Hphi_corr_same[5];
  TH2F* Hphi_corr_semi[5];

  TH2F* Hphi_corr_opp_rmEMC;
  TH2F* Hphi_corr_same_rmEMC;
  TH2F* Hphi_corr_semi_rmEMC;

  TH2F* Hphi_corr_opp_rmEMCTPC;
  TH2F* Hphi_corr_same_rmEMCTPC;
  TH2F* Hphi_corr_semi_rmEMCTPC;

  TH2F* Hphi_corr_same_rmelectron;

  TH2F* H_EMCtower[4];
  TH2F* H_EMCmod[4];

  TH2F* HRad_opp[4];
  TH2F* HRad_same[6];
  TH2F* HRad_semi[4];
  TH2F* HRad_same_nSig[2];
  TH2F* HRad_semi_nSig[4];

  // end of define 

  TFile*        histogram_output ;                 //  Histograms outputfile pointer

  UInt_t        mEventsProcessed ;                 //  Number of Events read and processed
  TString       mHistogramOutputFileName ;         //  Name of the histogram output file 


 protected:


 public:

  St_ehcorrelationMaker(StMuDstMaker* maker) ;       //  Constructor
  virtual          ~St_ehcorrelationMaker( ) ;       //  Destructor

  Int_t Init    ( ) ;                              //  Initiliaze the analysis tools ... done once
  Int_t Make    ( ) ;                              //  The main analysis that is done on each event
  Int_t Finish  ( ) ;                              //  Finish the analysis, close files, and clean up.
  double Cal_Invmass(StPhysicalHelixD helix1,StPhysicalHelixD helix2, double bField);

  void SetOutputFileName(TString name) {mHistogramOutputFileName = name;} // Make name available to member functions
  
  ClassDef(St_ehcorrelationMaker,1)                  //  Macro for CINT compatability
    
};

#endif















