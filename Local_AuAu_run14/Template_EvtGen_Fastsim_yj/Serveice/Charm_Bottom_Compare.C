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
#include "Binning_MB.h"

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

TH2F *mh2Hist_DcaVsPt_Dsplus[mh2Nhist];
TH2F *mh2Hist_DcaVsPt_Lcplus[mh2Nhist];

TH2F *mh2Hist_DcaVsPt_Dsminus[mh2Nhist];
TH2F *mh2Hist_DcaVsPt_Lcminus[mh2Nhist];




TH1F *mh1hist_Dca_D0[mh2Nhist][Npt];
TH1F *mh1hist_Dca_B0[mh2Nhist][Npt];

TH1F *mh1hist_Dca_D0bar[mh2Nhist][Npt];
TH1F *mh1hist_Dca_B0bar[mh2Nhist][Npt];

TH1F *mh1hist_Dca_Dplus[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Bplus[mh2Nhist][Npt];

TH1F *mh1hist_Dca_Dminus[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Bminus[mh2Nhist][Npt];

TH1F *mh1hist_Dca_Dsminus[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Lcminus[mh2Nhist][Npt];

TH1F *mh1hist_Dca_Dsplus[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Lcplus[mh2Nhist][Npt];



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

TH1F *mh1hist_Dca_Dsminus_rebin[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Lcminus_rebin[mh2Nhist][Npt];

TH1F *mh1hist_Dca_Dsplus_rebin[mh2Nhist][Npt];
TH1F *mh1hist_Dca_Lcplus_rebin[mh2Nhist][Npt];



TH1F *mh1Charm_dca_rebin[mh2Nhist][Npt];
TH1F *mh1Bottom_dca_rebin[mh2Nhist][Npt];


TH1F *mh1hist_Dca_D_rebin[mh2Nhist][Npt];
TH1F *mh1hist_Dca_B_rebin[mh2Nhist][Npt];


TH1F *mh1Charm_dca[mh2Nhist][Npt];
TH1F *mh1Bottom_dca[mh2Nhist][Npt];



TString mh2DcaHistName_D0[mh2Nhist]={"mh2D0rDcaVspt0","mh2D0rDcaVspt1","mh2D0rDcaVspt2"};
TString mh2DcaHistName_B0[mh2Nhist]={"mh2B0rDcaVspt0","mh2B0rDcaVspt1","mh2B0rDcaVspt2"};

TString mh2DcaHistName_Dplus[mh2Nhist]={"mh2DplusrDcaVspt0","mh2DplusrDcaVspt1","mh2DplusrDcaVspt2"};
TString mh2DcaHistName_Bplus[mh2Nhist]={"mh2BplusrDcaVspt0","mh2BplusrDcaVspt1","mh2BplusrDcaVspt2"};

TString mh2DcaHistName_Dsplus[mh2Nhist]={"mh2DsplusrDcaVspt0","mh2DsplusrDcaVspt1","mh2DsplusrDcaVspt2"};
TString mh2DcaHistName_Lcplus[mh2Nhist]={"mh2LcrDcaVspt0","mh2LcrDcaVspt1","mh2LcrDcaVspt2"};

TString mh2DcaHistName_D0bar[mh2Nhist]={"mh2D0barrDcaVspt0","mh2D0barrDcaVspt1","mh2D0barrDcaVspt2"};
TString mh2DcaHistName_B0bar[mh2Nhist]={"mh2B0barrDcaVspt0","mh2B0barrDcaVspt1","mh2B0barrDcaVspt2"};

TString mh2DcaHistName_Dminus[mh2Nhist]={"mh2DminusrDcaVspt0","mh2DminusrDcaVspt1","mh2DminusrDcaVspt2"};
TString mh2DcaHistName_Bminus[mh2Nhist]={"mh2BminusrDcaVspt0","mh2BminusrDcaVspt1","mh2BminusrDcaVspt2"};





// const int  nDcasDca = 54;
// Double_t const  DcaEdgeDca[nDcasDca+1] = {-0.1   , -0.09 ,     -0.08  ,   -0.07    , -0.06    , -0.05 , -0.0475 , -0.045 , -0.0425 , -0.04 , -0.0375 , -0.035 , -0.0325 , -0.03 , -0.0275 , -0.025 , -0.0225 , -0.02,-0.018,-0.016,-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014,0.016,0.018,0.02 ,0.0225 , 0.025 , 0.0275 , 0.03 , 0.0325 , 0.035 , 0.0375 , 0.04 , 0.0425 , 0.045 , 0.0475 , 0.05    , 0.06  ,  0.07    , 0.08    , 0.09   ,0.1};

TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
int Charm_Bottom_Compare(){


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
 

  // TFile * inFile_D0= new TFile("input/D0.root","READ");
  // TFile * inFile_D0bar= new TFile("input/D0bar.root","READ");
  
  // TFile * inFile_Dplus= new TFile("input/Dplus.root","READ");
  // TFile * inFile_Dminus= new TFile("input/Dminus.root","READ");


  //--------------

  TFile * inFile_D0= new TFile("../input_new_20171024/TypeID_Ana_421.root","READ");
  TFile * inFile_D0bar= new TFile("../input_new_20171024/TypeID_Ana_-421.root","READ");
  
  TFile * inFile_Dplus= new TFile("../input_new_20171024/TypeID_Ana_411.root","READ");
  TFile * inFile_Dminus= new TFile("../input_new_20171024/TypeID_Ana_-411.root","READ");

  
  //----------------

  TFile * inFile_Dsplus= new TFile("../input_new_20171024/TypeID_Ana_431.root","READ");
  TFile * inFile_Dsminus= new TFile("../input_new_20171024/TypeID_Ana_-431.root","READ");

  TFile * inFile_Lcplus= new TFile("../input_new_20171024/TypeID_Ana_4122.root","READ");
  TFile * inFile_Lcminus= new TFile("../input_new_20171024/TypeID_Ana_-4122.root","READ");
  
  
  
  // TFile * inFile_Bplus= new TFile("input/Bplus.root","READ");
  // TFile * inFile_Bminus= new TFile("input/Bminus.root","READ");
  
   
  // TFile * inFile_B0= new TFile("input/B0.root","READ");
  // TFile * inFile_B0bar= new TFile("input/B0bar.root","READ");




  //---------------

  TFile * inFile_Bplus= new TFile("../input_new_20171024/TypeID_Ana_521.root","READ");
  TFile * inFile_Bminus= new TFile("../input_new_20171022/TypeID_Ana_-521.root","READ");
  
   
  TFile * inFile_B0= new TFile("../input_new_20171024/TypeID_Ana_511.root","READ");
  TFile * inFile_B0bar= new TFile("../input_new_20171024/TypeID_Ana_-511.root","READ");
  
  
  //----------------

  //project to pT

  
  TFile *file_fastsim=new TFile("File_fastsim.root","RECREATE");

  for(Int_t ihist=0;ihist<mh2Nhist;ihist++)
    {
      mh2Hist_DcaVsPt_D0[ihist]=(TH2F *) inFile_D0->Get(mh2DcaHistName_D0[ihist]);
      mh2Hist_DcaVsPt_Dplus[ihist]=(TH2F *) inFile_Dplus->Get(mh2DcaHistName_Dplus[ihist]);
      mh2Hist_DcaVsPt_Bplus[ihist]=(TH2F *) inFile_Bplus->Get(mh2DcaHistName_Bplus[ihist]);
      mh2Hist_DcaVsPt_B0[ihist]=(TH2F *) inFile_B0->Get(mh2DcaHistName_B0[ihist]);


      mh2Hist_DcaVsPt_Dsplus[ihist]=(TH2F *) inFile_Dsplus->Get(mh2DcaHistName_Dsplus[ihist]);
      mh2Hist_DcaVsPt_Lcplus[ihist]=(TH2F *) inFile_Lcplus->Get(mh2DcaHistName_Lcplus[ihist]);
		  
      
      mh2Hist_DcaVsPt_D0bar[ihist]=(TH2F *) inFile_D0bar->Get(mh2DcaHistName_D0[ihist]);
      mh2Hist_DcaVsPt_D0bar[ihist]->SetName(mh2Hist_DcaVsPt_D0bar[ihist]->GetName()+TString("D0bar"));
      mh2Hist_DcaVsPt_B0bar[ihist]=(TH2F *) inFile_B0bar->Get(mh2DcaHistName_B0[ihist]);
      mh2Hist_DcaVsPt_B0bar[ihist]->SetName(mh2Hist_DcaVsPt_B0bar[ihist]->GetName()+TString("B0bar"));

      mh2Hist_DcaVsPt_Dminus[ihist]=(TH2F *) inFile_Dminus->Get(mh2DcaHistName_Dplus[ihist]);
      mh2Hist_DcaVsPt_Dminus[ihist]->SetName(mh2Hist_DcaVsPt_Dminus[ihist]->GetName()+TString("Dminus"));
      
      mh2Hist_DcaVsPt_Bminus[ihist]=(TH2F *) inFile_Bminus->Get(mh2DcaHistName_Bplus[ihist]);
      mh2Hist_DcaVsPt_Bminus[ihist]->SetName(mh2Hist_DcaVsPt_Bminus[ihist]->GetName()+TString("Bminus"));

      mh2Hist_DcaVsPt_Dsminus[ihist]=(TH2F *) inFile_Dsminus->Get(mh2DcaHistName_Dsplus[ihist]);
      mh2Hist_DcaVsPt_Dsminus[ihist]->SetName(mh2Hist_DcaVsPt_Dsminus[ihist]->GetName()+TString("Dsminus"));
      

      mh2Hist_DcaVsPt_Lcminus[ihist]=(TH2F *) inFile_Lcminus->Get(mh2DcaHistName_Lcplus[ihist]);
      mh2Hist_DcaVsPt_Lcminus[ihist]->SetName(mh2Hist_DcaVsPt_Lcminus[ihist]->GetName()+TString("Lcminus"));
      
      
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

      //      return 0;
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



	  sprintf(buf,"mh1rDca_hist%ipt%iDsminus",ihist,ipt);
      	  mh1hist_Dca_Dsminus[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_Dsminus[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);

	  sprintf(buf,"mh1rDca_hist%ipt%iDsplus",ihist,ipt);
      	  mh1hist_Dca_Dsplus[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_Dsplus[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);

	  sprintf(buf,"mh1rDca_hist%ipt%iLcminus",ihist,ipt);
	  mh1hist_Dca_Lcminus[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_Lcminus[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);

	  sprintf(buf,"mh1rDca_hist%ipt%iLcplus",ihist,ipt);
      	  mh1hist_Dca_Lcplus[ihist][ipt]= (TH1F *) mh2Hist_DcaVsPt_Lcplus[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);

	  
	  
	  

	}
    }


  const Int_t IHIST=1;
  // draw D D+

  

  // mh1hist_Dca_Dplus[IHIST][ipt]->Draw("sameC");
  // mh1hist_Dca_Dsplus[IHIST][ipt]->Draw("sameC");
  // mh1hist_Dca_Lcplus[IHIST][ipt]->Draw("sameC");

  //  mh1hist_Dca_D[IHIST][ipt]->Draw("sameC");



  TLegend *legend_D  = new TLegend(0.15,0.65,0.4,0.85);
  legend_D ->AddEntry(mh1hist_Dca_D0[1][0],"Dca_{XY}","l");
  legend_D ->AddEntry(mh1hist_Dca_D0[2][0],"Dca_{Z}","l");


  legend_D ->SetBorderSize(0);
  legend_D ->SetTextSize(0.05);
  legend_D ->SetFillStyle(0);
  legend_D ->SetTextFont(62);

  //D0 
  TCanvas *c5_D0=new TCanvas("c5_D0","",1200,800);
  c5_D0->Divide(4,2);

  TCanvas *c5_D0_ratio=new TCanvas("c5_D0_ratio","",1200,800);
  c5_D0_ratio->Divide(4,2);
  for(Int_t ipt=0;ipt<Npt;ipt++)
    {

      mh1hist_Dca_D0[IHIST][ipt]->SetTitle(mh1Title[ipt]);
      c5_D0->cd(ipt+1);
      gPad->SetLogy();
      mh1hist_Dca_D0[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_D0[IHIST+1][ipt]->Rebin(2);

      mh1hist_Dca_D0[IHIST+1][ipt]->SetLineColor(2);
      mh1hist_Dca_D0[IHIST+1][ipt]->SetMarkerColor(2);

      mh1hist_Dca_D0[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_D0[IHIST+1][ipt]->Rebin(2);

	  
      mh1hist_Dca_D0[IHIST][ipt]->Draw();
      mh1hist_Dca_D0[IHIST+1][ipt]->Draw("same");

      legend_D->Draw();
      TH1F *ratio= (TH1F *)mh1hist_Dca_D0[IHIST][ipt]->Clone("ratio");
      ratio->GetYaxis()->SetRangeUser(0,2);
      ratio->SetTitle(mh1Title[ipt]);
      ratio->GetYaxis()->SetTitle("DCA_{XY}/DCA_{Z}");
	  
      ratio->Divide(mh1hist_Dca_D0[IHIST+1][ipt]);

      c5_D0_ratio->cd(ipt+1);
      ratio->Draw();
    }

    
  c5_D0->SaveAs("Plots/D0.pdf");
  c5_D0_ratio->SaveAs("Plots/D0_ratio.pdf");

  // Dplus
  TCanvas *c5_Dplus=new TCanvas("c5_Dplus","",1200,800);
  c5_Dplus->Divide(4,2);

  TCanvas *c5_Dplus_ratio=new TCanvas("c5_Dplus_ratio","",1200,800);
  c5_Dplus_ratio->Divide(4,2);
  for(Int_t ipt=0;ipt<Npt;ipt++)
    {

      mh1hist_Dca_Dplus[IHIST][ipt]->SetTitle(mh1Title[ipt]);
      c5_Dplus->cd(ipt+1);
      gPad->SetLogy();
      mh1hist_Dca_Dplus[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_Dplus[IHIST+1][ipt]->Rebin(2);

      mh1hist_Dca_Dplus[IHIST+1][ipt]->SetLineColor(2);
      mh1hist_Dca_Dplus[IHIST+1][ipt]->SetMarkerColor(2);

      mh1hist_Dca_Dplus[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_Dplus[IHIST+1][ipt]->Rebin(2);

	  
      mh1hist_Dca_Dplus[IHIST][ipt]->Draw();
      mh1hist_Dca_Dplus[IHIST+1][ipt]->Draw("same");

      legend_D->Draw();
      TH1F *ratio= (TH1F *)mh1hist_Dca_Dplus[IHIST][ipt]->Clone("ratio");
      ratio->GetYaxis()->SetRangeUser(0,2);
      ratio->SetTitle(mh1Title[ipt]);
      ratio->GetYaxis()->SetTitle("DCA_{XY}/DCA_{Z}");
	  
      ratio->Divide(mh1hist_Dca_Dplus[IHIST+1][ipt]);

      c5_Dplus_ratio->cd(ipt+1);
      ratio->Draw();
    }

    
  c5_Dplus->SaveAs("Plots/Dplus.pdf");
  c5_Dplus_ratio->SaveAs("Plots/Dplus_ratio.pdf");


  //Ds
  TCanvas *c5_Lcplus=new TCanvas("c5_Lcplus","",1200,800);
  c5_Lcplus->Divide(4,2);

  TCanvas *c5_Lcplus_ratio=new TCanvas("c5_Lcplus_ratio","",1200,800);
  c5_Lcplus_ratio->Divide(4,2);
  for(Int_t ipt=0;ipt<Npt;ipt++)
    {

      mh1hist_Dca_Lcplus[IHIST][ipt]->SetTitle(mh1Title[ipt]);
      c5_Lcplus->cd(ipt+1);
      gPad->SetLogy();
      mh1hist_Dca_Lcplus[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_Lcplus[IHIST+1][ipt]->Rebin(2);

      mh1hist_Dca_Lcplus[IHIST+1][ipt]->SetLineColor(2);
      mh1hist_Dca_Lcplus[IHIST+1][ipt]->SetMarkerColor(2);

      mh1hist_Dca_Lcplus[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_Lcplus[IHIST+1][ipt]->Rebin(2);

	  
      mh1hist_Dca_Lcplus[IHIST][ipt]->Draw();
      mh1hist_Dca_Lcplus[IHIST+1][ipt]->Draw("same");

      legend_D->Draw();
      TH1F *ratio= (TH1F *)mh1hist_Dca_Lcplus[IHIST][ipt]->Clone("ratio");
      ratio->GetYaxis()->SetRangeUser(0,2);
      ratio->SetTitle(mh1Title[ipt]);
      ratio->GetYaxis()->SetTitle("DCA_{XY}/DCA_{Z}");
	  
      ratio->Divide(mh1hist_Dca_Lcplus[IHIST+1][ipt]);

      c5_Lcplus_ratio->cd(ipt+1);
      ratio->Draw();
    }

    
  c5_Lcplus->SaveAs("Plots/Lcplus.pdf");
  c5_Lcplus_ratio->SaveAs("Plots/Lcplus_ratio.pdf");

  
  TCanvas *c5_B0=new TCanvas("c5_B0","",1200,800);
  c5_B0->Divide(4,2);

  TCanvas *c5_B0_ratio=new TCanvas("c5_B0_ratio","",1200,800);
  c5_B0_ratio->Divide(4,2);
  for(Int_t ipt=0;ipt<Npt;ipt++)
    {

      mh1hist_Dca_B0[IHIST][ipt]->SetTitle(mh1Title[ipt]);
      c5_B0->cd(ipt+1);
      gPad->SetLogy();
      mh1hist_Dca_B0[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_B0[IHIST+1][ipt]->Rebin(2);

      mh1hist_Dca_B0[IHIST+1][ipt]->SetLineColor(2);
      mh1hist_Dca_B0[IHIST+1][ipt]->SetMarkerColor(2);

      mh1hist_Dca_B0[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_B0[IHIST+1][ipt]->Rebin(2);

	  
      mh1hist_Dca_B0[IHIST][ipt]->Draw();
      mh1hist_Dca_B0[IHIST+1][ipt]->Draw("same");

      legend_D->Draw();
      TH1F *ratio= (TH1F *)mh1hist_Dca_B0[IHIST][ipt]->Clone("ratio");
      ratio->GetYaxis()->SetRangeUser(0,2);
      ratio->SetTitle(mh1Title[ipt]);
      ratio->GetYaxis()->SetTitle("DCA_{XY}/DCA_{Z}");
	  
      ratio->Divide(mh1hist_Dca_B0[IHIST+1][ipt]);

      c5_B0_ratio->cd(ipt+1);
      ratio->Draw();
    }

    
  c5_B0->SaveAs("Plots/B0.pdf");
  c5_B0_ratio->SaveAs("Plots/B0_ratio.pdf");

  
    TCanvas *c5_Bplus=new TCanvas("c5_Bplus","",1200,800);
  c5_Bplus->Divide(4,2);

  TCanvas *c5_Bplus_ratio=new TCanvas("c5_Bplus_ratio","",1200,800);
  c5_Bplus_ratio->Divide(4,2);
  for(Int_t ipt=0;ipt<Npt;ipt++)
    {

      mh1hist_Dca_Bplus[IHIST][ipt]->SetTitle(mh1Title[ipt]);
      c5_Bplus->cd(ipt+1);
      gPad->SetLogy();
      mh1hist_Dca_Bplus[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_Bplus[IHIST+1][ipt]->Rebin(2);

      mh1hist_Dca_Bplus[IHIST+1][ipt]->SetLineColor(2);
      mh1hist_Dca_Bplus[IHIST+1][ipt]->SetMarkerColor(2);

      mh1hist_Dca_Bplus[IHIST][ipt]->Rebin(2);
      mh1hist_Dca_Bplus[IHIST+1][ipt]->Rebin(2);

	  
      mh1hist_Dca_Bplus[IHIST][ipt]->Draw();
      mh1hist_Dca_Bplus[IHIST+1][ipt]->Draw("same");

      legend_D->Draw();
      TH1F *ratio= (TH1F *)mh1hist_Dca_Bplus[IHIST][ipt]->Clone("ratio");
      ratio->GetYaxis()->SetRangeUser(0,2);
      ratio->SetTitle(mh1Title[ipt]);
      ratio->GetYaxis()->SetTitle("DCA_{XY}/DCA_{Z}");
	  
      ratio->Divide(mh1hist_Dca_Bplus[IHIST+1][ipt]);

      c5_Bplus_ratio->cd(ipt+1);
      ratio->Draw();
    }

    
  c5_Bplus->SaveAs("Plots/Bplus.pdf");
  c5_Bplus_ratio->SaveAs("Plots/Bplus_ratio.pdf");


  // return 0;
  
  TH2F *mh2D0_eta_Pt;
  TH2F *mh2Dplus_eta_Pt;
  TH2F *mh2Lc_eta_Pt;
  TH2F *mh2Bplus_eta_Pt;
  TH2F *mh2B0_eta_Pt;

  TH1F *mh1D0_eta_Pt[Npt];
  TH1F *mh1Dplus_eta_Pt[Npt];
  TH1F *mh1Lc_eta_Pt[Npt];
  TH1F *mh1Bplus_eta_Pt[Npt];
  TH1F *mh1B0_eta_Pt[Npt];


  mh2D0_eta_Pt=(TH2F *) inFile_D0->Get("mh2D0_pT_Eta");
  mh2Lc_eta_Pt=(TH2F *) inFile_Lcplus->Get("mh2Lcplus_pT_Eta");
  mh2Bplus_eta_Pt=(TH2F *) inFile_Bplus->Get("mh2Bplus_pT_Eta");



  
  TCanvas *c5_eta=new TCanvas("c5_eta","",1200,800);
  c5_eta->Divide(4,2);
  
  
  for(Int_t ipt=0;ipt<Npt;ipt++)
    {
      sprintf(buf,"_ipt%i",ipt);
      mh1D0_eta_Pt[ipt]= (TH1F *) mh2D0_eta_Pt->ProjectionY(buf+TString("mh1D0_eta_Pt"),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      mh1Lc_eta_Pt[ipt]= (TH1F *) mh2Lc_eta_Pt->ProjectionY(buf+TString("mh1Lc_eta_Pt"),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
      mh1Bplus_eta_Pt[ipt]= (TH1F *) mh2Bplus_eta_Pt->ProjectionY(buf+TString("mh1Bplus_eta_Pt"),Xbin_ptlow[ipt],Xbin_pthigh[ipt]);

      
      mh1D0_eta_Pt[ipt]->SetLineColor(1);
      c5_eta->cd(ipt+1);


      mh1D0_eta_Pt[ipt]->Scale(mh1Bplus_eta_Pt[ipt]->Integral()/mh1D0_eta_Pt[ipt]->Integral());
      mh1Lc_eta_Pt[ipt]->Scale(mh1Bplus_eta_Pt[ipt]->Integral()/mh1Lc_eta_Pt[ipt]->Integral());


      mh1D0_eta_Pt[ipt]->Rebin(2);
      mh1Lc_eta_Pt[ipt]->Rebin(2);
      mh1Bplus_eta_Pt[ipt]->Rebin(2);

      
      mh1D0_eta_Pt[ipt]->SetLineColor(1);
      mh1Lc_eta_Pt[ipt]->SetLineColor(2);
      mh1Bplus_eta_Pt[ipt]->SetLineColor(4);

      mh1D0_eta_Pt[ipt]->GetXaxis()->SetRangeUser(-0.8,0.8);

      mh1D0_eta_Pt[ipt]->GetXaxis()->SetTitle("Eta");
      mh1D0_eta_Pt[ipt]->SetTitle(mh1Title[ipt]);
      mh1D0_eta_Pt[ipt]->Draw();
      mh1Lc_eta_Pt[ipt]->Draw("same");
      mh1Bplus_eta_Pt[ipt]->Draw("same");
  
      //      cout<< mh1Bplus_eta_Pt[ipt]->GetName()<<endl;
    }

  TLegend *legend_eta  = new TLegend(0.35,0.35,0.55,0.55);
  legend_eta ->AddEntry(mh1D0_eta_Pt[0],"D0 #rightarrow e","l");
  legend_eta ->AddEntry(mh1Lc_eta_Pt[0],"#Lambdac #rightarrow e","l");
  legend_eta ->AddEntry(mh1Bplus_eta_Pt[0],"B+ #rightarrow e","l");

  legend_eta ->SetBorderSize(0);
  legend_eta ->SetTextSize(0.04);
  legend_eta ->SetFillStyle(0);
  legend_eta ->SetTextFont(62);


  c5_eta->cd(1);
  legend_eta->Draw();
  c5_eta->SaveAs("Plots/Eta.pdf");
  
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
