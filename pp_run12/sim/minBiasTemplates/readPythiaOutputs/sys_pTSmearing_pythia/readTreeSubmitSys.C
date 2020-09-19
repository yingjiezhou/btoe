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

Int_t getPtBin(Float_t);

const Int_t numPtBins = anaConst::nPtBins;
Float_t lowpt[numPtBins],highpt[numPtBins];

const Float_t hptCut=anaConst::hptCut;

const float PI = TMath::Pi();
const float deletacut = 10.;
const float EtaCut = 0.7;
const float hEtaCut = 1.0;
const Float_t Vz_offset = .0;
const Float_t Vz_cut = 30;
const Float_t refmult_binWidth = 25;
const Int_t refmult_binNumber = 5;   //Vz bin 20
const int Phibin = 200;

// Prepare output file and Hists
//TFile fout("readTreeOut_Oct30_3.root","RECREATE");

//defining histograms
TH1D* hEventTallyce[numPtBins];
TH1D* hEventTallybe[numPtBins];
TH1D* hEventTallybce[numPtBins];
TH1D* hdPhiRawce[numPtBins];
TH1D* hdPhiRawceN[numPtBins];
TH1D* hdPhiRawbe[numPtBins];
TH1D* hdPhiRawbeN[numPtBins];
TH1D* hdPhiRawbce[numPtBins];
TH1D* hdEtaRawce[numPtBins];
TH1D* hdEtaRawbe[numPtBins];
TH1D* hrefmult  = new TH1D("hrefmult","hrefmult",1000,0,500); 
TH1D* hept[numPtBins]; 
const char localDir[1000] = "/global/project/projectdirs/star/pwg/starhf/zamiller/minBiasTemplates101015";
const char outDir[1000] = "/global/project/projectdirs/star/pwg/starhf/zamiller/minBiasTemplates101015";

Double_t PseudoRapidity(Double_t pt, Double_t pz);
Double_t CosTheta(Double_t pt, Double_t pz);

