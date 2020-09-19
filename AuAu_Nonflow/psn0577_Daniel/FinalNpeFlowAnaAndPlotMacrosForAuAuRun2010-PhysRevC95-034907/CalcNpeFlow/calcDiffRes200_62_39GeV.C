/*
 * plotRes200GeV.C
 *
 *  Created on: Jul 15, 2012
 *      Author: dkikola
 */

#include "style.C"

void calcDiffRes200_62_39GeV(){

	setWindowDressing();
	gROOT->ForceStyle();

	int errXwidth  = 6; //the size of the lines at the end of the error bars 
	gStyle->SetEndErrorSize(errXwidth);
	
	float Xmin = 0., Xmax = 3.25;
	float Ymin = -0.1, Ymax = 0.25;

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

	v2_2part_39GeVmb->SetLineColor(kBlack);
	v2_2part_39GeVmb->SetMarkerColor(kBlack);
	v2_2part_39GeVmb->SetMarkerStyle(kFullCircle);
	
	v2_2part_62GeVmb->SetLineColor(kBlue);
	v2_2part_62GeVmb->SetMarkerColor(kBlue);
	v2_2part_62GeVmb->SetMarkerStyle(kFullTriangleDown);
	grSystErr62GeV->SetLineColor(kBlue);

	v2_2part_200GeVmb->SetLineColor(kRed);
	v2_2part_200GeVmb->SetMarkerColor(kRed);
	v2_2part_200GeVmb->SetMarkerStyle(kFullSquare);
	grSystErr200GeV->SetLineColor(kRed);


	float maxPt = 1.; // 1 GeV

	float chi2_62_200GeV = 0.;
	float chi2_39_200GeV = 0.;


	int ndf = 0;

	for(int i = 0; v2_2part_62GeVmb->GetN(); i++){
		float pt = v2_2part_39GeVmb->GetX()[i];

		cout << "pt[200]: " <<  v2_2part_200GeVmb->GetX()[i] << " ";
		cout << "pt[62]: " <<  v2_2part_62GeVmb->GetX()[i] << " ";
		cout << "pt[39]: " <<  v2_2part_39GeVmb->GetX()[i] << endl;


		if(pt>maxPt) break;

		float v2_200GeV = v2_2part_200GeVmb->GetY()[i];
		float v2_200GeV_stat = v2_2part_200GeVmb->GetEY()[i];
		float v2_200GeV_syst = grSystErr200GeV->GetEY()[i];

		float v2_62GeV = v2_2part_62GeVmb->GetY()[i];
		float v2_62GeV_stat = v2_2part_62GeVmb->GetEY()[i];
		float v2_62GeV_syst = grSystErr62GeV->GetEY()[i];

		float v2_39GeV = v2_2part_39GeVmb->GetY()[i];
		float v2_39GeV_stat = v2_2part_39GeVmb->GetEY()[i];
		float v2_39GeV_syst = grSystErr39GeV->GetEY()[i];

		float err200GeV = sqrt(v2_200GeV_stat*v2_200GeV_stat + v2_200GeV_syst* v2_200GeV_syst);
		float err62GeV = sqrt(v2_62GeV_stat*v2_62GeV_stat + v2_62GeV_syst* v2_62GeV_syst);
		float err39GeV = sqrt(v2_39GeV_stat*v2_39GeV_stat + v2_39GeV_syst* v2_39GeV_syst);

		
		//cout << "v2_200GeV-v2_39GeV: " << v2_200GeV-v2_39GeV << endl;
		cout << "err39GeV: " << err39GeV << " err200GeV: " << err200GeV << endl;
                cout << "relative err39: " << err39GeV/v2_39GeV << endl;
                cout << "relative err62: " << err62GeV/v2_62GeV << endl;
                cout << "relative err200: " << err200GeV/v2_200GeV << endl;


		cout << "pt: " << pt << " ";
		float zval_62GeV = (v2_200GeV-v2_62GeV)/sqrt(err200GeV*err200GeV + err62GeV*err62GeV);
		cout << "z-test (200 - 62): " << zval_62GeV << " ";
		float zval_39GeV = (v2_200GeV-v2_39GeV)/sqrt(err200GeV*err200GeV + err39GeV*err39GeV);
		cout << "z-test (200 - 39): " <<  zval_39GeV<< endl;

		//cout << "chi2_62_200GeV: " << zval_62GeV*zval_62GeV << endl;
		//chi2_62_200GeV += zval_62GeV*zval_62GeV;
		chi2_62_200GeV += pow((v2_200GeV-v2_62GeV),2)/(err200GeV*err200GeV + err62GeV*err62GeV);
		//chi2_39_200GeV += zval_39GeV*zval_39GeV;
		chi2_39_200GeV += pow((v2_200GeV-v2_39GeV),2)/(err200GeV*err200GeV + err39GeV*err39GeV);
		ndf++;

	}


	cout << "chi2/ndf for 200-62 GeV consistency:" << chi2_62_200GeV << "/" << ndf << " prob: " << TMath::Prob(chi2_62_200GeV,ndf) << endl;
	cout << "chi2/ndf for 200-39 GeV consistency:" << chi2_39_200GeV << "/" << ndf << " prob: " << TMath::Prob(chi2_39_200GeV,ndf) << endl;





}



