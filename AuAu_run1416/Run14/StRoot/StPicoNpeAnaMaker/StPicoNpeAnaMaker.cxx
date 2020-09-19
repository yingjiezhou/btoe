
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "TFile.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "TMVA/MethodCuts.h"
#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoEvent/StPicoBEmcPidTraits.h"
#include "StPicoEvent/StPicoMtdPidTraits.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StPicoEvent/StPicoEmcTrigger.h"
#include "StPicoNpeEventMaker/StPicoNpeEvent.h"
#include "StPicoNpeEventMaker/StElectronPair.h"
#include "StPicoEvent/StPicoEmcTrigger.h"
#include "StBTofUtil/tofPathLength.hh"
#include "StMuDSTMaker/COMMON/StMuTypes.hh"
#include "StLorentzVectorF.hh"
#include "phys_constants.h"
#include "StZDCConstants.h"
#include "SystemOfUnits.h"
#include "StPicoNpeAnaMaker.h"
#include "StNpeCuts.h"
#define Melectron 0.00051099907
#include "StRefMultCorr/StRefMultCorr.h"
#include "StRefMultCorr/CentralityMaker.h"
ClassImp(StPicoNpeAnaMaker)
StPicoNpeAnaMaker::StPicoNpeAnaMaker(char const * name,char const * inputFilesList,
                                     char const * outName, StPicoDstMaker* picoDstMaker):
StMaker(name),mPicoDstMaker(picoDstMaker),mPicoNpeEvent(NULL), mOutFileName(outName), mInputFileList(inputFilesList),
mOutputFile(NULL), mChain(NULL), mEventCounter(0), mNpeCuts(NULL)
{mFmsDbMaker = NULL;}

