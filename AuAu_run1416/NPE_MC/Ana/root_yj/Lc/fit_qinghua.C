{
  gROOT->ProcessLine(".x ~/myStyle.C");
  //for centrality//
  double xx_cata[3] = {30.1,119.6,279.8}; //Npart
  double yy_cata[3] = {0.60593021,0.72847165,0.930602}; //Lc/D0 ratio
  TGraph *rat = new TGraph(3, xx_cata, yy_cata);
  TF1 *f = new TF1("fr", "[0]+[1]*x", 0, 400);
  f->SetParameter(0,0.55);
  rat->Fit(f);
  rat->Draw();
  return ;
  double ratio = f->Eval(348.74);
  double mbratio = f->Eval(97.56);
  cout<<ratio<<"   "<< mbratio<<"   "<< ratio/mbratio<<endl;
  //TFile* fIn1 = new TFile("Catania1080.root", "READ");
  //TGraph *mbr = (TGraph *)fIn1->Get("g_rat_h2");
  double lc_x[14]={0.11344,0.49159,0.99579,1.5,2.0042,2.5084, 3,3.5042,3.9958,4.5,5.0042,5.5084,6,6.30252};
  double lc_y[14]={1.06143,1.10996,1.25051,1.44071,1.59913,1.62314,1.4843,1.21379,0.942128,0.725841,0.580436,0.511373,0.481779,0.464159};
  TGraph *gr_lc = new TGraph(14,lc_x,lc_y);

  TGraph *mbr = new TGraph(14,lc_x,lc_y);
  
  //gr_lc->Draw();
  //mbr->Draw("same");
  
  //cout<<mbr->Eval(0.11344)<<endl;
  //for (int i=0;i<mbr->GetN();i++){
  //
  //}
  //TGraph *mbr = (TGraph *)fIn1->Get("g_rat_h2");
  
  TCanvas *clc = new TCanvas("clc","clc");
  //TGraph *copym = mbr;
  //copym->SetLineColor(kGreen+2);
  //copym->DrawClone();
  ////mbr->Draw("same");
  
  cout<<ratio/mbratio<<endl;
  for(int i=0;i<mbr->GetN();i++){
    mbr->GetY()[i] *=ratio/mbratio;
    
  }
  
  TFile* fIn1_c5 = new TFile("C5_Catania1080.root", "RECREATE");
  mbr->Write("LctoD0");
  fIn1_c5->Close();
  mbr->SetLineColor(kRed);
  gr_lc->SetLineColor(kBlue);
  gr_lc->GetYaxis()->SetTitle("#Lambda_{c}/D^{0}");
  gr_lc->GetXaxis()->SetTitle("p_{T} [GeV]");
  gr_lc->GetYaxis()->SetTitleOffset(0.85);
  gr_lc->GetYaxis()->SetRangeUser(0.4, 3);
  gr_lc->Draw();
  mbr->Draw("same");
  TLegend *leg = new TLegend(0.6,0.65,0.94,0.94);
  leg->AddEntry(gr_lc, "MB (Tshingua model)", "L");
  leg->AddEntry(mbr, "0-5%", "L");
  //leg->AddEntry(mbr, "Catania1080 ratio", "L");
  leg->Draw("same");
  clc->SaveAs("qinghua_ratio_comp.pdf");
  
}







