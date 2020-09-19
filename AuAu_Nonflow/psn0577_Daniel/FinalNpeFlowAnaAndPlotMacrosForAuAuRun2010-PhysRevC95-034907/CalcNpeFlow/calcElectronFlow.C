#if !defined(__CINT__) || defined(__MAKECINT__)

// Todo: convert this macro to a class

#include <TFile.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TH3.h>
#include <TProfile2D.h>
#include <TLegend.h>
#include <TMath.h>
#include <TMultiGraph.h>

#endif

#include "style.C"

using namespace std;

TGraphErrors* calcV2_2part(TFile* fin, int CentClass, float v2_ref, float v2_ref_err, const char* whatToCalc = "hadron_moments/Hadron", bool corrAcc = true);
TGraphErrors* calcV2_4part(TFile* fin, int CentClass, float c4Ref, float c4RefErr, const char* whatToCalc = "hadron_moments/Hadron", bool corrAcc = true);

void calcRefV2_2part(TFile* fin, int CentClass, float& v2_ref, float& v2_ref_err, bool corrAcc = true);
void calcRefV2_4part(TFile* fin, int CentClass, float& c4, float& c4Err, bool corrAcc = true);


void calcElectronFlow(const char* inFileNam, const char* outFileNam = "results.root", bool calcV2_4 = false, bool calc_ele_v2 = true, bool corrAcc = true, bool calcV2VsPt = false) {

    gStyle->SetPalette(1, 0);
    setWindowDressing();
    
    TFile* fin = new TFile(inFileNam);

    cout << "getting data" << endl;

    const int NCentClass = 10;

    TGraphErrors* v2_4part[NCentClass];
    TGraphErrors* v2_2part[NCentClass];
    TGraphErrors* incEle_v2_2part[NCentClass];
    TGraphErrors* lsEle_v2_2part[NCentClass];
    TGraphErrors* ulEle_v2_2part[NCentClass];

    TGraphErrors* incEle_v2_4part[NCentClass];
    TGraphErrors* lsEle_v2_4part[NCentClass];
    TGraphErrors* ulEle_v2_4part[NCentClass];

    TMultiGraph* mGrResults[NCentClass];

    TCanvas* cFlow[NCentClass];
    TLegend* leg[NCentClass];

	float v2Ref = 0., v2RefErr = 0.;
	float c4Ref = 0., c4RefErr = 0.;

	TGraphErrors* hadrons_v2_4part_10_40percent = new TGraphErrors("data/DataForCrosscheck/v2_4part_run4_AuAU_30_40_Bai_PhD_thesis.txt");
	TGraphErrors* hadrons_v2_EP_10_40percent = new TGraphErrors("data/DataForCrosscheck/v2_2part_run4_AuAU_30_40_Bai_PhD_thesis.txt");
	 
	hadrons_v2_4part_10_40percent->SetMarkerStyle(kOpenStar);
	hadrons_v2_4part_10_40percent->SetMarkerSize(2.);
	hadrons_v2_4part_10_40percent->SetMarkerColor(kBlue);
	hadrons_v2_4part_10_40percent->SetMarkerColor(kBlue);


	hadrons_v2_EP_10_40percent->SetMarkerStyle(kFullStar);
	hadrons_v2_EP_10_40percent->SetMarkerSize(2.);
	hadrons_v2_EP_10_40percent->SetMarkerColor(kBlack);

	TGraphErrors* v2InclVsCent = new TGraphErrors();
	TGraphErrors* v2_4partInclVsCent = new TGraphErrors();

   float x[NCentClass] = {10,8,7,6,5,4,3,2,1,0};
   TString centLabel[NCentClass] = {TString("0-60%"),TString("70-80%"), TString("60-70%"), TString("50-60%"), 
					TString("40-50%"),TString("30-40%"), TString("20-30%"),
					TString("10-20%"), TString("5-10%"),TString("0-5%")};
    int nPts = 0;

    for(int cent = 0; cent < NCentClass; cent++){

    	//if(cent!=1)continue;

    	calcRefV2_2part(fin, cent, v2Ref, v2RefErr,corrAcc);
    	cout <<  " v2{2} ref: " << v2Ref << " " << v2RefErr << endl;

    	v2InclVsCent->SetPoint(nPts,x[cent],v2Ref);
    	v2InclVsCent->SetPointError(nPts,0,v2RefErr);

    	if(calcV2_4){
			calcRefV2_4part(fin, cent, c4Ref, c4RefErr,corrAcc);
			cout <<  c4Ref << " " << c4RefErr << endl;

			if(calcV2VsPt){
				v2_4part[cent] =  calcV2_4part(fin, cent, c4Ref, c4RefErr, "hadron_moments/Hadron",corrAcc);
				v2_4part[cent]->SetName(TString("v2_4part_cent_")+=cent);
			}

			float v2_4 = pow(c4Ref,0.25);
			float v2_4_err = 0.25*pow(c4Ref,-0.75)*c4RefErr;

			cout << "v2_4 ref: " << v2_4 << " +/- " << v2_4_err << endl;

			v2_4partInclVsCent->SetPoint(nPts,x[cent],v2_4);
			v2_4partInclVsCent->SetPointError(nPts,0,v2_4_err);

			if(calcV2VsPt){
				v2_2part[cent] = calcV2_2part(fin, cent, v2Ref, v2RefErr,"hadron_moments/Hadron",corrAcc);
				v2_2part[cent]->SetName(TString("v2_2part_cent_")+=cent);

				v2_2part[cent]->SetMarkerStyle(kFullCircle);
				v2_2part[cent]->SetMarkerColor(kRed);

				if(calcV2_4){
					v2_4part[cent]->SetMarkerStyle(kFullSquare);
					v2_4part[cent]->SetMarkerColor(kBlack);
				}
			}
    	}

        if(calc_ele_v2){
			incEle_v2_2part[cent] = calcV2_2part(fin, cent, v2Ref, v2RefErr,"inc_ele_moments/incEle",corrAcc);
			incEle_v2_2part[cent]->SetName(TString("v2IncEleCent_2part")+=cent);
			incEle_v2_2part[cent]->SetMarkerStyle(kFullTriangleDown);
			incEle_v2_2part[cent]->SetMarkerColor(kBlue);

			incEle_v2_4part[cent] = calcV2_4part(fin, cent, c4Ref, c4RefErr,"inc_ele_moments/incEle",corrAcc);
			incEle_v2_4part[cent]->SetName(TString("v2IncEleCent_4part")+=cent);
			incEle_v2_4part[cent]->SetMarkerStyle(kOpenCircle);
			incEle_v2_4part[cent]->SetMarkerColor(kBlue);

			lsEle_v2_2part[cent] = calcV2_2part(fin, cent, v2Ref, v2RefErr,"ls_ele_moments/lsEle",corrAcc);
			lsEle_v2_2part[cent]->SetName(TString("v2LsEleCent_2part")+=cent);
			lsEle_v2_2part[cent]->SetMarkerStyle(kFullTriangleUp);
			lsEle_v2_2part[cent]->SetMarkerColor(kGreen);

			lsEle_v2_4part[cent] = calcV2_4part(fin, cent,  c4Ref, c4RefErr,"ls_ele_moments/lsEle",corrAcc);

			lsEle_v2_4part[cent]->SetName(TString("v2LsEleCent_4part")+=cent);
			lsEle_v2_4part[cent]->SetMarkerStyle(kOpenTriangleUp);
			lsEle_v2_4part[cent]->SetMarkerColor(kGreen);

			ulEle_v2_2part[cent] = calcV2_2part(fin, cent, v2Ref, v2RefErr,"ul_ele_moments/ulEle",corrAcc);

			ulEle_v2_2part[cent]->SetName(TString("v2UlEleCent_2part")+=cent);
			ulEle_v2_2part[cent]->SetMarkerStyle(kFullSquare);
			ulEle_v2_2part[cent]->SetMarkerColor(kBlack);

			ulEle_v2_4part[cent] = calcV2_4part(fin, cent, c4Ref, c4RefErr,"ul_ele_moments/ulEle",corrAcc);

			ulEle_v2_4part[cent]->SetName(TString("v2UlEleCent_4part")+=cent);
			ulEle_v2_4part[cent]->SetMarkerStyle(kOpenSquare);
			ulEle_v2_4part[cent]->SetMarkerColor(kBlack);

        }
        

        if(calcV2VsPt || calc_ele_v2){
		cFlow[cent] = new TCanvas;
		cFlow[cent]->SetTitle(TString("centrality class: ")+=centLabel[cent]);
		mGrResults[cent] = new TMultiGraph();
		if(calcV2VsPt){
		  mGrResults[cent]->Add(v2_2part[cent]);
		  if(calcV2_4)mGrResults[cent]->Add(v2_4part[cent]);
		}
        }
        if(calc_ele_v2){
        	mGrResults[cent]->Add(incEle_v2_2part[cent]);
        	//mGrResults[cent]->Add(incEle_v2_4part[cent]);

		mGrResults[cent]->Add(lsEle_v2_2part[cent]);
		//mGrResults[cent]->Add(lsEle_v2_4part[cent]);

        	mGrResults[cent]->Add(ulEle_v2_2part[cent]);
        	//mGrResults[cent]->Add(ulEle_v2_4part[cent]);

        }

	if(calcV2VsPt || calc_ele_v2){
		mGrResults[cent]->Draw("ap");
		mGrResults[cent]->GetXaxis()->SetTitle("p_{T} [GeV/c]"); 
		mGrResults[cent]->GetYaxis()->SetTitle("v_{2}");
		mGrResults[cent]->GetXaxis()->SetLimits(0,8);
		//mGrResults[cent]->GetYaxis()->SetRangeUser(-0.15,0.15);
		mGrResults[cent]->SetTitle(TString("centrality class: ")+=centLabel[cent]);

		leg[cent] = new TLegend(0.12,0.6,0.45,0.85);
		leg[cent]->SetFillColor(0);
		leg[cent]->SetHeader(TString("centrality class: ")+=centLabel[cent]);
		
		if(calc_ele_v2){
		  leg[cent]->AddEntry(incEle_v2_2part[cent],"Inc. ele. v_{2}{2}","p");
		  leg[cent]->AddEntry(incEle_v2_4part[cent],"Inc. ele. v_{2}{4}","p");
		  leg[cent]->AddEntry(lsEle_v2_2part[cent],"LS v_{2}{2}","p");
		  //leg[cent]->AddEntry(lsEle_v2_4part[cent],"LS v_{2}{4}","p");
		  leg[cent]->AddEntry(ulEle_v2_2part[cent],"UL v_{2}{2}","p");
		  //leg[cent]->AddEntry(ulEle_v2_4part[cent],"UL v_{2}{4}","p");
		} 
		leg[cent]->Draw("same");

	}


        if(calcV2VsPt){
			mGrResults[cent]->Add(hadrons_v2_4part_10_40percent);
			mGrResults[cent]->Add(hadrons_v2_EP_10_40percent);

			leg[cent]->AddEntry(v2_2part[cent],"v_{2}{2}, |#eta|<1","p");
			if(calcV2_4)leg[cent]->AddEntry(v2_4part[cent],"v_{2}{4}, |#eta|<1","p");
			
			leg[cent]->AddEntry(hadrons_v2_4part_10_40percent,"v_{2}{4} 30-40% Run4,|#eta|<1.3","p");
			leg[cent]->AddEntry(hadrons_v2_EP_10_40percent,"v_{2}{2}  30-40% Run4, |#eta|<1.3","p");

			

			
        }
        
	  

        nPts++;

    }


    v2InclVsCent->SetMarkerColor(kRed);
    v2InclVsCent->SetLineColor(kRed);
    v2InclVsCent->SetMarkerStyle(kFullSquare);
    v2InclVsCent->SetMarkerSize(1.6);

    v2_4partInclVsCent->SetMarkerColor(kBlue);
    v2_4partInclVsCent->SetLineColor(kBlue);
    v2_4partInclVsCent->SetMarkerStyle(kFullTriangleDown);
    v2_4partInclVsCent->SetMarkerSize(1.6);

    TCanvas* cVsVsCent = new TCanvas;
    TMultiGraph* mGrV2VsCent = new TMultiGraph();

	TGraphErrors* hadrons_v2_2part_vs_cent = new TGraphErrors("data/DataForCrosscheck/v2_ch_hadron_AuAu_200GeV_vs_cent.txt");
	hadrons_v2_2part_vs_cent->SetMarkerStyle(kOpenCircle);
	hadrons_v2_2part_vs_cent->SetMarkerSize(1.6);
	hadrons_v2_2part_vs_cent->SetMarkerColor(kBlack);

	TGraphErrors* hadrons_v2_4part_vs_cent = new TGraphErrors("data/DataForCrosscheck/v2_4part_ch_hadron_AuAu_200GeV_vs_cent.txt");
	hadrons_v2_4part_vs_cent->SetMarkerStyle(kOpenStar);
	hadrons_v2_4part_vs_cent->SetMarkerSize(1.6);
	hadrons_v2_4part_vs_cent->SetMarkerColor(kBlack);
	
	TGraphErrors* hadrons_v2_2part_62GeV_vs_cent = new TGraphErrors("data/DataForCrosscheck/v2_ch_hadron_AuAu_62GeV_vs_cent.txt","%lg %lg %lg");
	hadrons_v2_2part_62GeV_vs_cent->SetMarkerStyle(kOpenCircle);
	hadrons_v2_2part_62GeV_vs_cent->SetMarkerSize(1.6);
	hadrons_v2_2part_62GeV_vs_cent->SetMarkerColor(kBlack);
	
	TGraphErrors* hadrons_v2_2part_39GeV_vs_cent = new TGraphErrors("data/DataForCrosscheck/v2_ch_hadron_AuAu_39GeV_vs_cent.txt","%lg %lg %lg");
	hadrons_v2_2part_39GeV_vs_cent->SetMarkerStyle(kOpenCircle);
	hadrons_v2_2part_39GeV_vs_cent->SetMarkerSize(1.6);
	hadrons_v2_2part_39GeV_vs_cent->SetMarkerColor(kBlack);


	mGrV2VsCent->Add(hadrons_v2_2part_vs_cent);
	//mGrV2VsCent->Add(hadrons_v2_2part_62GeV_vs_cent);
	//mGrV2VsCent->Add(hadrons_v2_2part_39GeV_vs_cent);


	mGrV2VsCent->Add(v2InclVsCent);
	mGrV2VsCent->Add(v2_4partInclVsCent);
	mGrV2VsCent->Add(hadrons_v2_4part_vs_cent);

	mGrV2VsCent->Draw("ap");

	mGrV2VsCent->GetXaxis()->SetTitle("cent");
	mGrV2VsCent->GetYaxis()->SetTitle("v_{2}");
    mGrV2VsCent->GetYaxis()->SetRangeUser(0,0.1);
    v2InclVsCent->SetName("v2InclVsCent");
    v2_4partInclVsCent->SetName("v2_4partInclVsCentt");

    
    TLegend* legCent = new TLegend(0.12,0.6,0.45,0.85);
    legCent->SetFillColor(0);
    legCent->AddEntry(hadrons_v2_2part_vs_cent,"v_{2}{2} Run 4  200 GeV, |#eta|<1","p");
    legCent->AddEntry(hadrons_v2_4part_vs_cent,"v_{2}{4} Run 4  200 GeV, |#eta|<1","p");
    //legCent->AddEntry(v2InclVsCent,"v_{2}{2} Run 10 62 GeV MB, |#eta|<1","p");
    //legCent->AddEntry(v2_4partInclVsCent,"v_{2}{4} Run 10 62 GeV MB, |#eta|<1","p");
    legCent->AddEntry(v2InclVsCent,"v_{2}{2} Run 10 200 GeV HT, |#eta|<1","p");
    legCent->AddEntry(v2_4partInclVsCent,"v_{2}{4} Run 10 200 GeV HT, |#eta|<1","p");
    legCent->Draw("same");
  
    
    TFile* fout = new TFile(outFileNam, "recreate");
    fout->cd();
    v2InclVsCent->Write();
    v2_4partInclVsCent->Write();
    
    if(calcV2VsPt){
      
      for(int cent = 0; cent < NCentClass; cent++){
      	v2_2part[cent]->Write();
	v2_4part[cent]->Write();
      }
	
    }  
    
    
    
    if(calc_ele_v2){
	for(int cent = 0; cent < NCentClass; cent++){
		incEle_v2_2part[cent]->Write();
		lsEle_v2_2part[cent]->Write();
		ulEle_v2_2part[cent]->Write();
		incEle_v2_4part[cent]->Write();
		lsEle_v2_4part[cent]->Write();
		ulEle_v2_4part[cent]->Write();
	}
    }
    
    fout->Close();

}

