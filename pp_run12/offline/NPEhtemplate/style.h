TLatex* drawLatex(Double_t x,Double_t y,char* text,Int_t textFont,Double_t textSize,Int_t colorIndex){
	TLatex *latex =new TLatex(x,y,text);
	latex->SetNDC();
	latex->SetTextFont(textFont);
	latex->SetTextSize(textSize);
	latex->SetTextColor(colorIndex);
	latex->Draw("same");
	return latex;
}
void setcolz()
{
	const Int_t NRGBs=5;
	const Int_t NCont=32;

	Double_t stops[NRGBs]={0.00,0.34,0.61,0.84,1.00};
	Double_t red[NRGBs]={0.00,0.00,0.87,1.00,0.51};
	Double_t green[NRGBs]={0.00,0.81,1.00,0.20,0.00};
	Double_t blue[NRGBs]={0.51,1.00,0.12,0.00,0.00};
	TColor::CreateGradientColorTable(NRGBs,stops,red,green,blue,NCont);
	gStyle->SetNumberContours(NCont);
}
void setstyle()
{
	TStyle* myStyle = new TStyle("myStyle","Styles");
	myStyle->SetPalette(1,0); // avoid horrible default color scheme
	myStyle->SetOptStat(0);//"e");
	myStyle->SetOptTitle(1);
	myStyle->SetOptDate(0);
	myStyle->SetOptFit(0);
	myStyle->SetEndErrorSize(0.01);
	myStyle->SetLabelSize(0.057,"xyz"); // size of axis value font
	myStyle->SetTitleX(0.2f);
	myStyle->SetTitleY(0.96f);
	myStyle->SetTitleW(0.5f);
	myStyle->SetTickLength(0.025,"xyz");
	myStyle->SetTitleFont(42,"xyz"); // font option 
	myStyle->SetLabelFont(42,"xyz");
	//myStyle->SetTitleOffset(0.8,"z");
	//myStyle->SetTitleOffset(1.2,"y");
	//myStyle->SetTitleFillColor(10);
	myStyle->SetLineWidth(2);
	myStyle->SetCanvasDefW(700);
	myStyle->SetCanvasDefH(600);
	myStyle->SetCanvasColor(0);// canvas...
	myStyle->SetCanvasBorderMode(0);
	myStyle->SetCanvasBorderSize(0);
	myStyle->SetPadColor(0);
	myStyle->SetPadBorderSize(1);
	myStyle->SetPadBorderMode(-1);
	//myStyle->SetPadBottomMargin(0.14); //margins...
	//myStyle->SetPadTopMargin(0.06);
	//myStyle->SetPadLeftMargin(0.14);
	//myStyle->SetPadRightMargin(0.04);
	myStyle->SetPadGridX(0); // grids, tickmarks
	myStyle->SetPadGridY(0);
	myStyle->SetPadTickX(1);
	myStyle->SetPadTickY(1);
	//myStyle->SetFrameBorderSize(1);
	myStyle->SetFrameBorderMode(-1);
	myStyle->SetFrameFillColor(0);
	//myStyle->SetFrameLineWidth(2); // default 2
	myStyle->SetPaperSize(20,24); // US letter size
	gROOT->SetStyle("myStyle");
	cout << "Styles are Set!" << endl;
}
void setstyle1()
{
	TStyle* myStyle = new TStyle("myStyle","Styles");
	myStyle->SetPalette(1,0); // avoid horrible default color scheme
	myStyle->SetOptStat(0);//"e");
	myStyle->SetOptTitle(1);
	myStyle->SetOptDate(0);
	myStyle->SetOptFit(0);
	myStyle->SetEndErrorSize(0.01);
	myStyle->SetLabelSize(0.057,"xyz"); // size of axis value font
	myStyle->SetTitleX(0.2f);
	myStyle->SetTitleY(0.96f);
	myStyle->SetTitleW(0.5f);
	myStyle->SetTickLength(0.025,"xyz");
	myStyle->SetTitleFont(42,"xyz"); // font option 
	myStyle->SetLabelFont(42,"xyz");
	//myStyle->SetTitleFont(62,"xyz"); // font option 
	//myStyle->SetLabelFont(62,"xyz");
	//myStyle->SetTitleOffset(0.8,"z");
	//myStyle->SetTitleOffset(1.2,"y");
	//myStyle->SetTitleFillColor(10);
	//myStyle->SetLineWidth(2);
	myStyle->SetCanvasDefW(700);
	myStyle->SetCanvasDefH(600);
	myStyle->SetCanvasColor(0);// canvas...
	myStyle->SetCanvasBorderMode(0);
	myStyle->SetCanvasBorderSize(0);
	myStyle->SetPadColor(0);
	myStyle->SetPadBorderSize(1);
	myStyle->SetPadBorderMode(-1);
	//myStyle->SetPadBottomMargin(0.14); //margins...
	//myStyle->SetPadTopMargin(0.06);
	//myStyle->SetPadLeftMargin(0.14);
	//myStyle->SetPadRightMargin(0.04);
	myStyle->SetPadGridX(0); // grids, tickmarks
	myStyle->SetPadGridY(0);
	myStyle->SetPadTickX(1);
	myStyle->SetPadTickY(1);
	//myStyle->SetFrameBorderSize(1);
	myStyle->SetFrameBorderMode(-1);
	myStyle->SetFrameFillColor(0);
	//myStyle->SetFrameLineWidth(2);
	myStyle->SetPaperSize(20,24); // US letter size
	gROOT->SetStyle("myStyle");
	cout << "Styles are Set!" << endl;
}

