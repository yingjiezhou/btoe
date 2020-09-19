{
//========= Macro generated from object: Graph_from_Fb_to_Raa_e_sys/
//========= by ROOT version6.16/00
   
   Double_t Graph_from_Fb_to_Raa_e_sys_fx1004[4] = {
   3.05,
   4.05,
   5.05,
   7.05};
   Double_t Graph_from_Fb_to_Raa_e_sys_fy1004[4] = {
   0.935712,
   0.747994,
   0.662946,
   0.733945};
   Double_t Graph_from_Fb_to_Raa_e_sys_fex1004[4] = {
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t Graph_from_Fb_to_Raa_e_sys_fey1004[4] = {
   0.250849,
   0.145696,
   0.141428,
   0.224363};
   gre = new TGraphErrors(4,Graph_from_Fb_to_Raa_e_sys_fx1004,Graph_from_Fb_to_Raa_e_sys_fy1004,Graph_from_Fb_to_Raa_e_sys_fex1004,Graph_from_Fb_to_Raa_e_sys_fey1004);
   gre->SetName("Graph_from_Fb_to_Raa_e_sys");
   gre->SetTitle("");
   gre->SetFillColor(40);
   gre->SetLineColor(40);
   
   TH1F *Graph_Graph_from_Fb_to_Raa_e_sys1004 = new TH1F("Graph_Graph_from_Fb_to_Raa_e_sys1004","",100,2.53,7.57);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->SetMinimum(0.441884);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->SetMaximum(1.25426);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->SetDirectory(0);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_from_Fb_to_Raa_e_sys1004->SetLineColor(ci);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetXaxis()->SetLabelFont(42);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetXaxis()->SetTitleFont(42);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetYaxis()->SetLabelFont(42);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetYaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetYaxis()->SetTitleFont(42);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetZaxis()->SetLabelFont(42);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fb_to_Raa_e_sys1004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_from_Fb_to_Raa_e_sys1004);
   
   gre->Draw("");
}
