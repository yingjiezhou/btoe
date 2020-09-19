void plotJpsiNpeRatio(const char* FileName="jpsi", const char* FileName2="hf")
{
  
  gROOT->ProcessLine(".x ~/myStyle.C");
  gStyle->SetOptStat(0);
  
  char name[1000];
  sprintf(name, "rootfile/%s.root", FileName);
  TFile *fpy = new TFile(name,"READ");
  
  sprintf(name, "rootfile/%s.root", FileName2);
  TFile *fpy2 = new TFile(name,"READ");
  
  char label[100];
  TLatex lat1;
  
  Float_t ptrange[] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5};
  auto hjpsiNPEr = new TH1D("", "", 8, ptrange);
  
  
  TH1D *hEventTallyce[14];
  TH1D *hEventTallybe[14];
  
  TH1D *hEventTallyce2[14];
  TH1D *hEventTallybe2[14];
  
  TCanvas *c = new TCanvas("c","Pythia B/C Hists",150,0,1100,900);
  
  for(int i=0; i<8; i++){
    hEventTallyce[i] = (TH1D* )fpy->Get(Form("ceEventTally_%i",i));
    hEventTallybe[i] = (TH1D* )fpy->Get(Form("beEventTally_%i",i));
    
    hEventTallyce2[i] = (TH1D* )fpy2->Get(Form("ceEventTally_%i",i));
    hEventTallybe2[i] = (TH1D* )fpy2->Get(Form("beEventTally_%i",i));
    
    cout<<hEventTallyce[i]->GetBinContent(1)<<"    "<<hEventTallyce2[i]->GetBinContent(1)<<endl;
    
     cout<<hEventTallybe[i]->GetBinContent(1)<<"    "<<hEventTallybe2[i]->GetBinContent(1)<<endl;
    
         cout<<hEventTallybe[i]->GetBinContent(1)+hEventTallyce[i]->GetBinContent(1)<<"    "<<hEventTallybe2[i]->GetBinContent(1)+hEventTallyce2[i]->GetBinContent(1)<<endl;
    auto rt = hEventTallyce[i]->GetBinContent(1)+hEventTallybe[i]->GetBinContent(1);
    rt /= (hEventTallyce2[i]->GetBinContent(1)+hEventTallybe2[i]->GetBinContent(1));
    hjpsiNPEr->SetBinContent(i+1, rt);
    hjpsiNPEr->SetBinError(i+1, 1e-8);

  }
  c->cd();
  c->SetGridx();
  c->SetGridy();
  hjpsiNPEr->GetXaxis()->SetTitle("p_{T}(GeV/c)");
  hjpsiNPEr->GetYaxis()->SetTitle("J/#psi/NPE");
  hjpsiNPEr->GetXaxis()->SetRangeUser(2, 10);
  hjpsiNPEr->GetYaxis()->SetRangeUser(0, 0.5);
  hjpsiNPEr->Draw("pe");
//  c->SaveAs("pic/Jpsi_over_NpE.pdf");
  
}


