{
//========= Macro generated from object: Graph_from_Fb_to_e_sys/
//========= by ROOT version6.16/00
   
   Double_t Graph_from_Fb_to_e_sys_fx1002[4] = {
   3,
   4,
   5,
   7};
   Double_t Graph_from_Fb_to_e_sys_fy1002[4] = {
   1.64258,
   2.59051,
   1.75883,
   1.90152};
   Double_t Graph_from_Fb_to_e_sys_fex1002[4] = {
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t Graph_from_Fb_to_e_sys_fey1002[4] = {
   0.388396,
   0.467689,
   0.345136,
   0.500915};
   gre = new TGraphErrors(4,Graph_from_Fb_to_e_sys_fx1002,Graph_from_Fb_to_e_sys_fy1002,Graph_from_Fb_to_e_sys_fex1002,Graph_from_Fb_to_e_sys_fey1002);
   gre->SetName("Graph_from_Fb_to_e_sys");
   gre->SetTitle("");
   gre->SetFillColor(29);
   gre->SetLineColor(29);
   
   TH1F *Graph_Graph_from_Fb_to_e_sys1002 = new TH1F("Graph_Graph_from_Fb_to_e_sys1002","",100,2.48,7.52);
   Graph_Graph_from_Fb_to_e_sys1002->SetMinimum(1.07379);
   Graph_Graph_from_Fb_to_e_sys1002->SetMaximum(3.2386);
   Graph_Graph_from_Fb_to_e_sys1002->SetDirectory(0);
   Graph_Graph_from_Fb_to_e_sys1002->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph_from_Fb_to_e_sys1002->SetLineColor(ci);
   Graph_Graph_from_Fb_to_e_sys1002->GetXaxis()->SetLabelFont(42);
   Graph_Graph_from_Fb_to_e_sys1002->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fb_to_e_sys1002->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fb_to_e_sys1002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fb_to_e_sys1002->GetXaxis()->SetTitleFont(42);
   Graph_Graph_from_Fb_to_e_sys1002->GetYaxis()->SetLabelFont(42);
   Graph_Graph_from_Fb_to_e_sys1002->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fb_to_e_sys1002->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fb_to_e_sys1002->GetYaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fb_to_e_sys1002->GetYaxis()->SetTitleFont(42);
   Graph_Graph_from_Fb_to_e_sys1002->GetZaxis()->SetLabelFont(42);
   Graph_Graph_from_Fb_to_e_sys1002->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fb_to_e_sys1002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_from_Fb_to_e_sys1002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fb_to_e_sys1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_from_Fb_to_e_sys1002);
   
   gre->Draw("");
}
