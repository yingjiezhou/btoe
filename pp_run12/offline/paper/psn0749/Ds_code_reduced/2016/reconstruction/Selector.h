//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov  6 02:23:13 2017 by ROOT version 5.34/30
// from TTree LcBg/SixCutVal
// found on file: BDTresponse_Lc_36_1020.root
//////////////////////////////////////////////////////////

#ifndef Selector_h
#define Selector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "THnSparse.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Selector : public TSelector {
    public :
        TTree          *fChain;   //!pointer to the analyzed TTree or TChain
        UInt_t         fNumberOfEvents;
        UInt_t         decayCh;
        TH3D           *h3bkg_010_Ds;
        TH3D           *h3bkg_1040_Ds;
        TH3D           *h3bkg_4080_Ds;
        TH3D           *h3RS_010_Ds;
        TH3D           *h3RS_1040_Ds;
        TH3D           *h3RS_4080_Ds;
        TH3D           *h3bkg_010_Lc[165];
        TH3D           *h3sg_010_Lc[165];
        TH3D           *h3bkg_1040_Lc[165];
        TH3D           *h3sg_1040_Lc[165];
        TH3D           *h3bkg_4080_Lc[165];
        TH3D           *h3sg_4080_Lc[165];
        TH1F           *response_Ds1040_Scan[4];
        char buf[1024];
         TH1F           *response_010_Scan;   
         TH1F           *response_1040_Scan;   
         TH1F           *response_4080_Scan;   
        THnSparseD     *hDsCentPtEtaMDphi;
        THnSparseD     *hDsCentPtEtaMDphiLikeSign;
        //  float  GetSignificance( const float sig_counts, const float bkg_counts);

        // Declaration of leaf types
Float_t         PhiMass;
   Float_t         Eta;
   Float_t         Phi;
   Float_t         decayLength;
   Float_t         cosTheta;
   Float_t         dcaDaughters;
   Float_t         k1RDca;
   Float_t         piRDca;
   Float_t         k2RDca;
   Float_t         RDca12;
   Float_t         rM;
   Float_t         dcaLcToPv;
   Float_t           cent;
   Float_t         rPt;
   Float_t         massDiff;
   Float_t         rPt_Phi;
   Float_t         rPtpi;
   Float_t         rPt12;
  Float_t           flag;
  Float_t            DsCharge;
   Float_t         reweight;
   Float_t         mva_BDT;

// List of branches
        
 TBranch        *b_PhiMass;   //!
   TBranch        *b_Eta;   //!
   TBranch        *b_Phi;   //!
   TBranch        *b_decayLength;   //!
   TBranch        *b_cosTheta;   //!
   TBranch        *b_dcaDaughters;   //!
   TBranch        *b_k1RDca;   //!
   TBranch        *b_piRDca;   //!
   TBranch        *b_k2RDca;   //!
   TBranch        *b_RDca12;   //!
   TBranch        *b_rM;   //!
   TBranch        *b_dcaLcToPv;   //!
   TBranch        *b_cent;   //!
   TBranch        *b_rPt;   //!
   TBranch        *b_massDiff;   //!
   TBranch        *b_rPt_Phi;   //!
   TBranch        *b_rPtpi;   //!
   TBranch        *b_rPt12;   //!
   TBranch        *b_flag;   //!
   TBranch        *b_DsCharge;   //!
   TBranch        *b_reweight;   //!
   TBranch        *b_mBdt    ;   //!

Selector(TTree * /*tree*/ =0) : fChain(0)/* h3bkg_Lc(0), h3sg_Lc(0)*/ { }
        virtual ~Selector() { }
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
   ClassDef(Selector,0);
};

#endif

#ifdef Selector_cxx
void Selector::Init(TTree *tree)
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
   
 fChain->SetBranchAddress("PhiMass", &PhiMass, &b_PhiMass);
   fChain->SetBranchAddress("Eta", &Eta, &b_Eta);
   fChain->SetBranchAddress("Phi", &Phi, &b_Phi);
   fChain->SetBranchAddress("decayLength", &decayLength, &b_decayLength);
   fChain->SetBranchAddress("cosTheta", &cosTheta, &b_cosTheta);
   fChain->SetBranchAddress("dcaDaughters", &dcaDaughters, &b_dcaDaughters);
   fChain->SetBranchAddress("k1RDca", &k1RDca, &b_k1RDca);
   fChain->SetBranchAddress("piRDca", &piRDca, &b_piRDca);
   fChain->SetBranchAddress("k2RDca", &k2RDca, &b_k2RDca);
   fChain->SetBranchAddress("RDca12", &RDca12, &b_RDca12);
   fChain->SetBranchAddress("rM", &rM, &b_rM);
   fChain->SetBranchAddress("dcaLcToPv", &dcaLcToPv, &b_dcaLcToPv);
   fChain->SetBranchAddress("cent", &cent, &b_cent);
   fChain->SetBranchAddress("rPt", &rPt, &b_rPt);
   fChain->SetBranchAddress("massDiff", &massDiff, &b_massDiff);
   fChain->SetBranchAddress("rPt_Phi", &rPt_Phi, &b_rPt_Phi);
   fChain->SetBranchAddress("rPtpi", &rPtpi, &b_rPtpi);
   fChain->SetBranchAddress("rPt12", &rPt12, &b_rPt12);
   fChain->SetBranchAddress("flag", &flag, &b_flag);
   fChain->SetBranchAddress("DsCharge", &DsCharge, &b_DsCharge);
   fChain->SetBranchAddress("reweight", &reweight, &b_reweight);
   fChain->SetBranchAddress("mva_BDT", &mva_BDT, &b_mBdt    );

}

Bool_t Selector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_cxx
