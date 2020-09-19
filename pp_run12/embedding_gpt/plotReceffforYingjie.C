#include "style.h"
void plotReceffforYingjie()
{
	setstyle();
	TLatex tx;
	tx.SetTextSize(0.06);
	tx.SetTextFont(42);
	//TCanvas *cc=Canvas("cc",0.14,0.04,0.15,0.06,0,0,0);
	//cc->SetGrid(1,1);
	TH2F *htmp;
	TLegend *lg;
  
  TH1F *hRcptMeeSMD2US_0_pt[];
  TH1F *hRcptMeeSMD2US_2_pt[];
  TH1F *hRcptMeePi0Dalitz[];
  TH1F *hRcptMeeEtaDalitz[];
  TH1F *hRcptMeeGamma[];

  
	TFile *f = new TFile("Eff_Pi0Dalitz.root");
	TH1F *InputNumberPi0Dalitz=(TH1F *)f->Get("hnTotalyCut");
	TH1F *EleNumberPi0Dalitz=(TH1F *)f->Get("RcptPosEleSMD");
	TH2F *RcptMeePi0Dalitz = (TH2F *)f->Get("RcptMeeSMD2");
  for(Int_t ptbin=0; ptbin<numPtBins; ptbin++){
    hRcptMeePi0Dalitz[ptbin] = (TH1F*)RcptMeePi0Dalitz->ProjectionY(Form("hRcptMeePi0Dalitz_%i", ptbin), RcptMeePi0Dalitz->GetXaxis()->FindBin(lowpt[ptbin]), RcptMeePi0Dalitz->GetXaxis()->FindBin(highpt[ptbin]));
  }
	f = new TFile("Eff_EtaDalitz.root");
	TH1F *InputNumberEtaDalitz=(TH1F *)f->Get("hnTotalyCut");
	TH1F *EleNumberEtaDalitz=(TH1F *)f->Get("RcptPosEleSMD");
	TH2F *RcptMeeEtaDalitz = (TH2F *)f->Get("RcptMeeSMD2");
  for(Int_t ptbin=0; ptbin<numPtBins; ptbin++){
    hRcptMeeEtaDalitz[ptbin] = (TH1F*)RcptMeeEtaDalitz->ProjectionY(Form("hRcptMeeEtaDalitz_%i", ptbin), RcptMeeEtaDalitz->GetXaxis()->FindBin(lowpt[ptbin]), RcptMeeEtaDalitz->GetXaxis()->FindBin(highpt[ptbin]));
  }
	f = new TFile("Eff_Gamma.root");
	TH1F *InputNumberGamma=(TH1F *)f->Get("hnTotalyCut");
	TH1F *EleNumberGamma=(TH1F *)f->Get("RcptPosEleSMD");
	TH2F *RcptMeeGamma = (TH2F *)f->Get("RcptMeeSMD2");
  for(Int_t ptbin=0; ptbin<numPtBins; ptbin++){
    hRcptMeeGamma[ptbin] = (TH1F*)RcptMeeGamma->ProjectionY(Form("hRcptMeeGamma_%i", ptbin), RcptMeeGamma->GetXaxis()->FindBin(lowpt[ptbin]), RcptMeeGamma->GetXaxis()->FindBin(highpt[ptbin]));
  }

  
  f = new TFile("npe_tree_May5_11default_gpt_dist.root");
  for(Int_t ptbin=0; ptbin<numPtBins; ptbin++){
    auto ftp = (TH2F*)f->Get("RcptMeeSMD2_0");
    auto hRcptMeeSMD2_0 = (TH1F*)ftp->ProjectionY(Form("RcptMeeSMD2_0_y_%i", ptbin), ftp->GetXaxis()->FindBin(lowpt[ptbin]), ftp->GetXaxis()->FindBin(highpt[ptbin]));
    ftp = (TH2F*)f->Get("RcptMeeSMD2_2");
    auto hRcptMeeSMD2_2 = (TH1F*)ftp->ProjectionY(Form("RcptMeeSMD2_2_y_%i", ptbin), ftp->GetXaxis()->FindBin(lowpt[ptbin]), ftp->GetXaxis()->FindBin(highpt[ptbin]));
    ftp = (TH2F*)f->Get("hRcptMeeSMD2US_0");
    auto hRcptMeeSMD2US_0 = (TH1F*)ftp->ProjectionY(Form("hRcptMeeSMD2US_0_y_%i", ptbin), ftp->GetXaxis()->FindBin(lowpt[ptbin]), ftp->GetXaxis()->FindBin(highpt[ptbin]));
    ftp = (TH2F*)f->Get("hRcptMeeSMD2US_2");
    auto hRcptMeeSMD2US_2 = (TH1F*)ftp->ProjectionY(Form("hRcptMeeSMD2US_0_y_%i", ptbin), ftp->GetXaxis()->FindBin(lowpt[ptbin]), ftp->GetXaxis()->FindBin(highpt[ptbin]));
    hRcptMeeSMD2US_0->Add(hRcptMeeSMD2_0, -1);
    hRcptMeeSMD2US_2->Add(hRcptMeeSMD2_2, -1);
    
    hRcptMeeSMD2US_0->Scale(1./hRcptMeeSMD2US_0->GetEntries());
    hRcptMeeSMD2US_2->Scale(1./hRcptMeeSMD2US_2->GetEntries());
    hRcptMeeSMD2US_0_pt[ptbin] = hRcptMeeSMD2US_0->Clone();
    hRcptMeeSMD2US_2_pt[ptbin] = hRcptMeeSMD2US_0->Clone();
 
  }
  


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
//  EleNumberGamma->Print("ALL");
//	EleNumber->Print("ALL");
	TH1F *hPi0DalitzCon = (TH1F*) EleNumberPi0Dalitz->Clone("hPi0DalitzCon");
	hPi0DalitzCon->Divide(EleNumber);
//	hPi0DalitzCon->Print("ALL");
	TH1F *hEtaDalitzCon = (TH1F*) EleNumberEtaDalitz->Clone("hEtaDalitzCon");
	hEtaDalitzCon->Divide(EleNumber);
	TH1F *hGammaCon = (TH1F*) EleNumberGamma->Clone("hGammaCon");
	hGammaCon->Divide(EleNumber);
//	hGammaCon->Print("ALL");
  TCanvas *cd=Canvas("c",0.15,0.03,0.15,0.06,0,0,0);
  cd->SetGrid(1,1);
  hEtaDalitzCon->GetYaxis()->SetRangeUser(0, 1);
  hEtaDalitzCon->GetXaxis()->SetRangeUser(2, 10);

  Style(hEtaDalitzCon,1,1,2,22,kRed,1.7,"plsame");
  Style(hPi0DalitzCon,1,1,2,8,kGreen+1,1.6,"psame");
  Style(hGammaCon,1,1,2,23,kBlue,1.7,"plsame");
  cd->SaveAs("relative_con.pdf");
  
	TCanvas *c=Canvas("c",0.15,0.03,0.15,0.06,0,0,0);
	c->SetGrid(1,1);
  c->SetLogy();
	TH1F *heff=(TH1F *)RcptMeePi0Dalitz->Clone("heff");
	for(int i=0;i<200;i++){
//    hRcptMeeSMD2US_0->SetBinContent(i+1, hRcptMeeSMD2US_0->GetBinContent(i+1)/(2*TMath::Pi()* hRcptMeeSMD2US_0->FindBin(i+1)*0.1));
//      hRcptMeeSMD2US_2->SetBinContent(i+1, hRcptMeeSMD2US_2->GetBinContent(i+1)/(2*TMath::Pi()* hRcptMeeSMD2US_2->FindBin(i+1)*0.1));
//    hRcptMeeSMD2US_0->SetBinError(i+1, 1e-10);
//    hRcptMeeSMD2US_2->SetBinError(i+1, 1e-10);

		heff->SetBinContent(i+1,RcptMeeGamma->GetBinContent(i+1)*hGammaCon->GetBinContent(i+1)+RcptMeePi0Dalitz->GetBinContent(i+1)*hPi0DalitzCon->GetBinContent(i+1)+RcptMeeEtaDalitz->GetBinContent(i+1)*hEtaDalitzCon->GetBinContent(i+1));
		heff->SetBinError(i+1,sqrt(pow(RcptMeeGamma->GetBinError(i+1)*hGammaCon->GetBinContent(i+1),2)+pow(RcptMeePi0Dalitz->GetBinError(i+1)*hPi0DalitzCon->GetBinContent(i+1),2)+pow(RcptMeeEtaDalitz->GetBinError(i+1)*hEtaDalitzCon->GetBinContent(i+1),2)));
	}
//	TH1F *heffbg=(TH1F *)heff->Clone();
//	heff->Print("ALL");

  RcptMeeGamma->GetXaxis()->SetRangeUser(0, 12);
  RcptMeeGamma->GetYaxis()->SetRangeUser(1e-7, 1e6);

  RcptMeeGamma->GetXaxis()->SetTitle("p_{T}");
//  RcptMeeGamma->GetYaxis()->SetTitle("p_{\rm T}");

//  RcptMeePi0Dalitz->Scale(1e-1);
//  RcptMeeEtaDalitz->Scale(1e-2);
//  RcptMeeGamma->Scale(1e1);
	Style(RcptMeeGamma,1,1,2,22,kRed,1.7,"plsame");
	Style(RcptMeePi0Dalitz,1,1,2,8,kGreen+1,1.6,"psame");
	Style(RcptMeeEtaDalitz,1,1,2,23,kBlue,1.7,"plsame");
	Style(heff,1,1,2,21,kOrange+1,1.5,"plsame");
  Style(hRcptMeeSMD2US_0,1,1,2,23+4,kOrange+1,1.5,"plsame");
  Style(hRcptMeeSMD2US_2,1,1,2,24+4,kOrange+1,1.5,"plsame");

//
//	TF1 *fun = new TF1("feff","[0]/(exp(-(x-[1])/[2])+1)+[3]",0,11.5);
//	fun->SetParameters(1.004,-0.01253,2.158,-0.4732);
//	heff->Fit(fun,"N0RIS","",0,11.5);
  
//	const double *par,*parerr;
//	par = fun->GetParameters();
//	parerr = fun->GetParErrors();
//	fun->SetParameters(par[0],par[1],par[2],par[3]);
//	heff->Fit(fun,"N0RIS","",0,11.5);
//  TFitResultPtr fitr = heff->Fit(fun,"N0RIS","",0. ,11.5);
//  TH1D *Funcerr = new TH1D("Funcerr","",900, 0.,11.5);
//	for(int i=0;i<900;i++){
//		double PTerr=0.005;
//		double PT=i*0.01+PTerr+2.5;
//		double Y=fun->Eval(PT);
//		double Tpperr = fun->IntegralError(PT-PTerr,PT+PTerr,fitr->GetParams(),fitr->GetCovarianceMatrix().GetMatrixArray())/(PTerr*2.);
//		Funcerr->SetBinContent(i+1,Y);
//		Funcerr->SetBinError(i+1,Tpperr);
//	}
//	Funcerr->SetFillColor(kYellow+1);
//	Style(Funcerr,1,kYellow+1,2,0,kYellow+1,1.4,"E4same");
//	StyleFun(fun,1,1,4,8,6,1.44,"lsame");
//  fun->SetRange(0.,11.5);
//	char chh1[50],chh2[50],chh3[50],chh4[50],chh5[50];
//
//	sprintf(chh1,"#chi^{2} / ndf = %6.2f / %d",fun->GetChisquare(),fun->GetNDF());
//	sprintf(chh2,"p_{0} = %5.3e #pm %4.2e",fun->GetParameter(0),fun->GetParError(0));
//	sprintf(chh3,"p_{1} = %5.3f #pm %5.3f",fun->GetParameter(1),fun->GetParError(1));
//	sprintf(chh4,"p_{2} = %5.3f #pm %5.3f",fun->GetParameter(2),fun->GetParError(2));
//	sprintf(chh5,"p_{3} = %5.3f #pm %5.3f",fun->GetParameter(3),fun->GetParError(3));
	TPaveStats *ptstats;
	ptstats= new TPaveStats(0.7,0.17,0.97,0.4,"brNDC");
	ptstats->SetName("stats");
	ptstats->SetBorderSize(2);
	ptstats->SetFillColor(10);
	ptstats->SetTextAlign(12);
	ptstats->SetTextSize(0.03);
	ptstats->SetTextFont(42);
//	TText *text = ptstats->AddText(chh1);
//	text = ptstats->AddText(chh2);
//	text = ptstats->AddText(chh3);
//	text = ptstats->AddText(chh4);
//	text = ptstats->AddText(chh5);
//	ptstats->Draw();

	lg= Legend(0.40,0.6,0.7,0.92,0.05);
	lg->AddEntry(RcptMeeGamma,"#gamma conversion + direct #gamma #rightarrow e^{+}e^{-}#times 10","pl");
	lg->AddEntry(RcptMeePi0Dalitz,"#pi^{0} #rightarrow #gammae^{+}e^{-}#times 1e-1","pl");
	lg->AddEntry(RcptMeeEtaDalitz,"#eta #rightarrow #gammae^{+}e^{-}#times 1e-2","pl");
	lg->AddEntry(heff,"Combined","pl");
  lg->AddEntry(hRcptMeeSMD2US_0,"Data HT0","pl");
  lg->AddEntry(hRcptMeeSMD2US_2,"Data HT2","pl");

  lg->Draw("same");
//	lg->AddEntry(Funcerr,"Fitting uncertainty","f");
//	lg= Legend(0.37,0.2,0.69,0.35,0.045);
//	lg->AddEntry(fun,"Fit to Combined","l");
//	lg->AddEntry(fun,"p_{0}/(e^{-(p_{T}-p_{1})/p_{2}}+1)+p_{3}","");
	tx.DrawLatex(6,1e-2,"p+p @ #sqrt{s} = 200GeV");
	c->SaveAs("PartnerEpT.pdf");
  auto fs  = new TFile("partnerDist.root", "RECREATE");
  fs->cd();
  heff->Write("PartnerCombine.root");
  fs->Close();
}
