# ifndef StTrigEfficiency_h
# define  StTrigEfficiency_h

#include "StMcAccpTracks.h"
#include "StMcAccpEventCount.h"
#include "StMcAccpTracks.h"
#include "TH1F.h"
#include "TH2F.h"
//#include "TH1D.h"
#include "TFile.h"

class TString;
class TF1;
class TH1D;
class TH2D;

class  TH3F;
class StMcAccpEventCount;
class StMcAccpTracks; 
class StPheRecoPair;
class StPheRecoTrack;

class StTrigEfficiency
{
 public:
  StTrigEfficiency(const char *outName);
  virtual ~StTrigEfficiency();

  void bookHistogram() ;
  void read(TString filename);
  void WriteHistogram();
    Double_t Weight(Float_t );
 private:
    TFile * mOutputFile;
    
    TFile * weightFile;
    //  StMcAccpTracks *AcTracks;
    // StMcAccpEventCount *mAcEvent;   

  // Event

    TH1F*     m_DSMadc11_cut;
    TH1F*     m_DSMadc18_cut;
    TH1F*     m_DSMadc;

  ClassDef(StTrigEfficiency,1)

};

#endif
