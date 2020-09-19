#include "Draw.h"
#include "TLine.h"
#include "TLatex.h"
#include "TH1.h"
#include "TH3.h"
#include "TF1.h"
#include "math.h"
#include "string.h"
#include "TROOT.h"
#include "TFile.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TMath.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "TLegend.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"
#include "TFitResultPtr.h"
#include "TMatrixT.h"

using namespace std;
using namespace TMath;


void Ds_RawYield_DiffFit_Split_run14(TString mCent, int Cut_num, int mPt_Mini, int mPt_Max, int cent_low, int cent_high, int SigNum, int & num_RSAll,  int & num_hist, int & num_fit, int & num_fit_BKfromWS, int & num_fit_183_201, int & num_fit_19_21, int & num_fit_second, int & err_hist, int & err_fit, int & err_fit_BKfromWS, int & err_fit_183_201, int & err_fit_19_21, int & err_fit_second, double & width_fit, double & width_fit_err, double & mean_fit, double & mean_fit_err, double & signi_fit, double & signi_fit_err, double & BkgNum, double & BkgNum_err, double & RSNum, double & RSNum_err)
	//void draw_Ds( )
{
	TH1::SetDefaultSumw2();
	TH3D *sig_largeh3;
	TH3D *bkg_largeh3;
	TH1D *sig_largeh1;
	TH1D *bkg_largeh1;	
	TH3D *h3bkg_Ds;
	TH1D *h1bkg_Ds;	
	TH3D *h3RS_Ds;
	TH1D *h1RS_Ds;	



	TF1 *fMass = new TF1("fMass","([0])/sqrt(2*TMath::Pi())/[2]*exp(-(x-[1])*(x-[1])/2./[2]/[2])+[3]+[4]*x+([5])/sqrt(2*TMath::Pi())/[7]*exp(-(x-[6])*(x-[6])/2./[7]/[7])", 1.8, 2.1);
	TF1 *fMass_BKfromWS = new TF1("fMass_BKfromWS","([0])/sqrt(2*TMath::Pi())/[2]*exp(-(x-[1])*(x-[1])/2./[2]/[2])+[3]+[4]*x+([5])/sqrt(2*TMath::Pi())/[7]*exp(-(x-[6])*(x-[6])/2./[7]/[7])", 1.8, 2.1);
	TF1 *fMass_second = new TF1("fMass_second","([0])/sqrt(2*TMath::Pi())/[2]*exp(-(x-[1])*(x-[1])/2./[2]/[2])+[3]+[4]*x+[5]*x*x+([6])/sqrt(2*TMath::Pi())/[8]*exp(-(x-[7])*(x-[7])/2./[8]/[8])", 1.8, 2.1);
	TF1 *fMass_183_201 = new TF1("fMass_183_201","([0])/sqrt(2*TMath::Pi())/[2]*exp(-(x-[1])*(x-[1])/2./[2]/[2])+[3]+[4]*x+([5])/sqrt(2*TMath::Pi())/[7]*exp(-(x-[6])*(x-[6])/2./[7]/[7])", 1.8, 2.05);
	TF1 *fMass_19_21 = new TF1("fMass_19_21","([0])/sqrt(2*TMath::Pi())/[2]*exp(-(x-[1])*(x-[1])/2./[2]/[2])+[3]+[4]*x+([5])/sqrt(2*TMath::Pi())/[7]*exp(-(x-[6])*(x-[6])/2./[7]/[7])",1.83,2.1);
	// TF1 *fMass = new TF1("fMass","gaus",1.9,2.1);
	fMass->SetParName(0, "yield_D_{s}");  fMass->SetParName(1, "#mu_D_{s}");  fMass->SetParName(2, "#sigma_D_{s}");  fMass->SetParName(3, "p0");  fMass->SetParName(4, "p1"); fMass->SetParName(5, "yield_D"); fMass->SetParName(6, "#mu_D"); fMass->SetParName(7, "#sigma_D");


	TFile *File_input_Large_run14 = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/DataCut_0080_1_8_KPipT0.5_run14.root");
	sig_largeh3 = (TH3D*)File_input_Large_run14->Get(Form("h3sg_%s_Lc_%i",mCent.Data(), Cut_num));
	bkg_largeh3 =(TH3D*)File_input_Large_run14->Get(Form("h3bkg_%s_Lc_%i",mCent.Data(), Cut_num));
	h3bkg_Ds =(TH3D*)File_input_Large_run14->Get(Form("h3bkg_%s_Ds",mCent.Data()));
	h3RS_Ds =(TH3D*)File_input_Large_run14->Get(Form("h3RS_%s_Ds",mCent.Data()));

	sig_largeh1 = (TH1D*)sig_largeh3->ProjectionZ("rM_Lc_310_1080sg",mPt_Mini, mPt_Max, cent_low, cent_high);//4-5,6-7,8-10,11,16
	bkg_largeh1 = (TH1D*)bkg_largeh3->ProjectionZ("rM_Lc_310_1080bkg", mPt_Mini, mPt_Max, cent_low, cent_high);
	h1bkg_Ds = (TH1D*)h3bkg_Ds->ProjectionZ("h1bkg_Ds", mPt_Mini, mPt_Max, cent_low, cent_high);
	h1RS_Ds = (TH1D*)h3RS_Ds->ProjectionZ("h1RS_Ds", mPt_Mini, mPt_Max, cent_low, cent_high);

int Maxmum_Bin = sig_largeh1->GetBinContent(sig_largeh1->GetMaximumBin());
       int Minimum_Bin = sig_largeh1->GetBinContent(sig_largeh1->GetMinimumBin());
//cout << "Maxmum_Bin = " << Maxmum_Bin << endl;
//cout << "Minimum_Bin = " << Minimum_Bin << endl;


	TFitResultPtr Rpar;
	TFitResultPtr Rpar_BKfromWS;
	TFitResultPtr Rpar_183_201;
	TFitResultPtr Rpar_19_21;
	TFitResultPtr Rpar_second;
	TF1 *f_BK = new TF1("f_BK","[0]+[1]*x", 1.8, 2.1);
	fMass->SetParameters(11, 1.967, 0.009, 2.286, 2.286, 5, 1.867, 0.01);  
	fMass->SetParLimits(2,0.009,0.013);
	fMass->SetParLimits(1,1.958,1.978);
	fMass->SetParLimits(6,1.859,1.879);
	fMass->SetParLimits(7,0.005,0.015);

	TF1 *f_BK_BKfromWS = new TF1("f_BK_BKfromWS","[0]+[1]*x", 1.8, 2.1);
	f_BK_BKfromWS->SetParameters(2.286, 2.286);  
	fMass_BKfromWS->SetParameters(11, 1.967, 0.009, 2.286, 2.286, 5, 1.867, 0.01);  
	fMass_BKfromWS->SetParLimits(2,0.009,0.013);
	fMass_BKfromWS->SetParLimits(1,1.958,1.978);
	fMass_BKfromWS->SetParLimits(6,1.859,1.879);
	fMass_BKfromWS->SetParLimits(7,0.005,0.015);

	TF1 *f_BK_183_201 = new TF1("f_BK_183_201","[0]+[1]*x", 1.8, 2.05);
	fMass_183_201->SetParameters(11, 1.967, 0.009, 2.286, 2.286, 5, 1.867, 0.01);  
	fMass_183_201->SetParLimits(2,0.009,0.013);
	fMass_183_201->SetParLimits(1,1.958,1.978);
	fMass_183_201->SetParLimits(6,1.859,1.879);
	fMass_183_201->SetParLimits(7,0.005,0.015);

	TF1 *f_BK_19_21 = new TF1("f_BK_19_21","[0]+[1]*x", 1.83, 2.1);
	fMass_19_21->SetParameters(11, 1.967, 0.009, 2.286, 2.286, 5, 1.867, 0.01);  
	fMass_19_21->SetParLimits(2,0.009,0.013);
	fMass_19_21->SetParLimits(1,1.958,1.978);
	fMass_19_21->SetParLimits(6,1.859,1.879);
	fMass_19_21->SetParLimits(7,0.005,0.015);

	TF1 *f_BK_second = new TF1("f_BK_second","[0]+[1]*x+[2]*x*x", 1.8, 2.1);
	fMass_second->SetParameters(11, 1.967, 0.009, 2.286, 2.286, 2, 5, 1.867, 0.01);  
	fMass_second->SetParLimits(2,0.009,0.013);
	fMass_second->SetParLimits(1,1.958,1.978);
	fMass_second->SetParLimits(7,1.859,1.879);
	fMass_second->SetParLimits(8,0.005,0.015);

	//	TCanvas *c1 = new TCanvas("c1","c1",10,10,700,550);
	TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);
	//  gStyle->SetEndErrorSize(0);
	c1->SetFillColor(10);
	c1->SetFillStyle(0);
	c1->SetBorderMode(0);
	c1->SetBorderSize(0);
	c1->SetFrameFillColor(10);
	c1->SetFrameFillStyle(0);
	c1->SetFrameBorderMode(0);
	//c1->SetLogy();
	c1->SetGridx(0);
	c1->SetGridy(0);
	c1->SetLeftMargin(0.1);
	c1->SetBottomMargin(0.12);
	c1->SetTopMargin(0.04);
	c1->SetRightMargin(0.1);
	c1->cd();
	gStyle->SetOptStat(0);
	gStyle->SetStatY(0.7);                
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.15);                
	gStyle->SetStatH(0.1);                
	gStyle->SetOptFit(0);
	gStyle->SetLineColor(0);
	sig_largeh1->SetTitle("");
	sig_largeh1->GetYaxis()->SetNdivisions(505,'Y');
	sig_largeh1->GetXaxis()->SetNdivisions(510,'X');
	sig_largeh1->GetYaxis()->SetTitle("Counts (per 8 MeV/c^{2})");
	sig_largeh1->GetYaxis()->SetTitleSize(0.05);
	sig_largeh1->GetYaxis()->SetTitleOffset(0.9);
	sig_largeh1->GetXaxis()->SetTitle("Invariant Mass M_{#phi(K^{#pm}K^{#mp})#pi^{#pm}} (GeV/c^{2})");
	sig_largeh1->GetXaxis()->SetTitleSize(0.05);
	sig_largeh1->GetXaxis()->SetTitleOffset(0.9);
	sig_largeh1->GetXaxis()->SetTitleColor(1);
	sig_largeh1->GetXaxis()->CenterTitle();
	sig_largeh1->GetYaxis()->CenterTitle();
