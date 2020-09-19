{
//========= Macro generated from object: Graph_from_Npe_Raa_all_sys/
//========= by ROOT version6.16/00
   
   Double_t Graph_from_Npe_Raa_all_sys_fx1008[4] = {
   3,
   4,
   5,
   6.75};
   Double_t Graph_from_Npe_Raa_all_sys_fy1008[4] = {
   0.685687,
   0.480987,
   0.515541,
   0.567754};
   Double_t Graph_from_Npe_Raa_all_sys_fex1008[4] = {
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t Graph_from_Npe_Raa_all_sys_fey1008[4] = {
   0.0866199,
   0.0351662,
   0.0431478,
   0.0880557};
   gre = new TGraphErrors(4,Graph_from_Npe_Raa_all_sys_fx1008,Graph_from_Npe_Raa_all_sys_fy1008,Graph_from_Npe_Raa_all_sys_fex1008,Graph_from_Npe_Raa_all_sys_fey1008);
   gre->SetName("Graph_from_Npe_Raa_all_sys");
   gre->SetTitle("");
   gre->SetFillColor(41);
   gre->SetLineColor(41);
   gre->Draw("");
}
