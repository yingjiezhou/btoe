void PIDe_Pt_4.pdf()
{
//=========Macro generated from canvas: c1/full fit
//=========  (Wed Aug 14 12:04:36 2019) by ROOT version 6.16/00
   TCanvas *c1 = new TCanvas("c1", "full fit",10,70,700,475);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.14);
   c1->SetRightMargin(0.05);
   c1->SetTopMargin(0.05);
   c1->SetBottomMargin(0.16);
   c1->SetFrameLineWidth(2);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "pad1",0,0,1,1);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-13.0963,-1.712193,6.162963,8.989013);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLogy();
   pad1->SetTickx(1);
   pad1->SetTicky(1);
   pad1->SetLeftMargin(0.14);
   pad1->SetRightMargin(0.05);
   pad1->SetTopMargin(0.08);
   pad1->SetBottomMargin(0.16);
   pad1->SetFrameLineWidth(2);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameLineWidth(2);
   pad1->SetFrameBorderMode(0);
   
   TH1D *frame_7f8af4b44950__1 = new TH1D("frame_7f8af4b44950__1","",100,-10.4,5.2);
   frame_7f8af4b44950__1->SetBinContent(1,1.426341e+07);
   frame_7f8af4b44950__1->SetMinimum(1);
   frame_7f8af4b44950__1->SetMaximum(1.358052e+08);
   frame_7f8af4b44950__1->SetEntries(1);
   frame_7f8af4b44950__1->SetDirectory(0);
   frame_7f8af4b44950__1->SetStats(0);
   frame_7f8af4b44950__1->SetLineWidth(2);
   frame_7f8af4b44950__1->SetMarkerStyle(20);
   frame_7f8af4b44950__1->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7f8af4b44950__1->GetXaxis()->SetNdivisions(505);
   frame_7f8af4b44950__1->GetXaxis()->SetLabelFont(132);
   frame_7f8af4b44950__1->GetXaxis()->SetLabelOffset(0.01);
   frame_7f8af4b44950__1->GetXaxis()->SetLabelSize(0.06);
   frame_7f8af4b44950__1->GetXaxis()->SetTitleSize(0.072);
   frame_7f8af4b44950__1->GetXaxis()->SetTitleOffset(0.95);
   frame_7f8af4b44950__1->GetXaxis()->SetTitleFont(132);
   frame_7f8af4b44950__1->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7f8af4b44950__1->GetYaxis()->SetLabelFont(132);
   frame_7f8af4b44950__1->GetYaxis()->SetLabelOffset(0.01);
   frame_7f8af4b44950__1->GetYaxis()->SetLabelSize(0.06);
   frame_7f8af4b44950__1->GetYaxis()->SetTitleSize(0.1);
   frame_7f8af4b44950__1->GetYaxis()->SetTitleOffset(0.6);
   frame_7f8af4b44950__1->GetYaxis()->SetTitleFont(132);
   frame_7f8af4b44950__1->GetZaxis()->SetLabelFont(132);
   frame_7f8af4b44950__1->GetZaxis()->SetLabelSize(0.06);
   frame_7f8af4b44950__1->GetZaxis()->SetTitleSize(0.072);
   frame_7f8af4b44950__1->GetZaxis()->SetTitleOffset(1.2);
   frame_7f8af4b44950__1->GetZaxis()->SetTitleFont(132);
   frame_7f8af4b44950__1->Draw("FUNC");
   
   Double_t HistM_fx3001[30] = {
   -10.14,
   -9.62,
   -9.1,
   -8.58,
   -8.06,
   -7.54,
   -7.02,
   -6.5,
   -5.98,
   -5.46,
   -4.94,
   -4.42,
   -3.9,
   -3.38,
   -2.86,
   -2.34,
   -1.82,
   -1.3,
   -0.78,
   -0.26,
   0.26,
   0.78,
   1.3,
   1.82,
   2.34,
   2.86,
   3.38,
   3.9,
   4.42,
   4.94};
   Double_t HistM_fy3001[30] = {
   232,
   1832,
   10157,
   41283,
   148390,
   444989,
   1197206,
   2793895,
   5878196,
   9897681,
   1.313462e+07,
   1.358052e+07,
   1.127371e+07,
   7080514,
   3936094,
   1813247,
   761673,
   369530,
   264444,
   233549,
   180247,
   106170,
   50029,
   19261,
   6659,
   4633,
   4989,
   6275,
   6218,
   5231};
   Double_t HistM_felx3001[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26};
   Double_t HistM_fely3001[30] = {
   14.73975,
   42.30479,
   100.2832,
   202.6828,
   384.7146,
   666.5751,
   1093.669,
   1670.995,
   2423.999,
   3145.558,
   3623.672,
   3684.675,
   3357.135,
   2660.424,
   1983.459,
   1346.069,
   872.2389,
   607.39,
   513.7414,
   482.7693,
   424.0554,
   325.3378,
   223.1722,
   138.2849,
   81.10423,
   67.56798,
   70.13462,
   78.71648,
   78.35588,
   71.82738};
   Double_t HistM_fehx3001[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26};
   Double_t HistM_fehy3001[30] = {
   15.73975,
   43.30479,
   101.2832,
   203.6828,
   385.7146,
   667.5751,
   1094.669,
   1671.995,
   2424.999,
   3146.558,
   3624.672,
   3685.675,
   3358.135,
   2661.424,
   1984.459,
   1347.069,
   873.2389,
   608.39,
   514.7414,
   483.7693,
   425.0554,
   326.3378,
   224.1722,
   139.2849,
   82.10423,
   68.56798,
   71.13462,
   79.71648,
   79.35588,
   72.82738};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(30,HistM_fx3001,HistM_fy3001,HistM_felx3001,HistM_fehx3001,HistM_fely3001,HistM_fehy3001);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   
   TH1F *Graph_HistM3001 = new TH1F("Graph_HistM3001","Histogram of dataHist_plot__PID",100,-11.96,6.76);
   Graph_HistM3001->SetMinimum(195.5342);
   Graph_HistM3001->SetMaximum(1.49426e+07);
   Graph_HistM3001->SetDirectory(0);
   Graph_HistM3001->SetStats(0);
   Graph_HistM3001->SetLineWidth(2);
   Graph_HistM3001->SetMarkerStyle(20);
   Graph_HistM3001->GetXaxis()->SetNdivisions(505);
   Graph_HistM3001->GetXaxis()->SetLabelFont(132);
   Graph_HistM3001->GetXaxis()->SetLabelOffset(0.01);
   Graph_HistM3001->GetXaxis()->SetLabelSize(0.06);
   Graph_HistM3001->GetXaxis()->SetTitleSize(0.072);
   Graph_HistM3001->GetXaxis()->SetTitleOffset(0.95);
   Graph_HistM3001->GetXaxis()->SetTitleFont(132);
   Graph_HistM3001->GetYaxis()->SetLabelFont(132);
   Graph_HistM3001->GetYaxis()->SetLabelOffset(0.01);
   Graph_HistM3001->GetYaxis()->SetLabelSize(0.06);
   Graph_HistM3001->GetYaxis()->SetTitleSize(0.072);
   Graph_HistM3001->GetYaxis()->SetTitleOffset(0.95);
   Graph_HistM3001->GetYaxis()->SetTitleFont(132);
   Graph_HistM3001->GetZaxis()->SetLabelFont(132);
   Graph_HistM3001->GetZaxis()->SetLabelSize(0.06);
   Graph_HistM3001->GetZaxis()->SetTitleSize(0.072);
   Graph_HistM3001->GetZaxis()->SetTitleOffset(1.2);
   Graph_HistM3001->GetZaxis()->SetTitleFont(132);
   grae->SetHistogram(Graph_HistM3001);
   
   grae->Draw("p");
   
   Double_t PID_Curve_fx1[116] = {
   -10,
   -9.85,
   -9.7,
   -9.55,
   -9.4,
   -9.25,
   -9.1,
   -8.95,
   -8.8,
   -8.65,
   -8.5,
   -8.35,
   -8.2,
   -8.05,
   -7.9,
   -7.75,
   -7.6,
   -7.45,
   -7.3,
   -7.15,
   -7,
   -6.925,
   -6.85,
   -6.775,
   -6.7,
   -6.625,
   -6.55,
   -6.475,
   -6.4,
   -6.325,
   -6.25,
   -6.1,
   -5.95,
   -5.8,
   -5.65,
   -5.575,
   -5.5,
   -5.425,
   -5.35,
   -5.275,
   -5.2,
   -5.125,
   -5.05,
   -4.975,
   -4.9,
   -4.825,
   -4.75,
   -4.675,
   -4.6,
   -4.525,
   -4.45,
   -4.375,
   -4.3,
   -4.15,
   -4,
   -3.85,
   -3.7,
   -3.55,
   -3.4,
   -3.25,
   -3.1,
   -2.95,
   -2.8,
   -2.65,
   -2.5,
   -2.35,
   -2.2,
   -2.05,
   -1.9,
   -1.75,
   -1.6,
   -1.45,
   -1.3,
   -1.15,
   -1,
   -0.85,
   -0.7,
   -0.55,
   -0.4,
   -0.25,
   -0.1,
   0.05,
   0.2,
   0.35,
   0.5,
   0.65,
   0.8,
   0.95,
   1.1,
   1.25,
   1.4,
   1.55,
   1.7,
   1.85,
   2,
   2.15,
   2.3,
   2.45,
   2.6,
   2.75,
   2.9,
   3.05,
   3.2,
   3.35,
   3.5,
   3.65,
   3.8,
   3.95,
   4.1,
   4.25,
   4.4,
   4.55,
   4.7,
   4.85,
   5,
   5};
   Double_t PID_Curve_fy1[116] = {
   150.8795,
   257.8349,
   434.8933,
   725.1519,
   1197.337,
   1961.091,
   3191.409,
   5167.27,
   8331.63,
   13382.26,
   21404.96,
   34061.48,
   53842.65,
   84390.67,
   130881.8,
   200440,
   302522.9,
   449189.8,
   655125.8,
   937278.8,
   1313963,
   1543488,
   1803328,
   2095363,
   2421158,
   2781865,
   3178124,
   3609963,
   4076715,
   4576927,
   5108297,
   6250802,
   7467846,
   8709955,
   9915399,
   1.048303e+07,
   1.101555e+07,
   1.150437e+07,
   1.194129e+07,
   1.231874e+07,
   1.263005e+07,
   1.286955e+07,
   1.303283e+07,
   1.311683e+07,
   1.312276e+07,
   1.30751e+07,
   1.29802e+07,
   1.283929e+07,
   1.265421e+07,
   1.242733e+07,
   1.216152e+07,
   1.186005e+07,
   1.152655e+07,
   1.07792e+07,
   9952110,
   9078068,
   8187675,
   7307592,
   6459448,
   5659425,
   4918425,
   4242660,
   3634496,
   3093390,
   2616771,
   2200805,
   1840973,
   1532485,
   1270525,
   1050384,
   867504.4,
   717481.2,
   596047.7,
   499067.3,
   422546.7,
   362674.9,
   315887,
   278944.2,
   249017.2,
   223757.6,
   201344.5,
   180494.4,
   160431.2,
   140817.7,
   121658.8,
   103188.1,
   85754.92,
   69724.45,
   55402.02,
   42985.92,
   32549.09,
   24045.01,
   17330.64,
   12198.52,
   8410.784,
   5729.427,
   3939.376,
   2862.39,
   2361.38,
   2335.768,
   2709.531,
   3414.768,
   4374.838,
   5491.874,
   6643.13,
   7688.669,
   8489.549,
   8931.9,
   8949.63,
   8538.314,
   7755.372,
   6706.218,
   5520.629,
   4326.445,
   3227.777,
   3227.777};
   TGraph *graph = new TGraph(116,PID_Curve_fx1,PID_Curve_fy1);
   graph->SetName("PID_Curve");
   graph->SetTitle("Projection of completePDF");
   graph->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_PID_Curve1 = new TH1F("Graph_PID_Curve1","Projection of completePDF",116,-11.5,6.5);
   Graph_PID_Curve1->SetMinimum(135.7915);
   Graph_PID_Curve1->SetMaximum(1.443502e+07);
   Graph_PID_Curve1->SetDirectory(0);
   Graph_PID_Curve1->SetStats(0);
   Graph_PID_Curve1->SetLineWidth(2);
   Graph_PID_Curve1->SetMarkerStyle(20);
   Graph_PID_Curve1->GetXaxis()->SetNdivisions(505);
   Graph_PID_Curve1->GetXaxis()->SetLabelFont(132);
   Graph_PID_Curve1->GetXaxis()->SetLabelOffset(0.01);
   Graph_PID_Curve1->GetXaxis()->SetLabelSize(0.06);
   Graph_PID_Curve1->GetXaxis()->SetTitleSize(0.072);
   Graph_PID_Curve1->GetXaxis()->SetTitleOffset(0.95);
   Graph_PID_Curve1->GetXaxis()->SetTitleFont(132);
   Graph_PID_Curve1->GetYaxis()->SetLabelFont(132);
   Graph_PID_Curve1->GetYaxis()->SetLabelOffset(0.01);
   Graph_PID_Curve1->GetYaxis()->SetLabelSize(0.06);
   Graph_PID_Curve1->GetYaxis()->SetTitleSize(0.072);
   Graph_PID_Curve1->GetYaxis()->SetTitleOffset(0.95);
   Graph_PID_Curve1->GetYaxis()->SetTitleFont(132);
   Graph_PID_Curve1->GetZaxis()->SetLabelFont(132);
   Graph_PID_Curve1->GetZaxis()->SetLabelSize(0.06);
   Graph_PID_Curve1->GetZaxis()->SetTitleSize(0.072);
   Graph_PID_Curve1->GetZaxis()->SetTitleOffset(1.2);
   Graph_PID_Curve1->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_PID_Curve1);
   
   graph->Draw("l");
   
   Double_t e_signal_fx2[123] = {
   -10,
   -9.85,
   -9.7,
   -9.55,
   -9.4,
   -9.25,
   -9.1,
   -8.95,
   -8.8,
   -8.65,
   -8.5,
   -8.35,
   -8.2,
   -8.05,
   -7.9,
   -7.75,
   -7.6,
   -7.45,
   -7.3,
   -7.15,
   -7,
   -6.85,
   -6.7,
   -6.55,
   -6.4,
   -6.25,
   -6.1,
   -5.95,
   -5.8,
   -5.65,
   -5.5,
   -5.35,
   -5.2,
   -5.05,
   -4.9,
   -4.75,
   -4.6,
   -4.45,
   -4.3,
   -4.15,
   -4,
   -3.85,
   -3.7,
   -3.55,
   -3.4,
   -3.25,
   -3.1,
   -2.95,
   -2.8,
   -2.65,
   -2.5,
   -2.35,
   -2.275,
   -2.2,
   -2.125,
   -2.05,
   -1.975,
   -1.9,
   -1.825,
   -1.75,
   -1.675,
   -1.6,
   -1.525,
   -1.45,
   -1.3,
   -1.15,
   -1,
   -0.85,
   -0.775,
   -0.7,
   -0.625,
   -0.55,
   -0.475,
   -0.4,
   -0.325,
   -0.25,
   -0.175,
   -0.1,
   -0.025,
   0.05,
   0.125,
   0.2,
   0.275,
   0.35,
   0.425,
   0.5,
   0.65,
   0.8,
   0.95,
   1.025,
   1.1,
   1.175,
   1.25,
   1.325,
   1.4,
   1.475,
   1.55,
   1.625,
   1.7,
   1.775,
   1.85,
   2,
   2.15,
   2.3,
   2.45,
   2.6,
   2.75,
   2.9,
   3.05,
   3.2,
   3.35,
   3.5,
   3.65,
   3.8,
   3.95,
   4.1,
   4.25,
   4.4,
   4.55,
   4.7,
   4.85,
   5,
   5};
   Double_t e_signal_fy2[123] = {
   3.095994e-20,
   1.737222e-19,
   9.491951e-19,
   5.050104e-18,
   2.616315e-17,
   1.319849e-16,
   6.483411e-16,
   3.101184e-15,
   1.444429e-14,
   6.551031e-14,
   2.89313e-13,
   1.244145e-12,
   5.209772e-12,
   2.124277e-11,
   8.434291e-11,
   3.260849e-10,
   1.227602e-09,
   4.500172e-09,
   1.60637e-08,
   5.583502e-08,
   1.889786e-07,
   6.22821e-07,
   1.998751e-06,
   6.245957e-06,
   1.90057e-05,
   5.631366e-05,
   0.0001624756,
   0.0004564651,
   0.001248739,
   0.003326446,
   0.008628476,
   0.02179377,
   0.05360134,
   0.12837,
   0.2993617,
   0.6797882,
   1.503128,
   3.236405,
   6.785387,
   13.85259,
   27.538,
   53.30629,
   100.4776,
   184.4187,
   329.5985,
   573.6017,
   972.0314,
   1603.965,
   2577.237,
   4032.354,
   6143.383,
   9113.838,
   10990.44,
   13165.58,
   15666.64,
   18519.24,
   21746.11,
   25365.95,
   29392.19,
   33831.71,
   38683.63,
   43938.13,
   49575.5,
   55565.33,
   68424.41,
   82047.04,
   95798.69,
   108918.3,
   114984.3,
   120583.3,
   125616.6,
   129992.5,
   133628.9,
   136456.4,
   138419.9,
   139480.8,
   139618,
   138828.8,
   137128.9,
   134551.9,
   131147.9,
   126982.7,
   122134.6,
   116692.8,
   110754.3,
   104421.1,
   90986.62,
   77198.95,
   63780.81,
   57397.92,
   51311.35,
   45566.11,
   40195.89,
   35223.5,
   30661.58,
   26513.55,
   22774.68,
   19433.36,
   16472.32,
   13869.88,
   11601.18,
   7955.987,
   5312.89,
   3454.717,
   2187.453,
   1348.683,
   809.7029,
   473.3543,
   269.4584,
   149.3626,
   80.6189,
   42.37177,
   21.68508,
   10.80663,
   5.244019,
   2.477896,
   1.14011,
   0.5108048,
   0.2228476,
   0.09466858,
   0.03916052,
   0.01577378,
   0.01577378};
   graph = new TGraph(123,e_signal_fx2,e_signal_fy2);
   graph->SetName("e_signal");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#339933");
   graph->SetLineColor(ci);
   graph->SetLineStyle(7);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_e_signal2 = new TH1F("Graph_e_signal2","Projection of completePDF",123,-11.5,6.5);
   Graph_e_signal2->SetMinimum(2.786394e-20);
   Graph_e_signal2->SetMaximum(153579.8);
   Graph_e_signal2->SetDirectory(0);
   Graph_e_signal2->SetStats(0);
   Graph_e_signal2->SetLineWidth(2);
   Graph_e_signal2->SetMarkerStyle(20);
   Graph_e_signal2->GetXaxis()->SetNdivisions(505);
   Graph_e_signal2->GetXaxis()->SetLabelFont(132);
   Graph_e_signal2->GetXaxis()->SetLabelOffset(0.01);
   Graph_e_signal2->GetXaxis()->SetLabelSize(0.06);
   Graph_e_signal2->GetXaxis()->SetTitleSize(0.072);
   Graph_e_signal2->GetXaxis()->SetTitleOffset(0.95);
   Graph_e_signal2->GetXaxis()->SetTitleFont(132);
   Graph_e_signal2->GetYaxis()->SetLabelFont(132);
   Graph_e_signal2->GetYaxis()->SetLabelOffset(0.01);
   Graph_e_signal2->GetYaxis()->SetLabelSize(0.06);
   Graph_e_signal2->GetYaxis()->SetTitleSize(0.072);
   Graph_e_signal2->GetYaxis()->SetTitleOffset(0.95);
   Graph_e_signal2->GetYaxis()->SetTitleFont(132);
   Graph_e_signal2->GetZaxis()->SetLabelFont(132);
   Graph_e_signal2->GetZaxis()->SetLabelSize(0.06);
   Graph_e_signal2->GetZaxis()->SetTitleSize(0.072);
   Graph_e_signal2->GetZaxis()->SetTitleOffset(1.2);
   Graph_e_signal2->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_e_signal2);
   
   graph->Draw("l");
   
   Double_t pi_signal_fx3[116] = {
   -10,
   -9.85,
   -9.7,
   -9.55,
   -9.4,
   -9.25,
   -9.1,
   -8.95,
   -8.8,
   -8.65,
   -8.5,
   -8.35,
   -8.2,
   -8.05,
   -7.9,
   -7.75,
   -7.6,
   -7.45,
   -7.3,
   -7.15,
   -7,
   -6.925,
   -6.85,
   -6.775,
   -6.7,
   -6.625,
   -6.55,
   -6.475,
   -6.4,
   -6.325,
   -6.25,
   -6.1,
   -5.95,
   -5.8,
   -5.65,
   -5.575,
   -5.5,
   -5.425,
   -5.35,
   -5.275,
   -5.2,
   -5.125,
   -5.05,
   -4.975,
   -4.9,
   -4.825,
   -4.75,
   -4.675,
   -4.6,
   -4.525,
   -4.45,
   -4.375,
   -4.3,
   -4.15,
   -4,
   -3.85,
   -3.7,
   -3.55,
   -3.4,
   -3.25,
   -3.1,
   -2.95,
   -2.8,
   -2.65,
   -2.5,
   -2.35,
   -2.2,
   -2.05,
   -1.9,
   -1.75,
   -1.6,
   -1.45,
   -1.3,
   -1.15,
   -1,
   -0.85,
   -0.7,
   -0.55,
   -0.4,
   -0.25,
   -0.1,
   0.05,
   0.2,
   0.35,
   0.5,
   0.65,
   0.8,
   0.95,
   1.1,
   1.25,
   1.4,
   1.55,
   1.7,
   1.85,
   2,
   2.15,
   2.3,
   2.45,
   2.6,
   2.75,
   2.9,
   3.05,
   3.2,
   3.35,
   3.5,
   3.65,
   3.8,
   3.95,
   4.1,
   4.25,
   4.4,
   4.55,
   4.7,
   4.85,
   5,
   5};
   Double_t pi_signal_fy3[116] = {
   9.774985,
   22.08113,
   48.71505,
   104.9573,
   220.8206,
   453.6439,
   909.9328,
   1781.941,
   3406.734,
   6357.935,
   11582.43,
   20595.04,
   35742.02,
   60537.51,
   100063.5,
   161402.3,
   254042.2,
   390160.7,
   584660.7,
   854809.3,
   1219334,
   1442872,
   1696873,
   1983286,
   2303745,
   2659467,
   3051159,
   3478912,
   3942111,
   4439357,
   4968389,
   6108227,
   7325194,
   8568796,
   9777115,
   1.034668e+07,
   1.088144e+07,
   1.13728e+07,
   1.181252e+07,
   1.219305e+07,
   1.250766e+07,
   1.275068e+07,
   1.291767e+07,
   1.300554e+07,
   1.301548e+07,
   1.297194e+07,
   1.288125e+07,
   1.274463e+07,
   1.256388e+07,
   1.234134e+07,
   1.207986e+07,
   1.178271e+07,
   1.145348e+07,
   1.071446e+07,
   9895318,
   9028731,
   8145214,
   7271362,
   6428753,
   5633528,
   4896545,
   4223967,
   3618091,
   3078280,
   2601843,
   2184793,
   1822446,
   1509840,
   1242017,
   1014182,
   821796.9,
   660608.1,
   526666.3,
   416327.1,
   326250.9,
   253403.6,
   195055.6,
   148779.2,
   112441.9,
   84195.75,
   62460.92,
   45905.94,
   33424.26,
   24109.07,
   17227.41,
   12194.88,
   8551.67,
   5940.719,
   4088.282,
   2787.123,
   1882.28,
   1259.289,
   834.6012,
   547.9556,
   356.3891,
   229.6233,
   146.5616,
   92.6695,
   58.04517,
   36.01704,
   22.13922,
   13.48123,
   8.132216,
   4.859606,
   2.876774,
   1.68703,
   0.9800601,
   0.5640208,
   0.3215511,
   0.1816007,
   0.1016009,
   0.0563106,
   0.03091686,
   0.01681563,
   0.009060318,
   0.009060318};
   graph = new TGraph(116,pi_signal_fx3,pi_signal_fy3);
   graph->SetName("pi_signal");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(6);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_pi_signal3 = new TH1F("Graph_pi_signal3","Projection of completePDF",116,-11.5,6.5);
   Graph_pi_signal3->SetMinimum(0.008154286);
   Graph_pi_signal3->SetMaximum(1.431702e+07);
   Graph_pi_signal3->SetDirectory(0);
   Graph_pi_signal3->SetStats(0);
   Graph_pi_signal3->SetLineWidth(2);
   Graph_pi_signal3->SetMarkerStyle(20);
   Graph_pi_signal3->GetXaxis()->SetNdivisions(505);
   Graph_pi_signal3->GetXaxis()->SetLabelFont(132);
   Graph_pi_signal3->GetXaxis()->SetLabelOffset(0.01);
   Graph_pi_signal3->GetXaxis()->SetLabelSize(0.06);
   Graph_pi_signal3->GetXaxis()->SetTitleSize(0.072);
   Graph_pi_signal3->GetXaxis()->SetTitleOffset(0.95);
   Graph_pi_signal3->GetXaxis()->SetTitleFont(132);
   Graph_pi_signal3->GetYaxis()->SetLabelFont(132);
   Graph_pi_signal3->GetYaxis()->SetLabelOffset(0.01);
   Graph_pi_signal3->GetYaxis()->SetLabelSize(0.06);
   Graph_pi_signal3->GetYaxis()->SetTitleSize(0.072);
   Graph_pi_signal3->GetYaxis()->SetTitleOffset(0.95);
   Graph_pi_signal3->GetYaxis()->SetTitleFont(132);
   Graph_pi_signal3->GetZaxis()->SetLabelFont(132);
   Graph_pi_signal3->GetZaxis()->SetLabelSize(0.06);
   Graph_pi_signal3->GetZaxis()->SetTitleSize(0.072);
   Graph_pi_signal3->GetZaxis()->SetTitleOffset(1.2);
   Graph_pi_signal3->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_pi_signal3);
   
   graph->Draw("l");
   
   Double_t pi2_signal_fx4[127] = {
   -10,
   -9.85,
   -9.7,
   -9.55,
   -9.4,
   -9.25,
   -9.1,
   -8.95,
   -8.8,
   -8.65,
   -8.5,
   -8.35,
   -8.2,
   -8.05,
   -7.9,
   -7.75,
   -7.6,
   -7.45,
   -7.3,
   -7.15,
   -7,
   -6.85,
   -6.7,
   -6.55,
   -6.4,
   -6.25,
   -6.1,
   -5.95,
   -5.8,
   -5.65,
   -5.5,
   -5.35,
   -5.2,
   -5.05,
   -4.9,
   -4.75,
   -4.6,
   -4.45,
   -4.3,
   -4.15,
   -4,
   -3.85,
   -3.7,
   -3.55,
   -3.4,
   -3.25,
   -3.1,
   -2.95,
   -2.8,
   -2.65,
   -2.5,
   -2.35,
   -2.2,
   -2.05,
   -1.9,
   -1.75,
   -1.6,
   -1.45,
   -1.3,
   -1.15,
   -1,
   -0.85,
   -0.7,
   -0.55,
   -0.4,
   -0.25,
   -0.1,
   0.05,
   0.2,
   0.35,
   0.5,
   0.65,
   0.8,
   0.95,
   1.1,
   1.25,
   1.4,
   1.55,
   1.7,
   1.85,
   2,
   2.15,
   2.225,
   2.3,
   2.375,
   2.45,
   2.525,
   2.6,
   2.675,
   2.75,
   2.825,
   2.9,
   2.975,
   3.05,
   3.125,
   3.2,
   3.35,
   3.5,
   3.575,
   3.65,
   3.6875,
   3.725,
   3.7625,
   3.8,
   3.8375,
   3.875,
   3.9125,
   3.95,
   3.9875,
   4.025,
   4.0625,
   4.1,
   4.1375,
   4.175,
   4.2125,
   4.25,
   4.2875,
   4.325,
   4.3625,
   4.4,
   4.475,
   4.55,
   4.7,
   4.85,
   4.925,
   5,
   5};
   Double_t pi2_signal_fy4[127] = {
   2.748047e-90,
   2.676991e-88,
   2.482548e-86,
   2.191675e-84,
   1.841969e-82,
   1.473725e-80,
   1.122479e-78,
   8.138941e-77,
   5.618047e-75,
   3.691735e-73,
   2.309424e-71,
   1.375322e-69,
   7.797099e-68,
   4.208133e-66,
   2.16209e-64,
   1.057513e-62,
   4.924085e-61,
   2.182695e-59,
   9.210612e-58,
   3.700085e-56,
   1.41502e-54,
   5.151592e-53,
   1.785452e-51,
   5.890911e-50,
   1.85031e-48,
   5.532668e-47,
   1.574898e-45,
   4.26774e-44,
   1.100959e-42,
   2.703787e-41,
   6.321227e-40,
   1.406883e-38,
   2.980867e-37,
   6.012498e-36,
   1.154503e-34,
   2.110392e-33,
   3.672474e-32,
   6.083903e-31,
   9.594748e-30,
   1.440498e-28,
   2.058826e-27,
   2.801266e-26,
   3.628414e-25,
   4.474114e-24,
   5.252006e-23,
   5.869094e-22,
   6.243739e-21,
   6.323335e-20,
   6.096429e-19,
   5.595418e-18,
   4.888971e-17,
   4.066587e-16,
   3.220109e-15,
   2.427386e-14,
   1.741947e-13,
   1.190032e-12,
   7.739454e-12,
   4.791701e-11,
   2.82421e-10,
   1.584645e-09,
   8.464373e-09,
   4.304131e-08,
   2.08355e-07,
   9.601742e-07,
   4.212346e-06,
   1.759243e-05,
   6.99448e-05,
   0.0002647359,
   0.0009538894,
   0.003271983,
   0.01068444,
   0.03321394,
   0.09829168,
   0.2769114,
   0.7426648,
   1.89615,
   4.608718,
   10.66389,
   23.48976,
   49.25719,
   98.33052,
   186.868,
   252.8969,
   338.072,
   446.4078,
   582.2525,
   750.1495,
   954.6436,
   1200.029,
   1490.044,
   1827.525,
   2214.035,
   2649.492,
   3131.827,
   3656.704,
   4217.343,
   5406.395,
   6597.881,
   7155.471,
   7665.297,
   7897.155,
   8111.042,
   8305.137,
   8477.763,
   8627.4,
   8752.716,
   8852.582,
   8926.091,
   8972.572,
   8991.596,
   8982.989,
   8946.83,
   8883.452,
   8793.435,
   8677.6,
   8536.992,
   8372.871,
   8186.686,
   7980.059,
   7754.76,
   7255.803,
   6705.939,
   5520.503,
   4326.389,
   3759.97,
   3227.752,
   3227.752};
   graph = new TGraph(127,pi2_signal_fx4,pi2_signal_fy4);
   graph->SetName("pi2_signal");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);
   graph->SetLineColor(6);
   graph->SetLineStyle(6);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_pi2_signal4 = new TH1F("Graph_pi2_signal4","Projection of completePDF",127,-11.5,6.5);
   Graph_pi2_signal4->SetMinimum(2.473242e-90);
   Graph_pi2_signal4->SetMaximum(9890.756);
   Graph_pi2_signal4->SetDirectory(0);
   Graph_pi2_signal4->SetStats(0);
   Graph_pi2_signal4->SetLineWidth(2);
   Graph_pi2_signal4->SetMarkerStyle(20);
   Graph_pi2_signal4->GetXaxis()->SetNdivisions(505);
   Graph_pi2_signal4->GetXaxis()->SetLabelFont(132);
   Graph_pi2_signal4->GetXaxis()->SetLabelOffset(0.01);
   Graph_pi2_signal4->GetXaxis()->SetLabelSize(0.06);
   Graph_pi2_signal4->GetXaxis()->SetTitleSize(0.072);
   Graph_pi2_signal4->GetXaxis()->SetTitleOffset(0.95);
   Graph_pi2_signal4->GetXaxis()->SetTitleFont(132);
   Graph_pi2_signal4->GetYaxis()->SetLabelFont(132);
   Graph_pi2_signal4->GetYaxis()->SetLabelOffset(0.01);
   Graph_pi2_signal4->GetYaxis()->SetLabelSize(0.06);
   Graph_pi2_signal4->GetYaxis()->SetTitleSize(0.072);
   Graph_pi2_signal4->GetYaxis()->SetTitleOffset(0.95);
   Graph_pi2_signal4->GetYaxis()->SetTitleFont(132);
   Graph_pi2_signal4->GetZaxis()->SetLabelFont(132);
   Graph_pi2_signal4->GetZaxis()->SetLabelSize(0.06);
   Graph_pi2_signal4->GetZaxis()->SetTitleSize(0.072);
   Graph_pi2_signal4->GetZaxis()->SetTitleOffset(1.2);
   Graph_pi2_signal4->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_pi2_signal4);
   
   graph->Draw("l");
   
   Double_t k_signal_fx5[114] = {
   -10,
   -9.85,
   -9.7,
   -9.55,
   -9.4,
   -9.25,
   -9.1,
   -8.95,
   -8.8,
   -8.65,
   -8.5,
   -8.35,
   -8.2,
   -8.125,
   -8.05,
   -7.975,
   -7.9,
   -7.825,
   -7.75,
   -7.675,
   -7.6,
   -7.45,
   -7.3,
   -7.15,
   -7,
   -6.85,
   -6.7,
   -6.625,
   -6.55,
   -6.475,
   -6.4,
   -6.325,
   -6.25,
   -6.175,
   -6.1,
   -6.025,
   -5.95,
   -5.875,
   -5.8,
   -5.725,
   -5.65,
   -5.575,
   -5.5,
   -5.35,
   -5.2,
   -5.05,
   -4.9,
   -4.75,
   -4.6,
   -4.45,
   -4.3,
   -4.15,
   -4,
   -3.85,
   -3.7,
   -3.55,
   -3.4,
   -3.25,
   -3.1,
   -2.95,
   -2.8,
   -2.65,
   -2.5,
   -2.35,
   -2.2,
   -2.05,
   -1.9,
   -1.75,
   -1.6,
   -1.45,
   -1.3,
   -1.15,
   -1,
   -0.85,
   -0.7,
   -0.55,
   -0.4,
   -0.25,
   -0.1,
   0.05,
   0.2,
   0.35,
   0.5,
   0.65,
   0.8,
   0.95,
   1.1,
   1.25,
   1.4,
   1.55,
   1.7,
   1.85,
   2,
   2.15,
   2.3,
   2.45,
   2.6,
   2.75,
   2.9,
   3.05,
   3.2,
   3.35,
   3.5,
   3.65,
   3.8,
   3.95,
   4.1,
   4.25,
   4.4,
   4.55,
   4.7,
   4.85,
   5,
   5};
   Double_t k_signal_fy5[114] = {
   141.1045,
   235.7538,
   386.1782,
   620.1947,
   976.5163,
   1507.447,
   2281.476,
   3385.33,
   4924.897,
   7024.324,
   9822.524,
   13466.44,
   18100.63,
   20830.2,
   23853.16,
   27180.11,
   30818.34,
   34771.23,
   39037.65,
   43611.41,
   48480.75,
   59029.11,
   70465.14,
   82469.53,
   94628.93,
   106454.9,
   117413.6,
   122397.9,
   126964.5,
   131052,
   134603.9,
   137570.2,
   139908.4,
   141584.7,
   142574.4,
   142864.3,
   142652.1,
   142082.3,
   141159.3,
   139890,
   138283.9,
   136352.9,
   134111,
   128762,
   122388.8,
   115166.5,
   107285.5,
   98943.4,
   90336.46,
   81652.58,
   73064.65,
   64725.49,
   56764.12,
   49283.68,
   42360.68,
   36045.69,
   30365.07,
   25323.62,
   20907.78,
   17089.16,
   13828.15,
   11077.4,
   8785.012,
   6897.274,
   5360.967,
   4125.147,
   3142.435,
   2369.865,
   1769.342,
   1307.767,
   956.9286,
   693.2012,
   497.1297,
   352.948,
   248.0746,
   172.6173,
   118.9097,
   81.09246,
   54.74877,
   36.59307,
   24.2133,
   15.86133,
   10.28622,
   6.603935,
   4.197399,
   2.641121,
   1.645231,
   1.014603,
   0.6194353,
   0.3743918,
   0.2240203,
   0.1327024,
   0.07782176,
   0.04518079,
   0.02596792,
   0.0147758,
   0.008323301,
   0.004641632,
   0.002562574,
   0.001400595,
   0.0007578436,
   0.0004059542,
   0.0002152807,
   0.0001130222,
   5.874257e-05,
   3.022545e-05,
   1.539654e-05,
   7.764334e-06,
   3.876286e-06,
   1.915834e-06,
   9.374125e-07,
   4.540818e-07,
   2.177549e-07,
   2.177549e-07};
   graph = new TGraph(114,k_signal_fx5,k_signal_fy5);
   graph->SetName("k_signal");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#999933");
   graph->SetLineColor(ci);
   graph->SetLineStyle(6);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_k_signal5 = new TH1F("Graph_k_signal5","Projection of completePDF",114,-11.5,6.5);
   Graph_k_signal5->SetMinimum(1.959795e-07);
   Graph_k_signal5->SetMaximum(157150.7);
   Graph_k_signal5->SetDirectory(0);
   Graph_k_signal5->SetStats(0);
   Graph_k_signal5->SetLineWidth(2);
   Graph_k_signal5->SetMarkerStyle(20);
   Graph_k_signal5->GetXaxis()->SetNdivisions(505);
   Graph_k_signal5->GetXaxis()->SetLabelFont(132);
   Graph_k_signal5->GetXaxis()->SetLabelOffset(0.01);
   Graph_k_signal5->GetXaxis()->SetLabelSize(0.06);
   Graph_k_signal5->GetXaxis()->SetTitleSize(0.072);
   Graph_k_signal5->GetXaxis()->SetTitleOffset(0.95);
   Graph_k_signal5->GetXaxis()->SetTitleFont(132);
   Graph_k_signal5->GetYaxis()->SetLabelFont(132);
   Graph_k_signal5->GetYaxis()->SetLabelOffset(0.01);
   Graph_k_signal5->GetYaxis()->SetLabelSize(0.06);
   Graph_k_signal5->GetYaxis()->SetTitleSize(0.072);
   Graph_k_signal5->GetYaxis()->SetTitleOffset(0.95);
   Graph_k_signal5->GetYaxis()->SetTitleFont(132);
   Graph_k_signal5->GetZaxis()->SetLabelFont(132);
   Graph_k_signal5->GetZaxis()->SetLabelSize(0.06);
   Graph_k_signal5->GetZaxis()->SetTitleSize(0.072);
   Graph_k_signal5->GetZaxis()->SetTitleOffset(1.2);
   Graph_k_signal5->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_k_signal5);
   
   graph->Draw("l");
   
   Double_t HistM1_fx3002[30] = {
   -10.14,
   -9.62,
   -9.1,
   -8.58,
   -8.06,
   -7.54,
   -7.02,
   -6.5,
   -5.98,
   -5.46,
   -4.94,
   -4.42,
   -3.9,
   -3.38,
   -2.86,
   -2.34,
   -1.82,
   -1.3,
   -0.78,
   -0.26,
   0.26,
   0.78,
   1.3,
   1.82,
   2.34,
   2.86,
   3.38,
   3.9,
   4.42,
   4.94};
   Double_t HistM1_fy3002[30] = {
   0,
   0,
   10135,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   957,
   89417,
   204456,
   177882,
   106095,
   50029,
   19261,
   6659,
   4633,
   4989,
   6275,
   6218,
   5231};
   Double_t HistM1_felx3002[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26};
   Double_t HistM1_fely3002[30] = {
   0,
   0,
   100.174,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   30.43946,
   298.5272,
   451.6684,
   421.2609,
   325.2227,
   223.1722,
   138.2849,
   81.10423,
   67.56798,
   70.13462,
   78.71648,
   78.35588,
   71.82738};
   Double_t HistM1_fehx3002[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26};
   Double_t HistM1_fehy3002[30] = {
   1.147874,
   1.147874,
   101.174,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   1.147874,
   31.43946,
   299.5272,
   452.6684,
   422.2609,
   326.2227,
   224.1722,
   139.2849,
   82.10423,
   68.56798,
   71.13462,
   79.71648,
   79.35588,
   72.82738};
   grae = new TGraphAsymmErrors(30,HistM1_fx3002,HistM1_fy3002,HistM1_felx3002,HistM1_fehx3002,HistM1_fely3002,HistM1_fehy3002);
   grae->SetName("HistM1");
   grae->SetTitle("Histogram of dataHist1_plot__PID");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#cccccc");
   grae->SetLineColor(ci);
   grae->SetLineWidth(2);

   ci = TColor::GetColor("#cccccc");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(8);
   
   TH1F *Graph_HistM13002 = new TH1F("Graph_HistM13002","Histogram of dataHist1_plot__PID",100,-11.96,6.76);
   Graph_HistM13002->SetMinimum(225.3995);
   Graph_HistM13002->SetMaximum(225399.5);
   Graph_HistM13002->SetDirectory(0);
   Graph_HistM13002->SetStats(0);
   Graph_HistM13002->SetLineWidth(2);
   Graph_HistM13002->SetMarkerStyle(20);
   Graph_HistM13002->GetXaxis()->SetNdivisions(505);
   Graph_HistM13002->GetXaxis()->SetLabelFont(132);
   Graph_HistM13002->GetXaxis()->SetLabelOffset(0.01);
   Graph_HistM13002->GetXaxis()->SetLabelSize(0.06);
   Graph_HistM13002->GetXaxis()->SetTitleSize(0.072);
   Graph_HistM13002->GetXaxis()->SetTitleOffset(0.95);
   Graph_HistM13002->GetXaxis()->SetTitleFont(132);
   Graph_HistM13002->GetYaxis()->SetLabelFont(132);
   Graph_HistM13002->GetYaxis()->SetLabelOffset(0.01);
   Graph_HistM13002->GetYaxis()->SetLabelSize(0.06);
   Graph_HistM13002->GetYaxis()->SetTitleSize(0.072);
   Graph_HistM13002->GetYaxis()->SetTitleOffset(0.95);
   Graph_HistM13002->GetYaxis()->SetTitleFont(132);
   Graph_HistM13002->GetZaxis()->SetLabelFont(132);
   Graph_HistM13002->GetZaxis()->SetLabelSize(0.06);
   Graph_HistM13002->GetZaxis()->SetTitleSize(0.072);
   Graph_HistM13002->GetZaxis()->SetTitleOffset(1.2);
   Graph_HistM13002->GetZaxis()->SetTitleFont(132);
   grae->SetHistogram(Graph_HistM13002);
   
   grae->Draw("p");
   
   Double_t HistM_fx3003[30] = {
   -10.14,
   -9.62,
   -9.1,
   -8.58,
   -8.06,
   -7.54,
   -7.02,
   -6.5,
   -5.98,
   -5.46,
   -4.94,
   -4.42,
   -3.9,
   -3.38,
   -2.86,
   -2.34,
   -1.82,
   -1.3,
   -0.78,
   -0.26,
   0.26,
   0.78,
   1.3,
   1.82,
   2.34,
   2.86,
   3.38,
   3.9,
   4.42,
   4.94};
   Double_t HistM_fy3003[30] = {
   232,
   1832,
   10157,
   41283,
   148390,
   444989,
   1197206,
   2793895,
   5878196,
   9897681,
   1.313462e+07,
   1.358052e+07,
   1.127371e+07,
   7080514,
   3936094,
   1813247,
   761673,
   369530,
   264444,
   233549,
   180247,
   106170,
   50029,
   19261,
   6659,
   4633,
   4989,
   6275,
   6218,
   5231};
   Double_t HistM_felx3003[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26};
   Double_t HistM_fely3003[30] = {
   14.73975,
   42.30479,
   100.2832,
   202.6828,
   384.7146,
   666.5751,
   1093.669,
   1670.995,
   2423.999,
   3145.558,
   3623.672,
   3684.675,
   3357.135,
   2660.424,
   1983.459,
   1346.069,
   872.2389,
   607.39,
   513.7414,
   482.7693,
   424.0554,
   325.3378,
   223.1722,
   138.2849,
   81.10423,
   67.56798,
   70.13462,
   78.71648,
   78.35588,
   71.82738};
   Double_t HistM_fehx3003[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26};
   Double_t HistM_fehy3003[30] = {
   15.73975,
   43.30479,
   101.2832,
   203.6828,
   385.7146,
   667.5751,
   1094.669,
   1671.995,
   2424.999,
   3146.558,
   3624.672,
   3685.675,
   3358.135,
   2661.424,
   1984.459,
   1347.069,
   873.2389,
   608.39,
   514.7414,
   483.7693,
   425.0554,
   326.3378,
   224.1722,
   139.2849,
   82.10423,
   68.56798,
   71.13462,
   79.71648,
   79.35588,
   72.82738};
   grae = new TGraphAsymmErrors(30,HistM_fx3003,HistM_fy3003,HistM_felx3003,HistM_fehx3003,HistM_fely3003,HistM_fehy3003);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   
   TH1F *Graph_HistM3003 = new TH1F("Graph_HistM3003","Histogram of dataHist_plot__PID",100,-11.96,6.76);
   Graph_HistM3003->SetMinimum(195.5342);
   Graph_HistM3003->SetMaximum(1.49426e+07);
   Graph_HistM3003->SetDirectory(0);
   Graph_HistM3003->SetStats(0);
   Graph_HistM3003->SetLineWidth(2);
   Graph_HistM3003->SetMarkerStyle(20);
   Graph_HistM3003->GetXaxis()->SetNdivisions(505);
   Graph_HistM3003->GetXaxis()->SetLabelFont(132);
   Graph_HistM3003->GetXaxis()->SetLabelOffset(0.01);
   Graph_HistM3003->GetXaxis()->SetLabelSize(0.06);
   Graph_HistM3003->GetXaxis()->SetTitleSize(0.072);
   Graph_HistM3003->GetXaxis()->SetTitleOffset(0.95);
   Graph_HistM3003->GetXaxis()->SetTitleFont(132);
   Graph_HistM3003->GetYaxis()->SetLabelFont(132);
   Graph_HistM3003->GetYaxis()->SetLabelOffset(0.01);
   Graph_HistM3003->GetYaxis()->SetLabelSize(0.06);
   Graph_HistM3003->GetYaxis()->SetTitleSize(0.072);
   Graph_HistM3003->GetYaxis()->SetTitleOffset(0.95);
   Graph_HistM3003->GetYaxis()->SetTitleFont(132);
   Graph_HistM3003->GetZaxis()->SetLabelFont(132);
   Graph_HistM3003->GetZaxis()->SetLabelSize(0.06);
   Graph_HistM3003->GetZaxis()->SetTitleSize(0.072);
   Graph_HistM3003->GetZaxis()->SetTitleOffset(1.2);
   Graph_HistM3003->GetZaxis()->SetTitleFont(132);
   grae->SetHistogram(Graph_HistM3003);
   
   grae->Draw("p");
   
   TPaveText *pt = new TPaveText(0.62,0.7,0.88,0.88,"BRNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetLineWidth(2);
   pt->SetTextFont(132);
   pt->SetTextSize(0.07);
   TText *pt_LaTex = pt->AddText("#it{p}_{T} #in [1.5,2.0] GeV");
   pt->Draw();
   
   TH1D *frame_7f8af4b44950__2 = new TH1D("frame_7f8af4b44950__2","",100,-10.4,5.2);
   frame_7f8af4b44950__2->SetBinContent(1,1.426341e+07);
   frame_7f8af4b44950__2->SetMinimum(1);
   frame_7f8af4b44950__2->SetMaximum(1.358052e+08);
   frame_7f8af4b44950__2->SetEntries(1);
   frame_7f8af4b44950__2->SetDirectory(0);
   frame_7f8af4b44950__2->SetStats(0);
   frame_7f8af4b44950__2->SetLineWidth(2);
   frame_7f8af4b44950__2->SetMarkerStyle(20);
   frame_7f8af4b44950__2->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7f8af4b44950__2->GetXaxis()->SetNdivisions(505);
   frame_7f8af4b44950__2->GetXaxis()->SetLabelFont(132);
   frame_7f8af4b44950__2->GetXaxis()->SetLabelOffset(0.01);
   frame_7f8af4b44950__2->GetXaxis()->SetLabelSize(0.06);
   frame_7f8af4b44950__2->GetXaxis()->SetTitleSize(0.072);
   frame_7f8af4b44950__2->GetXaxis()->SetTitleOffset(0.95);
   frame_7f8af4b44950__2->GetXaxis()->SetTitleFont(132);
   frame_7f8af4b44950__2->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7f8af4b44950__2->GetYaxis()->SetLabelFont(132);
   frame_7f8af4b44950__2->GetYaxis()->SetLabelOffset(0.01);
   frame_7f8af4b44950__2->GetYaxis()->SetLabelSize(0.06);
   frame_7f8af4b44950__2->GetYaxis()->SetTitleSize(0.1);
   frame_7f8af4b44950__2->GetYaxis()->SetTitleOffset(0.6);
   frame_7f8af4b44950__2->GetYaxis()->SetTitleFont(132);
   frame_7f8af4b44950__2->GetZaxis()->SetLabelFont(132);
   frame_7f8af4b44950__2->GetZaxis()->SetLabelSize(0.06);
   frame_7f8af4b44950__2->GetZaxis()->SetTitleSize(0.072);
   frame_7f8af4b44950__2->GetZaxis()->SetTitleOffset(1.2);
   frame_7f8af4b44950__2->GetZaxis()->SetTitleFont(132);
   frame_7f8af4b44950__2->Draw("AXISSAME");
   
   TLegend *leg = new TLegend(0.18,0.65,0.35,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->Draw();
   pad1->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
