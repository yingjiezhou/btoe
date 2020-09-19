/*--------------------Xiaozhi------------------------------------
 
 Version 1.0
 by xiaozhi
 Tue Jan  3 21:59:02 CST 2017
 
 Version 2.0
 by xiaozhi
 Tue Oct 31 14:39:09 CST 2017
 
 Version 3.0
 by yingjie
 Tue Mar 28 15:28:09 CST 2019
 ---------------------------------------------------------------
 */
#include<fstream>
#include <iostream>
#include "TLatex.h"
#include "TStyle.h"
#include "TH3F.h"
#include "TF1.h"
#include "TMath.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLine.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TNtuple.h"
#include "../Binning_MB.h"

using namespace std;
//Bool_t DCA_Z_flag=true;
const int mh2Nhist=3;
const int mh2Ndca=2;
const int Ntrig=4;
const int Trg=0;

const Double_t DCAMIN=-0.1;
const Double_t DCAMAX=0.1;
Bool_t print_dcaBinning=true;
Bool_t unlike_like_method=false;
Bool_t add_HT_trigger=true;


const Double_t Pi0_BR=0.12; // was changed in the hijing productio
const Double_t Eta_BR=0.068; // was changed in the hijing productio
//-----------------data-----------------------

TH2F *mh2data_HFT_inclusive[mh2Ndca][Ntrig];
TH2F *mh2data_HFT_unlike[mh2Ndca][Ntrig];
TH2F *mh2data_HFT_like[mh2Ndca][Ntrig];

TH1F *mh1data_HFT_inclusive[mh2Ndca][Ntrig][Npt];
TH1F *mh1data_HFT_unlike[mh2Ndca][Ntrig][Npt];
TH1F *mh1data_HFT_like[mh2Ndca][Ntrig][Npt];
TH1F *mh1data_HFT_unlike_like[mh2Ndca][Ntrig][Npt];

TH1F *mh1data_HFT_inclusive_rebin[mh2Ndca][Ntrig][Npt]; //rebin
TH1F *mh1data_HFT_unlike_rebin[mh2Ndca][Ntrig][Npt];
TH1F *mh1data_HFT_like_rebin[mh2Ndca][Ntrig][Npt];
TH1F *mh1data_HFT_unlike_like_rebin[mh2Ndca][Ntrig][Npt];
//-----------------simulation----------------
TH2F *mh2Hijing_pi[mh2Ndca];
TH1F *mh1Hijing_pi_Pt[mh2Ndca][Npt];

TH2F *mh2Hijing_pi0_e[mh2Ndca];
TH2F *mh2Hijing_pi0_e_Same_MC[mh2Ndca];
TH2F *mh2Hijing_pi0_e_unlike[mh2Ndca];
TH2F *mh2Hijing_pi0_e_like[mh2Ndca];

TH1F *mh1Hijing_pi0_e_Pt[mh2Ndca][Npt];
TH1F *mh1Hijing_pi0_e_Pt_same_MC[mh2Ndca][Npt];
TH1F *mh1Hijing_pi0_e_Pt_unlike[mh2Ndca][Npt];
TH1F *mh1Hijing_pi0_e_Pt_like[mh2Ndca][Npt];
TH1F *mh1Hijing_pi0_e_Pt_unlike_like[mh2Ndca][Npt];

TH1F *mh1Hijing_pi0_e_Pt_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_pi0_e_Pt_same_MC_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_pi0_e_Pt_unlike_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_pi0_e_Pt_like_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_pi0_e_Pt_unlike_like_rebin[mh2Ndca][Npt];

// gamma
TH2F *mh2Hijing_gamma_e[mh2Ndca];
TH2F *mh2Hijing_gamma_e_Same_MC[mh2Ndca];
TH2F *mh2Hijing_gamma_e_unlike[mh2Ndca];
TH2F *mh2Hijing_gamma_e_like[mh2Ndca];

TH1F *mh1Hijing_gamma_e_Pt[mh2Ndca][Npt];
TH1F *mh1Hijing_gamma_e_Pt_same_MC[mh2Ndca][Npt];
TH1F *mh1Hijing_gamma_e_Pt_unlike[mh2Ndca][Npt];
TH1F *mh1Hijing_gamma_e_Pt_like[mh2Ndca][Npt];
TH1F *mh1Hijing_gamma_e_Pt_unlike_like[mh2Ndca][Npt];

TH1F *mh1Hijing_gamma_e_Pt_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_gamma_e_Pt_same_MC_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_gamma_e_Pt_unlike_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_gamma_e_Pt_like_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_gamma_e_Pt_unlike_like_rebin[mh2Ndca][Npt];

// eta
TH2F *mh2Hijing_eta_e[mh2Ndca];
TH2F *mh2Hijing_eta_e_Same_MC[mh2Ndca];
TH2F *mh2Hijing_eta_e_unlike[mh2Ndca];
TH2F *mh2Hijing_eta_e_like[mh2Ndca];

TH1F *mh1Hijing_eta_e_Pt[mh2Ndca][Npt];
TH1F *mh1Hijing_eta_e_Pt_same_MC[mh2Ndca][Npt];
TH1F *mh1Hijing_eta_e_Pt_unlike[mh2Ndca][Npt];
TH1F *mh1Hijing_eta_e_Pt_like[mh2Ndca][Npt];
TH1F *mh1Hijing_eta_e_Pt_unlike_like[mh2Ndca][Npt];

TH1F *mh1Hijing_eta_e_Pt_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_eta_e_Pt_same_MC_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_eta_e_Pt_unlike_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_eta_e_Pt_like_rebin[mh2Ndca][Npt];
TH1F *mh1Hijing_eta_e_Pt_unlike_like_rebin[mh2Ndca][Npt];
//=========================================================================================
// string name for MC

TString mh2Name_pi0_HFT_unlike[mh2Ndca]={"DcaXY_pi0_unlike1","DcaZ_pi0_unlike1"};
TString mh2Name_pi0_HFT_like[mh2Ndca]={"DcaXY_pi0_like1","DcaZ_pi0_like1"};

TString mh2Name_eta_HFT_unlike[mh2Ndca]={"DcaXY_eta_unlike1","DcaZ_eta_unlike1"};
TString mh2Name_eta_HFT_like[mh2Ndca]={"DcaXY_eta_like1","DcaZ_eta_like1"};

TString mh2Name_gamma_HFT_unlike[mh2Ndca]={"DcaXY_gamma_unlike1","DcaZ_gamma_unlike1"};
TString mh2Name_gamma_HFT_like[mh2Ndca]={"DcaXY_gamma_like1","DcaZ_gamma_like1"};

TString mh2Name_pi[mh2Ndca]={"mh2piDcaXYVspt1","mh2piDcaZVspt1"};
TString mh2Name_pi0_e[mh2Ndca]={"mh2_pi0_electronDcaXYVspt1","mh2_pi0_electronDcaZVspt1"};
TString mh2Name_gamma_e[mh2Ndca]={"mh2_gamma_electronDcaXYVspt1","mh2_gamma_electronDcaZVspt1"};
TString mh2Name_eta_e[mh2Ndca]={"mh2_eta_electronDcaXYVspt1","mh2_eta_electronDcaZVspt1"};

