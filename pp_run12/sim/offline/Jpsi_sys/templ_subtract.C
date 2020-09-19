TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t   textAngle=0);

void templ_subtract(const char* FileName="hf", const char* FileName2="Lc")
{
  
  // Open ROOT File
  gROOT->SetBatch(kTRUE); // sets batch mode, so don't draw canvas
  //  gStyle->SetOptStat(0);
  gStyle->SetOptStat(111111);
  // Set Style parameters for this macro
  gStyle->SetOptTitle(1);
  
  const char* PdfFileName= "templ_Subtract";
  
  char name[1000];
  sprintf(name, "rootfile/%s.root", FileName);
  TFile *fpy = new TFile(name,"READ");
  
  sprintf(name, "rootfile/%s.root", FileName2); // be subtracted
  TFile *fpy2 = new TFile(name,"READ");
  
  char label[100];
  TLatex lat1;
  Float_t lowpt[14] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5};
  Float_t highpt[14] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 18.5};
  Float_t low[] = {0, 0, 0, 0, 0, 0, 0, 0, 0,};

//  Float_t low[] = {0, 0, 0, 0, 0, -0.1, -0.15, -0.4, -0.3};
  Float_t high[] = {0.22, 0.22, 0.22, 0.32, 0.32, 0.32, 0.5, 0.5, 0.5};
