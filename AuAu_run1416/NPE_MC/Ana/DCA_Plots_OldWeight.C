Double_t func(Double_t *x, Double_t *par){
    Double_t arg = 0;
    Double_t val = 0;
    if(par[2]!=0 && par[1]!=1){
	arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
	val = par[0]*sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1]));//exp(arg*(1/(1-par[1])));
    }
    return val;
}
Double_t func1(Double_t *x, Double_t *par){
    Double_t arg = 0;
    Double_t val = 0;
    if(par[2]!=0 && par[1]!=1){
	arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
	val = par[0]*(sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1])));//exp(arg*(1/(1-par[1])));
    }
    return val;
}
Double_t func2(Double_t *x, Double_t *par){
    Double_t arg = 0;
    Double_t val = 0;
    if(par[2]!=0 && par[1]!=1){
	arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
	val = par[0]*(sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1])));//exp(arg*(1/(1-par[1])));
    }
    Double_t arg1 = 0;
    if(par[4]!=0 && par[5]!=1){
	arg1 = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[5]*(1-par[4]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
	val += par[3]*sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg1,-1/(1-par[4]));//exp(arg*(1/(1-par[1])));
    }
    return val;
}


void DCA_Plots(int save = 1 , int weight_data=1){ 
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");    
    TGaxis::SetMaxDigits(3);  
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

    TFile *fi = new TFile("root/Pi0_Gamma_Ratio.root");
    pi0_weights = (TH1F*) fi->Get("pi0_weights");
    gamma_weights = (TH1F*) fi->Get("gamma_weights");
    //TFile *fi = new TFile("root/Weight.root");
    //pi0_weights = (TH1F*) fi->Get("Pi");
    //gamma_weights = (TH1F*) fi->Get("gamma_PYT");


    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    TH1F *comp = new TH1F("comp","",numPtBins,binning);   
    TH1F *comp1 = new TH1F("comp1","",numPtBins,binning);   
    TH1F *comp2 = new TH1F("comp2","",numPtBins,binning);   
    TH1F *comp3 = new TH1F("comp3","",numPtBins,binning);   
    TH1F *comp4 = new TH1F("comp4","",numPtBins,binning);    
    TH1F *comp5 = new TH1F("comp5","",numPtBins,binning);  
    TH1F *check1 = new TH1F("check1","",numPtBins,binning);   
    TH1F *check2 = new TH1F("check2","",numPtBins,binning);   
    TH1F *check3 = new TH1F("check3","",numPtBins,binning);   
    TH1F *check4 = new TH1F("check4","",numPtBins,binning);    
    TH1F *check5 = new TH1F("check5","",numPtBins,binning);  
    TH1F *corr1 = new TH1F("corr1","",numPtBins,binning);   
    TH1F *corr2 = new TH1F("corr2","",numPtBins,binning);   
    TH1F *corr3 = new TH1F("corr3","",numPtBins,binning);   
    TH1F *corr4 = new TH1F("corr4","",numPtBins,binning);    
    TH1F *corr5 = new TH1F("corr5","",numPtBins,binning);  
    if(save){	
	char dFile[500];
	sprintf(dFile,"All_Decays_newiso_full.root");
	TFile *f_D = new TFile(dFile);
	TChain *ch1 = f_D->Get("Signal_tree");
        char dFile3[500];
        sprintf(dFile3,"MC_newiso_full.root");
        TFile *f_D3 = new TFile(dFile3);
	TChain *ch11 = f_D3->Get("EH");
	char dFile1[500];
	sprintf(dFile1,"../../NPE_Ana/production/NPE_Tuples_TuneB8.root");
	TFile *f_D1 = new TFile(dFile1);
	ch3 = (TChain*)f_D1->Get("PhoE");
	ch33 = (TChain*)f_D1->Get("Signal");

	TH2F *dcapt = new TH2F("dcapt","dcapt",2*260,-12,1,85,0,8.5);dcapt->Sumw2();
	TH2F *dcapt_ni = new TH2F("dcapt_ni","dcapt_ni",2*260,-12,1,85,0,8.5);dcapt_ni->Sumw2();
	TH2F *dcapt_all = new TH2F("dcapt_all","dcapt_all",2*260,-12,1,85,0,8.5);dcapt_all->Sumw2();
	TH2F *dcapt_eta = new TH2F("dcapt_eta","dcapt_eta",2*260,-12,1,85,0,8.5);dcapt_eta->Sumw2();
	TH2F *dcapt_pi0 = new TH2F("dcapt_pi0","dcapt_pi0",2*260,-12,1,85,0,8.5);dcapt_pi0->Sumw2();
	TH2F *dcapt_pi0_gamma = new TH2F("dcapt_pi0_gamma","dcapt_pi0_gamma",2*260,-12,1,85,0,8.5);dcapt_pi0_gamma->Sumw2();
	TH2F *dcapt_eta_gamma = new TH2F("dcapt_eta_gamma","dcapt_eta_gamma",2*260,-12,1,85,0,8.5);dcapt_eta_gamma->Sumw2();
	TH2F *dcapt_gamma = new TH2F("dcapt_gamma","dcapt_gamma",2*260,-12,1,85,0,8.5);dcapt_gamma->Sumw2();



	TH2F *dcapt_all_nw = new TH2F("dcapt_all_nw","dcapt_all_nw",2*260,-12,1,85,0,8.5);dcapt_all_nw->Sumw2();
	TH2F *dcapt_eta_nw = new TH2F("dcapt_eta_nw","dcapt_eta_nw",2*260,-12,1,85,0,8.5);dcapt_eta_nw->Sumw2();
	TH2F *dcapt_pi0_nw = new TH2F("dcapt_pi0_nw","dcapt_pi0_nw",2*260,-12,1,85,0,8.5);dcapt_pi0_nw->Sumw2();
	TH2F *dcapt_pi0_gamma_nw = new TH2F("dcapt_pi0_gamma_nw","dcapt_pi0_gamma_nw",2*260,-12,1,85,0,8.5);dcapt_pi0_gamma_nw->Sumw2();
	TH2F *dcapt_eta_gamma_nw = new TH2F("dcapt_eta_gamma_nw","dcapt_eta_gamma_nw",2*260,-12,1,85,0,8.5);dcapt_eta_gamma_nw->Sumw2();
	TH2F *dcapt_gamma_nw = new TH2F("dcapt_gamma_nw","dcapt_gamma_nw",2*260,-12,1,85,0,8.5);dcapt_gamma_nw->Sumw2();

	TH2F *dcapt_all_nw_ni = new TH2F("dcapt_all_nw_ni","dcapt_all_nw_ni",2*260,-12,1,85,0,8.5);dcapt_all_nw_ni->Sumw2();
	TH2F *dcapt_eta_nw_ni = new TH2F("dcapt_eta_nw_ni","dcapt_eta_nw_ni",2*260,-12,1,85,0,8.5);dcapt_eta_nw_ni->Sumw2();
	TH2F *dcapt_pi0_nw_ni = new TH2F("dcapt_pi0_nw_ni","dcapt_pi0_nw_ni",2*260,-12,1,85,0,8.5);dcapt_pi0_nw_ni->Sumw2();
	TH2F *dcapt_pi0_gamma_nw_ni = new TH2F("dcapt_pi0_gamma_nw_ni","dcapt_pi0_gamma_nw_ni",2*260,-12,1,85,0,8.5);dcapt_pi0_gamma_nw_ni->Sumw2();
	TH2F *dcapt_eta_gamma_nw_ni = new TH2F("dcapt_eta_gamma_nw_ni","dcapt_eta_gamma_nw_ni",2*260,-12,1,85,0,8.5);dcapt_eta_gamma_nw_ni->Sumw2();
	TH2F *dcapt_gamma_nw_ni = new TH2F("dcapt_gamma_nw_ni","dcapt_gamma_nw_ni",2*260,-12,1,85,0,8.5);dcapt_gamma_nw_ni->Sumw2();



	TH2F *dcapt_all_nw1 = new TH2F("dcapt_all_nw1","dcapt_all_nw1",2*260,-12,1,85,0,8.5);dcapt_all_nw1->Sumw2();
	TH2F *dcapt_eta_nw1 = new TH2F("dcapt_eta_nw1","dcapt_eta_nw1",2*260,-12,1,85,0,8.5);dcapt_eta_nw1->Sumw2();
	TH2F *dcapt_pi0_nw1 = new TH2F("dcapt_pi0_nw1","dcapt_pi0_nw1",2*260,-12,1,85,0,8.5);dcapt_pi0_nw1->Sumw2();
	TH2F *dcapt_pi0_gamma_nw1 = new TH2F("dcapt_pi0_gamma_nw1","dcapt_pi0_gamma_nw1",2*260,-12,1,85,0,8.5);dcapt_pi0_gamma_nw1->Sumw2();
	TH2F *dcapt_eta_gamma_nw1 = new TH2F("dcapt_eta_gamma_nw1","dcapt_eta_gamma_nw1",2*260,-12,1,85,0,8.5);dcapt_eta_gamma_nw1->Sumw2();
	TH2F *dcapt_gamma_nw1 = new TH2F("dcapt_gamma_nw1","dcapt_gamma_nw1",2*260,-12,1,85,0,8.5);dcapt_gamma_nw1->Sumw2();


	TH2F *dcapt_eh_gamma = new TH2F("dcapt_eh_gamma","dcapt_eh_gamma",2*260,-12,1,85,0,8.5);dcapt_eh_gamma->Sumw2();
	TH2F *dcapt_eh_eta = new TH2F("dcapt_eh_eta","dcapt_eh_eta",2*260,-12,1,85,0,8.5);dcapt_eh_eta->Sumw2();
	TH2F *dcapt_eh_pi0 = new TH2F("dcapt_eh_pi0","dcapt_eh_pi0",2*260,-12,1,85,0,8.5);dcapt_eh_pi0->Sumw2();
	TH2F *dcapt_eh_eta_gamma = new TH2F("dcapt_eh_eta_gamma","dcapt_eh_eta_gamma",2*260,-12,1,85,0,8.5);dcapt_eh_eta_gamma->Sumw2();
	TH2F *dcapt_eh_pi0_gamma = new TH2F("dcapt_eh_pi0_gamma","dcapt_eh_pi0_gamma",2*260,-12,1,85,0,8.5);dcapt_eh_pi0_gamma->Sumw2();
	TH2F *dcapt_eh_all = new TH2F("dcapt_eh_all","dcapt_eh_all",2*260,-12,1,85,0,8.5);dcapt_eh_all->Sumw2();
	TH2F *dcapt_eh_all_m1 = new TH2F("dcapt_eh_all_m1","dcapt_eh_all_m1",2*260,-12,1,85,0,8.5);dcapt_eh_all_m1->Sumw2();
	TH2F *dcapt_eh_all_m2 = new TH2F("dcapt_eh_all_m2","dcapt_eh_all_m2",2*260,-12,1,85,0,8.5);dcapt_eh_all_m2->Sumw2();
	TH2F *dcapt_eh_all_m3 = new TH2F("dcapt_eh_all_m3","dcapt_eh_all_m3",2*260,-12,1,85,0,8.5);dcapt_eh_all_m3->Sumw2();
	TH2F *dcapt_eh_all_m4 = new TH2F("dcapt_eh_all_m4","dcapt_eh_all_m4",2*260,-12,1,85,0,8.5);dcapt_eh_all_m4->Sumw2();
	
        TH2F *dcapt_all_m1 = new TH2F("dcapt_all_m1","dcapt_all_m1",2*260,-12,1,85,0,8.5);dcapt_all_m1->Sumw2();
        TH2F *dcapt_all_m2 = new TH2F("dcapt_all_m2","dcapt_all_m2",2*260,-12,1,85,0,8.5);dcapt_all_m2->Sumw2();
        TH2F *dcapt_all_m3 = new TH2F("dcapt_all_m3","dcapt_all_m3",2*260,-12,1,85,0,8.5);dcapt_all_m3->Sumw2();
        TH2F *dcapt_all_m4 = new TH2F("dcapt_all_m4","dcapt_all_m4",2*260,-12,1,85,0,8.5);dcapt_all_m4->Sumw2();

	TH2F *dr_eh_gamma = new TH2F("dr_eh_gamma","dr_eh_gamma",85,0,8.5,100,0,10);dr_eh_gamma->Sumw2();
	TH2F *dr_eh_eta = new TH2F("dr_eh_eta","dr_eh_eta",85,0,8.5,100,0,10);dr_eh_eta->Sumw2();
	TH2F *dr_eh_pi0 = new TH2F("dr_eh_pi0","dr_eh_pi0",85,0,8.5,100,0,10);dr_eh_pi0->Sumw2();
	TH2F *dr_eh_eta_gamma = new TH2F("dr_eh_eta_gamma","dr_eh_eta_gamma",85,0,8.5,100,0,10);dr_eh_eta_gamma->Sumw2();
	TH2F *dr_eh_pi0_gamma = new TH2F("dr_eh_pi0_gamma","dr_eh_pi0_gamma",85,0,8.5,100,0,10);dr_eh_pi0_gamma->Sumw2();
	TH2F *dr_eh_all = new TH2F("dr_eh_all","dr_eh_all",85,0,8.5,100,0,10);dr_eh_all->Sumw2();

	TH2F *mass_eh_gamma = new TH2F("mass_eh_gamma","mass_eh_gamma",85,0,8.5,150,0,0.015);mass_eh_gamma->Sumw2();
	TH2F *mass_eh_eta = new TH2F("mass_eh_eta","mass_eh_eta",85,0,8.5,150,0,0.015);mass_eh_eta->Sumw2();
	TH2F *mass_eh_pi0 = new TH2F("mass_eh_pi0","mass_eh_pi0",85,0,8.5,150,0,0.015);mass_eh_pi0->Sumw2();
	TH2F *mass_eh_eta_gamma = new TH2F("mass_eh_eta_gamma","mass_eh_eta_gamma",85,0,8.5,150,0,0.015);mass_eh_eta_gamma->Sumw2();
	TH2F *mass_eh_pi0_gamma = new TH2F("mass_eh_pi0_gamma","mass_eh_pi0_gamma",85,0,8.5,150,0,0.015);mass_eh_pi0_gamma->Sumw2();
	TH2F *mass_eh_all = new TH2F("mass_eh_all","mass_eh_all",85,0,8.5,150,0,0.015);mass_eh_all->Sumw2();

	TH2F *h1 = new TH2F("h1","h1",2*260,-12,1,85,0,8.5);
	TH2F *h2 = new TH2F("h2","h2",2*260,-12,1,85,0,8.5);
	TH2F *h11 = new TH2F("h11","h11",85,0,8.5,100,0,10);
	TH2F *h22 = new TH2F("h22","h22",85,0,8.5,100,0,10);	
	TH2F *h111 = new TH2F("h111","h111",85,0,8.5,150,0,0.015);
	TH2F *h222 = new TH2F("h222","h222",85,0,8.5,150,0,0.015);	
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
	float s_hft;
	float s_phi;
	float s_iso;
	float s_px1;
	float s_px2;
	float s_ist;
	float s_ssd;
	float s_cen;
	float s_parentphi;

	double num_e = 1288444;
	int num_eta = 200e3;//750E3;
	int num_pi0 = 200e3;//1280E3;
	double num_gamma = 16.78E6;
//======================================================================     
	ch3->Project("h1","probe_pt:log(abs(probe_dca)+0.000000001)","probe_charge*tag_charge<0 && probe_pt>0.6  &&  probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && abs(1/tag_beta-1)<0.025 && pair_dca<1")  ;
	ch3->Project("h2","probe_pt:log(abs(probe_dca)+0.000000001)","probe_charge*tag_charge>0 && probe_pt>0.6  &&  probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && abs(1/tag_beta-1)<0.025 && pair_dca<1")  ;
	ch3->Project("h11","pair_decayradius:probe_pt","probe_charge*tag_charge<0 && probe_pt>0 &&  probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && pair_dca<1")  ;
	ch3->Project("h22","pair_decayradius:probe_pt","probe_charge*tag_charge>0 && probe_pt>0 &&  probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && pair_dca<1")  ;
	ch3->Project("h111","PhoE_M:probe_pt","probe_charge*tag_charge<0 && probe_pt>0 &&  probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && pair_dca<1")  ;
	ch3->Project("h222","PhoE_M:probe_pt","probe_charge*tag_charge>0 && probe_pt>0 &&  probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && pair_dca<1")  ;
	h1->Add(h2,-1);
	h11->Add(h22,-1);
	h111->Add(h222,-1);
//======================================================================
	ch1->SetBranchAddress("sig_pt",&s_pt);
	ch1->SetBranchAddress("sig_Pxl1Truth",&s_px1);
	ch1->SetBranchAddress("sig_Pxl2Truth",&s_px2);
	ch1->SetBranchAddress("sig_IstTruth",&s_ist);
	ch1->SetBranchAddress("sig_SsdTruth",&s_ssd);
	ch1->SetBranchAddress("event_centrality",&s_cen);
	ch1->SetBranchAddress("sig_dca",&s_dcaxy);
	ch1->SetBranchAddress("sig_hft",&s_hft);
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

	for(int i =0;i<ch1->GetEntries();i++){
	    ch1->GetEntry(i);
	    if(i%100000==0)cout << "on " << i << " of " << ch1->GetEntries() << endl;
	    if(!(s_id==3 || s_id==2))continue;
	    if(s_pt<0.6)continue;
	    if(s_hft<1)continue;
	 
	    double ww = 1;
	    double ww2 =1;
	    double prox = 0;
	    //============================================
            //Get Weights
            //============================================	 
	    if(s_head == 7 && s_gparentid==0){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		prox = s_parentpt;
		if(s_parentpt<0.35)s_parentpt=0.35;	      
		int bin = pi0_weights->FindBin(s_parentpt);
                ww = pi0_weights->GetBinContent(bin);
		ww2*=0.01174; 	
	    } else if(s_head == 17 && s_gparentid==0){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		if(s_parentpt<0.35)s_parentpt=0.35;
		int bin = pi0_weights->FindBin(s_parentpt);
                ww = pi0_weights->GetBinContent(bin);
		ww2*= num_pi0/num_eta * 0.45 * 0.0069;				            
	    } else if(s_head == 1 && s_gparentid==0){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		prox = s_parentpt;
		if(s_parentpt<0.35)s_parentpt=0.35;
		int bin = gamma_weights->FindBin(s_parentpt);
                ww = gamma_weights->GetBinContent(bin); 
		if(ww>50)ww=1;
	    }	 	  
	    //============================================
	    // Fill
	    //ww*=10e6;
            //============================================

	    if(s_head==0)dcapt_ni->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt);
	    if(s_head==7 && s_parentid==7){	
		dcapt_pi0_nw_ni->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt);       
	    } 
	    if(s_head==17 && s_parentid==17){    
		dcapt_eta_nw_ni->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt);
	    }
	    if(s_head==1){
		dcapt_gamma_nw_ni->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt);
	    }
	}

	for(int i =0;i<ch1->GetEntries();i++){
	    ch1->GetEntry(i);
	    if(i%100000==0)cout << "on " << i << " of " << ch1->GetEntries() << endl;
	    if(!(s_id==3 || s_id==2))continue;
	    if(s_pt<0.6)continue;
	    if(s_hft<1)continue;
	   if(s_iso==0)continue;
	    double ww = 1;
	    double ww2 =1;
	    double prox = 0;
	    //============================================
            //Get Weights
            //============================================	 
	    if(s_head == 7 && s_gparentid==0){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		prox = s_parentpt;
		if(s_parentpt<0.35)s_parentpt=0.35;	      
		int bin = pi0_weights->FindBin(s_parentpt);
                ww = pi0_weights->GetBinContent(bin);
		ww2*=0.01174; 	
	    } else if(s_head == 17 && s_gparentid==0){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		if(s_parentpt<0.35)s_parentpt=0.35;
		int bin = pi0_weights->FindBin(s_parentpt);
                ww = pi0_weights->GetBinContent(bin);
		ww2*= num_pi0/num_eta * 0.45 * 0.0069;				            
	    } else if(s_head == 1 && s_gparentid==0){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		prox = s_parentpt;
		if(s_parentpt<0.35)s_parentpt=0.35;
		int bin = gamma_weights->FindBin(s_parentpt);
                ww = gamma_weights->GetBinContent(bin); 
		if(ww>50)ww=1;
	    }	 	  
	    //============================================
	    // Fill
	    //ww*=10e6;
            //============================================	  
	    if(s_head==0)dcapt->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt);
	    if(s_head==7 && s_parentid==7){
		dcapt_pi0->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
		dcapt_pi0_nw->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt);       
	    } 
	    if(s_head==17 && s_parentid==17){
		dcapt_eta->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
		dcapt_eta_nw->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt);
	    }
	    if((s_head==7 && s_parentid==7)||(s_head==17 && s_parentid==17)){
		dcapt_all->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
		dcapt_all_nw->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt);
		if(s_px1*s_px2*s_ist==0)dcapt_all_m1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
		else if(s_ist*s_px2*s_px1>0)dcapt_all_m4->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);		
	    }
	    if(s_head==1){
		dcapt_gamma->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
		dcapt_gamma_nw->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt);
		dcapt_eta_gamma->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*0.2*1/(1.21361-1));
		dcapt_pi0_gamma->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*0.8*1/(1.21361-1));
		dcapt_eta_gamma_nw->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,0.2*1/(1.21361-1));
		dcapt_pi0_gamma_nw->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,0.8*1/(1.21361-1));
	    }
	    if(s_head==1){
		dcapt_all->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*(1+1/(1.21361-1)));	
		dcapt_all_nw->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,(1+1/(1.21361-1)));
		if(s_px1*s_px2*s_ist*s_ssd==0)dcapt_all_m1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*(1+1/(1.21361-1)));
		else if(s_ist*s_px2*s_px1>0)dcapt_all_m4->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*(1+1/(1.21361-1)));		    		
	    }
	}
		
