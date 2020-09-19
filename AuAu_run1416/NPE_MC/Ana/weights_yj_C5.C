void data_MB(TGraphErrors *gpi,TGraphErrors *ggamma);
void data_C5(TGraphErrors *gpi_c5);
void data_C5M(TMultiGraph *gmpi_c5);
void data_12C5(TGraphErrors *gpi);
Double_t func(Double_t *x, Double_t *par);
Double_t func3(Double_t *x, Double_t *par);
Double_t func1(Double_t *x, Double_t *par);
Double_t func2(Double_t *x, Double_t *par);
void norm(TH1D *h);
void norm1(TH1D *h);

void getHist(TH1D* h,TF1 *f);

//======================================================================================================

void weights_yj_C5(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  //gStyle->SetPadLeftMargin(2);
  TGaxis::SetMaxDigits(3);
  //============================================================================
  
  double xx3[11]={0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.25,3,4.25};
  double yy3[11]={1.229721,1.145734,1.172174,1.172357,1.211729,1.201061,1.234643,1.223676,1.225788,1.307334,1.363853};
  double xx3e[11]={0,0,0,0,0,0,0,0,0,0,0};
  double yy3e[11]={0.0825,0.0732,0.0737,0.0727,0.0759,0.0769,0.0797,0.0826,0.0804,0.0883,0.1258};
  double pully[31];
  double pully2[24];
  double pullye[31];
  double pullye2[24];
  
  double xx4[7]={3.15e-01,9.68e-01,1.35,1.89,2.56,3.75,5.88};
  double yy4[7]={4.16e-02*2*TMath::Pi()*3.15e-01
    ,3.59e-02*2*TMath::Pi()*9.68e-01
    ,2.48e-02*2*TMath::Pi()*1.35
    ,9.50e-03*2*TMath::Pi()*1.89
    ,2.00e-03*2*TMath::Pi()*2.56
    ,2.32e-04*2*TMath::Pi()*3.75
    ,6.65e-06*2*TMath::Pi()*5.88};
  double xx4e[7]={0,0,0,0,0,0,0};
  double yy4e[7]={0.010026464980241,0.0081608,0.0047634,0.00194612,0.00048301,0.00005131,0.00000186};
  
  TGraphErrors *gpi = new TGraphErrors();
  TGraphErrors *ggamma = new TGraphErrors();
  data_MB(gpi,ggamma);
 
  
  TGraphErrors *gd0 = new TGraphErrors(7,xx4,yy4,xx4e,yy4e);
  TGraphErrors *grat = new TGraphErrors(11,xx3,yy3,xx3e,yy3e);
  
  TGraphErrors *gpi_c5 = new TGraphErrors(); // 0905
  data_C5(gpi_c5);
  TGraphErrors *gpi_12C5 = new TGraphErrors();
  data_12C5(gpi_12C5);
  
  auto *gmpi_c5 = new TMultiGraph();
  data_C5M(gmpi_c5);
  //======================================================================================================

  //int const numPtBins=10;
  //double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5,20};
  int const numPtBins=200;
  double binning[numPtBins+1];
  for(int i =0 ;i<numPtBins+1;i++){
    binning[i]=i*20./200.;
  }
  TH1F* ratio =  new TH1F("ratio","ratio",numPtBins,binning);
  
  //TFile * f= new TFile("root/Gen_full.root");
  TFile * f= new TFile("root_yj/NewWeights_yj_central5_v3.root");
  auto write_gamma=((TH2D*)f->Get("write_gamma"))->ProjectionY(); // parent pt
  auto write_pi0=((TH2D*)f->Get("write_pi0"))->ProjectionY();
  
  write_pi0->SetMarkerColor(kRed);
  write_gamma->SetMarkerColor(kRed);
  write_pi0->SetMarkerStyle(22);
  
  write_gamma->SetMarkerStyle(22);
  write_pi0->SetLineColor(kRed);
  write_gamma->SetLineColor(kRed);
  
  TFile * fmb= new TFile("root_yj/NewWeights_yj_full.root");
  auto write_pi0_mb=((TH2D*)fmb->Get("write_pi0"))->ProjectionY();
  write_pi0_mb->SetMarkerColor(kGreen-2);
  write_pi0_mb->SetMarkerStyle(22);

  
  auto gen_gamma=((TH2D*)f->Get("gen_gamma"))->ProjectionY();
  auto gen_pi0=((TH2D*)f->Get("gen_pi0"))->ProjectionY();
  //gen_gamma->Rebin();
  //gen_pi0->Rebin();
  
  //norm(gen_gamma);
 // norm(gen_pi0);
  norm(write_pi0);
  norm(write_pi0_mb);
  norm(write_gamma);
  
  TH1F * pi0_weights = new TH1F("pi0_weights","pi0_weights",200,0,20);
  TH1F * D0_weights = new TH1F("D0_weights","D0_weights",200,0,20);
  TH1F * gamma_weights = new TH1F("gamma_weights","gamma_weights",200,0,20);
  
  for(int i = 1; i< gen_gamma->GetNbinsX()+1;i++){
    double temp1 = gen_gamma->GetBinContent(i);
    double temp11 = gen_gamma->GetBinError(i);
    double temp2 = gen_gamma->GetBinCenter(i);
    double temp3 = gen_pi0->GetBinContent(i);
    double temp33 = gen_pi0->GetBinError(i);
    double temp4 = gen_pi0->GetBinCenter(i);
    gen_gamma->SetBinContent(i,1./2./3.14*temp1/temp2/1.4/gen_gamma->GetBinWidth(i));
    gen_gamma->SetBinError(i,1./2./3.14*temp11/temp2/1.4/gen_gamma->GetBinWidth(i));
    gen_pi0->SetBinContent(i,1./2./3.14*temp3/temp4/1.4/gen_pi0->GetBinWidth(i));
    gen_pi0->SetBinError(i,1./2./3.14*temp33/temp4/1.4/gen_pi0->GetBinWidth(i));
  }
 //======================================================================================================
  
  TF1 *fpi = new TF1("fpi",func,0.1,20,3);
  fpi->SetParameter(0,1.44381e+04);
  fpi->SetParameter(1,9.18928e-01);
  fpi->SetParameter(2,1.10008e-01);
  
  TF1 *fpi_c5 = new TF1("fpi_c5",func,0.1,20,3);
  fpi_c5->SetParameter(0,1.44381e+04);
  fpi_c5->SetParameter(1,9.18928e-01);
  fpi_c5->SetParameter(2,1.10008e-01);
  
  TF1 *fpi12_c5 = new TF1("fpi12_c5",func,0.1,20,3);
  //fpi12_c5->SetParameter(0,1.44381e+04);
  //fpi12_c5->SetParameter(1,9.18928e-01);
  //fpi12_c5->SetParameter(2,1.10008e-01);

  fpi12_c5->SetParameter(0,15000);
  fpi12_c5->SetParameter(1,1.);
  fpi12_c5->SetParameter(2,0.1);

  
  TF1 *fmpi_c5 = new TF1("fmpi_c5",func,0.1,20,3);
  fmpi_c5->SetParameter(0,1.44381e+04);
  fmpi_c5->SetParameter(1,9.18928e-01);
  fmpi_c5->SetParameter(2,1.10008e-01);
  
  
  TF1 *fd0 = new TF1("fd0",func,0.1,20,3);
  //fd0->SetParameter(0,1.44381e+04);
  //fd0->SetParameter(1,9.18928e-01);
  fd0->SetParameter(2,1.10008e-01);
  TF1 *fgamma = new TF1("fgamma",func1,1,20,3);
  fgamma->SetParameter(0,7.38384e+08);
  fgamma->SetParameter(1,8.73512e-01);
  fgamma->SetParameter(2,9.10666e-03);
  TF1 *fpimc = new TF1("fpimc",func,0.1,20,3);
  fpimc->SetParameter(0,1.44381e+04);
  fpimc->SetParameter(1,9.18928e-01);
  fpimc->SetParameter(2,1.10008e-01);
  TF1 *fgammamc = new TF1("fgammamc",func1,1,20,3);
  fgammamc->SetParameter(0,7.38384e+08);
  fgammamc->SetParameter(1,8.73512e-01);
  fgammamc->SetParameter(2,9.10666e-03);
  
  TF1 *fratio = new TF1("fratio",func2,0.1,20,6);
  fratio->SetParameter(0,1.44381e+04);
  fratio->SetParameter(1,9.18928e-01);
  fratio->SetParameter(2,1.10008e-01);
  fratio->SetParameter(3,7.38384e+08);
  fratio->SetParameter(4,8.73512e-01);
  fratio->SetParameter(5,9.10666e-03);
  //============================================================================
  
  gpi->Fit(fpi,"r"); // fit from data point zyj

  
  //============================================================================
  /*
  TCanvas *c1w = new TCanvas("c1w","c1w");
  TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
  TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
  pad1->SetBottomMargin(0.02);
  pad1->SetTopMargin(0.08);
  pad2->SetTopMargin(0.015);
  pad2->SetBottomMargin(0.5);
  pad2->SetBorderMode(0);
  pad1->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  pad1->SetLogy();
  //gpi->GetYaxis()->SetRangeUser(10e-9,1000);
  //gpi->Fit(fpi,"r"); // fit from data point zyj
  
   //gpi_c5->GetYaxis()->SetRangeUser(10e-9,1000);
   //gpi_c5->SetMarkerColor(kBlack);
   //gpi_c5->SetMarkerStyle(21);
   //gpi_c5->Fit(fpi_c5,"r");
  
  gpi_12C5->Fit(fpi12_c5,"r");
  //gmpi_c5->SetMarkerColor(4);
  //gmpi_c5->SetMarkerStyle(20);
  
  int bin = gen_pi0->FindBin(0.4);
  write_pi0->Scale(fpi12_c5->Integral(0,20)*2*3.14*1.4);
  
   //fpi->SetLineColor(kBlue);
   //fpi_c5->SetLineColor(kOrange);
   //gpi->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}} #frac{d^{2}N}{dydp_{T}} [#frac{c^{2}}{GeV^{2}}]");
   //gpi->GetYaxis()->SetTitleOffset(0.85);
   
   //gpi->Draw("APE");
  //write_pi0->Draw("PE");
  //fpi->Draw("l same");
  //gpi_c5->Draw("PE same");
  //fpi_c5->Draw("l same");
  //gmpi_c5->Draw("PE same");
  gpi_12C5->Draw();
  fpi12_c5->Draw("l same");
  
  pad2->cd();
  double xp[31], xxep[31];
  for(int i = 0; i<31;i++){
    xp[i]= (gpi_12C5->GetX())[i];
    xxep[i]=(gpi_12C5->GetErrorX(i));
    auto b= (gpi_12C5->GetY())[i];
    auto be=(gpi_12C5->GetErrorY(i));
    //cout<<a<<b<<ae<<be<<endl;
    pully[i] = (fpi12_c5->Eval(xp[i]))/b;
    pullye[i] = (fpi12_c5->Eval(xp[i])/b)*sqrt(be/b);
  }
  
  TGraphErrors *gpi_p = new TGraphErrors(31,xp,pully,xxep,pullye);
  gpi_p->GetXaxis()->SetTitle("p_{T} [GeV]");
  gpi_p->GetYaxis()->SetTitle("Fit/Data");
  gpi_p->SetTitle(0);
  gpi_p->GetYaxis()->SetTitleSize(0.15);
  gpi_p->GetYaxis()->SetLabelSize(0.1);
  gpi_p->GetYaxis()->CenterTitle();
  gpi_p->GetYaxis()->SetTitleOffset(0.3);
  gpi_p->GetYaxis()->SetNdivisions(505);
  gpi_p->GetYaxis()->SetRangeUser(0,1.7);
  gpi_p->GetXaxis()->SetTitleSize(0.3);
  gpi_p->GetXaxis()->SetLabelSize(0.15);
  gpi_p->GetXaxis()->SetTitleOffset(0.63);
  gpi_p->Draw("APE");
  TF1 *fline = new TF1("fline","1",0,20);
  fline->SetLineStyle(7);
  fline->Draw("same");
  c1w->SaveAs("pi_spectrum_comp_3.pdf");
  */
  //============================================================================
  
  TCanvas *cpi = new TCanvas("cpi","cpi");
  TPad *pad11 = new TPad("pad11","pad11",0.0,0.25,1.0,1.0);
  TPad *pad21 = new TPad("pad21","pad21",0.0,0.0,1.0,0.255);
  pad11->SetBottomMargin(0.02);
  pad11->SetTopMargin(0.08);
  pad21->SetTopMargin(0.015);
  pad21->SetBottomMargin(0.5);
  pad21->SetBorderMode(0);
  pad11->SetBorderMode(0);
  pad11->Draw();
  pad21->Draw();
  pad11->cd();
  pad11->SetLogy();
  gpi_12C5->Fit(fpi12_c5,"r");
  //TLatex lat2;
  //lat2.DrawLatex(8,1,"Central5 #pi");
  
  TLegend *leg = new TLegend(0.5,0.5,0.92,0.92);
  leg->AddEntry(write_pi0_mb,"MB weighted #pi","LP");
  //leg->AddEntry(write_pi0,"Central5 weighted #pi","LP");
  leg->AddEntry(write_pi0,"Scaled Central5 weighted #pi","LP");
  leg->AddEntry(fpi12_c5,"Central5 fit #pi","LP");

  int bin = gen_pi0->FindBin(0.4);
  write_pi0->Scale(fpi12_c5->Integral(0,20)*2*3.14*1.4);// norm 之后，就为1 了，只有乘上之前fit 函数在（0，20）的积分，才能和gpi_12C5进行对比
  write_pi0_mb->Scale(fpi->Integral(0,20)*2*3.14*1.4);
  //cout<<"central5 to mb ratio is : "<<write_pi0->Integral(0, 20)/write_pi0_mb->Integral(0, 20)<<endl;
  int pt2 = write_pi0->FindBin(2.);
  int pt20 = write_pi0->FindBin(20.);
  cout<<"central5 to mb ratio in pt 2 is: "<<write_pi0->GetBinContent(pt2)/write_pi0_mb->GetBinContent(pt2)<<endl;
  double ra = write_pi0->GetBinContent(pt2)/write_pi0_mb->GetBinContent(pt2);
  cout<<"central5 to mb ratio is : "<<write_pi0->Integral(pt2, pt20)/write_pi0_mb->Integral(pt2, pt20)<<endl;
  write_pi0->Scale(1./ra);
  
  //gmpi_c5->Fit(fmpi_c5, "r");
  fpi12_c5->SetLineColor(kBlue);
  gpi_12C5->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}} #frac{d^{2}N}{dydp_{T}} [#frac{c^{2}}{GeV^{2}}]");
  gpi_12C5->GetYaxis()->SetTitleOffset(0.85);
  gpi_12C5->GetYaxis()->SetRangeUser(10e-9,100);
  
  gpi_12C5->Draw("APE");
  write_pi0->Draw("PE same");
  write_pi0_mb->Draw("PE same");
  fpi12_c5->Draw("l same");
  leg->Draw("same");
  pad21->cd();
  
  double xp1[31], xxep1[31];
  double pully1[31],pullye1[31];
  for(int i = 0; i<31;i++){
    xp1[i]= (gpi_12C5->GetX())[i];
    xxep1[i]=(gpi_12C5->GetErrorX(i));
    auto b= (gpi_12C5->GetY())[i];
    auto be=(gpi_12C5->GetErrorY(i));
    //cout<<xp1[i]<<" is     "<<b<<endl;
    pully1[i] = (fpi12_c5->Eval(xp1[i]))/b;
    pullye1[i] = (fpi12_c5->Eval(xp1[i])/b)*sqrt(be/b);
  }
  
  TGraphErrors *gpi_p1 = new TGraphErrors(31,xp1,pully1,xxep1,pullye1);
  gpi_p1->GetXaxis()->SetTitle("p_{T} [GeV]");
  gpi_p1->GetYaxis()->SetTitle("Fit/Data");
  gpi_p1->SetTitle(0);
  gpi_p1->GetYaxis()->SetTitleSize(0.15);
  gpi_p1->GetYaxis()->SetLabelSize(0.1);
  gpi_p1->GetYaxis()->CenterTitle();
  gpi_p1->GetYaxis()->SetTitleOffset(0.3);
  gpi_p1->GetYaxis()->SetNdivisions(505);
  gpi_p1->GetYaxis()->SetRangeUser(0,1.7);
  gpi_p1->GetXaxis()->SetTitleSize(0.3);
  gpi_p1->GetXaxis()->SetLabelSize(0.15);
  gpi_p1->GetXaxis()->SetTitleOffset(0.63);
  gpi_p1->Draw("APE");
  TF1 *fline = new TF1("fline","1",0,20);
  fline->SetLineStyle(7);
  fline->Draw("same");
  cpi->SaveAs("pi_spectrum_pi_12C5_v3.pdf");
  //============================================================================
  
