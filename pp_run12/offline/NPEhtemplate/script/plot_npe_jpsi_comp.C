TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t   textAngle=0);

void plot_npe_jpsi(){
  // Open ROOT File
  gROOT->ProcessLine(".x ~/myStyle.C");
//  gROOT->SetBatch(kTRUE); // sets batch mode, so don't draw canvas
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  bool doNorm = false;
  const Int_t numPtBins = 9;
  TH1D* projData0[numPtBins];
  TH1D* projData2[numPtBins];
  TH1D* pileupCorrect[numPtBins][2];
  TH2F* histoNorms;
  TH1D *hdPhiRawce[14];
  TH1D *hdPhiRawbe[14];
  TH1D *hEventTallyce[14];
  TH1D *hEventTallybe[14];
  TH1D *hdPhiRawceSym[14];
  TH1D *hdPhiRawbeSym[14];
  TH1D* projDataHF[numPtBins];
  
  Float_t lowpt[14] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 5.5, 15.5};
  Float_t highpt[14] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 5.5, 15.5, 18.5};
  
  Float_t low[] = {0, 0, 0, 0, 0, -0.1, -0.1, -0.1, -0.1};
  Float_t high[] = {0.135, 0.135, 0.135, 0.2, 0.2, 0.2, 1.6, 1.6, 1.6};
  
  Float_t promptJpsi[] = {0.12, 0.12, 0.1, 0.06, 0.05, 0.035, 0.035, 0.28643, 0.28643};
  Float_t norms[] = {0, 0, 0, 0, 0, 0};
  Float_t normhf[] = {0, 0, 0, 0, 0, 0};

  char name[1000];
  char label[100];
  TFile *fD = new TFile("FFOutput/npe_tree_May5_processed_default.root","READ");
  histoNorms  = (TH2F*)fD->Get("histoNorms");
  
  TFile *fJpsi = new TFile("/Users/zhouyingjie/Local/PWG/btoe/pp_run12/sim/offline/Jpsi_sys/rootfile/Jpsie_Octet.root","READ");
  //============================================================================
  
  Double_t norm0,norm2;
  for(Int_t ptbin=0; ptbin<6; ptbin++){
    projData0[ptbin]= (TH1D*)fD->Get(Form("NPEhDelPhi_0_%i",ptbin));
    projData2[ptbin]= (TH1D*)fD->Get(Form("NPEhDelPhi_2_%i",ptbin));
    
    pileupCorrect[ptbin][0] = (TH1D*)fD->Get(Form("pileupCorrection_%i_0",ptbin));
    pileupCorrect[ptbin][1] = (TH1D*)fD->Get(Form("pileupCorrection_%i_2",ptbin));
    
    norm0 = histoNorms->GetBinContent(histoNorms->GetBin(1,ptbin+1));
    norm2 = histoNorms->GetBinContent(histoNorms->GetBin(3,ptbin+1));
    
    if(ptbin<2) projDataHF[ptbin] = (TH1D* )projData0[ptbin]->Clone(Form("projDataHF_%d", ptbin));
    else projDataHF[ptbin] = (TH1D* )projData2[ptbin]->Clone(Form("projDataHF_%d", ptbin));
    
    if(doNorm){
      projData0[ptbin] -> Scale(1./norm0);
      projData2[ptbin] -> Scale(1./norm2);
      
      projData0[ptbin]->Add(pileupCorrect[ptbin][0],-1);
      projData2[ptbin]->Add(pileupCorrect[ptbin][1],-1);
    }
 
//    projData0[ptbin] ->Draw();
//    return ;
    if(ptbin <2)norms[ptbin] = promptJpsi[ptbin]*norm0;
    else norms[ptbin] = promptJpsi[ptbin]*norm2;
    
    if(ptbin <2)normhf[ptbin] = (1.-promptJpsi[ptbin])*norm0;
    else normhf[ptbin] =(1.-promptJpsi[ptbin])*norm2;
  }
  //============================================================================

  TCanvas *c = new TCanvas("c","template Hists");
