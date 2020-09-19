#include "TFile.h"
#include <fstream>
#include <iostream>
#include <TChain.h>
#include "TLeaf.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TMath.h"
#include "TProfile.h"
#include "TObjArray.h"
#include "TNtuple.h"
#include "TVector2.h"
#include "anaConst.h"
#include "TString.h"


TH1D *hept;
TH1D *hcept;
TH1D *hbept;
TH1D *hbcept;

const float EtaCut = 0.7;
const float yCut = 0.5;

void readTreeESec(TString filelist="crossSectionE.list",TString outFile="crossSectionE.root")
{
  TFile fout(outFile,"RECREATE");
  TH1F::SetDefaultSumw2();
  TH1D::SetDefaultSumw2();
  
  hept = new TH1D("hept", "hept", 2000., 0., 20.);
  hcept = new TH1D("hcept", "hcept", 2000., 0., 20.);
  hbept = new TH1D("hbept", "hbept", 2000., 0., 20.);
  hbcept = new TH1D("hbcept", "hbcept", 2000., 0., 20.);
  
  //=====================================
  TChain* chain = new TChain("tree");
  int nfile = 0;
  char filename[1000];
  ifstream fstream(filelist.Data());
  int ifile = 0;
  while (fstream >> filename)
  {
    nfile+= chain->Add(filename);
    std::cout << "Got File: " << filename << std::endl;
  }
  
  std::cout <<"Added "<<nfile<<" files"<<std::endl;
  std::cout<<"# entries in chain: "<<chain->GetEntries()<<std::endl;
  if (chain == 0) return;
  
  
  Long64_t nentries = chain->GetEntriesFast();
  int x = 0; int n = nentries; int w = 25;
  
  for(int i = 0; i < nentries; i++){
    Long64_t ientry = chain->LoadTree(i);
    if (ientry < 0) break;
    TBranch *b_destep = chain->GetBranch("hf2eDecay");
    TLeaf* leaf_orig_id            = b_destep->GetLeaf("orig_id");
    TLeaf* leaf_orig_status           = b_destep->GetLeaf("orig_status");
    TLeaf* leaf_hf_id              = b_destep->GetLeaf("hf_id");
    TLeaf* leaf_hf_status              = b_destep->GetLeaf("hf_status");
    TLeaf* leaf_hf_pt              = b_destep->GetLeaf("hf_pt");
    TLeaf* leaf_hf_y                = b_destep->GetLeaf("hf_y");
    
    TLeaf* leaf_e_y               = b_destep->GetLeaf("e_y");
    TLeaf* leaf_e_eta             = b_destep->GetLeaf("e_eta");
    TLeaf* leaf_e_pt                = b_destep->GetLeaf("e_pt");
    
    TLeaf* leaf_weight                = b_destep->GetLeaf("weight");
    TLeaf* leaf_sigmaGen                = b_destep->GetLeaf("sigmaGen");
    
    x = i+1;
    // Process Completion bar
    if ( (x != n) && (x % (n/100) == 0) )
    {
      float ratio  =  (float)x/(float)n;
      int   c      =  ratio * w;
      
      if(ratio < 1){
        std::cout << (int)(ratio*100) << "% [";
        for (int x=0; x<c; x++) std::cout << "=";
        for (int x=c; x<w; x++) std::cout << " ";
        std::cout << "]\r" << std::flush ;
      }
    }
    
    chain->GetEntry(i);
    
    auto weight = (Float_t)leaf_weight->GetValue(0);
    auto sigmaGen = (Float_t)leaf_sigmaGen->GetValue(0);
    
    //    cout<<weight<<"  -  "<<sigmaGen<<" - "<<sigmaGen/5000000.<<endl;
    auto orig_id = (Float_t)leaf_orig_id->GetValue(0);
    auto orig_status = (Float_t)leaf_orig_status->GetValue(0);
    //    auto hf_id = (Float_t)leaf_hf_id->GetValue(0);
    auto hf_status = (Float_t)leaf_hf_status->GetValue(0);
    auto hf_id = (Float_t)leaf_hf_id->GetValue(0);
    auto hf_pt = (Float_t)leaf_hf_pt->GetValue(0);
    auto hf_y = (Float_t)leaf_hf_y->GetValue(0);
    
    auto e_y = (Float_t)leaf_e_y->GetValue(0);
    auto e_eta = (Float_t)leaf_e_eta->GetValue(0);
    auto e_pt = (Float_t)leaf_e_pt->GetValue(0);
    
    
    hf_id = TMath::Abs(hf_id);
    orig_id = TMath::Abs(orig_id);
    //    if(hf_y > yCut || hf_y < -yCut) continue;
    if(orig_id == 0) continue; //If no origin or more than 1 than id == 0
    if(orig_status == -1 || orig_status == -2) continue;
    if(e_y < -yCut && e_y > yCut) continue;
    int flavor = static_cast<int>(hf_id/pow(10.,static_cast<int>(log10(hf_id))));
    if(flavor == 4){
      int gflavor = static_cast<int>(orig_id/pow(10.,static_cast<int>(log10(orig_id))));
      if(gflavor == 5){
        hbcept->Fill(e_pt, weight);
        hbept->Fill(e_pt, weight);
      }
      else hcept->Fill(e_pt, weight);
    }
    else hbept->Fill(e_pt, weight);
    
    hept->Fill(e_pt, weight); // total b+c
  }
  std::cout << "100% [";
  for (int x=0; x<w; x++) std::cout << "=";
  std::cout << "]" << std::endl;
  
  fout.Write();
  fout.Close();
  delete chain;
}
