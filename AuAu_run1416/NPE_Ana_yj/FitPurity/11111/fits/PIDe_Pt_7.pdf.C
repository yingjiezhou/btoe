void PIDe_Pt_7.pdf()
{
//=========Macro generated from canvas: c1/full fit
//=========  (Wed Aug 14 14:51:31 2019) by ROOT version 6.16/00
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
   pad1->Range(-13.0963,-1.251577,6.162963,6.570779);
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
   
   TH1D *frame_7fde0269ecc0__1 = new TH1D("frame_7fde0269ecc0__1","",100,-10.4,5.2);
   frame_7fde0269ecc0__1->SetBinContent(1,92820.34);
   frame_7fde0269ecc0__1->SetMinimum(1);
   frame_7fde0269ecc0__1->SetMaximum(881030);
   frame_7fde0269ecc0__1->SetEntries(1);
   frame_7fde0269ecc0__1->SetDirectory(0);
   frame_7fde0269ecc0__1->SetStats(0);
   frame_7fde0269ecc0__1->SetLineWidth(2);
   frame_7fde0269ecc0__1->SetMarkerStyle(20);
   frame_7fde0269ecc0__1->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fde0269ecc0__1->GetXaxis()->SetNdivisions(505);
   frame_7fde0269ecc0__1->GetXaxis()->SetLabelFont(132);
   frame_7fde0269ecc0__1->GetXaxis()->SetLabelOffset(0.01);
   frame_7fde0269ecc0__1->GetXaxis()->SetLabelSize(0.06);
   frame_7fde0269ecc0__1->GetXaxis()->SetTitleSize(0.072);
   frame_7fde0269ecc0__1->GetXaxis()->SetTitleOffset(0.95);
   frame_7fde0269ecc0__1->GetXaxis()->SetTitleFont(132);
   frame_7fde0269ecc0__1->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7fde0269ecc0__1->GetYaxis()->SetLabelFont(132);
   frame_7fde0269ecc0__1->GetYaxis()->SetLabelOffset(0.01);
   frame_7fde0269ecc0__1->GetYaxis()->SetLabelSize(0.06);
   frame_7fde0269ecc0__1->GetYaxis()->SetTitleSize(0.1);
   frame_7fde0269ecc0__1->GetYaxis()->SetTitleOffset(0.6);
   frame_7fde0269ecc0__1->GetYaxis()->SetTitleFont(132);
   frame_7fde0269ecc0__1->GetZaxis()->SetLabelFont(132);
   frame_7fde0269ecc0__1->GetZaxis()->SetLabelSize(0.06);
   frame_7fde0269ecc0__1->GetZaxis()->SetTitleSize(0.072);
   frame_7fde0269ecc0__1->GetZaxis()->SetTitleOffset(1.2);
   frame_7fde0269ecc0__1->GetZaxis()->SetTitleFont(132);
   frame_7fde0269ecc0__1->Draw("FUNC");
   
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
   0,
   57,
   301,
   1293,
   4387,
   12724,
   26167,
   43036,
   58629,
   66371,
   71942,
   76645,
   88103,
   85753,
   74011,
   50998,
   27630,
   13478,
   7468,
   5048,
   3827,
   2136,
   995,
   324,
   168,
   14,
   7,
   0,
   6,
   0};
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
   0,
   7.527619,
   16.85655,
   35.46179,
   65.73632,
   112.3018,
   161.2629,
   206.9518,
   241.6348,
   257.1262,
   267.7205,
   276.3488,
   296.3219,
   292.3366,
   271.5501,
   225.3279,
   165.7235,
   115.5959,
   85.91904,
   70.55104,
   61.36477,
   45.71958,
   31.04758,
   17.50694,
   12.47112,
   3.6965,
   2.58147,
   0,
   2.379931,
   0};
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
   1.147874,
   8.594007,
   17.85655,
   36.46179,
   66.73632,
   113.3018,
   162.2629,
   207.9518,
   242.6348,
   258.1262,
   268.7205,
   277.3488,
   297.3219,
   293.3366,
   272.5501,
   226.3279,
   166.7235,
   116.5959,
   86.91904,
   71.55104,
   62.36477,
   46.71958,
   32.04758,
   18.50694,
   13.47112,
   4.830381,
   3.770281,
   1.147874,
   3.583642,
   1.147874};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(30,HistM_fx3001,HistM_fy3001,HistM_felx3001,HistM_fehx3001,HistM_fely3001,HistM_fehy3001);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   
   TH1F *Graph_HistM3001 = new TH1F("Graph_HistM3001","Histogram of dataHist_plot__PID",100,-11.96,6.76);
   Graph_HistM3001->SetMinimum(97.24035);
   Graph_HistM3001->SetMaximum(97240.35);
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
   
   Double_t PID_Curve_fx1[111] = {
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
   -3.625,
   -3.55,
   -3.475,
   -3.4,
   -3.325,
   -3.25,
   -3.175,
   -3.1,
   -3.025,
   -2.95,
   -2.875,
   -2.8,
   -2.65,
   -2.5,
   -2.35,
   -2.2,
   -2.05,
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
   Double_t PID_Curve_fy1[111] = {
   17.63538,
   29.06176,
   47.78129,
   78.12358,
   126.6449,
   203.0134,
   321.0843,
   500.1139,
   765.9998,
   1152.356,
   1701.154,
   2462.589,
   3493.812,
   4856.186,
   6610.886,
   8812.857,
   11503.49,
   14702.74,
   18401.76,
   22557.32,
   27089.47,
   31883.46,
   36796.57,
   41669.71,
   46342.8,
   50671.95,
   54546.18,
   57900.83,
   60753.84,
   63188.52,
   65285.55,
   67152.74,
   68909.54,
   70669.42,
   72522.71,
   74522.36,
   76674.59,
   78935.42,
   81213.43,
   83378.37,
   85274.1,
   86734.43,
   87599.72,
   87765.01,
   87732.45,
   87490.46,
   87030.24,
   86276.92,
   85144.04,
   83638.16,
   81773.3,
   79570.3,
   77056.08,
   74262.85,
   71227.12,
   64589.45,
   57480.61,
   50238.28,
   43169.84,
   36529.33,
   30503.7,
   27760.29,
   25208.44,
   22852.06,
   20691.44,
   18723.66,
   16943.03,
   13909.44,
   11507.54,
   9638.643,
   8200.195,
   7094.615,
   6235.211,
   5549.444,
   4980.038,
   4484.511,
   4033.661,
   3609.454,
   3202.658,
   2810.486,
   2434.41,
   2078.268,
   1746.732,
   1444.171,
   1173.892,
   937.7365,
   735.9782,
   567.4399,
   429.764,
   319.7582,
   233.7559,
   167.9433,
   118.6255,
   82.41678,
   56.35587,
   37.95564,
   25.20148,
   16.51447,
   10.69424,
   6.853619,
   4.353966,
   2.74669,
   1.723783,
   1.078142,
   0.6731241,
   0.420074,
   0.2622955,
   0.1639533,
   0.1025996,
   0.06425676,
   0.06425676};
   TGraph *graph = new TGraph(111,PID_Curve_fx1,PID_Curve_fy1);
   graph->SetName("PID_Curve");
   graph->SetTitle("Projection of completePDF");
   graph->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_PID_Curve1 = new TH1F("Graph_PID_Curve1","Projection of completePDF",111,-11.5,6.5);
   Graph_PID_Curve1->SetMinimum(0.05783109);
   Graph_PID_Curve1->SetMaximum(96541.5);
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
   
   Double_t e_signal_fx2[120] = {
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
   1.1,
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
   Double_t e_signal_fy2[120] = {
   4.416539e-16,
   1.65879e-15,
   6.103384e-15,
   2.199987e-14,
   7.76854e-14,
   2.687378e-13,
   9.10727e-13,
   3.023553e-12,
   9.833703e-12,
   3.133189e-11,
   9.779712e-11,
   2.990443e-10,
   8.958083e-10,
   2.628843e-09,
   7.557606e-09,
   2.128501e-08,
   5.872641e-08,
   1.587315e-07,
   4.203032e-07,
   1.090266e-06,
   2.770589e-06,
   6.897343e-06,
   1.682138e-05,
   4.018939e-05,
   9.406567e-05,
   0.0002156855,
   0.0004844855,
   0.001066131,
   0.00229832,
   0.004853784,
   0.010042,
   0.02035309,
   0.04041199,
   0.07860681,
   0.1497891,
   0.2796213,
   0.5113641,
   0.9161368,
   1.607905,
   2.764589,
   4.656618,
   7.683884,
   12.42113,
   19.67031,
   30.51626,
   46.37902,
   69.05289,
   100.7192,
   143.9171,
   201.4572,
   276.2632,
   371.1363,
   426.8643,
   488.4429,
   556.039,
   629.7442,
   709.5625,
   795.3982,
   887.0459,
   984.1812,
   1192.986,
   1416.661,
   1648.035,
   1878.179,
   2096.899,
   2198.615,
   2293.444,
   2380.097,
   2457.36,
   2524.122,
   2579.404,
   2622.382,
   2652.406,
   2669.018,
   2671.964,
   2661.198,
   2636.886,
   2599.399,
   2549.306,
   2487.36,
   2414.475,
   2331.709,
   2240.234,
   2141.313,
   2036.265,
   1813.197,
   1581.706,
   1351.689,
   1131.612,
   928.0863,
   834.0365,
   745.6744,
   663.2556,
   586.9217,
   516.71,
   452.5651,
   394.3509,
   341.8629,
   252.984,
   183.402,
   130.2522,
   90.6225,
   61.76708,
   41.2428,
   26.97797,
   17.28783,
   10.85279,
   6.674407,
   4.021183,
   2.373368,
   1.372291,
   0.7773159,
   0.4313391,
   0.2344823,
   0.1248738,
   0.06514825,
   0.03329692,
   0.01667153,
   0.008177431,
   0.008177431};
   graph = new TGraph(120,e_signal_fx2,e_signal_fy2);
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
   
   TH1F *Graph_e_signal2 = new TH1F("Graph_e_signal2","Projection of completePDF",120,-11.5,6.5);
   Graph_e_signal2->SetMinimum(3.974885e-16);
   Graph_e_signal2->SetMaximum(2939.161);
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
   -4.075,
   -4,
   -3.925,
   -3.85,
   -3.775,
   -3.7,
   -3.625,
   -3.55,
   -3.475,
   -3.4,
   -3.325,
   -3.25,
   -3.175,
   -3.1,
   -3.025,
   -2.95,
   -2.875,
   -2.8,
   -2.725,
   -2.65,
   -2.5,
   -2.35,
   -2.2,
   -2.05,
   -1.9,
   -1.825,
   -1.75,
   -1.675,
   -1.6,
   -1.525,
   -1.45,
   -1.375,
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
   5.590385,
   7.836919,
   10.91217,
   15.09543,
   20.75282,
   28.36333,
   38.55326,
   52.1419,
   70.20251,
   94.14384,
   125.8185,
   167.6666,
   222.9022,
   295.7547,
   391.77,
   518.1813,
   684.348,
   902.2563,
   1187.062,
   1557.642,
   2037.092,
   2653.113,
   3438.16,
   4429.278,
   5667.462,
   7196.464,
   9060.921,
   11303.77,
   13962.98,
   17067.65,
   20633.74,
   24659.72,
   29122.48,
   33974.06,
   39139.55,
   44516.77,
   49977.88,
   55373.32,
   60537.86,
   65298.68,
   67473.89,
   69484.75,
   71311.84,
   72937.15,
   74344.36,
   75519.12,
   76449.29,
   77125.17,
   77539.65,
   77688.36,
   77500.65,
   76894.03,
   75878.67,
   74471.87,
   72697.32,
   70584.4,
   68167.38,
   65484.47,
   62576.78,
   59487.3,
   52937.73,
   46177.12,
   39514.44,
   33204.57,
   27435.8,
   24793.96,
   22326.44,
   20037.86,
   17929.35,
   15999.01,
   14242.32,
   12652.63,
   11221.6,
   8796.24,
   6881.346,
   5388.885,
   4235.536,
   3347.554,
   2663.066,
   2132.409,
   1717.168,
   1388.523,
   1125.346,
   912.3776,
   738.6436,
   596.1951,
   479.1603,
   383.0717,
   304.4125,
   240.3217,
   188.4109,
   146.6519,
   113.3084,
   86.89173,
   66.131,
   49.9484,
   37.43824,
   27.84704,
   20.55454,
   15.05564,
   10.94339,
   7.893413,
   5.649859,
   4.013007,
   2.828535,
   1.978394,
   1.373166,
   0.945786,
   0.6464306,
   0.4384401,
   0.2950923,
   0.1970901,
   0.1306264,
   0.08591255,
   0.0560714,
   0.0560714};
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
   Graph_pi_signal3->SetMinimum(0.05046426);
   Graph_pi_signal3->SetMaximum(85457.19);
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
   
   Double_t p_signal_fx4[116] = {
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
   -7.975,
   -7.9,
   -7.825,
   -7.75,
   -7.675,
   -7.6,
   -7.525,
   -7.45,
   -7.375,
   -7.3,
   -7.15,
   -7,
   -6.85,
   -6.7,
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
   -5.425,
   -5.35,
   -5.275,
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
   Double_t p_signal_fy4[116] = {
   12.04499,
   21.22484,
   36.86913,
   63.02815,
   105.8921,
   174.6501,
   282.531,
   447.972,
   695.7973,
   1058.212,
   1575.335,
   2294.923,
   3270.91,
   4560.431,
   5340.375,
   6219.116,
   7202.32,
   8294.676,
   9499.636,
   10819.14,
   12253.37,
   13800.49,
   15456.42,
   17214.7,
   20999.68,
   25052.38,
   29230.35,
   33358.41,
   37240.43,
   39026.04,
   40675.33,
   42165.44,
   43475.48,
   44587.18,
   45485.26,
   46157.9,
   46597.06,
   46804.11,
   46790.86,
   46560.93,
   46120.87,
   45480.32,
   44651.81,
   43650.33,
   42493,
   41198.58,
   39787.02,
   36695.28,
   33383,
   30005.31,
   26696.21,
   23561.19,
   20673.96,
   18076.93,
   15784.69,
   13789.6,
   12068.18,
   10587.61,
   9311.366,
   8203.638,
   7232.378,
   6370.964,
   5598.738,
   4900.691,
   4266.62,
   3690.023,
   3166.957,
   2695.016,
   2272.501,
   1897.819,
   1569.107,
   1284.044,
   1039.804,
   833.1202,
   660.3982,
   517.8659,
   401.7187,
   308.2527,
   233.9716,
   175.6648,
   130.4572,
   95.83208,
   69.63243,
   50.04597,
   35.57812,
   25.01802,
   17.40117,
   11.97181,
   8.146978,
   5.483891,
   3.651209,
   2.404584,
   1.566385,
   1.009283,
   0.6432539,
   0.4055155,
   0.2528646,
   0.1559639,
   0.09515146,
   0.05741989,
   0.03427399,
   0.0202359,
   0.01181777,
   0.006826599,
   0.003900574,
   0.00220449,
   0.001232376,
   0.0006814495,
   0.0003727174,
   0.000201642,
   0.0001079041,
   5.7115e-05,
   2.990322e-05,
   1.548607e-05,
   7.932676e-06,
   7.932676e-06};
   graph = new TGraph(116,p_signal_fx4,p_signal_fy4);
   graph->SetName("p_signal");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);
   graph->SetLineColor(7);
   graph->SetLineStyle(6);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_p_signal4 = new TH1F("Graph_p_signal4","Projection of completePDF",116,-11.5,6.5);
   Graph_p_signal4->SetMinimum(7.139409e-06);
   Graph_p_signal4->SetMaximum(51484.52);
   Graph_p_signal4->SetDirectory(0);
   Graph_p_signal4->SetStats(0);
   Graph_p_signal4->SetLineWidth(2);
   Graph_p_signal4->SetMarkerStyle(20);
   Graph_p_signal4->GetXaxis()->SetNdivisions(505);
   Graph_p_signal4->GetXaxis()->SetLabelFont(132);
   Graph_p_signal4->GetXaxis()->SetLabelOffset(0.01);
   Graph_p_signal4->GetXaxis()->SetLabelSize(0.06);
   Graph_p_signal4->GetXaxis()->SetTitleSize(0.072);
   Graph_p_signal4->GetXaxis()->SetTitleOffset(0.95);
   Graph_p_signal4->GetXaxis()->SetTitleFont(132);
   Graph_p_signal4->GetYaxis()->SetLabelFont(132);
   Graph_p_signal4->GetYaxis()->SetLabelOffset(0.01);
   Graph_p_signal4->GetYaxis()->SetLabelSize(0.06);
   Graph_p_signal4->GetYaxis()->SetTitleSize(0.072);
   Graph_p_signal4->GetYaxis()->SetTitleOffset(0.95);
   Graph_p_signal4->GetYaxis()->SetTitleFont(132);
   Graph_p_signal4->GetZaxis()->SetLabelFont(132);
   Graph_p_signal4->GetZaxis()->SetLabelSize(0.06);
   Graph_p_signal4->GetZaxis()->SetTitleSize(0.072);
   Graph_p_signal4->GetZaxis()->SetTitleOffset(1.2);
   Graph_p_signal4->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_p_signal4);
   
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
   301,
   105,
   128,
   232,
   213,
   365,
   415,
   517,
   369,
   352,
   181,
   126,
   166,
   185,
   124,
   132,
   2360,
   4503,
   3821,
   2136,
   995,
   324,
   168,
   14,
   7,
   0,
   6,
   0};
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
   16.85655,
   9.759142,
   10.82475,
   14.73975,
   14.10308,
   18.61151,
   19.87768,
   22.24313,
   18.71588,
   18.26832,
   12.96291,
   10.7361,
   12.3938,
   13.11066,
   10.64675,
   11,
   48.0824,
   66.60626,
   61.31626,
   45.71958,
   31.04758,
   17.50694,
   12.47112,
   3.6965,
   2.58147,
   0,
   2.379931,
   0};
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
   17.85655,
   10.75914,
   11.82475,
   15.73975,
   15.10308,
   19.61151,
   20.87768,
   23.24313,
   19.71588,
   19.26832,
   13.96291,
   11.7361,
   13.3938,
   14.11066,
   11.64675,
   12,
   49.0824,
   67.60626,
   62.31626,
   46.71958,
   32.04758,
   18.50694,
   13.47112,
   4.830381,
   3.770281,
   1.147874,
   3.583642,
   1.147874};
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
   Graph_HistM13002->SetMinimum(5.027667);
   Graph_HistM13002->SetMaximum(5027.667);
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
   0,
   57,
   301,
   1293,
   4387,
   12724,
   26167,
   43036,
   58629,
   66371,
   71942,
   76645,
   88103,
   85753,
   74011,
   50998,
   27630,
   13478,
   7468,
   5048,
   3827,
   2136,
   995,
   324,
   168,
   14,
   7,
   0,
   6,
   0};
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
   0,
   7.527619,
   16.85655,
   35.46179,
   65.73632,
   112.3018,
   161.2629,
   206.9518,
   241.6348,
   257.1262,
   267.7205,
   276.3488,
   296.3219,
   292.3366,
   271.5501,
   225.3279,
   165.7235,
   115.5959,
   85.91904,
   70.55104,
   61.36477,
   45.71958,
   31.04758,
   17.50694,
   12.47112,
   3.6965,
   2.58147,
   0,
   2.379931,
   0};
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
   1.147874,
   8.594007,
   17.85655,
   36.46179,
   66.73632,
   113.3018,
   162.2629,
   207.9518,
   242.6348,
   258.1262,
   268.7205,
   277.3488,
   297.3219,
   293.3366,
   272.5501,
   226.3279,
   166.7235,
   116.5959,
   86.91904,
   71.55104,
   62.36477,
   46.71958,
   32.04758,
   18.50694,
   13.47112,
   4.830381,
   3.770281,
   1.147874,
   3.583642,
   1.147874};
   grae = new TGraphAsymmErrors(30,HistM_fx3003,HistM_fy3003,HistM_felx3003,HistM_fehx3003,HistM_fely3003,HistM_fehy3003);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   
   TH1F *Graph_HistM3003 = new TH1F("Graph_HistM3003","Histogram of dataHist_plot__PID",100,-11.96,6.76);
   Graph_HistM3003->SetMinimum(97.24035);
   Graph_HistM3003->SetMaximum(97240.35);
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
   TText *pt_LaTex = pt->AddText("#it{p}_{T} #in [3.5,4.5] GeV");
   pt->Draw();
   
   TH1D *frame_7fde0269ecc0__2 = new TH1D("frame_7fde0269ecc0__2","",100,-10.4,5.2);
   frame_7fde0269ecc0__2->SetBinContent(1,92820.34);
   frame_7fde0269ecc0__2->SetMinimum(1);
   frame_7fde0269ecc0__2->SetMaximum(881030);
   frame_7fde0269ecc0__2->SetEntries(1);
   frame_7fde0269ecc0__2->SetDirectory(0);
   frame_7fde0269ecc0__2->SetStats(0);
   frame_7fde0269ecc0__2->SetLineWidth(2);
   frame_7fde0269ecc0__2->SetMarkerStyle(20);
   frame_7fde0269ecc0__2->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fde0269ecc0__2->GetXaxis()->SetNdivisions(505);
   frame_7fde0269ecc0__2->GetXaxis()->SetLabelFont(132);
   frame_7fde0269ecc0__2->GetXaxis()->SetLabelOffset(0.01);
   frame_7fde0269ecc0__2->GetXaxis()->SetLabelSize(0.06);
   frame_7fde0269ecc0__2->GetXaxis()->SetTitleSize(0.072);
   frame_7fde0269ecc0__2->GetXaxis()->SetTitleOffset(0.95);
   frame_7fde0269ecc0__2->GetXaxis()->SetTitleFont(132);
   frame_7fde0269ecc0__2->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7fde0269ecc0__2->GetYaxis()->SetLabelFont(132);
   frame_7fde0269ecc0__2->GetYaxis()->SetLabelOffset(0.01);
   frame_7fde0269ecc0__2->GetYaxis()->SetLabelSize(0.06);
   frame_7fde0269ecc0__2->GetYaxis()->SetTitleSize(0.1);
   frame_7fde0269ecc0__2->GetYaxis()->SetTitleOffset(0.6);
   frame_7fde0269ecc0__2->GetYaxis()->SetTitleFont(132);
   frame_7fde0269ecc0__2->GetZaxis()->SetLabelFont(132);
   frame_7fde0269ecc0__2->GetZaxis()->SetLabelSize(0.06);
   frame_7fde0269ecc0__2->GetZaxis()->SetTitleSize(0.072);
   frame_7fde0269ecc0__2->GetZaxis()->SetTitleOffset(1.2);
   frame_7fde0269ecc0__2->GetZaxis()->SetTitleFont(132);
   frame_7fde0269ecc0__2->Draw("AXISSAME");
   pad1->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
