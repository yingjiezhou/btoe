{
//=========Macro generated from canvas: c1/full fit
//=========  (Thu Jan 17 17:24:24 2019) by ROOT version5.34/30
   TCanvas *c1 = new TCanvas("c1", "full fit",0,0,700,500);
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
   TPad *pad1 = new TPad("pad1", "pad1",0,0.25,1,1);
   pad1->Draw();
   pad1->cd();
   pad1->Range(0,0,1,1);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetTickx(1);
   pad1->SetTicky(1);
   pad1->SetLeftMargin(0.14);
   pad1->SetRightMargin(0.05);
   pad1->SetTopMargin(0.08);
   pad1->SetBottomMargin(0.02);
   pad1->SetFrameLineWidth(2);
   pad1->SetFrameBorderMode(0);
   
   TH1D *frame_ad86130__19 = new TH1D("frame_ad86130__19","",100,-2.6,5.026667);
   frame_ad86130__19->SetBinContent(1,195196.2);
   frame_ad86130__19->SetMaximum(195196.2);
   frame_ad86130__19->SetEntries(2);
   frame_ad86130__19->SetDirectory(0);
   frame_ad86130__19->SetStats(0);
   frame_ad86130__19->SetLineWidth(2);
   frame_ad86130__19->SetMarkerStyle(20);
   frame_ad86130__19->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_ad86130__19->GetXaxis()->SetNdivisions(505);
   frame_ad86130__19->GetXaxis()->SetLabelFont(132);
   frame_ad86130__19->GetXaxis()->SetLabelOffset(0.01);
   frame_ad86130__19->GetXaxis()->SetLabelSize(0.06);
   frame_ad86130__19->GetXaxis()->SetTitleSize(0.072);
   frame_ad86130__19->GetXaxis()->SetTitleOffset(0.95);
   frame_ad86130__19->GetXaxis()->SetTitleFont(132);
   frame_ad86130__19->GetYaxis()->SetTitle("Events / ( 0.346667 )");
   frame_ad86130__19->GetYaxis()->SetLabelFont(132);
   frame_ad86130__19->GetYaxis()->SetLabelOffset(0.01);
   frame_ad86130__19->GetYaxis()->SetLabelSize(0.06);
   frame_ad86130__19->GetYaxis()->SetTitleSize(0.1);
   frame_ad86130__19->GetYaxis()->SetTitleOffset(0.6);
   frame_ad86130__19->GetYaxis()->SetTitleFont(132);
   frame_ad86130__19->GetZaxis()->SetLabelFont(132);
   frame_ad86130__19->GetZaxis()->SetLabelSize(0.06);
   frame_ad86130__19->GetZaxis()->SetTitleSize(0.072);
   frame_ad86130__19->GetZaxis()->SetTitleOffset(1.2);
   frame_ad86130__19->GetZaxis()->SetTitleFont(132);
   frame_ad86130__19->Draw("FUNC");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(22);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillColor(1);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-2.426667,0);
   grae->SetPointError(0,0.1733333,0.1733333,0,1.147874);
   grae->SetPoint(1,-2.08,0);
   grae->SetPointError(1,0.1733333,0.1733333,0,1.147874);
   grae->SetPoint(2,-1.733333,0);
   grae->SetPointError(2,0.1733333,0.1733333,0,1.147874);
   grae->SetPoint(3,-1.386667,44);
   grae->SetPointError(3,0.1733333,0.1733333,6.60794,7.68351);
   grae->SetPoint(4,-1.04,1949);
   grae->SetPointError(4,0.1733333,0.1733333,43.65031,44.65031);
   grae->SetPoint(5,-0.6933333,8708);
   grae->SetPointError(5,0.1733333,0.1733333,92.818,93.818);
   grae->SetPoint(6,-0.3466667,15234);
   grae->SetPointError(6,0.1733333,0.1733333,122.9271,123.9271);
   grae->SetPoint(7,0,14522);
   grae->SetPointError(7,0.1733333,0.1733333,120.0083,121.0083);
   grae->SetPoint(8,0.3466667,11813);
   grae->SetPointError(8,0.1733333,0.1733333,108.1888,109.1888);
   grae->SetPoint(9,0.6933333,8316);
   grae->SetPointError(9,0.1733333,0.1733333,90.69348,91.69348);
   grae->SetPoint(10,1.04,5383);
   grae->SetPointError(10,0.1733333,0.1733333,72.87063,73.87063);
   grae->SetPoint(11,1.386667,3080);
   grae->SetPointError(11,0.1733333,0.1733333,55,56);
   grae->SetPoint(12,1.733333,1555);
   grae->SetPointError(12,0.1733333,0.1733333,38.93666,39.93666);
   grae->SetPoint(13,2.08,792);
   grae->SetPointError(13,0.1733333,0.1733333,27.64694,28.64694);
   grae->SetPoint(14,2.426667,322);
   grae->SetPointError(14,0.1733333,0.1733333,17.45132,18.45132);
   grae->SetPoint(15,2.773333,182);
   grae->SetPointError(15,0.1733333,0.1733333,13,14);
   grae->SetPoint(16,3.12,121);
   grae->SetPointError(16,0.1733333,0.1733333,10.51136,11.51136);
   grae->SetPoint(17,3.466667,130);
   grae->SetPointError(17,0.1733333,0.1733333,10.91271,11.91271);
   grae->SetPoint(18,3.813333,149);
   grae->SetPointError(18,0.1733333,0.1733333,11.71679,12.71679);
   grae->SetPoint(19,4.16,156);
   grae->SetPointError(19,0.1733333,0.1733333,12,13);
   grae->SetPoint(20,4.506667,192);
   grae->SetPointError(20,0.1733333,0.1733333,13.36542,14.36542);
   grae->SetPoint(21,4.853333,147);
   grae->SetPointError(21,0.1733333,0.1733333,11.63466,12.63466);
   grae->Draw("p");
   
   TGraph *graph = new TGraph(123);
   graph->SetName("PID_Curve");
   graph->SetTitle("Projection of completePDF");
   graph->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   graph->SetPoint(0,-2.26,0.00400209685);
   graph->SetPoint(1,-2.1674,0.01622644183);
   graph->SetPoint(2,-2.0748,0.06147367635);
   graph->SetPoint(3,-1.9822,0.2176132133);
   graph->SetPoint(4,-1.8896,0.7197994723);
   graph->SetPoint(5,-1.797,2.224682161);
   graph->SetPoint(6,-1.7044,6.424725947);
   graph->SetPoint(7,-1.6118,17.33689937);
   graph->SetPoint(8,-1.5192,43.71378743);
   graph->SetPoint(9,-1.4266,102.9901356);
   graph->SetPoint(10,-1.334,226.7268794);
   graph->SetPoint(11,-1.2877,327.9484032);
   graph->SetPoint(12,-1.2414,466.380708);
   graph->SetPoint(13,-1.1951,652.0909618);
   graph->SetPoint(14,-1.1488,896.4133809);
   graph->SetPoint(15,-1.1025,1211.549122);
   graph->SetPoint(16,-1.0562,1609.92732);
   graph->SetPoint(17,-1.0099,2103.313746);
   graph->SetPoint(18,-0.9636,2701.68304);
   graph->SetPoint(19,-0.9173,3411.907743);
   graph->SetPoint(20,-0.871,4236.358539);
   graph->SetPoint(21,-0.8247,5171.54949);
   graph->SetPoint(22,-0.7784,6206.992318);
   graph->SetPoint(23,-0.7321,7324.437496);
   graph->SetPoint(24,-0.6858,8497.670618);
   graph->SetPoint(25,-0.5932,10870.48109);
   graph->SetPoint(26,-0.5469,11985.93783);
   graph->SetPoint(27,-0.52375,12506.06995);
   graph->SetPoint(28,-0.5006,12993.55003);
   graph->SetPoint(29,-0.47745,13442.8988);
   graph->SetPoint(30,-0.4543,13848.92847);
   graph->SetPoint(31,-0.43115,14206.84203);
   graph->SetPoint(32,-0.408,14512.3274);
   graph->SetPoint(33,-0.38485,14761.64376);
   graph->SetPoint(34,-0.3617,14951.69777);
   graph->SetPoint(35,-0.33855,15080.10744);
   graph->SetPoint(36,-0.3154,15145.25181);
   graph->SetPoint(37,-0.2691,15144.04221);
   graph->SetPoint(38,-0.2228,15099.99645);
   graph->SetPoint(39,-0.1765,15020.80559);
   graph->SetPoint(40,-0.1302,14907.02403);
   graph->SetPoint(41,-0.0839,14759.44491);
   graph->SetPoint(42,-0.0376,14579.09088);
   graph->SetPoint(43,0.055,14125.22322);
   graph->SetPoint(44,0.1476,13557.68633);
   graph->SetPoint(45,0.2402,12891.43399);
   graph->SetPoint(46,0.3328,12143.45486);
   graph->SetPoint(47,0.4254,11332.05526);
   graph->SetPoint(48,0.518,10476.12073);
   graph->SetPoint(49,0.6106,9594.397362);
   graph->SetPoint(50,0.7032,8704.830435);
   graph->SetPoint(51,0.7958,7823.991382);
   graph->SetPoint(52,0.8884,6966.616381);
   graph->SetPoint(53,0.981,6145.270766);
   graph->SetPoint(54,1.0736,5370.144365);
   graph->SetPoint(55,1.1662,4648.974339);
   graph->SetPoint(56,1.2588,3987.084687);
   graph->SetPoint(57,1.3514,3387.525817);
   graph->SetPoint(58,1.444,2851.293735);
   graph->SetPoint(59,1.5366,2377.606411);
   graph->SetPoint(60,1.6292,1964.21475);
   graph->SetPoint(61,1.7218,1607.726982);
   graph->SetPoint(62,1.8144,1303.92789);
   graph->SetPoint(63,1.907,1048.077597);
   graph->SetPoint(64,1.9996,835.1784684);
   graph->SetPoint(65,2.0922,660.2023523);
   graph->SetPoint(66,2.1848,518.2739681);
   graph->SetPoint(67,2.2774,404.8092474);
   graph->SetPoint(68,2.37,315.6099536);
   graph->SetPoint(69,2.4626,246.9178307);
   graph->SetPoint(70,2.5552,195.4329527);
   graph->SetPoint(71,2.6478,158.3019529);
   graph->SetPoint(72,2.7404,133.0824912);
   graph->SetPoint(73,2.833,117.6907566);
   graph->SetPoint(74,2.9256,110.3390082);
   graph->SetPoint(75,3.0182,109.4701307);
   graph->SetPoint(76,3.1108,113.6958283);
   graph->SetPoint(77,3.2034,121.744338);
   graph->SetPoint(78,3.296,132.4223378);
   graph->SetPoint(79,3.3886,144.5940498);
   graph->SetPoint(80,3.4812,157.1784785);
   graph->SetPoint(81,3.5738,169.1634649);
   graph->SetPoint(82,3.6664,179.6330419);
   graph->SetPoint(83,3.759,187.8027608);
   graph->SetPoint(84,3.8516,193.0565293);
   graph->SetPoint(85,3.9442,194.9782647);
   graph->SetPoint(86,4.0368,193.3724138);
   graph->SetPoint(87,4.1294,188.2690305);
   graph->SetPoint(88,4.222,179.9113833);
   graph->SetPoint(89,4.3146,168.7266235);
   graph->SetPoint(90,4.4072,155.2824466);
   graph->SetPoint(91,4.4998,140.2345543);
   graph->SetPoint(92,4.5924,124.270773);
   graph->SetPoint(93,4.685,108.057805);
   graph->SetPoint(94,4.7776,92.19581775);
   graph->SetPoint(95,4.8702,77.18462856);
   graph->SetPoint(96,4.9628,63.40342049);
   graph->SetPoint(97,5.0091,57.05766403);
   graph->SetPoint(98,5.020675,55.53188943);
   graph->SetPoint(99,5.03225,0);
   graph->SetPoint(100,5.0554,0);
   graph->SetPoint(101,5.148,0);
   graph->SetPoint(102,5.2406,0);
   graph->SetPoint(103,5.3332,0);
   graph->SetPoint(104,5.4258,0);
   graph->SetPoint(105,5.5184,0);
   graph->SetPoint(106,5.611,0);
   graph->SetPoint(107,5.7036,0);
   graph->SetPoint(108,5.7962,0);
   graph->SetPoint(109,5.8888,0);
   graph->SetPoint(110,5.9814,0);
   graph->SetPoint(111,6.074,0);
   graph->SetPoint(112,6.1666,0);
   graph->SetPoint(113,6.2592,0);
   graph->SetPoint(114,6.3518,0);
   graph->SetPoint(115,6.4444,0);
   graph->SetPoint(116,6.537,0);
   graph->SetPoint(117,6.6296,0);
   graph->SetPoint(118,6.7222,0);
   graph->SetPoint(119,6.8148,0);
   graph->SetPoint(120,6.9074,0);
   graph->SetPoint(121,7,0);
   graph->SetPoint(122,7,0);
   graph->Draw("l");
   
   graph = new TGraph(120);
   graph->SetName("completePDF_Norm[PID]_Comp[e_signal]_Range[fit_nll_completePDF_dataHist]_NormRange[fit_nll_completePDF_dataHist]");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetFillStyle(3007);

   ci = TColor::GetColor("#339933");
   graph->SetLineColor(ci);
   graph->SetLineStyle(7);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   graph->SetPoint(0,-2.26,0.00400209685);
   graph->SetPoint(1,-2.1674,0.01622644183);
   graph->SetPoint(2,-2.0748,0.06147367635);
   graph->SetPoint(3,-1.9822,0.2176132133);
   graph->SetPoint(4,-1.8896,0.7197994723);
   graph->SetPoint(5,-1.797,2.224682161);
   graph->SetPoint(6,-1.7044,6.424725947);
   graph->SetPoint(7,-1.6118,17.33689937);
   graph->SetPoint(8,-1.5192,43.71378743);
   graph->SetPoint(9,-1.4266,102.9901356);
   graph->SetPoint(10,-1.334,226.7268794);
   graph->SetPoint(11,-1.2877,327.9484032);
   graph->SetPoint(12,-1.2414,466.380708);
   graph->SetPoint(13,-1.1951,652.0909618);
   graph->SetPoint(14,-1.1488,896.4133809);
   graph->SetPoint(15,-1.1025,1211.549122);
   graph->SetPoint(16,-1.0562,1609.92732);
   graph->SetPoint(17,-1.0099,2103.313746);
   graph->SetPoint(18,-0.9636,2701.68304);
   graph->SetPoint(19,-0.9173,3411.907743);
   graph->SetPoint(20,-0.871,4236.358539);
   graph->SetPoint(21,-0.8247,5171.54949);
   graph->SetPoint(22,-0.7784,6206.992318);
   graph->SetPoint(23,-0.7321,7324.437496);
   graph->SetPoint(24,-0.6858,8497.670618);
   graph->SetPoint(25,-0.5932,10870.48109);
   graph->SetPoint(26,-0.5469,11985.93783);
   graph->SetPoint(27,-0.52375,12506.06995);
   graph->SetPoint(28,-0.5006,12993.55003);
   graph->SetPoint(29,-0.47745,13442.8988);
   graph->SetPoint(30,-0.4543,13848.92847);
   graph->SetPoint(31,-0.43115,14206.84203);
   graph->SetPoint(32,-0.408,14512.3274);
   graph->SetPoint(33,-0.38485,14761.64376);
   graph->SetPoint(34,-0.3617,14951.69777);
   graph->SetPoint(35,-0.33855,15080.10744);
   graph->SetPoint(36,-0.3154,15145.25181);
   graph->SetPoint(37,-0.2691,15144.04221);
   graph->SetPoint(38,-0.2228,15099.99645);
   graph->SetPoint(39,-0.1765,15020.80559);
   graph->SetPoint(40,-0.1302,14907.02403);
   graph->SetPoint(41,-0.0839,14759.4449);
   graph->SetPoint(42,-0.0376,14579.09087);
   graph->SetPoint(43,0.055,14125.22322);
   graph->SetPoint(44,0.1476,13557.68631);
   graph->SetPoint(45,0.2402,12891.43395);
   graph->SetPoint(46,0.3328,12143.45477);
   graph->SetPoint(47,0.4254,11332.05506);
   graph->SetPoint(48,0.518,10476.12032);
   graph->SetPoint(49,0.6106,9594.396556);
   graph->SetPoint(50,0.7032,8704.82885);
   graph->SetPoint(51,0.7958,7823.988323);
   graph->SetPoint(52,0.8884,6966.610591);
   graph->SetPoint(53,0.981,6145.260008);
   graph->SetPoint(54,1.0736,5370.124753);
   graph->SetPoint(55,1.1662,4648.93926);
   graph->SetPoint(56,1.2588,3987.023122);
   graph->SetPoint(57,1.3514,3387.419799);
   graph->SetPoint(58,1.444,2851.1146);
   graph->SetPoint(59,1.5366,2377.309421);
   graph->SetPoint(60,1.6292,1963.731623);
   graph->SetPoint(61,1.7218,1606.955837);
   graph->SetPoint(62,1.8144,1302.72016);
   graph->SetPoint(63,1.907,1046.221671);
   graph->SetPoint(64,1.9996,832.3800722);
   graph->SetPoint(65,2.0922,656.0622093);
   graph->SetPoint(66,2.1848,512.2639039);
   graph->SetPoint(67,2.2774,396.2487204);
   graph->SetPoint(68,2.37,303.645868);
   graph->SetPoint(69,2.4626,230.5113232);
   graph->SetPoint(70,2.5552,173.3574606);
   graph->SetPoint(71,2.6478,129.1570731);
   graph->SetPoint(72,2.7404,95.32772704);
   graph->SetPoint(73,2.833,69.70206844);
   graph->SetPoint(74,2.9256,50.48908259);
   graph->SetPoint(75,3.0182,36.23052922);
   graph->SetPoint(76,3.1108,25.75593149);
   graph->SetPoint(77,3.2034,18.13866123);
   graph->SetPoint(78,3.296,12.65489608);
   graph->SetPoint(79,3.3886,8.746560846);
   graph->SetPoint(80,3.4812,5.988822553);
   graph->SetPoint(81,3.5738,4.062290283);
   graph->SetPoint(82,3.6664,2.729768687);
   graph->SetPoint(83,3.759,1.817214219);
   graph->SetPoint(84,3.8516,1.198427567);
   graph->SetPoint(85,3.9442,0.7829658842);
   graph->SetPoint(86,4.0368,0.506756436);
   graph->SetPoint(87,4.1294,0.3249234771);
   graph->SetPoint(88,4.222,0.2063898314);
   graph->SetPoint(89,4.3146,0.1298736019);
   graph->SetPoint(90,4.4072,0.08096155847);
   graph->SetPoint(91,4.4998,0.04999910366);
   graph->SetPoint(92,4.5924,0.03058940032);
   graph->SetPoint(93,4.685,0.01853980203);
   graph->SetPoint(94,4.7776,0.0111317798);
   graph->SetPoint(95,4.8702,0.006621395148);
   graph->SetPoint(96,4.9628,0.00390175316);
   graph->SetPoint(97,5.0554,0);
   graph->SetPoint(98,5.148,0);
   graph->SetPoint(99,5.2406,0);
   graph->SetPoint(100,5.3332,0);
   graph->SetPoint(101,5.4258,0);
   graph->SetPoint(102,5.5184,0);
   graph->SetPoint(103,5.611,0);
   graph->SetPoint(104,5.7036,0);
   graph->SetPoint(105,5.7962,0);
   graph->SetPoint(106,5.8888,0);
   graph->SetPoint(107,5.9814,0);
   graph->SetPoint(108,6.074,0);
   graph->SetPoint(109,6.1666,0);
   graph->SetPoint(110,6.2592,0);
   graph->SetPoint(111,6.3518,0);
   graph->SetPoint(112,6.4444,0);
   graph->SetPoint(113,6.537,0);
   graph->SetPoint(114,6.6296,0);
   graph->SetPoint(115,6.7222,0);
   graph->SetPoint(116,6.8148,0);
   graph->SetPoint(117,6.9074,0);
   graph->SetPoint(118,7,0);
   graph->SetPoint(119,7,0);
   graph->Draw("l");
   
   graph = new TGraph(118);
   graph->SetName("completePDF_Norm[PID]_Comp[pi2_signal]_Range[fit_nll_completePDF_dataHist]_NormRange[fit_nll_completePDF_dataHist]");
   graph->SetTitle("Projection of completePDF");

   ci = TColor::GetColor("#339933");
   graph->SetFillColor(ci);
   graph->SetLineColor(6);
   graph->SetLineStyle(6);
   graph->SetLineWidth(3);
   graph->SetMarkerStyle(20);
   graph->SetPoint(0,-2.26,5.15246239e-17);
   graph->SetPoint(1,-2.1674,1.825031679e-16);
   graph->SetPoint(2,-2.0748,6.342837793e-16);
   graph->SetPoint(3,-1.9822,2.162989565e-15);
   graph->SetPoint(4,-1.8896,7.237404805e-15);
   graph->SetPoint(5,-1.797,2.376123041e-14);
   graph->SetPoint(6,-1.7044,7.654425633e-14);
   graph->SetPoint(7,-1.6118,2.419434735e-13);
   graph->SetPoint(8,-1.5192,7.503654619e-13);
   graph->SetPoint(9,-1.4266,2.283438828e-12);
   graph->SetPoint(10,-1.334,6.818102851e-12);
   graph->SetPoint(11,-1.2414,1.997539316e-11);
   graph->SetPoint(12,-1.1488,5.742285018e-11);
   graph->SetPoint(13,-1.0562,1.61968953e-10);
   graph->SetPoint(14,-0.9636,4.482666462e-10);
   graph->SetPoint(15,-0.871,1.217303016e-09);
   graph->SetPoint(16,-0.7784,3.24353502e-09);
   graph->SetPoint(17,-0.6858,8.480004947e-09);
   graph->SetPoint(18,-0.5932,2.175360513e-08);
   graph->SetPoint(19,-0.5006,5.475502701e-08);
   graph->SetPoint(20,-0.408,1.352304132e-07);
   graph->SetPoint(21,-0.3154,3.277044764e-07);
   graph->SetPoint(22,-0.2228,7.791982951e-07);
   graph->SetPoint(23,-0.1302,1.817905211e-06);
   graph->SetPoint(24,-0.0376,4.161521057e-06);
   graph->SetPoint(25,0.055,9.347394658e-06);
   graph->SetPoint(26,0.1476,2.060092323e-05);
   graph->SetPoint(27,0.2402,4.454925122e-05);
   graph->SetPoint(28,0.3328,9.452610331e-05);
   graph->SetPoint(29,0.4254,0.0001967980191);
   graph->SetPoint(30,0.518,0.0004020196777);
   graph->SetPoint(31,0.6106,0.0008058078997);
   graph->SetPoint(32,0.7032,0.001584795945);
   graph->SetPoint(33,0.7958,0.003058248723);
   graph->SetPoint(34,0.8884,0.005790684134);
   graph->SetPoint(35,0.981,0.01075832277);
   graph->SetPoint(36,1.0736,0.01961177423);
   graph->SetPoint(37,1.1662,0.03507896904);
   graph->SetPoint(38,1.2588,0.0615650701);
   graph->SetPoint(39,1.3514,0.1060179877);
   graph->SetPoint(40,1.444,0.179135787);
   graph->SetPoint(41,1.5366,0.2969906498);
   graph->SetPoint(42,1.6292,0.4831264538);
   graph->SetPoint(43,1.7218,0.7711457702);
   graph->SetPoint(44,1.8144,1.20772975);
   graph->SetPoint(45,1.907,1.855926058);
   graph->SetPoint(46,1.9996,2.798396154);
   graph->SetPoint(47,2.0922,4.140143005);
   graph->SetPoint(48,2.1848,6.01006419);
   graph->SetPoint(49,2.2774,8.560526967);
   graph->SetPoint(50,2.37,11.96408556);
   graph->SetPoint(51,2.4626,16.4065075);
   graph->SetPoint(52,2.5552,22.07549212);
   graph->SetPoint(53,2.6478,29.14487973);
   graph->SetPoint(54,2.6941,33.25043353);
   graph->SetPoint(55,2.7404,37.75476419);
   graph->SetPoint(56,2.7867,42.66636235);
   graph->SetPoint(57,2.833,47.98868814);
   graph->SetPoint(58,2.8793,53.71944828);
   graph->SetPoint(59,2.9256,59.84992558);
   graph->SetPoint(60,3.0182,73.23960151);
   graph->SetPoint(61,3.1108,87.93989681);
   graph->SetPoint(62,3.2034,103.6056767);
   graph->SetPoint(63,3.296,119.7674417);
   graph->SetPoint(64,3.3886,135.847489);
   graph->SetPoint(65,3.4812,151.1896559);
   graph->SetPoint(66,3.5275,158.3676303);
   graph->SetPoint(67,3.5738,165.1011747);
   graph->SetPoint(68,3.6201,171.3062915);
   graph->SetPoint(69,3.6664,176.9032732);
   graph->SetPoint(70,3.7127,181.8183991);
   graph->SetPoint(71,3.759,185.9855466);
   graph->SetPoint(72,3.8053,189.3476706);
   graph->SetPoint(73,3.8516,191.8581017);
   graph->SetPoint(74,3.8979,193.4816244);
   graph->SetPoint(75,3.9442,194.1952988);
   graph->SetPoint(76,3.9905,193.989);
   graph->SetPoint(77,4.0368,192.8656574);
   graph->SetPoint(78,4.0831,190.8411851);
   graph->SetPoint(79,4.1294,187.944107);
   graph->SetPoint(80,4.1757,184.214888);
   graph->SetPoint(81,4.222,179.7049935);
   graph->SetPoint(82,4.2683,174.4757079);
   graph->SetPoint(83,4.3146,168.5967499);
   graph->SetPoint(84,4.3609,162.1447281);
   graph->SetPoint(85,4.4072,155.2014851);
   graph->SetPoint(86,4.4998,140.1845552);
   graph->SetPoint(87,4.5924,124.2401836);
   graph->SetPoint(88,4.685,108.0392652);
   graph->SetPoint(89,4.7776,92.18468597);
   graph->SetPoint(90,4.8702,77.17800716);
   graph->SetPoint(91,4.9628,63.39951873);
   graph->SetPoint(92,5.0091,57.05467942);
   graph->SetPoint(93,5.020675,55.52909924);
   graph->SetPoint(94,5.03225,0);
   graph->SetPoint(95,5.0554,0);
   graph->SetPoint(96,5.148,0);
   graph->SetPoint(97,5.2406,0);
   graph->SetPoint(98,5.3332,0);
   graph->SetPoint(99,5.4258,0);
   graph->SetPoint(100,5.5184,0);
   graph->SetPoint(101,5.611,0);
   graph->SetPoint(102,5.7036,0);
   graph->SetPoint(103,5.7962,0);
   graph->SetPoint(104,5.8888,0);
   graph->SetPoint(105,5.9814,0);
   graph->SetPoint(106,6.074,0);
   graph->SetPoint(107,6.1666,0);
   graph->SetPoint(108,6.2592,0);
   graph->SetPoint(109,6.3518,0);
   graph->SetPoint(110,6.4444,0);
   graph->SetPoint(111,6.537,0);
   graph->SetPoint(112,6.6296,0);
   graph->SetPoint(113,6.7222,0);
   graph->SetPoint(114,6.8148,0);
   graph->SetPoint(115,6.9074,0);
   graph->SetPoint(116,7,0);
   graph->SetPoint(117,7,0);
   graph->Draw("l");
   
   grae = new TGraphAsymmErrors(22);
   grae->SetName("HistM1");
   grae->SetTitle("Histogram of dataHist1_plot__PID");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   grae->SetLineColor(ci);
   grae->SetLineWidth(2);

   ci = TColor::GetColor("#cccccc");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-2.426667,185470);
   grae->SetPointError(0,0.1733333,0.1733333,430.1626,431.1626);
   grae->SetPoint(1,-2.08,107115);
   grae->SetPointError(1,0.1733333,0.1733333,326.7847,327.7847);
   grae->SetPoint(2,-1.733333,60101);
   grae->SetPointError(2,0.1733333,0.1733333,244.6556,245.6556);
   grae->SetPoint(3,-1.386667,36535);
   grae->SetPointError(3,0.1733333,0.1733333,190.642,191.642);
   grae->SetPoint(4,-1.04,24533);
   grae->SetPointError(4,0.1733333,0.1733333,156.1309,157.1309);
   grae->SetPoint(5,-0.6933333,19027);
   grae->SetPointError(5,0.1733333,0.1733333,137.4393,138.4393);
   grae->SetPoint(6,-0.3466667,17611);
   grae->SetPointError(6,0.1733333,0.1733333,132.2074,133.2074);
   grae->SetPoint(7,0,14944);
   grae->SetPointError(7,0.1733333,0.1733333,121.7467,122.7467);
   grae->SetPoint(8,0.3466667,11871);
   grae->SetPointError(8,0.1733333,0.1733333,108.4553,109.4553);
   grae->SetPoint(9,0.6933333,8319);
   grae->SetPointError(9,0.1733333,0.1733333,90.70992,91.70992);
   grae->SetPoint(10,1.04,5384);
   grae->SetPointError(10,0.1733333,0.1733333,72.87745,73.87745);
   grae->SetPoint(11,1.386667,3080);
   grae->SetPointError(11,0.1733333,0.1733333,55,56);
   grae->SetPoint(12,1.733333,1555);
   grae->SetPointError(12,0.1733333,0.1733333,38.93666,39.93666);
   grae->SetPoint(13,2.08,792);
   grae->SetPointError(13,0.1733333,0.1733333,27.64694,28.64694);
   grae->SetPoint(14,2.426667,322);
   grae->SetPointError(14,0.1733333,0.1733333,17.45132,18.45132);
   grae->SetPoint(15,2.773333,182);
   grae->SetPointError(15,0.1733333,0.1733333,13,14);
   grae->SetPoint(16,3.12,121);
   grae->SetPointError(16,0.1733333,0.1733333,10.51136,11.51136);
   grae->SetPoint(17,3.466667,130);
   grae->SetPointError(17,0.1733333,0.1733333,10.91271,11.91271);
   grae->SetPoint(18,3.813333,149);
   grae->SetPointError(18,0.1733333,0.1733333,11.71679,12.71679);
   grae->SetPoint(19,4.16,156);
   grae->SetPointError(19,0.1733333,0.1733333,12,13);
   grae->SetPoint(20,4.506667,192);
   grae->SetPointError(20,0.1733333,0.1733333,13.36542,14.36542);
   grae->SetPoint(21,4.853333,147);
   grae->SetPointError(21,0.1733333,0.1733333,11.63466,12.63466);
   grae->Draw("p");
   
   grae = new TGraphAsymmErrors(22);
   grae->SetName("HistM");
   grae->SetTitle("Histogram of dataHist_plot__PID");
   grae->SetFillColor(1);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-2.426667,0);
   grae->SetPointError(0,0.1733333,0.1733333,0,1.147874);
   grae->SetPoint(1,-2.08,0);
   grae->SetPointError(1,0.1733333,0.1733333,0,1.147874);
   grae->SetPoint(2,-1.733333,0);
   grae->SetPointError(2,0.1733333,0.1733333,0,1.147874);
   grae->SetPoint(3,-1.386667,44);
   grae->SetPointError(3,0.1733333,0.1733333,6.60794,7.68351);
   grae->SetPoint(4,-1.04,1949);
   grae->SetPointError(4,0.1733333,0.1733333,43.65031,44.65031);
   grae->SetPoint(5,-0.6933333,8708);
   grae->SetPointError(5,0.1733333,0.1733333,92.818,93.818);
   grae->SetPoint(6,-0.3466667,15234);
   grae->SetPointError(6,0.1733333,0.1733333,122.9271,123.9271);
   grae->SetPoint(7,0,14522);
   grae->SetPointError(7,0.1733333,0.1733333,120.0083,121.0083);
   grae->SetPoint(8,0.3466667,11813);
   grae->SetPointError(8,0.1733333,0.1733333,108.1888,109.1888);
   grae->SetPoint(9,0.6933333,8316);
   grae->SetPointError(9,0.1733333,0.1733333,90.69348,91.69348);
   grae->SetPoint(10,1.04,5383);
   grae->SetPointError(10,0.1733333,0.1733333,72.87063,73.87063);
   grae->SetPoint(11,1.386667,3080);
   grae->SetPointError(11,0.1733333,0.1733333,55,56);
   grae->SetPoint(12,1.733333,1555);
   grae->SetPointError(12,0.1733333,0.1733333,38.93666,39.93666);
   grae->SetPoint(13,2.08,792);
   grae->SetPointError(13,0.1733333,0.1733333,27.64694,28.64694);
   grae->SetPoint(14,2.426667,322);
   grae->SetPointError(14,0.1733333,0.1733333,17.45132,18.45132);
   grae->SetPoint(15,2.773333,182);
   grae->SetPointError(15,0.1733333,0.1733333,13,14);
   grae->SetPoint(16,3.12,121);
   grae->SetPointError(16,0.1733333,0.1733333,10.51136,11.51136);
   grae->SetPoint(17,3.466667,130);
   grae->SetPointError(17,0.1733333,0.1733333,10.91271,11.91271);
   grae->SetPoint(18,3.813333,149);
   grae->SetPointError(18,0.1733333,0.1733333,11.71679,12.71679);
   grae->SetPoint(19,4.16,156);
   grae->SetPointError(19,0.1733333,0.1733333,12,13);
   grae->SetPoint(20,4.506667,192);
   grae->SetPointError(20,0.1733333,0.1733333,13.36542,14.36542);
   grae->SetPoint(21,4.853333,147);
   grae->SetPointError(21,0.1733333,0.1733333,11.63466,12.63466);
   grae->Draw("p");
   
   TPaveText *pt = new TPaveText(-2.353437e-185,-2.353437e-185,-2.353437e-185,-2.353437e-185,"BRNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetLineWidth(2);
   pt->SetTextFont(132);
   pt->SetTextSize(0.07);
   TText *text = pt->AddText("#it{p}_{T} #in [2.0,2.5] GeV");
   pt->Draw();
   
   TH1D *frame_ad86130__20 = new TH1D("frame_ad86130__20","",100,-2.6,5.026667);
   frame_ad86130__20->SetBinContent(1,195196.2);
   frame_ad86130__20->SetMaximum(195196.2);
   frame_ad86130__20->SetEntries(2);
   frame_ad86130__20->SetDirectory(0);
   frame_ad86130__20->SetStats(0);
   frame_ad86130__20->SetLineWidth(2);
   frame_ad86130__20->SetMarkerStyle(20);
   frame_ad86130__20->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_ad86130__20->GetXaxis()->SetNdivisions(505);
   frame_ad86130__20->GetXaxis()->SetLabelFont(132);
   frame_ad86130__20->GetXaxis()->SetLabelOffset(0.01);
   frame_ad86130__20->GetXaxis()->SetLabelSize(0.06);
   frame_ad86130__20->GetXaxis()->SetTitleSize(0.072);
   frame_ad86130__20->GetXaxis()->SetTitleOffset(0.95);
   frame_ad86130__20->GetXaxis()->SetTitleFont(132);
   frame_ad86130__20->GetYaxis()->SetTitle("Events / ( 0.346667 )");
   frame_ad86130__20->GetYaxis()->SetLabelFont(132);
   frame_ad86130__20->GetYaxis()->SetLabelOffset(0.01);
   frame_ad86130__20->GetYaxis()->SetLabelSize(0.06);
   frame_ad86130__20->GetYaxis()->SetTitleSize(0.1);
   frame_ad86130__20->GetYaxis()->SetTitleOffset(0.6);
   frame_ad86130__20->GetYaxis()->SetTitleFont(132);
   frame_ad86130__20->GetZaxis()->SetLabelFont(132);
   frame_ad86130__20->GetZaxis()->SetLabelSize(0.06);
   frame_ad86130__20->GetZaxis()->SetTitleSize(0.072);
   frame_ad86130__20->GetZaxis()->SetTitleOffset(1.2);
   frame_ad86130__20->GetZaxis()->SetTitleFont(132);
   frame_ad86130__20->Draw("AXISSAME");
   pad1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: pad2
   pad2 = new TPad("pad2", "pad2",0,0,1,0.255);
   pad2->Draw();
   pad2->cd();
   pad2->Range(0,0,1,1);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetTickx(1);
   pad2->SetTicky(1);
   pad2->SetLeftMargin(0.14);
   pad2->SetRightMargin(0.05);
   pad2->SetTopMargin(0.015);
   pad2->SetBottomMargin(0.5);
   pad2->SetFrameLineWidth(2);
   pad2->SetFrameBorderMode(0);
   
   TH1D *frame_ae3d930__21 = new TH1D("frame_ae3d930__21","",100,-2.6,5.026667);
   frame_ae3d930__21->SetBinContent(1,7.968278);
   frame_ae3d930__21->SetMinimum(-9.9);
   frame_ae3d930__21->SetMaximum(9.9);
   frame_ae3d930__21->SetEntries(1);
   frame_ae3d930__21->SetDirectory(0);
   frame_ae3d930__21->SetStats(0);
   frame_ae3d930__21->SetLineWidth(2);
   frame_ae3d930__21->SetMarkerStyle(20);
   frame_ae3d930__21->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_ae3d930__21->GetXaxis()->SetNdivisions(505);
   frame_ae3d930__21->GetXaxis()->SetLabelFont(132);
   frame_ae3d930__21->GetXaxis()->SetLabelOffset(0.01);
   frame_ae3d930__21->GetXaxis()->SetLabelSize(0.15);
   frame_ae3d930__21->GetXaxis()->SetTitleSize(0.3);
   frame_ae3d930__21->GetXaxis()->SetTitleOffset(0.63);
   frame_ae3d930__21->GetXaxis()->SetTitleFont(132);
   frame_ae3d930__21->GetYaxis()->SetTitle("Pull");
   frame_ae3d930__21->GetYaxis()->CenterTitle(true);
   frame_ae3d930__21->GetYaxis()->SetNdivisions(505);
   frame_ae3d930__21->GetYaxis()->SetLabelFont(132);
   frame_ae3d930__21->GetYaxis()->SetLabelOffset(0.01);
   frame_ae3d930__21->GetYaxis()->SetLabelSize(0.1);
   frame_ae3d930__21->GetYaxis()->SetTitleSize(0.15);
   frame_ae3d930__21->GetYaxis()->SetTitleOffset(0.3);
   frame_ae3d930__21->GetYaxis()->SetTitleFont(132);
   frame_ae3d930__21->GetZaxis()->SetLabelFont(132);
   frame_ae3d930__21->GetZaxis()->SetLabelSize(0.06);
   frame_ae3d930__21->GetZaxis()->SetTitleSize(0.072);
   frame_ae3d930__21->GetZaxis()->SetTitleOffset(1.2);
   frame_ae3d930__21->GetZaxis()->SetTitleFont(132);
   frame_ae3d930__21->Draw("FUNC");
   
   grae = new TGraphAsymmErrors(21);
   grae->SetName("pull_HistM_PID_Curve");
   grae->SetTitle("Pull of Histogram of dataHist_plot__PID and Projection of completePDF");
   grae->SetFillColor(1);
   grae->SetLineColor(0);
   grae->SetLineWidth(2);
   grae->SetMarkerStyle(8);
   grae->SetPoint(0,-2.08,-0.0513408);
   grae->SetPointError(0,0,0,0,1);
   grae->SetPoint(1,-1.733333,-4.453798);
   grae->SetPointError(1,0,0,0,1);
   grae->SetPoint(2,-1.386667,-14.62236);
   grae->SetPointError(2,0,0,0.8600158,1);
   grae->SetPoint(3,-1.04,3.813048);
   grae->SetPointError(3,0,0,1,1.022909);
   grae->SetPoint(4,-0.6933333,4.322681);
   grae->SetPointError(4,0,0,1,1.010774);
   grae->SetPoint(5,-0.3466667,1.61815);
   grae->SetPointError(5,0,0,1,1.008135);
   grae->SetPoint(6,0,1.059935);
   grae->SetPointError(6,0,0,1,1.008333);
   grae->SetPoint(7,0.3466667,-1.913653);
   grae->SetPointError(7,0,0,0.9908415,1);
   grae->SetPoint(8,0.6933333,-5.274259);
   grae->SetPointError(8,0,0,0.9890941,1);
   grae->SetPoint(9,1.04,-3.633375);
   grae->SetPointError(9,0,0,0.9864628,1);
   grae->SetPoint(10,1.386667,-1.84468);
   grae->SetPointError(10,0,0,0.9821429,1);
   grae->SetPoint(11,1.733333,-0.3728102);
   grae->SetPointError(11,0,0,0.9749603,1);
   grae->SetPoint(12,2.08,3.933334);
   grae->SetPointError(12,0,0,1,1.03617);
   grae->SetPoint(13,2.426667,2.774934);
   grae->SetPointError(13,0,0,1,1.057302);
   grae->SetPoint(14,2.773333,4.183969);
   grae->SetPointError(14,0,0,1,1.076923);
   grae->SetPoint(15,3.12,0.6188102);
   grae->SetPointError(15,0,0,1,1.095135);
   grae->SetPoint(16,3.466667,-2.115671);
   grae->SetPointError(16,0,0,0.9160561,1);
   grae->SetPoint(17,3.813333,-3.29371);
   grae->SetPointError(17,0,0,0.9213638,1);
   grae->SetPoint(18,4.16,-2.269786);
   grae->SetPointError(18,0,0,0.9230769,1);
   grae->SetPoint(19,4.506667,3.961657);
   grae->SetPointError(19,0,0,1,1.07482);
   grae->SetPoint(20,4.853333,5.76563);
   grae->SetPointError(20,0,0,1,1.08595);
   grae->Draw("b");
   
   TH1D *frame_ae3d930__22 = new TH1D("frame_ae3d930__22","",100,-2.6,5.026667);
   frame_ae3d930__22->SetBinContent(1,7.968278);
   frame_ae3d930__22->SetMinimum(-9.9);
   frame_ae3d930__22->SetMaximum(9.9);
   frame_ae3d930__22->SetEntries(1);
   frame_ae3d930__22->SetDirectory(0);
   frame_ae3d930__22->SetStats(0);
   frame_ae3d930__22->SetLineWidth(2);
   frame_ae3d930__22->SetMarkerStyle(20);
   frame_ae3d930__22->GetXaxis()->SetTitle("n#sigma_{e}");
   frame_ae3d930__22->GetXaxis()->SetNdivisions(505);
   frame_ae3d930__22->GetXaxis()->SetLabelFont(132);
   frame_ae3d930__22->GetXaxis()->SetLabelOffset(0.01);
   frame_ae3d930__22->GetXaxis()->SetLabelSize(0.15);
   frame_ae3d930__22->GetXaxis()->SetTitleSize(0.3);
   frame_ae3d930__22->GetXaxis()->SetTitleOffset(0.63);
   frame_ae3d930__22->GetXaxis()->SetTitleFont(132);
   frame_ae3d930__22->GetYaxis()->SetTitle("Pull");
   frame_ae3d930__22->GetYaxis()->CenterTitle(true);
   frame_ae3d930__22->GetYaxis()->SetNdivisions(505);
   frame_ae3d930__22->GetYaxis()->SetLabelFont(132);
   frame_ae3d930__22->GetYaxis()->SetLabelOffset(0.01);
   frame_ae3d930__22->GetYaxis()->SetLabelSize(0.1);
   frame_ae3d930__22->GetYaxis()->SetTitleSize(0.15);
   frame_ae3d930__22->GetYaxis()->SetTitleOffset(0.3);
   frame_ae3d930__22->GetYaxis()->SetTitleFont(132);
   frame_ae3d930__22->GetZaxis()->SetLabelFont(132);
   frame_ae3d930__22->GetZaxis()->SetLabelSize(0.06);
   frame_ae3d930__22->GetZaxis()->SetTitleSize(0.072);
   frame_ae3d930__22->GetZaxis()->SetTitleOffset(1.2);
   frame_ae3d930__22->GetZaxis()->SetTitleFont(132);
   frame_ae3d930__22->Draw("AXISSAME");
   pad2->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
