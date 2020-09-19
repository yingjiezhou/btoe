void plotPurity_yj(int pass=5){
  
  gROOT->ProcessLine(".x ~/myStyle.C");
     Double_t lhcbTSize    = 0.06;
  char file[50];
  sprintf(file,"./%i/yields.dat",1);
  ifstream data(file);
  char file1[50];
  sprintf(file1,"./%i/yields.dat",2);
  ifstream data1(file1);
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  //int const numPtBins=5;
  //double binning[numPtBins+1]={0.6,1,1.5,2.5,3.5,8.5};
  int const num=9;
  //double kunsu_p[num]={0.90,0.87,0.78,0.86,0.79,0.74,0.66,0.58};
  //double kunsu_p[num]={0.90,0.84,0.65,0.63,0.41,0.30,0.20,0.12};
  //double const kunsu_b[num+1]={1.0,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  double kunsu_e[num]={1,0.86,0.86,0.85,0.86,0.85,0.85,0.85,0.85};
  double kunsu_y[num]={ 1,4008278,2468138,1123100,333933,208449,30757,5510,1756};
  
  double kunsu_p[num]={0.999999,0.95,0.92,0.78,0.82,0.87,0.88,0.94,0.86}; // ??
  double kunsu_pe[num]={0.01,0.01,0.01,0.01,0.01,0.02,0.03,0.10,0.09}; // zyj err
  double kunsu_pe1[num]={0.01,0.01,0.02,0.01,0.04,0.01,0.11,0.18,0.15};
  double const kunsu_b[num+1]={0.6,1.0,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};  // zyj pt
  
  TH1F *hp_k = new TH1F("hp_k","",num,kunsu_b);
  TH1F *hp_k1 = new TH1F("hp_k1","",num,kunsu_b);
  //TH1F *he_k = new TH1F("he_k","",num,kunsu_b);// zyj comment
  for(int i =1; i<10;i++){
    //hp_k->SetBinContent(i,1-kunsu_p[i-1]);
    hp_k->SetBinContent(i,kunsu_p[i-1]);
    hp_k1->SetBinContent(i,kunsu_p[i-1]);
    hp_k->SetBinError(i,kunsu_pe[i-1]);
    hp_k1->SetBinError(i,kunsu_pe1[i-1]);
  }
  hp_k->SetLineColor(1);
  hp_k->SetMarkerColor(1);
  hp_k->SetMarkerStyle(8);
  hp_k1->SetLineColor(1);
  hp_k1->SetLineColor(kBlue);
  hp_k1->SetMarkerColor(1);
  hp_k1->SetMarkerStyle(8);
  //he_k->SetLineColor(kBlue);
  //he_k->SetMarkerColor(kBlue);
  double y;
  double y_e;
  double p1;
  double p2;
  double p3;
  double pT;
  double eff;
  
  TH1F *hy1 = new TH1F("hy1","",numPtBins,binning);
  TH1F *hy11 = new TH1F("hy11","",numPtBins,binning);
  TH1F *he1 = new TH1F("he1","",numPtBins,binning);
  TH1F *he11 = new TH1F("he11","",numPtBins,binning);
  TH1F *hp1 = new TH1F("hp1","",numPtBins,binning);
  TH1F *hp11 = new TH1F("hp11","",numPtBins,binning);
  TH1F *hp2 = new TH1F("hp2","",numPtBins,binning);
  TH1F *hp3 = new TH1F("hp3","",numPtBins,binning);
  //=============================================================================

  TH1F *he = new TH1F("he","",numPtBins,binning);
  if(data.is_open()){
    while(!data.eof()){
      char out[50];
      y=0;
      y_e=0;
      pT=0;
      p1 = 0;
      p2= 0 ;
      p3= 0 ;
      eff=0;
      double t1 =0;
      double t2 =0 ;
      data >> pT >> y >> y_e >> p1 >> eff >> p3 >> p2 >> p3;
      if(y<.0001)y=0;
      int a=y;
      int b=y_e;
      sprintf(out,"Pt %10.0f %10.0d  %10.0d",pT,a,b);
      if(pT!=0){
        hy1->SetBinContent(pT,a);
        hy1->SetBinError(pT,b);
        //hp1->SetBinContent(pT,1-p1); // zyj, purity from 1 dat
        hp1->SetBinContent(pT,p1); // zyj, purity from 1 dat
        hp1->SetBinError(pT,(p1)*b/a);
        he1->SetBinContent(pT,eff);
        he1->SetBinError(pT ,eff*b/a);
        cout <<out << endl;
      }
    }
    
  } else {
    cout <<"Nope \n";
  }
  data.close();
  //==============================================================================
  
  if(data1.is_open()){
    while(!data1.eof()){
      char out[50];
      y=0;
      y_e=0;
      pT=0;
      p1 = 0;
      p2= 0 ;
      p3= 0 ;
      eff=0;
      data1 >> pT >> y >> y_e >> p1 >> eff;// >> p2 >> p3;
      if(y<.0001)y=0;
      int a=y;
      int b=y_e;
      sprintf(out,"Pt %10.0f %10.0d  %10.0d",pT,a,b);
      if(pT!=0){
        hy11->SetBinContent(pT,a);
        hy11->SetBinError(pT,b);
        hp11->SetBinContent(pT,p1);
        hp11->SetBinError(pT,p1*b/a);
        he11->SetBinContent(pT,eff);
        he11->SetBinError(pT ,eff*b/a);
        cout <<out << endl;
      }
    }
    
  } else {
    cout <<"Nope \n";
  }
  data1.close();
  //==============================================================================
  TH1F *hpe = new TH1F("hpe","",numPtBins,binning);

  for(int i =1;i<10;i++){
    double pe = hp_k->GetBinContent(i)/(hp1->GetBinContent(i));
    //double pe = (hp1->GetBinContent(i)-hp_k->GetBinContent(i))/hp1->GetBinContent(i);
    //double pe =((1.-hp_k->GetBinContent(i))-(1.-hp1->GetBinContent(i)))/(1.-hp1->GetBinContent(i));
    cout<<pe<<endl;
    //hp11->SetBinContent(i,pe);
    //hp11->SetBinError(i,1e-6);
    //if(i>3)hpe->SetBinContent(i,pe);
    //if(i>3)hpe->SetBinError(i,1e-8);
    hpe->SetBinContent(i,pe);
    hpe->SetBinError(i,1e-8);
  }
  
  //=============================================================================

  TCanvas *c2 = new TCanvas("c2","c2");
  TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
  //TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
  TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.3);

  //pad1->SetBottomMargin(0.01);
  //pad2->SetTopMargin(0.01);
  //pad2->SetBottomMargin(0.5);

  
  pad1->SetBottomMargin(0.08);
  pad2->SetBottomMargin(0.5);
  pad2->SetTopMargin(0.1);

  pad2->SetBorderMode(0);
  pad1->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  TLegend *leg = new TLegend(0.2,0.65,0.6,0.9);
  hp1->SetMarkerStyle(25);
  hp1->GetYaxis()->SetTitleOffset(0.85);
  //hp1->GetXaxis()->SetTitle("#it{p}_{T} GeV/#it{c}");
  //hp1->GetYaxis()->SetTitle("Hadron fraction");
  hp1->GetYaxis()->SetTitle("Electron purity");
  hp1->GetYaxis()->SetRangeUser(0,1);
  leg->AddEntry(hp1,"Standard Cuts","PLE"); // this is from Matt
  leg->AddEntry(hp_k,"Standard + MVA Likelihood Cuts","PEL"); //
  hp1->Draw("PE");
  hp_k->Draw("same PE");
  leg->Draw("same");
  pad2->cd();
  hpe->GetXaxis()->SetTitle("#it{p}_{T} GeV/#it{c}");
  hpe->GetYaxis()->SetTitle("#frac{Likelihood}{Standard}");
  //hpe->GetYaxis()->SetTitle("#frac{Standard}{Likelihood}");
  hpe->SetTitle(0);
  hpe->GetYaxis()->SetTitleSize(lhcbTSize);
  hpe->GetYaxis()->SetLabelSize(1.2*lhcbTSize);
  hpe->GetYaxis()->CenterTitle();
  hpe->GetYaxis()->SetTitleOffset(0.3);
  hpe->GetYaxis()->SetNdivisions(505);
  hpe->GetYaxis()->SetRangeUser(0, 1.8);
  hpe->GetXaxis()->SetTitleSize(lhcbTSize);
  hpe->GetXaxis()->SetLabelSize(1.2*lhcbTSize);
  hpe->GetXaxis()->SetTitleOffset(0.63);
  //leg->AddEntry(hpe,"#frac{p_{e}^{likelihood cuts}-p_{e}^{rectangular cuts}}{p_{e}^{rectangular cuts}}",""); // this is from Matt
  hpe->Draw();// purity after likelihood cut???
  TF1 *fline = new TF1("fline","1",0,10);
  fline->SetLineStyle(7);
  fline->Draw("same");
  //c2->SaveAs("purity_comparsion_QM.pdf");
  return ;
  //=============================================================================

  
  TCanvas *c22 = new TCanvas("c22","c22");
  hp_k->Divide(hp1);
  hp_k->Draw();
  //=============================================================================

  TCanvas *c3 = new TCanvas("c3","c3");
  he11->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  he11->GetYaxis()->SetTitle("n#sigma_{e} Efficiency"); // integral range / whole range, value got from .dat,already saved
  //he1->Draw("PE");
  he11->Draw("same PE");
  he1->Draw("same PE");
  //=============================================================================
  
  TCanvas *c4 = new TCanvas("c4","c4");
  he->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  he->GetYaxis()->SetTitle("#DeltaLL(e-#pi) Efficiency");
  he->Draw("PE");
  
}

