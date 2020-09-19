// input from pl_fitPaper.C

#include "anaConst.h"
void DrawDeltaPhi(){
  
  gROOT->ProcessLine(".x ~/myStyle.C");

  auto f = new TFile("FFOutput/DrawsysChange_default_May5_FIT.root", "READ");
  auto fchi = (TH1F*)f->Get("chi2");
  Float_t lowpt[9],highpt[9];
  for(Int_t c=0; c< 9; c++){
    lowpt[c] = anaConst::lpt[c];
    highpt[c] = anaConst::hpt[c];
  }
  
  TCanvas *cplot = new TCanvas("cplot","full fit");

  for(Int_t ptbin=0; ptbin<7; ptbin++)
  {
    auto dClone = (TH1D*)f->Get(Form("bcToe_DeltaPhi_fit_%1.1f_%1.1f", lowpt[ptbin], highpt[ptbin]));
    auto cClone = (TH1D*)f->Get(Form("bcToe_DeltaPhi_%1.1f_%1.1f", lowpt[ptbin], highpt[ptbin]));
    auto cClone2 = (TH1D*)f->Get(Form("cToe_DeltaPhi_%1.1f_%1.1f", lowpt[ptbin], highpt[ptbin]));
    auto bClone2 = (TH1D*)f->Get(Form("bToe_DeltaPhi_%1.1f_%1.1f", lowpt[ptbin], highpt[ptbin]));
    
    cClone->SetMarkerSize(3);
    cClone->SetLineWidth(3);
    cClone->GetXaxis()->SetRangeUser(-1.5, 1.5);
    
    cClone->SetLineColor(kGreen+3);
    cClone->SetMarkerColor(kGreen+3);
    dClone->SetLineColor(kBlack);
    dClone->SetMarkerColor(kBlack);
    cClone2->SetLineColor(kBlue);
    cClone2->SetMarkerColor(kBlue);
    cClone2->SetLineWidth(2);
    bClone2->SetLineColor(kRed);
    bClone2->SetLineColor(kRed);
    bClone2->SetLineWidth(2);
    
    TLegend *legg=new TLegend(0.2,0.65,0.47,0.8);
    legg ->SetBorderSize(0);
    legg ->SetTextSize(0.04);
    legg ->SetFillStyle(0);
    legg ->SetTextFont(62);
    legg->AddEntry(cClone2,"MC D #rightarrow e","l");
    legg->AddEntry(bClone2,"MC B #rightarrow e","l");
    legg->AddEntry(dClone,"data NPE","pe");
    legg->AddEntry(cClone,"Template Fit","l");
    
    if(ptbin == 2){
      TPaveText* txt = new TPaveText(0.2,0.82,0.47,0.89,"BRNDC");
      txt->SetTextSize(0.07);
      txt->SetTextColor(1);
      txt->SetBorderSize(0.1);
      txt->SetFillColor(0);
      txt->SetFillStyle(0);
      TPaveText* txt1 = new TPaveText(0.56,0.6,0.9,0.76,"BRNDC");
      txt1->SetTextSize(0.07);
      txt1->SetTextColor(1);
      txt1->SetBorderSize(0.1);
      txt1->SetFillColor(0);
      txt1->SetFillStyle(0);
      char chi2[50];
      char entr[50];
      char ptShow[50];
      Float_t curChi2 = fchi->GetBinContent(ptbin);
      Int_t curNDF = 47;
      sprintf(chi2,"#chi^{2}/NDF=%1.2f/%d",curChi2, curNDF);
      sprintf(ptShow,"#it{p}_{T} #in [%1.1f,%1.1f] GeV",lowpt[ptbin],highpt[ptbin]);
      sprintf(entr,"High Tower 2");
      txt->AddText(ptShow);
      txt1->AddText(entr);
      txt1->AddText(chi2);
      
      cplot->cd();
      TPaveText *Name = new TPaveText(gStyle->GetPadLeftMargin() + 0.4,
                                      0.77 - gStyle->GetPadTopMargin(),
                                      gStyle->GetPadLeftMargin() + 0.8,
                                      0.95 - gStyle->GetPadTopMargin(),
                                      "BRNDC");
      Name->AddText("STAR p+p 200 GeV");
      Name->SetFillColorAlpha(0, 0);
      Name->SetTextAlign(12);
      Name->SetBorderSize(0);
      TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
      TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
      TGaxis::SetMaxDigits(3);
      pad1->SetBottomMargin(0.02);
      pad1->SetTopMargin(0.08);
      pad2->SetTopMargin(0.015);
      pad2->SetBottomMargin(0.5);
      pad2->SetBorderMode(0);
      pad1->SetBorderMode(0);
      cplot->SetBorderMode(0);
      pad1->Draw();
      pad2->Draw();
      pad1->cd();
      dClone->GetYaxis()->SetTitleSize(0.08);
      dClone->GetYaxis()->SetTitleOffset(0.78);
      dClone->GetXaxis()->SetTitle("#Delta_{#phi_{eh}}(rad)");
      dClone->GetYaxis()->SetTitle("#frac{1}{N_{NPE}} #frac{dN}{d(#Delta#phi)}");
      //        dClone->GetYaxis()->SetRangeUser(0.2,max*10);
     
      cClone2->SetLineStyle(6);
      bClone2->SetLineStyle(8);
      dClone->GetXaxis()->SetNdivisions(510);
      dClone->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      cClone2->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      bClone2->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      dClone->Draw("p");
      cClone->Draw("same hist]["); // combine
      cClone2->Draw("same hist][");
      bClone2->Draw("same hist][");
      legg->Draw("same");
      Name->Draw("SAME");
      txt->Draw("same");
      txt1->Draw("same");
      
      
      pad2->cd();
      auto Fit_Ratio= (TH1F*)dClone->Clone(Form("dClone"));
      Fit_Ratio->SetLineColor(kBlack);
      Fit_Ratio->SetMarkerColor(kBlack);
      Fit_Ratio->Divide(cClone);
      
      Fit_Ratio->SetTitle(0);
      Fit_Ratio->GetYaxis()->SetRangeUser(0.6,1.4);
      Fit_Ratio->GetYaxis()->SetTitleSize(0.15);
      Fit_Ratio->GetYaxis()->SetTitleOffset(0.3);
      Fit_Ratio->GetYaxis()->SetLabelSize(0.1);
      Fit_Ratio->GetYaxis()->SetNdivisions(505);
      Fit_Ratio->GetYaxis()->CenterTitle();
      Fit_Ratio->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      Fit_Ratio->GetXaxis()->SetTitleSize(0.24);
      Fit_Ratio->GetXaxis()->SetTitleOffset(0.8);
      Fit_Ratio->GetXaxis()->SetLabelSize(0.14);
      Fit_Ratio->GetXaxis()->SetNdivisions(510);
      Fit_Ratio->GetXaxis()->SetTitle("#Delta_{#phi_{eh}}(rad)");
      Fit_Ratio->GetYaxis()->SetTitle("Data/Fit");
      Fit_Ratio->Draw("hist][");
    }
    
  }
  
}
