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
//#include "anaConst.h"
#include "TString.h"


TH1D *heptN;
TH1D *heptNy;
TH1D *hjeptN;
//TH1D *hjceptN;
//TH1D *hjbeptN;



const float EtaCut = 0.7;
const float yCut = 0.5;

void readTreeJpsiSec(TString filelist="test.list",TString outFile="HQbcSet_hist.root")
{
  TFile fout(outFile,"RECREATE");
  TH1F::SetDefaultSumw2();
  TH1D::SetDefaultSumw2();
  
  heptN = new TH1D("heptN", "heptN", 2000., 0., 20.);
  heptNy = new TH1D("heptNy", "heptNy", 2000., 0., 20.);
  
  hjeptN = new TH1D("hjeptN", "hjeptN", 2000., 0., 20.);
//  hjceptN = new TH1D("hjceptN", "hjceptN", 2000., 0., 20.);
//  hjbeptN = new TH1D("hjbeptN", "hjbeptN", 2000., 0., 20.);
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
    TBranch *b_destep = chain->GetBranch("jpsiDecay");
    TLeaf* leaf_orig_id            = b_destep->GetLeaf("orig_id");
    TLeaf* leaf_orig_status           = b_destep->GetLeaf("orig_status");
    TLeaf* leaf_jpsi_id              = b_destep->GetLeaf("jpsi_id");
    TLeaf* leaf_jpsi_status              = b_destep->GetLeaf("jpsi_status");
    TLeaf* leaf_jpsi_pt              = b_destep->GetLeaf("jpsi_pt");
    TLeaf* leaf_jpsi_y                = b_destep->GetLeaf("jpsi_y");
    
    TLeaf* leaf_e_y               = b_destep->GetLeaf("e_y");
    TLeaf* leaf_e_eta             = b_destep->GetLeaf("e_eta");
    TLeaf* leaf_e_pt                = b_destep->GetLeaf("e_pt");
    TLeaf* leaf_p_y               = b_destep->GetLeaf("p_y");
    TLeaf* leaf_p_eta             = b_destep->GetLeaf("p_eta");
    TLeaf* leaf_p_pt                = b_destep->GetLeaf("p_pt");
    
    TLeaf* leaf_weight                = b_destep->GetLeaf("weight");
    TLeaf* leaf_sigmaGen                = b_destep->GetLeaf("sigmaGen");

    x = i+1;
    // Process Completion bar
//    if ( (x != n) && (x % (n/100) == 0) )
//    {
//      float ratio  =  (float)x/(float)n;
//      int   c      =  ratio * w;
//
//      if(ratio < 1){
//        std::cout << (int)(ratio*100) << "% [";
//        for (int x=0; x<c; x++) std::cout << "=";
//        for (int x=c; x<w; x++) std::cout << " ";
//        std::cout << "]\r" << std::flush ;
//      }
//    }
    
    chain->GetEntry(i);
    
    auto weight = (Float_t)leaf_weight->GetValue(0);
    auto sigmaGen = (Float_t)leaf_sigmaGen->GetValue(0);

//    cout<<weight<<"  -  "<<sigmaGen<<" - "<<sigmaGen/5000000.<<endl;
    auto orig_id = (Float_t)leaf_orig_id->GetValue(0);
    auto orig_status = (Float_t)leaf_orig_status->GetValue(0);
//    auto jpsi_id = (Float_t)leaf_jpsi_id->GetValue(0);
    auto jpsi_status = (Float_t)leaf_jpsi_status->GetValue(0);
    auto jpsi_id = (Float_t)leaf_jpsi_id->GetValue(0);
    auto jpsi_pt = (Float_t)leaf_jpsi_pt->GetValue(0);
    auto jpsi_y = (Float_t)leaf_jpsi_y->GetValue(0);
    
    auto e_y = (Float_t)leaf_e_y->GetValue(0);
    auto e_eta = (Float_t)leaf_e_eta->GetValue(0);
    auto e_pt = (Float_t)leaf_e_pt->GetValue(0);
    
    auto p_y = (Float_t)leaf_p_y->GetValue(0);
    auto p_eta = (Float_t)leaf_p_eta->GetValue(0);
    auto p_pt = (Float_t)leaf_p_pt->GetValue(0);
    
    
//    if(jpsi_y > yCut || jpsi_y < -yCut) continue;
    if(orig_id == 0) continue; //If no origin or more than 1 than id == 0
    if(orig_id != 443) continue;
    if(orig_status == -1 || orig_status == -2) continue;
    if(jpsi_id != 443 ) continue;
    
    if(jpsi_y < yCut && jpsi_y > -yCut) hjeptN->Fill(jpsi_pt, weight);
    
    if(e_y < yCut && e_y > -yCut) heptNy->Fill(e_pt, weight);
    if(e_eta < EtaCut && e_eta > -EtaCut) heptN->Fill(e_pt, weight);
  }
  
  
//  std::cout << "100% [";
//  for (int x=0; x<w; x++) std::cout << "=";
//  std::cout << "]" << std::endl;
  
  fout.Write();
  fout.Close();
  delete chain;
}
