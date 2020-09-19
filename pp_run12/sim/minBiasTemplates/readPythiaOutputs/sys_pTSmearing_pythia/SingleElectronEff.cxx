//Analysis trees from embedding
//Author ShenghuiZhang
//09/2016
///////////////////////////////////////////////////////////

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
#include "TRandom3.h"
#include "TMath.h"
#include "TVector2.h"
#include "TVector3.h"
//#include "StThreeVectorF.hh"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TUnixSystem.h"
#include "TRandom3.h"
#include "TGraphErrors.h"
#include "TMath.h"
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>

//#include "StPhysicalHelixD.h"
//#include "SystemOfUnits.h"
//#include "PhysicalConstants.h"

#include "mcT.h"
#include "histogram.h"
#include "mBadRunList.h"

using namespace std;

int main(int argc, char **argv)
{
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
	weightFile=new TFile("fonll200gev.root","READ");
	gFONLLu=(TGraphErrors *) weightFile->Get("gFONLLu");
	double x[152],y[152],xerr[152],yerr[152];
	for(int i=0; i<gFONLLu->GetN(); i++) {
		int a=gFONLLu->GetPoint(i,x[i],y[i]);
		y[i]=y[i]*2*TMath::Pi()*x[i]/30.;
		yerr[i]=gFONLLu->GetErrorY(i)*2*TMath::Pi()*x[i]/30.;
		xerr[i]=gFONLLu->GetErrorX(i);
	}
	gFONLL =new TGraphErrors(152,x,y,xerr,yerr);
	MassE = 0.000511;

	hmcpt              = new TH1F("hmcpt","",1000,0.,20.);
	hmcptw             = new TH1F("hmcptw","",nPtBinsAll,ptbinAll);
	hPtCorr            = new TH2F("PtCorr","",1000,0.,20.,1000,0.,20.);
	hPtDiff            = new TH2F("PtDiff","",1000,0.,20.,400,-0.5,0.5);
	hPtCorrJ            = new TH2F("PtCorrJ","",1000,0.,20.,1000,0.,20.);
	hPtDiffJ            = new TH2F("PtDiffJ","",1000,0.,20.,400,-0.5,0.5);
	hdeltaPtovermcPt_RDM= new TH1F("hdeltaPtovermcPt_RDM","",400,-0.5,0.5);
	hPtCorrg            = new TH2F("PtCorrg","",1000,0.,20.,1000,0.,20.);
	hPtDiffg            = new TH2F("PtDiffg","",1000,0.,20.,400,-0.5,0.5);
	hPtCorrW            = new TH2F("PtCorrW","",1000,0.,20.,1000,0.,20.);
	hPtDiffW            = new TH2F("PtDiffW","",1000,0.,20.,400,-0.5,0.5);
	hPtCorrJW            = new TH2F("PtCorrJW","",1000,0.,20.,1000,0.,20.);
	hPtDiffJW            = new TH2F("PtDiffJW","",1000,0.,20.,400,-0.5,0.5);
	hPtCorrgW            = new TH2F("PtCorrgW","",1000,0.,20.,1000,0.,20.);
	hPtDiffgW            = new TH2F("PtDiffgW","",1000,0.,20.,400,-0.5,0.5);
	hrcpt              = new TH1F("hrcpt","",1000,0.,20.);
	hrcptw             = new TH1F("hrcptw","",nPtBinsAll,ptbinAll);
	hrcptmc            = new TH1F("hrcptmc","",1000,0.,20.);
	hrcptmcw           = new TH1F("hrcptmcw","",nPtBinsAll,ptbinAll);
	hTPCtracksTHT0      = new TH1F("TPCtracksTHT0","",nPtBinsAll,ptbinAll);
	hTPCtracksTHT2      = new TH1F("TPCtracksTHT2","",nPtBinsAll,ptbinAll);
	hTPCtracksTHT0Mc    = new TH1F("TPCtracksTHT0Mc","",nPtBinsAll,ptbinAll);
	hTPCtracksTHT2Mc    = new TH1F("TPCtracksTHT2Mc","",nPtBinsAll,ptbinAll);
	hnHitsFit          = new TH2F("hnHitsFit","",1000,0.,20.,50,0.,50.);
	hnHitsDedx         = new TH2F("hnHitsDedx","",1000,0.,20.,50,0.,50.);
	hDca               = new TH2F("hDca","",1000,0.,20.,50,0.,5.);
	hnHitsFitWt        = new TH2F("hnHitsFitWt","",1000,0.,20.,50,0.,50.);
	hnHitsDedxWt       = new TH2F("hnHitsDedxWt","",1000,0.,20.,50,0.,50.);
	hDcaWt             = new TH2F("hDcaWt","",1000,0.,20.,50,0.,5.);
	hrcptwnHitsFit     = new TH1F("hrcptwnHitsFit","",nPtBinsAll,ptbinAll);
	hrcptwnHitsDedx    = new TH1F("hrcptwnHitsDedx","",nPtBinsAll,ptbinAll);
	hrcptwDca          = new TH1F("hrcptwDca","",nPtBinsAll,ptbinAll);
	hTPCtracksAdc0SysHT0      = new TH1F("hTPCtracksAdc0SysHT0","",nPtBinsAll,ptbinAll);
	hTPCtracksAdc0SysHT2      = new TH1F("hTPCtracksAdc0SysHT2","",nPtBinsAll,ptbinAll);
	hTPCtracksPOESysHT0      = new TH1F("hTPCtracksPOESysHT0","",nPtBinsAll,ptbinAll);
	hTPCtracksPOESysHT2      = new TH1F("hTPCtracksPOESysHT2","",nPtBinsAll,ptbinAll);
	hTPCtracksAdc0SysSMDHT0   = new TH1F("hTPCtracksAdc0SysSMDHT0","",nPtBinsAll,ptbinAll);
	hTPCtracksAdc0SysSMDHT2   = new TH1F("hTPCtracksAdc0SysSMDHT2","",nPtBinsAll,ptbinAll);
	hTPCtracksPOESysSMDHT0   = new TH1F("hTPCtracksPOESysSMDHT0","",nPtBinsAll,ptbinAll);
	hTPCtracksPOESysSMDHT2   = new TH1F("hTPCtracksPOESysSMDHT2","",nPtBinsAll,ptbinAll);
	//hEMCmatchingtracks = new TH1F("EMCmatchingtracks","",nPtBinsAll,ptbinAll);
	hPve               = new TH2F("Pve","",1000,0.,20.,120,0.,3.);
	hEMCtracks         = new TH1F("EMCtracks","",nPtBinsAll,ptbinAll);
	hTPCtracksHT0      = new TH1F("TPCtracksHT0","",nPtBinsAll,ptbinAll);
	//hTPCtracksHT0      = new TH1F("TPCtracksHT0","",500,0,10);
	hTPCtracksHT2      = new TH1F("TPCtracksHT2","",nPtBinsAll,ptbinAll);
	hTPCtracksHT0Mc    = new TH1F("TPCtracksHT0Mc","",nPtBinsAll,ptbinAll);
	hTPCtracksHT2Mc    = new TH1F("TPCtracksHT2Mc","",nPtBinsAll,ptbinAll);
	hTPCtracksSMDHT0   = new TH1F("TPCtracksSMDHT0","",nPtBinsAll,ptbinAll);
	hTPCtracksSMDHT2   = new TH1F("TPCtracksSMDHT2","",nPtBinsAll,ptbinAll);
	hTPCtracksSMDHT0Mc = new TH1F("TPCtracksSMDHT0Mc","",nPtBinsAll,ptbinAll);
	hTPCtracksSMDHT2Mc = new TH1F("TPCtracksSMDHT2Mc","",nPtBinsAll,ptbinAll);
	hSMDtracks         = new TH1F("SMDtracks","",nPtBinsAll,ptbinAll);
	hAdc0vsdsmAdc      = new TH2F("Adc0vsdsmAdc","",1000,0,2000,100,0,100);
	hAdc0vsdsmAdcCut   = new TH2F("Adc0vsdsmAdcCut","",1000,0,2000,100,0,100);
	hAdc0              = new TH2F("Adc0","",1000,0,20,1000,0,2000);
	hdsmAdc            = new TH2F("dsmAdc","",1000,0,20,100,0,100);
	hAdc0Cut           = new TH2F("Adc0Cut","",1000,0,20,1000,0,2000);
	hdsmAdcCut         = new TH2F("dsmAdcCut","",1000,0,20,100,0,100);
	//--------------------
	// loop the chain
	//--------------------
	TChain *chain = new TChain("mcT");
	chain->Add(FileInPut.Data());

	int nevents = (int)chain->GetEntries();
	cout << "== total entries : " << nevents << endl;

	mcT *t = new mcT(chain);
	mNBadRuns = sizeof(mBadRuns_HT)/sizeof(int);

	//TRandom *gRandom = new TRandom3();
	gRandom->SetSeed(atoi(argv[2]));
	cout<<"argv[2] "<<gRandom->GetSeed()<<" "<<argv[2]<<" "<<atoi(argv[2])<<endl;

	//TF1 *myGaus = new TF1("myGaus","gaus",-10,10);
	//myGaus->SetParameters(1,-0.4036,0.8688);

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

		int nTracks   = t->nTracks;
		for(int j=0;j<nTracks;j++) {

			//===========================
			if(t->parentGeantId[j]!=0)continue;
			float mcpt  = t->E_mcPt[j];
			float mceta = t->E_mcEta[j];
			float mcphi = t->E_mcPhi[j];
			TLorentzVector Mc(0.,0.,0.,0.);
			Mc.SetPtEtaPhiM(mcpt,mceta,mcphi,MassE);
			bool tag = kFALSE;
			for(int g=0;g<nTracks;g++){
				if(g==j) continue;
				if(t->parentGeantId[g]!=0)continue;
				float mcptk  = t->E_mcPt[g];
				float mcetak = t->E_mcEta[g];
				float mcphik = t->E_mcPhi[g];
				TLorentzVector Mck(0.,0.,0.,0.);
				Mck.SetPtEtaPhiM(mcptk,mcetak,mcphik,MassE);

				Double_t deta = Mc.Rapidity() - Mck.Rapidity();
				Double_t dphi = mcphi - mcphik;
				while(dphi>2*TMath::Pi()) dphi -= 2.*TMath::Pi();
				while(dphi<0) dphi += 2.*TMath::Pi();
				while(dphi>TMath::Pi()) dphi = dphi -2*TMath::Pi();
				if(TMath::Abs(deta)<0.1 && TMath::Abs(dphi)<0.5) tag = kTRUE;
			}
			if(tag) continue;
			if(fabs(mceta)>0.7)continue;
			if(mcpt<0.2||mcpt>15)continue;
			float wt = gFONLL->Eval(mcpt);
			/////////////////////
			//eff TPC denominator
			/////////////////////
			hmcpt->Fill(mcpt);
			hmcptw->Fill(mcpt,wt);
			if(t->E_rcNCommonHits[j]<10) continue;
			float pt = t->E_rcPt[j];
			if(pt!=-999) pt = SmearPt(mcpt);
			if(pt!=-999){
				hPtCorr->Fill(mcpt, t->E_rcPt[j]);
				hPtDiff->Fill(mcpt, (t->E_rcPt[j]-mcpt)/mcpt);
				hPtCorrJ->Fill(mcpt, pt);
				hPtDiffJ->Fill(mcpt, (pt-mcpt)/mcpt);
				hPtCorrg->Fill(mcpt, t->E_rcgPt[j]);
				hPtDiffg->Fill(mcpt, (t->E_rcgPt[j]-mcpt)/mcpt);
				hPtCorrW->Fill(mcpt, t->E_rcPt[j],wt);
				hPtDiffW->Fill(mcpt, (t->E_rcPt[j]-mcpt)/mcpt,wt);
				hPtCorrJW->Fill(mcpt, pt,wt);
				hPtDiffJW->Fill(mcpt, (pt-mcpt)/mcpt,wt);
				hPtCorrgW->Fill(mcpt, t->E_rcgPt[j],wt);
				hPtDiffgW->Fill(mcpt, (t->E_rcgPt[j]-mcpt)/mcpt,wt);
			}
			if(isHotTower(t->E_rctowerId[j])) continue;
			float eta = t->E_rcEta[j];
			float phi = t->E_rcPhi[j];
			//if(fabs(eta)>0.7) continue;
			float dca = t->E_dca[j];
			//float nsigma = myGaus->GetRandom();
			int  nHitsFit = t->E_rcNHitsFit[j];
			int  nMaxPts = t->E_rcNHitsPoss[j];
			int  nDedxPts = t->E_rcNdEdx[j];
			float Rx = t->E_HelixX[j]; 
			float Ry = t->E_HelixY[j];
			float FirstTpcR = sqrt(Rx*Rx+Ry*Ry);
			float e = t->E_rcEnergy0[j];
			int   adc0 = t->E_rcadc0[j];
			int   dsmAdc = t->E_rcdsmadc[j];
			TLorentzVector Rc(0.,0.,0.,0.);
			//Rc.SetPtEtaPhiM(t->E_rcgPt[j],t->E_rcgEta[j],t->E_rcgPhi[j],MassE);
			Rc.SetPtEtaPhiM(pt,eta,phi,MassE);
			//Rc.SetPtEtaPhiM(t->E_rcPt[j],eta,phi,MassE);
			float p = Rc.P();//sqrt(pow(Rc.Px(),2)+pow(Rc.Py(),2)+pow(Rc.Pz(),2));
			float pe = (e>0)? p/e:9999;
			int  nEta = t->E_rcnEta[j];
			int  nPhi = t->E_rcnPhi[j];
			if(nEta<0)nEta=0;
			if(nPhi<0)nPhi=0;
			float zDist = t->E_rczDist[j];
			float phiDist = t->E_rcphiDist[j];
			bool cutOK = 
				nMaxPts>0   &&
				fabs(1.0*nHitsFit)/nMaxPts>0.52 &&
				fabs(1.0*nHitsFit)/nMaxPts<1.02;
			if(fabs(eta)<0.7&&cutOK) {
				//if(cutOK)
				if (nDedxPts>=15 && dca<1.5 && FirstTpcR<73){
					hnHitsFit->Fill(pt, nHitsFit);
					hnHitsFitWt->Fill(pt, nHitsFit,wt);
				}

				if(nHitsFit>=20 && dca<1.5 && FirstTpcR<73){
					hnHitsDedx->Fill(pt, nDedxPts);
					hnHitsDedxWt->Fill(pt, nDedxPts,wt);
				}

				if(nHitsFit>=20 && nDedxPts>=15 && FirstTpcR<73){
					hDca->Fill(pt, dca);
					hDcaWt->Fill(pt, dca,wt);
				}
			}
			////////////////////////////////////////////
			if(cutOK && nHitsFit>=20 && nDedxPts>=15 && dca<1.5 && FirstTpcR<73)
			{
				////////////////////////////////////// 
				//eff TPC numerator
				//////////////////////////////////////
				hrcpt->Fill(pt);
				hrcptw->Fill(pt,wt);
				hrcptmc->Fill(mcpt);
				hrcptmcw->Fill(mcpt,wt);
				if(nHitsFit>=25)
					hrcptwnHitsFit->Fill(pt,wt);
				if(nDedxPts>=18)
					hrcptwnHitsDedx->Fill(pt,wt);
				if(dca<1.0)
					hrcptwDca->Fill(pt,wt);
				hAdc0vsdsmAdc->Fill(adc0,dsmAdc,wt);
				hAdc0->Fill(pt,adc0,wt);
				hdsmAdc->Fill(pt,dsmAdc,wt);
				if(dsmAdc>11&&adc0>180){
					hTPCtracksTHT0->Fill(pt,wt);
					hTPCtracksTHT0Mc->Fill(mcpt,wt);
				}
				if(dsmAdc>18&&adc0>300){
					hTPCtracksTHT2->Fill(pt,wt);
					hTPCtracksTHT2Mc->Fill(mcpt,wt);
				}
				if(e>0){
					///////////////////////////////////////
					hPve->Fill(pt,pe,wt);
					if(pe>0.3&&pe<1.5){
						hEMCtracks->Fill(pt,wt);
						//cout<<"adc0"<<adc0<<"dsmadc"<<dsmAdc<<endl;
						hAdc0vsdsmAdcCut->Fill(adc0,dsmAdc,wt);
						hAdc0Cut->Fill(pt,adc0,wt);
						hdsmAdcCut->Fill(pt,dsmAdc,wt);
						if(dsmAdc>11&&adc0>180){
							hTPCtracksHT0->Fill(pt,wt);
							hTPCtracksHT0Mc->Fill(mcpt,wt);
							if(adc0>196)hTPCtracksAdc0SysHT0->Fill(pt,wt);
							if(pe>0.6)hTPCtracksPOESysHT0->Fill(pt,wt);
						}
						if(dsmAdc>18&&adc0>300){
							hTPCtracksHT2->Fill(pt,wt);
							hTPCtracksHT2Mc->Fill(mcpt,wt);
							if(adc0>316)hTPCtracksAdc0SysHT2->Fill(pt,wt);
							if(pe>0.6)hTPCtracksPOESysHT2->Fill(pt,wt);
						}
						if(nEta>1&&nPhi>1&&fabs(zDist)<3&&fabs(phiDist)<0.015){
							hSMDtracks->Fill(pt,wt);
							if(dsmAdc>11&&adc0>180){
								hTPCtracksSMDHT0->Fill(pt,wt);
								hTPCtracksSMDHT0Mc->Fill(mcpt,wt);
								if(adc0>196)hTPCtracksAdc0SysSMDHT0->Fill(pt,wt);
								if(pe>0.6)hTPCtracksPOESysSMDHT0->Fill(pt,wt);
							}
							if(dsmAdc>18&&adc0>300){
								hTPCtracksSMDHT2->Fill(pt,wt);
								hTPCtracksSMDHT2Mc->Fill(mcpt,wt);
								if(adc0>316)hTPCtracksAdc0SysSMDHT2->Fill(pt,wt);
								if(pe>0.6)hTPCtracksPOESysSMDHT2->Fill(pt,wt);
							}
						}
					}
				}
			}
		} //track loop
	} // end event looping
	TFile *fout = new TFile(FileOutPut,"recreate");
	fout->cd();
	hmcpt->Write();
	hrcpt->Write();
	hPtCorr->Write();
	hPtDiff->Write();
	hPtCorrJ->Write();
	hPtDiffJ->Write();
	hPtCorrg->Write();
	hPtDiffg->Write();
	hPtCorrW->Write();
	hPtDiffW->Write();
	hPtCorrJW->Write();
	hPtDiffJW->Write();
	hPtCorrgW->Write();
	hPtDiffgW->Write();
	hrcptmc->Write();
	hmcptw->Write();
	hrcptw->Write();
	hrcptmcw->Write();
	hTPCtracksTHT0->Write();
	hTPCtracksTHT2->Write();
	hTPCtracksTHT0Mc->Write();
	hTPCtracksTHT2Mc->Write();
	hnHitsFit->Write();
	hnHitsDedx->Write();
	hDca->Write();
	hnHitsFitWt->Write();
	hnHitsDedxWt->Write();
	hDcaWt->Write();
	hrcptwnHitsFit->Write();
	hrcptwnHitsDedx->Write();
	hrcptwDca->Write();
	hTPCtracksAdc0SysHT0->Write();
	hTPCtracksAdc0SysHT2->Write();
	hTPCtracksPOESysHT0->Write();
	hTPCtracksPOESysHT2->Write();
	hTPCtracksAdc0SysSMDHT0->Write();
	hTPCtracksAdc0SysSMDHT2->Write();
	hTPCtracksPOESysSMDHT0->Write();
	hTPCtracksPOESysSMDHT2->Write();
	//hEMCmatchingtracks->Write();
	hPve->Write();
	hEMCtracks->Write();
	hTPCtracksHT0->Write();
	hTPCtracksHT2->Write();
	hTPCtracksHT0Mc->Write();
	hTPCtracksHT2Mc->Write();
	hSMDtracks->Write();
	hTPCtracksSMDHT0->Write();
	hTPCtracksSMDHT2->Write();
	hTPCtracksSMDHT0Mc->Write();
	hTPCtracksSMDHT2Mc->Write();
	hAdc0vsdsmAdc->Write();
	hAdc0vsdsmAdcCut->Write();
	hAdc0->Write();
	hAdc0Cut->Write();
	hdsmAdc->Write();
	hdsmAdcCut->Write();
	hdeltaPtovermcPt_RDM->Write();

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

