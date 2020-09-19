/*
 *
Declear all the histogram 
Tue Dec  1 13:21:15 PST 2015
by Xiaozhi Bai
*
*/

#ifndef Histogram_H_
#define Histogram_H_

#include <TObject.h>

class TFile;
class TProfile;
class TH1F;
class TH2F;
class TH3F;


class Histogram : public TObject {
public:
  Histogram();
  virtual ~Histogram();
  void writeData(TFile *outputFile) const;
  char *imgOutDir;
  TString outputQaName;

  const static  int nTrg=4;

  // Event level
  TH1F   *mh1nEvents[nTrg];
  TH2F *mh2hVzVsVpdVz_noCut[nTrg];
  TH2F *mh2hVzVsDiff_noCut[nTrg];

  TH2F *mh2hVzVsVpdVz[nTrg];

  // inclusive electron
  TH2F * mh2NsigmaeVsPt[nTrg];
  TH1F  *mh1inclusive_electron[nTrg]; 
  TH2F * mh2dcaVsPt[nTrg];
  TH2F * mh2dcaXYVsPt[nTrg];
  TH2F * mh2dcaZVsPt[nTrg];

  TH1F *  mh1pi_pt[nTrg];
  TH1F *  mh1pi_pt_HFT[nTrg];
  

  TH2F * mh2NsigmaeVsPt_HFT[nTrg];
  TH1F  *mh1inclusive_electron_HFT[nTrg]; 
  TH2F * mh2dcaVsPt_HFT[nTrg];
  TH2F * mh2dcaXYVsPt_HFT[nTrg];
  TH2F * mh2dcaZVsPt_HFT[nTrg];

  TH3F * mh3pT_dcaXY_Phi_HFT_EtaPlus[nTrg];
  TH3F * mh3pT_dcaXY_Phi_HFT_EtaMinus[nTrg];

  TH2F *mh2dcaXYVsPt_HFT_Positron[nTrg];
  TH2F *mh2dcaXYVsPt_HFT_Electron[nTrg];
      


  
  // photonic electron
  TH3F * mh3InvMassVsPtVsPairdca_unlike[nTrg];
  TH3F * mh3InvMassVsPtVsPairdca_like[nTrg];

  
  TH2F * mh2InvMassVsPt_unlike[nTrg];
  TH2F * mh2InvMassVsPt_like[nTrg];

  TH2F * mh2PairdcaVsPt_unlike[nTrg];
  TH2F * mh2PairdcaVsPt_like[nTrg];

  TH2F * mh2dcaVsPt_unlike[nTrg];
  TH2F * mh2dcaVsPt_like[nTrg];

  TH2F * mh2dcaXYVsPt_unlike[nTrg];
  TH2F * mh2dcaXYVsPt_like[nTrg];

  TH2F * mh2dcaZVsPt_unlike[nTrg];
  TH2F * mh2dcaZVsPt_like[nTrg];

  
  TH2F * mh2ConversionXVsY_unlike[nTrg];
  TH2F * mh2ConversionXVsY_like[nTrg];
 
  TH2F * mh2ConversionRVsZ_unlike[nTrg];
  TH2F * mh2ConversionRVsZ_like[nTrg];

  TH2F * mh2ConversionRVsPt_unlike[nTrg];
  TH2F * mh2ConversionRVsPt_like[nTrg];

  TH2F  *mh2partnerNsigmaeVspt_unlike[nTrg];
  TH2F  *mh2partnerNsigmaeVspt_like[nTrg];

  TH2F  *mh2NsigmaeVspt_unlike[nTrg];
  TH2F  *mh2NsigmaeVspt_like[nTrg];

  
  TH2F *  mh2Dz_unlike[nTrg];
  TH2F * mh2Dz_like[nTrg];

  TH2F *  mh2Dphi_unlike[nTrg];
  TH2F * mh2Dphi_like[nTrg];

  TH2F * mh2Poe_unlike[nTrg];
  TH2F * mh2Poe_like[nTrg];

  
  // with HFT


  TH3F * mh3InvMassVsPtVsPairdca_HFT_unlike[nTrg];
  TH3F * mh3InvMassVsPtVsPairdca_HFT_like[nTrg];



  
  TH2F * mh2InvMassVsPt_HFT_unlike[nTrg];
  TH2F * mh2InvMassVsPt_HFT_like[nTrg];

  TH2F * mh2PairdcaVsPt_HFT_unlike[nTrg];
  TH2F * mh2PairdcaVsPt_HFT_like[nTrg];

  TH2F * mh2dcaVsPt_HFT_unlike[nTrg];
  TH2F * mh2dcaVsPt_HFT_like[nTrg];

  TH2F * mh2dcaXYVsPt_HFT_unlike[nTrg];
  TH2F * mh2dcaXYVsPt_HFT_like[nTrg];

  TH2F * mh2dcaZVsPt_HFT_unlike[nTrg];
  TH2F * mh2dcaZVsPt_HFT_like[nTrg];

  
  TH2F * mh2ConversionXVsY_HFT_unlike[nTrg];
  TH2F * mh2ConversionXVsY_HFT_like[nTrg];
 
  TH2F * mh2ConversionRVsZ_HFT_unlike[nTrg];
  TH2F * mh2ConversionRVsZ_HFT_like[nTrg];

  TH2F * mh2ConversionRVsPt_HFT_unlike[nTrg];
  TH2F * mh2ConversionRVsPt_HFT_like[nTrg];

  TH2F  *mh2partnerNsigmaeVspt_HFT_unlike[nTrg];
  TH2F  *mh2partnerNsigmaeVspt_HFT_like[nTrg];

  TH2F  *mh2NsigmaeVspt_HFT_unlike[nTrg];
  TH2F  *mh2NsigmaeVspt_HFT_like[nTrg];

  // opertimize the cuts

  TH2F *  mh2Dz_HFT_unlike[nTrg];
  TH2F * mh2Dz_HFT_like[nTrg];
  
  TH2F *  mh2Dphi_HFT_unlike[nTrg];
  TH2F *  mh2Dphi_HFT_like[nTrg];
  TH2F *  mh2Poe_HFT_unlike[nTrg];
  TH2F *  mh2Poe_HFT_like[nTrg];


};

#endif 