/*
  
  TCanvas *cpim = new TCanvas("cpim","cpim");
  TPad *pad111 = new TPad("pad111","pad111",0.0,0.25,1.0,1.0);
  TPad *pad211 = new TPad("pad211","pad211",0.0,0.0,1.0,0.255);
  pad111->SetBottomMargin(0.02);
  pad111->SetTopMargin(0.08);
  pad211->SetTopMargin(0.015);
  pad211->SetBottomMargin(0.5);
  pad211->SetBorderMode(0);
  pad111->SetBorderMode(0);
  pad111->Draw();
  pad211->Draw();
  pad111->cd();
  pad111->SetLogy();
  //gmpi_c5->Fit(fmpi_c5,"r");
  fmpi_c5->SetLineColor(kRed);
  fmpi_c5->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}} #frac{d^{2}N}{dydp_{T}} [#frac{c^{2}}{GeV^{2}}]");
  //fmpi_c5->GetYaxis()->SetTitleOffset(0.85);
  fpi->Draw();
  fmpi_c5->Draw("same");
  
  pad211->cd();
  TH1D* hpi  = new TH1D("hpi","hpi",80,2,15);hpi->Sumw2();
  TH1D* hmpi_c5  = new TH1D("hmpi_c5","hmpi_c5",80,2,15);hmpi_c5->Sumw2();
  getHist(hmpi_c5,fmpi_c5); // 把fit 得到的r图线转换成hist
  getHist(hpi,fpi);
  norm1(hmpi_c5);
  norm1(hpi);
  hpi->Divide(hmpi_c5);
  hpi->Draw();
  hpi->GetXaxis()->SetTitle("p_{T} [GeV]");
  hpi->GetYaxis()->SetTitle("MB/Central5");
  hpi->SetTitle(0);
  hpi->GetYaxis()->SetTitleSize(0.15);
  hpi->GetYaxis()->SetLabelSize(0.1);
  hpi->GetYaxis()->CenterTitle();
  hpi->GetYaxis()->SetTitleOffset(0.3);
  hpi->GetYaxis()->SetNdivisions(505);
  hpi->GetYaxis()->SetRangeUser(0,1.7);
  hpi->GetXaxis()->SetTitleSize(0.3);
  hpi->GetXaxis()->SetLabelSize(0.15);
  hpi->GetXaxis()->SetTitleOffset(0.63);
  fline->Draw("same");
  cpim->SaveAs("pi_spectrum_pim.pdf");
*/
/*
  pad211->cd();
  
  double mxp1[11], mxxep1[11];
  double mpully1[11],mpullye1[11];
  for(int i = 0; i<11;i++){
    mxp1[i]= (gmpi_c5->GetX())[i];
    mxxep1[i]=(gmpi_c5->GetErrorX(i));
    auto b= (gmpi_c5->GetY())[i];
    auto be=(gmpi_c5->GetErrorY(i));
    //cout<<a<<b<<ae<<be<<endl;
    mpully1[i] = (fmpi_c5->Eval(mxp1[i]))/b;
    mpullye1[i] = (fmpi_c5->Eval(mxp1[i])/b)*sqrt(be/b);
  }
  
  TGraphErrors *gpi_p1m = new TGraphErrors(11,mxp1,mpully1,mxxep1,mpullye1);
  gpi_p1m->GetXaxis()->SetTitle("p_{T} [GeV]");
  gpi_p1m->GetYaxis()->SetTitle("Fit/Data");
  gpi_p1m->SetTitle(0);
  gpi_p1m->GetYaxis()->SetTitleSize(0.15);
  gpi_p1m->GetYaxis()->SetLabelSize(0.1);
  gpi_p1m->GetYaxis()->CenterTitle();
  gpi_p1m->GetYaxis()->SetTitleOffset(0.3);
  gpi_p1m->GetYaxis()->SetNdivisions(505);
  gpi_p1m->GetYaxis()->SetRangeUser(0,1.7);
  gpi_p1m->GetXaxis()->SetTitleSize(0.3);
  gpi_p1m->GetXaxis()->SetLabelSize(0.15);
  gpi_p1m->GetXaxis()->SetTitleOffset(0.63);
  gpi_p1m->Draw("APE");
  //TF1 *fline = new TF1("fline","1",0,20);
  //fline->SetLineStyle(7);
  fline->Draw("same");
  //cpim->SaveAs("pi_spectrum_pim.pdf");
  */
}
//======================================================================================================