TString mh2Name_pi0_e_same_MC[mh2Ndca]={"DcaXY_pi01","DcaZ_pi01"};
TString mh2Name_eta_e_same_MC[mh2Ndca]={"DcaXY_eta1","DcaZ_eta1"};
TString mh2Name_gamma_e_same_MC[mh2Ndca]={"DcaXY_gamma1","DcaZ_gamma1"};

//string name for data
TString mh2Name_data_HFT_inclusive_DCAXY[Ntrig]={"mh2dcaXYVsPt_HFT_Trg0","mh2dcaXYVsPt_HFT_Trg1","mh2dcaXYVsPt_HFT_Trg2","mh2dcaXYVsPt_HFT_Trg3"};
TString mh2Name_data_HFT_unlike_DCAXY[Ntrig]={"mh2dcaXYVsPt_HFT_unlikeTrg0","mh2dcaXYVsPt_HFT_unlikeTrg1","mh2dcaXYVsPt_HFT_unlikeTrg2","mh2dcaXYVsPt_HFT_unlikeTrg3"};
TString mh2Name_data_HFT_like_DCAXY[Ntrig]={"mh2dcaXYVsPt_HFT_likeTrg0","mh2dcaXYVsPt_HFT_likeTrg1","mh2dcaXYVsPt_HFT_likeTrg2","mh2dcaXYVsPt_HFT_likeTrg3"};
TString mh2Name_data_HFT_inclusive_DCAZ[Ntrig]={"mh2dcaZVsPt_HFT_Trg0","mh2dcaZVsPt_HFT_Trg1","mh2dcaZVsPt_HFT_Trg2","mh2dcaZVsPt_HFT_Trg3"};
TString mh2Name_data_HFT_unlike_DCAZ[Ntrig]={"mh2dcaZVsPt_HFT_unlikeTrg0","mh2dcaZVsPt_HFT_unlikeTrg1","mh2dcaZVsPt_HFT_unlikeTrg2","mh2dcaZVsPt_HFT_unlikeTrg3"};
TString mh2Name_data_HFT_like_DCAZ[Ntrig]={"mh2dcaZVsPt_HFT_likeTrg0","mh2dcaZVsPt_HFT_likeTrg1","mh2dcaZVsPt_HFT_likeTrg2","mh2dcaZVsPt_HFT_likeTrg3"};

TString Xmh2Title[mh2Nhist]={"p_{T} GeV/c","p_{T} GeV/c","p_{T} GeV/c"};
TString Ymh2Title[mh2Nhist]={"3D dca (cm)","dcaXY (cm)","dcaZ (cm)"};
TString mh2Title[mh2Nhist]={"mcHFT","mc&&rc HFT","mc&&rc&&true HFT"};
//=========================================================================================

char buf[1024];

void SetHistogram_TH1(TH1F *hist_1D,Double_t LineColor,Double_t MarkerStyle,Double_t MarkerColor,char* Title, char* XTitle,char* YTitle);
void SetLegend(TLegend *legend_data,Double_t BorderSize=0,Double_t TextSize=0.04,Double_t FillStyle=0,Double_t TextFont=62);

