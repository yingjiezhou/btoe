void plot(){
    gROOT->ProcessLine(".x myStyle.C");  
    TGaxis::SetMaxDigits(4);  
//////////////////////////////////////////////////////////////////
    TH2F *h1;
    TH2F *h2;
    TH2F *h3;
    TH1F *h1_x;
    TH1F *h1_y;
    TFile *fi = new TFile("../test.root");
    h1 = (TH2F*) fi->Get("hJpsip");
    h2 = (TH2F*) fi->Get("hJpsip_1");
    h3 = (TH2F*) fi->Get("hJpsip_2");
    h1->Add(h2);
    h1->Add(h3);
    h1->RebinX(10);
    h1->RebinY(10);
    h1_x = (TH1F*)h1->ProjectionX();
    
    h1_y = (TH1F*)h1->ProjectionY();
    TCanvas *c1 = new TCanvas("c1","c1",1000,500);
    c1->Divide(2,1);
    cout << "Number of candidates "<< h1->Integral() << endl;
    c1->cd(1);
    h1_x->Draw();
    c1->cd(2);
    h1_y->Draw();

}
