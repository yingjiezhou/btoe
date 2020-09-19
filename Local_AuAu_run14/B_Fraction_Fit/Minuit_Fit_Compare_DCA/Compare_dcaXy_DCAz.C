#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TObjArray.h>
#include <TString.h>
#include <TFractionFitter.h>
#include <TLegend.h>
#include <TLatex.h>
#include "fstream"
#include "iostream"
#include "TH1F.h"
#include "TF1.h"
#include "TMinuit.h"
#include "TGraph.h"
#include "TLine.h"

using namespace std;


bool Fit_DCAXY=false;
bool Fit_DCAZ=true;

bool Plots_ratio=false;


const int mh2Nhist=3;
const int Npt=8;
const int IHIST=0;
const int DRAWING=1;
const Double_t MINDCA=-0.1;
const Double_t MAXDCA=0.1;

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex);

void Compare_dcaXy_DCAz(){
  
  char buf[1024];
  char outputname[50];
  char Trg[50];
  Float_t ptbin[Npt+1]={1,1.2,1.5,2,2.5,3.5,4.5,5.5,8.5};  

  
  

  TFile *Output_file=new TFile("OutPut/Fit_B_fraction_MB.root","RECREATE");

  TFile *input_data_DCAXY =new TFile("./Input/Data_inclusive_photonic.root","READ");
  TFile *input_data_DCAZ =new TFile("./Input/Data_inclusive_photonic.root","READ");
  TFile *input_purity =new TFile("Input/purity_MB.root","READ");

  

  TFile *input_fastsim=new TFile("./Input/File_fastsim.root","READ");
  TFile *input_phe_hijing_DCAXY=new TFile("./Input/Photonic_electron_template.root","READ");
  TFile *input_phe_hijing_DCAZ=new TFile("./Input/Photonic_electron_template.root","READ");

  TFile *input_hadron_data=new TFile("./Input/Dca_hadron_MB.root","READ");


  //TFile *input_hadron_data=new TFile("./Input/Dca_hadron_MB_Kaon.root","READ");
  //TFile *input_hadron_data=new TFile("./Input/Dca_hadron_MB_hadron_all.root","READ");
    
  
  double NMC=1;
  TString PTBIN[Npt]={"1.5<p_{T}^{e}<2 GeV/c","2<p_{T}^{e}<2.5 GeV/c","2.5<p_{T}^{e}<3.5 GeV/c","3.5<p_{T}^{e}<4.5 GeV/c","4.5<p_{T}^{e}<5.5 GeV/c","5.5<p_{T}^{e}<8.5 GeV/c"};

  // fastsim    
  TH1F *mh1Charm_dca[mh2Nhist][Npt];
  TH1F *mh1Bottom_dca[mh2Nhist][Npt];

  // from hijing
  TH1F * mh1Phe_dca[mh2Nhist][Npt];    
  TH1F * mh1pi_dca[mh2Nhist][Npt];    

  // from data
  TH1F * mh1data_inclusive[mh2Nhist][Npt];
  TH1F * mh1data_phe[mh2Nhist][Npt];

  TH1F * mh1data_inclusive_XY[mh2Nhist][Npt];
  TH1F * mh1data_inclusive_Z[mh2Nhist][Npt];

  // Hadron from Data
  
TH1F *mh1data_hadron[mh2Nhist][Npt];
  //  TH1F *mh1data_hadron[mh2Nhist][Npt];

  // from fastsim
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {

	  sprintf(buf,"mh1rDca_hist%ipt%i_D",ihist,ipt);
	  mh1Charm_dca[ihist][ipt]=(TH1F *)  input_fastsim->Get(buf);
	  sprintf(buf,"mh1rDca_hist%ipt%i_B",ihist,ipt);
	  mh1Bottom_dca[ihist][ipt]=(TH1F *)  input_fastsim->Get(buf);


	  mh1Charm_dca[ihist][ipt]->Scale(1./mh1Charm_dca[ihist][ipt]->Integral(),"width");
	  mh1Bottom_dca[ihist][ipt]->Scale(1./mh1Bottom_dca[ihist][ipt]->Integral(),"width");
	      
      cout<< " ihst "<<ihist<< " ipt "<< ipt<< " "<< mh1Charm_dca[ihist][ipt]->GetTitle()<<endl;
      cout<< " ihst "<<ihist<< " ipt "<< ipt<< " "<<mh1Bottom_dca[ihist][ipt]->GetTitle()<<endl;
    }
  }
  //  mh1Bottom_dca[1][2]->Draw();
  
