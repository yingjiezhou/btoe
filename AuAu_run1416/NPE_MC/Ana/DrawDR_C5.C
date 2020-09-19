void norm5(TH1F *h);
void DrawDR_C5(){
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};   
    //TFile *f = new TFile("./root_yj/DCA_plots_yj_central5_resubmit.root");
    TFile *f = new TFile("./root_yj/DCA_plots_yj_central5_v3_2_resubmit.root");
    auto dr =(TH2F*)f->Get("dr_eh_all");
    auto h11 = (TH2F*) f->Get("h11");
    dr->SetLineColor(kRed);
    dr->SetMarkerColor(kRed);

    dr->GetXaxis()->SetRangeUser(2,8.5);
    h11->GetXaxis()->SetRangeUser(2,8.5);
    auto dr_0 =(TH1F*) dr->ProjectionY();
    dr_0->SetName("dr_0");
    auto h11_0 =(TH1F*) h11->ProjectionY();
    h11_0->SetName("h11_0"); 
    norm5(dr_0);
    norm5(h11_0);
     dr_0->Rebin(2);
    h11_0->Rebin(2);
    char label[100];
    float low_pt = 2.;
    float high_pt = 8.5;
    sprintf(label,"#it{p}_{T}#in [%1.1f,%1.1f] GeV",low_pt,high_pt);
    TLatex lat2;

    TLegend *leg = new TLegend(0.2,0.2,0.4,0.4);
    leg->AddEntry(h11_0,"Data","lP");
    leg->AddEntry(dr_0,"Embedding","lP");

    TCanvas *c5 = new TCanvas("c5","c5");
    c5->SetLogy();
    dr_0->GetYaxis()->SetRangeUser(1e-5, 1e0);
    dr_0->Draw("PE");
    h11_0->Draw("same PE");
    lat2.DrawLatex(5, 0.1,label);
    leg->Draw("same");
    return ;



    dr->GetXaxis()->SetRangeUser(binning[0],binning[1]);
    h11->GetXaxis()->SetRangeUser(binning[0],binning[1]);
    auto dr_1 =(TH1F*) dr->ProjectionY();
    dr_1->SetName("dr_1");
    auto h11_1 =(TH1F*) h11->ProjectionY();
    h11_1->SetName("h11_1"); 

    dr->GetXaxis()->SetRangeUser(binning[1],binning[2]);
    h11->GetXaxis()->SetRangeUser(binning[1],binning[2]);
    auto dr_2 =(TH1F*) dr->ProjectionY();
    dr_2->SetName("dr_2");
    auto h11_2 =(TH1F*) h11->ProjectionY();
    h11_2->SetName("h11_2"); 

    dr->GetXaxis()->SetRangeUser(binning[2],binning[3]);
    h11->GetXaxis()->SetRangeUser(binning[2],binning[3]);
    auto dr_3 =(TH1F*) dr->ProjectionY();
    dr_3->SetName("dr_3");
    auto h11_3 =(TH1F*) h11->ProjectionY();
    h11_3->SetName("h11_3"); 

    dr->GetXaxis()->SetRangeUser(binning[3],binning[4]);
    h11->GetXaxis()->SetRangeUser(binning[3],binning[4]);
    auto dr_4 =(TH1F*) dr->ProjectionY();
    dr_4->SetName("dr_4");
    auto h11_4 =(TH1F*) h11->ProjectionY();
    h11_4->SetName("h11_4"); 

    dr->GetXaxis()->SetRangeUser(binning[4],binning[5]);
    h11->GetXaxis()->SetRangeUser(binning[4],binning[5]);
    auto dr_5 =(TH1F*) dr->ProjectionY();
    dr_5->SetName("dr_5");
    auto h11_5 =(TH1F*) h11->ProjectionY();
    h11_5->SetName("h11_5"); 

    dr->GetXaxis()->SetRangeUser(binning[5],binning[6]);
    h11->GetXaxis()->SetRangeUser(binning[5],binning[6]);
    auto dr_6 =(TH1F*) dr->ProjectionY();
    dr_6->SetName("dr_6");
    auto h11_6 =(TH1F*) h11->ProjectionY();
    h11_6->SetName("h11_6"); 

    dr->GetXaxis()->SetRangeUser(binning[6],binning[7]);
    h11->GetXaxis()->SetRangeUser(binning[6],binning[7]);
    auto dr_7 =(TH1F*) dr->ProjectionY();
    dr_7->SetName("dr_7");
    auto h11_7 =(TH1F*) h11->ProjectionY();
    h11_7->SetName("h11_7"); 


    dr->GetXaxis()->SetRangeUser(binning[7],binning[8]);
    h11->GetXaxis()->SetRangeUser(binning[7],binning[8]);
    auto dr_8 =(TH1F*) dr->ProjectionY();
    dr_8->SetName("dr_8");
    auto h11_8 =(TH1F*) h11->ProjectionY();
    h11_8->SetName("h11_8"); 

    dr->GetXaxis()->SetRangeUser(binning[8],binning[9]);
    h11->GetXaxis()->SetRangeUser(binning[8],binning[9]);
    auto dr_9 =(TH1F*) dr->ProjectionY();
    dr_9->SetName("dr_9");
    auto h11_9 =(TH1F*) h11->ProjectionY();
    h11_9->SetName("h11_9"); 

    norm5(dr_1);
    norm5(h11_1);
    norm5(dr_2);
    norm5(h11_2);
    norm5(dr_3);
    norm5(h11_3);
    norm5(dr_4);
    norm5(h11_4);
    norm5(dr_5);
    norm5(h11_5);
    norm5(dr_6);
    norm5(h11_6);
    norm5(dr_7);
    norm5(h11_7);
    norm5(dr_8);
    norm5(h11_8);
    norm5(dr_9);
    norm5(h11_9);

    TCanvas *c1 = new TCanvas ("c1","",1800,800);
    gPad->SetLogy();
    c1->Divide(5,2);
    c1->cd(1);
    dr_1->Draw("PE");
    h11_1->Draw("same PE");

   c1->cd(2);
    dr_2->Draw("PE");
    h11_2->Draw("same PE");

   c1->cd(3);
    dr_3->Draw("PE");
    h11_3->Draw("same PE");

   c1->cd(4);
    dr_4->Draw("PE");
    h11_4->Draw("same PE");

   c1->cd(5);
    dr_5->Draw("PE");
    h11_5->Draw("same PE");

   c1->cd(6);
    dr_6->Draw("PE");
    h11_6->Draw("same PE");

   c1->cd(7);
    dr_7->Draw("PE");
    h11_7->Draw("same PE");

    c1->cd(8);
    dr_8->Draw("PE");
    h11_8->Draw("same PE");

    c1->cd(9);
    dr_9->Draw("PE");
    h11_9->Draw("same PE");

}
void norm5(TH1F *h){
    h->GetXaxis()->SetTitle("Decay Radius [cm]");
    h->GetYaxis()->SetTitle("A. U.");
    h->GetYaxis()->SetRangeUser(0.00001,0.4);
    h->Rebin();
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double width = h->GetBinWidth(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1);
	h->SetBinError(i,err/norm1);
    }
}
