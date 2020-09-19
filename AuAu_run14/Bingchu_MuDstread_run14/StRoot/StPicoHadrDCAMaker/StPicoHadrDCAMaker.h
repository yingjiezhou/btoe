#ifndef StPicoHadrDCAMaker_h
#define StPicoHadrDCAMaker_h
#include "StRoot/StPicoDstMaker/StPicoTrack.h"
#include "StMaker.h"
class StPicoDst;
class StPicoEvent;
class StPicoDstMaker;
class StPicoMtdHit;
class StPicoTrack;
class TString;
class TH1F;
class TH2F;
class TH3F;
class THnSparse;
class TFile;
class StPicoHadrDCAMaker : public StMaker {
 public:
     StPicoHadrDCAMaker(const char *name, StPicoDstMaker *picoMaker, const char *outName);
     virtual ~StPicoHadrDCAMaker();
     Bool_t passGoodTrack(StPicoEvent*, StPicoTrack*, int ); // ZWM
     Bool_t passGoodTrack_NoEta(StPicoEvent*, StPicoTrack*, int ); // ZWM
     Bool_t passBEMCCuts(StPicoEvent*, StPicoTrack*, int );   // ZWM
     Bool_t passBEMCCuts_noTrigger(StPicoEvent*, StPicoTrack*, int );   // ZWM
     Bool_t passTOFCuts(StPicoEvent*, StPicoTrack*, int );   // ZWM
     Int_t passSMDCuts(StPicoEvent*, StPicoTrack*, int );   // ZWM, return INT becuase could fit multiple cases
     Bool_t Ismuontrack(StPicoEvent*, StPicoTrack* );
     Bool_t IspassTOFcuts(StPicoTrack*);
     Bool_t IspassBEMCcuts(StPicoTrack*);
  
     Bool_t passEventCuts(StPicoEvent*,int);  // ZWM
     Bool_t pass_HFT_EventCuts(StPicoEvent*,int);  // ZWM

     Bool_t passEventCuts_NodVz(StPicoEvent*,int);  // ZWM
     Bool_t checkHotTower(int, int); //ZWM
     Bool_t checkTriggers(StPicoEvent*, int);
     Bool_t isMB(StPicoEvent*);
     Bool_t isBHT0(StPicoEvent*);
     Bool_t isBHT1(StPicoEvent*);
     Bool_t isBHT2(StPicoEvent*);
     Bool_t isBHT3(StPicoEvent*);
     Double_t RotatePhi(Double_t phi) const;   
     //virtual Int_t Init();
     //virtual Int_t Make();
     //virtual void  Clear(Option_t *opt="");
     //virtual Int_t Finish();
     Int_t Init();
     Int_t Make();
     void  Clear(Option_t *opt="");
     Int_t Finish();

     void    DeclareHistograms();
     void    WriteHistograms();
     Int_t    FillHistograms(Int_t, StPicoEvent*);
     Int_t    dVzStudy(StPicoEvent*);

     void  SetDefaultCuts();               // ZWM

      // ZWM Functions
     void   setNSigECuts(float l, float h)  { nSigELow = l;  nSigEHigh = h; };
     void   setNSigPCuts(float l, float h)  { nSigPLow = l;  nSigPHigh = h; };
     void   setNSigKCuts(float l, float h)  { nSigKLow = l;  nSigKHigh = h; };
     void   setNSigPiCuts(float l, float h) { nSigPiLow = l; nSigEHigh = h; };
     void   setvZCuts(int tr, float vz, float dvz)  { vZcut[tr] = vz; dvZcut[tr] = dvz; };
     void   setvZCutsHFT(int tr, float vz, float dvz)  { vZcutHFT[tr] = vz; dvZcutHFT[tr] = dvz; };
     void   setPrimaryPtCut(float tpt, float bpt ) { bemcPtCut = bpt; tofPtCut = tpt; };
     void   setPrimaryEtaCut(float et)      { etaCut = et; };
     void   setPrimaryDCACut(float dca)     { dcaCut = dca; };
     void   setNhitsCuts(float dedx, float fit, float ratio) 
        { nhitsdEdxCut = dedx; nhitsFitCut = fit; nhitsRatioCut = ratio; };
     void   setPoECut(float pEl, float pEh) { poeCutLow = pEl; poeCutHigh = pEh; };
     void   setToFBetaCut(float iB)         { tofInvBetaCut = iB; };
     void   setToFLocalyCut(float lY)       { toflocalyCut = lY; };
     void   setKaonEnhCut(float kel, float keh) { kaonEnhCutLow = kel; kaonEnhCutHigh = keh; };
     void   setPionEnhCut(float pel, float peh) { pionEnhCutLow = pel; pionEnhCutHigh = peh; };
     void   setProtonEnhCut(float pel, float peh) { protonEnhCutLow = pel; protonEnhCutHigh = peh; };
     void   setDsmAdcCut(int trg, int val) { dsmAdcCut[trg] = val; };
     int    getDsmAdcCut(int trg)            { return dsmAdcCut[trg]; };

