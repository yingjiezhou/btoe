
void Draw_dphi()
{

  gSystem->Load("libGraphic.so");
  Graphic *Gp = new Graphic();
  Gp->SetPallet(); 

  gStyle->SetOptFit(1); 

  const double Pi = acos(-1.0);

  ifstream fin("Purity_ppy06_h2_0.txt");
  //ifstream fin("../purity_test/Purity_ppy06_h2_0.txt");
  double puri[4],qq;
  for(int i=0; i<4; i++)fin>>qq>>puri[i];
  for(int i=0; i<4; i++)cout << puri[i] << endl;

  TFile *file0 = TFile::Open("Hist_ppy06.root");

  int ID=0;

   TF1 *Geff = new TF1("Geff","[0]/(exp(-x/[1])+1)+[2]");
   Geff->SetParameters(1.97,1.088,-1.201);


  
  TH2D *phi_inc   = phi_corr_0_c2_we->Clone("phi_inc");   // inclusive
  TH2D *phi_semi  = phi_corr_4_c2_rc->Clone("phi_semi");  // semi 
  TH2D *phi_opp0  = phi_corr_6_c2_we->Clone("phi_opp0");  // opp no part 
  TH2D *phi_same0 = phi_corr_7_c2_we->Clone("phi_same0"); // same no part
  TH2D *phi_same =  phi_corr_2_c2_rc->Clone("phi_same");
  TH2D *phi_hadron = phi_corr_c2_hadron->Clone("phi_hadron"); 
  
  // set histgrams

  TH1D *dphi_inc[4];  //[0]>3.0, [1]>4.0, [2]>5.0, [3]>6.0, [4]>7.0, [5]>8.0, [6]>9.0
  TH1D *dphi_semi[4];
  TH1D *dphi_opp0[4];
  TH1D *dphi_same0[4];
  TH1D *dphi_same[4];
  TH1D *dphi_hadron[4];

  char name0[100];
  char name1[100];
  char name2[100];
  char name3[100];
  char name4[100];
  char name5[100];

  for(int j=0; j<4; j++)
    {
      //int mim = 30 + j*10; 
      //int max = 30 + (j+1)*10; 

      int mim = 0;
      int max = 0; 

      if(j==0)
        {
         mim = 56; 
         max = 65; 
        }
      else if(j==1)       
        {
         mim = 66; 
         max = 75; 
        }
      else if(j==2)
        { 
         mim = 76; 
         max = 85; 
        }
      else
       {
         mim = 86; 
         max = 95; 
		}	 	

      cout << "pT = " << Pt_check_0->GetBinCenter(mim) << " ;  " <<  Pt_check_0->GetBinCenter(max) << endl;

      float N_inc = Pt_check_0->Integral(mim,max);
      float N_opp = Pt_check_1->Integral(mim,max);
      float N_sam = Pt_check_2->Integral(mim,max);
      float N_semi = Pt_check_3->Integral(mim,max);

      double pT = ((double)mim + (double)max -1.0)/20.0;
      double eff = Geff->Eval(pT);
      //double eff = 0.8;
      double fac = (1.0/eff)-1.0;
      cout << "pT = " << pT << " ; eff = " << eff << endl;

      float N_np = (N_inc*puri[j])-(1.0/eff)*(N_opp-N_sam);

      float N_had_trig = hadron_pT_trig->Integral(mim,max);
      float N_had = 0.0;
      N_had = N_inc*(1.0-puri[j]);

      sprintf(name0,"dphi_inc_%d",j);
      sprintf(name1,"dphi_semi_%d",j);
      sprintf(name2,"dphi_opp0_%d",j);
      sprintf(name3,"dphi_same0_%d",j);
      sprintf(name4,"dphi_same_%d",j);
      sprintf(name5,"dphi_hadron_%d",j);

      dphi_inc[j]   = phi_inc  -> ProjectionY(name0,mim,max); // inclusive
      dphi_semi[j]  = phi_semi -> ProjectionY(name1,mim,max); // semi
      dphi_opp0[j]  = phi_opp0 -> ProjectionY(name2,mim,max); // opp keep
      dphi_same0[j] = phi_same0 -> ProjectionY(name3,mim,max); // same keep 
      dphi_same[j] = phi_same -> ProjectionY(name4,mim,max); // same keep 
      dphi_hadron[j] = phi_hadron -> ProjectionY(name5,mim,max); // same keep 

      dphi_inc[j]->Rebin(4);
      dphi_semi[j]->Rebin(4);
      dphi_opp0[j]->Rebin(4);
      dphi_same0[j]->Rebin(4);
      dphi_same[j]->Rebin(4);
      dphi_hadron[j]->Rebin(4);

      dphi_inc[j]->Sumw2();
      dphi_semi[j]->Sumw2();
      dphi_opp0[j]->Sumw2();
      dphi_same0[j]->Sumw2();
      dphi_same[j]->Sumw2();
      dphi_hadron[j]->Sumw2();


      dphi_hadron[j]->Scale(N_had/N_had_trig);
      dphi_semi[j]->Add(dphi_hadron[j],-1);

      dphi_opp0[j]->Add(dphi_same0[j],-1); //dphi_same
      dphi_opp0[j]->Scale(fac);
      dphi_semi[j]->Add(dphi_same[j],1);
      dphi_semi[j]->Add(dphi_opp0[j],-1); 

      dphi_semi[j]->Scale(1.0/N_np); 


    }  

  //------------ Draw ---------------------

  // dndphi   

  TH1D *Gwaku = new TH1D("Gwaku","",62,-Pi,Pi);

  TCanvas *c1 = new TCanvas();
  //c1->Divide(4,2);
  c1->Divide(2,2);
  
  for(int i=0; i<4; i++)
    {
     c1->cd(i+1);
     Gwaku->Draw();

     dphi_semi[i]->Draw();
    }
  
 // ---------- Fill -------------------------
 
 char name[100];
 if(ID==0)sprintf(name,"Nonp_h_ppy06.root");
 
 TFile *fileout = new TFile(name,"recreate");
 dphi_semi[0]->Write("dphi0_0"); 
 dphi_semi[1]->Write("dphi0_1"); 
 dphi_semi[2]->Write("dphi0_2"); 
 dphi_semi[3]->Write("dphi0_3"); 

}
