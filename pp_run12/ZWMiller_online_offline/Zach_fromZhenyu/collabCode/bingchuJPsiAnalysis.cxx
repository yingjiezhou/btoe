#define Mkaon 0.493677
#define Mproton 0.93827231
#define Melectron 0.00051099907
#define PI 3.1415927

//#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "sys/types.h"
#include "dirent.h"

#include "math.h"
#include "string.h"
//Add the data structure
#include <iomanip>
//#include <stdio.h> 

#ifndef __CINT__  
#include "TROOT.h"
#include "TFile.h" 
#include "TChain.h"
#include "TMath.h"
#include "TH1.h" 
#include "TH2.h"   
#include "TH3.h" 
#include "TF1.h" 
#include "TStyle.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TVector2.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TUnixSystem.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#include "pevent.h"
#include "anaCuts.h"
using std::cout;
using std::endl;
using std::setw;
#endif 

enum pairMode{
	OneEID=1,
	TwoEID=2
};

void bookHistograms(char* outFile);
bool passEvent(pevent* event);
bool passTrack(pevent* event, int i);
bool EmcTrackOverlap(pevent* event);
bool TpcTrackOverlap(pevent* event);
void makeRealPairs();
void makeCorrelationPairs();
void makeMixedPairs(int cenBufferPointer, int vzBufferPointer);
void makeMixedCorrPairs(int cenBufferPointer, int vzBufferPointer);
void copyCurrentToBuffer(int cenBufferPointer, int vzBufferPointer);
void writeHistograms(char* outFile);
void printCuts();
void setPairingMode(pairMode mode);
double getHadronWt(double pt, double eta);

TH2F *hNe;
TH1F *hTriggerId;
TH2F *hNJpsiHadron;

TH3F *hNHadronZdcXPt;
TH3F *hNHadronZdcXPtLS;

TH3F *hEmceEtaPtNsige;
TH3F *hNumInvMassvsPtMB;
TH3F *hDenInvMassvsPtMB;
TH3F *hDenInvMassvsPtLikePosMB;
TH3F *hDenInvMassvsPtLikeNegMB;
TH3F *hDenInvMassvsPtRotateMB;

TH3F *hNumdPhiJpsiPtHPt;
TH3F *hNumdPhiJpsiPtHPtEffWt;
TH3F *hDendPhiJpsiPtHPtLike;
TH3F *hDendPhiJpsiPtHPtLikeEffWt;
TH3F *hDendPhiJpsiPtHPtSide;
TH3F *hDendPhiJpsiPtHPtSideEffWt;
TH3F *hDendPhiJpsiPtHPtMix;
TH3F *hDendPhiJpsiPtHPtMixEffWt;
TH2F *hDenJpsiHdEtavsdPhiMix;
TH2F *hDenJpsiHdEtavsdPhiMixEffWt;

//add for embedding
TH2F *hTpcEplusPtEta;
TH2F *hTpcEminusPtEta;
TH2F *hEmcEplusPtEta;
TH2F *hEmcEminusPtEta;
TH1F *hnTrigE;

TH2F *hTrigEEtavsPhi;

TH2F *hnSigEvsp, *hnSigEvspt;
TH2F *hnSigEvspCut1, *hnSigEvsptCut1;
TH2F *hnSigEvspCut2, *hnSigEvsptCut2;

TH2F* hHt0PuritynSigEvsPt;
TH2F* hHt1PuritynSigEvsPt;
TH2F* hHt2PuritynSigEvsPt;
TH2F* hHt0PuritynSigEvsP;
TH2F* hHt1PuritynSigEvsP;
TH2F* hHt2PuritynSigEvsP;


TH2F *hDataEmcdeltaEta;
TH2F *hDataEmcdeltaPhi;
TH2F *hDataEmcdeltaR;

TH2F *hDataTpcdeltaEta;
TH2F *hDataTpcdeltaPhi;
TH2F *hDataTpcdeltaR;

TH2F *hDataPEvsPt;
TH2F *hDataPEvsPtHT2;
TH2F *hDataPEvsPtHT0;
TH2F *hDataPEvsPtHT1;

TH2F *hDataPEvsPtHT1Cut;
TH2F *hDataAdc0vsPt;
TH2F *hDataHt0Adc0vsPt;
TH2F *hDataHt1Adc0vsPt;
TH2F *hDataHt1Adc0vsPtCut;
TH2F *hDataHt2Adc0vsPt;

TH2F *hHitsFitvsPt;
TH2F *hHitsFitvsHitsDedx;
TH2F *hHitsDedxvsPt;
TH2F *hDcavsPt;
TH2F *hEtavsPt;
TH2F *hPhivsPt;
TH2F *hNegPhivsPt;
TH2F *hPosPhivsPt;


pairMode mPairingMode = OneEID;
const int MaxEmcElectron = 1000, MaxTpcElectron = 1000, MaxJpsi = 20, MaxHadron = 1000;
int iran = 0;
int current_nEmce, current_nTpce, current_nJpsi, current_nJpsiLS, current_nHadron, current_nTrigE, current_nJpsiSide;
int current_centrality = 0;
TLorentzVector current_emce[MaxEmcElectron];
TLorentzVector current_tpce[MaxTpcElectron];

int current_jpsiDau1Id[MaxJpsi], current_jpsiDau2Id[MaxJpsi];
TLorentzVector current_jpsi[MaxJpsi];
int current_jpsiLSDau1Id[MaxJpsi], current_jpsiLSDau2Id[MaxJpsi];
TLorentzVector current_jpsiLS[MaxJpsi];
int current_jpsiSideDau1Id[MaxJpsi], current_jpsiSideDau2Id[MaxJpsi];
TLorentzVector current_jpsiSide[MaxJpsi];

int current_hadronId[MaxHadron];
TVector3 current_hadron[MaxHadron];

char current_tpceTofTag[MaxTpcElectron];
int current_emceId[MaxEmcElectron], current_tpceId[MaxTpcElectron];
char current_emceq[MaxEmcElectron], current_tpceq[MaxTpcElectron];
char current_emcIsTrg[MaxEmcElectron];
bool  current_EmcHits[MaxEmcElectron];
bool current_TpcHits[MaxTpcElectron];

int vzBufferPointer, cenBufferPointer;
const int nVzBin = 100;
const int nCenBin = 1;
const int nMaxEventsInBuffer = 10;
int nEventsInBuffer[nCenBin][nVzBin];
bool buffer_fullFlag[nCenBin][nVzBin];
int buffer_nEmce[nCenBin][nVzBin][nMaxEventsInBuffer], buffer_nTpce[nCenBin][nVzBin][nMaxEventsInBuffer];
TLorentzVector buffer_emce[nCenBin][nVzBin][nMaxEventsInBuffer][MaxEmcElectron];
TLorentzVector buffer_tpce[nCenBin][nVzBin][nMaxEventsInBuffer][MaxTpcElectron];
char buffer_emceq[nCenBin][nVzBin][nMaxEventsInBuffer][MaxEmcElectron];
char buffer_emcIsTrg[nCenBin][nVzBin][nMaxEventsInBuffer][MaxEmcElectron];
char buffer_tpceq[nCenBin][nVzBin][nMaxEventsInBuffer][MaxTpcElectron];
char buffer_tpceTofTag[nCenBin][nVzBin][nMaxEventsInBuffer][MaxTpcElectron];


int buffer_nJpsi[nCenBin][nVzBin][nMaxEventsInBuffer], buffer_nHadron[nCenBin][nVzBin][nMaxEventsInBuffer];
TLorentzVector buffer_jpsi[nCenBin][nVzBin][nMaxEventsInBuffer][MaxJpsi];
TVector3 buffer_hadron[nCenBin][nVzBin][nMaxEventsInBuffer][MaxHadron];
int nHadrons[4] = {0,0,0,0};

bool  isBHT0;
bool  isBHT1;
bool  isBHT2;
int mHTselect = 0;
TRandom3 *myRandom;
TFile *mFile;
double effPars[20][3];
TF1 *fEff;

