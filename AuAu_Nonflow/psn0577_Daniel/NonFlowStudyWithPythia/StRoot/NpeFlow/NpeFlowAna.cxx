#include <iostream>
#include <stdio.h>
#include <fstream>

#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TNtuple.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TRandom.h"
#include "TMath.h"
#include "TComplex.h"
#include "TDatime.h"
#include "TRandom3.h"
#include "TGraph.h"


#include "../container/TParticleMc.h"

#include "NpeFlowAna.h"
#include "QandM24.h"

using namespace std;

ClassImp( NpeFlow);

//______________________________________________
NpeFlow::NpeFlow() {

	anaBottom = false;
	anaCharm = false;	    
	useTriggeredData = false;
	hasTrigger = false;

    pT_cut = 0.0;
    eta_cut = 1.0;
    eta_ele_cut = 0.7;

    pt_ele = new TH1F("pt_ele","pt_ele",npt, pt_xbin);
    pt_ele->Sumw2();
    pt_had = new TH1F("pt_had","pt_had",100,0.,10.);
    pt_had->Sumw2();
    pt_K = new TH1F("pt_K","pt_K",npt,0.,pT_max);
    pt_K->Sumw2();
    pt_pi = new TH1F("pt_pi","pt_pi",npt,0.,pT_max);
    pt_pi->Sumw2();
    pt_p = new TH1F("pt_p","pt_p",npt,0.,pT_max);
    pt_p->Sumw2();



    eta_ele = new TH1F("eta_ele","eta_ele",neta,eta_min,eta_max);
    eta_had = new TH1F("eta_had","eta_had",neta,eta_min,eta_max);
    eta_K = new TH1F("eta_K","eta_K",neta,eta_min,eta_max);
    eta_pi = new TH1F("eta_pi","eta_pi",neta,eta_min,eta_max);
    eta_p = new TH1F("eta_p","eta_p",neta,eta_min,eta_max);

    refFlowTrackMult = new TH1F("refFlowTrackMult","Reference Flow Track Mult",22200,0.,200.);
    refFlowTrackMult->Sumw2();

    hEvenCounter = new TH1F("hEvenCounter","hEvenCounter",2,0.,1.);

    // v2 histograms
    char histName[50];

    for (int ibin = 0; ibin < npt; ++ibin) {
    	sprintf(histName, "incEle_M2_2part_pTbin_%d", ibin);
    	incEle_M2_2part[ibin] = new TH1F(histName, histName, 10,-1.,1.);
    	incEle_M2_2part[ibin]->Sumw2();

	}

	refFlow_M2_2part = new TH1F("Ref_M2_2part", "Ref_M2_2part", 10,-1.,1.);
	refFlow_M2_2part->Sumw2();

	
	cout << "pT binning: " << endl;
	float dpt = (pT_max - pT_min)/npt;
	for (int ibin = 0; ibin < npt+1; ++ibin) {
		//pt_xbin[ibin] = ibin*dpt;
		cout << pt_xbin[ibin] << " " << endl;
	}
	
	cout << endl;
}

//______________________________________________
NpeFlow::~NpeFlow() {
}

//____________________________
void NpeFlow::setPtCut(float in) {
	pT_cut = in;
}

//_____________________________
void NpeFlow::setEtaCut(float in) {
	eta_cut = in;
}


//__________________________________________
bool NpeFlow::acceptedTrack(float pT, float eta, int kf) {
	
/*
	if (fabs(eta) < eta_cut && pT > pT_cut)
		return true;
	else
		return false;
*/

	if(pT<0.2) return false; // simple cut off for lowest pT tracks
	float test = mRandGen->Uniform(0., 1.);

	
	switch (kf) {
		case 211:	//pion or electron
		case 11:
			if (test < mPionRecoEff->Eval(pT)) return true;
			else return false;
		case 321:
			if (test < mKaonRecoEff->Eval(pT)) return true;
			else return false;
		case 2212:
			if (test < mProtonRecoEff->Eval(pT)) return true;
			else return false;
	}
}

//__________________________________________
void NpeFlow::showCuts() {
	cout << "Applied cuts:" << endl;
	cout << "\t pTcut: " << pT_cut << endl;
	cout << "\t eta cut: |eta | < " << eta_cut << endl;
}

//__________________________________________
void NpeFlow::setOutFileName(const char* in) {
	outFileName = in;

}

