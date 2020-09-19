#include "fitdata1D.C"
void calcPurity(int rs=1,int save=0, int doAllFits=0)
{
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  ///// Electron PID cuts
  float cutLow = 0;
  float cutHigh = 0;
  //////
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  
  
  int pt=4;//Here
  
  
  char dFile[500];
  //sprintf(dFile,"../production/NPE_Tuples_TuneB9_Small.root");
  sprintf(dFile,"/Volumes/YJMAC/Matt_production/NPE_Tuples_TuneB12.root");
  TFile *f_D = new TFile(dFile);
  
  //auto h01_2D = (TH2F*)f_D->Get("hDcaLog3D_1"); //zyj mva
  auto h01_2D = (TH2F*)f_D->Get("hDcaLog3D_1"); //zyj mva
  auto h01_2D1 = (TH2F*)f_D->Get("hDcaLog3D_4");
  auto h01_2D_pi = (TH2F*)f_D->Get("hDcaLog3D_pi_1");
  
  h01_2D->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
  
  h01_2D1->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
  h01_2D_pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
  
  
  auto h01=(TH1F*)h01_2D->ProjectionY();
  auto h01_1=(TH1F*)h01_2D1->ProjectionY();
  auto h01_pi=(TH1F*)h01_2D_pi->ProjectionY();
  
  h01->Rebin(16);
  h01_1->Rebin(16);
  h01_pi->Rebin(16);
  TH1F* h01_calc= new TH1F("h01_calc","h01_calc",h01->GetNbinsX(),-12,1);
  
  TH1F* hpur= new TH1F("hpur","hpur",numPtBins,binning);
  TH1F* heff2= new TH1F("heff2","heff2",numPtBins,binning);
  
  auto h01_rat=(TH1F*) h01->Clone();
  h01_rat->SetName("h01_rat");
  double eff[9]={0.786182,0.820068, 0.834184,0.854135 ,0.866355,0.87522, 0.914286, 0.973684,0.87037};
  //double yield[9]={7939965.0236,1237638.2525,1098984.79792,263045.491728,68145.188841,45469.274668,7227.286792,1170.670332,315.219788
  double yield[7]={2.05781e+06, };
  
  int bin1 = h01_1->FindBin(-10);
  int bin2 = h01_1->FindBin(-2);
  
  for(int i=1;i<h01->GetNbinsX()+1;i++){
    
    double N= h01_1->GetBinContent(i);
    double Nst = h01->GetBinContent(i);
    double b = N-Nst;
    double a=1;
    if(Nst>0){
      a = Nst/(N);
    }
    h01_rat->SetBinContent(i,a);
    
    if(N>0)h01_rat->SetBinError(i,a*sqrt(1/N));
    //double weight = h01_pi->GetBinContenten(i)/h01_pi->Integral(bin1,bin2);
    //double val = (a*N*(1-eff[pt-1]) - eff[pt-1]*b  - Nst + N *eff[pt-1])/(1-eff[pt-1]);
    //h01_calc->SetBinContent(i,b * (-N*(a-eff[pt-1])));
    //h01_calc->SetBinError(i,0);
    
  }
  TF1 *f1 = new TF1("f1","[0]",-10,-2);
  h01_rat->Fit("f1","R","",-5,-2);
  double norm = f1->GetParameter(0);
  
  
  for(int i=1;i<10;i++){
    h01_2D->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    h01_2D1->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    
    auto h02=(TH1F*)h01_2D->ProjectionY();
    auto h01_2=(TH1F*)h01_2D1->ProjectionY();
    double Nst = h02->Integral();//GetBinContent(i);
    double N = h01_2->Integral();//GetBinContent(i);
    int flag = 0;
    
    double frac2 = N-yield[i-1];//(1000.-j)/1000.*N ;
    double frac1 = yield[i-1];//N*j/1000.;
    
    double eff2 = (Nst - frac1*eff[i-1])/frac2;
    if(eff2<0)continue;
    double newEff = (frac1*eff[i-1] + frac2*eff2);
    
    cout << newEff << " " << Nst  << " " << frac2 << " " << frac1 << " " << frac1/(frac2+frac1) << endl;
    hpur->SetBinContent(i,frac1/(frac2+frac1));
    heff2->SetBinContent(i,eff2);
    
  }
  
  TCanvas *crat = new TCanvas("crat","crat");
  h01_rat->GetYaxis()->SetRangeUser(0.5,1);
  h01_rat->Draw("PE");
  
  TCanvas *c1 = new TCanvas("c1","c1");
  hpur->GetYaxis()->SetRangeUser(0.,1);
  hpur->Draw("P");
  heff2->Draw("same Hist");
  
  
  TCanvas *cpi = new TCanvas("cpi","cpi");
  h01_pi->GetXaxis()->SetRangeUser(-10,-2);
  h01_calc->GetXaxis()->SetRangeUser(-10,-2);
  h01_pi->SetLineColor(kRed);
  h01_pi->Draw("hist");
  h01_calc->Draw("same hist");
  
  //cout << h01_calc->Integral()<< " " << (h01_1->Integral()-h01_calc->Integral()) <<  " " << h01_1->Integral() << endl;
  
  //cout << " Purity " << (h01->Integral()-h01_calc->Integral())/h01->Integral() << endl;
}

