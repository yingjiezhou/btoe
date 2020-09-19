/*
 * plotRes200GeV.C
 *
 *  Created on: Jul 15, 2012
 *      Author: dkikola
 */


#include "style.C"

void plotRes200GeVWithModels(bool addPhenix = false) {


	gROOT->ForceStyle();
	setWindowDressing();
	//flowPlotsStyle->SetPadRightMargin(0.32);

	int errXwidth  = 6; //the size of the lines at the end of the error bars
	gStyle->SetEndErrorSize(errXwidth);

	float Xmin = 0.0, Xmax = 4.0;
	float Ymin = -0.01, Ymax = 0.2;

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

	TFile* fSystErr2part_200GeV_mb = new TFile(v2_2part_200GeV_mb_syst_err_fname);
	TFile* fSystErr4part_200GeV_mb = new TFile(v2_4part_200GeV_mb_syst_err_fname);
	TFile* fSystErr2part_200GeV_ht = new TFile(v2_2part_200GeV_ht_syst_err_fname);

    TGraphErrors* v2_2part_mb = (TGraphErrors*)f2part_mb->Get("v2NpeVsPts");
    TGraphErrors* v2_4part_mb = (TGraphErrors*)f4part_mb->Get("v2NpeVsPts");
    TGraphErrors* v2_2part_ht = (TGraphErrors*)f2part_ht->Get("v2NpeVsPts");

    TGraphAsymmErrors* grSystErrv2_2part200GeV_mb = (TGraphAsymmErrors*)fSystErr2part_200GeV_mb->Get("v2NpeSystErrVsPt");
    TGraphAsymmErrors* grSystErrv2_4part200GeV_mb = (TGraphAsymmErrors*)fSystErr4part_200GeV_mb->Get("v2NpeSystErrVsPt");
    TGraphAsymmErrors* grSystErrv2_2part200GeV_ht = (TGraphAsymmErrors*)fSystErr2part_200GeV_ht->Get("v2NpeSystErrVsPt");

    TGraphErrors* grV2PheStatErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_stat.err.txt");
    TGraphErrors* grV2PheSystErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_sys.err.txt");

    // models
    TGraph* grVanHess = new TGraph("data/Models/t-matrix-wong-potential-v2-rhic-minbias.dat");
    TGraph* grMinHe = new TGraph("data/Models/tamu.txt");
    TGraph* grBAMPS = new TGraph("data/Models/BAMPS_hf_electron_v2_pt_rhic200_0_60_centrality.dat");
    TGraph* grBAMPS_heavy_quark = new TGraph("data/Models/BAMPS_heavy_quarks_v2_pt_rhic200_0_60_centrality.dat");

   TGraph* grGossiaux = new TGraph("data/Models/v2_col_and_rad_eloss_Gossiaux.txt");


    grVanHess->SetLineWidth(3);
    grVanHess->SetLineColor(kRed);
    grVanHess->SetLineStyle(9);

    grBAMPS->SetLineWidth(3);
    grBAMPS->SetLineColor(kBlue);
    grBAMPS->SetLineStyle(10);

    grBAMPS_heavy_quark->SetLineWidth(3);
    grBAMPS_heavy_quark->SetLineColor(kMagenta);
    grBAMPS_heavy_quark->SetLineStyle(3);

    grGossiaux->SetLineWidth(3);
    grGossiaux->SetLineColor(kTeal+4);
    grGossiaux->SetLineStyle(6);

    grMinHe->SetLineWidth(3);
    grMinHe->SetLineColor(kBlack);

    v2_4part_mb->SetLineColor(kBlack);
    v2_4part_mb->SetMarkerColor(kBlack);
    v2_4part_mb->SetMarkerStyle(kFullCircle);
    grSystErrv2_4part200GeV_mb->SetLineColor(kBlack);
/*
    v2_2part_ht->SetLineColor(kGreen+3);
    v2_2part_ht->SetMarkerColor(kGreen+3);
    v2_2part_ht->SetMarkerStyle(kFullStar);
    v2_2part_ht->SetMarkerSize(MarkerSize + 0.5);
*/
    v2_2part_ht->SetLineColor(kRed);
    v2_2part_ht->SetMarkerColor(kRed);
    v2_2part_ht->SetMarkerStyle(kFullSquare);
    grSystErrv2_2part200GeV_ht->SetLineColor(kRed);

    v2_2part_mb->SetLineColor(kRed);
    v2_2part_mb->SetMarkerColor(kRed);
    v2_2part_mb->SetMarkerStyle(kFullSquare);

	grSystErrv2_2part200GeV_mb->SetLineColor(kRed);
	grSystErrv2_2part200GeV_mb->SetLineWidth(LineWidth);

	// shift points a bit
	for(int i = 0; i<v2_4part_mb->GetN();i++){
		v2_4part_mb->GetX()[i]+=0.06;
		grSystErrv2_4part200GeV_mb->GetX()[i]+=0.06;
	}

	for(int i = 0; i<v2_2part_ht->GetN();i++){
		v2_2part_ht->GetX()[i]-=0.06;
		grSystErrv2_2part200GeV_ht->GetX()[i]-=0.06;
	}

	// remove v2{4} points with pT>1 GeV/c -too large errors
	for(int i = 5; i<v2_4part_mb->GetN();i++){
		v2_4part_mb->SetPoint(i,-1,0);
		grSystErrv2_4part200GeV_mb->SetPoint(i,-1,0);
	}


	for(int i = 8; i<v2_2part_mb->GetN();i++){
	      v2_2part_mb->SetPoint(i,-1,0);
	      grSystErrv2_2part200GeV_mb->SetPoint(i,-1,0);
	}

	// remove v2{2} HT points with pT<2 GeV/c - trigger efficiency is very small
	for(int i = 0; i<4;i++){
		v2_2part_ht->SetPoint(i,-1,0);
		grSystErrv2_2part200GeV_ht->SetPoint(i,-1,0);
	}


	TMultiGraph* v2vsPt = new TMultiGraph();

	TCanvas* cPhoNpeVsPt = new TCanvas("cPhoNpeVsPt","cPhoNpeVsPt",800,600);
	cPhoNpeVsPt->SetLeftMargin(0.13);

	if (addPhenix) {
		v2vsPt->Add(grV2PheStatErr,"zp ");
		v2vsPt->Add(grV2PheSystErr,"[]");
	}

	v2vsPt->Add(v2_2part_mb,"zp ");
	v2vsPt->Add(grSystErrv2_2part200GeV_mb,"[]");

	v2vsPt->Add(v2_4part_mb,"zp ");
	v2vsPt->Add(grSystErrv2_4part200GeV_mb,"[]");

	//v2vsPt->Add(grVanHess,"l ");
	v2vsPt->Add(grMinHe,"l ");
	v2vsPt->Add(grBAMPS,"l ");
	v2vsPt->Add(grGossiaux,"l ");
	v2vsPt->Add(grBAMPS_heavy_quark,"l ");

	v2vsPt->Draw("a");


	float yLow = 0.67;

    TLegend *leg2 = new TLegend(0.15, 0.57, 0.3, 0.69);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->SetTextFont(132); //Times-Roman
	//leg2->SetMargin(0.15);
	leg2->SetTextSize(0.06);


	gPad->Update();
	//v2vsPt->GetYaxis()->SetTitle("Non-photonic electron v_{2}");
	v2vsPt->GetYaxis()->SetTitle("e_{HF} v_{2}");

	v2vsPt->GetYaxis()->SetTitleOffset(0.84);
	v2vsPt->GetYaxis()->CenterTitle(1);
	//v2vsPt->GetYaxis()->SetTitle("v_{2}");
	//v2vsPt->GetYaxis()->SetTitleOffset(0.85);
	v2vsPt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	v2vsPt->GetXaxis()->SetLimits(Xmin, Xmax);
	v2vsPt->GetYaxis()->SetRangeUser(Ymin, Ymax);

	TLine* lZero = new TLine(Xmin, 0, Xmax, 0);
	lZero->Draw();

	if(addPhenix){
	  //leg2->AddEntry(grV2PheStatErr,"PHENIX v_{2}{EP}, PRC 84, 044905","p");
		leg2->AddEntry(grV2PheStatErr,"PHENIX v_{2}{EP} 0-60%","p");
	}

	leg2->AddEntry(v2_2part_mb,"v_{2}{2}","p");
	leg2->AddEntry(v2_4part_mb,"v_{2}{4}","p");

	TLegend *legModel = new TLegend(0.15, 0.7, 0.5, 0.93);
	legModel->SetFillColor(0);
	legModel->SetFillStyle(0);
	legModel->SetTextFont(132); //Times-Roman
	//legModel->SetMargin(0.1);
	legModel->SetTextSize(0.044);

	//legModel->AddEntry(grVanHess,"van Hees et al. PRL 100, 192301(min-bias)","l");
	//legModel->AddEntry(grMinHe,"He et al. PRC 86, 014903 (min-bias)","l");
	legModel->AddEntry(grMinHe,"He et al.","l");
	//legModel->AddEntry(grBAMPS,"Uphoff et al. arXiv:1205.4945 (0-60%)","l");
	legModel->AddEntry(grBAMPS,"BAMPS e","l");
	legModel->AddEntry(grBAMPS_heavy_quark,"BAMPS heavy quark","l");

	//legModel->AddEntry(grGossiaux,"#splitline{Gossiaux et al. (0-60%)}{J. Phys. G: Nucl. Part. Phys. 37 094019}","l");
	legModel->AddEntry(grGossiaux,"Gossiaux et al.","l");

	legModel->Draw("same");

	TLatex label;
	label.SetTextSize(0.06);
	label.DrawLatexNDC(0.55,0.87,"Au+Au #sqrt{s_{NN}}=200 GeV");
	label.DrawTextNDC(0.55,0.79,"0-60% centrality");


	leg2->Draw("same");


	f2part_mb->Close();
	f4part_mb->Close();
	f2part_ht->Close();

	fSystErr2part_200GeV_mb->Close();
	fSystErr4part_200GeV_mb->Close();
	fSystErr2part_200GeV_ht->Close();

	return;
}
