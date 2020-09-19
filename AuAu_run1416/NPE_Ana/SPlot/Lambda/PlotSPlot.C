void PlotSPlot(int save=0){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3);  
    gStyle->SetPalette(56);
    gStyle->SetPadRightMargin(0.1);
//////////////////////////////////////////////////////////////////
    char dFile[500];
    sprintf(dFile,"./out.root");
 
    TFile *f_D = new TFile(dFile);
    TChain *ch1 = f_D->Get("Ks_tree_sw");
  
    TH1F *hmass = new TH1F("hmass","hmass",100,0.45,0.55); hmass->Sumw2();
    TH1F *hmass_bkg = new TH1F("hmass_bkg ","hmass_bkg ",100,0.45,0.55); hmass_bkg ->Sumw2();


   
    TH2F *hnsige_p = new TH2F("hnsige_p","hnsige_p",200,0,10,260,-13,13);hnsige_p->Sumw2(); 
    TH2F *hbeta_p = new TH2F("hbeta_p","hbeta_p",200,0,10,50,0.5,2);hbeta_p->Sumw2(); 
    TH1F *hpt = new TH1F("hpt","hpt",20,0,10); hpt->Sumw2();
    TH1F *hpass = new TH1F("hpass","hpass",20,0,10); hpass->Sumw2();
    TH1F *hfail = new TH1F("hfail","hfail",20,0,10); hfail->Sumw2();
    TH1F *hbetaeff = new TH1F("hbetaeff","hbetaeff",20,0,10); hpt->Sumw2();
    TH1F *hnsige = new TH1F("hnsige","hnsige",130,-13,13); hnsige->Sumw2();
    TH1F *hnsigpi = new TH1F("hnsigpi","hnsigpi",130,-13,13); hnsigpi->Sumw2();
    TH1F *hbeta = new TH1F("hbeta","hbeta",50,-0.05,0.05); hbeta->Sumw2();
    TH1F *hbetae = new TH1F("hbetae","hbetae",50,-0.05,0.05); hbetae->Sumw2();
    TH1F *hemc0 = new TH1F("hemc0","hemc0",100,0,5); hemc0->Sumw2();
    TH1F *hzdist = new TH1F("hzdist","hzdist",100,-15,15); hzdist->Sumw2();
    TH1F *hphidist = new TH1F("hphidist","hphidist",100,-0.2,0.2); hphidist->Sumw2();
    TH1F *hnphi = new TH1F("hnphi","hnphi",10,0,10); hnphi->Sumw2();
    TH1F *hneta = new TH1F("hneta","hneta",10,0,10); hneta->Sumw2();
    TH2F *hnsige_p_s = new TH2F("hnsige_p_s","hnsige_p",200,0,10,260,-13,13);hnsige_p_s->Sumw2();
    TH2F *hbeta_p_s = new TH2F("hbeta_p_s","hbeta_p",200,0,10,50,0.5,2);hbeta_p_s->Sumw2();
    TH1F *hpt_s = new TH1F("hpt_s","hpt",20,0,10); hpt_s->Sumw2();
    TH1F *hnsige_s = new TH1F("hnsige_s","hnsige",130,-13,13); hnsige_s->Sumw2();
    TH1F *hnsigpi_s = new TH1F("hnsigpi_s","hnsigpi",130,-13,13); hnsigpi_s->Sumw2();
    TH1F *hbeta_s = new TH1F("hbeta_s","hbeta",50,-0.05,0.05); hbeta_s->Sumw2();
    TH1F *hbetae_s = new TH1F("hbetae_s","hbetae",50,-0.05,0.05); hbetae_s->Sumw2();
    TH1F *hemc0_s = new TH1F("hemc0_s","hemc0",100,0,5); hemc0_s->Sumw2();
    TH1F *hzdist_s = new TH1F("hzdist_s","hzdist",100,-15,15); hzdist_s->Sumw2();
    TH1F *hphidist_s = new TH1F("hphidist_s","hphidist",100,-0.2,0.2); hphidist_s->Sumw2();
    TH1F *hnphi_s = new TH1F("hnphi_s","hnphi",10,0,10); hnphi_s->Sumw2();
    TH1F *hneta_s = new TH1F("hneta_s","hneta",10,0,10); hneta_s->Sumw2();
    TH2F *hnsige_p_sb = new TH2F("hnsige_p_sb","hnsige_p",200,0,10,260,-13,13);hnsige_p_sb->Sumw2();
    TH2F *hbeta_p_sb = new TH2F("hbeta_p_sb","hbeta_p",200,0,10,50,0.5,2);hbeta_p_sb->Sumw2();
    TH1F *hpt_sb = new TH1F("hpt_sb","hpt",20,0,10); hpt_sb->Sumw2();
    TH1F *hnsige_sb = new TH1F("hnsige_sb","hnsige",130,-13,13); hnsige_sb->Sumw2();
    TH1F *hnsigpi_sb = new TH1F("hnsigpi_sb","hnsigpi",130,-13,13); hnsigpi_sb->Sumw2();
    TH1F *hbeta_sb = new TH1F("hbeta_sb","hbeta",50,-0.05,0.05); hbeta_sb->Sumw2();
    TH1F *hbetae_sb = new TH1F("hbetae_sb","hbetae",50,-0.05,0.05); hbetae_sb->Sumw2();
    TH1F *hemc0_sb = new TH1F("hemc0_sb","hemc0",100,0,5); hemc0_sb->Sumw2();
    TH1F *hzdist_sb = new TH1F("hzdist_sb","hzdist",100,-15,15); hzdist_sb->Sumw2();
    TH1F *hphidist_sb = new TH1F("hphidist_sb","hphidist",100,-0.2,0.2); hphidist_sb->Sumw2();
    TH1F *hnphi_sb = new TH1F("hnphi_sb","hnphi",10,0,10); hnphi_sb->Sumw2();
    TH1F *hneta_sb = new TH1F("hneta_sb","hneta",10,0,10); hneta_sb->Sumw2();


    hnsige_p->GetYaxis()->SetTitle("n#sigma_{e}");
    hnsige_p->GetXaxis()->SetTitle("#it{p}");
    hbeta_p->GetYaxis()->SetTitle("1/#beta");
    hbeta_p->GetXaxis()->SetTitle("#it{p}");
    hbeta->GetXaxis()->SetTitle("#Delta#beta_{#pi}");
    hbetae->GetXaxis()->SetTitle("#Delta#beta_{e}");
    hemc0->GetXaxis()->SetTitle("Track #it{p}/EMC0");
    hzdist->GetXaxis()->SetTitle("#Delta#it{z}");
    hphidist->GetXaxis()->SetTitle("#Delta#it{#phi}");
    hneta->GetXaxis()->SetTitle("# hits #eta");
    hnphi->GetXaxis()->SetTitle("# hits #phi");
    hnsige->GetXaxis()->SetTitle("n#sigma_{e}");
    hnsigpi->GetXaxis()->SetTitle("n#sigma_{#pi}");
    hpt->GetXaxis()->SetTitle("#it{p}_{T}");
    float nsige = 0;
    float beta = 0;
    float pt = 0;
    float p = 0;
    float emc0 = 0;
    float nsigpi = 0;
    float zdist = 0;
    float phidist = 0;
    float nphi = 0;
    float neta = 0;
    float sw = 0;
    float mass=0;
    float bkgw =0;
    ch1->SetBranchAddress("probe_nsige",&nsige);
    ch1->SetBranchAddress("probe_beta",&beta);
    ch1->SetBranchAddress("probe_pt",&pt);
    ch1->SetBranchAddress("probe_p",&p);
    ch1->SetBranchAddress("probe_emc0",&emc0);
    ch1->SetBranchAddress("probe_nsigpi",&nsigpi);
    ch1->SetBranchAddress("probe_zdist",&zdist);
    ch1->SetBranchAddress("probe_phidist",&phidist);
    ch1->SetBranchAddress("probe_nphi",&nphi);
    ch1->SetBranchAddress("probe_neta",&neta);
    ch1->SetBranchAddress("sWeight",&sw);
    ch1->SetBranchAddress("sWeight_bkg",&bkgw);    

    ch1->SetBranchAddress("Ks_M",&mass);
    for(int i =0;i<ch1->GetEntries();i++){
	ch1->GetEntry(i);
	if(i%10000==0)cout << "on loop " << i << " of " << ch1->GetEntries() << endl;	   
	hnsige->Fill(nsige,sw);
	hmass->Fill(mass,sw);
	hmass_bkg->Fill(mass,bkgw);
	hnsigpi->Fill(nsigpi,sw);
	hnsige_p->Fill(p,nsige,sw);
	hpt->Fill(pt,sw);   
	if(emc0>0){
	    hemc0->Fill(p/emc0,sw);
	    hzdist->Fill(zdist,sw);
	    hphidist->Fill(phidist,sw);
	}
	if(nphi>0||neta>0){
	    hneta->Fill(neta,sw);
	    hnphi->Fill(nphi,sw);
	}
	int isPion=0;
	double pimass=0;
	if(beta!=0)pimass = p*p*(1/beta/beta-1);
	if(pimass < (0.019+0.003) && pimass > (0.019-0.003))isPion=1;
	if(isPion)hpass->Fill(pt,sw);
	if(!isPion)hfail->Fill(pt,sw);
	
	if(beta!=0){
	    hbeta->Fill((1/beta - 1/(p / TMath::Sqrt(p*p+0.13957018*0.13957018)))/ (1/beta),sw);
	    hbetae->Fill((1/beta - 1/(p / TMath::Sqrt(p*p+0.00051099907*0.00051099907)))/ (1/beta),sw);
	    hbeta_p->Fill(p,1/beta,sw);
	}
	if(fabs(mass-0.4976)<0.01){
	    hnsige_s->Fill(nsige,sw);
	    hnsigpi_s->Fill(nsigpi,sw);
	    hnsige_p_s->Fill(p,nsige,sw);
	    hpt_s->Fill(pt,sw);
	    if(emc0>0){
		hemc0_s->Fill(p/emc0,sw);
		hzdist_s->Fill(zdist,sw);
		hphidist_s->Fill(phidist,sw);
	    }
	    if(nphi>0||neta>0){
		hneta_s->Fill(neta,sw);
		hnphi_s->Fill(nphi,sw);
	    }
	    if(beta!=0){
		hbeta_s->Fill((1/beta - 1/(p / TMath::Sqrt(p*p+0.13957018*0.13957018)))/ (1/beta),sw);
		hbetae_s->Fill((1/beta - 1/(p / TMath::Sqrt(p*p+0.00051099907*0.00051099907)))/ (1/beta),sw);
		hbeta_p_s->Fill(p,1/beta,sw);
	    }
	}
	if((mass<0.4976-0.02 && mass>0.4976-0.03) || (mass>0.4976+0.02 && mass<0.4976+0.03)){
            hnsige_sb->Fill(nsige,sw);
            hnsigpi_sb->Fill(nsigpi,sw);
            hnsige_p_sb->Fill(p,nsige,sw);
            hpt_sb->Fill(pt,sw);
            if(emc0>0){
                hemc0_sb->Fill(p/emc0,sw);
                hzdist_sb->Fill(zdist,sw);
                hphidist_sb->Fill(phidist,sw);
            }
            if(nphi>0||neta>0){
                hneta_sb->Fill(neta,sw);
                hnphi_sb->Fill(nphi,sw);
            }
            if(beta!=0){
                hbeta_sb->Fill((1/beta - 1/(p / TMath::Sqrt(p*p+0.13957018*0.13957018)))/ (1/beta),sw);
                hbetae_sb->Fill((1/beta - 1/(p / TMath::Sqrt(p*p+0.00051099907*0.00051099907)))/ (1/beta),sw);
                hbeta_p_sb->Fill(p,1/beta,sw);
            }
        }
    }

    hnsige_s->Add(hnsige_sb,-1);
    hnsigpi_s->Add(hnsigpi_sb,-1);
    hnsige_p_s->Add(hnsige_p_sb,-1);
    hpt_s->Add(hpt_sb,-1);
    hemc0_s->Add(hemc0_sb,-1);
    hzdist_s->Add(hzdist_sb,-1);
    hphidist_s->Add(hphidist_sb,-1);
    hneta_s->Add(hneta_sb,-1);
    hnphi_s->Add(hnphi_sb,-1);
    hbeta_s->Add(hbeta_sb,-1);
    hbetae_s->Add(hbetae_sb,-1);
    hbeta_p_s->Add(hbeta_p_sb,-1);


    hpt_s->SetLineColor(kRed);
    hpt_s->SetMarkerColor(kRed);

    hnsige_s->SetLineColor(kRed);
    hnsige_s->SetMarkerColor(kRed);
    hnsigpi_s->SetLineColor(kRed);
    hnsigpi_s->SetMarkerColor(kRed);
    hemc0_s->SetLineColor(kRed);
    hemc0_s->SetMarkerColor(kRed);
    hzdist_s->SetLineColor(kRed);
    hzdist_s->SetMarkerColor(kRed);
    hphidist_s->SetLineColor(kRed);
    hphidist_s->SetMarkerColor(kRed);
    hneta_s->SetLineColor(kRed);
    hneta_s->SetMarkerColor(kRed);
    hnphi_s->SetLineColor(kRed);
    hnphi_s->SetMarkerColor(kRed);
    hbeta_s->SetLineColor(kRed);
    hbeta_s->SetMarkerColor(kRed);
    hbetae_s->SetLineColor(kRed);
    hbetae_s->SetMarkerColor(kRed);
    

    norm(hnsige);
    norm(hnsigpi);
    norm(hpt);
    norm(hbeta);
    norm(hbetae);
    norm(hzdist);
    norm(hphidist);
    norm(hneta);
    norm(hnphi);
    norm(hemc0);
    norm(hnsige_s);
    norm(hnsigpi_s);
    norm(hpt_s);
    norm(hbeta_s);
    norm(hbetae_s);
    norm(hzdist_s);
    norm(hphidist_s);
    norm(hneta_s);
    norm(hnphi_s);
    norm(hemc0_s);
    TCanvas *c3 = new TCanvas("c3","c3");
    hmass->Draw();
    hmass_bkg->SetLineColor(kRed);
    hmass_bkg->SetMarkerColor(kRed);
    hmass_bkg->Draw("same");
    TCanvas *c2 = new TCanvas("c2","c2",1200,500);   
    c2->Divide(2,1);
    
    c2->cd(1);
    hnsige_p->Draw("COLZ");
    c2->cd(2);
    hbeta_p->Draw("COLZ");
    //c2->cd(3);
    //hnsige_p_s->Draw("COLZ");
    //c2->cd(4);
    //hbeta_p_s->Draw("COLZ");
    TCanvas *c1 = new TCanvas("c1","c1",1800,1000);
    c1->Divide(5,2);
    c1->cd(1);
    hpt->Draw();
    hpt_s->Draw("same");
    c1->cd(2);
    hnsige->Draw();
    hnsige_s->Draw("same");
    c1->cd(3);
    hnsigpi->Draw();
    hnsigpi_s->Draw("same");
    c1->cd(4);
    hbeta->Draw();
    hbeta_s->Draw("same");
    c1->cd(5);
    hbetae->Draw();
    hbetae_s->Draw("same");
    c1->cd(6);
    hemc0->Draw();
    hemc0_s->Draw("same");
    c1->cd(7);
    hzdist->Draw();
    hzdist_s->Draw("same");
    c1->cd(8);
    hphidist->Draw();
    hphidist_s->Draw("same");
    c1->cd(9);
    hneta->Draw();
    hneta_s->Draw("same");
    c1->cd(10);
    hnphi->Draw();
    hnphi_s->Draw("same");


    for(int i=1;i<hfail->GetNbinsX()+1;i++){
	double temp1 = hfail->GetBinContent(i);
	double temp2 = hpass->GetBinContent(i);	
	double temp11 = hfail->GetBinError(i);
	double temp22 = hpass->GetBinError(i);		
	cout << i << " " << temp1 << " " << temp2 << endl;
	if(temp1>0 || temp2>0){
	    hbetaeff->SetBinContent(i,temp2/(temp1+temp2));
	    hbetaeff->SetBinError(i,sqrt(temp2/(temp1+temp2)/(temp1+temp2)*temp11*temp11 + temp1/(temp1+temp2)/(temp1+temp2)*temp22*temp22));
	}else{
	    hbetaeff->SetBinContent(i,0);
	    hbetaeff->SetBinError(i,0);
	}
    }
    TCanvas *c99 = new TCanvas("c99","eff.");
    hbetaeff->GetXaxis()->SetTitle("#it{p}_{T} [GeV}");
    hbetaeff->GetYaxis()->SetTitle("Efficiency");
    hbetaeff->Draw();

}//End

