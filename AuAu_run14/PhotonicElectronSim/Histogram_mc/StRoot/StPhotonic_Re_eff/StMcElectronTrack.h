//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jul  5 20:21:06 2015 by ROOT version 5.34/09
// from TTree tracksMC/tracks
// found on file: /star/data01/pwg/xiao00/Dca_DCA_simulation/AnaPico/production/Ana.root
//////////////////////////////////////////////////////////

#ifndef ReadAna_h
#define ReadAna_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class StMcElectronTrack {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   Float_t         geantId;
   Float_t         p;
   Float_t         pt;
   Float_t         svx;
   Float_t         svy;
   Float_t         svz;
   Float_t         pgeantId;
   Float_t         pp;
   Float_t         ppt;
   Float_t         phi;
   Float_t         pphi;
   Float_t         y;
   Float_t         py;
   Float_t         eta;
   Float_t         peta;
   Float_t         label;
   Float_t         plabel;
   Float_t         gplabel;
   Float_t         rp;
   Float_t         rpt;
   Float_t         reta;
   Float_t         rphi;
   Float_t         nfit;
   Float_t         ncom;
   Float_t         nmax;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Float_t         dca;
   Float_t         dcaxy;
   Float_t         dcaz;
   Float_t         isHFT;
   Float_t         mcHFT;
   Float_t         trueHFT;
   Float_t         chi2;
   Float_t         nDedxPts;
   Float_t         dedx;
   Float_t         dedx_2;
   Float_t         nSigPi;
   Float_t         nSigK;
   Float_t         nSigP;
   Float_t         nSigE;
   Float_t         bemcId;
   Float_t         btowAdc0;
   Float_t         btowE0;
   Float_t         btowE;
   Float_t         bemcDistZ;
   Float_t         bemcDistPhi;
   Float_t         bsmdNEta;
   Float_t         bsmdNPhi;
   Float_t         btowId;
   Float_t         pr_rp;
   Float_t         pr_rpT;
   Float_t         stpcx;
   Float_t         stpcy;
   Float_t         stpcz;
   Float_t         gpgeantId;
   Float_t         gppt;
   // List of branches
   TBranch        *b_geantId;   //!
   TBranch        *b_p;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_svx;   //!
   TBranch        *b_svy;   //!
   TBranch        *b_svz;   //!
   TBranch        *b_pgeantId;   //!
   TBranch        *b_pp;   //!
   TBranch        *b_ppt;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_pphi;   //!
   TBranch        *b_y;   //!
   TBranch        *b_py;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_peta;   //!
   TBranch        *b_label;   //!
   TBranch        *b_plabel;   //!
   TBranch        *b_gplabel;   //!
   TBranch        *b_rp;   //!
   TBranch        *b_rpt;   //!
   TBranch        *b_reta;   //!
   TBranch        *b_rphi;   //!
   TBranch        *b_nfit;   //!
   TBranch        *b_ncom;   //!
   TBranch        *b_nmax;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_dca;   //!
   TBranch        *b_dcaxy;   //!
   TBranch        *b_dcaz;   //!
   TBranch        *b_isHFT;   //!
   TBranch        *b_mcHFT;   //!
   TBranch        *b_trueHFT;   //!

   TBranch        *b_chi2;   //!
   TBranch        *b_nDedxPts;   //!
   TBranch        *b_dedx;   //!
   TBranch        *b_dedx_2;   //!
   TBranch        *b_nSigPi;   //!
   TBranch        *b_nSigK;   //!
   TBranch        *b_nSigP;   //!
   TBranch        *b_nSigE;   //!
   TBranch        *b_bemcId;   //!
   TBranch        *b_btowAdc0;   //!
   TBranch        *b_btowE0;   //!
   TBranch        *b_btowE;   //!
   TBranch        *b_bemcDistZ;   //!
   TBranch        *b_bemcDistPhi;   //!
   TBranch        *b_bsmdNEta;   //!
   TBranch        *b_bsmdNPhi;   //!
   TBranch        *b_btowId;   //!
   TBranch        *b_pr_rp;   //!
   TBranch        *b_pr_rpT;   //!
   TBranch        *b_stpcx;   //!
   TBranch        *b_stpcy;   //!
   TBranch        *b_stpcz;   //!
   TBranch        *b_gpgeantId;   //!
   TBranch        *b_gppt;   //!
   StMcElectronTrack();
   //  StMcElectronTrack(TTree *tree=0);
   virtual ~StMcElectronTrack();
  
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Int_t    GetEntries(); 
   virtual void     Init(TTree *tree);
   ClassDef(StMcElectronTrack,1);   
  
};

#endif
