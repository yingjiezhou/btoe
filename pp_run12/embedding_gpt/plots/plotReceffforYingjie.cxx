#include "../../ptbin.h"
#include "../../style.h"
void plotReceffforYingjie()
{
	setstyle();
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetTextFont(42);
	//TCanvas *cc=Canvas("cc",0.14,0.04,0.15,0.06,0,0,0);
	//cc->SetGrid(1,1);
	TH2F *htmp;
	TLegend *lg;
	TFile *f = new TFile("DataMaker/Pi0Dalitz_hist_forYingjie.root");
	//TFile *f = new TFile("DataMaker/Pi0Dalitz_hist_Sys_forYingjie.root");
	//TFile *f = new TFile("DataMaker/Pi0Dalitz_hist_BRSys_forYingjie.root");
	TH1F *InputNumberPi0Dalitz=(TH1F *)f->Get("hnTotalyCut");
	TH1F *EleNumberPi0Dalitz=(TH1F *)f->Get("RcptPosEleSMD");
	TH1F *RcptPi0Dalitz = (TH1F *)f->Get("RcptSMD");
	TH1F *RcptMeePi0Dalitz = (TH1F *)f->Get("RcptMeeSMD2");
	//TH1F *RcptMeePi0Dalitz = (TH1F *)f->Get("RcptMeeSysSMD");
	//TH1F *RcptMeePi0Dalitz = (TH1F *)f->Get("RcptMeeGptP");
	//TFile *f = new TFile("DataMaker/EtaDalitz_hist_forYingjie.root");
	//TFile *f = new TFile("DataMaker/EtaDalitz_hist_Sys_forYingjie.root");
	TFile *f = new TFile("DataMaker/EtaDalitz_hist_BRSys_forYingjie.root");
	TH1F *InputNumberEtaDalitz=(TH1F *)f->Get("hnTotalyCut");
	TH1F *EleNumberEtaDalitz=(TH1F *)f->Get("RcptPosEleSMD");
	TH1F *RcptEtaDalitz = (TH1F *)f->Get("RcptSMD");
	TH1F *RcptMeeEtaDalitz = (TH1F *)f->Get("RcptMeeSMD2");
	//TH1F *RcptMeeEtaDalitz = (TH1F *)f->Get("RcptMeeSysSMD");
	//TH1F *RcptMeeEtaDalitz = (TH1F *)f->Get("RcptMeeGptP");
	TFile *f = new TFile("DataMaker/Gamma_hist_forYingjie.root");
	//TFile *f = new TFile("DataMaker/Gamma_hist_Sys_forYingjie.root");
	TH1F *InputNumberGamma=(TH1F *)f->Get("hnTotalyCut");
	TH1F *EleNumberGamma=(TH1F *)f->Get("RcptPosEleSMD");
	TH1F *RcptGamma = (TH1F *)f->Get("RcptSMD");
	TH1F *RcptMeeGamma = (TH1F *)f->Get("RcptMeeSMD2");
	//TH1F *RcptMeeGamma = (TH1F *)f->Get("RcptMeeSysSMD");
	//TH1F *RcptMeeGamma = (TH1F *)f->Get("RcptMeeGptP");
	////////////////////////////////////////////////////////////////////
	//Rec. eff.
	///////////////////////////////////////////////////////////////////
	TH1F *hReceffPi0Dalitz = (TH1F*) calEffHistB(RcptMeePi0Dalitz,RcptPi0Dalitz);
	hReceffPi0Dalitz->SetName("hReceffPi0Dalitz");
	TH1F *hReceffEtaDalitz = (TH1F*) calEffHistB(RcptMeeEtaDalitz,RcptEtaDalitz);
	hReceffEtaDalitz->SetName("hReceffEtaDalitz");
	TH1F *hReceffGamma = (TH1F*) calEffHistB(RcptMeeGamma,RcptGamma);
	hReceffGamma->SetName("hReceffGamma");

	/*cc=Canvas("cc",0.12,0.06,0.15,0.06,0,1,0);
	cc->SetGrid(1,1);
	float ymin,ymax;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pi0Dalitz Rec. eff.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	RcptPi0Dalitzbg=(TH1F *)RcptPi0Dalitz->Clone();
	RcptMeePi0Dalitzbg=(TH1F *)RcptMeePi0Dalitz->Clone();
	ymin = 1e-4;
	ymax = 100;//RcptPi0Dalitz->GetMaximum()*10;
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	htmp->SetNdivisions(505,"y");
	Style(RcptPi0Dalitzbg,1,kBlack,2,22,kBlack,2.15,"psame");
	Style(RcptPi0Dalitz,1,kBlack,2,22,kRed,1.65,"hfpsame");
	Style(RcptMeePi0Dalitzbg,1,kBlack,2,23,kBlack,2.15,"psame");
	Style(RcptMeePi0Dalitz,1,kBlack,2,23,6,1.65,"hfpsame");
	lg = Legend(0.17,0.2,0.45,0.35,0.045);
	lg->AddEntry(RcptPi0Dalitzbg,"N_{rc} (Tagged e)","pl");
	lg->AddEntry(RcptMeePi0Dalitzbg,"N_{rc} (Tagged e + Partner e + Pair ee)","pl");
	lg = Legend(0.17,0.2,0.45,0.35,0.045);
	lg->AddEntry(RcptPi0Dalitz,"N_{rc} (Tagged e)","pl");
	lg->AddEntry(RcptMeePi0Dalitz,"N_{rc} (Tagged e + Partner e + Pair ee)","pl");
	tx.DrawLatex(5.5,2.0e1,"p+p @ #sqrt{s} = 200GeV");
	tx.DrawLatex(7.0,0.5e1,"#pi^{0} #rightarrow #gammae^{+}e^{-}");
	cc->SaveAs("pic/Pi0DalitzReceffND.png");
	cc->SaveAs("pic/Pi0DalitzReceffND.eps");

	cc->SetLogy(0);*/
	hReceffPi0Dalitzbg=(TH1F *)hReceffPi0Dalitz->Clone();
	/*ymin = 0;
	ymax = 1.4;
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,ymin,ymax,"p_{T} (GeV/c)","Reconstruction effciency",0.075,0.85,0.07,0.75);
	Style(hReceffPi0Dalitzbg,1,kBlack,2,8,kBlack,1.9,"psame");
	Style(hReceffPi0Dalitz,1,kBlack,2,8,kGreen+1,1.7,"psame");
	tx.DrawLatex(5.5,1.25,"p+p @ #sqrt{s} = 200GeV");
	tx.DrawLatex(7.0,1.09,"#pi^{0} #rightarrow #gammae^{+}e^{-}");
	cc->SaveAs("pic/Pi0DalitzReceff.png");
	cc->SaveAs("pic/Pi0DalitzReceff.eps");
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//EtaDalitz Rec. eff.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	cc->SetLogy(1);
	RcptEtaDalitzbg=(TH1F *)RcptEtaDalitz->Clone();
	RcptMeeEtaDalitzbg=(TH1F *)RcptMeeEtaDalitz->Clone();
	ymin = 1e-5;//1e-6;
	ymax = 100;//RcptEtaDalitz->GetMaximum()*10;
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	Style(RcptEtaDalitzbg,1,kBlack,2,22,kBlack,2.15,"psame");
	Style(RcptEtaDalitz,1,kBlack,2,22,kRed,1.65,"hfpsame");
	Style(RcptMeeEtaDalitzbg,1,kBlack,2,23,kBlack,2.15,"psame");
	Style(RcptMeeEtaDalitz,1,kBlack,2,23,6,1.65,"hfpsame");
	lg = Legend(0.17,0.2,0.45,0.35,0.045);
	lg->AddEntry(RcptEtaDalitzbg,"N_{rc} (Tagged e)","pl");
	lg->AddEntry(RcptMeeEtaDalitzbg,"N_{rc} (Tagged e + Partner e + Pair ee)","pl");
	lg = Legend(0.17,0.2,0.45,0.35,0.045);
	lg->AddEntry(RcptEtaDalitz,"N_{rc} (Tagged e)","pl");
	lg->AddEntry(RcptMeeEtaDalitz,"N_{rc} (Tagged e + Partner e + Pair ee)","pl");
	//tx.DrawTextNDC(0.55,0.85,"p+p @ 200 GeV");
	tx.DrawLatex(5.5,2.0e1,"p+p @ #sqrt{s} = 200GeV");
	tx.DrawLatex(7.0,0.5e1,"#eta #rightarrow #gammae^{+}e^{-}");
	cc->SaveAs("pic/EtaDalitzReceffND.png");
	cc->SaveAs("pic/EtaDalitzReceffND.eps");

	cc->SetLogy(0);*/
	hReceffEtaDalitzbg=(TH1F *)hReceffEtaDalitz->Clone();
	/*ymin = 0;
	ymax = 1.4;
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,ymin,ymax,"p_{T} (GeV/c)","Reconstruction effciency",0.075,0.85,0.07,0.75);
	Style(hReceffEtaDalitzbg,1,kBlack,2,8,kBlack,1.9,"psame");
	Style(hReceffEtaDalitz,1,kBlack,2,8,kGreen+1,1.7,"psame");
	tx.DrawLatex(5.5,1.25,"p+p @ #sqrt{s} = 200GeV");
	tx.DrawLatex(7.0,1.09,"#eta #rightarrow #gammae^{+}e^{-}");
	cc->SaveAs("pic/EtaDalitzReceff.png");
	cc->SaveAs("pic/EtaDalitzReceff.eps");
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//Gamma Rec. eff.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	cc->SetLogy(1);
	RcptGammabg=(TH1F *)RcptGamma->Clone();
	RcptMeeGammabg=(TH1F *)RcptMeeGamma->Clone();
	ymin = 1e-5;
	ymax = 100;//RcptGamma->GetMaximum()*50;
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,ymin,ymax,"p_{T} (GeV/c)","Counts",0.075,0.85,0.07,0.85);
	Style(RcptGammabg,1,kBlack,2,22,kBlack,2.15,"psame");
	Style(RcptGamma,1,kBlack,2,22,kRed,1.65,"hfpsame");
	Style(RcptMeeGammabg,1,kBlack,2,23,kBlack,2.15,"psame");
	Style(RcptMeeGamma,1,kBlack,2,23,6,1.65,"hfpsame");
	lg = Legend(0.17,0.2,0.45,0.35,0.045);
	lg->AddEntry(RcptGammabg,"N_{rc} (Tagged e)","pl");
	lg->AddEntry(RcptMeeGammabg,"N_{rc} (Tagged e + Partner e + Pair ee)","pl");
	lg = Legend(0.17,0.2,0.45,0.35,0.045);
	lg->AddEntry(RcptGamma,"N_{rc} (Tagged e)","pl");
	lg->AddEntry(RcptMeeGamma,"N_{rc} (Tagged e + Partner e + Pair ee)","pl");
	//tx.DrawTextNDC(0.41,0.85,"p+p @ 200 GeV");
	tx.DrawLatex(5.,2.0e1,"p+p @ #sqrt{s} = 200GeV");
	tx.SetTextSize(0.065);
	tx.DrawLatex(4.2,3.0,"#gamma conversion + direct #gamma #rightarrow e^{+}e^{-}");
	cc->SaveAs("pic/GammaReceffND.png");
	cc->SaveAs("pic/GammaReceffND.eps");

	cc->SetLogy(0);*/
	hReceffGammabg=(TH1F *)hReceffGamma->Clone();
	/*ymin = 0;
	ymax = 1.4;
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,ymin,ymax,"p_{T} (GeV/c)","Reconstruction effciency",0.075,0.85,0.07,0.75);
	Style(hReceffGammabg,1,kBlack,2,8,kBlack,1.9,"psame");
	Style(hReceffGamma,1,kBlack,2,8,kGreen+1,1.7,"psame");
	tx.DrawLatex(5.,1.25,"p+p @ #sqrt{s} = 200GeV");
	tx.DrawLatex(4.2,1.09,"#gamma conversion + direct #gamma #rightarrow e^{+}e^{-}");
	cc->SaveAs("pic/GammaReceff.png");
	cc->SaveAs("pic/GammaReceff.eps");*/

	////////////////////////////////////////////////////////////////////
	//Rec. eff. Con
	///////////////////////////////////////////////////////////////////
	EleNumberPi0Dalitz->Sumw2();
	EleNumberEtaDalitz->Sumw2();
	EleNumberGamma->Sumw2();
	EleNumberPi0Dalitz->Scale(1.0/InputNumberPi0Dalitz->GetEntries());
	EleNumberEtaDalitz->Scale(1.0/InputNumberEtaDalitz->GetEntries());
	EleNumberGamma->Scale(1.0/InputNumberGamma->GetEntries());

	TH1F *EleNumber=(TH1F *)EleNumberPi0Dalitz->Clone();
	EleNumber->Sumw2();
	EleNumber->Add(EleNumberEtaDalitz,1);
	EleNumber->Add(EleNumberGamma,1);
    EleNumberGamma->Print("ALL");
	EleNumber->Print("ALL");
	TH1F *hPi0DalitzCon = (TH1F*) EleNumberPi0Dalitz->Clone("hPi0DalitzCon");
	hPi0DalitzCon->Divide(EleNumber);
	hPi0DalitzCon->Print("ALL");
	TH1F *hEtaDalitzCon = (TH1F*) EleNumberEtaDalitz->Clone("hEtaDalitzCon");
	hEtaDalitzCon->Divide(EleNumber);
	TH1F *hGammaCon = (TH1F*) EleNumberGamma->Clone("hGammaCon");
	hGammaCon->Divide(EleNumber);
	hGammaCon->Print("ALL");

	TCanvas *c=Canvas("c",0.15,0.03,0.15,0.06,0,0,0);
	c->SetGrid(1,1);
	/*c->SetLogy(1);
	EleNumberGammabg=(TH1F *)EleNumberGamma->Clone();
	EleNumberPi0Dalitzbg=(TH1F *)EleNumberPi0Dalitz->Clone();
	EleNumberEtaDalitzbg=(TH1F *)EleNumberEtaDalitz->Clone();
	ymin = 1e-14;
	ymax = 1e-4;//EleNumberGamma->GetMaximum()*100;
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,ymin,ymax,"p_{T} (GeV/c)","#frac{1}{2#pip_{T}}#frac{d^{2}N}{dp_{T}dy} [(GeV/c)^{-2}]",0.075,0.8,0.06,1.35);
	htmp->SetNdivisions(505,"y");
	Style(EleNumberGammabg,1,1,2,22,1,2.15,"psame");
	Style(EleNumberGamma,1,1,2,22,kRed,1.65,"hfpsame");
	Style(EleNumberPi0Dalitzbg,1,1,2,8,1,1.9,"psame");
	Style(EleNumberPi0Dalitz,1,1,2,8,kGreen+1,1.4,"hfpsame");
	Style(EleNumberEtaDalitzbg,1,1,2,23,1,2.15,"psame");
	Style(EleNumberEtaDalitz,1,1,2,23,kBlue+1,1.65,"hfpsame");

	lg= Legend(0.4,0.65,0.75,0.83,0.055);
	lg->AddEntry(EleNumberGammabg,"#gamma conversion + direct #gamma #rightarrow e^{+}e^{-}","pl");
	lg->AddEntry(EleNumberPi0Dalitzbg,"#pi^{0} #rightarrow #gammae^{+}e^{-}","pl");
	lg->AddEntry(EleNumberEtaDalitzbg,"#eta #rightarrow #gammae^{+}e^{-}","pl");
	lg= Legend(0.4,0.65,0.75,0.83,0.055);
	lg->AddEntry(EleNumberGamma,"#gamma conversion + direct #gamma #rightarrow e^{+}e^{-}","pl");
	lg->AddEntry(EleNumberPi0Dalitz,"#pi^{0} #rightarrow #gammae^{+}e^{-}","pl");
	lg->AddEntry(EleNumberEtaDalitz,"#eta #rightarrow #gammae^{+}e^{-}","pl");
	tx.DrawLatex(5.3,1.0e-5,"p+p @ #sqrt{s} = 200GeV");
	c->SaveAs("pic/ReceffConND.png");
	c->SaveAs("pic/ReceffConND.eps");

	c->SetLogy(0);
	hGammaConbg=(TH1F *)hGammaCon->Clone();
	hPi0DalitzConbg=(TH1F *)hPi0DalitzCon->Clone();
	hEtaDalitzConbg=(TH1F *)hEtaDalitzCon->Clone();
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,0.,1.0,"p_{T} (GeV/c)","Relative Contribution",0.075,0.85,0.075,0.75);
	//Style(heffbg[k],1,1,3,8,1,1.9,"psame");
	htmp->SetNdivisions(505,"y");
	Style(hGammaConbg,1,1,2,22,1,2.5,"psame");
	Style(hGammaCon,1,1,2,22,kRed,1.9,"psame");
	Style(hPi0DalitzConbg,1,1,2,8,1,2.3,"psame");
	Style(hPi0DalitzCon,1,1,2,8,kGreen+1,1.7,"psame");
	Style(hEtaDalitzConbg,1,1,2,23,1,2.5,"psame");
	Style(hEtaDalitzCon,1,1,2,23,kBlue+1,1.9,"psame");
	lg= Legend(0.4,0.4,0.7,0.62,0.055);
	lg->AddEntry(hGammaConbg,"#gamma conversion + direct #gamma #rightarrow e^{+}e^{-}","pl");
	lg->AddEntry(hPi0DalitzConbg,"#pi^{0} #rightarrow #gammae^{+}e^{-}","pl");
	lg->AddEntry(hEtaDalitzConbg,"#eta #rightarrow #gammae^{+}e^{-}","pl");
	lg= Legend(0.4,0.4,0.7,0.62,0.055);
	lg->AddEntry(hGammaCon,"#gamma conversion + direct #gamma #rightarrow e^{+}e^{-}","pl");
	lg->AddEntry(hPi0DalitzCon,"#pi^{0} #rightarrow #gammae^{+}e^{-}","pl");
	lg->AddEntry(hEtaDalitzCon,"#eta #rightarrow #gammae^{+}e^{-}","pl");
	tx.DrawLatex(5.5,0.89,"p+p @ #sqrt{s} = 200GeV");
	c->SaveAs("pic/ReceffCon.png");
	c->SaveAs("pic/ReceffCon.eps");*/

	TH1F *heff=(TH1F *)hReceffPi0Dalitz->Clone("heff");
	for(int i=0;i<nPtBins;i++){
		heff->SetBinContent(i+1,hReceffGamma->GetBinContent(i+1)*hGammaCon->GetBinContent(i+1)+hReceffPi0Dalitz->GetBinContent(i+1)*hPi0DalitzCon->GetBinContent(i+1)+hReceffEtaDalitz->GetBinContent(i+1)*hEtaDalitzCon->GetBinContent(i+1));
		heff->SetBinError(i+1,sqrt(pow(hReceffGamma->GetBinError(i+1)*hGammaCon->GetBinContent(i+1),2)+pow(hReceffPi0Dalitz->GetBinError(i+1)*hPi0DalitzCon->GetBinContent(i+1),2)+pow(hReceffEtaDalitz->GetBinError(i+1)*hEtaDalitzCon->GetBinContent(i+1),2)));
	}
	TH1F *heffbg=(TH1F *)heff->Clone();
	heff->Print("ALL");
	htmp=histo2D("htmp",20,PtMinhtmp[0],12,20,0,1.4,"p_{T} (GeV/c)","Reconstruction effciency",0.075,0.85,0.07,0.75);
	//htmp->SetNdivisions(505,"y");
	Style(hReceffGammabg,1,1,2,22,1,2.1,"psame");
	Style(hReceffGamma,1,1,2,22,kRed,1.7,"plsame");
	Style(hReceffPi0Dalitzbg,1,1,2,8,1,1.85,"psame");
	Style(hReceffPi0Dalitz,1,1,2,8,kGreen+1,1.6,"psame");
	Style(hReceffEtaDalitzbg,1,1,2,23,1,2.1,"psame");
	Style(hReceffEtaDalitz,1,1,2,23,kBlue,1.7,"plsame");
	Style(heffbg,1,1,2,21,1,1.8,"psame");
	Style(heff,1,1,2,21,kOrange+1,1.5,"plsame");

	TF1 *fun = new TF1("feff","[0]/(exp(-(x-[1])/[2])+1)+[3]",PtMin[0],11.5);
	fun->SetParameters(1.004,-0.01253,2.158,-0.4732);
	heff->Fit(fun,"N0RIS","",PtMin[0],11.5);
	//heff->Fit(fun,"N0RIS","",4,PtMax[0]);
	const double *par,*parerr;
	par = fun->GetParameters();
	parerr = fun->GetParErrors();

	fun->SetParameters(par[0],par[1],par[2],par[3]);
	heff->Fit(fun,"N0RIS","",PtMin[0],11.5);
	//heff->Fit(fun,"N0RIS","",4,PtMax[0]);
	TFitResultPtr fitr = heff->Fit(fun,"N0RIS","",PtMin[0],11.5);
	TH1D *Funcerr = new TH1D("Funcerr","",900,PtMin[0],11.5);
	for(int i=0;i<900;i++){
		double PTerr=0.005;
		double PT=i*0.01+PTerr+2.5;
		double Y=fun->Eval(PT);
		double Tpperr = fun->IntegralError(PT-PTerr,PT+PTerr,fitr->GetParams(),fitr->GetCovarianceMatrix().GetMatrixArray())/(PTerr*2.);
		Funcerr->SetBinContent(i+1,Y);
		Funcerr->SetBinError(i+1,Tpperr);
	}
	Funcerr->SetFillColor(kYellow+1);
	Style(Funcerr,1,kYellow+1,2,0,kYellow+1,1.4,"E4same");
	StyleFun(fun,1,1,4,8,6,1.44,"lsame");	
	fun->SetRange(PtMin[0],11.5);
	char chh1[50],chh2[50],chh3[50],chh4[50],chh5[50];

	sprintf(chh1,"#chi^{2} / ndf = %6.2f / %d",fun->GetChisquare(),fun->GetNDF());
	sprintf(chh2,"p_{0} = %5.3e #pm %4.2e",fun->GetParameter(0),fun->GetParError(0));
	sprintf(chh3,"p_{1} = %5.3f #pm %5.3f",fun->GetParameter(1),fun->GetParError(1));
	sprintf(chh4,"p_{2} = %5.3f #pm %5.3f",fun->GetParameter(2),fun->GetParError(2));
	sprintf(chh5,"p_{3} = %5.3f #pm %5.3f",fun->GetParameter(3),fun->GetParError(3));
	TPaveStats *ptstats;
	ptstats= new TPaveStats(0.7,0.17,0.97,0.4,"brNDC");
	ptstats->SetName("stats");
	ptstats->SetBorderSize(2);
	ptstats->SetFillColor(10);
	ptstats->SetTextAlign(12);
	ptstats->SetTextSize(0.03);
	ptstats->SetTextFont(42);
	TText *text = ptstats->AddText(chh1);
	text = ptstats->AddText(chh2);
	text = ptstats->AddText(chh3);
	text = ptstats->AddText(chh4);
	text = ptstats->AddText(chh5);
	ptstats->Draw();

	lg= Legend(0.2,0.58,0.64,0.83,0.05);
	lg->AddEntry(hReceffGammabg,"#gamma conversion + direct #gamma #rightarrow e^{+}e^{-}","pl");
	lg->AddEntry(hReceffPi0Dalitzbg,"#pi^{0} #rightarrow #gammae^{+}e^{-}","pl");
	lg->AddEntry(hReceffEtaDalitzbg,"#eta #rightarrow #gammae^{+}e^{-}","pl");
	lg->AddEntry(heffbg,"Combined","pl");
	lg->AddEntry(Funcerr,"Fitting uncertainty","f");
	lg= Legend(0.2,0.58,0.64,0.83,0.05);
	lg->AddEntry(hReceffGamma,"#gamma conversion + direct #gamma #rightarrow e^{+}e^{-}","pl");
	lg->AddEntry(hReceffPi0Dalitz,"#pi^{0} #rightarrow #gammae^{+}e^{-}","pl");
	lg->AddEntry(hReceffEtaDalitz,"#eta #rightarrow #gammae^{+}e^{-}","pl");
	lg->AddEntry(heff,"Combined","pl");
	lg->AddEntry(Funcerr,"Fitting uncertainty","f");
	lg= Legend(0.37,0.2,0.69,0.35,0.045);
	lg->AddEntry(fun,"Fit to Combined","l");
	lg->AddEntry(fun,"p_{0}/(e^{-(p_{T}-p_{1})/p_{2}}+1)+p_{3}","");
	//tx.SetTextSize(0.07);
	tx.DrawLatex(2.35,1.26,"p+p @ #sqrt{s} = 200GeV");
	c->SaveAs("pic/ReceffforYingjie.png");
	c->SaveAs("pic/ReceffforYingjie.eps");
	TH1F *hefffun=(TH1F *)heff->Clone("hefffun");
	TH1F *hefffunSysUnc=(TH1F *)heff->Clone("hefffunSysUnc");

	for(int i=0;i<nPtBins-1;i++){
		hefffun->SetBinContent(i+1,fun->Eval(0.5*(ptbinfyj[i+1]+ptbinfyj[i])));
		hefffun->SetBinError(i+1,0.0);//heff->GetBinError(i+1));
		hefffunSysUnc->SetBinContent(i+1,fun->Eval(0.5*(ptbinfyj[i+1]+ptbinfyj[i]))+Funcerr->GetBinError(Funcerr->FindBin(0.5*(ptbinfyj[i+1]+ptbinfyj[i])+1e-6)));
		hefffunSysUnc->SetBinError(i+1,0);//becasue fit uncertainty includes the systermatic uncertaintyheffw->GetBinError(i+1));
	}
	hefffun->Print("ALL");
		f=new TFile("effroot/PHEReceffSysforYingjie.root");
		TH1F *hReceffG=(TH1F *)f->Get("ReceffG");
		TH1F *hReceffE=(TH1F *)f->Get("ReceffE");
		TH1F *hReceffP=(TH1F *)f->Get("ReceffP");
		TH1F *hReceffEBR=(TH1F *)f->Get("ReceffEBR");
		TH1F *hReceffPBR=(TH1F *)f->Get("ReceffPBR");
		TH1F *hReceff=(TH1F *)heff->Clone("Receff");
		for(int i=0;i<hReceff->GetNbinsX();i++){
			hReceff->SetBinContent(i+1,hefffun->GetBinContent(i+1));
			hReceff->SetBinError(i+1,sqrt(pow(hefffunSysUnc->GetBinContent(i+1)-hefffun->GetBinContent(i+1),2)+pow(hReceffG->GetBinContent(i+1)-hefffun->GetBinContent(i+1),2)+pow(hReceffP->GetBinContent(i+1)-hefffun->GetBinContent(i+1),2)+pow(hReceffE->GetBinContent(i+1)-hefffun->GetBinContent(i+1),2)+pow(hReceffPBR->GetBinContent(i+1)-hefffun->GetBinContent(i+1),2)+pow(hReceffEBR->GetBinContent(i+1)-hefffun->GetBinContent(i+1),2)+pow(hefffun->GetBinContent(i+1)*0.05,2)));
		}
	//hReceffEtaDalitz->Print("ALL");
	//heff->SetName("ReceffMassSys");
	//hefffun->SetName("ReceffGptSys");
	/*TFile* file = new TFile("effroot/PHEReceffforYingjie.root","UPDATE");
	//TFile* file = new TFile("effroot/PHEReceffgptforYingjie.root","RECREATE");
	file->cd();
	//hReceffPi0Dalitz->Write();
	//hReceffEtaDalitz->Write();
	//hReceffGamma->Write();
	//heff->Write();
	//hefffun->Write();
	hReceff->Write();
	//hefffunSysUnc->Write();
	file->Close();*/
	//hefffun->SetName("ReceffG");
	//hefffun->SetName("ReceffP");
	//hefffun->SetName("ReceffPBR");
	//hefffun->SetName("ReceffE");
	hefffun->SetName("ReceffEBR");
	TFile* file = new TFile("effroot/PHEReceffSysforYingjie.root","UPDATE");
	file->cd();
	hefffun->Write();
	file->Close();
}
