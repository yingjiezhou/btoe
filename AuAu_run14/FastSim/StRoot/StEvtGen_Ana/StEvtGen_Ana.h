#ifndef StEvtGen_Ana_h
#define  StEvtGen_Ana_h
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TF1.h"

#include "TGraph.h"

#include "StMaker.h"

class TString;
class TF1;
class TH1D;
class TH2D;
class TGraphErrors;
class  TH3F;


class StEvtGen_Ana : public StMaker
{
 public:
  StEvtGen_Ana(const char *outName);
  virtual ~StEvtGen_Ana();
  
  void bookHistogram() ;
  void read(TString filename);
  void WriteHistogram();
  Double_t Weight(Float_t pt,int); 

    private:

  TFile * mOutputFile;
  TH1D *Weight_pt_pi;  
  TH1D *Weight_pt_eta;  

  TGraph *gr_Weight_pt_pi;  
  TGraph *gr_Weight_pt_eta;  
  TGraphErrors *gr_pp_specatra;

  TF1 * D_pp200_data;  
  TGraph* B_pp200_fonll;
  TGraph* D_pp200_fonll;

  TGraph *Graph_from_F_levy_D0_0_80;
  TGraph *Graph_from_F_levy_Dpm_0_80;
  TGraph *Graph_from_F_levy_Ds_0_80;
  TGraph *Graph_from_F_levy_Lc_0_80;
  
  TH2F * mh2D0DcaVspt[3];
  TH2F * mh2DplusDcaVspt[3];
  TH2F * mh2B0DcaVspt[3];
  TH2F * mh2BplusDcaVspt[3];


  TH2F *  mh2D0rDcaVspt[3];
  TH2F *  mh2DplusrDcaVspt[3];
  TH2F *  mh2DsplusrDcaVspt[3];
  TH2F *  mh2LcrDcaVspt[3];

  TH2F *  mh2B0rDcaVspt[3];
  TH2F*  mh2BplusrDcaVspt[3];





  TH2F *mh2pi0DcaVspt[3];
  TH2F *mh2pi0rDcaVspt[3];
  TH2F *mh2etaDcaVspt[3];
  TH2F *mh2etarDcaVspt[3];



  TH2F *mh2McptVsEta;
  TH2F *mh2McptVsPhi;
  TH2F *mh2EtaVsPhi;
  TH1F *mh1NCounts;
  TH1F *mh1NCounts_after_weight;


  TH1F *mh1rpt_D_e;
  TH1F *mh1pt_D_e;


  TH1F *  mh2D0cTao;
  TH1F * mh2B0cTao;

  TH1F * mh2DpluscTao;
  TH1F * mh2BpluscTao;

  TH2F *mh2D0_electron_delta_CosPhi;
  TH2F *  mh2Dplus_electron_delta_CosPhi;
  TH2F * mh2B0_electron_delta_CosPhi;
  TH2F * mh2Bplus_electron_delta_CosPhi;


  TH1F *  mh2D0barcTao;
  TH1F *  mh2B0barcTao;
  TH1F *  mh2DminuscTao;
  TH1F *  mh2BminuscTao;

  TH1F *  mh2OcB0cTao;
  TH1F*  mh2OcB0barcTao;

  //input and outPut pT Eta Phi check
  TH2F *  mh2Lcplus_pT_Eta;
  TH2F *  mh2D0_pT_Eta;
  TH2F *  mh2Bplus_pT_Eta;


  


  
  /* TH1F * mh1pt; */
  /* TH1F*  mh1ptBde; */
  /* TH1F*  mh1ptBe; */

  /* TH1F * mh1Eta; */
  /* TH1F * mh1Phi; */
  /* TH1F * mh1Tao; */
  /* TH1F * mh1InvMass; */

  
  /* TH2F * mh2EtaVspt; */
  /* TH2F * mh2PhiVspt; */
  /* TH2F * mh2EtaVsPhi; */


  /* TH2F * mh2mEtaVspt; */
  /* TH2F * mh2mPhiVspt; */

  
  /* TH2F * mh2PathlenghVsParentP; */
  /* TH2F *  mh2TimeVsP; */
  /* TH2F *  mh2PathlenghVsTime; */
  
  /* TH2F *  mh2GammapVsParentp; */
  /* TH2F *  mh2GammaptVsParentpt; */
  /* TH2F * mh2GammaEnergyVsParentEnergy; */
 
  
  // mothter



  //  Float_t Pt_xx[9]={2.5,3.5,4.5,5.5,6.5,7.5,8.5,10.5,16.5};
 
  ClassDef(StEvtGen_Ana,1)

};

#endif
