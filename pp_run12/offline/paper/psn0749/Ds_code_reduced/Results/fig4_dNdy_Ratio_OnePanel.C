void fig4_dNdy_Ratio_OnePanel()
{
	gROOT->Reset();
//	gROOT->LoadMacro("~/work/work/fitfun/Levy.C");

	void scaleGraph(TGraphErrors *gr,Double_t scale)
	{
		Int_t NPoint = gr->GetN();
		for(int i=0;i<NPoint;i++)
		{
			Double_t x = gr->GetX()[i];
			Double_t y = gr->GetY()[i];
			Double_t ex = gr->GetEX()[i];
			Double_t ey = gr->GetEY()[i];
			y = scale*y;
			gr->SetPoint(i,x,y);
			gr->SetPointError(i, ex, ey*scale);
		}
	}
	void scaleGraph(TGraphAsymmErrors *gr,Double_t scale)
	{
		Int_t NPoint = gr->GetN();
		for(int i=0;i<NPoint;i++)
		{
			Double_t x = gr->GetX()[i];
			Double_t y = gr->GetY()[i];
			Double_t exl = gr->GetEXlow()[i];
			Double_t eyl = gr->GetEYlow()[i];
			Double_t exh = gr->GetEXhigh()[i];
			Double_t eyh = gr->GetEYhigh()[i];
			y = scale*y;
			gr->SetPoint(i,x,y);
			gr->SetPointError(i,exl,exh,eyl*scale,eyh*scale);
		}
	}


	const Double_t MassDs = 1.9685;
	const Int_t NPt = 5;
	double pT[NPt], y[NPt], ye[NPt], yes[NPt], yet[NPt];
	double x_Pythia[1] = {2}, y_Pythia[1] = {0.17}; 
	double x_Kpi_pp[1] = {2}, y_Kpi_pp[1] = {0.1021}, ye_Kpi_pp[1] = {0.0081}; 
	double x_Kpi[9] = {14.5, 26.93, 47.25, 76.66, 115.49, 166.63, 234.54, 325.85, 352.40};
	double y_Kpi[9] = {0.127, 0.137, 0.143, 0.142, 0.147, 0.145, 0.147, 0.153, 0.151};
	double ye_Kpi[9] = {0.010, 0.011, 0.011, 0.012, 0.013, 0.013, 0.015, 0.017, 0.018};
	
	double x_PhiK_pp[1] = {2}, y_PhiK_pp[1] = {0.12414}, ye_PhiK_pp[1] = {0.025}; 
	double x_PhiK[9] = {14.5+10, 26.93+10, 47.25+10, 76.66+10, 115.49+10, 166.63+10, 234.54+10, 325.85+10, 352.40+10};
	double y_PhiK[9] = {0.14493, 0.15571, 0.15607, 0.17204, 0.17349, 0.17614, 0.18711, 0.16618, 0.16061};
	double ye_PhiK[9] = {2.91e-02, 2.83e-02, 2.85e-02, 2.92e-02, 0.0306, 0.03369, 0.03261, 0.03079, 0.03078}; 
	
	TFile *fin = new TFile("root/DsD0_Ratio.root");
	TGraphErrors *gr_stat_tmp;
	TGraphErrors *gr_sys_tmp;
	TGraphErrors *gr_Kpi = new TGraphErrors(9, x_Kpi, y_Kpi, 0, ye_Kpi);
	TGraphErrors *gr_Kpi_pp = new TGraphErrors(1, x_Kpi_pp, y_Kpi_pp, 0, ye_Kpi_pp);
	TGraphErrors *gr_PhiK = new TGraphErrors(9, x_PhiK, y_PhiK, 0, ye_PhiK);
	TGraphErrors *gr_PhiK_pp = new TGraphErrors(1, x_PhiK_pp, y_PhiK_pp, 0, ye_PhiK_pp);
	TGraphErrors *gr_Pythia = new TGraphErrors(1, x_Pythia, y_Pythia, 0, 0); 
	gr_stat_tmp = (TGraphErrors *)fin->Get("DsD0_err_dNdy_Ratio");
	gr_sys_tmp = (TGraphErrors *)fin->Get("DsD0_sys_dNdy_Ratio");
	gr_stat_tmp->Print();
	TGraphErrors *RHIC_sequential = new TGraphErrors("./DsD0_ratio_Theory/DsD0_Npart_Sequential_coalescence.dat", "%lg %lg %lg %lg");
	for(int j=0;j<NPt;j++) {
	  pT[j] = gr_stat_tmp->GetX()[j];
	  y[j] = gr_stat_tmp->GetY()[j];
	  ye[j] = gr_stat_tmp->GetEY()[j];
	  yes[j] = gr_sys_tmp->GetEY()[j];
	  yet[j] = sqrt(ye[j]*ye[j]+yes[j]*yes[j]);
	  //cout << "pT[j] = " << pT[j] << endl;
	  //cout << "y[j] = " << y[j] << endl;
	  //cout << "ye[j] = " << ye[j] << endl;
	  //cout << "yes[j] = " << yes[j] << endl;
	  //cout << "yet[j] = " << yet[j] << endl;
	}
	TGraphErrors *gr_stat;
	TGraphErrors *gr_stat2;
	TGraphErrors *gr_stat3;
	TGraphErrors *gr_stat4;
	TGraphErrors *gr_total;
	gr_stat = new TGraphErrors(NPt, pT, y, 0, ye);
	gr_stat2 = (TGraphErrors*)gr_stat->Clone("gr_stat2");
	gr_stat3 = (TGraphErrors*)gr_stat->Clone("gr_stat3");
	gr_stat4 = (TGraphErrors*)gr_stat->Clone("gr_stat4");
	
	gr_stat->SetMarkerStyle(20);
	gr_stat->SetMarkerSize(2.5);
	gr_stat->SetMarkerColor(2);
	gr_stat->SetLineColor(1);
	gr_stat->SetLineWidth(2);
	gr_stat2->SetMarkerSize(2.53);
	gr_stat2->SetMarkerStyle(24);
	gr_stat2->SetMarkerColor(1);
	gr_stat2->SetLineWidth(2);
	gr_stat3->SetMarkerSize(2.56);
	gr_stat3->SetMarkerStyle(24);
	gr_stat3->SetMarkerColor(1);
	gr_stat3->SetLineWidth(2);
	
	gr_stat4->SetMarkerSize(2.59);
	gr_stat4->SetMarkerStyle(24);
	gr_stat4->SetMarkerColor(1);
	gr_stat4->SetLineWidth(2);

	RHIC_sequential->SetMarkerSize(2);
	RHIC_sequential->SetMarkerStyle(20);
	RHIC_sequential->SetFillStyle(3001);
	RHIC_sequential->SetFillColor(12);
//	RHIC_sequential->SetMarkerColor(1);	
	RHIC_sequential->SetLineColor(12);
	RHIC_sequential->SetLineStyle(3001);
//	RHIC_sequential->SetLineWidth(2);

	TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
	gStyle->SetOptFit(0);
        gStyle->SetOptStat(0);
        gStyle->SetEndErrorSize(0.001);

        c1->SetFillColor(10);
        c1->SetFillStyle(0);
        c1->SetBorderMode(0);
        c1->SetBorderSize(0);
        c1->SetFrameFillColor(10);
        c1->SetFrameFillStyle(0);
        c1->SetFrameBorderMode(0);
        //  c1->SetLogy();
        c1->SetGridx(0);
        c1->SetGridy(0);
        c1->SetLeftMargin(0.13);
        c1->SetBottomMargin(0.16);
        c1->SetTopMargin(0.02);
        c1->SetRightMargin(0.02);
        c1->Draw();

	double x1 = -10;
	double x2 = 399;
	double y1 = 0.0;
	double y2 = 0.83;
	TH1 *h0 = new TH1D("h0","",1,x1, x2);
	h0->SetMinimum(y1);
	h0->SetMaximum(y2);
	h0->GetXaxis()->SetNdivisions(207);
	h0->GetXaxis()->CenterTitle();
	h0->GetXaxis()->SetTitle("N_{part}");
        h0->GetXaxis()->SetTickLength(0.03);
	h0->GetXaxis()->SetTitleOffset(1.1);
	h0->GetXaxis()->SetTitleSize(0.06);
	h0->GetXaxis()->SetLabelOffset(0.015);
	h0->GetXaxis()->SetLabelSize(0.045);
	h0->GetXaxis()->SetLabelFont(42);
	h0->GetXaxis()->SetTitleFont(42);
	h0->GetYaxis()->SetNdivisions(405);
	h0->GetYaxis()->CenterTitle();
	h0->GetYaxis()->SetTitle("Ratio");
	h0->GetYaxis()->SetTitleOffset(1.);
        h0->GetYaxis()->SetTickLength(0.02);
	h0->GetYaxis()->SetTitleSize(0.06);
	h0->GetYaxis()->SetLabelOffset(0.015);
	h0->GetYaxis()->SetLabelSize(0.045);
	h0->GetYaxis()->SetLabelFont(42);
	h0->GetYaxis()->SetTitleFont(42);
	h0->Draw("c");

	TLine *l1 = new TLine(x1,y1,x2,y1);
	l1->SetLineWidth(3);
	l1->Draw("same");
	TLine *l2 = new TLine(x1,y2,x2,y2);
	l2->SetLineWidth(3);
	l2->Draw("same");
	TLine *l3 = new TLine(x1,y1,x1,y2);
	l3->SetLineWidth(3);
	l3->Draw("same");
	TLine *l4 = new TLine(x2,y1,x2,y2);
	l4->SetLineWidth(3);
	l4->Draw("same");

	RHIC_sequential->Draw("e3");
	const Double_t xoff = 8;
	const Double_t yoff = 0.015;
	for(int j=0;j<NPt;j++) {
		double x1 = pT[j] - xoff;
		double x2 = pT[j] + xoff;
		double y1 = y[j] - yes[j];
		double y2 = y[j] + yes[j];

		TLine *la = new TLine(x1, y1, x1, y1+yoff);
		la->Draw("same");
		TLine *lb = new TLine(x2, y1, x2, y1+yoff);
		lb->Draw("same");
		TLine *lc = new TLine(x1, y2, x1, y2-yoff);
		lc->Draw("same");
		TLine *ld = new TLine(x2, y2, x2, y2-yoff);
		ld->Draw("same");
		TLine *le = new TLine(x1, y1, x2, y1);
		le->SetLineWidth(2);
		le->Draw("same");
		TLine *lf = new TLine(x1, y2, x2, y2);
		lf->SetLineWidth(2);
		lf->Draw("same");
	}
	gr_stat->Draw("p");
	gr_stat2->Draw("p");
	gr_stat3->Draw("p");
	gr_stat4->Draw("p");
/*
	gr_Kpi->SetMarkerStyle(27);
	gr_Kpi->SetMarkerSize(2.0);
	gr_Kpi->SetMarkerColor(1);
	gr_Kpi->SetLineColor(1);
	gr_Kpi->SetLineWidth(1);
	gr_Kpi->Draw("p");    

	gr_Kpi_pp->SetMarkerStyle(33);
	gr_Kpi_pp->SetMarkerSize(2.0);
	gr_Kpi_pp->SetMarkerColor(8);
	gr_Kpi_pp->SetLineColor(8);
	gr_Kpi_pp->SetLineWidth(1);
	gr_Kpi_pp->Draw("p");    

	gr_PhiK->SetMarkerStyle(25);
	gr_PhiK->SetMarkerSize(2.0);
	gr_PhiK->SetMarkerColor(1);
	gr_PhiK->SetLineColor(1);
	gr_PhiK->SetLineWidth(1);
	gr_PhiK->Draw("p"); 

	gr_PhiK_pp->SetMarkerStyle(21);
	gr_PhiK_pp->SetMarkerSize(1.5);
	gr_PhiK_pp->SetMarkerColor(8);
	gr_PhiK_pp->SetLineColor(8);
	gr_PhiK_pp->SetLineWidth(1);
	gr_PhiK_pp->Draw("p"); 
*/
	gr_Pythia->SetMarkerStyle(23);
	gr_Pythia->SetMarkerSize(2.5);
	gr_Pythia->SetMarkerColor(2);
	gr_Pythia->SetLineColor(2);
	gr_Pythia->SetLineWidth(1);   
	gr_Pythia->Draw("p");    

	double x1 = -10;
	double x2 = 399;
	double y1 = 0.01;
	double y2 = 0.83;

	



	gr_Kpi->SetMarkerStyle(24);
        gr_Kpi->SetMarkerSize(2.5);
        gr_Kpi->SetMarkerColor(1);
        gr_Kpi->SetLineColor(1);
        gr_Kpi->SetLineWidth(1);
        gr_Kpi->Draw("p");   

        gr_PhiK->SetMarkerStyle(26);
        gr_PhiK->SetMarkerSize(2.5);
        gr_PhiK->SetMarkerColor(1);
        gr_PhiK->SetLineColor(1);
        gr_PhiK->SetLineWidth(1);
        gr_PhiK->Draw("p");   

	gr_Kpi_pp->SetMarkerStyle(20);
	gr_Kpi_pp->SetMarkerSize(2.5);
	gr_Kpi_pp->SetMarkerColor(1);
	gr_Kpi_pp->SetLineColor(1);
	gr_Kpi_pp->SetLineWidth(1);
	gr_Kpi_pp->Draw("p");    

	gr_PhiK_pp->SetMarkerStyle(23);
	gr_PhiK_pp->SetMarkerSize(2.5);
	gr_PhiK_pp->SetMarkerColor(1);
	gr_PhiK_pp->SetLineColor(1);
	gr_PhiK_pp->SetLineWidth(1);
	gr_PhiK_pp->Draw("p");    


	TLatex *tex = new TLatex(10, y2*0.92, "(D^{+}_{s}+D^{-}_{s})/(D^{0}+#bar{D}^{0})");
        tex->SetTextFont(42);
	tex->SetTextSize(0.045);
	tex->Draw("same");
	

	TLegend *leg = new TLegend(0.17, 0.71, 0.45, 0.89);
        leg->SetFillStyle(0);
        leg->SetLineStyle(0);
        leg->SetLineColor(10);
        leg->SetLineWidth(0.);
        leg->SetTextSize(0.042);
        leg->AddEntry(gr_stat," STAR Au+Au","p");
        leg->AddEntry(RHIC_sequential, "Tsinghua, seq. coal.", "f");
	leg->AddEntry(gr_Pythia," PYTHIA p+p","p");
	leg->Draw("same");

 
	TLegend *leg = new TLegend(0.60, 0.77, 0.85, 0.89);
        leg->SetFillStyle(0);
        leg->SetLineStyle(0);
        leg->SetLineColor(10);
        leg->SetLineWidth(0.);
        leg->SetTextSize(0.045);
        leg->AddEntry(gr_PhiK_pp," ","p");
        leg->AddEntry(gr_Kpi_pp," ","p");
        leg->Draw();
	TLegend *leg = new TLegend(0.66, 0.77, 0.95, 0.89);
        leg->SetFillStyle(0);
        leg->SetLineStyle(0);
        leg->SetLineColor(10);
        leg->SetLineWidth(0.);
        leg->SetTextSize(0.045);
        leg->AddEntry(gr_PhiK," 2#phi/(K^{+}+K^{-})","p");
        leg->AddEntry(gr_Kpi," (K^{+}+K^{-})/(#pi^{+}+#pi^{-})","p");
        // leg->AddEntry(RHIC_sequential, "Tsinghua, seq. coal.", "f");
	// leg->AddEntry(gr_Pythia," PYTHIA p+p","p");
        leg->Draw();

	TLatex *tex = new TLatex(220, y2*0.92, "p+p");
	tex->SetTextFont(22);
	tex->SetTextSize(0.04);
	tex->Draw("same");
	TLatex *tex = new TLatex(250, y2*0.92, "Au+Au");
        tex->SetTextFont(22);
        tex->SetTextSize(0.04);
        tex->Draw("same");

	TLatex *tex = new TLatex(250, y2*0.05, "#sqrt{s_{NN}} = 200 GeV");
	tex->SetTextFont(42);
	tex->SetTextSize(0.055);
	tex->Draw("same");

	// TLatex *tex = new TLatex(20, y2*0.8, "1.5 < p_{T} < 5 GeV/c");
	// tex->SetTextFont(42);
	// tex->SetTextSize(0.08);
	// tex->Draw("same");


	c1->Update();

	c1->SaveAs("fig/fig4_dNdy_Ratio_OnePanel.pdf");
	c1->SaveAs("fig/fig4_dNdy_Ratio_OnePanel.png");


}
