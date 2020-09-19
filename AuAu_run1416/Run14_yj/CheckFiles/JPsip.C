void JPsip(){
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(4);  
//////////////////////////////////////////////////////////////////

    TFile *fi = new TFile("./hist.root");
    h1 = (TH2F*) fi->Get("h2D");
    h2 = (TH2F*) fi->Get("h2D1");
    h3 = (TH2F*) fi->Get("h2Dws");
    h4 = (TH2F*) fi->Get("h2D1ws");
//    h1->RebinY(8);
//    h1->RebinX(8);
    h1->RebinX();
    h1->RebinY(4);
    h2->RebinX();
    h2->RebinY(4);
    h3->RebinX();
    h3->RebinY(4);
    h4->RebinX();
    h4->RebinY(4);    
    cout <<"Bin check " << h1->GetXaxis()->GetBinWidth(1) << " " << h3->GetXaxis()->GetBinWidth(1)<< endl;
//h1->Add(h2);
    //h1->Add(h3);
    
    TCanvas *c1 = new TCanvas("c1","c1");
    c1->Divide(2,1);
    c1->cd(1);
    cout << "Number of candidates "<< h1->Integral() << endl;
    h1->Draw("COLZ");
    c1->cd(2);
    h3->Draw("COLZ");
    TCanvas *c3 = new TCanvas("c3","c3",1000,500);
    c3->Divide(2,1);
    c3->cd(1);
    h1->RebinX(8);
    h2->RebinX(8);
    h3->RebinX(8);
    h4->RebinX(8);
    h1->RebinY();
    h2->RebinY();
    h3->RebinY();
    h4->RebinY();
    h2->SetLineColor(kBlue);
    h2->SetMarkerColor(kBlue);
    h2->SetLineColor(kGreen-2);
    h2->SetMarkerColor(kGreen-2);
    h1->GetYaxis()->SetRangeUser(3.04,3.12);
    h2->GetYaxis()->SetRangeUser(3.04,3.12);
    h3->GetYaxis()->SetRangeUser(3.04,3.12);
    h4->GetYaxis()->SetRangeUser(3.04,3.12);
    h11 = (TH1F*)h1->ProjectionY();
    h12 = (TH1F*)h1->ProjectionX();
    h21 = (TH1F*)h2->ProjectionY();
    h22 = (TH1F*)h2->ProjectionX();
    h31 = (TH1F*)h3->ProjectionY();
    h32 = (TH1F*)h3->ProjectionX();    
    h41 = (TH1F*)h4->ProjectionY();
    h42 = (TH1F*)h4->ProjectionX();
    h21->SetLineColor(kBlue);
    h21->SetMarkerColor(kBlue);
    h31->SetLineColor(kMagenta);
    h31->SetMarkerColor(kMagenta);
    h41->SetLineColor(kRed);
    h41->SetMarkerColor(kRed);
    h22->SetLineColor(kBlue);
    h22->SetMarkerColor(kBlue);
    h32->SetLineColor(kMagenta);
    h32->SetMarkerColor(kMagenta);
    h42->SetLineColor(kRed);
    h42->SetMarkerColor(kRed);
    h11->Draw("PE");
    
    h31->Draw("same PE");
    
    c3->cd(2);
    
    h12->Draw("PE");
    
    h32->Draw("same PE");
    TCanvas *c33 = new TCanvas("c33","c33",1000,500);
    c33->Divide(2,1);
    c33->cd(1);
    h21->Draw("same PE");
    h41->Draw("same PE");
    c33->cd(2);
    h22->Draw("same PE");
    h42->Draw("same PE");
}
