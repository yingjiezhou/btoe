
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
void Charm_spectra_1()
{

  TFile *file_re=new TFile("cHadron.root","READ");
  
   TF1 *f1= (TF1 *) file_re->Get("D0_0_10_levy");
   TF1 *f2= (TF1 *) file_re->Get("D0_10_40_levy");
   TF1 *f3= (TF1 *) file_re->Get("D0_40_80_levy");



   return ;
   f1->Draw();
   f2->Draw();
   f3->Draw();
  

   
  // fa1->Write();
  // fc1->Write();

  // file->Close();


  

   cout<< f1->GetName()<<endl;;
   cout<<  f2->GetName()<<endl;;
   // cout<<  f3->GetName()<endl;;

  
  const int nhist=3;
  TString hist_name[nhist]={"D0_0_10_levy","D0_10_40_levy","D0_40_80_levy"};  
 
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

  return;

  //----------------------
  
  for(Int_t ihist=0;ihist<nhist;ihist++)
    {

      cout<< hist_name_TH1F[ihist]<<endl;
      mh1hist_levy[ihist]= (TH1F*) inFile->Get(hist_name_TH1F[ihist]);

      //  sprintf(buf,"D0_hist_%i",ihist);
      
      //     mh1F[ihist]->SetName(buf);
      //      cout<< ihist<<endl;

      cout<< mh1hist_levy[ihist]->GetName()<<endl;
    }

  mh1hist_levy[0]->Draw();
  mh1hist_levy[1]->Draw("same");
  mh1hist_levy[2]->Draw("same");
  
  

  // TCanvas *c5_D=new TCanvas("c5_D","",800,1200);
  // mh1F[0]->Draw();
  
  // mh1F[1]->Draw("same");
  // mh1F[2]->Draw("same");
  
  // inFile->Close();
  
  // c5_D->SaveAs("charm_spectra.pdf");
}
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


