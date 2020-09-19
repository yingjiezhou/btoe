void norm(TH1F *h);
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

void HF_DCA_yj(int save = 0, int weight_data=0){
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  //////////////////////////////////////////////////////////////////

    TFile * f= new TFile("root_yj/HF_plots.root"); //yj
    //TFile * f= new TFile("root/root/HF_plots.root");
    auto dcapt_d_all=(TH2F*)f->Get("dcapt_d_all");
    auto dcapt_b_all=(TH2F*)f->Get("dcapt_b_all");
    auto dcapt_d0=(TH2F*)f->Get("dcapt_d0");
    auto dcapt_b0=(TH2F*)f->Get("dcapt_b0");
    auto dcapt_dp=(TH2F*)f->Get("dcapt_dp");
    auto dcapt_bp=(TH2F*)f->Get("dcapt_bp");
    auto dcapt_ds=(TH2F*)f->Get("dcapt_ds");
    auto dcapt_bs=(TH2F*)f->Get("dcapt_bs");
    auto dcapt_lc=(TH2F*)f->Get("dcapt_lc");
    auto dcapt_lb=(TH2F*)f->Get("dcapt_lb");

    auto phipt_d_all=(TH2F*)f->Get("phipt_d_all");
    auto phipt_b_all=(TH2F*)f->Get("phipt_b_all");
    auto phipt_d0=(TH2F*)f->Get("phipt_d0");
    auto phipt_b0=(TH2F*)f->Get("phipt_b0");
    auto phipt_dp=(TH2F*)f->Get("phipt_dp");
    auto phipt_bp=(TH2F*)f->Get("phipt_bp");
    auto phipt_ds=(TH2F*)f->Get("phipt_ds");
    auto phipt_bs=(TH2F*)f->Get("phipt_bs");
    auto phipt_lc=(TH2F*)f->Get("phipt_lc");
    auto phipt_lb=(TH2F*)f->Get("phipt_lb");
    
    auto dcapt_lin_d_all=(TH2F*)f->Get("dcapt_lin_d_all");
    auto dcapt_lin_b_all=(TH2F*)f->Get("dcapt_lin_b_all");
    auto dcapt_lin_d0=(TH2F*)f->Get("dcapt_lin_d0");
    auto dcapt_lin_b0=(TH2F*)f->Get("dcapt_lin_b0");
    auto dcapt_lin_dp=(TH2F*)f->Get("dcapt_lin_dp");
    auto dcapt_lin_bp=(TH2F*)f->Get("dcapt_lin_bp");
    auto dcapt_lin_ds=(TH2F*)f->Get("dcapt_lin_ds");
    auto dcapt_lin_bs=(TH2F*)f->Get("dcapt_lin_bs");
    auto dcapt_lin_lc=(TH2F*)f->Get("dcapt_lin_lc");
    auto dcapt_lin_lb=(TH2F*)f->Get("dcapt_lin_lb");
    
    dcapt_d_all->SetLineColor(kRed);
    dcapt_d_all->SetFillColor(kRed);
    dcapt_d_all->SetFillStyle(3007);
    dcapt_d_all->SetMarkerColor(kRed);
    dcapt_b_all->SetLineColor(kBlue);
    dcapt_b_all->SetFillColor(kBlue);
    dcapt_b_all->SetFillStyle(3006);
    dcapt_b_all->SetMarkerColor(kBlue);
    dcapt_d0->SetLineColor(kMagenta);
    dcapt_d0->SetMarkerColor(kMagenta);
    dcapt_dp->SetLineColor(kRed);
    dcapt_dp->SetMarkerColor(kRed);
    dcapt_ds->SetLineColor(kOrange);
    dcapt_ds->SetMarkerColor(kOrange);
    dcapt_lc->SetLineColor(1);
    dcapt_lc->SetMarkerColor(1);
    dcapt_b0->SetLineColor(kGreen-2);
    dcapt_b0->SetMarkerColor(kGreen-2);
    dcapt_bp->SetLineColor(kBlue);
    dcapt_bp->SetMarkerColor(kBlue);
    dcapt_bs->SetLineColor(kCyan+1);
    dcapt_bs->SetMarkerColor(kCyan+1);
    dcapt_lb->SetLineColor(51);
    dcapt_lb->SetMarkerColor(51);
    dcapt_lin_d_all->SetLineColor(kRed);
    dcapt_lin_d_all->SetMarkerColor(kRed);
    dcapt_lin_b_all->SetLineColor(kBlue);
    dcapt_lin_b_all->SetMarkerColor(kBlue);
    dcapt_lin_d0->SetLineColor(kMagenta);
    dcapt_lin_d0->SetMarkerColor(kMagenta);
    dcapt_lin_dp->SetLineColor(kRed);
    dcapt_lin_dp->SetMarkerColor(kRed);
    dcapt_lin_ds->SetLineColor(kOrange);
    dcapt_lin_ds->SetMarkerColor(kOrange);
    dcapt_lin_lc->SetLineColor(1);
    dcapt_lin_lc->SetMarkerColor(1);
    dcapt_lin_b0->SetLineColor(kGreen-2);
    dcapt_lin_b0->SetMarkerColor(kGreen-2);
    dcapt_lin_bp->SetLineColor(kBlue);
    dcapt_lin_bp->SetMarkerColor(kBlue);
    dcapt_lin_bs->SetLineColor(kCyan+1);
    dcapt_lin_bs->SetMarkerColor(kCyan+1);
    dcapt_lin_lb->SetLineColor(51);
    dcapt_lin_lb->SetMarkerColor(51);
    
    phipt_d_all->SetLineColor(kRed);
    phipt_d_all->SetMarkerColor(kRed);
    phipt_b_all->SetLineColor(kBlue);
    phipt_b_all->SetMarkerColor(kBlue);
    
    // ========== DCA plots
    double low = 2;
    double high = 2.5;
    phipt_d_all->GetYaxis()->SetRangeUser(low,high);
    phipt_b_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_d_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_b_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_d0->GetYaxis()->SetRangeUser(low,high);
    dcapt_b0->GetYaxis()->SetRangeUser(low,high);
    dcapt_dp->GetYaxis()->SetRangeUser(low,high);
    dcapt_bp->GetYaxis()->SetRangeUser(low,high);
    dcapt_ds->GetYaxis()->SetRangeUser(low,high);
    dcapt_bs->GetYaxis()->SetRangeUser(low,high);
    dcapt_lc->GetYaxis()->SetRangeUser(low,high);
    dcapt_lb->GetYaxis()->SetRangeUser(low,high);
    auto dca_d_all =(TH1F*)dcapt_d_all->ProjectionX();
    auto dca_b_all =(TH1F*)dcapt_b_all->ProjectionX();
    
    auto dca_d0 =(TH1F*)dcapt_d0->ProjectionX();
    auto dca_b0 =(TH1F*)dcapt_b0->ProjectionX();
    auto dca_dp =(TH1F*)dcapt_dp->ProjectionX();
    auto dca_bp =(TH1F*)dcapt_bp->ProjectionX();
    auto dca_ds =(TH1F*)dcapt_ds->ProjectionX();
    auto dca_bs =(TH1F*)dcapt_bs->ProjectionX();
    auto dca_lb =(TH1F*)dcapt_lb->ProjectionX();
    auto dca_lc =(TH1F*)dcapt_lc->ProjectionX();
    
    auto pt_d0 =(TH1F*)dcapt_d0->ProjectionY();
    auto pt_b0 =(TH1F*)dcapt_b0->ProjectionY();
    auto pt_dp =(TH1F*)dcapt_dp->ProjectionY();
    auto pt_bp =(TH1F*)dcapt_bp->ProjectionY();
    auto pt_ds =(TH1F*)dcapt_ds->ProjectionY();
    auto pt_bs =(TH1F*)dcapt_bs->ProjectionY();
    auto pt_lb =(TH1F*)dcapt_lb->ProjectionY();
    auto pt_lc =(TH1F*)dcapt_lc->ProjectionY();
    
    
    dcapt_lin_d_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_b_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_d0->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_b0->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_dp->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_bp->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_ds->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_bs->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_lc->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_lb->GetYaxis()->SetRangeUser(low,high);
    auto dca_lin_d_all =(TH1F*)dcapt_lin_d_all->ProjectionX();
    auto dca_lin_b_all =(TH1F*)dcapt_lin_b_all->ProjectionX();
    auto dca_lin_d0 =(TH1F*)dcapt_lin_d0->ProjectionX();
    auto dca_lin_b0 =(TH1F*)dcapt_lin_b0->ProjectionX();
    auto dca_lin_dp =(TH1F*)dcapt_lin_dp->ProjectionX();
    auto dca_lin_bp =(TH1F*)dcapt_lin_bp->ProjectionX();
    auto dca_lin_ds =(TH1F*)dcapt_lin_ds->ProjectionX();
    auto dca_lin_bs =(TH1F*)dcapt_lin_bs->ProjectionX();
    auto dca_lin_lb =(TH1F*)dcapt_lin_lb->ProjectionX();
    auto dca_lin_lc =(TH1F*)dcapt_lin_lc->ProjectionX();
    auto phi_d_all =(TH1F*)phipt_d_all->ProjectionX();
    auto phi_b_all =(TH1F*)phipt_b_all->ProjectionX();
    
    norm(phi_d_all);
    norm(phi_b_all);
    norm(dca_d_all);
    norm(dca_b_all);
    norm(dca_d0);
    norm(dca_b0);
    norm(dca_dp);
    norm(dca_bp);
    norm(dca_ds);
    norm(dca_bs);
    norm(dca_lc);
    norm(dca_lb);
    
    norm(dca_lin_d_all);
    norm(dca_lin_b_all);
    norm(dca_lin_d0);
    norm(dca_lin_b0);
    norm(dca_lin_dp);
    norm(dca_lin_bp);
    norm(dca_lin_ds);
    norm(dca_lin_bs);
    norm(dca_lin_lc);
    norm(dca_lin_lb);
    TLegend *leg1 = new TLegend(0.2,0.5,0.4,0.9);
    
    leg1->AddEntry(dca_d0,"#it{D}^{0}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_dp,"#it{D}^{+}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_ds,"#it{D}^{+}_{s}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_lc,"#it{#Lambda}^{+}_{c}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_b0,"#it{B}^{0}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_bp,"#it{B}^{+}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_bs,"#it{B}^{0}_{s}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_lb,"#it{#Lambda}^{0}_{b}#rightarrow #it{e}X","l");
    
    TCanvas *c1 = new TCanvas("c1","DCA Shapes");
    dca_d0->GetYaxis()->SetTitle("Arb. Units");
    dca_d0->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    dca_d0->GetXaxis()->SetRangeUser(-6,0);
    dca_b0->GetYaxis()->SetTitle("Arb. Units");
    dca_b0->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    dca_b0->GetXaxis()->SetRangeUser(-6,0);
    dca_d0->Draw("hist");
    dca_dp->Draw("same hist");
    dca_b0->Draw("same hist");
    dca_bp->Draw("same hist");
    dca_ds->Draw("same hist");
    dca_bs->Draw("same hist");
    dca_lc->Draw("same hist");
    dca_lb->Draw("same hist");
    leg1->Draw("same");
    //leg->Draw("same");
    //}
    c1->SaveAs("plots_HF_yj/All_DCA_Shapes.pdf");
    
    TCanvas *c11 = new TCanvas("c11","charm Shapes");
    dca_d0->Draw("hist");
    dca_dp->Draw("same hist");
    dca_ds->Draw("same hist");
    dca_lc->Draw("same hist");
    c11->SaveAs("plots_HF_yj/charm_Shapes.pdf");

    
    TCanvas *c111 = new TCanvas("c111","b Shapes");
    dca_b0->Draw("hist");
    dca_bp->Draw("same hist");
    dca_bs->Draw("same hist");
    dca_lb->Draw("same hist");
    c111->SaveAs("plots_HF_yj/bottom_Shapes.pdf");

    
    TCanvas *c1111 = new TCanvas("c1111","Comb. Shapes");
    TLegend *leg = new TLegend(0.2,0.5,0.4,0.9);
    dca_b_all->SetFillStyle(3004);
    dca_d_all->SetFillStyle(3005);
    leg->AddEntry(dca_d_all,"#it{c}#rightarrow#it{e}X","l");
    leg->AddEntry(dca_b_all,"#it{b}#rightarrow#it{e}X","l");
    dca_d_all->GetYaxis()->SetTitle("Arb. Units");
    dca_d_all->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    dca_d_all->GetXaxis()->SetRangeUser(-6,0);
    dca_d_all->Draw("hist");
    dca_b_all->Draw("same hist");
    leg->Draw("same");
    c1111->SaveAs("plots_HF_yj/Comb_Shapes.pdf");

    
    TCanvas *c2 = new TCanvas("c2","all lin Shapes");
    dca_lin_d_all->GetYaxis()->SetTitle("Arb. Units");
    dca_lin_d_all->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    dca_lin_d_all->GetXaxis()->SetRangeUser(-6,0);
    dca_lin_d_all->Draw("hist");
    dca_lin_b_all->Draw("same hist");
    leg->Draw("same");
    c2->SaveAs("plots_HF_yj/all_lin.pdf");

    
    TCanvas *c3 = new TCanvas("c3","phi res");
    phi_d_all->GetYaxis()->SetTitle("Arb. Units");
    phi_d_all->GetXaxis()->SetTitle("#Delta#phi");
    phi_d_all->GetXaxis()->SetRangeUser(-1,1);
    phi_d_all->Draw("hist");
    phi_b_all->Draw("same hist");
    leg->Draw("same");
    c3->SaveAs("plots_HF_yj/delta_phi.pdf");

    
    low = 0;
    high = 8.5;
    dcapt_d0->GetYaxis()->SetRangeUser(low,high);
    dcapt_b0->GetYaxis()->SetRangeUser(low,high);
    dcapt_dp->GetYaxis()->SetRangeUser(low,high);
    dcapt_bp->GetYaxis()->SetRangeUser(low,high);
    dcapt_ds->GetYaxis()->SetRangeUser(low,high);
    dcapt_bs->GetYaxis()->SetRangeUser(low,high);
    dcapt_lc->GetYaxis()->SetRangeUser(low,high);
    dcapt_lb->GetYaxis()->SetRangeUser(low,high);
    pt_d0 =(TH1F*)dcapt_d0->ProjectionY();
    pt_b0 =(TH1F*)dcapt_b0->ProjectionY();
    pt_dp =(TH1F*)dcapt_dp->ProjectionY();
    pt_bp =(TH1F*)dcapt_bp->ProjectionY();
    pt_ds =(TH1F*)dcapt_ds->ProjectionY();
    pt_bs =(TH1F*)dcapt_bs->ProjectionY();
    pt_lb =(TH1F*)dcapt_lb->ProjectionY();
    pt_lc =(TH1F*)dcapt_lc->ProjectionY();
    
    
    TH1F *pt_d_all = new TH1F("pt_d_all","pt_d_all",pt_d0->GetNbinsX(),0,8.5);pt_d_all->Sumw2();
    TH1F *pt_b_all = new TH1F("pt_b_all","pt_b_all",pt_d0->GetNbinsX(),0,8.5);pt_b_all->Sumw2();
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    TH1F * charm_1 = new TH1F("charm_1","charm_1", numPtBins,binning);
    TH1F * bottom_1 = new TH1F("bottom_1","bottom_1", numPtBins,binning);
    TH1F * charm_2 = new TH1F("charm_2","charm_2", numPtBins,binning);
    TH1F * bottom_2 = new TH1F("bottom_2","bottom_2", numPtBins,binning);
    TH1F * charm_3 = new TH1F("charm_3","charm_3", numPtBins,binning);
    TH1F * bottom_3 = new TH1F("bottom_3","bottom_3", numPtBins,binning);
    TH1F * charm_4 = new TH1F("charm_4","charm_4", numPtBins,binning);
    TH1F * bottom_4 = new TH1F("bottom_4","bottom_4", numPtBins,binning);
    TH1F * charm_yield = new TH1F("charm_yield","charm_yield", numPtBins,binning);
    TH1F * bottom_yield = new TH1F("bottom_yield","bottom_yield", numPtBins,binning);
    
    double num_b0 = 11392251;
    double num_bp = 11101472;
    double num_bs = 11141042;
    double num_lb = 8165929;
    double num_dp = 10079412;
    double num_d0 = 10056703;
    double num_ds = 2053032;
    double num_lc = 10092100;
    
    double d0_sl = 0.0649;
    double dp_sl = 0.1607;
    double ds_sl = 0.065;
    double lc_sl = 0.045;
    double d0_cs = 41;
    double dp_cs = 18;//41./2.;//18;
    double ds_cs = 15;//0.4*41;//15;
    double lc_cs = 69;//41;
    
    double b0_sl = 0.1030;
    double bp_sl = 0.1108;
    double bs_sl = 0.1024;
    double lb_sl = 0.1026;
    double b0_cs = 1;
    double bp_cs = 1;
    double bs_cs = 0.122*2;
    double lb_cs = 1;
    double scale = 2.83609e+08/num_d0; // zyj???
    pt_d0->Scale(scale*d0_sl);
    pt_dp->Scale(dp_sl*dp_cs/d0_cs * num_d0/num_dp * scale); // pt spectrue for e decay channel???
    pt_ds->Scale(ds_sl*ds_cs/d0_cs * num_d0/num_ds * scale);
    pt_lc->Scale(lc_sl*lc_cs/d0_cs * num_d0/num_lc * scale);
    pt_d_all->Add(pt_d0);
    pt_d_all->Add(pt_dp);
    pt_d_all->Add(pt_ds);
    pt_d_all->Add(pt_lc);
    double forscale = 0.29;//num_d0*(1+num_dp/num_d0*0.5+num_ds/num_d0*0.4+num_lc/num_d0*69./41.) / (num_b0*(1+num_bp/num_b0+num_bs/num_d0*0.122+num_lb/num_b0*0.259)); // zyj charm and bottom hadron number??
    double scale1 = 2.83609e+08/forscale/137/num_b0*0.36; // zyj 137 *0.36????
    cout << "Scaling factors " << scale << " " << scale1 << endl;
    
    pt_b0->Scale(scale1*b0_sl);
    pt_bp->Scale(bp_sl*bp_cs/b0_cs * num_b0/num_bp * scale1);
    pt_bs->Scale(bs_sl*bs_cs/b0_cs * num_b0/num_bs * scale1);
    pt_lb->Scale(lb_sl*lb_cs/b0_cs * num_b0/num_lb * scale1);
    
    pt_b_all->Add(pt_b0);
    pt_b_all->Add(pt_bp);
    pt_b_all->Add(pt_bs);
    pt_b_all->Add(pt_lb);
    
    double finalScale = 1;//0.15;//pt_b_all->Integral()/pt_d_all->Integral();
    cout << "c/b scaling " << finalScale << endl;
    pt_b_all->Scale(finalScale);
    pt_b0->Scale(finalScale);
    pt_bp->Scale(finalScale);
    pt_bs->Scale(finalScale);
    pt_lb->Scale(finalScale);
    //=====================================================================================
    // frac. dist.
    
    double eff[9]={0.633673698548,  0.666336412584,  0.67659412964,   0.71909796477,   0.702890272245,  0.69985391904,   0.729281142186,  0.7624432562,    0.68022809943}; // HFT eff? how about TPC?
    for(int i =0;i<10;i++){
      int bin1 = pt_d0->FindBin(binning[i]);
      int bin2 = pt_d0->FindBin(binning[i+1]);
      double temp1 = pt_d0->Integral(bin1,bin2);
      double temp2 = pt_dp->Integral(bin1,bin2);
      double temp3 = pt_ds->Integral(bin1,bin2);
      double temp4 = pt_lc->Integral(bin1,bin2);
      double temp = (temp1+temp2+temp3+temp4);//zyj = pt_d_all->Integral(bin1,bin2);??
      charm_yield->SetBinContent(i+1,temp*eff[i]);
      if(temp>0)charm_yield->SetBinError(i+1,sqrt(1/(temp*eff[i]))); // zyj = pt_d_all* eff??
      charm_1->SetBinContent(i+1,temp1/temp);
      charm_2->SetBinContent(i+1,temp2/temp);
      charm_3->SetBinContent(i+1,temp3/temp);
      charm_4->SetBinContent(i+1,temp4/temp);
      temp1 = pt_b0->Integral(bin1,bin2);
      temp2 = pt_bp->Integral(bin1,bin2);
      temp3 = pt_bs->Integral(bin1,bin2);
      temp4 = pt_lb->Integral(bin1,bin2);
      temp = temp1+temp2+temp3+temp4;
      bottom_1->SetBinContent(i+1,temp1/temp);
      bottom_2->SetBinContent(i+1,temp2/temp);
      bottom_3->SetBinContent(i+1,temp3/temp);
      bottom_4->SetBinContent(i+1,temp4/temp);
      bottom_yield->SetBinContent(i+1,temp*eff[i]);
      if(temp>0)bottom_yield->SetBinError(i+1,sqrt(1/(temp*eff[i])));
    }
    TLegend *leg5 = new TLegend(0.6,0.7,0.9,0.9);
    leg5->AddEntry(charm_1,"D^{0}#rightarrow eX","l");
    leg5->AddEntry(charm_2,"D^{+}#rightarrow eX","l");
    leg5->AddEntry(charm_3,"D_{s}#rightarrow eX","l");
    leg5->AddEntry(charm_4,"#Lambda_{c}#rightarrow eX","l");
    TLegend *leg55 = new TLegend(0.6,0.7,0.9,0.9);
    leg55->AddEntry(bottom_1,"B^{0}#rightarrow eX","l");
    leg55->AddEntry(bottom_2,"B^{+}#rightarrow eX","l");
    leg55->AddEntry(bottom_3,"B_{s}#rightarrow eX","l");
    leg55->AddEntry(bottom_4,"#Lambda_{b}#rightarrow eX","l");
    
    charm_1->SetLineColor(kMagenta);
    charm_1->SetMarkerColor(kMagenta);
    charm_2->SetLineColor(kRed);
    charm_2->SetMarkerColor(kRed);
    charm_3->SetLineColor(kOrange);
    charm_3->SetMarkerColor(kOrange);
    charm_4->SetLineColor(1);
    charm_4->SetMarkerColor(1);
    bottom_1->SetLineColor(kGreen-2);
    bottom_1->SetMarkerColor(kGreen-2);
    bottom_2->SetLineColor(kBlue);
    bottom_2->SetMarkerColor(kBlue);
    bottom_3->SetLineColor(kCyan+1);
    bottom_3->SetMarkerColor(kCyan+1);
    bottom_4->SetLineColor(51);
    bottom_4->SetMarkerColor(51);
    TCanvas *c_c = new TCanvas("c_c","fracs",1000,500);
    c_c->Divide(2,1);
    c_c->cd(1);
    charm_1->GetYaxis()->SetRangeUser(0,1);
    charm_1->GetYaxis()->SetTitle("Relative Fraction");
    charm_1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    bottom_1->GetYaxis()->SetRangeUser(0,1);
    bottom_1->GetYaxis()->SetTitle("Relative Fraction");
    bottom_1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    charm_1->Draw("hist");
    charm_2->Draw("hist same");
    charm_3->Draw("hist same");
    charm_4->Draw("hist same");
    leg5->Draw("same");
    c_c->cd(2);
    bottom_1->Draw("hist");
    bottom_2->Draw("hist same");
    bottom_3->Draw("hist same");
    bottom_4->Draw("hist same");
    leg55->Draw("same");
    c_c->SaveAs("plots_HF_yj/frac_pt.pdf");

    //=====================================================================================
    // pt dist.
    TCanvas *c_pt = new TCanvas("c_pt","pts",1000,500);
    c_pt->Divide(2,1);
    c_pt->cd(1);
    //pt_d0->GetYaxis()->SetRangeUser(0.001,2);
    pt_d0->GetYaxis()->SetTitle("Normalized dN/dp_{T}");
    pt_b0->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    //pt_b0->GetYaxis()->SetRangeUser(0.001,2);
    pt_b0->GetYaxis()->SetTitle("Normalized dN/dp_{T}");
    pt_b0->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    pt_d_all->SetLineColor(kGray+1);
    pt_d_all->SetLineStyle(7);
    pt_b_all->SetLineColor(kGray+1);
    pt_b_all->SetLineStyle(7);
    pt_d0->Draw("hist");
    pt_dp->Draw("hist same");
    pt_ds->Draw("hist same");
    pt_lc->Draw("hist same");
    pt_d_all->DrawClone("hist same");
    leg5->Draw("same");
    c_pt->cd(2);
    pt_b0->Draw("hist");
    pt_bp->Draw("hist same");
    pt_bs->Draw("hist same");
    pt_lb->Draw("hist same");
    pt_b_all->DrawClone("hist same");
    leg55->Draw("same");
    c_pt->SaveAs("plots_HF_yj/pt.pdf");

    //=====================================================================================
    // all pt dist.
    TCanvas *c22 = new TCanvas("c22","all pt Shapes");
    //norm(pt_b_all);
    //norm(pt_d_all);
    pt_d_all->SetLineColor(kRed);
    pt_b_all->SetLineColor(kBlue);
    pt_d_all->Draw("hist");
    pt_b_all->DrawClone("same hist");
    c22->SaveAs("plots_HF_yj/all_pt.pdf");

    //=====================================================================================
    // b frac. dist.
    for(int i = 1 ;i<pt_b_all->GetNbinsX()+1;i++){
      double temp1 = pt_b_all->GetBinContent(i);
      double temp2 = pt_d_all->GetBinContent(i);
      if(temp1>0)pt_b_all->SetBinContent(i,temp1/(temp1+temp2));
      else pt_b_all->SetBinContent(i,0);
      pt_b_all->SetBinError(i,0);
    }
    TCanvas *c222 = new TCanvas("c222","pt ratio Shapes");
    pt_b_all->Draw("PE");
    c222->SaveAs("plots_HF_yj/b_c_ratio.pdf");

    
    //=====================================================================================
    // yield * eff. dist.
    TCanvas *cy = new TCanvas("cy","expected yield");
    charm_yield->GetXaxis()->SetTitle("p_{T} [GeV]");
    charm_yield->GetYaxis()->SetTitle("Raw Yield");
    charm_yield->SetLineColor(kRed);
    charm_yield->SetMarkerColor(kRed);
    bottom_yield->SetLineColor(kBlue);
    bottom_yield->SetMarkerColor(kBlue);
    charm_yield->Draw("same");
    bottom_yield->Draw("same");
    cy->SaveAs("plots_HF_yj/yield.pdf");

}

void norm(TH1F *h){
  h->Rebin(4);
  double norm1 = h->Integral();
  int bins = h->GetNbinsX();
  for(int i=1; i<bins+1;i++){
    double temp = h->GetBinContent(i);
    double err = h->GetBinError(i);
    h->SetBinContent(i,temp/norm1);
    h->SetBinError(i,err/norm1);
  }
}


