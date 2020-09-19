
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
#include "Lc_spectra/myFunction.h"
//TH1F *mh1hist[nhist];

char buf[512];
TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
const float twoPI = 2.*TMath::Pi();
void Charm_spectra()
{

  TH1F::SetDefaultSumw2();
  TH2F::SetDefaultSumw2();
  TH3F::SetDefaultSumw2();
  
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
  
  TFile * inFile=  new TFile("cHadron.root","READ");
    TFile * inFile_Lc=  new TFile("Lc_spectra/out/Lc_10_80.root","READ");
    TFile * inFile_Lc2=  new TFile("Lc_spectra/LcPt_10t80_sysfix.root","READ");


  
  TFile * outFile=  new TFile("Charm_spectra.root","RECREATE");


  TH1F *hD0_spectra_0_10=(TH1F *) inFile->Get("hD0_spectra_0_10");
  TH1F *hD0_spectra_10_40=(TH1F *) inFile->Get("hD0_spectra_10_40");
  TH1F *hD0_spectra_40_80=(TH1F *) inFile->Get("hD0_spectra_40_80");
  TH1F *hD0_spectra_0_80=(TH1F *) inFile->Get("hD0_spectra_0_80");
  TH1F *hD0_spectra_10_60=(TH1F *) inFile->Get("hD0_spectra_10_60");


  
  TGraphErrors *D0_10_40_err=(TGraphErrors *) inFile->Get("D0_10_40_err");
  TGraphErrors *D0_10_40_sys=(TGraphErrors *) inFile->Get("D0_10_40_sys");

  TGraphErrors *D0_10_60_err=(TGraphErrors *) inFile->Get("D0_10_60_err");
  TGraphErrors *D0_10_60_sys=(TGraphErrors *) inFile->Get("D0_10_60_sys");

  TGraphErrors *D0_0_80_err=(TGraphErrors *) inFile->Get("D0_0_80_err");
  TGraphErrors *D0_0_80_sys=(TGraphErrors *) inFile->Get("D0_0_80_sys");


  TGraphErrors *Dpm_10_40_err=(TGraphErrors *) inFile->Get("Dpm_10_40_err");
  TGraphErrors *Dpm_10_40_sys=(TGraphErrors *) inFile->Get("Dpm_10_40_sys");

  TGraphErrors *Ds_10_40_err=(TGraphErrors *) inFile->Get("Ds_10_40_err");
  TGraphErrors *Ds_10_40_sys=(TGraphErrors *) inFile->Get("Ds_10_40_sys");
  


  //  TH1F*  hLc_spectra_10_60_mean=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_mean");

  
  

  for(int i=0;i<D0_10_60_err->GetN();i++)
    {
      Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999;
      
      D0_10_60_sys->GetPoint(i,x_central,y_central);
      y_err=D0_10_60_sys->GetErrorY(i);
      //cout<< x_central<<"\t"<<y_central<<" \t"<<y_err<<endl;
      D0_10_60_sys->SetPoint(i,x_central,y_central*10);
      D0_10_60_sys->SetPointError(i,0,y_err*10);

      D0_0_80_sys->GetPoint(i,x_central,y_central);
      y_err=D0_0_80_sys->GetErrorY(i);
      //cout<< x_central<<"\t"<<y_central<<" \t"<<y_err<<endl;
      D0_0_80_sys->SetPoint(i,x_central,y_central*100);
      D0_0_80_sys->SetPointError(i,0,y_err*100);


      
    }
  cout<< " scale done"<<endl;
  // TH1F * mh1D0_10_40_sys=new 

  for(int i=0;i<Ds_10_40_err->GetN();i++)
    {
      Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999;
      
      Ds_10_40_sys->GetPoint(i,x_central,y_central);
      y_err=Ds_10_40_sys->GetErrorY(i);
      Ds_10_40_sys->SetPoint(i,x_central,y_central/(2*TMath::Pi()*x_central));
      Ds_10_40_sys->SetPointError(i,0,y_err/(2*TMath::Pi()*x_central));

      Ds_10_40_err->GetPoint(i,x_central,y_central);
      y_err=Ds_10_40_err->GetErrorY(i);
      Ds_10_40_err->SetPoint(i,x_central,y_central/(2*TMath::Pi()*x_central));
      Ds_10_40_err->SetPointError(i,0,y_err/(2*TMath::Pi()*x_central));
    }
 
  


  
  
  
  TH1F *hDpm_spectra_0_10=(TH1F *) inFile->Get("hDpm_spectra_0_10");
  TH1F *hDpm_spectra_10_40=(TH1F *) inFile->Get("hDpm_spectra_10_40");

  TH1F *hDs_spectra_0_10=(TH1F *) inFile->Get("hDs_spectra_0_10");
  TH1F *hDs_spectra_10_40=(TH1F *) inFile->Get("hDs_spectra_10_40");


  TH1F *hLc_spectra_10_60_mean=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_mean");
  TH1F *hLc_spectra_10_60_model1=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_model1");
  TH1F *hLc_spectra_10_60_model2=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_model2");
  TH1F *hLc_spectra_10_60_model3=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_model3");
  
  
//    TGraphErrors  *Lc_10_60_err=(TGraphErrors *) inFile_Lc->Get("Lc_10_60_err");
//    TGraphErrors  *Lc_10_60_sys=(TGraphErrors *) inFile_Lc->Get("Lc_10_60_sys");
    TGraphErrors  *Lc_10_60_err=(TGraphErrors *) inFile_Lc2->Get("gLc");
    TGraphErrors  *Lc_10_60_sys=(TGraphErrors *) inFile_Lc2->Get("gLcSys");

    
  // hLc_spectra_10_60_mean->Draw();
  // return 0;

  //  TH1F *hLc_spectra_10_60_mean_new=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_mean");
  
  // hLc_spectra_10_60_mean->Draw();
  // hLc_spectra_10_60_mean_new->SetLineColor(2);
  // hLc_spectra_10_60_mean_new->Draw("same");
  
  // return 0;
  
  
  TH1F * hDpm_spectra_0_80=(TH1F *) hD0_spectra_0_80->Clone("hDpm_spectra_0_80");
  hDpm_spectra_0_80->Multiply(hDpm_spectra_10_40);
  hDpm_spectra_0_80->Divide(hD0_spectra_10_40);

  TH1F * hDs_spectra_0_80=(TH1F *) hD0_spectra_0_80->Clone("hDs_spectra_0_80");
  hDs_spectra_0_80->Multiply(hDs_spectra_10_40);
  hDs_spectra_0_80->Divide(hD0_spectra_10_40);

//  TH1F * hLc_spectra_0_80=(TH1F *) hD0_spectra_0_80->Clone("hLc_spectra_0_80");
//  hLc_spectra_0_80->Multiply(hLc_spectra_10_60_mean);
//  hLc_spectra_0_80->Divide(hD0_spectra_10_60);
  
    TH1F * hLc_spectra_0_80 = (TH1F*) inFile_Lc2->Get("hSpec_0");


  
  
  TCanvas *cD0=new TCanvas("cD0","",1000,800);
  gPad->SetLogy();
  TH1F *h_Scale=new TH1F("h_Scale","",200,0,10);  
  h_Scale->Sumw2();

  for(int ibin=0;ibin<hD0_spectra_10_40->GetNbinsX();ibin++)
    {

      h_Scale->SetBinContent(ibin+1,twoPI*h_Scale->GetBinCenter(ibin));
      h_Scale->SetBinError(ibin+1,0);
    }

  

  hD0_spectra_10_40->Divide(h_Scale);
  hD0_spectra_10_60->Divide(h_Scale);
  hD0_spectra_0_80->Divide(h_Scale);  

  hD0_spectra_0_80->Scale(100);
  hD0_spectra_10_60->Scale(10);
  //  D0_10_60_err->Scale(10);
  
  TH2F *hh_D0=new TH2F("hh_D0","",100,0.15,10,100,0.5e-8,1e2);
  

  hh_D0->SetTitle("");
  hh_D0->GetXaxis()->SetTitle("p_{T} GeV/c");
  hh_D0->GetYaxis()->SetTitle("d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");
  hh_D0->Draw();

  hD0_spectra_10_40->SetFillColor(7);
  hD0_spectra_0_80->SetFillColor(7);
  hD0_spectra_10_60->SetFillColor(7);
  hD0_spectra_0_10->SetFillColor(7);
  
    
  hD0_spectra_10_40->Draw("samee4");
  hD0_spectra_0_80->Draw("samee3");

  hD0_spectra_10_60->Draw("samee3");
  // hD0_spectra_0_10->Draw("samee3");

    

  //D0_10_40_sys->SetLineColor(2);
  // D0_10_40_err->Draw("samePe");


  D0_10_40_err->SetMarkerSize(0.5);
  // D0_10_40_sys->SetMarkerSize(0.5);

  D0_10_60_sys->SetMarkerColor(2);
  D0_10_60_sys->SetLineColor(2);
   
   
  D0_10_60_sys->Draw("samePE");
  D0_0_80_sys->Draw("samePE");
  D0_10_40_sys->Draw("samePE");  
  
  cout<<  hD0_spectra_10_40->Integral()<<endl;;

  

  //  hDpm_spectra_0_80->Draw();



  TF1 *F_levy_D0_10_40_levy=new TF1("F_levy_D0_10_40_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,20);
  TF1 *F_levy_D0_10_60_levy=new TF1("F_levy_D0_10_60_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,20);
  TF1 *F_levy_D0_0_80_levy=new TF1("F_levy_D0_0_80_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,20);


  F_levy_D0_10_40_levy->SetLineStyle(7);
  F_levy_D0_10_60_levy->SetLineStyle(7);
  F_levy_D0_0_80_levy->SetLineStyle(7);
  
  F_levy_D0_10_40_levy->SetParameter(0,7.94507362951369145e-01);
  F_levy_D0_10_40_levy->SetParameter(1,3.41491720490613881e-01);
  F_levy_D0_10_40_levy->SetParameter(2,1.65826943646445919e+01);

  F_levy_D0_10_60_levy->SetParameter(0,7.94507362951369145e-01);
  F_levy_D0_10_60_levy->SetParameter(1,3.41491720490613881e-01);
  F_levy_D0_10_60_levy->SetParameter(2,1.65826943646445919e+01);

  F_levy_D0_0_80_levy->SetParameter(0,7.94507362951369145e-01);
  F_levy_D0_0_80_levy->SetParameter(1,3.41491720490613881e-01);
  F_levy_D0_0_80_levy->SetParameter(2,1.65826943646445919e+01);
  
  
  hD0_spectra_10_40->Fit("F_levy_D0_10_40_levy","R","same",0,10);
  hD0_spectra_10_60->Fit("F_levy_D0_10_60_levy","R","same",0,10);
  hD0_spectra_0_80->Fit("F_levy_D0_0_80_levy","R","same",0,10);    


    
  TLegend *legend_D0  = new TLegend(0.65,0.65,0.9,0.8);
    
    
  legend_D0 ->AddEntry(D0_0_80_sys,"D^{0} x 10^{2} 0-80%","PE");
  legend_D0 ->AddEntry(D0_10_60_sys,"D^{0} x 10 10-60%","PE");
  legend_D0 ->AddEntry(D0_10_40_sys,"D^{0}  10-40%","PE");


  
  legend_D0 ->SetBorderSize(0);
  legend_D0 ->SetTextSize(0.04);
  legend_D0 ->SetFillStyle(0);
  legend_D0 ->SetTextFont(22);

  
  legend_D0->Draw();

  sprintf(buf,"Au+Au @ 200 GeV");
  drawLatex(0.65,0.86,buf,22,0.05,1);



  
  cD0->SaveAs("Plots/D0.pdf");



  
  // spectra from Dpm
  

  TH2F *hh_Dpm=new TH2F("hh_Dpm","",100,0.15,10,100,0.5e-8,1e2);
  hh_Dpm->SetTitle("");
  hh_Dpm->GetXaxis()->SetTitle("p_{T} GeV/c");
  hh_Dpm->GetYaxis()->SetTitle("d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");

  TCanvas *cDpm=new TCanvas("cDpm","",800,600);
  gPad->SetLogy();

  hh_Dpm->Draw();


  
  hDpm_spectra_10_40->Divide(h_Scale);


  hDpm_spectra_10_40->SetLineColor(7);
  hDpm_spectra_10_40->SetFillColor(7);
  
  hDpm_spectra_10_40->Draw("samee3");

  //  hD0_spectra_10_40->Draw("same");

  TF1 *F_levy_Dpm_10_40_levy=new TF1("F_levy_Dpm_10_40_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.869300*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.869300*1.869300)-1.869300)/([2]*[1]),-[2])",0,20);
  TF1 *F_levy_Dpm_0_80_levy=new TF1("F_levy_Dpm_0_80_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.869300*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.869300*1.869300)-1.869300)/([2]*[1]),-[2])",0,20);

  F_levy_Dpm_0_80_levy->SetLineStyle(7);
  F_levy_Dpm_0_80_levy->SetLineColor(1);

  F_levy_Dpm_0_80_levy->SetParameter(0,7.94507362951369145e-01);
  F_levy_Dpm_0_80_levy->SetParameter(1,3.41491720490613881e-01);
  F_levy_Dpm_0_80_levy->SetParameter(2,1.65826943646445919e+01);

  F_levy_Dpm_10_40_levy->SetLineStyle(7);
  F_levy_Dpm_10_40_levy->SetParameter(0,1.34556545243901676e-01);
  F_levy_Dpm_10_40_levy->SetParameter(1,3.95808440173182619e-01);
  F_levy_Dpm_10_40_levy->SetParameter(2,1.53002053028547209e+01);
  
  
  hDpm_spectra_0_80->Scale(100);

  hDpm_spectra_0_80->SetFillColor(7);

  hDpm_spectra_0_80->Divide(h_Scale);
  hDpm_spectra_0_80->Draw("samee3");
  hDpm_spectra_0_80->Draw("samee3");
  hDpm_spectra_0_80->Fit("F_levy_Dpm_0_80_levy","same",0,10);
  F_levy_Dpm_0_80_levy->Draw("same");

  F_levy_Dpm_10_40_levy->Draw("same");
  Dpm_10_40_err->Draw("samePE");

  sprintf(buf,"Au+Au @ 200 GeV");
  drawLatex(0.5,0.86,buf,22,0.05,1);


  TLegend *legend_Dpm  = new TLegend(0.5,0.65,0.8,0.8);
  legend_Dpm ->AddEntry(Dpm_10_40_err,"D^{#pm} 10-40%","p");
  legend_Dpm ->AddEntry(F_levy_Dpm_0_80_levy,"D^{#pm} x 1e^{2} Scaled 10-40% To 0-80%","l");
  legend_Dpm ->SetBorderSize(0);
  legend_Dpm ->SetTextSize(0.035);
  legend_Dpm ->SetFillStyle(0);
  legend_Dpm ->SetTextFont(22);
  legend_Dpm->Draw();

  



  // power law
  // TF1 *pl=new TF1("pl",PowLaw,0,20,3);
  // pl->SetLineColor(4);
  // pl->SetLineStyle(7);
  // pl->SetParameter(0,0.165619);
  // pl->SetParameter(1,3437467.878645);
  // pl->SetParameter(2,1.335002);

  // hDpm_spectra_0_80->Fit("pl","R","same",0,10);
  // pl->Draw("same");
  // F_levy_Dpm_0_80_levy->Draw("same");
  // hDpm_spectra_0_80->Fit("pl","R","same",0,10);    
  


  
  // hDpm_spectra_10_40->Divide(hDpm_spectra_0_80);

  // hDpm_spectra_10_40->Draw();
  
  
  cDpm->SaveAs("Plots/Dpm.pdf");
  
  // spectra from Ds 

  TH2F *hh_Ds=new TH2F("hh_Ds","",100,0.15,8,100,1e-8,1e2);
  hh_Ds->SetTitle("");
  hh_Ds->GetXaxis()->SetTitle("p_{T} GeV/c");
  hh_Ds->GetYaxis()->SetTitle("d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");

  TCanvas *cDs=new TCanvas("cDs","",800,600);
  gPad->SetLogy();

  hh_Ds->Draw();
  // hDs_spectra_10_40->Divide(h_Scale);




  
   TF1 *F_levy_Ds_10_40_levy=new TF1("F_levy_Ds_10_40_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.969000*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.969000*1.969000)-1.969000)/([2]*[1]),-[2])*2.0*TMath::Pi()*x[0]",0,20);

   //TF1 *F_levy_Ds_10_40_levy=new TF1("F_levy_Ds_10_40_levy","[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.969000*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.969000*1.969000)-1.969000)/([2]*[1]),-[2])*2.0*TMath::Pi()*x[0]",0,20);

  F_levy_Ds_10_40_levy->SetParameter(0,9.98029067932034303e-02);
  F_levy_Ds_10_40_levy->SetParameter(1,4.36518583354367440e-01);
  F_levy_Ds_10_40_levy->SetParameter(2,2.36632228463234178e+01);

  TF1 *F_levy_Ds_0_80_levy=new TF1("F_levy_Ds_0_80_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.969000*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.969000*1.969000)-1.969000)/([2]*[1]),-[2])*2.0*TMath::Pi()*x[0]",0,20);

  F_levy_Ds_0_80_levy->SetParameter(0,9.98029067932034303e-02);
  F_levy_Ds_0_80_levy->SetParameter(1,4.36518583354367440e-01);
  F_levy_Ds_0_80_levy->SetParameter(2,2.36632228463234178e+01);

     
  F_levy_Ds_10_40_levy->SetLineStyle(7);
  hDs_spectra_10_40->SetFillColor(7);
  hDs_spectra_0_80->SetFillColor(7);

  hDs_spectra_0_80->Scale(100);

  hDs_spectra_0_80->Divide(h_Scale);
  hDs_spectra_10_40->Divide(h_Scale);
  
  hDs_spectra_10_40->Draw("samee3");
  hDs_spectra_0_80->Draw("samee3");

  hDs_spectra_0_80->Fit("F_levy_Ds_0_80_levy","","same",1,8);

  //F_levy_Ds_10_40_levy->Draw("same");
  cout<< "Fit Ds"<<endl;
  F_levy_Ds_0_80_levy->Draw("same");
  TF1 *pl=new TF1("pl",PowLaw,0,20,3);
  pl->SetLineColor(4);
  pl->SetLineStyle(7);
  pl->SetParameter(0,0.165619);
  pl->SetParameter(1,3437467.878645);
  pl->SetParameter(2,1.335002);

  F_levy_Ds_0_80_levy->SetLineColor(6);
  F_levy_Ds_0_80_levy->SetLineStyle(7);
  
  hDs_spectra_0_80->Fit("pl","","same",0.2,8);
  // pl->Draw("same");
  Ds_10_40_err->Draw("sameP");     

    sprintf(buf,"Au+Au @ 200 GeV");
  drawLatex(0.65,0.86,buf,22,0.05,1);

  
   TLegend *legend_Ds  = new TLegend(0.45,0.75,0.75,0.85);
  legend_Ds ->AddEntry(Ds_10_40_err,"Ds 10-40%","p");
  legend_Ds ->AddEntry(F_levy_Ds_0_80_levy,"Ds x 1e^{2} Scaled 10-40% To 0-80% Levy Fit","l");
  legend_Ds ->AddEntry(pl,"Ds x 1e^{2} Scaled 10-40% To 0-80% Power-Law Fit","l");
  legend_Ds ->SetBorderSize(0);
  legend_Ds ->SetTextSize(0.03);
  legend_Ds ->SetFillStyle(0);
  legend_Ds ->SetTextFont(22);
  legend_Ds->Draw();

  
  cDs->SaveAs("Plots/Ds.pdf");
  

     

  // spectra from Lc 
  
  
    TH2F *hh_Lc=new TH2F("hh_Lc","",100,0.15,10,100,0.5e-8,1e2);
    hh_Lc->SetTitle("");
    hh_Lc->GetXaxis()->SetTitle("p_{T} GeV/c");
    hh_Lc->GetYaxis()->SetTitle("d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");

    TCanvas *cLc=new TCanvas("cLc","",800,600);
    gPad->SetLogy();

    hh_Lc->Draw();

    //hLc_spectra_0_80->Divide(h_Scale);
    hLc_spectra_0_80->Scale(100);

    
    //hLc_spectra_10_60->Draw("same");
    TF1 *fp_0_60=new TF1("fp_0_60","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+2.88153*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+2.88153*2.88153)-2.88153)/([2]*[1]),-[2])",0,20);
    fp_0_60->SetParameter(0,2.72777072933978959e-01);
    fp_0_60->SetParameter(1,3.42766125081739426e-01);
    fp_0_60->SetParameter(2,7.80713e+06);

    TF1 *fp_0_80=new TF1("fp_0_80","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+2.88153*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+2.88153*2.88153)-2.88153)/([2]*[1]),-[2])",0,20);
    fp_0_80->SetParameter(0,2.72777072933978959e-01);
    fp_0_80->SetParameter(1,3.42766125081739426e-01);
    fp_0_80->SetParameter(2,7.80713e+06);

    TF1 *pl_lc_0_60=new TF1("pl_lc_0_60",PowLaw,0,20,3);
    pl_lc_0_60->SetParameter(0,0.165619);
    pl_lc_0_60->SetParameter(1,3437467.878645);
    pl_lc_0_60->SetParameter(2,1.335002);

    TF1 *pl_lc_0_80=new TF1("pl_lc_0_80",PowLaw,0,20,3);
    pl_lc_0_80->SetParameter(0,0.165619);
    pl_lc_0_80->SetParameter(1,3437467.878645);
    pl_lc_0_80->SetParameter(2,1.335002);

    
    //hLc_spectra_10_60_mean->Fit("fp_0_60","R","same",0.2,10);

    fp_0_60->SetLineColor(2);
    fp_0_60->SetLineStyle(7);

    pl_lc_0_60->SetLineColor(4);
    pl_lc_0_60->SetLineStyle(7);

    fp_0_80->SetLineColor(2);
    fp_0_80->SetLineStyle(7);

    pl_lc_0_80->SetLineColor(4);
    pl_lc_0_80->SetLineStyle(7);

    
    
     hLc_spectra_0_80->SetFillColor(3);

    double x, y;
    for (int ii = 0 ; ii < 3 ; ii++){
        Lc_10_60_err->GetPoint(ii, x, y);
        Lc_10_60_err->SetPoint(ii, x, y*209);
        Lc_10_60_sys->GetPoint(ii, x, y);
        Lc_10_60_sys->SetPoint(ii, x, y*209);
    }
    Lc_10_60_err->Fit("pl_lc_0_80","R","same",0.2,10);
    Lc_10_60_err->Fit("fp_0_80","R","same",0.2,10);
    pl_lc_0_80->Draw("same");
    

    
    Lc_10_60_err->SetMarkerStyle(20);
    Lc_10_60_err->SetMarkerSize(1.6);
    Lc_10_60_err->SetLineStyle(1);
    Lc_10_60_sys->Draw("samepe");
    Lc_10_60_err->Draw("samePE");


    TLegend *legend_Lc  = new TLegend(0.55,0.65,0.85,0.85);
    legend_Lc ->AddEntry(Lc_10_60_err,"#Lambdac 10-80%","p");
    legend_Lc ->AddEntry(fp_0_80,"Levy Fit","l");
    legend_Lc ->AddEntry(pl_lc_0_60,"Power-law Fit","l");

    
    legend_Lc ->SetBorderSize(0);
    legend_Lc ->SetTextSize(0.035);
    legend_Lc ->SetFillStyle(0);
    legend_Lc ->SetTextFont(22);
    legend_Lc->Draw();
  
  sprintf(buf,"Au+Au @ 200 GeV");
  drawLatex(0.55,0.86,buf,22,0.05,1);
    

    
    cLc->SaveAs("Plots/Lc.pdf");


    TCanvas *cD0_wPt=new TCanvas("cD0_wPt","",1000,800);
    gPad->SetLogy();
    
    

    TH2F *hh_D_wPt=new TH2F("hh_D_wPt","",100,0.15,20,100,0.5e-15,1e2);
    hh_D_wPt->SetTitle("");
    hh_D_wPt->GetXaxis()->SetTitle("p_{T} GeV/c");
    hh_D_wPt->GetYaxis()->SetTitle("d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");
    hh_D_wPt->Draw();
    //    F_levy_D0_0_80_levy->SetTitle("");

    F_levy_D0_0_80_levy->SetLineColor(1);
    F_levy_Dpm_0_80_levy->SetLineColor(2);
    F_levy_Ds_0_80_levy->SetLineColor(3);
    fp_0_80->SetLineColor(4);

    pl_lc_0_80->SetLineColor(6);
    
    F_levy_D0_0_80_levy->Draw("same");
    F_levy_Dpm_0_80_levy->Draw("same");
    F_levy_Ds_0_80_levy->Draw("same");
    fp_0_80->Draw("same");

    pl_lc_0_80->Draw("same");
    
    TLegend *legend_D_wPt  = new TLegend(0.55,0.65,0.85,0.85);
    legend_D_wPt ->AddEntry(F_levy_D0_0_80_levy,"D^{0} 0-80% Levy Fit","l");
    legend_D_wPt ->AddEntry(F_levy_Dpm_0_80_levy,"D^{#pm} 0-80% Levy Fit","l");
    legend_D_wPt ->AddEntry(F_levy_Ds_0_80_levy,"Ds 0-80% Levy Fit","l");
    legend_D_wPt ->AddEntry(fp_0_80,"#Lambdac 0-80% Levy Fit","l");
    legend_D_wPt ->AddEntry(pl_lc_0_80,"#Lambdac 0-80% Power-law Fit","l");

    legend_D_wPt ->SetBorderSize(0);
    legend_D_wPt ->SetTextSize(0.035);
    legend_D_wPt ->SetFillStyle(0);
    legend_D_wPt ->SetTextFont(22);
    legend_D_wPt->Draw();
    

    
    legend_D_wPt->Draw();
    drawLatex(0.55,0.88,buf,22,0.05,1);
    cD0_wPt->SaveAs("Plots/D0_wPt.pdf");


    TH1F *F_levy_D0_0_80 =new TH1F("F_levy_D0_0_80","",200,0,20);
    TH1F *F_levy_Dpm_0_80 =new TH1F("F_levy_Dpm_0_80","",200,0,20);
    TH1F *F_levy_Ds_0_80 =new TH1F("F_levy_Ds_0_80","",200,0,20);
    TH1F *F_levy_Lc_0_80 =new TH1F("F_levy_Lc_0_80","",200,0,20);
    

    for(int i=0;i<F_levy_D0_0_80->GetNbinsX();i++)
      {
	F_levy_D0_0_80->SetBinContent(i+1,2*TMath::Pi()*F_levy_D0_0_80->GetBinCenter(i+1)*F_levy_D0_0_80_levy->Eval(F_levy_D0_0_80->GetBinCenter(i+1)));
	F_levy_Dpm_0_80->SetBinContent(i+1,2*TMath::Pi()*F_levy_Dpm_0_80->GetBinCenter(i+1)*F_levy_Dpm_0_80_levy->Eval(F_levy_Dpm_0_80->GetBinCenter(i+1)));
	F_levy_Ds_0_80->SetBinContent(i+1,2*TMath::Pi()*F_levy_Ds_0_80->GetBinCenter(i+1)*F_levy_Ds_0_80_levy->Eval(F_levy_Ds_0_80->GetBinCenter(i+1)));
	F_levy_Lc_0_80->SetBinContent(i+1,2*TMath::Pi()*F_levy_Lc_0_80->GetBinCenter(i+1)*fp_0_80->Eval(F_levy_Lc_0_80->GetBinCenter(i+1)));

      }



    TCanvas *cLc_Mod=new TCanvas("cLc_Mod","",1000,800);
    gPad->SetLogy();
    
    

    TH2F *hh_Lc_Mod=new TH2F("hh_Lc_Mod","",100,0.15,10,100,0.5e-7,1);
    hh_Lc_Mod->SetTitle("");
    hh_Lc_Mod->GetXaxis()->SetTitle("p_{T} GeV/c");
    hh_Lc_Mod->GetYaxis()->SetTitle("d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-2}");

    hh_Lc_Mod->Draw();

    hLc_spectra_10_60_model1->SetFillColor(1);
    hLc_spectra_10_60_model2->SetFillColor(2);
    hLc_spectra_10_60_model3->SetFillColor(4);
    
    hLc_spectra_10_60_model1->Draw("samee3");
    hLc_spectra_10_60_model2->Draw("samee3");
    hLc_spectra_10_60_model3->Draw("samee3");

    TLegend *legend_Lc_Mod  = new TLegend(0.65,0.75,0.85,0.85);
    TString nameMod[3] = {"Ko: di-quark", "Ko: three-quark", "Greco"};
    
    legend_Lc_Mod ->AddEntry(hLc_spectra_10_60_model1,nameMod[0],"f");
    legend_Lc_Mod ->AddEntry(hLc_spectra_10_60_model2,nameMod[1],"f");
    legend_Lc_Mod ->AddEntry(hLc_spectra_10_60_model3,nameMod[2],"f");

    legend_Lc_Mod ->SetBorderSize(0);
    legend_Lc_Mod ->SetTextSize(0.045);
    legend_Lc_Mod ->SetFillStyle(0);
    legend_Lc_Mod ->SetTextFont(22);
    legend_Lc_Mod->Draw();


    sprintf(buf,"Au+Au @ 200 GeV #Lambdac 10-60%");
    drawLatex(0.65,0.88,buf,22,0.04,1);

    cLc_Mod->SaveAs("Plots/Lc_Mod.png");



    // save the file for the output

    TCanvas *c5_D=new TCanvas("c5_D","",800,1200);
    
    gPad->SetLogy();

    F_levy_D0_0_80->Draw("same");
    F_levy_Dpm_0_80->Draw("same");
    F_levy_Ds_0_80->Draw("same");
    F_levy_Lc_0_80->Draw("same");

    c5_D->SaveAs("Plots/D_wPt.pdf");


    TGraph *gr_F_levy_D0_0_80= new TGraph(F_levy_D0_0_80);
    TGraph *gr_F_levy_Dpm_0_80= new TGraph(F_levy_Dpm_0_80);
    TGraph *gr_F_levy_Ds_0_80= new TGraph(F_levy_Ds_0_80);
    TGraph *gr_F_levy_Lc_0_80= new TGraph(F_levy_Lc_0_80);


    TFile *weight_charm_Fit_data=new TFile("weight_charm_Fit_data_0_80.root","RECREATE");

    weight_charm_Fit_data->cd();

    F_levy_D0_0_80->Write();
    F_levy_Dpm_0_80->Write();
    F_levy_Ds_0_80->Write();
    F_levy_Lc_0_80->Write();
    

    gr_F_levy_D0_0_80->Write();
    gr_F_levy_Dpm_0_80->Write();
    gr_F_levy_Ds_0_80->Write();
    gr_F_levy_Lc_0_80->Write();
    
    
    return 0;          
  
  
  // // 0=40
  // TH1F *hDpm_spectra_0_40=( TH1F *) hDpm_spectra_0_10->Clone("hDpm_spectra_0_40");
  // hDpm_spectra_0_40->Add(hDpm_spectra_10_40,3);
  // hDpm_spectra_0_40->Scale(1./4);

  

  // TH1F *hDs_spectra_0_40=( TH1F *) hDs_spectra_0_10->Clone("hDs_spectra_0_40");
  // hDs_spectra_0_40->Add(hDs_spectra_10_40);
  
  

  // TH1F * hD0_spectra_0_80_add= (TH1F *) hD0_spectra_0_10->Clone("hD0_spectra_0_80_add");
  // hD0_spectra_0_80_add->Scale(1);
  // hD0_spectra_0_80_add->Add(hD0_spectra_10_40,3);
  // hD0_spectra_0_80_add->Add(hD0_spectra_40_80,4);
  // hD0_spectra_0_80_add->Scale(1./8);

  
  
  // hD0_spectra_0_80_add->Divide(hD0_spectra_0_80);
  // hD0_spectra_0_80_add->Draw("e2");  
    
 






  
  
  


  //  TF1 * f_levy_Lc_10_40_levy= (TF1 *) inFile->Get("D0_10_40_levy");

  //TH1F *hD0_spectra_10_40=(TH1F *) inFile->Get("hD0_spectra_10_40");

  //  TGraphErrors	*D0_10_40_err=(TGraphErrors *) inFile->Get("D0_10_40_err");
  // TGraphErrors	*Dpm_10_40_err=(TGraphErrors *) inFile->Get("Dpm_10_40_err");
  // TGraphErrors	*Ds_10_40_err=(TGraphErrors *) inFile->Get("Ds_10_40_err");
  
}
  // f_levy_D0_10_40_levy->Draw();
  // f_levy_Dpm_10_40_levy->Draw("same");
  // f_levy_Ds_10_40_levy->Draw("same");




  // TF1 *F_levy_Dpm_10_40_levy=new TF1("F_levy_Dpm_10_40_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.869300*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.869300*1.869300)-1.869300)/([2]*[1]),-[2])",0,20);

  // TF1 *F_levy_Ds_10_40_levy=new TF1("F_levy_Ds_10_40_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.969000*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.969000*1.969000)-1.969000)/([2]*[1]),-[2])*2.0*TMath::Pi()*x[0]",0,20);


  
  

  // F_levy_D0_10_40_levy->SetParameter(0,f_levy_D0_10_40_levy->GetParameter(0));
  // F_levy_D0_10_40_levy->SetParameter(1,f_levy_D0_10_40_levy->GetParameter(1));
  // F_levy_D0_10_40_levy->SetParameter(2,f_levy_D0_10_40_levy->GetParameter(2));
  

  // F_levy_Dpm_10_40_levy->SetParameter(0,f_levy_Dpm_10_40_levy->GetParameter(0));
  // F_levy_Dpm_10_40_levy->SetParameter(1,f_levy_Dpm_10_40_levy->GetParameter(1));
  // F_levy_Dpm_10_40_levy->SetParameter(2,f_levy_Dpm_10_40_levy->GetParameter(2));
  

  // F_levy_Ds_10_40_levy->SetParameter(0,f_levy_Ds_10_40_levy->GetParameter(0));
  // F_levy_Ds_10_40_levy->SetParameter(1,f_levy_Ds_10_40_levy->GetParameter(1));
  // F_levy_Ds_10_40_levy->SetParameter(2,f_levy_Ds_10_40_levy->GetParameter(2));
  


  
  // F_levy_D0_10_40_levy->SetLineColor(1);
  // F_levy_D0_10_40_levy->SetLineColor(2);
  // F_levy_D0_10_40_levy->SetLineColor(4);

  // hD0_spectra_10_40->SetMarkerStyle(20);
  // hD0_spectra_10_40->SetMarkerSize(1.3);
  
  //  hD0_spectra_10_40->Draw("sameP");

  
  
  // F_levy_D0_10_40_levy->Draw("same");
  // F_levy_Dpm_10_40_levy->Draw("same");
  // F_levy_Ds_10_40_levy->Draw("same");

  // F_levy_D0_10_40_levy->SetLineColor(1);
  // F_levy_Dpm_10_40_levy->SetLineColor(2);
  // F_levy_Ds_10_40_levy->SetLineColor(4);
  

  

  // D0_10_40_err->SetMarkerColor(1);
  // Dpm_10_40_err->SetMarkerColor(2);
  // //  Ds_10_40_err->SetMarkerColor(4);
  


  // for(int i=0;i<F_levy_D0_10_40->GetNbinsX();i++)
  //   {
  //     F_levy_D0_10_40->SetBinContent(i+1,2*TMath::Pi()*F_levy_D0_10_40->GetBinCenter(i+1)*F_levy_D0_10_40_levy->Eval(F_levy_D0_10_40->GetBinCenter(i+1)));
  //     F_levy_Dpm_10_40->SetBinContent(i+1,2*TMath::Pi()*F_levy_Dpm_10_40->GetBinCenter(i+1)*F_levy_Dpm_10_40_levy->Eval(F_levy_Dpm_10_40->GetBinCenter(i+1)));
  //     F_levy_Ds_10_40->SetBinContent(i+1,F_levy_Ds_10_40_levy->Eval(F_levy_Ds_10_40->GetBinCenter(i+1)));
  //   }


  // F_levy_D0_10_40->SetLineColor(6);

  // F_levy_D0_10_40->Draw("same");
  // F_levy_Dpm_10_40->Draw("same");
  // F_levy_Ds_10_40->Draw("same");


  // F_levy_D0_10_40->SetLineColor(1);
  // F_levy_Dpm_10_40->SetLineColor(2);
  // F_levy_Ds_10_40->SetLineColor(4);
  
  // f_levy_D0_10_40_levy->Draw("same");
  // f_levy_Dpm_10_40_levy->Draw("same");
  // f_levy_Ds_10_40_levy->Draw("same");


  
  // D0_10_40_err->Draw("samePE");
  // Dpm_10_40_err->Draw("samePE");
  // Ds_10_40_err->Draw("samePE");

    

//   TLegend *legend_D  = new TLegend(0.65,0.55,0.85,0.85);

//   // legend_D ->AddEntry(D0_10_40_err,"D^{0} Data","pe");
//   // legend_D ->AddEntry(Dpm_10_40_err,"D^{#pm} Data","pe");
//   // legend_D ->AddEntry(Ds_10_40_err,"Ds Data","pe");

//   legend_D ->AddEntry(F_levy_D0_10_40,"D^{0} Levy fit","l");
//   legend_D ->AddEntry(F_levy_Dpm_10_40,"D^{#pm} Levy fit","l");
//   legend_D ->AddEntry(F_levy_Ds_10_40,"Ds Levy fit","l");

  
//   legend_D ->SetBorderSize(0);
//   legend_D ->SetTextSize(0.05);
//   legend_D ->SetFillStyle(0);
//   legend_D ->SetTextFont(12);

  
//   legend_D->Draw();
  
//   c5_D->SaveAs("charm_spectra.pdf");
//   F_levy_D0_10_40->Write();
//   F_levy_Dpm_10_40->Write();
//   F_levy_Ds_10_40->Write();
//   outFile->cd();
  
  
//   return ;
  
// }
// TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex)
// {
//   TLatex *latex = new TLatex(x,y,text);
//   latex->SetNDC();
//   latex->SetTextFont(textFont);
//   latex->SetTextSize(textSize);
//   latex->SetTextColor(colorIndex);
//   latex->Draw("same");
//   return latex;
// }







/*

  const int nhist=3;
  // const int 
  TString hist_name_D0[nhist]={"D0_0_10_levy","D0_10_40_levy","D0_40_80_levy"};
  TString hist_name_D_plus[nhist]={"D0_0_10_levy","D0_10_40_levy","D0_40_80_levy"};
  TString hist_name_Ds[nhist]={"D0_0_10_levy","D0_10_40_levy","D0_40_80_levy"};
  TString hist_name_D_plus[nhist]={"D0_0_10_levy","D0_10_40_levy","D0_40_80_levy"};
  


  
  TString hist_name_TH1F[nhist]={"hD0_spectra_0_10","hD0_spectra_10_40","hD0_spectra_40_80"};

  TF1 *mh1F[nhist];
  TH1F *mh1hist_levy[nhist];

 
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();
  
  gStyle->SetOptStat(00000);
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleOffset(1.3,"X");
  gStyle->SetTitleOffset(1,"Y");
  gStyle->SetPadTopMargin(0.13);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.13);
  
  TFile * inFile=  new TFile("cHadron.root","READ");



  // TF1 * TF1

  for(Int_t ihist=0;ihist<nhist;ihist++)
  {

  sprintf(buf,"D0_hist_%i",ihist);
      
  cout<< hist_name[ihist]<<endl;
  mh1F[ihist]= (TF1*) inFile->Get(hist_name[ihist]);
      
  //sprintf(buf,"D0_hist_%i",ihist);
  //mh1F[ihist]->SetName(buf);
  //cout<< ihist<<endl;
      
  cout<< mh1F[ihist]->GetName()<<endl;
  }

  //  return;

  //----------------------
  
  for(Int_t ihist=0;ihist<nhist;ihist++)
  {

  cout<< hist_name_TH1F[ihist]<<endl;

  mh1hist_levy[ihist]= (TH1F*) inFile->Get(hist_name_TH1F[ihist]);

  //  sprintf(buf,"D0_hist_%i",ihist);
      
  mh1F[ihist]->SetName(buf);
  //      cout<< ihist<<endl;

  cout<< mh1hist_levy[ihist]->GetName()<<endl;
  }

  mh1hist_levy[0]->Draw();
  mh1hist_levy[1]->Draw("same");
  mh1hist_levy[2]->Draw("same");
  
  

  TCanvas *c5_D=new TCanvas("c5_D","",800,1200);
  mh1F[0]->Draw();
  
  mh1F[1]->Draw("same");
  mh1F[2]->Draw("same");


  cout<< mh1F[2]->GetParameter(0)<< " "<<mh1F[2]->GetParameter(1) <<" "<<mh1F[2]->GetParameter(2)<<endl;

  TF1 *ff=new TF1("ff","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,20);

  
  ff->SetParameter(0,mh1F[1]->GetParameter(0));
  ff->SetParameter(1,mh1F[1]->GetParameter(1));
  ff->SetParameter(2,mh1F[1]->GetParameter(2));

  ff->Draw();

  
  //  mh1F[0]->Draw("same");
  // mh1F[1]->Draw("same");

  mh1F[1]->SetLineColor(4);

  mh1F[1]->Draw("same");

  
  inFile->Close();

  
  c5_D->SaveAs("charm_spectra.pdf");
  }
*/
//return ;
  

// TH2F * mh2D0=(TH2F *) inFile->Get("D0YVsPt");
// TH2F * mh2Dplus=(TH2F *) inFile->Get("DplusYVsPt");
// TH2F * mh2Ds=(TH2F *) inFile->Get("D_sYVsPt");
// TH2F * mh2Lc=(TH2F *) inFile->Get("LcYVsPt");


// TH1F *  mh1D0= (TH1F *)mh2D0->ProjectionX("mh1D0");
// TH1F *  mh1Dplus= (TH1F *)mh2Dplus->ProjectionX("mh1Dplus");
// TH1F *  mh1Ds= (TH1F *)mh2Ds->ProjectionX("mh1Ds");
// TH1F *  mh1Lc= (TH1F *)mh2Lc->ProjectionX("mh1Lc");

// TH2F *hh =new TH2F("hh","",100,0,8,100,0,1);
// hh->GetXaxis()->SetTitle("Rapidity"xg);
// hh->GetYaxis()->SetTitle("Ratio");


// if(!pT)
//   {
//     TH1F *  mh1D0= (TH1F *)mh2D0->ProjectionY("mh1D0");
//     TH1F *  mh1Dplus= (TH1F *)mh2Dplus->ProjectionY("mh1Dplus");
//     TH1F *  mh1Ds= (TH1F *)mh2Ds->ProjectionY("mh1Ds");

//     // TH1F *  mh1Lc= (TH1F *)mh2Lc->ProjectionY("mh1Lc");
//     // TH2F *hh =new TH2F("hh","",100,-1.5,1.5,100,0,1);
//     // hh->GetXaxis()->SetTitle("Rapidity");
//     // hh->GetYaxis()->SetTitle("Ratio");

      
//   }
    
//  mh1D0->Rebin(4);
//  mh1Dplus->Rebin(4);
//  mh1Ds->Rebin(4);
//  mh1Lc->Rebin(4);



// TCanvas *c5_D=new TCanvas("c5_D","",800,1200);
  
// mh1Dplus->Divide(mh1D0);
// mh1Ds->Divide(mh1D0);
// mh1Lc->Divide(mh1D0);

// mh1Dplus->SetLineColor(2);
// mh1Ds->SetLineColor(3);
// mh1Lc->SetLineColor(4);
// // mh1Lc->Fit("pol0");
// // mh1Ds->Fit("pol0");

// // mh1Dplus->

// TLegend *legend_D  = new TLegend(0.15,0.65,0.4,0.85);
// legend_D ->AddEntry(mh1Dplus,"D^{#pm}/(D^{0}+#bar{D^{0}})","l");
// legend_D ->AddEntry(mh1Ds,"Ds^{#pm}/(D^{0}+#bar{D^{0}})","l");
// legend_D ->AddEntry(mh1Lc,"#Lambda_{c}^{#pm}/(D^{0}+#bar{D^{0}})","l");

// legend_D ->SetBorderSize(0);
// legend_D ->SetTextSize(0.05);
// legend_D ->SetFillStyle(0);
// legend_D ->SetTextFont(62);

  


  

// hh->Draw();
// mh1Dplus->Draw("same");
// mh1Ds->Draw("same");
// mh1Lc->Draw("same");
// legend_D->Draw("same");
  
  
// c5_D->SaveAs("TestCharm_frag_y.pdf");


