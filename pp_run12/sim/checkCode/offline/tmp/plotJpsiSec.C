 #include "style.h"
void plotCompJpsiSec(){
  setstyle();
//  gROOT->ProcessLine(".x ~/myStyle.C");
  TFile* file = new TFile("JpsidNdydpTSpectrumpp.root","READ");
  auto GJpsi = (TGraphErrors*) file->Get("Jpsi");
  
  auto f = new TFile("QAJpsiPureSec_v2.root", "READ");
  auto hjeptN = (TH1D*)f->Get("hjeptN");

  hjeptN->Rebin(25);
  hjeptN->Scale(1./0.0594); //jpsi decay fraction
//  cout<<hjeptN->GetNbinsX()<<endl;
  
  hjeptN->Scale(1, "width");
  for(int i = 0; i< hjeptN->GetNbinsX(); i++){
    double pt = hjeptN->GetBinCenter(i+1);
    double tmpp = 1./(2* TMath::Pi() * pt);// * hjeptN->GetBinWidth(i)); ////!!!!! notice here divide by dpT

    tmpp = tmpp/6221.;
    hjeptN->SetBinContent(i+1, hjeptN->GetBinContent(i+1) * tmpp ); //
    hjeptN->SetBinError(i+1, 1e-9);
  }
  
  
  auto tmp = 2.628*1e-6/hjeptN->GetBinContent(hjeptN->FindBin(1));
  cout<<tmp<<"  scale tmp"<<endl;
  hjeptN->Scale(tmp);
  double xzebo[10] = {1.013, 1.924, 2.685, 3.181, 3.982, 4.631, 5.278, 6.194, 6.993, 7.830};
  double yzebo[10] = {2.628, 1.138, 0.473, 0.243, 0.072, 0.027, 0.013, 0.003, 0.001, 0.001};
  double ezebo[10] = {0};
  double xs[8] = {2.55, 3.14, 4.01, 6.06, 7.53, 8.94, 10.2, 11.9};
  double ys[8] = {5.13e-7, 2.07e-7, 6.35e-8, 4.15e-9, 7.39e-10, 1.58e-10, 4.83e-11, 1.24e-11};
  double es[8] = {0};

  
  for(auto i = 0; i<10; i++){
    yzebo[i] = yzebo[i]*1e-6;
    
  }

  
  TGraph* gr = new TGraph(10,xzebo, yzebo);
  auto gs = new TGraph(8, xs, ys);
  
//  cout<<gr->Eval(2.5)<<"   "<<gs->Eval(2.5)<<endl;
  
  TCanvas *cc=Canvas("cc",0.155,0.025,0.15,0.06,0,1,0);
  TH1F *htmp=histo("htmp",20,0,20,1e-15,1e-3,"p_{T} (GeV/c)","d^{2}#sigma/(2#pip_{T}dp_{T}dy) (mb GeV^{-2} c^{3})",0.075,0.85,0.065,1.15);
  htmp->SetNdivisions(505,"y");
  StyleTGraph(GJpsi,1,1,3,8,kCyan-2,0.9,"psame");
  Style(hjeptN,1,kYellow+1,3,8,kYellow+1,0.9,"psame");
//  StyleTGraphT(gs,1,1,3,8,kRed+2,0.9,"psame");
  StyleTGraphT(gr,1,1,3,8,kRed+2,0.9,"psame");

  auto leg = new TLegend(0.55,0.6,0.9,0.78);
  leg->AddEntry(gr,"J/#psi#rightarrow#it{e^{+}e^{-}}(from zebo*1e-6, K=0.4356)","p");
//  leg->AddEntry(gs,"J/#psi#rightarrow#it{e^{+}e^{-}}(from shenghui*Br)","p");
  leg->AddEntry(GJpsi,"J/#psi#rightarrow#it{e^{+}e^{-}}(from shenghui)","p");
  leg->AddEntry(hjeptN,Form("J/#psi#rightarrow#it{e^{+}e^{-}}(from Yingjie*%.2f)", tmp),"p");
  
  leg->SetFillStyle (0);
  leg->SetFillColor (0);
  leg->SetBorderSize(0);
  leg->Draw("same");
  
  TLatex tx;
  tx.SetTextSize(0.07);
  tx.SetTextFont(42);
  tx.DrawLatex(8.99,6e-5,"p+p @ #sqrt{s} = 200 GeV");
  tx.DrawLatex(13.3,6e-6,"J/#Psi");
  
  
 
  
//  auto c = new TCanvas("c", "c");
//  c->SetLogy();
//  gr->GetYaxis()->SetRangeUser(1e-15, 1e-3);
//  gr->GetXaxis()->SetRangeUser(2.5, 8);
//  gr->SetLineColor(2);
//  gr->GetXaxis()->SetTitle("p_{T}");
//  gr->GetYaxis()->SetTitle("1/(2#pip_{T})*d#sigma^{2}/dp_{T}dy(mb/GeV^{2})");
//  gr->GetXaxis()->SetNdivisions(515, "X");
//  gr->Draw("al");
//  gs->Draw("same l");
//  leg->Draw("same");
  cc->SaveAs("jpsiCompJpsiSec.pdf");
  return;
}
