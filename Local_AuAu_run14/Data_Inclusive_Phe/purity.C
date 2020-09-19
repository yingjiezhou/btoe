/*--------------------Xiaozhi------------------------------------ 

This macro is for the photo electron nsigma in different Pt bin
for the nsigma Electran calibration 
low Pt electron purity

---------------------------------------------------------------
*/

#include<fstream>
#include <iostream>
#include<iomanip>
#include "TLatex.h"
#include "TStyle.h"
#include "TH3F.h"
#include "TF1.h"
#include "TMath.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TGraphErrors.h"
#include "../../../Binning_HT.h"

using namespace std;



void Draw_purity(TH1D * );
void Draw_purity_sys(TH1D *,TH1D *,TH1D * );
// Double_t Get_sys_Error(TH1F const *,Int_t);
Double_t Get_sts_Error(TH1F *const ,Int_t, TF1 *, TF1 *,TF1 *,TF1 *,Int_t,Int_t,Double_t ,Double_t);
void Fit_electron_purity(TH1F * a[]);
// void nSigma_cut_efficiency( TH1F *,TH1F *,TH1F *,TH1F *,TH1F *,TH1F *,Float_t,Float_t,Float_t,Float_t);

TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
Double_t Fit_purity(TH1F * const inclusive,Int_t ipt,Float_t E_mean_err,Float_t E_sigma_err, TF1 *,TF1 *, TF1 *,TF1 *,int ,Int_t);

//TFile *File=new TFile("nSigmaE_calibration.root","READ");
TFile *File_electron=new TFile("nsigmaE_mean_sigma_hft_0_root","READ","READ");

TFile *File_hadron=new TFile("hadron_nsigmaE.root","READ");


TGraphErrors *gr_pi_Mean=(TGraphErrors *) File_hadron->Get("Graph_from_nsigmaPI_pT_diff_2_pfx");
TGraphErrors *gr_proton_Mean=(TGraphErrors *) File_hadron->Get("Graph_from_nsigmaP_pT_diff_2_pfx");
TGraphErrors *gr_kaon_Mean=(TGraphErrors *) File_hadron->Get("Graph_from_nsigmaK_pT_diff_2_pfx");

TH1F *pi_Mean;
TH1F *proton_Mean;
TH1F *kaon_Mean;

// TH1F *electron_Sigma=(TH1F *) File->Get("Sigma");
// TH1F *electron_Mean=(TH1F *) File->Get("Mean");  

TH1F *electron_Sigma=(TH1F *) File_electron->Get("Electron_nsigmaE_sigma");
TH1F *electron_Mean=(TH1F *) File_electron->Get("Electron_nsigmaE_mean");  


char buf[1024];


// TF1 *total_3;
// TF1 *g1;
// TF1 *g2;
// TF1 *g3;

bool HFT_flag=1;
bool SMD_cut_flag=1;

