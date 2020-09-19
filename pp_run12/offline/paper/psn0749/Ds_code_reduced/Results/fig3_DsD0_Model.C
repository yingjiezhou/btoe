
void drawSysError(TGraphAsymmErrors *gsyserr,double width=0.2, double length=0.1);
void fig3_DsD0_Model()
{
	gROOT->Reset();

	void shiftTGraph(TGraphErrors *gr1, Float_t shift)
	{
		Int_t NPoint = gr1->GetN();
		for(int i=0;i<NPoint;i++)
		{
			float x = gr1->GetX()[i];
			float y = gr1->GetY()[i];
			float ex = gr1->GetEX()[i];
			float ey = gr1->GetEY()[i];

			gr1->SetPoint(i,x+shift,y);
			gr1->SetPointError(i, ex, ey);
		}
	}


	const Double_t MassDs = 1.9685;
	const Int_t NC = 3;
	const Int_t NPt = 6;
	double pT[NC][NPt], y[NC][NPt], ye[NC][NPt], yes[NC][NPt], yet[NC][NPt];
	TString mCent[6] = {"0_10", "10_40_binning", "40_80", "40_60", "60_80", "10_40"};

	TFile *fin = new TFile("root/DsD0_Ratio.root");
	TGraphErrors *gr_stat_tmp[NC];
	TGraphErrors *gr_sys_tmp[NC];
	for(int i=0;i<NC;i++) {
		gr_stat_tmp[i] = (TGraphErrors *)fin->Get(Form("DsD0_err_%s_Ratio", mCent[i].Data()));
		gr_sys_tmp[i] = (TGraphErrors *)fin->Get(Form("DsD0_sys_%s_Ratio", mCent[i].Data()));

		if (i == 1) 
		{
			shiftTGraph(gr_stat_tmp[1], -0.12*1);
			shiftTGraph(gr_sys_tmp[1], -0.12*1);
		}
		gr_stat_tmp[i]->Print();
		for(int j=0;j<NPt;j++) {
			pT[i][j] = gr_stat_tmp[i]->GetX()[j];
			y[i][j] = gr_stat_tmp[i]->GetY()[j];
			ye[i][j] = gr_stat_tmp[i]->GetEY()[j];
			yes[i][j] = gr_sys_tmp[i]->GetEY()[j];  
			yet[i][j] = sqrt(ye[i][j]*ye[i][j]+yes[i][j]*yes[i][j]);
		}
	}

	TGraphErrors *gr_stat[NC];
	TGraphErrors *gr_total[NC];
	const Int_t kMarkerStyle[NC] = {20, 20, 20};
	const Int_t kColor[NC] = {1,1,1};
	for(int i=0;i<NC;i++) {
		gr_stat[i] = new TGraphErrors(NPt, pT[i], y[i], 0, ye[i]);
		gr_stat[i]->SetMarkerSize(2.);
		gr_stat[i]->SetMarkerColor(kColor[i]);
		gr_stat[i]->SetLineWidth(2);
		gr_stat[i]->SetLineColor(kColor[i]);
		gr_stat[i]->SetMarkerStyle(kMarkerStyle[i]);

		gr_total[i] = new TGraphErrors(NPt, pT[i], y[i], 0, yet[i]);
	}

	// pythia
	TFile *f_p = new TFile("root/ALICE_pp7TeV_PbPb5TeV_Pythia.root");
	TH1D *h_p = (TH1D *)f_p->Get("Pythia_Monash_tune_200GeV");

	TH1D *h_p_LHC = (TH1D *)f_p->Get("Pythia_Monash_tune_7TeV");
	TGraphAsymmErrors *gr_pp7TeV = (TGraphAsymmErrors *)f_p->Get("pp7GeV");  
	TGraphAsymmErrors *gr_3050_PbPb5TeV = (TGraphAsymmErrors *)f_p->Get("PbPb5TeV_3050");  
	TGraphAsymmErrors *gr_010_PbPb5TeV = (TGraphAsymmErrors *)f_p->Get("PbPb5TeV_010");  
	TGraphAsymmErrors *gr_pp7TeV_sys = (TGraphAsymmErrors *)f_p->Get("pp7GeV_sys");  
	TGraphAsymmErrors *gr_3050_PbPb5TeV_sys = (TGraphAsymmErrors *)f_p->Get("PbPb5TeV_3050_sys");  
	TGraphAsymmErrors *gr_010_PbPb5TeV_sys = (TGraphAsymmErrors *)f_p->Get("PbPb5TeV_010_sys");  

	TGraphErrors *RHIC_sequential = new TGraphErrors("./DsD0_ratio_Theory/Theory_results_RHIC_sequential.dat", "%lg %lg %lg %lg");
	TGraphErrors *RHIC_sequential_010 = new TGraphErrors("./DsD0_ratio_Theory/Theory_results_RHIC_sequential.dat", "%lg %lg %lg %lg");
	TGraphErrors *RHIC_simultaneous = new TGraphErrors("./DsD0_ratio_Theory/Theory_results_RHIC_simultaneous.dat", "%lg %lg %lg %lg");
	TGraphErrors *LHC_sequential = new TGraphErrors("./DsD0_ratio_Theory/Theory_results_LHC_sequential.dat", "%lg %lg %lg %lg");
	TGraphErrors *LHC_simultaneous = new TGraphErrors("./DsD0_ratio_Theory/Theory_results_LHC_simultaneous.dat", "%lg %lg %lg %lg");
	TGraphErrors *RHIC_010_coal = new TGraphErrors("./DsD0_ratio_Theory/coal_0_10.dat", "%lg %lg %lg %lg");
	TGraphErrors *RHIC_010_coal_fragm = new TGraphErrors("./DsD0_ratio_Theory/coal_fragm_0_10.dat", "%lg %lg %lg %lg");
	TGraphErrors *RHIC_020_TAMU = new TGraphErrors("./DsD0_ratio_Theory/TMMU_0-20%_DsD0_Ratio.dat", "%lg %lg %lg %lg");
	TGraphErrors *RHIC_010_Shanshan = new TGraphErrors("./DsD0_ratio_Theory/ratio_Ds_D0_010_Shanshan.dat", "%lg %lg %lg %lg");
	TGraphErrors *RHIC_1040_Shanshan = new TGraphErrors("./DsD0_ratio_Theory/ratio_Ds_D0_1040_Shanshan.dat", "%lg %lg %lg %lg");

	gr_pp7TeV->SetMarkerSize(1.5);
	gr_pp7TeV->SetMarkerColor(28);
	gr_pp7TeV->SetMarkerStyle(20);
	gr_pp7TeV->SetLineColor(28);
	gr_pp7TeV->SetLineWidth(2);
	gr_pp7TeV_sys->SetLineColor(28);
	gr_pp7TeV_sys->SetLineWidth(1);

	gr_010_PbPb5TeV->SetMarkerSize(1.5);
	gr_010_PbPb5TeV->SetMarkerColor(1);
	gr_010_PbPb5TeV->SetMarkerStyle(24);
	gr_010_PbPb5TeV->SetLineColor(1);
	gr_010_PbPb5TeV->SetLineWidth(2);
	gr_010_PbPb5TeV_sys->SetLineColor(1);
	gr_010_PbPb5TeV_sys->SetLineWidth(1);

	RHIC_simultaneous->SetLineColor(1);
	RHIC_simultaneous->SetLineStyle(7);
	RHIC_simultaneous->SetLineWidth(2);

	RHIC_sequential->SetLineColor(1);
	RHIC_sequential->SetLineStyle(8);
	RHIC_sequential->SetLineWidth(2);

	RHIC_sequential_010->SetLineColor(1);
	RHIC_sequential_010->SetLineStyle(5);
	RHIC_sequential_010->SetLineWidth(2);

	RHIC_1040_Shanshan->SetLineColor(2);
	RHIC_1040_Shanshan->SetLineStyle(9);
	RHIC_1040_Shanshan->SetLineWidth(2);

	RHIC_010_coal->SetLineColor(1);
	RHIC_010_coal->SetLineStyle(2);
	RHIC_010_coal->SetLineWidth(2);

	RHIC_010_coal_fragm->SetLineColor(1);
	RHIC_010_coal_fragm->SetLineStyle(1);
	RHIC_010_coal_fragm->SetLineWidth(2);

	RHIC_010_Shanshan->SetLineColor(1);
	RHIC_010_Shanshan->SetLineStyle(9);
	RHIC_010_Shanshan->SetLineWidth(2);


	RHIC_020_TAMU->SetLineColor(1);
	RHIC_020_TAMU->SetLineStyle(10);
	RHIC_020_TAMU->SetLineWidth(2);

	TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,800);
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);
	gStyle->SetEndErrorSize(0.001);
	c1->cd();
	TPad *p1=new TPad("p1","p1",0.,0,1.,1.);
	p1->SetFillColor(10);
	p1->SetFillStyle(0);
	p1->SetBorderMode(0);
	p1->SetBorderSize(0);
	p1->SetFrameFillColor(10);
	p1->SetFrameFillStyle(0);
	p1->SetFrameBorderMode(0);
	//  c1->SetLogy();
	p1->SetGridx(0);
	p1->SetGridy(0);
	p1->SetLeftMargin(0.15);
	p1->SetBottomMargin(0.16);
	p1->SetTopMargin(0.02);
	p1->SetRightMargin(0.02);
	p1->Draw();
	p1->Divide(1,2,0);
	p1->cd(1);
	double x1 = 0.2;
	double x2 = 7.5;
	double y1 = 0.01;
	double y2 = 0.95;
	TH1 *h0 = new TH1D("h0","",1,x1, x2);
	h0->SetMinimum(y1);
	h0->SetMaximum(y2);
	h0->GetXaxis()->SetNdivisions(208);
	h0->GetXaxis()->CenterTitle();
	h0->GetXaxis()->SetTitle("Transverse Momentum p_{T} (GeV/c)");
	h0->GetXaxis()->SetTitleOffset(1.1);
	h0->GetXaxis()->SetTickLength(0.03);
	h0->GetXaxis()->SetTitleSize(0.09);
	h0->GetXaxis()->SetLabelOffset(0.01);
	h0->GetXaxis()->SetLabelSize(0.08);
	h0->GetXaxis()->SetLabelFont(42);
	h0->GetXaxis()->SetTitleFont(42);
	h0->GetYaxis()->SetNdivisions(305);
	h0->GetYaxis()->CenterTitle();
	h0->GetYaxis()->SetTitle("(D_{s}^{+}+D_{s}^{-})/(D^{0}+#bar{D}^{0})");
	h0->GetYaxis()->SetTitleOffset(0.8);
	h0->GetYaxis()->SetTickLength(0.02);
	h0->GetYaxis()->SetTitleSize(0.09);
	h0->GetYaxis()->SetLabelOffset(0.015);
	h0->GetYaxis()->SetLabelSize(0.08);
	h0->GetYaxis()->SetLabelFont(42);
	h0->GetYaxis()->SetTitleFont(42);
	h0->Draw("c");

	TLine *l1 = new TLine(x1,y1,x2,y1);
	l1->SetLineWidth(2);
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

	h_p->SetLineColor(8);
	h_p->SetLineWidth(3);
	h_p->Draw("samec");


	RHIC_010_coal->Draw("same");
	RHIC_010_Shanshan->Draw("same");
	RHIC_010_coal_fragm->Draw("same");
	RHIC_020_TAMU->Draw("same");
