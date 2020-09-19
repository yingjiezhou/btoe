/*
 * plotRes200GeV.C
 *
 *  Created on: Jul 15, 2012
 *      Author: dkikola
 */
#include "style.C"

void plotPurityPhoEleRecoEff(){

	gROOT->ForceStyle();
	setWindowDressing();

	int errXwidth  = 6; //the size of the lines at the end of the error bars 
	gStyle->SetEndErrorSize(errXwidth);
	
	float Xmin = 0.25, Xmax = 9.5;
	float Ymin = 0.0, Ymax = 1.2;
	float YminEff = 0., YmaxEff = 0.8;
	

	TString purity_200GeV_fname = "data/DataForNpeStudy/EffPurity/purity_AuAu200GeV_CalculatedVsPconvertedToPt.root";
	TString purity_62GeV_fname = "data/DataForNpeStudy/EffPurity/purity_AuAu62GeV_CalculatedVsPconvertedToPt.root";
	TString purity_39GeV_fname = "data/DataForNpeStudy/EffPurity/purity_AuAu39GeV_CalculatedVsPconvertedToPt.root";

	TString eff_200GeV_fname = "data/DataForNpeStudy/EffPurity/phoRecoEffVsPt_AuAu200GeV_0_60_withTotalErr.root";
	TString eff_62GeV_fname = "data/DataForNpeStudy/EffPurity/phoRecoEffVsPt_AuAu62GeV_0_60_withTotalErr.root";
	TString eff_39GeV_fname = "data/DataForNpeStudy/EffPurity/phoRecoEffVsPt_AuAu39GeV_0_60_withTotalErr.root";

	TFile* fpurity_200GeV = new TFile(purity_200GeV_fname);
	TFile* fpurity_62GeV = new TFile(purity_62GeV_fname);
	TFile* fpurity_39GeV = new TFile(purity_39GeV_fname);
	TFile* feff_200GeV = new TFile(eff_200GeV_fname);
	TFile* feff_62GeV = new TFile(eff_62GeV_fname);
	TFile* feff_39GeV = new TFile(eff_39GeV_fname);



	TGraph* grPurity200GeV = (TGraph*)fpurity_200GeV->Get("grPrityMeanVal");
	TGraph* grPurityMin200GeV = (TGraph*)fpurity_200GeV->Get("grPrityMinVal");
	TGraph* grPurityMax200GeV = (TGraph*)fpurity_200GeV->Get("grPrityMaxVal");

	TGraph* grPurity62GeV = (TGraph*)fpurity_62GeV->Get("grPrityMeanVal");
	TGraph* grPurityMin62GeV = (TGraph*)fpurity_62GeV->Get("grPrityMinVal");
	TGraph* grPurityMax62GeV = (TGraph*)fpurity_62GeV->Get("grPrityMaxVal");

	TGraph* grPurity39GeV = (TGraph*)fpurity_39GeV->Get("grPrityMeanVal");
	TGraph* grPurityMin39GeV = (TGraph*)fpurity_39GeV->Get("grPrityMinVal");
	TGraph* grPurityMax39GeV = (TGraph*)fpurity_39GeV->Get("grPrityMaxVal");

	//grPrityMeanVal or grPrityMaxVal or grPrityMinVal


	TGraphErrors* grEff62GeV= (TGraphErrors*)feff_62GeV->Get("phoRecoEffVsPt_0_60");
	TGraphErrors* grEff200GeV= (TGraphErrors*)feff_200GeV->Get("phoRecoEffVsPt_0_60");
	TGraphErrors* grEff39GeV= (TGraphErrors*)feff_39GeV->Get("phoRecoEffVsPt_0_60");


	grEff62GeV->SetLineColor(kRed);
	grEff62GeV->SetLineWidth(4);

	grEff62GeV->SetFillColor(kRed);
	grEff62GeV->SetFillStyle(3358);


	grEff200GeV->SetLineColor(kBlack);
	grEff200GeV->SetLineWidth(4);
	//grEff200GeV->SetLineStyle(9);
	grEff200GeV->SetFillColor(kBlack);
	grEff200GeV->SetFillStyle(3953);
	
	grEff39GeV->SetLineColor(kBlue);
	grEff39GeV->SetLineWidth(4);
	grEff39GeV->SetFillColor(kBlue);
	grEff39GeV->SetFillStyle(3935);

	grPurity39GeV->SetLineColor(kBlue);
	grPurity39GeV->SetLineWidth(3);
	grPurityMin39GeV->SetLineColor(kBlue);
	grPurityMin39GeV->SetLineWidth(2);
	grPurityMin39GeV->SetLineStyle(9);
	grPurityMax39GeV->SetLineColor(kBlue);
	grPurityMax39GeV->SetLineWidth(2);
	grPurityMax39GeV->SetLineStyle(9);


	grPurity62GeV->SetLineColor(kRed);
	grPurity62GeV->SetLineWidth(3);
	grPurityMin62GeV->SetLineColor(kRed);
	grPurityMin62GeV->SetLineWidth(2);
	grPurityMin62GeV->SetLineStyle(9);
	grPurityMax62GeV->SetLineColor(kRed);
	grPurityMax62GeV->SetLineWidth(2);
	grPurityMax62GeV->SetLineStyle(9);


	grPurity200GeV->SetLineColor(kBlack);
	grPurity200GeV->SetLineWidth(4);
	grPurityMin200GeV->SetLineColor(kBlack);
	grPurityMin200GeV->SetLineWidth(2);
	grPurityMin200GeV->SetLineStyle(9);
	grPurityMax200GeV->SetLineColor(kBlack);
	grPurityMax200GeV->SetLineWidth(2);
	grPurityMax200GeV->SetLineStyle(9);


	TGraphAsymmErrors* purityErr200GeV = new TGraphAsymmErrors();
	TGraphAsymmErrors* purityErr62GeV = new TGraphAsymmErrors();
	TGraphAsymmErrors* purityErr39GeV = new TGraphAsymmErrors();

	for(int i=0; i<grPurity200GeV->GetN(); i++){

		if(grPurity200GeV->GetX()[i]<10) {
			purityErr200GeV->SetPoint(i,grPurity200GeV->GetX()[i],grPurity200GeV->GetY()[i]);
			purityErr200GeV->SetPointError(i,0,0,grPurity200GeV->GetY()[i] - grPurityMin200GeV->GetY()[i],grPurityMax200GeV->GetY()[i]-grPurity200GeV->GetY()[i]);
		}
	}

	for(int i=0; i<grPurity62GeV->GetN(); i++){

		purityErr62GeV->SetPoint(i,grPurity62GeV->GetX()[i],grPurity62GeV->GetY()[i]);
		purityErr62GeV->SetPointError(i,0,0,grPurity62GeV->GetY()[i] - grPurityMin62GeV->GetY()[i],grPurityMax62GeV->GetY()[i]-grPurity62GeV->GetY()[i]);

	}

	for(int i=0; i<grPurity39GeV->GetN(); i++){

		purityErr39GeV->SetPoint(i,grPurity39GeV->GetX()[i],grPurity39GeV->GetY()[i]);
		purityErr39GeV->SetPointError(i,0,0,grPurity39GeV->GetY()[i] - grPurityMin39GeV->GetY()[i],grPurityMax39GeV->GetY()[i]-grPurity39GeV->GetY()[i]);

	}

	purityErr39GeV->SetLineColor(kBlue);
	purityErr39GeV->SetLineWidth(4);

	purityErr39GeV->SetFillColor(kBlue);
	purityErr39GeV->SetFillStyle(3435);

	purityErr62GeV->SetLineColor(kRed);
	purityErr62GeV->SetLineWidth(4);

	purityErr62GeV->SetFillColor(kRed);
	purityErr62GeV->SetFillStyle(3453);

	purityErr200GeV->SetLineColor(kBlack);
	purityErr200GeV->SetLineWidth(4);
	//grEff200GeV->SetLineStyle(9);
	purityErr200GeV->SetFillColor(kGray);
	purityErr200GeV->SetFillStyle(3001);

	//grPurity200GeV->SetLineStyle(9);
	


	TCanvas* cPurity = new  TCanvas("cPurity","cPurity",800,600);
	cPurity->SetLogx(1);

	TBox* ex1 = new TBox(0.4,0,0.6,1.2);
	//ex1->SetFillStyle(3935);
	//ex1->SetFillColor(kBlack);
	ex1->SetFillStyle(0);
	ex1->SetLineColor(kBlack);
	ex1->SetLineWidth(2);
	ex1->SetLineStyle(7);

	TBox* ex1a = new TBox(0.4,0.05,0.6,0.4);
	ex1a->SetFillStyle(3935);
	ex1a->SetFillColor(kBlack);
	ex1a->SetLineColor(kBlack);

	TBox* ex2 = new TBox(0.7,0,1.2,1.2);
	//ex2->SetFillStyle(3935);
	//ex2->SetFillColor(kBlack);
	ex2->SetFillStyle(0);
	ex2->SetLineColor(kBlack);
	ex2->SetLineWidth(2);
	ex2->SetLineStyle(7);
	
	TBox* ex2a = new TBox(0.7,0.05,1.2,0.4);
	ex2a->SetFillStyle(3935);
	ex2a->SetFillColor(kBlack);
	ex2a->SetLineColor(kBlack);
	ex2a->SetLineColor(kBlack);
	ex2a->SetLineWidth(2);
	ex2a->SetLineStyle(7);

	purityErr200GeV->SetLineStyle(9);
	purityErr62GeV->SetLineStyle(10);

	purityErr200GeV->Draw("a3");
	ex1->Draw();
	ex1a->Draw();
	ex2->Draw();
	ex2a->Draw();
	purityErr200GeV->Draw("3 same");
	purityErr200GeV->Draw("lX same");
	purityErr62GeV->Draw("3 same");
	purityErr62GeV->Draw("lX same");
	purityErr39GeV->Draw("3 same");
	purityErr39GeV->Draw("lX same");

/*	grPurity200GeV->Draw("al");

	grPurityMin200GeV->Draw("l same");
	grPurityMax200GeV->Draw("l same");

	grPurity62GeV->Draw("l same");
	grPurityMin62GeV->Draw("l same");
	grPurityMax62GeV->Draw("l same");
*/
	TLegend *leg = new TLegend(0.55,0.3,0.8,0.7);
	leg->SetFillStyle(0);
	leg->SetTextFont(132); //Times-Roman
	leg->SetMargin(0.4);
	leg->SetTextSize(0.06);
	leg->SetHeader("Au+Au collisions");
	leg->AddEntry(purityErr200GeV,"#sqrt{s_{NN}}=200 GeV","lf");
	leg->AddEntry(purityErr62GeV,"#sqrt{s_{NN}}=62.4 GeV","lf");
	leg->AddEntry(purityErr39GeV,"#sqrt{s_{NN}}=39 GeV","lf");
	leg->AddEntry(ex2a,"Excluded range","lf");

	leg->Draw("same");

	purityErr200GeV->GetYaxis()->SetTitle("Purity");
	purityErr200GeV->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	purityErr200GeV->GetXaxis()->SetLimits(Xmin,Xmax);
	purityErr200GeV->GetYaxis()->SetRangeUser(Ymin,Ymax);
	purityErr200GeV->GetXaxis()->SetMoreLogLabels();
	purityErr200GeV->GetXaxis()->SetNoExponent();
/*
	purityErr39GeV->GetYaxis()->SetTitle("Purity");
	purityErr39GeV->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	purityErr39GeV->GetXaxis()->SetLimits(Xmin,Xmax);
	purityErr39GeV->GetYaxis()->SetRangeUser(Ymin,Ymax);
	purityErr39GeV->GetXaxis()->SetMoreLogLabels();
	purityErr39GeV->GetXaxis()->SetNoExponent();
*/

	TLatex label;
	label.DrawTextNDC(0.88,0.85,"(a)");
	//label.DrawTextNDC(0.25,0.25,"0-80% centrality");
	label.DrawTextNDC(0.55,0.2,"0-60% centrality");


	TCanvas* cPhoEleEff = new  TCanvas("cPhoEleEff","cPhoEleEff",800,600);

	grEff200GeV->SetLineStyle(9);
	grEff62GeV->SetLineStyle(10);

	grEff39GeV->SetFillColor(kBlue);
	grEff39GeV->SetFillStyle(3556);

		grEff62GeV->SetFillColor(kRed);
		grEff62GeV->SetFillStyle(3565);

		//grEff200GeV->SetLineStyle(9);
		grEff200GeV->SetFillColor(kGray);
		grEff200GeV->SetFillStyle(3001);



	grEff200GeV->Draw("a3");
	grEff200GeV->Draw("lX same");
	grEff62GeV->Draw("3 same");
	grEff62GeV->Draw("lX same");
	grEff39GeV->Draw("3 same");
	grEff39GeV->Draw("lX same");
	
	grEff200GeV->GetYaxis()->SetTitle("#varepsilon_{Photonic tagging}");
	grEff200GeV->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	grEff200GeV->GetYaxis()->SetRangeUser(YminEff,YmaxEff);	
	grEff200GeV->GetXaxis()->SetRangeUser(0.2,8.);

	TLegend *leg2 = new TLegend(0.55,0.18,0.8,0.5);
	leg2->SetFillStyle(0);
	leg2->SetTextFont(132); //Times-Roman
	leg2->SetMargin(0.4);
	leg2->SetTextSize(0.06);
	leg2->SetHeader("Au+Au collisions");
	leg2->AddEntry(grEff200GeV,"#sqrt{s_{NN}}=200 GeV","lf");
	leg2->AddEntry(grEff62GeV,"#sqrt{s_{NN}}=62.4 GeV","lf");
	leg2->AddEntry(grEff39GeV,"#sqrt{s_{NN}}=39 GeV","lf");
	leg2->Draw("same");
	
	label.DrawTextNDC(0.88,0.85,"(b)");
	label.DrawTextNDC(0.25,0.85,"0-60% centrality");


	// print out data
	cout << "Purity, 200 GeV:" << endl;
	purityErr200GeV->Print();

	cout << "Purity, 62.4 GeV:" << endl;
	purityErr62GeV->Print();

	cout << "Purity, 39 GeV:" << endl;
	purityErr39GeV->Print();

	cout << "Pho. reco eff. 200 GeV:" << endl;
	grEff200GeV->Print();

	cout << "Pho. reco eff. 62.4 GeV:" << endl;
	grEff62GeV->Print();

	cout << "Pho. reco eff. 39 GeV:" << endl;
	grEff39GeV->Print();
}

