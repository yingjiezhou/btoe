#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class PlotFile;
#endif

#ifndef __CINT__
//#include <stdio.h>
#include <stdlib.h>
//#include "iostream.h"
//#include "iomanip.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "math.h"
#include <cstring>
#include "string.h"

#include "TROOT.h"
#include "TFile.h"

#include "TChain.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TRandom.h"
//#include "TMath.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TUnixSystem.h"
#include "TRandom3.h"
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "PicoDst.h"
#include "histogram.h"

#include "StPhysicalHelixD.h"
#include "SystemOfUnits.h"
#include "PhysicalConstants.h"
#include "mBadRunList.h"
//#include "mTriggerList.h"
#include "mHotTowerList.h"
using namespace std;

#define MassE 0.000511

//VzCut -30 +30, lots of material outside this region
#define VzCut 35.
//correlation between TPC-Vz and Vpd-Vz, remove pileup vertecies 
#define VzDiff 6.

//init cuts ------------------------------------------
//#define yLocalCut    1.8   // |<1.8 TOF local pad position cut to remove edge effect
//#define betaCut      0.03  // |<0.03 need check 1/beta width
#define nFPtsCut     20    // >=20 require TPC track quality at least 20 out of 45
#define nFPtsCutSys  25    // >=20 require TPC track quality at least 20 out of 45
#define ndEdxPtsCut  15    //10 ensure dEdx resolution is good
#define ndEdxPtsCutSys  18    //10 ensure dEdx resolution is good
#define PtsRMin      0.52  // >0.52 reject splitting tracks
#define PtsRMax      1.20  // <1.20
#define minPtCut     1.5   // >0.2 pt below 0.2 efficiency is too low, acceptance limit
#define dcaCut       1.5   // <2. ensure primary track for tag electron
#define dcaCutSys       1.0   // <2. ensure primary track for tag electron
#define TPCFR        73.
#define EtaCut       0.7    // |<1.
//#define yCut         1.    // |<1.
#define PoeMin      0.3
#define PoeMinSys      0.6
#define PoeMax      1.5
#define DistZ       3.0
#define DistPhi     0.015
#define NEta        2
#define NPhi        2
#define PairDiffMax  1.    // <2cm ensure partner track is attached to tag electron
#define PairDiffMin  0.    // >0
//#define nParSigEMin  -0.5    // Partner nSigE cut min
//#define nParSigEMax  3.0    // Partner nSigE cut max
//-----------------------------------------------------

