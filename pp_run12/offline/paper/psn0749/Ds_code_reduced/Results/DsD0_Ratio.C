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

void DsD0_Ratio()
{
//	gROOT->Reset();

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
			double len = length;
			//      cout<< " y = " << y<<  endl;
			//            cout << " ey_l = " << ey_l << "ey_h =  " << ey_h << endl; 
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

	double ErrorAdd(double x, double y)
	{
		return sqrt(x*x + y*y);
	}
	double ErrorDiv(double x, double y, double dx, double dy)
	{
		return x/y*ErrorAdd(dx/x, dy/y);
	}


	const Int_t NC = 8;
	const Int_t NC_Ratio = 8;
	const Int_t NPt = 5;
	double pT_D0[NC][NPt], y_D0[NC][NPt], ye_D0[NC][NPt], yes_D0[NC][NPt];
	double y_dNdy_D0[NC], ye_dNdy_D0[NC], yes_dNdy_D0[NC];
	double y_dNdy_Ds[NC], ye_dNdy_Ds[NC], yes_dNdy_Ds[NC];
	double pT_Ds[NC][NPt], y_Ds[NC][NPt], ye_Ds[NC][NPt], yes_Ds[NC][NPt];
	double y_Ratio[NC][NPt], ye_Ratio[NC][NPt], yes_Ratio[NC][NPt];
	double y_dNdy_Ratio[NC_Ratio], ye_dNdy_Ratio[NC_Ratio], yes_dNdy_Ratio[NC_Ratio];
	double dpT_dNdy[3] = {1, 1, 1.5};

	TGraphErrors *grDs_Yield_stat_run1416[NC];
	TGraphErrors *grDs_Yield_sys_forRatio_run1416[NC];
	TGraphErrors *grD0_Yield_stat_run14[NC];
	TGraphErrors *grD0_Yield_sys_run14[NC];
	TGraphErrors *grDsD0_err_Ratio[8];
	TGraphErrors *grDsD0_sys_Ratio[8];
	TGraphErrors *grDsD0_err_dNdy_Ratio;
	TGraphErrors *grDsD0_sys_dNdy_Ratio;

	TString mCent[8] = {"0_10", "10_40_binning", "40_80", "40_60", "60_80", "10_40", "10_20", "20_40"};

	TFile *fDsYield = new TFile("root/Spectrum_run1416_Ds.root");
	TFile *fD0Yield = new TFile("root/D0_Spectra_Run14_HFT_PtShift_forChuanOnlyRawYieldTopoSys.root");
	TFile *fout = new TFile("root/DsD0_Ratio.root","recreate");

	for(int i=0;i<NC;i++) {
		grDs_Yield_stat_run1416[i] = (TGraphErrors *)fDsYield->Get(Form("Ds_Yield_stat_%s_run1416", mCent[i].Data()));
		grDs_Yield_sys_forRatio_run1416[i] = (TGraphErrors *)fDsYield->Get(Form("Ds_Yield_sys_forRatio_%s_run1416", mCent[i].Data()));
		grD0_Yield_stat_run14[i] = (TGraphErrors *)fD0Yield->Get(Form("gD0_err_%s", mCent[i].Data()));
		grD0_Yield_sys_run14[i] = (TGraphErrors *)fD0Yield->Get(Form("gD0_sys_%s", mCent[i].Data()));
		//grD0_Yield_stat_run14[i]->Print();
//		cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
		for(int j=0;j<NPt;j++) {
			pT_Ds[i][j] = grDs_Yield_stat_run1416[i]->GetX()[j];
			y_Ds[i][j] = grDs_Yield_stat_run1416[i]->GetY()[j];
			ye_Ds[i][j] = grDs_Yield_stat_run1416[i]->GetEY()[j];
			yes_Ds[i][j] = grDs_Yield_sys_forRatio_run1416[i]->GetEY()[j];
    
			pT_D0[i][j] = grD0_Yield_stat_run14[i]->GetX()[j];
			y_D0[i][j] = grD0_Yield_stat_run14[i]->GetY()[j];
			ye_D0[i][j] = grD0_Yield_stat_run14[i]->GetEY()[j];
			yes_D0[i][j] = grD0_Yield_sys_run14[i]->GetEY()[j];

			y_Ratio[i][j] = y_Ds[i][j]/y_D0[i][j];
			ye_Ratio[i][j] = ErrorDiv(y_Ds[i][j], y_D0[i][j], ye_Ds[i][j], ye_D0[i][j]);
			yes_Ratio[i][j] = ErrorDiv(y_Ds[i][j], y_D0[i][j], yes_Ds[i][j], yes_D0[i][j]);
			//			cout << "pT_Ds =" << pT_Ds[i][j]  << endl;
			//	cout << "y_D0 =" << y_D0[i][j]  << endl;
			//	cout << "y_Ds =" << y_Ds[i][j]  << endl;
			//	cout << "ye_Ds[i][j] = " << ye_Ds[i][j]<< endl;
			//	cout << "ye_D0[i][j] = " << ye_D0[i][j]<< endl;
			//cout << "yes_Ds[i][j] = " << yes_Ds[i][j]<< endl;
			//	cout << "yes_D0[i][j] = " << yes_D0[i][j]<< endl;
			//	cout << "y_Ratio =" << y_Ratio[i][j]  << endl;
			//	cout << "ye_Ratio =" << ye_Ratio[i][j]  << endl;
			//	cout << "yes_Ratio =" << yes_Ratio[i][j]  << endl;
			//		cout << "!------------------------------!" << endl;
double sys_Ds_Forratio = yes_Ds[i][j]/y_Ds[i][j];
double sys_D0_Forratio = yes_D0[i][j]/y_D0[i][j];
double sys_ratio = yes_Ratio[i][j]/y_Ratio[i][j];
if (i==1)
{

// cout <<" sys_Ds_Forratio= "<< sys_Ds_Forratio << endl;
// cout <<" sys_D0_Forratio= "<< sys_D0_Forratio << endl;
// cout << "sys_ratio = " << sys_ratio << endl;
}
		}
	}

	for(int i=0;i<NC;i++) 
	{
		if (i==0 || i==6 || i==7) 
		{
			for(int j=0;j<3;j++)// 1.5-5 GeV/c; 
			{
				y_dNdy_D0[i] += 2*TMath::Pi()*y_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j];
				ye_dNdy_D0[i] += pow(2*TMath::Pi()*ye_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j], 2);
				yes_dNdy_D0[i] += pow(2*TMath::Pi()*yes_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j], 2);
				y_dNdy_Ds[i] += 2*TMath::Pi()*y_Ds[i][j]*pT_Ds[i][j]*dpT_dNdy[j];
				ye_dNdy_Ds[i] += pow(2*TMath::Pi()*ye_Ds[i][j]*pT_Ds[i][j]*dpT_dNdy[j], 2);
				yes_dNdy_Ds[i] += pow(2*TMath::Pi()*yes_Ds[i][j]*pT_Ds[i][j]*dpT_dNdy[j], 2);			
			}

		}
		else if (i==3 || i==4)
		{
			for(int j=0;j<3;j++)
			{
				y_dNdy_D0[i] += 2*TMath::Pi()*y_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j];
				ye_dNdy_D0[i] += pow(2*TMath::Pi()*ye_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j], 2);
				yes_dNdy_D0[i] += pow(2*TMath::Pi()*yes_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j], 2);
				//		cout << "y_D0[i][j] =" << y_D0[i][j] << endl;
				//		cout << "ye_D0[i][j] =" << ye_D0[i][j] << endl;

			}
			for(int j=0;j<1;j++)
			{
				y_dNdy_Ds[i] += 2*TMath::Pi()*y_Ds[i][j]*pT_Ds[i][j]*3.5;
				ye_dNdy_Ds[i] += pow(2*TMath::Pi()*ye_Ds[i][j]*pT_Ds[i][j]*3.5, 2);
				yes_dNdy_Ds[i] += pow(2*TMath::Pi()*yes_Ds[i][j]*pT_Ds[i][j]*3.5, 2);			
				//				cout << "y_Ds[i][j] =" << y_Ds[i][j] << endl;
				//					cout << "ye_Ds[i][j] =" << ye_Ds[i][j] << endl;
				//					cout << "yes_Ds[i][j] =" << yes_Ds[i][j] << endl;

			}


		}
		ye_dNdy_D0[i] = sqrt(ye_dNdy_D0[i]);
		ye_dNdy_Ds[i] = sqrt(ye_dNdy_Ds[i]);
		yes_dNdy_D0[i] = sqrt(yes_dNdy_D0[i]);
		yes_dNdy_Ds[i] = sqrt(yes_dNdy_Ds[i]);
		cout << "i = " << i << endl;
		//cout << "y_dNdy_D0[i] = " << y_dNdy_D0[i] << endl;
		//	  cout << "y_dNdy_Ds[i] = " << y_dNdy_Ds[i] << endl;
		//	  cout << "ye_dNdy_D0[i] = " << ye_dNdy_D0[i] << endl;
		//	  cout << "ye_dNdy_Ds[i] = " << ye_dNdy_Ds[i] << endl;
	//	cout << "yes_dNdy_D0[i] = " << yes_dNdy_D0[i] << endl;
	//	cout << "yes_dNdy_Ds[i] = " << yes_dNdy_Ds[i] << endl;

	}
	/*		if (i==1 ) //Ds 10-40%
			{
			for(int j=0;j<NPt;j++) {
			if (j >= 3 && j <= 4)
			{
			y_dNdy_Ds[i] += 2*TMath::Pi()*y_Ds[i][j]*pT_Ds[i][j]*dpT_dNdy[j-2];
			ye_dNdy_Ds[i] += pow(2*TMath::Pi()*ye_Ds[i][j]*pT_Ds[i][j]*dpT_dNdy[j-2], 2);
			yes_dNdy_Ds[i] += pow(2*TMath::Pi()*yes_Ds[i][j]*pT_Ds[i][j]*dpT_dNdy[j-2], 2);
	//	cout << "y_Ds[i][j] =" << y_Ds[i][j] << endl;
	}
	}
	y_dNdy_Ds[i] += 2*TMath::Pi()*y_Ds[5][0]*pT_Ds[5][0]*1;
	ye_dNdy_Ds[i] += pow(2*TMath::Pi()*ye_Ds[5][0]*pT_Ds[5][0]*1, 2);
	yes_dNdy_Ds[i] += pow(2*TMath::Pi()*yes_Ds[5][0]*pT_Ds[5][0]*1, 2);
	ye_dNdy_Ds[i] = sqrt(ye_dNdy_Ds[i]);
	yes_dNdy_Ds[i] = sqrt(yes_dNdy_Ds[i]);
	//	cout << "y_Ds[i][j] =" << y_Ds[5][0] << endl;
	//cout << "y_dNdy_Ds[i] = " << y_dNdy_Ds[i] << endl;
	cout << "y_dNdy_Ds[i] = " << y_dNdy_Ds[i] << endl;
	cout << "ye_dNdy_Ds[i] = " << ye_dNdy_Ds[i] << endl;
	cout << "yes_dNdy_Ds[i] = " << yes_dNdy_Ds[i] << endl;
	}

	if (i==3 || i ==4) //40-60%, 60-80%
	{
	for(int j=0;j<NPt;j++) {
	if (j >= 1 && j <= 3)
	{
	y_dNdy_D0[i] += 2*TMath::Pi()*y_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j-1];
	ye_dNdy_D0[i] += pow(2*TMath::Pi()*ye_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j-1], 2);
	yes_dNdy_D0[i] += pow(2*TMath::Pi()*yes_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j-1], 2);
	//	cout << "y_D0[i][j] =" << y_D0[i][j] << endl;
	}
	}
	y_dNdy_Ds[i] = 2*TMath::Pi()*y_Ds[i][0]*pT_Ds[i][0]*3.5;
	ye_dNdy_Ds[i] = 2*TMath::Pi()*ye_Ds[i][0]*pT_Ds[i][0]*3.5;
	yes_dNdy_Ds[i] = 2*TMath::Pi()*yes_Ds[i][0]*pT_Ds[i][0]*3.5;
	ye_dNdy_D0[i] = sqrt(ye_dNdy_D0[i]);
	yes_dNdy_D0[i] = sqrt(yes_dNdy_D0[i]);

	//	cout << "y_dNdy_D0[i] = " << y_dNdy_D0[i] << endl;
	//	cout << "y_dNdy_Ds[i] = " << y_dNdy_Ds[i] << endl;
	cout << "y_dNdy_D0[i] = " << y_dNdy_D0[i] << endl;
	cout << "y_dNdy_Ds[i] = " << y_dNdy_Ds[i] << endl;
	cout << "ye_dNdy_D0[i] = " << ye_dNdy_D0[i] << endl;
	cout << "ye_dNdy_Ds[i] = " << ye_dNdy_Ds[i] << endl;
	cout << "yes_dNdy_D0[i] = " << yes_dNdy_D0[i] << endl;
	cout << "yes_dNdy_Ds[i] = " << yes_dNdy_Ds[i] << endl;
	}
	if (i==5) //D0, 10-40%
	{
	for(int j=0;j<NPt;j++) {
	if (j >= 1 && j <= 3)
	{
	y_dNdy_D0[i] += 2*TMath::Pi()*y_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j-1];
	ye_dNdy_D0[i] += pow(2*TMath::Pi()*ye_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j-1], 2);
	yes_dNdy_D0[i] += pow(2*TMath::Pi()*yes_D0[i][j]*pT_D0[i][j]*dpT_dNdy[j-1], 2);
	//	cout << "y_D0[i][j] =" << y_D0[i][j] << endl;
	}
	}
	cout << "&&&&&&&&&&&&&&&&&&&&&&"<< endl;
	ye_dNdy_D0[i] = sqrt(ye_dNdy_D0[i]);
	yes_dNdy_D0[i] = sqrt(yes_dNdy_D0[i]);
	//cout << "y_dNdy_D0[i] = " << y_dNdy_D0[i] << endl;
	cout << "y_dNdy_D0[i] = " << y_dNdy_D0[i] << endl;
	cout << "ye_dNdy_D0[i] = " << ye_dNdy_D0[i] << endl;
	cout << "yes_dNdy_D0[i] = " << yes_dNdy_D0[i] << endl;
	}
	}
	 */
