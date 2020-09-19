
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
  

  TFile * inFile=  new TFile("Charm_spectra.root","READ");

  TH1F *  F_levy_D0_10_40= (TH1F *) inFile->Get("F_levy_D0_10_40");
  TH1F *  F_levy_Dpm_10_40= (TH1F *) inFile->Get("F_levy_Dpm_10_40");
  TH1F * F_levy_Ds_10_40= (TH1F *) inFile->Get("F_levy_Ds_10_40");
  TH1F * hLc_spectra_10_60_mean= (TH1F *) inFile->Get("hLc_spectra_10_60_mean"); 


  
  TCanvas *c5_D=new TCanvas("c5_D","",1000,1000);

  gPad->SetLogy();

  TH2F *hh=new TH2F("hh","",100,0,20,100,0.5e-11,1);

  hh->SetTitle("");
  hh->GetXaxis()->SetTitle("p_{T} GeV/c");
  hh->GetYaxis()->SetTitle("d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-2}");
  hh->Draw();
  

  

  F_levy_D0_10_40->Draw("same");
  F_levy_Dpm_10_40->Draw("same");
  F_levy_Ds_10_40->Draw("same");
  hLc_spectra_10_60_mean->Draw("same");

  

  F_levy_D0_10_40->SetLineColor(1);
  F_levy_Dpm_10_40->SetLineColor(2);
  F_levy_Ds_10_40->SetLineColor(4);
  hLc_spectra_10_60_mean->SetLineColor(6);
  

  sprintf(buf,"Au+Au @ 200 GeV");
  drawLatex(0.6,0.84,buf,22,0.045,1);
  // drawLatex(0.86,0.84,"0-80 %",22,0.045,4);
    

  TLegend *legend_D  = new TLegend(0.6,0.6,0.8,0.8);


  legend_D ->AddEntry(F_levy_D0_10_40,"D^{0} Levy fit","l");
  legend_D ->AddEntry(F_levy_Dpm_10_40,"D^{#pm} Levy fit","l");
  legend_D ->AddEntry(F_levy_Ds_10_40,"Ds Levy fit","l");
  legend_D ->AddEntry(hLc_spectra_10_60_mean,"#Lambda_{c} Scale Model To Data","l");

  
  legend_D ->SetBorderSize(0);
  legend_D ->SetTextSize(0.05);
  legend_D ->SetFillStyle(0);
  legend_D ->SetTextFont(12);

  
  legend_D->Draw();


  
  
  c5_D->SaveAs("Charm_spectra.pdf");


  // F_levy_D0_10_40->Scale(1./F_levy_D0_10_40->Integral());
  // F_levy_Dpm_10_40->Scale(1./F_levy_Dpm_10_40->Integral());
  // F_levy_Ds_10_40->Scale(1./F_levy_Ds_10_40->Integral());

  TGraph *gr_F_levy_D0_10_40= new TGraph(F_levy_D0_10_40);
  TGraph *gr_F_levy_Dpm_10_40= new TGraph(F_levy_Dpm_10_40);
  TGraph *gr_F_levy_Ds_10_40= new TGraph(F_levy_Ds_10_40);
  TGraph *gr_hLc_spectra_10_60_mean= new TGraph(hLc_spectra_10_60_mean);
  TFile *weight_charm_Fit_data=new TFile("weight_charm_Fit_data.root","RECREATE");

  weight_charm_Fit_data->cd();
  F_levy_D0_10_40->Write();
  F_levy_Dpm_10_40->Write();
  F_levy_Ds_10_40->Write();
  hLc_spectra_10_60_mean->Write();

  gr_F_levy_D0_10_40->Write();
  gr_F_levy_Dpm_10_40->Write();
  gr_F_levy_Ds_10_40->Write();
  gr_hLc_spectra_10_60_mean->Write();
  
  
  
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


