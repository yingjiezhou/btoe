void norm(TH1F *h);
Double_t func1(Double_t *x, Double_t *par){
  Double_t arg = 0;
  Double_t val = 0;
  if(par[2]!=0 && par[1]!=1){
    arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
    val = par[0]*sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1]));//exp(arg*(1/(1-par[1])));
  }
  return val;
}
Double_t func(Double_t *x, Double_t *par){
  Double_t arg = 0;
  Double_t val = 0;
  double mass = 1-86484;
  if(par[1]!=0 && par[1]!=1){
    arg = (par[0]*par[1]+sqrt(x[0]*x[0]+mass*mass))/(mass+par[0]*par[1]);
    val = 1./2./TMath::Pi() *(( par[0]-1) * (par[0]-2) ) / (par[0]*par[1]+mass)/(mass*(par[0]-1)+par[0]*par[1])*TMath::Power(arg,-par[0]);
  }
  return val;
}

void Dcomp_MB_C5(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  //gStyle->SetPadLeftMargin(2);
  TGaxis::SetMaxDigits(3);
  
  TFile * inFile_D0=  new TFile("root_yj/D0_Spectra_Run14HFT.prc.root","READ");
  TGraphErrors *gd0=(TGraphErrors *) inFile_D0->Get("gD0_err_0_10");
  
  double xx4[7]={3.15e-01,9.68e-01,1.35,1.89,2.56,3.75,5.88};
  double yy4[7]={4.16e-02//*2*TMath::Pi()*3.15e-01
    ,3.59e-02//*2*TMath::Pi()*9.68e-01
    ,2.48e-02//*2*TMath::Pi()*1.35
    ,9.50e-03//*2*TMath::Pi()*1.89
    ,2.00e-03//*2*TMath::Pi()*2.56
    ,2.32e-04//*2*TMath::Pi()*3.75
    ,6.65e-06};//*2*TMath::Pi()*5.88};
  double xx4e[7]={0,0,0,0,0,0,0};
  double yy4e[7]={0.010026464980241,0.0081608,0.0047634,0.00194612,0.00048301,0.00005131,0.00000186};
  
  TGraphErrors *gd0_mb = new TGraphErrors(7,xx4,yy4,xx4e,yy4e);
  TF1 *fd0_mb = new TF1("fd0_mb",func1,0.315,20,3);
  fd0_mb->SetParameter(0,1.44381e+01);
  fd0_mb->SetParameter(1,0.11);
  fd0_mb->SetParameter(2,1.10008e-01);
  
  
  TF1 *fd0= new TF1("fd0","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*   TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,20);
  fd0->SetParameter(0,2.66458e+01);
  fd0->SetParameter(1,3.39421e-01);
  fd0->SetParameter(2,1.33430e+01);
  
  //=======================================================================

  gd0->Fit(fd0,"r");
  gd0_mb->Fit(fd0_mb,"r");
  
  //cout<<fd0->Integral(0, 20)<<endl;
  //=======================================================================
  
  TCanvas *c11 = new  TCanvas("c11","c11");
  c11->SetLogy();
  gd0->SetMarkerColor(kBlue);
  gd0->SetLineColor(kBlue);
  gd0->SetMarkerStyle(22);
  gd0->SetLineStyle(6);
  
  gd0_mb->SetLineColor(kRed);
  gd0_mb->SetMarkerColor(kRed);
  gd0_mb->SetMarkerStyle(22);
  gd0_mb->SetLineStyle(7);
  gd0->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}} #frac{d^{2}N}{dydp_{T}}[#frac{c^{2}}{GeV^{2}}]");
  gd0->GetXaxis()->SetTitle("p_{T} [GeV]");
  gd0->GetYaxis()->SetTitleOffset(0.85);
  gd0->GetYaxis()->SetRangeUser(4e-6, 1.);
  
  TLegend *leg = new TLegend(0.5,0.5,0.8,0.8);
  leg->AddEntry(gd0_mb,"D^{0} MB","LP");
  //leg->AddEntry(gd0,"Central5 #pi","LP");
  leg->AddEntry(gd0,"D^{0} 0-10\%","LP");
  
  gd0->Draw();
  gd0_mb->Draw("same");
  fd0->Draw("same");
  leg->Draw("same");
  //c11->SaveAs("D0_fit_MB.pdf");
  c11->SaveAs("D0_fit_MB_C5_comp.pdf");
  //=======================================================================
  
}
void norm(TH1F *h){
  double norm1 = h->Integral();
  int bins = h->GetNbinsX();
  for(int i=1; i<bins+1;i++){
    double temp = h->GetBinContent(i);
    double width = h->GetBinWidth(i);
    double err = h->GetBinError(i);
    h->SetBinContent(i,temp/norm1);
    h->SetBinError(i,0);//err/norm1);
  }
  
}



