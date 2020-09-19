//#include <stdio>
//#include <iomanip>

void makeRAA_e()
{
  gROOT->Reset();

  TFile *f_dau = new TFile("RAA_All_Combine.root");
  TH1D *h_e = (TH1D *)f_dau->Get("Electron_Raa_B");
  h_e->Rebin(5); h_e->Scale(0.2);
  TH1D *h_De = (TH1D *)f_dau->Get("Electron_Raa_D");
  h_De->Rebin(5); h_De->Scale(0.2);

  const Int_t n_dau = 26;
  double x_dau[n_dau], y_e[n_dau], y_De[n_dau];
  for(int i=0;i<n_dau;i++) {
    if(i<20) {
      x_dau[i] = (i+0.5)*0.5;
    } else if(i<26) {
      x_dau[i] = (i-20+0.5)*1.0+10.;
    }
    int j = h_e->FindBin(x_dau[i]);
    y_e[i] = h_e->GetBinContent(j);
    y_De[i] = h_De->GetBinContent(j);
  }

  TGraph *gr_e = new TGraph(n_dau, x_dau, y_e);
  gr_e->SetName("RAA_e_B");
  TGraph *gr_De = new TGraph(24, x_dau, y_De);
  gr_De->SetName("RAA_e_D");
  
  TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0.01);
  c1->SetFillColor(10);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderMode(0);
  
  // c1->SetGridx();
  // c1->SetGridy();
  c1->SetTickx();
  c1->SetTicky();
  //  c1->SetLogx();
  c1->SetLogy();
  
  c1->SetLeftMargin(0.13);
  c1->SetBottomMargin(0.16);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);


  double x1 = 0.; //0.5;  //0.;
  double x2 = 15; //40;   //15;
  double y1 = 0.14;
  double y2 = 1.5;

  TH1D *d0 = new TH1D("d0","",1,x1,x2);
  d0->SetMinimum(y1);
  d0->SetMaximum(y2);
  d0->GetXaxis()->SetNdivisions(208);
  d0->GetXaxis()->CenterTitle();
  d0->GetXaxis()->SetTitle("Transverse Momentum p_{T} (GeV/c)");
  d0->GetXaxis()->SetTitleOffset(1.2);
  d0->GetXaxis()->SetTitleSize(0.06);
  d0->GetXaxis()->SetLabelOffset(0.01);
  d0->GetXaxis()->SetLabelSize(0.045);
  d0->GetXaxis()->SetLabelFont(42);
  d0->GetXaxis()->SetTitleFont(42);
  d0->GetYaxis()->SetNdivisions(505);
  d0->GetYaxis()->CenterTitle();
  d0->GetYaxis()->SetTitle("Nuclear Modification Factor R_{AA}^{0-10%}");
  d0->GetYaxis()->SetTitleOffset(1.0);
  d0->GetYaxis()->SetTitleSize(0.06);
  d0->GetYaxis()->SetLabelOffset(0.005);
  d0->GetYaxis()->SetLabelSize(0.045);
  d0->GetYaxis()->SetLabelFont(42);
  d0->GetYaxis()->SetTitleFont(42);
  d0->SetLineWidth(2);
  d0->Draw();

  TLatex *tex = new TLatex(-1.0,0.195,"0.2");
  tex->SetTextFont(42);
  tex->SetTextSize(0.045);
  tex->Draw("same");

  TLine *l1 = new TLine(x1,y1,x2,y1);
  l1->SetLineWidth(3);
  l1->Draw("same");
  TLine *l2 = new TLine(x1,y2,x2,y2);
  l2->SetLineWidth(3);
  l2->Draw("same");
  TLine *l3 = new TLine(x1,y1,x1,y2);
  l3->SetLineWidth(3);
  l3->Draw("same");
  TLine *l4 = new TLine(x2,y1,x2,y2);
  l4->SetLineWidth(3);
  l4->Draw("same");

  TLine *l0 = new TLine(x1,1,x2,1);
  l0->SetLineWidth(2);
  l0->SetLineStyle(2);
  l0->Draw("same");

  gr_e->SetLineStyle(3);
  gr_e->SetLineColor(1);
  gr_e->SetLineWidth(2);
  gr_e->Draw("c");

  gr_De->SetLineStyle(3);
  gr_De->SetLineColor(4);
  gr_De->SetLineWidth(2);
  gr_De->Draw("c");
  
  TLegend *leg = new TLegend(0.72, 0.59, 0.95, 0.94);
  leg->SetFillColor(10);
  //  leg->SetFillStyle(10);
  leg->SetLineStyle(4000);
  leg->SetLineColor(10);
  leg->SetLineWidth(0.);
  leg->SetTextFont(42);
  leg->SetTextSize(0.045);
  leg->AddEntry(gr_e,"B #rightarrow e","l");
  leg->AddEntry(gr_De,"D #rightarrow e","l");  
  leg->Draw();

  c1->Update();
  c1->SaveAs("RAA_Proj_e.eps");
  c1->SaveAs("RAA_Proj_e.png");

  TFile *file=new TFile("B_D_Raa.root","RECREATE");
  gr_e->Write();
  gr_De->Write();
  
}

