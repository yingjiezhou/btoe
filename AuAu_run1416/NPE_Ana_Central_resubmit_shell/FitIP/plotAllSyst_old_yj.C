#include "TMatrix.h"
void getErrors(TH2F* frac, TH1F* fr);
void getData(TH1F* y,TH1F* ysys,TH2F* h,TH2F* f,TH2F* f1,TH2F* f2,TH2F* f3, int bin,char file[], int central, TH1F* running);
void norm(TH1F *h);
double eff[9]={0,0,0,0.952039,0.964109,0.974269,0.983159,0.988961,0.994107};
//====================================================================

void plotAllSyst_old_yj(int savefrac = 0){
  gROOT->ProcessLine(".x ~/myStyle.C");
  double xp[21]={1.1,
    1.3,
    1.5,
    1.7,
    1.9,
    2.1,
    2.3,
    2.5,
    2.7,
    2.9,
    3.1,
    3.3,
    3.5,
    3.7,
    3.9,
    4.25,
    4.75,
    5.5,
    6.5,
    7.5,
    8.5};
  double yp[21]={0.0353,
    0.0529,
    0.0767,
    0.107,
    0.143,
    0.184,
    0.229,
    0.275,
    0.321,
    0.367,
    0.409,
    0.446,
    0.482,
    0.513,
    0.541,
    0.58,
    0.621,
    0.655,
    0.681,
    0.681,
    0.667};
  double xep[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  double yep[21]={0.0118,
    0.0175,
    0.0247,
    0.0326,
    0.0405,
    0.0472,
    0.0522,
    0.0556,
    0.0575,
    0.0581,
    0.0581,
    0.0579,
    0.0581,
    0.0588,
    0.0598,
    0.0616,
    0.0657,
    0.0708,
    0.0784,
    0.0881,
    0.0992};
  
  TGraphErrors *phe = new TGraphErrors(20,xp,yp,xep,yep);
  phe->SetLineColor(kCyan);
  phe->SetFillColor(kCyan);
  
  // DUKE
  double yDuke[20];
  double xDukeB[20] = {0.250E+00, 0.750E+00, 0.125E+01, 0.175E+01, 0.225E+01, 0.275E+01, 0.325E+01, 0.375E+01, 0.425E+01, 0.475E+01, 0.525E+01, 0.575E+01, 0.625E+01, 0.675E+01, 0.725E+01, 0.775E+01, 0.825E+01, 0.875E+01, 0.925E+01, 0.975E+01};
  double yDukeB[20] = {0.952E+00, 0.960E+00, 0.943E+00, 0.964E+00, 0.107E+01, 0.112E+01, 0.109E+01, 0.105E+01, 0.982E+00, 0.897E+00, 0.848E+00, 0.815E+00, 0.759E+00, 0.725E+00, 0.721E+00, 0.683E+00, 0.642E+00, 0.637E+00, 0.623E+00, 0.602E+00};
  TGraph * gDukeBtoE = new TGraph(20,xDukeB,yDukeB);
  double yDukeD[20] = {0.740E+00, 0.803E+00, 0.102E+01, 0.850E+00, 0.692E+00, 0.591E+00, 0.535E+00, 0.474E+00, 0.482E+00, 0.471E+00, 0.461E+00, 0.477E+00, 0.459E+00, 0.464E+00, 0.454E+00, 0.450E+00, 0.423E+00, 0.478E+00, 0.445E+00, 0.439E+00};
  TGraph * gDukeDtoE = new TGraph(20,xDukeB,yDukeD);
  for(int i = 0;i<20;i++){
    yDuke[i] =yDukeB[i] / yDukeD[i];
  }
  TGraph * gDuke = new TGraph(20,xDukeB,yDuke);
  gDuke->SetLineColor(kRed);
  gDuke->SetLineStyle(8);
  gDuke->SetLineWidth(2);
  
  TFile *fk = new TFile("../../forYifei/electronFraction/finalBtoEFraction.root");
  auto kunsu = (TH1F*) fk->Get("run14_bF_sts");
  auto kunsu1 = (TH1F*) fk->Get("run14_bF_sys");
  kunsu->SetMarkerColor(kRed);
  kunsu->SetMarkerStyle(25);
  kunsu->SetLineColor(kRed);
  kunsu->GetXaxis()->SetRangeUser(2,8.5);
  kunsu1->GetXaxis()->SetRangeUser(2,8.5);
  
  ifstream data_b("b_pp200.txt");
  ifstream data_c("c_pp200.txt");
  
  vector<double> x;
  vector<double> xu;
  vector<double> yb;
  vector<double> yc;
  vector<double> eub;
  vector<double> euc;
  vector<double> edb;
  vector<double> edc;
  TH1F *hb_t = new TH1F("hb_t","",100,0,10);
  TH1F *hb_t1 = new TH1F("hb_t1","",100,0,10);
  TH1F *hc_t = new TH1F("hc_t","",100,0,10);
  TH1F *hr_t = new TH1F("hr_t","",100,0,10);
  TH1F *hb_et = new TH1F("hb_et","",100,0,10);
  TH1F *hc_et = new TH1F("hc_et","",100,0,10);
  double lumi = 1;//500e-6;
  if(data_b.is_open()){
    while(!data_b.eof()){
      double x1;
      double y1;
      double eu;
      double ed;
      double p1;
      double p2;
      double p3;
      double p4;
      double eff;
      data_b >> x1 >> y1 >> eu >> ed >> p1 >> p2 >> p3 >> p4;
      x.push_back(x1);
      xu.push_back(x1-10/100);
      yb.push_back(y1);
      eub.push_back(eu-y1);
      edb.push_back(y1-ed);
      int bin = hb_t->FindBin(x1);
      hb_t->SetBinContent(bin,y1*lumi);
      hb_t->SetBinError(bin,(y1-ed)*lumi);
      hb_t1->SetBinContent(bin,y1*lumi);
      hb_t1->SetBinError(bin,(y1-ed)*lumi);
    }
  }
  if(data_c.is_open()){
    while(!data_c.eof()){
      double x1;
      double y1;
      double eu;
      double ed;
      double p1;
      double p2;
      double p3;
      double p4;
      data_c >> x1 >> y1 >> eu >> ed >> p1 >> p2 >> p3 >> p4;
      yc.push_back(y1);
      euc.push_back(eu-y1);
      edc.push_back(y1-ed);
      int bin = hc_t->FindBin(x1);
      hc_t->SetBinContent(bin,y1*lumi);
      hc_t->SetBinError(bin,(y1-ed)*lumi);
    }
  }
  
  double x_b[100];double xe_b[100];
  double y_bc[100];double e_bc[100];
  double y_c[100];
  
  for(int i = 0;i<100;i++){
    x_b[i] = x[i];
    xe_b[i] = 0;
    //double temp = pt_d_all->GetBinContent(pt_d_all->FindBin(x_b[i]));
    y_bc[i] = yb[i]/(yb[i]+yc[i]);
    y_c[i] = yc[i];
    e_bc[i] = 0;
  }
  y_bc[0]=0;
  TGraphErrors *gb = new TGraphErrors(100,x_b,y_bc,xe_b,e_bc); // FONLL b fraction
  TGraphErrors *gc = new TGraphErrors(100,x_b,y_c,xe_b,e_bc); // FONLL c spectrum
  //====================================================================
  
  TFile * f= new TFile("../../NPE_MC/Ana/root_yj/HF_plots.root");
  auto dcapt_d_all=(TH2F*)f->Get("dcapt_d_all");
  auto dcapt_b_all=(TH2F*)f->Get("dcapt_b_all");
  auto pt_d_all =(TH1F*)dcapt_d_all->ProjectionY();
  auto pt_b_all =(TH1F*)dcapt_b_all->ProjectionY();
  norm(pt_b_all);
  norm(pt_d_all);
  pt_d_all->Scale(hc_t->Integral()/pt_d_all->Integral()); // from data, charm spectrum
  
  hb_t->Scale(2.83609e+08/(41./142.)/hc_t->Integral());//*9.5711E-03);//hb_t->Integral()/hc_t->Integral());
  hb_t->Scale(0.55*0.7*0.8*0.5);
  hb_t1->Scale(0.55*0.7*0.8*0.5*43.9/1000*291);
  
  cout << "HEEEREEE " << hb_t->Integral() << " " << hc_t->Integral() << endl; // ???
 
  //======================================================================
// pp
  //double yy[9] =   {0,0,0,0,0,0.31697,0.418603,0.48473,5.8E-01}; // pp, same, but rebin to fit for AA
  //double ee1[9] =  {0,0,0,0,0,0.0603727,0.0664046,0.0943932,6.5E-02};
  //double ee2l[9] = {0,0,0,0,0,0.030116,0.032119,0.074922,0.0825};
  //double ee2h[9] = {0,0,0,0,0,0.023401,0.054527,0.103078,0.043};
  // combine run12 and run6
  double xx2[6] =   {3,4,5,6,7,8};
  double xxe2[6] =   {0,0,0,0,0,0};
  double xxe22[6] =   {0.2,0.2,0.2,0.2,0.2,0.2};
  double yy2[6] =   {0.31697,0.418603,0.48473,0.61381,0.52239,0.486374};
  double ee12[6] =  {0.0603727,0.0664046,0.0943932,0.0603727,0.0664046,0.0943932}; // stat.
  double ee2l2[6] = {0.030116,0.032119,0.074922,0.0825,0.060429,0.037368}; // sys. left
  double ee2h2[6] = {0.023401,0.054527,0.103078,0.038138,0.029753,0.111897}; // sys. right
  TFile *run12 = new TFile("run12NPEh_rBPoints.root");
  TGraphAsymmErrors* StatError = (TGraphAsymmErrors*)run12->Get("StatError");
  TGraphAsymmErrors* systError =(TGraphAsymmErrors*)run12->Get("systError");
  for(int i = 0;i<6;i++){
    double _x;double _y;
    StatError->GetPoint(i,_x,_y);
    double e1 = StatError->GetErrorYlow(i);
    double e2 = StatError->GetErrorYhigh(i);
    double e3 = systError->GetErrorYlow(i);
    double e4 = systError->GetErrorYhigh(i);
    cout << "Run12 data " <<  _x << " " << _y << " " << e1 << " " << e2 << " " << e3 << " " << e4 << endl;
    double t1 = yy2[i];
    double t2 = ee12[i]; // stat
    double t3 = ee2l2[i];
    double t4 = ee2h2[i];
    double ny = (t1/t2/t2 + _y/e1/e1) / (1/t2/t2 + 1/e1/e1);
    
    
    yy2[i] = ny;
    ee12[i] = 1/sqrt(1/t2/t2 + 1/e1/e1);
    ee2l2[i] = (t3/t2/t2 + e3/e1/e1) / (1/t2/t2 + 1/e1/e1);
    ee2h2[i] = (t4/t2/t2 + e4/e1/e1) / (1/t2/t2 + 1/e1/e1);
  }
  TGraphAsymmErrors *gpp = new TGraphAsymmErrors(6,xx2,yy2,xxe2,xxe2,ee12,ee12);
  TGraphAsymmErrors *gpp_sys = new TGraphAsymmErrors(6,xx2,yy2,xxe22,xxe22,ee2l2,ee2h2);
  //======================================================================
  
  TCanvas *ccharm = new TCanvas("ccharm","charm");
  gc->Draw("APE");
  pt_d_all->Draw("hist same");
  ccharm->SaveAs("sys_yj/charm_spectrum.pdf");
  //======================================================================
  
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  int const numSysBins=10;
  double binning1[numSysBins+1]={0,1,2,3,4,5,6,7,8,9,10};
  
  TH2F *h1 = new TH2F("h1","h1",numPtBins,binning,numSysBins,binning1);
  TH2F *h1_ht = new TH2F("h1_ht","h1_ht",numPtBins,binning,numSysBins,binning1);
  
  TH2F *frac = new TH2F("frac","frac",numPtBins,binning,numSysBins,binning1);
  TH2F *frac_ht = new TH2F("frac_ht","frac_ht",numPtBins,binning,numSysBins,binning1);
  
  TH2F *frac1 = new TH2F("frac1","frac1",numPtBins,binning,numSysBins,binning1);
  TH2F *frac1_ht = new TH2F("frac1_ht","frac1_ht",numPtBins,binning,numSysBins,binning1);
  TH2F *frac2 = new TH2F("frac2","frac2",numPtBins,binning,numSysBins,binning1);
  TH2F *frac2_ht = new TH2F("frac2_ht","frac2_ht",numPtBins,binning,numSysBins,binning1);
  TH2F *frac3 = new TH2F("frac3","frac3",numPtBins,binning,numSysBins,binning1);
  TH2F *frac3_ht = new TH2F("frac3_ht","frac3_ht",numPtBins,binning,numSysBins,binning1);
  TH1F *frb = new TH1F("frb","frb",numPtBins,binning);
  TH1F *frb_ht = new TH1F("frb_ht","frb_ht",numPtBins,binning);
  TH1F *frc = new TH1F("frc","frc",numPtBins,binning);
  TH1F *frc_ht = new TH1F("frc_ht","frc_ht",numPtBins,binning);
  TH1F *fre = new TH1F("fre","fre",numPtBins,binning);
  TH1F *fre_ht = new TH1F("fre_ht","fre_ht",numPtBins,binning);
  TH1F *frh = new TH1F("frh","frh",numPtBins,binning);
  TH1F *frh_ht = new TH1F("frh_ht","frh_ht",numPtBins,binning);
  
  TH1F *h_yield_mb = new TH1F("h_yield_mb","h_yield_mb",numPtBins,binning);
  TH1F *h_yield_ht = new TH1F("h_yield_ht","h_yield_ht",numPtBins,binning);
  TH1F *h_yield_mb_sys = new TH1F("h_yield_mb_sys","h_yield_mb_sys",numPtBins,binning);
  TH1F *h_yield_ht_sys = new TH1F("h_yield_ht_sys","h_yield_ht_sys",numPtBins,binning);
  
  TH1F *h_ave = new TH1F("h_ave","h_ave",numPtBins,binning);
  TH1F *h_ave_sys = new TH1F("h_ave_sys","h_ave_sys",numPtBins,binning);
  TH1F *h_rel_er1 = new TH1F("h_rel_er1","h_rel_er1",numPtBins,binning);
  TH1F *kunsu_rel_er1 = new TH1F("kunsu_rel_er1","kunsu_rel_er1",numPtBins,binning);
  TH1F *h_rel_er = new TH1F("h_rel_er","h_rel_er",numPtBins,binning);
  TH1F *kunsu_rel_er = new TH1F("kunsu_rel_er","kunsu_rel_er",numPtBins,binning);
  TH1F *h = new TH1F("h","h",numPtBins,binning);
  TH1F *h_ht = new TH1F("h_ht","h_ht",numPtBins,binning);
  TH1F *h_sys = new TH1F("h_sys","h_sys",numPtBins,binning);
  TH1F *h_sys_ht = new TH1F("h_sys_ht","h_sys_ht",numPtBins,binning);
  TH1F *er = new TH1F("er","er",numPtBins,binning);
  TH1F *er_ht = new TH1F("er_ht","er_ht",numPtBins,binning);
  TH1F *y_sys_mb = new TH1F("y_sys_mb","y_sys_mb",numPtBins,binning);
  TH1F *y_sys_ht = new TH1F("y_sys_ht","y_sys_ht",numPtBins,binning);
  
  getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,1,"./11133/yields.dat",1,y_sys_mb);//Central 11
  //getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,1,"./1111133/yields.dat",1,y_sys_mb);//Central 11
  getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,2,"./702/yields.dat",0,y_sys_mb);//phoe 1-pion
  getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,3,"./704/yields.dat",0,y_sys_mb);//phoe 1-gamma
  getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,4,"./706/yields.dat",0,y_sys_mb);// phoe 2
  //getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,5,"./710/yields.dat",0,y_sys_mb);// pt spectra
  getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,5,"./708/yields.dat",0,y_sys_mb);// pt spectra
  getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,6,"./710/yields.dat",0,y_sys_mb);// pt spectra
  getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,7,"./712/yields.dat",0,y_sys_mb);// more dp fragmetation
  getData(h_yield_mb,h_yield_mb_sys,h1,frac,frac1,frac2,frac3,8,"./714/yields.dat",2,y_sys_mb);// less dp fragmetation
  
  getData(h_yield_ht,h_yield_ht_sys,h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,1,"./401/yields.dat",1,y_sys_ht);//12
  getData(h_yield_ht,h_yield_ht_sys,h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,2,"./403/yields.dat",0,y_sys_ht);
  getData(h_yield_ht,h_yield_ht_sys,h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,3,"./405/yields.dat",0,y_sys_ht);
  getData(h_yield_ht,h_yield_ht_sys,h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,4,"./407/yields.dat",0,y_sys_ht);
  getData(h_yield_ht,h_yield_ht_sys,h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,5,"./409/yields.dat",0,y_sys_ht);
  getData(h_yield_ht,h_yield_ht_sys,h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,6,"./415/yields.dat",0,y_sys_ht);
  getData(h_yield_ht,h_yield_ht_sys,h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,7,"./411/yields.dat",0,y_sys_ht);
  getData(h_yield_ht,h_yield_ht_sys,h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,8,"./413/yields.dat",2,y_sys_ht);
  
  //h1->Draw();
  //h1_ht->Draw("same");
  //return;
  cout << "B fractions "<<endl;
  getErrors(frac,frb);
  getErrors(frac_ht,frb_ht);
  cout << "C fractions "<<endl;
  getErrors(frac1,frc);
  getErrors(frac1_ht,frc_ht);
  cout << "E fractions "<<endl;
  getErrors(frac2,fre);
  getErrors(frac2_ht,fre_ht);
  cout << "H fractions "<<endl;
  getErrors(frac3,frh);
  getErrors(frac3_ht,frh_ht); // zyj put value and error in a hist
  
  cout << "Doing Min. bias errors " << endl;
  cout << "Errors are phoe1-pion - phoe1-gamma - phoe2 const - pt spectra - fragmentaion" <<  endl;
  for(int i = 5; i<numPtBins; i++){
    cout << "on pT bin " << i << " " << endl;
    double cen = 0;
    double phoe = 0;
    double frag = 0;
    double err = 0;
    double spec = 0;
    for(int j = 1; j<numSysBins+1; j++){
      double val = h1->GetBinContent(i,j);
      double val_e = h1->GetBinError(i,j);
      if(val>0){
        if(j==1){
          h->SetBinContent(i,val);
          h_sys->SetBinContent(i,val);
          h->SetBinError(i,val_e); // stat. error
          cen = val;
        }else{
          if(j==2 || j==3 || j==5 || j==6 || j==7 || j == 8){
            if(j==2)phoe = val;
            if(j==3)if(fabs(cen-val)>fabs(cen-phoe))phoe = val;
            if(j==3)err+= (cen-phoe)*(cen-phoe);
            if(j==5)spec = val;
            if(j==6)if(fabs(cen-val)>fabs(cen-spec))spec = val;
            if(j==6)err+= (cen-spec)*(cen-spec);
            if(j==7)frag = val;
            if(j==8)if(fabs(cen-val)>fabs(cen-frag))frag = val;
            if(j==8)err+= (cen-frag)*(cen-frag);
          }else{
            err+= (cen-val)*(cen-val);
          }
          
          cout << j << " " << cen << " " << val << " " << fabs(cen-val)/cen << " ";
        }
        cout << endl;
      }
    }
    if(err>0){
      er->SetBinContent(i,sqrt(err)); // just for showing sys error, otherwise is useless
      cout << "Total error " << sqrt(err) << " " << sqrt(err)/cen << endl;
      h_sys->SetBinError(i,sqrt(err));
    }
  }
  
  /*
  cout << "DoingHT errors " << endl;
  cout << "Errors are phoe1-pion - phoe1-gamma - phoe2 const - pt spectra - fragmentaion" <<  endl;
  for(int i = 6; i<numPtBins+1; i++){
    cout << "on pT bin " << i << " " << endl;
    double cen = 0;
    double phoe = 0;
    double frag = 0;
    double spec = 0;
    double err = 0;
    for(int j = 1; j<numSysBins+1; j++){
      double val = h1_ht->GetBinContent(i,j);
      double val_e = h1_ht->GetBinError(i,j);
      if(val>0){
        if(j==1){
          h_ht->SetBinContent(i,val);
          h_sys_ht->SetBinContent(i,val);
          h_ht->SetBinError(i,val_e);
          cen = val;
        }else{
          if(j==2 || j==3 || j==5 || j==6 || j==7 || j == 8){
            if(j==2)phoe = val;
            if(j==3)if(fabs(cen-val)>fabs(cen-phoe))phoe = val;
            if(j==3)err+= (cen-phoe)*(cen-phoe);
            if(j==5)spec = val;
            if(j==6)if(fabs(cen-val)>fabs(cen-spec))spec = val;
            if(j==6)err+= (cen-spec)*(cen-spec);
            if(j==7)frag = val;
            if(j==8)if(fabs(cen-val)>fabs(cen-frag))frag = val;
            if(j==8)err+= (cen-frag)*(cen-frag);
          }else{
            err+= (cen-val)*(cen-val);
          }
          
          cout << j << " " << cen << " " << val << " " << fabs(cen-val)/cen << " ";
        }
        cout << endl;
      }
    }
    if(err>0){
      er_ht->SetBinContent(i,sqrt(err));
      cout << "Total error " << sqrt(err) << " " << sqrt(err)/cen << endl;
      h_sys_ht->SetBinError(i,sqrt(err));
    }
  }
  */

  
  // average HT and MB
  for(int i =1; i<9;i++){ // don't inculde last point
    double temp1 = h->GetBinContent(i);
    double temp2 = h->GetBinError(i);
    double temp22 = h_sys->GetBinError(i);
    double temp3 = h_ht->GetBinContent(i);
    double temp4 = h_ht->GetBinError(i);
    double temp44 = h_sys_ht->GetBinError(i);
    if(temp1>0 && temp3>0){
      double temp = temp1/temp2/temp2 + temp3/temp4/temp4;
      double er1 = 1/temp2/temp2 + 1/temp4/temp4;
      h_ave->SetBinContent(i,temp/er1);
      h_ave->SetBinError(i,sqrt(1/er1));
      h_ave_sys->SetBinContent(i,temp/er1); // combine
      double temp_er = temp22/temp2/temp2 + temp44/temp4/temp4; // will need sys
      h_ave_sys->SetBinError(i,temp_er/er1);
    }else if(temp1>0 && temp3==0){
      h_ave->SetBinContent(i,temp1);
      h_ave_sys->SetBinContent(i,temp1);
      h_ave->SetBinError(i,temp2);
      h_ave_sys->SetBinError(i,temp22);
    }
    else if(temp1==0 && temp3>0){
      h_ave->SetBinContent(i,temp3);
      h_ave_sys->SetBinContent(i,temp3);
      h_ave->SetBinError(i,temp4);
      h_ave_sys->SetBinError(i,temp44);
    }
  }
  h->SetMarkerStyle(24);
  h_sys->SetMarkerStyle(24);
  h->SetLineColor(kBlue);
  h_sys->SetLineColor(kBlue);
  h->SetMarkerColor(kBlue);
  h_sys->SetMarkerColor(kBlue);
  h_sys->SetFillColor(kBlue);
  h_sys->SetFillStyle(3004);
  h_ht->SetMarkerStyle(25);
  h_sys_ht->SetMarkerStyle(25);
  h_ht->SetLineColor(kRed);
  h_sys_ht->SetLineColor(kRed);
  h_ht->SetMarkerColor(kRed);
  h_sys_ht->SetMarkerColor(kRed);
  h_sys_ht->SetFillColor(kRed);
  h_sys_ht->SetFillStyle(3005);
  
  h_yield_ht->SetMarkerStyle(24);
  h_yield_ht_sys->SetMarkerStyle(24);
  h_yield_ht->SetLineColor(kBlue);
  h_yield_ht_sys->SetLineColor(kBlue);
  h_yield_ht->SetMarkerColor(kBlue);
  h_yield_ht_sys->SetFillStyle(3004);
  h_yield_mb_sys->SetFillColor(kGray);
  h_yield_mb_sys->SetFillStyle(3005);
  
  hb_t->SetLineColor(kRed-2); //?????
  hb_t->SetLineStyle(7);
  hb_t1->SetLineColor(kGreen-2);
  hb_t1->SetLineStyle(5);
  
  for(int i = 0 ;i<9;i++){
    dcapt_b_all->GetYaxis()->SetRangeUser(binning[i],binning[i+1]);
    TH1D* tempp = dcapt_b_all->ProjectionX();
    int bin11 = tempp->FindBin(-2);
    int bin22 = tempp->FindBin(-1);
    double effi = tempp->Integral(bin11,bin22)/tempp->Integral();
    cout << "Efficiency dca cut bin " << i+1 << " " << effi << endl;
  }// not used?? dca cut eff, used for ??v2??
 
  //======================================================================
  TLegend *leg4 = new TLegend(0.5,0.65,0.9,0.9);
  
  leg4->AddEntry(h_yield_mb,"Min. Bias","PLE");
  leg4->AddEntry(h_yield_ht,"High Tower","PLE");
  leg4->AddEntry(hb_t,"[N(D^{0})/f_{D^{0}}]#times[#sigma(#it{pp}#rightarrow#it{b})/#sigma(#it{pp}#rightarrow#it{c})]#times#varepsilon(#it{e})","L");
  leg4->AddEntry(hb_t1,"FONLL#times#it{L}#times<N_{coll}>#times#varepsilon(#it{e})","L");
  
  TCanvas *cy = new TCanvas("cy","yields");
  cy->SetLogy();
  h_yield_mb->GetYaxis()->SetTitle("dN_{raw}/d#it{p}_{T} [1/GeV]");
  h_yield_mb->GetYaxis()->SetRangeUser(1,10e6);
  h_yield_mb->GetXaxis()->SetRangeUser(0,8.5);
  h_yield_mb->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  h_yield_mb->Draw("PE");
  h_yield_ht->Draw("PE same");
  h_yield_ht_sys->Draw("same E2");
  h_yield_mb_sys->Draw("same E2");
  h_yield_mb->Draw("E1 same");
  h_yield_ht->Draw("E1 same");
  //y_sys_mb->Draw("hist same");
  //y_sys_ht->Draw("hist same");
  //pt_b_all->Draw("hist same"); //???
  hb_t->Draw("hist same");
  hb_t1->Draw("hist same");
  leg4->Draw("same");
  gPad->RedrawAxis();
  cy->SaveAs("sys_yj/yields.pdf");
  //======================================================================
  
  TPaveText *Name11 = new TPaveText(0.172,0.81,0.512,0.89,"BRNDC");
  Name11->AddText("STAR Central-5");
  Name11->SetFillColorAlpha(0, 0);
  Name11->SetTextAlign(12);
  Name11->SetBorderSize(0);

  TCanvas *c1 = new TCanvas("c1","Final");
  TLegend *leg3 = new TLegend(0.5,0.2,0.9,0.3);
  leg3->AddEntry(h,"Central-5","PLE");
  //leg3->AddEntry(h_ht,"High Tower","PLE");
  h->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
  h->GetYaxis()->SetRangeUser(0,1);
  h->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  h->Draw("E1");
  h_sys->Draw("same E2");
  //h_ht->Draw("same E1");
  //h_sys_ht->Draw("same E2");
  //h_ht->Draw("same E1");
  h->Draw("same E1");
  leg3->Draw("same");
  //Name11->Draw("same");
  c1->SaveAs("sys_yj/Final_fraction.pdf");
  //======================================================================
  
  TCanvas *c2 = new TCanvas("c2","Real. Errors");
  TLegend *leg22 = new TLegend(0.2,0.5,0.5,0.9);
  leg22->AddEntry(er,"Min. Bias Syst.","PLE");
  leg22->AddEntry(er_ht,"High Tower Syst.","PLE");
  er_ht->SetLineColor(kRed);
  er->GetYaxis()->SetRangeUser(0, 0.16);
  er->Draw();
  er_ht->Draw("same");
  leg22->Draw("same");
  c2->SaveAs("sys_yj/Real_err.pdf");
  c2->SaveAs("sys_yj/Real_err.C");
  //======================================================================
  
  gb->SetLineStyle(7);
  kunsu1->SetLineColor(kBlue);
  kunsu1->SetFillColor(kBlue);
  kunsu1->SetFillColorAlpha(kBlue,0.5);
  kunsu1->SetFillStyle(3004);
  h_ave_sys->SetFillColor(kGray);
  gpp->SetMarkerStyle(25);
  gpp->SetMarkerColor(kBlue);
  gpp->SetLineColor(kBlue);
  gpp_sys->SetMarkerStyle(25);
  gpp_sys->SetMarkerColor(kBlue);
  gpp_sys->SetLineColor(kBlue);
  gpp_sys->SetFillColor(kBlue);
  gpp_sys->SetFillColorAlpha(kBlue,0.5);
  gpp_sys->SetFillStyle(3004);
  TLegend *leg = new TLegend(0.5,0.2,0.9,0.45);
  leg->AddEntry(h_ave,"Au+Au #sqrt{s_{NN}} = 200 GeV","PLE");
  leg->AddEntry(gpp,"#it{p}+#it{p} #sqrt{s} = 200 GeV","PLE");
  leg->AddEntry(kunsu,"Old Results","PLE");
  leg->AddEntry(gb,"FONLL #it{p}+#it{p} #sqrt{s} = 200 GeV","L");
  
  
  TPaveText *Name = new TPaveText(0.164,0.733,0.45,0.8,"BRNDC");
  Name->AddText("STAR Central-5");
  Name->SetFillColorAlpha(0, 0);
  Name->SetTextAlign(12);
  Name->SetBorderSize(0);
  TPaveText *Name1 = new TPaveText(0.182,0.81,0.522,0.89,"BRNDC");
  Name1->AddText("STAR Central-5");
  //Name1->AddText("STAR 0-80%");
  Name1->SetFillColorAlpha(0, 0);
  Name1->SetTextAlign(12);
  Name1->SetBorderSize(0);
  //Name->SetTextFont(32);
  //======================================================================
  
  TCanvas *c3 = new TCanvas("c3","Weighted Ave");
  h_ave->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
  h_ave->GetYaxis()->SetRangeUser(0,1);
  h_ave->GetXaxis()->SetRangeUser(0,8.5);
  h_ave->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  h_ave->Draw("PE");
  h_ave_sys->Draw("same E2");
  kunsu1->Draw("same E2");
  gpp_sys->Draw("same E2");
  h_ave->Draw("same E1");
  kunsu->Draw("same");
  gpp->Draw("same PE");
  //kunsu->Draw("same");
  gb->Draw("same");
  leg->Draw("same");
  Name1->Draw("same");
  gPad->RedrawAxis();
  c3->SaveAs("sys_yj/MB_HT_average.pdf");
  //======================================================================
  // relative error
  for(int i = 5; i<10; i++){
    double temp1 = h_ave->GetBinContent(i);
    double temp2 = h_ave->GetBinError(i);
    double temp11 = kunsu->GetBinContent(i-1);
    double temp22 = kunsu->GetBinError(i-1);
    double temp3 = h_ave_sys->GetBinContent(i);
    double temp4 = h_ave_sys->GetBinError(i);
    double temp33 = kunsu1->GetBinContent(i-1);
    double temp44 = kunsu1->GetBinError(i-1);
    if(temp1>0)h_rel_er->SetBinContent(i,temp2/temp1); //stat.
    if(temp11>0)kunsu_rel_er->SetBinContent(i,temp22/temp11);
    if(temp4>0)h_rel_er1->SetBinContent(i,temp4/temp3); // sys
    if(temp44>0)kunsu_rel_er1->SetBinContent(i,temp44/temp33);
  }
  TLegend *leg11 = new TLegend(0.2,0.7,0.9,0.9);
  kunsu_rel_er->SetLineColor(kRed);
  kunsu_rel_er1->SetLineColor(kRed);
  kunsu_rel_er1->SetLineStyle(7);
  h_rel_er1->SetLineStyle(7);
  leg11->AddEntry(h_rel_er,"New Results Stat.","l");
  leg11->AddEntry(h_rel_er1,"New Results Syst.","l");
  leg11->AddEntry(kunsu_rel_er,"Old Results Stat.","l");
  leg11->AddEntry(kunsu_rel_er1,"Old Results Syst.","l");
  //======================================================================
  // ave and normalize
  
  TCanvas *c34 = new TCanvas("c34","Relative. er");
  h_rel_er->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  h_rel_er->GetYaxis()->SetTitle("Relative Uncertainty");
  h_rel_er->GetYaxis()->SetRangeUser(0,0.5);
  h_rel_er->Draw("hist");
  kunsu_rel_er->Draw("SAME hist");
  h_rel_er1->Draw("same hist");
  kunsu_rel_er1->Draw("SAME hist");
  leg11->Draw("same");
  c34->SaveAs("sys_yj/realative_err.pdf");
  //======================================================================
  
  TLegend *leg1 = new TLegend(0.2,0.7,0.9,0.9);
  frb->SetLineColor(kGreen-2);
  frb->SetMarkerColor(kGreen-2);
  frc->SetLineColor(kMagenta);
  frc->SetMarkerColor(kMagenta);
  frh->SetLineColor(kRed);
  frh->SetMarkerColor(kRed);
  fre->SetLineColor(kOrange);
  fre->SetMarkerColor(kOrange);
  frb_ht->SetLineColor(kGreen-2);
  frb_ht->SetMarkerColor(kGreen-2);
  frc_ht->SetLineColor(kMagenta);
  frc_ht->SetMarkerColor(kMagenta);
  frh_ht->SetLineColor(kRed);
  frh_ht->SetMarkerColor(kRed);
  fre_ht->SetLineColor(kOrange);
  fre_ht->SetMarkerColor(kOrange);
  leg1->SetHeader("log_{10}(|DCA|/cm)#in[-2.0,1.0]");
  leg1->AddEntry(frb,"#it{b}#rightarrow#it{c}","PLE");
  leg1->AddEntry(frc,"#it{c}#rightarrow#it{c}","PLE");
  leg1->AddEntry(frh,"Hadrons","PLE");
  leg1->AddEntry(fre,"Photonic #it{e}","PLE");
  TLatex lat;
  
  TF1 *line = new TF1("line","1",0,100);
  line->SetLineStyle(7);
  //======================================================================
  // get raa ratio
  
  /*
  double yy[9] =   {0,0,0,0,0,0.31697,0.418603,0.48473,5.8E-01}; // run6 result, with last bin combined
  double ee1[9] =  {0,0,0,0,0,0.0603727,0.0664046,0.0943932,6.5E-02};
  double ee2l[9] = {0,0,0,0,0,0.030116,0.032119,0.074922,0.0825};
  double ee2h[9] = {0,0,0,0,0,0.023401,0.054527,0.103078,0.043};
  */
  double yy[9] =   {0,0,0,0,0,0.280,
		      0.385,
		      0.514,
		      0.589}; // after combine
  double ee1[9] =  {0,0,0,0,0,0.049,
  	      0.051,
  	      0.046,
  	      0.051};
  double ee2l[9] = {0,0,0,0,0,0.026,
  	      0.026,
  	      0.027,
  	      0.051};
  double ee2h[9] = {0,0,0,0,0,0.024,
		      0.040,
		      0.035,
		      0.033};


  TGraphAsymmErrors *raa = new TGraphAsymmErrors();
  TGraphAsymmErrors *raa_sys = new TGraphAsymmErrors();
  TGraphAsymmErrors *raa_sys1 = new TGraphAsymmErrors(); // not used
  TGraphAsymmErrors *raa_sys2 = new TGraphAsymmErrors();
  int cnt = 0;
  for(int i= 5 ; i<9; i++){
    double tmp1 = h_ave->GetBinContent(i+1);//+h_ave_sys->GetBinError(i+1);
    double err1 =  h_ave->GetBinError(i+1); // stat.
    double err2 =  h_ave_sys->GetBinError(i+1); //syst.
    
    double tmp2 = yy[i];//+ee2h[i];
    double err3 = ee1[i]; // pp stat.
    double err4l = ee2l[i]; // pp sys.
    double err4h = ee2h[i];
    cout<<"b in pp :"<<tmp2<< "    b in AA:    "<<tmp1<<endl;
    double val = (1/tmp2-1)/(1/tmp1-1);
    if(tmp1>0 && tmp2>0){
      double error_st = val*sqrt(err1 * err1 /tmp1/tmp1/(tmp1-1)/(tmp1-1)
                                 + err3 * err3/tmp2/tmp2/(tmp2-1)/(tmp2-1)); //stat
      double error_sy1 = val*sqrt(err2 * err2 /tmp1/tmp1/(tmp1-1)/(tmp1-1)
                                  + err4l * err4l/tmp2/tmp2/(tmp2-1)/(tmp2-1));
      double error_sy2 = val*sqrt(err2 * err2 /tmp1/tmp1/(tmp1-1)/(tmp1-1)
                                  + err4h * err4h/tmp2/tmp2/(tmp2-1)/(tmp2-1)); // sys. two combine
      double error_sy11 = val*sqrt(err2 * err2 /tmp1/tmp1/(tmp1-1)/(tmp1-1));// sys. for AA
      double error_sy21 = val*sqrt(err2 * err2 /tmp1/tmp1/(tmp1-1)/(tmp1-1));
      
      double error_sy12 = val*sqrt(err4l * err4l /tmp1/tmp1/(tmp1-1)/(tmp1-1)); // sys. for pp
      double error_sy22 = val*sqrt(err4h * err4h /tmp1/tmp1/(tmp1-1)/(tmp1-1));
      cout<<"ddddddddddddd"<<val<<endl;
      raa->SetPoint(cnt,h_ave->GetBinCenter(i+1),val);
      raa->SetPointError(cnt,0,0,error_st,error_st);
      raa_sys->SetPoint(cnt,h_ave->GetBinCenter(i+1),val);
      raa_sys->SetPointError(cnt,0.1,0.1,error_sy1,error_sy2);
      
      raa_sys1->SetPoint(cnt,h_ave->GetBinCenter(i+1),val);
      raa_sys1->SetPointError(cnt,0.1,0.1,error_sy11,error_sy21);
      raa_sys2->SetPoint(cnt,h_ave->GetBinCenter(i+1),val);
      raa_sys2->SetPointError(cnt,0.1,0.1,error_sy12,error_sy22);
      cnt++;
    }
  }
  
  raa_sys->SetFillColor(kGray);
  raa_sys->SetFillColor(kGray);
  raa->GetYaxis()->SetRangeUser(0,5);
  raa->GetXaxis()->SetRangeUser(0.01,8.5);
  raa->GetYaxis()->SetTitle("R_{AA}^{b#rightarrow#it{e}}/R_{AA}^{c#rightarrow#it{e}}");
  raa->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  TF1 *fit = new TF1("fit","[0]",1,10);
  TF1 *fit1 = new TF1("fit1","[0]",1,10);
  TF1 *fit2 = new TF1("fit2","[0]",1,10);
  fit->SetLineColor(kBlue);
  fit->SetLineStyle(5);
  raa->Fit("fit");
  return ;
  //======================================
  
  TH1F * spread1 = new TH1F("spread1","spread1",200,0,5);
  TH1F * spread2 = new TH1F("spread2","spread2",200,0,5);
  TF1 func("func","gaus(0)",-10,10);
  func.SetParameter(0,1);
  func.SetParameter(1,0);
  func.SetParameter(2,1);
  func.SetParameter(0,1/func.Integral(-100,100));
  double format1[100];
  double format2[100];
  cout << "filling matrices " << endl;
  // diff pt bin, and diff kinds of sys source
  for(int i= 0 ; i<4; i++){
    for(int j= 0 ; j<=i; j++){
      double temp1i = h_ave_sys->GetBinError(i+1+5);
      double temp1j = h_ave_sys->GetBinError(j+1+5);
      double temp11i = h_ave->GetBinError(i+1+5);
      double temp11j = h_ave->GetBinError(j+1+5);
      
      double temp2i = 0;
      double temp2j = 0;
      if(ee2l[i+5]>ee2h[i+5])temp2i =ee2l[i+5]; // pp sys.
      else  temp2i =ee2h[i+5];
      if(ee2l[j+5]>ee2h[j+5])temp2j =ee2l[j+5];
      else  temp2j =ee2h[j+5];
      
      double temp22i =ee1[i+5]; // pp stat
      double temp22j =ee1[j+5];
      if(i==j){
        format1[i+j*4] = temp1i*temp1j;// + temp11i*temp11j; // pp*aa sys
        format2[i+j*4] = temp2i*temp2j;// + temp22i*temp22j;
      }else{
        format1[i+j*4] = temp1i*temp1j*0.5;
        format2[i+j*4] = temp2i*temp2j*0.5;
      }
    }
  }
  for(int i=0; i<4; ++i) {
    for(int j=0; j<i; ++j) {
      format1[i*4+j]=format1[i+j*4];
      format2[i*4+j]=format2[i+j*4];
    }
  }
  TMatrixD const mat1(4,4,format1);
  TMatrixD const mat2(4,4,format2);
  
  TDecompChol chol1(mat1);
  TDecompChol chol2(mat2);
  
  if(!chol1.Decompose() || !chol2.Decompose()) cout<<"don't know how continue !!!!!!"<<endl;
  //if(chol1.Decompose()){
  TMatrixD dec11 = chol1.GetU();
  //TMatrixD dec1(2,dec11);
  TMatrixF dec1(TMatrix::kTransposed,dec11);
  dec1.Print();
  //}
  //if(chol2.Decompose()){
  TMatrixD dec22 = chol2.GetU();
  TMatrixF dec2(TMatrix::kTransposed,dec22);
  //TMatrixD dec2(2,dec22);
  dec2.Print();
  //}
  for(int i = 0; i<10000;i++){
    TGraphAsymmErrors *raa1 = new TGraphAsymmErrors();
    TGraphAsymmErrors *raa2 = new TGraphAsymmErrors();
    double sig1 = func.GetRandom();
    double sig2 = func.GetRandom();
    
    int cnt = 0 ;
    for(int j= 5 ; j<9; j++){
      double tmp1 = h_ave->GetBinContent(j+1);
      double err1 =  h_ave->GetBinError(j+1);
      double err2 =  h_ave_sys->GetBinError(j+1);
      double tmp2 = yy[j];
      double err3 = ee1[j];
      double err4l = ee2l[j];
      double err4h = ee2h[j];
      
      double shift1 = func.GetRandom()*dec1[j-5][0]+func.GetRandom()*dec1[j-5][1]+func.GetRandom()*dec1[j-5][2]+func.GetRandom()*dec1[j-5][3];
      double shift2 = func.GetRandom()*dec2[j-5][0]+func.GetRandom()*dec2[j-5][1]+func.GetRandom()*dec2[j-5][2]+func.GetRandom()*dec2[j-5][3];
      if(tmp1>0 && tmp2>0){
        double pert1 = shift1;//err2*sig1;
        double pert2 = 0;
        if(sig2>0)pert2 = shift2;//err4h*sig2;
        if(sig2<0)pert2 = shift2;//err4l*sig2;
        double valy1 = (1/(tmp2+pert2)-1)/(1/(tmp1+pert1)-1);
        
        double valy2 = (1/(tmp2+pert2)-1)/(1/(tmp1)-1);
        double stat1 = valy1*sqrt(err1 * err1 /(tmp1+pert1)/(tmp1+pert1)/((tmp1+pert1)-1)/((tmp1+pert1)-1)
                                  + err3 * err3/(tmp2+pert2)/(tmp2+pert2)/((tmp2+pert2)-1)/((tmp2+pert2)-1));
        
        double stat2 = valy2*sqrt(err1 * err1 /tmp1/tmp1/(tmp1-1)/(tmp1-1)
                                  + err3 * err3/(tmp2+pert2)/(tmp2+pert2)/((tmp2+pert2)-1)/((tmp2+pert2)-1));
        raa1->SetPoint(cnt,h_ave->GetBinCenter(j+1),valy1);
        raa1->SetPointError(cnt,0,0,stat1,stat1);
        
        raa2->SetPoint(cnt,h_ave->GetBinCenter(j+1),valy2); // will not use
        raa2->SetPointError(cnt,0,0,stat2,stat2);
        cnt++;
      }
   
      //cout << "\n";
    }
    raa1->Fit(fit1);
    raa2->Fit(fit2);
    spread1->Fill(fit1->GetParameter(0));
    
    spread2->Fill(fit2->GetParameter(0));
    raa1->Delete();
    raa2->Delete();
  }
  TLegend *legg = new TLegend(0.2,0.6,0.7,0.8);
  double vall = fit->GetParameter(0);
  double errr = fit->GetParError(0);
  double erh = 0.51;
  double erl = 0.48;
  //======================================================================
  
  TCanvas *cspread = new TCanvas("cspread","spread");
  //spread->Fit("gaus");
  TF1 func2("func2","gaus(0)",0,vall);
  func2.SetParameter(0,100);
  func2.SetParameter(1,1.86);
  func2.SetParameter(2,0.4);
  TF1 func22("func22","gaus(0)",vall,10);
  func22.SetParameter(0,100);
  func22.SetParameter(1,1.86);
  func22.SetParameter(2,0.4);
  
  TF1 func1("func1","gaus(0)",0,vall); // not used
  func1.SetParameter(0,100);
  func1.SetParameter(1,1.86);
  func1.SetParameter(2,0.4);
  TF1 func11("func11","gaus(0)",vall,10);
  func11.SetParameter(0,100);
  func11.SetParameter(1,1.86);
  func11.SetParameter(2,0.4);
  
  spread1->Fit("func2","R");
  spread1->Fit("func22","R");
  
  spread2->Fit("func1","R");
  spread2->Fit("func11","R");
  spread2->SetLineColor(kRed);

  spread1->Draw("PE");
  func2.SetLineColor(kBlue); //?????
  func22.SetLineColor(kCyan);
  //spread2->Draw("same PE");
  func2.Draw("same l");
  func22.Draw("same l");
  cspread->SaveAs("sys_yj/spread.pdf");

  erl =sqrt(func2.GetParameter(2)*func2.GetParameter(2));//func1.GetParameter(2)*func1.GetParameter(2) +
  erh =sqrt(func22.GetParameter(2)*func22.GetParameter(2));//
  
  char label[100];
  sprintf(label,"%1.2f #pm% 1.2f(stat.) ^{+%1.2f}_{-%1.2f}(syst.)",vall,errr,erh,erl);
  legg->AddEntry(fit,label,"l");
  legg->AddEntry(gDuke,"DUKE 0-80%","l");
  //======================================================================
  
  TCanvas *c44 = new TCanvas("c44","Raa_c/Raa_b");
  raa->Draw("PEA"); // so that fit result can be drawn
  raa_sys->Draw("same PE2");
  raa->Draw("same E1"); // draw again so that sys will be under raa point
  gDuke->Draw("same l");
  line->Draw("same");
  legg->Draw("same");
  Name1->Draw("same");
  c44->SaveAs("sys_yj/raa_fraction.pdf");
  //======================================================================
  
  TCanvas *c4 = new TCanvas("c4","Frac errors",1000,500);
  c4->Divide(2,1);
  c4->cd(1);
  frb->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  frb->GetYaxis()->SetTitle("Relative Fraction");
  frb->GetYaxis()->SetRangeUser(0,1.5);
  frb_ht->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  frb_ht->GetYaxis()->SetTitle("Relative Fraction");
  frb_ht->GetYaxis()->SetRangeUser(0,1.5);
  frb->Draw("PE");
  frc->Draw("same PE");
  fre->Draw("same PE");
  frh->Draw("same PE");
  line->Draw("same");
  leg1->Draw("same");
  
  lat.DrawLatex(5.7,1.2,"Min. Bias");
  c4->cd(2);
  frb_ht->Draw("PE");
  frc_ht->Draw("same PE");
  fre_ht->Draw("same PE");
  frh_ht->Draw("same PE");
  line->Draw("same");
  leg1->Draw("same");
  //lat.DrawLatex(5,1.2,"log_{10}(|DCA|/cm)#in[-1.5,1.0]");
  lat.DrawLatex(5.7,1.2,"High Tower");
  c4->SaveAs("sys_yj/FracComp_errors.pdf");
  //======================================================================

  if(savefrac){
    TFile save("root_yj/Fractions.root","RECREATE");
    frb->Write("bfrac");
    frc->Write("cfrac");
    frh->Write("hfrac");
    fre->Write("efrac");
    frb_ht->Write("bfrac_ht");
    frc_ht->Write("cfrac_ht");
    frh_ht->Write("hfrac_ht");
    fre_ht->Write("efrac_ht");
  }
  if(1){
    TFile save("root_yj/FracB.root","RECREATE");
    h_ave->Write("fb");
    h_ave_sys->Write("fb_sys");
    gb->Write("FONLL");
    gpp->Write("pp");
    gpp_sys->Write("pp_sys");
  }
}
//====================================================================

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
void getData(TH1F* y,TH1F* ysys,TH2F* h,TH2F* f,TH2F* f1,TH2F* f2,TH2F* f3, int bin,char file[], int central, TH1F* running) {
  ifstream data(file);
  if(data.is_open()){
    while(!data.eof()){
      int pT;
      double y1;double e1;double y2;double e2;
      double y3;double e3;double y4;double e4;
      double pur;double pure;double eff;double er;
      double fb1;double fb2;double fc1;double fc2;
      double fe1;double fe2;double fh1;double fh2;
      double br;double bkgr;double nper;double bre;
      double bkgre;double npere; double ere;
      
      data >> pT >> y1 >> e1 >> fb1 >> fb2 >> y2 >> e2 >> fc1 >> fc2 >> y3 >> e3 >> fe1 >> fe2 >> y4 >> e4 >> fh1 >> fh2 >> br >> bre >> bkgr>>bkgre >> nper >> npere >> er >> ere >> pur >> pure;
      if(pT!=0){
        if(central==1)y->SetBinContent(pT,y1/y->GetBinWidth(pT));// set yield unit
        if(central==1)y->SetBinError(pT,e1/y->GetBinWidth(pT));
        if(central==1)ysys->SetBinContent(pT,y1/y->GetBinWidth(pT));
        if(fabs(y1/y->GetBinWidth(pT)-y->GetBinContent(pT))>running->GetBinContent(pT))running->SetBinContent(pT,y1/y->GetBinWidth(pT)); // get large sys
        if(central==2)ysys->SetBinError(pT,fabs(running->GetBinContent(pT)-y->GetBinContent(pT)));
        h->SetBinContent(pT,bin,br);
        h->SetBinError(pT,bin,bre);
        f->SetBinContent(pT,bin,fb2);
        f1->SetBinContent(pT,bin,fc2);
        f2->SetBinContent(pT,bin,fe2);
        f3->SetBinContent(pT,bin,fh2);
      }
    }
  }
  else {
    cout <<"Nope " <<file  << "\n";
  }
  data.close();
}
void getErrors(TH2F* frac, TH1F* fr){
  //cout << "Doing frac errors " << endl;
  //cout << "Errors are phoe1-pion - phoe1-gamma - phoe2 const - pt spectra - fragmentaion" <<  endl;
  for(int i = 5; i<fr->GetNbinsX()+1; i++){
    //cout << "on pT bin " << i << " " << endl;
    double cen = 0;
    double phoe = 0;
    double frag = 0;
    double err = 0;
    for(int j = 1; j<frac->GetNbinsY()+1; j++){
      double val = frac->GetBinContent(i,j);
      double val_e = frac->GetBinError(i,j);
      if(val>0){
        if(j==1){
          fr->SetBinContent(i,val);
          
          cen = val;
        }else{
          if(j==2 || j==3 || j==6 || j == 7){
            if(j==2)phoe = val;
            if(j==3)if(fabs(cen-val)>fabs(cen-phoe))phoe = val;
            if(j==3)err+= (cen-phoe)*(cen-phoe);
            if(j==6)frag = val;
            if(j==7)if(fabs(cen-val)>fabs(cen-frag))frag = val;
            if(j==7)err+= (cen-frag)*(cen-frag);
          }else{
            err+= (cen-val)*(cen-val);
          }
          //cout << j << " " << cen << " " << val << " " << fabs(cen-val)/cen << " ";
        }
        //cout << endl;
      }
    }
    if(err>0 && cen>0){
      //cout << "Total error " << sqrt(err) << " " << sqrt(err)/cen << endl;
      fr->SetBinError(i,sqrt(err));
    }
  }
}