TLegend *legend=new TLegend(0.6,0.7,0.85,0.86);
    legend ->SetBorderSize(0);
    legend ->SetTextSize(0.06);
    legend ->SetFillStyle(0);
    legend ->SetTextFont(132);
    legend->AddEntry(mh1Charm_dca[1][1],"DCA_{XY}","lp");
    legend->AddEntry(mh1Charm_dca[2][1],"DCA_{Z}","l");
  
  TCanvas *c_D=new TCanvas("c_D","",1200,1000);
  TCanvas *c_B=new TCanvas("c_B","",1200,1000);
  c_D->Divide(4,2);
  c_B->Divide(4,2);
  
  for(Int_t ipt=0;ipt<Npt;ipt++) {

    if(!Plots_ratio){
    c_D->cd(ipt+1);
    gPad->SetLogy();
    // mh1Charm_dca[1][ipt]->Draw();

    // mh1Charm_dca[1][ipt]->Divide(mh1Charm_dca[2][ipt]);


    mh1Charm_dca[2][ipt]->SetLineColor(2);
    
    mh1Charm_dca[1][ipt]->Draw("");
    mh1Charm_dca[2][ipt]->Draw("same");
    legend->Draw();


    mh1Bottom_dca[2][ipt]->SetLineColor(2);
    c_B->cd(ipt+1);
       gPad->SetLogy();
    mh1Bottom_dca[1][ipt]->Draw();
    mh1Bottom_dca[2][ipt]->Draw("same");
    legend->Draw();
    }

    if(Plots_ratio){
      c_D->cd(ipt+1);
      gPad->SetLogy(0);
   
      mh1Charm_dca[1][ipt]->Divide(mh1Charm_dca[2][ipt]);
      mh1Charm_dca[1][ipt]->Draw();

      mh1Charm_dca[1][ipt]->GetYaxis()->SetRangeUser(0,2);
      mh1Charm_dca[1][ipt]->GetYaxis()->SetTitle("DCA_{XY}/DCA_{Z}");

      c_B->cd(ipt+1);
      gPad->SetLogy(0);
   
      mh1Bottom_dca[1][ipt]->Divide(mh1Bottom_dca[2][ipt]);
      mh1Bottom_dca[1][ipt]->Draw();

      mh1Bottom_dca[1][ipt]->GetYaxis()->SetRangeUser(0,2);
      mh1Bottom_dca[1][ipt]->GetYaxis()->SetTitle("DCA_{XY}/DCA_{Z}");


    }    
  }


  
  c_D->SaveAs("Plots/charm.pdf");
  c_B->SaveAs("Plots/bottom.pdf");





  


  TCanvas *c_Data_inc=new TCanvas("c_Data_inc","",1200,1000);
  c_Data_inc->Divide(4,2);
  
  TCanvas *c_hadron=new TCanvas("c_Hadron","",1200,1000);
  c_hadron->Divide(4,2);

  TCanvas *c_phe=new TCanvas("c_phe","",1200,1000);
  c_phe->Divide(4,2);
  
  
  

  //  mh1data_hadron[][]
    
  // hadron from data, please note 3D dca was not saved, will add it if ..
  for(Int_t ihist=1;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {

      if(ihist==1){
      sprintf(buf,"Hadron_dcaXY_%i_rebin",ipt);
      mh1data_hadron[ihist][ipt]=(TH1F *)  input_hadron_data->Get(buf);
      }
      if(ihist==2)
	{
	  sprintf(buf,"Hadron_dcaZ_%i_rebin",ipt);
	  mh1data_hadron[ihist][ipt]=(TH1F *)  input_hadron_data->Get(buf);
	}
      cout<< "hadron  "<<ihist<< " ipt "<< ipt<< " "<< mh1data_hadron[ihist][ipt]->GetTitle()<<endl;
    }



  }

  
      for(Int_t ipt=0;ipt<Npt;ipt++) {
	

	mh1data_hadron[2][ipt]->SetLineColor(2);

	mh1data_hadron[1][ipt]->Scale(1./mh1data_hadron[1][ipt]->Integral());
	mh1data_hadron[2][ipt]->Scale(1./mh1data_hadron[2][ipt]->Integral());

	
	
	mh1data_hadron[1][ipt]->SetMarkerStyle(20);

	mh1data_hadron[2][ipt]->SetMarkerStyle(20);

	mh1data_hadron[2][ipt]->SetMarkerColor(2);
	mh1data_hadron[1][ipt]->SetMarkerColor(4);

	if(!Plots_ratio){
	c_hadron->cd(ipt+1);
	gPad->SetLogy();
	mh1data_hadron[1][ipt]->Draw();
	mh1data_hadron[2][ipt]->Draw("same");
	}
	if(Plots_ratio)
	  {
	    c_hadron->cd(ipt+1);
	    gPad->SetLogy(0);
	    mh1data_hadron[1][ipt]->Divide(mh1data_hadron[2][ipt]);
	    mh1data_hadron[1][ipt]->GetYaxis()->SetRangeUser(0,2);
	    mh1data_hadron[1][ipt]->Draw();
	  }
	
	legend->Draw();
      }

      c_hadron->SaveAs("Plots/hadron.pdf");

  
  // from data 
  for(Int_t ihist=0;ihist<mh2Nhist-2;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
 
      sprintf(buf,"electron_data_Dca_inclusive00%i_rebin",ipt);
      mh1data_inclusive_XY[ihist][ipt]=(TH1F *)  input_data_DCAXY->Get(buf);
      sprintf(buf,"electron_data_Dca_inclusive10%i_rebin",ipt);
      mh1data_inclusive_Z[ihist][ipt]=(TH1F *)  input_data_DCAZ->Get(buf);
      
      // cout<< "data  ihst "<<ihist<< " ipt "<< ipt<< " "<< mh1data_inclusive[ihist][ipt]->GetTitle()<<endl;
      // cout<< "data ihst "<<ihist<< " ipt "<< ipt<< " "<<mh1data_phe[ihist][ipt]->GetTitle()<<endl;
    }
  }


  for(Int_t ipt=0;ipt<Npt;ipt++) {
    mh1data_inclusive_XY[0][ipt]->Scale(1./mh1data_inclusive_XY[0][ipt]->Integral());
    mh1data_inclusive_Z[0][ipt]->Scale(1./mh1data_inclusive_Z[0][ipt]->Integral());
    if(!Plots_ratio){
    c_Data_inc->cd(ipt+1);
    gPad->SetLogy();    

    mh1data_inclusive_XY[0][ipt]->SetLineColor(4);
    mh1data_inclusive_Z[0][ipt]->SetLineColor(2);
    
    mh1data_inclusive_XY[0][ipt]->SetMarkerColor(4);
    mh1data_inclusive_Z[0][ipt]->SetMarkerColor(2);
      
    mh1data_inclusive_XY[0][ipt]->Draw();
    mh1data_inclusive_Z[0][ipt]->Draw("same");
    legend->Draw();
    }
    if(Plots_ratio)
      {
	c_Data_inc->cd(ipt+1);
	gPad->SetLogy(0);

	mh1data_inclusive_XY[0][ipt]->GetYaxis()->SetTitle("DCA_{XY}/DCA_{Z}");
		
	mh1data_inclusive_XY[0][ipt]->Divide(mh1data_inclusive_Z[0][ipt]);
	mh1data_inclusive_XY[0][ipt]->GetYaxis()->SetRangeUser(0,2);
	mh1data_inclusive_XY[0][ipt]->Draw();

      }

  }
  
  c_Data_inc->SaveAs("Plots/Data_inclusive.pdf");



  TH1F *  mh1Phe_dca_XY[mh2Nhist][Npt];
  TH1F *  mh1Phe_dca_Z[mh2Nhist][Npt];
  
  // from hijing
  for(Int_t ihist=0;ihist<mh2Nhist-2;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
      sprintf(buf,"Corrected_hijing_single0_%i",ipt);
      mh1Phe_dca_XY[ihist][ipt]=(TH1F *)  input_phe_hijing_DCAXY->Get(buf);
      sprintf(buf,"Corrected_hijing_single1_%i",ipt);
      mh1Phe_dca_Z[ihist][ipt]=(TH1F *)  input_phe_hijing_DCAZ->Get(buf);
    }
  }

 for(Int_t ipt=0;ipt<Npt;ipt++) {

   mh1Phe_dca_XY[0][ipt]->Scale(1./mh1Phe_dca_XY[0][ipt]->Integral());
   mh1Phe_dca_Z[0][ipt]->Scale(1./mh1Phe_dca_Z[0][ipt]->Integral());

   if(!Plots_ratio) {
   c_phe->cd(ipt+1);
   gPad->SetLogy();    
   
   mh1Phe_dca_XY[0][ipt]->SetLineColor(4);
   mh1Phe_dca_Z[0][ipt]->SetLineColor(2);
   
   mh1Phe_dca_XY[0][ipt]->SetMarkerColor(4);
   mh1Phe_dca_Z[0][ipt]->SetMarkerColor(2);

   mh1Phe_dca_XY[0][ipt]->SetMarkerStyle(20);
   
   mh1Phe_dca_Z[0][ipt]->SetMarkerStyle(20);
   
   
   mh1Phe_dca_XY[0][ipt]->Draw();
   mh1Phe_dca_Z[0][ipt]->Draw("same");
   legend->Draw();

   }

   if(Plots_ratio)
     {
       c_phe->cd(ipt+1);
       gPad->SetLogy(0);
   
       mh1Phe_dca_XY[0][ipt]->Divide(mh1Phe_dca_Z[0][ipt]);
       mh1Phe_dca_XY[0][ipt]->GetYaxis()->SetRangeUser(0,2);
       
       mh1Phe_dca_XY[0][ipt]->Draw();
       
     }

   
  }
 c_phe->SaveAs("Plots/Phe.pdf");
  



    return 0;

  TCanvas *c1=new TCanvas("c1","",900,1000);
  TCanvas *c2=new TCanvas("c2","",800,1000);
    
  if(DRAWING) {
    gStyle->SetPadLeftMargin(0.06);
    gStyle->SetPadRightMargin(0.04);
    gStyle->SetPadTopMargin(0.09);
    gStyle->SetPadBottomMargin(0.16);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(1);
    gStyle->SetTitleSize(0.1);
    gStyle->SetOptLogy();
    gStyle->SetOptFit(1);

  }

  
  // // for(Int_t ipt=4;ipt<5;ipt++) {
  // for(Int_t ipt=pt_start;ipt<pt_end;ipt++) {

  // }
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

