#include "../ptbin.h"
#include "../style.h"
#include "../draw_sys.C"
#include "../draw_syspp.C"
void plotNPEoverPHE()
{
	setstyle();
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetTextFont(42);
	tx.SetNDC();
	TFile *f;
	TH2F *htmp;
	f=new TFile("../CrossSection/rootfile/NPE.root");
	TH1F *hRatioNPEPHE       = (TH1F*)f->Get("hRatioNPEPHE");
	hRatioNPEPHE->Print("All");
	f=new TFile("../SysUnc/rootfile/NPESys.root");
	TH1F *hSysnHitsFitCut       = (TH1F*)f->Get("hSysnHitsFitCut");
	TH1F *hSysnHitsDedxCut      = (TH1F*)f->Get("hSysnHitsDedxCut");
	TH1F *hSysDcaCut            = (TH1F*)f->Get("hSysDcaCut");
	TH1F *hSysMassCut           = (TH1F*)f->Get("hSysMassCut");
	TH1F *hSysGpTCut           = (TH1F*)f->Get("hSysGpTCut");
	TH1F *hSysnSigmaEFit2sigma  = (TH1F*)f->Get("hSysnSigmaEFit2sigma");
	f=new TFile("../SysUnc/rootfile/NPEoPHESys.root");
	TH1F *hSysnSigmaECut     = (TH1F*)f->Get("hRatioNPEPHEnSigmaECutSys");
	TH1F *hSysReceffFit  = (TH1F*)f->Get("hRatioNPEPHEReceffFitSys");
	TH1F *hSysBEMCeff    = (TH1F*)f->Get("hRatioNPEPHEBEMCSys");
	TH1F *hSysTriggereff     = (TH1F*)f->Get("hRatioNPEPHETriggereffSys");

	TH1F *hSys=(TH1F *)hSysTriggereff->Clone("hSys");
	for(int i=1;i<=nPtBins;i++){
		hSys->SetBinContent(i,sqrt(pow(hSysnHitsFitCut->GetBinContent(i),2)+pow(hSysnHitsDedxCut->GetBinContent(i),2)+pow(hSysDcaCut->GetBinContent(i),2)+pow(hSysMassCut->GetBinContent(i)/(fabs(hSysMassCut->GetBinContent(i))+1)*(1+1./hRatioNPEPHE->GetBinContent(i)),2)+pow(hSysGpTCut->GetBinContent(i)/(fabs(hSysGpTCut->GetBinContent(i))+1)*(1+1./hRatioNPEPHE->GetBinContent(i)),2)+pow(hSysnSigmaEFit2sigma->GetBinContent(i),2)+pow((hSysnSigmaECut->GetBinContent(i)-hRatioNPEPHE->GetBinContent(i))/hRatioNPEPHE->GetBinContent(i),2)+pow((hSysReceffFit->GetBinContent(i)-hRatioNPEPHE->GetBinContent(i))/hRatioNPEPHE->GetBinContent(i),2)+pow((hSysBEMCeff->GetBinContent(i)-hRatioNPEPHE->GetBinContent(i))/hRatioNPEPHE->GetBinContent(i),2)+pow((hSysTriggereff->GetBinContent(i)-hRatioNPEPHE->GetBinContent(i))/hRatioNPEPHE->GetBinContent(i),2)));
	    hSys->SetBinError(i,0);
	}
	TH1F *hNPEoverPHESys= new TH1F("hNPEoverPHESys",";p_{T} (GeV/c); Sys Unc",nPtBins,ptbin);	
	for(int i=0;i<nPtBins;i++) {
		hNPEoverPHESys->SetBinContent(i+1,hRatioNPEPHE->GetBinContent(i+1));
		hNPEoverPHESys->SetBinError(i+1,hRatioNPEPHE->GetBinContent(i+1)*hSys->GetBinContent(i+1));//0.1764);
		//cout<<hNPEoverPHESys->GetBinContent(i+1)<<" "<<hNPEoverPHESys->GetBinError(i+1)<<endl;
	}
	TGraphErrors *grNPEsys = new TGraphErrors(hNPEoverPHESys);
	hRatioNPEPHEbg=(TH1F *)hRatioNPEPHE->Clone();
	TCanvas *c=Canvas("c",0.12,0.036,0.15,0.06,0,0,0);
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,0,3,"p_{T} (GeV/c)","Signal/Background",0.075,0.85,0.07,0.83);
	//htmp->SetNdivisions(505,"y");
	Style(hRatioNPEPHEbg,1,1,1,8,1,1.9,"psame");
	draw_syspp(grNPEsys,kYellow+2,2.5,10);
	Style(hRatioNPEPHE,1,1,3,8,kYellow+2,1.7,"psame");
	/*StyleTGraph(gr08bg,1,1,2,23,1,2.3,"psame");
	draw_syspp(gr08sys,kGreen-1,2.5,10);
	StyleTGraph(gr08,1,1,2,23,kGreen-1,2.1,"psame");
	lg= Legend(0.5,0.7,0.9,0.8,0.04);
	lg->AddEntry(hRatioNPEPHEbg,"Run12,|y|<0.7","pl");
	lg->AddEntry(gr08bg,"Run08 published,|y|<0.5","pl");
	lg= Legend(0.5,0.7,0.9,0.8,0.04);
	lg->AddEntry(hRatioNPEPHE,"Run12,|y|<0.7","pl");
	lg->AddEntry(gr08,"Run08 published,|y|<0.5","pl");*/
	tx.DrawLatex(0.5,0.86,"p+p @ #sqrt{s} = 200 GeV");
	c->SaveAs("./pic/NPEovrePHE.png");
	c->SaveAs("./pic/NPEoverPHE.pdf");
}
