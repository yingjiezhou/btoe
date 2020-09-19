void templComp_py6_py8(const char* InputFile="Jpsi_sys/rootfile/hf.root")
{
  
  // Open ROOT File
  gROOT->ProcessLine(".x ~/myStyle.C");
  gROOT->SetBatch(kTRUE);
  //========================================
  
  const char* PdfFileName="plot_pyHF8_py6_comp";
  //========================================

  int par[4] = {0, 1, 2, 3};
  TFile *file1 = TFile::Open("PYTHIA_dndphi_ppy06.root");
  TH1D *PYTHIA_D;
  TH1D *PYTHIA_B;

  //  TH1D *Gwaku = new TH1D("Gwaku","",62,-Pi,Pi);
  
  
  
  //  cout<<PYTHIA_D->GetNbinsX()<<endl; // 64
  //========================================
  
  
  char name[1000];
  sprintf(name, "%s", InputFile);
  TFile *fpy = new TFile(name,"READ");
  
  char label[100];
  TLatex lat1;
  Float_t lowpt[14] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5};
  Float_t highpt[14] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 18.5};
  Float_t low[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,};
  Float_t high[] = {3.3, 3.3, 3.3, 5.8, 5.8, 5.8, 7.8, 7.8, 7.8};
  
  TH1D *hdPhiRawce[14];
  TH1D *hdPhiRawbe[14];
  TH1D *hdPhiRawceSym[14];
  TH1D *hdPhiRawbeSym[14];
  
  TH1D *hEventTallyce[14];
  TH1D *hEventTallybe[14];
    
  //TCanvas *c = new TCanvas("c", "c", 800, 800);
  TCanvas *c = new TCanvas("c","Pythia B/C Hists",150,0,1100,900);
  c->Divide(3, 3, 0, 0, 0);
  
  for(int i=0; i<9; i++){
    //for(int i=8; i<9; i++){
    
    hdPhiRawce[i] = (TH1D* )fpy->Get(Form("hdPhiRawce_%i", i));
    hdPhiRawbe[i] = (TH1D* )fpy->Get(Form("hdPhiRawbe_%i", i));
    hEventTallyce[i] = (TH1D* )fpy->Get(Form("ceEventTally_%i",i));
    hEventTallybe[i] = (TH1D* )fpy->Get(Form("beEventTally_%i",i));
    
    //    hdPhiRawceSym[i] = (TH1D* )hdPhiRawce[i]->Clone(Form("hdPhiRawceormSys_%i", i));
    //    hdPhiRawbeSym[i] = (TH1D* )hdPhiRawce[i]->Clone(Form("hdPhiRawbeormSys_%i", i));
    //
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
    
    
    hdPhiRawce[i]->Scale(1, "width");
    hdPhiRawbe[i]->Scale(1, "width");
    
    if(i>2 && i<7){
      char name1[100];
      sprintf(name1,"phy_pyhia_D_%d",par[i-3]);
      PYTHIA_D = (TH1D*)file1->Get(name1);
      
      char name2[100];
      sprintf(name2,"phy_pyhia_B_%d",par[i-3]);
      PYTHIA_B = (TH1D*)file1->Get(name2);
      
      PYTHIA_D->Sumw2();
      PYTHIA_B->Sumw2();
      
      PYTHIA_D->Scale(1, "width");
      PYTHIA_B->Scale(1, "width");
      PYTHIA_B->SetLineColor(2);
      
      
    }
    c->cd(i+1);
    hdPhiRawce[i]->SetLineColor(kBlack);
    hdPhiRawce[i]->GetXaxis()->SetTitle("#Delta#phi_{eh}");
    hdPhiRawce[i]->GetYaxis()->SetTitle("#frac{1}{N}#frac{dN}{d(#Delta#phi)}");
    //hdPhiRawce[i]->GetXaxis()->SetRangeUser(-TMath::Pi(),TMath::Pi());
    
    //    high[i] = hdPhiRawbe[i]->GetMaximum()*1.1;
    //    if(i == 0)high[i] = hdPhiRawce[i]->GetMaximum()*1.1;
//    low[i] = hdPhiRawbe[i]->GetBinContent(hdPhiRawbe[i]->FindBin(-1.5))*0.1;
//    high[i] = hdPhiRawbe[i]->GetBinContent(hdPhiRawbe[i]->FindBin(-3.))*1.6;
//
//    
//    cout<<low[i]<<"      "<<high[i]<<endl;
    hdPhiRawce[i]->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
    hdPhiRawce[i]->GetYaxis()->SetRangeUser(low[i], high[i]);
    hdPhiRawce[i]->SetMarkerStyle(20);
    hdPhiRawbe[i]->SetMarkerStyle(20);
    hdPhiRawbe[i]->SetMarkerSize(0.6);
    hdPhiRawce[i]->SetMarkerSize(0.6);
    
    
    //    cout<<hdPhiRawce[i]->Integral()<<"  -  "<<endl;
    hdPhiRawce[i]->Draw("PE");
    hdPhiRawbe[i]->SetLineColor(kRed);
    hdPhiRawbe[i]->SetMarkerColor(kRed);
    hdPhiRawbe[i]->Draw("same PE");
    
    
    TLegend* leg5 = new TLegend(0.2,0.7,0.5,0.85);
    leg5->SetBorderSize(0);
    
    if(i>2 && i<7){

      leg5->AddEntry(PYTHIA_B,"b#bar{b}#rightarrow NPE(Run6)", "l");
      leg5->AddEntry(PYTHIA_D,"c#bar{c}#rightarrow NPE(Run6)","l");
      PYTHIA_D->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());
      PYTHIA_B->GetXaxis()->SetRangeUser(-TMath::Pi(), TMath::Pi());

      PYTHIA_D->Draw("same hist ][");
      PYTHIA_B->Draw("same hist ][");
      leg5->Draw("same");
    }
    TLegend* leg = new TLegend(0.65,0.7,0.88,0.85);
    leg->SetBorderSize(0);
    leg->AddEntry(hdPhiRawbe[i],"b#bar{b}#rightarrow NPE", "p");
    leg->AddEntry(hdPhiRawce[i],"c#bar{c}#rightarrow NPE","p");
    
    
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
  sprintf(name, "pic/%s.pdf[", PdfFileName);
  temp->Print(name);
  
  temp = c;
  temp->Print(name);
  
  sprintf(name, "pic/%s.pdf]", PdfFileName);
  temp->Print(name);
  return 0;
}
