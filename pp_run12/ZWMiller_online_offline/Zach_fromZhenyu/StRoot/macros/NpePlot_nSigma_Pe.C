//this macro is for the photo electron nsigma in different Pt bin

//by xiaozhi bai

#include <iostream>
#include <stdio>
#include <stdlib>
#include <iostream>
#include <fstream>
#include <math.h>
#include "iomanip.h"
#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TLatex.h"
//#inlude "TPad.h"
#include "math.h"
#include "string.h"
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TH2.h"
//#include "TH3.h"
#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TRandom.h"
#include "TMath.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TUnixSystem.h"
#include "TRandom3.h"
//#include "NpePlot.h"
#include "TStopwatch.h"
//#include "TEfficiency.h"
#include "NpePlot_nSigma_Pe.h"
using namespace std;
void Projection();
//TH1F* Subjection(TH1F *h1,TH1F *h2);
void Subjection(TH1F *h1,TH1F *h2, TH1F *h3);
void NpePlot_nSigma_Pe()
{
  // TFile * inFile = new TFile(fielName.Data(),"READ");                        
  TFile * inFile= new TFile("hist_11_19.root");
  char buf[1024];

  //	TH1F::SetDefaultSumw2();
  
  gStyle->SetOptFit(kTRUE);                                                    
  // gStyle->SetOptStat(00000);                                              
  
  gStyle->SetOptTitle(0);
  
  for(Int_t iTrg=0;iTrg<3;iTrg++)
	{
	  sprintf(buf,"mh3nSigEUnlikeTrg%i",iTrg);
	  mh3nSigEUnlike[iTrg]=(TH3F *) inFile->Get(buf);
	  sprintf(buf,"mh3nSigElikeTrg%i",iTrg);
	  mh3nSigElike[iTrg]=(TH3F *) inFile->Get(buf);
	  sprintf(buf,"mh2InvMasslikeTrg%i",iTrg);
	  mh2InvMasslike[iTrg]=(TH2F *) inFile->Get(buf);

	  sprintf(buf,"mh2InvMassUnlikeTrg%i",iTrg);
	  mh2InvMassUnlike[iTrg]=(TH2F *) inFile->Get(buf);

	}
  
  Projection();
   draw_efficiency();
  draw_mean_sigma();
}
void draw_mean_sigma()
{  char temp[1024];
  gStyle->SetOptStat(00000);
  //TCanvas *c2=new TCanvas("mean_sigma","Fit_Mean_Sigma")
    TCanvas *c2 = new TCanvas("c2"," mean_SigmaE",0,0,800,600);
  setpad(c2,0.12,0.02,0.02,0.12);
  c2->cd();
  sprintf(temp,"mean from Fit");
  TLegend *legend = new TLegend(0.7,0.8,0.9,0.95);
  legend->AddEntry(mh1mean,temp,"lpe");
  sprintf(temp,"sigma from Fit");
  legend->AddEntry(mh1sigma,temp,"lpe");
  mh1mean->SetAxisRange(-1, 1.5, "y");                                                  
  mh1mean->SetMarkerStyle(20);
  mh1mean->SetMarkerColor(2);
  // mh1mean->SetMarkerStyle();                                                          
  mh1mean->Draw("Pe");
  mh1sigma->SetMarkerStyle(25);
  mh1sigma->SetMarkerColor(1);
  mh1sigma->Draw("SAMEPe");

  legend->SetTextFont(50);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
   legend->Draw();  
   sprintf(temp,"Sigma_Mean.gif");
   c2->SaveAs(temp);
}
void draw_efficiency()
{ 
  char buf[1024];
  //  gStyle->SetOptStat(00000);    
  // mh1num_no_cut->Sumw2();
  // mh1num_cut->Sumw2();
   mh1efff=(TH1F*)mh1num_cut->Clone("mh1efff");
   mh1efff->SetTitle("nsigma_cut_effiency");                                                 
   mh1efff->Reset();
   // mh1efff->TEfficiency(mh1num_cut,mh1num_no_cut);
  //  mh1efff->Sumw2();                                                       
   //   TEfficiency* pEff = 0;
   // TFile* pFile = new TFile("myfile.root","recreate");
 
  //h_pass and h_total are valid and consistent histograms
   // if(TEfficiency::CheckConsistency(mh1num_cut,mh1num_no_cut))
   // {cout<<"pass cut;     "<<endl;
   // pEff = new TEfficiency(mh1num_cut,mh1num_no_cut);
      // this will write the TEfficiency object to "myfile.root"
      // AND pEff will be attached to the current directory
   // pEff->Write();
   // }
   mh1efff->Divide(mh1num_cut,mh1num_no_cut,1,1);
   mh1efff->SetMarkerSize(1);
   mh1efff->SetMarkerStyle(20);
  mh1efff->SetMarkerColor(2);
   sprintf(buf,"nSigmaElectron Cut Effciency");
   TCanvas *c2 = new TCanvas("c2"," nSigma Electron",0,0,800,600);
   setpad(c2,0.12,0.02,0.02,0.12);
  c2->cd();
   mh1efff->Draw("P");
   drawLatex(0.25,0.45,buf,62,0.06,1);
   sprintf(buf,"nSigmaElectron cut efficiency.gif");
   c2->SaveAs(buf);
}
void Projection()
{ 
  char temp[1024];
  char latex[1024];
  Int_t step=10;
  Int_t pt_low=0;
  Int_t pt_high=30;
  for(Int_t ipt=0;ipt<8;ipt++)
    { Float_t Number_cut=0;
      Float_t Mean=0;
      Float_t MeanErr=0;
      Float_t Sigma=0;
      Float_t SigmaErr=0;
      if(ipt==1)
	{
	  pt_low=30;
	  pt_high=40;
	}
      if(ipt==6)   //pt from 8 to 10
	
	pt_high+=10;	      
      
      if(ipt==7)   //pt from 10 to 20
	{
	  pt_low+=10;
	  pt_high+=90;
	}
      for(Int_t iTrg=0;iTrg<3;iTrg++)
	{	
	  sprintf(temp,"mh1nSigEUnlikeTrg%i",iTrg);
	   mh3nSigEUnlike[iTrg]->GetZaxis()->SetRangeUser(0.,0.15);
	  mh1nSigEUnlike[iTrg]=(TH1F *)mh3nSigEUnlike[iTrg]->ProjectionX(temp,pt_low,pt_high,0,100);
	  sprintf(temp,"mh1nSigElikeTrg%i",iTrg);
	   mh3nSigElike[iTrg]->GetZaxis()->SetRangeUser(0.,0.15);
	  mh1nSigElike[iTrg]=(TH1F *)mh3nSigElike[iTrg]->ProjectionX(temp,pt_low,pt_high,0,100);
	  sprintf(temp,"mh1nSigETrg%i",iTrg);
	  mh1nSigE[iTrg]=(TH1F*) mh1nSigEUnlike[iTrg]->Clone();
	  Subjection(mh1nSigEUnlike[iTrg],mh1nSigElike[iTrg],mh1nSigE[iTrg]);
	  
	  if(iTrg>0)                                                                  
	    {mh1nSigEUnlike[iTrg]->Add(mh1nSigEUnlike[iTrg-1],1);             
		    mh1nSigElike[iTrg]->Add(mh1nSigElike[iTrg-1],1);                 
		    mh1nSigE[iTrg]->Add(mh1nSigE[iTrg-1],1);                         
	    }  
		//	Get_no_cuts(iTrg,Number_no_cut);
	}
      Number_cut=  Get_cuts(pt_low, pt_high);
      Float_t Number_no_cut=mh1nSigE[2]->GetEntries();
      cout<<"   Pt " <<pt_low/10<<" from  to "<<pt_high/10<<"is  "<<Number_cut<<endl;
      cout<<"pt_low "<<pt_low<<"pt_high "<<pt_high<<"   "<<"after cuts"<<Number_cut<<endl;
      cout<<"efficiency  "<<Number_cut/Number_no_cut<<endl;
      Float_t xpt=(pt_low+pt_high)/20;
      // Float_t eff=Number_cut/Number_no_cut;
      mh1num_no_cut->SetBinContent((xpt+1),Number_no_cut);
      mh1num_cut->SetBinContent((xpt+1),Number_cut);
    
      sprintf(temp,"mh1nSigE_%i_",pt_high/10);
      TLegend *legend = new TLegend(0.5,0.4,0.9,0.95);
      legend->AddEntry(mh1nSigE[0],temp,"lpe");
      sprintf(latex," Pt from %i to %i",pt_low/10,pt_high/10);
          mh1nSigE[2]->Rebin(2);
	  Draw_pt(mh1nSigE[2],temp,latex,legend,Mean,MeanErr,Sigma,SigmaErr);
	  mh1mean->SetBinContent((xpt+1),Mean);
	  mh1mean->SetBinError((xpt+1),MeanErr);
	  mh1sigma->SetBinContent((xpt+1),Sigma);
	  mh1sigma->SetBinError((xpt+1),SigmaErr);
      pt_high+=step;	 
      pt_low+=step;
      
    }
  // mh1efff->SetMarkerSize(1);
  // mh1mean->SetAxisRange(-1, 1.5, "y");                                                    
  // mh1mean->SetMarkerStyle(20);                                                        
  // mh1mean->SetMarkerColor(2); 
  // mh1mean->SetMarkerStyle();
  // mh1mean->Draw("Pe");
  // mh1sigma->SetMarkerStyle(25);
  // mh1sigma->SetMarkerColor(1);
  // mh1sigma->Draw("SAMEPe");
  
}
Float_t Get_cuts(Int_t pt_low,Int_t pt_high)
{ char temp[1024]; 
  TH1F *mh1PtUnlike[3];
  TH1F *mh1Ptlike[3];
  TH1F *mh1Pt[3];
  for(Int_t iTrg=0;iTrg<3;iTrg++)
    {
      sprintf(temp,"mh1PtUnlikeTrg%i",iTrg);
       mh3nSigEUnlike[iTrg]->GetZaxis()->SetRangeUser(0.,0.15);
      mh1PtUnlike[iTrg]=(TH1F *)mh3nSigEUnlike[iTrg]->ProjectionZ( temp,60,100,pt_low,pt_high);
      sprintf(temp,"mh1PtlikeTrg%i",iTrg);
       mh3nSigElike[iTrg]->GetZaxis()->SetRangeUser(0.,0.15);
      mh1Ptlike[iTrg]=(TH1F *)mh3nSigElike[iTrg]->ProjectionZ(temp,60,100,pt_low,pt_high);
      sprintf(temp,"mh1PtTrg%i",iTrg);
      mh1Pt[iTrg]=(TH1F*) mh1PtUnlike[iTrg]->Clone();
      Subjection(mh1PtUnlike[iTrg],mh1Ptlike[iTrg],mh1Pt[iTrg]);
      if(iTrg>0)                                                     

	{mh1PtUnlike[iTrg]->Add(mh1PtUnlike[iTrg-1],1);        
	  
	  mh1Ptlike[iTrg]->Add(mh1Ptlike[iTrg-1],1);           
	  
	  mh1Pt[iTrg]->Add(mh1Pt[iTrg-1],1);                   
	  
	}
      
    }
  return mh1Pt[2]->GetEntries();
  
}
void Subjection(TH1F *h1,TH1F *h2, TH1F *h3){
  
  h3->Add(h2,-1.0);
}
void Draw_pt(TH1F *hh,char *temp,char * latex,TLegend* legend,Float_t &mean,Float_t &MeanErr,Float_t &sigma,Float_t &SigmaErr)
{
  TCanvas *c2 = new TCanvas("c2"," nSigma Electron",0,0,800,600);
  setpad(c2,0.12,0.02,0.02,0.12);
  c2->cd();
 
  hh->Fit("gaus","","",-3,3);
   TF1 *gfit = hh->GetFunction("gaus");
   mean=gfit->GetParameter(1);
   MeanErr=gfit->GetParError(1);
   sigma=gfit->GetParameter(2);
   SigmaErr=gfit->GetParError(2);
   cout<<"mean: "<<gfit->GetParameter(1);

   cout<<"mean: "<<gfit->GetParError(1);
  hh->Draw("e");
  drawLatex(0.15,0.8,latex,62,0.06,1); 
  char *s=".gif";
  char *l="/plots2/";
  
  legend->SetTextFont(70);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  // legend->Draw();
    strcat(temp,s);
    c2->SaveAs(temp);
}
void setpad(TPad *pad,float left, float right, float top, float bottom)
{       
  pad->SetFillColor(10);                                                      
  pad->SetBorderMode(0);                                                       
  pad->SetBorderSize(10);                                                      
  pad->SetFrameFillColor(10);                                                  
  pad->SetFrameBorderMode(0);                                                  
  pad->SetFrameBorderSize(0);                                                  
  pad->SetLeftMargin(left);                                                    
  pad->SetRightMargin(right);                                                  
  pad->SetTopMargin(top);                                                      
  pad->SetBottomMargin(bottom);                                                
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




