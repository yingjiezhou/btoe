#ifndef StReadAna_h
#define  StMakeDataQa_h
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"

#include "TFile.h"
#include "StMaker.h"

class TString;
class TF1;
class TH1D;
class TH2D;
class TNtuple;
class  TH3F;
class  StPair;
class TGraphErrors;
class TGraph;
class StReadAna : public StMaker
{
 public:
  StReadAna(const char *outName);
  virtual ~StReadAna();
  
  void bookHistogram() ;
  void read(TString filename);
  void WriteHistogram();
  void Fill_gamma_electron_Mc(StPair *pair, int hft_flag);
  void Fill_pi0_electron_Mc(StPair *pair, int hft_flag);

  void Fill_gamma_electron_Rc(StPair *pair, int hft_flag);
  void Fill_pi0_electron_Rc(StPair *pair, int hft_flag);
  void Fill_eta_electron_Rc(StPair *pair, int hft_flag);
  
  // Double_t Weight(Float_t pt, Float_t ppt,Float_t gppt,Float_t geantId,Float_t pgeantId,Float_t gpgeantId); 
  Double_t Weight(Float_t pt, Float_t ppt,Float_t gppt,Float_t geantId,Float_t pgeantId,Float_t gpgeantId); 
  
 private:
  
  TFile * mOutputFile;
  TGraphErrors *gr_pi;

  TGraph *Graph_from_Gamma_pT;
  TGraph *Graph_from_EtaDalitz_pT;
  TGraph *Graph_from_Pi0Dalitz_pT;

  TGraph *Graph_from_Pi0_weight_0;
  TGraph *Graph_from_Eta_weight_0;
  TGraph *Graph_from_Gamma_0;

  TGraph *Graph_from_Pi_pT;
  TGraph *Graph_from_Electron_pT;

  TH1F *Gamma_pT;
  TH1F *EtaDalitz_pT;
  TH1F *Pi0Daliz_pT;
  TH1F *Pi_pT;
  TH1F *Electron_pT;





  TH2F *   mh2piDcaVspt_orig[3];
  TH2F *   mh2piDcaXYVspt_orig[3];
  TH2F *   mh2piDcaZVspt_orig[3];

  TH2F *   mh2piDcaVspt[3];
  TH2F *   mh2piDcaXYVspt[3];
  TH2F *   mh2piDcaZVspt[3];

  TH2F *   mh2pi_plusDcaVspt[3];
  TH2F *   mh2pi_plusDcaXYVspt[3];
  TH2F *   mh2pi_plusDcaZVspt[3];

  TH2F *   mh2pi_minusDcaVspt[3];
  TH2F *   mh2pi_minusDcaXYVspt[3];
  TH2F *   mh2pi_minusDcaZVspt[3];


  TH2F *   mh2piDcaVspt_embed[3];
  TH2F*    mh2piDcaZVspt_embed[3];
  TH2F *   mh2piDcaXYVspt_embed[3];


  TH2F *   mh2_pi0_electronDcaZVspt[3];
  TH2F *   mh2_pi0_electronDcaVspt[3];
  TH2F *   mh2_pi0_electronDcaXYVspt[3];

  //  TH3F *   mh3_pi0_electronDcaXYVspt[3];



  TH2F *   mh2_gamma_electronDcaZVspt[3];
  TH2F *   mh2_gamma_electronDcaVspt[3];
  TH2F *   mh2_gamma_electronDcaXYVspt[3];

  //  TH3F *   mh3_gamma_electronDcaXYVspt[3];

  TH2F *   mh2_eta_electronDcaZVspt[3];
  TH2F *   mh2_eta_electronDcaVspt[3];
  TH2F *   mh2_eta_electronDcaXYVspt[3];
  


 
  // mc track 

  TH2F * Mtp_pi0[3];
  TH2F * Stp_pi0[3];
  TH2F * Conversion_radius_pi0[3];