//double x_dNdy_Ratio[8] = {324, 62, 21, 235, 141};//0-10%, 40-60%, 60-80%, 10-20%, 20-40% 
double x_dNdy_Ratio[8] = {324, 30, 40,  62, 21, 200, 235, 141};//0-10%, 40-60%, 60-80%, 10-20%, 20-40%
for(int i=0;i<NC;i++)
{
	if (i==0 || i==3 || i==4 || i==6 || i==7)
	{
		y_dNdy_Ratio[i] = y_dNdy_Ds[i]/y_dNdy_D0[i];
		ye_dNdy_Ratio[i] = ErrorDiv(y_dNdy_Ds[i], y_dNdy_D0[i], ye_dNdy_Ds[i], ye_dNdy_D0[i]);
		yes_dNdy_Ratio[i] = ErrorDiv(y_dNdy_Ds[i], y_dNdy_D0[i], yes_dNdy_Ds[i], yes_dNdy_D0[i]);
	}
//	cout << "y_dNdy_Ratio[i] = "<< y_dNdy_Ratio[i]  << endl;
//	cout << "ye_dNdy_Ratio[i] = "<< ye_dNdy_Ratio[i]  << endl;
//	cout << "yes_dNdy_Ratio[i] = "<< yes_dNdy_Ratio[i]  << endl;
}
grDsD0_err_dNdy_Ratio = new TGraphErrors(NC_Ratio, x_dNdy_Ratio, y_dNdy_Ratio, 0, ye_dNdy_Ratio); 
grDsD0_sys_dNdy_Ratio = new TGraphErrors(NC_Ratio, x_dNdy_Ratio, y_dNdy_Ratio, 0, yes_dNdy_Ratio);
grDsD0_err_dNdy_Ratio->RemovePoint(1); 
grDsD0_sys_dNdy_Ratio->RemovePoint(1); 
grDsD0_err_dNdy_Ratio->RemovePoint(1); 
grDsD0_sys_dNdy_Ratio->RemovePoint(1); 
grDsD0_err_dNdy_Ratio->RemovePoint(3); 
grDsD0_sys_dNdy_Ratio->RemovePoint(3);
grDsD0_sys_dNdy_Ratio->Print();

