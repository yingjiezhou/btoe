#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<math.h>
#include<TFile.h>
#include<TF1.h>
#include<TH1.h>
#include<TH2.h>
#include<TGraph.h>
#include<TGraphErrors.h>
#include<TCanvas.h>
#include<TLine.h>
#include<TLegend.h>
#include<TLatex.h>
#include<TPad.h>
#include<TStyle.h>
#include"plotLibs.h"

void Divide(TCanvas* can,int x,int y,float marx, float mary){
  double xcoor1[10][10], xcoor2[10][10], ycoor1[10][10], ycoor2[10][10];
  Double_t xlow,ylow,xup,yup;
  double ratx[]={1,1,1,1,1,1,1,1};
  double raty[]={1,1,1,1,1,1,1,1};
  double fracx[10], fracy[10];

  double xsli=0,ysli=0;//for boundary
  //define the slice size;
  ratx[0]   +=marx;
  raty[y-1] +=mary;
  for(int i=0;i<x;i++){
    xsli+=ratx[i];
  }
  for(int i=0;i<y;i++){
    ysli+=raty[i];
  }
  fracx[0]=0;  fracy[0]=1;
  for(int i=1;i<=x;i++){
    fracx[i]=fracx[i-1]+ratx[i-1]/xsli;
  }
  for(int i=1;i<=y;i++){
    fracy[i]=fracy[i-1]-raty[i-1]/ysli;
  }
  //rescale
  double scal=0.995;
  for(int i=0;i<=x;i++){
    fracx[i]= fracx[i]*scal+(1-scal)*(0.5-fracx[i]);
  }
  for(int i=0;i<=y;i++){
    fracy[i]= fracy[i]*scal+(1-scal)*(0.5-fracy[i]);
  }
  can->cd();
  can->Divide(x,y);
  int count=1;
  for(int i=0;i<y;i++){
    for(int j=0;j<x;j++){
      can->cd(count);
      count++;
      xlow = fracx[j];      xup = fracx[j+1];
      ylow = fracy[i+1];    yup = fracy[i];
      ycoor1[i][j] = ylow;      ycoor2[i][j] = yup;
      //cout<<xlow<<" "<<ylow<<" "<<xup<<" "<<yup<<endl;
      gPad->SetPad(xlow,ylow,xup,yup);
      gPad->SetLeftMargin(0.13);
      gPad->SetRightMargin(0.03);
      gPad->SetTopMargin(0.01);
      gPad->SetBottomMargin(0.1);
      /*      if(j==0){
        gPad->SetLeftMargin(marx/ratx[0]);
      }
      if(i==y-1){
        gPad->SetBottomMargin(mary/raty[y-1]);
        }*/
    }
  }
}

TH1D* gr2Hist(const TGraphErrors* g1, std::vector<double> xBins) { 
   int nBins  = g1->GetN();
   if (xBins.size() != nBins+1) {std::cout << "Nbins Incomapatble, Check bin Vector passed" << std::endl; return (TH1D*)0;}

   double* xx = g1->GetX(); 
   double* yy = g1->GetY();
   double* ye = g1->GetEY();

   std::string gName = g1->GetName();
   std::string hName = "h_" + gName ;

   TH1D* h1 = new TH1D(hName.c_str(), "", nBins, &xBins[0]);
   for (int ib=0; ib<nBins; ib++) {
      h1->SetBinContent(ib+1, yy[ib]); 
      h1->SetBinError  (ib+1, ye[ib]); 
   } 
   return h1;
}


TH1D* grA2Hist(const TGraphAsymmErrors* g1, std::vector<double> xBins) {
   int nBins  = g1->GetN();
   if (xBins.size() != nBins+1) {std::cout << "Nbins Incomapatble, Check bin Vector passed" << std::endl; return (TH1D*)0;}

   double* xx  = g1->GetX();
   double* yy  = g1->GetY();
   double* yeU = g1->GetEYhigh();
   double* yeL = g1->GetEYlow();

   std::string gName = g1->GetName();
   std::string hName = "h_" + gName ;

   TH1D* h1 = new TH1D(hName.c_str(), "", nBins, &xBins[0]);
   for (int ib=0; ib<nBins; ib++) {
      h1->SetBinContent(ib+1, yy[ib]);
      h1->SetBinError  (ib+1, (yeU[ib]+yeL[ib])/2.0);
   }
   return h1;
}


TGraphErrors* hist2Gr(TH1D* h1, double* xVals) {
   
   std::vector<double> xx;
   std::vector<double> yy;
   std::vector<double> ye;

   for (int ib=0; ib<h1->GetNbinsX(); ib++) {
      if (!xVals) xx.push_back(h1->GetBinCenter(ib+1));
      else        xx.push_back(xVals[ib]);

      yy.push_back(h1->GetBinContent(ib+1));
      ye.push_back(h1->GetBinError  (ib+1));
   }


   std::string hName = h1->GetName();
   std::string gName = "g_" + gName ;

   TGraphErrors* g1 = new TGraphErrors(h1->GetNbinsX(), &xx[0], &yy[0], 0, &ye[0]); 
   g1->SetName(gName.c_str());

   return g1;
}

