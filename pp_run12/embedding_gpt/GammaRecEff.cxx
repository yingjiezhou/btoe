/******************************************************************************************
 *Tue Oct 9 15:24:09 PDT 2018                                                            *
 * This class for the Gamma rec. efficiency                                                 *
 * By Shenghui Zhang                                                         *
 ***********************************
 */
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
#include "string.h"

#include "TROOT.h"
#include "TFile.h"

#include "TChain.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TPaletteAxis.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TRandom.h"
#include "TMath.h"
#include "TVector2.h"
#include "TVector3.h"
//#include "StThreeVectorF.hh"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TUnixSystem.h"
#include "TRandom3.h"
#include "TGraphErrors.h"
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "StPhysicalHelixD.h"
#include "SystemOfUnits.h"
#include "PhysicalConstants.h"

#include "mcTGamma.h"
#include "histogram.h"
#include "mBadRunList.h"
using namespace std;
#define nFPtsCut     15    // >15
#define nFPtsCutTag  20    // >15
#define ndEdxCut     15
#define PtsRMin      0.52  // >0.55
#define PtsRMax      1.20
#define minPtCut     0.2   // >0.2
//#define maxPtCut     20.
#define dcaCut       1.5   // <2 no dca cut
//#define dcaXYCut     1.0
#define EtaCut       0.7    // |<1.

