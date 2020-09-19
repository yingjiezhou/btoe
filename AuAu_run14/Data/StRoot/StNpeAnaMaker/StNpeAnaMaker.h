#ifndef StNpeAnaMaker_h
#define StNpeAnaMaker_h
#include "StMaker.h"
#include "TLorentzVector.h"
#include "StHistogram/Histogram.h"

class StAnaTree;
class StEventHeader;
class StElectronTrack;
class StPartElectronTrack;
class StMuonTrack;
class StEEPair;
class StPhoEEPair;
class StEMuPair;
class StMuMuPair;
class StEmcTrigger;
class StPicoAnaTreeMaker;

class TString;
class TH1F;
class TH2F;
class TH3F;
class TFile;
class TF1;
class TLorentzVector;

class StNpeAnaMaker : public StMaker {
 public:
  StNpeAnaMaker(const Char_t *name, StPicoAnaTreeMaker *treeMaker, const Char_t *outName);
  virtual ~StNpeAnaMaker();
  
  virtual Int_t Init();
  virtual Int_t Make();
  virtual void  Clear(Option_t *opt="");
  virtual Int_t Finish();

  
  
  void    declareHistograms();


  Bool_t pass_MB_trigger_selection(StEventHeader *, Int_t &);
  Bool_t pass_HT1_trigger_selection(StEventHeader *, Int_t &);
  Bool_t pass_HT2_trigger_selection(StEventHeader *, Int_t &);
  Bool_t pass_HT3_trigger_selection(StEventHeader *, Int_t &);

  Bool_t isGoodEvent(StEventHeader *,Int_t);


  void  Fill_MB_Trigger_histogram(StAnaTree*,int);
  void  Fill_MB_Trigger_inclusive_histogram_without_HFT(StElectronTrack*,int);
  void  Fill_MB_Trigger_inclusive_histogram_with_HFT(StElectronTrack*,int);
  void  Fill_MB_Trigger_PHE_histogram_with_HFT(StPhoEEPair *,StElectronTrack *,StPartElectronTrack *,Int_t);
  void  Fill_MB_Trigger_PHE_histogram_without_HFT(StPhoEEPair *,StElectronTrack *,StPartElectronTrack *,Int_t);


  void  Fill_HT_Trigger_histogram(StAnaTree*,int);
  void  Fill_HT_Trigger_inclusive_histogram_without_HFT(StElectronTrack*,int);
  void  Fill_HT_Trigger_inclusive_histogram_with_HFT(StElectronTrack*,int);
  void  Fill_HT_Trigger_PHE_histogram_with_HFT(StPhoEEPair *,StElectronTrack *,StPartElectronTrack *,Int_t);
  void  Fill_HT_Trigger_PHE_histogram_without_HFT(StPhoEEPair *,StElectronTrack *,StPartElectronTrack *,Int_t);

  Bool_t pass_cut_Pt_Eta(StElectronTrack *);
  Bool_t pass_cut_GoodTrack(StElectronTrack * );
  Bool_t pass_cut_GoodTrack_partner(StPartElectronTrack *);
  Bool_t pass_Tof_Match( StElectronTrack *);
  Bool_t pass_cut_Tof( StElectronTrack *);
  Bool_t pass_cut_Tof_part( StPartElectronTrack *);

  Bool_t pass_cut_eePair( StPhoEEPair *Pair);
  Bool_t pass_cut_nsigmaE(StElectronTrack *);
  Bool_t pass_cut_partner_electron(StPartElectronTrack *);
  Bool_t pass_cut_isHFT_track(StElectronTrack * );  
  
  void determineTriggers();
  void clearTriggers();
  void  addTrigger(int tr, int id) { triggers[id].push_back(tr); };
  Bool_t  checkTriggers(StEventHeader *,int trigType);
  Bool_t isMinBias(StEventHeader *);
  Bool_t isBHT0( StEventHeader *);
  Bool_t isBHT1( StEventHeader *);
  Bool_t isBHT2(StEventHeader *);
  Bool_t isBHT3(StEventHeader *);
  bool isHT0;
  bool isHT1;
  bool isHT2;
  bool isHT3;
  bool isMB;
  vector<int> triggers[5]; //0-HT0, 1-HT1 ... 4-MB

  void fun_1(UInt_t n);


  // emc cuts

  Bool_t pass_cut_poe_HT(StElectronTrack *);
  Bool_t pass_cut_poe_MB(StElectronTrack *);

  Bool_t pass_cut_BSMD(StElectronTrack *);

  Bool_t pass_cut_poe_part(StPartElectronTrack *);
  Bool_t pass_cut_BSMD_part(StPartElectronTrack *);

  Bool_t pass_cut_Match_BSMD(StElectronTrack * );
  
  StPicoAnaTreeMaker *mPicoAnaTreeMaker;
  StAnaTree          *mAnaTree;

  TString    mOutName;
  TFile*	   fout;

  Histogram *hist;

  Double_t  mMtdT0Corr[30][5];

  TH1F *hnEvents;
  TH1F *hnEvents_GoodEvents;
  

  Int_t mNBadRuns_MB;
  Int_t mNBadRuns_HT;


		ClassDef(StNpeAnaMaker, 1)
};

/* inline void StNpeAnaMaker:: fun_1(UInt_t n) */
/* { */
/*   if(n<2)    */
/*     cout<<n; */
/*   if(n>=2)   */
/*     { */
/*       fun_1(n/2); */
/*       cout<<n%2; */
/*     } */
/* } */
/* inline   Bool_t StNpeAnaMaker::isMinBias(StEventHeader * ) { return true;} */
/* inline   Bool_t StNpeAnaMaker::isBHT0(StEventHeader *) { return true ;} */
/* inline   Bool_t StNpeAnaMaker::isBHT1(StEventHeader *) { return true; } */
/* inline   Bool_t StNpeAnaMaker::isBHT2(StEventHeader *) {  return true;} */
/* inline   Bool_t StNpeAnaMaker::isBHT3(StEventHeader *) { return true; } */


#endif
