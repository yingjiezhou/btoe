

/*
 *  
 *   3/17/2014/ xiaozhi bai
 *
 */
#include <iostream>
#include "StPhotonicReEff.h"
#include "StPair.h"
#include "StMcElectronTrack.h"
#include "TFile.h"
#include "TF1.h"
#include "TNtuple.h"
#include "TGraphErrors.h"
#include "cmath"
using namespace std;

ClassImp(StPhotonicReEff)
StPhotonicReEff::StPhotonicReEff(const char* outName)
{
  cout<< outName<< endl;
  
  mOutputFile=new TFile(outName,"RECREATE");
  TH1F::SetDefaultSumw2();  
  input=new TFile("/star/u/xiao00/work/Hijing_Pi0Dlitz_gamma_pi/histogram/StRoot/StReadAna/Weight.root","READ");
  pi_pt=(TH1D *) input->Get("Pi"); 
  gr_pi=new TGraphErrors(pi_pt);
}
StPhotonicReEff::~StPhotonicReEff()
{
  //
}
void StPhotonicReEff::bookHistogram()
{ 

   cout<<"gbook histogram"<<endl;

   


   // mc pt gamma
  mSingle_Track_pt_gamma=new TH1F("mSingle_Track_pt_gamma","",400,0,20);
  mSingle_Track_HFT_pt_gamma=new TH1F("mSingle_Track_HFT_pt_gamma","",400,0,20);
   // rc pt gamma
  mSingle_Track_rpt_gamma=new TH1F("mSingle_Track_rpt_gamma","",400,0,20);
  mSingle_Track_HFT_rpt_gamma=new TH1F("mSingle_Track_HFT_rpt_gamma","",400,0,20);

   // mc pt pi0
  mSingle_Track_pt_pi0=new TH1F("mSingle_Track_pt_pi0","",400,0,20);
  mSingle_Track_HFT_pt_pi0=new TH1F("mSingle_Track_HFT_pt_pi0","",400,0,20);
   // rc pt pi0
  mSingle_Track_rpt_pi0=new TH1F("mSingle_Track_rpt_pi0","",400,0,20);
  mSingle_Track_HFT_rpt_pi0=new TH1F("mSingle_Track_HFT_rpt_pi0","",400,0,20);

   for(Int_t ihist=0;ihist<nhist;ihist++)  
     {

       mh2massVsPt_gamma[ihist]=new TH2F(Form("mh2massVsPt_gammaHist%i",ihist),"",400,0,20,300,0,0.3);
       mh2massVsPt_pi0[ihist]=new TH2F(Form("mh2massVsPt_pi0Hist%i",ihist),"",400,0,20,300,0,0.3);;
       
       mh2massVsPt_gamma_unlike[ihist]=new TH2F(Form("mh2massVsPt_gamma_unlikeHist%i",ihist),"",400,0,20,300,0,0.3);
       mh2massVsPt_pi0_unlike[ihist]=new TH2F(Form("mh2massVsPt_pi0_unlikeHist%i",ihist),"",400,0,20,300,0,0.3);;

       mh2massVsPt_gamma_like[ihist]=new TH2F(Form("mh2massVsPt_gamma_likeHist%i",ihist),"",400,0,20,300,0,0.3);
       mh2massVsPt_pi0_like[ihist]=new TH2F(Form("mh2massVsPt_pi0_likeHist%i",ihist),"",400,0,20,300,0,0.3);;

       mh2pairdcaVsPt_gamma[ihist]=new TH2F(Form("mh2pairdcaVsPt_gammaHist%i",ihist),"",400,0,20,300,0,0.3);
       mh2pairdcaVsPt_pi0[ihist]=new TH2F(Form("mh2pairdcaVsPt_pi0Hist%i",ihist),"",400,0,20,300,0,0.3);;

       mh2pairdcaVsPt_gamma_unlike[ihist]=new TH2F(Form("mh2pairdcaVsPt_gamma_unlikeHist%i",ihist),"",400,0,20,300,0,0.3);
       mh2pairdcaVsPt_pi0_unlike[ihist]=new TH2F(Form("mh2pairdcaVsPt_pi0_unlikeHist%i",ihist),"",400,0,20,300,0,0.3);;

       mh2pairdcaVsPt_gamma_like[ihist]=new TH2F(Form("mh2pairdcaVsPt_gamma_likeHist%i",ihist),"",400,0,20,300,0,0.3);
       mh2pairdcaVsPt_pi0_like[ihist]=new TH2F(Form("mh2pairdcaVsPt_pi0_likeHist%i",ihist),"",400,0,20,300,0,0.3);;


       mPair_pt_gamma[ihist]=new TH1F(Form("mPair_pt_gammaHist%i",ihist),"",400,0,20);
       mPair_HFT_pt_gamma[ihist]=new TH1F(Form("mPair_HFT_pt_gammaHist%i",ihist),"",400,0,20);
       // rc pt gamma
       mPair_rpt_gamma[ihist]=new TH1F(Form("mPair_rpt_gammaHist%i",ihist),"",400,0,20);
       mPair_HFT_rpt_gamma[ihist]=new TH1F(Form("mPair_HFT_rpt_gammaHist%i",ihist),"",400,0,20);
       
       // mc pt pi0
       mPair_pt_pi0[ihist]=new TH1F(Form("mPair_pt_pi0Hist%i",ihist),"",400,0,20);
       mPair_HFT_pt_pi0[ihist]=new TH1F(Form("mPair_HFT_pt_pi0Hist%i",ihist),"",400,0,20);
       // rc pt pi0
       mPair_rpt_pi0[ihist]=new TH1F(Form("mPair_rpt_pi0Hist%i",ihist),"",400,0,20);
       mPair_HFT_rpt_pi0[ihist]=new TH1F(Form("mPair_HFT_rpt_pi0Hist%i",ihist),"",400,0,20);
     

     }
   
   mSingle_Track_pt_gamma->Sumw2();
   mSingle_Track_HFT_pt_gamma->Sumw2();

  mSingle_Track_rpt_gamma->Sumw2();
  mSingle_Track_HFT_rpt_gamma->Sumw2();

  mSingle_Track_pt_pi0->Sumw2();
  mSingle_Track_HFT_pt_pi0->Sumw2();

  mSingle_Track_rpt_pi0->Sumw2();
  mSingle_Track_HFT_rpt_pi0->Sumw2();

   for(Int_t ihist=0;ihist<nhist;ihist++)  
     {

       mh2massVsPt_gamma[ihist]->Sumw2();
       mh2massVsPt_pi0[ihist]->Sumw2();

       mh2massVsPt_gamma_unlike[ihist]->Sumw2();
       mh2massVsPt_pi0_unlike[ihist]->Sumw2();

       mh2massVsPt_gamma_like[ihist]->Sumw2();
       mh2massVsPt_pi0_like[ihist]->Sumw2();

       mh2pairdcaVsPt_gamma[ihist]->Sumw2();
       mh2pairdcaVsPt_pi0[ihist]->Sumw2();

       mh2pairdcaVsPt_gamma_unlike[ihist]->Sumw2();
       mh2pairdcaVsPt_pi0_unlike[ihist]->Sumw2();

       mh2pairdcaVsPt_gamma_like[ihist]->Sumw2();
       mh2pairdcaVsPt_pi0_like[ihist]->Sumw2();

       mPair_pt_gamma[ihist]->Sumw2();
       mPair_HFT_pt_gamma[ihist]->Sumw2();

       mPair_rpt_gamma[ihist]->Sumw2();
       mPair_HFT_rpt_gamma[ihist]->Sumw2();

       mPair_pt_pi0[ihist]->Sumw2();
       mPair_HFT_pt_pi0[ihist]->Sumw2();

       mPair_rpt_pi0[ihist]->Sumw2();
       mPair_HFT_rpt_pi0[ihist]->Sumw2();
     }
}
void StPhotonicReEff::read(TString fileName)
{ 
  TFile * infile=new TFile(fileName.Data());
  TNtuple* ntTracks=(TNtuple* ) infile->Get("nt_sngl");
  TNtuple * ntPair=(TNtuple* )infile->Get("nt_pair");
  StMcElectronTrack *tracksMC=new StMcElectronTrack(); 
  tracksMC->Init(ntTracks);
  StPair *Pair=new StPair();
  Pair->Init(ntPair);
  for(Int_t iTrk=0;iTrk<tracksMC->GetEntries();iTrk++)
    {
      tracksMC->GetEntry(iTrk);
      if(iTrk%2000==0)
	cout<<" working on single track "<<iTrk<<endl;
      // if((tracksMC->geantId==2||tracksMC->geantId==3)
      // 	 &&fabs(tracksMC->pt-tracksMC->rpt)/tracksMC->pt<1   
      // 	 &&abs(tracksMC->reta)<0.7&&tracksMC->rpt>0.2
      // 	 &&tracksMC->nfit>20&&tracksMC->nfit/tracksMC->nmax>0.52&&abs(tracksMC->dca)<1.5&&tracksMC->ncom>15)

      if((tracksMC->geantId==2||tracksMC->geantId==3)
	 &&fabs(tracksMC->vz)<6
         && tracksMC->dca<1.5 
	 && tracksMC->nfit>20 
         // && tracksMC->nDedxPts>15 
         && tracksMC->nfit/(Float_t)tracksMC->nmax > 0.52 
	 // && sqrt(tracksMC->stpcx*tracksMC->stpcx+tracksMC->stpcy*tracksMC->stpcy)<73 
	 &&0.2<tracksMC->rpt
	 &&10<tracksMC->ncom
	 && abs(tracksMC->rpt-tracksMC->pt)/tracksMC->pt<1
         && abs(tracksMC->eta)<0.7)
	{
	  Float_t weight=Weight(tracksMC->pt,tracksMC->ppt,tracksMC->gppt,tracksMC->geantId,tracksMC->pgeantId,tracksMC->gpgeantId); 
	  {
	    if(tracksMC->pgeantId==1&&tracksMC->gpgeantId==7)
	      {
		// mSingle_Track_pt_gamma->Fill(tracksMC->pt,weight);    
		// mSingle_Track_rpt_gamma->Fill(tracksMC->rpt,weight);    

		mSingle_Track_pt_gamma->Fill(tracksMC->pt);    
		mSingle_Track_rpt_gamma->Fill(tracksMC->rpt);    

		if(tracksMC->isHFT)
		  {
		    // mSingle_Track_HFT_pt_gamma->Fill(tracksMC->pt,weight);    
		    // mSingle_Track_HFT_rpt_gamma->Fill(tracksMC->rpt,weight);    
		 
		    mSingle_Track_HFT_pt_gamma->Fill(tracksMC->pt);    
		    mSingle_Track_HFT_rpt_gamma->Fill(tracksMC->rpt);    
		 
		  }
	      }
	    if(tracksMC->pgeantId==7)
	      {
		// mSingle_Track_pt_pi0->Fill(tracksMC->pt,weight);    
		// mSingle_Track_rpt_pi0->Fill(tracksMC->rpt,weight);    

		mSingle_Track_pt_pi0->Fill(tracksMC->pt);    
		mSingle_Track_rpt_pi0->Fill(tracksMC->rpt);    

		if(tracksMC->isHFT)
		  {
		    // mSingle_Track_HFT_pt_pi0->Fill(tracksMC->pt,weight);    
		    // mSingle_Track_HFT_rpt_pi0->Fill(tracksMC->rpt,weight);    
		 
		    mSingle_Track_HFT_pt_pi0->Fill(tracksMC->pt);    
		    mSingle_Track_HFT_rpt_pi0->Fill(tracksMC->rpt);    
		 
		  }
	      }
	  }
	}
    }
  //     return;
  // cout<< "finish single track "<<endl;
  for(Int_t iPair=0;iPair<Pair->GetEntries();iPair++)
    {
      //   cout<< Pair->p1eta<<endl;
      if(iPair%8000==0)
	cout<<" working on Pair "<<iPair<<endl;
      Pair->GetEntry(iPair);
      if((Pair->p1geantId==2||Pair->p1geantId==3)
	 &&fabs(Pair->vz)<6
         && Pair->p1dca<1.5 
	 && Pair->p1nfit>20 
         // && Pair->nDedxPts>15 
         && Pair->p1nfit/(Float_t)Pair->p1nmax > 0.52 
	 // && sqrt(Pair->stpcx*Pair->stpcx+Pair->stpcy*Pair->stpcy)<73 
	 &&0.2<Pair->p1rpt
	 &&10<Pair->p1ncom
	 && abs(Pair->p1rpt-Pair->p1pt)/Pair->p1pt<1
         && abs(Pair->p1eta)<0.7
	 &&(Pair->p2geantId==2||Pair->p2geantId==3)
	 // &&Pair->massDCA<0.24
	  &&Pair->p2rpt>0.2
	 &&abs(Pair->p2reta)<1
	 &&Pair->p2nfit>15
	 // &&Pair->pairDCA<1
	 &&Pair->p2ncom>10)
  	{ 
  	  Float_t weight= Weight(Pair->p1pt,Pair->p1ppt,Pair->p1gppt,Pair->p1geantId,Pair->p1pgeantId,Pair->p1gpgeantId); 
	  if(Pair->p1pgeantId==1&&Pair->p1gpgeantId==7&&Pair->massDCA<0.15)	 
	    {
	      if(Pair->p1svx==Pair->p2svx)
		{
		  mh2massVsPt_gamma[0]->Fill(Pair->p1pt,Pair->massDCA,weight);
		  mh2pairdcaVsPt_gamma[0]->Fill(Pair->p1pt,Pair->pairDCA,weight);	

		  mh2massVsPt_gamma[1]->Fill(Pair->p1pt,Pair->massDCA);
		  mh2pairdcaVsPt_gamma[1]->Fill(Pair->p1pt,Pair->pairDCA);	


		}
	      if(Pair->p1geantId!=Pair->p2geantId)
		{
		  mh2massVsPt_gamma_unlike[0]->Fill(Pair->p1pt,Pair->massDCA,weight);
		  mh2pairdcaVsPt_gamma_unlike[0]->Fill(Pair->p1pt,Pair->pairDCA,weight);	

		  mh2massVsPt_gamma_unlike[1]->Fill(Pair->p1pt,Pair->massDCA);
		  mh2pairdcaVsPt_gamma_unlike[1]->Fill(Pair->p1pt,Pair->pairDCA);	
		  mPair_pt_gamma[0]->Fill(Pair->p1pt);
		}
	      if(Pair->p1geantId==Pair->p2geantId)
		{
		  mh2massVsPt_gamma_like[0]->Fill(Pair->p1pt,Pair->massDCA,weight);
		  mh2pairdcaVsPt_gamma_like[0]->Fill(Pair->p1pt,Pair->pairDCA,weight);	

		  mh2massVsPt_gamma_like[1]->Fill(Pair->p1pt,Pair->massDCA);
		  mh2pairdcaVsPt_gamma_like[1]->Fill(Pair->p1pt,Pair->pairDCA);	
		  mPair_pt_pi0[1]->Fill(Pair->p1pt);
		}
	    }

	  ////////////////////////////////////////////////////////
	  // if(Pair->p1pgeantId==7&&Pair->p1gpgeantId==-9999)	 
	  //   {
	  //     if(Pair->p1svx==Pair->p2svx)
	  // 	{
	  // 	  mh2massVsPt_pi0[0]->Fill(Pair->p1pt,Pair->massDCA,weight);
	  // 	  mh2pairdcaVsPt_pi0[0]->Fill(Pair->p1pt,Pair->pairDCA,weight);	

	  // 	  mh2massVsPt_pi0[1]->Fill(Pair->p1pt,Pair->massDCA);
	  // 	  mh2pairdcaVsPt_pi0[1]->Fill(Pair->p1pt,Pair->pairDCA);	


	  // 	}
	  //     if(Pair->p1geantId!=Pair->p2geantId)
	  // 	{
	  // 	  mh2massVsPt_pi0_unlike[0]->Fill(Pair->p1pt,Pair->massDCA,weight);
	  // 	  mh2pairdcaVsPt_pi0_unlike[0]->Fill(Pair->p1pt,Pair->pairDCA,weight);	

	  // 	  mh2massVsPt_pi0_unlike[1]->Fill(Pair->p1pt,Pair->massDCA);
	  // 	  mh2pairdcaVsPt_pi0_unlike[1]->Fill(Pair->p1pt,Pair->pairDCA);	

	  // 	}
	  //     if(Pair->p1geantId==Pair->p2geantId)
	  // 	{
	  // 	  mh2massVsPt_pi0_like[0]->Fill(Pair->p1pt,Pair->massDCA,weight);
	  // 	  mh2pairdcaVsPt_pi0_like[0]->Fill(Pair->p1pt,Pair->pairDCA,weight);	

	  // 	  mh2massVsPt_pi0_like[1]->Fill(Pair->p1pt,Pair->massDCA);
	  // 	  mh2pairdcaVsPt_pi0_like[1]->Fill(Pair->p1pt,Pair->pairDCA);	
	  // 	}
	  //   }

	  ///////////////////////////////////////////////////////////////////////
	  if(Pair->p1pgeantId==7&&Pair->massDCA<0.15)	 
	    {
	      if(Pair->p1svx==Pair->p2svx)
		{
		  mh2massVsPt_pi0[2]->Fill(Pair->p1pt,Pair->massDCA,weight);
		  mh2pairdcaVsPt_pi0[2]->Fill(Pair->p1pt,Pair->pairDCA,weight);	

		  mh2massVsPt_pi0[3]->Fill(Pair->p1pt,Pair->massDCA);
		  mh2pairdcaVsPt_pi0[3]->Fill(Pair->p1pt,Pair->pairDCA);	

		  mPair_pt_pi0[0]->Fill(Pair->p1pt);

		}
	      if(Pair->p1geantId!=Pair->p2geantId)
		{
		  mh2massVsPt_pi0_unlike[2]->Fill(Pair->p1pt,Pair->massDCA,weight);
		  mh2pairdcaVsPt_pi0_unlike[2]->Fill(Pair->p1pt,Pair->pairDCA,weight);	

		  mh2massVsPt_pi0_unlike[3]->Fill(Pair->p1pt,Pair->massDCA);
		  mh2pairdcaVsPt_pi0_unlike[3]->Fill(Pair->p1pt,Pair->pairDCA);	
		  mPair_pt_pi0[0]->Fill(Pair->p1pt);
		}
	      if(Pair->p1geantId==Pair->p2geantId)
		{
		  mh2massVsPt_pi0_like[2]->Fill(Pair->p1pt,Pair->massDCA,weight);
		  mh2pairdcaVsPt_pi0_like[2]->Fill(Pair->p1pt,Pair->pairDCA,weight);	

		  mh2massVsPt_pi0_like[3]->Fill(Pair->p1pt,Pair->massDCA);
		  mh2pairdcaVsPt_pi0_like[3]->Fill(Pair->p1pt,Pair->pairDCA);	
		  mPair_pt_pi0[1]->Fill(Pair->p1pt);
		}
	    }

	      // mh2massVsPt_pi0[0]->Fill(Pair->p1pt,Pair->massDCA,weight);
	      // mh2pairdcaVsPt_pi0[0]->Fill(Pair->p1pt,Pair->pairDCA,weight);
	      

	      // if(Pair->p1svx==Pair->p2svx)
	      // 	{
	      // 	  mPair_pt_pi0[0]->Fill(Pair->p1pt,weight);
	      // 	}

	      // if(Pair->p2rpt>0.3&&Pair->p1svx==Pair->p2svx)
	      // 	{
	      // 	  mPair_pt_pi0[1]->Fill(Pair->p1pt,weight);
	      // 	}
	      // if(Pair->pairDCA<0.2&&(Pair->massDCA<0.05||Pair->p1pt>1.5))
	      // 	{	
	      // 	  mPair_pt_pi0[2]->Fill(Pair->p1pt,weight);
	      // 	}
	      // if(Pair->massDCA<0.06)
	      // 	{
	      // 	  mPair_pt_pi0[3]->Fill(Pair->p1pt,weight);
	      // 	}
	      // if(Pair->massDCA<0.1&&Pair->pairDCA<0.8)
	      // 	{
	      // 	  mPair_pt_pi0[4]->Fill(Pair->p1pt,weight);
	      // 	  if(Pair->p1geantId!=Pair->p2geantId)
	      // 	    mPair_rpt_pi0[0]->Fill(Pair->p1pt,weight);

	      // 	  if(Pair->p1geantId==Pair->p2geantId)
	      // 	    mPair_rpt_pi0[1]->Fill(Pair->p1pt,weight);
	      // 	}

	      // }


	}
    }
  //----------------------------------------------test1-------------------------------------------------------

	  //   //	    mPair_pt_gamma[0]->Fill(Pair->p1pt,weight);
	  //   {

	  //     mPair_rpt_gamma[0]->Fill(Pair->p1rpt,weight);
	  //     if(Pair->t1isHFT)
	  // 	{
	  // 	  mPair_HFT_pt_gamma[0]->Fill(Pair->p1pt,weight);
	  // 	  mPair_HFT_rpt_gamma[0]->Fill(Pair->p1rpt,weight);
	  // 	}
	  //   }
	  // if(Pair->p1pgeantId==7&&Pair->p1gpgeantId==-9999&&Pair->massDCA<0.24)
	  //   {
	  //     mPair_pt_pi0[1]->Fill(Pair->p1pt,weight);
	  //     mPair_rpt_pi0[1]->Fill(Pair->p1rpt,weight);
	  //     if(Pair->t1isHFT)
	  // 	{
	  // 	  mPair_HFT_pt_pi0[1]->Fill(Pair->p1pt,weight);
	  // 	  mPair_HFT_rpt_pi0[1]->Fill(Pair->p1rpt,weight);
	  // 	}
	  //   }


	  //}

}

