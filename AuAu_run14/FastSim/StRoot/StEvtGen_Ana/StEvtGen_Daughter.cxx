
#define StEvtGen_Daughter_cxx
#include "StEvtGen_Daughter.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

StEvtGen_Daughter::StEvtGen_Daughter()
{

}

StEvtGen_Daughter::~StEvtGen_Daughter()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t StEvtGen_Daughter::GetEntries()
{
  if(fChain) return fChain->GetEntriesFast();
  return 0;

}
Int_t StEvtGen_Daughter::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
// Long64_t StEvtGen_Daughter::LoadTree(Long64_t entry)
// {
// // Set the environment to read one entry
//    if (!fChain) return -5;
//    Long64_t centry = fChain->LoadTree(entry);
//    if (centry < 0) return centry;
//    if (fChain->GetTreeNumber() != fCurrent) {
//       fCurrent = fChain->GetTreeNumber();
//       Notify();
//    }
//    return centry;
// }

void StEvtGen_Daughter::Init(TTree *tree)
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

   fChain->SetBranchAddress("Ndaughter", &Ndaughter, &b_Ndaughter);
   fChain->SetBranchAddress("mpdg", mpdg, &b_mpdg);
   fChain->SetBranchAddress("mPx", mPx, &b_mPx);
   fChain->SetBranchAddress("mPy", mPy, &b_mPy);
   fChain->SetBranchAddress("mPz", mPz, &b_mPz);
   fChain->SetBranchAddress("mE", mE, &b_mE);
   fChain->SetBranchAddress("dpdg", dpdg, &b_dpdg);
   fChain->SetBranchAddress("dParent_pdg", dParent_pdg, &b_dParent_pdg);
   fChain->SetBranchAddress("dPx", dPx, &b_dPx);
   fChain->SetBranchAddress("dPy", dPy, &b_dPy);
   fChain->SetBranchAddress("dPz", dPz, &b_dPz);
   fChain->SetBranchAddress("dRPx", dRPx, &b_dRPx);
   fChain->SetBranchAddress("dRPy", dRPy, &b_dRPy);
   fChain->SetBranchAddress("dRPz", dRPz, &b_dRPz);
   fChain->SetBranchAddress("dE", dE, &b_dE);
   fChain->SetBranchAddress("dvx", dvx, &b_dvx);
   fChain->SetBranchAddress("dvy", dvy, &b_dvy);
   fChain->SetBranchAddress("dvz", dvz, &b_dvz);
   fChain->SetBranchAddress("dct", dct, &b_dct);
   fChain->SetBranchAddress("d3Ddca", d3Ddca, &b_d3Ddca);
   fChain->SetBranchAddress("ddcaXY", ddcaXY, &b_ddcaXY);
   fChain->SetBranchAddress("ddcaZ", ddcaZ, &b_ddcaZ);
   fChain->SetBranchAddress("d3DRdca", d3DRdca, &b_d3DRdca);
   fChain->SetBranchAddress("dRdcaXY", dRdcaXY, &b_dRdcaXY);
   fChain->SetBranchAddress("dRdcaZ", dRdcaZ, &b_dRdcaZ);
   fChain->SetBranchAddress("Ncent", Ncent, &b_Ncent);


}