grDsD0_err_Ratio[0] = new TGraphErrors(4, pT_Ds[0], y_Ratio[0], 0, ye_Ratio[0]); 
grDsD0_sys_Ratio[0] = new TGraphErrors(4, pT_Ds[0], y_Ratio[0], 0, yes_Ratio[0]); 
grDsD0_err_Ratio[1] = new TGraphErrors(5, pT_Ds[1], y_Ratio[1], 0, ye_Ratio[1]); 
grDsD0_sys_Ratio[1] = new TGraphErrors(5, pT_Ds[1], y_Ratio[1], 0, yes_Ratio[1]); 
grDsD0_err_Ratio[2] = new TGraphErrors(4, pT_Ds[2], y_Ratio[2], 0, ye_Ratio[2]); 
grDsD0_sys_Ratio[2] = new TGraphErrors(4, pT_Ds[2], y_Ratio[2], 0, yes_Ratio[2]); 
shiftTGraph(grDsD0_err_Ratio[1], 0.12*1);
shiftTGraph(grDsD0_sys_Ratio[1], 0.12*1);
shiftTGraph(grDsD0_err_Ratio[2], 0.12*2);
shiftTGraph(grDsD0_sys_Ratio[2], 0.12*2);

//shiftTGraph(grDsD0_err_Ratio[6], 0.12*1);
//shiftTGraph(grDsD0_sys_Ratio[6], 0.12*1);
//shiftTGraph(grDsD0_err_Ratio[7], 0.12*2);
//shiftTGraph(grDsD0_sys_Ratio[7], 0.12*2);