void StPhotonicReEff::WriteHistogram()
{ 
    mOutputFile->cd();


    mSingle_Track_pt_gamma->Write();
    mSingle_Track_HFT_pt_gamma->Write();

    mSingle_Track_rpt_gamma->Write();
    mSingle_Track_HFT_rpt_gamma->Write();

    mSingle_Track_pt_pi0->Write();
    mSingle_Track_HFT_pt_pi0->Write();

    mSingle_Track_rpt_pi0->Write();
    mSingle_Track_HFT_rpt_pi0->Write();

    for(Int_t ihist=0;ihist<nhist;ihist++)  
      {

	mh2massVsPt_gamma[ihist]->Write();
	mh2massVsPt_pi0[ihist]->Write();

	mh2massVsPt_gamma_unlike[ihist]->Write();
	mh2massVsPt_pi0_unlike[ihist]->Write();

	mh2massVsPt_gamma_like[ihist]->Write();
	mh2massVsPt_pi0_like[ihist]->Write();

	mh2pairdcaVsPt_gamma[ihist]->Write();
	mh2pairdcaVsPt_pi0[ihist]->Write();

	mh2pairdcaVsPt_gamma_unlike[ihist]->Write();
	mh2pairdcaVsPt_pi0_unlike[ihist]->Write();

	mh2pairdcaVsPt_gamma_like[ihist]->Write();
	mh2pairdcaVsPt_pi0_like[ihist]->Write();
	mPair_pt_gamma[ihist]->Write();
	mPair_HFT_pt_gamma[ihist]->Write();

	mPair_rpt_gamma[ihist]->Write();
	mPair_HFT_rpt_gamma[ihist]->Write();

	mPair_pt_pi0[ihist]->Write();
	mPair_HFT_pt_pi0[ihist]->Write();

	mPair_rpt_pi0[ihist]->Write();
	mPair_HFT_rpt_pi0[ihist]->Write();
      }

    mOutputFile->Close();
  }
Double_t StPhotonicReEff::Weight(Float_t pt, Float_t ppt,Float_t gppt,Float_t geantId,Float_t pgeantId,Float_t gpgeantId)
{
  Double_t weight=0; 

  // if((geantId==8||geantId==9)||pt>0) // hadron 
  //   weight=gr_pi->Eval(pt);
  if(pgeantId==7&&(geantId==2||geantId==3)&&pt>0&&ppt>0&&ppt<60) // Dalitz
    weight=gr_pi->Eval(ppt); 
  if(gpgeantId==7&&pgeantId==1&&(geantId==2||geantId==3)&&pt>0&&ppt>0&&gppt>0&&gppt<60) // gamma 
    weight=gr_pi->Eval(gppt);
   return weight;
 }

