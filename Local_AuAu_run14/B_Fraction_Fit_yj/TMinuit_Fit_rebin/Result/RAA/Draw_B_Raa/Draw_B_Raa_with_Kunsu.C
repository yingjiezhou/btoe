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
#include "TGraph.h"

#include "TRandom3.h"
#include "TGraphErrors.h"
#include "InPut/Binning_Raa.h"
//#include "makeRAA_e.C"
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
void Draw_B_Raa_with_Kunsu()

{
  
  char buf[1024];
  TH1::SetDefaultSumw2();
  gStyle->SetTitleSize(0.06,"XY");
  gStyle->SetTitleFontSize(0.1);
  gStyle->SetTitleOffset(1.,"X");
  gStyle->SetTitleOffset(1.,"Y");
  
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadRightMargin(0.06);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetEndErrorSize(6);
  gStyle->SetOptStat(000);
  
  TFile *input_Total_Raa=new TFile("InPut/NPEHTRaa080-1.root","READ");
  TFile *input_B_D_model=new TFile("InPut/B_D_Raa.root","READ");

  TFile *input_B_fraction_pp=new TFile("InPut/run12NPEh_rBPoints.root","READ");
  // TFile *input_B_fraction_AA=new TFile("InPut/Fit_B_fraction_MB.root","READ");
  TFile *input_B_fraction_AA=new TFile("InPut/Fit_B_fraction_MB_default.root","READ");
  TFile *input_B_fraction_AA_sys=new TFile("InPut/B_fraction_sys.root","READ");
  
  //=================================================
  TH1F *Npe_Raa_all_sts=(TH1F *) input_Total_Raa->Get("NPERaaStat_AuAu_0")->Clone("Npe_Raa_all_sts");
  TH1F *Npe_Raa_all_sys=(TH1F *) input_Total_Raa->Get("NPERaaSys_AuAu_0")->Clone("Npe_Raa_all_sys");
  TGraph *gr_Be= (TGraph *) input_B_D_model->Get("RAA_e_B");
  TGraph *gr_De= (TGraph *) input_B_D_model->Get("RAA_e_D");
  
  
  TGraphAsymmErrors *pp_sts=  (TGraphAsymmErrors *) input_B_fraction_pp->Get("StatError_Run6");
  TGraphAsymmErrors *pp_sys=  (TGraphAsymmErrors *) input_B_fraction_pp->Get("systError_Run6");
  TH1F *B_fraction_AA=(TH1F *) input_B_fraction_AA->Get("b_fraction_MB")->Clone("B_fraction_AA");
  TH1F *B_fraction_AA_sys=(TH1F *) input_B_fraction_AA_sys->Get("b_Fraction_sys")->Clone("B_Fraction_sys");
  //=================================================
  
  TH1F *  b_fraction_pp_sts=new TH1F("b_fraction_pp_sts","",Npt,ptbin);
  TH1F *  b_fraction_pp_sys=new TH1F("b_fraction_pp_sys","",Npt,ptbin);
  
  TH1F *  b_fraction_AuAu_sts=new TH1F("b_fraction_AuAu_sts","",Npt,ptbin);
  // TH1F *  b_fraction_AuAu_sys=new TH1F("b_fraction_AuAu_sys","",Npt,ptbin);
  
  TH1F *  Npe_AuAuRaa_sts=new TH1F("Npe_AuAuRaa_sts","",Npt,ptbin);
  // TH1F *  Npe_AuAuRaa_sys=new TH1F("Npe_AuAuRaa_sys","",Npt,ptbin);
  
  TH1F *  one_sts=new TH1F("one_sts","",Npt,ptbin);
  // TH1F *  one_sys=new TH1F("one_sys","",Npt,ptbin);
  
  TH1F *  Fc_to_e_AA_sts=new TH1F("Fc_to_e_AA_sts","",Npt,ptbin);
  TH1F *  Fc_to_e_pp_sts=new TH1F("Fc_to_e_pp_sts","",Npt,ptbin);
  
  // TH1F *  Fc_to_e_AA_sys=new TH1F("Fc_to_e_AA_sys","",Npt,ptbin);
  // TH1F *  Fc_to_e_pp_sys=new TH1F("Fc_to_e_pp_sys","",Npt,ptbin);
  
  TH1F *  Fc_to_e_sts=new TH1F("Fc_to_e_sts","",Npt,ptbin);
  TH1F *  Fb_to_e_sts=new TH1F("Fb_to_e_sts","",Npt,ptbin);
  
  // TH1F *  Fb_to_c_Rati_sts=new TH1F("Fb_to_e_sts","",Npt,ptbin);
  
  
  TH1F *  Fb_to_e_Raa_sys=new TH1F("Fb_to_Raa_e_sys","",Npt,ptbin);
  TH1F *  Fc_to_e_Raa_sts=new TH1F("Fc_to_e_Raa_sts","",Npt,ptbin);
  TH1F *  Fc_to_e_Raa_sys=new TH1F("Fc_to_e_Raa_sys","",Npt,ptbin);
  TH1F *  Fb_to_e_sys=new TH1F("Fb_to_e_sys","",Npt,ptbin);
  
  TH1F *  Fc_to_e_Raa_pp_sys=new TH1F("Fc_to_e_Raa_pp_sys","",Npt,ptbin);
  TH1F *  Fb_to_e_pp_sys=new TH1F("Fb_to_e_pp_sys","",Npt,ptbin);
  TH1F *  Fb_to_e_Raa_pp_sys=new TH1F("Fb_to_Raa_e_pp_sys","",Npt,ptbin);
  
  // TH1F *  Fb_to_e_sys=new TH1F("Fb_to_e_sys","",Npt,ptbin);
  // TH1F *  Fc_to_e_sys=new TH1F("Fc_to_e_sys","",Npt,ptbin);
  
  TH1F *Fb_to_e_Raa_sts;
  
  
  Npe_AuAuRaa_sts->Sumw2();
  // Npe_AuAuRaa_sys->Sumw2();
  
  one_sts->Sumw2();
  // one_sys->Sumw2();
  
  b_fraction_pp_sts->Sumw2();
  // b_fraction_pp_sys->Sumw2();
  
  b_fraction_AuAu_sts->Sumw2();
  // b_fraction_AuAu_sys->Sumw2();
  
  Fc_to_e_AA_sts->Sumw2();
  // Fc_to_e_AA_sys->Sumw2();
  
  Fc_to_e_pp_sts->Sumw2();
  // Fc_to_e_pp_sys->Sumw2();
  
  Fc_to_e_Raa_sts->Sumw2();
  // Fc_to_e_Raa_sys->Sumw2();
  
  Fc_to_e_Raa_pp_sys->Sumw2();
  Fb_to_e_pp_sys->Sumw2();
  Fb_to_e_Raa_pp_sys->Sumw2();
  
  //=================================================
  
  //Get pp result from run06; // zyj rebinned??
  b_fraction_pp_sts->SetBinContent(1,0.316971);
  b_fraction_pp_sts->SetBinError(1,0.060373);
  
  b_fraction_pp_sts->SetBinContent(2,0.418603);
  b_fraction_pp_sts->SetBinError(2,0.066405);
  
  b_fraction_pp_sts->SetBinContent(3,0.484639);
  b_fraction_pp_sts->SetBinError(3,0.094393);
  
  b_fraction_pp_sts->SetBinContent(4,0.522393);
  b_fraction_pp_sts->SetBinError(4,0.066405);
  
  //sys
  b_fraction_pp_sys->SetBinContent(1,0.316971);
  b_fraction_pp_sys->SetBinError(1,0.030117);
  
  b_fraction_pp_sys->SetBinContent(2,0.418603);
  b_fraction_pp_sys->SetBinError(2,0.032119);
  
  b_fraction_pp_sys->SetBinContent(3,0.484639);
  b_fraction_pp_sys->SetBinError(3,0.074831);
  
  b_fraction_pp_sys->SetBinContent(4,0.522393);
  b_fraction_pp_sys->SetBinError(4,0.060432);
  
  //=================================================

  //Get AuAu  Raa result from run06;
  Npe_AuAuRaa_sts->SetBinContent(1,Npe_Raa_all_sts->GetBinContent(1));
  Npe_AuAuRaa_sts->SetBinError(1,Npe_Raa_all_sts->GetBinError(1));
  
  Npe_AuAuRaa_sts->SetBinContent(2,Npe_Raa_all_sts->GetBinContent(2));
  Npe_AuAuRaa_sts->SetBinError(2,Npe_Raa_all_sts->GetBinError(2));
  
  Npe_AuAuRaa_sts->SetBinContent(3,Npe_Raa_all_sts->GetBinContent(3));
  Npe_AuAuRaa_sts->SetBinError(3,Npe_Raa_all_sts->GetBinError(3));
  
  Npe_AuAuRaa_sts->SetBinContent(4,Npe_Raa_all_sts->GetBinContent(4));
  Npe_AuAuRaa_sts->SetBinError(4,Npe_Raa_all_sts->GetBinError(4));// because take only 4 pt bin?
  
  //Get b fraction sts in AuAu result from run14;
  b_fraction_AuAu_sts->SetBinContent(1,B_fraction_AA->GetBinContent(5));
  b_fraction_AuAu_sts->SetBinError(1,B_fraction_AA->GetBinError(5));
  
  b_fraction_AuAu_sts->SetBinContent(2,B_fraction_AA->GetBinContent(6));
  b_fraction_AuAu_sts->SetBinError(2,B_fraction_AA->GetBinError(6));
  
  b_fraction_AuAu_sts->SetBinContent(3,B_fraction_AA->GetBinContent(7));
  b_fraction_AuAu_sts->SetBinError(3,B_fraction_AA->GetBinError(7));
  
  b_fraction_AuAu_sts->SetBinContent(4,B_fraction_AA->GetBinContent(8));
  b_fraction_AuAu_sts->SetBinError(4,B_fraction_AA->GetBinError(8)); // because take only 4 pt bin?
  //=================================================

  //
  one_sts->SetBinContent(1,1);
  one_sts->SetBinError(1,0);
  
  one_sts->SetBinContent(2,1);
  one_sts->SetBinError(2,0);
  
  one_sts->SetBinContent(3,1);
  one_sts->SetBinError(3,0);
  
  one_sts->SetBinContent(4,1);
  one_sts->SetBinError(4,0);
  
  //=================================================
  b_fraction_pp_sts->SetMarkerColor(2);
  b_fraction_pp_sts->SetMarkerStyle(20);
  b_fraction_pp_sts->SetLineColor(2);
  
  Npe_AuAuRaa_sts->SetMarkerColor(3);
  Npe_AuAuRaa_sts->SetMarkerStyle(20);
  Npe_AuAuRaa_sts->SetLineColor(3);
  
  b_fraction_AuAu_sts->SetMarkerColor(4);
  b_fraction_AuAu_sts->SetMarkerStyle(20);
  b_fraction_AuAu_sts->SetLineColor(4);
  //=================================================
  
  TCanvas *c2=new TCanvas("c2","",1000,1200);
  c2->cd();
  pp_sts->GetYaxis()->SetRangeUser(0,1);
  pp_sts->Draw(""); // because of run06 binning problem??
  b_fraction_pp_sts->Draw("samePE"); // rebinned pp zyj
  Npe_AuAuRaa_sts->Draw("samePE");
  b_fraction_AuAu_sts->Draw("samePE");
  
  c2->SaveAs("check.pdf");
  
  //=================================================
  // fraction ratio * RAA(e) = RAA(b/c->e)
  Fc_to_e_AA_sts->Add(one_sts);
  Fc_to_e_AA_sts->Add(b_fraction_AuAu_sts,-1);
  
  Fc_to_e_pp_sts->Add(one_sts);
  Fc_to_e_pp_sts->Add(b_fraction_pp_sts,-1);
  
  Fc_to_e_AA_sts->Divide(Fc_to_e_pp_sts);
  Fc_to_e_Raa_sts=(TH1F *) Fc_to_e_AA_sts->Clone("Fc_to_e_Raa_sts");
  Fc_to_e_Raa_sts->Multiply(Npe_AuAuRaa_sts);
  
  //BB
  
  Fb_to_e_sts->Add(b_fraction_AuAu_sts);
  Fb_to_e_sts->Divide(b_fraction_pp_sts);
  
  Fb_to_e_Raa_sts=(TH1F *) Fb_to_e_sts->Clone("Fb_to_e_Raa_sts");
  Fb_to_e_Raa_sts->Multiply(Npe_AuAuRaa_sts);
  Fb_to_e_Raa_sts->SetMarkerStyle(20);
  Fb_to_e_Raa_sts->SetMarkerColor(1);
  Fb_to_e_Raa_sts->SetLineColor(1);
  
  Fb_to_e_sts->Divide(Fc_to_e_AA_sts); // double ratio
  Fb_to_e_sts->SetMarkerStyle(20);
  Fb_to_e_sts->SetMarkerColor(4);
  Fb_to_e_sts->SetLineColor(4);
 
  
  //=================================================
  // draw hist setting
  TH2F *h1=new TH2F("h1","",100,0,10,100,0.15,4);
  TH2F *h2=new TH2F("h2","",100,0,10,2,0.5,4.1);
  
  //   h2->GetYaxis()->SetRangeUser(0.01,2.6);
  h2->GetXaxis()->SetTitle("p_{T}^{e} (GeV/c)");
  h2->GetYaxis()->SetTitle("R_{AA}^{b #rightarrow e} / R_{AA}^{c #rightarrow e}");
  
  
  h2->GetXaxis()->CenterTitle();
  h2->GetYaxis()->CenterTitle();
  
  h2->GetYaxis()->SetTitleSize(0.1);
  h2->GetXaxis()->SetTitleSize(0.14);
  
  //    h2->GetXaxis()->SetTitleOffset(1);
  h2->GetYaxis()->SetTitleOffset(0.4);
  h2->GetXaxis()->SetTitleOffset(0.8);
  
  h2->GetYaxis()->SetLabelSize(0.08);
  h2->GetXaxis()->SetLabelSize(0.08);
  
  h2->GetYaxis()->SetNdivisions(6);
  h1->GetYaxis()->SetNdivisions(20);
  
  //   h1->GetYaxis()->SetRangeUser(0.01,2.6);
  h1->GetXaxis()->SetTitle("p_{T}^{e} (GeV/c)");
  h1->GetYaxis()->SetTitle("R_{AA}");
  
  
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->CenterTitle();
  
  h1->GetYaxis()->SetTitleSize(0.06);
  h1->GetXaxis()->SetTitleSize(0.08);
  
  h1->GetXaxis()->SetTitleOffset(1);
  h1->GetYaxis()->SetTitleOffset(0.6);
  h1->GetYaxis()->SetLabelSize(0.08);
  h1->GetXaxis()->SetLabelSize(0.08);
  
  Fc_to_e_Raa_sts->SetMarkerStyle(20);
  Fc_to_e_Raa_sts->SetMarkerColor(2);
  Fc_to_e_Raa_sts->SetLineColor(2);
  
  Fc_to_e_AA_sts->SetMarkerStyle(20);
  Fc_to_e_AA_sts->SetMarkerColor(2);
  Fc_to_e_AA_sts->SetLineColor(2);
  
  Fb_to_e_Raa_sts->SetLineColor(1);
  Fb_to_e_Raa_sts->SetMarkerColor(1);
  Fb_to_e_Raa_sts->SetMarkerStyle(20);
  
  
  Fc_to_e_AA_sts->SetMarkerStyle(20);
  Fb_to_e_Raa_sts->SetMarkerSize(1.5);
  Fc_to_e_Raa_sts->SetMarkerSize(1.5);
  
  Fc_to_e_AA_sts->SetLineWidth(1.8);
  Fb_to_e_Raa_sts->SetLineWidth(1.8);
  Fc_to_e_Raa_sts->SetLineWidth(1.8);
  
  Fb_to_e_sts->SetMarkerSize(1.5);
  Fb_to_e_sts->SetLineWidth(1.8);
  Fb_to_e_sts->SetMarkerStyle(20);
  
  gr_De->SetLineColor(2);
  gr_Be->SetLineColor(1);
  
  TGraphErrors *gr_Npe_Raa_all_sts=new TGraphErrors(Npe_Raa_all_sts);
  TGraphErrors *gr_Npe_Raa_all_sys=new TGraphErrors(Npe_Raa_all_sys);
  
  
  // gr_Npe_Raa_all_sts->SetMarkerStyle(21);
  // gr_Npe_Raa_all_sts->SetMarkerSize(1.5);
  // gr_Npe_Raa_all_sts->SetLineWidth(1.8);
  
  //=================================================
  // calculate error
  
  for(Int_t ipt=0;ipt<4;ipt++)
  {
    cout<< "ipt ="<< ipt+1<<" Bf pp="<< b_fraction_pp_sts->GetBinContent(1,0.316971)<<"Bf AuAu= "<<B_fraction_AA->GetBinContent(ipt+5)<< Npe_Raa_all_sts->GetBinContent(ipt+1)<<endl;
    cout<<ipt << " RAA b "<< (B_fraction_AA->GetBinContent(ipt+5))/(b_fraction_pp_sts->GetBinContent(ipt+1))*Npe_Raa_all_sts->GetBinContent(ipt+1)<<" ";
    cout<< " hist "<<Fb_to_e_Raa_sts->GetBinContent(ipt+1)<<endl;
    cout<< " sts<<"<<Fb_to_e_Raa_sts->GetBinError(ipt+1)<< " "<<Fb_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA->GetBinError(ipt+5)/B_fraction_AA->GetBinContent(ipt+5),2)+TMath::Power(b_fraction_pp_sts->GetBinError(ipt+1)/b_fraction_pp_sts->GetBinContent(ipt+1),2)+TMath::Power(Npe_Raa_all_sts->GetBinError(ipt+1)/Npe_Raa_all_sts->GetBinContent(ipt+1),2)) <<endl;;
    
    cout<<ipt <<" RAA c "<< Fc_to_e_Raa_sts->GetBinContent(ipt+1)<<"  "<<(1-B_fraction_AA->GetBinContent(ipt+5))/(1-b_fraction_pp_sts->GetBinContent(ipt+1))*Npe_Raa_all_sts->GetBinContent(ipt+1)<<" "<<endl;
    
    cout<<ipt <<" Ratio "<< Fb_to_e_sts->GetBinContent(ipt+1)<<"  "<<
    (B_fraction_AA->GetBinContent(ipt+5)/b_fraction_pp_sts->GetBinContent(ipt+1))/((1-B_fraction_AA->GetBinContent(ipt+5))/(1-b_fraction_pp_sts->GetBinContent(ipt+1)))<<" "<<endl;
    //Fb_to_e_sts
    //cout<< " hist c "<<Fc_to_e_Raa_sts->GetBinContent(ipt+1)<<endl;
    
    cout<< " sts<< ratio "<<Fb_to_e_sts->GetBinError(ipt+1)<< " "<<Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA->GetBinError(ipt+5)/B_fraction_AA->GetBinContent(ipt+5),2)+TMath::Power(b_fraction_pp_sts->GetBinError(ipt+1)/b_fraction_pp_sts->GetBinContent(ipt+1),2)) <<endl;;
    
    
    Fb_to_e_Raa_sys->SetBinContent(ipt+1,Fb_to_e_Raa_sts->GetBinContent(ipt+1));
    Fc_to_e_Raa_sys->SetBinContent(ipt+1,Fc_to_e_Raa_sts->GetBinContent(ipt+1));
    
    float Fb_to_e_Raa_sys_err=Fb_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA_sys->GetBinError(ipt+5)/B_fraction_AA_sys->GetBinContent(ipt+5),2)+TMath::Power(Npe_Raa_all_sys->GetBinError(ipt+1)/Npe_Raa_all_sys->GetBinContent(ipt+1),2));
    
    float Fc_to_e_Raa_sys_err=Fc_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA_sys->GetBinError(ipt+5)/B_fraction_AA_sys->GetBinContent(ipt+5),2)+TMath::Power(Npe_Raa_all_sys->GetBinError(ipt+1)/Npe_Raa_all_sys->GetBinContent(ipt+1),2));//+TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    float Fb_to_e_sys_err=Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA_sys->GetBinError(ipt+5)/B_fraction_AA_sys->GetBinContent(ipt+5),2));//+TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    float Fb_to_e_Raa_pp_sys_err=Fb_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    float Fc_to_e_Raa_pp_sys_err=Fc_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    float Fb_to_e_pp_sys_err=Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    
    Fb_to_e_Raa_sys->SetBinError(ipt+1,Fb_to_e_Raa_sys_err);
    Fc_to_e_Raa_sys->SetBinError(ipt+1,Fc_to_e_Raa_sys_err);
    
    
    Fb_to_e_sys->SetBinContent(ipt+1,Fb_to_e_sts->GetBinContent(ipt+1));
    Fb_to_e_sys->SetBinError(ipt+1,Fb_to_e_sys_err);
    
    Fc_to_e_Raa_pp_sys->SetBinContent(ipt+1,Fc_to_e_Raa_sts->GetBinContent(ipt+1));
    Fb_to_e_pp_sys->SetBinContent(ipt+1,Fb_to_e_sts->GetBinContent(ipt+1));
    Fb_to_e_Raa_pp_sys->SetBinContent(ipt+1,Fb_to_e_Raa_sts->GetBinContent(ipt+1));
    
    Fc_to_e_Raa_pp_sys->SetBinError(ipt+1,Fc_to_e_Raa_pp_sys_err);
    Fb_to_e_pp_sys->SetBinError(ipt+1,Fb_to_e_Raa_pp_sys_err);
    Fb_to_e_Raa_pp_sys->SetBinError(ipt+1,Fb_to_e_pp_sys_err);
    
  }
  
  TGraphErrors * gr_Fb_to_e_Raa_sys= new TGraphErrors(Fb_to_e_Raa_sys);
  TGraphErrors * gr_Fc_to_e_Raa_sys= new TGraphErrors(Fc_to_e_Raa_sys);
  TGraphErrors * gr_Fb_to_e_sys= new TGraphErrors(Fb_to_e_sys);
  
  TGraphErrors * gr_Fb_to_e_Raa_pp_sys= new TGraphErrors(Fb_to_e_Raa_pp_sys);
  TGraphErrors * gr_Fc_to_e_Raa_pp_sys= new TGraphErrors(Fc_to_e_Raa_pp_sys);
  TGraphErrors * gr_Fb_to_e_pp_sys= new TGraphErrors(Fb_to_e_pp_sys);
  
  TGraphErrors *   gr_Fb_to_e_Raa_sts=new TGraphErrors(Fb_to_e_Raa_sts);
  TGraphErrors *   gr_Fc_to_e_Raa_sts=new TGraphErrors(Fc_to_e_Raa_sts);
  
  //=================================================
  // to a new hist
  
  for(Int_t ipoint=0;ipoint<4;ipoint++)
  {
    
    gr_Fc_to_e_Raa_sys->SetPointError(ipoint,0.1, gr_Fc_to_e_Raa_sys->GetErrorY(ipoint));
    gr_Fc_to_e_Raa_pp_sys->SetPointError(ipoint,0.0, gr_Fc_to_e_Raa_pp_sys->GetErrorY(ipoint));
    
    gr_Npe_Raa_all_sys->SetPointError(ipoint,0.1, gr_Npe_Raa_all_sys->GetErrorY(ipoint));
    
    gr_Fb_to_e_sys->SetPointError(ipoint,0.1, gr_Fb_to_e_sys->GetErrorY(ipoint));
    gr_Fb_to_e_pp_sys->SetPointError(ipoint,0.0, gr_Fb_to_e_pp_sys->GetErrorY(ipoint));
    
    gr_Fb_to_e_Raa_pp_sys->SetPointError(ipoint,0.0, gr_Fb_to_e_Raa_pp_sys->GetErrorY(ipoint));
    gr_Fb_to_e_Raa_sys->SetPointError(ipoint,0.1, gr_Fb_to_e_Raa_sys->GetErrorY(ipoint));
    
    gr_Fb_to_e_Raa_pp_sys->SetPointError(ipoint,0.0, gr_Fb_to_e_Raa_pp_sys->GetErrorY(ipoint));
    gr_Fb_to_e_Raa_sys->SetPointError(ipoint,0.1, gr_Fb_to_e_Raa_sys->GetErrorY(ipoint));
    
    Double_t bX=-99;Double_t bY=-99;
    
    gr_Fb_to_e_Raa_pp_sys->GetPoint(ipoint,bX,bY);
    gr_Fb_to_e_Raa_pp_sys->SetPoint(ipoint,bX+0.05,bY);
    gr_Fb_to_e_Raa_sys->SetPoint(ipoint,bX+0.05, bY);
    
    gr_Fb_to_e_Raa_sts->SetPoint(ipoint,bX+0.05, bY);
    gr_Fb_to_e_Raa_pp_sys->SetPointError(ipoint,0.1,gr_Fb_to_e_Raa_pp_sys->GetErrorY(ipoint));
    gr_Fb_to_e_Raa_sys->SetPointError(ipoint,0.1, gr_Fb_to_e_Raa_sys->GetErrorY(ipoint));
    
    
    
  }
  
  //=================================================
  // setting draw
  gr_Fb_to_e_Raa_sys->SetFillStyle(1001);
  gr_Fb_to_e_Raa_sys->SetFillColor(40);
  gr_Fb_to_e_Raa_sys->SetLineColor(40);
  
  gr_Fc_to_e_Raa_sys->SetFillStyle(1001);
  gr_Fc_to_e_Raa_sys->SetFillColor(17);
  gr_Fc_to_e_Raa_sys->SetLineColor(17);
  
  
  Npe_Raa_all_sts->SetMarkerStyle(20);
  Npe_Raa_all_sts->SetLineColor(6);
  Npe_Raa_all_sts->SetMarkerColor(6);
  Npe_Raa_all_sts->SetMarkerSize(1.5);
  
  
  gr_Npe_Raa_all_sys->SetFillStyle(1001);
  gr_Npe_Raa_all_sys->SetFillColor(41);
  gr_Npe_Raa_all_sys->SetLineColor(41);
  
  gr_Fb_to_e_sys->SetFillStyle(1001);
  gr_Fb_to_e_sys->SetFillColor(29);
  gr_Fb_to_e_sys->SetLineColor(29);
  
  
  gr_Fb_to_e_Raa_pp_sys->SetLineColor(1);
  gr_Fc_to_e_Raa_pp_sys->SetLineColor(2);
  gr_Fb_to_e_pp_sys->SetLineColor(4);
  
  gr_Fb_to_e_Raa_sts->SetLineColor(1);
  gr_Fb_to_e_Raa_sts->SetMarkerColor(1);
  gr_Fb_to_e_Raa_sts->SetMarkerStyle(20);
  
  gr_Fc_to_e_Raa_sts->SetLineColor(2);
  gr_Fc_to_e_Raa_sts->SetMarkerColor(2);
  gr_Fc_to_e_Raa_sts->SetMarkerStyle(20);
  
  //=================================================
  // model
  TGraphErrors *  gr_duke_B=new TGraphErrors("InPut/eForSTAR_0_80/RAA_Be.dat","%lg %lg");
  TGraphErrors *  gr_duke_D=new TGraphErrors("InPut/eForSTAR_0_80/RAA_De.dat","%lg %lg");
  
  gr_duke_D->SetLineColor(2);
  gr_duke_D->SetLineStyle(3);
  gr_duke_D->SetLineWidth(2);
  
  gr_duke_B->SetLineColor(1);
  gr_duke_B->SetLineStyle(3);
  gr_duke_B->SetLineWidth(2);
  
  
  // from Kunsu, double ratio???
  TFile *file_kunsu=new TFile("InPut/btoe_2000_kunsu.root","READ");
  TGraphAsymmErrors* doubleRatio=(TGraphAsymmErrors *) file_kunsu->Get("doubleRatio");
  TGraphAsymmErrors* doubleRatioSys=(TGraphAsymmErrors *) file_kunsu->Get("doubleRatioSys");
  
  TGraphAsymmErrors* doubleRatioc=(TGraphAsymmErrors *) file_kunsu->Get("doubleRatioc");
  TGraphAsymmErrors* doubleRatiocSys=(TGraphAsymmErrors *) file_kunsu->Get("doubleRatiocSys");
  
  
  for(Int_t i=0;i<8;i++)
  {
    Double_t bX=-99;Double_t bY=-99;
    doubleRatio->GetPoint(i,bX,bY);
    doubleRatio->SetPoint(i,bX+0.2,bY);
    
    doubleRatioSys->GetPoint(i,bX,bY);
    doubleRatioSys->SetPoint(i,bX+0.2,bY);
    
    doubleRatioc->GetPoint(i,bX,bY);
    doubleRatioc->SetPoint(i,bX+0.2,bY);
    
    doubleRatiocSys->GetPoint(i,bX,bY);
    doubleRatiocSys->SetPoint(i,bX+0.2,bY);

  }
  
  doubleRatio->SetMarkerSize(2.);
  doubleRatio->SetMarkerSize(2.);
  doubleRatio->SetMarkerStyle(21);
  doubleRatio->SetMarkerColor(3);
  doubleRatio->SetLineColor(3);
  doubleRatioSys->SetLineColor(3);
  
  //   doubleRatioc->SetMarkerSize(2.);
  doubleRatioc->SetMarkerSize(2.);
  doubleRatioc->SetMarkerStyle(21);
  doubleRatioc->SetMarkerColor(6);
  doubleRatioc->SetLineColor(6);
  doubleRatiocSys->SetLineColor(6);
  
  
  TLegend *legend  = new TLegend(0.65,0.65,0.76,0.95);
  legend ->AddEntry(Fb_to_e_Raa_sts,"B #rightarrow e xiaozhi","p");
  legend ->AddEntry(Fc_to_e_Raa_sts,"D #rightarrow e xiaozhi","p");
  //   legend ->AddEntry(Npe_Raa_all_sts,"(D+B) #rightarrow e","p");
  legend ->AddEntry(gr_duke_B,"0-80% B #rightarrow e Duke Model","l");
  legend ->AddEntry(gr_duke_D,"0-80% D #rightarrow e Duke Model","l");
  // legend ->AddEntry(PhNEX_sts,"PHENIX","lp");
  // legend ->AddEntry(gFONLLc,"FONLL","lp");
  // legend ->AddEntry(gFONLLl,"FONLL Uncertainty","lp");
  
  legend ->SetBorderSize(0);
  legend ->SetTextSize(0.05);
  legend ->SetFillStyle(0);
  legend->SetTextFont(62);
  
  TLegend *legend_1  = new TLegend(0.2,0.15,0.35,0.35);
  legend_1 ->AddEntry(doubleRatio,"B #rightarrow e kunsu","p");
  legend_1 ->AddEntry(doubleRatioc,"D #rightarrow e kunsu","p");
  //   legend ->AddEntry(Npe_Raa_all_sts,"(D+B) #rightarrow e","p");
  // legend ->AddEntry(PhNEX_sts,"PHENIX","lp");
  // legend ->AddEntry(gFONLLc,"FONLL","lp");
  // legend ->AddEntry(gFONLLl,"FONLL Uncertainty","lp");
  
  legend_1 ->SetBorderSize(0);
  legend_1 ->SetTextSize(0.05);
  legend_1 ->SetFillStyle(0);
  legend_1->SetTextFont(62);
  
  
  TLine *l1=new TLine(0,1,10,1);
  l1->SetLineColor(4);
  l1->SetLineWidth(2.5);
  l1->SetLineStyle(7);
  
  TCanvas *c3=new TCanvas("c3","",800,600);
  
  c3->cd();
  TPad* pad1 = new TPad("pad1","pad1",0.00,0.4,1.00,1.00);pad1->Draw();
  TPad* pad2 = new TPad("pad2","pad2",0.00,0.00,1.00,0.4);pad2->Draw();
  pad1->SetMargin(0.13,0.02,0,0.02);
  pad2->SetMargin(0.13,0.02,0.3,0.0);
  
  pad1->cd();
  gPad->SetLogy(1);
  h1->Draw();
  
  gr_Fb_to_e_Raa_sys->Draw("sameE2");
  gr_Fc_to_e_Raa_sys->Draw("sameE2");
  doubleRatio->Draw("samePE");
  doubleRatioSys->Draw("p[],same");
  
  doubleRatioc->Draw("samePE");

  gr_duke_D->Draw("samec");
  gr_duke_B->Draw("samec");

  gr_Fb_to_e_Raa_pp_sys->Draw("p[]:same");
  gr_Fc_to_e_Raa_pp_sys->Draw("p[]:same");
  
  gr_Fc_to_e_Raa_sts->Draw("samePE");
  gr_Fb_to_e_Raa_sts->Draw("samePE");
  
  l1->Draw("same");
  
  sprintf(buf,"STAR Au+Au@#sqrt{s_{NN}}=200 GeV");
  drawLatex(0.18,0.82,buf,62,0.06,1);
  
  sprintf(buf,"0-80 %  |#eta|<0.7");
  drawLatex(0.18,0.75,"0-80% |#eta|<0.7",62,0.06,1);
  
  
  legend ->Draw("same");
  legend_1 ->Draw("same");
  
  pad2->cd();
  
  h2->Draw("");
  
  
  
  //Fc_to_e_Raa_sts->Draw("samePE");
  
  gr_Fb_to_e_sys->Draw("sameE2");
  Fb_to_e_sts->Draw("samePE");
  gr_Fb_to_e_pp_sys->Draw("p[],same");
  
  //   Fb_to_e_sts->Print("all");
  
  //   l1->Draw("same");
  c3->SaveAs("B_Raa_run14.pdf");
  //=================================================
  
  TFile *Raa_B_D=new TFile("Raa_B_D.root","RECREATE");
  
  gr_Fb_to_e_Raa_sys->Write();
  Fb_to_e_Raa_sts->Write();
  gr_Fb_to_e_Raa_pp_sys->Write();
  gr_Fc_to_e_Raa_pp_sys->Write();
  Fc_to_e_Raa_sts->Write();
  gr_Fc_to_e_Raa_sys->Write();
  
  gr_Npe_Raa_all_sys->Write();
  Npe_Raa_all_sts->Write();
  
  Fb_to_e_sts->Write();
  gr_Fb_to_e_sys->Write();
  gr_Fb_to_e_pp_sys->Write();
  
  gr_Fb_to_e_pp_sys->SaveAs("Saved_Data/B_D_ratio_pp_sys.C");
  
  Fb_to_e_sts->SaveAs("Saved_Data/B_D_Ratio_sts.C");
  
  gr_Fb_to_e_sys->SaveAs("Saved_Data/B_D_Ratio_AuAu_sys.C");
  
  gr_Fb_to_e_pp_sys->SaveAs("Saved_Data/B_Raa_pp_sys.C");
  gr_Fb_to_e_Raa_sys->SaveAs("Saved_Data/B_Raa_AuAu_sys.C");
  Fb_to_e_Raa_sts->SaveAs("Saved_Data/B_Raa_sts.C");
  gr_Fb_to_e_Raa_pp_sys->SaveAs("Saved_Data/B_Raa_pp_sys.C");
  
  gr_Fc_to_e_Raa_pp_sys->SaveAs("Saved_Data/D_Raa_pp_sys.C");
  Fc_to_e_Raa_sts->SaveAs("Saved_Data/D_Raa_sts.C");
  gr_Fc_to_e_Raa_sys->SaveAs("Saved_Data/D_Raa_AuAu_sys.C");
  
  gr_Npe_Raa_all_sys->SaveAs("Saved_Data/Npe_Raa_sys.C");
  Npe_Raa_all_sts->SaveAs("Saved_Data/Npe_Raa_sts.C");
  
  
  c3->SaveAs("Draw_Raa.C");
  
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