//____________________________
void NpeFlow::calculate(int startFile, int endFile, int maxEvent, char *filelist) {

	char* filename = new char[1000];

	//.. loop over file list
	ifstream file_stream(filelist);

	int totalEvent = 0;

	int ifile = 0;

	TClonesArray* PythiaEvent = 0; //.. must add " = 0", otherwise code crash

	float maxPtRef = 2.;
	float minPtRef = 0.2;
        //float maxPtRef = 100.;	//this cuts represent cuts for Npe-hadron correlation in run5 and run6 from STAR
        //float minPtRef = 0.3;

	// initialize rangom generator for HT trigger efficiency simulations
	TDatime* timeForSeed = new TDatime();
	mRandGen = new TRandom3((UInt_t)timeForSeed->GetTime());

	if(useTriggeredData){
		mHtTriggerEff = new TGraph(mTrgEffFileName);
	}

	// tracking efficiency
	mKaonRecoEff = new TGraph(mKaonRecoEffFileName);
	mPionRecoEff = new TGraph(mPionRecoEffFileName);
	mProtonRecoEff = new TGraph(mProtonRecoEffFileName);


	while (file_stream >> filename) {

		//.. file handling
		if ((totalEvent >= maxEvent && maxEvent != 0) || ifile >= endFile) {
			cout << " totalEvent = " << totalEvent << " maxEvent = "
					<< maxEvent << endl;
			break;
		}

		//file_stream >> filename;

		if (ifile < startFile || !filename) {
			ifile++;
			continue;
		}

		ifile++;

		//..............................................

		TFile f(filename);

		if (f.IsZombie()) {
			cout << filename << " is a Zombie" << endl;
			continue;
		}
		cout << "file#" << ifile << ": " << filename << endl;
		TTree* hf = (TTree*) f.Get("minBiasPp200Triggered");
		if (!hf)
			continue;


		hf->SetBranchAddress("tracks", &PythiaEvent);

		int nevt = hf->GetEntries();

		cout << "Events: " << nevt << endl;

		//.. loop over events ...
		for (int evt = 1; evt < nevt; evt++) {

			if (!(evt % 10000))
				cout << evt << endl;

			Reset();
			PythiaEvent->Clear();

			hf->GetEntry(evt);
			int ntrk = PythiaEvent->GetEntriesFast();


			int ie = 0;
			int ip = 0;
			int ipH = 0;
			int inH = 0;

			TParticleMc* npe;
			TParticleMc* kaon;
			int nKaons = 0;

			for (int trkidx = 0; trkidx < ntrk; trkidx++) {
				TParticleMc* part = (TParticleMc*)PythiaEvent->At(trkidx);

				int kf = abs((int) part->get_KF());
				//int akf = abs((int)part->get_aKF()); //.. source: c,b quark or something else

				float track_pT = part->get_pt();
				float track_eta = part->get_eta();
				float phi = part->get_phi();

				if (!acceptedTrack(track_pT, track_eta, kf))
					continue;

				//.. fill histograms with basic kinematic variables and calc flow vectors

				if(kf==11){
					if(fabs(track_eta)>eta_ele_cut) continue;
					//if(useTriggeredData && track_pT<pTtrigger)continue;
					if(useTriggeredData && !acceptedHtEvent(track_pT))continue;
					hasTrigger = true;
	
					if(isHeavyMesonProd(part->get_pKF())){

						
						pt_ele->Fill(track_pT);
						eta_ele->Fill(track_eta);

						int ptbin = find_pt_bin(track_pT);

						if(ptbin>0){
							inc_ele_cos_2phi_cent_pT_bins[ptbin] += cos(2.*phi);
							inc_ele_sin_2phi_cent_pT_bins[ptbin] += sin(2.*phi);
							inc_ele_mult_pT_bins[ptbin]++;
						}
					}
				} else if(kf==211 || kf==321 || kf==2212){
				//} else if(kf==2212){	// use only protons
					if(track_pT>minPtRef && track_pT<maxPtRef){
					    cos2phi_RefFlow += cos(2.*phi);
					    sin2phi_RefFlow += sin(2.*phi);
					    multRefFlow++;
					}
				}

				switch (kf) {

				case 211:
					pt_pi->Fill(track_pT);
					eta_pi->Fill(track_eta);
					pt_had->Fill(track_pT);
					eta_had->Fill(track_eta);
					break;
				case 321:
					pt_K->Fill(track_pT);
					eta_K->Fill(track_eta);
					pt_had->Fill(track_pT);
					eta_had->Fill(track_eta);

					break;
				case 2212:
					pt_p->Fill(track_pT);
					eta_p->Fill(track_eta);
					pt_had->Fill(track_pT);
					eta_had->Fill(track_eta);
					break;
				default:
					break;
				}
			}

			if(useTriggeredData && !hasTrigger) continue;
			calcRefFlow_M2_2Part();
			calcEleMoments();
		}

		f.Close();
	}

	WriteHist();
}

