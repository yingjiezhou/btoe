void MakeDcaRes(){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(4);  
//////////////////////////////////////////////////////////////////

    int const nVzsDca = 4;
    float const VzEdgeDca[nVzsDca + 1] = { -6., -3., 0, 3., 6.};

    int const nEtasDca = 5;
    float const EtaEdgeDca[nEtasDca + 1] = { -1.0, -0.6, -0.2, 0.2, 0.6, 1.0};

    const Int_t nPtBinsDca = 19;
    const Double_t ptEdgeDca[nPtBinsDca + 1] =
	{
	    0.3, 0.4, 0.5,
	    0.6,  0.7 , 0.8 , 0.9 ,
	    1. , 1.25 , 1.5 , 1.75 , 2.  , 2.25 , 2.5 , 2.75 , 3.0 , 3.5,
	    4.  , 6. , 12.0
	};

    TH1F *PT = new TH1F("PT","",nPtBinsDca,ptEdgeDca);
    TH1F *ETA = new TH1F("ETA","",nEtasDca,EtaEdgeDca);
    TH1F *PV = new TH1F("PV","",nVzsDca,VzEdgeDca);
    TH2F * mh2DcaPtCentPartEtaVzPhi[nEtasDca][nVzsDca][nPtBinsDca];
    for(int i=0;i<nEtasDca;i++){
	for(int j=0;j<nVzsDca;j++){
	    for(int k=0;k<nPtBinsDca;k++){	      
		mh2DcaPtCentPartEtaVzPhi[i][j][k] = new TH2F(Form("mh2DcaPtCentPartEtaVzPhi_0_%i_%i_0_%i",i,j,k),Form("mh2DcaPtCentPartEtaVzPhi_0_%i_%i_0_%i",i,j,k),500,-1,1,500,-1,1);
	    }
	}
    }
    TH2F *h1  = new TH2F("h1","h1",500,-1,1,500,-1,1);
    char dFile1[150];
    sprintf(dFile1,"e_newiso.root");
    TFile *f_D = new TFile(dFile1);
    TChain *ch1 = f_D->Get("Signal_tree");
    float s_eta;
    float s_pt;
    float s_id;
    float s_head;
    float s_parentid;
    float s_gparentid;
    float s_ggparentid;
    float s_parentpt;
    float s_gparentpt;
    float s_ggparentpt;
    float s_dcaxy;
    float s_dcaz;
    float s_vz;
    float s_px1;
    float s_px2;
    float s_ist;
    float s_ssd;
    float s_hft;
    float s_phi;
    float s_iso;
    float s_cen;
    float s_parentphi;
    ch1->SetBranchAddress("sig_pt",&s_pt);
    ch1->SetBranchAddress("event_centrality",&s_cen);
    ch1->SetBranchAddress("sig_dcaxy",&s_dcaxy);
    ch1->SetBranchAddress("sig_dcaz",&s_dcaz);
    ch1->SetBranchAddress("sig_hft",&s_hft);
    ch1->SetBranchAddress("sig_vz",&s_vz);
    ch1->SetBranchAddress("sig_eta",&s_eta);
    ch1->SetBranchAddress("sig_Pxl1Truth",&s_px1);
    ch1->SetBranchAddress("sig_Pxl2Truth",&s_px2);
    ch1->SetBranchAddress("sig_IstTruth",&s_ist);
    ch1->SetBranchAddress("sig_SsdTruth",&s_ssd);
    ch1->SetBranchAddress("sig_id",&s_id);
    ch1->SetBranchAddress("sig_phi",&s_phi);
    ch1->SetBranchAddress("sig_phi2",&s_parentphi);
    ch1->SetBranchAddress("sig_head",&s_head);
    ch1->SetBranchAddress("sig_isiso",&s_iso);
    ch1->SetBranchAddress("sig_parentid",&s_parentid);
    ch1->SetBranchAddress("sig_gparentid",&s_gparentid);
    ch1->SetBranchAddress("sig_ggparentid",&s_ggparentid);
    ch1->SetBranchAddress("sig_parentpt",&s_parentpt);
    ch1->SetBranchAddress("sig_gparentpt",&s_gparentpt);
    ch1->SetBranchAddress("sig_ggparentpt",&s_ggparentpt);
    int num=0;
    for(int i =0;i<ch1->GetEntries();i++){
	ch1->GetEntry(i);
	if(i%100000==0)cout << "on " << i << " of " << ch1->GetEntries() << endl;
	if(!(s_id==3 || s_id==2))continue;
	if(s_hft<1)continue;
	if(s_eta<-1 || s_eta>1)continue;
	if(s_vz<-6 || s_vz>6)continue;
	if(s_pt>12)continue;
	if(s_head==0){
	    int bin1 = ETA->FindBin(s_eta);
	    int bin2 = PV->FindBin(s_vz);
	    int bin3 = PT->FindBin(s_pt);
	    mh2DcaPtCentPartEtaVzPhi[bin1-1][bin2-1][bin3-1]->Fill(s_dcaxy,s_dcaz);
	    h1->Fill(s_dcaxy,s_dcaz);
	    num++;
	}
    }
    cout << "Found " << num << " electrons" << endl;
    TFile f("root/DCAResolutions.root","RECREATE");
    h1->Write("h1");
    for(int i=0;i<nEtasDca;i++){
	for(int j=0;j<nVzsDca;j++){
	    for(int k=0;k<nPtBinsDca;k++){	  
		char save[150];
		sprintf(save, "mh2DcaPtCentPartEtaVzPhi_0_%i_%i_0_%i",i,j,k);
		char save1[150];
		sprintf(save1,"mh2DcaPtCentPartEtaVzPhi_1_%i_%i_0_%i",i,j,k);
		char save2[150];
		sprintf(save2,"mh2DcaPtCentPartEtaVzPhi_2_%i_%i_0_%i",i,j,k);
		mh2DcaPtCentPartEtaVzPhi[i][j][k]->Write(save);
		mh2DcaPtCentPartEtaVzPhi[i][j][k]->Write(save1);
		mh2DcaPtCentPartEtaVzPhi[i][j][k]->Write(save2);
		cout << "Events in " << i << " "  << j << " " << k << " " << mh2DcaPtCentPartEtaVzPhi[i][j][k]->Integral() << endl;
	    }
	}
    }    
    f.Close();
	
 
}//End
void norm(TH1F *h){
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
