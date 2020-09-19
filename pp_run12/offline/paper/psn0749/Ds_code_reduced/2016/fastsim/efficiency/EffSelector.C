#define EffSelector_cxx
// The class definition in EffSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("EffSelector.C")
// Root > T->Process("EffSelector.C","some options")
// Root > T->Process("EffSelector.C+")
//
#include "EffSelector.h"
#include <TH2.h>
#include <TStyle.h>
#include "TDatime.h"
#include "TSystem.h"
#include <stdio.h>
#include <iostream>
#include "TFile.h"
#include "TF1.h"
#include "TLorentzVector.h"

using namespace std;
int eventnumber = 0;
int per = 1;
TDatime tBegin, tNow;

void EffSelector::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	tBegin.Set();
	fNumberOfEvents = 0;
	cout << "-------Begin of job-------" << endl;
	tBegin.Print();

}

void EffSelector::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	TString option = GetOption();
	TString filename = option.ReplaceAll(".root", ""); // --> "./Ds_ch2"
	Ssiz_t last = filename.Last('/');
	filename.Remove(0, last + 1); // TString index star with 0, and Remove should remove the number of member. --> "Ds_ch"
	filename.ReplaceAll("Ds_ch", ""); // --> "2"
	cout << filename.Data() << endl;
	decayCh = filename.Atoi();  // Convert Char to Int
	cout << "Decay Channel is : " << decayCh << endl;
	TString const mCent[5] = {"010", "1040", "4080", "1020", "2040"};
	double pTbin[6]={0.0, 1.5, 2.5, 3.5, 5, 8};
	double pTbin_split[7]={0.0, 1, 2, 2.5, 3.5, 5, 8};
	//float ncoll[9] = {0.00342, 0.00809, 0.0174, 0.0342, 0.0625, 0.108, 0.18, 0.258, 0.327};

	//ncoll[9] ={};
	char name1[60];
	char name2[60];
	char name3[60];
	char name4[60];
	char name5[60];
	TH1::SetDefaultSumw2();
	for( int i = 0; i<5; i++)
{
   if (i != 1)
	{

		AllCounts[i] = new TH1F(Form("AllCouts_%s_Ds", mCent[i].Data()), "p_{T} GeV/c", 5, pTbin);
		PassAcc[i] = new TH1F(Form("PassAcc_%s_Ds",mCent[i].Data()), "p_{T} GeV/c", 5, pTbin);
		PassTpc[i] = new TH1F(Form("PassTpc_%s_Ds",mCent[i].Data()), "p_{T} GeV/c", 5, pTbin);
		PassTpcHft[i] = new TH1F(Form("PassTpcHft_%s_Ds",mCent[i].Data()), "p_{T} GeV/c", 5, pTbin);
		PassTpcHftPid[i] = new TH1F(Form("PassTpcHftPid_%s_Ds", mCent[i].Data()), "p_{T} GeV/c", 5, pTbin);
		PassTpcHftPidTopo[i] = new TH1F(Form("PassTpcHftPidTopo_%s_Ds", mCent[i].Data()), "p_{T} GeV/c", 5, pTbin);
		PassTpcHftPidTopoBDT[i] = new TH1F(Form("PassTpcHftPidTopoBDT_%s_Ds", mCent[i].Data()), "p_{T} GeV/c", 5, pTbin);
		BDT_response_pT2D[i] = new TH2F(Form("BDT_response_pT2D_%s", mCent[i].Data()), "", 240, -0.2, 1, 5, pTbin);
		BDT_response_TpcPidWeight_pT2D[i] = new TH2F(Form("BDT_response_TpcPidWeight_pT2D_%s", mCent[i].Data()), "", 240, -0.2, 1, 5, pTbin);
	}
else
	{

		AllCounts[i] = new TH1F(Form("AllCouts_%s_Ds", mCent[i].Data()), "p_{T} GeV/c", 6, pTbin_split);
		PassAcc[i] = new TH1F(Form("PassAcc_%s_Ds",mCent[i].Data()), "p_{T} GeV/c", 6, pTbin_split);
		PassTpc[i] = new TH1F(Form("PassTpc_%s_Ds",mCent[i].Data()), "p_{T} GeV/c", 6, pTbin_split);
		PassTpcHft[i] = new TH1F(Form("PassTpcHft_%s_Ds",mCent[i].Data()), "p_{T} GeV/c", 6, pTbin_split);
		PassTpcHftPid[i] = new TH1F(Form("PassTpcHftPid_%s_Ds", mCent[i].Data()), "p_{T} GeV/c", 6, pTbin_split);
		PassTpcHftPidTopo[i] = new TH1F(Form("PassTpcHftPidTopo_%s_Ds", mCent[i].Data()), "p_{T} GeV/c", 6, pTbin_split);
		PassTpcHftPidTopoBDT[i] = new TH1F(Form("PassTpcHftPidTopoBDT_%s_Ds", mCent[i].Data()), "p_{T} GeV/c", 6, pTbin_split);
		BDT_response_pT2D[i] = new TH2F(Form("BDT_response_pT2D_%s", mCent[i].Data()), "", 240, -0.2, 1, 6, pTbin_split);
		BDT_response_TpcPidWeight_pT2D[i] = new TH2F(Form("BDT_response_TpcPidWeight_pT2D_%s", mCent[i].Data()), "", 240, -0.2, 1, 6, pTbin_split);
	}
}
		AllCounts_46 = new TH1F("AllCouts_46_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassAcc_46 = new TH1F("PassAcc_46_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpc_46 = new TH1F("PassTpc_46_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpcHft_46 = new TH1F("PassTpcHft_46_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpcHftPid_46 = new TH1F("PassTpcHftPid_46_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpcHftPidTopo_46 = new TH1F("PassTpcHftPidTopo_46_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpcHftPidTopoBDT_46 = new TH1F("PassTpcHftPidTopoBDT_46_Ds", "p_{T} GeV/c", 1, 1.5, 5);
	
	AllCounts_68 = new TH1F("AllCouts_68_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassAcc_68 = new TH1F("PassAcc_68_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpc_68 = new TH1F("PassTpc_68_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpcHft_68 = new TH1F("PassTpcHft_68_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpcHftPid_68 = new TH1F("PassTpcHftPid_68_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpcHftPidTopo_68 = new TH1F("PassTpcHftPidTopo_68_Ds", "p_{T} GeV/c", 1, 1.5, 5);
		PassTpcHftPidTopoBDT_68 = new TH1F("PassTpcHftPidTopoBDT_68_Ds", "p_{T} GeV/c", 1, 1.5, 5);

	AllCounts_1040_1525 = new TH1F("AllCouts_1040_1525_Ds", "p_{T} GeV/c", 1, 1.5, 2.5);
		PassAcc_1040_1525 = new TH1F("PassAcc_1040_1525_Ds", "p_{T} GeV/c", 1, 1.5, 2.5);
		PassTpc_1040_1525 = new TH1F("PassTpc_1040_1525_Ds", "p_{T} GeV/c", 1, 1.5, 2.5);
		PassTpcHft_1040_1525 = new TH1F("PassTpcHft_1040_1525_Ds", "p_{T} GeV/c", 1, 1.5, 2.5);
		PassTpcHftPid_1040_1525 = new TH1F("PassTpcHftPid_1040_1525_Ds", "p_{T} GeV/c", 1, 1.5, 2.5);
		PassTpcHftPidTopo_1040_1525 = new TH1F("PassTpcHftPidTopo_1040_1525_Ds", "p_{T} GeV/c", 1, 1.5, 2.5);
		PassTpcHftPidTopoBDT_1040_1525 = new TH1F("PassTpcHftPidTopoBDT_1040_1525_Ds", "p_{T} GeV/c", 1, 1.5, 2.5);

	//TFile* fAuAu010Weight = new TFile("AuAu010_weight.root");
	//gf1AuAu010Weight = (TF1*)fAuAu010Weight->Get("f1Levy010");
	TFile* fAuAu010Weight = new TFile("DsSpectrum_Fit.root");
	gf1AuAu010Weight = (TF1*)fAuAu010Weight->Get("Levy_timepT_1");
	pTSpectra_Data = new TF1("pTSpectra_Data","[0]*exp([1]*x + [2])", 0, 12);
	pTSpectra_Data->FixParameter(0,2.10973e-05);
	pTSpectra_Data->FixParameter(1,-1.75125e+00);
	pTSpectra_Data->FixParameter(2,8.60801e+00);
	fAuAu010Weight->Close();
	DsSig  = new TTree("nt","Ds signal tree");
	DsSig->Branch("decayLength",&decayLength,"decayLength/F");
	DsSig->Branch("cosTheta",&cosTheta,"cosTheta/F");
	DsSig->Branch("dcaDaughters",&dcaDaughters,"dcaDaughters/F");
	DsSig->Branch("dcaLcToPv",&dcaLcToPv,"dcaLcToPv/F");
	DsSig->Branch("k1RDca",&k1RDca,"k1RDca/F");
	DsSig->Branch("piRDca",&piRDca,"piRDca/F");
	DsSig->Branch("RDca12",&RDca12,"RDca12/F");
	DsSig->Branch("k2RDca",&k2RDca,"k2RDca/F");
	DsSig->Branch("rM",&rM,"rM/F");
	DsSig->Branch("rEta",&rEta,"rEta/F");
	// DsSig->Branch("Mass_Phi",&Mass_Phi,"Mass_Phi/F");
	DsSig->Branch("rY",&rY,"rY/F");
	// DsSig->Branch("dcaLcToPv",&dcaLcToPv,"dcaLcToPv/F");
	DsSig->Branch("cent",&cent,"cent/F");
	DsSig->Branch("rPt",&rPt,"rPt/F");
	DsSig->Branch("massDiff",&massDiff,"massDiff/F");
	//DsSig->Branch("rPt_Phi",&rPt_Phi,"rPt_Phi/F");
	DsSig->Branch("rPtk1",&rPtk1,"rPtk1/F");
	DsSig->Branch("rPtk2",&rPtk2,"rPtk2/F");
	DsSig->Branch("rPt12",&rPt12,"rPt12/F");
	DsSig->Branch("rPtpi",&rPtpi,"rPtpi/F");
	DsSig->Branch("flag",&flag,"flag/F");
	DsSig->Branch("PIDweight",&PIDweight,"PIDweight/F");
	DsSig->Branch("TpcWeight",&TpcWeight,"TpcWeight/F");
	//   DsSig->Branch("HftAcc_Weight",&HftAcc_Weight,"HftAcc_Weight/F");

	fOutput->AddAll(gDirectory->GetList());
}
Bool_t EffSelector::Process(Long64_t entry)
{
	if (fNumberOfEvents ==0)
	{
		eventnumber = fChain->GetEntries();
		cout << "Entries = " << eventnumber << endl;
		if (eventnumber < 100) per = 1;
		else per = eventnumber / 100;
		cout << "per = " << per << endl;
	}
	if (fNumberOfEvents % per == 0) cout << "PROCESSING " << float(fNumberOfEvents) / eventnumber * 100 << "%...." << endl;
	GetEntry(entry);
	++fNumberOfEvents;

	if(cent <0) return kTRUE;
//int BDT_cut[6][5] = { {114+0.0, 72+0.0, 77+0.0, 77+0.0, 77+0.0 }, {107+0.0, 101+0.0, 60+0.0, 68+0.0, 70+0.0}, {42+0.0, 57+0.0, 67+0.0, 68+0.0, 68+0.0}, {107+0.0, 65+0.0, 72+0.0, 75+0.0, 75+0.0}, {96+0.0, 54+0.0, 62+0.0, 68+0.0, 68+0.0}, {106, 52, 51, 51, 51} };

//int BDT_cut[6][5] = { {114+16, 72+15, 77+18, 77+30, 77+30 }, {107+18, 101+25, 60+20, 68+20, 70+30}, {42+26, 57+23, 67+30, 68+26, 68+26}, {107+20, 65+20, 72+19, 75+28, 75+28}, {96+20, 54+20, 62+23, 68+29, 68+29}, {106+20, 52+28, 51+28, 51+28, 51+28}};

//int BDT_cut[6][5] = { {114-16, 72-15, 77-18, 77-30, 77-30 }, {107-16, 101-21, 60-25, 68-25, 70-30}, {42-30, 57-30, 67-25, 68-20, 68-20}, {107-24, 65-23, 72-30, 75-20, 75-20}, {96-18, 54-29, 62-30, 68-25, 68-25}, {106-20, 52-30, 51-30, 51-30, 51-30} };

float ncoll[9] = {0.00342, 0.00809, 0.0174, 0.0342, 0.0625, 0.108, 0.18, 0.258, 0.327};
	float mcweight=  gf1AuAu010Weight->Eval(rPt);
	//   float mcweight = pTSpectra_Data->Eval(rPt);
	//  int i = cent;
	float ncollW = 1;

	
	   bool PassTopology =  rPtk1 > 0.5 && rPtk2 > 0.5 && rPtpi > 0.6 && k1RDca > 0.006 && k2RDca > 0.006 && piRDca > 0.006  && decayLength > 0.012 && dcaDaughters < 0.01 && cosTheta >0.98 && cosTheta<1 && massDiff < 0.008 && fabs(rY) < 1 && rM >1.8 && rM < 2.1;
	bool PassTpcAcc = fabs(piREta) <1 && fabs(kREta) < 1 && fabs(pREta) < 1 ;
	bool PassHft = piHft > 0 && kHft > 0 && pHft > 0; 
	TpcWeight = piTpc*kTpc*pTpc;   
	float BDTcut;
	float AccCut = 0;
	float HftCut = 0;
	if(PassTpcAcc){AccCut = 1;}
	if(PassHft){HftCut = 1;}
	//HftAcc_Weight = AccCut*HftCut;
	//   cout << "flag1"<< endl;
	//if(cent <0) return kTRUE;
	//float mcweight=  gf1AuAu010Weight->Eval(rPt);
	if(cent >= 7)
	AllCounts[0]->Fill(rPt, mcweight*ncollW);
	else if(cent >= 4 && cent <= 6)
{
if (cent >=6 && cent <=6) AllCounts[3]->Fill(rPt, mcweight*ncollW);
if (cent >=4 && cent <=5) AllCounts[4]->Fill(rPt, mcweight*ncollW);
	AllCounts[1]->Fill(rPt, mcweight*ncollW);
	AllCounts_1040_1525->Fill(rPt, mcweight*ncollW);
}
	else
{ 
	AllCounts[2]->Fill(rPt, mcweight*ncollW);
if (cent >=2 && cent <=3) AllCounts_46->Fill(rPt, mcweight*ncollW);
if (cent >=0 && cent <=1) AllCounts_68->Fill(rPt, mcweight*ncollW);
}	// cout << "flag2"<< endl;
	if(PassTpcAcc)
	{
	//  cout << "flag3"<< endl;
	if(cent >= 7) 
	{
	PassAcc[0]->Fill(rPt, mcweight*ncollW);
	PassTpc[0]->Fill(rPt, mcweight*ncollW*TpcWeight);
	}
	else if(cent >= 4 && cent <= 6)
	{
if (cent >=6 && cent <=6) 
{
PassAcc[3]->Fill(rPt, mcweight*ncollW);
PassTpc[3]->Fill(rPt, mcweight*ncollW*TpcWeight);
}
if (cent >=4 && cent <=5) 
{
PassAcc[4]->Fill(rPt, mcweight*ncollW);
PassTpc[4]->Fill(rPt, mcweight*ncollW*TpcWeight);
}
	PassAcc[1]->Fill(rPt, mcweight*ncollW);
	PassTpc[1]->Fill(rPt, mcweight*ncollW*TpcWeight);
	PassAcc_1040_1525->Fill(rPt, mcweight*ncollW);
	PassTpc_1040_1525->Fill(rPt, mcweight*ncollW*TpcWeight);
	}
	else
	{
	PassAcc[2]->Fill(rPt, mcweight*ncollW);

	PassTpc[2]->Fill(rPt, mcweight*ncollW*TpcWeight);
if (cent >=2 && cent <=3) 
{
	PassAcc_46->Fill(rPt, mcweight*ncollW);
	PassTpc_46->Fill(rPt, mcweight*ncollW*TpcWeight);
}
if (cent >=0 && cent <=1) 
{
	PassAcc_68->Fill(rPt, mcweight*ncollW);
	PassTpc_68->Fill(rPt, mcweight*ncollW*TpcWeight);
}
	}
	}
	//cout << "flag4"<< endl;
	if(PassTpcAcc && PassHft)
	{  
	//  cout << "flag5"<< endl;
	if(cent >= 7)
	{
	PassTpcHft[0]->Fill(rPt, mcweight*ncollW*TpcWeight);
	PassTpcHftPid[0]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
	}
	else if(cent >= 4 && cent <= 6)
	{
if (cent >= 6 && cent <= 6)
{
        PassTpcHft[3]->Fill(rPt, mcweight*ncollW*TpcWeight);
	PassTpcHftPid[3]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
}
if (cent >= 4 && cent <= 5)
{
        PassTpcHft[4]->Fill(rPt, mcweight*ncollW*TpcWeight);
        PassTpcHftPid[4]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
}

        PassTpcHft[1]->Fill(rPt, mcweight*ncollW*TpcWeight);
	PassTpcHftPid[1]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
        PassTpcHft_1040_1525->Fill(rPt, mcweight*ncollW*TpcWeight);
	PassTpcHftPid_1040_1525->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
	}else
	{
        PassTpcHft[2]->Fill(rPt, mcweight*ncollW*TpcWeight);
	PassTpcHftPid[2]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
if (cent >=2 && cent <=3)
{
        PassTpcHft_46->Fill(rPt, mcweight*ncollW*TpcWeight);
	PassTpcHftPid_46->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
}
if (cent >=0 && cent <=1)
{
        PassTpcHft_68->Fill(rPt, mcweight*ncollW*TpcWeight);
	PassTpcHftPid_68->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
}
	}
	}
	// if(PassTpcAcc &&PassHft && PassTopology)
	if(PassTopology && PassTpcAcc && PassHft)
	{
	//cout << "flag7"<< endl;
	DsSig->Fill();
	if(cent >= 7)
	PassTpcHftPidTopo[0]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
	else if(cent >= 4 && cent <= 6)
{	
if (cent >= 6 && cent <= 6) PassTpcHftPidTopo[3]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
if (cent >= 4 && cent <= 5) PassTpcHftPidTopo[4]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
PassTpcHftPidTopo[1]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
PassTpcHftPidTopo_1040_1525->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
}
	else

{
	PassTpcHftPidTopo[2]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
if (cent >=2 && cent <=3) PassTpcHftPidTopo_46->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
if (cent >=0 && cent <=1) PassTpcHftPidTopo_68->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);
}
	}


	return kTRUE;

}
void EffSelector::SlaveTerminate()
{
	cout << "-------------End of Slave Job----------------" << endl;
	tNow.Set(); tNow.Print();
	cout << "Number of Event: " << fNumberOfEvents << ", elapsed time: " << tNow.Convert() - tBegin.Convert() << "seconds,rate: " << float(fNumberOfEvents) / (tNow.Convert() - tBegin.Convert()) << endl;
}

void EffSelector::Terminate()
{
	TString output = GetOption();

	TFile *hfile = new TFile(output, "RECREATE", "event time info");
	hfile->cd();
	 DsSig->Write();
	for(int i = 0; i < 5; i++)
	{
		   AllCounts[i]->Write();  
		     PassTpc[i]->Write();
		     PassAcc[i]->Write();
		     PassTpcHft[i]->Write();
		     PassTpcHftPid[i]->Write();
		     PassTpcHftPidTopo[i]->Write();
	}
		   AllCounts_46->Write();  
		     PassTpc_46->Write();
		     PassAcc_46->Write();
		     PassTpcHft_46->Write();
		     PassTpcHftPid_46->Write();
		     PassTpcHftPidTopo_46->Write();

		   AllCounts_68->Write();  
		     PassTpc_68->Write();
		     PassAcc_68->Write();
		     PassTpcHft_68->Write();
		     PassTpcHftPid_68->Write();
		     PassTpcHftPidTopo_68->Write();

		   AllCounts_1040_1525->Write();  
		     PassTpc_1040_1525->Write();
		     PassAcc_1040_1525->Write();
		     PassTpcHft_1040_1525->Write();
		     PassTpcHftPid_1040_1525->Write();
		     PassTpcHftPidTopo_1040_1525->Write();

	hfile->Close();

	fOutput->Delete();
	cout << "----------End of job----------" << endl;
	tNow.Set();
	tNow.Print();

}
