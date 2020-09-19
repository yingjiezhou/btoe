#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "math.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TFile.h"
#include "TPDF.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TLatex.h"
#include "TVector3.h"
#include "TVector2.h"
#include "TUnixSystem.h"
#include "TNtuple.h"
#include "TMinuit.h"
using std::cout;
using std::endl;

#include "hfProdTree.h"
#include <vector>

//global variables
const int maxInputFiles = 1000;
const char* indir=".";
const char* outdir=".";

float particleEtaCutMax = 0.7;
float particlePtCutMin  = 2.0;

//float hadronEtaCutMax = 4.0;
//float hadronEtaCutMin = 2.5;
float hadronPtCutMin = 0.15;
float hadronPtCutMax = 2.0;

// min-bias Au+Au
float RefFlowMultAuAu = 281.7;
float RefFlowMultErrAuAu = 7.58e-02;

float RefFlowAuAu = 0.0481507;  //v2{2} ref: 0.0481507 +/- 7.5517e-06 for 0-60% Au+Au 200 GeV (min-bias events)
float RefFlowErrAuAu = 7.5517e-06;

const int nEtaGaps=1;
const int nPtBins=5;
double etagap[nEtaGaps]={0.05};
double ptBin[nPtBins+1]={2.0, 2.5, 3.5, 4.5, 5.5, 8.5};

bool isFullRange = true;

double deltaPhi(double phi1, double phi2, double eta1, float deltaEta)
{
  
  // correct difference
  if(fabs(eta1)<deltaEta) return 4.0;
  
  double deltaphi = phi2-phi1;
  if (deltaphi < -M_PI) deltaphi += 2*M_PI;
  if (deltaphi > M_PI) deltaphi -= 2*M_PI;
  
  return deltaphi;
}