int purity(){



  gr_pi_Mean->Draw();
  gr_proton_Mean->Draw("sameP");
  gr_kaon_Mean->Draw("sameP");
  //electron_Mean->Draw();

TH3F::SetDefaultSumw2();  
TH2F::SetDefaultSumw2();  
TH1F::SetDefaultSumw2();  

//  gStyle->SetOptStat(00000);
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleOffset(1,"X");
  gStyle->SetTitleOffset(1,"Y");
  gStyle->SetPadTopMargin(0.13);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.1); 

  //  electron_Mean->Draw();

  TH1F *nsigmaE_inclusive[NpT_bins_run14_HT];

  // TFile * inFile=new TFile("../hist_ht.root","READ");
  TFile * inFile=new TFile("../ht_hist_hist.root","READ");
     //  TFile * inFile=new TFile("../ht_hft_10_23_hisogram.root","READ");
  
  TH2F * nsigmaE_inclusive_Trig1;
  TH2F * nsigmaE_inclusive_Trig2;
  TH2F * nsigmaE_inclusive_Trig3;

  if(HFT_flag)
    {
      nsigmaE_inclusive_Trig1=(TH2F *) inFile->Get("mnsigmaE_pT_HFT_E1"); 
      nsigmaE_inclusive_Trig2=(TH2F *) inFile->Get("mnsigmaE_pT_HFT_E2");
      nsigmaE_inclusive_Trig3=(TH2F *) inFile->Get("mnsigmaE_pT_HFT_E3"); 
    }
  else
    {
      nsigmaE_inclusive_Trig1=(TH2F *) inFile->Get("mnsigmaE_pT_E1"); 
      nsigmaE_inclusive_Trig2=(TH2F *) inFile->Get("mnsigmaE_pT_E2");
      nsigmaE_inclusive_Trig3=(TH2F *) inFile->Get("mnsigmaE_pT_E3"); 
    }


  if(SMD_cut_flag)
    {
      if(HFT_flag)
	{
	  nsigmaE_inclusive_Trig1=(TH2F *) inFile->Get("mnsigmaE_pT_HFT_E_SMD1"); 
	  nsigmaE_inclusive_Trig2=(TH2F *) inFile->Get("mnsigmaE_pT_HFT_E_SMD2");
	  nsigmaE_inclusive_Trig3=(TH2F *) inFile->Get("mnsigmaE_pT_HFT_E_SMD3"); 
	}
      else
	{
	  nsigmaE_inclusive_Trig1=(TH2F *) inFile->Get("mnsigmaE_pT_E_SMD1"); 
	  nsigmaE_inclusive_Trig2=(TH2F *) inFile->Get("mnsigmaE_pT_E_SMD2");
	  nsigmaE_inclusive_Trig3=(TH2F *) inFile->Get("mnsigmaE_pT_E_SMD3"); 
	}
    }
    
  
  
  nsigmaE_inclusive_Trig1->Sumw2();
  nsigmaE_inclusive_Trig1->Add(nsigmaE_inclusive_Trig2,1);
  nsigmaE_inclusive_Trig1->Add(nsigmaE_inclusive_Trig3,1);
    
  
  cout<< "  GetFile"<<endl;
  for(Int_t ipt=0;ipt<NpT_bins_run14_HT;ipt++)
    {
      sprintf(buf,"nSigmaE_pt%i",ipt);
      nsigmaE_inclusive[ipt]=(TH1F *) nsigmaE_inclusive_Trig1->ProjectionY(buf,Ptbin_d[ipt],Ptbin_u[ipt]);
      nsigmaE_inclusive[ipt]->Rebin(2);
      nsigmaE_inclusive[ipt]->SetMarkerStyle(24);
      nsigmaE_inclusive[ipt]->SetMarkerSize(0.5);
    }


  //calculate hadron mean
  pi_Mean=new TH1F("pi_Mean","",NpT_bins_run14_HT,pt_run14_HT);
  proton_Mean=new TH1F("proton_Mean","",NpT_bins_run14_HT,pt_run14_HT);
  kaon_Mean=new TH1F("kaon_Mean","",NpT_bins_run14_HT,pt_run14_HT);

  
  for(Int_t ipt=0;ipt<NpT_bins_run14_HT;ipt++)
    {

      cout<< gr_pi_Mean->Eval(pi_Mean->GetBinCenter(ipt+1))<<endl;;
      pi_Mean->SetBinContent(ipt+1,electron_Mean->GetBinContent(ipt+1)-gr_pi_Mean->Eval(pi_Mean->GetBinCenter(ipt+1)));
      proton_Mean->SetBinContent(ipt+1,electron_Mean->GetBinContent(ipt+1)-gr_proton_Mean->Eval(proton_Mean->GetBinCenter(ipt+1)));
      kaon_Mean->SetBinContent(ipt+1,electron_Mean->GetBinContent(ipt+1)-gr_kaon_Mean->Eval(kaon_Mean->GetBinCenter(ipt+1)));
      
    }
  

  
  // nsigmaE_inclusive[2]->Draw();
  
  //  nsigmaE_inclusive_Trig1->Draw("COLZ");
   
     Fit_electron_purity(nsigmaE_inclusive);
  return 0;
  

}