TGraphErrors* calcV2_2part(TFile* fin, int CentClass, float v2Ref, float v2RefErr, const char* whatToCalc, bool corrAcc) {

    char* histName = new char[100];
    TGraphErrors* gr_v2 = new TGraphErrors();

    int nPts = 0;

    if(TString(whatToCalc) == "hadron_moments/Hadron")
    	sprintf(histName, "QA_histogrmas/had_pT_vs_eta_%d", CentClass);
    else
    	sprintf(histName, "QA_histogrmas/ele_pT_vs_eta_%d", CentClass);
    TH1F* hpT = (TH1F*) fin->Get(histName);

	cout << "v2{2} excl. reg. calc.:" << endl;

  	sprintf(histName,"ref_flow_moments/RefAvgCos2Phi_cent_%d",CentClass);
	TH1F* RefAvgCos2Phi = (TH1F*) fin->Get(histName);

  	sprintf(histName,"ref_flow_moments/RefAvgSin2Phi_cent_%d",CentClass);
	TH1F* RefAvgSin2Phi = (TH1F*) fin->Get(histName);

    for (int i = 0; i < hpT->GetNbinsX(); i++) {

		sprintf(histName, "%s_M2_2part_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
		//cout << histName << endl;
		TH1F* hist_M2 = (TH1F*) fin->Get(histName);

		sprintf(histName, "%sAvgCos2Psi_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
		//cout << histName << endl;
		TH1F* HadronAvgCos2Psi = (TH1F*) fin->Get(histName);
		
		sprintf(histName, "%sAvgSin2Psi_cent_%d_pTbin_%d", whatToCalc, CentClass,i);		
		//cout << histName << endl;
		TH1F* HadronAvgSin2Psi = (TH1F*) fin->Get(histName);


		if (!hist_M2 || !RefAvgCos2Phi || !RefAvgSin2Phi
				|| !HadronAvgCos2Psi || !HadronAvgSin2Psi) {
			cerr << "missing data, aborting";
			return NULL;
		}

		float pT = hpT->GetXaxis()->GetBinCenter(i+1);

		float dn = hist_M2->GetMean();
		float dnErr = hist_M2->GetMeanError();


		float corr_acc = HadronAvgCos2Psi->GetMean()*RefAvgCos2Phi->GetMean() + HadronAvgSin2Psi->GetMean()*RefAvgSin2Phi->GetMean();
		cout << "correction: " <<  HadronAvgCos2Psi->GetMean() << " " << RefAvgCos2Phi->GetMean() << " ";
		cout <<  HadronAvgSin2Psi->GetMean() << " " << RefAvgSin2Phi->GetMean() << " " << corr_acc << endl;
		//cout << "dn: " << dn << " relative correction: " << corr_acc/dn << endl;
		if(corrAcc)dn = dn - corr_acc;

		float v2 = dn/v2Ref;
		float v2_err = v2*sqrt(pow(dnErr/dn,2) + pow(v2RefErr/v2Ref,2));
		gr_v2->SetPoint(nPts, pT, v2);
		gr_v2->SetPointError(nPts, 0, v2_err);

		nPts++;

		cout << pT << "\t" << v2 << " +/- " << v2_err << endl;

    }
    cout << "done" << endl;
    return gr_v2;
}


TGraphErrors* calcV2_4part(TFile* fin, int CentClass, float c4Ref, float c4RefErr, const char* whatToCalc, bool corrAcc) {

	char* histName = new char[100];
	TGraphErrors* v2_4part = new TGraphErrors();

    if(TString(whatToCalc) == "hadron_moments/Hadron")
    	sprintf(histName, "QA_histogrmas/had_pT_vs_eta_%d", CentClass);
    else
    	sprintf(histName, "QA_histogrmas/ele_pT_vs_eta_%d", CentClass);
    TH1F* hpT = (TH1F*) fin->Get(histName);

	int nPts  =0;

	cout << "v2{4} calc.:" << endl;
	cout << "p\tv2\tc2\tc2Ref\tc4Ref\tc4" << endl;

  	sprintf(histName,"ref_flow_moments/RefAvgCos2Phi_cent_%d",CentClass);
	TH1F* RefAvgCos2Phi = (TH1F*) fin->Get(histName);

  	sprintf(histName,"ref_flow_moments/RefAvgSin2Phi_cent_%d",CentClass);
	TH1F* RefAvgSin2Phi = (TH1F*) fin->Get(histName);

    sprintf(histName, "ref_flow_moments/RefAvgCos_Phi1PlusPhi2_cent_%d", CentClass);
    TH1F* RefAvgCos_Phi1PlusPhi2 = (TH1F*) fin->Get(histName);
    sprintf(histName, "ref_flow_moments/RefAvgSin_Phi1PlusPhi2_cent_%d", CentClass);
    TH1F* RefAvgSin_Phi1PlusPhi2 = (TH1F*) fin->Get(histName);

    sprintf(histName, "ref_flow_moments/RefAvgCos_Phi1MinusPhi2MinusPhi3_cent_%d", CentClass);
    TH1F* RefAvgCos_Phi1MinusPhi2MinusPhi3 = (TH1F*) fin->Get(histName);
    sprintf(histName, "ref_flow_moments/RefAvgSin_Phi1MinusPhi2MinusPhi3_cent_%d", CentClass);
    TH1F* RefAvgSin_Phi1MinusPhi2MinusPhi3 = (TH1F*) fin->Get(histName);

    sprintf(histName,"ref_flow_moments/Ref_M2_2part_cent_%d",CentClass);
	TH1F* Ref_M2_2part = (TH1F*) fin->Get(histName);


	float c2Ref = Ref_M2_2part->GetMean();
	float c2RefErr = Ref_M2_2part->GetMeanError();

	for (int i = 0; i < hpT->GetNbinsX(); i++) {

		sprintf(histName, "%s_M2_2part_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
		TH1F* M2_2part = (TH1F*) fin->Get(histName);

	    sprintf(histName, "%s_M2_4part_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
	    TH1F* M2_4part = (TH1F*) fin->Get(histName);

        //.. corrections for non-uniform acceptance
		sprintf(histName, "%sAvgCos2Psi_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
		TH1F* IntAvgCos2Psi = (TH1F*) fin->Get(histName);
		sprintf(histName, "%sAvgSin2Psi_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
		TH1F* IntAvgSin2Psi = (TH1F*) fin->Get(histName);
		sprintf(histName, "%sAvgCos_Psi1PlusPhi2_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
		TH1F* IntAvgCos_Psi1PlusPhi2 = (TH1F*) fin->Get(histName);
		sprintf(histName, "%sAvgSin_Psi1PlusPhi2_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
		TH1F* IntAvgSin_Psi1PlusPhi2 = (TH1F*) fin->Get(histName);

	    sprintf(histName, "%sAvgCos_Psi1PlusPhi2MinusPhi3_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
	    TH1F* IntAvgCos_Psi1PlusPhi2MinusPhi3 = (TH1F*) fin->Get(histName);
	    sprintf(histName, "%sAvgSin_Psi1PlusPhi2MinusPhi3_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
	    TH1F* IntAvgSin_Psi1PlusPhi2MinusPhi3 = (TH1F*) fin->Get(histName);
	    sprintf(histName, "%sAvgCos_Psi1MinusPhi2MinusPhi3_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
	    TH1F* IntAvgCos_Psi1MinusPhi2MinusPhi3 = (TH1F*) fin->Get(histName);
	    sprintf(histName, "%sAvgSin_Psi1MinusPhi2MinusPhi3_cent_%d_pTbin_%d", whatToCalc, CentClass,i);
	    TH1F* IntAvgSin_Psi1MinusPhi2MinusPhi3 = (TH1F*) fin->Get(histName);

	    if (!M2_2part || !M2_4part || !IntAvgCos2Psi ||!IntAvgSin2Psi
	    		|| !IntAvgCos_Psi1PlusPhi2 || !IntAvgCos_Psi1PlusPhi2MinusPhi3
	    		|| !IntAvgSin_Psi1PlusPhi2MinusPhi3 || !IntAvgCos_Psi1MinusPhi2MinusPhi3 || !IntAvgSin_Psi1MinusPhi2MinusPhi3 ) {
	        cerr << "missing data, aborting";
	        return NULL;
	    }

		float pT_tmp = hpT->GetXaxis()->GetBinCenter(i+1);
		//pT_tmp += 0.1;

		float c2 = M2_2part->GetMean();
		float c2Err = M2_2part->GetMeanError();

		//.. corrections
		const int NLines = 16;
		float line[NLines];

		line[0] = - IntAvgCos2Psi->GetMean()*RefAvgCos_Phi1MinusPhi2MinusPhi3->GetMean();
		line[1] = IntAvgSin2Psi->GetMean()*RefAvgSin_Phi1MinusPhi2MinusPhi3->GetMean();
		line[2] = -RefAvgCos2Phi->GetMean()*IntAvgCos_Psi1MinusPhi2MinusPhi3->GetMean();
		line[3] = RefAvgSin2Phi->GetMean()*IntAvgSin_Psi1MinusPhi2MinusPhi3->GetMean();
		line[4] = -2.*RefAvgCos2Phi->GetMean()*IntAvgCos_Psi1PlusPhi2MinusPhi3->GetMean();
		line[5] = -2.*RefAvgSin2Phi->GetMean()*IntAvgSin_Psi1PlusPhi2MinusPhi3->GetMean();
		line[6] = -IntAvgCos_Psi1PlusPhi2->GetMean()*RefAvgCos_Phi1PlusPhi2->GetMean();
		line[7] = -IntAvgSin_Psi1PlusPhi2->GetMean()*RefAvgSin_Phi1PlusPhi2->GetMean();
		line[8] = 2.*RefAvgCos_Phi1PlusPhi2->GetMean()*(IntAvgCos2Psi->GetMean()*RefAvgCos2Phi->GetMean()
				- IntAvgSin2Psi->GetMean()*RefAvgSin2Phi->GetMean());
		line[9] = 2.*RefAvgSin_Phi1PlusPhi2->GetMean()*(IntAvgCos2Psi->GetMean()*RefAvgSin2Phi->GetMean()
					+  IntAvgSin2Psi->GetMean()*RefAvgCos2Phi->GetMean());
		line[10] = 4.*Ref_M2_2part->GetMean()*(IntAvgCos2Psi->GetMean()*RefAvgCos2Phi->GetMean()
				+ IntAvgSin2Psi->GetMean()*RefAvgSin2Phi->GetMean());
		line[11] = 2*IntAvgCos_Psi1PlusPhi2->GetMean()*(pow(RefAvgCos2Phi->GetMean(),2) - pow(RefAvgSin2Phi->GetMean(),2));
		line[12] = 4.*IntAvgSin_Psi1PlusPhi2->GetMean()*RefAvgCos2Phi->GetMean()*RefAvgSin2Phi->GetMean();
		line[13] = 4.*M2_2part->GetMean()*(pow(RefAvgCos2Phi->GetMean(),2) + pow(RefAvgSin2Phi->GetMean(),2));
		line[14] = -6.*(pow(RefAvgCos2Phi->GetMean(),2) - pow(RefAvgSin2Phi->GetMean(),2))*
					(IntAvgCos2Psi->GetMean()*RefAvgCos2Phi->GetMean() - IntAvgSin2Psi->GetMean()*RefAvgSin2Phi->GetMean());
		line[15] = -12.*RefAvgCos2Phi->GetMean()*RefAvgSin2Phi->GetMean()*
					(IntAvgSin2Psi->GetMean()*RefAvgCos2Phi->GetMean() + IntAvgCos2Psi->GetMean() *RefAvgSin2Phi->GetMean());


		float correction = 0;
		
		if(corrAcc){
			for (int j = 0; j < NLines; ++j) {
				correction += line[j];
				//cout << "line[" << j << "]: " << line[j] << endl;
			}
		}
		
		float mom4part = M2_4part->GetMean();
		float mom4partErr = M2_4part->GetMeanError();

		float c4 = 2*c2*c2Ref - mom4part - correction;

		float c4Err = sqrt(pow(mom4partErr,2) + 4*pow(c2*c2RefErr,2) + 4*pow(c2Ref*c2Err,2));

		//if (c4 > 0) {
		float v2 = c4/pow(c4Ref,0.75);
		v2_4part->SetPoint(nPts, pT_tmp, v2);

		// f(m2,m2Ref,m4,m4Ref) = (2*m2*m2Ref -m4)/m4Ref^{3/4}
		float dfdm2 = 2.*c2Ref/pow(c4Ref,0.75);
		float dfdm2Ref = 2.*c2/pow(c4Ref,0.75);
		float dfdm4 = -1./pow(c4Ref,0.75);
		float dfdm4Ref = (0.75*mom4part - 1.5*c2*c2Ref)/pow(c4Ref,1.75);



		float v2_err = sqrt( pow(dfdm2*c2Err,2.) +pow(dfdm2Ref*c2RefErr,2.) + pow(dfdm4*mom4partErr,2) + pow(dfdm4Ref*c4RefErr,2));


		//float v2_err  =	v2*sqrt( pow(c4Err/c4,2) + pow(0.75*c4RefErr/c4Ref,2));
		v2_4part->SetPointError(nPts, 0, v2_err);
		nPts++;
		//}

		//cout << pT_tmp << "\t" << mom4part << " " << c2 << " " << c2Ref << " " << c4Ref << " " <<  c4 << " " << correction << endl;

	}

	return v2_4part;

}

void calcRefV2_2part(TFile* fin, int CentClass, float& v2_ref, float& v2_ref_err, bool corrAcc){

    char* histName = new char[100];

    sprintf(histName,"ref_flow_moments/Ref_M2_2part_cent_%d",CentClass);
	TH1F* M2_2part = (TH1F*) fin->Get(histName);

  	sprintf(histName,"ref_flow_moments/RefAvgCos2Phi_cent_%d",CentClass);
	TH1F* RefAvgCos2Phi = (TH1F*) fin->Get(histName);

  	sprintf(histName,"ref_flow_moments/RefAvgSin2Phi_cent_%d",CentClass);
	TH1F* RefAvgSin2Phi = (TH1F*) fin->Get(histName);

	delete histName;

	if (!M2_2part || !RefAvgCos2Phi || !RefAvgSin2Phi) {
		cerr << "missing data, aborting";
		return;
	}

	float avg_cos = RefAvgCos2Phi->GetMean();
	float avg_sin = RefAvgSin2Phi->GetMean();

	float correction = 0.;
	if(corrAcc)correction = pow(avg_cos,2) + pow(avg_sin,2);

	float c2 = M2_2part->GetMean() - correction;
	float c2Err = M2_2part->GetMeanError();

	//cout << "M2_2part->GetMean()" <<  M2_2part->GetMean() << " avg_sin: " << avg_sin << " avg_cos: " << avg_cos << endl;

	
	
	if (c2 > 0) {
		v2_ref = sqrt(c2);
		v2_ref_err = 0.5 / v2_ref * c2Err;
	}
	
 	cout << "cent: " << CentClass << " RefFlow: " << v2_ref << " +/- " << v2_ref_err << endl;
}

void calcRefV2_4part(TFile* fin, int CentClass, float& c4, float& c4Err, bool corrAcc){

    char* histName = new char[100];

    sprintf(histName,"ref_flow_moments/Ref_M2_4part_cent_%d",CentClass);
	TH1F* M2_4part = (TH1F*) fin->Get(histName);

    sprintf(histName,"ref_flow_moments/Ref_M2_2part_cent_%d",CentClass);
	TH1F* M2_2part = (TH1F*) fin->Get(histName);

    //.. corrections for non-uniform acceptance
	sprintf(histName, "ref_flow_moments/RefAvgCos2Phi_cent_%d", CentClass);
	TH1F* avg_cos = (TH1F*) fin->Get(histName);
	sprintf(histName, "ref_flow_moments/RefAvgSin2Phi_cent_%d", CentClass);
	TH1F* avg_sin = (TH1F*) fin->Get(histName);

    sprintf(histName, "ref_flow_moments/RefAvgCos_Phi1PlusPhi2_cent_%d", CentClass);
    TH1F* AvgCos_Phi1PlusPhi2 = (TH1F*) fin->Get(histName);
    sprintf(histName, "ref_flow_moments/RefAvgSin_Phi1PlusPhi2_cent_%d", CentClass);
    TH1F* AvgSin_Phi1PlusPhi2 = (TH1F*) fin->Get(histName);
    sprintf(histName, "ref_flow_moments/RefAvgCos_Phi1MinusPhi2MinusPhi3_cent_%d", CentClass);
    TH1F* RefAvgCos_Phi1MinusPhi2MinusPhi3 = (TH1F*) fin->Get(histName);
    sprintf(histName, "ref_flow_moments/RefAvgSin_Phi1MinusPhi2MinusPhi3_cent_%d", CentClass);
    TH1F* RefAvgSin_Phi1MinusPhi2MinusPhi3 = (TH1F*) fin->Get(histName);

	delete histName;

	if (!M2_4part || !M2_2part) {
		cerr << "missing data, aborting";
		return;
	}

	float cos2Phi = avg_cos->GetMean();
	float sin2Phi = avg_sin->GetMean();

	float cosSumPhi1Phi2 = AvgCos_Phi1PlusPhi2->GetMean();
	float sinSumPhi1Phi2 = AvgSin_Phi1PlusPhi2->GetMean();
	float cosDiffPhi1Phi2Phi3 = RefAvgCos_Phi1MinusPhi2MinusPhi3->GetMean();
	float sinDiffPhi1Phi2Phi3 = RefAvgSin_Phi1MinusPhi2MinusPhi3->GetMean();

	float c2 = M2_2part->GetMean();
	float c2Err = M2_2part->GetMeanError();

	float cosDiffPhi1Phi2 = c2;

	cout << "corrections: " <<endl;
	cout << "cos2Phi: " << cos2Phi << endl;
	cout << "cosDiffPhi1Phi2Phi3: " << cosDiffPhi1Phi2Phi3 << endl;
	cout << "sin2Phi: " << sinDiffPhi1Phi2Phi3 << endl;
	cout << "cosSumPhi1Phi2: " << cosSumPhi1Phi2 << endl;
	cout << "sinSumPhi1Phi2: " << sinSumPhi1Phi2 << endl;
	cout << "cosDiffPhi1Phi2: " << cosDiffPhi1Phi2 << endl;

	float correction = - 4.*cos2Phi*cosDiffPhi1Phi2Phi3
					   + 4.*sin2Phi*sinDiffPhi1Phi2Phi3
					   - pow(cosSumPhi1Phi2,2) - pow(sinSumPhi1Phi2,2)
					   + 4.*cosSumPhi1Phi2*(cos2Phi*cos2Phi - sin2Phi*sin2Phi)
					   + 8.*sinSumPhi1Phi2*sin2Phi*cos2Phi
					   + 8.*cosDiffPhi1Phi2*(cos2Phi*cos2Phi + sin2Phi*sin2Phi)
					   -6.*pow((cos2Phi*cos2Phi + sin2Phi*sin2Phi),2);

	float m4 = M2_4part->GetMean();
	float m4Err = M2_4part->GetMeanError();

	//cout << "calcRefV2_4par: c2: " <<  c2 << " m4: " << m4 << " correction: " << correction << endl;

	if(corrAcc)
		c4 = 2*c2*c2 -m4 - correction;
	else
		c4 = 2*c2*c2 - m4;

	//cout << "c4: " << c4 << endl;
	c4Err = sqrt(pow(m4Err,2) + pow(4*c2*c2Err,2));
	//cout << " m4 errors: m2Err/m2: " <<  c2Err/c2 << " m4Err/m4: " << m4Err/m4 << " c4Err/c4: " << c4Err/c4 <<  endl;


}