//	RHIC_sequential_010->Draw("same");
//	RHIC_simultaneous->Draw("same");

	const Int_t kLineStyle[NC] = {1, 2, 1};
	for(int i=0;i<1;i++) {
		if (i==1) NPt2 = 5;
		else NPt2 = 4;
		for(int j=0;j<NPt2;j++) {
			double x1 = pT[i][j] - 0.12;
			double x2 = pT[i][j] + 0.12;
			double y1 = y[i][j] - yes[i][j];
			double y2 = y[i][j] + yes[i][j];

			TLine *la = new TLine(x1, y1, x1, y1+0.015);
			la->SetLineColor(kColor[i]);
			la->Draw("same");
			TLine *lb = new TLine(x2, y1, x2, y1+0.015);
			lb->SetLineColor(kColor[i]);
			lb->Draw("same");
			TLine *lc = new TLine(x1, y2, x1, y2-0.015);
			lc->SetLineColor(kColor[i]);
			lc->Draw("same");
			TLine *ld = new TLine(x2, y2, x2, y2-0.015);
			ld->SetLineColor(kColor[i]);
			ld->Draw("same");
			TLine *le = new TLine(x1, y1, x2, y1);
			le->SetLineColor(kColor[i]);
			le->SetLineWidth(2);
			le->Draw("same");
			TLine *lf = new TLine(x1, y2, x2, y2);
			lf->SetLineColor(kColor[i]);
			lf->SetLineWidth(2);
			lf->Draw("same");
		}

		gr_stat[i]->Draw("p");
	}

	double x1 = 0.2;
	double x2 = 7.5;
	double y1 = 0.01;
	double y2 = 0.95;

	TLegend *leg = new TLegend(0.2, 0.88, 0.4, 0.96);
	leg->SetFillStyle(0);
	leg->SetLineStyle(0);
	leg->SetLineColor(10);
	leg->SetLineWidth(0.);
	leg->SetTextSize(0.08);
	leg->AddEntry(gr_stat[0]," Au+Au 0-10%","p");
	leg->Draw("same");

	// TLatex *tex = new TLatex(0.6, y2*0.9, "Au+Au 0-10%");
	// tex->SetTextFont(42);
	// tex->SetTextSize(0.08);
	// tex->Draw("same");
	TLatex *tex = new TLatex(0.6, y2*0.8, "#sqrt{s_{NN}} = 200 GeV");
	tex->SetTextFont(42);
	tex->SetTextSize(0.08);
	tex->Draw("same");

	TLatex *tex = new TLatex(x2*0.9, y2*0.07, "(a)");
	tex->SetTextFont(42);
	tex->SetTextSize(0.08);
	tex->Draw("same");


	const Char_t *txt[NC] = {"0-10%","10-40%","40-80%"};
	TLegend *leg = new TLegend(0.6, 0.6, 0.95, 0.97);
	leg->SetFillStyle(0);
	leg->SetLineStyle(0);
	leg->SetLineColor(10);
	leg->SetLineWidth(0.);
	leg->SetTextSize(0.07);
	leg->AddEntry(RHIC_010_coal,"Catania, coal.","l");
	leg->AddEntry(RHIC_010_coal_fragm,"Catania, coal.+frag.","l");
	leg->AddEntry(RHIC_010_Shanshan,"Cao,Ko","l");
	leg->AddEntry(RHIC_020_TAMU,"He,Rapp, 0-20%","l");
