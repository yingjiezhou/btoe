#include "../../ptbin.h"
#include "../../style.h"
void plotptresolution()
{
	setstyle();
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetNDC();
	tx.SetTextFont(42);
	TH1F *htmp;
	TLegend *lg;
	TFile *f;
	f=new TFile("DataMaker/Single_electron_eff.root");
	TH2F *hPtDiff = (TH2F *)f->Get("PtDiffW");
	//TH1F *hDiff = (TH1F *)hPtDiff->ProjectionY();
	TH1F *hDiff = (TH1F *)hPtDiff->ProfileX("h1",1,400,"s");
	hDiff->Sumw2();
	hDiff->Rebin(20);
	f=new TFile("../../TriggerBias/DataMaker/ana/NPEEvent/outmini_mix_mode1_hadd_hist.root");
	TH2F *hPtDiffr = (TH2F *)f->Get("PtDiff");
	//TH1F *hDiffr = (TH1F *)hPtDiffr->ProjectionY("",51,1000);
	TH1F *hDiffr = (TH1F *)hPtDiffr->ProfileX("h2",1,400,"s");
	TH1F *hDiffr1=(TH1F *)hDiffr->Clone("hDiffr1");
	f=new TFile("../../TriggerBias/DataMaker/ana/NPEEvent/outmini_mix_mode1_hadd_forPG4_hist.root");
	TH2F *hPtDiffr2 = (TH2F *)f->Get("PtDiff");
	TH1F *hDiffr2 = (TH1F *)hPtDiffr2->ProfileX("h3",1,400,"s");
	f=new TFile("../../TriggerBias/DataMaker/ana/NPEEvent/outmini_mix_mode1_hadd_forPG6_hist.root");
	TH2F *hPtDiffr3 = (TH2F *)f->Get("PtDiff");
	TH1F *hDiffr3 = (TH1F *)hPtDiffr3->ProfileX("h4",1,400,"s");
	hDiffr->Sumw2();
	hDiffr->Rebin(25);
	hDiffr1->Sumw2();
	hDiffr1->Rebin(100);
	hDiffr2->Sumw2();
	hDiffr2->Rebin(100);
	hDiffr3->Sumw2();
	hDiffr3->Rebin(100);
	
	//hDiffr->Scale(1./(1.0*hDiffr->Integral()));
	hDiffr->SetAxisRange(1.,1.9);
	hDiffr1->SetAxisRange(2.6,3.9);
	hDiffr2->SetAxisRange(4.0,5.9);
	hDiffr3->SetAxisRange(6.0,10);
	//hDiff->Scale(1./(1.0*hDiff->Integral()));
	
	TCanvas *cc=Canvas("cc",0.14,0.04,0.145,0.04,0,0,1);
    cc->SetGrid(1,1);
	float ymin,ymax;
	ymin = 1e-5;
	ymax = 1;
	//htmp=histo("htmp",20,-0.5,0.5,ymin,ymax,"(p_{T}^{primary rc}-p_{T}^{mc})/p_{T}^{mc}","1/N_{track}",0.075,0.9,0.07,0.85);
	//htmp=histo("htmp",20,-0.5,0.5,ymin,ymax,"(p_{T}^{global rc}-p_{T}^{mc})/p_{T}^{mc}","1/N_{track}",0.075,0.9,0.07,0.85);
	htmp=histo("htmp",20,0,10,-0.1,0.1,"p_{T}^{mc}","(p_{T}^{primary rc}-p_{T}^{mc})/p_{T}^{mc}",0.075,0.8,0.07,0.91);
	//htmp=histo("htmp",20,0,10,-0.1,0.1,"p_{T}^{mc}","(p_{T}^{global rc}-p_{T}^{mc})/p_{T}^{mc}",0.075,0.8,0.07,0.85);
	htmp->SetNdivisions(505,"y");
	//Style(hPtDiff,0,0,0,0,0,0,"colzsame");
	//Style(hPtDiffr,0,0,0,0,0,0,"colzsame");
	Style(hDiff,1,kRed,3,22,kRed,1.65,"psame");
	Style(hDiffr,1,kBlack,3,22,kBlack,1.65,"psame");
	Style(hDiffr1,1,kBlack,3,22,kBlack,1.65,"psame");
	Style(hDiffr2,1,kBlack,3,22,kBlack,1.65,"psame");
	Style(hDiffr3,1,kBlack,3,22,kBlack,1.65,"psame");
	tx.DrawLatex(0.3,0.88,"Run12 p+p @ #sqrt{s} = 200GeV");
	lg = Legend(0.55,0.73,0.9,0.85,0.05);
	lg->AddEntry(hDiff,"Single Electron","pl");
	lg->AddEntry(hDiffr,"HFE","pl");
	cc->SaveAs("pic/Resolution.png");
	cc->SaveAs("pic/Resolution.eps");
}
