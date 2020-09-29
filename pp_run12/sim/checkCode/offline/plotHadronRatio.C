void plotHadronRatio(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  
  auto f = new TFile("rootfile/readTreeHadron.root", "READ");
  auto hLc = (TH1D*) f->Get("hLc");
  auto hD0 = (TH1D*) f->Get("hD0");
  auto hLb = (TH1D*) f->Get("hLb");
  auto hB0 = (TH1D*) f->Get("hB0");
  auto h2Lb = (TH1D*) f->Get("h2Lb");
  auto h2B0 = (TH1D*) f->Get("h2B0");
  
  
  
  auto c = new TCanvas("c");
  c->cd();
  hLc->Divide(hD0);
  hLb->Divide(hB0);
  h2Lb->Divide(h2B0);
  
  auto leg = new TLegend(0.6,0.75,0.9,0.9);
  leg->AddEntry(hLc, "#Lambda_{c}^{+}/D^{0} |#eta|<1.");
  leg->AddEntry(hLb, "#Lambda_{b}^{0}/B^{0} |#eta|<1.");
  leg->AddEntry(h2Lb, "#Lambda_{b}^{0}/B^{0} 2<#eta<5");
  leg->SetFillStyle (0);
  leg->SetFillColor (0);
  leg->SetBorderSize(0);
  hLc->SetLineColor(1);
  hLb->SetLineColor(2);
  h2Lb->SetLineColor(kBlue);
  
  hLc->GetYaxis()->SetRangeUser(0, 3.2);
  hLc->GetXaxis()->SetTitle("hadron #it{p}_{T}(GeV/#it{c})");
  hLc->GetYaxis()->SetTitle("ratio");
  
  
  TLatex tx;
  tx.SetTextSize(0.05);
//  tx.SetTextFont(42);
  
  hLc->Draw("hist ");
  hLb->Draw("same hist ");
  h2Lb->Draw("same hist");
  leg->Draw("same");
  tx.DrawLatex(1.2,2.6,"pp 200GeV, PYTHIA8 w/ CR");
  c->SaveAs("pic/plotHadronRatio.pdf");
  return;
}