/////////////////////////////////////
// main function
/////////////////////////////////////
int main(int argc, char *argv[])
{
  float phiCut = 1.57;
  if(isFullRange)
    phiCut = 3.14;
  
  TString inputfilename, outputfilename;
  std::cout<<"Read in "<<inputfilename<<std::endl;
  
  if(argc<2) return 1;
  
  TString indir = "/star/data01/pwg/yjzhou19/Non-flow/npeHadronPhiCorr_rcf_charm/output";
  //TString indir = "/star/u/ypwang/disk01/analysisHF/Run14_Analysis/nonFlowEffect/npeHadronPhiCorr/output";
  TString outdir = "/star/data01/pwg/yjzhou19/Non-flow/hfAnaStudy_Yp_TPC_charm/output";
  
  TString inputrootfilename = argv[1];
  inputfilename = Form("%s/%s", indir.Data(), inputrootfilename.Data());
  
  TString outputrootfilename = inputrootfilename(0,inputrootfilename.Sizeof()-6)+"_hist.root";
  outputfilename = Form("%s/%s", outdir.Data(), outputrootfilename.Data());
  cout<<outputfilename<<endl;
  
  TFile *f = new TFile(inputfilename);
  TTree *tree;
  tree = (TTree*)f->Get("hfProdTree");
  hfProdTree *hfSimTree = new hfProdTree(tree);
  
  //----------------------------------
  // histograms definitions
  //----------------------------------
  TFile *file = new TFile(outputfilename,"RECREATE");
  TH1F* hStatistics;
  float fCrossSection,fNAcceptedEvent,fWeight;
  hStatistics=(TH1F*)f->Get("hStatistics");
  if{hStatistics}{
    fCrossSection = hStatistics->GetBinContent(1);
    fNAcceptedEvent = hStatistics->GetBinContent(2);
    fWeight = fCrossSection/fNAcceptedEvent;
  }
  //fWeight = 1.0;
  TH1F *hPTHat;
  hPTHat=(TH1F*)f->Get("hPTHat");
  
  //before cuts
  TH1F *hElecMult_gen = new TH1F("hElecMult_gen", "hElecMult_gen", 10, 0, 10);
  hElecMult_gen->Sumw2();
  TH1F *hPTTrkE_gen = new TH1F("hPTTrkE_gen", "hPTTrkE_gen", 500, 0., 50.);
  hPTTrkE_gen->Sumw2();
  TH1F *hEtaE_gen = new TH1F("hEtaE_gen", "hEtaE_gen", 40, -2., 2.);
  hEtaE_gen->Sumw2();
  TH1F *hPhiE_gen = new TH1F("hPhiE_gen", "hPhiE_gen", 200, -M_PI, M_PI);
  hPhiE_gen->Sumw2();
  
  //after cuts
  TH1F *hElecMult = new TH1F("hElecMult", "hElecMult", 10, 0, 10);
  hElecMult->Sumw2();
  TH1F *hPTTrkE = new TH1F("hPTTrkE", "hPTTrkE", 500, 0., 50.);
  hPTTrkE->Sumw2();
  TH1F *hEtaE = new TH1F("hEtaE", "hEtaE", 40, -2., 2.);
  hEtaE->Sumw2();
  TH1F *hPhiE = new TH1F("hPhiE", "hPhiE", 200, -M_PI, M_PI);
  hPhiE->Sumw2();
  
  TH2D* prfCorrelationV2Pt = new TH2D("prfCorrelationV2Pt", "prfCorrelationV2Pt", 200,0.,20.,200, -M_PI, M_PI);
  prfCorrelationV2Pt->Sumw2();
  
  char name1[100];
  TH1F* hCos2DPhi_allTracks[nPtBins+1]; //the last one indicate no pT cut required
  TH1F* hDPhi_allTracks[nPtBins+1]; //the last one indicate no pT cut required
  for(int iPt=0; iPt<nPtBins+1; iPt++) {
    sprintf(name1,"hCos2DPhi_allTracks_PtBin%d",iPt);
    hCos2DPhi_allTracks[iPt] = new TH1F(name1, name1, 210, -1.05, 1.05);
    hCos2DPhi_allTracks[iPt]->Sumw2();
    
    sprintf(name1,"hDPhi_allTracks_PtBin%d",iPt);
    hDPhi_allTracks[iPt] = new TH1F(name1, name1, 200, -M_PI, M_PI);
    hDPhi_allTracks[iPt]->Sumw2();
  }
  
  TH2D* prfCorrelationV2PtEta[nEtaGaps];
  TH1F* hCos2DPhi[nEtaGaps][nPtBins+1];
  TH1F* hDPhi[nEtaGaps][nPtBins+1];
  for(int h=0; h<nEtaGaps; h++){
    sprintf(name1,"prfCorrelationV2Pt_deltaEta0%d",h+1);
    prfCorrelationV2PtEta[h] = new TH2D(name1, name1, 200,0.,20.,200, -M_PI, M_PI);
    prfCorrelationV2PtEta[h]->Sumw2();
    
    for(int iPt=0; iPt<nPtBins+1; iPt++) {
      sprintf(name1,"hCos2DPhi_deltaEta0%d_PtBin%d",h+1,iPt);
      hCos2DPhi[h][iPt] = new TH1F(name1, name1, 210, -1.05, 1.05);
      hCos2DPhi[h][iPt]->Sumw2();
      
      sprintf(name1,"hDPhi_deltaEta0%d_PtBin%d",h+1,iPt);
      hDPhi[h][iPt] = new TH1F(name1, name1, 200, -M_PI, M_PI);
      hDPhi[h][iPt]->Sumw2();
    }
  }
  
  //count trigger NPE per pT bin
  int numTrigNPE[nPtBins+1][nEtaGaps+1];
  for(int ii=0; ii<nPtBins+1; ii++) {
    for(int jj=0; jj<nEtaGaps+1; jj++) {
      numTrigNPE[ii][jj] = 0;
    }
  }
  
  TH1F *hNumTrigNPE_allTracks = new TH1F("hNumTrigNPE_allTracks", "", 6, 0, 6.);
  TH1F *hNumTrigNPE_deltaEta1 = new TH1F("hNumTrigNPE_deltaEta1", "", 6, 0, 6.);
  TH1F *hNumTrigNPE_deltaEta2 = new TH1F("hNumTrigNPE_deltaEta2", "", 6, 0, 6.);
  TH1F *hNumTrigNPE_deltaEta3 = new TH1F("hNumTrigNPE_deltaEta3", "", 6, 0, 6.);
  TH1F *hNumTrigNPE_deltaEta4 = new TH1F("hNumTrigNPE_deltaEta4", "", 6, 0, 6.);
  hNumTrigNPE_allTracks->Sumw2();
  hNumTrigNPE_deltaEta1->Sumw2();
  hNumTrigNPE_deltaEta2->Sumw2();
  hNumTrigNPE_deltaEta3->Sumw2();
  hNumTrigNPE_deltaEta4->Sumw2();
  
  TH1F *hM2[nEtaGaps+1][nPtBins+1];
  TH1F *hV2[nEtaGaps+1][nPtBins+1];
  TH1F *hHad[nEtaGaps+1][nPtBins+1];
  TString hName[5] = {"noEtaGap","EtaGap_dot0","EtaGap_dot1","EtaGap_dot2","EtaGap_dot4"};
  for(int iGap=0; iGap<nEtaGaps+1; iGap++) {
    for(int iPt=0; iPt<nPtBins+1; iPt++) {
      hM2[iGap][iPt] = new TH1F(Form("hM2_%s_pTBin%d",hName[iGap].Data(),iPt),"",400, -2.0, 2.0);
      hM2[iGap][iPt]->Sumw2();
      hHad[iGap][iPt] = new TH1F(Form("hHad_%s_pTBin%d",hName[iGap].Data(),iPt),"",20,0.,20.);
      hHad[iGap][iPt]->Sumw2();
      
      hV2[iGap][iPt] = new TH1F(Form("hV2_%s_pTBin%d",hName[iGap].Data(),iPt),"",400, -2.0, 2.0);
      hV2[iGap][iPt]->Sumw2();
    }
  }
  //--------------------
  // loop the chain
  //--------------------
  int nevents = (int)tree->GetEntries();
  cout << "== Total Events : " << nevents << endl;
  
  //loop event
  for(int iEvent=0; iEvent<nevents; iEvent++) {
    if(!(iEvent%10000))
      cout << "Begin " << iEvent << "th entry...." << endl;
    
    //calculate
    int numNpeHadCorr[nPtBins+1][nEtaGaps+1];
    int numTrigNPEperEvt[nPtBins+1][nEtaGaps+1];
    for(int ii=0; ii<nPtBins+1; ii++) {
      for(int jj=0; jj<nEtaGaps+1; jj++) {
        numNpeHadCorr[ii][jj] = 0;
        numTrigNPEperEvt[ii][jj] = 0;
      }
    }
    
    float sumCos2Dphi_allTracks[nPtBins+1];
    for(int iPt=0; iPt<nPtBins+1; iPt++) {
      sumCos2Dphi_allTracks[iPt] = 0.;
    }
    
    float sumCos2Dphi[nEtaGaps][nPtBins+1];
    for(int h=0; h<nEtaGaps; h++){
      for(int iPt=0; iPt<nPtBins+1; iPt++) {
        sumCos2Dphi[h][iPt] = 0.;
      }
    }
    
    hfSimTree->GetEntry(iEvent);
    
    int numOfElectrons = hfSimTree->nElec;
    hElecMult_gen->Fill(numOfElectrons, fWeight);
    
    int passedNumOfElectrons = 0;
    for(int iElec=0; iElec<numOfElectrons; iElec++) {
      // zyj tree leaf
      double hpTTrkE=hfSimTree->pTTrkE[iElec];
      double hetaE=hfSimTree->etaE[iElec];
      double hphiE=hfSimTree->phiE[iElec];
      
      hPTTrkE_gen->Fill(hpTTrkE,fWeight);
      hEtaE_gen->Fill(hetaE, fWeight);
      hPhiE_gen->Fill(hphiE, fWeight);
      
      if(hpTTrkE < particlePtCutMin) continue; //pT cut for selected electron
      if( fabs(hetaE) > particleEtaCutMax ) continue; //eta cut for selected electron
      passedNumOfElectrons++;
      
      hEtaE->Fill(hetaE, fWeight);
      hPTTrkE->Fill(hpTTrkE,fWeight);
      hPhiE->Fill(hphiE, fWeight);
      
      int pTbinIndex = 0;
      if(hpTTrkE>=ptBin[0] && hpTTrkE<ptBin[1])   pTbinIndex = 0;
      if(hpTTrkE>=ptBin[1] && hpTTrkE<ptBin[2])   pTbinIndex = 1;
      if(hpTTrkE>=ptBin[2] && hpTTrkE<ptBin[3])   pTbinIndex = 2;
      if(hpTTrkE>=ptBin[3] && hpTTrkE<ptBin[4])   pTbinIndex = 3;
      if(hpTTrkE>=ptBin[4] && hpTTrkE<ptBin[5])   pTbinIndex = 4;
      //===================================hadron end ==============================

      // zyj hadron e correlation
      bool hasWritten_allTracks = false;
      bool hasWritten_etaGaps[nEtaGaps];
      for(int h=0; h<nEtaGaps; h++)
        hasWritten_etaGaps[h] = false;
      
      int numOfHadrons = hfSimTree->Hadrons_;
      for(int iBH=0; iBH<numOfHadrons; iBH++) {
        int pdgCode = hfSimTree->Hadrons_idSave[iBH];
        
        if(fabs(pdgCode)!=211 && fabs(pdgCode)!=321 && fabs(pdgCode)!=2212) continue;
        //if(fabs(pdgCode)!=111 && fabs(pdgCode)!=22) continue; //only consider charged pions, kaons, protons
        
        // e, hadron pt, eta cut
        TVector3 pSave(hfSimTree->Hadrons_pSave_xx[iBH], hfSimTree->Hadrons_pSave_yy[iBH], hfSimTree->Hadrons_pSave_zz[iBH]);
        
        //if( pSave.Eta() > hadronEtaCutMax || pSave.Eta() < hadronEtaCutMin ) continue;
        if( fabs(pSave.Eta())>1.) continue;
        if(pSave.Perp() < hadronPtCutMin || pSave.Perp() > hadronPtCutMax) continue; // fms, no need here
        if((hphiE==0)||(pSave.Phi()==0)) continue;
        
        float cosineDPhi_allTracks = 0.;
        float cosineDPhi_etaGaps[nEtaGaps];
        for(int j=0; j<nEtaGaps; j++) {
          cosineDPhi_etaGaps[j] = 0.;
        }
        
        float correlationV2 = deltaPhi(hphiE, pSave.Phi(), pSave.Eta(), 0); //Using all tracks
        if(deltaPhi(hphiE, pSave.Phi(), pSave.Eta(), 0) != 4.0) {
          prfCorrelationV2Pt->Fill(hpTTrkE, correlationV2, fWeight);
          
          hDPhi_allTracks[pTbinIndex]->Fill(correlationV2, fWeight);
          hDPhi_allTracks[5]->Fill(correlationV2, fWeight);
          
          if(fabs(correlationV2)<phiCut) {
            cosineDPhi_allTracks = TMath::Cos(2.*correlationV2);
            hCos2DPhi_allTracks[pTbinIndex]->Fill(cosineDPhi_allTracks, fWeight);
            hCos2DPhi_allTracks[5]->Fill(cosineDPhi_allTracks, fWeight);
            
            sumCos2Dphi_allTracks[pTbinIndex] += cosineDPhi_allTracks;
            sumCos2Dphi_allTracks[5] += cosineDPhi_allTracks;
            
            numNpeHadCorr[pTbinIndex][0]++;
            numNpeHadCorr[5][0]++;
            
            if(!hasWritten_allTracks) {
              numTrigNPE[pTbinIndex][0]++;
              numTrigNPE[5][0]++;
              
              numTrigNPEperEvt[pTbinIndex][0]++;
              numTrigNPEperEvt[5][0]++;
              
              hasWritten_allTracks = true;
            }
          }
        }
        
        if(hetaE*pSave.Eta() > 0) continue; // Using tracks from the opposite eta hemisphere
        
        // zyj calculate delta phi
        for(int h=0; h<nEtaGaps; h++){
          sprintf(name1,"prfCorrelationV2Pt_deltaEta0%d",h+1);
          if(deltaPhi(hphiE, pSave.Phi(), pSave.Eta(), etagap[h]) == 4.0) continue;
          float tempDeltaPhi = deltaPhi(hphiE, pSave.Phi(), pSave.Eta(), etagap[h]);
          prfCorrelationV2PtEta[h]->Fill(hpTTrkE, tempDeltaPhi, fWeight);
          
          hDPhi[h][pTbinIndex]->Fill(tempDeltaPhi, fWeight);
          hDPhi[h][5]->Fill(tempDeltaPhi, fWeight);
          
          if(fabs(tempDeltaPhi)<phiCut)    {
            cosineDPhi_etaGaps[h] = TMath::Cos(2.*tempDeltaPhi);
            hCos2DPhi[h][pTbinIndex]->Fill(cosineDPhi_etaGaps[h], fWeight);
            hCos2DPhi[h][5]->Fill(cosineDPhi_etaGaps[h], fWeight);
            
            sumCos2Dphi[h][pTbinIndex] += cosineDPhi_etaGaps[h];
            sumCos2Dphi[h][5] += cosineDPhi_etaGaps[h];
            
            numNpeHadCorr[pTbinIndex][h+1]++;
            numNpeHadCorr[5][h+1]++;
            
            if(!hasWritten_etaGaps[h]) {
              numTrigNPE[pTbinIndex][h+1]++;
              numTrigNPE[5][h+1]++;
              
              numTrigNPEperEvt[pTbinIndex][h+1]++;
              numTrigNPEperEvt[5][h+1]++;
              
              hasWritten_etaGaps[h] = true;
            }
          }
        }
      }//end of hadron vector loop per event
    }//end of b->e loop per event
    hElecMult->Fill(passedNumOfElectrons, fWeight);
    
    for(int iPt=0; iPt<nPtBins+1; iPt++) {
      if(numNpeHadCorr[iPt][0]>0){
        hM2[0][iPt]->Fill(sumCos2Dphi_allTracks[iPt]/numNpeHadCorr[iPt][0]);
        hHad[0][iPt]->Fill(numNpeHadCorr[iPt][0]/numTrigNPEperEvt[iPt][0]);
      }
      
      for(int h=0; h<nEtaGaps; h++){
        if(numNpeHadCorr[iPt][h+1]>0){
          hM2[h+1][iPt]->Fill(sumCos2Dphi[h][iPt]/numNpeHadCorr[iPt][h+1]);
          hHad[h+1][iPt]->Fill(numNpeHadCorr[iPt][h+1]/numTrigNPEperEvt[iPt][h+1]);
        }
      }
      
      if(numTrigNPEperEvt[iPt][0]>0) {
        hV2[0][iPt]->Fill(sumCos2Dphi_allTracks[iPt]/numTrigNPEperEvt[iPt][0]/RefFlowMultAuAu/RefFlowAuAu);
      }
      
      for(int h=0; h<nEtaGaps; h++){
        if(numTrigNPEperEvt[iPt][h+1]>0) {
          hV2[h+1][iPt]->Fill(sumCos2Dphi[h][iPt]/numTrigNPEperEvt[iPt][h+1]/RefFlowMultAuAu/RefFlowAuAu);
        }
      }
    }
    
  }//end of event loop
  
  for(int i=0; i<6; i++) {
    hNumTrigNPE_allTracks->SetBinContent(i+1, numTrigNPE[i][0]);
    hNumTrigNPE_deltaEta1->SetBinContent(i+1, numTrigNPE[i][1]);
    //hNumTrigNPE_deltaEta2->SetBinContent(i+1, numTrigNPE[i][2]);
    //hNumTrigNPE_deltaEta3->SetBinContent(i+1, numTrigNPE[i][3]);
    //hNumTrigNPE_deltaEta4->SetBinContent(i+1, numTrigNPE[i][4]);
  }
  
  hNumTrigNPE_allTracks->Write();
  hNumTrigNPE_deltaEta1->Write();
  //hNumTrigNPE_deltaEta2->Write();
  //hNumTrigNPE_deltaEta3->Write();
  //hNumTrigNPE_deltaEta4->Write();
  
  for(int iPt=0; iPt<nPtBins+1; iPt++) {
    hCos2DPhi_allTracks[iPt]->Write();
    hDPhi_allTracks[iPt]->Write();
  }
  
  for(int h=0; h<nEtaGaps; h++) {
    prfCorrelationV2PtEta[h]->Write();
    
    for(int iPt=0; iPt<nPtBins+1; iPt++) {
      hDPhi[h][iPt]->Write();
      hCos2DPhi[h][iPt]->Write();
    }
  }
  
  for(int iGap=0; iGap<nEtaGaps+1; iGap++) {
    for(int iPt=0; iPt<nPtBins+1; iPt++) {
      hM2[iGap][iPt]->Write();
      hV2[iGap][iPt]->Write();
      hHad[iGap][iPt]->Write();
    }
  }
  
  prfCorrelationV2Pt->Write();
  
  hStatistics->Write();
  hPTHat->Write();
  
  hElecMult_gen->Write();
  hPTTrkE_gen->Write();
  hEtaE_gen->Write();
  hPhiE_gen->Write();
  
  hElecMult->Write();
  hPTTrkE->Write();
  hEtaE->Write();
  hPhiE->Write();
  
  file->Close();
  
  return 0;
}



