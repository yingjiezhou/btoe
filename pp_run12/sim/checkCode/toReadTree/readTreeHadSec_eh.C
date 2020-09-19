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

const float EtaCut = 0.7;

void readTreeHadronSec(TString filelist="Trees.list",TString outFile="readTreeOutSubmitTEST.root")
{
  TFile fout(outFile,"RECREATE");
  TH1F::SetDefaultSumw2();
  TH1D::SetDefaultSumw2();

  auto heptN = new TH1D("heptN", "", 200., 0., 20.);
  auto hceptN = new TH1D("hceptN", "", 200., 0., 20.);
  auto hbeptN = new TH1D("hbeptN", "", 200., 0., 20.);
  
  auto hLceN = new TH1D("hLceN", "", 200., 0., 20.);
  auto hD0eN = new TH1D("hD0eN", "", 200., 0., 20.);
  auto hReseN = new TH1D("hReseN", "", 200., 0., 20.);
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
  
  
  Int_t  numberofcElectrons, numberofbElectrons, numberofbcElectrons;
  Int_t numberofcquark,numberofbquark;
  Float_t weight;
  Float_t electron_pt, electron_eta;
  
  Long64_t nentries = chain->GetEntriesFast();
  int x = 0; int n = nentries; int w = 25;

  for(int i = 0; i < nentries; i++){
    Long64_t ientry = chain->LoadTree(i);
    if (ientry < 0) break;
    TBranch *b_destep = chain->GetBranch("hf2eDecay");
    TLeaf* leaf_ce_pt               = b_destep->GetLeaf("ce_pt");
    TLeaf* leaf_be_pt               = b_destep->GetLeaf("be_pt");
    TLeaf* leaf_bce_pt              = b_destep->GetLeaf("bce_pt");
    TLeaf* lead_weight              = b_destep->GetLeaf("weight");
    
    TLeaf* leaf_be_eta              = b_destep->GetLeaf("be_eta");
    TLeaf* leaf_ce_eta              = b_destep->GetLeaf("ce_eta");
    TLeaf* leaf_bce_eta              = b_destep->GetLeaf("bce_eta");
    
    auto lead_ceMom_id = b_destep->GetLeaf("ceMom_id");
    auto lead_beMom_id = b_destep->GetLeaf("beMom_id");
    auto lead_bceMom_id = b_destep->GetLeaf("bceMom_id");

    TLeaf* leaf_numberofcElectrons  = b_destep->GetLeaf("numberofcElectrons");
    TLeaf* leaf_numberofbElectrons  = b_destep->GetLeaf("numberofbElectrons");
    TLeaf* leaf_numberofbcElectrons = b_destep->GetLeaf("numberofbcElectrons");
    
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
    weight = (Float_t)lead_weight->GetValue(0);
    numberofcElectrons = leaf_numberofcElectrons->GetValue(0);
    numberofbElectrons = leaf_numberofbElectrons->GetValue(0);
    numberofbcElectrons = leaf_numberofbcElectrons->GetValue(0);
    
    for(int trki = 0; trki < numberofcElectrons; trki++){
      electron_eta     = leaf_ce_eta->GetValue(trki);
//      cout<<electron_eta<<endl;
      if(electron_eta > EtaCut || electron_eta < -EtaCut) continue;

      electron_pt      = leaf_ce_pt->GetValue(trki);
      heptN->Fill(electron_pt, weight); // fill NPE pt, get pt spectrum
      hceptN->Fill(electron_pt, weight); // fill NPE pt, get pt spectrum
      
      auto momId = lead_ceMom_id->GetValue(trki);
      if(momId == 421) hD0eN->Fill(electron_pt, weight);
      if(momId == 4122) hLceN->Fill(electron_pt, weight);
      if(!(momId == 421 || momId == 4122)) hReseN->Fill(electron_pt, weight);
    }
    
    for(int trki = 0; trki < numberofbElectrons; trki++){
      electron_eta     = leaf_be_eta->GetValue(trki);
      if(electron_eta > EtaCut || electron_eta < -EtaCut) continue;

      electron_pt      = leaf_be_pt->GetValue(trki);
      heptN->Fill(electron_pt, weight); // fill NPE pt, get pt spectrum
      hbeptN->Fill(electron_pt, weight); // fill NPE pt, get pt spectrum
      hReseN->Fill(electron_pt, weight);
    }
    
    for(int trki = 0; trki < numberofbcElectrons; trki++){
      electron_eta     = leaf_bce_eta->GetValue(trki);
      if(electron_eta > EtaCut || electron_eta < -EtaCut) continue;

      electron_pt      = leaf_bce_pt->GetValue(trki);
      heptN->Fill(electron_pt, weight); // fill NPE pt, get pt spectrum
      hbeptN->Fill(electron_pt, weight); // fill NPE pt, get pt spectrum

      auto momId = lead_bceMom_id->GetValue(trki);
      if(momId == 421) hD0eN->Fill(electron_pt, weight);
      if(momId == 4122) hLceN->Fill(electron_pt, weight);
      if(!(momId == 421 || momId == 4122)) hReseN->Fill(electron_pt, weight);
    }
  }
  
  std::cout << "100% [";
  for (int x=0; x<w; x++) std::cout << "=";
  std::cout << "]" << std::endl;
  
  fout.Write();
  fout.Close();
  delete chain;
}
