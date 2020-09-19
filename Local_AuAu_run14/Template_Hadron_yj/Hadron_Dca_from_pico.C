/*--------------------Xiaozhi------------------------------------ 

  This macro to produce the hadron DCA background
  by Xiaozhi Bai
  Wed Dec 16 14:56:01 CST 2015
  
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
#include "TCanvas.h"
#include "TRandom3.h"
#include "TNtuple.h"
#include "../Binning_MB_yj.h"

const int mh2Nhist=3;
const int mh2Ndca=3;
Bool_t Draw_print_plots_flag=true;

Bool_t Hadron_from_pi=true; //default
Bool_t Hadron_from_kaon=false; //default
Bool_t Hadron_from_proton=false; //default
Bool_t Hadron_from_hadron=false; //default

//-----------------data-----------------------

TH2F *mh2data_HFT_hadron_dcaXY;
TH2F *mh2data_HFT_hadron_dcaZ;

TH1F *mh1data_HFT_hadron_dcaXY[Npt];
TH1F *mh1data_HFT_hadron_dcaZ[Npt];

TH1F *mh1data_HFT_hadron_dcaXY_2[Npt];
TH1F *mh1data_HFT_hadron_dcaZ_2[Npt];

char buf[1024];

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex);

int Hadron_Dca_from_pico(){

  TH2F:: SetDefaultSumw2();
  TH1F:: SetDefaultSumw2();
  
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleOffset(1,"X");
  gStyle->SetTitleOffset(1,"Y");
  gStyle->SetPadTopMargin(0.13);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.1); 
  gStyle->SetOptStat(00000);
  // gStyle->SetPadRightMargin(1.5);
  // gStyle->SetPadLeftMargin(3);
  
  //   return 1;
  if(Draw_print_plots_flag)
    {
      gStyle->SetOptStat(00000);
      gStyle->SetTitleSize(0.05,"XY");
      gStyle->SetTitleFontSize(0.06);
      gStyle->SetTitleOffset(1,"X");
      gStyle->SetTitleOffset(1,"Y");
      gStyle->SetPadTopMargin(0.02);
      gStyle->SetPadRightMargin(0.02);
      gStyle->SetPadBottomMargin(0.13);
      gStyle->SetPadLeftMargin(0.05); 
    }
 
  //TFile * inFile_data_pico= new TFile("Hadron_Dca_12_29.root","READ");
  //TFile * inFile_data_pico= new TFile("hadron_hist_allH_moreStat.root","READ");
  TFile * inFile_data_pico= new TFile("st_physics_more.root","READ");
  
  //TFile * File_data_hadron= new TFile("Dca_hadron_allH_moreStat_v2.root","RECREATE"); // new one
  //TFile * File_data_hadron= new TFile("Dca_hadron_qa_HFT_more_xzbin_v2.root","RECREATE"); // new one
  TFile * File_data_hadron= new TFile("Dca_hadron_qa_HFT_more_v2.root","RECREATE"); // new one
  
  if(Hadron_from_hadron)
    {
      mh2data_HFT_hadron_dcaXY=(TH2F *) inFile_data_pico->Get("HadronDcaXy_Pt_0");
      mh2data_HFT_hadron_dcaZ=(TH2F *) inFile_data_pico->Get("HadronDcaZ_Pt_0");
    }
  if(Hadron_from_kaon)
    {
      mh2data_HFT_hadron_dcaXY=(TH2F *) inFile_data_pico->Get("KaonDcaXy_Pt_0");
      mh2data_HFT_hadron_dcaZ=(TH2F *) inFile_data_pico->Get("KaonDcaZ_Pt_0");
    }
  if(Hadron_from_pi)
    {
      //mh2data_HFT_hadron_dcaXY=(TH2F *) inFile_data_pico->Get("PiDcaXy_Pt_0");
      //mh2data_HFT_hadron_dcaZ=(TH2F *) inFile_data_pico->Get("PiDcaZ_Pt_0");
      mh2data_HFT_hadron_dcaXY=(TH2F *) inFile_data_pico->Get("PiDcaXy_Pt_HFT_0");
      mh2data_HFT_hadron_dcaZ=(TH2F *) inFile_data_pico->Get("PiDcaZ_Pt_HFT_0");

    }
  // projection data
  for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      
      mh1data_HFT_hadron_dcaXY[ipt]  = (TH1F *) mh2data_HFT_hadron_dcaXY->ProjectionY(Form("Hadron_dcaXY_%i",ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      mh1data_HFT_hadron_dcaZ[ipt] = (TH1F *) mh2data_HFT_hadron_dcaZ->ProjectionY(Form("Hadron_dcaZ_%i",ipt),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
    }
   
  TH1F *Hadron_DcaXy_Rebin[Npt];
  TH1F *Hadron_DcaZ_Rebin[Npt];

  //return 0;
  for(Int_t ipt=0;ipt<Npt;ipt++)
  //for(Int_t ipt=0;ipt<1;ipt++)
    {
      Hadron_DcaXy_Rebin[ipt]=(TH1F *) mh1data_HFT_hadron_dcaXY[ipt]->Rebin(nDcasDca,mh1data_HFT_hadron_dcaXY[ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
      Hadron_DcaZ_Rebin[ipt]=(TH1F *) mh1data_HFT_hadron_dcaZ[ipt]->Rebin(nDcasDca,mh1data_HFT_hadron_dcaZ[ipt]->GetName()+TString("_rebin"),DcaEdgeDca);

      Hadron_DcaXy_Rebin[ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
      Hadron_DcaZ_Rebin[ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");

      Hadron_DcaXy_Rebin[ipt]->SetTitle(mh1Title[ipt]);
      Hadron_DcaZ_Rebin[ipt]->SetTitle(mh1Title[ipt]);

      if(!Draw_print_plots_flag){
	Hadron_DcaXy_Rebin[ipt]->Scale(1.,"width");
	Hadron_DcaZ_Rebin[ipt]->Scale(1.,"width");
      }

      File_data_hadron->cd();
      Hadron_DcaXy_Rebin[ipt]->Write();
      Hadron_DcaZ_Rebin[ipt]->Write();
      File_data_hadron->cd();
    }
  // draw DCAxy & DCAz
  for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      mh1data_HFT_hadron_dcaXY[ipt]->Rebin(5);
      mh1data_HFT_hadron_dcaZ[ipt]->Rebin(5);

      mh1data_HFT_hadron_dcaZ[ipt]->GetXaxis()->SetTitle("DCA_{Z} (cm)");
      mh1data_HFT_hadron_dcaXY[ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");

      mh1data_HFT_hadron_dcaXY[ipt]->GetYaxis()->SetTitle("Counts");
      mh1data_HFT_hadron_dcaZ[ipt]->GetYaxis()->SetTitle("Counts");

      mh1data_HFT_hadron_dcaXY[ipt]->SetTitle(mh1Title[ipt]);
      mh1data_HFT_hadron_dcaZ[ipt]->SetTitle(mh1Title[ipt]);


      mh1data_HFT_hadron_dcaXY[ipt]->SetMarkerColor(2);
      mh1data_HFT_hadron_dcaXY[ipt]->SetLineColor(2);
      mh1data_HFT_hadron_dcaXY[ipt]->SetMarkerStyle(20);

      mh1data_HFT_hadron_dcaZ[ipt]->SetMarkerColor(2);
      mh1data_HFT_hadron_dcaZ[ipt]->SetLineColor(2);
      mh1data_HFT_hadron_dcaZ[ipt]->SetMarkerStyle(20);
    }

  TCanvas *c3=new TCanvas("c3","",1000,800);
  c3->Divide(4,2);

  TCanvas *c4=new TCanvas("c4","",1000,800);
  c4->Divide(4,2);

  for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      c3->cd(ipt+1);
      gPad->SetLogy();

      mh1data_HFT_hadron_dcaXY[ipt]->GetXaxis()->CenterTitle(true);
      mh1data_HFT_hadron_dcaXY[ipt]->Draw("PE");
      c4->cd(ipt+1);
      gPad->SetLogy();
      mh1data_HFT_hadron_dcaZ[ipt]->Draw("PE");
    }

  c3->SaveAs("Plots/DcaXy_hadron_from_pico_hadron.pdf");
  c4->SaveAs("Plots/DcaZ_hadron_from_pico_hadron.pdf");



  if(Draw_print_plots_flag)
    {

      TCanvas *c5=new TCanvas("c5","",1000,1000);
      
      c5->cd();
      gPad->SetLogy();
      mh1data_HFT_hadron_dcaXY[2]->SetTitle("");
      mh1data_HFT_hadron_dcaXY[2]->GetYaxis()->SetTitle("");
      mh1data_HFT_hadron_dcaXY[2]->GetXaxis()->CenterTitle(true);
      mh1data_HFT_hadron_dcaXY[2]->Draw("PE");

      sprintf(buf,"STAR Au+Au @ 200 GeV");
      drawLatex(0.12,0.92,buf,62,0.035,1);

      sprintf(buf,"Hadron DCA_{XY} from data");
      drawLatex(0.12,0.85,buf,62,0.03,1);

      sprintf(buf,"1.5 < p_{T} < 2 GeV/c");
      drawLatex(0.12,0.76,buf,62,0.03,1);
   
      c5->SaveAs("Hadron_Dca_print.pdf");
    }
  
  return 0;
}

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex)
{
  TLatex *latex = new TLatex(x,y,text); 
  latex->SetNDC();
  latex->SetTextSize(textSize);   
  latex->SetTextColor(colorIndex); 
  latex->Draw("same");
  return latex;
}
