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


bool MB_trg=true;
bool HT_trg=false;

bool charm_kunsu=false;
bool bottom_kunsu=false;
bool phe_kunsu=false;
bool hadron_kunsu=false;
bool data_kunsu=false;

int gpT;
const int mh2Nhist=1;
const int Npt=8;
const int IHIST=0;
const int DRAWING=1;
const Double_t MINDCA=-0.1;
const Double_t MAXDCA=0.1;
int pt_start=-999;
int pt_end=-999;
TH1F *mc1_charm;
TH1F *mc2_bottom;
TH1F *mc3_phe;
TH1F *mc4_hadron;
TH1F *purity;
TH1F *data;

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex);
void chi2(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag);
void B_fit_Minuit(){
  
  char buf[1024];
  char outputname[50];
  char Trg[50];
  Float_t ptbin[Npt+1]={1,1.2,1.5,2,2.5,3.5,4.5,5.5,8.5};  
  double purity_kunsu[Npt] =  {0.1, 0.13, 0.22, 0.14, 0.21, 0.25, 0.3, 0.43};  
  
  TH1F *Purity_Kunsu=new TH1F("Purity_Kunsu","",Npt,ptbin);
  Purity_Kunsu->GetYaxis()->SetRangeUser(0,1);
  
  for( Int_t ipt=0;ipt<Npt;ipt++)
    {
      Purity_Kunsu->SetBinContent(ipt+1,purity_kunsu[ipt]);
      Purity_Kunsu->SetBinError(ipt+1,0);
      
    }

  TCanvas *cc=new TCanvas("cc","",600,800);

  Purity_Kunsu->SetMarkerStyle(20);
  Purity_Kunsu->SetMarkerColor(2);
  Purity_Kunsu->Draw("PE");

  cc->SaveAs("puirty.pdf");
  
  
  //  return ;
  TH1F *b_fraction_MB=new TH1F("b_fraction_MB","",Npt,ptbin);
  TH1F *b_fraction_HT=new TH1F("b_fraction_HT","",Npt,ptbin);

  TH1F *phe_fraction=new TH1F("phe_fraction","",Npt,ptbin);
  TH1F *hadron_fraction=new TH1F("hadron_fraction","",Npt,ptbin);
  TH1F *charm_fraction=new TH1F("charm_fraction","",Npt,ptbin);
  TH1F *bottom_fraction=new TH1F("bottom_fraction","",Npt,ptbin);
  TH1F *NPE_PHE_fraction=new TH1F("NPE_PHE_fraction","",Npt,ptbin);
  NPE_PHE_fraction->Sumw2();
  
  TH1F *Fit_Ratio[Npt];

  TFile *Output_file=new TFile("OutPut/Fit_B_fraction_MB.root","RECREATE");
  TFile *input_data;
  TFile *input_data_inc;
  TFile *input_purity;

  

  TFile *input_fastsim=new TFile("./Input/File_fastsim.root","READ");
  TFile *input_phe_hijing=new TFile("./Input/Hijing_Phe_1_26.root","READ");
  TFile *input_hadron_data=new TFile("./Input/Dca_hadron_MB.root","READ");
  //TFile *input_hadron_data=new TFile("./Input/Dca_hadron_MB_Kaon.root","READ");
  //TFile *input_hadron_data=new TFile("./Input/Dca_hadron_MB_hadron_all.root","READ");
  
  TFile *Output_file_kunsu=new TFile("OutPut/For_Kunsu.root","RECREATE");

  TFile *input_kunsu=new TFile("../Check_with_Kunsu/Input/hist_For_Xiao_All.root","READ");
  
  double NMC=1;
  TString PTBIN[Npt]={"1<p_{T}^{e}<1.2 GeV/c","1.2<p_{T}^{e}<1.5 GeV/c","1.5<p_{T}^{e}<2 GeV/c","2<p_{T}^{e}<2.5 GeV/c","2.5<p_{T}^{e}<3.5 GeV/c","3.5<p_{T}^{e}<4.5 GeV/c","4.5<p_{T}^{e}<5.5 GeV/c","5.5<p_{T}^{e}<8.5 GeV/c"};

  if(MB_trg){
    sprintf(Trg,"MB");
    input_data=new TFile("./Input/Data_1_26.root","READ");
    //====zyj=====
    input_data_inc=new TFile("./Input/Data_inclusive_photonic.root","READ");
    //====zyj=====
    //     Output_file
    input_purity=new TFile("Input/purity_MB.root","READ");
    // hadron purity
    purity=(TH1F *) input_purity->Get("purity_MB");
    
    pt_start=0;
    pt_end=8;
    
  }
  if(HT_trg)
    {
        
      sprintf(Trg,"HT");
      input_data=new TFile("./Input/Dca_inclusive_photonic_HT_9_5.root","READ");
      Output_file=new TFile("OutPut/Fit_B_fraction_HT.root","RECREATE");
      pt_start=3;
      pt_end=6;

    }

  // fastsim    
  TH1F *mh1Charm_dca[mh2Nhist][Npt];
  TH1F *mh1Bottom_dca[mh2Nhist][Npt];

  // from hijing
  TH1F * mh1Phe_dca[mh2Nhist][Npt];    
  TH1F * mh1pi_dca[mh2Nhist][Npt];    

  // from data
  TH1F * mh1data_inclusive[mh2Nhist][Npt];
  TH1F * mh1data_phe[mh2Nhist][Npt];
  // Hadron from Data
  TH1F *mh1data_hadron[mh2Nhist][Npt];

  // from fastsim
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
        
      sprintf(buf,"mh1rDca_hist%ipt%i_D",ihist+1,ipt);
      mh1Charm_dca[ihist][ipt]=(TH1F *)  input_fastsim->Get(buf);
      sprintf(buf,"mh1rDca_hist%ipt%i_B",ihist+1,ipt);
      mh1Bottom_dca[ihist][ipt]=(TH1F *)  input_fastsim->Get(buf);
      cout<< " ihst "<<ihist<< " ipt "<< ipt<< " "<< mh1Charm_dca[ihist][ipt]->GetTitle()<<endl;
      cout<< " ihst "<<ihist<< " ipt "<< ipt<< " "<<mh1Bottom_dca[ihist][ipt]->GetTitle()<<endl;

      
      
    }
  }

      
      //    return ;

    
  // from data 
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
      /*
      sprintf(buf,"electron_data_Dca_inclusive%i0%i_rebin",ihist,ipt);
      mh1data_inclusive[ihist][ipt]=(TH1F *)  input_data_inc->Get(buf);*/

      sprintf(buf,"electron_data_Dca_inclusive%i%i_rebin",ihist,ipt);
      mh1data_inclusive[ihist][ipt]=(TH1F *)  input_data->Get(buf);
      
      //   sprintf(buf,"electron_data_Dca_Unlike_like%i%i_rebin",ihist,ipt);

      sprintf(buf,"Corrected_Phe_data%i",ipt);
      mh1data_phe[ihist][ipt]=(TH1F *)  input_data->Get(buf);

      cout<< "data  ihst "<<ihist<< " ipt "<< ipt<< " "<< mh1data_inclusive[ihist][ipt]->GetTitle()<<endl;
      cout<< "data ihst "<<ihist<< " ipt "<< ipt<< " "<<mh1data_phe[ihist][ipt]->GetTitle()<<endl;
    }
  }

  // from hijing
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
      //    sprintf(buf,"Hijing_Single_electron_correct_to_data%i",ipt);
      sprintf(buf,"Corrected_hijing_single%i",ipt);
      mh1Phe_dca[ihist][ipt]=(TH1F *)  input_phe_hijing->Get(buf);
      cout<< "hijing  ihst "<<ihist<< " ipt "<< ipt<< " "<< mh1Phe_dca[ihist][ipt]->GetTitle()<<endl;
    }
  }

  // hadron from data, please note 3D dca was not saved, will add it if ..
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
      if(ihist==0||ihist==1)
        sprintf(buf,"Hadron_dcaXY_%i_rebin",ipt);
      else
        sprintf(buf,"hadron_DcaZ_data_%i_rebin",ipt);
      mh1data_hadron[ihist][ipt]=(TH1F *)  input_hadron_data->Get(buf);
      cout<< "hadron  "<<ihist<< " ipt "<< ipt<< " "<< mh1data_hadron[ihist][ipt]->GetTitle()<<endl;
    }
  }

  
  
  //------------------------------
    if(charm_kunsu)
    {

      for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
	for(Int_t ipt=0;ipt<Npt;ipt++) {
        
	  sprintf(buf,"charm_%i",ipt);
	  mh1Charm_dca[ihist][ipt]=(TH1F *)  input_kunsu->Get(buf);
	  // sprintf(buf,"bottom_%i",ipt);
	  // mh1Bottom_dca[ihist][ipt]=(TH1F *)  input_kunsu->Get(buf);
	  // mh1Charm_dca[ihist][ipt]->Scale(1,"width");

	  // mh1Bottom_dca[ihist][ipt]->Scale(1,"width");
      
	}
      }
    }

     if(bottom_kunsu)
    {

      for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
	for(Int_t ipt=0;ipt<Npt;ipt++) {
        
	  // sprintf(buf,"charm_%i",ipt);
	  // mh1Charm_dca[ihist][ipt]=(TH1F *)  input_kunsu->Get(buf);
	  sprintf(buf,"bottom_%i",ipt);
	  mh1Bottom_dca[ihist][ipt]=(TH1F *)  input_kunsu->Get(buf);
	  // mh1Charm_dca[ihist][ipt]->Scale(1,"width");

	  // mh1Bottom_dca[ihist][ipt]->Scale(1,"width");
      
	}
      }
    }


    
      if(hadron_kunsu)
	{

	  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
	    for(Int_t ipt=0;ipt<Npt;ipt++) {
        
	      sprintf(buf,"hadron_%i",ipt);
	      mh1data_hadron[ihist][ipt]=(TH1F *)  input_kunsu->Get(buf);
	      //      mh1data_hadron[ihist][ipt]->Scale(1,"width");


	      cout<<     mh1data_hadron[ihist][ipt]->GetName()<<endl;
	    }
	  }
	}

      if(phe_kunsu)
	{

	  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
	    for(Int_t ipt=0;ipt<Npt;ipt++) {
        
	      sprintf(buf,"phe_data_%i",ipt);
	      mh1Phe_dca[ihist][ipt]=(TH1F *)  input_kunsu->Get(buf);
	      mh1data_phe[ihist][ipt]=(TH1F *)  input_kunsu->Get(buf);

	      //mh1Phe_dca[ihist][ipt]->Scale(1,"width");
	      //    mh1data_phe[ihist][ipt]->Scale(1,"width");

	      // mh1Phe_dca[ihist][ipt]->Scale(1,"width");
	      // mh1data_phe[ihist][ipt]->Scale(1,"width");
	      
	    }
	  }
	}

      
      if(data_kunsu)
	{

	  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
	    for(Int_t ipt=0;ipt<Npt;ipt++) {
        
	      sprintf(buf,"incluse_data_%i",ipt);
	      mh1data_inclusive[ihist][ipt]=(TH1F *)  input_kunsu->Get(buf);
	      // mh1data_inclusive[ihist][ipt]->Scale(1,"width");

	      cout<<     mh1data_inclusive[ihist][ipt]->GetName()<<endl;
	    }
	  }
	}


  //-----------------------------

  
  
  


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



  TFile *file_kunsu=new TFile("File_tem_file_kunsu.root","RECREATE");  
  
  // for(Int_t ipt=4;ipt<5;ipt++) {
    for(Int_t ipt=pt_start;ipt<pt_end;ipt++) {

      if(ipt<4)
	gpT=1;
      else
	gpT=0;
      
    TString mcname0="mc1", mcname1="mc2", mcname2="mc3",mcname3="mc4",  dataname="data";
    mc1_charm=(TH1F*)mh1Charm_dca[IHIST][ipt]->Clone(mcname0+mh1Charm_dca[IHIST][ipt]->GetName());
    mc2_bottom=(TH1F*)mh1Bottom_dca[IHIST][ipt]->Clone(mcname1+mh1Bottom_dca[IHIST][ipt]->GetName());
    //phe from hijing
    if(ipt>4)
    mc3_phe=(TH1F*)mh1Phe_dca[IHIST][ipt]->Clone(mcname2+mh1Phe_dca[IHIST][ipt]->GetName());
    // phe from data
    else
      mc3_phe=(TH1F*)mh1data_phe[IHIST][ipt]->Clone(mcname2+mh1data_phe[IHIST][ipt]->GetName());
    mc4_hadron=(TH1F*)mh1data_hadron[IHIST][ipt]->Clone(mcname3+mh1data_hadron[IHIST][ipt]->GetName());
    
    
    data=(TH1F*)mh1data_inclusive[IHIST][ipt]->Clone(dataname+mh1data_inclusive[IHIST][ipt]->GetName());

    cout<< "Wwwwwwwwwwwwwwwwwwwwwwwww "<<mc2_bottom->GetBinError(30)<< "  "<<mc2_bottom->GetBinContent(30)<< endl;;
   
    // file_kunsu->cd();
    // if(ipt==4)
    //   {
    // 	mc1_charm->Write();
    // 	mc2_bottom->Write();
    // 	mc3_phe->Write();
    // 	mc4_hadron->Write();
    // 	data->Write();
    //   }
    
    cout<<mc1_charm->GetTitle()<<endl;
    cout<<mc2_bottom->GetTitle()<<endl;
    cout<<mc3_phe->GetTitle()<<endl;
    cout<<mc4_hadron->GetTitle()<<endl;

    cout<<data->GetTitle()<<endl;

    Output_file_kunsu->cd();
    mc1_charm->Write();
    mc2_bottom->Write();
    mc3_phe->Write();
    mc4_hadron->Write();
    data->Write();

    
    mc1_charm->Sumw2();
    mc2_bottom->Sumw2();
    cout<< "Wwwwwwwwwwwwwwwwwwwwwwwww "<<mc2_bottom->GetBinError(30)<<endl;;
    mc3_phe->Sumw2();
    mc4_hadron->Sumw2();
    
    // mc1_charm->Scale(1,"width");
    // mc2_bottom->Scale(1.,"width");
    
    
    mc1_charm->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    mc2_bottom->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    cout<< "Wwwwwwwwwwwwwwwwwwwwwwwww "<<mc2_bottom->GetBinError(30)<<endl;;
    mc3_phe->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    mc4_hadron->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    data->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    

    cout<< " !!!!!!!!!!!!"<< ipt<< " "<<mc1_charm->Integral() << " "<<mc2_bottom->Integral()<< " "<<mc3_phe->Integral() <<" "<<mc4_hadron->Integral()<< "  "<<data->Integral()<<endl;;

    mc1_charm->Scale(1,"width");
    mc2_bottom->Scale(1,"width");
    cout<< "Wwwwwwwwwwwwwwwwwwwwwwwww "<<mc2_bottom->GetBinError(30)<<endl;;
 // mc3_phe->Scale(1,"width");

 // data->Scale(1,"width");

    mc1_charm->Scale(1./mc1_charm->Integral());
    mc2_bottom->Scale(1./mc2_bottom->Integral());
    mc3_phe->Scale(1./mc3_phe->Integral());
    mc4_hadron->Scale(1./mc4_hadron->Integral());

    if(hadron_kunsu)
      mc4_hadron->Scale(1,"width");      
    cout<< "Wwwwwwwwwwwwwwwwwwwwwwwww "<<mc2_bottom->GetBinError(30)<<endl;;
    // TString title="";
    // data->SetTitle(title+PTBIN[ipt]);
    // data->GetXaxis()->SetTitle("DCA_{XY} (cm)");
    // data->GetXaxis()->SetTitleSize(0.04);
    // data->GetXaxis()->SetLabelSize(0.04);
    // data->GetYaxis()->SetLabelSize(0.05);
    // data->GetYaxis()->SetTitleOffset(1);
    // data->GetXaxis()->SetTitleOffset(1);
    // data->SetMaximum(data->GetMaximum()*1.3);
    // gPad->SetLogy();   

    double frac_norm = 0.;
    double fracErr_norm = 0.;
    double frac_btoe = 0.;
    double fracErr_btoe = 0.;
    double frac_ctoe = 0.;
    double fracErr_ctoe = 0.;
    double frac_phe = 0.;
    double fracErr_phe = 0.;
    double frac_hadron = 0.;
    double fracErr_hadron = 0.;

    TMinuit *gMinuit=new TMinuit(4); //initialize TMinuit with a maximum of 5 params
    gMinuit->SetMaxIterations(50000);
    gMinuit->SetFCN(chi2);
    gMinuit->SetErrorDef(1);
    
    double arglist[10];int ierflg=0;
    //set err definition to 1-sigma
    //arglist[0]=4; //was to get 2 sigma 
    arglist[0]=1; //error definition: chi^2 change by 1 to get 1 sigma
    gMinuit->mnexcm("SET ERR",arglist,1,ierflg);

    //starting values
    //   double vstart[4]={1,0.001,0.001,0.001}; //frac
    double vstart[4]={0,0.001,0.001,purity_kunsu[ipt]}; //frac
    double step[4]={0.0001,0.0001,0.0001,0.00001}; //starting step
    //bin/   gMinuit->mnparm(0,"frac 0",vstart[0],step[0],1e1,1e16,ierflg);
    //   gMinuit->mnparm(0,"frac 0",vstart[0],step[0],0,5*data->GetMaximum(),ierflg);
    gMinuit->mnparm(0,"frac 0",1,step[0],0,5*data->GetMaximum(),ierflg);
    gMinuit->mnparm(1,"frac 1",vstart[1],step[1],0.000,1.,ierflg);
    gMinuit->mnparm(2,"frac 2",vstart[2],step[2],0.000,1,ierflg);
    gMinuit->mnparm(3,"frac 3",vstart[3],step[3],0.000,1,ierflg);
    gMinuit->mnparm(3,"frac 3",vstart[3],step[3],purity_kunsu[ipt]-0.1,purity_kunsu[ipt]+0.15,ierflg);

    //   gMinuit->mnparm(3,"frac 3",vstart[2],step[3],1-purity->GetBinContent(ipt+1)-1e-6,1-purity->GetBinContent(ipt+1)+1e-6,ierflg);
    //  gMinuit->mnparm(3,"frac 3",vstart[3],step[3],1-purity->GetBinContent(ipt+1)-0.1,1-purity->GetBinContent(ipt+1)+0.15,ierflg);

    //gMinuit->mnparm(3,"frac 3",vstart[3],step[3],Purity[ipt]-0.1,Purity[ipt]+0.1,ierflg);
    cout<< " !!!!"<<ipt<<endl;
    //    gMinuit->mnparm(3,"frac 3",vstart[3],step[3],0.,1,ierflg);

    //--------------
    //bin/   gMinuit->mnparm(1,"frac 1",0.209+0.165,step[1],0.000,1.,ierflg);
    // gMinuit->mnparm(1,"frac 1",0.209+0.165,step[1],0,1.,ierflg);
    // gMinuit->mnparm(2,"frac 2",0.165/(0.209+0.165),step[1],0.000,1.,ierflg);
    //   gMinuit->mnparm(3,"frac 3",0.38109,step[1],0.000,1.,ierflg);

    // gMinuit->FixParameter(1);//,"frac 1",0.209+0.165,step[1],0.209+0.165,0.209+0.165,ierflg);
    //   gMinuit->FixParameter(2);//,"frac 1",0.209+0.165,step[1],0.209+0.165,0.209+0.165,ierflg);
    //   gMinuit->FixParameter(3);//,"frac 1",0.209+0.165,step[1],0.209+0.165,0.209+0.165,ierflg);
    
    //   gMinuit->mnparm(1,"frac 1",vstart[1],step[1],0.000,1.,ierflg);
    
    //---------------
    

    //   gMinuit->mnparm(3,"frac 3",vstart[3],step[3],1-purity->GetBinContent(ipt+1)-4*purity->GetBinError(ipt+1),1-purity->GetBinContent(ipt+1)+4*purity->GetBinError(ipt+1),ierflg);

    // if(ipt==0)
    //   gMinuit->mnparm(3,"frac 3",vstart[3],step[3],1-purity->GetBinContent(ipt+1)-0.05,1-purity->GetBinContent(ipt+1)+0.05,ierflg);

    // if(ipt==1)
    //   gMinuit->mnparm(3,"frac 3",vstart[3],step[3],1-purity->GetBinContent(ipt+1)-0.05,1-purity->GetBinContent(ipt+1)+0.08,ierflg);

    
    //simple scan to get better start values
    gMinuit->mnexcm("SCAN",arglist,1,ierflg); 
    cout<<"done with first scan!"<<endl;
    //minimization
    arglist[0]=50000; //maxcalls
    arglist[1]=0.2; // tolerance = 0.001*[this value]*[error def] //5.0 before
    gMinuit->mnexcm("MIGRAD",arglist,2,ierflg); 
    //gMinuit->mnexcm("MINIMIZE",arglist,2,ierflg); 
    //error analysis

    cout<<"done with fit!"<<endl;
    //fit results
    double dum1,dum2;
    TString *str0 = new TString("norm");
    TString *str1 = new TString("C#rightarrow e frac");
    TString *str2 = new TString("B#rightarrow e  frac");
    TString *str3 = new TString("hadron frac");

    gMinuit->mnpout(0,*str0,frac_norm,fracErr_norm,dum1,dum2,ierflg);
    gMinuit->mnpout(1,*str1,frac_ctoe,fracErr_ctoe,dum1,dum2,ierflg);
    gMinuit->mnpout(2,*str2,frac_btoe,fracErr_btoe,dum1,dum2,ierflg);
    gMinuit->mnpout(3,*str3,frac_hadron,fracErr_hadron,dum1,dum2,ierflg);

    cout<< " frac_btoe"<< frac_btoe<<endl;
    cout<< " frac_ctoe"<< frac_ctoe<<endl;
    
    //get variance/errors
    TGraph *contFrac_1sigma;
    TGraph *contFrac_2sigma;

    /*
    // cout<<"had pT = "<<ptHadLow[j]<<endl;
	
    // +--------------------------+
    // | run MINUIT               |
    // +--------------------------+
    TMinuit *gMinuit=new TMinuit(4); //initialize TMinuit with a maximum of 5 params
    gMinuit->SetMaxIterations(50000);
    gMinuit->SetFCN(chi2);
    gMinuit->SetErrorDef(1);
    
    double arglist[10];int ierflg=0;
    //set err definition to 1-sigma
    //arglist[0]=4; //was to get 2 sigma 
    arglist[0]=1; //error definition: chi^2 change by 1 to get 1 sigma
    gMinuit->mnexcm("SET ERR",arglist,1,ierflg);

    //starting values
    //   double vstart[4]={1,0.001,0.001,0.001}; //frac
    double vstart[4]={1,0.001,0.001,1-purity->GetBinContent(ipt+1)}; //frac
    double step[4]={1,0.0001,0.0001,0.0001}; //starting step
    //bin/   gMinuit->mnparm(0,"frac 0",vstart[0],step[0],1e1,1e16,ierflg);
    gMinuit->mnparm(0,"frac 0",vstart[0],step[0],10,5*data->GetMaximum(),ierflg);

    gMinuit->mnparm(1,"frac 1",vstart[1],step[1],0.000,1.,ierflg);
    gMinuit->mnparm(2,"frac 2",vstart[2],step[2],0.000,1,ierflg);
    gMinuit->mnparm(3,"frac 3",vstart[3],step[3],0.000,1,ierflg);
    //   gMinuit->mnparm(3,"frac 3",vstart[2],step[3],1-purity->GetBinContent(ipt+1)-1e-6,1-purity->GetBinContent(ipt+1)+1e-6,ierflg);
    //gMinuit->mnparm(3,"frac 3",vstart[3],step[3],1-purity->GetBinContent(ipt+1)-purity->GetBinError(ipt+1),1-purity->GetBinContent(ipt+1)+purity->GetBinError(ipt+1),ierflg);
    //  gMinuit->mnparm(3,"frac 3",vstart[3],step[3],purity_kunsu[ipt]-0.1,purity_kunsu[ipt]+0.1,ierflg);
	
    //    gMinuit->mnparm(3,"frac 3",vstart[3],step[3],purity[ipt]-0.1,purity[ipt]+0.1,ierflg);
    

    //   gMinuit->mnparm(3,"frac 3",vstart[3],step[3],1-purity->GetBinContent(ipt+1)-4*purity->GetBinError(ipt+1),1-purity->GetBinContent(ipt+1)+4*purity->GetBinError(ipt+1),ierflg);

    // if(ipt==0)
    //   gMinuit->mnparm(3,"frac 3",vstart[3],step[3],1-purity->GetBinContent(ipt+1)-0.05,1-purity->GetBinContent(ipt+1)+0.05,ierflg);

    // if(ipt==1)
    //   gMinuit->mnparm(3,"frac 3",vstart[3],step[3],1-purity->GetBinContent(ipt+1)-0.05,1-purity->GetBinContent(ipt+1)+0.08,ierflg);

    
    //simple scan to get better start values
    gMinuit->mnexcm("SCAN",arglist,1,ierflg); 
    cout<<"done with first scan!"<<endl;
    //minimization
    arglist[0]=50000; //maxcalls
    arglist[1]=0.5; // tolerance = 0.001*[this value]*[error def] //5.0 before
    gMinuit->mnexcm("MIGRAD",arglist,2,ierflg); 
    //gMinuit->mnexcm("MINIMIZE",arglist,2,ierflg); 
    //error analysis

    cout<<"done with fit!"<<endl;
    //fit results
    double dum1,dum2;
    TString *str0 = new TString("norm");
    TString *str1 = new TString("C#rightarrow e frac");
    TString *str2 = new TString("B#rightarrow e  frac");
    TString *str3 = new TString("hadron frac");

    gMinuit->mnpout(0,*str0,frac_norm,fracErr_norm,dum1,dum2,ierflg);
    gMinuit->mnpout(1,*str1,frac_ctoe,fracErr_ctoe,dum1,dum2,ierflg);
    gMinuit->mnpout(2,*str2,frac_btoe,fracErr_btoe,dum1,dum2,ierflg);
    gMinuit->mnpout(3,*str3,frac_hadron,fracErr_hadron,dum1,dum2,ierflg);

    cout<< " frac_btoe"<< frac_btoe<<endl;
    cout<< " frac_ctoe"<< frac_ctoe<<endl;
    
    //get variance/errors
    TGraph *contFrac_1sigma;
    TGraph *contFrac_2sigma;

    */

    
    //Print results
    double amin,edm,errdef;
    int nvpar,nparx,icstat;
    gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
    gMinuit->mnprin(3,amin);


    



    Double_t Frac_norm=frac_norm;
    Double_t Frac_ctoe=frac_ctoe;
    Double_t Frac_btoe= frac_ctoe*frac_btoe/(1-frac_btoe);
    Double_t Frac_hadron=frac_hadron;
    Double_t Frac_phe=(1-Frac_ctoe-Frac_hadron-Frac_btoe);    

    Double_t Frac_norm_err=fracErr_norm;
    Double_t Frac_ctoe_err=fracErr_ctoe;
    //  Double_t Frac_btoe_err=fracErr_btoe ;
    Double_t Frac_hadron_err=fracErr_hadron;

    Double_t Frac_phe_err=0;

    Double_t tem_err_charm=TMath::Power(Frac_ctoe_err*frac_btoe/(1-frac_btoe),2);
    //  Double_t tem_err_Bf=TMath::Power(fracErr_btoe/TMath::Power(1-frac_btoe,2),2);
    Double_t tem_err_Bf=TMath::Power(fracErr_btoe*Frac_ctoe/TMath::Power(1-frac_btoe,2),2);

    Double_t Frac_btoe_err=Frac_btoe*sqrt(tem_err_charm+tem_err_Bf);
    
    
    charm_fraction->SetBinContent(ipt+1,Frac_ctoe);
    bottom_fraction->SetBinContent(ipt+1,Frac_btoe);
    hadron_fraction->SetBinContent(ipt+1,Frac_hadron);
    phe_fraction->SetBinContent(ipt+1,Frac_phe);

    charm_fraction->SetBinError(ipt+1,Frac_ctoe_err);
    bottom_fraction->SetBinError(ipt+1,Frac_btoe_err);
    hadron_fraction->SetBinError(ipt+1,Frac_hadron_err);
    phe_fraction->SetBinError(ipt+1,0);


    // if(ipt==4)
    //   cout<< " DDDDDD "<<Frac_ctoe<<" B "<<Frac_btoe<< " phe" << Frac_phe<< " hadron"<< Frac_hadron<<endl;

    
    c1->cd();
    c1->SetLogy(1);
    gPad->Update();    
    data->Draw();



    
    Double_t Ratio_btoe=frac_btoe;
    Double_t RatioErr_btoe=fracErr_btoe;
    
    TH1F *mc1_charm_cl = (TH1F*)mc1_charm->Clone("mc1_charm_cl");
    mc1_charm_cl->Scale(Frac_ctoe*Frac_norm);
    mc1_charm_cl->SetLineColor(2);
    
    TH1F *mc2_bottom_cl = (TH1F*)mc2_bottom->Clone("mc2_bottom_cl");
    mc2_bottom_cl->Scale(Frac_btoe*Frac_norm);
    mc2_bottom_cl->SetLineColor(6);

    TH1F *mc3_phe_cl = (TH1F*)mc3_phe->Clone("mc3_phe_cl");
    mc3_phe_cl->Scale(Frac_phe*Frac_norm);
    mc3_phe_cl->SetLineColor(8);
    
    TH1F *mc4_hadron_cl = (TH1F*)mc4_hadron->Clone("mc4_hadron_cl");
    mc4_hadron_cl->Scale(Frac_hadron*Frac_norm);
    mc4_hadron_cl->SetLineColor(4);

    
    TH1F *mc_all_cl = (TH1F*)mc1_charm_cl->Clone("mc_all_cl");
    mc_all_cl->Add(mc2_bottom_cl);
    mc_all_cl->Add(mc3_phe_cl);
    mc_all_cl->Add(mc4_hadron_cl);
    mc_all_cl->SetLineColor(1);

    mc1_charm_cl->Sumw2(0);
    mc2_bottom_cl->Sumw2(0);
    mc3_phe_cl->Sumw2(0);
    mc4_hadron_cl->Sumw2(0);

    mc1_charm_cl->SetLineStyle(7);
    mc1_charm_cl->SetLineWidth(2);
    mc1_charm_cl->SetLineColor(4);

    mc2_bottom_cl->SetLineStyle(7);
    mc2_bottom_cl->SetLineWidth(2);
    mc2_bottom_cl->SetLineColor(6);

    mc3_phe_cl->SetLineStyle(7);
    mc3_phe_cl->SetLineWidth(2);
    mc3_phe_cl->SetLineColor(7);

    mc4_hadron_cl->SetLineStyle(7);
    mc4_hadron_cl->SetLineWidth(2);
    mc4_hadron_cl->SetLineColor(8);
    
    Fit_Ratio[ipt]= (TH1F * ) data->Clone(Form("Fit_Ratio"));
    data->GetXaxis()->SetTitle("DCA_{XY} (cm)");
    data->GetYaxis()->SetTitle("Counts");
    data->GetXaxis() -> CenterTitle();
    data->GetYaxis() -> CenterTitle();
    data->SetTitle("");
    data->GetXaxis()->SetTitle("DCA_{XY} cm");
    data->SetMarkerStyle(20);
    data->SetMarkerColor(1);
    data->SetLineColor(1);

    

    

    data->GetYaxis()->SetTitleSize(0.05);



    data->GetYaxis()->SetTitleOffset(1);
    data->GetYaxis()->SetLabelSize(0.05);
    data->SetMarkerSize(1.5);

    mc_all_cl->SetLineColor(2);
    mc_all_cl->SetLineWidth(2);

    TH1F *mc_all_cl_with_Err=(TH1F *) mc_all_cl->Clone("mc_all_cl_with_Err"); 
    mc_all_cl->Sumw2(0);    


    TLegend *legend=new TLegend(0.7,0.6,0.94,0.95);
    legend ->SetBorderSize(0);
    legend ->SetTextSize(0.04);
    legend ->SetFillStyle(0);
    legend ->SetTextFont(62);
    legend->AddEntry(data,"Inclusive Electron","lp");
    legend->AddEntry(mc_all_cl,"Template Fit","l");
    legend->AddEntry(mc1_charm_cl,"D #rightarrow e","l");
    legend->AddEntry(mc2_bottom_cl,"B #rightarrow e","l");
    legend->AddEntry(mc3_phe_cl,"PHE","l");
    legend->AddEntry(mc4_hadron_cl,"Hadron","l");
    

    
    
    
  
    TCanvas *c5=new TCanvas("c5","",1200,1000);
    
    c5->cd();
    TPad* pad1 = new TPad("pad1","pad1",0.00,0.4,1.00,1.00);pad1->Draw();
    TPad* pad2 = new TPad("pad2","pad2",0.00,0.00,1.00,0.4);pad2->Draw();
    pad1->SetMargin(0.12,0.02,0.00,0.02);
    pad2->SetMargin(0.12,0.02,0.25,0.00);


    pad1->cd();

    data->Draw("PE");
    mc1_charm_cl->Draw("sameL");
    mc2_bottom_cl->Draw("sameL");
    mc3_phe_cl->Draw("sameL");
    mc4_hadron_cl->Draw("sameL");
    mc_all_cl->Draw("sameL");

    legend->Draw("same");

    sprintf(buf,"STAR Au+Au @ 200 GeV");
    drawLatex(0.15,0.75,buf,62,0.04,1);
    sprintf(buf,PTBIN[ipt]);
    drawLatex(0.15,0.65,buf,62,0.04,1);
    

    sprintf(buf,"B_{e} / (B_{e}+C_{e}) = %4.3f #pm %4.3f",Ratio_btoe,RatioErr_btoe);
    drawLatex(0.15,0.55,buf,62,0.04,2);

    sprintf(buf,"STAR Preliminary");
    drawLatex(0.15,0.85,buf,62,0.06,2);

    //   continue;    

    if(ipt==999)
      {
    	sprintf(buf,"Incluesive electron=f_{B}e^{B}+f_{D}e^{D}+f_{PHE}e^{PHE}+f_{Hadron}e^{Hadron}");
    	drawLatex(0.28,0.1,buf,62,0.05,4);
      }

    
    pad2->cd();


    TLine *l1=new TLine(-0.1,1,0.1,1);
    l1->SetLineColor(4);
    l1->SetLineWidth(2.5);

    Fit_Ratio[ipt]=(TH1F *) mc_all_cl_with_Err->Clone(Form("Ratio_%i",ipt));
    pad2->cd();
    
    gPad->SetLogy(0);
    Fit_Ratio[ipt]->SetLineColor(2);
    Fit_Ratio[ipt]->SetMarkerColor(2);
    Fit_Ratio[ipt]->SetMarkerSize(1.5);
    Fit_Ratio[ipt]->SetMarkerStyle(20);



    Fit_Ratio[ipt]->Divide(data);
    
    Fit_Ratio[ipt]->GetYaxis()->SetRangeUser(0.01,2.6);
    Fit_Ratio[ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
    Fit_Ratio[ipt]->GetYaxis()->SetTitle("Fit/Data");

    
    Fit_Ratio[ipt]->GetXaxis()->CenterTitle();
    Fit_Ratio[ipt]->GetYaxis()->CenterTitle();

    Fit_Ratio[ipt]->GetYaxis()->SetTitleSize(0.08);
    Fit_Ratio[ipt]->GetXaxis()->SetTitleSize(0.08);

    Fit_Ratio[ipt]->GetXaxis()->SetTitleOffset(1);
    Fit_Ratio[ipt]->GetYaxis()->SetTitleOffset(0.6);
    Fit_Ratio[ipt]->GetYaxis()->SetLabelSize(0.08);
    Fit_Ratio[ipt]->GetXaxis()->SetLabelSize(0.08);

    Fit_Ratio[ipt]->SetTitle("");

    
    Fit_Ratio[ipt]->Draw();
    l1->Draw("same");








    
    // TH1F *ratio=(TH1F *) data->Clone("ratio");
    // c2->SetLogy(0);
    // ratio->Divide(mc_all_cl);
    // TLine *line_1=new TLine(MINDCA,1.0,MAXDCA,1.0);
    // line_1->SetLineColor(4);
    // line_1->SetLineStyle(7);
    // line_1->SetLineWidth(3);

    // // c1->cd(2)->SetTopMargin(0.0);
    // // c1->cd(2)->SetBottomMargin(0.14);
    // // c1->cd(2)->SetLeftMargin(0.1);
    // // gPad->SetLogy(0);
  
    // //   c2->cd();
    // ratio->SetLineColor(2);
    // ratio->SetMarkerColor(2);
    // ratio->GetYaxis()->SetRangeUser(0.4,2.6);
    // //   TPad *pad2 = new TPad("pad2","",0.001,0.001,0.99,0.3);
    // // gPad->Update();
    // // pad2->Draw();
    // // pad2->cd();
    //  ratio->Draw("PE");
    //  line_1->Draw("same");


     if(MB_trg)
      {
	
	b_fraction_MB->SetBinContent(ipt+1,frac_btoe);
	b_fraction_MB->SetBinError(ipt+1,fracErr_btoe);
      }

       
       
 c5->SaveAs(Form("Output/B_Fit_%i_pT_Fit_and_ratio.pdf",ipt));

	
  } // end pt


         TCanvas *c4=new TCanvas("c4","",900,1000);
       c4->cd();
       gPad->SetLogy(0);
       
       charm_fraction->SetMarkerStyle(20);
       bottom_fraction->SetMarkerStyle(20);
       hadron_fraction->SetMarkerStyle(20);
       phe_fraction->SetMarkerStyle(20);

       charm_fraction->SetMarkerColor(1);
       bottom_fraction->SetMarkerColor(2);
       hadron_fraction->SetMarkerColor(3);
       phe_fraction->SetMarkerColor(4);

       charm_fraction->SetLineColor(1);
       bottom_fraction->SetLineColor(2);
       hadron_fraction->SetLineColor(3);
       phe_fraction->SetLineColor(4);

       charm_fraction->GetXaxis()->SetTitle("p_{T} (GeV)");
       charm_fraction->GetYaxis()->SetTitle("Fraction");
       charm_fraction->GetYaxis()->SetRangeUser(0,1);
       
       charm_fraction->Draw("PE1");
       bottom_fraction->Draw("samePE1");
       hadron_fraction->Draw("samePE1");
       phe_fraction->Draw("samePE1");

       c4->SaveAs("Output/Fraction.pdf");    

       NPE_PHE_fraction->Add(charm_fraction);
       NPE_PHE_fraction->Add(bottom_fraction);
       NPE_PHE_fraction->Divide(phe_fraction);

       TCanvas *c7=new TCanvas("c7","",600,600);
       c7->cd();

       gPad->SetLogy(0);
       TPad*   pad3 = new TPad("pad3","pad3",0.02,0.02,1.00,1.00);

       pad3->SetMargin(0.13,0.13,0.13,0.13);
       pad3->Draw();
       NPE_PHE_fraction->SetMarkerColor(2);
       NPE_PHE_fraction->SetMarkerStyle(20);
       NPE_PHE_fraction->SetMarkerColor(2);
       NPE_PHE_fraction->GetYaxis()->SetRangeUser(0,2);
       NPE_PHE_fraction->Draw("PE");
       NPE_PHE_fraction->GetXaxis()->SetTitle("p_{T} GeV/c");

       sprintf(buf,"NPE/PHE");
    drawLatex(0.15,0.75,buf,22,0.04,1);
    
       
       c7->SaveAs("Output/Npe_Phe_ratio.pdf");
       
   if(MB_trg)
     {
       Output_file->cd();
       b_fraction_MB->Write();
       charm_fraction->Write();
       bottom_fraction->Write();
       hadron_fraction->Write();
       phe_fraction->Write();
    
       Output_file->Close();
     }
  return;
  
}
void chi2(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag){

  if(!mc1_charm || !mc2_bottom|| !mc3_phe|| !mc4_hadron ){cout<<"no template!"<<endl; return ;}

  // if(mc1_charm->GetNbinsX()!=mc2_bottom->GetNbinsX()){
  //   cout<<"Warning: unequal bins! bin1 = "<<mc1_charm->GetNbinsX()<<" bin2 = "<<mc2_bottom->GetNbinsX()<<endl;
  //   return ;
  // }

  double chiSq = 0.;
  int nDof = 0; 
  for(int k=0;k<mc1_charm->GetNbinsX();k++){


    // if(k<7||data->GetNbinsX()-7<k)
    //    continue;


    if(data->GetBinContent(k+1)<=0)
       continue;

    // if(data->GetBinContent(k+1)<=0)
    //    continue;
    
    
    double y1 = mc1_charm->GetBinContent(k+1);
    double y2 = mc2_bottom->GetBinContent(k+1);
    double y3 = mc3_phe->GetBinContent(k+1);
    double y4 = mc4_hadron->GetBinContent(k+1);
 
    
    // double ey1 = mc1_charm->GetBinError(k+1);
    // double ey2 = mc2_bottom->GetBinError(k+1);
    // double ey3 = mc3_phe->GetBinError(k+1);

    
    
    double y_data = data->GetBinContent(k+1);
    double ey_data = data->GetBinError(k+1);
    


    //   double eTemp=sqrt(ey1*ey1+ey2*ey2+ey3*ey3); 
    //double y0 = hdPhi_zb[i-2]->GetBinContent(k+1);
    //double ey0 = hdPhi_zb[i-2]->GetBinError(k+1);

    // by bingchu  // double ycomb = par[0]*y2+y1*(1.-par[0]); //
    double ycomb = par[0]*(par[1]*y1+par[1]*par[2]/(1-par[2])*y2+ (1-par[1]-par[1]*par[2]/(1-par[2])-par[3])*y3 + par[3]*y4); //
       //    double ycomb = par[0]*(par[1]*y0+par[2]*y1+ par[3]*y2 + 0.2*y3); //
    
    double ey1 = par[0]*par[1]*mc1_charm->GetBinError(k+1);
    double ey2 = par[0]*par[1]*par[2]/(1-par[2])*mc2_bottom->GetBinError(k+1);
    double ey3 = par[0]*(1-par[1]-par[1]*par[2]/(1-par[2])-par[3])*mc3_phe->GetBinError(k+1);
    double ey4 = par[0]*par[3]*mc4_hadron->GetBinError(k+1);
    double eTemp=sqrt(ey1*ey1+ey2*ey2+ey3*ey3+ey4*ey4);

    // if(k==30)
    //   {
    // 	//	cout<< " "<<ey1<< " "<<ey2<<" "<<ey3<< " "<<ey4<< ey_data<<endl;
    // 	cout<< " "<<mc1_charm->GetBinError(k+1)<< " "<<mc2_bottom->GetBinError(k+1)<<" "<<mc3_phe->GetBinError(k+1)<< " "<<mc4_hadron->GetBinError(k+1)<<" "<<data->GetBinError(k+1)<<endl;
    //   }

    
    //double ycomb = par[0]*y2+y1*par[1]; // 
    //    double delta = (ycomb-y_data)/ey_data;
    double delta = (ycomb-y_data)/sqrt(ey_data*ey_data+eTemp*eTemp);
        
    chiSq += delta*delta;
    nDof++;



  }
  func = chiSq;

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

