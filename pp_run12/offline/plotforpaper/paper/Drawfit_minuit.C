void doFit(TMinuit* ,Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&); // Generic call to start fit (function, param0, param1, err0, err1) with the par and err being global returns
void chi2_2(Int_t&,Double_t*,Double_t&,Double_t* ,Int_t);
double getFitFunction(Double_t*, double, double);
double getFitFunctionError(Double_t*,double, double);

Double_t p21[4],p20[4],e21U[4],e20U[4],e21D[4],e20D[4];
Int_t currentPtBin;
Double_t curChi2;
Double_t curNDF;
Int_t rangeBinLow, rangeBinHigh;

// Minuit Constants
double amin,edm,errdef;
int nvpar,nparx,icstat;
double arglist[10];int ierflg=0;
double dum1,dum2;
char buf[1024];

Float_t rangefit = 1.5;
TH1D* Hdphi0[4];
TH1D *Pythia_De[4];
TH1D *Pythia_Be[4];


void Drawfit_minuit()
{
  
//  gROOT->ProcessLine(".x ~/myStyle.C");
  gROOT->ForceStyle();
  gStyle->SetOptStat(0);
//  gStyle->SetStatFormat("6.3g"); // specified as c printf options
//  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);
  gStyle->SetPadLeftMargin(0.14);
  
  char nameR[100];
  char nameF[100];
  
  sprintf(nameR,"Nonp_h_ppy06.root");
  
  TFile *file0 = TFile::Open(nameR);
  

  Hdphi0[0] = (TH1D*)file0->Get("fit_25_35");
  Hdphi0[3] = (TH1D*)file0->Get("fit_55_65");
  
  for(int i=0; i<4; i++)
  {
    if(i==1 || i==2) continue;
    Hdphi0[i]->SetMarkerColor(1);
    Hdphi0[i]->SetMarkerSize(1);
    Hdphi0[i]->SetMarkerStyle(20);
  }
  
  // ------- get PYTHIA result
  
  TFile *file2 = TFile::Open("PYTHIA_dndphi_ppy06_matt.root");
  Hdphi0[0] -> SetTitle("2.5 < pT < 3.5");
  Hdphi0[3] -> SetTitle("5.5 < pT < 6.5");
  
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
  
  
//  TCanvas *c0 = new TCanvas();
  
  TH1D *Gwaku = new TH1D("Gwaku","",32,-3.3,3.3);
  Gwaku->SetMinimum(-0.02);
  Gwaku->SetMaximum(0.65);
  
  //  ofstream fout(nameF);
  double xx[4] = {6.0, 7.0, 8.0,9.0};
  
  auto tx1 = new TPaveText(.4,.75,.85,.85,"NB NDC1");
  auto tx2 = new TPaveText(.4,.75,.85,.85,"NB NDC2");

  char Label1[100];
  char Label2[100];
  
  TMinuit* gMinuit = new TMinuit(2);
  for(int i=0; i<4; i++)
  {
    if(i==1 || i==2) continue;
    
    currentPtBin = i;
    gMinuit->SetFCN(chi2_2);
    doFit(gMinuit,p21[i],p20[i],e21U[i],e20U[i],e21D[i],e20D[i]);
    if(i == 0)sprintf(Label1,"Chi2/NDF: %.2f/%.0f; rB: %.2f",curChi2,curNDF,p21[i]);
    else sprintf(Label2,"Chi2/NDF: %.2f/%.0f; rB: %.2f",curChi2,curNDF,p21[i]);
    if(i == 0) tx1->AddText(Label1);
    else tx2->AddText(Label2);
    
    if(i == 0) tx1->SetFillColor(kWhite);
    else tx2->SetFillColor(kWhite);
//    cout<<Label1<<endl;
    
//    cout<<"========================================================"<<endl;
//    cout << p21[i] << "  UPErr: " << e21U[i] << "  DwErr: " << e20U[i] << endl;
  }
  
  TCanvas *c1 = new TCanvas();
  c1->Divide(2);
  c1->cd(1);
  Pythia_De[0]->Scale(1. - p21[0]);
  Pythia_Be[0]->Scale(p21[0]);

  Hdphi0[0]->GetYaxis()->SetRangeUser(0., 0.44);
  Hdphi0[0]->Draw();
  Pythia_De[0]->Draw("same hist");
  Pythia_Be[0]->Draw("same hist");
  tx1->Draw("same");
  
  c1->cd(2);
  Pythia_De[3]->Scale(1. - p21[3]);
  Pythia_Be[3]->Scale(p21[3]);
  Hdphi0[3]->Draw();
  Pythia_De[3]->Draw("same hist");
  Pythia_Be[3]->Draw("same hist");
  tx2->Draw("same");
  c1->SaveAs("Drawfit_minuit.pdf");

}

