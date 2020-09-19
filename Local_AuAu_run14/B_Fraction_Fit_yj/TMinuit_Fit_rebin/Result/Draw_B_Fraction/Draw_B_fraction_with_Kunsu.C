#include <iostream>
#include<iomanip>
#include <fstream>
#include "TLatex.h"
#include "TStyle.h"
#include "TH3F.h"
#include "TF1.h"
#include "TMath.h"
#include "TLine.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TRandom3.h"
#include "TGraphErrors.h"

// #include "/Users/xiaozhi/NPE_work/NPE_low_pt/Binning/Bin.h"
// #include "/Users/xiaozhi/NPE_work/NPE_low_pt/NPE_Spectra/RAA/for_xiaozhi/Binning.h"
using namespace std;
const Double_t PI=TMath::Pi();
Int_t gColor08=1;
Int_t gColor08_fill=1;
Int_t gMStyle08=20;


Int_t gColor12HT=2;
Int_t gColor12HT_fill=42;
Int_t gMStyle12HT=20;

Int_t gColor12MB=2;
Int_t gColor12MB_fill=42;
Int_t gMStyle12MB=24;


Int_t lWidth=3;
Int_t lStyle=2;
Int_t lStyle_c=1;
Int_t lColor=4;

TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
char buf[1024];
void Draw_B_fraction_with_Kunsu()

