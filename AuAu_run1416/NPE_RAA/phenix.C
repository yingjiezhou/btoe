double x [28] = {0.35,0.45,0.55,0.65,0.75,0.85,0.95,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.2,4.8,5.5,6.5,7.5,8.5};
double xe [28] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double xes [28] = {0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05}; // raa sys. err in x????
double yy [28] = {0.0796,0.0403,0.0224,0.013,0.00796,0.00533,0.00347,0.00195,0.000951,0.000445,0.000198,0.0001,0.0000521,0.0000293,0.0000166,0.00000963,0.00000579,0.00000361,0.00000225,0.00000147,0.00000113,0.000000624,0.000000324,0.000000116,0.0000000287,0.0000000084,0.00000000504,0.00000000166};//yield
double yey [28] = {0.00251,0.00109,0.000566,0.000344,0.000212,0.000142,0.0001,0.0000456,0.0000114,0.00000508,0.00000177,0.000001,0.000000616,0.000000408,0.000000278,0.000000197,0.000000144,0.000000108,0.0000000823,0.0000000642,0.0000000528,0.0000000401,0.0000000175,0.0000000105,0.00000000462,0.00000000242,0.00000000207,0.00000000129};
double yraa [28] = {0.953,1.08,1.09,1.17,0.997,1.16,1.01,0.996,1.23,1.1,0.968,0.906,0.837,0.808,0.764,0.716,0.68,0.654,0.616,0.6,0.672,0.534,0.507,0.401,0.289,0.297,0.535,0.468};//raa
double yeraa [28] = {0.455,0.425,0.317,0.333,0.213,0.255,0.198,0.136,0.247,0.258,0.00867,0.00908,0.0099,0.013,0.0128,0.0146,0.0169,0.0196,0.0226,0.0262,0.0314,0.0343,0.0273,0.0364,0.0466,0.0857,0.219,0.364};
double yeraa_s [28] = {0.301,0.342,0.257,0.295,0.171,0.195,0.134,0.124,0.148,0.128,0.177,0.16,0.145,0.134,0.127,0.143,0.134,0.126,0.119,0.115,0.124,0.102,0.097,0.0813,0.0696,0.073,0.102,0.128}; // raa sys. err in y, symmetric
double mybin[6]={2,2.5,3.5,4.5,5.5,8.5};
double mycenter[5]={2.25,3,4,5,7};
double mywidth[5]={0.25,0.5,0.5,0.5,1.5};
Double_t func(Double_t *x, Double_t *par){
  Double_t arg = 0;
  Double_t val = 0;
  if(par[2]!=0 && par[1]!=1){
    arg = 1+sqrt(x[0]*x[0])/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
    val = par[0]*sqrt(x[0]*x[0])*TMath::Power(arg,-1/(1-par[1]));//exp(arg*(1/(1-par[1])));
  }
  return val;
}
void phenix(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  TGraphErrors *gy = new TGraphErrors(28,x,yy,xe,yey);
  TGraphErrors *gr = new TGraphErrors(28,x,yraa,xe,yeraa);
  TGraphErrors *gr_s = new TGraphErrors(28,x,yraa,xes,yeraa_s);
  gr_s->SetFillColor(kGray);
  gr_s->SetFillStyle(1000);
  
  TF1* f1 = new TF1("f1",func,2,8.5,3);
  f1->SetParameter(0,1.44381e+04);
  f1->SetParameter(1,9.18928e-01);
  f1->SetParameter(2,1.10008e-01);
  TF1* f2 = new TF1("f2","[0] + [1]*x + [2]*x*x",2,8.5);
  f1->SetLineStyle(7);
  f2->SetLineStyle(7);
  gy->Fit("f1","R");
  gr->Fit("f2","R");
  
  
  TH2F * hy = new TH2F("hy","hy",5,0,5,5000,0,5);//rel. error
  TH2F * hr = new TH2F("hr","hr",5,0,5,5000,0,5);//rel. error
  TGraphErrors *my_y = new TGraphErrors();
  TGraphErrors *my_raa =new TGraphErrors();
  TGraphErrors *my_y_sys = new TGraphErrors();
  TGraphErrors *my_raa_sys =new TGraphErrors();
  
  for(int i = 0; i<5; i++){
    double low  = mybin[i];double high = mybin[i+1];//integration limits
    double r = Int2(f1,f2,low,high);
    double y = Int1(f1,low,high);
    double width = mybin[i+1] - mybin[i];
    my_y->SetPoint(i+1,mycenter[i],y/width);
    my_y_sys->SetPoint(i+1,mycenter[i],y/width); // central value
    my_raa->SetPoint(i+1,mycenter[i],r);
    my_raa_sys->SetPoint(i+1,mycenter[i],r);
  }
  //    getSys1(my_y,hy);
  //  getSys2(my_raa,hr);
  //getSys3(my_raa_sys);
  getSys(my_raa_sys); // sys. err for raa
  getStat(my_raa,gr); // stat. err for raa
  getStat1(my_y,gy); // stat. err for y
  TCanvas *c11 = new TCanvas("c11","raa sys");
  hr->Draw("COLZ");
  
  TLatex lat;
  TF1* f = new TF1("f","1",0,100);
  f->SetLineStyle(5);
  TCanvas *c12 = new TCanvas("c12","yield");
  gy->GetXaxis()->SetTitle("#it{p}_{T}^{e} [GeV]");
  gy->GetYaxis()->SetTitle("Invariant Yield");
  gy->Draw("APE");
  my_y->SetLineColor(kBlue);
  my_y->SetMarkerColor(kBlue);
  my_y->SetMarkerStyle(25);
  my_y_sys->SetLineColor(kBlue);
  my_y_sys->SetMarkerColor(kBlue);
  my_y_sys->SetMarkerStyle(25);
  my_y_sys->SetFillColor(kBlue);
  my_y_sys->SetFillStyle(3004);
  
  my_y->Draw("same PE");
  //my_y_sys->Draw("same E2"); // zyj ?? no sys. error?
  lat.DrawLatex(3,0.001,"PHENIX PhysRevC.84.044905");
  //================================================================================
  
  TCanvas *c2 = new TCanvas("c2","raa");
  gr->GetXaxis()->SetTitle("#it{p}_{T}^{e} [GeV]");
  gr->GetYaxis()->SetTitle("NPE #it{R}_{AA}");
  gr->GetYaxis()->SetRangeUser(0,2);
  gr->Draw("APE");
  gr_s->Draw("same E2");
  gr->Draw("same PE");
  my_raa->SetMarkerStyle(25);
  my_raa->SetLineColor(kBlue);
  my_raa->SetMarkerColor(kBlue);
  my_raa_sys->SetMarkerStyle(25);
  my_raa_sys->SetLineColor(kBlue);
  my_raa_sys->SetMarkerColor(kBlue);
  my_raa_sys->SetFillColor(kBlue);
  my_raa_sys->SetFillStyle(3004);
  my_raa_sys->Draw("same E2");
  my_raa->Draw("same PE");
  lat.DrawLatex(3,1.4,"PHENIX PhysRevC.84.044905");
  f->Draw("l same");
  //================================================================================
  
  TFile file("NPE_RAA.root","RECREATE");
  my_raa->Write("raa_stat");
  my_raa_sys->Write("raa_sys");
}
void norm(TH1F *h){
  double norm1 = h->Integral();
  int bins = h->GetNbinsX();
  for(int i=1; i<bins+1;i++){
    double temp = h->GetBinContent(i);
    double width = h->GetBinWidth(i);
    double err = h->GetBinError(i);
    h->SetBinContent(i,temp/norm1);
    h->SetBinError(i,err/norm1);
  }
}