//======================================================================
//======================================================================
//======================================================================
    h1->SetMarkerStyle(8);
    h1->SetLineColor(1);
    h1->SetMarkerColor(1);
    h1->GetXaxis()->SetTitle("ln(|DCA|/cm)");
    h1->GetYaxis()->SetTitle("A. U.");
    dcapt_all->SetLineColor(kBlue);  
    dcapt_all->SetMarkerColor(kBlue);
    dcapt_all_m1->SetLineColor(kBlue);
    dcapt_all_m1->SetMarkerColor(kBlue);
    dcapt_all_m4->SetLineColor(kOrange-1);
    dcapt_all_m4->SetMarkerColor(kOrange-1);
    dcapt_all->SetMarkerStyle(25);  
    dcapt_eh_all->SetLineColor(kRed);  
    dcapt_eh_all->SetMarkerColor(kRed);
    dcapt_eh_all->SetMarkerStyle(25); 
    dcapt_eh_all_m1->SetLineColor(kMagenta);  
    dcapt_eh_all_m1->SetMarkerColor(kMagenta);
    dcapt_eh_all_m1->SetMarkerStyle(24); 
    dcapt_eh_all_m2->SetLineColor(kBlue);  
    dcapt_eh_all_m2->SetMarkerColor(kBlue);
    dcapt_eh_all_m2->SetMarkerStyle(25); 
    dcapt_eh_all_m3->SetLineColor(kCyan);  
    dcapt_eh_all_m3->SetMarkerColor(kCyan);
    dcapt_eh_all_m3->SetMarkerStyle(26); 
    dcapt_eh_all_m4->SetLineColor(kOrange-1);  
    dcapt_eh_all_m4->SetMarkerColor(kOrange-1);
    dcapt_eh_all_m4->SetMarkerStyle(26);  
    dcapt_gamma->SetLineColor(kRed);  
    dcapt_gamma->SetMarkerColor(kRed);  
    dcapt_eh_gamma->SetLineColor(kRed);  
    dcapt_eh_gamma->SetMarkerColor(kRed);  
    dcapt_pi0->SetLineColor(kBlue);  
    dcapt_pi0->SetMarkerColor(kBlue); 

    dcapt_pi0_nw->SetLineColor(kBlue);  
    dcapt_pi0_nw->SetMarkerColor(kBlue); 
    dcapt_eta_nw->SetLineColor(kGreen-2);
    dcapt_eta_nw->SetMarkerColor(kGreen-2); 
    dcapt_gamma_nw->SetLineColor(kRed);  
    dcapt_gamma_nw->SetMarkerColor(kRed);
    dcapt_pi0_nw_ni->SetLineColor(kBlue);  
    dcapt_pi0_nw_ni->SetMarkerColor(kBlue); 
    dcapt_eta_nw_ni->SetLineColor(kGreen-2);
    dcapt_eta_nw_ni->SetMarkerColor(kGreen-2); 
    dcapt_gamma_nw_ni->SetLineColor(kRed);  
    dcapt_gamma_nw_ni->SetMarkerColor(kRed);  


    dcapt_all_nw1->SetMarkerStyle(25);  
    dcapt_pi0_nw1->SetMarkerStyle(25); 
    dcapt_eta_nw1->SetMarkerStyle(25); 
    dcapt_gamma_nw1->SetMarkerStyle(25);  
    dcapt_pi0_nw1->SetLineColor(kBlue);  
    dcapt_pi0_nw1->SetMarkerColor(kBlue); 
    dcapt_eta_nw1->SetLineColor(kGreen-2);
    dcapt_eta_nw1->SetMarkerColor(kGreen-2); 
    dcapt_gamma_nw1->SetLineColor(kRed);  
    dcapt_gamma_nw1->SetMarkerColor(kRed);  


    dcapt_eh_pi0->SetLineColor(kBlue);  
    dcapt_eh_pi0->SetMarkerColor(kBlue);   
    dcapt_eta->SetLineColor(kGreen-2);
    dcapt_eta->SetMarkerColor(kGreen-2); 
    dcapt_eh_eta->SetLineColor(kGreen-2);
    dcapt_eh_eta->SetMarkerColor(kGreen-2); 
    dcapt_pi0_gamma->SetLineColor(kCyan);  
    dcapt_pi0_gamma->SetMarkerColor(kCyan);  
    dcapt_eh_pi0_gamma->SetLineColor(kCyan);  
    dcapt_eh_pi0_gamma->SetMarkerColor(kCyan);   
    dcapt_eta_gamma->SetLineColor(kGray+1);
    dcapt_eta_gamma->SetMarkerColor(kGray+1); 
    dcapt_eh_eta_gamma->SetLineColor(kGray+1);
    dcapt_eh_eta_gamma->SetMarkerColor(kGray+1); 
   
    pt_eta =(TH1F*)dcapt_eta->ProjectionY();     
    pt_pi0 =(TH1F*)dcapt_pi0->ProjectionY(); 
    pt_eta_gamma =(TH1F*)dcapt_eta_gamma->ProjectionY();     
    pt_pi0_gamma =(TH1F*)dcapt_pi0_gamma->ProjectionY();  
    pt_gamma =(TH1F*)dcapt_gamma->ProjectionY();  
    pt_eta_nw =(TH1F*)dcapt_eta_nw->ProjectionY();     
    pt_pi0_nw =(TH1F*)dcapt_pi0_nw->ProjectionY(); 
    pt_eta_gamma_nw =(TH1F*)dcapt_eta_gamma_nw->ProjectionY();     
    pt_pi0_gamma_nw =(TH1F*)dcapt_pi0_gamma_nw->ProjectionY();  
    pt_gamma_nw =(TH1F*)dcapt_gamma_nw->ProjectionY(); 


    pt_eta_nw_ni =(TH1F*)dcapt_eta_nw_ni->ProjectionY();     
    pt_pi0_nw_ni =(TH1F*)dcapt_pi0_nw_ni->ProjectionY(); 
    pt_gamma_nw_ni =(TH1F*)dcapt_gamma_nw_ni->ProjectionY(); 

    for(int i=0;i<9;i++){
	int bin1 = pt_pi0->FindBin(binning[i]);
	int bin2 = pt_pi0->FindBin(binning[i+1]);
	double temp1 = pt_pi0->Integral(bin1,bin2);
	double temp2 = pt_eta->Integral(bin1,bin2);
	double temp3 = pt_gamma->Integral(bin1,bin2);
	double temp4 = pt_pi0_gamma->Integral(bin1,bin2);
	double temp5 = pt_eta_gamma->Integral(bin1,bin2);
	double temp6 = temp1+temp2+temp3+temp4+temp5;
	double temp11 = pt_pi0_nw->Integral(bin1,bin2);
	double temp22 = pt_eta_nw->Integral(bin1,bin2);
	double temp33 = pt_gamma_nw->Integral(bin1,bin2);
	double temp44 = pt_pi0_gamma_nw->Integral(bin1,bin2);
	double temp55 = pt_eta_gamma_nw->Integral(bin1,bin2);
	comp1->SetBinContent(i+1,temp1/temp6);
	comp2->SetBinContent(i+1,temp2/temp6);
	comp3->SetBinContent(i+1,temp3/temp6);
	comp4->SetBinContent(i+1,temp4/temp6);
	comp5->SetBinContent(i+1,temp5/temp6);
	corr1->SetBinContent(i+1,temp1/temp6);
	corr2->SetBinContent(i+1,temp11/temp22*temp2/temp6);
	corr3->SetBinContent(i+1,temp11/temp33*temp3/temp6);
	corr4->SetBinContent(i+1,temp11/temp44*temp4/temp6);
	corr5->SetBinContent(i+1,temp11/temp55*temp5/temp6);
    }
    comp1->SetLineColor(kBlue);
    comp1->SetMarkerColor(kBlue);   
    comp2->SetLineColor(kGreen-2);
    comp2->SetMarkerColor(kGreen-2);
    comp3->SetLineColor(kRed);
    comp3->SetMarkerColor(kRed); 
    comp4->SetLineColor(kCyan);
    comp4->SetMarkerColor(kCyan);
    comp5->SetLineColor(kGray);
    comp5->SetMarkerColor(kGray);
    TCanvas *ccomp = new TCanvas("ccomp","ccomp");
    comp1->GetYaxis()->SetRangeUser(0,1);
    comp1->Draw("same");
    comp2->Draw("same");
    comp3->Draw("same");
    comp4->Draw("same");
    comp5->Draw("same");


