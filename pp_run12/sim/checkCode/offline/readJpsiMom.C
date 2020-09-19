void readJpsiMom(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  auto ft = new TFile("rootfile/directJpsi_MB_v3.root", "READ");
//  auto h1t = (TH1D*) ft->Get("hjeptN"); // jpsi pt spectrum
//  h1t->Rebin(10);
//
//  for(int i = 0; i< h1t->GetNbinsX(); i++){
//    double pt = h1t->GetBinCenter(i+1);
//    double tmpp = 1./(2* TMath::Pi() * pt* h1t->GetBinWidth(i)); ////!!!!! notice here divide by dpT
//    tmpp = tmpp / 1. ; // rapidy
//    tmpp = tmpp/5996. * 0.059; // number of root file
//    h1t->SetBinContent(i+1, h1t->GetBinContent(i+1) * tmpp);
//    h1t->SetBinError(i+1, h1t->GetBinError(i+1)*tmpp);
//  }
//
//  h1t->SetMarkerColor(kRed+2);
//  h1t->SetLineColor(kRed+2);
  //========================================
  
  gStyle->SetTitle(" ");
  auto hmomp = new TH1D("hmomp", "", 100, 0., 100.);
  auto hmomq = new TH1D("hmomq", "", 200, 400., 600.);
  auto hmom13 = new TH1D("hmom13", "", 2000, 4000, 6000);
  auto hmom1 = new TH1D("hmomq1", "", 200, 10400, 10600);
  auto hmom12 = new TH1D("hmom12", "", 200, 20400, 20600);
  auto hmom122 = new TH1D("hmom122", "", 200, 100400, 100600);
  auto hmom11 = new TH1D("hmomq11", "", 200, 9900400, 9900600);
  auto hmom111 = new TH1D("hmomq111", "", 200, 9910400, 9910600);
  
  
  TNtuple *nf = (TNtuple*)ft->Get("qaCheck");
  Int_t entries = (Int_t)nf->GetEntries();
  cout<<"number of jpsi : "<<entries<<endl;
  cout<<"======================================== "<<endl;
  float pMom;
  nf->SetBranchAddress("momID",&pMom);
  for (Int_t ki=1;ki<entries;ki++)
  {
    nf->GetEntry(ki);
    pMom = fabs(pMom);
    if(pMom>0 && pMom<100)hmomp->Fill(pMom);
    else if(pMom>400 && pMom<600)hmomq->Fill(pMom);
    else if(pMom > 4000 && pMom < 6000)hmom13->Fill(pMom);
    else if(pMom>10400 && pMom<10600)hmom1->Fill(pMom);
    else if(pMom>20400 && pMom<20600)hmom12->Fill(pMom);
    else if(pMom>100400 && pMom<100600)hmom122->Fill(pMom);
    else if(pMom>9900400 && pMom<9900600)hmom11->Fill(pMom);
    else if(pMom>9910400 && pMom<9910600)hmom111->Fill(pMom);
    else cout<<pMom<<endl;
    
  }
  
  auto c = new TCanvas();
//  c->Divide(4,2,0.002,0.002,0.);
  c->Divide(4,2,1e-3);

  c->cd(1);
  gPad->SetLogy(1);
  hmomp->Draw();
  c->cd(2);
  gPad->SetLogy(1);
  hmomq->Draw();
  c->cd(3);
  gPad->SetLogy(1);
  hmom13->Draw();
  c->cd(4);
  gPad->SetLogy(1);
  for(auto i=0; i<200; i++) hmom1->GetXaxis()->ChangeLabel(i+1,330.,-1,0);
  hmom1->GetXaxis()->SetNoExponent(kTRUE);
  hmom1->Draw();
  c->cd(5);
  gPad->SetLogy(1);
  for(auto i=0; i<200; i++) hmom12->GetXaxis()->ChangeLabel(i+1,330.,-1,0);
  hmom12->GetXaxis()->SetNoExponent(kTRUE);
  hmom12->Draw();
  c->cd(6);
  gPad->SetLogy(1);
  for(auto i=0; i<200; i++) hmom122->GetXaxis()->ChangeLabel(i+1,330.,-1,0);
  hmom122->GetXaxis()->SetNoExponent(kTRUE);
  hmom122->Draw();
  c->cd(7);
  gPad->SetLogy(1);
  for(auto i=0; i<200; i++) hmom11->GetXaxis()->ChangeLabel(i+1,330.,-1,0);
  hmom11->GetXaxis()->SetNoExponent(kTRUE);
  hmom11->Draw();
  c->cd(8);
  gPad->SetLogy(1);
  for(auto i=0; i<200; i++) hmom111->GetXaxis()->ChangeLabel(i+1,330.,-1,0);
  hmom111->GetXaxis()->SetNoExponent(kTRUE);
  hmom111->Draw();
  
  c->SaveAs("readJpsiMom.pdf");
}
