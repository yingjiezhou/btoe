void MVACuts(int bin=0){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    gStyle->SetPalette(56);

//////////////////////////////////////////////////////////////////

    int const numPtBins=6;
    double binning[numPtBins+1]={0.6,1,1.5,2.5,3.5,4.5,8.5};

    char dFile[500];
    char dFile1[500];
    sprintf(dFile,"../production/NPE_Tuples_TuneA8.root");
    TFile *f_D = new TFile(dFile);
    ch1 = (TChain*)f_D->Get("PhoE");
    //TChain *ch1 = new TChain("PhoE");                                                 
    //for(int i=0;i<1224;i++){                                                         
    //sprintf(dFile,"../production/1B25DF82A722E08EDA050A65739F5D57_%i.root",i);                              
    //ch1->AddFile(dFile);                                                       
    //}    
    TH1F *hg = new TH1F("hg","hg",numPtBins,binning);
    TH1F *hgws = new TH1F("hgws","hgws",numPtBins,binning);                                                         
    TH1F *h1 = new TH1F("h1","h1",numPtBins,binning);
    TH1F *h1ws = new TH1F("h1ws","h1ws",numPtBins,binning);
    TH1F *h2 = new TH1F("h2","h2",numPtBins,binning);
    TH1F *h2ws = new TH1F("h2ws","h2ws",numPtBins,binning);
    TH1F *h3 = new TH1F("h3","h3",numPtBins,binning);
    TH1F *h3ws = new TH1F("h3ws","h3ws",numPtBins,binning);
    ch1->Project("hg",  "probe_pt","probe_charge*tag_charge<0");
    ch1->Project("hgws",  "probe_pt","probe_charge*tag_charge>0");
    ch1->Project("h1",  "probe_pt","probe_charge*tag_charge<0 && probe_nsige>-1 && probe_nsige<3");
    ch1->Project("h1ws",  "probe_pt","probe_charge*tag_charge>0 && probe_nsige>-1 && probe_nsige<3");
    ch1->Project("h2",  "probe_pt","probe_charge*tag_charge<0 && probe_mva>0.1");
    ch1->Project("h2ws",  "probe_pt","probe_charge*tag_charge>0 && probe_mva>0.1");
    ch1->Project("h3",  "probe_pt","probe_charge*tag_charge<0 && probe_mva>0.1 && probe_nsige>-1 && probe_nsige<3");
    ch1->Project("h3ws",  "probe_pt","probe_charge*tag_charge>0 && probe_mva>0.1 && probe_nsige>-1 && probe_nsige<3");
    hg->Add(hgws,-1);
    h1->Add(h1ws,-1);
    h2->Add(h2ws,-1);
    h3->Add(h3ws,-1);
    TLegend *leg = new TLegend(0.7,0.3,0.9,0.6);
    leg->AddEntry(h1,"-1<n#sigma_{e}<3","pl");
    leg->AddEntry(h2,"#DeltaLL(e-pi)>0","pl");
    leg->AddEntry(h3,"-1<n#sigma_{e}<3 && #DeltaLL(e-pi)>0","pl");
    leg->SetFillColor(0);
    h1->GetYaxis()->SetTitle("Efficiency");
    h1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    h1->GetYaxis()->SetRangeUser(0,1);
    getEff(h1,hg);
    getEff(h2,hg);
    getEff(h3,hg);    
    h3->SetMarkerStyle(26);
    h2->SetMarkerStyle(25);
    TCanvas *c1 = new TCanvas("c1","");
    h1->Draw("PE same");
    h2->Draw("PE same");
    h3->Draw("PE same");
    leg->Draw("same");
  
  

}//End

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
void getEff(TH1F *h,TH1F *g){
  
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	double err = h->GetBinError(i);
	if(temp1>0){
	    h->SetBinContent(i,temp/temp1);
	    h->SetBinError(i,temp/temp1 * sqrt(err*err/temp/temp));
	}else{
	    h->SetBinContent(i,0);
	    h->SetBinError(i,0);
	}
    }
}
