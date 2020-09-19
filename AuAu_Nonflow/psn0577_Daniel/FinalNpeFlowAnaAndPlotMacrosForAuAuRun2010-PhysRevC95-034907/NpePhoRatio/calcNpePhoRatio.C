 /*
 * calcNpeFlow.C
 *
 *  Created on: Nov 11, 2011
 *      Author: dkikola
 */

#include <TFile.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <iostream>
#include <math.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>
#include <TLine.h>

using namespace std;

#include "style.C"


void calcV2_4part(TFile* fin, int CentClass, TH1D* phoIncdNdpT,  TH1D* ul_ele_pT, TH1D* ls_ele_pT);

TH2F *getHistSum2D(const Char_t *basename, const UShort_t min, const UShort_t max)
{
        TH2F *hist = NULL;

        for (UShort_t nc = min; nc <= max; ++nc) {
                /* Generate the histogram's name from base + current class number */
                ostringstream sst;
                sst << basename << '_';
                //sst.fill('0');
                sst.width(1);
                sst << nc;
                const Char_t *fullname = sst.str().c_str();

                /* If there is an object to process, process it */
                cout << fullname << ":\t";
                TObject *get = gDirectory->Get(fullname);
                if (get != NULL)
                        if (hist == NULL) {
                                cout << "cloning";
                                hist = (TH2F *)(get->Clone(basename));
                                hist->Sumw2();
                        } else {
                                cout << "adding";
                                hist->Add((TH2F *)(get));
                        }
                else
                        cout << "not found";
                cout << '\n';
        }
        cout << endl;

        return hist;
}

TH1F *getHistSum1D(const Char_t *basename, const UShort_t min, const UShort_t max)
{
        TH1F *hist = NULL;

        for (UShort_t nc = min; nc <= max; ++nc) {
                /* Generate the histogram's name from base + current class number */
                ostringstream sst;
                sst << basename << '_';
                //sst.fill('0');
                sst.width(1);
                sst << nc;
                const Char_t *fullname = sst.str().c_str();

                /* If there is an object to process, process it */
                cout << fullname << ":\t";
                TObject *get = gDirectory->Get(fullname);
                if (get != NULL)
                        if (hist == NULL) {
                                cout << "cloning";
                                hist = (TH1F *)(get->Clone(basename));
                                hist->Sumw2();
                        } else {
                                cout << "adding";
                                hist->Add((TH1F *)(get));
                        }
                else
                        cout << "not found";
                cout << '\n';
        }
        cout << endl;

        return hist;
}



void removeBinsWithBadPurity(TGraph* gr){

	// remove points with pT < 0.2 GeV/c
	for(int i = 0; i<gr->GetN();i++){
		if(gr->GetX()[i]<0.2){
			gr->RemovePoint(i);
			i--;
		}
	}

	// Remove points with large syst. error due to purity (overlap with protons and kaons) 

		for(int i = 0; i<gr->GetN();i++){
			if((gr->GetX()[i]<1.2 && gr->GetX()[i]>0.7) || (gr->GetX()[i]<0.6 && gr->GetX()[i]>0.4)){
				gr->RemovePoint(i);
				i--;
			}
		}
	
	

}

