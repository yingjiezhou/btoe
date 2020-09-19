TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t   textAngle=0);

void templ_npe_hf_jpsi()
{
  
  // Open ROOT File
  gROOT->ProcessLine(".x ~/myStyle.C");
  gROOT->SetBatch(kTRUE); // sets batch mode, so don't draw canvas
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  bool doNorm = kFALSE;
  char name[1000];
  TFile *fpy = new TFile("rootfile/npe.root","READ");
  TFile *fpy2 = new TFile("rootfile/hf.root","READ"); // new CR code
  TFile *fpy3 = new TFile("rootfile/jpsi.root","READ"); // new CR code

  char label[100];
  TLatex lat1;
  Float_t lowpt[14] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 5.5, 15.5};
  Float_t highpt[14] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 5.5, 15.5, 18.5};
  
  Float_t low[] = {0, 0, 0, 0, 0, -0.1, -0.1, -0.1, -0.1};
  Float_t high[] = {0.135, 0.135, 0.135, 0.2, 0.2, 0.2, 1.6, 1.6, 1.6};
  
  
  TH1D *hdPhiRawce[14];
  TH1D *hdPhiRawbe[14];
  TH1D *hEventTallyce[14];
  TH1D *hEventTallybe[14];
  TH1D *hdPhiRawceSym[14];
  TH1D *hdPhiRawbeSym[14];
  
  TH1D *h2dPhiRawce[14];
  TH1D *h2dPhiRawbe[14];
  TH1D *h2EventTallyce[14];
  TH1D *h2EventTallybe[14];
  TH1D *h2dPhiRawceSym[14];
  TH1D *h2dPhiRawbeSym[14];
  
  TH1D *h3dPhiRawce[14];
  TH1D *h3dPhiRawbe[14];
  TH1D *h3EventTallyce[14];
  TH1D *h3EventTallybe[14];
  TH1D *h3dPhiRawceSym[14];
  TH1D *h3dPhiRawbeSym[14];
  
  TCanvas *c = new TCanvas("c","Pythia B/C Hists");