int main(int argc, char **argv)
{
	if(argc != 3) exit(1);

	FileOutPut = "./out/NPE_";
	FileOutPut += argv[1];
	FileOutPut += "_";
	FileOutPut += argv[2];
	FileOutPut += ".root";

	cout << FileOutPut << endl;

	char listname[100];
	sprintf(listname,"List/%s.list",argv[1]);

	cout << listname << endl;

	//----------------------------------
	// Open files and add to the chain
	//----------------------------------
	TChain *chain = new TChain("PicoDst");
	char filename[512];
	ifstream *inputStream = new ifstream;
	inputStream->open(listname);
	if (!(inputStream)) {
		printf("can not open list file\n");
		return 0;
	}
	for(;inputStream->good();){
		inputStream->getline(filename,512);
		if(inputStream->good()) {
			TFile *ftmp = TFile::Open(filename);
			if(!ftmp||!(ftmp->IsOpen())||!(ftmp->GetNkeys())) {
				cout<<"something wrong"<<endl;
			} else {
				cout<<"read in "<<filename<<endl;
				chain->Add(filename);

			}
			delete ftmp;
		}
	}


	fout = new TFile(FileOutPut,"recreate");
	//--------------------
	// loop the chain
	//--------------------
	int nevents = (int)chain->GetEntries();
	cout << "== total entries : " << nevents << endl;

	PicoDst *t = new PicoDst(chain);

	mNBadRuns_HT = sizeof(mBadRuns_HT)/sizeof(int);
	/*int mBadRuns[100];
	  if(strcmp(argv[2], mTrigger[0]) == 0) {mNBadRuns = sizeof(mBadRuns_HT0)/sizeof(int); memcpy(mBadRuns,mBadRuns_HT0,sizeof(mBadRuns_HT0));}
	  else if(strcmp(argv[2], mTrigger[1]) == 0) {mNBadRuns = sizeof(mBadRuns_HT1)/sizeof(int); memcpy(mBadRuns,mBadRuns_HT1,sizeof(mBadRuns_HT1));}
	  else if(strcmp(argv[2], mTrigger[2]) == 0) {mNBadRuns = sizeof(mBadRuns_HT2)/sizeof(int); memcpy(mBadRuns,mBadRuns_HT2,sizeof(mBadRuns_HT2));}
	  */
	cout<<"mNBadRuns_HT"<<mNBadRuns_HT<<endl;

	for(int ie=0;ie<nevents;ie++){

		if(ie%100000==0) cout << "begin " << ie << "th entry...." << endl;
		t->GetEntry(ie);
		hnEvent->Fill(0);
		//initialize
		CurrentEvent_RunId =t->Event_mRunId[0];

		int realRunId=1;
		for(int i=0;i<mNBadRuns_HT;i++){
			if(CurrentEvent_RunId==mBadRuns_HT[i]) {
				cout<<"mBadRuns_HT"<<mBadRuns_HT[i]<<endl;
				realRunId=0; break;
			}
		}
		if(realRunId==0) continue;
		hnEvent->Fill(1);
		CurrentEvent_bField =t->Event_mBField[0]*kilogauss;
		CurrentEvent_Id     = -999;
		CurrentEvent_Vz     = -999.;

		if(!(((t->Event_mTriggerWord[0])>>6 & 0x1)||((t->Event_mTriggerWord[0])>>8 & 0x1))) continue; //bht0 -bbcmb -tof0 && bht2 -bbcmb select trigger
		int eventPass = 0;

		if((strcmp(argv[2], mTrigger[0]) == 0)&&((t->Event_mTriggerWord[0])>>6 & 0x1)){eventPass = 1; mHTth = 11; mHTAdc0th = 180; mHTAdc0thSys=196; mEmcPtth = 2.5;} //HT0 180  Et>2.6
		else if((strcmp(argv[2], mTrigger[1]) == 0)&&((t->Event_mTriggerWord[0])>>8 & 0x1)){ eventPass = 1;mHTth = 18; mHTAdc0th = 300; mHTAdc0thSys=316; mEmcPtth = 4.0;}  //HT2 300 Et>4.2
		if(eventPass==0) continue;
		hnEvent->Fill(2);
		CurrentEvent_Vz = t->Event_mPrimaryVertex_mX3[0];
		float vpdVz     = 0.01*t->Event_mVzVpd[0];
		hVpdVz->Fill(vpdVz,CurrentEvent_Vz);
		if(fabs(CurrentEvent_Vz) > VzCut) continue;
		hnEvent->Fill(3);
		hVpdVzcut->Fill(vpdVz,CurrentEvent_Vz);
		hVzDiff->Fill(vpdVz - CurrentEvent_Vz);
		float Ranking=t->Event_mRanking[0];
		//if(Ranking<=0)continue;
		if(Ranking>0)hnEvent->Fill(4);
		//if(fabs(vpdVz - CurrentEvent_Vz) > VzDiff) continue;
		if(fabs(vpdVz - CurrentEvent_Vz) < VzDiff) hnEvent->Fill(5);

		CurrentEvent_Id     = t->Event_mEventId[0];

		CurrentEvent_nEs   = 0;
		CurrentEvent_nEMCE = 0;

		int nTracks = t->Tracks_;

		for(int i=0; i<nTracks; i++) {
			///////////////////////////////////////////
			///////////////////////////
			//global partner electron//
			///////////////////////////
			if(!isGoodPartner(t,i)) continue;
			int TOWId    = t->Tracks_mBTOWId[i];
			if(checkHotTower(TOWId)) continue;
			int charge = (t->Tracks_mNHitsFit[i]<0) ? -1 : 1;
			float nSigE = 0.01*t->Tracks_mNSigmaElectron[i];
			TVector3 gmom(t->Tracks_mGMomentum_mX1[i],t->Tracks_mGMomentum_mX2[i],t->Tracks_mGMomentum_mX3[i]);
			float gp    = gmom.Mag();            
			float geta  = gmom.PseudoRapidity();
			//float gpt   = mom.Perp();
			TVector3 pmom(t->Tracks_mPMomentum_mX1[i],t->Tracks_mPMomentum_mX2[i],t->Tracks_mPMomentum_mX3[i]);
			float pp    = pmom.Mag();
			float ppt   = pmom.Perp();
			float peta  = pmom.PseudoRapidity();
			float dca     = (Float_t)t->Tracks_mGDca[i]/1000.;
			int nHitsFit  = 1.*t->Tracks_mNHitsFit[i];
			int nHitsDedx = t->Tracks_mNHitsDedx[i];
			float EMCE    = 0.001*t->Tracks_mBTOWE[i];
			float EMCpovere = (EMCE>0) ? gp/EMCE : -999.;
			float ZDist     = 0.01*t->Tracks_mBEMCDistZ[i];
			float PhiDist   = 0.0001*t->Tracks_mBEMCDistPhi[i];
			int nEta        = t->Tracks_mBSMDNEta[i];
			int nPhi        = t->Tracks_mBSMDNPhi[i];
			if(fabs(geta)<1.0) {
				CurrentEvent_EId[CurrentEvent_nEs]       = i;
				CurrentEvent_ECharge[CurrentEvent_nEs]   = charge;
				CurrentEvent_EPt[CurrentEvent_nEs]       = ppt;
				CurrentEvent_EEta[CurrentEvent_nEs]      = peta;
				CurrentEvent_EHelixPx[CurrentEvent_nEs]  = t->Tracks_mGMomentum_mX1[i];
				CurrentEvent_EHelixPy[CurrentEvent_nEs]  = t->Tracks_mGMomentum_mX2[i];
				CurrentEvent_EHelixPz[CurrentEvent_nEs]  = t->Tracks_mGMomentum_mX3[i];
				CurrentEvent_EHelixX[CurrentEvent_nEs]   = 0.01*t->Tracks_mOriginX[i];
				CurrentEvent_EHelixY[CurrentEvent_nEs]   = 0.01*t->Tracks_mOriginY[i];
				CurrentEvent_EHelixZ[CurrentEvent_nEs]   = 0.01*t->Tracks_mOriginZ[i];
				CurrentEvent_ENhitsFit[CurrentEvent_nEs] = nHitsFit;
				CurrentEvent_ENhitsDedx[CurrentEvent_nEs]= nHitsDedx;
				CurrentEvent_EDca[CurrentEvent_nEs]      = dca;
				CurrentEvent_ETOWE[CurrentEvent_nEs]     = EMCE;
				CurrentEvent_ETOWpovere[CurrentEvent_nEs]= EMCpovere;
				CurrentEvent_EDistZ[CurrentEvent_nEs]    = ZDist;
				CurrentEvent_EDistPhi[CurrentEvent_nEs]  = PhiDist;
				CurrentEvent_ESMDNEta[CurrentEvent_nEs]  = nEta;
				CurrentEvent_ESMDNPhi[CurrentEvent_nEs]  = nPhi;
				CurrentEvent_nEs ++;
			}

			///////////////////
			//tagged electron//
			///////////////////
			if(!isGoodTrack(t,i)) continue;
			int dsmadc   = -999;
			int adc0     = t->Tracks_mBTOWADC0[i];

			hAdc0->Fill(ppt, adc0);
			int nEmcTrigger = t->Trigger_;
			for(int nEmc=0;nEmc<nEmcTrigger;nEmc++){
				int emcTrgID=t->Trigger_mId[nEmc];
				if(emcTrgID==TOWId){
					dsmadc = t->Trigger_mAdc[nEmc];
					hdsmAdc->Fill(ppt, dsmadc);
					hAdc0vsdsmAdc->Fill(adc0, dsmadc);
					break;
				}
			}
			int  isTriggered = 0;
			if(dsmadc>mHTth && adc0>mHTAdc0th) isTriggered = 1;
			int  isTrackQ = 0;
			if(nHitsFit>=nFPtsCut&&nHitsDedx>=ndEdxPtsCut&&dca<dcaCut) isTrackQ = 1;
			if(isTriggered&&isTrackQ&&isEMCTrack(t,i)){
				hNSigE->Fill(pp, nSigE);
				hNSigEPt->Fill(ppt, nSigE);
				if(adc0>mHTAdc0thSys) hNSigEPtAdc0->Fill(ppt,nSigE);
				if(nHitsFit>=nFPtsCutSys) hNSigEPtnHitsFit->Fill(ppt,nSigE);
				if(nHitsDedx>=ndEdxPtsCutSys) hNSigEPtnHitsDedx->Fill(ppt,nSigE);
				if(dca<dcaCutSys) hNSigEPtDca->Fill(ppt,nSigE);
				if(EMCpovere>PoeMinSys) hNSigEPtEMCpovere->Fill(ppt,nSigE);
				if(isSMDTrack(t,i)){
					hNSigESMD->Fill(pp, nSigE);
					hNSigEPtSMD->Fill(ppt, nSigE);
					if(adc0>mHTAdc0thSys) hNSigEPtAdc0SMD->Fill(ppt,nSigE);
					if(nHitsFit>=nFPtsCutSys) hNSigEPtnHitsFitSMD->Fill(ppt,nSigE);
					if(nHitsDedx>=ndEdxPtsCutSys) hNSigEPtnHitsDedxSMD->Fill(ppt,nSigE);
					if(dca<dcaCutSys) hNSigEPtDcaSMD->Fill(ppt,nSigE);
					if(EMCpovere>PoeMinSys) hNSigEPtEMCpovereSMD->Fill(ppt,nSigE);
				}
				if(nSigE>-1.&&nSigE<3.){
					hAdc0Cut->Fill(ppt, adc0);
					hdsmAdcCut->Fill(ppt, dsmadc);
					hAdc0vsdsmAdcCut->Fill(adc0, dsmadc);
					if(isSMDTrack(t,i)){
						hAdc0CutSMD->Fill(ppt, adc0);
						hdsmAdcCutSMD->Fill(ppt, dsmadc);
						hAdc0vsdsmAdcCutSMD->Fill(adc0, dsmadc);
					}
				}
			}

			CurrentEvent_EMCEId[CurrentEvent_nEMCE]       = i;
			CurrentEvent_EMCECharge[CurrentEvent_nEMCE]   = (t->Tracks_mNHitsFit[i]<0) ? -1 : 1;
			CurrentEvent_EMCEPt[CurrentEvent_nEMCE]       = ppt;
			CurrentEvent_EMCEHelixPx[CurrentEvent_nEMCE]  = t->Tracks_mGMomentum_mX1[i];
			CurrentEvent_EMCEHelixPy[CurrentEvent_nEMCE]  = t->Tracks_mGMomentum_mX2[i];
			CurrentEvent_EMCEHelixPz[CurrentEvent_nEMCE]  = t->Tracks_mGMomentum_mX3[i];
			CurrentEvent_EMCEHelixX[CurrentEvent_nEMCE]   = 0.01*t->Tracks_mOriginX[i];
			CurrentEvent_EMCEHelixY[CurrentEvent_nEMCE]   = 0.01*t->Tracks_mOriginY[i];
			CurrentEvent_EMCEHelixZ[CurrentEvent_nEMCE]   = 0.01*t->Tracks_mOriginZ[i];
			CurrentEvent_EMCENhitsFit[CurrentEvent_nEMCE] = nHitsFit;
			CurrentEvent_EMCENhitsDedx[CurrentEvent_nEMCE]= nHitsDedx;
			CurrentEvent_EMCEDca[CurrentEvent_nEMCE]      = dca;
			CurrentEvent_EMCETOWpovere[CurrentEvent_nEMCE]= EMCpovere;
			CurrentEvent_EMCEDistZ[CurrentEvent_nEMCE]    = ZDist;
			CurrentEvent_EMCEDistPhi[CurrentEvent_nEMCE]  = PhiDist;
			CurrentEvent_EMCESMDNEta[CurrentEvent_nEMCE]  = nEta;
			CurrentEvent_EMCESMDNPhi[CurrentEvent_nEMCE]  = nPhi;
			CurrentEvent_EMCEDsmADC[CurrentEvent_nEMCE]   = dsmadc;
			CurrentEvent_EMCEADC0[CurrentEvent_nEMCE]     = adc0;
			CurrentEvent_EMCENSigE[CurrentEvent_nEMCE]    = nSigE;
			CurrentEvent_nEMCE ++;
			//cout<<CurrentEvent_nEMCE<<endl;
		}

		hnE->Fill(CurrentEvent_nEMCE,CurrentEvent_nEs);
		if(CurrentEvent_nEMCE < 1 || CurrentEvent_nEs < 1) continue; //at least find 1 pair candidate
		hnEvent->Fill(6);

		makerealevent();
	} // end event looping
	cout << "Writing histograms ... " << endl;
	writeHistograms();
	cout<<"end of program"<<endl;
	return(0);
	exit(0);
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
bool isGoodPartner(PicoDst *tr,int id)
{
	TVector3 trmom(tr->Tracks_mGMomentum_mX1[id],tr->Tracks_mGMomentum_mX2[id],tr->Tracks_mGMomentum_mX3[id]);
	float pt = trmom.Perp();
	if(pt <= 0.3) return false;
	float nhits = 1.*tr->Tracks_mNHitsFit[id];
	float nhitmax = 1.*tr->Tracks_mNHitsMax[id];
	float ratio = fabs(nhits)/nhitmax;
	if(ratio<PtsRMin || ratio>PtsRMax) return false;

	return true;
}
//--------------------------------------------------------------------
bool isGoodTrack(PicoDst *tr,int id)
{
	TVector3 trmom(tr->Tracks_mPMomentum_mX1[id],tr->Tracks_mPMomentum_mX2[id],tr->Tracks_mPMomentum_mX3[id]);
	float pt = trmom.Perp();
	if(pt<minPtCut) return false;

	float eta = trmom.PseudoRapidity();
	if(fabs(eta)>EtaCut) return false;

	float nhits = 1.*tr->Tracks_mNHitsFit[id];
	int nhitmax = 1.*tr->Tracks_mNHitsMax[id];
	float ratio = fabs(nhits)/nhitmax;
	if(ratio<PtsRMin || ratio>PtsRMax) return false;

	float Rx = 0.01*tr->Tracks_mOriginX[id];
	float Ry = 0.01*tr->Tracks_mOriginY[id];
	float FirstTpcR = sqrt(Rx*Rx+Ry*Ry);
	if(FirstTpcR>=TPCFR) return false;

	return true;
}
//--------------------------------------------------------------------
bool isEMCTrack(PicoDst *tr,int id)
{
	TVector3 trmom(tr->Tracks_mGMomentum_mX1[id],tr->Tracks_mGMomentum_mX2[id],tr->Tracks_mGMomentum_mX3[id]);
	float gp    = trmom.Mag();            
	float EMCE     = 0.001*tr->Tracks_mBTOWE[id];
	float EMCpovere = (EMCE>0) ? gp/EMCE : -999.;
	if(EMCE<0) return false;
	if(EMCpovere<PoeMin || EMCpovere>PoeMax) return false;

	return true;
}
//--------------------------------------------------------------------
bool isSMDTrack(PicoDst *tr,int id)
{
	float EMCDistZ     = 0.01*tr->Tracks_mBEMCDistZ[id];
	float EMCDistPhi = 0.0001*tr->Tracks_mBEMCDistPhi[id];
	int SMDNEta     = tr->Tracks_mBSMDNEta[id];
	int SMDNPhi  = tr->Tracks_mBSMDNPhi[id];
	if(fabs(EMCDistZ)>DistZ) return false;
	if(fabs(EMCDistPhi)>DistPhi) return false;
	if(SMDNEta<NEta) return false;
	if(SMDNPhi<NPhi) return false;

	return true;
}
//-----------------------------------------------------------------------
bool checkHotTower(int towId)
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
void makerealevent()
{
	TLorentzVector FourMom1(0,0,0,0);
	TLorentzVector FourMom2(0,0,0,0);
	TLorentzVector FourMomR(0,0,0,0);

	for(int i=0; i<CurrentEvent_nEMCE; i++) {
		TVector3 Helix1P(CurrentEvent_EMCEHelixPx[i],CurrentEvent_EMCEHelixPy[i],CurrentEvent_EMCEHelixPz[i]);
		TVector3 Helix1O(CurrentEvent_EMCEHelixX[i],CurrentEvent_EMCEHelixY[i],CurrentEvent_EMCEHelixZ[i]);
		int   charge1  = CurrentEvent_EMCECharge[i];
		StPhysicalHelixD Helix1(Helix1P,Helix1O,CurrentEvent_bField,charge1);

		for(int j=0; j<CurrentEvent_nEs; j++) {
			if(CurrentEvent_EMCEId[i] == CurrentEvent_EId[j]) continue;

			TVector3 Helix2P(CurrentEvent_EHelixPx[j],CurrentEvent_EHelixPy[j],CurrentEvent_EHelixPz[j]);
			TVector3 Helix2O(CurrentEvent_EHelixX[j],CurrentEvent_EHelixY[j],CurrentEvent_EHelixZ[j]);
			int   charge2  = CurrentEvent_ECharge[j];
			float PtPart       = CurrentEvent_EPt[j];
			float EtaPart      = CurrentEvent_EEta[j];
			int   ENhitsFit    = CurrentEvent_ENhitsFit[j];
			int   ENhitsDedx   = CurrentEvent_ENhitsDedx[j];
			float EDca         = CurrentEvent_EDca[j];
			float ETOWE        = CurrentEvent_ETOWE[j];
			float ETOWpovere   = CurrentEvent_ETOWpovere[j];
			float EDistZ       = CurrentEvent_EDistZ[j]; 
			float EDistPhi     = CurrentEvent_EDistPhi[j];
			int   ESMDNEta     = CurrentEvent_ESMDNEta[j];
			int   ESMDNPhi     = CurrentEvent_ESMDNPhi[j];
			StPhysicalHelixD Helix2(Helix2P,Helix2O,CurrentEvent_bField,charge2);

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
			int   EMCENhitsFit    = CurrentEvent_EMCENhitsFit[i];
			int   EMCENhitsDedx   = CurrentEvent_EMCENhitsDedx[i];
			float EMCEDca         = CurrentEvent_EMCEDca[i];
			float EMCETOWpovere   = CurrentEvent_EMCETOWpovere[i];
			float EMCEDistZ       = CurrentEvent_EMCEDistZ[i]; 
			float EMCEDistPhi     = CurrentEvent_EMCEDistPhi[i];
			int   EMCESMDNEta     = CurrentEvent_EMCESMDNEta[i];
			int   EMCESMDNPhi     = CurrentEvent_EMCESMDNPhi[i];
			int   EMCEDsmADC      = CurrentEvent_EMCEDsmADC[i];
			int   EMCEADC0        = CurrentEvent_EMCEADC0[i];
			float EMCENSigE       = CurrentEvent_EMCENSigE[i];
			int  isTriggered = 0;
			int  isTrackQ = 0;
			int  isTrackQPart = 0;
			int  isEMC = 0;
			int  isSMD = 0;
			if(EMCEDsmADC>mHTth && EMCEADC0>mHTAdc0th) isTriggered = 1;
			if(EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut) isTrackQ = 1;
			if(fabs(EtaPart)<0.7&&ENhitsFit>=nFPtsCut&&ENhitsDedx>=ndEdxPtsCut&&EDca<dcaCut) isTrackQPart = 1;
			if(EMCETOWpovere>PoeMin && EMCETOWpovere<PoeMax) isEMC = 1;
			if(fabs(EMCEDistZ)<DistZ && fabs(EMCEDistPhi)<DistPhi && EMCESMDNEta>=NEta && EMCESMDNPhi>=NPhi) isSMD = 1;
			if(charge1*charge2 == -1) {
				/////////////////////////////////////////////////////
				//PHE
				/////////////////////////////////////////////////////
				if(isTriggered&&isTrackQ&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.) {
					hmvspt->Fill(PtTag,M);
					if(EMCEADC0>mHTAdc0thSys) hmvsptAdc0->Fill(PtTag,M);
					if(EMCENhitsFit>=nFPtsCutSys) hmvsptnHitsFit->Fill(PtTag,M);
					if(EMCENhitsDedx>=ndEdxPtsCutSys) hmvsptnHitsDedx->Fill(PtTag,M);
					if(EMCEDca<dcaCutSys) hmvsptDca->Fill(PtTag,M);
					if(EMCETOWpovere>PoeMinSys) hmvsptEMCpovere->Fill(PtTag,M);
					if(isSMD){ 
						hmvsptSMD->Fill(PtTag,M);
						if(EMCEADC0>mHTAdc0thSys) hmvsptAdc0SMD->Fill(PtTag,M);
						if(EMCENhitsFit>=nFPtsCutSys) hmvsptnHitsFitSMD->Fill(PtTag,M);
						if(EMCENhitsDedx>=ndEdxPtsCutSys) hmvsptnHitsDedxSMD->Fill(PtTag,M);
						if(EMCEDca<dcaCutSys) hmvsptDcaSMD->Fill(PtTag,M);
						if(EMCETOWpovere>PoeMinSys) hmvsptEMCpovereSMD->Fill(PtTag,M);
					}
				}
				if(M>0.1) continue;
				/////////////////////////////////////////////////////
				//Distribution
				/////////////////////////////////////////////////////
				if(isEMC&&EMCENSigE>-1.&&EMCENSigE<3.){
					if(isTrackQ) hAdc0PHE->Fill(PtTag,EMCEADC0);
					if(isTriggered&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut)
						hnHitsFit->Fill(PtTag,EMCENhitsFit);
					if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCEDca<dcaCut)
						hnHitsDedx->Fill(PtTag,EMCENhitsDedx);
					if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut)
						hDca->Fill(PtTag,EMCEDca);
					if(isSMD){
						if(isTrackQ) hAdc0PHESMD->Fill(PtTag,EMCEADC0);
						if(isTriggered&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut)
							hnHitsFitSMD->Fill(PtTag,EMCENhitsFit);
						if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCEDca<dcaCut)
							hnHitsDedxSMD->Fill(PtTag,EMCENhitsDedx);
						if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut)
							hDcaSMD->Fill(PtTag,EMCEDca);
					}
				}
				/////////////////////////////////////////////////////
				//nsigmae eff
				/////////////////////////////////////////////////////
				if(isTriggered&&isTrackQ&&isEMC){
					hNSigEeff->Fill(PtTag,EMCENSigE);
					if(isSMD) hNSigEeffSMD->Fill(PtTag,EMCENSigE);
					////////////////////////////////////////////////////
					//SMD eff
					///////////////////////////////////////////////////
					if(EMCENSigE>-1.&&EMCENSigE<3.){ 
						hTPCtracksTag->Fill(PtTag);
						if(isSMD) hSMDtracksTag->Fill(PtTag);
					}
				}
				/////////////////////////////////////////////////////
				//EMC eff
				/////////////////////////////////////////////////////
				if(isTriggered&&isTrackQ&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.&&isTrackQPart){
					hTPCtracks->Fill(PtPart);
					if(ETOWE>0.){//&&(fabs(dEta)>0.1||fabs(dPhi)>0.105))
						hEMCmatchingtracks->Fill(PtPart);
						if(ETOWpovere>PoeMin&&ETOWpovere<PoeMax){
							hEMCtracks->Fill(PtPart);
							if(ESMDNEta>0.&&ESMDNPhi>0.){
								hSMDmatchingtracks->Fill(PtPart);
								if(ESMDNEta>=NEta&&ESMDNPhi>=NPhi&&fabs(EDistPhi)<DistPhi&&fabs(EDistZ)<DistZ)
									hSMDtracks->Fill(PtPart);
							}
						}
					}
					if(isSMD){
						hTPCtracksSMD->Fill(PtPart);
						if(ETOWE>0.){//&&(fabs(dEta)>0.1||fabs(dPhi)>0.PoeMax))
							hEMCmatchingtracksSMD->Fill(PtPart);
							if(ETOWpovere>PoeMin&&ETOWpovere<PoeMax){
								hEMCtracksSMD->Fill(PtPart);
								if(ESMDNEta>0.&&ESMDNPhi>0.){
									hSMDmatchingtracksSMD->Fill(PtPart);
									if(ESMDNEta>=NEta&&ESMDNPhi>=NPhi&&fabs(EDistPhi)<DistPhi&&fabs(EDistZ)<DistZ)
										hSMDtracksSMD->Fill(PtPart);
								}
							}
						}
					}
				}
			}
			else{
				/////////////////////////////////////////////////////
				//PHE
				/////////////////////////////////////////////////////
				if(isTriggered&&isTrackQ&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.) {
					hmvsptlike->Fill(PtTag,M);
					if(EMCEADC0>mHTAdc0thSys) hmvsptAdc0like->Fill(PtTag,M);
					if(EMCENhitsFit>=nFPtsCutSys) hmvsptnHitsFitlike->Fill(PtTag,M);
					if(EMCENhitsDedx>=ndEdxPtsCutSys) hmvsptnHitsDedxlike->Fill(PtTag,M);
					if(EMCEDca<dcaCutSys) hmvsptDcalike->Fill(PtTag,M);
					if(EMCETOWpovere>PoeMinSys) hmvsptEMCpoverelike->Fill(PtTag,M);
					if(isSMD){ 
						hmvsptSMDlike->Fill(PtTag,M);
						if(EMCEADC0>mHTAdc0thSys) hmvsptAdc0SMDlike->Fill(PtTag,M);
						if(EMCENhitsFit>=nFPtsCutSys) hmvsptnHitsFitSMDlike->Fill(PtTag,M);
						if(EMCENhitsDedx>=ndEdxPtsCutSys) hmvsptnHitsDedxSMDlike->Fill(PtTag,M);
						if(EMCEDca<dcaCutSys) hmvsptDcaSMDlike->Fill(PtTag,M);
						if(EMCETOWpovere>PoeMinSys) hmvsptEMCpovereSMDlike->Fill(PtTag,M);
					}
				}
				if(M>0.1) continue;
				/////////////////////////////////////////////////////
				//Distribution
				/////////////////////////////////////////////////////
				if(isEMC&&EMCENSigE>-1.&&EMCENSigE<3.){
					if(isTrackQ) hAdc0PHElike->Fill(PtTag,EMCEADC0);
					if(isTriggered&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut)
						hnHitsFitlike->Fill(PtTag,EMCENhitsFit);
					if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCEDca<dcaCut)
						hnHitsDedxlike->Fill(PtTag,EMCENhitsDedx);
					if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut)
						hDcalike->Fill(PtTag,EMCEDca);
					if(isSMD){
						if(isTrackQ) hAdc0PHESMDlike->Fill(PtTag,EMCEADC0);
						if(isTriggered&&EMCENhitsDedx>=ndEdxPtsCut&&EMCEDca<dcaCut)
							hnHitsFitSMDlike->Fill(PtTag,EMCENhitsFit);
						if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCEDca<dcaCut)
							hnHitsDedxSMDlike->Fill(PtTag,EMCENhitsDedx);
						if(isTriggered&&EMCENhitsFit>=nFPtsCut&&EMCENhitsDedx>=ndEdxPtsCut)
							hDcaSMDlike->Fill(PtTag,EMCEDca);
					}
				}
				/////////////////////////////////////////////////////
				//nsigmae eff
				/////////////////////////////////////////////////////
				if(isTriggered&&isTrackQ&&isEMC){
					hNSigEefflike->Fill(PtTag,EMCENSigE);
					if(isSMD) hNSigEeffSMDlike->Fill(PtTag,EMCENSigE);
					////////////////////////////////////////////////////
					//SMD eff
					///////////////////////////////////////////////////
					if(EMCENSigE>-1.&&EMCENSigE<3.){ 
						hTPCtracksTaglike->Fill(PtTag);
						if(isSMD) hSMDtracksTaglike->Fill(PtTag);
					}
				}
				/////////////////////////////////////////////////////
				//EMC eff
				/////////////////////////////////////////////////////
				if(isTriggered&&isTrackQ&&isEMC&&EMCENSigE>-1.&&EMCENSigE<3.&&isTrackQPart){
					hTPCtrackslike->Fill(PtPart);
					if(ETOWE>0.){//&&(fabs(dEta)>0.1||fabs(dPhi)>0.PoeMax))
						hEMCmatchingtrackslike->Fill(PtPart);
						if(ETOWpovere>PoeMin&&ETOWpovere<PoeMax){
							hEMCtrackslike->Fill(PtPart);
							if(ESMDNEta>0.&&ESMDNPhi>0.){
								hSMDmatchingtrackslike->Fill(PtPart);
								if(ESMDNEta>=NEta&&ESMDNPhi>=NPhi&&fabs(EDistPhi)<DistPhi&&fabs(EDistZ)<DistZ)
									hSMDtrackslike->Fill(PtPart);
							}
						}
					}
					if(isSMD){
						hTPCtracksSMDlike->Fill(PtPart);
						if(ETOWE>0.){//&&(fabs(dEta)>0.1||fabs(dPhi)>0.PoeMax))
							hEMCmatchingtracksSMDlike->Fill(PtPart);
							if(ETOWpovere>PoeMin&&ETOWpovere<PoeMax){
								hEMCtracksSMDlike->Fill(PtPart);
								if(ESMDNEta>0.&&ESMDNPhi>0.){
									hSMDmatchingtracksSMDlike->Fill(PtPart);
									if(ESMDNEta>=NEta&&ESMDNPhi>=NPhi&&fabs(EDistPhi)<DistPhi&&fabs(EDistZ)<DistZ)
										hSMDtracksSMDlike->Fill(PtPart);
								}
							}
						}
					}
				}
			}
		}//e2
	}//e1
}

