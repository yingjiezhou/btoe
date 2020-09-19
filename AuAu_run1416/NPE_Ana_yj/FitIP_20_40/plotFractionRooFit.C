void norm(TH1F *h);
void plotFractionRooFit(int pass=1){
  
  gROOT->ProcessLine(".x ~/myStyle.C");
  char file[50];
  sprintf(file,"./%i/yields.dat",101); //mb 11
  ifstream data(file);
  char file1[50];
  sprintf(file1,"./%i/yields.dat",2); // ht
  ifstream data1(file1);
  
  TFile * f= new TFile("../../NPE_MC/Ana/root_yj/HF_plots.root");
  //TFile * f= new TFile("../../NPE_MC/Ana/root_yj/HF_plots_FONLL.root");
  auto dcapt_d_all=(TH2F*)f->Get("dcapt_d_all");
  auto dcapt_b_all=(TH2F*)f->Get("dcapt_b_all");
  auto pt_d_all =(TH1F*)dcapt_d_all->ProjectionY();
  auto pt_b_all =(TH1F*)dcapt_b_all->ProjectionY();
  norm(pt_b_all);
  norm(pt_d_all);
  pt_b_all->Scale(pt_d_all->Integral()/pt_b_all->Integral()/132.35);
  for(int i = 1 ;i<pt_b_all->GetNbinsX()+1;i++){
    double temp1 = pt_b_all->GetBinContent(i);
    double temp2 = pt_d_all->GetBinContent(i);
    if(temp1>0)pt_b_all->SetBinContent(i,temp1/(temp1+temp2));
    else pt_b_all->SetBinContent(i,0);
  }
  
  
  //TFile *fk = new TFile("/project/projectdirs/starprod/rnc/mkelsey/forYifei/electronFraction/finalBtoEFraction.root");
  //kunsu = (TH1F*) fk->Get("run14_bF_sts");
  //kunsu->SetMarkerColor(kRed);
  //kunsu->SetMarkerStyle(25);
  //kunsu->SetLineColor(kRed);
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
      eub.push_back(eu-y1); // not used
      edb.push_back(y1-ed);
      int bin = hb_t->FindBin(x1);
      hb_t->SetBinContent(bin,y1*lumi);
      hb_t->SetBinError(bin,(y1-ed)*lumi);
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
  double x_b[100];
  double xe_b[100];
  double y_bc[100];
  double e_bc[100];
  for(int i = 0;i<100;i++){
    x_b[i] = x[i];
    xe_b[i] = 0;
    y_bc[i] = yb[i]/(yb[i]+yc[i]);
    e_bc[i] = 0;
    
    
  }
  TGraphErrors *gb = new TGraphErrors(100,x_b,y_bc,xe_b,e_bc);
  
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  double binning1[numPtBins+1]={0.6+0.1,1+0.1,1.2+0.1,1.5+0.1,2.0+0.1,2.5+0.1,3.5+0.1,4.5+0.1,5.5+0.1,8.5};
  double binning2[numPtBins+1]={0.6-0.1,1-0.1,1.2-0.1,1.5-0.1,2.0-0.1,2.5-0.1,3.5-0.1,4.5-0.1,5.5-0.1,8.5};
  
  
  TH1F *h = new TH1F("h","",numPtBins,binning);
  
  TH1F *hfracb1 = new TH1F("hfracb1","",numPtBins,binning);
  TH1F *hfracc1 = new TH1F("hfracc1","",numPtBins,binning);
  TH1F *hfrace1 = new TH1F("hfrace1","",numPtBins,binning);
  TH1F *hfrach1 = new TH1F("hfrach1","",numPtBins,binning);
  
  TH1F *hfracb2 = new TH1F("hfracb2","",numPtBins,binning);
  TH1F *hfracc2 = new TH1F("hfracc2","",numPtBins,binning);
  TH1F *hfrace2 = new TH1F("hfrace2","",numPtBins,binning);
  TH1F *hfrach2 = new TH1F("hfrach2","",numPtBins,binning);
  
  
  TH1F *hfracb1_ht = new TH1F("hfracb1_ht","",numPtBins,binning);
  TH1F *hfracc1_ht = new TH1F("hfracc1_ht","",numPtBins,binning);
  TH1F *hfrace1_ht = new TH1F("hfrace1_ht","",numPtBins,binning);
  TH1F *hfrach1_ht = new TH1F("hfrach1_ht","",numPtBins,binning);
  
  TH1F *hfracb2_ht = new TH1F("hfracb2_ht","",numPtBins,binning);
  TH1F *hfracc2_ht = new TH1F("hfracc2_ht","",numPtBins,binning);
  TH1F *hfrace2_ht = new TH1F("hfrace2_ht","",numPtBins,binning);
  TH1F *hfrach2_ht = new TH1F("hfrach2_ht","",numPtBins,binning);
  
  TH1F *hline = new TH1F("hline","",numPtBins,binning);
  TH1F *h1 = new TH1F("h1","",numPtBins,binning2);
  TH1F *h2 = new TH1F("h2","",numPtBins,binning);
  TH1F *h3 = new TH1F("h3","",numPtBins,binning);
  TH1F *h4 = new TH1F("h4","",numPtBins,binning);
  TH1F *hb = new TH1F("hb","",numPtBins,binning);
  TH1F *hc = new TH1F("hc","",numPtBins,binning);
  TH1F *he = new TH1F("he","",numPtBins,binning);
  TH1F *hh = new TH1F("hh","",numPtBins,binning);
  
  TH1F *h1_ht = new TH1F("h1_ht","",numPtBins,binning1);
  TH1F *h2_ht = new TH1F("h2_ht","",numPtBins,binning);
  TH1F *h3_ht = new TH1F("h3_ht","",numPtBins,binning);
  TH1F *h4_ht = new TH1F("h4_ht","",numPtBins,binning);
  TH1F *hb_ht = new TH1F("hb_ht","",numPtBins,binning);
  TH1F *hc_ht = new TH1F("hc_ht","",numPtBins,binning);
  TH1F *he_ht = new TH1F("he_ht","",numPtBins,binning);
  TH1F *hh_ht = new TH1F("hh_ht","",numPtBins,binning);
  
  if(data.is_open()){
    while(!data.eof()){
      char out[50];
      int pT;
      double y1;
      double e1;
      double y2;
      double e2;
      double y3;
      double e3;
      double y4;
      double e4;
      double pur;
      double pure;
      double eff;
      
      
      double fb1;
      double fb2;
      double fc1;
      double fc2;
      double fe1;
      double fe2;
      double fh1;
      double fh2;
      
      double br;
      double bkgr;
      double nper;
      double bre;
      double bkgre;
      double npere;
      double ere;
      double er;
      data >> pT >> y1 >> e1 >> fb1 >> fb2 >> y2 >> e2 >> fc1 >> fc2 >> y3 >> e3 >> fe1 >> fe2 >> y4 >> e4 >> fh1 >> fh2 >> br >> bre >> bkgr>>bkgre >> nper >> npere >> er >> ere >> pur >> pure;
      if(pT!=0){
        h1->SetBinContent(pT,br);
        h1->SetBinError(pT,bre);
        h2->SetBinContent(pT,(y1+y2)/y3);
        //cout<<"NPE PE ratio is :::::::::::::: "<<(y1+y2)/y3<<endl;
        //h2->SetBinError(pT,0);
        h2->SetBinError(pT,(y1+y2)/y3 * sqrt((e1+e2)*(e1+e2)/(y1+y2)/(y1+y2)+e3*e3/y3/y3));
        
        hb->SetBinContent(pT,y1/(y1+y2+y3+y4));
        hb->SetBinError(pT,y1/(y1+y2+y3+y4)*e1/y2);
        hc->SetBinContent(pT,y2/(y1+y2+y3+y4));
        hc->SetBinError(pT,y2/(y1+y2+y3+y4)*e2/y2);
        he->SetBinContent(pT,y3/(y1+y2+y3+y4));
        he->SetBinError(pT,y3/(y1+y2+y3+y4)*0.0000001);
        hh->SetBinContent(pT,y4/(y1+y2+y3+y4));
        hh->SetBinError(pT,y4/(y1+y2+y3+y4)*e4/y4);
        // fb1
        h4->SetBinContent(pT,1-pur);
        h4->SetBinError(pT,pure);
        hline->SetBinContent(pT,1);
      }
    }
    
  }
  else {
    cout <<"Nope \n";
  }
  hline->SetBinContent(1,1);
  hline->SetBinContent(3,1);
  hline->SetBinContent(3,1);
  hline->SetBinContent(4,1);
  hline->SetBinContent(5,1);
  hline->SetBinContent(6,1);
  hline->SetBinContent(7,1);
  hline->SetBinContent(8,1);
  hline->SetBinContent(9,1);
  
  
  if(data1.is_open()){
    while(!data1.eof()){
      char out[50];
      int pT;
      double y1;
      double e1;
      double y2;
      double e2;
      double y3;
      double e3;
      double y4;
      double e4;
      double pur;
      double pure;
      double eff;
      
      double fb1;
      double fb2;
      double fc1;
      double fc2;
      double fe1;
      double fe2;
      double fh1;
      double fh2;
      
      double br;
      double bkgr;
      double nperat;
      double bre;
      double bkgre;
      double nperate;
      double er;
      double ere;
      double nper;
      double npere;
      data1 >> pT >> y1 >> e1 >> fb1 >> fb2 >> y2 >> e2 >> fc1 >> fc2 >> y3 >> e3 >> fe1 >> fe2 >> y4 >> e4 >> fh1 >> fh2 >> br >> bre >> bkgr>>bkgre >> nper >> npere >>  er >> ere >> pur >> pure;
      if(pT!=0){
        cout<<"========================================="<<endl;
        cout<<pT<<"is  "<<br<<endl;
        cout<<"========================================="<<endl;
        h1_ht->SetBinContent(pT,br);
        h1_ht->SetBinError(pT,bre);
        h4_ht->SetBinContent(pT,1-pur);
        h4_ht->SetBinError(pT,pure);
        h2_ht->SetBinContent(pT,(y1+y2)/y3);
        h2_ht->SetBinError(pT,(y1+y2)/y3 * sqrt((e1+e2)*(e1+e2)/(y1+y2)/(y1+y2)+e3*e3/y3/y3));
        hb_ht->SetBinContent(pT,y1/(y1+y2+y3+y4));
        hb_ht->SetBinError(pT,y1/(y1+y2+y3+y4)*e1/y1);
        hc_ht->SetBinContent(pT,y2/(y1+y2+y3+y4));
        hc_ht->SetBinError(pT,y2/(y1+y2+y3+y4)*e2/y2);
        he_ht->SetBinContent(pT,y3/(y1+y2+y3+y4));
        he_ht->SetBinError(pT,y3/(y1+y2+y3+y4)*0.0000001);
        hh_ht->SetBinContent(pT,y4/(y1+y2+y3+y4));
        hh_ht->SetBinError(pT,y4/(y1+y2+y3+y4)*e4/y4);
      }
    }
    
  }
  else {
    cout <<"Nope \n";
  }

  for(int i =1; i<10;i++){
    double temp1 = h1->GetBinContent(i);
    double temp2 = h1->GetBinError(i);
    double temp3 = h1_ht->GetBinContent(i);
    double temp4 = h1_ht->GetBinError(i);
    if(temp1>0 && temp3>0){
      double temp = temp1/temp2/temp2 + temp3/temp4/temp4;
      double er = 1/temp2/temp2 + 1/temp4/temp4;
      h->SetBinContent(i,temp/er);
      h->SetBinError(i,sqrt(1/er));
    }else if(temp1>0 && temp3==0){
      h->SetBinContent(i,temp1);
      h->SetBinError(i,temp2);
    }
    else if(temp1==0 && temp3>0){
      h->SetBinContent(i,temp3);
      h->SetBinError(i,temp4);
    }
  }

  TCanvas *c1 = new TCanvas("c1","c1");
  h1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  h1->GetXaxis()->SetRangeUser(1,8.5);
  h1->GetYaxis()->SetRangeUser(0,1);
  h1_ht->SetMarkerStyle(24);
  h1_ht->SetMarkerColor(kBlue);
  h1_ht->SetLineColor(kBlue);
  h1->SetMarkerStyle(25);
  h1->SetMarkerColor(kGreen-2);
  h1->SetLineColor(kGreen-2);
  h1->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
  
  TLegend *leg1 = new TLegend(0.5,0.2,0.9,0.5);
  leg1->AddEntry(h1,"New Results MB","PE");
  leg1->AddEntry(gb,"FONLL pp 200GeV","L");
  //leg1->AddEntry(pt_b_all,"HF template MB","PE");
  
  h1->Draw();
  h1_ht->SetMarkerStyle(26);
  h1_ht->Draw("same");
  //kunsu->Draw("same");
  gb->SetLineStyle(7);
  gb->Draw("same");
  //pt_b_all->SetLineColor(kMagenta);
  //pt_b_all->Draw("same hist");
  leg1->Draw("same");
  c1->SaveAs("plots_yj/b_fraction_comp_yj.pdf");
  c1->SaveAs("plots_yj/b_fraction_comp_yj.C");
  //===================================================================
  // comp 0930
     TH1F *hmb = new TH1F("hmb","hmb",numPtBins,binning);
     TH1F *hht = new TH1F("hht","hht",numPtBins,binning);
  for(int i = 5; i<numPtBins; i++){
    cout << "on pT bin " << i << " " << endl;
    double val = h1->GetBinContent(i);
    double val_e = h1->GetBinError(i);
    hmb->SetBinContent(i,val);
    hmb->SetBinError(i,val_e);
  }
  
  for(int i = 6; i<numPtBins+1; i++){
    cout << "on pT bin " << i << " " << endl;
    double val = h1_ht->GetBinContent(i);
    double val_e = h1_ht->GetBinError(i);
    hht->SetBinContent(i,val);
    hht->SetBinError(i,val_e);
  }
  
  TCanvas *c5 = new TCanvas("c5","c5");
  hmb->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  hmb->GetXaxis()->SetRangeUser(1,8.5);
  hmb->GetYaxis()->SetRangeUser(0,1);
  hht->SetMarkerStyle(25);
  hht->SetMarkerColor(kRed);
  hht->SetLineColor(kRed);
  hmb->SetMarkerStyle(24);
  hmb->SetMarkerColor(kBlue);
  hmb->SetLineColor(kBlue);
  hmb->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
  
  TLegend *leg3 = new TLegend(0.5,0.2,0.9,0.45);
  leg3->AddEntry(hmb,"Min. Bias","PLE");
  leg3->AddEntry(hht,"High Tower","PLE");
  //leg1->AddEntry(pt_b_all,"HF template MB","PE");
  TPaveText *Name = new TPaveText(0.164,0.733,0.55,0.9,"BRNDC");
  Name->AddText("STAR 20-40%");
  Name->SetFillColorAlpha(0, 0);
  Name->SetTextAlign(12);
  Name->SetBorderSize(0);
  
  hmb->Draw("E1");
  hht->Draw("same E1");
  leg3->Draw("same");
  Name->Draw("same");
  c5->SaveAs("plots_yj/b_fraction_final_yj.pdf");
  c5->SaveAs("plots_yj/b_fraction_final_yj.C");
  

  /*

  TCanvas *c11 = new TCanvas("c11","c1");
  h->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  h->GetXaxis()->SetRangeUser(1,8.5);
  h->GetYaxis()->SetRangeUser(0,1);
  h->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
  h->Draw("same");
  
  //kunsu->Draw("same");
  //gb->SetLineColor(kRed-2);
  gb->Draw("same");
  */
  TCanvas *c2 = new TCanvas("c2","c2");
  h2->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  h2->GetYaxis()->SetTitle("NPE/PE");
  h2->Draw("same");
  h2_ht->SetLineColor(kRed);
  c2->SaveAs("plots_yj/NPE_PE_ratio_yj.pdf");
  //h2_ht->Draw("same");
  TCanvas *c3 = new TCanvas("c3","c3");
  hb->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  hb->GetYaxis()->SetTitle("Relative Fraction");
  hb->GetYaxis()->SetRangeUser(0,1);
  hb->SetLineColor(kGreen-2);
  hb->SetMarkerColor(kGreen-2);
  hc->SetLineColor(kMagenta);
  hc->SetMarkerColor(kMagenta);
  he->SetLineColor(kOrange-1);
  he->SetMarkerColor(kOrange-1);
  hh->SetLineColor(kRed);
  hh->SetMarkerColor(kRed);
  h4->SetLineColor(kRed);
  h4->SetMarkerColor(kRed);
  h4->SetMarkerStyle(26);
  TLegend *leg = new TLegend(0.2,0.6,0.5,0.9);
  leg->AddEntry(hb,"#it{b}#rightarrow #it{e}","PE");
  leg->AddEntry(hc,"#it{c}#rightarrow #it{e}","PE");
  leg->AddEntry(he,"Photonic #it{e}","PE");
  leg->AddEntry(hh,"Hadrons","PE");
  leg->AddEntry(h4,"1-Purity","l");
  hb->Draw("PE same");
  hc->Draw("PE same");
  he->Draw("PE same");
  hh->Draw("PE same");
  h4->SetLineStyle(5);
  hline->SetLineStyle(5);
  h4->Draw("histe same");
  leg->Draw("same");
  c3->SaveAs("plots_yj/bfraction_yj.pdf");
  
  /*
  
  TCanvas *c33 = new TCanvas("c33","c3 ht");
  hb_ht->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  hb_ht->GetYaxis()->SetTitle("Relative Fraction");
  hb_ht->GetYaxis()->SetRangeUser(0,1);
  hb_ht->SetLineColor(kGreen-2);
  hb_ht->SetMarkerColor(kGreen-2);
  hc_ht->SetLineColor(kMagenta);
  hc_ht->SetMarkerColor(kMagenta);
  he_ht->SetLineColor(kOrange-1);
  he_ht->SetMarkerColor(kOrange-1);
  hh_ht->SetLineColor(kRed);
  hh_ht->SetMarkerColor(kRed);
  h4_ht->SetLineColor(kRed);
  h4_ht->SetMarkerColor(kRed);
  h4_ht->SetMarkerStyle(26);
  hb_ht->Draw("PE same");
  hc_ht->Draw("PE same");
  he_ht->Draw("PE same");
  hh_ht->Draw("PE same");
  h4_ht->SetLineStyle(5);
  hline->SetLineStyle(5);
  h4_ht->Draw("histe same");
  leg->Draw("same");
  
  */
  TCanvas *c4 = new TCanvas("c4","c4");
  hb_t->SetLineColor(kGreen-2);
  hc_t->SetLineColor(kMagenta);
  hc_t->Draw(" hist");
  hb_t->Draw("same hist");
  c4->SaveAs("plots_yj/pt_b_d_yj.pdf");
  cout << "Norm for c is " << hc_t->Integral() << endl;
  cout << "Norm for b is " << hb_t->Integral() << endl;
  cout << "Norm for c/b is " << hc_t->Integral()/hb_t->Integral() << endl;
}


void norm(TH1F *h){
  //h->Rebin(4);
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