//	leg->AddEntry(RHIC_sequential_010,"Tsinghua, seq. coal.","l");
	leg->AddEntry(h_p,"PYTHIA p+p","l");
	leg->Draw();

	p1->cd(2);
	double x1 = 0.2;
	double x2 = 7.5;
	double y1 = 0.01;
	double y2 = 0.95;
	TH1 *h0 = new TH1D("h0","",1,x1, x2);
	h0->SetMinimum(y1);
	h0->SetMaximum(y2);
	h0->GetXaxis()->SetNdivisions(208);
	h0->GetXaxis()->CenterTitle();
	h0->GetXaxis()->SetTitle("Transverse Momentum p_{T} (GeV/c)");
	h0->GetXaxis()->SetTitleOffset(1.1);
	h0->GetXaxis()->SetTickLength(0.03);
	h0->GetXaxis()->SetTitleSize(0.073);
	h0->GetXaxis()->SetLabelOffset(0.01);
	h0->GetXaxis()->SetLabelSize(0.066);
	h0->GetXaxis()->SetLabelFont(42);
	h0->GetXaxis()->SetTitleFont(42);
	h0->GetYaxis()->SetNdivisions(305);
	h0->GetYaxis()->CenterTitle();
	h0->GetYaxis()->SetTitle("(D_{s}^{+}+D_{s}^{-})/(D^{0}+#bar{D}^{0})");
	h0->GetYaxis()->SetTitleOffset(1);
	h0->GetYaxis()->SetTickLength(0.025);
	h0->GetYaxis()->SetTitleSize(0.073);
	h0->GetYaxis()->SetLabelOffset(0.015);
	h0->GetYaxis()->SetLabelSize(0.066);
	h0->GetYaxis()->SetLabelFont(42);
	h0->GetYaxis()->SetTitleFont(42);
	h0->Draw("c");

	TLine *l1 = new TLine(x1,y1,x2,y1);
	l1->SetLineWidth(3);
	l1->Draw("same");
	TLine *l2 = new TLine(x1,y2,x2,y2);
	l2->SetLineWidth(2);
	l2->Draw("same");
	TLine *l3 = new TLine(x1,y1,x1,y2);
	l3->SetLineWidth(3);
	l3->Draw("same");
	TLine *l4 = new TLine(x2,y1,x2,y2);
	l4->SetLineWidth(3);
	l4->Draw("same");

	h_p->SetLineColor(8);
	h_p->SetLineWidth(3);
	h_p->Draw("samec");


	RHIC_sequential->Draw("same");
	RHIC_simultaneous->Draw("same");
	//RHIC_1040_Shanshan->Draw("same");
	const Int_t kLineStyle[NC] = {1, 2, 1};
	for(int i=1;i<2;i++) {
		if (i==1) NPt2 = 5;
		else NPt2 = 4;
		for(int j=0;j<NPt2;j++) {
			double x1 = pT[i][j] - 0.12;
			double x2 = pT[i][j] + 0.12;
			double y1 = y[i][j] - yes[i][j];
			double y2 = y[i][j] + yes[i][j];

			TLine *la = new TLine(x1, y1, x1, y1+0.015);
			la->SetLineColor(kColor[i]);
			la->Draw("same");
			TLine *lb = new TLine(x2, y1, x2, y1+0.015);
			lb->SetLineColor(kColor[i]);
			lb->Draw("same");
			TLine *lc = new TLine(x1, y2, x1, y2-0.015);
			lc->SetLineColor(kColor[i]);
			lc->Draw("same");
			TLine *ld = new TLine(x2, y2, x2, y2-0.015);
			ld->SetLineColor(kColor[i]);
			ld->Draw("same");
			TLine *le = new TLine(x1, y1, x2, y1);
			le->SetLineColor(kColor[i]);
			le->SetLineWidth(2);
			le->Draw("same");
			TLine *lf = new TLine(x1, y2, x2, y2);
			lf->SetLineColor(kColor[i]);
			lf->SetLineWidth(2);
			lf->Draw("same");
		}

		gr_stat[i]->Draw("p");
	}

	double x1 = 0.2;
	double x2 = 7.5;
	double y1 = 0.0;
	double y2 = 0.95;
	TLegend *leg = new TLegend(0.2, 0.89, 0.4, 0.97);
	leg->SetFillStyle(0);
	leg->SetLineStyle(0);
	leg->SetLineColor(10);
	leg->SetLineWidth(0.);
	leg->SetTextSize(0.063);
	leg->AddEntry(gr_stat[1]," Au+Au 10-40%","p");
	leg->Draw("same");
	TLatex *tex = new TLatex(0.6, y2*0.78, "#sqrt{s_{NN}} = 200 GeV"); 
	tex->SetTextFont(42);
	tex->SetTextSize(0.066);
	tex->Draw("same");
	TLatex *tex = new TLatex(x2*0.9, y2*0.09, "(b)");
	tex->SetTextFont(42);
	tex->SetTextSize(0.07);
	tex->Draw("same");


	const Char_t *txt[NC] = {"0-10%","10-40%","40-80%"};
	TLegend *leg = new TLegend(0.6, 0.75, 0.96, 0.97);
	leg->SetFillStyle(0);
	leg->SetLineStyle(0);
	leg->SetLineColor(10);
	leg->SetLineWidth(0.);
	leg->SetTextSize(0.058);
	leg->AddEntry(RHIC_sequential,"Tsinghua, seq. coal.","l");
	leg->AddEntry(RHIC_simultaneous,"Tsinghua, sim. coal.","l"); 