//======================================================================
    for(int i =0;i<ch1->GetEntries();i++){
	ch1->GetEntry(i);
	if(i%100000==0)cout << "on " << i << " of " << ch1->GetEntries() << endl;
	if(!(s_id==3 || s_id==2))continue;
	if(s_pt<0.6)continue;
	if(s_hft<1)continue;
	if(s_iso==0)continue;
	double ww = 1;
	//============================================
	//Get Weights
	//============================================	 
	int binn = corr1->FindBin(s_pt);
	if(s_head == 7 && s_gparentid==0){	  
	    ww = corr1->GetBinContent(binn);		
	} else if(s_head == 17 && s_gparentid==0){
	    ww = corr2->GetBinContent(binn);			            
	} else if(s_head == 1 && s_gparentid==0){
	    ww = corr3->GetBinContent(binn);//+corr4->GetBinContent(binn)+corr5->GetBinContent(binn);			
	}	 	  
	//============================================
	// Fill
	//============================================	  
	if(s_head==7 && s_parentid==7){
	    dcapt_pi0_nw1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww);       
	} 
	if(s_head==17 && s_parentid==17){   
	    dcapt_eta_nw1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww);
	}
	if((s_head==7 && s_parentid==7)||(s_head==17 && s_parentid==17)){
	    dcapt_all_nw1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww);		
	}
	if(s_head==1){      
	    dcapt_gamma_nw1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww);	
	    dcapt_eta_gamma_nw1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,0.2*1/(1.21361-1)*ww);
	    dcapt_pi0_gamma_nw1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,0.8*1/(1.21361-1)*ww);
	}
	if(s_head==1){
	    dcapt_all_nw1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww*1/(1.21361-1));		    		
	}
    }