c5=new TCanvas ("c5","c5",800,600);
c5->cd();
TPad *p5=new TPad("p5","p5",0.,0,1.,1.);
p5->SetFillColor(10);
p5->SetTopMargin(0.1);
p5->SetBottomMargin(0.15);
p5->SetLeftMargin(0.2);
p5->SetRightMargin(0.1);
p5->SetGrid(0,0);
//       p5->SetLogy();
p5->SetTicks(1,1);
p5->SetBorderMode(0);
p5->SetFrameFillColor(0);
p5->SetFrameLineWidth(1);
p5->Draw();
p5->cd();
TH2F *h1_5 = new TH2F("h1_5","",20,1,8,20,0,0.8);
h1_5->SetStats(0);
//        h1_5->SetTitle(Name_Cent[2].Data());
h1_5->GetYaxis()->SetTitle("D_{s}/D^{0}");
h1_5->GetYaxis()->CenterTitle(1);
h1_5->GetYaxis()->SetTitleSize(0.05);
h1_5->GetYaxis()->SetTitleOffset(1);
h1_5->GetYaxis()->SetLabelSize(0.04);
h1_5->GetYaxis()->SetLabelOffset(0.011);
h1_5->GetYaxis()->SetLabelFont(42);
h1_5->GetYaxis()->SetTitleFont(42);
h1_5->GetYaxis()->SetTickLength(0.02);