//____________________________
void NpeFlow::fillPtSpectra(int startFile, int endFile, int maxEvent, char *filelist) {

	char* filename = new char[1000];

	//.. loop over file list
	ifstream file_stream(filelist);

	int totalEvent = 0;

	int ifile = 0;

	TClonesArray* PythiaEvent = 0; //.. must add " = 0", otherwise code crash

	// initialize rangom generator for HT trigger efficiency simulations
	TDatime* timeForSeed = new TDatime();
	mRandGen = new TRandom3((UInt_t)timeForSeed->GetTime());

	if(useTriggeredData){
		mHtTriggerEff = new TGraph(mTrgEffFileName);
	}

	// tracking efficiency
	mKaonRecoEff = new TGraph(mKaonRecoEffFileName);
	mPionRecoEff = new TGraph(mPionRecoEffFileName);
	mProtonRecoEff = new TGraph(mProtonRecoEffFileName);


	while (file_stream >> filename) {

		//.. file handling
		if ((totalEvent >= maxEvent && maxEvent != 0) || ifile >= endFile) {
			cout << " totalEvent = " << totalEvent << " maxEvent = "
					<< maxEvent << endl;
			break;
		}

		//file_stream >> filename;

		if (ifile < startFile || !filename) {
			ifile++;
			continue;
		}

		ifile++;

		//..............................................

		TFile f(filename);

		if (f.IsZombie()) {
			cout << filename << " is a Zombie" << endl;
			continue;
		}
		cout << "file#" << ifile << ": " << filename << endl;
		TTree* hf = (TTree*) f.Get("minBiasPp200Triggered");
		if (!hf)
			continue;


		hf->SetBranchAddress("tracks", &PythiaEvent);

		int nevt = hf->GetEntries();

		cout << "Events: " << nevt << endl;

		//.. loop over events ...
		for (int evt = 1; evt < nevt; evt++) {

			if (!(evt % 10000))
				cout << evt << endl;

			Reset();
			PythiaEvent->Clear();

			hf->GetEntry(evt);
			int ntrk = PythiaEvent->GetEntriesFast();


			int ie = 0;
			int ip = 0;
			int ipH = 0;
			int inH = 0;

			TParticleMc* npe;
			TParticleMc* kaon;
			int nKaons = 0;


			// first loop: check if has HT trigger
			for (int trkidx = 0; trkidx < ntrk; trkidx++) {
				TParticleMc* part = (TParticleMc*)PythiaEvent->At(trkidx);

				int kf = abs((int) part->get_KF());
				//int akf = abs((int)part->get_aKF()); //.. source: c,b quark or something else

				float track_pT = part->get_pt();
				float track_eta = part->get_eta();
				float phi = part->get_phi();

				if (!acceptedTrack(track_pT, track_eta, kf))
					continue;

				//.. fill histograms with basic kinematic variables and calc flow vectors

				if(kf==11){
					if(fabs(track_eta)>eta_ele_cut) continue;
					//if(useTriggeredData && track_pT<pTtrigger)continue;
					if(useTriggeredData && !acceptedHtEvent(track_pT))continue;
					hasTrigger = true;
				} 
			}
			

			if(hasTrigger){
				hEvenCounter->Fill(1);
				for (int trkidx = 0; trkidx < ntrk; trkidx++) {
					TParticleMc* part = (TParticleMc*)PythiaEvent->At(trkidx);
		
					int kf = abs((int) part->get_KF());
					//int akf = abs((int)part->get_aKF()); //.. source: c,b quark or something else
		
					float track_pT = part->get_pt();
					float track_eta = part->get_eta();
					float phi = part->get_phi();
		
					if (!acceptedTrack(track_pT, track_eta, kf))
						continue;
		
					//.. fill histograms with basic kinematic variables and calc flow vectors
					if(kf==211 || kf==321 || kf==2212){
						pt_had->Fill(track_pT);
						eta_had->Fill(track_eta);
					}
				}
			}	
		}

		f.Close();
	}

	WriteHist();
}

//______________________________________________
void NpeFlow::WriteHist() {

	//.. prepare output file ...

	char* resultfile = new char[100];
	sprintf(resultfile, "%s%s%s", "ana_",outFileName,".root");

	cout << "resultfile: " << resultfile << endl;
	TFile *result = new TFile(resultfile, "RECREATE");
	result->mkdir("QA_hist");
	result->cd("QA_hist");

	pt_ele->Write();
	pt_had->Write();
	pt_K->Write();
	pt_pi->Write();
	pt_p->Write();
	eta_ele->Write();
	eta_had->Write();
	eta_K->Write();
	eta_pi->Write();
	eta_p->Write();
        refFlowTrackMult->Write();
        hEvenCounter->Write();
	result->cd();
	result->mkdir("inc_ele_moments");
	result->cd("inc_ele_moments");

	for(int j = 0; j< npt; j++){
		incEle_M2_2part[j]->Write();
	}

	result->cd();
	result->mkdir("ref_flow_moments");
	result->cd("ref_flow_moments");
	refFlow_M2_2part->Write();
	result->cd();
	//.. Reference flow
}