double Int2(TF1 *f1 ,TF1 *f2, double low , double high){ // get integral via use pt sepctrum as a weight
  double step = (high-low)/100.;
  double sum = 0;
  for(int i=0;i<100;i++){
    sum+= (f1->Integral(low+i*step,low+(i+1)*step)/f1->Integral(low,high))*f2->Integral(low+i*step,low+(i+1)*step)/step;
  }
  return sum;
}
double Int1(TF1 *f1 , double low , double high){
  double step= (high-low)/100.;
  double sum = 0;
  for(int i=0;i<100;i++){
    sum+= f1->Integral(low+i*step,low+(i+1)*step);
  }
  return sum;
}
void getStat(TGraphErrors *g, TGraphErrors *r){
  for(int i = 0; i <5; i++){
    double ey = g->GetErrorY(i+1);
    double ex = g->GetErrorX(i+1);
    double low  = mybin[i];double high = mybin[i+1];
    double er = 0;
    double norm = 0;
    for(int j =0 ; j<28;j++){
      if(x[j]>low && x[j]<high){
        er+=yeraa[j]*yy[j]; // use spectrum as a weight, so here: stat err * yy
        norm+ = yy[j];
      }
    }
    g->SetPointError(i+1,ex,sqrt(ey*ey+er*er/norm/norm));
  }
}
void getSys(TGraphErrors *g){
  
  for(int i = 0; i <5; i++){
    double ey = g->GetErrorY(i+1);
    double ex = g->GetErrorX(i+1);
    double low  = mybin[i];double high = mybin[i+1];
    double er = 0;
    double norm = 0;
    for(int j =0 ; j<28;j++){
      if(x[j]>low && x[j]<high){
        er+=yeraa_s[j]*yy[j];
        norm+ = yy[j];
      }
    }
    g->SetPointError(i+1,mywidth[i],sqrt(ey*ey+er*er/norm/norm));
  }
}
void getStat1(TGraphErrors *g, TGraphErrors *r){
  
  for(int i = 0; i <5; i++){
    double ey = g->GetErrorY(i+1);
    double ex = g->GetErrorX(i+1);
    double low  = mybin[i];double high = mybin[i+1];
    double er = 0;
    double norm = 0;
    for(int j =0 ; j<28;j++){
      if(x[j]>low && x[j]<high){
        er+=yey[j]*yy[j];
        norm+ = yy[j];
      }
    }
    g->SetPointError(i+1,ex,sqrt(ey*ey+er*er/norm/norm));
  }
}
//================================================================================

