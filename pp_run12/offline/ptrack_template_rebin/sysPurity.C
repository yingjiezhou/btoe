{
//  gROOT->ProcessLine(".x ~/myStyle.C");
//  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1111);
  double pa[3], pac[3];
  TFile* f = new TFile("Purity.root");
  TH1F* p = (TH1F*) f->Get("purity");
  TH1F* pC = (TH1F*) p->Clone();
  p->SetName("Shifted by Error(+)");
  pC->SetName("From data");

  
  pC->SetLineColor(kBlue);
  pC->SetMarkerColor(kBlue);
  
  // move points in purity to highest error bar point
  TCanvas * test = new TCanvas("test");
//  test->cd();

  TH1F* changeHist = p;
//  changeHist->DrawClone("AP");
  TAxis* ax = changeHist->GetXaxis();
  for(int chn = ax->GetFirst(); chn <= ax->GetLast(); chn++)
  {
    double current = changeHist->GetBinContent(chn);
    double error = changeHist->GetBinError(chn);
    changeHist->SetBinContent(chn, current+error);
  }
  changeHist->SetLineColor(kGreen);
  changeHist->SetMarkerColor(kGreen);
//  changeHist->DrawClone("same");
  
//  p->GetYaxis()->SetRangeUser(0, 1.3);
  p->Fit("pol2","Q");
  pC->Fit("pol2","Q", "sames");
  
  p->GetFunction("pol2")->SetLineColor(kGreen);
  pC->GetFunction("pol2")->SetLineColor(kBlue);

//  p->Draw();
//  pC->Draw("same");
  test->Update(); //to force the creation of "stats"
  TPaveStats *stat = (TPaveStats*)(p->FindObject("stats"));
  TPaveStats *stat1 = (TPaveStats*)(pC->FindObject("stats"));
  if(stat && stat1) {
//    cout<<"xxx"<<endl;
    stat->SetTextColor(kGreen);
    stat1->SetTextColor(kBlue);
    stat->SetY1NDC(0.3);
    stat->SetY2NDC(0.6);
    stat1->SetY1NDC(0.3);
    stat1->SetY2NDC(0.6);
    stat->SetX1NDC(0.3);
    stat->SetX2NDC(0.5);
    float height = stat1->GetX2NDC() - stat1->GetX1NDC();
    stat1->SetX1NDC(stat->GetX1NDC() - height);
    stat1->SetX2NDC(stat->GetX1NDC() );
    stat1->Draw();
  }

  TF1* fit = p->GetFunction("pol2"); // shifted
  pa[0] = fit->GetParameter(0);
  pa[1] = fit->GetParameter(1);
  pa[2] = fit->GetParameter(2);
  
  TF1* fitc = pC->GetFunction("pol2"); // shifted
  pac[0] = fitc->GetParameter(0);
  pac[1] = fitc->GetParameter(1);
  pac[2] = fitc->GetParameter(2);
  
  test->SaveAs("sysPurity.pdf");
  
  FILE* pFile;
  pFile = fopen("purParFits_shift.txt","w");
  fprintf(pFile,"%lf %lf %lf",pa[0],pa[1],pa[2]);
  fclose(pFile);
  
  FILE* pFileC;
  pFileC = fopen("purParFits.txt","w");
  fprintf(pFileC,"%lf %lf %lf",pac[0],pac[1],pac[2]);
  fclose(pFileC);
  
  
}