void readTreeSubmit(TString filelist="/global/project/projectdirs/star/pwg/starhf/zamiller/minBiasTemplates101015/Trees.list",TString outFile="/global/project/projectdirs/star/pwg/starhf/zamiller/minBiasTemplates101015/readTreeOutSubmitTEST.root")
{

  //TString filelist=Form("%s/%s",localDir,fileIn);
  //TString outFile=Form("%s/%s",outDir,fileOut);

  TFile fout(outFile,"RECREATE");
  TH1F::SetDefaultSumw2(); 
  TH1D::SetDefaultSumw2(); 

  for(Int_t c=0; c< numPtBins; c++)
  {
    lowpt[c] = anaConst::lpt[c];
    highpt[c] = anaConst::hpt[c];
  }
  for(Int_t ptbin = 0; ptbin < numPtBins; ptbin++)
  {
    hdEtaRawce[ptbin] = new TH1D(Form("hdEtaRawce_%i",ptbin),"hdEtaRawce",100, -5,5);
    hdEtaRawbe[ptbin] = new TH1D(Form("hdEtaRawbe_%i",ptbin),"hdEtaRawbe",100, -5,5);
    hEventTallyce[ptbin] = new TH1D(Form("ceEventTally_%i",ptbin),"ceEvent Tally",1,0,1);
    hEventTallybe[ptbin] = new TH1D(Form("beEventTally_%i",ptbin),"beEvent Tally",1,0,1);
    hEventTallybce[ptbin] = new TH1D(Form("bceEventTally_%i",ptbin),"bceEvent Tally",1,0,1);
    hdPhiRawce[ptbin] = new TH1D(Form("hdPhiRawce_%i",ptbin),"hdPhiRawce",100,-3.14,3.14);
    hdPhiRawbe[ptbin] = new TH1D(Form("hdPhiRawbe_%i",ptbin),"hdPhiRawbe",100,-3.14,3.14);
    hdPhiRawbce[ptbin] = new TH1D(Form("hdPhiRawbce_%i",ptbin),"hdPhiRawbce",100,-3.14,3.14);
    hept[ptbin] = new TH1D(Form("hept_%i",ptbin),"hept",200,0.,20.);
  }

  // Make Chain
  TChain* chain = new TChain("tree");
  int nfile = 0;
  /*  nfile += chain->Add("Oct30_set13/pythia_tree_Oct30_13.root");
      nfile += chain->Add("Oct30_set14/pythia_tree_Oct30_14.root");
      nfile += chain->Add("Oct30_set15/pythia_tree_Oct30_15.root");
      nfile += chain->Add("Oct30_set16/pythia_tree_Oct30_16.root");
      nfile += chain->Add("Oct30_set17/pythia_tree_Oct30_17.root");
  //  nfile += chain->Add("Oct30_set12/pythia_tree_Oct30_12.root");
  //  nfile += chain->Add("Oct26_set3/pythia_tree_Oct26_3.root");
  // nfile += chain->Add("Oct18_set4/pythia_tree_Oct18_4.root");
  //nfile += chain->Add("liweiTemplate_part2.root");*/
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

  int ceNtrigger=0;
  int beNtrigger=0;
  int bceNtrigger=0;
  int ptbin,maxptbin;

  //define variables
  Int_t   Event, numberofcElectrons, numberofbElectrons,numberofbcElectrons, numberofHadrons, noTracks;   //
  Float_t celectron_id,celectron_status,celectron_pt,celectron_pz,celectron_phi,celectron_eta,celectron_y; //track info
  Float_t belectron_id,belectron_status,belectron_pt,belectron_pz,belectron_phi,belectron_eta,belectron_y;
  Float_t bcelectron_id,bcelectron_status,bcelectron_pt,bcelectron_pz,bcelectron_phi,bcelectron_eta,bcelectron_y;
  Float_t assoh_id,assoh_status,assoh_pt,assoh_pz,assoh_phi,assoh_eta,assoh_y;

  int goodEvent = 0;


  Long64_t nentries = chain->GetEntriesFast();
  int x = 0; int n = nentries; int w = 25;

  for(int i = 0; i < nentries; i++){
    Long64_t ientry = chain->LoadTree(i);
    if (ientry < 0) break;
    TBranch *b_destep = chain->GetBranch("hf2eDecay");

    TLeaf* leaf_Event_id            = b_destep->GetLeaf("Event_id");
    TLeaf* leaf_refMult             = b_destep->GetLeaf("refMult");
    TLeaf* leaf_numberofcElectrons  = b_destep->GetLeaf("numberofcElectrons");
    TLeaf* leaf_numberofbElectrons  = b_destep->GetLeaf("numberofbElectrons");
    TLeaf* leaf_numberofbcElectrons = b_destep->GetLeaf("numberofbcElectrons");
    TLeaf* leaf_numberofHadrons     = b_destep->GetLeaf("numberofHadrons");
    TLeaf* leaf_noTracks            = b_destep->GetLeaf("noTracks");

    TLeaf* leaf_ce_id               = b_destep->GetLeaf("ce_id");
    TLeaf* leaf_ce_status           = b_destep->GetLeaf("ce_status");
    TLeaf* leaf_ce_pt               = b_destep->GetLeaf("ce_pt");
    TLeaf* leaf_ce_pz               = b_destep->GetLeaf("ce_pz");
    TLeaf* leaf_ce_phi              = b_destep->GetLeaf("ce_phi");
    TLeaf* leaf_ce_eta              = b_destep->GetLeaf("ce_eta");
    TLeaf* leaf_ce_y                = b_destep->GetLeaf("ce_y");

    TLeaf* leaf_be_id               = b_destep->GetLeaf("be_id");
    TLeaf* leaf_be_status           = b_destep->GetLeaf("be_status");
    TLeaf* leaf_be_pt               = b_destep->GetLeaf("be_pt");
    TLeaf* leaf_be_pz               = b_destep->GetLeaf("be_pz");
    TLeaf* leaf_be_phi              = b_destep->GetLeaf("be_phi");
    TLeaf* leaf_be_eta              = b_destep->GetLeaf("be_eta");
    TLeaf* leaf_be_y                = b_destep->GetLeaf("be_y");

    TLeaf* leaf_bce_id              = b_destep->GetLeaf("bce_id");
    TLeaf* leaf_bce_status          = b_destep->GetLeaf("bce_status");
    TLeaf* leaf_bce_pt              = b_destep->GetLeaf("bce_pt");
    TLeaf* leaf_bce_pz              = b_destep->GetLeaf("bce_pz");
    TLeaf* leaf_bce_phi             = b_destep->GetLeaf("bce_phi");
    TLeaf* leaf_bce_eta             = b_destep->GetLeaf("bce_eta");
    TLeaf* leaf_bce_y               = b_destep->GetLeaf("bce_y");

    TLeaf* leaf_hadron_id           = b_destep->GetLeaf("hadron_id");
    TLeaf* leaf_hadron_status       = b_destep->GetLeaf("hadron_status");
    TLeaf* leaf_hadron_pt           = b_destep->GetLeaf("hadron_pt");
    TLeaf* leaf_hadron_pz           = b_destep->GetLeaf("hadron_pz");
    TLeaf* leaf_hadron_phi          = b_destep->GetLeaf("hadron_phi");
//    TLeaf* leaf_hadron_eta          = b_destep->GetLeaf("hadron_eta");
    TLeaf* leaf_hadron_y            = b_destep->GetLeaf("hadron_y");

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


    // if(i%10000 == 0)
    //   std::cout <<"Entry: "<< i << std::endl;
    chain->GetEntry(i);

    Event   = (int)leaf_Event_id->GetValue(0);
    numberofcElectrons = (int)leaf_numberofcElectrons->GetValue(0);
    // std::cout << numberofcElectrons << " ";
    numberofbElectrons = (int)leaf_numberofbElectrons->GetValue(0);
    numberofbcElectrons = (int)leaf_numberofbcElectrons->GetValue(0);
    numberofHadrons = (int)leaf_numberofHadrons->GetValue(0);
    // std::cout << "numHad: " << numberofHadrons << std::endl;
    noTracks        = leaf_noTracks->GetValue(0);
    hrefmult -> Fill(noTracks);

    //loop through matched primary tracks electron find c decayed electron
    int ceNtrigcount=0;
    maxptbin = 0;
    for(int trki = 0; trki < numberofcElectrons; trki++){
      celectron_id      = (int)leaf_ce_id->GetValue(trki);
      celectron_status  = (int)leaf_ce_status->GetValue(trki);
      celectron_pt      = leaf_ce_pt->GetValue(trki);
      celectron_pz      = leaf_ce_pz->GetValue(trki);
      celectron_phi     = leaf_ce_phi->GetValue(trki);
      celectron_eta     = leaf_ce_eta->GetValue(trki);
      celectron_y       = leaf_ce_y->GetValue(trki);
      if(celectron_pt!=-999) celectron_pt = SmearPt(celectron_pt);
      if(celectron_eta > EtaCut || celectron_eta < -EtaCut) continue;
      ptbin = getPtBin(celectron_pt);
      if(ptbin == -99) continue;
      if(ptbin > maxptbin)
        maxptbin = ptbin;
      hept[ptbin]->Fill(celectron_pt); // fill NPE pt, get pt spectrum
      hEventTallyce[maxptbin]->Fill(0.5); //fill for each NPE, to get the number of e

      for(int trkj = 0; trkj < numberofHadrons; trkj++){

        assoh_id = (int)leaf_hadron_id->GetValue(trkj);
        assoh_status  = (int)leaf_hadron_status->GetValue(trkj);
        assoh_pt      = leaf_hadron_pt->GetValue(trkj);
        assoh_pz      = leaf_hadron_pz->GetValue(trkj);
        assoh_phi     = leaf_hadron_phi->GetValue(trkj);
        assoh_eta     = PseudoRapidity(assoh_pt, assoh_pz);;
        assoh_y       = leaf_hadron_y->GetValue(trkj);
        if(assoh_pt!=-999) assoh_pt = SmearPt(assoh_pt);

        if(assoh_eta > hEtaCut || assoh_eta < -hEtaCut) continue;

        float deltPhi = assoh_phi - celectron_phi;
        float deltEta = assoh_eta - celectron_eta;
        if(deltPhi < -PI)  deltPhi += 2*PI;
        if(deltPhi >  PI) deltPhi -= 2*PI;
        if(abs(deltEta) > deletacut) continue;
        if(assoh_pt>hptCut)
        {
          hdPhiRawce[ptbin]->Fill(deltPhi); 
          hdEtaRawce[ptbin]->Fill(deltEta);
          ceNtrigcount++;
        }
      }
    }
    //if(ceNtrigcount>0)hEventTallyce[maxptbin]->Fill(0.5);
    //if(ceNtrigcount>0)ceNtrigger++;

    //b decayed electron-------------------------------------------------- 
    int beNtrigcount=0;
    maxptbin = 0;
    for(int trki = 0; trki < numberofbElectrons; trki++){
      belectron_id = (int)leaf_be_id->GetValue(trki);
      belectron_status  = (int)leaf_be_status->GetValue(trki);
      belectron_pt      = leaf_be_pt->GetValue(trki);
      belectron_pz      = leaf_be_pz->GetValue(trki);
      belectron_phi     = leaf_be_phi->GetValue(trki);
      belectron_eta     = leaf_be_eta->GetValue(trki);
      belectron_y        = leaf_be_y->GetValue(trki);
      if(belectron_pt!=-999) belectron_pt = SmearPt(belectron_pt);

      if(belectron_eta > EtaCut || belectron_eta < -EtaCut) continue;
      ptbin = getPtBin(belectron_pt);
      if(ptbin == -99) continue;
      if(ptbin > maxptbin)
        maxptbin = ptbin;
      hept[ptbin]->Fill(belectron_pt);
      hEventTallybe[maxptbin]->Fill(0.5); //fill for each NPE
      for(int trkj = 0; trkj < numberofHadrons; trkj++){

        assoh_id = (int)leaf_hadron_id->GetValue(trkj);
        assoh_status  = (int)leaf_hadron_status->GetValue(trkj);
        assoh_pt      = leaf_hadron_pt->GetValue(trkj);
        assoh_pz      = leaf_hadron_pz->GetValue(trkj);
        assoh_phi     = leaf_hadron_phi->GetValue(trkj);
        assoh_eta     = PseudoRapidity(assoh_pt, assoh_pz);
        assoh_y       = leaf_hadron_y->GetValue(trkj);
        if(assoh_pt!=-999) assoh_pt = SmearPt(assoh_pt);

        if(assoh_eta > hEtaCut || assoh_eta < -hEtaCut) continue;

        float deltPhi = assoh_phi - belectron_phi;
        float deltEta = assoh_eta - belectron_eta;
        if(deltPhi < -PI)  deltPhi += 2*PI;
        if(deltPhi >  PI) deltPhi -= 2*PI;
        if(abs(deltEta) > deletacut) continue;
        if(assoh_pt>hptCut)
        {
          hdPhiRawbe[ptbin]->Fill(deltPhi);
          hdEtaRawbe[ptbin]->Fill(deltEta);  
          beNtrigcount++;
        }
      }
    }
    //    if(beNtrigcount>0)hEventTallybe[maxptbin]->Fill("be non photonic electron",1);
    //    if(beNtrigcount>0)beNtrigger++;
    //bce decayed electron-----------------------------------------------------------------                                                                                           
    int bceNtrigcount=0;
    maxptbin = 0;
    for(int trki = 0; trki < numberofbcElectrons; trki++){
      bcelectron_id = (int)leaf_bce_id->GetValue(trki);
      bcelectron_status  = (int)leaf_bce_status->GetValue(trki);
      bcelectron_pt      = leaf_bce_pt->GetValue(trki);
      bcelectron_pz      = leaf_bce_pz->GetValue(trki);
      bcelectron_phi     = leaf_bce_phi->GetValue(trki);
      bcelectron_eta     = leaf_bce_eta->GetValue(trki);
      bcelectron_y       = leaf_bce_y->GetValue(trki);
      if(bcelectron_pt!=-999) bcelectron_pt = SmearPt(bcelectron_pt);
      if(bcelectron_eta > EtaCut || bcelectron_eta < -EtaCut) continue;
      ptbin = getPtBin(bcelectron_pt);
      if(ptbin == -99) continue;
      if(ptbin > maxptbin)
        maxptbin = ptbin;
      hept[ptbin]->Fill(bcelectron_pt);
      hEventTallybe[maxptbin]->Fill(0.5); //fill for each NPE
      for(int trkj = 0; trkj < numberofHadrons; trkj++){

        assoh_id = (int)leaf_hadron_id->GetValue(trkj);
        assoh_status  = (int)leaf_hadron_status->GetValue(trkj);
        assoh_pt      = leaf_hadron_pt->GetValue(trkj);
        assoh_pz      = leaf_hadron_pz->GetValue(trkj);
        assoh_phi     = leaf_hadron_phi->GetValue(trkj);
        assoh_eta     = PseudoRapidity(assoh_pt, assoh_pz);
        assoh_y       = leaf_hadron_y->GetValue(trkj);
        if(assoh_pt!=-999) assoh_pt = SmearPt(assoh_pt);
        if(assoh_eta > hEtaCut || assoh_eta < -hEtaCut) continue;

        float deltPhi = assoh_phi - bcelectron_phi;
        float deltEta = assoh_eta - celectron_eta;
        if(deltPhi < -PI)  deltPhi += 2*PI;
        if(deltPhi >  PI) deltPhi -= 2*PI;
        if(abs(deltEta) > deletacut) continue;
        if(assoh_pt>hptCut)
        {
          hdPhiRawbe[ptbin]->Fill(deltPhi);
          hdEtaRawbe[ptbin]->Fill(deltEta);  
          bceNtrigcount++;
        }
      }
    }
    //    if(bceNtrigcount>0)hEventTallybe[maxptbin]->Fill("be non photonic electron",1);
    //    if(bceNtrigcount>0)beNtrigger++;


    /* if(ceNtrigger+bceNtrigger+beNtrigger > 0){
       std::cout<<"ce Trigger electron number = "<<ceNtrigger<<std::endl;
       std::cout<<"be Trigger electron number = "<<beNtrigger<<std::endl;
       std::cout<<"bce Trigger electron number = "<<bceNtrigger<<std::endl;
       }*/
  }

  // After Fill Manipulations
  for(int qq = 0; qq < numPtBins; qq++)
  {
    hdPhiRawceN[qq] = (TH1D*)hdPhiRawce[qq]->Clone();
    hdPhiRawceN[qq] -> SetName(Form("hdPhiRawceN_%i",qq));
    hdPhiRawceN[qq] -> Sumw2();
    hdPhiRawceN[qq] -> Scale(1./(Double_t)hEventTallyce[qq]->GetBinContent(1));
    hdPhiRawbeN[qq] = (TH1D*)hdPhiRawbe[qq]->Clone();
    hdPhiRawbeN[qq] -> SetName(Form("hdPhiRawbeN_%i",qq));
    hdPhiRawbeN[qq] -> Sumw2();
    hdPhiRawbeN[qq] -> Scale(1./(Double_t)hEventTallybe[qq]->GetBinContent(1));
  }

  std::cout << "100% [";
  for (int x=0; x<w; x++) std::cout << "=";
  std::cout << "]" << std::endl;
  fout.Write();
  fout.Close();
  delete chain;
}