  TH2F * Rctp_pi0[3];
  TH2F * pairDca_pi0[3];
  TH2F * pairMass_pi0[3];
  TH2F * Conversion_Rc_radius_pi0[3];

  //
  TH2F * Mtp_gamma[3];
  TH2F * Conversion_radius_gamma[3];

  TH2F * Rctp_gamma[3];
  TH2F * pairDca_gamma[3];
  TH2F * pairMass_gamma[3];
  TH2F * Conversion_Rc_radius_gamma[3];

  // unlike like
  TH2F * Mtp_pi0_unlike[3];
  TH2F * Conversion_radius_pi0_unlike[3];

  TH2F * Rctp_pi0_unlike[3];
  TH2F * pairDca_pi0_unlike[3];
  TH2F * pairMass_pi0_unlike[3];
  TH2F * Conversion_Rc_radius_pi0_unlike[3];


  TH2F * Mtp_pi0_like[3];
  TH2F * Conversion_radius_pi0_like[3];

  TH2F * Rctp_pi0_like[3];
  TH2F * pairDca_pi0_like[3];
  TH2F * pairMass_pi0_like[3];

  TH2F * Conversion_Rc_radius_pi0_like[3]; 

  // gamma to e
  TH2F * Mtp_gamma_unlike[3];
  TH2F * Conversion_radius_gamma_unlike[3];

  TH2F * Rctp_gamma_unlike[3];
  TH2F * pairDca_gamma_unlike[3];
  TH2F * pairMass_gamma_unlike[3];
  TH2F * Conversion_Rc_radius_gamma_unlike[3];


  TH2F * Mtp_gamma_like[3];
  TH2F * Conversion_radius_gamma_like[3];

  TH2F * Rctp_gamma_like[3];
  TH2F * pairDca_gamma_like[3];
  TH2F * pairMass_gamma_like[3];
  TH2F * Conversion_Rc_radius_gamma_like[3];




  // dca pi0 
  TH2F * Dca_pi0_unlike[3];
  TH2F * Dca_pi0_like[3];

  TH2F * DcaXY_pi0_unlike[3];
  TH2F * DcaXY_pi0_like[3];

  TH2F * DcaZ_pi0_unlike[3];
  TH2F * DcaZ_pi0_like[3];

  TH2F * Dca_pi0[3];
  TH2F * DcaXY_pi0[3];
  TH2F * DcaZ_pi0[3];

  // TH3F * mh3DcaXY_pi0[3];
  // dca gamma

  TH2F * Dca_gamma_unlike[3];
  TH2F * Dca_gamma_like[3];

  TH2F * DcaXY_gamma_unlike[3];
  TH2F * DcaXY_gamma_like[3];

  TH2F * DcaZ_gamma_unlike[3];
  TH2F * DcaZ_gamma_like[3];

  TH2F * Dca_gamma[3];
  TH2F * DcaXY_gamma[3];
  TH2F * DcaZ_gamma[3];
  //  TH3F * mh3DcaXY_gamma[3];
  // dca eta

  TH2F * Dca_eta_unlike[3];
  TH2F * Dca_eta_like[3];

  TH2F * DcaXY_eta_unlike[3];
  TH2F * DcaXY_eta_like[3];

  TH2F * DcaZ_eta_unlike[3];
  TH2F * DcaZ_eta_like[3];

  TH2F * Dca_eta[3];
  TH2F * DcaXY_eta[3];
  TH2F * DcaZ_eta[3];


  //dca D0
  TH2F * DcaXY_D0[3];
  TH2F * DcaZ_D0[3];

  

  TH1F * Events_gamma[3];
  TH1F * Events_pi0[3];
  TH1F * Events_eta[3];

  TH1F * pT_spectra_gamma[3];
  TH1F * pT_spectra_pi0[3];
  TH1F * pT_spectra_eta[3];

  




 
  ClassDef(StReadAna,1)

};

#endif
