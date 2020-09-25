
TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t textAngle=0);
void plot2D(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  auto f  = new TFile("rootfile/22default_gpt_dist_2d_hadron_zoom_qa.root", "READ");

  int trig = 0;
  auto lsr = (TH3F*)f->Get(Form("mh3DelPhiPhotLSNP_%i",trig)); // gpt larger, 0305
  auto usr = (TH3F*)f->Get(Form("mh3DelPhiPhotUSNP_%i",trig));
  auto lsl = (TH3F*)f->Get(Form("mh3DelPhiPhotLS_%i",trig)); // smaller, 0203
  auto usl = (TH3F*)f->Get(Form("mh3DelPhiPhotUS_%i",trig));

  char *ptbin = "0203_whadroncut_wotrig_trig0";
//  Double_t lowpt={2.5, 3.5, 4.5};
//  Double_t highpt={3.5, 4.5, 5.5};
  float lowpt = 2.5;
  float highpt = 3.5;
  auto r1d =lsr->GetZaxis()->FindBin(lowpt);
  auto r1u =lsr->GetZaxis()->FindBin(highpt);
  
  
  cout<<r1d<<" - "<<r1u<<endl;
  lsr->GetZaxis()->SetRange(r1d, r1u-1);
  usr->GetZaxis()->SetRange(r1d, r1u-1);
  lsl->GetZaxis()->SetRange(r1d, r1u-1);
  usl->GetZaxis()->SetRange(r1d, r1u-1);
  
  auto lsgptr = (TH2D*)lsr->Project3D("yx_gpt0305_ls"); // x=phi, y=eta
  auto usgptr = (TH2D*)usr->Project3D("yx_gpt0305_us");
  auto lsgptl = (TH2D*)lsl->Project3D("yx_gpt0203_ls");
  auto usgptl = (TH2D*)usl->Project3D("yx_gpt0203_us");
//  lsgptr->GetXaxis()->SetRangeUser(-0.08, 0.08);

  auto lsgptr_phi = (TH1D*)lsgptr->ProjectionX("yx_gpt0305_ls_phi");
  auto lsgptr_eta = (TH1D*)lsgptr->ProjectionY("yx_gpt0305_ls_eta");
  auto usgptr_phi = (TH1D*)usgptr->ProjectionX("yx_gpt0305_us_phi"); //us
  auto usgptr_eta = (TH1D*)usgptr->ProjectionY("yx_gpt0305_us_eta");
  
  auto lsgptl_phi = (TH1D*)lsgptl->ProjectionX("yx_gpt0203_ls_phi");
  auto lsgptl_eta = (TH1D*)lsgptl->ProjectionY("yx_gpt0203_ls_eta");
  auto usgptl_phi = (TH1D*)usgptl->ProjectionX("yx_gpt0203_us_phi");
  auto usgptl_eta = (TH1D*)usgptl->ProjectionY("yx_gpt0203_us_eta");
  
  //=========================================================
  
  lsgptl->GetYaxis()->SetTitle("#Delta#eta");
  lsgptl->GetXaxis()->SetTitle("#Delta#phi");
  usgptr->GetYaxis()->SetTitle("#Delta#eta");
  usgptr->GetXaxis()->SetTitle("#Delta#phi");
  usgptl->GetYaxis()->SetTitle("#Delta#eta");
  usgptl->GetXaxis()->SetTitle("#Delta#phi");
  lsgptr->GetYaxis()->SetTitle("#Delta#eta");
  lsgptr->GetXaxis()->SetTitle("#Delta#phi");
  
//  int bin = 0;
////  cout<<lsgptl->GetEntries()<<endl;
//  for(auto i = 0; i<100; i++){
//    for(auto j=0; j<80; j++){
//      if(lsgptl->GetBinContent(i, j)>0) {
////        cout<<lsgptl->GetBinContent(i, j)<<endl;
//        bin++;
//      }
//    }
//  }
//  cout<<bin<<endl;
//  return;

  auto c1 = new TCanvas();
//  c1->Divide(2, 2, 0, 0, 0);
  c1->Divide(2, 2);
  c1->cd(1);
  lsgptl->Draw("colz");
  drawLatex(0.18, 0.88, "LikeSign e-h", 22, 0.06, 1);
  drawLatex(0.18, 0.78, "0.2<gpt<0.3", 22, 0.06, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.3", lowpt, highpt), 22, 0.06, 1);

  c1->cd(2);
  usgptl->Draw("colz");
  drawLatex(0.18, 0.88, "UnLikeSign e-h", 22, 0.06, 1);
  drawLatex(0.18, 0.78, "0.2<gpt<0.3", 22, 0.06, 1);

  c1->cd(3);
  lsgptr->Draw("colz");
  drawLatex(0.18, 0.78, "0.3<gpt<0.5", 22, 0.06, 1);

  c1->cd(4);
  usgptr->Draw("colz");
  drawLatex(0.18, 0.78, "0.3<gpt<0.5", 22, 0.06, 1);
  c1->SaveAs(Form("plot2D_%s.pdf", ptbin));
  
  usgptr_phi->GetXaxis()->SetTitle("#Delta#phi");
  auto c2 = new TCanvas(); // phi
  //c2->Divide(2,2, 0, 0, 0);
  c2->Divide(2,2, 0.01, 0.01);
  c2->cd(1);
  lsgptl_phi->Draw();
  drawLatex(0.18, 0.88, "LikeSign e-h", 22, 0.06, 1);
  drawLatex(0.18, 0.78, "0.2<gpt<0.3", 22, 0.06, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.3", lowpt, highpt), 22, 0.06, 1);

  c2->cd(2);
  usgptl_phi->Draw();
  drawLatex(0.18, 0.88, "UnLikeSign e-h", 22, 0.06, 1);
  drawLatex(0.18, 0.78, "0.2<gpt<0.3", 22, 0.06, 1);
  
  c2->cd(3);
  lsgptr_phi->Draw();
  drawLatex(0.18, 0.78, "0.3<gpt<0.5", 22, 0.06, 1);
  
  c2->cd(4);
  
  usgptr_phi->Draw();
  drawLatex(0.18, 0.78, "0.3<gpt<0.5", 22, 0.06, 1);
  c2->SaveAs(Form("plot2D_phi_%s.pdf", ptbin));
  
  usgptr_eta->GetXaxis()->SetTitle("#Delta#eta");
  auto c22 = new TCanvas(); // phi
  //c22->Divide(2,2, 0, 0, 0);
  c22->Divide(2,2);
  c22->cd(1);
  lsgptl_eta->Draw();
  drawLatex(0.18, 0.88, "LikeSign e-h", 22, 0.06, 1);
  drawLatex(0.18, 0.78, "0.2<gpt<0.3", 22, 0.06, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.3", lowpt, highpt), 22, 0.06, 1);

  c22->cd(2);
  usgptl_eta->Draw();
  drawLatex(0.18, 0.88, "UnLikeSign e-h", 22, 0.06, 1);
  drawLatex(0.18, 0.78, "0.2<gpt<0.3", 22, 0.06, 1);
  
  c22->cd(3);
  lsgptr_eta->Draw();
  drawLatex(0.18, 0.78, "0.3<gpt<0.5", 22, 0.06, 1);
  c22->cd(4);
  usgptr_eta->Draw();
  drawLatex(0.18, 0.78, "0.3<gpt<0.5", 22, 0.06, 1);
  c22->SaveAs(Form("plot2D_eta_%s.pdf", ptbin));
  

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
