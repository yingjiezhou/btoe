// Offline Plots - Z. Miller July 24, 2015
//
// .L offline.C
// offline("FILENAME") # Without .root Extension

#include "anaConst.h"

// Declare functions
Bool_t checkPaintAllTrigs();
void checkBatchMode();
Bool_t checkMakePDF();
Bool_t checkMakeRoot();
void offline(const char* FileName="Sep19", const char* FileNameR="default")
{
  TH1F::SetDefaultSumw2();
  gROOT->SetBatch(kTRUE);
  
  // Set Style parameters for this macro
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1); // Show Title (off by default for cleanliness)
  gErrorIgnoreLevel = kError; // Set Verbosity Level (kPrint shows all)
  
  //=========================================================
  // for sys. study
  Bool_t doPurity = kFALSE;
  Bool_t doRec = kFALSE;
  Bool_t doRecGpt = kFALSE; // phe partner e gpt
  Bool_t doRecMass = kFALSE; // phe pair mass cut
  Bool_t doPuritySigmae = kFALSE; // change nsigmae
  Bool_t doPurityPoe = kFALSE;
  Bool_t doPurityAdc0 = kFALSE;
  Bool_t doRecGpt2 = kFALSE; // phe partner e gpt, 04 cut
  Bool_t doMinusP = kFALSE;
  Bool_t doMinusR = kFALSE;
  Bool_t doPileup = kFALSE;
  Bool_t doMinusPp = kFALSE;

  if(strcmp ("purityPlus", FileNameR) == 0) doPurity = kTRUE;
  if(strcmp ("purityMinus", FileNameR) == 0) doMinusP = kTRUE;
  if(strcmp ("recPlus", FileNameR) == 0) doRec = kTRUE;
  if(strcmp ("recMinus", FileNameR) == 0) doMinusR = kTRUE;
  if(strcmp ("pileupPlus", FileNameR) == 0) doPileup = kTRUE;
  if(strcmp ("pileupMinus", FileNameR) == 0) doMinusPp = kTRUE;
  if(strcmp ("nsigmae", FileNameR) == 0) doPuritySigmae = kTRUE;
  if(strcmp ("poe", FileNameR) == 0) doPurityPoe = kTRUE;
  if(strcmp ("trig", FileNameR) == 0) doPurityAdc0 = kTRUE;
  if(strcmp ("masscut", FileNameR) == 0) doRecMass = kTRUE;
  if(strcmp ("gpt", FileNameR) == 0) doRecGpt = kTRUE;
  if(strcmp ("gpt04", FileNameR) == 0) doRecGpt2 = kTRUE;
  //===================================================================================
  // Set Output options
  //  Int_t number;
  //Bool_t fPaintAll = checkPaintAllTrigs();
  Bool_t fPaintAll = kFALSE;
  //checkBatchMode();
  //  Bool_t makePDF = checkMakePDF();
  //  Bool_t makeROOT= checkMakeRoot();
  
  Bool_t makePDF = kTRUE;
  Bool_t makeROOT= kTRUE;
  // Open ROOT File
  char name[1000];
  
  if(doPurity || doRec || doPileup || doMinusP || doMinusR || doMinusPp) sprintf(name,"input/data/%s_default.root",FileName);
  else sprintf(name,"input/data/%s_%s.root",FileName, FileNameR);

  if(doPurityAdc0) sprintf(name,"input/data/%s_trig.root",FileName);
  if(doPuritySigmae) sprintf(name,"input/data/%s_nsigmae.root",FileName);
  if(doPurityPoe) sprintf(name,"input/data/%s_poe.root",FileName);
  if(doRecMass) sprintf(name,"input/data/%s_masscut.root",FileName);
  if(doRecGpt) sprintf(name,"input/data/%s_gpt.root",FileName);
  
  
  TFile *f = new TFile(name,"READ");
  if (f->IsOpen()==kFALSE)
  { std::cout << "!!! File Not Found !!!" << std::endl;
    exit(1); }
  sprintf(name, "efficiency/forYingjie_loosecut_pTrig/PurityforYingjie.root");
  if(doPuritySigmae)sprintf(name, "efficiency/forYingjie_tightcut_pTrig/PurityforYingjie.root");
  if(doPurityPoe)   sprintf(name, "efficiency/forYingjie_loosecut_pTrig/InEdNdpTAndPurityforYingjiePOESys.root");
  if(doPurityAdc0)  sprintf(name, "efficiency/forYingjie_loosecut_pTrig/InEdNdpTAndPurityforYingjieAdc0Sys.root");
  TFile *fpur = new TFile(name,"READ");
  
  // get PHE rec eff from root file
  sprintf(name, "efficiency/forYingjie_loosecut_pTrig_update/PHEReceffforYingjie.root");
  TFile *frec = new TFile(name,"READ");
  
  char fname[100];
  TFile* file;
  if(makeROOT){
    sprintf(fname,Form("FFOutput/npe_tree_%s_processed_%s.root", FileName, FileNameR));
    file = new TFile(fname,"RECREATE");
    if (file->IsOpen()==kFALSE)
    {
      std::cout << "!!! Outfile Not Opened !!!" << std::endl;
      makeROOT = kFALSE;
    }
  }
  
  const Int_t numPtBins = anaConst::nPtBins;
  Float_t lowpt[numPtBins],highpt[numPtBins];
  for(Int_t c=0; c< numPtBins; c++){
    lowpt[c] = anaConst::lpt[c];
    highpt[c] = anaConst::hpt[c];
  }
  Float_t hptCut=anaConst::hptCut;
  const Int_t numTrigs = 4;
  //  Double_t epsilon[numPtBins] = {0.593164, 0.626663, 0.655916, 0.674654, 0.685596, 0.700600, 0.716682, 0.724638, 0.713977, 0.730550, 0.735204, 0.744336, 0.761323, 0.758423};
  Float_t hptMax=anaConst::hptMax; // Set max above range to allow overflow
  Float_t lowPhi=anaConst::lowPhi, highPhi=anaConst::highPhi;
  Double_t pu[2]; // To store fit parameters for later use
  Double_t puE[2]; // To store fit parameter errors for later use
  Double_t hhNorm, HHScale, hadPur, inclNorm, USNorm, LSNorm;
  
  Double_t epsilon[numPtBins];
  Double_t epsilonPurity[numPtBins];
  
  // get purity from root file
  Float_t ptran[] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5};
  auto hpurt = new TH1F("hpurt", "", 9, ptran);
  auto hrect = new TH1F("hrect", "", 9, ptran);
  
  
  auto cpur = new TCanvas("cpur", "cpur", 150,0,1150,1000);
  auto hpur0 = (TH1F*)fpur->Get("hPurity_HT0");
  auto hpur2 = (TH1F*)fpur->Get("hPurity_HT2");
  auto hpur0Tmp = (TH1F*)hpur0->Clone("hPStat_HT0"); // save for stat. error
  auto hpur2Tmp = (TH1F*)hpur2->Clone("hPStat_HT2");
  
  if(doPurity || doMinusP){
    hpur0 = (TH1F*)fpur->Get("hPuritySys_HT0");
    hpur2 = (TH1F*)fpur->Get("hPuritySys_HT2");
  }
  for(auto i=0; i<numPtBins; i++){ // combine HT0 and HT2
    if(i<2) {
      if(doPurity) epsilonPurity[i] = hpur0->GetBinContent(i+1)+hpur0->GetBinError(i+1);
      else if(doMinusP) epsilonPurity[i] = hpur0->GetBinContent(i+1)-hpur0->GetBinError(i+1);
      else epsilonPurity[i] = hpur0->GetBinContent(i+1);
      hpurt->SetBinContent(i+1, epsilonPurity[i]);
      hpurt->SetBinError(i+1, hpur0Tmp->GetBinError(i+1));
    }
    else {
      if(doPurity) epsilonPurity[i] = hpur2->GetBinContent(i+1)+hpur2->GetBinError(i+1);
      else if(doMinusP) epsilonPurity[i] = hpur2->GetBinContent(i+1)-hpur2->GetBinError(i+1);
      else epsilonPurity[i] = hpur2->GetBinContent(i+1);
      hpurt->SetBinContent(i+1, epsilonPurity[i]);
      hpurt->SetBinError(i+1, hpur2Tmp->GetBinError(i+1));
    }
    cout<<"purity: "<<hpurt->GetBinContent(i+1)<<endl;;
  }
  hpurt->GetYaxis()->SetRangeUser(0, 1);
  hpurt->GetXaxis()->SetTitle("p_{T,e} GeV/c");
  hpurt->GetYaxis()->SetTitle("purity");
  hpurt->Fit("pol2","Q","",0.2,14);
  TF1* fitPurity = hpurt->GetFunction("pol2");
  
  auto crec = new TCanvas("crec", "crec", 150,0,1150,1000);
  auto hrec = (TH1F*)frec->Get("Receff");
  //  auto hrecTmp = hrec->Clone("PHEForError");
  if(doRecMass) hrec = (TH1F*)frec->Get("ReceffMassSys");
  //  if(doRecGpt) hrec = (TH1F*)frec->Get("ReceffGptSys"); // shenghui give me the wrong rec effi., the same 0.3 cut effi
  //  if(doRecGpt) hrec = (TH1F*)frec->Get("Receff");
  if(doRecGpt) hrec = (TH1F*)frec->Get("ReceffGpt02Sys");
  if(doRecGpt2) hrec = (TH1F*)frec->Get("ReceffGpt04Sys");
  if(doPurityPoe)hrec = (TH1F*)frec->Get("ReceffPOESys");
  
  for(auto i=0; i<9; i++){
    if(doRec) epsilon[i] = hrec->GetBinContent(i+1)+hrec->GetBinError(i+1);
    else if(doMinusR)epsilon[i] = hrec->GetBinContent(i+1)-hrec->GetBinError(i+1);
    else epsilon[i] = hrec->GetBinContent(i+1);
    hrect->SetBinContent(i+1, epsilon[i]);
    hrect->SetBinError(i+1, 1e-8);
  }
  
  
  TF1 *fitRec = new TF1("fitRec","[0]/(1.0 + TMath::Exp(-(x-[1])/[2])) + [3]",2.5,14);
  fitRec->SetParameters(1.1, 0.795, 1.022, -0.398);
  if(doRecMass){
    fitRec = new TF1("fitRec","[0]*(1.0 -TMath::Exp(-(x+[1])/[2]))",0,20);
    fitRec->SetParameters(0.8,9.37659e-02,4.40904e-01);
  }
  hrect->GetYaxis()->SetRangeUser(0, 1);
  hrect->GetXaxis()->SetTitle("P_{T,e} GeV/c");
  hrect->GetYaxis()->SetTitle("rec effi");
  hrect->SetMarkerSize(1.5);
  hrect->SetMarkerStyle(2);
  hrect->Fit("fitRec","RQ+","",2.5,14);
  
  //===================================================================================
  // beging analysis
  
  TH1F * hPurityTmp;
  TH1D * LSIM[numPtBins][numTrigs];
  TH1D * LSIMNP[numPtBins][numTrigs];
  
  TH1D * USIM[numPtBins][numTrigs];
  TH1D * ULIMNP[numPtBins][numTrigs];
  
  TH1D * INCL[numPtBins][numTrigs];
  TH1D * LSMM[numPtBins][numTrigs];
  TH1D * USMM[numPtBins][numTrigs];
  TH1D * HHDP[numPtBins][numTrigs];
  TH1D * NSPI[numPtBins][numTrigs];
  
  TH3F* mh3DelPhiInclWt[numTrigs];
  TH3F* mh3DelPhiPhotLSWt[numTrigs];
  TH3F* mh3DelPhiPhotUSWt[numTrigs];
  TH3F* mh3DelPhiPhotUSNP[numTrigs];
  TH3F* mh3DelPhiPhotLSNP[numTrigs];
  TH3F* mh3DelPhiHadHadWt[numTrigs];
  
  TH2F* mh2InvMassPtLS[numTrigs];
  TH2F* mh2InvMassPtUS[numTrigs];
  
  TH2F* mh2PtEZdcx[numTrigs];
  TH2F* mh2PtEZdcxUS[numTrigs];
  TH2F* mh2PtEZdcxLS[numTrigs];
  TH2F* mh2PtEZdcxHad[numTrigs];
  TH3F* mh3nTracksZdcx[numTrigs];
  TH3F* mh3nTracksZdcxUS[numTrigs];
  TH3F* mh3nTracksZdcxLS[numTrigs];
  TH3F* mh3nTracksZdcxHad[numTrigs];
  TH3F* mh3MixedDelPhi;
  TH3F* mh3MixedDelEta;
  TH3F* mh3MixedEtaPhi;
  TH3F* mh3MixedEtaPhiWt;
  TH2F* mh2nSigmaPion[numTrigs];
  
  TH1F* mh1PtHadTracks[numTrigs];
  TH1F* mh1PtETracks[numTrigs];
  
  
  TH1D* projDelPhiInclWt[numPtBins][numTrigs];
  TH1D* projDelPhiPhotLSWt[numPtBins][numTrigs];
  TH1D* projDelPhiPhotLSNP[numPtBins][numTrigs];
  TH1D* projDelPhiPhotUSNP[numPtBins][numTrigs];
  TH1D* projDelPhiPhotUSWt[numPtBins][numTrigs];
  TH1D* projDelPhiHadHadWt[numPtBins][numTrigs];
  
  TH1D* projTracksTrigUS[numPtBins][numTrigs];
  TH1D* projTracksTrigLS[numPtBins][numTrigs];
  TH1D* projInvMassLS[numPtBins][numTrigs];
  TH1D* projInvMassUS[numPtBins][numTrigs];
  TH1D* projnSigmaPion[numPtBins][numTrigs];
  TH1D* projEMixedEtaPhi;
  TH1D* projPMixedEtaPhi;
  TH1D* projPMixedEtaPhiWt;
  TH1D* mixedDelPhi;
  TH1D* mixedDelPhiWt;
  TH1D* mixedEventCorrection;
  TH2D* proj2DMixedEtaPhi;
  TH2D* proj2DMixedEvent[numPtBins];
  TH1D* projMixedDelPhi[numPtBins];
  TH1D* projMixedDelEta[numPtBins];
  TH1D* projMixedDelPhiWt[numPtBins];
  TH1D* mixedEventDelPhiCorrect[numPtBins];
  TH2F* histoNorms;
  TH1D* projZDCxHad[numPtBins][numTrigs];
  TH1D* projZDCxTrig[numPtBins][numTrigs];
  TH1D* projZDCxHadUS[numPtBins][numTrigs];
  TH1D* projZDCxTrigUS[numPtBins][numTrigs];
  TH1D* projZDCxHadLS[numPtBins][numTrigs];
  TH1D* projZDCxTrigLS[numPtBins][numTrigs];
  TH1D* projZDCxHadHad[numPtBins][numTrigs];
  TH1D* projZDCxTrigHad[numPtBins][numTrigs];
  TH1D* pileTrigs[numPtBins][numTrigs];
  TH1D* pileupCorrection[numPtBins][numTrigs];
  // 1D 2.5-3.5 GeV Check
  TH1F* mh1delPhiIncl;
  TH1F* mh1delPhiUS;
  TH1F* mh1delPhiLS;
  TH1F* mh1delPhiHad;
  TH1F* mh1TrigCount;
  TH1F* inclusivePU;
  TH1F* unlikePU;
  TH1F* likePU;
  TH1F* hadronPU;
  // For Comparison of Dists in different trigs
  TH1F* inclTrig[numPtBins][numTrigs];
  TH1F* npeTrig[numPtBins][numTrigs];
  TH1F* usTrig[numPtBins][numTrigs];
  TH1F* usTrigNP[numPtBins][numTrigs];
  TH1F* lsTrig[numPtBins][numTrigs];
  TH1F* lsTrigNP[numPtBins][numTrigs];
  TH1F* hadTrig[numPtBins][numTrigs];
  TH1F* usmlsTrig[numPtBins][numTrigs];
  
  TProfile2D* profileZDCx[numTrigs];
  TCanvas * c[numTrigs];
  TCanvas * IN[numTrigs];
  TCanvas * pile[numTrigs];
  TCanvas * pileC[numTrigs];
  TCanvas * pileHad[numTrigs];
  TCanvas * pileTrig[numTrigs];
  TCanvas * result[numTrigs];
  TCanvas * inMass[numTrigs];
  TCanvas * cHH[numTrigs];
  TCanvas * nSigPi[numTrigs];
  TCanvas * mixedC;
  TCanvas * mixedCbinEta;
  TCanvas * mixedCbinPhi;
  TCanvas * mixedCbin;
  TCanvas * mixedEventEff;
  TCanvas * singlePlot;
  
  TCanvas * usComp;
  TCanvas * usNPComp;
  TCanvas * lsComp;
  TCanvas * lsNPComp;
  TCanvas * usmlsComp;
  TCanvas * inclComp;
  
  
  TPaveText* lbl[numPtBins];
  TPaveText* pulbl[numPtBins];
  TPaveText* stat[numPtBins];
  char textLabel[100];
  
  singlePlot =  new TCanvas("singlePlot","Single Plot",150,0,1150,1000);
  auto fitSlope = new TCanvas("mixedC","Mixed Events",150,0,1150,1000);
  
  /// Mixed Event
  mixedC     = new TCanvas("mixedC","Mixed Events",150,0,1150,1000);
  mixedCbinEta = new TCanvas("mixedCbinEta","Mixed Events Eta",150,0,1150,1000);
  mixedCbinPhi = new TCanvas("mixedCbinPhi","Mixed Events Phi",150,0,1150,1000);
  mixedCbin = new TCanvas("mixedCbin","Mixed Events 2D",150,0,1150,1000);
  mixedEventEff = new TCanvas("mixedEventEff","Mixed Event Efficiency Correct",150,0,1150,1000);
  
  usComp     = new TCanvas("usComp","usComp",150,0,1150,1000);
  usNPComp     = new TCanvas("usNPComp","usNPComp",150,0,1150,1000);
  lsComp     = new TCanvas("lsComp","lsComp",150,0,1150,1000);
  lsNPComp     = new TCanvas("lsNPComp","lsNPComp",150,0,1150,1000);
  
  usmlsComp     = new TCanvas("usmlsComp","usmlsComp",150,0,1150,1000);
  inclComp = new TCanvas("inclComp","inclComp",150,0,1150,1000);
  
  mixedC       -> Divide(2,2);
  mixedCbinEta -> Divide(3,3);
  mixedCbinPhi -> Divide(3,3);
  mixedEventEff -> Divide(3,3);
  usComp->Divide(3,2);
  usNPComp->Divide(3,2);
  lsComp->Divide(3,2);
  lsNPComp->Divide(3,2);
  
  usmlsComp->Divide(3,2);
  inclComp->Divide(3,2);
  
  //===================================================================================
  
  mh3MixedDelPhi = (TH3F*)f->Get("mh3MixedDelPhi");
  mh3MixedDelEta = (TH3F*)f->Get("mh3MixedDelEta");
  mh3MixedEtaPhi = (TH3F*)f->Get("mh3MixedEtaPhi");
  mh3MixedEtaPhiWt = (TH3F*)f->Get("mh3MixedEtaPhiWt");
  
  projPMixedEtaPhi  = mh3MixedEtaPhi -> ProjectionX("projPMixedEtaPhi");
  projEMixedEtaPhi  = mh3MixedEtaPhi -> ProjectionY("projEMixedEtaPhi");
  proj2DMixedEtaPhi = (TH2D*)mh3MixedEtaPhi -> Project3D("yx");
  Int_t RB2 = 2;
  projEMixedEtaPhi->Rebin(RB2);
  projPMixedEtaPhi->Rebin(RB2);
  
  mixedC->cd(4);
  mixedC->SetLogz(1);
  proj2DMixedEtaPhi->GetXaxis()->SetTitle("#Delta#phi");
  proj2DMixedEtaPhi->GetXaxis()->SetRangeUser(lowPhi,highPhi);
  proj2DMixedEtaPhi->GetYaxis()->SetTitle("#Delta#eta");
  proj2DMixedEtaPhi->GetYaxis()->SetRangeUser(-1.5,1.5);
  proj2DMixedEtaPhi->Draw("colz");
  
  mixedDelPhi = mh3MixedEtaPhi->ProjectionX("mixedDelPhi",0,-1,0,-1); // project all Mixed Event pt regions to delPhi
  mixedDelPhiWt = mh3MixedEtaPhiWt->ProjectionX("mixedDelPhiWt",0,-1,0,-1); // project all Mixed Event pt regions to delPhi
  mixedDelPhi->Sumw2();mixedDelPhiWt->Sumw2();
  mixedDelPhi->Rebin(2);mixedDelPhiWt->Rebin(2);
  mixedEventCorrection = (TH1D*)mixedDelPhi->Clone();
  mixedEventCorrection->SetName("mixedEventCorrection");
  mixedEventCorrection->Divide(mixedDelPhiWt);
  mixedEventCorrection->SetTitle("");
  mixedC->cd(1);
  mixedDelPhiWt->GetXaxis()->SetRangeUser(lowPhi,highPhi);
  mixedDelPhiWt->GetXaxis()->SetTitle("#Delta#phi");
  mixedDelPhiWt->GetYaxis()->SetTitle("Counts");
  mixedDelPhiWt->GetYaxis()->SetRangeUser(0,20000);
  mixedDelPhiWt->SetTitle("Mixed Event #Delta#phi, w/o efficiency as a weight");
  mixedDelPhiWt->Draw();
  mixedC->cd(2);
  mixedDelPhi->GetXaxis()->SetRangeUser(lowPhi,highPhi);
  mixedDelPhi->GetXaxis()->SetTitle("#Delta#phi");
  mixedDelPhi->GetYaxis()->SetTitle("Counts");
  mixedDelPhi->GetYaxis()->SetRangeUser(0,20000);
  mixedDelPhi->SetTitle("Mixed Event #Delta#phi, w/ efficiency as a weight");
  mixedDelPhi->Draw();
  mixedC->cd(3);
  mixedEventCorrection->SetTitle("Ratio of unweighted:weighted");
  mixedEventCorrection->GetXaxis()->SetTitle("#Delta#phi");
  mixedEventCorrection->GetXaxis()->SetRangeUser(lowPhi,highPhi);
  mixedEventCorrection->GetYaxis()->SetTitle("Efficiency");
  mixedEventCorrection->GetYaxis()->SetRangeUser(0.2,1.4);
  mixedEventCorrection->Draw("");
  
  TH3F* temp3D[numPtBins];
  // PtBins for Mixed Event
  for(Int_t ptbin = 0; ptbin < numPtBins; ptbin++){
    
    // Init necessary plotting tools
    lbl[ptbin] = new TPaveText(.2,.8,.5,.85,Form("NB NDC%i",ptbin));
    sprintf(textLabel,"%.1f < P_{T,e} < %.1f",lowpt[ptbin],highpt[ptbin]);
    lbl[ptbin]->AddText(textLabel);
    lbl[ptbin]->SetFillColor(kWhite);
    
    projMixedDelPhi[ptbin] = mh3MixedEtaPhi->ProjectionX(Form("projMixedDelPhi_%i",ptbin),0,-1,mh3MixedEtaPhi->GetZaxis()->FindBin(lowpt[ptbin]),mh3MixedEtaPhi->GetZaxis()->FindBin(highpt[ptbin])-1);
    projMixedDelPhiWt[ptbin] = mh3MixedEtaPhiWt->ProjectionX(Form("projMixedDelPhiWt_%i",ptbin),0,-1,mh3MixedEtaPhiWt->GetZaxis()->FindBin(lowpt[ptbin]),mh3MixedEtaPhiWt->GetZaxis()->FindBin(highpt[ptbin])-1);
    projMixedDelEta[ptbin] = mh3MixedEtaPhi->ProjectionY(Form("projMixedDelEta_%i",ptbin),0,-1,mh3MixedEtaPhi->GetZaxis()->FindBin(lowpt[ptbin]),mh3MixedEtaPhi->GetZaxis()->FindBin(highpt[ptbin])-1);
    
    projMixedDelPhi[ptbin]->Rebin(2);
    projMixedDelPhiWt[ptbin]->Rebin(2);
    mixedEventDelPhiCorrect[ptbin] = (TH1D*)projMixedDelPhi[ptbin]->Clone();
    mixedEventDelPhiCorrect[ptbin]->SetName(Form("delPhiCorrection_%i",ptbin));
    mixedEventDelPhiCorrect[ptbin] -> Divide(projMixedDelPhiWt[ptbin]); // This calculates the delta phi correction by doing unweighted/weighted
    
    mixedEventEff->cd(ptbin+1);
    mixedEventDelPhiCorrect[ptbin]->GetYaxis()->SetRangeUser(0,1);
    mixedEventDelPhiCorrect[ptbin]->GetXaxis()->SetRangeUser(lowPhi,highPhi);
    //mixedEventDelPhiCorrect[ptbin]->Rebin(2); // Rebin to use in delPhi division
    mixedEventDelPhiCorrect[ptbin]->Draw();
    
    mixedCbinEta->cd(ptbin+1);
    projMixedDelEta[ptbin]->GetXaxis()->SetRangeUser(-2.5,2.5);
    projMixedDelEta[ptbin]->GetXaxis()->SetTitle("#Delta#eta");
    projMixedDelEta[ptbin]->Draw();
    
    mixedCbinPhi->cd(ptbin+1);
    projMixedDelPhi[ptbin]->GetXaxis()->SetRangeUser(lowPhi-.5,highPhi+.5);
    // projMixedDelPhi[ptbin]->GetYaxis()->SetRangeUser(0,2000);
    projMixedDelPhi[ptbin]->GetXaxis()->SetTitle("#Delta#phi");
    projMixedDelPhi[ptbin]->Draw();
    
  }
  
  //===================================================================================
  
  /// TRIGGER LOOP
  histoNorms = new TH2F("histoNorms","",4,0,12,20,0,20); // Fill normalization in a single histogram for accessing later
  
  const int num=10;
  const char *slopeName[num] = {"NPE 0", "SemiInc 0", "US 0", "LS 0", "Had 0", "NPE 2", "SemiInc 2", "US 2", "LS 2", "Had 2"};
  auto fs = new TH1F("fs", "", num, 0, num);  // Fill pile slope for later comp.
  fs->SetTitle("pileup fits, parameter 1");
  fs->SetCanExtend(TH1::kAllAxes);
  fs->LabelsDeflate();
  fs->SetMarkerStyle(20);
  //  fs->SetMarkerSize(0.4);
  
  for(Int_t trig = 0; trig < numTrigs; trig++){
    
    if(!fPaintAll && (trig == 1 || trig == 3)) continue;
    // Create and Segment Canvas
    c[trig]        = new TCanvas(Form("c%i",trig),"Photonic Hists",150,0,1150,1000);
    IN[trig]       = new TCanvas(Form("IN%i",trig),"Inclusive Hists",150,0,1150,1000);
    pile[trig]     = new TCanvas(Form("pile%i",trig),"Pileup Monitor",150,0,1150,1000);
    pileC[trig]     = new TCanvas(Form("pileC%i",trig),"Pileup Correction Monitor",150,0,1150,1000);
    pileHad[trig]  = new TCanvas(Form("pileHad%i",trig),"Pileup Hadron per Event",150,0,1150,1000);
    pileTrig[trig] = new TCanvas(Form("pileTrig%i",trig),"Pileup Trigger per Event",150,0,1150,1000);
    inMass[trig]   = new TCanvas(Form("inMass%i",trig),"Invariant Mass",150,0,1150,1000);
    result[trig]   = new TCanvas(Form("result%i",trig),"Inclusive - Photonic",150,0,1150,1000);
    cHH[trig]      = new TCanvas(Form("cHH%i",trig),"Hadron-Hadron Distributions",150,0,1150,1000);
    nSigPi[trig]   = new TCanvas(Form("nSigPi_%i",trig),"n#sigma#pi QA",150,0,1150,1000);
    
    c[trig]        -> Divide(3,3);
    inMass[trig]   -> Divide(3,3);
    IN[trig]       -> Divide(3,3);
    result[trig]   -> Divide(3,3);
    cHH[trig]      -> Divide(3,3);
    nSigPi[trig]   -> Divide(3,3);
    
    
    // Pileup Calculation (using just the hPtCut in the anaConst.h), Done here since need fit results in deltaPhi
    mh3nTracksZdcx[trig]    = (TH3F*)f->Get(Form("mh3nTracksZdcx_%i_%i",trig,0));   // originally filled for various hpT cuts, use 0 which starts at hpt > 0.3
    mh3nTracksZdcxUS[trig]  = (TH3F*)f->Get(Form("mh3nTracksZdcxUS_%i_%i",trig,0)); // These histos are (epT,hpT,ZDCx), get nHadrons vs ZDCx
    mh3nTracksZdcxLS[trig]  = (TH3F*)f->Get(Form("mh3nTracksZdcxLS_%i_%i",trig,0));
    mh3nTracksZdcxHad[trig] = (TH3F*)f->Get(Form("mh3nTracksZdcxHad_%i_%i",trig,0));
    mh3nTracksZdcx[trig]->Sumw2(); mh3nTracksZdcxUS[trig]->Sumw2(); mh3nTracksZdcxLS[trig]->Sumw2();  mh3nTracksZdcxHad[trig]->Sumw2();
    
    mh2PtEZdcx[trig]       = (TH2F*)f->Get(Form("mh2PtEZdcx_%i",trig));            // Filled (epT,ZDCx). Get nTrigs vs ZDCx
    mh2PtEZdcxUS[trig]     = (TH2F*)f->Get(Form("mh2PtEZdcxUS_%i",trig));
    mh2PtEZdcxLS[trig]     = (TH2F*)f->Get(Form("mh2PtEZdcxLS_%i",trig));
    mh2PtEZdcxHad[trig]     = (TH2F*)f->Get(Form("mh2PtEZdcxHad_%i",trig));
    mh2PtEZdcx[trig]->Sumw2(); mh2PtEZdcxUS[trig]->Sumw2(); mh2PtEZdcxLS[trig]->Sumw2(); mh2PtEZdcxHad[trig]->Sumw2();
    
    mh2InvMassPtLS[trig]    = (TH2F*)f->Get(Form("mh2InvMassPtLS_%i",trig));
    mh2InvMassPtUS[trig]    = (TH2F*)f->Get(Form("mh2InvMassPtUS_%i",trig));
    
    mh1PtHadTracks[trig]    = (TH1F*)f->Get(Form("mh1PtHadTracks_%i",trig));
    mh1PtETracks[trig]      = (TH1F*)f->Get(Form("mh1PtETracks_%i",trig));
    mh2nSigmaPion[trig]     = (TH2F*)f->Get(Form("mh2nSigmaPionPt_%i",trig));
    
    Double_t pulowpt[4]  = {2.5,4,6,8};
    Double_t puhighpt[4] = {20,6,8,20};
    if(trig == 0){pulowpt[0]=2.5; puhighpt[0]=10.4;}
    if(trig == 2){pulowpt[0]=4.5; puhighpt[0]=10.4;}
    //===================================================================================
    // get pile slope, for pile correction
    
    for(Int_t ptbin=0; ptbin<1; ptbin++)// cut in to trigger pt slices
    {
      projZDCxHad[ptbin][trig] = mh3nTracksZdcx[trig]->ProjectionZ(Form("projZDCxHad_%i_%i",ptbin,trig),mh3nTracksZdcx[trig]->GetXaxis()->FindBin(pulowpt[ptbin]),mh3nTracksZdcx[trig]->GetXaxis()->FindBin(puhighpt[ptbin])-1,mh3nTracksZdcx[trig]->GetYaxis()->FindBin(hptCut),mh3nTracksZdcx[trig]->GetYaxis()->FindBin(hptMax));
      projZDCxHadUS[ptbin][trig] = mh3nTracksZdcxUS[trig]->ProjectionZ(Form("projZDCxHadUS_%i_%i",ptbin,trig),mh3nTracksZdcxUS[trig]->GetXaxis()->FindBin(pulowpt[ptbin]),mh3nTracksZdcxUS[trig]->GetXaxis()->FindBin(puhighpt[ptbin])-1,mh3nTracksZdcxUS[trig]->GetYaxis()->FindBin(hptCut),mh3nTracksZdcxUS[trig]->GetYaxis()->FindBin(hptMax));
      projZDCxHadLS[ptbin][trig] = mh3nTracksZdcxLS[trig]->ProjectionZ(Form("projZDCxHadLS_%i_%i",ptbin,trig),mh3nTracksZdcxLS[trig]->GetXaxis()->FindBin(pulowpt[ptbin]),mh3nTracksZdcxLS[trig]->GetXaxis()->FindBin(puhighpt[ptbin])-1,mh3nTracksZdcxLS[trig]->GetYaxis()->FindBin(hptCut),mh3nTracksZdcxLS[trig]->GetYaxis()->FindBin(hptMax));
      projZDCxHadHad[ptbin][trig] = mh3nTracksZdcxHad[trig]->ProjectionZ(Form("projZDCxHadHad_%i_%i",ptbin,trig),mh3nTracksZdcxHad[trig]->GetXaxis()->FindBin(pulowpt[ptbin]),mh3nTracksZdcxHad[trig]->GetXaxis()->FindBin(puhighpt[ptbin])-1,mh3nTracksZdcxHad[trig]->GetYaxis()->FindBin(hptCut),mh3nTracksZdcxHad[trig]->GetYaxis()->FindBin(hptMax));
      
      projZDCxTrig[ptbin][trig] = mh2PtEZdcx[trig]->ProjectionY(Form("projZDCxTrig_%i_%i",ptbin,trig),mh2PtEZdcx[trig]->GetXaxis()->FindBin(pulowpt[ptbin]),mh2PtEZdcx[trig]->GetXaxis()->FindBin(puhighpt[ptbin])-1);
      projZDCxTrigUS[ptbin][trig] = mh2PtEZdcxUS[trig]->ProjectionY(Form("projZDCxTrigUS_%i_%i",ptbin,trig),mh2PtEZdcxUS[trig]->GetXaxis()->FindBin(pulowpt[ptbin]),mh2PtEZdcxUS[trig]->GetXaxis()->FindBin(puhighpt[ptbin])-1);
      projZDCxTrigLS[ptbin][trig] = mh2PtEZdcxLS[trig]->ProjectionY(Form("projZDCxTrigLS_%i_%i",ptbin,trig),mh2PtEZdcxLS[trig]->GetXaxis()->FindBin(pulowpt[ptbin]),mh2PtEZdcxLS[trig]->GetXaxis()->FindBin(puhighpt[ptbin])-1);
      projZDCxTrigHad[ptbin][trig] = mh2PtEZdcxHad[trig]->ProjectionY(Form("projZDCxTrigHad_%i_%i",ptbin,trig),mh2PtEZdcxHad[trig]->GetXaxis()->FindBin(pulowpt[ptbin]),mh2PtEZdcxHad[trig]->GetXaxis()->FindBin(puhighpt[ptbin])-1);
      
      // Rebin to make the statistics better
      Int_t RBpu = 5;
      projZDCxHad[ptbin][trig]     -> Rebin(RBpu);
      projZDCxHadUS[ptbin][trig]   -> Rebin(RBpu);
      projZDCxHadLS[ptbin][trig]   -> Rebin(RBpu);
      projZDCxHadHad[ptbin][trig]  -> Rebin(RBpu);
      projZDCxTrig[ptbin][trig]    -> Rebin(RBpu);
      projZDCxTrigUS[ptbin][trig]  -> Rebin(RBpu);
      projZDCxTrigLS[ptbin][trig]  -> Rebin(RBpu);
      projZDCxTrigHad[ptbin][trig] -> Rebin(RBpu);
      
      pulbl[ptbin] = new TPaveText(.15,.15,.35,.23,Form("NB NDC%i",ptbin));
      sprintf(textLabel,"%.1f < P_{T,e} < %.1f",pulowpt[ptbin],puhighpt[ptbin]);
      pulbl[ptbin]->AddText(textLabel);
      pulbl[ptbin]->SetFillColor(kWhite);
      
      // Make plots for each subset
      inclusivePU = (TH1F*)projZDCxHad[ptbin][trig]->Clone(); inclusivePU->Divide(projZDCxTrig[ptbin][trig]);
      inclusivePU->SetName(Form("inclusivePU_%i",trig));
      unlikePU = (TH1F*)projZDCxHadUS[ptbin][trig]->Clone(); unlikePU->Divide(projZDCxTrigUS[ptbin][trig]);
      unlikePU->SetName(Form("unlikePU_%i",trig));
      likePU = (TH1F*)projZDCxHadLS[ptbin][trig]->Clone(); likePU->Divide(projZDCxTrigLS[ptbin][trig]);
      likePU->SetName(Form("likePU_%i",trig));
      hadronPU = (TH1F*)projZDCxHadHad[ptbin][trig]->Clone(); hadronPU->Divide(projZDCxTrigHad[ptbin][trig]);
      hadronPU->SetName(Form("hadronPU_%i",trig));
      inclusivePU->SetLineColor(kMagenta);
      unlikePU->SetLineColor(kRed);
      likePU->SetLineColor(kBlue);
      hadronPU->SetLineColor(kGreen+3);
      inclusivePU->SetMarkerColor(kMagenta);
      unlikePU->SetMarkerColor(kRed);
      likePU->SetMarkerColor(kBlue);
      hadronPU->SetMarkerColor(kGreen+3);
      inclusivePU->SetMarkerStyle(20);
      unlikePU->SetMarkerStyle(21);
      likePU->SetMarkerStyle(22);
      hadronPU->SetMarkerStyle(23);
      
      // Draw
      pileHad[trig]->cd();
      gPad->SetLeftMargin(0.12);
      projZDCxHad[ptbin][trig]->SetLineColor(kBlack);
      projZDCxHadUS[ptbin][trig]->SetLineColor(kRed);
      projZDCxHadLS[ptbin][trig]->SetLineColor(kBlue);
      projZDCxHadHad[ptbin][trig]->SetLineColor(kGreen+3);
      projZDCxTrig[ptbin][trig]->SetLineColor(kBlack);
      projZDCxTrigUS[ptbin][trig]->SetLineColor(kRed);
      projZDCxTrigLS[ptbin][trig]->SetLineColor(kBlue);
      projZDCxTrigHad[ptbin][trig]->SetLineColor(kGreen+3);
      TLegend* legPU = new TLegend(0.45,0.6,0.85,0.79);
      legPU->AddEntry(projZDCxHad[ptbin][trig],"Semi-Inclusive Trigs","lpe");
      legPU->AddEntry(projZDCxHadUS[ptbin][trig],"Unlike Sign Trigs","lpe");
      legPU->AddEntry(projZDCxHadLS[ptbin][trig],"Like Sign Trigs","lpe");
      legPU->AddEntry(projZDCxHadHad[ptbin][trig],"Hadron-Hadron Trigs","lpe");
      projZDCxHad[ptbin][trig]->GetYaxis()->SetTitle("<nHadrons>");
      projZDCxHad[ptbin][trig]->GetXaxis()->SetTitle("ZDCx");
      projZDCxHad[ptbin][trig]->SetTitle("");
      projZDCxHad[ptbin][trig] -> DrawCopy();
      projZDCxHadUS[ptbin][trig] -> DrawCopy("same");
      projZDCxHadLS[ptbin][trig] -> DrawCopy("same");
      projZDCxHadHad[ptbin][trig] -> DrawCopy("same");
      legPU->Draw("same");
      pulbl[ptbin]->Draw("same");
      
      pileTrig[trig]->cd();
      gPad->SetLeftMargin(0.12);
      projZDCxTrig[ptbin][trig]->GetYaxis()->SetTitle("<nTriggers>");
      projZDCxTrig[ptbin][trig]->GetXaxis()->SetTitle("ZDCx");
      projZDCxTrig[ptbin][trig] ->SetTitle("");
      projZDCxTrig[ptbin][trig] -> DrawCopy();
      projZDCxTrigUS[ptbin][trig] -> DrawCopy("same");
      projZDCxTrigLS[ptbin][trig] -> DrawCopy("same");
      projZDCxTrigHad[ptbin][trig] -> DrawCopy("same");
      legPU->Draw("same");
      pulbl[ptbin]->Draw("same");
      
      Float_t xCom = (pulowpt[ptbin]+puhighpt[ptbin])/2.0;
      //      Double_t epsCom = effPar[0]*(1.0 -TMath::Exp(-(xCom+effPar[1])/effPar[2]));
      Double_t epsCom = fitRec->Eval(xCom);
      Float_t pur = fitPurity->Eval(xCom);
      //      Float_t pur = purPar[0] + (purPar[1]*xCom)+(purPar[2]*xCom*xCom);
      
      projZDCxHad[ptbin][trig] -> Add(projZDCxHadUS[ptbin][trig], 1);
      projZDCxHad[ptbin][trig] -> Scale(pur);
      projZDCxHadUS[ptbin][trig] -> Add(projZDCxHadLS[ptbin][trig], -1.);
      projZDCxHadUS[ptbin][trig] -> Scale(1./epsCom);
      projZDCxHad[ptbin][trig] -> Add(projZDCxHadUS[ptbin][trig], -1.);
      
      projZDCxTrig[ptbin][trig] -> Add(projZDCxTrigUS[ptbin][trig], 1);
      projZDCxTrig[ptbin][trig] -> Scale(pur);
      projZDCxTrigUS[ptbin][trig] -> Add(projZDCxTrigLS[ptbin][trig], -1.);
      projZDCxTrigUS[ptbin][trig] -> Scale(1./epsCom);
      projZDCxTrig[ptbin][trig] -> Add(projZDCxTrigUS[ptbin][trig], -1.);
      
      // Actually do the division of total hadrons/total trigs
      projZDCxHad[ptbin][trig]->Divide(projZDCxTrig[ptbin][trig]);
      
      // plot projections
      pile[trig]->cd();
      projZDCxHad[ptbin][trig]->SetLineColor(kBlack);
      projZDCxHad[ptbin][trig]->SetMarkerStyle(25);
      projZDCxHad[ptbin][trig]->GetXaxis()->SetTitle("ZDCx");
      projZDCxHad[ptbin][trig]->GetYaxis()->SetTitle("<nHadrons>/<nTrigs>");
      projZDCxHad[ptbin][trig]->GetYaxis()->SetRangeUser(0,20);
      //
      gStyle->SetOptFit(1111);
      projZDCxHad[ptbin][trig]->Fit("pol1","Q");
      projZDCxHad[ptbin][trig]->GetFunction("pol1")->SetLineColor(kBlack);
      TPaveStats *st = ((TPaveStats*)(projZDCxHad[ptbin][trig]->GetListOfFunctions()->FindObject("stats")));
      if (st) {
        st->SetTextColor(projZDCxHad[ptbin][trig]->GetFunction("pol1")->GetLineColor());
        st->SetX1NDC(0.64); st->SetX2NDC(0.99);
        st->SetY1NDC(0.4); st->SetY2NDC(0.6);
      }
      pile[trig]->Modified();pile[trig]->Update();
      projZDCxHad[ptbin][trig]->Draw("");
      pulbl[ptbin]->Draw("same");
      
      // Draw for each Dist
      inclusivePU ->Draw("same");
      unlikePU    ->Draw("same");
      likePU      ->Draw("same");
      hadronPU    ->Draw("same");
      
      TLegend* pileupLeg = new TLegend(0.2,0.73,0.55,0.85);
      pileupLeg->AddEntry(projZDCxHad[ptbin][trig],"NPE","lpe");
      pileupLeg->AddEntry(inclusivePU,"Semi-Inclusive","lpe");
      pileupLeg->AddEntry(unlikePU,"Unlike Sign","lpe");
      pileupLeg->AddEntry(likePU,"Like Sign","lpe");
      pileupLeg->AddEntry(hadronPU,"Hadron","lpe");
      pileupLeg->Draw("same");
      
      TF1 *fitResult = projZDCxHad[ptbin][trig]->GetFunction("pol1");
      
      inclusivePU->Fit("pol1","Q");
      TF1* inclusiveFIT = inclusivePU->GetFunction("pol1");
      unlikePU->Fit("pol1","Q");
      TF1* unlikeFIT = unlikePU->GetFunction("pol1");
      likePU->Fit("pol1","Q");
      TF1* likeFIT = likePU->GetFunction("pol1");
      hadronPU->Fit("pol1","Q");
      TF1* hadronFIT = hadronPU->GetFunction("pol1");
      inclusiveFIT->SetLineColor(kMagenta);
      unlikeFIT->SetLineColor(kRed);
      likeFIT->SetLineColor(kBlue);
      hadronFIT->SetLineColor(kGreen+3);
      
      // Get Fit information and store to use in corrections
      pu[0] = hadronFIT->GetParameter(0);
      pu[1] = hadronFIT->GetParameter(1);
      puE[0] = hadronFIT->GetParError(0);
      puE[1] = hadronFIT->GetParError(1);
      //      pu[0] = fitResult->GetParameter(0);
      //      pu[1] = fitResult->GetParameter(1);
      //      puE[0] = fitResult->GetParError(0);
      //      puE[1] = fitResult->GetParError(1);
      cout << "pu1: " << pu[1] << " puE[1]: " << puE[1] << endl;
      
      if(trig == 0){
        fs->Fill(slopeName[0], fitResult->GetParameter(1));
        fs->SetBinError(1,fitResult->GetParError(1));
        fs->Fill(slopeName[1], inclusiveFIT->GetParameter(1));
        fs->SetBinError(2,inclusiveFIT->GetParError(1));
        fs->Fill(slopeName[2], unlikeFIT->GetParameter(1));
        fs->SetBinError(3,unlikeFIT->GetParError(1));
        fs->Fill(slopeName[3], likeFIT->GetParameter(1));
        fs->SetBinError(4,likeFIT->GetParError(1));
        fs->Fill(slopeName[4], hadronFIT->GetParameter(1));
        fs->SetBinError(5,hadronFIT->GetParError(1));
      }
      else{
        fs->Fill(slopeName[5], fitResult->GetParameter(1));
        fs->SetBinError(6,fitResult->GetParError(1));
        fs->Fill(slopeName[6], inclusiveFIT->GetParameter(1));
        fs->SetBinError(7,inclusiveFIT->GetParError(1));
        fs->Fill(slopeName[7], unlikeFIT->GetParameter(1));
        fs->SetBinError(8,unlikeFIT->GetParError(1));
        fs->Fill(slopeName[8], likeFIT->GetParameter(1));
        fs->SetBinError(9,likeFIT->GetParError(1));
        fs->Fill(slopeName[9], hadronFIT->GetParameter(1));
        fs->SetBinError(10,hadronFIT->GetParError(1));
      }
      
    }
    
    // Make Projections (first get 2d/3d hists, then project)
    //===================================================================================
    
    mh3DelPhiInclWt[trig]   = (TH3F*)f->Get(Form("mh3DelPhiInclWt_%i",trig));
    mh3DelPhiHadHadWt[trig]   = (TH3F*)f->Get(Form("mh3DelPhiHadHadWt_%i",trig));
    
    mh3DelPhiPhotLSWt[trig] = (TH3F*)f->Get(Form("mh3DelPhiPhotLSWt_%i",trig));
    mh3DelPhiPhotUSNP[trig] = (TH3F*)f->Get(Form("mh3DelPhiPhotUSNP_%i",trig));
    
    mh3DelPhiPhotUSWt[trig] = (TH3F*)f->Get(Form("mh3DelPhiPhotUSWt_%i",trig));
    mh3DelPhiPhotLSNP[trig] = (TH3F*)f->Get(Form("mh3DelPhiPhotLSNP_%i",trig));
    
    
    //===================================================================
    // read histo.
    for(Int_t ptbin=0; ptbin<numPtBins; ptbin++)
    {
      // - Make projections into electron ptbins
      projDelPhiInclWt[ptbin][trig] = mh3DelPhiInclWt[trig]->ProjectionX(Form("projDelPhiInclWt_%i_%i",ptbin,trig),mh3DelPhiInclWt[trig]->GetYaxis()->FindBin(lowpt[ptbin]),mh3DelPhiInclWt[trig]->GetYaxis()->FindBin(highpt[ptbin])-1,mh3DelPhiInclWt[trig]->GetZaxis()->FindBin(hptCut),mh3DelPhiInclWt[trig]->GetZaxis()->FindBin(hptMax));
      
      projDelPhiPhotUSWt[ptbin][trig] = mh3DelPhiPhotUSWt[trig]->ProjectionX(Form("projDelPhiPhotUSWt_%i_%i",ptbin,trig),mh3DelPhiPhotUSWt[trig]->GetYaxis()->FindBin(lowpt[ptbin]),mh3DelPhiPhotUSWt[trig]->GetYaxis()->FindBin(highpt[ptbin])-1,mh3DelPhiPhotUSWt[trig]->GetZaxis()->FindBin(hptCut),mh3DelPhiPhotUSWt[trig]->GetZaxis()->FindBin(hptMax));
      
      projDelPhiPhotLSWt[ptbin][trig] = mh3DelPhiPhotLSWt[trig]->ProjectionX(Form("projDelPhiPhotLSWt_%i_%i",ptbin,trig),mh3DelPhiPhotLSWt[trig]->GetYaxis()->FindBin(lowpt[ptbin]),mh3DelPhiPhotLSWt[trig]->GetYaxis()->FindBin(highpt[ptbin])-1,mh3DelPhiPhotLSWt[trig]->GetZaxis()->FindBin(hptCut),mh3DelPhiPhotLSWt[trig]->GetZaxis()->FindBin(hptMax));
      
      projDelPhiPhotLSNP[ptbin][trig] = mh3DelPhiPhotLSNP[trig]->ProjectionX(Form("projDelPhiPhotLSNP_%i_%i",ptbin,trig),mh3DelPhiPhotLSNP[trig]->GetYaxis()->FindBin(lowpt[ptbin]),mh3DelPhiPhotLSNP[trig]->GetYaxis()->FindBin(highpt[ptbin])-1,mh3DelPhiPhotLSNP[trig]->GetZaxis()->FindBin(hptCut),mh3DelPhiPhotLSNP[trig]->GetZaxis()->FindBin(hptMax));
      
      projDelPhiPhotUSNP[ptbin][trig] = mh3DelPhiPhotUSNP[trig]->ProjectionX(Form("projDelPhiPhotUSNP_%i_%i",ptbin,trig),mh3DelPhiPhotUSNP[trig]->GetYaxis()->FindBin(lowpt[ptbin]),mh3DelPhiPhotUSNP[trig]->GetYaxis()->FindBin(highpt[ptbin])-1,mh3DelPhiPhotUSNP[trig]->GetZaxis()->FindBin(hptCut),mh3DelPhiPhotUSNP[trig]->GetZaxis()->FindBin(hptMax));
      
      
      projInvMassUS[ptbin][trig] = mh2InvMassPtUS[trig]->ProjectionX(Form("projInvMassUS_%i_%i",ptbin,trig),mh2InvMassPtUS[trig]->GetYaxis()->FindBin(lowpt[ptbin]),mh2InvMassPtUS[trig]->GetYaxis()->FindBin(highpt[ptbin])-1);
      
      projInvMassLS[ptbin][trig] = mh2InvMassPtLS[trig]->ProjectionX(Form("projInvMassLS_%i_%i",ptbin,trig),mh2InvMassPtLS[trig]->GetYaxis()->FindBin(lowpt[ptbin]),mh2InvMassPtLS[trig]->GetYaxis()->FindBin(highpt[ptbin])-1);
      
      projTracksTrigUS[ptbin][trig] = mh2PtEZdcxUS[trig]->ProjectionY(Form("projTracksTrigUS_%i_%i",ptbin,trig),mh2PtEZdcxUS[trig]->GetXaxis()->FindBin(lowpt[ptbin]),mh2PtEZdcxUS[trig]->GetXaxis()->FindBin(highpt[ptbin])-1);
      projTracksTrigLS[ptbin][trig] = mh2PtEZdcxLS[trig]->ProjectionY(Form("projTracksTrigLS_%i_%i",ptbin,trig),mh2PtEZdcxLS[trig]->GetXaxis()->FindBin(lowpt[ptbin]),mh2PtEZdcxLS[trig]->GetXaxis()->FindBin(highpt[ptbin])-1);
      
      projDelPhiHadHadWt[ptbin][trig] = mh3DelPhiHadHadWt[trig]->ProjectionX(Form("projDelPhiHadHadWt_%i_%i",ptbin,trig),mh3DelPhiHadHadWt[trig]->GetYaxis()->FindBin(lowpt[ptbin]),mh3DelPhiHadHadWt[trig]->GetYaxis()->FindBin(highpt[ptbin])-1,mh3DelPhiHadHadWt[trig]->GetZaxis()->FindBin(hptCut),mh3DelPhiHadHadWt[trig]->GetZaxis()->FindBin(hptMax));
      
      
      projnSigmaPion[ptbin][trig] = mh2nSigmaPion[trig]->ProjectionX(Form("projnSigmaPion_%i_%i",ptbin,trig),mh2nSigmaPion[trig]->GetYaxis()->FindBin(lowpt[ptbin]),mh2nSigmaPion[trig]->GetYaxis()->FindBin(highpt[ptbin])-1);
      
      //for pileup correction (need nTrigs per ZDC per ptbin)
      projZDCxTrig[ptbin][trig] = mh2PtEZdcx[trig]->ProjectionY(Form("projZDCxTrig_%i_%i",ptbin,trig),mh2PtEZdcx[trig]->GetXaxis()->FindBin(lowpt[ptbin]),mh2PtEZdcx[trig]->GetXaxis()->FindBin(highpt[ptbin])-1);
      projZDCxTrigUS[ptbin][trig] = mh2PtEZdcxUS[trig]->ProjectionY(Form("projZDCxTrigUS_%i_%i",ptbin,trig),mh2PtEZdcxUS[trig]->GetXaxis()->FindBin(lowpt[ptbin]),mh2PtEZdcxUS[trig]->GetXaxis()->FindBin(highpt[ptbin])-1);
      projZDCxTrigLS[ptbin][trig] = mh2PtEZdcxLS[trig]->ProjectionY(Form("projZDCxTrigLS_%i_%i",ptbin,trig),mh2PtEZdcxLS[trig]->GetXaxis()->FindBin(lowpt[ptbin]),mh2PtEZdcxLS[trig]->GetXaxis()->FindBin(highpt[ptbin])-1);
      projZDCxTrigHad[ptbin][trig] = mh2PtEZdcxHad[trig]->ProjectionY(Form("projZDCxTrigHad_%i_%i",ptbin,trig),mh2PtEZdcxHad[trig]->GetXaxis()->FindBin(lowpt[ptbin]),mh2PtEZdcxHad[trig]->GetXaxis()->FindBin(highpt[ptbin])-1);
    }
    
    //===================================================================
    // begin to get deltphi dist.
    
    for(Int_t ptbin = 0; ptbin < numPtBins; ptbin++){
      //=======================================================
      // get purity histo,
      hPurityTmp = (TH1F*)projZDCxTrig[ptbin][trig]->Clone("purityStatForPileup");
      for(auto i=0; i<projZDCxTrig[ptbin][trig]->GetXaxis()->GetLast(); i++){
        hPurityTmp->SetBinContent(i+1, hpurt->GetBinContent(ptbin+1));
        hPurityTmp->SetBinError(i+1, hpurt->GetBinError(ptbin+1));
        //        cout<<"Purity stat error"<<hpurt->GetBinError(ptbin+1)<<endl;
      }
      
      // Init necessary plotting tools
      lbl[ptbin] = new TPaveText(.15,.15,.35,.23,Form("NB NDC%i",ptbin));
      sprintf(textLabel,"%.1f < P_{T,e} < %.1f",lowpt[ptbin],highpt[ptbin]);
      lbl[ptbin]->AddText(textLabel);
      lbl[ptbin]->SetFillColor(kWhite);
      
      // Calculate electron purity from pol3 fit of xiaozhi data
      //      Float_t ptAv = (lowpt[ptbin]+highpt[ptbin])/2.;
      //      Float_t purity = purPar[0] + (purPar[1]*ptAv)+(purPar[2]*ptAv*ptAv);;
      //      Float_t purity = epsilonPurity[ptbin];
      hadPur = 1-epsilonPurity[ptbin];
      // Calculate PHe Reconstruction Eff from Xiaozhi embedding (fit)
      //      Float_t x = ptAv;
      //      Double_t recoEfficiency = effPar[0]*(1.0 -TMath::Exp(-(x+effPar[1])/effPar[2]));
      //      epsilon[ptbin] = recoEfficiency;
      
      projZDCxTrig[ptbin][trig] -> Add(projZDCxTrigUS[ptbin][trig], 1);
      projZDCxTrig[ptbin][trig] -> Multiply(hPurityTmp);
      //      projZDCxTrig[ptbin][trig] -> Scale(epsilonPurity[ptbin]);
      projZDCxTrigUS[ptbin][trig] -> Add(projZDCxTrigLS[ptbin][trig], -1.);
      projZDCxTrigUS[ptbin][trig] -> Scale(1./epsilon[ptbin]);
      projZDCxTrig[ptbin][trig] -> Add(projZDCxTrigUS[ptbin][trig], -1.);
      
      pileTrigs[ptbin][trig] = (TH1D*)projZDCxTrig[ptbin][trig]->Clone(Form("projZDCxTrig_%i_%i",ptbin,trig));
      
      
      // Make stats label with purity and effeciency
      char statLabel[100];
      stat[ptbin] = new TPaveText(.5,.7,.85,.87,Form("NB NDC%i",ptbin));
      sprintf(statLabel,"Eff: %.2f; ePure:%.2f",epsilon[ptbin],epsilonPurity[ptbin]);
      stat[ptbin]->InsertText(statLabel);
      stat[ptbin]->SetFillColor(kWhite);
      
      // Calculate Normalization for NPE delPhi
      inclNorm = mh1PtETracks[trig]->Integral(mh1PtETracks[trig]->GetXaxis()->FindBin(lowpt[ptbin]),mh1PtETracks[trig]->GetXaxis()->FindBin(highpt[ptbin])-1);
      LSNorm   = projTracksTrigLS[ptbin][trig]->Integral();
      USNorm   = projTracksTrigUS[ptbin][trig]->Integral();
      hhNorm   = mh1PtHadTracks[trig]->Integral(mh1PtHadTracks[trig]->GetXaxis()->FindBin(lowpt[ptbin]),mh1PtHadTracks[trig]->GetXaxis()->FindBin(highpt[ptbin])-1);
      HHScale = (Float_t)(inclNorm+USNorm)/(Float_t)hhNorm; // so the purity comparison is 1:1
      Float_t Norm = (Float_t)inclNorm - (1/epsilon[ptbin] - 1.)*(Float_t)USNorm + (1/epsilon[ptbin])*(Float_t)LSNorm - HHScale*hadPur*hhNorm; // Use the number of "signal" counts
      histoNorms->SetBinContent(histoNorms->GetBin(trig+1,ptbin+1), Norm); // Find the bin and fill with the
      
      // Calculate pileup for this ptbin
      Double_t pileCorrect=0.,pileNumTrigs=0.;
      for(Int_t zdcBin=0; zdcBin < pileTrigs[ptbin][trig]->GetXaxis()->GetLast();zdcBin++)
      {
        Double_t c=0,n=0;
        n = (Double_t)pileTrigs[ptbin][trig]->GetBinContent(zdcBin);        // Number of trigs in zdc
        c = pu[1]*pileTrigs[ptbin][trig]->GetBinCenter(zdcBin);   // From fit: (p1*zdc+p0)-p0
        //cout << pileTrigs[ptbin][trig]->GetBinCenter(zdcBin) << " " << c << " " << n << endl;
        pileCorrect += c*n;
        pileNumTrigs += n;
      }
      Double_t dphiBins = (Double_t)projDelPhiInclWt[ptbin][trig]->FindBin(3.14) - (Double_t)projDelPhiInclWt[ptbin][trig]->FindBin(-3.14);
      //  cout << "c*n: " << pileCorrect << " n: " << pileNumTrigs;
      //      cout<<"dphiBins    "<<dphiBins<<endl;
      pileCorrect = pileCorrect/pileNumTrigs/dphiBins;  // divide weighted average by number of bins.
      //cout << " pilecorrection: "<< pileCorrect<< endl; // Subtract this value from every bin before scaling.
      
      // Fill a histogram with the pileup correction in every bin
      pileupCorrection[ptbin][trig] = (TH1D*)projDelPhiPhotLSWt[ptbin][trig]->Clone(); // Clone a delPhi hist to get proper binning
      pileupCorrection[ptbin][trig]->SetName(Form("pileupCorrection_%i_%i",ptbin,trig));
      pileupCorrection[ptbin][trig]->Sumw2();
      for(Int_t ii=0; ii < pileupCorrection[ptbin][trig]->GetXaxis()->GetLast();ii++)
      {
        if(doPileup)pileupCorrection[ptbin][trig]->SetBinContent(ii,pileCorrect + pileCorrect*(puE[1]/pu[1]));
        else if(doMinusPp)pileupCorrection[ptbin][trig]->SetBinContent(ii,pileCorrect - pileCorrect*(puE[1]/pu[1]));
        else pileupCorrection[ptbin][trig]->SetBinContent(ii,pileCorrect);
        pileupCorrection[ptbin][trig]->SetBinError(ii,pileCorrect*(puE[1]/pu[1])); // Assign percentage of fit error to pileup correction error
      }
      
      c[trig]->cd(ptbin+1);
      // Assign to a single, simpler name for manip
      LSIM[ptbin][trig]  = projDelPhiPhotLSWt[ptbin][trig];
      LSIMNP[ptbin][trig]  = projDelPhiPhotLSNP[ptbin][trig];
      ULIMNP[ptbin][trig]  = projDelPhiPhotUSNP[ptbin][trig];
      
      USIM[ptbin][trig]  = projDelPhiPhotUSWt[ptbin][trig];
      INCL[ptbin][trig]  = projDelPhiInclWt[ptbin][trig];
      HHDP[ptbin][trig]  = projDelPhiHadHadWt[ptbin][trig];
      
      
      LSMM[ptbin][trig]  = projInvMassLS[ptbin][trig];
      USMM[ptbin][trig]  = projInvMassUS[ptbin][trig];
      NSPI[ptbin][trig]  = projnSigmaPion[ptbin][trig];
      
      // Rebin all as necessary
      Int_t RB = 1;
      LSIM[ptbin][trig]  -> Rebin(RB);
      LSIMNP[ptbin][trig]  -> Rebin(RB);
      ULIMNP[ptbin][trig]  -> Rebin(RB);
      
      USIM[ptbin][trig]  -> Rebin(RB);
      INCL[ptbin][trig]  -> Rebin(RB);
      HHDP[ptbin][trig]  -> Rebin(RB);
      NSPI[ptbin][trig]  -> Rebin(10);
      
      //=======================================================
      // get purity histo,
      hPurityTmp = (TH1F*)projDelPhiPhotLSWt[ptbin][trig]->Clone("purityStat");
      for(auto i=0; i<projDelPhiPhotLSWt[ptbin][trig]->GetXaxis()->GetLast(); i++){
        hPurityTmp->SetBinContent(i+1, hpurt->GetBinContent(ptbin+1));
        hPurityTmp->SetBinError(i+1, hpurt->GetBinError(ptbin+1));
      }
      // Actually manipulate histos and plot (photnic del Phi)
      
      USIM[ptbin][trig]->SetLineColor(kRed);
      USIM[ptbin][trig]->SetLineWidth(1);
      USIM[ptbin][trig]->GetXaxis()->SetTitle("#Delta#phi_{eh}");
      USIM[ptbin][trig]->GetXaxis()->SetRangeUser(lowPhi,highPhi);
      if(ptbin == 0)
        USIM[ptbin][trig]->SetTitle("Photonic Electron Reconstruction (No Partner Track)");
      else if (ptbin == 1 && trig !=3)
        USIM[ptbin][trig]->SetTitle(Form("HT%i",trig));
      else if (trig == 3 && ptbin == 1)
        USIM[ptbin][trig]->SetTitle("MB");
      else
        USIM[ptbin][trig]->SetTitle("");
      USIM[ptbin][trig]->Draw("");
      
      LSIM[ptbin][trig]->SetLineColor(kBlack);
      LSIM[ptbin][trig]->SetLineWidth(1);
      LSIM[ptbin][trig]->Draw(" same");
      lbl[ptbin]->Draw("same");
      
      // Subtraction of (USNP-LS)
      TH1F *SUB = (TH1F*)USIM[ptbin][trig]->Clone(); //
      SUB->SetName("Subtraction");      // Create SUB as a clone of USIM
      SUB->Add(LSIM[ptbin][trig],-1);
      SUB->SetLineColor(kBlue);
      SUB->SetLineWidth(1);
      SUB->SetFillStyle(3001);
      SUB->SetFillColor(kBlue);
      SUB->Draw("same");
      lbl[ptbin]->Draw("same");
      TLegend* leg = new TLegend(0.2,0.73,0.55,0.85);
      leg->AddEntry(USIM[ptbin][trig],"Unlike Sign, with partner","lpe");
      leg->AddEntry(LSIM[ptbin][trig],"Like Sign, with partner", "lpe");
      leg->AddEntry(SUB,"Unlike - Like, with partner", "lpe");
      leg->Draw();
      
      // Actually manipulate histos and plot (photonic InvMass)
      inMass[trig]->cd(ptbin+1);
      USMM[ptbin][trig]->SetLineColor(kRed);
      USMM[ptbin][trig]->SetLineWidth(1);
      USMM[ptbin][trig]->GetXaxis()->SetTitle("InvMass (GeV/c^{2})");
      USMM[ptbin][trig]->GetXaxis()->SetRangeUser(0,0.4);
      if(ptbin == 0)
        USMM[ptbin][trig]->SetTitle("Photonic Electron Reconstruction");
      else if (ptbin == 1 && trig !=3)
        USMM[ptbin][trig]->SetTitle(Form("HT%i",trig));
      else if (trig == 3 && ptbin == 1)
        USMM[ptbin][trig]->SetTitle("MB");
      else
        USMM[ptbin][trig]->SetTitle("");
      USMM[ptbin][trig]->Draw("");
      
      LSMM[ptbin][trig]->SetLineColor(kBlack);
      LSMM[ptbin][trig]->SetLineWidth(1);
      LSMM[ptbin][trig]->Draw("same");
      lbl[ptbin]->Draw("same");
      
      // Subtraction of (US-LS)
      TH1F *SUB4 = (TH1F*)USMM[ptbin][trig]->Clone(); //
      SUB4->SetName("Subtraction");      // Create SUB as a clone of USIM
      SUB4->Add(LSMM[ptbin][trig],-1);
      SUB4->SetLineColor(kBlue);
      SUB4->SetLineWidth(1);
      SUB4->SetFillStyle(3001);
      SUB4->SetFillColor(kBlue);
      SUB4->Draw("same");
      TLegend* leg2 = new TLegend(0.45,0.6,0.85,0.75);
      leg2->AddEntry(USMM[ptbin][trig],"Unlike Sign","lpe");
      leg2->AddEntry(LSMM[ptbin][trig],"Like Sign", "lpe");
      leg2->AddEntry(SUB4,"Unlike - Like", "lpe");
      leg2->Draw();
      
      // Handle Inclusive Hists
      IN[trig]->cd(ptbin+1);
      INCL[ptbin][trig]->SetLineColor(kBlue);
      INCL[ptbin][trig]->SetLineWidth(1);
      INCL[ptbin][trig]->GetXaxis()->SetTitle("#Delta#phi_{eh}");
      INCL[ptbin][trig]->GetXaxis()->SetRangeUser(lowPhi,highPhi);
      if(ptbin == 0)
        INCL[ptbin][trig]->SetTitle("Semi-Inclusive Electrons");
      else if (ptbin == 1 && trig !=3)
        INCL[ptbin][trig]->SetTitle(Form("HT%i",trig));
      else if (trig == 3 && ptbin == 1)
        INCL[ptbin][trig]->SetTitle("MB");
      else
        INCL[ptbin][trig]->SetTitle("");
      INCL[ptbin][trig]->Draw("");
      lbl[ptbin]->Draw("same");
      IN[trig]->Update();
      
      // Plot Had-Had correlations
      cHH[trig]->cd(ptbin+1);
      HHDP[ptbin][trig]->SetLineColor(kGreen+3);
      HHDP[ptbin][trig]->SetLineWidth(1);
      HHDP[ptbin][trig]->GetXaxis()->SetTitle("#Delta#phi_{eh}");
      HHDP[ptbin][trig]->GetXaxis()->SetRangeUser(lowPhi,highPhi);
      if(ptbin == 0)
        HHDP[ptbin][trig]->SetTitle("Hadron-Hadron Correlations");
      else if (ptbin == 1 && trig !=3)
        HHDP[ptbin][trig]->SetTitle(Form("HT%i",trig));
      else if (trig == 3 && ptbin == 1)
        HHDP[ptbin][trig]->SetTitle("MB");
      else
        HHDP[ptbin][trig]->SetTitle("");
      HHDP[ptbin][trig]->Draw("");
      lbl[ptbin]->Draw("same");
      
      // Subtraction of Inclusive - (1/e - 1)US + (1/e)LS - (1-purity)HadHad
      result[trig]->cd(ptbin+1);
      TH1F *INCDP = (TH1F*)INCL[ptbin][trig]->Clone();
      TH1F *ULDP  = (TH1F*)USIM[ptbin][trig]->Clone();
      TH1F *LSDP  = (TH1F*)LSIM[ptbin][trig]->Clone();
      TH1F *LSDPNP  = (TH1F*)LSIMNP[ptbin][trig]->Clone();
      TH1F *ULDPNP  = (TH1F*)ULIMNP[ptbin][trig]->Clone();
      
      //=======================================================
      TH1F *HADDP = (TH1F*)HHDP[ptbin][trig]->Clone();
      INCDP->SetName(Form("scaleNPEhDelPhi_%i_%i",trig,ptbin));

      ULDPNP->Scale(1./epsilon[ptbin] - 1.); // Scale each distribution by associated factors
      LSDPNP->Scale(1./epsilon[ptbin] - 1.);
      
      HADDP->Scale(HHScale);
      INCDP->Add(HADDP,-1);
      HADDP->Multiply(hPurityTmp); // since I use multiply
      INCDP->Add(HADDP,1);
      
      INCDP->Add(ULDPNP,-1);
      INCDP->Add(LSDPNP,1);
      INCDP->Add(LSDP,1);
      //=======================================================
      
      TH1F *unscaleINCDP = (TH1F*)INCDP->Clone();   //
      unscaleINCDP->SetName(Form("NPEhDelPhi_%i_%i",trig,ptbin)); // Make a clone before normalization, to pass to fit program
      INCDP->Scale(1./((Double_t)Norm));//*INCDP->GetBinWidth(1)));
      INCDP->SetLineColor(kBlack);
      INCDP->SetLineWidth(1);
      INCDP->SetFillStyle(3001);
      INCDP->SetFillColor(kYellow);
      INCDP->GetXaxis()->SetRangeUser(lowPhi,highPhi);
      INCDP->GetXaxis()->SetTitle("#Delta#phi_{eh}");
      INCDP->GetYaxis()->SetTitle("1/N_{NPE} #upoint dN/d(#Delta)#phi");
      INCDP->GetYaxis()->SetTitleOffset(1.55);
      if(ptbin == 0)
        INCDP->SetTitle("#Delta#phi Non-Photonic Electrons and Hadrons");
      else if (ptbin == 1 && trig !=3)
        INCDP->SetTitle(Form("HT%i",trig));
      else if (trig == 3 && ptbin == 1)
        INCDP->SetTitle("MB");
      else
        INCDP->SetTitle("");
      INCDP->Draw("");
      lbl[ptbin]->Draw("same");
      
      // Setup unscaled for fractionFit (don't normalize here!)
      unscaleINCDP->SetLineColor(kBlack);
      unscaleINCDP->SetLineWidth(1);
      unscaleINCDP->SetFillStyle(3001);
      unscaleINCDP->SetFillColor(kYellow);
      unscaleINCDP->GetXaxis()->SetRangeUser(lowPhi,highPhi);
      unscaleINCDP->GetXaxis()->SetTitle("#Delta#phi_{eh}");
      unscaleINCDP->GetYaxis()->SetTitle("1/N_{NPE} #upoint dN/d(#Delta)#phi");
      unscaleINCDP->GetYaxis()->SetTitleOffset(1.55);
      if(ptbin == 0)
        unscaleINCDP->SetTitle("#Delta#phi Non-Photonic Electrons and Hadrons");
      else if (ptbin == 1 && trig !=3)
        unscaleINCDP->SetTitle(Form("HT%i",trig));
      else if (trig == 3 && ptbin == 1)
        unscaleINCDP->SetTitle("MB");
      else
        unscaleINCDP->SetTitle("");
      
      // nSigmaPion QA
      nSigPi[trig]->cd(ptbin+1);
      NSPI[ptbin][trig]->SetLineColor(kGreen+3);
      NSPI[ptbin][trig]->SetLineWidth(1);
      NSPI[ptbin][trig]->GetXaxis()->SetTitle("n#sigma_{#pi}");
      NSPI[ptbin][trig]->GetXaxis()->SetRangeUser(-2.,2.);
      if(ptbin == 0)
        NSPI[ptbin][trig]->SetTitle("n Sigma Pion (n#sigma_{#pi})");
      else if (ptbin == 1 && trig !=3)
        NSPI[ptbin][trig]->SetTitle(Form("HT%i",trig));
      else if (trig == 3 && ptbin == 1)
        NSPI[ptbin][trig]->SetTitle("MB");
      else
        NSPI[ptbin][trig]->SetTitle("");
      NSPI[ptbin][trig]->Draw("");
      lbl[ptbin]->Draw("same");
      
      
      TH1F *INCLUSIVE = (TH1F*)INCL[ptbin][trig]->Clone();
      TH1F *UNLIKE  = (TH1F*)ULDP->Clone();
      TH1F *UNLIKENP  = (TH1F*)ULDPNP->Clone();
      TH1F *LIKE  = (TH1F*)LSDP->Clone();
      TH1F *LIKENP  = (TH1F*)LSDPNP->Clone();
      
      TH1F *HADRON = (TH1F*)HHDP[ptbin][trig]->Clone();
      TH1F *USmLS  = (TH1F*)UNLIKENP->Clone();
      USmLS->Add(LIKENP,-1);
      
      
//      INCLUSIVE->Scale(1./((Double_t)Norm));
//      UNLIKE->Scale(1./((Double_t)Norm));
//      UNLIKENP->Scale(1./((Double_t)Norm));
//      LIKE->Scale(1./((Double_t)Norm));
//      LIKENP->Scale(1./((Double_t)Norm));
//      USmLS->Scale(1./((Double_t)Norm));
//      HADRON->Scale(1./((Double_t)Norm));
      
      INCLUSIVE->SetLineColor(7);
      LIKE->SetLineColor(kBlue);
      //      INCLUSIVE->GetYaxis()->SetRangeUser(0.001,10);
      //      gPad->SetLogy(1);
      INCLUSIVE->GetXaxis()->SetRangeUser(lowPhi,highPhi);
      INCLUSIVE->SetMarkerStyle(20);
      UNLIKE->SetMarkerStyle(21);
      LIKE->SetMarkerStyle(22);
      HADRON->SetMarkerStyle(23);
      USmLS->SetMarkerStyle(34);
      INCLUSIVE->SetMarkerColor(7);
      INCLUSIVE->SetMarkerSize(0.3);
      UNLIKE->SetMarkerSize(0.3);
      LIKE->SetMarkerSize(0.3);
      HADRON->SetMarkerSize(0.3);
      USmLS->SetMarkerSize(0.3);
      INCLUSIVE->SetMarkerColor(7);
      UNLIKE->SetMarkerColor(kRed);
      LIKE->SetMarkerColor(kBlue);
      HADRON->SetMarkerColor(kGreen+3);
      
      // Clone the distributions for comparisons across trigs
      inclTrig[ptbin][trig]  = (TH1F*)INCLUSIVE->Clone();
      inclTrig[ptbin][trig]  ->SetName(Form("inclTrig_%i_%i",ptbin, trig));
      usTrig[ptbin][trig]    = (TH1F*)UNLIKE->Clone();
      usTrig[ptbin][trig]    ->SetName(Form("usTrig_%i_%i",ptbin, trig));
      usTrigNP[ptbin][trig]    = (TH1F*)UNLIKENP->Clone();
      usTrigNP[ptbin][trig]    ->SetName(Form("usTrigNP_%i_%i",ptbin, trig));
      lsTrig[ptbin][trig]    = (TH1F*)LIKE->Clone();
      lsTrig[ptbin][trig]    ->SetName(Form("lsTrig_%i_%i",ptbin, trig));
      lsTrigNP[ptbin][trig]    = (TH1F*)LIKENP->Clone();
      lsTrigNP[ptbin][trig]    ->SetName(Form("lsTrigNP_%i_%i",ptbin, trig));
      usmlsTrig[ptbin][trig]    = (TH1F*)USmLS->Clone();
      usmlsTrig[ptbin][trig]    ->SetName(Form("usmlsTrig_%i_%i, no partner",ptbin, trig));
      hadTrig[ptbin][trig]   = (TH1F*)HADRON->Clone();
      hadTrig[ptbin][trig]   ->SetName(Form("hadTrig_%i_%i",ptbin, trig));
      npeTrig[ptbin][trig]   = (TH1F*)INCDP->Clone();
      npeTrig[ptbin][trig]   ->SetName(Form("npeTrig_%i_%i",ptbin, trig));
    }
    
    //===================================================================
    
    pileC[trig]->cd();
    gPad->SetLeftMargin(0.12);
    for(Int_t ptbin = 0; ptbin < numPtBins; ptbin++){
      if(ptbin ==0){
        pileupCorrection[ptbin][trig]->SetTitle(" ");
        pileupCorrection[ptbin][trig]->GetYaxis()->SetRangeUser(0, 0.1);
        pileupCorrection[ptbin][trig]->SetNdivisions(512,"y");
        pileupCorrection[ptbin][trig]->GetXaxis()->SetTitle("#Delta_{#phi_{eh}}");
        pileupCorrection[ptbin][trig]->GetYaxis()->SetTitle("#frac{1}{N_{NPE}}#frac{dN}{d(#Delta_{#phi})}");
      }
      if(trig == 0)pileupCorrection[ptbin][trig]->SetLineColor(kAzure+ptbin);
      else pileupCorrection[ptbin][trig]->SetLineColor(kSpring+ptbin);
      
      auto pileTmp = (TH1D*)pileupCorrection[ptbin][trig]->Clone("pileCorreDraw");
      pileTmp->Sumw2(0);
      if(ptbin == 0)pileTmp->Draw();
      else pileTmp->Draw("same");
    }
  }
  fitSlope->cd();
  fs->GetYaxis()->SetRangeUser(-1.2e-4, 2.2e-4);
  fitSlope->SetGridy();
  fs->Draw("PE X0");
  
  
  //===================================================================
  
  // Plot all of the distributions for each trigger
  for(Int_t ptbin = 0; ptbin < numPtBins; ptbin++)
  {
    inclTrig[ptbin][0]  -> SetLineColor(kBlack);
    inclTrig[ptbin][0]  -> SetMarkerColor(kBlack);
    usTrig[ptbin][0]    -> SetLineColor(kBlack);
    usTrig[ptbin][0]    -> SetMarkerColor(kBlack);
    lsTrig[ptbin][0]    -> SetLineColor(kBlack);
    lsTrig[ptbin][0]    -> SetMarkerColor(kBlack);
    
    usTrigNP[ptbin][0]    -> SetLineColor(kBlack);
    usTrigNP[ptbin][0]    -> SetMarkerColor(kBlack);
    lsTrigNP[ptbin][0]    -> SetLineColor(kBlack);
    lsTrigNP[ptbin][0]    -> SetMarkerColor(kBlack);
    usmlsTrig[ptbin][0]    -> SetLineColor(kBlack);
    usmlsTrig[ptbin][0]    -> SetMarkerColor(kBlack);
    
    hadTrig[ptbin][0]   -> SetLineColor(kBlack);
    hadTrig[ptbin][0]   -> SetMarkerColor(kBlack);
    npeTrig[ptbin][0]   -> SetLineColor(kBlack);
    npeTrig[ptbin][0]   -> SetMarkerColor(kBlack);
    inclTrig[ptbin][2]  -> SetLineColor(kRed);
    inclTrig[ptbin][2]  -> SetMarkerColor(kRed);
    
    usTrig[ptbin][2]    -> SetLineColor(kRed);
    usTrig[ptbin][2]    -> SetMarkerColor(kRed);
    lsTrig[ptbin][2]    -> SetLineColor(kRed);
    lsTrig[ptbin][2]    -> SetMarkerColor(kRed);
    usTrigNP[ptbin][2]    -> SetLineColor(kRed);
    usTrigNP[ptbin][2]    -> SetMarkerColor(kRed);
    lsTrigNP[ptbin][2]    -> SetLineColor(kRed);
    lsTrigNP[ptbin][2]    -> SetMarkerColor(kRed);
    usmlsTrig[ptbin][2]    -> SetLineColor(kBlack);
    usmlsTrig[ptbin][2]    -> SetMarkerColor(kBlack);
    
    hadTrig[ptbin][2]   -> SetLineColor(kRed);
    hadTrig[ptbin][2]   -> SetMarkerColor(kRed);
    npeTrig[ptbin][2]   -> SetLineColor(kRed);
    npeTrig[ptbin][2]   -> SetMarkerColor(kRed);
    
    if(ptbin == 0)
    {
      inclTrig[ptbin][0]->SetTitle("semi-Inclusive Trigger DeltaPhi Comparison, with Partner");
      usTrig[ptbin][0]->SetTitle("Unlike Sign Trigger DeltaPhi Comparison, with Partner");
      usTrigNP[ptbin][0]->SetTitle("Unlike Sign Trigger DeltaPhi Comparison, no Partner");
      lsTrig[ptbin][0]->SetTitle("Like Sign Trigger DeltaPhi Comparison, with Partner");
      lsTrigNP[ptbin][0]->SetTitle("Like Sign Trigger DeltaPhi Comparison, no Partner");
      usmlsTrig[ptbin][0]->SetTitle("UNLike - Like Sign Trigger DeltaPhi Comparison, no Partner");
      hadTrig[ptbin][0]->SetTitle("Hadron-Hadron Trigger DeltaPhi Comparison");
      npeTrig[ptbin][0]->SetTitle("NPE Trigger DeltaPhi Comparison");
    }
    else
    {
      inclTrig[ptbin][0]->SetTitle("");
      usTrig[ptbin][0]->SetTitle("");
      lsTrig[ptbin][0]->SetTitle("");
      hadTrig[ptbin][0]->SetTitle("");
      npeTrig[ptbin][0]->SetTitle("");
    }
    
    
    
//    inclTrig[ptbin][0]->GetYaxis()->SetRangeUser(.001,0.2);
//    usTrig[ptbin][0]->GetYaxis()->SetRangeUser(.001,0.12);
//    usTrigNP[ptbin][0]->GetYaxis()->SetRangeUser(.001,0.12);
//    lsTrig[ptbin][0]->GetYaxis()->SetRangeUser(.001,0.08);
//    lsTrigNP[ptbin][0]->GetYaxis()->SetRangeUser(.001,0.08);
//    usmlsTrig[ptbin][0]->GetYaxis()->SetRangeUser(.001,0.1);
//
//    inclTrig[ptbin][2]->GetYaxis()->SetRangeUser(.001,0.2);
//    usTrig[ptbin][2]->GetYaxis()->SetRangeUser(.001,0.12);
//    usTrigNP[ptbin][2]->GetYaxis()->SetRangeUser(.001,0.12);
//    lsTrig[ptbin][2]->GetYaxis()->SetRangeUser(.001,0.08);
//    lsTrigNP[ptbin][2]->GetYaxis()->SetRangeUser(.001,0.08);
//    usmlsTrig[ptbin][2]->GetYaxis()->SetRangeUser(.001,0.1);
    
    inclTrig[ptbin][0]->GetYaxis()->SetRangeUser(.001,1600);
     usTrig[ptbin][0]->GetYaxis()->SetRangeUser(.001,1600);
     usTrigNP[ptbin][0]->GetYaxis()->SetRangeUser(.001,1600);
     lsTrig[ptbin][0]->GetYaxis()->SetRangeUser(.001,1600);
     lsTrigNP[ptbin][0]->GetYaxis()->SetRangeUser(.001,1600);
     usmlsTrig[ptbin][0]->GetYaxis()->SetRangeUser(-1000,400);

     inclTrig[ptbin][2]->GetYaxis()->SetRangeUser(.001,1600);
     usTrig[ptbin][2]->GetYaxis()->SetRangeUser(.001,1600);
     usTrigNP[ptbin][2]->GetYaxis()->SetRangeUser(.001,1600);
     lsTrig[ptbin][2]->GetYaxis()->SetRangeUser(.001,1600);
     lsTrigNP[ptbin][2]->GetYaxis()->SetRangeUser(.001,1600);
     usmlsTrig[ptbin][2]->GetYaxis()->SetRangeUser(-1000,400);
    //======================================================================
    //
    inclComp->cd(ptbin+1);
    //    gPad->SetLogy(1);
    if(ptbin<2)inclTrig[ptbin][0]  -> Draw("p");
    else inclTrig[ptbin][2]  -> Draw("same p");
    //    compLeg->Draw("same");
    //    lbl[ptbin]->Draw("same");
    usComp->cd(ptbin+1);
    if(ptbin<2)usTrig[ptbin][0]    -> Draw("p");
    else usTrig[ptbin][2]    -> Draw("same p");
    
    usNPComp->cd(ptbin+1);
    if(ptbin<2)usTrigNP[ptbin][0]    -> Draw("p");
    else usTrigNP[ptbin][2]    -> Draw("same p");

    lsComp->cd(ptbin+1);
    if(ptbin<2)lsTrig[ptbin][0]    -> Draw("p");
    else lsTrig[ptbin][2]    -> Draw("same p");
    
    lsNPComp->cd(ptbin+1);
    //    gPad->SetLogy(1);
    if(ptbin<2)lsTrigNP[ptbin][0]    -> Draw("p");
    else lsTrigNP[ptbin][2]    -> Draw("same p");
    
    usmlsComp->cd(ptbin+1);
    //    gPad->SetLogy(1);
    if(ptbin<2)usmlsTrig[ptbin][0]    -> Draw("p");
    else usmlsTrig[ptbin][2]    -> Draw("same p");
  }
  // Draw on "SinglePlot" canvas for saving single plots from grid
  TPad* pNew = (TPad*)result[2]->GetPad(4)->Clone();
  singlePlot->cd();
  pNew->ResizePad();
  pNew->Draw();
  
  // Make PDF with output canvases
  if(makePDF)
  {
    //Set front page
    TCanvas* fp = new TCanvas("fp","Front Page",100,0,1000,900);
    fp->cd();
    TBox *bLabel = new TBox(0.01, 0.88, 0.99, 0.99);
    bLabel->SetFillColor(38);
    bLabel->Draw();
    TLatex tl;
    tl.SetNDC();
    tl.SetTextColor(kWhite);
    tl.SetTextSize(0.033);
    char tlName[100];
    char tlName2[100];
    
    TString titlename = FileName;
    int found = titlename.Last('/');
    if(found >= 0){
      titlename.Replace(0, found+1, "");
    }
    sprintf(tlName, "RUN 12 pp 200 GeV NPE-h    #Delta#phi Analysis");
    tl.SetTextSize(0.05);
    tl.SetTextColor(kWhite);
    tl.DrawLatex(0.05, 0.92,tlName);
    
    TBox *bFoot = new TBox(0.01, 0.01, 0.99, 0.12);
    bFoot->SetFillColor(38);
    bFoot->Draw();
    tl.SetTextColor(kWhite);
    tl.SetTextSize(0.05);
    tl.DrawLatex(0.05, 0.05, (new TDatime())->AsString());
    tl.SetTextColor(kBlack);
    tl.SetTextSize(0.03);
    tl.DrawLatex(0.1, 0.14, titlename);
    sprintf(tlName,"eID: -1 < n  #sigma_{e TPC} < 3;  #left|gDCA #right| < 1 cm; 0.3 < p/E < 1.5;");
    tl.DrawLatex(0.1, 0.8,tlName);
    sprintf(tlName,"       nHitsFit > 20; nHits   #frac{dE}{dx} > 15; nHitFit/Max > 0.52;    #left|#eta#right| < 0.7;");
    tl.DrawLatex(0.1, 0.75,tlName);
    sprintf(tlName,"       n #phi > 1; n #eta > 1;  #left|dZ#right| < 3 cm;  #left|d#phi#right| < 0.015;");
    tl.DrawLatex(0.1, 0.7,tlName);
    sprintf(tlName,"hID: p_{T} > %.2f;  #left|#eta#right| < 1; nHitsFit > 15; nHits   #frac{dE}{dx} > 10; DCA < 1 cm;", hptCut);
    tl.DrawLatex(0.1, 0.6,tlName);
    sprintf(tlName,"Event:  #left|V_{z}#right| < 35 cm;");
    tl.DrawLatex(0.1, 0.5,tlName);
    sprintf(tlName,"Triggers:  BHT0; BHT2;");
    tl.DrawLatex(0.1, 0.4,tlName);
    
    
    // Place canvases in order
    TCanvas* temp = new TCanvas();
    sprintf(name, "FFOutput/%s_output_%s.pdf[", FileName, FileNameR);
    temp->Print(name);
    sprintf(name, "FFOutput/%s_output_%s.pdf", FileName, FileNameR);
    temp = fp; // print front page
    temp->Print(name);
    //    temp = mixedEventEff;
    //    temp->Print(name);
    temp = crec;
    temp->Print(name);
    temp = cpur;
    temp->Print(name);
    temp = mixedC;
    temp->Print(name);
    temp = singlePlot;
    temp->Print(name);
    temp = fitSlope;
    temp->Print(name);
    /*temp = mixedCbinEta;
     temp->Print(name);
     temp = mixedCbinPhi;
     temp->Print(name);
     temp = mixedCbin;
     temp->Print(name);*/
    temp = inclComp;
    temp->Print(name);
    temp = lsNPComp;
    temp->Print(name);
    temp = lsComp;
    temp->Print(name);
    temp = usComp;
    temp->Print(name);
    temp = usNPComp;
    temp->Print(name);
    temp = usmlsComp;
    temp->Print(name);
    
    //    temp = inclComp;
    //    temp->Print(name);
    //    temp = usComp;
    //    temp->Print(name);
    //    temp = usNPComp;
    //    temp->Print(name);
    //    temp = lsComp;
    //    temp->Print(name);
    //    temp = lsNPComp;
    //    temp->Print(name);
    //    temp = usmlsComp;
    //    temp->Print(name);
    
    //    temp = hadComp;
    //    temp->Print(name);
    //    temp = npeComp;
    //    temp->Print(name);
    for(Int_t ii=0; ii<numTrigs; ii++)
    {
      if(!fPaintAll && (ii==1 || ii==3))
        continue;
      temp = IN[ii];
      temp->Print(name);
      temp = c[ii]; // PHE, with partner
      temp->Print(name);
      temp = cHH[ii]; // HH
      temp->Print(name);
      temp = result[ii]; // NPE
      temp->Print(name);
      
      temp = pileTrig[ii];
      temp->Print(name);
      temp = pileHad[ii];
      temp->Print(name);
      temp = pile[ii];
      temp->Print(name);
      temp = pileC[ii];
      temp->Print(name);
    }
    sprintf(name, "FFOutput/%s_output_%s.pdf]", FileName, FileNameR);
    temp->Print(name);
  }
  
  if(makeROOT)
  {
    file->Write();
    file->Close();
  }
}