Int_t getPtBin(Float_t ept)
{
  Int_t q = 0;
  if(ept < anaConst::lpt[q])
  {
    q = -98;
  }
  else
  {
    for(Int_t ii=0; ii < anaConst::nPtBins; ii++)
    {
      if(anaConst::lpt[ii] <= ept)
        continue;
      q = ii;
      break;  
    }
  }
  q--; // reset to last bin where lowpt wasn't bigger
  return q;
}

Double_t CosTheta(Double_t pt, Double_t pz){
  Double_t ptot = sqrt(pt*pt + pz*pz);
  return ptot == 0.0 ? 1.0 : pz/ptot;
}

Double_t PseudoRapidity(Double_t pt, Double_t pz){
  double cosTheta = CosTheta(pt, pz);
  if (cosTheta*cosTheta < 1) return -0.5* TMath::Log( (1.0-cosTheta)/(1.0+cosTheta) );
  if (pz == 0) return 0;
  //Warning("PseudoRapidity","transvers momentum = 0! return +/- 10e10");
  if (pz > 0) return 10e10;
  else        return -10e10;
}

//-------------------------------------------------------------------------------
Double_t CrystalBall2(Double_t *x, Double_t *par)
{
  Double_t N = par[0];
  Double_t mu = par[1];
  Double_t s = par[2];
  Double_t n1 = par[3];
  Double_t alpha1 = par[4];
  Double_t n2 = par[5];
  Double_t alpha2 = par[6];

  Double_t A = TMath::Power(n1/fabs(alpha1), n1) * TMath::Exp(-alpha1*alpha1/2.);
  Double_t B = n1/fabs(alpha1) - fabs(alpha1);

  Double_t C = TMath::Power(n2/fabs(alpha2), n2) * TMath::Exp(-alpha2*alpha2/2.);
  Double_t D = n2/fabs(alpha2) - fabs(alpha2);

  Double_t norm = (x[0]-mu)/s;

  if(norm < -alpha1) {
    return N * A * TMath::Power(B-norm, -n1);
  } else if(norm < alpha2) {
    return N * TMath::Exp(-0.5*norm*norm);
  } else {
    return N * C * TMath::Power(D+norm, -n2);
  }
}

