#include "ptbin.h"
#include "style.h"
void plotNPEGpTCutSys()
{
	setstyle();
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetNDC();
	tx.SetTextFont(42);
	TLatex tx1;
	tx1.SetTextSize(0.06);
	tx1.SetNDC();
	tx1.SetTextFont(42);
	auto cc=Canvas("cc",0.15,0.03,0.15,0.06,0,1,0);
	TPDF *mypdf = new TPDF("result/NPEGpTCutSys.pdf",111);
	mypdf->Off();
	TFile *f;
	TH1F *hSigma,*hGpT,*hGpTSys,*hReceff,*hReceffSys,*hSys;
	TH2F *htmp;
	TH1F *hGpTDisEta[nPtBins],*hGpTDis[nPtBins],*hGpTDislike[nPtBins],*hGpTDisUK_K[nPtBins],*hGpTDisPi0[nPtBins],*hGpTDisPhoton[nPtBins];
	TLegend *lg;
	f=new TFile("shenghui/Pi0Dalitz_hist.root");
	TH2F *hGpTvsptPi0  = (TH2F *)f->Get("hGpTPartWt");
	f=new TFile("shenghui/EtaDalitz_hist.root");
	TH2F *hGpTvsptEta  = (TH2F *)f->Get("hGpTPartWt");
	f=new TFile("shenghui/Gamma_hist.root");
	TH2F *hGpTvsptPhoton  = (TH2F *)f->Get("hGpTPartWt");

	f=new TFile("shenghui/NPE_HT0.root");
	TH2F *hGpTvspt0  = (TH2F *)f->Get("hGpTPartSMD");
	TH2F *hGpTvsptlike0  = (TH2F *)f->Get("hGpTPartSMDlike");

	f=new TFile("shenghui/NPE_HT2.root");
	TH2F *hGpTvspt2  = (TH2F *)f->Get("hGpTPartSMD");
	TH2F *hGpTvsptlike2  = (TH2F *)f->Get("hGpTPartSMDlike");

	hGpT= new TH1F("hGpT",";p_{T} (GeV/c); yield",nPtBins,ptbin);
	hGpTSys= new TH1F("hGpTSys",";p_{T} (GeV/c); yield",nPtBins,ptbin);
	//for(int i=3; i<4; i++) {
	for(int i=0; i<nPtBins; i++) {
		int ptlw = (int)hGpTvsptPi0->GetXaxis()->FindBin(ptbin[i]+1e-6);
		int ptup = (int)hGpTvsptPi0->GetXaxis()->FindBin(ptbin[i+1]-1e-6);

		hGpTDisPi0[i] = (TH1F *)hGpTvsptPi0->ProjectionY(Form("GpTDisPi0_%d",i),ptlw,ptup);
		hGpTDisPi0[i]->Sumw2();
		hGpTDisPi0[i]->Scale(1./hGpTDisPi0[i]->Integral());
		hGpTDisPi0[i]->Rebin(5);
		hGpTDisPi0[i]->Scale(1./5.);

		hGpTDisEta[i] = (TH1F *)hGpTvsptEta->ProjectionY(Form("GpTDisEta_%d",i),ptlw,ptup);
		hGpTDisEta[i]->Sumw2();
		hGpTDisEta[i]->Scale(1./hGpTDisEta[i]->Integral());
		hGpTDisEta[i]->Rebin(5);
		hGpTDisEta[i]->Scale(1./5.);

		hGpTDisPhoton[i] = (TH1F *)hGpTvsptPhoton->ProjectionY(Form("GpTDisPhoton_%d",i),ptlw,ptup);
		hGpTDisPhoton[i]->Sumw2();
		hGpTDisPhoton[i]->Scale(1./hGpTDisPhoton[i]->Integral());
		hGpTDisPhoton[i]->Rebin(5);
		hGpTDisPhoton[i]->Scale(1./5.);

		if(i<3){
			hGpTDis[i] = (TH1F *)hGpTvspt0->ProjectionY(Form("GpTDisEE_%d",i),ptlw,ptup);
			hGpTDislike[i] = (TH1F *)hGpTvsptlike0->ProjectionY(Form("GpTDisEElike_%d",i),ptlw,ptup);
		}
		else{
			hGpTDis[i] = (TH1F *)hGpTvspt2->ProjectionY(Form("GpTDisEE_%d",i),ptlw,ptup);
			hGpTDislike[i] = (TH1F *)hGpTvsptlike2->ProjectionY(Form("GpTDisEElike_%d",i),ptlw,ptup);
		}
		hGpTDisUK_K[i] = (TH1F *)hGpTDis[i]->Clone(Form("GpTDisUK_K_%d",i));
		hGpTDisUK_K[i]->Sumw2();
		hGpTDisUK_K[i]->Add(hGpTDislike[i],-1);
		//hGpTDisSys[i] = (TH1F *)hGpTDisUK_K[i]->Clone(Form("GpTDis_%d",i));
		hGpTDisUK_K[i]->Scale(1./hGpTDisUK_K[i]->Integral());
		hGpTDisUK_K[i]->Rebin(5);
		hGpTDisUK_K[i]->Scale(1./5.);

		htmp = histo2D("htmp",20,0,10,10,1e-8,1e1,"Gp_{T} (GeV/c)","1/N_{tracks}",0.075,0.83,0.08,0.85);
		//htmp = histo2D("htmp",20,0,10,10,0,0.05,"Gp_{T} (GeV/c)","1/N_{tracks}",0.075,0.83,0.08,0.85);
		htmp->SetNdivisions(505,"x");
		htmp->SetNdivisions(505,"y");
		Style(hGpTDisEta[i],1,1,3,23,kBlue,2.1,"psame");
		Style(hGpTDisPi0[i],1,1,3,8,kGreen+1,1.8,"psame");
		Style(hGpTDisPhoton[i],1,1,3,22,kRed,2.1,"psame");
		Style(hGpTDisUK_K[i],1,1,3,21,1,1.75,"psame");
		lg= Legend(0.5,0.53,0.84,0.76,0.045);
		lg->AddEntry(hGpTDisUK_K[i],"Photonic electron","pl");
		lg->AddEntry(hGpTDisPhoton[i],"#gamma Conversion Embedding","pl");
		lg->AddEntry(hGpTDisPi0[i],"#pi^{0} Dalitz Decay Embedding","pl");
		lg->AddEntry(hGpTDisEta[i],"#eta Dalitz Decay Embedding","pl");
		tx.DrawLatex(0.5,0.85,"p+p @ #sqrt{s} = 200 GeV");
		tx1.DrawLatex(0.52,0.78,Form("%4.2f < p_{T} < %4.2f GeV/c",ptbin[i],ptbin[i+1]));
		mypdf->On();
		cc->Update();
		if(i<nPtBins-1)mypdf->NewPage();
		cc->Modified();
		mypdf->Off();
		cc->SaveAs(Form("./pic/shenghui_NPEGpTCutSys_%d.png",i));

		float Nes   = hGpTDis[i]->Integral(hGpTDis[i]->FindBin(0.3+1e-6),hGpTDis[i]->GetNbinsX());
		float Nebg   = hGpTDislike[i]->Integral(hGpTDislike[i]->FindBin(0.3+1e-6),hGpTDislike[i]->GetNbinsX());
		float Ne   = Nes-Nebg;//hGpTDisSys[i]->Integral(1,hGpTDisSys[i]->FindBin(0.15-1e-6));
		hGpT->SetBinContent(i+1,Ne);
		hGpT->SetBinError(i+1,sqrt(Nes+Nebg));
		//cout<<"Ne"<<sqrt(Ne)<<" "<<sqrt(Nes+Nebg)<<" "<<sqrt(hGpTDis[i]->Integral(1,hGpTDis[i]->FindBin(0.15-1e-6))+hGpTDislike[i]->Integral(1,hGpTDis[i]->FindBin(0.15-1e-6)))<<endl;
		float NesSys = hGpTDis[i]->Integral(hGpTDis[i]->FindBin(0.2+1e-6),hGpTDis[i]->GetNbinsX());
		float NebgSys = hGpTDislike[i]->Integral(hGpTDislike[i]->FindBin(0.2+1e-6),hGpTDislike[i]->GetNbinsX());
		float NeSys   = NesSys-NebgSys;//hGpTDisSys[i]->Integral(1,hGpTDisSys[i]->FindBin(0.15-1e-6));
		hGpTSys->SetBinContent(i+1,NeSys);
		hGpTSys->SetBinError(i+1,sqrt(NesSys+NebgSys));
	}
	mypdf->On();
	mypdf->Close();
	/*hGpT->Print("ALL");
	hGpTSys->Print("ALL");


	hSys= new TH1F("hSysGpTCut",";p_{T} (GeV/c); #frac{1}{2#pip_{T}}#frac{d^{2}N}{dp_{T}dy} [(GeV/c)^{-2}]",nPtBins,ptbin);
	//////////////////////////////////////////////////////////////////////
	//TPC tracking eff
	/////////////////////////////////////////////////////////////////////
	f=new TFile("../Efficiency/embedding/effroot/PHEReceffSysGpt.root");
	hReceffSys=(TH1F *)f->Get("hefffun");//heffGpTCut
	f=new TFile("../Efficiency/embedding/effroot/PHEReceff.root");
	hReceff=(TH1F *)f->Get("hefffun");
	hGpTSys->Sumw2();
	hGpT->Sumw2();
	hGpTSys->Divide(hReceffSys);
	hGpT->Divide(hReceff);
	hSigma=(TH1F *)hGpTSys->Clone("hSigmaGpTCut");
	hSigma->Sumw2();
	hSigma->Divide(hGpT);
	hSigma->Print("ALL");
	for(int i=0;i<nPtBins;i++){
	hSys->SetBinContent(i+1,1-hSigma->GetBinContent(i+1));
	hSys->SetBinError(i+1,hSigma->GetBinError(i+1));
	}
	hSigmabg=(TH1F *)hSigma->Clone();
	cc->Clear();
	cc->SetLogy(0);
	cc->SetGrid(1,1);
	htmp = histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],10,0.5,1.5,"p_{T} (GeV/c)","#sigma_{Gp_{T}}",0.075,0.83,0.08,0.7);
	htmp->SetNdivisions(505,"y");
	Style(hSigmabg,1,1,1,8,1,1.9,"psame");
	Style(hSigma,1,1,3,8,kGreen+1,1.7,"psame");
	TF1 *fun = new TF1("funSysGpTCut","pol0",2.5,10);
	fun->SetParameter(0,1.0);
	hSigma->Fit(fun,"N0IR","",2.5,10);
	StyleFun(fun,1,1,5,23,11,1.2,"E4same");
	drawLatex(0.65,0.37,Form("%3.3f #pm %3.3f",fun->GetParameter(0), fun->GetParError(0)),42,0.06,1);
	tx.DrawLatex(0.5,0.85,"p+p @ #sqrt{s} = 200 GeV");
	cc->SaveAs("./figure/NPEGpTCutSys.png");
	cc->SaveAs("./figure/NPEGpTCutSys.eps");
	file = new TFile("rootfile/NPESys.root","UPDATE");
	//file = new TFile("rootfile/NPESysHT0.root","UPDATE");
	//file = new TFile("rootfile/NPESysHT2.root","UPDATE");
	file->cd();
	hSys->Write();
	fun->Write();
	file->Close();*/
	}