sig_largeh1->SetAxisRange(Minimum_Bin*0.6-1,Maxmum_Bin*1.5,"Y");
	sig_largeh1->SetMarkerStyle(20);
	sig_largeh1->SetLineColor(2);
	sig_largeh1->SetMarkerColor(2);
	sig_largeh1->SetMarkerSize(1.8);
	sig_largeh1->Draw("e same");
	bkg_largeh1->SetMarkerStyle(24);
	bkg_largeh1->SetLineColor(4);
	bkg_largeh1->SetMarkerColor(4);
	bkg_largeh1->SetMarkerSize(1.8);

        
	Rpar = sig_largeh1->Fit(fMass, "SQLR");
	TMatrixDSym mat = Rpar->GetCovarianceMatrix();
	TMatrixDSym mat1;
	mat.GetSub(3,4,3,4,mat1);
	Double_t *matrixPram = mat1.GetMatrixArray();
	Double_t *Par   = fMass->GetParameters();
	double *Par_err = fMass->GetParErrors();
	f_BK->SetParameters(&Par[3]);
	f_BK->SetLineStyle(2); 
	f_BK->SetLineWidth(1); 
	f_BK->SetLineColor(4); 
	f_BK->Draw("same");
	double binstar = Par[1] - 3*Par[2];
	Int_t Bin_siglarge_Start = sig_largeh1->FindBin(binstar+0.00001);
	double binstop = Par[1] + 3*Par[2];
	Int_t Bin_siglarge_Stop = sig_largeh1->FindBin(binstop-0.00001);
	int Bin_Start_SideLeft = 1; 
	int Bin_Stop_SideLeft = 1 + Bin_siglarge_Stop - Bin_siglarge_Start; 
	int Bin_Start_SideRight = 38 - (Bin_siglarge_Stop - Bin_siglarge_Start); 
	int Bin_Stop_SideRight = 38; 
//	cout << "Bin_siglarge_Stop = " << Bin_siglarge_Stop << endl;
//	  cout << "Bin_siglarge_Start = " << Bin_siglarge_Start << endl;
	 // cout << " Bin_Stop_SideLeft = " << Bin_Stop_SideLeft << endl;
	  //cout << " Bin_Start_SideRight = " << Bin_Start_SideRight << endl;
	        
	//calculate Bkg from hist
        BkgNum = h1bkg_Ds->IntegralAndError(Bin_siglarge_Start, Bin_siglarge_Stop, BkgNum_err);
        RSNum = h1RS_Ds->IntegralAndError(Bin_siglarge_Start, Bin_siglarge_Stop, RSNum_err);
        double scale = (RSNum - SigNum)/BkgNum;
//cout << "BkgNum =" << BkgNum <<endl; 
//cout << "RSNum =" << RSNum <<endl; 
//cout << "SigNum =" << SigNum <<endl; 
//cout << "!!!!!!!!!! scale !!!!!!! =" << scale <<endl; 
	double Bkg_err_hist = 0;
	double Bkg_counts_hist = bkg_largeh1->IntegralAndError(Bin_siglarge_Start, Bin_siglarge_Stop, Bkg_err_hist);
	double Bkg_err_SideLeft = 0;
	double Bkg_counts_SideLeft = bkg_largeh1->IntegralAndError(Bin_Start_SideLeft, Bin_Stop_SideLeft , Bkg_err_SideLeft);
	double Bkg_err_SideRight = 0;
	double Bkg_counts_SideRight = bkg_largeh1->IntegralAndError(Bin_Start_SideRight, Bin_Stop_SideRight , Bkg_err_SideRight);
	//calculate Bkg from scaled by RS_Leftside 
	double RS_err_SideRight = 0;
	double RS_counts_SideRight = sig_largeh1->IntegralAndError(Bin_Start_SideRight, Bin_Stop_SideRight , RS_err_SideRight);
if (scale<2) bkg_largeh1->Scale(scale);
	       bkg_largeh1->Draw("e same"); 
	double Bkg_err_Scaledhist = 0;
	double Bkg_counts_Scaledhist = bkg_largeh1->IntegralAndError(Bin_siglarge_Start, Bin_siglarge_Stop, Bkg_err_Scaledhist);
	// calculate RS and Ds counts from hist       
	double RS_err = 0;
	double RS_num = sig_largeh1->IntegralAndError(Bin_siglarge_Start, Bin_siglarge_Stop, RS_err);
	int  Ds_counts_hist = RS_num - Bkg_counts_hist;
	int  Ds_counts_Scaledhist = RS_num - Bkg_counts_Scaledhist;
	int  Ds_counts_Side = RS_num - (Bkg_counts_SideLeft + Bkg_counts_SideRight)*0.5;
	int Ds_err_Side = sqrt((Bkg_err_SideLeft*Bkg_err_SideLeft + Bkg_err_SideRight*Bkg_err_SideRight)*0.25 + RS_err*RS_err);  
	int  Ds_err_hist = sqrt(RS_err*RS_err+Bkg_err_hist*Bkg_err_hist);
	int  Ds_err_Scaledhist = sqrt(RS_err*RS_err+Bkg_err_Scaledhist*Bkg_err_Scaledhist);
	// calculate Ds counts from fitting
	double Bkg_ploy_num =0;
	double Bin_cent = 0;
        int Ds_counts_fit =0;
	for( int j = Bin_siglarge_Start; j<=Bin_siglarge_Stop; j++)
	{
		Bin_cent =  bkg_largeh1->GetBinCenter(j);
		Bkg_ploy_num += f_BK->Eval(Bin_cent);
	}
	Double_t Bkg_ploy_err = f_BK->IntegralError(binstar,binstop,&Par[3],matrixPram)/sig_largeh1->GetBinWidth(1);
if (Bkg_ploy_num>=0)	 Ds_counts_fit = RS_num - Bkg_ploy_num;
else      Ds_counts_fit = RS_num; 
cout << "RS_num = " << RS_num << endl;
	int     Ds_err_fit = sqrt(RS_err*RS_err+Bkg_ploy_err*Bkg_ploy_err);  
	//calculate significance from fitting
	float Significance = Ds_counts_fit/pow((Ds_counts_fit + Bkg_ploy_num),0.5);
	double Signi_sig_err = ((pow((RS_num+Bkg_ploy_num),2))/(4*pow(RS_num,3)))*RS_err*RS_err;
	double Signi_bkg_err = (1/RS_num)*Bkg_ploy_err*Bkg_ploy_err;
	float Signi_err = sqrt(Signi_sig_err+Signi_bkg_err);
//float Significance = Ds_counts_Scaledhist/pow((Ds_counts_Scaledhist + Bkg_counts_Scaledhist),0.5);
  //      double Signi_sig_err = ((pow((RS_num+Ds_counts_Scaledhist),2))/(4*pow(RS_num,3)))*RS_err*RS_err;
    //    double Signi_bkg_err = (1/RS_num)*Bkg_err_Scaledhist*Bkg_err_Scaledhist;
      //  float Signi_err = sqrt(Signi_sig_err+Signi_bkg_err);

