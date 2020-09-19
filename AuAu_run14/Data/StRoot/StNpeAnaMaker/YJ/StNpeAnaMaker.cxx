/***********************************************************************************************
 * Wed Nov  2 16:57:04 CDT 2016
 * This class for read  run14 Anatree and  Fill all the No-phoronic electron realted histogram  *
 * By xiaozhi Bai xiaozhi@uic.edu                                                               *
 ***********************************************************************************************/
// StNpeAnaMaker.cxx

#include "StRoot/StPicoAnaTreeMaker/StAnaTree.h"
#include "StRoot/StPicoAnaTreeMaker/StPicoAnaTreeMaker.h"
#include "StRoot/StPicoAnaTreeMaker/StEventHeader.h"
#include "StRoot/StPicoAnaTreeMaker/StElectronTrack.h"
#include "StRoot/StPicoAnaTreeMaker/StHadronTrack.h"
#include "StRoot/StPicoAnaTreeMaker/StPartElectronTrack.h"
#include "StRoot/StPicoAnaTreeMaker/StMuonTrack.h"
#include "StRoot/StPicoAnaTreeMaker/StEEPair.h"
#include "StRoot/StPicoAnaTreeMaker/StPhoEEPair.h"
#include "StRoot/StPicoAnaTreeMaker/StEMuPair.h"
#include "StRoot/StPicoAnaTreeMaker/StMuMuPair.h"
#include "StRoot/StPicoAnaTreeMaker/StEmcTrigger.h"
#include "StMessMgr.h"
#include "StThreeVectorF.hh"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TF1.h"
#include "TRandom3.h"
#include "TLorentzVector.h"
#include "mBadRunList.h"
#include "StNpeAnaMaker.h"
#include "StCuts.h"
#include "iostream"
#include "StHistogram/Histogram.h"

const Int_t   nCentrals =10; 
const Float_t  eMass =0.000510999;
const Float_t  muMass= 0.1056583715;
Bool_t  HT_flag=1;
Bool_t  MB_flag=1;

ClassImp(StNpeAnaMaker)