//  c->Divide(3, 2, 0, 0, 0);
  c->Divide(3, 2);
  
  for(auto i = 0; i<6; i++){
    hdPhiRawce[i] = (TH1D* )fJpsi->Get(Form("hdPhiRawce_%i", i));
    hdPhiRawbe[i] = (TH1D* )fJpsi->Get(Form("hdPhiRawbe_%i", i));
    hEventTallyce[i] = (TH1D* )fJpsi->Get(Form("ceEventTally_%i",i));
    hEventTallybe[i] = (TH1D* )fJpsi->Get(Form("beEventTally_%i",i));
    
    hdPhiRawceSym[i] = new TH1D(Form("hdPhiRawceormSys_%i", i), "", 100, -TMath::Pi(), TMath::Pi());
    hdPhiRawbeSym[i] = new TH1D(Form("hdPhiRawbeormSys_%i", i), "", 100, -TMath::Pi(), TMath::Pi());
    
    hdPhiRawceSym[i]->Sumw2(0);
    hdPhiRawbeSym[i]->Sumw2(0);
    
    for(auto j = 0; j<hdPhiRawce[i]->GetNbinsX(); j++){
      Double_t cn = hdPhiRawce[i]->GetBinContent(j+1);
      Double_t cns = hdPhiRawce[i]->GetBinContent(100-j);
      hdPhiRawceSym[i]->SetBinContent(j+1, cns);
      
      Double_t bn = hdPhiRawbe[i]->GetBinContent(j+1);
      Double_t bns = hdPhiRawbe[i]->GetBinContent(100-j);
      hdPhiRawbeSym[i]->SetBinContent(j+1, bns);
    }
    
    hdPhiRawceSym[i]->Sumw2(1);
    hdPhiRawbeSym[i]->Sumw2(1);
    
    hdPhiRawceSym[i]->Add(hdPhiRawce[i], 1);
    hdPhiRawbeSym[i]->Add(hdPhiRawbe[i], 1);
    
    hdPhiRawceSym[i]->Scale(0.5);
    hdPhiRawbeSym[i]->Scale(0.5);
    
    if(hEventTallyce[i]->GetBinContent(1))hdPhiRawceSym[i]->Scale(1./hEventTallyce[i]->GetBinContent(1));
    if(hEventTallybe[i]->GetBinContent(1))hdPhiRawbeSym[i]->Scale(1./hEventTallybe[i]->GetBinContent(1));
    
    hdPhiRawce[i] = (TH1D* )hdPhiRawceSym[i]->Clone("hdPhiRawceSym_ag");
    hdPhiRawbe[i] = (TH1D* )hdPhiRawbeSym[i]->Clone("hdPhiRawbeSym_ag");
    
    hdPhiRawce[i]->Scale(norms[i]);
    //============================================================================
    
    projDataHF[i]->Add(hdPhiRawce[i], -1);
    
    if(doNorm) projDataHF[i]->Scale(1./normhf[i]);
    if(doNorm) hdPhiRawce[i]->Scale(1./norms[i]);
    
    //============================================================================
    
    c->cd(i+1);
    hdPhiRawce[i]->SetLineStyle(1);
    hdPhiRawce[i]->SetLineColor(kRed);

    projData0[i]->SetLineStyle(1);
    projData2[i]->SetLineStyle(1);
    projData0[i]->SetLineColor(kGreen+1);
    projData2[i]->SetLineColor(kGreen+1);
    
    projDataHF[i]->SetLineStyle(1);
    projDataHF[i]->SetLineColor(kBlue);
    
//    hdPhiRawce[i]->GetYaxis()->SetRangeUser(0, projData2[i]->GetBinContent(projData2[i]->FindBin(0.1))*1.3);
//    hdPhiRawce[i]->GetYaxis()->SetRangeUser(0, projData0[0]->GetBinContent(projData0[0]->FindBin(0.1))*1.3);
    if(i<3)hdPhiRawce[i]->GetYaxis()->SetRangeUser(0, 2000);
    else hdPhiRawce[i]->GetYaxis()->SetRangeUser(0, 800);
    
    if(doNorm) hdPhiRawce[i]->GetYaxis()->SetRangeUser(0, 0.3);

    hdPhiRawce[i]->Draw("hist");
    if(i<2) projData0[i]->Draw("hist ][ same");
    else projData2[i]->Draw("hist ][ same");
    projDataHF[i]->Draw("hist ][ same");

    auto leg = new TLegend(0.55,0.7,0.9,0.9);
    leg->SetTextSize(0.05);
    leg->SetFillStyle (0);
    leg->SetFillColor (0);
    leg->SetBorderSize(0);
    leg->AddEntry(projData0[i],"inclusive e-h","l");
    leg->AddEntry(projDataHF[i],"hf#rightarrow e-h","l");
    leg->AddEntry(hdPhiRawce[i],"pormpt J/#psi#rightarrow e-h","l");
    leg->Draw("same");
    
    sprintf(label,"#it{p}_{T}#in [%1.1f,%1.1f] GeV/c",lowpt[i],highpt[i]);
    drawLatex(0.15, 0.8, label, 22, 0.05, 1);
    c->Update();
  }
  
  const char *FileName = "templ_npe_jpsi_oct_ht02";
  TCanvas* temp = new TCanvas();
  sprintf(name, "Plots/%s.pdf[", FileName);
  temp->Print(name);
  
  temp = c;
  temp->Print(name);
  
  sprintf(name, "Plots/%s.pdf]", FileName);
  temp->Print(name);
  
}

TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t   textAngle=0)
{
  TLatex *latex = new TLatex(x,y,text.Data());
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->SetTextAngle(textAngle);
  latex->Draw("same");
  return latex;
}
