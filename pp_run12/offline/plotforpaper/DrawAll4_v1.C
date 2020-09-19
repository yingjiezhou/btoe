#include "anaConst.h"
#include "style.h"

void CanvasPartition(TCanvas *C,const Int_t Nx = 2,const Int_t Ny = 2,
                     Float_t lMargin = 0.15, Float_t rMargin = 0.05,
                     Float_t bMargin = 0.15, Float_t tMargin = 0.05);

void DrawAll4()
{
  
  //  gROOT->ProcessLine(".x ~/myStyle.C");
  setstyle();
  TLatex tx;
  tx.SetNDC();
  tx.SetTextFont(42);
  
//  gStyle->SetOptStat(0);
  
  auto f = new TFile("FFOutput/DrawsysChange_default_May5_FIT.root", "READ");
  auto fchi = (TH1F*)f->Get("chi2");
  Float_t lowpt[3],highpt[3];
  Int_t null = 0;
  for(Int_t ptbin=0; ptbin< 7; ptbin++){
    if(ptbin==1 || ptbin==3 || ptbin==4 || ptbin==6) continue;
    lowpt[null] = anaConst::lpt[ptbin];
    highpt[null] = anaConst::hpt[ptbin];
    cout<<lowpt[null]<<highpt[null]<<endl;
    
    null++;
  }
  
  TCanvas *C = (TCanvas*) gROOT->FindObject("C");
  if (C) delete C;
  C = new TCanvas("C","canvas",166,45,1427,671);
  C->SetFillStyle(4000);
  
  // Number of PADS
  const Int_t Nx = 3;
  const Int_t Ny = 2;
  
  // Margins
  Float_t lMargin = 0.1;
  Float_t rMargin = 0.05;
  //  Float_t bMargin = 0.15;
  //  Float_t tMargin = 0.05;
  Float_t bMargin = 0.1;
  Float_t tMargin = 0.;
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
      
      //      auto h = (TH1D*)f->Get(Form("bcToe_DeltaPhi_fit_%1.1f_%1.1f", lowpt[j], highpt[j]));
      auto dClone = (TH1D*)f->Get(Form("bcToe_DeltaPhi_fit_%1.1f_%1.1f", lowpt[i], highpt[i]));
      dClone->GetYaxis()->SetRangeUser(0.0001,1.1*dClone->GetMaximum());
      //      char hname[16];
      //      sprintf(hname,"h_%i_%i",i,j);
      //      TH1D *dClone = (TH1D*) h->Clone(hname);
      //      dClone->Reset();
      //      dClone->Draw();
      
      //       y axis range
      //      hFrame->GetYaxis()->SetRangeUser(0.0001,1.2*h->GetMaximum());
      
//      dClone->SetTitle(0);
      // Format for y axis
//      dClone->GetYaxis()->SetLabelFont(42);
//      dClone->GetYaxis()->SetLabelSize(16);
//      dClone->GetYaxis()->SetLabelOffset(0.02);
//      dClone->GetYaxis()->SetTitleFont(43);
//      dClone->GetYaxis()->SetTitleSize(16);
//      dClone->GetYaxis()->SetTitleOffset(3);
      
      dClone->GetYaxis()->CenterTitle();
      dClone->GetYaxis()->SetNdivisions(505);
      
      // TICKS Y Axis
      //      hFrame->GetYaxis()->SetTickLength(xFactor*0.04/yFactor);
      
      // Format for x axis
//      dClone->GetXaxis()->SetLabelFont(42);
//      dClone->GetXaxis()->SetLabelSize(16);
//      dClone->GetXaxis()->SetLabelOffset(0.02);
//      dClone->GetXaxis()->SetTitleFont(43);
//      dClone->GetXaxis()->SetTitleSize(16);
//      dClone->GetXaxis()->SetTitleOffset(5);
      //
      
      dClone->GetXaxis()->CenterTitle();
      dClone->GetXaxis()->SetNdivisions(510);
      
      dClone->GetXaxis()->SetTitle(" ");
      dClone->GetYaxis()->SetTitle("#frac{1}{N_{NPE}} #frac{dN}{d(#Delta#phi_{eh})}(rad^{-1})");
      
      // TICKS X Axis
      //      hFrame->GetXaxis()->SetTickLength(yFactor*0.06/xFactor);
      
      auto cClone = (TH1D*)f->Get(Form("bcToe_DeltaPhi_%1.1f_%1.1f", lowpt[i], highpt[i]));
      auto cClone2 = (TH1D*)f->Get(Form("cToe_DeltaPhi_%1.1f_%1.1f", lowpt[i], highpt[i]));
      auto bClone2 = (TH1D*)f->Get(Form("bToe_DeltaPhi_%1.1f_%1.1f", lowpt[i], highpt[i]));
      cClone->GetXaxis()->SetRangeUser(-1.5, 1.5);

     

//
//      cClone->SetMarkerSize(3);
//      cClone->SetLineWidth(3);
//
//      cClone->SetLineColor(kGreen+3);
//      cClone->SetMarkerColor(kGreen+3);
//      dClone->SetLineColor(kBlack);
//      dClone->SetMarkerColor(kBlack);
//      cClone2->SetLineColor(kBlue);
//      cClone2->SetMarkerColor(kBlue);
//      cClone2->SetLineWidth(2);
//      bClone2->SetLineColor(kRed);
//      bClone2->SetLineColor(kRed);
//      bClone2->SetLineWidth(2);
      
      TLegend *legg=new TLegend(0.54,0.71,1.,0.95);
      legg ->SetBorderSize(0);
      legg ->SetTextSize(0.04);
      legg ->SetFillStyle(0);
      legg ->SetTextFont(42);
      legg->AddEntry(cClone2,"MC D #rightarrow e","lp");
      legg->AddEntry(bClone2,"MC B #rightarrow e","lp");
      legg->AddEntry(dClone,"data NPE","pe");
      legg->AddEntry(cClone,"Template Fit","l");
      
      
      TPaveText* Name = new TPaveText(0.6,0.82,0.98,1.,"BRNDC");
      Name->SetFillColorAlpha(0, 0);
      Name->SetTextFont(42);
      Name->SetTextAlign(12);
      Name->SetBorderSize(0);
      Name->AddText("p+p @ #sqrt{s} = 200 GeV");
      
      char chi2[50];
      char entr[50];
      char ptShow[50];
      Float_t curChi2 = fchi->GetBinContent(i);
      Int_t curNDF = 47;
      sprintf(entr,"(a) HT0 Trigger Sample");
      if(i==1)sprintf(entr,"(b) HT2 Trigger Sample");
      if(i==2)sprintf(entr,"(c) HT2 Trigger Sample");

      sprintf(ptShow,"%1.1f < #it{p}_{T} < %1.1f GeV/c",lowpt[i], highpt[i]);
      sprintf(chi2,"#chi^{2}/NDF=%1.2f/%d",curChi2, curNDF);

      TPaveText* txt = new TPaveText(0.28,0.69,0.68,0.95,"BRNDC");
      if(i==1) txt = new TPaveText(0.04,0.69,0.37,0.95,"BRNDC");
      if(i==2) txt = new TPaveText(0.03,0.69,0.43,0.95,"BRNDC");

      txt->SetTextSize(0.05);
      txt->SetTextFont(42);
      txt->SetTextColor(1);
      txt->SetTextAlign(12);
      txt->SetBorderSize(0.);
      txt->SetFillColor(0);
      txt->SetFillStyle(0);
      txt->AddText(entr);
      txt->AddText(ptShow);
//      txt->AddText("p_{T}^{h}>0.3 GeV/c");
//      txt->AddText("|#eta|<0.7");
      txt->AddText(chi2);

//      TPaveText* txt1 = new TPaveText(0.56,0.6,0.9,0.76,"BRNDC");
//      txt1->SetTextSize(0.07);
//      txt1->SetTextColor(1);
//      txt1->SetBorderSize(0.1);
//      txt1->SetFillColor(0);
//      txt1->SetFillStyle(0);
      
//      txt1->AddText(entr);
//      txt1->AddText(chi2);
      
      TGaxis::SetMaxDigits(3);
      
      cClone2->SetLineStyle(6);
      bClone2->SetLineStyle(8);
      dClone->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      cClone2->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      bClone2->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      if(j == 1){
        
        Style(dClone,1,1,1,8,1,0.7,"p");
        Style(cClone,1,kGreen+2,4,8,kGreen+2,0.8,"same hist][");
        Style(cClone2,1,1,1,33,kBlue+2,0.8,"same pe");
        Style(bClone2,1,1,1,21,kRed,0.6,"same pe");

//        //      dClone->Draw("same p");
//        dClone->Draw("p");
//        //      h->Draw("same p");
//        cClone->Draw("same hist]["); // combine
//        cClone2->Draw("same pe");
//        bClone2->Draw("same pe");
        if(i==1)legg->Draw("same");
        if(i==0)Name->Draw("SAME");
        txt->Draw("same");

        

        //      txt1->Draw("same");
      }
      else{
        auto ll = new TLine(-TMath::Pi(),1., TMath::Pi(), 1.);
        ll->SetLineStyle(2);
        auto Fit_Ratio= (TH1F*)dClone->Clone(Form("dClone"));
//        Fit_Ratio->SetLineColor(kBlack);
//        Fit_Ratio->SetMarkerColor(kBlack);
        Fit_Ratio->Divide(cClone);
        
//        Fit_Ratio->SetTitle(0);
        Fit_Ratio->GetYaxis()->SetRangeUser(0.7,1.3);
        
//        Fit_Ratio->GetYaxis()->SetLabelFont(42);
        Fit_Ratio->GetYaxis()->SetLabelSize(0.09);
//        Fit_Ratio->GetYaxis()->SetLabelOffset(0.48);
//        Fit_Ratio->GetYaxis()->SetTitleFont(43);
        Fit_Ratio->GetYaxis()->SetTitleSize(0.11);
        Fit_Ratio->GetYaxis()->SetTitleOffset(0.48);
        
        Fit_Ratio->GetYaxis()->CenterTitle();
        Fit_Ratio->GetYaxis()->SetNdivisions(505);
        
        // TICKS Y Axis
        //      hFrame->GetYaxis()->SetTickLength(xFactor*0.04/yFactor);
        
        // Format for x axis
//        Fit_Ratio->GetXaxis()->SetLabelFont(42);
        Fit_Ratio->GetXaxis()->SetLabelSize(0.09);
//        Fit_Ratio->GetXaxis()->SetLabelOffset(0.02);
//        Fit_Ratio->GetXaxis()->SetTitleFont(43);
        Fit_Ratio->GetXaxis()->SetTitleSize(0.11);
//        Fit_Ratio->GetXaxis()->SetTitleOffset(5);
        //
        
        Fit_Ratio->GetXaxis()->CenterTitle(0);
        Fit_Ratio->GetXaxis()->SetNdivisions(510);
        
        Fit_Ratio->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
        Fit_Ratio->GetXaxis()->SetTitle(" ");
        Fit_Ratio->GetYaxis()->SetTitle("Data/Fit");
        if(i==2)Fit_Ratio->GetXaxis()->SetTitle("#Delta#phi_{eh}(rad)");
        
        Style(Fit_Ratio,1,1,1,8,1,0.7,"pe");
//        Fit_Ratio->Draw("pe");
        ll->Draw("same");
      }
      
      //      if(j == 0){
      //        TLatex *xtitle = new TLatex();
      //        xtitle->SetTextAlign(22);
      //        xtitle->SetTextSize(0.09);
      //        xtitle->DrawLatexNDC(0.6,0.22,"#Delta_{#phi_{eh}}(rad)");
      //      }
      //      if(j==2){
      //
      //        TLatex *ytitle = new TLatex();
      //        ytitle->SetTextAlign(22);
      //        ytitle->SetTextSize(0.09);
      //        ytitle->SetTextAngle(90);
      ////        ytitle->DrawLatexNDC(0.,0.38,"#frac{1}{N_{NPE}} #frac{dN}{d(#Delta#phi)}");
      //        ytitle->DrawLatexNDC(0.07,0.43,"1/N_{e}(dN/d#Delta#phi)_{e-h} (rad^{-1})");
      //      }
      
      
      
    }
  }
  C->cd();
  C->SaveAs("DrawAll4.pdf");
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
        vposu = bMargin + vStep-0.3;
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
