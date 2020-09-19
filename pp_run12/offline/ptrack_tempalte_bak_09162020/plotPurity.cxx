#include "../ptbin.h"
#include "../style.h"
void plotPurity()
{
	setstyle();
	TLatex tx;
	tx.SetNDC();
	tx.SetTextFont(42);
	TCanvas *cc=Canvas("cc",0.12,0.036,0.15,0.06,0,1,0);
	TH1F *hInE[trigger],*hPurity[trigger],*hPuritySys[trigger],*hPHE[trigger],*hInEbg[trigger],*hPuritybg[trigger],*hPHEbg[trigger];
	TH2F *htmp;
	TLegend *lg;
	////////////////////////////////
	TFile *f;
	for(int k=1;k<trigger;k++){
		f = new TFile("../RawYield/rootfile/InEdNdpTAndPurity.root");
		//f = new TFile("rootfile/InEdNdpTAndPurityforYingjie.root");
		hPurity[k]=(TH1F *)f->Get(Form("hPurity_%s",Trigger[k]));
		//f = new TFile("rootfile/InEdNdpTAndPurityforYingjieSys.root");
		f = new TFile("../RawYield/rootfile/InEdNdpTAndPurityFit2sigmaSys.root");
		  hPuritySys[k]=(TH1F *)f->Get(Form("hPurity_%s",Trigger[k]));
		  hPuritySys[k]->SetName(Form("hPuritySys_%s",Trigger[k]));
		  hPuritySys[k]->Add(hPurity[k],-1);
		  //hPuritySys[k]->Print("ALL");
		//f = new TFile("rootfile/PurityFitforYingjie.root");
		f = new TFile("../RawYield/rootfile/PurityFit.root");
		for(int i=0; i<nPtBins; i++) {
			if(k==1&&i>7) continue;
			if(k==2&&i<2) continue;
			//if(k==1&&i>5) continue;
			//if(k==2&&i<1) continue;
			TF1 *fpurity= (TF1 *)f->Get(Form("fpurity_%d_%d",i,k));
			cout<<hPurity[k]->GetBinContent(i+1)<<" "<<hPurity[k]->GetBinError(i+1)<<" "<<fpurity->GetParameter(2)/fpurity->GetParameter(1)<<endl;
			hPurity[k]->SetBinError(i+1,sqrt(pow(hPurity[k]->GetBinError(i+1),2)+pow(hPurity[k]->GetBinContent(i+1)*fpurity->GetParameter(2)/fpurity->GetParameter(1),2)));
			hPuritySys[k]->SetBinError(i+1,hPuritySys[k]->GetBinContent(i+1));
			hPuritySys[k]->SetBinContent(i+1,hPurity[k]->GetBinContent(i+1));
			cout<<"ddd"<<hPurity[k]->GetBinContent(i+1)<<" "<<hPurity[k]->GetBinError(i+1)<<" "<<fpurity->GetParameter(2)/fpurity->GetParameter(1)<<endl;
		}
		hPuritybg[k]=(TH1F *)hPurity[k]->Clone();
		hPurity[k]->SetAxisRange(PtMin[k],PtMax[k],"X");
		hPuritybg[k]->SetAxisRange(PtMin[k],PtMax[k],"X");
		//hPurity[k]->SetAxisRange(PtMin[k],PtMaxfyj[k],"X");
		//hPuritybg[k]->SetAxisRange(PtMin[k],PtMaxfyj[k],"X");
	}
	cc->SetLogy(0);
	hPurity[1]->SetAxisRange(2.5,3.9,"X");
	hPuritybg[1]->SetAxisRange(2.5,3.9,"X");
	htmp=histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],20,0,1.4,"p_{T} (GeV/c)","Purity",0.075,0.85,0.07,0.83);
	//htmp=histo2D("htmp",20,PtMinhtmp[0],12,20,0,1.4,"p_{T} (GeV/c)","Purity",0.075,0.85,0.07,0.83);
	Style(hPuritybg[1],1,1,1,8,1,1.9,"psame");
	Style(hPurity[1],1,1,3,8,kYellow+2,1.7,"psame");
	Style(hPuritybg[2],1,1,1,8,1,1.9,"psame");
	Style(hPurity[2],1,1,3,8,kYellow+2,1.7,"psame");
	tx.SetTextSize(0.07);
	tx.DrawLatex(0.5,0.86,"p+p @ #sqrt{s} = 200 GeV");
	tx.SetTextSize(0.065);
	tx.DrawLatex(0.15,0.2,"(b)");
	cc->SaveAs("pic/Purity.png");
	cc->SaveAs("pic/Purity.eps");
}