//======================================================================
	float s_dr;
	float s_m;
	float s_c1;	
	float s_c2;
	float s_dca;
	float s_hft2;
	ch11->SetBranchAddress("eh_pt",&s_pt);
	ch11->SetBranchAddress("eh_Pxl1Truth",&s_px1);
	ch11->SetBranchAddress("eh_Pxl2Truth",&s_px2);
	ch11->SetBranchAddress("eh_IstTruth",&s_ist);
	ch11->SetBranchAddress("eh_SsdTruth",&s_ssd);
	ch11->SetBranchAddress("eh_dca",&s_dcaxy);
	ch11->SetBranchAddress("eh_hft1",&s_hft);
	ch11->SetBranchAddress("eh_hft2",&s_hft2);
	ch11->SetBranchAddress("eh_pair_decaypos",&s_dr);
        ch11->SetBranchAddress("eh_pair_dca",&s_dca);
	ch11->SetBranchAddress("eh_comb_mass",&s_m);
	ch11->SetBranchAddress("eh_charge",&s_c1);
	ch11->SetBranchAddress("eh_h_charge",&s_c2);
	ch11->SetBranchAddress("eh_head",&s_head);
	ch11->SetBranchAddress("eh_id",&s_id);
	ch11->SetBranchAddress("event_centrality",&s_cen);
	ch11->SetBranchAddress("eh_parentid",&s_parentid);
	ch11->SetBranchAddress("eh_gparentid",&s_gparentid);
	ch11->SetBranchAddress("eh_ggparentid",&s_ggparentid);
	ch11->SetBranchAddress("eh_parentpt",&s_parentpt);
	ch11->SetBranchAddress("eh_gparentpt",&s_gparentpt);
	ch11->SetBranchAddress("eh_ggparentpt",&s_ggparentpt);
	for(int i =0;i<ch11->GetEntries();i++){
	    ch11->GetEntry(i);
	    if(i%1000000==0)cout << "on " << i << " of " << ch11->GetEntries() << endl;;
	    if(s_pt<0.6)continue;
	    if(s_c1*s_c2>0)continue;
	    if(s_hft<1||s_hft2<1)continue;  
	    if(s_m>0.015)continue; 	 
	    double ww = 1;
	    double ww2 = 1;
	    double ww3 =1;
	    int binn = corr1->FindBin(s_pt);
	    if(s_head == 7 && s_gparentid==0){	  
		ww3 = corr1->GetBinContent(binn);		
	    } else if(s_head == 17 && s_gparentid==0){
		ww3 = corr2->GetBinContent(binn);			            
	    } else if(s_head == 1 && s_gparentid==0){
		ww3 = corr3->GetBinContent(binn)+corr4->GetBinContent(binn)+corr5->GetBinContent(binn);			
	    }	 	     
	    if(s_head == 7){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		if(s_parentpt<0.35)s_parentpt=0.35;
		int bin = pi0_weights->FindBin(s_parentpt);
                ww = pi0_weights->GetBinContent(bin);
		ww2*=0.01174;               	
	    }
	    if(s_head == 17){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;
		if(s_parentpt<0.35)s_parentpt=0.35;
		int bin = pi0_weights->FindBin(s_parentpt);
                ww = pi0_weights->GetBinContent(bin);
		ww2*= num_pi0/num_eta*0.45;
		ww2*=0.0069;	   
	    }
	    if(s_head == 1){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
	        if(s_parentpt<0.35)s_parentpt=0.35;
		int bin = gamma_weights->FindBin(s_parentpt);
                ww = gamma_weights->GetBinContent(bin);
  		ww2*= 1;			     
	    }
	    if(s_head==1){
		dcapt_eh_gamma->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
	    	dr_eh_gamma->Fill(s_pt,s_dr,ww2*ww);
	    	mass_eh_gamma->Fill(s_pt,s_m,ww2*ww);
	    }
	    if(s_head==7){
		if(s_parentid==7)dcapt_eh_pi0->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);		 
		if(s_parentid==7)dr_eh_pi0->Fill(s_pt,s_dr,ww2*ww);
		if(s_parentid==7)mass_eh_pi0->Fill(s_pt,s_m,ww2*ww);		 	
	    }
	    if(s_head==17){
		if(s_parentid==17)dcapt_eh_eta->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);       	
		if(s_parentid==17)dr_eh_eta->Fill(s_pt,s_dr,ww2*ww);
		if(s_parentid==17)mass_eh_eta->Fill(s_pt,s_m,ww2*ww);	 
	    }
	    if(s_head==17||s_head==7){
		dcapt_eh_all->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
		if(s_px1*s_px2*s_ist==0)dcapt_eh_all_m1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
		if(s_px2==0)dcapt_eh_all_m2->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
		dcapt_eh_all_m3->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww3);
		if(s_ist*s_px2*s_px1>0)dcapt_eh_all_m4->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww);
	    }
	    if(s_head==17||s_head==7){
		dr_eh_all->Fill(s_pt,s_dr,ww2*ww);
		mass_eh_all->Fill(s_pt,s_m,ww2*ww);
	    }
	    if(s_head==1){
		dcapt_eh_all->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*(1+1/(1.21361-1)));
		if(s_px1*s_px2*s_ist==0)dcapt_eh_all_m1->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*(1+1/(1.21361-1)));
		if(s_px2==0)dcapt_eh_all_m2->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*(1+1/(1.21361-1)));
		dcapt_eh_all_m3->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww3);
		if(s_ist*s_px2*s_px1>0)dcapt_eh_all_m4->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*(1+1/(1.21361-1)));
		dr_eh_all->Fill(s_pt,s_dr,ww2*ww*(1+1/(1.21361-1)));
		mass_eh_all->Fill(s_pt,s_m,ww2*ww);
		dr_eh_eta_gamma->Fill(s_pt,s_dr,ww2*ww*0.2*1/(1.21361-1));
		mass_eh_eta_gamma->Fill(s_pt,s_m,ww2*ww*0.2*1/(1.21361-1));
		dcapt_eh_eta_gamma->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*0.2*1/(1.21361-1));
		dr_eh_pi0_gamma->Fill(s_pt,s_dr,ww2*ww*0.8*1/(1.21361-1));
		mass_eh_pi0_gamma->Fill(s_pt,s_m,ww2*ww*0.8*1/(1.21361-1));
		dcapt_eh_pi0_gamma->Fill(log(fabs(s_dcaxy)+0.000000001),s_pt,ww2*ww*0.8*1/(1.21361-1));
	    }
	}
