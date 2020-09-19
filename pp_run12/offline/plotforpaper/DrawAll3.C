#include "anaConst.h"

void CanvasPartition(TCanvas *C,const Int_t Nx = 2,const Int_t Ny = 2,
                     Float_t lMargin = 0.15, Float_t rMargin = 0.05,
                     Float_t bMargin = 0.15, Float_t tMargin = 0.05);

void DrawAll3()
{
  
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  gStyle->SetOptStat(0);
  
  auto f = new TFile("FFOutput/DrawsysChange_default_May5_FIT.root", "READ");
  auto fchi = (TH1F*)f->Get("chi2");
  Float_t lowpt[3],highpt[3];
  Int_t null = 0;
  for(Int_t ptbin=0; ptbin< 7; ptbin++){
    if(ptbin==1 || ptbin==3 || ptbin==4 || ptbin==6) continue;
    lowpt[2-null] = anaConst::lpt[ptbin];
    highpt[2-null] = anaConst::hpt[ptbin];
    cout<<lowpt[null]<<highpt[null]<<endl;
    
    null++;
  }
  
  TCanvas *C = (TCanvas*) gROOT->FindObject("C");
  if (C) delete C;
  C = new TCanvas("C","canvas",500,45,530,755);
  C->SetFillStyle(4000);
  
  // Number of PADS
  const Int_t Nx = 1;
  const Int_t Ny = 3;
  
  // Margins
  Float_t lMargin = 0.18;
  Float_t rMargin = 0.05;
  Float_t bMargin = 0.15;
  Float_t tMargin = 0.05;
  
  // Canvas setup
  CanvasPartition(C,Nx,Ny,lMargin,rMargin,bMargin,tMargin);
  
  
  // Dummy histogram.
  //  TH1F *h = (TH1F*) gROOT->FindObject("histo");
  //  if (h) delete h;
  //  h = new TH1F("histo","",100,-5.0,5.0);
  //  h->FillRandom("gaus",10000);
  //  h->GetXaxis()->SetTitle("x axis");
  //  h->GetYaxis()->SetTitle("y axis");
  //
  TPad *pad[Nx][Ny];
  
  for (Int_t i=0;i<Nx;i++) {
    for (Int_t j=0;j<Ny;j++) {
      auto h = (TH1D*)f->Get(Form("bcToe_DeltaPhi_fit_%1.1f_%1.1f", lowpt[j], highpt[j]));
      
      C->cd(0);
      
      // Get the pads previously created.
      char pname[16];
      sprintf(pname,"pad_%i_%i",i,j);
      pad[i][j] = (TPad*) gROOT->FindObject(pname);
      pad[i][j]->Draw();
      pad[i][j]->SetFillStyle(4000);
      pad[i][j]->SetFrameFillStyle(4000);
      pad[i][j]->cd();
      
      // Size factors
      Float_t xFactor = pad[0][0]->GetAbsWNDC()/pad[i][j]->GetAbsWNDC();
      Float_t yFactor = pad[0][0]->GetAbsHNDC()/pad[i][j]->GetAbsHNDC();
      
      char hname[16];
      sprintf(hname,"h_%i_%i",i,j);
      TH1D *dClone = (TH1D*) h->Clone(hname);
      dClone->Reset();
      dClone->Draw();
      
      //       y axis range
      //      hFrame->GetYaxis()->SetRangeUser(0.0001,1.2*h->GetMaximum());
      
      // Format for y axis
      dClone->GetYaxis()->SetLabelFont(43);
      dClone->GetYaxis()->SetLabelSize(16);
      dClone->GetYaxis()->SetLabelOffset(0.02);
      dClone->GetYaxis()->SetTitleFont(43);
      dClone->GetYaxis()->SetTitleSize(16);
      dClone->GetYaxis()->SetTitleOffset(5);
      
      dClone->GetYaxis()->CenterTitle();
      dClone->GetYaxis()->SetNdivisions(505);
      
      // TICKS Y Axis
      //      hFrame->GetYaxis()->SetTickLength(xFactor*0.04/yFactor);
      
      // Format for x axis
      dClone->GetXaxis()->SetLabelFont(43);
      dClone->GetXaxis()->SetLabelSize(16);
      dClone->GetXaxis()->SetLabelOffset(0.02);
      dClone->GetXaxis()->SetTitleFont(43);
      dClone->GetXaxis()->SetTitleSize(16);
      dClone->GetXaxis()->SetTitleOffset(5);
//
      
      dClone->GetXaxis()->CenterTitle();
      dClone->GetXaxis()->SetNdivisions(505);
      
      dClone->GetXaxis()->SetTitle(" ");
      dClone->GetYaxis()->SetTitle(" ");
      
      // TICKS X Axis
      //      hFrame->GetXaxis()->SetTickLength(yFactor*0.06/xFactor);
      
      auto cClone = (TH1D*)f->Get(Form("bcToe_DeltaPhi_%1.1f_%1.1f", lowpt[j], highpt[j]));
      auto cClone2 = (TH1D*)f->Get(Form("cToe_DeltaPhi_%1.1f_%1.1f", lowpt[j], highpt[j]));
      auto bClone2 = (TH1D*)f->Get(Form("bToe_DeltaPhi_%1.1f_%1.1f", lowpt[j], highpt[j]));
      
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
      Float_t curChi2 = fchi->GetBinContent(j);
      Int_t curNDF = 47;
      sprintf(chi2,"#chi^{2}/NDF=%1.2f/%d",curChi2, curNDF);
      sprintf(ptShow,"#it{p}_{T} #in [%1.1f,%1.1f] GeV",lowpt[j],highpt[j]);
      sprintf(entr,"High Tower 2");
      txt->AddText(ptShow);
      txt1->AddText(entr);
      txt1->AddText(chi2);
      TPaveText *Name = new TPaveText(gStyle->GetPadLeftMargin() + 0.4,
                                      0.77 - gStyle->GetPadTopMargin(),
                                      gStyle->GetPadLeftMargin() + 0.8,
                                      0.95 - gStyle->GetPadTopMargin(),
                                      "BRNDC");
      Name->AddText("STAR p+p 200 GeV");
      Name->SetFillColorAlpha(0, 0);
      Name->SetTextAlign(12);
      Name->SetBorderSize(0);
      
      TGaxis::SetMaxDigits(3);
      
      cClone2->SetLineStyle(6);
      bClone2->SetLineStyle(8);
      dClone->GetXaxis()->SetNdivisions(510);
      dClone->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      cClone2->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      bClone2->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      //      dClone->Draw("same p");
      h->Draw("same p");
      cClone->Draw("same hist]["); // combine
      cClone2->Draw("same hist][");
      bClone2->Draw("same hist][");
      legg->Draw("same");
      Name->Draw("SAME");
      txt->Draw("same");
      txt1->Draw("same");
      
      if(j == 0){
        TLatex *xtitle = new TLatex();
        xtitle->SetTextAlign(22);
        xtitle->SetTextSize(0.09);
        xtitle->DrawLatexNDC(0.6,0.22,"#Delta_{#phi_{eh}}(rad)");
      }
      if(j==2){
        
        TLatex *ytitle = new TLatex();
        ytitle->SetTextAlign(22);
        ytitle->SetTextSize(0.09);
        ytitle->SetTextAngle(90);
//        ytitle->DrawLatexNDC(0.,0.38,"#frac{1}{N_{NPE}} #frac{dN}{d(#Delta#phi)}");
        ytitle->DrawLatexNDC(0.07,0.43,"1/N_{e}(dN/d#Delta#phi)_{e-h} (rad^{-1})");
      }
    }
  }
  C->cd();
  C->SaveAs("DrawAll3.pdf");
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
