void b_fraction_final_matt()
{
//=========Macro generated from canvas: c5/c5
//=========  (Mon Sep 30 10:44:03 2019) by ROOT version 6.16/00
   TCanvas *c5 = new TCanvas("c5", "c5",10,70,700,475);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c5->Range(-0.2962963,-0.2025316,8.962963,1.063291);
   c5->SetFillColor(0);
   c5->SetBorderMode(0);
   c5->SetBorderSize(2);
   c5->SetTickx(1);
   c5->SetTicky(1);
   c5->SetLeftMargin(0.14);
   c5->SetRightMargin(0.05);
   c5->SetTopMargin(0.05);
   c5->SetBottomMargin(0.16);
   c5->SetFrameLineWidth(2);
   c5->SetFrameBorderMode(0);
   c5->SetFrameLineWidth(2);
   c5->SetFrameBorderMode(0);
   Double_t xAxis3_yj[10] = {0.6+0.2, 1+0.2, 1.2+0.2, 1.5+0.2, 2+0.2, 2.5+0.2, 3.5+0.2, 4.5+0.2, 5.5+0.2, 8.5+0.2};
   
   TH1F *hmb__3_yj = new TH1F("hmb__3_yj","hmb",9, xAxis3_yj);
   hmb__3_yj->SetBinContent(5,0.250667);
   hmb__3_yj->SetBinContent(6,0.400152);
   hmb__3_yj->SetBinContent(7,0.466991);
   hmb__3_yj->SetBinContent(8,0.600006);
   hmb__3_yj->SetBinError(5,0.0122648);
   hmb__3_yj->SetBinError(6,0.018922);
   hmb__3_yj->SetBinError(7,0.0499963);
   hmb__3_yj->SetBinError(8,0.170107);
   hmb__3_yj->SetMinimum(0);
   hmb__3_yj->SetMaximum(1);
   hmb__3_yj->SetEntries(4);
   hmb__3_yj->SetStats(0);

   Int_t ci_yj;      // for color index setting
   ci_yj = TColor::GetColor("#0000ff");
   hmb__3_yj->SetLineColor(ci_yj);
   hmb__3_yj->SetLineWidth(2);

   ci_yj = TColor::GetColor("#0000ff");
   hmb__3_yj->SetMarkerColor(ci_yj);
   hmb__3_yj->SetMarkerStyle(24);
   hmb__3_yj->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
   hmb__3_yj->GetXaxis()->SetRange(2,9);
   hmb__3_yj->GetXaxis()->SetNdivisions(505);
   hmb__3_yj->GetXaxis()->SetLabelFont(132);
   hmb__3_yj->GetXaxis()->SetLabelOffset(0.01);
   hmb__3_yj->GetXaxis()->SetLabelSize(0.06);
   hmb__3_yj->GetXaxis()->SetTitleSize(0.072);
   hmb__3_yj->GetXaxis()->SetTitleOffset(0.95);
   hmb__3_yj->GetXaxis()->SetTitleFont(132);
   hmb__3_yj->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
   hmb__3_yj->GetYaxis()->SetLabelFont(132);
   hmb__3_yj->GetYaxis()->SetLabelOffset(0.01);
   hmb__3_yj->GetYaxis()->SetLabelSize(0.06);
   hmb__3_yj->GetYaxis()->SetTitleSize(0.072);
   hmb__3_yj->GetYaxis()->SetTitleOffset(0.95);
   hmb__3_yj->GetYaxis()->SetTitleFont(132);
   hmb__3_yj->GetZaxis()->SetLabelFont(132);
   hmb__3_yj->GetZaxis()->SetLabelSize(0.06);
   hmb__3_yj->GetZaxis()->SetTitleSize(0.072);
   hmb__3_yj->GetZaxis()->SetTitleOffset(1.2);
   hmb__3_yj->GetZaxis()->SetTitleFont(132);
   hmb__3_yj->Draw("E1");
   Double_t xAxis4_yj[10] = {0.6+0.2, 1+0.2, 1.2+0.2, 1.5+0.2, 2+0.2, 2.5+0.2, 3.5+0.2, 4.5+0.2, 5.5+0.2, 8.5+0.2}; 
   
   TH1F *hht__4_yj = new TH1F("hht__4_yj","hht",9, xAxis4_yj);
   hht__4_yj->SetBinContent(6,0.58563);
   hht__4_yj->SetBinContent(7,0.598869);
   hht__4_yj->SetBinContent(8,0.642587);
   hht__4_yj->SetBinContent(9,0.790271);
   hht__4_yj->SetBinError(6,0.164012);
   hht__4_yj->SetBinError(7,0.101775);
   hht__4_yj->SetBinError(8,0.105496);
   hht__4_yj->SetBinError(9,0.166438);
   hht__4_yj->SetEntries(4);
   hht__4_yj->SetStats(0);

   ci_yj = TColor::GetColor("#ff0000");
   hht__4_yj->SetLineColor(ci_yj);
   hht__4_yj->SetLineWidth(2);

   ci_yj = TColor::GetColor("#ff0000");
   hht__4_yj->SetMarkerColor(ci_yj);
   hht__4_yj->SetMarkerStyle(25);
   hht__4_yj->GetXaxis()->SetNdivisions(505);
   hht__4_yj->GetXaxis()->SetLabelFont(132);
   hht__4_yj->GetXaxis()->SetLabelOffset(0.01);
   hht__4_yj->GetXaxis()->SetLabelSize(0.06);
   hht__4_yj->GetXaxis()->SetTitleSize(0.072);
   hht__4_yj->GetXaxis()->SetTitleOffset(0.95);
   hht__4_yj->GetXaxis()->SetTitleFont(132);
   hht__4_yj->GetYaxis()->SetLabelFont(132);
   hht__4_yj->GetYaxis()->SetLabelOffset(0.01);
   hht__4_yj->GetYaxis()->SetLabelSize(0.06);
   hht__4_yj->GetYaxis()->SetTitleSize(0.072);
   hht__4_yj->GetYaxis()->SetTitleOffset(0.95);
   hht__4_yj->GetYaxis()->SetTitleFont(132);
   hht__4_yj->GetZaxis()->SetLabelFont(132);
   hht__4_yj->GetZaxis()->SetLabelSize(0.06);
   hht__4_yj->GetZaxis()->SetTitleSize(0.072);
   hht__4_yj->GetZaxis()->SetTitleOffset(1.2);
   hht__4_yj->GetZaxis()->SetTitleFont(132);
   hht__4_yj->Draw("same E1");
   
   TLegend *leg = new TLegend(0.5,0.2,0.9,0.45,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("hmb","Min. Bias","PLE");

   ci_yj = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci_yj);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci_yj = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci_yj);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("hht","High Tower","PLE");

   ci_yj = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci_yj);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci_yj = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci_yj);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.164,0.733,0.55,0.9,"BRNDC");
   pt->SetBorderSize(0);

   ci_yj = 1179;
   color = new TColor(ci_yj, 1, 1, 1, " ", 0);
   pt->SetFillColor(ci_yj);
   pt->SetLineWidth(2);
   pt->SetTextAlign(12);
   pt->SetTextFont(132);
   TText *pt_LaTex = pt->AddText("STAR 20-40%");
   pt->Draw();
   c5->Modified();
   c5->cd();
   c5->SetSelected(c5);
}