//======================================================================
	TFile f("root/DCA_plots.root","RECREATE");
	dcapt_gamma->Write("dcapt_gamma");
	dcapt_pi0->Write("dcapt_pi0");
	dcapt_eta->Write("dcapt_eta");
	dcapt_pi0_gamma->Write("dcapt_pi0_gamma");
	dcapt_eta_gamma->Write("dcapt_eta_gamma");
	dcapt_eh_gamma->Write("dcapt_eh_gamma");
	dcapt_eh_pi0->Write("dcapt_eh_pi0");
	dcapt_eh_eta->Write("dcapt_eh_eta");
	dcapt_eh_pi0_gamma->Write("dcapt_eh_pi0_gamma");
	dcapt_eh_eta_gamma->Write("dcapt_eh_eta_gamma");
	dcapt_eh_all->Write("dcapt_eh_all");
	dcapt_eh_all_m1->Write("dcapt_eh_all_m1");
	dcapt_eh_all_m2->Write("dcapt_eh_all_m2");
	dcapt_eh_all_m3->Write("dcapt_eh_all_m3");
	dcapt_eh_all_m4->Write("dcapt_eh_all_m4");
        dcapt_all_m1->Write("dcapt_all_m1");
        dcapt_all_m2->Write("dcapt_all_m2");
        dcapt_all_m3->Write("dcapt_all_m3");
        dcapt_all_m4->Write("dcapt_all_m4");
	dr_eh_gamma->Write("dr_eh_gamma");
	dr_eh_pi0->Write("dr_eh_pi0");
	dr_eh_eta->Write("dr_eh_eta");
	dr_eh_pi0_gamma->Write("dr_eh_pi0_gamma");
	dr_eh_eta_gamma->Write("dr_eh_eta_gamma");
	dr_eh_all->Write("dr_eh_all");
	dcapt_all->Write("dcapt_all");
	dcapt_all_nw->Write("dcapt_all_nw");
	dcapt_eta_nw->Write("dcapt_eta_nw");
	dcapt_pi0_nw->Write("dcapt_pi0_nw");
	dcapt_gamma_nw->Write("dcapt_gamma_nw");


	dcapt_all_nw1->Write("dcapt_all_nw1");
	dcapt_gamma_nw1->Write("dcapt_gamma_nw1");
	dcapt->Write("dcapt");
	dcapt_ni->Write("dcapt_ni");
	h1->Write("h1");
	h11->Write("h11");
	h111->Write("h111");
	f.Close();
    }
    pt= (TH1F*)dcapt->ProjectionY();
    pt_ni= (TH1F*)dcapt_ni->ProjectionY();    
    for(int i=1; i<pt_eta_nw_ni->GetNbinsX()+1;i++){
	double temp11 = pt_pi0_nw->GetBinContent(i);
	double temp22 = pt_eta_nw->GetBinContent(i);
	double temp33 = pt_gamma_nw->GetBinContent(i);
	double temp44 = pt->GetBinContent(i);
	double temp1 = pt_pi0_nw_ni->GetBinContent(i);
	double temp2 = pt_eta_nw_ni->GetBinContent(i);
	double temp3 = pt_gamma_nw_ni->GetBinContent(i);
	double temp4 = pt_ni->GetBinContent(i);


	if(temp4>0 && temp44>0){
	    pt_ni->SetBinContent(i,temp44/temp4);	
	    pt_ni->SetBinError(i,temp44/temp4*sqrt(1/temp44));
	}else{
	    pt_ni->SetBinContent(i,0);	
	    pt_ni->SetBinError(i,0);
	}
	if(temp1>0 && temp11>0){
	    pt_pi0_nw_ni->SetBinContent(i,temp11/temp1);	
	    pt_pi0_nw_ni->SetBinError(i,temp11/temp1*sqrt(1/temp11));
	}else{
	    pt_pi0_nw_ni->SetBinContent(i,0);	
	    pt_pi0_nw_ni->SetBinError(i,0);
	}
	if(temp3>0 && temp3>0){
	    pt_gamma_nw_ni->SetBinContent(i,temp33/temp3);
	    double temp = temp3-temp33;
	    pt_gamma_nw_ni->SetBinError(i,sqrt(temp/temp3/temp3*temp/temp3/temp3*temp33 + temp33/temp3/temp3*temp33/temp3/temp3*temp));
	}else{
	    pt_gamma_nw_ni->SetBinContent(i,0);	
	    pt_gamma_nw_ni->SetBinError(i,0);
	}

	if(temp2>0 && temp22>0){
	    pt_eta_nw_ni->SetBinContent(i,temp22/temp2);	
	    pt_eta_nw_ni->SetBinError(i,temp22/temp2*sqrt(1/temp22));
	}else{
	    pt_eta_nw_ni->SetBinContent(i,0);	
	    pt_eta_nw_ni->SetBinError(i,0);
	}

    }
    pt_ni->GetYaxis()->SetRangeUser(0,1);
    pt_ni->GetYaxis()->SetTitle("Isolation Efficiency"); 
    pt_ni->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");    
    TCanvas *ciso = new TCanvas("ciso","iso eff.");
    pt_ni->Draw("PE");
    pt_pi0_nw_ni->Draw("same PE");
    pt_eta_nw_ni->Draw("same PE");
    pt_gamma_nw_ni->Draw("same PE");   
    


    pt_eta_nw1 =(TH1F*)dcapt_eta_nw1->ProjectionY();     
    pt_pi0_nw1 =(TH1F*)dcapt_pi0_nw1->ProjectionY(); 
    pt_eta_gamma_nw1 =(TH1F*)dcapt_eta_gamma_nw1->ProjectionY();     
    pt_pi0_gamma_nw1 =(TH1F*)dcapt_pi0_gamma_nw1->ProjectionY();  
    pt_gamma_nw1 =(TH1F*)dcapt_gamma_nw1->ProjectionY(); 
    for(int i=0;i<9;i++){
	int bin1 = pt_pi0_nw1->FindBin(binning[i]);
	int bin2 = pt_pi0_nw1->FindBin(binning[i+1]);
	double temp1 = pt_pi0_nw1->Integral(bin1,bin2);
	double temp2 = pt_eta_nw1->Integral(bin1,bin2);
	double temp3 = pt_gamma_nw1->Integral(bin1,bin2);
	double temp4 = pt_pi0_gamma_nw1->Integral(bin1,bin2);
	double temp5 = pt_eta_gamma_nw1->Integral(bin1,bin2);
	double temp6 = temp1+temp2+temp3+temp4+temp5;
	check1->SetBinContent(i+1,temp1/temp6);
	check2->SetBinContent(i+1,temp2/temp6);
	check3->SetBinContent(i+1,temp3/temp6);
	check4->SetBinContent(i+1,temp4/temp6);
	check5->SetBinContent(i+1,temp5/temp6);

    }
    check1->SetLineColor(kBlue);
    check1->SetMarkerColor(kBlue);   
    check2->SetLineColor(kGreen-2);
    check2->SetMarkerColor(kGreen-2);
    check3->SetLineColor(kRed);
    check3->SetMarkerColor(kRed); 
    check4->SetLineColor(kCyan);
    check4->SetMarkerColor(kCyan);
    check5->SetLineColor(kGray);
    check5->SetMarkerColor(kGray);
    TCanvas *ccheck = new TCanvas("ccheck","ccheck");
    check1->Draw();
    check2->Draw("same");   
    check3->Draw("same");   
    check4->Draw("same");   
    check5->Draw("same");   

    pt_eta_nw =(TH1F*)dcapt_eta_nw->ProjectionY();     
    pt_pi0_nw =(TH1F*)dcapt_pi0_nw->ProjectionY(); 
    pt_eta_gamma_nw =(TH1F*)dcapt_eta_gamma_nw->ProjectionY();     
    pt_pi0_gamma_nw =(TH1F*)dcapt_pi0_gamma_nw->ProjectionY();  
    pt_gamma_nw =(TH1F*)dcapt_gamma_nw->ProjectionY(); 

    pt_gamma_nw->Rebin();
    pt_eta_gamma_nw->Rebin();
    pt_pi0_gamma_nw->Rebin();
    pt_pi0_nw->Rebin(); 
    pt_eta_nw->Rebin();   
    pt_gamma->Rebin();
    pt_eta_gamma->Rebin();
    pt_pi0_gamma->Rebin();
    pt_pi0->Rebin(); 
    pt_eta->Rebin();  
 
    norm5(pt_eta);
    norm5(pt_pi0);   
    norm5(pt_gamma);
    norm5(pt_pi0_gamma);
    norm5(pt_eta_gamma);
    norm5(pt_eta_nw);
    norm5(pt_pi0_nw);   
    norm5(pt_gamma_nw);
    norm5(pt_pi0_gamma_nw);
    norm5(pt_eta_gamma_nw);
    TCanvas *cpt = new TCanvas("cpt","cpt",2500,500);
    pt_pi0_nw->SetLineColor(1);
    pt_pi0_gamma_nw->SetLineColor(1);
    pt_eta_nw->SetLineColor(1);
    pt_pi0_gamma_nw->SetLineColor(1);
    pt_gamma_nw->SetLineColor(1);

      
    cpt->Divide(5,1);
    cpt->cd(1);
    pt_pi0->GetYaxis()->SetRangeUser(0,0.1);
    pt_pi0->Draw();
    pt_pi0_nw->Draw("hist same");
    cpt->cd(2);
    pt_eta->GetYaxis()->SetRangeUser(0,0.1);
    pt_eta->Draw();
    pt_eta_nw->Draw("hist same");
    cpt->cd(3);
    pt_gamma->GetYaxis()->SetRangeUser(0,0.1);
    pt_gamma->Draw();
    pt_gamma_nw->Draw("hist same");
    cpt->cd(4);
    pt_pi0_gamma->GetYaxis()->SetRangeUser(0,0.1);
    pt_pi0_gamma->Draw();
    pt_pi0_gamma_nw->Draw("hist same");
    cpt->cd(5);
    pt_eta_gamma->GetYaxis()->SetRangeUser(0,0.1);
    pt_eta_gamma->Draw();
    pt_eta_gamma_nw->Draw("hist same");

    // ========== DCA plots 
    double low = 2.5;
    double high = 3.5;
    h1->GetYaxis()->SetRangeUser(low,high);   
    hx =(TH1F*)h1->ProjectionX();