int main(int argc, char** argv) 
{
	if(argc!=1&&argc!=5) return -1;
	char *inFile="testana.list";
	char outFile[1024];
	sprintf(outFile,"test");
	if(argc==5){
		inFile = argv[1];
		//sprintf(outFile,"%s_%s",mHeader,argv[2]);
		sprintf(outFile,"%s",argv[2]);
		pairMode mode = static_cast<pairMode>(atoi(argv[3]));
		cout<<"input arguements: "<<argv[1]<<" "<<argv[2]<<" "<<argv[3]<<" "<<argv[4]<<endl;
		if(mode>TwoEID||mode<OneEID){ 
			cout<<"wrong input mode : "<<argv[3]<<endl;
			return -1;
		}
		setPairingMode(mode);
		mHTselect = atoi(argv[4]);
		cout<<"input HT trigger = "<<mHTselect<<endl;
	}

	myRandom = new TRandom3();

	bookHistograms(outFile);

	//+---------------------------------+
	//| open files and add to the chain |
	//+---------------------------------+
	TChain *chain = new TChain("pevent");

	Int_t ifile=0;
	char filename[512];
	ifstream *inputStream = new ifstream;
	inputStream->open(inFile);
	if (!(inputStream)) {
		printf("can not open list file\n");
		return 0;
	}
	for(;inputStream->good();){
		inputStream->getline(filename,512);
		if(inputStream->good()) {
			TFile *ftmp = new TFile(filename);
			if(!ftmp||!(ftmp->IsOpen())||!(ftmp->GetNkeys())) {
				cout<<"something wrong"<<endl;
			} else {
				cout<<"read in "<<ifile<<"th file: "<<filename<<endl;
				chain->Add(filename);
				ifile++;
			}
			delete ftmp;
		}
	}
	delete inputStream;
	pevent *eventtree = new pevent(chain);

	ifstream inf("/global/homes/h/huangbc/pwg/eliza14_bk/jpsi/emb/pikp_run12/txt/comb_eff_fit.txt");
	if(!inf.good()){ 
		cout<<"No input efficiency tables!"<<endl;
		return -1;
	}
	for(int i=0;i<20;i++){
		for(int j=0;j<3;j++) inf>>effPars[i][j];
	}
	fEff = new TF1("fEff","[0]*exp(-pow([1]/x,[2]))",0.2,15);

	//+-------------+
	//| loop events |
	//+-------------+
	Int_t n = chain->GetEntries();
	cout<<n<<" events"<<endl;

	for(int i=0;i<n;i++){ 
		if(i%10000==0) cout << "begin " << i << "th entry...." << endl;
		eventtree->GetEntry(i);

		current_nEmce = 0;
		current_nTpce = 0;
		current_nJpsi = 0;
		current_nJpsiSide = 0;
		current_nJpsiLS = 0;
		current_nHadron = 0;
		current_nTrigE = 0;

		for(int j=0;j<4;j++) nHadrons[j] = 0;

		isBHT0      = kFALSE;
		isBHT1      = kFALSE;
		isBHT2      = kFALSE;
		current_centrality = 0;

		for(Int_t m=0;m<MaxEmcElectron;m++)
		{
			current_EmcHits[m] = kTRUE;
			current_TpcHits[m] = kFALSE;
		}


		if(!passEvent(eventtree)) continue;
		EmcTrackOverlap(eventtree);
		TpcTrackOverlap(eventtree);
		for(int j=0;j<eventtree->npTracks;j++) passTrack(eventtree, j);
		hNe->Fill(current_nEmce,current_nTpce);
		hnTrigE->Fill(current_nTrigE);

		vzBufferPointer=int((eventtree->vz-mVzCut[0])/(mVzCut[1]-mVzCut[0])*nVzBin);
		if(vzBufferPointer<0||vzBufferPointer>=nVzBin) {
			cout<<"vz out of range!!!!"<<endl;
			continue;
		}

		cenBufferPointer= current_centrality;
		//cout<<"current_nEmce = "<<current_nEmce<<" current_nTpce = "<<current_nTpce<<endl;
		if(current_nEmce+current_nTpce<2) continue;

		makeRealPairs();
		makeMixedPairs(cenBufferPointer,vzBufferPointer);
		makeMixedCorrPairs(cenBufferPointer,vzBufferPointer);
		copyCurrentToBuffer(cenBufferPointer, vzBufferPointer);
		makeCorrelationPairs();

		if(current_nJpsi>0){ 
			for(int k=0;k<4;k++) hNHadronZdcXPt->Fill(zdcRate, nHadrons[k], k+0.5);
		}
		if(current_nJpsiLS>0){
			for(int k=0;k<4;k++) hNHadronZdcXPtLS->Fill(zdcRate, nHadrons[k], k+0.5);
		}
		hNJpsiHadron->Fill(current_nJpsi,current_nHadron);

	}//end of event loop	
	cout<<"Writing histograms into "<<outFile<<".ana.root"<<endl;
	writeHistograms(outFile);
	delete chain;
	printCuts();
	cout<<"end of program"<<endl; 
	return 0;
} 
//===============================================================================================
void makeRealPairs()
{
	TLorentzVector jpsi(0,0,0,0);
	//+-------------+
	//| TPCe + TPCe |
	//+-------------+
	if(!isBHT0&&!isBHT1&&!isBHT2){
	for(int i=0;i<current_nTpce;i++) {
		for(int j=i+1;j<current_nTpce;j++) {
			if(current_tpceId[i]==current_tpceId[j]) continue;
			//cout<<"current_tpceTofTag[i] = "<<current_tpceTofTag[i]*1<<" current_tpceTofTag[j] = "<<current_tpceTofTag[j]*1<<endl;
			if(mPairingMode==TwoEID){
				if(!current_tpceTofTag[i]||!current_tpceTofTag[j]) continue;
			}
			if(mPairingMode==OneEID){
				if(!current_tpceTofTag[i]&&!current_tpceTofTag[j]) continue;
			}
			//cout<<"mPairingMode = "<<mPairingMode*1<<" pass "<<endl;
			jpsi = current_tpce[i] + current_tpce[j];
			Double_t pt_low = current_tpce[j].Pt();
			if(pt_low>=2.) pt_low = 2. - 1e-4;
			if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]) {
				if(current_tpceq[i]+current_tpceq[j]==0) {//unlike-sign
					if(current_centrality==0){ 
						hNumInvMassvsPtMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
						if(jpsi.M()>mJpsiMassCut[0]&&jpsi.M()<mJpsiMassCut[1]){
							current_jpsi[current_nJpsi]=jpsi;
							current_jpsiDau1Id[current_nJpsi] = current_tpceId[i];
							current_jpsiDau2Id[current_nJpsi] = current_tpceId[j];
							current_nJpsi++;
						}
						if((jpsi.M()>2.6&&jpsi.M()<2.7)||(jpsi.M()>3.5&&jpsi.M()<3.6)){

							current_jpsiSide[current_nJpsiSide]=jpsi;
							current_jpsiSideDau1Id[current_nJpsiSide] = current_tpceId[i];
							current_jpsiSideDau2Id[current_nJpsiSide] = current_tpceId[j];
							current_nJpsiSide++;
						}
					}
				} else if(current_tpceq[i]+current_tpceq[j]==2) {//like-sign positive
					if(current_centrality==0){ 
						hDenInvMassvsPtLikePosMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
						if(jpsi.M()>mJpsiMassCut[0]&&jpsi.M()<mJpsiMassCut[1]){
							current_jpsiLS[current_nJpsiLS]=jpsi;
							current_jpsiLSDau1Id[current_nJpsiLS] = current_tpceId[i];
							current_jpsiLSDau2Id[current_nJpsiLS] = current_tpceId[j];
							current_nJpsiLS++;
						}
					}
				} else if(current_tpceq[i]+current_tpceq[j]==-2) {//like-sign negative
					if(current_centrality==0){ 
						hDenInvMassvsPtLikeNegMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
						if(jpsi.M()>mJpsiMassCut[0]&&jpsi.M()<mJpsiMassCut[1]){
							current_jpsiLS[current_nJpsiLS]=jpsi;
							current_jpsiLSDau1Id[current_nJpsiLS] = current_tpceId[i];
							current_jpsiLSDau2Id[current_nJpsiLS] = current_tpceId[j];
							current_nJpsiLS++;
						}
					}
				}
			}

			//+--------------+
			//| rotate Tpc e |
			//+--------------+
			TLorentzVector tpceRotate(0,0,0,0);
			tpceRotate.SetVectM(-current_tpce[i].Vect(), current_tpce[i].M());
			jpsi = tpceRotate + current_tpce[j];
			if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]&&
					current_tpceq[i]+current_tpceq[i]==0) {
				if(current_centrality==0) hDenInvMassvsPtRotateMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
			}
		}//end of TPC e loop
	}//end of TPC e loop
	}


	//+-------------+
	//| EMCe + TPCe |
	//+-------------+
	for(int i=0;i<current_nEmce;i++) {
		for(int j=0;j<current_nTpce;j++) {
			if(current_emceId[i]==current_tpceId[j]) continue;
			if(current_emcIsTrg[i]<0) continue;
			if(mPairingMode==TwoEID){
				if(!current_tpceTofTag[j]) continue;
			}
			//if(mPairingMode==OneEID){
			// do nothing
			//}
			jpsi = current_emce[i] + current_tpce[j];
			Double_t pt_low = current_tpce[j].Pt();
			if(pt_low>=2.) pt_low = 2. - 1e-4;
			if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]) {

				if(current_emceq[i]+current_tpceq[j]==0) {//unlike-sign
					if(current_centrality==0){ 
						hNumInvMassvsPtMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
						if(jpsi.M()>mJpsiMassCut[0]&&jpsi.M()<mJpsiMassCut[1]){
							current_jpsi[current_nJpsi]=jpsi;
							current_jpsiDau1Id[current_nJpsi] = current_emceId[i];
							current_jpsiDau2Id[current_nJpsi] = current_tpceId[j];
							current_nJpsi++;
						}
						if((jpsi.M()>2.6&&jpsi.M()<2.7)||(jpsi.M()>3.5&&jpsi.M()<3.6)){

							current_jpsiSide[current_nJpsiSide]=jpsi;
							current_jpsiSideDau1Id[current_nJpsiSide] = current_emceId[i];
							current_jpsiSideDau2Id[current_nJpsiSide] = current_tpceId[j];
							current_nJpsiSide++;
						}

					}
				} else if(current_emceq[i]+current_tpceq[j]==2) {//like-sign positive
					if(current_centrality==0){ 
						hDenInvMassvsPtLikePosMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
						if(jpsi.M()>mJpsiMassCut[0]&&jpsi.M()<mJpsiMassCut[1]){
							current_jpsiLS[current_nJpsiLS]=jpsi;
							current_jpsiLSDau1Id[current_nJpsiLS] = current_emceId[i];
							current_jpsiLSDau2Id[current_nJpsiLS] = current_tpceId[j];
							current_nJpsiLS++;
						}
					}
				} else if(current_emceq[i]+current_tpceq[j]==-2) {//like-sign negative
					if(current_centrality==0){ 
						hDenInvMassvsPtLikeNegMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
						if(jpsi.M()>mJpsiMassCut[0]&&jpsi.M()<mJpsiMassCut[1]){
							current_jpsiLS[current_nJpsiLS]=jpsi;
							current_jpsiLSDau1Id[current_nJpsiLS] = current_emceId[i];
							current_jpsiLSDau2Id[current_nJpsiLS] = current_tpceId[j];
							current_nJpsiLS++;
						}
					}
				}
			}

			//+--------------+
			//| rotate EMC e |
			//+--------------+
			TLorentzVector emceRotate(0,0,0,0);
			emceRotate.SetVectM(-current_emce[i].Vect(), current_emce[i].M());
			jpsi = emceRotate + current_tpce[j];
			if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]&&
					current_emceq[i]+current_tpceq[i]==0) {
				if(current_centrality==0) hDenInvMassvsPtRotateMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
			}
		}//end of TPC e loop
	}//end of EMC e loop

	//+-----------+
	//| EMC + EMC |
	//+-----------+
	for(int i=0;i<current_nEmce;i++) {
		for(int j=i+1;j<current_nEmce;j++) {
			if(current_emceId[i]==current_emceId[j]) continue;
			if(current_emcIsTrg[i]>=0&&current_emcIsTrg[j]>=0) continue;
			if(current_emcIsTrg[i]<0&&current_emcIsTrg[j]<0) continue;
			jpsi = current_emce[i] + current_emce[j];
			Double_t pt_low = current_emce[j].Pt()>current_emce[i].Pt()?current_emce[i].Pt():current_emce[j].Pt();
			if(pt_low>=2.) pt_low = 2. - 1e-4;
			if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]) {
				if(current_emceq[i]+current_emceq[j]==0) {//unlike-sign
					if(current_centrality==0){ 
						hNumInvMassvsPtMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
						if(jpsi.M()>mJpsiMassCut[0]&&jpsi.M()<mJpsiMassCut[1]){
							current_jpsi[current_nJpsi]=jpsi;
							current_jpsiDau1Id[current_nJpsi] = current_emceId[i];
							current_jpsiDau2Id[current_nJpsi] = current_emceId[j];
							current_nJpsi++;
						}
						if((jpsi.M()>2.6&&jpsi.M()<2.7)||(jpsi.M()>3.4&&jpsi.M()<3.6)){

							current_jpsiSide[current_nJpsiSide]=jpsi;
							current_jpsiSideDau1Id[current_nJpsiSide] = current_emceId[i];
							current_jpsiSideDau2Id[current_nJpsiSide] = current_emceId[j];
							current_nJpsiSide++;
						}
					}
				} else if(current_emceq[i]+current_emceq[j]==2) {//like-sign positive
					if(current_centrality==0){ 
						hDenInvMassvsPtLikePosMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
						if(jpsi.M()>mJpsiMassCut[0]&&jpsi.M()<mJpsiMassCut[1]){
							current_jpsiLS[current_nJpsiLS]=jpsi;
							current_jpsiLSDau1Id[current_nJpsiLS] = current_emceId[i];
							current_jpsiLSDau2Id[current_nJpsiLS] = current_emceId[j];
							current_nJpsiLS++;
						}
					}
				} else if(current_emceq[i]+current_emceq[j]==-2) {//like-sign negative
					if(current_centrality==0){ 
						hDenInvMassvsPtLikeNegMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
						if(jpsi.M()>mJpsiMassCut[0]&&jpsi.M()<mJpsiMassCut[1]){
							current_jpsiLS[current_nJpsiLS]=jpsi;
							current_jpsiLSDau1Id[current_nJpsiLS] = current_emceId[i];
							current_jpsiLSDau2Id[current_nJpsiLS] = current_emceId[j];
							current_nJpsiLS++;
						}
					}
				}
			}

			//+-----------+
			//| rotate e+ |
			//+-----------+
			TLorentzVector emceRotate(0,0,0,0);
			emceRotate.SetVectM(-current_emce[i].Vect(), current_emce[i].M());
			jpsi = emceRotate + current_emce[j];
			if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]&&
					current_emceq[i]+current_emceq[j]==0) {
				if(current_centrality==0) hDenInvMassvsPtRotateMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
			}
		}//end of TPC e loop
	}//end of EMC e loop
}
//================================================================================================
void makeMixedPairs(int cenBufferPointer, int vzBufferPointer)
{
	TLorentzVector jpsi(0,0,0,0);
	for(int iBufferEvent=0;iBufferEvent<nEventsInBuffer[cenBufferPointer][vzBufferPointer];iBufferEvent++) {
		//+-------------------------------+
		//| current EMC e  + buffer TPC e |
		//+-------------------------------+
		for(int i=0;i<current_nEmce;i++) {
			for(int j=0;j<buffer_nTpce[cenBufferPointer][vzBufferPointer][iBufferEvent];j++) {
				if(current_emceq[i]+buffer_tpceq[cenBufferPointer][vzBufferPointer][iBufferEvent][j]!=0) continue;//select unlike-sign
				if(mPairingMode == TwoEID){
					if(!buffer_tpceTofTag[cenBufferPointer][vzBufferPointer][iBufferEvent][j]) continue;
				}
				jpsi = current_emce[i] + buffer_tpce[cenBufferPointer][vzBufferPointer][iBufferEvent][j];
				Double_t pt_low =buffer_tpce[cenBufferPointer][vzBufferPointer][iBufferEvent][j].Pt();
				if(pt_low>2.) pt_low = 2. - 1e-4;
				if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]) {
					if(current_centrality==0) hDenInvMassvsPtMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
				}
			}//end of current e+ loop
		}// end of buffer e- loop

		//+-------------------------------+
		//| current TPC e  + buffer EMC e |
		//+-------------------------------+
		for(int i=0;i<current_nTpce;i++) {
			for(int j=0;j<buffer_nEmce[cenBufferPointer][vzBufferPointer][iBufferEvent];j++) {
				if(current_tpceq[i]+buffer_emceq[cenBufferPointer][vzBufferPointer][iBufferEvent][j]!=0) continue;//select unlike-sign
				if(mPairingMode == TwoEID){
					if(!current_tpceTofTag[i]) continue;
				}
				jpsi = current_tpce[i] + buffer_emce[cenBufferPointer][vzBufferPointer][iBufferEvent][j];
				Double_t pt_low = current_tpce[i].Pt();
				if(pt_low>2.) pt_low = 2. - 1e-4;
				if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]) {
					if(current_centrality==0) hDenInvMassvsPtMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
				}
			}//end of current e+ loop
		}// end of buffer e- loop

		//+------------------------------+
		//| current EMC e + buffer EMC e |
		//+------------------------------+
		if(current_nEmce>1) {//this event has EMC e + EMC e pair 
			for(int i=0;i<current_nEmce;i++) {
				for(int j=0;j<buffer_nEmce[cenBufferPointer][vzBufferPointer][iBufferEvent];j++) {
					if(current_emceq[i]+buffer_emceq[cenBufferPointer][vzBufferPointer][iBufferEvent][j]!=0) continue;//select unlike-sign
					jpsi = current_emce[i] + buffer_emce[cenBufferPointer][vzBufferPointer][iBufferEvent][j];
					double pt1 = current_emce[i].Pt();
					double pt2 = buffer_emce[cenBufferPointer][vzBufferPointer][iBufferEvent][j].Pt();
					Double_t pt_low = pt1>pt2?pt2:pt1;
					if(pt_low>2.) pt_low = 2. - 1e-4;
					if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]) {
						if(current_centrality==0) hDenInvMassvsPtMB->Fill(jpsi.Pt(), pt_low, jpsi.M());
					}
				}//end of current e loop
			}//end of buffer e loop
		}//end of this event nEmce requirement

	}//end of buffer events loop
}
//================================================================================================
void makeMixedCorrPairs(int cenBufferPointer, int vzBufferPointer)
{
	TLorentzVector jpsi(0,0,0,0);
	TVector3 had(0,0,0);
	for(int iBufferEvent=0;iBufferEvent<nEventsInBuffer[cenBufferPointer][vzBufferPointer];iBufferEvent++) {
		//+-------------------------------+
		//| current jpsi  + buffer hadron |
		//+-------------------------------+
		for(int i=0;i<current_nJpsi;i++) {
			for(int j=0;j<buffer_nHadron[cenBufferPointer][vzBufferPointer][iBufferEvent];j++) {
				jpsi = current_jpsi[i];
				had = buffer_hadron[cenBufferPointer][vzBufferPointer][iBufferEvent][j];
				//Double_t pt_low = had.Pt();
				double pt_h = had.Pt();
				double eta_h = had.Eta();
				double wt = getHadronWt(pt_h,eta_h);
				double deta = jpsi.Eta()-eta_h;
				double dphi = jpsi.Phi()-had.Phi();
				if(dphi<-PI/2.) dphi+=2.*PI;
				if(dphi>3.*PI/2.) dphi-=2.*PI;
				if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]) {
					if(current_centrality==0){ 
						hDendPhiJpsiPtHPtMix->Fill(jpsi.Pt(), pt_h, dphi);
						hDendPhiJpsiPtHPtMixEffWt->Fill(jpsi.Pt(), pt_h, dphi, wt);
						if(pt_h>0.5){
							hDenJpsiHdEtavsdPhiMix->Fill(dphi,deta);
							hDenJpsiHdEtavsdPhiMixEffWt->Fill(dphi,deta,wt);
						}
					}
				}
			}// end of hadron
		}// end of jpsi

		//+-------------------------------+
		//| current hadron  + buffer jpsi |
		//+-------------------------------+
		for(int i=0;i<current_nHadron;i++) {
			for(int j=0;j<buffer_nJpsi[cenBufferPointer][vzBufferPointer][iBufferEvent];j++) {
				jpsi = buffer_jpsi[cenBufferPointer][vzBufferPointer][iBufferEvent][j];
				had = current_hadron[i];
				//Double_t pt_low = current_tpce[i].Pt();
				double pt_h = had.Pt();
				double eta_h = had.Eta();
				double wt = getHadronWt(pt_h,eta_h);
				double deta = jpsi.Eta()-eta_h;
				double dphi = jpsi.Phi()-had.Phi();
				if(dphi<-PI/2.) dphi+=2.*PI;
				if(dphi>3.*PI/2.) dphi-=2.*PI;
				//if(pt_low>2.) pt_low = 2. - 1e-4;
				if(jpsi.Rapidity()>mPairYCut[0]&&jpsi.Rapidity()<=mPairYCut[1]) {
					if(current_centrality==0){ 
						hDendPhiJpsiPtHPtMix->Fill(jpsi.Pt(), pt_h, dphi);
						hDendPhiJpsiPtHPtMixEffWt->Fill(jpsi.Pt(), pt_h, dphi, wt);
						if(pt_h>0.5){
							hDenJpsiHdEtavsdPhiMix->Fill(dphi,deta);
							hDenJpsiHdEtavsdPhiMixEffWt->Fill(dphi,deta,wt);
						}
					}
				}
			}//end of jpsi
		}// end of hadron
	}
}

