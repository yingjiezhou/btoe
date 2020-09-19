#include "ptbin.h"
#include "style.h"
void plotNPEGpTCutSysYj()
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
	f=new TFile("yj/Pi0Dalitz_hist.root");
	TH2F *hGpTvsptPi0  = (TH2F *)f->Get("RcptMeeSMD2");
	f=new TFile("yj/EtaDalitz_hist.root");
	TH2F *hGpTvsptEta  = (TH2F *)f->Get("RcptMeeSMD2");
	f=new TFile("yj/Gamma_hist.root");
	TH2F *hGpTvsptPhoton  = (TH2F *)f->Get("RcptMeeSMD2");

	f=new TFile("npe_tree_May5_11default_gpt_dist.root");
	TH2F *hGpTvspt0  = (TH2F *)f->Get("hRcptMeeSMD2US_0");
	TH2F *hGpTvsptlike0  = (TH2F *)f->Get("RcptMeeSMD2_0");

	f=new TFile("npe_tree_May5_11default_gpt_dist.root");
	TH2F *hGpTvspt2  = (TH2F *)f->Get("hRcptMeeSMD2US_2");
	TH2F *hGpTvsptlike2  = (TH2F *)f->Get("RcptMeeSMD2_2");

//	hGpT= new TH1F("hGpT",";p_{T} (GeV/c); yield",nPtBins,ptbin);
//	hGpTSys= new TH1F("hGpTSys",";p_{T} (GeV/c); yield",nPtBins,ptbin);
	//for(int i=3; i<4; i++) {
	for(int i=0; i<7; i++) {
		int ptlw = (int)hGpTvsptPi0->GetXaxis()->FindBin(ptbin[i]+1e-6);
		int ptup = (int)hGpTvsptPi0->GetXaxis()->FindBin(ptbin[i+1]-1e-6);

		hGpTDisPi0[i] = (TH1F *)hGpTvsptPi0->ProjectionY(Form("GpTDisPi0_%d",i),ptlw,ptup);
		hGpTDisPi0[i]->Sumw2();
    hGpTDisPi0[i]->GetXaxis()->SetRangeUser(0.2, 20);
		hGpTDisPi0[i]->Scale(1./hGpTDisPi0[i]->Integral());
//		hGpTDisPi0[i]->Rebin(5);
//		hGpTDisPi0[i]->Scale(1./5.);

		hGpTDisEta[i] = (TH1F *)hGpTvsptEta->ProjectionY(Form("GpTDisEta_%d",i),ptlw,ptup);
		hGpTDisEta[i]->Sumw2();
    hGpTDisEta[i]->GetXaxis()->SetRangeUser(0.2, 20);
		hGpTDisEta[i]->Scale(1./hGpTDisEta[i]->Integral());
//		hGpTDisEta[i]->Rebin(5);
//		hGpTDisEta[i]->Scale(1./5.);

		hGpTDisPhoton[i] = (TH1F *)hGpTvsptPhoton->ProjectionY(Form("GpTDisPhoton_%d",i),ptlw,ptup);
		hGpTDisPhoton[i]->Sumw2();
    hGpTDisPhoton[i]->GetXaxis()->SetRangeUser(0.2, 20);
		hGpTDisPhoton[i]->Scale(1./hGpTDisPhoton[i]->Integral());
//		hGpTDisPhoton[i]->Rebin(5);
//		hGpTDisPhoton[i]->Scale(1./5.);

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
    cout<<hGpTDisUK_K[i]->Integral()<<"   Entrie  "<<hGpTDisUK_K[i]->GetEntries()<<endl;

		hGpTDisUK_K[i]->Scale(1./hGpTDisUK_K[i]->Integral());
//		hGpTDisUK_K[i]->Rebin(5);
//		hGpTDisUK_K[i]->Scale(1./5.);

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
		cc->SaveAs(Form("./pic/comp_NPEGpTCutSys_%d.pdf",i));

	}
	mypdf->On();
	mypdf->Close();

	}
