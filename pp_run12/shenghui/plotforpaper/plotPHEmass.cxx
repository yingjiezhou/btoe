#include "../ptbin.h"
#include "../style.h"

void plotPHEmass()
{
	setstyle();
	TLatex tx;
	tx.SetNDC();
	tx.SetTextFont(42);
	TLatex tl;
	TH1F *hPHE[trigger],*htmp[trigger],*hm[nPtBins][trigger],*hmlike[nPtBins][trigger],*hmUK_K[nPtBins][trigger],*hmbg[nPtBins][trigger],*hmlikebg[nPtBins][trigger];
	TH2F *hmvspt[trigger],*hmvsptlike[trigger];
	TBox *bLabel;
	TBox *bFoot;
	TLegend *lg;
	float ymin,ymax;
	TFile *f;
	TCanvas *cc=Canvas("cc",0.12,0.036,0.15,0.06,0,0,0);
	TPDF *mypdf = new TPDF("result/PHEMass.pdf",111);
	//TPDF *mypdf = new TPDF("result/PHEMassSMD.pdf",111);
	mypdf->Off();
	for(int k=1;k<trigger;k++){
	//for(int k=1;k<2;k++){
		f = new TFile(Form("../RawYield/DataMaker/NPE_%s.root",Trigger[k]));
		hmvspt[k]     = (TH2F *)f->Get("mvspt_5");
		hmvsptlike[k]    = (TH2F *)f->Get("mvsptlike_5");
		//hmvspt[k]     = (TH2F *)f->Get("mvsptSMD_5");
		//hmvsptlike[k]    = (TH2F *)f->Get("mvsptSMDlike_5");
		//hmvspt[k]     = (TH2F *)f->Get("mvsptAdc0");
		//hmvsptlike[k]    = (TH2F *)f->Get("mvsptAdc0like");
		//hmvspt[k]     = (TH2F *)f->Get("mvsptEMCpovere");
		//hmvsptlike[k]    = (TH2F *)f->Get("mvsptEMCpoverelike");

		if(k==1){
			bLabel= new TBox(0.01, 0.88, 0.99, 0.99);
			bLabel->SetFillColor(kBlack);
			bLabel->Draw();
			tl.SetTextSize(0.08);
			tl.DrawTextNDC(0.032,0.5,"Plot Photonic e Mass distribution");
			bFoot= new TBox(0.01, 0.01, 0.99, 0.12);
			bFoot->SetFillColor(kBlack);
			bFoot->Draw();
			tl.SetTextColor(kWhite);
			tl.SetTextSize(0.05);
			tl.DrawLatex(0.05, 0.05, (new TDatime())->AsString());
			tl.SetTextColor(kBlack);
			tl.SetTextSize(0.1);
			cc->Update();
		}
		hPHE[k]= new TH1F(Form("hPHE_%s",Trigger[k]),";p_{T} (GeV/c); dN/dp_{T} (GeV/c)^{-1}",nPtBins,ptbin);
		for(int i=0; i<nPtBins; i++) {
		//for(int i=0; i<1; i++) {
			int ptlw = (int)hmvspt[k]->GetXaxis()->FindBin(ptbin[i]+1e-6);
			int ptup = (int)hmvspt[k]->GetXaxis()->FindBin(ptbin[i+1]-1e-6);

			hm[i][k] = (TH1F *)hmvspt[k]->ProjectionY(Form("mee_%d_%d",i,k),ptlw,ptup);
			hmlike[i][k] = (TH1F *)hmvsptlike[k]->ProjectionY(Form("meelike_%d_%d",i,k),ptlw,ptup);
			hmUK_K[i][k] = (TH1F *)hm[i][k]->Clone(Form("meeUK_K_%d_%d",i,k));
			hmUK_K[i][k]->Sumw2();
			hmUK_K[i][k]->Add(hmlike[i][k],-1);
			//cout<<hmUK_K[i][k]->GetNbinsX()<<endl;
			/*for(int j=0;j<hmUK_K[i][k]->GetNbinsX();j++){
			if(hmUK_K[i][k]->GetBinContent(j+1)<0) {
				hmUK_K[i][k]->SetBinContent(j+1,0);
				hmUK_K[i][k]->SetBinError(j+1,0);
			}
			}*/
			
			int  mMax=(int) hm[i][k]->GetXaxis()->FindBin(0.24-1e-6);
			//int  mMax=(int) hm[i][k]->GetXaxis()->FindBin(0.15-1e-6);
			int Nee   = hm[i][k]->Integral(1,mMax);
			int Neebg = hmlike[i][k]->Integral(1,mMax);

			//int Nphe   = hmUK_K[i][k]->Integral(1,mMax);//Nee - Neebg;
			//int Nphee  = sqrt(Nphe);//sqrt(Nee + Neebg);
			int Nphe   = Nee - Neebg;
			int Nphee  = sqrt(Nee + Neebg);
			float ept=ptbin[i+1]-ptbin[i];
			//cout<<mMax<<" "<<Nphe<<" "<<ept<<endl;
			hPHE[k]->SetBinContent(i+1,Nphe/ept);
			hPHE[k]->SetBinError(i+1,Nphee/ept);

			hm[i][k]->Rebin(5);
			hmlike[i][k]->Rebin(5);
			hmUK_K[i][k]->Rebin(5);
			hmlikebg[i][k]=(TH1F *)hmlike[i][k]->Clone();
			hmbg[i][k]=(TH1F *)hm[i][k]->Clone();

			//float ymin = 1e-1;//hmUK_K[i][k]->GetMinimum();
			//float ymax = hm[i][k]->GetMaximum()*20.0;
			//htmp[k]=histo(Form("htmp_%d",k),24,-0.005,0.3,ymin,ymax,"Mass_{ee} (GeV/c^{2})","Counts",0.06,0.95,0.06,1.05);
			float ymin = hmUK_K[i][k]->GetMinimum();
			float ymax = hm[i][k]->GetMaximum()*2.0;
			htmp[k]=histo(Form("htmp_%d",k),24,-0.005,0.3,ymin,ymax,"Mass_{ee} (GeV/c^{2})","Counts",0.06,0.95,0.06,1.05);
			htmp[k]->SetNdivisions(506,"x");
			Style(hmbg[i][k],1,1,3,22,1,2.5,"hfpsame");
			Style(hm[i][k],1,1,3,22,kRed,1.9,"hfpsame");
			Style(hmlikebg[i][k],1,1,3,23,1,2.5,"hfpsame");
			Style(hmlike[i][k],1,1,3,23,kGreen+1,1.9,"hfpsame");
			Style(hmUK_K[i][k],1,1,3,8,1,1.7,"hfpsame");
			l1 = Line(0.24,0,0.24,hm[i][k]->GetMaximum()*0.85,7,6,5);
			lg = Legend(0.58,0.555,0.98,0.755,0.045);
			lg->AddEntry(hm[i][k],"Unlike Sign","pl");
			lg->AddEntry(hmlike[i][k],"Like Sign","pl");
			lg->AddEntry(hmUK_K[i][k],"Unlike - Like Sign","pl");
			lg->AddEntry(l1,"M_{ee} cut","l");
			tx.SetTextSize(0.055);
			tx.DrawLatex(0.545,0.795,Form("%4.1f < p_{T} < %4.1f GeV/c",ptbin[i],ptbin[i+1]));
			tx.SetTextSize(0.065);
			tx.DrawLatex(0.15,0.86,"(a)");
			//tx.SetTextSize(0.065);
			//tx.DrawLatex(0.14,0.87,"p+p @ 200 GeV");
			//lg = Legend(0.58,0.64,0.98,0.84,0.045);
			lg= Legend(0.405,0.825,0.815,0.94,0.07);
			lg->AddEntry(hm[i][k],"p+p @ #sqrt{s} = 200 GeV","");
			tx.SetTextSize(0.06);
			//tx.DrawLatex(0.3,0.79,triggerid[k]);
			//if(k==1&&i>4) continue;
			//if(k==2&&i<2) continue;
			cc->cd();
			mypdf->On();
			cc->Update();
			mypdf->NewPage();
			cc->Modified();
			mypdf->Off();
			cc->SaveAs(Form("pic/pic%s/PHEMass_%d.eps",Trigger[k],i));
			cc->SaveAs(Form("pic/pic%s/PHEMass_%d.png",Trigger[k],i));
		}
	}
	mypdf->On();
	mypdf->Close();
}

