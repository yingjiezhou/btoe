/*--------------------Yjzhou------------------------------------

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
TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
void DrawFrameDCA(TCanvas *c5_D,TLegend *legend_D,TH1F *h1hist_Dca_D0_rebin, TH1F *h1hist_Dca_D_rebin,Int_t i, Int_t ihist, Int_t ipt);

bool Lc_Flag=true; // you can remove the Lc contribution from switch it into false
const int mh2Nhist=3;
const int Np=3;

const char * Ymh2Titlename[mh2Nhist]={" 3Ddca (cm)"," dcaXY (cm)"," dcaZ (cm) "};
const char * Ymh1Titlename[mh2Nhist]={" dca (cm)"," dcaXY (cm)"," dcaZ (cm) "};

const char * dname[Np] = {"D0",  "Dplus","D0bar",};
const char * mh2DcaHistName_D0[Np][mh2Nhist]={Form("mh2%srDcaVspt0",dname[0]),Form("mh2%srDcaVspt1",dname[0]),Form("mh2%srDcaVspt2",dname[0]),
  Form("mh2%srDcaVspt0",dname[1]),Form("mh2%srDcaVspt1",dname[1]),Form("mh2%srDcaVspt1",dname[1]),
  Form("mh2%srDcaVspt0",dname[2]),Form("mh2%srDcaVspt1",dname[2]),Form("mh2%srDcaVspt2",dname[2])
};

const char * ddpg[Np] = {"421", "411","-421",};
const char * dLegend[Np] = {"D^{0}->e", "D^{+}->e","-421",};

char buf[1024];

TH2F *mh2Hist_DcaVsPt_D0[mh2Nhist];

TH1F *mh1hist_Dca_D0[mh2Nhist][Np][Npt];
TH1F *mh1hist_Dca_D0_rebin[mh2Nhist][Np][Npt];
TH1F *temh1hist_Dca_D0_rebin[mh2Nhist][Np][Npt];


TH1F *mh1hist_Dca_D[mh2Nhist][Np][Npt]; // total
TH1F *mh1hist_Dca_D_rebin[mh2Nhist][Np][Npt];

//=============================================================================

int Charm_Bottom_Decay_electrons_EvtGen(){

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  
  gStyle->SetOptStat(00000);
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleOffset(1.3,"X");
  gStyle->SetTitleOffset(1,"Y");
  gStyle->SetPadTopMargin(0.13);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.13);
 //=============================================================================
  
  TFile * inFile_D0;
  TLegend *legend_D;
  TCanvas *c5_D; // for DCA each components
  
  TFile *file_fastsim=new TFile("File_fastsim.root","RECREATE");
  for(Int_t ihist=0;ihist<1;ihist++){ // DCA components
    cout<< Form(" %s ",Ymh2Titlename[ihist] )<<endl;

    for(Int_t i=0; i<2; i++){
      inFile_D0= new TFile(Form("input/TypeID_Ana_%s.root", ddpg[i]),"READ");
      mh2Hist_DcaVsPt_D0[ihist]= (TH2F *) inFile_D0->Get(mh2DcaHistName_D0[i][ihist]);
      cout<<" particle "<<i<<endl;
      
      for(Int_t ipt=0;ipt<Npt;ipt++){ // pt bin
        cout<<" pt range: "<<ipt<<endl;
        sprintf(buf,"mh1rDca_hist%ipt%i_%ipart",ihist,ipt, i);
        mh1hist_Dca_D0[ihist][i][ipt]= (TH1F *) mh2Hist_DcaVsPt_D0[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]= (TH1F *) mh1hist_Dca_D0[ihist][i][ipt]->Rebin(nDcasDca,mh1hist_Dca_D0[ihist][i][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
        //=============================================================================
        
        sprintf(buf,"mh1rDca_hist%ipt%i_D",ihist,ipt);
        if(i==0){
          mh1hist_Dca_D_rebin[ihist][0][ipt]=(TH1F *) mh1hist_Dca_D0_rebin[ihist][i][ipt]->Clone(buf);
        }else{
          mh1hist_Dca_D_rebin[ihist][i][ipt]=(TH1F *) mh1hist_Dca_D0_rebin[ihist][i][ipt]->Clone(buf);
          mh1hist_Dca_D_rebin[ihist][0][ipt]->Add(mh1hist_Dca_D_rebin[ihist][i][ipt]); // add all HF DCA dist
        }
        mh1hist_Dca_D_rebin[ihist][0][ipt]->SetLineColor(4);
        mh1hist_Dca_D_rebin[ihist][0][ipt]->SetTitle(mh1Title[ipt]);
        file_fastsim->cd();
        mh1hist_Dca_D_rebin[ihist][0][ipt]->Write(); // to save all HF
        //=============================================================================

        mh1hist_Dca_D0_rebin[ihist][i][ipt]->SetDirectory(0);
        //mh1hist_Dca_D0[ihist][0][ipt]->Write(); // save all DCA
        //DrawFrameDCA(c5,legend,mh1hist_Dca_D0_rebin[ihist][ipt],mh1hist_Dca_D_rebin[ihist][ipt],i, ihist, ipt);// To draw same
        //sprintf(buf,"mh1rDca_hist%ipt%i_D0copy",ihist,ipt);
        //temh1hist_Dca_D0_rebin[ihist][i][ipt]=(TH1F *) mh1hist_Dca_D0_rebin[ihist][i][ipt]->Clone(buf);
      }// end for pt loop
    } // end for pariticle loop
    inFile_D0->Close();

    //=============================================================================
    legend_D = new TLegend(0.15,0.65,0.4,0.85);
    c5_D=new TCanvas(Form("%s",Ymh2Titlename[ihist] ),"",1200,800);
    c5_D->Divide(4,2);
    legend_D ->AddEntry(mh1hist_Dca_D0_rebin[ihist][0][0],Form("%s", dLegend[0]), "l");
    legend_D ->AddEntry(mh1hist_Dca_D0_rebin[ihist][1][0],Form("%s", dLegend[1]), "l");
    legend_D ->AddEntry(mh1hist_Dca_D_rebin[ihist][0][0],"Charm->e","l");
    legend_D ->SetBorderSize(0);
    legend_D ->SetTextSize(0.05);
    legend_D ->SetFillStyle(0);
    legend_D ->SetTextFont(62);
    cout<< Form("Draw into  %s Canvas",Ymh2Titlename[ihist] )<<endl;
    //=============================================================================
    for(Int_t ipt=0; ipt<Npt; ipt++){
      c5_D->cd(ipt+1);
      gPad->SetLogy();
      cout<<" pt range: "<<ipt<<endl;
      mh1hist_Dca_D_rebin[ihist][0][ipt]->Draw(); // total
      legend_D->Draw("same");
    //=============================================================================
      for(Int_t i=0;i<2;i++){ // pt bin
        //cout<<" particle: "<<i<<endl;
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->GetYaxis()->SetTitle("");
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->GetXaxis()->SetLabelSize(0.04);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->GetYaxis()->SetLabelSize(0.04);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->SetTitle(mh1Title[ipt]);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->SetLineColor(i+1);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->Scale(1.,"width");
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->Sumw2(0);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->Draw("same");// 之前就是因为这里循环的时候还是draw，而不是draw same 而导致一直只能画一个
      }
    }
  //=============================================================================
    
  }// end for DCA components loop

  return 0;
}
