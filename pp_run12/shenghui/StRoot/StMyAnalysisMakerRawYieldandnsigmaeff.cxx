#include "StMyAnalysisMaker.h"
#include "StRoot/StPicoEvent/StPicoDst.h"
#include "StRoot/StPicoEvent/StPicoTrack.h"
#include "StRoot/StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StPicoEvent/StPicoEvent.h"
#include "StRoot/StPicoEvent/StPicoBEmcPidTraits.h"
#include "StRoot/StPicoEvent/StPicoEmcTrigger.h"
#include "StRoot/StPicoDstMaker/StPicoUtilities.h"
#include "StRoot/StPicoEvent/StPicoPhysicalHelix.h"
#include "StDcaGeometry.h"

#include "TVector3.h"
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include <map>
#include <iostream>
#include <fstream>
#include "mBadRunList.h"
#include "mHotTowerList.h"
Bool_t fillhistflag=1;
ofstream runidfiles;
Int_t runIndex;
Int_t randomId;
map<Int_t,Int_t> mTotalRunId;
Int_t mTotalRun = 848;//603


ClassImp(StMyAnalysisMaker)

	//-----------------------------------------------------------------------------
StMyAnalysisMaker::StMyAnalysisMaker(const char* name, StPicoDstMaker *picoMaker, const char* outName,int trigSelect)
	: StMaker(name)
{
	mPicoDstMaker = picoMaker;
	mPicoDst = 0;
	TH1F:: SetDefaultSumw2();
	TH2F:: SetDefaultSumw2();
	mOutName = outName;
	mTrigSelect = trigSelect;
	mTriggerIDs.clear();
	mTriggerIDs.push_back(370542);     // bht0 -bbcmb -tof0
	mTriggerIDs.push_back(370522);     // bht2 -bbcmb

	//mNBadRuns = sizeof(mBadRuns)/sizeof(int);
	mNBadRuns_HT0 = sizeof(mBadRuns_HT0)/sizeof(int);
	mNBadRuns_HT2 = sizeof(mBadRuns_HT2)/sizeof(int);

	MassE = 0.000511;
	VzCut = 35.;
	VzDiff = 6.;
	mHTth = 0;
	mHTAdc0th = 250;
	mEmcPtth = 2.5;
	nFPtsCutPart = 15;
	nFPtsCut = 20;    // >=20 require TPC track quality at least 20 out of 45
	ndEdxPtsCut = 15;    //10 ensure dEdx resolution is good
	PtsRMin = 0.52;  // >0.52 reject splitting tracks
	PtsRMax = 1.20;  // <1.20
	minPtCut = 1.5; // >0.2 pt below 0.2 efficiency is too low, acceptance limit
	dcaCut = 1.5;  // <2. ensure primary track for tag electron
	TPCFR = 73.;
	EtaCut = 0.7;    // |<1.
	PoeMin = 0.3;
	PoeMax = 1.5;
	DistZ = 3.0;
	DistPhi = 0.015;
	NEta = 2;
	NPhi = 2;
	PairDiffMax = 1.;   // <2cm ensure partner track is attached to tag electron
	PairDiffMin = 0.;
}

