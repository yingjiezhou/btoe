// Based on the MuDST tools written by Frank Laue.
// Based on the DST Tutorial by Dan Magestro on the STAR Computing/Tutorials page.
// Updated 9/4/2006 by Jim Thomas to include the latest DST format, and Scheduler techniques.

#include <iostream>
#include "PhorecoMaker.h"
#include "StEvent/StEventTypes.h"
#include "StMcEventTypes.hh"

#include "SystemOfUnits.h"
#include "StEmcUtil/others/emcDetectorName.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/projection/StEmcPosition.h"
#include "StEmcADCtoEMaker/StBemcData.h"
#include "StEmcADCtoEMaker/StEmcADCtoEMaker.h"
#include "StEmcRawMaker/StBemcTables.h"
#include "StEmcTriggerMaker/StEmcTriggerMaker.h"
#include "StDaqLib/EMC/StEmcDecoder.h"
#include "StPreEclMaker/StPreEclMaker.h"
#include "StEpcMaker/StEpcMaker.h"
#include "StJetMaker/StFourPMakers/StMuEmcPosition.h"
#include "St_db_Maker/St_db_Maker.h"
#include "StDetectorDbMaker/StDetectorDbMaker.h"
#include "StDetectorDbMaker/StDetectorDbTriggerID.h"
#include "StAssociationMaker/StTrackPairInfo.hh"
#include "StThreeVector.hh"
#include "StPhysicalHelix.hh"
#include "StLorentzVector.hh"

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TObjArray.h"

#define NumberOfTH1F      20                     // Number of Histograms

ClassImp(PhorecoMaker)                   // Macro for CINT compatibility


//PhorecoMaker::PhorecoMaker( StMuDstMaker* maker ) : StMaker("SimpleAnalysisMaker")
PhorecoMaker::PhorecoMaker(const Char_t *name) : StMaker(name)
{ // Initialize and/or zero all public/private data members here.
  /*
  for ( Int_t i = 0 ; i < NumberOfTH1F ; i++ )  // Zero the histogram pointers
  {
  histogram[i] = NULL ;
  histogram_2D[i] = NULL ;
  }
  */
  
  //mMuDstMaker      = maker ;                    // Pass MuDst pointer to DstAnlysisMaker Class member functions
  //histogram_output = NULL  ;                    // Zero the Pointer to histogram output file
  mEventsProcessed = 0     ;                    // Zero the Number of Events processed by the maker 
  mFileName = "" ;               // Histogram Output File Name will be set inside the "analysis".C macro
  
}


PhorecoMaker::~PhorecoMaker() 
  
{ // Destroy and/or zero out all public/private data members here.
  
}


