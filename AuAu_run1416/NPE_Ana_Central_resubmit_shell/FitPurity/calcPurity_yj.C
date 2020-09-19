void calcPurity_yj(int rs=1,int save=0, int doAllFits=0)
{
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};


  char dFile[500];
  sprintf(dFile,"/Volumes/YJMAC/Matt_production/NPE_Tuples_Central5.root");
  //sprintf(dFile,"../production/NPE_Tuples_TuneA10.root");
  TFile *f_D = new TFile(dFile);

  auto h01_2D = (TH2F*)f_D->Get("hDcaLog3D_6"); //zyj mva, w/o iso
  
  //auto h01_2D = (TH2F*)f_D->Get("hDcaLog3D_1"); //zyj mva, w/ iso

  TH1F* hpur= new TH1F("hpur","hpur",numPtBins,binning); // yj mva
  TH1F* hpur2= new TH1F("hpur2","hpur2",numPtBins,binning); // yj no mva
  TH1F* hpur3= new TH1F("hpur3","hpur3",numPtBins,binning); //matt mva
  TH1F* hpur33= new TH1F("hpur33","hpur33",numPtBins,binning); //matt no mva

  //================================================================================

  double eff[9]={0.7968543, 0.8307959, 0.8227239, 0.824273, 0.8810916, 0.9247312, 0.84, 1., 1.}; //0.45 cut eff, matt Central5
  double yield[9]={97722, 97722, 97722, 36359, 10836, 8296, 1438, 362, 263}; //  matt_Central5.root
  double yield_err[9]={542, 542, 542, 295, 144, 601, 122, 55, 21}; //  matt_Central5.root
   double r[9]={0.82933, 0.82933, 0.82933, 0.883735, 0.635876, 0.494455, 0.46909, 0.486311, 0.467936}; // Central5,matt
    double purity[9]={0.816212,0.816212,0.816212,0.728672,0.65352,0.544784,0.481189,0.647605,0.819007}; // matt
  //double purity_err[9]={};??
  
    double purity_matt[9]={0, 0, 0, 0, 0.268, 0.234, 0.286, 0.347, 0.}
    double purity_matt_err[9]={0, 0, 0, 0, 0, 0.031, 0.027, 0.089, 0};
    double purity_matt_mva[9]={0, 0, 0, 0, 0.176, 0.128, 0.123, 0.059, 0.}
    double purity_matt_mva_err[9]={0, 0, 0, 0, 0, 0, 0, 0.03, 0}

  /*
  double eff2[9]={0.640328, 0.7489481, 0.7873832, 0.8501071, 0.8425926, 0.9019608, 0.9333333,1, 1,}; // 0.45 cut eff , yj Central5
  double yield2[9]={49967, 49967, 49967, 18833, 4905, 5092, 983, 279, 170};
  double yield2_err[9]={349, 349, 349, 167, 96, 239, 73, 207, 2};
  double r2[9]={0.82933, 0.82933, 0.82933, 0.883735, 0.635876, 0.494455, 0.46909, 0.486311, 0.467936}; // Central5,zyj
  double purity2[9]={0.837476, 0.837476, 0.837476, 0.7281, 0.65489, 0.579759, 0.408277, 0.65505, 0.685347};
  double purity2_err[9]={};
  double r2[9]={0.775279, 0.775279, 0.775279, 0.792416, 0.652992, 0.409782, 0.324513, 0.329337, 0.321697};*/
  
  for(int i=3;i<8;i++){
    h01_2D->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    auto h02=(TH1F*)h01_2D->ProjectionY();
    double Nst = h02->Integral();
    cout<<Nst<<" is the number of inc e after mva cut and purity is: "<<eff[i-1]*yield[i-1]*r[i-1]/Nst<<endl;
    
    hpur->SetBinContent(i,1-eff[i-1]*yield[i-1]*r[i-1]/Nst);
    //hpur2->SetBinContent(i,1.-eff2[i-1]*yield[i-1]*r2[i-1]/Nst);
    hpur2->SetBinContent(i,1-purity[i-1]); // 0.4 cut
    //hpur2->SetBinError(i, purity);
    hpur3->SetBinContent(i, 1-purity_matt_mva[i-1]);
    hpur3->SetBinError(i, 1-purity_matt_mva_err[i-1]);


  }