void getSys1(TGraphErrors *g, TH2F *s){
  TF1* fun = new TF1("fun",func,2,8.5,3);
  fun->SetParameter(0,1.44381e+04);
  fun->SetParameter(1,9.18928e-01);
  fun->SetParameter(2,1.10008e-01);
  TF1* gaus = new TF1("gaus","gaus(0)",-5,5);
  gaus->SetParameter(0,1);
  gaus->SetParameter(1,0);
  for(int loop=0;loop<50;loop++){//toy loop
    double newy[28];
    for(int i =0;i<28;i++){
      gaus->SetParameter(2,yey[i]/yy[i]);
      newy[i] = yy[i]*(1+gaus->GetRandom());
      //cout << "New y's " << yy[i] << " " << newy[i] << endl;
    }
    TGraphErrors *gnew = new TGraphErrors(28,x,newy,xe,yey);
    Int_t fitStatus = gnew->Fit("fun","RF");
    if(fitStatus==0){
      for(int i = 0; i<5; i++){
        double low  = mybin[i];double high = mybin[i+1];//integration limits
        double y = Int1(fun,low,high);
        double _y;
        double _x;
        g->GetPoint(i+1,_x,_y);
        s->Fill(i,y/_y/(high-low));
        //cout << "Fillss " << y << " " << _y << endl;
      }
    }else{
      loop+=-1;
      fun->SetParameter(0,1.44381e+04);
      fun->SetParameter(1,9.18928e-01);
      fun->SetParameter(2,1.10008e-01);
    }
  }
  for(int i = 0; i<5; i++){
    temp = (TH1F*) s->ProjectionY("temp",i,i);
    double _y;
    double _x;
    g->GetPoint(i+1,_x,_y);
    g->SetPointError(i+1,mywidth[i],_y*temp->GetRMS());
    cout << "RMS " << temp->GetRMS() << endl;
    temp->Delete();
  }
}
void getSys2(TGraphErrors *g, TH2F *s){
  TF1* fun = new TF1("fun",func,2,8.5,3);
  fun->SetParameter(0,1.44381e+04);
  fun->SetParameter(1,9.18928e-01);
  fun->SetParameter(2,1.10008e-01);
  TF1* fun2 = new TF1("fun2","[0] + [1]*x + [2]*x*x",2,8.5);
  TF1* gaus = new TF1("gaus","gaus(0)",-5,5);
  gaus->SetParameter(0,1);
  gaus->SetParameter(1,0);
  for(int loop=0;loop<50;loop++){//toy loop
    double newy[28];
    double newy2[28];
    for(int i =0;i<28;i++){
      gaus->SetParameter(2,yey[i]/yy[i]);
      newy[i] = yy[i]*(1+gaus->GetRandom());
      gaus->SetParameter(2,yeraa[i]/yraa[i]);
      newy2[i] = yraa[i]*(1+gaus->GetRandom());
    }
    TGraphErrors *gnew = new TGraphErrors(28,x,yy,xe,yey);
    TGraphErrors *gnew2 = new TGraphErrors(28,x,newy2,xe,yeraa);
    Int_t fitStatus = gnew->Fit("fun","R");
    gnew2->Fit("fun2","R");
    if(fitStatus==0){
      for(int i = 0; i<5; i++){
        double low  = mybin[i];double high = mybin[i+1];//integration limits
        double y = Int2(fun,fun2,low,high);
        double _y;
        double _x;
        g->GetPoint(i+1,_x,_y);
        s->Fill(i,y/_y);
      }
    }
    else{
      fun->SetParameter(0,1.44381e+04);
      fun->SetParameter(1,9.18928e-01);
      fun->SetParameter(2,1.10008e-01);
      loop+=-1;
    }
  }
  for(int i = 0; i<5; i++){
    temp = (TH1F*) s->ProjectionY("temp",i,i);
    double _y;
    double _x;
    g->GetPoint(i+1,_x,_y);
    g->SetPointError(i+1,mywidth[i],_y*temp->GetRMS());
    cout << "RMS " << temp->GetRMS() << endl;
    temp->Delete();
  }
  
}
void getSys3(TGraphErrors *g){
  TF1* fun = new TF1("fun",func,2,8.5,3);
  fun->SetParameter(0,1.44381e+04);
  fun->SetParameter(1,9.18928e-01);
  fun->SetParameter(2,1.10008e-01);
  TF1* fun2 = new TF1("fun2","[0] + [1]*x + [2]*x*x",2,8.5);
  TF1* fun1 = new TF1("fun1","[0] + [1]*x + [2]*x*x",2,8.5);
  TF1* gaus = new TF1("gaus","gaus(0)",-5,5);
  gaus->SetParameter(0,1);
  gaus->SetParameter(1,0);
  double newy2[28];
  double newy1[28];
  for(int i =0;i<28;i++){
    newy2[i] = yraa[i]+yeraa_s[i];
    newy1[i] = yraa[i]-yeraa_s[i];
  }
  TH1F *hlow = new TH1F("hlow","hlow",5,0,5);
  TH1F *hhigh =new TH1F("hhigh","hhigh",5,0,5);
  
  TGraphErrors *gnew = new TGraphErrors(28,x,yy,xe,yey);
  TGraphErrors *gnew2 = new TGraphErrors(28,x,newy2,xe,yeraa);
  TGraphErrors *gnew1 = new TGraphErrors(28,x,newy1,xe,yeraa);
  Int_t fitStatus = gnew->Fit("fun","R");
  gnew2->Fit("fun2","R");
  gnew1->Fit("fun1","R");
  for(int i = 0; i<5; i++){
    double low  = mybin[i];double high = mybin[i+1];//integration limits
    double y = Int2(fun,fun2,low,high);
    double y1 = Int2(fun,fun1,low,high);
    hhigh->SetBinContent(i,y);
    hlow->SetBinContent(i,y1);
  }
  
  for(int i = 0; i<5; i++){
    double temp1 = hlow->GetBinContent(i);
    double temp2 = hhigh->GetBinContent(i);
    double _y;
    double _x;
    g->GetPoint(i+1,_x,_y);
    if(fabs(temp1-_y)>fabs(temp2-_y))g->SetPointError(i+1,mywidth[i],fabs(temp1-_y));
    else g->SetPointError(i+1,mywidth[i],fabs(temp2-_y));
  }
  
}

