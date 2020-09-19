
#ifndef anaConst_H
#define anaConst_H

namespace anaConst
{

  // Xiaozhi Binning
  // const Int_t nPtBins = 14; 
  //Float_t lpt[14] ={2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.5,10.,14.0};
  //Float_t hpt[14]={3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.5,10.,14.,200.};

  // Run5 Binning
  const Int_t nPtBins = 9;
  Float_t lpt[nPtBins] ={2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5, 10.5};
  Float_t hpt[nPtBins] ={3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5};

//  const Int_t Nbins_AA = 11;
//  Double_t pt_arr_AuAu[Nbins_AA+1] = {2.5,3,3.5,4,4.5,5,5.5,6,7,8,10,13};
//const Int_t nPtBins = 9;
//Float_t lpt[nPtBins] ={2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5, 10.5};
//Float_t hpt[nPtBins] ={3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5};


  Float_t hptCut=0.3; Float_t hptMax = 19;
  //Float_t lowPhi=-3.25, highPhi=3.25;
  Float_t lowPhi=-3., highPhi=3.;
  //Float_t lowPhi=-TMath::Pi(), highPhi=TMath::Pi();
  
}

#endif
