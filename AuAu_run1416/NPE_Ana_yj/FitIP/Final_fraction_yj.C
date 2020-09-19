void Final_fraction(TH1F *h__1_yj_yj, TH1F *h_sys__2_yj_yj, TH1F *h_ht__3_yj_yj, TH1F *h_sys_ht__4_yj_yj, TH1F *h_ht__5_yj_yj, TH1F *h__6_yj_yj)
{
//=========Macro generated from canvas: c1/Final
//=========  (Mon Sep 30 09:05:15 2019) by ROOT version 6.16/00
  
   Double_t xAxis1[10] = {0.6+0.2, 1+0.2, 1.2+0.2, 1.5+0.2, 2+0.2, 2.5+0.2, 3.5+0.2, 4.5+0.2, 5.5+0.2, 8.5+0.2};
   
   TH1F *h__1_yj = new TH1F("h__1_yj","h",9, xAxis1);
   h__1_yj->SetBinContent(5,0.284646);
   h__1_yj->SetBinContent(6,0.435371);
   h__1_yj->SetBinContent(7,0.57172);
   h__1_yj->SetBinContent(8,0.649617);
   h__1_yj->SetBinContent(9,0.701379);
   h__1_yj->SetBinError(5,0.00715841);
   h__1_yj->SetBinError(6,0.0108699);
   h__1_yj->SetBinError(7,0.0317822);
   h__1_yj->SetBinError(8,0.0996994);
   h__1_yj->SetBinError(9,0.362389);
   h__1_yj->SetMinimum(0);
   h__1_yj->SetMaximum(1);
   h__1_yj->SetEntries(5);
   h__1_yj->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h__1_yj->SetLineColor(ci);
   h__1_yj->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   h__1_yj->SetMarkerColor(ci);
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
   Double_t xAxis2[10] = {0.6+0.2, 1+0.2, 1.2+0.2, 1.5+0.2, 2+0.2, 2.5+0.2, 3.5+0.2, 4.5+0.2, 5.5+0.2, 8.5+0.2};
   
   TH1F *h_sys__2_yj = new TH1F("h_sys__2_yj","h_sys",9, xAxis2);
   h_sys__2_yj->SetBinContent(5,0.284646);
   h_sys__2_yj->SetBinContent(6,0.435371);
   h_sys__2_yj->SetBinContent(7,0.57172);
   h_sys__2_yj->SetBinContent(8,0.649617);
   h_sys__2_yj->SetBinContent(9,0.701379);
   h_sys__2_yj->SetBinError(5,0.0260434);
   h_sys__2_yj->SetBinError(6,0.02091913);
   h_sys__2_yj->SetBinError(7,0.02194204);
   h_sys__2_yj->SetBinError(8,0.04049865);
   h_sys__2_yj->SetBinError(9,0.1290588);
   h_sys__2_yj->SetEntries(5);
   h_sys__2_yj->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   h_sys__2_yj->SetFillColor(ci);
   h_sys__2_yj->SetFillStyle(3004);

   ci = TColor::GetColor("#0000ff");
   h_sys__2_yj->SetLineColor(ci);
   h_sys__2_yj->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   h_sys__2_yj->SetMarkerColor(ci);
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
   Double_t xAxis3[10] = {0.6+0.2, 1+0.2, 1.2+0.2, 1.5+0.2, 2+0.2, 2.5+0.2, 3.5+0.2, 4.5+0.2, 5.5+0.2, 8.5+0.2};
   
   TH1F *h_ht__3_yj = new TH1F("h_ht__3_yj","h_ht",9, xAxis3);
   h_ht__3_yj->SetBinContent(6,0.539437);
   h_ht__3_yj->SetBinContent(7,0.594971);
   h_ht__3_yj->SetBinContent(8,0.690326);
   h_ht__3_yj->SetBinContent(9,0.762447);
   h_ht__3_yj->SetBinError(6,0.0761403);
   h_ht__3_yj->SetBinError(7,0.0560297);
   h_ht__3_yj->SetBinError(8,0.0621876);
   h_ht__3_yj->SetBinError(9,0.1049);
   h_ht__3_yj->SetEntries(4);
   h_ht__3_yj->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   h_ht__3_yj->SetLineColor(ci);
   h_ht__3_yj->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   h_ht__3_yj->SetMarkerColor(ci);
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
   Double_t xAxis4[10] = {0.6+0.2, 1+0.2, 1.2+0.2, 1.5+0.2, 2+0.2, 2.5+0.2, 3.5+0.2, 4.5+0.2, 5.5+0.2, 8.5+0.2};
   
   TH1F *h_sys_ht__4_yj = new TH1F("h_sys_ht__4_yj","h_sys_ht",9, xAxis4);
   h_sys_ht__4_yj->SetBinContent(6,0.539437);
   h_sys_ht__4_yj->SetBinContent(7,0.594971);
   h_sys_ht__4_yj->SetBinContent(8,0.690326);
   h_sys_ht__4_yj->SetBinContent(9,0.762447);
   h_sys_ht__4_yj->SetBinError(6,0.03371884);
   h_sys_ht__4_yj->SetBinError(7,0.03115801);
   h_sys_ht__4_yj->SetBinError(8,0.02406623);
   h_sys_ht__4_yj->SetBinError(9,0.04109743);
   h_sys_ht__4_yj->SetEntries(4);
   h_sys_ht__4_yj->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   h_sys_ht__4_yj->SetFillColor(ci);
   h_sys_ht__4_yj->SetFillStyle(3005);

   ci = TColor::GetColor("#ff0000");
   h_sys_ht__4_yj->SetLineColor(ci);
   h_sys_ht__4_yj->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   h_sys_ht__4_yj->SetMarkerColor(ci);
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
   Double_t xAxis5[10] = {0.6+0.2, 1+0.2, 1.2+0.2, 1.5+0.2, 2+0.2, 2.5+0.2, 3.5+0.2, 4.5+0.2, 5.5+0.2, 8.5+0.2};
   
   TH1F *h_ht__5_yj = new TH1F("h_ht__5_yj","h_ht",9, xAxis5);
   h_ht__5_yj->SetBinContent(6,0.539437);
   h_ht__5_yj->SetBinContent(7,0.594971);
   h_ht__5_yj->SetBinContent(8,0.690326);
   h_ht__5_yj->SetBinContent(9,0.762447);
   h_ht__5_yj->SetBinError(6,0.0761403);
   h_ht__5_yj->SetBinError(7,0.0560297);
   h_ht__5_yj->SetBinError(8,0.0621876);
   h_ht__5_yj->SetBinError(9,0.1049);
   h_ht__5_yj->SetEntries(4);
   h_ht__5_yj->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   h_ht__5_yj->SetLineColor(ci);
   h_ht__5_yj->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   h_ht__5_yj->SetMarkerColor(ci);
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
   Double_t xAxis6[10] = {0.6+0.2, 1+0.2, 1.2+0.2, 1.5+0.2, 2+0.2, 2.5+0.2, 3.5+0.2, 4.5+0.2, 5.5+0.2, 8.5+0.2};
   
   TH1F *h__6_yj = new TH1F("h__6_yj","h",9, xAxis6);
   h__6_yj->SetBinContent(5,0.284646);
   h__6_yj->SetBinContent(6,0.435371);
   h__6_yj->SetBinContent(7,0.57172);
   h__6_yj->SetBinContent(8,0.649617);
   h__6_yj->SetBinContent(9,0.701379);
   h__6_yj->SetBinError(5,0.00715841);
   h__6_yj->SetBinError(6,0.0108699);
   h__6_yj->SetBinError(7,0.0317822);
   h__6_yj->SetBinError(8,0.0996994);
   h__6_yj->SetBinError(9,0.362389);
   h__6_yj->SetMinimum(0);
   h__6_yj->SetMaximum(1);
   h__6_yj->SetEntries(5);
   h__6_yj->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   h__6_yj->SetLineColor(ci);
   h__6_yj->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   h__6_yj->SetMarkerColor(ci);
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
}
