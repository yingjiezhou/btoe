/*
 * plotRes200GeV.C
 *
 *  Created on: Jul 15, 2012
 *      Author: dkikola
 */

#include <TFile.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TROOT.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TLine.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TGraphAsymmErrors.h>

#include "style.C"

void removeNonflow(TGraph* gr, TGraph* nonflow);

void printData(TGraphErrors* v2Stat, TGraphAsymmErrors* v2syst){

	cout << "pt [GeV/c]\tv2\tstat. err\tsyst.err" << endl;
	for(int i = 0; i<v2Stat->GetN();i++){
		cout << v2Stat->GetX()[i] << "\t" << v2Stat->GetY()[i] << "\t";
		cout << v2Stat->GetEY()[i] << "\t" << v2syst->GetEY()[i] << endl; 
	}
}


void plotRes200GeV(bool addPhenix = false, bool subtractNonflow = false){


	gROOT->ForceStyle();
	setWindowDressing();

	int errXwidth  = 8; //the size of the lines at the end of the error bars
	gStyle->SetEndErrorSize(errXwidth);

	float Xmin = 0.0, Xmax = 8.0;
	float Ymin = -0.02, Ymax = 0.25;

	// Event plane results from Wenquin
	const int NepPts = 5;
	 float x[NepPts]={2.5,3.5,4.5,5.5,7}; //pT
	 float xe[NepPts]={0.5,0.5,0.5,0.5,1}; //pT err

	 float y[NepPts] = {0.0962731,0.0933855,0.0711847,0.133556,0.175828};  				//NPE v2
	 float ye[NepPts] = {0.0407939, 0.0234428, 0.0217291,0.0293258,0.0454885};			//v2 err;
	 //syst. error on v2{EP}
	 float yeUp[NepPts] = {0.00632994,0.00427849,0.00567323,0.00297623,0.00982399};			//v2 err;
	 float yeLow[NepPts] = {0.008501,0.00485422,0.00724429,0.00403387,0.014402};			//v2 err;

	/* v2 using photonic v2 from simulations */

	TString v2_2part_mb_fname = "data/NpeFlow/v2_2part_MB_AuAu200GeV-2016-05-05.root";
	TString v2_2part_ht_fname = "data/NpeFlow/v2_2part_HT_AuAu200GeV.root";
	TString v2_4part_mb_fname ="data/NpeFlow/v2_4part_MB_AuAu200GeV-2016-05-05.root";
	TString v2_2part_200GeV_mb_syst_err_fname =  v2_2part_mb_fname; 
	TString v2_4part_200GeV_mb_syst_err_fname = v2_4part_mb_fname; 
	TString v2_2part_200GeV_ht_syst_err_fname = v2_2part_ht_fname; 
	TString v2_2part_nonflow_fname = "data/NpeFlow/nonfow_run5_ht1_run6_ht2_pythia_combined_Jan13_2014_pointsAtMeanPt.txt";



	TFile* f2part_mb = new TFile(v2_2part_mb_fname);
	TFile* f4part_mb = new TFile(v2_4part_mb_fname);
	TFile* f2part_ht = new TFile(v2_2part_ht_fname);
	//TFile* f_2part_nonflow = new TFile(v2_2part_nonflow_fname);


	TFile* fSystErr2part_200GeV_mb = new TFile(v2_2part_200GeV_mb_syst_err_fname);
	TFile* fSystErr4part_200GeV_mb = new TFile(v2_4part_200GeV_mb_syst_err_fname);
	TFile* fSystErr2part_200GeV_ht = new TFile(v2_2part_200GeV_ht_syst_err_fname);

	TGraphErrors* v2_2part_mb = (TGraphErrors*)f2part_mb->Get("v2NpeVsPts");
    TGraphErrors* v2_4part_mb = (TGraphErrors*)f4part_mb->Get("v2NpeVsPts");
    TGraphErrors* v2_2part_ht = (TGraphErrors*)f2part_ht->Get("v2NpeVsPts");

    TGraphErrors* v2_2part_nonflow = new TGraphErrors(v2_2part_nonflow_fname,"%lg %lg %lg");

    TGraphAsymmErrors* grSystErrv2_2part200GeV_mb = (TGraphAsymmErrors*)fSystErr2part_200GeV_mb->Get("v2NpeSystErrVsPt");
    TGraphAsymmErrors* grSystErrv2_4part200GeV_mb = (TGraphAsymmErrors*)fSystErr4part_200GeV_mb->Get("v2NpeSystErrVsPt");
    TGraphAsymmErrors* grSystErrv2_2part200GeV_ht = (TGraphAsymmErrors*)fSystErr2part_200GeV_ht->Get("v2NpeSystErrVsPt");


    TGraphErrors* v2_EventPlane = new TGraphErrors(NepPts,x,y,0,ye);
    TGraphAsymmErrors* v2SystErr_EventPlane = new TGraphAsymmErrors(NepPts,x,y,0,0,yeLow, yeUp);

    TGraphErrors* grV2PheStatErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_stat.err.txt");
    TGraphErrors* grV2PheSystErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_sys.err.txt");

    v2_4part_mb->SetLineColor(kBlack);
    v2_4part_mb->SetMarkerColor(kBlack);
    v2_4part_mb->SetMarkerStyle(kFullCircle);

    grSystErrv2_4part200GeV_mb->SetLineColor(kBlack);

    v2_2part_ht->SetLineColor(kGreen+3);
    v2_2part_ht->SetMarkerColor(kGreen+3);
    v2_2part_ht->SetMarkerStyle(kFullStar);
    v2_2part_ht->SetMarkerSize(MarkerSize + 0.5);

    grSystErrv2_2part200GeV_ht->SetLineColor(kGreen+3);

    v2_2part_mb->SetLineColor(kRed);
    v2_2part_mb->SetMarkerColor(kRed);
    v2_2part_mb->SetMarkerStyle(kFullSquare);


	grV2PheStatErr->SetMarkerStyle(kOpenCircle);
	grV2PheStatErr->SetMarkerColor(kBlue);
	grV2PheStatErr->SetLineWidth(LineWidth);
	grV2PheStatErr->SetLineColor(kBlue);
	grV2PheSystErr->SetLineColor(kBlue);
	grV2PheSystErr->SetLineWidth(LineWidth);


	grSystErrv2_2part200GeV_mb->SetLineColor(kRed);
	grSystErrv2_2part200GeV_mb->SetLineWidth(LineWidth);

	v2_EventPlane->SetMarkerStyle(kOpenStar);
	v2_EventPlane->SetMarkerColor(kBlack);
	v2_EventPlane->SetLineColor(kBlack);
	v2_EventPlane->SetLineWidth(LineWidth);
	v2_EventPlane->SetMarkerSize(MarkerSize + 0.5);
	v2SystErr_EventPlane->SetLineColor(kBlack);

	v2_2part_nonflow->SetLineColor(kBlack);
	v2_2part_nonflow->SetFillColor(kGray);
	//v2_2part_nonflow->SetFillStyle(3356);

	// Print out data points
	cout << "v2{2} part, Au+Au 200 GeV min-bias" << endl;
	printData(v2_2part_mb, grSystErrv2_2part200GeV_mb);

	cout << "v2{EP} Au+Au 200 GeV Hight Tower" << endl;
	//printData(v2_EventPlane, v2SystErr_EventPlane);
	v2_EventPlane->Print();
	v2SystErr_EventPlane->Print();

	cout << "v2{2} Au+Au 200 GeV Hight Tower" << endl;
	printData(v2_2part_ht, grSystErrv2_2part200GeV_ht);

	cout << "v2{4} part, Au+Au 200 GeV min-bias" << endl;
	printData(v2_4part_mb, grSystErrv2_4part200GeV_mb);


	// plot nonflow for pt < 8 GeV
	for(int i = 0; i<v2_2part_nonflow->GetN();i++){
		if(v2_2part_nonflow->GetX()[i]>7.5){
			v2_2part_nonflow->RemovePoint(i);
		}
	}

	// shift points a bit
	for(int i = 0; i<v2_4part_mb->GetN();i++){
		v2_4part_mb->GetX()[i]+=0.06;
		grSystErrv2_4part200GeV_mb->GetX()[i]+=0.06;
	}

	for(int i = 0; i<v2_2part_ht->GetN();i++){
		v2_2part_ht->GetX()[i]-=0.06;
		grSystErrv2_2part200GeV_ht->GetX()[i]-=0.06;
	}

	// remove v2{4} points with pT>3 GeV -too large errors
	for(int i = 0; i<v2_4part_mb->GetN();i++){
		if(v2_4part_mb->GetX()[i]>3){
			v2_4part_mb->RemovePoint(i);
			grSystErrv2_4part200GeV_mb->RemovePoint(i);
			i--;
		}
	}


	for(int i = 0; i<v2_2part_mb->GetN();i++){
		if(v2_2part_mb->GetX()[i]>3){
			v2_2part_mb->RemovePoint(i);
			grSystErrv2_2part200GeV_mb->RemovePoint(i);

			i--;
		}
	}


	// remove v2{2} HT points with pT<2 GeV - trigger efficiency is very low
	for(int i = 0; i<v2_2part_ht->GetN();i++){
		if(v2_2part_ht->GetX()[i]<2){
			v2_2part_ht->RemovePoint(i);
			grSystErrv2_2part200GeV_ht->RemovePoint(i);
			i--;
		}
	}



	TCanvas* cPhoNpeVsPt = new TCanvas("cPhoNpeVsPt","cPhoNpeVsPt",800*1.1,600*1.1);
	TMultiGraph* mGrRes = new TMultiGraph();

	TMultiGraph* mGrResNonFlow = new TMultiGraph();


	if(!subtractNonflow){
		mGrRes->Add(v2_2part_nonflow,"3");
		mGrRes->Add(v2_2part_nonflow,"zlx");

		mGrResNonFlow->Add(v2_2part_nonflow,"3");
		mGrResNonFlow->Add(v2_2part_nonflow,"zlx");
	}

	if(addPhenix){
		mGrRes->Add(grV2PheStatErr,"zp");
		mGrRes->Add(grV2PheSystErr,"[]");
	}

	mGrRes->Add(v2_2part_mb,"zp");
	mGrRes->Add(grSystErrv2_2part200GeV_mb,"[]");
	mGrRes->Add(v2_4part_mb,"zp");
	mGrRes->Add(grSystErrv2_4part200GeV_mb,"[]");
	mGrRes->Add(v2_2part_ht,"zp");
	mGrRes->Add(grSystErrv2_2part200GeV_ht,"[]");
	mGrRes->Add(v2_EventPlane,"zp");
	mGrRes->Add(v2SystErr_EventPlane,"[]");

	mGrResNonFlow->Add(v2_2part_mb,"zp");
	mGrResNonFlow->Add(grSystErrv2_2part200GeV_mb,"[]");
	mGrResNonFlow->Add(v2_2part_ht,"zp");
	mGrResNonFlow->Add(grSystErrv2_2part200GeV_ht,"[]");
	mGrResNonFlow->Add(v2_EventPlane,"zp");
	mGrResNonFlow->Add(v2SystErr_EventPlane,"[]");


	mGrRes->Draw("a");
	gPad->Update();
	//mGrRes->GetYaxis()->SetTitle("Non-photonic electron v_{2}");
	mGrRes->GetYaxis()->SetTitle("e_{HF} v_{2}");
	mGrRes->GetYaxis()->SetTitleOffset(0.84);
	mGrRes->GetYaxis()->CenterTitle(1);
	mGrRes->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	mGrRes->GetXaxis()->SetLimits(Xmin,Xmax);
	mGrRes->GetYaxis()->SetRangeUser(Ymin,Ymax);

	TLine* lZero = new TLine(Xmin,0,Xmax,0);
	lZero->Draw();

	TLegend *leg1 = new TLegend(0.15,0.67,0.4,0.92);
	leg1->SetFillColor(0);
	leg1->SetTextFont(132); //Times-Roman
	leg1->SetMargin(0.12);
	leg1->SetTextSize(0.06);
	if(addPhenix){
	  //leg2->AddEntry(grV2PheStatErr,"PHENIX v_{2}{EP}, PRC 84, 044905","p");
		leg1->AddEntry(grV2PheStatErr,"PHENIX v_{2}{EP}","p");
	}
	leg1->AddEntry(v2_2part_mb,"v_{2}{2} min-bias","p");
	leg1->AddEntry(v2_4part_mb,"v_{2}{4} min-bias","p");
	leg1->AddEntry(v2_2part_ht,"v_{2}{2} High-Tower","p");
	leg1->AddEntry(v2_EventPlane,"v_{2}{EP}","p");
	leg1->AddEntry(v2_2part_nonflow,"non-flow (p+p data)","lf");
	//leg1->AddEntry(v2_2part_nonflow_pythia,"non-flow (PYTHIA)","lf");

	leg1->Draw("same");

	TLatex label;
	label.SetTextSize(0.06);
	label.DrawTextNDC(0.88,0.85,"(a)");
	label.DrawLatexNDC(0.55,0.25,"Au+Au #sqrt{s_{NN}}=200 GeV");
	label.DrawTextNDC(0.58,0.86,"0-60% centrality");




	TCanvas* cFlowNonFlow = new TCanvas("cFlowNonFlow","cFlowNonFlow",800*1.1,600*1.1);

	mGrResNonFlow->Draw("a");
	mGrResNonFlow->GetYaxis()->SetTitle("v_{2}");
	mGrResNonFlow->GetYaxis()->SetTitleOffset(0.85);
	mGrResNonFlow->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	mGrResNonFlow->GetXaxis()->SetLimits(Xmin,Xmax);
	mGrResNonFlow->GetYaxis()->SetRangeUser(Ymin,Ymax);

	lZero->Draw();

	TLegend *leg2 = new TLegend(0.15,0.67,0.4,0.92);
	leg2->SetFillColor(0);
	leg2->SetTextFont(132); //Times-Roman
	leg2->SetMargin(0.12);
	leg2->SetTextSize(0.06);

	leg2->AddEntry(v2_2part_mb,"v_{2}{2} min-bias","p");
	leg2->AddEntry(v2_2part_ht,"v_{2}{2} High-Tower","p");
	leg2->AddEntry(v2_EventPlane,"v_{2}{EP}","p");
	leg2->AddEntry(v2_2part_nonflow,"non-flow (p+p data)","lf");

	leg2->Draw("same");

}

void removeNonflow(TGraph* gr, TGraph* nonflow){

	float minPt = nonflow->GetX()[0] - 0.1;

	for(int i=0;i<gr->GetN();i++){
		if(gr->GetX()[i]> minPt){
			float val = nonflow->Eval(gr->GetX()[i]);
			gr->GetY()[i] -= val;
		}
	}
}
