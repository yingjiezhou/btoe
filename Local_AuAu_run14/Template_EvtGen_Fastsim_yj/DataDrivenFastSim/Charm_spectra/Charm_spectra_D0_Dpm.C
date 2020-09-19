
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
void Charm_spectra_D0_Dpm()
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
  

  TFile *file_from_guannan=new TFile("Run14_Dpm_MyRaa_pT1.0.withScale_fromGuanan.root","READ");

  TGraphErrors *gMyAuAuSpectra_0_80= (TGraphErrors *)file_from_guannan->Get("gMyAuAuSpectra_0_80");



  for(int i=0;i<D0_10_60_err->GetN();i++)
    {
      Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999,y_sys;
      D0_10_60_sys->GetPoint(i,x_central,y_central);
      y_err=D0_10_60_sys->GetErrorY(i);
      //cout<< x_central<<"\t"<<y_central<<" \t"<<y_err<<endl;
      D0_10_60_sys->SetPoint(i,x_central,y_central*10);
      D0_10_60_sys->SetPointError(i,0,y_err*10);

      D0_0_80_sys->GetPoint(i,x_central,y_central);
      y_sys=D0_0_80_sys->GetErrorY(i);
      y_err=D0_0_80_err->GetErrorY(i);
      //cout<< x_central<<"\t"<<y_central<<" \t"<<y_err<<endl;
      D0_0_80_sys->SetPoint(i,x_central,y_central);
      D0_0_80_sys->SetPointError(i,0,sqrt(y_err*y_err+y_sys*y_sys));
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

      Ds_10_40_sys->GetPoint(i,x_central,y_central);
      y_err=Ds_10_40_err->GetErrorY(i);
      Ds_10_40_sys->SetPoint(i,x_central,y_central/(2*TMath::Pi()*x_central));
      Ds_10_40_sys->SetPointError(i,0,y_err/(2*TMath::Pi()*x_central));
    }
 
  
  
  TH1F *hDpm_spectra_0_10=(TH1F *) inFile->Get("hDpm_spectra_0_10");
  TH1F *hDpm_spectra_10_40=(TH1F *) inFile->Get("hDpm_spectra_10_40");

  TH1F *hDs_spectra_0_10=(TH1F *) inFile->Get("hDs_spectra_0_10");
  TH1F *hDs_spectra_10_40=(TH1F *) inFile->Get("hDs_spectra_10_40");


  TH1F *hLc_spectra_10_60_mean=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_mean");
  TH1F *hLc_spectra_10_60_model1=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_model1");
  TH1F *hLc_spectra_10_60_model2=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_model2");
  TH1F *hLc_spectra_10_60_model3=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_model3");
  
  
  TGraphErrors  *Lc_10_60_err=(TGraphErrors *) inFile_Lc->Get("Lc_10_60_err");
  TGraphErrors  *Lc_10_60_sys=(TGraphErrors *) inFile_Lc->Get("Lc_10_60_sys");

  // hLc_spectra_10_60_mean->Draw();
  // return 0;

  //  TH1F *hLc_spectra_10_60_mean_new=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_mean");
  
  // hLc_spectra_10_60_mean->Draw();
  // hLc_spectra_10_60_mean_new->SetLineColor(2);
  // hLc_spectra_10_60_mean_new->Draw("same");
  
  // return 0;
  
  // 这里的都没什么用，可以注释掉，后续没有用到
  TH1F * hDpm_spectra_0_80=(TH1F *) hD0_spectra_0_80->Clone("hDpm_spectra_0_80");
  hDpm_spectra_0_80->Multiply(hDpm_spectra_10_40);
  hDpm_spectra_0_80->Divide(hD0_spectra_10_40);

  TH1F * hDs_spectra_0_80=(TH1F *) hD0_spectra_0_80->Clone("hDs_spectra_0_80");
  hDs_spectra_0_80->Multiply(hDs_spectra_10_40);
  hDs_spectra_0_80->Divide(hD0_spectra_10_40);

  TH1F * hLc_spectra_0_80=(TH1F *) hD0_spectra_0_80->Clone("hLc_spectra_0_80");
  hLc_spectra_0_80->Multiply(hLc_spectra_10_60_mean);
  hLc_spectra_0_80->Divide(hD0_spectra_10_60);
  


  
  
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

  // hD0_spectra_0_80->Scale(100);
  // hD0_spectra_10_60->Scale(10);
  
  
  TH2F *hh_D0=new TH2F("hh_D0","",100,0.1,12,100,0.5e-10,1);
  hh_D0->SetTitle("");
  hh_D0->GetXaxis()->SetTitle("p_{T} GeV/c");
  hh_D0->GetYaxis()->SetTitle("d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");
  hh_D0->Draw();

  hD0_spectra_10_40->SetFillColor(7);
  hD0_spectra_0_80->SetFillColor(7);
  hD0_spectra_10_60->SetFillColor(7);
  hD0_spectra_0_10->SetFillColor(7);
  
    
  // hD0_spectra_10_40->Draw("samee4");
  // hD0_spectra_0_80->Draw("samee3");
  // hD0_spectra_10_60->Draw("samee3");
  //hD0_spectra_0_10->Draw("samee3");

    

  D0_10_40_sys->SetLineColor(2);
  //  D0_10_40_err->Draw("samePe");


  // D0_10_40_err->SetMarkerSize(0.5);
  // D0_10_40_sys->SetMarkerSize(0.5);

  D0_10_60_sys->SetMarkerColor(2);
  D0_10_60_sys->SetLineColor(2);
   
   
  //  D0_10_60_sys->Draw("samePE");
  D0_0_80_sys->Draw("samePE");


  D0_0_80_err->SetMarkerStyle(22);
  D0_0_80_err->Draw("samePE");
  //D0_10_40_sys->Draw("samePE");  
  
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

  F_levy_D0_0_80_levy->SetParameter(0,2.66458e+01);
  F_levy_D0_0_80_levy->SetParameter(1,3.39421e-01);
  F_levy_D0_0_80_levy->SetParameter(2,1.33430e+01);
  
  
  // hD0_spectra_10_40->Fit("F_levy_D0_10_40_levy","R","same",0,10);
  // hD0_spectra_10_60->Fit("F_levy_D0_10_60_levy","R","same",0,10);
  //  hD0_spectra_0_80->Fit("F_levy_D0_0_80_levy","R","same",0,10);    


  
  

  



  //  new  TCanvas;
  cD0->cd();


  TF1 *pl_0_80=new TF1("pl_D0_0_80",PowLaw,6.5,20,3);
  pl_0_80->SetLineColor(4);
  pl_0_80->SetLineStyle(7);
  pl_0_80->SetParameter(0,0.165619);
  pl_0_80->SetParameter(1,3437467.878645);
  pl_0_80->SetParameter(2,1.335002);

  D0_0_80_sys->Fit("F_levy_D0_0_80_levy","R","",0,10);
  D0_0_80_sys->Fit(pl_0_80,"R","same",3.5,8.5);




  F_levy_D0_0_80_levy->SetLineColor(2);
  F_levy_D0_0_80_levy->SetLineWidth(4);

  
  
  // D0_0_80_sys->Fit(pl_0_80,"R","same",2,8);
  // D0_0_80_sys->Fit(pl_0_80,"R","same",2,8);
  
  

  TH1F *D0_levy_powerLaw=new TH1F("D0_levy_powerLaw","",400,0,20);

  TH1F *Dpm_D0_ratio=new TH1F("Dpm_D0_ratio","",400,0,20);
  Dpm_D0_ratio->Sumw2();

  for( int ibin=0;ibin<D0_levy_powerLaw->GetNbinsX();ibin++)
    {
      D0_levy_powerLaw->SetBinContent(ibin+1,F_levy_D0_0_80_levy->Eval(D0_levy_powerLaw->GetBinCenter(ibin+1))); // 先对直方图fit，fit 之后从这个函数里面取数
      if(ibin<200)
	
      D0_levy_powerLaw->SetBinError(ibin+1,hD0_spectra_10_40->GetBinError(ibin+1));
      else
	{
	  D0_levy_powerLaw->SetBinError(ibin+1,0.5*abs(F_levy_D0_0_80_levy->Eval(D0_levy_powerLaw->GetBinCenter(ibin+1))-pl_0_80->Eval(D0_levy_powerLaw->GetBinCenter(ibin+1))));
	}
      Dpm_D0_ratio->SetBinContent(ibin+1,0.2274/0.6176);
      Dpm_D0_ratio->SetBinError(ibin+1,sqrt((0.0128/0.6176)*(0.0128/0.6176)+(0.0160/0.2274)*(0.0160/0.2274)));
      
    }
  
  D0_levy_powerLaw->SetFillStyle(3144);
  D0_levy_powerLaw->SetFillColor(3);
  // D0_levy_powerLaw->SetLineColor(1);
  D0_levy_powerLaw->Draw("samee2");
  F_levy_D0_0_80_levy->Draw("same");
  pl_0_80->Draw("same");


  TH1F * Dpm_levy_powerLaw= (TH1F *) D0_levy_powerLaw->Clone("Dpm_levy_powerLaw");

  Dpm_levy_powerLaw->Multiply(Dpm_D0_ratio); //把D0scale 到Dpm,通过fragmentation function
  
  Dpm_levy_powerLaw->SetFillStyle(3144);
  Dpm_levy_powerLaw->SetFillColor(6);

  Dpm_levy_powerLaw->SetMarkerStyle(20);
  Dpm_levy_powerLaw->SetMarkerSize(0.02);
  Dpm_levy_powerLaw->SetMarkerColor(1);
  
  Dpm_levy_powerLaw->Draw("samee2");
  D0_0_80_sys->Draw("samePE");
  //  Dpm_levy_powerLaw->Draw("samep");
  
  //  https://arxiv.org/pdf/1509.01061.pdf Table 11



  // cross checked with Guanna

  gMyAuAuSpectra_0_80->SetMarkerStyle(20);
  gMyAuAuSpectra_0_80->SetMarkerColor(1);

 // for(int i=0;i<gMyAuAuSpectra_0_80->GetN();i++)
 //    {
 //      Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999;
      
 //      gMyAuAuSpectra_0_80->GetPoint(i,x_central,y_central);
 //      gMyAuAuSpectra_0_80->GetErrorY(i);

 //      // gMyAuAuSpectra_0_80->SetPoint(i,x_central,y_central/(2*TMath::Pi()*x_central));
 //      // gMyAuAuSpectra_0_80->SetPointError(i,0,y_err/(2*TMath::Pi()*x_central));

 //      // gMyAuAuSpectra_0_80->SetPoint(i,x_central,y_central/(x_central));
 //      // gMyAuAuSpectra_0_80->SetPointError(i,0,y_err/(x_central));

 //    }
  
  //gMyAuAuSpectra_0_80->Draw("sameP");

  
  TLegend *legend_D0  = new TLegend(0.55,0.65,0.9,0.85);
  legend_D0 ->AddEntry(D0_0_80_sys,"D^{0} Data 0-80%","PE"); // 几个直方图
  legend_D0 ->AddEntry(F_levy_D0_0_80_levy,"Levy Fit D^{0}","L");
  legend_D0 ->AddEntry(pl_0_80,"Power-Law Fit D^{0}","L");

  legend_D0 ->AddEntry(D0_levy_powerLaw,"D^{0} Uncertainties","f"); // 拟合的线
  legend_D0 ->AddEntry(Dpm_levy_powerLaw,"Scaled D^{0} to D^{#pm} by pp Frag. Ratio","f");
  //  legend_D0 ->AddEntry(gMyAuAuSpectra_0_80,"Cross check with Guannan D^{#pm}","p");



  
  legend_D0 ->SetBorderSize(0);
  legend_D0 ->SetTextSize(0.035);
  legend_D0 ->SetFillStyle(0);
  legend_D0 ->SetTextFont(22);

  
  legend_D0->Draw();

  sprintf(buf,"Au+Au @ 200 GeV");
  drawLatex(0.55,0.87,buf,22,0.05,1);
  cD0->SaveAs("Plots/D0_Dpm.pdf");

  D0_levy_powerLaw->Draw();
  Dpm_levy_powerLaw->Draw("same");


  
  TH1F *F_levy_D0_0_80= (TH1F *)D0_levy_powerLaw->Clone("F_levy_D0_0_80");
  TH1F *F_levy_Dpm_0_80=(TH1F *)Dpm_levy_powerLaw->Clone("F_levy_Dpm_0_80");
  
  
  TGraph *gr_F_levy_D0_0_80= new TGraph(F_levy_D0_0_80);
  TGraph *gr_F_levy_Dpm_0_80= new TGraph(F_levy_Dpm_0_80);

  TFile *weight_charm_Fit_data=new TFile("weight_charm_Fit_data_0_80_D0_Dpm.root","RECREATE");

  weight_charm_Fit_data->cd();

  F_levy_D0_0_80->Write();
  F_levy_Dpm_0_80->Write();
  // F_levy_Ds_0_80->Write();
  // F_levy_Lc_0_80->Write();
    

  gr_F_levy_D0_0_80->Write();
  gr_F_levy_Dpm_0_80->Write();
  // gr_F_levy_Ds_0_80->Write();
  // gr_F_levy_Lc_0_80->Write();
    
    
  return 0;          
}
