void plot(){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
//////////////////////////////////////////////////////////////////
    char dFile[500];
    sprintf(dFile,"./out.root");
    TFile *f_D = new TFile(dFile);
    TTree *tree = (TTree*)f_D->Get("PhoE_tree_sw");
    TH2F *hpair_decayradius = new TH2F("hPhoE_decayradius","",150,0,15,200,-13,13);
    TH2F *hsW = new TH2F("hsW","",200,-13,13,100,-1,2);
    TH1F *hpt = new TH1F("hpt","",20,0,20);
    TH1F *hnsige = new TH1F("hnsige","",200,-13,13);hnsige->Sumw2();
    TH2F *h2D = new TH2F("h2D","",200,13,13,150,0,15);
    TH1F *hnsige1 = new TH1F("hnsige1","",200,-13,13);hnsige1->Sumw2();
    TH1F *hbeta = new TH1F("hbeta","",50,0,3);
    /*tree->Draw("pair_decayradius >> hpair_decayradius");
    tree->Draw("sWeight >> hsW");
    tree->Draw("probe_pt >> hpt", "sWeight");
    tree->Draw("probe_nsige >> hnsige", " sWeight");
    tree->Draw("probe_nsige >> hnsige1");
    tree->Draw("probe_beta >> hbeta", " sWeight");*/
    float weight;
    float bkgweight;
    float mass;
    float pt;
    float p;
    float emc0;
    float nphi;
    float neta;
    float charge;
    float beta;
    float nsige;
    tree->SetBranchAddress("pair_decayradius",&mass) ;
    tree->SetBranchAddress("sWeight",&weight) ;
    tree->SetBranchAddress("sWeight_bkg",&bkgweight) ;
    tree->SetBranchAddress("probe_pt",&pt) ;
    tree->SetBranchAddress("probe_p",&p) ;
    tree->SetBranchAddress("probe_emc0",&emc0) ;
    tree->SetBranchAddress("probe_nphi",&nphi) ;
    tree->SetBranchAddress("probe_neta",&neta) ;
    tree->SetBranchAddress("probe_charge",&charge) ;
    tree->SetBranchAddress("probe_beta",&beta) ;
    tree->SetBranchAddress("probe_nsige",&nsige) ;

    for(int i = 0;i < tree->GetEntries();i++){
	tree->GetEntry(i);
	if(mass>2.25 && mass<3.75){
	    hnsige->Fill(nsige,weight);
	    hnsige1->Fill(nsige);
	    h2D->Fill(nsige,mass);
	    hsW->Fill(nsige,weight);
	    hpair_decayradius->Fill(mass,nsige);
	}
    }

    TCanvas *c1 =new TCanvas("c1","M");
    hpair_decayradius->Draw("COLZ");
    
    TCanvas *c2 =new TCanvas("c2","sW");
    hsW->Draw("COLZ");
    TCanvas *c3 =new TCanvas("c3","hpt");
    h2D->Draw("COLZ");
    TCanvas *c4 =new TCanvas("c4","hnsige");
    hnsige->SetLineColor(kRed);
    hnsige->Draw();
    hnsige1->Draw("same");
   TCanvas *c5 =new TCanvas("c5","hbeta");
    hbeta->Draw();
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
