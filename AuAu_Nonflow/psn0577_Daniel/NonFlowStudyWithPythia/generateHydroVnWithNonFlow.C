#include <TF1.h>
#include <TF2.h>

#include <TRandom3.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TStopwatch.h>
#include <TCanvas.h>
#include <TDirectory.h>
#include <TSystem.h>
#include <TTree.h>
#include "StRoot/container/TParticleMc.h"
#include <TClonesArray.h>
#include <TFile.h>

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <string>
#include <TString.h>
#include <TDatime.h>
#include <exception>

using namespace std;

float phiTo0TwoPi(float phi);
void calcAzimuthalCorrelation(TObjArray* traks_forward,TObjArray *tracks_backward,TH3F *PtForVsPtBackVsdNdDeltaPhi, TH2F* dNdDeltaPhidNdDeltaEta);
float findPhiOfDijetLeadingPart(TClonesArray *pythia_traks);
int findEtaBin(double dEta, double etaMin, double etaMax);


bool isChargedParticle(int PdgId);
bool isResonanceDaughter(int PartPdgId);

void generateHydroVnWithNonFlow(TString filelist = "short.list", TString outfileName = "output", bool genHydroFlow = true, bool addPythia = true, bool addFlowToPythia = false, bool calcAzimuthCorr = false){

    gSystem->Load("container.so");

    TString resultfile("vnn_");
    resultfile.Append(outfileName);
    resultfile.Append(".root");
    
    float v2_factor = 0.1; //.. used in hydro flow: v_2(pT) = v2_factor*pT
    float v3_factor = 0.1; //.. flow: v_3(pT) = v3_factor*pT


    cout << "Outfile: " << resultfile << endl;

    const int NPtBins = 20;
    const int NEtaBins = 20;

    double dEta = 0.1;
    double etaMin = -1.;
    double etaMax = 1.;


    double PtMax = 10;
    double dpT = PtMax/NPtBins;
    cout << "NPtBins: " << NPtBins << " PtMax: " << PtMax << " dpT: " <<  dpT << endl;

    //exponentila fit to Phenix Au+Au data, 30-40% Au+Au
    TF1* ptDist = new TF1("ptDist","[0]*x*exp(-x/[1])",0,PtMax);
    ptDist->SetParameter(0,2.39840e+02);
    ptDist->SetParameter(1,2.30029e-01);
	
/*
    TF1* ptDist = new TF1("ptDist","[0]*x*TMath::Power(1+ x*x/([1]*[1]),[2])",0,PtMax);
    ptDist->SetParameter(0,1.07996e+02);
    ptDist->SetParameter(1,8.97031e-01);
    ptDist->SetParameter(2,-3.88074e+00);
*/
	//.. functions to generate particles with given flow, eta and pT
	//.. 0< pT < 10
	//.. 0.5<|eta|<1
	//.. v2(pT) = 0.1*pT

	double pi_2 = 2.*TMath::Pi();

	TDatime* timeForSeed = new TDatime();

	TRandom3 *randGen = new TRandom3((UInt_t)timeForSeed->GetTime());

	//.. Elliptic flow distribution with assumption that v2(pT) = 0.1*pT, x = phi - Phi_{RP}, y - pT
	//.. Elliptic flow distribution with assumption that v2(pT) = 0.1*pT, x = phi - Phi_{RP}, y - pT
	TF2* v2cosDeltaPhiVspT = new TF2("v2cosDeltaPhiVspT","1+2*[0]*y*cos(2*x)",-pi_2,pi_2,0,PtMax);
	v2cosDeltaPhiVspT->SetParameter(0,v2_factor);
	TF2* v2v3cosDeltaPhiVspT = new TF2("v2v3cosDeltaPhiVspT","1+2*([0]*y*cos(2*x)+[1]*y*cos(3*x))",-pi_2,pi_2,0,PtMax);
	v2v3cosDeltaPhiVspT->SetParameter(0,v2_factor);
	v2v3cosDeltaPhiVspT->SetParameter(1,v3_factor);

	//.. Flow imposed on Pythia
	float v2_factor_Pythia = 0.3;
	float v3_factor_Pythia = 0.1;

	TF2* Pythia_v2v3cosDeltaPhiVspT = new TF2("Pythia_v2v3cosDeltaPhiVspT","1+2*([0]*y*cos(2*x)+[1]*y*cos(3*x))",-pi_2,pi_2,0,PtMax);
	Pythia_v2v3cosDeltaPhiVspT->SetParameter(0,v2_factor_Pythia);
	Pythia_v2v3cosDeltaPhiVspT->SetParameter(1,v3_factor_Pythia);

	TF1* Pythia_v2cosDeltaPhi = new TF1("Pythia_v2cosDeltaPhi","1+2*([0]*cos(2*x))",-pi_2,pi_2);
	Pythia_v2cosDeltaPhi->SetParameter(0,v2_factor_Pythia);

	//..  function used in random number generation, max na min value of v2cosDeltaPhiVspT for given pT
	TF1* maxCosDeltaPhi = new TF1("maxCosDeltaPhi","1+2*[0]*x+2*[1]*x",0,PtMax);
	maxCosDeltaPhi->SetParameter(0,v2_factor);
	maxCosDeltaPhi->SetParameter(1,v3_factor);

	//..  function used in random number generation, max na min value of v2cosDeltaPhiVspT for given pT
	TF1* Pythia_maxCosDeltaPhi = new TF1("maxCosDeltaPhi","1+2*[0]",0,PtMax);
	Pythia_maxCosDeltaPhi->SetParameter(0,v2_factor_Pythia);

	TH3F* PtForVsPtBackVsV11PairAvg = new TH3F("PtForVsPtBackVsV11PairAvg","pT_{For} Vs pT_{Back} vs V_{11}",NPtBins,0,PtMax,NPtBins,0,PtMax,220,-1.1,1.1);
	PtForVsPtBackVsV11PairAvg->SetYTitle("p_{T}^{Forward} [GeV]");
	PtForVsPtBackVsV11PairAvg->SetXTitle("p_{T}^{Backward} (Reference) [GeV]");

	TH3F* PtForVsPtBackVsV22PairAvg = new TH3F("PtForVsPtBackVsV22PairAvg","pT_{For} Vs pT_{Back} vs V_{22}",NPtBins,0,PtMax,NPtBins,0,PtMax,220,-1.1,1.1);
	PtForVsPtBackVsV22PairAvg->SetYTitle("p_{T}^{Forward} [GeV]");
	PtForVsPtBackVsV22PairAvg->SetXTitle("p_{T}^{Backward} (Reference) [GeV]");

	TH3F* PtForVsPtBackVsV22 = new TH3F("PtForVsPtBackVsV22","pT_{For} Vs pT_{Back} vs V_{22}",NPtBins,0,PtMax,NPtBins,0,PtMax,220,-1.1,1.1);
	PtForVsPtBackVsV22->SetYTitle("p_{T}^{Forward} [GeV]");
	PtForVsPtBackVsV22->SetXTitle("p_{T}^{Backward} (Reference) [GeV]");


	TH3F* PtForVsPtBackVsV33PairAvg = new TH3F("PtForVsPtBackVsV33PairAvg","pT_{For} Vs pT_{Back} vs V_{33}",NPtBins,0,PtMax,NPtBins,0,PtMax,220,-1.1,1.1);
	PtForVsPtBackVsV33PairAvg->SetYTitle("p_{T}^{Forward} [GeV]");
	PtForVsPtBackVsV33PairAvg->SetXTitle("p_{T}^{Backward} (Reference) [GeV]");

	TH3F* PtForVsPtBackVsV33 = new TH3F("PtForVsPtBackVsV33","pT_{For} Vs pT_{Back} vs V_{33}",NPtBins,0,PtMax,NPtBins,0,PtMax,220,-1.1,1.1);
	PtForVsPtBackVsV33->SetYTitle("p_{T}^{Forward} [GeV]");
	PtForVsPtBackVsV33->SetXTitle("p_{T}^{Backward} (Reference) [GeV]");

	TH3F* PtForVsPtBackVsV44PairAvg = new TH3F("PtForVsPtBackVsV44PairAvg","pT_{For} Vs pT_{Back} vs V_{44}",NPtBins,0,PtMax,NPtBins,0,PtMax,220,-1.1,1.1);
	PtForVsPtBackVsV44PairAvg->SetYTitle("p_{T}^{Forward} [GeV]");
	PtForVsPtBackVsV44PairAvg->SetXTitle("p_{T}^{Backward} (Reference) [GeV]");

	TH3F* PtForVsPtBackVsV55PairAvg = new TH3F("PtForVsPtBackVsV55PairAvg","pT_{For} Vs pT_{Back} vs V_{55}",NPtBins,0,PtMax,NPtBins,0,PtMax,220,-1.1,1.1);
	PtForVsPtBackVsV55PairAvg->SetYTitle("p_{T}^{Forward} [GeV]");
	PtForVsPtBackVsV55PairAvg->SetXTitle("p_{T}^{Backward} (Reference) [GeV]");


	TH1D* pythia_phi = new TH1D("pythia_phi","dN/d#psi",200,-pi_2,pi_2);
	pythia_phi->SetYTitle("#phi");

	TH1D* pythia_dphi = new TH1D("pythia_dphi","dN/d#Delta#psi",200,-pi_2,pi_2);
	pythia_dphi->SetYTitle("#Delta #phi");

	TH1D* toymodel_phi = new TH1D("toymodel_phi","dN/d#psi",200,-pi_2,pi_2);
	toymodel_phi->SetYTitle("#phi");

	TH1D* toymodel_RP = new TH1D("toymodel_RP","dN/d#Psi",200,-pi_2,pi_2);
	toymodel_RP->SetYTitle("#phi");

	TH3F* PtForVsPtBackVsdNdDeltaPhi = new TH3F("PtForVsPtBackVsdNdDeltaPhi","pT_{For} Vs pT_{Back} vs dN/d#Delta#phi",NPtBins,0,PtMax,NPtBins,0,PtMax,50,0,TMath::TwoPi());
	PtForVsPtBackVsdNdDeltaPhi->SetYTitle("p_{T}^{Forward} [GeV]");
	PtForVsPtBackVsdNdDeltaPhi->SetXTitle("p_{T}^{Backward} (Reference) [GeV]");
	PtForVsPtBackVsdNdDeltaPhi->SetYTitle("#Delta #phi");

	TH2F* dNdDeltaPhidNdDeltaEta = new TH2F("dNdDeltaPhidNdDeltaEta"," dN/d#Delta#phi vs d#Delta#eta",50,0,TMath::TwoPi(),25,0,2.5);
	dNdDeltaPhidNdDeltaEta->SetYTitle("#Delta #phi");
	dNdDeltaPhidNdDeltaEta->SetXTitle("#Delta #phi");

	/*
	 * the reference multiplicity (|eta|<0.5) brackets for Au+Au run 10 for 20-45% central events are 93 - 266
	 * similar multiplicity should be observed in 0.5<|eta|<1,
	 * therefore I assume that for forward and backward rapidity I should have 46 - 133 particles
	 * I generate this numbers independently for each part of TPC
	 */

	int upMult = 10*133; //133;
	int lowMult = 10*46; //46;
	int multForward = 0, multBackward = 0;

	double RP = 0, dphi = 0.;
	double test = 0;
	double pT = 0., phi = 0., phi2 = 0., phi3 = 0., phi4 = 0., phi5 = 0., v1 = 0., v2 = 0., v3 = 0., v4 = 0.,v5 = 0.;
	int pTbin = 0;

	double cos1phiVspT_forward[NPtBins];
	double sin1phiVspT_forward [NPtBins];
	double cos1phiVspT_backward[NPtBins];
	double sin1phiVspT_backward[NPtBins];

	double cos2phiVspT_forward[NPtBins];
	double sin2phiVspT_forward [NPtBins];
	double cos2phiVspT_backward[NPtBins];
	double sin2phiVspT_backward[NPtBins];

	double cos3phiVspT_forward[NPtBins];
	double sin3phiVspT_forward [NPtBins];
	double cos3phiVspT_backward[NPtBins];
	double sin3phiVspT_backward[NPtBins];

	double cos4phiVspT_forward[NPtBins];
	double sin4phiVspT_forward [NPtBins];
	double cos4phiVspT_backward[NPtBins];
	double sin4phiVspT_backward[NPtBins];

	double cos5phiVspT_forward[NPtBins];
	double sin5phiVspT_forward [NPtBins];
	double cos5phiVspT_backward[NPtBins];
	double sin5phiVspT_backward[NPtBins];

	double cos2phiVsEta[NEtaBins];
	double sin2phiVsEta[NEtaBins];

	long mult_Eta[NPtBins];

	long mult_forward[NPtBins];
	long mult_backward [NPtBins];

	TH1D* dNpT_forward = new TH1D("dNpT_forward","dNpT_forward",NPtBins,0,PtMax);
	dNpT_forward->SetXTitle("p_{T} [GeV]");
	TH1D* dNpT_backward = new TH1D("dNpT_backward","dNpT_backward",NPtBins,0,PtMax);
	dNpT_backward->SetXTitle("p_{T} [GeV]");

	TH1D* dNpT_forward_pythia = new TH1D("dNpT_forward_pythia","dNpT_forward_pythia",NPtBins,0,PtMax);
	dNpT_forward_pythia->SetXTitle("p_{T} [GeV]");	

	TH1D* dNpT_backward_pythia = new TH1D("dNpT_backward_pythia","dNpT_backward_pythia",NPtBins,0,PtMax);
	dNpT_backward_pythia->SetXTitle("p_{T} [GeV]");
	
	TH2F* v2VsPt = new TH2F("v2VsPtHydro","Hydro v2 vs pT",100,0,PtMax,100,-pi_2,pi_2);
	v2VsPt->SetXTitle("p_{T} [GeV]");
	v2VsPt->SetYTitle("#phi -#Phi_{RP})");

	TH1D* eventCounter = new TH1D("eventCounter","eventCounter",2,0,2);
	TH2F* eventCounterPt = new TH2F("eventCounterPt","Event Counter for each v2(pt,pt)",NPtBins,0,PtMax,NPtBins,0,PtMax);
	TH2F* pairCounterPt = new TH2F("pairCounterPt","Pair Counter for each v2(pt,pt)",NPtBins,0,PtMax,NPtBins,0,PtMax);


	PtForVsPtBackVsV11PairAvg->Sumw2();
	PtForVsPtBackVsV22PairAvg->Sumw2();
    	PtForVsPtBackVsV22->Sumw2();
    	PtForVsPtBackVsV33PairAvg->Sumw2();
    	PtForVsPtBackVsV33->Sumw2();
    	PtForVsPtBackVsV44PairAvg->Sumw2();
    	PtForVsPtBackVsV55PairAvg->Sumw2();

	cout << "File list read " << endl;

	TStopwatch timer;
	timer.Start();

	//.. read list of Pythia files
 	ifstream file_stream(filelist);


	string filename;
	int ifile = 0;

	TClonesArray *pythia_traks = new TClonesArray("TParticleMc");
	TObjArray *traks_forward = new TObjArray(20);
	TObjArray *tracks_backward = new TObjArray(20);
	
	TFile* f;
	TTree *nt_pythia_tracks; 

	while (file_stream >> filename) {

		ifile++;
		cout << "file  = " << ifile << " name = " << filename << endl;

		f = new TFile(filename.c_str());

		nt_pythia_tracks = (TTree*) f->Get("minBiasPp200Triggered");
	//	nt_pythia_tracks = (TTree*) f->Get("minBiasEe200MinBias");


		nt_pythia_tracks->SetBranchAddress("tracks",&pythia_traks);

        	int Nevents = (int)nt_pythia_tracks->GetEntries();

		//.. for each event:
		for (int ievt = 0; ievt < Nevents; ievt++) {

			//.. generate reaction plane with random orientation
			RP = randGen->Uniform(0, pi_2);
			toymodel_RP->Fill(RP);

			if(!(ievt%10000))cout  << ievt << endl;

			//.. fill histograms for pythia events
			eventCounter->Fill(1);

			pythia_traks->Clear();
			if(calcAzimuthCorr){
				traks_forward->Clear();
				tracks_backward->Clear();
			}

			for(int i =0; i< NPtBins; i++){
				cos1phiVspT_forward[i] = 0.;
				sin1phiVspT_forward[i] = 0.;
				cos1phiVspT_backward[i] = 0.;
				sin1phiVspT_backward[i] = 0.;

				cos2phiVspT_forward[i] = 0.;
				sin2phiVspT_forward[i] = 0.;
				cos2phiVspT_backward[i] = 0.;
				sin2phiVspT_backward[i] = 0.;

				cos3phiVspT_forward[i] = 0.;
				sin3phiVspT_forward[i] = 0.;
				cos3phiVspT_backward[i] = 0.;
				sin3phiVspT_backward[i] = 0.;

				cos4phiVspT_forward[i] = 0.;
				sin4phiVspT_forward[i] = 0.;
				cos4phiVspT_backward[i] = 0.;
				sin4phiVspT_backward[i] = 0.;

				cos5phiVspT_forward[i] = 0.;
				sin5phiVspT_forward[i] = 0.;
				cos5phiVspT_backward[i] = 0.;
				sin5phiVspT_backward[i] = 0.;

				mult_forward[i] = 0;
				mult_backward[i] = 0;
			}

			for(int i =0; i< NEtaBins; i++){
				double cos2phiVsEta[NEtaBins];
				double sin2phiVsEta[NEtaBins];

				long mult_Eta[NPtBins];
			}

			if(addPythia){
				nt_pythia_tracks->GetEntry(ievt);
							
				Int_t nParticles = pythia_traks->GetEntriesFast();
				float phiShift = 0;
				if(addFlowToPythia){
					
					float jet_phi =  findPhiOfDijetLeadingPart(pythia_traks);
					
					bool accepted = false;
					while(!accepted){
						dphi = randGen->Uniform(0, TMath::TwoPi());
						float pt_rot = 3.;	//.. my assumption
						test = randGen->Uniform(0, Pythia_maxCosDeltaPhi->Eval(pt_rot));
	
 			 			if(test < Pythia_v2cosDeltaPhi->Eval(dphi)){
							accepted = true;
							phiShift = dphi - jet_phi + RP; //.. subtract jet anizmuthal angle and add flow modulation 
							pythia_dphi->Fill(dphi);	// sanity check
						}
					}
					
				}

				for (Int_t i = 0; i < nParticles; i++) {
					TParticleMc *part = (TParticleMc*) pythia_traks->At(i);
	
					if (fabs(part->get_eta()) < 1.) {
						//.. no eta gap
						if(!isChargedParticle(part->get_KF()))continue;
						//if(isResonanceDaughter(part->get_pKF()))continue;

						phi = part->get_phi() + phiShift;
						/*
						if (part->get_px() == 0.0 && part->get_py() == 0.0)
							phi = 0.;
						else
							phi = TMath::ATan2(part->get_py(), part->get_px())
									+ TMath::Pi(); //.. to bring phi in 0, 2Pi range
						*/
						//.. add hydrodynamic flow to Pythia particles
						
	
	
						phi2 = 2. * phi;
						phi3 = 3. * phi;
						phi4 = 4. * phi;
						phi5 = 5. * phi;

						pythia_phi->Fill(phi);
						pTbin = (int)(part->get_pt()/dpT);
						if(pTbin >= NPtBins)continue;
							
						if (part->get_eta() > 0.5) {

							if(calcAzimuthCorr)
								traks_forward->Add(part); 
							cos1phiVspT_forward[pTbin] += cos(phi);
							sin1phiVspT_forward[pTbin] += sin(phi);

							cos2phiVspT_forward[pTbin] += cos(phi2);
							sin2phiVspT_forward[pTbin] += sin(phi2);

							cos3phiVspT_forward[pTbin] += cos(phi3);
							sin3phiVspT_forward[pTbin] += sin(phi3);

							cos4phiVspT_forward[pTbin] += cos(phi4);
							sin4phiVspT_forward[pTbin] += sin(phi4);

							cos5phiVspT_forward[pTbin] += cos(phi5);
							sin5phiVspT_forward[pTbin] += sin(phi5);

							dNpT_forward_pythia->Fill(part->get_pt());
							mult_forward[pTbin]++;
						}
						
						if (part->get_eta() < -0.5) {
						
							if(calcAzimuthCorr)
								tracks_backward->Add(part); 
							cos1phiVspT_backward[pTbin] += cos(phi);
							sin1phiVspT_backward[pTbin] += sin(phi);

							cos2phiVspT_backward[pTbin] += cos(phi2);
							sin2phiVspT_backward[pTbin] += sin(phi2);

							cos3phiVspT_backward[pTbin] += cos(phi3);
							sin3phiVspT_backward[pTbin] += sin(phi3);

							cos4phiVspT_backward[pTbin] += cos(phi4);
							sin4phiVspT_backward[pTbin] += sin(phi4);

							cos5phiVspT_backward[pTbin] += cos(phi5);
							sin5phiVspT_backward[pTbin] += sin(phi5);

							dNpT_backward_pythia->Fill(part->get_pt());
							mult_backward[pTbin]++;
						}
	
					}	
	
				}
			}
			
			if(genHydroFlow){
				//.. generate particles with hydro flow
				multForward = (int) randGen->Uniform(lowMult, upMult);
				multBackward = (int) randGen->Uniform(lowMult, upMult);
	
				/*
				* algorithm:
				* generate pT (assumption: eta and pT are independent so eta does not matter)
				* generate phi for a given v2(pT)
				* add to the list
				*/
				int nForward = 0;
				while (nForward < multForward) {
					pT = ptDist->GetRandom();
					pTbin = (int)(pT/dpT);
					if(pTbin >= NPtBins)continue;
	
					//..  eta = randGen->Uniform(-1,-0.5); //this does not matter
	
					phi = randGen->Uniform(0, pi_2);
					test = randGen->Uniform(0, maxCosDeltaPhi->Eval(pT));
					dphi = phi - RP;
					if (dphi < 0)dphi += pi_2;
					phi2 = 2. * phi;
					phi3 = 3. * phi;
					phi4 = 4. * phi;
					phi5 = 5. * phi;

				toymodel_phi->Fill(phi);
	
				if (test < v2v3cosDeltaPhiVspT->Eval(dphi, pT)) {
					v2VsPt->Fill(pT, dphi);

						cos1phiVspT_forward[pTbin] += cos(phi);
						sin1phiVspT_forward[pTbin] += sin(phi);

						cos2phiVspT_forward[pTbin] += cos(phi2);
						sin2phiVspT_forward[pTbin] += sin(phi2);

						cos3phiVspT_forward[pTbin] += cos(phi3);
						sin3phiVspT_forward[pTbin] += sin(phi3);

						cos4phiVspT_forward[pTbin] += cos(phi4);
						sin4phiVspT_forward[pTbin] += sin(phi4);

						cos5phiVspT_forward[pTbin] += cos(phi5);
						sin5phiVspT_forward[pTbin] += sin(phi5);

						dNpT_forward->Fill(pT);			
						mult_forward[pTbin]++;
						nForward++;
					}
				}
				
				int nBackward = 0;
				while (nBackward < multBackward) {
					pT = ptDist->GetRandom();
					pTbin = (int)(pT/dpT);
					if(pTbin >= NPtBins)continue;
	
					phi = randGen->Uniform(0, pi_2);
					test = randGen->Uniform(0, maxCosDeltaPhi->Eval(pT));
					dphi = phi - RP;
					if (dphi < 0)dphi += pi_2;
					phi2 = 2. * phi;
					phi3 = 3. * phi;
					phi4 = 4. * phi;
					phi5 = 5. * phi;
	
					toymodel_phi->Fill(phi);
	
					if (test < v2v3cosDeltaPhiVspT->Eval(dphi, pT)) {
						/* if(calcAzimuthCorr){
							TParticleMc *part_back = new  TParticleMc();
							part_back->S
							tracks_backward->Add(part);
						} */
						v2VsPt->Fill(pT, dphi);
						cos1phiVspT_backward[pTbin] += cos(phi);
						sin1phiVspT_backward[pTbin] += sin(phi);

						cos2phiVspT_backward[pTbin] += cos(phi2);
						sin2phiVspT_backward[pTbin] += sin(phi2);

						cos3phiVspT_backward[pTbin] += cos(phi3);
						sin3phiVspT_backward[pTbin] += sin(phi3);

						cos4phiVspT_backward[pTbin] += cos(phi4);
						sin4phiVspT_backward[pTbin] += sin(phi4);

						cos5phiVspT_backward[pTbin] += cos(phi5);
						sin5phiVspT_backward[pTbin] += sin(phi5);

						dNpT_backward->Fill(pT);
						mult_backward[pTbin]++;
						nBackward++;
					}
				}
			}

			if(calcAzimuthCorr)
				calcAzimuthalCorrelation(traks_forward,tracks_backward,PtForVsPtBackVsdNdDeltaPhi,dNdDeltaPhidNdDeltaEta);
		

			//.. Calculate and store v2
			
			for(int i = 0; i< NPtBins; i++)
				for(int j = 0; j< NPtBins; j++){
				int ntrk_forward = mult_forward[i];
				int ntrk_backward = mult_backward[j];
				if(ntrk_forward > 0 && ntrk_backward > 0){

					float N = ntrk_forward*ntrk_backward;

					pairCounterPt->SetBinContent(j+1,i+1,pairCounterPt->GetBinContent(j+1,i+1)+N);

					float pTRef = pairCounterPt->GetXaxis()->GetBinCenter(j+1);
					float pTInt = pairCounterPt->GetYaxis()->GetBinCenter(i+1);

					v1 = cos1phiVspT_backward[j]*cos1phiVspT_forward[i] +
				     	sin1phiVspT_backward[j]*sin1phiVspT_forward[i];

					v2 = cos2phiVspT_backward[j]*cos2phiVspT_forward[i] +
				     	sin2phiVspT_backward[j]*sin2phiVspT_forward[i];

					v3 = cos3phiVspT_backward[j]*cos3phiVspT_forward[i] +
				     	sin3phiVspT_backward[j]*sin3phiVspT_forward[i];

					v4 = cos4phiVspT_backward[j]*cos4phiVspT_forward[i] +
				     	sin4phiVspT_backward[j]*sin4phiVspT_forward[i];

					v5 = cos5phiVspT_backward[j]*cos5phiVspT_forward[i] +
				     	sin5phiVspT_backward[j]*sin5phiVspT_forward[i];

					//.. accumulate v2 and number of events ()
					eventCounterPt->SetBinContent(j+1,i+1,eventCounterPt->GetBinContent(j+1,i+1)+1);

					v1 = v1/N;
					PtForVsPtBackVsV11PairAvg->Fill(pTRef,pTInt,v1);

					v2 = v2/N;
					PtForVsPtBackVsV22PairAvg->Fill(pTRef,pTInt,v2);
					PtForVsPtBackVsV22->Fill(pTRef,pTInt,v2,N);

					v3 = v3/N;
					PtForVsPtBackVsV33PairAvg->Fill(pTRef,pTInt,v3);
					PtForVsPtBackVsV33->Fill(pTRef,pTInt,v3,N);

					v4 = v4/N;
					PtForVsPtBackVsV44PairAvg->Fill(pTRef,pTInt,v4);

					v5 = v5/N;
					PtForVsPtBackVsV55PairAvg->Fill(pTRef,pTInt,v5);

				}
			}
		}
		delete f;
	}


	timer.Stop();
	cout << " Time used: " << timer.RealTime() << "  " <<
	timer.CpuTime() << std::endl;

	
	TFile* result = new TFile(resultfile, "RECREATE");
	result->cd();
	cout << "Writing data" << endl;
	
	dNpT_forward->Write();
	dNpT_backward->Write();
	eventCounter->Write();
	pythia_phi->Write();
	toymodel_phi->Write();
	dNpT_backward_pythia->Write();
	dNpT_forward_pythia->Write();
	eventCounterPt->Write();
	toymodel_RP->Write();
	pairCounterPt->Write();
	v2VsPt->Write();
	PtForVsPtBackVsV11PairAvg->Write();
	PtForVsPtBackVsV22PairAvg->Write();
	PtForVsPtBackVsV22->Write();
	PtForVsPtBackVsV33PairAvg->Write();
	PtForVsPtBackVsV33->Write();
	PtForVsPtBackVsV44PairAvg->Write();
	PtForVsPtBackVsV55PairAvg->Write();

	dNdDeltaPhidNdDeltaEta->Write();
	pythia_dphi->Write();

	if(calcAzimuthCorr)
		PtForVsPtBackVsdNdDeltaPhi->Write();

    	result->Close();


}

