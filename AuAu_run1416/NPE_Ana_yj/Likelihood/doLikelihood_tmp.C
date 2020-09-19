#include "fitData.C"
#include "TChain.h"
//#include "fitData_Pion.C"

void ZERO(TH1F* h){
  for(int i = 0; i<h->GetNbinsX()+1;i++){
    double temp = h->GetBinContent(i);
    if(temp<0)h->SetBinContent(i,0);
  }
}

void norm(TH1F *h);
void norm1(TH1F *h);

void doLikelihood_tmp(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  gStyle->SetPalette(56);
  TGaxis::SetMaxDigits(4);
  
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  //int const numPtBins=5;
  //double binning[numPtBins+1]={0.6,1,1.5,2.5,3.5,8.5};
  //TFile *file_e = new TFile("./root/weights_electron.root"); // matt
  //TFile *file_p = new TFile("./root/weights_pion.root");//matt 
  TFile *file_e = new TFile("./root_yj/weights_electron_highPt_B10.root");
  TFile *file_p = new TFile("./root_yj/weights_pion_highPt_B10.root");//smooth
  auto electron_weight_povere=(TH1F*)file_e->Get("electron_weight_povere");
  auto electron_weight_nsige=(TH1F*)file_e->Get("electron_weight_nsige");
  auto electron_weight_deltabeta=(TH1F*)file_e->Get("electron_weight_deltabeta");
  auto electron_weight_zdist=(TH1F*)file_e->Get("electron_weight_zdist");
  auto electron_weight_phidist=(TH1F*)file_e->Get("electron_weight_phidist");
  auto pion_weight_povere=(TH1F*)file_p->Get("pion_weight_povere");
  auto pion_weight_nsigpi=(TH1F*)file_p->Get("pion_weight_nsigpi");
  auto pion_weight_deltabeta=(TH1F*)file_p->Get("pion_weight_deltabeta");
  auto pion_weight_zdist=(TH1F*)file_p->Get("pion_weight_zdist");
  auto pion_weight_phidist=(TH1F*)file_p->Get("pion_weight_phidist");
  //========================================================================
  

  TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);

  TCanvas *canv2 = new TCanvas ("canv2","weights"); // 这个图之前就应该画过
  //canv2->Divide(3,2);
  pion_weight_povere->SetLineColor(kRed);
  pion_weight_nsigpi->SetLineColor(kRed);
  pion_weight_deltabeta->SetLineColor(kRed);
  pion_weight_zdist->SetLineColor(kRed);
  pion_weight_phidist->SetLineColor(kRed);
  
  electron_weight_povere->GetYaxis()->SetTitle("Likelihood PDF"); // Probability
  electron_weight_nsige->GetYaxis()->SetTitle("Probability");
  pion_weight_nsigpi->GetYaxis()->SetTitle("Probability");
  electron_weight_deltabeta->GetYaxis()->SetTitle("Probability");
  electron_weight_zdist->GetYaxis()->SetTitle("Probability");
  electron_weight_phidist->GetYaxis()->SetTitle("Probability");
  
  //electron_weight_povere->GetYaxis()->SetTitleOffset(1.05);
  //electron_weight_nsige->GetYaxis()->SetTitleOffset(1.3);
  //pion_weight_nsigpi->GetYaxis()->SetTitleOffset(1.3);
  //electron_weight_deltabeta->GetYaxis()->SetTitleOffset(1.3);
  //electron_weight_zdist->GetYaxis()->SetTitleOffset(1.3);
  //electron_weight_phidist->GetYaxis()->SetTitleOffset(1.3);
  
  electron_weight_povere->GetXaxis()->SetTitle("#it{pc}/#it{E}");
  electron_weight_nsige->GetXaxis()->SetTitle("n#sigma_{e}");
  pion_weight_nsigpi->GetXaxis()->SetTitle("n#sigma_{#pi}");
  electron_weight_zdist->GetXaxis()->SetTitle("#Delta#it{z}");
  electron_weight_phidist->GetXaxis()->SetTitle("#Delta#phi");
  
  //canv2->cd(1);
  electron_weight_povere->Draw("hist");
  pion_weight_povere->Draw("same hist");
  //electron_povere->Draw("same PE");
  //pion_povere->Draw("same PE");
  pion_weight_povere->SetLineColor(kRed);
  leg->AddEntry(electron_weight_povere,"Electrons","L");
  leg->AddEntry(pion_weight_povere,"Pions","L");
  leg->Draw("same");
  /*
   canv2->cd(2);
   electron_weight_zdist->Draw("hist");
   pion_weight_zdist->Draw("same hist");
   //electron_zdist->Draw("same PE");
   //pion_zdist->Draw("same PE");
   leg->Draw("same");
   canv2->cd(3);
   electron_weight_phidist->Draw("hist");
   pion_weight_phidist->Draw("same hist");
   //electron_phidist->Draw("same PE");
   //pion_phidist->Draw("same PE");
   leg->Draw("same");
   canv2->cd(4);
   electron_weight_nsige->Draw("hist");
   pion_weight_nsigpi->Draw("hist same");
   //electron_nsige->Draw("same PE");
   //pion_nsige->Draw("same PE");
   leg->Draw("same");
   //canv2->cd(5);
   //pion_weight_nsigpi->GetXaxis()->SetRangeUser(-5,13);
   //pion_weight_nsigpi->Draw("hist");
   // electron_nsigpi->Draw("same PE");
   //pion_nsigpi->Draw("same PE");
   //leg->Draw("same");
   canv2->cd(5);
   pion_deltabeta_e->GetXaxis()->SetTitle("(1/#beta - 1/#beta_{exp,e})/(1/#beta)");
   pion_deltabeta_e->GetYaxis()->SetTitle("Probability");
   //pion_deltabeta_e->Draw("PE");
   electron_weight_deltabeta->Draw("same hist");
   pion_weight_deltabeta->Draw("same hist");
   //electron_deltabeta_e->Draw("same PE");
   leg->Draw("same");
   //canv2->cd(7);
   //electron_deltabeta_p->GetYaxis()->SetRangeUser(0,1);
   //electron_deltabeta_p->GetXaxis()->SetRangeUser(-0.030,0.020);
   // electron_deltabeta_p->GetYaxis()->SetTitle("Probability");
   //electron_deltabeta_p->GetXaxis()->SetTitle("(1/#beta - 1/#beta_{exp,#pi})/(1/#beta)");
   //electron_deltabeta_p->Draw("PE");
   //pion_weight_deltabeta->Draw("same hist");
   //pion_deltabeta_p->Draw("same PE");
   //leg->Draw("same");
   */
  canv2->SaveAs("plots_likelihood_yj_B10_TuneCut/Elec_pion_Probability.pdf");
  //========================================================================

  
}
