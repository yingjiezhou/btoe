//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar  8 01:24:07 2018 by ROOT version 5.34/30
// from TTree nt/
// found on file: DsSimu_Eff4.root
//////////////////////////////////////////////////////////

#ifndef EffSelector_h
#define EffSelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TTree.h"
#include "THnSparse.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class EffSelector : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  UInt_t         fNumberOfEvents;
     UInt_t         decayCh;
bool PassTpcAcc;
bool PassHft;
bool PassTopology;

   TH1F    *PassTpcHftPidTopoBDT_4080[41];

   TH1F    *AllCounts_46;
   TH1F     *PassTpc_46;
   TH1F     *PassAcc_46;
  TH1F      *PassTpcHft_46;
  TH1F       *PassTpcHftPid_46;
  TH1F         *PassTpcHftPidTopoBDT_46;
//  TH1F         *PassTpcHftPidTopoBDT_46[61];
  TH1F          *PassTpcHftPidTopo_46;

   TH1F    *AllCounts_68;
   TH1F     *PassTpc_68;
   TH1F     *PassAcc_68;
  TH1F      *PassTpcHft_68;
  TH1F       *PassTpcHftPid_68;
  TH1F         *PassTpcHftPidTopoBDT_68;
  //TH1F         *PassTpcHftPidTopoBDT_68[61];
  TH1F          *PassTpcHftPidTopo_68;

 TH1F    *AllCounts_1040_1525;
   TH1F     *PassTpc_1040_1525;
   TH1F     *PassAcc_1040_1525;
  TH1F      *PassTpcHft_1040_1525;
  TH1F       *PassTpcHftPid_1040_1525;
  TH1F         *PassTpcHftPidTopoBDT_1040_1525;
  TH1F          *PassTpcHftPidTopo_1040_1525;

   TH1F    *h1PhiMass;
   TH1F    *h1PhiMass_cut;

   TH1F    *AllCounts[5];
   TH1F     *PassTpc[5];
   TH1F     *PassAcc[5];
  TH1F      *PassTpcHft[5];
  TH1F       *PassTpcHftPid[5];
  TH1F         *PassTpcHftPidTopoBDT[5];
//  TH1F         *PassTpcHftPidTopoBDT[5][61];
  TH1F         *PassTpcHftPidTopo[5];
 TH2F           *BDT_response_TpcPidWeight_pT2D[5];
 TH2F           *BDT_response_pT2D[5];
 
 TH3D         *response_h3;
 TH3D         *rPt_pi_h3;
 TH3D             *rPt_k1_h3;
 TH3D           *rPt_k2_h3;
 TH3D           *piDca_h3;
 TH3D           *k1Dca_h3;
 TH3D          *k2Dca_h3;
 TH3D          *CosTheta_h3;
 TH3D          *decayLength_h3;
 TH3D          *dcaDaughters_h3;
 TH3D          *massDiff_h3;
 TH3D          *Mass_Phi_h3;
 TH3D          *rM_Ds_h3;

 TH3D         *response_h3_BDTcut;
 TH3D         *rPt_pi_h3_BDTcut;
 TH3D             *rPt_k1_h3_BDTcut;
 TH3D           *rPt_k2_h3_BDTcut;
 TH3D           *piDca_h3_BDTcut;
 TH3D           *k1Dca_h3_BDTcut;
 TH3D          *k2Dca_h3_BDTcut;
 TH3D          *CosTheta_h3_BDTcut;
 TH3D          *decayLength_h3_BDTcut;
 TH3D          *dcaDaughters_h3_BDTcut;
 TH3D          *massDiff_h3_BDTcut;
 TH3D          *Mass_Phi_h3_BDTcut;
 TH3D          *rM_Ds_h3_BDTcut;
 //float ncoll[9];
TF1* pTSpectra_Data;
 TF1* gf1AuAu010Weight;