void chi2_2(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag){
  
  Int_t ptbin = currentPtBin;
  
  curChi2 = 0.;
  curNDF = 0.;
  double chiSq = 0.;
  int nDof = 0;
  
  rangeBinLow  = Hdphi0[ptbin]->GetXaxis()->FindBin(-1.*rangefit);
  rangeBinHigh  = Hdphi0[ptbin]->GetXaxis()->FindBin(rangefit);
  for(int k=rangeBinLow;k<rangeBinHigh;k++){
    
    double y1  = Pythia_De[ptbin]     -> GetBinContent(k+1);
    double y2  = Pythia_Be[ptbin]     -> GetBinContent(k+1);
    double y0  = Hdphi0[ptbin] -> GetBinContent(k+1);
    double ey0 = Hdphi0[ptbin] -> GetBinError(k+1);
    double ey1 = Pythia_De[ptbin]     -> GetBinError(k+1);
    double ey2 = Pythia_Be[ptbin]     -> GetBinError(k+1);
    
    double ycomb = getFitFunction(par,y1,y2);
    double ycomberr = getFitFunctionError(par,ey1,ey2);
    double delta = (ycomb - y0) / sqrt(ey0*ey0+ycomberr*ycomberr);
    chiSq += delta*delta;
    nDof++;
  }
  
  func = chiSq;
  curChi2 = chiSq;
  curNDF = nDof;
  
}

double getFitFunction(Double_t *par, double y1, double y2)
{
  double ycomb;
  //  if(oneParamFit)
  //    ycomb = FITPARA*(par[0]*y2 + y1*(1-par[0])); // rb*yb + (1-rb)*yv
  //  else
  ycomb = par[1]*par[0]*y2 + y1*(1-par[0])*par[1]; //A*rb*yb + A*(1-rb)*yc
  return ycomb;
}

double getFitFunctionError(Double_t *par, double ey1, double ey2)
{
  // double ycomberr = FITPARA*sqrt(par[0]*par[0]*ey2*ey2 + (1-par[0])*(1-par[0])*ey1*ey1);
  double ycomberr;
  //  if(oneParamFit)
  //    ycomberr = FITPARA*sqrt(par[0]*par[0]*ey2*ey2 + (1-par[0])*(1-par[0])*ey1*ey1);
  //  else
  ycomberr = sqrt(par[1]*par[0]*par[1]*par[0]*ey2*ey2 + ey1*ey1*(1-par[0])*par[1]*(1-par[0])*par[1]); //A*rb*yb + A*(1-rb)*yc
  return ycomberr;
}

void doFit(TMinuit* gMinuit, Double_t& p0, Double_t& p1, Double_t& e0U, Double_t& e1U, Double_t& e0D, Double_t& e1D)
{
  Double_t e0, e1;
  gMinuit->SetMaxIterations(50000);
  arglist[0]=1; //error definition: chi^2 change by 1 to get 1 sigma
  gMinuit->mnexcm("SET ERR",arglist,1,ierflg);
  
  //starting values
  double vstart[2]={0.1,1}; //frac
  double step[2]={0.005,0.005}; //starting step
  gMinuit->mnparm(0,"BtoNPE frac",vstart[0],step[0],0.000,1,ierflg);
  gMinuit->mnparm(1,"Scale Factor",vstart[1],step[1],0.6,2.,ierflg);
  gMinuit->mnexcm("MIGRAD",arglist,0,ierflg);
  gMinuit->mnexcm("MINOS",arglist,0,ierflg);
  
  cout<< "done with fit! Error Flag: " << ierflg << endl;
  
  //fit results
  TString *str0 = new TString("BtoNPE frac");
  TString *str1 = new TString("Scale Factor");
  
  gMinuit->mnpout(0,*str0,p0,e0,dum1,dum2,ierflg);
  gMinuit->mnpout(1,*str1,p1,e1,dum1,dum2,ierflg);
  gMinuit->mnerrs(0, e0U, e0D, dum1, dum2);
  gMinuit->mnerrs(1, e1U, e1D, dum1, dum2);
  if(e0U == 0.) e0U = 1.-p0;
  if(e0D == 0.) e0D = p0; else e0D = -e0D;
  if(e1U == 0.) e1U = 1.-p1;
  if(e1D == 0.) e1D = p1; else e1D = -e1D;
  
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
  gMinuit->mnprin(4,amin);
    
}