Bool_t checkPaintAllTrigs(){
  
  Bool_t cPaintAll = kFALSE;
  Int_t number = 2;
  while(number > 1 || number < 0){
    std::cout << "Show all trigs? [default: 0]: ";
    std::string input;
    std::getline( std::cin, input );
    if ( !input.empty() ) {
      std::istringstream stream( input );
      stream >> number;
      if(number == 1)
        cPaintAll=kTRUE;
    }
    else
      number = 0;
  }
  
  return cPaintAll;
  
}

void checkBatchMode(){
  
  // sets batch mode, so don't draw canvas
  Int_t number = 2;
  while(number > 1 || number < 0){
    std::cout << "Batch Mode? [default: 1]: ";
    std::string input;
    std::getline( std::cin, input );
    if ( !input.empty() ) {
      std::istringstream stream( input );
      stream >> number;
      if(number == 0)
        gROOT->SetBatch(kFALSE);
      if(number == 1)
        gROOT->SetBatch(kTRUE);
    }
    else
    {
      number = 1;
      gROOT->SetBatch(kTRUE);
    }
  }
}

Bool_t checkMakePDF(){
  
  // Set option for pdf creation
  Int_t number = 2; Bool_t fmakePDF = kTRUE;
  while(number > 1 || number < 0){
    std::cout << "Make PDF? [default: 1]: ";
    std::string input;
    std::getline( std::cin, input );
    if ( !input.empty() ){
      std::istringstream stream( input );
      stream >> number;
      if(number == 0)
        fmakePDF = kFALSE;
      if(number == 1)
        fmakePDF = kTRUE;
    }
    else
      number = 1;
  }
  return fmakePDF;
}

Bool_t checkMakeRoot(){
  
  // Set option for .root creation
  Int_t number = 2; Bool_t fmakeROOT = kTRUE;
  while(number > 1 || number < 0){
    std::cout << "Make .root? [default: 1]: ";
    std::string input;
    std::getline( std::cin, input );
    if ( !input.empty() ){
      std::istringstream stream( input );
      stream >> number;
      if(number == 0)
        fmakeROOT = kFALSE;
      if(number == 1){
        fmakeROOT = kTRUE;
      }
    }
    else
      number = 1;
  }
  return fmakeROOT;
}