void getEff(TH1F *h,TH1F *g, int mar, int col){
 
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	if(temp1>0 && temp>0){
	    g->SetBinContent(i,temp/temp1);
	    g->SetBinError(i,temp/temp1*sqrt(1/temp + 1/temp1));
	}else{
	    g->SetBinContent(i,0);
	    g->SetBinError(i,0);
	}
    }
    g->SetMarkerStyle(mar);
    g->SetMarkerColor(col);
    g->SetLineColor(col);
}
void getEff3(TH1F *h,TH1F *g, int mar, int col){
 
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	if(temp1>0)cout << "Pt " << i << " " << temp << " " << temp1 << " " << temp/temp1 <<endl;
	if(temp1>0 && temp>0){
	    g->SetBinContent(i,temp/temp1);
	    g->SetBinError(i,temp/temp1*sqrt(1/temp + 1/temp1));
	}else{
	    g->SetBinContent(i,0);
	    g->SetBinError(i,0);
	}
    }
    g->SetMarkerStyle(mar);
    g->SetMarkerColor(col);
    g->SetLineColor(col);
}
void getEff1(TH1F *h,TH1F *g, int mar, int col){
  
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	if(temp1>0 && temp>0){
	    g->SetBinContent(i,temp/temp1);
	    g->SetBinError(i,temp/temp1*sqrt(1/temp + 1/temp1));
	}else{
	    g->SetBinContent(i,0);
	    g->SetBinError(i,0);
	}
    }
    g->SetMarkerStyle(mar);
    g->SetMarkerColor(col);
    g->SetLineColor(col);
}
void getEff11(TH1F *h,TH1F *g, int mar, int col){
  
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	if(temp1>0 && temp>0){
	    h->SetBinContent(i,temp/temp1);
	    h->SetBinError(i,temp/temp1*sqrt(1/temp + 1/temp1));
	}else{
	    h->SetBinContent(i,0);
	    h->SetBinError(i,0);
	}
    }
    h->SetMarkerStyle(mar);
    h->SetMarkerColor(col);
    h->SetLineColor(col);
}
void getEff2(int rebin,TH1F *h,TH1F *g, int mar, int col, string name){
    if(rebin>0){
	h->Rebin(rebin);
	g->Rebin(rebin);
    }
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	if(temp1>0 && temp>0){
	    g->SetBinContent(i,temp/temp1);
	    g->SetBinError(i,temp/temp1*sqrt(1/temp + 1/temp1));
	}else{
	    g->SetBinContent(i,0);
	    g->SetBinError(i,0);
	}
    }
    g->SetMarkerStyle(mar);
    g->SetMarkerColor(col);
    g->SetLineColor(col);
    g->GetYaxis()->SetRangeUser(0,1);
    g->GetYaxis()->SetTitle("HFT Ratio (Emb. Eff.)");    
    char nn[100];
    sprintf(nn,"%s",name.data());
    g->GetXaxis()->SetTitle(nn);    
}
void getEff2D(TH2F *h,TH2F *g,TH2F *e){
    h->Rebin(5);
    g->Rebin(5);
    int bins = h->GetNbinsX();
    int bins2 = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	for(int j=1; j<bins2+1;j++){
	    double temp = h->GetBinContent(i,j);
	    double temp1 = g->GetBinContent(i,j);
	    if(temp1>0 && temp>0){
		e->SetBinContent(i,j,temp/temp1);
		e->SetBinError(i,j,temp/temp1*sqrt(1/temp + 1/temp1));
	    }else{
		e->SetBinContent(i,j,0);
		e->SetBinError(i,j,0);
	    }
	}
    }
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
