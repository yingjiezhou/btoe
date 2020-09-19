float pi = 3.1415826;

TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t textAngle=0);
Float_t correct_dPhi(Float_t dP);
void DrawEmbInc(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  auto f  = new TFile("rootfile/embedding_woTag_Remove.root", "READ");
  
  char *ptbin = "1";
  char *filename = "embedding_woTag_Remove";
  bool isZoom = true;
  
  float lowpt = 2.5;
  float highpt = 3.5;
  
  auto mh3DelPhiIncTrig0 = (TH3F*)f->Get("mh3DelPhiIncTrig0");
  auto mh3DelPhiIncTrig2 = (TH3F*)f->Get("mh3DelPhiIncTrig2");
  
  auto r1d =mh3DelPhiIncTrig0->GetZaxis()->FindBin(lowpt);
  auto r1u =mh3DelPhiIncTrig0->GetZaxis()->FindBin(highpt);
  
  mh3DelPhiIncTrig2->GetZaxis()->SetRange(r1d, r1u-1);
  mh3DelPhiIncTrig0->GetZaxis()->SetRange(r1d, r1u-1);
  
  auto usgptr = (TH2D*)mh3DelPhiIncTrig0->Project3D("yx_gpt0305_us");
  
  if(isZoom){
    r1d =usgptr->GetXaxis()->FindBin(-0.1);
    r1u =usgptr->GetXaxis()->FindBin(0.1);
    usgptr->GetXaxis()->SetRange(r1d, r1u);
    r1d =usgptr->GetYaxis()->FindBin(-0.1);
    r1u =usgptr->GetYaxis()->FindBin(0.1);
    usgptr->GetYaxis()->SetRange(r1d, r1u);
  }
  
  auto usgptr_phi = (TH1D*)usgptr->ProjectionX("yx_gpt0305_us_phi"); //us
  auto usgptr_eta = (TH1D*)usgptr->ProjectionY("yx_gpt0305_us_eta");
  
  //=========================================================
  
  usgptr->GetYaxis()->SetTitle("#Delta#eta");
  usgptr->GetXaxis()->SetTitle("#Delta#phi");

  //=========================================================
  
  auto c1 = new TCanvas();
//  c1->SetLogz();
  usgptr->Draw("colz");

  drawLatex(0.18, 0.88, "Inclusive e-e", 22, 0.06, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.", lowpt, highpt), 22, 0.06, 1);
  c1->SaveAs(Form("print/Print2D_%s_%s.pdf", ptbin, filename));
  //=========================================================
  
  usgptr_phi->GetXaxis()->SetTitle("#Delta#phi");

  auto c2 = new TCanvas(); // phi
  usgptr_phi->Draw();
  drawLatex(0.18, 0.88, "Inclusive e-e", 22, 0.06, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.", lowpt, highpt), 22, 0.06, 1);
  c2->SaveAs(Form("print/Print2D_phi_%s_%s.pdf", ptbin, filename));
  //=========================================================

  usgptr_eta->GetXaxis()->SetTitle("#Delta#eta");
  
  auto c22 = new TCanvas(); // phi
  usgptr_eta->Draw();
  drawLatex(0.18, 0.88, "Inclusive e-e", 22, 0.06, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.", lowpt, highpt), 22, 0.06, 1);
  c22->SaveAs(Form("print/Print2D_eta_%s_%s.pdf", ptbin, filename));
  
}
Float_t correct_dPhi(Float_t dP)
{
  
  if(dP > pi) dP = dP - 2*pi;
  if(dP < -pi) dP = dP + 2*pi;
  return dP;
  
}
TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t textAngle=0)
{
  TLatex *latex = new TLatex(x,y,text.Data());
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->SetTextAngle(textAngle);
  latex->Draw("same");
  return latex;
}