//----------------------------------------------------------------------------- 
StMyAnalysisMaker::~StMyAnalysisMaker()
{ 
	//delete mPrescales;
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
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();

	hnEvent     = new TH1F("nEvent","nEvent",10,0.,10.);
	hVpdVz      = new TH2F("vpdVz","vpdVz",400,-200.,200.,400,-200.,200.);
	hVpdVzcut   = new TH2F("vpdVzcut","vpdVzcut",200,-100.,100.,200,-100.,100.);
	hVzDiff     = new TH1F("VzDiff","",200,-20.,20.);
	//hVzDiffGood = new TH1F("VzDiffGood","",200,-20.,20.);
	//hBTOWERid   = new TH2F("BTOWERid","",35000,13.038000,13.073000,10000,0,10000.);
	hBTOWERid   = new TH1F("BTOWERid","",10000,0,10000.);
	hAdc0         = new TH2F("Adc0","",1000,0,20,1000,0,2000);
	hdsmAdc       = new TH2F("dsmAdc","",1000,0,20,100,0,100);
	hAdc0vsdsmAdc = new TH2F("Adc0vsdsmAdc","",1000,0,2000,100,0,100);
	hAdc0Cut          = new TH2F("Adc0Cut","",1000,0,20,1000,0,2000);
	hdsmAdcCut        = new TH2F("dsmAdcCut","",1000,0,20,100,0,100);
	hAdc0vsdsmAdcCut  = new TH2F("Adc0vsdsmAdcCut","",1000,0,2000,100,0,100);
	hNSigEEMC            = new TH2F("nSigEEMC","nSigEEMC",1000,0.,20.,400,-20.,20.);
	hNSigEPtEMC          = new TH2F("nSigEPtEMC","nSigEPtEMC",1000,0.,20.,400,-20.,20.);
	hNSigE            = new TH2F("nSigE","nSigE",1000,0.,20.,400,-20.,20.);
	hNSigEPt          = new TH2F("nSigEPt","nSigEPt",1000,0.,20.,400,-20.,20.);
	hnE               = new TH2F("hnE","nE",10,0,10,10,0,10);
	hmvsptEMC     = new TH2F("hmvsptEMC","m vs pt same event unlike EMC",1000,0.,20.,500,0.,0.5);
	hmvsptEMClike = new TH2F("hmvsptEMClike","m vs pt like EMC",1000,0.,20.,500,0.,0.5);
	hmvspt     = new TH2F("hmvspt","m vs pt same event unlike",1000,0.,20.,500,0.,0.5);
	hmvsptlike = new TH2F("hmvsptlike","m vs pt like",1000,0.,20.,500,0.,0.5);
	hNSigEeff          = new TH2F("nSigEeff","nSigEeff",1000,0.,20.,400,-20.,20.);
	hNSigEeffCut       = new TH2F("nSigEeffCut","nSigEeffCut",1000,0.,20.,400,-20.,20.);
	hNSigEeffTight     = new TH2F("nSigEeffTight","nSigEeffTight",1000,0.,20.,400,-20.,20.);
	hNSigEeffCutTight  = new TH2F("nSigEeffCutTight","nSigEeffCutTight",1000,0.,20.,400,-20.,20.);
	hNSigEeffVeryTight     = new TH2F("nSigEeffVeryTight","nSigEeffVeryTight",1000,0.,20.,400,-20.,20.);
	hNSigEeffCutVeryTight  = new TH2F("nSigEeffCutVeryTight","nSigEeffCutVeryTight",1000,0.,20.,400,-20.,20.);
	hTPCtracksTrigger  = new TH1F("TPCtracksTrigger","TPCtracksTrigger",1000,0.,20.);
	hSMDtracks   = new TH1F("SMDtracks","SMDtracks",1000,0.,20.);
	hAdc0PHE           = new TH2F("Adc0PHE","",1000,0,20,1000,0,2000);
	hdsmAdcPHE         = new TH2F("dsmAdcPHE","",1000,0,20,100,0,100);
	hAdc0vsdsmAdcPHE   = new TH2F("Adc0vsdsmAdcPHE","",1000,0,2000,100,0,100);
	hNSigEefflike      = new TH2F("nSigEefflike","nSigEefflike",1000,0.,20.,400,-20.,20.);
	hNSigEeffCutlike   = new TH2F("nSigEeffCutlike","nSigEeffCutlike",1000,0.,20.,400,-20.,20.);
	hNSigEeffTightlike = new TH2F("nSigEeffTightlike","nSigEeffTightlike",1000,0.,20.,400,-20.,20.);
	hNSigEeffCutTightlike = new TH2F("nSigEeffCutTightlike","nSigEeffCutTightlike",1000,0.,20.,400,-20.,20.);
	hNSigEeffVeryTightlike = new TH2F("nSigEeffVeryTightlike","nSigEeffVeryTightlike",1000,0.,20.,400,-20.,20.);
	hNSigEeffCutVeryTightlike = new TH2F("nSigEeffCutVeryTightlike","nSigEeffCutVeryTightlike",1000,0.,20.,400,-20.,20.);
	hTPCtracksTriggerlike = new TH1F("TPCtracksTriggerlike","TPCtracksTriggerlike",1000,0.,20.);
	hSMDtrackslike  = new TH1F("SMDtrackslike","SMDtrackslike",1000,0.,20.);
	hAdc0PHElike          = new TH2F("Adc0PHElike","",1000,0,20,1000,0,2000);
	hdsmAdcPHElike        = new TH2F("dsmAdcPHElike","",1000,0,20,100,0,100);
	hAdc0vsdsmAdcPHElike  = new TH2F("Adc0vsdsmAdcPHElike","",1000,0,2000,100,0,100);
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

	event=mPicoDst->event();
	if(!event) {
		LOG_WARN << " No mEvent! Skip! " << endm;
		return kStWarn;
	}

	hnEvent->Fill(0);

	TVector3 pVtx = event->primaryVertex();
	if(fabs(pVtx.X())<1e-5 && fabs(pVtx.Y())<1e-5 && fabs(pVtx.Z())<1e-5) return kStOK;
	hnEvent->Fill(1);
	float Vr = sqrt(pow(pVtx.X(),2.)+pow(pVtx.Y(),2.));
	if(Vr>=2)return kStOK;
	hnEvent->Fill(2);
	int RUNID = event->runId();
	//cout<<"mTrigSelect"<<mTrigSelect<<endl;
	if(mTrigSelect==0){
		for(int i=0;i<mNBadRuns_HT0;i++){ if(RUNID==mBadRuns_HT0[i]) return kStOK; }
	}
	else if(mTrigSelect==2){
		for(int i=0;i<mNBadRuns_HT2;i++){ if(RUNID==mBadRuns_HT2[i]) return kStOK; }
	}
	hnEvent->Fill(3);
	int eventPass = 0;
	if(mTrigSelect==0&&isHT0_BBCMB_TOF0(event, mTriggerIDs)){eventPass = 1; mHTth = 11; mHTAdc0th = 180; mEmcPtth = 2.5;}//HT0 180  Et>2.6
	else if(mTrigSelect==2&&isHT2_BBCMB(event, mTriggerIDs)) {eventPass = 1; mHTth = 18; mHTAdc0th = 304; mEmcPtth = 4.0;}//HT2 300 Et>4.2
	if(eventPass==0) return kStOK;
	hnEvent->Fill(4);

	float ranking=event->ranking();
	if( ranking<=0. ) return kStOK;
	hnEvent->Fill(5);
	float vpdVz = event->vzVpd();
	hVpdVz->Fill(vpdVz,pVtx.Z());
	if(fabs(pVtx.Z()) > VzCut) return kStOK;
	hnEvent->Fill(6);
	hVpdVzcut->Fill(vpdVz,pVtx.Z());
	hVzDiff->Fill(vpdVz - pVtx.Z());
	//hmVxy->Fill(pVtx.Y(), pVtx.Y());
	//hmVzx->Fill(pVtx.Z(), pVtx.Y());
	//if(fabs(vpdVz - pVtx.Z()) > VzDiff) continue;
	if(fabs(vpdVz - pVtx.Z()) < VzDiff) hnEvent->Fill(7);

	CurrentEvent_bField =event->bField()*kilogauss;
	CurrentEvent_nEs   = 0;
	CurrentEvent_nEMCE = 0;
	loopTrack();
	hnE->Fill(CurrentEvent_nEMCE,CurrentEvent_nEs);
	if(CurrentEvent_nEMCE < 1 || CurrentEvent_nEs < 1) return kStOK;; //at least find 1 pair candidate
	hnEvent->Fill(8);

	makerealevent();
	return kStOK;
}
//----------------------------------------------------------------------------- 
Int_t StMyAnalysisMaker::loopTrack() {
	TVector3 pVtx = event->primaryVertex();
	int nE = mPicoDst->numberOfTracks();
	//cout<<"CurrentEvent_nEs"<<CurrentEvent_nEs<<endl;
	for(int i=0;i<nE;i++){
		StPicoTrack* eTrk = (StPicoTrack*)mPicoDst->track(i);
		if(!eTrk) continue;
		if(!isGoodPartner(eTrk)) continue;
		TVector3 gmom = eTrk->gMom();
		TVector3 origin = eTrk->origin();
		int TOWIdPart = -999;
		Int_t bemcPidTraitsIndex = eTrk->bemcPidTraitsIndex();
		if(bemcPidTraitsIndex>=0){
		StPicoBEmcPidTraits *bemcPidTraitsPart   =  mPicoDst->bemcPidTraits(bemcPidTraitsIndex);
		TOWIdPart = bemcPidTraitsPart->btowId();
		}
		if(checkHotTower(TOWIdPart)) continue;
		
		if(fabs(gmom.PseudoRapidity())<1.0){
		CurrentEvent_EId[CurrentEvent_nEs]       = i;
		CurrentEvent_ECharge[CurrentEvent_nEs]   = eTrk->charge();
		CurrentEvent_EHelixPx[CurrentEvent_nEs]  = gmom.X();
		CurrentEvent_EHelixPy[CurrentEvent_nEs]  = gmom.Y();
		CurrentEvent_EHelixPz[CurrentEvent_nEs]  = gmom.Z();
		CurrentEvent_EHelixX[CurrentEvent_nEs]   = origin.X();
		CurrentEvent_EHelixY[CurrentEvent_nEs]   = origin.Y();
		CurrentEvent_EHelixZ[CurrentEvent_nEs]   = origin.Z();
		CurrentEvent_nEs ++;
		}
		if(!isGoodTrack(eTrk)) continue;
		float dca = eTrk->gDCA(pVtx).Mag();
		if(dca > dcaCut) continue;
		if(bemcPidTraitsIndex<0) continue;
		StPicoBEmcPidTraits *bemcPidTraits   =  mPicoDst->bemcPidTraits(bemcPidTraitsIndex);
		int TOWId = bemcPidTraits->btowId();
		hBTOWERid->Fill(TOWId);
		if(checkHotTower(TOWId)) continue;
		TVector3 pmom = eTrk->pMom();
		float pp    = pmom.Mag();
		float ppt   = pmom.Perp();
		float nSigE = eTrk->nSigmaElectron();
		int dsmadc   = 0;
		int adc0     = bemcPidTraits->bemcAdc0();
		hAdc0->Fill(ppt, adc0);
		int nEmcTrigger = mPicoDst->numberOfEmcTriggers();
		for(int nEmc=0;nEmc<nEmcTrigger;nEmc++){
			StPicoEmcTrigger *emcTrg = (StPicoEmcTrigger*)mPicoDst->emcTrigger(nEmc);
			int emcTrgID=emcTrg->id();
			if(emcTrgID==TOWId){
				dsmadc = emcTrg->adc();
				hdsmAdc->Fill(ppt, dsmadc);
				hAdc0vsdsmAdc->Fill(adc0, dsmadc);
				break;
			}
		}
		int  isTriggered = 0;
		if(dsmadc>mHTth && adc0>mHTAdc0th) isTriggered = 1;
		if(!isTriggered) continue;
		if(isEMCTrack(eTrk,bemcPidTraits)){
			hNSigEEMC->Fill(pp, nSigE);
			hNSigEPtEMC->Fill(ppt, nSigE);
			if(isSMDTrack(eTrk,bemcPidTraits)){
			hNSigE->Fill(pp, nSigE);
			hNSigEPt->Fill(ppt, nSigE);
			}
			if(nSigE>-1.&&nSigE<3.){
				hAdc0Cut->Fill(ppt, adc0);
				hdsmAdcCut->Fill(ppt, dsmadc);
				hAdc0vsdsmAdcCut->Fill(adc0, dsmadc);
			}
		}
		float EMCE     = bemcPidTraits->bemcE();
		float EMCpovere = (EMCE>0) ? gmom.Mag()/EMCE : -999.;
		CurrentEvent_EMCEId[CurrentEvent_nEMCE]       = i;
		CurrentEvent_EMCECharge[CurrentEvent_nEMCE]   = eTrk->charge();
		CurrentEvent_EMCEPt[CurrentEvent_nEMCE]       = ppt;
		//CurrentEvent_EMCEEta[CurrentEvent_nEMCE]      = peta;
		//CurrentEvent_EMCEPhi[CurrentEvent_nEMCE]      = pphi;
		CurrentEvent_EMCEHelixPx[CurrentEvent_nEMCE]  = gmom.X();
		CurrentEvent_EMCEHelixPy[CurrentEvent_nEMCE]  = gmom.Y();
		CurrentEvent_EMCEHelixPz[CurrentEvent_nEMCE]  = gmom.Z();
		CurrentEvent_EMCEHelixX[CurrentEvent_nEMCE]   = origin.X();
		CurrentEvent_EMCEHelixY[CurrentEvent_nEMCE]   = origin.Y();
		CurrentEvent_EMCEHelixZ[CurrentEvent_nEMCE]   = origin.Z();
		//CurrentEvent_EMCETOWE[CurrentEvent_nEMCE]     = EMCE;
		CurrentEvent_EMCETOWpovere[CurrentEvent_nEMCE]= EMCpovere;
		CurrentEvent_EMCEDistZ[CurrentEvent_nEMCE]    = bemcPidTraits->bemcZDist();
		CurrentEvent_EMCEDistPhi[CurrentEvent_nEMCE]  = bemcPidTraits->bemcPhiDist();
		CurrentEvent_EMCESMDNEta[CurrentEvent_nEMCE]  = bemcPidTraits->bemcSmdNEta();
		CurrentEvent_EMCESMDNPhi[CurrentEvent_nEMCE]  = bemcPidTraits->bemcSmdNPhi();
		CurrentEvent_EMCEDsmADC[CurrentEvent_nEMCE]   = dsmadc;
		CurrentEvent_EMCEADC0[CurrentEvent_nEMCE]     = adc0;
		CurrentEvent_EMCENSigE[CurrentEvent_nEMCE]    = nSigE;
		CurrentEvent_nEMCE ++;
	}
	return kStOK;
}//end of main fucntion

