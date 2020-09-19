#include <stdio.h>
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include "TDatime.h"
#include "TSystem.h"
#include "TPad.h"
#include "TVirtualPad.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TString.h"
#include "StyleUtilities.h"
#include "Draw.h"

void SysError_Ds_run1416()
{

	TLine* drawLine(Double_t xlow,Double_t ylow, Double_t xup, Double_t yup, Double_t lineWidth, Int_t lineColor,Int_t linestyle);
	void shiftTGraph(TGraphErrors *gr1, Float_t shift);
	void drawSysError(TGraphAsymmErrors *gsyserr,double width=0.2, double length=0.1);
	void drawSysError(TGraphErrors *gsyserr,double width=0.2, double length=0.1);
	void scaleGraph(TGraphAsymmErrors *gr,Double_t scale);
	void scaleGraph(TGraphErrors *gr,Double_t scale);
	void drawSysError(TGraphAsymmErrors *gsyserr,double width, double length)
	{
		//cout<<"num = " << gsyserr->GetN()<<endl; 
		for(int i=0;i<gsyserr->GetN();i++) {
			float x   = gsyserr->GetX()[i];
			float y   = gsyserr->GetY()[i];
			float ey_l  = gsyserr->GetEYlow()[i];
			float ey_h  = gsyserr->GetEYhigh()[i];
			double x1 = x - width;
			double x2 = x + width;
			double y1 = y - ey_l;
			double y2 = y + ey_h;
			double len = length;
			//	cout<< " y = " << y<<  endl;
			//	cout << " ey_l = " << ey_l << "ey_h =  " << ey_h << endl;
			//	 cout << " x1 = " << x1 << "x2 = " << x2 << "y1 = " << y1 << "y2 = " << y2<< endl;  
			TLine *l1 = new TLine(x1,y1,x2,y1); // -
			l1->SetLineWidth(2.5);
			l1->SetLineColor(gsyserr->GetMarkerColor());
			l1->Draw("same");
			TLine *l2 = new TLine(x1,y2,x2,y2); // -
			l2->SetLineWidth(2.5);
			l2->SetLineColor(gsyserr->GetMarkerColor());
			l2->Draw("same");
			TLine *l3 = new TLine(x1,y1,x1,y1+len);
			l3->SetLineWidth(2.5);
			l3->SetLineColor(gsyserr->GetMarkerColor());
			l3->Draw("same");
			TLine *l4 = new TLine(x1,y2,x1,y2-len);
			l4->SetLineWidth(2.5);
			l4->SetLineColor(gsyserr->GetMarkerColor());
			l4->Draw("same");
			TLine *l5 = new TLine(x2,y1,x2,y1+len);
			l5->SetLineWidth(2.5);
			l5->SetLineColor(gsyserr->GetMarkerColor());
			l5->Draw("same");
			TLine *l6 = new TLine(x2,y2,x2,y2-len);
			l6->SetLineWidth(2.5);
			l6->SetLineColor(gsyserr->GetMarkerColor());
			l6->Draw("same");
		}

	}
	void drawSysError(TGraphErrors *gsyserr,double width, double length)
	{
		//cout<<"num = " << gsyserr->GetN()<<endl; 
		for(int i=0;i<gsyserr->GetN();i++) {
			float x   = gsyserr->GetX()[i];
			float y   = gsyserr->GetY()[i];
			float ey_l  = gsyserr->GetEY()[i];
			float ey_h  = gsyserr->GetEY()[i];
			double x1 = x - width;
			double x2 = x + width;
			double y1 = y - ey_l;
			double y2 = y + ey_h;
			double len = length*y;
			//      cout<< " y = " << y<<  endl;
			//	      cout << " ey_l = " << ey_l << "ey_h =  " << ey_h << endl; 
			//         cout << " x1 = " << x1 << "x2 = " << x2 << "y1 = " << y1 << "y2 = " << y2<< endl;
			TLine *l1 = new TLine(x1,y1,x2,y1); // -
			l1->SetLineWidth(2.5);
			l1->SetLineColor(gsyserr->GetMarkerColor());
			l1->Draw("same");
			TLine *l2 = new TLine(x1,y2,x2,y2); // -
			l2->SetLineWidth(2.5);
			l2->SetLineColor(gsyserr->GetMarkerColor());
			l2->Draw("same");
			TLine *l3 = new TLine(x1,y1,x1,y1+len);
			l3->SetLineWidth(2.5);
			l3->SetLineColor(gsyserr->GetMarkerColor());
			l3->Draw("same");
			TLine *l4 = new TLine(x1,y2,x1,y2-len);
			l4->SetLineWidth(2.5);
			l4->SetLineColor(gsyserr->GetMarkerColor());
			l4->Draw("same");
			TLine *l5 = new TLine(x2,y1,x2,y1+len);
			l5->SetLineWidth(2.5);
			l5->SetLineColor(gsyserr->GetMarkerColor());
			l5->Draw("same");
			TLine *l6 = new TLine(x2,y2,x2,y2-len);
			l6->SetLineWidth(2.5);
			l6->SetLineColor(gsyserr->GetMarkerColor());
			l6->Draw("same");
		}

	}

	void shiftTGraph(TGraphErrors *gr1, Float_t shift)
	{
		Int_t NPoint = gr1->GetN();
		for(int i=0;i<NPoint;i++)
		{
			float x = gr1->GetX()[i];
			float y = gr1->GetY()[i];
			float ex = gr1->GetEX()[i];
			float ey = gr1->GetEY()[i];

			gr1->SetPoint(i,x+shift,y);
			gr1->SetPointError(i, ex, ey);
		}
	}

	void scaleGraph(TGraphAsymmErrors *gr,Double_t scale)
	{
		Int_t NPoint = gr->GetN();
		for(int i=0;i<NPoint;i++)
		{
			Double_t x = gr->GetX()[i];
			Double_t y = gr->GetY()[i];
			Double_t exl = gr->GetEXlow()[i];
			Double_t eyl = gr->GetEYlow()[i];
			Double_t exh = gr->GetEXhigh()[i];
			Double_t eyh = gr->GetEYhigh()[i];
			y = scale*y;
			gr->SetPoint(i,x,y);
			gr->SetPointError(i,exl,exh,eyl*scale,eyh*scale);
		}
	}

	void scaleGraph(TGraphErrors *gr,Double_t scale)
	{
		Int_t NPoint = gr->GetN();
		for(int i=0;i<NPoint;i++)
		{
			Double_t x = gr->GetX()[i];
			Double_t y = gr->GetY()[i];
			Double_t ex = gr->GetEX()[i];
			Double_t ey = gr->GetEY()[i];
			y = scale*y;
			gr->SetPoint(i,x,y);
			gr->SetPointError(i, ex, ey*scale);
		}
	}


	TH1::SetDefaultSumw2();
	TFile *input_RawYield_run14 = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/Raw_root/Ds_RawYield_run14_phy_defaultBDTcut.root");
	TFile *input_RawYield_highBDTcut_run14  = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/Raw_root/Ds_RawYield_run14_phy_highBDTcut.root");
	TFile *input_RawYield_lowBDTcut_run14  = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/Raw_root/Ds_RawYield_run14_phy_lowBDTcut.root");
	TFile *input_RawYield_run16 = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/Raw_root/Ds_RawYield_run16_Combined_phyAndsst_defaultBDTcut.root");
	TFile *input_RawYield_highBDTcut_run16  = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/Raw_root/Ds_RawYield_run16_Combined_phyAndsst_highBDTcut.root");
	TFile *input_RawYield_lowBDTcut_run16  = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/Raw_root/Ds_RawYield_run16_Combined_phyAndsst_lowBDTcut.root");


	TFile *input_Eff_run14 = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/eff_root/DsEff_0080_18_kpT0.5_NFit20_phy_run14_DefaultBDT_final.root");
	TFile *input_Eff_highBDTcut_run14  = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/eff_root/DsEff_0080_18_kpT0.5_NFit20_phy_run14_HighBDT_final.root");
	TFile *input_Eff_lowBDTcut_run14  = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/eff_root/DsEff_0080_18_kpT0.5_NFit20_phy_run14_LowBDT_final.root");
	TFile *input_Eff_run16 = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/eff_root/DsEff_0080_18_kpT0.5_NFit20_sstAndphy_run16_DefaultBDT_final.root");
	TFile *input_Eff_run16_D0pTShape = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/eff_root/DsEff_0080_18_kpT0.5_NFit20_sstAndphy_run16_DefaultBDT_D0pTShape_final.root");
	TFile *input_Eff_highBDTcut_run16  = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/eff_root/DsEff_0080_18_kpT0.5_NFit20_sstAndphy_run16_HighBDT_final.root");
	TFile *input_Eff_lowBDTcut_run16  = TFile::Open("/star/u/fuchuan/data02/Ds/Ds_code_GPC/analysis/eff_root/DsEff_0080_18_kpT0.5_NFit20_sstAndphy_run16_LowBDT_final.root");

	TFile *output_DsYield_Myrun14 = new TFile("Spectrum_run1416_Ds.root","recreate");
	TFile *output_SysErr = new TFile("SysError_run1416.root","recreate");
//	TFile *output_DsYield_Sys = new TFile("DsYield_Sys_run1416.root","recreate");

	TH1F *Ds_RawYield_hist_run14[10];
	TH1F *Ds_RawYield_fit_run14[10];
	TH1F *Ds_RawYield_fit_183_201_run14[10];
	TH1F *Ds_RawYield_fit_19_21_run14[10];
	TH1F *Ds_RawYield_fit_second_run14[10];
	TH1F *Ds_RawYield_fit_highBDTcut_run14[10];
	TH1F *Ds_RawYield_fit_lowBDTcut_run14[10];
	TH1F *Ds_RawYield_hist_run16[10];
	TH1F *Ds_RawYield_fit_run16[10];
	TH1F *Ds_RawYield_fit_183_201_run16[10];
	TH1F *Ds_RawYield_fit_19_21_run16[10];
	TH1F *Ds_RawYield_fit_second_run16[10];
	TH1F *Ds_RawYield_fit_highBDTcut_run16[10];
	TH1F *Ds_RawYield_fit_lowBDTcut_run16[10];

	TH1F *Ds_Yield_hist_run14[10];
	TH1F *Ds_Yield_fit_run14[10];
	TH1F *Ds_Yield_fit_183_201_run14[10];
	TH1F *Ds_Yield_fit_19_21_run14[10];
	TH1F *Ds_Yield_fit_second_run14[10];
	TH1F *Ds_Yield_fit_highBDTcut_run14[10];
	TH1F *Ds_Yield_fit_lowBDTcut_run14[10];
	TH1F *Ds_Yield_hist_run16[10];
	TH1F *Ds_Yield_fit_run16_D0pTShape[10];
	TH1F *Ds_Yield_fit_run16[10];
	TH1F *Ds_Yield_fit_183_201_run16[10];
	TH1F *Ds_Yield_fit_19_21_run16[10];
	TH1F *Ds_Yield_fit_second_run16[10];
	TH1F *Ds_Yield_fit_highBDTcut_run16[10];
	TH1F *Ds_Yield_fit_lowBDTcut_run16[10];


	TH1F *Ds_EffFinal_run14[10];
	TH1F *Ds_EffFinal_highBDTcut_run14[10];
	TH1F *Ds_EffFinal_lowBDTcut_run14[10];	
	TH1F *Ds_EffFinal_run16[10];
	TH1F *Ds_EffFinal_run16_D0pTShape[10];
	TH1F *Ds_EffFinal_highBDTcut_run16[10];
	TH1F *Ds_EffFinal_lowBDTcut_run16[10];	

	TH1F *mh1Sys_RawYield_run14[8];
	TH1F *mh1Sys_TPC_run14[8];
	TH1F *mh1Sys_PID_run14[8];
	TH1F *mh1Sys_BDTcut_run14[8];
	TH1F *mh1Sys_SecTrack_run14[8];
	TH1F *mh1Sys_pTShape_run14[8];
	TH1F *mh1Sys_RawYield_run16[8];
	TH1F *mh1Sys_TPC_run16[8];
	TH1F *mh1Sys_PID_run16[8];
	TH1F *mh1Sys_BDTcut_run16[8];
	TH1F *mh1Sys_SecTrack_run16[8];
	TH1F *mh1Sys_pTShape_run16[8];

double VertexCor[3] = {0.83932, 0.875405, 0.685425};
	TString const Name_D0run14[3] = {"0_10", "10_40", "40_80"};
	TString const Name_Cent[8] = {"0-10%", "10-40%", "40-80%", "40-60%", "60-80%", "10-40%_(1.5-2.5)", "10-20%", "20-40%"};
	TString const hName_Cent[8] = {"0_10", "10_40_binning", "40_80", "40_60", "60_80", "10_40", "10_20", "20_40"};
	TString const hNameRawYield_fit[8] = {"h010_fit", "h1040_fit", "h4080_fit", "RawYield_4060_155_fit", "RawYield_6080_155_fit", "RawYield_1040_1525_fit", "h1020_fit", "h2040_fit"};
	TString const hNameRawYield_hist[8] = {"h010_hist", "h1040_hist", "h4080_hist", "RawYield_4060_155_hist", "RawYield_6080_155_hist", "RawYield_1040_1525_hist", "h1020_hist", "h2040_hist"};
	TString const hNameRawYield_fit_183_201[8] = {"h010_fit_183_201", "h1040_fit_183_201", "h4080_fit_183_201", "RawYield_4060_155_fit_183_201", "RawYield_6080_155_fit_183_201", "RawYield_1040_1525_fit_183_201", "h1020_fit_183_201", "h2040_fit_183_201"};
	TString const hNameRawYield_fit_19_21[8] = {"h010_fit_19_21", "h1040_fit_19_21", "h4080_fit_19_21", "RawYield_4060_155_fit_19_21", "RawYield_6080_155_fit_19_21", "RawYield_1040_1525_fit_19_21", "h1020_fit_19_21", "h2040_fit_19_21"};
	TString const hNameRawYield_fit_second[8] = {"h010_fit_second", "h1040_fit_second", "h4080_fit_second", "RawYield_4060_155_fit_second", "RawYield_6080_155_fit_second", "RawYield_1040_1525_fit_second", "h1020_fit_second", "h2040_fit_second"};
	TString const hName_EffFinal[8] = {"PassAllEff_0", "PassAllEff_1", "PassAllEff_2", "PassAllEff_46", "PassAllEff_68","PassAllEff_1040_1525", "PassAllEff_3", "PassAllEff_4"};
	float pTbins[6] = {0, 1.5, 2.5, 3.5, 5, 8}; 
	float pTbins_split[7] = {0, 1, 2, 2.5, 3.5, 5, 8}; 

	double gr_x[8][6] = {{-100, 1.95121, 2.93578, 4.1161, 6.09053, 100}, {-100, 1.48558, 2.23541, 2.93578, 4.1161, 6.09053}, {-100, 1.95121, 2.93578, 4.1161, 6.09053, 100}, {2.61486, 300, 400, 500, 600, 700}, {2.61486, 300, 400, 500, 600, 700}, {1.95121, 300, 400, 500, 600, 700}, {-100, 1.95121, 2.93578, 4.1161, 6.09053, 100}, {-100, 1.95121, 2.93578, 4.1161, 6.09053, 100}};
	double e_x[6] = {0};

	double Ds_Yield_hist_run14_bin[8][6];
	double Ds_Yield_fit_run14_bin[8][6];
	double Ds_Yield_fit_183_201_run14_bin[8][6];
	double Ds_Yield_fit_19_21_run14_bin[8][6];
	double Ds_Yield_fit_second_run14_bin[8][6];
	double Ds_Yield_highBDTcut_run14_bin[8][6];
	double Ds_Yield_lowBDTcut_run14_bin[8][6];
	double Ds_Yield_hist_run16_bin[8][6];
	double Ds_Yield_fit_run16_D0pTShape_bin[8][6];
	double Ds_Yield_fit_run16_bin[8][6];
	double Ds_Yield_fit_183_201_run16_bin[8][6];
	double Ds_Yield_fit_19_21_run16_bin[8][6];
	double Ds_Yield_fit_second_run16_bin[8][6];
	double Ds_Yield_highBDTcut_run16_bin[8][6];
	double Ds_Yield_lowBDTcut_run16_bin[8][6];

	double Ds_Yield_hist_run14_err[8][6];
	double Ds_Yield_fit_run14_err[8][6];
	double Ds_Yield_fit_183_201_run14_err[8][6];
	double Ds_Yield_fit_19_21_run14_err[8][6];
	double Ds_Yield_fit_second_run14_err[8][6];
	double Ds_Yield_highBDTcut_run14_err[8][6];
	double Ds_Yield_lowBDTcut_run14_err[8][6];
	double Ds_Yield_hist_run16_err[8][6];
	double Ds_Yield_fit_run16_D0pTShape_err[8][6];
	double Ds_Yield_fit_run16_err[8][6];
	double Ds_Yield_fit_183_201_run16_err[8][6];
	double Ds_Yield_fit_19_21_run16_err[8][6];
	double Ds_Yield_fit_second_run16_err[8][6];
	double Ds_Yield_highBDTcut_run16_err[8][6];
	double Ds_Yield_lowBDTcut_run16_err[8][6];


	double Ds_SysError_run16[8][6];      
	double Ds_TotalError_run16[8][6];      
	double Ds_SysError_run14[8][6];      
	double Ds_TotalError_run14[8][6];      
	double Ds_SysError_forRatio_run16[8][6];      
	double Ds_SysError_forRatio_run14[8][6];      

	double Diff_fit_hist_run14_bin[8][6]; 
	double Diff_fit_183_201_run14_bin[8][6]; 
	double Diff_fit_19_21_run14_bin[8][6]; 
	double Diff_fit_second_run14_bin[8][6];
	double sys_rawYield_run14[8][6]; 
	double Diff_highBDTcut_run14_bin[8][6]; 
	double Diff_lowBDTcut_run14_bin[8][6];

	double Diff_fit_hist_run16_bin[8][6]; 
	double Diff_fit_hist_run16_bin_D0pTShape[8][6]; 
	double Sys_pTShape[8][6]; 
	double Diff_fit_183_201_run16_bin[8][6]; 
	double Diff_fit_19_21_run16_bin[8][6]; 
	double Diff_fit_second_run16_bin[8][6];
	double sys_rawYield_run16[8][6]; 
	double Diff_highBDTcut_run16_bin[8][6]; 
	double Diff_lowBDTcut_run16_bin[8][6];

	double Correlation_stat_highBDT_run14[8][6];
	double Correlation_stat_lowBDT_run14[8][6];
	double sys_highBDTcut_run14_bin[8][6];
	double sys_lowBDTcut_run14_bin[8][6];
	double sys_BDTcut_run14_bin[8][6];

	double Correlation_stat_highBDT_run16[8][6];
	double Correlation_stat_lowBDT_run16[8][6];
	double sys_highBDTcut_run16_bin[8][6];
	double sys_lowBDTcut_run16_bin[8][6];
	double sys_BDTcut_run16_bin[8][6];

	double w_stat_run14[8][6];
	double w_stat_run16[8][6];
	double Ds_Yield_stat_run1416_bin[8][6];
	double Ds_Yield_stat_run1416_err[8][6];
	double Ds_Yield_sys_run1416_err[8][6];
	double Ds_Yield_sys_forRatio_run1416_err[8][6];


	TGraphErrors *grDs_Yield_fit_run14[8];
	TGraphErrors *grDs_Yield_fit_183_201_run14[8];
	TGraphErrors *grDs_Yield_fit_19_21_run14[8];
	TGraphErrors *grDs_Yield_fit_second_run14[8];
	TGraphErrors *grDs_Yield_highBDTcut_run14[8];
	TGraphErrors *grDs_Yield_lowBDTcut_run14[8];

	TGraphErrors *grDs_Yield_fit_run16[8];
	TGraphErrors *grDs_Yield_fit_183_201_run16[8];
	TGraphErrors *grDs_Yield_fit_19_21_run16[8];
	TGraphErrors *grDs_Yield_fit_second_run16[8];
	TGraphErrors *grDs_Yield_highBDTcut_run16[8];
	TGraphErrors *grDs_Yield_lowBDTcut_run16[8];

	TGraphErrors *grDs_Yield_SysError_run16[8];
	TGraphErrors *grDs_Yield_TotalError_run16[8];
	TGraphErrors *grDs_Yield_SysError_run14[8];
	TGraphErrors *grDs_Yield_TotalError_run14[8];
	TGraphErrors *grDs_Yield_stat_run1416[8];
	TGraphErrors *grDs_Yield_sys_run1416[8];
	TGraphErrors *grDs_Yield_sys_forRatio_run1416[8];

        TGraphErrors *grDs_stat_Rcp_Base4080_run1416[8];          
        TGraphErrors *grDs_sys_Rcp_Base4080_run1416[8];          

	double Rcp_defaultBDT_run14[8][6];
	double Rcp_highBDT_run14[8][6];
	double Diff_Rcp_highBDT_run14[8][6];
	double Rcp_lowBDT_run14[8][6];
	double Diff_Rcp_lowBDT_run14[8][6];
	double RcpSys_BDTcut_run14[8][6];

	double Rcp_defaultBDT_run16[8][6];
	double Rcp_highBDT_run16[8][6];
	double Diff_Rcp_highBDT_run16[8][6];
	double Rcp_lowBDT_run16[8][6];
	double Diff_Rcp_lowBDT_run16[8][6];
	double RcpSys_BDTcut_run16[8][6];

	double RcpSys_BDTcut_run1416[8][6];
	double RcpSys_RawYield_run1416[8][6];
	double Sys_RawYield_run1416[8][6];
	double RcpSys_run1416[8][6];
	double Rcp_run1416[8][6];
	double Rcp_statErr_run1416[8][6];
	double Rcp_Scale_num[8] = {938.8, 386.8, 56.99, 91.37, 21.37, 386.8, 579.89, 288.35};

	double ErrorAdd(double x, double y)
	{
		return sqrt(x*x + y*y);
	}
	double ErrorDiv(double x, double y, double dx, double dy)
	{
		return x/y*ErrorAdd(dx/x, dy/y);
	}

	for (int i = 0; i <=7; i++ )

	{

		Ds_RawYield_hist_run14[i] = (TH1F*)input_RawYield_run14->Get(hNameRawYield_hist[i].Data());
		Ds_RawYield_fit_run14[i] = (TH1F*)input_RawYield_run14->Get(hNameRawYield_fit[i].Data());
		Ds_RawYield_fit_183_201_run14[i] = (TH1F*)input_RawYield_run14->Get(hNameRawYield_fit_183_201[i].Data());
		Ds_RawYield_fit_19_21_run14[i] = (TH1F*)input_RawYield_run14->Get(hNameRawYield_fit_19_21[i].Data());
		Ds_RawYield_fit_second_run14[i] = (TH1F*)input_RawYield_run14->Get(hNameRawYield_fit_second[i].Data());
		Ds_RawYield_fit_highBDTcut_run14[i] = (TH1F*)input_RawYield_highBDTcut_run14->Get(hNameRawYield_fit[i].Data());
		Ds_RawYield_fit_lowBDTcut_run14[i] = (TH1F*)input_RawYield_lowBDTcut_run14->Get(hNameRawYield_fit[i].Data());
		Ds_EffFinal_run14[i] = (TH1F*)input_Eff_run14->Get(hName_EffFinal[i].Data()); 
		Ds_EffFinal_highBDTcut_run14[i] = (TH1F*)input_Eff_highBDTcut_run14->Get(hName_EffFinal[i].Data()); 
		Ds_EffFinal_lowBDTcut_run14[i] = (TH1F*)input_Eff_lowBDTcut_run14->Get(hName_EffFinal[i].Data()); 
if (i==2 || i==3 || i==4)
{
Ds_EffFinal_run14[i]->Scale(VertexCor[i-2]);
Ds_EffFinal_highBDTcut_run14[i]->Scale(VertexCor[i-2]);
Ds_EffFinal_lowBDTcut_run14[i]->Scale(VertexCor[i-2]);
}

		Ds_Yield_hist_run14[i] = new TH1F(*Ds_RawYield_hist_run14[i]);
		Ds_Yield_hist_run14[i]->Divide(Ds_RawYield_hist_run14[i], Ds_EffFinal_run14[i], 1, 1);
		Ds_Yield_fit_run14[i] = new TH1F(*Ds_RawYield_fit_run14[i]);
		Ds_Yield_fit_run14[i]->Divide(Ds_RawYield_fit_run14[i], Ds_EffFinal_run14[i], 1, 1);
		Ds_Yield_fit_183_201_run14[i] = new TH1F(*Ds_RawYield_fit_183_201_run14[i]);
		Ds_Yield_fit_183_201_run14[i]->Divide(Ds_RawYield_fit_183_201_run14[i], Ds_EffFinal_run14[i], 1, 1);
		Ds_Yield_fit_19_21_run14[i] = new TH1F(*Ds_RawYield_fit_19_21_run14[i]);
		Ds_Yield_fit_19_21_run14[i]->Divide(Ds_RawYield_fit_19_21_run14[i], Ds_EffFinal_run14[i], 1, 1);
		Ds_Yield_fit_second_run14[i] = new TH1F(*Ds_RawYield_fit_second_run14[i]);
		Ds_Yield_fit_second_run14[i]->Divide(Ds_RawYield_fit_second_run14[i], Ds_EffFinal_run14[i], 1, 1);
		Ds_Yield_fit_highBDTcut_run14[i] = new TH1F(*Ds_RawYield_fit_highBDTcut_run14[i]);
		Ds_Yield_fit_highBDTcut_run14[i]->Divide(Ds_RawYield_fit_highBDTcut_run14[i], Ds_EffFinal_highBDTcut_run14[i], 1, 1);
		Ds_Yield_fit_lowBDTcut_run14[i] = new TH1F(*Ds_RawYield_fit_lowBDTcut_run14[i]);
		Ds_Yield_fit_lowBDTcut_run14[i]->Divide(Ds_RawYield_fit_lowBDTcut_run14[i], Ds_EffFinal_lowBDTcut_run14[i], 1, 1);

		Ds_RawYield_hist_run16[i] = (TH1F*)input_RawYield_run16->Get(hNameRawYield_hist[i].Data());
		Ds_RawYield_fit_run16[i] = (TH1F*)input_RawYield_run16->Get(hNameRawYield_fit[i].Data());
		Ds_RawYield_fit_183_201_run16[i] = (TH1F*)input_RawYield_run16->Get(hNameRawYield_fit_183_201[i].Data());
		Ds_RawYield_fit_19_21_run16[i] = (TH1F*)input_RawYield_run16->Get(hNameRawYield_fit_19_21[i].Data());
		Ds_RawYield_fit_second_run16[i] = (TH1F*)input_RawYield_run16->Get(hNameRawYield_fit_second[i].Data());
		Ds_RawYield_fit_highBDTcut_run16[i] = (TH1F*)input_RawYield_highBDTcut_run16->Get(hNameRawYield_fit[i].Data());
		Ds_RawYield_fit_lowBDTcut_run16[i] = (TH1F*)input_RawYield_lowBDTcut_run16->Get(hNameRawYield_fit[i].Data());
		Ds_EffFinal_run16[i] = (TH1F*)input_Eff_run16->Get(hName_EffFinal[i].Data()); 
		Ds_EffFinal_run16_D0pTShape[i] = (TH1F*)input_Eff_run16_D0pTShape->Get(hName_EffFinal[i].Data()); 
		Ds_EffFinal_highBDTcut_run16[i] = (TH1F*)input_Eff_highBDTcut_run16->Get(hName_EffFinal[i].Data()); 
		Ds_EffFinal_lowBDTcut_run16[i] = (TH1F*)input_Eff_lowBDTcut_run16->Get(hName_EffFinal[i].Data()); 
if (i==2 || i==3 || i==4)
{
Ds_EffFinal_run16[i]->Scale(VertexCor[i-2]);
Ds_EffFinal_run16_D0pTShape[i]->Scale(VertexCor[i-2]);
Ds_EffFinal_highBDTcut_run16[i]->Scale(VertexCor[i-2]);
Ds_EffFinal_lowBDTcut_run16[i]->Scale(VertexCor[i-2]);
}
//cout << "Ds_EffFinal_run16[i]->GetBinContent(1) = "<< Ds_EffFinal_run16[i]->GetBinContent(1) << endl;
//cout << "Ds_EffFinal_run16_D0pTShape[i]->GetBinContent(1) = "<< Ds_EffFinal_run16_D0pTShape[i]->GetBinContent(1) << endl;

		Ds_Yield_hist_run16[i] = new TH1F(*Ds_RawYield_hist_run16[i]);
		Ds_Yield_hist_run16[i]->Divide(Ds_RawYield_hist_run16[i], Ds_EffFinal_run16[i], 1, 1);
		Ds_Yield_fit_run16_D0pTShape[i] = new TH1F(*Ds_RawYield_hist_run16[i]);
		Ds_Yield_fit_run16_D0pTShape[i]->Divide(Ds_RawYield_fit_run16[i], Ds_EffFinal_run16_D0pTShape[i], 1, 1);
		Ds_Yield_fit_run16[i] = new TH1F(*Ds_RawYield_fit_run16[i]);
		Ds_Yield_fit_run16[i]->Divide(Ds_RawYield_fit_run16[i], Ds_EffFinal_run16[i], 1, 1);
		Ds_Yield_fit_183_201_run16[i] = new TH1F(*Ds_RawYield_fit_183_201_run16[i]);
		Ds_Yield_fit_183_201_run16[i]->Divide(Ds_RawYield_fit_183_201_run16[i], Ds_EffFinal_run16[i], 1, 1);
		Ds_Yield_fit_19_21_run16[i] = new TH1F(*Ds_RawYield_fit_19_21_run16[i]);
		Ds_Yield_fit_19_21_run16[i]->Divide(Ds_RawYield_fit_19_21_run16[i], Ds_EffFinal_run16[i], 1, 1);
		Ds_Yield_fit_second_run16[i] = new TH1F(*Ds_RawYield_fit_second_run16[i]);
		Ds_Yield_fit_second_run16[i]->Divide(Ds_RawYield_fit_second_run16[i], Ds_EffFinal_run16[i], 1, 1);
		Ds_Yield_fit_highBDTcut_run16[i] = new TH1F(*Ds_RawYield_fit_highBDTcut_run16[i]);
		Ds_Yield_fit_highBDTcut_run16[i]->Divide(Ds_RawYield_fit_highBDTcut_run16[i], Ds_EffFinal_highBDTcut_run16[i], 1, 1);
		Ds_Yield_fit_lowBDTcut_run16[i] = new TH1F(*Ds_RawYield_fit_lowBDTcut_run16[i]);
		Ds_Yield_fit_lowBDTcut_run16[i]->Divide(Ds_RawYield_fit_lowBDTcut_run16[i], Ds_EffFinal_lowBDTcut_run16[i], 1, 1);

		if (i == 1)
		{ 
			mh1Sys_RawYield_run14[i] = new TH1F(Form("mh1Sys_RawYield_run14_%i",i),Form("mh1Sys_RawYield_run14_%i",i), 6, pTbins_split );
			mh1Sys_PID_run14[i] = new TH1F(Form("mh1Sys_PID_run14_%i",i),Form("mh1Sys_PID_run14_%i",i), 6, pTbins_split );
			mh1Sys_TPC_run14[i] = new TH1F(Form("mh1Sys_TPC_run14_%i",i),Form("mh1Sys_TPC_run14_%i",i), 6, pTbins_split );
			mh1Sys_BDTcut_run14[i] = new TH1F(Form("mh1Sys_BDTcut_run14_%i",i),Form("mh1Sys_BDTcut_run14_%i",i), 6, pTbins_split );
			mh1Sys_SecTrack_run14[i] = new TH1F(Form("mh1Sys_SecTrack_run14_%i",i),Form("mh1Sys_SecTrack_run14_%i",i), 6, pTbins_split );
			mh1Sys_pTShape_run14[i] = new TH1F(Form("mh1Sys_pTShape_run14_%i",i),Form("mh1Sys_pTShape_run14_%i",i), 6, pTbins_split );
			mh1Sys_RawYield_run16[i] = new TH1F(Form("mh1Sys_RawYield_run16_%i",i),Form("mh1Sys_RawYield_run16_%i",i), 6, pTbins_split );
			mh1Sys_PID_run16[i] = new TH1F(Form("mh1Sys_PID_run16_%i",i),Form("mh1Sys_PID_run16_%i",i), 6, pTbins_split );
			mh1Sys_TPC_run16[i] = new TH1F(Form("mh1Sys_TPC_run16_%i",i),Form("mh1Sys_TPC_run16_%i",i), 6, pTbins_split );
			mh1Sys_BDTcut_run16[i] = new TH1F(Form("mh1Sys_BDTcut_run16_%i",i),Form("mh1Sys_BDTcut_run16_%i",i), 6, pTbins_split );
			mh1Sys_SecTrack_run16[i] = new TH1F(Form("mh1Sys_SecTrack_run16_%i",i),Form("mh1Sys_SecTrack_run16_%i",i), 6, pTbins_split );
			mh1Sys_pTShape_run16[i] = new TH1F(Form("mh1Sys_pTShape_run16_%i",i),Form("mh1Sys_pTShape_run16_%i",i), 6, pTbins_split );
		}
		else  if(i == 3 || i == 4 || i == 5)
		{
			mh1Sys_RawYield_run14[i] = new TH1F(Form("mh1Sys_RawYield_run14_%i",i),Form("mh1Sys_RawYield_run14_%i",i), 1, 1.5, 5 );
			mh1Sys_PID_run14[i] = new TH1F(Form("mh1Sys_PID_run14_%i",i),Form("mh1Sys_PID_run14_%i",i), 1, 1.5, 5 );
			mh1Sys_TPC_run14[i] = new TH1F(Form("mh1Sys_TPC_run14_%i",i),Form("mh1Sys_TPC_run14_%i",i), 1, 1.5, 5 );
			mh1Sys_BDTcut_run14[i] = new TH1F(Form("mh1Sys_BDTcut_run14_%i",i),Form("mh1Sys_BDTcut_run14_%i",i), 1, 1.5, 5 );
			mh1Sys_SecTrack_run14[i] = new TH1F(Form("mh1Sys_SecTrack_run14_%i",i),Form("mh1Sys_SecTrack_run14_%i",i), 1, 1.5, 5 );
			mh1Sys_pTShape_run14[i] = new TH1F(Form("mh1Sys_pTShape_run14_%i",i),Form("mh1Sys_pTShape_run14_%i",i), 1, 1.5, 5 );
			mh1Sys_RawYield_run16[i] = new TH1F(Form("mh1Sys_RawYield_run16_%i",i),Form("mh1Sys_RawYield_run16_%i",i), 1, 1.5, 5 );
			mh1Sys_PID_run16[i] = new TH1F(Form("mh1Sys_PID_run16_%i",i),Form("mh1Sys_PID_run16_%i",i), 1, 1.5, 5 );
			mh1Sys_TPC_run16[i] = new TH1F(Form("mh1Sys_TPC_run16_%i",i),Form("mh1Sys_TPC_run16_%i",i), 1, 1.5, 5 );
			mh1Sys_BDTcut_run16[i] = new TH1F(Form("mh1Sys_BDTcut_run16_%i",i),Form("mh1Sys_BDTcut_run16_%i",i), 1, 1.5, 5 );
			mh1Sys_SecTrack_run16[i] = new TH1F(Form("mh1Sys_SecTrack_run16_%i",i),Form("mh1Sys_SecTrack_run16_%i",i), 1, 1.5, 5 );
			mh1Sys_pTShape_run16[i] = new TH1F(Form("mh1Sys_pTShape_run16_%i",i),Form("mh1Sys_pTShape_run16_%i",i), 1, 1.5, 5 );
		}
		else
		{
			mh1Sys_RawYield_run14[i] = new TH1F(Form("mh1Sys_RawYield_run14_%i",i),Form("mh1Sys_RawYield_run14_%i",i), 5, pTbins );
			mh1Sys_PID_run14[i] = new TH1F(Form("mh1Sys_PID_run14_%i",i),Form("mh1Sys_PID_run14_%i",i), 5, pTbins );
			mh1Sys_TPC_run14[i] = new TH1F(Form("mh1Sys_TPC_run14_%i",i),Form("mh1Sys_TPC_run14_%i",i), 5, pTbins );
			mh1Sys_BDTcut_run14[i] = new TH1F(Form("mh1Sys_BDTcut_run14_%i",i),Form("mh1Sys_BDTcut_run14_%i",i), 5, pTbins );
			mh1Sys_SecTrack_run14[i] = new TH1F(Form("mh1Sys_SecTrack_run14_%i",i),Form("mh1Sys_SecTrack_run14_%i",i), 5, pTbins );
			mh1Sys_pTShape_run14[i] = new TH1F(Form("mh1Sys_pTShape_run14_%i",i),Form("mh1Sys_pTShape_run14_%i",i), 5, pTbins );
			mh1Sys_RawYield_run16[i] = new TH1F(Form("mh1Sys_RawYield_run16_%i",i),Form("mh1Sys_RawYield_run16_%i",i), 5, pTbins );
			mh1Sys_PID_run16[i] = new TH1F(Form("mh1Sys_PID_run16_%i",i),Form("mh1Sys_PID_run16_%i",i), 5, pTbins );
			mh1Sys_TPC_run16[i] = new TH1F(Form("mh1Sys_TPC_run16_%i",i),Form("mh1Sys_TPC_run16_%i",i), 5, pTbins );
			mh1Sys_BDTcut_run16[i] = new TH1F(Form("mh1Sys_BDTcut_run16_%i",i),Form("mh1Sys_BDTcut_run16_%i",i), 5, pTbins );
			mh1Sys_SecTrack_run16[i] = new TH1F(Form("mh1Sys_SecTrack_run16_%i",i),Form("mh1Sys_SecTrack_run16_%i",i), 5, pTbins );
			mh1Sys_pTShape_run16[i] = new TH1F(Form("mh1Sys_pTShape_run16_%i",i),Form("mh1Sys_pTShape_run16_%i",i), 5, pTbins );
		}

	}
/*	
	output_DsYield_Sys->cd();
		for (int i = 0; i < 8 ; i++)
		{
		Ds_Yield_fit_run16[i]->SetName(Form("Ds_Yield_fit_run16_%i", i));
		Ds_Yield_fit_run16[i]->Write();
		Ds_Yield_fit_run14[i]->SetName(Form("Ds_Yield_fit_run14_%i", i));
		Ds_Yield_fit_run14[i]->Write();

		Ds_Yield_hist_run16[i]->SetName(Form("Ds_Yield_hist_run16_%i", i));
		Ds_Yield_fit_183_201_run16[i]->SetName(Form("Ds_Yield_fit_183_201_run16_%i", i));
		Ds_Yield_fit_19_21_run16[i]->SetName(Form("Ds_Yield_fit_19_21_run16_%i", i));
		Ds_Yield_fit_second_run16[i]->SetName(Form("Ds_Yield_fit_second_run16_%i", i));
		Ds_Yield_fit_highBDTcut_run16[i]->SetName(Form("Ds_Yield_fit_highBDTcut_run16_%i", i));
		Ds_Yield_fit_lowBDTcut_run16[i]->SetName(Form("Ds_Yield_fit_lowBDTcut_run16_%i", i));
		Ds_Yield_hist_run16[i]->Write();
		Ds_Yield_fit_183_201_run16[i]->Write();
		Ds_Yield_fit_19_21_run16[i]->Write();
		Ds_Yield_fit_second_run16[i]->Write();
		Ds_Yield_fit_highBDTcut_run16[i]->Write();
		Ds_Yield_fit_lowBDTcut_run16[i]->Write();

		Ds_Yield_hist_run14[i]->SetName(Form("Ds_Yield_hist_run14_%i", i));
		Ds_Yield_fit_183_201_run14[i]->SetName(Form("Ds_Yield_fit_183_201_run14_%i", i));
		Ds_Yield_fit_19_21_run14[i]->SetName(Form("Ds_Yield_fit_19_21_run14_%i", i));
		Ds_Yield_fit_second_run14[i]->SetName(Form("Ds_Yield_fit_second_run14_%i", i));
		Ds_Yield_fit_highBDTcut_run14[i]->SetName(Form("Ds_Yield_fit_highBDTcut_run14_%i", i));
		Ds_Yield_fit_lowBDTcut_run14[i]->SetName(Form("Ds_Yield_fit_lowBDTcut_run14_%i", i));
		Ds_Yield_hist_run14[i]->Write();
		Ds_Yield_fit_183_201_run14[i]->Write();
		Ds_Yield_fit_19_21_run14[i]->Write();
		Ds_Yield_fit_second_run14[i]->Write();
		Ds_Yield_fit_highBDTcut_run14[i]->Write();
		Ds_Yield_fit_lowBDTcut_run14[i]->Write();
		}
*/
	 
	TF1 *pTSpectra_mT_My[3];
	TF1 *Exponential_Run14My_Fitted[3];
	TF1 *Exponential_Run14Nasim_Fitted[3];
	TF1 *Exponential_Run16My_Fitted[3];
	TF1 *Ratio_fit_run16_My[3];
	TF1 *Ratio_fit_run16_Nasim[3];
	TF1 *Exponential[3];

	TF1 *Exponential_Run16My = new TF1("Exponential_Run16My","[0]*exp([1]*x + [2])",1.5, 8);
	TF1 *Exponential_Run14My = new TF1("Exponential_Run14My","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.96828*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.96828*1.96828)-1.96828)/([2]*[1]),-[2])",1, 8);
	TF1 *Exponential_Run14My_Fit;
	TF1 *Exponential_Run14Nasim = new TF1("Exponential_Run14Nasim","[0]*exp([1]*x + [2])",1.5, 8);
	TF1 *Ratio_fit_run16_My;
	TF1 *Ratio_fit_run16_Nasim;
	Exponential_Run16My->SetLineStyle(2);
	Exponential_Run16My->SetLineColor(1);
	Exponential_Run16My->SetLineWidth(1);

	Exponential_Run14My->SetLineStyle(2);
	Exponential_Run14My->SetLineColor(2);
	Exponential_Run14My->SetLineWidth(1);
	Exponential_Run14My->SetParameters(0.255, 0.545, 5);

	Exponential_Run14Nasim->SetLineStyle(2);
	Exponential_Run14Nasim->SetLineColor(4);
	Exponential_Run14Nasim->SetLineWidth(1);
	for(Int_t i=0; i<=2; i++)
	{
		Exponential[i] = new TF1(Form("Exponential_%i", i ),"[0]*exp([1]*x + [2])",1.5, 8);
		Exponential_Run14My_Fitted[i] = new TF1(Form("Exponential_Run14My_Fitted_%i", i),"[0]*exp([1]*x + [2])",1.5, 8);
		Exponential_Run14Nasim_Fitted[i] = new TF1(Form("Exponential_Run14Nasim_Fitted_%i", i),"[0]*exp([1]*x + [2])",1.5, 8);
		Exponential_Run16My_Fitted[i] = new TF1(Form("Exponential_Run16My_Fitted_%i", i),"[0]*exp([1]*x + [2])",1.5, 8);
		Exponential[i]->SetParameters(1.5, -1.5, -1.5);
		Exponential_Run14My_Fitted[i]->SetParameters(1.5, -1.5, -1.5);
		Exponential_Run14Nasim_Fitted[i]->SetParameters(1.5, -1.5, -1.5);
		Exponential_Run16My_Fitted[i]->SetParameters(1.5, -1.5, -1.5);
		Exponential[i]->SetLineStyle(2);
		Exponential_Run14My_Fitted[i]->SetLineStyle(2);
		Exponential_Run14Nasim_Fitted[i]->SetLineStyle(2);
		Exponential_Run16My_Fitted[i]->SetLineStyle(2);
		Exponential[i]->SetLineColor(28);
		Exponential_Run14My_Fitted[i]->SetLineColor(2);
		Exponential_Run14Nasim_Fitted[i]->SetLineColor(4);
		Exponential_Run16My_Fitted[i]->SetLineColor(1);
		Exponential[i]->SetLineWidth(1);
		Exponential_Run14My_Fitted[i]->SetLineWidth(1);
		Exponential_Run14Nasim_Fitted[i]->SetLineWidth(1);
		Exponential_Run16My_Fitted[i]->SetLineWidth(1);
	}

	for(Int_t i=0; i<=7; i++)
	{
	//	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
		for(Int_t j=0; j<=5; j++)
		{

			Ds_Yield_hist_run14_bin[i][j] = Ds_Yield_hist_run14[i]->GetBinContent(j+1);         
			Ds_Yield_fit_run14_bin[i][j] = Ds_Yield_fit_run14[i]->GetBinContent(j+1);         
			Ds_Yield_fit_183_201_run14_bin[i][j] = Ds_Yield_fit_183_201_run14[i]->GetBinContent(j+1);         
			Ds_Yield_fit_19_21_run14_bin[i][j] = Ds_Yield_fit_19_21_run14[i]->GetBinContent(j+1);         
			Ds_Yield_fit_second_run14_bin[i][j] = Ds_Yield_fit_second_run14[i]->GetBinContent(j+1);         
			Ds_Yield_highBDTcut_run14_bin[i][j] = Ds_Yield_fit_highBDTcut_run14[i]->GetBinContent(j+1);         
			Ds_Yield_lowBDTcut_run14_bin[i][j] = Ds_Yield_fit_lowBDTcut_run14[i]->GetBinContent(j+1);         
			//cout << "Ds_Yield_fit_run14_bin[i][j] =" << Ds_Yield_fit_run14_bin[i][j] << endl;
			Ds_Yield_hist_run14_err[i][j] = Ds_Yield_hist_run14[i]->GetBinError(j+1);         
			Ds_Yield_fit_run14_err[i][j] = Ds_Yield_fit_run14[i]->GetBinError(j+1);         
			Ds_Yield_fit_183_201_run14_err[i][j] = Ds_Yield_fit_183_201_run14[i]->GetBinError(j+1);         
			Ds_Yield_fit_19_21_run14_err[i][j] = Ds_Yield_fit_19_21_run14[i]->GetBinError(j+1);         
			Ds_Yield_fit_second_run14_err[i][j] = Ds_Yield_fit_second_run14[i]->GetBinError(j+1);         
			Ds_Yield_highBDTcut_run14_err[i][j] = Ds_Yield_fit_highBDTcut_run14[i]->GetBinError(j+1);         
			Ds_Yield_lowBDTcut_run14_err[i][j] = Ds_Yield_fit_lowBDTcut_run14[i]->GetBinError(j+1);         

			Diff_fit_hist_run14_bin[i][j] = Ds_Yield_fit_run14_bin[i][j] - Ds_Yield_hist_run14_bin[i][j];
			Diff_highBDTcut_run14_bin[i][j] = Ds_Yield_fit_run14_bin[i][j] - Ds_Yield_highBDTcut_run14_bin[i][j];
			Diff_lowBDTcut_run14_bin[i][j] = Ds_Yield_fit_run14_bin[i][j] - Ds_Yield_lowBDTcut_run14_bin[i][j];
			Diff_fit_183_201_run14_bin[i][j] = Ds_Yield_fit_run14_bin[i][j] - Ds_Yield_fit_183_201_run14_bin[i][j];
			Diff_fit_19_21_run14_bin[i][j] = Ds_Yield_fit_run14_bin[i][j] - Ds_Yield_fit_19_21_run14_bin[i][j];
			Diff_fit_second_run14_bin[i][j] = Ds_Yield_fit_run14_bin[i][j] - Ds_Yield_fit_second_run14_bin[i][j];

			sys_rawYield_run14[i][j] = fabs(Diff_fit_183_201_run14_bin[i][j]) > fabs(Diff_fit_19_21_run14_bin[i][j]) ? fabs(Diff_fit_183_201_run14_bin[i][j]) : fabs(Diff_fit_19_21_run14_bin[i][j]);
			sys_rawYield_run14[i][j] = fabs(sys_rawYield_run14[i][j]) > fabs(Diff_fit_second_run14_bin[i][j]) ? fabs(sys_rawYield_run14[i][j]) : fabs(Diff_fit_second_run14_bin[i][j]);
//			             cout << "fabs(Diff_fit_hist_run14_bin[i][j]) = " << fabs(Diff_fit_hist_run14_bin[i][j]) << endl;
//			             cout << "fabs(Diff_fit_183_201_run14_bin[i][j]) = " << fabs(Diff_fit_183_201_run14_bin[i][j]) << endl;
//			       cout << "fabs(Diff_fit_19_21_run14_bin[i][j]) = " << fabs(Diff_fit_19_21_run14_bin[i][j]) << endl;
//			   cout << " fabs(Diff_fit_second_run14_bin[i][j]) = " << fabs(Diff_fit_second_run14_bin[i][j]) << endl;
//			cout << " sys_rawYield_run14[i][j] = " << sys_rawYield_run14[i][j]  << endl;
			Correlation_stat_highBDT_run14[i][j] = sqrt(fabs(Ds_Yield_fit_run14_err[i][j]*Ds_Yield_fit_run14_err[i][j] - Ds_Yield_highBDTcut_run14_err[i][j]*Ds_Yield_highBDTcut_run14_err[i][j]));
			Correlation_stat_lowBDT_run14[i][j] = sqrt(fabs(Ds_Yield_fit_run14_err[i][j]*Ds_Yield_fit_run14_err[i][j] - Ds_Yield_lowBDTcut_run14_err[i][j]*Ds_Yield_lowBDTcut_run14_err[i][j]));
			sys_highBDTcut_run14_bin[i][j] = fabs(Diff_highBDTcut_run14_bin[i][j]) - Correlation_stat_highBDT_run14[i][j];
			sys_lowBDTcut_run14_bin[i][j] = fabs(Diff_lowBDTcut_run14_bin[i][j]) - Correlation_stat_lowBDT_run14[i][j];
			if ( sys_highBDTcut_run14_bin[i][j] <=0 && sys_lowBDTcut_run14_bin[i][j] <=0 ) { sys_BDTcut_run14_bin[i][j] = 0;}
			else if ( sys_highBDTcut_run14_bin[i][j] <= 0 ) { sys_BDTcut_run14_bin[i][j] = sys_lowBDTcut_run14_bin[i][j];}
			else if ( sys_lowBDTcut_run14_bin[i][j] <= 0 ) { sys_BDTcut_run14_bin[i][j] = sys_highBDTcut_run14_bin[i][j];}
			else {sys_BDTcut_run14_bin[i][j] = sys_lowBDTcut_run14_bin[i][j] > sys_highBDTcut_run14_bin[i][j] ? sys_lowBDTcut_run14_bin[i][j] : sys_highBDTcut_run14_bin[i][j]; }
double sys_run14 = (sys_BDTcut_run14_bin[i][j]/Ds_Yield_fit_run14_bin[i][j]);
//cout << "Ds_Yield_fit_run14_bin[i][j] = " << Ds_Yield_fit_run14_bin[i][j] << endl;
//cout << "Ds_Yield_lowBDTcut_run14_bin[i][j] = " << Ds_Yield_lowBDTcut_run14_bin[i][j] << endl;
//cout << "Correlation_stat_lowBDT_run14[i][j] = " << Correlation_stat_lowBDT_run14[i][j] << endl;
//			cout << "sys_highBDTcut_run14_bin[i][j] = " << sys_highBDTcut_run14_bin[i][j] << endl;
//			cout << "sys_lowBDTcut_run14_bin[i][j] = " << sys_lowBDTcut_run14_bin[i][j] << endl;
//			cout << "sys_BDTcut_run14_bin[i][j]/Ds_Yield_fit_run14_bin[i][j] = " << sys_run14 << endl;


			Ds_Yield_hist_run16_bin[i][j] = Ds_Yield_hist_run16[i]->GetBinContent(j+1);         
			Ds_Yield_fit_run16_D0pTShape_bin[i][j] = Ds_Yield_fit_run16_D0pTShape[i]->GetBinContent(j+1);         
			Ds_Yield_fit_run16_bin[i][j] = Ds_Yield_fit_run16[i]->GetBinContent(j+1);         
			Ds_Yield_fit_183_201_run16_bin[i][j] = Ds_Yield_fit_183_201_run16[i]->GetBinContent(j+1);         
			Ds_Yield_fit_19_21_run16_bin[i][j] = Ds_Yield_fit_19_21_run16[i]->GetBinContent(j+1);         
			Ds_Yield_fit_second_run16_bin[i][j] = Ds_Yield_fit_second_run16[i]->GetBinContent(j+1);         
			Ds_Yield_highBDTcut_run16_bin[i][j] = Ds_Yield_fit_highBDTcut_run16[i]->GetBinContent(j+1);         
			Ds_Yield_lowBDTcut_run16_bin[i][j] = Ds_Yield_fit_lowBDTcut_run16[i]->GetBinContent(j+1);         

			Ds_Yield_hist_run16_err[i][j] = Ds_Yield_hist_run16[i]->GetBinError(j+1);         
			Ds_Yield_fit_run16_D0pTShape_err[i][j] = Ds_Yield_fit_run16_D0pTShape[i]->GetBinError(j+1);         
			Ds_Yield_fit_run16_err[i][j] = Ds_Yield_fit_run16[i]->GetBinError(j+1);         
			Ds_Yield_fit_183_201_run16_err[i][j] = Ds_Yield_fit_183_201_run16[i]->GetBinError(j+1);         
			Ds_Yield_fit_19_21_run16_err[i][j] = Ds_Yield_fit_19_21_run16[i]->GetBinError(j+1);         
			Ds_Yield_fit_second_run16_err[i][j] = Ds_Yield_fit_second_run16[i]->GetBinError(j+1);         
			Ds_Yield_highBDTcut_run16_err[i][j] = Ds_Yield_fit_highBDTcut_run16[i]->GetBinError(j+1);         
			Ds_Yield_lowBDTcut_run16_err[i][j] = Ds_Yield_fit_lowBDTcut_run16[i]->GetBinError(j+1);         

			Diff_fit_hist_run16_bin_D0pTShape[i][j] = fabs(Ds_Yield_fit_run16_D0pTShape_bin[i][j] - Ds_Yield_fit_run16_bin[i][j]);
                        Sys_pTShape[i][j] = Diff_fit_hist_run16_bin_D0pTShape[i][j]/Ds_Yield_fit_run16_bin[i][j];
			Diff_fit_hist_run16_bin[i][j] = Ds_Yield_fit_run16_bin[i][j] - Ds_Yield_hist_run16_bin[i][j];
			Diff_highBDTcut_run16_bin[i][j] = Ds_Yield_fit_run16_bin[i][j] - Ds_Yield_highBDTcut_run16_bin[i][j];
			Diff_lowBDTcut_run16_bin[i][j] = Ds_Yield_fit_run16_bin[i][j] - Ds_Yield_lowBDTcut_run16_bin[i][j];
//cout << "Sys_pTShape[i][j] = " << Sys_pTShape[i][j] << endl;
			Diff_fit_183_201_run16_bin[i][j] = Ds_Yield_fit_run16_bin[i][j] - Ds_Yield_fit_183_201_run16_bin[i][j];
			Diff_fit_19_21_run16_bin[i][j] = Ds_Yield_fit_run16_bin[i][j] - Ds_Yield_fit_19_21_run16_bin[i][j];
			Diff_fit_second_run16_bin[i][j] = Ds_Yield_fit_run16_bin[i][j] - Ds_Yield_fit_second_run16_bin[i][j];

			sys_rawYield_run16[i][j] = fabs(Diff_fit_183_201_run16_bin[i][j]) > fabs(Diff_fit_19_21_run16_bin[i][j]) ? fabs(Diff_fit_183_201_run16_bin[i][j]) : fabs(Diff_fit_19_21_run16_bin[i][j]);
			sys_rawYield_run16[i][j] = fabs(sys_rawYield_run16[i][j]) > fabs(Diff_fit_second_run16_bin[i][j]) ? fabs(sys_rawYield_run16[i][j]) : fabs(Diff_fit_second_run16_bin[i][j]);
/*			             cout << "fabs(Diff_fit_183_201_run16_bin[i][j]) = " << fabs(Diff_fit_183_201_run16_bin[i][j]) << endl;
			       cout << "fabs(Diff_fit_19_21_run16_bin[i][j]) = " << fabs(Diff_fit_19_21_run16_bin[i][j]) << endl;
			   cout << " fabs(Diff_fit_second_run16_bin[i][j]) = " << fabs(Diff_fit_second_run16_bin[i][j]) << endl;
			cout << " sys_rawYield_run16[i][j] = " << sys_rawYield_run16[i][j]  << endl;
			cout << " Ds_Yield_fit_run16_bin[i][j] = " << Ds_Yield_fit_run16_bin[i][j]  << endl;
*/
			Correlation_stat_highBDT_run16[i][j] = sqrt(fabs(Ds_Yield_fit_run16_err[i][j]*Ds_Yield_fit_run16_err[i][j] - Ds_Yield_highBDTcut_run16_err[i][j]*Ds_Yield_highBDTcut_run16_err[i][j]));
			Correlation_stat_lowBDT_run16[i][j] = sqrt(fabs(Ds_Yield_fit_run16_err[i][j]*Ds_Yield_fit_run16_err[i][j] - Ds_Yield_lowBDTcut_run16_err[i][j]*Ds_Yield_lowBDTcut_run16_err[i][j]));
			sys_highBDTcut_run16_bin[i][j] = fabs(Diff_highBDTcut_run16_bin[i][j]) - Correlation_stat_highBDT_run16[i][j];
			sys_lowBDTcut_run16_bin[i][j] = fabs(Diff_lowBDTcut_run16_bin[i][j]) - Correlation_stat_lowBDT_run16[i][j];
			if ( sys_highBDTcut_run16_bin[i][j] <=0 && sys_lowBDTcut_run16_bin[i][j] <=0 ) { sys_BDTcut_run16_bin[i][j] = 0;}
			else if ( sys_highBDTcut_run16_bin[i][j] <= 0 ) { sys_BDTcut_run16_bin[i][j] = sys_lowBDTcut_run16_bin[i][j];}
			else if ( sys_lowBDTcut_run16_bin[i][j] <= 0 ) { sys_BDTcut_run16_bin[i][j] = sys_highBDTcut_run16_bin[i][j];}
			else {sys_BDTcut_run16_bin[i][j] = sys_lowBDTcut_run16_bin[i][j] > sys_highBDTcut_run16_bin[i][j] ? sys_lowBDTcut_run16_bin[i][j] : sys_highBDTcut_run16_bin[i][j]; }

double sys_run16 = (sys_BDTcut_run16_bin[i][j]/Ds_Yield_fit_run16_bin[i][j]);
//			cout << "sys_highBDTcut_run16_bin[i][j] = " << sys_highBDTcut_run16_bin[i][j] << endl;
//			cout << "sys_lowBDTcut_run16_bin[i][j] = " << sys_lowBDTcut_run16_bin[i][j] << endl;
//cout << "Ds_Yield_fit_run16_bin[i][j] = " << Ds_Yield_fit_run16_bin[i][j] << endl;
//cout << "Ds_Yield_highBDTcut_run16_bin[i][j] = " << Ds_Yield_highBDTcut_run16_bin[i][j] << endl;
//cout << "Ds_Yield_lowBDTcut_run16_bin[i][j] = " << Ds_Yield_lowBDTcut_run16_bin[i][j] << endl;
//			cout << "sys_BDTcut_run16_bin[i][j]/Ds_Yield_fit_run16_bin[i][j] = " << sys_run16 << endl;
			Ds_SysError_run14[i][j] = sqrt(pow(sys_rawYield_run14[i][j],2) + pow(sys_BDTcut_run14_bin[i][j],2) + pow(Ds_Yield_fit_run14_bin[i][j]*0.09,2) + pow(Ds_Yield_fit_run14_bin[i][j]*0.03,2) + pow(Ds_Yield_fit_run14_bin[i][j]*0.03,2) + pow(Sys_pTShape[i][j]*Ds_Yield_fit_run14_bin[i][j], 2));//3% for TPC tracking, 1% for PID, 3% for secondary track from D0 2 < pT < 3 ;
			Ds_SysError_run16[i][j] = sqrt(pow(sys_rawYield_run16[i][j],2) + pow(sys_BDTcut_run16_bin[i][j],2) + pow(Ds_Yield_fit_run16_bin[i][j]*0.09,2) + pow(Ds_Yield_fit_run16_bin[i][j]*0.03,2) + pow(Ds_Yield_fit_run16_bin[i][j]*0.03,2) + pow(Diff_fit_hist_run16_bin_D0pTShape[i][j], 2));//3% for TPC tracking, 1% for PID, 3% for secondary track from D0 2 < pT < 3 ;

//double sys_BDTcut_14 = sys_BDTcut_run14_bin[i][j]/Ds_Yield_fit_run14_bin[i][j];
//double sys_BDTcut_16 = sys_BDTcut_run16_bin[i][j]/Ds_Yield_fit_run16_bin[i][j];
//if (i==1)
//{
//cout << " sys_BDTcut_14 = " << sys_BDTcut_14 << endl;
//cout << " sys_BDTcut_16 = " << sys_BDTcut_16 << endl;

//}
			//                      cout << "sys_BDTcut_run14_bin[i][j] = " << sys_BDTcut_run14_bin[i][j] << endl;
			//	cout << "Ds_Yield_fit_run14_bin[i][j] = " << Ds_Yield_fit_run14_bin[i][j] << endl;
			Ds_SysError_forRatio_run14[i][j] = sqrt(pow(sys_rawYield_run14[i][j],2) + pow(sys_BDTcut_run14_bin[i][j],2) + pow(Ds_Yield_fit_run14_bin[i][j]*0.03,2) + pow(Ds_Yield_fit_run14_bin[i][j]*0.01,2));
			Ds_TotalError_run14[i][j] = sqrt(pow(Ds_SysError_run14[i][j], 2) + pow(Ds_Yield_fit_run14_err[i][j], 2));	
			Ds_SysError_forRatio_run16[i][j] = sqrt(pow(sys_rawYield_run16[i][j],2) + pow(sys_BDTcut_run16_bin[i][j],2) + pow(Ds_Yield_fit_run16_bin[i][j]*0.03,2) + pow(Ds_Yield_fit_run14_bin[i][j]*0.01,2));
			Ds_TotalError_run16[i][j] = sqrt(pow(Ds_SysError_run16[i][j], 2) + pow(Ds_Yield_fit_run16_err[i][j], 2));	
			w_stat_run14[i][j] = 1/(Ds_Yield_fit_run14_err[i][j]*Ds_Yield_fit_run14_err[i][j]);
			w_stat_run16[i][j] = 1/(Ds_Yield_fit_run16_err[i][j]*Ds_Yield_fit_run16_err[i][j]);
			//cout << "w_stat_run14[i][j] =" << w_stat_run14[i][j] << endl;
			Ds_Yield_stat_run1416_bin[i][j] =( Ds_Yield_fit_run14_bin[i][j]*w_stat_run14[i][j] + Ds_Yield_fit_run16_bin[i][j]*w_stat_run16[i][j] )/(w_stat_run14[i][j] + w_stat_run16[i][j]);
				//		cout << " Ds_Yield_fit_run14_bin[i][j] = " << Ds_Yield_fit_run14_bin[i][j] << endl;
				//		cout << "Ds_Yield_fit_run16_bin[i][j] = " << Ds_Yield_fit_run16_bin[i][j] << endl;
			//			cout << " Ds_Yield_stat_run1416_bin[i][j] = " << Ds_Yield_stat_run1416_bin[i][j] << endl;
			Ds_Yield_stat_run1416_err[i][j] = sqrt(1/(w_stat_run14[i][j]+w_stat_run16[i][j]));
			Ds_Yield_sys_run1416_err[i][j] =( Ds_SysError_run14[i][j]*w_stat_run14[i][j] + Ds_SysError_run16[i][j]*w_stat_run16[i][j] )/(w_stat_run14[i][j] + w_stat_run16[i][j]);
			Ds_Yield_sys_forRatio_run1416_err[i][j] =( Ds_SysError_forRatio_run14[i][j]*w_stat_run14[i][j] + Ds_SysError_forRatio_run16[i][j]*w_stat_run16[i][j] )/(w_stat_run14[i][j] + w_stat_run16[i][j]);
			//Ds_ratio_sys_run1416_err[i][j] =( Ds_SysError_ratio_run14[i][j]*w_stat_run14[i][j] + Ds_SysError_ratio[i][j]*w_stat_run16[i][j] )/(w_stat_run14[i][j] + w_stat_run16[i][j]);		
			//DsD0_ratio_sys_run1416_err[i][j] = ErrorDiv(Ds_Yield_stat_run1416_bin[i][j], D0_Yield_run14_bin[i][j], Ds_ratio_sys_run1416_err[i][j], D0_Yield_sys_run14_err[i][j]);

			//			DsD0_ratio_stat_run1416_err[i][j] = ErrorDiv(Ds_Yield_stat_run1416_bin[i][j], D0_Yield_run14_bin[i][j], Ds_Yield_stat_run1416_err[i][j], D0_Yield_stat_run14_err[i][j]);
			//			DsD0_ratio_run1416_bin[i][j] = Ds_Yield_stat_run1416_bin[i][j]/D0_Yield_run14_bin[i][j];
		}
	}

	for ( int i  = 0; i<=7; i++)
	{
		if (i==0 || i==6 || i==7)//0: 0-10%; 6: 10-20%; 7: 20-40%
		{
			for(Int_t j=0; j<=5; j++)
			{
                           double y = Ds_Yield_stat_run1416_bin[i][j]/Rcp_Scale_num[i];
                           double err = Ds_Yield_stat_run1416_err[i][j]/Rcp_Scale_num[i];
                           double base = Ds_Yield_stat_run1416_bin[2][j]/Rcp_Scale_num[2];
                           double base_err = Ds_Yield_stat_run1416_err[2][j]/Rcp_Scale_num[2];
                                Rcp_run1416[i][j] = y/base;  
                                Rcp_statErr_run1416[i][j] = ErrorDiv(y, base, err, base_err);  
				Rcp_defaultBDT_run14[i][j] = Ds_Yield_fit_run14_bin[i][j]/Ds_Yield_fit_run14_bin[2][j];  
				Rcp_highBDT_run14[i][j] = Ds_Yield_highBDTcut_run14_bin[i][j]/Ds_Yield_highBDTcut_run14_bin[2][j];  
				Rcp_lowBDT_run14[i][j] = Ds_Yield_lowBDTcut_run14_bin[i][j]/Ds_Yield_lowBDTcut_run14_bin[2][j]; 
				Diff_Rcp_highBDT_run14[i][j] = fabs(Rcp_defaultBDT_run14[i][j]-Rcp_highBDT_run14[i][j]); 
				Diff_Rcp_lowBDT_run14[i][j] = fabs(Rcp_defaultBDT_run14[i][j]-Rcp_lowBDT_run14[i][j]); 
				RcpSys_BDTcut_run14[i][j] = TMath::Max(Diff_Rcp_highBDT_run14[i][j], Diff_Rcp_lowBDT_run14[i][j]);
                     // double Rcp_Relative_Sys = RcpSys_BDTcut_run14[i][j]/Rcp_defaultBDT_run14[i][j];
		//		cout << "Rcp_Relative_Sys =" << Rcp_Relative_Sys<< endl;
				Rcp_defaultBDT_run16[i][j] = Ds_Yield_fit_run16_bin[i][j]/Ds_Yield_fit_run16_bin[2][j];  
				Rcp_highBDT_run16[i][j] = Ds_Yield_highBDTcut_run16_bin[i][j]/Ds_Yield_highBDTcut_run16_bin[2][j];  
				Rcp_lowBDT_run16[i][j] = Ds_Yield_lowBDTcut_run16_bin[i][j]/Ds_Yield_lowBDTcut_run16_bin[2][j]; 
				Diff_Rcp_highBDT_run16[i][j] = fabs(Rcp_defaultBDT_run16[i][j]-Rcp_highBDT_run16[i][j]); 
				Diff_Rcp_lowBDT_run16[i][j] = fabs(Rcp_defaultBDT_run16[i][j]-Rcp_lowBDT_run16[i][j]); 
				RcpSys_BDTcut_run16[i][j] = TMath::Max(Diff_Rcp_highBDT_run16[i][j], Diff_Rcp_lowBDT_run16[i][j]);
                            RcpSys_BDTcut_run1416[i][j] = (RcpSys_BDTcut_run14[i][j]*w_stat_run14[i][j] + RcpSys_BDTcut_run16[i][j]*w_stat_run16[i][j])*(Rcp_Scale_num[2]/Rcp_Scale_num[i])/(w_stat_run14[i][j] + w_stat_run16[i][j]);
Sys_RawYield_run1416[i][j] =( sys_rawYield_run14[i][j]*w_stat_run14[i][j] + sys_rawYield_run16[i][j]*w_stat_run16[i][j] )/(w_stat_run14[i][j] + w_stat_run16[i][j]);
double SysErr_RawYield = Sys_RawYield_run1416[i][j]/Rcp_Scale_num[i];
double base_SysErr_RawYield = Sys_RawYield_run1416[2][j]/Rcp_Scale_num[2];
RcpSys_RawYield_run1416[i][j] = ErrorDiv(y, base, SysErr_RawYield, base_SysErr_RawYield);
RcpSys_run1416[i][j] = sqrt(pow(RcpSys_BDTcut_run1416[i][j], 2) + pow(RcpSys_RawYield_run1416[i][j], 2));
//cout << "RcpSys_BDTcut_run1416[i][j] = "<< RcpSys_BDTcut_run1416[i][j] << endl; 
//cout << "RcpSys_RawYield_run1416[i][j] = "<< RcpSys_RawYield_run1416[i][j] << endl; 
//cout << "RcpSys_run1416[i][j] = "<< RcpSys_run1416[i][j] << endl; 
//cout << "Rcp_run1416[i][j] = "<< Rcp_run1416[i][j] << endl; 
			}
grDs_stat_Rcp_Base4080_run1416[i]  = new TGraphErrors(6, gr_x[i], Rcp_run1416[i], e_x, Rcp_statErr_run1416[i]); 
grDs_sys_Rcp_Base4080_run1416[i]  = new TGraphErrors(6, gr_x[i], Rcp_run1416[i], e_x, RcpSys_run1416[i]); 
		}

}
	for ( int i  = 0; i<=7; i++)
		{
		if (i==1)
		{
			for ( int j  = 1; j<=5; j++)
			{
				mh1Sys_RawYield_run14[i]->SetBinContent(j+1, sys_rawYield_run14[i][j]/Ds_Yield_fit_run14_bin[i][j]);
				mh1Sys_RawYield_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_PID_run14[i]->SetBinContent(j+1, 0.03);
				mh1Sys_PID_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_TPC_run14[i]->SetBinContent(j+1, 0.09);
				mh1Sys_TPC_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_BDTcut_run14[i]->SetBinContent(j+1, sys_BDTcut_run14_bin[i][j]/Ds_Yield_fit_run14_bin[i][j]);
				mh1Sys_BDTcut_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_pTShape_run14[i]->SetBinContent(j+1, Sys_pTShape[i][j]);
				mh1Sys_pTShape_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_SecTrack_run14[i]->SetBinContent(j+1, 0.03);
				mh1Sys_SecTrack_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_RawYield_run16[i]->SetBinContent(j+1, sys_rawYield_run16[i][j]/Ds_Yield_fit_run16_bin[i][j]);
				mh1Sys_RawYield_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_PID_run16[i]->SetBinContent(j+1, 0.03);
				mh1Sys_PID_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_TPC_run16[i]->SetBinContent(j+1, 0.09);
				mh1Sys_TPC_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_BDTcut_run16[i]->SetBinContent(j+1, sys_BDTcut_run16_bin[i][j]/Ds_Yield_fit_run16_bin[i][j]);
				mh1Sys_BDTcut_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_pTShape_run16[i]->SetBinContent(j+1, Sys_pTShape[i][j]);
				mh1Sys_pTShape_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_SecTrack_run16[i]->SetBinContent(j+1, 0.03);
				mh1Sys_SecTrack_run16[i]->SetBinError(j+1, 1e-6);
			}
		}   
		else  if(i == 3 || i == 4 || i == 5)
		{
			for ( int j  = 0; j<=0; j++)
			{
				mh1Sys_RawYield_run14[i]->SetBinContent(j+1, sys_rawYield_run14[i][j]/Ds_Yield_fit_run14_bin[i][j]);
				mh1Sys_RawYield_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_PID_run14[i]->SetBinContent(j+1, 0.03);
				mh1Sys_PID_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_TPC_run14[i]->SetBinContent(j+1, 0.09);
				mh1Sys_TPC_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_BDTcut_run14[i]->SetBinContent(j+1, sys_BDTcut_run14_bin[i][j]/Ds_Yield_fit_run14_bin[i][j]);
				mh1Sys_BDTcut_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_pTShape_run14[i]->SetBinContent(j+1, Sys_pTShape[i][j]);
				mh1Sys_pTShape_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_SecTrack_run14[i]->SetBinContent(j+1, 0.03);
				mh1Sys_SecTrack_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_RawYield_run16[i]->SetBinContent(j+1, sys_rawYield_run16[i][j]/Ds_Yield_fit_run16_bin[i][j]);
				mh1Sys_RawYield_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_PID_run16[i]->SetBinContent(j+1, 0.03);
				mh1Sys_PID_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_TPC_run16[i]->SetBinContent(j+1, 0.09);
				mh1Sys_TPC_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_BDTcut_run16[i]->SetBinContent(j+1, sys_BDTcut_run16_bin[i][j]/Ds_Yield_fit_run16_bin[i][j]);
				mh1Sys_BDTcut_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_pTShape_run16[i]->SetBinContent(j+1, Sys_pTShape[i][j]);
				mh1Sys_pTShape_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_SecTrack_run16[i]->SetBinContent(j+1, 0.03);
				mh1Sys_SecTrack_run16[i]->SetBinError(j+1, 1e-6);
			}
		}
		else
		{
			for ( int j  = 1; j<=4; j++)
			{
				mh1Sys_RawYield_run14[i]->SetBinContent(j+1, sys_rawYield_run14[i][j]/Ds_Yield_fit_run14_bin[i][j]);
				mh1Sys_RawYield_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_PID_run14[i]->SetBinContent(j+1, 0.03);
				mh1Sys_PID_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_TPC_run14[i]->SetBinContent(j+1, 0.09);
				mh1Sys_TPC_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_BDTcut_run14[i]->SetBinContent(j+1, sys_BDTcut_run14_bin[i][j]/Ds_Yield_fit_run14_bin[i][j]);
				mh1Sys_BDTcut_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_pTShape_run14[i]->SetBinContent(j+1, Sys_pTShape[i][j]);
				mh1Sys_pTShape_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_SecTrack_run14[i]->SetBinContent(j+1, 0.03);
				mh1Sys_SecTrack_run14[i]->SetBinError(j+1, 1e-6);
				mh1Sys_RawYield_run16[i]->SetBinContent(j+1, sys_rawYield_run16[i][j]/Ds_Yield_fit_run16_bin[i][j]);
				mh1Sys_RawYield_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_PID_run16[i]->SetBinContent(j+1, 0.03);
				mh1Sys_PID_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_TPC_run16[i]->SetBinContent(j+1, 0.09);
				mh1Sys_TPC_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_BDTcut_run16[i]->SetBinContent(j+1, sys_BDTcut_run16_bin[i][j]/Ds_Yield_fit_run16_bin[i][j]);
				mh1Sys_BDTcut_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_pTShape_run16[i]->SetBinContent(j+1, Sys_pTShape[i][j]);
				mh1Sys_pTShape_run16[i]->SetBinError(j+1, 1e-6);
				mh1Sys_SecTrack_run16[i]->SetBinContent(j+1, 0.03);
				mh1Sys_SecTrack_run16[i]->SetBinError(j+1, 1e-6);
			}
		}
	}
	for ( int i  = 0; i<=7; i++)
	{

		grDs_Yield_fit_run14[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_run14_bin[i], e_x, Ds_Yield_fit_run14_err[i]); 
		grDs_Yield_fit_183_201_run14[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_183_201_run14_bin[i], e_x, Ds_Yield_fit_183_201_run14_err[i]); 
		grDs_Yield_fit_19_21_run14[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_19_21_run14_bin[i], e_x, Ds_Yield_fit_19_21_run14_err[i]); 
		grDs_Yield_fit_second_run14[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_second_run14_bin[i], e_x, Ds_Yield_fit_second_run14_err[i]); 
		grDs_Yield_highBDTcut_run14[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_highBDTcut_run14_bin[i], e_x, Ds_Yield_highBDTcut_run14_err[i]); 
		grDs_Yield_lowBDTcut_run14[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_lowBDTcut_run14_bin[i], e_x, Ds_Yield_lowBDTcut_run14_err[i]); 

		grDs_Yield_fit_run16[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_run16_bin[i], e_x, Ds_Yield_fit_run16_err[i]); 
		grDs_Yield_fit_183_201_run16[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_183_201_run16_bin[i], e_x, Ds_Yield_fit_183_201_run16_err[i]); 
		grDs_Yield_fit_19_21_run16[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_19_21_run16_bin[i], e_x, Ds_Yield_fit_19_21_run16_err[i]); 
		grDs_Yield_fit_second_run16[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_second_run16_bin[i], e_x, Ds_Yield_fit_second_run16_err[i]); 
		grDs_Yield_highBDTcut_run16[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_highBDTcut_run16_bin[i], e_x, Ds_Yield_highBDTcut_run16_err[i]); 
		grDs_Yield_lowBDTcut_run16[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_lowBDTcut_run16_bin[i], e_x, Ds_Yield_lowBDTcut_run16_err[i]); 

		grDs_Yield_SysError_run14[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_run14_bin[i], e_x, Ds_SysError_run14[i]); 
		grDs_Yield_TotalError_run14[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_run14_bin[i], e_x, Ds_TotalError_run14[i]); 
		grDs_Yield_SysError_run16[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_run16_bin[i], e_x, Ds_SysError_run16[i]);
		grDs_Yield_TotalError_run16[i] = new TGraphErrors(6, gr_x[i], Ds_Yield_fit_run16_bin[i], e_x, Ds_TotalError_run16[i]); 
		grDs_Yield_stat_run1416[i]  = new TGraphErrors(6, gr_x[i], Ds_Yield_stat_run1416_bin[i], e_x, Ds_Yield_stat_run1416_err[i]);
		grDs_Yield_sys_run1416[i]  = new TGraphErrors(6, gr_x[i], Ds_Yield_stat_run1416_bin[i], e_x, Ds_Yield_sys_run1416_err[i]);
		grDs_Yield_sys_forRatio_run1416[i]  = new TGraphErrors(6, gr_x[i], Ds_Yield_stat_run1416_bin[i], e_x, Ds_Yield_sys_forRatio_run1416_err[i]);


	}

	output_SysErr->cd();
	for (int i = 0; i < 8 ; i++)
	{
		mh1Sys_RawYield_run14[i]->Write();
		mh1Sys_TPC_run14[i]->Write();
		mh1Sys_PID_run14[i]->Write();
		mh1Sys_BDTcut_run14[i]->Write();
		mh1Sys_pTShape_run14[i]->Write();
		mh1Sys_SecTrack_run14[i]->Write();
		mh1Sys_RawYield_run16[i]->Write();
		mh1Sys_TPC_run16[i]->Write();
		mh1Sys_PID_run16[i]->Write();
		mh1Sys_BDTcut_run16[i]->Write();
		mh1Sys_pTShape_run16[i]->Write();
		mh1Sys_SecTrack_run16[i]->Write();
	}
     output_SysErr->Close();

	output_DsYield_Myrun14->cd();
	for (int i = 0; i < 8 ; i++)
	{

		/*	grDs_Yield_fit_run14[i]->SetName(Form("Ds_Yield_fit_%s_run14", hName_Cent[i].Data()));
			grDs_Yield_SysError_run14[i]->SetName(Form("Ds_Yield_SysError_%s_run14", hName_Cent[i].Data()));
			grDs_Yield_fit_183_201_run14[i]->SetName(Form("Ds_Yield_fit_182_205_%s_run14", hName_Cent[i].Data()));
			grDs_Yield_fit_19_21_run14[i]->SetName(Form("Ds_Yield_fit_19_21_%s_run14", hName_Cent[i].Data()));
			grDs_Yield_fit_second_run14[i]->SetName(Form("Ds_Yield_fit_second_%s_run14", hName_Cent[i].Data()));
			grDs_Yield_highBDTcut_run14[i]->SetName(Form("Ds_Yield_highBDTcut_%s_run14", hName_Cent[i].Data()));
			grDs_Yield_lowBDTcut_run14[i]->SetName(Form("Ds_Yield_lowBDTcut_%s_run14", hName_Cent[i].Data()));
			grDs_Yield_fit_run14[i]->Write();
			grDs_Yield_SysError_run14[i]->Write();
			grDs_Yield_fit_183_201_run14[i]->Write();
			grDs_Yield_fit_19_21_run14[i]->Write();
			grDs_Yield_fit_second_run14[i]->Write();
			grDs_Yield_highBDTcut_run14[i]->Write();
			grDs_Yield_lowBDTcut_run14[i]->Write();

			grDs_Yield_fit_run16[i]->SetName(Form("Ds_Yield_fit_%s_run16", hName_Cent[i].Data()));
			grDs_Yield_SysError_run16[i]->SetName(Form("Ds_Yield_SysError_%s_run16", hName_Cent[i].Data()));
			grDs_Yield_fit_183_201_run16[i]->SetName(Form("Ds_Yield_fit_182_205_%s_run16", hName_Cent[i].Data()));
			grDs_Yield_fit_19_21_run16[i]->SetName(Form("Ds_Yield_fit_19_21_%s_run16", hName_Cent[i].Data()));
			grDs_Yield_fit_second_run16[i]->SetName(Form("Ds_Yield_fit_second_%s_run16", hName_Cent[i].Data()));
			grDs_Yield_highBDTcut_run16[i]->SetName(Form("Ds_Yield_highBDTcut_%s_run16", hName_Cent[i].Data()));
			grDs_Yield_lowBDTcut_run16[i]->SetName(Form("Ds_Yield_lowBDTcut_%s_run16", hName_Cent[i].Data()));
			grDs_Yield_fit_run16[i]->Write();
			grDs_Yield_SysError_run16[i]->Write();
			grDs_Yield_fit_183_201_run16[i]->Write();
			grDs_Yield_fit_19_21_run16[i]->Write();
			grDs_Yield_fit_second_run16[i]->Write();
			grDs_Yield_highBDTcut_run16[i]->Write();
			grDs_Yield_lowBDTcut_run16[i]->Write();
		 */
		if (i == 1)
		{
			grDs_Yield_stat_run1416[i]->RemovePoint(0);
			grDs_Yield_sys_run1416[i]->RemovePoint(0);
			grDs_Yield_sys_forRatio_run1416[i]->RemovePoint(0);
                        grDs_Yield_fit_run14[i]->RemovePoint(0);
                        grDs_Yield_fit_run16[i]->RemovePoint(0);
                        grDs_Yield_SysError_run14[i]->RemovePoint(0);
                        grDs_Yield_SysError_run16[i]->RemovePoint(0);
		}
		else if (i == 3 || i == 4 || i == 5)
		{
			for (int j = 0; j < 5; j++)
			{
				grDs_Yield_stat_run1416[i]->RemovePoint(1);
				grDs_Yield_sys_run1416[i]->RemovePoint(1);
				grDs_Yield_sys_forRatio_run1416[i]->RemovePoint(1);
                        grDs_Yield_fit_run14[i]->RemovePoint(1);
                        grDs_Yield_fit_run16[i]->RemovePoint(1);
                        grDs_Yield_SysError_run14[i]->RemovePoint(1);
                        grDs_Yield_SysError_run16[i]->RemovePoint(1);
			}
		}
		else
		{
			grDs_Yield_stat_run1416[i]->RemovePoint(0);
			grDs_Yield_sys_run1416[i]->RemovePoint(0);
			grDs_Yield_sys_forRatio_run1416[i]->RemovePoint(0);
                        grDs_Yield_fit_run14[i]->RemovePoint(0);
                        grDs_Yield_fit_run16[i]->RemovePoint(0);
                        grDs_Yield_SysError_run14[i]->RemovePoint(0);
                        grDs_Yield_SysError_run16[i]->RemovePoint(0);

			grDs_Yield_stat_run1416[i]->RemovePoint(4);
			grDs_Yield_sys_run1416[i]->RemovePoint(4);
			grDs_Yield_sys_forRatio_run1416[i]->RemovePoint(4);
                        grDs_Yield_fit_run14[i]->RemovePoint(4);
                        grDs_Yield_fit_run16[i]->RemovePoint(4);
                        grDs_Yield_SysError_run14[i]->RemovePoint(4);
                        grDs_Yield_SysError_run16[i]->RemovePoint(4);
		}
		grDs_Yield_stat_run1416[i]->SetName(Form("Ds_Yield_stat_%s_run1416", hName_Cent[i].Data()));
		grDs_Yield_sys_run1416[i]->SetName(Form("Ds_Yield_sys_%s_run1416", hName_Cent[i].Data()));
		grDs_Yield_sys_forRatio_run1416[i]->SetName(Form("Ds_Yield_sys_forRatio_%s_run1416", hName_Cent[i].Data()));
		grDs_Yield_stat_run1416[i]->Write();
		grDs_Yield_sys_run1416[i]->Write();
		grDs_Yield_sys_forRatio_run1416[i]->Write();
grDs_Yield_fit_run14[i]->SetName(Form("Ds_Yield_stat_%s_run14", hName_Cent[i].Data()));
grDs_Yield_fit_run16[i]->SetName(Form("Ds_Yield_stat_%s_run16", hName_Cent[i].Data()));
grDs_Yield_SysError_run14[i]->SetName(Form("Ds_Yield_sys_%s_run14", hName_Cent[i].Data()));
grDs_Yield_SysError_run16[i]->SetName(Form("Ds_Yield_sys_%s_run16", hName_Cent[i].Data()));
grDs_Yield_fit_run14[i]->Write();
grDs_Yield_fit_run16[i]->Write();
grDs_Yield_SysError_run14[i]->Write();
grDs_Yield_SysError_run16[i]->Write();


	}
for ( int i  = 0; i<=7; i++)
        {
                if (i==0 || i==6 || i==7)//0: 0-10%; 6: 10-20%; 7: 20-40%
                {
     grDs_stat_Rcp_Base4080_run1416[i]->RemovePoint(0);
     grDs_sys_Rcp_Base4080_run1416[i]->RemovePoint(0);
     grDs_stat_Rcp_Base4080_run1416[i]->RemovePoint(4);
     grDs_sys_Rcp_Base4080_run1416[i]->RemovePoint(4);

		grDs_stat_Rcp_Base4080_run1416[i]->SetName(Form("grDs_stat_Rcp_Base4080_%s_run1416", hName_Cent[i].Data()));
		grDs_sys_Rcp_Base4080_run1416[i]->SetName(Form("grDs_sys_Rcp_Base4080_%s_run1416", hName_Cent[i].Data()));
                grDs_stat_Rcp_Base4080_run1416[i]->Write();
                grDs_sys_Rcp_Base4080_run1416[i]->Write();
}
}



}