float phiTo0TwoPi(float phi){

	if (phi <  -2*TMath::TwoPi())phi -= 2.*TMath::TwoPi();
	if (phi < 0)phi += TMath::TwoPi();
	if (phi > 2*TMath::TwoPi())phi -= 2.*TMath::TwoPi();
	if (phi > TMath::TwoPi())phi -= TMath::TwoPi();

	return phi;
}

int findEtaBin(double dEta, double etaMin, double etaMax ){

	double eta = etaMin;
	int bin = 0;
	while (eta < etaMax){
		if(eta > etaMin && eta < etaMin+dEta)return bin;
		bin++;
		etaMin += dEta;
	
	}	
	return -1;
}

void calcAzimuthalCorrelation(TObjArray* traks_forward,TObjArray *tracks_backward,TH3F *PtForVsPtBackVsdNdDeltaPhi, TH2F* dNdDeltaPhidNdDeltaEta){

	//.. calc dN/d#Delta #phi distibution for accepted tracks

	float phiForw = 0., phiBack = 0., dphi = 0.;

	for(int iFor = 0; iFor < traks_forward->GetEntriesFast(); iFor++){
		TParticleMc *partForw = (TParticleMc*) traks_forward->At(iFor);
		if (partForw->get_px()==0.0 && partForw->get_py()==0.0)
			phiForw = 0.;
		else
			phiForw = TMath::ATan2(partForw->get_py(), partForw->get_px())
							+ TMath::Pi(); //.. to bring phi in 0, 2Pi range
		for(int iBack = 0; iBack < tracks_backward->GetEntriesFast(); iBack++){
			TParticleMc *partBack = (TParticleMc*) tracks_backward->At(iBack);
			if (partBack->get_px() == 0.0 && partBack->get_py() == 0.0)
				phiBack = 0.;
			else
				phiBack = TMath::ATan2(partBack->get_py(), partBack->get_px())
							+ TMath::Pi();	
			dphi = phiForw-phiBack;
			if(dphi<0)dphi += TMath::TwoPi();
			PtForVsPtBackVsdNdDeltaPhi->Fill(partForw->get_pt(),partBack->get_pt(),dphi);
			dNdDeltaPhidNdDeltaEta->Fill(dphi,fabs(partForw->get_eta() -partBack->get_eta()));
		}
	}
}

