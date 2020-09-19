
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
#include "../Lc_spectra/myFunction.h"
//TH1F *mh1hist[nhist];

char buf[512];
TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
const float twoPI = 2.*TMath::Pi();
const Int_t N_0_10=1.14707e+08;
const Int_t N_10_40=3.5796e+08;
const Int_t N_40_80=4.85838e+08;
const Int_t N_0_80=958505000.;

void Charm_spectra_Ds()
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
  


  
  TFile * inFile_xiaolong=  new TFile("input/cHadron.root","READ");
  TFile * inFile_Nesim=  new TFile("fromChuan/DsoverD0_AndSpectrum_new_test.root","READ");

  TFile * outFile=  new TFile("Plots/Charm_spectra.root","RECREATE");

  // file from Xiaolong 
  TGraphErrors *Ds_0_10_err=(TGraphErrors *) inFile_xiaolong->Get("Ds_0_10_err");// just to compate with fuchuang
  TGraphErrors *Ds_0_10_sys=(TGraphErrors *) inFile_xiaolong->Get("Ds_0_10_sys");
  TGraphErrors *Ds_10_40_err=(TGraphErrors *) inFile_xiaolong->Get("Ds_10_40_err");
  TGraphErrors *Ds_10_40_sys=(TGraphErrors *) inFile_xiaolong->Get("Ds_10_40_sys");
  // file from Nesim 

  TGraphAsymmErrors *Ds_0_10_Nesim_sts=(TGraphAsymmErrors *) inFile_Nesim->Get("Ds_pTSepctrum_Combined_stat0"); // from fuchuang, to fit
  TGraphAsymmErrors *Ds_0_10_Nesim_sys=(TGraphAsymmErrors *) inFile_Nesim->Get("Ds_pTSepctrum_Combined_sys0");

  TGraphAsymmErrors *Ds_10_40_Nesim_sts=(TGraphAsymmErrors *) inFile_Nesim->Get("Ds_pTSepctrum_Combined_stat1");
  TGraphAsymmErrors *Ds_10_40_Nesim_sys=(TGraphAsymmErrors *) inFile_Nesim->Get("Ds_pTSepctrum_Combined_sys1");

  TGraphAsymmErrors *Ds_40_80_Nesim_sts=(TGraphAsymmErrors *) inFile_Nesim->Get("Ds_pTSepctrum_Combined_stat2");
  TGraphAsymmErrors *Ds_40_80_Nesim_sys=(TGraphAsymmErrors *) inFile_Nesim->Get("Ds_pTSepctrum_Combined_sys2");

  TGraphErrors *Ds_0_80_Nesim_sts=new  	TGraphErrors(4);

  // Ds_0_10_Nesim->Draw();
  // Ds_0_10_Nesim->Draw();

  // 这些直方图只是用来过度的，最后用来拟合的直方图还是定义的Ds_0_80_Nesim_sts 这个
  TH1F *mh10_10_Nesim=new TH1F("mh10_10_Nesim","",4,0,5); // final to fit, fill with Nesim
  TH1F *mh110_40_Nesim=new TH1F("mh110_40_Nesim","",4,0,5);
  TH1F *mh140_80_Nesim=new TH1F("mh140_80_Nesim","",4,0,5);
  TH1F *mh10_80_Nesim=new TH1F("mh10_80_Nesim","",4,0,5);

  // mh10_10_Nesim->Sumw2();
  // mh110_40_Nesim->Sumw2();
  // mh140_80_Nesim->Sumw2();
  // mh10_80_Nesim->Sumw2();


  for(int i=0;i<Ds_10_40_err->GetN();i++)
    {
      Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999,y_err_sys=-999;

      Ds_0_10_sys->GetPoint(i,x_central,y_central);
      y_err_sys=Ds_0_10_sys->GetErrorY(i); // sys is to get y value
      y_err=Ds_0_10_err->GetErrorY(i);
      Ds_0_10_err->SetPoint(i,x_central,y_central/(2*TMath::Pi()*x_central)*10); // zyj 为什么要这么设置一个数值， 应该是归一化，1/2pidx，除以bin width
      Ds_0_10_err->SetPointError(i,0,sqrt(y_err*y_err+y_err_sys*y_err_sys)/(2*TMath::Pi()*x_central)*10);
      // cout<< " "<< y_err/y_central<<"\t"<<y_err_sys/y_central<<endl;

      Ds_10_40_sys->GetPoint(i,x_central,y_central);
      y_err_sys=Ds_10_40_sys->GetErrorY(i);
      y_err=Ds_10_40_err->GetErrorY(i);
      Ds_10_40_err->SetPoint(i,x_central,y_central/(2*TMath::Pi()*x_central));
      Ds_10_40_err->SetPointError(i,0,sqrt(y_err*y_err+y_err_sys*y_err_sys)/(2*TMath::Pi()*x_central));

      //cout<< " pt \t"<<x_central<<endl;
    }


  for(int i=0;i<Ds_0_10_Nesim_sts->GetN();i++)
    {
      Double_t x_central=-999.0,y_central=-999.0,x_err=-999.0,y_err=-999.0,y_err_sys=-999.0;

      Ds_0_10_Nesim_sys->GetPoint(i,x_central,y_central);
      y_err_sys=Ds_0_10_Nesim_sys->GetErrorY(i);
      y_err=Ds_0_10_Nesim_sts->GetErrorY(i);

      Ds_0_10_Nesim_sts->SetPoint(i,x_central,y_central*10);// reset y value
      Ds_0_10_Nesim_sts->SetPointError(i,0,0,sqrt(y_err*y_err+y_err_sys*y_err_sys)*10,sqrt(y_err*y_err+y_err_sys*y_err_sys)*10); // 也就是说，开始的时候是系统误差和统计误差一起计算的，现在是充填值，两者误差加起来你
      mh10_10_Nesim->SetBinContent(i+1,y_central); // 这个新建的一个直方图，填值，下面fit
      mh10_10_Nesim->SetBinError(i+1,sqrt(y_err*y_err+y_err_sys*y_err_sys));

      cout<< y_central<<" Nesim"<< y_err<<"\t"<<y_err_sys<<" \t"<<sqrt(y_err*y_err+y_err_sys*y_err_sys)<<endl;

      Ds_10_40_Nesim_sys->GetPoint(i,x_central,y_central);
      y_err_sys=Ds_10_40_Nesim_sys->GetErrorY(i);
      y_err=Ds_10_40_Nesim_sts->GetErrorY(i);
      Ds_10_40_Nesim_sts->SetPoint(i,x_central,y_central);
      Ds_10_40_Nesim_sts->SetPointError(i,0,0,sqrt(y_err*y_err+y_err_sys*y_err_sys),sqrt(y_err*y_err+y_err_sys*y_err_sys));
      mh110_40_Nesim->SetBinContent(i+1,y_central);
      mh110_40_Nesim->SetBinError(i+1,sqrt(y_err*y_err+y_err_sys*y_err_sys));
    
      cout<< y_central<<" Nesim"<< y_err<<"\t"<<y_err_sys<<" \t"<<sqrt(y_err*y_err+y_err_sys*y_err_sys)<<endl;
      
      Ds_40_80_Nesim_sys->GetPoint(i,x_central,y_central);
      y_err_sys=Ds_40_80_Nesim_sys->GetErrorY(i);
      y_err=Ds_40_80_Nesim_sts->GetErrorY(i);
      Ds_40_80_Nesim_sts->SetPoint(i,x_central,y_central);
      Ds_40_80_Nesim_sts->SetPointError(i,0,0,sqrt(y_err*y_err+y_err_sys*y_err_sys),sqrt(y_err*y_err+y_err_sys*y_err_sys));

      mh140_80_Nesim->SetBinContent(i+1,y_central);
      mh140_80_Nesim->SetBinError(i+1,sqrt(y_err*y_err+y_err_sys*y_err_sys));

      cout<< y_central<<" Nesim"<< y_err<<"\t"<<y_err_sys<<" \t"<<sqrt(y_err*y_err+y_err_sys*y_err_sys)<<endl;
    }



  
  
  // combine for 0-80
  mh10_10_Nesim->Scale(N_0_10); // zyj 不同centrality bin combine 的时候需要不是直接相加，需要和归一化相加
  mh110_40_Nesim->Scale(N_10_40);
  mh140_80_Nesim->Scale(N_40_80);

  mh10_80_Nesim->Add(mh10_10_Nesim);
  mh10_80_Nesim->Add(mh110_40_Nesim);
  mh10_80_Nesim->Add(mh140_80_Nesim);

  mh10_80_Nesim->Scale(1./(N_0_80));

  //  for the plots
    mh10_80_Nesim->Scale(100.);
  


  for(int i=0;i<Ds_0_10_Nesim_sts->GetN();i++)
    {
      Double_t x_central=-999.0,y_central=-999.0,x_err=-999.0,y_err=-999.0,y_err_sys=-999.0;

	
      Ds_0_10_Nesim_sys->GetPoint(i,x_central,y_central);
      y_err_sys=Ds_0_10_Nesim_sys->GetErrorY(i);
      y_err=Ds_0_10_Nesim_sts->GetErrorY(i);

      Ds_0_80_Nesim_sts->SetPoint(i,x_central,mh10_80_Nesim->GetBinContent(i+1)); //这里只是为了能够使其x_central 是和010 是一样的，其他没什么
      Ds_0_80_Nesim_sts->SetPointError(i,0,mh10_80_Nesim->GetBinError(i+1)); // 这是新建的一个直方图，用于等下的fit
      //  cout<< " "<<mh10_80_Nesim->GetBinError(i+1)<<endl;
      
    }  
  


  TH2F *hh_Ds=new TH2F("hh_Ds","",100,0,12,100,1e-10,10);
  hh_Ds->SetTitle("");
  hh_Ds->GetXaxis()->SetTitle("p_{T} GeV/c");
  hh_Ds->GetYaxis()->SetTitle("d^{2}N/(N_{ev}2#pip_{T}dp_{T}dy) (GeV/c)^{-2}");

  TCanvas *cDs=new TCanvas("cDs","",800,600);
  gPad->SetLogy();

  hh_Ds->Draw();
  

  Ds_0_10_Nesim_sts->SetMarkerColor(1);
  Ds_0_10_Nesim_sts->SetLineColor(1);

  Ds_10_40_Nesim_sts->SetMarkerColor(2);
  Ds_10_40_Nesim_sts->SetLineColor(2);
  
  Ds_40_80_Nesim_sts->SetMarkerColor(3);
  Ds_40_80_Nesim_sts->SetLineColor(3);

  Ds_0_80_Nesim_sts->SetLineColor(4);
  Ds_0_80_Nesim_sts->SetMarkerColor(4);
  

   Ds_0_80_Nesim_sts->SetMarkerStyle(20);
  
  Ds_0_10_err->SetMarkerStyle(24);
  Ds_10_40_err->SetMarkerStyle(24);

   
   // Ds_0_10_err->Draw("samePE");
   // Ds_10_40_err->Draw("samePE");


  // Ds_10_40_err->Draw("samePE");

  TF1 *F_levy_Ds_0_10_levy=new TF1("F_levy_Ds_0_10_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.969000*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.969000*1.969000)-1.969000)/([2]*[1]),-[2])*2.0*TMath::Pi()*x[0]",0,20);

  TF1 *F_levy_Ds_10_40_levy=new TF1("F_levy_Ds_10_40_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.969000*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.969000*1.969000)-1.969000)/([2]*[1]),-[2])*2.0*TMath::Pi()*x[0]",0,20);

  TF1 *F_levy_Ds_40_80_levy=new TF1("F_levy_Ds_40_80_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.969000*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.969000*1.969000)-1.969000)/([2]*[1]),-[2])*2.0*TMath::Pi()*x[0]",0,20);

  TF1 *F_levy_Ds_0_80_levy=new TF1("F_levy_Ds_0_80_levy","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.969000*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.969000*1.969000)-1.969000)/([2]*[1]),-[2])*2.0*TMath::Pi()*x[0]",0,20);

  
  // F_levy_Ds_0_80_levy->SetParameter(0,1.07459e+01);
  // F_levy_Ds_0_80_levy->SetParameter(1,2.45735e+06);
  // F_levy_Ds_0_80_levy->SetParameter(2,1.23360e+00);

  F_levy_Ds_0_10_levy->SetParameter(0,9.98029067932034303e-01);
  F_levy_Ds_0_10_levy->SetParameter(1,3.15098e-01);
  F_levy_Ds_0_10_levy->SetParameter(2,1.80233e+01);

  F_levy_Ds_10_40_levy->SetParameter(0,9.98029067932034303e-01);
  F_levy_Ds_10_40_levy->SetParameter(1,3.15098e-01);
  F_levy_Ds_10_40_levy->SetParameter(2,1.80233e+01);

  F_levy_Ds_40_80_levy->SetParameter(0,9.98029067932034303e-01);
  F_levy_Ds_40_80_levy->SetParameter(1,3.15098e-01);
  F_levy_Ds_40_80_levy->SetParameter(2,1.80233e+01);

  F_levy_Ds_0_80_levy->SetParameter(0,9.98029067932034303e-01);
  F_levy_Ds_0_80_levy->SetParameter(1,3.15098e-01);
  F_levy_Ds_0_80_levy->SetParameter(2,1.80233e+01);

  
  //  F_levy_Ds_0_80_levy->SetParLimits(0,
  // F_levy_Ds_0_80_levy->SetParLimits(1,2.93365e-01-0.5*2.93365e-01,2.93365e-01+0.5*2.93365e-01);
  // F_levy_Ds_0_80_levy->SetParLimits(2,1.80233e+01-0.5*1.80233e+01,1.80233e+01+1.80233e+01);
  
  // 下面这些函数没有用到，总体思路是一样的，对数据进行拟合，再从拟合函数抽样
  TF1 *pl_0_10=new TF1("pl_0_10",PowLaw,0,20,3);
  pl_0_10->SetLineColor(4);
  pl_0_10->SetLineStyle(7);
  pl_0_10->SetParameter(0,0.165619);
  pl_0_10->SetParameter(1,3437467.878645);
  pl_0_10->SetParameter(2,1.335002);


  TF1 *pl_10_40=new TF1("pl_10_40",PowLaw,0,20,3);
  pl_10_40->SetLineColor(4);
  pl_10_40->SetLineStyle(7);
  pl_10_40->SetParameter(0,0.165619);
  pl_10_40->SetParameter(1,3437467.878645);
  pl_10_40->SetParameter(2,1.335002);

  TF1 *pl_40_80=new TF1("pl_40_80",PowLaw,0,20,3);
  pl_40_80->SetLineColor(4);
  pl_40_80->SetLineStyle(7);
  pl_40_80->SetParameter(0,0.165619);
  pl_40_80->SetParameter(1,3437467.878645);
  pl_40_80->SetParameter(2,1.335002);

  //
  TF1 *pl_0_80=new TF1("pl_0_80",PowLaw,0,20,3);
  pl_0_80->SetLineColor(4);
  pl_0_80->SetLineStyle(7);
  pl_0_80->SetParameter(0,0.165619);
  pl_0_80->SetParameter(1,3437467.878645);
  pl_0_80->SetParameter(2,1.335002);


  
  
  F_levy_Ds_0_10_levy->SetLineColor(6);
  F_levy_Ds_0_10_levy->SetLineStyle(7);

  F_levy_Ds_10_40_levy->SetLineColor(6);
  F_levy_Ds_10_40_levy->SetLineStyle(7);

  F_levy_Ds_40_80_levy->SetLineColor(6);
  F_levy_Ds_40_80_levy->SetLineStyle(7);

  F_levy_Ds_0_80_levy->SetLineColor(6);
  F_levy_Ds_0_80_levy->SetLineStyle(7);

  
  /*  
  Ds_0_10_Nesim_sts->Fit("F_levy_Ds_0_10_levy","R0","",1,6.5);
  Ds_0_10_Nesim_sts->Fit("pl_0_10","R0","q",1,6.5);
  
  F_levy_Ds_0_10_levy->Draw("same");
  pl_0_10->Draw("same");

  
  
  Ds_10_40_Nesim_sts->Fit("F_levy_Ds_10_40_levy","R0","same",1,6.5);
  Ds_10_40_Nesim_sts->Fit("pl_10_40","R0","same",1,6.5);

  F_levy_Ds_10_40_levy->Draw("same");
  pl_10_40->Draw("same");

  
  Ds_40_80_Nesim_sts->Fit("F_levy_Ds_40_80_levy","R0","same",1,6.5);
  Ds_40_80_Nesim_sts->Fit("pl_40_80","R0","",1,6.5);

  F_levy_Ds_40_80_levy->Draw("same");
  pl_40_80->Draw("same");

  */
   Ds_0_80_Nesim_sts->Fit("F_levy_Ds_0_80_levy","R0","",1,6.5);
   Ds_0_80_Nesim_sts->Fit("pl_0_80","R0","",1,6.5);


   F_levy_Ds_0_80_levy->Draw("same");
   pl_0_80->Draw("same");

   
  Ds_0_10_Nesim_sts->Draw("samePE");
  Ds_10_40_Nesim_sts->Draw("samePE");
  Ds_40_80_Nesim_sts->Draw("samePE");
  Ds_0_80_Nesim_sts->Draw("samePE");

   Ds_0_10_err->Draw("samePE");
   Ds_10_40_err->Draw("samePE");

   //F_levy_Ds_0_80_levy->Draw("same");
   
   //  F_levy_Ds_0_80_levy->Draw("same");

  TLegend *legend_Ds  = new TLegend(0.55,0.65,0.8,0.9);
  legend_Ds ->AddEntry(Ds_0_10_Nesim_sts,"Ds 0-10% x 10","p");
  legend_Ds ->AddEntry(Ds_10_40_Nesim_sts,"Ds 10-40%","p");
  legend_Ds ->AddEntry(Ds_40_80_Nesim_sts,"Ds 40-80%","p");
  legend_Ds ->AddEntry(Ds_0_80_Nesim_sts,"Ds 0-80% x 100","p");
  legend_Ds ->AddEntry(F_levy_Ds_40_80_levy,"Levy Fit","L");
  legend_Ds ->AddEntry(pl_40_80,"Power-Law Fit","l");

  legend_Ds ->AddEntry(Ds_0_10_err,"Ds 0-10% x 10 from Xiaolong","P");
  legend_Ds ->AddEntry(Ds_10_40_err,"Ds 10-40% from Xiaolong","P");


  
  legend_Ds ->SetBorderSize(0);
  legend_Ds ->SetTextSize(0.04);
  legend_Ds ->SetFillStyle(0);
  legend_Ds ->SetTextFont(132);
  legend_Ds->Draw();
  

  TH1F *mh1Ds_0_80=new TH1F("mh1Ds_0_80","",400,0,20);
  TH1F *mh1Ds_0_80_noError=(TH1F *) mh1Ds_0_80->Clone("mh1Ds_0_80_noError");
  
  for(int i=0;i<mh1Ds_0_80->GetNbinsX();i++)
  {

    mh1Ds_0_80->SetBinContent(i+1,0.5*fabs(F_levy_Ds_0_80_levy->Eval(mh1Ds_0_80->GetBinCenter(i+1))+pl_0_80->Eval(mh1Ds_0_80->GetBinCenter(i+1))));
    mh1Ds_0_80_noError->SetBinContent(i+1,0.5*fabs(F_levy_Ds_0_80_levy->Eval(mh1Ds_0_80->GetBinCenter(i+1))+pl_0_80->Eval(mh1Ds_0_80->GetBinCenter(i+1))));
    
    mh1Ds_0_80->SetBinContent(i+1,0.5*fabs(F_levy_Ds_0_80_levy->Eval(mh1Ds_0_80->GetBinCenter(i+1))+pl_0_80->Eval(mh1Ds_0_80->GetBinCenter(i+1))));
    mh1Ds_0_80->SetBinError(i+1,0.5*fabs(F_levy_Ds_0_80_levy->Eval(mh1Ds_0_80->GetBinCenter(i+1))-pl_0_80->Eval(mh1Ds_0_80->GetBinCenter(i+1))));
}

  mh1Ds_0_80->SetFillColor(3);
  mh1Ds_0_80->SetFillStyle(3002);
  mh1Ds_0_80_noError->SetLineColor(2);
  mh1Ds_0_80_noError->SetLineWidth(2);

  
  // TH1F *mh1Ds_0_80_noError=(TH1F *) mh1Ds_0_80->Clone("mh1Ds_0_80_noError");
  // mh1Ds_0_80_noError->Sumw2(0);
    
  mh1Ds_0_80->Draw("samee3");;
  mh1Ds_0_80_noError->Draw("sameL");;
  
  
  cDs->SaveAs("Plots/Ds_0_80_widthXiaolong.pdf");
  // cDs->SaveAs("Plots/Ds_0_80.pdf");

  mh1Ds_0_80->Scale(1./100.);
  
  TFile *weight_charm_Fit_data=new TFile("Plots/weight_charm_Fit_data_0_80_Ds.root","RECREATE");
  weight_charm_Fit_data->cd();

  TH1F *F_levy_Ds_0_80= (TH1F *)mh1Ds_0_80->Clone("F_levy_Ds_0_80");
  TGraph *gr_F_levy_Ds_0_80= new TGraph(F_levy_Ds_0_80);
  
  F_levy_Ds_0_80->Write();

   gr_F_levy_Ds_0_80->Write();
  // gr_F_levy_Lc_0_80->Write();


  
}
  

