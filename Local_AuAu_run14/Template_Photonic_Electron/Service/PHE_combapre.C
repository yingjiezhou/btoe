/*--------------------Xiaozhi------------------------------------ 

This macors for the different D and B hadron decay electrons DCA combine

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
//#include "../Binning_MB.h"

using namespace std;



TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
// fastsim    
int PHE_combapre(){




  //---------------------

  
  //---------------------
  








const int mh2Nhist=1;
const int Npt=8;


  //return 0;
  
TH1F *mh1Charm_dca[mh2Nhist][Npt];
TH1F *mh1Bottom_dca[mh2Nhist][Npt];

TH1F *mh1Charm_dca_old[mh2Nhist][Npt];
TH1F *mh1Bottom_dca_old[mh2Nhist][Npt];


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
  // gStyle->SetLineWidth(1);
 

  TFile * input_fastsim= new TFile("/Users/xiaozhibai/work/Analysis/run14/simulation/Fraction_Fit/B_Fraction_fit/Minuit_Fit_2_15/Input/Hijing_Phe_1_26.root","READ");
  //   TFile * input_fastsim= new TFile("File_fastsim.root","READ");
  TFile * input_fastsim_old= new TFile("Hijing_Phe_1_26.root","READ");
  //  TFile * input_fastsim_old= new TFile("/Users/xiaozhibai/work/Analysis/run14/simulation/Fraction_Fit/Charm_Bottom_dca_EvgGen/File_fastsim.root","READ");
  
  
  
  
  
  char buf[1014];


  


for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
        

      sprintf(buf,"Corrected_hijing_single%i",ipt);
      mh1Charm_dca[ihist][ipt]=(TH1F *)  input_fastsim->Get(buf);

      // sprintf(buf,"mh1rDca_hist%ipt%i_B",ihist+1,ipt);
      // mh1Bottom_dca[ihist][ipt]=(TH1F *)  input_fastsim->Get(buf);


      sprintf(buf,"Corrected_hijing_single%i",ipt);
      mh1Charm_dca_old[ihist][ipt]=(TH1F *)  input_fastsim_old->Get(buf);
      // sprintf(buf,"mh1rDca_hist%ipt%i_B",ihist+1,ipt);
      // mh1Bottom_dca_old[ihist][ipt]=(TH1F *)  input_fastsim_old->Get(buf);
      

      
      // cout<< " ihst "<<ihist<< " ipt "<< ipt<< " "<< mh1Charm_dca[ihist][ipt]->GetTitle()<<endl;
      //  cout<< " ihst "<<ihist<< " ipt "<< ipt<< " "<<mh1Bottom_dca[ihist][ipt]->GetTitle()<<endl;

      
      
    }
  }


 TCanvas *c5_D=new TCanvas("c5_D","",1200,800);
 TCanvas *c6_D=new TCanvas("c6_D","",1200,800);
 TCanvas *c7_D=new TCanvas("c7_D","",1200,800);
  
  c5_D->Divide(4,2);
  c6_D->Divide(4,2);
  c7_D->Divide(4,2);


 for(Int_t ihist=0;ihist<mh2Nhist;ihist++)
    {
      for(Int_t ipt=0;ipt<Npt;ipt++)
        {
          if(ihist==0)
            c5_D->cd(ipt+1);

	  gPad->SetLogy();
	  mh1Charm_dca[ihist][ipt]->Scale(1./mh1Charm_dca[ihist][ipt]->Integral(),"width");
	  mh1Charm_dca_old[ihist][ipt]->Scale(1./mh1Charm_dca_old[ihist][ipt]->Integral(),"width");
	  mh1Charm_dca_old[ihist][ipt]->SetLineColor(2);
	  mh1Charm_dca_old[ihist][ipt]->SetMarkerColor(2);
	  
	  //mh1Charm_dca[ihist][ipt]->Draw();
	  mh1Charm_dca_old[ihist][ipt]->Draw("");
	      

	}
    }



 for(Int_t ihist=0;ihist<mh2Nhist;ihist++)
    {
      for(Int_t ipt=0;ipt<Npt;ipt++)
        {
          if(ihist==0)
            c6_D->cd(ipt+1);

	  //	  gPad->SetLogy();
	  // mh1Charm_dca[ihist][ipt]->Scale(1./mh1Charm_dca[ihist][ipt]->Integral(),"width");
	  // mh1Charm_dca_old[ihist][ipt]->Scale(1./mh1Charm_dca_old[ihist][ipt]->Integral(),"width");
	  // mh1Charm_dca_old[ihist][ipt]->SetLineColor(2);
	  // mh1Charm_dca_old[ihist][ipt]->SetMarkerColor(2);
	  
	   mh1Charm_dca[ihist][ipt]->Divide(mh1Charm_dca_old[ihist][ipt]);
	   mh1Charm_dca[ihist][ipt]->Draw();


	  // mh1Bottom_dca_old[ihist][ipt]->Divide(mh1Bottom_dca[ihist][ipt]);
	  // mh1Bottom_dca_old[ihist][ipt]->Draw();

	}
    }

 

 c5_D->SaveAs("dd.pdf");
 c6_D->SaveAs("cc.pdf");

 return 0;
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
