//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 21 12:21:32 2015 by ROOT version 5.34/09
// from TTree nt_pair/pairs
// found on file: /star/data01/pwg/zaochen/forxiaozhi/AnaPico/production/hist_Gamma.root
//////////////////////////////////////////////////////////

#ifndef StPair_h
#define StPair_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class StPair {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
   Float_t         p1geantId;
   Float_t         p1p;
   Float_t         p1pt;
   Float_t         p1svx;
   Float_t         p1svy;
   Float_t         p1svz;
   Float_t         p1pgeantId;
   Float_t         p1pp;
   Float_t         p1ppt;
   Float_t         p1eta;
   Float_t         p1peta;
   Float_t         p1label;
   Float_t         p1rp;
   Float_t         p1rpt;
   Float_t         p1reta;
   Float_t         p1rphi;
   Float_t         p1ndedx;
   Float_t         p1nfit;
   Float_t         p1ncom;
   Float_t         p1nmax;
   Float_t         p1dca;
   Float_t         p1dcaxy;
   Float_t         p1dcaz;
   Float_t         t1isHFT;
   Float_t         t1mcHFT;
   Float_t         t1trueHFT;
   Float_t         p1chi2;
   Float_t         p2geantId;
   Float_t         p2p;
   Float_t         p2pt;
   Float_t         p2svx;
   Float_t         p2svy;
   Float_t         p2svz;
   Float_t         p2pgeantId;
   Float_t         p2pp;
   Float_t         p2ppt;
   Float_t         p2eta;
   Float_t         p2peta;
   Float_t         p2label;
   Float_t         p2rp;
   Float_t         p2rpt;
   Float_t         p2reta;
   Float_t         p2rphi;
   Float_t         p2nfit;
   Float_t         p2ncom;
   Float_t         p2nmax;
   Float_t         p2dca;
   Float_t         p2dcaxy;
   Float_t         p2dcaz;
   Float_t         t2isHFT;
   Float_t         t2mcHFT;
   Float_t         t2trueHFT;
   Float_t         p2chi2;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Float_t         massDCA;
   Float_t         mcMassPair;
   Float_t         pairDCA;
   Float_t         pairPT;
   Float_t         theta;
   Float_t         xpair;
   Float_t         ypair;
   Float_t         zpair;
   Float_t         mult;
   Float_t         dist;
   Float_t         p1bemcId;
   Float_t         p1btowAdc0;
   Float_t         p1btowE0;
   Float_t         p1btowE;
   Float_t         p1bemcDistZ;
   Float_t         p1bemcDistPhi;
   Float_t         p1bsmdNEta;
   Float_t         p1bsmdNPhi;
   Float_t         p1btowId;
   Float_t         p2bemcId;
   Float_t         p2btowAdc0;
   Float_t         p2btowE0;
   Float_t         p2btowE;
   Float_t         p2bemcDistZ;
   Float_t         p2bemcDistPhi;
   Float_t         p2bsmdNEta;
   Float_t         p2bsmdNPhi;
   Float_t         p2btowId;
   Float_t         p1pr_rp;
   Float_t         p1pr_rpT;
   Float_t         p2pr_rp;
   Float_t         p2pr_rpT;
   Float_t         p1stpcx;
   Float_t         p1stpcy;
   Float_t         p1stpcz;
   Float_t         p1gpgeantId;
   Float_t         p1gppt;
   Float_t         p2gpgeantId;
   Float_t         p2gppt;

   // List of branches
   TBranch        *b_p1geantId;   //!
   TBranch        *b_p1p;   //!
   TBranch        *b_p1pt;   //!
   TBranch        *b_p1svx;   //!
   TBranch        *b_p1svy;   //!
   TBranch        *b_p1svz;   //!
   TBranch        *b_p1pgeantId;   //!
   TBranch        *b_p1pp;   //!
   TBranch        *b_p1ppt;   //!
   TBranch        *b_p1eta;   //!
   TBranch        *b_p1peta;   //!
   TBranch        *b_p1label;   //!
   TBranch        *b_p1rp;   //!
   TBranch        *b_p1rpt;   //!
   TBranch        *b_p1reta;   //!
   TBranch        *b_p1rphi;   //!
   TBranch        *b_p1ndedx;   //!
   TBranch        *b_p1nfit;   //!
   TBranch        *b_p1ncom;   //!
   TBranch        *b_p1nmax;   //!
   TBranch        *b_p1dca;   //!
   TBranch        *b_p1dcaxy;   //!
   TBranch        *b_p1dcaz;   //!
   TBranch        *b_t1isHFT;   //!
   TBranch        *b_t1mcHFT;   //!
   TBranch        *b_t1trueHFT;   //!
   TBranch        *b_p1chi2;   //!
   TBranch        *b_p2geantId;   //!
   TBranch        *b_p2p;   //!
   TBranch        *b_p2pt;   //!
   TBranch        *b_p2svx;   //!
   TBranch        *b_p2svy;   //!
   TBranch        *b_p2svz;   //!
   TBranch        *b_p2pgeantId;   //!
   TBranch        *b_p2pp;   //!
   TBranch        *b_p2ppt;   //!
   TBranch        *b_p2eta;   //!
   TBranch        *b_p2peta;   //!
   TBranch        *b_p2label;   //!
   TBranch        *b_p2rp;   //!
   TBranch        *b_p2rpt;   //!
   TBranch        *b_p2reta;   //!
   TBranch        *b_p2rphi;   //!
   TBranch        *b_p2nfit;   //!
   TBranch        *b_p2ncom;   //!
   TBranch        *b_p2nmax;   //!
   TBranch        *b_p2dca;   //!
   TBranch        *b_p2dcaxy;   //!
   TBranch        *b_p2dcaz;   //!
   TBranch        *b_t2isHFT;   //!
   TBranch        *b_t2mcHFT;   //!
   TBranch        *b_t2trueHFT;   //!
   TBranch        *b_p2chi2;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_massDCA;   //!
   TBranch        *b_mcMassPair;   //!
   TBranch        *b_pairDCA;   //!
   TBranch        *b_pairPT;   //!
   TBranch        *b_theta;   //!
   TBranch        *b_xpair;   //!
   TBranch        *b_ypair;   //!
   TBranch        *b_zpair;   //!
   TBranch        *b_mult;   //!
   TBranch        *b_dist;   //!
   TBranch        *b_p1bemcId;   //!
   TBranch        *b_p1btowAdc0;   //!
   TBranch        *b_p1btowE0;   //!
   TBranch        *b_p1btowE;   //!
   TBranch        *b_p1bemcDistZ;   //!
   TBranch        *b_p1bemcDistPhi;   //!
   TBranch        *b_p1bsmdNEta;   //!
   TBranch        *b_p1bsmdNPhi;   //!
   TBranch        *b_p1btowId;   //!
   TBranch        *b_p2bemcId;   //!
   TBranch        *b_p2btowAdc0;   //!
   TBranch        *b_p2btowE0;   //!
   TBranch        *b_p2btowE;   //!
   TBranch        *b_p2bemcDistZ;   //!
   TBranch        *b_p2bemcDistPhi;   //!
   TBranch        *b_p2bsmdNEta;   //!
   TBranch        *b_p2bsmdNPhi;   //!
   TBranch        *b_p2btowId;   //!
   TBranch        *b_p1pr_rp;   //!
   TBranch        *b_p1pr_rpT;   //!
   TBranch        *b_p2pr_rp;   //!
   TBranch        *b_p2pr_rpT;   //!
   TBranch        *b_p1stpcx;   //!
   TBranch        *b_p1stpcy;   //!
   TBranch        *b_p1stpcz;   //!
   TBranch        *b_p1gpgeantId;   //!
   TBranch        *b_p1gppt;   //!
   TBranch        *b_p2gpgeantId;   //!
   TBranch        *b_p2gppt;   //!

   
  StPair();
  virtual ~StPair();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Int_t    GetEntries();                                     
  virtual void     Init(TTree *tree);
  ClassDef(StPair,1);                                                                             

};