TGraphErrors* Divide(TGraphErrors* g1, TGraphErrors* g2) {

   TGraphErrors* gRet = 0;
   if (g1->GetN() != g2->GetN()) {std::cout << "Divide: Cannot divide TGraphs with different number of bins " << std::endl; return gRet;}

   std::vector<double> binX;
   for (int ib=0; ib<g1->GetN()+1; ib++) binX.push_back(ib);
   TH1D* h1 = (TH1D*)gr2Hist(g1, binX);
   TH1D* h2 = (TH1D*)gr2Hist(g2, binX);

   h1->Divide(h2);

   gRet = (TGraphErrors*) hist2Gr(h1, g1->GetX());

   delete h1; delete h2;

   return gRet;

}

TGraphErrors* Divide(TGraphAsymmErrors* g1, TGraphAsymmErrors* g2) {

   TGraphErrors* gRet = 0;
   if (g1->GetN() != g2->GetN()) {std::cout << "Divide: Cannot divide TGraphs with different number of bins " << std::endl; return gRet;}

   std::vector<double> binX;
   for (int ib=0; ib<g1->GetN()+1; ib++) binX.push_back(ib);
   TH1D* h1 = (TH1D*)grA2Hist(g1, binX);
   TH1D* h2 = (TH1D*)grA2Hist(g2, binX);

   h1->Divide(h2);

   gRet = (TGraphErrors*) hist2Gr(h1, g1->GetX());

   delete h1; delete h2;

   return gRet;

}


void formatHist1(TH1* coor) {
   coor->GetYaxis()->SetNdivisions(505); coor->GetXaxis()->SetNdivisions(505);
   coor->GetYaxis()->SetTitleOffset(1.0);  coor->GetXaxis()->SetTitleOffset(1.0);
   coor->GetYaxis()->SetTitleFont(43);   coor->GetYaxis()->SetTitleSize(24);
   coor->GetYaxis()->SetLabelFont(43);   coor->GetYaxis()->SetLabelSize(23);
   coor->GetXaxis()->SetTitleFont(43);   coor->GetXaxis()->SetTitleSize(24);
   coor->GetXaxis()->SetLabelFont(43);   coor->GetXaxis()->SetLabelSize(23);
}

void formatHist2(TH2* coor) {
   coor->GetYaxis()->SetNdivisions(505); coor->GetXaxis()->SetNdivisions(505);
   coor->GetYaxis()->SetTitleOffset(2.0);  coor->GetXaxis()->SetTitleOffset(2.0);
   coor->GetYaxis()->SetTitleFont(43);   coor->GetYaxis()->SetTitleSize(22);
   coor->GetYaxis()->SetLabelFont(43);   coor->GetYaxis()->SetLabelSize(20);
   coor->GetXaxis()->SetTitleFont(43);   coor->GetXaxis()->SetTitleSize(22);
   coor->GetXaxis()->SetLabelFont(43);   coor->GetXaxis()->SetLabelSize(20);
   coor->GetZaxis()->SetTitleFont(43);   coor->GetZaxis()->SetTitleSize(22);
   coor->GetZaxis()->SetLabelFont(43);   coor->GetZaxis()->SetLabelSize(20);
}

void formatGraph(TGraphErrors* coor) {
   coor->GetYaxis()->SetNdivisions(505); coor->GetXaxis()->SetNdivisions(505);
   coor->GetYaxis()->SetTitleOffset(1.8);  coor->GetXaxis()->SetTitleOffset(1.8);
   coor->GetYaxis()->SetTitleFont(43);   coor->GetYaxis()->SetTitleSize(20);
   coor->GetYaxis()->SetLabelFont(43);   coor->GetYaxis()->SetLabelSize(18);
   coor->GetXaxis()->SetTitleFont(43);   coor->GetXaxis()->SetTitleSize(20);
   coor->GetXaxis()->SetLabelFont(43);   coor->GetXaxis()->SetLabelSize(18);
}

void formatGraph(TGraph* coor) {
   coor->GetYaxis()->SetNdivisions(505); coor->GetXaxis()->SetNdivisions(505);
   coor->GetYaxis()->SetTitleOffset(1.8);  coor->GetXaxis()->SetTitleOffset(1.8);
   coor->GetYaxis()->SetTitleFont(43);   coor->GetYaxis()->SetTitleSize(22);
   coor->GetYaxis()->SetLabelFont(43);   coor->GetYaxis()->SetLabelSize(22);
   coor->GetXaxis()->SetTitleFont(43);   coor->GetXaxis()->SetTitleSize(22);
   coor->GetXaxis()->SetLabelFont(43);   coor->GetXaxis()->SetLabelSize(22);
}

void formatGraphA(TGraphAsymmErrors* coor) {
   coor->GetYaxis()->SetNdivisions(505); coor->GetXaxis()->SetNdivisions(505);
   coor->GetYaxis()->SetTitleOffset(1.8);  coor->GetXaxis()->SetTitleOffset(1.8);
   coor->GetYaxis()->SetTitleFont(43);   coor->GetYaxis()->SetTitleSize(20);
   coor->GetYaxis()->SetLabelFont(43);   coor->GetYaxis()->SetLabelSize(18);
   coor->GetXaxis()->SetTitleFont(43);   coor->GetXaxis()->SetTitleSize(20);
   coor->GetXaxis()->SetLabelFont(43);   coor->GetXaxis()->SetLabelSize(18);
}
