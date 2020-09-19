void runget_sym_minu(const char* FileName="pythia_npe_tree_May18", const char* FileName2="pythia_npe_dist_Jun9_old")
{
  
  // Open ROOT File
  gROOT->SetBatch(kTRUE); // sets batch mode, so don't draw canvas
//  gStyle->SetOptStat(0);
  gStyle->SetOptStat(111111);
  // Set Style parameters for this macro
  gStyle->SetOptTitle(1);
  
  char name[1000];
  sprintf(name, "input/%s.root", FileName);
  TFile *fpy = new TFile(name,"READ");
  
  sprintf(name, "input/%s.root", FileName2);
  TFile *fpy2 = new TFile(name,"READ");
  
  char label[100];
  TLatex lat1;
  Float_t lowpt[14] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5};
  Float_t highpt[14] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 18.5};
  Float_t low[] = {0, 0, 0, 0, 0, -0.1, -0.15, -0.4, -0.3};
  Float_t high[] = {0.3, 0.32, 0.32, 0.45, 0.47, 0.6, 1, 2, 1.6};
  
  TH1D *hdPhiRawce[14];
  TH1D *hdPhiRawbe[14];
//  TH1D *hdPhiRawceSym[14];
//  TH1D *hdPhiRawbeSym[14];
  
  TH1D *hEventTallyce[14];
  TH1D *hEventTallybe[14];
  
  TH1D *h2dPhiRawce[14];
  TH1D *h2dPhiRawbe[14];
  TH1D *h2EventTallyce[14];
  TH1D *h2EventTallybe[14];
  
  TFile *fsy = new TFile(Form("AfterSub_%s.root", FileName), "RECREATE");
  
//  //TCanvas *c = new TCanvas("c", "c", 800, 800);
//  TCanvas *c = new TCanvas("c","Pythia B/C Hists",150,0,1100,900);
//  c->Divide(3, 3);
  
  for(int i=0; i<9; i++){
    //for(int i=8; i<9; i++){

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
  
  TH1D* hdPhiRawceJpsi[9];
  TH1D* hEventTallyceJpsi[9];
  for(int i=0; i<9; i++){
    hdPhiRawceJpsi[i] = (TH1D*)h2dPhiRawce[i]->Clone(Form("hdPhiRawceJpsi_%i", i));
    hdPhiRawceJpsi[i]->Add(h2dPhiRawbe[i], 1);
    
    hEventTallyceJpsi[i] = (TH1D*)h2EventTallyce[i]->Clone(Form("ceEventTallyJpsi_%i",i));
    hEventTallyceJpsi[i]->Add(h2EventTallybe[i], 1);
  }
  
  fsy->cd();
  for(int i=0; i<9; i++){
    hdPhiRawce[i]->Write();
    hdPhiRawbe[i]->Write();
    hEventTallyce[i]->Write();
    hEventTallybe[i]->Write();
    hdPhiRawceJpsi[i]->Write();
    hEventTallyceJpsi[i]->Write();
  }
  fsy->Close();

}


