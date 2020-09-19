TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t   textAngle=0);
void templ_jpsi_h(const char* FileName="Jpsi_Singlet_test", const char* FileName2="Jpsi_Octet_y")
{
  
  // Open ROOT File
    gROOT->ProcessLine(".x ~/myStyle.C");
  gROOT->SetBatch(kTRUE); // sets batch mode, so don't draw canvas
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  char name[1000];
  sprintf(name, "rootfile/%s.root", FileName);
  TFile *fpy = new TFile(name,"READ");
  sprintf(name, "rootfile/%s.root", FileName2);
  TFile *fpy2 = new TFile(name,"READ"); // new CR code
  
  char label[100];
  TLatex lat1;
  //  Float_t lowpt[5] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 5.5, 15.5};
  //  Float_t highpt[5] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 5.5, 15.5, 18.5};
  
  Float_t lowpt[5] = {0, 2, 4, 6, 8};
  Float_t highpt[5] = {2, 4, 6, 8, 12};
  
  //Float_t low[] = {0, 0, 0, 0, 0, -0.1, -0.15, -0.4, -0.3};
  Float_t low[] = {0, 0, 0, 0, 0, -0.1, -0.1, -0.1, -0.1};
  
  //  Float_t high[] = {0.3, 0.32, 0.32, 0.45, 0.47, 0.6, 1, 2, 1.6};
  //  Float_t high[] = {0.35, 0.35, 0.35, 0.6, 0.6, 0.6, 1.6, 1.6, 1.6};
  Float_t high[] = {0., 0.12, 0.12, 0.2, 0.2, 0.2, 1.6, 1.6, 1.6};
  
  
  TH1D *hdPhiRawce[5];
  TH1D *hdPhiRawbe[5];
  TH1D *hEventTallyce[5];
  TH1D *hEventTallybe[5];
  TH1D *hdPhiRawceSym[5];
  TH1D *hdPhiRawbeSym[5];
  
  TH1D *h2dPhiRawce[5];
  TH1D *h2dPhiRawbe[5];
  TH1D *h2EventTallyce[5];
  TH1D *h2EventTallybe[5];
  TH1D *h2dPhiRawceSym[5];
  TH1D *h2dPhiRawbeSym[5];
  
  TCanvas *c = new TCanvas("c","Pythia B/C Hists",150,0,1100,900);
  c->Divide(3, 2, 0, 0, 0);
  //  c->Divide(3, 3);
  
  
  for(int i=0; i<5; i++){
    
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
    
    if(hEventTallyce[i]->GetBinContent(1))hdPhiRawceSym[i]->Scale(1./hEventTallyce[i]->GetBinContent(1));
    if(hEventTallybe[i]->GetBinContent(1))hdPhiRawbeSym[i]->Scale(1./hEventTallybe[i]->GetBinContent(1));
    
    //    hdPhiRawceSym[i]->Write();
    //    hdPhiRawbeSym[i]->Write();
    
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
    
    if(h2EventTallyce[i]->GetBinContent(1))h2dPhiRawceSym[i]->Scale(1./h2EventTallyce[i]->GetBinContent(1));
    if(h2EventTallybe[i]->GetBinContent(1))h2dPhiRawbeSym[i]->Scale(1./h2EventTallybe[i]->GetBinContent(1));
    
    //    hdPhiRawceSym[i]->Write();
    //    hdPhiRawbeSym[i]->Write();
    
    h2dPhiRawce[i] = (TH1D* )h2dPhiRawceSym[i]->Clone("h2dPhiRawceSym_ag");
    h2dPhiRawbe[i] = (TH1D* )h2dPhiRawbeSym[i]->Clone("h2dPhiRawbeSym_ag");
    
    //============================================================================
    
    
    c->cd(i+1);
    hdPhiRawce[i]->SetLineColor(kBlack);
    hdPhiRawce[i]->GetXaxis()->SetTitle("#Delta#phi_{J/#psi-h}");
    hdPhiRawce[i]->GetYaxis()->SetTitle("#frac{1}{N_{J/#psi}}#frac{dN}{d(#Delta#phi)}");
    hdPhiRawce[i]->GetXaxis()->SetRangeUser(-3.5, 3.5);
    
    hdPhiRawce[i]->Scale(1, "width");
    hdPhiRawbe[i]->Scale(1, "width");
    h2dPhiRawce[i]->Scale(1, "width");
    
    //    auto tmp = hdPhiRawbe[i]->GetBinContent(hdPhiRawbe[i]->FindBin(0))*1.3;
    auto tmp = hdPhiRawce[i]->GetBinContent(hdPhiRawce[i]->FindBin(3.1))*1.3;
    low[i] =hdPhiRawce[i]->GetBinContent(hdPhiRawce[i]->FindBin(0))*0.02;
    //    if(i > 4) low[i] =hdPhiRawce[i]->GetBinContent(hdPhiRawce[i]->FindBin(0))*-1.4;
    low[i]=0;
    if(i<3){tmp=3.1;}
    else tmp=6;
    hdPhiRawce[i]->GetYaxis()->SetRangeUser(low[i], tmp);
    
    //    if(i > 5) tmp = hdPhiRawbe[i]->GetBinContent(hdPhiRawce[i]->FindBin(-3))*2.1;
    
    //    hdPhiRawce[i]->SetMarkerStyle(20);
    //    hdPhiRawbe[i]->SetMarkerStyle(21);
    //    hdPhiRawbe[i]->SetMarkerSize(0.6);
    //    hdPhiRawce[i]->SetMarkerSize(0.6);
    ////    hdPhiRawbe[i]->SetMarkerSize(0.5);
    ////    hdPhiRawce[i]->SetMarkerSize(0.5);
    //
    //    h2dPhiRawce[i]->SetMarkerStyle(24);
    //    h2dPhiRawbe[i]->SetMarkerStyle(25);
    //    h2dPhiRawbe[i]->SetMarkerSize(0.6);
    //    h2dPhiRawce[i]->SetMarkerSize(0.6);
    ////    h2dPhiRawbe[i]->SetMarkerSize(0.5);
    ////    h2dPhiRawce[i]->SetMarkerSize(0.5);
    hdPhiRawce[i]->SetLineStyle(2);
    h2dPhiRawce[i]->SetLineStyle(2);
    
    
    
    
    //    if(i == 0)cout<<"integrated over dphi"<<endl;
    //    cout<<hdPhiRawce[i]->Integral()<<endl;
    hdPhiRawce[i]->SetLineColor(kGreen+1);
    hdPhiRawce[i]->SetMarkerColor(kGreen+1);
    hdPhiRawce[i]->Draw("l");
    hdPhiRawbe[i]->SetLineColor(kRed);
    hdPhiRawbe[i]->SetMarkerColor(kRed);
    //    hdPhiRawbe[i]->Draw("same PE");
    
    //    h2dPhiRawbe[i]->Draw("same PE");
    h2dPhiRawce[i]->SetLineColor(kBlue);
    h2dPhiRawce[i]->SetMarkerColor(kBlue);
    h2dPhiRawce[i]->Draw("l same");
    //    h2dPhiRawbe[i]->SetLineColor(kRed);
    //    h2dPhiRawbe[i]->SetMarkerColor(kRed);
    
    TLegend* leg = new TLegend(0.55,0.7,0.84,0.85);
    leg->SetFillStyle (0);
    leg->SetFillColor (0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.05);
    //    leg->AddEntry(hdPhiRawbe[i],"b#bar{b}#rightarrow NPE(Singlet)", "lp");
    leg->AddEntry(hdPhiRawce[i],"c#bar{c}#rightarrow NPE(Singlet)","lp");
    leg->Draw("same");
    
    drawLatex(0.18, 0.6, "#it{p}_{T}^{h} > 0.5", 22, 0.05, 1);
//    drawLatex(0.18, 0.52, "|#eta_{J/#psi}| <0.7", 22, 0.05, 1);
    drawLatex(0.18, 0.52, "|y_{J/#psi}| < 1.", 22, 0.05, 1);

    drawLatex(0.18, 0.44, "|#eta_{h}| <1", 22, 0.05, 1);
    drawLatex(0.18, 0.36, "J/#psi#rightarrow e^{-}e^{+}, |#eta_{e}| <1.", 22, 0.05, 1);

    TLegend* leg2 = new TLegend(0.14,0.7,0.4,0.85);
    leg2->SetFillStyle (0);
    leg2->SetFillColor (0);
    leg2->SetBorderSize(0);
    leg2->SetTextSize(0.05);
    //    leg2->AddEntry(h2dPhiRawbe[i],"b#bar{b}#rightarrow NPE(new tune)", "lp");
    leg2->AddEntry(h2dPhiRawce[i],"c#bar{c}#rightarrow NPE(Octet)","lp");
    leg2->Draw("same");
    
    if(i == 0)
      hdPhiRawce[i]->SetTitle("Pythia e/b-h correlation");
    else
      hdPhiRawce[i]->SetTitle("");
    
    sprintf(label,"#it{p}_{T}^{J/#psi}#in [%1.1f,%1.1f] GeV/c",lowpt[i],highpt[i]);
    if(i <5) lat1.DrawLatex(-3, 0.2,label);
//    if(i >4) lat1.DrawLatex(-3, 0.3,label);
    c->Update();
    
  }
  
  TCanvas* temp = new TCanvas();
  sprintf(name, "pic/%s_comp_%s.pdf[", FileName, FileName2);
  temp->Print(name);
  
  temp = c;
  temp->Print(name);
  
  sprintf(name, "pic/%s_comp_%s.pdf]", FileName, FileName2);
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
