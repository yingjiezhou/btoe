# ifndef StPhotonicReEff_h
# define  StPhotonicReEff_h

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TGraphErrors.h"
class TString;
class TF1;
class TH1D;
class TH2D;
class  TH3F;
class StPair;
class StMcElectronTrack;
class StPhotonicReEff
{
 public:
  StPhotonicReEff(const char *outName);
  virtual ~StPhotonicReEff();

  void bookHistogram() ;
  void read(TString filename);
  void WriteHistogram();
  Double_t Weight(Float_t pt, Float_t ppt,Float_t gppt,Float_t geantId,Float_t pgeantId,Float_t gpgeantId); 
 private:
    TFile * mOutputFile;
    
    TFile * weightFile;
    TGraphErrors * TError;
    TF1 *wightFunction;
    TGraphErrors *gr_pi;
    TFile *input;
    TH1D*   pi_pt;


    static int const nhist=5;

    TH2F    *mh2massVsPt_gamma[nhist];
    TH2F    *mh2massVsPt_pi0[nhist];

    TH2F    *mh2massVsPt_gamma_unlike[nhist];
    TH2F    *mh2massVsPt_pi0_unlike[nhist];

    TH2F    *mh2massVsPt_gamma_like[nhist];
    TH2F    *mh2massVsPt_pi0_like[nhist];

    TH2F    *mh2pairdcaVsPt_gamma[nhist];
    TH2F    *mh2pairdcaVsPt_pi0[nhist];

    TH2F    *mh2pairdcaVsPt_gamma_unlike[nhist];
    TH2F    *mh2pairdcaVsPt_pi0_unlike[nhist];

    TH2F    *mh2pairdcaVsPt_gamma_like[nhist];
    TH2F    *mh2pairdcaVsPt_pi0_like[nhist];


    // mc pt gamma
    TH1F*    mSingle_Track_pt_gamma;
    TH1F*    mPair_pt_gamma[nhist];
    TH1F*    mSingle_Track_HFT_pt_gamma;
    TH1F*    mPair_HFT_pt_gamma[nhist];

    // rc pt gamma
    TH1F*    mSingle_Track_rpt_gamma;
    TH1F*    mPair_rpt_gamma[nhist];
    TH1F*    mSingle_Track_HFT_rpt_gamma;
    TH1F*    mPair_HFT_rpt_gamma[nhist];

    // mc pt pi0
    TH1F*    mSingle_Track_pt_pi0;
    TH1F*    mPair_pt_pi0[nhist];
    TH1F*    mSingle_Track_HFT_pt_pi0;
    TH1F*    mPair_HFT_pt_pi0[nhist];

    // rc pt pi0
    TH1F*    mSingle_Track_rpt_pi0;
    TH1F*    mPair_rpt_pi0[nhist];
    TH1F*    mSingle_Track_HFT_rpt_pi0;
    TH1F*    mPair_HFT_rpt_pi0[nhist];



  ClassDef(StPhotonicReEff,1)
};
#endif
