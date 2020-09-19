
#include "anaConst.h"
void CanvasPartition(TCanvas *C,const Int_t Nx = 2,const Int_t Ny = 2,
                     Float_t lMargin = 0.15, Float_t rMargin = 0.05,
                     Float_t bMargin = 0.15, Float_t tMargin = 0.05);

void DrawAll2()
{
//  gROOT->ProcessLine(".x ~/myStyle.C");

   auto C = new TCanvas("C","canvas",1024,640);
   C->SetFillStyle(4000);

   // Number of PADS
   const Int_t Nx = 1;
   const Int_t Ny = 3;

   // Margins
   Float_t lMargin = 0.12;
   Float_t rMargin = 0.05;
   Float_t bMargin = 0.15;
   Float_t tMargin = 0.05;

   // Canvas setup
   CanvasPartition(C,Nx,Ny,lMargin,rMargin,bMargin,tMargin);
   TPad *pad[Nx][Ny];

   for (Int_t i=0;i<Nx;i++) {
      for (Int_t j=0;j<Ny;j++) {
         C->cd(0);
         // Get the pads previously created.
         char pname[16];
         sprintf(pname,"pad_%i_%i",i,j);
         pad[i][j] = (TPad*) gROOT->FindObject(pname);
         pad[i][j]->Draw();
         pad[i][j]->SetFillStyle(4000);
         pad[i][j]->SetFrameFillStyle(4000);
         pad[i][j]->cd();
      }
   }

  auto f = new TFile("FFOutput/DrawsysChange_default_May5_FIT.root", "READ");
  auto fchi = (TH1F*)f->Get("chi2");
  Float_t lowpt[9],highpt[9];
  for(Int_t c=0; c< 9; c++){
    lowpt[c] = anaConst::lpt[c];
    highpt[c] = anaConst::hpt[c];
  }
  auto null = 0;
    for(Int_t ptbin=0; ptbin<7; ptbin++)
    {
      
      if(ptbin==1 || ptbin==3 || ptbin==4 || ptbin==6) continue;
      
//      // Size factors
//      Float_t xFactor = pad[0][0]->GetAbsWNDC()/pad[i][j]->GetAbsWNDC();
//      Float_t yFactor = pad[0][0]->GetAbsHNDC()/pad[i][j]->GetAbsHNDC();
      
      auto htmp = (TH1D*)f->Get(Form("bcToe_DeltaPhi_fit_%1.1f_%1.1f", lowpt[ptbin], highpt[ptbin]));
      
      char hname[16];
      sprintf(hname,"h_%i",null);
      TH1D *dClone = (TH1D*)htmp->Clone(hname);
      dClone->Reset();
      dClone->Draw();
      
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
      
//      cplot->cd(null+1);
      pad[0][null]->cd();
      
      TPaveText *Name = new TPaveText(gStyle->GetPadLeftMargin() + 0.4,
                                      0.77 - gStyle->GetPadTopMargin(),
                                      gStyle->GetPadLeftMargin() + 0.8,
                                      0.95 - gStyle->GetPadTopMargin(),
                                      "BRNDC");
      Name->AddText("STAR p+p 200 GeV");
      Name->SetFillColorAlpha(0, 0);
      Name->SetTextAlign(12);
      Name->SetBorderSize(0);
  //    TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
  //    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
      TGaxis::SetMaxDigits(3);
  //    pad1->SetBottomMargin(0.02);
  //    pad1->SetTopMargin(0.08);
  //    pad2->SetTopMargin(0.015);
  //    pad2->SetBottomMargin(0.5);
  //    pad2->SetBorderMode(0);
  //    pad1->SetBorderMode(0);
  //    cplot->SetBorderMode(0);
  //    pad1->Draw();
  //    pad2->Draw();
  //    pad1->cd();
  //    if(ptbin == 5)gPad->SetBottomMargin(0.18);
  //    if(ptbin == 0){
//      dClone->GetYaxis()->CenterTitle(true);
//      dClone->GetYaxis()->SetLabelOffset(0.01);
//      dClone->GetYaxis()->SetLabelSize(0.09);
//      dClone->GetYaxis()->SetTitleSize(0.09);
//      dClone->GetYaxis()->SetTitleOffset(0.76);
      
//      dClone->GetXaxis()->SetLabelOffset(0.01);
//      dClone->GetXaxis()->SetLabelSize(0.09);
//      dClone->GetXaxis()->SetTitleSize(0.12);
//      dClone->GetXaxis()->SetTitleOffset(0.95);
  //    }

//      dClone->GetXaxis()->SetTitle(" ");
//      dClone->GetYaxis()->SetTitle(" ");

//      if(ptbin == 5)dClone->GetXaxis()->SetTitle("#Delta_{#phi_{eh}}(rad)");
//      if(ptbin == 0)dClone->GetYaxis()->SetTitle("#frac{1}{N_{NPE}} #frac{dN}{d(#Delta#phi)}");
      //        dClone->GetYaxis()->SetRangeUser(0.2,max*10);

      cClone2->SetLineStyle(6);
      bClone2->SetLineStyle(8);
      dClone->GetXaxis()->SetNdivisions(510);
      dClone->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      cClone2->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      bClone2->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      dClone->Draw("same p");
//      cClone->Draw("same hist]["); // combine
//      cClone2->Draw("same hist][");
//      bClone2->Draw("same hist][");
//      legg->Draw("same");
//      Name->Draw("SAME");
//      txt->Draw("same");
//      txt1->Draw("same");
      if(null == 0){
        TLatex *xtitle = new TLatex();
        xtitle->SetTextAlign(22);
        xtitle->SetTextSize(0.1415929);
        xtitle->DrawLatexNDC(0.5,0.1,"X Title");
      }
      
  //    pad2->cd();
  //    auto Fit_Ratio= (TH1F*)dClone->Clone(Form("dClone"));
  //    Fit_Ratio->SetLineColor(kBlack);
  //    Fit_Ratio->SetMarkerColor(kBlack);
  //    Fit_Ratio->Divide(cClone);
  //
  //    Fit_Ratio->SetTitle(0);
  //    Fit_Ratio->GetYaxis()->SetRangeUser(0.6,1.4);
  //    Fit_Ratio->GetYaxis()->SetTitleSize(0.15);
  ////    Fit_Ratio->GetYaxis()->SetTitleOffset(0.3);
  //    Fit_Ratio->GetYaxis()->SetLabelSize(0.1);
  //    Fit_Ratio->GetYaxis()->SetNdivisions(505);
  //    Fit_Ratio->GetYaxis()->CenterTitle();
  //    Fit_Ratio->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
  //    Fit_Ratio->GetXaxis()->SetTitleSize(0.24);
  ////    Fit_Ratio->GetXaxis()->SetTitleOffset(0.8);
  //    Fit_Ratio->GetXaxis()->SetLabelSize(0.14);
  //    Fit_Ratio->GetXaxis()->SetNdivisions(510);
  //    Fit_Ratio->GetXaxis()->SetTitle("#Delta_{#phi_{eh}}(rad)");
  //    Fit_Ratio->GetYaxis()->SetTitle("Data/Fit");
  //    Fit_Ratio->Draw("hist][");
      null++;
    }
  C->cd(0);
  auto ytitlepad = new TPad("ytitlepad","",0.,0.,0.1,1.);
  ytitlepad->Draw();
  ytitlepad->cd();
  TLatex *ytitle = new TLatex();
  ytitle->SetTextAlign(22);
  ytitle->SetTextSize(0.3);
  ytitle->SetTextAngle(90);
  ytitle->DrawLatexNDC(0.5,0.5,"Y Title");

}



