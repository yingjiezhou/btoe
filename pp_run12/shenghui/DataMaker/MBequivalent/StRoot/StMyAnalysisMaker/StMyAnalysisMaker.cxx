#include "StMyAnalysisMaker.h"
#include "StRoot/StPicoDstMaker/StPicoDst.h"
#include "StRoot/StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StPicoDstMaker/StPicoEvent.h"
#include "StRoot/StPicoDstMaker/StPicoUtilities.h"
#include "StDcaGeometry.h"

#include "StRoot/StPicoPrescales/prescales.h"
//#include "StRoot/StPicoPrescales/StPicoPrescalesConstants.h"
#include "StRoot/StPicoPrescales/StTRIGGERS.h"
//#include "StRoot/StPicoPrescales/StPicoPrescales.h"
#include "StThreeVectorF.hh"
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH1F.h"
#include "TH3F.h"
#include "TFile.h"
#include <map>
#include <iostream>
#include <fstream>
#include "../mBadRunList.h"

//#define BBCMB_TOF0         13
//#define HT0_BBCMB_TOF0     6
//#define BBCMB              2
//#define HT2_BBCMB          8

/*Bool_t fillhistflag=1;
  ofstream runidfiles;
  Int_t runIndex;
  Int_t randomId;
 *map<Int_t,Int_t> mTotalRunId;
 Int_t mTotalRun = 848;//603
 */

ClassImp(StMyAnalysisMaker)

	//-----------------------------------------------------------------------------
	//StMyAnalysisMaker::StMyAnalysisMaker(const char* name, StPicoDstMaker *picoMaker, const char* outName,int trigSelect)
	StMyAnalysisMaker::StMyAnalysisMaker(const char* name, StPicoDstMaker *picoMaker, const char* outName)
: StMaker(name)
{
	mPicoDstMaker = picoMaker;
	mPicoDst = 0;
	TH1F:: SetDefaultSumw2();//zaochen add
	mOutName = outName;
	//mTrigSelect = trigSelect;

	//mNBadRuns_HT0 = sizeof(mBadRuns_HT0)/sizeof(int);
	//mNBadRuns_HT2 = sizeof(mBadRuns_HT2)/sizeof(int);
	mNBadRuns_HT = sizeof(mBadRuns_HT)/sizeof(int);
}

//----------------------------------------------------------------------------- 
StMyAnalysisMaker::~StMyAnalysisMaker()
{ 
	delete mPrescales;
}
//----------------------------------------------------------------------------- 
Int_t StMyAnalysisMaker::Init() {
	if(mOutName!="") {
		fout = new TFile(mOutName.Data(),"RECREATE");
	}else{
		fout = new TFile("picoQA_test.root","RECREATE");
	}
	DeclareHistograms();
	return kStOK;
}

//----------------------------------------------------------------------------- 
Int_t StMyAnalysisMaker::Finish() {
	fout->cd();
	fout->Write();
	fout->Close();
	return kStOK;
}