void calcNpePhoRatio(int energy=200, TString trigger = "MB", const char* outFileNam = "results.root", int CentClassMin = 0, int CentClassMax = 0, float Xmin =0.2, float Xmax = 4., float Ymin = -0.05, float Ymax = 0.25 ){

	
    gStyle->SetPalette(1, 0);
    setWindowDressing();

    gROOT->ForceStyle(); //.. force objects to use current style

	TH1D* phoIncdNdpT;
	TH1D* ul_ele_pT;
	TH1D* ls_ele_pT;
	TH1D* phoEledNdpT;
	
	const int npt = 12;
	float pt_bins[npt] = {0};
	
	TString inSpectraFileName;
	TString inEffFileName;
	TString inPurityFileName;
	TString inKe3ToNpeRatio;
	
	// Au+Au 200 GeV min-bias
	if(energy==200){

		float tmp_200[npt] = {0.1, 0.279,0.467678,0.623067,0.861229,1.31974,1.6027,1.85453,2.40745,4.5621,6.8011,8.50316};

		for(int i = 0;i<npt;i++)
				pt_bins[i] = tmp_200[i];

		// min-bias
		if(trigger=="MB"){
			inSpectraFileName = "../CalcNpeFlow/data/DataForNpeStudy/ElectronV2/AuAu200GeV_MB/Moments/NpeV2-2part-MomentsAuAu200GeV-2016-05-05.root";
		}

		// st_ht events
		if(trigger=="HT"){
			inSpectraFileName = "../CalcNpeFlow/data/DataForNpeStudy/ElectronV2/AuAu200GeV_ST_HT/Moments/v2_ele_AuAu200GeV_st_ht.root";
		}

		inEffFileName = "../CalcNpeFlow/data/DataForNpeStudy/EffPurity/phoRecoEffVsPt_AuAu200GeV_0_60_withTotalErr.root"; // 200 GeV
		inPurityFileName =  "../CalcNpeFlow/data/DataForNpeStudy/EffPurity/purity_AuAu200GeV_CalculatedVsPconvertedToPt.root";
		inKe3ToNpeRatio = "../CalcNpeFlow/data/DataForNpeStudy/Ke3/Ke3ToNpeRatio_AuAu200GeV.root";

	}
	else if(energy==62){

		const int npt_62 = 10;
		float tmp_bins_62[npt_62] = {0.1,0.279,0.467678,0.623067,0.861229,1.43325,2.30294,3.3468,4.5621,6.8011};

		for(int i = 0;i<npt;i++)
				pt_bins[i] = tmp_bins_62[i];

		// Au+Au 62 GeV MB events
		inSpectraFileName = "../CalcNpeFlow/data/DataForNpeStudy/ElectronV2/AuAu62GeV_MB/Moments/NpeV2-2part-MomentsAuAu62GeV-2016-04-14.root";
		inEffFileName = "../CalcNpeFlow/data/DataForNpeStudy/EffPurity/phoRecoEffVsPt_AuAu62GeV_0_60_withTotalErr.root";
		inPurityFileName =  "../CalcNpeFlow/data/DataForNpeStudy/EffPurity/purity_AuAu62GeV_CalculatedVsPconvertedToPt.root";	// 62 GeV
		inKe3ToNpeRatio = "../CalcNpeFlow/data/DataForNpeStudy/Ke3/Ke3ToNpeRatio_AuAu62GeV.root";

	} else if(energy==39){

		const int npt_62 = 10;
		float tmp_bins_62[npt_62] = {0.1,0.279,0.467678,0.623067,0.861229,1.43325,2.30294,3.3468,4.5621,6.8011};

		for(int i = 0;i<npt;i++)
				pt_bins[i] = tmp_bins_62[i];

		// Au+Au 39 GeV MB events
		inSpectraFileName = "../CalcNpeFlow/data/DataForNpeStudy/ElectronV2/AuAu39GeV_MB/Moments/NpeV2-2part-MomentsAuAu39GeV-2016-04-15.root";
		inEffFileName = "../CalcNpeFlow/data/DataForNpeStudy/EffPurity/phoRecoEffVsPt_AuAu39GeV_0_60_withTotalErr.root";
		inPurityFileName =  "../CalcNpeFlow/data/DataForNpeStudy/EffPurity/purity_AuAu39GeV_CalculatedVsPconvertedToPt.root";	// 62 GeV
		inKe3ToNpeRatio = "../CalcNpeFlow/data/DataForNpeStudy/Ke3/Ke3ToNpeRatio_AuAu39GeV.root";

	}


	TFile* inEffFile = new TFile(inEffFileName);
	TFile* inPurityFile = new TFile(inPurityFileName);
	TFile* inKe3ToNpeRatioFile = new TFile(inKe3ToNpeRatio);

	TGraphErrors* effFit;
	TGraph* purityVsPt;
	TGraph* purityVsPtMax;
	TGraph* purityVsPtMin;
	TGraph* effFitError;

	TGraphErrors* Ke3ToNpeRatio = (TGraphErrors*)inKe3ToNpeRatioFile->Get("grKe3NpeRatio");
	TGraphErrors* Ke3ToNpeRatioError = (TGraphErrors*)inKe3ToNpeRatioFile->Get("grKe3NpeRatio_error");



	effFit= (TGraphErrors*)inEffFile->Get("phoRecoEffVsPt_0_60");
	effFitError = (TGraph*)inEffFile->Get("grSystErr_0_60");

	purityVsPt = (TGraph*)inPurityFile->Get("grPrityMeanVal");  //grPrityMeanVal or grPrityMaxVal or grPrityMinVal
	purityVsPtMax = (TGraph*)inPurityFile->Get("grPrityMaxVal");
	purityVsPtMin = (TGraph*)inPurityFile->Get("grPrityMinVal");


	TFile* inSpectraFile = new TFile(inSpectraFileName);

	char* histName = new char[100];
	TH1F* hVz = (TH1F*)inSpectraFile->Get("QA_histogrmas/hVz_0");
	TH2F* inc_ele_pT_vs_eta = (TH2F*)inSpectraFile->Get("QA_histogrmas/ele_pT_vs_eta_0");
	TH2F* ul_ele_pT_vs_eta = (TH2F*)inSpectraFile->Get("QA_histogrmas/ul_ele_pT_vs_eta_0");
	TH2F* ls_ele_pT_vs_eta = (TH2F*)inSpectraFile->Get("QA_histogrmas/ls_ele_pT_vs_eta_0");

	int nEvents = hVz->GetEntries();
	cout << "No. of events: " << nEvents << endl;
	if(nEvents ==0)nEvents =1;

	if (!inc_ele_pT_vs_eta || !inc_ele_pT_vs_eta || !ls_ele_pT_vs_eta) {
		cout << "missing data, aborting";
		return;
	}

	phoIncdNdpT  = inc_ele_pT_vs_eta->ProjectionX("phoIncdNdpT");
	ul_ele_pT = ul_ele_pT_vs_eta->ProjectionX("ul_ele_pT");
	ls_ele_pT = ls_ele_pT_vs_eta->ProjectionX("ls_ele_pT");
	phoEledNdpT = (TH1D*)ul_ele_pT->Clone("phoEledNdpT");
	
	phoEledNdpT->Add(ls_ele_pT,-1.);

	TH1D* pho_ele_syst_err = (TH1D*)phoEledNdpT->Clone("pho_ele_syst_err");
	TH1D* inc_ele_syst_err = (TH1D*)phoIncdNdpT->Clone("pho_ele_syst_err");

	
	//scale photonic electron by efficiency, bin by bin
	for(int bin = 1; bin < phoEledNdpT->GetNbinsX(); ++bin){
			float pT =  pt_bins[bin-1]; //phoEledNdpT->GetBinCenter(bin);
			float pho = phoEledNdpT->GetBinContent(bin);
			float phoErr = phoEledNdpT->GetBinError(bin);
			float eff = effFit->Eval(pT);

			float effErr = eff*effFitError->Eval(pT);

			phoEledNdpT->SetBinContent(bin,pho/eff);
			phoEledNdpT->SetBinError(bin,phoErr/eff);

			pho_ele_syst_err->SetBinContent(bin,pho/eff);
			pho_ele_syst_err->SetBinError(bin,pho*effErr/pow(eff,2));



		}

	// scale inclusive electron dN/dpT by purity
	TH1D* rawdNdpt = (TH1D*)phoIncdNdpT->Clone("rawdNdpt");
	
	for(int bin = 1; bin < phoIncdNdpT->GetNbinsX(); ++bin){

			float pT =  pt_bins[bin-1]; //phoIncdNdpT->GetBinCenter(bin);
			float ele = phoIncdNdpT->GetBinContent(bin);
			float eleErr = phoIncdNdpT->GetBinError(bin);
			float purity = purityVsPt->Eval(pT);


	
			phoIncdNdpT->SetBinContent(bin,purity*ele);
			phoIncdNdpT->SetBinError(bin,purity*eleErr);

			// estimate symetrized error on purity: this can be either max deviation, algegraic or geometrical mean.
			float purityMaxErr = purityVsPtMax->Eval(pT) - purity;
			float purityMinErr = purity - purityVsPtMin->Eval(pT);
			float purityErr = 0.5*(purityMaxErr + purityMinErr);

			inc_ele_syst_err->SetBinContent(bin,purity*ele);
			inc_ele_syst_err->SetBinError(bin,ele*purityErr);

	}


	TH1D* purityCheck =  (TH1D*)phoIncdNdpT->Clone("purityCheck");
	purityCheck->Divide(rawdNdpt);

	TH1D* npedNdpt = (TH1D*)phoIncdNdpT->Clone("npedNdpt");
	TH1D* npedNdptSystErr = (TH1D*)inc_ele_syst_err->Clone("npedNdptSystErr");

	npedNdpt->Add(phoEledNdpT,-1.);
	npedNdptSystErr->Add(pho_ele_syst_err,-1.);

	// correct for Ke3/NPE ratio
	for(int bin = 1; bin < npedNdpt->GetNbinsX(); ++bin){

			float pT = pt_bins[bin-1]; //npedNdpt->GetBinCenter(bin);
			float Npe = npedNdpt->GetBinContent(bin);
			float NpeErr = npedNdpt->GetBinError(bin);

			double fk = Ke3ToNpeRatio->Eval(pT);	// Ke3/Npe ratio

			npedNdpt->SetBinContent(bin,Npe/(1+fk));
			npedNdpt->SetBinError(bin,NpeErr/(1+fk));

			npedNdptSystErr->SetBinContent(bin,npedNdptSystErr->GetBinContent(bin)/(1+fk));

			float systErr = npedNdptSystErr->GetBinError(bin)/(1+fk);
			float systErrKe3ToNpeRatio = Npe/pow(1+fk,2)*Ke3ToNpeRatioError->Eval(pT);

			npedNdptSystErr->SetBinError(bin,sqrt(systErr*systErr + systErrKe3ToNpeRatio*npedNdptSystErr->GetBinError(bin)/(1+fk)));
	}



	TH1D* phoNpeRatio = (TH1D*)npedNdpt->Clone("phoNpeRatio");
	phoNpeRatio->Divide(phoEledNdpT);

	TH1D* phoNpeRatioSystErr = (TH1D*)npedNdptSystErr->Clone("phoNpeRatioSystErr");
	phoNpeRatioSystErr->Divide(pho_ele_syst_err);

	TCanvas* cdNdPtInc = new TCanvas;
	phoIncdNdpT->Draw("he");

	//phoEledNdpT->Scale(1./nEvents);
	TCanvas* cdNdPtPho = new TCanvas;
	phoEledNdpT->Draw("he");

	TCanvas* cdNdPtPhoNpeRatio = new TCanvas;
	phoNpeRatio->Draw("he");
	phoNpeRatio->GetXaxis()->SetRangeUser(0.25,8.);
	phoNpeRatio->GetXaxis()->SetTitle("p_{T} [GeV]");
	phoNpeRatio->GetYaxis()->SetTitle("NPE/Pho.Ele");

	phoNpeRatioSystErr->SetLineColor(kRed);
	phoNpeRatioSystErr->Draw("pe same");


	// now, convert histogram to TGraphErrors and place points at the mean pT, not the bin center
	/*
	int binToRm = phoNpeRatio->FindBin(0.625);
	phoNpeRatio->SetBinContent(binToRm,0);
	phoNpeRatio->SetBinError(binToRm,0);
	phoNpeRatioSystErr->SetBinContent(binToRm,0);
	phoNpeRatioSystErr->SetBinError(binToRm,0);
	*/


	TGraphErrors* grPhoNpeRatio = new TGraphErrors(phoNpeRatio);
	grPhoNpeRatio->SetName("grPhoNpeRatio");

	TGraphErrors* grPhoNpeRatioSystErr = new TGraphErrors(phoNpeRatioSystErr);
	grPhoNpeRatioSystErr->SetName("grPhoNpeRatioSystErr");


	for(int i=0; i<grPhoNpeRatio->GetN();i++){
		cout << "pT: " << grPhoNpeRatio->GetX()[i] << endl;
		grPhoNpeRatio->GetX()[i] = pt_bins[i];
		grPhoNpeRatioSystErr->GetX()[i] = pt_bins[i];

	}

	removeBinsWithBadPurity(grPhoNpeRatio);
	removeBinsWithBadPurity(grPhoNpeRatioSystErr);



	TCanvas* cPurity = new TCanvas;
	purityCheck->Draw("he");
	purityVsPt->Draw("lp same");
	effFit->Draw("lp same");

	TFile* fout = new TFile(outFileNam, "recreate");
	fout->cd();
	phoEledNdpT->Write();
	phoIncdNdpT->Write();
	phoNpeRatio->Write();
	phoNpeRatioSystErr->Write();
	npedNdpt->Write();
	grPhoNpeRatio->Write();
	grPhoNpeRatioSystErr->Write();
	fout->Close();

	



}
