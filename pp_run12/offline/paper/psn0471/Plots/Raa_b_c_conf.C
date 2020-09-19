//#include <Stiostream.h>
#include <stdlib.h>
#include <math.h>
#include "TVector2.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TMath.h"
#include "TText.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TLine.h"
#include "TBox.h"

void Raa_b_c_conf() {

  gSystem->Load("libGraphic.so");
  Graphic *Gp = new Graphic();
  Gp->SetPallet(); 
  gStyle->SetOptFit(1);

        delete gRandom;
        gRandom = new TRandom3(0);

	//double r_mean = 0.5187612, r_sigma = 0.06911154;
	//double raa_mean = 0.2801, raa_sigma = 0.0364;
	//double raa_mean = 0.2801, raa_sigma = 0.2364;

        // weight average ; calculate from Cal_mean.dat
        double r_mean = 0.5325; 
        double r_sigma = 0.035; //weight ave.
        double raa_mean = 0.2801;
        double raa_sigma = 0.0364;

	double raa_c, raa_b;
	int neve = 10000000;
	int count = 0;

	TH2D *Raa = new TH2D("Raa","",100,0,1.,200,-1,1.);
        TH2D *Raa_theory = new TH2D("Raa_theory","",60,0.1,0.4,60,0.5,0.8);
	TH1D *Raa_pro = new TH1D("Raa_pro","",100,0,1);
        TH1D *rnd_ch0 = new TH1D("rnd_ch0","",100,0,1);
        TH1D *rnd_ch1 = new TH1D("rnd_ch1","",100,0,1);
        TH1D *rnd_ch2 = new TH1D("rnd_ch2","",100,-0.5,0.5);
        TH1D *rnd_ch3 = new TH1D("rnd_ch3","",100,0.0,1.0);

	for(int i=0;i<neve;i++) {

                //double r_mean_sys = gRandom->Uniform(0.478722,0.7089);
                //double r_mean_sys = gRandom->Uniform(0.491,0.7089);
                double r_mean_sys = gRandom->Uniform(0.4744,0.592);
		double rr = gRandom->Gaus(r_mean_sys,r_sigma);
		//double rr = gRandom->Gaus(r_mean_sys,0);
                rnd_ch0->Fill(r_mean_sys);
                rnd_ch1->Fill(rr);

                double sys0 = gRandom->Rndm();
                sys0 = (sys0-0.5)*2.0*0.2689;
                double raa_mean_sys = raa_mean+sys0;
		double raa= gRandom->Gaus(raa_mean_sys,raa_sigma);
                rnd_ch2->Fill(sys0);
                rnd_ch3->Fill(raa);
                if(raa<0)continue;
		raa_c = gRandom->Rndm();
		raa_b = (raa - raa_c*(1-rr))/rr;
		//if(raa_b < 0) continue;
		count++;
		Raa->Fill(raa_c,raa_b);
//		Raa_pro->Fill(raa_c,raa_b);
		if(((i+1)%10000)==0) cout<<"event = "<<i+1<<endl;
	}
 	
        TCanvas *c0 = new TCanvas();
        c0->Divide(2,2);
        c0->cd(1);
        rnd_ch0->Draw();    
        c1->cd(2);
        rnd_ch1->Draw();    
        c0->cd(3);
        rnd_ch2->Draw();    
        c1->cd(4);
        rnd_ch3->Draw();    

	TCanvas *can = new TCanvas("can","can",600,400);
	Raa->GetXaxis()->SetTitle("R_{AA}^{c}");
        Raa->GetYaxis()->SetTitle("R_{AA}^{b}");
	Raa->Sumw2();
//	Raa->Scale(1./count);
	Raa->Draw("colz");

        //TCanvas *can2 = new TCanvas("can2","can2",600,400);
        TCanvas *can2 = new TCanvas("can2","can2",400,400);
  	gPad->SetGridx(0);
  	gPad->SetGridy(0);
   	gPad->SetTickx();
   	gPad->SetTicky();
//   	gPad->SetLogy();
//   	gPad->SetLogx();
   	gPad->SetFrameBorderMode(0);
   	gPad->SetTopMargin(0.025);
   	gPad->SetLeftMargin(0.11);
   	gPad->SetRightMargin(3e-2);
   	gPad->SetBottomMargin(0.17);

  // make a histogram
  TString* histGraphName = new TString("Flow_v1");
  TH1F* histGraph = new TH1F(histGraphName->Data(), "", 5, 0.0, 1.);
  //TH1F* histGraph = new TH1F(histGraphName->Data(), "", 8, 0.0, 1.);
  delete histGraphName;
  histGraph->SetMaximum(1);//1e3);
  //histGraph->SetMinimum(-0.2);//1e-9);
  histGraph->SetMinimum(0.0);//1e-9);
  histGraph->SetLineColor(kBlack);
  histGraph->SetXTitle("R_{AA}^{c}");
  histGraph->GetXaxis()->SetLabelSize(0.07);
  histGraph->GetXaxis()->SetTitleSize(0.08);
  histGraph->GetXaxis()->SetTitleOffset(0.8);
  histGraph->SetYTitle("R_{AA}^{b}");
  histGraph->GetYaxis()->SetLabelSize(0.07);
  histGraph->GetYaxis()->SetTitleSize(0.08);
  histGraph->GetYaxis()->SetTitleOffset(0.6);
  histGraph->GetYaxis()->SetNdivisions(505);
  histGraph->Draw();

float Raa_charge = 2.281633e-01, Raa_charge_err = 1.714286e-02;
TBox *box_c = new TBox(Raa_charge-Raa_charge_err,0,Raa_charge+Raa_charge_err,1);
box_c->SetFillColor(17);
//box_c->Draw();
TBox *box_b = new TBox(0,Raa_charge-Raa_charge_err,1,Raa_charge+Raa_charge_err);
box_b->SetFillColor(17);
//box_b->Draw();

TGraphErrors *Gright = new TGraphErrors(1);
Gright->SetPoint(0,Raa_charge,Raa_charge);
Gright->SetPointError(0,Raa_charge_err,Raa_charge_err);
Gright->Draw("P");

TBox *box_point =  new TBox(Raa_charge-Raa_charge_err,Raa_charge-Raa_charge_err,Raa_charge+Raa_charge_err,Raa_charge+Raa_charge_err);
box_point->SetFillColor(1);
//box_point->SetFillStyle(0);
box_point->Draw();

TLine *line = new TLine(0,0,1,1);
line->SetLineWidth(1);
line->SetLineStyle(2);
line->Draw();
TLine *line0 = new TLine(0,0,1,0);
line0->SetLineWidth(1);
line0->Draw();

double ori_x = 380, ori_y = 548;
double gauge_x = (908 - ori_x)/8., gauge_y = (28 - ori_y)/1.;
double c_up_x[9] = {575, 610, 644, 670, 705, 735, 774, 802, 839};
double c_up_y[9] = {388, 397, 404, 409, 415, 419, 423, 426, 430};
double c_lo_x[9] = {571, 607, 641, 677, 708, 748, 771, 803, 840};
double c_lo_y[9] = {407, 410, 416, 425, 433, 431, 428, 433, 440};
double b_up_x[9] = {573, 599, 643, 674, 708, 744, 781, 811, 847};
double b_up_y[9] = {152, 166, 186, 199, 212, 225, 237, 246, 256};
double b_lo_x[9] = {582, 610, 640, 679, 711, 743, 782, 817, 847};
double b_lo_y[9] = {166, 176, 189, 215, 225, 239, 241, 257, 266};
for(int i=0;i<9;i++) {
c_up_x[i] = (c_up_x[i] - ori_x)/gauge_x + 2;
c_lo_x[i] = (c_lo_x[i] - ori_x)/gauge_x + 2;
b_up_x[i] = (b_up_x[i] - ori_x)/gauge_x + 2;
b_lo_x[i] = (b_lo_x[i] - ori_x)/gauge_x + 2;
c_up_y[i] = (c_up_y[i] - ori_y)/gauge_y;
c_lo_y[i] = (c_lo_y[i] - ori_y)/gauge_y;
b_up_y[i] = (b_up_y[i] - ori_y)/gauge_y;
b_lo_y[i] = (b_lo_y[i] - ori_y)/gauge_y;
}
TGraph * c_up_band = new TGraph(9,c_up_x,c_up_y);
TGraph * c_lo_band = new TGraph(9,c_lo_x,c_lo_y);
TGraph * b_up_band = new TGraph(9,b_up_x,b_up_y);
TGraph * b_lo_band = new TGraph(9,b_lo_x,b_lo_y);

	for(int i=0;i<10000;i++) {
		double pt = (gRandom->Rndm())*4.2+5;
		double c_up_val = c_up_band->Eval(pt);
                double c_lo_val = c_lo_band->Eval(pt);
                double b_up_val = b_up_band->Eval(pt);
                double b_lo_val = b_lo_band->Eval(pt);
		double c_raa = (gRandom->Rndm())*(c_up_val-c_lo_val) + c_lo_val;
		double b_raa = (gRandom->Rndm())*(b_up_val-b_lo_val) + b_lo_val;
		Raa_theory->Fill(c_raa,b_raa);
	}
        Raa_theory->Draw("cont,same");

	//const double sigma1 = 0.9544;//0.6827;
	//const double sigma1 = 0.6827;//0.6827;
	const double sigma1 = 0.9;//0.6827;
	double Raa_c[100],sig1_below[100],sig1_above[100];
	for(int i=0;i<100;i++) {
		Raa_c[i] = Raa->ProjectionX()->GetBinCenter(i+1);
		double Raa_b = (raa_mean - Raa_c[i]*(1-r_mean))/r_mean;
		TH1* Raa_b_hist = (TH1*)Raa->ProjectionY("",i+1,i+1);
		int peak = Raa_b_hist->FindBin(Raa_b);
		double peak_below = Raa_b_hist->Integral(0,peak);
		double peak_above = Raa_b_hist->Integral(peak,200);
//cout<<peak<<","<<peak_below<<","<<peak_above<<endl;
		for(int j=peak;j>0;j--) {
			double integral = Raa_b_hist->Integral(j-1,peak);
			integral /= peak_below;
			if(integral > sigma1) {
				sig1_below[i] = Raa_b_hist->GetBinCenter(j-1);
				break;
			}
		}
//cout<<sig1_below[i]<<",";
//cout<<endl;
		for(int j=peak;j<200;j++) {
                        double integral = Raa_b_hist->Integral(peak,j+1);
                        integral /= peak_above;
                        if(integral > sigma1) {
				sig1_above[i] = Raa_b_hist->GetBinCenter(j+1);
                        	break;
			}
                }
		Raa_pro->SetBinContent(i+1,Raa_b);
                Raa_pro->SetBinError(i+1,0);
	}	
	Raa_pro->SetLineWidth(2);
        Raa_pro->SetLineColor(2);
	Raa_pro->Draw("same,c");

	int N_sig1_below=100,N_sig1_above=100;
//	for(int i=0;i<100;i++) { if(sig1_below[i] < 0) {N_sig1_below = i;break;}}
//        for(int i=0;i<100;i++) { if(sig1_above[i] < 0) {N_sig1_above = i;break;}}
	cout<<N_sig1_below<<","<<N_sig1_above<<endl;
	TGraph *contour_sig1_below = new TGraph(N_sig1_below,Raa_c,sig1_below);
        contour_sig1_below->SetLineStyle(2);
        //contour_sig1_below->SetLineStyle(3);
        contour_sig1_below->SetLineWidth(2);
        contour_sig1_below->SetLineColor(4);
	contour_sig1_below->Draw("c");
        TGraph *contour_sig1_above = new TGraph(N_sig1_above,Raa_c,sig1_above);
        //contour_sig1_above->SetLineStyle(3);
        contour_sig1_above->SetLineStyle(2);
        contour_sig1_above->SetLineWidth(2);
        contour_sig1_above->SetLineColor(4);
        contour_sig1_above->Draw("c");

        //TFile *fileout = new TFile("RAA_cont.root","recreate");
        //TFile *fileout = new TFile("tmp.root","recreate");
        TFile *fileout = new TFile("RAA_cont_sig2.root","recreate");
	Raa->Write("Raa");
        histGraph->Write("histGraph");
        box_c->Write("box_c");
        box_b->Write("box_b");
        line->Write("line");
        line0->Write("line0");
        Raa_theory->Write("Raa_theory");
	Raa_pro->Write("Raa_pro");
	contour_sig1_below->Write("contour_sig1_below");
        contour_sig1_above->Write("contour_sig1_above");
        Gright->Write("light_point");
        box_point->Write("light_box");

}
