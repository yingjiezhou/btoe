{
//========= Macro generated from object: Graph_from_Fb_to_e_pp_sys/
//========= by ROOT version6.06/08
   
   Double_t Graph_from_Fb_to_e_pp_sys_fx1001[4] = {
   3,
   4,
   5,
   7};
   Double_t Graph_from_Fb_to_e_pp_sys_fy1001[4] = {
   2.23442,
   3.29332,
   2.24169,
   2.34991};
   Double_t Graph_from_Fb_to_e_pp_sys_fex1001[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph_from_Fb_to_e_pp_sys_fey1001[4] = {
   0.104633,
   0.0620117,
   0.111404,
   0.0905128};
   TGraphErrors *gre = new TGraphErrors(4,Graph_from_Fb_to_e_pp_sys_fx1001,Graph_from_Fb_to_e_pp_sys_fy1001,Graph_from_Fb_to_e_pp_sys_fex1001,Graph_from_Fb_to_e_pp_sys_fey1001);
   gre->SetName("Graph_from_Fb_to_e_pp_sys");
   gre->SetTitle("");
   gre->SetLineColor(4);
   gre->Draw("");
}