     void   setadc0Cut(int trg, int val) { adc0Cut[trg] = val; };
     int    getadc0Cut(int trg)            { return adc0Cut[trg]; };

     void   setSMDCuts(int ne, int np, float zd, float pd) 

     {nEtaCut = ne; nPhiCut = np; zDistCut = zd; phiDistCut = pd; };
     void   setSMDCuts2(int ne, int np, float zd, float pd) 
     {nEtaCut2 = ne; nPhiCut2 = np; zDistCut2 = zd; phiDistCut2 = pd; };

     void addTrigger(int tr, int id) { triggers[id].push_back(tr); };
     void setRunMode(int md) { runMode = md; };

  private:
   StPicoDstMaker *mPicoDstMaker;
   StPicoDst      *mPicoDst;
   
   map<Int_t,Int_t> mTotalRunId;
   const int pp = 0;
   const int AuAu = 1;
   int runMode;
   vector<int> triggers[5]; //0-HT0, 1-HT1 ... 4-MB
   // dsm adc
   int dsmAdcCut[4];
   int adc0Cut[4];

   // Trigger Tracking
   int numTrigs;
   int trig;
   // Event cut vars
   float vZcut[4];
   float dvZcut[4];
   float vZcutHFT[4];
   float dvZcutHFT[4];
   // Track cut vars
   float bemcPtCut, tofPtCut, etaCut, dcaCut;
   float nhitsdEdxCut, nhitsFitCut, nhitsRatioCut;
   float poeCutLow, poeCutHigh;
   float tofInvBetaCut,toflocalyCut;
   
   // SMD cuts (1 = Xiaozhi run 12 cuts, 2 = Daniel run 10 cuts [tighter])
   int nEtaCut, nPhiCut;
   float zDistCut, phiDistCut;
   int nEtaCut2, nPhiCut2;
   float zDistCut2, phiDistCut2;

   //TPC cuts (not used for purity, here in case)
   float nSigELow, nSigEHigh;
   float nSigPLow, nSigPHigh;
   float nSigKLow, nSigKHigh;
   float nSigPiLow, nSigPiHigh;
   float pionEnhCutLow,pionEnhCutHigh;
   float protonEnhCutLow,protonEnhCutHigh;
   float kaonEnhCutLow,kaonEnhCutHigh;
   int trigCounter;
   TString    mOutName;

   Int_t   mNBadRuns;       
   Int_t   mNHotTower1;
   Int_t   mNHotTower2;
   Int_t   mNHotTower3;
   Int_t  trkHFTflag;
    
   TFile*	   fout;
    //-----event QA-----

    TH1F*      trigType;
    TH1F*      hNEvents[4];

    //---------Track QA----------
    //-------TPC information------
    TH1F*      mNptracks[4];
    TH1F*      mNgtracks[4];
    TH1F*      hNTracks[4];
    //====zyj=====
    TH2F* HadronDcaXy_Pt[4][2];
    TH2F*  HadronDcaZ_Pt[4][2];
    TH2F*     PiDcaXy_Pt[4][2];
    TH2F*      PiDcaZ_Pt[4][2];
    TH2F*   KaonDcaXy_Pt[4][2];
    TH2F*    KaonDcaZ_Pt[4][2];

    TH2F*  mnsigmaE_pT_all[4][2];
    TH2F*  TOF_beta_p_all[4][2];
    //====zyj=====

    ClassDef(StPicoHadrDCAMaker, 1)
};

#endif