{
//========= Macro generated from object: Graph_from_Fb_to_e_pp_sys/
//========= by ROOT version6.16/00
   
   Double_t Graph_from_Fb_to_e_pp_sys_fx1001[4] = {
   3,
   4,
   5,
   7};
   Double_t Graph_from_Fb_to_e_pp_sys_fy1001[4] = {
   1.64258,
   2.59051,
   1.75883,
   1.90152};
   Double_t Graph_from_Fb_to_e_pp_sys_fex1001[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph_from_Fb_to_e_pp_sys_fey1001[4] = {
   0.0889067,
   0.0573928,
   0.102363,
   0.084905};
   TGraphErrors *gre = new TGraphErrors(4,Graph_from_Fb_to_e_pp_sys_fx1001,Graph_from_Fb_to_e_pp_sys_fy1001,Graph_from_Fb_to_e_pp_sys_fex1001,Graph_from_Fb_to_e_pp_sys_fey1001);
   gre->SetName("Graph_from_Fb_to_e_pp_sys");
   gre->SetTitle("");
   gre->SetLineColor(4);
   gre->Draw("");
}