void NpeFlow::Reset(){

    hasTrigger = false;

	//.. moments for reference flow
    cos2phi_RefFlow = 0.0;
    sin2phi_RefFlow = 0.0;
    multRefFlow = 0.0;

    //.. moments for inclusive electrons
    for (int ibin = 0; ibin < npt; ++ibin) {
        inc_ele_cos_2phi_cent_pT_bins[ibin] = 0.0;
        inc_ele_sin_2phi_cent_pT_bins[ibin] = 0.0;
        inc_ele_mult_pT_bins[ibin] = 0.0;
	}
}

int NpeFlow::find_pt_bin(float pT)
{
	for (int bin = 0; bin < npt; ++bin) {
		if(pT< pt_xbin[bin+1]) return bin;
	}
	return -1;
}

void NpeFlow::calcRefFlow_M2_2Part()
{

    int nb = multRefFlow;
    double Qcosb = cos2phi_RefFlow;
    double Qsinb = sin2phi_RefFlow;

    double m2 = Moment2(nb, Qcosb, Qsinb);
    double Npair = 1.0*nb*(nb-1);

    refFlow_M2_2part->Fill(m2,Npair);
    refFlowTrackMult->Fill(multRefFlow);
}

void NpeFlow::calcEleMoments()
{

    //.. calculate the moments
    for (int binX = 0; binX < npt; binX++) {
    	if (inc_ele_mult_pT_bins[binX] > 0) {

                //.. calculate differential flow with 2-part cumumlants
            	int na = inc_ele_mult_pT_bins[binX];
                double Qcosa = inc_ele_cos_2phi_cent_pT_bins[binX];
                double Qsina = inc_ele_sin_2phi_cent_pT_bins[binX];

                int nb = multRefFlow;
                double Qcosb = cos2phi_RefFlow;
                double Qsinb = sin2phi_RefFlow;

                double m2_2part = Moment2(na, Qcosa, Qsina, nb, Qcosb, Qsinb);
                double Npair = 1.0*na*nb;
                incEle_M2_2part[binX]->Fill(m2_2part,Npair);
        }
    }
}

bool NpeFlow::isHeavyMesonProd(int kf){

	const int Ncharm = 18;
	const int Nbottom = 24;

	int charmedMesonPGD_ID[Ncharm] = {411,421,10411,10421,413,423,10413,10423,20413,20423,415,425,431,10431,433,10433,20433,435};
    int charmedBottomPGD_ID[Nbottom] = {511,521,10511,10521,513,523,10513,10523,20513,20523, 515, 525, 531, 10531, 533, 10533,
                                                                    20533, 535, 541, 10541, 543, 10543, 20543, 545};

    if (anaCharm) {
		for (int i = 0; i < Ncharm; i++)
			if (kf == charmedMesonPGD_ID[i])
				return true;
	}

    if (anaBottom) {
		for (int i = 0; i < Nbottom; i++)
			if (kf == charmedBottomPGD_ID[i])
				return true;
	}

     return false;
}


void NpeFlow::setAnaBottom(bool in){
	this->anaBottom = in;
}

void NpeFlow::setAnaCharm(bool in){
	this->anaCharm = in;
}

bool NpeFlow::getAnaBottom(){
	return anaBottom;
}
bool NpeFlow::getAnaCharm(){
	return anaCharm;
}

void NpeFlow::setTriggerPt(float in){
	pTtrigger = in;
	useTriggeredData = true;
}
 

void NpeFlow::setHtTrigEffFileName(const char* in){
	mTrgEffFileName = in;
}

void NpeFlow::setKaonRecoEffFileName(const char* in){
	mKaonRecoEffFileName = in;
}

void NpeFlow::setPionRecoEffFileName(const char* in){
	mPionRecoEffFileName = in;
}

void NpeFlow::setProtonRecoEffFileName(const char* in){
	mProtonRecoEffFileName = in;
}


bool NpeFlow::acceptedHtEvent(float elePt){

	if(elePt<pTtrigger) return false; // simple cut off for a range when there is no data, i.e. ussualy below 2 GeV to avoid negative trigger efficienccy from extrapolation from higher pT
	float test = mRandGen->Uniform(0., 1.);
	if (test < mHtTriggerEff->Eval(elePt,0,"S")) return true;
	else return false;
}
