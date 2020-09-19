void Likelihood_Efficiency_pt_yj(TH1F *pt_eff_e__5);
void Likelihood_Efficiency_pt_matt(TH1F *pt_eff_e__5);

void calcPurity_err_yj(int rs=1,int save=0, int doAllFits=0)
{
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  
  TH1F::SetDefaultSumw2();
  
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};

  char dFile[500];
  //sprintf(dFile,"/Volumes/YJMAC/Matt_production/NPE_Tuples_Central5.root"); //matt weight
  sprintf(dFile,"production/NPE_Tuples_TuneCentral5.root"); //yj
  TFile *f_D = new TFile(dFile);
  auto h01_2D = (TH2F*)f_D->Get("hDcaLog3D_6"); //zyj mva, w/o iso
  
  TH1F* thNe_mva= new TH1F("thNe_mva","thNe_mva",numPtBins,binning);

  //TH1F* hpur2= new TH1F("hpur","hpur",numPtBins,binning); // yj mva
  TH1F* hpur22= new TH1F("hpur22","hpur22",numPtBins,binning); // yj no mva
  
  TH1F* hpur3= new TH1F("hpur3","hpur3",numPtBins,binning); //matt mva
  TH1F* hpur33= new TH1F("hpur33","hpur33",numPtBins,binning); //matt no mva
  //================================================================================

  TH1F* eff_yj = new TH1F("","",numPtBins,binning);
  Likelihood_Efficiency_pt_yj(eff_yj);
  
  double purity_matt[9]={0, 0, 0, 0, 0.268, 0.234, 0.286, 0.347, 0.};
  double purity_matt_err[9]={0, 0, 0, 0, 0, 0, 0, 0.03, 0};
  
  double purity_matt_mva[9]={0, 0, 0, 0, 0.176, 0.128, 0.123, 0.059, 0.};
  double purity_matt_mva_err[9]={0, 0, 0, 0, 0, 0.031, 0.027, 0.089, 0};

  double purity22[9]={0.837476, 0.837476, 0.837476, 0.7281, 0.65489, 0.579759, 0.408277, 0.65505, 0.685347}; // w/o mva
  double yield2[9]={49967, 49967, 49967, 18833, 4905, 5092, 983, 279, 170};
  double yield2_err[9]={349, 349, 349, 167, 96, 239, 73, 207, 2};
  double r2[9]={0.775279, 0.775279, 0.775279, 0.792416, 0.652992, 0.409782, 0.324513, 0.329337, 0.321697};
  TH1F *thNe =new TH1F("thNe","thNe",numPtBins,binning);
  for(auto i= 0;i<9; i++){
    thNe->SetBinContent(i+1, yield2[i]*r2[i]);
    thNe->SetBinError(i+1, yield2_err[i]*r2[i]);
    //cout<<r2[i]<<endl;
    hpur22->SetBinContent(i+1, 1-purity22[i]); // purity w/o mva cut, yj central-5
    hpur22->SetBinError(i+1, 0.00001); // purity w/o mva cut, yj central-5

     hpur3->SetBinContent(i+1, purity_matt_mva[i]);
       hpur3->SetBinError(i+1, purity_matt_mva_err[i]); // mb, mva
    hpur33->SetBinContent(i+1, purity_matt[i]);
      hpur33->SetBinError(i+1, purity_matt_err[i]); // matt, mb trigger, no mva

  }
  
  double num;
  double numErr;
  for(int i=1;i<10;i++){
    h01_2D->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    auto h02=(TH1F*)h01_2D->ProjectionY();
    num = h02->IntegralAndError(1, h02->GetNbinsX(), numErr);
    thNe_mva->SetBinContent(i, num);
    thNe_mva->SetBinError(i, numErr);
  }

  auto temp=(TH1F* )thNe->Clone("purity");//Ne
  temp->Multiply(eff_yj); // Ne*effi
  auto hpur2=(TH1F* )thNe_mva->Clone("hfraction");
  hpur2->Add(temp, -1);
  hpur2->Divide(thNe_mva); //purity w/ mva cut, yj central-5
  //================================================================================
  
  TCanvas *c1 = new TCanvas("c1","c1");
  hpur2->GetYaxis()->SetRangeUser(-1,1.);
  hpur2->GetYaxis()->SetTitle("Hadron Fraction");
  hpur2->GetXaxis()->SetTitle("#it{p}_{T}  [GeV]");
  hpur2->SetMarkerStyle(25);
  hpur22->SetMarkerStyle(25);
  hpur3->SetMarkerStyle(26);
  hpur33->SetMarkerStyle(26);
  hpur2->SetMarkerSize(0.8);
  hpur22->SetMarkerSize(0.8);
  hpur3->SetMarkerSize(0.8);
  hpur33->SetMarkerSize(0.8);
  
  hpur2->SetMarkerColor(kRed);
  hpur3->SetMarkerColor(kRed);
  hpur2->SetLineColor(kRed);
  hpur3->SetLineColor(kRed);
  
  hpur2->Draw("PE");
  hpur22->Draw("same PE");
  hpur3->Draw("same PE");
  hpur33->Draw("same PE");
  
  TLegend *leg = new TLegend(0.65,0.74,0.85,0.9);
  leg->AddEntry(hpur22,"Rectangular purity, Central-5","LPE");
  leg->AddEntry(hpur33,"Rectangular purity, MB","LPE");
  leg->AddEntry(hpur2,"MVA > 0.45, Central-5","LPE");
  leg->AddEntry(hpur3,"MVA > 0.45, MB","LPE");
  leg->Draw("same");
  c1->SaveAs("hadron_fraction_comp.pdf");
  return ;
}