TTree *DsSig;
   // Declaration of leaf types
   Float_t         cent;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Float_t         vzIdx;
   Float_t         RDca12;
   Float_t         Phimass;
   Float_t         massDiff;
   Float_t         massDiff2;
   Float_t         rPt12;
   Float_t         rPt_Phi;
   Float_t         Mass_Phi;
   Float_t         pid;
   Float_t         w;
   Float_t         PIDweight;
   Float_t         m;
   Float_t         pt;
   Float_t         eta;
   Float_t         y;
   Float_t         phi;
   Float_t         v00x;
   Float_t         v00y;
   Float_t         v00z;
   Float_t         rM;
   Float_t         rPt;
   Float_t         rEta;
   Float_t         rY;
   Float_t         rPhi;
   Float_t         rV0x;
   Float_t         rV0y;
   Float_t         rV0z;
   Float_t         rV12x;
   Float_t         rV12y;
   Float_t         rV12z;
   Float_t         rV23x;
   Float_t         rV23y;
   Float_t         rV23z;
   Float_t         rV31x;
   Float_t         rV31y;
   Float_t         rV31z;
   Float_t         dcaDaughters;
   Float_t         decayLength;
   Float_t         dcaLcToPv;
   Float_t         cosTheta;
   Float_t         anglekpi;
   Float_t         cosThetaStar;
   Float_t         Dcakpi;
   Float_t         Dcapip;
   Float_t         Dcapk;
   Float_t         kM;
   Float_t         kPt;
   Float_t         kEta;
   Float_t         kY;
   Float_t         kPhi;
   Float_t         kDca;
   Float_t         kRM;
   Float_t         rPtk1;
   Float_t         kREta;
   Float_t         kRY;
   Float_t         kRPhi;
   Float_t         kRV00x;
   Float_t         kRV00y;
   Float_t         kRV00z;
   Float_t         k1RDca;
   Float_t         kRSDca;
   Float_t         kRDcaXY;
   Float_t         kRDcaZ;
   Float_t         kEtaIdx;
   Float_t         kPtIdx;
   Float_t         kTpc;
   Float_t         piM;
   Float_t         piPt;
   Float_t         piEta;
   Float_t         piY;
   Float_t         piPhi;
   Float_t         piDca;
   Float_t         piRM;
   Float_t         rPtpi;
   Float_t         piREta;
   Float_t         piRY;
   Float_t         piRPhi;
   Float_t         piRV00x;
   Float_t         piRV00y;
   Float_t         piRV00z;
   Float_t         piRDca;
   Float_t         piRSDca;
   Float_t         piRDcaXY;
   Float_t         piRDcaZ;
   Float_t         piEtaIdx;
   Float_t         piPtIdx;
   Float_t         piTpc;
   Float_t         pM;
   Float_t         pPt;
   Float_t         pEta;
   Float_t         pY;
   Float_t         pPhi;
   Float_t         pDca;
   Float_t         pRM;
   Float_t         rPtk2;
   Float_t         pREta;
   Float_t         pRY;
   Float_t         pRPhi;
   Float_t         pRV00x;
   Float_t         pRV00y;
   Float_t         pRV00z;
   Float_t         k2RDca;
   Float_t         pRSDca;
   Float_t         pRDcaXY;
   Float_t         pRDcaZ;
   Float_t         pEtaIdx;
   Float_t         pPtIdx;
   Float_t         pTpc;
   Float_t         kHft;
   Float_t         piHft;
   Float_t         pHft;
   Float_t         flag;
  Float_t         mva_BDT;
  Float_t         TpcWeight; 
  // List of branches
   TBranch        *b_cent;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_vzIdx;   //!
   TBranch        *b_RDca12;   //!
   TBranch        *b_Phimass;   //!
   TBranch        *b_massDiff;   //!
   TBranch        *b_massDiff2;   //!
   TBranch        *b_rPt12;   //!
   TBranch        *b_rPt_Phi;   //!
   TBranch        *b_Mass_Phi;   //!
   TBranch        *b_pid;   //!
   TBranch        *b_w;   //!
   TBranch        *b_PIDweight;   //!
   TBranch        *b_m;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_y;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_v00x;   //!
   TBranch        *b_v00y;   //!
   TBranch        *b_v00z;   //!
   TBranch        *b_rM;   //!
   TBranch        *b_rPt;   //!
   TBranch        *b_rEta;   //!
   TBranch        *b_rY;   //!
   TBranch        *b_rPhi;   //!
   TBranch        *b_rV0x;   //!
   TBranch        *b_rV0y;   //!
   TBranch        *b_rV0z;   //!
   TBranch        *b_rV12x;   //!
   TBranch        *b_rV12y;   //!
   TBranch        *b_rV12z;   //!
   TBranch        *b_rV23x;   //!
   TBranch        *b_rV23y;   //!
   TBranch        *b_rV23z;   //!
   TBranch        *b_rV31x;   //!
   TBranch        *b_rV31y;   //!
   TBranch        *b_rV31z;   //!
   TBranch        *b_dcaDaughters;   //!
   TBranch        *b_decayLength;   //!
   TBranch        *b_dcaLcToPv;   //!
   TBranch        *b_cosTheta;   //!
   TBranch        *b_anglekpi;   //!
   TBranch        *b_cosThetaStar;   //!
   TBranch        *b_Dcakpi;   //!
   TBranch        *b_Dcapip;   //!
   TBranch        *b_Dcapk;   //!
   TBranch        *b_kM;   //!
   TBranch        *b_kPt;   //!
   TBranch        *b_kEta;   //!
   TBranch        *b_kY;   //!
   TBranch        *b_kPhi;   //!
   TBranch        *b_kDca;   //!
   TBranch        *b_kRM;   //!
   TBranch        *b_rPtk1;   //!
   TBranch        *b_kREta;   //!
   TBranch        *b_kRY;   //!
   TBranch        *b_kRPhi;   //!
   TBranch        *b_kRV00x;   //!
   TBranch        *b_kRV00y;   //!
   TBranch        *b_kRV00z;   //!
   TBranch        *b_k1RDca;   //!
   TBranch        *b_kRSDca;   //!
   TBranch        *b_kRDcaXY;   //!
   TBranch        *b_kRDcaZ;   //!
   TBranch        *b_kEtaIdx;   //!
   TBranch        *b_kPtIdx;   //!
   TBranch        *b_kTpc;   //!
   TBranch        *b_piM;   //!
   TBranch        *b_piPt;   //!
   TBranch        *b_piEta;   //!
   TBranch        *b_piY;   //!
   TBranch        *b_piPhi;   //!
   TBranch        *b_piDca;   //!
   TBranch        *b_piRM;   //!
   TBranch        *b_rPtpi;   //!
   TBranch        *b_piREta;   //!
   TBranch        *b_piRY;   //!
   TBranch        *b_piRPhi;   //!
   TBranch        *b_piRV00x;   //!
   TBranch        *b_piRV00y;   //!
   TBranch        *b_piRV00z;   //!
   TBranch        *b_piRDca;   //!
   TBranch        *b_piRSDca;   //!
   TBranch        *b_piRDcaXY;   //!
   TBranch        *b_piRDcaZ;   //!
   TBranch        *b_piEtaIdx;   //!
   TBranch        *b_piPtIdx;   //!
   TBranch        *b_piTpc;   //!
   TBranch        *b_pM;   //!
   TBranch        *b_pPt;   //!
   TBranch        *b_pEta;   //!
   TBranch        *b_pY;   //!
   TBranch        *b_pPhi;   //!
   TBranch        *b_pDca;   //!
   TBranch        *b_pRM;   //!
   TBranch        *b_rPtk2;   //!
   TBranch        *b_pREta;   //!
   TBranch        *b_pRY;   //!
   TBranch        *b_pRPhi;   //!
   TBranch        *b_pRV00x;   //!
   TBranch        *b_pRV00y;   //!
   TBranch        *b_pRV00z;   //!
   TBranch        *b_k2RDca;   //!
   TBranch        *b_pRSDca;   //!
   TBranch        *b_pRDcaXY;   //!
   TBranch        *b_pRDcaZ;   //!
   TBranch        *b_pEtaIdx;   //!
   TBranch        *b_pPtIdx;   //!
   TBranch        *b_pTpc;   //!
   TBranch        *b_kHft;   //!
   TBranch        *b_piHft;   //!
   TBranch        *b_pHft;   //!
   TBranch        *b_flag;   //!
   TBranch        *b_mBdt    ;   //!
   TBranch        *b_TpcWeight ;
   EffSelector(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~EffSelector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(EffSelector,0);
};