//================Set Ragne
    dcapt_eh_pi0->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_eta->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_pi0_gamma->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_eta_gamma->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_gamma->GetYaxis()->SetRangeUser(low,high);
    dcapt_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_all_nw1->GetYaxis()->SetRangeUser(low,high);
    dcapt_eta->GetYaxis()->SetRangeUser(low,high);
    dcapt_pi0->GetYaxis()->SetRangeUser(low,high);
    dcapt_eta_gamma->GetYaxis()->SetRangeUser(low,high);
    dcapt_pi0_gamma->GetYaxis()->SetRangeUser(low,high);
    dcapt_gamma->GetYaxis()->SetRangeUser(low,high);
    dcapt_eta_nw->GetYaxis()->SetRangeUser(low,high);
    dcapt_pi0_nw->GetYaxis()->SetRangeUser(low,high);
    dcapt_eta_gamma_nw->GetYaxis()->SetRangeUser(low,high);
    dcapt_pi0_gamma_nw->GetYaxis()->SetRangeUser(low,high);
    dcapt_gamma_nw->GetYaxis()->SetRangeUser(low,high);
    dcapt_eta_nw1->GetYaxis()->SetRangeUser(low,high);
    dcapt_pi0_nw1->GetYaxis()->SetRangeUser(low,high);
    dcapt_eta_gamma_nw1->GetYaxis()->SetRangeUser(low,high);
    dcapt_pi0_gamma_nw1->GetYaxis()->SetRangeUser(low,high);
    dcapt_gamma_nw1->GetYaxis()->SetRangeUser(low,high);
//============Project
    dca_eh_pi0 =(TH1F*)dcapt_eh_pi0->ProjectionX();  
    dca_eh_eta =(TH1F*)dcapt_eh_eta->ProjectionX(); 
    dca_eh_pi0_gamma =(TH1F*)dcapt_eh_pi0_gamma->ProjectionX();  
    dca_eh_eta_gamma =(TH1F*)dcapt_eh_eta_gamma->ProjectionX(); 
    dca_eh_all =(TH1F*)dcapt_eh_all->ProjectionX();  
    dca_eh_all_m1 =(TH1F*)dcapt_eh_all_m1->ProjectionX();
    dca_eh_all_m4 =(TH1F*)dcapt_eh_all_m4->ProjectionX();
    dca_eh_gamma =(TH1F*)dcapt_eh_gamma->ProjectionX();  
    dca_all =(TH1F*)dcapt_all->ProjectionX();
    dca_all_nw =(TH1F*)dcapt_all_nw->ProjectionX();
    dca_all_nw1 =(TH1F*)dcapt_all_nw1->ProjectionX();
    dca_all_m1 =(TH1F*)dcapt_all_m1->ProjectionX();
    dca_all_m4 =(TH1F*)dcapt_all_m4->ProjectionX();  
    dca_eta =(TH1F*)dcapt_eta->ProjectionX();     
    dca_pi0 =(TH1F*)dcapt_pi0->ProjectionX(); 
    dca_eta_gamma =(TH1F*)dcapt_eta_gamma->ProjectionX();     
    dca_pi0_gamma =(TH1F*)dcapt_pi0_gamma->ProjectionX();  
    dca_gamma =(TH1F*)dcapt_gamma->ProjectionX();  
    dca_eta_nw1 =(TH1F*)dcapt_eta_nw1->ProjectionX();     
    dca_pi0_nw1 =(TH1F*)dcapt_pi0_nw1->ProjectionX(); 
    dca_eta_gamma_nw1 =(TH1F*)dcapt_eta_gamma_nw1->ProjectionX();     
    dca_pi0_gamma_nw1 =(TH1F*)dcapt_pi0_gamma_nw1->ProjectionX();  
    dca_gamma_nw1 =(TH1F*)dcapt_gamma_nw1->ProjectionX();   
    dca_eta_nw =(TH1F*)dcapt_eta_nw->ProjectionX();     
    dca_pi0_nw =(TH1F*)dcapt_pi0_nw->ProjectionX(); 
    dca_eta_gamma_nw =(TH1F*)dcapt_eta_gamma_nw->ProjectionX();     
    dca_pi0_gamma_nw =(TH1F*)dcapt_pi0_gamma_nw->ProjectionX();  
    dca_gamma_nw =(TH1F*)dcapt_gamma_nw->ProjectionX();     
  
    norm6(dca_all);
    norm6(dca_all_nw);
    norm6(dca_all_nw1);
    norm6(dca_all_m1);
    norm6(dca_all_m4);
    norm6(dca_pi0);
    norm6(dca_eta);
    norm6(dca_pi0_gamma);
    norm6(dca_eta_gamma);
    norm6(dca_gamma);
    norm6(dca_pi0_nw1);
    norm6(dca_eta_nw1);
    norm6(dca_pi0_gamma_nw1);
    norm6(dca_eta_gamma_nw1);
    norm6(dca_gamma_nw1);
    norm6(dca_pi0_nw);
    norm6(dca_eta_nw);
    norm6(dca_pi0_gamma_nw);
    norm6(dca_eta_gamma_nw);
    norm6(dca_gamma_nw);
    norm(dca_eh_pi0);
    norm(dca_eh_eta);
    norm(dca_eh_pi0_gamma);
    norm(dca_eh_eta_gamma);
    norm(dca_eh_gamma);
    norm(dca_eh_all);
    norm(dca_eh_all_m1);
    norm(dca_eh_all_m4);
    norm(hx);
  
    TCanvas *c1 = new TCanvas ("c1","dca single e ");

    dca_gamma->Draw("pe");
    dca_pi0->Draw("same pe");
    dca_eta->Draw("same pe");
    dca_gamma_nw->Draw("same hist");
    dca_pi0_nw->Draw("same hist");
    dca_eta_nw->Draw("same hist");
    dca_gamma_nw1->Draw("same pe");
    dca_pi0_nw1->Draw("same pe");
    dca_eta_nw1->Draw("same pe");
    TCanvas *c12 = new TCanvas ("c12","all dca single e ");
    dca_all->Draw("same pe");
    dca_all_nw->Draw("same hist");
    dca_all_nw1->Draw("same pe");
    //dca_pi0_gamma->Draw("same pe");
    //dca_eta_gamma->Draw("same pe");
    TCanvas *c13 = new TCanvas ("c13","all1 dca single e ");  
    dca_all_nw1->Draw("same pe");
    dca_gamma_nw1->Draw("same pe");
    dca_pi0_nw1->Draw("same pe");
    dca_eta_nw1->Draw("same pe");
    TCanvas *c3 = new TCanvas ("c3","2D ",1000,500);
    h11->RebinX();
    h11->RebinY();
    dr_eh_all->RebinX();
    dr_eh_all->RebinY();
    norm2D(h11);
    norm2D(dr_eh_all);
    c3->Divide(2,1);
    c3->cd(1);
    h11->GetYaxis()->SetTitle("Decay Radius [cm]");
    h11->GetXaxis()->SetTitle("p_{T} [GeV]");
    h11->GetZaxis()->SetRangeUser(0,0.01);
    h11->Draw("COLZ");
    c3->cd(2);
    dr_eh_all->GetYaxis()->SetTitle("Decay Radius [cm]");
    dr_eh_all->GetXaxis()->SetTitle("p_{T} [GeV]");
    dr_eh_all->GetZaxis()->SetRangeUser(0,0.01);
    dr_eh_all->Draw("COLZ");

    double low1=2.0;
    double high1=8.5;
    TCanvas *c31 = new TCanvas ("c31","1D ");
    dr_eh_all->GetXaxis()->SetRangeUser(low1,high1);
    h11->GetXaxis()->SetRangeUser(low1,high1);
    //dr_eh_all->GetYaxis()->SetRangeUser(0,5);
    //h11->GetYaxis()->SetRangeUser(0,5);
    dr_1_x =(TH1F*) dr_eh_all->ProjectionY();
    h11_1_x =(TH1F*) h11->ProjectionY();
    dr_1_x->SetLineColor(kRed);
    dr_1_x->SetMarkerColor(kRed);

    //dr_1_x->Rebin();
    //h11_1_x->Rebin();
    norm5(dr_1_x);
    norm5(h11_1_x);
    dr_1_x->Draw("PE");
    h11_1_x->Draw("same PE");  
    TCanvas *c33 = new TCanvas ("c33","mass2D ",1000,500);
    h111->RebinX();
    h111->RebinY();
    mass_eh_all->RebinX();
    mass_eh_all->RebinY();
    norm2D(h111);
    norm2D(mass_eh_all);
   
    c33->Divide(2,1);
    c33->cd(1);
    h111->GetYaxis()->SetTitle("m(ee)");
    h111->GetXaxis()->SetTitle("p_{T} [GeV]");
    h111->GetZaxis()->SetRangeUser(0,0.01);
    h111->Draw("COLZ");
    c33->cd(2);
    mass_eh_all->GetYaxis()->SetTitle("m(ee)");
    mass_eh_all->GetXaxis()->SetTitle("p_{T} [GeV]");
    mass_eh_all->GetZaxis()->SetRangeUser(0,0.01);
    mass_eh_all->Draw("COLZ");

    TCanvas *c331 = new TCanvas ("c331","1D mass");
    mass_eh_all->GetXaxis()->SetRangeUser(low1,high1);
    h111->GetXaxis()->SetRangeUser(low1,high1);
    mass_1_x =(TH1F*)  mass_eh_all->ProjectionY();
    h111_1_x =(TH1F*)  h111->ProjectionY();
    mass_1_x->SetLineColor(kRed);
    mass_1_x->Rebin();
    h111_1_x->Rebin();
    norm5(mass_1_x);
    norm5(h111_1_x);
    mass_1_x->Draw("PE");
    h111_1_x->Draw("same PE");  

