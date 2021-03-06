void PIDe_Pt_7.pdf()
{
//=========Macro generated from canvas: c1/full fit
//=========  (Mon Jul 29 16:36:34 2019) by ROOT version 6.19/01
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
   
   TH1D *frame_7fa769d8bb00__13 = new TH1D("frame_7fa769d8bb00__13","",100,-10.22667,5.026667);
   frame_7fa769d8bb00__13->SetBinContent(1,120447.1);
   frame_7fa769d8bb00__13->SetMinimum(1);
   frame_7fa769d8bb00__13->SetMaximum(1048990);
   frame_7fa769d8bb00__13->SetEntries(2);
   frame_7fa769d8bb00__13->SetDirectory(0);
   frame_7fa769d8bb00__13->SetStats(0);
   frame_7fa769d8bb00__13->SetLineWidth(2);
   frame_7fa769d8bb00__13->SetMarkerStyle(20);
   frame_7fa769d8bb00__13->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fa769d8bb00__13->GetXaxis()->SetNdivisions(505);
   frame_7fa769d8bb00__13->GetXaxis()->SetLabelFont(132);
   frame_7fa769d8bb00__13->GetXaxis()->SetLabelOffset(0.01);
   frame_7fa769d8bb00__13->GetXaxis()->SetLabelSize(0.06);
   frame_7fa769d8bb00__13->GetXaxis()->SetTitleSize(0.072);
   frame_7fa769d8bb00__13->GetXaxis()->SetTitleOffset(0.95);
   frame_7fa769d8bb00__13->GetXaxis()->SetTitleFont(132);
   frame_7fa769d8bb00__13->GetYaxis()->SetTitle("Events / ( 0.693333 )");
   frame_7fa769d8bb00__13->GetYaxis()->SetLabelFont(132);
   frame_7fa769d8bb00__13->GetYaxis()->SetLabelOffset(0.01);
   frame_7fa769d8bb00__13->GetYaxis()->SetLabelSize(0.06);
   frame_7fa769d8bb00__13->GetYaxis()->SetTitleSize(0.1);
   frame_7fa769d8bb00__13->GetYaxis()->SetTitleOffset(0.6);
   frame_7fa769d8bb00__13->GetYaxis()->SetTitleFont(132);
   frame_7fa769d8bb00__13->GetZaxis()->SetLabelFont(132);
   frame_7fa769d8bb00__13->GetZaxis()->SetLabelSize(0.06);
   frame_7fa769d8bb00__13->GetZaxis()->SetTitleSize(0.072);
   frame_7fa769d8bb00__13->GetZaxis()->SetTitleOffset(1.2);
   frame_7fa769d8bb00__13->GetZaxis()->SetTitleFont(132);
   frame_7fa769d8bb00__13->Draw("FUNC");
   
   Double_t HistM_fx3019[22] = {
   -9.88,
   -9.186667,
   -8.493333,
   -7.8,
   -7.106667,
   -6.413333,
   -5.72,
   -5.026667,
   -4.333333,
   -3.64,
   -2.946667,
   -2.253333,
   -1.56,
   -0.8666667,
   -0.1733333,
   0.52,
   1.213333,
   1.906667,
   2.6,
   3.293333,
   3.986667,
   4.68};
   Double_t HistM_fy3019[22] = {
   14,
   266,
   2055,
   9215,
   28215,
   55041,
   74866,
   82624,
   94437,
   104899,
   91485,
   55422,
   23158,
   9934,
   5981,
   3466,
   1441,
   420,
   62,
   6,
   4,
   6};
   Double_t HistM_felx3019[22] = {
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667};
   Double_t HistM_fely3019[22] = {
   3.6965,
   15.81717,
   44.83487,
   95.49609,
   167.474,
   234.1087,
   273.117,
   286.9443,
   306.8064,
   323.3815,
   301.9653,
   234.9193,
   151.6783,
   99.17071,
   76.83854,
   58.37487,
   37.4638,
   20,
   7.852713,
   2.379931,
   1.914339,
   2.379931};
   Double_t HistM_fehx3019[22] = {
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667};
   Double_t HistM_fehy3019[22] = {
   4.830381,
   16.81717,
   45.83487,
   96.49609,
   168.474,
   235.1087,
   274.117,
   287.9443,
   307.8064,
   324.3815,
   302.9653,
   235.9193,
   152.6783,
   100.1707,
   77.83854,
   59.37487,
   38.4638,
   21,
   8.916365,
   3.583642,
   3.162753,
   3.583642};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(22,HistM_fx3019,HistM_fy3019,HistM_felx3019,HistM_fehx3019,HistM_fely3019,HistM_fehy3019);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillStyle(1000);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   grae->Draw("p");
   
   Double_t PID_Curve_fx29[139] = {
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
   -4.675,
   -4.6375,
   -4.6,
   -4.58125,
   -4.5625,
   -4.54375,
   -4.525,
   -4.50625,
   -4.4875,
   -4.46875,
   -4.45,
   -4.375,
   -4.35625,
   -4.3375,
   -4.31875,
   -4.3,
   -4.225,
   -4.15,
   -4.075,
   -4,
   -3.925,
   -3.85,
   -3.775,
   -3.7,
   -3.55,
   -3.4,
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
   -0.175,
   -0.1,
   -0.025,
   0.05,
   0.125,
   0.2,
   0.275,
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
   Double_t PID_Curve_fy29[139] = {
   3.510432,
   5.663885,
   9.249681,
   15.16306,
   24.7756,
   40.12691,
   64.15625,
   100.9613,
   156.0569,
   236.5898,
   351.4451,
   511.1685,
   727.6186,
   1013.275,
   1380.161,
   1838.381,
   2394.368,
   3048.996,
   3795.816,
   4619.717,
   5496.332,
   6392.451,
   7267.612,
   8076.846,
   8774.368,
   9317.828,
   9672.567,
   9815.308,
   9776.912,
   9622.993,
   9360.235,
   8998.398,
   8550.756,
   8033.566,
   7465.538,
   6872.504,
   6668.011,
   6791.261,
   7459.419,
   8207.029,
   9402.18,
   11210.68,
   13816.03,
   17397.71,
   22098.68,
   27984.86,
   35002.84,
   67812.77,
   74373.74,
   79001.03,
   81227.81,
   81340.08,
   80734.01,
   79613.83,
   78002.66,
   75934.59,
   73453.72,
   70612.84,
   67471.92,
   64096.36,
   56919.29,
   49644.91,
   42811.63,
   39710.92,
   36889.79,
   34391.8,
   32253.66,
   30505.17,
   29169.4,
   28262.98,
   27796.46,
   27774.8,
   28197.83,
   29060.69,
   30354.24,
   32065.47,
   34177.74,
   36671.02,
   39522.06,
   42704.48,
   46188.85,
   49942.74,
   53930.74,
   62453.3,
   71418.5,
   80451.87,
   89154.91,
   93255.74,
   97122.93,
   100708.6,
   103967.4,
   106857.6,
   109341.2,
   111385.3,
   112962.5,
   114051.5,
   114637.2,
   114711.6,
   114273.3,
   113328.2,
   111888.6,
   109973.6,
   107608.1,
   104822.8,
   101653.1,
   98138.53,
   94321.81,
   85964.37,
   76955.48,
   67666.73,
   58442.03,
   49578.08,
   41311.26,
   33811.27,
   27181.21,
   21462.99,
   16646.62,
   12681.66,
   9489.437,
   6974.596,
   5035.146,
   3570.421,
   2486.802,
   1701.287,
   1143.217,
   754.5615,
   489.1878,
   311.5099,
   194.8426,
   119.7049,
   72.23656,
   42.81736,
   24.92883,
   14.25623,
   8.008122,
   4.418588,
   2.394794,
   1.274946,
   1.274946};
   TGraph *graph = new TGraph(139,PID_Curve_fx29,PID_Curve_fy29);
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
   
   Double_t e_signal_fx30[112] = {
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
   -0.175,
   -0.1,
   -0.025,
   0.05,
   0.125,
   0.2,
   0.275,
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
   Double_t e_signal_fy30[112] = {
   8.945016e-12,
   2.808801e-11,
   8.663132e-11,
   2.624478e-10,
   7.809531e-10,
   2.282554e-09,
   6.552864e-09,
   1.847802e-08,
   5.117921e-08,
   1.392342e-07,
   3.720593e-07,
   9.765455e-07,
   2.517601e-06,
   6.375222e-06,
   1.585688e-05,
   3.873953e-05,
   9.296189e-05,
   0.0002191137,
   0.0005072806,
   0.001153562,
   0.002576604,
   0.005652864,
   0.01218157,
   0.02578412,
   0.05360623,
   0.1094693,
   0.2195752,
   0.4326019,
   0.8371583,
   1.591259,
   2.9709,
   5.448153,
   9.813515,
   17.36257,
   30.17292,
   51.50328,
   86.3508,
   142.204,
   230.0231,
   365.4645,
   570.3388,
   874.248,
   1316.287,
   1946.616,
   2827.64,
   4034.429,
   5653.977,
   7782.876,
   10523.01,
   13975.08,
   18229.82,
   23357.41,
   29395.5,
   36337.18,
   44120.01,
   52617.95,
   61637.7,
   70920.68,
   80151.83,
   88975,
   93116.27,
   97014.49,
   100623.9,
   103900.9,
   106804.8,
   109299,
   111351.1,
   112934.5,
   114028.2,
   114617.7,
   114694.9,
   114259,
   113315.7,
   111877.7,
   109963.9,
   107599.5,
   104815.2,
   101646.2,
   98132.32,
   94316.21,
   85959.81,
   76951.77,
   67663.71,
   58439.57,
   49576.09,
   41309.66,
   33809.98,
   27180.18,
   21462.18,
   16645.98,
   12681.16,
   9489.045,
   6974.293,
   5034.912,
   3570.242,
   2486.666,
   1701.184,
   1143.139,
   754.5031,
   489.1443,
   311.4778,
   194.8189,
   119.6876,
   72.22397,
   42.80826,
   24.92228,
   14.25155,
   8.0048,
   4.416242,
   2.393147,
   1.273796,
   1.273796};
   graph = new TGraph(112,e_signal_fx30,e_signal_fy30);
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
   
   Double_t pi_signal_fx31[128] = {
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
   -4.675,
   -4.6375,
   -4.61875,
   -4.6,
   -4.58125,
   -4.5625,
   -4.54375,
   -4.525,
   -4.50625,
   -4.4875,
   -4.46875,
   -4.45,
   -4.375,
   -4.35625,
   -4.3375,
   -4.31875,
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
   -2.275,
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
   Double_t pi_signal_fy31[128] = {
   1.323362,
   1.646292,
   2.03611,
   2.503579,
   3.060465,
   3.719456,
   4.494044,
   5.398353,
   6.446902,
   7.654324,
   9.035007,
   10.60269,
   12.37,
   14.34793,
   16.5453,
   18.96819,
   21.61938,
   24.49776,
   27.59787,
   30.9094,
   34.41689,
   38.09944,
   41.93064,
   45.87861,
   49.90626,
   53.97165,
   58.02863,
   62.02758,
   65.91637,
   69.64143,
   73.14894,
   76.3861,
   79.30243,
   81.85112,
   83.99256,
   90.84212,
   190.498,
   465.6017,
   772.5314,
   1284.963,
   2107.811,
   3377.892,
   5260.967,
   7940.485,
   11595.87,
   16370.04,
   22328.87,
   29418.88,
   62509.77,
   69138.91,
   73833.43,
   76126.46,
   76303.93,
   75946.92,
   75054.13,
   73644.49,
   71747.58,
   69402.62,
   66657.07,
   63565.1,
   60185.76,
   56581.16,
   52814.53,
   45043.34,
   37336.44,
   33631.54,
   30079.57,
   26712.19,
   23553.92,
   20622.24,
   17928,
   15475.89,
   13265.2,
   11290.5,
   9542.535,
   8008.967,
   6675.223,
   5525.219,
   4542.031,
   3007.611,
   1939.578,
   1219.642,
   749.2872,
   451.1662,
   267.6189,
   157.6404,
   93.31727,
   56.41502,
   35.48004,
   23.58354,
   16.68256,
   12.49798,
   9.78585,
   7.886508,
   6.457936,
   5.324645,
   4.395527,
   3.62095,
   2.971226,
   2.426231,
   1.970595,
   1.591567,
   1.278094,
   1.020438,
   0.8100004,
   0.6392248,
   0.5015214,
   0.3911938,
   0.3033616,
   0.2338812,
   0.1792652,
   0.1366037,
   0.1034892,
   0.07794596,
   0.05836575,
   0.04344986,
   0.03215768,
   0.02366175,
   0.01730912,
   0.01258836,
   0.009101839,
   0.006542671,
   0.004675704,
   0.00332204,
   0.002346543,
   0.001647852,
   0.001150466,
   0.001150466};
   graph = new TGraph(128,pi_signal_fx31,pi_signal_fy31);
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
   
   Double_t p_signal_fx32[117] = {
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
   Double_t p_signal_fy32[117] = {
   2.18707,
   4.017593,
   7.213571,
   12.65948,
   21.71513,
   36.40746,
   59.6622,
   95.56291,
   149.61,
   228.9354,
   342.4101,
   500.5658,
   715.2486,
   998.9275,
   1170.45,
   1363.616,
   1579.616,
   1819.413,
   2083.682,
   2372.749,
   2686.534,
   3024.498,
   3385.591,
   3768.217,
   4588.807,
   5461.912,
   6354.345,
   7225.669,
   7639.451,
   8030.941,
   8394.428,
   8724.409,
   9015.736,
   9263.747,
   9464.386,
   9614.318,
   9711.02,
   9752.848,
   9746.478,
   9710.158,
   9645.059,
   9551.76,
   9431.092,
   9284.115,
   9112.111,
   8916.564,
   8699.134,
   8461.64,
   7934.353,
   7351.372,
   6730.159,
   6088.105,
   5441.755,
   4806.132,
   4194.232,
   3616.672,
   3081.526,
   2594.313,
   2158.137,
   1773.926,
   1440.761,
   1156.241,
   916.8639,
   718.3916,
   556.1828,
   425.4748,
   321.6104,
   240.2074,
   177.273,
   129.2703,
   93.14398,
   66.31486,
   46.65164,
   32.4282,
   22.27301,
   15.11592,
   10.13656,
   6.716553,
   4.397463,
   2.844841,
   1.818502,
   1.148601,
   0.7168446,
   0.4420594,
   0.2693619,
   0.1621779,
   0.09648218,
   0.0567156,
   0.0329426,
   0.01890659,
   0.01072182,
   0.006007913,
   0.003326431,
   0.00181984,
   0.0009837564,
   0.0005254617,
   0.0002773276,
   0.0001446247,
   7.452246e-05,
   3.794222e-05,
   1.908714e-05,
   9.486944e-06,
   4.658527e-06,
   2.259691e-06,
   1.082461e-06,
   5.11813e-07,
   2.386122e-07,
   1.094564e-07,
   4.918945e-08,
   2.145687e-08,
   8.895734e-09,
   3.318163e-09,
   9.116679e-10,
   0,
   0,
   0,
   0};
   graph = new TGraph(117,p_signal_fx32,p_signal_fy32);
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
   
   Double_t HistM1_fx3020[22] = {
   -9.88,
   -9.186667,
   -8.493333,
   -7.8,
   -7.106667,
   -6.413333,
   -5.72,
   -5.026667,
   -4.333333,
   -3.64,
   -2.946667,
   -2.253333,
   -1.56,
   -0.8666667,
   -0.1733333,
   0.52,
   1.213333,
   1.906667,
   2.6,
   3.293333,
   3.986667,
   4.68};
   Double_t HistM1_fy3020[22] = {
   0,
   134,
   908,
   3980,
   12821,
   24459,
   25354,
   16242,
   4095,
   229,
   0,
   2266,
   14072,
   9910,
   5981,
   3466,
   1437,
   376,
   40,
   6,
   2,
   2};
   Double_t HistM1_felx3020[22] = {
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667};
   Double_t HistM1_fely3020[22] = {
   0,
   11.08663,
   29.63719,
   62.58922,
   112.731,
   155.8945,
   158.7302,
   126.9451,
   63.49414,
   14.641,
   0,
   47.10515,
   118.1265,
   99.05024,
   76.83854,
   58.37487,
   37.41108,
   18.89716,
   6.298,
   2.379931,
   1.291815,
   1.291815};
   Double_t HistM1_fehx3020[22] = {
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667};
   Double_t HistM1_fehy3020[22] = {
   1.147874,
   12.08663,
   30.63719,
   63.58922,
   113.731,
   156.8945,
   159.7302,
   127.9451,
   64.49414,
   15.641,
   1.147874,
   48.10515,
   119.1265,
   100.0502,
   77.83854,
   59.37487,
   38.41108,
   19.89716,
   7.377261,
   3.583642,
   2.63786,
   2.63786};
   grae = new TGraphAsymmErrors(22,HistM1_fx3020,HistM1_fy3020,HistM1_felx3020,HistM1_fehx3020,HistM1_fely3020,HistM1_fehy3020);
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
   
   Double_t HistM_fx3021[22] = {
   -9.88,
   -9.186667,
   -8.493333,
   -7.8,
   -7.106667,
   -6.413333,
   -5.72,
   -5.026667,
   -4.333333,
   -3.64,
   -2.946667,
   -2.253333,
   -1.56,
   -0.8666667,
   -0.1733333,
   0.52,
   1.213333,
   1.906667,
   2.6,
   3.293333,
   3.986667,
   4.68};
   Double_t HistM_fy3021[22] = {
   14,
   266,
   2055,
   9215,
   28215,
   55041,
   74866,
   82624,
   94437,
   104899,
   91485,
   55422,
   23158,
   9934,
   5981,
   3466,
   1441,
   420,
   62,
   6,
   4,
   6};
   Double_t HistM_felx3021[22] = {
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667};
   Double_t HistM_fely3021[22] = {
   3.6965,
   15.81717,
   44.83487,
   95.49609,
   167.474,
   234.1087,
   273.117,
   286.9443,
   306.8064,
   323.3815,
   301.9653,
   234.9193,
   151.6783,
   99.17071,
   76.83854,
   58.37487,
   37.4638,
   20,
   7.852713,
   2.379931,
   1.914339,
   2.379931};
   Double_t HistM_fehx3021[22] = {
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667,
   0.3466667};
   Double_t HistM_fehy3021[22] = {
   4.830381,
   16.81717,
   45.83487,
   96.49609,
   168.474,
   235.1087,
   274.117,
   287.9443,
   307.8064,
   324.3815,
   302.9653,
   235.9193,
   152.6783,
   100.1707,
   77.83854,
   59.37487,
   38.4638,
   21,
   8.916365,
   3.583642,
   3.162753,
   3.583642};
   grae = new TGraphAsymmErrors(22,HistM_fx3021,HistM_fy3021,HistM_felx3021,HistM_fehx3021,HistM_fely3021,HistM_fehy3021);
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
   TText *pt_LaTex = pt->AddText("#it{p}_{T} #in [3.5,4.5] GeV");
   pt->Draw();
   
   TH1D *frame_7fa769d8bb00__14 = new TH1D("frame_7fa769d8bb00__14","",100,-10.22667,5.026667);
   frame_7fa769d8bb00__14->SetBinContent(1,120447.1);
   frame_7fa769d8bb00__14->SetMinimum(1);
   frame_7fa769d8bb00__14->SetMaximum(1048990);
   frame_7fa769d8bb00__14->SetEntries(2);
   frame_7fa769d8bb00__14->SetDirectory(0);
   frame_7fa769d8bb00__14->SetStats(0);
   frame_7fa769d8bb00__14->SetLineWidth(2);
   frame_7fa769d8bb00__14->SetMarkerStyle(20);
   frame_7fa769d8bb00__14->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_7fa769d8bb00__14->GetXaxis()->SetNdivisions(505);
   frame_7fa769d8bb00__14->GetXaxis()->SetLabelFont(132);
   frame_7fa769d8bb00__14->GetXaxis()->SetLabelOffset(0.01);
   frame_7fa769d8bb00__14->GetXaxis()->SetLabelSize(0.06);
   frame_7fa769d8bb00__14->GetXaxis()->SetTitleSize(0.072);
   frame_7fa769d8bb00__14->GetXaxis()->SetTitleOffset(0.95);
   frame_7fa769d8bb00__14->GetXaxis()->SetTitleFont(132);
   frame_7fa769d8bb00__14->GetYaxis()->SetTitle("Events / ( 0.693333 )");
   frame_7fa769d8bb00__14->GetYaxis()->SetLabelFont(132);
   frame_7fa769d8bb00__14->GetYaxis()->SetLabelOffset(0.01);
   frame_7fa769d8bb00__14->GetYaxis()->SetLabelSize(0.06);
   frame_7fa769d8bb00__14->GetYaxis()->SetTitleSize(0.1);
   frame_7fa769d8bb00__14->GetYaxis()->SetTitleOffset(0.6);
   frame_7fa769d8bb00__14->GetYaxis()->SetTitleFont(132);
   frame_7fa769d8bb00__14->GetZaxis()->SetLabelFont(132);
   frame_7fa769d8bb00__14->GetZaxis()->SetLabelSize(0.06);
   frame_7fa769d8bb00__14->GetZaxis()->SetTitleSize(0.072);
   frame_7fa769d8bb00__14->GetZaxis()->SetTitleOffset(1.2);
   frame_7fa769d8bb00__14->GetZaxis()->SetTitleFont(132);
   frame_7fa769d8bb00__14->Draw("AXISSAME");
   
   TLegend *leg = new TLegend(0,0,0,0,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("PID_Curve","PID_Curve","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("e_signal","e_signal","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("pi_signal","pi_signal","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("pi2_signal","pi2_signal","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("k_signal","k_signal","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("p_signal","p_signal","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("HistM1","IncE","LP");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("HistM","IncE_MVA","LP");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   pad1->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
