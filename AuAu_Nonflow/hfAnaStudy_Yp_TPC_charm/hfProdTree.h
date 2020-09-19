//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 29 21:23:50 2019 by ROOT version 5.34/30
// from TTree hfProdTree/E and hadron tree
// found on file: output/NpeBHcorr_r1pT1_100.root
//////////////////////////////////////////////////////////

#ifndef hfProdTree_h
#define hfProdTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxHadrons = 300;
const Int_t kMaxElectrons = 10;

class hfProdTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           nElec;
   Double_t        pTTrkE[kMaxElectrons];   //[nElec]
   Double_t        etaE[kMaxElectrons];   //[nElec]
   Double_t        phiE[kMaxElectrons];   //[nElec]
   Double_t        idE[kMaxElectrons];   //[nElec]
   Int_t           Hadrons_;
   Int_t           Hadrons_idSave[kMaxHadrons];   //[Hadrons_]
   Int_t           Hadrons_statusSave[kMaxHadrons];   //[Hadrons_]
   Int_t           Hadrons_mother1Save[kMaxHadrons];   //[Hadrons_]
   Int_t           Hadrons_mother2Save[kMaxHadrons];   //[Hadrons_]
   Int_t           Hadrons_daughter1Save[kMaxHadrons];   //[Hadrons_]
   Int_t           Hadrons_daughter2Save[kMaxHadrons];   //[Hadrons_]
   Int_t           Hadrons_colSave[kMaxHadrons];   //[Hadrons_]
   Int_t           Hadrons_acolSave[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_pSave_xx[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_pSave_yy[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_pSave_zz[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_pSave_tt[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_mSave[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_scaleSave[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_polSave[kMaxHadrons];   //[Hadrons_]
   Bool_t          Hadrons_hasVertexSave[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_vProdSave_xx[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_vProdSave_yy[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_vProdSave_zz[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_vProdSave_tt[kMaxHadrons];   //[Hadrons_]
   Double_t        Hadrons_tauSave[kMaxHadrons];   //[Hadrons_]

   // List of branches
   TBranch        *b_nElec;   //!
   TBranch        *b_pTTrkE;   //!
   TBranch        *b_etaE;   //!
   TBranch        *b_phiE;   //!
   TBranch        *b_idE;   //!
   TBranch        *b_Hadrons_;   //!
   TBranch        *b_Hadrons_idSave;   //!
   TBranch        *b_Hadrons_statusSave;   //!
   TBranch        *b_Hadrons_mother1Save;   //!
   TBranch        *b_Hadrons_mother2Save;   //!
   TBranch        *b_Hadrons_daughter1Save;   //!
   TBranch        *b_Hadrons_daughter2Save;   //!
   TBranch        *b_Hadrons_colSave;   //!
   TBranch        *b_Hadrons_acolSave;   //!
   TBranch        *b_Hadrons_pSave_xx;   //!
   TBranch        *b_Hadrons_pSave_yy;   //!
   TBranch        *b_Hadrons_pSave_zz;   //!
   TBranch        *b_Hadrons_pSave_tt;   //!
   TBranch        *b_Hadrons_mSave;   //!
   TBranch        *b_Hadrons_scaleSave;   //!
   TBranch        *b_Hadrons_polSave;   //!
   TBranch        *b_Hadrons_hasVertexSave;   //!
   TBranch        *b_Hadrons_vProdSave_xx;   //!
   TBranch        *b_Hadrons_vProdSave_yy;   //!
   TBranch        *b_Hadrons_vProdSave_zz;   //!
   TBranch        *b_Hadrons_vProdSave_tt;   //!
   TBranch        *b_Hadrons_tauSave;   //!

   hfProdTree(TTree *tree=0);
   virtual ~hfProdTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

//#ifdef hfProdTree_cxx
hfProdTree::hfProdTree(TTree *tree) //: fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output/NpeBHcorr_r1pT1_100.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("output/NpeBHcorr_r1pT1_100.root");
      }
      f->GetObject("hfProdTree",tree);

   }
   Init(tree);
}

hfProdTree::~hfProdTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t hfProdTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t hfProdTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void hfProdTree::Init(TTree *tree)
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
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nElec", &nElec, &b_nElec);
   fChain->SetBranchAddress("pTTrkE", pTTrkE, &b_pTTrkE);
   fChain->SetBranchAddress("etaE", etaE, &b_etaE);
   fChain->SetBranchAddress("phiE", phiE, &b_phiE);
   fChain->SetBranchAddress("idE", idE, &b_idE);
   fChain->SetBranchAddress("Hadrons", &Hadrons_, &b_Hadrons_);
   fChain->SetBranchAddress("Hadrons.idSave", Hadrons_idSave, &b_Hadrons_idSave);
   fChain->SetBranchAddress("Hadrons.statusSave", Hadrons_statusSave, &b_Hadrons_statusSave);
   fChain->SetBranchAddress("Hadrons.mother1Save", Hadrons_mother1Save, &b_Hadrons_mother1Save);
   fChain->SetBranchAddress("Hadrons.mother2Save", Hadrons_mother2Save, &b_Hadrons_mother2Save);
   fChain->SetBranchAddress("Hadrons.daughter1Save", Hadrons_daughter1Save, &b_Hadrons_daughter1Save);
   fChain->SetBranchAddress("Hadrons.daughter2Save", Hadrons_daughter2Save, &b_Hadrons_daughter2Save);
   fChain->SetBranchAddress("Hadrons.colSave", Hadrons_colSave, &b_Hadrons_colSave);
   fChain->SetBranchAddress("Hadrons.acolSave", Hadrons_acolSave, &b_Hadrons_acolSave);
   fChain->SetBranchAddress("Hadrons.pSave.xx", Hadrons_pSave_xx, &b_Hadrons_pSave_xx);
   fChain->SetBranchAddress("Hadrons.pSave.yy", Hadrons_pSave_yy, &b_Hadrons_pSave_yy);
   fChain->SetBranchAddress("Hadrons.pSave.zz", Hadrons_pSave_zz, &b_Hadrons_pSave_zz);
   fChain->SetBranchAddress("Hadrons.pSave.tt", Hadrons_pSave_tt, &b_Hadrons_pSave_tt);
   fChain->SetBranchAddress("Hadrons.mSave", Hadrons_mSave, &b_Hadrons_mSave);
   fChain->SetBranchAddress("Hadrons.scaleSave", Hadrons_scaleSave, &b_Hadrons_scaleSave);
   fChain->SetBranchAddress("Hadrons.polSave", Hadrons_polSave, &b_Hadrons_polSave);
   fChain->SetBranchAddress("Hadrons.hasVertexSave", Hadrons_hasVertexSave, &b_Hadrons_hasVertexSave);
   fChain->SetBranchAddress("Hadrons.vProdSave.xx", Hadrons_vProdSave_xx, &b_Hadrons_vProdSave_xx);
   fChain->SetBranchAddress("Hadrons.vProdSave.yy", Hadrons_vProdSave_yy, &b_Hadrons_vProdSave_yy);
   fChain->SetBranchAddress("Hadrons.vProdSave.zz", Hadrons_vProdSave_zz, &b_Hadrons_vProdSave_zz);
   fChain->SetBranchAddress("Hadrons.vProdSave.tt", Hadrons_vProdSave_tt, &b_Hadrons_vProdSave_tt);
   fChain->SetBranchAddress("Hadrons.tauSave", Hadrons_tauSave, &b_Hadrons_tauSave);
   Notify();
}

Bool_t hfProdTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void hfProdTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t hfProdTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
void hfProdTree::Loop()
{}
//#endif // #ifdef hfProdTree_cxx