//===================================================================================
//============================== Doing pt DCA plots now==============================
//===================================================================================

    h1->GetYaxis()->SetRangeUser(binning[0],binning[1]);   
    hx1 =(TH1F*)h1->ProjectionX("hx1"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[0],binning[1]);   
    dca_eh_all1 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all1"); 

    dcapt_eh_all_m1->GetYaxis()->SetRangeUser(binning[0],binning[1]);   
    dca_eh_all_m11 =(TH1F*)dcapt_eh_all_m1->ProjectionX("dca_eh_all_m11");
    dcapt_eh_all_m2->GetYaxis()->SetRangeUser(binning[0],binning[1]);   
    dca_eh_all_m12 =(TH1F*)dcapt_eh_all_m2->ProjectionX("dca_eh_all_m12");
    dcapt_eh_all_m3->GetYaxis()->SetRangeUser(binning[0],binning[1]);   
    dca_eh_all_m13 =(TH1F*)dcapt_eh_all_m3->ProjectionX("dca_eh_all_m13");
    dcapt_eh_all_m4->GetYaxis()->SetRangeUser(binning[0],binning[1]);   
    dca_eh_all_m14 =(TH1F*)dcapt_eh_all_m4->ProjectionX("dca_eh_all_m14");

    h1->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    hx2 =(TH1F*)h1->ProjectionX("hx2"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    dca_eh_all2 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all2"); 
    dcapt_eh_all_m1->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    dca_eh_all_m21 =(TH1F*)dcapt_eh_all_m1->ProjectionX("dca_eh_all_m21"); 
    dcapt_eh_all_m2->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    dca_eh_all_m22 =(TH1F*)dcapt_eh_all_m2->ProjectionX("dca_eh_all_m22"); 
    dcapt_eh_all_m3->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    dca_eh_all_m23 =(TH1F*)dcapt_eh_all_m3->ProjectionX("dca_eh_all_m23"); 
    dcapt_eh_all_m4->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    dca_eh_all_m24 =(TH1F*)dcapt_eh_all_m4->ProjectionX("dca_eh_all_m24"); 

    h1->GetYaxis()->SetRangeUser(binning[2],binning[3]);   
    hx3 =(TH1F*)h1->ProjectionX("hx3"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[2],binning[3]);   
    dca_eh_all3 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all3"); 
    dcapt_eh_all_m1->GetYaxis()->SetRangeUser(binning[2],binning[4]);   
    dca_eh_all_m31 =(TH1F*)dcapt_eh_all_m1->ProjectionX("dca_eh_all_m31");
    dcapt_eh_all_m2->GetYaxis()->SetRangeUser(binning[2],binning[3]);   
    dca_eh_all_m32 =(TH1F*)dcapt_eh_all_m2->ProjectionX("dca_eh_all_m32");
    dcapt_eh_all_m3->GetYaxis()->SetRangeUser(binning[2],binning[3]);   
    dca_eh_all_m33 =(TH1F*)dcapt_eh_all_m3->ProjectionX("dca_eh_all_m33");
    dcapt_eh_all_m4->GetYaxis()->SetRangeUser(binning[2],binning[3]);   
    dca_eh_all_m34 =(TH1F*)dcapt_eh_all_m4->ProjectionX("dca_eh_all_m34");

    h1->GetYaxis()->SetRangeUser(binning[3],binning[4]);   
    hx4 =(TH1F*)h1->ProjectionX("hx4"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[3],binning[4]);   
    dca_eh_all4 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all4"); 
    dcapt_eh_all_m1->GetYaxis()->SetRangeUser(binning[3],binning[4]);   
    dca_eh_all_m41 =(TH1F*)dcapt_eh_all_m1->ProjectionX("dca_eh_all_m41"); 
    dcapt_eh_all_m2->GetYaxis()->SetRangeUser(binning[3],binning[4]);   
    dca_eh_all_m42 =(TH1F*)dcapt_eh_all_m2->ProjectionX("dca_eh_all_m42"); 
    dcapt_eh_all_m3->GetYaxis()->SetRangeUser(binning[3],binning[4]);   
    dca_eh_all_m43 =(TH1F*)dcapt_eh_all_m3->ProjectionX("dca_eh_all_m43"); 
    dcapt_eh_all_m4->GetYaxis()->SetRangeUser(binning[3],binning[4]);   
    dca_eh_all_m44 =(TH1F*)dcapt_eh_all_m4->ProjectionX("dca_eh_all_m44"); 

    h1->GetYaxis()->SetRangeUser(binning[4],binning[5]);   
    hx5 =(TH1F*)h1->ProjectionX("hx5"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[4],binning[5]);   
    dca_eh_all5 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all5"); 
    dcapt_eh_all_m1->GetYaxis()->SetRangeUser(binning[4],binning[5]);   
    dca_eh_all_m51 =(TH1F*)dcapt_eh_all_m1->ProjectionX("dca_eh_all_m51"); 
    dcapt_eh_all_m2->GetYaxis()->SetRangeUser(binning[4],binning[5]);   
    dca_eh_all_m52 =(TH1F*)dcapt_eh_all_m2->ProjectionX("dca_eh_all_m52"); 
    dcapt_eh_all_m3->GetYaxis()->SetRangeUser(binning[4],binning[5]);   
    dca_eh_all_m53 =(TH1F*)dcapt_eh_all_m3->ProjectionX("dca_eh_all_m53"); 
    dcapt_eh_all_m4->GetYaxis()->SetRangeUser(binning[4],binning[5]);   
    dca_eh_all_m54 =(TH1F*)dcapt_eh_all_m4->ProjectionX("dca_eh_all_m54"); 

    h1->GetYaxis()->SetRangeUser(binning[5],binning[6]);   
    hx6 =(TH1F*)h1->ProjectionX("hx6"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[5],binning[6]);   
    dca_eh_all6 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all6"); 
    dcapt_eh_all_m1->GetYaxis()->SetRangeUser(binning[5],binning[6]);   
    dca_eh_all_m61 =(TH1F*)dcapt_eh_all_m1->ProjectionX("dca_eh_all_m61");
    dcapt_eh_all_m2->GetYaxis()->SetRangeUser(binning[5],binning[6]);   
    dca_eh_all_m62 =(TH1F*)dcapt_eh_all_m2->ProjectionX("dca_eh_all_m62");
    dcapt_eh_all_m3->GetYaxis()->SetRangeUser(binning[5],binning[6]);   
    dca_eh_all_m63 =(TH1F*)dcapt_eh_all_m3->ProjectionX("dca_eh_all_m63");
    dcapt_eh_all_m4->GetYaxis()->SetRangeUser(binning[5],binning[6]);   
    dca_eh_all_m64 =(TH1F*)dcapt_eh_all_m4->ProjectionX("dca_eh_all_m64");

    h1->GetYaxis()->SetRangeUser(binning[6],binning[7]);   
    hx7 =(TH1F*)h1->ProjectionX("hx7");
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[6],binning[7]);   
    dca_eh_all7 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all7"); 
    dcapt_eh_all_m1->GetYaxis()->SetRangeUser(binning[6],binning[7]);   
    dca_eh_all_m71 =(TH1F*)dcapt_eh_all_m1->ProjectionX("dca_eh_all_m71"); 
    dcapt_eh_all_m2->GetYaxis()->SetRangeUser(binning[6],binning[7]);   
    dca_eh_all_m72 =(TH1F*)dcapt_eh_all_m2->ProjectionX("dca_eh_all_m72"); 
    dcapt_eh_all_m3->GetYaxis()->SetRangeUser(binning[6],binning[7]);   
    dca_eh_all_m73 =(TH1F*)dcapt_eh_all_m3->ProjectionX("dca_eh_all_m73"); 
    dcapt_eh_all_m4->GetYaxis()->SetRangeUser(binning[6],binning[7]);   
    dca_eh_all_m74 =(TH1F*)dcapt_eh_all_m4->ProjectionX("dca_eh_all_m74"); 
    h1->GetYaxis()->SetRangeUser(binning[7],binning[8]);   
    hx8 =(TH1F*)h1->ProjectionX("hx8"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[7],binning[8]);   
    dca_eh_all8 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all8"); 
    dcapt_eh_all_m1->GetYaxis()->SetRangeUser(binning[7],binning[8]);   
    dca_eh_all_m81 =(TH1F*)dcapt_eh_all_m1->ProjectionX("dca_eh_all_m81"); 
    dcapt_eh_all_m2->GetYaxis()->SetRangeUser(binning[7],binning[8]);   
    dca_eh_all_m82 =(TH1F*)dcapt_eh_all_m2->ProjectionX("dca_eh_all_m82"); 
    dcapt_eh_all_m3->GetYaxis()->SetRangeUser(binning[7],binning[8]);   
    dca_eh_all_m83 =(TH1F*)dcapt_eh_all_m3->ProjectionX("dca_eh_all_m83"); 
    dcapt_eh_all_m4->GetYaxis()->SetRangeUser(binning[7],binning[8]);   
    dca_eh_all_m84 =(TH1F*)dcapt_eh_all_m4->ProjectionX("dca_eh_all_m84"); 
    h1->GetYaxis()->SetRangeUser(binning[8],binning[9]);   
    hx9 =(TH1F*)h1->ProjectionX("hx9"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[8],binning[9]);   
    dca_eh_all9 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all9");  
    dcapt_eh_all_m1->GetYaxis()->SetRangeUser(binning[8],binning[9]);   
    dca_eh_all_m91 =(TH1F*)dcapt_eh_all_m1->ProjectionX("dca_eh_all_m91"); 
    dcapt_eh_all_m2->GetYaxis()->SetRangeUser(binning[8],binning[9]);   
    dca_eh_all_m92 =(TH1F*)dcapt_eh_all_m2->ProjectionX("dca_eh_all_m92"); 
    dcapt_eh_all_m3->GetYaxis()->SetRangeUser(binning[8],binning[9]);   
    dca_eh_all_m93 =(TH1F*)dcapt_eh_all_m3->ProjectionX("dca_eh_all_m93"); 
    dcapt_eh_all_m4->GetYaxis()->SetRangeUser(binning[8],binning[9]);   
    dca_eh_all_m94 =(TH1F*)dcapt_eh_all_m4->ProjectionX("dca_eh_all_m94");  
    norm(hx1);
    norm(hx2);
    norm(hx3);
    norm(hx4);
    norm(hx5);
    norm(hx6);
    norm(hx7);
    norm(hx8);
    norm(hx9);
    norm(dca_eh_all1);
    norm(dca_eh_all2);
    norm(dca_eh_all3);
    norm(dca_eh_all4);
    norm(dca_eh_all5);
    norm(dca_eh_all6);
    norm(dca_eh_all7);
    norm(dca_eh_all8);
    norm(dca_eh_all9);
    norm3(dca_eh_all_m11);
    norm3(dca_eh_all_m21);
    norm3(dca_eh_all_m31);
    norm3(dca_eh_all_m41);
    norm3(dca_eh_all_m51);
    norm3(dca_eh_all_m61);
    norm3(dca_eh_all_m71);
    norm3(dca_eh_all_m81);
    norm3(dca_eh_all_m91);
    norm3(dca_eh_all_m13);
    norm3(dca_eh_all_m23);
    norm3(dca_eh_all_m33);
    norm3(dca_eh_all_m43);
    norm3(dca_eh_all_m53);
    norm3(dca_eh_all_m63);
    norm3(dca_eh_all_m73);
    norm3(dca_eh_all_m83);
    norm3(dca_eh_all_m93);
    norm3(dca_eh_all_m12);
    norm3(dca_eh_all_m22);
    norm3(dca_eh_all_m32);
    norm3(dca_eh_all_m42);
    norm3(dca_eh_all_m52);
    norm3(dca_eh_all_m62);
    norm3(dca_eh_all_m72);
    norm3(dca_eh_all_m82);
    norm3(dca_eh_all_m92);
    norm33(dca_eh_all_m14);
    norm33(dca_eh_all_m24);
    norm33(dca_eh_all_m34);
    norm33(dca_eh_all_m44);
    norm33(dca_eh_all_m54);
    norm33(dca_eh_all_m64);
    norm33(dca_eh_all_m74);
    norm33(dca_eh_all_m84);
    norm33(dca_eh_all_m94);



    TLegend *leg2 = new TLegend(0.2,0.3,0.8,0.7);
    leg2->AddEntry(hx1,"Data Photonic pairs","PE");
    leg2->AddEntry(dca_eh_all1,"Emb. Photonic pairs","PE");
    leg2->AddEntry(dca_eh_all_m44,"Emb. Matched","l");	
    leg2->AddEntry(dca_eh_all_m11,"Emb. Mis-matched","l");	
    //leg2->AddEntry(dca_eh_all_m12,"!Px2Truth","l");
    //leg2->AddEntry(dca_eh_all_m13,"!IstTruth","l");	
    TCanvas *c11 = new TCanvas ("c11","dca phoe pairs",1800,800);
    c11->Divide(5,2);
    c11->cd(1);
    hx1->Draw("same PE");   
    dca_eh_all1->Draw("same PE");
    dca_eh_all_m11->Draw("same hist");
    //dca_eh_all_m12->Draw("same hist");
    //dca_eh_all_m13->Draw("same hist");
    dca_eh_all_m14->Draw("same hist");
    c11->cd(2);
    hx2->Draw("same PE");   
    dca_eh_all2->Draw("same PE");
    dca_eh_all_m21->Draw("same hist");
    //dca_eh_all_m22->Draw("same hist");
    //dca_eh_all_m23->Draw("same hist");
    dca_eh_all_m24->Draw("same hist");
    c11->cd(3);
    hx3->Draw("same PE");   
    dca_eh_all3->Draw("same PE");
    dca_eh_all_m31->Draw("same hist");
    //dca_eh_all_m32->Draw("same hist");
    //dca_eh_all_m33->Draw("same hist");
    dca_eh_all_m34->Draw("same hist");
    c11->cd(4);
    hx4->Draw("same PE");   
    dca_eh_all4->Draw("same PE");
    dca_eh_all_m41->Draw("same hist");
    //dca_eh_all_m42->Draw("same hist");
    //dca_eh_all_m43->Draw("same hist");
    dca_eh_all_m44->Draw("same hist");
    c11->cd(5);
    hx5->Draw("same PE");   
    dca_eh_all5->Draw("same PE");
    dca_eh_all_m51->Draw("same hist");
    //dca_eh_all_m52->Draw("same hist");
    //dca_eh_all_m53->Draw("same hist");
    dca_eh_all_m54->Draw("same hist");
    c11->cd(6);
    hx6->Draw("same PE");   
    dca_eh_all6->Draw("same PE");
    dca_eh_all_m61->Draw("same hist");
    //dca_eh_all_m62->Draw("same hist");
    //dca_eh_all_m63->Draw("same hist");
    dca_eh_all_m64->Draw("same hist");
    c11->cd(7);
    hx7->Draw("same PE");   
    dca_eh_all7->Draw("same PE");
    dca_eh_all_m71->Draw("same hist");
    //dca_eh_all_m72->Draw("same hist");
    //dca_eh_all_m73->Draw("same hist");
    dca_eh_all_m74->Draw("same hist");
    c11->cd(8);
    hx8->Draw("same PE");   
    dca_eh_all8->Draw("same PE");
    dca_eh_all_m81->Draw("same hist");
    //dca_eh_all_m82->Draw("same hist");
    //dca_eh_all_m83->Draw("same hist");
    dca_eh_all_m84->Draw("same hist");

    c11->cd(9);
    hx9->Draw("same PE");   
    dca_eh_all9->Draw("same PE");
    dca_eh_all_m91->Draw("same hist");
    //dca_eh_all_m92->Draw("same hist");
    //dca_eh_all_m93->Draw("same hist");
    dca_eh_all_m94->Draw("same hist");
    c11->cd(10);
    leg2->Draw();
    
}//End

