
double fit_pythia(double *x, double *par)
{
 
 TFile *file1 = TFile::Open("PYTHIA_dndphi_ppy06.root");

 char name1[100];
 sprintf(name1,"phy_pyhia_D_%d",par[1]);
 PYTHIA_D = (TH1D*)file1->Get(name1);

 char name2[100];
 sprintf(name2,"phy_pyhia_B_%d",par[1]);
 PYTHIA_B = (TH1D*)file1->Get(name2);

 int bin = PYTHIA_D->FindBin(x[0]);


 double py_D = PYTHIA_D->GetBinContent(bin);
 double py_B = PYTHIA_B->GetBinContent(bin);
 double val = par[0]*py_B + (1.0-par[0])*py_D;


 file1->Close(); 

 return val;
}

void Draw_Comp_PYTHIA()
{

  gSystem->Load("libGraphic.so");
  Graphic *Gp = new Graphic();
  Gp->SetPallet(); 
  gStyle->SetOptFit(1);

  char nameR[100];
  char nameF[100];

     sprintf(nameR,"Nonp_h_ppy06.root"); 
     sprintf(nameF,"BD_06.dat"); 
  
  TFile *file0 = TFile::Open(nameR);

  TH1D* Hdphi0[4];
  Hdphi0[0] = (TH1D*)file0->Get("dphi0_0"); 
  Hdphi0[1] = (TH1D*)file0->Get("dphi0_1"); 
  Hdphi0[2] = (TH1D*)file0->Get("dphi0_2"); 
  Hdphi0[3] = (TH1D*)file0->Get("dphi0_3"); 
 

 
  for(int i=0; i<4; i++)
     {
      Hdphi0[i]->SetMarkerColor(1);
      Hdphi0[i]->SetMarkerSize(1);
      Hdphi0[i]->SetMarkerStyle(20);
      }
  
  // ------- get PYTHIA result 

  TFile *file2 = TFile::Open("PYTHIA_dndphi_ppy06.root");
  TH1D *Pythia_De[4];
  TH1D *Pythia_Be[4];

  Hdphi0[0] -> SetTitle("5.5 < pT < 6.5"); 
  Hdphi0[1] -> SetTitle("6.5 < pT < 7.5"); 
  Hdphi0[2] -> SetTitle("7.5 < pT < 8.5"); 
  Hdphi0[3] -> SetTitle("8.5 < pT < 9.5"); 

  for(int i=0;i<4; i++)
     {
      char name1[100];
      sprintf(name1,"phy_pyhia_D_%d",i);
      Pythia_De[i] = (TH1D*)file2->Get(name1);

      char name2[100];
      sprintf(name2,"phy_pyhia_B_%d",i);
      Pythia_Be[i] = (TH1D*)file2->Get(name2);

      Pythia_De[i]->SetLineColor(2);
      Pythia_Be[i]->SetLineColor(4);

    }


  TCanvas *c0 = new TCanvas();
   
  TH1D *Gwaku = new TH1D("Gwaku","",32,-3.3,3.3); 
  Gwaku->SetMinimum(-0.02);
  Gwaku->SetMaximum(0.65);
 
  TF1 *fpythia = new TF1("fpythia",fit_pythia,-1.5,1.5,2);
 
  ofstream fout(nameF);
  double xx[4] = {6.0, 7.0, 8.0,9.0};  

   c0->Divide(2,2);
   for(int i=0; i<4; i++)
     {
      c0->cd(i+1);
      Gwaku->Draw(); 
      Hdphi0[i]->Draw("same");

      
     fpythia->SetParameter(0,0.6);
     fpythia->FixParameter(1,i);
     fpythia->SetLineWidth(1);
     Hdphi0[i]->Fit("fpythia","R");  
     //Hdphi0[i]->Fit("fpythia","R");  


      Pythia_De[i]->Draw("same");
      Pythia_Be[i]->Draw("same");

      double ratio = fpythia->GetParameter(0);
      double e_ratio = fpythia->GetParError(0);

      fout << xx[i] << "  " << ratio << "  " << 0.0 << "  " << e_ratio << endl;

     }

  TCanvas *c1 = new TCanvas();
  Hdphi0[0]->Draw(); 
  Pythia_De[0]->Draw("same");
  Pythia_Be[0]->Draw("same");
  
}
