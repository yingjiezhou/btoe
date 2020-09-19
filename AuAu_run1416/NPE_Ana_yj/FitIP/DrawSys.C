void data_sys(TH1F *er__1, TH1F *er__2);

void DrawSys(){

  gROOT->ProcessLine(".x ~/myStyle.C");
  Double_t xAxis1[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5};
  TH1F *sys_yj = new TH1F("er__1","er",9, xAxis1);
  TH1F *sys_Matt = new TH1F("er__2","er2",9, xAxis1);
  data_sys(sys_yj, sys_Matt);
  TCanvas *sys_comp = new TCanvas("sys_comp", "sys_comp");
  TLegend *leg22 = new TLegend(0.2,0.5,0.5,0.9);
  leg22->AddEntry(sys_yj,"Min. Bias Syst. YJ","PL");
  leg22->AddEntry(sys_Matt,"Min. Bias Syst. Matt","PL");

  sys_yj->GetYaxis()->SetRangeUser(0, 0.16);
  sys_yj->SetLineColor(kRed);
  sys_yj->SetLineStyle(9);
  sys_Matt->SetLineStyle(9);
  sys_yj->Draw();
  sys_Matt->Draw("same");
  leg22->Draw("same");

  sys_comp->SaveAs("sys_comp.pdf");

  return ;
}

void data_sys(TH1F *er__1, TH1F *er__2){
   er__1->SetBinContent(5,0.02604339);
   er__1->SetBinContent(6,0.02091913);
   er__1->SetBinContent(7,0.02194204);
   er__1->SetBinContent(8,0.04049865);
   er__1->SetBinContent(9,0.1290588);
   er__1->SetEntries(5);
   er__1->SetStats(0000);
   er__1->SetLineWidth(2);
   er__1->SetMarkerStyle(20);
   er__1->GetXaxis()->SetNdivisions(505);

   er__2->SetBinContent(5,0.02436258);
   er__2->SetBinContent(6,0.0207101);
   er__2->SetBinContent(7,0.02138056);
   er__2->SetBinContent(8,0.03534933);
   er__2->SetBinContent(9,0.1484424);
   er__2->SetEntries(5);
   er__2->SetStats(0000);
   er__2->SetLineWidth(2);
   er__2->SetMarkerStyle(20);
   er__2->GetXaxis()->SetNdivisions(505);
 
}