//-----------------------------------------------------------------------------
StNpeAnaMaker::StNpeAnaMaker(const char* name, StPicoAnaTreeMaker *treeMaker, const char* outName)
: StMaker(name)
{
  mPicoAnaTreeMaker = treeMaker;
  mAnaTree = 0;
  TH1F:: SetDefaultSumw2();
  TH2F:: SetDefaultSumw2();
  TH3F:: SetDefaultSumw2();
  mOutName = outName;
  mNBadRuns_MB = sizeof(mBadRuns_MB)/sizeof(int);
  mNBadRuns_HT = sizeof(mBadRuns_HT)/sizeof(int);
  cout<< " start new file "<<endl; 
  //0 -BHT0, 1-BHT1, 2-BHT2, 3-BHT3, 4-MB
  triggers[0].push_back(-999);
  triggers[0].push_back(-999);
  
  triggers[1].push_back(450201);
  triggers[1].push_back(450211);
  triggers[2].push_back(450202);
  triggers[2].push_back(450212);
  triggers[3].push_back(450203);
  triggers[3].push_back(450213);
  //MB
  triggers[4].push_back(450050); // vpdmb-5-p-nobsmd-hlt (production_mid_2014, production_low_2014)
  triggers[4].push_back(450060); // vpdmb-5-p-nobsmd-hlt (production_mid_2014, production_low_2014)
  triggers[4].push_back(450005); // vpdmb-5-p-nobsmd (production_2014)
  triggers[4].push_back(450015); // vpdmb-5-p-nobsmd (production_2014, production_mid_2014, production_low_2014)
  triggers[4].push_back(450025); // vpdmb-5-p-nobsmd (production_mid_2014, production_low_2014)
  triggers[4].push_back(450010); // VPDMB-30 (production_2014, production_mid_2014, production_low_2014)
  triggers[4].push_back(450020); // VPDMB-30 (production_2014, production_mid_2014, production_low_2014)
  triggers[4].push_back(450011); // MB-mon (production_2014, production_mid_2014, production_low_2014)
  triggers[4].push_back(450021); // MB-mon (production_2014, production_mid_2014, production_low_2014)
  triggers[4].push_back(450009);   // vPDMB-5-p-nobsmd-ssd-hlt (production_mid_2014, production_low_2014) 


}
//----------------------------------------------------------------------------- 
StNpeAnaMaker::~StNpeAnaMaker(){
  /*  */
}
//----------------------------------------------------------------------------- 
Int_t StNpeAnaMaker::Init() {
  bool   bDEBUG =true;
  if(bDEBUG)cout<<"\nBeginning Init().."<<endl;
  hist = new Histogram(); 
  if(bDEBUG)cout<<"\nHistograms Initialised.."<<endl;
  hist->outputQaName =mOutName;
  if(bDEBUG)cout<<"HistogramsQa Loaded.";
  TString treeFileName;
  treeFileName =mOutName;
  fout = new TFile(treeFileName.Data(), "RECREATE");
  declareHistograms();
  return kStOK;
}
//----------------------------------------------------------------------------- 
Int_t StNpeAnaMaker::Finish() {
  fout->cd();
  hist->writeData(fout);
  fout->Write();
  fout->Close();
  // printCuts();
  return kStOK;
}
//-----------------------------------------------------------------------------
void StNpeAnaMaker::declareHistograms() {
  fout->cd();
  hnEvents = new TH1F("hnEvents","hnEvents",10,0,10);
  //  hnTracks = new TH1F("hnTracks","hnTracks",10,0,10);
}
//----------------------------------------------------------------------------- 
void StNpeAnaMaker::Clear(Option_t *opt) {
  
}
//----------------------------------------------------------------------------- 
Int_t StNpeAnaMaker::Make() {
  if(!mPicoAnaTreeMaker) {
    LOG_WARN << " No PicoAnaTreeMaker! Skip! " << endm;
    return kStOK;
  }
  mAnaTree = (StAnaTree *) mPicoAnaTreeMaker->anaTree();

  if(!mAnaTree) {
    LOG_WARN << " No AnaTree! Skip! " << endm;
    return kStOK;
  }
  StEventHeader* mEvent= (StEventHeader *)mAnaTree->event();
  if(!mEvent) {
    LOG_WARN << " No mEvent! Skip! " << endm;
    return kStWarn;
  }
  hnEvents->Fill(1.5); // counting the total number of events before bad run reject
  int runId = mEvent->runId();
  if(isMinBias(mEvent))      // reject bad run i MB
    {
      for(int i=0;i<mNBadRuns_MB;i++){
  	if(runId==mBadRuns_MB[i])
  	  {
  	    LOG_INFO<< " This is bad run !! rejected "<<endm;
	    return kStOK;
  	  }
      }
    }
  if(isBHT1(mEvent)||isBHT2(mEvent)||isBHT3(mEvent))   // reject bad run  HT
    {
      for(int i=0;i<mNBadRuns_HT;i++){
  	if(runId==mBadRuns_HT[i])
  	  {
  	    LOG_INFO<< " This is bad run !! rejected "<<endm;
	    return kStOK;
  	  }
      }
    }
  
  hnEvents->Fill(2.5); // counting the total number of events after bad run reject
  Int_t bTrg=-999;;
  if(pass_MB_trigger_selection(mEvent,bTrg)) 
    {
      hist->mh1nEvents[bTrg]->Fill(1.5);
      hnEvents->Fill(4.5); 
      hist->mh2hVzVsVpdVz_noCut[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->vzVpd());
      hist->mh2hVzVsDiff_noCut[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->primaryVertex().z()-mEvent->vzVpd());
      
      if(isGoodEvent(mEvent,bTrg)&&MB_flag) 
	{
	  hist->mh1nEvents[bTrg]->Fill(2.5);  
	  hist->mh2hVzVsVpdVz[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->vzVpd());
	  Fill_MB_Trigger_histogram(mAnaTree,bTrg);
	}

    }

  bTrg=-999;;
  if(pass_HT1_trigger_selection(mEvent,bTrg)) 
    {
      hist->mh1nEvents[bTrg]->Fill(1.5);
      hnEvents->Fill(5.5); 
      hist->mh2hVzVsVpdVz_noCut[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->vzVpd());
      hist->mh2hVzVsDiff_noCut[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->primaryVertex().z()-mEvent->vzVpd());
      
      if(isGoodEvent(mEvent,bTrg)&&HT_flag) 
	{
	  hist->mh1nEvents[bTrg]->Fill(2.5);  
	  hist->mh2hVzVsVpdVz[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->vzVpd());
	  Fill_HT_Trigger_histogram(mAnaTree,bTrg);
	}
    }
  bTrg=-999;
  if(pass_HT2_trigger_selection(mEvent,bTrg)) 
    {
      hist->mh1nEvents[bTrg]->Fill(1.5);
      hnEvents->Fill(6.5); 
      hist->mh2hVzVsVpdVz_noCut[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->vzVpd());
      hist->mh2hVzVsDiff_noCut[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->primaryVertex().z()-mEvent->vzVpd());
      if(isGoodEvent(mEvent,bTrg)&&HT_flag) 
	{
	  hist->mh1nEvents[bTrg]->Fill(2.5);  
	  hist->mh2hVzVsVpdVz[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->vzVpd());
	  Fill_HT_Trigger_histogram(mAnaTree,bTrg);
	}
    }
  bTrg=-999;;
  if(pass_HT3_trigger_selection(mEvent,bTrg)) 
    {

      hnEvents->Fill(7.5); 
      hist->mh1nEvents[bTrg]->Fill(1.5);
      hist->mh2hVzVsVpdVz_noCut[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->vzVpd());
      hist->mh2hVzVsDiff_noCut[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->primaryVertex().z()-mEvent->vzVpd());
      if(isGoodEvent(mEvent,bTrg)&&HT_flag) 
	{
	  hist->mh1nEvents[bTrg]->Fill(2.5);  
	  hist->mh2hVzVsVpdVz[bTrg]->Fill(mEvent->primaryVertex().z(),mEvent->vzVpd());
	  Fill_HT_Trigger_histogram(mAnaTree,bTrg);
	}
    }
  return kStOK;
  
}//end of make
void StNpeAnaMaker::Fill_MB_Trigger_histogram(StAnaTree *mAnaTree,int bTrg)
{
  for(unsigned int i=0;i<mAnaTree->numberOfETracks();i++)
    {
      StElectronTrack *eTrk = (StElectronTrack*)mAnaTree->eTrack(i);
      if(
	 pass_cut_Pt_Eta(eTrk)
	 &&pass_cut_GoodTrack(eTrk)
	 &&pass_cut_nsigmaE(eTrk)
	 &&pass_Tof_Match(eTrk)
	 &&pass_cut_Tof(eTrk)
	 &&pass_cut_poe_MB(eTrk))
	{
	  Fill_MB_Trigger_inclusive_histogram_without_HFT(eTrk,bTrg);
	  if(eTrk->isHFTTrack())
	    Fill_MB_Trigger_inclusive_histogram_with_HFT(eTrk,bTrg);
	}   
    }
  // now fill MB phe histogram 
  for( unsigned int ipair=0; ipair< mAnaTree->numberOfPhoEEPairs();ipair++){	
    StPhoEEPair* ee_Pair = (StPhoEEPair*) mAnaTree->phoEEPair(ipair);
    int primaryEIndex =  ee_Pair->primEIndex();
    int  partnerIndex = ee_Pair->partEIndex();
    StElectronTrack *eTrk1 = mAnaTree->eTrack(primaryEIndex);
    StPartElectronTrack *eTrk2 = mAnaTree->partETrack(partnerIndex);
    if(eTrk1->id()==eTrk2->id()) continue;
    if(!pass_cut_eePair(ee_Pair)) continue;
    if(
       pass_cut_Pt_Eta(eTrk1)
       &&pass_cut_GoodTrack(eTrk1)
       &&pass_cut_nsigmaE(eTrk1)
       &&pass_Tof_Match(eTrk1)
       &&pass_cut_Tof(eTrk1)
       &&pass_cut_poe_MB(eTrk1)
       &&pass_cut_GoodTrack_partner(eTrk2)      
       &&pass_cut_partner_electron(eTrk2)       
       //&&pass_cut_Tof_part(eTrk2)
       // &&pass_cut_poe_part(eTrk2)
       )
      {
	Fill_MB_Trigger_PHE_histogram_without_HFT(ee_Pair,eTrk1,eTrk2,bTrg);
	if(eTrk1->isHFTTrack())
	  Fill_MB_Trigger_PHE_histogram_with_HFT(ee_Pair,eTrk1,eTrk2,bTrg);
      }
  }
}
void StNpeAnaMaker::Fill_HT_Trigger_histogram(StAnaTree *mAnaTree,int bTrg)
{
  //---------------------------------------------loop hadron ------------------
  for(unsigned int i=0;i<mAnaTree->numberOfHTracks();i++){
    StHadronTrack *hTrk = (StHadronTrack*)mAnaTree->hTrack(i);
    
    if(hTrk->gMom().perp()>0.2&&fabs(hTrk->gMom().pseudoRapidity())<0.7&& abs(hTrk->nSigmaPion())<0.6&&hTrk->nHitsFit()>20&&abs(hTrk->dca())<1.5)
      {
	hist->mh1pi_pt[bTrg]->Fill(hTrk->gMom().perp());    
	if(hTrk->isHFTTrack())
	  hist->mh1pi_pt_HFT[bTrg]->Fill(hTrk->gMom().perp());    
      } 
  }
  //---------------------------------------------loop hadron ------------------
  // Fill_HT_Trigger_inclusive_histogram(mAnaTree,bTrg);
  for(unsigned int i=0;i<mAnaTree->numberOfETracks();i++){
    StElectronTrack *eTrk = (StElectronTrack*)mAnaTree->eTrack(i);
  
    int DSmAdc=0;
    if(eTrk->emcTriggerId()!=-1)
      {
    	StEmcTrigger *Emcpid= (StEmcTrigger *) mAnaTree->emcTrigger(eTrk->emcTriggerId()); 
    	DSmAdc=Emcpid->adc();
      } 
 
    if(bTrg==1&&DSmAdc<cuts::DSMadc_HT1) continue;
    if(bTrg==2&&DSmAdc<cuts::DSMadc_HT2) continue;
    if(bTrg==3&&DSmAdc<cuts::DSMadc_HT3) continue;
    
    if(bTrg==1&&eTrk->adc0()<cuts::adc0_HT1) continue;
    if(bTrg==2&&eTrk->adc0()<cuts::adc0_HT2) continue;
    if(bTrg==3&&eTrk->adc0()<cuts::adc0_HT3) continue;
    
    if(
       pass_cut_Pt_Eta(eTrk)
       &&pass_cut_GoodTrack(eTrk)
       &&pass_cut_nsigmaE(eTrk)
       // &&pass_cut_Match_BSMD(eTrk)
       // &&pass_cut_BSMD(eTrk)
       &&pass_cut_poe_HT(eTrk)
       )
      {
	Fill_HT_Trigger_inclusive_histogram_without_HFT(eTrk, bTrg);
	if(eTrk->isHFTTrack())
	  {
	    Fill_HT_Trigger_inclusive_histogram_with_HFT(eTrk,bTrg);
	  }
      }
  } // end of single Ht inclusive e loop
  
  for(unsigned int ipair=0; ipair< mAnaTree->numberOfPhoEEPairs();ipair++){	
    StPhoEEPair* ee_Pair = (StPhoEEPair*) mAnaTree->phoEEPair(ipair);
    int primaryEIndex =  ee_Pair->primEIndex();
    int  partnerIndex = ee_Pair->partEIndex();
    StElectronTrack *eTrk1 = mAnaTree->eTrack(primaryEIndex);
    StPartElectronTrack *eTrk2 = mAnaTree->partETrack(partnerIndex);
    
    if(eTrk1->id()==eTrk2->id()) continue;
    int DSmAdc=0;
    if(eTrk1->emcTriggerId()!=-1)
      {
    	StEmcTrigger *Emcpid= (StEmcTrigger *) mAnaTree->emcTrigger(eTrk1->emcTriggerId()); 
    	DSmAdc=Emcpid->adc();
      } 
    //    cout<< "DSMadc"<<  DSmAdc<<"  "<<eTrk1->adc0()<<endl;
    
    if(bTrg==1&&eTrk1->adc0()<cuts::adc0_HT1) continue;
    if(bTrg==2&&eTrk1->adc0()<cuts::adc0_HT2) continue;
    if(bTrg==3&&eTrk1->adc0()<cuts::adc0_HT3) continue;
    
    if(bTrg==1&&DSmAdc<cuts::DSMadc_HT1) continue;
    if(bTrg==2&&DSmAdc<cuts::DSMadc_HT2) continue;
    if(bTrg==3&&DSmAdc<cuts::DSMadc_HT3) continue;
    

    if(!pass_cut_eePair(ee_Pair)) continue;

    if(pass_cut_Pt_Eta(eTrk1)
       &&pass_cut_GoodTrack(eTrk1)
       &&pass_cut_nsigmaE(eTrk1)
       //  &&pass_cut_Match_BSMD(eTrk1 )
       // &&pass_cut_BSMD(eTrk1)
       &&pass_cut_poe_HT(eTrk1)
       &&pass_cut_GoodTrack_partner(eTrk2)
       // &&pass_cut_partner_electron(eTrk2)
       // &&pass_cut_poe_part(eTrk2)
       // &&pass_cut_BEMC_part(eTrk2)
       )
      {
	Fill_HT_Trigger_PHE_histogram_without_HFT(ee_Pair,eTrk1,eTrk2,bTrg);
	if(eTrk1->isHFTTrack())
	  Fill_HT_Trigger_PHE_histogram_with_HFT(ee_Pair,eTrk1,eTrk2,bTrg);
      }
  }
}
void  StNpeAnaMaker::Fill_HT_Trigger_inclusive_histogram_without_HFT(StElectronTrack *eTrk,int bTrg)
{
  hist->mh2NsigmaeVsPt[bTrg]->Fill(eTrk->nSigmaElectron(),eTrk->gMom().perp());
  hist->mh1inclusive_electron[bTrg]->Fill(eTrk->gMom().perp()); 
  hist->mh2dcaVsPt[bTrg]->Fill(eTrk->dca(),eTrk->gMom().perp()); 
  hist->mh2dcaXYVsPt[bTrg]->Fill(eTrk->dcaXY(),eTrk->gMom().perp()); 
  hist->mh2dcaZVsPt[bTrg]->Fill(eTrk->dcaZ(),eTrk->gMom().perp()); 
  return ;
}