//-----------------------------------------------------------------------
void writeHistograms()
{
	fout->cd();

	hnEvent->Write();
	hVpdVz->Write();
	hVpdVzcut->Write();
	hVzDiff->Write();
	hAdc0->Write();
	hdsmAdc->Write();
	hAdc0vsdsmAdc->Write();
	hNSigE->Write();
	hNSigEPt->Write();
	hNSigEPtAdc0->Write();
	hNSigEPtnHitsFit->Write();
	hNSigEPtnHitsDedx->Write();
	hNSigEPtDca->Write();
	hNSigEPtEMCpovere->Write();
	hNSigESMD->Write();
	hNSigEPtSMD->Write();
	hNSigEPtAdc0SMD->Write();
	hNSigEPtnHitsFitSMD->Write();
	hNSigEPtnHitsDedxSMD->Write();
	hNSigEPtDcaSMD->Write();
	hNSigEPtEMCpovereSMD->Write();
	hAdc0Cut->Write();
	hdsmAdcCut->Write();
	hAdc0vsdsmAdcCut->Write();
	hAdc0CutSMD->Write();
	hdsmAdcCutSMD->Write();
	hAdc0vsdsmAdcCutSMD->Write();
	hnE->Write();
	hmvspt->Write();
	hmvsptlike->Write();
	hmvsptAdc0->Write();
	hmvsptAdc0like->Write();
	hmvsptnHitsFit->Write();
	hmvsptnHitsFitlike->Write();
	hmvsptnHitsDedx->Write();
	hmvsptnHitsDedxlike->Write();
	hmvsptDca->Write();
	hmvsptDcalike->Write();
	hmvsptEMCpovere->Write();
	hmvsptEMCpoverelike->Write();
	hmvsptSMD->Write();
	hmvsptSMDlike->Write();
	hmvsptAdc0SMD->Write();
	hmvsptAdc0SMDlike->Write();
	hmvsptnHitsFitSMD->Write();
	hmvsptnHitsFitSMDlike->Write();
	hmvsptnHitsDedxSMD->Write();
	hmvsptnHitsDedxSMDlike->Write();
	hmvsptDcaSMD->Write();
	hmvsptDcaSMDlike->Write();
	fout->Close();
}

