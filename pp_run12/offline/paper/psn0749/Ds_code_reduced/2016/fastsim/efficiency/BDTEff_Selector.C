#define BDTEff_Selector_cxx
// The class definition in BDTEff_Selector.h has been generated automatically
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
// Root > T->Process("BDTEff_Selector.C")
// Root > T->Process("BDTEff_Selector.C","some options")
// Root > T->Process("BDTEff_Selector.C+")
//
#include "BDTEff_Selector.h"
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

void BDTEff_Selector::Begin(TTree * /*tree*/)
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

void BDTEff_Selector::SlaveBegin(TTree * /*tree*/)
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
Bool_t BDTEff_Selector::Process(Long64_t entry)
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
 int BDT_cut[6][5] = { {113, 75, 81, 86, 86}, {102, 105, 61, 68, 72}, {40, 58, 71, 65, 65}, {113, 66, 72, 76, 76}, {98, 55, 63, 67, 67}, {101, 54, 28, 28, 28} };// combined st_sst and st_physics

//int BDT_cut[6][5] = { {113+10, 75+10, 81+17, 86+26, 86+26}, {102+16, 105+19, 61+20, 68+20, 72+30}, {40+23, 58+27, 71+29, 65+30, 65+30}, {113+12, 66+18, 72+16, 76+30, 76+30}, {98+23, 55+22, 63+28, 67+30, 67+30}, {101+20, 54+24, 28+30, 28+30, 28+30} };// combined st_sst and st_physics
//
//int BDT_cut[6][5] = { {113-10, 75-10, 81-17, 86-30, 86-30}, {102-14, 105-19, 61-23, 68-30, 72-30}, {40-30, 58-30, 71-15, 65-5, 65-5}, {113-12, 66-20, 72-26, 76-26, 76-26}, {98-12, 55-29, 63-30, 67-30, 67-30}, {101-20, 54-30, 28-27, 28-27, 28-27} };// combined st_sst and st_physics
//
float ncoll[9] = {0.00342, 0.00809, 0.0174, 0.0342, 0.0625, 0.108, 0.18, 0.258, 0.327};
	float mcweight=  gf1AuAu010Weight->Eval(rPt);
	//   float mcweight = pTSpectra_Data->Eval(rPt);
	//  int i = cent;
	float ncollW = 1;
		if(cent >= 7)
		{
			//if ( rPt>2.5 && rPt<8) {cout << " mva_BDT_010_258 " << mva_BDT << endl;};
			if( rPt>1.5 && rPt<2.5 && mva_BDT > (BDT_cut[0][0]*0.005-0.2) ){ PassTpcHftPidTopoBDT[0]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>2.5 && rPt<3.5 && mva_BDT > (BDT_cut[0][1]*0.005-0.2) ){ PassTpcHftPidTopoBDT[0]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>3.5 && rPt<5 && mva_BDT > (BDT_cut[0][2]*0.005-0.2) ){ PassTpcHftPidTopoBDT[0]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>5 && rPt<8 && mva_BDT > (BDT_cut[0][3]*0.005-0.2) ){ PassTpcHftPidTopoBDT[0]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
		}
		else if(cent >= 4 && cent <= 6 )
		{
			if( rPt>1 && rPt<2 && mva_BDT > (BDT_cut[1][0]*0.005-0.2) ){ PassTpcHftPidTopoBDT[1]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>2 && rPt<2.5 && mva_BDT > (BDT_cut[1][1]*0.005-0.2) ){ PassTpcHftPidTopoBDT[1]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>1.5 && rPt<2.5 && mva_BDT > (BDT_cut[5][0]*0.005-0.2) ){ PassTpcHftPidTopoBDT_1040_1525->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>2.5 && rPt<3.5 && mva_BDT > (BDT_cut[1][2]*0.005-0.2) ){ PassTpcHftPidTopoBDT[1]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>3.5 && rPt<5 && mva_BDT > (BDT_cut[1][3]*0.005-0.2) ){ PassTpcHftPidTopoBDT[1]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>5 && rPt<8 && mva_BDT > (BDT_cut[1][4]*0.005-0.2) ){ PassTpcHftPidTopoBDT[1]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}

			if( rPt>1.5 && rPt<2.5 && cent >=6 && mva_BDT > (BDT_cut[3][0]*0.005-0.2) ){ PassTpcHftPidTopoBDT[3]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>2.5 && rPt<3.5 && cent >=6 && mva_BDT > (BDT_cut[3][1]*0.005-0.2) ){ PassTpcHftPidTopoBDT[3]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>3.5 && rPt<5 && cent >=6 && mva_BDT > (BDT_cut[3][2]*0.005-0.2) ){ PassTpcHftPidTopoBDT[3]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>5 && rPt<8 && cent >=6 && mva_BDT > (BDT_cut[3][3]*0.005-0.2) ){ PassTpcHftPidTopoBDT[3]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}

			if( rPt>1.5 && rPt<2.5 && cent <=5 && mva_BDT > (BDT_cut[4][0]*0.005-0.2) ){ PassTpcHftPidTopoBDT[4]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>2.5 && rPt<3.5 && cent <=5 && mva_BDT > (BDT_cut[4][1]*0.005-0.2) ){ PassTpcHftPidTopoBDT[4]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>3.5 && rPt<5 && cent <=5 && mva_BDT > (BDT_cut[4][2]*0.005-0.2) ){ PassTpcHftPidTopoBDT[4]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>5 && rPt<8 && cent <=5 && mva_BDT > (BDT_cut[4][3]*0.005-0.2) ){ PassTpcHftPidTopoBDT[4]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
		}
		else 
		{
			if( rPt>1.5 && rPt<2.5 && mva_BDT > (BDT_cut[2][0]*0.005-0.2) ){ PassTpcHftPidTopoBDT[2]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>2.5 && rPt<3.5 && mva_BDT > (BDT_cut[2][1]*0.005-0.2) ){ PassTpcHftPidTopoBDT[2]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>3.5 && rPt<5 && mva_BDT > (BDT_cut[2][2]*0.005-0.2) ){ PassTpcHftPidTopoBDT[2]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>5 && rPt<8 && mva_BDT > (BDT_cut[2][3]*0.005-0.2) ){ PassTpcHftPidTopoBDT[2]->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>1.5 && rPt<5 && cent >=2 && cent <=3 && mva_BDT > (BDT_cut[5][1]*0.005-0.2) ){ PassTpcHftPidTopoBDT_46->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}
			if( rPt>1.5 && rPt<5 && cent >=0 && cent <=1 && mva_BDT > (BDT_cut[5][2]*0.005-0.2) ){ PassTpcHftPidTopoBDT_68->Fill(rPt, mcweight*PIDweight*ncollW*TpcWeight);}

		}

	
	return kTRUE;

}
void BDTEff_Selector::SlaveTerminate()
{
	cout << "-------------End of Slave Job----------------" << endl;
	tNow.Set(); tNow.Print();
	cout << "Number of Event: " << fNumberOfEvents << ", elapsed time: " << tNow.Convert() - tBegin.Convert() << "seconds,rate: " << float(fNumberOfEvents) / (tNow.Convert() - tBegin.Convert()) << endl;
}

void BDTEff_Selector::Terminate()
{
	TString output = GetOption();

	TFile *hfile = new TFile(output, "RECREATE", "event time info");
	hfile->cd();
	for(int i = 0; i < 5; i++)
	{
		PassTpcHftPidTopoBDT[i]->Write();
	}

	PassTpcHftPidTopoBDT_46->Write();
		PassTpcHftPidTopoBDT_68->Write();
		PassTpcHftPidTopoBDT_1040_1525->Write();

	hfile->Close();

	fOutput->Delete();
	cout << "----------End of job----------" << endl;
	tNow.Set();
	tNow.Print();

}
