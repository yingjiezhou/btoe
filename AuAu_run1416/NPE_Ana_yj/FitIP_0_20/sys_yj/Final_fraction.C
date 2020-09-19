void Final_fraction()
{
//=========Macro generated from canvas: c1/Final
//=========  (Mon Sep 30 09:35:09 2019) by ROOT version 6.16/00
   TCanvas *c1 = new TCanvas("c1", "Final",10,70,700,475);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(-0.7654321,-0.2025316,8.987654,1.063291);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.14);
   c1->SetRightMargin(0.05);
   c1->SetTopMargin(0.05);
   c1->SetBottomMargin(0.16);
   c1->SetFrameLineWidth(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameLineWidth(2);
   c1->SetFrameBorderMode(0);
   Double_t xAxis1_yj[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h__1_yj = new TH1F("h__1_yj","h",9, xAxis1_yj);
   h__1_yj->SetBinContent(5,0.318942);
   h__1_yj->SetBinContent(6,0.469444);
   h__1_yj->SetBinContent(7,0.670662);
   h__1_yj->SetBinContent(8,0.737576);
   h__1_yj->SetBinError(5,0.00993923);
   h__1_yj->SetBinError(6,0.0149332);
   h__1_yj->SetBinError(7,0.0475619);
   h__1_yj->SetBinError(8,0.144196);
   h__1_yj->SetMinimum(0);
   h__1_yj->SetMaximum(1);
   h__1_yj->SetEntries(4);
   h__1_yj->SetStats(0);

   Int_t ci_yj;      // for color index setting
   TColor *color; // for color definition with alpha
   ci_yj = TColor::GetColor("#0000ff");
   h__1_yj->SetLineColor(ci_yj);
   h__1_yj->SetLineWidth(2);

   ci_yj = TColor::GetColor("#0000ff");
   h__1_yj->SetMarkerColor(ci_yj);
   h__1_yj->SetMarkerStyle(24);
   h__1_yj->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
   h__1_yj->GetXaxis()->SetNdivisions(505);
   h__1_yj->GetXaxis()->SetLabelFont(132);
   h__1_yj->GetXaxis()->SetLabelOffset(0.01);
   h__1_yj->GetXaxis()->SetLabelSize(0.06);
   h__1_yj->GetXaxis()->SetTitleSize(0.072);
   h__1_yj->GetXaxis()->SetTitleOffset(0.95);
   h__1_yj->GetXaxis()->SetTitleFont(132);
   h__1_yj->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
   h__1_yj->GetYaxis()->SetLabelFont(132);
   h__1_yj->GetYaxis()->SetLabelOffset(0.01);
   h__1_yj->GetYaxis()->SetLabelSize(0.06);
   h__1_yj->GetYaxis()->SetTitleSize(0.072);
   h__1_yj->GetYaxis()->SetTitleOffset(0.95);
   h__1_yj->GetYaxis()->SetTitleFont(132);
   h__1_yj->GetZaxis()->SetLabelFont(132);
   h__1_yj->GetZaxis()->SetLabelSize(0.06);
   h__1_yj->GetZaxis()->SetTitleSize(0.072);
   h__1_yj->GetZaxis()->SetTitleOffset(1.2);
   h__1_yj->GetZaxis()->SetTitleFont(132);
   h__1_yj->Draw("E1");
   Double_t xAxis2_yj[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h_sys__2_yj = new TH1F("h_sys__2_yj","h_sys",9, xAxis2_yj);
   h_sys__2_yj->SetBinContent(5,0.318942);
   h_sys__2_yj->SetBinContent(6,0.469444);
   h_sys__2_yj->SetBinContent(7,0.670662);
   h_sys__2_yj->SetBinContent(8,0.737576);
   h_sys__2_yj->SetBinError(5,0.02522695);
   h_sys__2_yj->SetBinError(6,0.0156823);
   h_sys__2_yj->SetBinError(7,0.007647864);
   h_sys__2_yj->SetBinError(8,0.02131035);
   h_sys__2_yj->SetEntries(4);
   h_sys__2_yj->SetStats(0);

   ci_yj = TColor::GetColor("#0000ff");
   h_sys__2_yj->SetFillColor(ci_yj);
   h_sys__2_yj->SetFillStyle(3004);

   ci_yj = TColor::GetColor("#0000ff");
   h_sys__2_yj->SetLineColor(ci_yj);
   h_sys__2_yj->SetLineWidth(2);

   ci_yj = TColor::GetColor("#0000ff");
   h_sys__2_yj->SetMarkerColor(ci_yj);
   h_sys__2_yj->SetMarkerStyle(24);
   h_sys__2_yj->GetXaxis()->SetNdivisions(505);
   h_sys__2_yj->GetXaxis()->SetLabelFont(132);
   h_sys__2_yj->GetXaxis()->SetLabelOffset(0.01);
   h_sys__2_yj->GetXaxis()->SetLabelSize(0.06);
   h_sys__2_yj->GetXaxis()->SetTitleSize(0.072);
   h_sys__2_yj->GetXaxis()->SetTitleOffset(0.95);
   h_sys__2_yj->GetXaxis()->SetTitleFont(132);
   h_sys__2_yj->GetYaxis()->SetLabelFont(132);
   h_sys__2_yj->GetYaxis()->SetLabelOffset(0.01);
   h_sys__2_yj->GetYaxis()->SetLabelSize(0.06);
   h_sys__2_yj->GetYaxis()->SetTitleSize(0.072);
   h_sys__2_yj->GetYaxis()->SetTitleOffset(0.95);
   h_sys__2_yj->GetYaxis()->SetTitleFont(132);
   h_sys__2_yj->GetZaxis()->SetLabelFont(132);
   h_sys__2_yj->GetZaxis()->SetLabelSize(0.06);
   h_sys__2_yj->GetZaxis()->SetTitleSize(0.072);
   h_sys__2_yj->GetZaxis()->SetTitleOffset(1.2);
   h_sys__2_yj->GetZaxis()->SetTitleFont(132);
   h_sys__2_yj->Draw("same E2");
   Double_t xAxis3_yj[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h_ht__3_yj = new TH1F("h_ht__3_yj","h_ht",9, xAxis3_yj);
   h_ht__3_yj->SetBinContent(6,0.541219);
   h_ht__3_yj->SetBinContent(7,0.652418);
   h_ht__3_yj->SetBinContent(8,0.754851);
   h_ht__3_yj->SetBinContent(9,0.816859);
   h_ht__3_yj->SetBinError(6,0.0909077);
   h_ht__3_yj->SetBinError(7,0.0785984);
   h_ht__3_yj->SetBinError(8,0.0902677);
   h_ht__3_yj->SetBinError(9,0.146675);
   h_ht__3_yj->SetEntries(4);
   h_ht__3_yj->SetStats(0);

   ci_yj = TColor::GetColor("#ff0000");
   h_ht__3_yj->SetLineColor(ci_yj);
   h_ht__3_yj->SetLineWidth(2);

   ci_yj = TColor::GetColor("#ff0000");
   h_ht__3_yj->SetMarkerColor(ci_yj);
   h_ht__3_yj->SetMarkerStyle(25);
   h_ht__3_yj->GetXaxis()->SetNdivisions(505);
   h_ht__3_yj->GetXaxis()->SetLabelFont(132);
   h_ht__3_yj->GetXaxis()->SetLabelOffset(0.01);
   h_ht__3_yj->GetXaxis()->SetLabelSize(0.06);
   h_ht__3_yj->GetXaxis()->SetTitleSize(0.072);
   h_ht__3_yj->GetXaxis()->SetTitleOffset(0.95);
   h_ht__3_yj->GetXaxis()->SetTitleFont(132);
   h_ht__3_yj->GetYaxis()->SetLabelFont(132);
   h_ht__3_yj->GetYaxis()->SetLabelOffset(0.01);
   h_ht__3_yj->GetYaxis()->SetLabelSize(0.06);
   h_ht__3_yj->GetYaxis()->SetTitleSize(0.072);
   h_ht__3_yj->GetYaxis()->SetTitleOffset(0.95);
   h_ht__3_yj->GetYaxis()->SetTitleFont(132);
   h_ht__3_yj->GetZaxis()->SetLabelFont(132);
   h_ht__3_yj->GetZaxis()->SetLabelSize(0.06);
   h_ht__3_yj->GetZaxis()->SetTitleSize(0.072);
   h_ht__3_yj->GetZaxis()->SetTitleOffset(1.2);
   h_ht__3_yj->GetZaxis()->SetTitleFont(132);
   h_ht__3_yj->Draw("same E1");
   Double_t xAxis4_yj[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h_sys_ht__4_yj = new TH1F("h_sys_ht__4_yj","h_sys_ht",9, xAxis4_yj);
   h_sys_ht__4_yj->SetBinContent(6,0.541219);
   h_sys_ht__4_yj->SetBinContent(7,0.652418);
   h_sys_ht__4_yj->SetBinContent(8,0.754851);
   h_sys_ht__4_yj->SetBinContent(9,0.816859);
   h_sys_ht__4_yj->SetBinError(6,0.04512625);
   h_sys_ht__4_yj->SetBinError(7,0.04672319);
   h_sys_ht__4_yj->SetBinError(8,0.03236365);
   h_sys_ht__4_yj->SetBinError(9,0.06873046);
   h_sys_ht__4_yj->SetEntries(4);
   h_sys_ht__4_yj->SetStats(0);

   ci_yj = TColor::GetColor("#ff0000");
   h_sys_ht__4_yj->SetFillColor(ci_yj);
   h_sys_ht__4_yj->SetFillStyle(3005);

   ci_yj = TColor::GetColor("#ff0000");
   h_sys_ht__4_yj->SetLineColor(ci_yj);
   h_sys_ht__4_yj->SetLineWidth(2);

   ci_yj = TColor::GetColor("#ff0000");
   h_sys_ht__4_yj->SetMarkerColor(ci_yj);
   h_sys_ht__4_yj->SetMarkerStyle(25);
   h_sys_ht__4_yj->GetXaxis()->SetNdivisions(505);
   h_sys_ht__4_yj->GetXaxis()->SetLabelFont(132);
   h_sys_ht__4_yj->GetXaxis()->SetLabelOffset(0.01);
   h_sys_ht__4_yj->GetXaxis()->SetLabelSize(0.06);
   h_sys_ht__4_yj->GetXaxis()->SetTitleSize(0.072);
   h_sys_ht__4_yj->GetXaxis()->SetTitleOffset(0.95);
   h_sys_ht__4_yj->GetXaxis()->SetTitleFont(132);
   h_sys_ht__4_yj->GetYaxis()->SetLabelFont(132);
   h_sys_ht__4_yj->GetYaxis()->SetLabelOffset(0.01);
   h_sys_ht__4_yj->GetYaxis()->SetLabelSize(0.06);
   h_sys_ht__4_yj->GetYaxis()->SetTitleSize(0.072);
   h_sys_ht__4_yj->GetYaxis()->SetTitleOffset(0.95);
   h_sys_ht__4_yj->GetYaxis()->SetTitleFont(132);
   h_sys_ht__4_yj->GetZaxis()->SetLabelFont(132);
   h_sys_ht__4_yj->GetZaxis()->SetLabelSize(0.06);
   h_sys_ht__4_yj->GetZaxis()->SetTitleSize(0.072);
   h_sys_ht__4_yj->GetZaxis()->SetTitleOffset(1.2);
   h_sys_ht__4_yj->GetZaxis()->SetTitleFont(132);
   h_sys_ht__4_yj->Draw("same E2");
   Double_t xAxis5_yj[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h_ht__5_yj = new TH1F("h_ht__5_yj","h_ht",9, xAxis5_yj);
   h_ht__5_yj->SetBinContent(6,0.541219);
   h_ht__5_yj->SetBinContent(7,0.652418);
   h_ht__5_yj->SetBinContent(8,0.754851);
   h_ht__5_yj->SetBinContent(9,0.816859);
   h_ht__5_yj->SetBinError(6,0.0909077);
   h_ht__5_yj->SetBinError(7,0.0785984);
   h_ht__5_yj->SetBinError(8,0.0902677);
   h_ht__5_yj->SetBinError(9,0.146675);
   h_ht__5_yj->SetEntries(4);
   h_ht__5_yj->SetStats(0);

   ci_yj = TColor::GetColor("#ff0000");
   h_ht__5_yj->SetLineColor(ci_yj);
   h_ht__5_yj->SetLineWidth(2);

   ci_yj = TColor::GetColor("#ff0000");
   h_ht__5_yj->SetMarkerColor(ci_yj);
   h_ht__5_yj->SetMarkerStyle(25);
   h_ht__5_yj->GetXaxis()->SetNdivisions(505);
   h_ht__5_yj->GetXaxis()->SetLabelFont(132);
   h_ht__5_yj->GetXaxis()->SetLabelOffset(0.01);
   h_ht__5_yj->GetXaxis()->SetLabelSize(0.06);
   h_ht__5_yj->GetXaxis()->SetTitleSize(0.072);
   h_ht__5_yj->GetXaxis()->SetTitleOffset(0.95);
   h_ht__5_yj->GetXaxis()->SetTitleFont(132);
   h_ht__5_yj->GetYaxis()->SetLabelFont(132);
   h_ht__5_yj->GetYaxis()->SetLabelOffset(0.01);
   h_ht__5_yj->GetYaxis()->SetLabelSize(0.06);
   h_ht__5_yj->GetYaxis()->SetTitleSize(0.072);
   h_ht__5_yj->GetYaxis()->SetTitleOffset(0.95);
   h_ht__5_yj->GetYaxis()->SetTitleFont(132);
   h_ht__5_yj->GetZaxis()->SetLabelFont(132);
   h_ht__5_yj->GetZaxis()->SetLabelSize(0.06);
   h_ht__5_yj->GetZaxis()->SetTitleSize(0.072);
   h_ht__5_yj->GetZaxis()->SetTitleOffset(1.2);
   h_ht__5_yj->GetZaxis()->SetTitleFont(132);
   h_ht__5_yj->Draw("same E1");
   Double_t xAxis6_yj[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h__6_yj = new TH1F("h__6_yj","h",9, xAxis6_yj);
   h__6_yj->SetBinContent(5,0.318942);
   h__6_yj->SetBinContent(6,0.469444);
   h__6_yj->SetBinContent(7,0.670662);
   h__6_yj->SetBinContent(8,0.737576);
   h__6_yj->SetBinError(5,0.00993923);
   h__6_yj->SetBinError(6,0.0149332);
   h__6_yj->SetBinError(7,0.0475619);
   h__6_yj->SetBinError(8,0.144196);
   h__6_yj->SetMinimum(0);
   h__6_yj->SetMaximum(1);
   h__6_yj->SetEntries(4);
   h__6_yj->SetStats(0);

   ci_yj = TColor::GetColor("#0000ff");
   h__6_yj->SetLineColor(ci_yj);
   h__6_yj->SetLineWidth(2);

   ci_yj = TColor::GetColor("#0000ff");
   h__6_yj->SetMarkerColor(ci_yj);
   h__6_yj->SetMarkerStyle(24);
   h__6_yj->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
   h__6_yj->GetXaxis()->SetNdivisions(505);
   h__6_yj->GetXaxis()->SetLabelFont(132);
   h__6_yj->GetXaxis()->SetLabelOffset(0.01);
   h__6_yj->GetXaxis()->SetLabelSize(0.06);
   h__6_yj->GetXaxis()->SetTitleSize(0.072);
   h__6_yj->GetXaxis()->SetTitleOffset(0.95);
   h__6_yj->GetXaxis()->SetTitleFont(132);
   h__6_yj->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
   h__6_yj->GetYaxis()->SetLabelFont(132);
   h__6_yj->GetYaxis()->SetLabelOffset(0.01);
   h__6_yj->GetYaxis()->SetLabelSize(0.06);
   h__6_yj->GetYaxis()->SetTitleSize(0.072);
   h__6_yj->GetYaxis()->SetTitleOffset(0.95);
   h__6_yj->GetYaxis()->SetTitleFont(132);
   h__6_yj->GetZaxis()->SetLabelFont(132);
   h__6_yj->GetZaxis()->SetLabelSize(0.06);
   h__6_yj->GetZaxis()->SetTitleSize(0.072);
   h__6_yj->GetZaxis()->SetTitleOffset(1.2);
   h__6_yj->GetZaxis()->SetTitleFont(132);
   h__6_yj->Draw("same E1");
   
   TLegend *leg = new TLegend(0.5,0.2,0.9,0.45,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h","Min. Bias","PLE");

   ci_yj = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci_yj);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci_yj = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci_yj);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h_ht","High Tower","PLE");

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
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