Double_t SmearPt(double mcpt)
{

	TF1 *f_AB = new TF1("f_AB", &ABf, 0, 20, 2 );
	f_AB->SetParameters(0.005580,0.008293);////from bingchu's event activities note
	double sigmaptoverpt = (double)f_AB->Eval(mcpt);

	TF1 *f_CB2 = new TF1("f_CB2", &CrystalBall2, -0.5, 0.5, 7 );

	f_CB2->SetParameters(2.893e4,-0.001152,0.01034,1.305,1.659,3.432,1.75);
	//f_CB2->SetParErrors(47.65,0.000015,0.00002,0.008,0.005,0.042,0.01);

	double deltaPtovermcPt_RDM = f_CB2->GetRandom();
	//cout<<"deltaPtovermcPt_RDM"<<deltaPtovermcPt_RDM<<endl;
	hdeltaPtovermcPt_RDM->Fill(deltaPtovermcPt_RDM);

	double smrpt = mcpt + mcpt*(deltaPtovermcPt_RDM/0.01)*sigmaptoverpt;//sigmaptoverpt: real resolution from data and emebeding Jpsi signal matching;deltaPtovermcPt_RDM/0.01: rc pt possibility in this MC pt, using 0.01 is due to all resolution is normalized to 0.01.

	return smrpt;
}