void getEff(TH1F *h,TH1F *g,TH1F *e){
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	if(temp1>0 && temp>0){
	    e->SetBinContent(i,temp/temp1);
	    e->SetBinError(i,temp/temp1*sqrt(1/temp + 1/temp1));
	}else{
	    e->SetBinContent(i,0);
	    e->SetBinError(i,0);
	}
    }
}
void getEff1(TH1F *h,TH1F *g){
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	if(temp1>0 && temp>0){
	    h->SetBinContent(i,temp/temp1);
	    h->SetBinError(i,temp/temp1*sqrt(1/temp1));
	}else{
	    h->SetBinContent(i,0);
	    h->SetBinError(i,0);
	}
    }
}

void norm(TH1F *h){
    h->Rebin(26);
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
void norm5(TH1F *h){
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
void norm6(TH1F *h){
    h->Rebin(8);
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
void norm3(TH1F *h){
    h->Rebin(26);
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double width = h->GetBinWidth(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1);
	h->SetBinError(i,err/norm1);
    }
    h->Scale(0.14);
}
void norm33(TH1F *h){
    h->Rebin(26);
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double width = h->GetBinWidth(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1);
	h->SetBinError(i,err/norm1);
    }
    h->Scale(0.8);
}
void norm1(TH1F *h){
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
void normW(TH1F *h){
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double width = h->GetBinWidth(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1*h->GetBinCenter(i)*2*TMath::Pi()*width);
	h->SetBinError(i,err/norm1*h->GetBinCenter(i)*2*TMath::Pi()*width);
    }
    cout << " Nomalization " << h->Integral() << endl;
}
void norm2D(TH2F *h){
    double norm1 = h->Integral();
    int binx = h->GetNbinsX();
    int biny = h->GetNbinsY();
    for(int i=1; i<binx+1;i++){
	for(int j=1; j<biny+1;j++){
	    double temp = h->GetBinContent(i,j);
	    double err = h->GetBinError(i,j);
	    h->SetBinContent(i,j,temp/norm1);
	    h->SetBinError(i,j,err/norm1);
	}
    }
    cout << " Nomalization " << h->Integral() << endl;
}
