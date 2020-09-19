Double_t func(Double_t *x, Double_t *par){
  Double_t arg = 0;
  Double_t val = 0;
  if(par[2]!=0 && par[1]!=1){
    arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
    val = par[0]*sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1]));//exp(arg*(1/(1-par[1])));
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
  if(par[4]!=0 && par[5]!=1){
    arg1 = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[5]*(1-par[4]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
    val += par[3]*sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg1,-1/(1-par[4]));//exp(arg*(1/(1-par[1])));
  }
  return val;
}
void calcWeights(TH1D* g, TH1D* r, TH1D *w){
  for(int i = 1; i < g->GetNbinsX()+1 ; i++){
    double temp1 = g->GetBinContent(i);
    double temp2 = r->GetBinContent(i);
    if(temp2>0)w->SetBinContent(i,temp1/temp2);
    else w->SetBinContent(i,0);
  }
}
void calcWeightsFit(TF1* g, TF1* r, TH1D *w){
  for(int i = 1; i < w->GetNbinsX()+1 ; i++){
    double temp1 = g->Integral(w->GetBinLowEdge(i),w->GetBinLowEdge(i)+w->GetBinWidth(i));
    double temp2 = r->Integral(w->GetBinLowEdge(i),w->GetBinLowEdge(i)+w->GetBinWidth(i));
    if(temp2>0)w->SetBinContent(i,temp1/temp2);
    else w->SetBinContent(i,0);
  }
}
void convYield(TH1D * h){
  for(int i=1;i<h->GetNbinsX()+1;i++){
    double temp1 = h->GetBinContent(i);
    double temp2 = h->GetBinWidth(i);
    double temp3 = h->GetBinCenter(i);
    h->SetBinContent(i,temp1/2./TMath::Pi()/temp2/temp3);
  }
}

