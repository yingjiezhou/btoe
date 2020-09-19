void norm(TH1F *h);
void weight_D_central_sys(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  //gStyle->SetPadLeftMargin(2);
  TGaxis::SetMaxDigits(3);
  
  TFile * inFile_D0=  new TFile("root_yj/D0_Spectra_Run14HFT.prc.root","READ");
  TGraphErrors *gd0=(TGraphErrors *) inFile_D0->Get("gD0_sys_0_10");
  //TGraphErrors *gd0s=(TGraphErrors *) inFile_D0->Get("gD0_sys_0_10");

  //=======================================================================
  //int npoint = gd0->GetN();
  Double_t xx4[11];
  Double_t xx4e[11];
  Double_t yy4[11];
  Double_t yy4e[11];
  //Double_t *fY_err_sys[11];
  for(int i=0;i<gd0->GetN();i++){
    gd0->GetPoint(i,xx4[i], yy4[i]);
    xx4e[i]=0;
    yy4e[i] = gd0->GetErrorY(i);
    //fY_err_sys[i] = gd0s->GetErrorY(i);
  }
  
  double yy41[11];
  double yy42[11];
  for(auto i=0; i<11; i++){
    if(i<6){
      yy41[i]=yy4[i]+yy4e[i];
      yy42[i]=yy4[i]-yy4e[i];
    }else{
      yy41[i]=yy4[i]-yy4e[i];
      yy42[i]=yy4[i]+yy4e[i];
    }
  }
  
  TGraphErrors *gd01 = new TGraphErrors(11,xx4,yy41,xx4e,yy4e); // soft
  TGraphErrors *gd02 = new TGraphErrors(11,xx4,yy42,xx4e,yy4e);
  
  //=======================================================================
  
  TF1 *fd0= new TF1("fd0","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,20);
  fd0->SetParameter(0,2.66458e+01);
  fd0->SetParameter(1,3.39421e-01);
  fd0->SetParameter(2,1.33430e+01);
  
  TF1 *fd01= new TF1("fd01","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,20);
  fd01->SetParameter(0,2.66458e+01);
  fd01->SetParameter(1,3.39421e-01);
  fd01->SetParameter(2,1.33430e+01);
  
  TF1 *fd02= new TF1("fd02","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,20);
  fd02->SetParameter(0,2.66458e+01);
  fd02->SetParameter(1,3.39421e-01);
  fd02->SetParameter(2,1.33430e+01);
  
  //=======================================================================
  
  TCanvas *c11 = new  TCanvas("c11","c11");
  c11->SetLogy();
  gd0->GetYaxis()->SetRangeUser(1e-6, 1e0);
  gd0->Fit(fd0);
  gd01->Fit(fd01); // soft
  gd02->Fit(fd02);
  gd0->SetMarkerColor(kBlack);
  //gd0->SetLineColor(kBlue);
  gd0->Draw("AP");
  fd0->Draw("same");
  fd01->SetLineStyle(9);
  fd01->Draw("same");
  fd02->SetLineStyle(9);
  fd02->Draw("same");
  c11->SaveAs("D0_fit_6.pdf");
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
    Data_d->SetBinContent(i,fd02->Integral(Data_d->GetBinLowEdge(i),Data_d->GetBinLowEdge(i)+Data_d->GetBinWidth(i))*(20./100.)*2.*TMath::Pi()*Data_d->GetBinCenter(i)); // dN/dpT
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
  
  TFile fi("root_yj/D_Weights_Alt_c5_hard.root","RECREATE");
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

