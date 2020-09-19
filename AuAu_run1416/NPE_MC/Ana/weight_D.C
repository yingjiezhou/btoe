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

void weight_D(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  //gStyle->SetPadLeftMargin(2);
  TGaxis::SetMaxDigits(3);
  TVirtualFitter::SetDefaultFitter("Minuit2");

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
  //double yy4e[7]={0,0,0,0,0,0,0};
  TGraphErrors *gd0 = new TGraphErrors(7,xx4,yy4,xx4e,yy4e);
  TF1 *fd0 = new TF1("fd0",func1,0.315,20,3);
  fd0->SetParameter(0,1.44381e+01);
  fd0->SetParameter(1,0.11);
  fd0->SetParameter(2,1.10008e-01);
  //gd0->Fit(fd0);
  
  cout<<fd0->Integral(0, 20)<<endl;
  //=======================================================================
  
  TCanvas *c11 = new  TCanvas("c11","c11");
  c11->SetLogy();
  //c11->Divide(2);
  //c11->cd(1);
  gd0->Fit(fd0);
  gd0->SetMarkerColor(kBlue);
  gd0->SetLineColor(kBlue);
  gd0->Draw();
  fd0->Draw("same");
  /*
  c11->cd(2);
  gd0->Fit(fd0, "VE");
  gd0->Draw();
  //fd0->Draw("same");*/
  c11->SaveAs("D0_fit.pdf");
  //=======================================================================

  double width[7]={0.7,0.4,0.5,0.6,0.8,2}; //dpT, 粗略j估计的
  double sum=0;
  cout << "Doing sum" << endl;
  for(int i=0;i<7;i++){
    sum+=yy4[i]*xx4[i]*2*TMath::Pi()*width[i]*800000000;// to get yield,why
    cout << "Sum " << sum << endl;
  }
  cout << "Total sum " << sum << endl;
  //=======================================================================
  
  TH1F *Data = new TH1F("Data","Data",100,0,20);
  TH1F *Check = new TH1F("Check","Check",100,0,20);
  TH1F *Check1 = new TH1F("Check1","Check1",100,0,20);
  TH1F *Data_d = new TH1F("Data_d","Data_d",100,0,20);
  TH1F *Weight = new TH1F("Weight","Weight",100,0,20);
  for(int i = 1; i<Data->GetNbinsX()+1 ;i++){
    
    Data->SetBinContent(i,20000.);///(20./100.)/2./TMath::Pi()/Data->GetBinCenter(i));
    Check->SetBinContent(i,20000.);
    Check1->SetBinContent(i,20000.);
    Data_d->SetBinContent(i,fd0->Integral(Data_d->GetBinLowEdge(i),Data_d->GetBinLowEdge(i)+Data_d->GetBinWidth(i))*(20./100.)*2.*TMath::Pi()*Data_d->GetBinCenter(i)); // dN/dpT
    Data->SetBinError(i,0);
  }
  norm(Data);
  norm(Data_d);
  for(int i = 1; i<Data->GetNbinsX()+1 ;i++){
    
    double temp1=Data_d->GetBinContent(i);  //fd0->Eval(Data->GetBinCenter(i))/fd0->Integral(0,20);
    double temp2=Data->GetBinContent(i);
    if(temp2>0)Weight->SetBinContent(i,temp1/temp2);//
    else Weight->SetBinContent(i,1);
  }
  
  //=======================================================================

  TCanvas *c1 = new  TCanvas("c1","c1");
  Data_d->Draw();
  Data->Draw("PE same");
  c1->SaveAs("D0_sample.pdf");
  //=======================================================================

  TCanvas *c2 = new  TCanvas("c2","c2");
  //Weight->Scale( 800E6);
  Weight->Draw(); // 最后会用到的weight
  Check->Multiply(Weight); //看weight 之后是不是对的, 因为weight 已经是归一化了，所以这是
  Check->Draw("same");
  //=======================================================================

  cout << "Integral w/ no weights " << Check1->Integral() << endl;
  cout << "Integral w/ weights " << Check->Integral() << endl;
  cout <<  "Ratio with / without " << Check->Integral()/Check1->Integral() << endl;
  TFile fi("root_yj/D_Weights_Alt.root","RECREATE");
  Weight->Write("D_Weights");
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