//  Float_t high[] = {0.3, 0.32, 0.32, 0.45, 0.47, 0.6, 1, 2, 1.6};
  
  TH1D *hdPhiRawce[14];
  TH1D *hdPhiRawbe[14];
  TH1D *hdPhiRawceSym[14];
  TH1D *hdPhiRawbeSym[14];
  
  TH1D *hEventTallyce[14];
  TH1D *hEventTallybe[14];
  
  TH1D *h2dPhiRawce[14];
  TH1D *h2dPhiRawbe[14];
  TH1D *h2EventTallyce[14];
  TH1D *h2EventTallybe[14];
    
  TCanvas *c = new TCanvas("c","Pythia B/C Hists");
  c->Divide(3, 3);
  
  for(int i=0; i<9; i++){
    hdPhiRawce[i] = (TH1D* )fpy->Get(Form("hdPhiRawce_%i", i));
    hdPhiRawbe[i] = (TH1D* )fpy->Get(Form("hdPhiRawbe_%i", i));
    hEventTallyce[i] = (TH1D* )fpy->Get(Form("ceEventTally_%i",i));
    hEventTallybe[i] = (TH1D* )fpy->Get(Form("beEventTally_%i",i));
    
    h2dPhiRawce[i] = (TH1D* )fpy2->Get(Form("hdPhiRawce_%i", i));
    h2dPhiRawbe[i] = (TH1D* )fpy2->Get(Form("hdPhiRawbe_%i", i));
    h2EventTallyce[i] = (TH1D* )fpy2->Get(Form("ceEventTally_%i",i));
    h2EventTallybe[i] = (TH1D* )fpy2->Get(Form("beEventTally_%i",i));
    
    hdPhiRawce[i]->Add(h2dPhiRawce[i], -1);
    hdPhiRawbe[i]->Add(h2dPhiRawbe[i], -1);
    hEventTallyce[i]->Add(h2EventTallyce[i], -1);
    hEventTallybe[i]->Add(h2EventTallybe[i], -1);
  }
  
  for(int i = 0; i<9; i++){
    hdPhiRawceSym[i] = new TH1D(Form("hdPhiRawceormSys_%i", i), "", 100,-TMath::Pi(),TMath::Pi());
    hdPhiRawbeSym[i] = new TH1D(Form("hdPhiRawbeormSys_%i", i), "", 100,-TMath::Pi(),TMath::Pi());
    //    hdPhiRawceSym[i] = new TH1D(Form("hdPhiRawceormSys_%i", i), "", 100,-3.14,3.14);
    //       hdPhiRawbeSym[i] = new TH1D(Form("hdPhiRawbeormSys_%i", i), "", 100,-3.14,3.14);
    //    hdPhiRawceSym[i]->Sumw2();
    //    hdPhiRawbeSym[i]->Sumw2();
    hdPhiRawceSym[i]->Sumw2(0); // ensure this hist don't have error
    hdPhiRawbeSym[i]->Sumw2(0);
    
    
    for(auto j = 0; j<hdPhiRawce[i]->GetNbinsX(); j++){
      //      if(j==0) cout<<hdPhiRawce[i]->GetBinContent(1)<<"  "<<hdPhiRawbe[i]->GetBinContent(1)<<endl;
      //for(auto j = 0; j<105; j++){
      
      Double_t cn = hdPhiRawce[i]->GetBinContent(j+1);
      Double_t cns = hdPhiRawce[i]->GetBinContent(100-j);
      //cout<<"  charm  "<<cns<<"    "<<cn<<"    "<<(cn+cns)/2.<<endl;
      //hdPhiRawce[i]->SetBinContent(j+1, (cn+cns)/2.);
      
      hdPhiRawceSym[i]->SetBinContent(j+1, cns);
      //hdPhiRawceSym[i]->SetBinContent(j+1, (cn+cns)/2.);
      
      Double_t bn = hdPhiRawbe[i]->GetBinContent(j+1);
      Double_t bns = hdPhiRawbe[i]->GetBinContent(100-j);
      //cout<<bn<<" bottom  "<<bns<<endl;
      //hdPhiRawbe[i]->SetBinContent(j+1, (bn+bns)/2.);
      hdPhiRawbeSym[i]->SetBinContent(j+1, bns);
      //hdPhiRawbeSym[i]->SetBinContent(j+1, (bn+bns)/2.);
    }
    
    hdPhiRawceSym[i]->Sumw2(1);
    hdPhiRawbeSym[i]->Sumw2(1);
    
    hdPhiRawceSym[i]->Add(hdPhiRawce[i], 1);
    hdPhiRawbeSym[i]->Add(hdPhiRawbe[i], 1);
    
    hdPhiRawceSym[i]->Scale(0.5);
    hdPhiRawbeSym[i]->Scale(0.5);
    
    
    
    if(hEventTallyce[i]->GetBinContent(1))hdPhiRawceSym[i]->Scale(1./hEventTallyce[i]->GetBinContent(1));
    if(hEventTallybe[i]->GetBinContent(1))hdPhiRawbeSym[i]->Scale(1./hEventTallybe[i]->GetBinContent(1));
    
    //
    hdPhiRawce[i] = (TH1D* )hdPhiRawceSym[i]->Clone("hdPhiRawceSym_ag");
    hdPhiRawbe[i] = (TH1D* )hdPhiRawbeSym[i]->Clone("hdPhiRawbeSym_ag");
    
    
    c->cd(i+1);
    hdPhiRawce[i]->SetLineColor(kBlack);
    hdPhiRawce[i]->GetXaxis()->SetTitle("#Delta#phi_{eh}");
    hdPhiRawce[i]->GetYaxis()->SetTitle("#frac{1}{N}#frac{dN}{d(#Delta#phi)}");
    //hdPhiRawce[i]->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
    
    //    high[i] = hdPhiRawbe[i]->GetMaximum()*1.1;
    //    if(i == 0)high[i] = hdPhiRawce[i]->GetMaximum()*1.1;
    hdPhiRawce[i]->GetXaxis()->SetRangeUser(-3.5, 3.5);
    hdPhiRawce[i]->GetYaxis()->SetRangeUser(low[i], high[i]);
    hdPhiRawce[i]->SetMarkerStyle(20);
    hdPhiRawbe[i]->SetMarkerStyle(21);
    hdPhiRawbe[i]->SetMarkerSize(0.6);
    hdPhiRawce[i]->SetMarkerSize(0.6);
    
    
//    cout<<hdPhiRawce[i]->Integral()<<"  -  "<<endl;
    hdPhiRawce[i]->Draw("PE");
    hdPhiRawbe[i]->SetLineColor(kRed);
    hdPhiRawbe[i]->SetMarkerColor(kRed);
    hdPhiRawbe[i]->Draw("same PE");
    
    //TLegend* leg = new TLegend(0.4,0.7,0.75,0.85);
    TLegend* leg = new TLegend(0.65,0.7,0.88,0.85);
    leg->SetBorderSize(0);
    
    leg->AddEntry(hdPhiRawbe[i],"b#bar{b}#rightarrow NPE", "lp");
    leg->AddEntry(hdPhiRawce[i],"c#bar{c}#rightarrow NPE","lp");
    //    leg->Draw("same");
    
    if(i == 0)
      hdPhiRawce[i]->SetTitle("Pythia e/b-h correlation");
    else
      hdPhiRawce[i]->SetTitle("");
    
    sprintf(label,"#it{p}_{T}#in [%1.1f,%1.1f] GeV/c",lowpt[i],highpt[i]);
    if(i <5) lat1.DrawLatex(-3, 0.03,label);
    if(i >4) lat1.DrawLatex(-3, -0.05,label);
    //    lat1.DrawLatex(-2.5,0.03,label);
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

