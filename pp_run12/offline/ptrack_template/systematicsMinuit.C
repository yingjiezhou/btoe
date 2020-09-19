// Minuit Fit - Z. Miller Sep 8, 2015
//
// .L minuitFit.C
// fractionFit() 
// takes output of offline.C (data version) and readTree.C (templates) as inputs.
// Copy current best data and templates as "current%s.root" {Template,Data}

#include "anaConst.h"

TGraphAsymmErrors *getPrelimnaryStat();
TGraphAsymmErrors *getPrelimnarySys();
void drawtext();

Bool_t checkMakePDF();
Bool_t checkMakeRoot();
Bool_t haveName;
void chi2_0(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
void chi2_2(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
void chi2_0S(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
void chi2_2S(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
void chi2_C(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
void chi2_P0(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
void chi2_P1(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
void chi2_PP(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
void chi2_PP1(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
void doFit(TMinuit* ,Double_t&, Double_t&, Double_t&); // Generic call to start fit (function, param0, param1, err0, err1) with the par and err being global returns
void doFit(TMinuit* ,Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&); // Generic call to start fit (function, param0, param1, err0, err1) with the par and err being global returns

double getFitFunction(Double_t*, double, double);
double getFitFunctionError(Double_t*,double, double);
double getFitFunctionS(Double_t*, double, double);
double getFitFunctionErrorS(Double_t*,double, double);
char FileName[100];
char FileNameR[100];
const Int_t numPtBins = anaConst::nPtBins;
TH1D* projB[numPtBins];
TH1D* projC[numPtBins];
TH1D* projData0[numPtBins];
TH1D* projData2[numPtBins];
TH1D* projData0S[numPtBins];
TH1D* projData2S[numPtBins];
TH1D* combData[numPtBins];
TH1D* plotD0[numPtBins];
TH1D* plotD2[numPtBins];
TH1D* plotD0S[numPtBins];
TH1D* plotD2S[numPtBins];
TH1D* plotC[numPtBins];
TH1D* plotB[numPtBins];
TH1D* pileupCorrect[numPtBins][2];
TH2F* histoNorms;
TH1D* pileupCorrectS[numPtBins][2];
TH2F* histoNormsS;
TH1F* bPtNorms[numPtBins];
TH1F* cPtNorms[numPtBins];
TH1F* cbPtNorms[numPtBins];
TH1D* projCB[numPtBins]; // zyj
TF1 *hfit[numPtBins];

// Previous Analysis
TH1D *Hdphi[2];
TH1D *HpphiD[2];
TH1D *HpphiB[2];

Int_t currentPtBin;
Double_t curChi2;
Double_t curNDF;

// Minuit Constants
double amin,edm,errdef;
int nvpar,nparx,icstat;
double arglist[10];int ierflg=0;
double dum1,dum2;
char buf[1024];
//
//Double_t plotHigh[numPtBins] = {0.3,0.32,0.32,0.45,0.47,0.6,1.0,2,1.6,1.6,1.6,1.6,1.6,1.6};
//Double_t plotLow[numPtBins] = {0.0,0.0,0.0,0.0,0.0,-0.1,-0.15,-0.4,-0.3,-0.3,-0.2,-0.2,-0.2,-0.2};

Double_t plotHigh[numPtBins] = {3.2,3.2,3.2,4.2,4.2,4.2,4,4,4};
//Double_t plotHigh[numPtBins] = {0.32,0.32,0.32,0.6,0.6,0.6,1.6,1.6,1.6};

Double_t plotLow[numPtBins] = {-0.1,-0.1,-0.1,0.0,0.0,0.0,-0.1,-0.1,-0.1};

// Global values for simple fit handling
Double_t p00[numPtBins],p01[numPtBins],p20[numPtBins],p21[numPtBins];
Double_t e00U[numPtBins],e01U[numPtBins],e20U[numPtBins],e21U[numPtBins];
Double_t e00D[numPtBins],e01D[numPtBins],e20D[numPtBins],e21D[numPtBins];
Double_t pC0[numPtBins],pC1[numPtBins],eC0[numPtBins],eC1[numPtBins];
Double_t eC0U[numPtBins],eC1U[numPtBins];
Double_t eC0D[numPtBins],eC1D[numPtBins];

Double_t Rb0[numPtBins],Rb2[numPtBins],RbC[numPtBins],A0[numPtBins],A2[numPtBins],pT[numPtBins];
Double_t eb0U[numPtBins],eb2U[numPtBins],ebCU[numPtBins],dx[numPtBins];
Double_t eb0D[numPtBins],eb2D[numPtBins],ebCD[numPtBins];
Double_t eA0U[numPtBins],eA2U[numPtBins];
Double_t eA0D[numPtBins],eA2D[numPtBins];

Double_t p00S[numPtBins],p01S[numPtBins],p20S[numPtBins],p21S[numPtBins];
Double_t e00US[numPtBins],e01US[numPtBins],e20US[numPtBins],e21US[numPtBins];
Double_t e00DS[numPtBins],e01DS[numPtBins],e20DS[numPtBins],e21DS[numPtBins];
Double_t pC0S[numPtBins],pC1S[numPtBins],eC0S[numPtBins],eC1S[numPtBins];
Double_t eC0US[numPtBins],eC1US[numPtBins];
Double_t eC0DS[numPtBins],eC1DS[numPtBins];

Double_t Rb0S[numPtBins],Rb2S[numPtBins],RbCS[numPtBins],A0S[numPtBins],A2S[numPtBins];
Double_t eb0US[numPtBins],eb2US[numPtBins],ebCUS[numPtBins],dxS[numPtBins];
Double_t eb0DS[numPtBins],eb2DS[numPtBins],ebCDS[numPtBins];
Double_t eA0US[numPtBins],eA2US[numPtBins];
Double_t eA0DS[numPtBins],eA2DS[numPtBins];


Double_t sysChange0[numPtBins],sysChange2[numPtBins],sysChange[numPtBins],sysError[numPtBins];
Double_t sysChangeUp[numPtBins], sysChangeDown[numPtBins], sysChangeAbs[numPtBins];
Double_t ptOFF1[numPtBins],ptOFF2[numPtBins],ptSys[numPtBins];
Int_t plotCount0 = 0, plotCount2 = 0, plotCount = 0, plotCountSys=0;
Double_t RbP[2],EbP[2],pTP[2],SF[2],eSF[2];
Double_t RbPP[2],EbPP[2],pTPP[2],SFPP[2],eSFPP[2];
// For Scale Check
Double_t scX[numPtBins], scY[numPtBins];

Int_t rangeLow, rangeHigh;
Int_t rangefit = 1.5;

Bool_t kSymmetrize = kTRUE; // if true, symmetrize templates about dPhi=0
Bool_t oneParamFit = kFALSE; // if false, do 2 param fit
Bool_t bUp = kFALSE;
Bool_t bDown = kFALSE;
Double_t FITPARAS = 1.066; // From Fit of P1. Error is 0.007 on fit`

//Double_t hjpsiconTot[] = {0.188643, 0.127731, 0.0762974, 0.0578912, 0.0506605, 0.0491143, 0.0478802, 0.0379366, 0.0407632};
Double_t hjpsiconTot[] = {0.12, 0.12, 0.1, 0.06, 0.05, 0.035, 0.035, 0.28643, 0.28643};

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex);


void systematicsMinuit(const char* FileName="Sep19", const char* FileNameR="default", Bool_t doPileup = kFALSE, Bool_t doPythia = kFALSE, Bool_t doFitRange = kFALSE, Bool_t doJpsi = kFALSE)
{
//  bUp = kTRUE;
//  bDown = kTRUE;
  gROOT->SetBatch(kTRUE);
  gStyle->SetOptStat(0);
  TH1F::SetDefaultSumw2();
  TH1D::SetDefaultSumw2();
  
  if(doFitRange) rangefit = 3;

  char name[1000];
  
  cout << "Must Use Same Binning as previous Analysis!" << endl;
  
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  haveName = kFALSE;
  char fname[100];
  TFile* file;
  Bool_t makePDF = kTRUE;
  Bool_t makeROOT =kTRUE;
  //  Bool_t makePDF = checkMakePDF();
  //  Bool_t makeROOT = checkMakeRoot();
  if(makeROOT){
    sprintf(fname,"FFOutput/sysChange_%s_%s_FIT.root",FileNameR, FileName);
    file = new TFile(fname,"RECREATE");
    if (file->IsOpen()==kFALSE)
    {
      std::cout << "!!! Outfile Not Opened !!!" << std::endl;
      makeROOT = kFALSE;
    }
  }
  
  sprintf(fname,"FFOutput/sysChange_default_%s_FIT.root",FileName);
  TFile *fdef = new TFile(fname,"READ");
  TGraphAsymmErrors *grd = (TGraphAsymmErrors*)fdef->Get("HT0"); // old pythia template
  
  TGraphAsymmErrors *pstat = getPrelimnaryStat();
  TGraphAsymmErrors *psyst = getPrelimnarySys();
  
  
  //sprintf(name,"output/sim/Done_pythia_npe_tree_May4.root"); // from Zach

  sprintf(name,"output/sim/pythia_npe_tree_May18.root"); // from Zach, old
//  sprintf(name,"minBiasTemplates111915/readTreeOutput/input/pythia_npe_tree_May9.root"); // from yjzhou
  if(doPythia) sprintf(name,"output/sim/pythia_npe_tree_May26.root"); // from new pythia tune
//  if(doPythia) sprintf(name,"/Users/zhouyingjie/Local/PWG/btoe/pp_run12/sim/checkCode/offline/Jpsi_sys/rootfile/hf.root"); // with no prompt jpsi,(since non-prompt jpsi is small, can be just from HF, mean non-prompt also removed)
  if(doPythia && doJpsi) sprintf(name,"output/sim/pythia_npe_tree_May18_hf_OctetJpsi.root");// new, bak

  
  TFile *fT = new TFile(name,"READ");
  
  sprintf(name,Form("FFOutput/npe_tree_%s_processed_default.root", FileName));
  TFile *fD = new TFile(name,"READ");
  
  if(doPileup || doPythia || oneParamFit || doFitRange) sprintf(name,Form("FFOutput/npe_tree_%s_processed_default.root", FileName));
  else sprintf(name,Form("FFOutput/npe_tree_%s_processed_%s.root", FileName, FileNameR));
  TFile *fS = new TFile(name,"READ");
  
  if (fT->IsOpen()==kFALSE || fD->IsOpen()==kFALSE || fS->IsOpen()==kFALSE)
  { std::cout << "!!!!!! Either B,C, or Data File not found !!!!!!" << std::endl
    << "Looking for currentB.root, currentC.root, and currentData.root" << std::endl;
    exit(1); }
  
  // Set constants and projection bins (from header file anaConst, analysis constants)
  
  Float_t lowpt[numPtBins],highpt[numPtBins];
  for(Int_t c=0; c< numPtBins; c++){
    lowpt[c] = anaConst::lpt[c];
    highpt[c] = anaConst::hpt[c];
  }
  Float_t hptCut=anaConst::hptCut;
  
  // Make Canvases
  TCanvas* deltaPhi  = new TCanvas("deltaPhi","Pythia Delta Phi",150,0,1150,1000);
  TCanvas* deltaPhi2  = new TCanvas("deltaPhi2","Pythia Delta Phi",150,0,1150,1000);
  TCanvas* fitResult0 = new TCanvas("fitResult0","RB Extraction HT0",150,0,1150,1000);
  TCanvas* fitResult2 = new TCanvas("fitResult2","RB Extraction HT2",150,0,1150,1000);
  TCanvas* fitResult02 = new TCanvas("fitResult02","RB Extraction HT02",150,0,1150,1000);
  TCanvas* fitRatio = new TCanvas("fitRatio","fit over data",150,0,1150,1000);

  TCanvas* pileC = new TCanvas("pileC","",150,0,1150,1000);
  
  //  TCanvas* fitResultC = new TCanvas("fitResultC","RB Extraction Combined Trigs",150,0,1150,1000);
  //  TCanvas* fitResultP = new TCanvas("fitResultP","RB Previous Analysis",150,0,1150,1000);
  //  TCanvas* scaleCheck = new TCanvas("scaleCheck","Check scale diff",150,0,1150,1000);
  //  TCanvas* prettyPlot = new TCanvas("prettyPlot","PrettyPlot",150,0,1150,1000);
  deltaPhi  ->Divide(3,3);
  deltaPhi2 ->Divide(3,3);
  fitResult0->Divide(3,3);
  fitResult2->Divide(3,3);
  fitResult02->Divide(3,2, 0, 0, 0);
  fitRatio->Divide(3,2, 0, 0, 0);
  pileC->Divide(3,3);
//  deltaPhiSys->Divide(3,3);
  //fitResultC->Divide(3,3);
  //fitResultP->Divide(2,2);
  //scaleCheck->Divide(1,2);
  
  
  // Get and Draw histos
  TPaveText* lbl[numPtBins];
  TPaveText* stat[4][numPtBins];
  char statLabel[100];
  char textLabel[100];
  Int_t plotbin;
  Double_t norm0,norm2,normB,normC,norm0S,norm2S, normCB;
  
  // Get ptbin independent hists
  histoNorms  = (TH2F*)fD->Get("histoNorms");
  histoNormsS = (TH2F*)fS->Get("histoNorms");
  // Get Previous Analysis
  //  TFile *file3 = new TFile("/Users/zach/Research/previousNPEhFigures/Chi2_25_35.root");
  //  Hdphi[0]  = (TH1D*)file3->Get("fit_25_35");
  //  HpphiD[0] = (TH1D*)file3->Get("De_25_35");
  //  HpphiB[0] = (TH1D*)file3->Get("Be_25_35");
  //  TFile *file4 = new TFile("/Users/zach/Research/previousNPEhFigures/Chi2_55_65.root");
  //  Hdphi[1]  = (TH1D*)file4->Get("fit_55_65");
  //  HpphiD[1] = (TH1D*)file4->Get("De_55_65");
  //  HpphiB[1] = (TH1D*)file4->Get("Be_55_65");
  //  TCanvas *pileU = new TCanvas("pileU","pileU",100,0,1000,1000);
  //  pileU->Divide(1,2);
  
  FILE* pFile;
  pFile = fopen(Form("FFOutput/SysChange_%s.txt", FileNameR),"w");
  
  //  for(Int_t ptbin=0; ptbin<numPtBins; ptbin++)
  for(Int_t ptbin=0; ptbin<7; ptbin++)
  {
    
    hfit[ptbin] = new TF1(Form("hfit_%d", ptbin), "pol0", -1.75, 1.75);
    hfit[ptbin]->SetLineColor(kBlue);
    
    bPtNorms[ptbin]   = (TH1F*)fT->Get(Form("beEventTally_%i",ptbin));
    cPtNorms[ptbin]   = (TH1F*)fT->Get(Form("ceEventTally_%i",ptbin));
    
    if(doJpsi){
      cbPtNorms[ptbin]   = (TH1F*)fT->Get(Form("ceEventTallyJpsi_%i",ptbin)); //zyj, should be prompt jpsi dist.
      projCB[ptbin] = (TH1D*)fT->Get(Form("hdPhiRawceJpsi_%i",ptbin));
    }
    
    if(kSymmetrize)
    {
      norm0 = histoNorms->GetBinContent(histoNorms->GetBin(1,ptbin+1));
      norm2 = histoNorms->GetBinContent(histoNorms->GetBin(3,ptbin+1));
      normB = 2.0*bPtNorms[ptbin]->GetBinContent(1); //2x is for wrapping about dPhi = 0
      normC = 2.0*cPtNorms[ptbin]->GetBinContent(1);
      if(doJpsi) normCB = 2.0*cbPtNorms[ptbin]->GetBinContent(1);
      norm0S = histoNormsS->GetBinContent(histoNormsS->GetBin(1,ptbin+1));
      norm2S = histoNormsS->GetBinContent(histoNormsS->GetBin(3,ptbin+1));
    }
    else
    {
      norm0 = histoNorms->GetBinContent(histoNorms->GetBin(1,ptbin+1));
      norm2 = histoNorms->GetBinContent(histoNorms->GetBin(3,ptbin+1));
      normB = bPtNorms[ptbin]->GetBinContent(1);
      normC = cPtNorms[ptbin]->GetBinContent(1);
      if(doJpsi) normCB = cbPtNorms[ptbin]->GetBinContent(1);
      norm0S = histoNormsS->GetBinContent(histoNormsS->GetBin(1,ptbin+1));
      norm2S = histoNormsS->GetBinContent(histoNormsS->GetBin(3,ptbin+1));
    }
    
//    cout << ptbin << "; 0: " << norm0 << " 2: " << norm2 << endl;
    
    if( norm0 == 0)
    {
      cout << ptbin << " For this bin, some norm0 = 0" << endl;
      continue;
    }
    if( norm2 == 0 )
    {
      cout << ptbin << " For this bin, some norm2 = 0" << endl;
      continue;
    }
    if( normB == 0 )
    {
      cout << ptbin << " For this bin, some normB = 0" << endl;
      continue;
    }
    if( normC == 0)
    {
      cout << ptbin << " For this bin, some normC = 0" << endl;
      continue;
    }
    plotbin = ptbin;
    // Init necessary plotting tools
    lbl[ptbin] = new TPaveText(.17,.15,.35,.21,Form("NB NDC%i",ptbin));
    sprintf(textLabel,"%.1f < P_{T} < %.1f",lowpt[ptbin],highpt[ptbin]);
    lbl[ptbin]->AddText(textLabel);
    lbl[ptbin]->SetFillColor(kWhite);
    
    projB[ptbin] = (TH1D*)fT->Get(Form("hdPhiRawbe_%i",ptbin));
    projC[ptbin] = (TH1D*)fT->Get(Form("hdPhiRawce_%i",ptbin));
    projData0[ptbin]= (TH1D*)fD->Get(Form("NPEhDelPhi_0_%i",ptbin));
    projData2[ptbin]= (TH1D*)fD->Get(Form("NPEhDelPhi_2_%i",ptbin));
    projData0S[ptbin]= (TH1D*)fS->Get(Form("NPEhDelPhi_0_%i",ptbin));
    projData2S[ptbin]= (TH1D*)fS->Get(Form("NPEhDelPhi_2_%i",ptbin));
    
    pileupCorrect[ptbin][0] = (TH1D*)fD->Get(Form("pileupCorrection_%i_0",ptbin));
    pileupCorrect[ptbin][1] = (TH1D*)fD->Get(Form("pileupCorrection_%i_2",ptbin));
    pileupCorrectS[ptbin][0] = (TH1D*)fS->Get(Form("pileupCorrection_%i_0",ptbin));
    pileupCorrectS[ptbin][1] = (TH1D*)fS->Get(Form("pileupCorrection_%i_2",ptbin));
    
    pileupCorrect[ptbin][0]->Sumw2(); pileupCorrect[ptbin][1]->Sumw2();
    projData0[ptbin]->Sumw2(); projData2[ptbin]->Sumw2();
    pileupCorrectS[ptbin][0]->Sumw2(); pileupCorrectS[ptbin][1]->Sumw2();
    projData0S[ptbin]->Sumw2(); projData2S[ptbin]->Sumw2();
    
    // To test systematic shift in pileup subtraction
    if(doPileup){
      TH1D* changeHist;
      for(int i = 0; i < 2; i++){
        changeHist = pileupCorrectS[ptbin][i];
        //        changeHist->SetMarkerStyle(20);
        TH1D* beforeShift = (TH1D*) changeHist->Clone();
        beforeShift->SetLineColor(kBlack);
        beforeShift->SetMarkerColor(kBlack);
        if(i == 0)
          beforeShift->SetTitle("Pileup Correction Systematic HT0/HT2");
        beforeShift->GetYaxis()->SetTitle("1/N dN/d(#Delta#phi)");
        TAxis* ax = changeHist->GetXaxis();
        for(int chn = ax->GetFirst(); chn <= ax->GetLast(); chn++)
        {
          double current = changeHist->GetBinContent(chn);
          double error = changeHist->GetBinError(chn);
          changeHist->SetBinContent(chn, current+error);
        }
        //        changeHist->SetTitle("pt ");
        changeHist->SetLineColor(kRed);
        changeHist->SetMarkerColor(kBlack);
        pileupCorrectS[ptbin][i] = (TH1D*)changeHist->Clone(Form("UppileupCorrection_%i_%i",ptbin,i));
      }
    }
    
    // Do any rebinning
    Int_t RB = 2;
    projB[ptbin]->Rebin(RB);
    projC[ptbin]->Rebin(RB);
    if(doJpsi)projCB[ptbin]->Rebin(RB);
    projData0[ptbin]->Rebin(RB);
    projData2[ptbin]->Rebin(RB);
    projData0S[ptbin]->Rebin(RB);
    projData2S[ptbin]->Rebin(RB);
    
    pileupCorrect[ptbin][0]->Rebin(RB);
    pileupCorrect[ptbin][1]->Rebin(RB);
    pileupCorrectS[ptbin][0]->Rebin(RB);
    pileupCorrectS[ptbin][1]->Rebin(RB);

    
    
    // Assume symmetry for templates, use all statistics on one side, then wrap about 0
    if(kSymmetrize)
    {
      for(int q=projC[ptbin]->GetXaxis()->GetFirst(); q < projC[ptbin]->GetXaxis()->FindBin(0.0); q++)
      {
        projC[ptbin]->Sumw2(0);
        double binDPhi = projC[ptbin]->GetXaxis()->GetBinCenter(q);  // get dPhi (should be negative)
        double binVal  = projC[ptbin]->GetBinContent(q); // get number of counts in -dPhi
        int posDPhi = projC[ptbin]->GetXaxis()->FindBin(abs(binDPhi)); // get +dPhi bin
        double binVal2 = projC[ptbin]->GetBinContent(posDPhi); // get number of counts in dPhi
        projC[ptbin]->SetBinContent(q,binVal+binVal2); // Set negative dPhi to combination of dPhi contents
        projC[ptbin]->SetBinContent(posDPhi,binVal+binVal2); // Set positive dPhi to combination of dPhi contents
        projC[ptbin]->Sumw2(1);
        
        projB[ptbin]->Sumw2(0);
        binDPhi = projB[ptbin]->GetXaxis()->GetBinCenter(q);  // get dPhi (should be negative)
        binVal  = projB[ptbin]->GetBinContent(q); // get number of counts in -dPhi
        posDPhi = projB[ptbin]->GetXaxis()->FindBin(abs(binDPhi)); // get +dPhi bin
        binVal2 = projB[ptbin]->GetBinContent(posDPhi); // get number of counts in dPhi
        projB[ptbin]->SetBinContent(q,binVal+binVal2); // Set negative dPhi to combination of dPhi contents
        projB[ptbin]->SetBinContent(posDPhi,binVal+binVal2); // Set positive dPhi to combination of dPhi contents
        projB[ptbin]->Sumw2(1);
        
        if(doJpsi){
          projCB[ptbin]->Sumw2(0);
          binDPhi = projCB[ptbin]->GetXaxis()->GetBinCenter(q);  // get dPhi (should be negative)
          binVal  = projCB[ptbin]->GetBinContent(q); // get number of counts in -dPhi
          posDPhi = projCB[ptbin]->GetXaxis()->FindBin(abs(binDPhi)); // get +dPhi bin
          binVal2 = projCB[ptbin]->GetBinContent(posDPhi); // get number of counts in dPhi
          projCB[ptbin]->SetBinContent(q,binVal+binVal2); // Set negative dPhi to combination of dPhi contents
          projCB[ptbin]->SetBinContent(posDPhi,binVal+binVal2); // Set positive dPhi to combination of dPhi contents
          projCB[ptbin]->Sumw2(1);
        }
      }
    }

    
    // Clone to make plots without effecting fits
    plotD0[ptbin] = (TH1D*) projData0[ptbin]->Clone();
    plotD2[ptbin] = (TH1D*) projData2[ptbin]->Clone();
    plotD0S[ptbin] = (TH1D*) projData0S[ptbin]->Clone();
    plotD2S[ptbin] = (TH1D*) projData2S[ptbin]->Clone();
    plotB[ptbin]  = (TH1D*) projB[ptbin]->Clone();
    plotC[ptbin]  = (TH1D*) projC[ptbin]->Clone();
    
    // Set features that are the same in plots
    projData0[ptbin]->SetLineColor(kBlue);
    projData2[ptbin]->SetLineColor(kGreen+3);
    projB[ptbin]->SetLineColor(kRed);
    projC[ptbin]->SetLineColor(kBlack);
    projC[ptbin]->GetXaxis()->SetRangeUser(anaConst::lowPhi,anaConst::highPhi);
    plotD0[ptbin]->SetLineColor(kBlue);
    plotD2[ptbin]->SetLineColor(kGreen+3);
    plotD0[ptbin]->SetMarkerStyle(20);
    plotD0[ptbin]->SetMarkerColor(kBlue);
    plotD0[ptbin]->SetMarkerSize(0.4);
    plotB[ptbin]->SetLineColor(kRed);
    plotC[ptbin]->SetLineColor(kBlack);
    plotC[ptbin]->GetXaxis()->SetRangeUser(anaConst::lowPhi,anaConst::highPhi);
    
    projData0S[ptbin]->SetLineColor(kBlue);
    projData2S[ptbin]->SetLineColor(kGreen+3);
    plotD0S[ptbin]->SetLineColor(kBlue);
    plotD2S[ptbin]->SetLineColor(kGreen+3);
    plotD0S[ptbin]->SetMarkerStyle(20);
    plotD0S[ptbin]->SetMarkerColor(kBlue);
    plotD0S[ptbin]->SetMarkerSize(0.4);
    
    combData[ptbin] = (TH1D*) projData0[ptbin]->Clone();
    combData[ptbin] -> Add(projData2[ptbin]);
    combData[ptbin]->SetLineColor(kBlue);
    combData[ptbin]->SetMarkerStyle(20);
    combData[ptbin]->SetMarkerColor(kBlue);
    combData[ptbin]->SetMarkerSize(0.4);
    combData[ptbin]->SetTitle("");
    
    // Normalize
    projB[ptbin]     -> Scale(1./normB);
    projC[ptbin]     -> Scale(1./normC);
    projData0[ptbin] -> Scale(1./norm0);
    projData2[ptbin] -> Scale(1./norm2);
    plotD0[ptbin]    -> Scale(1./norm0);
    plotD2[ptbin]    -> Scale(1./norm2);
    plotB[ptbin]     -> Scale(1./normB);
    plotC[ptbin]     -> Scale(1./normC);
    combData[ptbin]  -> Scale(1./(norm0+norm2));
    projData0S[ptbin] -> Scale(1./norm0S);
    projData2S[ptbin] -> Scale(1./norm2S);
    plotD0S[ptbin]    -> Scale(1./norm0S);
    plotD2S[ptbin]    -> Scale(1./norm2S);
    if(doJpsi){
       projCB[ptbin]->Scale(1./normCB); // normalized jpsi from pythia
     }
    
    // Subtract Pileup correction (data only)
    projData0[ptbin]->Add(pileupCorrect[ptbin][0],-1);
    projData2[ptbin]->Add(pileupCorrect[ptbin][1],-1);
    projData0S[ptbin]->Add(pileupCorrectS[ptbin][0],-1);
    projData2S[ptbin]->Add(pileupCorrectS[ptbin][1],-1);
    
    //=============================================================
    // here, use formular to subtract the jpsi con. from data !!! zyj
//    if(doJpsi){
////      auto tmp = 0.14*2*2;
////      if(ptbin>2) tmp = 0.06*2*2;
//      auto tmp = hjpsiconTot[ptbin];
//      projCB[ptbin]->Scale(tmp);
//      projData0S[ptbin]->Add(projCB[ptbin], -1);
//      projData2S[ptbin]->Add(projCB[ptbin], -1);
//      projData0S[ptbin]->Scale(1./(1.-tmp));
//      projData2S[ptbin]->Scale(1./(1.-tmp));
//    }
    //=============================================================
    
    projB[ptbin]     -> Scale(1, "width");
    projC[ptbin]     -> Scale(1, "width");
    projData0[ptbin] -> Scale(1, "width");
    projData2[ptbin] -> Scale(1, "width");
    plotD0[ptbin]    -> Scale(1, "width");
    plotD2[ptbin]    -> Scale(1, "width");
    plotB[ptbin]     -> Scale(1, "width");
    plotC[ptbin]     -> Scale(1, "width");
    combData[ptbin]  -> Scale(1, "width");
    projData0S[ptbin] -> Scale(1, "width");
    projData2S[ptbin] -> Scale(1, "width");
    plotD0S[ptbin]    -> Scale(1, "width");
    plotD2S[ptbin]    -> Scale(1, "width");
    if(doJpsi){
      projCB[ptbin]->Scale(1, "width"); // normalized jpsi from pythia
    }
    //=============================================================
    
    // Draw Templates on own plots
    if(ptbin+1 <= 9) deltaPhi->cd(plotbin+1);
    if(ptbin+1 > 9) deltaPhi2->cd(ptbin-8); // in case of more pt bin
    plotC[ptbin]->GetYaxis()->SetRangeUser(plotLow[ptbin],plotHigh[ptbin]);
    plotC[ptbin]->SetMarkerStyle(20);
    plotC[ptbin]->SetMarkerSize(0.6);
    plotB[ptbin]->SetMarkerStyle(21);
    plotB[ptbin]->SetMarkerSize(0.6);
    plotB[ptbin]->SetMarkerColor(kRed);
    plotC[ptbin]->GetXaxis()->SetTitle("#Delta#phi_{NPE-h} (rad)");
    plotC[ptbin]->GetYaxis()->SetTitle("#frac{1}{N_{NPE}} #frac{dN}{d(#Delta#phi)}");
    plotC[ptbin]->GetXaxis()->SetLabelSize(0.05);
    plotC[ptbin]->GetYaxis()->SetLabelSize(0.05);
    plotC[ptbin]  -> Draw("");
    plotB[ptbin]  -> Draw("same");
    //plotD0[ptbin] -> Draw("same");
    //plotD2[ptbin] -> Draw("same");
    lbl[ptbin]    -> Draw("same");
    
    TLegend* leg = new TLegend(0.65,0.6,0.85,0.85);
    leg->SetTextSize(.06);
    leg->AddEntry(plotB[ptbin],"b#bar{b}#rightarrow NPE","lp");
    leg->AddEntry(plotC[ptbin],"c#bar{c}#rightarrow NPE","lp");
    //leg->AddEntry(projData0[ptbin],"HT0","lpe");
    //leg->AddEntry(projData2[ptbin],"HT2","lpe");
    leg->Draw();
    
    /////////////////////
    // Do the actual fits
    /////////////////////
    //=======================================================================================

    currentPtBin = ptbin;
    cout << "!!!!!!! HT0 ptbin: " << highpt[ptbin] << "-" << lowpt[ptbin] <<" !!!!!!!"<< endl;
    TMinuit* gMinuit = new TMinuit(2);
    TMinuit* gMinuitS = new TMinuit(2);

    gMinuit->SetFCN(chi2_0);
    currentPtBin = ptbin;
    //    if(!oneParamFit) doFit(gMinuit,p01[ptbin], e01U[ptbin],e01D[ptbin]);
    ////    doFit(gMinuit,p01[ptbin],p00[ptbin],e01[ptbin],e00[ptbin]);
    //    else
    doFit(gMinuit,p01[ptbin],p00[ptbin],e01U[ptbin],e00U[ptbin],e01D[ptbin],e00D[ptbin]);
    
    if(oneParamFit && bUp) FITPARAS = p00[ptbin]+e00U[ptbin];
    if(oneParamFit && bDown) FITPARAS = p00[ptbin]-e00D[ptbin];
    gMinuitS->SetFCN(chi2_0S);
    if(oneParamFit) doFit(gMinuitS,p01S[ptbin], e01US[ptbin],e01DS[ptbin]);
    else doFit(gMinuitS,p01S[ptbin],p00S[ptbin],e01US[ptbin],e00US[ptbin],e01DS[ptbin],e00DS[ptbin]);
    //    doFit(gMinuit,p01S[ptbin],p00S[ptbin],e01S[ptbin],e00S[ptbin]);
    
    //=======================================================================================
    // assign to plotting variables
    if(highpt[ptbin] < 5)
    {
      pT[ptbin] = (lowpt[ptbin]+highpt[ptbin])/2.;
      dx[plotCount0] = 0.;
      ptOFF1[plotCount0] = pT[ptbin];
      //      ptOFF1[plotCount0] = pT[ptbin]-0.1;
      Rb0[plotCount0] = p01[ptbin];///(p01[ptbin]+p00[ptbin]);
      eb0U[plotCount0] = e01U[ptbin];
      eb0D[plotCount0] = e01D[ptbin];
      //      eb0[plotCount0] = e01[ptbin];
      Rb0S[plotCountSys] = p01S[ptbin];///(p01[ptbin]+p00[ptbin]);
      eb0US[plotCountSys] = e01US[ptbin];
      eb0DS[plotCountSys] = e01DS[ptbin];
      //      eb0S[plotCount0] = e01S[ptbin];
      
      A0[plotCountSys] = p00[ptbin];///(p01[ptbin]+p00[ptbin]);
      //      eA0[plotCountSys] = e00[ptbin];
      eA0U[plotCount0] = e00U[ptbin];
      eA0D[plotCount0] = e00D[ptbin];
      
      
      A0S[plotCountSys] = p00S[ptbin];///(p01[ptbin]+p00[ptbin]);
      eA0US[plotCountSys] = e00US[ptbin];
      eA0DS[plotCountSys] = e00DS[ptbin];
      //      eA0S[plotCountSys] = e00S[ptbin];
      if(doPythia || doFitRange){
        Double_t x,y;
        grd->GetPoint(plotCount0, x, y);
        Rb0[plotCount0] = y;
        eb0U[plotCount0] = grd->GetErrorYhigh(plotCount0);;
        eb0D[plotCount0] = grd->GetErrorYlow(plotCount0);
      }
      
//      sysChangeUp[plotCountSys] = sqrt(abs(eb0US[plotCountSys]-eb0U[plotCountSys]));
//      sysChangeDown[plotCountSys] = sqrt(abs(eb0DS[plotCountSys]-eb0D[plotCountSys]));
      sysChangeUp[plotCountSys] = sqrt(abs(eb0US[plotCountSys]*eb0US[plotCountSys]-eb0U[plotCountSys]*eb0U[plotCountSys]));
      sysChangeDown[plotCountSys] = sqrt(abs(eb0DS[plotCountSys]*eb0DS[plotCountSys]-eb0D[plotCountSys]*eb0D[plotCountSys]));
//      cout<<eb0US[plotCountSys]<<"                    error                 "<<eb0U[plotCountSys]<<endl;
      sysChange[plotCountSys] = 100.*(Rb0S[plotCountSys]-Rb0[plotCount0])/Rb0[plotCount0];
      sysChangeAbs[plotCountSys] = abs(Rb0S[plotCountSys]-Rb0[plotCount0]);
      cout<<FileNameR<<"  HT0 ptbin:"<<lowpt[ptbin]<<" - "<<highpt[ptbin]<<"   perc. change:"<<sysChange[plotCountSys] <<endl;

      fprintf(pFile,"%d %.3f %.3f %.3f %3f %3f %3f\n",plotCount0,Rb0[plotCount0],Rb0S[plotCountSys],abs(Rb0S[plotCountSys]-Rb0[plotCount0]), sysChangeUp[plotCountSys],sysChangeDown[plotCountSys], sysChange[plotCountSys]);
      
//      fprintf(pFile,"%d %.3f %.3f %.3f \n",plotCount0,Rb0[plotCount0],Rb0S[plotCountSys],sysChange[plotCountSys]);
      
      pileC->cd(plotCount0+1);
      //      beforeShift
      //      if(ptbin == 0)pileupCorrect[ptbin][0]->SetTitle("HT0");
      //      else
      pileupCorrect[ptbin][0]->SetTitle(" ");
      //      pileupCorrect[ptbin][0]->SetMarkerColor(kBlack);
      //      pileupCorrect[ptbin][0]->SetLineColor(kBlack);
//      pileupCorrect[ptbin][0]->GetYaxis()->SetRangeUser(-0.01, 0.04);
      pileupCorrect[ptbin][0]->GetYaxis()->SetRangeUser(0., 0.01);

      pileupCorrect[ptbin][0]->Draw();
      pileupCorrectS[ptbin][0]->Draw("same");
      //      sysError[plotCountSys] = ((e01[ptbin]*e01[ptbin])/(p01[ptbin]*p01[ptbin]) + (e01S[ptbin]*e01S[ptbin])/(p01S[ptbin]*p01S[ptbin]))*sysChange[plotCountSys];
      ptSys[plotCountSys] = pT[ptbin];
      plotCount0++;
      plotCountSys++;
      
    }
    
    // Plot results
//    fitResult0->cd(ptbin+1);

    TLine *l1=new TLine(-3.14,1,3.14,1);
    l1->SetLineColor(4);
    l1->SetLineWidth(2.5);
    l1->SetLineStyle(2);

    TH1D* dClone = (TH1D*) projData0S[ptbin]->Clone();
    TH1D* cClone = (TH1D*) projC[ptbin]->Clone();
    TH1D* cClone2 = (TH1D*) projC[ptbin]->Clone();
    TH1D* bClone = (TH1D*) projB[ptbin]->Clone();
    TH1D* bClone2 = (TH1D*) projB[ptbin]->Clone();
    stat[0][ptbin] = new TPaveText(.4,.75,.85,.85,Form("NB NDC%i",ptbin));
    //    sprintf(statLabel,"Chi2/NDF: %.2f/%.0f",curChi2,curNDF);
    sprintf(statLabel,"Chi2/NDF: %.2f/%.0f; rB: %.2f",curChi2,curNDF,p01S[ptbin]);
    stat[0][ptbin]->InsertText(statLabel);
    stat[0][ptbin]->InsertText(textLabel);
    stat[0][ptbin]->SetFillColor(kWhite);
    if(!oneParamFit) FITPARAS = p00S[ptbin];
    cClone->Scale((1.-p01S[ptbin])*FITPARAS); bClone->Scale(p01S[ptbin]*FITPARAS); // scale by contribution param
    cClone2->Scale((1.-p01S[ptbin])*FITPARAS); bClone2->Scale(p01S[ptbin]*FITPARAS);
    cClone->Add(bClone);
    //cClone->Scale(dClone->GetMaximum()/cClone->GetMaximum());
    dClone->GetXaxis()->SetRangeUser(anaConst::lowPhi,anaConst::highPhi);
    dClone->GetYaxis()->SetRangeUser(plotLow[ptbin],plotHigh[ptbin]);
    dClone->SetMarkerStyle(20);
    dClone->SetMarkerColor(kBlue);
    cClone->SetMarkerStyle(24);
    dClone->SetMarkerSize(0.6);
    cClone->SetMarkerSize(0.6);
    dClone->GetXaxis()->SetLabelSize(0.05);
    dClone->GetYaxis()->SetLabelSize(0.05);
    cClone2->SetLineColor(kBlack);
    bClone2->SetLineColor(kRed);
    if(ptbin<2){
      fitResult02->cd(ptbin+1);
      dClone->Draw();
      cClone->Draw("same");
      cClone2->Draw("same hist");
      bClone2->Draw("same hist");
      stat[0][ptbin]->Draw("same");
      
      auto hFit_Ratio=(TH1D *) cClone->Clone(Form("Ratio_%i",ptbin));
      hFit_Ratio->SetLineColor(2);
      hFit_Ratio->SetMarkerColor(2);
      hFit_Ratio->SetMarkerSize(0.4);
      hFit_Ratio->SetMarkerStyle(20);
      hFit_Ratio->Divide(dClone);
      hFit_Ratio->GetXaxis()->SetTitle("#Delta_{#phi_{eh}}");
      hFit_Ratio->GetYaxis()->SetTitle("Fit/Data");
      hFit_Ratio->GetYaxis()->CenterTitle();
      hFit_Ratio->GetYaxis()->SetRangeUser(0.61,1.51);
      hFit_Ratio->SetTitle(" ");
      fitRatio->cd(ptbin+1);
      hFit_Ratio->Fit(Form("hfit_%d", ptbin), "R+");
      hFit_Ratio->Draw();
      sprintf(buf,"pol0 fit: %4.3f #pm %4.3f", hfit[ptbin]->GetParameter(0), hfit[ptbin]->GetParError(0));
      drawLatex(0.12,0.76,buf,62,0.07,4);
      l1->Draw("same");
//      lbl[ptbin]->Draw("same");
    }
    
    //=======================================================================================
    cout << "!!!!!!! HT2 ptbin: " <<  highpt[ptbin] << "-" << lowpt[ptbin] <<" !!!!!!!"<< endl;
    gMinuit->SetFCN(chi2_2);
    //    if(!oneParamFit) doFit(gMinuit,p21[ptbin], e21U[ptbin],e21D[ptbin]);
    //
    ////    doFit(gMinuit,p21[ptbin],p20[ptbin],e21[ptbin],e20[ptbin]);
    //    else
    doFit(gMinuit,p21[ptbin],p20[ptbin],e21U[ptbin],e20U[ptbin],e21D[ptbin],e20D[ptbin]);
  
    if(oneParamFit && bUp) FITPARAS = p20[ptbin]+e20U[ptbin];
    if(oneParamFit && bDown) FITPARAS = p20[ptbin]-e20D[ptbin];
    gMinuitS->SetFCN(chi2_2S);

    //    doFit(gMinuit,p21S[ptbin],p20S[ptbin],e21S[ptbin],e20S[ptbin]);
    if(oneParamFit) doFit(gMinuitS,p21S[ptbin], e21US[ptbin],e21DS[ptbin]);
    else doFit(gMinuitS,p21S[ptbin],p20S[ptbin],e21US[ptbin],e20US[ptbin],e21DS[ptbin],e20DS[ptbin]);
    
    // assign to plotting variables
    if(highpt[ptbin] > 4.6)
    {
      
      pT[ptbin] = (lowpt[ptbin]+highpt[ptbin])/2.;
      ptOFF1[plotCount0] = pT[ptbin];
      Rb0[plotCount0] = p21[ptbin];///(p21[ptbin]+p20[ptbin]);
      eb0U[plotCount0] = e21U[ptbin];
      eb0D[plotCount0] = e21D[ptbin];
      
      //      eb0[plotCount0] = e21[ptbin];
      
      Rb0S[plotCountSys] = p21S[ptbin];///(p21[ptbin]+p20[ptbin]);
      eb0US[plotCountSys] = e21US[ptbin];
      eb0DS[plotCountSys] = e21DS[ptbin];
      
      //      eb0S[plotCount2] = e21S[ptbin];
      
      //      ptOFF2[plotCount2] = pT[ptbin]+0.1;
      //      Rb2[plotCount2] = p21[ptbin];///(p21[ptbin]+p20[ptbin]);
      //      eb2[plotCount2] = e21[ptbin];
      //      Rb2S[plotCount2] = p21S[ptbin];///(p21[ptbin]+p20[ptbin]);
      //      eb2S[plotCount2] = e21S[ptbin];
      A0[plotCount0] = p20[ptbin];///(p21[ptbin]+p22[ptbin]);
      eA0U[plotCount0] = e20U[ptbin];
      eA0D[plotCount0] = e20D[ptbin];
      
      //      eA0[plotCountSys] = e20[ptbin];
      A0S[plotCountSys] = p20S[ptbin];///(p21[ptbin]+p22[ptbin]);
      eA0US[plotCountSys] = e20US[ptbin];
      eA0DS[plotCountSys] = e20DS[ptbin];
      
      //      eA0S[plotCountSys] = e20S[ptbin];
//      cout<<FileNameR<<"  "<<Rb0S[plotCountSys]<<"    "<<Rb0[plotCount0]<<endl;
      if(doPythia || doFitRange){
        Double_t x,y;
        grd->GetPoint(plotCount0, x, y);
        Rb0[plotCount0] = y;
        eb0U[plotCount0] = grd->GetErrorYhigh(plotCount0);;
        eb0D[plotCount0] = grd->GetErrorYlow(plotCount0);
      }
      

      sysChangeUp[plotCountSys] = sqrt(abs(eb0US[plotCountSys]*eb0US[plotCountSys]-eb0U[plotCountSys]*eb0U[plotCountSys]));
      sysChangeDown[plotCountSys] = sqrt(abs(eb0DS[plotCountSys]*eb0DS[plotCountSys]-eb0D[plotCountSys]*eb0D[plotCountSys]));
      sysChange[plotCountSys] = 100.*(Rb0S[plotCountSys]-Rb0[plotCount0])/Rb0[plotCount0];
      sysChangeAbs[plotCountSys] = abs(Rb0S[plotCountSys]-Rb0[plotCount0]);

      cout<<FileNameR<<"  HT2 ptbin:"<<lowpt[ptbin]<<" - "<<highpt[ptbin]<<"  perc. change :"<<sysChange[plotCountSys] <<endl;
      fprintf(pFile,"%d %.3f %.3f %.3f %3f %3f %3f\n",plotCount0,Rb0[plotCount0],Rb0S[plotCountSys],abs(Rb0S[plotCountSys]-Rb0[plotCount0]), sysChangeUp[plotCountSys],sysChangeDown[plotCountSys], sysChange[plotCountSys]);
      
      pileC->cd(plotCount0+1);
      //      beforeShift
      //      cout<<pileupCorrect[ptbin][0]->GetBinContent(100)<<"    pileup correction factor"<<endl;
      pileupCorrect[ptbin][1]->SetTitle(" ");
      //      pileupCorrect[ptbin][1]->SetMarkerColor(kBlack);
      //      pileupCorrect[ptbin][1]->SetLineColor(kBlack);
//      pileupCorrect[ptbin][1]->GetYaxis()->SetRangeUser(-0.01, 0.04);
      pileupCorrect[ptbin][1]->GetYaxis()->SetRangeUser(0., 0.01);

      pileupCorrect[ptbin][1]->Draw();
      pileupCorrectS[ptbin][1]->Draw("same");
      //      beforeShift->Draw();
      //      pileupCorrectS->Draw("same");
      
      //      sysError[plotCountSys] = ((e21[ptbin]*e21[ptbin])/(p21[ptbin]*p21[ptbin]) + (e21S[ptbin]*e21S[ptbin])/(p21S[ptbin]*p21S[ptbin]))*sysChange[plotCountSys];;
      ptSys[plotCountSys] = pT[ptbin];
      plotCount0++;
      plotCountSys++;
      //      plotCount2++;
      //      plotCountSys++;
    }
    
    // Plot results
    fitResult2->cd(ptbin+1);
    dClone = (TH1D*) projData2S[ptbin]->Clone();
    cClone = (TH1D*) projC[ptbin]->Clone();
    bClone = (TH1D*) projB[ptbin]->Clone();
    cClone2 = (TH1D*) projC[ptbin]->Clone();
    bClone2 = (TH1D*) projB[ptbin]->Clone();
    stat[2][ptbin] = new TPaveText(.4,.75,.85,.85,Form("NB NDC%i",ptbin));
    //    sprintf(statLabel,"Chi2/NDF: %.2f/%.2f",curChi2,curNDF);
    sprintf(statLabel,"Chi2/NDF: %.2f/%.0f; rB: %.2f",curChi2,curNDF,p21S[ptbin]);
    stat[2][ptbin]->InsertText(statLabel);
    stat[2][ptbin]->InsertText(textLabel);
    stat[2][ptbin]->SetFillColor(kWhite);
    if(!oneParamFit) FITPARAS = p20S[ptbin];
    cClone->Scale((1.-p21S[ptbin])*FITPARAS); bClone->Scale(p21S[ptbin]*FITPARAS); // scale by contribution param
    cClone2->Scale((1.-p21S[ptbin])*FITPARAS); bClone2->Scale(p21S[ptbin]*FITPARAS); // scale by contribution param
    cClone->Add(bClone);
    // cClone->Scale(dClone->GetMaximum()/cClone->GetMaximum());
    dClone->GetXaxis()->SetRangeUser(anaConst::lowPhi,anaConst::highPhi);
    dClone->GetYaxis()->SetRangeUser(plotLow[ptbin],plotHigh[ptbin]);
    dClone->SetMarkerStyle(20);
    cClone->SetMarkerStyle(24);
    dClone->SetMarkerColor(kGreen+3);
    dClone->SetMarkerSize(0.6);
    cClone->SetMarkerSize(0.6);
    dClone->GetXaxis()->SetLabelSize(0.05);
    dClone->GetYaxis()->SetLabelSize(0.05);
    cClone2->SetLineColor(kBlack);
    bClone2->SetLineColor(kRed);
    if(ptbin>1 && ptbin<6){
      fitResult02->cd(ptbin+1);
      dClone->Draw();
      cClone->Draw("same");
      cClone2->Draw("same hist");
      bClone2->Draw("same hist");
      stat[2][ptbin]->Draw("same");
      
      auto hFit_Ratio=(TH1D *) cClone->Clone(Form("Ratio_%i",ptbin));
      hFit_Ratio->SetLineColor(2);
      hFit_Ratio->SetMarkerColor(2);
      hFit_Ratio->SetMarkerSize(0.4);
      hFit_Ratio->SetMarkerStyle(20);
      hFit_Ratio->Divide(dClone);
      hFit_Ratio->GetYaxis()->SetRangeUser(0.41,1.81);
      if(ptbin == 2)hFit_Ratio->GetYaxis()->SetRangeUser(0.61,1.51);
      hFit_Ratio->GetXaxis()->SetTitle("#Delta_{#phi_{eh}}");
      hFit_Ratio->GetYaxis()->SetTitle("Fit/Data");
      hFit_Ratio->GetYaxis()->CenterTitle();
      hFit_Ratio->SetTitle(" ");
      fitRatio->cd(ptbin+1);
      hFit_Ratio->Fit(Form("hfit_%d", ptbin), "R+");;
      hFit_Ratio->Draw();
      sprintf(buf,"pol0 fit: %4.3f #pm %4.3f", hfit[ptbin]->GetParameter(0), hfit[ptbin]->GetParError(0));
      drawLatex(0.12,0.76,buf,62,0.07,4);
      l1->Draw("same");
    }
    
    //    lbl[ptbin]->Draw("same");
//    cout << "!!!!!!! HTC ptbin: " <<  highpt[ptbin] << "-" << lowpt[ptbin] <<" !!!!!!!"<< endl;
    //    gMinuit->SetFCN(chi2_C);
    //    doFit(gMinuit,pC1[ptbin],pC0[ptbin],eC1[ptbin],eC0[ptbin]);
    //    // assign to plotting variables
    //    pT[ptbin] = (lowpt[ptbin]+highpt[ptbin])/2.;
    //    RbC[plotCount] = pC1[ptbin];///(p21[ptbin]+p20[ptbin]);
    //    ebC[plotCount] = eC1[ptbin];
    //    plotCount++;
  }
  
  fclose(pFile);
  
  // Get FONLL Calc
  //  Int_t l=0;
  char line[1000];
  //  Float_t xF[100],yF[100],minF[100],maxF[100];
  //  ifstream fp("/Users/zach/Research/pythia/200GeVTemplate/FONLL.txt",ios::in);
  //  while (!fp.eof()){
  //    fp.getline(line,1000);
  //    sscanf(line,"%f %f %f %f",&xF[l],&yF[l],&minF[l],&maxF[l]);
  //    //  printf("L: %f %f\n",xF[l],yF[l]);
  //    l++;
  //  }
  //  fp.close();
  
  // Get Previous Analysis
  Int_t p=0;
  Float_t xP[100],yP[100],dyP[100],dyPSL[100],dyPSH[100],dxPS[100];
  ifstream fp1("../../ZWMiller_online_offline/Zach_fromZhenyu/run12NPEhResults/getPointsFromImage/Run6Result.txt",ios::in);
  while (!fp1.eof()){
    fp1.getline(line,1000);
    sscanf(line,"%f %f %f %f %f",&xP[p],&yP[p],&dyP[p],&dyPSL[p],&dyPSH[p]);
    // printf("L: %f %f\n",xF[l],yF[l]);
    dyPSL[p] = yP[p]-dyPSL[p];   // convert from max/min of error bar to value of
    dyPSH[p] = dyPSH[p] - yP[p]; // error bar for plotting
    dxPS[p] = 0.15;
    xP[p] +=0.2;
    p++;
  }
  fp1.close();
  
  //  Int_t p=0;
  //  //  Float_t xP[100],yP[100],dyP[100];
  //  Float_t xP[100],yP[100],dyP[100],dyPSL[100],dyPSH[100],dxPS[100];
  //  ifstream fp1("/Users/zach/Research/pythia/200GeVTemplate/run5_6.txt",ios::in);
  //  while (!fp1.eof()){
  //    fp1.getline(line,1000);
  //    //    sscanf(line,"%f %f %f",&xP[p],&yP[p],&dyP[p]);
  //    sscanf(line,"%f %f %f %f %f",&xP[p],&yP[p],&dyP[p],&dyPSL[p],&dyPSH[p]);
  //    // printf("L: %f %f\n",xF[l],yF[l]);
  //    dyPSL[p] = yP[p]-dyPSL[p];   // convert from max/min of error bar to value of
  //    dyPSH[p] = dyPSH[p] - yP[p]; // error bar for plotting
  //    dxPS[p] = 0.15;
  //    p++;
  //  }
  //  fp1.close();
  
  //cout << "at bottom contrib plot" << endl;
  TCanvas* c1  = new TCanvas("c1","Bottom Contribution",150,0,1150,1000);
  //  TGraphErrors *gr0     = new TGraphErrors(plotCount0-1,ptOFF1,Rb0,dx,eb0);
  //  TGraphErrors *gr2     = new TGraphErrors(plotCount2,ptOFF2,Rb2,dx,eb2);
  
  
  
  //  TGraphErrors *grC     = new TGraphErrors(plotCount,pT,RbC,dx,ebC);
  //  TGraphErrors *grF     = new TGraphErrors(l-1,xF,yF);
  //  TGraphErrors *grFmax  = new TGraphErrors(l-1,xF,maxF);
  //  TGraphErrors *grFmin  = new TGraphErrors(l-1,xF,minF);
  //  TGraphErrors *grPr    = new TGraphErrors(2,pTP,RbP,0,EbP);
  //  TGraphErrors *grPPr   = new TGraphErrors(2,pTPP,RbPP,0,EbPP);
  
  TGraphErrors *grP     = new TGraphErrors(p-1,xP,yP,0,dyP);
  //  TGraphAsymmErrors *grP = new TGraphAsymmErrors(p-1,xP,yP,dxPS,dxPS,dyP,dyP);
  
  TGraphAsymmErrors *grPS = new TGraphAsymmErrors(p-1,xP,yP,dxPS,dxPS,dyPSL,dyPSH);
  
  //  TGraphErrors *gr0     = new TGraphErrors(plotCount0-1,ptOFF1,Rb0,dx,eb0);
  TGraphAsymmErrors* gr0 = new TGraphAsymmErrors(plotCount0,ptOFF1,Rb0,dx,dx,eb0D,eb0U);
  TGraphAsymmErrors* gr0S = new TGraphAsymmErrors(plotCountSys,ptSys,Rb0S,dxS,dxS,eb0DS,eb0US);
  TGraphAsymmErrors* grA = new TGraphAsymmErrors(plotCount0,ptOFF1,A0,dx,dx,eA0D,eA0U);
  TGraphAsymmErrors* grAS = new TGraphAsymmErrors(plotCountSys,ptSys,A0S,dxS,dxS,eA0DS,eA0US);
  
  //  gr0->SetName("gMINOS");
  //  TGraphErrors *gr0S     = new TGraphErrors(plotCountSys,ptOFF1,Rb0S,dx,eb0S);
  
  //  TGraphAsymmErrors* gN0 = new TGraphAsymmErrors(plotCount0-1,ptOFF1,Scale0,dx,dx,eScale0D,eScale0U);
  //  gN0->SetName("geMINOS");
  //  TGraphErrors *gr0S     = new TGraphErrors(plotCountSys,ptOFF1,Rb0S,dx,eb0S);
  //  TGraphErrors *gr2S     = new TGraphErrors(plotCount2,ptOFF2,Rb2S,dx,eb2S);
  //  TGraphErrors *grA     = new TGraphErrors(plotCountSys,ptSys,A0,dx,eA0);
  //  TGraphErrors *grAS     = new TGraphErrors(plotCountSys,ptSys,A0S,dx,eA0S);
  
  TGraphErrors *change0     = new TGraphErrors(plotCountSys,ptSys,sysChange);
  TGraphAsymmErrors *change0_stat     = new TGraphAsymmErrors(plotCountSys,ptSys,sysChangeAbs,dx, dx, sysChangeDown,sysChangeUp);

  // TGraphErrors *change2     = new TGraphErrors(plotCount2,ptOFF2,sysChange2);
  
  //  TGraph* grshade = new TGraph(2*(l-1));
  //  grshade->SetName("shade");
  //  int n = l-1;
  //  for (int i=0;i<n;i++) {
  //    grshade->SetPoint(i,xF[i],maxF[i]);
  //    grshade->SetPoint(n+i,xF[n-i-1],minF[n-i-1]);
  //  }
  //  grshade->SetFillStyle(1001);
  //  grshade->SetFillColor(19);
  
  c1->cd(1);
  gPad->SetBottomMargin(0.15);
  gPad->SetLeftMargin(0.12);
  //
  psyst->SetLineColor(kRed);
  psyst->SetMarkerColor(kRed);
  psyst->SetFillStyle(0);
  psyst->SetLineWidth(2);
  pstat->SetLineWidth(2);
  pstat->SetMarkerStyle(20);
  pstat->SetMarkerSize(1.5);
  pstat->SetMarkerColor(kRed);
  pstat->SetLineColor(kRed);
  pstat->GetYaxis()->SetRangeUser(-0.2,1.2);
  pstat->GetXaxis()->SetRangeUser(0,12);
  
  psyst->GetYaxis()->SetRangeUser(-0.1,1.2);
  psyst->GetXaxis()->SetRangeUser(0,12);
  
  //
  grPS->SetTitle("");
  grPS->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  grPS->GetYaxis()->SetTitle("B#rightarrowNPE / Inclusive#rightarrowNPE");
  grPS->GetXaxis()->SetTitleSize(0.06);
  grPS->GetYaxis()->SetTitleSize(0.06);
  grPS->GetXaxis()->SetTitleOffset(0.95);
  grPS->GetYaxis()->SetTitleOffset(0.95);
  grPS->GetXaxis()->SetLabelSize(0.06);
  grPS->GetYaxis()->SetLabelSize(0.06);
  grPS->GetXaxis()->SetLimits(0,12);
  grPS->GetYaxis()->SetRangeUser(-0.1,1.2);
  //  grshade->SetTitle("");
  //  grshade->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  //  grshade->GetYaxis()->SetTitle("B#rightarrowNPE / Inclusive#rightarrowNPE");
  //  grshade->GetXaxis()->SetTitleSize(0.06);
  //  grshade->GetYaxis()->SetTitleSize(0.06);
  //  grshade->GetXaxis()->SetTitleOffset(0.95);
  //  grshade->GetYaxis()->SetTitleOffset(0.77);
  //  grshade->GetXaxis()->SetLabelSize(0.06);
  //  grshade->GetYaxis()->SetLabelSize(0.06);
  //  grshade->GetXaxis()->SetLimits(0,12);
  //  grshade->GetYaxis()->SetRangeUser(-0.1,1.2);
  
  //  grP->SetTitle("");
  //  grP->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  //  grP->GetYaxis()->SetTitle("B#rightarrowNPE / Inclusive#rightarrowNPE");
  //  grP->GetXaxis()->SetTitleSize(0.06);
  //  grP->GetYaxis()->SetTitleSize(0.06);
  //  grP->GetXaxis()->SetTitleOffset(0.95);
  //  grP->GetYaxis()->SetTitleOffset(0.77);
  //  grP->GetXaxis()->SetLabelSize(0.06);
  //  grP->GetYaxis()->SetLabelSize(0.06);
  gr0->SetMarkerStyle(20);
  gr0->SetMarkerSize(1.4);
  //  gr0->SetLineColor(kRed);
  //  gr0->SetMarkerColor(kRed);
  gr0->SetLineColor(kBlue);
  gr0->SetMarkerColor(kBlue);
  //    gr0->SetMarkerStyle(22);
  gr0->SetMarkerSize(1.4);
  
  if(doPythia || doFitRange){
    grd->SetMarkerStyle(20);
    grd->SetMarkerSize(1.4);
    //  gr0->SetLineColor(kRed);
    //  gr0->SetMarkerColor(kRed);
    grd->SetLineColor(kBlue);
    grd->SetMarkerColor(kBlue);
    //    gr0->SetMarkerStyle(22);
    grd->SetMarkerSize(1.4);
    gr0 = grd;
  }
  
  //  gr2->SetLineColor(kRed);
  //  gr2->SetMarkerColor(kRed);
  gr0S->SetMarkerStyle(24);
  gr0S->SetMarkerSize(1.4);
  gr0S->SetLineColor(kGreen+2);
  gr0S->SetMarkerColor(kGreen+2);
  //  gr2S->SetMarkerStyle(26);
  //  gr2S->SetMarkerSize(1.4);
  //  gr2S->SetLineColor(kMagenta);
  //  gr2S->SetMarkerColor(kMagenta);
  //  grC->SetMarkerStyle(24);
  //  grC->SetMarkerSize(1);
  //  grC->SetLineColor(kMagenta);
  //  grC->SetMarkerColor(kMagenta);
  //  grP->GetXaxis()->SetLimits(0,15);
  //  grP->GetYaxis()->SetRangeUser(0,1);
  //  grP->SetMarkerSize(1.4);
  
  grP->SetMarkerSize(2.5);
  //  grF->SetLineStyle(1);
  //  grFmax->SetLineStyle(2);
  //  grFmin->SetLineStyle(2);
  //  grP->SetMarkerStyle(33);
  grP->SetMarkerStyle(29);
  grP->SetMarkerColor(kBlack);
  grPS->SetMarkerColor(kBlack);
  grPS->SetLineColor(kBlack);
  //  grPr->SetMarkerStyle(29);
  //  grPr->SetMarkerColor(9);
  //  grPr->SetLineColor(9);
  //  grPPr->SetMarkerStyle(29);
  //  grPPr->SetMarkerColor(49);
  //  grPPr->SetLineColor(49);
  
  //  grshade->Draw("AF");
  grPS->Draw("a pe2");
  grP->Draw("same pe");
  
  //  grP->Draw("AP");
  //grC->Draw("same P");
  //  gr2->Draw("same P");
  //  grF->Draw("same");
  //  grFmax->Draw("same");
  //  grFmin->Draw("same");
  if(doPythia || doFitRange) grd->Draw("same P");
  else gr0->Draw("same P");
  
  gr0S->Draw("same P");
  pstat->Draw("same pe");
  psyst->Draw("same pe2");
  //  gr2S->Draw("same P");
  // grPr->Draw("same P");
  //grPPr->Draw("same P");
  
  TLegend* leg2 = new TLegend(0.15,0.7,0.52,0.88);
  //  leg2->SetTextSize(.05);
  leg2->SetFillStyle (0);
  leg2->SetFillColor (0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(grP,"STAR Run 6","pe");
  leg2->AddEntry(pstat,"STAR Run 12(Prelimary)","pe");
  leg2->AddEntry(gr0,"STAR Run 12(Yingjie)","pe");
  //  leg2->AddEntry(gr0,"STAR Run 12 - HT0","pe");
  //  leg2->AddEntry(gr2,"STAR Run 12 - HT2","pe");
  leg2->AddEntry(gr0S,Form("STAR Run 12, %s(Yingjie)", FileNameR),"pe");
  //  leg2->AddEntry(gr2S,"STAR Run 12 - HT2, Sys","pe");
  // leg2->AddEntry(grC,"STAR Run 12 - Combined Analysis","pe");
  //  leg2->AddEntry(grPr,"Run 12 Data, Run 5/6 Templates)","pe");
  //leg2->AddEntry(grPPr,"Run 5/6 Refit (prev Template)","pe");
  //  leg2->AddEntry(grF,"FONLL Calculation","l");
  leg2->Draw("same");
  
  TCanvas* syc = new TCanvas("syc","Systematic Changes",150,0,1150,1000);
  syc->cd(1);
  change0->SetTitle(Form("%s", FileNameR));
  change0->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  change0->GetYaxis()->SetTitle("Percent Change (%)");
  change0->GetXaxis()->SetTitleSize(0.06);
  change0->GetYaxis()->SetTitleSize(0.06);
  change0->GetXaxis()->SetTitleOffset(0.95);
  change0->GetYaxis()->SetTitleOffset(0.77);
  change0->GetXaxis()->SetLabelSize(0.05);
  change0->GetYaxis()->SetLabelSize(0.05);
  change0->GetXaxis()->SetLimits(2,15);
  change0->GetYaxis()->SetRangeUser(-50,50);
  change0->SetMarkerStyle(22);
  change0->SetMarkerSize(1.4);
  change0->SetLineColor(kRed);
  change0->SetMarkerColor(kRed);
  /* change2->SetMarkerStyle(22);
   change2->SetMarkerSize(1.4);
   change2->SetLineColor(kRed);
   change2->SetMarkerColor(kRed);*/
  change0->Draw("AP");
  //change2->Draw("same P");
  gStyle->SetOptFit(1111);
  TLine *ll = new TLine(2, 10, 15, 10);
  TLine *lln = new TLine(2, -10, 15, -10);

  ll->SetLineStyle(2);
  lln->SetLineStyle(2);
  
  ll->SetLineColor(kBlue);
  lln->SetLineColor(kBlue);
  ll->Draw("same");
  lln->Draw("same");

//  change0->Fit("pol0","Q", "", 2.5, 9);
//  TF1* fitRes = change0->GetFunction("pol0");
//  fitRes->SetLineColor(kGreen);
//  fitRes->Draw("same");
  
  TCanvas* fitA = new TCanvas("fitA","Test Fit Param A",150,0,1150,1000);
  //  if(oneParamFit){
  grA->SetName("grA");
  TExec *ex = new TExec("ex","drawtext();");
  grA->GetListOfFunctions()->Add(ex);

  fitA->cd();
  grA->SetTitle("Norm. Fit Param");
  grA->GetXaxis()->SetTitle("pT");
  grA->GetYaxis()->SetTitle("p1");
  grA->GetYaxis()->SetRangeUser(0, 3);
  grA->SetMarkerSize(1.4);
  grA->SetMarkerStyle(20);
  grA->SetMarkerColor(kRed);
  grA->Draw("AP");
  gStyle->SetOptFit(1111);
  grA->Fit("pol0","Q", "", 2,9);
  //  grA->Fit("pol0","Q");
  TF1* fitResA = grA->GetFunction("pol0");
  fitResA->Draw("same");
  //  }
  
  TCanvas* fitAS = new TCanvas("fitAS","Test Fit Param AS",150,0,1150,1000);
  if(!oneParamFit){
    fitAS->cd();
    grAS->SetTitle(Form("Norm. Fit Param(%s)", FileNameR));
    grAS->GetXaxis()->SetTitle("pT");
    grAS->GetYaxis()->SetTitle("p1");
    grAS->GetYaxis()->SetRangeUser(0, 3);
    grAS->SetMarkerSize(1.4);
    grAS->SetMarkerStyle(20);
    grAS->SetMarkerColor(kRed);
    grAS->Draw("AP");
    gStyle->SetOptFit(1111);
    //  grA->Fit("pol0","Q", "", 0, 8);
    grAS->Fit("pol0","Q");
    TF1* fitResAS = grAS->GetFunction("pol0");
    fitResAS->Draw("same");
  }
  
  // Write to Root File if open
  if(makeROOT){
    //    file3->Close();
    //    file4->Close();
    file->cd();
    grP->Write("PreviousData");
    grPS->Write("PreviousDataSys");
    //grC->Write("same P");
    //    gr2->Write("HT2");
    //    grF->Write("FONLL");
    //    grFmax->Write("FONLLmax");
    //    grFmin->Write("FONLLmin");
    gr0->Write("HT0");
//    change0->Write(Form("sysChange_%s", FileNameR));
    change0->Write("sysChange");
    change0_stat->Write("sysChange_stat");
    gr0S->Write("sys");
    grA->Write("normsmall");
    grAS->Write("normfull");

    //    grshade->Write("grshade");
    // grPr->Write("PrevTempMyData");
    //grPPr->Write("PrevTempPreData");
  }
  
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
    sprintf(tlName, "RUN 12 NPE-h   #Delta#phi Correlations");
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
    sprintf(tlName,"TEST");
    tl.DrawLatex(0.1, 0.8,tlName);
    
    // Place canvases in order
    TCanvas* temp = new TCanvas();
    sprintf(name, "FFOutput/sys/%s_%s.pdf[", FileName, FileNameR);
    temp->Print(name);
    sprintf(name, "FFOutput/sys/%s_%s.pdf", FileName, FileNameR);
    
    temp = deltaPhi;
    temp->Print(name);
//    temp = fitResult0;
//    temp->Print(name);
//    temp = fitResult2;
//    temp->Print(name);
    temp = fitResult02;
    temp->Print(name);
    temp = fitRatio;
    temp->Print(name);
    // temp = fitResultC;
    // temp->Print(name);
    temp = pileC;
    if(doPileup) temp->Print(name);
    temp = c1;
    temp->Print(name);
    temp = syc;
    temp->Print(name);
    temp = fitA;
    //    if(oneParamFit)
    temp->Print(name);
    temp = fitAS;
    if(!oneParamFit)temp->Print(name);
    
    
    sprintf(name, "FFOutput/sys/%s_%s.pdf]", FileName, FileNameR);
    temp->Print(name);
  }
  if(makeROOT)
  {
    file->Write();
    file->Close();
  }
}


void doFit(TMinuit* gMinuit, Double_t& p0, Double_t& p1, Double_t& e0U, Double_t& e1U, Double_t& e0D, Double_t& e1D)
{
  Double_t e0, e1;
  gMinuit->SetMaxIterations(50000);
  arglist[0]=1; //error definition: chi^2 change by 1 to get 1 sigma
  gMinuit->mnexcm("SET ERR",arglist,1,ierflg);
  
  //starting values
  double vstart[2]={0.1,1}; //frac
  double step[2]={0.005,0.005}; //starting step
  gMinuit->mnparm(0,"BtoNPE frac",vstart[0],step[0],0.000,1,ierflg);
  gMinuit->mnparm(1,"Scale Factor",vstart[1],step[1],0.6,2.,ierflg);
  //simple scan to get better start values
  //  gMinuit->mnexcm("SCAN",arglist,0,ierflg);
  //  cout<<"done with first scan!"<<endl;
  gMinuit->mnexcm("MIGRAD",arglist,0,ierflg);
  gMinuit->mnexcm("MINOS",arglist,0,ierflg);
  
  //minimization
  //  arglist[0]=5000; //maxcalls
  //  arglist[1]=0.5; // tolerance = 0.001*[this value]*[error def] //5.0 before
  //  gMinuit->mnexcm("MINIMIZE",arglist,2,ierflg);
  
  cout<< "done with fit! Error Flag: " << ierflg << endl;
  
  //fit results
  TString *str0 = new TString("BtoNPE frac");
  TString *str1 = new TString("Scale Factor");
  //  gMinuit->mnpout(0,*str0,p0,e0,dum1,dum2,ierflg);
  //  gMinuit->mnpout(1,*str1,p1,e1,dum1,dum2,ierflg);
  
  gMinuit->mnpout(0,*str0,p0,e0,dum1,dum2,ierflg);
  gMinuit->mnpout(1,*str1,p1,e1,dum1,dum2,ierflg);
  gMinuit->mnerrs(0, e0U, e0D, dum1, dum2);
  gMinuit->mnerrs(1, e1U, e1D, dum1, dum2);
//  cout<<e0U<<"   yjjjjjj   "<<p0<<" "<<e0D<<" "<<e1U<<" "<<e1D<<endl;
  if(e0U == 0.) e0U = 1.-p0;
  if(e0D == 0.) e0D = p0; else e0D = -e0D;
  if(e1U == 0.) e1U = 1.-p1;
  if(e1D == 0.) e1D = p1; else e1D = -e1D;
  
  //  cout << endl << endl << "rB: " << p0 << "  A: " << p1 << endl
  //  << "eB: " << e0 << " eA: " << e1 << endl << endl;
  
  //Print results
  
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
  gMinuit->mnprin(4,amin);
  
}

void doFit(TMinuit* gMinuit, Double_t& p0, Double_t& e0U,Double_t& e0D)
{
  Double_t e0, e1;
  gMinuit->SetMaxIterations(50000);
  arglist[0]=1; //error definition: chi^2 change by 1 to get 1 sigma
  gMinuit->mnexcm("SET ERR",arglist,1,ierflg);
  
  //starting values
  double vstart[2]={0.1,1}; //frac
  double step[2]={0.005,0.005}; //starting step
  gMinuit->mnparm(0,"BtoNPE frac",vstart[0],step[0],0.000,1,ierflg);
  //  gMinuit->mnparm(1,"Scale Factor",vstart[1],step[1],0.000,2,ierflg);
  //simple scan to get better start values
  //  gMinuit->mnexcm("SCAN",arglist,0,ierflg);
  //  cout<<"done with first scan!"<<endl;
//  gMinuit->FixParameter(0);
  gMinuit->mnexcm("MIGRAD",arglist,0,ierflg);
  gMinuit->mnexcm("MINOS",arglist,0,ierflg);
  
  //minimization
  //  arglist[0]=5000; //maxcalls
  //  arglist[1]=0.5; // tolerance = 0.001*[this value]*[error def] //5.0 before
  //  gMinuit->mnexcm("MINIMIZE",arglist,2,ierflg);
  
  cout<< "done with fit! Error Flag: " << ierflg << endl;
  
  //fit results
  TString *str0 = new TString("BtoNPE frac");
  TString *str1 = new TString("Scale Factor");
  gMinuit->mnpout(0,*str0,p0,e0,dum1,dum2,ierflg);
  //  gMinuit->mnpout(1,*str1,p1,e1,dum1,dum2,ierflg);
  
  //  gMinuit->mnpout(0,*str0,p0,e0,dum1,dum2,ierflg);
  //  gMinuit->mnpout(1,*str1,p1,e1,dum1,dum2,ierflg);
  gMinuit->mnerrs(0, e0U, e0D, dum1, dum2);
  //  gMinuit->mnerrs(1, e1U, e1D, dum1, dum2);
  //  cout<<e0U<<" "<<p0<<" "<<e0D<<" "<<e1U<<" "<<e1D<<endl;
  if(e0U == 0.) e0U = 1.-p0;
  if(e0D == 0.) e0D = p0; else e0D = -e0D;
  //  if(e1U == 0.) e1U = 1.-p1;
  //  if(e1D == 0.) e1D = p1; else e1D = -e1D;
  
  //  cout << endl << endl << "rB: " << p0 << "  A: " << p1 << endl
  //  << "eB: " << e0 << " eA: " << e1 << endl << endl;
  
  //Print results
  
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
  gMinuit->mnprin(4,amin);
  
}

void chi2_0(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag){
  
  Int_t ptbin = currentPtBin;
  
  if(projData0[ptbin]->GetNbinsX()!= projC[ptbin]->GetNbinsX()){
    cout<<"Warning: unequal bins! bin1 = "<< projData0[ptbin]->GetNbinsX()<<" bin2 = "<<projC[ptbin]->GetNbinsX()<<endl;
    return 0;
  }
  curChi2 = 0.;
  curNDF = 0.;
  double chiSq = 0.;
  int nDof = 0;
  
//  cout<<projData0[ptbin]->GetXaxis()->FindBin(3)<<"   xxxxx"<<projData0[ptbin]->GetXaxis()->FindBin(-3)<<"  "<<projData0[ptbin]->GetXaxis()->FindBin(1.5)<<"  "<<projData0[ptbin]->GetXaxis()->FindBin(1.75)<<projData0[ptbin]->GetBinCenter(125)<<endl;
  rangeLow  = projData0[ptbin]->GetXaxis()->FindBin(-1.*rangefit);
  rangeHigh  = projData0[ptbin]->GetXaxis()->FindBin(rangefit);

  for(int k=rangeLow;k<rangeHigh;k++){
    
    double y1  = projC[ptbin]     -> GetBinContent(k+1);
    double y2  = projB[ptbin]     -> GetBinContent(k+1);
    double y0  = projData0[ptbin] -> GetBinContent(k+1);
    double ey0 = projData0[ptbin] -> GetBinError(k+1);
    double ey1 = projC[ptbin]     -> GetBinError(k+1);
    double ey2 = projB[ptbin]     -> GetBinError(k+1);
    
    double ycomb = getFitFunction(par,y1,y2);
    double ycomberr = getFitFunctionError(par,ey1,ey2);
    double delta = (ycomb - y0) / sqrt(ey0*ey0+ycomberr*ycomberr);
    
    chiSq += delta*delta;
    nDof++;
    
    //debug
    //cout <<"k: " << k << " c: " << y1 << " b: " << y2 << " data/er: " << y0 << "/"
    //	 << ey0 << " c2: " << chiSq << endl;
  }
  
  func = chiSq;
  curChi2 = chiSq;
  curNDF = nDof;
  
}

void chi2_2(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag){
  
  Int_t ptbin = currentPtBin;
  
  if(projData2[ptbin]->GetNbinsX()!= projC[ptbin]->GetNbinsX()){
    cout<<"Warning: unequal bins! bin1 = "<< projData0[ptbin]->GetNbinsX()<<" bin2 = "<<projC[ptbin]->GetNbinsX()<<endl;
    return 0;
  }
  
  curChi2 = 0.;
  curNDF = 0.;
  double chiSq = 0.;
  int nDof = 0;
  
  rangeLow  = projData0[ptbin]->GetXaxis()->FindBin(-1.*rangefit);
  rangeHigh  = projData0[ptbin]->GetXaxis()->FindBin(rangefit);
  for(int k=rangeLow;k<rangeHigh;k++){
    
    double y1  = projC[ptbin]     -> GetBinContent(k+1);
    double y2  = projB[ptbin]     -> GetBinContent(k+1);
    double y0  = projData2[ptbin] -> GetBinContent(k+1);
    double ey0 = projData2[ptbin] -> GetBinError(k+1);
    double ey1 = projC[ptbin]     -> GetBinError(k+1);
    double ey2 = projB[ptbin]     -> GetBinError(k+1);
    
    double ycomb = getFitFunction(par,y1,y2);
    double ycomberr = getFitFunctionError(par,ey1,ey2);
    double delta = (ycomb - y0) / sqrt(ey0*ey0+ycomberr*ycomberr);
    chiSq += delta*delta;
    nDof++;
    
    //debug
    //cout <<"k: " << k << " c: " << y1 << " b: " << y2 << " data/er: " << y0 << "/"
    //	 << ey0 << " c2: " << chiSq << endl;
  }
  
  func = chiSq;
  curChi2 = chiSq;
  curNDF = nDof;
  
}

void chi2_0S(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag){
  
  Int_t ptbin = currentPtBin;
  
  rangeLow  = projData0[ptbin]->GetXaxis()->FindBin(-1.*rangefit);
  rangeHigh  = projData0[ptbin]->GetXaxis()->FindBin(rangefit);
  if(projData0S[ptbin]->GetNbinsX()!= projC[ptbin]->GetNbinsX()){
    cout<<"Warning: unequal bins! bin1 = "<< projData0S[ptbin]->GetNbinsX()<<" bin2 = "<<projC[ptbin]->GetNbinsX()<<endl;
    return 0;
  }
  curChi2 = 0.;
  curNDF = 0.;
  double chiSq = 0.;
  int nDof = 0;
  
  for(int k=rangeLow;k<rangeHigh;k++){
    
    double y1  = projC[ptbin]     -> GetBinContent(k+1);
    double y2  = projB[ptbin]     -> GetBinContent(k+1);
    double y0  = projData0S[ptbin] -> GetBinContent(k+1);
    double ey0 = projData0S[ptbin] -> GetBinError(k+1);
    double ey1 = projC[ptbin]     -> GetBinError(k+1);
    double ey2 = projB[ptbin]     -> GetBinError(k+1);
    
    double ycomb = getFitFunctionS(par,y1,y2);
    double ycomberr = getFitFunctionErrorS(par,ey1,ey2);
    double delta = (ycomb - y0) / sqrt(ey0*ey0+ycomberr*ycomberr);
    
    chiSq += delta*delta;
    nDof++;
    
    //debug
    //cout <<"k: " << k << " c: " << y1 << " b: " << y2 << " data/er: " << y0 << "/"
    //	 << ey0 << " c2: " << chiSq << endl;
  }
  
  func = chiSq;
  curChi2 = chiSq;
  curNDF = nDof;
  
}

void chi2_2S(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag){
  
  Int_t ptbin = currentPtBin;
  
  rangeLow  = projData0[ptbin]->GetXaxis()->FindBin(-1.*rangefit);
  rangeHigh  = projData0[ptbin]->GetXaxis()->FindBin(rangefit);
  if(projData2S[ptbin]->GetNbinsX()!= projC[ptbin]->GetNbinsX()){
    cout<<"Warning: unequal bins! bin1 = "<< projData2S[ptbin]->GetNbinsX()<<" bin2 = "<<projC[ptbin]->GetNbinsX()<<endl;
    return 0;
  }
  
  curChi2 = 0.;
  curNDF = 0.;
  double chiSq = 0.;
  int nDof = 0;
  
  for(int k=rangeLow;k<rangeHigh;k++){
    
    double y1  = projC[ptbin]     -> GetBinContent(k+1);
    double y2  = projB[ptbin]     -> GetBinContent(k+1);
    double y0  = projData2S[ptbin] -> GetBinContent(k+1);
    double ey0 = projData2S[ptbin] -> GetBinError(k+1);
    double ey1 = projC[ptbin]     -> GetBinError(k+1);
    double ey2 = projB[ptbin]     -> GetBinError(k+1);
    
    double ycomb = getFitFunctionS(par,y1,y2);
    double ycomberr = getFitFunctionErrorS(par,ey1,ey2);
    double delta = (ycomb - y0) / sqrt(ey0*ey0+ycomberr*ycomberr);
    chiSq += delta*delta;
    nDof++;
    
    //debug
    //cout <<"k: " << k << " c: " << y1 << " b: " << y2 << " data/er: " << y0 << "/"
    //	 << ey0 << " c2: " << chiSq << endl;
  }
  
  func = chiSq;
  curChi2 = chiSq;
  curNDF = nDof;
  
}

double getFitFunction(Double_t *par, double y1, double y2)
{
  double ycomb;
  //  if(oneParamFit)
  //    ycomb = FITPARA*(par[0]*y2 + y1*(1-par[0])); // rb*yb + (1-rb)*yv
  //  else
  ycomb = par[1]*par[0]*y2 + y1*(1-par[0])*par[1]; //A*rb*yb + A*(1-rb)*yc
  return ycomb;
}

double getFitFunctionError(Double_t *par, double ey1, double ey2)
{
  // double ycomberr = FITPARA*sqrt(par[0]*par[0]*ey2*ey2 + (1-par[0])*(1-par[0])*ey1*ey1);
  double ycomberr;
  //  if(oneParamFit)
  //    ycomberr = FITPARA*sqrt(par[0]*par[0]*ey2*ey2 + (1-par[0])*(1-par[0])*ey1*ey1);
  //  else
  ycomberr = sqrt(par[1]*par[0]*par[1]*par[0]*ey2*ey2 + ey1*ey1*(1-par[0])*par[1]*(1-par[0])*par[1]); //A*rb*yb + A*(1-rb)*yc
  return ycomberr;
}

double getFitFunctionS(Double_t *par, double y1, double y2)
{
  double ycomb;
  if(oneParamFit)
    ycomb = FITPARAS*(par[0]*y2 + y1*(1-par[0])); // rb*yb + (1-rb)*yv
  else
    ycomb = par[1]*par[0]*y2 + y1*(1-par[0])*par[1]; //A*rb*yb + A*(1-rb)*yc
  return ycomb;
}

double getFitFunctionErrorS(Double_t *par, double ey1, double ey2)
{
  double ycomberr;
  if(oneParamFit)
    ycomberr = FITPARAS*sqrt(par[0]*par[0]*ey2*ey2 + (1-par[0])*(1-par[0])*ey1*ey1);
  else
    ycomberr = sqrt(par[1]*par[0]*par[1]*par[0]*ey2*ey2 + ey1*ey1*(1-par[0])*par[1]*(1-par[0])*par[1]); //A*rb*yb + A*(1-rb)*yc
  return ycomberr;
}
//=================================================================================
TGraphAsymmErrors *getPrelimnaryStat(){
  float pT[9], Rb[9], dyU[9], dyD[9], dysU[9], dysD[9];
  float dx[9] = {0.};
  float dx2[9] = {0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18};
  float x1, x2, x3, x4, x5, x6;
  ifstream infile("../../ZWMiller_online_offline/Zach_fromZhenyu/run12NPEhResults/getPointsFromImage/plotPoints.txt");
  int i = 0;
  string line;
  cout << "Run 12 Points" << endl;
  while(getline(infile,line))
  {
    sscanf(line.c_str(),"%f %f %f %f %f %f",&x1, &x2, &x3, &x4, &x5, &x6);
    pT[i] = x1-0.3;
    Rb[i] = x2;
    dyU[i] = x3-x2;
    dyD[i] = x2-x4;
    dysU[i] = x5-x2;
    dysD[i] = x2-x6;
    i++;
  }
  TGraphAsymmErrors* pstat = new TGraphAsymmErrors(9,pT,Rb,dx,dx,dyD,dyU);
  return pstat;
  
}
TGraphAsymmErrors *getPrelimnarySys(){
  
  float pT[9], Rb[9], dyU[9], dyD[9], dysU[9], dysD[9];
  float dx[9] = {0.};
  float dx2[9] = {0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18,0.18};
  float x1, x2, x3, x4, x5, x6;
  ifstream infile("../../ZWMiller_online_offline/Zach_fromZhenyu/run12NPEhResults/getPointsFromImage/plotPoints.txt");
  int i = 0;
  string line;
  cout << "Run 12 Points" << endl;
  while(getline(infile,line))
  {
    sscanf(line.c_str(),"%f %f %f %f %f %f",&x1, &x2, &x3, &x4, &x5, &x6);
    pT[i] = x1-0.3;
    Rb[i] = x2;
    dyU[i] = x3-x2;
    dyD[i] = x2-x4;
    dysU[i] = x5-x2;
    dysD[i] = x2-x6;
    i++;
  }
  TGraphAsymmErrors* psyst = new TGraphAsymmErrors(9,pT,Rb,dx2,dx2,dysD,dysU);
  //  psyst->Draw();
  return psyst;
}
//=================================================================================
void drawtext()
{
  Int_t i,n;
  Double_t x,y;
  TLatex l;
  
  l.SetTextSize(0.025);
  l.SetTextFont(42);
  l.SetTextAlign(21);
  l.SetTextColor(kBlue);
  
  TGraphAsymmErrors *g = (TGraphAsymmErrors*)gPad->GetListOfPrimitives()->FindObject("grA");
  n = g->GetN();
  
  for (i=0; i<n; i++) {
    g->GetPoint(i,x,y);
    auto yh = (Float_t)g->GetErrorYhigh(i);
    auto yl = (Float_t)g->GetErrorYlow(i);
    
//    l.PaintText(x,y+0.2,Form("(%4.3f+%4.3f-%4.3f)",y,yh,yl));
    l.PaintText(x,y+0.2,Form("%4.3f",y));

  }
}
//=================================================================================
TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex){
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  // latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
  
}

