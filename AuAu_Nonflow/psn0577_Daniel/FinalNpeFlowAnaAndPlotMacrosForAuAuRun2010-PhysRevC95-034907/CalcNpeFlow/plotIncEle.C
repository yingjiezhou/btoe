/*
 * plotRes200GeV.C
 *
 *  Created on: Jul 15, 2012
 *      Author: dkikola
 */

#include "style.C"

void removeHighPtPoints(TGraph* gr, float maxPt){
	
	for(int i = 0; i<gr->GetN();i++){
		if(gr->GetX()[i]>maxPt){
			gr->RemovePoint(i);
			i--;
		}
	}
}

void removeLowPtPoints(TGraph* gr, float minPt){
	
	for(int i = 0; i<gr->GetN();i++){
		if(gr->GetX()[i]<minPt){
			gr->RemovePoint(i);
			i--;
		}
	}
}


void plotIncEle(){

	gROOT->ForceStyle();
	setWindowDressing();

	//flowPlotsStyle->SetLineWidth(1);


	int errXwidth  = 6; //the size of the lines at the end of the error bars 
	gStyle->SetEndErrorSize(errXwidth);
	
	float Xmin = -0.04, Xmax = 2.9;
	float Ymin = 0.0, Ymax = 0.19;

    int lineWidth  =4;
    int lineStyle = 7;

    TString v2_2part_39GeV_fname = "data/NpeFlow/v2_2part_MB_AuAu39GeV-withInterpolatedPhetonicElectron.root";
   	TString v2_2part_62GeV_fname = "data/NpeFlow/v2_2part_MB_AuAu62GeV-withInterpolatedPhetonicElectron.root";

   	TString v2_2part_mb_fname = "data/NpeFlow/v2_2part_MB_AuAu200GeV-withInterpolatedPhetonicElectron.root"; 
   	TString v2_2part_ht_fname = "data/NpeFlow/v2_2part_HT_AuAu200GeV.root";
   	TString v2_4part_mb_fname = "data/NpeFlow/v2_4part_MB_AuAu200GeV-2016-05-05.root";

   	TFile* f2part_mb = new TFile(v2_2part_mb_fname);
   	TFile* f4part_mb = new TFile(v2_4part_mb_fname);
   	TFile* f2part_ht = new TFile(v2_2part_ht_fname);

	TFile* f2part_39GeVmb = new TFile(v2_2part_39GeV_fname);
	TFile* f2part_62GeVmb = new TFile(v2_2part_62GeV_fname);

	TGraphErrors* v2Pho39GeV = (TGraphErrors*)f2part_39GeVmb->Get("v2PhoVsPt");
	TGraphErrors* v2Pho62GeV = (TGraphErrors*)f2part_62GeVmb->Get("v2PhoVsPt");
   	TGraphErrors* v2Pho200GeV = (TGraphErrors*)f2part_mb->Get("v2PhoVsPt");

	TGraphErrors* v2_2part_62GeVmb = (TGraphErrors*)f2part_62GeVmb->Get("v2IncEleCent_2part0");
	TGraphErrors* v2_2part_39GeVmb = (TGraphErrors*)f2part_39GeVmb->Get("v2IncEleCent_2part0");
	TGraphErrors* v2_2part_mb = (TGraphErrors*)f2part_mb->Get("v2IncEleCent_2part0");
    TGraphErrors* v2_4part_mb = (TGraphErrors*)f4part_mb->Get("v2IncEleCent_4part0");
    TGraphErrors* v2_2part_ht = (TGraphErrors*)f2part_ht->Get("v2IncEleCent_2part0");


	// Print out data points
	cout << "v2{2} part, Au+Au 39 GeV min-bias" << endl;
	v2_2part_39GeVmb->Print();
	cout << "v2{2} part, Au+Au 62 GeV min-bias" << endl;
	v2_2part_62GeVmb->Print();
	cout << "v2{2} part, Au+Au 200 GeV min-bias" << endl;
	v2_2part_mb->Print();	
	cout << "v2{2} part, Au+Au 200 GeV High Tower" << endl;
	v2_2part_ht->Print();
	cout << "v2{4} part, Au+Au 200 GeV min-bias" << endl;
	v2_4part_mb->Print();
	
	cout << "photonic electrons v2, Au+Au 39 GeV min-bias" << endl;
	v2Pho39GeV->Print();
	cout << "photonic electrons v2, Au+Au 62.4 GeV min-bias" << endl;
	v2Pho62GeV->Print();
	cout << "photonic electrons v2, Au+Au 200 GeV min-bias" << endl;
	v2Pho200GeV->Print();
	


	v2_2part_39GeVmb->SetLineColor(kBlack);
	v2_2part_39GeVmb->SetMarkerColor(kBlack);
	v2_2part_39GeVmb->SetMarkerStyle(kFullCircle);
	
	v2_2part_62GeVmb->SetLineColor(kBlack);
	v2_2part_62GeVmb->SetMarkerColor(kBlack);
	v2_2part_62GeVmb->SetMarkerStyle(kFullCircle);

    v2Pho39GeV->SetFillColor(33);
    v2Pho39GeV->SetMarkerColor(33);
    v2Pho39GeV->SetMarkerStyle(kOpenSquare);
    v2Pho62GeV->SetFillColor(33);
    v2Pho62GeV->SetMarkerColor(33);
    v2Pho62GeV->SetMarkerStyle(kOpenSquare);

	TGraphErrors* grV2PheStatErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_stat.err.txt");
	TGraphErrors* grV2PheSystErr = new TGraphErrors("data/DataforCrosscheck/npe_v2_phenix_0_60_AuAu200GeV_sys.err.txt");


	v2_4part_mb->SetLineColor(kBlue);
	v2_4part_mb->SetMarkerColor(kBlue);
	v2_4part_mb->SetMarkerStyle(kFullSquare);

    v2_2part_ht->SetLineColor(kRed);
	v2_2part_ht->SetMarkerColor(kRed);
	v2_2part_ht->SetMarkerStyle(kFullStar);
	v2_2part_ht->SetMarkerSize(MarkerSize + 0.5);

    v2_2part_mb->SetLineColor(kBlack);
    v2_2part_mb->SetMarkerColor(kBlack);
    v2_2part_mb->SetMarkerStyle(kFullCircle);

	grV2PheStatErr->SetMarkerStyle(kOpenCircle);
	grV2PheStatErr->SetMarkerColor(kBlue);
	grV2PheStatErr->SetLineColor(kBlue);
	grV2PheSystErr->SetLineColor(kBlue);

		// shift points a bit
		for(int i = 0; i<v2_4part_mb->GetN();i++){
			v2_4part_mb->GetX()[i]+=0.06;
		}

		for(int i = 0; i<v2_2part_ht->GetN();i++){
			v2_2part_ht->GetX()[i]-=0.06;
		}

		
		
		for(int i = 0; i<v2_2part_mb->GetN();i++){
			if(v2_2part_mb->GetX()[i]>3){
				v2_2part_mb->RemovePoint(i);
				i--;
			}
		}
		
	// remove v2{2} MB points at high pT< GeV - too low statistics.
	removeHighPtPoints(v2_2part_mb,3);
	removeHighPtPoints(v2_2part_62GeVmb,2);
	removeHighPtPoints(v2_2part_39GeVmb,2);
	removeHighPtPoints(v2_4part_mb,3);


	// remove v2{2} HT points with pT<2 GeV - trigger efficiency is very small
	removeLowPtPoints(v2_2part_ht,2);

	TCanvas* cPhoNpeVsPt = new  TCanvas("cPhoNpeVsPt","cPhoNpeVsPt",800,600);
	v2_2part_62GeVmb->Draw("ap");
	v2Pho62GeV->Draw("3");
	v2_2part_62GeVmb->Draw("p same");

	v2_2part_62GeVmb->GetYaxis()->SetTitle("Electron v_{2}");
	v2_2part_62GeVmb->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	v2_2part_62GeVmb->GetXaxis()->SetLimits(Xmin,Xmax);
	v2_2part_62GeVmb->GetYaxis()->SetRangeUser(Ymin,Ymax);

	TLine* lZero = new TLine(Xmin,0,Xmax,0);
	lZero->Draw();

	TLegend *leg = new TLegend(0.15,0.8,0.3,0.97);
	leg->SetFillStyle(0);
	leg->SetTextFont(132); //Times-Roman
	leg->SetMargin(0.2);
	leg->SetTextSize(0.06);
	leg->AddEntry(v2_2part_62GeVmb,"Inclusive v_{2}{2}","p");
	leg->AddEntry(v2Pho62GeV,"Photonic v_{2}","f");
	leg->Draw("same");

	TLatex label;
	label.DrawTextNDC(0.88,0.85,"(b)");
	label.DrawTextNDC(0.65,0.85,"Au+Au 62.4 GeV");

	v2_2part_39GeVmb->GetYaxis()->SetTitle("v_{2}");
	v2_2part_39GeVmb->GetYaxis()->CenterTitle(1);
	v2_2part_39GeVmb->GetYaxis()->SetTitleOffset(1.2);

	v2_2part_39GeVmb->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	v2_2part_39GeVmb->GetXaxis()->SetLimits(Xmin,Xmax);
	v2_2part_39GeVmb->GetYaxis()->SetRangeUser(Ymin,Ymax);

	lZero->Draw();



	label.DrawTextNDC(0.88,0.85,"(c)");
	label.DrawTextNDC(0.65,0.85,"Au+Au 39 GeV");


	TCanvas* cAll = new TCanvas("cAll","cAll",1200,400);


	cAll->SetFillColor(0);
	cAll->SetFrameFillStyle(0);
	cAll->Divide(3,1,0.,0.0);
	cAll->GetPad(1)->SetLeftMargin(0.17);

	cAll->cd(1);
	v2_2part_39GeVmb->SetMarkerSize(1.25);
    v2_2part_39GeVmb->Draw("ap");
    //v2Pho39GeV->Draw("p same");
    v2Pho39GeV->Draw("3");

    v2_2part_39GeVmb->Draw("p same");

    v2_2part_39GeVmb->GetYaxis()->SetTitle("Electron v_{2}");


    TLegend *leg2 = new TLegend(0.2,0.83,0.7,0.98);
    leg2->SetFillStyle(0);
    leg2->SetTextFont(132); //Times-Roman
    leg2->SetMargin(0.2);
    leg2->SetTextSize(0.06);
    leg2->AddEntry(v2_2part_39GeVmb,"Inclusive v_{2}{2}, Min-Bias","p");
    leg2->AddEntry(v2Pho39GeV,"Photonic v_{2}","f");
    leg2->Draw("same");

    //label.DrawTextNDC(0.88,0.85,"(a)");
    label.DrawLatexNDC(0.35,0.25,"Au+Au #sqrt{s_{NN}}=39 GeV");

	cAll->cd(2);
	v2_2part_62GeVmb->SetMarkerSize(1.25);
	v2_2part_62GeVmb->Draw("ap");
	v2Pho62GeV->Draw("3"); //Draw("p same"); 
	v2_2part_62GeVmb->Draw("p same");

    //label.DrawTextNDC(0.88,0.85,"(b)");
    //label.DrawTextNDC(0.67,0.9,"Au+Au 62.4 GeV");
    label.DrawLatexNDC(0.3,0.25,"Au+Au #sqrt{s_{NN}}=62.4 GeV");
    label.DrawTextNDC(0.15,0.9,"0-60% centrality");

	cAll->cd(3);
	v2_2part_mb->SetMarkerSize(1.25);
	v2_4part_mb->SetMarkerSize(1.25);
	v2_2part_ht->SetMarkerSize(2);
	v2Pho200GeV->SetFillColor(33);
	v2Pho200GeV->SetMarkerColor(33);
	v2Pho200GeV->SetMarkerStyle(kOpenSquare);
	v2Pho200GeV->Draw("a3"); //Draw("ap");
	v2_2part_mb->Draw("p same");
	v2_4part_mb->Draw("p same");
	v2_2part_ht->Draw("p same");

	v2Pho200GeV->GetYaxis()->SetTitle("Electron v_{2}");
	v2Pho200GeV->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	v2Pho200GeV->GetXaxis()->SetLimits(-0.09,7.9);
	v2Pho200GeV->GetYaxis()->SetRangeUser(Ymin,Ymax);
	v2Pho200GeV->GetXaxis()->SetLimits(-0.1,7.7);
	v2Pho200GeV->GetYaxis()->CenterTitle(1);


	TLegend *leg3 = new TLegend(0.01,0.83,0.7,0.98);
	leg3->SetFillColor(0);
	leg3->SetTextFont(132); //Times-Roman
	leg3->SetMargin(0.2);
	leg3->SetTextSize(0.06);
	leg3->AddEntry(v2_4part_mb,"Inclusive v_{2}{4}, Min-Bias","p");
	leg3->AddEntry(v2_2part_ht,"Inclusive v_{2}{2}, High-Tower","p");
	leg3->Draw("same");

    //label.DrawTextNDC(0.88,0.85,"(c)");
    //label.DrawTextNDC(0.67,0.9,"200 GeV");
    label.DrawLatexNDC(0.3,0.25,"Au+Au #sqrt{s_{NN}}=200 GeV");


    cAll->Print("cInclPhotonic_all.pdf");

}



