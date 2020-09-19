#include "../ptbin.h"
#include "../style.h"
#include "../draw_sys.C"
#include "../draw_syspp.C"
#include "../CrossSection/binning_shift.h"
void plotHFe()
{
	setstyle();
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetTextFont(42);
	tx.SetNDC();
	TFile *f;
	TH2F *htmp;
	f=new TFile("../Background/rootfile/BackgroundSpectrum.root");
	TH1F *hJPsi=(TH1F *)f->Get("JpsiElectron");
	TH1F *hUpsilon=(TH1F *)f->Get("UpsilonElectron");
	TH1F *hUpsilonlow=(TH1F *)f->Get("UpsilonElectronlow");
	TH1F *hUpsilonhigh=(TH1F *)f->Get("UpsilonElectronhigh");
	TH1F *hDrellYan=(TH1F *)f->Get("hDrellYanElectron");
	TH1F *hlight_vector_mesons=(TH1F *)f->Get("LvmElectron");

	TH1F *hJPsiS=new TH1F("hJPsiS","",nPtBins,ptbin);
	TH1F *hJPsiSys=new TH1F("hJPsiSys","",nPtBins,ptbin);
	for(int i=0;i<nPtBins;i++) {
		hJPsiS->SetBinContent(i+1,hJPsi->GetBinContent(hJPsi->FindBin((ptbin[i]+ptbin[i+1])/2.)));
		hJPsiS->SetBinError(i+1,0);
		hJPsiSys->SetBinContent(i+1,hJPsi->GetBinContent(hJPsi->FindBin((ptbin[i]+ptbin[i+1])/2.)));
		hJPsiSys->SetBinError(i+1,hJPsi->GetBinError(hJPsi->FindBin((ptbin[i]+ptbin[i+1])/2.)));
	}
	TH1F *hUpsilonS=new TH1F("hUpsilonS","",nPtBins,ptbin);
	TH1F *hUpsilonSys=new TH1F("hUpsilonSys","",nPtBins,ptbin);
	for(int i=0;i<nPtBins;i++) {
		hUpsilonS->SetBinContent(i+1,hUpsilon->GetBinContent(hUpsilon->FindBin((ptbin[i]+ptbin[i+1])/2.)));
		hUpsilonS->SetBinError(i+1,0);
		hUpsilonSys->SetBinContent(i+1,hUpsilon->GetBinContent(hUpsilon->FindBin((ptbin[i]+ptbin[i+1])/2.)));
		hUpsilonSys->SetBinError(i+1,hUpsilon->GetBinContent(hUpsilon->FindBin((ptbin[i]+ptbin[i+1])/2.))-hUpsilonlow->GetBinContent(hUpsilon->FindBin((ptbin[i]+ptbin[i+1])/2.)));
	}
	TH1F *hDrellYanS=new TH1F("hDrellYanS","",nPtBins,ptbin);
	TH1F *hDrellYanSys=new TH1F("hDrellYanSys","",nPtBins,ptbin);
	for(int i=0;i<nPtBins;i++) {
		hDrellYanS->SetBinContent(i+1,hDrellYan->GetBinContent(hDrellYan->FindBin((ptbin[i]+ptbin[i+1])/2.)));
		hDrellYanS->SetBinError(i+1,0);
		hDrellYanSys->SetBinContent(i+1,hDrellYan->GetBinContent(hDrellYan->FindBin((ptbin[i]+ptbin[i+1])/2.)));
		hDrellYanSys->SetBinError(i+1,hDrellYan->GetBinError(hDrellYan->FindBin((ptbin[i]+ptbin[i+1])/2.)));
	}
	TH1F *hlight_vector_mesonsS=new TH1F("hlight_vector_mesonsS","",nPtBins,ptbin);
	TH1F *hlight_vector_mesonsSys=new TH1F("hlight_vector_mesonsSys","",nPtBins,ptbin);
	for(int i=0;i<nPtBins;i++) {
		hlight_vector_mesonsS->SetBinContent(i+1,hlight_vector_mesons->GetBinContent(hlight_vector_mesons->FindBin((ptbin[i]+ptbin[i+1])/2.)));
		hlight_vector_mesonsS->SetBinError(i+1,0);
		hlight_vector_mesonsSys->SetBinContent(i+1,hlight_vector_mesons->GetBinContent(hlight_vector_mesons->FindBin((ptbin[i]+ptbin[i+1])/2.)));
		hlight_vector_mesonsSys->SetBinError(i+1,hlight_vector_mesons->GetBinError(hlight_vector_mesons->FindBin((ptbin[i]+ptbin[i+1])/2.)));
	}
	////////////////////////////////////////////////////////////////////////////////////////
	//bin shift
	///////////////////////////////////////////////////////////////////////////////////
	f=new TFile("../CrossSection/rootfile/NPE.root");
	TH1F *hNPE=(TH1F *)f->Get("hNPE");
	hNPE->Sumw2();
	hNPE->Print("ALL");
	f=new TFile("../SysUnc/rootfile/NPESys.root");
	TH1F *hSys=(TH1F *)f->Get("hSys");
	TH1F *hNPESyswobs= new TH1F("hNPESyswobs",";p_{T} (GeV/c); Sys Unc",nPtBins,ptbin);	
	for(int i=0;i<nPtBins;i++) {
		hNPESyswobs->SetBinContent(i+1,hNPE->GetBinContent(i+1));
		hNPESyswobs->SetBinError(i+1,hNPE->GetBinContent(i+1)*sqrt(pow(hSys->GetBinContent(i+1),2)+pow(0.03,2)+0.03*0.03+pow(0.0035,2)));//total, bin shift, trigger bias, Nch of trigger bias
	}
	TGraphErrors *grNPEsyswobs = new TGraphErrors(hNPESyswobs);
	TH1F *hNPEwobsbg=(TH1F *)hNPE->Clone("hNPEwobsbg");
	TCanvas *cc1=Canvas("cc1",0.14,0.04,0.15,0.06,0,1,0);
	cc1->SetGrid(1,1);
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,1e-11,1e-3,"p_{T} (GeV/c)","Ed^{3}#sigma/dp^{3} (mb GeV^{-2}c^{3})",0.075,0.85,0.07,0.98);
	Style(hNPEwobsbg,1,1,3,8,1,1.9,"plsame");
	draw_syspp(grNPEsyswobs,kYellow+1,2.5,10);
	Style(hNPE,1,1,3,8,kYellow+1,1.7,"plsame");
	tx.SetTextSize(0.07);
	tx.DrawLatex(0.48,0.86,"p+p @ #sqrt{s} = 200 GeV");
	tx.DrawLatex(0.65,0.78,"NPE");
	cc1->SaveAs("./pic/NPEwoBF.png");
	cc1->SaveAs("./pic/NPEwoBF.eps");
	//TH1F *hNPEcorr=(TH1F *)hNPE->Clone("hNPEcorr");
	TH1F *hNPEcorr=new TH1F("hNPEcorr","",nPtBins,ptbin);
	for(int i=0;i<nPtBins;i++) {
		hNPEcorr->SetBinContent(i+1,hNPE->GetBinContent(i+1)*2*TMath::Pi()*hNPE->GetBinCenter(i+1)/30.);
		hNPEcorr->SetBinError(i+1,hNPE->GetBinError(i+1)*2*TMath::Pi()*hNPE->GetBinCenter(i+1)/30.);
	}
	hNPEcorr->Print("ALL");
	
	hNPEcorrbg=(TH1F *)hNPEcorr->Clone();
	hNPEcorrbg->Print("ALL");
	TCanvas *cc=Canvas("cc",0.17,0.01,0.15,0.06,0,1,0);
	cc->SetGrid(1,1);
	//TH2F *htmp = histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],1e4,1e-8,1e-1,"p_{T} (GeV/c)","#frac{d^{2}N}{dp_{T}dy} [(GeV/c)^{-1}]",0.075,0.85,0.055,1.4);
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,1e-11,1e-4,"p_{T} (GeV/c)","#frac{d^{2}N}{dp_{T}dy} [(GeV/c)^{-1}]",0.075,0.85,0.055,1.4);
	Style(hNPEcorrbg,1,1,1,8,1,1.9,"psame");
	Style(hNPEcorr,1,1,3,8,kGreen+1,1.85,"psame");
	TF1 *fun = new TF1("fun","[0]*x*pow(exp([1]*x)+x/[2],[3])",2.5,10);
	fun->SetParameters(3.52116e+00,-5.64504e-01,3.36886e-01,-6.51479e+00);
	TF1 *fun1 = new TF1("fun1","[0]*x/pow(1+x/[1],[2])",2.5,10);
	//fun1->SetParameters(5.02232,2.81618e-002,3.66697);//2.16211,1.22296,-9.17302);
	fun1->SetParameters(2.16211,1.22296,9.17302);
	hNPEcorr->Fit(fun,"IN0R","",2.5,10);
	hNPEcorr->Fit(fun1,"IN0R","",2.5,10);
	StyleFun(fun,1,1,5,8,1,1.44,"lsame");
	StyleFun(fun1,1,kRed,5,8,1,1.44,"lsame");
	lg= Legend(0.6,0.68,0.89,0.88,0.06);
    lg->AddEntry(fun,"p_{0}*x*(e^{p_{1}*x}+x/p_{2})^{p_{3}}","l");
	lg= Legend(0.18,0.43,0.48,0.53,0.06);
    lg->AddEntry(fun1,"p_{0}*x/(1+x/p_{1})^{p_{2}}","l");
	char chh1[50],chh2[50],chh3[50],chh4[50],chh5[50];
	sprintf(chh1,"#chi^{2} / ndf = %6.2f / %d",fun->GetChisquare(),fun->GetNDF());
	sprintf(chh2,"p_{0} = %5.3f #pm %4.3f",fun->GetParameter(0),fun->GetParError(0));
	sprintf(chh3,"p_{1} = %5.3f #pm %4.3f",fun->GetParameter(1),fun->GetParError(1));
	sprintf(chh4,"p_{2} = %5.3f #pm %4.3f",fun->GetParameter(2),fun->GetParError(2));
	sprintf(chh5,"p_{3} = %5.3f #pm %4.3f",fun->GetParameter(3),fun->GetParError(3));
	TPaveStats *ptstats;
	ptstats= new TPaveStats(0.675,0.48,0.925,0.73,"brNDC");
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
	sprintf(chh1,"#chi^{2} / ndf = %6.2f / %d",fun1->GetChisquare(),fun1->GetNDF());
	sprintf(chh2,"p_{0} = %5.3f #pm %4.3f",fun1->GetParameter(0),fun1->GetParError(0));
	sprintf(chh3,"p_{1} = %5.3f #pm %4.3f",fun1->GetParameter(1),fun1->GetParError(1));
	sprintf(chh4,"p_{2} = %5.3f #pm %4.3f",fun1->GetParameter(2),fun1->GetParError(2));
	ptstats= new TPaveStats(0.2,0.18,0.45,0.42,"brNDC");
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
	ptstats->Draw();
	tx.DrawLatex(0.2,0.85,"p+p @ #sqrt{s} = 200 GeV");
	tx.SetTextSize(0.06);
	tx.DrawTextNDC(0.75,0.855,"NPE");
	cc->SaveAs("./pic/NPEforBinShiftFit.eps");
	cc->SaveAs("./pic/NPEforBinShiftFit.png");
	
	TH1F *hNPEcorrSys=(TH1F *)hNPEcorr->Clone("hNPEcorrSys");
	hNPEcorr = (TH1F*) get_bin_shift_crrection(1e7,fun,nPtBins,ptbin);
	hNPEcorrbg=(TH1F *)hNPEcorr->Clone();
	hNPEcorrSys = (TH1F*) get_bin_shift_crrection(1e7,fun1,nPtBins,ptbin);
	hNPEcorrSysbg=(TH1F *)hNPEcorrSys->Clone();
	TCanvas *c=Canvas("c",0.12,0.05,0.15,0.06,0,0,0);
	c->SetGrid(1,1);
	TH2F *htmp = histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],2,0.5,1.5,"p_{T} (GeV/c)","Bin Shift Correction",0.075,0.85,0.07,0.7);
	htmp->SetNdivisions(505,"y");
	Style(hNPEcorrSysbg,1,1,1,22,1,2.5,"psame");
	Style(hNPEcorrSys,1,1,3,22,kRed,1.9,"psame");
	Style(hNPEcorrbg,1,1,1,23,1,2.5,"psame");
	Style(hNPEcorr,1,1,3,23,kGreen+1,1.9,"psame");
	lg= Legend(0.37,0.2,0.7,0.35,0.045);
    lg->AddEntry(hNPEcorrSysbg,"estimated using p_{0}*x/(1+x/p_{1})^{p_{2}}","pl");
    lg->AddEntry(hNPEcorrbg,"estimated using p_{0}*x*(e^{p_{1}*x}+x/p_{2})^{p_{3}}","pl");
	lg= Legend(0.37,0.2,0.7,0.35,0.045);
    lg->AddEntry(hNPEcorrSys,"estimated using p_{0}*x/(1+x/p_{1})^{p_{2}}","pl");
    lg->AddEntry(hNPEcorr,"estimated using p_{0}*x*(e^{p_{1}*x}+x/p_{2})^{p_{3}}","pl");
	tx.SetTextSize(0.07);
	tx.DrawLatex(0.5,0.86,"p+p @ #sqrt{s} = 200 GeV");
	c->SaveAs("./pic/NPEforBinShiftCorr.eps");
	c->SaveAs("./pic/NPEforBinShiftCorr.png");
    hNPE->Divide(hNPEcorr);
	
	TH1F *hNPESys= new TH1F("hNPESys",";p_{T} (GeV/c); Sys Unc",nPtBins,ptbin);	
	for(int i=0;i<nPtBins;i++) {
		hNPESys->SetBinContent(i+1,hNPE->GetBinContent(i+1));
		hNPESys->SetBinError(i+1,hNPE->GetBinContent(i+1)*sqrt(pow(hSys->GetBinContent(i+1),2)+pow((hNPEcorr->GetBinContent(i+1)-hNPEcorrSys->GetBinContent(i+1))/hNPEcorrSys->GetBinContent(i+1),2)+pow(0.03,2)+0.03*0.03+pow(0.0035,2)));//total, bin shift, trigger bias, Nch of trigger bias, good event fraction sys
	}
	TGraphErrors *grNPEsys = new TGraphErrors(hNPESys);
	TH1F *hNPEbg=(TH1F *)hNPE->Clone("hNPEbg");
	TCanvas *c1=Canvas("c1",0.14,0.04,0.15,0.06,0,1,0);
	c1->SetGrid(1,1);
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,1e-11,1e-3,"p_{T} (GeV/c)","Ed^{3}#sigma/dp^{3} (mb GeV^{-2}c^{3})",0.075,0.85,0.07,0.98);
	Style(hNPEbg,1,1,3,8,1,1.9,"plsame");
	draw_syspp(grNPEsys,kYellow+1,2.5,10);
	Style(hNPE,1,1,3,8,kYellow+1,1.7,"plsame");
	tx.SetTextSize(0.07);
	tx.DrawLatex(0.48,0.86,"p+p @ #sqrt{s} = 200 GeV");
	tx.DrawLatex(0.65,0.78,"NPE");
	c1->SaveAs("./pic/NPE.png");
	c1->SaveAs("./pic/NPE.eps");
	
	TH1F *hRatioHNPE=(TH1F *)hJPsiS->Clone("hRatioHNPE");
	hRatioHNPE->Sumw2();
	hRatioHNPE->Add(hUpsilonS,1);
	hRatioHNPE->Add(hDrellYanS,1);
	hRatioHNPE->Add(hlight_vector_mesonsS,1);
	hRatioHNPE->Divide(hNPE);
	TH1F *hRatioHNPESys=(TH1F *)hJPsiSys->Clone("hRatioHNPESys");
	hRatioHNPESys->Sumw2();
	hRatioHNPESys->Add(hUpsilonSys,1);
	hRatioHNPESys->Add(hDrellYanSys,1);
	hRatioHNPESys->Add(hlight_vector_mesonsSys,1);
	hRatioHNPESys->Divide(hNPESys);
	TGraphErrors *grRatioHNPEsys = new TGraphErrors(hRatioHNPESys);
	TH1F *hRatioHNPEbg=(TH1F *)hRatioHNPE->Clone("hRatioHNPEbg");
	TCanvas *c6=Canvas("c6",0.14,0.04,0.15,0.06,0,0,0);
	c6->SetGrid(1,1);
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,0,0.2,"p_{T} (GeV/c)","HDE/NPE",0.075,0.85,0.07,0.98);
	Style(hRatioHNPEbg,1,1,3,8,1,1.9,"plsame");
	draw_syspp(grRatioHNPEsys,kYellow+1,2.5,10);
	Style(hRatioHNPE,1,1,3,8,kYellow+1,1.7,"plsame");
	tx.DrawLatex(0.5,0.86,"p+p @ #sqrt{s} = 200 GeV");
	c6->SaveAs("./pic/HadronContribution.png");
	c6->SaveAs("./pic/HadronContribution.eps");

	TH1F *hHFE=(TH1F *)hNPE->Clone("hHFE");
	hHFE->Sumw2();
	hHFE->Add(hJPsiS,-1);
	hHFE->Add(hUpsilonS,-1);
	hHFE->Add(hDrellYanS,-1);
	hHFE->Add(hlight_vector_mesonsS,-1);
	TH1F *hHFESys=(TH1F *)hNPESys->Clone("hHFESys");
	hHFESys->Sumw2();
	hHFESys->Add(hJPsiSys,-1);
	hHFESys->Add(hUpsilonSys,-1);
	hHFESys->Add(hDrellYanSys,-1);
	hHFESys->Add(hlight_vector_mesonsSys,-1);
	TGraphErrors *grHFEsys = new TGraphErrors(hHFESys);
	TH1F *hHFEbg=(TH1F *)hHFE->Clone("hHFEbg");
	
	TFile* file = new TFile("rootfile/NPEBinShift.root","RECREATE");
	file->cd();
	hNPE->Write();
	hNPESys->Write();
	hHFE->Write();
	hHFESys->Write();
	file->Close();
	/////////////////////////////////////////////////////////////////////////////
	//NPE
	/////////////////////////////////////////////////////////////////////////////
	TFile *f = new TFile("../CrossSection/DataMaker/fonll200gev.root");
	TGraphErrors *grc =(TGraphErrors *)f->Get("gFONLLc");
	TGraphErrors *grl =(TGraphErrors *)f->Get("gFONLLl");
	TGraphErrors *gru =(TGraphErrors *)f->Get("gFONLLu");

	TCanvas *c4=Canvas("c4",0.14,0.04,0.15,0.06,0,1,0);
	c4->SetGrid(1,1);
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,1e-11,1e-3,"p_{T} (GeV/c)","Ed^{3}#sigma/dp^{3} (mb GeV^{-2}c^{3})",0.075,0.85,0.07,0.98);
	StyleTGraph(gru,1,1,4,8,1,1.9,"lsame");
	StyleTGraph(grc,2,1,4,8,1,1.9,"lsame");
	StyleTGraph(grl,3,1,4,8,1,1.9,"lsame");
	Style(hHFEbg,1,1,3,8,1,1.9,"plsame");
	draw_syspp(grHFEsys,kYellow+1,2.5,10);
	Style(hHFE,1,1,3,8,kYellow+1,1.7,"plsame");
	lg= Legend(0.43,0.7,0.8,0.92,0.045);
	lg->AddEntry(hHFEbg,"High p_{T} HFE 2012 STAR,|y|<0.7","pl");
	lg->AddEntry(gru,"FONLL (upper limit)","l");
	lg->AddEntry(grc,"FONLL","l");
	lg->AddEntry(grl,"FONLL (lower limit)","l");
	lg= Legend(0.43,0.7,0.8,0.92,0.045);
	lg->AddEntry(hHFE,"High p_{T} HFE 2012 STAR,|y|<0.7","pl");
	lg->AddEntry(gru,"FONLL (upper limit)","l");
	lg->AddEntry(grc,"FONLL","l");
	lg->AddEntry(grl,"FONLL (lower limit)","l");
	tx.DrawLatex(0.17,0.2,"p+p @ #sqrt{s} = 200 GeV");
	c4->SaveAs("./pic/HFe.png");
	c4->SaveAs("./pic/HFe.eps");
	/////////////////////////////////////////////////////////////////////////////////////
	//phenix and star publised data
	////////////////////////////////////////////////////////////////////////////////////
	/////////////////////
	//NPE2008
	////////////////////
	Double_t x08[9],x08err[9],y08[9],y08staterr[9],y08syserr[9],xl08[9],xr08[9],eyl08[9],eyh08[9];
	ifstream indata("../CrossSection/DataMaker/NPE_Run08.dat");
	for(int i=0;i<9;i++) indata>>x08[i]>>y08[i]>>y08staterr[i]>>y08syserr[i];
	indata.close();
	Double_t x08jpsi[11],x08jpsierr[11],y08jpsi[11],y08jpsistaterr[11],y08jpsisyserr[11],xl08jpsi[11],xr08jpsi[11],eyl08jpsi[11],eyh08jpsi[11];
	ifstream indatajpsi("../CrossSection/DataMaker/Background_JPsi.txt");
	for(int i=0;i<11;i++) indatajpsi>>x08jpsi[i]>>y08jpsi[i]>>y08jpsisyserr[i];
	indatajpsi.close();
	Double_t x08upsilon[11],x08upsilonerr[11],y08upsilon[11],y08upsilonstaterr[11],y08upsilonsyserr[11],xl08upsilon[11],xr08upsilon[11],eyl08upsilon[11],eyh08upsilon[11];
	ifstream indataupsilon("../CrossSection/DataMaker/Background_Upsilon.txt");
	for(int i=0;i<11;i++) indataupsilon>>x08upsilon[i]>>y08upsilon[i]>>y08upsilonsyserr[i];
	indataupsilon.close();
	Double_t x08lvm[11],x08lvmerr[11],y08lvm[11],y08lvmstaterr[11],y08lvmsyserr[11],xl08lvm[11],xr08lvm[11],eyl08lvm[11],eyh08lvm[11];
	ifstream indatalvm("../CrossSection/DataMaker/Background_light_vector_mesons.txt");
	for(int i=0;i<11;i++) indatalvm>>x08lvm[i]>>y08lvm[i]>>y08lvmsyserr[i];
	indatalvm.close();
	for(int i=7;i<9;i++){
		if(i==7){
			y08jpsi[i]=(y08jpsi[i]+y08jpsi[i+1])/2.;
			y08jpsisyserr[i]=sqrt(pow(y08jpsisyserr[i],2)+pow(y08jpsisyserr[i+1],2))/2.;
			y08upsilon[i]=(y08upsilon[i]+y08upsilon[i+1])/2.;
			y08upsilonsyserr[i]=sqrt(pow(y08upsilonsyserr[i],2)+pow(y08upsilonsyserr[i+1],2))/2.;
			y08lvm[i]=(y08lvm[i]+y08lvm[i+1])/2.;
			y08lvmsyserr[i]=sqrt(pow(y08lvmsyserr[i],2)+pow(y08lvmsyserr[i+1],2))/2.;
		}
		else{
			y08jpsi[i]=(y08jpsi[i+1]+y08jpsi[i+2])/2.;
			y08jpsisyserr[i]=sqrt(pow(y08jpsisyserr[i+1],2)+pow(y08jpsisyserr[i+2],2))/2.;
			y08upsilon[i]=(y08upsilon[i+1]+y08upsilon[i+2])/2.;
			y08upsilonsyserr[i]=sqrt(pow(y08upsilonsyserr[i+1],2)+pow(y08upsilonsyserr[i+2],2))/2.;
			y08lvm[i]=(y08lvm[i+1]+y08lvm[i+2])/2.;
			y08lvmsyserr[i]=sqrt(pow(y08lvmsyserr[i+1],2)+pow(y08lvmsyserr[i+2],2))/2.;
		}
	}
	Double_t x08dy[10],x08dyerr[10],y08dy[10],y08dystaterr[10],y08dysyserr[10],xl08dy[10],xr08dy[10],eyl08dy[10],eyh08dy[10];
	ifstream indatady("../CrossSection/DataMaker/Background_DrellYan.txt");
	for(int i=0;i<10;i++) indatady>>x08dy[i]>>y08dy[i]>>y08dysyserr[i];
	indatady.close();
	for(int i=0;i<9;i++){
		if(i<7){
			y08dy[i]=(y08dy[i]+y08dy[i+1])/2.;
			y08dysyserr[i]=sqrt(pow(y08dysyserr[i],2)+pow(y08dysyserr[i+1],2))/2.;
		}
		else{
			y08dy[i]=y08dy[i+1];
			y08dysyserr[i]=y08dysyserr[i+1];
		}
	}
	for(int i=0;i<9;i++){
		x08err[i]=(x08[i+1]-x08[i])/2.;
		y08[i]=y08[i]-y08jpsi[i]-y08upsilon[i]-y08dy[i];
		y08syserr[i]=sqrt(pow(y08syserr[i],2)+pow(y08jpsisyserr[i],2)+pow(y08upsilonsyserr[i],2)+pow(y08dysyserr[i],2));
		//y08[i]=y08[i]-y08jpsi[i]-y08upsilon[i]-y08lvm[i]-y08dy[i];
		//y08syserr[i]=sqrt(pow(y08syserr[i],2)+pow(y08jpsisyserr[i],2)+pow(y08upsilonsyserr[i],2)+pow(y08lvmsyserr[i],2)+pow(y08dysyserr[i],2));
	cout<<"08"<<x08[i]<<" "<<y08[i]<<" "<<y08jpsi[i]<<" "<<y08upsilon[i]<<" "<<y08lvm[i]<<" "<<y08dy[i]<<endl;
	}
	TGraphErrors *gr08=new TGraphErrors(9,x08,y08,x08err,y08staterr);
	TGraphErrors *gr08bg=new TGraphErrors(9,x08,y08,x08err,y08staterr);
	TGraphErrors *gr08sys=new TGraphErrors(9,x08,y08,x08err,y08syserr);
	/////////////////////////
	//npePHENIX
	////////////////////////
	Double_t x[28],xerr[28],y[28],yphenixstaterr[28],yphenixsyserr[28];
	ifstream indata1("../CrossSection/DataMaker/phenixresult.dat");
	for(int i=0;i<28;i++) indata1>>x[i]>>y[i]>>yphenixstaterr[i]>>yphenixsyserr[i];
	indata1.close();
	for(int i=0;i<28;i++) xerr[i]=(x[i+1]-x[i])/2.;
	TGraphErrors *grphenix=new TGraphErrors(28,x,y,xerr,yphenixstaterr);
	TGraphErrors *grphenixbg=new TGraphErrors(28,x,y,xerr,yphenixstaterr);
	TGraphErrors *grphenixsys=new TGraphErrors(28,x,y,xerr,yphenixsyserr);

	TCanvas *ccc=Canvas("ccc",0.14,0.036,0.15,0.06,0,1,0);
	//ccc->SetGrid(1,1);
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,1e-11,1e-3,"p_{T} (GeV/c)","Ed^{3}#sigma/dp^{3} (mb GeV^{-2}c^{3})",0.075,0.85,0.07,0.98);
	StyleTGraph(gru,1,1,4,8,1,1.9,"lsame");
	StyleTGraph(grc,2,1,4,8,1,1.9,"lsame");
	StyleTGraph(grl,3,1,4,8,1,1.9,"lsame");
	StyleTGraph(grphenixbg,1,1,2,22,1,2.3,"psame");
	draw_syspp(grphenixsys,kMagenta+1,2.0,10);
	StyleTGraph(grphenix,1,kMagenta+1,2,22,kMagenta+1,1.9,"psame");
	StyleTGraph(gr08bg,1,1,2,23,1,2.3,"psame");
	draw_syspp(gr08sys,kGreen-1,2.5,10);
	StyleTGraph(gr08,1,kGreen-1,2,23,kGreen-1,1.9,"psame");
	Style(hHFEbg,1,1,2,8,1,1.9,"psame");
	draw_syspp(grHFEsys,kYellow+2,2.5,10);
	Style(hHFE,1,kYellow+2,2,8,kYellow+2,1.7,"psame");
	lg= Legend(0.45,0.5,0.76,0.82,0.04);
	lg->AddEntry(hHFEbg,"eHF 2012 STAR,|y|<0.7","pl");
	lg->AddEntry(grphenixbg,"eHF PHENIX 2005,|y|<0.35","pl");
	lg->AddEntry(gr08bg,"eHF 2008 STAR published,|y|<0.5","pl");
	lg->AddEntry(gru,"FONLL (upper limit)","l");
	lg->AddEntry(grc,"FONLL","l");
	lg->AddEntry(grl,"FONLL (lower limit)","l");
	lg= Legend(0.45,0.5,0.76,0.82,0.04);
	lg->AddEntry(hHFE,"eHF 2012 STAR,|y|<0.7","pl");
	lg->AddEntry(grphenix,"eHF PHENIX 2005,|y|<0.35","pl");
	lg->AddEntry(gr08,"eHF 2008 STAR published,|y|<0.5","pl");
	lg->AddEntry(gru,"FONLL (upper limit)","l");
	lg->AddEntry(grc,"FONLL","l");
	lg->AddEntry(grl,"FONLL (lower limit)","l");
	tx.SetTextSize(0.07);
	tx.DrawLatex(0.47,0.86,"p+p @ #sqrt{s} = 200 GeV");
	tx.SetTextSize(0.065);
	tx.DrawLatex(0.16,0.86,"(a)");
	ccc->SaveAs("./pic/HFeCompared.png");
	ccc->SaveAs("./pic/HFeCompared.eps");
	/////////////////////////////////////////////////////////////////////////////////////
	//phenix and star publised data/fonll
	////////////////////////////////////////////////////////////////////////////////////
	f=new TFile("../CrossSection/rootfile/NPEBinShiftEMC.root");
	TH1F *hHFEEMC=(TH1F *)f->Get("hHFE");
	TH1F *hHFEEMCSys=(TH1F *)f->Get("hHFESys");
	double ptHigh[nPtBins],all12High[nPtBins],ratio12High[nPtBins],ratio12Higherr[nPtBins],ratio12Highsyserr[nPtBins];
	double ptHighEMC[nPtBins],all12HighEMC[nPtBins],ratio12HighEMC[nPtBins],ratio12HighEMCerr[nPtBins],ratio12HighEMCsyserr[nPtBins];
	for(int i=0;i<nPtBins;i++)
	{
		ptHigh[i] = (ptbin[i]+ptbin[i+1])/2;
		all12High[i] = grc->Eval(ptHigh[i]);
		ratio12High[i] = hHFE->GetBinContent(i+1)/all12High[i];
		ratio12Higherr[i] = hHFE->GetBinError(i+1)/all12High[i];
		ratio12Highsyserr[i] = hHFESys->GetBinError(i+1)/all12High[i];
		ratio12HighEMC[i] = hHFEEMC->GetBinContent(i+1)/all12High[i];
		ratio12HighEMCerr[i] = hHFEEMC->GetBinError(i+1)/all12High[i];
		ratio12HighEMCsyserr[i] = hHFEEMCSys->GetBinError(i+1)/all12High[i];
	}
	TGraphErrors *grratio12Highbg=new TGraphErrors(nPtBins,ptHigh,ratio12High,0,ratio12Higherr);
	TGraphErrors *grratio12High=new TGraphErrors(nPtBins,ptHigh,ratio12High,0,ratio12Higherr);
	TGraphErrors *grratio12Highsys=new TGraphErrors(nPtBins,ptHigh,ratio12High,0,ratio12Highsyserr);
	TGraphErrors *grratio12HighEMCbg=new TGraphErrors(nPtBins,ptHigh,ratio12HighEMC,0,ratio12HighEMCerr);
	TGraphErrors *grratio12HighEMC=new TGraphErrors(nPtBins,ptHigh,ratio12HighEMC,0,ratio12HighEMCerr);
	TGraphErrors *grratio12HighEMCsys=new TGraphErrors(nPtBins,ptHigh,ratio12HighEMC,0,ratio12HighEMCsyserr);

	double xtmp,allc,allup,alllow,xFONLL[152],ratioc[152],ratioup[152],ratiolow[152];
	for(int i=0;i<152;i++)
	{
		grc->GetPoint(i,xtmp,allc);
		grl->GetPoint(i,xtmp,alllow);
		gru->GetPoint(i,xtmp,allup);
		xFONLL[i]=xtmp;
		ratioc[i]=allc/allc;
		ratioup[i]=allup/allc;
		ratiolow[i]=alllow/allc;
	}
	TGraphErrors *grratioC =new TGraphErrors(152,xFONLL,ratioc,0,0);
	TGraphErrors *grratioLOW =new TGraphErrors(152,xFONLL,ratiolow,0,0);
	TGraphErrors *grratioUP =new TGraphErrors(152,xFONLL,ratioup,0,0);
	TCanvas *c5=Canvas("c5",0.12,0.06,0.15,0.06,0,0,0);
	c5->SetGrid(1,1);
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,0,4.0,"p_{T} (GeV/c)","Data/FONLL",0.075,0.85,0.07,0.78);
	htmp->SetNdivisions(505,"y");
	StyleTGraph(grratioUP,1,1,4,8,1,1.9,"lsame");
	StyleTGraph(grratioC,2,4,4,8,1,1.9,"lsame");
	StyleTGraph(grratioLOW,3,4,4,8,1,1.9,"lsame");
	StyleTGraph(grratio12Highbg,1,1,3,8,1,1.9,"psame");
	draw_syspp(grratio12Highsys,kYellow+1,2.5,10);
	StyleTGraph(grratio12High,1,1,3,8,kYellow+1,1.7,"psame");
	lg= Legend(0.42,0.7,0.8,0.9,0.045);
	lg->AddEntry(grratio12Highbg,"High p_{T} HFE 2012 STAR,|y|<0.7","pl");
	lg->AddEntry(grratioUP,"FONLL (upper limit)","l");
	lg->AddEntry(grratioC,"FONLL","l");
	lg->AddEntry(grratioLOW,"FONLL (lower limit)","l");
	lg= Legend(0.42,0.7,0.8,0.9,0.045);
	lg->AddEntry(grratio12High,"High p_{T} HFE 2012 STAR,|y|<0.7","pl");
	lg->AddEntry(grratioUP,"FONLL (upper limit)","l");
	lg->AddEntry(grratioC,"FONLL","l");
	lg->AddEntry(grratioLOW,"FONLL (lower limit)","l");
	tx.DrawLatex(0.46,0.5,"p+p @ #sqrt{s} = 200 GeV");
	c5->SaveAs("./pic/HFeoverFONLL.png");
	c5->SaveAs("./pic/HFeoverFONLL.eps");
	
	double allPHENIX[28],ratioPHENIX[28],ratioPHENIXerr[28],ratioPHENIXsyserr[28];
	for(int i=0;i<28;i++)
	{
		allPHENIX[i] = grc->Eval(x[i]);
		ratioPHENIX[i]=y[i]/allPHENIX[i];
		ratioPHENIXerr[i]=yphenixstaterr[i]/allPHENIX[i];
		ratioPHENIXsyserr[i]=yphenixsyserr[i]/allPHENIX[i];
	}
	TGraphErrors *grratioPHENIX=new TGraphErrors(28,x,ratioPHENIX,0,ratioPHENIXerr);
	TGraphErrors *grratioPHENIXbg=new TGraphErrors(28,x,ratioPHENIX,0,ratioPHENIXerr);
	TGraphErrors *grratioPHENIXsys=new TGraphErrors(28,x,ratioPHENIX,0,ratioPHENIXsyserr);

	double all08[9],ratio08[9],ratio08err[9],ratio08syserr[9];
	for(int i=0;i<9;i++)
	{
		all08[i] = grc->Eval(x08[i]);
		ratio08[i]=y08[i]/all08[i];
		ratio08err[i]=y08staterr[i]/all08[i];
		ratio08syserr[i]=y08syserr[i]/all08[i];
	}
	TGraphErrors *grratio08bg=new TGraphErrors(9,x08,ratio08,0,ratio08err);
	TGraphErrors *grratio08=new TGraphErrors(9,x08,ratio08,0,ratio08err);
	TGraphErrors *grratio08sys=new TGraphErrors(9,x08,ratio08,0,ratio08syserr);

	TCanvas *cccc=Canvas("cccc",0.12,0.036,0.15,0.06,0,0,0);
	//cccc->SetGrid(1,1);
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,0.5,4.0,"p_{T} (GeV/c)","Data/FONLL",0.075,0.85,0.07,0.78);
	//htmp->SetNdivisions(505,"y");
	StyleTGraph(grratioUP,1,1,4,8,1,1.9,"lsame");
	StyleTGraph(grratioC,2,4,4,8,1,1.9,"lsame");
	StyleTGraph(grratioLOW,3,1,4,8,1,1.9,"lsame");
	StyleTGraph(grratioPHENIXbg,1,1,2,22,1,2.3,"psame");
	draw_syspp(grratioPHENIXsys,kMagenta+1,2.0,10);
	StyleTGraph(grratioPHENIX,1,kMagenta+1,2,22,kMagenta+1,2.1,"psame");
	StyleTGraph(grratio08,1,1,2,23,1,2.3,"psame");
	draw_syspp(grratio08sys,kGreen-1,2.5,10);
	StyleTGraph(grratio08,1,kGreen-1,2,23,kGreen-1,2.1,"psame");
	//StyleTGraph(grratio12HighEMCbg,1,1,2,23,1,2.3,"psame");
	//draw_syspp(grratio12HighEMCsys,kGreen-1,2.5,10);
	//StyleTGraph(grratio12HighEMC,1,1,2,23,kGreen-1,2.1,"psame");
	StyleTGraph(grratio12Highbg,1,1,2,8,1,1.9,"psame");
	draw_syspp(grratio12Highsys,kYellow+2,2.5,10);
	StyleTGraph(grratio12High,1,kYellow+2,2,8,kYellow+2,1.7,"psame");
	lg= Legend(0.46,0.5,0.81,0.82,0.04);
	lg->AddEntry(grratio12Highbg,"eHF 2012 STAR,|y|<0.7","pl");
	lg->AddEntry(grratioPHENIXbg,"eHF PHENIX 2005,|y|<0.35","pl");
	lg->AddEntry(grratio08bg,"eHF 2008 STAR published,|y|<0.5","pl");
	//lg->AddEntry(grratio12Highbg,"SMD","pl");
	//lg->AddEntry(grratio12HighEMCbg,"EMC","pl");
	lg->AddEntry(grratioUP,"FONLL (upper limit)","l");
	lg->AddEntry(grratioC,"FONLL","l");
	lg->AddEntry(grratioLOW,"FONLL (lower limit)","l");
	lg= Legend(0.46,0.5,0.81,0.82,0.04);
	lg->AddEntry(grratio12High,"eHF 2012 STAR,|y|<0.7","pl");
	lg->AddEntry(grratioPHENIX,"eHF PHENIX 2005,|y|<0.35","pl");
	lg->AddEntry(grratio08,"eHF 2008 STAR published,|y|<0.5","pl");
	//lg->AddEntry(grratio12High,"SMD","pl");
	//lg->AddEntry(grratio12HighEMC,"EMC","pl");
	lg->AddEntry(grratioUP,"FONLL (upper limit)","l");
	lg->AddEntry(grratioC,"FONLL","l");
	lg->AddEntry(grratioLOW,"FONLL (lower limit)","l");
	tx.SetTextSize(0.07);
	tx.DrawLatex(0.47,0.86,"p+p @ #sqrt{s} = 200 GeV");
	tx.SetTextSize(0.065);
	tx.DrawLatex(0.16,0.86,"(b)");
	cccc->SaveAs("./pic/HFeoverFONLLCompared.png");
	cccc->SaveAs("./pic/HFeoverFONLLCompared.eps");
}