{
  
  char buf[1024];
  TH1::SetDefaultSumw2();
  gStyle->SetTitleSize(0.06,"XY");
  gStyle->SetTitleFontSize(0.1);
  gStyle->SetTitleOffset(1.,"X");
  gStyle->SetTitleOffset(1.,"Y");

  gStyle->SetPadTopMargin(0.02);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetEndErrorSize(8);
  gStyle->SetOptStat(000);
  

  TFile *input_run14_sts=new TFile("InPut/Fit_B_fraction_MB_default.root","READ");
  TFile *input_run14_sys=new TFile("InPut/B_fraction_sys.root","READ");

  TFile *input_run12_pp=new TFile("InPut/run12NPEh_rBPoints.root","READ");

  
  TH1F *B_fraction_MB=(TH1F *) input_run14_sts->Get("b_fraction_MB")->Clone("B_fraction_MB");
  TH1F *B_fraction_sys=(TH1F *) input_run14_sys->Get("b_Fraction_sys")->Clone("B_fraction_sys");
  
  TGraphErrors *  gr_B_fraction_MB=new TGraphErrors(B_fraction_MB);
  TGraphErrors *  gr_B_fraction_sys=new TGraphErrors(B_fraction_sys);

  TFile *input_PHENIX=new TFile("InPut/PHENIX.root","READ");
  TGraphAsymmErrors *gr_B_fraction_PHENIX=(TGraphAsymmErrors *) input_PHENIX->Get("Graph"); 



    cout<< gr_B_fraction_MB->GetN()<<endl;
    //    cout<< gr_B_fraction_HT->GetN()<<endl;

    for(Int_t ipoint=0;ipoint<gr_B_fraction_MB->GetN();ipoint++)
      {
	gr_B_fraction_MB->SetPointError(ipoint,gr_B_fraction_MB->GetErrorX(ipoint), gr_B_fraction_MB->GetErrorY(ipoint));
	gr_B_fraction_sys->SetPointError(ipoint,0.1, gr_B_fraction_sys->GetErrorY(ipoint));
	
      }


    gr_B_fraction_MB->SetMarkerStyle(20);
    //   gr_B_fraction_sys->SetMarkerStyle(21);

    gr_B_fraction_MB->SetMarkerColor(4);
    //   gr_B_fraction_sys->SetMarkerColor(4);

    gr_B_fraction_MB->SetMarkerSize(2.2);
    //   gr_B_fraction_sys->SetMarkerSize();
    
    gr_B_fraction_MB->SetLineColor(4);
    //   gr_B_fraction_sys->SetLineColor(2);

    gr_B_fraction_MB->SetLineWidth(2);

    gr_B_fraction_sys->SetFillStyle(1001);
    gr_B_fraction_sys->SetFillColor(40);
    gr_B_fraction_sys->SetLineColor(40);
    gr_B_fraction_sys->SetLineWidth(2);

    // run12

    
    TGraphAsymmErrors *run12_pp_sts=  (TGraphAsymmErrors *) input_run12_pp->Get("StatError_Run6");
    TGraphAsymmErrors *run12_pp_sys=  (TGraphAsymmErrors *) input_run12_pp->Get("systError_Run6");    

    for(Int_t ipoint=0;ipoint<run12_pp_sys->GetN();ipoint++)
      {
	run12_pp_sys->SetPointError(ipoint,0.1,0.1, run12_pp_sys->GetErrorY(ipoint),run12_pp_sys->GetErrorY(ipoint));


	//run12_pp_sys->SetPointError(ipoint,0, 0);
	 run12_pp_sys->SetPoint(ipoint,-999, -999);

      }

    run12_pp_sts->SetLineColor(1);
    run12_pp_sts->SetMarkerColor(1);
    run12_pp_sts->SetMarkerStyle(20);

    run12_pp_sys->SetLineColor(1);
    run12_pp_sys->SetMarkerColor(1);

   
    run12_pp_sts->SetMarkerSize(2.2);


    // FONLL
    TGraph *FONLL[2];
    FONLL[0] = new TGraph("InPut/FONLL_BAND_UP.dat");
    FONLL[1] = new TGraph("InPut/FONLL_BAND_DW.dat");
    FONLL[0]->SetLineStyle(2);
    FONLL[1]->SetLineStyle(2);

    // e_D0
// Graphic *Gp = new Graphic();
//  Gp->SetPallet();
  
    TGraphErrors *Ge_D0 = new TGraphErrors("InPut/e_D0.dat");
    TGraphAsymmErrors *Ge_D0_sys = new TGraphAsymmErrors(1);
    Ge_D0_sys->SetPoint(0,5.55,0.439); 
    double sysdw_eD0 = 0.1481;
    double sysup_eD0 = 0.1725;

    // cout << sysdw_eD0 << " : " << sysup_eD0 << endl;
  
    Ge_D0_sys->SetPointError(0,0.1,0.1,sysdw_eD0,sysup_eD0); // data get from Andre (10/02/08) 
    Ge_D0_sys->SetFillStyle(0);
    Ge_D0->SetMarkerStyle(22);
    Ge_D0->SetMarkerColor(1);
    Ge_D0->SetMarkerSize(2.2);

    Ge_D0->SetLineColor(1);
    Ge_D0_sys->SetLineColor(1);

    Ge_D0->SetLineWidth(2);
    Ge_D0_sys->SetLineWidth(2);
    
  //   TGraphAsymmErrorsBracket *Ge_D0_sys = new TGraphAsymmErrorsBracket(*Ge_D0_tmp);
  // Ge_D0_sys->SetBracketSize(5, 5);
  // Ge_D0_sys->SetBracketColor(1);


    //   Gp->SetGraphStyles(Ge_D0,21,1);

  // Ge_D0->Draw("P");
  //Ge_D_1->Draw("P");



    // from Kunsu
    TFile *file_kunsu=new TFile("btoe_2000_kunsu.root","READ");
    TGraphAsymmErrors* btoe=(TGraphAsymmErrors *) file_kunsu->Get("btoe");
    TGraphAsymmErrors* btoeSys=(TGraphAsymmErrors *) file_kunsu->Get("btoeSys");

    for(Int_t i=0;i<8;i++)
      {
	Double_t bX=-99;Double_t bY=-99;
	btoe->GetPoint(i,bX,bY);
	btoe->SetPoint(i,bX+0.2,bY);

	btoeSys->GetPoint(i,bX,bY);
	btoeSys->SetPoint(i,bX+0.2,bY);
	btoeSys->SetPoint(i,bX+0.2,bY);

	
      }

    btoe->SetMarkerSize(2.);
    TCanvas *c6=new TCanvas("c6","",1400,950);
    TH2F *h6=new TH2F("h6","",100,0.2,8.5,100,0,1.2);
    h6->Draw();
    h6->GetXaxis()->SetTitle("p_{T}^{e} (GeV/c)");
    h6->GetYaxis()->SetTitle("B#rightarrow NPE / inclusive#rightarrow NPE");
    //      h6->GetXaxis()->SetTitleSize(0.04);
    h6->GetXaxis()->SetLabelSize(0.05);
    h6->GetYaxis()->SetLabelSize(0.05);
    // h6->GetYaxis()->SetTitleOffset(1);
    // h6->GetXaxis()->SetTitleOffset(1);
    
    h6->GetXaxis()->CenterTitle(true);
    h6->GetYaxis()->CenterTitle(true);
    h6->Draw();

    // Draw PHENIX

    btoe->Draw("samePE");
    btoeSys->Draw("p[],same");
    
    // gr_B_fraction_PHENIX->SetLineWidth(4);
    // gr_B_fraction_PHENIX->Draw("3Lsame");
    // run12_pp_sts->Draw("samePE");
    // run12_pp_sys->Draw("same e2");
    //Ge_D0->SetName("eD0");
    // Ge_D0->Draw("sameP");
    // Ge_D0_sys->Draw("same e2");

    gr_B_fraction_sys->Draw("sameE2");
    gr_B_fraction_MB->Draw("samePE");
    //  gr_B_fraction_sys-> Draw("p:[]same");
    // FONLL[0]->Draw("same");
    // FONLL[1]->Draw("same");
    
    sprintf(buf,"Au+Au@#sqrt{s_{NN}}=200 GeV");
    drawLatex(0.2,0.92,buf,62,0.04,4);

    TLegend *legend  = new TLegend(0.2,0.65,0.4,0.9);
    legend ->AddEntry(gr_B_fraction_MB,"This analysis Xiaozhi","lp");
    legend ->AddEntry(btoe,"This analysi Kunsu","lp");

    legend ->AddEntry(run12_pp_sts,"STAR p+p e-hadron correlation ^{[2]}","lp");
    legend ->AddEntry(Ge_D0,"STAR p+p e-D^{0} correlation","lp");

    legend ->AddEntry(gr_B_fraction_PHENIX,"PHENIX ^{[3]}","l");
    legend ->AddEntry(FONLL[1],"FONLL^{[4]}","l");    

    // legend ->AddEntry(PhNEX_sts,"PHENIX","lp");
    // legend ->AddEntry(gFONLLc,"FONLL","lp");
    // legend ->AddEntry(gFONLLl,"FONLL Uncertainty","lp");
    
    legend ->SetBorderSize(0);
    legend ->SetTextSize(0.04);
    legend ->SetFillStyle(0);
    legend->SetTextFont(62);
    legend ->Draw("same");


  c6->SaveAs("B_fraction.pdf");
  c6->SaveAs("B_fraction.gif");
  c6->SaveAs("B_fraction.png");

  
      return ;

}

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex)
{
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
}
