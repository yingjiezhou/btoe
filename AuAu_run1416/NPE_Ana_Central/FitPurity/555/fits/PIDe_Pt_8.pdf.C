void PIDe_Pt_8.pdf()
{
//=========Macro generated from canvas: c1/full fit
//=========  (Sun Aug 18 21:36:33 2019) by ROOT version 6.16/00
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
   pad1->Range(0,0,1,1);
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
   
   TH1D *frame_7fded7a9ccd0__11 = new TH1D("frame_7fded7a9ccd0__11","",100,-10.4,5.2);
   frame_7fded7a9ccd0__11->SetBinContent(1,633.746);
   frame_7fded7a9ccd0__11->SetMinimum(1);
   frame_7fded7a9ccd0__11->SetMaximum(5790);
   frame_7fded7a9ccd0__11->SetEntries(1);
   frame_7fded7a9ccd0__11->SetDirectory(0);
   frame_7fded7a9ccd0__11->SetStats(0);
   frame_7fded7a9ccd0__11->SetLineWidth(2);
   frame_7fded7a9ccd0__11->SetMarkerStyle(20);
   frame_7fded7a9ccd0__11->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fded7a9ccd0__11->GetXaxis()->SetNdivisions(505);
   frame_7fded7a9ccd0__11->GetXaxis()->SetLabelFont(132);
   frame_7fded7a9ccd0__11->GetXaxis()->SetLabelOffset(0.01);
   frame_7fded7a9ccd0__11->GetXaxis()->SetLabelSize(0.06);
   frame_7fded7a9ccd0__11->GetXaxis()->SetTitleSize(0.072);
   frame_7fded7a9ccd0__11->GetXaxis()->SetTitleOffset(0.95);
   frame_7fded7a9ccd0__11->GetXaxis()->SetTitleFont(132);
   frame_7fded7a9ccd0__11->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7fded7a9ccd0__11->GetYaxis()->SetLabelFont(132);
   frame_7fded7a9ccd0__11->GetYaxis()->SetLabelOffset(0.01);
   frame_7fded7a9ccd0__11->GetYaxis()->SetLabelSize(0.06);
   frame_7fded7a9ccd0__11->GetYaxis()->SetTitleSize(0.1);
   frame_7fded7a9ccd0__11->GetYaxis()->SetTitleOffset(0.6);
   frame_7fded7a9ccd0__11->GetYaxis()->SetTitleFont(132);
   frame_7fded7a9ccd0__11->GetZaxis()->SetLabelFont(132);
   frame_7fded7a9ccd0__11->GetZaxis()->SetLabelSize(0.06);
   frame_7fded7a9ccd0__11->GetZaxis()->SetTitleSize(0.072);
   frame_7fded7a9ccd0__11->GetZaxis()->SetTitleOffset(1.2);
   frame_7fded7a9ccd0__11->GetZaxis()->SetTitleFont(132);
   frame_7fded7a9ccd0__11->Draw("FUNC");
   
   Double_t HistM_fx3011[30] = {
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
   Double_t HistM_fy3011[30] = {
   0,
   0,
   0,
   3,
   11,
   37,
   74,
   138,
   240,
   314,
   369,
   415,
   510,
   579,
   576,
   471,
   308,
   171,
   86,
   69,
   47,
   27,
   11,
   1,
   2,
   2,
   0,
   0,
   0,
   0};
   Double_t HistM_felx3011[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
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
   Double_t HistM_fely3011[30] = {
   0,
   0,
   0,
   1.632705,
   3.265579,
   6.055143,
   8.582844,
   11.25798,
   15,
   17.2271,
   18.71588,
   19.87768,
   22.08871,
   23.56761,
   23.50521,
   21.20829,
   17.05705,
   12.58625,
   9.255555,
   8.286444,
   6.831172,
   5.163771,
   3.265579,
   0.8272462,
   1.291815,
   1.291815,
   0,
   0,
   0,
   0};
   Double_t HistM_fehx3011[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
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
   Double_t HistM_fehy3011[30] = {
   1.147874,
   1.147874,
   1.147874,
   2.918186,
   4.416521,
   7.137555,
   9.641101,
   12.25798,
   16,
   18.2271,
   19.71588,
   20.87768,
   23.08871,
   24.56761,
   24.50521,
   22.20829,
   18.05705,
   13.58625,
   10.30959,
   9.346779,
   7.904289,
   6.260244,
   4.416521,
   2.299527,
   2.63786,
   2.63786,
   1.147874,
   1.147874,
   1.147874,
   1.147874};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(30,HistM_fx3011,HistM_fy3011,HistM_felx3011,HistM_fehx3011,HistM_fely3011,HistM_fehy3011);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   grae->Draw("p");
   
   Double_t PID_Curve_fx25[117] = {
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
   -2.575,
   -2.5,
   -2.425,
   -2.3875,
   -2.35,
   -2.3125,
   -2.275,
   -2.2,
   -2.125,
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
   Double_t PID_Curve_fy25[117] = {
   0.04234887,
   0.07245021,
   0.1218689,
   0.2015589,
   0.3277694,
   0.5240744,
   0.8239054,
   1.273572,
   1.935679,
   2.892746,
   4.250678,
   6.141602,
   8.725433,
   12.18939,
   16.74469,
   22.61962,
   30.04853,
   39.25662,
   50.44081,
   63.74801,
   79.25253,
   96.93504,
   116.6664,
   138.1992,
   161.1699,
   185.1131,
   209.4894,
   233.7246,
   257.2564,
   279.5859,
   300.3245,
   319.2323,
   336.2386,
   352.3786,
   369.9394,
   389.093,
   409.7954,
   431.8361,
   454.8183,
   478.1565,
   501.0924,
   522.7323,
   542.1034,
   558.2236,
   570.18,
   574.3496,
   577.2059,
   578.6869,
   578.747,
   577.3027,
   574.1999,
   569.4471,
   563.0842,
   555.1741,
   545.8004,
   535.0653,
   523.0864,
   509.9942,
   502.6823,
   493.9388,
   483.7997,
   472.36,
   446.0993,
   416.4112,
   384.7584,
   321.3083,
   291.8602,
   264.9607,
   240.9514,
   219.8787,
   201.5709,
   185.7229,
   171.9715,
   159.9531,
   139.8561,
   123.4543,
   109.5465,
   97.43655,
   86.69167,
   77.01332,
   68.18682,
   60.06343,
   52.55007,
   45.59808,
   39.1904,
   33.32868,
   28.02185,
   23.27716,
   19.09407,
   15.46107,
   12.35478,
   9.741012,
   7.576983,
   5.814158,
   4.401218,
   3.28679,
   2.421704,
   1.760665,
   1.263329,
   0.8948291,
   0.6258546,
   0.4323856,
   0.2952035,
   0.199274,
   0.1330847,
   0.08799764,
   0.05765663,
   0.0374703,
   0.02418039,
   0.01551337,
   0.009907955,
   0.006307942,
   0.004008728,
   0.002546238,
   0.001618297,
   0.001030104,
   0.001030104};
   TGraph *graph = new TGraph(117,PID_Curve_fx25,PID_Curve_fy25);
   graph->SetName("PID_Curve");
   graph->SetTitle("Projection of completePDF");
   graph->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   graph->Draw("l");
   
   Double_t e_signal_fx26[112] = {
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
   -1.675,
   -1.6,
   -1.525,
   -1.45,
   -1.375,
   -1.3,
   -1.225,
   -1.15,
   -1.075,
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
   Double_t e_signal_fy26[112] = {
   1.527188e-10,
   3.708366e-10,
   8.870901e-10,
   2.090489e-09,
   4.853142e-09,
   1.109923e-08,
   2.50068e-08,
   5.550321e-08,
   1.213593e-07,
   2.614105e-07,
   5.547126e-07,
   1.159599e-06,
   2.388047e-06,
   4.844764e-06,
   9.682722e-06,
   1.906414e-05,
   3.697703e-05,
   7.065481e-05,
   0.0001329984,
   0.0002466301,
   0.0004505477,
   0.0008108311,
   0.001437524,
   0.002510698,
   0.004319854,
   0.00732215,
   0.01222653,
   0.02011234,
   0.03259245,
   0.0520315,
   0.08182965,
   0.1267798,
   0.1935015,
   0.2909468,
   0.4309609,
   0.6288645,
   0.9040059,
   1.280208,
   1.786013,
   2.454617,
   3.323363,
   4.432684,
   5.824395,
   7.539279,
   9.613993,
   12.07738,
   14.9464,
   18.22198,
   21.88514,
   25.89394,
   30.18158,
   34.65618,
   39.20256,
   43.68609,
   47.95864,
   51.86633,
   53.63588,
   55.2585,
   56.71743,
   57.99729,
   59.08437,
   59.96685,
   60.63504,
   61.08152,
   61.3013,
   61.29193,
   61.05352,
   60.58872,
   59.90273,
   59.00316,
   57.89987,
   56.60485,
   55.13197,
   53.49671,
   51.71593,
   49.80758,
   45.68343,
   41.27785,
   36.74264,
   32.21948,
   27.83311,
   23.68645,
   19.85789,
   16.40066,
   13.34395,
   10.69553,
   8.445309,
   6.569367,
   5.034155,
   3.800358,
   2.826295,
   2.070644,
   1.494474,
   1.062591,
   0.7442844,
   0.5135783,
   0.3491158,
   0.2337907,
   0.1542339,
   0.1002369,
   0.06417564,
   0.04047696,
   0.02515014,
   0.01539459,
   0.009283047,
   0.005514524,
   0.00322716,
   0.001860493,
   0.001056648,
   0.0005911909,
   0.0003258518,
   0.0003258518};
   graph = new TGraph(112,e_signal_fx26,e_signal_fy26);
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
   graph->Draw("l");
   
   Double_t pi_signal_fx27[121] = {
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
   -5.125,
   -5.05,
   -4.975,
   -4.9,
   -4.825,
   -4.75,
   -4.6,
   -4.45,
   -4.3,
   -4.15,
   -4,
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
   -2.575,
   -2.5,
   -2.425,
   -2.35,
   -2.2,
   -2.05,
   -1.9,
   -1.75,
   -1.675,
   -1.6,
   -1.525,
   -1.45,
   -1.375,
   -1.3,
   -1.225,
   -1.15,
   -1.075,
   -1,
   -0.925,
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
   Double_t pi_signal_fy27[121] = {
   3.178344e-07,
   7.66341e-07,
   1.812457e-06,
   4.204728e-06,
   9.568254e-06,
   2.135758e-05,
   4.676229e-05,
   0.0001004302,
   0.0002115715,
   0.0004371943,
   0.0008861689,
   0.001761907,
   0.003436166,
   0.006573395,
   0.01233474,
   0.02270359,
   0.04099055,
   0.07259347,
   0.126106,
   0.2148813,
   0.3591584,
   0.5888409,
   0.9469662,
   1.49381,
   2.311431,
   3.508255,
   5.223069,
   7.627547,
   10.92619,
   15.35242,
   21.15971,
   28.60665,
   37.93576,
   43.37095,
   49.34637,
   55.87501,
   62.96311,
   70.60913,
   78.8028,
   96.74348,
   116.5001,
   137.6117,
   159.4443,
   181.2121,
   202.0179,
   211.7632,
   220.9109,
   229.3454,
   236.9567,
   243.6431,
   249.3132,
   253.8883,
   257.3038,
   259.5111,
   260.4784,
   260.1363,
   258.3451,
   255.1272,
   250.536,
   244.6475,
   237.5574,
   229.3788,
   220.2395,
   210.2781,
   199.6412,
   176.9431,
   153.3364,
   129.9228,
   107.6351,
   97.14578,
   87.18684,
   77.80993,
   69.05199,
   60.93607,
   53.47242,
   46.65974,
   40.48665,
   34.93321,
   29.97245,
   25.57191,
   21.69507,
   15.35423,
   10.62487,
   7.188654,
   4.75554,
   3.075959,
   1.945313,
   1.202893,
   0.727265,
   0.4299192,
   0.2484902,
   0.1404301,
   0.07759602,
   0.04192249,
   0.02214538,
   0.01143793,
   0.005776174,
   0.002852078,
   0.001376927,
   0.0006499632,
   0.0002999819,
   0.0001353723,
   5.973002e-05,
   2.57682e-05,
   1.086936e-05,
   4.482826e-06,
   1.807709e-06,
   7.127435e-07,
   2.747682e-07,
   1.035686e-07,
   3.816965e-08,
   1.375424e-08,
   4.845998e-09,
   1.669392e-09,
   5.62292e-10,
   1.851799e-10,
   5.962851e-11,
   1.877339e-11,
   5.779092e-12,
   1.739422e-12,
   1.739422e-12};
   graph = new TGraph(121,pi_signal_fx27,pi_signal_fy27);
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
   graph->Draw("l");
   
   Double_t k_signal_fx28[129] = {
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
   -3.025,
   -2.95,
   -2.875,
   -2.8,
   -2.725,
   -2.65,
   -2.575,
   -2.5,
   -2.425,
   -2.3875,
   -2.36875,
   -2.35,
   -2.33125,
   -2.3125,
   -2.275,
   -2.2375,
   -2.2,
   -2.1625,
   -2.125,
   -2.0875,
   -2.05,
   -1.975,
   -1.9,
   -1.8625,
   -1.825,
   -1.7875,
   -1.75,
   -1.7125,
   -1.675,
   -1.6375,
   -1.6,
   -1.5625,
   -1.525,
   -1.4875,
   -1.45,
   -1.4125,
   -1.375,
   -1.3,
   -1.225,
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
   Double_t k_signal_fy28[129] = {
   4.991326e-05,
   8.972791e-05,
   0.0001594227,
   0.0002799522,
   0.0004858794,
   0.000833459,
   0.001413029,
   0.002367711,
   0.003921187,
   0.006418261,
   0.01038313,
   0.01660161,
   0.02623512,
   0.04097576,
   0.06325312,
   0.09650459,
   0.1455208,
   0.2168768,
   0.3194568,
   0.4650742,
   0.6691807,
   0.9516464,
   1.337577,
   1.858117,
   2.551164,
   3.461901,
   4.643035,
   6.154607,
   8.063242,
   10.44071,
   13.36169,
   16.90067,
   21.12796,
   26.1049,
   31.87848,
   38.47549,
   45.89673,
   54.11161,
   63.05363,
   72.61742,
   82.65755,
   92.9898,
   103.3949,
   113.625,
   123.4127,
   132.4819,
   140.5609,
   144.1485,
   147.3952,
   150.2742,
   152.7613,
   154.8353,
   156.4784,
   157.6763,
   158.4187,
   158.699,
   158.2733,
   157.5659,
   156.5254,
   155.1582,
   153.4732,
   149.194,
   143.794,
   137.4044,
   130.1762,
   122.2737,
   113.869,
   105.1353,
   87.34672,
   70.11771,
   62.01895,
   54.38658,
   47.28571,
   40.76043,
   34.8352,
   29.51676,
   24.79646,
   20.65292,
   17.0547,
   13.96295,
   11.33395,
   9.121282,
   7.27782,
   5.757282,
   3.511252,
   2.069138,
   1.178148,
   0.3445635,
   0.08783558,
   0.01951656,
   0.003779792,
   0.0006380639,
   9.388411e-05,
   1.20407e-05,
   1.345994e-06,
   1.311493e-07,
   1.113835e-08,
   8.245314e-10,
   5.320168e-11,
   2.992093e-12,
   1.466752e-13,
   6.267145e-15,
   2.334074e-16,
   7.576893e-18,
   2.143875e-19,
   5.287366e-21,
   1.136609e-22,
   2.12968e-24,
   3.478158e-26,
   4.951263e-28,
   6.143479e-30,
   6.644227e-32,
   6.263344e-34,
   5.146355e-36,
   3.685741e-38,
   2.300815e-40,
   1.251902e-42,
   5.93732e-45,
   2.454383e-47,
   8.843537e-50,
   2.777418e-52,
   7.603058e-55,
   1.814124e-57,
   3.772918e-60,
   6.839423e-63,
   1.08067e-65,
   1.488328e-68,
   1.786635e-71,
   1.786635e-71};
   graph = new TGraph(129,k_signal_fx28,k_signal_fy28);
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
   graph->Draw("l");
   
   Double_t p_signal_fx29[107] = {
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
   Double_t p_signal_fy29[107] = {
   0.04229864,
   0.07235971,
   0.1217076,
   0.2012748,
   0.3272739,
   0.5232196,
   0.8224455,
   1.271103,
   1.931546,
   2.885891,
   4.239408,
   6.123237,
   8.69576,
   12.14184,
   16.66909,
   22.50039,
   29.86199,
   38.96708,
   49.99511,
   63.06781,
   78.22374,
   95.39374,
   114.3804,
   134.8448,
   156.3029,
   178.1356,
   199.6111,
   219.9223,
   229.38,
   238.2344,
   246.386,
   253.7407,
   260.2118,
   265.7213,
   270.2019,
   273.5982,
   275.8675,
   276.9813,
   276.6364,
   274.6668,
   271.1858,
   266.2512,
   259.9442,
   252.367,
   243.6401,
   233.8993,
   223.2919,
   211.9732,
   200.1026,
   187.8401,
   175.3428,
   162.7614,
   150.2376,
   137.9017,
   125.8707,
   114.2467,
   103.1161,
   92.54929,
   82.60067,
   73.30912,
   64.6988,
   56.78039,
   49.55237,
   43.00256,
   37.10975,
   31.84533,
   27.17485,
   23.05964,
   19.45816,
   16.32732,
   13.6236,
   11.30402,
   9.326907,
   7.652552,
   6.243654,
   5.06565,
   4.086913,
   3.278835,
   2.615818,
   2.075198,
   1.6371,
   1.284266,
   1.00184,
   0.7771515,
   0.5994831,
   0.4598456,
   0.3507608,
   0.2660565,
   0.2006784,
   0.150519,
   0.1122654,
   0.08326532,
   0.06141103,
   0.04503939,
   0.03284751,
   0.0238219,
   0.01717964,
   0.01232014,
   0.008785797,
   0.006230323,
   0.004393431,
   0.003080781,
   0.002148235,
   0.00148959,
   0.001027106,
   0.0007042519,
   0.0007042519};
   graph = new TGraph(107,p_signal_fx29,p_signal_fy29);
   graph->SetName("p_signal");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);
   graph->SetLineColor(7);
   graph->SetLineStyle(6);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   graph->Draw("l");
   
   Double_t HistM_fx3012[30] = {
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
   Double_t HistM_fy3012[30] = {
   0,
   0,
   0,
   3,
   11,
   37,
   74,
   138,
   240,
   314,
   369,
   415,
   510,
   579,
   576,
   471,
   308,
   171,
   86,
   69,
   47,
   27,
   11,
   1,
   2,
   2,
   0,
   0,
   0,
   0};
   Double_t HistM_felx3012[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
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
   Double_t HistM_fely3012[30] = {
   0,
   0,
   0,
   1.632705,
   3.265579,
   6.055143,
   8.582844,
   11.25798,
   15,
   17.2271,
   18.71588,
   19.87768,
   22.08871,
   23.56761,
   23.50521,
   21.20829,
   17.05705,
   12.58625,
   9.255555,
   8.286444,
   6.831172,
   5.163771,
   3.265579,
   0.8272462,
   1.291815,
   1.291815,
   0,
   0,
   0,
   0};
   Double_t HistM_fehx3012[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
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
   Double_t HistM_fehy3012[30] = {
   1.147874,
   1.147874,
   1.147874,
   2.918186,
   4.416521,
   7.137555,
   9.641101,
   12.25798,
   16,
   18.2271,
   19.71588,
   20.87768,
   23.08871,
   24.56761,
   24.50521,
   22.20829,
   18.05705,
   13.58625,
   10.30959,
   9.346779,
   7.904289,
   6.260244,
   4.416521,
   2.299527,
   2.63786,
   2.63786,
   1.147874,
   1.147874,
   1.147874,
   1.147874};
   grae = new TGraphAsymmErrors(30,HistM_fx3012,HistM_fy3012,HistM_felx3012,HistM_fehx3012,HistM_fely3012,HistM_fehy3012);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   grae->Draw("p");
   
   TPaveText *pt = new TPaveText(0,0,0,0,"BRNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetLineWidth(2);
   pt->SetTextFont(132);
   pt->SetTextSize(0.07);
   TText *pt_LaTex = pt->AddText("#it{p}_{T} #in [4.5,5.5] GeV");
   pt->Draw();
   
   TH1D *frame_7fded7a9ccd0__12 = new TH1D("frame_7fded7a9ccd0__12","",100,-10.4,5.2);
   frame_7fded7a9ccd0__12->SetBinContent(1,633.746);
   frame_7fded7a9ccd0__12->SetMinimum(1);
   frame_7fded7a9ccd0__12->SetMaximum(5790);
   frame_7fded7a9ccd0__12->SetEntries(1);
   frame_7fded7a9ccd0__12->SetDirectory(0);
   frame_7fded7a9ccd0__12->SetStats(0);
   frame_7fded7a9ccd0__12->SetLineWidth(2);
   frame_7fded7a9ccd0__12->SetMarkerStyle(20);
   frame_7fded7a9ccd0__12->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fded7a9ccd0__12->GetXaxis()->SetNdivisions(505);
   frame_7fded7a9ccd0__12->GetXaxis()->SetLabelFont(132);
   frame_7fded7a9ccd0__12->GetXaxis()->SetLabelOffset(0.01);
   frame_7fded7a9ccd0__12->GetXaxis()->SetLabelSize(0.06);
   frame_7fded7a9ccd0__12->GetXaxis()->SetTitleSize(0.072);
   frame_7fded7a9ccd0__12->GetXaxis()->SetTitleOffset(0.95);
   frame_7fded7a9ccd0__12->GetXaxis()->SetTitleFont(132);
   frame_7fded7a9ccd0__12->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7fded7a9ccd0__12->GetYaxis()->SetLabelFont(132);
   frame_7fded7a9ccd0__12->GetYaxis()->SetLabelOffset(0.01);
   frame_7fded7a9ccd0__12->GetYaxis()->SetLabelSize(0.06);
   frame_7fded7a9ccd0__12->GetYaxis()->SetTitleSize(0.1);
   frame_7fded7a9ccd0__12->GetYaxis()->SetTitleOffset(0.6);
   frame_7fded7a9ccd0__12->GetYaxis()->SetTitleFont(132);
   frame_7fded7a9ccd0__12->GetZaxis()->SetLabelFont(132);
   frame_7fded7a9ccd0__12->GetZaxis()->SetLabelSize(0.06);
   frame_7fded7a9ccd0__12->GetZaxis()->SetTitleSize(0.072);
   frame_7fded7a9ccd0__12->GetZaxis()->SetTitleOffset(1.2);
   frame_7fded7a9ccd0__12->GetZaxis()->SetTitleFont(132);
   frame_7fded7a9ccd0__12->Draw("AXISSAME");
   pad1->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