TH1F* histo(const Char_t* name1, Int_t nBins,double xlow1, double xup1, Double_t ylow, Double_t yup, const Char_t* xTitle, const Char_t* yTitle,Double_t xTitleSize,Double_t xTitleOffset,Double_t yTitleSize,Double_t yTitleOffset){
	TH1F *dd = new TH1F(name1,"",nBins,xlow1,xup1);
	dd->SetMinimum(ylow);
	dd->SetMaximum(yup);
	dd->GetXaxis()->SetTitle(xTitle);
	dd->GetYaxis()->SetTitle(yTitle);

	dd->GetXaxis()->SetTitleSize(xTitleSize);
	dd->GetXaxis()->SetTitleOffset(xTitleOffset);
	dd->GetYaxis()->SetTitleSize(yTitleSize);
	dd->GetYaxis()->SetTitleOffset(yTitleOffset);
	//dd->GetXaxis()->CenterTitle(kTRUE);
	//dd->GetYaxis()->CenterTitle(kTRUE);
	dd->GetXaxis()->SetNdivisions(512);
	dd->Draw();
	return dd;
}
TH2F* histo2D(const Char_t* name1, Int_t nBinsx,double xlow1, double xup1, Int_t nBinsy, Double_t ylow, Double_t yup, const Char_t* xTitle, const Char_t* yTitle,Double_t xTitleSize,Double_t xTitleOffset,Double_t yTitleSize,Double_t yTitleOffset){
	TH2F *dd = new TH2F(name1,"",nBinsx,xlow1,xup1,nBinsy,ylow,yup);
	dd->SetMinimum(ylow);
	dd->SetMaximum(yup);
	dd->GetXaxis()->SetTitle(xTitle);
	dd->GetYaxis()->SetTitle(yTitle);

	dd->GetXaxis()->SetTitleSize(xTitleSize);
	dd->GetXaxis()->SetTitleOffset(xTitleOffset);
	dd->GetYaxis()->SetTitleSize(yTitleSize);
	dd->GetYaxis()->SetTitleOffset(yTitleOffset);
	//dd->GetXaxis()->CenterTitle(kTRUE);
	//dd->GetYaxis()->CenterTitle(kTRUE);
	dd->GetXaxis()->SetNdivisions(512);
	dd->Draw();
	return dd;
}

