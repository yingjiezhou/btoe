double fit_pythia(double *x, double *par)
{
  
  TFile *file1 = TFile::Open("PYTHIA_dndphi_ppy06_matt.root");
  
  char name1[100];
  int i = par[1];
//  cout<<i<<endl;
  sprintf(name1,"phy_pyhia_D_%d",i);
//  cout<<name1<<endl;
  auto PYTHIA_D = (TH1D*)file1->Get(name1);
  
  char name2[100];
  sprintf(name2,"phy_pyhia_B_%d",i);
  auto PYTHIA_B = (TH1D*)file1->Get(name2);
  
  PYTHIA_D->Rebin(4);
  PYTHIA_B->Rebin(4);

  
  int bin = PYTHIA_D->FindBin(x[0]);
  
  double py_D = PYTHIA_D->GetBinContent(bin);
  double py_B = PYTHIA_B->GetBinContent(bin);
  double val = par[0]*py_B + (1.0-par[0])*py_D;
  
  file1->Close();
  
  return val;
}

void Drawfit()
{
  
  gStyle->SetOptFit(1);
  
  char nameR[100];
  char nameF[100];
  
  sprintf(nameR,"Nonp_h_ppy06.root");
  
  TFile *file0 = TFile::Open(nameR);
  
  TH1D* Hdphi0[4];
  Hdphi0[0] = (TH1D*)file0->Get("fit_55_65");
  Hdphi0[1] = (TH1D*)file0->Get("fit_25_35");
  
  for(int i=0; i<2; i++)
  {
    Hdphi0[i]->SetMarkerColor(1);
    Hdphi0[i]->SetMarkerSize(1);
    Hdphi0[i]->SetMarkerStyle(20);
  }
  
  // ------- get PYTHIA result
  
  TFile *file2 = TFile::Open("PYTHIA_dndphi_ppy06_matt.root");
  TH1D *Pythia_De[4];
  TH1D *Pythia_Be[4];
  
  Hdphi0[0] -> SetTitle("5.5 < pT < 6.5");
  Hdphi0[1] -> SetTitle("2.5 < pT < 3.5");
  
  for(int i=0;i<2; i++)
  {
    char name1[100];
    sprintf(name1,"phy_pyhia_D_%d",i);
    Pythia_De[i] = (TH1D*)file2->Get(name1);
    
    char name2[100];
    sprintf(name2,"phy_pyhia_B_%d",i);
    Pythia_Be[i] = (TH1D*)file2->Get(name2);

    Pythia_De[i]->SetLineColor(2);
    Pythia_Be[i]->SetLineColor(4);
    
    Pythia_De[i]->Rebin(4.);
    Pythia_Be[i]->Rebin(4.);
    
//    cout<<Pythia_De[i]->GetNbinsX()<<endl;

  }
  
  
//  TCanvas *c0 = new TCanvas();
  
  TH1D *Gwaku = new TH1D("Gwaku","",32,-3.3,3.3);
  Gwaku->SetMinimum(-0.02);
  Gwaku->SetMaximum(0.65);
  
  TF1 *fpythia = new TF1("fpythia",fit_pythia,-1.5,1.5,2);
  
  //  ofstream fout(nameF);
  double xx[4] = {6.0, 7.0, 8.0,9.0};
  
//  c0->Divide(2,2);
  for(int i=0; i<2; i++)
  {
//    c0->cd(i+1);
//    Gwaku->Draw();
//    Hdphi0[i]->Draw("same");
    
//    cout<<Hdphi0[i]->GetNbinsX()<<endl;
    fpythia->SetParameter(0,0.6);
    fpythia->FixParameter(1,i);
    fpythia->SetLineWidth(1);
    Hdphi0[i]->Fit("fpythia","R");
    
//    Pythia_De[i]->Draw("same");
//    Pythia_Be[i]->Draw("same");
    
    double ratio = fpythia->GetParameter(0);
    double e_ratio = fpythia->GetParError(0);
    
    //      fout << xx[i] << "  " << ratio << "  " << 0.0 << "  " << e_ratio << endl;
    
  }
  
  TCanvas *c1 = new TCanvas();
  c1->Divide(2);
  c1->cd(2);
  Hdphi0[0]->Draw();
  Pythia_De[0]->Draw("same hist");
  Pythia_Be[0]->Draw("same hist");
  
  c1->cd(1);
  Hdphi0[1]->GetYaxis()->SetRangeUser(0., 0.44);
  Hdphi0[1]->Draw();
  Pythia_De[1]->Draw("same hist");
  Pythia_Be[1]->Draw("same hist");
  
  c1->SaveAs("Matt_fit.pdf");
}
