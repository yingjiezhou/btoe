void b_fraction_final_yj()
{
//=========Macro generated from canvas: c5/c5
//=========  (Mon Sep 30 10:45:37 2019) by ROOT version 6.16/00
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
   Double_t xAxis3[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *hmb__3 = new TH1F("hmb__3","hmb",9, xAxis3);
   hmb__3->SetBinContent(5,0.248614);
   hmb__3->SetBinContent(6,0.39961);
   hmb__3->SetBinContent(7,0.468965);
   hmb__3->SetBinContent(8,0.610928);
   hmb__3->SetBinError(5,0.0122303);
   hmb__3->SetBinError(6,0.0189966);
   hmb__3->SetBinError(7,0.0504947);
   hmb__3->SetBinError(8,0.17475);
   hmb__3->SetMinimum(0);
   hmb__3->SetMaximum(1);
   hmb__3->SetEntries(4);
   hmb__3->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   hmb__3->SetLineColor(ci);
   hmb__3->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   hmb__3->SetMarkerColor(ci);
   hmb__3->SetMarkerStyle(24);
   hmb__3->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
   hmb__3->GetXaxis()->SetRange(2,9);
   hmb__3->GetXaxis()->SetNdivisions(505);
   hmb__3->GetXaxis()->SetLabelFont(132);
   hmb__3->GetXaxis()->SetLabelOffset(0.01);
   hmb__3->GetXaxis()->SetLabelSize(0.06);
   hmb__3->GetXaxis()->SetTitleSize(0.072);
   hmb__3->GetXaxis()->SetTitleOffset(0.95);
   hmb__3->GetXaxis()->SetTitleFont(132);
   hmb__3->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
   hmb__3->GetYaxis()->SetLabelFont(132);
   hmb__3->GetYaxis()->SetLabelOffset(0.01);
   hmb__3->GetYaxis()->SetLabelSize(0.06);
   hmb__3->GetYaxis()->SetTitleSize(0.072);
   hmb__3->GetYaxis()->SetTitleOffset(0.95);
   hmb__3->GetYaxis()->SetTitleFont(132);
   hmb__3->GetZaxis()->SetLabelFont(132);
   hmb__3->GetZaxis()->SetLabelSize(0.06);
   hmb__3->GetZaxis()->SetTitleSize(0.072);
   hmb__3->GetZaxis()->SetTitleOffset(1.2);
   hmb__3->GetZaxis()->SetTitleFont(132);
   hmb__3->Draw("E1");
   Double_t xAxis4[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *hht__4 = new TH1F("hht__4","hht",9, xAxis4);
   hht__4->SetBinContent(6,0.58563);
   hht__4->SetBinContent(7,0.598869);
   hht__4->SetBinContent(8,0.642587);
   hht__4->SetBinContent(9,0.790271);
   hht__4->SetBinError(6,0.164012);
   hht__4->SetBinError(7,0.101775);
   hht__4->SetBinError(8,0.105496);
   hht__4->SetBinError(9,0.166438);
   hht__4->SetEntries(4);
   hht__4->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   hht__4->SetLineColor(ci);
   hht__4->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   hht__4->SetMarkerColor(ci);
   hht__4->SetMarkerStyle(25);
   hht__4->GetXaxis()->SetNdivisions(505);
   hht__4->GetXaxis()->SetLabelFont(132);
   hht__4->GetXaxis()->SetLabelOffset(0.01);
   hht__4->GetXaxis()->SetLabelSize(0.06);
   hht__4->GetXaxis()->SetTitleSize(0.072);
   hht__4->GetXaxis()->SetTitleOffset(0.95);
   hht__4->GetXaxis()->SetTitleFont(132);
   hht__4->GetYaxis()->SetLabelFont(132);
   hht__4->GetYaxis()->SetLabelOffset(0.01);
   hht__4->GetYaxis()->SetLabelSize(0.06);
   hht__4->GetYaxis()->SetTitleSize(0.072);
   hht__4->GetYaxis()->SetTitleOffset(0.95);
   hht__4->GetYaxis()->SetTitleFont(132);
   hht__4->GetZaxis()->SetLabelFont(132);
   hht__4->GetZaxis()->SetLabelSize(0.06);
   hht__4->GetZaxis()->SetTitleSize(0.072);
   hht__4->GetZaxis()->SetTitleOffset(1.2);
   hht__4->GetZaxis()->SetTitleFont(132);
   hht__4->Draw("same E1");
   
   TLegend *leg = new TLegend(0.5,0.2,0.9,0.45,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("hmb","Min. Bias","PLE");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("hht","High Tower","PLE");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.164,0.733,0.55,0.9,"BRNDC");
   pt->SetBorderSize(0);

   ci = 1179;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   pt->SetFillColor(ci);
   pt->SetLineWidth(2);
   pt->SetTextAlign(12);
   pt->SetTextFont(132);
   TText *pt_LaTex = pt->AddText("STAR 20-40%");
   pt->Draw();
   c5->Modified();
   c5->cd();
   c5->SetSelected(c5);
}
