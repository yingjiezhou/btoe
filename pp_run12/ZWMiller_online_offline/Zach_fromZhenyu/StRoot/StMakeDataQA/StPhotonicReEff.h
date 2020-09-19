# ifndef StPhotonicReEff_h
# define  StPhotonicReEff_h

#include "StMcAccpTracks.h"
#include "StMcAccpEventCount.h"
#include "StMcAccpTracks.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TGraphErrors.h"

class TString;
class TF1;
class TH1D;
class TH2D;

class  TH3F;
class StMcAccpEventCount;
class StMcAccpTracks; 
class StPheRecoPair;
class StPheRecoTrack;

class StPhotonicReEff
{
 public:
  StPhotonicReEff(const char *outName);
  virtual ~StPhotonicReEff();

  void bookHistogram() ;
  void read(TString filename);
  void WriteHistogram();
    Double_t Weight(Float_t );
 private:
    TFile * mOutputFile;
    TFile * weightFile;

    TF1*    wightFunction;
    TGraphErrors *  TError;
    //  StMcAccpTracks *AcTracks;
    // StMcAccpEventCount *mAcEvent;   

  // Event

    TH1F*    mSingle_Track;
    TH1F*    mPair;

  ClassDef(StPhotonicReEff,1)

};

#endif
