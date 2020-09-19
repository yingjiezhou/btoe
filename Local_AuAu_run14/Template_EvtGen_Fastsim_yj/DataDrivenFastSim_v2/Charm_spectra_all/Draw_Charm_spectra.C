
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
//TH1F *mh1hist[nhist];

char buf[512];
TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
void Draw_Charm_spectra()
{

  gStyle->SetOptStat(00000);
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleOffset(1.3,"X");
  gStyle->SetTitleOffset(1,"Y");
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.13);
  //  gStyle->SetTicks(1,1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  
  // TH2F *test=new TH2F("test","",10,0,1,10,0,1);
  // test->Draw();  
  // return ;
  


  
  
  TFile * inFile_D0_Dpm=  new TFile("weight_charm_Fit_data_0_80_D0_Dpm.root","READ");
  TFile * inFile_Ds=  new TFile("weight_charm_Fit_data_0_80_Ds.root","READ");
  TFile * inFile_Lc=  new TFile("weight_charm_Fit_data_0_80_Lc.root","READ");

  
  
  TH1F * F_levy_D0_0_80= (TH1F *) inFile_D0_Dpm->Get("F_levy_D0_0_80");
  TH1F * F_levy_Dpm_0_80= (TH1F *) inFile_D0_Dpm->Get("F_levy_Dpm_0_80");
  TH1F * F_levy_Ds_0_80= (TH1F *) inFile_Ds->Get("F_levy_Ds_0_80");
  TH1F * F_levy_Lc_0_80= (TH1F *) inFile_Lc->Get("F_levy_Lc_0_80"); 

  F_levy_Lc_0_80->Scale(1./100);

  Double_t Error_D0=-999.;
  Double_t Error_Dpm=-999.;
  Double_t Error_Ds=-999.;
  Double_t Error_Lc=-999.;

  Double_t Intg_D0=-999.;
  Double_t Intg_Dpm=-999.;
  Double_t Intg_Ds=-999.;
  Double_t Intg_Lc=-9999.;


  Intg_D0=F_levy_D0_0_80->IntegralAndError(1,F_levy_D0_0_80->GetNbinsX(),Error_D0);
  Intg_Dpm=F_levy_Dpm_0_80->IntegralAndError(1,F_levy_Dpm_0_80->GetNbinsX(),Error_Dpm);
  Intg_Ds=F_levy_Ds_0_80->IntegralAndError(1,F_levy_Ds_0_80->GetNbinsX(),Error_Ds);
  Intg_Lc=F_levy_Lc_0_80->IntegralAndError(1,F_levy_Lc_0_80->GetNbinsX(),Error_Lc);  

  Double_t   Total_charm=Intg_D0+Intg_Dpm+Intg_Ds+Intg_Lc;
  Double_t   Total_charm_Error=sqrt(Error_D0*Error_D0+Error_Dpm*Error_Dpm+Error_Ds*Error_Ds);

  cout<< Total_charm<< " charm \t"<<Total_charm_Error<< " "<<Error_Lc<<endl;
  TH1F *charm_Fragmetaio=new TH1F("charm_Fragmetaio","",4,0,4);
    
  Double_t Total=(F_levy_D0_0_80->Integral("width")
  		  +F_levy_Dpm_0_80->Integral("width")
  		  +F_levy_Ds_0_80->Integral("width")
  		  +F_levy_Lc_0_80->Integral("width"));


  charm_Fragmetaio->SetBinContent(1,F_levy_D0_0_80->Integral()/Total);
  
  cout<< "D0 Frag" <<F_levy_D0_0_80->Integral()/Total<<endl;
  cout<< "Dpm Frag" <<F_levy_Dpm_0_80->Integral()/Total<<endl;
  cout<< "Ds Frag" <<F_levy_Ds_0_80->Integral()/Total<<endl;
  cout<< "Lc Frag" <<F_levy_Lc_0_80->Integral()/Total<<endl;
  cout<< "Total" <<Total<<endl;
  

  Double_t x=0.88;
  cout<< F_levy_D0_0_80->IntegralAndError(1,200,x,"")<<endl;;
  cout<<x<<endl;
  
  
  TCanvas *c5_D=new TCanvas("c5_D","",900,600);

  gPad->SetLogy();

  TH2F *hh=new TH2F("hh","",100,0,20,100,0.5e-11,1);

  hh->SetTitle("");
  hh->GetXaxis()->SetTitle("p_{T} GeV/c");
  hh->GetYaxis()->SetTitle("d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-2}");
  hh->Draw();
  

  TH1F *TwoPIPT=new TH1F("TwoPIPT","",400,0,20);
  
  
  for(Int_t ibin=0;ibin<F_levy_D0_0_80->GetNbinsX();ibin++)
    {
      TwoPIPT->SetBinContent(ibin+1,2.*TMath::Pi()*TwoPIPT->GetBinCenter(ibin));
      TwoPIPT->SetBinError(ibin+1,0);
    }

  F_levy_D0_0_80->Multiply(TwoPIPT);
  F_levy_Dpm_0_80->Multiply(TwoPIPT);
  F_levy_Ds_0_80->Multiply(TwoPIPT);

   
  


  F_levy_D0_0_80->SetFillColor(1);
  F_levy_Dpm_0_80->SetFillColor(2);
  F_levy_Ds_0_80->SetFillColor(3);
  F_levy_Lc_0_80->SetFillColor(4);

  F_levy_D0_0_80->SetFillStyle(3001);
  F_levy_Dpm_0_80->SetFillStyle(3001);
  F_levy_Ds_0_80->SetFillStyle(3001);
  
  
  
  F_levy_D0_0_80->Draw("samee3");
  F_levy_Dpm_0_80->Draw("same3");
  F_levy_Ds_0_80->Draw("same3");
  F_levy_Lc_0_80->Draw("same");

  F_levy_D0_0_80->SetLineColor(1);
  F_levy_Dpm_0_80->SetLineColor(2);
  F_levy_Ds_0_80->SetLineColor(3);
  F_levy_Lc_0_80->SetLineColor(4);

  

  sprintf(buf,"Au+Au @ 200 GeV");
  drawLatex(0.6,0.84,buf,22,0.045,1);
  // drawLatex(0.86,0.84,"0-80 %",22,0.045,4);
    

  TLegend *legend_D  = new TLegend(0.6,0.6,0.8,0.8);


  legend_D ->AddEntry(F_levy_D0_0_80,"D^{0} Levy fit","l");
  legend_D ->AddEntry(F_levy_Dpm_0_80,"D^{#pm} Levy fit","l");
  legend_D ->AddEntry(F_levy_Ds_0_80,"Ds Levy fit","l");
  legend_D ->AddEntry(F_levy_Lc_0_80,"#Lambda_{c} Scale Model To Data","l");

  
  legend_D ->SetBorderSize(0);
  legend_D ->SetTextSize(0.05);
  legend_D ->SetFillStyle(0);
  legend_D ->SetTextFont(12);

  
  legend_D->Draw();


  
  
  c5_D->SaveAs("Charm_spectra.pdf");


  // F_levy_D0_0_80->Scale(1./F_levy_D0_0_80->Integral());
  // F_levy_Dpm_0_80->Scale(1./F_levy_Dpm_0_80->Integral());
  // F_levy_Ds_0_80->Scale(1./F_levy_Ds_0_80->Integral());

  TGraph *gr_F_levy_D0_0_80= new TGraph(F_levy_D0_0_80);
  TGraph *gr_F_levy_Dpm_0_80= new TGraph(F_levy_Dpm_0_80);
  TGraph *gr_F_levy_Ds_0_80= new TGraph(F_levy_Ds_0_80);
  TGraph *gr_F_levy_Lc_0_80= new TGraph(F_levy_Lc_0_80);

  TFile *weight_charm_Fit_data=new TFile("weight_charm_Fit_data.root","RECREATE");

  weight_charm_Fit_data->cd();
  F_levy_D0_0_80->Write();
  F_levy_Dpm_0_80->Write();
  F_levy_Ds_0_80->Write();
  F_levy_Lc_0_80->Write();


  gr_F_levy_D0_0_80->Write();
  gr_F_levy_Dpm_0_80->Write();
  gr_F_levy_Ds_0_80->Write();
  gr_F_levy_Lc_0_80->Write();

  
  
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




