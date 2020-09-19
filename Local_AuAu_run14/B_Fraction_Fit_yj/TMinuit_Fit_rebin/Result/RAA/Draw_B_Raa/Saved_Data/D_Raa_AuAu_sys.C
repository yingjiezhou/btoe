{
//========= Macro generated from object: Graph_from_Fc_to_e_Raa_sys/
//========= by ROOT version6.16/00
   
   Double_t Graph_from_Fc_to_e_Raa_sys_fx1007[4] = {
   3,
   4,
   5,
   7};
   Double_t Graph_from_Fc_to_e_Raa_sys_fy1007[4] = {
   0.569659,
   0.288744,
   0.376924,
   0.385978};
   Double_t Graph_from_Fc_to_e_Raa_sys_fex1007[4] = {
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t Graph_from_Fc_to_e_Raa_sys_fey1007[4] = {
   0.152716,
   0.0562422,
   0.0804102,
   0.117991};
   gre = new TGraphErrors(4,Graph_from_Fc_to_e_Raa_sys_fx1007,Graph_from_Fc_to_e_Raa_sys_fy1007,Graph_from_Fc_to_e_Raa_sys_fex1007,Graph_from_Fc_to_e_Raa_sys_fey1007);
   gre->SetName("Graph_from_Fc_to_e_Raa_sys");
   gre->SetTitle("");
   gre->SetFillColor(17);
   gre->SetLineColor(17);
   
   TH1F *Graph_Graph_from_Fc_to_e_Raa_sys1007 = new TH1F("Graph_Graph_from_Fc_to_e_Raa_sys1007","",100,2.48,7.52);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->SetMinimum(0.183515);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->SetMaximum(0.771363);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->SetDirectory(0);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_from_Fc_to_e_Raa_sys1007->SetLineColor(ci);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetXaxis()->SetLabelFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetXaxis()->SetTitleFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetYaxis()->SetLabelFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetYaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetYaxis()->SetTitleFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetZaxis()->SetLabelFont(42);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_from_Fc_to_e_Raa_sys1007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_from_Fc_to_e_Raa_sys1007);
   
   gre->Draw("");
}
