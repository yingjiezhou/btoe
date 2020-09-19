/*
 * plotRes200GeV.C
 *
 *  Created on: Jul 15, 2012
 *      Author: dkikola
 */

#include "style.C"

//Phenix NPE v2 data for 20-40% central Au+Au 26.4 GeV collisions, read from Fig. 24 in http://journals.aps.org/prc/abstract/10.1103/PhysRevC.91.044907
const int NphenixPts = 6;
double v2_phenix_62GeV_pt[NphenixPts] = {1.1537,1.4563,1.7589,2.0520,	2.3546,	3.2530};
double v2_phenix_62GeV[NphenixPts] = {0.0265,0.0563,0.0778,	0.0679,	0.3427,	0.2070};

double v2_phenix_62GeV_statUp[NphenixPts] = {0.0265,0.0381,0.0546,0.0762,0.1093,0.1076};
double v2_phenix_62GeV_statLow[NphenixPts] = {0.0315,	0.0364,	0.0546,	0.0778,	0.1142,0.1126};
double v2_phenix_62GeV_systUp[NphenixPts] = {0.0546,	0.0381,	0.0298,	0.0248,	0.0497,	0.0182};
double v2_phenix_62GeV_systLow[NphenixPts] = {0.1258,	0.0728,	0.0563,	0.0530,	0.0563,	0.0613};

