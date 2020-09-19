/*
 *  
 *   3/17/2014/ xiaozhi bai
 *
 */




#include <iostream>
#include "StPhotonicReEff.h"
#include "StMcAccpTracks.h"
#include "StMcAccpEventCount.h"
#include "StPheRecoPair.h"
#include "StPheRecoTrack.h"
#include "TFile.h"
#include "TF1.h"
#include "TNtuple.h"
#include "TGraphErrors.h"
#include "cmath"
using namespace std;

ClassImp(StPhotonicReEff)
  
StPhotonicReEff::StPhotonicReEff(const char* outName)
{
  TH1F::SetDefaultSumw2();  
  mOutputFile=new TFile(outName,"RECREATE");
   weightFile=new TFile("pi0_gamma_fit.root","READ");
   wightFunction=(TF1 *) weightFile->Get("fun");
   TError=(TGraphErrors *) weightFile->Get("gra");
}
 StPhotonicReEff::~StPhotonicReEff()
{

  //..
  //
}
void StPhotonicReEff::bookHistogram()
{ 
  cout<<"gbook histogram"<<endl;

  //  Float_t Pt_xx[10]={1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,10.5,16.5};
  
  //track
  mSingle_Track=new TH1F("mSingle_Track","mSingle_Track",2000,0,20);
  //Pair
  mPair=new TH1F("mPair","mPir",2000,0,20);
  


}
void StPhotonicReEff::read(TString fileName)
{ 

  //  TH1F::SetDefaultSumw2();
  TFile * infile=new TFile(fileName.Data());
  if( TNtuple* ntTracks=(TNtuple* ) infile->Get("nt_sngl"));
  cout<<"   Get File"<<endl;
  TNtuple* ntTracks=(TNtuple* ) infile->Get("nt_sngl");
  TNtuple * ntPair=(TNtuple* )infile->Get("nt_pair");
    
  StPheRecoTrack * tracksMC=new StPheRecoTrack; 
  tracksMC->Init(ntTracks);
  StPheRecoPair *Pair=new StPheRecoPair;
  Pair->Init(ntPair);
  
  for(Int_t iTrk=0;iTrk<tracksMC->GetEntries();iTrk++)
    {
      tracksMC->GetEntry(iTrk);
      
      if(
 	 fabs(tracksMC->vz)<35 && (tracksMC->pgeantId==10007)
	 && tracksMC->dca<1.5 
	 && tracksMC->nfit>20 
	 && tracksMC->nDedxPts>15 
	 && tracksMC->nfit/(Float_t)tracksMC->nmax > 0.52 
	 && sqrt(tracksMC->stpcx*tracksMC->stpcx+tracksMC->stpcy*tracksMC->stpcy)<73 
	 &&0.2<tracksMC->rpt 
	 && abs(tracksMC->eta)<0.7
	 )
	
	{
	  //               
	  //                         cout<<"weighrt"<<Weight(tracksMC->ppt)<<endl;
	  Float_t weight= Weight(tracksMC->ppt);
	  mSingle_Track->Fill(tracksMC->pt,weight);    
	}
    }
  for(Int_t iPair=0;iPair<Pair->GetEntries();iPair++)
    {
      Pair->GetEntry(iPair);
      if(
	 (Pair->p1pgeantId==10007 && Pair->p2pgeantId==10007) 
	 && fabs(Pair->p1eta)<35
	 && fabs(Pair->p1eta)<0.7 
	 &&0.2<Pair->p2rpt 
	 && Pair->p1nfit>20 
	 && Pair->p1nfit/(Float_t)Pair->p1nmax>0.52 
	 && Pair->p1ndedx>15 
	  && 0.2<Pair->p1rpt
	 && sqrt(Pair->p1stpcx*Pair->p1stpcx+Pair->p1stpcy*Pair->p1stpcy)<73
	 && Pair->p1dca<1.5 
	 && Pair->p2nfit>20 && (Float_t)Pair->p2nfit/(Float_t)Pair->p2nmax>0.52
         
	 &&
	  Pair->massDCA<0.8
	
	 && Pair->pairDCA<1
	 )	
	{ 
	  Float_t weight= Weight(Pair->p1ppt);
	  mPair->Fill(Pair->p1pt,weight);
	}
      
    }
  
  
}
void StPhotonicReEff::WriteHistogram()
{ 
  mOutputFile->cd();
  mSingle_Track->Write();
  mPair->Write();
  
  //
}
Double_t StPhotonicReEff::Weight(Float_t pt)
{
  Double_t weight; 
  //    TFile * weightFile=new TFile("pi0_gamma_fit.root","READ");
  // weightFile->cd();
  
  
  if(pt<=3)
    weight=TError->Eval(pt);
  if(3<pt) 
    weight=wightFunction->Eval(pt);
  return weight;
  
}
