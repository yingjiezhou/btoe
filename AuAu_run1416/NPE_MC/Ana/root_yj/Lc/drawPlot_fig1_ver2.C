#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<stdexcept>
#include<cmath>
#include<ctime>

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TPad.h"
#include "TLine.h"
#include "TSystem.h"
#include "TStopwatch.h"

const double PI = std::acos(-1.0);

void setpad(TPad *pad, float left, float right, float top, float bottom) {
   pad->SetFillColor(0);
   pad->SetBorderMode(0);
   pad->SetBorderSize(0);
   pad->SetFrameFillColor(0);
   pad->SetFrameBorderMode(0);
   pad->SetFrameBorderSize(0);
   pad->SetLeftMargin(left);
   pad->SetRightMargin(right);
   pad->SetTopMargin(top);
   pad->SetBottomMargin(bottom);
}

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex) {
   TLatex *latex = new TLatex(x, y, text);
   latex->SetNDC();
   latex->SetTextFont(textFont);
   latex->SetTextSize(textSize);
   latex->SetTextColor(colorIndex);
   latex->Draw("same");
   return latex;
}

int drawPlot_fig1_ver2() {

   TStopwatch*   stopWatch = new TStopwatch();
   stopWatch->Start();

   std::string localPath = "/gpfs01/star/pwg/rksooraj/codeforgpc_lc/Results/";

   TFile* fIn1 = new TFile((localPath + "Out_invmass_2014.root").c_str());
   TFile* fIn2 = new TFile((localPath + "Out_invmass_2016.root").c_str());

   char name[500], name1[500];

   TFile* fOut = new TFile("Out_drawPlot_fig1.root","recreate");

   TH1F* hunlike;
   TH1F* hunlike_fit;
   TH1F* hlike;
   TH1F* hsig_likesub;
   TH1F* hsig_fitsub;
   TH1F* hsig_fitlikesub;

   TF1*  fun1; 
   TF1*  fun1Like; 
   TF1*  fun1Bg; 
   TF1*  fun1Sg; 

   TH1F* hunlike_cent;
   TH1F* hunlike_cent_fit;
   TH1F* hlike_cent;
   TH1F* hsig_likesub_cent;
   TH1F* hsig_fitsub_cent;
   TH1F* hsig_fitlikesub_cent;

   TF1*  fun1_cent;
   TF1*  fun1Like_cent;
   TF1*  fun1Bg_cent;
   TF1*  fun1Sg_cent;

   hunlike = (TH1F*)((TH1F*)fIn1->Get("hunlike_1080"))->Clone("h_unlike"); hunlike->Add((TH1F*)fIn2->Get("hunlike_1080"));
   hlike   = (TH1F*)((TH1F*)fIn1->Get("hlike_1080"))->Clone("h_like");     hlike->Add((TH1F*)fIn2->Get("hlike_1080"));
   hlike->Scale(1.0/3);
   
   hunlike_cent = (TH1F*)((TH1F*)fIn1->Get("hunlike_020"))->Clone("h_unlike_cent"); hunlike_cent->Add((TH1F*)fIn2->Get("hunlike_020"));
   hlike_cent   = (TH1F*)((TH1F*)fIn1->Get("hlike_020"))->Clone("h_like_cent");     hlike_cent->Add((TH1F*)fIn2->Get("hlike_020"));
   hlike_cent->Scale(1.0/3);

   hunlike_fit      = (TH1F*)hunlike->Clone("unlike_fit"); 
   hunlike_cent_fit = (TH1F*)hunlike_cent->Clone("unlike_cent_fit");

   hunlike->Reset(); hunlike_cent->Reset();
   for (int ib=0;ib<hunlike_fit->GetNbinsX();ib++) {
      hunlike->SetBinContent(ib+1,hunlike_fit->GetBinContent(ib+1));
      hunlike->SetBinError  (ib+1,hunlike_fit->GetBinError  (ib+1));
   } 
   for (int ib=0;ib<hunlike_cent_fit->GetNbinsX();ib++) {
      hunlike_cent->SetBinContent(ib+1,hunlike_cent_fit->GetBinContent(ib+1));
      hunlike_cent->SetBinError  (ib+1,hunlike_cent_fit->GetBinError  (ib+1));
   } 

   hsig_likesub      = (TH1F*)hunlike->Clone("hsig_likesub"); hsig_likesub->Add(hlike,-1);
   hsig_likesub_cent = (TH1F*)hunlike_cent->Clone("hsig_likesub_cent"); hsig_likesub_cent->Add(hlike_cent,-1);

   float yx1 = hunlike->GetBinContent(hunlike->FindBin(2.08));
   float yx2 = hunlike->GetBinContent(hunlike->FindBin(2.52));
   float slope = (yx2-yx1)/(2.52-2.08);
   float y0 = (yx1 + yx2)/2.0;
   float sig = hunlike->GetBinContent(hunlike->FindBin(2.286)) - ((yx2+yx1)/2.0);

   TH1F* hlike_fit = (TH1F*)hlike->Clone("hlike_fit");
   fun1Like = new TF1("fun1Like","pol2",2.08,2.52);
   fun1Like->SetParameters(y0,slope,0.01);
   fun1Like->SetLineStyle(4);
   fun1Like->SetLineWidth(1);
   hlike_fit->Fit(fun1Like,"QR");

   fun1 = new TF1("fun1", "pol2+gaus(3)", 2.08, 2.52);
   fun1->SetLineWidth(1);
   fun1->SetParameters(y0,slope,0.01,sig,2.286,0.01);
   fun1->FixParameter(4,2.286);
   fun1->FixParameter(2,fun1Like->GetParameter(2));
   fun1->SetParLimits(5,0.05,0.02);
   TFitResultPtr r = hunlike_fit->Fit(fun1,"QR");

   sprintf(name,"fun1Sg"); fun1Sg = new TF1(name,"gaus",2.08,2.52);
   sprintf(name,"fun1Bg"); fun1Bg = new TF1(name,"pol2",2.08,2.52); 
   fun1Sg->SetParameters(fun1->GetParameter(3),fun1->GetParameter(4),fun1->GetParameter(5));
   fun1Bg->SetParameters(fun1->GetParameter(0),fun1->GetParameter(1),fun1->GetParameter(2));

   hsig_fitsub = (TH1F*)hunlike->Clone("hsig_fitsub"); hsig_fitsub->Add(fun1Bg,-1);
   hsig_fitlikesub = (TH1F*)hunlike->Clone("hsig_fitlikesub"); hsig_fitlikesub->Add(fun1Like,-1);

   int bL = hunlike->GetXaxis()->FindBin(fun1Sg->GetParameter(1)-3*fun1Sg->GetParameter(2) + 1e-4);
   int bU = hunlike->GetXaxis()->FindBin(fun1Sg->GetParameter(1)+3*fun1Sg->GetParameter(2) - 1e-4);

   double yld1, yld1_err; yld1 = hsig_fitsub->IntegralAndError(bL,bU,yld1_err);
   double yld2, yld2_bg; 
   yld2    = fun1Sg->Integral(hunlike->GetBinLowEdge(bL),hunlike->GetBinLowEdge(bU+1))/hunlike->GetBinWidth(1);    
   yld2_bg = fun1->Integral(hunlike->GetBinLowEdge(bL),hunlike->GetBinLowEdge(bU+1))/hunlike->GetBinWidth(1);    
   double yld3, yld3_err; yld3 = hsig_fitlikesub->IntegralAndError(bL,bU,yld3_err);
   float sig1 = yld1/yld1_err; 
   float sig2 = yld2/sqrt(yld2_bg); 
   float sig3 = yld3/yld3_err; 

   std::cout << "Counts = " << yld1 << " +/- " << yld1_err << ": sig = " << sig1 << ": sig_fit = " << sig2 << ": sig_fitlike = " << sig3 << std::endl;

   float yx1_cent = hunlike_cent->GetBinContent(hunlike_cent->FindBin(2.08));
   float yx2_cent = hunlike_cent->GetBinContent(hunlike_cent->FindBin(2.5));
   float slope_cent = (yx2_cent-yx1_cent)/(2.52-2.08);
   float y0_cent = (yx1_cent + yx2_cent)/2.0;
   float sig_cent = hunlike_cent->GetBinContent(hunlike_cent->FindBin(2.286)) - ((yx2_cent+yx1_cent)/2.0);

   TH1F* hlike_fit_cent = (TH1F*)hlike_cent->Clone("hlike_fit_cent");
   fun1Like_cent = new TF1("fun1Like_cent","pol2",2.08,2.52);
   fun1Like_cent->SetParameters(y0_cent,slope_cent,0.01);
   fun1Like_cent->SetLineStyle(4);
   fun1Like_cent->SetLineWidth(1);
   hlike_fit_cent->Fit(fun1Like_cent,"QR");

   fun1_cent = new TF1("fun1_cent", "pol2+gaus(3)", 2.08, 2.52);
   fun1_cent->SetLineWidth(1);
   fun1_cent->SetParameters(y0_cent,slope_cent,0.01,sig_cent,2.286,0.01);
   fun1_cent->FixParameter(4,2.286);
   fun1_cent->FixParameter(2,fun1Like_cent->GetParameter(2));
   fun1_cent->SetParLimits(5,0.05,0.02);
   TFitResultPtr r_cent = hunlike_cent_fit->Fit(fun1_cent,"QR");

   sprintf(name,"fun1Sg_cent"); fun1Sg_cent = new TF1(name,"gaus",2.08,2.52);
   sprintf(name,"fun1Bg_cent"); fun1Bg_cent = new TF1(name,"pol2",2.08,2.52);
   fun1Sg_cent->SetParameters(fun1_cent->GetParameter(3),fun1_cent->GetParameter(4),fun1_cent->GetParameter(5));
   fun1Bg_cent->SetParameters(fun1_cent->GetParameter(0),fun1_cent->GetParameter(1),fun1_cent->GetParameter(2));

   hsig_fitsub_cent = (TH1F*)hunlike_cent->Clone("hsig_fitsub_cent"); hsig_fitsub_cent->Add(fun1Bg_cent,-1);

   hsig_fitlikesub_cent = (TH1F*)hunlike_cent->Clone("hsig_fitlikesub_cent"); hsig_fitlikesub_cent->Add(fun1Like_cent,-1);

   int bL_cent = hunlike_cent->GetXaxis()->FindBin(fun1Sg_cent->GetParameter(1)-3*fun1Sg_cent->GetParameter(2) + 1e-4);
   int bU_cent = hunlike_cent->GetXaxis()->FindBin(fun1Sg_cent->GetParameter(1)+3*fun1Sg_cent->GetParameter(2) - 1e-4);
   std::cout << "low = " << fun1Sg_cent->GetParameter(1)-3*fun1Sg_cent->GetParameter(2) + 1e-4 << ": up = " << fun1Sg_cent->GetParameter(1)+3*fun1Sg_cent->GetParameter(2) - 1e-4 << std::endl;

   double yld1_cent, yld1_err_cent; yld1_cent = hsig_fitsub_cent->IntegralAndError(bL_cent,bU_cent-1,yld1_err_cent);
   double yld2_cent, yld2_bg_cent;
   yld2_cent    = fun1Sg_cent->Integral(hsig_likesub_cent->GetBinLowEdge(bL),hsig_likesub_cent->GetBinLowEdge(bU+1))/hunlike_cent->GetBinWidth(1);
   yld2_bg_cent = fun1_cent->Integral(hsig_likesub_cent->GetBinLowEdge(bL),hsig_likesub_cent->GetBinLowEdge(bU+1))/hunlike->GetBinWidth(1);
   double yld3_cent, yld3_err_cent; yld3_cent = hsig_fitlikesub_cent->IntegralAndError(bL_cent,bU_cent,yld3_err_cent);
   float sig1_cent = yld1_cent/yld1_err_cent;
   float sig2_cent = yld2_cent/sqrt(yld2_bg_cent);
   float sig3_cent = yld3_cent/yld3_err_cent;

   fOut->cd(0); fOut->Write(0);

   int   sty[]  = {20, 20, 20 , 28      ,23 ,30, 24, 29};
   float siz[]  = {0.8,0.8,0.9, 1.0     ,1.2,1.2,1.0,1.2,1.2};
   int   col[]  = {kRed-2 , kBlue-9 , kBlack,   kGreen+2,7  ,6 , 9 , 8 , 11};
   int   col2[] = {kGray+1 , kBlue-9 , kBlack, kGreen+2,7  ,6 , 9 , 8 , 11};

   TLegend* l1;
   l1 = new TLegend(0.22, 0.62, 0.42, 0.82);
   l1->SetFillStyle(0);
   l1->SetBorderSize(0);
   l1->SetTextFont(43);
   l1->SetTextSize(21);

   TLatex text;
   text.SetNDC(1);
   text.SetTextFont(43);
   text.SetTextSize(22);

   {
      char buf[1000];
      TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 650, 1100);
      gStyle->SetOptFit(0);
      gStyle->SetOptStat(0);
      gStyle->SetEndErrorSize(2);

      TPad* pad1  = new TPad("padB1","padB1",0.03,0.0 ,1.0 ,0.53);
      TPad* pad2  = new TPad("padB2","padB2",0.03,0.53,1.0 ,1.0);

      c1->cd(0); pad1->Draw();
      c1->cd(0); pad2->Draw();

      pad1->cd();
      pad1->SetLogy(0);
      setpad(pad1, 0.14, 0.03, 0.005, 0.16);
      pad1->SetTickx(0);
      pad1->SetTicky(0);
      
      fun1->SetNpx(1000);
      fun1Bg->SetNpx(1000);

      fun1Bg->SetLineStyle(2);
      fun1Bg->SetLineColor(1);
      fun1Bg->SetLineWidth(1);

      hunlike->GetXaxis()->SetRangeUser(2.08,2.52);
      hunlike->GetYaxis()->SetRangeUser(-2,175);
      hunlike->SetMarkerStyle(20);
      hunlike->SetMarkerSize(1);
      hunlike->SetLineColor(2);
      hunlike->SetLineWidth(2.);
      hunlike->SetMarkerColor(2);
      hunlike->Draw();
      hunlike_fit->Draw("same");
      hunlike->Draw("same");

      sprintf(buf, "Counts/(%d MeV/c^{2})", 10);
      hunlike->GetYaxis()->SetTitle(buf);
      hunlike->GetXaxis()->SetLabelOffset(0.01);
      hunlike->GetYaxis()->SetLabelOffset(0.01);
      hunlike->GetXaxis()->SetTitle("M_{pK#pi} (GeV/c^{2})");
      hunlike->GetYaxis()->SetNdivisions(205);
      hunlike->GetXaxis()->SetNdivisions(205);
      hunlike->GetXaxis()->SetTitleSize(0.06);
      hunlike->GetYaxis()->SetTitleSize(0.06);
      hunlike->GetXaxis()->SetLabelSize(0.06);
      hunlike->GetYaxis()->SetLabelSize(0.06);
      cout << "Axis Label FONT = "<< hunlike->GetXaxis()->GetLabelFont() <<endl;;
      cout << "Axis Label  FONT = "<< hunlike->GetYaxis()->GetLabelFont() <<endl;;
      hunlike->GetXaxis()->SetTitleOffset(1.1);
      hunlike->GetYaxis()->SetTitleOffset(1.1);
      hunlike->GetXaxis()->SetTitleFont(42);
      hunlike->GetYaxis()->SetTitleFont(42);
      hunlike->GetXaxis()->SetLabelFont(42);
      hunlike->GetYaxis()->SetLabelFont(42);
      hunlike->GetXaxis()->CenterTitle();
      hunlike->GetYaxis()->CenterTitle();

      hlike_fit->SetFillColor(kGray+2);
      hlike_fit->SetLineColor(kGray+2);
      hlike_fit->SetFillStyle(3003);
      hlike_fit->Draw("Hsame");

      TF1* fun1Norm = new TF1("fun1Norm","gaus",2.08,2.52);
      fun1Norm->SetParameters(fun1->GetParameter(3)/sqrt(2.*TMath::Pi())/fun1->GetParameter(5),fun1->GetParameter(4),fun1->GetParameter(5));
      fun1Norm->SetParError (0,fun1->GetParError(3));
      fun1Norm->SetParError (1,fun1->GetParError(4));
      fun1Norm->SetParError (2,fun1->GetParError(5));

      Float_t chi2 = fun1Norm->GetChisquare();
      Float_t ndf = fun1Norm->GetNDF();
      Float_t amp = fun1Norm->GetParameter(0);
      Float_t amperror = fun1Norm->GetParError(0);
      Float_t mean = fun1Norm->GetParameter(1);
      Float_t meanerror = fun1Norm->GetParError(1);
      Float_t sigma = fun1Norm->GetParameter(2);
      Float_t sigmaerror = fun1Norm->GetParError(2);

      TLegend *leg = new TLegend(0.66, 0.58, 0.88, 0.72);
      leg->SetBorderSize(0);
      leg->SetTextFont(43);
      leg->SetTextSize(26);

      leg->AddEntry(hunlike, "pK^{-}#pi^{+} + #bar{p}K^{+}#pi^{-} ", "pl");
      leg->AddEntry(hlike, "wrong-sign", "l");

      sprintf(buf, "(b)");
      drawLatex(0.18, 0.92, buf, 43, 26, 1);
      sprintf(buf, "%s ", "10-80%");
      drawLatex(0.24, 0.92, buf, 43, 26, 1);
      sprintf(buf, "%2.1f<p_{T}<%2.1f GeV/c", 3.0, 6.0);
      drawLatex(0.64, 0.87, buf, 43, 26, 1);

      sprintf(buf, "#(#Lambda_{c}) = %3.0f #pm %2.0f", yld1, yld1_err);
      drawLatex(0.18, 0.85, buf, 43, 23, 1);

      std::cout << "amp = " << amp << ": mean = " << mean << ": sigma = " << sigma << std::endl;

      pad2->cd();
      pad2->SetLogy(0);
      setpad(pad2, 0.14, 0.03, 0.03, 0.005);
      pad2->SetTickx(0);
      pad2->SetTicky(0);
  
      
      fun1_cent->SetNpx(1000);
      fun1Bg_cent->SetNpx(1000);

      fun1Bg_cent->SetLineStyle(2);
      fun1Bg_cent->SetLineColor(1);
      fun1Bg_cent->SetLineWidth(1);

      hunlike_cent->GetXaxis()->SetRangeUser(2.08,2.52);
      hunlike_cent->GetYaxis()->SetRangeUser(-2,125);
      hunlike_cent->SetMarkerStyle(20);
      hunlike_cent->SetMarkerSize(1);
      hunlike_cent->SetLineColor(2);
      hunlike_cent->SetLineWidth(2.);
      hunlike_cent->SetMarkerColor(2);
      hunlike_cent->Draw();
      hunlike_cent_fit->Draw("same");
      hunlike_cent->Draw("same");

      sprintf(buf, "Counts/(%d MeV/c^{2})", 10);
      hunlike_cent->GetYaxis()->SetTitle(buf);
      hunlike_cent->GetXaxis()->SetLabelOffset(0.01);
      hunlike_cent->GetYaxis()->SetLabelOffset(0.01);
      hunlike_cent->GetXaxis()->SetTitle("M_{pK#pi} (GeV/c^{2})");
      hunlike_cent->GetXaxis()->SetNdivisions(205);
      hunlike_cent->GetYaxis()->SetNdivisions(205);
      hunlike_cent->GetXaxis()->SetTitleSize(0.06);
      hunlike_cent->GetYaxis()->SetTitleSize(0.06);
      hunlike_cent->GetXaxis()->SetLabelSize(0.06);
      hunlike_cent->GetYaxis()->SetLabelSize(0.06);
      cout << "Axis Label FONT = "<< hunlike_cent->GetXaxis()->GetLabelFont() <<endl;;
      cout << "Axis Label  FONT = "<< hunlike_cent->GetYaxis()->GetLabelFont() <<endl;;
      hunlike_cent->GetXaxis()->SetTitleOffset(1.1);
      hunlike_cent->GetYaxis()->SetTitleOffset(1.1);
      hunlike_cent->GetXaxis()->SetTitleFont(42);
      hunlike_cent->GetYaxis()->SetTitleFont(42);
      hunlike_cent->GetXaxis()->SetLabelFont(42);
      hunlike_cent->GetYaxis()->SetLabelFont(42);
      hunlike_cent->GetXaxis()->CenterTitle();
      hunlike_cent->GetYaxis()->CenterTitle();

      hlike_fit_cent->SetFillColor(kGray+2);
      hlike_fit_cent->SetLineColor(kGray+2);
      hlike_fit_cent->SetFillStyle(3003);
      hlike_fit_cent->Draw("Hsame");

      TF1* fun1Norm_cent = new TF1("fun1Norm","gaus",2.08,2.52);
      fun1Norm_cent->SetParameters(fun1_cent->GetParameter(3)/sqrt(2.*TMath::Pi())/fun1_cent->GetParameter(5),fun1_cent->GetParameter(4),fun1_cent->GetParameter(5));
      fun1Norm_cent->SetParError (0,fun1_cent->GetParError(3));
      fun1Norm_cent->SetParError (1,fun1_cent->GetParError(4));
      fun1Norm_cent->SetParError (2,fun1_cent->GetParError(5));

      Float_t chi2_cent = fun1Norm_cent->GetChisquare();
      Float_t ndf_cent = fun1Norm_cent->GetNDF();
      Float_t amp_cent = fun1Norm_cent->GetParameter(0);
      Float_t amperror_cent = fun1Norm_cent->GetParError(0);
      Float_t mean_cent = fun1Norm_cent->GetParameter(1);
      Float_t meanerror_cent = fun1Norm_cent->GetParError(1);
      Float_t sigma_cent = fun1Norm_cent->GetParameter(2);
      Float_t sigmaerror_cent = fun1Norm_cent->GetParError(2);

      TLegend *leg_cent = new TLegend(0.66, 0.56, 0.88, 0.72);
      leg_cent->SetBorderSize(0);
      leg_cent->SetTextFont(43);
      leg_cent->SetTextSize(26);

      leg_cent->AddEntry(hunlike_cent, "pK^{-}#pi^{+} + #bar{p}K^{+}#pi^{-} ", "pl");
      leg_cent->AddEntry(hlike_fit_cent, "wrong-sign", "f");
      leg_cent->Draw("same");

      sprintf(buf, "Au+Au, #sqrt{s_{NN}} = 200GeV ");
      drawLatex(0.54, 0.89, buf, 43, 26, 1);
      sprintf(buf, "(a)");
      drawLatex(0.18, 0.9, buf, 43, 26, 1);
      sprintf(buf, "%s ", "0-20%");
      drawLatex(0.24, 0.9, buf, 43, 26, 1);
      sprintf(buf, "%2.1f<p_{T}<%2.1f GeV/c", 3.0, 6.0);
      drawLatex(0.64, 0.8, buf, 43, 26, 1);
      sprintf(buf, "#bf{#it{STAR}}");
      drawLatex(0.21, 0.72, buf, 43, 26, 1);

      sprintf(buf, "#(#Lambda_{c}) = %3.0f #pm %2.0f", yld1_cent, yld1_err_cent);
      drawLatex(0.18, 0.83, buf, 43, 23, 1);

      sprintf(buf, "LcInvmassCombined_1080.pdf");
      c1->SaveAs(buf); 
      sprintf(buf, "LcInvmassCombined_1080.png");
      c1->SaveAs(buf); 
      sprintf(buf, "LcInvmassCombined_1080.eps");
      c1->SaveAs(buf); 
   }

   return 0;
}