void data(TGraphErrors *gpi,TGraphErrors *ggamma);
void getHist(TH1D* h,TF1 *f);
void getEff(TH1D* h,TH1D* g,TH1D* e){
  int bins = h->GetNbinsX();
  for(int i = 1 ; i < bins+1 ; i++){
    double temp = h->GetBinContent(i);
    double temp1 = g->GetBinContent(i);
    if(temp1>0 && temp>0){
      e->SetBinContent(i,temp/temp1);
      e->SetBinError(i,temp/temp1*sqrt(1/temp + 1/temp1));
    }else{
      e->SetBinContent(i,0);
      e->SetBinError(i,0);
    }
  }
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


void runGen_Central5(int save = 0){
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGraphErrors *gpi = new TGraphErrors();
  TGraphErrors *ggamma = new TGraphErrors();
  data(gpi,ggamma);
  TGaxis::SetMaxDigits(4);
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  //////////////////////////////////////////////////////////////////
  TF1 *fpi = new TF1("fpi",func,0.1,20,3);
  fpi->SetParameter(0,1.44381e+04);
  fpi->SetParameter(1,9.18928e-01);
  fpi->SetParameter(2,1.10008e-01);
  
  TF1 *fgamma = new TF1("fgamma",func1,1,20,3);
  fgamma->SetParameter(0,7.38384e+03);
  fgamma->SetParameter(1,8.73512e-01);
  fgamma->SetParameter(2,9.10666e-03);
  TF1 *fpimc = new TF1("fpimc",func,0.1,20,3);
  //fpimc->SetParameter(0,1.44381e+04);
  //fpimc->SetParameter(1,9.18928e-01);
  //fpimc->SetParameter(2,1.10008e-01);
  TF1 *fetamc = new TF1("fetamc",func,0.1,20,3);
  //fetamc->SetParameter(0,1.44381e+04);
  //fetamc->SetParameter(1,9.18928e-01);
  //fetamc->SetParameter(2,1.10008e-01);
  TF1 *fgammamc = new TF1("fgammamc",func1,1,20,3); // not used here
  //fgammamc->SetParameter(0,7.38384e+08);
  //fgammamc->SetParameter(1,8.73512e-01);
  //fgammamc->SetParameter(2,9.10666e-03);

  // zyj below Pi0_Gamma_Ratio.root is not used here
  TFile *fi = new TFile("root/Pi0_Gamma_Ratio.root");
  auto ratio = (TH1F*) fi->Get("ratio");
  auto pi0_weights = (TH1F*) fi->Get("pi0_weights");
  auto gamma_weights = (TH1F*) fi->Get("gamma_weights");

  TH2D* gen_eta  = new TH2D("gen_eta","gen_eta",200,0,20,200,0,20);gen_eta->Sumw2();
  TH2D* gen_pi0  = new TH2D("gen_pi0","gen_pi0",200,0,20,200,0,20);gen_pi0->Sumw2();
  TH2D* gen_gamma  = new TH2D("gen_gamma","gen_gamma",200,0,20,200,0,20);gen_gamma->Sumw2();
  TH2D* fit_eta  = new TH2D("fit_eta","fit_eta",200,0,20,200,0,20);fit_eta->Sumw2();
  TH2D* fit_pi0  = new TH2D("fit_pi0","fit_pi0",200,0,20,200,0,20);fit_pi0->Sumw2();
  TH2D* fit_gamma  = new TH2D("fit_gamma","fit_gamma",200,0,20,200,0,20);fit_gamma->Sumw2();
  TH1D* weight_eta  = new TH1D("weight_eta","weight_eta",200,0,20);weight_eta->Sumw2();
  TH1D* weight_pi0  = new TH1D("weight_pi0","weight_pi0",200,0,20);weight_pi0->Sumw2();
  TH1D* weight_gamma  = new TH1D("weight_gamma","weight_gamma",200,0,20);weight_gamma->Sumw2();
  TH1D* weight_new_eta  = new TH1D("weight_new_eta","weight_new_eta",200,0,20);weight_new_eta->Sumw2();
  TH1D* weight_new_pi0  = new TH1D("weight_new_pi0","weight_new_pi0",200,0,20);weight_new_pi0->Sumw2();
  TH1D* weight_new_gamma  = new TH1D("weight_new_gamma","weight_new_gamma",200,0,20);weight_new_gamma->Sumw2();
  TH1D* hist_eta  = new TH1D("hist_eta","hist_eta",200,0,20);hist_eta->Sumw2();
  TH1D* hist_pi0  = new TH1D("hist_pi0","hist_pi0",200,0,20);hist_pi0->Sumw2();
  TH1D* hist_gamma  = new TH1D("hist_gamma","hist_gamma",200,0,20);hist_gamma->Sumw2();
  TH2D* write_eta  = new TH2D("write_eta","write_eta",200,0,20,200,0,20);write_eta->Sumw2();
  TH2D* write_pi0  = new TH2D("write_pi0","write_pi0",200,0,20,200,0,20);write_pi0->Sumw2();
  TH2D* write_gamma  = new TH2D("write_gamma","write_gamma",200,0,20,200,0,20);write_gamma->Sumw2();
  TH1D* ratio1 = new TH1D("ratio1","ratio1",200,0,20);ratio1->Sumw2();
  TH1D* fine_eta  = new TH1D("fine_eta","fine_eta",2000,0,20);fine_eta->Sumw2();
  TH1D* fine_pi0  = new TH1D("fine_pi0","fine_pi0",2000,0,20);fine_pi0->Sumw2();
  TH1D* fine_gamma  = new TH1D("fine_gamma","fine_gamma",2000,0,20);fine_gamma->Sumw2();
  float s_eta;
  float s_pt;
  float s_id;
  float s_head;
  float s_parentid;
  float s_gparentid;
  float s_ggparentid;
  float s_parentpt;
  float s_gparentpt;
  float s_ggparentpt;
  float m_pt;
  float centrality;
  char dFile[500];
  //==========================================================================
  
  sprintf(dFile,"root/MC_newiso_full_new.root");
  //sprintf(dFile,"/Volumes/YJMAC/Matt_production/MC.root");// zyj
  TFile *f_D = new TFile(dFile);
  TChain *ch2 = (TChain *)f_D->Get("Gen_tree");
  ch2->SetBranchAddress("gen_eta",&s_eta);
  ch2->SetBranchAddress("gen_id",&s_id);
  ch2->SetBranchAddress("gen_pt",&s_pt);
  ch2->SetBranchAddress("gen_parentpt",&m_pt);
  ch2->SetBranchAddress("gen_head",&s_head);
  ch2->SetBranchAddress("gen_parentid",&s_parentid);
  ch2->SetBranchAddress("gen_gparentid",&s_gparentid);
  ch2->SetBranchAddress("gen_ggparentid",&s_ggparentid);
  ch2->SetBranchAddress("event_centrality", &centrality);
  double norm_e = 0;//gen_pi0->Integral();
  double norm_pi0 = 0;//gen_pi0->Integral();
  double norm_eta = 0;//gen_eta->Integral();
  double norm_gamma = 0;//gen_gamma->Integral();
  double norm_pi0_e = 0;//gen_pi0->Integral();
  double norm_eta_e = 0;//gen_eta->Integral();
  double norm_gamma_e = 0;//gen_gamma->Integral();
  TCanvas *cfit = new TCanvas("cfit","pi0");
  gpi->Fit(fpi);
  gpi->Draw("APE");
  fpi->Draw("same");
  
  TCanvas *cfit1 = new TCanvas("cfit1","gamma");
  ggamma->Fit(fgamma,"R");
  ggamma->Draw("APE");
  fgamma->Draw("same");
  
  TH1F *Pi0GammaRatio = new TH1F("Pi0GammaRatio","Pi0GammaRatio",numPtBins,binning);
  for(int i = 1; i<10; i++){
    double temp1 = fpi->Integral(binning[i-1],binning[i]);
    double temp2 = fgamma->Integral(binning[i-1],binning[i]);
    Pi0GammaRatio->SetBinContent(i,temp1/temp2);
  }
  TCanvas *crat = new TCanvas("crat","gamma/pi0 ratio");
  Pi0GammaRatio->Draw();
  double int_gamma = fgamma->Integral(0,20);
  double int_pi0 = fpi->Integral(0,20);
  //int_gamma+= 1.17 *fgamma->Eval(1.17/2);
  //int_pi0+= 0.35 *fpi->Eval(0.35);
  cout << "=============================" << endl;
  cout <<"Total pi0/gamma integral from fit " << int_pi0/int_gamma << endl;
  //if(save){
    for(int i =0;i<ch2->GetEntries();i++){//ch2->GetEntries()
      ch2->GetEntry(i);
      if(centrality<8)continue; //0901
      if(i%1000000==0)cout << "on " << i << " of " << ch2->GetEntries() << endl;
      if(s_id==1 && s_parentid==0)norm_gamma++;
      if(s_id==7 && s_parentid==0)norm_pi0++;
      if(s_id==17 && s_parentid==0)norm_eta++;
      if(!(s_id==2||s_id==3))continue;
      if(s_parentid==0)norm_e++;
      if(s_parentid==17){
        norm_eta_e++;
        gen_eta->Fill(s_pt,m_pt);
        fit_eta->Fill(s_pt,m_pt);
        fine_eta->Fill(m_pt);
      }
      if(s_parentid==7){
        norm_pi0_e++;
        gen_pi0->Fill(s_pt,m_pt);
        fit_pi0->Fill(s_pt,m_pt);
        fine_pi0->Fill(m_pt);
      }
      if(s_parentid==1 && s_head==1 && s_gparentid==0){
        norm_gamma_e++;
        gen_gamma->Fill(s_pt,m_pt);
        fit_gamma->Fill(s_pt,m_pt);
        fine_gamma->Fill(m_pt);
      }
    }
    
    getHist(hist_pi0,fpi); // 把fit 得到的r图线转换成hist
    getHist(hist_gamma,fgamma);
    
    cout << "============Numbers==========" << endl;
    cout << "=============================" << endl;
    cout <<"Total pi0/gamma integral from fit " << int_pi0/int_gamma << endl;
    cout <<"Total e's with no parentid " << norm_e << endl;
    cout <<"Total generated pi0 " << norm_pi0 << endl;
    cout <<"Total generated eta " << norm_eta << endl;
    cout <<"Total generated gamma " << norm_gamma << endl;
    cout <<"Total generated pi0->e " << norm_pi0_e << endl;
    cout <<"Total generated eta->e " << norm_eta_e << endl;
    cout <<"Total generated gamma->e " << norm_gamma_e << endl;
    cout << "=================================" << endl;
    if(norm_pi0>0)   cout <<"Total generated eta/pi0 " << norm_eta/norm_pi0 << endl;
    if(norm_gamma>0) cout <<"Total generated pi0/gamma " << norm_pi0/norm_gamma << endl;
    cout << "=================================" << endl;
    cout << "============End Numbers==========" << endl;
    
    auto fit_pi0_y = (TH1D*)fit_pi0->ProjectionY();
    auto fit_gamma_y = (TH1D*)fit_gamma->ProjectionY();
    auto fit_eta_y = (TH1D*)fit_eta->ProjectionY();
    fit_pi0_y->SetLineColor(kRed);
    fit_pi0_y->SetMarkerColor(kRed);
    fit_gamma_y->SetLineColor(kRed);
    fit_gamma_y->SetMarkerColor(kRed);
    fit_eta_y->SetLineColor(kBlue);
    fit_eta_y->SetMarkerColor(kBlue);
    
    norm(hist_pi0);
    norm(hist_gamma);
    norm(fit_pi0_y);
    norm(fit_gamma_y);
    norm(fit_eta_y);
    
    //convYield(fit_pi0_y);
    //convYield(fit_eta_y);
    //convYield(fit_gamma_y);
    //fit_pi0_y->Fit(fpimc);
    //fit_eta_y->Fit(fetamc);
    //fit_gamma_y->Fit(fgammamc);
    /*
    TCanvas *chist = new TCanvas("chist","pi0 comapre");
    //hist_pi0->Draw("PE");
    fit_pi0_y->Draw("same PE");
    fit_eta_y->Draw("same PE");
    TCanvas *chists1 = new TCanvas("chist1","gamma compare");
    //hist_gamma->Draw("PE");
    fit_gamma_y->Draw("same PE");
    */
    calcWeights(hist_pi0,fit_pi0_y,weight_pi0);
    calcWeights(hist_pi0,fit_eta_y,weight_eta);
    calcWeights(hist_gamma,fit_gamma_y,weight_gamma);
    
    //calcWeightsFit(fpi,fpimc,weight_pi0);
    //calcWeightsFit(fpi,fetamc,weight_eta);
    //calcWeightsFit(fgamma,fgammamc,weight_gamma);
    
    //weight_pi0->Scale(1);//pi0->eX BR
    //weight_eta->Scale(norm_pi0/norm_eta*0.0069/0.01174*0.45);//pi0->eX BR
    //weight_gamma->Scale(norm_pi0/norm_gamma);// gamma/pi0 generation/Dalitz decay of pi0
    //weight_gamma->Scale(int_gamma/int_pi0);// gamma/pi0 production -> coNstant
    /*
    TCanvas *cweight = new TCanvas("cweight","pi0 weights");
    weight_pi0->Draw();
    TCanvas *cweight1 = new TCanvas("cweight1","eta weights");
    weight_eta->Draw();
    TCanvas *cweight2 = new TCanvas("cweight2","gamma weights");
    weight_gamma->Draw();*/
    
    for(int i =0;i<ch2->GetEntries();i++){//ch2->GetEntries()
      ch2->GetEntry(i);
      if(centrality<8)continue; //0901
      if(i%1000000==0)cout << "on " << i << " of " << ch2->GetEntries() << endl;
      if(!(s_id==2||s_id==3))continue;
      if(s_parentid==17){
        int bin = weight_eta->FindBin(m_pt);
        write_eta->Fill(s_pt,m_pt,weight_eta->GetBinContent(bin));
      }
      if(s_parentid==7){
        int bin = weight_pi0->FindBin(m_pt);
        write_pi0->Fill(s_pt,m_pt,weight_pi0->GetBinContent(bin));
        //write_pi0->Fill(s_pt,m_pt,1.5);
      }
      if(s_parentid==1 && s_head==1 && s_gparentid==0){
        int bin = weight_gamma->FindBin(m_pt);
        write_gamma->Fill(s_pt,m_pt,weight_gamma->GetBinContent(bin));
      }
    }
  
    write_pi0->SetMarkerColor(kBlue);
    write_pi0->SetLineColor(kBlue);
    write_gamma->SetMarkerColor(kBlue);
    write_gamma->SetLineColor(kBlue);
    write_eta->SetMarkerColor(kBlue);
    write_eta->SetLineColor(kBlue);
    
    TH1D *pi0_x = write_pi0->ProjectionX();
    TH1D *pi0_y = write_pi0->ProjectionY();
    TH1D *gen_pi0_x = gen_pi0->ProjectionX();
    TH1D *gen_pi0_y = gen_pi0->ProjectionY();
    
    TH1D *gamma_x = write_gamma->ProjectionX();
    TH1D *gamma_y = write_gamma->ProjectionY();
    TH1D *gen_gamma_x = gen_gamma->ProjectionX();
    TH1D *gen_gamma_y = gen_gamma->ProjectionY();
    
    TH1D *eta_x = write_eta->ProjectionX();
    TH1D *eta_y = write_eta->ProjectionY();
    TH1D *gen_eta_x = gen_eta->ProjectionX();
    TH1D *gen_eta_y = gen_eta->ProjectionY();
    /*
    TCanvas *c1 = new TCanvas("c1","pi0 pt");
    gen_pi0_y->Draw();
    pi0_y->Draw("same");
  */
    TCanvas *c2 = new TCanvas("c2","pi0->e pt");
    gen_pi0_x->Draw();
    pi0_x->Draw("same");
  //return ;
    TCanvas *c11 = new TCanvas("c11","gamma pt");
    gen_gamma_y->Draw();
    gamma_y->Draw("same");
    TCanvas *c22 = new TCanvas("c22","gamma-> e pt");
    gen_gamma_x->Draw();
    gamma_x->Draw("same");
    TCanvas *c111 = new TCanvas("c111","eta pt");
    gen_eta_y->Draw();
    eta_y->Draw("same");
    TCanvas *c222 = new TCanvas("c222","eta-> e pt");
    gen_eta_x->Draw();
    eta_x->Draw("same");
    
    calcWeights(pi0_x,gen_pi0_x,weight_new_pi0);
    //calcWeights(pi0_y,gen_pi0_y,weight_new_pi0); // zyj test

    calcWeights(eta_x,gen_eta_x,weight_new_eta);
    calcWeights(gamma_x,gen_gamma_x,weight_new_gamma);
    
    
    //weight_new_pi0->Scale(0.01174);//pi0->eX BR
    //weight_new_eta->Scale(0.0069);//eta->eX BR
    //weight_new_eta->Scale(norm_pi0/norm_eta*0.45);// generation and eta/pi0 production
    //weight_new_gamma->Scale(norm_pi0/norm_gamma);// gamma/pi0 generation
    //weight_new_gamma->Scale(int_gamma/int_pi0);// gamma/pi0 production -> coNstant
    
    //  weight_pi0->Scale(1);//pi0->eX BR
    //  weight_gamma->Scale(norm_pi0/norm_gamma/0.01174);// gamma/pi0 generation/Dalitz decay of pi0
    //  weight_gamma->Scale(int_gamma/int_pi0);// gamma/pi0 production -> coNstant
    
    TFile ff1("root_yj/NewWeights_yj_central5.root","RECREATE");
    weight_new_pi0->Write("pi0_new_weights");
    weight_new_eta->Write("eta_new_weights");
    weight_new_gamma->Write("gamma_new_weights");
    weight_pi0->Write("pi0_weights");
    weight_eta->Write("eta_weights");
    weight_gamma->Write("gamma_weights");
    gen_pi0->Write();
    gen_eta->Write();
    gen_gamma->Write();
    write_pi0->Write();
    write_gamma->Write();
    write_eta->Write();
    fit_pi0_y->Write("fit_pi0_y");
    fit_gamma_y->Write("fit_gamma_y");
    fit_eta_y->Write("fit_eta_y");
    Pi0GammaRatio->Write();
  //}else{
  /*
    TFile *ff1 = new TFile("root_yj/NewWeights.root","READ");
    // draw weighted pt gen of e and mother, do comparison
    write_pi0 = (TH2D*)ff1->Get("write_pi0");
    write_gamma  = (TH2D*)ff1->Get("write_gamma");
    write_eta  = (TH2D*)ff1->Get("write_eta");
    Pi0GammaRatio = (TH1F*)ff1->Get("Pi0GammaRatio");
    
    pi0_x = write_pi0->ProjectionX();// zyj decay e pt dist. after weight
    eta_x =write_eta->ProjectionX();
    gamma_x =write_gamma->ProjectionX();
   
    pi0_y =write_pi0->ProjectionY(); // zyj decay mother pt dist. after weight
    eta_y =write_eta->ProjectionY();
    gamma_y =write_gamma->ProjectionY();
    TH1F* comp1_pi0= new TH1F("comp1_pi0","",numPtBins,binning);//,binningwrite_pi0->GetNbinsX(),0,20);
    TH1F* comp1_eta= new TH1F("comp1_eta","",numPtBins,binning);//,binningwrite_pi0->GetNbinsX(),0,20);
    TH1F* comp1_gamma= new TH1F("comp1_gamma","",numPtBins,binning);//write_pi0->GetNbinsX(),0,20);
    for(int i = 1; i<10;i++){
      int bin1 = pi0_y->FindBin(binning[i-1]);
      int bin2 = pi0_y->FindBin(binning[i]);
      double temp1 = pi0_y->Integral(bin1,bin2);//GetBinContent(i);
      double temp2 = eta_y->Integral(bin1,bin2);//GetBinContent(i);
      double temp3 = gamma_y->Integral(bin1,bin2);//GetBinContent(i);
      double temp = temp1+temp2+temp3;
      comp1_pi0->SetBinContent(i,temp1/temp3);
      comp1_eta->SetBinContent(i,temp2/temp3);
      comp1_pi0->SetBinError(i,0);
      comp1_eta->SetBinError(i,0);
    }
   
    cout << "Scaling factor for pi0 and eta " << Pi0GammaRatio->Integral()/comp1_pi0->Integral() << endl;
    comp1_pi0->Scale(Pi0GammaRatio->Integral()/comp1_pi0->Integral());
    
    TCanvas *c7 = new TCanvas("c7","ratio");
    comp1_pi0->SetMarkerColor(kBlue);
    comp1_pi0->SetLineColor(kBlue);
    comp1_eta->SetMarkerColor(kGreen-2);
    comp1_eta->SetLineColor(kGreen-2);
    comp1_pi0->Draw("PE same");
    comp1_eta->Draw("PE same");
    
    
    pi0_y->Divide(gamma_y);
    eta_y->Divide(gamma_y);
    //pi0_y->Draw("PE");
    //eta_y->SetLineColor(kRed);
    //eta_y->SetMarkerColor(kRed);
    //eta_y->Draw("same PE");
    Pi0GammaRatio->Draw("same hist");
    
    TH1F* comp_pi0= new TH1F("comp_pi0","",numPtBins,binning);//,binningwrite_pi0->GetNbinsX(),0,20);
    TH1F* comp_eta= new TH1F("comp_eta","",numPtBins,binning);//,binningwrite_pi0->GetNbinsX(),0,20);
    TH1F* comp_gamma= new TH1F("comp_gamma","",numPtBins,binning);//write_pi0->GetNbinsX(),0,20);
    
    for(int i = 1; i<10;i++){
      int bin1 = pi0_x->FindBin(binning[i-1]);
      int bin2 = pi0_x->FindBin(binning[i]);
      double temp1 = pi0_x->Integral(bin1,bin2)/80*0.0174;//GetBinContent(i);
      double temp2 = eta_x->Integral(bin1,bin2)/80*0.0174;//GetBinContent(i);
      double temp3 = gamma_x->Integral(bin1,bin2)*0.01*0.8/(1.21-1);//GetBinContent(i);
      double temp = temp1+temp2+temp3;
      comp_pi0->SetBinContent(i,temp1/temp);
      comp_eta->SetBinContent(i,temp2/temp);
      comp_gamma->SetBinContent(i,temp3/temp);
      comp_pi0->SetBinError(i,0);
      comp_eta->SetBinError(i,0);
      comp_gamma->SetBinError(i,0);
    }
   
    comp_pi0->SetMarkerColor(kBlue);
    comp_pi0->SetLineColor(kBlue);
    comp_eta->SetMarkerColor(kGreen-2);
    comp_eta->SetLineColor(kGreen-2);
    comp_gamma->SetMarkerColor(kCyan);
    comp_gamma->SetLineColor(kCyan);
    TCanvas *c8 = new TCanvas("c8","comp");
    comp_pi0->Draw("PE same");
    comp_eta->Draw("PE same");
    comp_gamma->Draw("PE same");
  }*/
}//End



void data(TGraphErrors *gpi,TGraphErrors *ggamma){
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
