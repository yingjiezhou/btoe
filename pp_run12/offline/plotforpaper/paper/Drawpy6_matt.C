void Drawpy6_matt(){
  
  gROOT->ProcessLine(".x ~/myStyle.C");

  // Get Previous Analysis
  Int_t p=0;
  Float_t xP[100],yP[100],dyP[100],dyPSL[100],dyPSH[100],dxPS[100];
  ifstream fp1("/Users/zhouyingjie/Local/PWG/btoe/pp_run12/offline/plotforpaper/Run6Result.txt",ios::in);
  char line[1000];
  while (!fp1.eof()){
    fp1.getline(line,1000);
    sscanf(line,"%f %f %f %f %f",&xP[p],&yP[p],&dyP[p],&dyPSL[p],&dyPSH[p]);
    // printf("L: %f %f\n",xF[l],yF[l]);
    dyPSL[p] = yP[p]-dyPSL[p];   // convert from max/min of error bar to value of
    dyPSH[p] = dyPSH[p] - yP[p]; // error bar for plotting
    dxPS[p] = 0.15;
    xP[p] +=0.2;
    p++;
  }
  fp1.close();
  
  TGraphErrors *grP     = new TGraphErrors(p-1,xP,yP,0,dyP);
  TGraphAsymmErrors *grPS = new TGraphAsymmErrors(p-1,xP,yP,dxPS,dxPS,dyPSL,dyPSH);
  
  grP->SetMarkerSize(1.5);
  grP->SetMarkerStyle(29);
  grP->SetMarkerColor(kBlack);
  grP->SetLineColor(kBlack);
  
  grPS->SetMarkerColor(kBlack);
  grPS->SetLineColor(kBlack);
  grPS->SetLineWidth(2);
  grPS->SetFillColor(kBlack);
  grPS->SetFillStyle(1);
  grPS->SetMarkerStyle(29);
  grPS->SetMarkerSize(1.5);
  
  Double_t p00[2] = {3., 6.};
  Double_t p01[2] = {0.430447, 0.604335};
  Double_t p10[2] = {0.0824667, 0.104065};
  Double_t p11[2] = {0.0262399, 0.0401248};
  Double_t dx[2] = {0.15, 0.15};
  auto gr0 = new TGraphAsymmErrors(2,p00,p01,dx,dx,p10,p11); // matt
  
  TCanvas* fpp = new TCanvas("fpp","sys");
  
  gr0->SetMarkerStyle(20);
  gr0->SetMarkerSize(1.5);
  gr0->SetLineColor(kBlue);
  gr0->SetMarkerColor(kBlue);
  gr0->SetTitle("");
  gr0->GetXaxis()->SetTitle("NPE p_{T} (GeV/c)");
  gr0->GetYaxis()->SetTitle("B#rightarrowNPE / Inclusive#rightarrowNPE");
  gr0->GetYaxis()->SetRangeUser(-0.1, 1.2);

  TLegend* leg2 = new TLegend(0.15,0.7,0.62,0.88);
  //  leg2->SetTextSize(.05);
  leg2->SetFillStyle (0);
  leg2->SetFillColor (0);
  leg2->SetBorderSize(0);
  leg2->AddEntry(grP,"STAR Run 6","pe");
  leg2->AddEntry(gr0,"STAR Run 6(w/ Matt's py6 template)","pe");
  grP->GetYaxis()->SetRangeUser(0, 1.);
  grP->Draw("ape"); // run6
  grPS->Draw("same pe2");
  gr0->Draw("same pe");
  leg2->Draw("same");
  fpp->SaveAs("Drawpy6_matt.pdf");
  
}