void Fit_electron_purity(TH1F * nsigmaE_inclusive[])
{

  TH1D *purity_HT=new TH1D("purity_HT","",NpT_bins_run14_HT,pt_run14_HT);
  TH1D *purity_oneSigma=new TH1D("purity_oneSigma","",NpT_bins_run14_HT,pt_run14_HT);
  TH1D *purity_twoSigma=new TH1D("purity_twoSigma","",NpT_bins_run14_HT,pt_run14_HT);
  TH1D *purity_threeSigma=new TH1D("purity_threeSigma","",NpT_bins_run14_HT,pt_run14_HT);


  TH1F * mh1Electron_Constant=new TH1F("mh1Electron_Constant","",NpT_bins_run14_HT,pt_run14_HT);
  TH1F * mh1Electron_Mean=new TH1F("mh1Electron_Mean","",NpT_bins_run14_HT,pt_run14_HT);
  TH1F * mh1Electron_Sigma=new TH1F("mh1Electron_Sigma","",NpT_bins_run14_HT,pt_run14_HT);

  TH1F * mh1Pion_Constant=new TH1F("mh1Pion_Constant","",NpT_bins_run14_HT,pt_run14_HT);
  TH1F * mh1Pion_Mean=new TH1F("mh1Pion_Mean","",NpT_bins_run14_HT,pt_run14_HT);
  TH1F * mh1Pion_Sigma=new TH1F("mh1Pion_Sigma","",NpT_bins_run14_HT,pt_run14_HT);

  TH1F * mh1Proton_Constant=new TH1F("mh1Proton_Constant","",NpT_bins_run14_HT,pt_run14_HT);
  TH1F * mh1Proton_Mean=new TH1F("mh1Proton_Mean","",NpT_bins_run14_HT,pt_run14_HT);
  TH1F * mh1Proton_Sigma=new TH1F("mh1Proton_Sigma","",NpT_bins_run14_HT,pt_run14_HT);

  TH1F * mh1Kaon_Constant=new TH1F("mh1Kaon_Constant","",NpT_bins_run14_HT,pt_run14_HT);
  TH1F * mh1Kaon_Mean=new TH1F("mh1Kaon_Mean","",NpT_bins_run14_HT,pt_run14_HT);
  TH1F * mh1Kaon_Sigma=new TH1F("mh1Kaon_Sigma","",NpT_bins_run14_HT,pt_run14_HT);

  
  
  gStyle->SetOptFit(111);

  TCanvas *c2=new TCanvas("c2","",1200,1000);
  TCanvas *c3=new TCanvas("c3","",1200,1000);
  
  c2->Divide(2,2);
  c3->Divide(2,2);
  

  int Npad=1;
  
  for(Int_t ipt=0;ipt<NpT_bins_run14_HT;ipt++)
    {
      
          TF1 *   total_3 =new TF1(TString("total_3"),"[0]*TMath::Gaus(x,[1],[2],1) + [3]*TMath::Gaus(x,[4],[5],1) + [6]*TMath::Gaus(x,[7],[8],1)",-15,15);
	  //TF1 *   total_3 =new TF1(TString("total_3"),"[0]*TMath::Gaus(x,[1],[2],1) + [3]*TMath::Gaus(x,[4],[5],1) + [6]*TMath::Gaus(x,[7],[8],1)+[9]*TMath::Gaus(x,[10],[11],1)",-15,15);
      TF1 *  g1=new TF1(TString("g1"),"[0]*TMath::Gaus(x,[1],[2],1)",-15,15);   
      TF1 * g2=new TF1(TString("g2"),"[0]*TMath::Gaus(x,[1],[2],1)",-15,15);   
      TF1 *  g3=new TF1(TString("g3"),"[0]*TMath::Gaus(x,[1],[2],1)",-15,15); 
      
      //   total_3->SetParNames("k+p C", "k+p #mu", "k+p #sigma", "#pi C", "#pi #mu", "#pi #sigma","e C","e #mu","e #sigma");
      total_3->SetLineColor(kBlue);
      g1->SetLineColor(kRed);
      g2->SetLineColor(kGreen+3);
      g3->SetLineColor(kMagenta);

      g2->SetLineStyle(7);
      g3->SetLineStyle(7);

      
      if(ipt<6)
	{
	  c2->cd(Npad++);
	  gPad->SetLogy(1);
	}
      else 
        {
          c3->cd(Npad++);
          gPad->SetLogy(1);
        }
      if(Npad==7) Npad=1;
      
      nsigmaE_inclusive[ipt]->SetTitle(mh1_pT_Title_HT[ipt]);
      nsigmaE_inclusive[ipt]->GetXaxis()->SetTitle("nSigmaE");
      nsigmaE_inclusive[ipt]->GetYaxis()->SetTitle("Counts");
      
      //nsigmaE_inclusive[ipt]->GetYaxis()->SetRangeUser(1,1.3*nsigmaE_inclusive[ipt]->GetMaximum());
      nsigmaE_inclusive[ipt]->GetXaxis()->SetRangeUser(-15,15);  
      
      Float_t k_p_mean=0.5*(proton_Mean->GetBinContent(ipt+1)+kaon_Mean->GetBinContent(ipt+1));
      total_3->SetParameter(1,k_p_mean);
      total_3->SetParameter(2,1);
      
      total_3->SetParameter(4,pi_Mean->GetBinContent(ipt+1));
      total_3->SetParameter(5,1);
	
      total_3->SetParameter(7,electron_Mean->GetBinContent(ipt+1));
      total_3->SetParameter(8,electron_Sigma->GetBinContent(ipt+1));
      
      

      total_3->SetParLimits(2,0.6,1.5);
      total_3->SetParLimits(4,pi_Mean->GetBinContent(ipt+1)-0.5,pi_Mean->GetBinContent(ipt+1)+0.5);
      total_3->SetParLimits(5,0.6,1.5);


      
      total_3->SetParLimits(7,electron_Mean->GetBinContent(ipt+1)-electron_Mean->GetBinError(ipt+1),electron_Mean->GetBinContent(ipt+1)+electron_Mean->GetBinError(ipt+1));
      total_3->SetParLimits(8,electron_Sigma->GetBinContent(ipt+1)-electron_Sigma->GetBinError(ipt+1),electron_Sigma->GetBinContent(ipt+1)+electron_Sigma->GetBinError(ipt+1));
      
      // //total_3->SetParLimits(1, );
      
	
      nsigmaE_inclusive[ipt]->Fit(total_3,"R","same",-10,5);
      
      
      g1->SetParameter(0,total_3->GetParameter(6));
      g1->SetParameter(1,total_3->GetParameter(7));
      g1->SetParameter(2,total_3->GetParameter(8));
      
      g2->SetParameter(0,total_3->GetParameter(3));
      g2->SetParameter(1,total_3->GetParameter(4));
      g2->SetParameter(2,total_3->GetParameter(5));
      
      g3->SetParameter(0,total_3->GetParameter(0));
      g3->SetParameter(1,total_3->GetParameter(1));
      g3->SetParameter(2,total_3->GetParameter(2));
       
       
      g1->Draw("same");
      g2->Draw("same");
      g3->Draw("same");


      mh1Electron_Constant->SetBinContent(ipt+1,total_3->GetParameter(6));
      mh1Electron_Constant->SetBinError(ipt+1,total_3->GetParError(6));
      
      mh1Electron_Mean->SetBinContent(ipt+1,total_3->GetParameter(7));
      mh1Electron_Mean->SetBinError(ipt+1,total_3->GetParError(7));
      
      mh1Electron_Sigma->SetBinContent(ipt+1,total_3->GetParameter(8));
      mh1Electron_Sigma->SetBinError(ipt+1,total_3->GetParError(8));

      //pion
      mh1Pion_Constant->SetBinContent(ipt+1,total_3->GetParameter(3));
      mh1Pion_Constant->SetBinError(ipt+1,total_3->GetParError(3));
      
      mh1Pion_Mean->SetBinContent(ipt+1,total_3->GetParameter(4));
      mh1Pion_Mean->SetBinError(ipt+1,total_3->GetParError(4));
      
      mh1Pion_Sigma->SetBinContent(ipt+1,total_3->GetParameter(5));
      mh1Pion_Sigma->SetBinError(ipt+1,total_3->GetParError(5));

      
      
      //kaon_proton
      mh1Kaon_Constant->SetBinContent(ipt+1,total_3->GetParameter(0));
      mh1Kaon_Constant->SetBinError(ipt+1,total_3->GetParError(0));
      
      mh1Kaon_Mean->SetBinContent(ipt+1,total_3->GetParameter(1));
      mh1Kaon_Mean->SetBinError(ipt+1,total_3->GetParError(1));
      
      mh1Kaon_Sigma->SetBinContent(ipt+1,total_3->GetParameter(2));
      mh1Kaon_Sigma->SetBinError(ipt+1,total_3->GetParError(2));


      
      
      
      TLegend *legend = new TLegend(0.15,0.55,0.35,0.8);
      legend->AddEntry(g1,"e ","lp");
      legend->AddEntry(g2,"#pi ","lp");
      legend->AddEntry(g3,"k+p","lp");
      legend->AddEntry(total_3,"Fit","lp");

      legend->SetBorderSize(0);
      legend->SetFillStyle(0);
      legend->SetTextSize(0.055);
      legend ->SetTextFont(62);       
      legend->Draw("same");

  
      c2->SaveAs(Form("plots/purity_fit_c2_%i.pdf",HFT_flag));
      c3->SaveAs(Form("plots/purity_fit_c3_%i.pdf",HFT_flag));






            
      Double_t mPurity=g1->Integral(-1,3)/total_3->Integral(-1,3);
      purity_HT->SetBinContent(ipt+1,mPurity);

      //       continue;
      //   Double_t mPurity_sys=Get_purity_sys(nsigmaE_inclusive[ipt],ipt,);

     
      //     Double_t mPurity_sts=Get_purity_sts(nsigmaE_inclusive[ipt],ipt);
      Double_t mPurity_temp_oneSigma= Fit_purity(nsigmaE_inclusive[ipt],ipt,electron_Mean->GetBinError(ipt+1),electron_Sigma->GetBinError(ipt+1),total_3,g1,g2,g3,1,1); 
      Double_t mPurity_temp_twoSigma= Fit_purity(nsigmaE_inclusive[ipt],ipt,electron_Mean->GetBinError(ipt+1),electron_Sigma->GetBinError(ipt+1),total_3,g1,g2,g3,2,1); 
      Double_t mPurity_temp_threeSigma= Fit_purity(nsigmaE_inclusive[ipt],ipt,electron_Mean->GetBinError(ipt+1),electron_Sigma->GetBinError(ipt+1),total_3,g1,g2,g3,3,1); 



      purity_oneSigma->SetBinContent(ipt+1,mPurity_temp_oneSigma);
      purity_twoSigma->SetBinContent(ipt+1,mPurity_temp_twoSigma);
      purity_threeSigma->SetBinContent(ipt+1,mPurity_temp_threeSigma);
      

      
      Double_t purity_mean=(mPurity_temp_oneSigma+mPurity_temp_twoSigma+mPurity_temp_threeSigma)/3.;

      
      Double_t mPurity_sys=0;
      if(abs(purity_mean-mPurity_temp_oneSigma)>mPurity_sys)
	mPurity_sys=abs(purity_mean-mPurity_temp_oneSigma);
      
      if(abs(purity_mean-mPurity_temp_twoSigma)>mPurity_sys)
	mPurity_sys=abs(purity_mean-mPurity_temp_twoSigma);
      
      if(abs(purity_mean-mPurity_temp_threeSigma)>mPurity_sys)
	mPurity_sys=abs(purity_mean-mPurity_temp_threeSigma);


      // continue;


      Double_t mPurity_sts=0.0;
      //     mPurity_sts= Get_sts_Error(nsigmaE_inclusive[ipt],ipt,total_3,g1,g2,g3,3,0,purity_mean,mPurity_sys);

      purity_HT->SetBinContent(ipt+1,purity_mean);
      purity_HT->SetBinError(ipt+1,sqrt(mPurity_sys*mPurity_sys+mPurity_sts*mPurity_sts));

      Fit_purity(nsigmaE_inclusive[ipt],ipt,electron_Mean->GetBinError(ipt+1),electron_Sigma->GetBinError(ipt+1),total_3,g1,g2,g3,1,1); 
      Fit_purity(nsigmaE_inclusive[ipt],ipt,electron_Mean->GetBinError(ipt+1),electron_Sigma->GetBinError(ipt+1),total_3,g1,g2,g3,2,1); 
      Fit_purity(nsigmaE_inclusive[ipt],ipt,electron_Mean->GetBinError(ipt+1),electron_Sigma->GetBinError(ipt+1),total_3,g1,g2,g3,3,1); 
      
       TFile *file_purity=new TFile("purity_HT.root","RECREATE");
       purity_HT->Write();
       file_purity->Close();

    }

  
  Draw_purity_sys(purity_oneSigma,purity_twoSigma,purity_threeSigma);

  Draw_purity(purity_HT);

  TFile *file_3=new TFile("Mean_Sigma_Hadron.root","RECREATE");

  mh1Electron_Constant->Write();
  mh1Electron_Mean->Write();
  mh1Electron_Sigma->Write();
   
  mh1Pion_Constant->Write();
  mh1Pion_Mean->Write();
  mh1Pion_Sigma->Write();
   
  mh1Kaon_Constant->Write();
  mh1Kaon_Mean->Write();
  mh1Kaon_Sigma->Write();

}

