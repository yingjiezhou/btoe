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
bool Draw_noXerror=true;
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
void Draw_B_Raa()

{
  
  char buf[1024];
  //  TH1::SetDefaultSumw2();
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
  TFile *input_B_fraction_pp=new TFile("InPut/run12NPEh_rBPoints.root","READ");
  TFile *file_AuAu_bfraction=new TFile("InPut/run14_AuAu_bfraction.root","READ");
  
  // TFile *input_B_fraction_AA=new TFile("InPut/Fit_B_fraction_MB.root","READ");
  TFile *input_B_fraction_AA=new TFile("InPut/Fit_B_fraction_MB_default.root","READ");
  TFile *input_B_fraction_AA_sys=new TFile("InPut/B_fraction_sys.root","READ");
  TFile *input_B_D_model=new TFile("InPut/B_D_Raa.root","READ");
  
  
  
  TH1F *Npe_Raa_all_sts=(TH1F *) input_Total_Raa->Get("NPERaaStat_AuAu_0")->Clone("Npe_Raa_all_sts");
  TH1F *Npe_Raa_all_sys=(TH1F *) input_Total_Raa->Get("NPERaaSys_AuAu_0")->Clone("Npe_Raa_all_sys");
  
  TH1F *B_fraction_AA=(TH1F *) file_AuAu_bfraction->Get("run14_bF_sts")->Clone("B_fraction_AA");
  TH1F *B_fraction_AA_sys=(TH1F *) file_AuAu_bfraction->Get("run14_bF_sts")->Clone("B_Fraction_sys");
  
  TGraph *gr_Be= (TGraph *) input_B_D_model->Get("RAA_e_B");
  TGraph *gr_De= (TGraph *) input_B_D_model->Get("RAA_e_D");
  
  
  
  TH1F *  b_fraction_pp_sts=new TH1F("b_fraction_pp_sts","",Npt,ptbin);
  TH1F *  b_fraction_pp_sys=new TH1F("b_fraction_pp_sys","",Npt,ptbin);
  
  TH1F *  b_fraction_pp_sys_low=new TH1F("b_fraction_pp_sys_low","",Npt,ptbin);
  TH1F *  b_fraction_pp_sys_high=new TH1F("b_fraction_pp_high","",Npt,ptbin);
  
  
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
  
  TH1F * Fb_to_e_Raa_sts;// zyj
  
  // TH1F *  Fb_to_c_Rati_sts=new TH1F("Fb_to_e_sts","",Npt,ptbin);
  
  
  TH1F *  Fb_to_e_Raa_sys=new TH1F("Fb_to_Raa_e_sys","",Npt,ptbin);
  TH1F *  Fc_to_e_Raa_sts=new TH1F("Fc_to_e_Raa_sts","",Npt,ptbin);
  TH1F *  Fc_to_e_Raa_sys=new TH1F("Fc_to_e_Raa_sys","",Npt,ptbin);
  TH1F *  Fb_to_e_sys=new TH1F("Fb_to_e_sys","",Npt,ptbin);
  
  TH1F *  Fc_to_e_Raa_pp_sys=new TH1F("Fc_to_e_Raa_pp_sys","",Npt,ptbin);
  TH1F *  Fb_to_e_pp_sys=new TH1F("Fb_to_e_pp_sys","",Npt,ptbin);
  TH1F *  Fb_to_e_Raa_pp_sys=new TH1F("Fb_to_Raa_e_pp_sys","",Npt,ptbin);
  
  // TH1F *  Fc_to_e_Raa_pp_sys=new TH1F("Fc_to_e_Raa_pp_sys","",Npt,ptbin);
  // TH1F *  Fb_to_e_sys=new TH1F("Fb_to_e_sys","",Npt,ptbin);
  // TH1F *  Fc_to_e_sys=new TH1F("Fc_to_e_sys","",Npt,ptbin);
  
  
  
  
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
  
  
  //Get pp result from run06;
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
  b_fraction_pp_sys_low->SetBinError(1,0.030117);
  b_fraction_pp_sys_high->SetBinError(1,0.023400);
  
  
  b_fraction_pp_sys->SetBinContent(2,0.418603);
  b_fraction_pp_sys->SetBinError(2,0.032119);
  b_fraction_pp_sys_low->SetBinError(2,0.032119);
  b_fraction_pp_sys_high->SetBinError(2,0.054527);
  
  b_fraction_pp_sys->SetBinContent(3,0.484639);
  b_fraction_pp_sys->SetBinError(3,0.074831);
  b_fraction_pp_sys_low->SetBinError(3,0.074831);
  b_fraction_pp_sys_high->SetBinError(3,0.103169);
  
  b_fraction_pp_sys->SetBinContent(4,0.522393);
  b_fraction_pp_sys->SetBinError(4,0.060432);
  b_fraction_pp_sys_low->SetBinError(1,0.060432);
  b_fraction_pp_sys_high->SetBinError(1,0.029751);
  
  
  
  //Get AuAu  Raa result from run06;
  Npe_AuAuRaa_sts->SetBinContent(1,Npe_Raa_all_sts->GetBinContent(1));
  Npe_AuAuRaa_sts->SetBinError(1,Npe_Raa_all_sts->GetBinError(1));
  
  Npe_AuAuRaa_sts->SetBinContent(2,Npe_Raa_all_sts->GetBinContent(2));
  Npe_AuAuRaa_sts->SetBinError(2,Npe_Raa_all_sts->GetBinError(2));
  
  Npe_AuAuRaa_sts->SetBinContent(3,Npe_Raa_all_sts->GetBinContent(3));
  Npe_AuAuRaa_sts->SetBinError(3,Npe_Raa_all_sts->GetBinError(3));
  
  Npe_AuAuRaa_sts->SetBinContent(4,Npe_Raa_all_sts->GetBinContent(4));
  Npe_AuAuRaa_sts->SetBinError(4,Npe_Raa_all_sts->GetBinError(4));
  
  //Get b fraction in AuAu   result from run14;
  b_fraction_AuAu_sts->SetBinContent(1,B_fraction_AA->GetBinContent(5));
  b_fraction_AuAu_sts->SetBinError(1,B_fraction_AA->GetBinError(5));
  
  b_fraction_AuAu_sts->SetBinContent(2,B_fraction_AA->GetBinContent(6));
  b_fraction_AuAu_sts->SetBinError(2,B_fraction_AA->GetBinError(6));
  
  b_fraction_AuAu_sts->SetBinContent(3,B_fraction_AA->GetBinContent(7));
  b_fraction_AuAu_sts->SetBinError(3,B_fraction_AA->GetBinError(7));
  
  b_fraction_AuAu_sts->SetBinContent(4,B_fraction_AA->GetBinContent(8));
  b_fraction_AuAu_sts->SetBinError(4,B_fraction_AA->GetBinError(8));
  
  //
  one_sts->SetBinContent(1,1);
  one_sts->SetBinError(1,0);
  
  one_sts->SetBinContent(2,1);
  one_sts->SetBinError(2,0);
  
  one_sts->SetBinContent(3,1);
  one_sts->SetBinError(3,0);
  
  one_sts->SetBinContent(4,1);
  one_sts->SetBinError(4,0);
  
  
  
  
  
  b_fraction_pp_sts->SetMarkerColor(2);
  b_fraction_pp_sts->SetMarkerStyle(20);
  b_fraction_pp_sts->SetLineColor(2);
  
  Npe_AuAuRaa_sts->SetMarkerColor(3);
  Npe_AuAuRaa_sts->SetMarkerStyle(20);
  Npe_AuAuRaa_sts->SetLineColor(3);
  
  b_fraction_AuAu_sts->SetMarkerColor(4);
  b_fraction_AuAu_sts->SetMarkerStyle(20);
  b_fraction_AuAu_sts->SetLineColor(4);
  
  
  
  TGraphAsymmErrors *pp_sts=  (TGraphAsymmErrors *) input_B_fraction_pp->Get("StatError_Run6");
  TGraphAsymmErrors *pp_sys=  (TGraphAsymmErrors *) input_B_fraction_pp->Get("systError_Run6");
  
  
  TCanvas *c2=new TCanvas("c2","",1000,1200);
  c2->cd();
  pp_sts->GetYaxis()->SetRangeUser(0,1);
  pp_sts->Draw("");
  b_fraction_pp_sts->Draw("samePE");
  Npe_AuAuRaa_sts->Draw("samePE");
  b_fraction_AuAu_sts->Draw("samePE");
  
  c2->SaveAs("check.pdf");
  
  
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
  
  Fb_to_e_sts->Divide(Fc_to_e_AA_sts);
  
  Fb_to_e_sts->SetMarkerStyle(20);
  Fb_to_e_sts->SetMarkerColor(4);
  Fb_to_e_sts->SetLineColor(4);
  
  Fb_to_e_Raa_sts->SetMarkerStyle(20);
  Fb_to_e_Raa_sts->SetMarkerColor(1);
  Fb_to_e_Raa_sts->SetLineColor(1);
  
  
  
  TH2F *h1=new TH2F("h1","",100,0,10,100,0.01,2);
  TH2F *h2=new TH2F("h2","",100,0,10,2,0.,5);
  
  
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
  
  h2->GetYaxis()->SetNdivisions(4);
  h1->GetYaxis()->SetNdivisions(6);
  
  
  //   h1->GetYaxis()->SetRangeUser(0.01,2.6);
  h1->GetXaxis()->SetTitle("p_{T}^{e} (GeV/c)");
  h1->GetYaxis()->SetTitle("R_{AA}");
  
  
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->CenterTitle();
  
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetTitleSize(0.08);
  
  h1->GetXaxis()->SetTitleOffset(1);
  h1->GetYaxis()->SetTitleOffset(0.6);
  h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetLabelSize(0.04);
  
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
  
  
  // cout<< " @@ "<<Fb_to_e_sts->GetBinError(1);
  // gr_Npe_Raa_all_sts->SetMarkerStyle(21);
  // gr_Npe_Raa_all_sts->SetMarkerSize(1.5);
  // gr_Npe_Raa_all_sts->SetLineWidth(1.8);
  
  
  
  for(Int_t ipt=0;ipt<4;ipt++)
  {
    
    cout<< "ipt ="<< ipt+1<<endl;
    //cou<<" Bf pp="<< b_fraction_pp_sts->GetBinContent(ipt+1)<<"Bf AuAu= "<<B_fraction_AA->GetBinContent(ipt+5)<< " AuAu all"<<Npe_Raa_all_sts->GetBinContent(ipt+1)<<endl;
    cout<< " central "<< "Bf AuAu"<<B_fraction_AA->GetBinContent(ipt+5)<<" Bf pp "<<b_fraction_pp_sts->GetBinContent(ipt+1)<< " AuAu Npe all "<< Npe_Raa_all_sts->GetBinContent(ipt+1) <<endl;
    cout<< " sts Err "<< "Bf AuAu"<<B_fraction_AA->GetBinError(ipt+5)<<" Bf pp "<<b_fraction_pp_sts->GetBinError(ipt+1)<< " AuAu Npe all "<< Npe_Raa_all_sts->GetBinError(ipt+1)<<endl;
    cout<< " sys Err "<< "Bf AuAu"<<B_fraction_AA_sys->GetBinError(ipt+5)<<" Bf pp "<<b_fraction_pp_sys->GetBinError(ipt+1)<< " AuAu Npe all "<< Npe_Raa_all_sys->GetBinError(ipt+1)<<endl;
    
    
    
    // cout<<ipt << " RAA b "<< (B_fraction_AA->GetBinContent(ipt+5))/(b_fraction_pp_sts->GetBinContent(ipt+1))*Npe_Raa_all_sts->GetBinContent(ipt+1)<<" ";
    // cout<< " hist "<<Fb_to_e_Raa_sts->GetBinContent(ipt+1)<<endl;
    // cout<< " sts<<"<<Fb_to_e_Raa_sts->GetBinError(ipt+1)<< " "<<Fb_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA->GetBinError(ipt+5)/B_fraction_AA->GetBinContent(ipt+5),2)+TMath::Power(b_fraction_pp_sts->GetBinError(ipt+1)/b_fraction_pp_sts->GetBinContent(ipt+1),2)+TMath::Power(Npe_Raa_all_sts->GetBinError(ipt+1)/Npe_Raa_all_sts->GetBinContent(ipt+1),2)) <<endl;;
    
    // cout<<ipt <<" RAA c "<< Fc_to_e_Raa_sts->GetBinContent(ipt+1)<<"  "<<(1-B_fraction_AA->GetBinContent(ipt+5))/(1-b_fraction_pp_sts->GetBinContent(ipt+1))*Npe_Raa_all_sts->GetBinContent(ipt+1)<<" "<<endl;
    
    // cout<<ipt <<" Ratio "<< Fb_to_e_sts->GetBinContent(ipt+1)<<"  "<<
    //   (B_fraction_AA->GetBinContent(ipt+5)/b_fraction_pp_sts->GetBinContent(ipt+1))/((1-B_fraction_AA->GetBinContent(ipt+5))/(1-b_fraction_pp_sts->GetBinContent(ipt+1)))<<" "<<endl;
    // //Fb_to_e_sts
    // //cout<< " hist c "<<Fc_to_e_Raa_sts->GetBinContent(ipt+1)<<endl;
    
    // cout<< " sts<< ratio "<<Fb_to_e_sts->GetBinError(ipt+1)<< " "<<Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA->GetBinError(ipt+5)/B_fraction_AA->GetBinContent(ipt+5),2)+TMath::Power(b_fraction_pp_sts->GetBinError(ipt+1)/b_fraction_pp_sts->GetBinContent(ipt+1),2)) <<endl;;
    
    
    Fb_to_e_Raa_sys->SetBinContent(ipt+1,Fb_to_e_Raa_sts->GetBinContent(ipt+1));
    Fc_to_e_Raa_sys->SetBinContent(ipt+1,Fc_to_e_Raa_sts->GetBinContent(ipt+1));
    
    //float Fb_to_e_Raa_sys_err=Fb_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA_sys->GetBinError(ipt+5)/B_fraction_AA_sys->GetBinContent(ipt+5),2)+TMath::Power(Npe_Raa_all_sys->GetBinError(ipt+1)/Npe_Raa_all_sys->GetBinContent(ipt+1),2));// +TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    float Fb_to_e_Raa_sys_err=Fb_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA_sys->GetBinError(ipt+5)/B_fraction_AA_sys->GetBinContent(ipt+5),2)+TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));// +TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    float Fb_to_e_Raa_sts_err=Fb_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA->GetBinError(ipt+5)/B_fraction_AA->GetBinContent(ipt+5),2)+TMath::Power(b_fraction_pp_sts->GetBinError(ipt+1)/b_fraction_pp_sts->GetBinContent(ipt+1),2));// +TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    float Fb_to_e_Raa_AA=Fb_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(Npe_Raa_all_sts->GetBinError(ipt+1)/Npe_Raa_all_sts->GetBinContent(ipt+1),2)+TMath::Power(Npe_Raa_all_sys->GetBinError(ipt+1)/Npe_Raa_all_sys->GetBinContent(ipt+1),2));// +TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    //
    float Fc_to_e_Raa_sys_err=Fc_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA_sys->GetBinError(ipt+5)/(1-B_fraction_AA_sys->GetBinContent(ipt+5)),2)+TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/(1-b_fraction_pp_sys->GetBinContent(ipt+1)),2));// +TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    float Fc_to_e_Raa_sts_err=Fc_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA->GetBinError(ipt+5)/(1-B_fraction_AA->GetBinContent(ipt+5)),2)+TMath::Power(b_fraction_pp_sts->GetBinError(ipt+1)/(1-b_fraction_pp_sts->GetBinContent(ipt+1)),2));// +TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    float Fc_to_e_Raa_AA=Fc_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(Npe_Raa_all_sts->GetBinError(ipt+1)/Npe_Raa_all_sts->GetBinContent(ipt+1),2)+TMath::Power(Npe_Raa_all_sys->GetBinError(ipt+1)/Npe_Raa_all_sys->GetBinContent(ipt+1),2));// +TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    
    cout<< "WWWWW"<< Fb_to_e_Raa_sts_err<<" "<<Fb_to_e_Raa_sys_err<<" "<<Fb_to_e_Raa_AA<< " "<<endl;
    cout<< "WWWWW"<< Fc_to_e_Raa_sts_err<<" "<<Fc_to_e_Raa_sys_err<<" "<<Fc_to_e_Raa_AA<< " "<<endl;
    
    //float Fc_to_e_Raa_sys_err=Fc_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA_sys->GetBinError(ipt+5)/B_fraction_AA_sys->GetBinContent(ipt+5),2)+TMath::Power(Npe_Raa_all_sys->GetBinError(ipt+1)/Npe_Raa_all_sys->GetBinContent(ipt+1),2));//+TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    //float Fb_to_e_sys_err=Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA_sys->GetBinError(ipt+5)/B_fraction_AA_sys->GetBinContent(ipt+5),2));
    
    // float Fb_to_e_sts_err=Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA->GetBinError(ipt+5)/(1-B_fraction_AA->GetBinContent(ipt+5)),2)
    //                    +TMath::Power(B_fraction_AA->GetBinError(ipt+5)/B_fraction_AA->GetBinContent(ipt+5),2)
    //                    +TMath::Power(b_fraction_pp_sts->GetBinError(ipt+1)/b_fraction_pp_sts->GetBinContent(ipt+1),2)
    //                    +TMath::Power(b_fraction_pp_sts->GetBinError(ipt+1)/(1-b_fraction_pp_sts->GetBinContent(ipt+1)),2));
    
    float Fb_to_e_sts_err=Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA->GetBinError(ipt+5)/(B_fraction_AA->GetBinContent(ipt+5)*(1-B_fraction_AA->GetBinContent(ipt+5))),2)+TMath::Power(b_fraction_pp_sts->GetBinError(ipt+1)/(b_fraction_pp_sts->GetBinContent(ipt+1)*(1-b_fraction_pp_sts->GetBinContent(ipt+1))),2));
    float Fb_to_e_sys_err=Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(B_fraction_AA_sys->GetBinError(ipt+5)/(B_fraction_AA_sys->GetBinContent(ipt+5)*(1-B_fraction_AA_sys->GetBinContent(ipt+5))),2)+TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/(b_fraction_pp_sys->GetBinContent(ipt+1)*(1-b_fraction_pp_sys->GetBinContent(ipt+1))),2));
    float Fb_to_e_pp_sys_err=Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/(b_fraction_pp_sys->GetBinContent(ipt+1)*(1-b_fraction_pp_sys->GetBinContent(ipt+1))),2));
    
    Fb_to_e_sts->SetBinError(ipt+1,Fb_to_e_sts_err);
    
    cout<< "!!!!!!!"<<Fb_to_e_sts_err<<endl;
    
    float Fb_to_e_Raa_pp_sys_err=Fb_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    float Fc_to_e_Raa_pp_sys_err=Fc_to_e_Raa_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/(1-b_fraction_pp_sys->GetBinContent(ipt+1)),2));
    
    //float Fb_to_e_pp_sys_err=Fb_to_e_sts->GetBinContent(ipt+1)*sqrt(TMath::Power(b_fraction_pp_sys->GetBinError(ipt+1)/b_fraction_pp_sys->GetBinContent(ipt+1),2));
    
    
    Fb_to_e_Raa_sys->SetBinError(ipt+1,Fb_to_e_Raa_sys_err);
    Fc_to_e_Raa_sys->SetBinError(ipt+1,Fc_to_e_Raa_sys_err);
    
    
    Fb_to_e_sys->SetBinContent(ipt+1,Fb_to_e_sts->GetBinContent(ipt+1));
    Fb_to_e_sys->SetBinError(ipt+1,Fb_to_e_sys_err);
    
    Fc_to_e_Raa_pp_sys->SetBinContent(ipt+1,Fc_to_e_Raa_sts->GetBinContent(ipt+1));
    Fb_to_e_pp_sys->SetBinContent(ipt+1,Fb_to_e_sts->GetBinContent(ipt+1));
    Fb_to_e_Raa_pp_sys->SetBinContent(ipt+1,Fb_to_e_Raa_sts->GetBinContent(ipt+1));
    
    Fc_to_e_Raa_pp_sys->SetBinError(ipt+1,Fc_to_e_Raa_pp_sys_err);
    Fb_to_e_pp_sys->SetBinError(ipt+1,Fb_to_e_pp_sys_err);
    Fb_to_e_Raa_pp_sys->SetBinError(ipt+1,Fb_to_e_pp_sys_err);
    
    
    
    
    Fb_to_e_Raa_sts->SetBinError(ipt+1,Fb_to_e_Raa_sts_err);
    Fb_to_e_Raa_sys->SetBinError(ipt+1,Fb_to_e_Raa_sys_err);
    Fb_to_e_Raa_pp_sys->SetBinError(ipt+1,Fb_to_e_Raa_AA);
    
    Fc_to_e_Raa_sts->SetBinError(ipt+1,Fc_to_e_Raa_sts_err);
    Fc_to_e_Raa_sys->SetBinError(ipt+1,Fc_to_e_Raa_sys_err);
    Fc_to_e_Raa_pp_sys->SetBinError(ipt+1,Fc_to_e_Raa_AA);
    
    
    
    
    
    
    cout<< " from my calculation"<<endl;
    cout<< " D Raa ="<< Fc_to_e_Raa_sts->GetBinContent(ipt+1)<< " sts. err "<<Fc_to_e_Raa_sts->GetBinError(ipt+1)<< " sys. err. from AuAu"<<Fc_to_e_Raa_sys->GetBinContent(ipt+1)<< " sys. err from pp "<<Fc_to_e_Raa_pp_sys->GetBinError(ipt+1) <<endl;
    cout<< " B Raa ="<< Fb_to_e_Raa_sts->GetBinContent(ipt+1)<< " sts. err "<<Fb_to_e_Raa_sts->GetBinError(ipt+1)<< " sys. err."<<Fb_to_e_Raa_sys->GetBinError(ipt+1)<< " sys. err from pp "<<Fb_to_e_Raa_pp_sys->GetBinError(ipt+1) <<endl;
    cout<< " B/D ratio ="<< Fb_to_e_sts->GetBinContent(ipt+1)<< " sts. err "<<Fb_to_e_sts->GetBinError(ipt+1)<< " sys. err."<<Fb_to_e_sys->GetBinError(ipt+1)<< " sys. err from pp "<<Fb_to_e_pp_sys->GetBinError(ipt+1) <<endl;
    
  }
  
  TGraphErrors * gr_Fb_to_e_Raa_sys= new TGraphErrors(Fb_to_e_Raa_sys);
  TGraphErrors * gr_Fc_to_e_Raa_sys= new TGraphErrors(Fc_to_e_Raa_sys);
  TGraphErrors * gr_Fb_to_e_sys= new TGraphErrors(Fb_to_e_sys);
  TGraphErrors   *gr_Fb_to_e_sts=new TGraphErrors(Fb_to_e_sts);
  
  TGraphErrors * gr_Fb_to_e_Raa_pp_sys= new TGraphErrors(Fb_to_e_Raa_pp_sys);
  TGraphErrors * gr_Fc_to_e_Raa_pp_sys= new TGraphErrors(Fc_to_e_Raa_pp_sys);
  TGraphErrors * gr_Fb_to_e_pp_sys= new TGraphErrors(Fb_to_e_pp_sys);
  
  TGraphErrors *   gr_Fb_to_e_Raa_sts=new TGraphErrors(Fb_to_e_Raa_sts);
  TGraphErrors *   gr_Fc_to_e_Raa_sts=new TGraphErrors(Fc_to_e_Raa_sts);
  
  
  
  
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
    
    
    //
    if(Draw_noXerror)
    {
      gr_Fc_to_e_Raa_sys->SetPointError(ipoint,0., gr_Fc_to_e_Raa_sys->GetErrorY(ipoint));
      gr_Fc_to_e_Raa_sts->SetPointError(ipoint,0., gr_Fc_to_e_Raa_sts->GetErrorY(ipoint));
      
      gr_Fc_to_e_Raa_pp_sys->SetPointError(ipoint,0.0, gr_Fc_to_e_Raa_pp_sys->GetErrorY(ipoint));
      
      gr_Npe_Raa_all_sys->SetPointError(ipoint,0., gr_Npe_Raa_all_sys->GetErrorY(ipoint));
      
      gr_Fb_to_e_sys->SetPointError(ipoint,0., gr_Fb_to_e_sys->GetErrorY(ipoint));
      gr_Fb_to_e_sts->SetPointError(ipoint,0., gr_Fb_to_e_sts->GetErrorY(ipoint));
      
      gr_Fb_to_e_pp_sys->SetPointError(ipoint,0.0, gr_Fb_to_e_pp_sys->GetErrorY(ipoint));
      
      gr_Fb_to_e_Raa_pp_sys->SetPointError(ipoint,0.0, gr_Fb_to_e_Raa_pp_sys->GetErrorY(ipoint));
      gr_Fb_to_e_Raa_sys->SetPointError(ipoint,0., gr_Fb_to_e_Raa_sys->GetErrorY(ipoint));
      
      gr_Fb_to_e_Raa_pp_sys->SetPointError(ipoint,0.0, gr_Fb_to_e_Raa_pp_sys->GetErrorY(ipoint));
      gr_Fb_to_e_Raa_sys->SetPointError(ipoint,0., gr_Fb_to_e_Raa_sys->GetErrorY(ipoint));
      
      
      
    }
    
    Double_t bX=-99;Double_t bY=-99;
    
    gr_Fb_to_e_Raa_pp_sys->GetPoint(ipoint,bX,bY);
    gr_Fb_to_e_Raa_pp_sys->SetPoint(ipoint,bX+0.05,bY);
    gr_Fb_to_e_Raa_sys->SetPoint(ipoint,bX+0.05, bY);
    
    gr_Fb_to_e_Raa_sts->SetPoint(ipoint,bX+0.05, bY);
    gr_Fb_to_e_Raa_pp_sys->SetPointError(ipoint,0.,gr_Fb_to_e_Raa_pp_sys->GetErrorY(ipoint));
    gr_Fb_to_e_Raa_sys->SetPointError(ipoint,0.1, gr_Fb_to_e_Raa_sys->GetErrorY(ipoint));
    if(Draw_noXerror){
      gr_Fb_to_e_Raa_sys->SetPointError(ipoint,0, gr_Fb_to_e_Raa_sys->GetErrorY(ipoint));
      gr_Fb_to_e_Raa_sts->SetPointError(ipoint,0, gr_Fb_to_e_Raa_sts->GetErrorY(ipoint));
    }
    
    
  }
  
  gr_Fb_to_e_Raa_sys->SetFillStyle(1001);
  gr_Fb_to_e_Raa_sys->SetFillColor(42);
  gr_Fb_to_e_Raa_sys->SetLineColor(42);
  
  gr_Fc_to_e_Raa_sys->SetFillStyle(1001);
  gr_Fc_to_e_Raa_sys->SetFillColor(33);
  gr_Fc_to_e_Raa_sys->SetLineColor(33);
  
  
  Npe_Raa_all_sts->SetMarkerStyle(20);
  Npe_Raa_all_sts->SetLineColor(6);
  Npe_Raa_all_sts->SetMarkerColor(6);
  Npe_Raa_all_sts->SetMarkerSize(1.5);
  
  
  gr_Npe_Raa_all_sys->SetFillStyle(1001);
  gr_Npe_Raa_all_sys->SetFillColor(41);
  gr_Npe_Raa_all_sys->SetLineColor(41);
  
  gr_Fb_to_e_sys->SetFillStyle(1001);
  gr_Fb_to_e_sys->SetFillColor(39);
  gr_Fb_to_e_sys->SetLineColor(39);
  
  
  gr_Fb_to_e_Raa_pp_sys->SetLineColor(2);
  gr_Fb_to_e_Raa_pp_sys->SetMarkerStyle(20);
  gr_Fb_to_e_Raa_pp_sys->SetMarkerColor(2);
  
  
  gr_Fc_to_e_Raa_pp_sys->SetLineColor(4);
  gr_Fb_to_e_pp_sys->SetLineColor(1);
  
  gr_Fb_to_e_Raa_sts->SetLineColor(2);
  gr_Fb_to_e_Raa_sts->SetMarkerColor(2);
  gr_Fb_to_e_Raa_sts->SetMarkerStyle(20);
  
  gr_Fc_to_e_Raa_sts->SetLineColor(4);
  gr_Fc_to_e_Raa_sts->SetMarkerColor(4);
  gr_Fc_to_e_Raa_sts->SetMarkerStyle(20);
  
  gr_Fb_to_e_sts->SetLineColor(1);
  gr_Fb_to_e_sts->SetMarkerColor(1);
  gr_Fb_to_e_sts->SetMarkerStyle(20);
  
  
  TGraphErrors *  gr_duke_B=new TGraphErrors("InPut/eForSTAR_0_80/RAA_Be.dat","%lg %lg");
  TGraphErrors *  gr_duke_D=new TGraphErrors("InPut/eForSTAR_0_80/RAA_De.dat","%lg %lg");
  
  //   TGraphErrors *  gr_duke_B=new TGraphErrors("NPECrossSectionStatSys.dat","%lg %lg %*lg %lg");
  
  gr_duke_D->SetLineColor(4);
  gr_duke_D->SetLineStyle(7);
  gr_duke_D->SetLineWidth(4);
  
  gr_duke_B->SetLineColor(2);
  gr_duke_B->SetLineStyle(7);
  gr_duke_B->SetLineWidth(4);
  
  
  // gr_Fb_to_e_Raa_pp_sys->SetLineWidth(2);
  // gr_Fc_to_e_Raa_pp_sys->SetLineWidth(2);
  // gr_Fb_to_e_pp_sys->SetLineWidth(2);
  
  //   gr_Fc_to_e_Raa_sys->SetPointError(ipoint,0.03, gr_Fc_to_e_Raa_sys->GetErrorY(ipoint));
  
  
  // gr_B_fraction_sys->SetFillStyle(1001);
  // gr_B_fraction_sys->SetFillColor(40);
  // gr_B_fraction_sys->SetLineColor(40);
  // gr_B_fraction_sys->SetLineWidth(2);
  
  // gr_Fb_to_e_Raa_sys->SetPointError(ipoint,0.03, gr_Fb_to_e_Raa_sys->GetErrorY(ipoint));
  // gr_Fc_to_e_Raa_sys->SetPointError(ipoint,0.03, gr_Fc_to_e_Raa_sys->GetErrorY(ipoint));
  
  
  // Fb_to_e_Raa_sys->SetBinError(ipt+1,Fb_to_e_Raa_sys_err);
  // Fc_to_e_Raa_sys->SetBinError(ipt+1,Fc_to_e_Raa_sys_err);
  
  
  
  
  TLegend *legend  = new TLegend(0.65,0.65,0.76,0.95);
  legend ->AddEntry(gr_Fb_to_e_Raa_sts,"B #rightarrow e","p");
  legend ->AddEntry(gr_Fc_to_e_Raa_sts,"D #rightarrow e","p");
  //   legend ->AddEntry(Npe_Raa_all_sts,"(D+B) #rightarrow e","p");
  legend ->AddEntry(gr_duke_B,"B #rightarrow e Duke Model","l");
  legend ->AddEntry(gr_duke_D,"D #rightarrow e Duke Model","l");
  // legend ->AddEntry(PhNEX_sts,"PHENIX","lp");
  // legend ->AddEntry(gFONLLc,"FONLL","lp");
  // legend ->AddEntry(gFONLLl,"FONLL Uncertainty","lp");
  
  legend ->SetBorderSize(0);
  legend ->SetTextSize(0.04);
  legend ->SetFillStyle(0);
  legend->SetTextFont(62);
  
  TLine *l1=new TLine(0,1,10,1);
  l1->SetLineColor(1);
  l1->SetLineWidth(2.5);
  l1->SetLineStyle(7);
  
  TCanvas *c3=new TCanvas("c3","",800,800);
  
  c3->cd();
  TPad* pad1 = new TPad("pad1","pad1",0.00,0.3,1.00,1.00);pad1->Draw();
  TPad* pad2 = new TPad("pad2","pad2",0.00,0.00,1.00,0.3);pad2->Draw();
  pad1->SetMargin(0.13,0.02,0,0.02);
  pad2->SetMargin(0.13,0.02,0.3,0.0);
  
  pad1->cd();
  gPad->SetLogy(0);
  h1->Draw();
  
  gr_duke_D->Draw("samec");
  gr_duke_B->Draw("samec");
  
  gr_Fb_to_e_Raa_sys->Draw("sameE2");
  gr_Fc_to_e_Raa_sys->Draw("sameE2");
  gr_Fb_to_e_Raa_pp_sys->Draw("p[]:same");
  gr_Fc_to_e_Raa_pp_sys->Draw("p[]:same");
  gr_Fc_to_e_Raa_sts->Draw("samePE");
  gr_Fb_to_e_Raa_sts->Draw("samePE");
  
  gr_Fb_to_e_Raa_sys->SetName("gr_B_Raa_com_sys");
  gr_Fc_to_e_Raa_sys->SetName("gr_C_Raa_com_sys");
  gr_Fb_to_e_Raa_pp_sys->SetName("gr_all_B_Npe_Raa_com_sys");
  gr_Fc_to_e_Raa_pp_sys->SetName("gr_all_C_Npe_Raa_com_sys");
  gr_Fc_to_e_Raa_sts->SetName("gr_C_Raa_com_sts");
  gr_Fb_to_e_Raa_sts->SetName("gr_B_Raa_com_sts");
  
  
  
  l1->Draw("same");
  
  sprintf(buf,"STAR Au+Au200 GeV");
  drawLatex(0.18,0.82,buf,62,0.05,1);
  
  sprintf(buf,"0-80 %  |y|<0.7");
  drawLatex(0.18,0.75,"0-80% |y|<0.7",62,0.05,1);
  
  sprintf(buf,"STAR Preliminary");
  //  drawLatex(0.18,0.9,buf,62,0.06,2);
  
  
  legend ->Draw("same");
  
  //-----------------
  float x1 =9.5; // pt_low;
  float x2 =10;// pt_high;
  
  float y1 =1.1; // pt_low;
  float y2 =0.9;// pt_high;
  
  TBox* box=new TBox;
  box->SetX1(x1);
  box->SetX2(x2);
  box->SetY1(y1);
  box->SetY2(y2);
  box->SetFillColor(38);
  box->SetLineColor(38);
  box->SetLineWidth(2);
  box->SetLineStyle(3);
  box->SetFillStyle(1001);
  box->Draw("same");
  //-----------------
  
  pad2->cd();
  
  h2->Draw("");
  
  
  
  //Fc_to_e_Raa_sts->Draw("samePE");
  
  gr_Fb_to_e_sys->Draw("sameE2");
  gr_Fb_to_e_sts->Draw("samePE");
  //   gr_Fb_to_e_sts->Fit("pol0");
  
  //   gr_Fb_to_e_pp_sys->Draw("p[],same");
  
  //   Fb_to_e_sts->Print("all");
  
  //   l1->Draw("same");
  c3->SaveAs("B_Raa_run14.pdf");
  
  c3->cd(0);
  
  
  TFile *Raa_B_D=new TFile("Raa_B_D.root","RECREATE");
  
  gr_Fb_to_e_Raa_sys->Write();
  gr_Fc_to_e_Raa_sys->Write();
  gr_Fb_to_e_Raa_pp_sys->Write();
  gr_Fc_to_e_Raa_pp_sys->Write();
  gr_Fc_to_e_Raa_sts->Write();
  gr_Fb_to_e_Raa_sts->Write();
  
  gr_Fb_to_e_sys->Write();
  gr_Fb_to_e_sts->Write();
  
  // gr_Fb_to_e_Raa_sys->Write();
  // Fb_to_e_Raa_sts->Write();
  // gr_Fb_to_e_Raa_pp_sys->Write();
  // gr_Fc_to_e_Raa_pp_sys->Write();
  // Fc_to_e_Raa_sts->Write();
  // gr_Fc_to_e_Raa_sys->Write();
  
  // gr_Npe_Raa_all_sys->Write();
  // Npe_Raa_all_sts->Write();
  
  
  
  
  
  
  // Fb_to_e_sts->Write();
  // gr_Fb_to_e_sys->Write();
  // gr_Fb_to_e_pp_sys->Write();
  
  
  
  // c3->SaveAs("Draw_Raa_xiaozhi.pdf");
  // c3->SaveAs("Draw_Raa_xiaozhi.png");
  // c3->SaveAs("Draw_Raa_xiaozhi.gif");
  
  
  return ;
  
}