#endif


/* pair::pair(TTree *tree) : fChain(0)  */
/* { */
/*   // if parameter tree is not specified (or zero), connect the file */
/*   // used to generate this class and read the Tree. */
/*   if (tree == 0) { */
/*     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/star/data01/pwg/zaochen/forxiaozhi/AnaPico/production/hist_Gamma.root"); */
/*     if (!f || !f->IsOpen()) { */
/*       f = new TFile("/star/data01/pwg/zaochen/forxiaozhi/AnaPico/production/hist_Gamma.root"); */
/*     } */
/*     f->GetObject("nt_pair",tree); */

/*   } */
/*   Init(tree); */
/* } */

/* pair::~pair() */
/* { */
/*   if (!fChain) return; */
/*   delete fChain->GetCurrentFile(); */
/* } */

/* Int_t pair::GetEntry(Long64_t entry) */
/* { */
/*   // Read contents of entry. */
/*   if (!fChain) return 0; */
/*   return fChain->GetEntry(entry); */
/* } */
/* Long64_t pair::LoadTree(Long64_t entry) */
/* { */
/*   // Set the environment to read one entry */
/*   if (!fChain) return -5; */
/*   Long64_t centry = fChain->LoadTree(entry); */
/*   if (centry < 0) return centry; */
/*   if (fChain->GetTreeNumber() != fCurrent) { */
/*     fCurrent = fChain->GetTreeNumber(); */
/*     Notify(); */
/*   } */
/*   return centry; */
/* } */

