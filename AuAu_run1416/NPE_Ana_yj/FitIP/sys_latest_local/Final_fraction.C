void Final_fraction()
{
//=========Macro generated from canvas: c1/Final
//=========  (Mon Sep 30 09:08:43 2019) by ROOT version 6.16/00
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
   Double_t xAxis1[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h__1 = new TH1F("h__1","h",9, xAxis1);
   h__1->SetBinContent(5,0.286525);
   h__1->SetBinContent(6,0.436221);
   h__1->SetBinContent(7,0.571527);
   h__1->SetBinContent(8,0.649949);
   h__1->SetBinContent(9,0.701772);
   h__1->SetBinError(5,0.00715709);
   h__1->SetBinError(6,0.0108507);
   h__1->SetBinError(7,0.0317072);
   h__1->SetBinError(8,0.0996867);
   h__1->SetBinError(9,0.362562);
   h__1->SetMinimum(0);
   h__1->SetMaximum(1);
   h__1->SetEntries(5);
   h__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h__1->SetLineColor(ci);
   h__1->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   h__1->SetMarkerColor(ci);
   h__1->SetMarkerStyle(24);
   h__1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
   h__1->GetXaxis()->SetNdivisions(505);
   h__1->GetXaxis()->SetLabelFont(132);
   h__1->GetXaxis()->SetLabelOffset(0.01);
   h__1->GetXaxis()->SetLabelSize(0.06);
   h__1->GetXaxis()->SetTitleSize(0.072);
   h__1->GetXaxis()->SetTitleOffset(0.95);
   h__1->GetXaxis()->SetTitleFont(132);
   h__1->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
   h__1->GetYaxis()->SetLabelFont(132);
   h__1->GetYaxis()->SetLabelOffset(0.01);
   h__1->GetYaxis()->SetLabelSize(0.06);
   h__1->GetYaxis()->SetTitleSize(0.072);
   h__1->GetYaxis()->SetTitleOffset(0.95);
   h__1->GetYaxis()->SetTitleFont(132);
   h__1->GetZaxis()->SetLabelFont(132);
   h__1->GetZaxis()->SetLabelSize(0.06);
   h__1->GetZaxis()->SetTitleSize(0.072);
   h__1->GetZaxis()->SetTitleOffset(1.2);
   h__1->GetZaxis()->SetTitleFont(132);
   h__1->Draw("E1");
   Double_t xAxis2[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h_sys__2 = new TH1F("h_sys__2","h_sys",9, xAxis2);
   h_sys__2->SetBinContent(5,0.286525);
   h_sys__2->SetBinContent(6,0.436221);
   h_sys__2->SetBinContent(7,0.571527);
   h_sys__2->SetBinContent(8,0.649949);
   h_sys__2->SetBinContent(9,0.701772);
   h_sys__2->SetBinError(5,0.02436258);
   h_sys__2->SetBinError(6,0.0207101);
   h_sys__2->SetBinError(7,0.02138056);
   h_sys__2->SetBinError(8,0.03534933);
   h_sys__2->SetBinError(9,0.1484424);
   h_sys__2->SetEntries(5);
   h_sys__2->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   h_sys__2->SetFillColor(ci);
   h_sys__2->SetFillStyle(3004);

   ci = TColor::GetColor("#0000ff");
   h_sys__2->SetLineColor(ci);
   h_sys__2->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   h_sys__2->SetMarkerColor(ci);
   h_sys__2->SetMarkerStyle(24);
   h_sys__2->GetXaxis()->SetNdivisions(505);
   h_sys__2->GetXaxis()->SetLabelFont(132);
   h_sys__2->GetXaxis()->SetLabelOffset(0.01);
   h_sys__2->GetXaxis()->SetLabelSize(0.06);
   h_sys__2->GetXaxis()->SetTitleSize(0.072);
   h_sys__2->GetXaxis()->SetTitleOffset(0.95);
   h_sys__2->GetXaxis()->SetTitleFont(132);
   h_sys__2->GetYaxis()->SetLabelFont(132);
   h_sys__2->GetYaxis()->SetLabelOffset(0.01);
   h_sys__2->GetYaxis()->SetLabelSize(0.06);
   h_sys__2->GetYaxis()->SetTitleSize(0.072);
   h_sys__2->GetYaxis()->SetTitleOffset(0.95);
   h_sys__2->GetYaxis()->SetTitleFont(132);
   h_sys__2->GetZaxis()->SetLabelFont(132);
   h_sys__2->GetZaxis()->SetLabelSize(0.06);
   h_sys__2->GetZaxis()->SetTitleSize(0.072);
   h_sys__2->GetZaxis()->SetTitleOffset(1.2);
   h_sys__2->GetZaxis()->SetTitleFont(132);
   h_sys__2->Draw("same E2");
   Double_t xAxis3[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h_ht__3 = new TH1F("h_ht__3","h_ht",9, xAxis3);
   h_ht__3->SetBinContent(6,0.539437);
   h_ht__3->SetBinContent(7,0.594971);
   h_ht__3->SetBinContent(8,0.690326);
   h_ht__3->SetBinContent(9,0.762447);
   h_ht__3->SetBinError(6,0.0761403);
   h_ht__3->SetBinError(7,0.0560297);
   h_ht__3->SetBinError(8,0.0621876);
   h_ht__3->SetBinError(9,0.1049);
   h_ht__3->SetEntries(4);
   h_ht__3->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   h_ht__3->SetLineColor(ci);
   h_ht__3->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   h_ht__3->SetMarkerColor(ci);
   h_ht__3->SetMarkerStyle(25);
   h_ht__3->GetXaxis()->SetNdivisions(505);
   h_ht__3->GetXaxis()->SetLabelFont(132);
   h_ht__3->GetXaxis()->SetLabelOffset(0.01);
   h_ht__3->GetXaxis()->SetLabelSize(0.06);
   h_ht__3->GetXaxis()->SetTitleSize(0.072);
   h_ht__3->GetXaxis()->SetTitleOffset(0.95);
   h_ht__3->GetXaxis()->SetTitleFont(132);
   h_ht__3->GetYaxis()->SetLabelFont(132);
   h_ht__3->GetYaxis()->SetLabelOffset(0.01);
   h_ht__3->GetYaxis()->SetLabelSize(0.06);
   h_ht__3->GetYaxis()->SetTitleSize(0.072);
   h_ht__3->GetYaxis()->SetTitleOffset(0.95);
   h_ht__3->GetYaxis()->SetTitleFont(132);
   h_ht__3->GetZaxis()->SetLabelFont(132);
   h_ht__3->GetZaxis()->SetLabelSize(0.06);
   h_ht__3->GetZaxis()->SetTitleSize(0.072);
   h_ht__3->GetZaxis()->SetTitleOffset(1.2);
   h_ht__3->GetZaxis()->SetTitleFont(132);
   h_ht__3->Draw("same E1");
   Double_t xAxis4[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h_sys_ht__4 = new TH1F("h_sys_ht__4","h_sys_ht",9, xAxis4);
   h_sys_ht__4->SetBinContent(6,0.539437);
   h_sys_ht__4->SetBinContent(7,0.594971);
   h_sys_ht__4->SetBinContent(8,0.690326);
   h_sys_ht__4->SetBinContent(9,0.762447);
   h_sys_ht__4->SetBinError(6,0.03371884);
   h_sys_ht__4->SetBinError(7,0.03115801);
   h_sys_ht__4->SetBinError(8,0.02406623);
   h_sys_ht__4->SetBinError(9,0.04109743);
   h_sys_ht__4->SetEntries(4);
   h_sys_ht__4->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   h_sys_ht__4->SetFillColor(ci);
   h_sys_ht__4->SetFillStyle(3005);

   ci = TColor::GetColor("#ff0000");
   h_sys_ht__4->SetLineColor(ci);
   h_sys_ht__4->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   h_sys_ht__4->SetMarkerColor(ci);
   h_sys_ht__4->SetMarkerStyle(25);
   h_sys_ht__4->GetXaxis()->SetNdivisions(505);
   h_sys_ht__4->GetXaxis()->SetLabelFont(132);
   h_sys_ht__4->GetXaxis()->SetLabelOffset(0.01);
   h_sys_ht__4->GetXaxis()->SetLabelSize(0.06);
   h_sys_ht__4->GetXaxis()->SetTitleSize(0.072);
   h_sys_ht__4->GetXaxis()->SetTitleOffset(0.95);
   h_sys_ht__4->GetXaxis()->SetTitleFont(132);
   h_sys_ht__4->GetYaxis()->SetLabelFont(132);
   h_sys_ht__4->GetYaxis()->SetLabelOffset(0.01);
   h_sys_ht__4->GetYaxis()->SetLabelSize(0.06);
   h_sys_ht__4->GetYaxis()->SetTitleSize(0.072);
   h_sys_ht__4->GetYaxis()->SetTitleOffset(0.95);
   h_sys_ht__4->GetYaxis()->SetTitleFont(132);
   h_sys_ht__4->GetZaxis()->SetLabelFont(132);
   h_sys_ht__4->GetZaxis()->SetLabelSize(0.06);
   h_sys_ht__4->GetZaxis()->SetTitleSize(0.072);
   h_sys_ht__4->GetZaxis()->SetTitleOffset(1.2);
   h_sys_ht__4->GetZaxis()->SetTitleFont(132);
   h_sys_ht__4->Draw("same E2");
   Double_t xAxis5[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h_ht__5 = new TH1F("h_ht__5","h_ht",9, xAxis5);
   h_ht__5->SetBinContent(6,0.539437);
   h_ht__5->SetBinContent(7,0.594971);
   h_ht__5->SetBinContent(8,0.690326);
   h_ht__5->SetBinContent(9,0.762447);
   h_ht__5->SetBinError(6,0.0761403);
   h_ht__5->SetBinError(7,0.0560297);
   h_ht__5->SetBinError(8,0.0621876);
   h_ht__5->SetBinError(9,0.1049);
   h_ht__5->SetEntries(4);
   h_ht__5->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   h_ht__5->SetLineColor(ci);
   h_ht__5->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   h_ht__5->SetMarkerColor(ci);
   h_ht__5->SetMarkerStyle(25);
   h_ht__5->GetXaxis()->SetNdivisions(505);
   h_ht__5->GetXaxis()->SetLabelFont(132);
   h_ht__5->GetXaxis()->SetLabelOffset(0.01);
   h_ht__5->GetXaxis()->SetLabelSize(0.06);
   h_ht__5->GetXaxis()->SetTitleSize(0.072);
   h_ht__5->GetXaxis()->SetTitleOffset(0.95);
   h_ht__5->GetXaxis()->SetTitleFont(132);
   h_ht__5->GetYaxis()->SetLabelFont(132);
   h_ht__5->GetYaxis()->SetLabelOffset(0.01);
   h_ht__5->GetYaxis()->SetLabelSize(0.06);
   h_ht__5->GetYaxis()->SetTitleSize(0.072);
   h_ht__5->GetYaxis()->SetTitleOffset(0.95);
   h_ht__5->GetYaxis()->SetTitleFont(132);
   h_ht__5->GetZaxis()->SetLabelFont(132);
   h_ht__5->GetZaxis()->SetLabelSize(0.06);
   h_ht__5->GetZaxis()->SetTitleSize(0.072);
   h_ht__5->GetZaxis()->SetTitleOffset(1.2);
   h_ht__5->GetZaxis()->SetTitleFont(132);
   h_ht__5->Draw("same E1");
   Double_t xAxis6[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *h__6 = new TH1F("h__6","h",9, xAxis6);
   h__6->SetBinContent(5,0.286525);
   h__6->SetBinContent(6,0.436221);
   h__6->SetBinContent(7,0.571527);
   h__6->SetBinContent(8,0.649949);
   h__6->SetBinContent(9,0.701772);
   h__6->SetBinError(5,0.00715709);
   h__6->SetBinError(6,0.0108507);
   h__6->SetBinError(7,0.0317072);
   h__6->SetBinError(8,0.0996867);
   h__6->SetBinError(9,0.362562);
   h__6->SetMinimum(0);
   h__6->SetMaximum(1);
   h__6->SetEntries(5);
   h__6->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   h__6->SetLineColor(ci);
   h__6->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   h__6->SetMarkerColor(ci);
   h__6->SetMarkerStyle(24);
   h__6->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
   h__6->GetXaxis()->SetNdivisions(505);
   h__6->GetXaxis()->SetLabelFont(132);
   h__6->GetXaxis()->SetLabelOffset(0.01);
   h__6->GetXaxis()->SetLabelSize(0.06);
   h__6->GetXaxis()->SetTitleSize(0.072);
   h__6->GetXaxis()->SetTitleOffset(0.95);
   h__6->GetXaxis()->SetTitleFont(132);
   h__6->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
   h__6->GetYaxis()->SetLabelFont(132);
   h__6->GetYaxis()->SetLabelOffset(0.01);
   h__6->GetYaxis()->SetLabelSize(0.06);
   h__6->GetYaxis()->SetTitleSize(0.072);
   h__6->GetYaxis()->SetTitleOffset(0.95);
   h__6->GetYaxis()->SetTitleFont(132);
   h__6->GetZaxis()->SetLabelFont(132);
   h__6->GetZaxis()->SetLabelSize(0.06);
   h__6->GetZaxis()->SetTitleSize(0.072);
   h__6->GetZaxis()->SetTitleOffset(1.2);
   h__6->GetZaxis()->SetTitleFont(132);
   h__6->Draw("same E1");
   
   TLegend *leg = new TLegend(0.5,0.2,0.9,0.45,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h","Min. Bias","PLE");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h_ht","High Tower","PLE");

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
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
