
void drawSysError(TGraphAsymmErrors *gsyserr,double width=0.2, double length=0.1);
void drawSysError(TGraphErrors *gsyserr,double width=0.2, double length=0.1);
void fig2_DsD0_ALICE()
{
	gROOT->Reset();

	const Double_t MassDs = 1.9685;
	const Int_t NC = 3;
	const Int_t NPt = 6;
	double pT[NC][NPt], y[NC][NPt], ye[NC][NPt], yes[NC][NPt], yet[NC][NPt];
	TString mCent[6] = {"0_10", "10_40_binning", "40_80", "40_60", "60_80", "10_40"};
	cout << "flag1" << endl;
	TFile *fin = new TFile("root/DsD0_Ratio.root");
	TGraphErrors *gr_stat_tmp[NC];
	TGraphErrors *gr_sys_tmp[NC];
	for(int i=0;i<NC;i++)
	{
		gr_stat_tmp[i] = (TGraphErrors *)fin->Get(Form("DsD0_err_%s_Ratio", mCent[i].Data()));
		gr_sys_tmp[i] = (TGraphErrors *)fin->Get(Form("DsD0_sys_%s_Ratio", mCent[i].Data()));
		gr_stat_tmp[i]->Print();

		for(int j=0;j<NPt;j++)
		{
			pT[i][j] = gr_stat_tmp[i]->GetX()[j];
			y[i][j] = gr_stat_tmp[i]->GetY()[j];
			ye[i][j] = gr_stat_tmp[i]->GetEY()[j];
			yes[i][j] = gr_sys_tmp[i]->GetEY()[j];
			yet[i][j] = sqrt(ye[i][j]*ye[i][j]+yes[i][j]*yes[i][j]);
//cout << "y[i][j] =" << y[i][j] << endl;
//cout << "pT[i][j] =" << pT[i][j] << endl;
//cout << "yes[i][j] =" << yes[i][j] << endl;
		}
	}

	TGraphErrors *gr_stat[NC];
	TGraphErrors *gr_total[NC];
	const Int_t kMarkerStyle[NC] = {20, 24, 22};
	const Int_t kColor[NC] = {1,2,4};
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

//	TGraphErrors *RHIC_sequential = new TGraphErrors("Theory_results_RHIC_sequential.dat", "%lg %lg %lg %lg");
//	TGraphErrors *RHIC_simultaneous = new TGraphErrors("Theory_results_RHIC_simultaneous.dat", "%lg %lg %lg %lg");
//	TGraphErrors *RHIC_010_coal = new TGraphErrors("coal_0_10.dat", "%lg %lg %lg %lg");
//	TGraphErrors *RHIC_010_coal_fragm = new TGraphErrors("coal_fragm_0_10.dat", "%lg %lg %lg %lg");

	gr_pp7TeV->SetMarkerSize(1.8);
	gr_pp7TeV->SetMarkerColor(28);
	gr_pp7TeV->SetMarkerStyle(20);
	gr_pp7TeV->SetLineColor(28);
	gr_pp7TeV->SetLineWidth(2);
	gr_pp7TeV_sys->SetLineColor(28);
	gr_pp7TeV_sys->SetLineWidth(1);

	gr_010_PbPb5TeV->SetMarkerSize(1.8);
	gr_010_PbPb5TeV->SetMarkerColor(1);
	gr_010_PbPb5TeV->SetMarkerStyle(24);
	gr_010_PbPb5TeV->SetLineColor(1);
	gr_010_PbPb5TeV->SetLineWidth(2);
	gr_010_PbPb5TeV_sys->SetLineColor(1);
	gr_010_PbPb5TeV_sys->SetLineWidth(1);

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
	double x2 = 11;
	double y1 = 0.01;
	double y2 = 0.85;
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

	h_p_LHC->SetLineColor(6);
	h_p_LHC->SetLineWidth(3);

	const Int_t kLineStyle[NC] = {1, 2, 1};
	for(int i=0;i<NC;i++) {
if (i==1) int NPt2 = 5;
else  NPt2 = 4;
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
	double x2 = 11;
	double y1 = 0.01;
	double y2 = 0.85;

	TLatex *tex = new TLatex(0.9, y2*0.88, "STAR Au+Au");
	tex->SetTextFont(42);
	tex->SetTextSize(0.08);
	tex->Draw("same");
	TLatex *tex = new TLatex(0.9, y2*0.78, "#sqrt{s_{NN}} = 200 GeV");
	tex->SetTextFont(42);
	tex->SetTextSize(0.08);
	tex->Draw("same");
	TLatex *tex = new TLatex(x2*0.9, y2*0.08, "(a)");
	tex->SetTextFont(42);
	tex->SetTextSize(0.095);
	tex->Draw("same");


	const Char_t *txt[NC] = {" 0-10%"," 10-40%"," 40-80%"};
	TLegend *leg = new TLegend(0.76, 0.55, 0.96, 0.96);
	leg->SetFillStyle(0);
	leg->SetLineStyle(0);
	leg->SetLineColor(10);
	leg->SetLineWidth(0.);
	leg->SetTextSize(0.075);

	for(int i=0;i<NC;i++) {
		leg->AddEntry(gr_stat[i],txt[i],"p");
	}
	leg->AddEntry(h_p, " PYTHIA","l");
	leg->Draw();


	TLatex *tex = new TLatex(7.5, 0.12, "PYTHIA");
	tex->SetTextFont(42);
	tex->SetTextAngle(3);
	tex->SetTextSize(0.08);
	//	tex->Draw("same");

	p1->cd(2);
	double x1 = 0.2;
	double x2 = 11;
	double y1 = 0.0;
	double y2 = 0.85;
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

	h_p_LHC->SetLineColor(6);
	h_p_LHC->SetLineWidth(3);
	h_p_LHC->Draw("samec");


	gr_pp7TeV->Draw("psame"); 
	drawSysError(gr_pp7TeV_sys,0.1,0.01);
	gr_010_PbPb5TeV->Draw("psame"); 
	drawSysError(gr_010_PbPb5TeV_sys,0.12,0.012);
	const Int_t kLineStyle[NC] = {1, 2, 1};
	for(int i=0;i<1;i++) {
if (i==1) int NPt2 = 5;
else  NPt2 = 4;

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
	double x2 = 11;
	double y1 = 0.01;
	double y2 = 0.85;

	TLatex *tex = new TLatex(x2*0.9, y2*0.88, "(b)");
	tex->SetTextFont(42);
	tex->SetTextSize(0.08);
	tex->Draw("same");


	const Char_t *txt[NC] = {"0-10%","10-40%","40-80%"};
	TLegend *leg = new TLegend(0.2, 0.73, 0.45, 0.95);;
	leg->SetFillStyle(0);
	leg->SetLineStyle(0);
	leg->SetLineColor(10);
	leg->SetLineWidth(0.);
	leg->SetTextSize(0.06);
	leg->AddEntry(gr_stat[0], "STAR Au+Au 200 GeV (0-10%)", "p");
	leg->AddEntry(gr_010_PbPb5TeV, "ALICE Pb+Pb 5.02 TeV (0-10%)", "p");
	leg->AddEntry(gr_pp7TeV, "ALICE p+p 7 TeV", "p");
	leg->Draw();

	TLatex *tex = new TLatex(1.8, y2*0.05, "PYTHIA p+p");
	tex->SetTextFont(42);
	tex->SetTextSize(0.06);
	tex->Draw("same");
	TLegend *leg = new TLegend(0.52, 0.2, 0.7, 0.3);;
	leg->SetFillStyle(0);
	leg->SetLineStyle(0);
	leg->SetLineColor(10);
	leg->SetLineWidth(0.);
	leg->SetTextSize(0.06);
	leg->AddEntry(h_p, "200 GeV", "l");
	leg->Draw();
	TLegend *leg = new TLegend(0.72, 0.2, 0.9, 0.3);;
	leg->SetFillStyle(0);
	leg->SetLineStyle(0);
	leg->SetLineColor(10);
	leg->SetLineWidth(0.);
	leg->SetTextSize(0.06);
	leg->AddEntry(h_p_LHC, "7 TeV", "l");
	leg->Draw();

	c1->Update();

	c1->SaveAs("fig/fig2_DsD0_ALICE.pdf");
	c1->SaveAs("fig/fig2_DsD0_ALICE.png");


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
		l3->SetLineWidth(1);
		l3->SetLineColor(gsyserr->GetMarkerColor());
		l3->Draw("same");
		TLine *l4 = new TLine(x1,y2,x1,y2-len);
		l4->SetLineWidth(1);
		l4->SetLineColor(gsyserr->GetMarkerColor());
		l4->Draw("same");
		TLine *l5 = new TLine(x2,y1,x2,y1+len);
		l5->SetLineWidth(1);
		l5->SetLineColor(gsyserr->GetMarkerColor());
		l5->Draw("same");
		TLine *l6 = new TLine(x2,y2,x2,y2-len);
		l6->SetLineWidth(1);
		l6->SetLineColor(gsyserr->GetMarkerColor());
		l6->Draw("same");
	}
}
/*void drawSysError(TGraphErrors *gsyserr,double width, double length)
  {
//cout<<"num = " << gsyserr->GetN()<<endl; 
for(int i=0;i<gsyserr->GetN();i++) {
float x   = gsyserr->GetX()[i];
float y   = gsyserr->GetY()[i];
float ey_l  = gsyserr->GetEY()[i];
float ey_h  = gsyserr->GetEY()[i];
double x1 = x - width;
double x2 = x + width;
double y1 = y - ey_l;
double y2 = y + ey_h;
double len = length;
//      cout<< " y = " << y<<  endl;
//            cout << " ey_l = " << ey_l << "ey_h =  " << ey_h << endl; 
//         cout << " x1 = " << x1 << "x2 = " << x2 << "y1 = " << y1 << "y2 = " << y2<< endl;
TLine *l1 = new TLine(x1,y1,x2,y1); // -
l1->SetLineWidth(2.5);
l1->SetLineColor(gsyserr->GetMarkerColor());
l1->Draw("same");
TLine *l2 = new TLine(x1,y2,x2,y2); // -
l2->SetLineWidth(2.5);
l2->SetLineColor(gsyserr->GetMarkerColor());
l2->Draw("same");
TLine *l3 = new TLine(x1,y1,x1,y1+len);
l3->SetLineWidth(2.5);
l3->SetLineColor(gsyserr->GetMarkerColor());
l3->Draw("same");
TLine *l4 = new TLine(x1,y2,x1,y2-len);
l4->SetLineWidth(2.5);
l4->SetLineColor(gsyserr->GetMarkerColor());
l4->Draw("same");
TLine *l5 = new TLine(x2,y1,x2,y1+len);
l5->SetLineWidth(2.5);
l5->SetLineColor(gsyserr->GetMarkerColor());
l5->Draw("same");
TLine *l6 = new TLine(x2,y2,x2,y2-len);
l6->SetLineWidth(2.5);
l6->SetLineColor(gsyserr->GetMarkerColor());
l6->Draw("same");
}

}*/
