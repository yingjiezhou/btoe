void fig1b_spectrum()
{
  gROOT->Reset();
//  gROOT->LoadMacro("~/work/work/fitfun/Levy.C");

void scaleGraph(TGraphErrors *gr,Double_t scale)
        {
                Int_t NPoint = gr->GetN();
                for(int i=0;i<NPoint;i++)
                {
                        Double_t x = gr->GetX()[i];
                        Double_t y = gr->GetY()[i];
                        Double_t ex = gr->GetEX()[i];
                        Double_t ey = gr->GetEY()[i];
                        y = scale*y;
                        gr->SetPoint(i,x,y);
                        gr->SetPointError(i, ex, ey*scale);
                }
        }
void scaleGraph(TGraphAsymmErrors *gr,Double_t scale)
        {
                Int_t NPoint = gr->GetN();
                for(int i=0;i<NPoint;i++)
                {
                        Double_t x = gr->GetX()[i];
                        Double_t y = gr->GetY()[i];
                        Double_t exl = gr->GetEXlow()[i];
                        Double_t eyl = gr->GetEYlow()[i];
                        Double_t exh = gr->GetEXhigh()[i];
                        Double_t eyh = gr->GetEYhigh()[i];
                        y = scale*y;
                        gr->SetPoint(i,x,y);
                        gr->SetPointError(i,exl,exh,eyl*scale,eyh*scale);
                }
        }


  const Double_t MassDs = 1.9685;
  const Int_t NC = 3;
  const Int_t NPt = 5;
  double pT[NC][NPt], y[NC][NPt], ye[NC][NPt], yes[NC][NPt], yet[NC][NPt];
TF1 *fun_tmp = new TF1("fun_tmp","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.96828*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.96828*1.96828)-1.96828)/([2]*[1]),-[2])", 1, 7);
TF1 *fun_tmp_timepT = new TF1("fun_tmp_timepT","(1/(2*TMath::Pi()))*[0]*([2]-1)*([2]-2)/([2]*[1]*([2]*[1]+1.96828*([2]-2)))*TMath::Power(([2]*[1]+TMath::Sqrt(x[0]*x[0]+1.96828*1.96828)-1.96828)/([2]*[1]),-[2])*x[0]", 1, 7);
  TF1 *fitfun[NC];
  TF1 *fitfun_timepT[NC];
//  TF1 *fun_tmp = new TF1("fun_tmp",Levy,1.0, 7.0, 4);
  fun_tmp->SetParameters(0.255, 0.545, 5);
//  fun_tmp->FixParameter(3, MassDs);
  
  //TFile *fin = new TFile("root/DsoverD0_AndSpectrum_new.root");
  TFile *fin = new TFile("root/Spectrum_run1416_Ds.root");
//  TFile *fout = new TFile("DsSpectrum_Fit.root","recreate");
  TGraphErrors *gr_stat_tmp[NC];
  TGraphErrors *gr_sys_tmp[NC];
TString mCent[3] = {"0_10", "10_40_binning", "40_80"};
  for(int i=0;i<NC;i++) {
    gr_stat_tmp[i] = (TGraphErrors *)fin->Get(Form("Ds_Yield_stat_%s_run1416", mCent[i].Data()));
    gr_sys_tmp[i] = (TGraphErrors *)fin->Get(Form("Ds_Yield_sys_%s_run1416", mCent[i].Data()));
    gr_stat_tmp[i]->Print();
if(i==0)
{
scaleGraph(gr_stat_tmp[i],2);
scaleGraph(gr_sys_tmp[i],2);
} 
 for(int j=0;j<NPt;j++) 
{
      pT[i][j] = gr_stat_tmp[i]->GetX()[j];
      y[i][j] = gr_stat_tmp[i]->GetY()[j];
      ye[i][j] = gr_stat_tmp[i]->GetEY()[j];
      yes[i][j] = gr_sys_tmp[i]->GetEY()[j];
      yet[i][j] = sqrt(ye[i][j]*ye[i][j]+yes[i][j]*yes[i][j]);
}

//cout << "pT[i][j] = " << pT[i][j] << endl;
//cout << "y[i][j] = " << y[i][j] << endl;
//cout << "ye[i][j] = " << ye[i][j] << endl;
//cout << "yes[i][j] = " << yes[i][j] << endl;
//cout << "yet[i][j] = " << yet[i][j] << endl;
  }
  TGraphErrors *gr_stat[NC];
  TGraphErrors *gr_total[NC];
  const Int_t kMarkerStyle[NC] = {20, 24, 20};
  for(int i=0;i<NC;i++) {
    gr_stat[i] = new TGraphErrors(NPt, pT[i], y[i], 0, ye[i]);
    gr_stat[i]->SetMarkerSize(2.0);
    gr_stat[i]->SetMarkerColor(1);
    gr_stat[i]->SetLineWidth(2);
    gr_stat[i]->SetMarkerStyle(kMarkerStyle[i]);
    
    gr_total[i] = new TGraphErrors(NPt, pT[i], y[i], 0, yet[i]);
/*if (i==0 || i == 2)
{
gr_stat[i]->RemovePoint(4);
gr_total[i]->RemovePoint(4);
}*/
    gr_total[i]->Fit("fun_tmp","R");
fun_tmp_timepT->SetParameters(fun_tmp->GetParameters());
    fitfun[i] = (TF1 *)fun_tmp->Clone();
    fitfun_timepT[i] = (TF1 *)fun_tmp_timepT->Clone();
    fitfun[i]->SetName(Form("Levy_%d",i));
    fitfun_timepT[i]->SetName(Form("Levy_timepT_%d",i));
  }

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
  c1->SetLogy();
  c1->SetGridx(0);
  c1->SetGridy(0);
  c1->SetLeftMargin(0.2);
  c1->SetBottomMargin(0.16);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);

  double x1 = 0.2;
  double x2 = 8.9;
  double y1 = 5e-8;
  double y2 = 1e-1;
  TH1 *h0 = new TH1D("h0","",1,x1, x2);
  h0->SetMinimum(y1);
  h0->SetMaximum(y2);
  h0->GetXaxis()->SetNdivisions(208);
  h0->GetXaxis()->CenterTitle();
  h0->GetXaxis()->SetTitle("Transverse Momentum p_{T} (GeV/c)");
  h0->GetXaxis()->SetTitleOffset(1.1);
  h0->GetXaxis()->SetTitleSize(0.06);
  h0->GetXaxis()->SetLabelOffset(0.01);
  h0->GetXaxis()->SetLabelSize(0.05);
  h0->GetXaxis()->SetLabelFont(42);
  h0->GetXaxis()->SetTitleFont(42);
  h0->GetYaxis()->SetNdivisions(303);
  h0->GetYaxis()->CenterTitle();
  h0->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (c^{2}/GeV^{2})");
  h0->GetYaxis()->SetTitleOffset(1.6);
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

  const Int_t kLineStyle[NC] = {1, 2, 1};
  for(int i=0;i<NC;i++) {
if (i==1) int NPt2 =5;
else int NPt2 =4;
    for(int j=0;j<NPt2;j++) {
      double x1 = pT[i][j] - 0.15;
      double x2 = pT[i][j] + 0.15;
      double y1 = y[i][j] - yes[i][j];
      double y2 = y[i][j] + yes[i][j];
            
      TLine *la = new TLine(x1, y1, x1, y1*1.15);
      la->Draw("same");
      TLine *lb = new TLine(x2, y1, x2, y1*1.15);
      lb->Draw("same");
      TLine *lc = new TLine(x1, y2, x1, y2*0.85);
      lc->Draw("same");
      TLine *ld = new TLine(x2, y2, x2, y2*0.85);
      ld->Draw("same");
      TLine *le = new TLine(x1, y1, x2, y1);
      le->SetLineWidth(2);
      le->Draw("same");
      TLine *lf = new TLine(x1, y2, x2, y2);
      lf->SetLineWidth(2);
      lf->Draw("same");
    }
    
    fitfun[i]->SetLineWidth(2);
    fitfun[i]->SetLineColor(1);
    fitfun[i]->SetLineStyle(kLineStyle[i]);
    fitfun[i]->Draw("same");
    gr_stat[i]->Draw("p");
  }

  double x1 = 0.2;
  double x2 = 8.9;
  double y1 = 5e-8;
  double y2 = 1e-1;
  
  TLatex *tex = new TLatex(3.2, y2*0.3, "STAR Au+Au #rightarrow D_{s}^{#pm}+X");
  tex->SetTextFont(42);
  tex->SetTextSize(0.06);
  tex->Draw("same");
  TLatex *tex = new TLatex(4.5, y2*0.09, "#sqrt{s_{NN}} = 200 GeV");
  tex->SetTextFont(42);
  tex->SetTextSize(0.06);
  tex->Draw("same");


  const Double_t x_txt[NC] = {7.1, 7.1, 7.1};
  const Double_t y_txt[NC] = {3e-6, 1e-6, 3.e-7};
  const Char_t *txt[NC] = {"0-10%#times2","10-40%","40-80%"};
  for(int i=0;i<NC;i++) {
    TLatex *tex = new TLatex(x_txt[i], y_txt[i], txt[i]);
    tex->SetTextFont(42);
    tex->SetTextSize(0.055);
    tex->Draw("same");
  }

  TLine *ll1 = new TLine(0.6, y1*8, 1.3, y1*8);
  ll1->SetLineWidth(2);
  ll1->SetLineStyle(1);
  ll1->Draw("same");
  TLine *ll2 = new TLine(0.6, y1*6, 1.3, y1*6);
  ll2->SetLineWidth(2);
  ll2->SetLineStyle(2);
  ll2->Draw("same");
  TLatex *tex = new TLatex(1.5, y1*5, "Levy fit");
  tex->SetTextFont(42);
  tex->SetTextSize(0.06);
  tex->Draw("same");

TLatex *tex = new TLatex(x2*0.9, y2*0.3, "(b)");
        tex->SetTextFont(42);
        tex->SetTextSize(0.07);
        tex->Draw("same");

//fout->cd();
//for(int i=0;i<NC;i++) {
//fitfun[i]->Write();
//fitfun_timepT[i]->Write();
//}
  

  c1->Update();

  c1->SaveAs("fig/fig1b_spectrum.pdf");
  c1->SaveAs("fig/fig1b_spectrum.png");
  
  
}
