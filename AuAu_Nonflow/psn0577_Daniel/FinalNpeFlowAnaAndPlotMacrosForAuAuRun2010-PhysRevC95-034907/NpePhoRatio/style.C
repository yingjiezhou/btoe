
#define LegFontSize 0.09
#define LegMargin 0.25
#define MarkerSize 1.5


void setWindowDressing(){
	
	TStyle *vNnPaperStyle= new TStyle("vNnPaperStyle","plain plots style");
	//
	// use plain black on white colors
	
	vNnPaperStyle->SetFrameBorderMode(0);
	vNnPaperStyle->SetCanvasBorderMode(0);
	vNnPaperStyle->SetPadBorderMode(0);
	vNnPaperStyle->SetPadColor(0);
	vNnPaperStyle->SetCanvasColor(0);
	vNnPaperStyle->SetStatColor(0);
	vNnPaperStyle->SetFrameFillColor(0);

	// set the paper & margin sizes
	vNnPaperStyle->SetPaperSize(20,26);
	vNnPaperStyle->SetPadTopMargin(0.05);
	vNnPaperStyle->SetPadRightMargin(0.03);
	vNnPaperStyle->SetPadBottomMargin(0.16);
	vNnPaperStyle->SetPadLeftMargin(0.13);
	//
	// use large Times-Roman fonts
	vNnPaperStyle->SetTextFont(132);
	vNnPaperStyle->SetTextSize(0.08);
	vNnPaperStyle->SetLabelFont(132,"x");
	vNnPaperStyle->SetTitleFont(132,"x");
	vNnPaperStyle->SetTitleFont(132,"y");
	vNnPaperStyle->SetLabelFont(132,"y");
	vNnPaperStyle->SetLabelFont(132,"z");
	vNnPaperStyle->SetLabelSize(0.06,"x");
	vNnPaperStyle->SetTitleSize(0.07,"x");
	vNnPaperStyle->SetLabelSize(0.06,"y");
	vNnPaperStyle->SetTitleSize(0.07,"y");
	vNnPaperStyle->SetLabelSize(0.06,"z");
	vNnPaperStyle->SetTitleSize(0.07,"z");
	vNnPaperStyle->SetTitleOffset(0.8,"y");
	vNnPaperStyle->SetLegendBorderSize(0.0);

	// use bold lines and markers
	vNnPaperStyle->SetMarkerStyle(20);
	vNnPaperStyle->SetMarkerSize(MarkerSize);
	vNnPaperStyle->SetLineWidth(2);
	vNnPaperStyle->SetHistLineWidth(3);
	vNnPaperStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
	//
	// get rid of X error bars and y error bar caps
	vNnPaperStyle->SetErrorX(0.001);

	// do not display any of the standard histogram decorations
	vNnPaperStyle->SetOptTitle(0);
	vNnPaperStyle->SetOptStat(0);
	vNnPaperStyle->SetOptFit(0);

	// put tick marks on top and RHS of plots
	vNnPaperStyle->SetPadTickX(1);
	vNnPaperStyle->SetPadTickY(1);
	
	// set large legend fonts

	vNnPaperStyle->cd();
	
//	gROOT->Reset();
//   	gROOT->SetStyle("Plain");
//   	gStyle->SetLabelSize(0.04, "x");
//   	gStyle->SetLabelSize(0.04, "y");
//   	gStyle->SetTitleW(0.60);
//   	gStyle->SetTitleH(0.06);
//   	gStyle->SetOptStat(0);
//   	gStyle->SetOptFit(111);
//   	gStyle->SetOptDate(0);
//   	/* Switch grid off */
//   	gStyle->SetPadGridX(0);
//   	gStyle->SetPadGridY(0);
//   	/* plots properties */
//   	gStyle->SetMarkerSize(0.9);
//   	gStyle->SetPadRightMargin(0.015);
   	
   	
   	
   	
}
