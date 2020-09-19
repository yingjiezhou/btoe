void Real_err()
{
//=========Macro generated from canvas: c2/Real. Errors
//=========  (Mon Sep 30 09:05:16 2019) by ROOT version 6.16/00
   TCanvas *c2 = new TCanvas("c2", "Real. Errors",10,70,700,475);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c2->Range(-0.7654321,-0.03240506,8.987654,0.1701266);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetTickx(1);
   c2->SetTicky(1);
   c2->SetLeftMargin(0.14);
   c2->SetRightMargin(0.05);
   c2->SetTopMargin(0.05);
   c2->SetBottomMargin(0.16);
   c2->SetFrameLineWidth(2);
   c2->SetFrameBorderMode(0);
   c2->SetFrameLineWidth(2);
   c2->SetFrameBorderMode(0);
   Double_t xAxis7[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *er__7 = new TH1F("er__7","er",9, xAxis7);
   er__7->SetBinContent(5,0.02604339);
   er__7->SetBinContent(6,0.02091913);
   er__7->SetBinContent(7,0.02194204);
   er__7->SetBinContent(8,0.04049865);
   er__7->SetBinContent(9,0.1290588);
   er__7->SetMinimum(0);
   er__7->SetMaximum(0.16);
   er__7->SetEntries(5);
   er__7->SetStats(0);
   er__7->SetLineWidth(2);
   er__7->SetMarkerStyle(20);
   er__7->GetXaxis()->SetNdivisions(505);
   er__7->GetXaxis()->SetLabelFont(132);
   er__7->GetXaxis()->SetLabelOffset(0.01);
   er__7->GetXaxis()->SetLabelSize(0.06);
   er__7->GetXaxis()->SetTitleSize(0.072);
   er__7->GetXaxis()->SetTitleOffset(0.95);
   er__7->GetXaxis()->SetTitleFont(132);
   er__7->GetYaxis()->SetLabelFont(132);
   er__7->GetYaxis()->SetLabelOffset(0.01);
   er__7->GetYaxis()->SetLabelSize(0.06);
   er__7->GetYaxis()->SetTitleSize(0.072);
   er__7->GetYaxis()->SetTitleOffset(0.95);
   er__7->GetYaxis()->SetTitleFont(132);
   er__7->GetZaxis()->SetLabelFont(132);
   er__7->GetZaxis()->SetLabelSize(0.06);
   er__7->GetZaxis()->SetTitleSize(0.072);
   er__7->GetZaxis()->SetTitleOffset(1.2);
   er__7->GetZaxis()->SetTitleFont(132);
   er__7->Draw("");
   Double_t xAxis8[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *er_ht__8 = new TH1F("er_ht__8","er_ht",9, xAxis8);
   er_ht__8->SetBinContent(6,0.03371884);
   er_ht__8->SetBinContent(7,0.03115801);
   er_ht__8->SetBinContent(8,0.02406623);
   er_ht__8->SetBinContent(9,0.04109742);
   er_ht__8->SetEntries(4);
   er_ht__8->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   er_ht__8->SetLineColor(ci);
   er_ht__8->SetLineWidth(2);
   er_ht__8->SetMarkerStyle(20);
   er_ht__8->GetXaxis()->SetNdivisions(505);
   er_ht__8->GetXaxis()->SetLabelFont(132);
   er_ht__8->GetXaxis()->SetLabelOffset(0.01);
   er_ht__8->GetXaxis()->SetLabelSize(0.06);
   er_ht__8->GetXaxis()->SetTitleSize(0.072);
   er_ht__8->GetXaxis()->SetTitleOffset(0.95);
   er_ht__8->GetXaxis()->SetTitleFont(132);
   er_ht__8->GetYaxis()->SetLabelFont(132);
   er_ht__8->GetYaxis()->SetLabelOffset(0.01);
   er_ht__8->GetYaxis()->SetLabelSize(0.06);
   er_ht__8->GetYaxis()->SetTitleSize(0.072);
   er_ht__8->GetYaxis()->SetTitleOffset(0.95);
   er_ht__8->GetYaxis()->SetTitleFont(132);
   er_ht__8->GetZaxis()->SetLabelFont(132);
   er_ht__8->GetZaxis()->SetLabelSize(0.06);
   er_ht__8->GetZaxis()->SetTitleSize(0.072);
   er_ht__8->GetZaxis()->SetTitleOffset(1.2);
   er_ht__8->GetZaxis()->SetTitleFont(132);
   er_ht__8->Draw("same");
   
   TLegend *leg = new TLegend(0.2,0.5,0.5,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("er","Min. Bias Syst.","PLE");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("er_ht","High Tower Syst.","PLE");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
