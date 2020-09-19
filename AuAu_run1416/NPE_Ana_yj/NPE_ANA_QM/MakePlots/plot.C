void plot(){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    char hist[150] = "hBnPhi"; //hBTOWId  // hBnEta  //hBZDist hDsmAdc hEoverP_all    M2  hBPhiDist hBAdc
    char axis[150] = "nHits SMD #phi"; //""Dsm Adc";
//////////////////////////////////////////////////////////////////
    char dFile[500];
    sprintf(dFile,"./test1.root");
    TFile *f_D = new TFile(dFile);
    h1 = (TH1F*) f_D->Get(hist);
    //h1->SetBinContent(1,0);
    //h1y = (TH1F*)h12->ProjectionX(); 
    //h1 = (TH1F*)h12->ProjectionY();
    char dFile1[500];
    sprintf(dFile1,"./test.root");
    TFile *f_D1 = new TFile(dFile1);
    h2 = (TH1F*) f_D1->Get(hist);
    //h2y = (TH1F*)h22->ProjectionX();
    //h2 = (TH1F*)h22->ProjectionY();
    h2->SetName("h2");
    h2->SetLineColor(kRed);
    h2->SetMarkerColor(kRed);

    //h1->SetLineWidth(0.00001);
    //h2->SetLineWidth(0.00001);
    //h1->GetXaxis()->SetRangeUser(-0.07,0.07);
    //h2->GetXaxis()->SetRangeUser(-0.07,0.07);
    //h1->Rebin(20);
    //h2->Rebin(20);
    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
    leg->AddEntry(h1,"LBNL PicoDst","pl");
    leg->AddEntry(h2,"Dev PicoDst","pl");
    leg->SetFillColor(0);
    char label[100];
    double width = h1->GetBinWidth(2);
    sprintf(label,"Normalized Entries",width);
    //h1->Rebin(10);
    //h2->Rebin(10);
    h1->GetYaxis()->SetTitle(label);
    h1->GetXaxis()->SetTitle(axis);
    h2->GetYaxis()->SetTitle(label);
    h2->GetXaxis()->SetTitle(axis);
    TCanvas *c1 = new TCanvas("c1","");
    norm(h1);
    norm(h2);
    h1->Draw("PE");
    h2->Draw("hist same");
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