void Likelihood_Efficiency_pt_matt(TH1F *pt_eff_e__5)
{
  double xAxis1[10]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  pt_eff_e__5 = new TH1F("pt_eff_e__5","pt_eff_e",9, xAxis1);
  pt_eff_e__5->SetBinContent(1,0.7660288);
  pt_eff_e__5->SetBinContent(2,0.8204768);
  pt_eff_e__5->SetBinContent(3,0.8736842);
  pt_eff_e__5->SetBinContent(4,0.8776824);
  pt_eff_e__5->SetBinContent(5,0.8888889);
  pt_eff_e__5->SetBinContent(6,0.8823529);
  pt_eff_e__5->SetBinContent(7,1);
  pt_eff_e__5->SetBinContent(8,1);
  pt_eff_e__5->SetBinContent(9,1);
  pt_eff_e__5->SetBinError(1,0.00482729);
  pt_eff_e__5->SetBinError(2,0.01061471);
  pt_eff_e__5->SetBinError(3,0.01239689);
  pt_eff_e__5->SetBinError(4,0.01644842);
  pt_eff_e__5->SetBinError(5,0.03463105);
  pt_eff_e__5->SetBinError(6,0.04511559);
  pt_eff_e__5->SetBinError(7,0.06051536);
  pt_eff_e__5->SetBinError(8,0);
  pt_eff_e__5->SetBinError(9,0);
}

void Likelihood_Efficiency_pt_yj(TH1F *pt_eff_e__5)
{
  double xAxis1[10]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  //pt_eff_e__5 = new TH1F("pt_eff_e__5","pt_eff_e",9, xAxis1);
  pt_eff_e__5->SetBinContent(1,0.640328);
  pt_eff_e__5->SetBinContent(2,0.7489481);
  pt_eff_e__5->SetBinContent(3,0.7873832);
  pt_eff_e__5->SetBinContent(4,0.8501071);
  pt_eff_e__5->SetBinContent(5,0.8425926);
  pt_eff_e__5->SetBinContent(6,0.9019608);
  pt_eff_e__5->SetBinContent(7,0.9333333);
  pt_eff_e__5->SetBinContent(8,1);
  pt_eff_e__5->SetBinContent(9,1);
  pt_eff_e__5->SetBinError(1,0.005312327);
  pt_eff_e__5->SetBinError(2,0.01167453);
  pt_eff_e__5->SetBinError(3,0.01433334);
  pt_eff_e__5->SetBinError(4,0.01754429);
  pt_eff_e__5->SetBinError(5,0.03604197);
  pt_eff_e__5->SetBinError(6,0.04650655);
  pt_eff_e__5->SetBinError(7,0.08267973);
  pt_eff_e__5->SetBinError(8,0);
  pt_eff_e__5->SetBinError(9,0);
}

