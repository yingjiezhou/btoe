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

void removeBinsWithBadPurity(int energy, TGraph* gr);


void calcNpeFlowWithSystErr(int energy = 200, int CentClass = 0, TString flowToCalc = "2part", TString outFileNam = "results.root", bool subtratHadronVs = true, float Xmin =0.1, float Xmax = 8.2, float Ymin = -0.05, float Ymax = 0.4 ){

	bool usePhenixV2 = 0;
	bool usePhoFlowSim = 1;


	TString inSpectraFileName, inFlowFileName, inEffFileName, inPhoV2SimName, inPurityFileName, inHadronFlowFileName, inKe3ToNpeRatio, inKe3V2;  

	int npt = 12;
	vector<float>pt_bins;

	
	
	
	// Au+Au 200 GeV min-bias
	if(energy==200){

		if(flowToCalc=="2part" || flowToCalc=="2part_ht"){
			const int npt_200 = 12;
			float pt_bins_200[npt_200] = {0.1, 0.279,0.467678,0.623067,0.861229,1.31974,1.6027,1.85453,2.40745,4.5621,6.8011,8.50316};
			for(int i = 0;i<npt_200;i++)
				pt_bins.push_back(pt_bins_200[i]);
		} else {
			
			const int npt_200 = 10;
			float pt_bins_200[npt_200] = {0.1, 0.279,0.467678,0.623067,0.861229,1.43325,2.40745,4.5621,6.8011,8.50316};
			for(int i = 0;i<npt_200;i++)
				pt_bins.push_back(pt_bins_200[i]);
		}		


		// v2{2}, min-bias
		if(flowToCalc=="2part"){
			inSpectraFileName = "data/DataForNpeStudy/ElectronV2/AuAu200GeV_MB/Moments/NpeV2-2part-MomentsAuAu200GeV-2016-05-05.root";
			inFlowFileName = "data/DataForNpeStudy/ElectronV2/AuAu200GeV_MB/EleV2/EleV2_2part_AuAu200GeV_2016-05-05.root";
			}

		//v2{4}, min-bias
		if(flowToCalc=="4part"){
			
			inSpectraFileName = "data/DataForNpeStudy/ElectronV2/AuAu200GeV_MB/Moments/NpeV2-2part-MomentsAuAu200GeV-2016-05-05.root";
			inFlowFileName = "data/DataForNpeStudy/ElectronV2/AuAu200GeV_MB/EleV2/EleV2_2part_AuAu200GeV_2016-05-05.root";
		}

		// Au+Au 200 GeV st_ht events
		if(flowToCalc=="2part_ht"){

			inSpectraFileName = "data/DataForNpeStudy/ElectronV2/AuAu200GeV_ST_HT/Moments/v2_ele_AuAu200GeV_st_ht.root";
			inFlowFileName = "data/DataForNpeStudy/ElectronV2/AuAu200GeV_ST_HT/EleV2/v2_ele_for_2part_results.root";
			flowToCalc="2part";
		}

		inEffFileName = "data/DataForNpeStudy/EffPurity/phoRecoEffVsPt_AuAu200GeV_0_60_withTotalErr.root"; // 200 GeV
		inPhoV2SimName = "data/DataForNpeStudy/PhoEleV2Sim/200GeV/combinedPhoEleV2.root";
		
		inPurityFileName = "data/DataForNpeStudy/EffPurity/purity_AuAu200GeV_CalculatedVsPconvertedToPt.root";
		inHadronFlowFileName = "data/DataForNpeStudy/HadronV2/hadron_v2_AuAu200GeV_MB.root";
		// with K0L included
		inKe3ToNpeRatio = "data/DataForNpeStudy/Ke3/Ke3ToNpeRatio_AuAu200GeV.root";
		inKe3V2 = "data/DataForNpeStudy/Ke3/Ke3_v2_AuAu200GeV_0_60.root";


	} else if(energy==62){
		
		const int npt_62 = 10;
		float pt_bins_62[npt_62] = {0.1,0.279,0.467678,0.623067,0.861229,1.43325,2.30294,3.3468,4.5621,6.8011};
		for(int i = 0;i<npt_62;i++)
			pt_bins.push_back(pt_bins_62[i]);

		// Au+Au 62 GeV MB events
		inSpectraFileName = "data/DataForNpeStudy/ElectronV2/AuAu62GeV_MB/Moments/NpeV2-2part-MomentsAuAu62GeV-2016-04-14.root";
		inFlowFileName = "data/DataForNpeStudy/ElectronV2/AuAu62GeV_MB/EleV2/EleV2_2part_AuAu62GeV_2016-04-14.root";

		inEffFileName = "data/DataForNpeStudy/EffPurity/phoRecoEffVsPt_AuAu62GeV_0_60_withTotalErr.root";
		inPhoV2SimName = "data/DataForNpeStudy/PhoEleV2Sim/62GeV/combinedPhoEleV2.root";
		
	    inPurityFileName = "data/DataForNpeStudy/EffPurity/purity_AuAu62GeV_CalculatedVsPconvertedToPt.root";
		inHadronFlowFileName = "data/DataForNpeStudy/HadronV2/hadron_v2_AuAu62GeV_MB.root";
		inKe3ToNpeRatio = "data/DataForNpeStudy/Ke3/Ke3ToNpeRatio_AuAu62GeV.root";
		inKe3V2 = "data/DataForNpeStudy/Ke3/Ke3_v2_AuAu62GeV_0_60.root";


	} else if(energy==39){
		const int npt_39 = 10;
		//float pt_bins_39[npt_39] = {0.1,0.327803,0.579913,0.823174,1.0461,1.41605,3.3468,4.5621,6.8011,8.50316};
		float pt_bins_39[npt_39] = {0.1,0.279,0.467678,0.623067,0.861229,1.43325,2.30294,3.3468,4.5621,6.8011};

		for(int i = 0;i<npt_39;i++)
			pt_bins.push_back(pt_bins_39[i]);
		
		inSpectraFileName = "data/DataForNpeStudy/ElectronV2/AuAu39GeV_MB/Moments/NpeV2-2part-MomentsAuAu39GeV-2016-04-15.root";
		inFlowFileName = "data/DataForNpeStudy/ElectronV2/AuAu39GeV_MB/EleV2/EleV2_2part_AuAu39GeV_2016-04-17.root";

		inEffFileName = "data/DataForNpeStudy/EffPurity/phoRecoEffVsPt_AuAu39GeV_0_60_withTotalErr.root";
		inPhoV2SimName = "data/DataForNpeStudy/PhoEleV2Sim/39GeV/combinedPhoEleV2.root";
	    inPurityFileName = "data/DataForNpeStudy/EffPurity/purity_AuAu39GeV_CalculatedVsPconvertedToPt.root";

		inHadronFlowFileName = "data/DataForNpeStudy/HadronV2/hadron_v2_AuAu39GeV_MB.root";
		inKe3ToNpeRatio = "data/DataForNpeStudy/Ke3/Ke3ToNpeRatio_AuAu39GeV.root";
		inKe3V2 = "data/DataForNpeStudy/Ke3/Ke3_v2_AuAu39GeV_0_60.root";

	}
	
	
	for(int i=0;i<pt_bins.size();i++)
		cout << pt_bins[i] << " " ;
		
	cout << endl;
	
	npt = pt_bins.size();

	TGraphErrors* v2Pho_Phenix_cocktile = new TGraphErrors("data/DataforCrosscheck/Phenix_photonicEle_v2_minbias_cocktail.txt");

	TFile* inPhoV2SimFile = new TFile(inPhoV2SimName);
	TFile* inKe3V2File = new TFile(inKe3V2);
	TFile* inKe3ToNpeRatioFile = new TFile(inKe3ToNpeRatio);

	TGraphErrors* v2PhoVsPt = (TGraphErrors*)inPhoV2SimFile->Get("PhotonicElectronV2_0_60");
	TGraph* v2PhoRelativeErrVsPt = (TGraph*)inPhoV2SimFile->Get("grRelativeErr_0_60");

	TGraphErrors* v2Ke3VsPt = (TGraphErrors*)inKe3V2File->Get("PhotonicEleV2");
	TGraphErrors* v2Ke3RelativeErrVsPt = (TGraphErrors*)inKe3V2File->Get("v2PhoEleRelativeErr");

	TGraphErrors* Ke3ToNpeRatio = (TGraphErrors*)inKe3ToNpeRatioFile->Get("grKe3NpeRatio");
	TGraphErrors* Ke3ToNpeRatioError = (TGraphErrors*)inKe3ToNpeRatioFile->Get("grKe3NpeRatio_error");



	v2PhoVsPt->SetName("v2PhoVsPt");
	v2PhoVsPt->RemovePoint(0);
	v2PhoRelativeErrVsPt->RemovePoint(0); // first point (pT<0.2 GeV) needs be removed because of unphysical errors, remove it to have batter error estimation between points
	
	// Get Hadron v2
	char* sName = new char[100];
	
	TFile* inHadv2File;
	TGraphErrors* v2Hadron;
	
	if(subtratHadronVs){
	  inHadv2File= new TFile(inHadronFlowFileName);
	  sprintf(sName, "v2_%s_cent_%d", flowToCalc.Data(), CentClass);
	  
	  v2Hadron = (TGraphErrors*)inHadv2File->Get("v2_hadron_MB");
	  
	  if(!v2Hadron){
	    cout << "No hadron v2 data" << endl;
	    return;
	  }
	}
	
	// Get Photonic Reco. Eff and purity
	TFile* inEffFile = new TFile(inEffFileName);
	TFile* inPurityFile = new TFile(inPurityFileName);

	TGraphErrors* eff_fit;
	TGraph* purityVsPt;
	TGraph* purityVsPtMax;
	TGraph* purityVsPtMin;
	TGraph* eff_fit_error;

	eff_fit= (TGraphErrors*)inEffFile->Get("phoRecoEffVsPt_0_60");
	eff_fit_error = (TGraph*)inEffFile->Get("grSystErr_0_60");

	purityVsPt = (TGraph*)inPurityFile->Get("grPrityMeanVal");  //grPrityMeanVal or grPrityMaxVal or grPrityMinVal
	purityVsPtMax = (TGraph*)inPurityFile->Get("grPrityMaxVal");
	purityVsPtMin = (TGraph*)inPurityFile->Get("grPrityMinVal");
	
	gStyle->SetPalette(1, 0);
	setWindowDressing();

	gROOT->ForceStyle(); //.. force objects to use current style

	//Phenix NPE, 0-60 Au+Au 200 GeV

	TGraphErrors* grV2PheStatErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_stat.err.txt");
	TGraphErrors* grV2PheSystErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_sys.err.txt");

	grV2PheStatErr->SetMarkerStyle(kOpenCircle);
	grV2PheStatErr->SetMarkerColor(kBlue);
	grV2PheStatErr->SetLineWidth(2);
	grV2PheStatErr->SetLineColor(kBlue);
	grV2PheSystErr->SetLineWidth(2);
	grV2PheSystErr->SetLineColor(kBlue);

	TH1D* inc_ele_pT;
	TH1D* ul_ele_pT;
	TH1D* ls_ele_pT;

	TFile* inSpectraFile = new TFile(inSpectraFileName);

	sprintf(sName, "QA_histogrmas/ele_pT_vs_eta_%d", CentClass);
	TH2F* inc_ele_pT_vs_eta = (TH2F*) inSpectraFile->Get(sName);
	inc_ele_pT_vs_eta->Sumw2();
	
	sprintf(sName, "QA_histogrmas/ul_ele_pT_vs_eta_%d", CentClass);
	TH2F* ul_ele_pT_vs_eta = (TH2F*) inSpectraFile->Get(sName);
	ul_ele_pT_vs_eta->Sumw2();

	sprintf(sName, "QA_histogrmas/ls_ele_pT_vs_eta_%d", CentClass);
	TH2F* ls_ele_pT_vs_eta = (TH2F*) inSpectraFile->Get(sName);
	ls_ele_pT_vs_eta->Sumw2();

	if (!inc_ele_pT_vs_eta || !inc_ele_pT_vs_eta || !ls_ele_pT_vs_eta) {
		cout << "missing data, aborting";
		return;
	}

	int NbinsY = inc_ele_pT_vs_eta->GetNbinsY();
	inc_ele_pT  = inc_ele_pT_vs_eta->ProjectionX("inc_ele_pT", 1, NbinsY, "e");
	ul_ele_pT = ul_ele_pT_vs_eta->ProjectionX("ul_ele_pT", 1, NbinsY, "e");
	ls_ele_pT = ls_ele_pT_vs_eta->ProjectionX("ls_ele_pT", 1, NbinsY, "e");

	if(inc_ele_pT==NULL){
		cout << "inc_ele_pT==NULL"<< endl;
		return;
	}

	//TCanvas* cDnDpT = new TCanvas;

	//.. Get flow:
	TFile* inFlowFile = new TFile(inFlowFileName);
	sprintf(sName, "v2IncEleCent_%s%d", flowToCalc.Data(), CentClass);
	TGraphErrors* v2IncVspT = (TGraphErrors*)inFlowFile->Get(sName);



	int NptsInc = v2IncVspT->GetN();

	TGraphErrors* v2NpeVsPt = new TGraphErrors();
	v2NpeVsPt->SetName("v2NpeVsPts");

	TGraphErrors* v2NpeSystErrVsPt = new TGraphErrors();
	v2NpeSystErrVsPt->SetName("v2NpeSystErrVsPt");

	double pTMax = Xmax;
	double pT = 0;
	int bin = 1;	// histogram binning starts from 1, not 0 as in the case of TGraph
	int n = 0;		// point in the v2Pho graphs
	double xUl = 0., vUL = 0., xLs = 0, vLs = 0, xInc = 0, v2Inc = 0,  xHad = 0, vHad = 0;
	double ptInc;
	float purity, purityErr;
	double v2Pho = 0., v2PhoErr = 0.;
	
	while(pT < pTMax){

		//pT = ul_ele_pT->GetBinCenter(bin);
		pT = pt_bins[bin-1];

		// change the pt from bin center to mean pt for inclusive electrons
		
		if(bin<v2IncVspT->GetN())
			v2IncVspT->GetX()[bin-1] = pT;
		
		

		purity = purityVsPt->Eval(pT);
		// estimate symetrized error on purity: this can be either max deviation, algegraic or geometrical mean.
		float purityMaxErr = purityVsPtMax->Eval(pT) - purity;
		float purityMinErr = purity - purityVsPtMin->Eval(pT);
		purityErr = 0.5*(purityMaxErr + purityMinErr);

		if(purity>0)
			cout << "pT: " << pT << " purity: " <<  purity<< " relative puirty err: " <<purityErr/purity << endl;

		double nUl = ul_ele_pT->GetBinContent(bin);
		double nLs = ls_ele_pT->GetBinContent(bin);
		double nInc = inc_ele_pT->GetBinContent(bin);

		double dNincSyst = nInc*purityErr;	// error on inlcusive electrons due to purity
		double dNinc = sqrt(nInc);			// stat erron on inclusive electon candidates
		nInc = purity*nInc;

		if(nInc>0)
			cout << "N inc.: " << nInc << " relative error: " << dNinc/nInc << endl;

		double ptUl = ul_ele_pT->GetBinCenter(bin);

		v2IncVspT->GetPoint(bin-1,ptInc,v2Inc);
		ptInc = pt_bins[bin-1];

		double v2IncErr = v2IncVspT->GetErrorY(bin-1);

		if(subtratHadronVs){

		    vHad = v2Hadron->Eval(ptInc);

		    double hadErr = 0.;	// stat. error on charged hadron v2 is negligible
		    cout << "pT: " << ptInc << " vHad: " << vHad <<" hadErr: " << hadErr << endl;
		    
		    // correct v2 inclusive for hadron contamination
		    v2Inc = 1./purity*(v2Inc - (1-purity)*vHad);
		    v2IncErr = 1./purity*sqrt(v2IncErr*v2IncErr + pow((1-purity)*hadErr,2));
		}  
		
		double NPho = nUl-nLs;

		if(NPho>0){
		  double dNpho = sqrt(nUl + nLs);

		  v2Pho = v2PhoVsPt->Eval(pT);
		  v2PhoErr = 0;	// errro on photonic electron v2 simulations included in syst. error

		  double eff = eff_fit->Eval(pT);

		  NPho = NPho/eff;
		  dNpho = dNpho/eff;

		  double Npe = nInc - NPho;

		  double fk = Ke3ToNpeRatio->Eval(pT);	// Ke3/Npe ratio
		  Npe = (nInc - NPho)/(1+fk);
		  double Nke3 = fk*Npe;	
		  double v2ke3 = v2Ke3VsPt->Eval(pT);		 	

		  if(Npe>0){
				double v2Npe = (v2Inc*nInc - v2Pho*NPho - Nke3*v2ke3)/Npe;

				double v2NpeErrPart1 = pow(v2IncErr*nInc/(Npe),2);
				double v2NpeErrPart2 = pow(v2PhoErr*NPho/(Npe),2);
				double v2NpeErrPart3 = pow(v2Pho*nInc*dNpho/(Npe*Npe),2);
				double v2NpeErrPart4 = pow(v2Inc*NPho*dNinc/(Npe*Npe),2);

				double v2NpeErr = sqrt(v2NpeErrPart1+v2NpeErrPart2+v2NpeErrPart3+v2NpeErrPart4);

				v2NpeVsPt->SetPoint(n,pT,v2Npe);
				v2NpeVsPt->SetPointError(n,0,v2NpeErr);

				cout << "pT: "<< pT <<" v2: " << v2Npe <<" stat. err: " << v2NpeErr << endl;
				cout << "pT: "<< pT <<" NPho/Npe: " << NPho/Npe << endl;

				// now calcualate systematic error due to photonic v2
				v2PhoErr = v2Pho*v2PhoRelativeErrVsPt->Eval(pT);
				double v2NpeErrDueTov2Pho = NPho/Npe*v2PhoErr;
				cout << "v2NpeErrDueTov2Pho: " << v2NpeErrDueTov2Pho << endl;;

				// now calcualate systematic error due to Ke3 v2
				double v2Ke3Err = v2ke3*v2Ke3RelativeErrVsPt->Eval(pT);
				double v2NpeErrDueTov2Ke3 = Nke3/Npe*v2Ke3Err;
				cout << "v2NpeErrDueTov2Ke3: " << v2NpeErrDueTov2Ke3 << endl;;

				// now calcualate systematic error due to Ke3/NPE ratio
				cout << "Ke3ToNpeRatioError: " <<  Ke3ToNpeRatioError->Eval(pT) << endl;
				double ke3Err = Ke3ToNpeRatioError->Eval(pT)*Nke3;
				double v2NpeErrDueTov2Ke3NpeRatio =  (-Npe*v2ke3 + v2Inc*nInc - v2Pho*NPho - Nke3*v2ke3)/(Npe*Npe)*ke3Err;
				cout << "v2NpeErrDueTov2Ke3NpeRatio: " << v2NpeErrDueTov2Ke3NpeRatio << endl;;

				// now calcualate systematic error due to purity
				double v2NpeErrDueToPurity = NPho/pow(Npe,2)*(v2Pho -v2Inc)*dNincSyst;
				cout << "v2NpeErrDueToPurity: " << v2NpeErrDueToPurity << endl;;

				// now cacluate systematic error due to photonic reconstrction efficiency
				double effSystErr = 0.25*eff*eff_fit_error->Eval(pT);
				double v2NpeErrDueToPhoRecoEff = eff*NPho*(v2Pho*nInc -v2Inc*nInc)/pow(eff*Npe,2)*effSystErr;
				cout << "v2NpeErrDueToPhoRecoEff: " << v2NpeErrDueToPhoRecoEff << endl;;

				double totalSystErr = sqrt(pow(v2NpeErrDueTov2Pho,2)+pow(v2NpeErrDueToPhoRecoEff,2) + pow(v2NpeErrDueToPurity,2) + pow(v2NpeErrDueTov2Ke3,2) + pow(v2NpeErrDueTov2Ke3NpeRatio,2));
				cout << "totalSystErr: " << totalSystErr << endl;


				cout << "pT: "<< pT <<" v2 with sys. err: " << v2Npe << ",v2NpeErrDueTov2Pho: " << v2NpeErrDueTov2Pho;
				cout << ", v2NpeErrDueToPhoRecoEff: " << v2NpeErrDueToPhoRecoEff;
				cout << ", v2NpeErrDueToPurity: " << v2NpeErrDueToPurity;
				cout << ", v2NpeErrDueTov2Ke3: " << v2NpeErrDueTov2Ke3;
				cout << ", v2NpeErrDueTov2Ke3NpeRatio: " << v2NpeErrDueTov2Ke3NpeRatio << endl;

				v2NpeSystErrVsPt->SetPoint(n,pT,v2Npe);
				v2NpeSystErrVsPt->SetPointError(n,0,totalSystErr);


				n++;

			  
	
				
			  }
			  


			  
		  }
		
		bin++;
	}
	
	
	// add point with the lowest NPE pT for plotting iss
	int currnetNpts = v2PhoVsPt->GetN();
	pT = pt_bins[1];		  
	v2Pho = v2PhoVsPt->Eval(pT);
	// now calcualate systematic error due to photonic v2
	v2PhoErr = v2Pho*v2PhoRelativeErrVsPt->Eval(pT);
	v2PhoVsPt->SetPoint(currnetNpts,pT,v2Pho);
	v2PhoVsPt->SetPointError(currnetNpts,0,v2PhoErr);	
	v2PhoVsPt->Sort(); //sort points along x axis, to avoind ploting issues

	v2PhoVsPt->SetMarkerStyle(kFullCircle);
	v2NpeVsPt->SetMarkerColor(kRed);
	v2NpeVsPt->SetMarkerStyle(kFullSquare);
	v2NpeVsPt->SetLineColor(kRed);
	v2IncVspT->SetLineColor(kBlue);
	v2IncVspT->SetMarkerColor(kBlue);
	v2IncVspT->SetMarkerStyle(kFullTriangleDown);
	v2NpeSystErrVsPt->SetLineColor(kRed);

	TCanvas* cNpeVsPt = new  TCanvas;
	v2PhoVsPt->Draw("ap");
	v2NpeVsPt->Draw("p same");
	v2NpeSystErrVsPt->Draw("[]");
	v2IncVspT->Draw("p same");

	v2PhoVsPt->GetYaxis()->SetTitle("v_{2}");
	v2PhoVsPt->GetXaxis()->SetTitle("p_{T} GeV/c");
	v2PhoVsPt->GetXaxis()->SetLimits(Xmin,Xmax);
	v2PhoVsPt->GetYaxis()->SetRangeUser(Ymin,Ymax);

	TLine* lZero = new TLine(Xmin,0,Xmax,0); 
	lZero->Draw();
	
	TLegend *leg = new TLegend(0.15,0.7,0.3,0.9);
	leg->SetFillColor(0);
	leg->SetTextFont(132); //Times-Roman
	leg->SetMargin(0.2);
	leg->SetTextSize(0.06);
	leg->AddEntry(v2IncVspT,"Inclusive","p");
	leg->AddEntry(v2PhoVsPt,"Photonic","p");
	leg->AddEntry(v2NpeVsPt,"NPE","p");
	leg->Draw("same");

	TCanvas* cPhoNpeVsPt = new  TCanvas;
	v2NpeVsPt->Draw("ap");
	v2NpeSystErrVsPt->Draw("[]");
	grV2PheStatErr->Draw("p same");
	grV2PheSystErr->Draw("[]");
	v2NpeVsPt->GetYaxis()->SetTitle("v_{2}");
	v2NpeVsPt->GetXaxis()->SetTitle("p_{T} GeV/c");
	v2NpeVsPt->GetXaxis()->SetLimits(Xmin,Xmax);
	v2NpeVsPt->GetYaxis()->SetRangeUser(Ymin,Ymax);
	lZero->Draw();

	TLegend *leg2 = new TLegend(0.15,0.7,0.3,0.9);
	leg2->SetFillColor(0);
	leg2->SetTextFont(132); //Times-Roman
	leg2->SetMargin(0.2);
	leg2->SetTextSize(0.06);
	leg2->AddEntry(grV2PheStatErr,"PHENIX v_{2}^{NPE}{EP}, Au+Au 200 GeV, 0-60%","p");
	leg2->AddEntry(v2NpeVsPt,"NPE","p");
	leg2->Draw("same");

	// now remove bins with bad purity
	removeBinsWithBadPurity(energy,v2NpeVsPt);
	removeBinsWithBadPurity(energy,v2IncVspT);
	removeBinsWithBadPurity(energy,v2NpeSystErrVsPt);

	TFile* fout = new TFile(outFileNam, "recreate");
	fout->cd();
	v2PhoVsPt->Write();
	v2NpeVsPt->Write();
	v2NpeSystErrVsPt->Write();
	v2IncVspT->Write();
	fout->Close();
	

}

void removeBinsWithBadPurity(int energy, TGraph* gr){

	// remove points with pT < 0.2 GeV/c
	for(int i = 0; i<gr->GetN();i++){
		if(gr->GetX()[i]<0.2){
			gr->RemovePoint(i);
			i--;
		}
	}

	// Remove points where syst. uncertitity on puirt is too large
	//if(energy==39 || energy==62){
		for(int i = 0; i<gr->GetN();i++){
			if((gr->GetX()[i]<1.2 && gr->GetX()[i]>0.7) || (gr->GetX()[i]<0.6 && gr->GetX()[i]>0.4)){
				gr->RemovePoint(i);
				i--;
			}
		}
	//}
	

}