//================================================================================================
void copyCurrentToBuffer(int cenBufferPointer, int vzBufferPointer)
{
	if(nEventsInBuffer[cenBufferPointer][vzBufferPointer]>=nMaxEventsInBuffer) buffer_fullFlag[cenBufferPointer][vzBufferPointer] = kTRUE;

	TRandom3 *gRandom = new TRandom3(iran++);
	int eventPointer = -1;
	if(buffer_fullFlag[cenBufferPointer][vzBufferPointer]){//full, random replace one
		eventPointer =  (int) gRandom->Uniform(0,nMaxEventsInBuffer-1e-6);
	} else {
		eventPointer = nEventsInBuffer[cenBufferPointer][vzBufferPointer];
	}
	delete gRandom;

	buffer_nEmce[cenBufferPointer][vzBufferPointer][eventPointer] = current_nEmce;
	for(int i=0;i<current_nEmce;i++) {
		buffer_emce[cenBufferPointer][vzBufferPointer][eventPointer][i] = current_emce[i];
		buffer_emceq[cenBufferPointer][vzBufferPointer][eventPointer][i] = current_emceq[i];
		buffer_emcIsTrg[cenBufferPointer][vzBufferPointer][eventPointer][i] = current_emcIsTrg[i];
	}

	buffer_nTpce[cenBufferPointer][vzBufferPointer][eventPointer] = current_nTpce;
	for(int i=0;i<current_nTpce;i++) {
		buffer_tpce[cenBufferPointer][vzBufferPointer][eventPointer][i] = current_tpce[i];
		buffer_tpceq[cenBufferPointer][vzBufferPointer][eventPointer][i] = current_tpceq[i];
		buffer_tpceTofTag[cenBufferPointer][vzBufferPointer][eventPointer][i] = current_tpceTofTag[i];
	}

	//J/psi
	buffer_nJpsi[cenBufferPointer][vzBufferPointer][eventPointer] = current_nJpsi;
	for(int i=0;i<current_nJpsi;i++) {
		buffer_jpsi[cenBufferPointer][vzBufferPointer][eventPointer][i] = current_jpsi[i];
	}

	//hadron
	buffer_nHadron[cenBufferPointer][vzBufferPointer][eventPointer] = current_nHadron;
	for(int i=0;i<current_nHadron;i++) {
		buffer_hadron[cenBufferPointer][vzBufferPointer][eventPointer][i] = current_hadron[i];
	}

	if(nEventsInBuffer[cenBufferPointer][vzBufferPointer]<nMaxEventsInBuffer) {
		nEventsInBuffer[cenBufferPointer][vzBufferPointer] += 1;
	}

}
//================================================================================================
void printCuts() 
{
	cout<<endl;
	cout<<"------- print all configures ----------"<<endl;
	cout<<"Event Cuts:"<<endl;
	cout<<mVzCut[0]<<" < vzTpc < "<<mVzCut[1]<<endl;
	cout<<"|vzVpd - vzTpc| < "<<mVzDiffCut<<endl;
	cout<<"ranking > "<<mRankingCut<<endl;
	cout<<"trigger Ids: ";
	for(int i=0;i<nTrigIds;i++){
		printf("0x%X \t",mTriggerId[i]);
	}
	cout<<endl;

	cout<<"Track Cuts:"<<endl;
	cout<<"+++TPC+++"<<endl;
	cout<<mPtCut[0]<<" < pT < "<<mPtCut[1]<<endl;
	cout<<mEtaCut[0]<<" < eta < "<<mEtaCut[1]<<endl;
	cout<<"0 < Dca < "<<mDcaCut<<endl;
	cout<<"nHitsFit >= "<<mHitsFitCut<<endl;
	cout<<"nHitsdEdx >= "<<mHitsDedxCut<<endl;
	cout<<"nHitsRatio > "<<mHitsRatioCut<<endl;
	cout<<mnSigECut[0]<<" < nSigmaE < "<<mnSigECut[1]<<endl;
	cout<<mnSigELooseCut[0]<<" < loose nSigmaE < "<<mnSigELooseCut[1]<<endl;

	cout<<"+++TOF+++"<<endl;
	cout<<"|yLocal| < "<<myLocalCut<<endl;
	cout<<mBetaCut[0]<<" < 1-1/beta < "<<mBetaCut[1]<<endl;

	cout<<"+++EMC+++"<<endl;
	cout<<mPveCut[0]<<" < p/E < "<<mPveCut[1]<<endl;

	cout<<"+++Pair Level+++"<<endl;
	cout<<mPairYCut[0]<<" < yee < "<<mPairYCut[1]<<endl;
	cout<<"--------- end of configures -----------"<<endl;
	cout<<endl;
}
//================================================================================================
bool passEvent(pevent* event)
{
	UShort_t triggerId = event->triggerId;
	int htId = -1;
	for(int i=0;i<nTrigIds;i++){
		if(triggerId & mTriggerId[i]) htId = i;
	}
	//0, bht0-vpdmb; 1, bht1-vpdmb; 2, bht2; 3, bht0-bbcmb-tof0; 4, bht1-bbcmb-tof0; 5, bht2-bbcmb; 

	hTriggerId->Fill(htId);	
	//cout<<"triggerId = "<<triggerId<<" htId = "<<htId<<endl;
	if(mHTselect==0){
		if(htId==0&&htId!=1&&htId!=2&&htId!=3&&htId!=4&&htId!=5){ isBHT0=kTRUE; return true;}
	}
	if(mHTselect==1){
		if(htId==1&&htId!=2&&htId!=3&&htId!=4&&htId!=5){ isBHT1=kTRUE; return true;}
	}
	if(mHTselect==2){
		if(htId==2&&htId!=3&&htId!=4&&htId!=5){ isBHT2=kTRUE; return true;}
	}
	if(mHTselect==3){
		if(htId==3&&htId!=4&&htId!=5){ isBHT0=kTRUE; return true;}
	}
	if(mHTselect==4){
		if(htId==4&&htId!=5){ isBHT1=kTRUE; return true;}
	}
	if(mHTselect==5){
		if(htId==5){ isBHT2=kTRUE; return true;}
	}
	return false;
}