//------------------------------------------------------------------
bool StMyAnalysisMaker::isHT0_BBCMB_TOF0(StPicoEvent *event, IntVec mTriggerIDs)
{
	if(event->isTrigger(mTriggerIDs[0])) return true;	
	else return false;
}
//-----------------------------------------                                              
bool StMyAnalysisMaker::isHT2_BBCMB(StPicoEvent *event, IntVec mTriggerIDs)
{
	if(event->isTrigger(mTriggerIDs[1])) return true;	
	else return false;
}
bool StMyAnalysisMaker::isGoodPartner(StPicoTrack* PeTrk)
{
	TVector3 gmom = PeTrk->gMom();
	float pt = gmom.Perp();
	if(pt <= 0.3) return false;
	//float eta = gmom.PseudoRapidity();
	//if(fabs(eta)>1.0) return false;
	float nhits = 1.*PeTrk->nHitsFit();
	int nhitmax = 1.*PeTrk->nHitsMax();
	float ratio = fabs(nhits)/nhitmax;
	if(fabs(nhits)<nFPtsCutPart) return false;
	if(ratio<PtsRMin || ratio>PtsRMax) return false;

	return true;
}
//-----------------------------------------                                              
bool StMyAnalysisMaker::isGoodTrack(StPicoTrack* TeTrk)
{
	TVector3 pmom = TeTrk->pMom();
	float pt = pmom.Perp();
	if(pt<minPtCut) return false;
	float eta = pmom.PseudoRapidity();
	if(fabs(eta)>EtaCut) return false;
	float nhits = 1.*TeTrk->nHitsFit();
	int nhitmax = 1.*TeTrk->nHitsMax();
	int nhitsdEdx = 1.*TeTrk->nHitsDedx();
	float ratio = fabs(nhits)/nhitmax;
	if(fabs(nhits)<nFPtsCut) return false;
	if(ratio<PtsRMin || ratio>PtsRMax) return false;
	if(nhitsdEdx<ndEdxPtsCut) return false;

	float Rx = TeTrk->origin().X();
	float Ry = TeTrk->origin().Y();
	float FirstTpcR = sqrt(Rx*Rx+Ry*Ry);
	if(FirstTpcR>=TPCFR) return false;

	return true;
}
bool StMyAnalysisMaker::isEMCTrack(StPicoTrack* TeTrk, StPicoBEmcPidTraits *TbemcPidTraits)
{
	TVector3 gmom = TeTrk->gMom();
	float gp      = gmom.Mag();
	float EMCE    = TbemcPidTraits->bemcE();
	float EMCpovere  = (EMCE>0) ? gp/EMCE : -999.;
	if(EMCE<0) return false;
	if(EMCpovere<PoeMin || EMCpovere>PoeMax) return false;

	return true;
}
bool StMyAnalysisMaker::isSMDTrack(StPicoTrack* TeTrk, StPicoBEmcPidTraits *TbemcPidTraits)
{
	float EMCDistZ   = TbemcPidTraits->bemcZDist();
	float EMCDistPhi = TbemcPidTraits->bemcPhiDist();
	int SMDNEta      = TbemcPidTraits->bemcSmdNEta();
	int SMDNPhi  = TbemcPidTraits->bemcSmdNPhi();
	if(fabs(EMCDistZ)>DistZ) return false;
	if(fabs(EMCDistPhi)>DistPhi) return false;
	if(SMDNEta<NEta) return false;
	if(SMDNPhi<NPhi) return false;

	return true;
}
//-----------------------------------------------------------------------
bool StMyAnalysisMaker::checkHotTower(int towId)
{
	Int_t   mNHotTower;
	mNHotTower = sizeof(mHotTower)/sizeof(int);

	for(int i=0; i < mNHotTower; i++)
	{
		if(towId == mHotTower[i])
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------
void StMyAnalysisMaker::makerealevent()
{
	TLorentzVector FourMom1(0,0,0,0);
	TLorentzVector FourMom2(0,0,0,0);
	TLorentzVector FourMomR(0,0,0,0);

	for(int i=0; i<CurrentEvent_nEMCE; i++) {
		TVector3 Helix1P(CurrentEvent_EMCEHelixPx[i],CurrentEvent_EMCEHelixPy[i],CurrentEvent_EMCEHelixPz[i]);
		TVector3 Helix1O(CurrentEvent_EMCEHelixX[i],CurrentEvent_EMCEHelixY[i],CurrentEvent_EMCEHelixZ[i]);
		int   charge1  = CurrentEvent_EMCECharge[i];
		StPicoPhysicalHelix Helix1(Helix1P,Helix1O,CurrentEvent_bField,charge1);

		for(int j=0; j<CurrentEvent_nEs; j++) {
			if(CurrentEvent_EMCEId[i] == CurrentEvent_EId[j]) continue;

			TVector3 Helix2P(CurrentEvent_EHelixPx[j],CurrentEvent_EHelixPy[j],CurrentEvent_EHelixPz[j]);
			TVector3 Helix2O(CurrentEvent_EHelixX[j],CurrentEvent_EHelixY[j],CurrentEvent_EHelixZ[j]);
			int   charge2  = CurrentEvent_ECharge[j];
			StPicoPhysicalHelix Helix2(Helix2P,Helix2O,CurrentEvent_bField,charge2);

			double aPathLength = (Helix2.pathLengths(Helix1)).first;
			double ePathLength = (Helix2.pathLengths(Helix1)).second;

			TVector3 aOrigin   = Helix2.at(aPathLength);
			TVector3 eOrigin   = Helix1.at(ePathLength);
			TVector3 V0Origin  = (aOrigin+eOrigin)*0.5;
			TVector3 diff      = aOrigin-eOrigin;

			if(diff.Mag()<PairDiffMin || diff.Mag()>PairDiffMax) continue;

			TVector3 V0Mom1 = Helix1.momentumAt(ePathLength,CurrentEvent_bField);
			FourMom1.SetVectM(V0Mom1,MassE);

			TVector3 V0Mom2 = Helix2.momentumAt(aPathLength,CurrentEvent_bField);
			FourMom2.SetVectM(V0Mom2,MassE);
			FourMomR.SetVectM(-V0Mom2,MassE);

			TLorentzVector dieFourMom = FourMom1 + FourMom2;

			float M    = dieFourMom.M();
			TLorentzVector dieRFourMom = FourMom1 + FourMomR;

			if(M>0.3)continue;
			float PtTag           = CurrentEvent_EMCEPt[i];
			//float EMCETOWE        = CurrentEvent_EMCETOWE[i];
			float EMCETOWpovere   = CurrentEvent_EMCETOWpovere[i];
			float EMCEDistZ       = CurrentEvent_EMCEDistZ[i]; 
			float EMCEDistPhi     = CurrentEvent_EMCEDistPhi[i];
			int   EMCESMDNEta     = CurrentEvent_EMCESMDNEta[i];
			int   EMCESMDNPhi     = CurrentEvent_EMCESMDNPhi[i];
			int   EMCEDsmADC      = CurrentEvent_EMCEDsmADC[i];
			int   EMCEADC0        = CurrentEvent_EMCEADC0[i];
			float EMCENSigE       = CurrentEvent_EMCENSigE[i];
			//float ETOWE           = CurrentEvent_ETOWE[j];
			int  isEMC = 0;
			int  isSMD = 0;
			if(EMCETOWpovere>PoeMin && EMCETOWpovere<PoeMax) isEMC = 1;
			if(fabs(EMCEDistZ)<DistZ && fabs(EMCEDistPhi)<DistPhi && EMCESMDNEta>=NEta && EMCESMDNPhi>=NPhi) isSMD = 1;
			if(charge1*charge2 == -1) {
				/////////////////////////////////////////////////////
				//PHE
				/////////////////////////////////////////////////////
				if(isEMC&&EMCENSigE>-1.&&EMCENSigE<3.) {
					hmvsptEMC->Fill(PtTag,M);
					if(isSMD) hmvspt->Fill(PtTag,M);
				}
				/////////////////////////////////////////////////////
				//nsigmae eff
				/////////////////////////////////////////////////////
				if(M<0.1&&isEMC){
					hNSigEeff->Fill(PtTag,EMCENSigE);
					if(isSMD) hNSigEeffCut->Fill(PtTag,EMCENSigE);
					if(M<0.05&&diff.Mag()<0.5){
						hNSigEeffTight->Fill(PtTag,EMCENSigE);
						if(isSMD) hNSigEeffCutTight->Fill(PtTag,EMCENSigE);
						if(M<0.005){
							hNSigEeffVeryTight->Fill(PtTag,EMCENSigE);
							if(isSMD) hNSigEeffCutVeryTight->Fill(PtTag,EMCENSigE);
						}
					}
				}
				if(M<0.1&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.){
					hAdc0PHE->Fill(PtTag, EMCEADC0);
					hdsmAdcPHE->Fill(PtTag, EMCEDsmADC);
					hAdc0vsdsmAdcPHE->Fill(EMCEADC0, EMCEDsmADC);
				}
			}
			else{
				/////////////////////////////////////////////////////
				//PHE
				/////////////////////////////////////////////////////
				if(isEMC&&EMCENSigE>-1.&&EMCENSigE<3.){
					hmvsptEMClike->Fill(PtTag,M);
					if(isSMD) hmvsptlike->Fill(PtTag,M);
				}
				/////////////////////////////////////////////////////
				//nsigmae eff
				/////////////////////////////////////////////////////
				if(M<0.1&&isEMC){ 
					hNSigEefflike->Fill(PtTag,EMCENSigE);
					if(isSMD) hNSigEeffCutlike->Fill(PtTag,EMCENSigE);
					if(M<0.05&&diff.Mag()<0.5){
						hNSigEeffTightlike->Fill(PtTag,EMCENSigE);
						if(isSMD) hNSigEeffCutTightlike->Fill(PtTag,EMCENSigE);
						if(M<0.005){
							hNSigEeffVeryTightlike->Fill(PtTag,EMCENSigE);
							if(isSMD) hNSigEeffCutVeryTightlike->Fill(PtTag,EMCENSigE);
						}
					}
				}
				if(M<0.1&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.){
					hAdc0PHElike->Fill(PtTag, EMCEADC0);
					hdsmAdcPHElike->Fill(PtTag, EMCEDsmADC);
					hAdc0vsdsmAdcPHElike->Fill(EMCEADC0, EMCEDsmADC);
				}
			}
		}//e2
	}//e1
}
