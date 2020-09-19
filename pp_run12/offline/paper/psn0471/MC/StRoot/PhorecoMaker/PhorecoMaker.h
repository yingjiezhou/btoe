// Based on the MuDST tools written by Frank Laue.
// Based on the DST Tutorial by Dan Magestro on the STAR Computing/Tutorials page.
// Updated 9/4/2006 by Jim Thomas to include the latest DST format, and Scheduler techniques.

#ifndef PhorecoMaker_def
#define PhorecoMaker_def

#include "StMaker.h"
#include "StMuDSTMaker/COMMON/StMuTypes.hh"
#include "StAssociationMaker/StAssociationMaker.h"
#include "StAssociationMaker/EMC/StEmcAssociationMaker.h"
#include "TString.h"

class StEvent;
//class StMuDstMaker ;
class StMcEvent;
//class StEmcCollection;
class StEmcCollection;
class StEmcTriggerMaker;
class StEmcGeom;
class StEmcDecoder;
class StEmcPosition;
//class StSPtrVecEmcPoint;

class StTrack;
class StGlobalTrack;
class StPrimaryTrack;
class StSPtrVecEmcPoint;
class StEmcPoint;

class TFile        ;
class TH1F         ;
class TH2F         ;

#define MaxNumberOfTH1F     20

class PhorecoMaker : public StMaker
{
 public:

  //PhorecoMaker(StMuDstMaker* maker) ;       //  Constructor
  PhorecoMaker(const Char_t *name="Phoreco") ;       //  Constructor
  //virtual          ~PhorecoMaker( ) ;       //  Destructor
   ~PhorecoMaker( ) ;       //  Destructor

  void Clear(Option_t *option="");// called after every event to cleanup 
  Int_t Init( );                              //  Initiliaze the analysis tools ... done once
  Int_t Make( );                              //  The main analysis that is done on each event
  Int_t Finish( );                              //  Finish the analysis, close files, and clean up.

  //void SetOutputFileName(TString name) {mHistogramOutputFileName = name;} // Make name available to member functions
  void SetOutFile(const char* filename);	//set output file for Ntuple
  Bool_t PhotonicID(StMcTrack* mcTrack);
  Bool_t DalitzID(StMcTrack* mcTrack);
  double photonweights(double pt);
  double Nonphotonicweights(double pt);
 
 private:

  StEvent       *event;		//!
  StMcEvent 	*mcEvent;	//!
  //StEmcGeom*     mEmcGeom[4]; 
  StEmcAssociationMaker *emcassoc;//!
  StEmcCollection *emccol;	//!
  StEmcGeom 	*mEmcGeom[4];	//!
  StEmcDecoder    *mDecoder;	//!
  StEmcPosition* mEmcPosition ;

  //StMuDstMaker*  mMuDstMaker ;                      //  Make MuDst pointer available to member functions
  //StEmcCollection* mEmcCol;

  // Define Histograms

  //TH1F*         histogram[MaxNumberOfTH1F] ;         1D Histograms
  //TH2F*         histogram_2D[MaxNumberOfTH1F] ;      2D Histograms

  TH1F* HVertex[2];
  TH1F* HpT[4];
  TH1F* Heop[2];
  TH1F* Htrig[2];
  TH1F* Hover;
  TH1F* Hseltrk_all;
  TH1F* Hseltrk_TPC;
  TH1F* Hseltrk_emc;
  TH1F* Hinvmass[2];
  TH1F* Hinvmass_wocut[3];
  TH1F* Hopenphi[2];
  TH1F* Hopentheta[2];
  TH1F* HDCA[2];
  TH1F* Hopenangle[2];
  TH1F* HpT_pho[5];
  TH1F* Hele_Z;
  TH2F* Hinvmass_pT_Opp[2];
  TH2F* Hinvmass_pT_Same[2];

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

  TH2F* HdEdx_semi;
 
  TH2F* H_EMC_phi_eta;
 
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
  TH1F* Hnsig_e;
  
  TH2F *Hcheck_pair;

  TH1F *Hpair[2];
  TH1F *Hetag_check;

  TH2F *HdEdx_had;

  TH1F* Hhad_trig;
  
  TH1F* Hass_pT;

  TH1F* hPointEta;
  TH1F* hPointPhi;
  TH1F* hPointZ;
  
  TH1F* Hphotonice_pho_mc;
  TH1F* Hphotonice_dal_mc;
  TH1F* Hphotonice_pho;
  TH1F* Hphotonice_dal;
  TH1F* Hphotonice_pho_w;
  TH1F* Hphotonice_dal_w;

  TH1F* Hphotonice_pho_reco[2];
  TH1F* Hphotonice_dal_reco[2];
  TH1F* Hphotonice_pho_reco_w[2];
  TH1F* Hphotonice_dal_reco_w[2];


  TH1F* Hphotonice_pho_w_EMC;
  TH1F* Hphotonice_pho_reco_w_EMC[2];
  TH1F* Hphotonice_pho_EMC;
  TH1F* Hphotonice_pho_reco_EMC[2];

  TH1F* Hnonphotonice[2];
  TH1F* Hnonphotonice_w[2];

  TH2F* Hmomcorr;
  TH2F* Hmom_reso;
  
  TH1D* Hmcasso_pho;  
  TH1D* Hmcasso_dal;  

  // end of define 

  TFile*        histogram_output ;                 //  Histograms outputfile pointer

  UInt_t        mEventsProcessed ;                 //  Number of Events read and processed
  //TString       mHistogramOutputFileName ;         //  Name of the histogram output file 
  TString       mFileName ;         //  Name of the histogram output file 


 protected:

 /*
 public:

  //PhorecoMaker(StMuDstMaker* maker) ;       //  Constructor
  PhorecoMaker(const Char_t *name="Phoreco") ;       //  Constructor
  virtual          ~PhorecoMaker( ) ;       //  Destructor

  Int_t Init( ) ;                              //  Initiliaze the analysis tools ... done once
  Int_t Make( ) ;                              //  The main analysis that is done on each event
  Int_t Finish( ) ;                              //  Finish the analysis, close files, and clean up.

  //void SetOutputFileName(TString name) {mHistogramOutputFileName = name;} // Make name available to member functions
  void SetOutFile(const char* filename);	//set output file for Ntuple
 
  */

  //ClassDef(PhorecoMaker,1)                  //  Macro for CINT compatability
  ClassDef(PhorecoMaker,0)                  //  Macro for CINT compatability
    
};

#endif