TPaveStats *PaveStats(Double_t xlow,Double_t ylow,Double_t xup,Double_t yup){
	TPaveStats *ptstats= new TPaveStats(xlow,ylow,xup,yup,"brNDC");
	ptstats->SetName("stats");
	ptstats->SetBorderSize(2);
	ptstats->SetFillColor(10);
	ptstats->SetTextAlign(12);
	ptstats->SetTextSize(0.03);
	//ptstats->Draw();
	return ptstats;
}
TCanvas* Canvas(const Char_t* name,Double_t LeftMargin,Double_t RightMargin,Double_t BottomMargin,Double_t TopMargin,int logx,int logy,int logz){
	TCanvas *cc= new TCanvas(name,"",0,0,800,600);
	cc->SetTickx();
	cc->SetTicky();
	cc->SetFillColor(10);
	cc->SetBorderMode(0);
	cc->SetBorderSize(2);
	cc->SetFrameFillColor(0);
	cc->SetFrameBorderMode(0);
	cc->SetLeftMargin(LeftMargin);
	cc->SetRightMargin(RightMargin);
	cc->SetBottomMargin(BottomMargin);
	cc->SetTopMargin(TopMargin);
	cc->SetLogx(logx);
	cc->SetLogy(logy);
	cc->SetLogz(logz);
	return cc;
}
TCanvas* CanvasT(const Char_t* name,Double_t LeftMargin,Double_t RightMargin,Double_t BottomMargin,Double_t TopMargin,int logx,int logy,int logz){
	TCanvas *cc= new TCanvas(name,"",0,0,850,650);
	cc->SetTickx();
	cc->SetTicky();
	cc->SetFillColor(10);
	cc->SetBorderMode(0);
	cc->SetBorderSize(2);
	cc->SetFrameFillColor(0);
	cc->SetFrameBorderMode(0);
	cc->SetLeftMargin(LeftMargin);
	cc->SetRightMargin(RightMargin);
	cc->SetBottomMargin(BottomMargin);
	cc->SetTopMargin(TopMargin);
	cc->SetLogx(logx);
	cc->SetLogy(logy);
	cc->SetLogz(logz);
	return cc;
}
TCanvas* CanvasF(const Char_t* name,Double_t LeftMargin,Double_t RightMargin,Double_t BottomMargin,Double_t TopMargin,int logx,int logy,int logz){
	TCanvas *cc= new TCanvas(name,"",0,0,1200,600);
	cc->SetTickx();
	cc->SetTicky();
	cc->SetFillColor(10);
	cc->SetBorderMode(0);
	cc->SetBorderSize(2);
	cc->SetFrameFillColor(0);
	cc->SetFrameBorderMode(0);
	cc->SetLeftMargin(LeftMargin);
	cc->SetRightMargin(RightMargin);
	cc->SetBottomMargin(BottomMargin);
	cc->SetTopMargin(TopMargin);
	cc->SetLogx(logx);
	cc->SetLogy(logy);
	cc->SetLogz(logz);
	return cc;
}
TLegend* Legend(Double_t xlow,Double_t ylow,Double_t xup,Double_t yup,Double_t TextSize){//,TH1F *H1,const char *word1,const char* option1,TH1F *H2,const char *word2,const char* option2,TH1F *H3,const char *word3,const char* option3){
	TLegend* lg= new TLegend(xlow,ylow,xup,yup);
	lg->SetFillStyle(0);
	lg->SetFillColor(10);
	lg->SetBorderSize(0);
	lg->SetTextSize(TextSize);
	lg->SetTextFont(42);
	//lg->AddEntry(H1,word1,option1);
	//lg->AddEntry(H2,word2,option2);
	//lg->AddEntry(H3,word3,option3);
	lg->Draw();
	return lg;
}
TLine *Line(Double_t xlow,Double_t ylow,Double_t xup,Double_t yup,Double_t LineStyle,Color_t LineColor,Double_t LineWidth){
	TLine *l1 = new TLine(xlow,ylow,xup,yup);
	l1->SetLineWidth(LineWidth);
	l1->SetLineColor(LineColor);
	l1->SetLineStyle(LineStyle);
	l1->Draw();
	return l1;
}
void Style(TH1 *H1,Double_t LineStyle, Color_t LineColor, Double_t LineWidth,Double_t MarkerStyle,Color_t MarkerColor,Double_t MarkerSize,const char *option){
	//TH1F *H1;
	H1->SetLineStyle(LineStyle);
	H1->SetLineColor(LineColor);
	H1->SetLineWidth(LineWidth);
	H1->SetMarkerStyle(MarkerStyle);
	H1->SetMarkerColor(MarkerColor);
	H1->SetMarkerSize(MarkerSize);
	H1->SetTitle("");
	H1->Draw(option);
}
/*void Style(TH2 *H2, Double_t LineStyle, Color_t LineColor, Double_t LineWidth,Double_t MarkerStyle,Color_t MarkerColor,Double_t MarkerSize,const char *option){
	//TH1F *H1;
	H2->SetLineStyle(LineStyle);
	H2->SetLineColor(LineColor);
	H2->SetLineWidth(LineWidth);
	H2->SetMarkerStyle(MarkerStyle);
	H2->SetMarkerColor(MarkerColor);
	H2->SetMarkerSize(MarkerSize);
	H2->SetTitle("");
	H2->Draw(option);
}*/
void StyleFun(TF1 *F1, Double_t LineStyle, Color_t LineColor, Double_t LineWidth, Double_t MarkerStyle, Color_t MarkerColor, Double_t MarkerSize, const char *option){
	//TH1F *H1;
	F1->SetLineStyle(LineStyle);
	F1->SetLineColor(LineColor);
	F1->SetLineWidth(LineWidth);
	F1->SetMarkerStyle(MarkerStyle);
	F1->SetMarkerColor(MarkerColor);
	F1->SetMarkerSize(MarkerSize);
	F1->SetTitle("");
	F1->Draw(option);
}
void StyleTGraph(TGraphErrors *G1, Double_t LineStyle, Color_t LineColor, Double_t LineWidth,Double_t MarkerStyle,Color_t MarkerColor,Double_t MarkerSize,const char *option){
	//TH1F *H1;
	G1->SetLineStyle(LineStyle);
	G1->SetLineColor(LineColor);
	G1->SetLineWidth(LineWidth);
	G1->SetMarkerStyle(MarkerStyle);
	G1->SetMarkerColor(MarkerColor);
	G1->SetMarkerSize(MarkerSize);
	G1->SetTitle("");
	G1->Draw(option);
}
void StyleTGraphAsy(TGraphAsymmErrors *G1, Double_t LineStyle, Color_t LineColor, Double_t LineWidth,Double_t MarkerStyle,Color_t MarkerColor,Double_t MarkerSize,const char *option){
	//TH1F *H1;
	G1->SetLineStyle(LineStyle);
	G1->SetLineColor(LineColor);
	G1->SetLineWidth(LineWidth);
	G1->SetMarkerStyle(MarkerStyle);
	G1->SetMarkerColor(MarkerColor);
	G1->SetMarkerSize(MarkerSize);
	G1->SetTitle("");
	G1->Draw(option);
}
void StyleTGraphT(TGraph *G1, Double_t LineStyle, Color_t LineColor, Double_t LineWidth,Double_t MarkerStyle,Color_t MarkerColor,Double_t MarkerSize,const char *option){
	//TH1F *H1;
	G1->SetLineStyle(LineStyle);
	G1->SetLineColor(LineColor);
	G1->SetLineWidth(LineWidth);
	G1->SetMarkerStyle(MarkerStyle);
	G1->SetMarkerColor(MarkerColor);
	G1->SetMarkerSize(MarkerSize);
	G1->SetTitle("");
	G1->Draw(option);
}
void setpad(TPad *pad,float left, float right, float top, float bottom, int logx, int logy, int logz){
	pad->SetFillColor(10);
	pad->SetBorderMode(0);
	pad->SetBorderSize(0);
	pad->SetFrameFillColor(10);
	pad->SetFrameBorderMode(0);
	pad->SetFrameBorderSize(0);
	pad->SetLeftMargin(left);
	pad->SetRightMargin(right);
	pad->SetTopMargin(top);
	pad->SetBottomMargin(bottom);
	pad->SetLogx(logx);
	pad->SetLogy(logy);
	pad->SetLogz(logz);
	return;
}

