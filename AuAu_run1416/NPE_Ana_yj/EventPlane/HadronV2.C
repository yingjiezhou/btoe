
vector<double>* xVecPtr = new vector<double>();
vector<double>* xVecPtr_er = new vector<double>();
vector<double>* xVal = new vector<double>();
void HadronV2(int save=0){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    gStyle->SetPalette(56);
//////////////////////////////////////////////////////////////////
    char dFile[500];
    char dFile1[500];
    sprintf(dFile,"../production/NPE_Tuples_TuneB12.root");
    //sprintf(dFile,"../TestArea/test.root");
    sprintf(dFile1,"../TestArea/test.root");
    TFile *f_D = new TFile(dFile);
    TFile *f_D1 = new TFile(dFile1);
    hv2=(TH2F*)f_D->Get("hHadronV2gweight");
    hr2=(TH2F*)f_D->Get("hInvResgweight");

    double pub_x[15]={0.297447,0.492561,0.690465,0.889393,1.08894,1.28902,1.48963,1.69072,1.89201,2.09311,2.29375,2.49383,2.69337,2.89233,3.15807};
    double pub_y[15]={0.0229839,0.0453241,0.0674561,0.086957,0.103475,0.117154,0.128465,0.137378,0.143993,0.148979 ,0.152308,0.153868,0.154476,0.153999,0.152728};
    double pub_ye[15]={0.000401199424032488,0.000300817467451609,0.000208109646775444,0.000137036108091992,0.0000777385361323456,
		       0.0000518348338475199,0.0000544679024747603,0.0000755761867257141,
		       0.0000984488191904809,0.000134354057627598,0.000177734287350528,0.000235543127337649,
		       0.00029106763695746,0.000379178275582871,0.000361205247520021};
    double pub_xe[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		       //double pub_x[17]={0.234,0.368,0.56,0.766,0.959,1.119,1.326,1.519,1.726,1.919,2.219,2.62,3.022,3.423,3.974,5.103,7.433};
		       //double pub_y[17]={0.024,0.04,0.066,0.092,0.113,0.129,0.149,0.165,0.18,0.192,0.207,0.219,0.225,0.226,0.222,0.208,0.232};
		       //double pub_ye[17]={0,0,0,0,0,0,0,0.001,0.001,0.001,0.001, 0.002,0.002,0.003,0.006,0.01832};
    TGraphErrors *gr = new TGraphErrors(15,pub_x,pub_y,pub_xe,pub_ye);

    double pub_x1[12]={0.225,
		       0.375,
		       0.525,
		       0.675,
		       0.825,
		       0.975,
		       1.12,
		       1.27,
		       1.42,
		       1.58,
		       1.73,
		       1.88};
    double pub_y1[12]={0.0189,
		       0.0321,
		       0.0466,
		       0.0598,
		       0.07,
		       0.0834,
		       0.0932,
		       0.103,
		       0.112,
		       0.12,
		       0.128,
		       0.136};
    double pub_ye1[12]={0.00009,
			0.00008,
			0.00009,
			0.0001,
			0.0001,
			0.0002,
			0.0002,
			0.0002,
			0.0003,
			0.0003,
			0.0004,
			0.0005};
    double pub_xe1[12]={0,0,0,0,0,0,0,0,0,0,0,0};
    TGraphErrors *gr1 = new TGraphErrors(12,pub_x1,pub_y1,pub_xe1,pub_ye1);
    gr1->SetMarkerColor(kBlue);
    gr1->SetMarkerColor(kBlue);


    gr->SetMarkerColor(kRed);
    gr->SetLineColor(kRed);
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    hv2->RebinX();
    hr2->RebinX();
    hv2->RebinY();
    hr2->RebinY();
    //TH1F *hpiv2 = new TH1F("hpiv2","hpiv2",numPtBins,binning);hpiv2->Sumw2();
    //TH1F *hcorr = new TH1F("hcorr","hcorr",numPtBins,binning);hcorr->Sumw2();
    TH1F *hpiv2 = new TH1F("hpiv2","hpiv2",hv2->GetNbinsX(),0,20);hpiv2->Sumw2();
    TH1F *hcorr = new TH1F("hcorr","hcorr",hv2->GetNbinsX(),0,20);hcorr->Sumw2();
 

    for(int i =1;i<hv2->GetNbinsX()+1;i++){//numPtBins+1;i++){//
	//hv2->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
	//hr2->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
	temp = (TH1F*)hv2->ProjectionY("temp",i,i+1);
	temp1 = (TH1F*)hr2->ProjectionY("temp1",i,i+1);
	//temp->Rebin();
	TF1 *f1 = new TF1("f1","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	temp->Fit(f1,"","",0,TMath::Pi()/2);
	double cor = temp1->GetMean();///sqrt(2);
	hpiv2->SetBinContent(i,f1->GetParameter(1)*cor);
	hcorr->SetBinContent(i,cor);
	hpiv2->SetBinError(i,f1->GetParError(1)*cor);
	f1->Delete();
	temp->Delete();
	temp1->Delete();
    }
    TLegend *leg = new TLegend(0.2,0.55,0.5,0.85);
    leg->AddEntry(gr,"STAR:PhysRevLett.116.062301","PLE");
    leg->AddEntry(hpiv2,"This analysis","PLE");
    TCanvas *c44 = new TCanvas("c44",""); 
    hpiv2->GetYaxis()->SetTitle("#it{v}_{2}^{h}");
    hpiv2->GetYaxis()->SetRangeUser(0,0.4);
    hpiv2->GetXaxis()->SetTitle("#it{p}_{T}^{h}");
    hpiv2->GetXaxis()->SetRangeUser(0,8);
    hpiv2->Draw("PE");
    gr->Draw("same PE");
    //gr1->Draw("same PE");
    leg->Draw("same");
    TCanvas *c11 = new TCanvas("c11",""); 
    hcorr->Draw();
    TCanvas *c111 = new TCanvas("c111",""); 
    hv2->GetXaxis()->SetRangeUser(1,1.2);
    temp = (TH1F*)hv2->ProjectionY("temp");
    TF1 *f1 = new TF1("f1","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
    temp->Rebin();
    temp->Fit(f1,"","",0.2,TMath::Pi()/2-0.2);       
    temp->Draw();
}

void norm(TH1F *h){
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1);
	h->SetBinError(i,err/norm1);
    }
}