Int_t PhorecoMaker::Init( )
//PhorecoMaker::Init( )
{ // Do once at the start of the analysis
  
  // Create Histogram output file
  
  //cout << "create histgram files" << endl;
	
  histogram_output = new TFile(mFileName, "recreate" ) ;  // Name was set previously in calling macro 
  
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


  HVertex[0] = new TH1F( "Vertex_0", "Event Vertex Z Position all ", 200, -100.0, 100.0 ) ; 
  HVertex[1] = new TH1F( "Vertex_1", "Event Vertex Z Position cut ", 200, -100.0, 100.0 ) ; 
  Heop[0]  = new TH1F( "EoP", "energy and mom. match", 300, 0, 3.0 ) ;
  Heop[1]  = new TH1F( "EoP_cut", "energy and mom. match af. cut", 300, 0, 3.0 ) ;
  Hover = new TH1F ("Over_seltrk", "Over sel trk", 10,-1,9);
  Hseltrk_all = new TH1F ("Num_seltrk_all", "Nummer of seltrk all", 100,0,100);
  Hseltrk_TPC = new TH1F ("Num_seltrk_TPC", "Nummer of seltrk TPC", 100,0,100);
  Hseltrk_emc = new TH1F ("Num_seltrk_emc", "Nummer of seltrk EMC", 100,0,100);
  Hinvmass[0]  = new TH1F( "Invmass_opp", "Invmass opp sign", 100, 0, 0.5) ;
  Hinvmass[1]  = new TH1F( "Invmass_same", "Invmass same sign", 100, 0, 0.5) ;
  Hinvmass_wocut[0]  = new TH1F( "Invmass_opp_wocut", "Invmass opp sign wo cut", 100, 0, 0.5) ;
  Hinvmass_wocut[1]  = new TH1F( "Invmass_same_wocut", "Invmass same sign wo cut", 100, 0, 0.5) ;
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
  Hmatch[1]  = new TH2F( "del_z", "del z of bEMC hit and proj.", 100, 0, 10, nbins, -10.0, 10.0 ) ;
  Heop_dEdx = new TH2F( "eop_dEdx", "eop dEdx corr pT>2", 30, 0, 3.0, 100, 0.0, 10.0 ) ;

  Hopenphi_pT[0]  = new TH2F( "Hopenphi_opp_pT", "phi opp sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopenphi_pT[1]  = new TH2F( "Hopenphi_same_pT", "phi same sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopentheta_pT[0]  = new TH2F( "Hopentheta_opp_pT", "theta opp sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopentheta_pT[1]  = new TH2F( "Hopentheta_same_pT", "theta same sign vs pT", 100,0,10, 160, 0, 1.6) ;
  HDCA_pT[0]  = new TH2F( "HDCA_opp_pT", "DCA opp sign vs pT", 100,0,10, 160, 0, 1.6) ;
  HDCA_pT[1]  = new TH2F( "HDCA_same_pT", "DCA same sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopenangle_pT[0]  = new TH2F( "Hopenangle_opp_pT", "angle opp sign vs pT", 100,0,10, 160, 0, 1.6) ;
  Hopenangle_pT[1]  = new TH2F( "Hopenangle_same_pT", "angle same sign vs pT", 100,0,10, 160, 0, 1.6) ;

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

  Hass_pT  = new TH1F( "Pt_ass_h2", "pT ass h2", 200, 0.0, 20.0 ) ;

  Hele_Z = new TH1F("Hele_Z_ht2","electron vs. Z vertex ht2",800,-40,40);

  Hinvmass_pT_Opp[0]  = new TH2F( "Invmass_opp_pT_pho", "Invmass opp sign pho.", 200, 0, 20, 100, 0, 0.5) ;
  Hinvmass_pT_Opp[1]  = new TH2F( "Invmass_opp_pT_dal", "Invmass opp sign Dal.", 200, 0, 20, 100, 0, 0.5) ;

  Hinvmass_pT_Same[0]  = new TH2F( "Invmass_same_pT_pho", "Invmass same sign pho", 200, 0, 20, 100, 0, 0.5) ;
  Hinvmass_pT_Same[1]  = new TH2F( "Invmass_same_pT_dal", "Invmass same sign Dal", 200, 0, 20, 100, 0, 0.5) ;

  H_dis_phi  = new TH2F( "dis_phi_h2", "delta phi EMC h2", 200, 0, 20, 200, -0.1, 0.1) ;

  H_dis_eta  = new TH2F( "dis_eta_h2", "delta eta EMC h2", 200, 0, 20, 200, -0.1, 0.1) ;

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

  //HpT_check[0]  = new TH1F( "Pt_check_0", "electron trigger inc", 200, 0.0, 20.0 ) ;
  //HpT_check[1]  = new TH1F( "Pt_check_1", "electron trigger opp", 200, 0.0, 20.0 ) ;
  //HpT_check[2]  = new TH1F( "Pt_check_2", "electron trigger same", 200, 0.0, 20.0 ) ;
  //HpT_check[3]  = new TH1F( "Pt_check_3", "electron trigger semi", 200, 0.0, 20.0 ) ;
  HpT_check[0]  = new TH1F( "Pt_check_0", "electron inc mix loop", 200, 0.0, 20.0 ) ;

  Hnsig_e = new TH1F("Hnsig_e","n sigma global check",10,0,10);

  Hcheck_pair = new TH2F ("Hcheck_pair_ht2","pair electron check ht2",100,0,10, 10,-1.5,8.5);

  Hpair[0] = new TH1F("Hpair0","opp cand",30,-0.5,29.5);
  Hpair[1] = new TH1F("Hpair1","same cand",30,-0.5,29.5);

  Hetag_check = new TH1F("Hetag_check","tag check for semi-inclusive",110,-100.5,9.5);
  
  //********* Hist for photon reco.

  Hphotonice_pho_mc = new TH1F("Hphotonice_pho_mc","photonic electron from conv. Mc",200,0,20);
  Hphotonice_dal_mc = new TH1F("Hphotonice_dal_mc","photonic electron from Dal. Mc",200,0,20);

  Hphotonice_pho = new TH1F("Hphotonice_pho","photonic electron from conv.",200,0,20);
  Hphotonice_dal = new TH1F("Hphotonice_dal","photonic electron from Dal.",200,0,20);
  Hphotonice_pho_w = new TH1F("Hphotonice_pho_w","photonic electron from conv. weight",200,0,20);
  Hphotonice_dal_w = new TH1F("Hphotonice_dal_w","photonic electron from Dal.weight",200,0,20);

  Hphotonice_pho_reco[0] = new TH1F("Hphotonice_pho_reco_opp","photonic electron from conv. reco opp",200,0,20);
  Hphotonice_dal_reco[0] = new TH1F("Hphotonice_dal_reco_opp","photonic electron from Dal.reco opp",200,0,20);
  Hphotonice_pho_reco_w[0] = new TH1F("Hphotonice_pho_w_reco_opp","photonic electron from conv. weight reco opp",200,0,20);
  Hphotonice_dal_reco_w[0] = new TH1F("Hphotonice_dal_w_reco_opp","photonic electron from Dal.weight reco opp",200,0,20);

  Hphotonice_pho_reco[1] = new TH1F("Hphotonice_pho_reco_same","photonic electron from conv. reco same",200,0,20);
  Hphotonice_dal_reco[1] = new TH1F("Hphotonice_dal_reco_same","photonic electron from Dal.reco same",200,0,20);
  Hphotonice_pho_reco_w[1] = new TH1F("Hphotonice_pho_w_reco_same","photonic electron from conv. weight reco same",200,0,20);
  Hphotonice_dal_reco_w[1] = new TH1F("Hphotonice_dal_w_reco_same","photonic electron from Dal.weight reco same",200,0,20);

  // request EMC

  Hphotonice_pho_w_EMC = new TH1F("Hphotonice_pho_w_EMC","photonic electron from conv. weight EMC",200,0,20);
  Hphotonice_pho_reco_w_EMC[0] = new TH1F("Hphotonice_pho_w_reco_opp_EMC","photonic electron from conv. weight reco opp EMC",200,0,20);
  Hphotonice_pho_reco_w_EMC[1] = new TH1F("Hphotonice_pho_w_reco_same_EMC","photonic electron from conv. weight reco same EMC",200,0,20);
  Hphotonice_pho_EMC = new TH1F("Hphotonice_pho_EMC","photonic electron from conv. unweight EMC",200,0,20);
  Hphotonice_pho_reco_EMC[0] = new TH1F("Hphotonice_pho_reco_opp_EMC","photonic electron from conv. unweight reco opp EMC",200,0,20);
  Hphotonice_pho_reco_EMC[1] = new TH1F("Hphotonice_pho_reco_same_EMC","photonic electron from conv.unweight reco same EMC",200,0,20);

  //********** Hist for nonphotonic eff

  Hnonphotonice[0] = new TH1F("Hnonphotonice0","nonphotonic electron org. unweight",200,0,20);
  Hnonphotonice[1] = new TH1F("Hnonphotonice1","nonphotonic electron TPC+EMC unweight",200,0,20);
  Hnonphotonice_w[0] = new TH1F("Hnonphotonice_w_0","nonphotonic electron org. weight",200,0,20);
  Hnonphotonice_w[1] = new TH1F("Hnonphotonice_w_1","nonphotonic electron TPC+EMC",200,0,20);

  //

  Hmomcorr = new TH2F("Hmomcorr","mom. corr Mc & rec",200,0,20,200,0,20);
  Hmom_reso = new TH2F("Hmom_reso","mom. reso",200,0,20,2000,-1,1);

  Hmcasso_pho = new TH1D("Hmcass_pho","# of associated mc track for conver",20,-0.5,19.5);
  Hmcasso_dal = new TH1D("Hmcass_dal","# of associated mc track for dalitz",20,-0.5,19.5);

  //initial EMC point  
  hPointEta = new TH1F("hPointEta","EtaB",302,mEtaB);
  hPointPhi = new TH1F("hPointPhi","PhiB",900,mGlobalPhiB);
  hPointZ   = new TH1F("hPointZ","Z",200,-200,200);
  // end of cretate Histgrams

  H_EMC_phi_eta = new TH2F( "H_EMC_phi_eta","EMC phi eta",900,mGlobalPhiB,302,mEtaB) ;


  mEmcPosition = new StEmcPosition();

  for(int i = 0; i < 4; i++){
    if(i == 1) continue;
    mEmcGeom[i] = StEmcGeom::getEmcGeom(detname[i].Data());         //bemc
  }
  
  cout << "EMC rad. =" << mEmcGeom[0]->Radius() << endl;
  cout << "SMDE rad. =" << mEmcGeom[2]->Radius() << endl;
  cout << "SMDP rad. =" << mEmcGeom[3]->Radius() << endl;
  
  //return kStOK ; 
  return StMaker::Init(); 
  
}


void
PhorecoMaker::Clear(Option_t *opt)
{
	cout<<"Maker::Clear()"<<endl;
	event = 0;
	//meEvent->clear();
	StMaker::Clear();		//this too
}


Int_t PhorecoMaker::Make( )
//PhorecoMaker::Make( )
{ // Do each event
  
  cout << "Get Mcevent" << endl;
  // Get 'event' data 
  
  //StMuEvent* muEvent      =  mMuDstMaker->muDst()->event() ;
  event = (StEvent*) GetInputDS("StEvent");
  
  mcEvent = (StMcEvent*) GetDataSet("StMcEvent");
  //if(!accept(event)){
  //  return kStSkip;
  //}
  
  StAssociationMaker* assoc = 0;
  assoc = (StAssociationMaker*) GetMaker("StAssociationMaker");
  
  rcTpcHitMapType *tpcHitMap = assoc->rcTpcHitMap();
  mcTpcHitMapType *tpcMcHitMap = assoc->mcTpcHitMap();
  rcTrackMapType *tpcTrackMap = assoc->rcTrackMap();
  mcTrackMapType *tpcMcTrackMap = assoc->mcTrackMap();
  
  if(!tpcHitMap){
    //gMessMgr->Warning() << " :: Warning :: Missing association map."<<endm;
    //incrementTally("PkMcNtuple: Missing association map");
    return kStWarn;
  }
  
  if(!tpcTrackMap){
    //gMessMgr->Warning() << " :: Warning :: Missing association map."<<endm;
    //incrementTally("PkMcNtuple: Missing association map");
    return kStWarn;
  }

  emcassoc = (StEmcAssociationMaker*) GetMaker("EmcAssoc");
  
  multiEmcTrackPoint *emcTrackPointMap = emcassoc->getTrackPointMap();
  multiEmcPointTrack *emcPointTrackMap = emcassoc->getPointTrackMap();

  StEmcTriggerMaker *trig = (StEmcTriggerMaker*) GetMaker("bemctrigger");
  //StEmcCollection *mEmcCol = event->emcCollection();
  
  
  // Cut on the number of vertices in the event.  On old tapes, no-vertex gets reported as VtxPosition=(0,0,0).
  /*
    if ( (muEvent->primaryVertexPosition().x() == 0) && (muEvent->primaryVertexPosition().y() == 0) 
    && (muEvent->primaryVertexPosition().z() == 0) ) return kStOK ;  // Skip events that do not have a primary vertex
  */
  
  cout << endl;
  //cout << "================== Run ; " << muEvent->eventNumber() << " Start ============ " << endl;
  //cout <<  muEvent->eventNumber() << endl;
  
  // Get EMC Collection
    

  float maxTowerE = 0.0;
  
  //StEmcCollection* mEmcCol = mMuDstMaker->muDst()->emcCollection(); 
  StEmcCollection *mEmcCol = event->emcCollection();
  StSPtrVecEmcPoint& bEmcPoints = mEmcCol->barrelPoints();
  
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

  
  // ------ get Mc Event --------------------

  // mcTrack

  double Z_vertex_mc = mcEvent->primaryVertex()->position().z();
  cout << "Z_vertex_mc = " << Z_vertex_mc << endl;

  if(fabs(Z_vertex_mc)<35.0)
       {
	StSPtrVecMcTrack& mcTracks = mcEvent->tracks();
	for(StSPtrVecMcTrack::iterator mcTrack = mcTracks.begin(); mcTrack != mcTracks.end(); mcTrack++)
            {
             float gid = (*mcTrack)->geantId();
             float key = (*mcTrack)->key();
             float pdgid = (*mcTrack)->pdgId();
             float eglab = (*mcTrack)->eventGenLabel(); // 99999 = add by hand (embedding)
             float mom = (*mcTrack)->momentum().x();
             float mcpT = (*mcTrack)->pt();
             float mceta = (*mcTrack)->pseudoRapidity();
             float shower = (*mcTrack)->isShower();         

             if(key<=0)continue;
             if(gid<=0)continue;
             //if(pdgid<=0)continue;
             //if(eglab<=0)continue;
	     
             float pgid = 99999;
             float pkey = 99999;
             float Num_decay = 99999;
             float peglab = -99999;
             int isPhotonic = 0;
             int isDalitz = 0;
	     
             if((*mcTrack)->parent())
	       {
                 pgid = (*mcTrack)->parent()->geantId();
                 pkey = (*mcTrack)->parent()->key();
                 peglab = (*mcTrack)->parent()->eventGenLabel();
	       }
	     
             //cout << "mcTrack = " << key << " : " << gid<< " ; " << pdgid << " ; " << eglab << endl;  
             cout << "mcTrack = " << key << " : " << gid<< " ; " << shower << " || " << pkey << " ; " << pgid << " ; " << eglab<< endl;  
             //cout << "TPC hits = " << (*mcTrack)->tpcHits() << endl;
             if((*mcTrack)->parent() && (*mcTrack)->parent()->stopVertex()) Num_decay = (*mcTrack)->parent()->stopVertex()->numberOfDaughters();
	     
             if((gid==2 || gid==3) && pgid==1 && Num_decay==2 && shower==0 && peglab==99999)
	       {  
                 cout << "key = " << key << " is embedding photonic electron." << endl;
                 isPhotonic = 1;
	       } 

             if((gid==2 || gid==3) && pgid==149 && Num_decay==3 && shower==0 && peglab==99999)
               {
                 cout << "key = " << key << " is embedding Dalitz." << endl;
                 isDalitz = 1;
	       }    
	     
             //bool isPhotonic = (gid==2 || gid==3) && pgid==1 && Num_decay==2 && shower==0;
             //bool isDalitz = (gid==2 || gid==3) && pgid==149 && Num_decay==3 && shower==0;
	     
             bool IdPho = PhotonicID(*mcTrack);
             bool IdDal = DalitzID(*mcTrack);
             cout << "isPhotonic = " << IdPho << endl;
             cout << "isDalitz = " << IdDal << endl;
             cout << endl;             
	     
             if(fabs(mceta)>0.7)continue;
             if(IdPho==1)Hphotonice_pho_mc->Fill(mcpT);
             if(IdDal==1)Hphotonice_dal_mc->Fill(mcpT);
            }
       }
  
  /*
    
  int Num_match = 0;
  
  int nptracks = mMuDstMaker->muDst()->numberOfPrimaryTracks();
  
  cout << "Event number " << muEvent->eventNumber() << " have " << bEmcPoints.size() << " EMC point ; "<< endl;
  
  // Do 'event' analysis based on event data 
  
  */
  
  //double Z_vertex = muEvent->primaryVertexPosition().z();
  double Z_vertex = event->primaryVertex()->position().z();
  cout << "Z_vertex = " << Z_vertex << endl;
  
  HVertex[0] -> Fill( Z_vertex ) ; // Make histogram of the vertex Z distribution
  
  //if(Z_vertex > 30 || Z_vertex < -40)return kStOK ;
  if(fabs(Z_vertex)>35.0)return kStOK ;
  int Z_id = int((Z_vertex+35.0)/5.0);
  
  cout << "Z_vertex = " << Z_vertex << endl;
  
  HVertex[1] -> Fill( Z_vertex ) ; // Make histogram of the vertex Z distribution
  
    
  //Double_t bField = muEvent->eventSummary().magneticField()/10.;
  //Double_t bField = event->summary()->magneticField()/10.;
  Double_t bField = event->runInfo()->magneticField()/10.;
  cout <<"bField = " << bField << endl;  

  // set mixing array
  int alltrk = 0;
  int seltrk = 0; // --- selected track for mixing 
  int emctrk = 0;
  float buff[250][23]; 
  for(int i=0; i<250; i++){
    for (int j=0; j<23; j++){
      buff[i][j]=0.0;
    }
  }


  StSPtrVecTrackNode& nodes = event->trackNodes();
  StPrimaryTrack *track;
  StGlobalTrack *gl_track;
 

  //-------------------------------- 

  cout << "primary track loop" << endl;

  //while ( ( track = (StMuTrack*)GetTracks.Next() ) )             // Main loop for Iterating over tracks
   for(StSPtrVecTrackNodeIterator node = nodes.begin(); node != nodes.end(); node++)
    { 
      alltrk = alltrk+1;
      
      int Num_bEMC = 0;
      int num_ele  = 0;    

      // get associate global track      
      //gl_track = track->globalTrack();

      gl_track = dynamic_cast<StGlobalTrack*>((*node)->track(global));;
      if(!gl_track)continue;
 
      track = dynamic_cast<StPrimaryTrack*>((*node)->track(primary));
      if(track==NULL)continue;

      cout << "key = " << track->key() << " ; " << gl_track->key() << endl; 
      
      short flag = track->flag(); 
      
      unsigned short nHitsFit = track->fitTraits().numberOfFitPoints();
      unsigned short nHitsPoss = track->numberOfPossiblePoints();
      float nfitOverMax = (float)nHitsFit/(float)nHitsPoss;
      cout << "nfitOverMax = " << nfitOverMax << endl;
      
      float eta = track->geometry()->momentum().pseudoRapidity();
      float phi = track->geometry()->momentum().phi();
      phi = atan2(sin(phi),cos(phi));
      float pT  = track->geometry()->momentum().perp();
      float chi2 = track->fitTraits().chi2();
      float mom = track->geometry()->momentum().mag();
      
      //StPtrVecTrackPidTraits traits = gl_track->pidTraits(kTpcId);
      //StDedxPidTraits pid= dynamic_cast<StDedxPidTraits*>(traits); // ? why loop
      //float dEdx = traits->mean();
      float dEdx = -9999; 
      StPtrVecTrackPidTraits traits = gl_track->pidTraits(kTpcId);
      if(traits.size()){
	StDedxPidTraits* pid;
	for(unsigned int i = 0; i < traits.size(); i++){
	  pid = dynamic_cast<StDedxPidTraits*>(traits[i]);
	  if(pid && pid->method() == kTruncatedMeanId) break;
	}
	if(!pid) continue;
	dEdx = pid->mean();
      }
      
      cout << "dE/dx =" << dEdx << endl; 
      float val_dEdx = dEdx*1e6 ;  
      
      float dcaGlobal = gl_track->impactParameter();
      
      
      //histogram[1] -> Fill(dcaGlobal);
      
      float pID = -99.9; // -99.9 --- not electron / 1 = electron 
      
      float g_momx_1 = gl_track->geometry()->momentum().x();  
      float g_momy_1 = gl_track->geometry()->momentum().y();  
      float g_momz_1 = gl_track->geometry()->momentum().z();  
      
      cout << "gmom = " << g_momx_1 << " ; " << g_momy_1 << " ; " << g_momz_1 << endl;
      
      
      //--------------------- find associate Mc Track  ---------------------------------------------//  
      
      pair<rcTrackMapIter,rcTrackMapIter> trackBounds = tpcTrackMap->equal_range(gl_track);
      
      bool isphotonic=99999;
      bool isdalitz=99999;
      int assmctrk_pho = 0;
      int assmctrk_dal = 0;
      float ass_parentpT = 99999;
      
      
      for (rcTrackMapIter trkIt=trackBounds.first; trkIt!=trackBounds.second; ++trkIt) 
	{
	  float assmom = (*trkIt).second->partnerMcTrack()->momentum().mag();
	  float asspT = (*trkIt).second->partnerMcTrack()->momentum().perp();
	  StMcTrack*   origTrk = (*trkIt).second->partnerMcTrack();
	  cout << "[" << mom << ", ";
	  cout << origTrk->momentum().mag() << "]" << endl;
	  cout << "[" << pT << ", ";
	  cout << origTrk->momentum().perp() << "]" << endl;
	  cout <<"asso key " << origTrk->key() <<  endl;
	  cout <<"asso geantID " << origTrk->geantId() << endl;
	  cout <<"asso parent geantID" << origTrk->parent()->geantId() << endl;
	  cout <<"asso parent key" << origTrk->parent()->key() << endl;
	  
	  ass_parentpT = origTrk->parent()->pt();
	  
	  Hmomcorr->Fill(pT,asspT); 
	  float delpT = (asspT - pT)/pT;
	  Hmom_reso->Fill(pT,delpT); 
	  
	  //if(fabs(delpT)>0.05)continue;
	  
	  isphotonic = PhotonicID(origTrk);
	  isdalitz = DalitzID(origTrk);
	  
	  cout << "isPhotonic = " << isphotonic << endl;
	  cout << "isDalitz = " << isdalitz << endl;
	  
	  if(isphotonic==1)
	    {
	      assmctrk_pho++;
	    }
	  
	  if(isdalitz==1)
	    {
	      assmctrk_dal++;
	    }
	  
	}
      
      cout << assmctrk_pho << " is associated" << endl;
      cout << assmctrk_dal << " is associated" << endl;
      
      // ********* Fill for nonphotonic e eff. calculation
      
      if(isphotonic==1 && eta>0.0 && eta<0.7)
        {
	  Hnonphotonice[0]->Fill(pT);
	  Hnonphotonice_w[0]->Fill(pT,Nonphotonicweights(pT));
	}
      
      
      if(flag<=0)continue;
      
      
      if(dcaGlobal > 0.0 && dcaGlobal < 1.5
	 //&& nHitsDedx > 15 && nHitsDedx < 50
	 && nHitsFit > 15 && nHitsFit < 50
	 && chi2 > 0.0 && chi2 < 3.0
	 && nfitOverMax > 0.52 && nfitOverMax < 1.2 
	 && fabs(eta)<0.7)
	{
	  //seltrk = seltrk+1;
	  
	  HdcaGlobal_check->Fill(dcaGlobal);
	  //HnHits_check->Fill(nHits);
	  //HnHitsdEdx_check->Fill(nHitsDedx);
	  Hchi_check->Fill(chi2);
	  //Hflag_check->Fill(flag);   
	  HnfitOverMax_check->Fill(nfitOverMax);   
	  Heta_check[0]->Fill(eta);   
	  
	  HpT[0] -> Fill(pT) ;
	  HpT_dEdx[0] -> Fill(pT, val_dEdx) ;
	  
	  // ********* Fill for photonic reco. calculation
	  
	  if(isphotonic==1)
	    {
	      Hmcasso_pho->Fill(assmctrk_pho);
	      Hphotonice_pho->Fill(pT);
	      Hphotonice_pho_w->Fill(pT,photonweights(ass_parentpT));
	    }
	  if(isdalitz==1)
	    {
	      Hmcasso_dal->Fill(assmctrk_dal);
	      Hphotonice_dal->Fill(pT);
	    } 
	  
	  
	  //--------------------- start electron ID with BEMC ---------------------------------------------//  
	  
	  StThreeVectorD posEMC, momEMC;
	  bool projEMC = mEmcPosition->trackOnEmc(&posEMC,&momEMC,track,bField,mEmcGeom[0]->Radius()); 
	  float EMC_x = posEMC.x();      
	  float EMC_y = posEMC.y();      
	  float EMC_pT = sqrt(pow(momEMC.x(),2)+pow(momEMC.y(),2));
	  float EMC_phi = posEMC.phi();
	  
	  cout << "EMC = " << EMC_x << " ; " << EMC_y << " ; " << EMC_phi << endl;
	  
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
	  
	  //cout << "check assosication tarck " << track->id() << " ; "<< projEMC << " ; " << projSMDE << " ; " << projSMDP << endl;
	  cout << "check assosication tarck " << " ; "<< projEMC << " ; " << projSMDE << " ; " << projSMDP << endl;
	  
	  if(projEMC && projSMDE && projSMDP && eta>0.0)   //projection point on the EMC & SMD && eta cuts request 
	    {
	      for(StSPtrVecEmcPointIterator point = bEmcPoints.begin(); point != bEmcPoints.end(); point++) // find associate point of EMC
		{
		  
		  Num_bEMC = Num_bEMC + 1;      
		  
		  float bemc_phi = (*point)->position().phi();
		  float bemc_eta = (*point)->position().pseudoRapidity();
		  float bemc_z = (*point)->position().z();
		  
		  float dis_phi = bemc_phi - SMDP_phi;
		  dis_phi = atan2(sin(dis_phi),cos(dis_phi));
		  float dis_z   = bemc_z   - SMDP_z; 
		  
		  float EMC_r = mEmcGeom[0]->Radius(); 
		  float dis_0 = sqrt(pow((EMC_r*cos(0.05) - EMC_r),2)+pow((EMC_r*sin(0.05)),2));
		  float EMC_x_asso = EMC_r*cos(bemc_phi);  
		  float EMC_y_asso = EMC_r*sin(bemc_phi);  
		  float dis_1 = sqrt(pow((EMC_x_asso-EMC_x) ,2)+pow((EMC_y_asso-EMC_y),2));      
		  
		  float dis_eta = bemc_eta - posSMDE.pseudoRapidity(); 
		  
		  //cout << "point addrees = " << point << endl; 
		  //cout << "assoc_phi = " << bemc_phi << " ; proj_phi = " << EMC_phi << " ; sub = " << dis_phi << endl; 
		  //cout << " dis_0 = " << dis_0 << " ; dis_1 = " << dis_1 << endl;
		  //if( dis_1 < dis_0) cout << "Distance match" << endl;
		  //cout << "dis_eta = " << dis_eta << endl;
		  
		  float r = sqrt(pow(dis_eta,2)+pow(dis_phi,2));
		  cout << "matching r = " << r << endl;		      
		  
		  //if(r<0.05){     
		  if(fabs(dis_phi) < 0.05 && fabs(dis_eta) < 0.05){     
		    //if(dis_1 < dis_0 && fabs(dis_eta) < 0.05){     
		    
		    emctrk = emctrk+1; 				
		    
		    H_dis_phi->Fill(pT,dis_phi);   
		    H_dis_eta->Fill(pT,dis_eta);   
		    
		    //Num_match = Num_match + 1;      
		    HpT[1]->Fill(pT);  
		    
		    cout << "matching "<< endl;
		    //cout << endl;
		    
		    //cout << "start R cut" << endl;
		    // association TPC track and EMC
		    Hmatch[0] -> Fill (pT, dis_phi) ;
		    Hmatch[1] -> Fill (pT, dis_eta) ;
		    
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
			    
			    pID = 1.0;  
			    HpT[3]->Fill(pT);
			    HpT_dEdx[3] -> Fill(pT,val_dEdx);
			    Hele_Z->Fill(Z_vertex);
			    
                            num_ele = num_ele+1; 

			    if(isphotonic==1 && num_ele==1)
			      {
                                H_EMC_phi_eta->Fill(bemc_phi,bemc_eta);
				//*************** Fill for photonic e reco.
				Hphotonice_pho_EMC->Fill(pT);
				Hphotonice_pho_w_EMC->Fill(pT,photonweights(ass_parentpT));
				//*************** Fill for nonphotonic eff calculation.
				Hnonphotonice[1]->Fill(pT);
				Hnonphotonice_w[1]->Fill(pT,Nonphotonicweights(pT));
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
	  
          
	  if(seltrk < 250) 
	    {
	      buff[seltrk][0] = pID; // not use in sim(pID)
	      buff[seltrk][1] = pT;
	      buff[seltrk][2] = track->geometry()->momentum().x(); 
	      buff[seltrk][3] = track->geometry()->momentum().y(); 
	      buff[seltrk][4] = track->geometry()->momentum().z(); 
	      buff[seltrk][5] = track->geometry()->charge(); 
	      buff[seltrk][6] = phi; 
	      buff[seltrk][7] = mom; 
	      buff[seltrk][8] =  gl_track->geometry()->momentum().x();  // get momentum at helix original point 
	      buff[seltrk][9] =  gl_track->geometry()->momentum().y(); 
	      buff[seltrk][10] = gl_track->geometry()->momentum().z(); 
	      buff[seltrk][11] = gl_track->geometry()->helix().origin().x();      // get point of helix 
	      buff[seltrk][12] = gl_track->geometry()->helix().origin().y();
	      buff[seltrk][13] = gl_track->geometry()->helix().origin().z();
	      buff[seltrk][14] = gl_track->key(); 
	      buff[seltrk][15] = gl_track->geometry()->momentum().mag();  
              buff[seltrk][18] = eta;   
              buff[seltrk][19] = val_dEdx;   
              buff[seltrk][20] = isphotonic;   
              buff[seltrk][21] = isdalitz;   
              buff[seltrk][22] = ass_parentpT;   
	      
	    }else{
	      Hover->Fill(1);  
	    }           
	  
	  
          
	  
	  seltrk++;
	}
      
      
    }  // while
   // cout <<"  ======== end of Track loop ============ " << endl; 
   
   
   
   //Hseltrk->Fill(seltrk);  
   
  //int mixloop = seltrk - 1;
   int mixloop = seltrk;
   //if(seltrk>100) mixloop = 100;
   
   
  //================================= Cal. electron Inv. mass ===============
   
   
   
  //TObjArray* gtracks = mMuDstMaker->muDst()->globalTracks() ;    // Create a TObject array containing the primary tracks
  //TObjArrayIter GetglTracks(gtracks) ;                              // Create an iterator to step through the tracks
  //StMuTrack* gtrack ;                                             // Pointer to a track
   
   StGlobalTrack *gtrack;
   
   
   for(int itrk=0; itrk<mixloop; itrk++) // primary electrn track
     {
       cout << "inv. mass loop =" << itrk << endl;
       
       //if(buff[itrk][0]!=1.0)continue; // remove hadron (electron is buff[i][0]==1.0)
       // not apply this cuts for embedding.
       // because if apply this cut, electron efficiency is also included
       
       
       if(buff[itrk][20]==1)HpT_check[0]->Fill(buff[itrk][1]);
       
       
       
       if(fabs(buff[itrk][18])>0.7)continue; // trigger e ; eta is less than 0.7
       //if(buff[itrk][20]!=1.0)continue; // remove not trigger particle
       
       int ecount_opp = 0; 
       int ecount_same = 0; 
       
       // make tag electron helix 
       StThreeVectorD PGlobal1(buff[itrk][8],buff[itrk][9],buff[itrk][10]);
       StThreeVectorD OGlobal1(buff[itrk][11],buff[itrk][12],buff[itrk][13]);
       StPhysicalHelixD helix1(PGlobal1,OGlobal1,bField*tesla,buff[itrk][5]);
       
       
       //while ( ( gtrack = (StMuTrack*)GetglTracks.Next() ) )  // find pair electron in global track
       for(StSPtrVecTrackNodeIterator node = nodes.begin(); node != nodes.end(); node++)
	 {
	   gtrack = dynamic_cast<StGlobalTrack*>((*node)->track(global));
	   if(!gtrack)continue;
	   
	   
	   pair<rcTrackMapIter,rcTrackMapIter> trackBounds = tpcTrackMap->equal_range(gtrack);
	   
	   int ass_pID = 99999;
	   
	   for (rcTrackMapIter trkIt=trackBounds.first; trkIt!=trackBounds.second; ++trkIt) 
	     {
	       StMcTrack*   origTrk = (*trkIt).second->partnerMcTrack();
	       ass_pID =  origTrk->geantId();
	       cout << "ass_pID = " << ass_pID << endl;
	     }
	   
	   unsigned short nHitsFit = gtrack->fitTraits().numberOfFitPoints();
	   unsigned short nHitsPoss = gtrack->numberOfPossiblePoints();
	   float nfitOverMax = (float)nHitsFit/(float)nHitsPoss;
	   
	   float eta = gtrack->geometry()->momentum().pseudoRapidity();
	   float pT = gtrack->geometry()->momentum().perp();
	   float chi2 = gtrack->fitTraits().chi2();
	   int gid = gtrack->key();  

	   if(
	      //fabs(gnsig_e) < 3.0
	      nHitsFit > 15 && nHitsFit < 50 
	      //&& nHitsDedx > 15 && nHitsDedx < 50
	      && chi2 > 0.0 && chi2 < 3.0
	      && fabs(eta)<1.05
	      && nfitOverMax > 0.52 && nfitOverMax < 1.2 
	      && (ass_pID==2 || ass_pID==3)
	      && pT>0.1)
	     {
	       Hchi_check_pair->Fill(chi2);
	       Heta_check_pair->Fill(eta);   
	       
	       float p_charge = gtrack->geometry()->charge();
	       float p_px = gtrack->geometry()->momentum().x();
	       float p_py = gtrack->geometry()->momentum().y();
	       float p_pz = gtrack->geometry()->momentum().z();
	       float p_ox = gtrack->geometry()->helix().origin().x();
	       float p_oy = gtrack->geometry()->helix().origin().y();
	       float p_oz = gtrack->geometry()->helix().origin().z();
	       
	       float sign = p_charge * buff[itrk][5];
	       int signID = 0; // opp
	       if(sign>0)signID = 1; // same 
	       
	       
	       if(buff[itrk][14] == gid) 
		 {
		   cout << endl;  
		   cout << "same track " << endl;
		   cout << "check momx " << p_px<< " ; " << buff[itrk][8] << endl;
		   cout << "check momy " << p_py<< " ; " << buff[itrk][9] << endl;
		   cout << "check orgx " << p_ox<< " ; " << buff[itrk][11] << endl;
		   continue;
		 }                    
	       
	       // make pair electron helix 
	       StThreeVectorD PGlobal2(p_px,p_py,p_pz);
	       StThreeVectorD OGlobal2(p_ox,p_oy,p_oz);
	       StPhysicalHelixD helix2(PGlobal2,OGlobal2,bField*tesla,p_charge);
	       
	       
	       // cal DCA of two tracks
	       pair<double,double> pathLength(helix1.pathLengths(helix2).first, helix1.pathLengths(helix2).second);                 
	       cout << "pathlength = " << pathLength.first << endl;	  
	       
	       float DCAlength = abs(helix1.at(pathLength.first) - helix2.at(pathLength.second));
	       cout << "DCAlength= " << DCAlength << endl;
	       //float DCAlength_mag = (helix1.at(pathLength.first) - helix2.at(pathLength.second)).mag(); // mag() --- same as abs()
	       
	       // get momentum at DCA of two track
	       
	       cout << "bField = " << bField << endl;
	       cout << "testla = " << tesla << endl;
	       
	       StThreeVectorD mom1_DCA = helix1.momentumAt(pathLength.first,  bField*tesla);
	       StThreeVectorD mom2_DCA = helix2.momentumAt(pathLength.second, bField*tesla);
	       
	       //cout << endl;
	       cout << "check total momentum X at DCA = " << mom1_DCA.x() << endl;
	       
	       float tot_mom1 = sqrt(pow(mom1_DCA.x(),2)+pow(mom1_DCA.y(),2)+pow(mom1_DCA.z(),2));
	       float tot_mom2 = sqrt(pow(mom2_DCA.x(),2)+pow(mom2_DCA.y(),2)+pow(mom2_DCA.z(),2));
	       
	       cout << "helix1(tag e) mom ; " << tot_mom1 << " ; " << buff[itrk][15] << endl;  
	       //cout << "helix2(pair e) mom ; " << tot_mom2 << " ; " << gtrack->p().mag() << endl;  
	       cout << "helix2(pair e) mom ; " << tot_mom2 << " ; " << gtrack->geometry()->momentum().mag() << endl;  
	       
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
	       
	       //cout << endl;
	       cout << "Invmass 3D= " << invmass << endl;
	       
	       
	       // cal phi and theta
	       float open_phi = Four1.phi() - Four2.phi(); 
	       float open_theta = Four1.theta() - Four2.theta(); 
	       
	       // <----- check phi
	       Four1.setPz(0);
	       Four2.setPz(0);
	       float open_phi2 = Four1.phi() - Four2.phi(); 
	       
	       //cout << endl;
	       //cout << "check phi ; meth1 = " << open_phi << " ; meth2 = " << open_phi2 << endl;
	       
	       
	       // cal 2D inv mass
	       Four1.setPx(sqrt(pow(mom1_DCA.x(),2)+pow(mom1_DCA.y(),2)));
	       Four1.setPy(0.);
	       Four1.setPz(mom1_DCA.z());
	       
	       Four2.setPx(sqrt(pow(mom2_DCA.x(),2)+pow(mom2_DCA.y(),2)));
	       Four2.setPy(0.);
	       Four2.setPz(mom2_DCA.z());
	       
	       double invmass2D = (Four1+Four2).m();
	       cout << "Invmass 2D= " << invmass2D << endl;
	       
	       // <----- check theta
	       float open_theta2 = Four1.theta() - Four2.theta(); 
	       
	       //cout << endl;
	       //cout << "check theta ; meth1 = " << open_theta << " ; meth2 = " << open_theta2 << endl;
	       
	       // cal opening angle
	       Float_t norm = sqrt(mom1_DCA.mag2()*mom2_DCA.mag2());
	       Float_t dot = mom1_DCA.x()*mom2_DCA.x()+mom1_DCA.y()*mom2_DCA.y()+mom1_DCA.z()*mom2_DCA.z();
	       float pairAngle;
	       if(norm > 0) pairAngle = acos(dot/norm);
	       
	       //<------- check open angle
	       
	       //cout << endl;
	       //cout << "open angle = " << pairAngle << endl;
	       
	       Hopenphi[signID] -> Fill(open_phi);
	       Hopentheta[signID] -> Fill(open_theta);
	       Hopenangle[signID] -> Fill(pairAngle);
	       HDCA[signID] -> Fill(DCAlength);
	       
	       Hopenphi_pT[signID] -> Fill(buff[itrk][1],open_phi);
	       Hopentheta_pT[signID] -> Fill(buff[itrk][1],open_theta);
	       Hopenangle_pT[signID] -> Fill(buff[itrk][1],pairAngle);
	       HDCA_pT[signID] -> Fill(buff[itrk][1],DCAlength);
	       
	       // 
	       Hinvmass_wocut[signID]->Fill(invmass2D);
	       //       
	       
	       if(DCAlength<1.0 &&
		  fabs(open_phi)<0.1 &&
		  fabs(open_theta)<0.05 &&
		  fabs(pairAngle)<0.15 
		  ){
		 Hinvmass[signID]->Fill(invmass2D);
		 
		 //cout << endl;
		 //cout << "org eID = " << buff[itrk][0] << endl; 
		 
		 
		 //--------- check electrons ---------------
		 
		 if(invmass2D<0.1 && signID==0)ecount_opp = ecount_opp+1;
		 if(invmass2D<0.1 && signID==1)ecount_same = ecount_same+1;
		 
		 //cout << "invmass = " << invmass2D << " ; signID = " << signID << " : ecount_same = " << ecount_same << endl;
		 //cout << "invmass = " << invmass2D << " ; signID = " << signID << " : ecount_opp = " << ecount_opp << endl;
		 
		 //-----------------------------------------
		 
		 if(invmass2D < 0.1 && buff[itrk][0]>=2.0)Hcheck_pair->Fill(buff[itrk][1],buff[itrk][0]);
		 
		 if(invmass2D < 0.1 && signID==0)
		   {
		     if(buff[itrk][20]==1)
		       {
			 Hinvmass_pT_Opp[0]->Fill(buff[itrk][1],invmass2D);  // photonic
		       }
		     buff[itrk][16] = 1.0;  // oppsign  
		     //cout << endl;
		     //cout << "invmass = " << invmass << " ; sign =" << sign << " ; e tag = " << buff[itrk][0] << endl;    
		   }
		 
		 if(invmass2D < 0.1 && signID==1)
		   {
		     if(buff[itrk][20]==1)
		       {
			 Hinvmass_pT_Same[0]->Fill(buff[itrk][1],invmass2D);  //photonic
		       }
		     buff[itrk][17] = 1.0;  // samesign 
		     //cout << endl;
		     //cout << "invmass = " << invmass << " ; sign =" << sign << " ; e tag = " << buff[itrk][0] << endl;    
		   }  
		 //cout << "current eID = " << buff[itrk][0] << endl; 
	       } // end of Geo. cut
	       
	     } // end gtrak cuts
	   
	 } // end of pair loop (while)
       
       if(buff[itrk][20]==1.0 && buff[itrk][16]==1.0) // photonic electron opp sign
         {
	   Hphotonice_pho_reco[0]->Fill(buff[itrk][1]);
	   Hphotonice_pho_reco_w[0]->Fill(buff[itrk][1],photonweights(buff[itrk][22]));
	   
	   if(buff[itrk][0]==1.0)
             {
	       Hphotonice_pho_reco_EMC[0]->Fill(buff[itrk][1]);
	       Hphotonice_pho_reco_w_EMC[0]->Fill(buff[itrk][1],photonweights(buff[itrk][22]));
             }
	 }
       
       if(buff[itrk][20]==1.0 && buff[itrk][17]==1.0) // photonic electron same sign
         {
	   Hphotonice_pho_reco[1]->Fill(buff[itrk][1]);
	   Hphotonice_pho_reco_w[1]->Fill(buff[itrk][1],photonweights(buff[itrk][22]));
	   
	   if(buff[itrk][0]==1.0)
	     {
	       Hphotonice_pho_reco_EMC[1]->Fill(buff[itrk][1]);
	       Hphotonice_pho_reco_w_EMC[1]->Fill(buff[itrk][1],photonweights(buff[itrk][22]));
	     }
	 }
       
       /*
	 if(buff[itrk][0]==1.0) HpT_pho[0]->Fill(buff[itrk][1]);  // inclusive
	 if(buff[itrk][0]==1.0 && buff[itrk][16]==1.0)HpT_pho[1]->Fill(buff[itrk][1]);  // opp sign
	 if(buff[itrk][0]==1.0 && buff[itrk][17]==1.0)HpT_pho[2]->Fill(buff[itrk][1]);  // same sign
	 HpT_pho[3]->Fill(buff[itrk][1]);   
      
       */
       
       
    } // end of electron loop (for itrk)
   
   
   
   Hseltrk_all->Fill(alltrk);  
   Hseltrk_TPC->Fill(seltrk);  
   Hseltrk_emc->Fill(emctrk);  
   
   cout << "================== Run  End ======================= " << endl;
   cout << "alltrk = " << alltrk << " ; seltrk = " << seltrk <<" ; emctrk = " << emctrk << endl;
   cout << "=================================================== " << endl;
   
   mEventsProcessed++ ;
   return kStOK ;
   
}


void PhorecoMaker::SetOutFile(const char* filename)
{
    mFileName = filename;
    return;
}

Int_t PhorecoMaker::Finish( )
//PhorecoMaker::Finish( )
{ // Do once at the end the analysis
  
  // Write histograms to disk, output miscellaneous other information
  
  //histogram_output -> Write() ;   // Write all histograms to disk 
  
  //cout << "Total Events Processed in DstMaker " << mEventsProcessed << endl ;
  
if(histogram_output){
	histogram_output->Write();  
	histogram_output->Close();
}


  return kStOk ;  

}


Bool_t PhorecoMaker::PhotonicID(StMcTrack* mcTrack){
    if(!mcTrack) return 0;

    bool shower = mcTrack->isShower();
    bool eminus = mcTrack->geantId() == 3;
    bool eplus = mcTrack->geantId() == 2;
   
   
    bool photonic = false;    
    if(mcTrack->parent() && mcTrack->parent()->stopVertex()){
        photonic = mcTrack->parent()->geantId()==1 
                   && mcTrack->parent()->stopVertex()->numberOfDaughters()==2
                   && mcTrack->parent()->eventGenLabel() == 99999;    
    } 

    return ((eminus || eplus) && !shower && photonic);
}


Bool_t PhorecoMaker::DalitzID(StMcTrack* mcTrack){
    if(!mcTrack) return 0;

    bool shower = mcTrack->isShower();
    bool eminus = mcTrack->geantId() == 3;
    bool eplus = mcTrack->geantId() == 2;

    bool dalitz = false;
    if(mcTrack->parent() && mcTrack->parent()->stopVertex()){
        dalitz = mcTrack->parent()->geantId()==149 
                && mcTrack->parent()->stopVertex()->numberOfDaughters()==3
                && mcTrack->parent()->eventGenLabel() == 99999;    
    } 			
    return ((eminus || eplus) && !shower && dalitz);
}


double PhorecoMaker::photonweights(double pt)
{
	double par[3]={1.554e+11,0.02968,7.29};
	double f=par[0]*pow(1+pt/par[1],-par[2]);
	return f;
}


double PhorecoMaker::Nonphotonicweights(double pt)
{
	double a[5]={5243, 11.07, 45.95, 0.013, 5.999};
	double f=a[0]/pow(exp(-a[1]*pt-a[2]*pt*pt)+pt/a[3],a[4]);
	return f;
}



