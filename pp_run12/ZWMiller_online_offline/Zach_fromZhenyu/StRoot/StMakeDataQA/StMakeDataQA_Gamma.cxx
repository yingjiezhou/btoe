/*
 *  
 *   3/17/2014/ xiaozhi bai
 *
 */




#include <iostream>
#include "StMakeDataQA_Gamma.h"
#include "StMcAccpTracks.h"
#include "StMcAccpEventCount.h"
#include "StPheRecoPair.h"
#include "StPheRecoTrack.h"
#include "TFile.h"
#include "TNtuple.h"
#include "cmath"
using namespace std;

ClassImp(StMakeDataQA_Gamma)
  
StMakeDataQA_Gamma::StMakeDataQA_Gamma(const char* outName)
{
  
  mOutputFile=new TFile(outName,"RECREATE");

}
 StMakeDataQA_Gamma::~StMakeDataQA_Gamma()
{

  //..
  //
}
void StMakeDataQA_Gamma::bookHistogram()
{ 
  cout<<"gbook histogram"<<endl;
  //
  // for(Int_t iTrg=0;iTrg<2;iTrg++)
  // {
  mDelta_Vz=new TH1F("mDelta_Vz","Vz",400,-1,1);
  //track
  mPhi_pt_cut=new TH2F ("mPhi_pt","",200,0,20,40,-4,4);
  mEta_pt_cut=new TH2F("mEta_pt","",200,0,20,30,-1.5,1.5);

  mHitFit_pt =new TH2F("mHitFit_pt","mHitFit_pt",200,0,20,60,0,60);
  mHitMax_pt=new TH2F("mHitMax_pt","mHitMax_pt",200,0,20,60,0,60);
  mHitsDedx=new TH2F("mHitsDedx","mHitsDedx",200,0,20,60,0,60);
  mNTrack=new TH1F("mNTrack","mNTrack",200,0,20);
   mFitPos_pt=new TH2F("mFitPos_pt","mFitPos_pt",200,0,20,100,0,1);
  mPoe=new TH2F("mPoe","mPoe",200,0,20,50,0,5);
  //cut

  mHitFit_pt_cut =new TH2F("mHitFit_pt_cut","mHitFit_pt_cut",200,0,20,60,0,60);
  mHitsDedx_cut=new TH2F("mHitsDedx_cut","mHitsDedx_cut",200,0,20,60,0,60);
  mFitPos_pt_cut=new TH2F("mFitPos_pt_cut","mFitPos_pt_cut",200,0,20,100,0,1);


  mNSMDEta_pt_cut=new TH2F("mNSMDEta_pt_cut","",200,0,20,10,0,10);
  mNSMDPhi_pt_cut=new TH2F("mNSMDPhi_pt_cut","",200,0,20,10,0,10);
 
  mDedx_pt_cut=new TH2F("mDedx_pt_cut","",200,0,20,60,1,6); 
  mgDca_pt_cut=new TH2F ("mgDca_pt_cut","",200,0,20,50,0,5);
  mNsigE_pt_cut=new TH2F("mNsigE_pt_cut","mNsigE_pt_cut",200,0,20,50,-5,5);
  mInvMass_pt_cut=new TH2F("mInvMass_pt_cut","",200,0,20,40,0,0.4); 
}
void StMakeDataQA_Gamma::read(TString fileName)
{
  //  cout<<"!!!!!!!!!!!!!!!!!read"<<endl;
  TFile * infile=new TFile(fileName.Data());
  //  TNtuple * mcTrack=(TNtuple*) infile->Get()
  // TNtuple* ntEventCount=(TNtuple*) infile->Get("eventCount");
  //  TNtuple* ntTracks=(TNtuple* ) infile->Get("tracksMC");
  if( TNtuple* ntTracks=(TNtuple* ) infile->Get("nt_sngl"));

      cout<<"   Get File"<<endl;
      TNtuple* ntTracks=(TNtuple* ) infile->Get("nt_sngl");
      TNtuple * ntPair=(TNtuple* )infile->Get("nt_pair");
  // cout<<ntEventCount->GetEntries()<<endl;
  //  StMcAccpEventCount* eventCount=new StMcAccpEventCount;
  // StMcAccpTracks* tracksMC=new StMcAccpTracks;
  StPheRecoTrack * tracksMC=new StPheRecoTrack; 
 tracksMC->Init(ntTracks);
 StPheRecoPair *Pair=new StPheRecoPair;
 Pair->Init(ntPair);
 // eventCount->Init(ntEventCount);
  
  // cout<<"  Entries"<<eventCount->GetEntries() <<endl;
  // cout<<"  Entries"<<tracksMC->GetEntries() <<endl; 
  
 // for (Int_t iEvent=0;iEvent<eventCount->GetEntries();iEvent++)//
 // {
 //   eventCount->GetEntry(iEvent);
      
 //   mDelta_Vz->Fill(abs(eventCount->vz-eventCount->mcVz));
 // }
  // cout<<"aa"<<endl;
  // cout<<"Track Entries "<<tracksMC->GetEntries()<<endl;
 for(Int_t iTrk=0;iTrk<tracksMC->GetEntries();iTrk++)
   {
     tracksMC->GetEntry(iTrk);
     if(tracksMC->dca<1.5 && tracksMC->nfit>20 && tracksMC->nDedxPts>15 
&& tracksMC->nfit/(Float_t)tracksMC->nmax > 0.52 
	&& sqrt(tracksMC->stpcx*tracksMC->stpcx+tracksMC->stpcy*tracksMC->stpcy)<73 
	&& 0<tracksMC->rpt && abs(tracksMC->eta)<0.7 &&tracksMC->bsmdNEta>1 
	&& tracksMC->bsmdNPhi>1 && 0.3<tracksMC->p/tracksMC->btowE0 
	&& tracksMC->p/tracksMC->btowE0<1.5 && tracksMC->nSigE<3 
	&& -1 <tracksMC->nSigE
	&& abs(tracksMC->bemcDistZ)<3
         && abs(tracksMC->bemcDistPhi)<0.015 )
       
       {
	 
	  //	  mPhi_pt_cut->Fill(tracksMC->pt,tracksMC->rphi);
	  // mEta_pt_cut->Fill(tracksMC->pt,tracksMC->reta);

	  //mHitFit_pt_cut->Fill(tracksMC->pt,tracksMC->nfit);
	  // mFitPos_pt_cut->Fill(tracksMC->pt,tracksMC->nfit/(Float_t)tracksMC->nmax);
	  // mHitsDedx_cut->Fill(tracksMC->pt,tracksMC->nDedxPts);

	  // mNSMDEta_pt_cut->Fill(tracksMC->pt,tracksMC->bsmdNEta);
	  // mNSMDPhi_pt_cut->Fill(tracksMC->pt,tracksMC->bsmdNPhi);
	  // mDedx_pt_cut->Fill(tracksMC->pt,tracksMC->dedx);
	  // mgDca_pt_cut->Fill(tracksMC->pt,tracksMC->dca);
	  // mNsigE_pt_cut->Fill(tracksMC->pt,tracksMC->nSigE);
	}
    }
  for(Int_t iPair=0;iPair<Pair->GetEntries();iPair++)
    {
      Pair->GetEntry(iPair);
      if( Pair->pairDCA<1 && Pair->p1nfit>20   && 0<Pair->p1rpt && Pair->p1ndedx>15 && Pair->p1nfit/(Float_t) Pair->p1nmax>0.52 && sqrt(Pair->p1stpcx*Pair->p1stpcx+Pair->p1stpcy*Pair->p1stpcy)<73 
&& 0<Pair->p2rpt && abs(Pair->p1eta)<0.7  && Pair->mcMassPair>0 
	  && Pair->mcMassPair<0.24 && Pair->p1dca<1.5 && abs(Pair->p1bemcDistZ)<3
	  && abs(Pair->p1bemcDistPhi)<0.015) 	
	{ cout<<"  pass   :!"<<endl;
	  mInvMass_pt_cut->Fill(Pair->pairPT,Pair->mcMassPair);
	  mPhi_pt_cut->Fill(Pair->p1pt,Pair->p1rphi);
          mEta_pt_cut->Fill(Pair->p1pt,Pair->p1reta);
	  mHitFit_pt_cut->Fill(Pair->p1pt,Pair->p1nfit);
	  mFitPos_pt_cut->Fill(Pair->p1pt,Pair->p1nfit/(Float_t)Pair->p1nmax);
	  mHitsDedx_cut->Fill(Pair->p1pt,Pair->p1ndedx);
	  
	  mNSMDEta_pt_cut->Fill(Pair->p1pt,Pair->p1bsmdNEta);
	  mNSMDPhi_pt_cut->Fill(Pair->p1pt,Pair->p1bsmdNPhi);
	  mDedx_pt_cut->Fill(Pair->p1pt,Pair->p1ndedx);
	  mgDca_pt_cut->Fill(Pair->p1pt,Pair->p1dca);
	  //  mHitFit_pt_cut->Fill(Pair->p1pt,Pair->p1nfit);
	  // mFitPos_pt_cut->Fill(Pair->p1pt,Pair->p1nfit/(Float_t)Pair->p1nmax);
	}
	
    }
   
  
}
void StMakeDataQA_Gamma::WriteHistogram()
{ 
  mOutputFile->cd();

  mPhi_pt_cut->Write();
  mEta_pt_cut->Write();

  mHitFit_pt_cut->Write();
  mFitPos_pt_cut->Write();
  mHitsDedx_cut->Write();

  mNSMDEta_pt_cut->Write();
  mNSMDPhi_pt_cut->Write();
  mDedx_pt_cut->Write();
  mgDca_pt_cut->Write();
  mNsigE_pt_cut->Write();
  mInvMass_pt_cut->Write();
  //
}