//========================================================================
bool passTrack(pevent* event, Int_t i)
{
	Int_t q = (event->track_NHitsFit[i]>0) ? 1 : -1;
	if(q!=1&&q!=-1) return kFALSE;
	Int_t nHitsFit = abs(event->track_NHitsFit[i]);
	Int_t nHitsDedx = event->track_NHitsDedx[i];
	Float_t beta = event->track_mBTofBeta[i]/20000.;
	Float_t ylocal = event->track_mBTofylocal[i]/1000.;
	Float_t nSigmaE = event->track_nSigmaE[i]/100.;
	Float_t nSigmaPi = event->track_nSigmaPi[i]/100.;
	Float_t nSigmaK = event->track_nSigmaK[i]/100.;
	Float_t nSigmaP = event->track_nSigmaP[i]/100.;
	Float_t px = event->track_px[i];
	Float_t py = event->track_py[i];
	Float_t pz = event->track_pz[i];
	Float_t pve = event->track_pve[i]/1000.;
	Float_t dca = event->track_dca[i]/1000.;
	int tofmatchflag = 0;
	if(ylocal>-1.8&&ylocal<1.8&&beta>0) tofmatchflag = 1;
	Int_t trackId = i;
	TVector3 mom(0,0,0);
	mom.SetXYZ(px,py,pz);

	Float_t pt = mom.Perp();
	Float_t p  = mom.Mag();
	Float_t phi = mom.Phi();
	Float_t eta = mom.Eta();
	Char_t tpcFlag = event->track_tpcFlag[i];
	Char_t tofFlag = event->track_tofFlag[i];
	Char_t emcFlag = event->track_emcFlag[i];
	Char_t smdFlag = event->track_smdFlag[i];
	
	Float_t energy = 0;
	if(pve>0) energy = p/pve;
	Float_t adc = event->track_adc0[i];

	if(nSigmaPi<2&&nSigmaPi>-2)
	{
		hHitsFitvsPt->Fill(nHitsFit,pt);
		hHitsDedxvsPt->Fill(nHitsDedx,pt);
		hHitsFitvsHitsDedx->Fill(nHitsFit,nHitsDedx);
		hDcavsPt->Fill(dca,pt);
		hEtavsPt->Fill(eta,pt);
		hPhivsPt->Fill(phi,pt);
		if(q<0)hNegPhivsPt->Fill(phi,pt);
		if(q>0)hPosPhivsPt->Fill(phi,pt);
	}

	//save hadron
	if(nHitsFit>=mHadronnHitsFitCut&&dca>0&&dca<=mHadronDcaCut&&eta>mEtaCut[0]&&eta<mEtaCut[1]){ //2015 Jul 20.
		current_hadronId[current_nHadron] = trackId;
		current_hadron[current_nHadron] = mom;
		current_nHadron++;
		if(pt>0.2) nHadrons[0]++;	
		if(pt>0.5) nHadrons[1]++;	
		if(pt>1.0) nHadrons[2]++;	
		if(pt>1.5) nHadrons[3]++;	
	}

	if(eta<mEtaCut[0] || eta>mEtaCut[1]) return kFALSE;

	if(q>0) hEmceEtaPtNsige->Fill(eta,pt,nSigmaE+7.);
	else if(q<0) hEmceEtaPtNsige->Fill(eta,pt,nSigmaE-7.);

	hnSigEvsp->Fill(p*q,nSigmaE);
	hnSigEvspt->Fill(pt*q,nSigmaE);

	if((pt<3.&&pt>2)&&(1./beta>mBetaCut[0])&&(1./beta<mBetaCut[1]))
	{
		if(energy>0.0001)
		{
			if((isBHT0)&&(adc>=180)&&(current_EmcHits[i]))
			{
				hHt0PuritynSigEvsP->Fill(p,nSigmaE);
				hHt0PuritynSigEvsPt->Fill(pt,nSigmaE);
			}
			if((isBHT1)&&(adc>=250)&&(current_EmcHits[i]))
			{
				hHt1PuritynSigEvsP->Fill(p,nSigmaE);
				hHt1PuritynSigEvsPt->Fill(pt,nSigmaE);
			}
			if((isBHT2)&&(adc>=300)&&(current_EmcHits[i]))
			{
				hHt2PuritynSigEvsP->Fill(p,nSigmaE);
				hHt2PuritynSigEvsPt->Fill(pt,nSigmaE);
			}
		}
	}
	if((pt>=3.)&&(pt<6.)&&(tofmatchflag>0))
	{
		if(energy>0.0001)
		{
			if((isBHT0)&&(adc>=180)&&(current_EmcHits[i]))
			{
				hHt0PuritynSigEvsP->Fill(p,nSigmaE);
				hHt0PuritynSigEvsPt->Fill(pt,nSigmaE);
			}
			if((isBHT1)&&(adc>=250)&&(current_EmcHits[i]))
			{
				hHt1PuritynSigEvsP->Fill(p,nSigmaE);
				hHt1PuritynSigEvsPt->Fill(pt,nSigmaE);
			}
			if((isBHT2)&&(adc>=300)&&(current_EmcHits[i]))
			{
				hHt2PuritynSigEvsP->Fill(p,nSigmaE);
				hHt2PuritynSigEvsPt->Fill(pt,nSigmaE);
			}
		}
	}

	if(pt>=6.)
	{
		if(energy>0.0001)
		{
			if((isBHT0)&&(adc>=180)&&(current_EmcHits[i]))
			{
				hHt0PuritynSigEvsP->Fill(p,nSigmaE);
				hHt0PuritynSigEvsPt->Fill(pt,nSigmaE);
			}
			if((isBHT1)&&(adc>=250)&&(current_EmcHits[i]))
			{
				hHt1PuritynSigEvsP->Fill(p,nSigmaE);
				hHt1PuritynSigEvsPt->Fill(pt,nSigmaE);
			}
			if((isBHT2)&&(adc>=300)&&(current_EmcHits[i]))
			{
				hHt2PuritynSigEvsP->Fill(p,nSigmaE);
				hHt2PuritynSigEvsPt->Fill(pt,nSigmaE);
			}
		}
	}
				
				
	if(nSigmaE>mnSigECut[0]&&nSigmaE<mnSigECut[1]) hDataAdc0vsPt->Fill(pt,adc);
	if(pt>2.&&pt<3.)
	{
		if((1./beta>mBetaCut[0])&&(1./beta<mBetaCut[1])&&nSigmaE>mnSigECut[0]&&nSigmaE<mnSigECut[1])
		{

			if(energy>0.0001)
			{
				Float_t poE = p/energy;
				hDataPEvsPt->Fill(pt,poE);
				// BHT0  adc>180  emc-electron
				if((isBHT0)&&(adc>=180)&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT0->Fill(pt,poE);
					hDataHt0Adc0vsPt->Fill(pt,adc);
				}
				//BHT2  adc>300  emc-electron
				if((isBHT2)&&(adc>=300)&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT2->Fill(pt,poE);
					hDataHt2Adc0vsPt->Fill(pt,adc);
				}
				//BHT1 adc>250 emc-elcetron
				if((isBHT1)&&(adc>=250)&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT1->Fill(pt,poE);
					hDataHt1Adc0vsPt->Fill(pt,adc);
				}
				if(isBHT1&&(!(current_EmcHits[i])))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT1Cut->Fill(pt,poE);
					hDataHt1Adc0vsPtCut->Fill(pt,poE);
				}
			}
		}
	}
	if(pt>=3.&&pt<6.)
	{
		if((1./beta>mBetaCut[0])&&(1./beta<mBetaCut[1])&&nSigmaE>mnSigECut[0]&&nSigmaE<mnSigECut[1])
		{
			if(energy>0.0001)
			{
				Float_t poE = p/energy;
				hDataPEvsPt->Fill(pt,poE);
				// BHT0  adc>180  emc-electron
				if((isBHT0)&&(adc>=180)&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT0->Fill(pt,poE);
					hDataHt0Adc0vsPt->Fill(pt,adc);
				}
				//BHT2  adc>300  emc-electron
				if((isBHT2)&&(adc>=300)&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT2->Fill(pt,poE);
					hDataHt2Adc0vsPt->Fill(pt,adc);
				}
				//BHT1 adc>250 emc-elcetron
				if((isBHT1)&&(adc>=250)&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT1->Fill(pt,poE);
					hDataHt1Adc0vsPt->Fill(pt,adc);
				};
				if(isBHT1&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT1Cut->Fill(pt,poE);
					hDataHt1Adc0vsPtCut->Fill(pt,poE);
				}
			}
		}
	}

	if(pt>=6.)
	{
		if((1./beta>mBetaCut[0])&&(1./beta<mBetaCut[1])&&nSigmaE>mnSigECut[0]&&nSigmaE<mnSigECut[1])
		{

			if(energy>0.0001)
			{
				Float_t poE = p/energy;
				hDataPEvsPt->Fill(pt,poE);
				// BHT0  adc>180  emc-electron
				if((isBHT0)&&(adc>=180)&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT0->Fill(pt,poE);
					hDataHt0Adc0vsPt->Fill(pt,adc);
				}
				//BHT2  adc>300  emc-electron
				if((isBHT2)&&(adc>=300)&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT2->Fill(pt,poE);
					hDataHt2Adc0vsPt->Fill(pt,adc);
				}
				//BHT1 adc>250 emc-elcetron
				if((isBHT1)&&(adc>=250)&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT1->Fill(pt,poE);
					hDataHt1Adc0vsPt->Fill(pt,adc);
				}
				if(isBHT1&&(current_EmcHits[i]))
				{
					Float_t poE = p/energy;
					hDataPEvsPtHT1Cut->Fill(pt,poE);
					hDataHt1Adc0vsPtCut->Fill(pt,poE);
				}
			}
		}
	}

	if(nHitsFit<mEmcHitsFitCut) return kFALSE;
	if(nHitsDedx<mEmcHitsDedxCut) return kFALSE;
	if(dca>mDcaCut) return kFALSE;

	if(nSigmaE>mnSigELooseCut[0]&&nSigmaE<mnSigELooseCut[1]) {//select loose electron
		int isEmcTrk = 0;
		//if(pt>mEmcMinPt) cout<<"nSigmaE = "<<nSigmaE<<" pve = "<<pve<<" pt= "<<pt<<endl;
		if(nSigmaE>mnSigECut[0]&&nSigmaE<mnSigECut[1]&&pve>mPveCut[0]&&pve<mPveCut[1]&&pt>mEmcMinPt
				/*// remove SMD cuts
				  &&smdFlag
				  */
		  ){
			current_emce[current_nEmce].SetPtEtaPhiM(pt,eta,phi,Melectron);
			current_emceId[current_nEmce] = trackId;
			current_emceq[current_nEmce] = q;
			current_emcIsTrg[current_nEmce] = -1;
			if(isBHT0 && pt>2.0 && adc>180) current_emcIsTrg[current_nEmce]  = 0;
			if(isBHT1 && pt>2.0 && adc>250) current_emcIsTrg[current_nEmce]  = 1;
			if(isBHT2 && pt>2.0 && adc>300) current_emcIsTrg[current_nEmce]  = 2;
			
			if(current_emcIsTrg[current_nEmce]>=0){ 
				hTrigEEtavsPhi->Fill(phi,eta);
				current_nTrigE++;
			}
			current_nEmce++;
			isEmcTrk = 1;

			if(q>0) hEmcEplusPtEta->Fill(pt,eta);
			if(q<0) hEmcEminusPtEta->Fill(pt,eta);
		}

		//exclude Emc track
		if(!isEmcTrk){
			current_tpce[current_nTpce].SetPtEtaPhiM(pt,eta,phi,Melectron);
			current_tpceId[current_nTpce] = trackId;
			current_tpceq[current_nTpce] = q;
			current_tpceTofTag[current_nTpce] = 0;
			if(nSigmaE>mnSigECut[0]&&nSigmaE<mnSigECut[1]&&1./beta>mBetaCut[0]&&1./beta<mBetaCut[1]&&fabs(ylocal)<myLocalCut){
				current_tpceTofTag[current_nTpce] = 1;

				if(q>0) hTpcEplusPtEta->Fill(pt,eta);
				if(q<0) hTpcEminusPtEta->Fill(pt,eta);
			}
			current_nTpce++;
		}
	}
	return kTRUE;
}
//========================================================================
void bookHistograms(char* outFile){
	char buf[1024];
	sprintf(buf,"%s.ana.root",outFile);
	mFile = new TFile(buf,"recreate");
	hNe = new TH2F("hNe","#EMC e vs. #TPC e;#EMC e candidate;#TPC e candidate;Counts",50,0,50,50,0,50);
	hTriggerId = new TH1F("hTriggerId","hTriggerId;htId;Counts",10,-1,9);
	char *label[10] = {"Wrong","BHT0","BHT1*VPDMB","BHT2","BHT0*BBCMB*TOF0","BHT1*BBCMB*TOF0","BHT2*BBCMB","","",""};
	hTriggerId->SetYTitle("# of events");
	for(int i=0;i<10;i++) hTriggerId->GetXaxis()->SetBinLabel(i+1,label[i]);
	hTriggerId->GetXaxis()->LabelsOption("v");
	hNJpsiHadron = new TH2F("hNJpsiHadron","#J/#psi vs. #hadron;#J/#psi candidate;#hadron candidate;Counts",50,0,50,50,0,50);
	
	hNHadronZdcXPt = new TH3F("hNHadronZdcXPt","#hadron vs zdcX in different pT cut;zdcX; #hadron candidate; pT cutType",200,0,20000,50,0,50,4,0,4);
	hNHadronZdcXPtLS = new TH3F("hNHadronZdcXPtLS","#hadron vs zdcX in different pT cut in LS;zdcX; #hadron candidate; pT cutType",200,0,20000,50,0,50,4,0,4);

	hEmceEtaPtNsige = new TH3F("hEmceEtaPtNsige","hEmceEtaPtNsige", 20, -1.,1.,150,0,15,350,-20.,15.);

	hNumInvMassvsPtMB = new TH3F("hNumInvMassvsPtMB","same event mass spectrum in MB;p_{T} (GeV/c);p_{Tdau};M_{inv} (GeV/c^{2})",300,0,15,20,0,2,1200,0,6);
	hDenInvMassvsPtMB = new TH3F("hDenInvMassvsPtMB","mixed event mass spectrum in MB;p_{T} (GeV/c);p_{Tdau};M_{inv} (GeV/c^{2})",300,0,15,20,0,2,1200,0,6);
	hDenInvMassvsPtLikePosMB = new TH3F("hDenInvMassvsPtLikePosMB","like-sign pos mass spectrum in MB;p_{T} (GeV/c);p_{Tdau};M_{inv} (GeV/c^{2})",300,0,15,20,0,2,1200,0,6);
	hDenInvMassvsPtLikeNegMB = new TH3F("hDenInvMassvsPtLikeNegMB","like-sign neg mass spectrum in MB;p_{T} (GeV/c);p_{Tdau};M_{inv} (GeV/c^{2})",300,0,15,20,0,2,1200,0,6);
	hDenInvMassvsPtRotateMB = new TH3F("hDenInvMassvsPtRotateMB","ratate mass spectrum in MB;p_{T} (GeV/c);p_{Tdau};M_{inv} (GeV/c^{2})",300,0,15,20,0,2,1200,0,6);

	hNumdPhiJpsiPtHPt = new TH3F("hNumdPhiJpsiPtHPt","hNumdPhiJpsiPtHPt;J/#psi p_{T} (GeV/c);h p_{T};d#Phi_{J/#psi-h} ",60,0,15,60,0,15,300,-PI/2.,PI*3./2.);
	hNumdPhiJpsiPtHPtEffWt = new TH3F("hNumdPhiJpsiPtHPtEffWt","hNumdPhiJpsiPtHPtEffWt;J/#psi p_{T} (GeV/c);h p_{T};d#Phi_{J/#psi-h} ",60,0,15,60,0,15,300,-PI/2.,PI*3./2.);
	hNumdPhiJpsiPtHPtEffWt->Sumw2();

	hDendPhiJpsiPtHPtLike = new TH3F("hDendPhiJpsiPtHPtLike","hDendPhiJpsiPtHPtLike;J/#psi p_{T} (GeV/c);h p_{T};d#Phi_{J/#psi-h} ",60,0,15,60,0,15,300,-PI/2.,PI*3./2.);
	hDendPhiJpsiPtHPtLikeEffWt = new TH3F("hDendPhiJpsiPtHPtLikeEffWt","hDendPhiJpsiPtHPtLikeEffWt;J/#psi p_{T} (GeV/c);h p_{T};d#Phi_{J/#psi-h} ",60,0,15,60,0,15,300,-PI/2.,PI*3./2.);
	hDendPhiJpsiPtHPtLikeEffWt->Sumw2();

	hDendPhiJpsiPtHPtSide = new TH3F("hDendPhiJpsiPtHPtSide","hDendPhiJpsiPtHPtSide;J/#psi p_{T} (GeV/c);h p_{T};d#Phi_{J/#psi-h} ",60,0,15,60,0,15,300,-PI/2.,PI*3./2.);
	hDendPhiJpsiPtHPtSideEffWt = new TH3F("hDendPhiJpsiPtHPtSideEffWt","hDendPhiJpsiPtHPtSideEffWt;J/#psi p_{T} (GeV/c);h p_{T};d#Phi_{J/#psi-h} ",60,0,15,60,0,15,300,-PI/2.,PI*3./2.);
	hDendPhiJpsiPtHPtSideEffWt->Sumw2();
	
	hDendPhiJpsiPtHPtMix = new TH3F("hDendPhiJpsiPtHPtMix","hDendPhiJpsiPtHPtMix;J/#psi p_{T} (GeV/c);h p_{T};d#Phi_{J/#psi-h} ",60,0,15,60,0,15,300,-PI/2.,PI*3./2.);
	hDendPhiJpsiPtHPtMixEffWt = new TH3F("hDendPhiJpsiPtHPtMixEffWt","hDendPhiJpsiPtHPtMixEffWt;J/#psi p_{T} (GeV/c);h p_{T};d#Phi_{J/#psi-h} ",60,0,15,60,0,15,300,-PI/2.,PI*3./2.);
	hDendPhiJpsiPtHPtMixEffWt->Sumw2();

	hDenJpsiHdEtavsdPhiMix = new TH2F("hDenJpsiHdEtavsdPhiMix","hDenJpsiHdEtavsdPhiMix;#Delta#phi;#Delta#eta ",300,-PI/2.,3./2.*PI,80,-2.,2.);
	hDenJpsiHdEtavsdPhiMixEffWt = new TH2F("hDenJpsiHdEtavsdPhiMixEffWt","hDenJpsiHdEtavsdPhiMixEffWt;#Delta#phi;#Delta#eta ",300,-PI/2.,3./2.*PI,80,-2.,2.);
	hDenJpsiHdEtavsdPhiMixEffWt->Sumw2();

	hEmcEplusPtEta = new TH2F("hEmcEplusPtEta","Tpc e^{+} Pt vs. Eta;p_{T} (GeV/c);#eta",150,0,15,20,-1,1);
	hTpcEplusPtEta = new TH2F("hTpcEplusPtEta","Tpc e^{+} Pt vs. Eta;p_{T} (GeV/c);#eta",150,0,15,20,-1,1);
	hTpcEminusPtEta = new TH2F("hTpcEminusPtEta","Tpc e^{+} Pt vs. Eta;p_{T} (GeV/c);#eta",150,0,15,20,-1,1);
	hEmcEminusPtEta = new TH2F("hEmcEminusPtEta","Tpc e^{+} Pt vs. Eta;p_{T} (GeV/c);#eta",150,0,15,20,-1,1);

	hnTrigE = new TH1F("hnTrigE","n Triggered e; # triggered e;",10,0,10);
	hTrigEEtavsPhi = new TH2F("hTrigEEtavsPhi","triggered e #eta vs #phi; #phi; #eta",120,-PI,PI,40,-1,1);

	hnSigEvsp = new TH2F("hnSigEvsp","nSigmaE vs. p;p (GeV/c);nSigE ;Counts",12000,-30,30,200,-10,10);
	hnSigEvspt = new TH2F("hnSigEvspt","nSigmaE vs. pT;p_{T} (GeV/c);nSigE ;Counts",12000,-30,30,200,-10,10);
	hnSigEvspCut1 = new TH2F("hnSigEvspCut1","nSigmaE vs. p after PID;p (GeV/c);nSigE (keV/cm);Counts",12000,-30,30,200,-10,10);
	hnSigEvsptCut1 = new TH2F("hnSigEvsptCut1","nSigmaE vs. pT after PID;p_{T} (GeV/c);nSigE (keV/cm);Counts",12000,-30,30,200,-10,10);
	hnSigEvspCut2 = new TH2F("hnSigEvspCut2","nSigmaE vs. p after PID;p (GeV/c);nSigE (keV/cm);Counts",12000,-30,30,200,-10,10);
	hnSigEvsptCut2 = new TH2F("hnSigEvsptCut2","nSigmaE vs. pT after PID;p_{T} (GeV/c);nSigE (keV/cm);Counts",12000,-30,30,200,-10,10);

	hHt0PuritynSigEvsPt = new TH2F("hHt0PuritynSigEvsPt","nSigmaE vs. pT after PID;p_{T} (GeV/c);nSigE (keV/cm);Counts",300,0,30,200,-10,10);
	hHt1PuritynSigEvsPt = new TH2F("hHt1PuritynSigEvsPt","nSigmaE vs. pT after PID;p_{T} (GeV/c);nSigE (keV/cm);Counts",300,0,30,200,-10,10);
	hHt2PuritynSigEvsPt = new TH2F("hHt2PuritynSigEvsPt","nSigmaE vs. pT after PID;p_{T} (GeV/c);nSigE (keV/cm);Counts",300,0,30,200,-10,10);
	hHt0PuritynSigEvsP = new TH2F("hHt0PuritynSigEvsP","nSigmaE vs. p after PID;p (GeV/c);nSigE (keV/cm);Counts",300,0,30,200,-10,10);
	hHt1PuritynSigEvsP = new TH2F("hHt1PuritynSigEvsP","nSigmaE vs. p after PID;p (GeV/c);nSigE (keV/cm);Counts",300,0,30,200,-10,10);
	hHt2PuritynSigEvsP = new TH2F("hHt2PuritynSigEvsP","nSigmaE vs. p after PID;p (GeV/c);nSigE (keV/cm);Counts",300,0,30,200,-10,10);

	hDataAdc0vsPt    = new TH2F("hDataAdc0vsPt","Adc0vsPt;p_{T}^{data} (GeV/c);Adc0",300,0,30,1000,0,1000);
	hDataHt0Adc0vsPt = new TH2F("hDataHt0Adc0vsPt","Ht0Adc0vsPt;p_{T}^{data} (GeV/c);Adc0 (HT0)",300,0,30,1000,0,1000);
	hDataHt1Adc0vsPt = new TH2F("hDataHt1Adc0vsPt","Ht1Adc0vsPt;p_{T}^{data} (GeV/c);Adc0 (HT1)",300,0,30,1000,0,1000);
	hDataHt1Adc0vsPtCut = new TH2F("hDataHt1Adc0vsPtCut","Ht1Adc0vsPt;p_{T}^{data} (GeV/c);Adc0 (HT1)",300,0,30,1000,0,1000);
	hDataHt2Adc0vsPt = new TH2F("hDataHt2Adc0vsPt","Ht2Adc0vsPt;p_{T}^{data} (GeV/c);Adc0 (HT2)",300,0,30,1000,0,1000);

	hDataPEvsPt= new TH2F("hDataPEvsPt","pE vs pt;p_{T} GeV/c;pE",300,0,30,300,0,3);

	hDataPEvsPtHT0 = new TH2F("hDataPEvsPtHT0","pE vs pt for BHT0;p_{T} GeV/c;pE",300,0,30,300,0,3);
	hDataPEvsPtHT1 = new TH2F("hDataPEvsPtHT1","pE vs pt for BHT1;p_{T} GeV/c;pE",300,0,30,300,0,3);
	hDataPEvsPtHT1Cut = new TH2F("hDataPEvsPtHT1Cut","pE vs pt for BHT1;p_{T} GeV/c;pE",300,0,30,300,0,3);
	hDataPEvsPtHT2 = new TH2F("hDataPEvsPtHT2","pE vs pt for BHT2;p_{T} GeV/c;pE",300,0,30,300,0,3);


	hHitsFitvsPt = new TH2F("hHitsFitvsPt","nHitsFit vs Pt;# of HitsFit;p_{T} (GeV/c)",50,0,50,300,0,30);
	hHitsFitvsHitsDedx = new TH2F("hHitsFitvsHitsDedx","nHitsFit vs nHitsDedx;# of HitsFit;nHitsDedx",50,0,50,50,0,50);
	hHitsDedxvsPt = new TH2F("hHitsDedxvsPt","nHitsDedx vs Pt;# of HitsFit;p_{T} (GeV/c)",50,0,50,300,0,30);
	hDcavsPt = new TH2F("hDcavsPt","Dca vs Pt;dca (cm);p_{T} (GeV/c)",150,0,15,300,0,30);
	hEtavsPt = new TH2F("hEtavsPt","Eta vs Pt;#eta ;p_{T} (GeV/c)",40,-3,3,300,0,30);
	hPhivsPt = new TH2F("hPhivsPt","phi vs Pt;#phi ;p_{T} (GeV/c)",360,-TMath::Pi(),TMath::Pi(),300,0,30);
	hNegPhivsPt = new TH2F("hNegPhivsPt","phi vs Pt;#phi ;p_{T} (GeV/c)",360,-TMath::Pi(),TMath::Pi(),300,0,30);
	hPosPhivsPt = new TH2F("hPosPhivsPt","phi vs Pt;#phi ;p_{T} (GeV/c)",360,-TMath::Pi(),TMath::Pi(),300,0,30);


	hDataEmcdeltaEta = new TH2F("hDataEmcdeltaEta","Eta vs Pt;p_{T} GeV/c;Eta",300,0,30,40,-2,-2);
	hDataEmcdeltaPhi = new TH2F("hDataEmcdeltaPhi","phi vs Pt;p_{T} GeV/c;Phi",300,0,30,360,-TMath::Pi(),TMath::Pi());
	hDataEmcdeltaR = new TH2F("hDataEmcdeltaR","dealtaR vs Pt;p_{T} GeV/c;deltaR",300,0,30,1000,0,100);

	hDataTpcdeltaEta = new TH2F("hDataTpcdeltaEta","Eta vs Pt;p_{T} GeV/c;Eta",300,0,30,40,-2,-2);
	hDataTpcdeltaPhi = new TH2F("hDataTpcdeltaPhi","phi vs Pt;p_{T} GeV/c;Phi",300,0,30,360,-TMath::Pi(),TMath::Pi());
	hDataTpcdeltaR = new TH2F("hDataTpcdeltaR","dealtaR vs Pt;p_{T} GeV/c;deltaR",300,0,30,1000,0,100);

}
//===============================================================================================
void writeHistograms(char* outFile)
{
	mFile->cd();
	//hNe->Write();
	//hEmceEtaPtNsige->Write();
	//hNumInvMassvsPtMB->Write();
	//hDenInvMassvsPtMB->Write();
	//hDenInvMassvsPtLikePosMB->Write();
	//hDenInvMassvsPtLikeNegMB->Write();
	//hDenInvMassvsPtRotateMB->Write();
	//hNumdPhiJpsiPtHPt->Write();
	//hDendPhiJpsiPtHPtLike->Write();
	mFile->Write();
	mFile->Close();
} 

