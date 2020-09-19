void calcPurity_yj(int rs=1,int save=0, int doAllFits=0)
{
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};

  char dFile[500];
  sprintf(dFile,"/Volumes/YJMAC/Matt_production/NPE_Tuples_TuneB10.root");
  //sprintf(dFile,"../production/NPE_Tuples_TuneA10.root");
  TFile *f_D = new TFile(dFile);

  auto h01_2D = (TH2F*)f_D->Get("hDcaLog3D_6"); //zyj mva, w/o iso
  //auto h01_2D = (TH2F*)f_D->Get("hDcaLog3D_1"); //zyj mva, w/ iso

  TH1F* hpur= new TH1F("hpur","hpur",numPtBins,binning);
  TH1F* hpur2= new TH1F("hpur2","hpur2",numPtBins,binning);
  //================================================================================

  double eff[9]={0.8073705, 0.839343, 0.8303109, 0.8343868, 0.9015595, 0.9498208, 0.944, 1., 1.}; // 0.45 cut eff , B10
  double eff2[9]={0.7968543, 0.8307959, 0.8227239, 0.824273, 0.8810916, 0.9247312, 0.84, 1., 1.}; //0.45 cut eff, matt B10
  double yield[9]={2.e+06, 2.e+06,2.05781e+06, 619160, 127081, 105241, 13476, 2578, 666}; // zyj, _B10.root

  double r1[9]={0.776349, 0.776349, 0.776349, 0.807167, 0.761829, 0.756064, 0.756064, 0.756064, 0.756064}; // B10,zyj
  double r2[9]={0.798738, 0.791867, 0.770234, 0.799012, 0.720882, 0.777247, 0.717014, 0.73675, 0.73675}; // B10,matt
  // 因为likelihood 分布不太一样，所以会影响分母，但是按道理差别不大

  for(int i=3;i<10;i++){
    h01_2D->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    auto h02=(TH1F*)h01_2D->ProjectionY();
    double Nst = h02->Integral();
    cout<<Nst<<" is the number of inc e after mva cut and purity is: "<<eff[i-1]*yield[i-1]*r1[i-1]/Nst<<endl;
    cout<<Nst<<" is the number of inc e after mva cut and purity is: "<<eff2[i-1]*yield[i-1]*r2[i-1]/Nst<<endl;
    hpur->SetBinContent(i,1.-eff[i-1]*yield[i-1]*r1[i-1]/Nst);
    hpur2->SetBinContent(i,1.-eff2[i-1]*yield[i-1]*r2[i-1]/Nst); // 0.4 cut
  }
//================================================================================

  TCanvas *c1 = new TCanvas("c1","c1");
  hpur->GetYaxis()->SetRangeUser(-1,1.);
  hpur->GetYaxis()->SetTitle("Hadron Fraction");
  hpur->GetXaxis()->SetTitle("#it{p}_{T}  [GeV]");
  hpur->SetMarkerColor(kRed);
  hpur->Draw("P");
  hpur2->Draw("same P");

  TLegend *leg = new TLegend(0.65,0.74,0.85,0.9);
  leg->AddEntry(hpur,"MVA > 0.45, YJ weight","LPE");
  leg->AddEntry(hpur2,"MVA > 0.45, Matt weight","LPE");
  leg->Draw("same");
  return ;
}


