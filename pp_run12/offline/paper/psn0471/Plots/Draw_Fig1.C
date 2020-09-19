Draw_Fig1()
{

  gSystem->Load("libGraphic.so");
  Graphic *Gp = new Graphic();
  Gp->SetPallet(); 
  gStyle->SetOptFit(1);


  TFile *file3 = new TFile("Chi2_25_35.root");
  TGraph *Gchi2_0 = chi2_25_35->Clone();
  TH1D *Hdphi_0 = fit_25_35->Clone();
  TH1D *Hdphi_De_0 = De_25_35->Clone();
  TH1D *Hdphi_Be_0 = Be_25_35->Clone();

  TFile *file4 = new TFile("Chi2_55_65.root");
  TGraph *Gchi2_1 = chi2_55_65->Clone();
  TH1D *Hdphi_1 = fit_55_65->Clone();
  TH1D *Hdphi_De_1 = De_55_65->Clone();
  TH1D *Hdphi_Be_1 = Be_55_65->Clone();

 TCanvas *c1 = new TCanvas("c1","c1",900,600);

 TPad *c1_1 = new TPad("c1_1", "c1_1",0.01,0.5,0.99,0.99);
 c1_1-> SetBottomMargin(0);
 TPad *c1_2 = new TPad("c1_2", "c1_2",0.01,0.01,0.99,0.509);
 c1_2-> SetTopMargin(0);
 c1_1->Draw();
 c1_2->Draw();

 c1_1->cd();

  //TCanvas *c1 = new TCanvas();
  //c1->Divide(1,2);
  //c1->cd(1);
  //Hdphi_0->SetMinimum(0.05);
  //Hdphi_0->SetMaximum(0.25);
  gPad-> SetBottomMargin(0.0);
  Hdphi_0->GetYaxis()->SetLabelSize(0.06);
  Hdphi_0->GetYaxis()->SetTitleSize(0.07);
  Hdphi_0->GetYaxis()->SetTitleOffset(0.6);
  Hdphi_0->GetXaxis()->SetLabelSize(0.06);
  Hdphi_0->GetXaxis()->SetTitleOffset(0.9);
  Hdphi_0->GetXaxis()->SetTitleSize(0.07);
  Hdphi_0->SetMaximum(0.3699);
  Hdphi_0->Draw();
  Hdphi_De_0->Draw("same");
  Hdphi_Be_0->Draw("same");

  Hdphi_De_0->SetName("pb");
  Hdphi_Be_0->SetName("pd");

   TLegend *leg = new TLegend(0.6,0.6,0.89,0.89);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.09);
   leg->AddEntry(pb,"#Delta #phi_{e_{B}-h}","L");
   leg->AddEntry(pd,"#Delta #phi_{e_{D}-h}","L");
   //leg->AddEntry(pf,"R_{B}#Delta #phi_{e_{B}-h}+(1-R_{B})#Delta #phi_{e_{D}-h}","L");
   leg->Draw(); 

   TLegend *leg1 = new TLegend(0.13,0.08,0.2,0.13);
   leg1->SetBorderSize(0);
   leg1->SetFillColor(0);
   leg1->SetTextSize(0.08);
   leg1->AddEntry(exp,"2.5<p_{T}^{trig}(GeV/c)<3.5","");
   leg1->Draw();


 c1_2->cd();
  //c1->cd(2);
  gPad-> SetBottomMargin(0.15);
  Hdphi_1->GetYaxis()->SetLabelSize(0.06);
  Hdphi_1->GetYaxis()->SetTitleSize(0.07);
  Hdphi_1->GetYaxis()->SetTitleOffset(0.6);
  Hdphi_1->GetXaxis()->SetLabelSize(0.06);
  Hdphi_1->GetXaxis()->SetTitleOffset(0.9);
  Hdphi_1->GetXaxis()->SetTitleSize(0.07);
  Hdphi_1->SetMaximum(0.3699);
  Hdphi_1->Draw();
  Hdphi_De_1->Draw("same");
  Hdphi_Be_1->Draw("same");


   TLegend *leg2 = new TLegend(0.13,0.2,0.2,0.25);
   leg2->SetBorderSize(0);
   leg2->SetFillColor(0);
   leg2->SetTextSize(0.08);
   leg2->AddEntry(exp,"5.5<p_{T}^{trig}(GeV/c)<6.5","");
   leg2->Draw();


  /*
  c1->cd(3);

  Gp->SetGraphStyles(Gchi2_0,20,1);
  Gchi2_0->SetMaximum(89); 
  Gchi2_0->SetTitle(""); 
  Gchi2_0->GetXaxis()->SetTitle("R_{B}"); 
  Gchi2_0->GetYaxis()->SetTitle("X^{2}"); 
  Gchi2_0->GetXaxis()->SetTitleSize(0.06); 
  Gchi2_0->GetYaxis()->SetTitleSize(0.06); 
  Gchi2_0->GetXaxis()->SetLabelSize(0.06); 
  Gchi2_0->GetYaxis()->SetLabelSize(0.06); 
  Gchi2_0->GetXaxis()->SetTitleOffset(0.9); 
  Gchi2_0->GetYaxis()->SetTitleOffset(0.7); 
  Gchi2_0->Draw("AP"); 
  Gp->SetGraphStyles(Gchi2_1,24,1);
  Gchi2_1->Draw("P");
  */




}
