 void norm(TH1D *h);
void getHist(TH1D* h,TF1 *f);
void GetRatio(){
  
  //gStyle->SetOptStat(00000);
  //gStyle->SetTitleSize(0.05,"XY");
  //gStyle->SetTitleFontSize(0.06);
  //gStyle->SetTitleOffset(1.3,"X");
  //gStyle->SetTitleOffset(1,"Y");
  //gStyle->SetPadTopMargin(0.03);
  //gStyle->SetPadRightMargin(0.02);
  //gStyle->SetPadBottomMargin(0.13);
  //gStyle->SetPadLeftMargin(0.13);
  //gStyle->SetPadTickY(1);
  //gStyle->SetPadTickX(1);
  TFile * inFile_D0=  new TFile("root_yj/D0_Spectra_Run14HFT.prc.root","READ");
  TFile * inFile_Dp=  new TFile("root_yj/Dpm_spectra_run14HFT.root","READ");
  
  TF1 *flevy_0_10=(TF1 *)inFile_D0->Get("flevy_0_10");
  TF1 *mflevy_0_10=(TF1 *)inFile_Dp->Get("mflevy_0_10");
  //TF1 *flevy_0_10= new TF1("flevy_0_10","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.864500*([2]-2)))*   TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.864500*1.864500)-1.864500)/([2]*[1]),-[2])",0,20);
  //TF1 *mflevy_0_10= new TF1("mflevy_0_10","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.869300*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.869300*1.869300)-1.869300)/([2]*[1]),-[2])",0,20);

  //mflevy_0_10->Draw();
  //flevy_0_10->Draw("same");
  //flevy_0_10->Draw();
  //mflevy_0_10->Draw("same");
  //TF1 h("h","mflevy_0_10/flevy_0_10",0,10);
  //h.Draw();
  //return ;
  
  //TH1D* h_levy_Dp_0_10  = new TH1D("h_levy_Dp_0_10","h_levy_Dp_0_10",60,2,8);h_levy_Dp_0_10->Sumw2();
  //TH1D* h_levy_D0_0_10  = new TH1D("h_levy_D0_0_10","h_levy_D0_0_10",60,2,8);h_levy_D0_0_10->Sumw2();
  //getHist(h_levy_Dp_0_10,mflevy_0_10); // 把fit 得到的r图线转换成hist
  //getHist(h_levy_D0_0_10,flevy_0_10);
  //h_levy_Dp_0_10->Divide(h_levy_D0_0_10);
  //h_levy_Dp_0_10->Draw();
  //cout<<h_levy_Dp_0_10->Integral()<<endl;
  //cout<<h_levy_Dp_0_10->GetNbinsX()<<endl;
  //cout<<h_levy_Dp_0_10->Integral()/h_levy_Dp_0_10->GetNbinsX()<<endl; 
  //return ;

  flevy_0_10->SetParameter(0,2.66458e+01);
  flevy_0_10->SetParameter(1,3.39421e-01);
  flevy_0_10->SetParameter(2,1.33430e+01);
  
  mflevy_0_10->SetParameter(0,2.66458e+01);
  mflevy_0_10->SetParameter(1,3.39421e-01);
  mflevy_0_10->SetParameter(2,1.33430e+01);
//=====================================================================================
  
  TGraphErrors *D0_0_10_err=(TGraphErrors *) inFile_D0->Get("gD0_err_0_10");
  TGraphErrors *D0_0_10_sys=(TGraphErrors *) inFile_D0->Get("gD0_sys_0_10");
  for(int i=0;i<D0_0_10_err->GetN();i++)
  {
    Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999,y_sys;
    D0_0_10_sys->GetPoint(i,x_central,y_central);
    y_sys=D0_0_10_sys->GetErrorY(i);
    y_err=D0_0_10_err->GetErrorY(i);
    
    D0_0_10_sys->SetPoint(i,x_central,y_central);
    D0_0_10_sys->SetPointError(i,0,sqrt(y_err*y_err+y_sys*y_sys));
  }
  //D0_0_10_sys->Draw();
  D0_0_10_sys->Fit("flevy_0_10","R","",0,10);
  /*
  TCanvas *cD0=new TCanvas("cD0","",1000,800);
  gPad->SetLogy();
  TLegend *legend_D0  = new TLegend(0.55,0.65,0.9,0.85);
  legend_D0 ->AddEntry(D0_0_10_sys,"D^{0} Data 0-10%","PE");
  legend_D0 ->AddEntry(flevy_0_10,"Levy Fit D^{0}","L");
  D0_0_10_sys->Draw();
  flevy_0_10->Draw("same");
  legend_D0->Draw("same");
  cD0->SaveAs("Plots/Dp0.pdf");*/
  //=====================================================================================
  
  TGraphErrors *Dpm_0_10_sys=(TGraphErrors *) inFile_Dp->Get("Dpm_spectra_sys_0_10");
  TGraphErrors *Dpm_0_10_err=(TGraphErrors *) inFile_Dp->Get("Dpm_spectra_err_0_10");

  for(int i=0;i<Dpm_0_10_err->GetN();i++)
  {
    Double_t x_central=-999,y_central=-999,x_err=-999,y_err=-999,y_sys;
    Dpm_0_10_sys->GetPoint(i,x_central,y_central);
    y_sys=Dpm_0_10_sys->GetErrorY(i);
    y_err=Dpm_0_10_err->GetErrorY(i);
    
    Dpm_0_10_sys->SetPoint(i,x_central,y_central);
    Dpm_0_10_sys->SetPointError(i,0,sqrt(y_err*y_err+y_sys*y_sys));
  }
  //D0_0_10_sys->Draw();
  Dpm_0_10_sys->Fit("mflevy_0_10","R","",0,10);
  /*
  TCanvas *cDpm=new TCanvas("cDpm","",1000,800);
  gPad->SetLogy();
  TLegend *legend_Dpm  = new TLegend(0.55,0.65,0.9,0.85);
  legend_Dpm ->AddEntry(Dpm_0_10_sys,"D^{+} Data 0-10%","PE");
  legend_Dpm ->AddEntry(mflevy_0_10,"Levy Fit D^{+}","L");
  Dpm_0_10_sys->Draw();
  mflevy_0_10->Draw("same");
  legend_Dpm->Draw("same");
  cDpm->SaveAs("Plots/Dpm.pdf");*/
  //=====================================================================================
  //TF1 *ratio = new TF1("ratio","mflevy_0_10/flevy_0_10",0,10);
  //ratio->Draw();
  
}


void norm(TH1D* h){
  double norm1 = h->Integral();
  for(int i = 1 ; i < h->GetNbinsX()+1 ; i++){
    double temp = h->GetBinContent(i);
    double width = h->GetBinWidth(i);
    double err = 0;//sqrt(temp);//h->GetBinError(i);
    h->SetBinContent(i,temp/norm1);
    h->SetBinError(i,err/norm1);
  }
}
void getHist(TH1D* h,TF1 *f){
  for(int i = 1; i < h->GetNbinsX()+1 ; i++){
    double temp1 = h->GetBinCenter(i);
    double temp2 = h->GetBinLowEdge(i);
    double temp3 = h->GetBinLowEdge(i)+h->GetBinWidth(i);
    double temp4 = f->Integral(temp2,temp3);//*2*TMath::Pi()*temp1/h->GetBinWidth(i);//*temp1;//h->GetBinWidth(i)*temp1;
    h->SetBinContent(i,temp4);
    }
}