bool isChargedParticle(int PartPdgId){

	int PdgId = abs(PartPdgId);
	if( PdgId==11 || PdgId==211	//.. electron or pi+/pi-
	|| PdgId==321 || PdgId==2212)	//.. or K+/K- or proton
		return true;
	else
		return false;
		
}

bool isResonanceDaughter(int PartPdgId){

	int ParenPdgId = abs(PartPdgId);
	if( ParenPdgId==113 || ParenPdgId==213	//.. rho0 or rho+
	|| ParenPdgId==221 || ParenPdgId==223	//.. or eta or omega
	|| ParenPdgId==310 || ParenPdgId==313	//.. or K0 short or K0*
	|| ParenPdgId==323 || ParenPdgId==331)	//.. or K*+ or eta'
		return true;
	else
		return false;

}

float findPhiOfDijetLeadingPart(TClonesArray *pythia_traks){

	float phi_jet = 0.;
	float maxP = 0.;

	Int_t nParticles = pythia_traks->GetEntriesFast();
	
	//.. select track with highest momentum, maybe neutral particles as well
	for (Int_t i = 0; i < nParticles; i++) {
		TParticleMc *part = (TParticleMc*) pythia_traks->At(i);
		
		float mom = sqrt(pow(part->get_px(),2) + pow(part->get_py(),2) + pow(part->get_pz(),2));
    
		if(mom > maxP){
			phi_jet = part->get_phi();
			maxP = mom; 	
		}
	}
	return  phi_jet;
}