h1_5->GetXaxis()->SetLabelFont(42);
h1_5->GetXaxis()->SetTitleFont(42);
h1_5->GetXaxis()->SetTitle("p_{T} GeV/c");
h1_5->GetXaxis()->CenterTitle(1);
h1_5->GetXaxis()->SetTitleSize(0.05);
h1_5->GetXaxis()->SetTitleOffset(1.2);
h1_5->GetXaxis()->SetLabelSize(0.05);
h1_5->GetXaxis()->SetLabelOffset(0.02);
h1_5->GetXaxis()->SetTickLength(0.02);
h1_5->Draw();

grDsD0_err_Ratio[0]->SetMarkerColor(4);
grDsD0_err_Ratio[0]->SetMarkerStyle(20);
grDsD0_err_Ratio[0]->SetLineColor(4);
grDsD0_err_Ratio[0]->SetMarkerSize(2);
grDsD0_err_Ratio[0]->Draw("PE");
grDsD0_sys_Ratio[0]->SetMarkerColor(4);
grDsD0_sys_Ratio[0]->SetLineColor(4);
drawSysError(grDsD0_sys_Ratio[0],0.1,0.01);

/*        grDsD0_err_Ratio[1]->SetMarkerColor(2);
	  grDsD0_err_Ratio[1]->SetMarkerStyle(20);
	  grDsD0_err_Ratio[1]->SetLineColor(2);
	  grDsD0_err_Ratio[1]->SetMarkerSize(2);
	  grDsD0_err_Ratio[1]->Draw("PE");
	  grDsD0_sys_Ratio[1]->SetMarkerColor(2);
	  grDsD0_sys_Ratio[1]->SetLineColor(2);
	  drawSysError(grDsD0_sys_Ratio[1],0.1,0.01);

	  grDsD0_err_Ratio[2]->SetMarkerColor(8);
	  grDsD0_err_Ratio[2]->SetMarkerStyle(20);
	  grDsD0_err_Ratio[2]->SetLineColor(8);
	  grDsD0_err_Ratio[2]->SetMarkerSize(2);
	  grDsD0_err_Ratio[2]->Draw("PE");
	  grDsD0_sys_Ratio[2]->SetMarkerColor(8);
	  grDsD0_sys_Ratio[2]->SetLineColor(8);
	  drawSysError(grDsD0_sys_Ratio[2],0.1,0.01);
 */
