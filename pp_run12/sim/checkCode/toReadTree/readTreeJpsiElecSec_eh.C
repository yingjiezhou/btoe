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

TH1D *hjeptN;
TH1D *hjceptN;
TH1D *hjbeptN;
TH1F *hbcmid;
TH1F *hbmid;
TH1F *hcmid;


const float EtaCut = 0.7;

void readTreeSecJpsi(TString filelist="QAJpsi.list",TString outFile="QAJpsi.root")
{
  TFile fout(outFile,"RECREATE");
  TH1F::SetDefaultSumw2();
  TH1D::SetDefaultSumw2();
  
  hept = new TH1D("hept", "hept", 2000., 0., 20.);
  hcept = new TH1D("hcept", "hcept", 2000., 0., 20.);
  hbept = new TH1D("hbept", "hbept", 2000., 0., 20.);
  
  heptN = new TH1D("heptN", "heptN", 2000., 0., 20.); //all
  hceptN = new TH1D("hceptN", "hceptN", 2000., 0., 20.); // only prompt c
  hbeptN = new TH1D("hbeptN", "hbeptN", 2000., 0., 20.); // only prompt b
  
  hjeptN = new TH1D("hjeptN", "hjeptN", 2000., 0., 20.); // all
  hjceptN = new TH1D("hjceptN", "hjceptN", 2000., 0., 20.); // only prompt jpsi->e
  hjbeptN = new TH1D("hjbeptN", "hjbeptN", 2000., 0., 20.); // only prompt b->jpsi->e
  hbcmid = new TH1F("hbcmid", "", 5500, 0,5500);
  hcmid = new TH1F("hcmid", "", 5000, 0,5000);
  hbmid = new TH1F("hbmid", "", 5500, 0,5500);
  
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
  Float_t Sigma_gen;
  Float_t celectron_pt, celectron_eta, ,belectron_eta, bcelectron_eta;
  
  
  Long64_t nentries = chain->GetEntriesFast();
  int x = 0; int n = nentries; int w = 25;
  
  for(int i = 0; i < nentries; i++){
    Long64_t ientry = chain->LoadTree(i);
    if (ientry < 0) break;
    TBranch *b_destep = chain->GetBranch("hf2eDecay");
    TLeaf* leaf_ce_pt               = b_destep->GetLeaf("ce_pt");
    TLeaf* leaf_be_pt               = b_destep->GetLeaf("be_pt");
    TLeaf* leaf_bce_pt              = b_destep->GetLeaf("bce_pt");
    TLeaf* lead_sigma_gen           = b_destep->GetLeaf("sigmaGen");
    
    TLeaf* leaf_be_eta              = b_destep->GetLeaf("be_eta");
    TLeaf* leaf_ce_eta              = b_destep->GetLeaf("ce_eta");
    TLeaf* leaf_bce_eta              = b_destep->GetLeaf("bce_eta");
    
    TLeaf* lead_c_pt                = b_destep->GetLeaf("c_pt");
    TLeaf* lead_b_pt                = b_destep->GetLeaf("b_pt");
    
    TLeaf* leaf_numberofcElectrons  = b_destep->GetLeaf("numberofcElectrons");
    TLeaf* leaf_numberofbElectrons  = b_destep->GetLeaf("numberofbElectrons");
    TLeaf* leaf_numberofbcElectrons = b_destep->GetLeaf("numberofbcElectrons");
    
    auto lead_ceMom_id = b_destep->GetLeaf("ceMom_id");
    auto lead_beMom_id = b_destep->GetLeaf("beMom_id");
    auto lead_bceMom_id = b_destep->GetLeaf("bceMom_id");
    
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
    Sigma_gen = (Float_t)lead_sigma_gen->GetValue(0);
    numberofcElectrons = leaf_numberofcElectrons->GetValue(0);
    numberofbElectrons = leaf_numberofbElectrons->GetValue(0);
    numberofbcElectrons = leaf_numberofbcElectrons->GetValue(0);
    
    for(int trki = 0; trki < numberofcElectrons; trki++){
      celectron_eta     = leaf_ce_eta->GetValue(trki);
      if(celectron_eta > EtaCut || celectron_eta < -EtaCut) continue;
      
      celectron_pt      = leaf_ce_pt->GetValue(trki);
      hept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      hcept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      
      heptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum
      hceptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum
      auto momId = lead_ceMom_id->GetValue(trki);
      hbcmid->Fill(momId);
      hcmid->Fill(momId);
//      if(momId != 443) continue;
      if(momId == 443)hjeptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum
      if(momId == 443)hjceptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum    }
    }
    for(int trki = 0; trki < numberofbElectrons; trki++){
      belectron_eta     = leaf_be_eta->GetValue(trki);
      if(belectron_eta > EtaCut || belectron_eta < -EtaCut) continue;
      
      celectron_pt      = leaf_be_pt->GetValue(trki);
      hept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      hbept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      
      heptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum
      hbeptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum
      auto momId = lead_beMom_id->GetValue(trki);
      hbcmid->Fill(momId);
      hbmid->Fill(momId);
//      if(momId != 443) continue;
      if(momId == 443)hjeptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum
      if(momId == 443)hjbeptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum
    }
    
    for(int trki = 0; trki < numberofbcElectrons; trki++){
      bcelectron_eta     = leaf_bce_eta->GetValue(trki);
      if(bcelectron_eta > EtaCut || bcelectron_eta < -EtaCut) continue;
      
      celectron_pt      = leaf_bce_pt->GetValue(trki);
      hept->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      heptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum
      auto momId = lead_beMom_id->GetValue(trki);
      hbcmid->Fill(momId);
//      if(momId != 443) continue;
      if(momId == 443)hjeptN->Fill(celectron_pt, Sigma_gen/5000000.); // fill NPE pt, get pt spectrum
    }
  }
  
  std::cout << "100% [";
  for (int x=0; x<w; x++) std::cout << "=";
  std::cout << "]" << std::endl;
  
  fout.Write();
  fout.Close();
  delete chain;
}
