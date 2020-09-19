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
void Draw_B_fraction()

{
  
  char buf[1024];
  TH1::SetDefaultSumw2();
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetTitleFontSize(0.1);
  gStyle->SetTitleOffset(1.,"X");
  gStyle->SetTitleOffset(1.,"Y");

  gStyle->SetPadTopMargin(0.02);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.12);
  //  gStyle->SetEndErrorSize(6);
  gStyle->SetOptStat(000);
  

  TFile *input_run14_sts=new TFile("InPut/Fit_B_fraction_MB.root","READ");

  TFile *input_run14_sys=new TFile("InPut/B_fraction_sys.root","READ");

  TFile *input_run12_pp=new TFile("InPut/run12NPEh_rBPoints.root","READ");


  TFile *input_run14_DCAXY_new =new TFile("../Output/Fit_B_fraction_DCA_0.root","READ");
  TFile *input_run14_DCAZ_new =new TFile("../Output/Fit_B_fraction_DCA_1.root","READ");

  

  
    TH1F *B_fraction_MB=(TH1F *) input_run14_sts->Get("b_fraction_MB")->Clone("B_fraction_MB");
    // TH1F *B_fraction_sys=(TH1F *) input_run14_sys->Get("b_Fraction_sys")->Clone("B_fraction_sys");
    TH1F *B_fraction_sys=(TH1F *) input_run14_sys->Get("b_Fraction")->Clone("B_fraction_sys");


    TH1F *B_fraction_MB_dcaxy=(TH1F *) input_run14_DCAXY_new->Get("b_fraction_MB")->Clone("B_fraction_MB_dcaxy");
    TH1F *B_fraction_MB_dcaz=(TH1F *) input_run14_DCAZ_new->Get("b_fraction_MB")->Clone("B_fraction_MB_dcaz");


    
    for(int ipt=0;ipt<8;ipt++)
      {
	
	B_fraction_MB->SetBinContent(ipt+1,B_fraction_sys->GetBinContent(ipt+1));

	if(ipt<2)
	  {
	    B_fraction_MB->SetBinContent(ipt+1,-999);
	    B_fraction_sys->SetBinContent(ipt+1,-999);

	    B_fraction_MB->SetBinError(ipt+1,0);
	    B_fraction_sys->SetBinError(ipt+1,0);

	    B_fraction_MB_dcaxy->SetBinError(ipt+1,0);
	    B_fraction_MB_dcaxy->SetBinContent(ipt+1,-999);

	    B_fraction_MB_dcaz->SetBinError(ipt+1,0);
	    B_fraction_MB_dcaz->SetBinContent(ipt+1,-999);
	  }
      }
  TGraphErrors *  gr_B_fraction_MB=new TGraphErrors(B_fraction_MB);
  TGraphErrors *  gr_B_fraction_sys=new TGraphErrors(B_fraction_sys);


  TGraphErrors *  gr_B_fraction_dcaxy_new=new TGraphErrors(B_fraction_MB_dcaxy);
  TGraphErrors *  gr_B_fraction_dcaz_new=new TGraphErrors(B_fraction_MB_dcaz);

  TFile *input_PHENIX=new TFile("InPut/PHENIX.root","READ");
  TGraphAsymmErrors *gr_B_fraction_PHENIX=(TGraphAsymmErrors *) input_PHENIX->Get("Graph"); 

  // B_fraction_MB->Print("all");

  //    B_fraction_MB->SetBinContent(2,0.2);
    // B_fraction_MB->Print("all");

  TFile *file_run14=new TFile("run14_AuAu_bfraction.root","RECREATE");

  B_fraction_MB->SetName("run14_bF_sts");
  B_fraction_sys->SetName("run14_bF_sys");

  B_fraction_MB->Write();
  B_fraction_sys->Write();
  

    cout<< gr_B_fraction_MB->GetN()<<endl;
    //    cout<< gr_B_fraction_HT->GetN()<<endl;

    for(Int_t ipoint=0;ipoint<gr_B_fraction_MB->GetN();ipoint++)
      {
	gr_B_fraction_MB->SetPointError(ipoint,gr_B_fraction_MB->GetErrorX(ipoint), gr_B_fraction_MB->GetErrorY(ipoint));
	gr_B_fraction_sys->SetPointError(ipoint,0.1, gr_B_fraction_sys->GetErrorY(ipoint));
      }

    gr_B_fraction_MB->SetMarkerStyle(20);
    //   gr_B_fraction_sys->SetMarkerStyle(21);

    gr_B_fraction_MB->SetMarkerColor(2);
    //   gr_B_fraction_sys->SetMarkerColor(4);

    gr_B_fraction_MB->SetMarkerSize(3.8);
    //   gr_B_fraction_sys->SetMarkerSize();
    
    gr_B_fraction_MB->SetLineColor(2);
    //   gr_B_fraction_sys->SetLineColor(2);

    gr_B_fraction_MB->SetLineWidth(2);

    gr_B_fraction_sys->SetFillStyle(1001);
    gr_B_fraction_sys->SetFillColor(42);
    gr_B_fraction_sys->SetLineColor(42);
    gr_B_fraction_sys->SetLineWidth(2);

    gr_B_fraction_dcaxy_new->SetMarkerStyle(20);
    gr_B_fraction_dcaz_new->SetMarkerStyle(20);

    gr_B_fraction_dcaxy_new->SetMarkerColor(3);
    gr_B_fraction_dcaz_new->SetMarkerColor(6);

    gr_B_fraction_dcaxy_new->SetLineColor(3);
    gr_B_fraction_dcaz_new->SetLineColor(6);

    gr_B_fraction_dcaxy_new->SetMarkerSize(2.0);
    gr_B_fraction_dcaz_new->SetMarkerSize(2.0);
    
    // run12

    
    TGraphAsymmErrors *run12_pp_sts=  (TGraphAsymmErrors *) input_run12_pp->Get("StatError_Run6");
    TGraphAsymmErrors *run12_pp_sys=  (TGraphAsymmErrors *) input_run12_pp->Get("systError_Run6");    

    for(Int_t ipoint=0;ipoint<run12_pp_sys->GetN();ipoint++)
      {
	run12_pp_sys->SetPointError(ipoint,0.1,0.1, run12_pp_sys->GetErrorYlow(ipoint),run12_pp_sys->GetErrorYhigh(ipoint));


	// run12_pp_sys->SetPointError(ipoint,0, 0);
	// run12_pp_sys->SetPoint(ipoint,-999, -999);

      }

    run12_pp_sts->SetLineColor(4);
    run12_pp_sts->SetMarkerColor(4);
    run12_pp_sts->SetMarkerStyle(20);

    // run12_pp_sys->SetLineColor(4);
    // run12_pp_sys->SetMarkerColor(4);

    run12_pp_sys->SetFillStyle(1001);
    run12_pp_sys->SetFillColor(34);
    run12_pp_sts->SetMarkerSize(3.8);


    // FONLL
    TGraph *FONLL[2];
    FONLL[0] = new TGraph("InPut/FONLL_BAND_UP.dat");
    FONLL[1] = new TGraph("InPut/FONLL_BAND_DW.dat");
    FONLL[0]->SetLineStyle(7);
    FONLL[1]->SetLineStyle(7);

    FONLL[0]->SetLineWidth(1.5);
    FONLL[1]->SetLineWidth(1.5);

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

    //   for(int ipt=0;ipt<8;ipt++)
    // {
    //   B_fraction_MB->SetBinContent(ipt+1,B_fraction_sys->GetBinContent(ipt+1));

    // }




    TCanvas *c6=new TCanvas("c6","",1400,1000);
    TH2F *h6=new TH2F("h6","",100,0.2,8.5,100,0,1.3);
    h6->Draw();
    h6->GetXaxis()->SetTitle("p_{T}^{e} (GeV/c)");
    //   h6->GetYaxis()->SetTitle("B#rightarrow e / (B+D) #rightarrow e");
    h6->GetYaxis()->SetTitle("N_{e_{B}}/(N_{e_{D}}+N_{e_{B}})");
    //      h6->GetXaxis()->SetTitleSize(0.04);
    h6->GetXaxis()->SetLabelSize(0.05);
    h6->GetYaxis()->SetLabelSize(0.05);
    // h6->GetYaxis()->SetTitleOffset(1);
    // h6->GetXaxis()->SetTitleOffset(1);
    
    h6->GetXaxis()->CenterTitle(true);
    h6->GetYaxis()->CenterTitle(true);
    h6->Draw();

    // Draw PHENIX

    
    gr_B_fraction_PHENIX->SetLineWidth(2);
    gr_B_fraction_PHENIX->SetLineColor(36);
    gr_B_fraction_PHENIX->SetFillColor(17);
    
    
    gr_B_fraction_PHENIX->Draw("3Lsame");
    //Ge_D0->SetName("eD0");
    // Ge_D0->Draw("sameP");
    // Ge_D0_sys->Draw("same e2");

    gr_B_fraction_sys->Draw("sameE2");
    gr_B_fraction_MB->Draw("samePE");

    gr_B_fraction_dcaxy_new->Draw("samePE");
    gr_B_fraction_dcaz_new->Draw("samePE");
	
    //  gr_B_fraction_sys-> Draw("p:[]same");

    run12_pp_sys->Draw("sameE2");
    run12_pp_sts->Draw("samePE");
    
    FONLL[0]->Draw("same");
    FONLL[1]->Draw("same");
    
    sprintf(buf,"Au+Au @ 200 GeV");
    drawLatex(0.65,0.9,buf,22,0.055,1);

    sprintf(buf,"Au+Au @ 200 GeV");
    drawLatex(0.65,0.84,"0-80 %",22,0.045,1);

    sprintf(buf,"STAR Preliminary");
    drawLatex(0.2,0.9,buf,62,0.05,2);


    
    TLegend *legend  = new TLegend(0.16,0.62,0.4,0.86);
    legend ->AddEntry(gr_B_fraction_MB,"STAR Au+Au HFT QM17","p");
    legend ->AddEntry(gr_B_fraction_dcaxy_new,"Included Ds,Lc","P");
    legend ->AddEntry(gr_B_fraction_dcaz_new,"Fit DCA_{Z}","P");
    
    legend ->AddEntry(run12_pp_sts,"STAR p+p e-hadron correlation ","p");
    //   legend ->AddEntry(Ge_D0,"STAR p+p e-D^{0} correlation","p");
    legend ->AddEntry(gr_B_fraction_PHENIX,"PHENIX Au+Au VTX","l");
    legend ->AddEntry(FONLL[1],"FONLL p+p","l");    

    // legend ->AddEntry(PhNEX_sts,"PHENIX","lp");
    // legend ->AddEntry(gFONLLc,"FONLL","lp");
    // legend ->AddEntry(gFONLLl,"FONLL Uncertainty","lp");
    
    legend ->SetBorderSize(0);
    legend ->SetTextSize(0.04);
    legend ->SetFillStyle(0);
    legend->SetTextFont(22);
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