//================================================================================

  TCanvas *c1 = new TCanvas("c1","c1");
  hpur->GetYaxis()->SetRangeUser(-1,1.);
  hpur->GetYaxis()->SetTitle("Hadron Fraction");
  hpur->GetXaxis()->SetTitle("#it{p}_{T}  [GeV]");
  hpur2->SetMarkerStyle(25);
  hpur2->SetMarkerSize(0.8);
  hpur2->SetMarkerColor(kRed);
  hpur2->SetLineColor(kRed);
  hpur->Draw("PE");
  hpur2->Draw("same PE");

  TLegend *leg = new TLegend(0.65,0.74,0.85,0.9);
  leg->AddEntry(hpur2,"Rectangular purity","LPE");
  leg->AddEntry(hpur,"MVA > 0.45, Matt weight","LPE");
  //leg->AddEntry(hpur2,"MVA > 0.45, Matt weight","LPE");
  leg->Draw("same");
  c1->SaveAs("hadron_fraction_comp.pdf");
  return ;
}


void Likelihood_Efficiency_pt_matt(TH1F *pt_eff_e__5)
{
  pt_eff_e__5 = new TH1F("pt_eff_e__5","pt_eff_e",9, xAxis1);
  pt_eff_e__5->SetBinContent(1,0.7660288);
  pt_eff_e__5->SetBinContent(2,0.8204768);
  pt_eff_e__5->SetBinContent(3,0.8736842);
  pt_eff_e__5->SetBinContent(4,0.8776824);
  pt_eff_e__5->SetBinContent(5,0.8888889);
  pt_eff_e__5->SetBinContent(6,0.8823529);
  pt_eff_e__5->SetBinContent(7,1);
  pt_eff_e__5->SetBinContent(9,1);
  pt_eff_e__5->SetBinError(1,0.00482729);
  pt_eff_e__5->SetBinError(2,0.01061471);
  pt_eff_e__5->SetBinError(3,0.01239689);
  pt_eff_e__5->SetBinError(4,0.01644842);
  pt_eff_e__5->SetBinError(5,0.03463105);
  pt_eff_e__5->SetBinError(6,0.04511559);
  pt_eff_e__5->SetBinError(7,0.06051536);
  pt_eff_e__5->SetBinError(8,nan);
}

void Likelihood_Efficiency_pt_yj(TH1F *pt_eff_e__5)
{
  pt_eff_e__5 = new TH1F("pt_eff_e__5","pt_eff_e",9, xAxis1);
  pt_eff_e__5->SetBinContent(1,0.640328);
  pt_eff_e__5->SetBinContent(2,0.7489481);
  pt_eff_e__5->SetBinContent(3,0.7873832);
  pt_eff_e__5->SetBinContent(4,0.8501071);
  pt_eff_e__5->SetBinContent(5,0.8425926);
  pt_eff_e__5->SetBinContent(6,0.9019608);
  pt_eff_e__5->SetBinContent(7,0.9333333);
  pt_eff_e__5->SetBinContent(9,1);
  pt_eff_e__5->SetBinError(1,0.005312327);
  pt_eff_e__5->SetBinError(2,0.01167453);
  pt_eff_e__5->SetBinError(3,0.01433334);
  pt_eff_e__5->SetBinError(4,0.01754429);
  pt_eff_e__5->SetBinError(5,0.03604197);
  pt_eff_e__5->SetBinError(6,0.04650655);
  pt_eff_e__5->SetBinError(7,0.08267973);
  pt_eff_e__5->SetBinError(8,nan);
  
  
}
