// Delta Phi Plots - Z. Miller July 21, 2015
//
// .L pl_delPhiAll.C
// delPhiAll("FILENAME") # Without .root Extension
#include "anaConst.h"
TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize,    Int_t colorIndex);

void pl_delPhiAll(const char* FileName="May5", const char* FileNameR="default")
{
  // Set Style parameters for this macro
  gStyle->SetOptTitle(1); // Show Title (off by default for cleanliness)
  gStyle->SetOptStat(0);
//  gROOT->ProcessLine(".x ~/myStyle.C");
  // Open ROOT File
  char name[1000];
  sprintf(name,"FFOutput/npe_tree_%s_processed_default.root",FileName);
  TFile *f = new TFile(name,"READ");
  if (f->IsOpen()==kFALSE)
  { std::cout << "!!! File Not Found !!!" << std::endl;
    exit(1); }
  // f->ls(); // - DEBUG by printing all objects in ROOT file
  
  const Int_t numPtBins = anaConst::nPtBins;
  const Int_t numTrigs = 4;
  //  Int_t numPtBins = 12;
  //  Int_t numTrigs = 4;
  TH1F * LSIM[numPtBins*numTrigs];
  TH1F * USIM[numPtBins*numTrigs];
  TH1F * INCL[numPtBins*numTrigs];
  TH1F * Had[numPtBins*numTrigs];
  
  TCanvas * c[numTrigs];
  //  TCanvas * IN[numTrigs];
  
  char buf[1024];
  
  c[0] = new TCanvas("c0", "c0");
  c[0] -> Divide(3,2, 0, 0);
  
  int num = 0;
  for(Int_t trig = 2; trig < numTrigs; trig++){
    if(trig == 1 || trig == 3) continue;
    // Create and Segment Canvas
    //    c[trig] = new TCanvas(Form("c%i",trig),"Photonic Hists",0,0,900,500);
    
    //    IN[trig]= new TCanvas(Form("IN%i",trig),"Inclusive Hists",0,0,900,500);
    //    IN[trig]-> Divide(3,3);
    c[0] -> Update();
    //    IN[trig]-> Update();
    
    //    for(Int_t ptbin = 0; ptbin < numPtBins-2; ptbin++){
    for(Int_t ptbin = 2; ptbin < 5; ptbin++){
      
      num++;
      Int_t counter = numPtBins*trig+ptbin;
      // DEBUG cout << counter << endl;
      c[0]->cd(num);
      if(num == 1)      gPad->SetLeftMargin(0.12);

//      gPad->SetTickx(1);
//      gPad->SetTicky(1);
      
      // Grab Histograms for manipulation (can draw without Get, must Get for manip)
      LSIM[counter] = (TH1F*)f->Get(Form("projDelPhiPhotLSWt_%i_%i",ptbin,trig)); // Like Sign Delta Phi (Photonic Electrons)
      USIM[counter] = (TH1F*)f->Get(Form("projDelPhiPhotUSWt_%i_%i",ptbin,trig)); // Unlike Sign Delta Phi (Photonic Electrons)
      INCL[counter] = (TH1F*)f->Get(Form("projDelPhiInclWt_%i_%i",ptbin,trig));   // Inclusive Delta Phi eh
      Had[counter] = (TH1F*)f->Get(Form("projDelPhiHadHadWt_%i_%i",ptbin,trig));   // had Delta Phi eh
      
//      cout<<LSIM[counter]->GetXaxis()->FindBin(-1.5)<<endl;
//      cout<<LSIM[counter]->GetXaxis()->FindBin(1.5)<<endl;
//      cout<<LSIM[counter]->GetXaxis()->FindBin(-3)<<endl;
//      cout<<LSIM[counter]->GetXaxis()->FindBin(3)<<endl;

      // Actually manipulate histos and plot
      INCL[counter]->SetLineColor(kBlack);
      INCL[counter]->SetLineWidth(1);
      Had[counter]->GetXaxis()->SetTitle("#Delta#phi_{eh}(rad)");
      Had[counter]->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      Had[counter]->GetYaxis()->SetNdivisions(504);
      //      if(ptbin == 0)
      //        INCL[counter]->SetTitle("Semi-Inclusive Electrons");
      //      else if (ptbin == 1 && trig !=3)
      //        INCL[counter]->SetTitle(Form("HT%i",trig));
      //      else if (trig == 3 && ptbin == 1)
      //        INCL[counter]->SetTitle("MB");
      //      else
      Had[counter]->GetYaxis()->SetTitle("Counts");
      sprintf(buf,"%1.1f<#it{p}_{T}<%1.1f",anaConst::lpt[ptbin], anaConst::hpt[ptbin]);
      
      TLegend* legg = new TLegend(0.58,0.8,0.97,0.96);
      legg->SetFillStyle (0);
      legg->SetFillColor (0);
      legg->SetBorderSize(0);
      legg->AddEntry(INCL[counter],"(Semi-INCL electrons)-h", "l");
      legg->AddEntry(Had[counter],"Hadrons-h", "l");
      
      Had[counter]->SetTitle("");
      Had[counter]->SetLineColor(kMagenta);
      Had[counter]->SetLineWidth(1);
      //      if(num < 4){
      Had[counter]->GetYaxis()->SetRangeUser(0, Had[counter]->GetMaximum()+150);

      Had[counter]->Draw("hist");
      INCL[counter]->Draw("same hist");
      if(num == 1)legg->Draw("same");
      drawLatex(0.2,0.91,buf,62,0.04,1);
      //      }
      //      else {
      c[0]->cd(3+num);
      if(num == 1) gPad->SetLeftMargin(0.12);

//      gPad->SetBottomMargin(0);
//      gPad->SetTopMargin(0);

      USIM[counter]->GetYaxis()->SetNdivisions(504);

      USIM[counter]->SetLineColor(kBlue);
      USIM[counter]->SetLineWidth(1);
      USIM[counter]->GetXaxis()->SetTitle("#Delta#phi_{eh}(rad)");
      USIM[counter]->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
      USIM[counter]->GetYaxis()->SetRangeUser(0, USIM[counter]->GetMaximum()+100);
      //      if(ptbin == 0)
      //        USIM[counter]->SetTitle("Photonic Electron Reconstruction");
      //      else if (ptbin == 1 && trig !=3)
      //        USIM[counter]->SetTitle(Form("HT%i",trig));
      //      else if (trig == 3 && ptbin == 1)
      //        USIM[counter]->SetTitle("MB");
      //      else
      USIM[counter]->SetTitle("");
      USIM[counter]->GetYaxis()->SetTitle("Counts");
      USIM[counter]->Draw("hist same");
      
      LSIM[counter]->SetLineColor(kRed);
      LSIM[counter]->SetLineWidth(1);
      LSIM[counter]->Draw("hist same");
      
      // Subtraction of (US-LS)
      TH1F *SUB = (TH1F*)USIM[counter]->Clone(); //
      SUB->SetName("Subtraction");      // Create SUB as a clone of USIM
      SUB->Add(LSIM[counter],-1);
      SUB->SetLineColor(kGreen+2);
      SUB->SetLineWidth(1);
      //      SUB->SetFillStyle(3001);
      //      SUB->SetFillColor(kBlue);
      SUB->Draw("hist same");
      
      TLegend* leg = new TLegend(0.6,0.75,0.93,0.93);
      leg->SetFillStyle (0);
      leg->SetFillColor (0);
      leg->SetBorderSize(0);
      leg->AddEntry(USIM[counter],"(ULS electrons)-h","l");
      leg->AddEntry(LSIM[counter],"(LS electrons)-h", "l");
      leg->AddEntry(SUB,"(ULS-LS electrons)-h", "l");
      if(num == 1)leg->Draw("same");
      drawLatex(0.2,0.91,buf,62,0.04,1);
      //      }
      //      INCL[counter]->Draw("hist");
      
      c[0]->Update();
    }
  }
  c[0]->Print("pl_delPhiAll.pdf","pdf");
  // Close ROOT File
  //f->Close();
  //delete f;
  
  // Make PDF if Desired
  //c1->Print("c1.pdf","pdf");
}

//=================================================================================

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize,    Int_t colorIndex){
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  // latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
  
}