//  c->Divide(3, 2, 0, 0, 0);
  c->Divide(3, 2);

  for(int i=0; i<6; i++){
    
    hdPhiRawce[i] = (TH1D* )fpy->Get(Form("hdPhiRawce_%i", i));
    hdPhiRawbe[i] = (TH1D* )fpy->Get(Form("hdPhiRawbe_%i", i));
    hEventTallyce[i] = (TH1D* )fpy->Get(Form("ceEventTally_%i",i));
    hEventTallybe[i] = (TH1D* )fpy->Get(Form("beEventTally_%i",i));
    
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
    
    hdPhiRawbeSym[i]->Add(hdPhiRawceSym[i]);
    
    if(doNorm && hEventTallyce[i]->GetBinContent(1) && hEventTallybe[i]->GetBinContent(1))hdPhiRawbeSym[i]->Scale(1./(hEventTallyce[i]->GetBinContent(1) + hEventTallybe[i]->GetBinContent(1)));
    
    
    hdPhiRawce[i] = (TH1D* )hdPhiRawceSym[i]->Clone("hdPhiRawceSym_ag");
    hdPhiRawbe[i] = (TH1D* )hdPhiRawbeSym[i]->Clone("hdPhiRawbeSym_ag");

    //============================================================================
    
    h2dPhiRawce[i] = (TH1D* )fpy2->Get(Form("hdPhiRawce_%i", i));
    h2dPhiRawbe[i] = (TH1D* )fpy2->Get(Form("hdPhiRawbe_%i", i));
    h2EventTallyce[i] = (TH1D* )fpy2->Get(Form("ceEventTally_%i",i));
    h2EventTallybe[i] = (TH1D* )fpy2->Get(Form("beEventTally_%i",i));
    
    h2dPhiRawceSym[i] = new TH1D(Form("h2dPhiRawceormSys_%i", i), "", 100, -TMath::Pi(), TMath::Pi());
    h2dPhiRawbeSym[i] = new TH1D(Form("h2dPhiRawbeormSys_%i", i), "", 100, -TMath::Pi(), TMath::Pi());
    
    h2dPhiRawceSym[i]->Sumw2(0);
    h2dPhiRawbeSym[i]->Sumw2(0);
    
    for(auto j = 0; j<h2dPhiRawce[i]->GetNbinsX(); j++){
      Double_t cn = h2dPhiRawce[i]->GetBinContent(j+1);
      Double_t cns = h2dPhiRawce[i]->GetBinContent(100-j);
      h2dPhiRawceSym[i]->SetBinContent(j+1, cns);
      
      Double_t bn = h2dPhiRawbe[i]->GetBinContent(j+1);
      Double_t bns = h2dPhiRawbe[i]->GetBinContent(100-j);
      h2dPhiRawbeSym[i]->SetBinContent(j+1, bns);
    }
    
    h2dPhiRawceSym[i]->Sumw2(1);
    h2dPhiRawbeSym[i]->Sumw2(1);
    
    h2dPhiRawceSym[i]->Add(h2dPhiRawce[i], 1);
    h2dPhiRawbeSym[i]->Add(h2dPhiRawbe[i], 1);
    
    h2dPhiRawceSym[i]->Scale(0.5);
    h2dPhiRawbeSym[i]->Scale(0.5);
    
    h2dPhiRawbeSym[i]->Add(h2dPhiRawceSym[i]);
    if(doNorm && h2EventTallyce[i]->GetBinContent(1) && h2EventTallybe[i]->GetBinContent(1))h2dPhiRawbeSym[i]->Scale(1./(h2EventTallyce[i]->GetBinContent(1) + h2EventTallybe[i]->GetBinContent(1)));

//    if(h2EventTallyce[i]->GetBinContent(1))h2dPhiRawceSym[i]->Scale(1./h2EventTallyce[i]->GetBinContent(1));
//    if(h2EventTallybe[i]->GetBinContent(1))h2dPhiRawbeSym[i]->Scale(1./h2EventTallybe[i]->GetBinContent(1));
    
    h2dPhiRawce[i] = (TH1D* )h2dPhiRawceSym[i]->Clone("h2dPhiRawceSym_ag");
    h2dPhiRawbe[i] = (TH1D* )h2dPhiRawbeSym[i]->Clone("h2dPhiRawbeSym_ag");
    //============================================================================
    
    h3dPhiRawce[i] = (TH1D* )fpy3->Get(Form("hdPhiRawce_%i", i));
    h3dPhiRawbe[i] = (TH1D* )fpy3->Get(Form("hdPhiRawbe_%i", i));
    h3EventTallyce[i] = (TH1D* )fpy3->Get(Form("ceEventTally_%i",i));
    h3EventTallybe[i] = (TH1D* )fpy3->Get(Form("beEventTally_%i",i));
    
    h3dPhiRawceSym[i] = new TH1D(Form("h3dPhiRawceormSys_%i", i), "", 100, -TMath::Pi(), TMath::Pi());
    h3dPhiRawbeSym[i] = new TH1D(Form("h3dPhiRawbeormSys_%i", i), "", 100, -TMath::Pi(), TMath::Pi());
    
    h3dPhiRawceSym[i]->Sumw2(0);
    h3dPhiRawbeSym[i]->Sumw2(0);
    
    for(auto j = 0; j<h3dPhiRawce[i]->GetNbinsX(); j++){
      Double_t cn = h3dPhiRawce[i]->GetBinContent(j+1);
      Double_t cns = h3dPhiRawce[i]->GetBinContent(100-j);
      h3dPhiRawceSym[i]->SetBinContent(j+1, cns);
      
      Double_t bn = h3dPhiRawbe[i]->GetBinContent(j+1);
      Double_t bns = h3dPhiRawbe[i]->GetBinContent(100-j);
      h3dPhiRawbeSym[i]->SetBinContent(j+1, bns);
    }
    
    h3dPhiRawceSym[i]->Sumw2(1);
    h3dPhiRawbeSym[i]->Sumw2(1);
    
    h3dPhiRawceSym[i]->Add(h3dPhiRawce[i], 1);
    h3dPhiRawbeSym[i]->Add(h3dPhiRawbe[i], 1);
    
    h3dPhiRawceSym[i]->Scale(0.5);
    h3dPhiRawbeSym[i]->Scale(0.5);
    
//    h3dPhiRawbeSym[i]->Add(h3dPhiRawceSym[i]);

//    if(h3EventTallyce[i]->GetBinContent(1) && h3EventTallybe[i]->GetBinContent(1))h3dPhiRawbeSym[i]->Scale(1./(h3EventTallyce[i]->GetBinContent(1) + h3EventTallybe[i]->GetBinContent(1)));
    
    
    if(doNorm && h3EventTallyce[i]->GetBinContent(1))h3dPhiRawceSym[i]->Scale(1./h3EventTallyce[i]->GetBinContent(1));
    if(doNorm && h3EventTallybe[i]->GetBinContent(1))h3dPhiRawbeSym[i]->Scale(1./h3EventTallybe[i]->GetBinContent(1));
    
    h3dPhiRawce[i] = (TH1D* )h3dPhiRawceSym[i]->Clone("h3dPhiRawceSym_ag");
    h3dPhiRawbe[i] = (TH1D* )h3dPhiRawbeSym[i]->Clone("h3dPhiRawbeSym_ag");
    
    h3dPhiRawbe[i] = (TH1D* )h3dPhiRawce[i]->Clone();
    //============================================================================
    
    
    c->cd(i+1);
//    hdPhiRawce[i]->GetXaxis()->SetTitle("#Delta#phi");
//    hdPhiRawce[i]->GetYaxis()->SetTitle("#frac{1}{N}#frac{dN}{d(#Delta#phi)}");
////    hdPhiRawce[i]->GetYaxis()->SetTitle("N");
//
//    hdPhiRawce[i]->GetXaxis()->SetRangeUser(-3.14, 3.14);
//    hdPhiRawce[i]->GetYaxis()->SetRangeUser(0, h2dPhiRawce[i]->GetBinContent(h2dPhiRawce[i]->FindBin(0))*1.3);
//
//    hdPhiRawce[i]->SetLineStyle(2);
//    h2dPhiRawce[i]->SetLineStyle(2);
//    h3dPhiRawce[i]->SetLineStyle(2);
//    hdPhiRawce[i]->SetLineColor(kGreen+1);
//    hdPhiRawce[i]->SetMarkerColor(kGreen+1);
//    h2dPhiRawce[i]->SetLineColor(kBlue);
//    h2dPhiRawce[i]->SetMarkerColor(kBlue);
//    h3dPhiRawce[i]->SetLineColor(kRed);
//    h3dPhiRawce[i]->SetMarkerColor(kRed);
    
//    hdPhiRawce[i]->Draw("hist ][");
//    h2dPhiRawce[i]->Draw("hist ][same");
//    h3dPhiRawce[i]->Draw("hist ][same");
  //=================================================================
    hdPhiRawbe[i]->GetXaxis()->SetTitle("#Delta#phi");
//    hdPhiRawbe[i]->GetYaxis()->SetTitle("#frac{1}{N}#frac{dN}{d(#Delta#phi)}");
    //    hdPhiRawce[i]->GetYaxis()->SetTitle("N");
    hdPhiRawbe[i]->GetXaxis()->SetRangeUser(-3.14, 3.14);
    hdPhiRawbe[i]->GetYaxis()->SetRangeUser(0, hdPhiRawbe[i]->GetBinContent(hdPhiRawbe[i]->FindBin(3.1))*1.3);
    if(doNorm) hdPhiRawbe[i]->GetYaxis()->SetRangeUser(0, 0.3);

    hdPhiRawbe[i]->SetLineStyle(1);
    h2dPhiRawbe[i]->SetLineStyle(1);
    h3dPhiRawbe[i]->SetLineStyle(1);
    hdPhiRawbe[i]->SetLineColor(kGreen+1);
    hdPhiRawbe[i]->SetMarkerColor(kGreen+1);
    h2dPhiRawbe[i]->SetLineColor(kBlue);
    h2dPhiRawbe[i]->SetMarkerColor(kBlue);
    h3dPhiRawbe[i]->SetLineColor(kRed);
    h3dPhiRawbe[i]->SetMarkerColor(kRed);


    hdPhiRawbe[i]->Draw("hist ][");
    h2dPhiRawbe[i]->Draw("hist ][same");
    h3dPhiRawbe[i]->Draw("hist ][same");
//=================================================================

    TLegend* leg = new TLegend(0.55,0.8,0.84,0.94);
    leg->SetFillStyle (0);
    leg->SetFillColor (0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.05);
//    leg->AddEntry(hdPhiRawce[i],"c#bar{c}#rightarrow NPE","l");
//    leg->AddEntry(h2dPhiRawce[i],"c#bar{c}#rightarrow hf","l");
//    leg->AddEntry(h3dPhiRawce[i],"c#bar{c}#rightarrow J#psi","l");
//
    leg->AddEntry(hdPhiRawbe[i],"NPE-h","l");
    leg->AddEntry(h2dPhiRawbe[i],"hf#rightarrow e-h","l");
    leg->AddEntry(h3dPhiRawbe[i],"prompt J#psi#rightarrow e-h","l");
    leg->Draw("same");
    //=================================================================


//    drawLatex(0.18, 0.44, "|#eta_{h}| <1", 22, 0.05, 1);
//    drawLatex(0.18, 0.36, "J/#psi#rightarrow e^{-}e^{+}, |#eta_{e}| <1.", 22, 0.05, 1);

//    TLegend* leg2 = new TLegend(0.14,0.7,0.4,0.85);
//    leg2->SetFillStyle (0);
//    leg2->SetFillColor (0);
//    leg2->SetBorderSize(0);
//    leg2->SetTextSize(0.05);
//    leg2->AddEntry(h2dPhiRawbe[i],"b#bar{b}#rightarrow NPE(Octet)", "lp");
//    leg2->AddEntry(h2dPhiRawce[i],"c#bar{c}#rightarrow NPE(Octet)","lp");
//    leg2->Draw("same");
    
//    if(i == 0)
//      hdPhiRawce[i]->SetTitle("Pythia e/b-h correlation");
//    else
//      hdPhiRawce[i]->SetTitle("");
    
    sprintf(label,"#it{p}_{T}#in [%1.1f,%1.1f] GeV/c",lowpt[i],highpt[i]);
    drawLatex(0.15, 0.8, label, 22, 0.05, 1);
//    if(i <9) lat1.DrawLatex(-3, 10,label);
    c->Update();
    
  }
  
  const char *FileName = "templ_npe_hf_jpsi_cpb";
  TCanvas* temp = new TCanvas();
  sprintf(name, "pic/%s.pdf[", FileName);
  temp->Print(name);
  
  temp = c;
  temp->Print(name);
  
  sprintf(name, "pic/%s.pdf]", FileName);
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
