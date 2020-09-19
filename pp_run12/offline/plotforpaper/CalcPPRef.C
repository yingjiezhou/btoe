void CalcPPRef(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  double x3[7] = {2.5,3.5,4.5,5.5,6.5,7.5,8.5};
  double x2[7] = {2.5+0.1,3.5+0.1,4.5+0.1,5.5+0.1,6.5+0.1,7.5+0.1,8.5+0.1};
  double x1[7] = {2.5-0.1,3.5-0.1,4.5-0.1,5.5-0.1,6.5-0.1,7.5-0.1,8.5-0.1};
  
  double y1[6] = {0.31697,0.418603,0.48473,0.61381,0.52239,0.486374};
  double e1[6] = {0.0603727,0.0664046,0.0943932,0.0603727,0.0664046,0.0943932};
  double e1h[6] = {0.0234,0.0545,0.103,0.0381,0.0298,0.112};
  double e1l[6] = {0.0301,0.0321,0.0749,0.0825,0.0604,0.0373};
  
//  TFile *run12 = new TFile("run12NPEh_rBPoints.root");
//  auto StatError = (TGraphAsymmErrors*)run12->Get("StatError");
//  auto SystError =(TGraphAsymmErrors*)run12->Get("systError");
  
  double y2[6] = {0.2098,0.334,0.5235,0.55833,0.68383,0.716};
  double e2[6] = {0.084,0.08133,0.05333,0.064,0.0933,0.16133};
  double e2l[6] = {0.01866,0.01733,0.012,0.012,0.02933,0.02533};
  double e2h[6] = {0.02534,0.01867,0.01333,0.01067,0.028,0.032};
  
//  for(int i =0;i<6;i++){
//    double _x;double _y;
//    StatError->GetPoint(i,_x,_y);
//    double e1 = StatError->GetErrorYlow(i);
//    double e22 = StatError->GetErrorYhigh(i);
//    double e3 = SystError->GetErrorYlow(i);
//    double e4 = SystError->GetErrorYhigh(i);
//    cout << "Run12 data " <<  _x << " " << _y << " " << e1 << " " << e22 << " " << e3 << " " << e4 << endl;
//    y2[i] = _y;
//    e2[i] = e1; // to do
//    e2l[i] = e3;
//    e2h[i] = e4;
//  }
//
  
  
  double e2la[6];
  double e1la[6];
  double e2ha[6];
  double e1ha[6];
  TH1F *h1 = new TH1F("h1","h1",6,x1);
  TH1F *h2 = new TH1F("h2","h2",6,x2);
  TH1F *h3 = new TH1F("h3","h3",6,x3);
  TGraphAsymmErrors *h1_sys = new TGraphAsymmErrors(6);
  TGraphAsymmErrors *h2_sys = new TGraphAsymmErrors(6);
  TGraphAsymmErrors *h3_sys = new TGraphAsymmErrors(6);
  for(int i =0;i<6;i++){
    h1->SetBinContent(i+1,y1[i]);
    h2->SetBinContent(i+1,y2[i]);
    h1->SetBinError(i+1,e1[i]);
    h2->SetBinError(i+1,e2[i]);
    
    h1_sys->SetPoint(i,h1->GetBinCenter(i+1),y1[i]);
    h2_sys->SetPoint(i,h2->GetBinCenter(i+1),y2[i]);
    h1_sys->SetPointError(i,0,0,e1l[i],e1h[i]);
    h2_sys->SetPointError(i,0,0,e2l[i],e2h[i]);
    
    e1la[i] = sqrt(e1l[i]*e1l[i] + e1[i]*e1[i]);
    e1ha[i] = sqrt(e1h[i]*e1h[i] + e1[i]*e1[i]);
    e2la[i] = sqrt(e2l[i]*e2l[i] + e2[i]*e2[i]);
    e2ha[i] = sqrt(e2h[i]*e2h[i] + e2[i]*e2[i]);
    
  }
  double weights[3] ={6.6E-01,2.4E-01,9.9E-02};
  double comb1; double comb2; double comb3;
  cout << endl;
  for(int i =0;i<6;i++){
    double b1 = (e1ha[i] - e1la[i]) / sqrt(2.*TMath::Pi());
    double b2 = (e2ha[i] - e2la[i]) / sqrt(2.*TMath::Pi());
    double a1 = (e1ha[i] - e1la[i])/2.;
    double a2 = (e2ha[i] - e2la[i])/2.;
    double s1 = (e1ha[i] + e1la[i])/2.;
    double s2 = (e2ha[i] + e2la[i])/2.;
    
    double v1 = s1*s1 +(1-2./TMath::Pi())*a1*a1;
    double v2 = s2*s2 +(1-2./TMath::Pi())*a2*a2;
    double w1 = 1/v1;
    double w2 = 1/v2;
    
    double sum = ((y1[i]-b1)*w1 + (y2[i]-b2)*w2) / (w1+w2);
    double er = 1/sqrt(w1+w2);
    double stat = 1/sqrt(1/e1[i]/e1[i]+1/e2[i]/e2[i]);
    
    double sys = sqrt(1/(w1+w2) - stat*stat);
    h3->SetBinContent(i+1,sum);
    h3->SetBinError(i+1,stat);
    
    h3_sys->SetPoint(i,h3->GetBinCenter(i+1),sum);
    h3_sys->SetPointError(i,0,0,sys,sys);
    cout<<h3->GetBinCenter(i+1)<<"   "<<sum<<" , "<<sys<<endl;
    //    cout << sys << ",";// << stat << " " << sys << endl;
    if(i>2){
      comb1+=sum*weights[i-3];
      comb2+=stat*weights[i-3];
      comb3+=sys*weights[i-3];
    }
  }
  cout << endl;
  cout <<"combined last bins " << comb1 << " " << comb2 << " " << comb3 << endl;
  //    double weights[3] = {6.6E-01,2.4E-01,9.9E-02};
  
  
  TCanvas *c1 = new TCanvas("c1","c1");
  h1->GetXaxis()->SetTitle("p_{T} (GeV/#it{c})");
  h1->GetYaxis()->SetTitle("#it{b}#rightarrow e / NPE");
  h1->GetYaxis()->SetRangeUser(0,1);
  h3->SetLineWidth(1);h2->SetLineWidth(1);h1->SetLineWidth(1);
  h2->SetLineColor(kRed);h2->SetMarkerColor(kRed);h2->SetMarkerStyle(24);
  h2_sys->SetLineColor(kRed);h2_sys->SetMarkerColor(kRed);h2_sys->SetMarkerStyle(22);
  h1->SetLineColor(kBlue);h1->SetMarkerColor(kBlue);h1->SetMarkerStyle(23);
  h1_sys->SetLineColor(kBlue);h1_sys->SetMarkerColor(kBlue);h1_sys->SetMarkerStyle(23);
  
  TLegend *leg = new TLegend(0.2,0.7,0.45,0.9);
  leg->AddEntry(h1,"Run6","PE");
  leg->AddEntry(h2,"Run12","PE");
  leg->AddEntry(h3,"Average","PE");
  
  
  h1->Draw("PE X0");
  h2->Draw("same PE X0");
  h3->Draw("same PE X0");
  h1_sys->Draw("same []");
  h2_sys->Draw("same []");
  h3_sys->Draw("same []");
  leg->Draw("same");
  
  c1->SaveAs("Zach_b.pdf");
  auto sf = new TFile("ppBfraction.root", "RECREATE");
  sf->cd();
  h3->Write("zach_stat");
  h3_sys->Write("zach_sys");
  sf->Close();
}
