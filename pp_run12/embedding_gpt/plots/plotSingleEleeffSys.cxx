#include "../../ptbin.h"
#include "../../style.h"
void plotSingleEleeffSys()
{
	setstyle();
	TLatex tx;
	tx.SetTextSize(0.07);
	TH1F *htmp;
	TLegend *lg;
	TFile *f=new TFile("DataMaker/Single_electron_eff.root");
	TH1F *hTPCtracks = (TH1F *)f->Get("hmcptw");
	TH1F *hTPCtracksnHitsFit = (TH1F *)f->Get("hrcptwnHitsFit");
	TH1F *hTPCtracksnHitsDedx = (TH1F *)f->Get("hrcptwnHitsDedx");
	TH1F *hTPCtracksDca = (TH1F *)f->Get("hrcptwDca");
	TH1F *hTPCtracksAdc0HT0 = (TH1F *)f->Get("hTPCtracksAdc0SysHT0");
	TH1F *hTPCtracksAdc0HT2 = (TH1F *)f->Get("hTPCtracksAdc0SysHT2");
	TH1F *hTPCtracksPOEHT0 = (TH1F *)f->Get("hTPCtracksPOESysHT0");
	TH1F *hTPCtracksPOEHT2 = (TH1F *)f->Get("hTPCtracksPOESysHT2");
	
	TH1F *hTPCtrackingeffnHitsFitplot = (TH1F*) calEffHistB(hTPCtracksnHitsFit,hTPCtracks);
	hTPCtrackingeffnHitsFitplot->SetName("hTPCtrackingeffnHitsFitplot");
	TH1F *hTPCtrackingeffnHitsDedxplot = (TH1F*) calEffHistB(hTPCtracksnHitsDedx,hTPCtracks);
	hTPCtrackingeffnHitsDedxplot->SetName("hTPCtrackingeffnHitsDedxplot");
	TH1F *hTPCtrackingeffDcaplot = (TH1F*) calEffHistB(hTPCtracksDca,hTPCtracks);
	hTPCtrackingeffDcaplot->SetName("hTPCtrackingeffDcaplot");
	
	TH1F *hSingleEleeffAdc0HT0plot = (TH1F*) calEffHistB(hTPCtracksAdc0HT0,hTPCtracks);
	hSingleEleeffAdc0HT0plot->SetName("hSingleEleeffAdc0HT0plot");
	TH1F *hSingleEleeffAdc0HT2plot = (TH1F*) calEffHistB(hTPCtracksAdc0HT2,hTPCtracks);
	hSingleEleeffAdc0HT2plot->SetName("hSingleEleeffAdc0HT2plot");
	
	TH1F *hSingleEleeffPOEHT0plot = (TH1F*) calEffHistB(hTPCtracksPOEHT0,hTPCtracks);
	hSingleEleeffPOEHT0plot->SetName("hSingleEleeffPOEHT0plot");
	TH1F *hSingleEleeffPOEHT2plot = (TH1F*) calEffHistB(hTPCtracksPOEHT2,hTPCtracks);
	hSingleEleeffPOEHT2plot->SetName("hSingleEleeffPOEHT2plot");
	
	TH1F *hTPCtrackingeffnHitsFit=new TH1F("hTPCtrackingeffnHitsFit","",nPtBins,ptbin);
	TH1F *hTPCtrackingeffnHitsDedx=new TH1F("hTPCtrackingeffnHitsDedx","",nPtBins,ptbin);
	TH1F *hTPCtrackingeffDca=new TH1F("hTPCtrackingeffDca","",nPtBins,ptbin);
	TH1F *hSingleEleeffAdc0HT0=new TH1F("hSingleEleeffAdc0HT0","",nPtBins,ptbin);
	TH1F *hSingleEleeffAdc0HT2=new TH1F("hSingleEleeffAdc0HT2","",nPtBins,ptbin);
	TH1F *hSingleEleeffPOEHT0=new TH1F("hSingleEleeffPOEHT0","",nPtBins,ptbin);
	TH1F *hSingleEleeffPOEHT2=new TH1F("hSingleEleeffPOEHT2","",nPtBins,ptbin);
	for(int i=0;i<nPtBins;i++){
	hTPCtrackingeffnHitsFit->SetBinContent(i+1,hTPCtrackingeffnHitsFitplot->GetBinContent(i+28));
	hTPCtrackingeffnHitsFit->SetBinError(i+1,hTPCtrackingeffnHitsFitplot->GetBinError(i+28));
	hTPCtrackingeffnHitsDedx->SetBinContent(i+1,hTPCtrackingeffnHitsDedxplot->GetBinContent(i+28));
	hTPCtrackingeffnHitsDedx->SetBinError(i+1,hTPCtrackingeffnHitsDedxplot->GetBinError(i+28));
	hTPCtrackingeffDca->SetBinContent(i+1,hTPCtrackingeffDcaplot->GetBinContent(i+28));
	hTPCtrackingeffDca->SetBinError(i+1,hTPCtrackingeffDcaplot->GetBinError(i+28));
	hSingleEleeffAdc0HT0->SetBinContent(i+1,hSingleEleeffAdc0HT0plot->GetBinContent(i+28));
	hSingleEleeffAdc0HT0->SetBinError(i+1,hSingleEleeffAdc0HT0plot->GetBinError(i+28));
	hSingleEleeffAdc0HT2->SetBinContent(i+1,hSingleEleeffAdc0HT2plot->GetBinContent(i+28));
	hSingleEleeffAdc0HT2->SetBinError(i+1,hSingleEleeffAdc0HT2plot->GetBinError(i+28));
	hSingleEleeffPOEHT0->SetBinContent(i+1,hSingleEleeffPOEHT0plot->GetBinContent(i+28));
	hSingleEleeffPOEHT0->SetBinError(i+1,hSingleEleeffPOEHT0plot->GetBinError(i+28));
	hSingleEleeffPOEHT2->SetBinContent(i+1,hSingleEleeffPOEHT2plot->GetBinContent(i+28));
	hSingleEleeffPOEHT2->SetBinError(i+1,hSingleEleeffPOEHT2plot->GetBinError(i+28));
	}
	TFile* file = new TFile("effroot/SingleEleeffSys.root","RECREATE");
	file->cd();
	hTPCtrackingeffnHitsFit->Write();
	hTPCtrackingeffnHitsDedx->Write();
	hTPCtrackingeffDca->Write();
	hSingleEleeffAdc0HT0->Write();
	hSingleEleeffAdc0HT2->Write();
	hSingleEleeffPOEHT0->Write();
	hSingleEleeffPOEHT2->Write();
	file->Close();
}