int Correct_hijing_and_data(){
  
  TH3F:: SetDefaultSumw2();
  TH2F:: SetDefaultSumw2();
  TH1F:: SetDefaultSumw2();
  
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleOffset(1,"X");
  gStyle->SetTitleOffset(1,"Y");
  gStyle->SetPadTopMargin(0.13);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetOptStat(00000);
  //=========================================================================================
  
  TFile * inFile_simu_hijing= new TFile("Input/hijing_20170920.root","READ");
  //TFile * inFile_data_MB= new TFile("Input/hist_mb_20170920.root","READ");
  
  //===zyj====
  TFile * inFile_data_MB= new TFile("Input/AnaTreeNPE_MB.root","READ");
  TFile * inFile_data_HT= new TFile("Input/AnaTreeNPE_HT.root","READ");
  //===zyj====
  
  TFile * inFile_data_phe_relative= new TFile("Phe_relative_combine_1_30.root","READ");
  
  //TFile * outFile_Hijing= new TFile("Photonic_electron_template.root","RECREATE");
  //TFile * outFile_data= new TFile("Data_inclusive_photonic.root","RECREATE");
  TFile * outFile_Hijing= new TFile("Photonic_electron_template_yj_xzbin.root","RECREATE");
  TFile * outFile_data= new TFile("Data_inclusive_photonic_yj_xzbin.root","RECREATE");
  
  // relative contribution
  TH1F  *pT_spectra_gamma_ratio_rebin_1=(TH1F *) inFile_data_phe_relative->Get("pT_spectra_gamma_ratio_rebin_1");
  TH1F  *pT_spectra_pi0_ratio_rebin_1=(TH1F *) inFile_data_phe_relative->Get("pT_spectra_pi0_ratio_rebin_1");
  TH1F*  pT_spectra_eta_ratio_rebin_1=(TH1F *) inFile_data_phe_relative->Get("pT_spectra_eta_ratio_rebin_1");
  //=========================================================================================
  // Get TH2F from  hijing simu
  
  for(Int_t idca=0;idca<mh2Ndca;idca++)
  {
    mh2Hijing_pi0_e_Same_MC[idca]=(TH2F *) inFile_simu_hijing->Get(mh2Name_pi0_e_same_MC[idca]); //DcaXY_pi01
    mh2Hijing_gamma_e_Same_MC[idca]=(TH2F *) inFile_simu_hijing->Get(mh2Name_gamma_e_same_MC[idca]);
    mh2Hijing_eta_e_Same_MC[idca]=(TH2F *) inFile_simu_hijing->Get(mh2Name_eta_e_same_MC[idca]);
    
    mh2Hijing_pi0_e[idca]=(TH2F *) inFile_simu_hijing->Get(mh2Name_pi0_e[idca]);//mh2_pi0_electronDcaXYVspt1
    mh2Hijing_eta_e[idca]=(TH2F *) inFile_simu_hijing->Get(mh2Name_eta_e[idca]);
    mh2Hijing_gamma_e[idca]=(TH2F *) inFile_simu_hijing->Get(mh2Name_gamma_e[idca]);
  }
  //=========================================================================================
  // Projection simulation
  
  for(Int_t idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      mh1Hijing_pi0_e_Pt_same_MC[idca][ipt]=(TH1F *) mh2Hijing_pi0_e_Same_MC[idca]->ProjectionY(Form("Pi0eDca_same_Mc%i%i",idca,ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      mh1Hijing_eta_e_Pt_same_MC[idca][ipt]=(TH1F *) mh2Hijing_eta_e_Same_MC[idca]->ProjectionY(Form("EtaeDca_same_Mc%i%i",idca,ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      mh1Hijing_gamma_e_Pt_same_MC[idca][ipt]=(TH1F *) mh2Hijing_gamma_e_Same_MC[idca]->ProjectionY(Form("GammaeDca_same_Mc%i%i",idca,ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      
      mh1Hijing_gamma_e_Pt_same_MC[idca][ipt]->SetLineColor(2);
      mh1Hijing_pi0_e_Pt_same_MC[idca][ipt]->SetLineColor(2);
      mh1Hijing_pi0_e_Pt_same_MC[idca][ipt]->SetTitle(mh1Title[ipt]); //title
      
      // single e from pi0 or gamma
      mh1Hijing_pi0_e_Pt[idca][ipt]=(TH1F *) mh2Hijing_pi0_e[idca]->ProjectionY(Form("Pi0eDca%i%i",idca,ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      mh1Hijing_eta_e_Pt[idca][ipt]=(TH1F *) mh2Hijing_eta_e[idca]->ProjectionY(Form("EtaeDca%i%i",idca,ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      mh1Hijing_gamma_e_Pt[idca][ipt]=(TH1F *) mh2Hijing_gamma_e[idca]->ProjectionY(Form("GammaeDca%i%i",idca,ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      
      mh1Hijing_eta_e_Pt[idca][ipt]->SetLineColor(3);
      mh1Hijing_gamma_e_Pt[idca][ipt]->SetLineColor(2);//color
      mh1Hijing_pi0_e_Pt[idca][ipt]->SetTitle(mh1Title[ipt]);
      mh1Hijing_pi0_e_Pt[idca][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
      if(idca==1) mh1Hijing_pi0_e_Pt[idca][ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
      mh1Hijing_pi0_e_Pt[idca][ipt]->GetYaxis()->SetTitle("Counts");
      //same
    }
  }
  
  TCanvas *c3=new TCanvas("c3","",1200,1400);
  c3->Divide(4,2);
  
  TCanvas *c4=new TCanvas("c4","",1200,1400);
  c4->Divide(4,2);
  
  for(Int_t idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      c3->cd(ipt+1);
      gPad->SetLogy();
      mh1Hijing_pi0_e_Pt_same_MC[idca][ipt]->Draw("PE");
      mh1Hijing_gamma_e_Pt_same_MC[idca][ipt]->Draw("same");
      mh1Hijing_eta_e_Pt_same_MC[idca][ipt]->Draw("same");
      
      c4->cd(ipt+1);
      gPad->SetLogy();
      mh1Hijing_pi0_e_Pt[idca][ipt]->Draw();
      mh1Hijing_gamma_e_Pt[idca][ipt]->Draw("same");
      mh1Hijing_eta_e_Pt[idca][ipt]->Draw("same");
    }
    c3->SaveAs(Form("Plots/Data_phe_gamma_%i_dca.pdf",idca));
    c4->SaveAs(Form("Plots/Data_single_%i_dca.pdf",idca));
  }
  //=========================================================================================
  // Rebin simulation
  
  for(Int_t idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      //pi0
      mh1Hijing_pi0_e_Pt_same_MC_rebin[idca][ipt]=( TH1F * )mh1Hijing_pi0_e_Pt_same_MC[idca][ipt]->Rebin(nDcasDca,mh1Hijing_pi0_e_Pt_same_MC[idca][ipt] ->GetName()+TString("_rebin"),DcaEdgeDca);
      mh1Hijing_pi0_e_Pt_rebin[idca][ipt]=( TH1F * )mh1Hijing_pi0_e_Pt[idca][ipt]->Rebin(nDcasDca,mh1Hijing_pi0_e_Pt[idca][ipt] ->GetName()+TString("_rebin"),DcaEdgeDca);
      
      mh1Hijing_pi0_e_Pt_same_MC_rebin[idca][ipt]->Scale(1,"width");
      mh1Hijing_pi0_e_Pt_rebin[idca][ipt]->Scale(1,"width");
      
      //eta
      mh1Hijing_eta_e_Pt_same_MC_rebin[idca][ipt]=( TH1F * )mh1Hijing_eta_e_Pt_same_MC[idca][ipt]->Rebin(nDcasDca,mh1Hijing_eta_e_Pt_same_MC[idca][ipt] ->GetName()+TString("_rebin"),DcaEdgeDca);
      mh1Hijing_eta_e_Pt_rebin[idca][ipt]=( TH1F * )mh1Hijing_eta_e_Pt[idca][ipt]->Rebin(nDcasDca,mh1Hijing_eta_e_Pt[idca][ipt] ->GetName()+TString("_rebin"),DcaEdgeDca);
      
      mh1Hijing_eta_e_Pt_same_MC_rebin[idca][ipt]->Scale(1,"width");
      mh1Hijing_eta_e_Pt_rebin[idca][ipt]->Scale(1,"width");
      
      //gamma
      mh1Hijing_gamma_e_Pt_same_MC_rebin[idca][ipt]=( TH1F * )mh1Hijing_gamma_e_Pt_same_MC[idca][ipt]->Rebin(nDcasDca,mh1Hijing_gamma_e_Pt_same_MC[idca][ipt] ->GetName()+TString("_rebin"),DcaEdgeDca);
      mh1Hijing_gamma_e_Pt_rebin[idca][ipt]=( TH1F * )mh1Hijing_gamma_e_Pt[idca][ipt]->Rebin(nDcasDca,mh1Hijing_gamma_e_Pt[idca][ipt] ->GetName()+TString("_rebin"),DcaEdgeDca);
      
      mh1Hijing_gamma_e_Pt_same_MC_rebin[idca][ipt]->Scale(1,"width");
      mh1Hijing_gamma_e_Pt_rebin[idca][ipt]->Scale(1,"width");
      
      // Draw hist set
      mh1Hijing_gamma_e_Pt_same_MC_rebin[idca][ipt]->SetLineColor(2);
      mh1Hijing_pi0_e_Pt_same_MC_rebin[idca][ipt]->SetLineColor(2);
      mh1Hijing_eta_e_Pt_same_MC_rebin[idca][ipt]->SetLineColor(2);
      
      mh1Hijing_gamma_e_Pt_rebin[idca][ipt]->SetLineColor(2);
      mh1Hijing_eta_e_Pt_rebin[idca][ipt]->SetLineColor(3);
      mh1Hijing_pi0_e_Pt_rebin[idca][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
      if(idca==1) mh1Hijing_pi0_e_Pt_rebin[idca][ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
      mh1Hijing_pi0_e_Pt_rebin[idca][ipt]->GetYaxis()->SetTitle("Counts");
    }
  }
  
  TCanvas *c32=new TCanvas("c32","",1200,1400);
  c32->Divide(4,2);//single
  TCanvas *c52=new TCanvas("c52","",1200,1400);
  c52->Divide(4,2); //pi0
  
  for(Int_t idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      c32->cd(ipt+1);
      gPad->SetLogy();
      mh1Hijing_pi0_e_Pt_rebin[idca][ipt]->Draw();
      mh1Hijing_gamma_e_Pt_rebin[idca][ipt]->Draw("same");
      mh1Hijing_eta_e_Pt_rebin[idca][ipt]->Draw("same");
      
      c52->cd(ipt+1);
      gPad->SetLogy();
      mh1Hijing_pi0_e_Pt_same_MC_rebin[idca][ipt]->Draw("same");
      mh1Hijing_gamma_e_Pt_same_MC_rebin[idca][ipt]->Draw("same");
      mh1Hijing_eta_e_Pt_same_MC_rebin[idca][ipt]->Draw("same");
    }
    c32->SaveAs(Form("Plots/Data_single_rebin_%i_dca.pdf",idca));
    c52->SaveAs(Form("Plots/Data_phe_pi0_rebin_%i_dca.pdf",idca));
    //=========================================================================================
    //ratio: single/same
    
    TH1F * mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[mh2Ndca][Npt];
    TH1F * mh1Hijing_pi0_e_Pt_same_MC_rebin_ratio[mh2Ndca][Npt];
    TH1F * mh1Hijing_eta_e_Pt_same_MC_rebin_ratio[mh2Ndca][Npt];
    
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[idca][ipt]= (TH1F *) mh1Hijing_gamma_e_Pt_same_MC_rebin[idca][ipt]->Clone(Form("mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio_%i",ipt));
      mh1Hijing_pi0_e_Pt_same_MC_rebin_ratio[idca][ipt]= (TH1F *) mh1Hijing_pi0_e_Pt_same_MC_rebin[idca][ipt]->Clone(Form("mh1Hijing_pi0_e_Pt_same_MC_rebin_ratio_%i",ipt));
      mh1Hijing_eta_e_Pt_same_MC_rebin_ratio[idca][ipt]= (TH1F *) mh1Hijing_eta_e_Pt_same_MC_rebin[idca][ipt]->Clone(Form("mh1Hijing_eta_e_Pt_same_MC_rebin_ratio%i",ipt));
      
      mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[idca][ipt]->Divide(mh1Hijing_gamma_e_Pt_rebin[idca][ipt]);
      mh1Hijing_pi0_e_Pt_same_MC_rebin_ratio[idca][ipt]->Divide(mh1Hijing_pi0_e_Pt_rebin[idca][ipt]);
      mh1Hijing_eta_e_Pt_same_MC_rebin_ratio[idca][ipt]->Divide(mh1Hijing_eta_e_Pt_rebin[idca][ipt]);
      
      // draw hist set
      mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[idca][ipt]->SetLineColor(1);
      mh1Hijing_pi0_e_Pt_same_MC_rebin_ratio[idca][ipt]->SetLineColor(2);
      mh1Hijing_eta_e_Pt_same_MC_rebin_ratio[idca][ipt]->SetLineColor(3);
      
      mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[idca][ipt]->GetYaxis()->SetRangeUser(0,1.4);
      mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[idca][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
      if(idca==1) mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[idca][ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
      mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[idca][ipt]->GetYaxis()->SetTitle("Counts");
      mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[idca][ipt]->SetTitle(mh1Title[ipt]);
    }
    
    TCanvas *c43=new TCanvas("c43","",1200,1400);
    c43->Divide(4,2);
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      c43->cd(ipt+1);
      mh1Hijing_gamma_e_Pt_same_MC_rebin_ratio[idca][ipt]->Draw();
      mh1Hijing_pi0_e_Pt_same_MC_rebin_ratio[idca][ipt]->Draw("same");
      mh1Hijing_eta_e_Pt_same_MC_rebin_ratio[idca][ipt]->Draw("same");
    }
    c43->SaveAs(Form("Plots/Gamma_single_phe_same_Mc_%i_dca.pdf",idca));
  }
  //=========================================================================================
  // add relative contribution for rebin hist
  
  TH1F* Single_Electron_hijing[mh2Ndca][Npt];//single
  TH1F* Phe_Electron_hijing[mh2Ndca][Npt];//same
  TH1F* Phe_Single_Electron_hijing[mh2Ndca][Npt]; //same+single
  
  TCanvas *c34=new TCanvas("c34","",1200,1400);
  c34->Divide(4,2);
  TCanvas *c44=new TCanvas("c44","",1200,1400);
  c44->Divide(4,2);
  for(Int_t idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      Single_Electron_hijing[idca][ipt]= new TH1F(Form("Single_Electron_hijing_%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Phe_Electron_hijing[idca][ipt]= new TH1F(Form("Phe_Electron_hijing_%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Phe_Single_Electron_hijing[idca][ipt]= new TH1F(Form("Phe_Single_Electron_hijing_%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      
      Single_Electron_hijing[idca][ipt]->Sumw2();
      Phe_Electron_hijing[idca][ipt]->Sumw2();
      Phe_Single_Electron_hijing[idca][ipt]->Sumw2();
      
      Single_Electron_hijing[idca][ipt]->Add(mh1Hijing_gamma_e_Pt_rebin[idca][ipt],pT_spectra_gamma_ratio_rebin_1->GetBinContent(ipt+1)); // relative contribution
      Single_Electron_hijing[idca][ipt]->Add(mh1Hijing_pi0_e_Pt_rebin[idca][ipt],Pi0_BR*pT_spectra_pi0_ratio_rebin_1->GetBinContent(ipt+1));
      Single_Electron_hijing[idca][ipt]->Add(mh1Hijing_eta_e_Pt_rebin[idca][ipt],Eta_BR*pT_spectra_eta_ratio_rebin_1->GetBinContent(ipt+1));
      
      Phe_Electron_hijing[idca][ipt]->Add(mh1Hijing_gamma_e_Pt_same_MC_rebin[idca][ipt],pT_spectra_gamma_ratio_rebin_1->GetBinContent(ipt+1));
      Phe_Electron_hijing[idca][ipt]->Add(mh1Hijing_pi0_e_Pt_same_MC_rebin[idca][ipt],Pi0_BR*pT_spectra_pi0_ratio_rebin_1->GetBinContent(ipt+1));
      Phe_Electron_hijing[idca][ipt]->Add(mh1Hijing_eta_e_Pt_same_MC_rebin[idca][ipt],Eta_BR*pT_spectra_eta_ratio_rebin_1->GetBinContent(ipt+1));
      
      // draw hist set
      Single_Electron_hijing[idca][ipt]->SetMarkerStyle(20);
      Phe_Electron_hijing[idca][ipt]->SetMarkerStyle(20);
      Single_Electron_hijing[idca][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
      Phe_Electron_hijing[idca][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
      if(idca==1)
      {
        Single_Electron_hijing[idca][ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
        Phe_Electron_hijing[idca][ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
      }
      Single_Electron_hijing[idca][ipt]->GetYaxis()->SetTitle("Counts");
      Phe_Electron_hijing[idca][ipt]->GetYaxis()->SetTitle("Counts");
      Single_Electron_hijing[idca][ipt]->SetTitle(mh1Title[ipt]);
      Phe_Electron_hijing[idca][ipt]->SetTitle(mh1Title[ipt]);
      Single_Electron_hijing[idca][ipt]->SetMarkerColor(2);
      Phe_Electron_hijing[idca][ipt]->SetMarkerColor(4);
      Single_Electron_hijing[idca][ipt]->GetYaxis()->SetRangeUser(0.1*Phe_Electron_hijing[idca][ipt]->GetMinimum(),10*Single_Electron_hijing[idca][ipt]->GetMaximum()); // zyj here to set large range
      
      //  Phe/single
      Phe_Single_Electron_hijing[idca][ipt]->Add(Phe_Electron_hijing[idca][ipt]); //single + same
      Phe_Single_Electron_hijing[idca][ipt]->Divide(Single_Electron_hijing[idca][ipt]);
      
      Phe_Single_Electron_hijing[idca][ipt]->SetMarkerColor(2);
      Phe_Single_Electron_hijing[idca][ipt]->SetLineColor(2);
      Phe_Single_Electron_hijing[idca][ipt]->SetMarkerStyle(20);
      Phe_Single_Electron_hijing[idca][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
      if(idca==1) Phe_Single_Electron_hijing[idca][ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
      Phe_Single_Electron_hijing[idca][ipt]->GetYaxis()->SetTitle("Phe/single");
      Phe_Single_Electron_hijing[idca][ipt]->SetTitle(mh1Title[ipt]);
    }
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      c34->cd(ipt+1);
      gPad->SetLogy();
      Single_Electron_hijing[idca][ipt]->Draw();
      Phe_Electron_hijing[idca][ipt]->Draw("same");
      c44->cd(ipt+1);
      Phe_Single_Electron_hijing[idca][ipt]->Draw("PE");
    }
    c34->SaveAs(Form("Plots/Combined_single_electron_%i_dca.pdf",idca));
    c44->SaveAs(Form("Plots/Combined_single_electron_ratio_%i_dca.pdf",idca));
  }
  //=========================================================================================
  // section 5 start data zyj
  
  for(int idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t itrg=0;itrg<Ntrig;itrg++)
    {
      if(idca==0)
      {
        if(itrg==0){
          mh2data_HFT_inclusive[idca][itrg]=(TH2F *) inFile_data_MB->Get(mh2Name_data_HFT_inclusive_DCAXY[itrg]);
          mh2data_HFT_unlike[idca][itrg]=(TH2F *) inFile_data_MB->Get(mh2Name_data_HFT_unlike_DCAXY[itrg]);
          mh2data_HFT_like[idca][itrg]=(TH2F *) inFile_data_MB->Get(mh2Name_data_HFT_like_DCAXY[itrg]);
        }
        else{
          mh2data_HFT_inclusive[idca][itrg]=(TH2F *) inFile_data_HT->Get(mh2Name_data_HFT_inclusive_DCAXY[itrg]);
          mh2data_HFT_unlike[idca][itrg]=(TH2F *) inFile_data_HT->Get(mh2Name_data_HFT_unlike_DCAXY[itrg]);
          mh2data_HFT_like[idca][itrg]=(TH2F *) inFile_data_HT->Get(mh2Name_data_HFT_like_DCAXY[itrg]);
        }
      }
      
      if(idca==1)
      {
        if(itrg==0){
          mh2data_HFT_inclusive[idca][itrg]=(TH2F *) inFile_data_MB->Get(mh2Name_data_HFT_inclusive_DCAZ[itrg]);
          mh2data_HFT_unlike[idca][itrg]=(TH2F *) inFile_data_MB->Get(mh2Name_data_HFT_unlike_DCAZ[itrg]);
          mh2data_HFT_like[idca][itrg]=(TH2F *) inFile_data_MB->Get(mh2Name_data_HFT_like_DCAZ[itrg]);
        }
        else{
          mh2data_HFT_inclusive[idca][itrg]=(TH2F *) inFile_data_HT->Get(mh2Name_data_HFT_inclusive_DCAZ[itrg]);
          mh2data_HFT_unlike[idca][itrg]=(TH2F *) inFile_data_HT->Get(mh2Name_data_HFT_unlike_DCAZ[itrg]);
          mh2data_HFT_like[idca][itrg]=(TH2F *) inFile_data_HT->Get(mh2Name_data_HFT_like_DCAZ[itrg]);
        }
      }
    }
  }
  
  for(int idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t itrg=0;itrg<Ntrig-1;itrg++) // xz 之前就不要trig 3
    {
      for(Int_t ipt=0;ipt<Npt;ipt++)
      {
        
        mh1data_HFT_inclusive[idca][itrg][ipt]  = (TH1F *) mh2data_HFT_inclusive[idca][itrg]->ProjectionX(Form("electron_data_Dca_inclusive%i%i%i",idca,itrg,ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
        mh1data_HFT_unlike[idca][itrg][ipt]  = (TH1F *) mh2data_HFT_unlike[idca][itrg]->ProjectionX(Form("electron_data_Dca_UnLike%i%i%i",idca,itrg,ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
        mh1data_HFT_like[idca][itrg][ipt]  = (TH1F *) mh2data_HFT_like[idca][itrg]->ProjectionX(Form("electron_data_Dca_Like%i%i%i",idca,itrg,ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
        mh1data_HFT_unlike_like[idca][itrg][ipt] =(TH1F *) mh1data_HFT_unlike[idca][itrg][ipt]->Clone(Form("electron_data_Dca_Unlike_like%i%i%i",idca,itrg,ipt));
        mh1data_HFT_unlike_like[idca][itrg][ipt]->Add(mh1data_HFT_like[idca][itrg][ipt],-1);
        
        // draw hist set
        mh1data_HFT_like[idca][itrg][ipt]->SetLineColor(2);
        mh1data_HFT_unlike[idca][itrg][ipt]->SetLineColor(1);
        mh1data_HFT_unlike_like[idca][itrg][ipt]->SetLineColor(4);
        
        mh1data_HFT_inclusive_rebin[idca][itrg][ipt]  = (TH1F *) mh1data_HFT_inclusive[idca][itrg][ipt]->Rebin(nDcasDca,mh1data_HFT_inclusive[idca][itrg][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
        mh1data_HFT_unlike_rebin[idca][itrg][ipt]  = (TH1F *) mh1data_HFT_unlike[idca][itrg][ipt]->Rebin(nDcasDca,mh1data_HFT_unlike[idca][itrg][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
        mh1data_HFT_like_rebin[idca][itrg][ipt]  = (TH1F *) mh1data_HFT_like[idca][itrg][ipt]->Rebin(nDcasDca,mh1data_HFT_like[idca][itrg][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
        mh1data_HFT_unlike_like_rebin[idca][itrg][ipt]  = (TH1F *) mh1data_HFT_unlike_like[idca][itrg][ipt]->Rebin(nDcasDca,mh1data_HFT_unlike_like[idca][itrg][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
        
        mh1data_HFT_inclusive_rebin[idca][itrg][ipt]->Scale(1.,"width");
        mh1data_HFT_unlike_like_rebin[idca][itrg][ipt]->Scale(1.,"width");
        mh1data_HFT_unlike_rebin[idca][itrg][ipt]->Scale(1.,"width");
        mh1data_HFT_like_rebin[idca][itrg][ipt]->Scale(1.,"width");
        
        mh1data_HFT_inclusive_rebin[idca][itrg][ipt]->SetMarkerStyle(20);
        mh1data_HFT_inclusive_rebin[idca][itrg][ipt]->SetMarkerColor(2);
        mh1data_HFT_inclusive_rebin[idca][itrg][ipt]->SetLineColor(2);
        
        mh1data_HFT_unlike_like_rebin[idca][itrg][ipt]->SetMarkerStyle(20);
        mh1data_HFT_unlike_like_rebin[idca][itrg][ipt]->SetMarkerColor(6);
        mh1data_HFT_unlike_like_rebin[idca][itrg][ipt]->SetLineColor(6);
        
        mh1data_HFT_unlike_rebin[idca][itrg][ipt]->SetMarkerStyle(20);
        mh1data_HFT_unlike_rebin[idca][itrg][ipt]->SetMarkerColor(4);
        mh1data_HFT_unlike_rebin[idca][itrg][ipt]->SetLineColor(4);
        
        mh1data_HFT_like_rebin[idca][itrg][ipt]->SetMarkerStyle(20);
        mh1data_HFT_like_rebin[idca][itrg][ipt]->SetMarkerColor(3);
        mh1data_HFT_like_rebin[idca][itrg][ipt]->SetLineColor(3);
      }
    }
  }
  // draw data
  TLegend *legend_data  = new TLegend(0.15,0.65,0.35,0.85);
  legend_data ->AddEntry(mh1data_HFT_unlike_rebin[0][1][0],"unlike","lp");
  legend_data ->AddEntry(mh1data_HFT_like_rebin[0][1][0],"like","lp");
  legend_data ->AddEntry(mh1data_HFT_unlike_like_rebin[0][1][0],"unlike-like","lp");
  SetLegend(legend_data,0,0.04,0,62);
  TCanvas *c35=new TCanvas("c35","",1200,1400);
  c35->Divide(4,2);
  TCanvas *c45=new TCanvas("c45","",1200,1400);
  c45->Divide(4,2);
  TCanvas *c55=new TCanvas("c55","",1200,1400);
  c55->Divide(4,2);
  for(int idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      mh1data_HFT_unlike[idca][Trg][ipt]->SetTitle(mh1Title[ipt]);
      mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->SetTitle(mh1Title[ipt]);
      mh1data_HFT_unlike_like_rebin[idca][2][ipt]->SetMarkerColor(6);
      if(add_HT_trigger){
        mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Add(mh1data_HFT_unlike_like_rebin[idca][1][ipt]);
        mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Add(mh1data_HFT_unlike_like_rebin[idca][2][ipt]);
        
        mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->Add(mh1data_HFT_inclusive_rebin[idca][1][ipt]);
        mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->Add(mh1data_HFT_inclusive_rebin[idca][2][ipt]);
        
        mh1data_HFT_unlike_rebin[idca][Trg][ipt]->Add(mh1data_HFT_unlike_rebin[idca][1][ipt]);
        mh1data_HFT_unlike_rebin[idca][Trg][ipt]->Add(mh1data_HFT_unlike_rebin[idca][2][ipt]);
        
        mh1data_HFT_unlike_rebin[idca][Trg][ipt]->Add(mh1data_HFT_like_rebin[idca][1][ipt]);
        mh1data_HFT_unlike_rebin[idca][Trg][ipt]->Add(mh1data_HFT_like_rebin[idca][2][ipt]);
      }
      Double_t min_phe=mh1data_HFT_like_rebin[idca][Trg][ipt]->GetMinimum();
      Double_t min_inc=mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->GetMinimum();
      
      if(min_inc<=10)
        min_inc=10;
      
      if(min_phe<=10)
        min_phe=10;
      
      // draw hist set
      mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->GetYaxis()->SetRangeUser(0.5*min_inc,10*mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->GetMaximum());
      mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->GetYaxis()->SetTitle("Counts");
      mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
      mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->GetXaxis()->CenterTitle(true);
      mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->SetTitle(mh1Title[ipt]);
      
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetYaxis()->SetRangeUser(0.1*min_phe,10*mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetMaximum());
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetYaxis()->SetTitle("Counts");
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetXaxis()->CenterTitle(true);
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->SetTitle(mh1Title[ipt]);
      
      if(idca==1)
      {
        mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
        mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
      }
    }
    
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      c35->cd(ipt+1);
      gPad->SetLogy();
      mh1data_HFT_unlike[idca][Trg][ipt]->Draw();
      mh1data_HFT_unlike_like[idca][Trg][ipt]->Draw("same");
      mh1data_HFT_like[idca][Trg][ipt]->Draw("same");
      
      legend_data->Draw();
      
      c45->cd(ipt+1);
      gPad->SetLogy();
      mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->Draw("PE");
      
      c55->cd(ipt+1);
      gPad->SetLogy();
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Draw("PE");
      mh1data_HFT_unlike_rebin[idca][Trg][ipt]->Draw("samePE");
      mh1data_HFT_like_rebin[idca][Trg][ipt]->Draw("samePE");
      legend_data->Draw("same");
    }
    c35->SaveAs(Form("Plots/Data_DcaXY_%i_dca.pdf",idca));
    c45->SaveAs(Form("Plots/Data_DcaXY_Inclusive_rebin_%i_dca.pdf",idca));
    c55->SaveAs(Form("Plots/Data_DcaXY_phe_rebin_%i_dca.pdf",idca));
  }
  //=========================================================================================
  //Hijing
  
  TH1F* Hijing_Single_electron[mh2Ndca][Npt];
  TH1F* Hijing_Single_electron_flip[mh2Ndca][Npt];
  TH1F* Hijing_phe_electron[mh2Ndca][Npt];
  TH1F* Hijing_phe_electron_flip[mh2Ndca][Npt];
  
  TH1F* Hijing_Single_electron_correct_to_data[mh2Ndca][Npt];
  TH1F* Hijing_Single_electron_flip_correct_to_data[mh2Ndca][Npt];
  
  TH1F* Hijing_Single_electron_ratio[mh2Ndca][Npt];
  TH1F* Hijing_Single_electron_flip_ratio[mh2Ndca][Npt];
  
  TH1F* Hijing_phe_electron_ratio[mh2Ndca][Npt];
  TH1F* Hijing_phe_electron_flip_ratio[mh2Ndca][Npt];
  
  TH1F* Hijing_Single_phe_electron_ratio[mh2Ndca][Npt];
  TH1F* Hijing_Single_phe_electron_flip_ratio[mh2Ndca][Npt];
  
  TH1F* Corrected_hijing_single[mh2Ndca][Npt];
  TH1F* Corrected_Phe_data[mh2Ndca][Npt];
  
  TH1F* Data_Over_Hijing_phe[mh2Ndca][Npt];
  TH1F* Data_Over_Hijing_phe_flip[mh2Ndca][Npt];
  
  TH1F* Data_Corrected_Phe_to_inclusive[mh2Ndca][Npt];
  
  TH1F* Ratio_rcData_rcHijing[mh2Ndca][Npt];
  
  //-----------------
  
  TH1F* Data_Over_Hijing_Data_rebin[mh2Ndca][Npt];
  TH1F* Data_Over_Hijing_phe_flip_Hijing_rebin[mh2Ndca][Npt];
  TH1F* Data_Over_Hijing_phe_flip_ratio_rebin[mh2Ndca][Npt];
  //----------------
  
  for(int idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      Hijing_Single_electron[idca][ipt]= new  TH1F(Form("Hijing_Single_electron_%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Hijing_Single_electron_flip[idca][ipt]= new  TH1F(Form("Hijing_Single_electron_flip%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Hijing_phe_electron_flip[idca][ipt]= new  TH1F(Form("Hijing_phe_electron_flip%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Hijing_phe_electron[idca][ipt]= new  TH1F(Form("Hijing_phe_electron%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      
      Hijing_Single_electron_flip_ratio[idca][ipt]= new  TH1F(Form("Hijing_Single_electron_flip_ratio%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Hijing_Single_electron_ratio[idca][ipt]= new  TH1F(Form("Hijing_Single_electron_ratio%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      
      Hijing_phe_electron_flip_ratio[idca][ipt]= new  TH1F(Form("Hijing_phe_electron_flip_ratio%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Hijing_phe_electron_ratio[idca][ipt]= new  TH1F(Form("Hijing_phe_electron_ratio%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Hijing_Single_phe_electron_ratio[idca][ipt]= new  TH1F(Form("Hijing_Single_phe_electron_ratio%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      
      Corrected_hijing_single[idca][ipt]= new  TH1F(Form("Corrected_hijing_single%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Corrected_Phe_data[idca][ipt]= new  TH1F(Form("Corrected_Phe_data%i_%i",idca,ipt),"",nDcasDca,DcaEdgeDca);
      Hijing_Single_electron[idca][ipt]->Sumw2();
      Hijing_Single_electron_flip[idca][ipt]->Sumw2();
      Hijing_phe_electron_flip[idca][ipt]->Sumw2();
      Hijing_phe_electron[idca][ipt]->Sumw2();
      Hijing_phe_electron_flip_ratio[idca][ipt]->Sumw2();
      Hijing_phe_electron_ratio[idca][ipt]->Sumw2();
      
      Corrected_hijing_single[idca][ipt]->Sumw2();
      Corrected_Phe_data[idca][ipt]->Sumw2();
      
      // get before
      Single_Electron_hijing[idca][ipt]->Scale(1./Single_Electron_hijing[idca][ipt]->Integral()); //Normalize single
      Phe_Electron_hijing[idca][ipt]->Scale(1./Phe_Electron_hijing[idca][ipt]->Integral()); // same
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Scale(1./mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Integral());//data
      
      // flip
      for(Int_t ibin=0;ibin<Hijing_Single_electron_flip[idca][ipt]->GetNbinsX();ibin++)
      {
        
        Hijing_Single_electron_flip[idca][ipt]->SetBinContent(ibin+1,Single_Electron_hijing[idca][ipt]->GetBinContent(Single_Electron_hijing[idca][ipt]->GetNbinsX()-ibin));
        Hijing_Single_electron_flip[idca][ipt]->SetBinError(ibin+1,Single_Electron_hijing[idca][ipt]->GetBinError(Single_Electron_hijing[idca][ipt]->GetNbinsX()-ibin));
        
        Hijing_phe_electron_flip[idca][ipt]->SetBinContent(ibin+1,Phe_Electron_hijing[idca][ipt]->GetBinContent(Single_Electron_hijing[idca][ipt]->GetNbinsX()-ibin));
        Hijing_phe_electron_flip[idca][ipt]->SetBinError(ibin+1,Phe_Electron_hijing[idca][ipt]->GetBinError(Single_Electron_hijing[idca][ipt]->GetNbinsX()-ibin));
      }
      
      Hijing_Single_electron[idca][ipt]->Add(Single_Electron_hijing[idca][ipt]);//copy single?
      Hijing_phe_electron[idca][ipt]->Add(Phe_Electron_hijing[idca][ipt],1); //copy same?
      
      Hijing_Single_phe_electron_ratio[idca][ipt]->Add(Single_Electron_hijing[idca][ipt]); //Hijing single/Hijing PHE
      Hijing_Single_phe_electron_ratio[idca][ipt]->Divide(Phe_Electron_hijing[idca][ipt]); // single/same ratio
      
      Hijing_phe_electron_flip_ratio[idca][ipt]->Add(mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]);// data/same filp
      Hijing_phe_electron_flip_ratio[idca][ipt]->Divide(Hijing_phe_electron_flip[idca][ipt]); // data unlike-like/hijing PHE filped
      
      Hijing_phe_electron_ratio[idca][ipt]->Add(mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]); // data/same
      Hijing_phe_electron_ratio[idca][ipt]->Divide(Hijing_phe_electron[idca][ipt]); //data unlike-like/hijing PHE filped
      
      Corrected_hijing_single[idca][ipt]->Add(Hijing_Single_electron_flip[idca][ipt]);//single filp/ same flip
      Corrected_Phe_data[idca][ipt]->Add(mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]); // Hijing single/data unlike-like
      
      if(ipt<=4) Corrected_hijing_single[idca][ipt]->Multiply(Hijing_phe_electron_flip_ratio[idca][ipt]);
      else Corrected_hijing_single[idca][ipt]->Multiply(Hijing_phe_electron_flip_ratio[idca][4]);
      
      Corrected_Phe_data[idca][ipt]->Multiply(Hijing_Single_phe_electron_ratio[idca][ipt]);
      
      // draw hist set
      Hijing_phe_electron_flip_ratio[idca][ipt]->SetMarkerStyle(20);
      Hijing_phe_electron_ratio[idca][ipt]->SetMarkerStyle(20);
      
      Hijing_phe_electron_flip_ratio[idca][ipt]->SetMarkerColor(3);
      Hijing_phe_electron_ratio[idca][ipt]->SetMarkerColor(2);
      
      Hijing_phe_electron_flip_ratio[idca][ipt]->SetLineColor(3);
      Hijing_phe_electron_ratio[idca][ipt]->SetLineColor(2);
      
      Hijing_phe_electron[idca][ipt]->SetMarkerColor(2);
      Hijing_phe_electron[idca][ipt]->SetMarkerStyle(20);
      Hijing_phe_electron[idca][ipt]->SetLineColor(2);
      
      Hijing_phe_electron_flip[idca][ipt]->SetMarkerColor(3);
      Hijing_phe_electron_flip[idca][ipt]->SetMarkerStyle(20);
      Hijing_phe_electron_flip[idca][ipt]->SetLineColor(3);
      
      Hijing_Single_electron[idca][ipt]->SetMarkerColor(1);
      Hijing_Single_electron[idca][ipt]->SetMarkerStyle(20);
      Hijing_Single_electron[idca][ipt]->SetLineColor(2);
      
      Hijing_Single_phe_electron_ratio[idca][ipt]->SetMarkerStyle(20);
      Hijing_Single_phe_electron_ratio[idca][ipt]->SetMarkerColor(2);
      Hijing_Single_phe_electron_ratio[idca][ipt]->SetLineColor(2);
      
      Single_Electron_hijing[idca][ipt]->Scale(1./Single_Electron_hijing[idca][ipt]->Integral());
    }
  }
  
  TCanvas *c36=new TCanvas("c36","",1200,1400);
  c36->Divide(4,2);
  TCanvas *c46=new TCanvas("c46","",1200,1400);
  c46->Divide(4,2);
  TCanvas *c56=new TCanvas("c56","",1200,1400);
  c56->Divide(4,2);
  
  TLegend *legend  = new TLegend(0.15,0.65,0.35,0.85);
  legend ->AddEntry(mh1data_HFT_unlike_like_rebin[0][Trg][0],"Data Unlike -like","lp");
  legend ->AddEntry(Hijing_phe_electron[0][0],"Hijing PHE","lp");
  legend ->AddEntry(Hijing_phe_electron_flip[0][0],"Hijing PHE flip","lp");
  
  SetLegend(legend,0,0.04,0,62);
  
  for(Int_t idca=0;idca<mh2Ndca;idca++)
  {
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      c36->cd(ipt+1);
      gPad->SetLogy();
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetXaxis()->SetTitle("DCA_{XY} cm");
      if(idca==1) mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetXaxis()->SetTitle("DCA_{Z} cm");
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetXaxis()->CenterTitle(true);
      
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->GetYaxis()->SetTitle("Counts");
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->SetTitle(mh1Title[ipt]);
      
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Draw("PE");
      Hijing_phe_electron[idca][ipt]->Draw("samePE");
      Hijing_phe_electron_flip[idca][ipt]->Draw("samePE");
      
      legend->Draw();
      c46->cd(ipt+1);
      
      Hijing_phe_electron_flip_ratio[idca][ipt]->GetYaxis()->SetRangeUser(0,3);
      Hijing_phe_electron_flip_ratio[idca][ipt]->GetXaxis()->SetTitle("DCA_{XY} cm");
      if(idca==1) Hijing_phe_electron_flip_ratio[idca][ipt]->GetXaxis()->SetTitle("DCA_{Z} cm");
      
      Hijing_phe_electron_flip_ratio[idca][ipt]->GetXaxis()->CenterTitle(true);
      
      Hijing_phe_electron_flip_ratio[idca][ipt]->GetYaxis()->SetTitle("Data unlike-like/Hijing Phe");
      Hijing_phe_electron_flip_ratio[idca][ipt]->SetTitle(mh1Title[ipt]);
      Hijing_phe_electron_flip_ratio[idca][ipt]->Draw("PE");
      Hijing_phe_electron_ratio[idca][ipt]->Draw("samePE");
      legend->Draw();
      
      c56->cd(ipt+1);
      Hijing_Single_phe_electron_ratio[idca][ipt]->GetYaxis()->SetRangeUser(0,2);
      Hijing_Single_phe_electron_ratio[idca][ipt]->GetXaxis()->SetTitle("DCA_{XY} cm");
      if(idca==1) Hijing_Single_phe_electron_ratio[idca][ipt]->GetXaxis()->SetTitle("DCA_{Z} cm");
      
      Hijing_Single_phe_electron_ratio[idca][ipt]->GetXaxis()->CenterTitle(true);
      
      Hijing_Single_phe_electron_ratio[idca][ipt]->GetYaxis()->SetTitle("Hijing Single/Hijing Phe");
      Hijing_Single_phe_electron_ratio[idca][ipt]->SetTitle(mh1Title[ipt]);
      Hijing_Single_phe_electron_ratio[idca][ipt]->Draw("");
      
    }
    c36->SaveAs(Form("Plots/Data_compar_with_hijing_%i.pdf",idca));
    c46->SaveAs(Form("Plots/Data_compar_with_hijing_ratio_%i.pdf",idca));
    c56->SaveAs(Form("Plots/Hijing_single_phe_ratio_%i.pdf",idca));
    
    for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      outFile_Hijing->cd();
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Scale(1./mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Integral());
      
      Hijing_phe_electron[idca][ipt]->Scale(1./Hijing_phe_electron[idca][ipt]->Integral());
      Hijing_phe_electron_flip[idca][ipt]->Scale(1./Hijing_phe_electron_flip[idca][ipt]->Integral());
      Corrected_hijing_single[idca][ipt]->Scale(1./Corrected_hijing_single[idca][ipt]->Integral());
      
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->SetTitle(mh1Title[ipt]);
      Hijing_phe_electron[idca][ipt]->SetTitle(mh1Title[ipt]);
      Hijing_phe_electron_flip[idca][ipt]->SetTitle(mh1Title[ipt]);
      Hijing_phe_electron_flip_ratio[idca][ipt]->SetTitle(mh1Title[ipt]);
      Hijing_phe_electron_ratio[idca][ipt]->SetTitle(mh1Title[ipt]);
      Corrected_hijing_single[idca][ipt]->SetTitle(mh1Title[ipt]);
      
      Hijing_phe_electron_flip_ratio[idca][ipt]->Write();
      Hijing_phe_electron_ratio[idca][ipt]->Write();
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Write();
      Hijing_phe_electron[idca][ipt]->Write();
      Hijing_phe_electron_flip[idca][ipt]->Write();
      Corrected_hijing_single[idca][ipt]->Write(); // use this zyj
      Corrected_Phe_data[idca][ipt]->Write();  // use this  zyj
      //==================================================================
      
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->SetTitle(mh1Title[ipt]);
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Scale(1./mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Integral());
      mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->SetTitle(mh1Title[ipt]);
      
      Corrected_Phe_data[idca][ipt]->Scale(1./Corrected_Phe_data[idca][ipt]->Integral());
      Corrected_Phe_data[idca][ipt]->SetTitle(mh1Title[ipt]);
      
      outFile_data->cd();
      mh1data_HFT_inclusive_rebin[idca][Trg][ipt]->Write(); // zyj divided bin width
      mh1data_HFT_unlike_like_rebin[idca][Trg][ipt]->Write();
      Corrected_Phe_data[idca][ipt]->Write();
    }
  }
  outFile_Hijing->Close();
  return 0;
}

void SetHistogram_TH1(TH1F *hist_1D,Double_t LineColor,Double_t MarkerStyle,Double_t MarkerColor,char* Title, char* XTitle,char* YTitle)
{
  hist_1D->SetLineColor(LineColor);
  hist_1D->SetMarkerColor(MarkerColor);
  hist_1D->SetMarkerStyle(MarkerStyle);
  hist_1D->SetMarkerStyle(MarkerStyle);
  hist_1D->SetTitle(Title);
  hist_1D->GetXaxis()->SetTitle(XTitle);
  hist_1D->GetYaxis()->SetTitle(YTitle);
  return ;
  
}
TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex)
{
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  // latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
}
void SetLegend(TLegend *legend_data,Double_t BorderSize=0,Double_t TextSize=0.04,Double_t FillStyle=0,Double_t TextFont=62)
{
  legend_data ->SetBorderSize(0);
  legend_data ->SetTextSize(0.04);
  legend_data ->SetFillStyle(0);
  legend_data ->SetTextFont(62);
  return ;
}



