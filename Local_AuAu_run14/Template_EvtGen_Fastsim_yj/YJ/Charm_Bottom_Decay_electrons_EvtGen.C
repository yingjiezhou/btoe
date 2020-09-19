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
bool Lc_Flag=true; // you can remove the Lc contribution from switch it into false
const int mh2Nhist=3; // number of DCA components
const int Np=3; // number of particle

const char * Ymh2Titlename[mh2Nhist]={" 3Ddca (cm)"," dcaXY (cm)"," dcaZ (cm) "};
const char * Ymh1Titlename[mh2Nhist]={"3Ddca","dcaXY","dcaZ"};

const char * ddpg[Np] = {"421", "411","-421",};
const char * dLegend[Np] = {"D^{0}->e", "D^{+}->e","#Lambda_{c}->e",};
const char * dname[Np] = {"D0", "Dplus","D0bar"};
const char * dnameL[Np] = {"D^{0}", "D^{+}","#Lambda_{c}"};

const char * mh2DcaHistName_D0[Np][mh2Nhist]={Form("mh2%srDcaVspt0",dname[0]),Form("mh2%srDcaVspt1",dname[0]),Form("mh2%srDcaVspt2",dname[0]),
  Form("mh2%srDcaVspt0",dname[1]),Form("mh2%srDcaVspt1",dname[1]),Form("mh2%srDcaVspt1",dname[1]),
  Form("mh2%srDcaVspt0",dname[2]),Form("mh2%srDcaVspt1",dname[2]),Form("mh2%srDcaVspt2",dname[2])
};

char buf[1024];

TH2F *mh2Hist_DcaVsPt_D0[mh2Nhist];

TH1F *mh1hist_Dca_D0[mh2Nhist][Np][Npt];
TH1F *mh1hist_Dca_D0_rebin[mh2Nhist][Np][Npt];

TH1F *D0_e_pT[Np];

TH1F *mh1hist_Dca_D[mh2Nhist][Np][Npt]; // all particle DCA
TH1F *mh1hist_Dca_D_rebin[mh2Nhist][Np][Npt];

void DrawFrameDCA(TH1F *[mh2Nhist][Np][Npt], TH1F *[mh2Nhist][Np][Npt]);
void DrawFramePt(TH1F *[Np]);
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
  TFile *file_fastsim=new TFile("File_fastsim.root","RECREATE");
  for(Int_t ihist=0;ihist<3;ihist++){ // DCA components loop ihist
    cout<< Form(" %s ",Ymh2Titlename[ihist] )<<endl;
    for(Int_t i=0; i<2; i++){ // particle loop i
      inFile_D0= new TFile(Form("input/TypeID_Ana_%s.root", ddpg[i]),"READ");
      mh2Hist_DcaVsPt_D0[ihist]= (TH2F *) inFile_D0->Get(mh2DcaHistName_D0[i][ihist]);
      cout<<" particle "<<i<<endl;
      //=============================================================================
      // get pt hist
      if(ihist == 0)D0_e_pT[i]= (TH1F*) mh2Hist_DcaVsPt_D0[ihist]->ProjectionX(Form("%s_e_pT",dname[i]));
      
      //=============================================================================

      for(Int_t ipt=0;ipt<Npt;ipt++){ // pt bin loop ipt
        //cout<<" pt range: "<<ipt<<endl;
        sprintf(buf,"mh1rDca_hist%d_pt%d_par%d",ihist,ipt, i);
        mh1hist_Dca_D0[ihist][i][ipt]= (TH1F *) mh2Hist_DcaVsPt_D0[ihist]->ProjectionY(buf,Xbin_ptlow[ipt],Xbin_pthigh[ipt]);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]= (TH1F *) mh1hist_Dca_D0[ihist][i][ipt]->Rebin(nDcasDca,mh1hist_Dca_D0[ihist][i][ipt]->GetName()+TString("_rebin"),DcaEdgeDca);
        // to combine all charm/beauty hist
        sprintf(buf,"mh1rDca_hist%d_pt%d_par%d",ihist,ipt,i);
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
      }// end for pt loop
    } // end for pariticle loop
  }// end for DCA components loop
  //=============================================================================

  DrawFrameDCA(mh1hist_Dca_D0, mh1hist_Dca_D_rebin);
  DrawFramePt(D0_e_pT);
  return 0;
}

