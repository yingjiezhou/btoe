#include "../../ptbin.h"
#include "../../style.h"
void plotSingleEleeffAll()
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
	TH1F *Mcpt = (TH1F *)f->Get("hmcptw");
	TH1F *Rcpt = (TH1F *)f->Get("hrcptw");
	TH1F *hTPCtracks=(TH1F *)f->Get("hrcptw");
	TH1F *hEMCtracks=(TH1F *)f->Get("EMCtracks");
	TH1F *hSMDtracks=(TH1F *)f->Get("SMDtracks");
	TH1F *hTPCtracksCut=(TH1F *)f->Get("EMCtracks");//EMCtracks");
	TH1F *hTPCtracksHT0=(TH1F *)f->Get("TPCtracksHT0");
	TH1F *hTPCtracksHT2=(TH1F *)f->Get("TPCtracksHT2");

	/*TH1F *hTPCtrackingeffplot = (TH1F*)Rcpt->Clone("hTPCtrackingeffplot");
	hTPCtrackingeffplot->Sumw2();
	hTPCtrackingeffplot->Divide(Mcpt);*/
	TH1F *hTPCtrackingeffplot = (TH1F*) calEffHistB(Rcpt,Mcpt);
	hTPCtrackingeffplot->SetName("hTPCtrackingeffplot");
	TH1F *hBEMCeffplot = (TH1F*) calEffHistB(hEMCtracks,hTPCtracks);
	hBEMCeffplot->SetName("hBEMCeffplot");
	TH1F *hBSMDeffplot = (TH1F*) calEffHistB(hSMDtracks,hEMCtracks);
	hBSMDeffplot->SetName("hBSMDeffplot");
	//TH1F *hSingleEleeffplot = (TH1F*) hSMDtracks->Clone("hSingleEleeffplot");
	//hSingleEleeffplot->Sumw2();
	//hSingleEleeffplot->Divide(hTPCtracks);
	TH1F *hTriggereffHT0plot = (TH1F*) calEffHistB(hTPCtracksHT0,hTPCtracksCut);
	hTriggereffHT0plot->SetName("hTriggereffHT0plot");
	TH1F *hTriggereffHT2plot = (TH1F*) calEffHistB(hTPCtracksHT2,hTPCtracksCut);
	hTriggereffHT2plot->SetName("hTriggereffHT2plot");
	//hTPCtracksCut->Print("ALL");
	//hTPCtracksHT2->Print("ALL");
	hTriggereffHT2plot->Print("ALL");
	hTriggereffHT0plot->Print("ALL");
	
	cc=Canvas("cc",0.12,0.06,0.15,0.06,0,1,0);
    cc->SetGrid(1,1);
	float ymin,ymax;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//TPC tracking eff.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	Mcptbg=(TH1F *)Mcpt->Clone();
    Rcptbg=(TH1F *)Rcpt->Clone();
	ymin = 1e-6;
	ymax = Mcpt->GetMaximum()*10;
	htmp=histo("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	Style(Mcptbg,1,kBlack,3,22,kBlack,2.15,"psame");
	Style(Mcpt,1,kBlack,3,22,kRed,1.65,"hfpsame");
	Style(Rcptbg,1,kBlack,3,23,kBlack,2.15,"psame");
	Style(Rcpt,1,kBlack,3,23,6,1.65,"hfpsame");
	lg = Legend(0.15,0.2,0.45,0.35,0.045);
	lg->AddEntry(Mcptbg,"N_{mc}","pl");
	lg->AddEntry(Rcptbg,"N_{rc} (Track Quality)","pl");
	lg = Legend(0.15,0.2,0.45,0.35,0.045);
	lg->AddEntry(Mcpt,"N_{mc}","pl");
	lg->AddEntry(Rcpt,"N_{rc} (Track Quality)","pl");
	tx.DrawLatex(0.48,0.85,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/TPCtrackingeffND.png");
	cc->SaveAs("pic/TPCtrackingeffND.eps");

	cc->Clear();
	cc->SetLogy(0);
	hTPCtrackingeffplotbg=(TH1F *)hTPCtrackingeffplot->Clone();
	ymin = 0;
	ymax = 1.4;
	htmp=histo("htmp1",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)","TPC tracking effciency",0.075,0.85,0.07,0.75);
	Style(hTPCtrackingeffplotbg,1,kBlack,3,8,kBlack,1.9,"psame");
	Style(hTPCtrackingeffplot,1,kBlack,3,8,kGreen+1,1.7,"psame");
	tx.DrawLatex(0.48,0.85,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/TPCtrackingeff.png");
	cc->SaveAs("pic/TPCtrackingeff.eps");
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//EMC eff.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	cc->SetLogy(1);
	hTPCtracksbg=(TH1F *)hTPCtracks->Clone();
    hEMCtracksbg=(TH1F *)hEMCtracks->Clone();
	ymin = hTPCtracks->GetMinimum()*1e-2;
	ymax = hTPCtracks->GetMaximum()*10;
	htmp=histo("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	Style(hTPCtracksbg,1,kBlack,3,22,kBlack,2.15,"psame");
	Style(hTPCtracks,1,kBlack,3,22,kRed,1.65,"hfpsame");
	Style(hEMCtracksbg,1,kBlack,3,23,kBlack,2.15,"psame");
	Style(hEMCtracks,1,kBlack,3,23,6,1.65,"hfpsame");
	lg = Legend(0.15,0.2,0.45,0.35,0.045);
	lg->AddEntry(hTPCtracksbg,"N_{rc} (Track Quality)","pl");
	lg->AddEntry(hEMCtracksbg,"N_{rc} (Track Quality + EMC)","pl");
	lg = Legend(0.15,0.2,0.45,0.35,0.045);
	lg->AddEntry(hTPCtracks,"N_{rc} (Track Quality)","pl");
	lg->AddEntry(hEMCtracks,"N_{rc} (Track Quality + EMC)","pl");
	tx.DrawLatex(0.48,0.85,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/BEMCeffND.png");
	cc->SaveAs("pic/BEMCeffND.eps");

	cc->SetLogy(0);
	hBEMCeffplotbg=(TH1F *)hBEMCeffplot->Clone();
	ymin = 0;
	ymax = 1.4;
	htmp=histo("htmp1",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)","BEMC effciency",0.075,0.85,0.07,0.75);
	Style(hBEMCeffplotbg,1,kBlack,3,8,kBlack,1.9,"psame");
	Style(hBEMCeffplot,1,kBlack,3,8,kGreen+1,1.7,"psame");
	tx.DrawLatex(0.48,0.85,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/BEMCeff.png");
	cc->SaveAs("pic/BEMCeff.eps");
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//SMD eff.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	cc->SetLogy(1);
	hEMCtracksbg=(TH1F *)hEMCtracks->Clone();
    hSMDtracksbg=(TH1F *)hSMDtracks->Clone();
	ymin = hEMCtracks->GetMinimum()*1e-2;
	ymax = hEMCtracks->GetMaximum()*10;
	htmp=histo("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	Style(hEMCtracksbg,1,kBlack,3,22,kBlack,2.15,"psame");
	Style(hEMCtracks,1,kBlack,3,22,kRed,1.65,"hfpsame");
	Style(hSMDtracksbg,1,kBlack,3,23,kBlack,2.15,"psame");
	Style(hSMDtracks,1,kBlack,3,23,6,1.65,"hfpsame");
	lg = Legend(0.15,0.2,0.45,0.35,0.045);
	lg->AddEntry(hEMCtracksbg,"N_{rc} (Track Quality + EMC)","pl");
	lg->AddEntry(hSMDtracksbg,"N_{rc} (Track Quality + EMC + SMD)","pl");
	lg = Legend(0.15,0.2,0.45,0.35,0.045);
	lg->AddEntry(hEMCtracks,"N_{rc} (Track Quality + EMC)","pl");
	lg->AddEntry(hSMDtracks,"N_{rc} (Track Quality + EMC + SMD)","pl");
	tx.DrawLatex(0.48,0.85,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/BSMDeffND.png");
	cc->SaveAs("pic/BSMDeffND.eps");

	cc->SetLogy(0);
	hBSMDeffplotbg=(TH1F *)hBSMDeffplot->Clone();
	ymin = 0;
	ymax = 1.4;
	htmp=histo("htmp1",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)","BSMD effciency",0.075,0.85,0.07,0.75);
	Style(hBSMDeffplotbg,1,kBlack,3,8,kBlack,1.9,"psame");
	Style(hBSMDeffplot,1,kBlack,3,8,kGreen+1,1.7,"psame");
	tx.DrawLatex(0.48,0.85,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/BSMDeff.png");
	cc->SaveAs("pic/BSMDeff.eps");
	/////////////////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////////////////
	/*cc->SetLogy(1);
	hTPCtracks->SetAxisRange(2.0,9.9);
	hSMDtracks->SetAxisRange(2.0,9.9);
	hTPCtracksbg=(TH1F *)hTPCtracks->Clone();
    hSMDtracksbg=(TH1F *)hSMDtracks->Clone();
	ymin = hTPCtracks->GetMinimum()*3e-3;
	ymax = hTPCtracks->GetMaximum()*10;
	htmp=histo("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	htmp->SetNdivisions(505,"y");
	Style(hTPCtracksbg,1,kBlack,3,22,kBlack,2.15,"psame");
	Style(hTPCtracks,1,kBlack,3,22,kRed,1.65,"hfpsame");
	Style(hSMDtracksbg,1,kBlack,3,8,kBlack,2.05,"psame");
	Style(hSMDtracks,1,kBlack,3,8,kGreen+1,1.65,"hfpsame");
	lg = Legend(0.2,0.19,0.55,0.34,0.045);
	lg->AddEntry(hTPCtracksbg,"N_{mc}","pl");
	lg->AddEntry(hSMDtracksbg,"N_{rc} (Track Quality + e>0 + P/E + ADC0>180)","pl");
	lg = Legend(0.2,0.19,0.55,0.34,0.045);
	lg->AddEntry(hTPCtracks,"N_{mc}","pl");
	lg->AddEntry(hSMDtracks,"N_{rc} (Track Quality + e>0 + P/E + ADC0>180)","pl");
	tx.DrawTextNDC(0.55,0.85,"p+p @ 200 GeV");
	cc->SaveAs("pic/SingleEleeffND.png");
	cc->SaveAs("pic/SingleEleeffND.eps");

	cc->SetLogy(0);
	hSingleEleeffplot->SetAxisRange(0.6,10);
	hSingleEleeffplotbg=(TH1F *)hSingleEleeffplot->Clone();
	ymin = 0;
	ymax = 1.0;
	htmp=histo("htmp1",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)"," EMC+TPC efficiency",0.075,0.85,0.07,0.75);
	htmp->SetNdivisions(505,"y");
	Style(hSingleEleeffplotbg,1,kBlack,3,22,kBlack,2.5,"psame");
	Style(hSingleEleeffplot,1,kBlack,3,22,kRed,2.0,"psame");
	lg = Legend(0.62,0.31,1.00,0.45,0.06);
	lg->AddEntry(hSingleEleeffplotbg,"HT0","pl");
	lg = Legend(0.62,0.31,1.00,0.45,0.06);
	lg->AddEntry(hSingleEleeffplot,"HT0","pl");
	tx.DrawTextNDC(0.55,0.86,"p+p @ 200 GeV");
	cc->SaveAs("pic/SingleEleeff.png");
	cc->SaveAs("pic/SingleEleeff.eps");
	
	TH1F *hSingleEleeff=new TH1F("hSingleEleeff","",nPtBins,ptbin);
	for(int i=0;i<nPtBins;i++){
	hSingleEleeff->SetBinContent(i+1,hSingleEleeffplot->GetBinContent(i+28));
	hSingleEleeff->SetBinError(i+1,hSingleEleeffplot->GetBinError(i+28));
	}
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//Trigger eff. 
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	cc->SetLogy(1);
	hTPCtracksCut->SetAxisRange(1.0,13.9);
	hTPCtracksHT0->SetAxisRange(1.0,13.9);
	hTPCtracksHT2->SetAxisRange(1.0,13.9);
	hTPCtracksCutbg=(TH1F *)hTPCtracksCut->Clone();
    hTPCtracksHT0bg=(TH1F *)hTPCtracksHT0->Clone();
	hTPCtracksHT2bg=(TH1F *)hTPCtracksHT2->Clone();
	ymin = hTPCtracksCut->GetMinimum()*3e-3;
	ymax = hTPCtracksCut->GetMaximum()*10;
	htmp=histo("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	htmp->SetNdivisions(505,"y");
	Style(hTPCtracksCutbg,1,kBlack,3,22,kBlack,2.15,"psame");
	Style(hTPCtracksCut,1,kBlack,3,22,kRed,1.65,"hfpsame");
	Style(hTPCtracksHT0bg,1,kBlack,3,8,kBlack,2.05,"psame");
	Style(hTPCtracksHT0,1,kBlack,3,8,kGreen+1,1.65,"hfpsame");
	Style(hTPCtracksHT2bg,1,kBlack,3,23,kBlack,2.15,"psame");
	Style(hTPCtracksHT2,1,kBlack,3,23,6,1.65,"hfpsame");
	lg = Legend(0.25,0.18,0.55,0.33,0.045);
	lg->AddEntry(hTPCtracksCutbg,"N_{rc} (Track Quality + e>0 + P/E)","pl");
	lg->AddEntry(hTPCtracksHT0bg,"N_{rc} (Track Quality + e>0 + P/E + ADC0>180)","pl");
	lg->AddEntry(hTPCtracksHT2bg,"N_{rc} (Track Quality + e>0 + P+E + ADC0>304)","pl");
	lg = Legend(0.25,0.18,0.55,0.33,0.045);
	lg->AddEntry(hTPCtracksCut,"N_{rc} (Track Quality + e>0 + P/E)","pl");
	lg->AddEntry(hTPCtracksHT0,"N_{rc} (Track Quality + e>0 + P/E + ADC0>180)","pl");
	lg->AddEntry(hTPCtracksHT2,"N_{rc} (Track Quality + e>0 + P/E + ADC0>304)","pl");
	tx.DrawTextNDC(0.55,0.85,"p+p @ 200 GeV");
	cc->SaveAs("pic/TriggereffND.png");
	cc->SaveAs("pic/TriggereffND.eps");

	cc->SetLogy(0);
	hTriggereffHT0plot->SetAxisRange(0.6,14);
	hTriggereffHT2plot->SetAxisRange(0.6,14);
	hTriggereffHT0plotbg=(TH1F *)hTriggereffHT0plot->Clone();
	hTriggereffHT2plotbg=(TH1F *)hTriggereffHT2plot->Clone();
	ymin = 0;
	ymax = 1.4;
	htmp=histo("htmp1",20,PtMinhtmp[0],PtMaxhtmp[0],ymin,ymax,"p_{T} (GeV/c)","Trigger effciency",0.075,0.85,0.07,0.75);
	Style(hTriggereffHT0plotbg,1,kBlack,3,22,kBlack,2.5,"psame");
	Style(hTriggereffHT0plot,1,kBlack,3,22,kRed,2.0,"psame");
	Style(hTriggereffHT2plotbg,1,kBlack,3,23,kBlack,2.5,"psame");
	Style(hTriggereffHT2plot,1,kBlack,3,23,kGreen+1,2.0,"psame");
	lg = Legend(0.62,0.36,1.00,0.5,0.05);
	lg->AddEntry(hTriggereffHT0plotbg,"HT0","pl");
	lg->AddEntry(hTriggereffHT2plotbg,"HT2","pl");
	lg = Legend(0.62,0.36,1.00,0.5,0.05);
	lg->AddEntry(hTriggereffHT0plot,"HT0","pl");
	lg->AddEntry(hTriggereffHT2plot,"HT2","pl");
	tx.DrawTextNDC(0.55,0.86,"p+p @ 200 GeV");
	cc->SaveAs("pic/Triggereff.png");
	cc->SaveAs("pic/Triggereff.eps");
	
	TH1F *hTPCtrackingeff=new TH1F("hTPCtrackingeff","",nPtBins,ptbin);
	TH1F *hBEMCeff=new TH1F("hBEMCeff","",nPtBins,ptbin);
	TH1F *hBSMDeff=new TH1F("hBSMDeff","",nPtBins,ptbin);
	TH1F *hTriggereffHT0=new TH1F("hTriggereffHT0","",nPtBins,ptbin);
	TH1F *hTriggereffHT2=new TH1F("hTriggereffHT2","",nPtBins,ptbin);
	for(int i=0;i<nPtBins;i++){
	hTPCtrackingeff->SetBinContent(i+1,hTPCtrackingeffplot->GetBinContent(i+28));
	hTPCtrackingeff->SetBinError(i+1,hTPCtrackingeffplot->GetBinError(i+28));
	hBEMCeff->SetBinContent(i+1,hBEMCeffplot->GetBinContent(i+28));
	hBEMCeff->SetBinError(i+1,hBEMCeffplot->GetBinError(i+28));
	hBSMDeff->SetBinContent(i+1,hBSMDeffplot->GetBinContent(i+28));
	hBSMDeff->SetBinError(i+1,hBSMDeffplot->GetBinError(i+28));
	hTriggereffHT0->SetBinContent(i+1,hTriggereffHT0plot->GetBinContent(i+28));
	hTriggereffHT0->SetBinError(i+1,hTriggereffHT0plot->GetBinError(i+28));
	hTriggereffHT2->SetBinContent(i+1,hTriggereffHT2plot->GetBinContent(i+28));
	hTriggereffHT2->SetBinError(i+1,hTriggereffHT2plot->GetBinError(i+28));
	}
	TFile* file = new TFile("effroot/SingleEleeff.root","UPDATE");
	file->cd();
	hTPCtrackingeff->Write();
	hBEMCeff->Write();
	hBSMDeff->Write();
	hTriggereffHT0->Write();
	hTriggereffHT2->Write();
	file->Close();
}