grDsD0_err_Ratio[1]->SetMarkerColor(2);
grDsD0_err_Ratio[1]->SetMarkerStyle(20);
grDsD0_err_Ratio[1]->SetLineColor(2);
grDsD0_err_Ratio[1]->SetMarkerSize(2);
grDsD0_err_Ratio[1]->Draw("PE");
grDsD0_sys_Ratio[1]->SetMarkerColor(2);
grDsD0_sys_Ratio[1]->SetLineColor(2);
drawSysError(grDsD0_sys_Ratio[1],0.1,0.01);

grDsD0_err_Ratio[2]->SetMarkerColor(8);
grDsD0_err_Ratio[2]->SetMarkerStyle(20);
grDsD0_err_Ratio[2]->SetLineColor(8);
grDsD0_err_Ratio[2]->SetMarkerSize(2);
grDsD0_err_Ratio[2]->Draw("PE");
grDsD0_sys_Ratio[2]->SetMarkerColor(8);
grDsD0_sys_Ratio[2]->SetLineColor(8);
drawSysError(grDsD0_sys_Ratio[2],0.1,0.01);

plotTopCent("Combined Run14+Run16",0.5,0.75,0.05,1,0.0,22,1);
TLegend *leg = new TLegend(0.25,0.7,0.45,0.85);
leg->AddEntry(grDsD0_err_Ratio[0],"0-10%", "p");
leg->AddEntry(grDsD0_err_Ratio[1],"10-40%", "p");
leg->AddEntry(grDsD0_err_Ratio[2],"40-80%", "p");
leg->SetTextSize(0.06);
leg->SetFillColor(0);
leg->SetLineColor(0);
leg->Draw();