//	leg->AddEntry(RHIC_1040_Shanshan,"Cao, Ko","l");
	leg->AddEntry(h_p,"PYTHIA p+p","l");
	leg->Draw();



	c1->Update();

	c1->SaveAs("fig/fig3_DsD0_Model.pdf");
	c1->SaveAs("fig/fig3_DsD0_Model.png");


}


void drawSysError(TGraphAsymmErrors *gsyserr,double width, double length)
{
	//cout<<"num = " << gsyserr->GetN()<<endl; 
	for(int i=0;i<gsyserr->GetN();i++) {
		float x   = gsyserr->GetX()[i];
		float y   = gsyserr->GetY()[i];
		float ey_l  = gsyserr->GetEYlow()[i];
		float ey_h  = gsyserr->GetEYhigh()[i];
		double x1 = x - width;
		double x2 = x + width;
		double y1 = y - ey_l;
		double y2 = y + ey_h;
		double len = length;
		//cout<< " y = " << y<<  endl;
		//cout << " ey_l = " << ey_l << "ey_h =  " << ey_h << endl;
		// cout << " x1 = " << x1 << "x2 = " << x2 << "y1 = " << y1 << "y2 = " << y2<< endl;  
		TLine *l1 = new TLine(x1,y1,x2,y1); // -
		l1->SetLineWidth(2);
		l1->SetLineColor(gsyserr->GetMarkerColor());
		l1->Draw("same");
		TLine *l2 = new TLine(x1,y2,x2,y2); // -
		l2->SetLineWidth(2);
		l2->SetLineColor(gsyserr->GetMarkerColor());
		l2->Draw("same");
		TLine *l3 = new TLine(x1,y1,x1,y1+len);
		l3->SetLineWidth(2);
		l3->SetLineColor(gsyserr->GetMarkerColor());
		l3->Draw("same");
		TLine *l4 = new TLine(x1,y2,x1,y2-len);
		l4->SetLineWidth(2);
		l4->SetLineColor(gsyserr->GetMarkerColor());
		l4->Draw("same");
		TLine *l5 = new TLine(x2,y1,x2,y1+len);
		l5->SetLineWidth(2);
		l5->SetLineColor(gsyserr->GetMarkerColor());
		l5->Draw("same");
		TLine *l6 = new TLine(x2,y2,x2,y2-len);
		l6->SetLineWidth(2);
		l6->SetLineColor(gsyserr->GetMarkerColor());
		l6->Draw("same");
	}
}

