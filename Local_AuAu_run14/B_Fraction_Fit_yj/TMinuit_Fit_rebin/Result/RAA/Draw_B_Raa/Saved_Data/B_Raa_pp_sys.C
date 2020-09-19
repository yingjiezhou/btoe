{
//========= Macro generated from object: Graph_from_Fb_to_Raa_e_pp_sys/
//========= by ROOT version6.16/00
   
   Double_t Graph_from_Fb_to_Raa_e_pp_sys_fx1005[4] = {
   3.05,
   4.05,
   5.05,
   7.05};
   Double_t Graph_from_Fb_to_Raa_e_pp_sys_fy1005[4] = {
   0.935712,
   0.747994,
   0.662946,
   0.733945};
   Double_t Graph_from_Fb_to_Raa_e_pp_sys_fex1005[4] = {
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t Graph_from_Fb_to_Raa_e_pp_sys_fey1005[4] = {
   0.15607,
   0.198767,
   0.271574,
   0.219974};
   gre = new TGraphErrors(4,Graph_from_Fb_to_Raa_e_pp_sys_fx1005,Graph_from_Fb_to_Raa_e_pp_sys_fy1005,Graph_from_Fb_to_Raa_e_pp_sys_fex1005,Graph_from_Fb_to_Raa_e_pp_sys_fey1005);
   gre->SetName("Graph_from_Fb_to_Raa_e_pp_sys");
   gre->SetTitle("");
   gre->Draw("");
}