/* void pair::Init(TTree *tree) */
/* { */
/*   // The Init() function is called when the selector needs to initialize */
/*   // a new tree or chain. Typically here the branch addresses and branch */
/*   // pointers of the tree will be set. */
/*   // It is normally not necessary to make changes to the generated */
/*   // code, but the routine can be extended by the user if needed. */
/*   // Init() will be called many times when running on PROOF */
/*   // (once per file to be processed). */

/*   // Set branch addresses and branch pointers */
/*   if (!tree) return; */
/*   fChain = tree; */
/*   fCurrent = -1; */
/*   fChain->SetMakeClass(1); */

/*   fChain->SetBranchAddress("t1Geantid", &t1Geantid, &b_t1Geantid); */
/*   fChain->SetBranchAddress("t1parent_Geantid", &t1parent_Geantid, &b_t1parent_Geantid); */
/*   fChain->SetBranchAddress("t1isHFT", &t1isHFT, &b_t1isHFT); */
/*   fChain->SetBranchAddress("t1g_Px", &t1g_Px, &b_t1g_Px); */
/*   fChain->SetBranchAddress("t1g_Py", &t1g_Py, &b_t1g_Py); */
/*   fChain->SetBranchAddress("t1g_Pz", &t1g_Pz, &b_t1g_Pz); */
/*   fChain->SetBranchAddress("t1p_Px", &t1p_Px, &b_t1p_Px); */
/*   fChain->SetBranchAddress("t1p_Py", &t1p_Py, &b_t1p_Py); */
/*   fChain->SetBranchAddress("t1p_Pz", &t1p_Pz, &b_t1p_Pz); */
/*   fChain->SetBranchAddress("t1vtx", &t1vtx, &b_t1vtx); */
/*   fChain->SetBranchAddress("t1vty", &t1vty, &b_t1vty); */
/*   fChain->SetBranchAddress("t1vtz", &t1vtz, &b_t1vtz); */
/*   fChain->SetBranchAddress("t1stx", &t1stx, &b_t1stx); */
/*   fChain->SetBranchAddress("t1sty", &t1sty, &b_t1sty); */
/*   fChain->SetBranchAddress("t1stz", &t1stz, &b_t1stz); */
/*   fChain->SetBranchAddress("t1_eta", &t1_eta, &b_t1_eta); */
/*   fChain->SetBranchAddress("t1nhitfit", &t1nhitfit, &b_t1nhitfit); */
/*   fChain->SetBranchAddress("t1dca", &t1dca, &b_t1dca); */
/*   fChain->SetBranchAddress("t1dcaXY", &t1dcaXY, &b_t1dcaXY); */
/*   fChain->SetBranchAddress("t1dcaZ", &t1dcaZ, &b_t1dcaZ); */
/*   fChain->SetBranchAddress("t2Geantid", &t2Geantid, &b_t2Geantid); */
/*   fChain->SetBranchAddress("t2parent_Geantid", &t2parent_Geantid, &b_t2parent_Geantid); */
/*   fChain->SetBranchAddress("t2isHFT", &t2isHFT, &b_t2isHFT); */
/*   fChain->SetBranchAddress("t2g_Px", &t2g_Px, &b_t2g_Px); */
/*   fChain->SetBranchAddress("t2g_Py", &t2g_Py, &b_t2g_Py); */
/*   fChain->SetBranchAddress("t2g_Pz", &t2g_Pz, &b_t2g_Pz); */
/*   fChain->SetBranchAddress("t2p_Px", &t2p_Px, &b_t2p_Px); */
/*   fChain->SetBranchAddress("t2p_Py", &t2p_Py, &b_t2p_Py); */
/*   fChain->SetBranchAddress("t2p_Pz", &t2p_Pz, &b_t2p_Pz); */
/*   fChain->SetBranchAddress("t2vtx", &t2vtx, &b_t2vtx); */
/*   fChain->SetBranchAddress("t2vty", &t2vty, &b_t2vty); */
/*   fChain->SetBranchAddress("t2vtz", &t2vtz, &b_t2vtz); */
/*   fChain->SetBranchAddress("t2stx", &t2stx, &b_t2stx); */
/*   fChain->SetBranchAddress("t2sty", &t2sty, &b_t2sty); */
/*   fChain->SetBranchAddress("t2stz", &t2stz, &b_t2stz); */
/*   fChain->SetBranchAddress("t2_eta", &t2_eta, &b_t2_eta); */
/*   fChain->SetBranchAddress("t2nhitfit", &t2nhitfit, &b_t2nhitfit); */
/*   fChain->SetBranchAddress("t2dca", &t2dca, &b_t2dca); */
/*   fChain->SetBranchAddress("t2dcaXY", &t2dcaXY, &b_t2dcaXY); */
/*   fChain->SetBranchAddress("t2dcaZ", &t2dcaZ, &b_t2dcaZ); */
/*   fChain->SetBranchAddress("pairDCA", &pairDCA, &b_pairDCA); */
/*   fChain->SetBranchAddress("thetaDCA", &thetaDCA, &b_thetaDCA); */
/*   fChain->SetBranchAddress("massPair", &massPair, &b_massPair); */
/*   fChain->SetBranchAddress("pairPT", &pairPT, &b_pairPT); */
/*   fChain->SetBranchAddress("DCA_x", &DCA_x, &b_DCA_x); */
/*   fChain->SetBranchAddress("DCA_y", &DCA_y, &b_DCA_y); */
/*   fChain->SetBranchAddress("DCA_z", &DCA_z, &b_DCA_z); */
/*   Notify(); */
/* } */

/* Bool_t pair::Notify() */
/* { */
/*   // The Notify() function is called when a new file is opened. This */
/*   // can be either for a new TTree in a TChain or when when a new TTree */
/*   // is started when using PROOF. It is normally not necessary to make changes */
/*   // to the generated code, but the routine can be extended by the */
/*   // user if needed. The return value is currently not used. */

/*   return kTRUE; */
/* } */

/* void pair::Show(Long64_t entry) */
/* { */
/*   // Print contents of entry. */
/*   // If entry is not specified, print current entry */
/*   if (!fChain) return; */
/*   fChain->Show(entry); */
/* } */
/* Int_t pair::Cut(Long64_t entry) */
/* { */
/*   // This function may be called from Loop. */
/*   // returns  1 if entry is accepted. */
/*   // returns -1 otherwise. */
/*   return 1; */
/* } */
/* #endif // #ifdef pair_cxx */