Double_t Fit_purity(TH1F * const inclusive,Int_t ipt,Float_t E_mean_err,Float_t E_sigma_err,TF1 *total_3,TF1 * g1,TF1 *g2,TF1 *g3, Int_t Sigma_flag,Int_t Draw_flag)
{
  TH1F *Inclusive= (TH1F *)  inclusive->Clone("Inclusive");
  TCanvas * c4=new TCanvas("c4","",1200,800);
  gPad->SetLogy();
  
  //  total_3->SetParNames("k+p C", "k+p #mu", "k+p #sigma", "#pi C", "#pi #mu", "#pi #sigma","e C","e #mu","e #sigma");
  total_3->SetLineColor(kBlue);
  g1->SetLineColor(kRed);
  g2->SetLineColor(kGreen+3);
  g3->SetLineColor(kMagenta);
  
  
  Inclusive->SetTitle(mh1_pT_Title_HT[ipt]);
  Inclusive->GetXaxis()->SetTitle("nSigmaE");
  Inclusive->GetYaxis()->SetTitle("Counts");
  
  //Inclusive->GetYaxis()->SetRangeUser(1,1.3*Inclusive->GetMaximum());
  // Inclusive->GetXaxis()->SetRangeUser(-12,15);  
  
  Float_t k_p_mean=0.5*(proton_Mean->GetBinContent(ipt+1)+kaon_Mean->GetBinContent(ipt+1));
  total_3->SetParameter(1,k_p_mean);
  total_3->SetParameter(2,1);
  
  total_3->SetParameter(4,pi_Mean->GetBinContent(ipt+1));
  total_3->SetParameter(5,1);
  
  total_3->SetParameter(7,electron_Mean->GetBinContent(ipt+1));
  total_3->SetParameter(8,electron_Sigma->GetBinContent(ipt+1));
  
  

  total_3->SetParLimits(2,0.6,1.5);
  total_3->SetParLimits(4,pi_Mean->GetBinContent(ipt+1)-0.5,pi_Mean->GetBinContent(ipt+1)+0.5);
  total_3->SetParLimits(5,0.6,1.5);


  
  total_3->SetParLimits(7,electron_Mean->GetBinContent(ipt+1)-Sigma_flag*E_mean_err,electron_Mean->GetBinContent(ipt+1)+Sigma_flag*E_mean_err);
  total_3->SetParLimits(8,electron_Sigma->GetBinContent(ipt+1)-Sigma_flag*E_sigma_err,electron_Sigma->GetBinContent(ipt+1)+Sigma_flag*E_sigma_err);
  

  
  if(Draw_flag==0)
    { 
      Inclusive->Fit(total_3,"RQ0","",-10,4);
    }  
  else
    Inclusive->Fit(total_3,"R","",-10,4);
  
  
  g1->SetParameter(0,total_3->GetParameter(6));
  g1->SetParameter(1,total_3->GetParameter(7));
  g1->SetParameter(2,total_3->GetParameter(8));
  
  g2->SetParameter(0,total_3->GetParameter(3));
  g2->SetParameter(1,total_3->GetParameter(4));
  g2->SetParameter(2,total_3->GetParameter(5));
  
  g3->SetParameter(0,total_3->GetParameter(0));
  g3->SetParameter(1,total_3->GetParameter(1));
  g3->SetParameter(2,total_3->GetParameter(2));
  
  if(Draw_flag!=0){
    TLegend *legend = new TLegend(0.15,0.6,0.35,0.8);
    legend->AddEntry(g1,"e ","lp");
    legend->AddEntry(g2,"#pi ","lp");
    legend->AddEntry(g3,"k+p","lp");
    legend->AddEntry(total_3,"Fit","lp");
    
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.055);
    legend ->SetTextFont(62);       
    legend->Draw("same");
    
    g1->Draw("same");
    g2->Draw("same");
    g3->Draw("same");
    sprintf(buf,"plots/purity_fit_%ipt_%i_sigma_constrain_hft_%i.pdf",ipt,Sigma_flag,HFT_flag);
    c4->SaveAs(buf);
    
    
  }
  return g1->Integral(-1,3)/total_3->Integral(-1,3);

}
/*
Double_t Get_sts_Error(TH1F * const inclusive,Int_t ipt,TF1 * total_3, TF1 *g1,TF1 *g2,TF1 *g3,Int_t Sigma_flag,Int_t draw_flag,Double_t purity_mean,Double_t purity_err)
{
  char buf[1024];
  TH1F *Inclusive= (TH1F *)  inclusive->Clone("Inclusive");
  TRandom3 *gRnd= new TRandom3(0);
  sprintf(buf,"purity_fit_%ipt",ipt);
  
  Double_t bin_low=purity_mean-50*purity_err;
  Double_t bin_high=purity_mean+50*purity_err;
  if(ipt==0)
    {
      bin_low=purity_mean-1e5*purity_err;
      bin_high=purity_mean+1e5*purity_err;
    }

  if(ipt==1)
    {
      bin_low=purity_mean-100*purity_err;
      bin_high=purity_mean+100*purity_err;
    }

  // if(ipt==2)
  //   {
  //     bin_low=purity_mean-40000*purity_err;
  //     bin_high=purity_mean+40000*purity_err;
  //   }


  TH1F *mh1purity_sts=new TH1F(buf,"",800,bin_low,bin_high);
  mh1purity_sts->SetTitle(mh1_pT_Title_HT[ipt]);
  TF1 *f_Fit = new TF1(TString("f_Fit"),"gaus",-1,1);
  f_Fit->SetParameter(1,purity_mean);
  TH1F *nsigmae_inclusive_shift=(TH1F *) Inclusive->Clone("nsigmae_inclusive_shift");

  for(Int_t i=1;i<=1000;i++)
    {
      for(Int_t bin=1; bin<=Inclusive->GetNbinsX();bin++)
  	{
  	  if(Inclusive->GetBinContent(bin) && Inclusive->GetBinError(bin))
	    
  	    nsigmae_inclusive_shift->SetBinContent(bin,gRnd->Gaus(Inclusive->GetBinContent(bin),Inclusive->GetBinError(bin)));
	  
  	} 
      
      Double_t purity =Fit_purity(nsigmae_inclusive_shift,ipt,electron_Mean->GetBinError(ipt+1), electron_Sigma->GetBinError(ipt+1),total_3,g1,g2,g3,Sigma_flag,draw_flag);
      mh1purity_sts->Fill(purity);
      cout<< " STS!!!!!"<<purity<<"  ipt="<<ipt<<endl;
   
    }

  TCanvas *c5=new TCanvas("c5","",600,800);
  mh1purity_sts->Fit(f_Fit,"R","");
  mh1purity_sts->GetXaxis()->SetTitle("purity");
  mh1purity_sts->GetYaxis()->SetTitle("Counts");
  c5->SaveAs(buf+TString("purity_sts.pdf"));
  return f_Fit->GetParameter(2);
}
*/
void Draw_purity_sys(TH1D * purity_oneSigma,TH1D *purity_twoSigma,TH1D *purity_threeSigma)
{
  gStyle->SetOptStat(00000);
  TCanvas *c3=new TCanvas("c3","",800,600);
  c3->cd();
  TH2F *h3=new TH2F("h3","",10,2,10,10,0,1.1);
  h3->Draw();
  h3->GetXaxis()->SetTitle("p_{T}");
  h3->GetYaxis()->SetTitle("purity");
  purity_oneSigma->SetMarkerStyle(20);
  purity_twoSigma->SetMarkerStyle(20);
  purity_threeSigma->SetMarkerStyle(20);

  purity_oneSigma->SetMarkerColor(1);
  purity_twoSigma->SetMarkerColor(2);
  purity_threeSigma->SetMarkerColor(3);


  purity_oneSigma->Draw("samePE1");
  purity_twoSigma->Draw("samePE1");
  purity_threeSigma->Draw("samePE1");

  TLegend *legend = new TLegend(0.15,0.35,0.35,0.6);
  legend->AddEntry(purity_oneSigma,"one sigma standard deviation","lp");
  legend->AddEntry(purity_twoSigma,"two sigma standard deviation","lp");
  legend->AddEntry(purity_threeSigma,"three sigma standard deviation","lp");
  
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.03);
  legend ->SetTextFont(62);       
  legend->Draw("same");

  c3->SaveAs(Form("plots/purity_HT_sys_hft_%i.pdf",HFT_flag));
}


//Double_t Get_purity_sys(TH1F * const in)
void Draw_purity(TH1D * purity)
{
  gStyle->SetOptStat(00000);
  TCanvas *c2=new TCanvas("c2","",800,600);
  c2->cd();
  TH2F *h2=new TH2F("h2","",10,2,10,10,0,1.1);
  h2->Draw();
  h2->GetXaxis()->SetTitle("p_{T}");
  h2->GetYaxis()->SetTitle("purity");
  purity->SetMarkerStyle(20);
  purity->SetMarkerColor(2);
  purity->Draw("samePE1");
  c2->SaveAs(Form("plots/purity_HT_hft_%i.pdf",HFT_flag));
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
