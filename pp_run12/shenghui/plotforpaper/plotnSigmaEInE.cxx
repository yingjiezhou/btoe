#include "../ptbin.h"
#include "../style.h"
#include <cstring>

void plotnSigmaEInE()
{
	setstyle();
	TLatex tx;
	tx.SetNDC();
	tx.SetTextFont(42);
	TLatex tl;
	TH1F *hInE[trigger],*hPurity[trigger],*htmp[trigger],*hnSigE[nPtBins][trigger],*hnSigE_sample[nPtBins][trigger],*hRatio[nPtBins][trigger],*hPurity_sample[nPtBins][trigger];
	TBox *bLabel;
	TBox *bFoot;
	TLegend *lg;
	float ymin,ymax,mean,rms;
	float Cons=1.0;
	TF1 *funpi  = new TF1("funpi","gaus");
	TF1 *funkp  = new TF1("funkp","gaus");
	TF1 *fune  = new TF1("fune","gaus");
	TF1 *fune_sample  = new TF1("fune_sample","gaus");
	TF1 *fpurity  = new TF1("fpurity","gaus");
	TF1 *total,*total_sample;
	TH1F *hnSigEpi[trigger],*hnSigEk[trigger],*hnSigEp[trigger],*hnSigEe[trigger],*hnSigEeSigma[trigger],*hMean[trigger],*hSigma[trigger];
	TH2F *hnSigEPt[trigger];
	TNtuple* nt_sample[nPtBins][trigger];
	TCanvas *cc=Canvas("cc",0.12,0.036,0.15,0.06,0,1,0);
	TPDF *mypdf = new TPDF("result/nSigEInE.pdf",111);
	//TPDF *mypdf = new TPDF("result/nSigEInEEMC.pdf",111);
	mypdf->Off();
	total = new TF1("total", "gaus(0)+gaus(3)+gaus(6)");
	total_sample = new TF1("total_sample", "gaus(0)+gaus(3)+gaus(6)");
	TFile *f;
	for(int k=1;k<trigger;k++){
		//for(int k=1;k<trigger-1;k++){
		f = new TFile("../Efficiency/effroot/nSigmaEHadron.root");
		hnSigEpi[k]=(TH1F *)f->Get(Form("hnSigmaEpi_%s",Trigger[k]));
		hnSigEk[k]=(TH1F *)f->Get(Form("hnSigmaEk_%s",Trigger[k]));
		hnSigEp[k]=(TH1F *)f->Get(Form("hnSigmaEp_%s",Trigger[k]));
		hnSigEe[k]=(TH1F *)f->Get(Form("hnSigmaEe_%s",Trigger[k]));
		hnSigEeSigma[k]=(TH1F *)f->Get(Form("hnSigmaEeSigma_%s",Trigger[k]));
		/*hnSigEpi[k]=(TH1F *)f->Get("hnSigmaEpi");
		  hnSigEk[k]=(TH1F *)f->Get("hnSigmaEk");
		  hnSigEp[k]=(TH1F *)f->Get("hnSigmaEp");
		  hnSigEe[k]=(TH1F *)f->Get("hnSigmaEe");
		  hnSigEeSigma[k]=(TH1F *)f->Get("hnSigmaEeSigma");*/
		f = new TFile(Form("../RawYield/DataMaker/NPE_%s.root",Trigger[k]));
		//f = new TFile(Form("/star/data01/pwg/yezhenyu/Run12/NPE/shenghui/20200406/HT/RawYield/DataMakerPrimary/NPE_%s.root",Trigger[k]));
		hnSigEPt[k]=(TH2F *)f->Get("nSigEPt");
		//hnSigEPt[k]=(TH2F *)f->Get("nSigEPtSMD");
		//hnSigEPt[k]=(TH2F *)f->Get("nSigEPtAdc0");
		//hnSigEPt[k]=(TH2F *)f->Get("nSigEPtEMCpovere");
		if(k==1){
			bLabel= new TBox(0.01, 0.88, 0.99, 0.99);
			bLabel->SetFillColor(kBlack);
			bLabel->Draw();
			tl.SetTextSize(0.08);
			tl.DrawTextNDC(0.13,0.5,"Plot InE nSigmaE distribution");
			bFoot= new TBox(0.01, 0.01, 0.99, 0.12);
			bFoot->SetFillColor(kBlack);
			bFoot->Draw();
			tl.SetTextColor(kWhite);
			tl.SetTextSize(0.05);
			tl.DrawLatex(0.05, 0.05, (new TDatime())->AsString());
			tl.SetTextColor(kBlack);
			tl.SetTextSize(0.1);
			cc->Update();
			cc->Clear();
		}
		hPurity[k]= new TH1F(Form("hPurity_%s",Trigger[k]),";p_{T} (GeV/c); Purity",nPtBins,ptbin);
		hInE[k]= new TH1F(Form("hInE_%s",Trigger[k]),";p_{T} (GeV/c); dN/dp_{T} (GeV/c)^{-1}",nPtBins,ptbin);
		hMean[k]= new TH1F(Form("hMean_%s",Trigger[k]),";p_{T} (GeV/c); dN/dp_{T} (GeV/c)^{-1}",nPtBins,ptbin);
		hSigma[k]= new TH1F(Form("hSigma_%s",Trigger[k]),";p_{T} (GeV/c); dN/dp_{T} (GeV/c)^{-1}",nPtBins,ptbin);
		for(int i=0; i<nPtBins; i++) {
			//for(int i=0; i<1; i++) {
			cc->SetLogy(1);
			int ptlw = (int)hnSigEPt[k]->GetXaxis()->FindBin(ptbin[i]+1e-6);
			int ptup = (int)hnSigEPt[k]->GetXaxis()->FindBin(ptbin[i+1]-1e-6);

			hnSigE[i][k] = (TH1F *)hnSigEPt[k]->ProjectionY(Form("nSigE_%d_%d",i,k),ptlw,ptup);
			hnSigE[i][k]->Sumw2();
			int  nMin=(int) hnSigE[i][k]->GetXaxis()->FindBin(nsigmaeMin+1e-6);
			int  nMax=(int) hnSigE[i][k]->GetXaxis()->FindBin(nsigmaeMax-1e-6);
			int Nee   = hnSigE[i][k]->Integral(nMin,nMax);
			cout<<"nMin"<<nMin<<"nMax"<<nMax<<"Nee"<<Nee<<endl;
			hnSigE[i][k]->Rebin(4);
			if(!(k==0&&i==0)){
				cc->Clear();
				cc->SetLogy(1);
			}
			//cc->cd();
			//pad->Draw();
			//pad->cd(1);
			//setpad(gPad,0.2,0.15,0.05,0.15,0,1,0);
			ymin=0.2;
			ymax=hnSigE[i][k]->GetMaximum()*1000;
			htmp[k]=histo(Form("htmp_%d",k),40,-20,20,ymin,ymax,"n#sigma_{e}","Counts",0.075,0.85,0.075,0.75);
			Style(hnSigE[i][k],1,1,1,8,kBlack,1.,"psame");
			funpi->SetParLimits(0,1,hnSigE[i][k]->GetMaximum());
			funpi->SetParameter(1,hnSigEpi[k]->GetBinContent(i+1));
			//cout<<"cccccccccc"<<hnSigEpi[k]->GetBinContent(i+1)<<endl;
			funpi->SetParLimits(1,hnSigEpi[k]->GetBinContent(i+1)-0.5,hnSigEpi[k]->GetBinContent(i+1)+0.5);
			//funpi->SetParLimits(1,hnSigEpi[k]->GetBinContent(i+1)-Cons*hnSigEpi[k]->GetBinError(i+1),hnSigEpi[k]->GetBinContent(i+1)+Cons*hnSigEpi[k]->GetBinError(i+1));
			funpi->SetParameter(2,1.0);
			funpi->SetRange(hnSigEpi[k]->GetBinContent(i+1)-8,hnSigEpi[k]->GetBinContent(i+1)+8);

			funkp->SetParLimits(0,1,hnSigE[i][k]->GetMaximum());
			funkp->SetParameter(1,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2);
			//funkp->SetParLimits(1,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2-0.5,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2+0.5);
			funkp->SetParLimits(1,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2-Cons*sqrt(pow(hnSigEk[k]->GetBinError(i+1),2)+pow(hnSigEp[k]->GetBinError(i+1),2))/2,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2+Cons*sqrt(pow(hnSigEk[k]->GetBinError(i+1),2)+pow(hnSigEp[k]->GetBinError(i+1),2))/2);
			funkp->SetParameter(2,1.0);
			funkp->SetRange((hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2-7,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2+7);

			fune->SetParLimits(0,1,hnSigE[i][k]->GetMaximum());
			fune->SetParameter(1,hnSigEe[k]->GetBinContent(i+1));
			fune->SetParLimits(1,hnSigEe[k]->GetBinContent(i+1)-Cons*hnSigEe[k]->GetBinError(i+1),hnSigEe[k]->GetBinContent(i+1)+Cons*hnSigEe[k]->GetBinError(i+1));
			fune->SetParameter(2,hnSigEeSigma[k]->GetBinContent(i+1));
			fune->SetParLimits(2,hnSigEeSigma[k]->GetBinContent(i+1)-Cons*hnSigEeSigma[k]->GetBinError(i+1),hnSigEeSigma[k]->GetBinContent(i+1)+Cons*hnSigEeSigma[k]->GetBinError(i+1));
			fune->SetRange(hnSigEe[k]->GetBinContent(i+1)-5*hnSigEeSigma[k]->GetBinContent(i+1),hnSigEe[k]->GetBinContent(i+1)+5*hnSigEeSigma[k]->GetBinContent(i+1));
			hnSigE[i][k]->Fit(funpi,"IN0R");
			hnSigE[i][k]->Fit(funkp,"IN0R");
			hnSigE[i][k]->Fit(fune,"IN0R");
			//hnSigE[i][k]->Fit(funpi,"IBL");
			//hnSigE[i][k]->Fit(funkp,"IBL");
			//hnSigE[i][k]->Fit(fune,"IBL");

			total->SetParameter(0,funpi->GetParameter(0));
			total->SetParameter(1,funpi->GetParameter(1));
			total->SetParameter(2,funpi->GetParameter(2));
			total->SetParameter(3,funkp->GetParameter(0));
			total->SetParameter(4,funkp->GetParameter(1));
			total->SetParameter(5,funkp->GetParameter(2));
			total->SetParameter(6,fune->GetParameter(0));
			total->SetParameter(7,fune->GetParameter(1));
			total->SetParameter(8,fune->GetParameter(2));

			total->SetParLimits(0,1,hnSigE[i][k]->GetMaximum());
			total->SetParLimits(1,hnSigEpi[k]->GetBinContent(i+1)-0.5,hnSigEpi[k]->GetBinContent(i+1)+0.5);
			//total->SetParLimits(1,hnSigEpi[k]->GetBinContent(i+1)-Cons*hnSigEpi[k]->GetBinError(i+1),hnSigEpi[k]->GetBinContent(i+1)+Cons*hnSigEpi[k]->GetBinError(i+1));
			total->SetParameter(2,1.0);
			//total->SetParLimits(2,0.8,1.2);

			total->SetParLimits(3,1,hnSigE[i][k]->GetMaximum());
			total->SetParLimits(4,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2-0.5,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2+0.5);
			//total->SetParLimits(4,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2-Cons*sqrt(pow(hnSigEk[k]->GetBinError(i+1),2)+pow(hnSigEp[k]->GetBinError(i+1),2))/2,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2+Cons*sqrt(pow(hnSigEk[k]->GetBinError(i+1),2)+pow(hnSigEp[k]->GetBinError(i+1),2))/2);
			total->SetParameter(5,1.0);
			//total->SetParLimits(5,0.8,1.2);

			total->SetParLimits(6,1,hnSigE[i][k]->GetMaximum());
			total->SetParameter(7,hnSigEe[k]->GetBinContent(i+1));
			total->SetParLimits(7,hnSigEe[k]->GetBinContent(i+1)-Cons*hnSigEe[k]->GetBinError(i+1),hnSigEe[k]->GetBinContent(i+1)+Cons*hnSigEe[k]->GetBinError(i+1));
			total->SetParameter(8,hnSigEeSigma[k]->GetBinContent(i+1));
			total->SetParLimits(8,hnSigEeSigma[k]->GetBinContent(i+1)-Cons*hnSigEeSigma[k]->GetBinError(i+1),hnSigEeSigma[k]->GetBinContent(i+1)+Cons*hnSigEeSigma[k]->GetBinError(i+1));
			total->SetRange(-12,5);
			/////////////////////////////////////////////////////////////////////////////////
			//total_sample
			////////////////////////////////////////////////////////////////////////////////
			total_sample->SetParameter(0,funpi->GetParameter(0));
			total_sample->SetParameter(1,funpi->GetParameter(1));
			total_sample->SetParameter(2,funpi->GetParameter(2));
			total_sample->SetParameter(3,funkp->GetParameter(0));
			total_sample->SetParameter(4,funkp->GetParameter(1));
			total_sample->SetParameter(5,funkp->GetParameter(2));
			total_sample->SetParameter(6,fune->GetParameter(0));
			total_sample->SetParameter(7,fune->GetParameter(1));
			total_sample->SetParameter(8,fune->GetParameter(2));

			total_sample->SetParLimits(0,1,hnSigE[i][k]->GetMaximum());
			total_sample->SetParLimits(1,hnSigEpi[k]->GetBinContent(i+1)-0.5,hnSigEpi[k]->GetBinContent(i+1)+0.5);
			total_sample->SetParameter(2,1.0);

			total_sample->SetParLimits(3,1,hnSigE[i][k]->GetMaximum());
			total_sample->SetParLimits(4,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2-0.5,(hnSigEk[k]->GetBinContent(i+1)+hnSigEp[k]->GetBinContent(i+1))/2+0.5);
			total_sample->SetParameter(5,1.0);

			total_sample->SetParLimits(6,1,hnSigE[i][k]->GetMaximum());
			total_sample->SetParameter(7,hnSigEe[k]->GetBinContent(i+1));
			total_sample->SetParLimits(7,hnSigEe[k]->GetBinContent(i+1)-Cons*hnSigEe[k]->GetBinError(i+1),hnSigEe[k]->GetBinContent(i+1)+Cons*hnSigEe[k]->GetBinError(i+1));
			total_sample->SetParameter(8,hnSigEeSigma[k]->GetBinContent(i+1));
			total_sample->SetParLimits(8,hnSigEeSigma[k]->GetBinContent(i+1)-Cons*hnSigEeSigma[k]->GetBinError(i+1),hnSigEeSigma[k]->GetBinContent(i+1)+Cons*hnSigEeSigma[k]->GetBinError(i+1));
			//total_sample->FixParameter(7,hnSigEe[k]->GetBinContent(i+1));
			//total_sample->FixParameter(8,hnSigEeSigma[k]->GetBinContent(i+1));
			total_sample->SetRange(-12,5);
			///////////////////////////////////////////////////////////////////////////////////////
			hnSigE[i][k]->Fit(total,"IN0R");
			//hnSigE[i][k]->Fit(total,"IBL");
			funpi->SetParameter(0,total->GetParameter(0));
			funpi->SetParameter(1,total->GetParameter(1));
			funpi->SetParameter(2,total->GetParameter(2));
			funkp->SetParameter(0,total->GetParameter(3));
			funkp->SetParameter(1,total->GetParameter(4));
			funkp->SetParameter(2,total->GetParameter(5));
			fune->SetParameter(0,total->GetParameter(6));
			fune->SetParameter(1,total->GetParameter(7));
			fune->SetParameter(2,total->GetParameter(8));

			StyleFun(total,1,kYellow+1,4,22,kBlue+2,1.4,"lsame");
			StyleFun(funkp,2,kGreen,4,28,kGreen+2,1.4,"lsame");
			StyleFun(funpi,2,kBlue,4,29,kPink+2,1.5,"lsame");
			StyleFun(fune,2,kRed,4,20,kRed+2,1.25,"lsame");
			l1 = Line(nsigmaeMin,0,nsigmaeMin,hnSigE[i][k]->GetMaximum()*5.0,4,6,3);
			l1 = Line(nsigmaeMax,0,nsigmaeMax,hnSigE[i][k]->GetMaximum()*5.0,4,6,3);
			lg= Legend(0.14,0.51,0.44,0.76,0.05);
			lg->AddEntry(total,"3 Gaussian","l");
			lg->AddEntry(funpi,"#pi^{#pm}","l");
			lg->AddEntry(funkp,"K^{#pm}+p^{#pm}","l");
			lg->AddEntry(fune,"e^{#pm}","l");
			lg->AddEntry(l1,"n#sigma_{e} cuts","l");
			hnSigE[i][k]->SetTitle("");
			char chh1[50],chh2[50],chh3[50],chh4[50],chh5[50],chh6[50],chh7[50],chh8[50],chh9[50],chh10[50];
			sprintf(chh1,"#chi^{2} / ndf = %6.2f / %d",total->GetChisquare(),total->GetNDF());
			sprintf(chh2,"C_{e} = %5.3e #pm %4.2e",total->GetParameter(6),total->GetParError(6));
			sprintf(chh3,"#mu_{e} = %5.3f #pm %5.3f",total->GetParameter(7),total->GetParError(7));
			sprintf(chh4,"#sigma_{e} = %5.3f #pm %5.3f",total->GetParameter(8),total->GetParError(8));
			sprintf(chh5,"C_{#pi} = %5.3e #pm %4.2e",total->GetParameter(0),total->GetParError(0));
			sprintf(chh6,"#mu_{#pi} = %5.3f #pm %5.3f",total->GetParameter(1),total->GetParError(1));
			sprintf(chh7,"#sigma_{#pi} = %5.3f #pm %5.3f",total->GetParameter(2),total->GetParError(2));
			sprintf(chh8,"C_{Kp} = %5.3e #pm %4.2e",total->GetParameter(3),total->GetParError(3));
			sprintf(chh9,"#mu_{Kp} = %5.3f #pm %5.3f",total->GetParameter(4),total->GetParError(4));
			sprintf(chh10,"#sigma_{Kp} = %5.3f #pm %5.3f",total->GetParameter(5),total->GetParError(5));
			TPaveStats *ptstats;
			ptstats= new TPaveStats(0.65,0.5,0.95,0.92,"brNDC");
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
			text = ptstats->AddText(chh6);
			text = ptstats->AddText(chh7);
			text = ptstats->AddText(chh8);
			text = ptstats->AddText(chh9);
			text = ptstats->AddText(chh10);
			ptstats->Draw();
			tx.SetTextSize(0.055);
			tx.DrawLatex(0.18,0.8,Form("%4.1f < p_{T} < %4.1f GeV/c",ptbin[i],ptbin[i+1]));
			tx.SetTextSize(0.06);
			//tx.DrawTextNDC(0.27,0.795,triggerid[k]);
			tx.SetTextSize(0.065);
			tx.DrawLatex(0.15,0.2,"(a)");
			lg= Legend(0.05,0.835,0.42,0.95,0.07);
			lg->AddEntry(funkp,"p+p @ #sqrt{s} = 200 GeV","");
			float dsige = (20.+20.)/hnSigE[i][k]->GetNbinsX();
			float ept=ptbin[i+1]-ptbin[i];

			float  nMc=total->Integral(nsigmaeMin,nsigmaeMax)/dsige;
			float  nData=fune->Integral(nsigmaeMin,nsigmaeMax)/dsige;

			float yield=(nData+1)/(nMc+2);
			float eyield=sqrt((nData+1)*(nData+2)/(nMc+2)/(nMc+3)-pow(nData+1,2)/pow(nMc+2,2));

			hPurity[k]->SetBinContent(i+1,yield);
			hPurity[k]->SetBinError(i+1,eyield);
			hMean[k]->SetBinContent(i+1,total->GetParameter(7));
			hMean[k]->SetBinError(i+1,total->GetParError(7));
			hSigma[k]->SetBinContent(i+1,total->GetParameter(8));
			hSigma[k]->SetBinError(i+1,total->GetParError(8));
			hInE[k]->SetBinContent(i+1,Nee/ept);
			hInE[k]->SetBinError(i+1,sqrt(Nee)/ept);
			cout<<Nee/ept<<" "<<nMc/ept<<" "<<fune->Integral(-3.5,3.0)/dsige/ept<<endl;
			//hInE[k]->SetBinContent(i+1,fune->Integral(-3.5,3.0)/dsige/ept);
			//hInE[k]->SetBinError(i+1,sqrt(fune->Integral(-3.5,3.0)/dsige)/ept);

			if(k==1&&i>7) continue;
			if(k==2&&i<2) continue;

			cc->cd();
			mypdf->On();
			cc->Update();
			mypdf->NewPage();
			cc->Modified();
			mypdf->Off();
			cc->SaveAs(Form("pic/pic%s/nSigmaEInE_%d.eps",Trigger[k],i));
			cc->SaveAs(Form("pic/pic%s/nSigmaEInE_%d.png",Trigger[k],i));
		}
		}
		mypdf->On();
		mypdf->Close();
	}
