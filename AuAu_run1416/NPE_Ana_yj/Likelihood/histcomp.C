


void norm(TH1F *h);
void histcomp(){
    gStyle->SetOptStat(0000);
    auto fi1 = new TFile("/Users/zhouyingjie/Local/PWG/PWGYJ/NPE/RCF_Run14_Ana_yj/Matt/NPE_Ana/Likelihood/root/Ks_pion.root","READ"); // Matt
    auto fi2 = new TFile("/Users/zhouyingjie/Local/PWG/PWGYJ/NPE/RCF_Run14_Ana_yj/Matt/NPE_Ana_yj/Likelihood/root_yj/Ks_pion.root", "READ");

    auto h1 = (TH2F* ) fi1->Get("hFit_pi_0");
    auto h2 = (TH2F* ) fi2->Get("hFit_pi_0");
    h1->SetName("h01_2D_pi_Matt");
    h2->SetName("h01_2D_pi_YJ");

    auto h11 = (TH1F* ) h1->ProjectionY();
    auto h22 = (TH1F* ) h2->ProjectionY();

    TCanvas *picomp= new TCanvas("picomp","pi comp");
    h22->SetLineColor(kRed);
    h22->SetMarkerColor(kRed);
    h22->SetMarkerStyle(24);
    h11->SetMarkerStyle(25);
    TLegend *leg2 = new TLegend(0.6,0.7,0.87,0.9);
    leg2->AddEntry(h11,"Matt sWeighted K_{s}#rightarrow #pi#pi","ep");
    leg2->AddEntry(h22,"YJ sWeighted K_{s}#rightarrow #pi#pi","pe");
    norm(h11);
    norm(h22);
    h11->GetXaxis()->SetTitle("n#sigma_{e}");
    h11->GetYaxis()->SetTitle("A. U.");
    h11->DrawNormalized("PE");
    h22->DrawNormalized("same PE");
    leg2->Draw("same");
}
void norm(TH1F *h){
   double norm1 = h->Integral();
   int bins = h->GetNbinsX();
   for(int i=1; i<bins+1;i++){
       double temp = h->GetBinContent(i);
   if(temp<0)temp=0;
       double err = h->GetBinError(i);
       h->SetBinContent(i,temp/norm1);
       h->SetBinError(i,err/norm1);
   }
}

