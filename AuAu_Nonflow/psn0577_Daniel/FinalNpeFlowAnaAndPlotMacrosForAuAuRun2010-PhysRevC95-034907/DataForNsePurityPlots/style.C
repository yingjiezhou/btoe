/*
 * plotRes200GeV.C
 *
 *  Created on: Jul 15, 2012
 *      Author: dkikola
 */

	float LegFontSize = 0.09;
	float LegMargin  = 0.25;
	float MarkerSize  = 2;
	float LineWidth  = 2.0;

void setWindowDressing(){

	TStyle *flowPlotsStyle= new TStyle("flowPlotsStyle","plain plots style");
	//
	// use plain black on white colors

	flowPlotsStyle->SetFrameBorderMode(0);
	flowPlotsStyle->SetCanvasBorderMode(0);
	flowPlotsStyle->SetPadBorderMode(0);
	flowPlotsStyle->SetPadColor(0);
	flowPlotsStyle->SetCanvasColor(0);
	flowPlotsStyle->SetStatColor(0);
	flowPlotsStyle->SetFrameFillColor(0);
	flowPlotsStyle->SetEndErrorSize(1.);

	// set the paper & margin sizes
	flowPlotsStyle->SetPaperSize(20,26);
	flowPlotsStyle->SetPadTopMargin(0.05);
	flowPlotsStyle->SetPadRightMargin(0.03);
	flowPlotsStyle->SetPadBottomMargin(0.16);
	flowPlotsStyle->SetPadLeftMargin(0.12);
	//
	// use large Times-Roman fonts
	flowPlotsStyle->SetTextFont(132);
	flowPlotsStyle->SetTextSize(0.08);
	flowPlotsStyle->SetLabelFont(132,"x");
	flowPlotsStyle->SetTitleFont(132,"x");
	flowPlotsStyle->SetTitleFont(132,"y");
	flowPlotsStyle->SetLabelFont(132,"y");
	flowPlotsStyle->SetLabelFont(132,"z");
	flowPlotsStyle->SetLabelSize(0.06,"x");
	flowPlotsStyle->SetTitleSize(0.07,"x");
	flowPlotsStyle->SetLabelSize(0.06,"y");
	flowPlotsStyle->SetTitleSize(0.07,"y");
	flowPlotsStyle->SetLabelSize(0.06,"z");
	flowPlotsStyle->SetTitleSize(0.07,"z");
	flowPlotsStyle->SetTitleOffset(0.85,"y");
	flowPlotsStyle->SetLegendBorderSize(0.0);

	// use bold lines and markers
	flowPlotsStyle->SetMarkerStyle(20);
	flowPlotsStyle->SetMarkerSize(MarkerSize);
	flowPlotsStyle->SetLineWidth(LineWidth);
	flowPlotsStyle->SetHistLineWidth(LineWidth);
	flowPlotsStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
	//
	// get rid of X error bars and y error bar caps
	//flowPlotsStyle->SetErrorX(0.001);

	// do not display any of the standard histogram decorations
	flowPlotsStyle->SetOptTitle(0);
	flowPlotsStyle->SetOptStat(0);
	flowPlotsStyle->SetOptFit(0);

	// put tick marks on top and RHS of plots
	flowPlotsStyle->SetPadTickX(1);
	flowPlotsStyle->SetPadTickY(1);

	// set large legend fonts

	flowPlotsStyle->cd();
}