//-----------------------------------------------------------------------------
void StMyAnalysisMaker::DeclareHistograms() {

	fout->cd();
	//std::string const prescalesFilesDirectoryName = "StRoot/run12pp200GeVPrescales";
	//mPrescales= new StPicoPrescales(prescalesFilesDirectoryName);
	mPrescales=prescales::Instance();

	//int nRuns = mPrescales->numberOfRuns();
	int nRuns = mPrescales->GetNumberOfRuns();
	TH1::SetDefaultSumw2();
	hnEvent       = new TH1F("nEvent","nEvent",10,0.,10.);
	hVzBBCMB_TOF0_R         = new TH1F("VzBBCMB_TOF0_R","Vz",800,-400.,400.);
	hVzHT0_BBCMB_TOF0_R     = new TH1F("VzHT0_BBCMB_TOF0_R","Vz",800,-400.,400.);
	hVzBBCMB_R              = new TH1F("VzBBCMB_R","Vz",800,-400.,400.);
	hVzHT2_BBCMB_R          = new TH1F("VzHT2_BBCMB_R","Vz",800,-400.,400.);
	hVzBBCMB_TOF0         = new TH1F("VzBBCMB_TOF0","Vz",800,-400.,400.);
	hVzHT0_BBCMB_TOF0     = new TH1F("VzHT0_BBCMB_TOF0","Vz",800,-400.,400.);
	hVzBBCMB              = new TH1F("VzBBCMB","Vz",800,-400.,400.);
	hVzHT2_BBCMB          = new TH1F("VzHT2_BBCMB","Vz",800,-400.,400.);

	mTotalBBCMB_forBHT0_EventsInRun_All = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_All","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_scale_All = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_scale_All","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun = new TH1F("mTotalBBCMB_forBHT0_EventsInRun","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_scale = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_scale","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_All_R = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_All_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_scale_All_R = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_scale_All_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_R = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_scale_R = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_scale_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_All = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_All","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_All_R = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_All_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_R = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_R = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_R","", nRuns+1, 0, nRuns+1);

	mTotalBBCMB_forBHT2_EventsInRun_All = new TH1F("mTotalBBCMB_forBHT2_EventsInRun_All","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT2_EventsInRun_scale_All = new TH1F("mTotalBBCMB_forBHT2_EventsInRun_scale_All","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT2_EventsInRun = new TH1F("mTotalBBCMB_forBHT2_EventsInRun","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT2_EventsInRun_scale = new TH1F("mTotalBBCMB_forBHT2_EventsInRun_scale","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT2_EventsInRun_All_R = new TH1F("mTotalBBCMB_forBHT2_EventsInRun_All_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT2_EventsInRun_scale_All_R = new TH1F("mTotalBBCMB_forBHT2_EventsInRun_scale_All_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT2_EventsInRun_R = new TH1F("mTotalBBCMB_forBHT2_EventsInRun_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT2_EventsInRun_scale_R = new TH1F("mTotalBBCMB_forBHT2_EventsInRun_scale_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT2_forBHT2_EventsInRun_All = new TH1F("mTotalBBCMBBHT2_forBHT2_EventsInRun_All","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT2_forBHT2_EventsInRun_scale_All = new TH1F("mTotalBBCMBBHT2_forBHT2_EventsInRun_scale_All","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT2_forBHT2_EventsInRun = new TH1F("mTotalBBCMBBHT2_forBHT2_EventsInRun","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT2_forBHT2_EventsInRun_All_R = new TH1F("mTotalBBCMBBHT2_forBHT2_EventsInRun_All_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT2_forBHT2_EventsInRun_scale_All_R = new TH1F("mTotalBBCMBBHT2_forBHT2_EventsInRun_scale_All_R","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT2_forBHT2_EventsInRun_R = new TH1F("mTotalBBCMBBHT2_forBHT2_EventsInRun_R","", nRuns+1, 0, nRuns+1);

	hVzBBCMB_TOF0_R_BBCMB         = new TH1F("VzBBCMB_TOF0_R_BBCMB","Vz",800,-400.,400.);
	hVzHT0_BBCMB_TOF0_R_BBCMB     = new TH1F("VzHT0_BBCMB_TOF0_R_BBCMB","Vz",800,-400.,400.);
	hVzBBCMB_TOF0_BBCMB         = new TH1F("VzBBCMB_TOF0_BBCMB","Vz",800,-400.,400.);
	hVzHT0_BBCMB_TOF0_BBCMB     = new TH1F("VzHT0_BBCMB_TOF0_BBCMB","Vz",800,-400.,400.);
	mTotalBBCMB_forBHT0_EventsInRun_All_BBCMB = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_All_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_scale_All_BBCMB = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_scale_All_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_BBCMB = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_scale_BBCMB = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_scale_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_All_R_BBCMB = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_All_R_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_scale_All_R_BBCMB = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_scale_All_R_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_R_BBCMB = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_R_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMB_forBHT0_EventsInRun_scale_R_BBCMB = new TH1F("mTotalBBCMB_forBHT0_EventsInRun_scale_R_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_All_BBCMB = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_All_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_BBCMB = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_BBCMB = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_All_R_BBCMB = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_All_R_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_R_BBCMB = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_R_BBCMB","", nRuns+1, 0, nRuns+1);
	mTotalBBCMBBHT0_forBHT0_EventsInRun_R_BBCMB = new TH1F("mTotalBBCMBBHT0_forBHT0_EventsInRun_R_BBCMB","", nRuns+1, 0, nRuns+1);
}

//----------------------------------------------------------------------------- 
void StMyAnalysisMaker::Clear(Option_t *opt) {

}

//----------------------------------------------------------------------------- 
Int_t StMyAnalysisMaker::Make() {

	if(!mPicoDstMaker) {
		LOG_WARN << " No PicoDstMaker! Skip! " << endm;
		return kStWarn;
	}

	mPicoDst = mPicoDstMaker->picoDst();
	if(!mPicoDst) {
		LOG_WARN << " No PicoDst! Skip! " << endm;
		return kStWarn;
	}

	StPicoEvent* event=mPicoDst->event();
	if(!event) {
		LOG_WARN << " No mEvent! Skip! " << endm;
		return kStWarn;
	}

	hnEvent->Fill(0);
	Double_t vztpc=event->primaryVertex().z();
	Double_t vxtpc=event->primaryVertex().x();
	Double_t vytpc=event->primaryVertex().y();
	Double_t vr=sqrt(vxtpc*vxtpc+vytpc*vytpc);
	if( fabs(vxtpc)<1.0e-5 && fabs(vytpc)<1.0e-5 && fabs(vztpc)<1.0e-5 ) return kStOK;
	hnEvent->Fill(1);
	if( fabs(vr)>=2. ) return kStOK;
	hnEvent->Fill(2);
	int RUNID = event->runId();
	for(int i=0;i<mNBadRuns_HT;i++){if(RUNID==mBadRuns_HT[i]) return kStOK; }
	hnEvent->Fill(3);
	/*/cout<<"mTrigSelect"<<mTrigSelect<<endl;
	  if(mTrigSelect==0){
	  for(int i=0;i<mNBadRuns_HT0;i++){ if(RUNID==mBadRuns_HT0[i]) return kStOK; }
	  }
	  else if(mTrigSelect==2){
	  for(int i=0;i<mNBadRuns_HT2;i++){ if(RUNID==mBadRuns_HT2[i]) return kStOK; }
	  }*/

	//Int_t RUNID = mPicoDst->event()->runId();
	Double_t ranking=event->ranking();
	int runindex = mPrescales->RunIndex(RUNID);
	//int runindex = mPrescales->runIndex(RUNID);
	//cout<<RUNID<<" "<<vztpc<<" "<<ranking<<" "<<mTriggerIDs[0]<<" "<<mTriggerIDs[1]<<endl;
	//if( ranking<=0. ) return kStOK;

	if(isBBCMB_TOF0(event) || isHT0_BBCMB_TOF0(event) || isBBCMB(event) || isHT2_BBCMB(event))
	{
		//if( fabs(vztpc)>35. ) return kStOK;

		float pscl_BBC_TOF0  = -1.;
		float pscl_BBCBHT0  = -1.;
		float pscl_BBC  = -1.;
		float pscl_BBCBHT2  = -1.;

		pscl_BBC_TOF0 = mPrescales->GetPrescale(RUNID, BBCMBTOF0);
		pscl_BBCBHT0 = mPrescales->GetPrescale(RUNID, HT0BBCMBTOF0);
		pscl_BBC = mPrescales->GetPrescale(RUNID, BBCMB);
		pscl_BBCBHT2 = mPrescales->GetPrescale(RUNID, HT2BBCMB);
		//pscl_BBC_TOF0 = mPrescales->prescale(RUNID, BBCMBTOF0);
		//pscl_BBCBHT0 = mPrescales->prescale(RUNID, HT0BBCMBTOF0);
		//pscl_BBC = mPrescales->prescale(RUNID, BBCMB);
		//pscl_BBCBHT2 = mPrescales->prescale(RUNID, HT2BBCMB);

		/*if(pscl_BBC_TOF0<=0||pscl_BBCBHT0<=0||pscl_BBC<=0||pscl_BBCBHT2<=0){
		  cout<<"-------------------------------------------"<<endl;
		  cout<<"pscl_BBC_TOF0: "<<pscl_BBC_TOF0<<endl;
		  cout<<"pscl_BBCBHT0: "<<pscl_BBCBHT0<<endl;
		  cout<<"pscl_BBC: "<<pscl_BBC<<endl;
		  cout<<"pscl_BBCBHT2: "<<pscl_BBCBHT2<<endl;
		  cout<<"trigger id "<<BBCMBTOF0<<" "<<HT0BBCMBTOF0<<" "<<BBCMB<<" "<<HT2BBCMB<<endl;
		  }*/
		float lvtm_BBC_TOF0  = -1.;
		float lvtm_BBCBHT0  = -1.;
		float lvtm_BBC  = -1.;
		float lvtm_BBCBHT2  = -1.;

		lvtm_BBC_TOF0 = mPrescales->GetLivetime(RUNID, BBCMBTOF0);
		lvtm_BBCBHT0 = mPrescales->GetLivetime(RUNID, HT0BBCMBTOF0);
		lvtm_BBC = mPrescales->GetLivetime(RUNID, BBCMB);
		lvtm_BBCBHT2 = mPrescales->GetLivetime(RUNID, HT2BBCMB);
		/*if(isBBCMB_TOF0(event)&&!(pscl_BBC_TOF0>0 && pscl_BBCBHT0>0 && lvtm_BBC_TOF0>0 && lvtm_BBCBHT0>0)){
		  cout<<"-------------------------------------------"<<endl;
		  cout<<"RUNID_BBCMB_TOF0 "<<RUNID<<endl;
		  }
		  if(isHT0_BBCMB_TOF0(event)&&!(pscl_BBC_TOF0>0 && pscl_BBCBHT0>0 && lvtm_BBC_TOF0>0 && lvtm_BBCBHT0>0)){
		  cout<<"-------------------------------------------"<<endl;
		  cout<<"RUNID_HT0 "<<RUNID<<endl;
		  }
		  if(isHT0_BBCMB_TOF0(event)&&!(pscl_BBC>0 && pscl_BBCBHT0>0 && lvtm_BBC>0 && lvtm_BBCBHT0>0)){
		  cout<<"-------------------------------------------"<<endl;
		  cout<<"RUNID_HT0_BBCMB "<<RUNID<<endl;
		  }
		  if(isBBCMB(event)&&!(pscl_BBC>0 && pscl_BBCBHT2>0 && lvtm_BBC>0 && lvtm_BBCBHT2>0)){
		  cout<<"-------------------------------------------"<<endl;
		  cout<<"RUNID_BBCMB "<<RUNID<<endl;
		  }
		  if(isHT2_BBCMB(event)&&!(pscl_BBC>0 && pscl_BBCBHT2>0 && lvtm_BBC>0 && lvtm_BBCBHT2>0)){
		  cout<<"-------------------------------------------"<<endl;
		  cout<<"RUNID_HT2 "<<RUNID<<endl;
		  }*/

		//cout<<pscl_BBC_TOF0<<" "<<pscl_BBCBHT0<<" "<<pscl_BBC<<" "<<pscl_BBCBHT2<<endl;
		//cout<<lvtm_BBC_TOF0<<" "<<lvtm_BBCBHT0<<" "<<lvtm_BBC<<" "<<lvtm_BBCBHT2<<endl;
		if(pscl_BBC_TOF0>0 && pscl_BBCBHT0>0 && lvtm_BBC_TOF0>0 && lvtm_BBCBHT0>0)
		{
			if(isBBCMB_TOF0(event)){
				hVzBBCMB_TOF0->Fill(vztpc);
				mTotalBBCMB_forBHT0_EventsInRun_All->Fill(runindex);
				mTotalBBCMB_forBHT0_EventsInRun_scale_All->Fill(runindex,pscl_BBC_TOF0);
				if(fabs(vztpc)<35.) mTotalBBCMB_forBHT0_EventsInRun->Fill(runindex);
				mTotalBBCMB_forBHT0_EventsInRun_scale->Fill(runindex, (1.*lvtm_BBCBHT0)/(1.*lvtm_BBC_TOF0)*(1.*pscl_BBC_TOF0)/(1.*pscl_BBCBHT0));
				if(ranking>0){
					hVzBBCMB_TOF0_R->Fill(vztpc);
					mTotalBBCMB_forBHT0_EventsInRun_All_R->Fill(runindex);
					mTotalBBCMB_forBHT0_EventsInRun_scale_All_R->Fill(runindex,pscl_BBC_TOF0);
					if(fabs(vztpc)<35.) mTotalBBCMB_forBHT0_EventsInRun->Fill(runindex);
					if(fabs(vztpc)<35.) mTotalBBCMB_forBHT0_EventsInRun_R->Fill(runindex);
					mTotalBBCMB_forBHT0_EventsInRun_scale_R->Fill(runindex, (1.*lvtm_BBCBHT0)/(1.*lvtm_BBC_TOF0)*(1.*pscl_BBC_TOF0)/(1.*pscl_BBCBHT0));
				}
			}
			if(isHT0_BBCMB_TOF0(event)){
				hVzHT0_BBCMB_TOF0->Fill(vztpc);
				mTotalBBCMBBHT0_forBHT0_EventsInRun_All->Fill(runindex);
				mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All->Fill(runindex,pscl_BBCBHT0);
				if(fabs(vztpc)<35.) mTotalBBCMBBHT0_forBHT0_EventsInRun->Fill(runindex);
				if(ranking>0){
					hVzHT0_BBCMB_TOF0_R->Fill(vztpc);
					mTotalBBCMBBHT0_forBHT0_EventsInRun_All_R->Fill(runindex);
					mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_R->Fill(runindex,pscl_BBCBHT0);
					if(fabs(vztpc)<35.) mTotalBBCMBBHT0_forBHT0_EventsInRun_R->Fill(runindex);
				}
			}
		}

		if(pscl_BBC>0 && pscl_BBCBHT2>0 && lvtm_BBC>0 && lvtm_BBCBHT2>0)
		{
			if(isBBCMB(event)){
				hVzBBCMB->Fill(vztpc);
				mTotalBBCMB_forBHT2_EventsInRun_All->Fill(runindex);
				mTotalBBCMB_forBHT2_EventsInRun_scale_All->Fill(runindex,pscl_BBC);
				if(fabs(vztpc)<35.)mTotalBBCMB_forBHT2_EventsInRun->Fill(runindex);
				mTotalBBCMB_forBHT2_EventsInRun_scale->Fill(runindex, (1.*lvtm_BBCBHT2)/(1.*lvtm_BBC)*(1.*pscl_BBC)/(1.*pscl_BBCBHT2));
				if(ranking>0){
					hVzBBCMB_R->Fill(vztpc);
					mTotalBBCMB_forBHT2_EventsInRun_All_R->Fill(runindex);
					mTotalBBCMB_forBHT2_EventsInRun_scale_All_R->Fill(runindex,pscl_BBC);
					if(fabs(vztpc)<35.)mTotalBBCMB_forBHT2_EventsInRun_R->Fill(runindex);
					mTotalBBCMB_forBHT2_EventsInRun_scale_R->Fill(runindex, (1.*lvtm_BBCBHT2)/(1.*lvtm_BBC)*(1.*pscl_BBC)/(1.*pscl_BBCBHT2));
				}
			}
			if(isHT2_BBCMB(event)){
				hVzHT2_BBCMB->Fill(vztpc);
				mTotalBBCMBBHT2_forBHT2_EventsInRun_All->Fill(runindex);
				mTotalBBCMBBHT2_forBHT2_EventsInRun_scale_All->Fill(runindex,pscl_BBCBHT2);
				if(fabs(vztpc)<35.) mTotalBBCMBBHT2_forBHT2_EventsInRun->Fill(runindex);
				if(ranking>0){
					hVzHT2_BBCMB_R->Fill(vztpc);
					mTotalBBCMBBHT2_forBHT2_EventsInRun_All_R->Fill(runindex);
					mTotalBBCMBBHT2_forBHT2_EventsInRun_scale_All_R->Fill(runindex,pscl_BBCBHT2);
					if(fabs(vztpc)<35.) mTotalBBCMBBHT2_forBHT2_EventsInRun_R->Fill(runindex);
				}
			}
		}
		if(pscl_BBC>0 && pscl_BBCBHT0>0 && lvtm_BBC>0 && lvtm_BBCBHT0>0)
		{
			if(isBBCMB(event)){
				hVzBBCMB_TOF0_BBCMB->Fill(vztpc);
				mTotalBBCMB_forBHT0_EventsInRun_All_BBCMB->Fill(runindex);
				mTotalBBCMB_forBHT0_EventsInRun_scale_All_BBCMB->Fill(runindex,pscl_BBC);
				if(fabs(vztpc)<35.) mTotalBBCMB_forBHT0_EventsInRun_BBCMB->Fill(runindex);
				mTotalBBCMB_forBHT0_EventsInRun_scale_BBCMB->Fill(runindex, (1.*lvtm_BBCBHT0)/(1.*lvtm_BBC)*(1.*pscl_BBC)/(1.*pscl_BBCBHT0));
				if(ranking>0){
					hVzBBCMB_TOF0_R_BBCMB->Fill(vztpc);
					mTotalBBCMB_forBHT0_EventsInRun_All_R_BBCMB->Fill(runindex);
					mTotalBBCMB_forBHT0_EventsInRun_scale_All_R_BBCMB->Fill(runindex,pscl_BBC);
					if(fabs(vztpc)<35.) mTotalBBCMB_forBHT0_EventsInRun_R_BBCMB->Fill(runindex);
					mTotalBBCMB_forBHT0_EventsInRun_scale_R_BBCMB->Fill(runindex, (1.*lvtm_BBCBHT0)/(1.*lvtm_BBC)*(1.*pscl_BBC)/(1.*pscl_BBCBHT0));
				}
			}
			if(isHT0_BBCMB_TOF0(event)){
				hVzHT0_BBCMB_TOF0_BBCMB->Fill(vztpc);
				mTotalBBCMBBHT0_forBHT0_EventsInRun_All_BBCMB->Fill(runindex);
				mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_BBCMB->Fill(runindex,pscl_BBCBHT0);
				if(fabs(vztpc)<35.) mTotalBBCMBBHT0_forBHT0_EventsInRun_BBCMB->Fill(runindex);
				if(ranking>0){
					hVzHT0_BBCMB_TOF0_R_BBCMB->Fill(vztpc);
					mTotalBBCMBBHT0_forBHT0_EventsInRun_All_R_BBCMB->Fill(runindex);
					mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_R_BBCMB->Fill(runindex,pscl_BBCBHT0);
					if(fabs(vztpc)<35.) mTotalBBCMBBHT0_forBHT0_EventsInRun_R_BBCMB->Fill(runindex);
				}
			}
		}
	}//BHT0 AND BHT2
	return kStOK;
}//end of main fucntion

bool StMyAnalysisMaker::isBBCMB_TOF0(StPicoEvent *event)
{
	int triggerWord = event->triggerWord();
	if(triggerWord>>BBCMBTOF0 & 0x1) return true;
	else return false;
}

//------------------------------------------------------------------
bool StMyAnalysisMaker::isHT0_BBCMB_TOF0(StPicoEvent *event)
{
	int triggerWord = event->triggerWord();
	if(triggerWord>>HT0BBCMBTOF0 & 0x1) return true;
	else return false;
}

//---------------------------------------------------  
bool StMyAnalysisMaker::isBBCMB(StPicoEvent *event)
{
	int triggerWord = event->triggerWord();
	if(triggerWord>>BBCMB & 0x1) return true;
	else return false;
}
//-----------------------------------------                                              
bool StMyAnalysisMaker::isHT2_BBCMB(StPicoEvent *event)
{
	int triggerWord = event->triggerWord();
	if(triggerWord>>HT2BBCMB & 0x1) return true;
	else return false;
}


//===================================================================


/*
//Int_t Nptrks = mPicoDst->numberOfTracks();
Float_t Ranking = mPicoDst->event()->ranking();
Float_t zdcx = mPicoDst->event()->ZDCx();
Float_t bbcx = mPicoDst->event()->BBCx();
zdcx=zdcx/1000.;
bbcx=bbcx/1000.;
Int_t Nmtdhits = mPicoDst->numberOfMtdHits();
Int_t Ntofhits = mPicoDst->numberOfBTofHits();
Int_t NRefmultPos=mPicoDst->event()->refMultPos();
Int_t NRefmultNeg=mPicoDst->event()->refMultNeg();
Int_t NGnremult=mPicoDst->event()->grefMult();
Int_t NRefmult=mPicoDst->event()->refMult();
Int_t NGtrks = mPicoDst->event()->numberOfGlobalTracks();
Int_t Ntofmatch = mPicoDst->event()->nBTOFMatch();
//	Int_t Nbemchits = mPicoDst->event()->
Int_t Nbemcmatch = mPicoDst->event()->nBEMCMatch();



*/
