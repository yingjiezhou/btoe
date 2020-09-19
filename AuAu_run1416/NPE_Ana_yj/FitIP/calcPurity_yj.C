#include "fitdata1D.C"
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

  auto h01_2D = (TH2F*)f_D->Get("hDcaLog3D_1"); //zyj mva

  TH1F* hpur= new TH1F("hpur","hpur",numPtBins,binning);
  TH1F* hpur2= new TH1F("hpur2","hpur2",numPtBins,binning);
  //================================================================================

  //double eff[9]={0.786182,0.820068, 0.834184,0.854135 ,0.866355,0.87522, 0.914286, 0.973684,0.87037};
  //double yield[9]={7939965.0236,1237638.2525,1098984.79792,263045.491728,68145.188841,45469.274668,7227.286792,1170.670332,404};
  //double yield[9]={1.86996e+07, 3.03061e+06, 1.48384e+06, 734008, 148702, 91858, 85858, 2727, 756}; // zyj, _A10.root
  double eff[9]={0.8073705, 0.839343, 0.8303109, 0.8343868, 0.9015595, 0.9498208, 0.944, 1., 1.}; // 0.45 cut eff , B10
  double yield[9]={2.05781e+06, 2.05781e+06,2.05781e+06, 619160, 127081, 105241, 13476, 2578, 666}; // zyj, _B10.root

  for(int i=3;i<10;i++){
    h01_2D->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    auto h02=(TH1F*)h01_2D->ProjectionY();
    double Nst = h02->Integral();
    cout<<Nst<<" is the number of inc e after mva cut and purity is: "<<eff[i-1]*yield[i-1]/Nst<<endl;
    hpur->SetBinContent(i,1.-eff[i-1]*yield[i-1]/Nst);
    //hpur2->SetBinContent(i,1.-eff2[i-1]*yield[i-1]/Nst); // 0.4 cut
  }
//================================================================================

  TCanvas *c1 = new TCanvas("c1","c1");
  hpur->GetYaxis()->SetRangeUser(0.,1);
  hpur->GetYaxis()->SetTitle("Hadron Fraction");
  hpur->GetXaxis()->SetTitle("#it{p}_{T}  [GeV]");
  hpur->SetMarkerColor(kRed);
  hpur->Draw("P");
  //hpur2->Draw("same P");

  TLegend *leg = new TLegend(0.4,0.6,0.7,0.9);
  leg->AddEntry(hpur,"MVA > 0.45","PE");
  //leg->AddEntry(hpur2,"MVA > 0.4","PE");
  leg->Draw("same");
  return ;
}


