// Based on the MuDST tools written by Frank Laue.
// Based on the DST Tutorial by Dan Magestro on the STAR Computing/Tutorials page.
// Updated 9/4/2006 by Jim Thomas to include the latest DST format, and Scheduler techniques.

#include <iostream>
#include "St_ehcorrelationMaker.h"
#include "StEventTypes.h"

#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"

#include "StEmcUtil/others/emcDetectorName.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/projection/StEmcPosition.h"
#include "StEmcADCtoEMaker/StBemcData.h"
#include "StEmcADCtoEMaker/StEmcADCtoEMaker.h"
#include "StEmcRawMaker/StBemcTables.h"
#include "StPreEclMaker/StPreEclMaker.h"
#include "StEpcMaker/StEpcMaker.h"
#include "St_db_Maker/St_db_Maker.h"
#include "StDetectorDbMaker/StDetectorDbMaker.h"
#include "StDetectorDbMaker/StDetectorDbTriggerID.h"
#include "StPhysicalHelix.hh"

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TObjArray.h"

#define NumberOfTH1F      20                     // Number of Histograms

ClassImp(St_ehcorrelationMaker)                   // Macro for CINT compatibility


St_ehcorrelationMaker::St_ehcorrelationMaker( StMuDstMaker* maker ) : StMaker("St_ehcorrelationMaker")

{ // Initialize and/or zero all public/private data members here.
  /*
   for ( Int_t i = 0 ; i < NumberOfTH1F ; i++ )  // Zero the histogram pointers
   {
   histogram[i] = NULL ;
   histogram_2D[i] = NULL ;
   }
   */
  
  mMuDstMaker      = maker ;                    // Pass MuDst pointer to DstAnlysisMaker Class member functions
  histogram_output = NULL  ;                    // Zero the Pointer to histogram output file
  mEventsProcessed = 0     ;                    // Zero the Number of Events processed by the maker
  mHistogramOutputFileName = "" ;               // Histogram Output File Name will be set inside the "analysis".C macro
  
}


St_ehcorrelationMaker::~St_ehcorrelationMaker() 

{ // Destroy and/or zero out all public/private data members here.
  
}


Int_t St_ehcorrelationMaker::Init( )

