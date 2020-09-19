
#ifndef anaConst_H
#define anaConst_H

namespace anaConst
{

  // Xiaozhi Binning
  // const Int_t nPtBins = 14; 
  //Float_t lpt[14] ={2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.5,10.,14.0};
  //Float_t hpt[14]={3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.5,10.,14.,200.};

//   Run5 Binning
  const Int_t nPtBins = 14; 
  Float_t lpt[nPtBins] ={2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5, 10.5,11.5,12.5,13.5,14.5,15.5};
  Float_t hpt[nPtBins] ={3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,18.5};

//   const Int_t nPtBins = 6; 
//   Float_t lpt[nPtBins] ={0, 2, 4, 6, 8, 12};
//   Float_t hpt[nPtBins] ={2, 4, 6, 8, 12, 200};

  Float_t hptCut=0.3; Float_t hptMax = 19;
//   Float_t hptCut=0.5; Float_t hptMax = 19;

  Float_t lowPhi=-3.25, highPhi=3.25;
}

#endif