void norm(TH1D *h){
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

void norm1(TH1D *h){
  double norm11 = h->Integral(2, 10);
  int bins = h->GetNbinsX();
  for(int i=1; i<bins+1;i++){
    double temp = h->GetBinContent(i);
    double width = h->GetBinWidth(i);
    double err = h->GetBinError(i);
    h->SetBinContent(i,temp/norm11);
    h->SetBinError(i,0);//err/norm1);
  }
}

Double_t func(Double_t *x, Double_t *par){
  Double_t arg = 0;
  Double_t val = 0;
  if(par[2]!=0 && par[1]!=1){
    arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
    val = par[0]*sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1]));//exp(arg*(1/(1-par[1])));
  }
  return val;
}
Double_t func3(Double_t *x, Double_t *par){
  Double_t arg = 0;
  Double_t val = 0;
  if(par[2]!=0 && par[1]!=1){
    arg = 1+sqrt(x[0]*x[0]+1864.84*1864.84)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
    val = par[0]*sqrt(x[0]*x[0]+1864.84*1864.84)*TMath::Power(arg,-1/(1-par[1]));//exp(arg*(1/(1-par[1])));
  }
  return val;
}
Double_t func1(Double_t *x, Double_t *par){
  Double_t arg = 0;
  Double_t val = 0;
  if(par[2]!=0 && par[1]!=1){
    arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
    val = par[0]*(sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1])));//exp(arg*(1/(1-par[1])));
  }
  return val;
}
Double_t func2(Double_t *x, Double_t *par){
  Double_t arg = 0;
  Double_t val = 0;
  if(par[2]!=0 && par[1]!=1){
    arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
    val = par[0]*(sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1])));//exp(arg*(1/(1-par[1])));
  }
  Double_t arg1 = 0;
  Double_t val1 = 0;
  if(par[5]!=0 && par[4]!=1){
    arg1 = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[5]*(1-par[4]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
    val1 = par[3]*(sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg1,-1/(1-par[4])));//exp(arg*(1/(1-par[1])));
  }
  return val/val1;
}
//======================================================================================================