void DrawFrameDCA(TH1F *[mh2Nhist][Np][Npt], TH1F *[mh2Nhist][Np][Npt]){
  TLegend *legend_D;
  TCanvas *c5_D; // for DCA each components
  for(Int_t ihist=0;ihist<3;ihist++){
  //cout<< Form("Starting to draw %s Canvas",Ymh2Titlename[ihist] )<<endl;
    legend_D = new TLegend(0.15,0.65,0.4,0.85);
    c5_D=new TCanvas(Form("%s",Ymh2Titlename[ihist] ),"",1200,800);
    c5_D->Divide(4,2);
    legend_D ->AddEntry(mh1hist_Dca_D0_rebin[ihist][0][0],Form("%s", dLegend[0]), "l"); //particle 1
    legend_D ->AddEntry(mh1hist_Dca_D0_rebin[ihist][1][0],Form("%s", dLegend[1]), "l");//particle 2
    legend_D ->AddEntry(mh1hist_Dca_D_rebin[ihist][0][0],"Charm->e","l");
    legend_D ->SetBorderSize(0);
    legend_D ->SetTextSize(0.05);
    legend_D ->SetFillStyle(0);
    legend_D ->SetTextFont(62);
    //=============================================================================
    for(Int_t ipt=0; ipt<Npt; ipt++){
      c5_D->cd(ipt+1);
      gPad->SetLogy();
      //cout<<" pt range: "<<ipt<<endl;
      //=============================================================================
      // hist draw frame
      mh1hist_Dca_D_rebin[ihist][0][ipt]->GetXaxis()->SetTitle(Ymh2Titlename[ihist]);
      mh1hist_Dca_D_rebin[ihist][0][ipt]->GetYaxis()->SetTitle("Counts");
      mh1hist_Dca_D_rebin[ihist][0][ipt]->GetXaxis()->CenterTitle(true);
      mh1hist_Dca_D_rebin[ihist][0][ipt]->GetYaxis()->CenterTitle(true);
      mh1hist_Dca_D_rebin[ihist][0][ipt]->GetXaxis()->SetLabelSize(0.04);
      mh1hist_Dca_D_rebin[ihist][0][ipt]->GetYaxis()->SetLabelSize(0.04);
      mh1hist_Dca_D_rebin[ihist][0][ipt]->SetTitle(mh1Title[ipt]);
      mh1hist_Dca_D_rebin[ihist][0][ipt]->SetLineColor(4);
      mh1hist_Dca_D_rebin[ihist][0][ipt]->GetXaxis()->SetRangeUser(-0.1,0.1);
      mh1hist_Dca_D_rebin[ihist][0][ipt]->Scale(1.,"width");
      mh1hist_Dca_D_rebin[ihist][0][ipt]->Sumw2(0);
      mh1hist_Dca_D_rebin[ihist][0][ipt]->Draw("C"); // total
      legend_D->Draw();
      //=============================================================================

      for(Int_t i=0;i<2;i++){ // pt bin
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->SetLineColor(i+1);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->Scale(1.,"width");
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->Sumw2(0);
        mh1hist_Dca_D0_rebin[ihist][i][ipt]->Draw("sameC");// 之前就是因为这里循环的时候还是draw，而不是draw same 而导致一直只能画一个
      }
    }
  //=============================================================================

  c5_D->SaveAs(Form("Plots/D_%s.pdf", Ymh1Titlename[ihist]));
  }
}

void DrawFramePt(TH1F* [Np]){
  
  TCanvas *c_D_pt=new TCanvas("c_D_pt","",800,600);
  TLegend *legend_D_pt  = new TLegend(0.65,0.65,0.9,0.8);
  gPad->SetLogy();
  TH2F *hh_D_pt=new TH2F("hh_D_pt","",100,0.15,10,100,0.5e-6,1e7);
  hh_D_pt->SetTitle("");
  hh_D_pt->GetXaxis()->SetTitle("p^{e}_{T} GeV/c");
  hh_D_pt->GetYaxis()->SetTitle("Counts");
  hh_D_pt->Draw();
  
  for(Int_t i=0; i<2; ++i){
    D0_e_pT[i]->SetLineColor(i+1);
    D0_e_pT[i]->Draw("same");
    legend_D_pt ->AddEntry(D0_e_pT[i],Form("%s Decay Electrons",dnameL[i]),"l");
    legend_D_pt ->SetBorderSize(0);
  }
  legend_D_pt->Draw();
  c_D_pt->SaveAs("Plots/c_D_pt.pdf");
}