Double_t ABf(double *x, double *par)
{
  double a = par[0];
  double b = par[1];
  //double f = (a*a*x[0]*x[0] + b*b);
  double f = sqrt(a*a*x[0]*x[0] + b*b);

  return f;
}

Double_t SmearPt(double mcpt)
{

  TF1 *f_AB = new TF1("f_AB", &ABf, 0, 20, 2 );
  f_AB->SetParameters(0.005580,0.008293);////from bingchu's event activities note
  double sigmaptoverpt = (double)f_AB->Eval(mcpt);

  TF1 *f_CB2 = new TF1("f_CB2", &CrystalBall2, -0.5, 0.5, 7 );

  f_CB2->SetParameters(2.893e4,-0.001152,0.01034,1.305,1.659,3.432,1.75);
  //f_CB2->SetParErrors(47.65,0.000015,0.00002,0.008,0.005,0.042,0.01);

  double deltaPtovermcPt_RDM = f_CB2->GetRandom();
  //cout<<"deltaPtovermcPt_RDM"<<deltaPtovermcPt_RDM<<endl;
  hdeltaPtovermcPt_RDM->Fill(deltaPtovermcPt_RDM);

  double smrpt = mcpt + mcpt*(deltaPtovermcPt_RDM/0.01)*sigmaptoverpt;//sigmaptoverpt: real resolution from data and emebeding Jpsi signal matching;deltaPtovermcPt_RDM/0.01: rc pt possibility in this MC pt, using 0.01 is due to all resolution is normalized to 0.01.

  return smrpt;
}