Int_t StPicoNpeAnaMaker::Init()
{
  
  //ZDCCalib=0;
  //ZDCCalib=1;
  ZDCCalib=2;
  //EPCalib=0;
  //EPCalib=1;
  EPCalib=2;
  std::stringstream ss_z, ss_ep; ss_z << ZDCCalib; ss_ep << EPCalib;
  std::string outBase = mOutFileName.Data();
  //m_fOut = new TFile((outBase + "_zdcCalib" + ss_z.str() + "_epCalib" + ss_ep.str() + ".root").c_str(),"recreate");
  //ZDC Calibration
  char name[500], name1[500];
  for (int is=0;is<8;is++) {
    sprintf(name, "ZDCSMD_east_ver%d",is+1); ZDCSMDHist_east_v[is] = new TH1F(name,name,2050,-50.,2000.);
    sprintf(name, "ZDCSMD_east_hor%d",is+1); ZDCSMDHist_east_h[is] = new TH1F(name,name,2050,-50.,2000.);
    sprintf(name, "ZDCSMD_west_ver%d",is+1); ZDCSMDHist_west_v[is] = new TH1F(name,name,2050,-50.,2000.);
    sprintf(name, "ZDCSMD_west_hor%d",is+1); ZDCSMDHist_west_h[is] = new TH1F(name,name,2050,-50.,2000.);
  }
  ZDCSMDCenterex = zdcconst::zdcsmd_ex0;
  ZDCSMDCenterey = zdcconst::zdcsmd_ey0;
  ZDCSMDCenterwx = zdcconst::zdcsmd_wx0;
  ZDCSMDCenterwy = zdcconst::zdcsmd_wy0;
  std::ifstream goodrunlist("goodruns_wpxl.txt");
  int runnum1; int cnt1=0;
  while(goodrunlist>>runnum1) {
    mGoodRunMap[runnum1] = cnt1; cnt1++;
  }
  NRUNS = mGoodRunMap.size();
  if (ZDCCalib>=1) {
    ZDCSMDBeamCenter = new TProfile2D("ZDCSMDBeamCenter","ZDCSMDBeamCenter", 4,0.5,4.5, 9300, 1507500.5,1516800.5,-20,20,"");
  }
  if (ZDCCalib>=2) {
    TFile* fZDCSMDConstFile = new TFile("zdcsmdBeamCenter.root", "READ");
    ZDCSMDBeamCenterFilled = (TProfile2D*)((TProfile2D *)fZDCSMDConstFile->Get("ZDCSMDBeamCenter"))->Clone("ZDCSMDBeamCenterFilled");
    ZDCSMDBeamCenterFilled->SetDirectory(0);
    fZDCSMDConstFile->Close();
  }
  //EP Calibration
  if (EPCalib==0) {
    //m_fOut->cd(0);
    for (int ic=0;ic<NCENT;ic++) {
      sprintf(name,"ZDCEPRecenter_cent%d_x",ic); ZDCEPRecenter_x[ic] = new TProfile2D(name,name,3.0,-0.5,2.5,  NRUNS,-0.5,NRUNS-0.5,  -20.0,20.0,"");
      sprintf(name,"ZDCEPRecenter_cent%d_y",ic); ZDCEPRecenter_y[ic] = new TProfile2D(name,name,3.0,-0.5,2.5  ,NRUNS,-0.5,NRUNS-0.5,  -20.0,20.0,"");
    }
  }
  else {
    TFile* fEPRecenter = new TFile("eprecenter.root");
    for (int ic=0;ic<NCENT;ic++) {
      sprintf(name,"ZDCEPRecenter_cent%d_x",ic);
      sprintf(name1,"ZDCEPRecenter_cent%d_x_Filled",ic);
      ZDCEPRecenter_x[ic] = (TProfile2D*)((TProfile2D*)fEPRecenter->Get(name))->Clone(name1);
      sprintf(name,"ZDCEPRecenter_cent%d_y",ic);
      sprintf(name1,"ZDCEPRecenter_cent%d_y_Filled",ic);
      ZDCEPRecenter_y[ic] = (TProfile2D*)((TProfile2D*)fEPRecenter->Get(name))->Clone(name1);
      ZDCEPRecenter_x[ic]->SetDirectory(0);
      ZDCEPRecenter_y[ic]->SetDirectory(0);
    }
    ZDCEPRecenterEntries = (TH1F*)fEPRecenter->Get("hZDCEPRecenterEntries"); ZDCEPRecenterEntries->SetDirectory(0);
    fEPRecenter->Close();
    
    //m_fOut->cd(0);
    for (int ic=0;ic<NCENT;ic++) {
      sprintf(name,"ZDCEPRecenterPass1_cent%d_x",ic);
      ZDCEPRecenterPass1_x[ic] = new TProfile2D(name,name,3.0,-0.5,2.5,  NRUNS,-0.5,NRUNS-0.5,  -20.0,20.0,"");
      sprintf(name,"ZDCEPRecenterPass1_cent%d_y",ic);
      ZDCEPRecenterPass1_y[ic] = new TProfile2D(name,name,3.0,-0.5,2.5  ,NRUNS,-0.5,NRUNS-0.5,  -20.0,20.0,"");
    }
  }
  if (EPCalib==1) {
    //m_fOut->cd(0);
    for (int ic=0;ic<NCENT;ic++) {
      sprintf(name,"ZDCEPShift_cent%d_cos",ic);
      ZDCEPShift_cos[ic] = new TProfile2D(name,name,3.0,-0.5,2.5,  9,0.5,9.5,  -2.0,2.0,"");
      sprintf(name,"ZDCEPShift_cent%d_sin",ic);
      ZDCEPShift_sin[ic] = new TProfile2D(name,name,3.0,-0.5,2.5  ,9,0.5,9.5,  -2.0,2.0,"");
    }
  }
  if (EPCalib>=2) {
    TFile* fEPShift = new TFile("eprecenter.root");
    for (int ic=0;ic<NCENT;ic++) {
      sprintf(name,"ZDCEPShift_cent%d_cos",ic);
      sprintf(name1,"ZDCEPShift_cent%d_cos_Filled",ic);
      ZDCEPShift_cos[ic] = (TProfile2D*)((TProfile2D*)fEPShift->Get(name))->Clone(name1);
      sprintf(name,"ZDCEPShift_cent%d_sin",ic);
      sprintf(name1,"ZDCEPShift_cent%d_sin_Filled",ic);
      ZDCEPShift_sin[ic] = (TProfile2D*)((TProfile2D*)fEPShift->Get(name))->Clone(name1);
      ZDCEPShift_cos[ic]->SetDirectory(0);
      ZDCEPShift_sin[ic]->SetDirectory(0);
    }
    fEPShift->Close();
  }
  
  sprintf(name,"ZDCEPPsi");    ZDCEPPsi    = new TH1F(name,"", 100, 0, 2*zdcconst::PI); ZDCEPPsi    ->Sumw2();
  sprintf(name,"ZDCEPPsi_rc"); ZDCEPPsi_rc = new TH1F(name,"", 100, 0, 2*zdcconst::PI); ZDCEPPsi_rc ->Sumw2();
  sprintf(name,"ZDCEPPsi_sh"); ZDCEPPsi_sh = new TH1F(name,"", 100, 0, 2*zdcconst::PI); ZDCEPPsi_sh ->Sumw2();
  
  for (int ic=0;ic<NCENT;ic++) {
    for (int iep=0;iep<NEP;iep++) {
      //            sprintf(name,"ZDCEPPsi_c%d_ep%d",ic,iep);    ZDCEPPsi    [ic][iep] = new TH1F(name,"", 100, 0, 2*zdcconst::PI); ZDCEPPsi    [ic][iep]->Sumw2();
      //          sprintf(name,"ZDCEPPsi_rc_c%d_ep%d",ic,iep); ZDCEPPsi_rc [ic][iep] = new TH1F(name,"", 100, 0, 2*zdcconst::PI); ZDCEPPsi_rc [ic][iep]->Sumw2();
      //sprintf(name,"ZDCEPPsi_sh_c%d_ep%d",ic,iep); ZDCEPPsi_sh [ic][iep] = new TH1F(name,"", 100, 0, 2*zdcconst::PI); ZDCEPPsi_sh [ic][iep]->Sumw2();
    }
    sprintf(name,"ZDCEPdPsi_c%d",ic);    ZDCEPdPsi   [ic] = new TH1F(name,"", 100, 0, 2*zdcconst::PI); ZDCEPdPsi   [ic]->Sumw2();
    sprintf(name,"ZDCEPdPsi_rc_c%d",ic); ZDCEPdPsi_rc[ic] = new TH1F(name,"", 100, 0, 2*zdcconst::PI); ZDCEPdPsi_rc[ic]->Sumw2();
    sprintf(name,"ZDCEPdPsi_sh_c%d",ic); ZDCEPdPsi_sh[ic] = new TH1F(name,"", 100, 0, 2*zdcconst::PI); ZDCEPdPsi_sh[ic]->Sumw2();
    
    sprintf(name,"ZDCEPRes_c%d",ic);     ZDCEPRes    [ic] = new TH1F(name,"", 220, -1.1, 1.1); ZDCEPRes    [ic]->Sumw2();
    sprintf(name,"ZDCEPRes_rc_c%d",ic);  ZDCEPRes_rc [ic] = new TH1F(name,"", 220, -1.1, 1.1); ZDCEPRes_rc [ic]->Sumw2();
    sprintf(name,"ZDCEPRes_sh_c%d",ic);  ZDCEPRes_sh [ic] = new TH1F(name,"", 220, -1.1, 1.1); ZDCEPRes_sh [ic]->Sumw2();
  }
  
  TFile *f_D1 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/EventPlane/root/event_corr_new.root");
  TFile *f_D2 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/EventPlane/root/event_res.root");
  run_centrality_corrx = (TH2F*) f_D1->Get("run_centrality_corrx");
  run_centrality_corrx->SetName("run_centrality_corrx");
  run_centrality_corrx->SetDirectory(0);
  run_centrality_corry = (TH2F*) f_D1->Get("run_centrality_corry");
  run_centrality_corry->SetName("run_centrality_corry");
  run_centrality_corry->SetDirectory(0);
  
  run_centrality_corrx1 = (TH2F*) f_D1->Get("run_centrality_corrx1");
  run_centrality_corrx1->SetName("run_centrality_corrx2");
  run_centrality_corrx1->SetDirectory(0);
  run_centrality_corry1 = (TH2F*) f_D1->Get("run_centrality_corry1");
  run_centrality_corry1->SetName("run_centrality_corry2");
  run_centrality_corry1->SetDirectory(0);
  run_centrality_corrx2 = (TH2F*) f_D1->Get("run_centrality_corrx2");
  run_centrality_corrx2->SetName("run_centrality_corrx2");
  run_centrality_corrx2->SetDirectory(0);
  run_centrality_corry2 = (TH2F*) f_D1->Get("run_centrality_corry2");
  run_centrality_corry2->SetName("run_centrality_corry2");
  run_centrality_corry2->SetDirectory(0);
  centrality_resolution = (TH2F*) f_D2->Get("centrality_resolution");
  centrality_resolution->SetDirectory(0);
  f_D1->Close();
  f_D2->Close();
  cout<< "    =====> Setting Ref Mult " << endl;
  mRefMultCorr = new StRefMultCorr("grefmult_P16id");
  mRefMultCorr->setVzForWeight(6, -6.0, 6.0);
  mRefMultCorr->readScaleForWeight("StRoot/StRefMultCorr/macros/weight_grefmult_vpd30_vpd5_Run14_P16id.txt");
  
  cout<< "    =====> End Ref Mult " << endl;
  mChain = new TChain("PicoDst");
  std::ifstream listOfFiles(mInputFileList.Data());
  if (listOfFiles.is_open())
  {
    std::string file;
    size_t pos;
    while (getline(listOfFiles, file))
    {
      pos = file.find_first_of(" ");
      if (pos!=string::npos ) file.erase(pos,file.length()-pos);
      LOG_INFO << "StPicoNpeAnaMaker - Adding :" << file << endm;
      mChain->Add(file.c_str());
    }
  }
  else
  {
    LOG_ERROR << "StPicoNpeAnaMaker - Could not open list of files. ABORT!" << endm;
    return kStErr;
  }
  //mChain->GetBranch("Event")->SetAutoDelete(kFALSE);
  //mChain->SetBranchAddress("Event", &mPicoDstMaker);
  cout<< "    =====> Setting output as " << mOutFileName.Data() << endl;
  mOutputFile = new TFile(mOutFileName.Data(), "RECREATE");
  mOutputFile->cd();
  cout<< "    =====> Setting NPE cuts " << endl;
  if (!mNpeCuts)mNpeCuts = new StNpeCuts;
  mNpeCuts->init();
  nType =12;
  
  // -------------- USER VARIABLES -------------------------
  cout<< "    =====> Setting User Hist/Trees " << endl;
  
  h1dEvent = new TH1I("h1dEvent", "Number of Events", 11, -1, 10);
  //h1dEventZDCx = new TH1F("h1dEventZDCx", "ZDCx distribution", 1000, 0, 100000);
  h1dEventRefMult = new TH1I("h1dEventRefMult", "RefMult distribution", 1000, 0, 1000);
  h1dEventTrigger = new TH1I("h1dEventTriggert", "Trigger", 10, 0, 10);
  h1dEventCentrality = new TH1I("h1dEventCentrality","h1dEventCentrality",10,0,10);
  h1dTrack = new TH1I("h1dTrack", "Number of Track", 10, 0, 10);
  hHftRatio_n = new TH2F("hHftRatio_n","hHftRatio_n",120,0,12,10,0,10);
  hHftRatio_d = new TH2F("hHftRatio_d","hHftRatio_d",120,0,12,10,0,10);
  hHftRatio_eta_n = new TH2F("hHftRatio_eta_n","hHftRatio_eta_n",250,-1,1,10,0,10);
  hHftRatio_eta_d = new TH2F("hHftRatio_eta_d","hHftRatio_eta_d",250,-1,1,10,0,10);
  hHftRatio_phi_n = new TH2F("hHftRatio_phi_n","hHftRatio_phi_n",200,-1,1,10,0,10);
  hHftRatio_phi_d = new TH2F("hHftRatio_phi_d","hHftRatio_phi_d",200,-1,1,10,0,10);
  hHftRatio_z_n = new TH2F("hHftRatio_z_n","hHftRatio_z_n",600,-6,6,10,0,10);
  hHftRatio_z_d = new TH2F("hHftRatio_z_d","hHftRatio_z_d",600,-6,6,10,0,10);
  //hQaPt = new TH1F("hQaPt","hQaPt",200,0,20);
  //hQaEta= new TH1F("hQaEta","hQaEta",100,-2,2);
  //hQaDca= new TH2F("hQaDca","hQaDca",200,-0.02,0.02,200,0,20);
  //hQaVxZ= new TH1F("hQaVxZ","hQaVxZ",300,-6,6);
  //hQaVxY= new TH1F("hQaVxY","hQaVxY",300,-6,6);
  //hQaVxX= new TH1F("hQaVxX","hQaVxX",300,-6,6);
  hJpsip = new TH2F("hJpsip","hJpsip",500,4,5,300,2.95,3.25);
  hJpsip_ws = new TH2F("hJpsip_ws","hJpsip_ws",500,4,5,300,2.95,3.25);
  hJpsip_1 = new TH2F("hJpsip_1","hJpsip_1",500,4,5,300,2.95,3.25);
  hJpsip_1_ws = new TH2F("hJpsip_1_ws","hJpsip_1_ws",500,4,5,300,2.95,3.25);
  hJpsip_2 = new TH2F("hJpsip_2","hJpsip_2",500,4,5,300,2.95,3.25);
  hJpsip_2_ws = new TH2F("hJpsip_2_ws","hJpsip_2_ws",500,4,5,300,2.95,3.25);
  hQaDcaXY1= new TH2F("hQaDcaXY1","hQaDcaXY1",200,-0.02,0.02,50,0,10);
  hQaDcaXY2= new TH2F("hQaDcaXY2","hQaDcaXY2",200,-0.02,0.02,50,0,10);
  hQaDcaXY3= new TH2F("hQaDcaXY3","hQaDcaXY3",200,-0.02,0.02,50,0,10);
  hQaDcaXY4= new TH2F("hQaDcaXY4","hQaDcaXY4",200,-0.02,0.02,50,0,10);
  hQaDcaXY5= new TH2F("hQaDcaXY5","hQaDcaXY5",200,-0.02,0.02,50,0,10);
  hQaDcaXY6= new TH2F("hQaDcaXY6","hQaDcaXY6",200,-0.02,0.02,50,0,10);
  hQaDcaXY7= new TH2F("hQaDcaXY7","hQaDcaXY7",200,-0.02,0.02,50,0,10);
  hQaDcaXY8= new TH2F("hQaDcaXY8","hQaDcaXY8",200,-0.02,0.02,50,0,10);
  hQaDcaZ1= new TH2F("hQaDcaZ1","hQaDcaZ1",200,-0.02,0.02,50,0,10);
  hQaDcaZ2= new TH2F("hQaDcaZ2","hQaDcaZ2",200,-0.02,0.02,50,0,10);
  hQaDcaZ3= new TH2F("hQaDcaZ3","hQaDcaZ3",200,-0.02,0.02,50,0,10);
  hQaDcaZ4= new TH2F("hQaDcaZ4","hQaDcaZ4",200,-0.02,0.02,50,0,10);
  hQaDcaZ5= new TH2F("hQaDcaZ5","hQaDcaZ5",200,-0.02,0.02,50,0,10);
  hQaDcaZ6= new TH2F("hQaDcaZ6","hQaDcaZ6",200,-0.02,0.02,50,0,10);
  hQaDcaZ7= new TH2F("hQaDcaZ7","hQaDcaZ7",200,-0.02,0.02,50,0,10);
  hQaDcaZ8= new TH2F("hQaDcaZ8","hQaDcaZ8",200,-0.02,0.02,50,0,10);
  hQaLogDca= new TH2F("hQaLogDca","hQaLogDca",600,-6,0,85,0,8.5);
  hQaLogDcaTOF= new TH2F("hQaLogDcaTOF","hQaLogDcaTOF",600,-6,0,85,0,8.5);
  //hQaNHitFit = new TH1F("hQaNHitFit","hQaNHitFit",100,0,100);
  //hQaNHitDedx = new TH1F("hQaNHitDedx","hQaNHitDedx",100,0,100);
  hHadronV1_p = new TH2F("hHadronV1_p","hHadronV1_p",40*4,-TMath::Pi()*4,TMath::Pi()*4,100,-1,1);hHadronV1_p->Sumw2();
  hHadronV1_m = new TH2F("hHadronV1_m","hHadronV1_m",40*4,-TMath::Pi()*4,TMath::Pi()*4,100,-1,1);hHadronV1_m->Sumw2();
  hHadronV2 = new TH2F("hHadronV2","hHadronV2",400,0,20,100,0,TMath::Pi());hHadronV2->Sumw2();
  hHadronV2gweight = new TH2F("hHadronV2gweight","hHadronV2gweight",400,0,20,100,0,TMath::Pi());hHadronV2gweight->Sumw2();
  hInvRes = new TH2F("hInvRes","hInvRes",400,0,20,200,0,10);hInvRes->Sumw2();
  hInvResgweight = new TH2F("hInvResgweight","hInvResgweight",400,0,20,200,0,10);hInvResgweight->Sumw2();
  
  for(int i  =0;i<10;i++){
    hFit[i]  = new TH2F (Form("hFit_%i",i),Form("hFit_%i",i), 200,0,20,300,-13,13);
    //hFit_EH[i]  = new TH2F (Form("hFit_EH_%i",i),Form("hFit_EH_%i",i), 200,0,20,300,-13,13);
    //hFit_MVA[i]  = new TH2F (Form("hFit_MVA_%i",i),Form("hFit_MVA_%i",i), 6500,-13,13,800,-4,4);
    hFit_e[i]  = new TH2F (Form("hFit_e_%i",i),Form("hFit_e_%i",i), 200,0,20,300,-13,13);
    hFit_e_WS[i]  = new TH2F (Form("hFit_e_WS_%i",i),Form("hFit_e_WS_%i",i), 200,0,20,300,-13,13);
    hFit_k[i]  = new TH2F (Form("hFit_k_%i",i),Form("hFit_k_%i",i), 200,0,20,300,-13,13);
    hFit_pi[i]  = new TH2F (Form("hFit_pi_%i",i),Form("hFit_pi_%i",i), 200,0,20,300,-13,13);
    hFit_2pi[i]  = new TH2F (Form("hFit_2pi_%i",i),Form("hFit_2pi_%i",i), 200,0,20,300,-13,13);
    hFit_p[i] = new TH2F (Form("hFit_p_%i",i),Form("hFit_p_%i",i), 200,0,20,300,-13,13);
    
    //hFit2D[i]  = new TH2F (Form("hFit2D_%i",i),Form("hFit2D_%i",i), 200,0,20,400,-4,4);
    //hFit2D_e[i]  = new TH2F (Form("hFit2D_e_%i",i),Form("hFit2D_e_%i",i), 200,0,20,400,-4,4);
    //hFit2D_e_WS[i]  = new TH2F (Form("hFit2D_e_WS_%i",i),Form("hFit2D_e_WS_%i",i), 200,0,20,400,-4,4);
    //hFit2D_k[i]  = new TH2F (Form("hFit2D_k_%i",i),Form("hFit2D_k_%i",i), 200,0,20,400,-4,4);
    //hFit2D_pi[i]  = new TH2F (Form("hFit2D_pi_%i",i),Form("hFit2D_pi_%i",i), 200,0,20,400,-4,4);
    //hFit2D_2pi[i]  = new TH2F (Form("hFit2D_2pi_%i",i),Form("hFit2D_2pi_%i",i), 200,0,20,400,-4,4);
    //hFit2D_p[i] = new TH2F (Form("hFit2D_p_%i",i),Form("hFit2D_p_%i",i), 200,0,20,400,-4,4);
    
  }
  for(int i  =0;i<8;i++){
    //hFit2D[i]  = new TH2F (Form("hFit2D_%i",i),Form("hFit2D_%i",i), 200,0,20,400,-4,4);
    //hFit2D_e[i]  = new TH2F (Form("hFit2D_e_%i",i),Form("hFit2D_e_%i",i), 200,0,20,400,-4,4);
    //hFit2D_e_WS[i]  = new TH2F (Form("hFit2D_e_WS_%i",i),Form("hFit2D_e_WS_%i",i), 200,0,20,400,-4,4);
    //hFit2D_pi[i]  = new TH2F (Form("hFit2D_pi_%i",i),Form("hFit2D_pi_%i",i), 200,0,20,400,-4,4);
    //hDca[i]  = new TH2F (Form("hDca_%i",i),Form("hDca_%i",i),200,0,20,400,-0.2,0.2);
    //hDca_e[i]  = new TH2F (Form("hDca_e_%i",i),Form("hDca_e_%i",i), 200,0,20,400,-0.2,0.2);
    //hDca_e_WS[i]  = new TH2F (Form("hDca_e_WS_%i",i),Form("hDca_e_WS_%i",i),200,0,20,400,-0.2,0.2);
    //hDca_k[i]  = new TH2F (Form("hDca_k_%i",i),Form("hDca_k_%i",i) ,200,0,20,400,-0.2,0.2);
    //hDca_pi[i]  = new TH2F (Form("hDca_pi_%i",i),Form("hDca_pi_%i",i),200,0,20,400,-0.2,0.2 );
    //hDca_2pi[i]  = new TH2F (Form("hDca_2pi_%i",i),Form("hDca_2pi_%i",i),200,0,20,400,-0.2,0.2);
    //hDca_p[i] = new TH2F (Form("hDca_p_%i",i),Form("hDca_p_%i",i),200,0,20,400,-0.2,0.2);
    //hDcaz[i]  = new TH2F (Form("hDcaz_%i",i),Form("hDcaz_%i",i),200,0,20,400,-0.2,0.2);
    //hDcaz_e[i]  = new TH2F (Form("hDcaz_e_%i",i),Form("hDcaz_e_%i",i), 200,0,20,400,-0.2,0.2);
    //hDcaz_e_WS[i]  = new TH2F (Form("hDcaz_e_WS_%i",i),Form("hDcaz_e_WS_%i",i),200,0,20,400,-0.2,0.2);
    //hDcaz_k[i]  = new TH2F (Form("hDcaz_k_%i",i),Form("hDcaz_k_%i",i) ,200,0,20,400,-0.2,0.2);
    //hDcaz_pi[i]  = new TH2F (Form("hDcaz_pi_%i",i),Form("hDcaz_pi_%i",i),200,0,20,400,-0.2,0.2 );
    //hDcaz_2pi[i]  = new TH2F (Form("hDcaz_2pi_%i",i),Form("hDcaz_2pi_%i",i),200,0,20,400,-0.2,0.2);
    //hDcaz_p[i] = new TH2F (Form("hDcaz_p_%i",i),Form("hDcaz_p_%i",i),200,0,20,400,-0.2,0.2);
    //hDca3D[i]  = new TH2F (Form("hDca3D_%i",i),Form("hDca3D_%i",i),200,0,20,500,0,0.5);
    //hDca3D_e[i]  = new TH2F (Form("hDca3D_e_%i",i),Form("hDca3D_e_%i",i), 200,0,20,500,0,5);
    //hDca3D_e_WS[i]  = new TH2F (Form("hDca3D_e_WS_%i",i),Form("hDca3D_e_WS_%i",i),200,0,20,500,0,5);
    //hDca3D_k[i]  = new TH2F (Form("hDca3D_k_%i",i),Form("hDca3D_k_%i",i) ,200,0,20,500,0,5);
    //hDca3D_pi[i]  = new TH2F (Form("hDca3D_pi_%i",i),Form("hDca3D_pi_%i",i),200,0,20,500,0,5);
    //hDca3D_2pi[i]  = new TH2F (Form("hDca3D_2pi_%i",i),Form("hDca3D_2pi_%i",i),200,0,20,500,0,5);
    //hDca3D_p[i] = new TH2F (Form("hDca3D_p_%i",i),Form("hDca3D_p_%i",i),200,0,20,500,0,0.5);
    hDcaLog3D[i]  = new TH2F (Form("hDcaLog3D_%i",i),Form("hDcaLog3D_%i",i),200,0,20,600,-6,0);
    hDcaLog3D_e[i]  = new TH2F (Form("hDcaLog3D_e_%i",i),Form("hDcaLog3D_e_%i",i), 200,0,20,600,-6,0);
    hDcaLog3D_e_WS[i]  = new TH2F (Form("hDcaLog3D_e_WS_%i",i),Form("hDcaLog3D_e_WS_%i",i),200,0,20,600,-6,0);
    //hDcaLog3D_k[i]  = new TH2F (Form("hDcaLog3D_k_%i",i),Form("hDcaLog3D_k_%i",i) ,200,0,20,600,-6,0);
    hDcaLog3D_pi[i]  = new TH2F (Form("hDcaLog3D_pi_%i",i),Form("hDcaLog3D_pi_%i",i),200,0,20,600,-6,0);
    //hDcaLog3D_2pi[i]  = new TH2F (Form("hDcaLog3D_2pi_%i",i),Form("hDcaLog3D_2pi_%i",i),200,0,20,600,-6,0);
    //hDcaLog3D_p[i] = new TH2F (Form("hDcaLog3D_p_%i",i),Form("hDcaLog3D_p_%i",i),200,0,20,600,-6,0);
  }
  //hBeta = new TH2F("hBeta","",200,0,20,500,0.8,1.6);
  //hMVA= new TH1F("hMVA","",1000,-2,2);
  //hnSigma = new TH2F("hnSigma","",200,0,20,500,-15,15);
  //hEoverP_all = new TH1F("hEoverP_all","hEoverP_all",100,0,3);
  //hBTOWId = new TH1F("hBTOWId","hBTOWId",4800,0,4800);
  //hBAdc = new TH1F("hBAdc","hBAdc",1000,0,1000);
  //hDsmAdc = new TH2F("hDsmAdc","hDsmAdc",100,0,100,1,0,4800);
  //hBnEta = new TH1F("hBnEta","hBnEta",10,0,10);
  //hBnPhi = new TH1F("hBnPhi","hBnPhi",10,0,10);
  //hBPhiDist = new TH1F("hBPhiDist","hBPhiDist",100,-.1,.1);
  //hBZDist = new TH1F("hBZDist","hBZDist",1000,-10,10);
  //hRunID = new TH1F("hRunID","hRunID",100000,0,100000);
  //M2 = new TH1F("M2","",750,-.5,1);
  hEventPlane_Res = new TH2F("EventPlane_Res","EventPlane_Res",9,0,9,400,-1,1);
  hEventPlane_Corr1 = new TH1F("EventPlane_Corr1","EventPlane_Corr1",315,0,3.15);
  hEventPlane_Corr2= new TH1F("EventPlane_Corr2","EventPlane_Corr2",315,0,3.15);
  hEventPlane= new TH1F("EventPlane","EventPlane",315,0,3.15);
  Event_tree = new TTree("Event","Event Tree");
  Event_tree->Branch("event_centrality",&ep_event_centrality,"event_centrality/F");
  Event_tree->Branch("event_qx1",&ep_event_qx1,"event_qx1/F");
  Event_tree->Branch("event_qx2",&ep_event_qx2,"event_qx2/F");
  Event_tree->Branch("event_qx",&ep_event_qx,"event_qx/F");
  Event_tree->Branch("event_qy1",&ep_event_qy1,"event_qy1/F");
  Event_tree->Branch("event_qy2",&ep_event_qy2,"event_qy2/F");
  Event_tree->Branch("event_qy",&ep_event_qy,"event_qy/F");
  Event_tree->Branch("run_id",&ep_run_id,"run_id/F");
  
  /*     EH_tree = new TTree("EH","electron hadron Tree");
   EH_tree->Branch("eh_dca",&eh_dca,"eh_dca/F");
   EH_tree->Branch("eh_event_gweight",&eh_event_gweight,"eh_event_gweight/F");
   EH_tree->Branch("eh_e_dcaxy",&eh_e_dcaxy,"eh_e_dcaxy/F");
   EH_tree->Branch("eh_e_dca",&eh_e_dca,"eh_e_dca/F");
   EH_tree->Branch("eh_h_dcaxy",&eh_h_dcaxy,"eh_h_dcaxy/F");
   EH_tree->Branch("eh_h_dca",&eh_h_dca,"eh_h_dca/F");
   EH_tree->Branch("eh_h_dcaz",&eh_h_dcaz,"eh_h_dcaz/F");
   EH_tree->Branch("eh_e_dcaz",&eh_e_dcaz,"eh_e_dcaz/F");
   EH_tree->Branch("eh_dcaxy",&eh_dcaxy,"eh_dcaxy/F");
   EH_tree->Branch("run_id",&eh_run_id,"run_id/F");
   EH_tree->Branch("eveFnt_qx",&eh_event_qx,"event_qx/F");
   EH_tree->Branch("event_qy",&eh_event_qy,"event_qy/F");
   EH_tree->Branch("event_qx1",&eh_event_qx1,"event_qx1/F");
   EH_tree->Branch("event_qy1",&eh_event_qy1,"event_qy1/F");
   EH_tree->Branch("event_qx2",&eh_event_qx2,"event_qx2/F");
   EH_tree->Branch("event_qy2",&eh_event_qy2,"event_qy2/F");
   EH_tree->Branch("event_g_qx",&eh_event_g_qx,"event_g_qx/F");
   EH_tree->Branch("event_g_qy",&eh_event_g_qy,"event_g_qy/F");
   
   EH_tree->Branch("event_g_qx1",&eh_event_g_qx1,"event_g_qx1/F");
   EH_tree->Branch("evehnt_g_qy1",&eh_event_g_qy1,"event_g_qy1/F");
   EH_tree->Branch("event_g_qx2",&eh_event_g_qx2,"event_g_qx2/F");
   EH_tree->Branch("event_g_qy2",&eh_event_g_qy2,"event_g_qy2/F");
   EH_tree->Branch("event_centrality",&eh_event_centrality,"event_centrality/F");
   EH_tree->Branch("eh_pair_dca",&eh_pair_dca,"eh_pair_dca/F");
   EH_tree->Branch("eh_pair_decayr",&eh_pair_decayr,"eh_pair_decayr/F");
   EH_tree->Branch("eh_pair_decaypos",&eh_pair_decaypos,"eh_pair_decaypos/F");
   EH_tree->Branch("eh_pair_angle",&eh_pair_angle,"eh_pair_angle/F");
   EH_tree->Branch("eh_pair_thetaangle",&eh_pair_thetaangle,"eh_pair_thetaangle/F");
   EH_tree->Branch("eh_pair_phi",&eh_pair_phi,"eh_pair_phi/F");
   EH_tree->Branch("eh_eta",&eh_phi,"eh_eta/F");
   EH_tree->Branch("eh_phi",&eh_phi,"eh_phi/F");
   EH_tree->Branch("eh_mass",&eh_mass,"eh_mass/F");
   EH_tree->Branch("eh_e_charge",&eh_e_charge,"eh_e_charge/F");
   EH_tree->Branch("eh_h_charge",&eh_h_charge,"eh_h_charge/F");
   EH_tree->Branch("eh_triggercat",&eh_triggercat,"eh_triggercat/F");
   EH_tree->Branch("eh_endvertex_x",&eh_endvertex_x,"eh_endvertex_x/F");
   EH_tree->Branch("eh_endvertex_y",&eh_endvertex_y,"eh_endvertex_y/F");
   EH_tree->Branch("eh_endvertex_z",&eh_endvertex_z,"eh_endvertex_z/F");
   EH_tree->Branch("eh_vertex_x",&eh_vertex_x,"eh_vertex_x/F");
   EH_tree->Branch("eh_vertex_y",&eh_vertex_y,"eh_vertex_y/F");
   EH_tree->Branch("eh_vertex_z",&eh_vertex_z,"eh_vertex_z/F");
   EH_tree->Branch("eh_e_px",&eh_e_px,"eh_e_px/F");
   EH_tree->Branch("eh_e_py",&eh_e_py,"eh_e_py/F");
   EH_tree->Branch("eh_e_pz",&eh_e_pz,"eh_e_pz/F");
   EH_tree->Branch("eh_e_mva",&eh_e_mva,"eh_e_mva/F");
   EH_tree->Branch("eh_h_px",&eh_h_px,"eh_h_px/F");
   EH_tree->Branch("eh_h_py",&eh_h_py,"eh_h_py/F");
   EH_tree->Branch("eh_h_pz",&eh_h_pz,"eh_h_pz/F");
   EH_tree->Branch("eh_h_nsigpi",&eh_h_nsigpi,"eh_h_nsigpi/F");
   EH_tree->Branch("eh_h_nsige",&eh_h_nsige,"eh_h_nsige/F");
   EH_tree->Branch("eh_e_nsige",&eh_e_nsige,"eh_e_nsige/F");
   EH_tree->Branch("eh_h_nsigk",&eh_h_nsigk,"eh_h_nsigk/F");
   EH_tree->Branch("eh_h_beta",&eh_h_beta,"eh_h_beta/F");
   EH_tree->Branch("eh_h_isprimary",&eh_h_isprimary,"eh_h_isprimary/F");
   EH_tree->Branch("eh_e_isprimary",&eh_e_isprimary,"eh_e_isprimary/F");
   EH_tree->Branch("eh_ncan",&eh_ncan,"eh_ncan/F");    */
  Signal_tree = new TTree("Signal","Signal Tree");
  Signal_tree->Branch("sig_dca",&sig_dca,"sig_dca/F");
  Signal_tree->Branch("sig_p",&sig_p,"sig_p/F");
  Signal_tree->Branch("event_ep1",&event_ep1,"event_ep1/F");
  Signal_tree->Branch("sig_chi2",&sig_chi2,"sig_chi2/F");
  Signal_tree->Branch("sig_isiso",&sig_isiso,"sig_isiso/F");
  Signal_tree->Branch("sig_triggercat",&sig_triggercat,"sig_triggercat/F");
  Signal_tree->Branch("sig_pt",&sig_pt,"sig_pt/F");
  Signal_tree->Branch("sig_dcaxy",&sig_dcaxy,"sig_dcaxy/F");
  Signal_tree->Branch("sig_dcaz",&sig_dcaz,"sig_dcaz/F");
  Signal_tree->Branch("sig_nsige",&sig_nsige,"sig_nsige/F");
  Signal_tree->Branch("sig_nsigpi",&sig_nsigpi,"sig_nsigpi/F");
  Signal_tree->Branch("sig_nsigk",&sig_nsigk,"sig_nsigk/F");
  Signal_tree->Branch("sig_nsigp",&sig_nsigp,"sig_nsigp/F");
  Signal_tree->Branch("sig_beta",&sig_beta,"sig_beta/F");
  Signal_tree->Branch("sig_emc0",&sig_emc0,"sig_emc0/F");
  Signal_tree->Branch("sig_eta",&sig_eta,"sig_eta/F");
  Signal_tree->Branch("sig_phi",&sig_phi,"sig_phi/F");
  Signal_tree->Branch("sig_phi2",&sig_phi2,"sig_phi2/F");
  Signal_tree->Branch("sig_neta",&sig_neta,"sig_neta/F");
  Signal_tree->Branch("sig_nphi",&sig_nphi,"sig_nphi/F");
  Signal_tree->Branch("sig_charge",&sig_charge,"sig_charge/F");
  Signal_tree->Branch("sig_phidist",&sig_phidist,"sig_phidist/F");
  Signal_tree->Branch("sig_zdist",&sig_zdist,"sig_zdist/F");
  Signal_tree->Branch("sig_mva",&sig_mva,"sig_mva/F");
  //Signal_tree->Branch("sig_mva_ht",&sig_mva_ht,"sig_mva_ht/F");
  Signal_tree->Branch("sig_yloc",&sig_yloc,"sig_yloc/F");
  Signal_tree->Branch("event_centrality",&event_centrality,"event_centrality/F");
  Signal_tree->Branch("event_qx1",&event_qx1,"event_qx1/F");
  Signal_tree->Branch("event_qx2",&event_qx2,"event_qx2/F");
  Signal_tree->Branch("event_qx",&event_qx,"event_qx/F");
  Signal_tree->Branch("event_qy1",&event_qy1,"event_qy1/F");
  Signal_tree->Branch("event_qy2",&event_qy2,"event_qy2/F");
  Signal_tree->Branch("event_qy",&event_qy,"event_qy/F");
  Signal_tree->Branch("event_gweight",&event_gweight,"event_gweight/F");
  Signal_tree->Branch("event_g_qx1",&event_g_qx1,"event_g_qx1/F");
  Signal_tree->Branch("event_g_qx2",&event_g_qx2,"event_g_qx2/F");
  Signal_tree->Branch("event_g_qx",&event_g_qx,"event_g_qx/F");
  Signal_tree->Branch("event_g_qy1",&event_g_qy1,"event_g_qy1/F");
  Signal_tree->Branch("event_g_qy2",&event_g_qy2,"event_g_qy2/F");
  Signal_tree->Branch("event_g_qy",&event_g_qy,"event_g_qy/F");
  Signal_tree->Branch("run_id",&run_id,"run_id/F");
  Signal_tree->Branch("event_id",&event_id,"event_id/F");
  Signal_tree->Branch("trigger_id",&sig_trigger_id,"trigger_id/F");
  /*     JPsi_tree = new TTree("JPsi","JPsi Tree");
   JPsi_tree->Branch("JPsi_M",&JPsi_M,"JPsi_M/F");
   JPsi_tree->Branch("probe_p",&probe_p,"probe_p/F");
   JPsi_tree->Branch("probe_pt",&probe_pt,"probe_pt/F");
   JPsi_tree->Branch("probe_dcaxy",&probe_dcaxy,"probe_dcaxy/F");
   JPsi_tree->Branch("probe_dca",&probe_dca,"probe_dca/F");
   JPsi_tree->Branch("probe_nsige",&probe_nsige,"probe_nsige/F");
   JPsi_tree->Branch("probe_nsigpi",&probe_nsigpi,"probe_nsigpi/F");
   JPsi_tree->Branch("probe_nsigk",&probe_nsigk,"probe_nsigk/F");
   JPsi_tree->Branch("probe_nsigp",&probe_nsigp,"probe_nsigp/F");
   JPsi_tree->Branch("probe_beta",&probe_beta,"probe_beta/F");
   JPsi_tree->Branch("probe_emc0",&probe_emc0,"probe_emc0/F");
   JPsi_tree->Branch("probe_neta",&probe_neta,"probe_neta/F");
   JPsi_tree->Branch("probe_nphi",&probe_nphi,"probe_nphi/F");
   JPsi_tree->Branch("probe_charge",&probe_charge,"probe_charge/F");
   JPsi_tree->Branch("probe_phidist",&probe_phidist,"probe_phidist/F");
   JPsi_tree->Branch("probe_zdist",&probe_zdist,"probe_zdist/F");
   JPsi_tree->Branch("tag_charge",&tag_charge,"tag_charge/F");
   JPsi_tree->Branch("tag_beta",&tag_beta,"tag_beta/F");
   JPsi_tree->Branch("tag_mva",&tag_mva,"tag_mva/F");
   JPsi_tree->Branch("tag_trigger",&tag_trigger,"tag_trigger/F");
   JPsi_tree->Branch("pair_dca",&pair_dca,"pair_dca/F");
   JPsi_tree->Branch("pair_theta",&pair_theta,"pair_theta/F");
   JPsi_tree->Branch("probe_ncan",&probe_ncan,"probe_ncan/F");
   JPsi_tree->Branch("probe_mva",&probe_mva,"probe_mva/F");
   JPsi_tree->Branch("probe_yloc",&probe_yloc,"probe_yloc/F");
   */
  Ks_tree = new TTree("Ks","Ks Tree");
  Ks_tree->Branch("Ks_M",&Ks_M,"Ks_M/F");
  Ks_tree->Branch("probe_triggercat",&Ks_triggercat,"probe_triggercat/F");
  Ks_tree->Branch("probe_p",&Ks_probe_p,"probe_p/F");
  Ks_tree->Branch("tag_p",&Ks_tag_p,"tag_p/F");
  Ks_tree->Branch("probe_pt",&Ks_probe_pt,"probe_pt/F");
  Ks_tree->Branch("probe_dcaxy",&Ks_probe_dcaxy,"probe_dcaxy/F");
  Ks_tree->Branch("probe_dca",&Ks_probe_dca,"probe_dca/F");
  Ks_tree->Branch("probe_nsige",&Ks_probe_nsige,"probe_nsige/F");
  Ks_tree->Branch("probe_nsigpi",&Ks_probe_nsigpi,"probe_nsigpi/F");
  Ks_tree->Branch("probe_nsigk",&Ks_probe_nsigk,"probe_nsigk/F");
  Ks_tree->Branch("probe_nsigp",&Ks_probe_nsigp,"probe_nsigp/F");
  Ks_tree->Branch("probe_beta",&Ks_probe_beta,"probe_beta/F");
  Ks_tree->Branch("probe_emc0",&Ks_probe_emc0,"probe_emc0/F");
  Ks_tree->Branch("probe_neta",&Ks_probe_neta,"probe_neta/F");
  Ks_tree->Branch("probe_nphi",&Ks_probe_nphi,"probe_nphi/F");
  Ks_tree->Branch("probe_phi",&Ks_probe_phi,"probe_phi/F");
  Ks_tree->Branch("probe_charge",&Ks_probe_charge,"probe_charge/F");
  Ks_tree->Branch("probe_phidist",&Ks_probe_phidist,"probe_phidist/F");
  Ks_tree->Branch("probe_zdist",&Ks_probe_zdist,"probe_zdist/F");
  Ks_tree->Branch("tag_charge",&Ks_tag_charge,"tag_charge/F");
  Ks_tree->Branch("tag_beta",&Ks_tag_beta,"tag_beta/F");
  Ks_tree->Branch("tag_mva",&Ks_tag_mva,"tag_mva/F");
  Ks_tree->Branch("tag_trigger",&Ks_tag_trigger,"tag_trigger/F");
  Ks_tree->Branch("pair_dca",&Ks_pair_dca,"pair_dca/F");
  Ks_tree->Branch("pair_theta",&Ks_pair_theta,"pair_theta/F");
  Ks_tree->Branch("probe_ncan",&Ks_probe_ncan,"probe_ncan/F");
  Ks_tree->Branch("probe_mva",&Ks_probe_mva,"probe_mva/F");
  Ks_tree->Branch("probe_yloc",&Ks_probe_yloc,"probe_yloc/F");
  /*
   Phi_tree = new TTree("Phi","Phi Tree");
   Phi_tree->Branch("Phi_M",&Phi_M,"Phi_M/F");
   Phi_tree->Branch("probe_triggercat",&Phi_triggercat,"probe_triggercat/F");
   Phi_tree->Branch("probe_p",&Phi_probe_p,"probe_p/F");
   Phi_tree->Branch("probe_pt",&Phi_probe_pt,"probe_pt/F");
   Phi_tree->Branch("probe_dcaxy",&Phi_probe_dcaxy,"probe_dcaxy/F");
   Phi_tree->Branch("probe_dca",&Phi_probe_dca,"probe_dca/F");
   Phi_tree->Branch("probe_nsige",&Phi_probe_nsige,"probe_nsige/F");
   Phi_tree->Branch("probe_nsigpi",&Phi_probe_nsigpi,"probe_nsigpi/F");
   Phi_tree->Branch("probe_nsigk",&Phi_probe_nsigk,"probe_nsigk/F");
   Phi_tree->Branch("probe_nsigp",&Phi_probe_nsigp,"probe_nsigp/F");
   Phi_tree->Branch("probe_beta",&Phi_probe_beta,"probe_beta/F");
   Phi_tree->Branch("probe_emc0",&Phi_probe_emc0,"probe_emc0/F");
   Phi_tree->Branch("probe_neta",&Phi_probe_neta,"probe_neta/F");
   Phi_tree->Branch("probe_nphi",&Phi_probe_nphi,"probe_nphi/F");
   Phi_tree->Branch("probe_charge",&Phi_probe_charge,"probe_charge/F");
   Phi_tree->Branch("probe_phidist",&Phi_probe_phidist,"probe_phidist/F");
   Phi_tree->Branch("probe_zdist",&Phi_probe_zdist,"probe_zdist/F");
   Phi_tree->Branch("tag_charge",&Phi_tag_charge,"tag_charge/F");
   Phi_tree->Branch("tag_beta",&Phi_tag_beta,"tag_beta/F");
   Phi_tree->Branch("tag_mva",&Phi_tag_mva,"tag_mva/F");
   Phi_tree->Branch("tag_trigger",&Phi_tag_trigger,"tag_trigger/F");
   Phi_tree->Branch("pair_dca",&Phi_pair_dca,"pair_dca/F");
   Phi_tree->Branch("pair_theta",&Phi_pair_theta,"pair_theta/F");
   Phi_tree->Branch("probe_ncan",&Phi_probe_ncan,"probe_ncan/F");
   Phi_tree->Branch("probe_mva",&Phi_probe_mva,"probe_mva/F");
   Phi_tree->Branch("probe_yloc",&Phi_probe_yloc,"probe_yloc/F");
   
   Lambda_tree = new TTree("Lambda","Lambda Tree");
   Lambda_tree->Branch("Lambda_M",&Lambda_M,"Lambda_M/F");
   Lambda_tree->Branch("probe_triggercat",&Lambda_triggercat,"probe_triggercat/F");
   Lambda_tree->Branch("probe_p",&Lambda_probe_p,"probe_p/F");
   Lambda_tree->Branch("probe_pt",&Lambda_probe_pt,"probe_pt/F");
   Lambda_tree->Branch("probe_dcaxy",&Lambda_probe_dcaxy,"probe_dcaxy/F");
   Lambda_tree->Branch("probe_dca",&Lambda_probe_dca,"probe_dca/F");
   Lambda_tree->Branch("probe_nsige",&Lambda_probe_nsige,"probe_nsige/F");
   Lambda_tree->Branch("probe_nsigpi",&Lambda_probe_nsigpi,"probe_nsigpi/F");
   Lambda_tree->Branch("probe_nsigk",&Lambda_probe_nsigk,"probe_nsigk/F");
   Lambda_tree->Branch("probe_nsigp",&Lambda_probe_nsigp,"probe_nsigp/F");
   Lambda_tree->Branch("probe_beta",&Lambda_probe_beta,"probe_beta/F");
   Lambda_tree->Branch("probe_emc0",&Lambda_probe_emc0,"probe_emc0/F");
   Lambda_tree->Branch("probe_neta",&Lambda_probe_neta,"probe_neta/F");
   Lambda_tree->Branch("probe_nphi",&Lambda_probe_nphi,"probe_nphi/F");
   Lambda_tree->Branch("probe_charge",&Lambda_probe_charge,"probe_charge/F");
   Lambda_tree->Branch("probe_phidist",&Lambda_probe_phidist,"probe_phidist/F");
   Lambda_tree->Branch("probe_zdist",&Lambda_probe_zdist,"probe_zdist/F");
   Lambda_tree->Branch("tag_charge",&Lambda_tag_charge,"tag_charge/F");
   Lambda_tree->Branch("tag_beta",&Lambda_tag_beta,"tag_beta/F");
   Lambda_tree->Branch("tag_mva",&Lambda_tag_mva,"tag_mva/F");
   Lambda_tree->Branch("tag_trigger",&Lambda_tag_trigger,"tag_trigger/F");
   Lambda_tree->Branch("pair_dca",&Lambda_pair_dca,"pair_dca/F");
   Lambda_tree->Branch("pair_theta",&Lambda_pair_theta,"pair_theta/F");
   Lambda_tree->Branch("probe_ncan",&Lambda_probe_ncan,"probe_ncan/F");
   Lambda_tree->Branch("probe_mva",&Lambda_probe_mva,"probe_mva/F");
   Lambda_tree->Branch("probe_yloc",&Lambda_probe_yloc,"probe_yloc/F");
   */
  PhoE_tree = new TTree("PhoE","PhoE Tree");
  PhoE_tree->Branch("PhoE_M",&PhoE_M,"PhoE_M/F");
  PhoE_tree->Branch("pair_decayradius",&phoe_pair_decayradius,"pair_decayradius/F");
  PhoE_tree->Branch("pair_dca",&phoe_pair_dca,"pair_dca/F");
  PhoE_tree->Branch("probe_triggercat",&phoe_triggercat,"probe_triggercat/F");
  PhoE_tree->Branch("pair_theta",&phoe_pair_theta,"pair_theta/F");
  PhoE_tree->Branch("pair_phi",&phoe_pair_phi,"pair_phi/F");
  PhoE_tree->Branch("pair_costheta",&phoe_pair_costheta,"pair_costheta/F");
  PhoE_tree->Branch("probe_p",&phoe_probe_p,"probe_p/F");
  PhoE_tree->Branch("probe_pt",&phoe_probe_pt,"probe_pt/F");
  PhoE_tree->Branch("probe_dcaxy",&phoe_probe_dcaxy,"probe_dcaxy/F");
  PhoE_tree->Branch("probe_dca",&phoe_probe_dca,"probe_dca/F");
  PhoE_tree->Branch("probe_dcaz",&phoe_probe_dcaz,"probe_dcaz/F");
  PhoE_tree->Branch("probe_nsige",&phoe_probe_nsige,"probe_nsige/F");
  PhoE_tree->Branch("probe_nsigpi",&phoe_probe_nsigpi,"probe_nsigpi/F");
  PhoE_tree->Branch("probe_nsigk",&phoe_probe_nsigk,"probe_nsigk/F");
  PhoE_tree->Branch("probe_nsigp",&phoe_probe_nsigp,"probe_nsigp/F");
  PhoE_tree->Branch("probe_beta",&phoe_probe_beta,"probe_beta/F");
  PhoE_tree->Branch("probe_emc0",&phoe_probe_emc0,"probe_emc0/F");
  PhoE_tree->Branch("probe_neta",&phoe_probe_neta,"probe_neta/F");
  PhoE_tree->Branch("probe_nphi",&phoe_probe_nphi,"probe_nphi/F");
  PhoE_tree->Branch("probe_phi",&phoe_probe_phi,"probe_phi/F");
  PhoE_tree->Branch("probe_charge",&phoe_probe_charge,"probe_charge/F");
  PhoE_tree->Branch("tag_charge",&phoe_tag_charge,"tag_charge/F");
  PhoE_tree->Branch("tag_beta",&phoe_tag_beta,"tag_beta/F");
  PhoE_tree->Branch("tag_mva",&phoe_tag_mva,"tag_mva/F");
  PhoE_tree->Branch("probe_phidist",&phoe_probe_phidist,"probe_phidist/F");
  PhoE_tree->Branch("probe_zdist",&phoe_probe_zdist,"probe_zdist/F");
  PhoE_tree->Branch("probe_ncan",&phoe_probe_ncan,"probe_ncan/F");
  PhoE_tree->Branch("probe_mva",&phoe_probe_mva,"probe_mva/F");
  PhoE_tree->Branch("probe_yloc",&phoe_probe_yloc,"probe_yloc/F");
  PhoE_tree->Branch("probe_chi2",&phoe_probe_chi2,"probe_chi2/F");
  PhoE_tree->Branch("tag_chi2",&phoe_tag_chi2,"tag_chi2/F");
  PhoE_tree->Branch("run_id",&phoe_run_id,"run_id/F");
  PhoE_tree->Branch("event_qx",&phoe_event_qx,"event_qx/F");
  PhoE_tree->Branch("event_qy",&phoe_event_qy,"event_qy/F");
  PhoE_tree->Branch("event_qx1",&phoe_event_qx1,"event_qx1/F");
  PhoE_tree->Branch("event_qy1",&phoe_event_qy1,"event_qy1/F");
  PhoE_tree->Branch("event_qx2",&phoe_event_qx2,"event_qx2/F");
  PhoE_tree->Branch("event_qy2",&phoe_event_qy2,"event_qy2/F");
  PhoE_tree->Branch("event_gweight",&phoe_event_gweight,"event_gweight/F");
  PhoE_tree->Branch("event_centrality",&phoe_event_centrality,"event_centrality/F");
  PhoE_tree->Branch("trigger_id",&phoe_trigger_id,"trigger_id/F");
  
  /*
   BKG_tree = new TTree("BKG","BKG Tree");
   BKG_tree->Branch("probe_p",&bkg_probe_p,"probe_p/F");
   BKG_tree->Branch("probe_phi",&bkg_probe_phi,"probe_phi/F");
   BKG_tree->Branch("probe_phi2",&bkg_probe_phi2,"probe_phi2/F");
   BKG_tree->Branch("probe_pt",&bkg_probe_pt,"probe_pt/F");
   BKG_tree->Branch("probe_triggercat",&bkg_triggercat,"probe_triggercat/F");
   BKG_tree->Branch("probe_dcaxy",&bkg_probe_dcaxy,"probe_dcaxy/F");
   BKG_tree->Branch("probe_dca",&bkg_probe_dca,"probe_dca/F");
   BKG_tree->Branch("probe_dcaz",&bkg_probe_dcaz,"probe_dcaz/F");
   BKG_tree->Branch("probe_nsige",&bkg_probe_nsige,"probe_nsige/F");
   BKG_tree->Branch("probe_nsigpi",&bkg_probe_nsigpi,"probe_nsigpi/F");
   BKG_tree->Branch("probe_nsigk",&bkg_probe_nsigk,"probe_nsigk/F");
   BKG_tree->Branch("probe_nsigp",&bkg_probe_nsigp,"probe_nsigp/F");
   BKG_tree->Branch("probe_beta",&bkg_probe_beta,"probe_beta/F");
   BKG_tree->Branch("probe_emc0",&bkg_probe_emc0,"probe_emc0/F");
   BKG_tree->Branch("probe_neta",&bkg_probe_neta,"probe_neta/F");
   BKG_tree->Branch("probe_nphi",&bkg_probe_nphi,"probe_nphi/F");
   BKG_tree->Branch("probe_charge",&bkg_probe_charge,"probe_charge/F");
   BKG_tree->Branch("probe_phidist",&bkg_probe_phidist,"probe_phidist/F");
   BKG_tree->Branch("probe_zdist",&bkg_probe_zdist,"probe_zdist/F");
   BKG_tree->Branch("probe_bkgcat",&bkg_probe_bkgcat,"probe_bkgcat/F");
   BKG_tree->Branch("probe_mva",&bkg_probe_mva,"probe_mva/F");
   BKG_tree->Branch("probe_yloc",&bkg_probe_yloc,"probe_yloc/F");
   BKG_tree->Branch("run_id",&bkg_run_id,"run_id/F");
   BKG_tree->Branch("probe_eta",&bkg_probe_eta,"probe_eta/F");
   BKG_tree->Branch("event_centrality",&bkg_event_centrality,"event_centrality/F");
   BKG_tree->Branch("event_qx1",&bkg_event_qx1,"event_qx1/F");
   BKG_tree->Branch("event_qx2",&bkg_event_qx2,"event_qx2/F");
   BKG_tree->Branch("event_qx",&bkg_event_qx,"event_qx/F");
   BKG_tree->Branch("event_qy1",&bkg_event_qy1,"event_qy1/F");
   BKG_tree->Branch("event_qy2",&bkg_event_qy2,"event_qy2/F");
   BKG_tree->Branch("event_qy",&bkg_event_qy,"event_qy/F");  */
  cout<< "    =====> Done with Hist/Trees " << endl;
  return kStOK;
}
//-----------------------------------------------------------------------------
StPicoNpeAnaMaker::~StPicoNpeAnaMaker()
{
  /*  */
}
//-----------------------------------------------------------------------------
Int_t StPicoNpeAnaMaker::Finish()
{
  LOG_INFO << " StPicoNpeAnaMaker - writing data and closing output file " <<endm;
  mOutputFile->cd();
  // --------------- USER HISTOGRAM WRITE --------------------
  h1dEvent->Write();
  hEventPlane_Corr1->Write();
  hEventPlane_Corr2->Write();
  hEventPlane_Res->Write();
  hEventPlane->Write();
  h1dEventRefMult->Write();
  h1dEventTrigger->Write();
  h1dEventCentrality->Write();
  h1dTrack->Write();
  hJpsip->Write();
  hJpsip_ws->Write();
  hJpsip_1->Write();
  hJpsip_1_ws->Write();
  hJpsip_2->Write();
  hJpsip_2_ws->Write();
  //hQaPt->Write();
  //hQaEta->Write();
  //hQaDca->Write();
  //hQaVxZ->Write();
  //hQaVxY->Write();
  //hQaVxX->Write();
  hQaDcaXY1->Write();
  hQaDcaXY2->Write();
  hQaDcaXY3->Write();
  hQaDcaXY4->Write();
  hQaDcaXY5->Write();
  hQaDcaXY6->Write();
  hQaDcaXY7->Write();
  hQaDcaXY8->Write();
  hQaDcaZ1->Write();
  hQaDcaZ2->Write();
  hQaDcaZ3->Write();
  hQaDcaZ4->Write();
  hQaDcaZ5->Write();
  hQaDcaZ6->Write();
  hQaDcaZ7->Write();
  hQaDcaZ8->Write();
  hQaLogDca->Write();
  hQaLogDcaTOF->Write();
  //hQaDcaZ->Write();
  //hQaNHitFit->Write();
  //hEoverP_all->Write();
  //hQaNHitDedx->Write();
  hHadronV1_p->Write();
  hHadronV1_m->Write();
  hHadronV2->Write();
  hHadronV2gweight->Write();
  hInvRes->Write();
  hInvResgweight->Write();
  hHftRatio_n->Write();
  hHftRatio_d->Write();
  hHftRatio_eta_n->Write();
  hHftRatio_eta_d->Write();
  hHftRatio_phi_n->Write();
  hHftRatio_phi_d->Write();
  hHftRatio_z_n->Write();
  hHftRatio_z_d->Write();
  for(int i=0;i<10;i++){
    hFit[i]->Write();
    //hFit_EH[i]->Write();
    //hFit_MVA[i]->Write();
    hFit_e[i]->Write();
    hFit_e_WS[i]->Write();
    hFit_pi[i]->Write();
    hFit_2pi[i]->Write();
    hFit_k[i]->Write();
    hFit_p[i]->Write();
    //hFit2D[i]->Write();
    //hFit2D_e[i]->Write();
    //hFit2D_e_WS[i]->Write();
    //hFit2D_pi[i]->Write();
    //hFit2D_2pi[i]->Write();
    //hFit2D_k[i]->Write();
    //hFit2D_p[i]->Write();
  }
  for(int i=0;i<8;i++){
    //hFit2D[i]->Write();
    //hFit2D_e[i]->Write();
    //hFit2D_e_WS[i]->Write();
    //hFit2D_pi[i]->Write();
    //hDca[i]->Write();
    //hDca_e[i]->Write();
    //hDca_e_WS[i]->Write();
    //hDca_pi[i]->Write();
    //hDca_2pi[i]->Write();
    //hDca_k[i]->Write();
    //hDca_p[i]->Write();
    hDcaLog3D[i]->Write();
    hDcaLog3D_e[i]->Write();
    hDcaLog3D_e_WS[i]->Write();
    hDcaLog3D_pi[i]->Write();
    //hDcaLog3D_2pi[i]->Write();
    //hDcaLog3D_k[i]->Write();
    //hDcaLog3D_p[i]->Write();
    //hDca3D[i]->Write();
    //hDca3D_e[i]->Write();
    //hDca3D_e_WS[i]->Write();
    //hDca3D_pi[i]->Write();
    //hDca3D_2pi[i]->Write();
    //hDca3D_k[i]->Write();
    //hDca3D_p[i]->Write();
    //hDcaz[i]->Write();
    //hDcaz_e[i]->Write();
    //hDcaz_e_WS[i]->Write();
    //hDcaz_pi[i]->Write();
    //hDcaz_2pi[i]->Write();
    //hDcaz_k[i]->Write();
    //hDcaz_p[i]->Write();
  }
  /*    for(int i=0;i<8;i++){
   ZDCSMDHist_east_v[i]->Write();
   ZDCSMDHist_east_h[i]->Write();
   ZDCSMDHist_west_v[i]->Write();
   ZDCSMDHist_west_h[i]->Write();
   }
   
   ZDCSMDBeamCenter->Write();
   ZDCSMDBeamCenterFilled->Write();
   ZDCEPRecenterEntries->Write();
   */
  for(int i = 0 ;i<NCENT;i++){
    //ZDCEPRecenter_x[i]->Write();
    //ZDCEPRecenter_y[i]->Write();
    //ZDCEPRecenterPass1_x[i]->Write();
    //ZDCEPRecenterPass1_y[i]->Write();
    //ZDCEPShift_cos[i]->Write();
    //ZDCEPShift_sin[i]->Write();
    ZDCEPdPsi[i]->Write();
    ZDCEPdPsi_rc[i]->Write();
    ZDCEPdPsi_sh[i]->Write();
    ZDCEPRes[i]->Write();
    ZDCEPRes_rc[i]->Write();
    ZDCEPRes_sh[i]->Write();
    //for(int j = 0; j<NEP;j++){
    //    ZDCEPPsi[i][j]->Write();
    //    ZDCEPPsi_rc[i][j]->Write();
    //    ZDCEPPsi_sh[i][j]->Write();
    //}
  }
  
  ZDCEPPsi->Write();
  ZDCEPPsi_rc->Write();
  ZDCEPPsi_sh->Write();
  //hBTOWId->Write();
  //hBAdc->Write();
  //hDsmAdc->Write();
  //hBnEta->Write();
  //hBnPhi->Write();
  //hBPhiDist->Write();
  //hBZDist->Write();
  //hRunID->Write();
  //hBeta->Write();
  //hMVA->Write();
  //hnSigma->Write();
  //M2->Write();
  //JPsi_tree->Write();
  Ks_tree->Write();
  //Phi_tree->Write();
  //Lambda_tree->Write();
  PhoE_tree->Write();
  //BKG_tree->Write();
  Signal_tree->Write();
  //EH_tree->Write();
  Event_tree->Write();
  mOutputFile->Close();
  return kStOK;
}
//-----------------------------------------------------------------------------
Int_t StPicoNpeAnaMaker::Make()
{
  readNextEvent();
  StPicoDst const* picoDst = mPicoDstMaker->picoDst();
  
  if (!picoDst)
  {
    LOG_WARN << "StPicoNpeAnaMaker - No PicoDst! Skip! " << endm;
    return kStWarn;
  }
  // -------------- USER ANALYSIS -------------------------
  mEP1=-100;
  // check if good event (including bad run)
  bool isHLT1 = false;
  bool isHLT2 = false;
  bool isHLT3 = false;
  bool isMB = false;
  //hRunID->Fill(picoDst->event()->runId());
  if (picoDst->event()->isTrigger(450050) || picoDst->event()->isTrigger(450060) ||
      picoDst->event()->isTrigger(450005) || picoDst->event()->isTrigger(450015) ||
      picoDst->event()->isTrigger(450025)) {
    
    h1dEventTrigger->Fill(1);
    isMB=true;
  } // MB
  if (picoDst->event()->isTrigger(450201) || picoDst->event()->isTrigger(450211) ) {
    
    h1dEventTrigger->Fill(2);
    isHLT1=true;
  }   // BHT1
  if (picoDst->event()->isTrigger(450202) || picoDst->event()->isTrigger(450212) ) {
    
    h1dEventTrigger->Fill(3);
    isHLT2=true;
  }  // BHT2
  if (picoDst->event()->isTrigger(450203) || picoDst->event()->isTrigger(450213) ) {
    
    h1dEventTrigger->Fill(4);
    isHLT3=true;
  }   // BHT3
  h1dEvent->Fill(-1);
  if(!isMB && !isHLT1 && !isHLT2 && !isHLT3)return kStOk; //Selecting events with correct trigger IDs
  h1dEventTrigger->Fill(0);
  TVector3 pVtx = picoDst->event()->primaryVertex();
  mRefMultCorr->init(picoDst->event()->runId());
  mRefMultCorr->initEvent(picoDst->event()->grefMult(),picoDst->event()->vzVpd(),picoDst->event()->ZDCx());
  int mRefMult = picoDst->event()->refMult();
  float mZDCx = picoDst->event()->ZDCx();
  h1dEvent->Fill(0);
  //h1dEventZDCx->Fill(mZDCx);
  h1dEventRefMult->Fill(mRefMult);
  mNpeCuts->setPicoDst(const_cast<const StPicoDst*>(picoDst));
  if(!mNpeCuts->isGoodRun(const_cast<const StPicoDst*>(picoDst)->event()))return kStOk;
  //  if(!( fabs(pVtx.z() - picoDst->event()->vzVpd())<3. && fabs(pVtx.z())<6.))return kStOk;
  h1dEvent->Fill(1.1);
  if(!( fabs(pVtx.z() - picoDst->event()->vzVpd())<3. && fabs(pVtx.z())<6.))return kStOk;
  if(TMath::Abs(pVtx.x()) < 1e-5 && TMath::Abs(pVtx.y()) < 1e-5 && TMath::Abs(pVtx.z() < 1e-5))return kStOk ;
  //if(!mNpeCuts->isGoodEvent(const_cast<const StPicoDst*>(picoDst), NULL))return kStOk;
  h1dEvent->Fill(2.1);
  if(isMB)h1dEvent->Fill(3.1);
  if(isHLT1)h1dEvent->Fill(4.1);
  if(isHLT2)h1dEvent->Fill(5.1);
  if(isHLT3)h1dEvent->Fill(6.1);
  
  float refMultc = mRefMultCorr->getRefMultCorr() ;
  gweight = mRefMultCorr->getWeight() ;
  centrality = mRefMultCorr->getCentralityBin9();
  if (centrality < 0 || centrality > 9) return kStOk;
  h1dEventCentrality->Fill(centrality);
  //hQaVxZ->Fill(pVtx.z());
  //hQaVxY->Fill(pVtx.y());
  //hQaVxX->Fill(pVtx.x());
  std::vector<unsigned short> idxPicoTaggedEs;
  std::vector<unsigned short> idxPicoTaggedEsLoose;
  std::vector<unsigned short> idxPicoPartnerEs;
  std::vector<unsigned short> idxPicoTightEs;
  std::vector<unsigned short> idxPicoTaggedPrs;
  std::vector<unsigned short> idxPicoUnbiasedEs;
  std::vector<unsigned short> idxPicoUnbiasedPs;
  std::vector<unsigned short> idxPicoTaggedPs;
  std::vector<unsigned short> idxPicoTaggedKs;
  //=========== Event Plane Calc. ===============
  double Plane=0;
  double Plane1=0;
  double Plane2=0;
  double Q1_X =0;
  double Q2_X =0;
  double Q1_Y =0;
  double Q2_Y =0;
  double Q_X =0;
  double Q_Y =0;
  
  TF1 random("random","1",0,500);
  int t1 = random.GetRandom();
  int t2 = random.GetRandom();
  int t3 = random.GetRandom();
  int t4 = random.GetRandom();
  int t5 = random.GetRandom();
  if(1){
    bool flag=0;
    for(int is=0;is<8;is++) {
      ZDCSMDHist_east_v[is]->Fill(ZDCSMD(0,0,is));
      ZDCSMDHist_east_h[is]->Fill(ZDCSMD(0,1,is));
      ZDCSMDHist_west_v[is]->Fill(ZDCSMD(1,0,is));
      ZDCSMDHist_west_h[is]->Fill(ZDCSMD(1,1,is));
      if ( (is<7 && ZDCSMD(0,0,is)<1e-4) || (ZDCSMD(0,1,is)<1e-4) || (is<7 && ZDCSMD(1,0,is)<1e-4) || (ZDCSMD(1,1,is)<1e-4) ) flag=1;
    }
    if (flag) {return 0;}
    //------------------------------------------------------------------------
    //---------------- Beam center correction  -----------------------
    if (ZDCCalib==1) {
      int RunId10 = (int)(picoDst->event()->runId()/10.);
      if(fabs(ZDCSMD_QEst().X())<10 && fabs(ZDCSMD_QEst().Y())<10 && fabs(ZDCSMD_QWst().X())<10 && fabs(ZDCSMD_QWst().Y())<10) {
        ZDCSMDBeamCenter->Fill(1,RunId10,ZDCSMD_QEst().X());
        ZDCSMDBeamCenter->Fill(2,RunId10,ZDCSMD_QEst().Y());
        ZDCSMDBeamCenter->Fill(3,RunId10,ZDCSMD_QWst().X());
        ZDCSMDBeamCenter->Fill(4,RunId10,ZDCSMD_QWst().Y());
      }
    }
    //------------------------------------------------------------------------
    //---------------- Apply beam center correction ----------------------------------------
    if (!(ZDCCalib>=2)) return 0;
    int RunId10 = (int)(picoDst->event()->runId()/10.);
    Double_t HistTest = 0.;
    while(HistTest < 1.) {
      HistTest = ZDCSMDBeamCenterFilled->GetBinContent(1,RunId10-1507500);  //1008000 for BES
      if(HistTest > 1.) {break;}
      RunId10 -= 1;
      if(RunId10 < 1507501) {break;}
    }
    if(RunId10 > 1507500) {
      ZDCSMDCenterex = HistTest;
      ZDCSMDCenterey = ZDCSMDBeamCenterFilled->GetBinContent(2,RunId10-1507500);
      ZDCSMDCenterwx = -1.*ZDCSMDBeamCenterFilled->GetBinContent(3,RunId10-1507500);
      ZDCSMDCenterwy = ZDCSMDBeamCenterFilled->GetBinContent(4,RunId10-1507500);
    }
    //----------------- for test --------------------------------------------
    if(fabs(ZDCSMD_QEst().X())<10 && fabs(ZDCSMD_QEst().Y())<10 && fabs(ZDCSMD_QWst().X())<10 && fabs(ZDCSMD_QWst().Y())<10) {
      ZDCSMDBeamCenter->Fill(1,RunId10,ZDCSMD_QEst().X());
      ZDCSMDBeamCenter->Fill(2,RunId10,ZDCSMD_QEst().Y());
      ZDCSMDBeamCenter->Fill(3,RunId10,ZDCSMD_QWst().X());
      ZDCSMDBeamCenter->Fill(4,RunId10,ZDCSMD_QWst().Y());
    }
    //------------------------------------------------------------------------
    TVector2 Q[NEP], Qrc[NEP], Qsh[NEP], Qsh2[NEP];
    float Psi[NEP], Psi_rc[NEP], Psi_sh[NEP];
    //Raw EP
    Q[0] = ZDCSMD_QEst(); Q[1] = ZDCSMD_QWst();
    Q[2].Set( Q[0].X()-Q[1].X(), Q[0].Y()-Q[1].Y() );
    
    for (int iep=0;iep<NEP;iep++) Psi[iep] = Q[iep].Phi();
    for (int iep=0;iep<NEP;iep++) {
      Qrc[iep] = Q[iep]; Qsh[iep] = Q[iep]; Qsh2[iep] = Q[iep];
      Psi_rc[iep] = Psi[iep]; Psi_sh[iep] = Psi[iep];
    }
    int runIndx = get_runIndex(picoDst->event()->runId());
    if (runIndx<0) {return 0;}
    //Recenter
    if (EPCalib==0) {
      for (int iep=0;iep<NEP;iep++) {
        ZDCEPRecenter_x[centrality]->Fill( iep,runIndx,Q[iep].X() );  ZDCEPRecenter_y[centrality]->Fill( iep,runIndx,Q[iep].Y() );
      }
    }
    else {
      for (int iep=0;iep<NEP;iep++) {
        Qrc[iep] = get_recenteredQ(Q[iep],centrality,runIndx,iep);
        Psi_rc[iep] = Qrc[iep].Phi();
        ZDCEPRecenterPass1_x[centrality]->Fill( iep,runIndx,Qrc[iep].X() );  ZDCEPRecenterPass1_y[centrality]->Fill( iep,runIndx,Qrc[iep].Y() );
      }
    }
    //Shift correction
    if (EPCalib==1) {
      for (int iep=0;iep<NEP;iep++) {
        for (int j=1;j<9;j++) {
          ZDCEPShift_cos[centrality]->Fill(iep,j,cos(j*Psi_rc[iep]));  ZDCEPShift_sin[centrality]->Fill(iep,j,sin(j*Psi_rc[iep]));
        }
      }
    }
    if (EPCalib>=2) {
      for (int iep=0;iep<NEP;iep++) {
        Qsh [iep] = get_shiftedQ (Qrc[iep],centrality,iep);
        Psi_sh[iep] = Qsh[iep].Phi();
      }
    }
    mEP1 = Psi_sh[2];
    //Fill EP Histograms
    for (int iep=2;iep<NEP;iep++) {
      ZDCEPPsi->Fill(Psi[iep]);
      ZDCEPPsi_rc->Fill(Psi_rc[iep]);
      ZDCEPPsi_sh->Fill(Psi_sh[iep]);
    }
    float dPsi    = getZDCEPCor(Psi[0],Psi[1]);
    float dPsi_rc = getZDCEPCor(Psi_rc[0],Psi_rc[1]);
    float dPsi_sh = getZDCEPCor(Psi_sh[0],Psi_sh[1]);
    ZDCEPdPsi   [centrality]->Fill(dPsi);    ZDCEPRes   [centrality]->Fill(cos(dPsi));
    ZDCEPdPsi_rc[centrality]->Fill(dPsi_rc); ZDCEPRes_rc[centrality]->Fill(cos(dPsi_rc));
    ZDCEPdPsi_sh[centrality]->Fill(dPsi_sh); ZDCEPRes_sh[centrality]->Fill(cos(dPsi_sh));
  }
  
  
  vector<int>().swap(mIsoEs);
  int nTracks = picoDst->numberOfTracks();
  if(0)//turn on when below is off for speed
  {
    for(int iTrack = 0 ; iTrack<nTracks;iTrack++){
      StPicoTrack* track = (StPicoTrack*) picoDst->track(iTrack);
      if(!track)break;
      if(fabs(track->nSigmaElectron())<3){
        mIsoEs.push_back(iTrack);
      }
    }
  }
  for(int iTrack = 0 ; iTrack<nTracks;iTrack++){
    StPicoTrack* track = (StPicoTrack*) picoDst->track(iTrack);
    if(!track)continue;//break;
    /*if(track->isHFTTrack()) cout << "IS HFT TRACK " << endl;
     if(track->hasPxl1Hit()) cout <<"IS PX1 TRACK "<< endl;
     if(track->hasPxl2Hit()) cout <<"IS PX2 TRACK "<< endl;
     if(track->hasIstHit()) cout <<"IS IsS TRACK "<< endl;
     if(track->hasSstHit()) cout <<"IS SST TRACK "<< endl;*/
    if(mNpeCuts->isTOFPion(track) && fabs(track->nSigmaPion())<2 && mNpeCuts->isUnbiasedTrackNoHft(track) && track->pMom().Mag()>0){
      hHftRatio_d->Fill(track->gPt(),centrality);
      hHftRatio_eta_d->Fill(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity(),centrality);
      hHftRatio_phi_d->Fill(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi()/TMath::Pi(),centrality);
      hHftRatio_z_d->Fill(picoDst->event()->primaryVertex().z(),centrality);
      if(track->isHFTTrack()){
        hHftRatio_n->Fill(track->gPt(),centrality);
        hHftRatio_eta_n->Fill(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity(),centrality);
        hHftRatio_phi_n->Fill(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi()/TMath::Pi(),centrality);
        hHftRatio_z_n->Fill(picoDst->event()->primaryVertex().z(),centrality);
      }
    }
    if(fabs(track->nSigmaElectron())<3){
      mIsoEs.push_back(iTrack);
    }
    if((iTrack == t1)){
      continue;
    }
    if(track->gPt()>0.15 && track->gPt()<2.  && !(track->nSigmaElectron()>-1 && track->nSigmaElectron()<3)){
      double ww = 0;
      if(track->gPt()<=2.)ww = track->gPt();
      if(track->gPt()>2.)ww = 2;
      
      if(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity()>0.1 && track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity()<1. ){
        Q1_X += ww*TMath::Cos(2.*track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi());
        Q1_Y += ww*TMath::Sin(2.*track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi());
      }
      if(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity()<-0.1 && track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity()>-1. ){
        Q2_X += ww*TMath::Cos(2.*track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi());
        Q2_Y += ww*TMath::Sin(2.*track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi());
      }
      if(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity()<1. && track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity()>-1. ){
        Q_X += ww*TMath::Cos(2.*track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi());
        Q_Y += ww*TMath::Sin(2.*track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi());
      }
    }
  }
  
  Plane = (TMath::Pi()+TMath::ATan2(-Q_Y,-Q_X)) / 2.;
  Plane1 = (TMath::Pi()+TMath::ATan2(-Q1_Y,-Q1_X)) / 2.;
  Plane2 = (TMath::Pi()+TMath::ATan2(-Q2_Y,-Q2_X)) / 2.;
  hEventPlane->Fill(Plane);
  hEventPlane_Corr1->Fill(Plane1);
  hEventPlane_Corr2->Fill(Plane2);
  hEventPlane_Res->Fill(centrality,TMath::Cos(2.*(Plane1-Plane2)));
  if(mNpeCuts->epTree())fillEventTree(centrality,Q_X,Q_Y,Q1_X,Q1_Y,Q2_X,Q2_Y); // Filling trees
  // ============= End Event Plane Cal. ===========
  for(int iTrack = 0 ; iTrack<nTracks;iTrack++){
    StPicoTrack* track = (StPicoTrack*) picoDst->track(iTrack);
    if (!track)break;
    TVector3 const pMom = track->gMom(pVtx,picoDst->event()->bField());
    float ptot = pMom.Mag();
    int index2tof = track->bTofPidTraitsIndex();
    double beta=-1;
    float mass=0;
    if(index2tof>=0) {
      StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
      if(tofPid){
        mass = ptot*ptot*(1/beta/beta-1);
        beta = tofPid->btofBeta();
      }
    }
    float adcCut[4] = {-999, 256, 304, 416};
    int adc0=0;
    if (track->bemcPidTraitsIndex() >= 0) {
      StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(track->bemcPidTraitsIndex());
      adc0 = Emc->bemcAdc0();
    }
    int trigCat=0;
    if(isMB)trigCat = 1;
    if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
    if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2]))trigCat = 3;
    if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2] && isHLT3 && adc0>=adcCut[3]))trigCat = 4;
    
    if (mNpeCuts->isGoodTaggedElectron(track))  idxPicoTaggedEs.push_back(iTrack);
    if (mNpeCuts->isGoodTaggedElectronLoose(track))  idxPicoTaggedEsLoose.push_back(iTrack);
    if (mNpeCuts->isGoodPartnerElectron(track)) idxPicoPartnerEs.push_back(iTrack);
    //cout<<"track beta is :"<<beta<<endl;
    if (mNpeCuts->isUnbiasedTrack(track)) {
    cout<<"; UnbiasedTrack beta is: "<<beta<<endl; // zyj
      idxPicoUnbiasedEs.push_back(iTrack);
      if(abs(track->nSigmaProton())<2 ) idxPicoTaggedPrs.push_back(iTrack);//mNpeCuts->isTOFPion(track) &&
    }

    if (mNpeCuts->isUnbiasedDisplTrack(track)){
    cout<<"; UnbiasedDisplTrack is : "<<beta<<endl;
      idxPicoUnbiasedPs.push_back(iTrack);
      if(abs(track->nSigmaPion())<2 ) idxPicoTaggedPs.push_back(iTrack);//mNpeCuts->isTOFPion(track) &&
      if(abs(track->nSigmaKaon())<2 && track->pMom().Mag()>0) idxPicoTaggedKs.push_back(iTrack);//mNpeCuts->isTOFKaon(track) &&
    }
    //hQaPt->Fill(track->gPt());
    //hQaEta->Fill(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).pseudoRapidity());
    //hQaDca->Fill(track->dcaGeometry().helix().curvatureSignedDistance(picoDst->event()->primaryVertex()),track->gPt());
    if(mNpeCuts->isUnbiasedTrack(track)){
      hQaLogDca->Fill(log10(fabs(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()))+1e-9),track->gPt());
      if(beta>0)hQaLogDcaTOF->Fill(log10(fabs(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()))+1e-9),track->gPt());
      if(fabs(track->nSigmaPion())<2){
        double dcaz = track->gDCAz(pVtx.z());
        if(centrality==0){
          hQaDcaXY1->Fill(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()),track->gPt());
          hQaDcaZ1->Fill(dcaz,track->gPt());
        }
        else if(centrality==1){
          hQaDcaXY2->Fill(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()),track->gPt());
          hQaDcaZ2->Fill(dcaz,track->gPt());
        }
        else if(centrality==2){
          hQaDcaXY3->Fill(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()),track->gPt());
          hQaDcaZ3->Fill(dcaz,track->gPt());
        }
        else if(centrality==3){
          hQaDcaXY4->Fill(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()),track->gPt());
          hQaDcaZ4->Fill(dcaz,track->gPt());
        }
        else if(centrality==4){
          hQaDcaXY5->Fill(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()),track->gPt());
          hQaDcaZ5->Fill(dcaz,track->gPt());
        }
        else if(centrality==5){
          hQaDcaXY6->Fill(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()),track->gPt());
          hQaDcaZ6->Fill(dcaz,track->gPt());
        }
        else if(centrality==6){
          hQaDcaXY7->Fill(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()),track->gPt());
          hQaDcaZ7->Fill(dcaz,track->gPt());
        }
        else if(centrality==7){
          hQaDcaXY8->Fill(track->gDCA(pVtx.x(),pVtx.y(),pVtx.z()),track->gPt());
          hQaDcaZ8->Fill(dcaz,track->gPt());
        }
      }
    }
    //hQaNHitFit->Fill(track->nHitsFit());
    //hQaNHitDedx->Fill(track->nHitsDedx());
    //=======MVA eval =======
    double MVADec = mNpeCuts->getDLL(track);
    bool isMVA   = MVADec > mNpeCuts->cutMVA();
    if (mNpeCuts->isGoodTaggedElectron(track) && ((track->gPt()<2.5&&mNpeCuts->isTOFElectron(track))||track->gPt()>=2.5))  idxPicoTightEs.push_back(iTrack);
    //=======End MVA eval =======
    if (mNpeCuts->isGoodInclusiveElectron(track)){
      if(mNpeCuts->myHist()){
        fillMyHistogram(track,pVtx,isMB,isHLT1,isHLT2,isHLT3, isMVA, MVADec);// Quick histograms
      }
      if(mNpeCuts->signalTree()){
        if(mNpeCuts->isBEMCElectron(track)){
          int isHT = ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) || (isHLT3 && adc0>=adcCut[3]));
          if((isMVA || isHT>0) && track->nSigmaElectron()>-1 && track->nSigmaElectron()<3)fillTree(track,pVtx,isMB,isHLT1,isHLT2,isHLT3,MVADec,centrality,Q_X,Q_Y,Q1_X,Q1_Y,Q2_X,Q2_Y); // Filling trees
        }
      }
    }
    // ================= BKG tree + hist ====================
    if(mNpeCuts->bkgTree()){
      if (mNpeCuts->isUnbiasedTrack(track) && mNpeCuts->isTPCHadron(track) && (trigCat>1 || (track->nSigmaPion()>6 &&  (mass < (0.019+0.003)) && (mass > (0.019-0.003)))||iTrack==t1||iTrack==t2||iTrack==t3||iTrack==t4||iTrack==t5||iTrack==t1+1||iTrack==t2+1||iTrack==t3+1||iTrack==t4+1||iTrack==t5+1))fillBKGTree(track,pVtx,isMB,isHLT1,isHLT2,isHLT3,MVADec,centrality,Q_X,Q_Y,Q1_X,Q1_Y,Q2_X,Q2_Y);
    }
    
    TVector2 *newphi = new TVector2(track->gPt()*cos(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi()),track->gPt()*sin(track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).Phi()));
    double dPhi = (newphi->Phi()-mEP1);
    newphi->Delete();
    while(dPhi<0)dPhi+= TMath::Pi()*2;
    while(dPhi>=TMath::Pi()*2)dPhi+= -TMath::Pi()*2;
    if(dPhi>=TMath::Pi())dPhi= 2*TMath::Pi()-dPhi;
    if(centrality<7 && mNpeCuts->isUnbiasedTrack(track) && fabs(track->nSigmaPion())<3){
      if(track->charge()>0)hHadronV1_p->Fill(dPhi,track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity());
      if(track->charge()<0)hHadronV1_m->Fill(dPhi,track->gMom(picoDst->event()->primaryVertex(), picoDst->event()->bField()).PseudoRapidity());
    }
    
    
    if(gweight>0 && gweight<10){
      if(mNpeCuts->isTOFPion(track) && mNpeCuts->isUnbiasedTrack(track) && fabs(track->nSigmaPion())<2){//mNpeCuts->isTOFPion(track) &&
        if(iTrack == t1){//TPC event plane part
          int bin =run_centrality_corrx ->FindBin(mPicoDstMaker->picoDst()->event()->runId()-15E6,centrality);
          double corrx = 0;//run_centrality_corrx->GetBinContent(bin);
          double corry = 0;//run_centrality_corry->GetBinContent(bin);
          double plane1 = (TMath::ATan2((Q_Y-corry),(Q_X-corrx))) / 2.;
          double res = 1;//sqrt(2)*centrality_resolution->GetBinContent(centrality+1);
          double dphi = (track->pMom().Phi()-plane1);
          if(track->pMom().Mag()==0)dphi= -1000;
          if(dphi<0)dphi+= TMath::Pi()*2;
          if(dphi>=TMath::Pi())dphi= TMath::Pi()*2-dphi;
          if(dphi>=TMath::Pi()/2)dphi= TMath::Pi()-dphi;
          double weight = gweight/res;
          hHadronV2->Fill(track->gPt(),dphi,1/res);
          hHadronV2gweight->Fill(track->gPt(),dphi,weight);
          hInvRes->Fill(track->gPt(),1/res);
          hInvResgweight->Fill(track->gPt(),1/res,gweight);
        }
      }
    }
    // ================= End BKG tree + hist =================
  }//Ntrack end first loop
  //==================== Electron Conv. Histograms
  if(mNpeCuts->phoeHist()){
    for(int i = 0;i<idxPicoTaggedEs.size();i++){
      StPicoTrack* tt = (StPicoTrack*) picoDst->track(idxPicoTaggedEs[i]);
      for(int j = 0; j<idxPicoPartnerEs.size();j++){
        StPicoTrack* tp = (StPicoTrack*) picoDst->track(idxPicoPartnerEs[j]);
        StElectronPair *elecPair = new StElectronPair(tt,tp,idxPicoTaggedEs[i],idxPicoPartnerEs[j],picoDst->event()->bField(),pVtx);
        if(elecPair){
          if(mNpeCuts->isGoodElectronPairLoose(elecPair)){
            double MVADec = mNpeCuts->getDLL(tp);
            fillPairHistogram(tp,pVtx,isMB,isHLT1,isHLT2,isHLT3,tt->charge()*tp->charge(),MVADec);
          }
        }
        elecPair->Delete();
      }
    }
  }
  //==================== JPsi tree
  //==================== JPsi p tree
  for(int i = 0;i<idxPicoTightEs.size();i++){
    //cout << "Can " << idxPicoTightEs.size() << endl;
    StPicoTrack* tt = (StPicoTrack*) picoDst->track(idxPicoTightEs[i]);
    for(int j = 0; j<idxPicoTightEs.size();j++){
      if(i==j)continue;
      StPicoTrack* tp = (StPicoTrack*) picoDst->track(idxPicoTightEs[j]);
      StElectronPair *elecPair = new StElectronPair(tt,tp,idxPicoTightEs[i],idxPicoTightEs[j],picoDst->event()->bField(),pVtx);
      if(elecPair){
        if(mNpeCuts->isGoodJPsi(elecPair)){
          //cout << "Found good pair" << endl;
          for(int k = 0; k<idxPicoTaggedPrs.size();k++){
            StPicoTrack* tk = (StPicoTrack*) picoDst->track(idxPicoTaggedPrs[k]);
            TVector3 const tkMom = tk->gMom(pVtx,picoDst->event()->bField());
            TVector3 const ttMom = tt->gMom(pVtx,picoDst->event()->bField());
            TVector3 const tpMom = tp->gMom(pVtx,picoDst->event()->bField());
            TLorentzVector ltk(tkMom.x(),tkMom.y(),tkMom.z(),sqrt(tkMom.Mag()*tkMom.Mag()+0.938*0.938));
            TLorentzVector ltt(ttMom.x(),ttMom.y(),tpMom.z(),ttMom.Mag());
            TLorentzVector ltp(tpMom.x(),tpMom.y(),ttMom.z(),tpMom.Mag());
            TLorentzVector pc = ltk+ltt+ltp;
            TLorentzVector jpsi = ltt+ltp;
            if(fabs(pc.PseudoRapidity())<1.5)continue;
            if(jpsi.Pt()<1){
              if(tt->charge()*tp->charge()<0)hJpsip->Fill(pc.M(),elecPair->pairMass());
              if(tt->charge()*tp->charge()>0)hJpsip_ws->Fill(pc.M(),elecPair->pairMass());
            }
            if(jpsi.Pt()>=1&&jpsi.Pt()<2){
              if(tt->charge()*tp->charge()<0)hJpsip_1->Fill(pc.M(),elecPair->pairMass());
              if(tt->charge()*tp->charge()>0)hJpsip_1_ws->Fill(pc.M(),elecPair->pairMass());
            }
            if(jpsi.Pt()>=2){
              if(tt->charge()*tp->charge()<0)hJpsip_2->Fill(pc.M(),elecPair->pairMass());
              if(tt->charge()*tp->charge()>0)hJpsip_2_ws->Fill(pc.M(),elecPair->pairMass());
            }
          }
        }
      }
    }
  }
  
  if(0){
    for(int i = 0;i<idxPicoTaggedEs.size();i++){
      StPicoTrack* tt = (StPicoTrack*) picoDst->track(idxPicoTaggedEs[i]);
      int nCan = 0; //nCandidates
      for(int j = 0; j<idxPicoUnbiasedEs.size();j++){
        StPicoTrack* tp = (StPicoTrack*) picoDst->track(idxPicoUnbiasedEs[j]);
        StElectronPair *elecPair = new StElectronPair(tt,tp,idxPicoTaggedEs[i],idxPicoUnbiasedEs[j],picoDst->event()->bField(),pVtx);
        if(elecPair){
          float Dec1 = mNpeCuts->getMVADec(tp);
          float Dec2 = mNpeCuts->getMVADec2(tp);
          float MVADec = log(Dec1+2)-log(Dec2+2);
          if(mNpeCuts->isGoodJPsi(elecPair)){
            fillJPsiTree(elecPair,tp,tt,pVtx,isMB,isHLT1,isHLT2,isHLT3,tt->charge()*tp->charge(),nCan,MVADec);
            nCan++;
          }
        }
      }
    }
  }
  //==================== Electron Conv. tree
  if(mNpeCuts->phoeTree()){
    for(int i = 0;i<idxPicoTaggedEs.size();i++){
      StPicoTrack* tt = (StPicoTrack*) picoDst->track(idxPicoTaggedEs[i]);
      int nCan = 0; //nCandidates
      for(int j = 0; j<idxPicoUnbiasedEs.size();j++){
        StPicoTrack* tp = (StPicoTrack*) picoDst->track(idxPicoUnbiasedEs[j]);
        StElectronPair *elecPair = new StElectronPair(tt,tp,idxPicoTaggedEs[i],idxPicoUnbiasedEs[j],picoDst->event()->bField(),pVtx);
        if(elecPair){
          double MVADec = mNpeCuts->getDLL(tp);
          if(mNpeCuts->isGoodElectronPair(elecPair)){
            fillPhoETree(elecPair,tp,tt,pVtx,isMB,isHLT1,isHLT2,isHLT3,tt->charge()*tp->charge(),nCan,MVADec,centrality,Q_X,Q_Y,Q1_X,Q1_Y,Q2_X,Q2_Y);
            nCan++;
          }
        }
        elecPair->Delete();
      }
    }
  }
  //==================== Hadron trees
  if(mNpeCuts->ksTree()){
    for(int i = 0;i<idxPicoTaggedPs.size();i++){
      StPicoTrack* tt = (StPicoTrack*) picoDst->track(idxPicoTaggedPs[i]);
      int nCan = 0; //nCandidates
      //if(!(i==t1||i==t2||i==t3||i==t4||i==t5))continue;
      int best=0;
      double temp=100;
      for(int j = 0; j<idxPicoUnbiasedPs.size();j++){
        if(idxPicoUnbiasedPs[j] == idxPicoTaggedPs[i])continue;
        StPicoTrack* tp = (StPicoTrack*) picoDst->track(idxPicoUnbiasedPs[j]);
        StElectronPair *elecPair = new StElectronPair(tt,tp,idxPicoTaggedPs[i],idxPicoUnbiasedPs[j],picoDst->event()->bField(),pVtx);
        if(elecPair){
          if(mNpeCuts->isGoodPionPair(elecPair)){
            nCan++;
            if(elecPair->pairDca()<temp){
              best = j;
              temp = elecPair->pairDca();
            }
          }
        }
        elecPair->Delete();
      }
      StPicoTrack* tprobe = (StPicoTrack*) picoDst->track(idxPicoUnbiasedPs[best]);
      StElectronPair *elecPair = new StElectronPair(tt,tprobe,idxPicoTaggedPs[i],idxPicoUnbiasedPs[best],picoDst->event()->bField(),pVtx);
      if(elecPair){
        double MVADec = mNpeCuts->getDLL(tprobe);
        if(mNpeCuts->isGoodPionPair(elecPair) && tprobe->gPt()>2.){
          fillKShortTree(elecPair,tprobe,tt,pVtx,isMB,isHLT1,isHLT2,isHLT3,tt->charge()*tprobe->charge(),nCan,MVADec);
        }
      }
      elecPair->Delete();
    }
  }
  /*    if(mNpeCuts->phiTree()){
   for(int i = 0;i<idxPicoTaggedKs.size();i++){
   StPicoTrack* tt = (StPicoTrack*) picoDst->track(idxPicoTaggedKs[i]);
   int nCan = 0; //nCandidates
   //if(!(i==t1||i==t2||i==t3||i==t4||i==t5))continue;
   int best=0;
   double temp=100;
   for(int j = 0; j<idxPicoUnbiasedPs.size();j++){
   if(idxPicoUnbiasedPs[j] == idxPicoTaggedKs[i])continue;
   StPicoTrack* tp = (StPicoTrack*) picoDst->track(idxPicoUnbiasedPs[j]);
   if(!tp->pMom().mag()>0)continue;
   StElectronPair *elecPair = new StElectronPair(tt,tp,idxPicoTaggedKs[i],idxPicoUnbiasedPs[j],picoDst->event()->bField(),pVtx);
   if(elecPair){
   if(mNpeCuts->isGoodKaonPair(elecPair) && tp->gPt()>0.6&& tt->charge()*tp->charge()<0){
   
   double MVADec = mNpeCuts->getDLL(tp);
   fillPhiTree(elecPair,tp,tt,pVtx,isMB,isHLT1,isHLT2,isHLT3,tt->charge()*tp->charge(),nCan,MVADec);
   //nCan++;
   //if(elecPair->pairDca()<temp){
   //  best = j;
   //  temp = elecPair->pairDca();
   //}
   }
   }
   }
   }
   //StPicoTrack* tprobe = (StPicoTrack*) picoDst->track(idxPicoUnbiasedPs[best]);
   //StElectronPair *elecPair = new StElectronPair(tt,tprobe,idxPicoTaggedKs[i],idxPicoUnbiasedPs[best],picoDst->event()->bField(),pVtx);
   //if(elecPair){
   //    double MVADec = mNpeCuts->getDLL(tprobe);
   //    if(mNpeCuts->isGoodKaonPair(elecPair) && tprobe->gPt()>0.6){
   //  fillPhiTree(elecPair,tprobe,tt,pVtx,isMB,isHLT1,isHLT2,isHLT3,tt->charge()*tprobe->charge(),nCan,MVADec);
   //    }
   //}
   }*/
  /*for(int i = 0;i<idxPicoTaggedPs.size();i++){
   StPicoTrack* tt = (StPicoTrack*) picoDst->track(idxPicoTaggedPs[i]);
   int nCan = 0; //nCandidates
   //if(!(i==t1||i==t2||i==t3||i==t4||i==t5))continue;
   int best=0;
   double temp=100;
   for(int j = 0; j<idxPicoUnbiasedPs.size();j++){
   if(idxPicoUnbiasedPs[j] == idxPicoTaggedPs[i])continue;
   StPicoTrack* tp = (StPicoTrack*) picoDst->track(idxPicoUnbiasedPs[j]);
   StElectronPair *elecPair = new StElectronPair(tt,tp,idxPicoTaggedPs[i],idxPicoUnbiasedPs[j],picoDst->event()->bField(),pVtx);
   if(elecPair){
   if(mNpeCuts->isGoodProtonPionPair(elecPair)){
   nCan++;
   if(elecPair->pairDca()<temp){
   best = j;
   temp = elecPair->pairDca();
   }
   }
   }
   }
   StPicoTrack* tprobe = (StPicoTrack*) picoDst->track(idxPicoUnbiasedPs[best]);
   StElectronPair *elecPair = new StElectronPair(tt,tprobe,idxPicoTaggedPs[i],idxPicoUnbiasedPs[best],picoDst->event()->bField(),pVtx);
   if(elecPair){
   double MVADec = mNpeCuts->getDLL(tprobe);
   if(mNpeCuts->isGoodProtonPionPair(elecPair) && tprobe->gPt()>0.6 && tt->charge()*tprobe->charge()<0){
   fillLambdaTree(elecPair,tprobe,tt,pVtx,isMB,isHLT1,isHLT2,isHLT3,tt->charge()*tprobe->charge(),nCan,MVADec);
   }
   }
   }*/
  return kStOK;
}
void StPicoNpeAnaMaker::fillPairHistogram(StPicoTrack* track,TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3, int qq, double MVADec){
  float pt = track->gPt();
  TVector3 const pMom = track->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  double MVADec2 = 0;//mNpeCuts->getDLL_highPt(track);
  double MVADec3 = 0;//mNpeCuts->getDLL_HT(track);
  float ptot = pMom.Mag();
  float beta = 0;
  float adc0 = 0;
  float mass = 0;
  int index2tof = track->bTofPidTraitsIndex();
  if(index2tof>=0) {
    StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
    if(tofPid){
      beta = tofPid->btofBeta();
      mass = ptot*ptot*(1/beta/beta-1);
    }
  }
  if (track->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(track->bemcPidTraitsIndex());
    adc0 = Emc->bemcAdc0();
  }
  float dcaz = track->gDCAz(pVtx.z());
  float dca = track->gDCAxy(pVtx.x(),pVtx.y());
  float dca3d = track->gDCA(pVtx.x(),pVtx.y(),pVtx.z());
  
  float nsige = track->nSigmaElectron();
  float adcCut[4] = {-999, 256, 304, 416};
  if(qq<0){
    if(((pt<2.5 && mNpeCuts->isTOFElectron(track)) || pt>=2.5 ) && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) || (isHLT3 && adc0>=adcCut[3]))){
      if(MVADec3>0.6)hFit_e[9]->Fill(pt,nsige);
      if(mNpeCuts->isBSMDElectron(track)&& mNpeCuts->isBEMCElectron(track)){
        hFit_e[7]->Fill(pt,nsige);
        //hFit2D_e[7]->Fill(pt,MVADec);
        //hFit2D_e[8]->Fill(pt,MVADec3);
        if(MVADec3>mNpeCuts->cutHTMVA())hFit_e[8]->Fill(pt,nsige);
        //if(MVADec3>0.45)hFit_e[9]->Fill(pt,nsige);
      }
    }else if(isMB){
      if(MVADec>0.6 && ((pt<2.5 && mNpeCuts->isTOFElectron(track)) || pt>=2.5 ))hFit_e[5]->Fill(pt,nsige);
      if((pt<2.5 && mNpeCuts->isTOFElectron(track) && isMB&& mNpeCuts->isBEMCElectron(track)) ||
         (pt>=2.5 && pt<3.5 && isMB&& mNpeCuts->isBEMCElectron(track)) ||
         (pt>=3.5 && isMB&& mNpeCuts->isBEMCElectron(track))){
        hFit_e[0]->Fill(pt,nsige);
        //if(nsige>-4.2)hFit2D_e[0]->Fill(pt,MVADec);
        if(MVADec>mNpeCuts->cutMVA())hFit_e[3]->Fill(pt,nsige);
        if(MVADec>0.0)hFit_e[4]->Fill(pt,nsige);
        if(MVADec>0.15)hFit_e[5]->Fill(pt,nsige);
        if(MVADec>0.3)hFit_e[6]->Fill(pt,nsige);
      }
    }
  }else{
    if(((pt<2.5 && mNpeCuts->isTOFElectron(track)) || pt>=2.5 ) && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) || (isHLT3 && adc0>=adcCut[3]))){
      if(MVADec3>0.6)hFit_e_WS[9]->Fill(pt,nsige);
      if(mNpeCuts->isBSMDElectron(track)&& mNpeCuts->isBEMCElectron(track)){
        hFit_e_WS[7]->Fill(pt,nsige);
        //hFit2D_e_WS[7]->Fill(pt,MVADec);
        //hFit2D_e_WS[8]->Fill(pt,MVADec3);
        if(MVADec3>mNpeCuts->cutHTMVA())hFit_e_WS[8]->Fill(pt,nsige);
      }
    }else if(isMB){
      if(MVADec>0.6 && ((pt<2.5 && mNpeCuts->isTOFElectron(track)) || pt>=2.5 ))hFit_e_WS[5]->Fill(pt,nsige);
      if((pt<2.5 && mNpeCuts->isTOFElectron(track) && isMB&& mNpeCuts->isBEMCElectron(track)) ||
         (pt>=2.5 && pt<3.5 && isMB&& mNpeCuts->isBEMCElectron(track)) ||
         (pt>=3.5 && isMB&& mNpeCuts->isBEMCElectron(track))){
        hFit_e_WS[0]->Fill(pt,nsige);
        //if(nsige>-4.2)hFit2D_e_WS[0]->Fill(pt,MVADec);
        if(MVADec>mNpeCuts->cutMVA())hFit_e_WS[3]->Fill(pt,nsige);
        if(MVADec>0.0)hFit_e_WS[4]->Fill(pt,nsige);
        //if(MVADec>0.15)hFit_e_WS[5]->Fill(pt,nsige);
        if(MVADec>0.3)hFit_e_WS[6]->Fill(pt,nsige);
      }
    }
  }
  ///========= /========= /========= /=========
  //========= Fill Electrons that pass final PID cut
  ///========= /========= /========= /=========
  
}
void StPicoNpeAnaMaker::fillMyHistogram(StPicoTrack* track, TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3, bool isMVA, double MVADec){
  float pt = track->gPt();
  TVector3 const pMom = track->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  float ptot = pMom.Mag();
  double MVADec2 = 0;//mNpeCuts->getDLL_highPt(track);
  double MVADec3 = 0;//mNpeCuts->getDLL_HT(track);
  int index2tof = track->bTofPidTraitsIndex();
  float mass = 0;
  float beta = 0;
  if(index2tof>=0) {
    StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
    if(tofPid){
      beta = tofPid->btofBeta();
      mass = ptot*ptot*(1/beta/beta-1);
    }
  }
  float dcaz = track->gDCAz(pVtx.z());
  float dca = track->gDCAxy(pVtx.x(),pVtx.y());
  float dca3d = track->gDCA(pVtx.x(),pVtx.y(),pVtx.z());
  
  float nsige = track->nSigmaElectron();
  float nsigpi = track->nSigmaPion();
  float adc0 = 0;
  float adcCut[4] = {-999, 256, 304, 416};
  int nPhi=-1;
  int nEta=-1;
  float phiDist = 0;
  float zDist = 0;
  float emc0=0;
  //for(int in = 0;in<mPicoDstMaker->picoDst()->numberOfEmcTriggers();in++){
  //StPicoEmcTrigger *DSM = mPicoDstMaker->picoDst()->emcTrigger(in);
  //if(DSM->flag()<0xf)hDsmAdc->Fill(DSM->adc(),DSM->id());
  //}
  if (track->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(track->bemcPidTraitsIndex());
    adc0 = Emc->bemcAdc0();
    nPhi = Emc->bemcSmdNPhi();
    nEta = Emc->bemcSmdNEta();
    phiDist = Emc->bemcPhiDist();
    zDist = Emc->bemcZDist();
    //hBTOWId->Fill(Emc->btowId());
    //hBAdc->Fill(adc0);
    //hBnPhi->Fill(nPhi);
    //hBnEta->Fill(nEta);
    //hBPhiDist->Fill(phiDist);
    //hBZDist->Fill(zDist);
  }
  bool isKaon = false;
  bool isPion = false;
  bool is2Pion = false;
  bool isProton = false;
  //M2->Fill(mass);
  if( (mass < (0.019+0.003)) && (mass > (0.019-0.003)))isPion=true;
  if( (mass < (0.019+0.003)) && (mass > (0.019-0.003)) && fabs(track->nSigmaPion())>7)is2Pion=true;
  if( (mass < (0.243+0.005)) && (mass > (0.243-0.005)))isKaon=true;
  if( (mass> (0.878-0.2)) && (mass <(0.878+0.2)))isProton=true;
  //hEoverP_all->Fill(eoverp);
  //hBeta->Fill(pt,(1/beta));
  //hnSigma->Fill(pt,nsige);
  //hMVA->Fill(MVADec);
  bool is_iso = 1;//isIso(track);
  //====================================
  //Looking at HT track now
  //====================================
  if( (isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) || (isHLT3 && adc0>=adcCut[3]) ){
    if(MVADec3>0.6 && ((pt<2.5 && mNpeCuts->isTOFElectron(track)) || pt>=2.5 )){
      hFit[9]->Fill(pt,nsige);
      if(isPion)hFit_pi[9]->Fill(pt,nsige);
      if(is2Pion)hFit_2pi[9]->Fill(pt,nsige);
      if(isKaon)hFit_k[9]->Fill(pt,nsige);
      if(isProton)hFit_p[9]->Fill(pt,nsige);
    }
    if(mNpeCuts->isBEMCElectron(track)  && ((pt<2.5 && mNpeCuts->isTOFElectron(track)) || pt>=2.5 ) && mNpeCuts->isBSMDElectron(track)){
      hFit[7]->Fill(pt,nsige);
      if(mNpeCuts->isElectron(track)){
        //hFit2D[1]->Fill(pt,MVADec);
        //hFit2D[2]->Fill(pt,MVADec3);
        if(isPion){
          //hFit2D_pi[1]->Fill(pt,MVADec);
          //hFit2D_pi[2]->Fill(pt,MVADec3);
        }
      }
      if(isPion)hFit_pi[7]->Fill(pt,nsige);
      if(is2Pion)hFit_2pi[7]->Fill(pt,nsige);
      if(isKaon)hFit_k[7]->Fill(pt,nsige);
      if(isProton)hFit_p[7]->Fill(pt,nsige);
      if(MVADec3>mNpeCuts->cutHTMVA()){
        hFit[8]->Fill(pt,nsige);
        if(isPion)hFit_pi[8]->Fill(pt,nsige);
      }
    }
  }else if(isMB){
    if(MVADec>0.6 && ((pt<2.5 && mNpeCuts->isTOFElectron(track)) || pt>=2.5 )){
      hFit[5]->Fill(pt,nsige);
      if(isPion)hFit_pi[5]->Fill(pt,nsige);
      if(is2Pion)hFit_2pi[5]->Fill(pt,nsige);
      if(isKaon)hFit_k[5]->Fill(pt,nsige);
      if(isProton)hFit_p[5]->Fill(pt,nsige);
    }
    if((pt<2.5 && mNpeCuts->isTOFElectron(track) && mNpeCuts->isBEMCElectron(track)) ||
       (pt>=2.5 && pt<3.5 && mNpeCuts->isBEMCElectron(track)) ||
       (pt>=3.5  && mNpeCuts->isBEMCElectron(track)) ){
      hFit[0]->Fill(pt,nsige);
      //if(mNpeCuts->isElectron(track)){
      //hFit2D[0]->Fill(pt,MVADec);
      //if(isPion)hFit2D_pi[0]->Fill(pt,MVADec);
      //}
      if(isPion)hFit_pi[0]->Fill(pt,nsige);
      if(is2Pion)hFit_2pi[0]->Fill(pt,nsige);
      if(isKaon)hFit_k[0]->Fill(pt,nsige);
      if(isProton)hFit_p[0]->Fill(pt,nsige);
      if(isMVA){
        hFit[3]->Fill(pt,nsige);
        if(isPion)hFit_pi[3]->Fill(pt,nsige);
      }
      if(MVADec>0.0){
        hFit[4]->Fill(pt,nsige);
        if(isPion)hFit_pi[4]->Fill(pt,nsige);
      }
      if(MVADec>0.3){
        hFit[6]->Fill(pt,nsige);
        if(isPion)hFit_pi[6]->Fill(pt,nsige);
      }
    }
  }
  ///=========  /=========/  /=========/  /=========/
  //========= Construct some pion DCA templates
  ///=========  /=========/  /=========/  /=========/
  if(abs(track->nSigmaPion()<2)  && mNpeCuts->isBEMCElectron(track)){//mNpeCuts->isTOFPion(track)
    //hDca_pi[1]->Fill(pt,dca);
    //hDcaz_pi[1]->Fill(pt,dcaz);
    //hDca3D_pi[1]->Fill(pt,fabs(dca3d));
    hDcaLog3D_pi[1]->Fill(pt,log10(fabs(dca3d+0.000000001)));
    if((isHLT1 && adc0>=adcCut[1])|| (isHLT2 && adc0>=adcCut[2]) || (isHLT3 && adc0>=adcCut[3 ])){
      //hDca_pi[3]->Fill(pt,dca);
      //hDcaz_pi[3]->Fill(pt,dcaz);
      //hDca3D_pi[3]->Fill(pt,fabs(dca3d));
      hDcaLog3D_pi[3]->Fill(pt,log10(fabs(dca3d+0.000000001)));
    }
    if(isPion){
      //hDca_pi[4]->Fill(pt,dca);
      //hDcaz_pi[4]->Fill(pt,dcaz);
      //hDca3D_pi[4]->Fill(pt,fabs(dca3d));
      hDcaLog3D_pi[4]->Fill(pt,log10(fabs(dca3d+0.000000001)));
      if((isHLT1 && adc0>=adcCut[1])|| (isHLT2 && adc0>=adcCut[2]) || (isHLT3 && adc0>=adcCut[3 ])){
        //hDca_pi[5]->Fill(pt,dca);
        //hDcaz_pi[5]->Fill(pt,dcaz);
        //hDca3D_pi[5]->Fill(pt,fabs(dca3d));
        hDcaLog3D_pi[5]->Fill(pt,log10(fabs(dca3d+0.000000001)));
      }
    }
  }
  ///=========  /=========/  /=========/  /=========/
  //========= Fill Electrons that pass final PID cut
  ///=========  /=========/  /=========/  /=========/
  if( isMVA || MVADec3>mNpeCuts->cutHTMVA() || mNpeCuts->isElectron(track)){
    is_iso = isIso(track);
    //Both HT and MB go in the next loop
    if(mNpeCuts->isBEMCElectron(track) && ((pt<2.5&&mNpeCuts->isTOFElectron(track))||pt>=2.5) ){
      //Looking at HT tracks only here====================================
      if( (isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) || (isHLT3 && adc0>=adcCut[3]) ){
        //Looking at MVA only
        if(MVADec3>0.6 && is_iso){
          //hDca[2]->Fill(pt,dca);
          //hDcaz[2]->Fill(pt,dcaz);
          //hDca3D[2]->Fill(pt,fabs(dca3d));
          hDcaLog3D[2]->Fill(pt,log10(fabs(dca3d+0.000000001)));
          if(isPion){
            //hDca_pi[2]->Fill(pt,dca);
            //hDca3D_pi[2]->Fill(pt,fabs(dca3d));
            hDcaLog3D_pi[2]->Fill(pt,log10(fabs(dca3d+0.000000001)));
          }
        }//Ending MVA only
        //Looking at NSigmae selected tracks
        if(mNpeCuts->isElectron(track)){
          //hDca[7]->Fill(pt,dca);
          //hDcaz[7]->Fill(pt,dcaz);
          //hDca3D[7]->Fill(pt,fabs(dca3d));
          hDcaLog3D[7]->Fill(pt,log10(fabs(dca3d+0.000000001)));
          if(is_iso){
            //hDca[5]->Fill(pt,dca);
            //hDcaz[5]->Fill(pt,dcaz);
            //hDca3D[5]->Fill(pt,fabs(dca3d));
            hDcaLog3D[5]->Fill(pt,log10(fabs(dca3d+0.000000001)));
            if(MVADec3>mNpeCuts->cutHTMVA()){//+HT MVA
              //hDca[3]->Fill(pt,dca);
              //hDcaz[3]->Fill(pt,dcaz);
              //hDca3D[3]->Fill(pt,fabs(dca3d));
              hDcaLog3D[3]->Fill(pt,log10(fabs(dca3d+0.000000001)));
            }//Ending HT MVA
          }
        }//Ending NSigmaE
      }//Done filling HT data
      //Now looking at MB data
      else if(isMB){
        //Looking at MVA only
        if(MVADec>0.6 && is_iso){
          //hDca[0]->Fill(pt,dca);
          //hDcaz[0]->Fill(pt,dcaz);
          //hDca3D[0]->Fill(pt,fabs(dca3d));
          hDcaLog3D[0]->Fill(pt,log10(fabs(dca3d+0.000000001)));
          if(isPion){
            //hDca_pi[0]->Fill(pt,dca);
            //hDca3D_pi[0]->Fill(pt,fabs(dca3d));
            hDcaLog3D_pi[0]->Fill(pt,log10(fabs(dca3d+0.000000001)));
          }
        }//Ending MVA only
        //Looking at NSigmae only
        if(mNpeCuts->isElectron(track)){
          if(is_iso){
            //hDca[4]->Fill(pt,dca);
            //hDcaz[4]->Fill(pt,dcaz);
            //hDca3D[4]->Fill(pt,fabs(dca3d));
            hDcaLog3D[4]->Fill(pt,log10(fabs(dca3d+0.000000001)));
          }
          if(isMVA){//Looking at MVA
            //hDca[6]->Fill(pt,dca);
            //hDcaz[6]->Fill(pt,dcaz);
            //hDca3D[6]->Fill(pt,fabs(dca3d));
            hDcaLog3D[6]->Fill(pt,log10(fabs(dca3d+0.000000001)));
            if(is_iso){
              //hDca[1]->Fill(pt,dca);
              //hDcaz[1]->Fill(pt,dcaz);
              //hDca3D[1]->Fill(pt,fabs(dca3d));
              hDcaLog3D[1]->Fill(pt,log10(fabs(dca3d+0.000000001)));
            }
          }//Ending MVA
        }//Ending NSigmae
      }//Ending MB
    }//End DCA filling
  }//End all selected electrons loop
}
void StPicoNpeAnaMaker::fillJPsiTree(StElectronPair * epair,StPicoTrack* tp,StPicoTrack* track,TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3, int qq, int can, double MVADec){
  float pt = tp->gPt();
  TVector3 const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  float ptot = pMom.Mag();
  float beta = 0;
  float tbeta = 0;
  float adc0 = 0;
  float adc01 = 0;
  float mass = 0;
  float YLoc = 0;
  int index2tof = tp->bTofPidTraitsIndex();
  int tindex2tof = track->bTofPidTraitsIndex();
  if(index2tof>=0) {
    StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
    if(tofPid){
      beta = tofPid->btofBeta();
      YLoc = tofPid->btofYLocal();
      mass = ptot*ptot*(1/beta/beta-1);
    }
  }
  if(tindex2tof>=0) {
    StPicoBTofPidTraits *ttofPid = mPicoDstMaker->picoDst()->btofPidTraits(tindex2tof);
    if(ttofPid){
      tbeta = ttofPid->btofBeta();
    }
  }
  float emc0 = 0;
  int nPhi=0;
  int nEta=0;
  float zDist=0;
  float phiDist=0;
  if (tp->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(tp->bemcPidTraitsIndex());
    adc0 = Emc->bemcAdc0();
    nPhi = Emc->bemcSmdNPhi();
    nEta = Emc->bemcSmdNEta();
    phiDist = Emc->bemcPhiDist();
    zDist = Emc->bemcZDist();
    
  }
  if (track->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc1 =  mPicoDstMaker->picoDst()->bemcPidTraits(track->bemcPidTraitsIndex());
    adc01 = Emc1->bemcAdc0();
  }
  float dcaz = tp->gDCAz(pVtx.z());
  float dca = tp->gDCAxy(pVtx.x(),pVtx.y());
  float dca3d = tp->gDCA(pVtx.x(),pVtx.y(),pVtx.z());
  float nsige = tp->nSigmaElectron();
  float nsigpi = tp->nSigmaPion();
  float nsigk = tp->nSigmaKaon();
  float nsigp = tp->nSigmaProton();
  float adcCut[4] = {-999, 256, 304, 416};
  //float Dec1 = mNpeCuts->getMVADec(track);
  //float Dec2 = mNpeCuts->getMVADec2(track);
  float TMVADec = mNpeCuts->getDLL(track);//log(Dec1+2)-log(Dec2+2);
  JPsi_M = epair->pairMass();
  pair_dca = epair->pairDca();
  probe_pt = pt;
  probe_dcaxy = dca;
  probe_dca = dca3d;
  probe_p = ptot;
  pair_theta = epair->pairAngle();
  probe_phidist = phiDist;
  probe_zdist = zDist;
  probe_nsige = nsige;
  probe_nsigpi = nsigpi;
  probe_nsigk = nsigk;
  probe_nsigp = nsigp;
  probe_beta = beta;
  tag_beta = tbeta;
  probe_neta = nEta;
  probe_nphi = nPhi;
  probe_emc0 = emc0;
  probe_yloc = YLoc;
  probe_charge = tp->charge();
  tag_charge = track->charge();
  probe_ncan = can;
  probe_mva = MVADec;
  tag_mva = TMVADec;
  tag_trigger = (isHLT1 && adc01>=adcCut[1])|| (isHLT2 && adc01>=adcCut[2]) || (isHLT3 && adc01>=adcCut[3]);
  JPsi_tree->Fill();
}
void StPicoNpeAnaMaker::fillKShortTree(StElectronPair * epair,StPicoTrack* tp,StPicoTrack* track,TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3, int qq, int can, double MVADec){
  float pt = tp->gPt();
  TVector3 const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  float ptot = pMom.Mag();
  TVector3 const p1Mom = track->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  float ptot_tag = p1Mom.Mag();
  float beta = 0;
  float tbeta = 0;
  float adc0 = 0;
  float adc01 = 0;
  float mass = 0;
  float YLoc = 0;
  int index2tof = tp->bTofPidTraitsIndex();
  int tindex2tof = track->bTofPidTraitsIndex();
  if(index2tof>=0) {
    StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
    if(tofPid){
      beta = tofPid->btofBeta();
      YLoc = tofPid->btofYLocal();
      mass = ptot*ptot*(1/beta/beta-1);
    }
  }
  if(tindex2tof>=0) {
    StPicoBTofPidTraits *ttofPid = mPicoDstMaker->picoDst()->btofPidTraits(tindex2tof);
    if(ttofPid){
      tbeta = ttofPid->btofBeta();
    }
  }
  float emc0 = 0;
  int nPhi=0;
  int nEta=0;
  float zDist=0;
  float phiDist=0;
  if (tp->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(tp->bemcPidTraitsIndex());
    adc0 = Emc->bemcAdc0();
    nPhi = Emc->bemcSmdNPhi();
    nEta = Emc->bemcSmdNEta();
    phiDist = Emc->bemcPhiDist();
    zDist = Emc->bemcZDist();
    
  }
  if (track->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc1 =  mPicoDstMaker->picoDst()->bemcPidTraits(track->bemcPidTraitsIndex());
    adc01 = Emc1->bemcAdc0();
  }
  float dcaz = tp->gDCAz(pVtx.z());
  float dca = tp->gDCAxy(pVtx.x(),pVtx.y());
  float dca3d = tp->gDCA(pVtx.x(),pVtx.y(),pVtx.z());
  float nsige = tp->nSigmaElectron();
  float nsigpi = tp->nSigmaPion();
  float nsigk = tp->nSigmaKaon();
  float nsigp = tp->nSigmaProton();
  float adcCut[4] = {-999, 256, 304, 416};
  int trigCat=0;
  if(isMB)trigCat = 1;
  if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2]))trigCat = 3;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2] && isHLT3 && adc0>=adcCut[3]))trigCat = 4;
  if(isMB && !((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 5;
  if(isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 6;
  if(!isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 7;
  if(((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 8;
  //if(trigCat==0)return;
  //float Dec1 = mNpeCuts->getMVADec(track);
  //float Dec2 = mNpeCuts->getMVADec2(track);
  float TMVADec = mNpeCuts->getDLL(track);//log(Dec1+2)-log(Dec2+2);
  Ks_M = epair->pairMassPion();
  Ks_pair_dca = epair->pairDca();
  Ks_probe_pt = pt;
  Ks_triggercat = trigCat;
  Ks_probe_dcaxy = dca;
  Ks_probe_dca = dca3d;
  Ks_probe_p = ptot;
  Ks_probe_phi =tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi();
  Ks_tag_p = ptot_tag;
  Ks_pair_theta = epair->pairAngle();
  Ks_probe_phidist = phiDist;
  Ks_probe_zdist = zDist;
  Ks_probe_nsige = nsige;
  Ks_probe_nsigpi = nsigpi;
  Ks_probe_nsigk = nsigk;
  Ks_probe_nsigp = nsigp;
  Ks_probe_beta = beta;
  Ks_tag_beta = tbeta;
  Ks_probe_neta = nEta;
  Ks_probe_nphi = nPhi;
  Ks_probe_emc0 = emc0;
  Ks_probe_yloc = YLoc;
  Ks_probe_charge = tp->charge();
  Ks_tag_charge = track->charge();
  Ks_probe_ncan = can;
  Ks_probe_mva = MVADec;
  Ks_tag_mva = TMVADec;
  Ks_tag_trigger = (isHLT1 && adc01>=adcCut[1])|| (isHLT2 && adc01>=adcCut[2]) || (isHLT3 && adc01>=adcCut[3]);
  Ks_tree->Fill();
}
void StPicoNpeAnaMaker::fillPhiTree(StElectronPair * epair,StPicoTrack* tp,StPicoTrack* track, TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3, int qq, int can, double MVADec){
  float pt = tp->gPt();
  TVector3 const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  float ptot = pMom.Mag();
  float beta = 0;
  float tbeta = 0;
  float adc0 = 0;
  float adc01 = 0;
  float mass = 0;
  float YLoc = 0;
  int index2tof = tp->bTofPidTraitsIndex();
  int tindex2tof = track->bTofPidTraitsIndex();
  if(index2tof>=0) {
    StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
    if(tofPid){
      beta = tofPid->btofBeta();
      YLoc = tofPid->btofYLocal();
      mass = ptot*ptot*(1/beta/beta-1);
    }
  }
  if(tindex2tof>=0) {
    StPicoBTofPidTraits *ttofPid = mPicoDstMaker->picoDst()->btofPidTraits(tindex2tof);
    if(ttofPid){
      tbeta = ttofPid->btofBeta();
    }
  }
  float emc0 = 0;
  int nPhi=0;
  int nEta=0;
  float zDist=0;
  float phiDist=0;
  if (tp->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(tp->bemcPidTraitsIndex());
    adc0 = Emc->bemcAdc0();
    nPhi = Emc->bemcSmdNPhi();
    nEta = Emc->bemcSmdNEta();
    phiDist = Emc->bemcPhiDist();
    zDist = Emc->bemcZDist();
  }
  if (track->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc1 =  mPicoDstMaker->picoDst()->bemcPidTraits(track->bemcPidTraitsIndex());
    adc01 = Emc1->bemcAdc0();
  }
  float dcaz = tp->gDCAz(pVtx.z());
  float dca = tp->gDCAxy(pVtx.x(),pVtx.y());
  float dca3d = tp->gDCA(pVtx.x(),pVtx.y(),pVtx.z());
  float nsige = tp->nSigmaElectron();
  float nsigpi = tp->nSigmaPion();
  float nsigk = tp->nSigmaKaon();
  float nsigp = tp->nSigmaProton();
  float adcCut[4] = {-999, 256, 304, 416};
  int trigCat=0;
  if(isMB)trigCat = 1;
  if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2]))trigCat = 3;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2] && isHLT3 && adc0>=adcCut[3]))trigCat = 4;
  if(isMB && !((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 5;
  if(isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 6;
  if(!isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 7;
  if(((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 8;
  //if(trigCat==0)return;
  //float Dec1 = mNpeCuts->getMVADec(track);
  //float Dec2 = mNpeCuts->getMVADec2(track);
  float TMVADec = mNpeCuts->getDLL(track);//log(Dec1+2)-log(Dec2+2);
  Phi_M = epair->pairMassKaon();
  Phi_pair_dca = epair->pairDca();
  Phi_probe_pt = pt;
  Phi_triggercat = trigCat;
  Phi_probe_dcaxy = dca;
  Phi_probe_dca = dca3d;
  Phi_probe_p = ptot;
  Phi_pair_theta = epair->pairAngle();
  Phi_probe_phidist = phiDist;
  Phi_probe_zdist = zDist;
  Phi_probe_nsige = nsige;
  Phi_probe_nsigpi = nsigpi;
  Phi_probe_nsigk = nsigk;
  Phi_probe_nsigp = nsigp;
  Phi_probe_beta = beta;
  Phi_tag_beta = tbeta;
  Phi_probe_neta = nEta;
  Phi_probe_nphi = nPhi;
  Phi_probe_emc0 = emc0;
  Phi_probe_yloc = YLoc;
  Phi_probe_charge = tp->charge();
  Phi_tag_charge = track->charge();
  Phi_probe_ncan = can;
  Phi_probe_mva = MVADec;
  Phi_tag_mva = TMVADec;
  Phi_tag_trigger = (isHLT1 && adc01>=adcCut[1])|| (isHLT2 && adc01>=adcCut[2]) || (isHLT3 && adc01>=adcCut[3]);
  Phi_tree->Fill();
}
void StPicoNpeAnaMaker::fillLambdaTree(StElectronPair * epair,StPicoTrack* tp,StPicoTrack* track,TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3, int qq, int can, double MVADec){
  float pt = tp->gPt();
  TVector3 const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  float ptot = pMom.Mag();
  float beta = 0;
  float tbeta = 0;
  float adc0 = 0;
  float adc01 = 0;
  float mass = 0;
  float YLoc = 0;
  int index2tof = tp->bTofPidTraitsIndex();
  int tindex2tof = track->bTofPidTraitsIndex();
  if(index2tof>=0) {
    StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
    if(tofPid){
      beta = tofPid->btofBeta();
      YLoc = tofPid->btofYLocal();
      mass = ptot*ptot*(1/beta/beta-1);
    }
  }
  if(tindex2tof>=0) {
    StPicoBTofPidTraits *ttofPid = mPicoDstMaker->picoDst()->btofPidTraits(tindex2tof);
    if(ttofPid){
      tbeta = ttofPid->btofBeta();
    }
  }
  float emc0 = 0;
  int nPhi=0;
  int nEta=0;
  float zDist=0;
  float phiDist=0;
  if (tp->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(tp->bemcPidTraitsIndex());
    adc0 = Emc->bemcAdc0();
    nPhi = Emc->bemcSmdNPhi();
    nEta = Emc->bemcSmdNEta();
    phiDist = Emc->bemcPhiDist();
    zDist = Emc->bemcZDist();
    
  }
  if (track->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc1 =  mPicoDstMaker->picoDst()->bemcPidTraits(track->bemcPidTraitsIndex());
    adc01 = Emc1->bemcAdc0();
  }
  float dcaz = tp->gDCAz(pVtx.z());
  float dca = tp->gDCAxy(pVtx.x(),pVtx.y());
  float dca3d = tp->gDCA(pVtx.x(),pVtx.y(),pVtx.z());
  float nsige = tp->nSigmaElectron();
  float nsigpi = tp->nSigmaPion();
  float nsigk = tp->nSigmaKaon();
  float nsigp = tp->nSigmaProton();
  float adcCut[4] = {-999, 256, 304, 416};
  int trigCat=0;
  if(isMB)trigCat = 1;
  if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2]))trigCat = 3;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2] && isHLT3 && adc0>=adcCut[3]))trigCat = 4;
  if(isMB && !((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 5;
  if(isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 6;
  if(!isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 7;
  if(((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 8;
  //if(trigCat==0)return;
  //float Dec1 = mNpeCuts->getMVADec(track);
  //float Dec2 = mNpeCuts->getMVADec2(track);
  float TMVADec = mNpeCuts->getDLL(track);//log(Dec1+2)-log(Dec2+2);
  Lambda_M = epair->pairMassKaon();
  Lambda_pair_dca = epair->pairDca();
  Lambda_probe_pt = pt;
  Lambda_triggercat = trigCat;
  Lambda_probe_dcaxy = dca;
  Lambda_probe_dca = dca3d;
  Lambda_probe_p = ptot;
  Lambda_pair_theta = epair->pairAngle();
  Lambda_probe_phidist = phiDist;
  Lambda_probe_zdist = zDist;
  Lambda_probe_nsige = nsige;
  Lambda_probe_nsigpi = nsigpi;
  Lambda_probe_nsigk = nsigk;
  Lambda_probe_nsigp = nsigp;
  Lambda_probe_beta = beta;
  Lambda_tag_beta = tbeta;
  Lambda_probe_neta = nEta;
  Lambda_probe_nphi = nPhi;
  Lambda_probe_emc0 = emc0;
  Lambda_probe_yloc = YLoc;
  Lambda_probe_charge = tp->charge();
  Lambda_tag_charge = track->charge();
  Lambda_probe_ncan = can;
  Lambda_probe_mva = MVADec;
  Lambda_tag_mva = TMVADec;
  Lambda_tag_trigger = (isHLT1 && adc01>=adcCut[1])|| (isHLT2 && adc01>=adcCut[2]) || (isHLT3 && adc01>=adcCut[3]);
  Lambda_tree->Fill();
}
void StPicoNpeAnaMaker::fillPhoETree(StElectronPair * epair,StPicoTrack* tp,StPicoTrack* track,TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3, int qq, int can, double MVADec,float cen,float qx, float qy,float qx1, float qy1,float qx2, float qy2){
  float pt = tp->gPt();
  TVector3 const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  float ptot = pMom.Mag();
  float beta = 0;
  float betat = 0;
  float adc0 = 0;
  float mass = 0;
  float YLoc = 0;
  int index2tof = tp->bTofPidTraitsIndex();
  int index2toft = track->bTofPidTraitsIndex();
  if(index2tof>=0) {
    StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
    if(tofPid){
      beta = tofPid->btofBeta();
      YLoc = tofPid->btofYLocal();
      mass = ptot*ptot*(1/beta/beta-1);
    }
  }
  if(index2toft>=0) {
    StPicoBTofPidTraits *tofPidt = mPicoDstMaker->picoDst()->btofPidTraits(index2toft);
    if(tofPidt){
      betat = tofPidt->btofBeta();
    }
  }
  float emc0 = 0;
  int nPhi=0;
  int nEta=0;
  float zDist=0;
  float phiDist=0;
  if (tp->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(tp->bemcPidTraitsIndex());
    adc0 = Emc->bemcAdc0();
    nPhi = Emc->bemcSmdNPhi();
    nEta = Emc->bemcSmdNEta();
    phiDist = Emc->bemcPhiDist();
    zDist = Emc->bemcZDist();
  }
  float dcaz = tp->gDCAz(pVtx.z());
  float dca = tp->gDCAxy(pVtx.x(),pVtx.y());
  float dca3d = tp->gDCA(pVtx.x(),pVtx.y(),pVtx.z());
  float nsige = tp->nSigmaElectron();
  float nsigpi = tp->nSigmaPion();
  float nsigk = tp->nSigmaKaon();
  float nsigp = tp->nSigmaProton();
  float adcCut[4] = {-999, 256, 304, 416};
  int trigCat=0;
  if(isMB)trigCat = 1;
  if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2]))trigCat = 3;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2] && isHLT3 && adc0>=adcCut[3]))trigCat = 4;
  if(isMB && !((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 5;
  if(isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 6;
  if(!isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 7;
  if(((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 8;
  //if(trigCat==0)return;
  PhoE_M = epair->pairMass();
  phoe_pair_decayradius = epair->pairDecayR();
  phoe_pair_dca = epair->pairDca();
  phoe_pair_theta = epair->pairAngle();
  phoe_pair_phi = epair->pairPhi();
  phoe_pair_costheta = epair->pairThetaAngle();
  phoe_probe_pt = pt;
  phoe_triggercat = trigCat;
  phoe_probe_p = ptot;
  phoe_probe_nsige = nsige;
  phoe_probe_nsigpi = nsigpi;
  phoe_probe_nsigk = nsigk;
  phoe_probe_nsigp = nsigp;
  phoe_probe_beta = beta;
  phoe_probe_phidist = phiDist;
  phoe_probe_zdist = zDist;
  phoe_probe_dcaxy = dca;
  phoe_trigger_id = trigger_id;
  phoe_probe_dca = dca3d;
  phoe_probe_dcaz = dcaz;
  phoe_probe_neta = nEta;
  phoe_probe_nphi = nPhi;
  phoe_probe_phi = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi();;
  phoe_probe_emc0 = emc0;
  phoe_probe_yloc = YLoc;
  phoe_probe_chi2 = tp->chi2();
  phoe_tag_chi2 = track->chi2();
  phoe_probe_charge = tp->charge();
  phoe_tag_charge = track->charge();
  phoe_probe_ncan = can;
  phoe_event_gweight = gweight;
  phoe_probe_mva = MVADec;
  phoe_tag_mva = mNpeCuts->getDLL(track);
  phoe_run_id = mPicoDstMaker->picoDst()->event()->runId();
  phoe_event_centrality = cen;
  phoe_event_qx = qx;
  phoe_event_qy = qy;
  phoe_event_qx1 = qx1;
  phoe_event_qy1 = qy1;
  phoe_event_qx2 = qx2;
  phoe_event_qy2 = qy2;
  phoe_tag_beta = betat;
  PhoE_tree->Fill();
}
void StPicoNpeAnaMaker::fillBKGTree(StPicoTrack* tp,TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3, double MVADec,float cen,float qx, float qy,float qx1, float qy1,float qx2, float qy2){
  float pt = tp->gPt();
  TVector3 const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  float ptot = pMom.Mag();
  float beta = 0;
  float adc0 = 0;
  float mass = 0;
  float YLoc = 0;
  int index2tof = tp->bTofPidTraitsIndex();
  if(index2tof>=0) {
    StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
    if(tofPid){
      beta = tofPid->btofBeta();
      YLoc = tofPid->btofYLocal();
      mass = ptot*ptot*(1/beta/beta-1);
    }
  }
  float emc0 = 0;
  int nPhi=0;
  int nEta=0;
  float zDist=0;
  float phiDist=0;;
  if (tp->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(tp->bemcPidTraitsIndex());
    adc0 = Emc->bemcAdc0();
    nPhi = Emc->bemcSmdNPhi();
    nEta = Emc->bemcSmdNEta();
    phiDist = Emc->bemcPhiDist();
    zDist = Emc->bemcZDist();
  }
  float dcaz = tp->gDCAz(pVtx.z());
  float dca = tp->gDCAxy(pVtx.x(),pVtx.y());
  float dca3d = tp->gDCA(pVtx.x(),pVtx.y(),pVtx.z());
  float nsige = tp->nSigmaElectron();
  float nsigpi= tp->nSigmaPion();
  float nsigk = tp->nSigmaKaon();
  float nsigp = tp->nSigmaProton();
  float adcCut[4] = {-999, 256, 304, 416};
  float BKGCat=0;
  int trigCat=0;
  if(isMB)trigCat = 1;
  if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2]))trigCat = 3;
  if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2] && isHLT3 && adc0>=adcCut[3]))trigCat = 4;
  if(isMB && !((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 5;
  if(isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 6;
  if(!isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 7;
  if(((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 8;
  //if(trigCat==0)return;
  
  if( ((mass < (0.019+0.0015)) && (mass> (0.019-0.0015)) ) && fabs(tp->nSigmaPion())<10)BKGCat=1;
  else if (  (mass< (0.019+0.003)) && (mass > (0.019-0.003)) && tp->nSigmaPion()>6)BKGCat=2;
  else if( ((mass < (0.243+0.005)) && (mass> (0.243-0.005))) && fabs(tp->nSigmaKaon())<2)BKGCat=3;
  else if( ((mass> (0.878-0.2)) && (mass<(0.878+0.2))) && fabs(tp->nSigmaProton())<2)BKGCat=4;
  bkg_probe_dcaxy = dca;
  bkg_probe_dca = dca3d;
  bkg_probe_dcaz = dcaz;
  bkg_probe_pt = pt;
  bkg_triggercat = trigCat;
  bkg_probe_p = ptot;
  bkg_probe_phidist = phiDist;
  bkg_probe_zdist = zDist;
  bkg_probe_nsige = nsige;
  bkg_probe_nsigpi = nsigpi;
  bkg_probe_nsigk = nsigk;
  bkg_probe_nsigp = nsigp;
  bkg_probe_beta = beta;
  bkg_probe_neta = nEta;
  bkg_probe_nphi = nPhi;
  bkg_probe_emc0 = emc0;
  bkg_probe_yloc = YLoc;
  bkg_probe_charge = tp->charge();
  bkg_probe_bkgcat = BKGCat;
  bkg_probe_mva = MVADec;
  bkg_run_id = mPicoDstMaker->picoDst()->event()->runId();
  bkg_event_centrality = cen;
  bkg_event_qx = qx;
  bkg_event_qx1 = qx1;
  bkg_event_qx2 = qx2;
  bkg_event_qy = qy;
  bkg_event_qy1 = qy1;
  bkg_event_qy2 = qy2;
  bkg_probe_phi = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi();
  bkg_probe_eta = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity();
  bkg_probe_phi2 = tp->pMom().Phi();//TMath::Pi()+TMath::ATan2(-pMom.y(),-pMom.x());
  
  if(BKGCat>0)BKG_tree->Fill();
}
void StPicoNpeAnaMaker::fillTree(StPicoTrack* tp,TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3,double MVADec, float cen, float qx, float qy,float qx1, float qy1,float qx2, float qy2){
  float pt = tp->gPt();
  TVector3 const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
  float ptot = pMom.Mag();
  float beta = 0;
  float adc0 = 0;
  float mass = 0;
  float YLoc = 0;
  int index2tof = tp->bTofPidTraitsIndex();
  if(index2tof>=0) {
    StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
    if(tofPid){
      beta = tofPid->btofBeta();
      YLoc = tofPid->btofYLocal();
      mass = ptot*ptot*(1/beta/beta-1);
    }
  }
  if(pt<2.5 && !mNpeCuts->isTOFElectron(tp))return;
  //if(pt>=3.5 && !mNpeCuts->isBSMDElectron(tp))return;
  float emc0 = 0;
  int nPhi=0;
  int nEta=0;
  float zDist=0;
  float phiDist=0;
  if (tp->bemcPidTraitsIndex() >= 0) {
    StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(tp->bemcPidTraitsIndex());
    adc0 = Emc->bemcAdc0();
    nPhi = Emc->bemcSmdNPhi();
    nEta = Emc->bemcSmdNEta();
    phiDist = Emc->bemcPhiDist();
    zDist = Emc->bemcZDist();
  }
  float dcaz = tp->gDCAz(pVtx.z());
  float dca = tp->gDCAxy(pVtx.x(),pVtx.y());
  float dca3d = tp->gDCA(pVtx.x(),pVtx.y(),pVtx.z());
  float nsige = tp->nSigmaElectron();
  float nsigpi = tp->nSigmaPion();
  float nsigk = tp->nSigmaKaon();
  float nsigp = tp->nSigmaProton();
  float adcCut[4] = {-999, 256, 304, 416};
  int trigCat = 0;
  if(isMB)trigCat = 1;
  if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
  if(isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2])))trigCat = 3;
  if(isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) || (isHLT3 && adc0>=adcCut[3])))trigCat = 4;
  if(isMB && !((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 5;
  if(isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 6;
  if(!isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 7;
  if(((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 8;
  //if(trigCat==0)return;
  sig_pt = pt;
  sig_trigger_id = trigger_id;
  sig_p = ptot;
  event_gweight = gweight;
  sig_chi2 = tp->chi2();
  event_qx = qx;
  event_qx1 = qx1;
  event_qx2 = qx2;
  event_qy = qy;
  event_qy1 = qy1;
  event_qy2 = qy2;
  double gap = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity();
  double Q_X=0;
  double Q_Y=0;
  double Q1_X=0;
  double Q1_Y=0;
  double Q2_X=0;
  double Q2_Y=0;
  for(int iTrack=0;iTrack< mPicoDstMaker->picoDst()->numberOfTracks();iTrack++){
    StPicoTrack* track = (StPicoTrack*) mPicoDstMaker->picoDst()->track(iTrack);
    if(!track)break;
    //if(fabs(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity()-gap)<0.1){
    //iTrack++;
    //continue;
    //}
    if(track->gPt()>0.15 && track->gPt()<2.  && !(track->nSigmaElectron()>-1 && track->nSigmaElectron()<3)){
      double ww = 0;
      if(track->gPt()<=2.)ww = track->gPt();
      if(track->gPt()>2.)ww = 2;
      
      if(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()>0.2 && track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()<1. ){
        Q1_X += ww*TMath::Cos(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
        Q1_Y += ww*TMath::Sin(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
      }
      if(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()<-0.2 && track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()>-1. ){
        Q2_X += ww*TMath::Cos(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
        Q2_Y += ww*TMath::Sin(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
      }
      if(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()<1. && track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()>-1. ){
        Q_X += ww*TMath::Cos(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
        Q_Y += ww*TMath::Sin(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
      }
    }
  }
  
  event_g_qx = Q_X;
  event_g_qx1 = Q1_X;
  event_g_qx2 = Q2_X;
  event_g_qy = Q_Y;
  event_g_qy1 = Q1_Y;
  event_g_qy2 = Q2_Y;
  sig_triggercat = trigCat;
  sig_nsige = nsige;
  sig_isiso =  isIso(tp);
  sig_nsigpi = nsigpi;
  sig_nsigk = nsigk;
  sig_nsigp = nsigp;
  sig_beta = beta;
  sig_phidist = phiDist;
  sig_zdist = zDist;
  sig_dcaxy = dca;
  sig_dcaz = dcaz;
  sig_dca = dca3d;
  event_ep1 = mEP1;
  sig_eta = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity();
  sig_phi = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi();
  sig_phi2 = tp->pMom().Phi();//TMath::Pi()+TMath::ATan2(-pMom.y(),-pMom.x());
  sig_neta = nEta;
  sig_nphi = nPhi;
  sig_emc0 = emc0;
  sig_yloc = YLoc;
  sig_charge = tp->charge();
  sig_mva = MVADec;
  sig_mva_ht = 0;//mNpeCuts->getDLL_HT(tp);
  event_centrality = cen;
  run_id = mPicoDstMaker->picoDst()->event()->runId();
  event_id = mPicoDstMaker->picoDst()->event()->eventId();
  Signal_tree->Fill();
}
void StPicoNpeAnaMaker::fillEventTree(float cen, float qx, float qy,float qx1, float qy1,float qx2, float qy2){
  ep_event_qx = qx;
  ep_event_qx1 = qx1;
  ep_event_qx2 = qx2;
  ep_event_qy = qy;
  ep_event_qy1 = qy1;
  ep_event_qy2 = qy2;
  ep_event_centrality = cen;
  ep_run_id = mPicoDstMaker->picoDst()->event()->runId();
  Event_tree->Fill();
}
/*void StPicoNpeAnaMaker::fillEHTree(StPicoTrack *electron, StPicoTrack *partner, TVector3 pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3,float cen, float qx, float qy,float qx1, float qy1,float qx2, float qy2,int ncan,double MVADec){
 
 if ((!electron || !partner) || (electron->id() == partner->id()))return;
 float pt = electron->gPt();
 float adcCut[4] = {-999, 256, 304, 416};
 double adc0=0;
 double nPhi=0;
 double nEta=0;
 if (electron->bemcPidTraitsIndex() >= 0) {
 StPicoBEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->bemcPidTraits(electron->bemcPidTraitsIndex());
 adc0 = Emc->bemcAdc0();
 nPhi = Emc->bemcSmdNPhi();
 nEta = Emc->bemcSmdNEta();
 }
 double beta=0;
 int index2tof = partner->bTofPidTraitsIndex();
 if(index2tof>=0) {
 StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
 if(tofPid){
 beta = tofPid->btofBeta();
 }
 }
 if(pt<2.5 && !mNpeCuts->isTOFElectron(electron))return;
 StPhysicalHelixD electronHelix = electron->dcaGeometry().helix();
 StPhysicalHelixD partnerHelix = partner->dcaGeometry().helix();
 
 // normal method
 
 pair<double,double> ss = electronHelix.pathLengths(partnerHelix);
 StThreeVectorD kAtDcaToPartner = electronHelix.at(ss.first);
 StThreeVectorD pAtDcaToElectron = partnerHelix.at(ss.second);
 
 // calculate DCA of partner to electron at their DCA
 StThreeVectorD VectorDca = kAtDcaToPartner - pAtDcaToElectron;
 StThreeVectorD DecayPoint = (kAtDcaToPartner/2 + pAtDcaToElectron/2) - pVtx;
 StThreeVectorD DecayPos = (kAtDcaToPartner/2 + pAtDcaToElectron/2);
 //mPairDecayR = static_cast<float>(DecayPoint.mag());
 eh_pair_decayr = static_cast<float>(sqrt(DecayPoint.x()*DecayPoint.x()+DecayPoint.y()*DecayPoint.y()+DecayPoint.z()*DecayPoint.z()));
 eh_pair_decaypos = static_cast<float>(sqrt(DecayPos.x()*DecayPos.x()+DecayPos.y()*DecayPos.y()));
 eh_pair_dca = static_cast<float>(VectorDca.mag());
 
 // calculate Lorentz vector of electron-partner pair
 StThreeVectorD const electronMomAtDca = electronHelix.momentumAt(ss.first, mPicoDstMaker->picoDst()->event()->bField() * kilogauss);
 StThreeVectorD const partnerMomAtDca = partnerHelix.momentumAt(ss.second,mPicoDstMaker->picoDst()->event()->bField()  * kilogauss);
 
 StThreeVectorF temp1 (electronMomAtDca.x(),electronMomAtDca.y(),0);
 StThreeVectorF temp2 (partnerMomAtDca.x(),partnerMomAtDca.y(),0);
 StThreeVectorF temp3 (0,electronMomAtDca.y(),electronMomAtDca.z());
 StThreeVectorF temp4 (0,partnerMomAtDca.y(),partnerMomAtDca.z());
 
 eh_pair_angle = electronMomAtDca.angle(partnerMomAtDca);
 eh_pair_thetaangle=temp1.angle(temp2);
 eh_pair_phi=temp3.angle(temp4);
 eh_e_px = electronMomAtDca.x();
 eh_e_py = electronMomAtDca.y();
 eh_e_pz = electronMomAtDca.z();
 eh_h_px = partnerMomAtDca.x();
 eh_h_py = partnerMomAtDca.y();
 eh_h_pz = partnerMomAtDca.z();
 eh_event_gweight = gweight;
 
 //StLorentzVectorF const electronFourMom(electronMomAtDca, electronMomAtDca.massHypothesis(Melectron));
 //StLorentzVectorF const partnerFourMom(partnerMomAtDca, partnerMomAtDca.massHypothesis(Melectron));
 
 StLorentzVectorD electronFourMom(0,0,0,0);
 StLorentzVectorD partnerFourMom(0,0,0,0);
 
 electronFourMom.setPx(electronMomAtDca.x());
 electronFourMom.setPy(electronMomAtDca.y());
 electronFourMom.setPz(electronMomAtDca.z());
 electronFourMom.setE(sqrt(electronMomAtDca.x()*electronMomAtDca.x()
 + electronMomAtDca.y()*electronMomAtDca.y()
 + electronMomAtDca.z()*electronMomAtDca.z() + 0.00051099907*0.00051099907));
 
 partnerFourMom.setPx(partnerMomAtDca.x());
 partnerFourMom.setPy(partnerMomAtDca.y());
 partnerFourMom.setPz(partnerMomAtDca.z());
 partnerFourMom.setE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
 + partnerMomAtDca.y()*partnerMomAtDca.y()
 + partnerMomAtDca.z()*partnerMomAtDca.z()
 + 0.1396*0.1396));
 
 StLorentzVectorF const epairFourMom = electronFourMom + partnerFourMom;
 
 eh_eta = epairFourMom.PseudoRapidity();
 eh_phi = epairFourMom.phi();
 eh_mass = epairFourMom.m();
 
 StThreeVectorD pair_mom(epairFourMom.x(),epairFourMom.y(),epairFourMom.z());
 StThreeVectorD Position = (kAtDcaToPartner + pAtDcaToElectron)/2.0;
 StPhysicalHelixD eHelix(pair_mom,Position,0,0);
 
 eh_dcaxy = eHelix.geometricSignedDistance(pVtx.x(),pVtx.y());
 eh_dca = eHelix.geometricSignedDistance(pVtx);
 eh_e_mva = MVADec;
 eh_endvertex_x = Position.x();
 eh_endvertex_y = Position.y();
 eh_endvertex_z = Position.z();
 eh_vertex_x = pVtx.x();
 eh_vertex_y = pVtx.y();
 eh_vertex_z = pVtx.z();
 int trigCat = 0;
 if(isMB)trigCat = 1;
 if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
 if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2]))trigCat = 3;
 if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2] && isHLT3 && adc0>=adcCut[3]))trigCat = 4;
 if(isMB && !((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 5;
 if(isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 6;
 if(!isMB && ((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 7;
 if(((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 8;
 
 eh_triggercat = trigCat;
 eh_event_centrality = cen;
 eh_event_qx = qx;
 eh_event_qy = qy;
 eh_event_qx1 = qx1;
 eh_event_qy1 = qy1;
 eh_event_qx2 = qx2;
 eh_event_qy2 = qy2;
 double gap = electron->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity();
 int iTrack=0;
 double Q_X=0;
 double Q_Y=0;
 double Q1_X=0;
 double Q1_Y=0;
 double Q2_X=0;
 double Q2_Y=0;
 while (1)
 {
 StPicoTrack* track = (StPicoTrack*) mPicoDstMaker->picoDst()->track(iTrack);
 if(!track)break;
 if(fabs(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()-gap)<0.1){
 iTrack++;
 continue;
 }
 if(track->gPt()>0.15 && track->gPt()<2.  && !(track->nSigmaElectron()>-1 && track->nSigmaElectron()<3)){
 double ww = 0;
 if(track->gPt()<=2.)ww = track->gPt();
 if(track->gPt()>2.)ww = 2;
 
 if(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()>0.05 && track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()<1. ){
 Q1_X += ww*TMath::Cos(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
 Q1_Y += ww*TMath::Sin(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
 }
 if(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()<-0.05 && track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()>-1. ){
 Q2_X += ww*TMath::Cos(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
 Q2_Y += ww*TMath::Sin(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
 }
 if(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()<1. && track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).PseudoRapidity()>-1. ){
 Q_X += ww*TMath::Cos(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
 Q_Y += ww*TMath::Sin(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).Phi());
 }
 }
 iTrack++;
 }
 eh_event_g_qx = Q_X;
 eh_event_g_qx1 = Q1_X;
 eh_event_g_qx2 = Q2_X;
 eh_event_g_qy = Q_Y;
 eh_event_g_qy1 = Q1_Y;
 eh_event_g_qy2 = Q2_Y ;
 
 
 eh_e_charge = electron->charge();
 eh_e_dcaxy = electronHelix.geometricSignedDistance(pVtx.x(),pVtx.y());
 eh_h_dcaxy = partnerHelix.geometricSignedDistance(pVtx.x(),pVtx.y());
 eh_e_dca = electronHelix.geometricSignedDistance(pVtx);
 eh_h_dca = partnerHelix.geometricSignedDistance(pVtx);
 eh_h_charge = partner->charge();
 eh_h_nsigpi = partner->nSigmaPion();
 eh_h_nsige = partner->nSigmaElectron();
 eh_e_nsige = electron->nSigmaElectron();
 eh_h_nsigk = partner->nSigmaKaon();
 eh_h_beta = beta;
 eh_h_isprimary = 0;//partner->isPrimary();
 eh_e_isprimary = 0;//electron->isPrimary();
 eh_run_id = mPicoDstMaker->picoDst()->event()->runId();
 eh_ncan = ncan;
 //if(0){
 //if(fabs(eh_h_dca)>0.05)hFit_EH[0]->Fill(pt,electron->nSigmaElectron());
 //if(fabs(eh_h_dca)>0.1)hFit_EH[1]->Fill(pt,electron->nSigmaElectron());
 //if(fabs(eh_h_dca)>0.15)hFit_EH[2]->Fill(pt,electron->nSigmaElectron());
 //if(electron->nSigmaElectron()>-1 && electron->nSigmaElectron()<3)EH_tree->Fill();
 //}
 }
 */
bool StPicoNpeAnaMaker::isIso(StPicoTrack  const *tp){
  //cout << " Iso track size " << mIsoEs.size() << endl;
  bool dec = true;
  for(int i=0;i<int(mIsoEs.size());i++){
    if(mIsoEs[i] == tp->id())continue;
    StPicoTrack* track1 = (StPicoTrack*) mPicoDstMaker->picoDst()->track(mIsoEs[i]);
    StElectronPair *elecPair = new StElectronPair(track1,tp,mIsoEs[i],tp->id(),mPicoDstMaker->picoDst()->event()->bField(),mPicoDstMaker->picoDst()->event()->primaryVertex());
    double mass = elecPair->pairMass();
    double dca = elecPair->pairDca();
    double decayr = elecPair->pairDecayR();
    double prod = track1->charge()*tp->charge();
    if(mass<0.15 && dca<0.2 && prod<0 && decayr<9) dec = false;
    elecPair->Delete();
  }
  return dec;
}

float StPicoNpeAnaMaker::ZDCSMD(int eastwest,int verthori,int strip) const {
  float retval=0;
  
  if (eastwest==0 && verthori==1) {
    retval = (mPicoDstMaker->picoDst()->event()->ZdcSmdEastHorizontal(strip)
              -zdcconst::zdcsmdPedstal[0][1][strip])/zdcconst::zdcsmdGainFac[0][1][strip];
  }
  if (eastwest==0 && verthori==0) {
    retval = (mPicoDstMaker->picoDst()->event()->ZdcSmdEastVertical(strip)
              -zdcconst::zdcsmdPedstal[0][0][strip])/zdcconst::zdcsmdGainFac[0][0][strip];
  }
  if (eastwest==1 && verthori==1) {
    retval = (mPicoDstMaker->picoDst()->event()->ZdcSmdWestHorizontal(strip)
              -zdcconst::zdcsmdPedstal[1][1][strip])/zdcconst::zdcsmdGainFac[1][1][strip];
  }
  if (eastwest==1 && verthori==0) {
    retval = (mPicoDstMaker->picoDst()->event()->ZdcSmdWestVertical(strip)
              -zdcconst::zdcsmdPedstal[1][0][strip])/zdcconst::zdcsmdGainFac[1][0][strip];
  }
  
  return retval;
}
Float_t StPicoNpeAnaMaker::ZDCSMD_GetPosition(int eastwest,int verthori,int strip) {
  
  if (ZDCCalib>=2) {
    if(eastwest==0 && verthori==0) return zdcconst::zdcsmd_x[strip]-ZDCSMDCenterex;
    if(eastwest==1 && verthori==0) return ZDCSMDCenterwx-zdcconst::zdcsmd_x[strip];
    if(eastwest==0 && verthori==1) return zdcconst::zdcsmd_y[strip]/sqrt(2.)-ZDCSMDCenterey;
    if(eastwest==1 && verthori==1) return zdcconst::zdcsmd_y[strip]/sqrt(2.)-ZDCSMDCenterwy;
  }
  if (ZDCCalib<2) {
    if(eastwest==0 && verthori==0) return zdcconst::zdcsmd_x[strip];
    if(eastwest==1 && verthori==0) return -zdcconst::zdcsmd_x[strip];
    if(eastwest==0 && verthori==1) return zdcconst::zdcsmd_y[strip]/sqrt(2.);
    if(eastwest==1 && verthori==1) return zdcconst::zdcsmd_y[strip]/sqrt(2.);
  }
  return 0;
}TVector2 StPicoNpeAnaMaker::ZDCSMD_QEst() {
  TVector2 mQ;
  Float_t eXsum=0.,eYsum=0.,eXWgt=0.,eYWgt=0.;
  
  for(int v=0;v<7;v++) {
    eXsum += ZDCSMD_GetPosition(0,0,v)*ZDCSMD(0,0,v);
    eXWgt += ZDCSMD(0,0,v);
  }//v
  for(int h=0;h<8;h++) {
    eYsum += ZDCSMD_GetPosition(0,1,h)*ZDCSMD(0,1,h);
    eYWgt += ZDCSMD(0,1,h);
  }//h
  mQ.Set((eXWgt>0.) ? eXsum/eXWgt:0.,(eYWgt>0.) ? eYsum/eYWgt:0.);
  return mQ;
}

TVector2 StPicoNpeAnaMaker::ZDCSMD_QWst() {
  TVector2 mQ;
  Float_t wXsum=0.,wYsum=0.,wXWgt=0.,wYWgt=0.;
  
  for(int v=0;v<7;v++) {
    wXsum += ZDCSMD_GetPosition(1,0,v)*ZDCSMD(1,0,v);
    wXWgt += ZDCSMD(1,0,v);
  }//v
  for(int h=0;h<8;h++) {
    wYsum += ZDCSMD_GetPosition(1,1,h)*ZDCSMD(1,1,h);
    wYWgt += ZDCSMD(1,1,h);
  }//h
  mQ.Set((wXWgt>0.) ? wXsum/wXWgt:0.,(wYWgt>0.) ? wYsum/wYWgt:0.);
  return mQ;
}
TVector2 StPicoNpeAnaMaker::get_recenteredQ(const TVector2& Q, int cent, int runIndx, int iep) {
  TVector2 Qrc=Q, Qcenter;
  
  Qcenter.Set(ZDCEPRecenter_x[cent]->GetBinContent(iep+1,runIndx+1), ZDCEPRecenter_y[cent]->GetBinContent(iep+1,runIndx+1));
  Qrc -= Qcenter;
  return Qrc;
}
TVector2 StPicoNpeAnaMaker::get_shiftedQ(const TVector2& Q, int cent, int iep) {
  TVector2 Qsh; float Psi = Q.Phi(), Psi_sh=Psi;
  for (int j=1;j<9;j++) Psi_sh += 2*( -ZDCEPShift_sin[cent]->GetBinContent(iep+1,j)*cos(j*Psi) + ZDCEPShift_cos[cent]->GetBinContent(iep+1,j)*sin(j*Psi))/(float)j;
  
  Qsh.Set( Q.Mod()*cos(Psi_sh), Q.Mod()*sin(Psi_sh));
  return Qsh;
}
float StPicoNpeAnaMaker::getZDCEPCor(float psi_a, float psi_b) {
  psi_b += zdcconst::PI;
  if (psi_b<0)    psi_b += 2*zdcconst::PI;
  if (psi_b>2*zdcconst::PI) psi_b -= 2*zdcconst::PI;
  
  float dpsi = psi_a - psi_b;
  if (dpsi<0)    dpsi += 2*zdcconst::PI;
  if (dpsi>2*zdcconst::PI) dpsi -= 2*zdcconst::PI;
  
  return dpsi;
}
int StPicoNpeAnaMaker::get_runIndex(int run) {
  
  int indx=-1;
  try {
    indx = mGoodRunMap.at(run);
  }
  catch (std::exception& excp1) {
    indx=-1;
  }
  return indx;
}
int StPicoNpeAnaMaker::get_centbShit(int ntrk) {
  
  static const int centCuts[] = {517, 477, 445, 416, 389, 363, 339, 316, 294, 273, 253, 234, 216, 199, 185, 168, 154, 141, 129, 119, 107, 97, 88, 79, 72, 64, 57, 51, 45, 40, 35, 31, 27, 23, 20, 17, 14, 12, 10, 8};
  
  int indx=-1;
  for (int ic=0;ic<NCENTSHIFT;ic++) {
    if (ntrk >= centCuts[ic]) {indx=ic; break;}
  }
  return indx;
}
int StPicoNpeAnaMaker::get_zdcXbin(float zdcx) {
  
  static float zdcxbins[] = {0,40,50,60,70,200};
  float zdcxkhz = zdcx/1e3;
  int zbin=-1;
  for (int iz=0;iz<NZDCX;iz++) {
    if (zdcxkhz>=zdcxbins[iz] && zdcxkhz<zdcxbins[iz+1]) {zbin=iz; break;}
  }
  if (zdcxkhz<zdcxbins[0]) zbin=0;
  if (zdcxkhz>=zdcxbins[NZDCX]) zbin=NZDCX-1;
  return zbin;
  
}

