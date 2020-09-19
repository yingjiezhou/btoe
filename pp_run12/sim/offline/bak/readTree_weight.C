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

TH1D *heptN;
TH1D *hceptN;
TH1D *hbeptN;

const float EtaCut = 0.7;

const char localDir[1000] = "/global/project/projectdirs/star/pwg/starhf/zamiller/minBiasTemplates101015";
const char outDir[1000] = "/global/project/projectdirs/star/pwg/starhf/zamiller/minBiasTemplates101015";
void readTree(TString filelist="/global/project/projectdirs/star/pwg/starhf/zamiller/minBiasTemplates101015/Trees.list",TString outFile="/global/project/projectdirs/star/pwg/starhf/zamiller/minBiasTemplates101015/readTreeOutSubmitTEST.root")
{
  TFile fout(outFile,"RECREATE");
  TH1F::SetDefaultSumw2();
  TH1D::SetDefaultSumw2();
  
  hept = new TH1D("hept", "hept", 200., 0., 20.);
  hcept = new TH1D("hcept", "hcept", 200., 0., 20.);
  hbept = new TH1D("hbept", "hbept", 200., 0., 20.);
  
  heptN = new TH1D("heptN", "heptN", 200., 0., 20.);
  hceptN = new TH1D("hceptN", "hceptN", 200., 0., 20.);
  hbeptN = new TH1D("hbeptN", "hbeptN", 200., 0., 20.);
  
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
  Float_t Sigma_gen;
  Float_t celectron_pt;
  Float_t celectron_eta;
  
  
  Long64_t nentries = chain->GetEntriesFast();
  int n = nentries;
  int n = nentries;
  for(int i = 0; i < nentries; i++){
    Long64_t ientry = chain->LoadTree(i);
    if (ientry < 0) break;
    TBranch *b_destep = chain->GetBranch("hf2eDecay");

    TLeaf* leaf_ce_pt               = b_destep->GetLeaf("ce_pt");
    TLeaf* leaf_be_pt               = b_destep->GetLeaf("be_pt");
    TLeaf* leaf_bce_pt              = b_destep->GetLeaf("bce_pt");
    TLeaf* lead_weight              = b_destep->GetLeaf("weight");
    
    TLeaf* leaf_ce_eta              = b_destep->GetLeaf("ce_eta");
    TLeaf* leaf_be_eta              = b_destep->GetLeaf("be_eta");
    TLeaf* leaf_bce_eta             = b_destep->GetLeaf("bce_eta");

    TLeaf* leaf_numberofcElectrons  = b_destep->GetLeaf("numberofcElectrons");
    TLeaf* leaf_numberofbElectrons  = b_destep->GetLeaf("numberofbElectrons");
    TLeaf* leaf_numberofbcElectrons = b_destep->GetLeaf("numberofbcElectrons");
    
    chain->GetEntry(i);
    numberofcElectrons = (int)leaf_numberofcElectrons->GetValue(0);
    numberofbElectrons = (int)leaf_numberofbElectrons->GetValue(0);
    numberofbcElectrons = (int)leaf_numberofbcElectrons->GetValue(0);
    weight = (Float_t)lead_weight->GetValue(0);

    for(int trki = 0; trki < numberofcElectrons; trki++){
      celectron_pt      = leaf_ce_pt->GetValue(trki);
      celectron_eta     = leaf_ce_eta->GetValue(trki);
      if(celectron_eta > EtaCut || celectron_eta < -EtaCut) continue;
      hept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      hcept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      
      heptN->Fill(celectron_pt, weight); // fill NPE pt, get pt spectrum
      hceptN->Fill(celectron_pt, weight); // fill NPE pt, get pt spectrum
    }
    
    for(int trki = 0; trki < numberofbElectrons; trki++){
      celectron_pt      = leaf_be_pt->GetValue(trki);
      celectron_eta     = leaf_be_eta->GetValue(trki);
      if(celectron_eta > EtaCut || celectron_eta < -EtaCut) continue;
      hept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      hbept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      
      heptN->Fill(celectron_pt, weight); // fill NPE pt, get pt spectrum
      hbeptN->Fill(celectron_pt, weight); // fill NPE pt, get pt spectrum
    }
    
    for(int trki = 0; trki < numberofbcElectrons; trki++){
      celectron_pt      = leaf_bce_pt->GetValue(trki);
      celectron_eta     = leaf_bce_eta->GetValue(trki);
      if(celectron_eta > EtaCut || celectron_eta < -EtaCut) continue;
      hept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      hbept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      
      heptN->Fill(celectron_pt, weight); // fill NPE pt, get pt spectrum
      hbeptN->Fill(celectron_pt, weight); // fill NPE pt, get pt spectrum
    }
  }
  
  fout.Write();
  fout.Close();
  delete chain;
}