c4=new TCanvas ("c4","c4",800,600);
c4->cd();
TPad *p4=new TPad("p4","p4",0.,0,1.,1.);
p4->SetFillColor(10);
p4->SetTopMargin(0.1);
p4->SetBottomMargin(0.15);
p4->SetLeftMargin(0.2);
p4->SetRightMargin(0.1);
p4->SetGrid(0,0);
//      p4->SetLogy();
p4->SetTicks(1,1);
p4->SetBorderMode(0);
p4->SetFrameFillColor(0);
p4->SetFrameLineWidth(1);
p4->Draw();
p4->cd();
TH2F *h1_4 = new TH2F("h1_4","",20,0,400,20,0,1);
h1_4->SetStats(0);
//h1_4->SetTitle(Name_Cent[0].Data());
h1_4->GetYaxis()->SetTitle("D_{s}/D^{0} (dN/dy)");
h1_4->GetYaxis()->CenterTitle(1);
h1_4->GetYaxis()->SetNdivisions(505);
h1_4->GetYaxis()->SetTitleSize(0.05);
h1_4->GetYaxis()->SetTitleOffset(1);
h1_4->GetYaxis()->SetLabelSize(0.04);
h1_4->GetYaxis()->SetLabelOffset(0.011);
h1_4->GetYaxis()->SetLabelFont(42);
h1_4->GetYaxis()->SetTitleFont(42);
h1_4->GetYaxis()->SetTickLength(0.02);

h1_4->GetXaxis()->SetLabelFont(42);
h1_4->GetXaxis()->SetTitleFont(42);
h1_4->GetXaxis()->SetTitle("Npart");
h1_4->GetXaxis()->CenterTitle(1);
h1_4->GetXaxis()->SetTitleSize(0.05);
h1_4->GetXaxis()->SetTitleOffset(1.2);
h1_4->GetXaxis()->SetLabelSize(0.05);
h1_4->GetXaxis()->SetLabelOffset(0.02);
h1_4->GetXaxis()->SetTickLength(0.02);
h1_4->Draw();

grDsD0_err_dNdy_Ratio->SetMarkerColor(4);
grDsD0_err_dNdy_Ratio->SetMarkerStyle(20);
grDsD0_err_dNdy_Ratio->SetLineColor(4);
grDsD0_err_dNdy_Ratio->SetMarkerSize(1.5);
grDsD0_sys_dNdy_Ratio->SetMarkerColor(4);
grDsD0_sys_dNdy_Ratio->SetLineColor(4);
grDsD0_err_dNdy_Ratio->Draw("pe");
drawSysError(grDsD0_sys_dNdy_Ratio, 5,0.01);
TLegend *leg = new TLegend(0.25,0.7,0.4,0.85);
leg->AddEntry(grDsD0_err_dNdy_Ratio, "From Bin counting, D_{s}", "p");
leg->SetTextSize(0.05);
leg->SetFillColor(0);
leg->SetLineColor(0);
leg->Draw();

fout->cd();
grDsD0_err_dNdy_Ratio->SetName("DsD0_err_dNdy_Ratio");
grDsD0_sys_dNdy_Ratio->SetName("DsD0_sys_dNdy_Ratio");
grDsD0_err_dNdy_Ratio->Write();
grDsD0_sys_dNdy_Ratio->Write();
for (int i = 0; i <= 2; i++)
{
	grDsD0_err_Ratio[i]->SetName(Form("DsD0_err_%s_Ratio", mCent[i].Data()));
	grDsD0_sys_Ratio[i]->SetName(Form("DsD0_sys_%s_Ratio", mCent[i].Data()));
	grDsD0_err_Ratio[i]->Write();
	grDsD0_sys_Ratio[i]->Write();

}

}











