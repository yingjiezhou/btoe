#define Selector_cxx
// The class definition in Selector.h has been generated automatically
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
// Root > T->Process("Selector.C")
// Root > T->Process("Selector.C","some options")
// Root > T->Process("Selector.C+")
//

#include "Selector.h"
#include <TH2.h>
#include <TStyle.h>
#include "TDatime.h"
#include "TSystem.h"
#include <stdio.h>
#include <iostream>
#include "TLorentzVector.h"
#include <TH1.h>
#include <TH3.h>
using namespace std;
int eventnumber = 0;
int per = 1;
int eventnum = 0;
int rightsign_num[200] = { 0};
int wrongsign_num[200] = { 0};
float S_num[200] = {0};
float B_num[200] = {0};
float Significance[200] = {0};
TDatime tBegin, tNow;
#define M_CUT         1 

void Selector::Begin(TTree * /*tree*/)
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

void Selector::SlaveBegin(TTree * /*tree*/)
{

	TH1::SetDefaultSumw2();
	TString option = GetOption();
	TString filename = option.ReplaceAll(".root", ""); // --> "./Ds_ch2"
	Ssiz_t last = filename.Last('/');
	filename.Remove(0, last + 1); // TString index star with 0, and Remove should remove the number of member. --> "Ds_ch
	filename.ReplaceAll("Lc.tmva", ""); // --> "2"
	cout << filename.Data() << endl;
	decayCh = filename.Atoi();  // Convert Char to Int
	cout << "Decay Channel is : " << decayCh << endl;
	// h3bkg_Lc = new TH3D("h3bkg_Lc", "Lc bkg vs pt vs cen with re-weight;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 10, 0, 10, 9, -0.5, 8.5, 40, 2.1, 2.5);
	// h3sg_Lc = new TH3D("h3sg_Lc", "Lc bkg vs pt vs cen with re-weight;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 10, 0, 10, 9, -0.5, 8.5, 40, 2.1, 2.5);
	TString HistName;
	h3bkg_010_Ds = new TH3D("h3bkg_010_Ds", "h3bkg_010_Ds;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
	h3bkg_1040_Ds = new TH3D("h3bkg_1040_Ds", "h3bkg_1040_Ds;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
	h3bkg_4080_Ds = new TH3D("h3bkg_4080_Ds", "h3bkg_4080_Ds;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
	h3RS_010_Ds = new TH3D("h3RS_010_Ds", "h3RS_010_Ds;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
	h3RS_1040_Ds = new TH3D("h3RS_1040_Ds", "h3RS_1040_Ds;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
	h3RS_4080_Ds = new TH3D("h3RS_4080_Ds", "h3RS_4080_Ds;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
	for (int i = 1; i < 161 ; i++ )
	{
		h3bkg_010_Lc[i] = new TH3D(Form("h3bkg_010_Lc_%i", i ), "Lc bkg vs pt vs cen with re-weight;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
		h3sg_010_Lc[i] = new TH3D(Form("h3sg_010_Lc_%i", i ), "Lc bkg vs pt vs cen with re-weight;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
		h3bkg_1040_Lc[i] = new TH3D(Form("h3bkg_1040_Lc_%i", i ), "Lc bkg vs pt vs cen with re-weight;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
		h3sg_1040_Lc[i] = new TH3D(Form("h3sg_1040_Lc_%i", i ), "Lc bkg vs pt vs cen with re-weight;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
		h3bkg_4080_Lc[i] = new TH3D(Form("h3bkg_4080_Lc_%i", i ), "Lc bkg vs pt vs cen with re-weight;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
		h3sg_4080_Lc[i] = new TH3D(Form("h3sg_4080_Lc_%i", i ), "Lc bkg vs pt vs cen with re-weight;p_{T} [GeV/c];Centrality;Invariant Mass [GeV/c^{2}]", 100, 0, 10, 9, -0.5, 8.5, 38, 1.8, 2.1);
	}






	fOutput->AddAll(gDirectory->GetList());

}


Bool_t Selector::Process(Long64_t entry)
{
	eventnum = eventnum +1;
	if (fNumberOfEvents == 0) {
		eventnumber = fChain->GetEntries();
		cout << "Entries = " << eventnumber << endl;
		if (eventnumber < 100) per = 1;
		else per = eventnumber / 100;

		cout << "per = " << per << endl;
	}
	if (fNumberOfEvents % per == 0) cout << "PROCESSING " << float(fNumberOfEvents) / eventnumber * 100 << "%...." << endl;
	GetEntry(entry);
	++fNumberOfEvents;
	//cout<< "1111111" << endl;
	//float BDTCut          =  0.1870;  // 0.2081
	if (cent < 0) return kTRUE; // 0-80 % centrality
	/*if (mva_BDT > (-0.2 + 82*0.005)&& cent >=7 && cent<=8 && rPt>1.5 && rPt<2.5 && flag<=1)
	  {
	  if (rM >= 1.9185 && rM <= 1.9263) { cout << " reweight = " << reweight << endl;}
	  }*/

	//if (DsCharge == 1) return kTRUE; 
	if (flag<=1 && mva_BDT>-10)
	{
		if(cent>=7 && cent<=8)
		{ h3bkg_010_Ds->Fill(rPt, cent, rM, reweight); }
		else if(cent>=4 && cent <=6)
		{h3bkg_1040_Ds->Fill(rPt, cent, rM, reweight);}
		else
		{h3bkg_4080_Ds->Fill(rPt, cent, rM, reweight);}

	}
	if (flag>=2 && mva_BDT>-10)
	{
		if(cent>=7 && cent<=8)
		{ h3RS_010_Ds->Fill(rPt, cent, rM, reweight); }
		else if(cent>=4 && cent <=6)
		{h3RS_1040_Ds->Fill(rPt, cent, rM, reweight);}
		else
		{h3RS_4080_Ds->Fill(rPt, cent, rM, reweight);}

	}

		for (int i = 1; i< 161; i++)
		{
			//cout << "flag1" << endl;
			if (mva_BDT > (-0.2 + i*0.005))
			{
				// if(rM>=2.26 && rM<=2.315)
				// {  allsign_num_cent1 = allsign_num_cent1 + 1;}
				if (flag>=2)
				{
					// cout<<"flag2"<<endl;
					if(cent>=7 && cent<=8)
					{ h3sg_010_Lc[i]->Fill(rPt, cent, rM, reweight); }
					else if(cent>=4 && cent <=6)
					{h3sg_1040_Lc[i]->Fill(rPt, cent, rM, reweight);}
					else 
					{h3sg_4080_Lc[i]->Fill(rPt, cent, rM, reweight);} 

				}
				else
				{  
					// cout<<"flag3"<< endl;
					if(cent>=7 && cent<=8)
					{ h3bkg_010_Lc[i]->Fill(rPt, cent, rM, reweight);}
					else if(cent>=4 && cent <=6)
					{h3bkg_1040_Lc[i]->Fill(rPt, cent, rM, reweight);}
					else
					{h3bkg_4080_Lc[i]->Fill(rPt, cent, rM, reweight);}


				}
			} 

		}
		return kTRUE;
	}

	void Selector::SlaveTerminate()
	{

		cout << "-------------End of Slave Job----------------" << endl;
		tNow.Set(); tNow.Print();
		cout << "Number of Event: " << fNumberOfEvents << ", elapsed time: " << tNow.Convert() - tBegin.Convert() << "seconds,rate: " << float(fNumberOfEvents) / (tNow.Convert() - tBegin.Convert()) << endl;
	}

	void Selector::Terminate()
	{
		// The Terminate() function is the last function to be called during
		// a query. It always runs on the client, it can be used to present
		// the results graphically or save the results to file.
		//cout << "allsign_num = " << allsign_num << endl;

		TString output = GetOption();
		TFile *hfile = new TFile(output, "RECREATE", "event time info");
		hfile->cd();
			h3bkg_010_Ds->Write();
			h3bkg_1040_Ds->Write();
			h3bkg_4080_Ds->Write();
			h3RS_010_Ds->Write();
			h3RS_1040_Ds->Write();
			h3RS_4080_Ds->Write();
		for( int i = 1; i< 161; i++)
		{
			h3bkg_010_Lc[i]->Write();
			h3sg_010_Lc[i]->Write();
			h3bkg_1040_Lc[i]->Write();
			h3sg_1040_Lc[i]->Write();
			h3bkg_4080_Lc[i]->Write();
			h3sg_4080_Lc[i]->Write();
		}

		// response_Scan->Write();
		hfile->Close();
		fOutput->Delete();
		cout << "----------End of job----------" << endl;
		tNow.Set();
		tNow.Print();
	} 
