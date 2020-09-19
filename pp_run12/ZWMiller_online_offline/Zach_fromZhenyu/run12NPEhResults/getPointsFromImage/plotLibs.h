#ifndef HEADER_UNIQ_PLOTLIBS_HH
#define HEADER_UNIQ_PLOTLIBS_HH

#include<vector>
#include<TCanvas.h>
#include<TH1.h>
#include<TH2.h>
#include<TGraphErrors.h>
#include<TGraphAsymmErrors.h>

void Divide          (TCanvas* can,int x,int y,float marx, float mary);
TH1D* gr2Hist        (const TGraphErrors* g1, std::vector<double> xBins);
TH1D* grA2Hist       (const TGraphAsymmErrors* g1, std::vector<double> xBins);
TGraphErrors* hist2Gr(TH1D* h1, double* xVals);
TGraphErrors* Divide (TGraphErrors* g1, TGraphErrors* g2);
TGraphErrors* Divide (TGraphAsymmErrors* g1, TGraphAsymmErrors* g2);

void formatHist1     (TH1* coor);
void formatHist2     (TH2* coor);
void formatGraph     (TGraphErrors* coor);
void formatGraph     (TGraph* coor);
void formatGraphA    (TGraphAsymmErrors* coor);


#endif
