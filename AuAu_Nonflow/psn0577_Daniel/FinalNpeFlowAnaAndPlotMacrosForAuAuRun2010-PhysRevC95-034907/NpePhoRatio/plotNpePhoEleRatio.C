/*
 * plotRes200GeV.C
 *
 *  Created on: Jul 15, 2012
 *      Author: dkikola
 */


void printData(TGraphErrors* v2Stat, TGraphErrors* v2syst){

	cout << "pt [GeV/c]\tS/B\tstat. err\tsyst.err" << endl;
	for(int i = 0; i<v2Stat->GetN();i++){
		cout << v2Stat->GetX()[i] << "\t" << v2Stat->GetY()[i] << "\t";
		cout << v2Stat->GetEY()[i] << "\t" << v2syst->GetEY()[i] << endl; 
	}
}


#include "style.C"

void plotNpePhoEleRatio(){

	gROOT->ForceStyle();
	setWindowDressing();

	int errXwidth  = 7; //the size of the lines at the end of the error bars
	gStyle->SetEndErrorSize(errXwidth);
	gStyle->SetErrorX(0);


	float Xmin = 0.0, Xmax = 8;
	float Ymin = 0.0, Ymax = 2;

	TString fname_200GeV = "NpePhoRatio/NpePhoRatio_AuAu200GeV_MB_0_60.root";
	TString fname_200GeV_ht = "NpePhoRatio/NpePhoRatio_AuAu200GeV_HT_0_60.root";

	TString fname_62GeV = "NpePhoRatio/NpePhoRatio_AuAu62GeV_MB_0_60.root";
	TString fname_39eV = "NpePhoRatio/NpePhoRatio_AuAu39GeV_MB_0_60.root";

	TFile* fin_200GeV = new TFile(fname_200GeV);
	TFile* fin_200GeV_ht = new TFile(fname_200GeV_ht);
	TFile* fin_62GeV = new TFile(fname_62GeV);
	TFile* fin_39GeV = new TFile(fname_39eV);

	TH1D* hRatio_200GeV = (TH1D*)fin_200GeV->Get("phoNpeRatio");
	TH1D* hRatio_200GeV_ht = (TH1D*)fin_200GeV_ht->Get("phoNpeRatio");
	TH1D* hRatio_62GeV = (TH1D*)fin_62GeV->Get("phoNpeRatio");
	TH1D* hRatio_39GeV = (TH1D*)fin_39GeV->Get("phoNpeRatio");

	TH1D* hRatio_sysErr_200GeV = (TH1D*)fin_200GeV->Get("phoNpeRatioSystErr");
	TH1D* hRatio_sysErr_200GeV_ht = (TH1D*)fin_200GeV_ht->Get("phoNpeRatioSystErr");
	TH1D* hRatio_sysErr_62GeV = (TH1D*)fin_62GeV->Get("phoNpeRatioSystErr");
	TH1D* hRatio_sysErr_39GeV = (TH1D*)fin_39GeV->Get("phoNpeRatioSystErr");

	TGraphErrors* ratio_200GeV = (TGraphErrors*)fin_200GeV->Get("grPhoNpeRatio");
	TGraphErrors* ratio_200GeV_ht = (TGraphErrors*)fin_200GeV_ht->Get("grPhoNpeRatio");
	TGraphErrors* ratio_62GeV = (TGraphErrors*)fin_62GeV->Get("grPhoNpeRatio");
	TGraphErrors* ratio_39GeV = (TGraphErrors*)fin_39GeV->Get("grPhoNpeRatio");


	TGraphErrors* ratio_sysErr_200GeV = (TGraphErrors*)fin_200GeV->Get("grPhoNpeRatioSystErr");
	TGraphErrors* ratio_sysErr_200GeV_ht = (TGraphErrors*)fin_200GeV_ht->Get("grPhoNpeRatioSystErr");
	TGraphErrors* ratio_sysErr_62GeV = (TGraphErrors*)fin_62GeV->Get("grPhoNpeRatioSystErr");
	TGraphErrors* ratio_sysErr_39GeV = (TGraphErrors*)fin_39GeV->Get("grPhoNpeRatioSystErr");


// Print out data points
	cout << "S/B, Au+Au 200 GeV min-bias" << endl;
	printData(ratio_200GeV, ratio_sysErr_200GeV);

	cout << "S/B, Au+Au 200 GeV high tower" << endl;
	printData(ratio_200GeV_ht, ratio_sysErr_200GeV_ht);

	cout << "S/B, Au+Au 62.4 GeV min-bias" << endl;
	printData(ratio_62GeV, ratio_sysErr_62GeV);

	cout << "S/B, Au+Au 39 GeV min-bias" << endl;
	printData(ratio_39GeV, ratio_sysErr_39GeV);







	ratio_200GeV->SetMarkerColor(kRed);
	ratio_200GeV->SetLineColor(kRed);
	ratio_200GeV->SetMarkerStyle(kFullCircle);
	ratio_sysErr_200GeV->SetLineColor(kRed);

	ratio_62GeV->SetMarkerColor(kBlack);
	ratio_62GeV->SetLineColor(kBlack);
	ratio_62GeV->SetMarkerStyle(kFullSquare);
	//ratio_62GeV->SetMarkerSize(MarkerSize+0.5);
	ratio_sysErr_62GeV->SetLineColor(kBlack);
	
	ratio_39GeV->SetMarkerStyle(kFullCircle);
	ratio_39GeV->SetMarkerColor(kRed);
	ratio_39GeV->SetLineColor(kRed);

	//ratio_39GeV->SetMarkerSize(2.);
	ratio_sysErr_39GeV->SetLineColor(kRed);

	ratio_200GeV_ht->SetLineColor(kBlack);
	ratio_200GeV_ht->SetMarkerColor(kBlack);
	ratio_200GeV_ht->SetMarkerStyle(kFullSquare);
	//ratio_200GeV_ht->SetMarkerSize(2.);
	ratio_sysErr_200GeV_ht->SetLineColor(kBlack);
	
	// shift points a bit
	/*
	for(int i = 0; i<ratio_62GeV->GetN();i++){
		ratio_62GeV->GetX()[i]+=0.06;
		ratio_sysErr_62GeV->GetX()[i]+=0.06;
	}
	*/
	
	
	for(int i = 0; i<ratio_39GeV->GetN();i++){
		ratio_39GeV->GetX()[i]+=0.01;
		ratio_sysErr_39GeV->GetX()[i]+=0.01;
	}
	

	// remove empty bins at high pt for 39 and 62 GeV
	for(int i = 0; i< ratio_39GeV->GetN();i++){
		if(ratio_62GeV->GetX()[i]>3){
			ratio_62GeV->RemovePoint(i);
			ratio_sysErr_62GeV->RemovePoint(i);
			ratio_39GeV->RemovePoint(i);
			ratio_sysErr_39GeV->RemovePoint(i);
			i--;
		}

	}


	for(int i = 0; i<ratio_200GeV_ht->GetN();i++){
		ratio_200GeV_ht->GetX()[i]+=0.03;
		ratio_sysErr_200GeV_ht->GetX()[i]+=0.03;
	}

	// remove v2{2} HT points with pT<2 GeV - trigger efficiency is very small
	for(int i = 0; i<ratio_200GeV_ht->GetN();i++){
		if(ratio_200GeV_ht->GetX()[i]<2){
			ratio_200GeV_ht->RemovePoint(i);
			ratio_sysErr_200GeV_ht->RemovePoint(i);
			i--;
		}
	}

	TLatex label;
	//label.SetTextSize(0.8);



	TCanvas* c200GeV = new  TCanvas("cPhoNpeVsPt200GeV","cPhoNpeVsPt200GeV",800,600);
	ratio_200GeV->Draw("zap");
	ratio_sysErr_200GeV->Draw("[]");
	ratio_200GeV_ht->Draw("zp same");
	ratio_sysErr_200GeV_ht->Draw("[]");
	ratio_200GeV->GetXaxis()->SetLimits(Xmin,Xmax);
	ratio_200GeV->GetYaxis()->SetRangeUser(Ymin,Ymax);
	ratio_200GeV->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	ratio_200GeV->GetYaxis()->SetTitle("Signal/Background");

	TLegend *leg = new TLegend(0.15,0.75,0.4,0.92);
	leg->SetFillStyle(0);
	leg->SetTextFont(132); //Times-Roman
	leg->SetMargin(0.2);
	leg->SetTextSize(0.06);
	leg->AddEntry(ratio_200GeV,"200 GeV min-bias","p");
	leg->AddEntry(ratio_200GeV_ht,"200 GeV High-Tower","p");
	leg->Draw("same");

	label.DrawTextNDC(0.88,0.85,"(a)");

	TCanvas* cLowEnergy = new  TCanvas("cPhoNpeVsPtLowEnergy","cPhoNpeVsPtLowEnergy",800,600);
	ratio_39GeV->Draw("azp");
	ratio_sysErr_39GeV->Draw("[]");
	ratio_62GeV->Draw("zp same");
	ratio_sysErr_62GeV->Draw("[]");

	ratio_39GeV->GetXaxis()->SetLimits(0,3.);
	ratio_39GeV->GetYaxis()->SetRangeUser(Ymin,1.);
	ratio_39GeV->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	ratio_39GeV->GetYaxis()->SetTitle("Signal/Background");


	TLegend *leg2 = new TLegend(0.15,0.75,0.4,0.92);
	leg2->SetFillStyle(0);
	leg2->SetTextFont(132); //Times-Roman
	leg2->SetMargin(0.2);
	leg2->SetTextSize(0.06);
	leg2->AddEntry(ratio_62GeV,"62.4 GeV","p");
	leg2->AddEntry(ratio_39GeV,"39 GeV","p");
	leg2->Draw("same");

	label.DrawTextNDC(0.88,0.85,"(b)");




	// put all data on the same plot
	ratio_62GeV->SetMarkerColor(kGreen+2);
	ratio_62GeV->SetLineColor(kGreen+2);
	ratio_62GeV->SetMarkerStyle(kFullTriangleDown);
	//ratio_62GeV->SetMarkerSize(MarkerSize+0.5);
	ratio_sysErr_62GeV->SetLineColor(kGreen+2);

	ratio_39GeV->SetMarkerStyle(kFullDiamond);
	ratio_39GeV->SetMarkerSize(MarkerSize+0.5);
	ratio_39GeV->SetMarkerColor(kBlue);
	ratio_39GeV->SetLineColor(kBlue);
	ratio_sysErr_39GeV->SetLineColor(kBlue);



	TCanvas* cAllEnergy = new  TCanvas("cAllEnergy","cAllEnergy",800,600);
	ratio_200GeV->Draw("zap");
	ratio_sysErr_200GeV->Draw("[]");
	ratio_200GeV_ht->Draw("zp same");
	ratio_sysErr_200GeV_ht->Draw("[]");
	ratio_39GeV->Draw("zp same");
	ratio_sysErr_39GeV->Draw("[]");
	ratio_62GeV->Draw("zp same");
	ratio_sysErr_62GeV->Draw("[]");

	ratio_200GeV->GetXaxis()->SetLimits(Xmin,Xmax);
	ratio_200GeV->GetYaxis()->SetRangeUser(Ymin,Ymax);
	ratio_200GeV->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	ratio_200GeV->GetYaxis()->SetTitle("Signal/Background");

	label.DrawTextNDC(0.5,0.25,"0-60% centrality");


	TLegend *leg3 = new TLegend(0.15,0.6,0.4,0.92);
	leg3->SetFillStyle(0);
	leg3->SetTextFont(132); //Times-Roman
	leg3->SetMargin(0.1);
	leg3->SetTextSize(0.055);
	leg3->SetHeader("Au+Au collisions");
	leg3->AddEntry(ratio_200GeV_ht,"#sqrt{s_{NN}}=200 GeV High-Tower","p");
	leg3->AddEntry(ratio_200GeV,"#sqrt{s_{NN}}=200 GeV Min-Bias","p");
	leg3->AddEntry(ratio_62GeV,"#sqrt{s_{NN}}=62.4 GeV Min-Bias","p");
	leg3->AddEntry(ratio_39GeV,"#sqrt{s_{NN}}=39 GeV Min-Bias","p");
	leg3->Draw("same");




}