{ // Do once at the start of the analysis
  
  // Create Histogram output file
  
  //cout << "create histgram files" << endl;
  
  histogram_output = new TFile( mHistogramOutputFileName, "recreate" ) ;  // Name was set previously in calling macro
  
  // Create Histograms
  //cout << "create histgram" << endl;
  
  const Int_t    nbins    =  100   ;
  
  //---------------- defining eta bin boundaries
  Int_t mNEta = 150;
  Float_t smetawdh, seta1wdh, seta2wdh, seta12wdh;
  smetawdh=0.9806;
  seta1wdh=0.7277;
  seta2wdh=0.9398;
  seta12wdh=0.0406;
  
  Float_t shift1, shift2;
  shift1 = 2.*smetawdh + seta1wdh;
  shift2 = shift1 + (seta1wdh+seta12wdh)*2*74 + (seta1wdh+seta12wdh) + (seta2wdh+seta12wdh);
  Float_t zb[151];
  Float_t mEtaB[303];
  zb[0] = 2.*smetawdh;
  for(int i=0; i<mNEta; i++){
    if(i<mNEta/2) {
      zb[i+1] = zb[i] + (seta1wdh+seta12wdh)*2;
    }
    else{
      zb[i+1] = zb[i] + (seta2wdh+seta12wdh)*2;
    }
    mEtaB[152+i] = -log(tan(atan2(float(230.705),zb[i])/2.0));
    mEtaB[150-i] = -mEtaB[152+i];
    //	cout<<"mEtaB["<<i<<"] = "<<mEtaB[i]<<endl;
  }
  mEtaB[152+mNEta] = -log(tan(atan2(float(230.705),zb[mNEta])/2.0));
  mEtaB[0] = - mEtaB[302];
  mEtaB[151] = 0;
  //cout<<"mEtaB[150] = "<<mEtaB[mNEta]<<endl;
  
  
  
  //-------------- defining phi bin boundaries
  //	Float_t *mPhiB[16] = {-0.04169,-0.03528,-0.02887,-0.02246,-0.01604,-0.00963,-0.00321,0.00321,0.00962,0.01604,0.02245,0.02887,0.03528,0.04169,0.04775 };
  
  Int_t mNSub = 15;
  Float_t sphiwdh = 0.668;
  Float_t sphidwdh = 0.07874;
  Float_t smdgaswdh = 0.295;
  
  Float_t shift = -22.835/2. + smdgaswdh + sphiwdh;
  Float_t mYB[16];
  Float_t mPhiB[16];
  mYB[0] = -22.835/2. + smdgaswdh;
  
  for(int i = 0; i < mNSub; i++){
    if(i==0 || i==(mNSub-1)) mYB[i+1] = mYB[i] + sphiwdh*2. + sphidwdh;
    else mYB[i+1] = mYB[i] + (sphiwdh + sphidwdh)*2.;
    mPhiB[i] = atan2(mYB[i], float(232.742));
    //		cout<<"mPhiB["<<i<<"] = "<<mPhiB[i]<<endl;
  }
  mPhiB[mNSub] = atan2(mYB[mNSub],float(232.742));
  //	cout<<"mPhiB[15] = "<<mPhiB[mNSub]<<endl;
  
  
  Int_t mNModule = 120;
  Float_t mPhiOffset = (75.-3.)/180.*TMath::Pi();
  Float_t mPhiStep = -TMath::TwoPi() / (mNModule/2);
  Float_t mPhiModule[60];
  Float_t mGlobalPhiB[901];
  
  for(int i = 0; i< mNModule/2; i++){
    Double_t phiW = mPhiOffset + mPhiStep*i;
    while(phiW >= TMath::Pi()) phiW -= TMath::TwoPi();
    while(phiW < -TMath::Pi()) phiW += TMath::TwoPi();
    mPhiModule[i] = phiW;
    //		cout<<"mPhiModule["<<i<<"] = "<<mPhiModule[i]<<endl;
    for(int j = 0; j <=mNSub; j++){
      if(j == 0 && i != 0){
        if(i==42) mGlobalPhiB[900] = mPhiModule[i] - mPhiB[j];
        else mGlobalPhiB[i*15+j] = ((mGlobalPhiB[i*15+j])+(mPhiModule[i] - mPhiB[j]))/2.;
      }else{
        if(i==59 && j==15) mGlobalPhiB[0] = ((mPhiModule[i]-mPhiB[j])+(mGlobalPhiB[0]))/2.;
        else mGlobalPhiB[i*15+j] = mPhiModule[i] - mPhiB[j];
      }
      //	cout<<"mGlobalPhiB["<<i*15+j<<"] = "<<mGlobalPhiB[i*15+j]<<endl;
    }
  }
  //sorting mGlobalPhiB
  for(int i = 0; i< 901; i++){
    Float_t min = 999;
    Int_t minindex;
    for(int j = i; j < 901; j++){
      if(min > mGlobalPhiB[j]){
        min = mGlobalPhiB[j];
        minindex = j;
      }
    }
    mGlobalPhiB[minindex] = mGlobalPhiB[i];
    mGlobalPhiB[i] = min;
    //		cout<<"mGlobalPhiB["<<i<<"] = "<<mGlobalPhiB[i]<<endl;
  }
  
  
  
  
  /*
   histogram[1]  = new TH1F( "dca", "Global dca", nbins, 0, 10 ) ;
   histogram[4]  = new TH1F( "phi", "phi for all particles", nbins, -3.14, 3.14 ) ;
   histogram[5]  = new TH1F( "eta", "eta after EMC asso.", nbins, -2.5, 2.5 ) ;
   histogram[6]  = new TH1F( "eta_bemc", "eta of bEMC", nbins, -2.5, 2.5 ) ;
   */
  
  HVertex[0] = new TH1F( "Vertex_0", "Event Vertex Z Position all ", 200, -100.0, 100.0 ) ;
  HVertex[1] = new TH1F( "Vertex_1", "Event Vertex Z Position cut ", 200, -100.0, 100.0 ) ;
  Heop[0]  = new TH1F( "EoP", "energy and mom. match", 300, 0, 3.0 ) ;
  Heop[1]  = new TH1F( "EoP_cut", "energy and mom. match af. cut", 300, 0, 3.0 ) ;
  Htrig[0] = new TH1F ("IDtrig_0", "trigger ID info bf eve sel", 13,-1.5,11.5);
  Htrig[1] = new TH1F ("IDtrig_1", "trigger ID info af eve sel", 13,-1.5,11.5);
  Hover = new TH1F ("Over_seltrk", "Over sel trk", 10,-1,9);
  Hseltrk = new TH1F ("Num_seltrk", "Nummer of seltrk", 100,0,100);
  Hinvmass[0]  = new TH2F( "Invmass_opp", "Invmass opp sign", 200,0,20,100, 0, 0.5) ;
  Hinvmass[1]  = new TH2F( "Invmass_same", "Invmass same sign", 200,0,20,100, 0, 0.5) ;
  Hinvmass_wocut[0]  = new TH2F( "Invmass_opp_wocut", "Invmass opp sign wo cut", 200,0,20,100, 0, 0.5) ;
  Hinvmass_wocut[1]  = new TH2F( "Invmass_same_wocut", "Invmass same sign wo cut", 200,0,20,100, 0, 0.5) ;
  Hopenphi[0]  = new TH1F( "Hopenphi_opp", "phi opp sign", 160, 0, 1.6) ;
  Hopenphi[1]  = new TH1F( "Hopenphi_same", "phi same sign", 160, 0, 1.6) ;
  Hopentheta[0]  = new TH1F( "Hopentheta_opp", "theta opp sign", 160, 0, 1.6) ;
  Hopentheta[1]  = new TH1F( "Hopentheta_same", "theta same sign", 160, 0, 1.6) ;
  HDCA[0]  = new TH1F( "HDCA_opp", "DCA opp sign", 160, 0, 1.6) ;
  HDCA[1]  = new TH1F( "HDCA_same", "DCA same sign", 160, 0, 1.6) ;
  Hopenangle[0]  = new TH1F( "Hopenangle_opp", "angle opp sign", 160, 0, 1.6) ;
  Hopenangle[1]  = new TH1F( "Hopenangle_same", "angle same sign", 160, 0, 1.6) ;
  
  HpT_dEdx[0]  = new TH2F( "Pt_Eloss", "dEdx vs. Pt", 1000, 0.0, 10.0, 1000, 0.0, 10.0 ) ;
  HpT_dEdx[1]  = new TH2F( "Pt_Eloss_ncut", "dEdx vs. Pt : nhit cut", 1000, 0.0, 10.0, 1000, 0.0, 10.0 ) ;
  HpT_dEdx[2]  = new TH2F( "Pt_Eloss_epcut", "dEdx vs. Pt : ep cut", 1000, 0.0, 10.0, 1000, 0.0, 10.0 ) ;
  HpT_dEdx[3]  = new TH2F( "Pt_Eloss_allcut", "dEdx vs. Pt : all cut", 1000, 0.0, 10.0, 1000, 0.0, 10.0 ) ;
  HpT_dEdx_trig  = new TH2F( "Pt_Eloss_h2", "dEdx vs. Pt : h2", 200, 0.0, 20.0, 1000, 0.0, 10.0 ) ;
  Hep_corr  = new TH2F( "E_p_corr", "E_p_corr_af_cut", 50, 0.0, 5.0, 50, 0.0, 5.0 ) ;
  Hnhit_corr = new TH2F( "Nhit_corr", "eta and phi hit corr.", 15, 0, 15, 15, 0, 15 ) ;
  Heta_phi_corr  = new TH2F( "EMC_p_e", "EMC_phi_eta", 256, -3.2, 3.2, 220, -1.1, 1.1 ) ;
  Hmatch[0]  = new TH2F( "del_phi", "del phi of bEMC hit and proj.", 100, 0, 10, nbins, -0.1, 0.1 ) ;
  Hmatch[1]  = new TH2F( "del_eta", "del eta of bEMC hit and proj.", 100, 0, 10, nbins, -0.1, 0.1 ) ;
  Heop_dEdx = new TH2F( "eop_dEdx", "eop dEdx corr pT>2", 30, 0, 3.0, 100, 0.0, 10.0 ) ;
  
  Hopenphi_pT[0]  = new TH2F( "Hopenphi_opp_pT", "phi opp sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopenphi_pT[1]  = new TH2F( "Hopenphi_same_pT", "phi same sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopentheta_pT[0]  = new TH2F( "Hopentheta_opp_pT", "theta opp sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopentheta_pT[1]  = new TH2F( "Hopentheta_same_pT", "theta same sign vs pT", 100,0,10, 160, 0, 1.6) ;
  HDCA_pT[0]  = new TH2F( "HDCA_opp_pT", "DCA opp sign vs pT", 100,0,10, 160, 0, 1.6) ;
  HDCA_pT[1]  = new TH2F( "HDCA_same_pT", "DCA same sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopenangle_pT[0]  = new TH2F( "Hopenangle_opp_pT", "angle opp sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopenangle_pT[1]  = new TH2F( "Hopenangle_same_pT", "angle same sign vs pT", 100,0,10, 160, 0, 1.6) ;
  
  
  //--- trig dep. e-h w. e-e
  
  Hphi_corr_we[0][0] = new TH2F( "phi_corr_0_c0_we", "azm. corr e all 0.5 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[0][1] = new TH2F( "phi_corr_1_c0_we", "azm. corr opp sign 0.5 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[0][2] = new TH2F( "phi_corr_2_c0_we", "azm. corr same sign 0.5 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[0][3] = new TH2F( "phi_corr_3_c0_we", "azm. corr semi ele 0.5 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[0][4] = new TH2F( "phi_corr_4_c0_we", "azm. corr opp sign keep part art 0.5 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[0][5] = new TH2F( "phi_corr_5_c0_we", "azm. corr same sign keep part art 0.5 we ", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[0][6] = new TH2F( "phi_corr_6_c0_we", "azm. corr opp sign no part art 0.5 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[0][7] = new TH2F( "phi_corr_7_c0_we", "azm. corr same sign no part art 0.5 we ", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  
  Hphi_corr_we[1][0] = new TH2F( "phi_corr_0_c1_we", "azm. corr e all 0.4 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[1][1] = new TH2F( "phi_corr_1_c1_we", "azm. corr opp sign 0.4 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[1][2] = new TH2F( "phi_corr_2_c1_we", "azm. corr same sign 0.4 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[1][3] = new TH2F( "phi_corr_3_c1_we", "azm. corr semi ele 0.4 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[1][4] = new TH2F( "phi_corr_4_c1_we", "azm. corr opp sign keep part art 0.4 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[1][5] = new TH2F( "phi_corr_5_c1_we", "azm. corr same sign keep part art 0.4 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[1][6] = new TH2F( "phi_corr_6_c1_we", "azm. corr opp sign no part art 0.4 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[1][7] = new TH2F( "phi_corr_7_c1_we", "azm. corr same sign no part art 0.4 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  
  Hphi_corr_we[2][0] = new TH2F( "phi_corr_0_c2_we", "azm. corr e all 0.3 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[2][1] = new TH2F( "phi_corr_1_c2_we", "azm. corr opp sign  0.3 we" , 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[2][2] = new TH2F( "phi_corr_2_c2_we", "azm. corr same sign 0.3 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[2][3] = new TH2F( "phi_corr_3_c2_we", "azm. corr semi ele 0.3 we" , 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[2][4] = new TH2F( "phi_corr_4_c2_we", "azm. corr opp sign keep part art 0.3 we" , 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[2][5] = new TH2F( "phi_corr_5_c2_we", "azm. corr same sign keep part art 0.3  we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[2][6] = new TH2F( "phi_corr_6_c2_we", "azm. corr opp sign no part art 0.3 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_we[2][7] = new TH2F( "phi_corr_7_c2_we", "azm. corr same sign no part art 0.3 we", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  
  //--- trig dep. e-h remove. conversion electron
  
  Hphi_corr_rc[0][0] = new TH2F( "phi_corr_0_c0_rc", "azm. corr e all 0.5 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[0][1] = new TH2F( "phi_corr_1_c0_rc", "azm. corr opp sign  0.5 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[0][2] = new TH2F( "phi_corr_2_c0_rc", "azm. corr same sign 0.5 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[0][3] = new TH2F( "phi_corr_3_c0_rc", "azm. corr semi ele 0.5 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[0][4] = new TH2F( "phi_corr_4_c0_rc", "azm. corr semi ele 0.5 rp ", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  
  Hphi_corr_rc[1][0] = new TH2F( "phi_corr_0_c1_rc", "azm. corr e all 0.4 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[1][1] = new TH2F( "phi_corr_1_c1_rc", "azm. corr opp sign  0.4 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[1][2] = new TH2F( "phi_corr_2_c1_rc", "azm. corr same sign 0.4 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[1][3] = new TH2F( "phi_corr_3_c1_rc", "azm. corr semi ele 0.4 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[1][4] = new TH2F( "phi_corr_4_c1_rc", "azm. corr semi ele 0.4 rp", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  
  Hphi_corr_rc[2][0] = new TH2F( "phi_corr_0_c2_rc", "azm. corr e all 0.3 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[2][1] = new TH2F( "phi_corr_1_c2_rc", "azm. corr opp sign 0.3 rc" , 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[2][2] = new TH2F( "phi_corr_2_c2_rc", "azm. corr same sign 0.3 rc", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[2][3] = new TH2F( "phi_corr_3_c2_rc", "azm. corr semi ele 0.3 rc" , 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_rc[2][4] = new TH2F( "phi_corr_4_c2_rc", "azm. corr semi ele 0.3 rc 2" , 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  
  // background hadron correlation
  
  Hphi_corr_hadron[0] = new TH2F( "phi_corr_c0_hadron", "azm. corr bg 0.5", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_hadron[1] = new TH2F( "phi_corr_c1_hadron", "azm. corr bg 0.4" , 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  Hphi_corr_hadron[2] = new TH2F( "phi_corr_c2_hadron", "azm. corr bg 0.3", 200, 0.0, 20.0, 256, -3.2, 3.2 ) ;
  
  //--- pT
  
  HpT[0]  = new TH1F( "Pt_h2", "Transverse Momentum for all particles h2", 200, 0.0, 20.0 ) ;
  HpT[1]  = new TH1F( "Pt_1_h2", "pT after proj h2", 200, 0.0, 20.0 ) ;
  HpT[2]  = new TH1F( "Pt_2_h2", "pT after nHit cut h2", 200, 0.0, 20.0 ) ;
  HpT[3]  = new TH1F( "Pt_3_h2", "pT after dEdx cut h2 (electron)", 200, 0.0, 20.0 ) ;
  
  HpT_pho[0] = new TH1F("HpT_photonic_0_h2","nontag electron h2",200,0,20);
  HpT_pho[1] = new TH1F("HpT_photonic_1_h2","oppsign h2",200,0,20);
  HpT_pho[2] = new TH1F("HpT_photonic_2_h2","same sign h2",200,0,20);
  HpT_pho[3] = new TH1F("HpT_photonic_3_h2","all electron h2",200,0,20);
  HpT_pho[4] = new TH1F("HpT_photonic_4_h2","semi inc h2",200,0,20);
  
  HpT_pho_insemi[0] = new TH1F("HpT_pho_insemi_opp","reco pho. insemi",200,0,20);
  HpT_pho_insemi[1] = new TH1F("HpT_pho_insemi_same","reco pho. insemi",200,0,20);
  
  Hass_pT  = new TH1F( "Pt_ass_h2", "pT ass h2", 200, 0.0, 20.0 );
  
  Hele_Z = new TH1F("Hele_Z_ht2","electron vs. Z vertex ht2",800,-40,40);
  Hpho_Z = new TH1F("Hpho_Z_ht2","pho electron vs. Z vertex ht2",800,-40,40);
  
  Hinvmass_pT_Opp  = new TH2F( "Invmass_opp_pT_h2", "Invmass opp sign h2", 200, 0, 20, 100, 0, 0.5) ;
  Hinvmass_pT_Same  = new TH2F( "Invmass_same_pT_h2", "Invmass same sign h2", 200, 0, 20, 100, 0, 0.5) ;
  
  Hinvmass_notreco[0]  = new TH2F( "Invmass_notreco0", "Invmass opp notreco", 200, 0, 20, 100, 0, 0.5) ;
  Hinvmass_notreco[1]  = new TH2F( "Invmass_notreco1", "Invmass same notreco", 200, 0, 20, 100, 0, 0.5) ;
  
  H_dis_phi  = new TH2F( "dis_phi", "delta phi EMC", 200, 0, 20, 200, -0.1, 0.1) ;
  H_dis_eta  = new TH2F( "dis_eta", "delta eta EMC", 200, 0, 20, 200, -0.1, 0.1) ;
  H_dis_phi_TPC  = new TH2F( "dis_phi_TPC", "delta phi EMC TPC point", 200, 0, 20, 3000, -1.5, 1.5) ;
  H_dis_eta_TPC  = new TH2F( "dis_eta_TPC", "delta eta EMC TPC point", 200, 0, 20, 2000, -1, 1) ;
  H_dis_phi_TPC_org  = new TH2F( "dis_phi_TPC_org", "delta phi EMC TPC proj", 200, 0, 20, 3000, -1.5, 1.5) ;
  H_dis_eta_TPC_org  = new TH2F( "dis_eta_TPC_org", "delta eta EMC TPC proj", 200, 0, 20, 2000, -1, 1) ;
  
  H_phi_TPC_EMC = new TH2F("H_phi_TPC_EMC","TPC EMC phi corr",300,-3,3,300,-3,3);
  H_eta_TPC_EMC = new TH2F("H_eta_TPC_EMC","TPC EMC eta corr",100,-1,1,100,-1,1);
  
  H_TPC_EMC_match = new TH1F("H_TPC_EMC_match","# of TPC EMC hit matching",10,0.0,10.0);
  
  //--- check Hist
  
  HdcaGlobal_check = new TH1F("HdcaGlobal_check","dca check",120,-2,10);
  HnHits_check = new TH1F("HnHits_check","nHits check",110,-10,100);
  HnHitsdEdx_check = new TH1F("HnHitsdEdx_check","dca check",120,0,120);
  Hchi_check = new TH1F("Hchi_check","chi2 check",70,-2,5);
  Hflag_check = new TH1F("Hflag_check","flag check",20,-1.0,20.0);
  HnfitOverMax_check = new TH1F("HnfitOverMax_check","nfitOverMax check",100,0.0,2.0);
  
  Heta_check[0] = new TH1F("Heta_check_sel","eta check asso",150,-1.5,1.5);
  Heta_check[1] = new TH1F("Heta_check_trig","eta check trig",150,-1.5,1.5);
  Heta_check[2] = new TH1F("Heta_check_asso","eta check asso",150,-1.5,1.5);
  
  
  HdcaGlobal_check_pair = new TH1F("HdcaGlobal_check_pair","dca check_pair",120,-2,10);
  HnHits_check_pair = new TH1F("HnHits_check_pair","nHits check_pair",110,-10,100);
  HnHitsdEdx_check_pair = new TH1F("HnHitsdEdx_check_pair","dca check_pair",120,0,120);
  Hchi_check_pair = new TH1F("Hchi_check_pair","chi2 check_pair",70,-2,5);
  Heta_check_pair = new TH1F("Heta_check_pair","eta check_pair",200,-1.0,1.0);
  Hflag_check_pair = new TH1F("Hflag_check_pair","flag check_pair",20,-1.0,20.0);
  
  HpT_check[0]  = new TH1F( "Pt_check_0", "electron trigger inc", 200, 0.0, 20.0 ) ;
  HpT_check[1]  = new TH1F( "Pt_check_1", "electron trigger opp", 200, 0.0, 20.0 ) ;
  HpT_check[2]  = new TH1F( "Pt_check_2", "electron trigger same", 200, 0.0, 20.0 ) ;
  HpT_check[3]  = new TH1F( "Pt_check_3", "electron trigger semi", 200, 0.0, 20.0 ) ;
  
  Hnsig_e[0] = new TH2F("Hnsig_e_0","n sigma for electron",100,0,10,200,-10,10);
  Hnsig_e[1] = new TH2F("Hnsig_e_1","n sigma for photonic electron(0.05)",100,0,10,200,-10,10);
  Hnsig_e[2] = new TH2F("Hnsig_e_2","n sigma for photonic electron(0.1)",100,0,10,200,-10,10);
  
  HnSig[0] = new TH2F("HnSig_0","n sigma for ass for opp",100,0,10,200,-10,10);
  HnSig[1] = new TH2F("HnSig_1","n sigma for ass for same",100,0,10,200,-10,10);
  HnSig[2] = new TH2F("HnSig_2","n sigma for ass for semi",100,0,10,200,-10,10);
  
  HpID[0] = new TH2F("HpID_0","pID for ass for opp",100,0,10,110,-101,9);
  HpID[1] = new TH2F("HpID_1","pID for ass for same",100,0,10,110,-101,9);
  HpID[2] = new TH2F("HpID_2","pID for ass for semi",100,0,10,110,-101,9);
  
  HpID_check_pair = new TH2F("HpID_check_pair","pID for pair ",100,0,10,110,-101,9);
  
  Hcheck_pair = new TH2F ("Hcheck_pair_ht2","pair electron check ht2",100,0,10, 10,-1.5,8.5);
  
  Hpair[0] = new TH1F("Hpair0","opp cand",30,-0.5,29.5);
  Hpair[1] = new TH1F("Hpair1","same cand",30,-0.5,29.5);
  
  Hetag_check = new TH1F("Hetag_check","tag check for semi-inclusive",110,-100.5,9.5);
  
  //HdEdx_had = new TH2F ("HdEdx_had", "dEdx for had trigger", 200,0,20, 150, 1.5, 3.0);
  HdEdx_had = new TH2F ("HdEdx_had", "dEdx for had trigger", 200,0,20, 200, -10, 10);
  
  HdEdx_semi  = new TH2F( "Pt_Eloss_semi_h2", "dEdx vs. Pt semi h2", 1000, 0.0, 10.0, 1000, 0.0, 10.0 ) ;
  
  
  Hhad_trig  = new TH1F( "hadron_pT_trig", "hadron trigger", 200, 0.0, 20.0 ) ;
  
  //initial EMC point
  hPointEta = new TH1F("hPointEta","EtaB",302,mEtaB);
  hPointPhi = new TH1F("hPointPhi","PhiB",900,mGlobalPhiB);
  hPointZ   = new TH1F("hPointZ","Z",200,-200,200);
  
  // spike check
  Hphi_eta_opp[0] = new TH2F("Hphi_eta_opp0","eta phi corr. for opp keep p",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_opp[1] = new TH2F("Hphi_eta_opp1","eta phi corr. for opp rm p",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_opp[2] = new TH2F("Hphi_eta_opp2","eta phi corr. for opp rm s hit",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_opp[3] = new TH2F("Hphi_eta_opp3","eta phi corr. for opp rm all",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_same[0] = new TH2F("Hphi_eta_same0","eta phi corr. for same keep p",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_same[1] = new TH2F("Hphi_eta_same1","eta phi corr. for same rm p",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_same[2] = new TH2F("Hphi_eta_same2","eta phi corr. for same rm s hit",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_same[3] = new TH2F("Hphi_eta_same3","eta phi corr. for same rm all",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_semi[0] = new TH2F("Hphi_eta_semi0","eta phi corr. for semi rm p",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_semi[1] = new TH2F("Hphi_eta_semi1","eta phi corr. for semi rm s hit",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_semi[2] = new TH2F("Hphi_eta_semi2","eta phi corr. for semi rm all",200,-1.0,1.0,256,-3.2,3.2);
  Hphi_eta_had = new TH2F("Hphi_eta_had","eta phi corr. for had",200,-1.0,1.0,256,-3.2,3.2);
  
  
  Hemc_eta_phi[0] = new TH2F("Hemc_eta_phi0","eta phi corr. for same",200,-1.0,1.0,256,-3.2,3.2);
  Hemc_eta_phi[1] = new TH2F("Hemc_eta_phi1","eta phi corr. for semi",200,-1.0,1.0,256,-3.2,3.2);
  Hemc_eta_phi[2] = new TH2F("Hemc_eta_phi2","eta phi corr. for semi EMC cut",200,-1.0,1.0,256,-3.2,3.2);
  
  Hsame_delpT[0] = new TH2F("Hsame_delpT0","pT corr. for same sign pT"         ,200,0,20,420,-10.5,10.5);
  Hsame_delpT[1] = new TH2F("Hsame_delpT1","pT corr. for same sign pT nHits>30",200,0,20,420,-10.5,10.5);
  
  Hsame_pTcorr[0] = new TH2F("Hsame_pTcorr0","pT corr. for same sign "         ,200,0,20,200,0,20);
  Hsame_pTcorr[1] = new TH2F("Hsame_pTcorr1","pT corr. for same sign nHits>30" ,200,0,20,200,0,20);
  
  
  
  Hphi_corr_opp_rmEMC = new TH2F("Hphi_corr_opp_rmEMC","phi corr. for opp rm same EMC Tower", 200,0,20, 256,-3.2,3.2);
  Hphi_corr_same_rmEMC = new TH2F("Hphi_corr_same_rmEMC","phi corr. for semi rm same EMC Tower", 200,0,20, 256,-3.2,3.2);
  Hphi_corr_semi_rmEMC = new TH2F("Hphi_corr_semi_rmEMC","phi corr. for semi rm same EMC Tower", 200,0,20, 256,-3.2,3.2);
  
  Hphi_corr_opp_rmEMCTPC = new TH2F("Hphi_corr_opp_rmEMCTPC","phi corr. for opp rm same EMC Tower small TPC", 200,0,20, 256,-3.2,3.2);
  Hphi_corr_same_rmEMCTPC = new TH2F("Hphi_corr_same_rmEMCTPC","phi corr. for same rm same EMC Tower small TPC", 200,0,20, 256,-3.2,3.2);
  Hphi_corr_semi_rmEMCTPC = new TH2F("Hphi_corr_semi_rmEMCTPC","phi corr. for semi rm same EMC Tower small TPC", 200,0,20, 256,-3.2,3.2);
  
  Hphi_corr_same_rmelectron = new TH2F("Hphi_corr_same_rmelectron","phi corr. for same rm same electron", 200,0,20, 256,-3.2,3.2);
  
  H_EMCtower[0] = new TH2F("H_EMCtower0","diff tower ID opp",200,0,20,10001,-5000.5,5000.5);
  H_EMCtower[1] = new TH2F("H_EMCtower1","diff tower ID same",200,0,20,10001,-5000.5,5000.5);
  H_EMCtower[2] = new TH2F("H_EMCtower2","diff tower ID semi req. small eta and phi",200,0,20,10001,-5000.5,5000.5);
  
  H_EMCmod[0] = new TH2F("H_EMCmod0","diff mod ID same",200,0,20,10001,-5000.5,5000.5);
  H_EMCmod[1] = new TH2F("H_EMCmod1","diff mod ID semi",200,0,20,10001,-5000.5,5000.5);
  H_EMCmod[2] = new TH2F("H_EMCmod2","diff mod ID semi req. small eta and phi",200,0,20,10001,-5000.5,5000.5);
  H_EMCmod[3] = new TH2F("H_EMCmod3","diff mod ID semi req. ee pair",200,0,20,10001,-5000.5,5000.5);
  
  HRad_opp[0] = new TH2F("HRad_opp_0","HRad phi and eta0 opp",200,0,20,200,-1,1);
  HRad_opp[1] = new TH2F("HRad_opp_1","HRad phi and eta1 opp",200,0,20,200,-1,1);
  HRad_opp[2] = new TH2F("HRad_opp_2","HRad phi and eta2 opp",200,0,20,200,-1,1);
  HRad_opp[3] = new TH2F("HRad_opp_3","HRad phi and eta3 opp",200,0,20,200,-1,1);
  
  HRad_same[0] = new TH2F("HRad_same_0","HRad phi and eta0 same",200,0,20,200,-1,1);
  HRad_same[1] = new TH2F("HRad_same_1","HRad phi and eta1 same",200,0,20,200,-1,1);
  HRad_same[2] = new TH2F("HRad_same_2","HRad phi and eta2 same",200,0,20,200,-1,1);
  HRad_same[3] = new TH2F("HRad_same_3","HRad phi and eta3 same",200,0,20,200,-1,1);
  HRad_same[4] = new TH2F("HRad_same_4","HRad phi and eta4 same",200,0,20,200,-1,1);
  HRad_same[5] = new TH2F("HRad_same_5","HRad phi and eta5 same",200,0,20,200,-1,1);
  
  HRad_same_nSig[0] = new TH2F("HRad_same_nSig0","HRad phi and eta0 same nSig>-1.",200,0,20,200,-1,1);
  HRad_same_nSig[1] = new TH2F("HRad_same_nSig1","HRad phi and eta1 same nSig<-1.",200,0,20,200,-1,1);
  HRad_semi_nSig[0] = new TH2F("HRad_semi_nSig0","HRad phi and eta0 semi nSig>-1.",200,0,20,200,-1,1);
  HRad_semi_nSig[1] = new TH2F("HRad_semi_nSig1","HRad phi and eta1 semi nSig<-1.",200,0,20,200,-1,1);
  HRad_semi_nSig[2] = new TH2F("HRad_semi_nSig2","HRad phi and eta0 semi nSig>-1. opp",200,0,20,200,-1,1);
  HRad_semi_nSig[3] = new TH2F("HRad_semi_nSig3","HRad phi and eta1 semi nSig>-1. same",200,0,20,200,-1,1);
  
  HRad_semi[0] = new TH2F("HRad_semi_0","HRad phi and eta0 semi",200,0,20,200,-1,1);
  HRad_semi[1] = new TH2F("HRad_semi_1","HRad phi and eta1 semi",200,0,20,200,-1,1);
  HRad_semi[2] = new TH2F("HRad_semi_2","HRad phi and eta2 semi",200,0,20,200,-1,1);
  HRad_semi[3] = new TH2F("HRad_semi_3","HRad phi and eta3 semi",200,0,20,200,-1,1);
  // end of cretate Histgrams
  
  mEmcPosition = new StEmcPosition();
  
  for(int i = 0; i < 4; i++){
    if(i == 1) continue;
    mEmcGeom[i] = StEmcGeom::getEmcGeom(detname[i].Data());         //bemc
  }
  
  
  
  //cout << "EMC rad. =" << mEmcGeom[0]->Radius() << endl;
  //cout << "SMDE rad. =" << mEmcGeom[2]->Radius() << endl;
  //cout << "SMDP rad. =" << mEmcGeom[3]->Radius() << endl;
  
  return kStOK ;
  
}


Int_t St_ehcorrelationMaker::Make( )

{ // Do each event
  
  // Get 'event' data
  
  StMuEvent* muEvent      =  mMuDstMaker->muDst()->event() ;
  
  
  
  // Cut on the number of vertices in the event.  On old tapes, no-vertex gets reported as VtxPosition=(0,0,0).
  
  if ( (muEvent->primaryVertexPosition().x() == 0) && (muEvent->primaryVertexPosition().y() == 0)
      && (muEvent->primaryVertexPosition().z() == 0) ) return kStOK ;  // Skip events that do not have a primary vertex
  
  
  cout << endl;
  cout << "================== Run ; " << muEvent->eventNumber() << " Start ============ " << endl;
  //cout <<  muEvent->eventNumber() << endl;
  
  // Get EMC Collection
  
  float maxTowerE = 0.0;
  
  StEmcCollection* mEmcCol = mMuDstMaker->muDst()->emcCollection();
  StSPtrVecEmcPoint& bEmcPoints = mEmcCol->barrelPoints();
  
  
  // Trig selection
  
  int trigID = 10;
  StMuTriggerIdCollection& trgcol = muEvent->triggerIdCollection();
  const StTriggerId& trigger = trgcol.nominal();
  if(trigger.isTrigger(117001))trigID=0; //mb
  
  if(
     trigger.isTrigger(117201) ||
     trigger.isTrigger(117821) ||
     trigger.isTrigger(127821) ||
     trigger.isTrigger(137821) ||
     trigger.isTrigger(137822)
     ){trigID=1;} //ht1
  
  
  if(
     trigger.isTrigger(117211) ||
     trigger.isTrigger(117212) ||
     trigger.isTrigger(127212) ||
     trigger.isTrigger(127213) ||
     trigger.isTrigger(137213)
     ){ trigID=2;} // ht2
  
  cout << "trigger = " << trigID << endl;
  Htrig[0]->Fill(trigID);
  //if(trigID == 10)return kStOK ;
  if(trigID != 2)return kStOK ;
  
  for(StSPtrVecEmcPointIterator point = bEmcPoints.begin(); point != bEmcPoints.end(); point++)
  {
    StPtrVecEmcCluster& towerCl = (*point)->cluster(kBarrelEmcTowerId);
    StPtrVecEmcRawHit& hits = (*towerCl.begin())->hit();
    StPtrVecEmcCluster& SMDE_Cl = (*point)->cluster(kBarrelSmdEtaStripId);
    StPtrVecEmcCluster& SMDP_Cl = (*point)->cluster(kBarrelSmdPhiStripId);
    StPtrVecEmcClusterIterator SMDE_Cl_Iter = SMDE_Cl.begin();
    StPtrVecEmcClusterIterator SMDP_Cl_Iter = SMDP_Cl.begin();
    
    if(SMDE_Cl_Iter != NULL && SMDP_Cl_Iter != NULL){
      hPointEta->Fill((*point)->position().pseudoRapidity());
      hPointPhi->Fill((*point)->position().phi());
      hPointZ->Fill((*point)->position().z());
    }
    
    for(StSPtrVecEmcRawHitIterator hit = hits.begin(); hit != hits.end(); hit++){
      if((*hit)->energy() > maxTowerE) maxTowerE = (*hit)->energy();
    }
  }
  
  cout << "maxTowerE = " << maxTowerE << endl;
  
  
  
  // ------
  
  
  int nptracks = mMuDstMaker->muDst()->numberOfPrimaryTracks();
  
  cout << "Event number " << muEvent->eventNumber() << " have " << bEmcPoints.size() << " EMC point ; "<< endl;
  
  // Do 'event' analysis based on event data
  
  double Z_vertex = muEvent->primaryVertexPosition().z();
  HVertex[0] -> Fill( Z_vertex ) ; // Make histogram of the vertex Z distribution
  
  //if(Z_vertex > 30 || Z_vertex < -40)return kStOK ;
  if(fabs(Z_vertex)>35.0)return kStOK ;
  int Z_id = int((Z_vertex+35.0)/5.0);
  
  cout << "Z_vertex = " << Z_vertex << endl;
  
  HVertex[1] -> Fill( Z_vertex ) ; // Make histogram of the vertex Z distribution
  
  Htrig[1]->Fill(trigID);
  
  Double_t bField = muEvent->eventSummary().magneticField()/10.;
  
  // set mixing array
  int seltrk = 0; // --- selected track for mixing
  float buff[250][30];
  for(int i=0; i<250; i++){
    for (int j=0; j<30; j++){
      buff[i][j]=0.0;
    }
  }
  
  // Get 'track' data, make cuts on tracks, do physics analysis, histogram results.
  
  TObjArray* tracks = mMuDstMaker->muDst()->primaryTracks() ;    // Create a TObject array containing the primary tracks
  TObjArrayIter GetTracks(tracks) ;                              // Create an iterator to step through the tracks
  
  StMuTrack* track ;                                             // Pointer to a track
  StMuTrack* gl_track;
  
  cout << "primary track loop" << endl;
  
  
  vector<int> array;
  
  while ( ( track = (StMuTrack*)GetTracks.Next() ) )             // Main loop for Iterating over tracks
  {
    
    int Num_bEMC = 0;
    
    // get associate global track
    
    gl_track = track->globalTrack();
    if(!gl_track)continue;
    
    // Get tarck information
    
    unsigned short nHits = track->nHits();
    unsigned short nHitsFit = track->nHitsFit();
    unsigned short nHitsDedx = track->nHitsDedx();
    unsigned short nHitsPoss = track->nHitsPoss();
    float nfitOverMax = (float)nHitsFit/(float)nHitsPoss;
    cout << "nfitOverMax = " << nfitOverMax << endl;
    
    short flag = track->flag();
    
    float dcaGlobal = track->dcaGlobal().mag();
    float eta = track->eta();
    float phi= track->phi();
    phi = atan2(sin(phi),cos(phi));
    float pT= track->pt();
    float dEdx = track->dEdx();
    float val_dEdx = dEdx*1e6 ;
    float chi2 = track->chi2();
    float mom = track->p().mag();  // need check
    float length = track->lengthMeasured();
    float nSigma = track->nSigmaElectron();
    //cout << "E =  " << length*dEdx << endl;
    cout <<"track key : promary = " <<track->id() << " ,global : "<< gl_track->id() << endl;
    //histogram[1] -> Fill(dcaGlobal);
    
    // check momentum
    
    float g_momx_0 = gl_track->p().x();
    float g_momy_0 = gl_track->p().y();
    float g_momz_0 = gl_track->p().z();
    float g_mom_0 = sqrt(pow(g_momx_0,2)+pow(g_momy_0,2)+pow(g_momz_0,2));
    float g_momx_1 = gl_track->helix().momentum(bField*tesla).x();
    float g_momy_1 = gl_track->helix().momentum(bField*tesla).y();
    float g_momz_1 = gl_track->helix().momentum(bField*tesla).z();
    float g_mom_1 = sqrt(pow(g_momx_1,2)+pow(g_momy_1,2)+pow(g_momz_1,2));
    
    float pID = -99.9; // -99.9 --- not electron / 1 = electron
    float trig_on = -99.9; // not trigger / 1 = trigger
    float phi_at_EMC = -99.9;
    float eta_at_EMC = -99.9;
    float EMCtowerID = -9999.9;
    float EMCmodID = -9999.9;
    int Nelectron = 0;
    //------------------------- associate particle cuts ----------------
    
    if(flag<=0)continue;
    
    HnfitOverMax_check->Fill(nfitOverMax);
    Hchi_check->Fill(chi2);
    
    if(dcaGlobal > 0.0 && dcaGlobal < 3.0
       && nHitsFit > 15 && nHitsFit < 50
       && fabs(eta)<1.05
       && nfitOverMax > 0.52 && nfitOverMax < 1.2
       && pT>0.3
       )
    {
      // make ass track histo
      
      Hass_pT->Fill(pT);
      
      //---------------------- start trigger selection ------------------------------------------------//
      
      if(dcaGlobal > 0.0 && dcaGlobal < 1.5
         && nHitsDedx > 15 && nHitsDedx < 50
         && chi2 > 0.0 && chi2 < 3.0
         && fabs(eta)<0.7)
      {
        trig_on = 1.0;
        
        HdcaGlobal_check->Fill(dcaGlobal);
        HnHits_check->Fill(nHits);
        HnHitsdEdx_check->Fill(nHitsDedx);
        //Hchi_check->Fill(chi2);
        Hflag_check->Fill(flag);
        //HnfitOverMax_check->Fill(nfitOverMax);
        Heta_check[0]->Fill(eta);
        
        HpT[0] -> Fill( track->pt() ) ;
        HpT_dEdx[0] -> Fill( pT, val_dEdx ) ;
        
        //--------------------- start electron ID with BEMC ---------------------------------------------//
        
        StThreeVectorD posEMC, momEMC;
        bool projEMC = mEmcPosition->trackOnEmc(&posEMC,&momEMC,track,bField,mEmcGeom[0]->Radius());
        float EMC_x = posEMC.x();
        float EMC_y = posEMC.y();
        float EMC_pT = sqrt(pow(momEMC.x(),2)+pow(momEMC.y(),2));
        float EMC_phi = posEMC.phi();
        float EMC_eta = posEMC.pseudoRapidity();
        int moduleH, etaH, subH, EMCTid;
        mEmcGeom[0]->getBin(posEMC.phi(), posEMC.pseudoRapidity(), moduleH, etaH, subH);
        mEmcGeom[0]->getId(moduleH, etaH, subH, EMCTid);
        EMCtowerID = (float)EMCTid;
        EMCmodID   = (float)moduleH;
        cout << "softID = " << EMCTid << " : " << EMCtowerID << " ; Module = "<< moduleH << endl;
        
        StThreeVectorD posSMDE, momSMDE;
        bool projSMDE = mEmcPosition->trackOnEmc(&posSMDE,&momSMDE,track,bField,mEmcGeom[2]->Radius());
        float SMDE_x = posSMDE.x();
        float SMDE_y = posSMDE.y();
        float SMDE_eta = posSMDE.pseudoRapidity();
        
        StThreeVectorD posSMDP, momSMDP;
        bool projSMDP = mEmcPosition->trackOnEmc(&posSMDP,&momSMDP,track,bField,mEmcGeom[3]->Radius());
        float SMDP_x = posSMDP.x();
        float SMDP_y = posSMDP.y();
        float SMDP_phi = posSMDP.phi();
        float SMDP_z = posSMDP.z();
        SMDP_phi = atan2(sin(SMDP_phi),cos(SMDP_phi));
        
        cout << "check assosication tarck " << track->id() << " ; "<< projEMC << " ; " << projSMDE << " ; " << projSMDP << endl;
        cout << "phi =" << phi << " ; EMC_phi = " << EMC_phi << endl;
        cout << "eta =" << eta << " ; EMC_eta = " << EMC_eta << endl;
        
        phi_at_EMC = EMC_phi;
        eta_at_EMC = EMC_eta;
        
        int Num_match = 0;
        float r_keep = 9999;
        
        
        if(projEMC && projSMDE && projSMDP)   //projection point on the EMC & SMD && eta cuts request
        {
          int EmcID = 0;
          for(StSPtrVecEmcPointIterator point = bEmcPoints.begin(); point != bEmcPoints.end(); point++) // find associate point of EMC
          {
            Num_bEMC = Num_bEMC + 1;
            EmcID++;
            
            float bemc_phi = (*point)->position().phi();
            float bemc_eta = (*point)->position().pseudoRapidity();
            float bemc_z = (*point)->position().z();
            
            float dis_phi = bemc_phi - SMDP_phi;
            dis_phi = atan2(sin(dis_phi),cos(dis_phi));
            float dis_z   = bemc_z   - SMDP_z;
            float dis_eta = bemc_eta - posSMDE.pseudoRapidity();
            
            float EMC_r = mEmcGeom[0]->Radius();
            float dis_0 = sqrt(pow((EMC_r*cos(0.05) - EMC_r),2)+pow((EMC_r*sin(0.05)),2));
            float EMC_x_asso = EMC_r*cos(bemc_phi);
            float EMC_y_asso = EMC_r*sin(bemc_phi);
            float dis_1 = sqrt(pow((EMC_x_asso-EMC_x) ,2)+pow((EMC_y_asso-EMC_y),2));
            
            //point match
            float track_match_phi = phi - bemc_phi;
            track_match_phi = atan2(sin(track_match_phi),cos(track_match_phi));
            float track_match_eta = phi - bemc_eta;
            //org. hit match
            float track_match_phi_org = phi - SMDP_phi;
            track_match_phi_org = atan2(sin(track_match_phi_org),cos(track_match_phi_org));
            float track_match_eta_org = phi - posSMDE.pseudoRapidity();
            
            
            //cout << "point addrees = " << point << endl;
            //cout << "assoc_phi = " << bemc_phi << " ; proj_phi = " << EMC_phi << " ; sub = " << dis_phi << endl;
            //cout << " dis_0 = " << dis_0 << " ; dis_1 = " << dis_1 << endl;
            //if( dis_1 < dis_0) cout << "Distance match" << endl;
            //cout << "dis_eta = " << dis_eta << endl;
            
            
            float r = sqrt(pow(dis_eta,2)+pow(dis_phi,2));
            
            if(r<0.05)
              //if(fabs(dis_phi) < 0.05 && fabs(dis_eta) < 0.05)
            {
              
              //if(dis_1 < dis_0 && fabs(dis_eta) < 0.05){
              Num_match = Num_match + 1;
              cout << "matching "<< Num_match<< endl;
              
              if(Num_match>1 && r_keep>r)break;
              cout << "seltrk = " << seltrk << "  EmcID = " << EmcID << " r = " << r << endl;
              
              vector<int>::iterator emcit = array.begin();
              array.push_back(EmcID);
              
              H_dis_phi->Fill(pT,dis_phi);
              H_dis_eta->Fill(pT,dis_eta);
              
              H_dis_phi_TPC->Fill(pT,track_match_phi);
              H_dis_eta_TPC->Fill(pT,track_match_eta);
              
              H_phi_TPC_EMC->Fill(phi,bemc_phi);
              H_eta_TPC_EMC->Fill(eta,bemc_eta);
              
              H_dis_phi_TPC_org->Fill(pT,track_match_phi_org);
              H_dis_eta_TPC_org->Fill(pT,track_match_eta_org);
              
              H_TPC_EMC_match->Fill(Num_match);
              
              HpT[1]->Fill(pT);
              
              //cout << endl;
              
              //cout << "start R cut" << endl;
              // association TPC track and EMC
              
              //cout << "Get energy " << endl;
              
              float energy = (*point)->energy(); // need check
              //float eop = energy/mom;
              float eop = mom/energy; // not E/p
              
              //cout << "Get EMC , SMDE , SMDP cluster " << endl;
              
              StPtrVecEmcCluster& BEMC_Cl = (*point)->cluster(kBarrelEmcTowerId);
              StPtrVecEmcCluster& SMDE_Cl = (*point)->cluster(kBarrelSmdEtaStripId);
              StPtrVecEmcCluster& SMDP_Cl = (*point)->cluster(kBarrelSmdPhiStripId);
              
              //cout << "Get EMC , SMDE , SMDP cluster first point" << endl;
              
              StPtrVecEmcClusterIterator SMDE_Cl_Iter = SMDE_Cl.begin();
              StPtrVecEmcClusterIterator SMDP_Cl_Iter = SMDP_Cl.begin();
              
              //cout << "Get EMC , SMDE , SMDP cluster hit point" << endl;
              //cout << "address of SMDE_Cl_Iter =" << SMDE_Cl_Iter << endl;
              //cout << "address of SMDP_Cl_Iter =" << SMDP_Cl_Iter << endl;
              
              if(SMDE_Cl_Iter == NULL) continue;
              if(SMDP_Cl_Iter == NULL) continue;
              
              int neta = (*SMDE_Cl_Iter)->nHits();
              int nphi = (*SMDP_Cl_Iter)->nHits();
              
              //cout <<" neta = " << neta << " ; nphi = " << nphi <<endl;
              
              Hnhit_corr -> Fill (neta , nphi);
              
              Heop[0] -> Fill (eop);
              
              float dis_phi_R = dis_phi * (mEmcGeom[2]->Radius());
              
              if(neta > 1 &&
                 nphi > 1 )
              {
                Heop[1] -> Fill (eop);
                HpT_dEdx[1] -> Fill(pT,val_dEdx) ;
                Hep_corr -> Fill(mom,energy) ;
                HpT[2]->Fill(pT);
                Heop_dEdx->Fill(eop,val_dEdx);
                
                if(eop>0.3 && eop<1.5)
                {
                  HpT_dEdx[2] -> Fill(pT,val_dEdx) ;
                  HpT_dEdx_trig -> Fill(pT,val_dEdx) ;
                  
                  Hnsig_e[0]->Fill(pT,nSigma);
                  
                  float mim_dEdx = 3.436;
                  
                  //if(val_dEdx > 3.38 && val_dEdx< 4.45)
                  //if(val_dEdx > mim_dEdx && val_dEdx< 4.5) // -0.5 sig - 3.0 sig
                  if(nSigma>-1.0 && nSigma<3.0) // -0.5 sig - 3.0 sig
                  {
                    pID = 1.0;
                    
                    Nelectron = Nelectron+1;
                    if(Nelectron==1)
                    {
                      HpT[3]->Fill(pT);
                      HpT_dEdx[3] -> Fill(pT,val_dEdx);
                    }
                    //Hele_Z->Fill(Z_vertex);
                  }
                  
                  //cout << "dEdx = " << val_dEdx << "pID = " << pID << endl;
                  
                }
              }
              //cout << "Get EMC , SMDE , SMDP cluster hit point done" << endl;
            }
            //cout <<" =========- end of matching ============ " << endl;
          }
          //cout <<" ========== end of bEMC loop ============ "<< endl;
        }
        cout <<" ========== end of projEMC =============== " << endl;
        //cout << "number of Barrel = " << Num_bEMC << endl;
      } // end of trigger particle selctions
      
      if(seltrk < 250)
      {
        buff[seltrk][0] = pID;
        buff[seltrk][1] = pT;
        buff[seltrk][2] = track->p().x();
        buff[seltrk][3] = track->p().y();
        buff[seltrk][4] = track->p().z();
        buff[seltrk][5] = track->charge();
        buff[seltrk][6] = phi;
        buff[seltrk][7] = mom;
        buff[seltrk][8] = gl_track->helix().momentum(bField*tesla).x();  // get momentum at helix original point
        buff[seltrk][9] = gl_track->helix().momentum(bField*tesla).y();
        buff[seltrk][10] = gl_track->helix().momentum(bField*tesla).z();
        buff[seltrk][11] = gl_track->helix().origin().x();      // get point of helix
        buff[seltrk][12] = gl_track->helix().origin().y();
        buff[seltrk][13] = gl_track->helix().origin().z();
        buff[seltrk][14] = gl_track->id();
        buff[seltrk][15] = gl_track->p().mag();
        buff[seltrk][18] = eta;
        buff[seltrk][19] = val_dEdx;
        buff[seltrk][20] = trig_on;
        buff[seltrk][21] = nSigma;
        buff[seltrk][22] = nHits;
        buff[seltrk][23] = phi_at_EMC;
        buff[seltrk][24] = eta_at_EMC;
        buff[seltrk][25] = EMCtowerID;
        buff[seltrk][26] = EMCmodID;
        cout << "softID ch = " << buff[seltrk][25] << endl;
        
      }else{
        Hover->Fill(1);
      }
      
      //cout << "current seltrk is " << seltrk << endl;
      
      seltrk++;
    }
    
  }  // while
  // cout <<"  ======== end of Track loop ============ " << endl;
  
  
  Hseltrk->Fill(seltrk);
  
  //int mixloop = seltrk - 1;
  int mixloop = seltrk;
  //if(seltrk>100) mixloop = 100;
  
  
  //================================= Cal. electron Inv. mass ===============
  
  TObjArray* gtracks = mMuDstMaker->muDst()->globalTracks() ;    // Create a TObject array containing the primary tracks
  TObjArrayIter GetglTracks(gtracks) ;                              // Create an iterator to step through the tracks
  
  StMuTrack* gtrack ;                                             // Pointer to a track
  
  for(int itrk=0; itrk<mixloop; itrk++) // primary electrn track
  {
    if(buff[itrk][0]!=1.0)continue; // remove hadron (electron is buff[i][0]==1.0)
    if(fabs(buff[itrk][18])>0.7)continue; // trigger e ; eta is less than 0.7
    if(buff[itrk][20]!=1.0)continue; // remove not trigger particle
    
    int ecount_opp = 0;
    int ecount_same = 0;
    double invmass_keep = -9999;
    
    // make tag electron helix
    StThreeVectorD PGlobal1(buff[itrk][8],buff[itrk][9],buff[itrk][10]);
    StThreeVectorD OGlobal1(buff[itrk][11],buff[itrk][12],buff[itrk][13]);
    StPhysicalHelixD helix1(PGlobal1,OGlobal1,bField*tesla,buff[itrk][5]);
    
    while ( ( gtrack = (StMuTrack*)GetglTracks.Next() ) )  // find pair electron in global track
    {
      
      unsigned short nHits = gtrack->nHits();
      unsigned short nHitsFit = gtrack->nHitsFit();
      unsigned short nHitsDedx = gtrack->nHitsDedx();
      unsigned short nHitsPoss = gtrack->nHitsPoss();
      float nfitOverMax = (float)nHitsFit/(float)nHitsPoss;
      
      int gtype = gtrack->type();
      float eta = gtrack->eta();
      float pT = gtrack->pt();
      float gnsig_e = gtrack->nSigmaElectron();
      float chi2 = gtrack->chi2();
      int gid = gtrack->id();
      
      /*  cout << endl;
       cout << "track type = " << gtype << endl;
       cout << "nsig. ele = "  << gnsig_e << endl; */
      
      
      //if(fabs(gnsig_e)>3.0)continue;
      //if(fabs(eta)>0.7)continue;
      //if(nHits<=20 && nHits>=50)continue;
      //if(nHitsDedx<=15 && nHitsDedx>=100)continue;
      //if(chi2<=0 && chi2>=3)continue;
      
      //cout << "pair nhits =" << nHits << endl;
      
      if(fabs(gnsig_e) < 3.0
         && nHitsFit > 15 && nHitsFit < 50
         && nHitsDedx > 15 && nHitsDedx < 50
         && chi2 > 0.0 && chi2 < 3.0
         && fabs(eta)<1.05
         && nfitOverMax > 0.52 && nfitOverMax < 1.2
         && pT>0.1)
      {
        //cout << "track "  << gid << " is electron candidtae "<< endl;
        //cout << "pair nhits cut =" << nHits << endl;
        
        HnHits_check_pair->Fill(nHits);
        HnHitsdEdx_check_pair->Fill(nHitsDedx);
        Hchi_check_pair->Fill(chi2);
        Heta_check_pair->Fill(eta);
        
        float p_charge = gtrack->charge();
        float p_px = gtrack->helix().momentum(bField*tesla).x();  //p_ mean pair
        float p_py = gtrack->helix().momentum(bField*tesla).y();
        float p_pz = gtrack->helix().momentum(bField*tesla).z();
        float p_ox = gtrack->helix().origin().x();
        float p_oy = gtrack->helix().origin().y();
        float p_oz = gtrack->helix().origin().z();
        
        float sign = p_charge * buff[itrk][5];
        int signID = 0; // opp
        if(sign>0)signID = 1; // same
        /*
         cout << endl;
         cout << "tag e c = " << buff[itrk][5] << "; pair e x = " << p_charge << " ;sign = " << sign
         << "; sign ID = " << signID <<endl;
         */
        
        if(buff[itrk][14] == gid)
        {
          /*
           cout << endl;
           cout << "same track " << endl;
           cout << "check momx " << p_px<< " ; " << buff[itrk][8] << endl;
           cout << "check momy " << p_py<< " ; " << buff[itrk][9] << endl;
           cout << "check orgx " << p_ox<< " ; " << buff[itrk][11] << endl;
           */
          continue;
        }
        
        // make pair electron helix
        StThreeVectorD PGlobal2(p_px,p_py,p_pz);
        StThreeVectorD OGlobal2(p_ox,p_oy,p_oz);
        StPhysicalHelixD helix2(PGlobal2,OGlobal2,bField*tesla,p_charge);
        
        // cal DCA of two tracks
        pair<double,double> pathLength(helix1.pathLengths(helix2).first, helix1.pathLengths(helix2).second);
        
        float DCAlength = abs(helix1.at(pathLength.first) - helix2.at(pathLength.second));
        //float DCAlength_mag = (helix1.at(pathLength.first) - helix2.at(pathLength.second)).mag(); // mag() --- same as abs()
        
        // get momentum at DCA of two track
        
        StThreeVectorD mom1_DCA = helix1.momentumAt(pathLength.first,  bField*tesla);
        StThreeVectorD mom2_DCA = helix2.momentumAt(pathLength.second, bField*tesla);
        /*
         cout << endl;
         cout << "check total momentum at DCA" << endl;
         */
        float tot_mom1 = sqrt(pow(mom1_DCA.x(),2)+pow(mom1_DCA.y(),2)+pow(mom1_DCA.z(),2));
        float tot_mom2 = sqrt(pow(mom2_DCA.x(),2)+pow(mom2_DCA.y(),2)+pow(mom2_DCA.z(),2));
        /*
         cout << "helix1(tag e) mom ; " << tot_mom1 << " ; " << buff[itrk][15] << endl;
         cout << "helix2(pair e) mom ; " << tot_mom2 << " ; " << gtrack->p().mag() << endl;
         */
        // cal Inv. mass of two particles
        
        const double me = 0.00051099906;	//mass of e
        
        StLorentzVectorD Four1, Four2;
        Four1.setPx(mom1_DCA.x());
        Four1.setPy(mom1_DCA.y());
        Four1.setPz(mom1_DCA.z());
        Four1.setE(mom1_DCA.massHypothesis(me));
        
        Four2.setPx(mom2_DCA.x());
        Four2.setPy(mom2_DCA.y());
        Four2.setPz(mom2_DCA.z());
        Four2.setE(mom2_DCA.massHypothesis(me));
        
        double invmass = (Four1+Four2).m();
        /*
         cout << endl;
         cout << "Invmass = " << invmass << endl;
         */
        
        // cal phi and theta
        float open_phi = Four1.phi() - Four2.phi();
        float open_theta = Four1.theta() - Four2.theta();
        
        // <----- check phi
        Four1.setPz(0);
        Four2.setPz(0);
        float open_phi2 = Four1.phi() - Four2.phi();
        /*
         cout << endl;
         cout << "check phi ; meth1 = " << open_phi << " ; meth2 = " << open_phi2 << endl;
         */
        
        // cal 2D inv mass
        Four1.setPx(sqrt(pow(mom1_DCA.x(),2)+pow(mom1_DCA.y(),2)));
        Four1.setPy(0.);
        Four1.setPz(mom1_DCA.z());
        
        Four2.setPx(sqrt(pow(mom2_DCA.x(),2)+pow(mom2_DCA.y(),2)));
        Four2.setPy(0.);
        Four2.setPz(mom2_DCA.z());
        
        double invmass2D = (Four1+Four2).m();
        
        double invmass2D_class = Cal_Invmass(helix1,helix2,bField);
        cout << "Inv mass = " << invmass2D << " ; " << invmass2D_class << endl;
        
        // <----- check theta
        float open_theta2 = Four1.theta() - Four2.theta();
        /*
         cout << endl;
         cout << "check theta ; meth1 = " << open_theta << " ; meth2 = " << open_theta2 << endl;
         */
        // cal opening angle
        Float_t norm = sqrt(mom1_DCA.mag2()*mom2_DCA.mag2());
        Float_t dot = mom1_DCA.x()*mom2_DCA.x()+mom1_DCA.y()*mom2_DCA.y()+mom1_DCA.z()*mom2_DCA.z();
        float pairAngle;
        if(norm > 0) pairAngle = acos(dot/norm);
        
        //<------- check open angle
        /*
         cout << endl;
         cout << "open angle = " << pairAngle << endl;
         */
        Hopenphi[signID] -> Fill(open_phi);
        Hopentheta[signID] -> Fill(open_theta);
        Hopenangle[signID] -> Fill(pairAngle);
        HDCA[signID] -> Fill(DCAlength);
        
        Hopenphi_pT[signID] -> Fill(buff[itrk][1],open_phi);
        Hopentheta_pT[signID] -> Fill(buff[itrk][1],open_theta);
        Hopenangle_pT[signID] -> Fill(buff[itrk][1],pairAngle);
        HDCA_pT[signID] -> Fill(buff[itrk][1],DCAlength);
        
        //
        Hinvmass_wocut[signID]->Fill(buff[itrk][1],invmass2D);
        //
        
        if(DCAlength<1.0 &&
           fabs(open_phi)<0.1 &&
           fabs(open_theta)<0.05 &&
           fabs(pairAngle)<0.15
           ){
          Hinvmass[signID]->Fill(buff[itrk][1],invmass2D);
          /*
           cout << endl;
           cout << "org eID = " << buff[itrk][0] << endl;
           */
          
          //--------- check electrons ---------------
          
          if(invmass2D<0.1 && signID==0)ecount_opp = ecount_opp+1;
          if(invmass2D<0.1 && signID==1)ecount_same = ecount_same+1;
          
          //cout << "invmass = " << invmass2D << " ; signID = " << signID << " : ecount_same = " << ecount_same << endl;
          //cout << "invmass = " << invmass2D << " ; signID = " << signID << " : ecount_opp = " << ecount_opp << endl;
          
          //-----------------------------------------
          
          //if(invmass   < 0.1 && buff[itrk][0]>=2.0)Hcheck_pair[0]->Fill(buff[itrk][0]);
          if(invmass2D < 0.1 && buff[itrk][0]>=2.0)Hcheck_pair->Fill(buff[itrk][1],buff[itrk][0]);
          
          if(invmass2D < 0.1 && signID==0)
          {
            Hinvmass_pT_Opp->Fill(buff[itrk][1],invmass2D);
            buff[itrk][16] = 1.0;  // oppsign
            invmass_keep = invmass2D;
            /*
             cout << endl;
             cout << "invmass = " << invmass << " ; sign =" << sign << " ; e tag = " << buff[itrk][0] << endl;
             */
          }
          
          if(invmass2D < 0.1 && signID==1)
          {
            Hinvmass_pT_Same->Fill(buff[itrk][1],invmass2D);
            buff[itrk][17] = 1.0;  // samesign
            /*
             cout << endl;
             cout << "invmass = " << invmass << " ; sign =" << sign << " ; e tag = " << buff[itrk][0] << endl;
             */
          }
          
          for(int atrk=0; atrk<mixloop; atrk++)  // make photonic e-h
          {
            if(itrk==atrk)continue; // remove myself
            if(buff[atrk][1]<0.3)continue;
            
            float phi_corr = buff[itrk][6] - buff[atrk][6];
            phi_corr = atan2(sin(phi_corr),cos(phi_corr));
            float eta_corr = buff[itrk][18] - buff[atrk][18];
            float R_corr = sqrt(pow(phi_corr,2)+pow(eta_corr,2));
            float pT_corr = buff[itrk][1] - buff[atrk][1];
            
            float phi_corr_emc = buff[itrk][23] - buff[atrk][23];
            phi_corr_emc = atan2(sin(phi_corr_emc),cos(phi_corr_emc));
            float eta_corr_emc = buff[itrk][24] - buff[atrk][24];
            
            float diff_EMCid = buff[itrk][25] - buff[atrk][25];
            float diff_EMCmodid = buff[itrk][26] - buff[atrk][26];
            
            
            if(invmass2D<0.1)
            {
              
              //if(buff[atrk][14]==gid && ecount_opp==1 && signID==0) // tag pair photonic electron
              if(buff[atrk][14]==gid && signID==0) // tag pair photonic electron
              {
                HpID_check_pair->Fill(buff[itrk][1],buff[atrk][0]);
                buff[atrk][27] = 1.0; // photonic electron pair (not need EMC electron (may be hadron))
              }
              //if(buff[atrk][14]==gid && ecount_same==1 && signID==1) // tag pair same sign electron
              if(buff[atrk][14]==gid && signID==1) // tag pair same sign electron
              {
                buff[atrk][28] = 1.0; // same sign electron pair (not need EMC electron (may be hadron))
              }
              
              
              
              /*
               if(buff[atrk][1]>=0.5)
               {
               // keep partner
               if(signID==0 && ecount_opp==1)Hphi_corr_we[0][4] -> Fill(buff[itrk][1],phi_corr); // opp sign partner
               if(signID==1 && ecount_same==1)Hphi_corr_we[0][5] -> Fill(buff[itrk][1],phi_corr); // same sign partner
               // reject partner
               if(gid == buff[atrk][14])continue;  // reject partner electron
               if(signID==0 && ecount_opp==1)Hphi_corr_we[0][6] -> Fill(buff[itrk][1],phi_corr); // opp sign no partner
               if(signID==1 && ecount_same==1)Hphi_corr_we[0][7] -> Fill(buff[itrk][1],phi_corr); // same sign no partner
               }
               
               if(buff[atrk][1]>=0.4)
               {
               // keep partner
               if(signID==0 && ecount_opp==1)Hphi_corr_we[1][4] -> Fill(buff[itrk][1],phi_corr); // opp sign partner
               if(signID==1 && ecount_same==1)Hphi_corr_we[1][5] -> Fill(buff[itrk][1],phi_corr); // same sign partner
               // reject partner
               if(gid == buff[atrk][14])continue;  // reject partner electron
               if(signID==0 && ecount_opp==1)Hphi_corr_we[1][6] -> Fill(buff[itrk][1],phi_corr); // opp sign no partner
               if(signID==1 && ecount_same==1)Hphi_corr_we[1][7] -> Fill(buff[itrk][1],phi_corr); // same sign no partner
               }
               */
              // keep partner
              if(signID==0 && ecount_opp==1)
              {
                Hphi_corr_we[2][4] -> Fill(buff[itrk][1],phi_corr); // opp sign partner
                HRad_opp[0]->Fill(buff[itrk][1],R_corr);
                if(buff[itrk][1]>5.5)Hphi_eta_opp[0]-> Fill(eta_corr,phi_corr); // delta phi & eta
              }
              
              if(signID==1 && ecount_same==1)
              {
                Hphi_corr_we[2][5] -> Fill(buff[itrk][1],phi_corr); // same sign partner
                HRad_same[0]->Fill(buff[itrk][1],R_corr);
                if(buff[itrk][1]>5.5)Hphi_eta_same[0]-> Fill(eta_corr,phi_corr); // delta phi & eta
              }
              
              // reject partner
              //if(gid == buff[atrk][14])continue;  // reject partner electron
              
              //if(signID==0 && ecount_opp==1)
              if(signID==0 && ecount_opp==1 && buff[atrk][14]!=gid)
              {
                Hphi_corr_we[2][6] -> Fill(buff[itrk][1],phi_corr); // opp sign no partner
                HRad_opp[1]->Fill(buff[itrk][1],R_corr);
                H_EMCtower[0] -> Fill(buff[itrk][1],diff_EMCid);
                if(buff[itrk][1]>5.5)Hemc_eta_phi[0]->Fill(eta_corr_emc,phi_corr_emc);
                if(buff[itrk][1]>5.5)Hphi_eta_opp[1]-> Fill(eta_corr,phi_corr); // delta phi & eta
                if(R_corr<0.05)HpID[0]->Fill(buff[itrk][1],buff[atrk][0]);
                if(R_corr<0.05)HnSig[0]->Fill(buff[itrk][1],buff[atrk][21]);
                
                if(buff[itrk][25]!=buff[atrk][25])
                {
                  HRad_opp[2]->Fill(buff[itrk][1],R_corr);
                  Hphi_corr_opp_rmEMC->Fill(buff[itrk][1],phi_corr);
                  if(buff[itrk][1]>5.5)Hphi_eta_opp[2]-> Fill(eta_corr,phi_corr); // delta phi & eta
                }
                
                if(buff[itrk][25]!=buff[atrk][25] &&
                   R_corr>0.05)
                {
                  HRad_opp[3]->Fill(buff[itrk][1],R_corr);
                  Hphi_corr_opp_rmEMCTPC->Fill(buff[itrk][1],phi_corr);
                  if(buff[itrk][1]>5.5)Hphi_eta_opp[3]-> Fill(eta_corr,phi_corr); // delta phi & eta
                }
              }
              
              //if(signID==1 && ecount_same==1)
              if(signID==1 && ecount_same==1 && buff[atrk][14]!=gid)
              {
                Hphi_corr_we[2][7] -> Fill(buff[itrk][1],phi_corr); // same sign no partner
                HRad_same[1]->Fill(buff[itrk][1],R_corr);
                H_EMCtower[1] -> Fill(buff[itrk][1],diff_EMCid);
                if(buff[itrk][1]>5.5)Hemc_eta_phi[1]->Fill(eta_corr_emc,phi_corr_emc);
                if(buff[itrk][1]>5.5)Hphi_eta_same[1]-> Fill(eta_corr,phi_corr); // delta phi & eta
                if(R_corr<0.05)HpID[1]->Fill(buff[itrk][1],buff[atrk][0]);
                if(R_corr<0.05)HnSig[1]->Fill(buff[itrk][1],buff[atrk][21]);
                if(buff[atrk][21]>-1.0)HRad_same_nSig[0]->Fill(buff[itrk][1],R_corr);
                if(buff[atrk][21]<-1.0)HRad_same_nSig[1]->Fill(buff[itrk][1],R_corr);
                
                if(buff[itrk][25]!=buff[atrk][25])
                {
                  HRad_same[2]->Fill(buff[itrk][1],R_corr);
                  Hphi_corr_same_rmEMC->Fill(buff[itrk][1],phi_corr);
                  if(buff[itrk][1]>5.5)Hphi_eta_same[2]-> Fill(eta_corr,phi_corr); // delta phi & eta
                }
                
                if(buff[itrk][25]!=buff[atrk][25] &&
                   R_corr>0.05)
                {
                  HRad_same[3]->Fill(buff[itrk][1],R_corr);
                  Hphi_corr_same_rmEMCTPC->Fill(buff[itrk][1],phi_corr);
                  if(buff[itrk][1]>5.5)Hphi_eta_same[3]-> Fill(eta_corr,phi_corr); // delta phi & eta
                }
                
                if(buff[atrk][0]!=1.0)
                {
                  HRad_same[4]->Fill(buff[itrk][1],R_corr);
                  Hphi_corr_same_rmelectron->Fill(buff[itrk][1],phi_corr);
                }
                
              }
              
              
              //(2) momentum
              if(signID==1 && ecount_same==1 && fabs(eta_corr)<0.05 && fabs(phi_corr)<0.05)
              {
                Hsame_delpT[0]->Fill(buff[itrk][1],pT_corr);
                Hsame_pTcorr[0]->Fill(buff[itrk][1],buff[atrk][1]);
                
                if(buff[itrk][22]>30 && buff[atrk][22]>30)
                {
                  Hsame_delpT[1]->Fill(buff[itrk][1],pT_corr);
                  Hsame_pTcorr[1]->Fill(buff[itrk][1],buff[atrk][1]);
                }
              }
              // end of spritting study ********************
              
            }
            //Hphi_corr_we[trigID][10] -> Fill(buff[itrk][1],phi_corr); // inclusive check
          }
          
          
          /*   cout << "current eID = " << buff[itrk][0] << endl; */
          
        }
        
      } // end gtrak cuts
      
    } // end of pair loop (while)
    
    if(buff[itrk][0]==1.0) HpT_pho[0]->Fill(buff[itrk][1]);  // inclusive
    if(buff[itrk][0]==1.0) Hele_Z->Fill(Z_vertex);
    if(buff[itrk][0]==1.0 && buff[itrk][16]==1.0)HpT_pho[1]->Fill(buff[itrk][1]);  // opp sign
    if(buff[itrk][0]==1.0 && buff[itrk][16]==1.0)Hpho_Z->Fill(Z_vertex);  // opp sign
    if(buff[itrk][0]==1.0 && buff[itrk][17]==1.0)HpT_pho[2]->Fill(buff[itrk][1]);  // same sign
    HpT_pho[3]->Fill(buff[itrk][1]);
    
    if(buff[itrk][0]==1.0 && buff[itrk][16]!=1.0) // semi-inc
    {
      HpT_pho[4]->Fill(buff[itrk][1]);
      HdEdx_semi->Fill(buff[itrk][1],buff[itrk][19]);
    }
    
    if(buff[itrk][0]==1.0 && buff[itrk][16]==1.0 && invmass_keep>=0 && invmass_keep<=0.05)Hnsig_e[1]->Fill(buff[itrk][1],buff[itrk][21]);  // opp sign
    if(buff[itrk][0]==1.0 && buff[itrk][16]==1.0 && invmass_keep>=0 && invmass_keep<=0.1) Hnsig_e[2]->Fill(buff[itrk][1],buff[itrk][21]);  // opp sign
    
    Hpair[0]->Fill(ecount_opp);
    Hpair[1]->Fill(ecount_same);
    
    
  } // end of electron loop (for itrk)
  
  //========================== mixing (e-h correlation) ================================
  
  if(mixloop>1)
  {
    cout << "mixing start"<<endl;
    
    for(int i=0; i<mixloop; i++)
    {
      cout << "mixloop = " << mixloop << endl;
      cout << "mixloop gid = " << buff[i][14] << endl;
      
      int N_notreco_opp = 0;
      int N_notreco_sam = 0;
      
      int num_ass = 0;
      
      if(buff[i][0] > 0.0
         && fabs(buff[i][18])<0.7 //select trigger ===> electron && eta < 0.7
         && buff[i][20]==1.0)
      {
        Heta_check[1]->Fill(buff[i][18]);
        /*
         cout << endl;
         cout << "=== cal correlation === " <<  endl;
         cout << "eID =  " << buff[i][0] << endl;
         */
        
        
        // make tag electron helix
        StThreeVectorD PGlobal1(buff[i][8],buff[i][9],buff[i][10]);
        StThreeVectorD OGlobal1(buff[i][11],buff[i][12],buff[i][13]);
        StPhysicalHelixD helix1(PGlobal1,OGlobal1,bField*tesla,buff[i][5]);
        
        
        for(int j=0; j<mixloop; j++)
        {
          if(i!=j) // remove same track
          {
            if(buff[j][1]<0.3)continue;
            int addcut = 0;
            
            // make associate  helix
            StThreeVectorD PGlobal2(buff[j][8],buff[j][9],buff[j][10]);
            StThreeVectorD OGlobal2(buff[j][11],buff[j][12],buff[j][13]);
            StPhysicalHelixD helix2(PGlobal2,OGlobal2,bField*tesla,buff[j][5]);
            double invmass2D_notreco = Cal_Invmass(helix1,helix2,bField);
            
            
            Heta_check[2]->Fill(buff[j][18]);
            
            num_ass = num_ass+1;
            
            if(trigID==2 && num_ass==1)
            {
              HpT_check[0]->Fill(buff[i][1]);
              if(buff[i][16]==1.0)HpT_check[1]->Fill(buff[i][1]);
              if(buff[i][17]==1.0)HpT_check[2]->Fill(buff[i][1]);
              if(buff[i][16]!=1.0)HpT_check[3]->Fill(buff[i][1]);
            }
            
            
            float phi_corr = buff[i][6] - buff[j][6];
            phi_corr = atan2(sin(phi_corr),cos(phi_corr));
            float eta_corr = buff[i][18] - buff[j][18];
            float R_corr = sqrt(pow(phi_corr,2)+pow(eta_corr,2));
            
            float phi_corr_emc = buff[i][23] - buff[j][23];
            phi_corr_emc = atan2(sin(phi_corr_emc),cos(phi_corr_emc));
            float eta_corr_emc = buff[i][24] - buff[j][24];
            
            float diff_EMCid = buff[i][25] - buff[j][25];
            float diff_EMCmodid = buff[i][26] - buff[j][26];
            
            int Sign = 0;    //opp
            if(buff[i][5]*buff[j][5]>0)Sign = 1; // same
            
            /*
             if(buff[j][1]>=0.5)
             {
             // include electrons
             Hphi_corr_we[0][0] -> Fill(buff[i][1],phi_corr);
             if(buff[i][16]==1.0)Hphi_corr_we[0][1] -> Fill(buff[i][1],phi_corr); // opp sign no partner
             if(buff[i][17]==1.0)Hphi_corr_we[0][2] -> Fill(buff[i][1],phi_corr); // same sign no partner
             if(buff[i][16]!=1.0)Hphi_corr_we[0][3] -> Fill(buff[i][1],phi_corr); // semi-inclusive
             
             // remove conversion electrons
             
             if(buff[j][16]==1.0)continue; // remove conversion electron
             Hphi_corr_rc[0][0] -> Fill(buff[i][1],phi_corr);
             if(buff[i][16]==1.0)Hphi_corr_rc[0][1] -> Fill(buff[i][1],phi_corr); // opp sign no partner
             if(buff[i][17]==1.0)Hphi_corr_rc[0][2] -> Fill(buff[i][1],phi_corr); // same sign no partner
             if(buff[i][16]!=1.0)
             {
             Hphi_corr_rc[0][3] -> Fill(buff[i][1],phi_corr); // semi-inclusive
             
             if(buff[i][17]!=1.0 && buff[j][17]!=1.0) // remove all pairs
             {
             Hphi_corr_rc[0][4] -> Fill(buff[i][1],phi_corr); // semi-inclusive
             }
             }
             }
             
             if(buff[j][1]>=0.4)
             {
             // include electrons
             Hphi_corr_we[1][0] -> Fill(buff[i][1],phi_corr);
             if(buff[i][16]==1.0)Hphi_corr_we[1][1] -> Fill(buff[i][1],phi_corr); // opp sign no partner
             if(buff[i][17]==1.0)Hphi_corr_we[1][2] -> Fill(buff[i][1],phi_corr); // same sign no partner
             if(buff[i][16]!=1.0)Hphi_corr_we[1][3] -> Fill(buff[i][1],phi_corr); // semi-inclusive
             
             // remove conversion electrons
             
             if(buff[j][16]==1.0)continue; // remove conversion electron
             Hphi_corr_rc[1][0] -> Fill(buff[i][1],phi_corr);
             if(buff[i][16]==1.0)Hphi_corr_rc[1][1] -> Fill(buff[i][1],phi_corr); // opp sign no partner
             if(buff[i][17]==1.0)Hphi_corr_rc[1][2] -> Fill(buff[i][1],phi_corr); // same sign no partner
             if(buff[i][16]!=1.0)
             {
             Hphi_corr_rc[1][3] -> Fill(buff[i][1],phi_corr); // semi-inclusive
             
             if(buff[i][17]!=1.0 && buff[j][17]!=1.0) // remove all pairs
             {
             #	              Hphi_corr_rc[1][4] -> Fill(buff[i][1],phi_corr); // semi-inclusive
             }
             }
             }
             */
            // include electrons
            Hphi_corr_we[2][0] -> Fill(buff[i][1],phi_corr);
            if(buff[i][16]==1.0)Hphi_corr_we[2][1] -> Fill(buff[i][1],phi_corr); // opp sign no partner
            if(buff[i][17]==1.0)Hphi_corr_we[2][2] -> Fill(buff[i][1],phi_corr); // same sign no partner
            if(buff[i][16]!=1.0)Hphi_corr_we[2][3] -> Fill(buff[i][1],phi_corr); // semi-inclusive
            
            // remove conversion electrons
            
            //if(buff[j][16]==1.0)continue; // remove conversion electron
            if(buff[j][16]!=1.0 && buff[j][27]!=1.0) // remove conversion electron  pair
            {
              Hphi_corr_rc[2][0] -> Fill(buff[i][1],phi_corr);
              if(buff[i][16]==1.0)Hphi_corr_rc[2][1] -> Fill(buff[i][1],phi_corr); // opp sign partner
              if(buff[i][16]!=1.0) // semi inclusive
              {
                Hphi_corr_rc[2][3] -> Fill(buff[i][1],phi_corr); // semi-inclusive
                HRad_semi[0]->Fill(buff[i][1],R_corr);
                H_EMCtower[2] -> Fill(buff[i][1],diff_EMCid);
                if(buff[i][1]>5.5)Hemc_eta_phi[2]->Fill(eta_corr_emc,phi_corr_emc);
                if(buff[i][1]>5.5)Hphi_eta_semi[0]-> Fill(eta_corr,phi_corr); // delta phi & eta
                if(R_corr<0.05)HpID[2]->Fill(buff[i][1],buff[j][0]);
                if(R_corr<0.05)HnSig[2]->Fill(buff[i][1],buff[j][21]);
                if(buff[j][21]>-1.0)HRad_semi_nSig[0]->Fill(buff[i][1],R_corr);
                if(buff[j][21]<-1.0)HRad_semi_nSig[1]->Fill(buff[i][1],R_corr);
                
                // --- make inv. mass plot
                if(buff[j][21]>-1.0 && Sign == 0)
                {
                  HRad_semi_nSig[2]->Fill(buff[i][1],R_corr);
                  Hinvmass_notreco[0]->Fill(buff[i][1],invmass2D_notreco);
                  
                  if(invmass2D_notreco<0.1)
                  {
                    N_notreco_opp = 1;
                    addcut = 1; // additional photonic electron
                    buff[j][29] = 1.0; // additional photonic electron
                  }
                }
                
                
                if(buff[j][21]>-1.0 && Sign == 1)
                {
                  HRad_semi_nSig[3]->Fill(buff[i][1],R_corr);
                  Hinvmass_notreco[1]->Fill(buff[i][1],invmass2D_notreco);
                  
                  if(invmass2D_notreco<0.1)
                  {
                    N_notreco_sam =  1;
                    addcut = 0; // back com. background
                    buff[j][29] = 0.0; // back com. background
                  }
                }
                
                if(addcut==0)
                {
                  HRad_semi[1]->Fill(buff[i][1],R_corr);
                  Hphi_corr_rc[2][4] -> Fill(buff[i][1],phi_corr); // semi-inclusive
                }
                
                //if(buff[j][21]>-1.0)cout << "Invmass_not_reco = " << invmass2D_notreco << endl;
                
                
                // --- remove same tower
                if(buff[i][25]!=buff[j][25] && addcut==0)
                {
                  HRad_semi[2]->Fill(buff[i][1],R_corr);
                  Hphi_corr_semi_rmEMC->Fill(buff[i][1],phi_corr);
                  if(buff[i][1]>5.5)Hphi_eta_semi[1]-> Fill(eta_corr,phi_corr); // delta phi & eta
                }
                
                if(buff[i][25]!=buff[j][25] &&
                   R_corr>0.05)
                {
                  HRad_semi[3]->Fill(buff[i][1],R_corr);
                  Hphi_corr_semi_rmEMCTPC->Fill(buff[i][1],phi_corr);
                  if(buff[i][1]>5.5)Hphi_eta_semi[2]-> Fill(eta_corr,phi_corr); // delta phi & eta
                }
                
              } // end of semi-inc
              
              if(buff[i][17]==1.0 && addcut==0)// same sign
              {
                if(buff[j][28]!=1.0)Hphi_corr_rc[2][2] -> Fill(buff[i][1],phi_corr);
                if(buff[j][28]!=1.0)HRad_same[5]->Fill(buff[i][1],R_corr);
              }
              
            } // end of remove pho. e
            
          }
        }   // end of mix loop
        
      } // end of electron trigger
      
      if(N_notreco_opp==1)HpT_pho_insemi[0]->Fill(buff[i][1]);
      if(N_notreco_sam==1)HpT_pho_insemi[1]->Fill(buff[i][1]);
      
      
      // bg correlation
      
      if(buff[i][0] < 0.0 &&
         fabs(buff[i][18])<0.7 &&
         buff[i][19]> 2.0 && buff[i][19]<3.0 &&
         //buff[i][21]> -6.0 && buff[i][21]<-3.0 &&
         buff[i][20]==1.0)
      {
        if(trigID==2)HdEdx_had -> Fill(buff[i][1],buff[i][19]);
        
        int num_assh = 0;
        
        for(int j=0; j<mixloop; j++)
        {
          if(i!=j) // remove same track
          {
            
            float phi_corr_bg = buff[i][6] - buff[j][6];
            phi_corr_bg = atan2(sin(phi_corr_bg),cos(phi_corr_bg));
            float eta_corr_bg = buff[i][18] - buff[j][18];
            
            if(buff[j][1]<0.3)continue;
            if(buff[j][16]==1.0)continue; // remove conversion electron
            Hphi_corr_hadron[0] -> Fill(buff[i][1],phi_corr_bg);
            if(buff[j][27]==1.0)continue; // remove conversion electron pair
            Hphi_corr_hadron[1] -> Fill(buff[i][1],phi_corr_bg);
            if(buff[j][29]==1.0)continue; // remove conversion electron
            //if(buff[j][17]==1.0)continue; // remove same sign electron
            
            num_assh = num_assh+1;
            
            if(trigID==2 && num_assh==1)Hhad_trig -> Fill(buff[i][1]);
            
            
            Hphi_corr_hadron[2] -> Fill(buff[i][1],phi_corr_bg);
            
            
            if(buff[i][1]>5.0)Hphi_eta_had-> Fill(eta_corr_bg,phi_corr_bg); // delta phi & eta
          }
        }
        
      } // end of bg correlation
      
      
    } // end of trigger loop
    
  } // end of e-h corr.
  
  
  //====================================================================
  
  
  cout << "================== Run ; " << muEvent->eventNumber() << " End ============ " << endl;
  cout << "seltrk = " << seltrk << endl;
  //cout << "number of match = " << Num_match << " ; size "<< bEmcPoints.size() << endl;
  //for(int ii=0; ii<2; ii++)cout << endl;
  
  mEventsProcessed++ ;
  return kStOK ;
  
}


double St_ehcorrelationMaker::Cal_Invmass(StPhysicalHelixD helix1,StPhysicalHelixD helix2, double bField)
{
  
  // cal DCA of two tracks
  pair<double,double> pathLength(helix1.pathLengths(helix2).first, helix1.pathLengths(helix2).second);
  
  float DCAlength = abs(helix1.at(pathLength.first) - helix2.at(pathLength.second));
  
  // get momentum at DCA of two track
  StThreeVectorD mom1_DCA = helix1.momentumAt(pathLength.first,  bField*tesla);
  StThreeVectorD mom2_DCA = helix2.momentumAt(pathLength.second, bField*tesla);
  
  
  float tot_mom1 = sqrt(pow(mom1_DCA.x(),2)+pow(mom1_DCA.y(),2)+pow(mom1_DCA.z(),2));
  float tot_mom2 = sqrt(pow(mom2_DCA.x(),2)+pow(mom2_DCA.y(),2)+pow(mom2_DCA.z(),2));
  
  
  const double me = 0.00051099906;	//mass of e
  
  StLorentzVectorD Four1, Four2;
  
  
  // cal 2D inv mass
  Four1.setPx(sqrt(pow(mom1_DCA.x(),2)+pow(mom1_DCA.y(),2)));
  Four1.setPy(0.);
  Four1.setPz(mom1_DCA.z());
  
  Four2.setPx(sqrt(pow(mom2_DCA.x(),2)+pow(mom2_DCA.y(),2)));
  Four2.setPy(0.);
  Four2.setPz(mom2_DCA.z());
  
  Four1.setE(mom1_DCA.massHypothesis(me));
  Four2.setE(mom2_DCA.massHypothesis(me));
  
  double invmass2D = (Four1+Four2).m();
  
  return invmass2D;
}

Int_t St_ehcorrelationMaker::Finish( )

{ // Do once at the end the analysis
  
  // Write histograms to disk, output miscellaneous other information
  
  histogram_output -> Write() ;   // Write all histograms to disk
  
  //cout << "Total Events Processed in DstMaker " << mEventsProcessed << endl ;
  
  return kStOk ;
  
}