/*
 
 
 TGraphErrors *  gr_B_fraction_MB=new TGraphErrors(B_fraction_MB);
 TGraphErrors *  gr_B_fraction_HT=new TGraphErrors(B_fraction_HT);
 
 TFile *input_PHENIX=new TFile("InPut/PHENIX.root","READ");
 TGraphAsymmErrors *gr_B_fraction_PHENIX=(TGraphAsymmErrors *) input_PHENIX->Get("Graph");
 
 
 
 cout<< gr_B_fraction_MB->GetN()<<endl;
 cout<< gr_B_fraction_HT->GetN()<<endl;
 
 for(Int_t ipoint=0;ipoint<gr_B_fraction_MB->GetN();ipoint++)
 {
 gr_B_fraction_MB->SetPointError(ipoint,0, gr_B_fraction_MB->GetErrorY(ipoint));
 
 continue;
 if(ipoint==gr_B_fraction_MB->GetN())
 {
 gr_B_fraction_MB->SetPointError(ipoint,0, 0);
 gr_B_fraction_MB->SetPoint(ipoint,-999, -999);
 }
 
 }
 
 for(Int_t ipoint=0;ipoint<gr_B_fraction_HT->GetN();ipoint++)
 {
 gr_B_fraction_HT->SetPointError(ipoint,0, gr_B_fraction_HT->GetErrorY(ipoint));
 if(ipoint<5)
 {
 gr_B_fraction_HT->SetPointError(ipoint,0, 0);
 gr_B_fraction_HT->SetPoint(ipoint,-999, -999);
 }
 }
 
 gr_B_fraction_MB->SetMarkerStyle(20);
 gr_B_fraction_HT->SetMarkerStyle(21);
 
 gr_B_fraction_MB->SetMarkerColor(4);
 gr_B_fraction_HT->SetMarkerColor(4);
 
 gr_B_fraction_MB->SetMarkerSize(1.6);
 gr_B_fraction_HT->SetMarkerSize(1.6);
 
 gr_B_fraction_MB->SetLineColor(4);
 gr_B_fraction_HT->SetLineColor(4);
 
 
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
 
 
 run12_pp_sts->SetMarkerSize(1.6);
 
 
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
 Ge_D0->SetMarkerSize(1.8);
 
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
 
 
 
 
 TCanvas *c6=new TCanvas("c6","",1000,1200);
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
 
 gr_B_fraction_PHENIX->SetLineWidth(4);
 gr_B_fraction_PHENIX->Draw("3Lsame");
 run12_pp_sts->Draw("samePE");
 run12_pp_sys->Draw("same e2");
 //Ge_D0->SetName("eD0");
 Ge_D0->Draw("sameP");
 Ge_D0_sys->Draw("same e2");
 gr_B_fraction_MB->Draw("sameP");
 //  gr_B_fraction_HT->Draw("sameP");
 FONLL[0]->Draw("same");
 FONLL[1]->Draw("same");
 
 
 TLegend *legend  = new TLegend(0.2,0.5,0.4,0.8);
 legend ->AddEntry(gr_B_fraction_MB,"MinBias run14","lp");
 legend ->AddEntry(gr_B_fraction_HT,"BEMC run14","lp");
 
 legend ->AddEntry(run12_pp_sts,"STAR p+p e-hadron correlation","lp");
 legend ->AddEntry(Ge_D0,"STAR p+p e-D^{0} correlation","lp");
 
 legend ->AddEntry(gr_B_fraction_PHENIX,"PHENIX","l");
 legend ->AddEntry(FONLL[1],"FONLL","l");
 
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
 */

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