void  StNpeAnaMaker::Fill_HT_Trigger_inclusive_histogram_with_HFT(StElectronTrack *eTrk,int bTrg)
{
  hist->mh2NsigmaeVsPt_HFT[bTrg]->Fill(eTrk->nSigmaElectron(),eTrk->gMom().perp());
  hist->mh1inclusive_electron_HFT[bTrg]->Fill(eTrk->gMom().perp()); 
  hist->mh2dcaVsPt_HFT[bTrg]->Fill(eTrk->dca(),eTrk->gMom().perp()); 
  hist->mh2dcaXYVsPt_HFT[bTrg]->Fill(eTrk->dcaXY(),eTrk->gMom().perp()); 
  hist->mh2dcaZVsPt_HFT[bTrg]->Fill(eTrk->dcaZ(),eTrk->gMom().perp()); 
  return ;

}
void  StNpeAnaMaker::Fill_HT_Trigger_PHE_histogram_with_HFT(StPhoEEPair *ee_Pair,StElectronTrack *eTrk1,StPartElectronTrack *eTrk2,Int_t bTrg)
{
  double PairMass = ee_Pair->pairMass();
  double PairDca = ee_Pair->pairDca();

  StThreeVectorF origin = ee_Pair->pairOrigin();

  if(eTrk1->charge()!=eTrk2->charge())
    {
      hist->mh3InvMassVsPtVsPairdca_HFT_unlike[bTrg]->Fill(PairMass,eTrk1->gMom().perp(),PairDca);
      hist->mh2InvMassVsPt_HFT_unlike[bTrg]->Fill(PairMass,eTrk1->gMom().perp());
      hist->mh2PairdcaVsPt_HFT_unlike[bTrg]->Fill(PairDca,eTrk1->gMom().perp());
      hist->mh2partnerNsigmaeVspt_HFT_unlike[bTrg]->Fill(eTrk2->nSigmaElectron(),eTrk2->gMom().perp());
      hist->mh2NsigmaeVspt_HFT_unlike[bTrg]->Fill(eTrk1->nSigmaElectron(),eTrk1->gMom().perp());

      hist->mh2Dz_HFT_unlike[bTrg]->Fill(eTrk1->zDist(),eTrk1->gMom().perp());
      hist->mh2Dphi_HFT_unlike[bTrg]->Fill(eTrk1->phiDist(),eTrk1->gMom().perp());
      hist->mh2Poe_HFT_unlike[bTrg]->Fill(eTrk1->gMom().perp(),eTrk1->gMom().mag()/eTrk1->e0());

      hist->mh2dcaVsPt_HFT_unlike[bTrg]->Fill(eTrk1->dca(),eTrk1->gMom().perp());
      hist->mh2dcaXYVsPt_HFT_unlike[bTrg]->Fill(eTrk1->dcaXY(),eTrk1->gMom().perp());
      hist->mh2dcaZVsPt_HFT_unlike[bTrg]->Fill(eTrk1->dcaZ(),eTrk1->gMom().perp());

    }
  if(eTrk1->charge()==eTrk2->charge())
    {
      hist->mh3InvMassVsPtVsPairdca_HFT_like[bTrg]->Fill(PairMass,eTrk1->gMom().perp(),PairDca);
      hist->mh2InvMassVsPt_HFT_like[bTrg]->Fill(PairMass,eTrk1->gMom().perp());
      hist->mh2PairdcaVsPt_HFT_like[bTrg]->Fill(PairDca,eTrk1->gMom().perp());
      hist->mh2partnerNsigmaeVspt_HFT_like[bTrg]->Fill(eTrk2->nSigmaElectron(),eTrk2->gMom().perp());
      hist->mh2NsigmaeVspt_HFT_like[bTrg]->Fill(eTrk1->nSigmaElectron(),eTrk1->gMom().perp());

      hist->mh2dcaVsPt_HFT_like[bTrg]->Fill(eTrk1->dca(),eTrk1->gMom().perp());
      hist->mh2dcaXYVsPt_HFT_like[bTrg]->Fill(eTrk1->dcaXY(),eTrk1->gMom().perp());
      hist->mh2dcaZVsPt_HFT_like[bTrg]->Fill(eTrk1->dcaZ(),eTrk1->gMom().perp());
      
      hist->mh2Dz_HFT_like[bTrg]->Fill(eTrk1->zDist(),eTrk1->gMom().perp());
      hist->mh2Dphi_HFT_like[bTrg]->Fill(eTrk1->phiDist(),eTrk1->gMom().perp());
      hist->mh2Poe_HFT_like[bTrg]->Fill(eTrk1->gMom().perp(),eTrk1->gMom().mag()/eTrk1->e0());
    }
}
void  StNpeAnaMaker::Fill_HT_Trigger_PHE_histogram_without_HFT(StPhoEEPair *ee_Pair,StElectronTrack *eTrk1,StPartElectronTrack *eTrk2,Int_t bTrg)
{
  double PairMass = ee_Pair->pairMass();
  double PairDca = ee_Pair->pairDca();
  
  StThreeVectorF origin = ee_Pair->pairOrigin();
  
  if(eTrk1->charge()!=eTrk2->charge())
    {
      hist->mh3InvMassVsPtVsPairdca_unlike[bTrg]->Fill(PairMass,eTrk1->gMom().perp(),PairDca);
      hist->mh2InvMassVsPt_unlike[bTrg]->Fill(PairMass,eTrk1->gMom().perp());

      hist->mh2PairdcaVsPt_unlike[bTrg]->Fill(PairDca,eTrk1->gMom().perp());

      hist->mh2dcaVsPt_unlike[bTrg]->Fill(eTrk1->dca(),eTrk1->gMom().perp());
      hist->mh2dcaXYVsPt_unlike[bTrg]->Fill(eTrk1->dcaXY(),eTrk1->gMom().perp());
      hist->mh2dcaZVsPt_unlike[bTrg]->Fill(eTrk1->dcaZ(),eTrk1->gMom().perp());

      hist->mh2partnerNsigmaeVspt_unlike[bTrg]->Fill(eTrk2->nSigmaElectron(),eTrk2->gMom().perp());
      hist->mh2NsigmaeVspt_unlike[bTrg]->Fill(eTrk1->nSigmaElectron(),eTrk1->gMom().perp());
      
      hist->mh2Dz_unlike[bTrg]->Fill(eTrk1->zDist(),eTrk1->gMom().perp());
      hist->mh2Dphi_unlike[bTrg]->Fill(eTrk1->phiDist(),eTrk1->gMom().perp());
      hist->mh2Poe_unlike[bTrg]->Fill(eTrk1->gMom().perp(),eTrk1->gMom().mag()/eTrk1->e0());
    }
  if(eTrk1->charge()==eTrk2->charge())
    {
      hist->mh3InvMassVsPtVsPairdca_like[bTrg]->Fill(PairMass,eTrk1->gMom().perp(),PairDca);
      hist->mh2InvMassVsPt_like[bTrg]->Fill(PairMass,eTrk1->gMom().perp());
      hist->mh2PairdcaVsPt_like[bTrg]->Fill(PairDca,eTrk1->gMom().perp());

      hist->mh2dcaVsPt_like[bTrg]->Fill(eTrk1->dca(),eTrk1->gMom().perp());
      hist->mh2dcaXYVsPt_like[bTrg]->Fill(eTrk1->dcaXY(),eTrk1->gMom().perp());
      hist->mh2dcaZVsPt_like[bTrg]->Fill(eTrk1->dcaZ(),eTrk1->gMom().perp());

      hist->mh2partnerNsigmaeVspt_like[bTrg]->Fill(eTrk2->nSigmaElectron(),eTrk2->gMom().perp());
      hist->mh2NsigmaeVspt_like[bTrg]->Fill(eTrk1->nSigmaElectron(),eTrk1->gMom().perp());
   
      hist->mh2Dz_like[bTrg]->Fill(eTrk1->zDist(),eTrk1->gMom().perp());
      hist->mh2Dphi_like[bTrg]->Fill(eTrk1->phiDist(),eTrk1->gMom().perp());
      hist->mh2Poe_like[bTrg]->Fill(eTrk1->gMom().perp(),eTrk1->gMom().mag()/eTrk1->e0());
    }
}
////////////////////////////////////////////////////
void  StNpeAnaMaker::Fill_MB_Trigger_PHE_histogram_with_HFT(StPhoEEPair *ee_Pair,StElectronTrack *eTrk1,StPartElectronTrack *eTrk2,Int_t bTrg)
{
  //  return;
  double PairMass = ee_Pair->pairMass();
  double PairDca = ee_Pair->pairDca();

  StThreeVectorF origin = ee_Pair->pairOrigin();

  if(eTrk1->charge()!=eTrk2->charge())
    {

      hist->mh2InvMassVsPt_HFT_unlike[bTrg]->Fill(PairMass,eTrk1->gMom().perp());
      hist->mh2PairdcaVsPt_HFT_unlike[bTrg]->Fill(PairDca,eTrk1->gMom().perp());
      hist->mh2dcaVsPt_HFT_unlike[bTrg]->Fill(eTrk1->dca(),eTrk1->gMom().perp());
      hist->mh2dcaXYVsPt_HFT_unlike[bTrg]->Fill(eTrk1->dcaXY(),eTrk1->gMom().perp());
      hist->mh2dcaZVsPt_HFT_unlike[bTrg]->Fill(eTrk1->dcaZ(),eTrk1->gMom().perp());

      hist->mh2ConversionXVsY_HFT_unlike[bTrg]->Fill(origin.x(),origin.y());
      hist->mh2ConversionRVsZ_HFT_unlike[bTrg]->Fill(origin.z(),sqrt(origin.x()*origin.x()+origin.y()*origin.y()));
      hist->mh2ConversionRVsPt_HFT_unlike[bTrg]->Fill(sqrt(origin.x()*origin.x()+origin.y()*origin.y()),eTrk1->gMom().perp());


      hist->mh2partnerNsigmaeVspt_HFT_unlike[bTrg]->Fill(eTrk2->nSigmaElectron(),eTrk2->gMom().perp());
      hist->mh2NsigmaeVspt_HFT_unlike[bTrg]->Fill(eTrk1->nSigmaElectron(),eTrk1->gMom().perp());

      hist->mh2Dz_HFT_unlike[bTrg]->Fill(eTrk1->zDist(),eTrk1->gMom().perp());
      hist->mh2Dphi_HFT_unlike[bTrg]->Fill(eTrk1->phiDist(),eTrk1->gMom().perp());
      hist->mh2Poe_HFT_unlike[bTrg]->Fill(eTrk1->gMom().perp(),eTrk1->gMom().mag()/eTrk1->e0());
    }
  if(eTrk1->charge()==eTrk2->charge())
    {
      hist->mh3InvMassVsPtVsPairdca_HFT_like[bTrg]->Fill(PairMass,eTrk1->gMom().perp(),PairDca);
      hist->mh2InvMassVsPt_HFT_like[bTrg]->Fill(PairMass,eTrk1->gMom().perp());
      hist->mh2PairdcaVsPt_HFT_like[bTrg]->Fill(PairDca,eTrk1->gMom().perp());
      hist->mh2dcaVsPt_HFT_like[bTrg]->Fill(eTrk1->dca(),eTrk1->gMom().perp());
      hist->mh2dcaXYVsPt_HFT_like[bTrg]->Fill(eTrk1->dcaXY(),eTrk1->gMom().perp());
      hist->mh2dcaZVsPt_HFT_like[bTrg]->Fill(eTrk1->dcaZ(),eTrk1->gMom().perp());

      hist->mh2ConversionXVsY_HFT_like[bTrg]->Fill(origin.x(),origin.y());
      hist->mh2ConversionRVsZ_HFT_like[bTrg]->Fill(origin.z(),sqrt(origin.x()*origin.x()+origin.y()*origin.y()));
      hist->mh2ConversionRVsPt_HFT_like[bTrg]->Fill(sqrt(origin.x()*origin.x()+origin.y()*origin.y()),eTrk1->gMom().perp());

      hist->mh2partnerNsigmaeVspt_HFT_like[bTrg]->Fill(eTrk2->nSigmaElectron(),eTrk2->gMom().perp());
      hist->mh2NsigmaeVspt_HFT_like[bTrg]->Fill(eTrk1->nSigmaElectron(),eTrk1->gMom().perp());
      
      hist->mh2Dz_HFT_like[bTrg]->Fill(eTrk1->zDist(),eTrk1->gMom().perp());
      hist->mh2Dphi_HFT_like[bTrg]->Fill(eTrk1->phiDist(),eTrk1->gMom().perp());
      hist->mh2Poe_HFT_like[bTrg]->Fill(eTrk1->gMom().perp(),eTrk1->gMom().mag()/eTrk1->e0());
    }
}
void  StNpeAnaMaker::Fill_MB_Trigger_PHE_histogram_without_HFT(StPhoEEPair *ee_Pair,StElectronTrack *eTrk1,StPartElectronTrack *eTrk2,Int_t bTrg)
{
  double PairMass = ee_Pair->pairMass();
  double PairDca = ee_Pair->pairDca();
  
  StThreeVectorF origin = ee_Pair->pairOrigin();
  
  if(eTrk1->charge()!=eTrk2->charge())
    {
      hist->mh3InvMassVsPtVsPairdca_unlike[bTrg]->Fill(PairMass,eTrk1->gMom().perp(),PairDca);
      hist->mh2InvMassVsPt_unlike[bTrg]->Fill(PairMass,eTrk1->gMom().perp());

      hist->mh2PairdcaVsPt_unlike[bTrg]->Fill(PairDca,eTrk1->gMom().perp());
      hist->mh2dcaVsPt_unlike[bTrg]->Fill(eTrk1->dca(),eTrk1->gMom().perp());
      hist->mh2dcaXYVsPt_unlike[bTrg]->Fill(eTrk1->dcaXY(),eTrk1->gMom().perp());
      hist->mh2dcaZVsPt_unlike[bTrg]->Fill(eTrk1->dcaZ(),eTrk1->gMom().perp());
      hist->mh2ConversionXVsY_unlike[bTrg]->Fill(origin.x(),origin.y());
      hist->mh2ConversionRVsZ_unlike[bTrg]->Fill(origin.z(),sqrt(origin.x()*origin.x()+origin.y()*origin.y()));
      hist->mh2ConversionRVsPt_unlike[bTrg]->Fill(sqrt(origin.x()*origin.x()+origin.y()*origin.y()),eTrk1->gMom().perp());

      hist->mh2partnerNsigmaeVspt_unlike[bTrg]->Fill(eTrk2->nSigmaElectron(),eTrk2->gMom().perp());
      hist->mh2NsigmaeVspt_unlike[bTrg]->Fill(eTrk1->nSigmaElectron(),eTrk1->gMom().perp());
      
      hist->mh2Dz_unlike[bTrg]->Fill(eTrk1->zDist(),eTrk1->gMom().perp());
      hist->mh2Dphi_unlike[bTrg]->Fill(eTrk1->phiDist(),eTrk1->gMom().perp());
      hist->mh2Poe_unlike[bTrg]->Fill(eTrk1->gMom().perp(),eTrk1->gMom().mag()/eTrk1->e0());
    }
  if(eTrk1->charge()==eTrk2->charge())
    {
      hist->mh3InvMassVsPtVsPairdca_like[bTrg]->Fill(PairMass,eTrk1->gMom().perp(),PairDca);
      hist->mh2InvMassVsPt_like[bTrg]->Fill(PairMass,eTrk1->gMom().perp());
      hist->mh2PairdcaVsPt_like[bTrg]->Fill(PairDca,eTrk1->gMom().perp());

      hist->mh2dcaVsPt_like[bTrg]->Fill(eTrk1->dca(),eTrk1->gMom().perp());
      hist->mh2dcaXYVsPt_like[bTrg]->Fill(eTrk1->dcaXY(),eTrk1->gMom().perp());
      hist->mh2dcaZVsPt_like[bTrg]->Fill(eTrk1->dcaZ(),eTrk1->gMom().perp());

      hist->mh2ConversionXVsY_like[bTrg]->Fill(origin.x(),origin.y());
      hist->mh2ConversionRVsZ_like[bTrg]->Fill(origin.z(),sqrt(origin.x()*origin.x()+origin.y()*origin.y()));
      hist->mh2ConversionRVsPt_like[bTrg]->Fill(sqrt(origin.x()*origin.x()+origin.y()*origin.y()),eTrk1->gMom().perp());

      hist->mh2partnerNsigmaeVspt_like[bTrg]->Fill(eTrk2->nSigmaElectron(),eTrk2->gMom().perp());
      hist->mh2NsigmaeVspt_like[bTrg]->Fill(eTrk1->nSigmaElectron(),eTrk1->gMom().perp());
   
      hist->mh2Dz_like[bTrg]->Fill(eTrk1->zDist(),eTrk1->gMom().perp());
      hist->mh2Dphi_like[bTrg]->Fill(eTrk1->phiDist(),eTrk1->gMom().perp());
      hist->mh2Poe_like[bTrg]->Fill(eTrk1->gMom().perp(),eTrk1->gMom().mag()/eTrk1->e0());
    }
}
void StNpeAnaMaker::Fill_MB_Trigger_inclusive_histogram_without_HFT(StElectronTrack* eTrk,int bTrg)
{
  hist->mh2NsigmaeVsPt[bTrg]->Fill(eTrk->nSigmaElectron(),eTrk->gMom().perp());
  hist->mh1inclusive_electron[bTrg]->Fill(eTrk->gMom().perp()); 
  hist->mh2dcaVsPt[bTrg]->Fill(eTrk->dca(),eTrk->gMom().perp()); 
  hist->mh2dcaXYVsPt[bTrg]->Fill(eTrk->dcaXY(),eTrk->gMom().perp()); 
  hist->mh2dcaZVsPt[bTrg]->Fill(eTrk->dcaZ(),eTrk->gMom().perp()); 


  return ;
}
void StNpeAnaMaker::Fill_MB_Trigger_inclusive_histogram_with_HFT(StElectronTrack* eTrk,int bTrg)
{
  hist->mh2NsigmaeVsPt_HFT[bTrg]->Fill(eTrk->nSigmaElectron(),eTrk->gMom().perp());
  hist->mh1inclusive_electron_HFT[bTrg]->Fill(eTrk->gMom().perp()); 
  hist->mh2dcaVsPt_HFT[bTrg]->Fill(eTrk->dca(),eTrk->gMom().perp()); 
  hist->mh2dcaXYVsPt_HFT[bTrg]->Fill(eTrk->dcaXY(),eTrk->gMom().perp()); 
  hist->mh2dcaZVsPt_HFT[bTrg]->Fill(eTrk->dcaZ(),eTrk->gMom().perp()); 


  return ;
}