#endif

#ifdef EffSelector_cxx
void EffSelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("cent", &cent, &b_cent);
   fChain->SetBranchAddress("vx", &vx, &b_vx);
   fChain->SetBranchAddress("vy", &vy, &b_vy);
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("vzIdx", &vzIdx, &b_vzIdx);
   fChain->SetBranchAddress("RDca12", &RDca12, &b_RDca12);
   fChain->SetBranchAddress("Phimass", &Phimass, &b_Phimass);
   fChain->SetBranchAddress("massDiff", &massDiff, &b_massDiff);
   //fChain->SetBranchAddress("massDiff2", &massDiff2, &b_massDiff2);
   fChain->SetBranchAddress("rPt12", &rPt12, &b_rPt12);
   fChain->SetBranchAddress("rPt_Phi", &rPt_Phi, &b_rPt_Phi);
 //  fChain->SetBranchAddress("Mass_Phi", &Mass_Phi, &b_Mass_Phi);
   fChain->SetBranchAddress("pid", &pid, &b_pid);
   fChain->SetBranchAddress("w", &w, &b_w);
   fChain->SetBranchAddress("PIDweight", &PIDweight, &b_PIDweight);
   fChain->SetBranchAddress("m", &m, &b_m);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("eta", &eta, &b_eta);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("v00x", &v00x, &b_v00x);
   fChain->SetBranchAddress("v00y", &v00y, &b_v00y);
   fChain->SetBranchAddress("v00z", &v00z, &b_v00z);
   fChain->SetBranchAddress("rM", &rM, &b_rM);
   fChain->SetBranchAddress("rPt", &rPt, &b_rPt);
   fChain->SetBranchAddress("rEta", &rEta, &b_rEta);
   fChain->SetBranchAddress("rY", &rY, &b_rY);
   fChain->SetBranchAddress("rPhi", &rPhi, &b_rPhi);
   fChain->SetBranchAddress("rV0x", &rV0x, &b_rV0x);
   fChain->SetBranchAddress("rV0y", &rV0y, &b_rV0y);
   fChain->SetBranchAddress("rV0z", &rV0z, &b_rV0z);
   fChain->SetBranchAddress("rV12x", &rV12x, &b_rV12x);
   fChain->SetBranchAddress("rV12y", &rV12y, &b_rV12y);
   fChain->SetBranchAddress("rV12z", &rV12z, &b_rV12z);
   fChain->SetBranchAddress("rV23x", &rV23x, &b_rV23x);
   fChain->SetBranchAddress("rV23y", &rV23y, &b_rV23y);
   fChain->SetBranchAddress("rV23z", &rV23z, &b_rV23z);
   fChain->SetBranchAddress("rV31x", &rV31x, &b_rV31x);
   fChain->SetBranchAddress("rV31y", &rV31y, &b_rV31y);
   fChain->SetBranchAddress("rV31z", &rV31z, &b_rV31z);
   fChain->SetBranchAddress("dcaDaughters", &dcaDaughters, &b_dcaDaughters);
   fChain->SetBranchAddress("decayLength", &decayLength, &b_decayLength);
   fChain->SetBranchAddress("dcaLcToPv", &dcaLcToPv, &b_dcaLcToPv);
   fChain->SetBranchAddress("cosTheta", &cosTheta, &b_cosTheta);
   fChain->SetBranchAddress("anglekpi", &anglekpi, &b_anglekpi);
   fChain->SetBranchAddress("cosThetaStar", &cosThetaStar, &b_cosThetaStar);
   fChain->SetBranchAddress("Dcakpi", &Dcakpi, &b_Dcakpi);
   fChain->SetBranchAddress("Dcapip", &Dcapip, &b_Dcapip);
   fChain->SetBranchAddress("Dcapk", &Dcapk, &b_Dcapk);
   fChain->SetBranchAddress("kM", &kM, &b_kM);
   fChain->SetBranchAddress("kPt", &kPt, &b_kPt);
   fChain->SetBranchAddress("kEta", &kEta, &b_kEta);
   fChain->SetBranchAddress("kY", &kY, &b_kY);
   fChain->SetBranchAddress("kPhi", &kPhi, &b_kPhi);
   fChain->SetBranchAddress("kDca", &kDca, &b_kDca);
   fChain->SetBranchAddress("kRM", &kRM, &b_kRM);
   fChain->SetBranchAddress("rPtk1", &rPtk1, &b_rPtk1);
   fChain->SetBranchAddress("kREta", &kREta, &b_kREta);
   fChain->SetBranchAddress("kRY", &kRY, &b_kRY);
   fChain->SetBranchAddress("kRPhi", &kRPhi, &b_kRPhi);
   fChain->SetBranchAddress("kRV00x", &kRV00x, &b_kRV00x);
   fChain->SetBranchAddress("kRV00y", &kRV00y, &b_kRV00y);
   fChain->SetBranchAddress("kRV00z", &kRV00z, &b_kRV00z);
   fChain->SetBranchAddress("k1RDca", &k1RDca, &b_k1RDca);
   fChain->SetBranchAddress("kRSDca", &kRSDca, &b_kRSDca);
   fChain->SetBranchAddress("kRDcaXY", &kRDcaXY, &b_kRDcaXY);
   fChain->SetBranchAddress("kRDcaZ", &kRDcaZ, &b_kRDcaZ);
   fChain->SetBranchAddress("kEtaIdx", &kEtaIdx, &b_kEtaIdx);
   fChain->SetBranchAddress("kPtIdx", &kPtIdx, &b_kPtIdx);
   fChain->SetBranchAddress("kTpc", &kTpc, &b_kTpc);
   fChain->SetBranchAddress("piM", &piM, &b_piM);
   fChain->SetBranchAddress("piPt", &piPt, &b_piPt);
   fChain->SetBranchAddress("piEta", &piEta, &b_piEta);
   fChain->SetBranchAddress("piY", &piY, &b_piY);
   fChain->SetBranchAddress("piPhi", &piPhi, &b_piPhi);
   fChain->SetBranchAddress("piDca", &piDca, &b_piDca);
   fChain->SetBranchAddress("piRM", &piRM, &b_piRM);
   fChain->SetBranchAddress("rPtpi", &rPtpi, &b_rPtpi);
   fChain->SetBranchAddress("piREta", &piREta, &b_piREta);
   fChain->SetBranchAddress("piRY", &piRY, &b_piRY);
   fChain->SetBranchAddress("piRPhi", &piRPhi, &b_piRPhi);
   fChain->SetBranchAddress("piRV00x", &piRV00x, &b_piRV00x);
   fChain->SetBranchAddress("piRV00y", &piRV00y, &b_piRV00y);
   fChain->SetBranchAddress("piRV00z", &piRV00z, &b_piRV00z);
   fChain->SetBranchAddress("piRDca", &piRDca, &b_piRDca);
   fChain->SetBranchAddress("piRSDca", &piRSDca, &b_piRSDca);
   fChain->SetBranchAddress("piRDcaXY", &piRDcaXY, &b_piRDcaXY);
   fChain->SetBranchAddress("piRDcaZ", &piRDcaZ, &b_piRDcaZ);
   fChain->SetBranchAddress("piEtaIdx", &piEtaIdx, &b_piEtaIdx);
   fChain->SetBranchAddress("piPtIdx", &piPtIdx, &b_piPtIdx);
   fChain->SetBranchAddress("piTpc", &piTpc, &b_piTpc);
   fChain->SetBranchAddress("pM", &pM, &b_pM);
   fChain->SetBranchAddress("pPt", &pPt, &b_pPt);
   fChain->SetBranchAddress("pEta", &pEta, &b_pEta);
   fChain->SetBranchAddress("pY", &pY, &b_pY);
   fChain->SetBranchAddress("pPhi", &pPhi, &b_pPhi);
   fChain->SetBranchAddress("pDca", &pDca, &b_pDca);
   fChain->SetBranchAddress("pRM", &pRM, &b_pRM);
   fChain->SetBranchAddress("rPtk2", &rPtk2, &b_rPtk2);
   fChain->SetBranchAddress("pREta", &pREta, &b_pREta);
   fChain->SetBranchAddress("pRY", &pRY, &b_pRY);
   fChain->SetBranchAddress("pRPhi", &pRPhi, &b_pRPhi);
   fChain->SetBranchAddress("pRV00x", &pRV00x, &b_pRV00x);
   fChain->SetBranchAddress("pRV00y", &pRV00y, &b_pRV00y);
   fChain->SetBranchAddress("pRV00z", &pRV00z, &b_pRV00z);
   fChain->SetBranchAddress("k2RDca", &k2RDca, &b_k2RDca);
   fChain->SetBranchAddress("pRSDca", &pRSDca, &b_pRSDca);
   fChain->SetBranchAddress("pRDcaXY", &pRDcaXY, &b_pRDcaXY);
   fChain->SetBranchAddress("pRDcaZ", &pRDcaZ, &b_pRDcaZ);
   fChain->SetBranchAddress("pEtaIdx", &pEtaIdx, &b_pEtaIdx);
   fChain->SetBranchAddress("pPtIdx", &pPtIdx, &b_pPtIdx);
   fChain->SetBranchAddress("pTpc", &pTpc, &b_pTpc);
   fChain->SetBranchAddress("kHft", &kHft, &b_kHft);
   fChain->SetBranchAddress("piHft", &piHft, &b_piHft);
   fChain->SetBranchAddress("pHft", &pHft, &b_pHft);
   fChain->SetBranchAddress("flag", &flag, &b_flag);
//   fChain->SetBranchAddress("mva_BDT", &mva_BDT, &b_mBdt    );
 //  fChain->SetBranchAddress("TpcWeight", &TpcWeight, &b_TpcWeight);
}

Bool_t EffSelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef EffSelector_cxx
