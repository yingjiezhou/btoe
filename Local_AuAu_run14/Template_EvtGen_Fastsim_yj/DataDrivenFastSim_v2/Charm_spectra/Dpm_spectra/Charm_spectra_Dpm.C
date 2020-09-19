
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
void Charm_spectra_Dpm()
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
  TFile * inFile_Lc=  new TFile("Lc_spectra/out/Lc.root","READ");


  
  TFile * outFile=  new TFile("Charm_spectra.root","RECREATE");


  TH1F *hD0_spectra_0_10=(TH1F *) inFile->Get("hD0_spectra_0_10");
  TH1F *hD0_spectra_10_40=(TH1F *) inFile->Get("hD0_spectra_10_40");
  TH1F *hD0_spectra_40_80=(TH1F *) inFile->Get("hD0_spectra_40_80");
  TH1F *hD0_spectra_0_80=(TH1F *) inFile->Get("hD0_spectra_0_80");
  TH1F *hD0_spectra_10_60=(TH1F *) inFile->Get("hD0_spectra_10_60");


  TGraphErrors *D0_0_10_err=(TGraphErrors *) inFile->Get("D0_0_10_err");
  TGraphErrors *D0_0_10_sys=(TGraphErrors *) inFile->Get("D0_0_10_sys");
  
  TGraphErrors *D0_10_40_err=(TGraphErrors *) inFile->Get("D0_10_40_err");
  TGraphErrors *D0_10_40_sys=(TGraphErrors *) inFile->Get("D0_10_40_sys");

  TGraphErrors *D0_10_60_err=(TGraphErrors *) inFile->Get("D0_10_60_err");
  TGraphErrors *D0_10_60_sys=(TGraphErrors *) inFile->Get("D0_10_60_sys");

  TGraphErrors *D0_0_80_err=(TGraphErrors *) inFile->Get("D0_0_80_err");
  TGraphErrors *D0_0_80_sys=(TGraphErrors *) inFile->Get("D0_0_80_sys");


  
  TGraphErrors *Dpm_10_40_err=(TGraphErrors *) inFile->Get("Dpm_10_40_err");
  TGraphErrors *Dpm_10_40_sys=(TGraphErrors *) inFile->Get("Dpm_10_40_sys");
  TGraphErrors *Dpm_0_10_err=(TGraphErrors *) inFile->Get("Dpm_0_10_err");
  TGraphErrors *Dpm_0_10_sys=(TGraphErrors *) inFile->Get("Dpm_0_10_sys");

  

  
  TGraphErrors *Ds_10_40_err=(TGraphErrors *) inFile->Get("Ds_10_40_err");
  TGraphErrors *Ds_10_40_sys=(TGraphErrors *) inFile->Get("Ds_10_40_sys");
  


    
  TH1F *hDpm_spectra_0_10=(TH1F *) inFile->Get("hDpm_spectra_0_10");
  TH1F *hDpm_spectra_10_40=(TH1F *) inFile->Get("hDpm_spectra_10_40");


  TFile *file_from_guannan=new TFile("Run14_Dpm_MyRaa_pT1.0.withScale_fromGuanan.root","READ");

  TGraphErrors *gMyAuAuSpectra_0_80= (TGraphErrors *)file_from_guannan->Get("gMyAuAuSpectra_0_80");
  TGraphErrors *gMyAuAuSpectra_10_40= (TGraphErrors *)file_from_guannan->Get("gMyAuAuSpectra_10_40");
  TGraphErrors *gMyAuAuSpectra_40_80= (TGraphErrors *)file_from_guannan->Get("gMyAuAuSpectra_40_80");

  TGraphErrors *gMyAuAuSpectra_0_10= (TGraphErrors *)file_from_guannan->Get("gMyAuAuSpectra_0_10");

  gMyAuAuSpectra_0_80->SetMarkerStyle(20);
  gMyAuAuSpectra_0_80->SetMarkerColor(1);

  gMyAuAuSpectra_0_10->SetMarkerStyle(20);
  gMyAuAuSpectra_0_10->SetMarkerColor(3);


  // TGraphErrors *D0_ratio_0_10_40=new TGraphErrors(D0_ratio_0_10_40->GetN());
  // TGraphErrors *Dpm_ratio_0_10_40=new TGraphErrors(Dpm_ratio_0_10_40->GetN());



  
  
  for(int i=0;i<Dpm_10_40_err->GetN();i++)
    {
      Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999,y_sys;
      Dpm_10_40_sys->GetPoint(i,x_central,y_central);
      y_err=Dpm_10_40_sys->GetErrorY(i);
      //cout<< x_central<<"\t"<<y_central<<" \t"<<y_err<<endl;
      Dpm_10_40_sys->SetPoint(i,x_central,y_central);
      Dpm_10_40_sys->SetPointError(i,0,y_err);

      // D0_0_80_sys->GetPoint(i,x_central,y_central);
      // y_sys=D0_0_80_sys->GetErrorY(i);
      // y_err=D0_0_80_err->GetErrorY(i);

      //cout<< x_central<<"\t"<<y_central<<" \t"<<y_err<<endl;
      // D0_0_80_sys->SetPoint(i,x_central,y_central);
      // D0_0_80_sys->SetPointError(i,0,sqrt(y_err*y_err+y_sys*y_sys));
    }

  

   for(int i=0;i<gMyAuAuSpectra_10_40->GetN();i++)
    {
      Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999,y_sys;
      gMyAuAuSpectra_10_40->GetPoint(i,x_central,y_central);
      y_err=gMyAuAuSpectra_10_40->GetErrorY(i);
      
      gMyAuAuSpectra_10_40->SetPoint(i,x_central,y_central/5);
      gMyAuAuSpectra_10_40->SetPointError(i,0,y_err/5);

      gMyAuAuSpectra_0_10->GetPoint(i,x_central,y_central);
      y_err=gMyAuAuSpectra_0_10->GetErrorY(i);
      
      gMyAuAuSpectra_0_10->SetPoint(i,x_central,y_central/20);
      gMyAuAuSpectra_0_10->SetPointError(i,0,y_err/20);

      gMyAuAuSpectra_40_80->GetPoint(i,x_central,y_central);
      y_err=gMyAuAuSpectra_40_80->GetErrorY(i);
      
      gMyAuAuSpectra_40_80->SetPoint(i,x_central,y_central/2);
      gMyAuAuSpectra_40_80->SetPointError(i,0,y_err/2);

      
      
      // D0_0_80_sys->GetPoint(i,x_central,y_central);
      // y_sys=D0_0_80_sys->GetErrorY(i);
      // y_err=D0_0_80_err->GetErrorY(i);

      //cout<< x_central<<"\t"<<y_central<<" \t"<<y_err<<endl;
      // D0_0_80_sys->SetPoint(i,x_central,y_central);
      // D0_0_80_sys->SetPointError(i,0,sqrt(y_err*y_err+y_sys*y_sys));
    }


  
  cout<< " scale done"<<endl;
  // TH1F * mh1D0_10_40_sys=new 




  
  TCanvas *cD0=new TCanvas("cD0","",1000,800);
  gPad->SetLogy();

  
  
  // hD0_spectra_0_80->Scale(100);
  // hD0_spectra_10_60->Scale(10);
  
  gMyAuAuSpectra_0_10->SetMarkerSize(1);
  Dpm_0_10_sys->SetMarkerSize(1);  
  Dpm_0_10_sys->SetMarkerStyle(20);  
  
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

    

  Dpm_10_40_sys->SetLineColor(2);
  Dpm_10_40_sys->SetMarkerColor(2);
  
  //  D0_10_40_err->Draw("samePe");


  // D0_10_40_err->SetMarkerSize(0.5);
  // D0_10_40_sys->SetMarkerSize(0.5);

  D0_10_60_sys->SetMarkerColor(2);
  D0_10_60_sys->SetLineColor(2);
   
   
  //  D0_10_60_sys->Draw("samePE");
  //  D0_0_10_sys->Draw("samePE");


  // Dpm_10_40_err->Draw("samePE");
  gMyAuAuSpectra_10_40->Draw("samePE");
  Dpm_10_40_sys->Draw("samePE");  

  
  
  gMyAuAuSpectra_0_10->Draw("samePE");

  Dpm_0_10_sys->Draw("samePE");  

  gMyAuAuSpectra_40_80->Draw("samePE");

  gMyAuAuSpectra_0_80->Draw("samePE");
  
  //  Dpm_0_10_err->Draw("samePE");
    
  cout<<  hD0_spectra_10_40->Integral()<<endl;;

  



  
  
  TLegend *legend_Dpm  = new TLegend(0.55,0.65,0.9,0.85);
  legend_Dpm ->AddEntry(Dpm_0_10_sys,"D^{#pm}  0-10% from Xiaolong","P");
  legend_Dpm ->AddEntry(Dpm_10_40_sys,"D^{#pm}  10-40% from Xiaolong","P");

  legend_Dpm ->AddEntry(gMyAuAuSpectra_0_10,"D^{#pm} 0-10% from Guanan","P");
  legend_Dpm ->AddEntry(gMyAuAuSpectra_10_40,"D^{#pm} 10-40% from Guanan","P");
  legend_Dpm ->AddEntry(gMyAuAuSpectra_40_80,"D^{#pm} 40-80% from Guanan","P");
  legend_Dpm ->AddEntry(gMyAuAuSpectra_0_80,"D^{#pm} 0-80% from Guanan","P");
  
  legend_Dpm ->SetBorderSize(0);
  legend_Dpm ->SetTextSize(0.035);
  legend_Dpm ->SetFillStyle(0);
  legend_Dpm ->SetTextFont(22);

  
  legend_Dpm->Draw();

  sprintf(buf,"Au+Au @ 200 GeV");
  drawLatex(0.55,0.87,buf,22,0.05,1);

  cD0->SaveAs("Plots/Dpm_guanna_xiaolong.pdf");
  
  return 0;

    
    
}
  // spectra from Dpm
  

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