// TGraphAsymmErrors *Dpm_10_40_err=(TGraphAsymmErrors *) inFile->Get("Dpm_10_40_err");
// TGraphAsymmErrors *Dpm_10_40_sys=(TGraphAsymmErrors *) inFile->Get("Dpm_10_40_sys");

  


//  TH1F*  hLc_spectra_10_60_mean=(TH1F *) inFile_Lc->Get("hLc_spectra_10_60_mean");

  
  

// for(int i=0;i<D0_10_60_err->GetN();i++)
//   {
//     Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999;
      
//     D0_10_60_sys->GetPoint(i,x_central,y_central);
//     y_err=D0_10_60_sys->GetErrorY(i);
//     //cout<< x_central<<"\t"<<y_central<<" \t"<<y_err<<endl;
//     D0_10_60_sys->SetPoint(i,x_central,y_central*10);
//     D0_10_60_sys->SetPointError(i,0,y_err*10);

//     D0_0_80_sys->GetPoint(i,x_central,y_central);
//     y_err=D0_0_80_sys->GetErrorY(i);
//     //cout<< x_central<<"\t"<<y_central<<" \t"<<y_err<<endl;
//     D0_0_80_sys->SetPoint(i,x_central,y_central*100);
//     D0_0_80_sys->SetPointError(i,0,y_err*100);


      
//   }
// cout<< " scale done"<<endl;
// TH1F * mh1D0_10_40_sys=new 

  