void data_C5(TGraphErrors *gpi_c5){
  double xx[19] = {1.25, 1.75, 2.25, 2.75, 3.25, 3.75, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.25, 7.75, 8.25, 8.75, 9.25, 9.75, 11};
   double xxe[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  double yy[19] = {3.039, 0.5591, 0.118, 0.02268, 0.00556, 0.0017, 0.0005783, 0.0002331, 9.258e-05, 4.647e-05, 2.217e-05, 1.299e-05, 7.239e-06, 4.109e-06, 2.452e-06, 1.491e-06, 9.71e-07, 7.603e-07, 2.597e-07};
  double yye[19] = {0.06038, 0.009532, 0.002011, 0.0004268, 0.0001184, 4.043e-05, 1.571e-05, 7.008e-06, 3.271e-06, 1.87e-06, 9.21e-07, 4.577e-07, 2.935e-07, 1.802e-07, 1.264e-07, 9.348e-08, 7.222e-08, 6.163e-08, 1.846e-08};
  for(int i = 1; i<19+1; i++){
    gpi_c5->SetPoint(i-1,xx[i-1],yy[i-1]);
    gpi_c5->SetPointError(i-1,xxe[i-1],yye[i-1]);
  }
}
void data_C5M(TMultiGraph *gmpi_c5){
  double xx[19] = {1.25, 1.75, 2.25, 2.75, 3.25, 3.75, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.25, 7.75, 8.25, 8.75, 9.25, 9.75, 11};
  double xxe[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  double yy[19] = {3.039, 0.5591, 0.118, 0.02268, 0.00556, 0.0017, 0.0005783, 0.0002331, 9.258e-05, 4.647e-05, 2.217e-05, 1.299e-05, 7.239e-06, 4.109e-06, 2.452e-06, 1.491e-06, 9.71e-07, 7.603e-07, 2.597e-07};
  double yye[19] = {0.06038, 0.009532, 0.002011, 0.0004268, 0.0001184, 4.043e-05, 1.571e-05, 7.008e-06, 3.271e-06, 1.87e-06, 9.21e-07, 4.577e-07, 2.935e-07, 1.802e-07, 1.264e-07, 9.348e-08, 7.222e-08, 6.163e-08, 1.846e-08};
  TGraphErrors *gr1 = new TGraphErrors(19,xx,yy,xxe,yye);

  double xx2[11]={5.25, 5.75, 6.25, 6.75, 7.25, 7.75, 8.25, 8.75, 9.25, 9.75, 11};
  double xx2e[11]={0,0,0,0,0,0,0,0,0,0,0};
  double yy2[11]={9.3942e-05, 4.5241e-05, 2.2734e-05, 1.2533e-05, 6.8618e-06, 4.1642e-06, 2.5978e-06, 1.5449e-06, 1.1183e-06, 7.6839e-07, 2.8374e-07};
  double yy2e[11]={8.6757e-07, 5.1663e-07, 3.2479e-07, 2.1669e-07, 1.4735e-07, 1.061e-07, 7.8155e-08, 5.7515e-08, 4.4668e-08, 3.5421e-08, 9.6036e-09};
  TGraphErrors *gr2 = new TGraphErrors(11, xx2,yy2,xx2e,yy2e);
  
  gr1->SetMarkerColor(kGreen+2);
  gr2->SetMarkerColor(6);

  gmpi_c5->Add(gr1);
  gmpi_c5->Add(gr2);
  
}
void data_MB(TGraphErrors *gpi,TGraphErrors *ggamma){
  double xx[31] = {3.50E-01,4.50E-01,5.50E-01,6.50E-01,7.50E-01,8.50E-01,9.50E-01,1.05E+00,1.15E+00,1.30E+00,1.50E+00,1.70E+00,1.90E+00,2.10E+00,2.35E+00, 2.63E+00,2.75E+00,2.88E+00,3.13E+00,3.38E+00,3.50E+00,3.63E+00,3.88E+00,4.25E+00,4.75E+00,5.25E+00,5.75E+00,6.50E+00,7.50E+00,9.00E+00,1.10E+01};
  double xxe[31] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  double yy[31] = {4.26E+01,2.56E+01,1.56783E+01,9.86E+00,6.31E+00,4.06E+00,2.65955E+00,1.771909E+00,1.17E+00,6.57E-01,3.1908E-01,1.56E-01,7.9025E-02,4.78E-02,2.13E-02,1.06E-02,7.48E-03,5.46E-03,2.834199E-03,1.55E-03,1.30E-03,8.70E-04,5.02E-04,2.41E-04,9.53E-05,4.10355E-05,1.79E-05,7.28139E-06,2.21749E-06,6.40E-07,1.10E-07};
  double yye[31] = {10.1257582925922,6.16275449454219,3.81753930693582,
    2.40996433998514,
    1.54802814250904,
    1.39443326480689,
    0.916378595341467,
    0.609412815749718,
    0.332821598457792,
    0.196180555611406,
    0.0864041347390274,
    0.0421343731411777,
    0.0217992660426905,
    0.0223785889635607,
    0.0102306500770968,
    0.00343786998008942,
    0.000585375921951014,
    0.00319489407336143,
    0.00160680456807914,
    0.00082073041134102,
    0.000433909716991911,
    0.000238846121174282,
    0.000135396632897572,
    0.0000634586526803083,
    0.0000252087365807967,
    0.0000107202119382035,
    0.00000488209391552436,
    0.00000195091645131205,
    0.00000066760167764918,
    0.000000285457562520246,
    0.0000000854622934398557};
  
  double xx2[24]={1.17606,1.68542,2.19144,2.69754,3.33822,4.36991,4.25,4.75,5.25,5.75,6.25,6.75,7.25,7.75,8.5,9.5,11,13};
  double yy2[24]={0.141133,0.0162162,0.00231514,0.000530275,0.00015278,2.00909E-05,1.533E-05,9.707E-06,4.981E-06,3.263E-06,1.547E-06,1.216E-06,8.215E-07,5.139E-07,2.494E-07,1.346E-07,4.688E-08,1.887E-08};
  double xx2e[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  double yy2e[24]={0.033677,0.003804,0.000732,0.000202,0.000049,0.000009,1.063E-05,4.635E-06,2.265E-06,1.16E-06,5.959E-07,3.855E-07,2.507E-07,1.579E-07,7.485E-08,4.15E-08,1.456E-08,6.394E-09};
  for(int i = 1; i<31+1;i++){
    gpi->SetPoint(i-1,xx[i-1],yy[i-1]);
    gpi->SetPointError(i-1,xxe[i-1],yye[i-1]);
  }
  for(int i = 1; i<24+1;i++){
    ggamma->SetPoint(i-1,xx2[i-1],yy2[i-1]);
    ggamma->SetPointError(i-1,xx2e[i-1],yy2e[i-1]);
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
void data_12C5(TGraphErrors *gpi){
  double xx[31] ={3.50E-01,
    4.50E-01,
    5.50E-01,
    6.50E-01,
    7.50E-01,
    8.50E-01,
    9.50E-01,
    1.05E+00,
    1.15E+00,
    1.30E+00,
    1.50E+00,
    1.70E+00,
    1.90E+00,
    2.10E+00,
    2.35E+00,
    2.75E+00,
    3.40E+00,
    2.63E+00,
    2.88E+00,
    3.13E+00,
    3.38E+00,
    3.63E+00,
    3.88E+00,
    4.25E+00,
    4.75E+00,
    5.25E+00,
    5.75E+00,
    6.44E+00,
    7.45E+00, 
    8.83E+00,
    1.09E+01};
  double xxe[31] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  double yy[31] = {1.84E+02,
    1.13E+02,
    6.97E+01,
    4.40E+01,
    2.82E+01,
    1.83E+01,
    1.20E+01,
    7.97E+00,
    5.50E+00,
    3.10E+00,
    1.49E+00,
    7.28E-01,
    3.67E-01,
    1.96E-01,
    8.87E-02,
    3.04E-02,
    4.87E-03,
    4.11E-02,
    2.06E-02,
    1.04E-02,
    5.46E-03,
    2.97E-03,
    1.67E-03,
    7.69E-04,
    2.95E-04,
    1.29E-04,
    5.60E-05,
    2.18E-05,
    7.05E-06,
    2.03E-06, 
    3.66E-07};
  double yye[31] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  for(int i = 1; i<31+1;i++){
    gpi->SetPoint(i-1,xx[i-1],yy[i-1]);
    gpi->SetPointError(i-1,xxe[i-1],yye[i-1]);
  }
  
}
