void fig1a_invmass()
{
  gROOT->Reset();

  TFile *fin = new TFile("root/WSandRS_run1416.root");
  TH1D *hSig = (TH1D *)fin->Get("sig_largeh1");
  TH1D *hBkg = (TH1D *)fin->Get("bkg_largeh1");
  TF1 *fitfun = (TF1 *)hSig->GetFunction("fMass");
  double *par = fitfun->GetParameters();

  TF1 *fun_Ds = new TF1("fun_Ds","([0])/sqrt(2*TMath::Pi())/[2]*exp(-(x-[1])*(x-[1])/2./[2]/[2])",1.8,2.1);
  fun_Ds->SetParameters(&par[0]);
  TF1 *fun_Dp = new TF1("fun_Dp","([0])/sqrt(2*TMath::Pi())/[2]*exp(-(x-[1])*(x-[1])/2./[2]/[2])",1.8,2.1);
  fun_Dp->SetParameters(&par[5]);
  TF1 *fun_bg = new TF1("fun_bg","[0]+[1]*x",1.8,2.1);
  fun_bg->SetParameters(&par[3]);

  
  TCanvas *c1 = new TCanvas("c1", "c1",0,0,900,700);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  //  gStyle->SetEndErrorSize(0);
  c1->SetFillColor(10);
  c1->SetFillStyle(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(0);
  c1->SetFrameFillColor(10);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  //c1->SetLogy();
  c1->SetGridx(0);
  c1->SetGridy(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.16);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);

  double x1 = 1.801;
  double x2 = 2.099;
  double y1 = 0.0;
  double y2 = 999+400.;
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(208);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("Invariant Mass M_{#phi(K^{#pm}K^{#mp})#pi^{#pm}} (GeV/c^{2})");
  h0->GetXaxis()->SetTitleOffset(1.1);
  h0->GetXaxis()->SetTitleSize(0.06);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.05);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(42);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->CenterTitle();
  h0->GetYaxis()->SetTitle("Counts (per 8 MeV/c^{2})");
  h0->GetYaxis()->SetTitleOffset(1.2);
  h0->GetYaxis()->SetTitleSize(0.06);
  h0->GetYaxis()->SetLabelOffset(0.015);
  h0->GetYaxis()->SetLabelSize(0.05);
  h0->GetYaxis()->SetLabelFont(42);
  h0->GetYaxis()->SetTitleFont(42);
  h0->Draw("c");

  TLine *l1 = new TLine(x1,y1,x2,y1);
  l1->SetLineWidth(2);
  l1->Draw("same");
  TLine *l2 = new TLine(x1,y2,x2,y2);
  l2->SetLineWidth(2);
  l2->Draw("same");
  TLine *l3 = new TLine(x1,y1,x1,y2);
  l3->SetLineWidth(2);
  l3->Draw("same");
  TLine *l4 = new TLine(x2,y1,x2,y2);
  l4->SetLineWidth(2);
  l4->Draw("same");

  // TLine *l0 = new TLine(x1, 0, x2, 0);
  // l0->SetLineWidth(1);
  // l0->SetLineStyle(2);
  // l0->Draw("same");

  fitfun->SetLineWidth(2);
  fitfun->SetLineColor(1);
  fitfun->Draw("same");

  fun_bg->SetLineWidth(2);
  fun_bg->SetLineStyle(2);
  fun_bg->SetLineColor(1);
  fun_bg->Draw("same");

  hBkg->SetFillColor(8);
  hBkg->SetFillStyle(3004);
  //  hBkg->Draw("hsame");

  hSig->SetMarkerSize(1.5);
  hSig->SetMarkerColor(4);
  hSig->SetLineWidth(2);
  hSig->SetLineColor(4);
  hSig->Draw("same");

  TLatex *tex = new TLatex(1.82, y2*0.9, "Au+Au #sqrt{s_{NN}} = 200 GeV");
  tex->SetTextFont(42);
  tex->SetTextSize(0.065);
  tex->Draw("same");
  
  TLatex *tex = new TLatex(1.82, y2*0.82, "1.5 < p_{T} < 8 GeV/c");
  tex->SetTextFont(42);
  tex->SetTextSize(0.065);
  tex->Draw("same");

  TLatex *tex = new TLatex(1.82, y2*0.74, "0-80%");
  tex->SetTextFont(42);
  tex->SetTextSize(0.065);
  tex->Draw("same");
  
  TLatex *tex = new TLatex(1.98, 1050, "D_{s}^{#pm}");
  tex->SetTextFont(32);
  tex->SetTextSize(0.055);
  tex->Draw("same");

  TLatex *tex = new TLatex(1.88, 600, "D^{#pm}");
  tex->SetTextFont(32);
  tex->SetTextSize(0.055);
  tex->Draw("same");

TLatex *tex = new TLatex(x2*0.985, y2*0.9, "(a)");
        tex->SetTextFont(42);
        tex->SetTextSize(0.07);
        tex->Draw("same");


  c1->Update();

  c1->SaveAs("fig/fig1a_invmass.pdf");
  c1->SaveAs("fig/fig1a_invmass.png");
}
