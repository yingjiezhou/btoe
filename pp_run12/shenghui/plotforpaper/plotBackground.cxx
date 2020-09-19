#include "../style.h"
#include "../ptbin.h"

void plotBackground()
{
	setstyle();
	TFile *fJpsi = new TFile("../Background/DataMaker/Jpsiee.root");
	TFile *fU1s = new TFile("../Background/DataMaker/Upsilon1see.root");
	TFile *fU2s = new TFile("../Background/DataMaker/Upsilon2see.root");
	TFile *fU3s = new TFile("../Background/DataMaker/Upsilon3see.root");
	TFile *fRho = new TFile("../Background/DataMaker/Rhoee.root");
	TFile *fOmegaee = new TFile("../Background/DataMaker/Omegaee.root");
	TFile *fOmegaDE = new TFile("../Background/DataMaker/Omegadalitz.root");
	TFile *fPhiee = new TFile("../Background/DataMaker/Phiee.root");
	TFile *fPhiDE = new TFile("../Background/DataMaker/Phidalitz.root");
	TFile *fDrellyan = new TFile("../Background/DataMaker/Drellyan.root");
	Double_t DrellyanCR,SumDrellyanCR=0;
	ifstream indata("../Background/DataMaker/DrellyanCR.txt");
	for(int i=0;i<1200;i++) {indata>>DrellyanCR; SumDrellyanCR=SumDrellyanCR+DrellyanCR;}
	indata.close();
	cout<<SumDrellyanCR/1200.<<endl;
	TFile *fErr = new TFile("../Background/rootfile/BackgroundSpectrumErr.root");
	TH1F *JpsiTwoElectronErr = (TH1F *)fErr->Get("JpsiElectronErr");
	TH1F *UpsilonTwoElectronhigh = (TH1F *)fErr->Get("UpsilonElectronhigh");
	TH1F *UpsilonTwoElectronlow = (TH1F *)fErr->Get("UpsilonElectronlow");
	//TH1F *LvmTwoElectronErr = (TH1F *)fErr->Get("LvmElectronErr");
	TH1F *RhoTwoElectronErr = (TH1F *)fErr->Get("RhoTwoElectronErr");
	TH1F *OmegaTwoElectronErr = (TH1F *)fErr->Get("OmegaTwoElectronErr");
	TH1F *OmegaDalitzdecayErr = (TH1F *)fErr->Get("OmegaDalitzdecayErr");
	TH1F *PhiTwoElectronErr = (TH1F *)fErr->Get("PhiTwoElectronErr");
	TH1F *PhiDalitzdecayErr = (TH1F *)fErr->Get("PhiDalitzdecayErr");
	TFile *fBRErr = new TFile("../Background/rootfile/BackgroundSpectrumBRErr.root");
	//TH1F *LvmTwoElectronBRErr = (TH1F *)fBRErr->Get("LvmElectronBRErr");
	TH1F *RhoTwoElectronBRErr = (TH1F *)fBRErr->Get("RhoTwoElectronBRErr");
	TH1F *OmegaTwoElectronBRErr = (TH1F *)fBRErr->Get("OmegaTwoElectronBRErr");
	TH1F *OmegaDalitzdecayBRErr = (TH1F *)fBRErr->Get("OmegaDalitzdecayBRErr");
	TH1F *PhiTwoElectronBRErr = (TH1F *)fBRErr->Get("PhiTwoElectronBRErr");
	TH1F *PhiDalitzdecayBRErr = (TH1F *)fBRErr->Get("PhiDalitzdecayBRErr");
	
	TF1 *fRapidity = new TF1("fRapidity","pow(cosh(3*x/4./sqrt(log([0]/2./[1]))/(1-pow(x,2)/2./[0]*[2])),-2.)",-5,5);
	fRapidity->SetParameter(0,200);//sqrt(s)
	fRapidity->SetParameter(1,0.938); // nucleon mass
	float Y,dY,ddY,Wt;
	/////////////////////////////////////////////////////////////////////////
	float dNdyJpsi=1.46289e-06*30;//BdNdy

	//fRapidity->SetParameter(2,3.096900);
	//Y=fRapidity->Integral(-5.0,5.0);
	TF1 *fRapidityJpsi = new TF1("fRapidityJpsi","[0]*exp(-0.5*x*x/[1]/[1])",-5,5);
	fRapidityJpsi->SetParameters(1,1.42);

	Y=fRapidityJpsi->Integral(-5.0,5.0);

	TH1F *JpsiTwoElectron    = (TH1F *)fJpsi->Get("PtElectron");
	JpsiTwoElectron->Sumw2();
	TH1F *EtaJpsiTwoElectron    = (TH1F *)fJpsi->Get("EtaElectron");

	EtaJpsiTwoElectron->Scale(2*Y/EtaJpsiTwoElectron->Integral());
	dY=EtaJpsiTwoElectron->Integral(EtaJpsiTwoElectron->FindBin(-0.7),EtaJpsiTwoElectron->FindBin(0.7));
	ddY=dY/JpsiTwoElectron->Integral();
	JpsiTwoElectron->Scale(ddY);
	Wt   =  dNdyJpsi/0.01/1.4;
	JpsiTwoElectron->Scale(Wt);
	JpsiTwoElectron->SetName("JpsiElectron");
	/////////////////////////////////////////////////////////////////////////
	float dNdyUpsilon1s=55.51e-9;

	fRapidity->SetParameter(2,9.46030);
	Y=fRapidity->Integral(-5.0,5.0);

	TH1F *Upsilon1sTwoElectron    = (TH1F *)fU1s->Get("PtElectron");
	Upsilon1sTwoElectron->Sumw2();
	TH1F *EtaUpsilon1sTwoElectron    = (TH1F *)fU1s->Get("EtaElectron");

	EtaUpsilon1sTwoElectron->Scale(2*Y/EtaUpsilon1sTwoElectron->Integral());
	dY=EtaUpsilon1sTwoElectron->Integral(EtaUpsilon1sTwoElectron->FindBin(-0.7),EtaUpsilon1sTwoElectron->FindBin(0.7));
	ddY=dY/Upsilon1sTwoElectron->Integral();
	Upsilon1sTwoElectron->Scale(ddY);
	Wt   =  dNdyUpsilon1s/0.01/1.4;
	Upsilon1sTwoElectron->Scale(Wt);
	/////////
	float dNdyUpsilon2s=16.10e-9;

	fRapidity->SetParameter(2,10.02326);
	Y=fRapidity->Integral(-5.0,5.0);

	TH1F *Upsilon2sTwoElectron    = (TH1F *)fU2s->Get("PtElectron");
	Upsilon2sTwoElectron->Sumw2();
	TH1F *EtaUpsilon2sTwoElectron    = (TH1F *)fU2s->Get("EtaElectron");

	EtaUpsilon2sTwoElectron->Scale(2*Y/EtaUpsilon2sTwoElectron->Integral());
	dY=EtaUpsilon2sTwoElectron->Integral(EtaUpsilon2sTwoElectron->FindBin(-0.7),EtaUpsilon2sTwoElectron->FindBin(0.7));
	ddY=dY/Upsilon2sTwoElectron->Integral();
	Upsilon2sTwoElectron->Scale(ddY);
	Wt   =  dNdyUpsilon2s/0.01/1.4;
	Upsilon2sTwoElectron->Scale(Wt);
	/////////
	float dNdyUpsilon3s=7.27e-9;

	fRapidity->SetParameter(2,10.3552);
	Y=fRapidity->Integral(-5.0,5.0);

	TH1F *Upsilon3sTwoElectron    = (TH1F *)fU3s->Get("PtElectron");
	Upsilon3sTwoElectron->Sumw2();
	TH1F *EtaUpsilon3sTwoElectron    = (TH1F *)fU3s->Get("EtaElectron");

	EtaUpsilon3sTwoElectron->Scale(2*Y/EtaUpsilon3sTwoElectron->Integral());
	dY=EtaUpsilon3sTwoElectron->Integral(EtaUpsilon3sTwoElectron->FindBin(-0.7),EtaUpsilon3sTwoElectron->FindBin(0.7));
	ddY=dY/Upsilon3sTwoElectron->Integral();
	Upsilon3sTwoElectron->Scale(ddY);
	Wt   =  dNdyUpsilon3s/0.01/1.4;
	Upsilon3sTwoElectron->Scale(Wt);
	TH1F *UpsilonTwoElectron = (TH1F *)Upsilon1sTwoElectron->Clone("UpsilonElectron");
	UpsilonTwoElectron->Sumw2();
	UpsilonTwoElectron->Add(Upsilon2sTwoElectron,1);
	UpsilonTwoElectron->Add(Upsilon3sTwoElectron,1);
	/////////////////////////////////////////////////////////////////////////
	float dNdyRho=0.214648*30;//0.22*30;

	fRapidity->SetParameter(2,0.77526);
	Y=fRapidity->Integral(-5.0,5.0);

	TH1F *RhoTwoElectron    = (TH1F *)fRho->Get("PtElectron");
	RhoTwoElectron->Sumw2();
	TH1F *EtaRhoTwoElectron    = (TH1F *)fRho->Get("EtaElectron");

	EtaRhoTwoElectron->Scale(2*Y/EtaRhoTwoElectron->Integral());
	dY=EtaRhoTwoElectron->Integral(EtaRhoTwoElectron->FindBin(-0.7),EtaRhoTwoElectron->FindBin(0.7));
	ddY=dY/RhoTwoElectron->Integral();
	RhoTwoElectron->Scale(ddY);
	Wt   =  dNdyRho*4.72e-5/0.01/1.4;
	RhoTwoElectron->Scale(Wt);
	/////////////////////////////////////////////////////////////////////////
	float dNdyOmega=0.118124*30;//0.13*30;

	fRapidity->SetParameter(2,0.78265);
	Y=fRapidity->Integral(-5.0,5.0);

	TH1F *OmegaDalitzdecay    = (TH1F *)fOmegaDE->Get("PtElectron");
	OmegaDalitzdecay->Sumw2();
	TH1F *EtaOmegaDalitzdecay    = (TH1F *)fOmegaDE->Get("EtaElectron");
	EtaOmegaDalitzdecay->Scale(2*Y/EtaOmegaDalitzdecay->Integral());
	dY=EtaOmegaDalitzdecay->Integral(EtaOmegaDalitzdecay->FindBin(-0.7),EtaOmegaDalitzdecay->FindBin(0.7));
	ddY=dY/OmegaDalitzdecay->Integral();
	OmegaDalitzdecay->Scale(ddY);
	Wt   =  dNdyOmega*7.7e-4/0.01/1.4;
	OmegaDalitzdecay->Scale(Wt);
	/////
	TH1F *OmegaTwoElectron    = (TH1F *)fOmegaee->Get("PtElectron");
	OmegaTwoElectron->Sumw2();
	TH1F *EtaOmegaTwoElectron    = (TH1F *)fOmegaee->Get("EtaElectron");

	EtaOmegaTwoElectron->Scale(2*Y/EtaOmegaTwoElectron->Integral());
	dY=EtaOmegaTwoElectron->Integral(EtaOmegaTwoElectron->FindBin(-0.7),EtaOmegaTwoElectron->FindBin(0.7));
	ddY=dY/OmegaTwoElectron->Integral();
	OmegaTwoElectron->Scale(ddY);
	Wt   =  dNdyOmega*7.36e-5/0.01/1.4;
	OmegaTwoElectron->Scale(Wt);
	/////////////////////////////////////////////////////////////////////////
	float dNdyPhi=0.0146987*30;//0.017*30;

	fRapidity->SetParameter(2,1.019461);
	Y=fRapidity->Integral(-5.0,5.0);

	TH1F *PhiDalitzdecay    = (TH1F *)fPhiDE->Get("PtElectron");
	PhiDalitzdecay->Sumw2();
	TH1F *EtaPhiDalitzdecay    = (TH1F *)fPhiDE->Get("EtaElectron");
	EtaPhiDalitzdecay->Scale(2*Y/EtaPhiDalitzdecay->Integral());
	dY=EtaPhiDalitzdecay->Integral(EtaPhiDalitzdecay->FindBin(-0.7),EtaPhiDalitzdecay->FindBin(0.7));
	ddY=dY/PhiDalitzdecay->Integral();
	PhiDalitzdecay->Scale(ddY);
	Wt   =  dNdyPhi*1.08e-4/0.01/1.4;
	PhiDalitzdecay->Scale(Wt);
	////////////
	TH1F *PhiTwoElectron    = (TH1F *)fPhiee->Get("PtElectron");
	PhiTwoElectron->Sumw2();
	TH1F *EtaPhiTwoElectron    = (TH1F *)fPhiee->Get("EtaElectron");
	EtaPhiTwoElectron->Scale(2*Y/EtaPhiTwoElectron->Integral());
	dY=EtaPhiTwoElectron->Integral(EtaPhiTwoElectron->FindBin(-0.7),EtaPhiTwoElectron->FindBin(0.7));
	ddY=dY/PhiTwoElectron->Integral();
	PhiTwoElectron->Scale(ddY);
	Wt   =  dNdyPhi*2.973e-4/0.01/1.4;
	PhiTwoElectron->Scale(Wt);
	/////////////////////////////////////////////////////////////////////////////////////////////
	TH1F *DrellyanTwoElectron    = (TH1F *)fDrellyan->Get("hDrellYanElectron");
	//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<JpsiTwoElectron->GetNbinsX();i++){
		JpsiTwoElectron->SetBinContent(i+1,JpsiTwoElectron->GetBinContent(i+1)/2/TMath::Pi()/JpsiTwoElectron->GetBinCenter(i+1)/2.);
		JpsiTwoElectron->SetBinError(i+1,JpsiTwoElectron->GetBinError(i+1)/2/TMath::Pi()/JpsiTwoElectron->GetBinCenter(i+1)/2.);
		UpsilonTwoElectron->SetBinContent(i+1,UpsilonTwoElectron->GetBinContent(i+1)/2/TMath::Pi()/UpsilonTwoElectron->GetBinCenter(i+1)/2.);
		UpsilonTwoElectron->SetBinError(i+1,UpsilonTwoElectron->GetBinError(i+1)/2/TMath::Pi()/UpsilonTwoElectron->GetBinCenter(i+1)/2.);
		//LvmTwoElectron->SetBinContent(i+1,LvmTwoElectron->GetBinContent(i+1)/2/TMath::Pi()/LvmTwoElectron->GetBinCenter(i+1)/2.);
		//LvmTwoElectron->SetBinError(i+1,LvmTwoElectron->GetBinError(i+1)/2/TMath::Pi()/LvmTwoElectron->GetBinCenter(i+1)/2.);
		RhoTwoElectron->SetBinContent(i+1,RhoTwoElectron->GetBinContent(i+1)/2/TMath::Pi()/RhoTwoElectron->GetBinCenter(i+1)/2.);
		RhoTwoElectron->SetBinError(i+1,RhoTwoElectron->GetBinError(i+1)/2/TMath::Pi()/RhoTwoElectron->GetBinCenter(i+1)/2.);
		OmegaTwoElectron->SetBinContent(i+1,OmegaTwoElectron->GetBinContent(i+1)/2/TMath::Pi()/OmegaTwoElectron->GetBinCenter(i+1)/2.);
		OmegaTwoElectron->SetBinError(i+1,OmegaTwoElectron->GetBinError(i+1)/2/TMath::Pi()/OmegaTwoElectron->GetBinCenter(i+1)/2.);
		OmegaDalitzdecay->SetBinContent(i+1,OmegaDalitzdecay->GetBinContent(i+1)/2/TMath::Pi()/OmegaDalitzdecay->GetBinCenter(i+1)/2.);
		OmegaDalitzdecay->SetBinError(i+1,OmegaDalitzdecay->GetBinError(i+1)/2/TMath::Pi()/OmegaDalitzdecay->GetBinCenter(i+1)/2.);
		PhiTwoElectron->SetBinContent(i+1,PhiTwoElectron->GetBinContent(i+1)/2/TMath::Pi()/PhiTwoElectron->GetBinCenter(i+1)/2.);
		PhiTwoElectron->SetBinError(i+1,PhiTwoElectron->GetBinError(i+1)/2/TMath::Pi()/PhiTwoElectron->GetBinCenter(i+1)/2.);
		PhiDalitzdecay->SetBinContent(i+1,PhiDalitzdecay->GetBinContent(i+1)/2/TMath::Pi()/PhiDalitzdecay->GetBinCenter(i+1)/2.);
		PhiDalitzdecay->SetBinError(i+1,PhiDalitzdecay->GetBinError(i+1)/2/TMath::Pi()/PhiDalitzdecay->GetBinCenter(i+1)/2.);
		
		JpsiTwoElectron->SetBinError(i+1,sqrt(pow(JpsiTwoElectron->GetBinError(i+1),2)+pow(JpsiTwoElectron->GetBinContent(i+1)-JpsiTwoElectronErr->GetBinContent(i+1),2)));
		//LvmTwoElectron->SetBinError(i+1,sqrt(pow(LvmTwoElectron->GetBinError(i+1),2)+pow(LvmTwoElectron->GetBinContent(i+1)-LvmTwoElectronErr->GetBinContent(i+1),2)+pow(LvmTwoElectron->GetBinContent(i+1)-LvmTwoElectronBRErr->GetBinContent(i+1),2)));
		RhoTwoElectron->SetBinError(i+1,sqrt(pow(RhoTwoElectron->GetBinError(i+1),2)+pow(RhoTwoElectron->GetBinContent(i+1)-RhoTwoElectronErr->GetBinContent(i+1),2)+pow(RhoTwoElectron->GetBinContent(i+1)-RhoTwoElectronBRErr->GetBinContent(i+1),2)));
		OmegaTwoElectron->SetBinError(i+1,sqrt(pow(OmegaTwoElectron->GetBinError(i+1),2)+pow(OmegaTwoElectron->GetBinContent(i+1)-OmegaTwoElectronErr->GetBinContent(i+1),2)+pow(OmegaTwoElectron->GetBinContent(i+1)-OmegaTwoElectronBRErr->GetBinContent(i+1),2)));
		OmegaDalitzdecay->SetBinError(i+1,sqrt(pow(OmegaDalitzdecay->GetBinError(i+1),2)+pow(OmegaDalitzdecay->GetBinContent(i+1)-OmegaDalitzdecayErr->GetBinContent(i+1),2)+pow(OmegaDalitzdecay->GetBinContent(i+1)-OmegaDalitzdecayBRErr->GetBinContent(i+1),2)));
		PhiTwoElectron->SetBinError(i+1,sqrt(pow(PhiTwoElectron->GetBinError(i+1),2)+pow(PhiTwoElectron->GetBinContent(i+1)-PhiTwoElectronErr->GetBinContent(i+1),2)+pow(PhiTwoElectron->GetBinContent(i+1)-PhiTwoElectronBRErr->GetBinContent(i+1),2)));
		PhiDalitzdecay->SetBinError(i+1,sqrt(pow(PhiDalitzdecay->GetBinError(i+1),2)+pow(PhiDalitzdecay->GetBinContent(i+1)-PhiDalitzdecayErr->GetBinContent(i+1),2)+pow(PhiDalitzdecay->GetBinContent(i+1)-PhiDalitzdecayBRErr->GetBinContent(i+1),2)));
	}
	for(int i=0;i<DrellyanTwoElectron->GetNbinsX();i++){
		DrellyanTwoElectron->SetBinContent(i+1,DrellyanTwoElectron->GetBinContent(i+1)/500000./1200.*1.23*SumDrellyanCR/1200./2/TMath::Pi()/DrellyanTwoElectron->GetBinCenter(i+1)/2./1.4/0.02);
		DrellyanTwoElectron->SetBinError(i+1,DrellyanTwoElectron->GetBinError(i+1)/500000./1200.*1.23*SumDrellyanCR/1200./2/TMath::Pi()/DrellyanTwoElectron->GetBinCenter(i+1)/2./1.4/0.02);
	}
	TH1F *LvmTwoElectron = (TH1F *)RhoTwoElectron->Clone("LvmElectron");
	LvmTwoElectron->Sumw2();
	LvmTwoElectron->Add(OmegaTwoElectron,1);
	LvmTwoElectron->Add(OmegaDalitzdecay,1);
	LvmTwoElectron->Add(PhiTwoElectron,1);
	LvmTwoElectron->Add(PhiDalitzdecay,1);
	//DrellyanTwoElectron->Rebin(2.);
	//DrellyanTwoElectron->Scale(1./2.);
	//JpsiTwoElectron->Print("ALL");
	//UpsilonTwoElectron->Print("ALL");
	//LvmTwoElectron->Print("ALL");
	//DrellyanTwoElectron->Print("ALL");
	/*TH1F *JpsiTwoElectronplot=(TH1F *)JpsiTwoElectron->Clone("JpsiTwoElectronplot");
	TH1F *LvmTwoElectronplot=(TH1F *)LvmTwoElectron->Clone("LvmTwoElectronplot");
	for(int i=0;i<JpsiTwoElectron->GetNbinsX();i++){
		JpsiTwoElectronplot->SetBinContent(i+1,JpsiTwoElectron->GetBinContent(i+1));
		JpsiTwoElectronplot->SetBinError(i+1,0);
		LvmTwoElectronplot->SetBinContent(i+1,LvmTwoElectron->GetBinContent(i+1));
		LvmTwoElectronplot->SetBinError(i+1,0);
	}*/
	/////////////////////////////////////////////////////////////////////////////////////////
	//JpsiTwoElectron->Print("ALL");
	//UpsilonTwoElectron->Print("ALL");
	const int NCL=2000;
	//cout<<UpsilonTwoElectron->GetNbinsX()<<endl;
	TH1F *JpsiTwoElectronplot=(TH1F *)JpsiTwoElectron->Clone("JpsiTwoElectronplot");
	float xupsilon[NCL],yupsilon[NCL],yupsilonhigh[NCL],yupsilonlow[NCL],yjpsi[NCL],yjpsierr[NCL];
	for(int i=0;i<NCL;i++){
		xupsilon[i]=UpsilonTwoElectron->GetBinCenter(i+1);
		yupsilon[i]=UpsilonTwoElectron->GetBinContent(i+1);
		yupsilonhigh[i]=UpsilonTwoElectronhigh->GetBinContent(i+1)-UpsilonTwoElectron->GetBinContent(i+1);
		yupsilonlow[i]=UpsilonTwoElectron->GetBinContent(i+1)-UpsilonTwoElectronlow->GetBinContent(i+1);
		yjpsi[i]=JpsiTwoElectron->GetBinContent(i+1);
		yjpsierr[i]=JpsiTwoElectron->GetBinError(i+1);
		JpsiTwoElectronplot->SetBinContent(i+1,JpsiTwoElectron->GetBinContent(i+1));
		JpsiTwoElectronplot->SetBinError(i+1,0);
	}
	TGraphAsymmErrors *GUpsilonTwoElectron=new TGraphAsymmErrors(NCL,xupsilon,yupsilon,0,0,yupsilonlow,yupsilonhigh);
	TGraphErrors *GJpsiTwoElectron=new TGraphErrors(NCL,xupsilon,yjpsi,0,yjpsierr);
	//LvmTwoElectron->Print("ALL");
	TCanvas *cc=Canvas("cc",0.15,0.03,0.15,0.06,0,1,0);
	//cc->SetGrid(1,1);
	float ymin = 1e-13;
	float ymax = 1e-5;
	TH1F *htmp1;
	htmp1 = histo("htmp1",4,2.5,10.,ymin,ymax,"p_{T} (GeV/c)","Ed^{3}#sigma/dp^{3} (mb GeV^{-2} c^{3})",0.075,0.85,0.075,0.98);
	htmp1->SetNdivisions(505,"y");
	GJpsiTwoElectron->SetFillColor(kCyan+2);
	GJpsiTwoElectron->SetFillStyle(3006);
	StyleTGraph(GJpsiTwoElectron,7,kYellow+1,3,0,kMagenta+2,0.9,"E3same");
	Style(JpsiTwoElectronplot,1,kMagenta+2,3,0,kCyan+2,0.9,"lsame");
	//Style(UpsilonTwoElectronhigh,2,kYellow+1,3,0,kMagenta+2,0.9,"lsame");
	//Style(UpsilonTwoElectronlow,7,kYellow+1,3,0,kMagenta+2,0.9,"lsame");
	GUpsilonTwoElectron->SetFillColor(kCyan+2);
	GUpsilonTwoElectron->SetFillStyle(3006);
	StyleTGraphAsy(GUpsilonTwoElectron,7,kYellow+1,3,0,kMagenta+2,0.9,"E3same");
	Style(UpsilonTwoElectron,1,kYellow+1,3,0,kMagenta+2,0.9,"lsame");
	Style(UpsilonTwoElectron,1,kYellow+1,3,0,kMagenta+2,0.9,"lsame");
	Style(LvmTwoElectron,1,kGreen-1,3,0,kYellow+1,0.9,"lsame");
	Style(DrellyanTwoElectron,1,kOrange+1,3,0,kGreen-1,0.9,"lsame");
	//Style(EtaDalitzdecay,1,kGreen+2,5,0,kOrange+1,0.9,"lsame");
	//Style(InclusiveElectron,1,kBlack,5,0,kBlack,0.9,"lsame");
	TLegend *lg= Legend(0.5,0.58,0.9,0.84,0.06);
	lg->AddEntry(JpsiTwoElectronplot,"J/#psi feeddown","l");
	lg->AddEntry(UpsilonTwoElectron,"#varUpsilon feeddown","l");
	lg->AddEntry(DrellyanTwoElectron,"Drell-Yan feeddown","l");
	lg->AddEntry(LvmTwoElectron,"#rho #omega #phi feeddown ","l");
	TLatex tx1;
	tx1.SetTextSize(0.07);
	tx1.SetTextFont(42);
	tx1.DrawLatex(5.8,1.5e-6,"p+p @ #sqrt{s} = 200GeV");
	/*TLine *l1,*l2,*l3,*l4,*l5,*l6,*l7,*l8;
	l3= Line(0,1e-12,0,1e4,1,1,2);
	l6= Line(20,1e-16,20,1e4,1,1,2);
	l7= Line(19,1.05e-16,20,1.05e-16,1,1,2.5);
	for(int g=0;g<19;g++){
		double x11=0, x12=0.4, x21=0, x22=0.17;
		double y1=1e3*Linescale[g];
		double y2=5e2*Linescale[g];
		double x41=19.6, x42=20.0, x51=19.83, x52=20.0;
		l1= Line(x11,y1,x12,y1,1,1,2);
		l2= Line(x21,y2,x22,y2,1,1,2);
		l4= Line(x41,y1,x42,y1,1,1,2);
		l5= Line(x51,y2,x52,y2,1,1,2);
	}*/
	cc->SaveAs("pic/BackgroundSpectrum.png");
	cc->SaveAs("pic/BackgroundSpectrum.pdf");
	cc->SaveAs("pic/BackgroundSpectrum.eps");
	cc->SaveAs("pic/BackgroundSpectrum.gif");
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	TFile* file = new TFile("rootfile/BackgroundSpectrum.root","RECREATE");
	file->cd();
	JpsiTwoElectron->Write();
	UpsilonTwoElectron->Write();
	UpsilonTwoElectronhigh->Write();
	UpsilonTwoElectronlow->Write();
	LvmTwoElectron->Write();
	DrellyanTwoElectron->Write();
	file->Close();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*TF1 *fRapidityJpsi = new TF1("fRapidityJpsi","pow(cosh(3*x/4./sqrt(log([0]/2./[1]))/(1-pow(x,2)/2./[0]*[2])),-2.)",-5,5);
	fRapidityJpsi->SetParameter(0,200);//sqrt(s)
	fRapidityJpsi->SetParameter(1,0.938); // nucleon mass
	fRapidityJpsi->SetParameter(2,3.096900); // meson mass 0.547853
	TCanvas *c=Canvas("c",0.16,0.02,0.15,0.06,0,0,0);
	c->SetGrid(1,1);
	htmp1=histo("htmp1",10,-5,5.,0,2,"Rapidity","dN/dy",0.075,0.85,0.085,0.85);
	htmp1->SetNdivisions(505,"y");
	StyleFun(fRapidity,1,1,3,23,1,0.9,"plfsame");
	fRapidity->SetFillStyle(3008);
	fRapidity->SetFillColor(1);
	StyleFun(fRapidityEta,1,kGreen+2,3,23,kGreen+2,0.9,"plfsame");
	fRapidityEta->SetFillStyle(3008);
	fRapidityEta->SetFillColor(kGreen+2);
	lg = Legend(0.78,0.77,1.18,0.9,0.08);
	lg->AddEntry(fRapidity,"#pi^{0}","plf");
	lg->AddEntry(fRapidityEta,"#eta","plf");
	tx1.DrawLatex(-4.3,1.76,"(b)");
	l3= Line(-5,0,-5,0.2,1,1,2);
	l4= Line(5,0,5,0.2,1,1,2);
	l1= Line(-5,0.1,-4.9,0.1,1,1,2);
	l2= Line(4.9,0.1,5,0.1,1,1,2);
	for(int g=0;g<50;g++){
		double x1=-5+0.2*g;
		double y11=0, y12=0.02;
		l5= Line(x1,y11,x1,y12,1,1,2);
		if(g<10){
			double x2=-5+1*g;
			double y21=0, y22=0.045;
			l6= Line(x2,y21,x2,y22,1,1,2);
		}
	}
	c->SaveAs("pic/RapidityDis.png");
	c->SaveAs("pic/RapidityDis.pdf");
	c->SaveAs("pic/RapidityDis.eps");
	c->SaveAs("pic/RapidityDis.gif");*/
}
