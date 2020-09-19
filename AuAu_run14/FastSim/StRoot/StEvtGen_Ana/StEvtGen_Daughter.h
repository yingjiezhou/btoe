  //////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 15 02:48:04 2015 by ROOT version 5.34/09
// from TTree Tree_1/Tree_1
// found on file: EvtGen_DMeson_production.root
//////////////////////////////////////////////////////////

#ifndef StEvtGen_Daughter_h
#define StEvtGen_Daughter_h

//#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class StEvtGen_Daughter {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Ndaughter;
   Int_t           mpdg[50];   //[Ndaughter]
   Double_t        mPx[50];   //[Ndaughter]
   Double_t        mPy[50];   //[Ndaughter]
   Double_t        mPz[50];   //[Ndaughter]
   Double_t        mE[50];   //[Ndaughter]
   Int_t           dpdg[50];   //[Ndaughter]
   Int_t           dParent_pdg[50];   //[Ndaughter]
   Double_t        dPx[50];   //[Ndaughter]
   Double_t        dPy[50];   //[Ndaughter]
   Double_t        dPz[50];   //[Ndaughter]
   Double_t        dRPx[50];   //[Ndaughter]
   Double_t        dRPy[50];   //[Ndaughter]
   Double_t        dRPz[50];   //[Ndaughter]
  
   Double_t        dE[50];   //[Ndaughter]
   Double_t        dvx[50];   //[Ndaughter]
   Double_t        dvy[50];   //[Ndaughter]
   Double_t        dvz[50];   //[Ndaughter]
   Double_t        dct[50];   //[Ndaughter]

   Double_t        d3Ddca[50];   //[Ndaughter]
   Double_t        ddcaXY[50];   //[Ndaughter]
   Double_t        ddcaZ[50];   //[Ndaughter]
   Double_t        d3DRdca[50];   //[Ndaughter]
   Double_t        dRdcaXY[50];   //[Ndaughter]
   Double_t        dRdcaZ[50];   //[Ndaughter]
   Int_t         Ncent[50];   //[Ndaughter]

   // List of branches
   TBranch        *b_Ndaughter;   //!
   TBranch        *b_mpdg;   //!
   TBranch        *b_mPx;   //!
   TBranch        *b_mPy;   //!
   TBranch        *b_mPz;   //!
   TBranch        *b_dRPx;   //!
   TBranch        *b_dRPy;   //!
   TBranch        *b_dRPz;   //!

   TBranch        *b_mE;   //!
   TBranch        *b_dpdg;   //!
   TBranch        *b_dParent_pdg;   //!
   TBranch        *b_dPx;   //!
   TBranch        *b_dPy;   //!
   TBranch        *b_dPz;   //!
   TBranch        *b_dE;   //!
   TBranch        *b_dvx;   //!
   TBranch        *b_dvy;   //!
   TBranch        *b_dvz;   //!
   TBranch        *b_dct;   //!
   TBranch        *b_d3Ddca;   //!
   TBranch        *b_ddcaXY;   //!
   TBranch        *b_ddcaZ;   //!
   TBranch        *b_d3DRdca;   //!
   TBranch        *b_dRdcaXY;   //!
   TBranch        *b_dRdcaZ;   //!
   TBranch        *b_Ncent;   //!

   StEvtGen_Daughter();
   virtual ~StEvtGen_Daughter();
   // virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Int_t    GetEntries();
   // virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   // virtual void     Loop();
   // virtual Bool_t   Notify();
   // virtual void     Show(Long64_t entry = -1);


   ClassDef(StEvtGen_Daughter,1)
};

#endif