//cout << "Ds_counts_fit = " << Ds_counts_fit << endl;
//cout << "Ds_counts_Scaledhist = " << Ds_counts_Scaledhist << endl;
//cout << "Ds_counts_Side = " << Ds_counts_Side << endl;
//cout << "Diff = " << abs(Ds_counts_Scaledhist-Ds_counts_fit)/Ds_counts_fit << endl;
	double RS_errAll = 0;
	int RS_numAll = sig_largeh1->IntegralAndError(1, 38, RS_errAll);

//	cout << "binstar = "<< binstar << "binstop = " << binstop << endl; 
//	cout << "Bkg_ploy_num = "<< Bkg_ploy_num << "Bkg_ploy_err = " << Bkg_ploy_err << endl;

         bkg_largeh1->Fit(f_BK_BKfromWS, "QLRN");
   Double_t *Par_fBK   = f_BK_BKfromWS->GetParameters();
fMass_BKfromWS->FixParameter(4, Par_fBK[1]);
Rpar_BKfromWS = sig_largeh1->Fit(fMass_BKfromWS, "SQLRN");
TMatrixDSym mat_BKfromWS = Rpar_BKfromWS->GetCovarianceMatrix();
        TMatrixDSym mat1_BKfromWS;
        mat_BKfromWS.GetSub(3,4,3,4,mat1_BKfromWS);
        Double_t *matrixPram_BKfromWS = mat1_BKfromWS.GetMatrixArray();
        Double_t *Par_BKfromWS   = fMass_BKfromWS->GetParameters();
        f_BK_BKfromWS->SetParameters(&Par_BKfromWS[3]);
        f_BK_BKfromWS->SetLineStyle(2);
        f_BK_BKfromWS->SetLineWidth(1);
        f_BK_BKfromWS->SetLineColor(2);
        f_BK_BKfromWS->Draw("same");
        double binstar_BKfromWS = Par_BKfromWS[1] - 3*Par_BKfromWS[2];
        Int_t Bin_siglarge_Start_BKfromWS = sig_largeh1->FindBin(binstar_BKfromWS+0.00001);
        double binstop_BKfromWS = Par_BKfromWS[1] + 3*Par_BKfromWS[2];
        Int_t Bin_siglarge_Stop_BKfromWS = sig_largeh1->FindBin(binstop_BKfromWS-0.00001);

        double Bkg_ploy_num_BKfromWS =0;
        double Bin_cent_BKfromWS = 0;
        for( int j = Bin_siglarge_Start_BKfromWS; j<=Bin_siglarge_Stop_BKfromWS; j++)
        {
                Bin_cent_BKfromWS =  bkg_largeh1->GetBinCenter(j);
                Bkg_ploy_num_BKfromWS += f_BK_BKfromWS->Eval(Bin_cent_BKfromWS);
        }
        Double_t Bkg_ploy_err_BKfromWS = f_BK_BKfromWS->IntegralError(binstar_BKfromWS, binstop_BKfromWS, &Par_BKfromWS[3], matrixPram_BKfromWS)/sig_largeh1->GetBinWidth(1);
        int Ds_counts_fit_BKfromWS = RS_num - Bkg_ploy_num_BKfromWS;
        int Ds_err_fit_BKfromWS = sqrt(RS_err*RS_err+Bkg_ploy_err_BKfromWS*Bkg_ploy_err_BKfromWS);



	Rpar_183_201 = sig_largeh1->Fit(fMass_183_201, "SQLRN");
	TMatrixDSym mat_183_201 = Rpar_183_201->GetCovarianceMatrix();
	TMatrixDSym mat1_183_201;
	mat_183_201.GetSub(3,4,3,4,mat1_183_201);
	Double_t *matrixPram_183_201 = mat1_183_201.GetMatrixArray();
	Double_t *Par_183_201   = fMass_183_201->GetParameters();
	f_BK_183_201->SetParameters(&Par_183_201[3]);
	f_BK_183_201->SetLineStyle(2); 
	f_BK_183_201->SetLineWidth(1); 
	f_BK_183_201->SetLineColor(1); 
	f_BK_183_201->Draw("same");
	double binstar_183_201 = Par_183_201[1] - 3*Par_183_201[2];
	Int_t Bin_siglarge_Start_183_201 = sig_largeh1->FindBin(binstar_183_201+0.00001);
	double binstop_183_201 = Par_183_201[1] + 3*Par_183_201[2];
	Int_t Bin_siglarge_Stop_183_201 = sig_largeh1->FindBin(binstop_183_201-0.00001);

	double Bkg_ploy_num_183_201 =0;
	double Bin_cent_183_201 = 0;
	for( int j = Bin_siglarge_Start_183_201; j<=Bin_siglarge_Stop_183_201; j++)
	{
		Bin_cent_183_201 =  bkg_largeh1->GetBinCenter(j);
		Bkg_ploy_num_183_201 += f_BK_183_201->Eval(Bin_cent_183_201);
	}
	Double_t Bkg_ploy_err_183_201 = f_BK_183_201->IntegralError(binstar_183_201, binstop_183_201, &Par_183_201[3], matrixPram_183_201)/sig_largeh1->GetBinWidth(1);
	int Ds_counts_fit_183_201 = RS_num - Bkg_ploy_num_183_201;
	int     Ds_err_fit_183_201 = sqrt(RS_err*RS_err+Bkg_ploy_err_183_201*Bkg_ploy_err_183_201);
//	cout << "binstar_183_201 = "<< binstar_183_201 << "binstop_183_201 = " << binstop_183_201 << endl; 
//	cout << "Bkg_ploy_num_183_201 = "<< Bkg_ploy_num_183_201 << "Bkg_ploy_err_183_201 = " << Bkg_ploy_err_183_201 << endl;

	Rpar_19_21 = sig_largeh1->Fit(fMass_19_21, "SQLRN");
	TMatrixDSym mat_19_21 = Rpar_19_21->GetCovarianceMatrix();
	TMatrixDSym mat1_19_21;
	mat_19_21.GetSub(3,4,3,4,mat1_19_21);
	Double_t *matrixPram_19_21 = mat1_19_21.GetMatrixArray();
	Double_t *Par_19_21   = fMass_19_21->GetParameters();
	f_BK_19_21->SetParameters(&Par_19_21[3]);
	f_BK_19_21->SetLineStyle(2); 
	f_BK_19_21->SetLineWidth(1); 
	f_BK_19_21->SetLineColor(28); 
	f_BK_19_21->Draw("same");
	double binstar_19_21 = Par_19_21[1] - 3*Par_19_21[2];
	Int_t Bin_siglarge_Start_19_21 = sig_largeh1->FindBin(binstar_19_21+0.00001);
	double binstop_19_21 = Par_19_21[1] + 3*Par_19_21[2];
	Int_t Bin_siglarge_Stop_19_21 = sig_largeh1->FindBin(binstop_19_21-0.00001);

	double Bkg_ploy_num_19_21 =0;
	double Bin_cent_19_21 = 0;
	for( int j = Bin_siglarge_Start_19_21; j<=Bin_siglarge_Stop_19_21; j++)
	{
		Bin_cent_19_21 =  bkg_largeh1->GetBinCenter(j);
		Bkg_ploy_num_19_21 += f_BK_19_21->Eval(Bin_cent_19_21);
	}
	Double_t Bkg_ploy_err_19_21 = f_BK_19_21->IntegralError(binstar_19_21, binstop_19_21, &Par_19_21[3], matrixPram_19_21)/sig_largeh1->GetBinWidth(1);
	int Ds_counts_fit_19_21 = RS_num - Bkg_ploy_num_19_21;
	int     Ds_err_fit_19_21 = sqrt(RS_err*RS_err+Bkg_ploy_err_19_21*Bkg_ploy_err_19_21);
//	cout << "binstar_19_21 = "<< binstar_19_21 << "binstop_19_21 = " << binstop_19_21 << endl; 
//	cout << "Bkg_ploy_num_19_21 = "<< Bkg_ploy_num_19_21 << "Bkg_ploy_err_19_21 = " << Bkg_ploy_err_19_21 << endl;

	Rpar_second = sig_largeh1->Fit(fMass_second, "SQLRN");
	TMatrixDSym mat_second = Rpar_second->GetCovarianceMatrix();
	TMatrixDSym mat1_second;
	mat_second.GetSub(3,5,3,5,mat1_second);
	Double_t *matrixPram_second = mat1_second.GetMatrixArray();
	Double_t *Par_second   = fMass_second->GetParameters();
