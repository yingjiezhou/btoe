void Likelihood_Response_Comparision_post()
{
//=========Macro generated from canvas: cp/post_DLL_comparsion
//=========  (Sun Aug 18 21:35:11 2019) by ROOT version 6.16/00
   TCanvas *cp = new TCanvas("cp", "post_DLL_comparsion",0,70,1280,730);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cp->Range(-1.432099,-0.06043916,1.654321,0.1744993);
   cp->SetFillColor(0);
   cp->SetBorderMode(0);
   cp->SetBorderSize(2);
   cp->SetTickx(1);
   cp->SetTicky(1);
   cp->SetLeftMargin(0.14);
   cp->SetRightMargin(0.05);
   cp->SetTopMargin(0.05);
   cp->SetBottomMargin(0.16);
   cp->SetFrameLineWidth(2);
   cp->SetFrameBorderMode(0);
   cp->SetFrameLineWidth(2);
   cp->SetFrameBorderMode(0);
   
   TH1F *DLL_p_post__3 = new TH1F("DLL_p_post__3","DLL_p_post",40,-1,1.5);
   DLL_p_post__3->SetBinContent(0,64.35854);
   DLL_p_post__3->SetBinContent(1,-0.005636109);
   DLL_p_post__3->SetBinContent(2,0.003198605);
   DLL_p_post__3->SetBinContent(3,0.002228698);
   DLL_p_post__3->SetBinContent(4,0.01066931);
   DLL_p_post__3->SetBinContent(5,0.02336599);
   DLL_p_post__3->SetBinContent(6,0.04417811);
   DLL_p_post__3->SetBinContent(7,0.1163596);
   DLL_p_post__3->SetBinContent(8,0.06723806);
   DLL_p_post__3->SetBinContent(9,0.1242872);
   DLL_p_post__3->SetBinContent(10,0.1216356);
   DLL_p_post__3->SetBinContent(11,0.1292343);
   DLL_p_post__3->SetBinContent(12,0.07664374);
   DLL_p_post__3->SetBinContent(13,0.03808762);
   DLL_p_post__3->SetBinContent(14,0.06402427);
   DLL_p_post__3->SetBinContent(15,0.04788033);
   DLL_p_post__3->SetBinContent(16,0.04130106);
   DLL_p_post__3->SetBinContent(17,0.03195594);
   DLL_p_post__3->SetBinContent(18,0.01195908);
   DLL_p_post__3->SetBinContent(19,0.01040247);
   DLL_p_post__3->SetBinContent(20,0.02448145);
   DLL_p_post__3->SetBinContent(21,0.004018856);
   DLL_p_post__3->SetBinContent(22,0.004975529);
   DLL_p_post__3->SetBinContent(23,0.004284303);
   DLL_p_post__3->SetBinContent(24,-0.001688328);
   DLL_p_post__3->SetBinContent(25,0.001279639);
   DLL_p_post__3->SetBinContent(26,-0.002083412);
   DLL_p_post__3->SetBinContent(27,0.003364474);
   DLL_p_post__3->SetBinContent(28,0.002939127);
   DLL_p_post__3->SetBinContent(29,-0.0007969993);
   DLL_p_post__3->SetBinContent(30,0.0004253878);
   DLL_p_post__3->SetBinContent(32,-0.0002138336);
   DLL_p_post__3->SetBinError(0,13.81121);
   DLL_p_post__3->SetBinError(1,0.008795604);
   DLL_p_post__3->SetBinError(2,0.005418536);
   DLL_p_post__3->SetBinError(3,0.005553074);
   DLL_p_post__3->SetBinError(4,0.01181608);
   DLL_p_post__3->SetBinError(5,0.01545591);
   DLL_p_post__3->SetBinError(6,0.01973265);
   DLL_p_post__3->SetBinError(7,0.02515003);
   DLL_p_post__3->SetBinError(8,0.01996923);
   DLL_p_post__3->SetBinError(9,0.02650927);
   DLL_p_post__3->SetBinError(10,0.02477647);
   DLL_p_post__3->SetBinError(11,0.02467993);
   DLL_p_post__3->SetBinError(12,0.02190581);
   DLL_p_post__3->SetBinError(13,0.01665286);
   DLL_p_post__3->SetBinError(14,0.01921277);
   DLL_p_post__3->SetBinError(15,0.01615402);
   DLL_p_post__3->SetBinError(16,0.01455464);
   DLL_p_post__3->SetBinError(17,0.01392453);
   DLL_p_post__3->SetBinError(18,0.01010818);
   DLL_p_post__3->SetBinError(19,0.007484512);
   DLL_p_post__3->SetBinError(20,0.01075378);
   DLL_p_post__3->SetBinError(21,0.006009184);
   DLL_p_post__3->SetBinError(22,0.004829993);
   DLL_p_post__3->SetBinError(23,0.005790928);
   DLL_p_post__3->SetBinError(24,0.001269566);
   DLL_p_post__3->SetBinError(25,0.004283845);
   DLL_p_post__3->SetBinError(26,0.001043308);
   DLL_p_post__3->SetBinError(27,0.005369256);
   DLL_p_post__3->SetBinError(28,0.003812943);
   DLL_p_post__3->SetBinError(29,0.0007241545);
   DLL_p_post__3->SetBinError(30,0.001445697);
   DLL_p_post__3->SetBinError(32,0.0002138336);
   DLL_p_post__3->SetEntries(2219);
   DLL_p_post__3->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   DLL_p_post__3->SetLineColor(ci);
   DLL_p_post__3->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   DLL_p_post__3->SetMarkerColor(ci);
   DLL_p_post__3->SetMarkerStyle(20);
   DLL_p_post__3->GetXaxis()->SetTitle("Likelihood Response");
   DLL_p_post__3->GetXaxis()->SetNdivisions(505);
   DLL_p_post__3->GetXaxis()->SetLabelFont(132);
   DLL_p_post__3->GetXaxis()->SetLabelOffset(0.01);
   DLL_p_post__3->GetXaxis()->SetLabelSize(0.06);
   DLL_p_post__3->GetXaxis()->SetTitleSize(0.072);
   DLL_p_post__3->GetXaxis()->SetTitleOffset(0.95);
   DLL_p_post__3->GetXaxis()->SetTitleFont(132);
   DLL_p_post__3->GetYaxis()->SetTitle("A. U.");
   DLL_p_post__3->GetYaxis()->SetLabelFont(132);
   DLL_p_post__3->GetYaxis()->SetLabelOffset(0.01);
   DLL_p_post__3->GetYaxis()->SetLabelSize(0.06);
   DLL_p_post__3->GetYaxis()->SetTitleSize(0.072);
   DLL_p_post__3->GetYaxis()->SetTitleOffset(0.95);
   DLL_p_post__3->GetYaxis()->SetTitleFont(132);
   DLL_p_post__3->GetZaxis()->SetLabelFont(132);
   DLL_p_post__3->GetZaxis()->SetLabelSize(0.06);
   DLL_p_post__3->GetZaxis()->SetTitleSize(0.072);
   DLL_p_post__3->GetZaxis()->SetTitleOffset(1.2);
   DLL_p_post__3->GetZaxis()->SetTitleFont(132);
   DLL_p_post__3->Draw("");
   
   TH1F *DLL_e_post__4 = new TH1F("DLL_e_post__4","DLL_e_post",40,-1,1.5);
   DLL_e_post__4->SetBinContent(17,0.0002747001);
   DLL_e_post__4->SetBinContent(18,0.003387968);
   DLL_e_post__4->SetBinContent(19,0.009797637);
   DLL_e_post__4->SetBinContent(20,0.03030858);
   DLL_e_post__4->SetBinContent(21,0.06281476);
   DLL_e_post__4->SetBinContent(22,0.08753777);
   DLL_e_post__4->SetBinContent(23,0.122791);
   DLL_e_post__4->SetBinContent(24,0.1422031);
   DLL_e_post__4->SetBinContent(25,0.1388151);
   DLL_e_post__4->SetBinContent(26,0.1309404);
   DLL_e_post__4->SetBinContent(27,0.1002655);
   DLL_e_post__4->SetBinContent(28,0.06977383);
   DLL_e_post__4->SetBinContent(29,0.04560022);
   DLL_e_post__4->SetBinContent(30,0.02499771);
   DLL_e_post__4->SetBinContent(31,0.01062174);
   DLL_e_post__4->SetBinContent(32,0.004486769);
   DLL_e_post__4->SetBinContent(33,0.003937368);
   DLL_e_post__4->SetBinContent(34,0.001190367);
   DLL_e_post__4->SetBinContent(35,0.002838568);
   DLL_e_post__4->SetBinContent(36,0.001739767);
   DLL_e_post__4->SetBinContent(37,0.002289168);
   DLL_e_post__4->SetBinContent(38,0.001922901);
   DLL_e_post__4->SetBinContent(39,0.000915667);
   DLL_e_post__4->SetBinContent(40,0.0005494002);
   DLL_e_post__4->SetBinContent(41,32);
   DLL_e_post__4->SetBinError(17,0.0001585982);
   DLL_e_post__4->SetBinError(18,0.0005569785);
   DLL_e_post__4->SetBinError(19,0.0009471734);
   DLL_e_post__4->SetBinError(20,0.00166591);
   DLL_e_post__4->SetBinError(21,0.002398279);
   DLL_e_post__4->SetBinError(22,0.002831174);
   DLL_e_post__4->SetBinError(23,0.003353142);
   DLL_e_post__4->SetBinError(24,0.003608472);
   DLL_e_post__4->SetBinError(25,0.003565227);
   DLL_e_post__4->SetBinError(26,0.003462626);
   DLL_e_post__4->SetBinError(27,0.003030014);
   DLL_e_post__4->SetBinError(28,0.002527639);
   DLL_e_post__4->SetBinError(29,0.002043395);
   DLL_e_post__4->SetBinError(30,0.00151293);
   DLL_e_post__4->SetBinError(31,0.0009862036);
   DLL_e_post__4->SetBinError(32,0.0006409669);
   DLL_e_post__4->SetBinError(33,0.000600443);
   DLL_e_post__4->SetBinError(34,0.0003301485);
   DLL_e_post__4->SetBinError(35,0.0005098218);
   DLL_e_post__4->SetBinError(36,0.00039913);
   DLL_e_post__4->SetBinError(37,0.0004578335);
   DLL_e_post__4->SetBinError(38,0.0004196114);
   DLL_e_post__4->SetBinError(39,0.0002895593);
   DLL_e_post__4->SetBinError(40,0.0002242917);
   DLL_e_post__4->SetBinError(41,5.656854);
   DLL_e_post__4->SetEntries(10961);
   DLL_e_post__4->SetStats(0);
   DLL_e_post__4->SetLineWidth(2);
   DLL_e_post__4->SetMarkerStyle(20);
   DLL_e_post__4->GetXaxis()->SetNdivisions(505);
   DLL_e_post__4->GetXaxis()->SetLabelFont(132);
   DLL_e_post__4->GetXaxis()->SetLabelOffset(0.01);
   DLL_e_post__4->GetXaxis()->SetLabelSize(0.06);
   DLL_e_post__4->GetXaxis()->SetTitleSize(0.072);
   DLL_e_post__4->GetXaxis()->SetTitleOffset(0.95);
   DLL_e_post__4->GetXaxis()->SetTitleFont(132);
   DLL_e_post__4->GetYaxis()->SetLabelFont(132);
   DLL_e_post__4->GetYaxis()->SetLabelOffset(0.01);
   DLL_e_post__4->GetYaxis()->SetLabelSize(0.06);
   DLL_e_post__4->GetYaxis()->SetTitleSize(0.072);
   DLL_e_post__4->GetYaxis()->SetTitleOffset(0.95);
   DLL_e_post__4->GetYaxis()->SetTitleFont(132);
   DLL_e_post__4->GetZaxis()->SetLabelFont(132);
   DLL_e_post__4->GetZaxis()->SetLabelSize(0.06);
   DLL_e_post__4->GetZaxis()->SetTitleSize(0.072);
   DLL_e_post__4->GetZaxis()->SetTitleOffset(1.2);
   DLL_e_post__4->GetZaxis()->SetTitleFont(132);
   DLL_e_post__4->Draw("same");
   
   TLegend *leg = new TLegend(0.7,0.7,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("DLL_e","Electrons","PEL");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("DLL_p","Pions","PEL");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   cp->Modified();
   cp->cd();
   cp->SetSelected(cp);
}
