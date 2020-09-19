void drawtext();
void makePlot_norepeate(const char* FileName="noRepeate"){
  
  gROOT->ProcessLine(".x ~/myStyle.C");
//  gROOT->SetBatch(kTRUE);
  //auto fyj = new TFile("../../offYJ/fit/tmpfit/Fit_B_fraction.root", "READ");
  //auto fyj = new TFile("../../offYJ/fit/tmpfit_sumw/Fit_B_fraction.root", "READ");
//  gStyle->SetOptFit(1111);

  char name[100];
  auto fyjd = new TFile(Form("FFOutput/sysChange_default_May5_FIT.root", FileName),"READ"); // gpt
  auto hdf = (TGraphAsymmErrors *)fyjd->Get("HT0");
  auto hnorm = (TGraphAsymmErrors *)fyjd->Get("normsmall");
  
  auto fyj = new TFile(Form("FFOutput/sysChange_default_May5_FIT_WrongPHELoop.root", FileName), "READ");
  auto hbyj = (TGraphAsymmErrors *)fyj->Get("HT0");
  auto hdef = (TGraphErrors*)fyj->Get("normsmall");

  
  TCanvas* c1 = new TCanvas("c1","test");
  c1->cd();
  
  hbyj->GetXaxis()->SetRangeUser(0,12);
  hbyj->GetYaxis()->SetRangeUser(-0.1,1.2);
//  hbyj->SetLineWidth(2);
  hbyj->SetMarkerSize(1.5);
  hbyj->SetMarkerStyle(20);
  hbyj->SetMarkerColor(kBlue);
  hbyj->SetLineColor(kBlue);
  
  hdf->GetXaxis()->SetRangeUser(0,12);
  hdf->GetYaxis()->SetRangeUser(-0.1,1.2);
  //  hbyj->SetLineWidth(2);
  hdf->SetMarkerSize(1.5);
  hdf->SetMarkerStyle(20);
  hdf->SetMarkerColor(kBlack);
  hdf->SetLineColor(kBlack);
  

  hbyj->Draw("ape");
  hdf->Draw("same pe");
  
 
  auto leg = new TLegend(0.6, 0.6, 0.85, 0.85);
  leg->SetBorderSize(0);
  leg->AddEntry(hbyj,"default","pe");
  leg->AddEntry(hdf,"Modified","pe");
  leg->Draw("same");
  

  TCanvas* temp = new TCanvas("temp","");
  sprintf(name, "bFraction_%s.pdf[", FileName);
  temp->Print(name);
//  temp = cnorm;
//  temp->Print(name);
  temp = c1;
  temp->Print(name);
//  temp = csys;
//  temp->Print(name);
  sprintf(name, "bFraction_%s.pdf]", FileName);
  temp->Print(name);
  //============================================================================================
  
  
  

  //  TFile* fOut = new TFile("run12NPEh_rBPoints.root","RECREATE");
  //  stat->Write("StatError");
  //  syst->Write("systError");
  //  stat6->Write("StatError_Run6");
  //  syst6->Write("systError_Run6");
  //  FONLL[0]->Write("FONLL_UPPER");
  //  FONLL[1]->Write("FONLL_LOWER");
  //  fOut->Close();
}

void drawtext()
{
  Int_t i,n;
  Double_t x,y;
  TLatex l;

  l.SetTextSize(0.025);
  l.SetTextFont(42);
  l.SetTextAlign(21);
  l.SetTextColor(kBlue);

  TGraphAsymmErrors *g = (TGraphAsymmErrors*)gPad->GetListOfPrimitives()->FindObject("grA");
  n = g->GetN();

  for (i=0; i<n; i++) {
    g->GetPoint(i,x,y);
    auto yh = (Float_t)g->GetErrorYhigh(i);
    auto yl = (Float_t)g->GetErrorYlow(i);

//    l.PaintText(x,y+0.2,Form("(%4.3f+%4.3f-%4.3f)",y,yh,yl));
    l.PaintText(x,y+0.2,Form("%4.3f",y));

  }
}
