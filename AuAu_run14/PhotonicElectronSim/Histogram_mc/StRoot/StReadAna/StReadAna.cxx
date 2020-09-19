#include <iostream>
#include "TFile.h"
#include "TNtuple.h"
#include "cmath"
#include "StReadAna.h"
#include "StMcElectronTrack.h"
#include "StPair.h"
#include "TLorentzVector.h"
#include "StThreeVectorF.hh"
#include "TGraphErrors.h"
using namespace std;

StReadAna::StReadAna(const char* outName)
{
  
  mOutputFile=new TFile(outName,"RECREATE");
  TFile *input=new TFile("/star/u/xiao00/Run14/Hijing_Simulation/Histogram_mc/StRoot/StReadAna/Weight.root","READ");
  TFile *input_Weight_gamma_pi0_eta=new TFile("StRoot/StReadAna/Weight_gamma_pi0_eta.root","READ");
  TH1D*   pi_pt=(TH1D *) input->Get("Pi"); 
  gr_pi=new TGraphErrors(pi_pt);
  // Graph_from_Gamma_pT=(TGraph *) input_Weight_gamma_pi0_eta->Get("Gamma_0_Weight_spectra");
  // Graph_from_Pi0Dalitz_pT=(TGraph *) input_Weight_gamma_pi0_eta->Get("Pi0_0_Weight_spectra");
  // Graph_from_EtaDalitz_pT=(TGraph *) input_Weight_gamma_pi0_eta->Get("Eta_0_Weight_spectra");

  Graph_from_Pi_pT=(TGraph *) input_Weight_gamma_pi0_eta->Get("Pi_0_Weight_spectra");
  //  Graph_from_Electron_pT=(TGraph *) input_Weight_gamma_pi0_eta->Get("Graph_from_Electron_pT");
  Graph_from_Gamma_0=(TGraph *) input_Weight_gamma_pi0_eta->Get("Gamma_0_Weight_spectra");
  Graph_from_Pi0_weight_0=(TGraph *) input_Weight_gamma_pi0_eta->Get("Pi0_0_Weight_spectra");
  Graph_from_Eta_weight_0=(TGraph *) input_Weight_gamma_pi0_eta->Get("Eta_0_Weight_spectra");


}
StReadAna::~StReadAna()
{
  //..
  //
}
void StReadAna::bookHistogram()
{ 
    // const  int  nDcasDca = 140;
    // Double_t const DcaEdgeDca[nDcasDca + 1] =
    //   {  -1 , -0.97 , -0.94 , -0.91 , -0.88 , -0.85 , -0.82 , -0.79 , -0.76 , -0.73 , -0.7 , -0.67 , -0.64 , -0.61 , -0.58 , -0.55 , -0.52 , -0.49 , -0.46 , -0.43 , -0.4 , -0.37 , -0.34 , -0.31 , -0.28 , -0.25 , -0.22 ,
    // 	 -0.19 , -0.16 , -0.13 , -0.1 , -0.0975 , -0.095 , -0.0925 , -0.09 , -0.0875 , -0.085 , -0.0825 , -0.08 , -0.0775 , -0.075 , -0.0725 , -0.07 , -0.0675 , -0.065 , -0.0625 , -0.06 , -0.0575 , -0.055 , -0.0525 , -0.05 , 
    // 	 -0.0475 , -0.045 , -0.0425 , -0.04 , -0.0375 , -0.035 , -0.0325 , -0.03 , -0.0275 , -0.025 , -0.0225 , -0.02 , -0.0175 , -0.015 , -0.0125 , -0.01 , -0.0075 , -0.005 , -0.0025 , 0 , 0.0025 , 0.005 , 0.0075 , 0.01 , 0.0125 ,
    // 	 0.015 , 0.0175 , 0.02 , 0.0225 , 0.025 , 0.0275 , 0.03 , 0.0325 , 0.035 , 0.0375 , 0.04 , 0.0425 , 0.045 , 0.0475 , 0.05 , 0.0525 , 0.055 , 0.0575 , 0.06 , 0.0625 , 0.065 , 0.0675 , 0.07 , 0.0725 , 0.075 , 0.0775 , 0.08 , 
    // 	 0.0825 , 0.085 , 0.0875 , 0.09 , 0.0925 , 0.095 , 0.0975 , 0.1 ,0.13 , 0.16 , 0.19 , 0.22 , 0.25 , 0.28 , 0.31 , 0.34 , 0.37 , 0.4 , 0.43 , 0.46 , 0.49 , 0.52 , 0.55 , 0.58 , 0.61 , 0.64 , 0.67 , 0.7 , 0.73 , 0.76 , 0.79 , 0.82 , 0.85 , 0.88 , 0.91 , 0.94 , 0.97 , 1  };

  const int  nDcasDca = 54;
  Double_t const  DcaEdgeDca[nDcasDca+1] = {-0.1   , -0.09 ,     -0.08  ,   -0.07    , -0.06    , -0.05 , -0.0475 , -0.045 , -0.0425 , -0.04 , -0.0375 , -0.035 , -0.0325 , -0.03 , -0.0275 , -0.025 , -0.0225 , -0.02,-0.018,-0.016,-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014,0.016,0.018,0.02 ,0.0225 , 0.025 , 0.0275 , 0.03 , 0.0325 , 0.035 , 0.0375 , 0.04 , 0.0425 , 0.045 , 0.0475 , 0.05    , 0.06  ,  0.07    , 0.08    , 0.09   ,0.1};



    cout<< " Number of dca bin " <<sizeof(DcaEdgeDca)/sizeof( DcaEdgeDca[1])<<endl;

    for(int i=0;i<nDcasDca+1;i++)
      {
	cout<< " Dca binning "<< i<< " "<< DcaEdgeDca[i+1]-DcaEdgeDca[i]<<endl;
      }

   Gamma_pT=new TH1F("Gamma_pT","",1000,0,20);
   EtaDalitz_pT=new TH1F("EtaDalitz_pT","",1000,0,20);
   Pi0Daliz_pT=new TH1F("Pi0Dalitz_pT","",1000,0,20);
   Pi_pT=new TH1F("Pi_pT","",1000,0,20);
   Electron_pT=new TH1F("Electron_pT","",1000,0,20);


  for(Int_t ihist=0;ihist<3;ihist++){
    
    // mh3mcHFTVsptVsEta_pi[ihist]=new TH3F(Form("mh3mcHFTVsptVsEta_pi%i",ihist),"",400,0,20,100,-1,1,50,0,50);
    // mh3mcHFTVsptVsEta_pi0_e[ihist]=new TH3F(Form("mh3mcHFTVsptVsEta_pi0_e%i",ihist),"",400,0,20,100,-1,1,50,0,50);
    // mh3mcHFTVsptVsEta_gamma_e[ihist]=new TH3F(Form("mh3mcHFTVsptVsEta_gamma_e%i",ihist),"",400,0,20,100,-1,1,50,0,50);
    
    
    // mh2piDcaVspt_orig[ihist]=new TH2F(Form("mh2piDcaVspt_orig%i",ihist),"",400,0,20,nDcasDca,DcaEdgeDca);
    // mh2piDcaZVspt_orig[ihist]=new TH2F(Form("mh2piDcaZVspt_orig%i",ihist),"",400,0,20,nDcasDca,DcaEdgeDca);
    // mh2piDcaXYVspt_orig[ihist]=new TH2F(Form("mh2piDcaXYVspt_orig%i",ihist),"",400,0,20,nDcasDca,DcaEdgeDca);

    mh2piDcaVspt_orig[ihist]=new TH2F(Form("mh2piDcaVspt_orig%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2piDcaZVspt_orig[ihist]=new TH2F(Form("mh2piDcaZVspt_orig%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2piDcaXYVspt_orig[ihist]=new TH2F(Form("mh2piDcaXYVspt_orig%i",ihist),"",400,0,20,400,-0.1,0.1);




    mh2piDcaVspt_embed[ihist]=new TH2F(Form("mh2piDcaVspt_embed%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2piDcaZVspt_embed[ihist]=new TH2F(Form("mh2piDcaZVspt_embed%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2piDcaXYVspt_embed[ihist]=new TH2F(Form("mh2piDcaXYVspt_embed%i",ihist),"",400,0,20,400,-0.1,0.1);



    mh2piDcaVspt[ihist]=new TH2F(Form("mh2piDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2piDcaZVspt[ihist]=new TH2F(Form("mh2piDcaZVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2piDcaXYVspt[ihist]=new TH2F(Form("mh2piDcaXYVspt%i",ihist),"",400,0,20,400,-0.1,0.1);

    mh2pi_plusDcaVspt[ihist]=new TH2F(Form("mh2pi_plusDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2pi_plusDcaZVspt[ihist]=new TH2F(Form("mh2pi_plusDcaZVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2pi_plusDcaXYVspt[ihist]=new TH2F(Form("mh2pi_plusDcaXYVspt%i",ihist),"",400,0,20,400,-0.1,0.1);

    mh2pi_minusDcaVspt[ihist]=new TH2F(Form("mh2pi_minusDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2pi_minusDcaZVspt[ihist]=new TH2F(Form("mh2pi_minusDcaZVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2pi_minusDcaXYVspt[ihist]=new TH2F(Form("mh2pi_minusDcaXYVspt%i",ihist),"",400,0,20,400,-0.1,0.1);



    mh2_pi0_electronDcaZVspt[ihist]=new TH2F(Form("mh2_pi0_electronDcaZVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2_pi0_electronDcaXYVspt[ihist]=new TH2F(Form("mh2_pi0_electronDcaXYVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2_pi0_electronDcaVspt[ihist]=new TH2F(Form("mh2_pi0_electronDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    //   mh3_pi0_electronDcaXYVspt[ihist]=new TH3F(Form("mh3_pi0_electronDcaXYVspt%i",ihist),"",200,0,10,80,-0.1,0.1,10,-3.14,3.14);

    mh2_gamma_electronDcaZVspt[ihist]=new TH2F(Form("mh2_gamma_electronDcaZVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2_gamma_electronDcaXYVspt[ihist]=new TH2F(Form("mh2_gamma_electronDcaXYVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2_gamma_electronDcaVspt[ihist]=new TH2F(Form("mh2_gamma_electronDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    //   mh3_gamma_electronDcaXYVspt[ihist]=new TH3F(Form("mh3_gamma_electronDcaXYVspt%i",ihist),"",200,0,10,80,-0.1,0.1,10,-3.14,3.14);

    mh2_eta_electronDcaZVspt[ihist]=new TH2F(Form("mh2_eta_electronDcaZVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2_eta_electronDcaXYVspt[ihist]=new TH2F(Form("mh2_eta_electronDcaXYVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2_eta_electronDcaVspt[ihist]=new TH2F(Form("mh2_eta_electronDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);


    Events_gamma[ihist]=new TH1F(Form("Events_gamma%i",ihist),"",10000,1000,100);
    Events_pi0[ihist]=new TH1F(Form("Events_pi0%i",ihist),"",10000,1000,100);
    Events_eta[ihist]=new TH1F(Form("Events_eta%i",ihist),"",10000,1000,100);
    
    pT_spectra_gamma[ihist]=new TH1F(Form("pT_spectra_gamma%i",ihist),"",400,0,20);
    pT_spectra_pi0[ihist]=new TH1F(Form("pT_spectra_pi0%i",ihist),"",400,0,20);
    pT_spectra_eta[ihist]=new TH1F(Form("pT_spectra_eta%i",ihist),"",400,0,20);
      

    // 
    
    Mtp_pi0[ihist]=new TH2F (Form("Mtp_pi0%i",ihist),"",800,-60,60,800,-60,60);
    Rctp_pi0[ihist]=new TH2F (Form("Rctp_pi0%i",ihist),"",800,-60,60,800,-60,60);
    Conversion_radius_pi0[ihist]=new TH2F(Form("Conversion_radius_pi0%i",ihist),"",400,0,20,400,0,20);

    pairDca_pi0[ihist]=new TH2F(Form("pairDca_pi0%i",ihist),"",400,0,20,500,0,1);
    pairMass_pi0[ihist]=new TH2F(Form("pairMass_pi0%i",ihist),"",400,0,20,100,0,0.2);
    Conversion_Rc_radius_pi0[ihist]=new TH2F(Form("Conversion_Rc_radius_pi0%i",ihist),"",400,0,20,400,0,20);

    Mtp_gamma[ihist]=new TH2F (Form("Mtp_gamma%i",ihist),"",800,-60,60,800,-60,60);
    Rctp_gamma[ihist]=new TH2F (Form("Rctp_gamma%i",ihist),"",800,-60,60,800,-60,60);
    Conversion_radius_gamma[ihist]=new TH2F(Form("Conversion_radius_gamma%i",ihist),"",400,0,20,400,0,20);

    pairDca_gamma[ihist]=new TH2F(Form("pairDca_gamma%i",ihist),"",400,0,20,500,0,1);
    pairMass_gamma[ihist]=new TH2F(Form("pairMass_gamma%i",ihist),"",400,0,20,100,0,0.2);
    Conversion_Rc_radius_gamma[ihist]=new TH2F(Form("Conversion_Rc_radius_gamma%i",ihist),"",400,0,20,400,0,20);

    //unlike like
    Mtp_pi0_unlike[ihist]=new TH2F (Form("Mtp_pi0_unlike%i",ihist),"",800,-60,60,800,-60,60);
    Rctp_pi0_unlike[ihist]=new TH2F (Form("Rctp_pi0_unlike%i",ihist),"",800,-60,60,800,-60,60);
    Conversion_radius_pi0_unlike[ihist]=new TH2F(Form("Conversion_radius_pi0_unlike%i",ihist),"",400,0,20,400,0,20);

    pairDca_pi0_unlike[ihist]=new TH2F(Form("pairDca_pi0_unlike%i",ihist),"",400,0,20,500,0,1);
    pairMass_pi0_unlike[ihist]=new TH2F(Form("pairMass_pi0_unlike%i",ihist),"",400,0,20,100,0,0.2);
    Conversion_Rc_radius_pi0_unlike[ihist]=new TH2F(Form("Conversion_Rc_radius_pi0_unlike%i",ihist),"",400,0,20,400,0,20);

    Mtp_pi0_like[ihist]=new TH2F (Form("Mtp_pi0_like%i",ihist),"",800,-60,60,800,-60,60);
    Rctp_pi0_like[ihist]=new TH2F (Form("Rctp_pi0_like%i",ihist),"",800,-60,60,800,-60,60);
    Conversion_radius_pi0_like[ihist]=new TH2F(Form("Conversion_radius_pi0_like%i",ihist),"",400,0,20,400,0,20);

    pairDca_pi0_like[ihist]=new TH2F(Form("pairDca_pi0_like%i",ihist),"",400,0,20,500,0,1);
    pairMass_pi0_like[ihist]=new TH2F(Form("pairMass_pi0_like%i",ihist),"",400,0,20,100,0,0.2);
    Conversion_Rc_radius_pi0_like[ihist]=new TH2F(Form("Conversion_Rc_radius_pi0_like%i",ihist),"",400,0,20,400,0,20);
    Dca_pi0_unlike[ihist]=new TH2F(Form("Dca_pi0_unlike%i",ihist),"",400,0,20,400,-0.1,0.1);
    Dca_pi0_like[ihist]=new TH2F(Form("Dca_pi0_like%i",ihist),"",400,0,20,400,-0.1,0.1);

    DcaXY_pi0_unlike[ihist]=new TH2F(Form("DcaXY_pi0_unlike%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaXY_pi0_like[ihist]=new TH2F(Form("DcaXY_pi0_like%i",ihist),"",400,0,20,400,-0.1,0.1);

    DcaZ_pi0_unlike[ihist]=new TH2F(Form("DcaZ_pi0_unlike%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaZ_pi0_like[ihist]=new TH2F(Form("DcaZ_pi0_like%i",ihist),"",400,0,20,400,-0.1,0.1);

    Dca_pi0[ihist]=new TH2F(Form("Dca_pi0%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaXY_pi0[ihist]=new TH2F(Form("DcaXY_pi0%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaZ_pi0[ihist]=new TH2F(Form("DcaZ_pi0%i",ihist),"",400,0,20,400,-0.1,0.1);
    //   mh3DcaXY_pi0[ihist]=new TH3F(Form("mh3DcaXY_pi0%i",ihist),"",200,0,10,80,-0.1,0.1,10,-3.14,3.14);
    //gamma
    Mtp_gamma_unlike[ihist]=new TH2F (Form("Mtp_gamma_unlike%i",ihist),"",800,-60,60,800,-60,60);
    Rctp_gamma_unlike[ihist]=new TH2F (Form("Rctp_gamma_unlike%i",ihist),"",800,-60,60,800,-60,60);
    Conversion_radius_gamma_unlike[ihist]=new TH2F(Form("Conversion_radius_gamma_unlike%i",ihist),"",400,0,20,400,0,20);

    pairDca_gamma_unlike[ihist]=new TH2F(Form("pairDca_gamma_unlike%i",ihist),"",400,0,20,500,0,1);
    pairMass_gamma_unlike[ihist]=new TH2F(Form("pairMass_gamma_unlike%i",ihist),"",400,0,20,100,0,0.2);
    Conversion_Rc_radius_gamma_unlike[ihist]=new TH2F(Form("Conversion_Rc_radius_gamma_unlike%i",ihist),"",400,0,20,400,0,20);

    Mtp_gamma_like[ihist]=new TH2F (Form("Mtp_gamma_like%i",ihist),"",800,-60,60,800,-60,60);
    Rctp_gamma_like[ihist]=new TH2F (Form("Rctp_gamma_like%i",ihist),"",800,-60,60,800,-60,60);
    Conversion_radius_gamma_like[ihist]=new TH2F(Form("Conversion_radius_gamma_like%i",ihist),"",400,0,20,400,0,20);

    pairDca_gamma_like[ihist]=new TH2F(Form("pairDca_gamma_like%i",ihist),"",400,0,20,500,0,1);
    pairMass_gamma_like[ihist]=new TH2F(Form("pairMass_gamma_like%i",ihist),"",400,0,20,100,0,0.2);
    Conversion_Rc_radius_gamma_like[ihist]=new TH2F(Form("Conversion_Rc_radius_gamma_like%i",ihist),"",400,0,20,400,0,20);

    Dca_gamma_unlike[ihist]=new TH2F(Form("Dca_gamma_unlike%i",ihist),"",400,0,20,400,-0.1,0.1);
    Dca_gamma_like[ihist]=new TH2F(Form("Dca_gamma_like%i",ihist),"",400,0,20,400,-0.1,0.1);

    DcaXY_gamma_unlike[ihist]=new TH2F(Form("DcaXY_gamma_unlike%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaXY_gamma_like[ihist]=new TH2F(Form("DcaXY_gamma_like%i",ihist),"",400,0,20,400,-0.1,0.1);

    DcaZ_gamma_unlike[ihist]=new TH2F(Form("DcaZ_gamma_unlike%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaZ_gamma_like[ihist]=new TH2F(Form("DcaZ_gamma_like%i",ihist),"",400,0,20,400,-0.1,0.1);


    Dca_gamma[ihist]=new TH2F(Form("Dca_gamma%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaXY_gamma[ihist]=new TH2F(Form("DcaXY_gamma%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaZ_gamma[ihist]=new TH2F(Form("DcaZ_gamma%i",ihist),"",400,0,20,400,-0.1,0.1);
    //   mh3DcaXY_gamma[ihist]=new TH3F(Form("mh3DcaXY_gamma%i",ihist),"",200,0,10,80,-0.1,0.1,10,-3.14,3.14);
    // eta
    Dca_eta_unlike[ihist]=new TH2F(Form("Dca_eta_unlike%i",ihist),"",400,0,20,400,-0.1,0.1);
    Dca_eta_like[ihist]=new TH2F(Form("Dca_eta_like%i",ihist),"",400,0,20,400,-0.1,0.1);

    DcaXY_eta_unlike[ihist]=new TH2F(Form("DcaXY_eta_unlike%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaXY_eta_like[ihist]=new TH2F(Form("DcaXY_eta_like%i",ihist),"",400,0,20,400,-0.1,0.1);

    DcaZ_eta_unlike[ihist]=new TH2F(Form("DcaZ_eta_unlike%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaZ_eta_like[ihist]=new TH2F(Form("DcaZ_eta_like%i",ihist),"",400,0,20,400,-0.1,0.1);


    Dca_eta[ihist]=new TH2F(Form("Dca_eta%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaXY_eta[ihist]=new TH2F(Form("DcaXY_eta%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaZ_eta[ihist]=new TH2F(Form("DcaZ_eta%i",ihist),"",400,0,20,400,-0.1,0.1);

    DcaXY_D0[ihist]=new TH2F(Form("DcaXY_D0%i",ihist),"",400,0,20,400,-0.1,0.1);
    DcaZ_D0[ihist]=new TH2F(Form("DcaZ_D0%i",ihist),"",400,0,20,400,-0.1,0.1);
    



 

  //
    // mh3mcHFTVsptVsEta_pi[ihist]->Sumw2();
    // mh3mcHFTVsptVsEta_pi0_e[ihist]->Sumw2();
    // mh3mcHFTVsptVsEta_gamma_e[ihist]->Sumw2();

     Events_gamma[ihist]->Sumw2();
    Events_pi0[ihist]->Sumw2();
    Events_eta[ihist]->Sumw2();
    
    pT_spectra_gamma[ihist]->Sumw2();
    pT_spectra_pi0[ihist]->Sumw2();
    pT_spectra_eta[ihist]->Sumw2();


    mh2piDcaVspt[ihist]->Sumw2();
    mh2piDcaZVspt[ihist]->Sumw2();
    mh2piDcaXYVspt[ihist]->Sumw2();

    mh2pi_plusDcaVspt[ihist]->Sumw2();
    mh2pi_plusDcaZVspt[ihist]->Sumw2();
    mh2pi_plusDcaXYVspt[ihist]->Sumw2();

    mh2pi_minusDcaVspt[ihist]->Sumw2();
    mh2pi_minusDcaZVspt[ihist]->Sumw2();
    mh2pi_minusDcaXYVspt[ihist]->Sumw2();

    mh2piDcaVspt_orig[ihist]->Sumw2();
    mh2piDcaZVspt_orig[ihist]->Sumw2();
    mh2piDcaXYVspt_orig[ihist]->Sumw2();

    mh2piDcaVspt_embed[ihist]->Sumw2();
    mh2piDcaZVspt_embed[ihist]->Sumw2();
    mh2piDcaXYVspt_embed[ihist]->Sumw2();
    
    mh2_pi0_electronDcaZVspt[ihist]->Sumw2();
    mh2_pi0_electronDcaXYVspt[ihist]->Sumw2();
    mh2_pi0_electronDcaVspt[ihist]->Sumw2();

    //   mh3_pi0_electronDcaXYVspt[ihist]->Sumw2();

    mh2_gamma_electronDcaZVspt[ihist]->Sumw2();
    mh2_gamma_electronDcaXYVspt[ihist]->Sumw2();
    mh2_gamma_electronDcaVspt[ihist]->Sumw2();

    //   mh3_gamma_electronDcaXYVspt[ihist]->Sumw2();

    mh2_eta_electronDcaZVspt[ihist]->Sumw2();
    mh2_eta_electronDcaXYVspt[ihist]->Sumw2();
    mh2_eta_electronDcaVspt[ihist]->Sumw2();


    Mtp_pi0[ihist]->Sumw2();
    Rctp_pi0[ihist]->Sumw2(); 
    pairDca_pi0[ihist]->Sumw2(); 
    pairMass_pi0[ihist]->Sumw2(); 
    Conversion_radius_pi0[ihist]->Sumw2();
    Conversion_Rc_radius_pi0[ihist]->Sumw2();

    Mtp_gamma[ihist]->Sumw2();
    Rctp_gamma[ihist]->Sumw2(); 
    pairDca_gamma[ihist]->Sumw2(); 
    pairMass_gamma[ihist]->Sumw2(); 
    Conversion_radius_gamma[ihist]->Sumw2();
    Conversion_Rc_radius_gamma[ihist]->Sumw2();
    //
    //unlike like
    Mtp_pi0_unlike[ihist]->Sumw2();
    Rctp_pi0_unlike[ihist]->Sumw2();
    Conversion_radius_pi0_unlike[ihist]->Sumw2();

    pairDca_pi0_unlike[ihist]->Sumw2();
    pairMass_pi0_unlike[ihist]->Sumw2();
    Conversion_Rc_radius_pi0_unlike[ihist]->Sumw2();

    Mtp_pi0_like[ihist]->Sumw2();
    Rctp_pi0_like[ihist]->Sumw2();
    Conversion_radius_pi0_like[ihist]->Sumw2();

    pairDca_pi0_like[ihist]->Sumw2();
    pairMass_pi0_like[ihist]->Sumw2();
    Conversion_Rc_radius_pi0_like[ihist]->Sumw2();
    Dca_pi0_unlike[ihist]->Sumw2();
    Dca_pi0_like[ihist]->Sumw2();

    DcaXY_pi0_unlike[ihist]->Sumw2();
    DcaXY_pi0_like[ihist]->Sumw2();

    DcaZ_pi0_unlike[ihist]->Sumw2();
    DcaZ_pi0_like[ihist]->Sumw2();

    Dca_pi0[ihist]->Sumw2();
    DcaXY_pi0[ihist]->Sumw2();
    DcaZ_pi0[ihist]->Sumw2();
    //   mh3DcaXY_pi0[ihist]->Sumw2();

    //gamma
    Mtp_gamma_unlike[ihist]->Sumw2();
    Rctp_gamma_unlike[ihist]->Sumw2();
    Conversion_radius_gamma_unlike[ihist]->Sumw2();

    pairDca_gamma_unlike[ihist]->Sumw2();
    pairMass_gamma_unlike[ihist]->Sumw2();
    Conversion_Rc_radius_gamma_unlike[ihist]->Sumw2();

    Mtp_gamma_like[ihist]->Sumw2();
    Rctp_gamma_like[ihist]->Sumw2();
    Conversion_radius_gamma_like[ihist]->Sumw2();

    pairDca_gamma_like[ihist]->Sumw2();
    pairMass_gamma_like[ihist]->Sumw2();
    Conversion_Rc_radius_gamma_like[ihist]->Sumw2();

    Dca_gamma_unlike[ihist]->Sumw2();
    Dca_gamma_like[ihist]->Sumw2();

    DcaXY_gamma_unlike[ihist]->Sumw2();
    DcaXY_gamma_like[ihist]->Sumw2();

    DcaZ_gamma_unlike[ihist]->Sumw2();
    DcaZ_gamma_like[ihist]->Sumw2();
    
    Dca_gamma[ihist]->Sumw2();
    DcaXY_gamma[ihist]->Sumw2();
    DcaZ_gamma[ihist]->Sumw2();
    //   mh3DcaXY_gamma[ihist]->Sumw2();

    Dca_eta_unlike[ihist]->Sumw2();
    Dca_eta_like[ihist]->Sumw2();

    DcaXY_eta_unlike[ihist]->Sumw2();
    DcaXY_eta_like[ihist]->Sumw2();

    DcaZ_eta_unlike[ihist]->Sumw2();
    DcaZ_eta_like[ihist]->Sumw2();
    
    Dca_eta[ihist]->Sumw2();
    DcaXY_eta[ihist]->Sumw2();
    DcaZ_eta[ihist]->Sumw2();
    DcaXY_D0[ihist]->Sumw2();
    DcaZ_D0[ihist]->Sumw2();
  }
   Gamma_pT->Sumw2();
   EtaDalitz_pT->Sumw2();
   Pi0Daliz_pT->Sumw2();
   Pi_pT->Sumw2();
   Electron_pT->Sumw2();

}
void StReadAna::read(TString fileName)
{
  cout<<"!!!!!!!!!!!!!!!!!read"<<fileName<<endl;
  
  TFile * infile=new TFile(fileName.Data());
  TNtuple* Tree=(TNtuple*) infile->Get("nt_sngl");
  StMcElectronTrack * McTrack=new StMcElectronTrack();
  McTrack->Init(Tree);
  for(Int_t iEvent=0;iEvent<Tree->GetEntries();iEvent++)//
    {
      if(iEvent%1000==0)
	cout<<"working on Event  "<<iEvent<<endl;
      McTrack->GetEntry(iEvent);
      
      if(McTrack->geantId==1)
	Gamma_pT->Fill(McTrack->pt);
      if(McTrack->geantId==147)
	EtaDalitz_pT->Fill(McTrack->pt);
      if(McTrack->geantId==149)
	Pi0Daliz_pT->Fill(McTrack->pt);

      if(McTrack->geantId==10008||McTrack->geantId==10009||McTrack->geantId==8||McTrack->geantId==9)
	Pi_pT->Fill(McTrack->pt);
      if(McTrack->geantId==2||McTrack->geantId==3)
	Electron_pT->Fill(McTrack->pt);

      if(fabs(McTrack->reta)>=0.7) continue;
      if(McTrack->rpt<0.2) continue;

      if(McTrack->nfit>=20&&McTrack->nfit/McTrack->nmax>0.52&&McTrack->ncom>15&&fabs(McTrack->dca)<1.5) 
      
	{	
	  // single electron from gamma
	  if(fabs((McTrack->pt-McTrack->rpt))/McTrack->pt>=1) continue;



    // Events_gamma[ihist]->Write();
    // Events_pi0[ihist]->Write();
    // Events_eta[ihist]->Write();
    
    // pT_spectra_gamma[ihist]->Write();
    // pT_spectra_pi0[ihist]->Write();
    // pT_spectra_eta[ihist]->Write();
     

	  if((McTrack->geantId==2||McTrack->geantId==3)&&McTrack->pgeantId==1)
	    {
	      Double_t weight_pi0=Weight(McTrack->pt,McTrack->ppt,McTrack->gppt,McTrack->geantId,McTrack->pgeantId,McTrack->gpgeantId); 
	      {
		mh2_gamma_electronDcaVspt[0]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		mh2_gamma_electronDcaZVspt[0]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		mh2_gamma_electronDcaXYVspt[0]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		//	mh3_gamma_electronDcaXYVspt[0]->Fill(McTrack->rpt,McTrack->dcaxy,McTrack->phi,weight_pi0);
		pT_spectra_gamma[0]->Fill(McTrack->rpt,weight_pi0);
	      }

	      if(McTrack->isHFT==1)
		{
		  mh2_gamma_electronDcaVspt[1]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2_gamma_electronDcaZVspt[1]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2_gamma_electronDcaXYVspt[1]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		  //	  mh3_gamma_electronDcaXYVspt[1]->Fill(McTrack->rpt,McTrack->dcaxy,McTrack->phi,weight_pi0);
		  pT_spectra_gamma[1]->Fill(McTrack->rpt,weight_pi0);
		}
	      
	      if(McTrack->isHFT==1&&McTrack->trueHFT==1)
		{
		  mh2_gamma_electronDcaVspt[2]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2_gamma_electronDcaZVspt[2]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2_gamma_electronDcaXYVspt[2]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		  pT_spectra_gamma[2]->Fill(McTrack->rpt,weight_pi0);
		}

	    }

	  // single electron from pi0
	  if((McTrack->geantId==2||McTrack->geantId==3)&&McTrack->pgeantId==149)
	    {
	      Double_t weight_pi0=Weight(McTrack->pt,McTrack->ppt,McTrack->gppt,McTrack->geantId,McTrack->pgeantId,McTrack->gpgeantId); 

	      // if(McTrack->geantId==2) cout<< " electron "<< weight_pi0<<endl;
	      // if(McTrack->geantId==3) cout<< " positron "<< weight_pi0<<endl;
	      
		{
		  mh2_pi0_electronDcaVspt[0]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2_pi0_electronDcaZVspt[0]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2_pi0_electronDcaXYVspt[0]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		  pT_spectra_pi0[0]->Fill(McTrack->rpt,weight_pi0);
		}
	      
	      if(McTrack->isHFT==1)
		{
		  mh2_pi0_electronDcaVspt[1]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2_pi0_electronDcaZVspt[1]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2_pi0_electronDcaXYVspt[1]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		  //	  mh3_pi0_electronDcaXYVspt[1]->Fill(McTrack->rpt,McTrack->dcaxy,McTrack->phi,weight_pi0);
		  pT_spectra_pi0[1]->Fill(McTrack->rpt,weight_pi0);
		}
	      
	      if(McTrack->isHFT==1&&McTrack->trueHFT==1)
		{
		  mh2_pi0_electronDcaVspt[2]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2_pi0_electronDcaZVspt[2]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2_pi0_electronDcaXYVspt[2]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		  pT_spectra_pi0[2]->Fill(McTrack->rpt,weight_pi0);
		}
	    }

	  // single electron from eta
	  if((McTrack->geantId==2||McTrack->geantId==3)&&McTrack->pgeantId==147)
	    {
	      Double_t weight_pi0=Weight(McTrack->pt,McTrack->ppt,McTrack->gppt,McTrack->geantId,McTrack->pgeantId,McTrack->gpgeantId); 

		{
		  mh2_eta_electronDcaVspt[0]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2_eta_electronDcaZVspt[0]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2_eta_electronDcaXYVspt[0]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		  pT_spectra_eta[0]->Fill(McTrack->rpt,weight_pi0);
		}
	      
	      if(McTrack->isHFT==1)
		{
		  mh2_eta_electronDcaVspt[1]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2_eta_electronDcaZVspt[1]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2_eta_electronDcaXYVspt[1]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		  pT_spectra_eta[1]->Fill(McTrack->rpt,weight_pi0);
		}
	      
	      if(McTrack->isHFT==1&&McTrack->trueHFT==1)
		{
		  mh2_eta_electronDcaVspt[2]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2_eta_electronDcaZVspt[2]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2_eta_electronDcaXYVspt[2]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		  pT_spectra_eta[2]->Fill(McTrack->rpt,weight_pi0);
		}
	    }

	  // single pi


	  if(McTrack->geantId==8||McTrack->geantId==9||McTrack->geantId==10008||McTrack->geantId==10009)
	    {
	      Double_t weight_pi0=Weight(McTrack->pt,McTrack->ppt,McTrack->gppt,McTrack->geantId,McTrack->pgeantId,McTrack->gpgeantId); 

		{


    		  mh2piDcaVspt[0]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2piDcaZVspt[0]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2piDcaXYVspt[0]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);

		  if(McTrack->geantId==8||McTrack->geantId==10008)
		    {
		      mh2pi_plusDcaVspt[0]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		      mh2pi_plusDcaZVspt[0]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		      mh2pi_plusDcaXYVspt[0]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		    }
		  if(McTrack->geantId==9||McTrack->geantId==10009)
		    {
		      mh2pi_minusDcaVspt[0]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		      mh2pi_minusDcaZVspt[0]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		      mh2pi_minusDcaXYVspt[0]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		    }

		  if(McTrack->geantId==8||McTrack->geantId==9)
		    {
		      mh2piDcaVspt_orig[0]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		      mh2piDcaZVspt_orig[0]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		      mh2piDcaXYVspt_orig[0]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		    }
		  if(McTrack->geantId==10008||McTrack->geantId==10009)
		    {
		      mh2piDcaVspt_embed[0]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		      mh2piDcaZVspt_embed[0]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		      mh2piDcaXYVspt_embed[0]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		    }
		}

	      if(McTrack->isHFT==1)
		{
		  mh2piDcaVspt[1]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2piDcaZVspt[1]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2piDcaXYVspt[1]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
	
    		  mh2piDcaVspt_orig[1]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2piDcaZVspt_orig[1]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2piDcaXYVspt_orig[1]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		}
	      if(McTrack->isHFT==1&&McTrack->trueHFT==1)
		{
		  mh2piDcaVspt[2]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2piDcaZVspt[2]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2piDcaXYVspt[2]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);

    		  mh2piDcaVspt_orig[2]->Fill(McTrack->rpt,McTrack->dca,weight_pi0);
		  mh2piDcaZVspt_orig[2]->Fill(McTrack->rpt,McTrack->dcaz,weight_pi0);
		  mh2piDcaXYVspt_orig[2]->Fill(McTrack->rpt,McTrack->dcaxy,weight_pi0);
		}
	    }
	  if((McTrack->geantId==2||McTrack->geantId==3)&&fabs(McTrack->pgeantId)==421)
	    {

	       DcaXY_D0[1]->Fill(McTrack->rpt,McTrack->dcaxy);
	       DcaZ_D0[1]->Fill(McTrack->rpt,McTrack->dcaz);
	    }

	}
    }
  



  TNtuple*  Pair=(TNtuple*) infile->Get("nt_pair");
  StPair*  pair=new StPair;
  
 pair->Init(Pair);
  cout<< Pair->GetEntries() <<endl;
  for(Int_t ipair=0;ipair<Pair->GetEntries();ipair++)//
    {
      if(ipair%100000==0)
	{
	  cout<<"working on Pair  "<<ipair<<endl;
	}
      pair->GetEntry(ipair);
      
  
      /*    

      if(fabs(pair->vz)>6) continue; 
      if(pair->p1geantId!=2&&pair->p1geantId!=3)  continue; 
      if(pair->p2geantId!=2&&pair->p2geantId!=3)  continue; 
      if(fabs(pair->p1eta)>0.7) continue;
      if(pair->p1pt<=0.2) continue;
      if(pair->p2pt<=0.2) continue;

      

      if(pair->p1pgeantId==1)
	{
	  Fill_gamma_electron_Mc(pair,0);
	  if(pair->t1isHFT==1)
	  Fill_gamma_electron_Mc(pair,1);
	  if(pair->t1isHFT==1&&pair->t1trueHFT)
	  Fill_gamma_electron_Mc(pair,2);
	}
      if(pair->p1pgeantId==149)
	{
	  Fill_pi0_electron_Mc(pair,0);
	  if(pair->t1isHFT==1)
	    Fill_pi0_electron_Mc(pair,1);
	  if(pair->t1isHFT==1&&pair->t1trueHFT)
	    Fill_pi0_electron_Mc(pair,2);
	}
      
      //if(pair->p1ncom<15) continue;
      //     if(fabs(pair->p1pt-pair->p1rpt)/pair->p1pt>1) continue;

      if(fabs((pair->p1pt-pair->p1rpt))/pair->p1pt>1) continue;            
      if(fabs(pair->p1reta)>0.7) continue;
      if(pair->p1rpt<=0.2) continue;
      if(pair->p2rpt<=0.2) continue;
      if(pair->p1nfit<=20||pair->p1nfit/pair->p1nmax<=0.52||pair->p1ncom<15) continue;
     
      if(pair->pairDCA>0.6||pair->massDCA>0.06) continue;

*/


      //-----------------------------------------------                                                                                             
      if(pair->p1geantId!=2&&pair->p1geantId!=3)  continue;                                                                                      
      if(pair->p2geantId!=2&&pair->p2geantId!=3)  continue;                                                                                      
      if(pair->p2geantId==pair->p1geantId)  continue;                                                                                        
      
      if(fabs(pair->p1reta)>=0.7) continue;                                                                                                      
      if(pair->p1rpt<=0.2) continue;                                                                                                             
      if(pair->p1nfit<20||pair->p1nfit/pair->p1nmax<=0.52|| fabs(pair->p1dca)>=1.5||pair->p1ncom<=15) continue;                                  
      if(fabs((pair->p1pt-pair->p1rpt))/pair->p1pt>1) continue;            
      
      
      if(pair->p2rpt<=0.2) continue;                                                                                                             
      if(fabs(pair->p2reta)>=1) continue;                                                                                                        
      if(pair->p2nfit<20||pair->p2nfit/pair->p2nmax<=0.52|| fabs(pair->p2dca)>=3||pair->p1ncom<=15) continue;                                
       if(fabs((pair->p2pt-pair->p2rpt))/pair->p2pt>1) continue;            
      if(pair->pairDCA>=0.6||pair->massDCA>=0.06) continue;                                                                                  
      
      // ----------------------------------------------- 
      

      if(pair->p1pgeantId==1)
	{
	   Fill_gamma_electron_Rc(pair,0);
	  if(pair->t1isHFT==1)
	  Fill_gamma_electron_Rc(pair,1);
	  if(pair->t1isHFT==1&&pair->t1trueHFT)
	  Fill_gamma_electron_Rc(pair,2);
	}
      if(pair->p1pgeantId==149)
	{
	   Fill_pi0_electron_Rc(pair,0);
	  if(pair->t1isHFT==1)
	    Fill_pi0_electron_Rc(pair,1);
	  if(pair->t1isHFT==1&&pair->t1trueHFT)
	    Fill_pi0_electron_Rc(pair,2);
	}

      if(pair->p1pgeantId==147)
	{
	   Fill_eta_electron_Rc(pair,0);
	  if(pair->t1isHFT==1)
	    Fill_eta_electron_Rc(pair,1);
	  if(pair->t1isHFT==1&&pair->t1trueHFT)
	    Fill_eta_electron_Rc(pair,2);
	
	}



      
      // if(pair->t1isHFT==1&&pair->p1svx==pair->p2svx)
      // 	{
      // 	  if(pair->p1pgeantId==7){
      // 	    Mtp_pi0[0]->Fill(pair->p1svx,pair->p1svy);		
      // 	    Rctp_pi0[0]->Fill(pair->xpair,pair->ypair);
      // 	    pairDca_pi0[0]->Fill(pair->p1rpt,pair->pairDCA);
      // 	    pairMass_pi0[0]->Fill(pair->p1rpt,pair->massDCA);
      // 	    Conversion_radius_pi0[0]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy));
      // 	    Conversion_Rc_radius_pi0[0]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair));
      // 	  }
      // 	  if(pair->p1pgeantId==1){
      // 	    Mtp_gamma[0]->Fill(pair->p1svx,pair->p1svy);		
      // 	    Rctp_gamma[0]->Fill(pair->xpair,pair->ypair);
      // 	    pairDca_gamma[0]->Fill(pair->p1rpt,pair->pairDCA);
      // 	    pairMass_gamma[0]->Fill(pair->p1rpt,pair->massDCA);
      // 	    Conversion_radius_gamma[0]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy));
      // 	    Conversion_Rc_radius_gamma[0]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair));
      // 	  }

      // 	}
      // // add mc HFT
      // if(pair->t1isHFT==1&&pair->t1mcHFT==1&&pair->p1svx==pair->p2svx)
      // 	{
      // 	  if(pair->p1pgeantId==7){
      // 	    Mtp_pi0[1]->Fill(pair->p1svx,pair->p1svy);		
      // 	    Rctp_pi0[1]->Fill(pair->xpair,pair->ypair);
      // 	    pairDca_pi0[1]->Fill(pair->p1rpt,pair->pairDCA);
      // 	    pairMass_pi0[1]->Fill(pair->p1rpt,pair->massDCA);
      // 	    Conversion_radius_pi0[1]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy));
      // 	    Conversion_Rc_radius_pi0[1]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair));
      // 	  }
      // 	  if(pair->p1pgeantId==1){
      // 	    Mtp_gamma[1]->Fill(pair->p1svx,pair->p1svy);		
      // 	    Rctp_gamma[1]->Fill(pair->xpair,pair->ypair);
      // 	    pairDca_gamma[1]->Fill(pair->p1rpt,pair->pairDCA);
      // 	    pairMass_gamma[1]->Fill(pair->p1rpt,pair->massDCA);
      // 	    Conversion_radius_gamma[1]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy));
      // 	    Conversion_Rc_radius_gamma[1]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair));
      // 	  }

      // 	}

      // // add true HFT 
      // if(pair->t1isHFT==1&&pair->t1mcHFT==1&&pair->t1trueHFT==1&&pair->p1svx==pair->p2svx)
      // 	{
      // 	  if(pair->p1pgeantId==7){
      // 	    Mtp_pi0[2]->Fill(pair->p1svx,pair->p1svy);		
      // 	    Rctp_pi0[2]->Fill(pair->xpair,pair->ypair);
      // 	    pairDca_pi0[2]->Fill(pair->p1rpt,pair->pairDCA);
      // 	    pairMass_pi0[2]->Fill(pair->p1rpt,pair->massDCA);
      // 	    Conversion_radius_pi0[2]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy));
      // 	    Conversion_Rc_radius_pi0[2]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair));
      // 	  }
      // 	  if(pair->p1pgeantId==1){
      // 	    Mtp_gamma[2]->Fill(pair->p1svx,pair->p1svy);		
      // 	    Rctp_gamma[2]->Fill(pair->xpair,pair->ypair);
      // 	    pairDca_gamma[2]->Fill(pair->p1rpt,pair->pairDCA);
      // 	    pairMass_gamma[2]->Fill(pair->p1rpt,pair->massDCA);
      // 	    Conversion_radius_gamma[2]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy));
      // 	    Conversion_Rc_radius_gamma[2]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair));
      // 	  }

      //	}
    }
}

void StReadAna::WriteHistogram()
{
  cout<<"  write"<<endl;
  mOutputFile->cd();


   Gamma_pT->Write();
   EtaDalitz_pT->Write();
   Pi0Daliz_pT->Write();
   Pi_pT->Write();
   Electron_pT->Write();


  for(Int_t ihist=0;ihist<3;ihist++){
    
    // mh3mcHFTVsptVsEta_pi[ihist]->Write();
    // mh3mcHFTVsptVsEta_pi0_e[ihist]->Write();
    // mh3mcHFTVsptVsEta_gamma_e[ihist]->Write();

    Events_gamma[ihist]->Write();
    Events_pi0[ihist]->Write();
    Events_eta[ihist]->Write();
    
    pT_spectra_gamma[ihist]->Write();
    pT_spectra_pi0[ihist]->Write();
    pT_spectra_eta[ihist]->Write();


    // mh2piDcaVspt[ihist]->Write();
    // mh2piDcaZVspt[ihist]->Write();
    // mh2piDcaXYVspt[ihist]->Write();

    // mh2pi_plusDcaVspt[ihist]->Write();
    // mh2pi_plusDcaZVspt[ihist]->Write();
    // mh2pi_plusDcaXYVspt[ihist]->Write();

    // mh2pi_minusDcaVspt[ihist]->Write();
    // mh2pi_minusDcaZVspt[ihist]->Write();
    // mh2pi_minusDcaXYVspt[ihist]->Write();

    // mh2piDcaVspt_orig[ihist]->Write();
    // mh2piDcaZVspt_orig[ihist]->Write();
    // mh2piDcaXYVspt_orig[ihist]->Write();

    // mh2piDcaVspt_embed[ihist]->Write();
    // mh2piDcaZVspt_embed[ihist]->Write();
    // mh2piDcaXYVspt_embed[ihist]->Write();

    
    
    mh2_pi0_electronDcaZVspt[ihist]->Write();
    mh2_pi0_electronDcaXYVspt[ihist]->Write();
    mh2_pi0_electronDcaVspt[ihist]->Write();
    
    //   mh3_pi0_electronDcaXYVspt[ihist]->Write();
    mh2_gamma_electronDcaZVspt[ihist]->Write();
    mh2_gamma_electronDcaXYVspt[ihist]->Write();
    mh2_gamma_electronDcaVspt[ihist]->Write();
    //   mh3_gamma_electronDcaXYVspt[ihist]->Write();

    mh2_eta_electronDcaZVspt[ihist]->Write();
    mh2_eta_electronDcaXYVspt[ihist]->Write();
    mh2_eta_electronDcaVspt[ihist]->Write();
    
    
    /*
    Mtp_pi0[ihist]->Write();
    Rctp_pi0[ihist]->Write(); 
    pairDca_pi0[ihist]->Write(); 
    pairMass_pi0[ihist]->Write(); 
    Conversion_radius_pi0[ihist]->Write();
    Conversion_Rc_radius_pi0[ihist]->Write();
    
    Mtp_gamma[ihist]->Write();
    Rctp_gamma[ihist]->Write(); 
    pairDca_gamma[ihist]->Write(); 
    pairMass_gamma[ihist]->Write(); 
    Conversion_radius_gamma[ihist]->Write();
    Conversion_Rc_radius_gamma[ihist]->Write();
    
    //unlike like
    Mtp_pi0_unlike[ihist]->Write();
    Rctp_pi0_unlike[ihist]->Write();
    Conversion_radius_pi0_unlike[ihist]->Write();

    pairDca_pi0_unlike[ihist]->Write();
    pairMass_pi0_unlike[ihist]->Write();
    Conversion_Rc_radius_pi0_unlike[ihist]->Write();

    Mtp_pi0_like[ihist]->Write();
    Rctp_pi0_like[ihist]->Write();
    Conversion_radius_pi0_like[ihist]->Write();

    pairDca_pi0_like[ihist]->Write();
    pairMass_pi0_like[ihist]->Write();
    Conversion_Rc_radius_pi0_like[ihist]->Write();
    */
    Dca_pi0_unlike[ihist]->Write();
    Dca_pi0_like[ihist]->Write();

    DcaXY_pi0_unlike[ihist]->Write();
    DcaXY_pi0_like[ihist]->Write();

    DcaZ_pi0_unlike[ihist]->Write();
    DcaZ_pi0_like[ihist]->Write();

    
    Dca_pi0[ihist]->Write();
    DcaXY_pi0[ihist]->Write();
    DcaZ_pi0[ihist]->Write();
    /*
    //gamma
    Mtp_gamma_unlike[ihist]->Write();
    Rctp_gamma_unlike[ihist]->Write();
    Conversion_radius_gamma_unlike[ihist]->Write();

    pairDca_gamma_unlike[ihist]->Write();
    pairMass_gamma_unlike[ihist]->Write();
    Conversion_Rc_radius_gamma_unlike[ihist]->Write();

    Mtp_gamma_like[ihist]->Write();
    Rctp_gamma_like[ihist]->Write();
    Conversion_radius_gamma_like[ihist]->Write();

    pairDca_gamma_like[ihist]->Write();
    pairMass_gamma_like[ihist]->Write();
    Conversion_Rc_radius_gamma_like[ihist]->Write();
    
    */

    Dca_gamma_unlike[ihist]->Write();
    Dca_gamma_like[ihist]->Write();

    DcaXY_gamma_unlike[ihist]->Write();
    DcaXY_gamma_like[ihist]->Write();

    DcaZ_gamma_unlike[ihist]->Write();
    DcaZ_gamma_like[ihist]->Write();

    //   mh3DcaXY_gamma[ihist]->Write();    
    
    Dca_gamma[ihist]->Write();
    DcaXY_gamma[ihist]->Write();
    DcaZ_gamma[ihist]->Write();
    
    //eta
    Dca_eta_unlike[ihist]->Write();
    Dca_eta_like[ihist]->Write();

    DcaXY_eta_unlike[ihist]->Write();
    DcaXY_eta_like[ihist]->Write();

    DcaZ_eta_unlike[ihist]->Write();
    DcaZ_eta_like[ihist]->Write();
    
    Dca_eta[ihist]->Write();
    DcaXY_eta[ihist]->Write();
    DcaZ_eta[ihist]->Write();
    
    DcaXY_D0[ihist]->Write();
    DcaZ_D0[ihist]->Write();


  }
  		
  mOutputFile->Close();
}
void StReadAna::Fill_gamma_electron_Mc(StPair *pair, int hft_flag)
{


 //  Double_t weight_pi0= Weight(pair->p1ppt,pair->p1gppt,pair->p1pgeantId,pair->p1gpgeantId);
  Double_t weight_pi0=Weight(pair->p1pt,pair->p1ppt,pair->p1gppt,pair->p1geantId,pair->p1pgeantId,pair->p1gpgeantId); 
  if(pair->p1svx==pair->p2svx)
    {
      Mtp_gamma[hft_flag]->Fill(pair->p1svx,pair->p1svy,weight_pi0);		
      Conversion_radius_gamma[hft_flag]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy),weight_pi0);
    }
  if(pair->p1geantId!=pair->p2geantId)
    {
      Mtp_gamma_unlike[hft_flag]->Fill(pair->p1svx,pair->p1svy,weight_pi0);		
      Conversion_radius_gamma_unlike[hft_flag]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy),weight_pi0);
    }
  if(pair->p1geantId==pair->p2geantId)
    {
      Mtp_gamma_like[hft_flag]->Fill(pair->p1svx,pair->p1svy,weight_pi0);		
      Conversion_radius_gamma_like[hft_flag]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy),weight_pi0);
    }
  return ;
}
void StReadAna::Fill_pi0_electron_Mc(StPair *pair, int hft_flag)
{
  //  Double_t weight_pi0= Weight(pair->p1ppt,0,pair->p1pgeantId,pair->p1gpgeantId);
  Double_t weight_pi0=Weight(pair->p1pt,pair->p1ppt,pair->p1gppt,pair->p1geantId,pair->p1pgeantId,pair->p1gpgeantId); 
  if(pair->p1svx==pair->p2svx)
    {
      Mtp_pi0[hft_flag]->Fill(pair->p1svx,pair->p1svy,weight_pi0);		
      Conversion_radius_pi0[hft_flag]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy),weight_pi0);
    }  
  if(pair->p1geantId!=pair->p2geantId)
    {
      Mtp_pi0_unlike[hft_flag]->Fill(pair->p1svx,pair->p1svy,weight_pi0);		
      Conversion_radius_pi0_unlike[hft_flag]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy),weight_pi0);
    }
  if(pair->p1geantId==pair->p2geantId)
    {
      Mtp_pi0_like[hft_flag]->Fill(pair->p1svx,pair->p1svy,weight_pi0);		
      Conversion_radius_pi0_like[hft_flag]->Fill(pair->p1rpt,sqrt(pair->p1svx*pair->p1svx+pair->p1svy*pair->p1svy),weight_pi0);
    }
  
  return ;
}
void StReadAna::Fill_gamma_electron_Rc(StPair *pair, int hft_flag)
{
  //  Double_t weight_pi0= Weight(pair->p1ppt,pair->p1gppt,pair->p1pgeantId,pair->p1gpgeantId);
  Double_t weight_pi0=Weight(pair->p1pt,pair->p1ppt,pair->p1gppt,pair->p1geantId,pair->p1pgeantId,pair->p1gpgeantId); 
  if(pair->p1svx==pair->p2svx)
    {
      Rctp_gamma[hft_flag]->Fill(pair->xpair,pair->ypair,weight_pi0);
      pairDca_gamma[hft_flag]->Fill(pair->p1rpt,pair->pairDCA,weight_pi0);
      pairMass_gamma[hft_flag]->Fill(pair->p1rpt,pair->massDCA,weight_pi0);
      Conversion_Rc_radius_gamma[hft_flag]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair),weight_pi0);
      Dca_gamma[hft_flag]->Fill(pair->p1rpt,pair->p1dca,weight_pi0);
      DcaXY_gamma[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,weight_pi0);
      DcaZ_gamma[hft_flag]->Fill(pair->p1rpt,pair->p1dcaz,weight_pi0);
      //     mh3DcaXY_gamma[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,pair->p1rphi,weight_pi0);
    }
  if(pair->p1geantId!=pair->p2geantId)
    {
   
      Rctp_gamma_unlike[hft_flag]->Fill(pair->xpair,pair->ypair,weight_pi0);
      pairDca_gamma_unlike[hft_flag]->Fill(pair->p1rpt,pair->pairDCA,weight_pi0);
      pairMass_gamma_unlike[hft_flag]->Fill(pair->p1rpt,pair->massDCA,weight_pi0);
      Conversion_Rc_radius_gamma_unlike[hft_flag]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair),weight_pi0);   
      Dca_gamma_unlike[hft_flag]->Fill(pair->p1rpt,pair->p1dca,weight_pi0);
      DcaXY_gamma_unlike[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,weight_pi0);
      DcaZ_gamma_unlike[hft_flag]->Fill(pair->p1rpt,pair->p1dcaz,weight_pi0);


    }  
  
  if(pair->p1geantId==pair->p2geantId)
    {
      Rctp_gamma_like[hft_flag]->Fill(pair->xpair,pair->ypair,weight_pi0);
      pairDca_gamma_like[hft_flag]->Fill(pair->p1rpt,pair->pairDCA,weight_pi0);
      pairMass_gamma_like[hft_flag]->Fill(pair->p1rpt,pair->massDCA,weight_pi0);
      Conversion_Rc_radius_gamma_like[hft_flag]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair),weight_pi0);   
      Dca_gamma_like[hft_flag]->Fill(pair->p1rpt,pair->p1dca,weight_pi0);
      DcaXY_gamma_like[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,weight_pi0);
      DcaZ_gamma_like[hft_flag]->Fill(pair->p1rpt,pair->p1dcaz,weight_pi0);
      
    }  


  return ;
}
void StReadAna::Fill_pi0_electron_Rc(StPair *pair, int hft_flag)
{
  //  Double_t weight_pi0= Weight(pair->p1ppt,pair->p1gppt,pair->p1pgeantId,pair->p1gpgeantId);
  Double_t weight_pi0=Weight(pair->p1pt,pair->p1ppt,pair->p1gppt,pair->p1geantId,pair->p1pgeantId,pair->p1gpgeantId); 

  // if(pair->p1geantId==2) cout<< " electron "<< weight_pi0<<endl;
  // if(pair->p1geantId==3) cout<< " positron "<< weight_pi0<<endl;

  if(pair->p1svx==pair->p2svx)
    {
      Rctp_pi0[hft_flag]->Fill(pair->xpair,pair->ypair,weight_pi0);
      pairDca_pi0[hft_flag]->Fill(pair->p1rpt,pair->pairDCA,weight_pi0);
      pairMass_pi0[hft_flag]->Fill(pair->p1rpt,pair->massDCA,weight_pi0);
      Conversion_Rc_radius_pi0[hft_flag]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair),weight_pi0);
      Dca_pi0[hft_flag]->Fill(pair->p1rpt,pair->p1dca,weight_pi0);
      DcaXY_pi0[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,weight_pi0);
      DcaZ_pi0[hft_flag]->Fill(pair->p1rpt,pair->p1dcaz,weight_pi0);
      //     mh3DcaXY_pi0[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,pair->p1rphi,weight_pi0);
    }
  if(pair->p1geantId!=pair->p2geantId)
    {
      Rctp_pi0_unlike[hft_flag]->Fill(pair->xpair,pair->ypair,weight_pi0);
      pairDca_pi0_unlike[hft_flag]->Fill(pair->p1rpt,pair->pairDCA,weight_pi0);
      pairMass_pi0_unlike[hft_flag]->Fill(pair->p1rpt,pair->massDCA,weight_pi0);
      Conversion_Rc_radius_pi0_unlike[hft_flag]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair),weight_pi0);   
      Dca_pi0_unlike[hft_flag]->Fill(pair->p1rpt,pair->p1dca,weight_pi0);
      DcaXY_pi0_unlike[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,weight_pi0);
      DcaZ_pi0_unlike[hft_flag]->Fill(pair->p1rpt,pair->p1dcaz,weight_pi0);


    }  
  if(pair->p1geantId==pair->p2geantId)
    {
      Rctp_pi0_like[hft_flag]->Fill(pair->xpair,pair->ypair,weight_pi0);
      pairDca_pi0_like[hft_flag]->Fill(pair->p1rpt,pair->pairDCA,weight_pi0);
      pairMass_pi0_like[hft_flag]->Fill(pair->p1rpt,pair->massDCA,weight_pi0);
      Conversion_Rc_radius_pi0_like[hft_flag]->Fill(pair->p1rpt,sqrt(pair->xpair*pair->xpair+pair->ypair*pair->ypair),weight_pi0);   
      Dca_pi0_like[hft_flag]->Fill(pair->p1rpt,pair->p1dca,weight_pi0);
      DcaXY_pi0_like[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,weight_pi0);
      DcaZ_pi0_like[hft_flag]->Fill(pair->p1rpt,pair->p1dcaz,weight_pi0);

    }  


  return ;
}
void StReadAna::Fill_eta_electron_Rc(StPair *pair, int hft_flag)
{
  //  Double_t weight_pi0= Weight(pair->p1ppt,pair->p1gppt,pair->p1pgeantId,pair->p1gpgeantId);
  Double_t weight_pi0=Weight(pair->p1pt,pair->p1ppt,pair->p1gppt,pair->p1geantId,pair->p1pgeantId,pair->p1gpgeantId); 
  if(pair->p1svx==pair->p2svx)
    {
      Dca_eta[hft_flag]->Fill(pair->p1rpt,pair->p1dca,weight_pi0);
      DcaXY_eta[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,weight_pi0);
      DcaZ_eta[hft_flag]->Fill(pair->p1rpt,pair->p1dcaz,weight_pi0);
    }
  if(pair->p1geantId!=pair->p2geantId)
    {

      Dca_eta_unlike[hft_flag]->Fill(pair->p1rpt,pair->p1dca,weight_pi0);
      DcaXY_eta_unlike[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,weight_pi0);
      DcaZ_eta_unlike[hft_flag]->Fill(pair->p1rpt,pair->p1dcaz,weight_pi0);
    }  
  if(pair->p1geantId==pair->p2geantId)
    {
      Dca_eta_like[hft_flag]->Fill(pair->p1rpt,pair->p1dca,weight_pi0);
      DcaXY_eta_like[hft_flag]->Fill(pair->p1rpt,pair->p1dcaxy,weight_pi0);
      DcaZ_eta_like[hft_flag]->Fill(pair->p1rpt,pair->p1dcaz,weight_pi0);

    }  


  return ;
}



Double_t StReadAna::Weight(Float_t pt, Float_t ppt,Float_t gppt,Float_t geantId,Float_t pgeantId,Float_t gpgeantId)
{


  //    return 1.0;
  // cout<< Graph_from_Gamma_pT->Eval(2.4)<<endl;
  // cout<< Graph_from_Pi_pT->Eval(2.4)<<endl;
  // cout<< Graph_from_Electron_pT->Eval(2.4)<<endl;

  Double_t weight_flat=0; 
  Double_t weight=0; 
  // hadron 
  if((geantId==8||geantId==9||geantId==10008||geantId==10009)&&pt>0&&pt<10) // hadron 
    {
      //   weight=gr_pi->Eval(pt);
      weight=Graph_from_Pi_pT->Eval(pt);
    }
  
  
  if((geantId==2||geantId==3)&&pgeantId==1&&ppt<20&&ppt>0) // gamma 
    {
      //   weight=Graph_from_Gamma_0->Eval(ppt);
      weight=Graph_from_Gamma_0->Eval(ppt);
    }

  if((geantId==2||geantId==3)&&pgeantId==147&&ppt<20&&ppt>0) // Eta 
    {
      weight=  Graph_from_Eta_weight_0->Eval(ppt);
	   //weight=Graph_from_EtaDalitz_pT->Eval(ppt);
    }


  if((geantId==2||geantId==3)&&pgeantId==149&&ppt<20&&ppt>0) // pi0 
    {
      weight=  Graph_from_Pi0_weight_0->Eval(ppt);
      //weight=Graph_from_Pi0Dalitz_pT->Eval(ppt);
    }

  return weight;
 
//return weight_flat*weight;
  
}