void plotPurityPheripheralCheck(){

	gROOT->ForceStyle();
	setWindowDressing();

	int errXwidth  = 6; //the size of the lines at the end of the error bars 
	gStyle->SetEndErrorSize(errXwidth);
	
	float Xmin = 1.25, Xmax = 8.0;
	float Ymin = 0.0, Ymax = 1.05;
	float YminEff = 0., YmaxEff = 0.8;

	TString purity_200GeV_fname = "/home/dkikola/Dropbox/Data/NpeFlow/Purity/200GeV_nseRecalibrated/purity_pheripheral_check.root";
	TFile* fpurity_200GeV = new TFile(purity_200GeV_fname);
	


	TGraph* grPurity200GeV_cent3 = (TGraph*)fpurity_200GeV->Get("purity/purity_vs_pt_cent3_cut0");
	TGraph* grPurity200GeV_cent4 = (TGraph*)fpurity_200GeV->Get("purity/purity_vs_pt_cent4_cut0");
	

	grPurity200GeV_cent3->SetLineColor(kRed);
	grPurity200GeV_cent3->SetLineWidth(3);
	


	grPurity200GeV_cent4->SetLineColor(kBlack);
	grPurity200GeV_cent4->SetLineWidth(3);
	grPurity200GeV_cent4->SetLineStyle(9);
	
	TCanvas* cPurity = new  TCanvas("cPurity","cPurity",800,600);
	//cPurity->SetLogx(1);

	

	grPurity200GeV_cent3->Draw("al");
	grPurity200GeV_cent4->Draw("l same");

	TLegend *leg = new TLegend(0.55,0.2,0.8,0.45);
	leg->SetHeader("Au+Au 200 GeV");	
	leg->SetFillStyle(0);
	leg->SetTextFont(132); //Times-Roman
	leg->SetMargin(0.4);
	leg->SetTextSize(0.06);
	leg->AddEntry(grPurity200GeV_cent3,"40-60%","lf");
	leg->AddEntry(grPurity200GeV_cent4,"60-80%","lf");


	leg->Draw("same");

	grPurity200GeV_cent3->GetYaxis()->SetTitle("Purity");
	grPurity200GeV_cent3->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	grPurity200GeV_cent3->GetXaxis()->SetLimits(Xmin,Xmax);
	grPurity200GeV_cent3->GetYaxis()->SetRangeUser(Ymin,Ymax);
	grPurity200GeV_cent3->GetXaxis()->SetMoreLogLabels();
	grPurity200GeV_cent3->GetXaxis()->SetNoExponent();
}



