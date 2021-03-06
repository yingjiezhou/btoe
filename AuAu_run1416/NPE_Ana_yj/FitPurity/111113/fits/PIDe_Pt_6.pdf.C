void PIDe_Pt_6.pdf()
{
//=========Macro generated from canvas: c1/full fit
//=========  (Wed Aug 14 17:06:56 2019) by ROOT version 6.16/00
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
   
   TH1D *frame_7fa5a5ed5bb0__7 = new TH1D("frame_7fa5a5ed5bb0__7","",100,-10.4,5.2);
   frame_7fa5a5ed5bb0__7->SetBinContent(1,1609623);
   frame_7fa5a5ed5bb0__7->SetMinimum(1);
   frame_7fa5a5ed5bb0__7->SetMaximum(1.336344e+07);
   frame_7fa5a5ed5bb0__7->SetEntries(2);
   frame_7fa5a5ed5bb0__7->SetDirectory(0);
   frame_7fa5a5ed5bb0__7->SetStats(0);
   frame_7fa5a5ed5bb0__7->SetLineWidth(2);
   frame_7fa5a5ed5bb0__7->SetMarkerStyle(20);
   frame_7fa5a5ed5bb0__7->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fa5a5ed5bb0__7->GetXaxis()->SetNdivisions(505);
   frame_7fa5a5ed5bb0__7->GetXaxis()->SetLabelFont(132);
   frame_7fa5a5ed5bb0__7->GetXaxis()->SetLabelOffset(0.01);
   frame_7fa5a5ed5bb0__7->GetXaxis()->SetLabelSize(0.06);
   frame_7fa5a5ed5bb0__7->GetXaxis()->SetTitleSize(0.072);
   frame_7fa5a5ed5bb0__7->GetXaxis()->SetTitleOffset(0.95);
   frame_7fa5a5ed5bb0__7->GetXaxis()->SetTitleFont(132);
   frame_7fa5a5ed5bb0__7->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7fa5a5ed5bb0__7->GetYaxis()->SetLabelFont(132);
   frame_7fa5a5ed5bb0__7->GetYaxis()->SetLabelOffset(0.01);
   frame_7fa5a5ed5bb0__7->GetYaxis()->SetLabelSize(0.06);
   frame_7fa5a5ed5bb0__7->GetYaxis()->SetTitleSize(0.1);
   frame_7fa5a5ed5bb0__7->GetYaxis()->SetTitleOffset(0.6);
   frame_7fa5a5ed5bb0__7->GetYaxis()->SetTitleFont(132);
   frame_7fa5a5ed5bb0__7->GetZaxis()->SetLabelFont(132);
   frame_7fa5a5ed5bb0__7->GetZaxis()->SetLabelSize(0.06);
   frame_7fa5a5ed5bb0__7->GetZaxis()->SetTitleSize(0.072);
   frame_7fa5a5ed5bb0__7->GetZaxis()->SetTitleOffset(1.2);
   frame_7fa5a5ed5bb0__7->GetZaxis()->SetTitleFont(132);
   frame_7fa5a5ed5bb0__7->Draw("FUNC");
   
   Double_t HistM_fx3010[30] = {
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
   Double_t HistM_fy3010[30] = {
   137,
   1222,
   6693,
   28859,
   101947,
   268248,
   548009,
   854300,
   1130731,
   1260805,
   1311243,
   1336344,
   1291583,
   1016244,
   701269,
   392669,
   184641,
   86207,
   50312,
   36853,
   27017,
   15971,
   7478,
   2797,
   762,
   248,
   131,
   123,
   117,
   89};
   Double_t HistM_felx3010[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
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
   Double_t HistM_fely3010[30] = {
   11.21537,
   34.46069,
   81.31229,
   169.3801,
   318.7918,
   517.4269,
   739.7765,
   923.7836,
   1062.858,
   1122.356,
   1144.595,
   1155.504,
   1135.978,
   1007.589,
   836.9182,
   626.1333,
   429.199,
   293.1107,
   223.8039,
   191.472,
   163.8692,
   125.8774,
   85.97688,
   52.38903,
   27.10888,
   15.25595,
   10.95644,
   10.6018,
   10.3282,
   9.416226};
   Double_t HistM_fehx3010[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
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
   Double_t HistM_fehy3010[30] = {
   12.21537,
   35.46069,
   82.31229,
   170.3801,
   319.7918,
   518.4269,
   740.7765,
   924.7836,
   1063.858,
   1123.356,
   1145.595,
   1156.504,
   1136.978,
   1008.589,
   837.9182,
   627.1333,
   430.199,
   294.1107,
   224.8039,
   192.472,
   164.8692,
   126.8774,
   86.97688,
   53.38903,
   28.10888,
   16.25595,
   11.95644,
   11.6018,
   11.3282,
   10.46934};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(30,HistM_fx3010,HistM_fy3010,HistM_felx3010,HistM_fehx3010,HistM_fely3010,HistM_fehy3010);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   grae->Draw("p");
   
   Double_t PID_Curve_fx15[116] = {
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
   -6.325,
   -6.25,
   -6.175,
   -6.1,
   -6.025,
   -5.95,
   -5.875,
   -5.8,
   -5.65,
   -5.5,
   -5.35,
   -5.275,
   -5.2,
   -5.125,
   -5.05,
   -4.975,
   -4.9,
   -4.75,
   -4.675,
   -4.6,
   -4.525,
   -4.4875,
   -4.45,
   -4.4125,
   -4.375,
   -4.3375,
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
   Double_t PID_Curve_fy15[116] = {
   232.2629,
   416.1302,
   730.895,
   1258.345,
   2123.276,
   3510.897,
   5688.261,
   9028.931,
   14039.01,
   21381.13,
   31891.29,
   46582.04,
   66624.11,
   93299.12,
   127917.3,
   171698,
   225616.9,
   290230.3,
   365495.8,
   450614.4,
   543923.3,
   642867,
   744069.1,
   843512.5,
   936825.2,
   979809.9,
   1019655,
   1055892,
   1088114,
   1115992,
   1139297,
   1157916,
   1172079,
   1194676,
   1214009,
   1235601,
   1249445,
   1266510,
   1287502,
   1312808,
   1342344,
   1375426,
   1446145,
   1479129,
   1506640,
   1525555,
   1530864,
   1532974,
   1531614,
   1526566,
   1517675,
   1504855,
   1473758,
   1439538,
   1362481,
   1275451,
   1180578,
   1080252,
   976991.3,
   873307.4,
   771568,
   673880.1,
   581999.3,
   497272,
   420613.3,
   352517,
   293092.7,
   242122.2,
   199127.7,
   163442.4,
   134278.9,
   110789.7,
   92117.61,
   77434.95,
   65972.37,
   57037.9,
   50028.31,
   44434.17,
   39840.07,
   35920.96,
   32435.49,
   29216.9,
   26162.13,
   23219.7,
   20377.08,
   17648.23,
   15062.28,
   12653.68,
   10454.65,
   8489.828,
   6773.352,
   5307.979,
   4085.843,
   3090.35,
   2298.652,
   1684.253,
   1219.383,
   876.9096,
   631.7077,
   461.4819,
   347.1449,
   272.8627,
   225.892,
   196.3112,
   176.7075,
   161.8527,
   148.3744,
   134.4173,
   119.2947,
   103.1373,
   86.5599,
   70.3702,
   55.34242,
   42.07001,
   30.89687,
   30.89687};
   TGraph *graph = new TGraph(116,PID_Curve_fx15,PID_Curve_fy15);
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
   
   Double_t e_signal_fx16[120] = {
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
   Double_t e_signal_fy16[120] = {
   3.449075e-15,
   1.295424e-14,
   4.766409e-14,
   1.718069e-13,
   6.066804e-13,
   2.098695e-12,
   7.112278e-12,
   2.361229e-11,
   7.679582e-11,
   2.446848e-10,
   7.637418e-10,
   2.335372e-09,
   6.995771e-09,
   2.052982e-08,
   5.902074e-08,
   1.662242e-07,
   4.586209e-07,
   1.239606e-06,
   3.282337e-06,
   8.514376e-06,
   2.163678e-05,
   5.386445e-05,
   0.0001313657,
   0.0003138569,
   0.000734601,
   0.001684385,
   0.003783565,
   0.008325896,
   0.01794861,
   0.03790537,
   0.07842249,
   0.1589464,
   0.3155953,
   0.6138758,
   1.16977,
   2.183688,
   3.993471,
   7.154522,
   12.55685,
   21.58991,
   36.36561,
   60.00688,
   97.00212,
   153.6142,
   238.3151,
   362.1945,
   539.2648,
   786.5609,
   1123.913,
   1573.269,
   2157.463,
   2898.369,
   3333.574,
   3814.468,
   4342.356,
   4917.954,
   5541.29,
   6211.62,
   6927.337,
   7685.91,
   9316.564,
   11063.34,
   12870.24,
   14667.54,
   16375.62,
   17169.96,
   17910.53,
   18587.24,
   19190.62,
   19711.99,
   20143.72,
   20479.35,
   20713.82,
   20843.56,
   20866.56,
   20782.48,
   20592.62,
   20299.86,
   19908.67,
   19424.9,
   18855.71,
   18209.36,
   17494.99,
   16722.47,
   15902.1,
   14160.07,
   12352.25,
   10555.94,
   8837.262,
   7247.84,
   6513.363,
   5823.304,
   5179.659,
   4583.533,
   4035.219,
   3534.283,
   3079.662,
   2669.76,
   1975.665,
   1432.268,
   1017.197,
   707.7116,
   482.3668,
   322.0835,
   210.683,
   135.0084,
   84.75431,
   52.12343,
   31.40322,
   18.53469,
   10.71684,
   6.070408,
   3.36852,
   1.831177,
   0.9751956,
   0.5087719,
   0.2600306,
   0.1301955,
   0.06386122,
   0.06386122};
   graph = new TGraph(120,e_signal_fx16,e_signal_fy16);
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
   
   Double_t pi_signal_fx17[128] = {
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
   -5.725,
   -5.65,
   -5.575,
   -5.5,
   -5.425,
   -5.35,
   -5.3125,
   -5.275,
   -5.2375,
   -5.2,
   -5.1625,
   -5.125,
   -5.0875,
   -5.05,
   -5.0125,
   -4.975,
   -4.9375,
   -4.9,
   -4.825,
   -4.75,
   -4.675,
   -4.6375,
   -4.6,
   -4.5625,
   -4.525,
   -4.4875,
   -4.45,
   -4.4125,
   -4.375,
   -4.3375,
   -4.3,
   -4.225,
   -4.15,
   -4.075,
   -4,
   -3.925,
   -3.85,
   -3.775,
   -3.7,
   -3.625,
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
   Double_t pi_signal_fy17[128] = {
   2.949871e-27,
   1.403561e-25,
   6.024524e-24,
   2.3328e-22,
   8.148835e-21,
   2.567892e-19,
   7.299972e-18,
   1.872099e-16,
   4.331116e-15,
   9.039282e-14,
   1.701889e-12,
   2.890626e-11,
   4.429103e-10,
   6.122134e-09,
   7.634017e-08,
   8.587499e-07,
   8.71452e-06,
   7.977806e-05,
   0.0006588502,
   0.004908549,
   0.03299004,
   0.2000211,
   1.094037,
   5.398229,
   24.0289,
   96.48945,
   349.5336,
   1142.25,
   3367.416,
   5562.734,
   8955.618,
   14051.37,
   21486.1,
   32019.33,
   46503.2,
   55503.97,
   65821.71,
   77556.51,
   90796.96,
   105615.7,
   122064.5,
   140169.7,
   159927.5,
   181299.2,
   204207.9,
   228535.3,
   254119.5,
   308190.4,
   364263.9,
   419593.7,
   446006.6,
   471039.8,
   494285.4,
   515349.6,
   533863.4,
   549493.1,
   561950.7,
   571002.8,
   576477.3,
   578269.7,
   577072.1,
   573536,
   567704.5,
   559647.9,
   549463,
   537270.5,
   523213,
   507452.1,
   490165.3,
   471542.7,
   431092.9,
   387743.7,
   343117.2,
   298719.9,
   255864.4,
   215615.2,
   178761,
   145811,
   117012.3,
   92384.03,
   71760.61,
   54840.23,
   41232.18,
   30499.82,
   22196.38,
   15892.46,
   11194.99,
   7758.551,
   5290.068,
   3548.672,
   2342.04,
   1520.711,
   971.4561,
   610.5532,
   377.5267,
   229.6656,
   137.4574,
   80.94015,
   46.8904,
   26.72562,
   14.98634,
   8.267751,
   4.487486,
   2.396308,
   1.258943,
   0.6507193,
   0.3309063,
   0.1655543,
   0.08148913,
   0.03946234,
   0.01880139,
   0.008812945,
   0.004064209,
   0.001843975,
   0.0008231098,
   0.0003614802,
   0.0001561835,
   6.639111e-05,
   2.776569e-05,
   1.142434e-05,
   4.624634e-06,
   1.841822e-06,
   7.216756e-07,
   2.78202e-07,
   1.055121e-07,
   3.937028e-08,
   1.445302e-08,
   1.445302e-08};
   graph = new TGraph(128,pi_signal_fx17,pi_signal_fy17);
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
   
   Double_t pi2_signal_fx18[125] = {
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
   1.775,
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
   2.75,
   2.9,
   2.975,
   3.05,
   3.125,
   3.2,
   3.275,
   3.35,
   3.425,
   3.4625,
   3.5,
   3.5375,
   3.575,
   3.6125,
   3.65,
   3.6875,
   3.725,
   3.7625,
   3.8,
   3.875,
   3.95,
   4.025,
   4.1,
   4.175,
   4.25,
   4.4,
   4.55,
   4.625,
   4.7,
   4.775,
   4.85,
   4.925,
   5,
   5};
   Double_t pi2_signal_fy18[125] = {
   3.252383e-62,
   8.032723e-61,
   1.914745e-59,
   4.405006e-58,
   9.780681e-57,
   2.09594e-55,
   4.334869e-54,
   8.65287e-53,
   1.666985e-51,
   3.09949e-50,
   5.562065e-49,
   9.633167e-48,
   1.610235e-46,
   2.597746e-45,
   4.044746e-44,
   6.078174e-43,
   8.815401e-42,
   1.233952e-40,
   1.667023e-39,
   2.173563e-38,
   2.735206e-37,
   3.321965e-36,
   3.893922e-35,
   4.40521e-34,
   4.809868e-33,
   5.068587e-32,
   5.154991e-31,
   5.060064e-30,
   4.793706e-29,
   4.383025e-28,
   3.867797e-27,
   3.294129e-26,
   2.707726e-25,
   2.148108e-24,
   1.64473e-23,
   1.215403e-22,
   8.668287e-22,
   5.966689e-21,
   3.963882e-20,
   2.54153e-19,
   1.57274e-18,
   9.393034e-18,
   5.414296e-17,
   3.012072e-16,
   1.617245e-15,
   8.380569e-15,
   4.191393e-14,
   2.023161e-13,
   9.425183e-13,
   4.237759e-12,
   1.83895e-11,
   7.701775e-11,
   3.113142e-10,
   1.214491e-09,
   4.572741e-09,
   1.661676e-08,
   5.82778e-08,
   1.972637e-07,
   6.44434e-07,
   2.031875e-06,
   6.183047e-06,
   1.815914e-05,
   5.147252e-05,
   0.000140813,
   0.0003717895,
   0.0009474116,
   0.002330062,
   0.005530744,
   0.0126703,
   0.02801413,
   0.05977985,
   0.1231175,
   0.2447212,
   0.4694732,
   0.869235,
   1.553284,
   2.67887,
   4.459022,
   7.163327,
   8.959269,
   11.1065,
   13.64673,
   16.61984,
   20.06188,
   24.00289,
   28.4644,
   33.45704,
   38.97801,
   45.00893,
   51.5139,
   58.43822,
   73.22891,
   88.56361,
   96.10852,
   103.3749,
   110.2086,
   116.4562,
   121.9709,
   126.6184,
   130.2819,
   131.7143,
   132.8674,
   133.7336,
   134.3072,
   134.5844,
   134.5634,
   134.2443,
   133.6293,
   132.7223,
   131.5294,
   128.3191,
   124.0812,
   118.9236,
   112.9735,
   106.3731,
   99.27365,
   84.19353,
   68.9145,
   61.52431,
   54.44146,
   47.74847,
   41.50841,
   35.7651,
   30.54426,
   30.54426};
   graph = new TGraph(125,pi2_signal_fx18,pi2_signal_fy18);
   graph->SetName("pi2_signal");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);
   graph->SetLineColor(6);
   graph->SetLineStyle(6);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   graph->Draw("l");
   
   Double_t k_signal_fx19[112] = {
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
   -7.675,
   -7.6,
   -7.525,
   -7.45,
   -7.375,
   -7.3,
   -7.225,
   -7.15,
   -7,
   -6.85,
   -6.7,
   -6.55,
   -6.4,
   -6.325,
   -6.25,
   -6.175,
   -6.1,
   -6.025,
   -5.95,
   -5.875,
   -5.8,
   -5.65,
   -5.5,
   -5.35,
   -5.2,
   -5.05,
   -4.9,
   -4.825,
   -4.75,
   -4.675,
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
   Double_t k_signal_fy19[112] = {
   77.11458,
   145.8711,
   269.7285,
   487.4984,
   861.1516,
   1486.699,
   2508.34,
   4135.775,
   6663.878,
   10492.84,
   16145.64,
   24278.31,
   35677.27,
   51237.56,
   71916.3,
   98658.07,
   114569.6,
   132292.4,
   151891.6,
   173409.2,
   196859.1,
   222223.9,
   249451.2,
   278450.4,
   341202.2,
   408945.6,
   479522,
   550250,
   618105.8,
   649976.7,
   679965,
   707710,
   732879.4,
   755177.4,
   774351.4,
   790197.7,
   802765.5,
   824407.2,
   842229.8,
   855477.8,
   863418.3,
   865393.5,
   860875,
   856063.5,
   849514.4,
   841219.1,
   831184.4,
   806005.9,
   774357,
   736863.2,
   694367.9,
   647886.8,
   598550.2,
   547539.1,
   496020.4,
   445087.6,
   395711.3,
   348703.2,
   304694.7,
   264129.9,
   227272.7,
   194223.6,
   164944,
   139285.4,
   117018,
   97859.51,
   81499.29,
   67618.89,
   55907.39,
   46072.22,
   37845.87,
   30989.12,
   25291.83,
   20571.85,
   16672.9,
   13461.81,
   10825.64,
   8668.936,
   6911.095,
   5484.174,
   4330.939,
   3403.238,
   2660.633,
   2069.247,
   1600.795,
   1231.753,
   942.6532,
   717.4657,
   543.0714,
   408.7975,
   306.0181,
   227.8072,
   168.6418,
   124.1473,
   90.88271,
   66.16009,
   47.89395,
   34.47737,
   24.68063,
   17.56898,
   12.4367,
   8.754504,
   6.1281,
   4.265677,
   2.952691,
   2.03243,
   1.391173,
   0.9469225,
   0.6409371,
   0.4314041,
   0.2887492,
   0.2887492};
   graph = new TGraph(112,k_signal_fx19,k_signal_fy19);
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
   
   Double_t p_signal_fx20[115] = {
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
   Double_t p_signal_fy20[115] = {
   155.1483,
   270.2591,
   461.1665,
   770.8466,
   1262.124,
   2024.198,
   3179.921,
   4893.156,
   7375.133,
   10888.29,
   15745.65,
   22303.73,
   30946.84,
   42061.56,
   48658.6,
   56000.97,
   64120.24,
   73039.91,
   82773.81,
   93324.49,
   104681.7,
   116821.1,
   143271.9,
   172164,
   202721,
   233921.2,
   264546,
   293257,
   306468,
   318695.3,
   329784.4,
   339593.2,
   347995.8,
   354885,
   360175,
   363803.1,
   365731.1,
   365946.4,
   364461.4,
   361313.3,
   356563,
   350293,
   342605.6,
   333619.6,
   323467.9,
   312294,
   287486.2,
   260430.7,
   232364.7,
   204411.7,
   177468.1,
   152216,
   129117,
   108428.4,
   90233.25,
   74478.67,
   61016.4,
   49639.66,
   40113.94,
   32200.2,
   25670.38,
   20316.32,
   15953.65,
   12422.15,
   9584.123,
   7321.843,
   5534.853,
   4137.484,
   3056.795,
   2230.912,
   1607.69,
   1143.598,
   802.7303,
   555.8909,
   379.7095,
   255.7944,
   169.9252,
   111.3046,
   71.88312,
   45.76956,
   28.73065,
   17.77954,
   10.84657,
   6.52311,
   3.867246,
   2.260115,
   1.302081,
   0.7394734,
   0.4139834,
   0.2284642,
   0.1242876,
   0.06665166,
   0.03523447,
   0.01836107,
   0.009431945,
   0.004776147,
   0.002384115,
   0.00117314,
   0.0005690431,
   0.0002720906,
   0.0001282493,
   5.958943e-05,
   2.729333e-05,
   1.2323e-05,
   5.48466e-06,
   2.406333e-06,
   1.040722e-06,
   4.436971e-07,
   1.864711e-07,
   7.72519e-08,
   3.154858e-08,
   1.270058e-08,
   5.04011e-09,
   1.971648e-09,
   1.971648e-09};
   graph = new TGraph(115,p_signal_fx20,p_signal_fy20);
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
   
   Double_t HistM1_fx3011[30] = {
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
   Double_t HistM1_fy3011[30] = {
   12,
   246,
   6693,
   6318,
   14869,
   26216,
   35310,
   46368,
   57932,
   55399,
   42017,
   28614,
   16146,
   7756,
   5103,
   3233,
   1885,
   1167,
   16644,
   33196,
   26820,
   15971,
   7478,
   2797,
   762,
   248,
   131,
   123,
   117,
   89};
   Double_t HistM1_felx3011[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
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
   Double_t HistM1_fely3011[30] = {
   3.415266,
   15.19235,
   81.31229,
   78.98742,
   121.4395,
   161.4143,
   187.4102,
   214.8329,
   240.1912,
   234.8705,
   204.4811,
   168.6575,
   126.5679,
   87.56957,
   70.93704,
   56.36167,
   42.91947,
   33.66504,
   128.5126,
   181.6984,
   163.2689,
   125.8774,
   85.97688,
   52.38903,
   27.10888,
   15.25595,
   10.95644,
   10.6018,
   10.3282,
   9.416226};
   Double_t HistM1_fehx3011[30] = {
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
   0.26,
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
   Double_t HistM1_fehy3011[30] = {
   4.559819,
   16.19235,
   82.31229,
   79.98742,
   122.4395,
   162.4143,
   188.4102,
   215.8329,
   241.1912,
   235.8705,
   205.4811,
   169.6575,
   127.5679,
   88.56957,
   71.93704,
   57.36167,
   43.91947,
   34.66504,
   129.5126,
   182.6984,
   164.2689,
   126.8774,
   86.97688,
   53.38903,
   28.10888,
   16.25595,
   11.95644,
   11.6018,
   11.3282,
   10.46934};
   grae = new TGraphAsymmErrors(30,HistM1_fx3011,HistM1_fy3011,HistM1_felx3011,HistM1_fehx3011,HistM1_fely3011,HistM1_fehy3011);
   grae->SetName("HistM1");
   grae->SetTitle("Histogram of dataHist1_plot__PID");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#cccccc");
   grae->SetLineColor(ci);
   grae->SetLineWidth(2);

   ci = TColor::GetColor("#cccccc");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(8);
   grae->Draw("p");
   
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
   137,
   1222,
   6693,
   28859,
   101947,
   268248,
   548009,
   854300,
   1130731,
   1260805,
   1311243,
   1336344,
   1291583,
   1016244,
   701269,
   392669,
   184641,
   86207,
   50312,
   36853,
   27017,
   15971,
   7478,
   2797,
   762,
   248,
   131,
   123,
   117,
   89};
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
   11.21537,
   34.46069,
   81.31229,
   169.3801,
   318.7918,
   517.4269,
   739.7765,
   923.7836,
   1062.858,
   1122.356,
   1144.595,
   1155.504,
   1135.978,
   1007.589,
   836.9182,
   626.1333,
   429.199,
   293.1107,
   223.8039,
   191.472,
   163.8692,
   125.8774,
   85.97688,
   52.38903,
   27.10888,
   15.25595,
   10.95644,
   10.6018,
   10.3282,
   9.416226};
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
   12.21537,
   35.46069,
   82.31229,
   170.3801,
   319.7918,
   518.4269,
   740.7765,
   924.7836,
   1063.858,
   1123.356,
   1145.595,
   1156.504,
   1136.978,
   1008.589,
   837.9182,
   627.1333,
   430.199,
   294.1107,
   224.8039,
   192.472,
   164.8692,
   126.8774,
   86.97688,
   53.38903,
   28.10888,
   16.25595,
   11.95644,
   11.6018,
   11.3282,
   10.46934};
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
   TText *pt_LaTex = pt->AddText("#it{p}_{T} #in [2.5,3.5] GeV");
   pt->Draw();
   
   TH1D *frame_7fa5a5ed5bb0__8 = new TH1D("frame_7fa5a5ed5bb0__8","",100,-10.4,5.2);
   frame_7fa5a5ed5bb0__8->SetBinContent(1,1609623);
   frame_7fa5a5ed5bb0__8->SetMinimum(1);
   frame_7fa5a5ed5bb0__8->SetMaximum(1.336344e+07);
   frame_7fa5a5ed5bb0__8->SetEntries(2);
   frame_7fa5a5ed5bb0__8->SetDirectory(0);
   frame_7fa5a5ed5bb0__8->SetStats(0);
   frame_7fa5a5ed5bb0__8->SetLineWidth(2);
   frame_7fa5a5ed5bb0__8->SetMarkerStyle(20);
   frame_7fa5a5ed5bb0__8->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fa5a5ed5bb0__8->GetXaxis()->SetNdivisions(505);
   frame_7fa5a5ed5bb0__8->GetXaxis()->SetLabelFont(132);
   frame_7fa5a5ed5bb0__8->GetXaxis()->SetLabelOffset(0.01);
   frame_7fa5a5ed5bb0__8->GetXaxis()->SetLabelSize(0.06);
   frame_7fa5a5ed5bb0__8->GetXaxis()->SetTitleSize(0.072);
   frame_7fa5a5ed5bb0__8->GetXaxis()->SetTitleOffset(0.95);
   frame_7fa5a5ed5bb0__8->GetXaxis()->SetTitleFont(132);
   frame_7fa5a5ed5bb0__8->GetYaxis()->SetTitle("Events / ( 0.52 )");
   frame_7fa5a5ed5bb0__8->GetYaxis()->SetLabelFont(132);
   frame_7fa5a5ed5bb0__8->GetYaxis()->SetLabelOffset(0.01);
   frame_7fa5a5ed5bb0__8->GetYaxis()->SetLabelSize(0.06);
   frame_7fa5a5ed5bb0__8->GetYaxis()->SetTitleSize(0.1);
   frame_7fa5a5ed5bb0__8->GetYaxis()->SetTitleOffset(0.6);
   frame_7fa5a5ed5bb0__8->GetYaxis()->SetTitleFont(132);
   frame_7fa5a5ed5bb0__8->GetZaxis()->SetLabelFont(132);
   frame_7fa5a5ed5bb0__8->GetZaxis()->SetLabelSize(0.06);
   frame_7fa5a5ed5bb0__8->GetZaxis()->SetTitleSize(0.072);
   frame_7fa5a5ed5bb0__8->GetZaxis()->SetTitleOffset(1.2);
   frame_7fa5a5ed5bb0__8->GetZaxis()->SetTitleFont(132);
   frame_7fa5a5ed5bb0__8->Draw("AXISSAME");
   pad1->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