void plotRes39_62GeV(bool addPhenix = false){

	setWindowDressing();
	gROOT->ForceStyle();

	int errXwidth  = 6; //the size of the lines at the end of the error bars 
	gStyle->SetEndErrorSize(errXwidth);
	
	float Xmin = 0., Xmax = 2.;
	float Ymin = -0.1, Ymax = 0.2;

	TString v2_2part_39GeV_fname = "data/NpeFlow/v2_2part_MB_AuAu39GeV-2016-04-17.root";
	TString v2_2part_62GeV_fname = "data/NpeFlow/v2_2part_MB_AuAu62GeV-2016-04-14.root";
	TString v2_2part_200GeV_fname = "data/NpeFlow/v2_2part_MB_AuAu200GeV-2016-05-05.root";

	TFile* f2part_39GeVmb = new TFile(v2_2part_39GeV_fname);
	TFile* f2part_62GeVmb = new TFile(v2_2part_62GeV_fname);
	TFile* f2part_200GeVmb = new TFile(v2_2part_200GeV_fname);

	TGraphErrors* v2_2part_200GeVmb = (TGraphErrors*)f2part_200GeVmb->Get("v2NpeVsPts");
	TGraphErrors* v2_2part_62GeVmb = (TGraphErrors*)f2part_62GeVmb->Get("v2NpeVsPts");
	TGraphErrors* v2_2part_39GeVmb = (TGraphErrors*)f2part_39GeVmb->Get("v2NpeVsPts");

	TGraphAsymmErrors* grSystErr39GeV = (TGraphAsymmErrors*)f2part_39GeVmb->Get("v2NpeSystErrVsPt");
	TGraphAsymmErrors* grSystErr62GeV = (TGraphAsymmErrors*)f2part_62GeVmb->Get("v2NpeSystErrVsPt");
	TGraphAsymmErrors* grSystErr200GeV = (TGraphAsymmErrors*)f2part_200GeVmb->Get("v2NpeSystErrVsPt");

	TGraphAsymmErrors* grStatErrPhenix62GeV = new TGraphAsymmErrors(NphenixPts,v2_phenix_62GeV_pt,v2_phenix_62GeV,0,0,v2_phenix_62GeV_statLow,v2_phenix_62GeV_statUp);
	TGraphAsymmErrors* grSystErrPhenix62GeV = new TGraphAsymmErrors(NphenixPts,v2_phenix_62GeV_pt,v2_phenix_62GeV,0,0,v2_phenix_62GeV_systLow,v2_phenix_62GeV_systUp);

    TGraphErrors* grV2PheStatErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_stat.err.txt");
    TGraphErrors* grV2PheSystErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_sys.err.txt");
	grV2PheStatErr->SetMarkerStyle(kOpenCircle);
	grV2PheStatErr->SetMarkerColor(kBlue);
	grV2PheStatErr->SetLineWidth(LineWidth);
	grV2PheStatErr->SetLineColor(kBlue);
	grV2PheSystErr->SetLineColor(kBlue);
	grV2PheSystErr->SetLineWidth(LineWidth);



	v2_2part_39GeVmb->SetLineColor(kBlack);
	v2_2part_39GeVmb->SetMarkerColor(kBlack);
	v2_2part_39GeVmb->SetMarkerStyle(kFullCircle);
	
	v2_2part_62GeVmb->SetLineColor(kBlue);
	v2_2part_62GeVmb->SetMarkerColor(kBlue);
	//v2_2part_62GeVmb->SetMarkerStyle(kFullTriangleDown);
	v2_2part_62GeVmb->SetMarkerStyle(kFullDiamond);
	v2_2part_62GeVmb->SetMarkerSize(2.5);
	grSystErr62GeV->SetLineColor(kBlue);

	v2_2part_200GeVmb->SetLineColor(kRed);
	v2_2part_200GeVmb->SetMarkerColor(kRed);
	v2_2part_200GeVmb->SetMarkerStyle(kFullSquare);
	grSystErr200GeV->SetLineColor(kRed);


	grStatErrPhenix62GeV->SetMarkerStyle(kOpenCircle);
	grStatErrPhenix62GeV->SetMarkerColor(kGreen+2);
	grStatErrPhenix62GeV->SetLineColor(kGreen+3);
	grStatErrPhenix62GeV->SetLineWidth(3);
	grSystErrPhenix62GeV->SetLineColor(kGreen+3);
	grSystErrPhenix62GeV->SetLineWidth(3);

	// shift points a bit
	for(int i = 0; i<v2_2part_39GeVmb->GetN();i++){
		v2_2part_39GeVmb->GetX()[i]+=0.03;
		grSystErr39GeV->GetX()[i]+=0.03;
	}

	for(int i = 0; i<v2_2part_62GeVmb->GetN();i++){
		v2_2part_62GeVmb->GetX()[i]-=0.03;
		grSystErr62GeV->GetX()[i]-=0.03;
	}

	TCanvas* cPhoNpeVsPt = new  TCanvas("cPhoNpeVsPt","cPhoNpeVsPt",800,600);
	cPhoNpeVsPt->SetLeftMargin(0.13);

	v2_2part_62GeVmb->Draw("zap");
	if(addPhenix){
		//grStatErrPhenix62GeV->Draw("zp same");
		grV2PheStatErr->Draw("zp same");
		grV2PheSystErr->Draw("[]");
		//grSystErrPhenix62GeV->Draw("[]");
	}
	v2_2part_39GeVmb->Draw("zp same");
	v2_2part_200GeVmb->Draw("zp same");

	grSystErr39GeV->Draw("[]");
	grSystErr62GeV->Draw("[]");
	grSystErr200GeV->Draw("[]");

	v2_2part_62GeVmb->GetYaxis()->SetTitle("v_{2}{2}");
	v2_2part_62GeVmb->GetYaxis()->SetTitle("Non-photonic electron v_{2}");
	v2_2part_62GeVmb->GetYaxis()->SetNdivisions(505);
	v2_2part_62GeVmb->GetYaxis()->CenterTitle(1);

	v2_2part_62GeVmb->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	v2_2part_62GeVmb->GetXaxis()->SetLimits(Xmin,Xmax);
	v2_2part_62GeVmb->GetYaxis()->SetRangeUser(Ymin,Ymax);

	TLine* lZero = new TLine(Xmin,0,Xmax,0);
	lZero->Draw();

	TLegend *leg2 = new TLegend(0.15,0.62,0.6,0.94);
	leg2->SetFillStyle(0);
	leg2->SetTextFont(132); //Times-Roman
	leg2->SetMargin(0.08);
	leg2->SetTextSize(0.05);
	leg2->SetHeader("Au+Au collisions");
	//if(addPhenix)leg2->AddEntry(grStatErrPhenix62GeV,"v_{2}{EP}, PHENIX, #sqrt{s_{NN}}=62.4 GeV, 20-40% cent.","p");
	if(addPhenix)leg2->AddEntry(grV2PheStatErr,"v_{2}{EP}, PHENIX, #sqrt{s_{NN}}=200 GeV","p");
	leg2->AddEntry(v2_2part_200GeVmb,"v_{2}{2}, #sqrt{s_{NN}}=200 GeV","p");
	leg2->AddEntry(v2_2part_62GeVmb,"v_{2}{2}, #sqrt{s_{NN}}=62.4 GeV","p");
	leg2->AddEntry(v2_2part_39GeVmb,"v_{2}{2}, #sqrt{s_{NN}}=39 GeV","p");

	leg2->Draw("same");

	TLatex label;
	label.DrawTextNDC(0.88,0.85,"(b)");
	label.DrawTextNDC(0.15,0.185,"0-60% centrality");

}



