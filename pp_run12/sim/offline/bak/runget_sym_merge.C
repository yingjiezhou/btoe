
void AddHist(TH1 *h, TH1 *h2, TH1 *hadd);
void runget_sym_merge(const char* FileName="Feb4")
{
  
  // Open ROOT File
  gROOT->SetBatch(kTRUE); // sets batch mode, so don't draw canvas
  gStyle->SetOptStat(0);
  // Set Style parameters for this macro
  gStyle->SetOptTitle(1);
  
  char name[1000];
  sprintf(name, "input/pythia_npe_tree_%s.root", FileName);
  TFile *fpy = new TFile(name,"READ");
  
  char label[100];
  TLatex lat1;
  Float_t lowpt[14] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5};
  Float_t highpt[14] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 18.5};
  Float_t low[] = {0, 0, 0, 0, 0, -0.1, -0.15, -0.4, -0.3};
  Float_t high[] = {0.3, 0.32, 0.32, 0.45, 0.47, 0.6, 1, 2, 1.6};
  
  TH1D *hdPhiRawce[14];
  TH1D *hdPhiRawbe[14];
  TH1D *hdPhiRawceSym[14];
  TH1D *hdPhiRawbeSym[14];
  
  TH1D *hEventTallyce[14];
  TH1D *hEventTallybe[14];
  
  TFile *fsy = new TFile(Form("pythia_npe_tree_sym_error_%s.root", FileName), "RECREATE");
  
  //TCanvas *c = new TCanvas("c", "c", 800, 800);
  TCanvas *c = new TCanvas("c","Pythia B/C Hists",150,0,1100,900);
  c->Divide(3, 3);
  
  for(int i=0; i<9; i++){
    //for(int i=8; i<9; i++){

    hdPhiRawce[i] = (TH1D* )fpy->Get(Form("hdPhiRawce_%i", i));
    hdPhiRawbe[i] = (TH1D* )fpy->Get(Form("hdPhiRawbe_%i", i));
    hEventTallyce[i] = (TH1D* )fpy->Get(Form("ceEventTally_%i",i));
    hEventTallybe[i] = (TH1D* )fpy->Get(Form("beEventTally_%i",i));
    
//       hdPhiRawceSym[i] = (TH1D* )hdPhiRawce[i]->Clone(Form("hdPhiRawceormSys_%i", i));
//       hdPhiRawbeSym[i] = (TH1D* )hdPhiRawce[i]->Clone(Form("hdPhiRawbeormSys_%i", i));

    hdPhiRawceSym[i] = new TH1D(Form("hdPhiRawceormSys_%i", i), "", 200, -10, 10);
    hdPhiRawbeSym[i] = new TH1D(Form("hdPhiRawbeormSys_%i", i), "", 200, -10, 10);
//    hdPhiRawceSym[i]->Sumw2();
//    hdPhiRawbeSym[i]->Sumw2();
    hdPhiRawceSym[i]->Sumw2(0); // 如果这个不删，后面再调用也没用，会一直用之前的error,
    hdPhiRawbeSym[i]->Sumw2(0);
    
    for(auto j = 0; j<hdPhiRawce[i]->GetNbinsX(); j++){
      //for(auto j = 0; j<105; j++){

      Double_t cn = hdPhiRawce[i]->GetBinContent(j+1);
      Double_t cns = hdPhiRawce[i]->GetBinContent(200-j);
      //cout<<"  charm  "<<cns<<"    "<<cn<<"    "<<(cn+cns)/2.<<endl;
      //hdPhiRawce[i]->SetBinContent(j+1, (cn+cns)/2.);
      
      hdPhiRawceSym[i]->SetBinContent(j+1, cns);
      //hdPhiRawceSym[i]->SetBinContent(j+1, (cn+cns)/2.);
      
      Double_t bn = hdPhiRawbe[i]->GetBinContent(j+1);
      Double_t bns = hdPhiRawbe[i]->GetBinContent(200-j);
      //cout<<bn<<" bottom  "<<bns<<endl;
      //hdPhiRawbe[i]->SetBinContent(j+1, (bn+bns)/2.);
      hdPhiRawbeSym[i]->SetBinContent(j+1, bns);
      //hdPhiRawbeSym[i]->SetBinContent(j+1, (bn+bns)/2.);
    }
    

    hdPhiRawceSym[i]->Add(hdPhiRawce[i], 1);
    hdPhiRawbeSym[i]->Add(hdPhiRawbe[i], 1);
    
    hdPhiRawceSym[i]->Scale(0.5);
    hdPhiRawbeSym[i]->Scale(0.5);

    hdPhiRawceSym[i]->Sumw2(1);
    hdPhiRawbeSym[i]->Sumw2(1);
    
//
//    if(hEventTallyce[i]->GetBinContent(1))hdPhiRawce[i]->Scale(1./hEventTallyce[i]->GetBinContent(1));
//    if(hEventTallybe[i]->GetBinContent(1))hdPhiRawbe[i]->Scale(1./hEventTallybe[i]->GetBinContent(1));
    
    if(hEventTallyce[i]->GetBinContent(1))hdPhiRawceSym[i]->Scale(1./hEventTallyce[i]->GetBinContent(1));
    if(hEventTallybe[i]->GetBinContent(1))hdPhiRawbeSym[i]->Scale(1./hEventTallybe[i]->GetBinContent(1));
    
//    if(hEventTallyce[i]->GetBinContent(1))hdPhiRawce[i]->Scale(1./hEventTallyce[i]->GetBinContent(1));
//    if(hEventTallybe[i]->GetBinContent(1))hdPhiRawbe[i]->Scale(1./hEventTallybe[i]->GetBinContent(1));
    
//    hdPhiRawce[i]->Write(Form("hdPhiRawceormSys_%i", i));
//    hdPhiRawbe[i]->Write(Form("hdPhiRawbeormSys_%i", i));
      hdPhiRawceSym[i]->Write();
      hdPhiRawbeSym[i]->Write();
      
      hdPhiRawce[i] = (TH1D* )hdPhiRawceSym[i]->Clone("hdPhiRawceSym_ag");
      hdPhiRawbe[i] = (TH1D* )hdPhiRawbeSym[i]->Clone("hdPhiRawbeSym_ag");

    
    c->cd(i+1);
    hdPhiRawce[i]->SetLineColor(kBlack);
    hdPhiRawce[i]->GetXaxis()->SetTitle("#Delta#phi_{eh}");
    hdPhiRawce[i]->GetYaxis()->SetTitle("#frac{1}{N}#frac{dN}{d(#Delta#phi)}");
    //hdPhiRawce[i]->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
    
    hdPhiRawce[i]->GetXaxis()->SetRangeUser(-3.5, 3.5);
    hdPhiRawce[i]->GetYaxis()->SetRangeUser(low[i], high[i]);
    hdPhiRawce[i]->SetMarkerStyle(20);
    hdPhiRawbe[i]->SetMarkerStyle(21);
    hdPhiRawbe[i]->SetMarkerSize(0.6);
    hdPhiRawce[i]->SetMarkerSize(0.6);
    
    
    hdPhiRawce[i]->Draw("PE");
    hdPhiRawbe[i]->SetLineColor(kRed);
    hdPhiRawbe[i]->SetMarkerColor(kRed);
    hdPhiRawbe[i]->Draw("same PE");
    
    //TLegend* leg = new TLegend(0.4,0.7,0.75,0.85);
    TLegend* leg = new TLegend(0.65,0.7,0.88,0.85);
    leg->SetBorderSize(0);

    leg->AddEntry(hdPhiRawbe[i],"b#bar{b}#rightarrow NPE", "l");
    leg->AddEntry(hdPhiRawce[i],"c#bar{c}#rightarrow NPE","l");
    leg->Draw("same");
    
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
  sprintf(name, "afterSym_%s.pdf[", FileName);
  temp->Print(name);

  temp = c;
  temp->Print(name);

  sprintf(name, "afterSym_%s.pdf]", FileName);
  temp->Print(name);

}


//=================================================================================

void AddHist(TH1 *h, TH1 *h2, TH1 *hadd){
  
  int bin1 = h->GetNbinsX();
  int bin2 = h2->GetNbinsX();
  if(bin1 != bin2){
     cout<<" failed to rebin histogram, bins are different with original histogram!"<<endl;
     return;
  }
  for(int i=0;i<bin2;i++){
    double c1 = h->GetBinContent(i+1);
    double c2 = h2->GetBinContent(i+1);
    double e1 = h->GetBinError(i+1);
    double e2 = h2->GetBinError(i+1);
    
    double val = 0;
    double err=0;
    if(e1>0 || e2>0){
      val = (c1/e1/e1+c2/e2/e2)/(1/e1/e1+1/e2/e2);
      err = sqrt(1/(1/e1/e1+1/e2/e2));
    }
    hadd->SetBinContent(i+1, val);
    hadd->SetBinError(i+1, err);
  }
  return 0;
  
}