void CanvasPartition(TCanvas *C,const Int_t Nx,const Int_t Ny,
                     Float_t lMargin, Float_t rMargin,
                     Float_t bMargin, Float_t tMargin)
{
   if (!C) return;

   // Setup Pad layout:
   Float_t vSpacing = 0.0;
   Float_t vStep  = (1.- bMargin - tMargin - (Ny-1) * vSpacing) / Ny;

   Float_t hSpacing = 0.0;
   Float_t hStep  = (1.- lMargin - rMargin - (Nx-1) * hSpacing) / Nx;

   Float_t vposd,vposu,vmard,vmaru,vfactor;
   Float_t hposl,hposr,hmarl,hmarr,hfactor;

   for (Int_t i=0;i<Nx;i++) {

      if (i==0) {
         hposl = 0.0;
         hposr = lMargin + hStep;
         hfactor = hposr-hposl;
         hmarl = lMargin / hfactor;
         hmarr = 0.0;
      } else if (i == Nx-1) {
         hposl = hposr + hSpacing;
         hposr = hposl + hStep + rMargin;
         hfactor = hposr-hposl;
         hmarl = 0.0;
         hmarr = rMargin / (hposr-hposl);
      } else {
         hposl = hposr + hSpacing;
         hposr = hposl + hStep;
         hfactor = hposr-hposl;
         hmarl = 0.0;
         hmarr = 0.0;
      }

      for (Int_t j=0;j<Ny;j++) {

         if (j==0) {
            vposd = 0.0;
            vposu = bMargin + vStep;
            vfactor = vposu-vposd;
            vmard = bMargin / vfactor;
            vmaru = 0.0;
         } else if (j == Ny-1) {
            vposd = vposu + vSpacing;
            vposu = vposd + vStep + tMargin;
            vfactor = vposu-vposd;
            vmard = 0.0;
            vmaru = tMargin / (vposu-vposd);
         } else {
            vposd = vposu + vSpacing;
            vposu = vposd + vStep;
            vfactor = vposu-vposd;
            vmard = 0.0;
            vmaru = 0.0;
         }

         C->cd(0);

         char name[16];
         sprintf(name,"pad_%i_%i",i,j);
         TPad *pad = (TPad*) gROOT->FindObject(name);
         if (pad) delete pad;
         pad = new TPad(name,"",hposl,vposd,hposr,vposu);
         pad->SetLeftMargin(hmarl);
         pad->SetRightMargin(hmarr);
         pad->SetBottomMargin(vmard);
         pad->SetTopMargin(vmaru);

         pad->SetFrameBorderMode(0);
         pad->SetBorderMode(0);
         pad->SetBorderSize(0);

         pad->Draw();
      }
   }
}
