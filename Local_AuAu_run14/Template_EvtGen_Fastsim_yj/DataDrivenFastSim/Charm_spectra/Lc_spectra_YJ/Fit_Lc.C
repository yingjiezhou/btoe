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

  const float twoPI = 2.*TMath::Pi();
  TCanvas* c1 = new TCanvas("c1", "A Canvas",800,600);
  gPad ->SetLogy();
  TGraphErrors *hLc_spectra_10_60_mean=new   TGraphErrors(3);
  const int nn = 3;
  const double ptbin[4] = {2.5, 3.5, 5.0, 8.0};
  const double yy[nn] = {8.3e-04, 6.2e-05, 1.9e-06};
  const double yyerr[nn] = {1.5e-04, 7.8e-06, 3.1e-07};
  const double yysys[nn] = {1.7e-04, 1.09e-05, 4.3e-07};
  for(int ipt=0; ipt<nn; ipt++) {
    float ptValue = 0.5*(ptbin[ipt]+ptbin[ipt+1]);
    hLc_spectra_10_60_mean->SetPoint(ipt,ptValue, yy[ipt]*twoPI*ptValue);
    hLc_spectra_10_60_mean->SetPointError(ipt,sqrt(yyerr[ipt]*yyerr[ipt]+ yysys[ipt]*yysys[ipt])*twoPI*ptValue); // 这就是最后存下来的hLc_spectra_10_60_mean
  }

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

  legend_D ->AddEntry(hLc_spectra_10_60_mean,"Scaled #Lambda_{c} Model To Data","pl");
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
  
  // zyj
  TH1F *mh1Lc_0_80=new TH1F("mh1Lc_0_80","",400,0,20);
  
  for(int i=0;i<mh1Lc_0_80->GetNbinsX();i++)
  {
    mh1Lc_0_80->SetBinContent(i+1,0.5*fabs(fp->Eval(mh1Lc_0_80->GetBinCenter(i+1))+pl->Eval(mh1Lc_0_80->GetBinCenter(i+1))));
    mh1Lc_0_80->SetBinError(i+1,0.5*fabs(fp->Eval(mh1Lc_0_80->GetBinCenter(i+1))-pl->Eval(mh1Lc_0_80->GetBinCenter(i+1))));
  }
  
  mh1Lc_0_80->SetFillColor(3);
  mh1Lc_0_80->SetFillStyle(3002);
  
  TFile *weight_charm_Fit_data=new TFile("weight_charm_Fit_data_0_80_Lc.root","RECREATE");
  weight_charm_Fit_data->cd();
  TH1F *F_levy_Lc_0_80= (TH1F *)mh1Lc_0_80->Clone("F_levy_Lc_0_80");
  TGraph *gr_F_levy_Lc_0_80= new TGraph(F_levy_Lc_0_80);
  
  F_levy_Lc_0_80->Write();
  gr_F_levy_Lc_0_80->Write();
  
}