Bool_t StNpeAnaMaker::pass_MB_trigger_selection(StEventHeader *evt, Int_t &bTrg)
{
  if(!evt) return kFALSE;
  if(isMinBias(evt)) 
    {
      bTrg = 0;
      return kTRUE;
    }
  else return kFALSE;
}

Bool_t StNpeAnaMaker::pass_HT1_trigger_selection(StEventHeader *evt, Int_t &bTrg)
{
  if(!evt) return kFALSE;
  if(isBHT1(evt)) 
    {
      bTrg = 1;
      return kTRUE;
    }
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_HT2_trigger_selection(StEventHeader *evt, Int_t &bTrg)
{
  if(!evt) return kFALSE;
  if(isBHT2(evt)) 
    {
      bTrg = 2;
      return kTRUE;
    }  

  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_HT3_trigger_selection(StEventHeader *evt, Int_t &bTrg)
{
  if(!evt) return kFALSE;
  if(isBHT3(evt)) 
    {  
      bTrg = 3;
      return kTRUE;
    } 
  else return kFALSE;
}
Bool_t StNpeAnaMaker::isGoodEvent(StEventHeader* evt,Int_t bTrg)
{
  if(!evt) return kFALSE;
  if(bTrg==0)
    {
      if(fabs(evt->primaryVertex().z())>=cuts::TpcVz_MB||fabs(evt->primaryVertex().z()-evt->vzVpd())>cuts::diff_vzVpdVz_MB) 
	return kFALSE;
    }
  if(bTrg==1)
    {
      if(fabs(evt->primaryVertex().z())>=cuts::TpcVz_HT1||fabs(evt->primaryVertex().z()-evt->vzVpd())>cuts::diff_vzVpdVz_HT1) 
	return kFALSE;
    }
  if(bTrg==2)
    {
      if(fabs(evt->primaryVertex().z())>=cuts::TpcVz_HT2||fabs(evt->primaryVertex().z()-evt->vzVpd())>cuts::diff_vzVpdVz_HT2) 
	return kFALSE;
    }
  if(bTrg==3)
    {
      if(fabs(evt->primaryVertex().z())>=cuts::TpcVz_HT3) 
	return kFALSE;
    }
  if(!(bTrg==0||bTrg==1||bTrg==2||bTrg==3)) return kFALSE;
  else  return kTRUE;
}
Bool_t StNpeAnaMaker::pass_cut_Pt_Eta(StElectronTrack *trk)
{
  Float_t Pt=trk->gMom().perp();
  Float_t eTa=trk->gMom().pseudoRapidity();
  if(fabs(eTa)<cuts::eta_max && Pt>cuts::pt_min)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_GoodTrack(StElectronTrack * trk)
{
  //  Float_t Pt=trk->gMom().perp();
  // Float_t eTa=trk->gMom().pseudoRapidity();
  Int_t nhitDedx=trk->nHitsDedx();
  Int_t nhitsFit=trk->nHitsFit();
  //  Int_t nhitsMax=trk->nHitsMax();
  Float_t gDca=trk->dca();
  
  if(gDca<cuts::gDca
     &&cuts::nhitDedx<nhitDedx
     &&nhitsFit>cuts::nhitsFit 
     )
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_Tof_Match(StElectronTrack *trk){
  
  if(cuts::max_pT_cut_Tof<=trk->gMom().perp())
    return kTRUE;
  
  Float_t tof_Ylaocal=trk->localY();
  if(fabs(tof_Ylaocal)<cuts::tof_Y
     // &&trk->btofMatchFlag()>0
     && trk->beta()>0)
    return kTRUE;
  else  return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_Tof( StElectronTrack *trk){

  if(cuts::max_pT_cut_Tof<=trk->gMom().perp())
    return kTRUE;
  Float_t tofbeta=trk->beta();
  if(fabs(1/tofbeta-1)<cuts::tofbeta)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_Tof_part( StPartElectronTrack *trk){

  if(cuts::max_pT_cut_Tof<=trk->gMom().perp())
    return kTRUE;
   
  Float_t tofbeta=trk->beta();
  if(fabs(1/tofbeta-1)<cuts::tofbeta)
    return kTRUE;
  else return kFALSE;
}

Bool_t StNpeAnaMaker::pass_cut_nsigmaE( StElectronTrack *trk){
  Float_t nsigamaE=trk->nSigmaElectron();
  if(nsigamaE<cuts::Nsigama_electron_high&&nsigamaE>cuts::Nsigama_electron_low)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_eePair( StPhoEEPair *Pair){
  
  Float_t pairMass=Pair->pairMass();
  Float_t Pairdca=Pair->pairDca();
  if(pairMass<cuts::InvMass&&Pairdca<cuts::pairDca)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_partner_electron(StPartElectronTrack *trk){
  
  Float_t nsigamaE=trk->nSigmaElectron();
  Float_t Pt=trk->gMom().perp();
  if(Pt<cuts::pt_min)
    return kFALSE;
  if(nsigamaE<cuts::nsigmaE_partner_high&&nsigamaE>cuts::nsigmaE_partner_low&& Pt>cuts::pt_min)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_GoodTrack_partner(StPartElectronTrack *trk)
{
  Float_t Pt=trk->gMom().perp();
  Float_t eTa=trk->gMom().pseudoRapidity();
  if(cuts::pt_min_partner<Pt&&fabs(eTa)<cuts::eta_partner)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_Match_BSMD(StElectronTrack * trk){
  if(cuts::min_pT_cut_BEMC>trk->gMom().perp())
    return kTRUE;
  if(cuts::Dz>=fabs(trk->zDist()) &&cuts::Dphi>=fabs(trk->phiDist()) )
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_BSMD(StElectronTrack *trk)
{

  if(cuts::min_pT_cut_BEMC>trk->gMom().perp())
    return kTRUE;

  Int_t nEta=trk->nEta();
  Int_t nPhi=trk->nPhi();
  if(nEta>=cuts::NEta && nPhi>=cuts::NPhi)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_BSMD_part(StPartElectronTrack *trk)
{

  if(cuts::min_pT_cut_BEMC>trk->gMom().perp())
    return kTRUE;

  Int_t nEta=trk->nEta();
  Int_t nPhi=trk->nPhi();
  if(nEta>=cuts::NEta && nPhi>=cuts::NPhi)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_poe_HT(StElectronTrack * trk)
{
  if(cuts::min_pT_cut_BEMC>trk->gMom().perp())
    return kTRUE;
  Float_t P=trk->gMom().mag();
  Float_t E=trk->e0();
  if(P/E>cuts::poe_low && P/E<cuts::poe_high)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_poe_MB(StElectronTrack * trk)
{

  if(cuts::min_pT_cut_BEMC>trk->gMom().perp())
    return kTRUE;
  
  Float_t P=trk->gMom().mag();
  Float_t E=trk->e0();
  if(P/E>cuts::poe_low && P/E<cuts::poe_high)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_poe_part(StPartElectronTrack * trk)
{

  if(cuts::min_pT_cut_BEMC>trk->gMom().perp())
    return kTRUE;
  
  Float_t P=trk->gMom().mag();
  Float_t E=trk->e0();
  if(P/E>cuts::poe_low && P/E<cuts::poe_high)
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::pass_cut_isHFT_track(StElectronTrack * trk)
{
  if(trk->isHFTTrack())
    return kTRUE;
  else return kFALSE;
}
Bool_t StNpeAnaMaker::checkTriggers(StEventHeader *evt,int trigType)
{
  for(auto trg = triggers[trigType].begin(); trg < triggers[trigType].end(); ++trg)
    {
      if(evt->isTrigger(*trg))
        return true;
    }
  return false;
}
Bool_t StNpeAnaMaker::isMinBias(StEventHeader *evt)
{ return checkTriggers(evt,4);}
Bool_t StNpeAnaMaker::isBHT0(StEventHeader *evt)
{
  return checkTriggers(evt,0);}
Bool_t StNpeAnaMaker::isBHT1(StEventHeader *evt) 
{ return checkTriggers(evt,1);}
Bool_t StNpeAnaMaker::isBHT2(StEventHeader *evt) 
{ return checkTriggers(evt,2);}
Bool_t StNpeAnaMaker::isBHT3(StEventHeader *evt) 
{ return checkTriggers(evt,3);}