void setPairingMode(pairMode mode){
	mPairingMode = mode;
}

void makeCorrelationPairs(){


	//+-------------+
	//| J/psi + h   |
	//+-------------+

	//unlike-sign
	for(int i=0;i<current_nJpsi;i++){
		int dau1id = current_jpsiDau1Id[i];
		int dau2id = current_jpsiDau2Id[i];
		for(int j=0;j<current_nHadron;j++){
			int hid = current_hadronId[j];
			if(dau1id==hid || dau2id==hid) continue;
			double phi_jpsi = current_jpsi[i].Phi();
			double pt_jpsi = current_jpsi[i].Pt();

			double phi_h = current_hadron[j].Phi();
			double pt_h = current_hadron[j].Pt();
			double dphi = phi_jpsi-phi_h;
			double eta_h = current_hadron[j].Eta();
			double wt = getHadronWt(pt_h,eta_h);
			if(dphi<-PI/2.) dphi+=2.*PI;
			if(dphi>3.*PI/2.) dphi-=2.*PI;
			hNumdPhiJpsiPtHPt->Fill(pt_jpsi,pt_h,dphi);
			hNumdPhiJpsiPtHPtEffWt->Fill(pt_jpsi,pt_h,dphi,wt);
		}
	}

	//like-sign
	for(int i=0;i<current_nJpsiLS;i++){
		int dau1id = current_jpsiLSDau1Id[i];
		int dau2id = current_jpsiLSDau2Id[i];
		for(int j=0;j<current_nHadron;j++){
			int hid = current_hadronId[j];
			if(dau1id==hid || dau2id==hid) continue;
			double phi_jpsi = current_jpsiLS[i].Phi();
			double pt_jpsi = current_jpsiLS[i].Pt();

			double phi_h = current_hadron[j].Phi();
			double pt_h = current_hadron[j].Pt();
			double dphi = phi_jpsi-phi_h;
			double eta_h = current_hadron[j].Eta();
			double wt = getHadronWt(pt_h,eta_h);

			if(dphi<-PI/2.) dphi+=2.*PI;
			if(dphi>3.*PI/2.) dphi-=2.*PI;
			hDendPhiJpsiPtHPtLike->Fill(pt_jpsi,pt_h,dphi);
			hDendPhiJpsiPtHPtLikeEffWt->Fill(pt_jpsi,pt_h,dphi,wt);
		}
	}

	//unlike-sign side band
	for(int i=0;i<current_nJpsiSide;i++){
		int dau1id = current_jpsiSideDau1Id[i];
		int dau2id = current_jpsiSideDau2Id[i];
		for(int j=0;j<current_nHadron;j++){
			int hid = current_hadronId[j];
			if(dau1id==hid || dau2id==hid) continue;
			double phi_jpsi = current_jpsiSide[i].Phi();
			double pt_jpsi = current_jpsiSide[i].Pt();

			double phi_h = current_hadron[j].Phi();
			double pt_h = current_hadron[j].Pt();
			double eta_h = current_hadron[j].Eta();
			double dphi = phi_jpsi-phi_h;
			double wt = getHadronWt(pt_h,eta_h);
			if(dphi<-PI/2.) dphi+=2.*PI;
			if(dphi>3.*PI/2.) dphi-=2.*PI;
			hDendPhiJpsiPtHPtSide->Fill(pt_jpsi,pt_h,dphi);
			hDendPhiJpsiPtHPtSideEffWt->Fill(pt_jpsi,pt_h,dphi,wt);
		}
	}

}

