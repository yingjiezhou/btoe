// Read Pythia produced c->e and b->e events from MinBias Pythia p+p 200 GeV events
// Updated Oct. 7, 2015 - Z. Miller

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

Double_t PseudoRapidity(Double_t pt, Double_t pz);
Double_t CosTheta(Double_t pt, Double_t pz);

void readTreeHadron(TString filelist="readTreeHadron.list"){
  
  TH1F::SetDefaultSumw2();
  TH1D::SetDefaultSumw2();
  auto fout = new TFile("readTreeHadron.root", "RECREATE");
  
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
  
  //define variables
  Int_t   Event, numberofcElectrons, numberofbElectrons,numberofbcElectrons, numberofHadrons, noTracks;   //
  Float_t celectron_id,celectron_status,celectron_pt,celectron_pz,celectron_phi,celectron_eta,celectron_y; //track info
  Float_t belectron_id,belectron_status,belectron_pt,belectron_pz,belectron_phi,belectron_eta,belectron_y;
  Float_t bcelectron_id,bcelectron_status,bcelectron_pt,bcelectron_pz,bcelectron_phi,bcelectron_eta,bcelectron_y;
  Float_t assoh_id,assoh_status,assoh_pt,assoh_pz,assoh_phi,assoh_eta,assoh_y, assoh_etaS;
  
  auto hLc = new TH1D("hLc", "", 200, 0., 20.);
  auto hD0 = new TH1D("hD0", "", 200, 0., 20.);
  
  auto hLb = new TH1D("hLb", "", 200, 0., 20.);
  auto hB0 = new TH1D("hB0", "", 200, 0., 20.);
  
  auto h2Lb = new TH1D("h2Lb", "", 200, 0., 20.);
  auto h2B0 = new TH1D("h2B0", "", 200, 0., 20.);
  
  // new pythia tune
  Long64_t nentries = chain->GetEntriesFast();
  for(int i = 0; i < nentries; i++){
    Long64_t ientry = chain->LoadTree(i);
    if (ientry < 0) break;
    TBranch *b_destep = chain->GetBranch("hf2eDecay");
    TLeaf* leaf_hadron_id           = b_destep->GetLeaf("hadron_id");
    TLeaf* leaf_hadron_status       = b_destep->GetLeaf("hadron_status");
    TLeaf* leaf_hadron_pt           = b_destep->GetLeaf("hadron_pt");
    TLeaf* leaf_hadron_pz           = b_destep->GetLeaf("hadron_pz");
    TLeaf* leaf_hadron_phi          = b_destep->GetLeaf("hadron_phi");
//    TLeaf* leaf_hadron_eta          = b_destep->GetLeaf("hadron_eta");
    TLeaf* leaf_hadron_y            = b_destep->GetLeaf("hadron_y");
    TLeaf* leaf_numberofHadrons     = b_destep->GetLeaf("numberofHadrons");

    chain->GetEntry(i);
    numberofHadrons = (int)leaf_numberofHadrons->GetValue(0);
    for(int trkj = 0; trkj < numberofHadrons; trkj++){
      assoh_id = (int)leaf_hadron_id->GetValue(trkj);
      assoh_status  = (int)leaf_hadron_status->GetValue(trkj);
      assoh_pt      = leaf_hadron_pt->GetValue(trkj);
      assoh_pz      = leaf_hadron_pz->GetValue(trkj);
      assoh_phi     = leaf_hadron_phi->GetValue(trkj);
      assoh_etaS     = PseudoRapidity(assoh_pt, assoh_pz);
      assoh_y       = leaf_hadron_y->GetValue(trkj);
      if(assoh_status == 0.) continue;
      if(assoh_etaS>-1. && assoh_etaS<1.){
        if(abs(assoh_id) == 421) hD0->Fill(assoh_pt);
        if(abs(assoh_id) == 4122)hLc->Fill(assoh_pt);
        if(abs(assoh_id) == 511) hB0->Fill(assoh_pt);
        if(abs(assoh_id) == 5122)hLb->Fill(assoh_pt);
        
      }
      if(assoh_etaS>2. && assoh_etaS<5.){
        if(abs(assoh_id) == 511) h2B0->Fill(assoh_pt);
        if(abs(assoh_id) == 5122)h2Lb->Fill(assoh_pt);
      }
    }
  }
  
  fout->Write();
  fout->Close();
  delete chain;
}

Double_t CosTheta(Double_t pt, Double_t pz){
  Double_t ptot = sqrt(pt*pt + pz*pz);
  return ptot == 0.0 ? 1.0 : pz/ptot;
}

Double_t PseudoRapidity(Double_t pt, Double_t pz){
  double cosTheta = CosTheta(pt, pz);
  if (cosTheta*cosTheta < 1) return -0.5* TMath::Log( (1.0-cosTheta)/(1.0+cosTheta) );
  if (pz == 0) return 0;
  if (pz > 0) return 10e10;
  else        return -10e10;
}
