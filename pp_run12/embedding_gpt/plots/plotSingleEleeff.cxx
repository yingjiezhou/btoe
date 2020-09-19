#include "../../ptbin.h"
#include "../../style.h"
void plotSingleEleeff()
{
	setstyle();
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetNDC();
	tx.SetTextFont(42);
	TCanvas *cc=Canvas("cc",0.14,0.04,0.15,0.06,0,0,0);
	cc->SetGrid(1,1);
	TH1F *htmp;
	TLegend *lg;
	TFile *f=new TFile("DataMaker/Single_electron_eff.root");
	TH1F *hTPCtracks = (TH1F *)f->Get("hmcptw");
	TH1F *hTPCtracksHT0=(TH1F *)f->Get("TPCtracksHT0");
	TH1F *hTPCtracksHT2=(TH1F *)f->Get("TPCtracksHT2");
	TH1F *hSingleEleeffHT0plot = (TH1F*) calEffHistB(hTPCtracksHT0,hTPCtracks);
	hSingleEleeffHT0plot->SetName("hSingleEleeffHT0plot");
	TH1F *hSingleEleeffHT2plot = (TH1F*) calEffHistB(hTPCtracksHT2,hTPCtracks);
	hSingleEleeffHT2plot->SetName("hSingleEleeffHT2plot");
	//hTPCtracks->Print("ALL");
	//hTPCtracksHT2->Print("ALL");
	//hSingleEleeffHT0plot->Print("ALL");
	
	cc=Canvas("cc",0.12,0.06,0.15,0.06,0,1,0);
    cc->SetGrid(1,1);
	float ymin,ymax;
	cc->SetLogy(1);
	hTPCtracks->SetAxisRange(2.0,9.9);
	hTPCtracksHT0->SetAxisRange(2.0,9.9);
	hTPCtracksHT2->SetAxisRange(2.0,9.9);
	hTPCtracksbg=(TH1F *)hTPCtracks->Clone();
    hTPCtracksHT0bg=(TH1F *)hTPCtracksHT0->Clone();
	hTPCtracksHT2bg=(TH1F *)hTPCtracksHT2->Clone();
	ymin = hTPCtracks->GetMinimum()*3e-3;
	ymax = hTPCtracks->GetMaximum()*10;
	htmp=histo("htmp",20,1.7,10.3,ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	htmp->SetNdivisions(505,"y");
	Style(hTPCtracksbg,1,kBlack,3,22,kBlack,2.15,"psame");
	Style(hTPCtracks,1,kBlack,3,22,kRed,1.65,"hfpsame");
	Style(hTPCtracksHT0bg,1,kBlack,3,8,kBlack,2.05,"psame");
	Style(hTPCtracksHT0,1,kBlack,3,8,kGreen+1,1.65,"hfpsame");
	Style(hTPCtracksHT2bg,1,kBlack,3,23,kBlack,2.15,"psame");
	Style(hTPCtracksHT2,1,kBlack,3,23,6,1.65,"hfpsame");
	lg = Legend(0.15,0.19,0.5,0.34,0.04);
	lg->AddEntry(hTPCtracksbg,"N_{mc}","pl");
	lg->AddEntry(hTPCtracksHT0bg,"N_{rc} (Track Quality + EMC + ADC0>180 + DSMADC>11)","pl");
	lg->AddEntry(hTPCtracksHT2bg,"N_{rc} (Track Quality + EMC + ADC0>300 + DSMADC>18)","pl");
	lg = Legend(0.15,0.19,0.5,0.34,0.04);
	lg->AddEntry(hTPCtracks,"N_{mc}","pl");
	lg->AddEntry(hTPCtracksHT0,"N_{rc} (Track Quality + EMC + ADC0>180 + DSMADC>11)","pl");
	lg->AddEntry(hTPCtracksHT2,"N_{rc} (Track Quality + EMC + ADC0>300 + DSMADC>18)","pl");
	tx.DrawLatex(0.5,0.85,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/SingleEleeffND.png");
	cc->SaveAs("pic/SingleEleeffND.eps");

	cc->SetLogy(0);
	hSingleEleeffHT0plot->SetAxisRange(1.0,10);
	hSingleEleeffHT2plot->SetAxisRange(1.0,10);
	hSingleEleeffHT0plotbg=(TH1F *)hSingleEleeffHT0plot->Clone();
	hSingleEleeffHT2plotbg=(TH1F *)hSingleEleeffHT2plot->Clone();
	ymin = 0;
	ymax = 1.0;
	htmp=histo("htmp1",20,0.8,10.2,ymin,ymax,"p_{T} (GeV/c)"," Single Electron efficiency",0.075,0.85,0.07,0.75);
	htmp->SetNdivisions(505,"y");
	Style(hSingleEleeffHT0plotbg,1,kBlack,3,22,kBlack,2.5,"psame");
	Style(hSingleEleeffHT0plot,1,kBlack,3,22,kRed,2.0,"psame");
	Style(hSingleEleeffHT2plotbg,1,kBlack,3,23,kBlack,2.5,"psame");
	Style(hSingleEleeffHT2plot,1,kBlack,3,23,kGreen+1,2.0,"psame");
	lg = Legend(0.62,0.31,1.00,0.45,0.06);
	lg->AddEntry(hSingleEleeffHT0plotbg,"HT0","pl");
	lg->AddEntry(hSingleEleeffHT2plotbg,"HT2","pl");
	lg = Legend(0.62,0.31,1.00,0.45,0.06);
	lg->AddEntry(hSingleEleeffHT0plot,"HT0","pl");
	lg->AddEntry(hSingleEleeffHT2plot,"HT2","pl");
	tx.DrawLatex(0.48,0.86,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/SingleEleeff.png");
	cc->SaveAs("pic/SingleEleeff.eps");
	
	TH1F *hSingleEleeffHT0=new TH1F("hSingleEleeffHT0","",nPtBins,ptbin);
	TH1F *hSingleEleeffHT2=new TH1F("hSingleEleeffHT2","",nPtBins,ptbin);
	hSingleEleeffHT0plot->Print("ALL");
	hSingleEleeffHT2plot->Print("ALL");
	for(int i=0;i<nPtBins;i++){
	hSingleEleeffHT0->SetBinContent(i+1,hSingleEleeffHT0plot->GetBinContent(i+28));
	hSingleEleeffHT0->SetBinError(i+1,hSingleEleeffHT0plot->GetBinError(i+28));
	hSingleEleeffHT2->SetBinContent(i+1,hSingleEleeffHT2plot->GetBinContent(i+28));
	hSingleEleeffHT2->SetBinError(i+1,hSingleEleeffHT2plot->GetBinError(i+28));
	}
	//hSingleEleeffHT2plot->Print("ALL");
	hSingleEleeffHT0->Print("ALL");
	hSingleEleeffHT2->Print("ALL");
	TFile* file = new TFile("effroot/SingleEleeff.root","RECREATE");
	//TFile* file = new TFile("effroot/Triggereff.root","RECREATE");
	file->cd();
	hSingleEleeffHT0->Write();
	hSingleEleeffHT2->Write();
	file->Close();
}
