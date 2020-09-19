TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t   textAngle=0);

void templComp_py8HQ_py8(const char* FileName="pythia_npe_tree_May18", const char* FileName2="oldHQ")
{
  
  // Open ROOT File
  gROOT->ProcessLine(".x ~/myStyle.C");
  gROOT->SetBatch(kTRUE); // sets batch mode, so don't draw canvas
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  const char* PdfFileName= "templComp_py8HQ_py8";
  char name[1000];
  sprintf(name, "input/%s.root", FileName);
  TFile *fpy = new TFile(name,"READ");
  sprintf(name, "input/%s.root", FileName2);
  TFile *fpy2 = new TFile(name,"READ"); // new CR code
  
  char label[100];
  TLatex lat1;
  Float_t lowpt[14] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 5.5, 15.5};
  Float_t highpt[14] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 5.5, 15.5, 18.5};
  
  //  Float_t lowpt[5] = {0, 2, 4, 6, 8};
  //  Float_t highpt[5] = {2, 4, 6, 8, 12};
  
  //Float_t low[] = {0, 0, 0, 0, 0, -0.1, -0.15, -0.4, -0.3};
  Float_t low[] = {0, 0, 0, 0, 0, -0.1, -0.1, -0.1, -0.1};
  
  //  Float_t high[] = {0.3, 0.32, 0.32, 0.45, 0.47, 0.6, 1, 2, 1.6};
  //  Float_t high[] = {0.35, 0.35, 0.35, 0.6, 0.6, 0.6, 1.6, 1.6, 1.6};
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
  
  TCanvas *c = new TCanvas("c","Pythia B/C Hists",150,0,1100,900);
  c->Divide(3, 2, 0, 0, 0);
  //  c->Divide(3, 3);
  
  
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
    
    
    h2dPhiRawce[i] = (TH1D* )h2dPhiRawceSym[i]->Clone("h2dPhiRawceSym_ag");
    h2dPhiRawbe[i] = (TH1D* )h2dPhiRawbeSym[i]->Clone("h2dPhiRawbeSym_ag");
    
    //============================================================================
    
    hdPhiRawce[i]->Scale(1, "width");
    hdPhiRawbe[i]->Scale(1, "width");
    h2dPhiRawce[i]->Scale(1, "width");
    h2dPhiRawbe[i]->Scale(1, "width");
    
    c->cd(i+1);
    hdPhiRawce[i]->SetLineColor(kBlack);
    hdPhiRawce[i]->GetXaxis()->SetTitle("#Delta#phi_{eh}");
    hdPhiRawce[i]->GetYaxis()->SetTitle("#frac{1}{N}#frac{dN}{d(#Delta#phi)}");
    
    hdPhiRawce[i]->SetMarkerStyle(24);
    hdPhiRawbe[i]->SetMarkerStyle(24);
//    hdPhiRawbe[i]->SetMarkerSize(0.6);
//    hdPhiRawce[i]->SetMarkerSize(0.6);
    
    
    hdPhiRawce[i]->GetYaxis()->SetRangeUser(low[i], 5);
    
    hdPhiRawce[i]->Draw("PE");
    hdPhiRawbe[i]->SetLineColor(kRed);
    hdPhiRawbe[i]->SetMarkerColor(kRed);
    hdPhiRawbe[i]->Draw("same PE");
    
    h2dPhiRawbe[i]->SetLineColor(kRed);
//    h2dPhiRawce[i]->SetLineColor(kGreen+1);
//    h2dPhiRawbe[i]->SetLineColor(kRed);

    TLegend* leg5 = new TLegend(0.2,0.7,0.5,0.85);
    leg5->SetBorderSize(0);
    leg5->AddEntry(h2dPhiRawbe[i],"b#bar{b}#rightarrow e, HQ", "l");
    leg5->AddEntry(h2dPhiRawce[i],"c#bar{c}#rightarrow e, HQ","l");
    h2dPhiRawce[i]->Draw("same hist ][");
    h2dPhiRawbe[i]->Draw("same hist ][");
    leg5->Draw("same");
    
    TLegend* leg = new TLegend(0.65,0.7,0.88,0.85);
    leg->SetBorderSize(0);
    leg->AddEntry(hdPhiRawbe[i],"b#bar{b}#rightarrow e, MB", "p");
    leg->AddEntry(hdPhiRawce[i],"c#bar{c}#rightarrow e, MB","p");
    leg->Draw("same");
    
    if(i == 0)
      hdPhiRawce[i]->SetTitle("Pythia e/b-h correlation");
    else
      hdPhiRawce[i]->SetTitle("");
    
    sprintf(label,"#it{p}_{T}#in [%1.1f,%1.1f] GeV/c",lowpt[i],highpt[i]);
    if(i <5) lat1.DrawLatex(-3, 0.03,label);
    if(i >4) lat1.DrawLatex(-3, -0.05,label);
    c->Update();
  }
  
  TCanvas* temp = new TCanvas();
  sprintf(name, "pic/%s.pdf[", PdfFileName);
  temp->Print(name);
  
  temp = c;
  temp->Print(name);
  
  sprintf(name, "pic/%s.pdf]", PdfFileName);
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