//cout << "Par_second[5] = " << Par_second[5] << endl;
	//for(int i = 0; i<=8; i++)
	//{
	// cout << "matrixPram_second[i] = " << matrixPram_second[i] << endl;  
	//}
	f_BK_second->SetParameters(&Par_second[3]);
	f_BK_second->SetLineStyle(2); 
	f_BK_second->SetLineWidth(1); 
	f_BK_second->SetLineColor(8); 
	f_BK_second->Draw("same");
	double binstar_second = Par_second[1] - 3*Par_second[2];
	Int_t Bin_siglarge_Start_second = sig_largeh1->FindBin(binstar_second+0.00001);
	double binstop_second = Par_second[1] + 3*Par_second[2];
	Int_t Bin_siglarge_Stop_second = sig_largeh1->FindBin(binstop_second-0.00001);

	double Bkg_ploy_num_second =0;
	double Bin_cent_second = 0;
	for( int j = Bin_siglarge_Start_second; j<=Bin_siglarge_Stop_second; j++)
	{
		Bin_cent_second =  bkg_largeh1->GetBinCenter(j);
		Bkg_ploy_num_second += f_BK_second->Eval(Bin_cent_second);
	}
	Double_t Bkg_ploy_err_second = f_BK_second->IntegralError(binstar_second, binstop_second, &Par_second[3], matrixPram_second)/sig_largeh1->GetBinWidth(1);
	int Ds_counts_fit_second = RS_num - Bkg_ploy_num_second;
	int     Ds_err_fit_second = sqrt(RS_err*RS_err+Bkg_ploy_err_second*Bkg_ploy_err_second);
//	cout << "binstar_second = "<< binstar_second << "binstop_second = " << binstop_second << endl; 
//	cout << "Bkg_ploy_num_second = "<< Bkg_ploy_num_second << "Bkg_ploy_err_second = " << Bkg_ploy_err_second << endl;
	num_RSAll = RS_numAll; 
//	cout << "RS_numAll = " << RS_numAll << endl;
	num_hist = Ds_counts_Scaledhist;
	num_fit = Ds_counts_fit;
	num_fit_BKfromWS = Ds_counts_fit_BKfromWS;
	num_fit_183_201 = Ds_counts_fit_183_201;
	num_fit_19_21 = Ds_counts_fit_19_21;
	num_fit_second = Ds_counts_fit_second;
	err_hist = Ds_err_Scaledhist;
	err_fit = Ds_err_fit;
	err_fit_BKfromWS = Ds_err_fit_BKfromWS;
	err_fit_183_201 = Ds_err_fit_183_201;
	err_fit_19_21 = Ds_err_fit_19_21;
	err_fit_second = Ds_err_fit_second;
	width_fit = binstop - binstar;
	width_fit_err = 6*Par_err[2];
	mean_fit = Par[1];
	mean_fit_err = Par_err[1];
        signi_fit = Significance;
        signi_fit_err = Signi_err;
	TString mCentrality;
	TString Lable = Form("Au+Au -> D_{s}^{#pm} + X, #sqrt{s_{NN}} = 200 GeV,2014");
	plotTopCent((char*)Lable.Data(),0.12,0.84+0.06,0.05,1,0.0,22,1);
	if (! mCent.CompareTo("010")) { mCentrality = "0-10%";}
	else if (! mCent.CompareTo("1040") && cent_low==5 && cent_high==7) { mCentrality = "10-40%";}
	else if (! mCent.CompareTo("1040") && cent_low==7 && cent_high==7) { mCentrality = "10-20%";}
	else if (! mCent.CompareTo("1040") && cent_high==6) { mCentrality = "20-40%";}
	else if(! mCent.CompareTo("4080")&& cent_low==1 && cent_high==4) { mCentrality = "40-80%";}
        else if (! mCent.CompareTo("4080")&& cent_high==2) { mCentrality = "60-80%";}
        else if (! mCent.CompareTo("4080")&& cent_low==3 && cent_high==4) { mCentrality = "40-60%";}
	TString Lable2 = Form("%.1f < p_{T} < %.1f GeV/c, %s",(mPt_Mini-1)*0.1, mPt_Max*0.1, mCentrality.Data()) ;
	//      TString Lable3 = Form("BG from scaled hist: #(D^{#pm}_{s})=%i#pm%i", Ds_counts_Scaledhist, Ds_err_Scaledhist);
	//      TString Lable3 = Form("BG from SideBand: #(D^{#pm}_{s})=%i#pm%i", Ds_counts_Side, Ds_err_Side);
	TString Lable3 = Form("Linear fit(1.8,2.1): #(D^{#pm}_{s})=%.i#pm%.i", Ds_counts_fit, Ds_err_fit);
	TString Lable4 = Form("Linear fit(1.8,2.05): #(D^{#pm}_{s})=%.i#pm%.i", Ds_counts_fit_183_201, Ds_err_fit_183_201);
	TString Lable5 = Form("Linear fit(1.83,2.1): #(D^{#pm}_{s})=%.i#pm%.i", Ds_counts_fit_19_21, Ds_err_fit_19_21);
	TString Lable6 = Form("Quadratic fit(1.8,2.1): #(D^{#pm}_{s})=%.i#pm%.i", Ds_counts_fit_second, Ds_err_fit_second);
	TString Lable7 = Form("S/#sqrt{S+B}=%.1f#pm%.1f",Significance, Signi_err);
	plotTopCent((char*)Lable2.Data(),0.12,0.8+0.06,0.04,1,0.0,22,1);
	plotTopCent((char*)Lable3.Data(),0.12,0.76+0.06,0.04,4,0.0,22,1);
	plotTopCent((char*)Lable4.Data(),0.12,0.72+0.06,0.04,1,0.0,22,1);
	plotTopCent((char*)Lable5.Data(),0.12,0.68+0.06,0.04,28,0.0,22,1);
	plotTopCent((char*)Lable6.Data(),0.12,0.64+0.06,0.04,8,0.0,22,1);
 plotTopCent(Form("Linear fit (WS shape): #(D^{#pm}_{s})=%.i#pm%.i",Ds_counts_fit_BKfromWS , Ds_err_fit_BKfromWS),0.12,0.6+0.06,0.04,2,0.0,22,1);
	plotTopCent((char*)Lable7.Data(),0.12,0.56+0.06,0.04,1,0.0,22,1);


	/*
	   TString Lable2 = Form("%.1f < p_{T} < %.1f GeV/c, %s",(mPt_Mini-1)*0.5, mPt_Max*0.5, mCent.Data()) ;
	   TString Lable = Form("Au+Au -> D_{s}^{#pm} + X, #sqrt{s_{NN}} = 200 GeV,2014");
	   plotTopCent((char*)Lable.Data(),0.12,0.84,0.05,1,0.0,22,1);
	   TString Lable3 = Form("BG from scaled hist: #(D^{#pm}_{s})=%i#pm%i", Ds_counts_Scaledhist, Ds_err_Scaledhist);
	//	TString Lable3 = Form("BG from SideBand: #(D^{#pm}_{s})=%i#pm%i", Ds_counts_Side, Ds_err_Side);
	TString Lable5 = Form("S/#sqrt{S+B}=%.1f#pm%.1f",Significance, Signi_err);
	TString Lable4 = Form("BG from fit: #(D^{#pm}_{s})=%.i#pm%.i", Ds_counts_fit, Ds_err_fit);
	plotTopCent((char*)Lable2.Data(),0.12,0.78,0.05,1,0.0,22,1);
	plotTopCent((char*)Lable3.Data(),0.12,0.72,0.05,2,0.0,22,1);
	plotTopCent((char*)Lable4.Data(),0.12,0.66,0.05,1,0.0,22,1);
	plotTopCent((char*)Lable5.Data(),0.12,0.6,0.05,2,0.0,22,1);
	 */
	TLegend* legend = new TLegend(0.65,0.65,0.85,0.8);
	legend->AddEntry(sig_largeh1,"Right-Sign", "p");
	//	legend->AddEntry(bkg_largeh1,"Wrong-Sign", "p");
	legend->SetTextSize(0.05);
	legend->SetLineColor(0);
	legend->SetTextFont(22);
	legend->Draw();
	//	TString mTitle = Form("../pic/DsRec_%s_%.1f_%.1f_lowBDTcut.eps",mCent.Data(), (mPt_Mini-1)*0.5, mPt_Max*0.5); 
	TString mTitle = Form("/home/fuchuan/TMVA_My/Anlysis_Ds/Raw_Sig/run14/pic/DsRec_%s_%.1f_%.1f_defaultBDT_DiffFit_Fit.pdf", mCentrality.Data(), (mPt_Mini-1)*0.1, mPt_Max*0.1); 
//		c1->SaveAs(mTitle.Data());
}

