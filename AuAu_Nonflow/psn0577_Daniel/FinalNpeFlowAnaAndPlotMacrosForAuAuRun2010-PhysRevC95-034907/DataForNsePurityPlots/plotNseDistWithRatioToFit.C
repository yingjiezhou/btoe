/*
 * plotMinvDist.C
 *
 *  Created on: Apr 14, 2012
 *      Author: dkikola
 */
#include "style.C"



void plotNseDistWithRatioToFit(bool lowPt = true, bool GaussianFit = true, TString inFileName = "AuAu62GeVPuirtyFitsGausForPlots/PurityHistGaussianFitsForPlots_AuAu62GeV.root")
{

	//low-pT: float lowP = 0.9-1.0 GeV, bin = 7
	//low-pT: P = 1.2-1.3 GeV, bin = 10
	//high-pT: float P = 2-4 GeV/c, bin = 14

	setWindowDressing();
	//gROOT->ForceStyle();
	gStyle->SetOptStat(0);

	int bin = 0;

	if(lowPt)bin = 10;// 7;
	else bin = 14;
	
	TFile* fIn = new TFile(inFileName);

	TString name;
	name.Form("proj_plot_bin%i",bin);

	cout << name << endl;

	TCanvas* cFits  = (TCanvas*)fIn->Get(name);


	if(!cFits) cout << "empty canvas" << endl;
	//cFits->SetLogy(1);
	//cFits->Draw();
	//cFits->Update();

	//return;



	TObject *obj;
	TIter next(cFits->GetListOfPrimitives());

	while ((obj = next())) {
		cout << "Reading: " << obj->GetName() << " " << obj->GetTitle() << endl;

		/* this is a list of object on this canvas:

		Reading: TFrame
		Reading: proj_bin5
		Reading: he
		Reading: hpi
		Reading: hp
		Reading: hk
		Reading: hMerged
		Reading: TPave
		Reading: title
		*/


	}

	TCanvas* cFitPanel = new TCanvas("cFitPanel","cFitPanel",800,800);
	TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0,0);
	TPad *pad2 = new TPad("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.2,0);
	pad1->SetFillColor(kWhite);
	pad2->SetFillColor(kWhite);

	pad1->Draw();
	pad2->Draw();

	cFitPanel->SetLeftMargin(0.15);
	pad1->SetBottomMargin(0.1);
	pad2->SetBottomMargin(0.3);
	pad1->SetLeftMargin(0.1);
	pad2->SetLeftMargin(0.1);
	/*flowPlotsStyle->SetPadTopMargin(0.05);
	flowPlotsStyle->SetPadRightMargin(0.03);
	flowPlotsStyle->SetPadBottomMargin(0.16);
	flowPlotsStyle->SetPadLeftMargin(0.12);
*/
	name.Form("proj_bin%d",bin);

	TF1* fun_pi_mb_pt5 = (TF1*)cFits->GetPrimitive("hpi");
	TF1* fun_e_mb_pt5 = (TF1*)cFits->GetPrimitive("he");
	TF1* fun_merg_pi_mb_pt5 = (TF1*)cFits->GetPrimitive("hMerged");
	TH1D *hist = (TH1D*)cFits->GetPrimitive(name);

	TF1* fun_k_mb_pt5 = 0;
	TF1* fun_p_mb_pt5 = 0;

	//if Gaussian+hist fits
	if(GaussianFit){
		fun_k_mb_pt5 = (TF1*)cFits->GetPrimitive("hk");
		fun_p_mb_pt5 = (TF1*)cFits->GetPrimitive("hp");

	} /* else {
		fun_k_mb_pt5 = (TH1D*)cFits->GetPrimitive("hNseKaonPlot");
		fun_p_mb_pt5 = (TH1D*)cFits->GetPrimitive("hNseProtonPlot");
	} */


	name.Form("proj_bin%d_ratioToFit",bin);
	TH1D *histRatio = (TH1D*)fIn->Get(name);


	fun_k_mb_pt5->SetLineStyle(10);
	fun_k_mb_pt5->SetLineWidth(3);

	fun_pi_mb_pt5->SetLineStyle(9);
	fun_pi_mb_pt5->SetLineWidth(3);

	fun_p_mb_pt5->SetLineStyle(8);
	fun_p_mb_pt5->SetLineWidth(3);

	fun_e_mb_pt5->SetLineStyle(7);
	fun_e_mb_pt5->SetLineWidth(3);

	fun_merg_pi_mb_pt5->SetLineStyle(3);
	fun_merg_pi_mb_pt5->SetLineWidth(3);


	//hist->SetYTitle("counts (arb. units)");
	hist->SetYTitle("dN/d(n#sigma_{e}) (counts)");
	hist->SetXTitle("n#sigma_{e}");

	if(lowPt)hist->SetMaximum(5e5);
	else hist->SetMaximum(1e4);
	hist->SetAxisRange(-10,8);

	pad1->cd();
	pad1->SetLogy(1);

	hist->Draw();
    hist->GetYaxis()->SetTitleSize(0.05);
    hist->GetXaxis()->SetTitleSize(0.05);
    hist->GetYaxis()->SetTitleOffset(0.9);


	fun_k_mb_pt5->Draw("same");
	fun_pi_mb_pt5->Draw("same");
	fun_p_mb_pt5->Draw("same");
	fun_merg_pi_mb_pt5->Draw("same");
	fun_e_mb_pt5->Draw("same");


	TLegend *leg;
	if(lowPt)leg = new TLegend(0.58,0.48,0.88,0.85);
	else leg = new TLegend(0.52,0.6,0.86,0.85);
	leg->SetFillStyle(0);
	leg->SetTextFont(132); //Times-Roman
	leg->SetMargin(0.4);
	leg->SetTextAlign(11);
	leg->SetTextSize(0.05);
	if(lowPt)leg->SetHeader("1.2 < p < 1.3 GeV/c");
	else leg->SetHeader("2 < p < 4 GeV/c");

	leg->AddEntry(fun_pi_mb_pt5,"Pions","l");
	if(lowPt)leg->AddEntry(fun_k_mb_pt5,"Kaons","l");
	else leg->AddEntry(fun_p_mb_pt5,"Kaons + Protons","l");
	leg->AddEntry(fun_e_mb_pt5,"Electrons","l");
	if(lowPt)leg->AddEntry(fun_p_mb_pt5,"Protons","l");
	if(lowPt)leg->AddEntry(fun_merg_pi_mb_pt5,"Merged Pions","l");

	leg->Draw("same");

	TLatex label;
	if(lowPt){
		label.DrawTextNDC(0.88,0.85,"(a)");
		label.DrawLatexNDC(0.15,0.85,"Au+Au #sqrt{s_{NN}}=62.4 GeV");
	} else {
		label.DrawTextNDC(0.88,0.85,"(b)");
		label.DrawTextNDC(0.13,0.85,"0-60% centrality");


	}

	pad2->cd();
	histRatio->SetLineWidth(2);
	histRatio->SetMarkerStyle(kFullCircle);
	histRatio->SetMarkerSize(0.8);

    histRatio->SetMaximum(1.69);
    histRatio->SetMinimum(0.29);
    histRatio->SetAxisRange(-10,8);
    histRatio->SetYTitle("Data/Fit");
    histRatio->GetYaxis()->SetTitleOffset(0.25);
    histRatio->GetXaxis()->SetTitleOffset(0.77);

	histRatio->Draw();

    histRatio->GetXaxis()->SetLabelSize(0.16);
    histRatio->GetXaxis()->SetTitleSize(0.19);

    histRatio->GetYaxis()->SetLabelSize(0.12);
    histRatio->GetYaxis()->SetTitleSize(0.16);
    histRatio->GetYaxis()->SetNdivisions(505);

    TLine* l = new TLine(-10,1,8,1);
    l->SetLineWidth(2);
    l->Draw("same");

    cFitPanel->Print("fig1.pdf");


}