///////////////////////////////////////////////////////////////////////////////
bool EmcTrackOverlap(pevent* event)
{
	float bfield = event->field;
	Int_t neTracks = event->npTracks;
	for(Int_t i=0;i<neTracks;i++)
	{
		for(Int_t j=i+1;j<neTracks;j++)
		{

			Float_t px1 = event->track_px[i];
			Float_t py1 = event->track_py[i];
			Float_t pz1 = event->track_pz[i];
			TVector3 mom1(0,0,0);
			mom1.SetXYZ(px1,py1,pz1);
			Float_t pt1 = mom1.Perp();
			Float_t p1  = mom1.Mag();
			Float_t phi1 = mom1.Phi();
			Float_t eta1 = mom1.Eta();
			Int_t q1 = (event->track_NHitsFit[i]>0) ? 1 : -1;
			if(eta1>1||eta1<-1)continue;

			Float_t px2 = event->track_px[j];
			Float_t py2 = event->track_py[j];
			Float_t pz2 = event->track_pz[j];
			TVector3 mom2(0,0,0);
			mom2.SetXYZ(px2,py2,pz2);
			Float_t pt2 = mom2.Perp();
			Float_t p2  = mom2.Mag();
			Float_t phi2 = mom2.Phi();
			Float_t eta2 = mom2.Eta();
			Int_t q2 = (event->track_NHitsFit[j]>0) ? 1 : -1;
			if(eta2>1||eta2<-1)continue;

			Char_t emcFlag1 = event->track_emcFlag[i];
			Char_t emcFlag2 = event->track_emcFlag[j];
			if(emcFlag1<=0) continue;
			if(emcFlag2<=0) continue;
			Float_t Dphi = 2*TMath::ASin(0.165/pt1);
			phi1 = phi1 + Dphi*q1;
			Dphi = 2*TMath::ASin(0.165/pt2);
			phi2 = phi2 + Dphi*q2;

			Float_t deltaphi = phi1 - phi2;

			if(deltaphi>=PI)deltaphi = deltaphi - 2*PI;
			if(deltaphi<=-PI)deltaphi = deltaphi + 2*PI;
			Float_t deltaeta = eta1 - eta2;

			Float_t deltaR = TMath::Sqrt(deltaphi*deltaphi+deltaeta*deltaeta);
			if(j==(i+1))
			{
				hDataEmcdeltaEta->Fill(pt1,deltaeta);
				hDataEmcdeltaPhi->Fill(pt1,deltaphi);
				hDataEmcdeltaR->Fill(pt1,deltaR);
			}
			if(deltaphi<0.1&&deltaeta<0.1)
			{
				current_EmcHits[i] = kFALSE;

			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

bool TpcTrackOverlap(pevent* event)
{
	Int_t npTracks = event->npTracks;
	for(Int_t i=0;i<npTracks;i++)
	{
		for(Int_t j=i+1;j<npTracks;j++)
		{
			Float_t px1 = event->track_px[i];
			Float_t py1 = event->track_py[i];
			Float_t pz1 = event->track_pz[i];
			TVector3 mom1(0,0,0);
			mom1.SetXYZ(px1,py1,pz1);
			Float_t pt1 = mom1.Perp();
			Float_t p1  = mom1.Mag();
			Float_t phi1 = mom1.Phi();
			Float_t eta1 = mom1.Eta();
			Int_t q1 = (event->track_NHitsFit[i]>0) ? 1 : -1;
			if(eta1>1||eta1<-1)continue;

			Char_t tofFlag1 = event->track_tofFlag[i];
			Char_t tofFlag2 = event->track_tofFlag[j];
			if(tofFlag1<=0) continue;
			if(tofFlag2<=0) continue;

			Float_t px2 = event->track_px[j];
			Float_t py2 = event->track_py[j];
			Float_t pz2 = event->track_pz[j];
			TVector3 mom2(0,0,0);
			mom2.SetXYZ(px2,py2,pz2);
			Float_t pt2 = mom2.Perp();
			Float_t p2  = mom2.Mag();
			Float_t phi2 = mom2.Phi();
			Float_t eta2 = mom2.Eta();
			Int_t q2 = (event->track_NHitsFit[j]>0) ? 1 : -1;
			if(eta2>=1||eta2<-1)continue;

			Float_t Dphi = 2*TMath::ASin(0.165/pt1);
			phi1 = phi1 + Dphi*q1;
			Dphi = 2*TMath::ASin(0.165/pt2);
			phi2 = phi2 + Dphi*current_emceq[i];

			Float_t deltaphi = phi1 - phi2;

			if(deltaphi>=PI)deltaphi = deltaphi - 2*PI;
			if(deltaphi<=-PI)deltaphi = deltaphi + 2*PI;
			Float_t deltaeta = eta1 - eta2;

			Float_t deltaR = TMath::Sqrt(deltaphi*deltaphi+deltaeta*deltaeta);

			hDataTpcdeltaEta->Fill(pt1,deltaeta);
			hDataTpcdeltaPhi->Fill(pt1,deltaphi);
			hDataTpcdeltaR->Fill(pt1,deltaR);

			if(deltaphi<0.2&&deltaeta<0.2)
			{
				current_TpcHits[i] = kTRUE;
				break;
			}

		}
	}
}

double getHadronWt(double pt, double eta){
	int etabin = floor((eta+1)/0.1);
	if(etabin<0||etabin>=20) return 0.;
	fEff->SetParameters(effPars[etabin]);
	double wt = fEff->Eval(pt);
	if(wt>0) return 1./wt;
	else return 0.;
}