int main(int argc, char **argv)
{
	TF1 *myGaus = new TF1("myGaus","gaus",-10,10);
	myGaus->SetParameters(1,-0.4134,0.9331);
	if(argc != 3) exit(1);
	FileOutPut = "out/Eff_";
	FileOutPut += argv[1];
	FileOutPut += ".root";
	FileInPut = "out/";
	FileInPut += argv[1];
	FileInPut += ".root";
	cout << "Reading "  << FileInPut  << endl;
	cout << "Creating " << FileOutPut << endl;

	TH1F:: SetDefaultSumw2();
	TH2F:: SetDefaultSumw2();

	weightFile=new TFile("GetGammaSpectrum/macros/rootfile/GammaSpectrumpp.root","READ");
	hGammaCS=(TH1F *) weightFile->Get("InclusiveGamma");
	hGammadNdpTdy=(TH1F *)hGammaCS->Clone("hGammadNdpTdy");
	cout<<"cn"<<hGammadNdpTdy->GetBinContent(hGammadNdpTdy->FindBin(7.95342))<<endl;
	for(int i=0;i<hGammaCS->GetNbinsX();i++){
		hGammadNdpTdy->SetBinContent(i+1,hGammaCS->GetBinContent(i+1)*2*TMath::Pi()*hGammaCS->GetBinCenter(i+1)/30.);
		hGammadNdpTdy->SetBinError(i+1,hGammaCS->GetBinError(i+1)*2*TMath::Pi()*hGammaCS->GetBinCenter(i+1)/30.);
	}
	MassE = 0.000511;
	hnTotal            = new TH1F("hnTotal","",40,-2.,2.);
	hnTotalyCut        = new TH1F("hnTotalyCut","",40,-2.,2.);
	hRcpt              = new TH1F("Rcpt","",nPtBins,ptbin);
	hRcptPosEle        = new TH1F("RcptPosEle","",nPtBins,ptbin);
	hRcptHT0           = new TH1F("RcptHT0","",nPtBins,ptbin);
	hRcptPosEleHT0     = new TH1F("RcptPosEleHT0","",nPtBins,ptbin);
	hRcptHT2           = new TH1F("RcptHT2","",nPtBins,ptbin);
	hRcptPosEleHT2     = new TH1F("RcptPosEleHT2","",nPtBins,ptbin);
	hRcptSMD           = new TH1F("RcptSMD","",nPtBins,ptbin);
	hRcptPosEleSMD     = new TH1F("RcptPosEleSMD","",nPtBins,ptbin);
	hRcptHT0SMD        = new TH1F("RcptHT0SMD","",nPtBins,ptbin);
	hRcptPosEleHT0SMD  = new TH1F("RcptPosEleHT0SMD","",nPtBins,ptbin);
	hRcptHT2SMD        = new TH1F("RcptHT2SMD","",nPtBins,ptbin);
	hRcptPosEleHT2SMD  = new TH1F("RcptPosEleHT2SMD","",nPtBins,ptbin);
	hmvspt             = new TH2F("mvspt","",1000,0.,20.,500,0.,0.5);
	hmvsptWt           = new TH2F("mvsptWt","",1000,0.,20.,500,0.,0.5);
	hmvsptHT0          = new TH2F("mvsptHT0","",1000,0.,20.,500,0.,0.5);
	hmvsptWtHT0        = new TH2F("mvsptWtHT0","",1000,0.,20.,500,0.,0.5);
	hmvsptHT2          = new TH2F("mvsptHT2","",1000,0.,20.,500,0.,0.5);
	hmvsptWtHT2        = new TH2F("mvsptWtHT2","",1000,0.,20.,500,0.,0.5);
	hmvsptSMD          = new TH2F("mvsptSMD","",1000,0.,20.,500,0.,0.5);
	hmvsptWtSMD        = new TH2F("mvsptWtSMD","",1000,0.,20.,500,0.,0.5);
	hmvsptHT0SMD       = new TH2F("mvsptHT0SMD","",1000,0.,20.,500,0.,0.5);
	hmvsptWtHT0SMD     = new TH2F("mvsptWtHT0SMD","",1000,0.,20.,500,0.,0.5);
	hmvsptHT2SMD       = new TH2F("mvsptHT2SMD","",1000,0.,20.,500,0.,0.5);
	hmvsptWtHT2SMD     = new TH2F("mvsptWtHT2SMD","",1000,0.,20.,500,0.,0.5);
	hGpTPart           = new TH2F("hGpTPart","",1000,0.,20.,1000,0.,20.);
	hGpTPartWt         = new TH2F("hGpTPartWt","",1000,0.,20.,1000,0.,20.);
	hRcptMeeGptP       = new TH1F("RcptMeeGptP","",nPtBins,ptbin);
	hRcptMee           = new TH1F("RcptMee","",nPtBins,ptbin);
	hRcptMeePOE        = new TH1F("RcptMeePOE","",nPtBins,ptbin);
	hRcptMeeHT0        = new TH1F("RcptMeeHT0","",nPtBins,ptbin);
	hRcptMeeHT2        = new TH1F("RcptMeeHT2","",nPtBins,ptbin);
	hRcptMeeSys        = new TH1F("RcptMeeSys","",nPtBins,ptbin);
	hRcptMeeSysHT0     = new TH1F("RcptMeeSysHT0","",nPtBins,ptbin);
	hRcptMeeSysHT2     = new TH1F("RcptMeeSysHT2","",nPtBins,ptbin);
	hRcptMeeSMD        = new TH1F("RcptMeeSMD","",nPtBins,ptbin);
	hRcptMeePOESMD     = new TH1F("RcptMeePOESMD","",nPtBins,ptbin);
	hRcptMeeHT0SMD     = new TH1F("RcptMeeHT0SMD","",nPtBins,ptbin);
	hRcptMeeHT2SMD     = new TH1F("RcptMeeHT2SMD","",nPtBins,ptbin);
	hRcptMeeSysSMD     = new TH1F("RcptMeeSysSMD","",nPtBins,ptbin);
	hRcptMeeSysHT0SMD  = new TH1F("RcptMeeSysHT0SMD","",nPtBins,ptbin);
	hRcptMeeSysHT2SMD  = new TH1F("RcptMeeSysHT2SMD","",nPtBins,ptbin);

	//--------------------
	// loop the chain
	//--------------------
	TChain *chain = new TChain("mcTGamma");
	chain->Add(FileInPut.Data());

	int nevents = (int)chain->GetEntries();
	cout << "== total entries : " << nevents << endl;

	mcTGamma *t = new mcTGamma(chain);
	mNBadRuns = sizeof(mBadRuns_HT)/sizeof(int);

	gRandom->SetSeed(atoi(argv[2]));

	for(int i=0;i<nevents;i++){
		if(i%10000==0) cout << "begin " << i << "th entry...." << endl;
		t->GetEntry(i);
		if(t->vx==-999.&&t->vy==-999.&&t->vz==-999.) continue;
		float Vr = sqrt(pow(t->vx,2.)+pow(t->vy,2.));
		if(Vr>=2) continue;
		int realRunId=1;
		for(int k=0;k<mNBadRuns;k++){
			if(t->runId==mBadRuns_HT[k]) {
				cout<<"mBadRuns"<<mBadRuns_HT[k]<<endl;
				realRunId=0; break;
			}
		}
		if(realRunId==0) continue;
		if(fabs(t->vz)>35.) continue;
		//if(!(t->triggerId==-995||t->triggerId==-993)) continue;
		//if(!(t->triggerId==-997||t->triggerId==-993)) continue;

		float bField = t->MagField*kilogauss;
		TLorentzVector positronRc(0.,0.,0.,0.);
		TLorentzVector electronRc(0.,0.,0.,0.);
		TLorentzVector positronRc1(0.,0.,0.,0.);
		TLorentzVector electronRc1(0.,0.,0.,0.);
		TLorentzVector FourMom1(0,0,0,0);
		TLorentzVector FourMom2(0,0,0,0);

		for(int k=0;k<t->nTracksGamma;k++) {

			if(t->mcEtaInput[k]>2000.) continue;
			hnTotal->Fill(t->mcEtaInput[k]);
			if(fabs(t->mcEtaInput[k])<1.0) hnTotalyCut->Fill(t->mcEtaInput[k]);
		}
		for(int j=0;j<t->nTracks;j++) {
			float pt  = t->mcPt[j];
			float eta = t->mcEta[j];
			float phi = t->mcPhi[j];
			if(eta>2000.) continue;
			if(pt<=0||pt>20)continue;
			if(fabs(eta)>1)continue;

			/*
			   float mcptE  = t->E_mcPt[j];
			   float mcetaE = t->E_mcEta[j];
			   float mcphiE = t->E_mcPhi[j];
			   TLorentzVector McE(0.,0.,0.,0.);
			   McE.SetPtEtaPhiM(mcptE,mcetaE,mcphiE,MassE);
			   bool tag = kFALSE;
			   for(int g=0;g<t->nTracks;g++){
			   if(g==j) continue;
			   float mcptk  = t->P_mcPt[g];
			   float mcetak = t->P_mcEta[g];
			   float mcphik = t->P_mcPhi[g];
			   TLorentzVector Mck(0.,0.,0.,0.);
			   Mck.SetPtEtaPhiM(mcptk,mcetak,mcphik,MassE);

			   Double_t deta = McE.Rapidity() - Mck.Rapidity();
			   Double_t dphi = mcphiE - mcphik;
			   while(dphi>2*TMath::Pi()) dphi -= 2.*TMath::Pi();
			   while(dphi<0) dphi += 2.*TMath::Pi();
			   while(dphi>TMath::Pi()) dphi = dphi -2*TMath::Pi();
			   if(TMath::Abs(deta)<0.1 && TMath::Abs(dphi)<0.5) tag = kTRUE;
			   }
			   if(tag) continue;*/
			float P_rcPt = t->P_rcPt[j];
			if(P_rcPt!=-999) P_rcPt = SmearPt(t->P_mcPt[j]);
			float E_rcPt = t->E_rcPt[j];
			if(E_rcPt!=-999) E_rcPt = SmearPt(t->E_mcPt[j]);
			positronRc.SetPtEtaPhiM(t->P_rcgPt[j], t->P_rcgEta[j], t->P_rcgPhi[j], MassE);
			electronRc.SetPtEtaPhiM(t->E_rcgPt[j], t->E_rcgEta[j], t->E_rcgPhi[j], MassE);
			positronRc1.SetPtEtaPhiM(P_rcPt, t->P_rcEta[j], t->P_rcPhi[j], MassE);
			electronRc1.SetPtEtaPhiM(E_rcPt, t->E_rcEta[j], t->E_rcPhi[j], MassE);
			float p_P = positronRc1.P();
			float pe_P = (t->P_rcEnergy0[j]>0)? p_P/t->P_rcEnergy0[j]:9999;
			float FirstTpcR_P = sqrt(t->P_HelixX[j]*t->P_HelixX[j]+t->P_HelixY[j]*t->P_HelixY[j]);
			float p_E = electronRc1.P();
			float pe_E = (t->E_rcEnergy0[j]>0)? p_E/t->E_rcEnergy0[j]:9999;
			float FirstTpcR_E = sqrt(t->E_HelixX[j]*t->E_HelixX[j]+t->E_HelixY[j]*t->E_HelixY[j]);

			bool positronCutOK = 0;
			if(t->P_rcNHitsFit[j]>=nFPtsCut&&t->P_rcNHitsPoss[j]>0&&(1.*t->P_rcNHitsFit[j])/(1.*t->P_rcNHitsPoss[j])>PtsRMin)
				positronCutOK = 1;
			bool electronCutOK = 0;
			if(t->E_rcNHitsFit[j]>=nFPtsCut&&t->E_rcNHitsPoss[j]>0&&(1.*t->E_rcNHitsFit[j])/(1.*t->E_rcNHitsPoss[j])>PtsRMin)
				electronCutOK = 1;

			//Double_t nsigma = myGaus->GetRandom();
			bool positronPriCutOK =
				P_rcPt       > minPtCut             &&
				fabs(t->P_rcEta[j]) < EtaCut        &&
				t->P_rcNHitsFit[j]  >= nFPtsCutTag  &&
				t->P_rcNdEdx[j]     >= ndEdxCut     &&
				//nsigma>-1.0     &&    nsigma<3.0    &&
				FirstTpcR_P<73                      &&
				t->P_dca[j]         > 0             &&
				t->P_dca[j]         < dcaCut        &&
				t->P_rcNHitsPoss[j] > 0             &&
				(1.*t->P_rcNHitsFit[j])/(1.*t->P_rcNHitsPoss[j])>PtsRMin && 
				//(1.*t->P_rcNHitsFit[j])/(1.*t->P_rcNHitsPoss[j])<PtsRMax &&
				t->P_rcEnergy0[j]    >0  && pe_P>0.3 && pe_P<1.5     &&
				t->P_rcNCommonHits[j]>=10                           &&
				!(isHotTower(t->P_rctowerId[j]));
			bool positronSMDPriCutOK =
				t->P_rcnEta[j]>1         &&  t->P_rcnPhi[j]>1       &&
				fabs(t->P_rczDist[j])<3.0 && fabs(t->P_rcphiDist[j])<0.015;
			bool  positronTriHT0PriCutOK =
				t->P_rcadc0[j]>180&&t->P_rcdsmadc[j]>11;
			bool  positronTriHT2PriCutOK =
				t->P_rcadc0[j]>300&&t->P_rcdsmadc[j]>18;

			bool electronPriCutOK =
				E_rcPt       > minPtCut            &&
				fabs(t->E_rcEta[j]) < EtaCut       &&
				t->E_rcNHitsFit[j]  >= nFPtsCutTag &&
				t->E_rcNdEdx[j]     >= ndEdxCut    &&
				//nsigma>-1.0     &&    nsigma<3.0   &&
				FirstTpcR_E<73                     &&
				t->E_dca[j]         > 0            &&
				t->E_dca[j]         < dcaCut       &&
				t->E_rcNHitsPoss[j] > 0            &&
				(1.*t->E_rcNHitsFit[j])/(1.*t->E_rcNHitsPoss[j])>PtsRMin &&
				//(1.*t->E_rcNHitsFit[j])/(1.*t->E_rcNHitsPoss[j])<PtsRMax &&
				t->E_rcEnergy0[j]>0 && pe_E>0.3 && pe_E<1.5          &&
				t->E_rcNCommonHits[j]>=10                           &&
				!(isHotTower(t->E_rctowerId[j]));
			bool electronSMDPriCutOK=
				t->E_rcnEta[j]>1 && t->E_rcnPhi[j]>1                &&
				fabs(t->E_rczDist[j])<3.0 && fabs(t->E_rcphiDist[j])<0.015;
			bool  electronTriHT0PriCutOK =
				t->E_rcadc0[j]>180&&t->E_rcdsmadc[j]>11;
			bool  electronTriHT2PriCutOK =
				t->E_rcadc0[j]>300&&t->E_rcdsmadc[j]>18;

			bool positronParCutOK =
				t->P_rcgPt[j]       > 0.2       &&
				fabs(t->P_rcgEta[j]) < 1.0      &&
				positronCutOK                   &&
				t->P_rcNCommonHits[j]>=10;//       &&
			//!(isHotTower(t->P_rctowerId[j]));

			bool electronParCutOK =
				t->E_rcgPt[j]       > 0.2        &&
				fabs(t->E_rcgEta[j]) < 1.0       &&
				electronCutOK                    &&
				t->E_rcNCommonHits[j]>=10;//        &&
			//!(isHotTower(t->E_rctowerId[j]));

			//float wt= hGammadNdpTdy->GetBinContent(hGammadNdpTdy->FindBin(pt));
			float wt= hGammadNdpTdy->GetBinContent(hGammadNdpTdy->FindBin(pt))+hGammadNdpTdy->GetBinError(hGammadNdpTdy->FindBin(pt));
			float wtEle = wt*2/(2*TMath::Pi())/hRcptPosEle->GetBinWidth(hRcptPosEle->FindBin(E_rcPt))/1.4*20;
			float wtPos = wt*2/(2*TMath::Pi())/hRcptPosEle->GetBinWidth(hRcptPosEle->FindBin(P_rcPt))/1.4*20;
			//===========================
			//denominator
			//===========================
			if(positronPriCutOK){
				hRcpt->Fill(P_rcPt,wt);
				hRcptPosEle->Fill(P_rcPt,wtPos/P_rcPt);
				if(positronTriHT0PriCutOK){
					hRcptHT0->Fill(P_rcPt,wt);
					hRcptPosEleHT0->Fill(P_rcPt,wtPos/P_rcPt);
				}
				if(positronTriHT2PriCutOK){
					hRcptHT2->Fill(P_rcPt,wt);
					hRcptPosEleHT2->Fill(P_rcPt,wtPos/P_rcPt);
				}
				if(positronSMDPriCutOK){
					hRcptSMD->Fill(P_rcPt,wt);
					hRcptPosEleSMD->Fill(P_rcPt,wtPos/P_rcPt);
					if(positronTriHT0PriCutOK){
						hRcptHT0SMD->Fill(P_rcPt,wt);
						hRcptPosEleHT0SMD->Fill(P_rcPt,wtPos/P_rcPt);
					}
					if(positronTriHT2PriCutOK){
						hRcptHT2SMD->Fill(P_rcPt,wt);
						hRcptPosEleHT2SMD->Fill(P_rcPt,wtPos/P_rcPt);
					}
				}
			}
			if(electronPriCutOK){
				hRcpt->Fill(E_rcPt,wt);
				hRcptPosEle->Fill(E_rcPt,wtEle/E_rcPt);
				if(electronTriHT0PriCutOK){
					hRcptHT0->Fill(E_rcPt,wt);
					hRcptPosEleHT0->Fill(E_rcPt,wtEle/E_rcPt);
				}
				if(electronTriHT2PriCutOK){
					hRcptHT2->Fill(E_rcPt,wt);
					hRcptPosEleHT2->Fill(E_rcPt,wtEle/E_rcPt);
				}
				if(electronSMDPriCutOK){
					hRcptSMD->Fill(E_rcPt,wt);
					hRcptPosEleSMD->Fill(E_rcPt,wtEle/E_rcPt);
					if(electronTriHT0PriCutOK){
						hRcptHT0SMD->Fill(E_rcPt,wt);
						hRcptPosEleHT0SMD->Fill(E_rcPt,wtEle/E_rcPt);
					}
					if(electronTriHT2PriCutOK){
						hRcptHT2SMD->Fill(E_rcPt,wt);
						hRcptPosEleHT2SMD->Fill(E_rcPt,wtEle/E_rcPt);
					}
				}
			}
			//=======================
			//numerator
			//=======================
			if(positronCutOK && electronCutOK) {
				TVector3 Helix1P(positronRc.Px(),positronRc.Py(),positronRc.Pz());
				TVector3 Helix1O(t->P_HelixX[j],t->P_HelixY[j],t->P_HelixZ[j]);
				StPhysicalHelixD Helix1(Helix1P,Helix1O,bField,1);

				TVector3 Helix2P(electronRc.Px(),electronRc.Py(),electronRc.Pz());
				TVector3 Helix2O(t->E_HelixX[j],t->E_HelixY[j],t->E_HelixZ[j]);
				StPhysicalHelixD Helix2(Helix2P,Helix2O,bField,-1);

				double aPathLength = (Helix2.pathLengths(Helix1)).first;
				double ePathLength = (Helix2.pathLengths(Helix1)).second;

				TVector3 aOrigin = Helix2.at(aPathLength);
				TVector3 eOrigin = Helix1.at(ePathLength);
				TVector3 V0Origin = (aOrigin+eOrigin)*0.5;
				TVector3 diff = aOrigin-eOrigin; 

				if(diff.Mag()<0. || diff.Mag()>1.0) continue;

				TVector3 V0Mom1 = Helix1.momentumAt(ePathLength,bField);
				FourMom1.SetVectM(V0Mom1,MassE);

				TVector3 V0Mom2 = Helix2.momentumAt(aPathLength,bField);
				FourMom2.SetVectM(V0Mom2,MassE);

				TLorentzVector dieFourMom = FourMom1 + FourMom2;
				float eept  = dieFourMom.Pt();
				float eem   = dieFourMom.M();
				float eeeta = dieFourMom.Eta();
				if(positronPriCutOK && electronParCutOK&&t->E_rcgPt[j]>0.3){
					hmvspt->Fill(P_rcPt,eem);
					hmvsptWt->Fill(P_rcPt,eem,wt);
					if(positronTriHT0PriCutOK){
						hmvsptHT0->Fill(P_rcPt,eem);
						hmvsptWtHT0->Fill(P_rcPt,eem,wt);
					}
					if(positronTriHT2PriCutOK){
						hmvsptHT2->Fill(P_rcPt,eem);
						hmvsptWtHT2->Fill(P_rcPt,eem,wt);
					}
					if(positronSMDPriCutOK){
						hmvsptSMD->Fill(P_rcPt,eem);
						hmvsptWtSMD->Fill(P_rcPt,eem,wt);
						if(positronTriHT0PriCutOK){
							hmvsptHT0SMD->Fill(P_rcPt,eem);
							hmvsptWtHT0SMD->Fill(P_rcPt,eem,wt);
						}
						if(positronTriHT2PriCutOK){
							hmvsptHT2SMD->Fill(P_rcPt,eem);
							hmvsptWtHT2SMD->Fill(P_rcPt,eem,wt);
						}
					}
				}
				if(electronPriCutOK && positronParCutOK&&t->P_rcgPt[j]>0.3){
					hmvspt->Fill(E_rcPt,eem);
					hmvsptWt->Fill(E_rcPt,eem,wt);
					if(electronTriHT0PriCutOK){
						hmvsptHT0->Fill(E_rcPt,eem);
						hmvsptWtHT0->Fill(E_rcPt,eem,wt);
					}
					if(electronTriHT2PriCutOK){
						hmvsptHT2->Fill(E_rcPt,eem);
						hmvsptWtHT2->Fill(E_rcPt,eem,wt);
					}
					if(electronSMDPriCutOK){
						hmvsptSMD->Fill(E_rcPt,eem);
						hmvsptWtSMD->Fill(E_rcPt,eem,wt);
						if(electronTriHT0PriCutOK){
							hmvsptHT0SMD->Fill(E_rcPt,eem);
							hmvsptWtHT0SMD->Fill(E_rcPt,eem,wt);
						}
						if(electronTriHT2PriCutOK){
							hmvsptHT2SMD->Fill(E_rcPt,eem);
							hmvsptWtHT2SMD->Fill(E_rcPt,eem,wt);
						}
					}
				}
				if(eem<0.24) {
					if(positronPriCutOK && electronParCutOK) { //tag: positron, partner: electron
						hRcptMeeGptP->Fill(P_rcPt,wt);
						hGpTPart->Fill(P_rcPt,t->E_rcgPt[j]);
						hGpTPartWt->Fill(P_rcPt,t->E_rcgPt[j],wt);
						if(t->E_rcgPt[j]>0.3){
							hRcptMee->Fill(P_rcPt,wt);
							if(pe_P>0.6) hRcptMeePOE->Fill(P_rcPt,wt);
							if(positronTriHT0PriCutOK) hRcptMeeHT0->Fill(P_rcPt,wt);
							if(positronTriHT2PriCutOK) hRcptMeeHT2->Fill(P_rcPt,wt);
							if(eem<0.15){
								hRcptMeeSys->Fill(P_rcPt,wt);
								if(positronTriHT0PriCutOK) hRcptMeeSysHT0->Fill(P_rcPt,wt);
								if(positronTriHT2PriCutOK) hRcptMeeSysHT2->Fill(P_rcPt,wt);
							}
							if(positronSMDPriCutOK) { //tag: positron, partner: electron
								hRcptMeeSMD->Fill(P_rcPt,wt);
								if(pe_P>0.6) hRcptMeePOESMD->Fill(P_rcPt,wt);
								if(positronTriHT0PriCutOK) hRcptMeeHT0SMD->Fill(P_rcPt,wt);
								if(positronTriHT2PriCutOK) hRcptMeeHT2SMD->Fill(P_rcPt,wt);
								if(eem<0.15){
									hRcptMeeSysSMD->Fill(P_rcPt,wt);
									if(positronTriHT0PriCutOK) hRcptMeeSysHT0SMD->Fill(P_rcPt,wt);
									if(positronTriHT2PriCutOK) hRcptMeeSysHT2SMD->Fill(P_rcPt,wt);
								}
							}
						}
					}
					if(electronPriCutOK && positronParCutOK) { //tag: electron, partner: positron
						hRcptMeeGptP->Fill(E_rcPt,wt);
						hGpTPart->Fill(E_rcPt,t->P_rcgPt[j]);
						hGpTPartWt->Fill(E_rcPt,t->P_rcgPt[j],wt);
						if(t->P_rcgPt[j]>0.3){
							hRcptMee->Fill(E_rcPt,wt);
							if(pe_E>0.6) hRcptMeePOE->Fill(E_rcPt,wt);
							if(electronTriHT0PriCutOK) hRcptMeeHT0->Fill(E_rcPt,wt);
							if(electronTriHT2PriCutOK) hRcptMeeHT2->Fill(E_rcPt,wt);
							if(eem<0.15){
								hRcptMeeSys->Fill(E_rcPt,wt);
								if(electronTriHT0PriCutOK) hRcptMeeSysHT0->Fill(E_rcPt,wt);
								if(electronTriHT2PriCutOK) hRcptMeeSysHT2->Fill(E_rcPt,wt);
							}
							if(electronSMDPriCutOK) { //tag: electron, partner: positron
								hRcptMeeSMD->Fill(E_rcPt,wt);
								if(pe_E>0.6) hRcptMeePOESMD->Fill(E_rcPt,wt);
								if(electronTriHT0PriCutOK) hRcptMeeHT0SMD->Fill(E_rcPt,wt);
								if(electronTriHT2PriCutOK) hRcptMeeHT2SMD->Fill(E_rcPt,wt);
								if(eem<0.15){
									hRcptMeeSysSMD->Fill(E_rcPt,wt);
									if(electronTriHT0PriCutOK) hRcptMeeSysHT0SMD->Fill(E_rcPt,wt);
									if(electronTriHT2PriCutOK) hRcptMeeSysHT2SMD->Fill(E_rcPt,wt);
								}
							}
						}
					}
				}
			}
		}
	}
	TFile *fout = new TFile(FileOutPut,"recreate");
	fout->cd();
	hnTotal->Write();
	hnTotalyCut->Write();
	hRcpt->Write();
	hRcptPosEle->Write();
	hRcptHT0->Write();
	hRcptPosEleHT0->Write();
	hRcptHT2->Write();
	hRcptPosEleHT2->Write();
	hRcptSMD->Write();
	hRcptPosEleSMD->Write();
	hRcptHT0SMD->Write();
	hRcptPosEleHT0SMD->Write();
	hRcptHT2SMD->Write();
	hRcptPosEleHT2SMD->Write();
	hmvspt->Write();
	hmvsptWt->Write();
	hmvsptHT0->Write();
	hmvsptWtHT0->Write();
	hmvsptHT2->Write();
	hmvsptWtHT2->Write();
	hmvsptSMD->Write();
	hmvsptWtSMD->Write();
	hmvsptHT0SMD->Write();
	hmvsptWtHT0SMD->Write();
	hmvsptHT2SMD->Write();
	hmvsptWtHT2SMD->Write();
	hRcptMeeGptP->Write();
	hGpTPart->Write();
	hGpTPartWt->Write();
	hRcptMee->Write();
	hRcptMeePOE->Write();
	hRcptMeeHT0->Write();
	hRcptMeeHT2->Write();
	hRcptMeeSys->Write();
	hRcptMeeSysHT0->Write();
	hRcptMeeSysHT2->Write();
	hRcptMeeSMD->Write();
	hRcptMeePOESMD->Write();
	hRcptMeeHT0SMD->Write();
	hRcptMeeHT2SMD->Write();
	hRcptMeeSysSMD->Write();
	hRcptMeeSysHT0SMD->Write();
	hRcptMeeSysHT2SMD->Write();
	fout->Close();
	cout<<"end of program"<<endl;
	return(0);
	exit(0);
}
int isHotTower(int towId)
{
	//Int_t  Hot_towerlist[]={31, 51, 114, 275, 293, 479, 509, 533, 555, 561, 639, 681, 740, 743, 749, 772, 779, 799, 840, 860, 880, 893, 897, 982, 986, 993, 1063, 1142, 1160, 1200, 1224, 1232, 1237, 1241, 1256, 1263, 1280, 1284, 1306, 1313, 1318, 1337, 1438, 1486, 1537, 1592, 1709, 1713, 1732, 1823, 1850, 1856, 1879, 1945, 1976, 1984, 2043, 2145, 2162, 2164, 2190, 2202, 2290, 2299, 2300, 2313, 2339, 2414, 2439, 2459, 2529, 2580, 2633, 2652, 2834, 2863, 2865, 2874, 3005, 3020, 3061, 3137, 3154, 3420, 3515, 3532, 3692, 3720, 3737, 3838, 3861, 3925, 3948, 4013, 4130, 4169, 4262, 4316, 4430, 4458, 4534, 4560, 4595, 4684, 4766, 4781,};//from Bingchu note about event activity
	Int_t Hot_towerlist[]={31, 51, 114, 275, 293, 479, 509, 533, 555, 561, 639, 681, 740, 743, 749, 772, 779, 799, 840, 860, 880, 893, 897, 982, 986, 993, 1063, 1142, 1160, 1200, 1224, 1232, 1237, 1241, 1256, 1263, 1280, 1284, 1306, 1313, 1318, 1337, 1438, 1486, 1537, 1592, 1709, 1713, 1732, 1823, 1850, 1856, 1879, 1945, 1976, 1984, 2043, 2145, 2162, 2164, 2190, 2202, 2290, 2299, 2300, 2313, 2339, 2414, 2439, 2459, 2529, 2580, 2633, 2652, 2834, 2863, 2865, 2874, 3005, 3020, 3061, 3137, 3154, 3420, 3515, 3532, 3692, 3720, 3737, 3838, 3861, 3925, 3948, 4013, 4130, 4169, 4262, 4316, 4430, 4458, 4534, 4560, 4595, 4684, 4766, 4781,50,245,251,385,405,682,691,775,1042,1304,1422,1443,1892,1906,2021,2022,2047,2051,2063,2083,2109,2146,2171,2267,2303,2368,2445,2493,2504,2521,2750,2861,3063,3171,3241,3292,3451,3453,3544,3726,3749,4050,4122,4230,4232,4353,4453,4469,4546,4646,4722,4727};//from Bingchu note about event activity
	//Int_t Hot_towerlist[]={31, 51, 114, 275, 293, 479, 509, 533, 555, 561, 639, 681, 740, 743, 749, 772, 779, 799, 840, 860, 880, 893, 897, 982, 986, 993, 1063, 1142, 1160, 1200, 1224, 1232, 1237, 1241, 1256, 1263, 1280, 1284, 1306, 1313, 1318, 1337, 1438, 1486, 1537, 1592, 1709, 1713, 1732, 1823, 1850, 1856, 1879, 1945, 1976, 1984, 2043, 2145, 2162, 2164, 2190, 2202, 2290, 2299, 2300, 2313, 2339, 2414, 2439, 2459, 2529, 2580, 2633, 2652, 2834, 2863, 2865, 2874, 3005, 3020, 3061, 3137, 3154, 3420, 3515, 3532, 3692, 3720, 3737, 3838, 3861, 3925, 3948, 4013, 4130, 4169, 4262, 4316, 4430, 4458, 4534, 4560, 4595, 4684, 4766, 4781,245,251,385,691,775,1042,1304,1443,1906,2021,2051,2063,2083,2109,2267,2493,2504,2521,2750,3063,3292,3451,3453,3544,3726,4050,4230,4453,4646};//from Bingchu note about event activity
	Int_t   mNHotTower;
	mNHotTower = sizeof(Hot_towerlist)/sizeof(int);
	for(Int_t i=0;i<mNHotTower;i++ )
	{
		if(Hot_towerlist[i]==towId)

			return kTRUE;
	}
	return kFALSE;
}
Double_t CrystalBall2(Double_t *x, Double_t *par)
{
	Double_t N = par[0];
	Double_t mu = par[1];
	Double_t s = par[2];
	Double_t n1 = par[3];
	Double_t alpha1 = par[4];
	Double_t n2 = par[5];
	Double_t alpha2 = par[6];

	Double_t A = TMath::Power(n1/fabs(alpha1), n1) * TMath::Exp(-alpha1*alpha1/2.);
	Double_t B = n1/fabs(alpha1) - fabs(alpha1);

	Double_t C = TMath::Power(n2/fabs(alpha2), n2) * TMath::Exp(-alpha2*alpha2/2.);
	Double_t D = n2/fabs(alpha2) - fabs(alpha2);

	Double_t norm = (x[0]-mu)/s;

	if(norm < -alpha1) {
		return N * A * TMath::Power(B-norm, -n1);
	} else if(norm < alpha2) {
		return N * TMath::Exp(-0.5*norm*norm);
	} else {
		return N * C * TMath::Power(D+norm, -n2);
	}
}
//-------------------------------------------------------------------------------
Double_t ABf(double *x, double *par)
{
	double a = par[0];
	double b = par[1];
	//double f = (a*a*x[0]*x[0] + b*b);
	double f = sqrt(a*a*x[0]*x[0] + b*b);

	return f;
}
//-------------------------------------------------------------------------------
Double_t SmearPt(double mcpt)
{

	TF1 *f_AB = new TF1("f_AB", &ABf, 0, 20, 2 );
	f_AB->SetParameters(0.005580,0.008293);////from bingchu's event activities note
	double sigmaptoverpt = (double)f_AB->Eval(mcpt);

	TF1 *f_CB2 = new TF1("f_CB2", &CrystalBall2, -0.5, 0.5, 7 );

	f_CB2->SetParameters(2.893e4,-0.001152,0.01034,1.305,1.659,3.432,1.75);
	//f_CB2->SetParErrors(47.65,0.000015,0.00002,0.008,0.005,0.042,0.01);

	double deltaPtovermcPt_RDM = f_CB2->GetRandom();

	double smrpt = mcpt + mcpt*(deltaPtovermcPt_RDM/0.01)*sigmaptoverpt;//sigmaptoverpt: real resolution from data and emebeding Jpsi signal matching;deltaPtovermcPt_RDM/0.01: rc pt possibility in this MC pt, using 0.01 is due to all resolution is normalized to 0.01.

	return smrpt;
}
