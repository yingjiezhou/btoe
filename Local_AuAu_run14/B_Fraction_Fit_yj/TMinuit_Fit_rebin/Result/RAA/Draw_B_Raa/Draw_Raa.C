void Draw_Raa()
{
//=========Macro generated from canvas: c3/
//=========  (Wed Jul  3 11:55:23 2019) by ROOT version 6.16/00
   TCanvas *c3 = new TCanvas("c3", "",0,70,1000,730);
   gStyle->SetOptStat(0);
   c3->Range(0,0,1,1);
   c3->SetFillColor(0);
   c3->SetBorderMode(0);
   c3->SetBorderSize(2);
   c3->SetLeftMargin(0.16);
   c3->SetRightMargin(0.06);
   c3->SetTopMargin(0.08);
   c3->SetBottomMargin(0.16);
   c3->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "pad1",0,0.4,1,1);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-1.529412,-0.8239087,10.23529,0.6311614);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLogy();
   pad1->SetLeftMargin(0.13);
   pad1->SetRightMargin(0.02);
   pad1->SetTopMargin(0.02);
   pad1->SetBottomMargin(0);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameBorderMode(0);
   
   TH2F *h1__5 = new TH2F("h1__5","",100,0,10,100,0.15,4);
   h1__5->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1__5->SetLineColor(ci);
   h1__5->GetXaxis()->SetTitle("p_{T}^{e} (GeV/c)");
   h1__5->GetXaxis()->CenterTitle(true);
   h1__5->GetXaxis()->SetLabelFont(42);
   h1__5->GetXaxis()->SetLabelSize(0.08);
   h1__5->GetXaxis()->SetTitleSize(0.08);
   h1__5->GetXaxis()->SetTitleOffset(1);
   h1__5->GetXaxis()->SetTitleFont(42);
   h1__5->GetYaxis()->SetTitle("R_{AA}");
   h1__5->GetYaxis()->CenterTitle(true);
   h1__5->GetYaxis()->SetNdivisions(20);
   h1__5->GetYaxis()->SetLabelFont(42);
   h1__5->GetYaxis()->SetLabelSize(0.08);
   h1__5->GetYaxis()->SetTitleSize(0.06);
   h1__5->GetYaxis()->SetTitleOffset(0.6);
   h1__5->GetYaxis()->SetTitleFont(42);
   h1__5->GetZaxis()->SetLabelFont(42);
   h1__5->GetZaxis()->SetLabelSize(0.035);
   h1__5->GetZaxis()->SetTitleSize(0.035);
   h1__5->GetZaxis()->SetTitleOffset(1);
   h1__5->GetZaxis()->SetTitleFont(42);
   h1__5->Draw("");
   
   Double_t Graph_from_Fb_to_Raa_e_sys_fx1009[4] = {
   3.05,
   4.05,
   5.05,
   7.05};
   Double_t Graph_from_Fb_to_Raa_e_sys_fy1009[4] = {
   0.9357122,
   0.7479938,
   0.6629463,
   0.7339454};
   Double_t Graph_from_Fb_to_Raa_e_sys_fex1009[4] = {
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t Graph_from_Fb_to_Raa_e_sys_fey1009[4] = {
   0.2508492,
   0.1456957,
   0.1414282,
   0.2243631};
   TGraphErrors *gre = new TGraphErrors(4,Graph_from_Fb_to_Raa_e_sys_fx1009,Graph_from_Fb_to_Raa_e_sys_fy1009,Graph_from_Fb_to_Raa_e_sys_fex1009,Graph_from_Fb_to_Raa_e_sys_fey1009);
   gre->SetName("Graph_from_Fb_to_Raa_e_sys");
   gre->SetTitle("");
   gre->SetFillColor(40);
   gre->SetLineColor(40);
   
   TH1F *Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009 = new TH1F("Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009","",100,2.53,7.57);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->SetMinimum(0.4418844);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->SetMaximum(1.254259);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->SetDirectory(0);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->SetLineColor(ci);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetYaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph_from_Fb_to_Raa_e_sys10041009);
   
   gre->Draw("e2");
   
   Double_t Graph_from_Fc_to_e_Raa_sys_fx1010[4] = {
   3,
   4,
   5,
   7};
   Double_t Graph_from_Fc_to_e_Raa_sys_fy1010[4] = {
   0.5696591,
   0.2887442,
   0.3769237,
   0.3859783};
   Double_t Graph_from_Fc_to_e_Raa_sys_fex1010[4] = {
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t Graph_from_Fc_to_e_Raa_sys_fey1010[4] = {
   0.1527163,
   0.05624218,
   0.0804102,
   0.1179915};
   gre = new TGraphErrors(4,Graph_from_Fc_to_e_Raa_sys_fx1010,Graph_from_Fc_to_e_Raa_sys_fy1010,Graph_from_Fc_to_e_Raa_sys_fex1010,Graph_from_Fc_to_e_Raa_sys_fey1010);
   gre->SetName("Graph_from_Fc_to_e_Raa_sys");
   gre->SetTitle("");
   gre->SetFillColor(17);
   gre->SetLineColor(17);
   
   TH1F *Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010 = new TH1F("Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010","",100,2.48,7.52);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->SetMinimum(0.1835147);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->SetMaximum(0.7713627);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->SetDirectory(0);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->SetLineColor(ci);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetYaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph_from_Fc_to_e_Raa_sys10071010);
   
   gre->Draw("e2");
   
   Double_t doubleRatio_fx3001[8] = {
   3.2,
   4.2,
   5.2,
   -98.8,
   -98.8,
   -98.8,
   -98.8,
   -98.8};
   Double_t doubleRatio_fy3001[8] = {
   1.321645,
   1.595802,
   1.24347,
   -99,
   -99,
   -99,
   -99,
   -99};
   Double_t doubleRatio_felx3001[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t doubleRatio_fely3001[8] = {
   0.2479606,
   0.2771208,
   0.2609063,
   0,
   0,
   0,
   0,
   0};
   Double_t doubleRatio_fehx3001[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t doubleRatio_fehy3001[8] = {
   0.187615,
   0.1736561,
   0.2098212,
   0,
   0,
   0,
   0,
   0};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(8,doubleRatio_fx3001,doubleRatio_fy3001,doubleRatio_felx3001,doubleRatio_fehx3001,doubleRatio_fely3001,doubleRatio_fehy3001);
   grae->SetName("doubleRatio");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetLineColor(3);
   grae->SetMarkerColor(3);
   grae->SetMarkerStyle(21);
   grae->SetMarkerSize(2);
   
   TH1F *Graph_doubleRatio3001 = new TH1F("Graph_doubleRatio3001","Graph",100,-109.2,15.6);
   Graph_doubleRatio3001->SetMinimum(0.005246404);
   Graph_doubleRatio3001->SetMaximum(5.246404);
   Graph_doubleRatio3001->SetDirectory(0);
   Graph_doubleRatio3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_doubleRatio3001->SetLineColor(ci);
   Graph_doubleRatio3001->GetXaxis()->SetLabelFont(42);
   Graph_doubleRatio3001->GetXaxis()->SetLabelSize(0.035);
   Graph_doubleRatio3001->GetXaxis()->SetTitleSize(0.06);
   Graph_doubleRatio3001->GetXaxis()->SetTitleOffset(1);
   Graph_doubleRatio3001->GetXaxis()->SetTitleFont(42);
   Graph_doubleRatio3001->GetYaxis()->SetLabelFont(42);
   Graph_doubleRatio3001->GetYaxis()->SetLabelSize(0.035);
   Graph_doubleRatio3001->GetYaxis()->SetTitleSize(0.06);
   Graph_doubleRatio3001->GetYaxis()->SetTitleOffset(1);
   Graph_doubleRatio3001->GetYaxis()->SetTitleFont(42);
   Graph_doubleRatio3001->GetZaxis()->SetLabelFont(42);
   Graph_doubleRatio3001->GetZaxis()->SetLabelSize(0.035);
   Graph_doubleRatio3001->GetZaxis()->SetTitleSize(0.035);
   Graph_doubleRatio3001->GetZaxis()->SetTitleOffset(1);
   Graph_doubleRatio3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_doubleRatio3001);
   
   grae->Draw("pe");
   
   Double_t doubleRatioSys_fx3002[8] = {
   3.2,
   4.2,
   5.2,
   -98.8,
   -98.8,
   -98.8,
   -98.8,
   -98.8};
   Double_t doubleRatioSys_fy3002[8] = {
   1.321645,
   1.595802,
   1.24347,
   -99,
   -99,
   -99,
   -99,
   -99};
   Double_t doubleRatioSys_felx3002[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t doubleRatioSys_fely3002[8] = {
   0.5181075,
   0.4644431,
   0.4012369,
   0,
   0,
   0,
   0,
   0};
   Double_t doubleRatioSys_fehx3002[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t doubleRatioSys_fehy3002[8] = {
   0.3878304,
   0.3098409,
   0.3476672,
   0,
   0,
   0,
   0,
   0};
   grae = new TGraphAsymmErrors(8,doubleRatioSys_fx3002,doubleRatioSys_fy3002,doubleRatioSys_felx3002,doubleRatioSys_fehx3002,doubleRatioSys_fely3002,doubleRatioSys_fehy3002);
   grae->SetName("doubleRatioSys");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetLineColor(3);
   grae->Draw("p[],");
   
   Double_t doubleRatioc_fx3003[8] = {
   3.2,
   4.2,
   5.2,
   -98.8,
   -98.8,
   -98.8,
   -98.8,
   -98.8};
   Double_t doubleRatioc_fy3003[8] = {
   0.84027,
   0.5780799,
   0.7062755,
   -99,
   -99,
   -99,
   -99,
   -99};
   Double_t doubleRatioc_felx3003[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t doubleRatioc_fely3003[8] = {
   0.08165105,
   0.1002326,
   0.2316067,
   0,
   0,
   0,
   0,
   0};
   Double_t doubleRatioc_fehx3003[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t doubleRatioc_fehy3003[8] = {
   0.09717239,
   0.1733888,
   0.3279269,
   0,
   0,
   0,
   0,
   0};
   grae = new TGraphAsymmErrors(8,doubleRatioc_fx3003,doubleRatioc_fy3003,doubleRatioc_felx3003,doubleRatioc_fehx3003,doubleRatioc_fely3003,doubleRatioc_fehy3003);
   grae->SetName("doubleRatioc");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetLineColor(6);
   grae->SetMarkerColor(6);
   grae->SetMarkerStyle(21);
   grae->SetMarkerSize(2);
   
   TH1F *Graph_doubleRatioc3003 = new TH1F("Graph_doubleRatioc3003","Graph",100,-109.2,15.6);
   Graph_doubleRatioc3003->SetMinimum(0.004437623);
   Graph_doubleRatioc3003->SetMaximum(4.437623);
   Graph_doubleRatioc3003->SetDirectory(0);
   Graph_doubleRatioc3003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_doubleRatioc3003->SetLineColor(ci);
   Graph_doubleRatioc3003->GetXaxis()->SetLabelFont(42);
   Graph_doubleRatioc3003->GetXaxis()->SetLabelSize(0.035);
   Graph_doubleRatioc3003->GetXaxis()->SetTitleSize(0.06);
   Graph_doubleRatioc3003->GetXaxis()->SetTitleOffset(1);
   Graph_doubleRatioc3003->GetXaxis()->SetTitleFont(42);
   Graph_doubleRatioc3003->GetYaxis()->SetLabelFont(42);
   Graph_doubleRatioc3003->GetYaxis()->SetLabelSize(0.035);
   Graph_doubleRatioc3003->GetYaxis()->SetTitleSize(0.06);
   Graph_doubleRatioc3003->GetYaxis()->SetTitleOffset(1);
   Graph_doubleRatioc3003->GetYaxis()->SetTitleFont(42);
   Graph_doubleRatioc3003->GetZaxis()->SetLabelFont(42);
   Graph_doubleRatioc3003->GetZaxis()->SetLabelSize(0.035);
   Graph_doubleRatioc3003->GetZaxis()->SetTitleSize(0.035);
   Graph_doubleRatioc3003->GetZaxis()->SetTitleOffset(1);
   Graph_doubleRatioc3003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_doubleRatioc3003);
   
   grae->Draw("pe");
   
   Double_t Graph0_fx1011[20] = {
   0.25,
   0.75,
   1.25,
   1.75,
   2.25,
   2.75,
   3.25,
   3.75,
   4.25,
   4.75,
   5.25,
   5.75,
   6.25,
   6.75,
   7.25,
   7.75,
   8.25,
   8.75,
   9.25,
   9.75};
   Double_t Graph0_fy1011[20] = {
   0.74,
   0.803,
   1.02,
   0.85,
   0.692,
   0.591,
   0.535,
   0.474,
   0.482,
   0.471,
   0.461,
   0.477,
   0.459,
   0.464,
   0.454,
   0.45,
   0.423,
   0.478,
   0.445,
   0.439};
   Double_t Graph0_fex1011[20] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1011[20] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(20,Graph0_fx1011,Graph0_fy1011,Graph0_fex1011,Graph0_fey1011);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetLineStyle(3);
   gre->SetLineWidth(2);
   
   TH1F *Graph_Graph01011 = new TH1F("Graph_Graph01011","Graph",100,0,10.7);
   Graph_Graph01011->SetMinimum(0.3633);
   Graph_Graph01011->SetMaximum(1.0797);
   Graph_Graph01011->SetDirectory(0);
   Graph_Graph01011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01011->SetLineColor(ci);
   Graph_Graph01011->GetXaxis()->SetLabelFont(42);
   Graph_Graph01011->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph01011->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01011->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01011->GetXaxis()->SetTitleFont(42);
   Graph_Graph01011->GetYaxis()->SetLabelFont(42);
   Graph_Graph01011->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph01011->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01011->GetYaxis()->SetTitleOffset(1);
   Graph_Graph01011->GetYaxis()->SetTitleFont(42);
   Graph_Graph01011->GetZaxis()->SetLabelFont(42);
   Graph_Graph01011->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01011->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01011->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01011);
   
   gre->Draw("c");
   
   Double_t Graph1_fx1012[20] = {
   0.25,
   0.75,
   1.25,
   1.75,
   2.25,
   2.75,
   3.25,
   3.75,
   4.25,
   4.75,
   5.25,
   5.75,
   6.25,
   6.75,
   7.25,
   7.75,
   8.25,
   8.75,
   9.25,
   9.75};
   Double_t Graph1_fy1012[20] = {
   0.952,
   0.96,
   0.943,
   0.964,
   1.07,
   1.12,
   1.09,
   1.05,
   0.982,
   0.897,
   0.848,
   0.815,
   0.759,
   0.725,
   0.721,
   0.683,
   0.642,
   0.637,
   0.623,
   0.602};
   Double_t Graph1_fex1012[20] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1012[20] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(20,Graph1_fx1012,Graph1_fy1012,Graph1_fex1012,Graph1_fey1012);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineStyle(3);
   gre->SetLineWidth(2);
   
   TH1F *Graph_Graph11012 = new TH1F("Graph_Graph11012","Graph",100,0,10.7);
   Graph_Graph11012->SetMinimum(0.5502);
   Graph_Graph11012->SetMaximum(1.1718);
   Graph_Graph11012->SetDirectory(0);
   Graph_Graph11012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11012->SetLineColor(ci);
   Graph_Graph11012->GetXaxis()->SetLabelFont(42);
   Graph_Graph11012->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11012->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11012->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11012->GetXaxis()->SetTitleFont(42);
   Graph_Graph11012->GetYaxis()->SetLabelFont(42);
   Graph_Graph11012->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11012->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11012->GetYaxis()->SetTitleOffset(1);
   Graph_Graph11012->GetYaxis()->SetTitleFont(42);
   Graph_Graph11012->GetZaxis()->SetLabelFont(42);
   Graph_Graph11012->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11012->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11012->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11012);
   
   gre->Draw("c");
   
   Double_t Graph_from_Fb_to_Raa_e_pp_sys_fx1013[4] = {
   3.05,
   4.05,
   5.05,
   7.05};
   Double_t Graph_from_Fb_to_Raa_e_pp_sys_fy1013[4] = {
   0.9357122,
   0.7479938,
   0.6629463,
   0.7339454};
   Double_t Graph_from_Fb_to_Raa_e_pp_sys_fex1013[4] = {
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t Graph_from_Fb_to_Raa_e_pp_sys_fey1013[4] = {
   0.15607,
   0.1987671,
   0.2715739,
   0.2199735};
   gre = new TGraphErrors(4,Graph_from_Fb_to_Raa_e_pp_sys_fx1013,Graph_from_Fb_to_Raa_e_pp_sys_fy1013,Graph_from_Fb_to_Raa_e_pp_sys_fex1013,Graph_from_Fb_to_Raa_e_pp_sys_fey1013);
   gre->SetName("Graph_from_Fb_to_Raa_e_pp_sys");
   gre->SetTitle("");
   gre->Draw("p[]:");
   
   Double_t Graph_from_Fc_to_e_Raa_pp_sys_fx1014[4] = {
   3,
   4,
   5,
   7};
   Double_t Graph_from_Fc_to_e_Raa_pp_sys_fy1014[4] = {
   0.5696591,
   0.2887442,
   0.3769237,
   0.3859783};
   Double_t Graph_from_Fc_to_e_Raa_pp_sys_fex1014[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph_from_Fc_to_e_Raa_pp_sys_fey1014[4] = {
   0.05412615,
   0.02215506,
   0.05819915,
   0.04465114};
   gre = new TGraphErrors(4,Graph_from_Fc_to_e_Raa_pp_sys_fx1014,Graph_from_Fc_to_e_Raa_pp_sys_fy1014,Graph_from_Fc_to_e_Raa_pp_sys_fex1014,Graph_from_Fc_to_e_Raa_pp_sys_fey1014);
   gre->SetName("Graph_from_Fc_to_e_Raa_pp_sys");
   gre->SetTitle("");
   gre->SetLineColor(2);
   gre->Draw("p[]:");
   
   Double_t Graph_from_Fc_to_e_Raa_sts_fx1015[4] = {
   3,
   4,
   5,
   7};
   Double_t Graph_from_Fc_to_e_Raa_sts_fy1015[4] = {
   0.5696591,
   0.2887442,
   0.3769237,
   0.3859783};
   Double_t Graph_from_Fc_to_e_Raa_sts_fex1015[4] = {
   0.5,
   0.5,
   0.5,
   1.5};
   Double_t Graph_from_Fc_to_e_Raa_sts_fey1015[4] = {
   0.07275431,
   0.06725957,
   0.1297796,
   0.2255538};
   gre = new TGraphErrors(4,Graph_from_Fc_to_e_Raa_sts_fx1015,Graph_from_Fc_to_e_Raa_sts_fy1015,Graph_from_Fc_to_e_Raa_sts_fex1015,Graph_from_Fc_to_e_Raa_sts_fey1015);
   gre->SetName("Graph_from_Fc_to_e_Raa_sts");
   gre->SetTitle("");
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph_from_Fc_to_e_Raa_sts1015 = new TH1F("Graph_Graph_from_Fc_to_e_Raa_sts1015","",100,1.9,9.1);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->SetMinimum(0.1122256);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->SetMaximum(0.6906122);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->SetDirectory(0);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_from_Fc_to_e_Raa_sts1015->SetLineColor(ci);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetXaxis()->SetLabelFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetXaxis()->SetTitleFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetYaxis()->SetLabelFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetYaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetYaxis()->SetTitleFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetZaxis()->SetLabelFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fc_to_e_Raa_sts1015->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_from_Fc_to_e_Raa_sts1015);
   
   gre->Draw("pe");
   
   Double_t Graph_from_Fb_to_e_Raa_sts_fx1016[4] = {
   3.05,
   4.05,
   5.05,
   7.05};
   Double_t Graph_from_Fb_to_e_Raa_sts_fy1016[4] = {
   0.9357122,
   0.7479938,
   0.6629463,
   0.7339454};
   Double_t Graph_from_Fb_to_e_Raa_sts_fex1016[4] = {
   0.5,
   0.5,
   0.5,
   1.5};
   Double_t Graph_from_Fb_to_e_Raa_sts_fey1016[4] = {
   0.2044186,
   0.1463474,
   0.1754212,
   0.2224822};
   gre = new TGraphErrors(4,Graph_from_Fb_to_e_Raa_sts_fx1016,Graph_from_Fb_to_e_Raa_sts_fy1016,Graph_from_Fb_to_e_Raa_sts_fex1016,Graph_from_Fb_to_e_Raa_sts_fey1016);
   gre->SetName("Graph_from_Fb_to_e_Raa_sts");
   gre->SetTitle("");
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph_from_Fb_to_e_Raa_sts1016 = new TH1F("Graph_Graph_from_Fb_to_e_Raa_sts1016","",100,1.95,9.15);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->SetMinimum(0.4222646);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->SetMaximum(1.205391);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->SetDirectory(0);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_from_Fb_to_e_Raa_sts1016->SetLineColor(ci);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetXaxis()->SetLabelFont(42);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetXaxis()->SetTitleFont(42);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetYaxis()->SetLabelFont(42);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetYaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetYaxis()->SetTitleFont(42);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetZaxis()->SetLabelFont(42);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fb_to_e_Raa_sts1016->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_from_Fb_to_e_Raa_sts1016);
   
   gre->Draw("pe");
   TLine *line = new TLine(0,1,10,1);
   line->SetLineColor(4);
   line->SetLineStyle(7);
   line->SetLineWidth(2);
   line->Draw();
   TLatex *   tex = new TLatex(0.18,0.82,"STAR Au+Au@#sqrt{s_{NN}}=200 GeV");
tex->SetNDC();
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.18,0.75,"0-80% |#eta|<0.7");
tex->SetNDC();
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.65,0.65,0.76,0.95,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("Fb_to_e_Raa_sts","B #rightarrow e xiaozhi","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Fc_to_e_Raa_sts","D #rightarrow e xiaozhi","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph1","0-80% B #rightarrow e Duke Model","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(3);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph0","0-80% D #rightarrow e Duke Model","l");
   entry->SetLineColor(2);
   entry->SetLineStyle(3);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   
   leg = new TLegend(0.2,0.15,0.35,0.35,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("doubleRatio","B #rightarrow e kunsu","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(3);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("doubleRatioc","D #rightarrow e kunsu","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(6);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   leg->Draw();
   pad1->Modified();
   c3->cd();
  
// ------------>Primitives in pad: pad2
   TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.4);
   pad2->Draw();
   pad2->cd();
   pad2->Range(-1.529412,-1.042857,10.23529,4.1);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetLeftMargin(0.13);
   pad2->SetRightMargin(0.02);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.3);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameBorderMode(0);
   
   TH2F *h2__6 = new TH2F("h2__6","",100,0,10,2,0.5,4.1);
   h2__6->SetStats(0);

   ci = TColor::GetColor("#000099");
   h2__6->SetLineColor(ci);
   h2__6->GetXaxis()->SetTitle("p_{T}^{e} (GeV/c)");
   h2__6->GetXaxis()->CenterTitle(true);
   h2__6->GetXaxis()->SetLabelFont(42);
   h2__6->GetXaxis()->SetLabelSize(0.08);
   h2__6->GetXaxis()->SetTitleSize(0.14);
   h2__6->GetXaxis()->SetTitleOffset(0.8);
   h2__6->GetXaxis()->SetTitleFont(42);
   h2__6->GetYaxis()->SetTitle("R_{AA}^{b #rightarrow e} / R_{AA}^{c #rightarrow e}");
   h2__6->GetYaxis()->CenterTitle(true);
   h2__6->GetYaxis()->SetNdivisions(6);
   h2__6->GetYaxis()->SetLabelFont(42);
   h2__6->GetYaxis()->SetLabelSize(0.08);
   h2__6->GetYaxis()->SetTitleSize(0.1);
   h2__6->GetYaxis()->SetTitleOffset(0.4);
   h2__6->GetYaxis()->SetTitleFont(42);
   h2__6->GetZaxis()->SetLabelFont(42);
   h2__6->GetZaxis()->SetLabelSize(0.035);
   h2__6->GetZaxis()->SetTitleSize(0.035);
   h2__6->GetZaxis()->SetTitleOffset(1);
   h2__6->GetZaxis()->SetTitleFont(42);
   h2__6->Draw("");
   
   Double_t Graph_from_Fb_to_e_sys_fx1017[4] = {
   3,
   4,
   5,
   7};
   Double_t Graph_from_Fb_to_e_sys_fy1017[4] = {
   1.642583,
   2.590507,
   1.758834,
   1.90152};
   Double_t Graph_from_Fb_to_e_sys_fex1017[4] = {
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t Graph_from_Fb_to_e_sys_fey1017[4] = {
   0.3883959,
   0.4676894,
   0.3451359,
   0.5009149};
   gre = new TGraphErrors(4,Graph_from_Fb_to_e_sys_fx1017,Graph_from_Fb_to_e_sys_fy1017,Graph_from_Fb_to_e_sys_fex1017,Graph_from_Fb_to_e_sys_fey1017);
   gre->SetName("Graph_from_Fb_to_e_sys");
   gre->SetTitle("");
   gre->SetFillColor(29);
   gre->SetLineColor(29);
   
   TH1F *Graph_Graph_Graph_from_Fb_to_e_sys10021017 = new TH1F("Graph_Graph_Graph_from_Fb_to_e_sys10021017","",100,2.48,7.52);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->SetMinimum(1.073786);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->SetMaximum(3.238597);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->SetDirectory(0);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->SetLineColor(ci);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetYaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_from_Fb_to_e_sys10021017->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph_from_Fb_to_e_sys10021017);
   
   gre->Draw("e2");
   Double_t xAxis5[5] = {2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *Fb_to_e_sts__7 = new TH1F("Fb_to_e_sts__7","",4, xAxis5);
   Fb_to_e_sts__7->SetBinContent(1,1.642583);
   Fb_to_e_sts__7->SetBinContent(2,2.590507);
   Fb_to_e_sts__7->SetBinContent(3,1.758834);
   Fb_to_e_sts__7->SetBinContent(4,1.90152);
   Fb_to_e_sts__7->SetBinError(1,0.3859958);
   Fb_to_e_sts__7->SetBinError(2,0.7727448);
   Fb_to_e_sts__7->SetBinError(3,0.7572908);
   Fb_to_e_sts__7->SetBinError(4,1.247071);
   Fb_to_e_sts__7->SetEntries(21.67329);
   Fb_to_e_sts__7->SetStats(0);
   Fb_to_e_sts__7->SetLineColor(4);
   Fb_to_e_sts__7->SetMarkerColor(4);
   Fb_to_e_sts__7->SetMarkerStyle(20);
   Fb_to_e_sts__7->SetMarkerSize(1.5);
   Fb_to_e_sts__7->GetXaxis()->SetLabelFont(42);
   Fb_to_e_sts__7->GetXaxis()->SetLabelSize(0.035);
   Fb_to_e_sts__7->GetXaxis()->SetTitleSize(0.06);
   Fb_to_e_sts__7->GetXaxis()->SetTitleOffset(1);
   Fb_to_e_sts__7->GetXaxis()->SetTitleFont(42);
   Fb_to_e_sts__7->GetYaxis()->SetLabelFont(42);
   Fb_to_e_sts__7->GetYaxis()->SetLabelSize(0.035);
   Fb_to_e_sts__7->GetYaxis()->SetTitleSize(0.06);
   Fb_to_e_sts__7->GetYaxis()->SetTitleOffset(1);
   Fb_to_e_sts__7->GetYaxis()->SetTitleFont(42);
   Fb_to_e_sts__7->GetZaxis()->SetLabelFont(42);
   Fb_to_e_sts__7->GetZaxis()->SetLabelSize(0.035);
   Fb_to_e_sts__7->GetZaxis()->SetTitleSize(0.035);
   Fb_to_e_sts__7->GetZaxis()->SetTitleOffset(1);
   Fb_to_e_sts__7->GetZaxis()->SetTitleFont(42);
   Fb_to_e_sts__7->Draw("samePE");
   
   Double_t Graph_from_Fb_to_e_pp_sys_fx1018[4] = {
   3,
   4,
   5,
   7};
   Double_t Graph_from_Fb_to_e_pp_sys_fy1018[4] = {
   1.642583,
   2.590507,
   1.758834,
   1.90152};
   Double_t Graph_from_Fb_to_e_pp_sys_fex1018[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph_from_Fb_to_e_pp_sys_fey1018[4] = {
   0.0889067,
   0.05739284,
   0.1023627,
   0.08490502};
   gre = new TGraphErrors(4,Graph_from_Fb_to_e_pp_sys_fx1018,Graph_from_Fb_to_e_pp_sys_fy1018,Graph_from_Fb_to_e_pp_sys_fex1018,Graph_from_Fb_to_e_pp_sys_fey1018);
   gre->SetName("Graph_from_Fb_to_e_pp_sys");
   gre->SetTitle("");
   gre->SetLineColor(4);
   gre->Draw("p[],");
   pad2->Modified();
   c3->cd();
   c3->Modified();
   c3->cd();
   c3->SetSelected(c3);
}