TH1D* calEffHist(TH1D *hden, TH1D *hnum)
//TH1F* calEffHist(TH1F *hden, TH1F *hnum)
{   
	Double_t num, den, eff, efferr;
	//TH1F *hEff = (TH1F*) hden->Clone("hEff");
	TH1D *hEff = (TH1D*) hden->Clone("hEff");
	for(int i=0;i<hEff->GetNbinsX();i++) {
		num = hnum->GetBinContent(i+1);
		den = hden->GetBinContent(i+1);
		if(den>0) {
			eff = (num+1)/(den+2);
			efferr = sqrt((num+1)*(num+2)/(den+2)/(den+3)-pow((num+1)/(den+2),2));
		} else {
			eff = 0;
			efferr = 0;
		}
		hEff->SetBinContent(i+1, eff);
		hEff->SetBinError(i+1, efferr);
	}
	return hEff;
}
TH1F* calEffHistB(TH1F *hRc, TH1F *hMc)
{
	TH1F *hEff = (TH1F*) hMc->Clone("hEff");
	//hRc->Sumw2();
	//hMc->Sumw2();
	hRc->SetBinContent(0,0);
	hRc->SetBinContent(hMc->GetNbinsX()+1,0);
	hMc->SetBinContent(0,1e-5);
	hMc->SetBinContent(hMc->GetNbinsX()+1,1e-5);
	for(int i=1;i<hMc->GetNbinsX()+1;i++){
		if(hMc->GetBinContent(i)<=0||hRc->GetBinContent(i)>hMc->GetBinContent(i)){
			hMc->SetBinContent(i,1);
			hRc->SetBinContent(i,1e-2);
		}
	}
	TGraphAsymmErrors *gr2=new TGraphAsymmErrors(hRc,hMc,"B");
	//gr2->BayesDivide(hRc,hMc);

	for(int i=0; i<hMc->GetNbinsX(); i++) {
		double x,y;
		int a=gr2->GetPoint(i,x,y);
		hEff->SetBinContent(i+1,y);
		hEff->SetBinError(i+1,gr2->GetErrorY(i));
	}
	return hEff;
}
