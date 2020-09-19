#include "../../ptbin.h"
#include "../../style.h"
void plotTriggereffforYingjie()
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
	TFile *f=new TFile("DataMaker/Single_electron_eff_forYingjie.root");
	TH1F *hTPCtracks0 = (TH1F *)f->Get("EMCtracks");
	TH1F *hTPCtracks2 = (TH1F *)hTPCtracks0->Clone("hTPCtracks2");
	TH1F *hTPCtracksSys0 = (TH1F *)hTPCtracks0->Clone("hTPCtracksSys0");
	TH1F *hTPCtracksSys2 = (TH1F *)hTPCtracks0->Clone("hTPCtracksSys2");
	TH1F *hTPCtracksHT0=(TH1F *)f->Get("TPCtracksHT0");
	TH1F *hTPCtracksHT2=(TH1F *)f->Get("TPCtracksHT2");
	TH1F *hTriggereffforYingjieHT0 = (TH1F*) hTPCtracksHT0->Clone("hTriggereffforYingjieHT0");
	TH1F *hTriggereffforYingjieHT2 = (TH1F*)hTPCtracksHT2->Clone("hTriggereffforYingjieHT2");
	TH1F *hTPCtracksSysHT0=(TH1F *)f->Get("hTPCtracksAdc0SysHT0");
	TH1F *hTPCtracksSysHT2=(TH1F *)f->Get("hTPCtracksAdc0SysHT2");
	TH1F *hTriggereffforYingjieSysHT0 = (TH1F*) hTPCtracksSysHT0->Clone("hTriggereffforYingjieSysHT0");
	TH1F *hTriggereffforYingjieSysHT2 = (TH1F*)hTPCtracksSysHT2->Clone("hTriggereffforYingjieSysHT2");
	hTPCtracks0->SetAxisRange(0,15);
	hTPCtracksHT0->SetAxisRange(0,15);
	hTPCtracksHT2->SetAxisRange(0,15);
	hTPCtracksHT0->SetBinContent(0,0);
	hTPCtracksHT2->SetBinContent(0,0);
	hTPCtracks0->SetBinContent(0,1e-5);
	hTPCtracks2->SetBinContent(0,1e-5);
	hTPCtracksHT0->SetBinContent(1001,0);
	hTPCtracksHT2->SetBinContent(1001,0);
	hTPCtracks0->SetBinContent(1001,1e-5);
	hTPCtracks2->SetBinContent(1001,1e-5);
	for(int i=1;i<1001;i++){
		if(hTPCtracks0->GetBinContent(i)<=0||hTPCtracksHT0->GetBinContent(i)>hTPCtracks0->GetBinContent(i)){
			hTPCtracks0->SetBinContent(i,1.0);
			hTPCtracksHT0->SetBinContent(i,1.0);
		}
	}
	TGraphAsymmErrors *gr0=new TGraphAsymmErrors(hTPCtracksHT0,hTPCtracks0,"B");
	for(int i=1;i<1001;i++){
		if(hTPCtracks2->GetBinContent(i)<=0||hTPCtracksHT2->GetBinContent(i)>hTPCtracks2->GetBinContent(i)){
			hTPCtracks2->SetBinContent(i,1.);
			hTPCtracksHT2->SetBinContent(i,1.0);
		}
	}
	TGraphAsymmErrors *gr2=new TGraphAsymmErrors(hTPCtracksHT2,hTPCtracks2,"B");
	hTPCtracksSysHT0->SetBinContent(0,0);
	hTPCtracksSysHT2->SetBinContent(0,0);
	hTPCtracksSys0->SetBinContent(0,1e-5);
	hTPCtracksSys2->SetBinContent(0,1e-5);
	hTPCtracksSysHT0->SetBinContent(1001,0);
	hTPCtracksSysHT2->SetBinContent(1001,0);
	hTPCtracksSys0->SetBinContent(1001,1e-5);
	hTPCtracksSys2->SetBinContent(1001,1e-5);
	for(int i=1;i<1001;i++){
		if(hTPCtracksSys0->GetBinContent(i)<=0||hTPCtracksSysHT0->GetBinContent(i)>hTPCtracksSys0->GetBinContent(i)){
			hTPCtracksSys0->SetBinContent(i,1.);
			hTPCtracksSysHT0->SetBinContent(i,1.0);
		}
	}
	TGraphAsymmErrors *gr0sys=new TGraphAsymmErrors(hTPCtracksSysHT0,hTPCtracksSys0,"B");
	for(int i=1;i<1001;i++){
		if(hTPCtracksSys2->GetBinContent(i)<=0||hTPCtracksSysHT2->GetBinContent(i)>hTPCtracksSys2->GetBinContent(i)){
			hTPCtracksSys2->SetBinContent(i,1.);
			hTPCtracksSysHT2->SetBinContent(i,1.0);
		}
	}
	TGraphAsymmErrors *gr2sys=new TGraphAsymmErrors(hTPCtracksSysHT2,hTPCtracksSys2,"B");
	for(int i=0; i<1000; i++) {
		double x0,y0;
		int a=gr0->GetPoint(i,x0,y0);
		hTriggereffforYingjieHT0->SetBinContent(i+1,y0);
		hTriggereffforYingjieHT0->SetBinError(i+1,gr0->GetErrorY(i));
		double x2,y2;
		int b=gr2->GetPoint(i,x2,y2);
		hTriggereffforYingjieHT2->SetBinContent(i+1,y2);
		hTriggereffforYingjieHT2->SetBinError(i+1,gr2->GetErrorY(i));
		double x0sys,y0sys;
		int c=gr0sys->GetPoint(i,x0sys,y0sys);
		hTriggereffforYingjieSysHT0->SetBinContent(i+1,y0sys);
		hTriggereffforYingjieSysHT0->SetBinError(i+1,gr0sys->GetErrorY(i));
		double x2sys,y2sys;
		int d=gr2sys->GetPoint(i,x2sys,y2sys);
		hTriggereffforYingjieSysHT2->SetBinContent(i+1,y2sys);
		hTriggereffforYingjieSysHT2->SetBinError(i+1,gr2sys->GetErrorY(i));
	}

	/*hTriggereffforYingjieSysHT0->Add(hTriggereffforYingjieHT0,-1);
	  hTriggereffforYingjieSysHT2->Add(hTriggereffforYingjieHT2,-1);
	  hTriggereffforYingjieSysHT0->Print("ALL");
	//hTriggereffforYingjieSysHT2->Print("ALL");
	for(int i=0; i<1000; i++) {
	float sysht0=fabs(hTriggereffforYingjieSysHT0->GetBinContent(i+1));
	float sysht2=fabs(hTriggereffforYingjieSysHT2->GetBinContent(i+1));
	hTriggereffforYingjieSysHT0->SetBinContent(i+1,hTriggereffforYingjieHT0->GetBinContent(i+1));
	hTriggereffforYingjieSysHT0->SetBinError(i+1,sysht0);
	hTriggereffforYingjieSysHT2->SetBinContent(i+1,hTriggereffforYingjieHT2->GetBinContent(i+1));
	hTriggereffforYingjieSysHT2->SetBinError(i+1,sysht2);
	}*/
	hTriggereffforYingjieHT0->Print("ALL");
	//hTriggereffforYingjieSysHT2->Print("ALL");
	cc=Canvas("cc",0.12,0.06,0.15,0.06,0,1,0);
	cc->SetGrid(1,1);
	float ymin,ymax;
	//cc->SetLogy(1);
	//hTPCtracks->SetAxisRange(2.0,9.9);
	//hTPCtracksHT0->SetAxisRange(2.0,9.9);
	//hTPCtracksHT2->SetAxisRange(2.0,9.9);
	hTPCtracksbg=(TH1F *)hTPCtracks0->Clone();
	hTPCtracksHT0bg=(TH1F *)hTPCtracksHT0->Clone();
	hTPCtracksHT2bg=(TH1F *)hTPCtracksHT2->Clone();
	ymin = hTPCtracks0->GetMinimum()*3e-3;
	ymax = hTPCtracks0->GetMaximum()*10;
	htmp=histo("htmp",20,1.7,15.3,ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	htmp->SetNdivisions(505,"y");
	Style(hTPCtracksbg,1,kBlack,3,22,kBlack,2.15,"psame");
	Style(hTPCtracks0,1,kBlack,3,22,kRed,1.65,"hfpsame");
	Style(hTPCtracksHT0bg,1,kBlack,3,8,kBlack,2.05,"psame");
	Style(hTPCtracksHT0,1,kBlack,3,8,kGreen+1,1.65,"hfpsame");
	Style(hTPCtracksHT2bg,1,kBlack,3,23,kBlack,2.15,"psame");
	Style(hTPCtracksHT2,1,kBlack,3,23,6,1.65,"hfpsame");
	lg = Legend(0.15,0.19,0.5,0.34,0.04);
	lg->AddEntry(hTPCtracksbg,"N_{rc} (Track Quality + EMC)","pl");
	lg->AddEntry(hTPCtracksHT0bg,"N_{rc} (Track Quality + EMC + ADC0>180 + DSMADC>11)","pl");
	lg->AddEntry(hTPCtracksHT2bg,"N_{rc} (Track Quality + EMC + ADC0>300 + DSMADC>18)","pl");
	lg = Legend(0.15,0.19,0.5,0.34,0.04);
	lg->AddEntry(hTPCtracks0,"N_{rc} (Track Quality + EMC)","pl");
	lg->AddEntry(hTPCtracksHT0,"N_{rc} (Track Quality + EMC + ADC0>180 + DSMADC>11)","pl");
	lg->AddEntry(hTPCtracksHT2,"N_{rc} (Track Quality + EMC + ADC0>300 + DSMADC>18)","pl");
	tx.DrawLatex(0.5,0.85,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/TriggereffforYingjieND.png");
	cc->SaveAs("pic/TriggereffforYingjieND.eps");

	cc->SetLogy(0);
	//hTriggereffforYingjieHT0->SetAxisRange(0.6,10);
	//hTriggereffforYingjieHT2->SetAxisRange(0.6,10);
	hTriggereffforYingjieHT0bg=(TH1F *)hTriggereffforYingjieHT0->Clone("hTriggereffforYingjieHT0bg");
	hTriggereffforYingjieHT2bg=(TH1F *)hTriggereffforYingjieHT2->Clone("hTriggereffforYingjieHT2bg");
	ymin = 0;
	ymax = 1.4;
	htmp=histo("htmp1",20,0.8,12,ymin,ymax,"p_{T} (GeV/c)"," Trigger efficiency",0.075,0.85,0.07,0.75);
	htmp->SetNdivisions(505,"y");
	Style(hTriggereffforYingjieHT0bg,1,kBlack,3,22,kBlack,2.5,"psame");
	Style(hTriggereffforYingjieHT0,1,kBlack,3,22,kRed,2.0,"psame");
	Style(hTriggereffforYingjieHT2bg,1,kBlack,3,23,kBlack,2.5,"psame");
	Style(hTriggereffforYingjieHT2,1,kBlack,3,23,kGreen+1,2.0,"psame");
	lg = Legend(0.62,0.31,1.00,0.45,0.06);
	lg->AddEntry(hTriggereffforYingjieHT0bg,"HT0","pl");
	lg->AddEntry(hTriggereffforYingjieHT2bg,"HT2","pl");
	lg = Legend(0.62,0.31,1.00,0.45,0.06);
	lg->AddEntry(hTriggereffforYingjieHT0,"HT0","pl");
	lg->AddEntry(hTriggereffforYingjieHT2,"HT2","pl");
	tx.DrawLatex(0.48,0.86,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("pic/TriggereffforYingjie.png");
	cc->SaveAs("pic/TriggereffforYingjie.eps");

	//hTriggereffforYingjieHT0->Print("ALL");
	//hTriggereffforYingjieHT2->Print("ALL");
	TFile* file = new TFile("effroot/TriggereffforYingjie.root","RECREATE");
	file->cd();
	hTriggereffforYingjieHT0->Write();
	hTriggereffforYingjieHT2->Write();
	hTriggereffforYingjieSysHT0->Write();
	hTriggereffforYingjieSysHT2->Write();
	file->Close();
}
