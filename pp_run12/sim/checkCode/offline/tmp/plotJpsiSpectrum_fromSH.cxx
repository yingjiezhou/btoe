#include "../../../style.h"
#include "TF1.h"
void plotJpsiSpectrum()
{
	setstyle();
	const int NBINS = 4000;//PT,Y,Tpperr;
	double PTerr=0.005, Y=0;

	TFile *fTh = new TFile("theory_pp200.root");
	TGraph *gR_th = (TGraph*)fTh->Get("bjpsiratio");
	TFile *fTh_Band = new TFile("fonllCEMband.root");
	TGraph *gR_th_band = (TGraph*)fTh_Band->Get("Graph");
	const int N=43;
	double x[N],y[N];
	for(int j=0;j<N;j++){
		int a=gR_th->GetPoint(j,x[j],y[j]);
		cout<<"cc"<<x[j]<<" "<<y[j]<<endl;
	}
	double xall[N+43],yall[N+43],xup[N],yup[N],xlow[N],ylow[N];
	for(int j=0;j<N+43;j++){
		int d=gR_th_band->GetPoint(j,xall[j],yall[j]);
		//cout<<xall[j]<<" "<<yall[j]<<endl;
	}
	for(int j=0;j<N;j++){
		xup[j]=xall[j];
		yup[j]=yall[j];
		//cout<<"up"<<xup[j]<<" "<<yup[j]<<endl;
	}
	for(int j=0;j<N;j++){
		xlow[j]=xall[85-j];
		ylow[j]=yall[85-j];
		//cout<<"low"<<xlow[j]<<" "<<ylow[j]<<endl;
	}

	double x1[N],y1[N],yerr[N];
	for(int j=0;j<N;j++){
		x1[j]=x[j];
		y1[j]=y[j];
		if((yup[j]-y[j])>(y[j]-ylow[j])) yerr[j]=yup[j]-y[j];
		else yerr[j]=y[j]-ylow[j];
		//cout<<"d"<<x1[j]<<" "<<y1[j]<<" "<<yerr[j]<<endl;
	}
	double x2[N],y2[N],y2err[N];
	for(int j=0;j<N;j++){
		x2[j]=x1[j];
		y2[j]=1-y1[j];
		y2err[j]=yerr[j];
		//cout<<"e"<<x2[j]<<" "<<y2[j]<<" "<<y2err[j]<<endl;
	}

	const int NJpsi=37;//24+15
	double xjpsi[NJpsi],yjpsi[NJpsi],yjpsi1[NJpsi],xjpsierr[NJpsi],yjpsistaterr,yjpsisyserr,yjpsierr[NJpsi],yjpsierr1[NJpsi];
	ifstream PHENIXppcsJpsi;
	PHENIXppcsJpsi.open("jpsispectrumPHENIX.dat");
	for(int j=0;j<22;j++){
		PHENIXppcsJpsi>>xjpsi[j]>>yjpsi[j]>>yjpsistaterr>>yjpsisyserr;
		yjpsi[j]=yjpsi[j]/(2*TMath::Pi()*xjpsi[j])*1e-6;
		yjpsierr[j]=sqrt(pow(yjpsistaterr,2)+pow(yjpsisyserr,2)+0.1*0.1)/(2*TMath::Pi()*xjpsi[j])*1e-6;//0.1 global err
	}
	ifstream STARppcsJpsi;
	STARppcsJpsi.open("jpsispectrumSTAR.dat");
	for(int j=22;j<NJpsi;j++){
		STARppcsJpsi>>xjpsi[j]>>yjpsi[j]>>yjpsistaterr>>yjpsisyserr;
		yjpsi[j]=yjpsi[j]*1e-6;
		yjpsierr[j]=sqrt(pow(yjpsistaterr,2)+pow(yjpsisyserr,2))*1e-6;
	}
	/*for(int j=0;j<NJpsi;j++){
		yjpsi1[j]=yjpsi[j]*xjpsi[j];
		yjpsierr1[j]=yjpsierr[j]*xjpsi[j];
	}*/
	TGraphErrors *GJpsibg=new TGraphErrors(NJpsi,xjpsi,yjpsi,0,yjpsierr);
	TGraphErrors *GJpsi=new TGraphErrors(NJpsi,xjpsi,yjpsi,0,yjpsierr);
	//TGraphErrors *GJpsi1=new TGraphErrors(NJpsi,xjpsi,yjpsi1,0,yjpsierr1);
	GJpsi->SetName("Jpsi");

	/*TF1 *TppJpsi1 = new TF1("TppJpsi1","[0]*x*sqrt(x*x+3.096900*3.096900)*pow(1+[1]*sqrt(x*x+3.096900*3.096900)/[2],-1./[1])",0,40);
	  TppJpsi1->SetParameters(1,0.0926,0.0964);
	//TppJpsi1->SetParameters(TppJpsi->GetParameters());
	TFitResultPtr fitr2;
	fitr2 = GJpsi1->Fit(TppJpsi1,"IN0RS","",0,40);
	double xsec_ext = 0., xsec_extErr = 0.;
	xsec_ext = TppJpsi1->Integral(0,40)*2.*TMath::Pi()/30.;
	xsec_extErr = TppJpsi1->IntegralError(0,40,fitr2->GetParams(),fitr2->GetCovarianceMatrix().GetMatrixArray())*2.*TMath::Pi()/30.;
	cout<<"xsec_ext = "<<xsec_ext<<" xsec_extErr = "<<xsec_extErr<<endl;*/
	TF1 *TppJpsi = new TF1("TppJpsi","[0]*sqrt(x*x+3.096900*3.096900)*pow(1+[1]*sqrt(x*x+3.096900*3.096900)/[2],-1./[1])",0,40);
	TppJpsi->SetParameters(1,0.0926,0.0964);
	TppJpsi->SetParLimits(0,0.,1000);
	GJpsi->Fit(TppJpsi,"IN0R","",0,40);
	TFitResultPtr fitr;
	fitr = GJpsi->Fit(TppJpsi,"IN0RS","",0,40);
	float chisquare=TppJpsi->GetChisquare();
	int ndf=TppJpsi->GetNDF();
	cout<<ndf<<endl;
	cout<<chisquare/(1.0*ndf)<<endl;
	double PTjpsi[NBINS]={0},YERRjpsi[NBINS]={0};
	for(int j=0;j<NBINS;j++) PTjpsi[j]=j*0.01+PTerr;
	fitr->GetConfidenceIntervals(NBINS,1,1,PTjpsi,YERRjpsi,0.6827,false);
	TH1F *FunJpsierr = new TH1F("FunJpsierr","FunJpsierr",NBINS,0,40.);
	TH1F *hFunJpsierr = new TH1F("hFunJpsierr","hFunJpsierr",NBINS,0,40.);
	double dNdyJpsi=0, dNdyJpsiErr=0;
	for(int j=0;j<NBINS;j++){
		Y=TppJpsi->Eval(PTjpsi[j]);
		FunJpsierr->SetBinContent(j+1,Y);
		FunJpsierr->SetBinError(j+1,YERRjpsi[j]);///(chisquare/(1.0*ndf)));

		hFunJpsierr->SetBinContent(j+1,Y*2*TMath::Pi()*hFunJpsierr->GetBinCenter(j+1)/30.);
		hFunJpsierr->SetBinError(j+1,FunJpsierr->GetBinError(j+1)*2*TMath::Pi()*hFunJpsierr->GetBinCenter(j+1)/30.);
	}
	integrateYieldAndErrorh(FunJpsierr,0,40,dNdyJpsi,dNdyJpsiErr);
	cout<<"dNdyJpsi = "<<dNdyJpsi/30.<<endl;
	cout<<"dNdyJpsiErr = "<<dNdyJpsiErr/30.<<endl;

	double xcjpsi[N],ycjpsi[N],ycjpsierr[N],ycjpsid[N],ycjpside[N],ycjpsiderr[N];
	for(int j=0;j<N;j++){
		xcjpsi[j]=x2[j];
		ycjpsi[j]=1e-1*y2[j]*FunJpsierr->GetBinContent(FunJpsierr->FindBin(x2[j]+1e-6));
		ycjpsierr[j]=ycjpsi[j]*sqrt(pow(y2err[j]/y2[j],2)+pow(FunJpsierr->GetBinError(FunJpsierr->FindBin(x2[j]+1e-6))/FunJpsierr->GetBinContent(FunJpsierr->FindBin(x2[j]+1e-6)),2));
		cout<<"cjpsi"<<xcjpsi[j]<<" "<<ycjpsi[j]<<" "<<ycjpsierr[j]<<" "<<" "<<ycjpsierr[j]/ycjpsi[j]<<" "<<y2err[j]/y2[j]<<" "<<FunJpsierr->GetBinError(FunJpsierr->FindBin(x2[j]+1e-6))<<" "<<FunJpsierr->GetBinContent(FunJpsierr->FindBin(x2[j]+1e-6))<<" "<<FunJpsierr->GetBinError(FunJpsierr->FindBin(x2[j]+1e-6))/FunJpsierr->GetBinContent(FunJpsierr->FindBin(x2[j]+1e-6))<<endl;
		ycjpsid[j]=y2[j]*hFunJpsierr->GetBinContent(hFunJpsierr->FindBin(x2[j]+1e-6));
		ycjpsiderr[j]=ycjpsid[j]*sqrt(pow(y2err[j]/y2[j],2)+pow(hFunJpsierr->GetBinError(hFunJpsierr->FindBin(x2[j]+1e-6))/hFunJpsierr->GetBinContent(hFunJpsierr->FindBin(x2[j]+1e-6)),2));
		ycjpside[j]=ycjpsid[j]-ycjpsiderr[j];
		//cout<<"cjpsi"<<xcjpsi[j]<<" "<<ycjpsid[j]<<" "<<ycjpsiderr[j]<<" "<<" "<<ycjpsiderr[j]/ycjpsid[j]<<" "<<y2err[j]/y2[j]<<" "<<hFunJpsierr->GetBinError(hFunJpsierr->FindBin(x2[j]+1e-6))<<" "<<hFunJpsierr->GetBinContent(hFunJpsierr->FindBin(x2[j]+1e-6))<<" "<<hFunJpsierr->GetBinError(hFunJpsierr->FindBin(x2[j]+1e-6))/hFunJpsierr->GetBinContent(hFunJpsierr->FindBin(x2[j]+1e-6))<<endl;
	}

	TGraphErrors *Gcjpsie=new TGraphErrors(N,xcjpsi,ycjpsi,0,ycjpsierr);
	TGraphErrors *Gcjpsibg=new TGraphErrors(N,xcjpsi,ycjpsi,0,0);
	TGraphErrors *Gcjpsi=new TGraphErrors(N,xcjpsi,ycjpsi,0,0);
	TGraphErrors *Gcjpsid=new TGraphErrors(N,xcjpsi,ycjpsid,0,ycjpsiderr);
	TGraphErrors *Gcjpside=new TGraphErrors(N,xcjpsi,ycjpside,0,0);
	Gcjpsie->SetName("Gcjpsi");
	Gcjpsid->SetName("Gcjpsidndydpt");
	Gcjpside->SetName("Gcjpsidndydpte");
	double dNdycJpsi=0, dNdycJpsiErr=0;
	integrateYieldAndError(Gcjpsie,0,22,dNdycJpsi,dNdycJpsiErr);
	cout<<"dNdycJpsi = "<<dNdycJpsi/1e-1<<" "<<endl;
	cout<<"dNdycJpsiErr = "<<dNdycJpsiErr/1e-1<<endl;
	TFile* file = new TFile("rootfile/JpsidNdydpTSpectrumpp.root","RECREATE");
	file->cd();
	hFunJpsierr->Write();
	FunJpsierr->Write();
	TppJpsi->Write();
	GJpsi->Write();
	Gcjpsie->Write();
	Gcjpsid->Write();
	Gcjpside->Write();
	file->Close();
	TCanvas *cc=Canvas("cc",0.155,0.025,0.15,0.06,0,1,0);
	TH1F *htmp=histo("htmp",20,0,20,1e-15,1e-3,"p_{T} (GeV/c)","Bd^{2}#sigma/(2#pip_{T}dp_{T}dy) (mb GeV^{-2} c^{3})",0.075,0.85,0.065,1.15);
	htmp->SetNdivisions(505,"y");
	FunJpsierr->SetFillColor(kYellow+1);
	Style(FunJpsierr,1,kYellow+1,3,0,kYellow+1,0.9,"E4same");
	StyleTGraph(GJpsibg,1,1,3,28,1,2.15,"psame");
	StyleTGraph(GJpsi,1,1,3,34,kGreen+2,1.9,"psame");
	StyleFun(TppJpsi,1,kBlack,3.0,8,kCyan-2,0.9,"lsame");
	Gcjpsie->SetFillColor(kCyan+2);
	Gcjpsie->SetFillStyle(3001);
	StyleTGraph(Gcjpsie,7,kYellow+1,3,0,kMagenta+2,0.9,"E3same");
	StyleTGraph(Gcjpsibg,0,0,0,30,1,2.35,"psame");
	StyleTGraph(Gcjpsi,1,1,3,29,kOrange+1,1.95,"psame");
	TLegend *lg = Legend(0.6,0.64,0.9,0.84,0.055);
	lg->AddEntry(GJpsibg,"inclusive J/#Psi","pl");
	lg->AddEntry(TppJpsi,"Tsallis fit","l");
	lg->AddEntry(Gcjpsibg,"prompt J/#Psi *0.1","pl");
	TLegend *lg = Legend(0.6,0.64,0.9,0.84,0.055);
	lg->AddEntry(GJpsi,"inclusive J/#Psi","pl");
	lg->AddEntry(TppJpsi,"Tsallis fit","l");
	lg->AddEntry(Gcjpsi,"prompt J/#Psi *0.1","pl");
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetTextFont(42);
	tx.DrawLatex(8.99,6e-5,"p+p @ #sqrt{s} = 200 GeV");
	//tx.DrawLatex(13.3,6e-6,"J/#Psi");
	cc->SaveAs("pic/JpsiSpectrum.pdf");
	cc->SaveAs("pic/JpsiSpectrum.gif");
	cc->SaveAs("pic/JpsiSpectrum.png");
	cc->SaveAs("pic/JpsiSpectrum.eps");

	TCanvas *c1=Canvas("c1",0.15,0.03,0.15,0.06,0,0,0);
	TH1F *htmp=histo("htmp",20,0,20,0,0.4,"p_{T} (GeV/c)","(B #rightarrow J/#Psi)/(inclusive J/#Psi)",0.075,0.85,0.065,1.05);
	htmp->SetNdivisions(505,"y");
	StyleTGraphT(gR_th,1,1,3,34,kGreen+2,1.9,"lsame");
	gR_th_band->SetFillColor(kGray+4);
	gR_th_band->SetFillStyle(3001);
	StyleTGraphT(gR_th_band,7,kYellow+1,3,0,kMagenta+2,0.9,"same");
	TLegend *lg = Legend(0.6,0.66,0.9,0.86,0.055);
	lg->AddEntry(gR_th,"FONLL+CEM","l");
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetTextFont(42);
	tx.DrawLatex(8.99,0.35,"p+p @ #sqrt{s} = 200 GeV");
	//tx.DrawLatex(13.3,6e-6,"J/#Psi");
	c1->SaveAs("pic/bJpsi.pdf");
	c1->SaveAs("pic/bJpsi.gif");
	c1->SaveAs("pic/bJpsi.png");
	c1->SaveAs("pic/bJpsi.eps");
	/*TF1 *TppJpsiP = new TF1("TppJpsiP","[0]/pow(exp([1]*x-[2]*x*x)+x/[3],[4])",0,40);
	  TppJpsiP->SetParameters(5.24e-6,-0.32,0.06,2.59,8.44);
	  TH1F *htmp=histo("htmp",20,0,20,1e-15,1e-3,"p_{T} (GeV/c)","Bd^{2}#sigma/(2#pip_{T}dp_{T}dy) (mb GeV^{-2} c^{3})",0.075,0.85,0.065,1.15);
	  htmp->SetNdivisions(505,"y");
	  FunJpsierr->SetFillColor(kYellow+1);
	  Style(FunJpsierr,1,kYellow+1,3,0,kYellow+1,0.9,"E4same");
	  StyleTGraph(GJpsibg,1,1,3,8,1,1.9,"psame");
	  StyleTGraph(GJpsi,1,1,3,8,kCyan-2,1.6,"psame");
	  StyleFun(TppJpsi,1,kBlack,3.0,8,kCyan-2,0.9,"lsame");
	  StyleFun(TppJpsiP,1,kRed,3.0,8,kCyan,0.9,"lsame");
	//Style(hJpsi,1,kBlack,3.0,8,kCyan-2,0.9,"lsame");
	TLegend *lg = Legend(0.43,0.65,0.63,0.8,0.05);
	//lg->AddEntry(TppJpsi,"A(e^(ap_{T}-bp_{T}^{2})+p_{T}/p_{0})^{-n}","l");
	lg->AddEntry(TppJpsiP,"Run08: A(exp(-ap_{T}-bp_{T}^{2})+p_{T}/p_{0})^{-n}","l");
	lg->AddEntry(TppJpsi,"Tsallis fit","l");
	TLatex tx;
	tx.SetTextSize(0.07);
	tx.SetTextFont(42);
	tx.DrawLatex(8.99,6e-5,"p+p @ #sqrt{s} = 200 GeV");
	tx.DrawLatex(13.3,6e-6,"J/#Psi");
	cc->SaveAs("pic/JpsiSpectrumCom08.pdf");
	cc->SaveAs("pic/JpsiSpectrumCom08.gif");
	cc->SaveAs("pic/JpsiSpectrumCom08.png");
	cc->SaveAs("pic/JpsiSpectrumCom08.eps");*/
}
void integrateYieldAndError(TGraphErrors *g, double min, double max, double &yield, double &err){

	yield = 0;
	err = 0;
	for(int i=0;i<g->GetN();i++){
		double x=0,y=0;
		g->GetPoint(i,x,y);
		double ex = 0.5/2.; //g->GetErrorX(i);
		double ey = g->GetErrorY(i);
		if(x<min||x>max) continue;
		yield += y*2.*TMath::Pi()*x*2.*ex;
		cout<<"x = "<<x<<" int y = "<<y*2.*TMath::Pi()*x*2.*ex<<endl;
		double eyi = ey*2.*TMath::Pi()*x*2.*ex;
		//err += eyi*eyi;
		err += eyi;
	}
	//err = sqrt(err);
}
void integrateYieldAndErrorh(TH1F *h, double min, double max, double &yield, double &err){

	yield = 0;
	err = 0;
	for(int i=0;i<h->GetNbinsX();i++){
		double x=h->GetBinCenter(i+1);
		double y=h->GetBinContent(i+1);
		double ex = h->GetBinWidth(i+1)/2.; //g->GetErrorX(i);
		double ey = h->GetBinError(i+1);
		if(x<min||x>max) continue;
		yield += y*2.*TMath::Pi()*x*2.*ex;
		//cout<<"x = "<<x<<" int y = "<<y*2.*TMath::Pi()*x*2.*ex<<endl;
		double eyi = ey*2.*TMath::Pi()*x*2.*ex;
		err += eyi;
		//err += eyi*eyi;
	}
	//err = sqrt(err);
}
