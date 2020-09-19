#include "myFunction.h"
void Fit_Lc()
{
  gStyle->SetOptStat(00000);
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleOffset(1.3,"X");
  gStyle->SetTitleOffset(1,"Y");
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.13);
  //  gStyle->SetTicks(1,1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);


  TCanvas* c1 = new TCanvas("c1", "A Canvas",800,600);
  TFile* fin = new TFile("out/Lc_10_80.root", "READ"); //from data
  TH1F  *hLc_spectra_10_60_mean = (TH1F *)fin->Get("hLc_spectra_10_60_mean"); // 这是通过模型给出的Lc/D0比值与D0的谱结合得到的对Lc 的谱的 预言形式
  gPad ->SetLogy();
  
  hLc_spectra_10_60_mean->Draw();

  // TF1 *fp=new TF1("fp","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,10);
  TF1 *fp=new TF1("fp","[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+2.88153*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+2.88153*2.88153)-2.88153)/([2]*[1]),-[2])",0,20);
  fp->SetParameter(0,2.72777072933978959e-01);
  fp->SetParameter(1,3.42766125081739426e-01);
  fp->SetParameter(2,7.80713e+06);
  
  hLc_spectra_10_60_mean->Fit("fp","R","same",0.2,10);

  TF1 *pl=new TF1("pl",PowLaw_time_pt,0,20,3);
  pl->SetParameter(0,0.165619);
  pl->SetParameter(1,3437467.878645);
  pl->SetParameter(2,1.335002);
  
  pl->SetLineColor(4);
  hLc_spectra_10_60_mean->Fit(pl,"R","same",0.2,10);


TH2F *hh=new TH2F("hh","",100,0,20,100,0.5e-15,1);

  hh->SetTitle("");
  hh->GetXaxis()->SetTitle("p_{T} GeV/c");
  hh->GetYaxis()->SetTitle("d^{2}N/(N_{ev}dp_{T}dy) (GeV/c)^{-2}");
  hh->Draw();


  
  fp->Draw("same");
  hLc_spectra_10_60_mean->Draw("same");
  pl->Draw("same");

  TLegend *legend_D  = new TLegend(0.6,0.7,0.8,0.85);

  legend_D ->AddEntry(hLc_spectra_10_60_mean,"Scaled #\Lambda_{c} Model To Data","pl");
  legend_D ->AddEntry(fp,"Levy Fit","l");
  legend_D ->AddEntry(pl,"Power Law Fit","l");

  
  legend_D ->SetBorderSize(0);
  legend_D ->SetTextSize(0.04);
  legend_D ->SetFillStyle(0);
  legend_D ->SetTextFont(12);

  
  legend_D->Draw();
  c1->SaveAs("out/Lc.pdf");
  c1->SaveAs("out/Lc.png");
  c1->SaveAs("out/Lc.gif");
}
