void Real_err()
{
//=========Macro generated from canvas: c2/Real. Errors
//=========  (Sun Sep 29 17:22:36 2019) by ROOT version 6.16/00
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
   Double_t xAxis1[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *er__1 = new TH1F("er__1","er",9, xAxis1);
   er__1->SetBinContent(5,0.1791102);
   er__1->SetBinContent(6,0.1641062);
   er__1->SetBinContent(7,0.3747286);
   er__1->SetBinContent(8,0.4367409);
   er__1->SetMinimum(0);
   er__1->SetMaximum(0.16);
   er__1->SetEntries(4);
   er__1->SetStats(0);
   er__1->SetLineWidth(2);
   er__1->SetMarkerStyle(20);
   er__1->GetXaxis()->SetNdivisions(505);
   er__1->GetXaxis()->SetLabelFont(132);
   er__1->GetXaxis()->SetLabelOffset(0.01);
   er__1->GetXaxis()->SetLabelSize(0.06);
   er__1->GetXaxis()->SetTitleSize(0.072);
   er__1->GetXaxis()->SetTitleOffset(0.95);
   er__1->GetXaxis()->SetTitleFont(132);
   er__1->GetYaxis()->SetLabelFont(132);
   er__1->GetYaxis()->SetLabelOffset(0.01);
   er__1->GetYaxis()->SetLabelSize(0.06);
   er__1->GetYaxis()->SetTitleSize(0.072);
   er__1->GetYaxis()->SetTitleOffset(0.95);
   er__1->GetYaxis()->SetTitleFont(132);
   er__1->GetZaxis()->SetLabelFont(132);
   er__1->GetZaxis()->SetLabelSize(0.06);
   er__1->GetZaxis()->SetTitleSize(0.072);
   er__1->GetZaxis()->SetTitleOffset(1.2);
   er__1->GetZaxis()->SetTitleFont(132);
   er__1->Draw("");
   Double_t xAxis2[10] = {0.6, 1, 1.2, 1.5, 2, 2.5, 3.5, 4.5, 5.5, 8.5}; 
   
   TH1F *er_ht__2 = new TH1F("er_ht__2","er_ht",9, xAxis2);
   er_ht__2->SetBinContent(6,0.2345942);
   er_ht__2->SetBinContent(7,0.4669099);
   er_ht__2->SetBinContent(8,0.2643711);
   er_ht__2->SetEntries(3);
   er_ht__2->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   er_ht__2->SetLineColor(ci);
   er_ht__2->SetLineWidth(2);
   er_ht__2->SetMarkerStyle(20);
   er_ht__2->GetXaxis()->SetNdivisions(505);
   er_ht__2->GetXaxis()->SetLabelFont(132);
   er_ht__2->GetXaxis()->SetLabelOffset(0.01);
   er_ht__2->GetXaxis()->SetLabelSize(0.06);
   er_ht__2->GetXaxis()->SetTitleSize(0.072);
   er_ht__2->GetXaxis()->SetTitleOffset(0.95);
   er_ht__2->GetXaxis()->SetTitleFont(132);
   er_ht__2->GetYaxis()->SetLabelFont(132);
   er_ht__2->GetYaxis()->SetLabelOffset(0.01);
   er_ht__2->GetYaxis()->SetLabelSize(0.06);
   er_ht__2->GetYaxis()->SetTitleSize(0.072);
   er_ht__2->GetYaxis()->SetTitleOffset(0.95);
   er_ht__2->GetYaxis()->SetTitleFont(132);
   er_ht__2->GetZaxis()->SetLabelFont(132);
   er_ht__2->GetZaxis()->SetLabelSize(0.06);
   er_ht__2->GetZaxis()->SetTitleSize(0.072);
   er_ht__2->GetZaxis()->SetTitleOffset(1.2);
   er_ht__2->GetZaxis()->SetTitleFont(132);
   er_ht__2->Draw("same");
   
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
