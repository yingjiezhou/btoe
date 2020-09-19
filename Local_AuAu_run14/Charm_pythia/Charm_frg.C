const bool pT=true;
void Charm_frg()
{

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
  
  TFile * inFile=  new TFile("Test.root","READ");


  TH2F * mh2D0=(TH2F *) inFile->Get("D0YVsPt");
  TH2F * mh2Dplus=(TH2F *) inFile->Get("DplusYVsPt");
  TH2F * mh2Ds=(TH2F *) inFile->Get("D_sYVsPt");
  TH2F * mh2Lc=(TH2F *) inFile->Get("LcYVsPt");


  TH1F *  mh1D0= (TH1F *)mh2D0->ProjectionX("mh1D0");
  TH1F *  mh1Dplus= (TH1F *)mh2Dplus->ProjectionX("mh1Dplus");
  TH1F *  mh1Ds= (TH1F *)mh2Ds->ProjectionX("mh1Ds");
  TH1F *  mh1Lc= (TH1F *)mh2Lc->ProjectionX("mh1Lc");

  TH2F *hh =new TH2F("hh","",100,0,8,100,0,1);
  hh->GetXaxis()->SetTitle("Rapidity");
  hh->GetYaxis()->SetTitle("Ratio");


  if(!pT)
    {
      TH1F *  mh1D0= (TH1F *)mh2D0->ProjectionY("mh1D0");
      TH1F *  mh1Dplus= (TH1F *)mh2Dplus->ProjectionY("mh1Dplus");
      TH1F *  mh1Ds= (TH1F *)mh2Ds->ProjectionY("mh1Ds");

      // TH1F *  mh1Lc= (TH1F *)mh2Lc->ProjectionY("mh1Lc");
      // TH2F *hh =new TH2F("hh","",100,-1.5,1.5,100,0,1);
      // hh->GetXaxis()->SetTitle("Rapidity");
      // hh->GetYaxis()->SetTitle("Ratio");

      
    }
    
   mh1D0->Rebin(4);
   mh1Dplus->Rebin(4);
   mh1Ds->Rebin(4);
   mh1Lc->Rebin(4);



  TCanvas *c5_D=new TCanvas("c5_D","",800,1200);
  
  mh1Dplus->Divide(mh1D0);
  mh1Ds->Divide(mh1D0);
  mh1Lc->Divide(mh1D0);

  mh1Dplus->SetLineColor(2);
  mh1Ds->SetLineColor(3);
  mh1Lc->SetLineColor(4);
  // mh1Lc->Fit("pol0");
  // mh1Ds->Fit("pol0");

  // mh1Dplus->

  TLegend *legend_D  = new TLegend(0.15,0.65,0.4,0.85);
  legend_D ->AddEntry(mh1Dplus,"D^{#pm}/(D^{0}+#bar{D^{0}})","l");
  legend_D ->AddEntry(mh1Ds,"Ds^{#pm}/(D^{0}+#bar{D^{0}})","l");
  legend_D ->AddEntry(mh1Lc,"#Lambda_{c}^{#pm}/(D^{0}+#bar{D^{0}})","l");

  legend_D ->SetBorderSize(0);
  legend_D ->SetTextSize(0.05);
  legend_D ->SetFillStyle(0);
  legend_D ->SetTextFont(62);

  


  

  hh->Draw();
  mh1Dplus->Draw("same");
  mh1Ds->Draw("same");
  mh1Lc->Draw("same");
  legend_D->Draw("same");
  
  
  c5_D->SaveAs("TestCharm_frag_y.pdf");

}