int main()
{
	TFile *output = new TFile("Ds_RawYield_run14_phy_defaultBDTcut.root","recreate");
	double xbins[6] = {0, 1.5, 2.5, 3.5, 5, 8};
	double xbins_split[7] = {0, 1, 2, 2.5, 3.5, 5, 8};
	TH1::SetDefaultSumw2();
	double pT[4] = {1.95121, 2.93578, 4.1161, 6.09053}; 
	double pT_split[5] = {1.48558, 2.23541, 2.93578, 4.1161, 6.09053}; 
	double mT[4];
	double mT_split[5];
	double dpT[4] = {1, 1, 1.5, 3}; 
	double dpT_split[5] = {1, 0.5, 1, 1.5, 3}; 
	double dmT[4]; 
	double dmT_split[5]; 
	for (int j = 0; j <= 3; j++)
	{
		mT[j] = sqrt(pT[j]*pT[j] + 1.96828*1.96828); 
		dmT[j] = sqrt(xbins[j+2]*xbins[j+2]+1.96828*1.96828) - sqrt(xbins[j+1]*xbins[j+1]+1.96828*1.96828);
//		cout << "mT[j] = "<< mT[j] << "dmT[j] = "<<  dmT[j] << endl;
	}
for (int j = 0; j <= 4; j++)
{
		mT_split[j] = sqrt(pT_split[j]*pT_split[j] + 1.96828*1.96828); 
		dmT_split[j] = sqrt(xbins_split[j+2]*xbins_split[j+2]+1.96828*1.96828) - sqrt(xbins_split[j+1]*xbins_split[j+1]+1.96828*1.96828);
}
	double Nev_16[5] = {1.25e8, 3.89e8, 5.28e8, 1.28e8, 2.61e8}; 
	double Nev_14[5] = {1.27e8, 3.53e8, 4.75e8, 1.16e8, 2.36e8}; 
	double dY = 2;
	//	double pT_BR_Nev_dpT_dy_run16[3][4]={ {12.56*1.846*0.0227*1.25e8*1*2, 12.56*2.845*0.0227*1.25e8*1*2, 12.56*3.949*0.0227*1.25e8*1.5*2, 12.56*5.645*0.0227*1.25e8*3*2}, {12.56*1.846*0.0227*3.89e8*1*2, 12.56*2.845*0.0227*3.89e8*1*2, 12.56*3.949*0.0227*3.89e8*1.5*2, 12.56*5.645*0.0227*3.89e8*3*2},{12.56*1.846*0.0227*5.28e8*1*2, 12.56*2.845*0.0227*5.28e8*1*2, 12.56*3.949*0.0227*5.28e8*1.5*2, 12.56*5.645*0.0227*5.28e8*3*2} };
	//	double pT_BR_Nev_dpT_dy_run14[3][4]={ {12.56*1.846*0.0227*1.27e8*1*2, 12.56*2.845*0.0227*1.27e8*1*2, 12.56*3.949*0.0227*1.27e8*1.5*2, 12.56*5.645*0.0227*1.27e8*3*2}, {12.56*1.846*0.0227*3.53e8*1*2, 12.56*2.845*0.0227*3.53e8*1*2, 12.56*3.949*0.0227*3.53e8*1.5*2, 12.56*5.645*0.0227*3.53e8*3*2},{12.56*1.846*0.0227*4.77e8*1*2, 12.56*2.845*0.0227*4.77e8*1*2, 12.56*3.949*0.0227*4.77e8*1.5*2, 12.56*5.645*0.0227*4.77e8*3*2} }; 
	double pT_BR_Nev_dpT_dy_run16[5][5];
	double mT_BR_Nev_dmT_dy[5][5];
	double pT_BR_Nev_dpT_dy_run14[5][5];
	for (int i = 0; i <= 4; i++)
	{
if (i != 1)
{
		for (int j = 0; j <= 3; j++)
		{
			pT_BR_Nev_dpT_dy_run16[i][j] = (12.56*0.0227*pT[j]*dpT[j]*dY*Nev_16[i]);
			mT_BR_Nev_dmT_dy[i][j] = (12.56*0.0227*mT[j]*dmT[j]*dY*Nev_14[i]);
			pT_BR_Nev_dpT_dy_run14[i][j] = (12.56*0.0227*pT[j]*dpT[j]*dY*Nev_14[i]);
			//cout << "pT_BR_Nev_dpT_dy_run16[i][j] = "<< pT_BR_Nev_dpT_dy_run16[i][j] << endl;
		}
}
else 
{
 for (int j = 0; j <= 4; j++)
                {
                        pT_BR_Nev_dpT_dy_run16[i][j] = (12.56*0.0227*pT_split[j]*dpT_split[j]*dY*Nev_16[i]);
                        mT_BR_Nev_dmT_dy[i][j] = (12.56*0.0227*mT_split[j]*dmT_split[j]*dY*Nev_14[i]);
                        pT_BR_Nev_dpT_dy_run14[i][j] = (12.56*0.0227*pT_split[j]*dpT_split[j]*dY*Nev_14[i]);
                        //cout << "pT_BR_Nev_dpT_dy_run16[i][j] = "<< pT_BR_Nev_dpT_dy_run16[i][j] << endl;
                }

}
	}


int BDT_cut[5][5] = { {114+0.0, 72+0.0, 77+0.0, 77+0.0, 77+0.0 }, {107+0.0, 101+0.0, 60+0.0, 68+0.0, 70+0.0}, {42+0.0, 57+0.0, 67+0.0, 68+0.0, 68+0.0}, {107+0.0, 65+0.0, 72+0.0, 75+0.0, 75+0.0}, {96+0.0, 54+0.0, 62+0.0, 68+0.0, 68+0.0}};

//int BDT_cut[5][5] = { {114+16, 72+15, 77+18, 77+30, 77+30 }, {107+18, 101+25, 60+20, 68+20, 70+30}, {42+26, 57+23, 67+30, 68+26, 68+26}, {107+20, 65+20, 72+19, 75+28, 75+28}, {96+20, 54+20, 62+23, 68+29, 68+29}};

//int BDT_cut[5][5] = { {114-16, 72-15, 77-18, 77-30, 77-30 }, {107-16, 101-21, 60-25, 68-25, 70-30}, {42-30, 57-30, 67-25, 68-20, 68-20}, {107-24, 65-23, 72-30, 75-20, 75-20}, {96-18, 54-29, 62-30, 68-25, 68-25}};


int SigNum[5][5] = {{271, 265, 158, 43, 43}, {327, 390, 765, 421, 113}, {146, 170, 110, 37, 37}, {284, 316, 150, 38, 38}, {404, 442, 270, 75, 75}};// run14_phy sigNum
	TString NameCent[5] = {"h010", "h1040", "h4080", "h1020", "h2040"};
	TString NameCent2[5] = {"010", "1040", "4080", "1040", "1040"};
	int pTBin_low[4] = {16, 26, 36, 51};
	int pTBin_high[4] = {25, 35, 50, 80};
	int CenBin_low[5] = {8, 5, 1, 7, 5};
	int CenBin_high[5] = {9, 7, 4, 7, 6};
	int pTBin_low_split[5] = {11, 21, 26, 36, 51};
	int pTBin_high_split[5] = {20, 25, 35, 50, 80};
	TH1F *RSNum_RS[5];
	TH1F *BkgNum_RS[5];
	TH1F *Significance_fit[5];
	TH1F *SigNum_fit[5];
	TH1F *SigNum_Bin[5];
	TH1F *RawYield_mT_fit[5];
	TH1F *RawYield_fit[5];
	TH1F *RawYield_fit_BKfromWS[5];
	TH1F *RawYield_fit_183_201[5];
	TH1F *RawYield_fit_19_21[5];
	TH1F *RawYield_fit_second[5];
	TH1F *RawYield_hist[5];
	TH1F *RawYield_RSAll[5];
	TH1F *Ds_MeanMass_fit[5];
	TH1F *Ds_WidthMass_fit[5];
        TH1F *RSNum_1040_1525_RS;
        TH1F *BkgNum_1040_1525_RS;
        TH1F *Significance_1040_1525_fit;
        TH1F *SigNum_1040_1525_fit;
        TH1F *SigNum_1040_1525_Bin;
        TH1F *RawYield_1040_1525_hist;
        TH1F *RawYield_1040_1525_fit;
        TH1F *RawYield_1040_1525_fit_BKfromWS;
        TH1F *RawYield_1040_1525_fit_183_201;
        TH1F *RawYield_1040_1525_fit_19_21;
        TH1F *RawYield_1040_1525_fit_second;

        TH1F *RSNum_4060_155_RS;
        TH1F *BkgNum_4060_155_RS;
	TH1F *Significance_4060_155_fit;
	TH1F *SigNum_4060_155_fit;
	TH1F *SigNum_4060_155_Bin;
        TH1F *RawYield_4060_155_hist;
        TH1F *RawYield_4060_155_fit;
        TH1F *RawYield_4060_155_fit_BKfromWS;
        TH1F *RawYield_4060_155_fit_183_201;
        TH1F *RawYield_4060_155_fit_19_21;
        TH1F *RawYield_4060_155_fit_second;
        TH1F *Ds_MeanMass_4060_155_fit;
        TH1F *Ds_WidthMass_4060_155_fit;

        TH1F *RSNum_6080_155_RS;
        TH1F *BkgNum_6080_155_RS;
	TH1F *Significance_6080_155_fit;
	TH1F *SigNum_6080_155_fit;
	TH1F *SigNum_6080_155_Bin;
        TH1F *RawYield_6080_155_hist;
        TH1F *RawYield_6080_155_fit;
        TH1F *RawYield_6080_155_fit_BKfromWS;
        TH1F *RawYield_6080_155_fit_183_201;
        TH1F *RawYield_6080_155_fit_19_21;
        TH1F *RawYield_6080_155_fit_second;
        TH1F *Ds_MeanMass_6080_155_fit;
        TH1F *Ds_WidthMass_6080_155_fit;

	//TString mh1Title[3][4] = {{"h010_mT_fit", "h010_fit", "h010_hist", "h010_RSAll"}, {"h1040_mT_fit", "h1040_fit", "h1040_hist", "h1040_RSAll"}, {"h4080_mT_fit", "h4080_fit", "h4080_hist", "h4080_RSAll"}};
	for (int i = 0; i<=4; i++)
	{
		if (i != 1)
		{
			RSNum_RS[i] = new TH1F(Form("%s_RSNum_RS", NameCent[i].Data()),"", 5, xbins);
			BkgNum_RS[i] = new TH1F(Form("%s_BkgNum_RS", NameCent[i].Data()),"", 5, xbins);
			Significance_fit[i] = new TH1F(Form("%s_Significance_fit", NameCent[i].Data()),"", 5, xbins);
			SigNum_fit[i] = new TH1F(Form("%s_SigNum_fit", NameCent[i].Data()),"", 5, xbins);
			SigNum_Bin[i] = new TH1F(Form("%s_SigNum_Bin", NameCent[i].Data()),"", 5, xbins);
			RawYield_mT_fit[i] = new TH1F(Form("%s_mT_fit", NameCent[i].Data()),"", 5, xbins);
			RawYield_fit[i] = new TH1F(Form("%s_fit", NameCent[i].Data()),"", 5, xbins);
			RawYield_fit_BKfromWS[i] = new TH1F(Form("%s_fit_BKfromWS", NameCent[i].Data()),"", 5, xbins);
			RawYield_fit_183_201[i] = new TH1F(Form("%s_fit_183_201", NameCent[i].Data()),"", 5, xbins);
			RawYield_fit_19_21[i] = new TH1F(Form("%s_fit_19_21", NameCent[i].Data()),"", 5, xbins);
			RawYield_fit_second[i] = new TH1F(Form("%s_fit_second", NameCent[i].Data()),"", 5, xbins);
			RawYield_hist[i] = new TH1F(Form("%s_hist", NameCent[i].Data()),"", 5, xbins);
			RawYield_RSAll[i] = new TH1F(Form("%s_RSAll", NameCent[i].Data()),"", 5, xbins);
			Ds_MeanMass_fit[i] = new TH1F(Form("%s_Ds_MeanMass_fit", NameCent[i].Data()),"", 5, xbins);
			Ds_WidthMass_fit[i] = new TH1F(Form("%s_Ds_WidthMass_fit", NameCent[i].Data()),"", 5, xbins);
		}
		else
		{
			RSNum_RS[i] = new TH1F(Form("%s_RSNum_RS", NameCent[i].Data()),"", 6, xbins_split);
			BkgNum_RS[i] = new TH1F(Form("%s_BkgNum_RS", NameCent[i].Data()),"", 6, xbins_split);
			Significance_fit[i] = new TH1F(Form("%s_Significance_fit", NameCent[i].Data()),"", 6, xbins_split);
			SigNum_fit[i] = new TH1F(Form("%s_SigNum_fit", NameCent[i].Data()),"", 6, xbins_split);
			SigNum_Bin[i] = new TH1F(Form("%s_SigNum_Bin", NameCent[i].Data()),"", 6, xbins_split);
			RawYield_mT_fit[i] = new TH1F(Form("%s_mT_fit", NameCent[i].Data()),"", 6, xbins_split);
			RawYield_fit[i] = new TH1F(Form("%s_fit", NameCent[i].Data()),"", 6, xbins_split);
			RawYield_fit_BKfromWS[i] = new TH1F(Form("%s_fit_BKfromWS", NameCent[i].Data()),"", 6, xbins_split);
			RawYield_fit_183_201[i] = new TH1F(Form("%s_fit_183_201", NameCent[i].Data()),"", 6, xbins_split);
			RawYield_fit_19_21[i] = new TH1F(Form("%s_fit_19_21", NameCent[i].Data()),"", 6, xbins_split);
			RawYield_fit_second[i] = new TH1F(Form("%s_fit_second", NameCent[i].Data()),"", 6, xbins_split);
			RawYield_hist[i] = new TH1F(Form("%s_hist", NameCent[i].Data()),"", 6, xbins_split);
			RawYield_RSAll[i] = new TH1F(Form("%s_RSAll", NameCent[i].Data()),"", 6, xbins_split);
			Ds_MeanMass_fit[i] = new TH1F(Form("%s_Ds_MeanMass_fit", NameCent[i].Data()),"", 6, xbins_split);
			Ds_WidthMass_fit[i] = new TH1F(Form("%s_Ds_WidthMass_fit", NameCent[i].Data()),"", 6, xbins_split);
		}
	}
			RSNum_1040_1525_RS = new TH1F("RSNum_1040_1525_RS","", 1, 1.5, 2.5);
			BkgNum_1040_1525_RS = new TH1F("BkgNum_1040_1525_RS","", 1, 1.5, 2.5);
			Significance_1040_1525_fit = new TH1F("Significance_1040_1525_fit","", 1, 1.5, 2.5);
			SigNum_1040_1525_fit = new TH1F("SigNum_1040_1525_fit","", 1, 1.5, 2.5);
			SigNum_1040_1525_Bin = new TH1F("SigNum_1040_1525_Bin","", 1, 1.5, 2.5);
			RawYield_1040_1525_hist = new TH1F("RawYield_1040_1525_hist","", 1, 1.5, 2.5);
			RawYield_1040_1525_fit = new TH1F("RawYield_1040_1525_fit","", 1, 1.5, 2.5);
			RawYield_1040_1525_fit_BKfromWS = new TH1F("RawYield_1040_1525_fit_BKfromWS","", 1, 1.5, 2.5);
			RawYield_1040_1525_fit_183_201 = new TH1F("RawYield_1040_1525_fit_183_201","", 1, 1.5, 2.5);
			RawYield_1040_1525_fit_19_21 = new TH1F("RawYield_1040_1525_fit_19_21","", 1, 1.5, 2.5);
			RawYield_1040_1525_fit_second = new TH1F("RawYield_1040_1525_fit_second","", 1, 1.5, 2.5);

			RSNum_4060_155_RS = new TH1F("RSNum_4060_155_RS","", 1, 1.5, 5);
			BkgNum_4060_155_RS = new TH1F("BkgNum_4060_155_RS","", 1, 1.5, 5);
			Significance_4060_155_fit = new TH1F("Significance_4060_155_fit","", 1, 1.5, 5);
                 	SigNum_4060_155_fit = new TH1F("SigNum_4060_155_fit","", 1, 1.5, 5);
                 	SigNum_4060_155_Bin = new TH1F("SigNum_4060_155_Bin","", 1, 1.5, 5);
                 	RawYield_4060_155_hist = new TH1F("RawYield_4060_155_hist","", 1, 1.5, 5);
                 	RawYield_4060_155_fit = new TH1F("RawYield_4060_155_fit","", 1, 1.5, 5);
                 	RawYield_4060_155_fit_BKfromWS = new TH1F("RawYield_4060_155_fit_BKfromWS","", 1, 1.5, 5);
			RawYield_4060_155_fit_183_201 = new TH1F("RawYield_4060_155_fit_183_201","", 1, 1.5, 5);
			RawYield_4060_155_fit_19_21 = new TH1F("RawYield_4060_155_fit_19_21","", 1, 1.5, 5);
			RawYield_4060_155_fit_second = new TH1F("RawYield_4060_155_fit_second","", 1, 1.5, 5);
                       Ds_MeanMass_4060_155_fit = new TH1F("Ds_MeanMass_4060_155_fit","", 1, 1.5, 5); 
                       Ds_WidthMass_4060_155_fit = new TH1F("Ds_WidthMass_4060_155_fit","", 1, 1.5, 5); 

			RSNum_6080_155_RS = new TH1F("RSNum_6080_155_RS","", 1, 1.5, 5);
			BkgNum_6080_155_RS = new TH1F("BkgNum_6080_155_RS","", 1, 1.5, 5);
			Significance_6080_155_fit = new TH1F("Significance_6080_155_fit","", 1, 1.5, 5);
                 	SigNum_6080_155_fit = new TH1F("SigNum_6080_155_fit","", 1, 1.5, 5);
                 	SigNum_6080_155_Bin = new TH1F("SigNum_6080_155_Bin","", 1, 1.5, 5);
                 	RawYield_6080_155_hist = new TH1F("RawYield_6080_155_hist","", 1, 1.5, 5);
                 	RawYield_6080_155_fit = new TH1F("RawYield_6080_155_fit","", 1, 1.5, 5);
                 	RawYield_6080_155_fit_BKfromWS = new TH1F("RawYield_6080_155_fit_BKfromWS","", 1, 1.5, 5);
			RawYield_6080_155_fit_183_201 = new TH1F("RawYield_6080_155_fit_183_201","", 1, 1.5, 5);
			RawYield_6080_155_fit_19_21 = new TH1F("RawYield_6080_155_fit_19_21","", 1, 1.5, 5);
			RawYield_6080_155_fit_second = new TH1F("RawYield_6080_155_fit_second","", 1, 1.5, 5);
                       Ds_MeanMass_6080_155_fit = new TH1F("Ds_MeanMass_6080_155_fit","", 1, 1.5, 5); 
                       Ds_WidthMass_6080_155_fit = new TH1F("Ds_WidthMass_6080_155_fit","", 1, 1.5, 5); 

	int num_RSAll, num_hist, num_fit, num_fit_BKfromWS, num_fit_183_201, num_fit_19_21, num_fit_second, err_hist, err_fit, err_fit_BKfromWS, err_fit_183_201, err_fit_19_21, err_fit_second;
	double width_fit, width_fit_err, mean_fit, mean_fit_err, signi_fit, signi_fit_err, BkgNum, BkgNum_err, RSNum, RSNum_err;

	for (int i = 0; i<=4; i++)
	{
		if (i != 1)
		{
			for (int j =0; j<=3; j++)
			{

				Ds_RawYield_DiffFit_Split_run14(NameCent2[i].Data(), BDT_cut[i][j], pTBin_low[j], pTBin_high[j],  CenBin_low[i], CenBin_high[i], SigNum[i][j], num_RSAll, num_hist, num_fit, num_fit_BKfromWS, num_fit_183_201, num_fit_19_21, num_fit_second, err_hist, err_fit, err_fit_BKfromWS, err_fit_183_201, err_fit_19_21, err_fit_second, width_fit, width_fit_err, mean_fit, mean_fit_err, signi_fit, signi_fit_err, BkgNum, BkgNum_err, RSNum, RSNum_err);
				BkgNum_RS[i]->SetBinContent(j+2,BkgNum);
				BkgNum_RS[i]->SetBinError(j+2,BkgNum_err);
				RSNum_RS[i]->SetBinContent(j+2,RSNum);
				RSNum_RS[i]->SetBinError(j+2,RSNum_err);
				Significance_fit[i]->SetBinContent(j+2,signi_fit);
				Significance_fit[i]->SetBinError(j+2,signi_fit_err);
				SigNum_fit[i]->SetBinContent(j+2,num_fit);
				SigNum_fit[i]->SetBinError(j+2,err_fit);
				SigNum_Bin[i]->SetBinContent(j+2,num_hist);
				SigNum_Bin[i]->SetBinError(j+2,err_hist);
				RawYield_mT_fit[i]->SetBinContent(j+2,num_fit/mT_BR_Nev_dmT_dy[i][j]);
				RawYield_mT_fit[i]->SetBinError(j+2,err_fit/mT_BR_Nev_dmT_dy[i][j]);   
				RawYield_fit[i]->SetBinContent(j+2,num_fit/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit[i]->SetBinError(j+2,err_fit/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_BKfromWS[i]->SetBinContent(j+2,num_fit_BKfromWS/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_BKfromWS[i]->SetBinError(j+2,err_fit_BKfromWS/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_183_201[i]->SetBinContent(j+2,num_fit_183_201/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_183_201[i]->SetBinError(j+2,err_fit_183_201/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_19_21[i]->SetBinContent(j+2,num_fit_19_21/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_19_21[i]->SetBinError(j+2,err_fit_19_21/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_second[i]->SetBinContent(j+2,num_fit_second/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_second[i]->SetBinError(j+2,err_fit_second/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_hist[i]->SetBinContent(j+2,num_hist/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_hist[i]->SetBinError(j+2,err_hist/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_RSAll[i]->SetBinContent(j+2,num_RSAll/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_RSAll[i]->SetBinError(j+2, 0);
				Ds_MeanMass_fit[i]->SetBinContent(j+2, mean_fit);
				Ds_MeanMass_fit[i]->SetBinError(j+2, mean_fit_err);
				Ds_WidthMass_fit[i]->SetBinContent(j+2, width_fit);
				Ds_WidthMass_fit[i]->SetBinError(j+2, width_fit_err);
			}
		}
		else
		{
			for (int j =0; j<=4; j++)
			{

				Ds_RawYield_DiffFit_Split_run14(NameCent2[i].Data(), BDT_cut[i][j], pTBin_low_split[j], pTBin_high_split[j], CenBin_low[i], CenBin_high[i], SigNum[i][j], num_RSAll, num_hist, num_fit, num_fit_BKfromWS, num_fit_183_201, num_fit_19_21, num_fit_second, err_hist, err_fit, err_fit_BKfromWS, err_fit_183_201, err_fit_19_21, err_fit_second, width_fit, width_fit_err, mean_fit, mean_fit_err, signi_fit, signi_fit_err, BkgNum, BkgNum_err, RSNum, RSNum_err);
				BkgNum_RS[i]->SetBinContent(j+2,BkgNum);
				BkgNum_RS[i]->SetBinError(j+2,BkgNum_err);
				RSNum_RS[i]->SetBinContent(j+2,RSNum);
				RSNum_RS[i]->SetBinError(j+2,RSNum_err);
				Significance_fit[i]->SetBinContent(j+2,signi_fit);
				Significance_fit[i]->SetBinError(j+2,signi_fit_err);
				SigNum_fit[i]->SetBinContent(j+2, num_fit);
				SigNum_fit[i]->SetBinError(j+2, err_fit);
				SigNum_Bin[i]->SetBinContent(j+2,num_hist);
				SigNum_Bin[i]->SetBinError(j+2,err_hist);
				RawYield_mT_fit[i]->SetBinContent(j+2,num_fit/mT_BR_Nev_dmT_dy[i][j]);
				RawYield_mT_fit[i]->SetBinError(j+2,err_fit/mT_BR_Nev_dmT_dy[i][j]);   
				RawYield_fit[i]->SetBinContent(j+2,num_fit/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit[i]->SetBinError(j+2,err_fit/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_BKfromWS[i]->SetBinContent(j+2,num_fit_BKfromWS/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_BKfromWS[i]->SetBinError(j+2,err_fit_BKfromWS/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_183_201[i]->SetBinContent(j+2,num_fit_183_201/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_183_201[i]->SetBinError(j+2,err_fit_183_201/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_19_21[i]->SetBinContent(j+2,num_fit_19_21/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_19_21[i]->SetBinError(j+2,err_fit_19_21/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_second[i]->SetBinContent(j+2,num_fit_second/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_fit_second[i]->SetBinError(j+2,err_fit_second/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_hist[i]->SetBinContent(j+2,num_hist/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_hist[i]->SetBinError(j+2,err_hist/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_RSAll[i]->SetBinContent(j+2,num_RSAll/pT_BR_Nev_dpT_dy_run14[i][j]);
				RawYield_RSAll[i]->SetBinError(j+2, 0);
				Ds_MeanMass_fit[i]->SetBinContent(j+2, mean_fit);
				Ds_MeanMass_fit[i]->SetBinError(j+2, mean_fit_err);
				Ds_WidthMass_fit[i]->SetBinContent(j+2, width_fit);
				Ds_WidthMass_fit[i]->SetBinError(j+2, width_fit_err);
			}
		}
	}

				Ds_RawYield_DiffFit_Split_run14("1040", 106, 16, 25,  5, 7, 600, num_RSAll, num_hist, num_fit, num_fit_BKfromWS, num_fit_183_201, num_fit_19_21, num_fit_second, err_hist, err_fit, err_fit_BKfromWS, err_fit_183_201, err_fit_19_21, err_fit_second, width_fit, width_fit_err, mean_fit, mean_fit_err, signi_fit, signi_fit_err, BkgNum, BkgNum_err, RSNum, RSNum_err);
				BkgNum_1040_1525_RS->SetBinError(1,BkgNum_err);
				BkgNum_1040_1525_RS->SetBinContent(1,BkgNum);
				RSNum_1040_1525_RS->SetBinError(1,RSNum_err);
				RSNum_1040_1525_RS->SetBinContent(1,RSNum);
				Significance_1040_1525_fit->SetBinContent(1,signi_fit);
				Significance_1040_1525_fit->SetBinError(1,signi_fit_err);
				SigNum_1040_1525_fit->SetBinContent(1,num_fit);
				SigNum_1040_1525_fit->SetBinError(1,err_fit);
				SigNum_1040_1525_Bin->SetBinContent(1,num_hist);
				SigNum_1040_1525_Bin->SetBinError(1,err_hist);
				RawYield_1040_1525_hist->SetBinContent(1,num_hist/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_hist->SetBinError(1,err_hist/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit->SetBinContent(1,num_fit/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit->SetBinError(1,err_fit/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit_BKfromWS->SetBinContent(1,num_fit_BKfromWS/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit_BKfromWS->SetBinError(1,err_fit_BKfromWS/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit_183_201->SetBinContent(1,num_fit_183_201/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit_183_201->SetBinError(1,err_fit_183_201/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit_19_21->SetBinContent(1,num_fit_19_21/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit_19_21->SetBinError(1,err_fit_19_21/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit_second->SetBinContent(1,num_fit_second/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				RawYield_1040_1525_fit_second->SetBinError(1,err_fit_second/(12.56*0.0227*pT[0]*dpT[0]*dY*Nev_14[1]));
				Ds_RawYield_DiffFit_Split_run14("4080", 52, 16, 50,  3, 4, 349, num_RSAll, num_hist, num_fit, num_fit_BKfromWS, num_fit_183_201, num_fit_19_21, num_fit_second, err_hist, err_fit, err_fit_BKfromWS, err_fit_183_201, err_fit_19_21, err_fit_second, width_fit, width_fit_err, mean_fit, mean_fit_err, signi_fit, signi_fit_err, BkgNum, BkgNum_err, RSNum, RSNum_err);//52+28, 52-30
				BkgNum_4060_155_RS->SetBinError(1,BkgNum_err);
				BkgNum_4060_155_RS->SetBinContent(1,BkgNum);
				RSNum_4060_155_RS->SetBinError(1,RSNum_err);
				RSNum_4060_155_RS->SetBinContent(1,RSNum);
				Significance_4060_155_fit->SetBinContent(1,signi_fit);
				Significance_4060_155_fit->SetBinError(1,signi_fit_err);
				SigNum_4060_155_fit->SetBinContent(1,num_fit);
				SigNum_4060_155_fit->SetBinError(1,err_fit);
				SigNum_4060_155_Bin->SetBinContent(1,num_hist);
				SigNum_4060_155_Bin->SetBinError(1,err_hist);
				RawYield_4060_155_hist->SetBinContent(1,num_hist/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_hist->SetBinError(1,err_hist/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit->SetBinContent(1,num_fit/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit->SetBinError(1,err_fit/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit_BKfromWS->SetBinContent(1,num_fit_BKfromWS/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit_BKfromWS->SetBinError(1,err_fit_BKfromWS/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit_183_201->SetBinContent(1,num_fit_183_201/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit_183_201->SetBinError(1,err_fit_183_201/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit_19_21->SetBinContent(1,num_fit_19_21/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit_19_21->SetBinError(1,err_fit_19_21/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit_second->SetBinContent(1,num_fit_second/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				RawYield_4060_155_fit_second->SetBinError(1,err_fit_second/(12.56*0.0227*2.61486*3.5*dY*2.4e8));
				Ds_MeanMass_4060_155_fit->SetBinContent(1, mean_fit);
				Ds_MeanMass_4060_155_fit->SetBinError(1, mean_fit_err);
				Ds_WidthMass_4060_155_fit->SetBinContent(1, width_fit);
				Ds_WidthMass_4060_155_fit->SetBinError(1, width_fit_err);
				Ds_RawYield_DiffFit_Split_run14("4080", 51, 16, 50,  1, 2, 44, num_RSAll, num_hist, num_fit, num_fit_BKfromWS, num_fit_183_201, num_fit_19_21, num_fit_second, err_hist, err_fit, err_fit_BKfromWS, err_fit_183_201, err_fit_19_21, err_fit_second, width_fit, width_fit_err, mean_fit, mean_fit_err, signi_fit, signi_fit_err, BkgNum, BkgNum_err, RSNum, RSNum_err);//51+28, 51-30
				BkgNum_6080_155_RS->SetBinError(1,BkgNum_err);
				BkgNum_6080_155_RS->SetBinContent(1,BkgNum);
				RSNum_6080_155_RS->SetBinError(1,RSNum_err);
				RSNum_6080_155_RS->SetBinContent(1,RSNum);
				Significance_6080_155_fit->SetBinContent(1,signi_fit);
				Significance_6080_155_fit->SetBinError(1,signi_fit_err);
				SigNum_6080_155_fit->SetBinContent(1,num_fit);
				SigNum_6080_155_fit->SetBinError(1,err_fit);
				SigNum_6080_155_Bin->SetBinContent(1,num_hist);
				SigNum_6080_155_Bin->SetBinError(1,err_hist);
				RawYield_6080_155_hist->SetBinContent(1,num_hist/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_hist->SetBinError(1,err_hist/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit->SetBinContent(1,num_fit/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit->SetBinError(1,err_fit/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit_BKfromWS->SetBinContent(1,num_fit_BKfromWS/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit_BKfromWS->SetBinError(1,err_fit_BKfromWS/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit_183_201->SetBinContent(1,num_fit_183_201/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit_183_201->SetBinError(1,err_fit_183_201/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit_19_21->SetBinContent(1,num_fit_19_21/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit_19_21->SetBinError(1,err_fit_19_21/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit_second->SetBinContent(1,num_fit_second/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				RawYield_6080_155_fit_second->SetBinError(1,err_fit_second/(12.56*0.0227*2.61486*3.5*dY*2.34e8));
				Ds_MeanMass_6080_155_fit->SetBinContent(1, mean_fit);
				Ds_MeanMass_6080_155_fit->SetBinError(1, mean_fit_err);
				Ds_WidthMass_6080_155_fit->SetBinContent(1, width_fit);
				Ds_WidthMass_6080_155_fit->SetBinError(1, width_fit_err);
	output->cd();
	for (int i = 0; i<=4; i++)
	{

		BkgNum_RS[i]->Write();
		RSNum_RS[i]->Write();
		Significance_fit[i]->Write();
		SigNum_fit[i]->Write();
		SigNum_Bin[i]->Write();
		RawYield_mT_fit[i]->Write();
		RawYield_hist[i]->Write();
		RawYield_fit[i]->Write();
		RawYield_fit_BKfromWS[i]->Write();
		RawYield_fit_183_201[i]->Write();
		RawYield_fit_19_21[i]->Write();
		RawYield_fit_second[i]->Write();
		Ds_MeanMass_fit[i]->Write();
		Ds_WidthMass_fit[i]->Write();

	}	
RSNum_1040_1525_RS->Write();
BkgNum_1040_1525_RS->Write();
Significance_1040_1525_fit->Write();
SigNum_1040_1525_fit->Write();
SigNum_1040_1525_Bin->Write();
RawYield_1040_1525_hist->Write();
RawYield_1040_1525_fit->Write();
RawYield_1040_1525_fit_BKfromWS->Write();
RawYield_1040_1525_fit_183_201->Write();
RawYield_1040_1525_fit_19_21->Write();
RawYield_1040_1525_fit_second->Write();

RSNum_4060_155_RS->Write();
BkgNum_4060_155_RS->Write();
Significance_4060_155_fit->Write();
SigNum_4060_155_fit->Write();
SigNum_4060_155_Bin->Write();
RawYield_4060_155_hist->Write();
RawYield_4060_155_fit->Write();
RawYield_4060_155_fit_BKfromWS->Write();
RawYield_4060_155_fit_183_201->Write();
RawYield_4060_155_fit_19_21->Write();
RawYield_4060_155_fit_second->Write();
Ds_MeanMass_4060_155_fit->Write();
Ds_WidthMass_4060_155_fit->Write();

RSNum_6080_155_RS->Write();
BkgNum_6080_155_RS->Write();
Significance_6080_155_fit->Write();
SigNum_6080_155_fit->Write();
SigNum_6080_155_Bin->Write();
RawYield_6080_155_hist->Write();
RawYield_6080_155_fit->Write();
RawYield_6080_155_fit_BKfromWS->Write();
RawYield_6080_155_fit_183_201->Write();
RawYield_6080_155_fit_19_21->Write();
RawYield_6080_155_fit_second->Write();
Ds_MeanMass_6080_155_fit->Write();
Ds_WidthMass_6080_155_fit->Write();
	return 0;

}





