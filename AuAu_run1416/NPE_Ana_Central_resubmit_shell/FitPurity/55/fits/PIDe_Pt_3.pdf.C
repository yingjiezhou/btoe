void PIDe_Pt_3.pdf()
{
//=========Macro generated from canvas: c1/full fit
//=========  (Sun Aug 18 21:39:29 2019) by ROOT version 6.16/00
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
   pad1->Range(-13.0963,-1.477176,6.162963,7.755172);
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
   
   TH1D *frame_7fc9ef25e550__1 = new TH1D("frame_7fc9ef25e550__1","",100,-10.4,5.2);
   frame_7fc9ef25e550__1->SetBinContent(1,1094443);
   frame_7fc9ef25e550__1->SetMinimum(1);
   frame_7fc9ef25e550__1->SetMaximum(1.038926e+07);
   frame_7fc9ef25e550__1->SetEntries(2);
   frame_7fc9ef25e550__1->SetDirectory(0);
   frame_7fc9ef25e550__1->SetStats(0);
   frame_7fc9ef25e550__1->SetLineWidth(2);
   frame_7fc9ef25e550__1->SetMarkerStyle(20);
   frame_7fc9ef25e550__1->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fc9ef25e550__1->GetXaxis()->SetNdivisions(505);
   frame_7fc9ef25e550__1->GetXaxis()->SetLabelFont(132);
   frame_7fc9ef25e550__1->GetXaxis()->SetLabelOffset(0.01);
   frame_7fc9ef25e550__1->GetXaxis()->SetLabelSize(0.06);
   frame_7fc9ef25e550__1->GetXaxis()->SetTitleSize(0.072);
   frame_7fc9ef25e550__1->GetXaxis()->SetTitleOffset(0.95);
   frame_7fc9ef25e550__1->GetXaxis()->SetTitleFont(132);
   frame_7fc9ef25e550__1->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7fc9ef25e550__1->GetYaxis()->SetLabelFont(132);
   frame_7fc9ef25e550__1->GetYaxis()->SetLabelOffset(0.01);
   frame_7fc9ef25e550__1->GetYaxis()->SetLabelSize(0.06);
   frame_7fc9ef25e550__1->GetYaxis()->SetTitleSize(0.1);
   frame_7fc9ef25e550__1->GetYaxis()->SetTitleOffset(0.6);
   frame_7fc9ef25e550__1->GetYaxis()->SetTitleFont(132);
   frame_7fc9ef25e550__1->GetZaxis()->SetLabelFont(132);
   frame_7fc9ef25e550__1->GetZaxis()->SetLabelSize(0.06);
   frame_7fc9ef25e550__1->GetZaxis()->SetTitleSize(0.072);
   frame_7fc9ef25e550__1->GetZaxis()->SetTitleOffset(1.2);
   frame_7fc9ef25e550__1->GetZaxis()->SetTitleFont(132);
   frame_7fc9ef25e550__1->Draw("FUNC");
   
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
   2,
   28,
   220,
   1592,
   9109,
   38840,
   126792,
   317011,
   609292,
   898342,
   1038926,
   951234,
   708497,
   433126,
   226755,
   103609,
   43722,
   21563,
   15399,
   12617,
   9464,
   5652,
   2547,
   1032,
   535,
   555,
   799,
   810,
   802,
   629};
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
   1.291815,
   5.259711,
   14.34082,
   39.40301,
   94.94239,
   196.5793,
   355.579,
   562.5375,
   780.0717,
   947.3092,
   1018.777,
   974.8124,
   841.2228,
   657.6233,
   475.6883,
   321.3839,
   208.5987,
   146.3443,
   123.5937,
   111.8265,
   96.78438,
   74.68145,
   49.97029,
   31.62865,
   22.63547,
   23.06374,
   27.77101,
   27.96489,
   27.82402,
   24.58486};
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
   2.63786,
   6.354446,
   15.34082,
   40.40301,
   95.94239,
   197.5793,
   356.579,
   563.5375,
   781.0717,
   948.3092,
   1019.777,
   975.8124,
   842.2228,
   658.6233,
   476.6883,
   322.3839,
   209.5987,
   147.3443,
   124.5937,
   112.8265,
   97.78438,
   75.68145,
   50.97029,
   32.62865,
   23.63547,
   24.06374,
   28.77101,
   28.96489,
   28.82402,
   25.58486};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(30,HistM_fx3001,HistM_fy3001,HistM_felx3001,HistM_fehx3001,HistM_fely3001,HistM_fehy3001);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   
   TH1F *Graph_HistM3001 = new TH1F("Graph_HistM3001","Histogram of dataHist_plot__PID",100,-11.96,6.76);
   Graph_HistM3001->SetMinimum(0.6373669);
   Graph_HistM3001->SetMaximum(1143940);
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
   -4.225,
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
   5.009596,
   10.19052,
   20.29545,
   39.57376,
   75.5475,
   141.2,
   258.3743,
   462.8727,
   811.8385,
   1394.028,
   2343.503,
   3857,
   6214.728,
   9803.504,
   15139.99,
   22890.4,
   33881.55,
   49096.85,
   69650.35,
   96732.17,
   131521.1,
   152141.8,
   175063.4,
   200371.5,
   228123.5,
   258343.4,
   291016.9,
   326085.9,
   363445.3,
   444356.7,
   531857.9,
   623203.5,
   714881.5,
   802800.2,
   843980.8,
   882571.4,
   918035,
   949862.5,
   977584.4,
   1000783,
   1019102,
   1032255,
   1040037,
   1042327,
   1039662,
   1032492,
   1020917,
   1005097,
   985248.1,
   961636.5,
   934574.5,
   904411.5,
   871526.9,
   836321.8,
   760611.2,
   680604,
   599460.7,
   519979,
   444454.1,
   374605.7,
   311567.8,
   255930.3,
   207818.4,
   166992.1,
   132951.3,
   105034.5,
   82502.05,
   64600.96,
   50609.51,
   39864.21,
   31772.3,
   25814,
   21538.58,
   18557.57,
   16537.75,
   15195.46,
   14292.68,
   13635.01,
   13070.52,
   12488.69,
   11818.59,
   11025.4,
   10105.23,
   9078.341,
   7981.394,
   6859.432,
   5758.605,
   4720.27,
   3776.972,
   2950.437,
   2251.418,
   1680.98,
   1232.71,
   895.273,
   654.8673,
   497.2022,
   408.822,
   377.7243,
   393.3607,
   446.1997,
   527.0883,
   626.6608,
   735.0101,
   841.7599,
   936.5697,
   1009.986,
   1054.452,
   1065.234,
   1041.024,
   984.0617,
   899.7144,
   795.602,
   680.4403,
   562.8391,
   450.2742,
   450.2742};
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
   Graph_PID_Curve1->SetMinimum(4.508636);
   Graph_PID_Curve1->SetMaximum(1146559);
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
   
   Double_t e_signal_fx2[124] = {
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
   -2.425,
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
   -1.45,
   -1.3,
   -1.15,
   -1,
   -0.925,
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
   Double_t e_signal_fy2[124] = {
   1.057384e-19,
   5.36463e-19,
   2.653819e-18,
   1.280052e-17,
   6.020168e-17,
   2.760668e-16,
   1.234368e-15,
   5.381453e-15,
   2.287595e-14,
   9.481642e-14,
   3.831886e-13,
   1.509963e-12,
   5.801559e-12,
   2.173441e-11,
   7.939179e-11,
   2.827666e-10,
   9.819858e-10,
   3.325118e-09,
   1.097826e-08,
   3.534148e-08,
   1.109329e-07,
   3.395167e-07,
   1.013179e-06,
   2.94806e-06,
   8.363939e-06,
   2.313716e-05,
   6.240711e-05,
   0.000164128,
   0.0004208778,
   0.001052335,
   0.002565528,
   0.006098515,
   0.01413501,
   0.03194427,
   0.07039054,
   0.1512378,
   0.3168336,
   0.6471824,
   1.288982,
   2.503178,
   4.739813,
   8.750953,
   15.7534,
   27.65144,
   47.3245,
   78.97306,
   128.4981,
   203.8632,
   315.3594,
   475.6609,
   699.542,
   840.3423,
   1003.125,
   1189.898,
   1402.557,
   1642.811,
   1912.101,
   2211.517,
   2541.71,
   2902.804,
   3294.32,
   3715.095,
   4163.228,
   5130.023,
   6163.581,
   7220.571,
   8247.735,
   8731.735,
   9185.918,
   9602.863,
   9975.509,
   10297.35,
   10562.64,
   10766.51,
   10905.21,
   10976.13,
   10977.94,
   10910.59,
   10775.37,
   10574.79,
   10312.59,
   9993.559,
   9623.4,
   9208.59,
   8756.163,
   8273.528,
   7768.262,
   6719.833,
   5667.844,
   4661.244,
   4187.243,
   3737.753,
   3315.501,
   2922.429,
   2559.735,
   2227.933,
   1926.927,
   1656.093,
   1414.362,
   1200.307,
   1012.232,
   848.251,
   584.4955,
   392.7016,
   257.258,
   164.3235,
   102.3423,
   62.14919,
   36.79937,
   21.24565,
   11.95981,
   6.564523,
   3.513232,
   1.833307,
   0.9327991,
   0.4627706,
   0.2238557,
   0.1055833,
   0.04855645,
   0.02177325,
   0.009519725,
   0.004058356,
   0.001686944,
   0.001686944};
   graph = new TGraph(124,e_signal_fx2,e_signal_fy2);
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
   
   TH1F *Graph_e_signal2 = new TH1F("Graph_e_signal2","Projection of completePDF",124,-11.5,6.5);
   Graph_e_signal2->SetMinimum(9.516459e-20);
   Graph_e_signal2->SetMaximum(12075.73);
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
   -4.225,
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
   5.009596,
   10.19052,
   20.29545,
   39.57376,
   75.5475,
   141.2,
   258.3743,
   462.8727,
   811.8385,
   1394.028,
   2343.503,
   3857,
   6214.728,
   9803.504,
   15139.99,
   22890.4,
   33881.55,
   49096.85,
   69650.35,
   96732.17,
   131521.1,
   152141.8,
   175063.4,
   200371.5,
   228123.5,
   258343.4,
   291016.9,
   326085.9,
   363445.3,
   444356.7,
   531857.9,
   623203.5,
   714881.5,
   802800.2,
   843980.8,
   882571.4,
   918035,
   949862.5,
   977584.4,
   1000783,
   1019102,
   1032255,
   1040037,
   1042326,
   1039661,
   1032492,
   1020917,
   1005097,
   985247.7,
   961635.9,
   934573.6,
   904410.2,
   871525.1,
   836319.3,
   760606.5,
   680595.2,
   599444.9,
   519951.3,
   444406.8,
   374526.8,
   311439.3,
   255726.4,
   207503,
   166516.4,
   132251.8,
   104031.4,
   81099.5,
   62688.85,
   48067.8,
   36569.89,
   27609.07,
   20683.98,
   15375,
   11337,
   8290.018,
   6009.538,
   4317.171,
   3072.378,
   2165.302,
   1510.753,
   1043.222,
   712.7896,
   481.7883,
   322.0961,
   212.9543,
   139.2225,
   89.99419,
   57.51363,
   36.33745,
   22.6959,
   14.01317,
   8.55285,
   5.160168,
   3.077444,
   1.814203,
   1.057178,
   0.6089416,
   0.3467102,
   0.1951284,
   0.1085517,
   0.05969179,
   0.03244547,
   0.01743231,
   0.009258001,
   0.004860049,
   0.002521885,
   0.001293514,
   0.0006558102,
   0.0003286595,
   0.0001628079,
   7.971974e-05,
   3.85849e-05,
   1.845993e-05,
   8.72979e-06,
   4.080738e-06,
   4.080738e-06};
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
   Graph_pi_signal3->SetMinimum(3.672664e-06);
   Graph_pi_signal3->SetMaximum(1146559);
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
   
   Double_t pi2_signal_fx4[121] = {
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
   1.925,
   2,
   2.075,
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
   3.05,
   3.2,
   3.275,
   3.35,
   3.425,
   3.5,
   3.575,
   3.65,
   3.725,
   3.8,
   3.8375,
   3.875,
   3.9125,
   3.95,
   3.9875,
   4.025,
   4.1,
   4.175,
   4.25,
   4.325,
   4.4,
   4.475,
   4.55,
   4.7,
   4.85,
   5,
   5};
   Double_t pi2_signal_fy4[121] = {
   3.590447e-60,
   7.834671e-59,
   1.653446e-57,
   3.374867e-56,
   6.662243e-55,
   1.271983e-53,
   2.348765e-52,
   4.194642e-51,
   7.245152e-50,
   1.210312e-48,
   1.955438e-47,
   3.055542e-46,
   4.617741e-45,
   6.749446e-44,
   9.541218e-43,
   1.304478e-41,
   1.724911e-40,
   2.205942e-39,
   2.728466e-38,
   3.263926e-37,
   3.776236e-36,
   4.225471e-35,
   4.572865e-34,
   4.786288e-33,
   4.845142e-32,
   4.743636e-31,
   4.491727e-30,
   4.11351e-29,
   3.643418e-28,
   3.121064e-27,
   2.585791e-26,
   2.07196e-25,
   1.605708e-24,
   1.203508e-23,
   8.724259e-23,
   6.116533e-22,
   4.147432e-21,
   2.719884e-20,
   1.725118e-19,
   1.05824e-18,
   6.278372e-18,
   3.602525e-17,
   1.999236e-16,
   1.073046e-15,
   5.570189e-15,
   2.796525e-14,
   1.35789e-13,
   6.376871e-13,
   2.896329e-12,
   1.272288e-11,
   5.405303e-11,
   2.221017e-10,
   8.826347e-10,
   3.392402e-09,
   1.261045e-08,
   4.533685e-08,
   1.57641e-07,
   5.301322e-07,
   1.724235e-06,
   5.423827e-06,
   1.650108e-05,
   4.855302e-05,
   0.0001381711,
   0.0003802905,
   0.001012304,
   0.002606174,
   0.00648923,
   0.01562716,
   0.03639689,
   0.08198712,
   0.1786176,
   0.3763569,
   0.7669602,
   1.511621,
   2.881445,
   5.312205,
   9.471887,
   16.33411,
   27.24278,
   43.94452,
   55.11792,
   68.55754,
   84.56525,
   103.4434,
   125.484,
   150.9551,
   180.0867,
   213.0541,
   249.961,
   290.8232,
   335.5523,
   383.9419,
   435.6575,
   490.2292,
   605.3827,
   723.0329,
   780.3393,
   835.1861,
   886.4563,
   933.0516,
   973.9313,
   1008.15,
   1034.896,
   1053.518,
   1059.632,
   1063.56,
   1065.276,
   1064.771,
   1062.046,
   1057.121,
   1040.8,
   1016.212,
   983.9559,
   944.803,
   899.6658,
   849.5627,
   795.5802,
   680.4308,
   562.835,
   450.2725,
   450.2725};
   graph = new TGraph(121,pi2_signal_fx4,pi2_signal_fy4);
   graph->SetName("pi2_signal");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);
   graph->SetLineColor(6);
   graph->SetLineStyle(6);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_pi2_signal4 = new TH1F("Graph_pi2_signal4","Projection of completePDF",121,-11.5,6.5);
   Graph_pi2_signal4->SetMinimum(3.231403e-60);
   Graph_pi2_signal4->SetMaximum(1171.804);
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
   
   Double_t HistM_fx3002[30] = {
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
   Double_t HistM_fy3002[30] = {
   2,
   28,
   220,
   1592,
   9109,
   38840,
   126792,
   317011,
   609292,
   898342,
   1038926,
   951234,
   708497,
   433126,
   226755,
   103609,
   43722,
   21563,
   15399,
   12617,
   9464,
   5652,
   2547,
   1032,
   535,
   555,
   799,
   810,
   802,
   629};
   Double_t HistM_felx3002[30] = {
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
   Double_t HistM_fely3002[30] = {
   1.291815,
   5.259711,
   14.34082,
   39.40301,
   94.94239,
   196.5793,
   355.579,
   562.5375,
   780.0717,
   947.3092,
   1018.777,
   974.8124,
   841.2228,
   657.6233,
   475.6883,
   321.3839,
   208.5987,
   146.3443,
   123.5937,
   111.8265,
   96.78438,
   74.68145,
   49.97029,
   31.62865,
   22.63547,
   23.06374,
   27.77101,
   27.96489,
   27.82402,
   24.58486};
   Double_t HistM_fehx3002[30] = {
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
   Double_t HistM_fehy3002[30] = {
   2.63786,
   6.354446,
   15.34082,
   40.40301,
   95.94239,
   197.5793,
   356.579,
   563.5375,
   781.0717,
   948.3092,
   1019.777,
   975.8124,
   842.2228,
   658.6233,
   476.6883,
   322.3839,
   209.5987,
   147.3443,
   124.5937,
   112.8265,
   97.78438,
   75.68145,
   50.97029,
   32.62865,
   23.63547,
   24.06374,
   28.77101,
   28.96489,
   28.82402,
   25.58486};
   grae = new TGraphAsymmErrors(30,HistM_fx3002,HistM_fy3002,HistM_felx3002,HistM_fehx3002,HistM_fely3002,HistM_fehy3002);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   
   TH1F *Graph_HistM3002 = new TH1F("Graph_HistM3002","Histogram of dataHist_plot__PID",100,-11.96,6.76);
   Graph_HistM3002->SetMinimum(0.6373669);
   Graph_HistM3002->SetMaximum(1143940);
   Graph_HistM3002->SetDirectory(0);
   Graph_HistM3002->SetStats(0);
   Graph_HistM3002->SetLineWidth(2);
   Graph_HistM3002->SetMarkerStyle(20);
   Graph_HistM3002->GetXaxis()->SetNdivisions(505);
   Graph_HistM3002->GetXaxis()->SetLabelFont(132);
   Graph_HistM3002->GetXaxis()->SetLabelOffset(0.01);
   Graph_HistM3002->GetXaxis()->SetLabelSize(0.06);
   Graph_HistM3002->GetXaxis()->SetTitleSize(0.072);
   Graph_HistM3002->GetXaxis()->SetTitleOffset(0.95);
   Graph_HistM3002->GetXaxis()->SetTitleFont(132);
   Graph_HistM3002->GetYaxis()->SetLabelFont(132);
   Graph_HistM3002->GetYaxis()->SetLabelOffset(0.01);
   Graph_HistM3002->GetYaxis()->SetLabelSize(0.06);
   Graph_HistM3002->GetYaxis()->SetTitleSize(0.072);
   Graph_HistM3002->GetYaxis()->SetTitleOffset(0.95);
   Graph_HistM3002->GetYaxis()->SetTitleFont(132);
   Graph_HistM3002->GetZaxis()->SetLabelFont(132);
   Graph_HistM3002->GetZaxis()->SetLabelSize(0.06);
   Graph_HistM3002->GetZaxis()->SetTitleSize(0.072);
   Graph_HistM3002->GetZaxis()->SetTitleOffset(1.2);
   Graph_HistM3002->GetZaxis()->SetTitleFont(132);
   grae->SetHistogram(Graph_HistM3002);
   
   grae->Draw("p");
   
   TPaveText *pt = new TPaveText(0.62,0.7,0.88,0.88,"BRNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetLineWidth(2);
   pt->SetTextFont(132);
   pt->SetTextSize(0.07);
   TText *pt_LaTex = pt->AddText("#it{p}_{T} #in [1.2,1.5] GeV");
   pt->Draw();
   
   TH1D *frame_7fc9ef25e550__2 = new TH1D("frame_7fc9ef25e550__2","",100,-10.4,5.2);
   frame_7fc9ef25e550__2->SetBinContent(1,1094443);
   frame_7fc9ef25e550__2->SetMinimum(1);
   frame_7fc9ef25e550__2->SetMaximum(1.038926e+07);
   frame_7fc9ef25e550__2->SetEntries(2);
   frame_7fc9ef25e550__2->SetDirectory(0);
   frame_7fc9ef25e550__2->SetStats(0);
   frame_7fc9ef25e550__2->SetLineWidth(2);
   frame_7fc9ef25e550__2->SetMarkerStyle(20);
   frame_7fc9ef25e550__2->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fc9ef25e550__2->GetXaxis()->SetNdivisions(505);
   frame_7fc9ef25e550__2->GetXaxis()->SetLabelFont(132);
   frame_7fc9ef25e550__2->GetXaxis()->SetLabelOffset(0.01);
   frame_7fc9ef25e550__2->GetXaxis()->SetLabelSize(0.06);
   frame_7fc9ef25e550__2->GetXaxis()->SetTitleSize(0.072);
   frame_7fc9ef25e550__2->GetXaxis()->SetTitleOffset(0.95);
   frame_7fc9ef25e550__2->GetXaxis()->SetTitleFont(132);
   frame_7fc9ef25e550__2->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7fc9ef25e550__2->GetYaxis()->SetLabelFont(132);
   frame_7fc9ef25e550__2->GetYaxis()->SetLabelOffset(0.01);
   frame_7fc9ef25e550__2->GetYaxis()->SetLabelSize(0.06);
   frame_7fc9ef25e550__2->GetYaxis()->SetTitleSize(0.1);
   frame_7fc9ef25e550__2->GetYaxis()->SetTitleOffset(0.6);
   frame_7fc9ef25e550__2->GetYaxis()->SetTitleFont(132);
   frame_7fc9ef25e550__2->GetZaxis()->SetLabelFont(132);
   frame_7fc9ef25e550__2->GetZaxis()->SetLabelSize(0.06);
   frame_7fc9ef25e550__2->GetZaxis()->SetTitleSize(0.072);
   frame_7fc9ef25e550__2->GetZaxis()->SetTitleOffset(1.2);
   frame_7fc9ef25e550__2->GetZaxis()->SetTitleFont(132);
   frame_7fc9ef25e550__2->Draw("AXISSAME");
   pad1->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
