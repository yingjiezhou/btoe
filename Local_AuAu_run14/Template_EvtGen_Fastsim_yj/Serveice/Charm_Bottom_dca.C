/*--------------------Xiaozhi------------------------------------ 

  this macro for the Hadron mean calibration

  at  low Pt electron purity

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
#include "../Binning_MB.h"

using namespace std;


const int mh2Nhist=3;
//const int Npt=7;

TString Ymh2Titlename[mh2Nhist]={" 3Ddca (cm)"," dcaXY (cm)"," dcaZ (cm) "};

TString Ymh1Titlename[mh2Nhist]={" dca (cm)"," dcaXY (cm)"," dcaZ (cm) "};
//TString Ymh1Titlename[mh2Nhist]={" dca (cm)"," dcaXY (cm)"," dcaZ (cm) "};

char buf[1024];

TH2F *mh2Hist_DcaVsPt_D0[mh2Nhist];
TH2F *mh2Hist_DcaVsPt_B0[mh2Nhist];

TH2F *mh2Hist_DcaVsPt_D0bar[mh2Nhist];
TH2F *mh2Hist_DcaVsPt_B0bar[mh2Nhist];


TH2F *mh2Hist_DcaVsPt_Dplus[mh2Nhist];
TH2F *mh2Hist_DcaVsPt_Bplus[mh2Nhist];

TH2F *mh2Hist_DcaVsPt_Dminus[mh2Nhist];
TH2F *mh2Hist_DcaVsPt_Bminus[mh2Nhist];



TH2F *mh2Hist_DcaVsPt_pi0[mh2Nhist];



TH1F *mh1hist_Dca_D0[mh2Nhist][Npt];
TH1F *mh1hist_Dca_B0[mh2Nhist][Npt];

TH1F *mh1hist_Dca_D0bar[mh2Nhist][Npt];
TH1F *mh1hist_Dca_B0bar[mh2Nhist][Npt];

TH1F *mh1hist_Dca_Dplus[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Bplus[mh2Nhist][Npt];

TH1F *mh1hist_Dca_Dminus[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Bminus[mh2Nhist][Npt];

TH1F *mh1hist_Dca_D[mh2Nhist][Npt];
TH1F *mh1hist_Dca_B[mh2Nhist][Npt];

TH1F *mh1hist_Dca_D0_rebin[mh2Nhist][Npt];
TH1F *mh1hist_Dca_B0_rebin[mh2Nhist][Npt];

TH1F *mh1hist_Dca_D0bar_rebin[mh2Nhist][Npt];
TH1F *mh1hist_Dca_B0bar_rebin[mh2Nhist][Npt];

TH1F *mh1hist_Dca_Dplus_rebin[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Bplus_rebin[mh2Nhist][Npt];

TH1F *mh1hist_Dca_Dminus_rebin[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Bminus_rebin[mh2Nhist][Npt];

TH1F *mh1Charm_dca_rebin[mh2Nhist][Npt];
TH1F *mh1Bottom_dca_rebin[mh2Nhist][Npt];


TH1F *mh1hist_Dca_pi0[mh2Nhist][Npt];



TH1F *mh1hist_Dca_D_rebin[mh2Nhist][Npt];
TH1F *mh1hist_Dca_B_rebin[mh2Nhist][Npt];


TH1F *mh1Charm_dca[mh2Nhist][Npt];
TH1F *mh1Bottom_dca[mh2Nhist][Npt];







// TString mh1Title_dca[Npt]= {"1<p_{T} < 1.2 (GeV/c)",
// 			    "1.2<p_{T} < 1.5 (GeV/c)", 
// 			    "1.5<p_{T} < 2 (GeV/c)",
// 			    "2<p_{T} < 3 (GeV/c)",
// 			    "3<p_{T} < 4 (GeV/c)",
// 			    "4<p_{T} < 5 (GeV/c)",
// 			    "5<p_{T} < 6 (GeV/c)",

// };



// Int_t Xbin_low[Npt]= {20,25,31,41,61,81,101};
// Int_t Xbin_high[Npt]={24,30,40,60,80,120,120};


TString mh2DcaHistName_D0[mh2Nhist]={"mh2D0rDcaVspt0","mh2D0rDcaVspt1","mh2D0rDcaVspt2"};
TString mh2DcaHistName_B0[mh2Nhist]={"mh2B0rDcaVspt0","mh2B0rDcaVspt1","mh2B0rDcaVspt2"};

TString mh2DcaHistName_Dplus[mh2Nhist]={"mh2DplusrDcaVspt0","mh2DplusrDcaVspt1","mh2DplusrDcaVspt2"};
TString mh2DcaHistName_Bplus[mh2Nhist]={"mh2BplusrDcaVspt0","mh2BplusrDcaVspt1","mh2BplusrDcaVspt2"};

TString mh2DcaHistName_D0bar[mh2Nhist]={"mh2D0barrDcaVspt0","mh2D0barrDcaVspt1","mh2D0barrDcaVspt2"};
TString mh2DcaHistName_B0bar[mh2Nhist]={"mh2B0barrDcaVspt0","mh2B0barrDcaVspt1","mh2B0barrDcaVspt2"};

TString mh2DcaHistName_Dminus[mh2Nhist]={"mh2DminusrDcaVspt0","mh2DminusrDcaVspt1","mh2DminusrDcaVspt2"};
TString mh2DcaHistName_Bminus[mh2Nhist]={"mh2BminusrDcaVspt0","mh2BminusrDcaVspt1","mh2BminusrDcaVspt2"};



TString mh2DcaHistName_pi0[mh2Nhist]={"mh2pi0rDcaVspt0","mh2pi0rDcaVspt1","mh2pi0rDcaVspt2"};




// const int  nDcasDca = 54;
// Double_t const  DcaEdgeDca[nDcasDca+1] = {-0.1   , -0.09 ,     -0.08  ,   -0.07    , -0.06    , -0.05 , -0.0475 , -0.045 , -0.0425 , -0.04 , -0.0375 , -0.035 , -0.0325 , -0.03 , -0.0275 , -0.025 , -0.0225 , -0.02,-0.018,-0.016,-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014,0.016,0.018,0.02 ,0.0225 , 0.025 , 0.0275 , 0.03 , 0.0325 , 0.035 , 0.0375 , 0.04 , 0.0425 , 0.045 , 0.0475 , 0.05    , 0.06  ,  0.07    , 0.08    , 0.09   ,0.1};

TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
void Draw_mh2_dca_pt(TH2F * const a[],TH2F * const b[]);//,TH2F * const c[]);
void   Draw_cTao(TH1F * cTaoD0,TH1F *cTaoB0,TH1F *,TH1F *);
int Charm_Bottom_dca(){


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
 

  TFile * inFile_D0= new TFile("input/D0.root","READ");
  TFile * inFile_D0bar= new TFile("input/D0bar.root","READ");
  
  TFile * inFile_Dplus= new TFile("input/Dplus.root","READ");
  TFile * inFile_Dminus= new TFile("input/Dminus.root","READ");

  TFile * inFile_Bplus= new TFile("input/Bplus.root","READ");
  TFile * inFile_Bminus= new TFile("input/Bminus.root","READ");
  
   
  TFile * inFile_B0= new TFile("input/B0.root","READ");
  TFile * inFile_B0bar= new TFile("input/B0bar.root","READ");

  // TFile * inFile_D0= new TFile("input_Weight_from_data/D0.root","READ");
  //  TFile * inFile_D0bar= new TFile("input_Weight_from_data/D0bar.root","READ");
   
  //  TFile * inFile_Dplus= new TFile("input_Weight_from_data/Dplus.root","READ");
  //  TFile * inFile_Dminus= new TFile("input_Weight_from_data/Dminus.root","READ");

  //  TFile * inFile_Bplus= new TFile("input_Weight_from_data/Bplus.root","READ");
  //  TFile * inFile_Bminus= new TFile("input_Weight_from_data/Bminus.root","READ");
   
   
  //  TFile * inFile_B0= new TFile("input_Weight_from_data/B0.root","READ");
  //  TFile * inFile_B0bar= new TFile("input_Weight_from_data/B0bar.root","READ");

   
   TFile * inFile_pi0= new TFile("input/pi0.root","READ");
   TFile *file_fastsim=new TFile("File_fastsim.root","RECREATE");


   //bin/  TFile * inFile_D0_kunnsu= new TFile("D0_eta_0.7Cut_rebin400.root","READ");
  //   TFile * inFile_D0_kunnsu= new TFile("Dplus_eta_0.7Cut_rebin400_fixedEtaCut.root","READ");


  // TH2F * mh2Hist_DcaD0_xiaozhi=(TH2F *) inFile_Dplus->Get("mh2DplusrDcaVspt1");
  // TH2F * mh2Hist_DcaD0_kunsu=(TH2F *) inFile_D0_kunnsu->Get("mh2DplusrDcaVspt1");

  // TH1F *  h1_xiaozhi= (TH1F *)mh2Hist_DcaD0_xiaozhi->ProjectionY("h1_xiaozhi",41,60);
  // TH1F *  h1_Kunsu= (TH1F *)mh2Hist_DcaD0_kunsu->ProjectionY("h1_kunsu",21,30);

  // h1_xiaozhi->Divide(h1_Kunsu);
  // h1_xiaozhi->Draw();

  // return 0;






 for(Int_t ihist=0;ihist<mh2Nhist;ihist++)
    {


      mh2Hist_DcaVsPt_D0[ihist]=(TH2F *) inFile_D0->Get(mh2DcaHistName_D0[ihist]);
      mh2Hist_DcaVsPt_Dplus[ihist]=(TH2F *) inFile_Dplus->Get(mh2DcaHistName_Dplus[ihist]);
      mh2Hist_DcaVsPt_Bplus[ihist]=(TH2F *) inFile_Bplus->Get(mh2DcaHistName_Bplus[ihist]);
      mh2Hist_DcaVsPt_B0[ihist]=(TH2F *) inFile_B0->Get(mh2DcaHistName_B0[ihist]);

      mh2Hist_DcaVsPt_D0bar[ihist]=(TH2F *) inFile_D0bar->Get(mh2DcaHistName_D0[ihist]);
      mh2Hist_DcaVsPt_D0bar[ihist]->SetName(mh2Hist_DcaVsPt_D0bar[ihist]->GetName()+TString("D0bar"));
      mh2Hist_DcaVsPt_B0bar[ihist]=(TH2F *) inFile_B0bar->Get(mh2DcaHistName_B0[ihist]);
      mh2Hist_DcaVsPt_B0bar[ihist]->SetName(mh2Hist_DcaVsPt_B0bar[ihist]->GetName()+TString("B0bar"));

      mh2Hist_DcaVsPt_Dminus[ihist]=(TH2F *) inFile_Dminus->Get(mh2DcaHistName_Dplus[ihist]);
      mh2Hist_DcaVsPt_Dminus[ihist]->SetName(mh2Hist_DcaVsPt_Dminus[ihist]->GetName()+TString("Dminus"));
      mh2Hist_DcaVsPt_Bminus[ihist]=(TH2F *) inFile_Bminus->Get(mh2DcaHistName_Bplus[ihist]);
      mh2Hist_DcaVsPt_Bminus[ihist]->SetName(mh2Hist_DcaVsPt_Bminus[ihist]->GetName()+TString("Bminus"));

      
      mh2Hist_DcaVsPt_pi0[ihist]=(TH2F *) inFile_pi0->Get(mh2DcaHistName_pi0[ihist]);
      
      mh2Hist_DcaVsPt_D0[ihist]->SetTitle("D^{0} #rightarrow e");
      mh2Hist_DcaVsPt_B0[ihist]->SetTitle("B^{0} #rightarrow e");

      
      mh2Hist_DcaVsPt_D0[ihist]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      mh2Hist_DcaVsPt_D0[ihist]->GetYaxis()->SetTitle(Ymh2Titlename[ihist]);
      
      mh2Hist_DcaVsPt_B0[ihist]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      mh2Hist_DcaVsPt_B0[ihist]->GetYaxis()->SetTitle(Ymh2Titlename[ihist]);


      mh2Hist_DcaVsPt_D0[ihist]->GetXaxis()->CenterTitle(true);
      mh2Hist_DcaVsPt_D0[ihist]->GetYaxis()->CenterTitle(true);


      mh2Hist_DcaVsPt_B0[ihist]->GetXaxis()->CenterTitle(true);
      mh2Hist_DcaVsPt_B0[ihist]->GetYaxis()->CenterTitle(true);

      cout<< " ihist "<< ihist<<endl;
     
      for(Int_t ipt=0;ipt<Npt;ipt++)
      	{

      	  sprintf(buf,"mh1rDca_hist%ipt%i_D0",ihist,ipt);
      	  mh1hist_Dca_D0[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_D0[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
	  sprintf(buf,"mh1rDca_hist%ipt%i_D0bar",ihist,ipt);
      	  mh1hist_Dca_D0bar[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_D0bar[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
	  
	  mh1hist_Dca_D0_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_D0[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_D0[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  mh1hist_Dca_D0bar_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_D0bar[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_D0bar[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  
      	  sprintf(buf,"mh1rDca_hist%ipt%iB0",ihist,ipt);
      	  mh1hist_Dca_B0[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_B0[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      	  sprintf(buf,"mh1rDca_hist%ipt%iB0bar",ihist,ipt);
      	  mh1hist_Dca_B0bar[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_B0bar[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
	  
      	  sprintf(buf,"mh1rDca_hist%ipt%iDplus",ihist,ipt);
      	  mh1hist_Dca_Dplus[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_Dplus[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);

      	  sprintf(buf,"mh1rDca_hist%ipt%iBplus",ihist,ipt);
      	  mh1hist_Dca_Bplus[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_Bplus[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);

	  
	  sprintf(buf,"mh1rDca_hist%ipt%iDminus",ihist,ipt);
      	  mh1hist_Dca_Dminus[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_Dminus[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);

      	  sprintf(buf,"mh1rDca_hist%ipt%iBminus",ihist,ipt);
      	  mh1hist_Dca_Bminus[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_Bminus[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);


	  mh1hist_Dca_D0_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_D0[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_D0[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  mh1hist_Dca_D0bar_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_D0bar[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_D0bar[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);

	  mh1hist_Dca_B0_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_B0[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_B0[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  mh1hist_Dca_B0bar_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_B0bar[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_B0bar[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  
	  mh1hist_Dca_Dplus_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_Dplus[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_Dplus[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  mh1hist_Dca_Bplus_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_Bplus[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_Bplus[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);

	  mh1hist_Dca_Dminus_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_Dminus[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_Dminus[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  mh1hist_Dca_Bminus_rebin[ihist][ipt]= (TH1F *) mh1hist_Dca_Bminus[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_Bminus[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  	  
      	  sprintf(buf,"mh1rDca_hist%ipt%ipi0",ihist,ipt);
      	  mh1hist_Dca_pi0[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_pi0[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);

	  	  
	  
	  // mh1hist_Dca_D0_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_D0_rebin[ihist][ipt]->Integral(),"width");
	  // mh1hist_Dca_D0bar_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_D0bar_rebin[ihist][ipt]->Integral(),"width");
      	  // mh1hist_Dca_Dplus_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_Dplus_rebin[ihist][ipt]->Integral(),"width");
	  // mh1hist_Dca_Dminus_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_Dminus_rebin[ihist][ipt]->Integral(),"width");

	  // mh1hist_Dca_B0_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_B0_rebin[ihist][ipt]->Integral(),"width");
      	  // mh1hist_Dca_B0bar_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_B0bar_rebin[ihist][ipt]->Integral(),"width");
	  // mh1hist_Dca_Bplus_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_Bplus_rebin[ihist][ipt]->Integral(),"width");
	  // mh1hist_Dca_Bminus_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_Bminus_rebin[ihist][ipt]->Integral(),"width");

	  mh1hist_Dca_D0_rebin[ihist][ipt]->Add(mh1hist_Dca_D0bar_rebin[ihist][ipt]);
	  mh1hist_Dca_Dplus_rebin[ihist][ipt]->Add(mh1hist_Dca_Dminus_rebin[ihist][ipt]);

	  mh1hist_Dca_B0_rebin[ihist][ipt]->Add(mh1hist_Dca_B0bar_rebin[ihist][ipt]);
	  mh1hist_Dca_Bplus_rebin[ihist][ipt]->Add(mh1hist_Dca_Bminus_rebin[ihist][ipt]);
	  
	  
	  // mh1hist_Dca_D0[ihist][ipt]->Scale(1.,"width");
	  // mh1hist_Dca_D0bar[ihist][ipt]->Scale(1.,"width");
      	  // mh1hist_Dca_Dplus[ihist][ipt]->Scale(1.,"width");

	  // mh1hist_Dca_B0[ihist][ipt]->Scale(1.,"width");
      	  // mh1hist_Dca_B0bar[ihist][ipt]->Scale(1.,"width");
	  // mh1hist_Dca_Bplus[ihist][ipt]->Scale(1.,"width");
	  


	  
	  sprintf(buf,"mh1rDca_hist%ipt%i_D",ihist,ipt);
	  mh1hist_Dca_D_rebin[ihist][ipt]=(TH1F *) mh1hist_Dca_D0_rebin[ihist][ipt]->Clone(buf);

	  sprintf(buf,"mh1rDca_hist%ipt%i_B",ihist,ipt);
	  mh1hist_Dca_B_rebin[ihist][ipt]=(TH1F *) mh1hist_Dca_B0_rebin[ihist][ipt]->Clone(buf);


	  //https://arxiv.org/pdf/1509.01061.pdf
	  // 0.6086/(0.6086+0.2404)=0.7168 systematic uncertainty 0.723 0.277
	  // B 0.5 0.5 
	    mh1hist_Dca_D_rebin[ihist][ipt]->Scale(0.7168);

	    // mh1hist_Dca_D_rebin[ihist][ipt]->Scale(0.7168);
	    // mh1hist_Dca_D_rebin[ihist][ipt]->Scale(0.723);

	  mh1hist_Dca_B_rebin[ihist][ipt]->Scale(0.5);
	  
	  mh1hist_Dca_D_rebin[ihist][ipt]->Add(mh1hist_Dca_Dplus_rebin[ihist][ipt],0.2832);

	  //mh1hist_Dca_D_rebin[ihist][ipt]->Add(mh1hist_Dca_Dplus_rebin[ihist][ipt],0.277);
	  
	  mh1hist_Dca_B_rebin[ihist][ipt]->Add(mh1hist_Dca_Bplus_rebin[ihist][ipt],0.5);

	  // mh1hist_Dca_D_rebin[ihist][ipt]->Scale(0.5);
	  // mh1hist_Dca_B_rebin[ihist][ipt]->Scale(0.5);

	  



      	  mh1hist_Dca_D0_rebin[ihist][ipt]->GetYaxis()->SetTitle("");
	  mh1hist_Dca_B0_rebin[ihist][ipt]->GetYaxis()->SetTitle("");

	  mh1hist_Dca_D0_rebin[ihist][ipt]->GetXaxis()->SetLabelSize(0.04);
	  mh1hist_Dca_B0_rebin[ihist][ipt]->GetXaxis()->SetLabelSize(0.04);

	  mh1hist_Dca_D0_rebin[ihist][ipt]->GetYaxis()->SetLabelSize(0.04);
	  mh1hist_Dca_B0_rebin[ihist][ipt]->GetYaxis()->SetLabelSize(0.04);

      	  mh1hist_Dca_D0_rebin[ihist][ipt]->SetTitle(mh1Title[ipt]);
	  mh1hist_Dca_B0_rebin[ihist][ipt]->SetTitle(mh1Title[ipt]);

      	  mh1hist_Dca_D0_rebin[ihist][ipt]->SetLineColor(1);
	  mh1hist_Dca_D0bar_rebin[ihist][ipt]->SetLineColor(3);
      	  mh1hist_Dca_Dplus_rebin[ihist][ipt]->SetLineColor(2);
	  mh1hist_Dca_D_rebin[ihist][ipt]->SetLineColor(4);
	  
	  mh1hist_Dca_B0_rebin[ihist][ipt]->SetLineColor(1);
      	  mh1hist_Dca_B0bar_rebin[ihist][ipt]->SetLineColor(3);
	  mh1hist_Dca_Bplus_rebin[ihist][ipt]->SetLineColor(2);
	  mh1hist_Dca_B_rebin[ihist][ipt]->SetLineColor(4);

	  //  mh1hist_Dca_pi0_rebin[ihist][ipt]->SetLineColor(11);

	  mh1hist_Dca_D_rebin[ihist][ipt]->SetTitle(mh1Title[ipt]);
	  mh1hist_Dca_B_rebin[ihist][ipt]->SetTitle(mh1Title[ipt]);


	  
	  file_fastsim->cd();
	  // mh1hist_Dca_D_rebin_rebin[ihist][ipt]=(TH1F *) mh1hist_Dca_D_rebin[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_D_rebin[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  // mh1hist_Dca_B_rebin_rebin[ihist][ipt]=(TH1F *) mh1hist_Dca_B_rebin[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_B_rebin[ihist][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
	  
	  // mh1hist_Dca_D_rebin_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);
	  // mh1hist_Dca_B_rebin_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);
	  // mh1hist_Dca_D_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);
	  // mh1hist_Dca_B_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);

	  // mh1hist_Dca_D_rebin_rebin[ihist][ipt]->Scale(1.,"width");
	  // mh1hist_Dca_B_rebin_rebin[ihist][ipt]->Scale(1.,"width");
	  // mh1hist_Dca_D_rebin[ihist][ipt]->Scale(1.,"width");
	  // mh1hist_Dca_B_rebin[ihist][ipt]->Scale(1.,"width");
	  
	  
	  mh1hist_Dca_D_rebin[ihist][ipt]->Write();
	  mh1hist_Dca_B_rebin[ihist][ipt]->Write();
	  // mh1hist_Dca_D_rebin_rebin[ihist][ipt]->Write();
	  // mh1hist_Dca_B_rebin_rebin[ihist][ipt]->Write();

	  
	  // mh1hist_Dca_D0_rebin[ihist][ipt]->Scale(0.0649*2);
	  // mh1hist_Dca_B0_rebin[ihist][ipt]->Scale(0.101*2);
	  // mh1hist_Dca_B0_rebin[ihist][ipt]->Scale(2./21);

	  //  mh1hist_Dca_D0bar_rebin[ihist][ipt]->Scale(0.0649);
	  //  mh1hist_Dca_B0bar_rebin[ihist][ipt]->Scale(0.101);
	  // mh1hist_Dca_Dplus_rebin[ihist][ipt]->Scale(0.1607*2);
	  // mh1hist_Dca_Bplus_rebin[ihist][ipt]->Scale(0.108*2);
	  // mh1hist_Dca_Bplus_rebin[ihist][ipt]->Scale(2./21);
	 
	  // mh1hist_Dca_pi0_rebin[ihist][ipt]->Scale();


	  


 	  // mh1hist_Dca_D0_rebin[ihist][ipt]->Rebin(4);
	  // mh1hist_Dca_B0_rebin[ihist][ipt]->Rebin(4);
	  // mh1hist_Dca_D0bar_rebin[ihist][ipt]->Rebin(4);
	  // mh1hist_Dca_B0bar_rebin[ihist][ipt]->Rebin(4);
	  // mh1hist_Dca_Dplus_rebin[ihist][ipt]->Rebin(4);
	  // mh1hist_Dca_Bplus_rebin[ihist][ipt]->Rebin(4);


	  // mh1hist_Dca_D0_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.06,0.06);
	  // mh1hist_Dca_B0_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.06,0.06);
	  // mh1hist_Dca_D0bar_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.06,0.06);
	  // mh1hist_Dca_B0bar_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.06,0.06);
	  // mh1hist_Dca_Dplus_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.06,0.06);
	  // mh1hist_Dca_Bplus_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.06,0.06);
	  
	  




	  // mh1hist_Dca_D0_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_D0_rebin[ihist][ipt]->Integral());
	  // mh1hist_Dca_B0_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_B0_rebin[ihist][ipt]->Integral());
	  // mh1hist_Dca_D0bar_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_D0bar_rebin[ihist][ipt]->Integral());
	  // mh1hist_Dca_B0bar_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_B0bar_rebin[ihist][ipt]->Integral());
	  // mh1hist_Dca_Dplus_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_Dplus_rebin[ihist][ipt]->Integral());
	  // mh1hist_Dca_Bplus_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_Bplus_rebin[ihist][ipt]->Integral());
	  // mh1hist_Dca_pi0_rebin[ihist][ipt]->Scale(1./mh1hist_Dca_pi0_rebin[ihist][ipt]->Integral());

	  // mh1hist_Dca_pi0_rebin[ihist][ipt]->Sumw2();

	  // mh1hist_Dca_D0_rebin[ihist][ipt]->Scale(1./1e7);
	  // mh1hist_Dca_B0_rebin[ihist][ipt]->Scale(1./1e7);
	  // mh1hist_Dca_D0bar_rebin[ihist][ipt]->Scale(1./1e7);
	  // mh1hist_Dca_B0bar_rebin[ihist][ipt]->Scale(1./1e7);
	  // mh1hist_Dca_Dplus_rebin[ihist][ipt]->Scale(1./1e7);
	  // mh1hist_Dca_Bplus_rebin[ihist][ipt]->Scale(1./1e7);
	}
    }

  // draw D D+
  TLegend *legend_D  = new TLegend(0.15,0.65,0.4,0.85);
  legend_D ->AddEntry(mh1hist_Dca_D0_rebin[0][0],"D^{0}->e","l");
  //legend_D ->AddEntry(mh1hist_Dca_D0bar[0][0],"#bar{D0}->e","l");
  legend_D ->AddEntry(mh1hist_Dca_Dplus_rebin[0][0],"D^{+}->e","l");
  legend_D ->AddEntry(mh1hist_Dca_D_rebin[0][0],"Charm->e","l");

  legend_D ->SetBorderSize(0);
  legend_D ->SetTextSize(0.05);
  legend_D ->SetFillStyle(0);
  legend_D ->SetTextFont(62);

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
	  if(ihist==1)
	    c6_D->cd(ipt+1);
	  if(ihist==2)
	    c7_D->cd(ipt+1);
	  gPad->SetLogy();
	    mh1hist_Dca_D0_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);
	  mh1hist_Dca_D0_rebin[ihist][ipt]->Sumw2(0);
	  mh1hist_Dca_D0bar_rebin[ihist][ipt]->Sumw2(0);
	  mh1hist_Dca_Dplus_rebin[ihist][ipt]->Sumw2(0);
	  mh1hist_Dca_D_rebin[ihist][ipt]->Sumw2(0);

	  mh1hist_Dca_D0_rebin[ihist][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
	  mh1hist_Dca_D0_rebin[ihist][ipt]->Draw("C");
	  // mh1hist_Dca_D0bar_rebin[ihist][ipt]->Draw("sameC");
	  mh1hist_Dca_Dplus_rebin[ihist][ipt]->Draw("sameC");
	  mh1hist_Dca_D_rebin[ihist][ipt]->Draw("sameC");
	  legend_D->Draw();
	}
    }

    c5_D->SaveAs("Plots/D_3ddca.pdf");
    c6_D->SaveAs("Plots/D_dcaXy.pdf");
    c7_D->SaveAs("Plots/D_sdcaZ.pdf");

    //   // draw B B+
  TLegend *legend_B  = new TLegend(0.15,0.65,0.4,0.85);
  legend_B ->AddEntry(mh1hist_Dca_B0_rebin[0][0],"B^{0}->e","l");
  // legend_B ->AddEntry(mh1hist_Dca_B0bar[0][0],"#bar{B0}->e","l");
  legend_B ->AddEntry(mh1hist_Dca_Bplus_rebin[0][0],"B^{+}->e","l");
  legend_B ->AddEntry(mh1hist_Dca_B_rebin[0][0],"Bottom->e","l");

  legend_B ->SetBorderSize(0);
  legend_B ->SetTextSize(0.05);
  legend_B ->SetFillStyle(0);
  legend_B ->SetTextFont(62);

  TCanvas *c5_B=new TCanvas("c5_B","",1200,1200);
  TCanvas *c6_B=new TCanvas("c6_B","",1200,1200);
  TCanvas *c7_B=new TCanvas("c7_B","",1200,1200);
  
  c5_B->Divide(4,2);
  c6_B->Divide(4,2);
  c7_B->Divide(4,2);

  
    for(Int_t ihist=0;ihist<mh2Nhist;ihist++)
    {
      for(Int_t ipt=0;ipt<Npt;ipt++)
  	{
	  if(ihist==0)
	    c5_B->cd(ipt+1);
	  if(ihist==1)
	    c6_B->cd(ipt+1);
	  if(ihist==2)
	    c7_B->cd(ipt+1);
	  gPad->SetLogy();
	    mh1hist_Dca_B0_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);
	  mh1hist_Dca_B0_rebin[ihist][ipt]->Sumw2(0);
	  mh1hist_Dca_B0bar_rebin[ihist][ipt]->Sumw2(0);
	  mh1hist_Dca_Bplus_rebin[ihist][ipt]->Sumw2(0);
	  mh1hist_Dca_B_rebin[ihist][ipt]->Sumw2(0);

	  mh1hist_Dca_B0_rebin[ihist][ipt]->GetXaxis()->SetTitle("DCA_{XY} (cm)");
	  
	  mh1hist_Dca_B0_rebin[ihist][ipt]->Draw("C");
	  // mh1hist_Dca_B0bar_rebin[ihist][ipt]->Draw("sameC");
	  mh1hist_Dca_Bplus_rebin[ihist][ipt]->Draw("sameC");
	  mh1hist_Dca_B_rebin[ihist][ipt]->Draw("sameC");

	  legend_B->Draw();
	}
    }

    c5_B->SaveAs("Plots/B_3ddca.pdf");
    c6_B->SaveAs("Plots/B_dcaXy.pdf");
    c7_B->SaveAs("Plots/B_sdcaZ.pdf");


    return 0;
    
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++)
    {
      for(Int_t ipt=0;ipt<Npt;ipt++)
  	{
	  sprintf(buf,"Charm_dca%ihist%ipt",ihist,ipt);
	  mh1Charm_dca_rebin[ihist][ipt]=(TH1F *)  mh1hist_Dca_D0_rebin[ihist][ipt]->Clone(buf);
	  sprintf(buf,"Bottom_dca%ihist%ipt",ihist,ipt);
	  mh1Bottom_dca_rebin[ihist][ipt]=(TH1F *)  mh1hist_Dca_B0_rebin[ihist][ipt]->Clone(buf);

	  mh1Charm_dca_rebin[ihist][ipt]->Add(mh1hist_Dca_Dplus_rebin[ihist][ipt],0.332);
	  mh1Bottom_dca_rebin[ihist][ipt]->Add(mh1hist_Dca_Bplus_rebin[ihist][ipt],1);

	  if(ipt==0)
	    mh1Charm_dca_rebin[ihist][ipt]->Scale(7.53/(mh1Charm_dca_rebin[ihist][ipt]->Integral()/mh1Bottom_dca_rebin[ihist][ipt]->Integral()));
	  if(ipt==1)
	    mh1Charm_dca_rebin[ihist][ipt]->Scale(1.35/(mh1Charm_dca_rebin[ihist][ipt]->Integral()/mh1Bottom_dca_rebin[ihist][ipt]->Integral()));
	  if(ipt==2)
	    mh1Charm_dca_rebin[ihist][ipt]->Scale(0.83/(mh1Charm_dca_rebin[ihist][ipt]->Integral()/mh1Bottom_dca_rebin[ihist][ipt]->Integral()));
	  if(ipt==3)
	    mh1Charm_dca_rebin[ihist][ipt]->Scale(0.64/(mh1Charm_dca_rebin[ihist][ipt]->Integral()/mh1Bottom_dca_rebin[ihist][ipt]->Integral()));
	  

	  if(ihist==0)
	  cout << mh1Charm_dca_rebin[ihist][ipt]->Integral()/mh1Bottom_dca_rebin[ihist][ipt]->Integral()<<endl;

	  mh1Charm_dca_rebin[ihist][ipt]->SetLineColor(8);
	  mh1Bottom_dca_rebin[ihist][ipt]->SetLineColor(9);
	  mh1Charm_dca_rebin[ihist][ipt]->SetLineWidth(3);
	  mh1Bottom_dca_rebin[ihist][ipt]->SetLineWidth(3);

	  mh1Charm_dca_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);
	  mh1Bottom_dca_rebin[ihist][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);

	  mh1Charm_dca_rebin[ihist][ipt]->SetTitle(mh1Title[ipt]);
	  mh1Bottom_dca_rebin[ihist][ipt]->SetTitle(mh1Title[ipt]);


  	}
    }

  
  TCanvas *c2=new TCanvas("c2","",1200,600);
  TCanvas *c3=new TCanvas("c3","",1200,600);
  TCanvas *c4=new TCanvas("c4","",1200,600);

  c2->Divide(2,2);
  c3->Divide(2,2);
  c4->Divide(2,2);



  
  TLegend *legend  = new TLegend(0.6,0.5,0.85,0.86);
  //  legend ->AddEntry(mh1hist_Dca_D0[0][0],"D0 #rightarrow e ","lp");
  //  legend ->AddEntry(mh1hist_Dca_D0bar[0][0],"D0bar  #rightarrow e ","lp");
  // legend ->AddEntry(mh1hist_Dca_B0[0][0],"B0  #rightarrow e ","lp");
  // legend ->AddEntry(mh1hist_Dca_B0bar[0][0],"B0bar  #rightarrow e ","lp");
  //  legend ->AddEntry(mh1hist_Dca_Dplus[0][0],"D+  #rightarrow e ","lp");
  //  legend ->AddEntry(mh1hist_Dca_Bplus[0][0],"B+  #rightarrow e ","lp");

   legend ->AddEntry(mh1Charm_dca[0][0],"D #rightarrow e ","lp");
   legend ->AddEntry(mh1Bottom_dca[0][0],"B  #rightarrow e ","lp");
  // legend ->AddEntry(mh1hist_Dca_pi0[0][0],"pi0  #rightarrow e ","lp");
  

  legend ->SetBorderSize(0);
  legend ->SetTextSize(0.045);
  legend ->SetFillStyle(0);
  legend ->SetTextFont(62);
  
  


  for(Int_t ihist=0;ihist<mh2Nhist;ihist++)
    {
      for(Int_t ipt=0;ipt<Npt;ipt++)
	{
	  if(ihist==0)
	    c2->cd(ipt+1);
	  if(ihist==1)
	    c3->cd(ipt+1);
	  if(ihist==2)
	    c4->cd(ipt+1);

	  gPad->SetLogy();
      	  
	  //  mh1hist_Dca_D0_rebin[ihist][ipt]->Draw("L");
	  //  mh1hist_Dca_B0_rebin[ihist][ipt]->Draw("sameL");
	  // // mh1hist_Dca_D0bar_rebin[ihist][ipt]->Draw("sameL");
	  // // mh1hist_Dca_B0bar_rebin[ihist][ipt]->Draw("sameL");
	  //  mh1hist_Dca_Dplus_rebin[ihist][ipt]->Draw("sameL");
	  //  mh1hist_Dca_Bplus_rebin[ihist][ipt]->Draw("sameL");
	  //  mh1hist_Dca_pi0_rebin[ihist][ipt]->Draw("sameL");





	   mh1Bottom_dca_rebin[ihist][ipt]->Draw("sameL");
	   mh1Charm_dca_rebin[ihist][ipt]->Draw("sameL");


	  
	  legend->Draw();
	  sprintf(buf,"Mean %4.3e +- %4.3e",mh1Charm_dca_rebin[ihist][ipt]->GetMean(),mh1Charm_dca_rebin[ihist][ipt]->GetMeanError());
	    drawLatex(0.15,0.85,buf,62,0.045,8);
	  sprintf(buf,"RMS %4.3e +- %4.3e",mh1Charm_dca_rebin[ihist][ipt]->GetRMS(),mh1Charm_dca_rebin[ihist][ipt]->GetRMSError());
	   drawLatex(0.15,0.8,buf,62,0.045,8);
          sprintf(buf,"Counts %4.3e ",mh1Charm_dca_rebin[ihist][ipt]->Integral());//,mh1Charm_dca_rebin[ihist][ipt]->IntegralAndError());
	   drawLatex(0.15,0.75,buf,62,0.045,8);



	  sprintf(buf,"Mean %4.3e +- %4.3e",mh1Bottom_dca_rebin[ihist][ipt]->GetMean(),mh1Bottom_dca_rebin[ihist][ipt]->GetMeanError());
	   drawLatex(0.15,0.7,buf,62,0.045,9);
	  sprintf(buf,"RMS %4.3e +- %4.3e",mh1Bottom_dca_rebin[ihist][ipt]->GetRMS(),mh1Bottom_dca_rebin[ihist][ipt]->GetRMSError());
	   drawLatex(0.15,0.65,buf,62,0.045,9);
	  sprintf(buf,"Counts %4.3e ",mh1Bottom_dca_rebin[ihist][ipt]->Integral());//,mh1Charm_dca_rebin[ihist][ipt]->IntegralAndError());
	   drawLatex(0.15,0.6,buf,62,0.045,9);


	}     
    }

  
  // c2->SaveAs("D_B_Rdca.gif");
  // c3->SaveAs("D_B_RdcaXY.gif");
  // c4->SaveAs("D_B_RdcaZ.gif");

  c2->SaveAs("D_B_Rdca.pdf");
  c3->SaveAs("D_B_RdcaXY.pdf");
  c4->SaveAs("D_B_RdcaZ.pdf");


  TFile *file_B_D=new TFile("NPE_fast_simulation.root","Recreate");
  for(int ihist=0;ihist<mh2Nhist;ihist++)
    {

      for(Int_t ipt=0;ipt<Npt;ipt++)
	{



	  //	  cout<<  mh1Bottom_dca_rebin_rebin[ihist][ipt]->GetName()<<endl;
	  mh1Bottom_dca_rebin[ihist][ipt]->Write();
	  mh1Charm_dca_rebin[ihist][ipt]->Write();

	  //  mh1Bottom_dca_rebin_rebin[ihist][ipt]->Write();
	  
	}
    }
  
  return 0;
  
  

      TH1F *cTaoD0=(TH1F *) inFile_D0->Get("mh2D0cTao");
      cTaoD0->SetName("cTaoD0");
      cTaoD0->SetTitle("D0 cTao");
      cTaoD0->GetXaxis()->SetRangeUser(0,7);

      TH1F *cTaoB0=(TH1F *) inFile_B0->Get("mh2B0cTao");
      cTaoB0->SetName("cTaoB0");
      cTaoB0->SetTitle("B0 cTao");
      cTaoB0->GetXaxis()->SetRangeUser(0,7);

      TH1F *cTaoB0_OC=(TH1F *) inFile_B0->Get("mh2OcB0barcTao");
      cTaoB0_OC->SetName("cTaoB0_OC");
      cTaoB0_OC->SetTitle("B0 cTao");
      cTaoB0_OC->GetXaxis()->SetRangeUser(0,7);
      cTaoB0->Add(cTaoB0_OC);


 
      TH1F *cTaoDplus=(TH1F *) inFile_Dplus->Get("mh2DpluscTao");
       cTaoDplus->SetName("cTaoDplus");
       cTaoDplus->SetTitle("D+ cTao");
       cTaoDplus->GetXaxis()->SetRangeUser(0,7);
       TH1F *cTaoBplus=(TH1F *) inFile_Bplus->Get("mh2BpluscTao");
       cTaoBplus->SetName("cTaoBplus");
       cTaoBplus->SetTitle("B+ cTao");
       cTaoBplus->GetXaxis()->SetRangeUser(0,7);

       //    Draw_mh2_dca_pt(mh2Hist_DcaVsPt_D0,mh2Hist_DcaVsPt_B0);
       // Draw_cTao(cTaoD0,cTaoB0,cTaoDplus,cTaoBplus);
}

void   Draw_cTao(TH1F * cTaoD0,TH1F *cTaoB0,TH1F * cTaoDplus,TH1F *cTaoBplus)
{
  gStyle->SetOptStat(111);  
  gStyle->SetOptFit(1111);

  Double_t p1=0;
  TF1 *f1=new TF1("f1","expo",0,10);  
  TCanvas *c3=new TCanvas("c3","",1200,1000);
  c3->Divide(2,2);
  c3->cd(1);
  gPad->SetLogy();
  cTaoD0->GetXaxis()->SetTitle("c#tau  (mm)");
  cTaoD0->GetYaxis()->SetTitle("Counts");
  cTaoD0->Fit("f1");

  sprintf(buf,"c #tau %4.5f (#mum)",-1./f1->GetParameter(1)*1e3);
  drawLatex(0.6,0.45,buf,62,0.07,2);

  sprintf(buf,"c #tau 123 (#mum) (PDG) ");
  drawLatex(0.6,0.35,buf,62,0.07,4);
  

  // p1=f1->GetParameter(1);


  c3->cd(2);
  gPad->SetLogy();
  cTaoB0->GetXaxis()->SetTitle("c#tau  (mm)");
  cTaoB0->GetYaxis()->SetTitle("Counts");
  // cTaoB0->Fit("expo");
  cTaoB0->Draw();
  c3->cd(3);
  gPad->SetLogy();
  cTaoDplus->GetXaxis()->SetTitle("c#tao  (mm) ");
  cTaoDplus->GetYaxis()->SetTitle("Counts");
  cTaoDplus->Fit("f1");
  //  p1=f1->GetParameter(1);

  sprintf(buf,"c #tau %4.5f (#mum)",-1./f1->GetParameter(1)*1e3);
  drawLatex(0.6,0.45,buf,62,0.07,2);

  sprintf(buf,"c #tau 312 (#mum) (PDG) ");
  drawLatex(0.6,0.35,buf,62,0.07,4);

  c3->cd(4);
  gPad->SetLogy();
  cTaoBplus->GetXaxis()->SetTitle("c#tau  (mm)");
  cTaoBplus->GetYaxis()->SetTitle("Counts");
  cTaoBplus->Fit("f1");


  sprintf(buf,"c #tau %4.5f (#mum)",-1./f1->GetParameter(1)*1e3);
  drawLatex(0.6,0.45,buf,62,0.07,2);

  sprintf(buf,"c #tau 491 (#mum) (PDG) ");
  drawLatex(0.6,0.35,buf,62,0.07,4);

  c3->SaveAs("ctao.pdf");
}

void Draw_mh2_dca_pt(TH2F * const D0[],TH2F * const B0[])//,TH2F * const c[])
{
  TH2F *mh2Hist_DcaVsPt_D0[mh2Nhist];
  TH2F *mh2Hist_DcaVsPt_B0[mh2Nhist];
  
  TCanvas *c2=new TCanvas("c2","",1200,600);
  c2->Divide(3,2);
    for(int ihist=0;ihist<mh2Nhist;ihist++)

    {
      sprintf(buf,"ihist%i",ihist);
      mh2Hist_DcaVsPt_D0[ihist]=(TH2F *) D0[ihist]->Clone(mh2DcaHistName_D0[ihist]+buf);
      mh2Hist_DcaVsPt_B0[ihist]=(TH2F *) B0[ihist]->Clone(mh2DcaHistName_B0[ihist]+buf);
      c2->cd(ihist+1);
      gPad->SetLogz();
      mh2Hist_DcaVsPt_D0[ihist]->Draw("COLZ");
      c2->cd(ihist+4);
      gPad->SetLogz();
      mh2Hist_DcaVsPt_B0[ihist]->Draw("COLZ");
    }
    c2->SaveAs("mh2dca_pt.png");
}



  // // TH1F * pi_dcaXY=new TH1F("pi_dcaXY","",Npt,ptbin);
  // // TH1F * pi_dcaZ=new TH1F("pi_dcaZ","",Npt,ptbin);

  // // TH1F * ele_dcaXY=new TH1F("ele_dcaXY","",Npt,ptbin);
  // // TH1F * ele_dcaZ=new TH1F("ele_dcaZ","",Npt,ptbin);

  // // TH1F * gross_pi_dcaXY=new TH1F("gross_pi_dcaXY","",Npt,ptbin);
  // // TH1F * gross_pi_dcaZ=new TH1F("gross_pi_dcaZ","",Npt,ptbin);

  // // TH1F * gross_ele_dcaXY=new TH1F("gross_ele_dcaXY","",Npt,ptbin);
  // // TH1F * gross_ele_dcaZ=new TH1F("gross_ele_dcaZ","",Npt,ptbin);



  // //   for(int ihist=0;ihist<mh2Nhist;ihist++){

  // // TCanvas *c2=new TCanvas("c2","",1200,600);
  // // c2->Divide(2,1);

  // // TCanvas *c3=new TCanvas("c3","tet",800,600);
  // // c3->Divide(2,2);

  // // TCanvas *c4=new TCanvas("c4","",800,600);
  // // c4->Divide(2,2);

  // // TCanvas *c5=new TCanvas("c5","",800,600);
  // // c5->Divide(2,2);


  // // Double_t electr_reselutionXY[Npt];
  // // Double_t pi_reselutionXY[Npt];

  // // Double_t electr_reselutionZ[Npt];
  // // Double_t pi_reselutionZ[Npt];

   


    
  // //   c2->cd(1);
  // //   gPad->SetLogz();
  // //   mh2Hist_DcaVsPt_pion[ihist]->Draw("colz");
  // //   c2->cd(2);
  // //   gPad->SetLogz();
  // //   mh2Hist_DcaVsPt_electron[ihist]->Draw("colz");
  // //   c2->SaveAs(mh2DcaHistName_pi[ihist]+TString("Dca.gif"));
     
  // //   //  continue;
  // //   int ipad=1;
  // //   for(Int_t ipt=0;ipt<Npt;ipt++)
  // //     {
  // // 	if(ipt<4)
  // // 	  {
  // // 	    c3->cd(ipad);
  // // 	    gPad->SetLogy();
  // // 	  }
  // // 	else if( ipt<8)
  // // 	  {
  // // 	    c4->cd(ipad);
  // // 	    gPad->SetLogy();
  // // 	  }
  // // 	else	if(ipt<12)
  // // 	  {
  // // 	  c5->cd(ipad);
  // // 	  gPad->SetLogy();
  // // 	  }
  // // 	ipad++;
  // // 	if(ipad==5)
  // // 	  ipad=1;
  // // 	//mh1hist_Dca_pion_rebin[ihist][ipt]->Scale(mh1hist_Dca_pion_rebin[ihist][ipt]->Integral("width")/mh1hist_Dca_electron_rebin[ihist][ipt]->Integral("width"));	

	
	
  // // 	TF1 *f0 =new TF1(mh1hist_Dca_pion_rebin[ihist][ipt]->GetName(),"[0]*TMath::Gaus(x,[1],[2],1)",-1,1);// fit the dca
  // // 	TF1 *f1 =new TF1(mh1hist_Dca_electron_rebin[ihist][ipt]->GetName(),"[0]*TMath::Gaus(x,[1],[2],1)",-1,1);// fit the dca


  // // 	// TF1 *f0 =new TF1(mh1hist_Dca_pion_rebin[ihist][ipt]->GetName(),"[0]*TMath::Gaus(x,[1],[2],1)+[3]*TMath::Gaus(x,[4],[5],1)",-1,1);// fit the dca
  // // 	// TF1 *f1 =new TF1(mh1hist_Dca_electron_rebin[ihist][ipt]->GetName(),"[0]*TMath::Gaus(x,[1],[2],1)+[3]*TMath::Gaus(x,[4],[5],1)",-1,1);// fit the dca

  // // 	// TF1 *g0 =new TF1("g0","[0]*TMath::Gaus(x,[1],[2],1)",-1,1);// fit the dca 
  // // 	// TF1 *g1 =new TF1("g1","[0]*TMath::Gaus(x,[1],[2],1)",-1,1);// fit the dca 
       
  // // 	f0->SetParameter(1,0);
  // // 	f0->SetParameter(2,7e-4);
     
  // // 	// f0->SetParameter(4,0);
  // // 	// f0->SetParameter(5,5);
     
     

  // // 	f1->SetParameter(1,0);
  // // 	f1->SetParameter(2,7e-4);
     
  // // 	f0->SetLineColor(3);
  // // 	f1->SetLineColor(4);

  // // 	// g0->SetLineColor(6);
  // // 	// g1->SetLineColor(7);

  // // 	// g0->SetLineStyle(7);
  // // 	// g1->SetLineStyle(7);
     
  // // 	TLegend *legend  = new TLegend(0.6,0.65,0.85,0.85);
  // // 	legend ->AddEntry(mh1hist_Dca_pion_rebin[ihist][ipt],"#pi   ","lp");
  // // 	legend ->AddEntry(f0," Fit #pi   ","lp");
  // // 	legend ->AddEntry(mh1hist_Dca_electron_rebin[ihist][ipt],"e ","lp");
  // // 	legend ->AddEntry(f1," Fit e   ","lp");
     

     
 
  // // 	legend ->SetBorderSize(0);
  // // 	legend ->SetTextSize(0.045);
  // // 	legend ->SetFillStyle(0);
  // // 	legend ->SetTextFont(62);
   
	

	 
  // // 	//  c3->cd(1);
  // // 	// gPad->SetLogy();

  // // 	mh1hist_Dca_electron_rebin[ihist][ipt]->Draw();	
	
  // // 	mh1hist_Dca_pion_rebin[ihist][ipt]->Draw("same");
  // // 	legend->Draw();
	
  // // 	if(ihist>0)
  // // 	  {

  // // 	    mh1hist_Dca_pion_rebin[ihist][ipt]->Fit(f0,"R0","",-0.08,0.08);
  // // 	    mh1hist_Dca_pion_rebin[ihist][ipt]->Fit(f0,"R","",-0.08,0.08);
  // // 	    sprintf(buf,"#sigma _{#pi} %4.5f +- %4.5f",f0->GetParameter(2),f0->GetParError(2));

  // // 		int bin1=mh1hist_Dca_pion_rebin[ihist][ipt]->FindBin(f0->GetParameter(1)-3*f0->GetParameter(2));
  // // 		int bin2=mh1hist_Dca_pion_rebin[ihist][ipt]->FindBin(f0->GetParameter(1)+3*f0->GetParameter(2));
  // // 		int bin_total=mh1hist_Dca_pion_rebin[ihist][ipt]->GetNbinsX();
  // // 		Double_t pass=	mh1hist_Dca_pion_rebin[ihist][ipt]->Integral(0,bin1)+mh1hist_Dca_pion_rebin[ihist][ipt]->Integral(bin2,bin_total);
  // // 		Double_t total=	mh1hist_Dca_pion_rebin[ihist][ipt]->Integral();
	    
  // // 	    if(ihist==1)
  // // 	      {
  // // 		Double_t err0=f0->GetParError(0);
  // // 		Double_t err2=f0->GetParError(2);
  // // 		Double_t delta_0=err0/f0->GetParameter(0);
  // // 		Double_t delta_2=err2/f0->GetParameter(2);

  // // 		Double_t err=fabs(f0->GetParameter(0)*f0->GetParameter(2))*sqrt(delta_0*delta_0+delta_2*delta_2);

  // // 		pi_dcaXY->SetBinContent(ipt+1,f0->GetParameter(2));
  // // 		pi_dcaXY->SetBinError(ipt+1,f0->GetParError(2));
	
  // // 		// int bin1=mh1hist_Dca_pion_rebin[ihist][ipt]->FindBin(f0->GetParameter(1)-3*f0->GetParameter(2));
  // // 		// int bin2=mh1hist_Dca_pion_rebin[ihist][ipt]->FindBin(f0->GetParameter(1)+3*f0->GetParameter(2));
  // // 		// int bin_total=mh1hist_Dca_pion_rebin[ihist][ipt]->GetNbinsX();
  // // 		// Double_t pass=	mh1hist_Dca_pion_rebin[ihist][ipt]->Integral(0,bin1)+mh1hist_Dca_pion_rebin[ihist][ipt]->Integral(bin2,bin_total);
  // // 		// Double_t total=	mh1hist_Dca_pion_rebin[ihist][ipt]->Integral();
  // // 		//cout<< pass/total<< " !!!!!!!!!!!!!!!!!!!!!! "<<endl;
  // // 		gross_pi_dcaXY->SetBinContent(ipt+1,pass/total*100);

  // // 		//	throw (-1);
  // // 	      }

  // // 	    if(ihist==2)
  // // 	      {

  // // 		Double_t err0=f0->GetParError(0);
  // // 		Double_t err2=f0->GetParError(2);
  // // 		Double_t delta_0=err0/f0->GetParameter(0);
  // // 		Double_t delta_2=err2/f0->GetParameter(2);

  // // 		Double_t err=fabs(f0->GetParameter(0)*f0->GetParameter(2))*sqrt(delta_0*delta_0+delta_2*delta_2);
		
  // // 		pi_dcaZ->SetBinContent(ipt+1,f0->GetParameter(2));
  // // 		pi_dcaZ->SetBinError(ipt+1,f0->GetParError(2));
	      

  // // 		//cout<< pass/total<< " !!!!!!!!!!!!!!!!!!!!!! "<<endl;
  // // 		gross_pi_dcaZ->SetBinContent(ipt+1,pass/total*100);

  // // 	      }
	    

  // // 	    drawLatex(0.15,0.8,buf,62,0.045,3);
  // // 	    legend->Draw(); 
	    
  // // 	    mh1hist_Dca_electron_rebin[ihist][ipt]->Fit(f1,"R0","",-0.08,0.08);
  // // 	    mh1hist_Dca_electron_rebin[ihist][ipt]->Fit(f1,"R","",-0.08,0.08);


  // // 	     bin1=mh1hist_Dca_electron_rebin[ihist][ipt]->FindBin(f1->GetParameter(1)-3*f1->GetParameter(2));
  // // 	     bin2=mh1hist_Dca_electron_rebin[ihist][ipt]->FindBin(f1->GetParameter(1)+3*f1->GetParameter(2));
  // // 	     bin_total=mh1hist_Dca_electron_rebin[ihist][ipt]->GetNbinsX();
  // // 	     pass=	mh1hist_Dca_electron_rebin[ihist][ipt]->Integral(0,bin1)+mh1hist_Dca_electron_rebin[ihist][ipt]->Integral(bin2,bin_total);
  // // 	     total=	mh1hist_Dca_electron_rebin[ihist][ipt]->Integral();

  // // 	    if(ihist==1)
  // // 	      {
  // // 		Double_t err0=f1->GetParError(0);
  // // 		Double_t err2=f1->GetParError(2);
  // // 		Double_t delta_0=err0/f1->GetParameter(0);
  // // 		Double_t delta_2=err2/f1->GetParameter(2);

  // // 		Double_t err=fabs(f1->GetParameter(0)*f1->GetParameter(2))*sqrt(delta_0*delta_0+delta_2*delta_2);

  // // 		  ele_dcaXY->SetBinContent(ipt+1,f1->GetParameter(2));
  // // 		  ele_dcaXY->SetBinError(ipt+1,f1->GetParError(2));
  // // 		  gross_ele_dcaXY->SetBinContent(ipt+1,pass/total*100);	

  // // 	      }

  // // 	    if(ihist==2)
  // // 	      {
  // // 		Double_t err0=f1->GetParError(0);
  // // 		Double_t err2=f1->GetParError(2);
  // // 		Double_t delta_0=err0/f1->GetParameter(0);
  // // 		Double_t delta_2=err2/f1->GetParameter(2);

  // // 		Double_t err=fabs(f1->GetParameter(0)*f1->GetParameter(2))*sqrt(delta_0*delta_0+delta_2*delta_2);

  // // 		ele_dcaZ->SetBinContent(ipt+1,f1->GetParameter(2));
  // // 		ele_dcaZ->SetBinError(ipt+1,f1->GetParError(2));
  // // 		gross_ele_dcaZ->SetBinContent(ipt+1,pass/total*100);		      
  // // 	      }
	    
  // // 	    sprintf(buf,"#sigma _{e} %4.5f +- %4.5f",f1->GetParameter(2),f1->GetParError(2));
  // // 	    drawLatex(0.15,0.75,buf,62,0.045,4);
  // // 	    legend->Draw(); 
  // // 	  }  
  // //      }
  // //   c3->SaveAs(mh2DcaHistName_pi[ihist]+TString("mh1Dca_c3.png"));
  // //   c4->SaveAs(mh2DcaHistName_pi[ihist]+TString("mh1Dca_c4.png"));
  // //   c5->SaveAs(mh2DcaHistName_pi[ihist]+TString("mh1Dca_c5.png"));
  // //    }  
      
  // //   pi_dcaXY->SetMarkerStyle(20);
  // //   pi_dcaZ->SetMarkerStyle(24);
    
  // //   pi_dcaXY->SetMarkerColor(3);
  // //   pi_dcaZ->SetMarkerColor(3);
    
  // //   ele_dcaXY->SetMarkerStyle(20);
  // //   ele_dcaZ->SetMarkerStyle(24);

  // //   ele_dcaXY->SetMarkerColor(4);
  // //   ele_dcaZ->SetMarkerColor(4);

  // //   TLegend *legend  = new TLegend(0.65,0.65,0.85,0.85);
  // //   legend ->AddEntry(ele_dcaXY,"e dcaXY resolution   ","lp");
  // //   legend ->AddEntry(pi_dcaXY,"#pi dcaXY resolution   ","lp");
  // //   legend ->AddEntry(ele_dcaZ,"e dcaZ resolution    ","lp");
  // //   legend ->AddEntry(pi_dcaZ,"#pi dcaZ resolution   ","lp");
    
 
  // // 	legend ->SetBorderSize(0);
  // // 	legend ->SetTextSize(0.035);
  // // 	legend ->SetFillStyle(0);
  // // 	legend ->SetTextFont(62);
   
    

  // //   TCanvas *c7=new TCanvas("c7","",800,600);
  // //   TH2F *hh=new TH2F("hh","",100,0,15,10,0.0002,0.01);
  // //   hh->GetXaxis()->SetTitle(" p_{T} (GeV/c)");
  // //     hh->GetYaxis()->SetTitle(" Resolution");

  // //   hh->Draw();
  // //   pi_dcaXY->Draw("sameLP");
  // //   pi_dcaZ->Draw("sameLP");
  // //   ele_dcaXY->Draw("sameLP");
  // //   ele_dcaZ->Draw("sameLP");

  // //   legend->Draw();    
  // //   c7->SaveAs("pi_Re.pdf");
  // //   TH1F *ratio_XY=(TH1F *) pi_dcaXY->Clone("ratio_XY");
  // //   TH1F *ratio_Z=(TH1F *) pi_dcaZ->Clone("ratio_Z");
 
  // //   ratio_XY->Sumw2();
  // //   ratio_Z->Sumw2();

  // //   ratio_XY->Divide(ele_dcaXY);
  // //   ratio_Z->Divide(ele_dcaZ);



  // //   //-------------------

  // // TH1D *h_frame = new TH1D("h_frame","h_title",150,0,15);
  // // h_frame->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  // // h_frame->GetYaxis()->SetTitle("Resolution");

  // // TCanvas *c1 = new TCanvas("c1","c1",1050,750);
  // // c1->Divide(2,1);
  // // c1->cd(1)->SetPad(0.01,0.4,0.99,0.99);
  // // c1->cd(1)->SetBottomMargin(0.0);
  // // h_frame->GetYaxis()->SetRangeUser(0.0001,1.2*pi_dcaXY->GetMaximum());
  // // //  h_frame->SetTitle("gaussians");
  // // h_frame->DrawCopy();
  // // pi_dcaXY->Draw("pe,same");
  // // ele_dcaXY->Draw("pe,same");

  // // pi_dcaZ->Draw("pe,same");
  // // ele_dcaZ->Draw("pe,same");

  // // legend->Draw();

  // // c1->cd(2)->SetPad(0.01,0.01,0.99,0.4);
  // // c1->cd(2)->SetTopMargin   (0.0);
  // // c1->cd(2)->SetBottomMargin(0.1);
  // // TLine *line1 = new TLine(0,1,15,1);
  // // line1->SetLineStyle(2);
  // // line1->SetLineColor(16);
  // // h_frame->GetYaxis()->SetRangeUser(0.5,1.5);
  // // h_frame->SetTitle("ratio");
  // // h_frame->GetYaxis()->SetTitle(" #pi/e  ratio");
  // // h_frame->DrawCopy();
  // // ratio_XY->Draw("pe,same");
  // // ratio_Z->Draw("pe,same");

  // // line1->Draw("same");
  // //   //------------------



  // // c1->SaveAs("Ratio.pdf");




  // //   TCanvas *c6=new TCanvas("c6","",800,600);
  // //   gross_pi_dcaXY->SetMarkerStyle(20);
  // //   gross_ele_dcaXY->SetMarkerStyle(20);
  // //   gross_pi_dcaZ->SetMarkerStyle(24);
  // //   gross_ele_dcaZ->SetMarkerStyle(24);

  // //   gross_pi_dcaZ->SetMarkerColor(3);
  // //   gross_ele_dcaZ->SetMarkerColor(4);

  // //   gross_pi_dcaXY->SetMarkerColor(3);
  // //   gross_ele_dcaXY->SetMarkerColor(4);

  // //   TH2F * h2=new TH2F("h2","",150,0,15,100,0,60);

  // //   h2->Draw();
  // //   h2->GetXaxis()->SetTitle("p_{T} GeV/c");
  // //   h2->GetYaxis()->SetTitle("Grass out of 3 #sigma %");

  // //   gross_pi_dcaXY->Draw("sameP");
  //   gross_pi_dcaZ->Draw("sameP");

  //   gross_ele_dcaXY->Draw("sameP");
  //   gross_ele_dcaZ->Draw("sameP");

  //   legend->Draw();
  //   c6->SaveAs("BK_gross.pdf");

  //   return 0;
  // }

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
