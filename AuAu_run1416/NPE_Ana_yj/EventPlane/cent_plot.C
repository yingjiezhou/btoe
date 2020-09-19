void cent_plot(){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
   
//////////////////////////////////////////////////////////////////
    char dFile[500];
    sprintf(dFile,"./root/histograms.root");
    TFile *f_D = new TFile(dFile);
    h1 = (TH1F*) f_D->Get("centrality_mb");
    h2 = (TH1F*) f_D->Get("centrality_ht");
  
   
    TCanvas *c1 = new TCanvas("c1","");
    norm(h1);
    norm(h2);
    h2->SetLineColor(kRed);
    h2->SetMarkerColor(kRed);    
    h1->Draw();
    h2->Draw("same");
   
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
