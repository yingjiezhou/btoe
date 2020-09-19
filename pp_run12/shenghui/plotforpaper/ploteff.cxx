#include "../ptbin.h"
#include "../style.h"
void ploteff()
{
	setstyle();
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetNDC();
	tx.SetTextFont(42);
	TFile *f;
	TH2F *htmp;
	f=new TFile("../Efficiency/embedding/effroot/PHEReceff.root");
	TH1F *hReceff=(TH1F *)f->Get("hefffun");
	///////////////////////////////////////////////////////////////////
	//nsigmae cut eff
	///////////////////////////////////////////////////////////////////
	f=new TFile("../Efficiency/effroot/nSigmaECuteff.root");
	TH1F *hnSigmaeCuteff_HT0=(TH1F *)f->Get("hnSigmaECuteff_HT0");
	TH1F *hnSigmaeCuteff_HT2=(TH1F *)f->Get("hnSigmaECuteff_HT2");
	f=new TFile("../Efficiency/effroot/SMDeff.root");
	TH1F *hSMDeff_HT0=(TH1F *)f->Get("hSMDeff_HT0");
	TH1F *hSMDeff_HT2=(TH1F *)f->Get("hSMDeff_HT2");
	f=new TFile("../Efficiency/embedding/effroot/SingleEleeff.root");
	TH1F *hSingleEleeff_HT0=(TH1F *)f->Get("hSingleEleeffHT0");
	TH1F *hSingleEleeff_HT2=(TH1F *)f->Get("hSingleEleeffHT2");
	
	TH1F *hReceffbg=(TH1F *)hReceff->Clone("hReceffbg");
	TH1F *hnSigmaeCuteff_HT0bg=(TH1F *)hnSigmaeCuteff_HT0->Clone("hnSigmaeCuteff_HT0bg");
	TH1F *hnSigmaeCuteff_HT2bg=(TH1F *)hnSigmaeCuteff_HT2->Clone("hnSigmaeCuteff_HT0bg");
	TH1F *hSMDeff_HT0bg=(TH1F *)hSMDeff_HT0->Clone("hSMDeff_HT0bg");
	TH1F *hSMDeff_HT2bg=(TH1F *)hSMDeff_HT2->Clone("hSMDeff_HT0bg");
	TH1F *hSingleEleeff_HT0bg=(TH1F *)hSingleEleeff_HT0->Clone("hSingleEleeff_HT0bg");
	TH1F *hSingleEleeff_HT2bg=(TH1F *)hSingleEleeff_HT2->Clone("hSingleEleeff_HT0bg");
	hnSigmaeCuteff_HT0->SetAxisRange(PtMin[1],PtMax[1],"X");
	hnSigmaeCuteff_HT2->SetAxisRange(PtMin[2],PtMax[2],"X");
	hSMDeff_HT0->SetAxisRange(PtMin[1],PtMax[1],"X");
	hSMDeff_HT2->SetAxisRange(PtMin[2],PtMax[2],"X");
	hSingleEleeff_HT0->SetAxisRange(PtMin[1],PtMax[1],"X");
	hSingleEleeff_HT2->SetAxisRange(PtMin[2],PtMax[2],"X");
	hnSigmaeCuteff_HT0bg->SetAxisRange(PtMin[1],PtMax[1],"X");
	hnSigmaeCuteff_HT2bg->SetAxisRange(PtMin[2],PtMax[2],"X");
	hSMDeff_HT0bg->SetAxisRange(PtMin[1],PtMax[1],"X");
	hSMDeff_HT2bg->SetAxisRange(PtMin[2],PtMax[2],"X");
	hSingleEleeff_HT0bg->SetAxisRange(PtMin[1],PtMax[1],"X");
	hSingleEleeff_HT2bg->SetAxisRange(PtMin[2],PtMax[2],"X");

	TCanvas *cc=Canvas("cc",0.12,0.04,0.15,0.06,0,0,0);
	htmp = histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],1,0,1.6,"p_{T} (GeV/c)","efficiency",0.07,0.95,0.075,0.75);
	Style(hnSigmaeCuteff_HT0,1,kCyan+1,2,33,kCyan+1,2.5,"plsame");
	Style(hnSigmaeCuteff_HT2,1,kBlue,2,21,kBlue,1.7,"plsame");
	//Style(hSMDeff_HT0,1,kMagenta+1,2,29,kMagenta+1,2.4,"plsame");
	//Style(hSMDeff_HT2,1,kGreen+1,2,23,kGreen+1,1.9,"plsame");
	Style(hReceff,1,kOrange,2,34,kOrange,2.0,"plsame");
	Style(hSingleEleeff_HT0,1,kBlack,2,8,kBlack,1.7,"plsame");
	Style(hSingleEleeff_HT2,1,kRed,2,22,kRed,1.9,"plsame");
	lg= Legend(0.62,0.58,0.97,0.91,0.04);
	lg->AddEntry(hnSigmaeCuteff_HT0,"HT0 n#sigma_{e} cut","pl");
	lg->AddEntry(hnSigmaeCuteff_HT2,"HT2 n#sigma_{e} cut","pl");
	lg->AddEntry(hReceff,"Reconstruction","pl");
	//lg->AddEntry(hSMDeff_HT0,"HT0 BSMD","pl");
	//lg->AddEntry(hSMDeff_HT2,"HT2 BSMD","pl");
	lg->AddEntry(hSingleEleeff_HT0,"HT0 Single electron","pl");
	lg->AddEntry(hSingleEleeff_HT2,"HT2 Single electron","pl");
	tx.DrawLatex(2.3,1.43,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("./pic/Eff.png");
	cc->SaveAs("./pic/Eff.eps");
	hnSigmaeCuteff_HT0->SetAxisRange(PtMin[1],3.9,"X");
	hnSigmaeCuteff_HT2->SetAxisRange(PtMin[2],PtMax[2],"X");
	hSMDeff_HT0->SetAxisRange(PtMin[1],3.9,"X");
	hSMDeff_HT2->SetAxisRange(PtMin[2],PtMax[2],"X");
	hSingleEleeff_HT0->SetAxisRange(PtMin[1],PtMax[2],"X");
	hSingleEleeff_HT2->SetAxisRange(PtMin[2],PtMax[2],"X");
	hnSigmaeCuteff_HT0bg->SetAxisRange(PtMin[1],3.9,"X");
	hnSigmaeCuteff_HT2bg->SetAxisRange(PtMin[2],PtMax[2],"X");
	hSMDeff_HT0bg->SetAxisRange(PtMin[1],3.9,"X");
	hSMDeff_HT2bg->SetAxisRange(PtMin[2],PtMax[2],"X");
	hSingleEleeff_HT0bg->SetAxisRange(PtMin[1],PtMax[2],"X");
	hSingleEleeff_HT2bg->SetAxisRange(PtMin[2],PtMax[2],"X");

	TCanvas *cc=Canvas("cc",0.12,0.036,0.15,0.06,0,0,0);
	htmp = histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],1,0,1.2,"p_{T} (GeV/c)","Efficiency",0.07,0.95,0.075,0.75);
	Style(hnSigmaeCuteff_HT0bg,1,1,2,33,1,2.8,"plsame");
	Style(hnSigmaeCuteff_HT0,1,kMagenta+2,2,33,kMagenta+2,2.4,"plsame");
	Style(hnSigmaeCuteff_HT2bg,1,1,2,33,1,2.8,"plsame");
	Style(hnSigmaeCuteff_HT2,1,kMagenta+2,2,33,kMagenta+2,2.4,"plsame");
	//Style(hnSigmaeCuteff_HT2,1,kBlue,2,21,kBlue,1.7,"plsame");
	//Style(hSMDeff_HT0bg,1,1,3,20,1,1.9,"plsame");
	//Style(hSMDeff_HT0,1,kYellow+1,3,20,kYellow+1,1.7,"plsame");
	//Style(hSMDeff_HT2bg,1,1,3,20,1,1.9,"plsame");
	//Style(hSMDeff_HT2,1,kYellow+1,3,20,kYellow+1,1.7,"plsame");
	//Style(hSMDeff_HT2,1,kGreen+1,2,23,kGreen+1,1.9,"plsame");
	//Style(hReceffbg,1,1,3,21,1,1.7,"plsame");
	//Style(hReceff,1,kGreen+1,3,21,kGreen+1,1.4,"plsame");
	//Style(hSingleEleeff_HT0,1,kBlack,2,8,kBlack,1.7,"plsame");
	Style(hSingleEleeff_HT0bg,1,1,2,34,1,2.35,"plsame");
	Style(hSingleEleeff_HT0,1,kOrange+1,2,34,kOrange+1,1.95,"plsame");
	Style(hSingleEleeff_HT2bg,1,1,2,29,1,2.7,"plsame");
	Style(hSingleEleeff_HT2,1,kCyan+2,2,29,kCyan+2,2.3,"plsame");
	lg= Legend(0.55,0.65,0.97,0.85,0.045);
	lg->AddEntry(hnSigmaeCuteff_HT0bg,"n#sigma_{e} cut","pl");
	//lg->AddEntry(hReceffbg,"Reconstruction","pl");
	//lg->AddEntry(hSMDeff_HT2bg,"BSMD EPID","pl");
	lg->AddEntry(hSingleEleeff_HT0bg,"HT0 Single electron","pl");
	lg->AddEntry(hSingleEleeff_HT2bg,"HT2 Single electron","pl");
	lg= Legend(0.55,0.65,0.97,0.85,0.045);
	lg->AddEntry(hnSigmaeCuteff_HT0,"n#sigma_{e} cut","pl");
	//lg->AddEntry(hReceff,"Reconstruction","pl");
	//lg->AddEntry(hSMDeff_HT2,"BSMD EPID","pl");
	lg->AddEntry(hSingleEleeff_HT0,"HT0 Single electron","pl");
	lg->AddEntry(hSingleEleeff_HT2,"HT2 Single electron","pl");
	tx.SetTextSize(0.07);
	tx.DrawLatex(0.5,0.86,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("./pic/EffforPaper.png");
	cc->SaveAs("./pic/EffforPaper.eps");
}
