void Draw_Fig2()
{
  gSystem->Load("libGraphic.so");
  Graphic *Gp = new Graphic();
  Gp->SetPallet(); 
  gStyle->SetOptFit(1);
 
  TCanvas *c2 = new TCanvas();  
  c2->Divide(2,1);
  c2->cd(1);

  gPad->SetTopMargin(0.07419058);
  gPad->SetBottomMargin(0.1278963);

  TGraphErrors *Gfit = new TGraphErrors("fit_Run5.dat");
  Gp->SetGraphStyles(Gfit,20,1);
  Gfit->SetTitle(""); 
  Gfit->SetMinimum(0.1); 
  Gfit->SetMaximum(0.99); 
  Gfit->GetYaxis()->SetTitle("r_{B}"); 
  Gfit->GetXaxis()->SetTitle("Fit Range (#pm)"); 
  Gfit->GetXaxis()->SetTitleSize(0.06); 
  Gfit->GetYaxis()->SetTitleSize(0.06); 
  Gfit->GetXaxis()->SetLabelSize(0.06); 
  Gfit->GetYaxis()->SetLabelSize(0.06); 
  Gfit->GetXaxis()->SetTitleOffset(0.9); 
  Gfit->GetYaxis()->SetTitleOffset(0.7); 
  //Gwaku->Draw(); 
  Gfit->Draw("AP"); 

  TGraphErrors *Gfit2 = new TGraphErrors("fit_Run6.dat");
  Gp->SetGraphStyles(Gfit2,24,1);
  Gfit2->Draw("P");
 
  Gfit->SetName("FRun5");
  Gfit2->SetName("FRun6");

  TText *t1 = new TText(2.75,0.9,"(a)");
  t1->SetTextSize(0.06);
  t1->Draw();

 TLegend *leg = new TLegend(0.15,0.75,0.35,0.89);
 leg->SetBorderSize(0);
 leg->SetTextSize(0.05);
 leg->AddEntry(FRun5,"2.5 < p_{T}^{trig} < 3.5","P");
 leg->AddEntry(FRun6,"5.5 < p_{T}^{trig} < 6.5","P");
 leg->Draw(); 


  c2->cd(2);

  gPad->SetTopMargin(0.07419058);
  gPad->SetBottomMargin(0.1278963);


  TFile *file = new TFile("Chi2_25_35.root");
  Gp->SetGraphStyles(chi2_25_35,20,1);


  chi2_25_35->SetMaximum(89); 
  //chi2_25_35->Draw("AP"); 
  chi2_25_35->SetTitle(""); 
  chi2_25_35->GetXaxis()->SetTitle("r_{B}"); 
  chi2_25_35->GetYaxis()->SetTitle("X^{2}"); 
  chi2_25_35->GetXaxis()->SetTitleSize(0.06); 
  chi2_25_35->GetYaxis()->SetTitleSize(0.06); 
  chi2_25_35->GetXaxis()->SetLabelSize(0.06); 
  chi2_25_35->GetYaxis()->SetLabelSize(0.06); 
  chi2_25_35->GetXaxis()->SetTitleOffset(0.9); 
   ->GetYaxis()->SetTitleOffset(0.7); 
  chi2_25_35->Draw("AP");

  TFile *file = new TFile("Chi2_55_65.root");
  Gp->SetGraphStyles(chi2_55_65,24,1);
  chi2_55_65->Draw("P");

  TText *t2 = new TText(0.91,82,"(b)");
  t2->SetTextSize(0.06);
  t2->Draw();

 TLine *ndf = new TLine(0,29,1.1,29);
 ndf->Draw();

  TText *t3 = new TText(0.6,25,"ndf = 29");
  t3->SetTextSize(0.05);
  t3->Draw();


}
