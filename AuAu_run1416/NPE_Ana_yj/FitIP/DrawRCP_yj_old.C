void norm(TH1F *h);
void getData(char file[], TH1F* h);
void DrawRCP_yj_old()
{//////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  double binning1[numPtBins+1]={0.6+0.15,1,1.2,1.5,2.0+0.15,2.5+0.15,3.5+0.15,4.5+0.15,5.5+0.15,8.5+0.15};
  double binning2[numPtBins+1]={0.6+0.075,1,1.2,1.5,2.0+0.075,2.5+0.075,3.5+0.075,4.5+0.075,5.5+0.075,8.5+0.075};
  double binning4[numPtBins+1]={0.6-0.15,1,1.2,1.5,2.0-0.15,2.5-0.15,3.5-0.15,4.5-0.15,5.5-0.15,8.5-0.15};
  double binning5[numPtBins+1]={0.6-0.15,1,1.2,1.5,2.0-0.22,2.5-0.22,3.5-0.22,4.5-0.22,5.5-0.22,8.5-0.22}; // 0-5%
  double binning3[numPtBins+1]={0.6-0.075,1,1.2,1.5,2.0-0.075,2.5-0.075,3.5-0.075,4.5-0.075,5.5-0.075,8.5-0.075};
  TH1F *hrat = new TH1F("hrat","hrat",numPtBins,binning);
  TH1F *hrat1 = new TH1F("hrat1","hrat1",numPtBins,binning);
  TH1F *hrat2 = new TH1F("hrat2","hrat2",numPtBins,binning1);
  
  TH1F *fb1 = new TH1F("fb1","fb1",numPtBins,binning3);
  TH1F *fb_0_201 = new TH1F("fb_0_201","fb_0_201",numPtBins,binning4);
  TH1F *fb_20_401 = new TH1F("fb_20_401","fb_20_401",numPtBins,binning2);
  TH1F *fb_40_801 = new TH1F("fb_40_801","fb_40_801",numPtBins,binning1);
  TH1F *fb_0_51 = new TH1F("fb_0_51","fb_0_51",numPtBins,binning5); //0909
  
  TFile *f1 = new TFile("../FitIP/root/FracB.root");
  auto fb= (TH1F*)f1->Get("fb");
  auto fb_sys= (TH1F*)f1->Get("fb_sys"); //will not used here
  auto FONLL= (TH1F*)f1->Get("FONLL");
  auto pp= (TH1F*)f1->Get("pp");
  auto pp_sys= (TH1F*)f1->Get("pp_sys");
  fb_sys->SetFillColor(kGray);
  
  //TFile *f11 = new TFile("../FitIP_0_20/root_yj/FracB_0_20_yj.root");
  TFile *f11 = new TFile("../FitIP_0_20/root/FracB_0_20.root");
  auto fb_0_20= (TH1F*)f11->Get("fb_0_20");
  auto fb_sys_0_20= (TH1F*)f11->Get("fb_sys_0_20");

  //auto fb_0_20= (TH1F*)f11->Get("fb");
  //auto fb_sys_0_20= (TH1F*)f11->Get("fb_sys");
  fb_0_201->SetLineColor(kRed);
  fb_0_201->SetMarkerColor(kRed);
  fb_0_201->SetMarkerStyle(26);
  TFile *f2 = new TFile("../FitIP_20_40/root/FracB_20_40.root");
  auto fb_20_40= (TH1F*)f2->Get("fb_20_40");
  auto fb_sys_20_40= (TH1F*)f2->Get("fb_sys_20_40");
  fb_20_401->SetLineColor(kGreen-2);
  fb_20_401->SetMarkerColor(kGreen-2);
  fb_20_401->SetMarkerStyle(27);
  TFile *f3 = new TFile("../FitIP_40_80/root/FracB_40_80.root");
  auto fb_40_80= (TH1F*)f3->Get("fb_40_80");
  auto fb_sys_40_80= (TH1F*)f3->Get("fb_sys_40_80");
  fb_40_801->SetLineColor(kMagenta);
  fb_40_801->SetMarkerColor(kMagenta);
  fb_40_801->SetMarkerStyle(25);
  
  // 0909
  //TH1F *fb_0_5 = new TH1F("fb_0_5","fb_0_5",numPtBins,binning);
  //getData("../../NPE_Ana_Central/FitIP/11/yields.dat", fb_0_5);
  TFile *f4 = new TFile("../../NPE_Ana_Central_resubmit/FitIP/root_yj/FracB_Qing.root");
  auto fb_0_5= (TH1F*)f4->Get("fb");
  fb_0_51->SetLineColor(kRed+2);
  fb_0_51->SetMarkerColor(kRed+3);
  fb_0_51->SetMarkerStyle(28);
  
  for(int i = 5; i<numPtBins+1; i++){
    fb1->SetBinContent(i,fb->GetBinContent(i));
    fb_0_201->SetBinContent(i,fb_0_20->GetBinContent(i));
    fb_20_401->SetBinContent(i,fb_20_40->GetBinContent(i));
    fb_40_801->SetBinContent(i,fb_40_80->GetBinContent(i));
    fb_0_51->SetBinContent(i,fb_0_5->GetBinContent(i));
    fb_0_51->SetBinError(i,fb_0_5->GetBinError(i));
    fb1->SetBinError(i,fb->GetBinError(i));
    fb_0_201->SetBinError(i,fb_0_20->GetBinError(i));
    fb_20_401->SetBinError(i,fb_20_40->GetBinError(i));
    fb_40_801->SetBinError(i,fb_40_80->GetBinError(i));
  }
  
  FONLL->SetLineStyle(7);
  pp->SetLineColor(kBlue);
  pp->SetMarkerColor(kBlue);
  pp->SetMarkerStyle(23);
  pp_sys->SetFillColor(kBlue);
  pp_sys->SetFillStyle(3004);
  TLegend *leg = new TLegend(0.67,0.17,0.94,0.5);
  leg->AddEntry(fb1,"Min. Bias","PE");
  leg->AddEntry(fb_0_51,"0-5%","PE");
  leg->AddEntry(fb_0_201,"0-20%","PE");
  leg->AddEntry(fb_20_401,"20-40%","PE");
  leg->AddEntry(fb_40_801,"40-80%","PE");
  leg->AddEntry(pp,"#it{p+p} #sqrt{s}=200 GeV","PE");
  leg->AddEntry(FONLL,"FONLL","L");
  
  TCanvas *c1 = new TCanvas ("c1","fbs");
  fb1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  fb1->GetYaxis()->SetTitle("N(#it{b}#rightarrow#it{e})/(N(#it{b}#rightarrow#it{e})+N(#it{c}#rightarrow#it{e}))");
  fb1->GetXaxis()->SetRangeUser(0,8.5);
  fb1->GetYaxis()->SetRangeUser(0,1);
  fb1->Draw("E1 X0");
  pp_sys->Draw("E2 same");
  pp->Draw("same PE");
  fb_0_51->Draw("E1 X0 same");
  fb_0_201->Draw("E1 X0 same");
  fb_40_801->Draw("E1 X0 same");
  fb_20_401->Draw("E1 X0 same");
  FONLL->Draw("l same");
  leg->Draw("same");
  c1->SaveAs("plots_yj/cent_depend_resubmit_Qing.pdf");
  //gPad->RedrawAxis();

  return ;
  //=================================================================================
  
  
  double temp3 = 0.;
  double temp33 = 0.;
  for(int i = 1; i<numPtBins+1; i++){
    double temp1 = fb_0_20->GetBinContent(i);
    double temp2 = fb_20_40->GetBinContent(i);
    temp3 = fb_40_80->GetBinContent(i);
    if(i==numPtBins) temp3=0.;
    double temp11 = fb_0_20->GetBinError(i);
    double temp22 = fb_20_40->GetBinError(i);
    temp33 = fb_40_80->GetBinError(i);
    if(i==numPtBins) temp33=0.;
    if(temp1>0 && temp2>0){ // 0,20 / 20,40
      hrat->SetBinContent(i,(1/temp2-1)/(1/temp1-1));
      hrat->SetBinError(i,(1/temp2-1)/(1/temp1-1)*sqrt(temp11*temp11/temp1/temp1/(temp1-1)/(temp1-1)+temp22*temp22/temp2/temp2/(temp2-1)/(temp2-1)));
    }
    if(temp1>0 && temp3>0){ //0,20 / 40,80
      hrat1->SetBinContent(i,(1/temp3-1)/(1/temp1-1));
      hrat1->SetBinError(i,(1/temp3-1)/(1/temp1-1)*sqrt(temp11*temp11/temp1/temp1/(temp1-1)/(temp1-1)+temp33*temp33/temp3/temp3)/(temp3-1)/(temp3-1));
    }
    if(temp2>0 && temp3>0){ // 20,40/ 40,80
      hrat2->SetBinContent(i,(1/temp3-1)/(1/temp2-1));
      hrat2->SetBinError(i,(1/temp3-1)/(1/temp2-1)*sqrt(temp22*temp22/temp2/temp2/(temp2-1)/(temp2-1)+temp33*temp33/temp3/temp3)/(temp3-1)/(temp3-1));
    }
    
  }
  gPad->RedrawAxis();

  //=================================================================================
  
  
  
  TCanvas *c11 = new TCanvas("c11","RCP/RCP");
  char label[100];
  char label1[100];
  char label2[100];
  
  TF1 *fit = new TF1("fit","[0]",2,10);
  fit->SetLineColor(kGreen+2);
  fit->SetLineStyle(5);
  TF1 *fit1 = new TF1("fit1","[0]",2,10);
  fit1->SetLineColor(kBlue);
  fit1->SetLineStyle(6);
  TF1 *fit2 = new TF1("fit2","[0]",2,10);
  fit2->SetLineColor(kRed);
  fit2->SetLineStyle(6);
  
  TF1 *line = new TF1("line","[0]",-1,10);
  line->SetLineStyle(7);
  line->SetParameter(0,1);
  TLegend *legg = new TLegend(0.2,0.6,0.5,0.8);
  TLegend *legg2 = new TLegend(0.2,0.6,0.5,0.8);
 
  hrat->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  hrat->GetYaxis()->SetTitle("R_{CP}^{#it{b}#rightarrow#it{e}}/R_{CP}^{#it{c}#rightarrow#it{e}}");
  hrat->GetXaxis()->SetRangeUser(0,8.5);
  hrat->GetYaxis()->SetRangeUser(0,4);
  hrat->SetLineColor(kGreen+2);
  hrat->SetMarkerColor(kGreen+2);
  hrat->Fit("fit");

  double vall = fit->GetParameter(0);
  double errr = fit->GetParError(0);
  
  
  sprintf(label,"#frac{0-20%%}{20-40%%}: %1.2f #pm %1.2f",vall,errr);
  legg->AddEntry(fit,label,"l");
  
   hrat->Draw("E1 X0");
  //fit->Draw("same");
  line->Draw("same");
  legg->Draw("same");

   TPaveText *Name = new TPaveText(0.182,0.8,0.722,0.94,"BRNDC");
   Name->AddText("STAR Au+Au #sqrt{s_{NN}} = 200 GeV");
   Name->SetFillColorAlpha(0, 0);
   Name->SetTextAlign(12);
   Name->SetBorderSize(0);
   Name->Draw("same");
   c11->SaveAs("plots_yj/Rcp_ratio_20_40.pdf");
  gPad->RedrawAxis();
  //=================================================================================
  
  TCanvas *c12 = new TCanvas ("c12","RCP/RCP2");


   
   hrat1->Fit("fit1");
   hrat2->Fit("fit2");

   double vall1 = fit1->GetParameter(0);
   double errr1 = fit1->GetParError(0);
   double vall2 = fit2->GetParameter(0);
   double errr2 = fit2->GetParError(0);
  sprintf(label1,"#frac{0-20%%}{40-80%%}: %1.2f #pm %1.2f",vall1,errr1);
   sprintf(label2,"#frac{20-40%%}{40-80%%}: %1.2f #pm %1.2f",vall2,errr2);
  legg2->AddEntry(fit1,label1,"l");
  legg2->AddEntry(fit2,label2,"l");
  
  hrat1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
  hrat1->GetYaxis()->SetTitle("R_{CP}^{#it{b}#rightarrow#it{e}}/R_{CP}^{#it{c}#rightarrow#it{e}}");
  hrat1->GetXaxis()->SetRangeUser(0,8.5);
  hrat1->GetYaxis()->SetRangeUser(0,4);
  hrat1->SetLineColor(kBlue);
  hrat1->SetMarkerColor(kBlue);
  hrat2->SetLineColor(kRed);
  hrat2->SetMarkerColor(kRed);
  hrat2->SetMarkerStyle(23);
  hrat1->Draw("E1 X0");
  hrat2->Draw("E1 X0 same");
  line->Draw("same");
  legg2->Draw("same");
  TPaveText *Name2 = new TPaveText(0.182,0.8,0.722,0.94,"BRNDC");
  Name2->AddText("STAR Au+Au #sqrt{s_{NN}} = 200 GeV");
  Name2->SetFillColorAlpha(0, 0);
  Name2->SetTextAlign(12);
  Name2->SetBorderSize(0);
  Name2->Draw("same");
  c12->SaveAs("plots_yj/Rcp_ratio_40_80.pdf");
  
  //=================================================================================

  
  
  
}//End
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

void getData(char file[], TH1F* h){
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
        h->SetBinContent(pT, br);
        h->SetBinError(pT, bre);
      }
    }
  }
  else {
    cout <<"Nope " <<file  << "\n";
  }
  data.close();
}


