void eff(int save=1){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3);  
    gStyle->SetPalette(56);
    gStyle->SetPadRightMargin(0.1);
//////////////////////////////////////////////////////////////////
    char dFile[500];
    sprintf(dFile,"./All_Decays_newiso.root");
    sprintf(dFile,"./e_newiso.root");
    TFile *f_D = new TFile(dFile);
    TChain *ch1_e = f_D->Get("Signal_tree");
    TChain *ch2_e = f_D->Get("Gen_tree");
    char dFile1[500];

    sprintf(dFile,"./pion_newiso.root");
    TFile *f_D1 = new TFile(dFile);
    TChain *ch1_pi = f_D1->Get("Signal_tree");
    TChain *ch2_pi = f_D1->Get("Gen_tree");
   
    sprintf(dFile,"./MC_newiso_full.root");
    TFile *f_D2 = new TFile(dFile);
    TChain *ch1_h = f_D2->Get("Signal_tree");
    TChain *ch2_h = f_D2->Get("Gen_tree");


    char dFile1[500];
    sprintf(dFile1,"../../NPE_Ana/production/NPE_Tuples_TuneA10.root");
    TFile *f_D10 = new TFile(dFile1);
    TH2F* ratio_pt_n= f_D10->Get("hHftRatio_n");
    TH2F* ratio_pt_d= f_D10->Get("hHftRatio_d");
    pt_n = (TH1F*)ratio_pt_n->ProjectionX("pt_n",0,10);
    pt_d = (TH1F*)ratio_pt_d->ProjectionX("pt_d",0,10);  
    pt_n1 = (TH1F*)ratio_pt_n->ProjectionX("pt_n1",1,2);
    pt_d1 = (TH1F*)ratio_pt_d->ProjectionX("pt_d1",1,2);  
    pt_n2 = (TH1F*)ratio_pt_n->ProjectionX("pt_n2",2,3);
    pt_d2 = (TH1F*)ratio_pt_d->ProjectionX("pt_d2",2,3);  
    pt_n3 = (TH1F*)ratio_pt_n->ProjectionX("pt_n3",3,4);
    pt_d3 = (TH1F*)ratio_pt_d->ProjectionX("pt_d3",3,4);  
    pt_n4 = (TH1F*)ratio_pt_n->ProjectionX("pt_n4",4,5);
    pt_d4 = (TH1F*)ratio_pt_d->ProjectionX("pt_d4",4,5);  
    pt_n5 = (TH1F*)ratio_pt_n->ProjectionX("pt_n5",5,6);
    pt_d5 = (TH1F*)ratio_pt_d->ProjectionX("pt_d5",5,6);  
    pt_n6 = (TH1F*)ratio_pt_n->ProjectionX("pt_n6",6,7);
    pt_d6 = (TH1F*)ratio_pt_d->ProjectionX("pt_d6",6,7);  
    pt_n7 = (TH1F*)ratio_pt_n->ProjectionX("pt_n7",7,8);
    pt_d7 = (TH1F*)ratio_pt_d->ProjectionX("pt_d7",7,8);  
    pt_n8 = (TH1F*)ratio_pt_n->ProjectionX("pt_n8",8,9);
    pt_d8 = (TH1F*)ratio_pt_d->ProjectionX("pt_d8",8,9);  
    TH2F* ratio_eta_n= f_D10->Get("hHftRatio_eta_n");
    TH2F* ratio_eta_d= f_D10->Get("hHftRatio_eta_d");
    eta_n = (TH1F*)ratio_eta_n->ProjectionX("eta_n",0,10);
    eta_d = (TH1F*)ratio_eta_d->ProjectionX("eta_d",0,10);  
    eta_n1 = (TH1F*)ratio_eta_n->ProjectionX("eta_n1",1,2);
    eta_d1 = (TH1F*)ratio_eta_d->ProjectionX("eta_d1",1,2);  
    eta_n2 = (TH1F*)ratio_eta_n->ProjectionX("eta_n2",2,3);
    eta_d2 = (TH1F*)ratio_eta_d->ProjectionX("eta_d2",2,3);  
    eta_n3 = (TH1F*)ratio_eta_n->ProjectionX("eta_n3",3,4);
    eta_d3 = (TH1F*)ratio_eta_d->ProjectionX("eta_d3",3,4);  
    eta_n4 = (TH1F*)ratio_eta_n->ProjectionX("eta_n4",4,5);
    eta_d4 = (TH1F*)ratio_eta_d->ProjectionX("eta_d4",4,5);  
    eta_n5 = (TH1F*)ratio_eta_n->ProjectionX("eta_n5",5,6);
    eta_d5 = (TH1F*)ratio_eta_d->ProjectionX("eta_d5",5,6);  
    eta_n6 = (TH1F*)ratio_eta_n->ProjectionX("eta_n6",6,7);
    eta_d6 = (TH1F*)ratio_eta_d->ProjectionX("eta_d6",6,7);  
    eta_n7 = (TH1F*)ratio_eta_n->ProjectionX("eta_n7",7,8);
    eta_d7 = (TH1F*)ratio_eta_d->ProjectionX("eta_d7",7,8);  
    eta_n8 = (TH1F*)ratio_eta_n->ProjectionX("eta_n8",8,9);
    eta_d8 = (TH1F*)ratio_eta_d->ProjectionX("eta_d8",8,9);  
    TH2F* ratio_phi_n= f_D10->Get("hHftRatio_phi_n");
    TH2F* ratio_phi_d= f_D10->Get("hHftRatio_phi_d");
    phi_n = (TH1F*)ratio_phi_n->ProjectionX("phi_n",0,10);
    phi_d = (TH1F*)ratio_phi_d->ProjectionX("phi_d",0,10);  
    phi_n1 = (TH1F*)ratio_phi_n->ProjectionX("phi_n1",1,2);
    phi_d1 = (TH1F*)ratio_phi_d->ProjectionX("phi_d1",1,2);  
    phi_n2 = (TH1F*)ratio_phi_n->ProjectionX("phi_n2",2,3);
    phi_d2 = (TH1F*)ratio_phi_d->ProjectionX("phi_d2",2,3);  
    phi_n3 = (TH1F*)ratio_phi_n->ProjectionX("phi_n3",3,4);
    phi_d3 = (TH1F*)ratio_phi_d->ProjectionX("phi_d3",3,4);  
    phi_n4 = (TH1F*)ratio_phi_n->ProjectionX("phi_n4",4,5);
    phi_d4 = (TH1F*)ratio_phi_d->ProjectionX("phi_d4",4,5);  
    phi_n5 = (TH1F*)ratio_phi_n->ProjectionX("phi_n5",5,6);
    phi_d5 = (TH1F*)ratio_phi_d->ProjectionX("phi_d5",5,6);  
    phi_n6 = (TH1F*)ratio_phi_n->ProjectionX("phi_n6",6,7);
    phi_d6 = (TH1F*)ratio_phi_d->ProjectionX("phi_d6",6,7);  
    phi_n7 = (TH1F*)ratio_phi_n->ProjectionX("phi_n7",7,8);
    phi_d7 = (TH1F*)ratio_phi_d->ProjectionX("phi_d7",7,8);  
    phi_n8 = (TH1F*)ratio_phi_n->ProjectionX("phi_n8",8,9);
    phi_d8 = (TH1F*)ratio_phi_d->ProjectionX("phi_d8",8,9);  
    TH2F* ratio_z_n= f_D10->Get("hHftRatio_z_n");
    TH2F* ratio_z_d= f_D10->Get("hHftRatio_z_d");
    z_n = (TH1F*)ratio_z_n->ProjectionX("z_n",0,10);
    z_d = (TH1F*)ratio_z_d->ProjectionX("z_d",0,10);  
    z_n1 = (TH1F*)ratio_z_n->ProjectionX("z_n1",1,2);
    z_d1 = (TH1F*)ratio_z_d->ProjectionX("z_d1",1,2);  
    z_n2 = (TH1F*)ratio_z_n->ProjectionX("z_n2",2,3);
    z_d2 = (TH1F*)ratio_z_d->ProjectionX("z_d2",2,3);  
    z_n3 = (TH1F*)ratio_z_n->ProjectionX("z_n3",3,4);
    z_d3 = (TH1F*)ratio_z_d->ProjectionX("z_d3",3,4);  
    z_n4 = (TH1F*)ratio_z_n->ProjectionX("z_n4",4,5);
    z_d4 = (TH1F*)ratio_z_d->ProjectionX("z_d4",4,5);  
    z_n5 = (TH1F*)ratio_z_n->ProjectionX("z_n5",5,6);
    z_d5 = (TH1F*)ratio_z_d->ProjectionX("z_d5",5,6);  
    z_n6 = (TH1F*)ratio_z_n->ProjectionX("z_n6",6,7);
    z_d6 = (TH1F*)ratio_z_d->ProjectionX("z_d6",6,7);  
    z_n7 = (TH1F*)ratio_z_n->ProjectionX("z_n7",7,8);
    z_d7 = (TH1F*)ratio_z_d->ProjectionX("z_d7",7,8);  
    z_n8 = (TH1F*)ratio_z_n->ProjectionX("z_n8",8,9);
    z_d8 = (TH1F*)ratio_z_d->ProjectionX("z_d8",8,9);  
   
    if(save){
	TH2F *pt_pi_r = new TH2F("pt_pi_r","pt_pi_r",20,0,10,10,0,10); 
	TH2F *pt_pi2_r = new TH2F("pt_pi2_r","pt_pi2_r",20,0,10,10,0,10); 
	TH2F *pt_e_r = new TH2F("pt_e_r","pt_e_r",20,0,10,10,0,10); 
	TH2F *pt_e2_r = new TH2F("pt_e2_r","pt_e2_r",20,0,10,10,0,10);
 
	TH2F *eta_pi_r = new TH2F("eta_pi_r","eta_pi_r",50,-1,1,10,0,10); 
	TH2F *eta_pi2_r = new TH2F("eta_pi2_r","eta_pi2_r",50,-1,1,10,0,10); 
	TH2F *eta_e_r = new TH2F("eta_e_r","eta_e_r",50,-1,1,10,0,10); 
	TH2F *eta_e2_r = new TH2F("eta_e2_r","eta_e2_r",50,-1,1,10,0,10); 

	TH2F *phi_pi_r = new TH2F("phi_pi_r","phi_pi_r",20,-1,1,10,0,10); 
	TH2F *phi_pi2_r = new TH2F("phi_pi2_r","phi_pi2_r",20,-1,1,10,0,10); 
	TH2F *phi_e_r = new TH2F("phi_e_r","phi_e_r",20,-1,1,10,0,10); 
	TH2F *phi_e2_r = new TH2F("phi_e2_r","phi_e2_r",20,-1,1,10,0,10); 

	TH2F *z_pi_r = new TH2F("z_pi_r","z_pi_r",60,-6,6,10,0,10); 
	TH2F *z_pi2_r = new TH2F("z_pi2_r","z_pi2_r",60,-6,6,10,0,10); 
	TH2F *z_e_r = new TH2F("z_e_r","z_e_r",60,-6,6,10,0,10); 
	TH2F *z_e2_r = new TH2F("z_e2_r","z_e2_r",60,-6,6,10,0,10); 

	TH1F *pt = new TH1F("pt","pt",50,0,10);
	TH1F *pt2 = new TH1F("pt2","pt2",50,0,10); 
	TH1F *pt_m1 = new TH1F("pt_m1","pt_m1",50,0,10);
	TH1F *pt2_m1 = new TH1F("pt2_m1","pt2_m1",50,0,10); 
	TH1F *pt_m2 = new TH1F("pt_m2","pt_m2",50,0,10);
	TH1F *pt2_m2 = new TH1F("pt2_m2","pt2_m2",50,0,10); 
	TH1F *pt_m3 = new TH1F("pt_m3","pt_m3",50,0,10);
	TH1F *pt2_m3 = new TH1F("pt2_m3","pt2_m3",50,0,10); 
	TH1F *pt_pi = new TH1F("pt_pi","pt_pi",50,0,10); 
	TH1F *pt_pi2 = new TH1F("pt_pi2","pt_pi2",50,0,10); 
	TH1F *pt_gamma = new TH1F("pt_gamma","pt_gamma",50,0,10); 
	TH1F *pt_gamma2 = new TH1F("pt_gamma2","pt_gamma2",50,0,10); 
	TH1F *pt_pi0 = new TH1F("pt_pi0","pt_pi0",50,0,10); 
	TH1F *pt_pi02 = new TH1F("pt_pi02","pt_pi02",50,0,10); 
	TH1F *pt_eta = new TH1F("pt_eta","pt_eta",50,0,10); 
	TH1F *pt_eta2 = new TH1F("pt_eta2","pt_eta2",50,0,10); 
	TH1F *pt_pi0_gamma = new TH1F("pt_pi0_gamma","pt_pi0_gamma",50,0,10); 
	TH1F *pt_pi0_gamma2 = new TH1F("pt_pi0_gamma2","pt_pi0_gamma2",50,0,10); 
	TH1F *pt_eta_gamma = new TH1F("pt_eta_gamma","pt_eta_gamma",50,0,10); 
	TH1F *pt_eta_gamma2 = new TH1F("pt_eta_gamma2","pt_eta_gamma2",50,0,10); 
	TH1F *pt_g = new TH1F("pt_g","pt_g",50,0,10);
	TH1F *pt_g_pi = new TH1F("pt_g_pi","pt_g_pi",50,0,10);
	TH1F *pt_g_gamma = new TH1F("pt_g_gamma","pt_g_gamma",50,0,10);
	TH1F *pt_g_pi0 = new TH1F("pt_g_pi0","pt_g_pi0",50,0,10);
	TH1F *pt_g_eta = new TH1F("pt_g_eta","pt_g_eta",50,0,10);
	TH1F *pt_g_pi0_gamma = new TH1F("pt_g_pi0_gamma","pt_g_pi0_gamma",50,0,10);
	TH1F *pt_g_eta_gamma = new TH1F("pt_g_eta_gamma","pt_g_eta_gamma",50,0,10);

	TH1F *phi = new TH1F("phi","phi",20,-3.15,3.15);
	TH1F *phi2 = new TH1F("phi2","phi2",20,-3.15,3.15); 
	TH1F *phi_pi = new TH1F("phi_pi","phi_pi",20,-3.15,3.15); 
	TH1F *phi_pi2 = new TH1F("phi_pi2","phi_pi2",20,-3.15,3.15); 
	TH1F *phi_gamma = new TH1F("phi_gamma","phi_gamma",20,-3.15,3.15); 
	TH1F *phi_gamma2 = new TH1F("phi_gamma2","phi_gamma2",20,-3.15,3.15); 
	TH1F *phi_pi0 = new TH1F("phi_pi0","phi_pi0",20,-3.15,3.15); 
	TH1F *phi_pi02 = new TH1F("phi_pi02","phi_pi02",20,-3.15,3.15); 
	TH1F *phi_eta = new TH1F("phi_eta","phi_eta",20,-3.15,3.15); 
	TH1F *phi_eta2 = new TH1F("phi_eta2","phi_eta2",20,-3.15,3.15); 
	TH1F *phi_pi0_gamma = new TH1F("phi_pi0_gamma","phi_pi0_gamma",20,-3.15,3.15); 
	TH1F *phi_pi0_gamma2 = new TH1F("phi_pi0_gamma2","phi_pi0_gamma2",20,-3.15,3.15); 
	TH1F *phi_eta_gamma = new TH1F("phi_eta_gamma","phi_eta_gamma",20,-3.15,3.15); 
	TH1F *phi_eta_gamma2 = new TH1F("phi_eta_gamma2","phi_eta_gamma2",20,-3.15,3.15); 
	TH1F *phi_g = new TH1F("phi_g","phi_g",20,-3.15,3.15);
	TH1F *phi_g_pi = new TH1F("phi_g_pi","phi_g_pi",20,-3.15,3.15);
	TH1F *phi_g_gamma = new TH1F("phi_g_gamma","phi_g_gamma",20,-3.15,3.15);
	TH1F *phi_g_pi0 = new TH1F("phi_g_pi0","phi_g_pi0",20,-3.15,3.15);
	TH1F *phi_g_eta = new TH1F("phi_g_eta","phi_g_eta",20,-3.15,3.15);
	TH1F *phi_g_pi0_gamma = new TH1F("phi_g_pi0_gamma","phi_g_pi0_gamma",20,-3.15,3.15);
	TH1F *phi_g_eta_gamma = new TH1F("phi_g_eta_gamma","phi_g_eta_gamma",20,-3.15,3.15);

	TH1F *z = new TH1F("z","z",20,-6,6);
	TH1F *z2 = new TH1F("z2","z2",20,-6,6); 
	TH1F *z_pi = new TH1F("z_pi","z_pi",20,-6,6); 
	TH1F *z_pi2 = new TH1F("z_pi2","z_pi2",20,-6,6); 
	TH1F *z_gamma = new TH1F("z_gamma","z_gamma",20,-6,6); 
	TH1F *z_gamma2 = new TH1F("z_gamma2","z_gamma2",20,-6,6); 
	TH1F *z_pi0 = new TH1F("z_pi0","z_pi0",20,-6,6); 
	TH1F *z_pi02 = new TH1F("z_pi02","z_pi02",20,-6,6); 
	TH1F *z_eta = new TH1F("z_eta","z_eta",20,-6,6); 
	TH1F *z_eta2 = new TH1F("z_eta2","z_eta2",20,-6,6); 
	TH1F *z_pi0_gamma = new TH1F("z_pi0_gamma","z_pi0_gamma",20,-6,6); 
	TH1F *z_pi0_gamma2 = new TH1F("z_pi0_gamma2","z_pi0_gamma2",20,-6,6); 
	TH1F *z_eta_gamma = new TH1F("z_eta_gamma","z_eta_gamma",20,-6,6); 
	TH1F *z_eta_gamma2 = new TH1F("z_eta_gamma2","z_eta_gamma2",20,-6,6); 
	TH1F *z_g = new TH1F("z_g","z_g",20,-6,6);
	TH1F *z_g_pi = new TH1F("z_g_pi","z_g_pi",20,-6,6);
	TH1F *z_g_gamma = new TH1F("z_g_gamma","z_g_gamma",20,-6,6);
	TH1F *z_g_pi0 = new TH1F("z_g_pi0","z_g_pi0",20,-6,6);
	TH1F *z_g_eta = new TH1F("z_g_eta","z_g_eta",20,-6,6);
	TH1F *z_g_pi0_gamma = new TH1F("z_g_pi0_gamma","z_g_pi0_gamma",20,-6,6);
	TH1F *z_g_eta_gamma = new TH1F("z_g_eta_gamma","z_g_eta_gamma",20,-6,6);


	TH1F *eta = new TH1F("eta","eta",50,-1,1);
	TH1F *eta2 = new TH1F("eta2","eta2",50,-1,1);
	TH1F *eta_pi = new TH1F("eta_pi","eta_pi",50,-1,1);
	TH1F *eta_pi2 = new TH1F("eta_pi2","eta_pi2",50,-1,1);
	TH1F *eta_gamma = new TH1F("eta_gamma","eta_gamma",50,-1,1);
	TH1F *eta_gamma2 = new TH1F("eta_gamma2","eta_gamma2",50,-1,1);
	TH1F *eta_pi0 = new TH1F("eta_pi0","eta_pi0",50,-1,1);
	TH1F *eta_pi02 = new TH1F("eta_pi02","eta_pi02",50,-1,1);
	TH1F *eta_eta = new TH1F("eta_eta","eta_eta",50,-1,1);
	TH1F *eta_eta2 = new TH1F("eta_eta2","eta_eta2",50,-1,1);
	TH1F *eta_pi0_gamma = new TH1F("eta_pi0_gamma","eta_pi0_gamma",50,-1,1);
	TH1F *eta_pi0_gamma2 = new TH1F("eta_pi0_gamma2","eta_pi0_gamma2",50,-1,1);
	TH1F *eta_eta_gamma = new TH1F("eta_eta_gamma","eta_eta_gamma",50,-1,1);
	TH1F *eta_eta_gamma2 = new TH1F("eta_eta_gamma2","eta_eta_gamma2",50,-1,1);
	TH1F *eta_g = new TH1F("eta_g","eta_g",50,-1,1);
	TH1F *eta_g_pi = new TH1F("eta_g_pi","eta_g_pi",50,-1,1);
	TH1F *eta_g_gamma = new TH1F("eta_g_gamma","eta_g_gamma",50,-1,1);
	TH1F *eta_g_pi0 = new TH1F("eta_g_pi0","eta_g_pi0",50,-1,1);
	TH1F *eta_g_eta = new TH1F("eta_g_eta","eta_g_eta",50,-1,1);
	TH1F *eta_g_pi0_gamma = new TH1F("eta_g_pi0_gamma","eta_g_pi0_gamma",50,-1,1);
	TH1F *eta_g_eta_gamma = new TH1F("eta_g_eta_gamma","eta_g_eta_gamma",50,-1,1);


	float s_vz;
	float s_ox;
	float s_oy;
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
	float s_cen;
	float s_eta;
	float s_z;
	float s_ox;
	float s_oy;
	float s_parentphi; 
	ch2_e->SetBranchAddress("gen_ox",&s_ox);
	ch2_e->SetBranchAddress("gen_oy",&s_oy);
	ch2_e->SetBranchAddress("gen_pt",&s_pt);
	ch2_e->SetBranchAddress("gen_vz",&s_z);
	ch2_e->SetBranchAddress("event_centrality",&s_cen);
	ch2_e->SetBranchAddress("gen_dcaxy",&s_dcaxy);
	ch2_e->SetBranchAddress("gen_id",&s_id);
	ch2_e->SetBranchAddress("gen_eta",&s_eta);
	ch2_e->SetBranchAddress("gen_phi",&s_phi);
	ch2_e->SetBranchAddress("gen_phi2",&s_parentphi);
	ch2_e->SetBranchAddress("gen_head",&s_head);
	ch2_e->SetBranchAddress("gen_parentid",&s_parentid);
	ch2_e->SetBranchAddress("gen_gparentid",&s_gparentid);
	ch2_e->SetBranchAddress("gen_ggparentid",&s_ggparentid);
	ch2_e->SetBranchAddress("gen_parentpt",&s_parentpt);
	ch2_e->SetBranchAddress("gen_gparentpt",&s_gparentpt);
	ch2_e->SetBranchAddress("gen_ggparentpt",&s_ggparentpt); 

	for(int i =0;i<ch2_e->GetEntries();i++){
	    ch2_e->GetEntry(i);
	    if(i%1000000==0)cout << "on e gen loop " << i << " of " << ch2_e->GetEntries() << endl;	   
	    if(fabs(s_eta)>0.7)continue;
	    if(fabs(s_pt)<0.6)continue;
	    //if(sqrt(s_ox*s_ox+s_oy*s_oy)>2)continue;	  
	    if(s_parentid==0 && s_head==0 && (s_id==3 || s_id==2)){//s_parentid==0&& s_head==0
		pt_g->Fill(s_pt);
		eta_g->Fill(s_eta);
		phi_g->Fill(s_phi);
		z_g->Fill(s_z);
	    }	
	}
	ch2_pi->SetBranchAddress("gen_ox",&s_ox);
	ch2_pi->SetBranchAddress("gen_oy",&s_oy);
	ch2_pi->SetBranchAddress("gen_pt",&s_pt);
	ch2_pi->SetBranchAddress("gen_vz",&s_z);
	ch2_pi->SetBranchAddress("event_centrality",&s_cen);
	ch2_pi->SetBranchAddress("gen_dcaxy",&s_dcaxy);
	ch2_pi->SetBranchAddress("gen_id",&s_id);
	ch2_pi->SetBranchAddress("gen_eta",&s_eta);
	ch2_pi->SetBranchAddress("gen_phi",&s_phi);
	ch2_pi->SetBranchAddress("gen_phi2",&s_parentphi);
	ch2_pi->SetBranchAddress("gen_head",&s_head);
	ch2_pi->SetBranchAddress("gen_parentid",&s_parentid);
	ch2_pi->SetBranchAddress("gen_gparentid",&s_gparentid);
	ch2_pi->SetBranchAddress("gen_ggparentid",&s_ggparentid);
	ch2_pi->SetBranchAddress("gen_parentpt",&s_parentpt);
	ch2_pi->SetBranchAddress("gen_gparentpt",&s_gparentpt);
	ch2_pi->SetBranchAddress("gen_ggparentpt",&s_ggparentpt); 
	for(int i =0;i<ch2_pi->GetEntries();i++){
	    ch2_pi->GetEntry(i);
	    if(i%1000000==0)cout << "on pion gen loop " << i << " of " << ch2_pi->GetEntries() << endl;	   
	    if(fabs(s_eta)>0.7)continue;
	    //if(fabs(s_pt)<0.6)continue;
	    //if(sqrt(s_ox*s_ox+s_oy*s_oy)>2)continue;
	    if((s_id==8 ||s_id==9) && s_parentid==0){
		pt_g_pi->Fill(s_pt);
		eta_g_pi->Fill(s_eta);
		phi_g_pi->Fill(s_phi);
		z_g_pi->Fill(s_z);
	    } 
	}
	ch2_h->SetBranchAddress("gen_ox",&s_ox);
	ch2_h->SetBranchAddress("gen_oy",&s_oy);
	ch2_h->SetBranchAddress("gen_pt",&s_pt);
	ch2_h->SetBranchAddress("gen_vz",&s_z);
	ch2_h->SetBranchAddress("event_centrality",&s_cen);
	ch2_h->SetBranchAddress("gen_dcaxy",&s_dcaxy);
	ch2_h->SetBranchAddress("gen_id",&s_id);
	ch2_h->SetBranchAddress("gen_eta",&s_eta);
	ch2_h->SetBranchAddress("gen_phi",&s_phi);
	ch2_h->SetBranchAddress("gen_phi2",&s_parentphi);
	ch2_h->SetBranchAddress("gen_head",&s_head);
	ch2_h->SetBranchAddress("gen_parentid",&s_parentid);
	ch2_h->SetBranchAddress("gen_gparentid",&s_gparentid);
	ch2_h->SetBranchAddress("gen_ggparentid",&s_ggparentid);
	ch2_h->SetBranchAddress("gen_parentpt",&s_parentpt);
	ch2_h->SetBranchAddress("gen_gparentpt",&s_gparentpt);
	ch2_h->SetBranchAddress("gen_ggparentpt",&s_ggparentpt); 
	for(int i =0;i<ch2_h->GetEntries();i++){
	    ch2_h->GetEntry(i);
	    if(i%1000000==0)cout << "on phoe loop " << i << " of " << ch2_h->GetEntries() << endl;	   
	    if(fabs(s_eta)>0.7)continue;
	    if(fabs(s_pt)<0.6)continue;
	    //if(sqrt(s_ox*s_ox+s_oy*s_oy)>2)continue;	  
	    if(!(s_id==3 || s_id==2))continue;
	    if(s_parentid==1 && s_gparentid==0 && s_ggparentid==0 && s_head==1){
		
                //if(sqrt(s_ox*s_ox+s_oy*s_oy)>2)continue;
		pt_g_gamma->Fill(s_pt);
		eta_g_gamma->Fill(s_eta);
		phi_g_gamma->Fill(s_phi);
		z_g_gamma->Fill(s_z);
	    }
	    if(s_head==7 && s_parentid==7){
		pt_g_pi0->Fill(s_pt);
		eta_g_pi0->Fill(s_eta);
		phi_g_pi0->Fill(s_phi);
		z_g_pi0->Fill(s_z);
	    }
	    if(s_head==17 && s_parentid==17){
		pt_g_eta->Fill(s_pt);
		eta_g_eta->Fill(s_eta);
		phi_g_eta->Fill(s_phi);
		z_g_eta->Fill(s_z);
	    }
	    if(s_head==7 && s_parentid==1){
		pt_g_pi0_gamma->Fill(s_pt);
		eta_g_pi0_gamma->Fill(s_eta);
		phi_g_pi0_gamma->Fill(s_phi);
		z_g_pi0_gamma->Fill(s_z);
	    }
	    if(s_head==17 && s_parentid==1){
		pt_g_eta_gamma->Fill(s_pt);
		eta_g_eta_gamma->Fill(s_eta);
		phi_g_eta_gamma->Fill(s_phi);
		z_g_eta_gamma->Fill(s_z);
	    }
	}
	float s_px1;
	float s_px2;
	float s_ist;
	float s_ssd;
	ch1_e->SetBranchAddress("sig_ox",&s_ox);
	ch1_e->SetBranchAddress("sig_oy",&s_oy);
	ch1_e->SetBranchAddress("sig_vz",&s_z);
	ch1_e->SetBranchAddress("sig_pt",&s_pt);
	ch1_e->SetBranchAddress("sig_Pxl1Truth",&s_px1);
	ch1_e->SetBranchAddress("sig_Pxl2Truth",&s_px2);
	ch1_e->SetBranchAddress("sig_IstTruth",&s_ist);
	ch1_e->SetBranchAddress("sig_SsdTruth",&s_ssd);
	ch1_e->SetBranchAddress("event_centrality",&s_cen);
	ch1_e->SetBranchAddress("sig_dcaxy",&s_dcaxy);
	ch1_e->SetBranchAddress("sig_hft",&s_hft);
	ch1_e->SetBranchAddress("sig_id",&s_id);
	ch1_e->SetBranchAddress("sig_eta",&s_eta);
	ch1_e->SetBranchAddress("sig_phi",&s_phi);
	ch1_e->SetBranchAddress("sig_phi2",&s_parentphi);
	ch1_e->SetBranchAddress("sig_head",&s_head);
	ch1_e->SetBranchAddress("sig_isiso",&s_iso);
	ch1_e->SetBranchAddress("sig_parentid",&s_parentid);
	ch1_e->SetBranchAddress("sig_gparentid",&s_gparentid);
	ch1_e->SetBranchAddress("sig_ggparentid",&s_ggparentid);
	ch1_e->SetBranchAddress("sig_parentpt",&s_parentpt);
	ch1_e->SetBranchAddress("sig_gparentpt",&s_gparentpt);
	ch1_e->SetBranchAddress("sig_ggparentpt",&s_ggparentpt);  
	for(int i =0;i<ch1_e->GetEntries();i++){
	    ch1_e->GetEntry(i);
	    if(i%100000==0)cout << "on e loop " << i << " of " << ch1_e->GetEntries() << endl;
	    if(fabs(s_pt)<0.6)continue;
	    if(fabs(s_eta)>0.7)continue;	    
	    if(sqrt(s_ox*s_ox+s_oy*s_oy)>1)continue;
	    if(s_parentid==0&& s_head==0&& s_gparentid==0&&(s_id==3 || s_id==2)){//s_parentid==0&& s_gparentid==0
		pt->Fill(s_pt);
		if(s_px1>0)pt_m1->Fill(s_pt);
		if(s_px1>0&&s_px2>0)pt_m2->Fill(s_pt);
		if(s_px1>0&&s_px2>0&&s_ist>0)pt_m3->Fill(s_pt);
		eta->Fill(s_eta);
		phi->Fill(s_phi);
		z->Fill(s_z);
		if(s_hft==1)pt2->Fill(s_pt);
		if(s_hft==1)eta2->Fill(s_eta);
		if(s_hft==1)phi2->Fill(s_phi);
		if(s_hft==1)z2->Fill(s_z);
       
		pt_e_r->Fill(s_pt,s_cen);	
		eta_e_r->Fill(s_eta,s_cen);
		phi_e_r->Fill(s_phi/TMath::Pi(),s_cen);      
		z_e_r->Fill(s_z,s_cen);		
		if(s_hft==1){

		    pt_e2_r->Fill(s_pt,s_cen);
		    eta_e2_r->Fill(s_eta,s_cen);
		    phi_e2_r->Fill(s_phi/TMath::Pi(),s_cen);
		    z_e2_r->Fill(s_z,s_cen);
		}
	    }
	}
	ch1_pi->SetBranchAddress("sig_ox",&s_ox);
	ch1_pi->SetBranchAddress("sig_oy",&s_oy);
	ch1_pi->SetBranchAddress("sig_vz",&s_z);
	ch1_pi->SetBranchAddress("sig_pt",&s_pt);
	ch1_pi->SetBranchAddress("event_centrality",&s_cen);
	ch1_pi->SetBranchAddress("sig_dcaxy",&s_dcaxy);
	ch1_pi->SetBranchAddress("sig_hft",&s_hft);
	ch1_pi->SetBranchAddress("sig_id",&s_id);
	ch1_pi->SetBranchAddress("sig_eta",&s_eta);
	ch1_pi->SetBranchAddress("sig_phi",&s_phi);
	ch1_pi->SetBranchAddress("sig_phi2",&s_parentphi);
	ch1_pi->SetBranchAddress("sig_head",&s_head);
	ch1_pi->SetBranchAddress("sig_isiso",&s_iso);
	ch1_pi->SetBranchAddress("sig_parentid",&s_parentid);
	ch1_pi->SetBranchAddress("sig_gparentid",&s_gparentid);
	ch1_pi->SetBranchAddress("sig_ggparentid",&s_ggparentid);
	ch1_pi->SetBranchAddress("sig_parentpt",&s_parentpt);
	ch1_pi->SetBranchAddress("sig_gparentpt",&s_gparentpt);
	ch1_pi->SetBranchAddress("sig_ggparentpt",&s_ggparentpt);  
	for(int i =0;i<ch1_pi->GetEntries();i++){
	    ch1_pi->GetEntry(i);
	    if(i%100000==0)cout << "on pion loop " << i << " of " << ch1_pi->GetEntries() << endl;
	    if(fabs(s_pt)<0.6)continue;
	    //if(sqrt(s_ox*s_ox+s_oy*s_oy)>2)continue;
	    if((s_id==8 ||s_id==9) && s_parentid==0){
		pt_pi->Fill(s_pt);
		eta_pi->Fill(s_eta);
		phi_pi->Fill(s_phi);
		z_pi->Fill(s_z);
		if(s_hft==1){
		    pt_pi2->Fill(s_pt);
		    eta_pi2->Fill(s_eta);
		    phi_pi2->Fill(s_phi);
		    z_pi2->Fill(s_z);
		}
		pt_pi_r->Fill(s_pt,s_cen);	
		eta_pi_r->Fill(s_eta,s_cen);
		phi_pi_r->Fill(s_phi/TMath::Pi(),s_cen);      ///TMath::Pi()
		z_pi_r->Fill(s_z,s_cen);		
		if(s_hft==1){
		    pt_pi2_r->Fill(s_pt,s_cen);
		    eta_pi2_r->Fill(s_eta,s_cen);
		    phi_pi2_r->Fill(s_phi/TMath::Pi(),s_cen);
		    z_pi2_r->Fill(s_z,s_cen);
		}
	    }
	}
	ch1_h->SetBranchAddress("sig_ox",&s_ox);
	ch1_h->SetBranchAddress("sig_oy",&s_oy);
	ch1_h->SetBranchAddress("sig_vz",&s_z);
	ch1_h->SetBranchAddress("sig_pt",&s_pt);
	ch1_h->SetBranchAddress("event_centrality",&s_cen);
	ch1_h->SetBranchAddress("sig_dcaxy",&s_dcaxy);
	ch1_h->SetBranchAddress("sig_hft",&s_hft);
	ch1_h->SetBranchAddress("sig_id",&s_id);
	ch1_h->SetBranchAddress("sig_eta",&s_eta);
	ch1_h->SetBranchAddress("sig_phi",&s_phi);
	ch1_h->SetBranchAddress("sig_Pxl1Truth",&s_px1);
	ch1_h->SetBranchAddress("sig_Pxl2Truth",&s_px2);
	ch1_h->SetBranchAddress("sig_IstTruth",&s_ist);
	ch1_h->SetBranchAddress("sig_SsdTruth",&s_ssd);
	ch1_h->SetBranchAddress("sig_phi2",&s_parentphi);
	ch1_h->SetBranchAddress("sig_head",&s_head);
	ch1_h->SetBranchAddress("sig_isiso",&s_iso);
	ch1_h->SetBranchAddress("sig_parentid",&s_parentid);
	ch1_h->SetBranchAddress("sig_gparentid",&s_gparentid);
	ch1_h->SetBranchAddress("sig_ggparentid",&s_ggparentid);
	ch1_h->SetBranchAddress("sig_parentpt",&s_parentpt);
	ch1_h->SetBranchAddress("sig_gparentpt",&s_gparentpt);
	ch1_h->SetBranchAddress("sig_ggparentpt",&s_ggparentpt);  
	for(int i =0;i<ch1_h->GetEntries();i++){
	    ch1_h->GetEntry(i);
	    if(i%100000==0)cout << "on phoe loop " << i << " of " << ch1_h->GetEntries() << endl;
	    if(fabs(s_pt)<0.6)continue;
	    //if(sqrt(s_ox*s_ox+s_oy*s_oy)>2)continue;
	    if(!(s_id==3 || s_id==2))continue;
	    if(s_head==1 && s_parentid==1){
		//if(sqrt(s_ox*s_ox+s_oy*s_oy)>2)continue;
		pt_gamma->Fill(s_pt);
		eta_gamma->Fill(s_eta);
		phi_gamma->Fill(s_phi);
		z_gamma->Fill(s_z);
		if(s_hft==1)pt_gamma2->Fill(s_pt);
		if(s_hft==1)eta_gamma2->Fill(s_eta);
		if(s_hft==1)phi_gamma2->Fill(s_phi);
		if(s_hft==1)z_gamma2->Fill(s_z);
	    }
	    if(s_head==7 && s_parentid==7){
		pt_pi0->Fill(s_pt);
		eta_pi0->Fill(s_eta);
		phi_pi0->Fill(s_phi);
		z_pi0->Fill(s_z);
		if(s_hft==1)pt_pi02->Fill(s_pt);
		if(s_hft==1)eta_pi02->Fill(s_eta);
		if(s_hft==1)phi_pi02->Fill(s_phi);
		if(s_hft==1)z_pi02->Fill(s_z);
		if(s_hft==1){
		    if(s_ist>0)pt2_m1->Fill(s_pt);
		    if(s_ist>0&&s_px2>0)pt2_m2->Fill(s_pt);
		    if(s_px1>0&&s_px2>0&&s_ist>0)pt2_m3->Fill(s_pt);
		}
	    }
	    if(s_head==17 && s_parentid==17){
		pt_eta->Fill(s_pt);
		eta_eta->Fill(s_eta);
		phi_eta->Fill(s_phi);
		z_eta->Fill(s_z);
		if(s_hft==1)pt_eta2->Fill(s_pt);
		if(s_hft==1)eta_eta2->Fill(s_eta);
		if(s_hft==1)phi_eta2->Fill(s_phi);
		if(s_hft==1)z_eta2->Fill(s_z);
	    }
	    if(s_head==7 && s_parentid==1){
		pt_pi0_gamma->Fill(s_pt);
		eta_pi0_gamma->Fill(s_eta);
		phi_pi0_gamma->Fill(s_phi);
		z_pi0_gamma->Fill(s_z);
		if(s_hft==1)pt_pi0_gamma2->Fill(s_pt);
		if(s_hft==1)eta_pi0_gamma2->Fill(s_eta);
		if(s_hft==1)phi_pi0_gamma2->Fill(s_phi);
		if(s_hft==1)z_pi0_gamma2->Fill(s_z);
	    }
	    if(s_head==17 && s_parentid==1){
		pt_eta_gamma->Fill(s_pt);
		eta_eta_gamma->Fill(s_eta);
		phi_eta_gamma->Fill(s_phi);
		z_eta_gamma->Fill(s_z);
		if(s_hft==1)pt_eta_gamma2->Fill(s_pt);
		if(s_hft==1)eta_eta_gamma2->Fill(s_eta);
		if(s_hft==1)phi_eta_gamma2->Fill(s_phi);
		if(s_hft==1)z_eta_gamma2->Fill(s_z);		
	    }
	}
	TFile f("root/ForEff.root","RECREATE");

	pt_pi_r->Write();
	pt_pi2_r->Write();
	pt_e_r->Write();
	pt_e2_r->Write();
	eta_pi_r->Write();
	eta_pi2_r->Write();
	eta_e_r->Write();
	eta_e2_r->Write();
	phi_pi_r->Write();
	phi_pi2_r->Write();
	phi_e_r->Write();
	phi_e2_r->Write();
	z_pi_r->Write();
	z_pi2_r->Write();
	z_e_r->Write();
	z_e2_r->Write();


	pt->Write();
	pt_gamma->Write();
	pt2->Write();
	pt2_m1->Write();
	pt2_m2->Write();
	pt2_m3->Write();
	pt_m1->Write();
	pt_m2->Write();
	pt_m3->Write();
	pt_g->Write();
	pt_pi->Write();
	pt_g_pi->Write();
	pt_pi2->Write();
	pt_g_gamma->Write();
	pt_gamma2->Write();
	pt_pi0->Write();
	pt_g_pi0->Write();
	pt_pi02->Write();
	pt_eta->Write();
	pt_g_eta->Write();
	pt_eta2->Write();
	pt_pi0_gamma->Write();
	pt_g_pi0_gamma->Write();
	pt_pi0_gamma2->Write();
	pt_eta_gamma->Write();
	pt_eta_gamma2->Write();
	pt_g_eta_gamma->Write();
	eta->Write();
	eta2->Write();
	eta_g->Write();
	eta_pi->Write();
	eta_g_pi->Write();
	eta_pi2->Write();
	eta_gamma->Write();
	eta_g_gamma->Write();
	eta_gamma2->Write();
	eta_pi0->Write();
	eta_g_pi0->Write();
	eta_pi02->Write();
	eta_eta->Write();
	eta_g_eta->Write();
	eta_eta2->Write();
	eta_pi0_gamma->Write();
	eta_g_pi0_gamma->Write();
	eta_pi0_gamma2->Write();
	eta_eta_gamma->Write();
	eta_eta_gamma2->Write();
	eta_g_eta_gamma->Write();

	phi->Write();
	phi_gamma->Write();
	phi2->Write();
	phi_g->Write();
	phi_pi->Write();
	phi_g_pi->Write();
	phi_pi2->Write();
	phi_g_gamma->Write();
	phi_gamma2->Write();
	phi_pi0->Write();
	phi_g_pi0->Write();
	phi_pi02->Write();
	phi_eta->Write();
	phi_g_eta->Write();
	phi_eta2->Write();
	phi_pi0_gamma->Write();
	phi_g_pi0_gamma->Write();
	phi_pi0_gamma2->Write();
	phi_eta_gamma->Write();
	phi_eta_gamma2->Write();
	phi_g_eta_gamma->Write();

	z->Write();
	z_gamma->Write();
	z2->Write();
	z_g->Write();
	z_pi->Write();
	z_g_pi->Write();
	z_pi2->Write();
	z_g_gamma->Write();
	z_gamma2->Write();
	z_pi0->Write();
	z_g_pi0->Write();
	z_pi02->Write();
	z_eta->Write();
	z_g_eta->Write();
	z_eta2->Write();
	z_pi0_gamma->Write();
	z_g_pi0_gamma->Write();
	z_pi0_gamma2->Write();
	z_eta_gamma->Write();
	z_eta_gamma2->Write();
	z_g_eta_gamma->Write();

    }
    if(save==0){
	TFile * f= new TFile("root/ForEff.root");

	pt_pi_r=(TH2F*)f->Get("pt_pi_r");    
	pt_pi2_r=(TH2F*)f->Get("pt_pi2_r");
	pt_e_r=(TH2F*)f->Get("pt_e_r");   
	pt_e2_r=(TH2F*)f->Get("pt_e2_r");
	eta_pi_r=(TH2F*)f->Get("eta_pi_r");     
	eta_pi2_r=(TH2F*)f->Get("eta_pi2_r");
	eta_e_r=(TH2F*)f->Get("eta_e_r");  
	phi_pi_r=(TH2F*)f->Get("phi_pi_r"); 
	phi_pi2_r=(TH2F*)f->Get("phi_pi2_r");
	phi_e_r=(TH2F*)f->Get("phi_e_r");  
	phi_e2_r=(TH2F*)f->Get("phi_e2_r");
	z_pi_r=(TH2F*)f->Get("z_pi_r");   
	z_e_r=(TH2F*)f->Get("z_e_r");
	z_e2_r=(TH2F*)f->Get("z_e2_r");

	pt=(TH1F*)f->Get("pt");
	pt2=(TH1F*)f->Get("pt2");
	pt2_m1=(TH1F*)f->Get("pt2_m1");
	pt2_m2=(TH1F*)f->Get("pt2_m2");
	pt2_m3=(TH1F*)f->Get("pt2_m3");
	pt_m1=(TH1F*)f->Get("pt_m1");
	pt_m2=(TH1F*)f->Get("pt_m2");
	pt_m3=(TH1F*)f->Get("pt_m3");
	pt_g=(TH1F*)f->Get("pt_g");
	pt_pi=(TH1F*)f->Get("pt_pi");
	pt_pi2=(TH1F*)f->Get("pt_pi2");	
	pt_g_pi=(TH1F*)f->Get("pt_g_pi");
	pt_gamma=(TH1F*)f->Get("pt_gamma");
	pt_g_gamma=(TH1F*)f->Get("pt_g_gamma");	
	pt_gamma2=(TH1F*)f->Get("pt_gamma2");
	pt_pi0=(TH1F*)f->Get("pt_pi0");	
	pt_g_pi0=(TH1F*)f->Get("pt_g_pi0");
	pt_pi02=(TH1F*)f->Get("pt_pi02");
	pt_eta=(TH1F*)f->Get("pt_eta");	
	pt_g_eta=(TH1F*)f->Get("pt_g_eta");
	pt_eta2=(TH1F*)f->Get("pt_eta2");	
	pt_eta_gamma2=(TH1F*)f->Get("pt_eta_gamma2");	
	pt_pi0_gamma=(TH1F*)f->Get("pt_pi0_gamma");
	pt_g_pi0_gamma=(TH1F*)f->Get("pt_g_pi0_gamma");	
	pt_pi0_gamma2=(TH1F*)f->Get("pt_pi0_gamma2");
	pt_eta_gamma=(TH1F*)f->Get("pt_eta_gamma");	
	pt_g_eta_gamma=(TH1F*)f->Get("pt_g_eta_gamma");		
	eta=(TH1F*)f->Get("eta");
	eta2=(TH1F*)f->Get("eta2");	      
	eta_g=(TH1F*)f->Get("eta_g");	
	eta_pi=(TH1F*)f->Get("eta_pi");	
	eta_pi2=(TH1F*)f->Get("eta_pi2");		
	eta_g_pi=(TH1F*)f->Get("eta_g_pi");
	eta_gamma=(TH1F*)f->Get("eta_gamma");	
	eta_g_gamma=(TH1F*)f->Get("eta_g_gamma");
	eta_gamma2=(TH1F*)f->Get("eta_gamma2");	
	eta_pi0=(TH1F*)f->Get("eta_pi0");	      
	eta_g_pi0=(TH1F*)f->Get("eta_g_pi0");
	eta_pi02=(TH1F*)f->Get("eta_pi02");
	eta_eta=(TH1F*)f->Get("eta_eta");	
	eta_g_eta=(TH1F*)f->Get("eta_g_eta");
	eta_eta2=(TH1F*)f->Get("eta_eta2");	
	eta_pi0_gamma=(TH1F*)f->Get("eta_pi0_gamma");	
	eta_g_pi0_gamma=(TH1F*)f->Get("eta_g_pi0_gamma");
	eta_pi0_gamma2=(TH1F*)f->Get("eta_pi0_gamma2");	
	eta_eta_gamma=(TH1F*)f->Get("eta_eta_gamma");	
	eta_g_eta_gamma=(TH1F*)f->Get("eta_g_eta_gamma");
	eta_eta_gamma2=(TH1F*)f->Get("eta_eta_gamma2");

	phi=(TH1F*)f->Get("phi");
	phi2=(TH1F*)f->Get("phi2");
	phi_g=(TH1F*)f->Get("phi_g");
	phi_pi=(TH1F*)f->Get("phi_pi");
	phi_pi2=(TH1F*)f->Get("phi_pi2");	
	phi_g_pi=(TH1F*)f->Get("phi_g_pi");
	phi_gamma=(TH1F*)f->Get("phi_gamma");
	phi_g_gamma=(TH1F*)f->Get("phi_g_gamma");	
	phi_gamma2=(TH1F*)f->Get("phi_gamma2");
	phi_pi0=(TH1F*)f->Get("phi_pi0");	
	phi_g_pi0=(TH1F*)f->Get("phi_g_pi0");
	phi_pi02=(TH1F*)f->Get("phi_pi02");
	phi_eta=(TH1F*)f->Get("phi_eta");	
	phi_g_eta=(TH1F*)f->Get("phi_g_eta");
	phi_eta2=(TH1F*)f->Get("phi_eta2");	
	phi_eta_gamma2=(TH1F*)f->Get("phi_eta_gamma2");	
	phi_pi0_gamma=(TH1F*)f->Get("phi_pi0_gamma");
	phi_g_pi0_gamma=(TH1F*)f->Get("phi_g_pi0_gamma");	
	phi_pi0_gamma2=(TH1F*)f->Get("phi_pi0_gamma2");
	phi_eta_gamma=(TH1F*)f->Get("phi_eta_gamma");	
	phi_g_eta_gamma=(TH1F*)f->Get("phi_g_eta_gamma");

	z=(TH1F*)f->Get("z");
	z2=(TH1F*)f->Get("z2");
	z_g=(TH1F*)f->Get("z_g");
	z_pi=(TH1F*)f->Get("z_pi");
	z_pi2=(TH1F*)f->Get("z_pi2");	
	z_g_pi=(TH1F*)f->Get("z_g_pi");
	z_gamma=(TH1F*)f->Get("z_gamma");
	z_g_gamma=(TH1F*)f->Get("z_g_gamma");	
	z_gamma2=(TH1F*)f->Get("z_gamma2");
	z_pi0=(TH1F*)f->Get("z_pi0");	
	z_g_pi0=(TH1F*)f->Get("z_g_pi0");
	z_pi02=(TH1F*)f->Get("z_pi02");
	z_eta=(TH1F*)f->Get("z_eta");	
	z_g_eta=(TH1F*)f->Get("z_g_eta");
	z_eta2=(TH1F*)f->Get("z_eta2");	
	z_eta_gamma2=(TH1F*)f->Get("z_eta_gamma2");	
	z_pi0_gamma=(TH1F*)f->Get("z_pi0_gamma");
	z_g_pi0_gamma=(TH1F*)f->Get("z_g_pi0_gamma");	
	z_pi0_gamma2=(TH1F*)f->Get("z_pi0_gamma2");
	z_eta_gamma=(TH1F*)f->Get("z_eta_gamma");	
	z_g_eta_gamma=(TH1F*)f->Get("z_g_eta_gamma");		

    }

	
 
 
    getEff3(pt,pt_g,8,1);
    getEff(eta,eta_g,8,1);
    getEff(pt_pi,pt_g_pi,24,1);
    getEff(eta_pi,eta_g_pi,24,1);
    getEff(pt_gamma,pt_g_gamma,21,2);
    getEff(eta_gamma,eta_g_gamma,21,2);
    getEff(pt_pi0,pt_g_pi0,22,4);
    getEff(eta_pi0,eta_g_pi0,22,4);
    getEff(pt_eta,pt_g_eta,23,80);
    getEff(eta_eta,eta_g_eta,23,80);
    getEff(pt_pi0_gamma,pt_g_pi0_gamma,26,66);
    getEff(eta_pi0_gamma,eta_g_pi0_gamma,26,66);
    getEff(pt_eta_gamma,pt_g_eta_gamma,25,14);
    getEff(eta_eta_gamma,eta_g_eta_gamma,25,14);

    
    getEff1(pt2,pt,8,1);
    getEff1(eta2,eta,8,1);
 
    getEff1(pt_pi2,pt_pi,24,1);
    getEff1(eta_pi2,eta_pi,24,1);
    getEff1(pt_gamma2,pt_gamma,21,2);
    getEff1(eta_gamma2,eta_gamma,21,2);
    getEff11(pt2_m1,pt_pi0,26,kMagenta);
    getEff11(pt2_m2,pt_pi0,22,kRed);
    getEff11(pt2_m3,pt_pi0,25,kCyan);
    getEff1(pt_pi02,pt_pi0,22,4);
    getEff1(eta_pi02,eta_pi0,22,4);
    getEff1(pt_eta2,pt_eta,23,80);
    getEff1(eta_eta2,eta_eta,23,80);
    getEff1(pt_pi0_gamma2,pt_pi0_gamma,26,66);
    getEff1(eta_pi0_gamma2,eta_pi0_gamma,26,66);
    getEff1(pt_eta_gamma2,pt_eta_gamma,25,14);
    getEff1(eta_eta_gamma2,eta_eta_gamma,25,14); 

    getEff(z,z_g,8,1);
    getEff(z_pi,z_g_pi,24,1);    
    getEff(z_gamma,z_g_gamma,21,2);    
    getEff(z_pi0,z_g_pi0,22,4);    
    getEff(z_eta,z_g_eta,23,80);    
    getEff(z_pi0_gamma,z_g_pi0_gamma,26,66);    
    getEff(z_eta_gamma,z_g_eta_gamma,25,14);
    
    getEff1(z2,z,8,1);    
    getEff1(z_pi2,z_pi,24,1);    
    getEff1(z_gamma2,z_gamma,21,2);    
    getEff1(z_pi02,z_pi0,22,4);    
    getEff1(z_eta2,z_eta,23,80);    
    getEff1(z_pi0_gamma2,z_pi0_gamma,26,66);
    getEff1(z_eta_gamma2,z_eta_gamma,25,14);
    
    getEff(phi,phi_g,8,1);
    getEff(phi_pi,phi_g_pi,24,1);    
    getEff(phi_gamma,phi_g_gamma,21,2);    
    getEff(phi_pi0,phi_g_pi0,22,4);    
    getEff(phi_eta,phi_g_eta,23,80);    
    getEff(phi_pi0_gamma,phi_g_pi0_gamma,26,66);    
    getEff(phi_eta_gamma,phi_g_eta_gamma,25,14);
    
    getEff1(phi2,phi,8,1);    
    getEff1(phi_pi2,phi_pi,24,1);    
    getEff1(phi_gamma2,phi_gamma,21,2);    
    getEff1(phi_pi02,phi_pi0,22,4);    
    getEff1(phi_eta2,phi_eta,23,80);    
    getEff1(phi_pi0_gamma2,phi_pi0_gamma,26,66);
    getEff1(phi_eta_gamma2,phi_eta_gamma,25,14);    
   
    TLegend *leg1 = new TLegend(0.65,0.7,0.85,0.9);
    leg1->AddEntry(pt_g_pi,"#pi","pl");
    leg1->AddEntry(pt_g,"Single e","pl");
    leg1->AddEntry(pt_g_pi0,"#pi^{0}#rightarrow e","pl");
    leg1->AddEntry(pt_g_eta,"#eta#rightarrow e","pl");
    leg1->AddEntry(pt_g_pi0_gamma,"#pi^{0}#rightarrow #gamma#rightarrow e","pl");
    leg1->AddEntry(pt_g_eta_gamma,"#eta#rightarrow #gamma#rightarrow e","pl");
    leg1->AddEntry(pt_g_gamma,"#gamma#rightarrow e","pl");    

    pt_g->GetYaxis()->SetTitle("#varepsilon_{TPC}");
    pt_g->GetYaxis()->SetRangeUser(0,1);
    pt_g->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    eta_g->GetYaxis()->SetTitle("#varepsilon_{TPC}");
    eta_g->GetYaxis()->SetRangeUser(0,1);
    eta_g->GetXaxis()->SetTitle("#eta");
    phi_g->GetYaxis()->SetTitle("#varepsilon_{TPC}");
    phi_g->GetYaxis()->SetRangeUser(0,1);
    phi_g->GetXaxis()->SetTitle("#phi"); 
    z_g->GetYaxis()->SetTitle("#varepsilon_{TPC}");
    z_g->GetYaxis()->SetRangeUser(0,1);
    z_g->GetXaxis()->SetTitle("Vertex #it{z} [cm]"); 
    pt->GetYaxis()->SetTitle("#varepsilon_{HFT}");
    pt->GetYaxis()->SetRangeUser(0,1);
    pt->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    eta->GetYaxis()->SetTitle("#varepsilon_{HTF}");
    eta->GetYaxis()->SetRangeUser(0,1);
    eta->GetXaxis()->SetTitle("#eta");
    phi->GetYaxis()->SetTitle("#varepsilon_{HTF}");
    phi->GetYaxis()->SetRangeUser(0,1);
    phi->GetXaxis()->SetTitle("#phi");   
    z->GetYaxis()->SetTitle("#varepsilon_{HFT}");
    z->GetYaxis()->SetRangeUser(0,1);
    z->GetXaxis()->SetTitle("Vertex #it{z} [cm]"); 

    TLegend *leg = new TLegend(0.2,0.2,0.4,0.4);
    leg->AddEntry(pt,"TPC+HFT","PE");
    TCanvas *c1 = new TCanvas("c1","c1");
    pt_g->Draw("PE");
    pt_g_pi->Draw("PE same");
    pt_g_gamma->Draw("PE same");
    pt_g_pi0_gamma->Draw("PE same");
    pt_g_eta_gamma->Draw("PE same");
    pt_g_pi0->Draw("PE same");
    pt_g_eta->Draw("PE same");
    leg1->Draw("same");
    TCanvas *c2 = new TCanvas("c2","c2");
    eta_g->Draw("PE");    
    eta_g_pi->Draw("PE same");
    eta_g_gamma->Draw("PE same");
    eta_g_pi0_gamma->Draw("PE same");
    eta_g_eta_gamma->Draw("PE same");
    eta_g_pi0->Draw("PE same");
    eta_g_eta->Draw("PE same"); 
    leg1->Draw("same");
    TCanvas *c3 = new TCanvas("c3","c3");
    phi_g->Draw("PE");
    phi_g_pi->Draw("PE same");
    phi_g_gamma->Draw("PE same");
    phi_g_pi0_gamma->Draw("PE same");
    phi_g_eta_gamma->Draw("PE same");
    phi_g_pi0->Draw("PE same");
    phi_g_eta->Draw("PE same");
    leg1->Draw("same");
    TCanvas *c4 = new TCanvas("c4","c4");
    z_g->Draw("PE");    
    z_g_pi->Draw("PE same");
    z_g_gamma->Draw("PE same");
    z_g_pi0_gamma->Draw("PE same");
    z_g_eta_gamma->Draw("PE same");
    z_g_pi0->Draw("PE same");
    z_g_eta->Draw("PE same"); 
    leg1->Draw("same");



    TCanvas *c111 = new TCanvas("c111","c111");
    pt_pi0->Draw("PE");
    pt2_m1->Draw("same PE");
    pt2_m2->Draw("same PE");
    pt2_m3->Draw("same PE");
    TCanvas *c11 = new TCanvas("c11","c11");
    pt->Draw("PE");
    pt_pi->Draw("PE same");
    pt_gamma->Draw("PE same");
    pt_pi0_gamma->Draw("PE same");
    pt_eta_gamma->Draw("PE same");
    pt_pi0->Draw("PE same");
    pt_eta->Draw("PE same");
    leg1->Draw("same");
    TCanvas *c22 = new TCanvas("c22","c22");
    eta->Draw("PE");    
    eta_pi->Draw("PE same");
    eta_gamma->Draw("PE same");
    eta_pi0_gamma->Draw("PE same");
    eta_eta_gamma->Draw("PE same");
    eta_pi0->Draw("PE same");
    eta_eta->Draw("PE same"); 
    leg1->Draw("same");
   TCanvas *c33 = new TCanvas("c33","c33");
    phi->Draw("PE");
    phi_pi->Draw("PE same");
    phi_gamma->Draw("PE same");
    phi_pi0_gamma->Draw("PE same");
    phi_eta_gamma->Draw("PE same");
    phi_pi0->Draw("PE same");
    phi_eta->Draw("PE same");
    leg1->Draw("same");
    TCanvas *c44 = new TCanvas("c44","c44");
    z->Draw("PE");    
    z_pi->Draw("PE same");
    z_gamma->Draw("PE same");
    z_pi0_gamma->Draw("PE same");
    z_eta_gamma->Draw("PE same");
    z_pi0->Draw("PE same");
    z_eta->Draw("PE same"); 
    leg1->Draw("same");
   
    pt_pi_1 = (TH1F*)pt_pi_r->ProjectionX("pt_pi_1",1,2);
    pt_pi_2 = (TH1F*)pt_pi_r->ProjectionX("pt_pi_2",2,3);
    pt_pi_3 = (TH1F*)pt_pi_r->ProjectionX("pt_pi_3",3,4);
    pt_pi_4 = (TH1F*)pt_pi_r->ProjectionX("pt_pi_4",4,5);
    pt_pi_5 = (TH1F*)pt_pi_r->ProjectionX("pt_pi_5",5,6);
    pt_pi_6 = (TH1F*)pt_pi_r->ProjectionX("pt_pi_6",6,7);
    pt_pi_7 = (TH1F*)pt_pi_r->ProjectionX("pt_pi_7",7,8);
    pt_pi_8 = (TH1F*)pt_pi_r->ProjectionX("pt_pi_8",8,9);
    pt_pi_9 = (TH1F*)pt_pi_r->ProjectionX("pt_pi_9",9,10);
    pt_pi2_1 = (TH1F*)pt_pi2_r->ProjectionX("pt_pi2_1",1,2);
    pt_pi2_2 = (TH1F*)pt_pi2_r->ProjectionX("pt_pi2_2",2,3);
    pt_pi2_3 = (TH1F*)pt_pi2_r->ProjectionX("pt_pi2_3",3,4);
    pt_pi2_4 = (TH1F*)pt_pi2_r->ProjectionX("pt_pi2_4",4,5);
    pt_pi2_5 = (TH1F*)pt_pi2_r->ProjectionX("pt_pi2_5",5,6);
    pt_pi2_6 = (TH1F*)pt_pi2_r->ProjectionX("pt_pi2_6",6,7);
    pt_pi2_7 = (TH1F*)pt_pi2_r->ProjectionX("pt_pi2_7",7,8);
    pt_pi2_8 = (TH1F*)pt_pi2_r->ProjectionX("pt_pi2_8",8,9);
    pt_pi2_9 = (TH1F*)pt_pi2_r->ProjectionX("pt_pi2_9",9,10);
    pt_e_1 = (TH1F*)pt_e_r->ProjectionX("pt_e_1",1,2);
    pt_e_2 = (TH1F*)pt_e_r->ProjectionX("pt_e_2",2,3);
    pt_e_3 = (TH1F*)pt_e_r->ProjectionX("pt_e_3",3,4);
    pt_e_4 = (TH1F*)pt_e_r->ProjectionX("pt_e_4",4,5);
    pt_e_5 = (TH1F*)pt_e_r->ProjectionX("pt_e_5",5,6);
    pt_e_6 = (TH1F*)pt_e_r->ProjectionX("pt_e_6",6,7);
    pt_e_7 = (TH1F*)pt_e_r->ProjectionX("pt_e_7",7,8);
    pt_e_8 = (TH1F*)pt_e_r->ProjectionX("pt_e_8",8,9);
    pt_e_9 = (TH1F*)pt_e_r->ProjectionX("pt_e_9",9,10);
    pt_e2_1 = (TH1F*)pt_e2_r->ProjectionX("pt_e2_1",1,2);
    pt_e2_2 = (TH1F*)pt_e2_r->ProjectionX("pt_e2_2",2,3);
    pt_e2_3 = (TH1F*)pt_e2_r->ProjectionX("pt_e2_3",3,4);
    pt_e2_4 = (TH1F*)pt_e2_r->ProjectionX("pt_e2_4",4,5);
    pt_e2_5 = (TH1F*)pt_e2_r->ProjectionX("pt_e2_5",5,6);
    pt_e2_6 = (TH1F*)pt_e2_r->ProjectionX("pt_e2_6",6,7);
    pt_e2_7 = (TH1F*)pt_e2_r->ProjectionX("pt_e2_7",7,8);
    pt_e2_8 = (TH1F*)pt_e2_r->ProjectionX("pt_e2_8",8,9);
    pt_e2_9 = (TH1F*)pt_e2_r->ProjectionX("pt_e2_9",9,10);   
 
    eta_pi_1 = (TH1F*)eta_pi_r->ProjectionX("eta_pi_1",1,2);
    eta_pi_2 = (TH1F*)eta_pi_r->ProjectionX("eta_pi_2",2,3);
    eta_pi_3 = (TH1F*)eta_pi_r->ProjectionX("eta_pi_3",3,4);
    eta_pi_4 = (TH1F*)eta_pi_r->ProjectionX("eta_pi_4",4,5);
    eta_pi_5 = (TH1F*)eta_pi_r->ProjectionX("eta_pi_5",5,6);
    eta_pi_6 = (TH1F*)eta_pi_r->ProjectionX("eta_pi_6",6,7);
    eta_pi_7 = (TH1F*)eta_pi_r->ProjectionX("eta_pi_7",7,8);
    eta_pi_8 = (TH1F*)eta_pi_r->ProjectionX("eta_pi_8",8,9);
    eta_pi_9 = (TH1F*)eta_pi_r->ProjectionX("eta_pi_9",9,10);
    eta_pi2_1 = (TH1F*)eta_pi2_r->ProjectionX("eta_pi2_1",1,2);
    eta_pi2_2 = (TH1F*)eta_pi2_r->ProjectionX("eta_pi2_2",2,3);
    eta_pi2_3 = (TH1F*)eta_pi2_r->ProjectionX("eta_pi2_3",3,4);
    eta_pi2_4 = (TH1F*)eta_pi2_r->ProjectionX("eta_pi2_4",4,5);
    eta_pi2_5 = (TH1F*)eta_pi2_r->ProjectionX("eta_pi2_5",5,6);
    eta_pi2_6 = (TH1F*)eta_pi2_r->ProjectionX("eta_pi2_6",6,7);
    eta_pi2_7 = (TH1F*)eta_pi2_r->ProjectionX("eta_pi2_7",7,8);
    eta_pi2_8 = (TH1F*)eta_pi2_r->ProjectionX("eta_pi2_8",8,9);
    eta_pi2_9 = (TH1F*)eta_pi2_r->ProjectionX("eta_pi2_9",9,10);
    eta_e_1 = (TH1F*)eta_e_r->ProjectionX("eta_e_1",1,2);
    eta_e_2 = (TH1F*)eta_e_r->ProjectionX("eta_e_2",2,3);
    eta_e_3 = (TH1F*)eta_e_r->ProjectionX("eta_e_3",3,4);
    eta_e_4 = (TH1F*)eta_e_r->ProjectionX("eta_e_4",4,5);
    eta_e_5 = (TH1F*)eta_e_r->ProjectionX("eta_e_5",5,6);
    eta_e_6 = (TH1F*)eta_e_r->ProjectionX("eta_e_6",6,7);
    eta_e_7 = (TH1F*)eta_e_r->ProjectionX("eta_e_7",7,8);
    eta_e_8 = (TH1F*)eta_e_r->ProjectionX("eta_e_8",8,9);
    eta_e_9 = (TH1F*)eta_e_r->ProjectionX("eta_e_9",9,10);
    eta_e2_1 = (TH1F*)eta_e2_r->ProjectionX("eta_e2_1",1,2);
    eta_e2_2 = (TH1F*)eta_e2_r->ProjectionX("eta_e2_2",2,3);
    eta_e2_3 = (TH1F*)eta_e2_r->ProjectionX("eta_e2_3",3,4);
    eta_e2_4 = (TH1F*)eta_e2_r->ProjectionX("eta_e2_4",4,5);
    eta_e2_5 = (TH1F*)eta_e2_r->ProjectionX("eta_e2_5",5,6);
    eta_e2_6 = (TH1F*)eta_e2_r->ProjectionX("eta_e2_6",6,7);
    eta_e2_7 = (TH1F*)eta_e2_r->ProjectionX("eta_e2_7",7,8);
    eta_e2_8 = (TH1F*)eta_e2_r->ProjectionX("eta_e2_8",8,9);
    eta_e2_9 = (TH1F*)eta_e2_r->ProjectionX("eta_e2_9",9,10);   

    phi_pi_1 = (TH1F*)phi_pi_r->ProjectionX("phi_pi_1",1,2);
    phi_pi_2 = (TH1F*)phi_pi_r->ProjectionX("phi_pi_2",2,3);
    phi_pi_3 = (TH1F*)phi_pi_r->ProjectionX("phi_pi_3",3,4);
    phi_pi_4 = (TH1F*)phi_pi_r->ProjectionX("phi_pi_4",4,5);
    phi_pi_5 = (TH1F*)phi_pi_r->ProjectionX("phi_pi_5",5,6);
    phi_pi_6 = (TH1F*)phi_pi_r->ProjectionX("phi_pi_6",6,7);
    phi_pi_7 = (TH1F*)phi_pi_r->ProjectionX("phi_pi_7",7,8);
    phi_pi_8 = (TH1F*)phi_pi_r->ProjectionX("phi_pi_8",8,9);
    phi_pi_9 = (TH1F*)phi_pi_r->ProjectionX("phi_pi_9",9,10);
    phi_pi2_1 = (TH1F*)phi_pi2_r->ProjectionX("phi_pi2_1",1,2);
    phi_pi2_2 = (TH1F*)phi_pi2_r->ProjectionX("phi_pi2_2",2,3);
    phi_pi2_3 = (TH1F*)phi_pi2_r->ProjectionX("phi_pi2_3",3,4);
    phi_pi2_4 = (TH1F*)phi_pi2_r->ProjectionX("phi_pi2_4",4,5);
    phi_pi2_5 = (TH1F*)phi_pi2_r->ProjectionX("phi_pi2_5",5,6);
    phi_pi2_6 = (TH1F*)phi_pi2_r->ProjectionX("phi_pi2_6",6,7);
    phi_pi2_7 = (TH1F*)phi_pi2_r->ProjectionX("phi_pi2_7",7,8);
    phi_pi2_8 = (TH1F*)phi_pi2_r->ProjectionX("phi_pi2_8",8,9);
    phi_pi2_9 = (TH1F*)phi_pi2_r->ProjectionX("phi_pi2_9",9,10);
    phi_e_1 = (TH1F*)phi_e_r->ProjectionX("phi_e_1",1,2);
    phi_e_2 = (TH1F*)phi_e_r->ProjectionX("phi_e_2",2,3);
    phi_e_3 = (TH1F*)phi_e_r->ProjectionX("phi_e_3",3,4);
    phi_e_4 = (TH1F*)phi_e_r->ProjectionX("phi_e_4",4,5);
    phi_e_5 = (TH1F*)phi_e_r->ProjectionX("phi_e_5",5,6);
    phi_e_6 = (TH1F*)phi_e_r->ProjectionX("phi_e_6",6,7);
    phi_e_7 = (TH1F*)phi_e_r->ProjectionX("phi_e_7",7,8);
    phi_e_8 = (TH1F*)phi_e_r->ProjectionX("phi_e_8",8,9);
    phi_e_9 = (TH1F*)phi_e_r->ProjectionX("phi_e_9",9,10);
    phi_e2_1 = (TH1F*)phi_e2_r->ProjectionX("phi_e2_1",1,2);
    phi_e2_2 = (TH1F*)phi_e2_r->ProjectionX("phi_e2_2",2,3);
    phi_e2_3 = (TH1F*)phi_e2_r->ProjectionX("phi_e2_3",3,4);
    phi_e2_4 = (TH1F*)phi_e2_r->ProjectionX("phi_e2_4",4,5);
    phi_e2_5 = (TH1F*)phi_e2_r->ProjectionX("phi_e2_5",5,6);
    phi_e2_6 = (TH1F*)phi_e2_r->ProjectionX("phi_e2_6",6,7);
    phi_e2_7 = (TH1F*)phi_e2_r->ProjectionX("phi_e2_7",7,8);
    phi_e2_8 = (TH1F*)phi_e2_r->ProjectionX("phi_e2_8",8,9);
    phi_e2_9 = (TH1F*)phi_e2_r->ProjectionX("phi_e2_9",9,10);   

    z_pi_1 = (TH1F*)z_pi_r->ProjectionX("z_pi_1",1,2);
    z_pi_2 = (TH1F*)z_pi_r->ProjectionX("z_pi_2",2,3);
    z_pi_3 = (TH1F*)z_pi_r->ProjectionX("z_pi_3",3,4);
    z_pi_4 = (TH1F*)z_pi_r->ProjectionX("z_pi_4",4,5);
    z_pi_5 = (TH1F*)z_pi_r->ProjectionX("z_pi_5",5,6);
    z_pi_6 = (TH1F*)z_pi_r->ProjectionX("z_pi_6",6,7);
    z_pi_7 = (TH1F*)z_pi_r->ProjectionX("z_pi_7",7,8);
    z_pi_8 = (TH1F*)z_pi_r->ProjectionX("z_pi_8",8,9);
    z_pi_9 = (TH1F*)z_pi_r->ProjectionX("z_pi_9",9,10);
    z_pi2_1 = (TH1F*)z_pi2_r->ProjectionX("z_pi2_1",1,2);
    z_pi2_2 = (TH1F*)z_pi2_r->ProjectionX("z_pi2_2",2,3);
    z_pi2_3 = (TH1F*)z_pi2_r->ProjectionX("z_pi2_3",3,4);
    z_pi2_4 = (TH1F*)z_pi2_r->ProjectionX("z_pi2_4",4,5);
    z_pi2_5 = (TH1F*)z_pi2_r->ProjectionX("z_pi2_5",5,6);
    z_pi2_6 = (TH1F*)z_pi2_r->ProjectionX("z_pi2_6",6,7);
    z_pi2_7 = (TH1F*)z_pi2_r->ProjectionX("z_pi2_7",7,8);
    z_pi2_8 = (TH1F*)z_pi2_r->ProjectionX("z_pi2_8",8,9);
    z_pi2_9 = (TH1F*)z_pi2_r->ProjectionX("z_pi2_9",9,10);
    z_e_1 = (TH1F*)z_e_r->ProjectionX("z_e_1",1,2);
    z_e_2 = (TH1F*)z_e_r->ProjectionX("z_e_2",2,3);
    z_e_3 = (TH1F*)z_e_r->ProjectionX("z_e_3",3,4);
    z_e_4 = (TH1F*)z_e_r->ProjectionX("z_e_4",4,5);
    z_e_5 = (TH1F*)z_e_r->ProjectionX("z_e_5",5,6);
    z_e_6 = (TH1F*)z_e_r->ProjectionX("z_e_6",6,7);
    z_e_7 = (TH1F*)z_e_r->ProjectionX("z_e_7",7,8);
    z_e_8 = (TH1F*)z_e_r->ProjectionX("z_e_8",8,9);
    z_e_9 = (TH1F*)z_e_r->ProjectionX("z_e_9",9,10);
    z_e2_1 = (TH1F*)z_e2_r->ProjectionX("z_e2_1",1,2);
    z_e2_2 = (TH1F*)z_e2_r->ProjectionX("z_e2_2",2,3);
    z_e2_3 = (TH1F*)z_e2_r->ProjectionX("z_e2_3",3,4);
    z_e2_4 = (TH1F*)z_e2_r->ProjectionX("z_e2_4",4,5);
    z_e2_5 = (TH1F*)z_e2_r->ProjectionX("z_e2_5",5,6);
    z_e2_6 = (TH1F*)z_e2_r->ProjectionX("z_e2_6",6,7);
    z_e2_7 = (TH1F*)z_e2_r->ProjectionX("z_e2_7",7,8);
    z_e2_8 = (TH1F*)z_e2_r->ProjectionX("z_e2_8",8,9);
    z_e2_9 = (TH1F*)z_e2_r->ProjectionX("z_e2_9",9,10);   



    getEff2(5,pt_n1,pt_d1,8,1,"#it{p}_{T} [GeV]");   
    getEff2(5,pt_n2,pt_d2,8,1,"#it{p}_{T} [GeV]");  
    getEff2(5,pt_n3,pt_d3,8,1,"#it{p}_{T} [GeV]");  
    getEff2(5,pt_n4,pt_d4,8,1,"#it{p}_{T} [GeV]");  
    getEff2(5,pt_n5,pt_d5,8,1,"#it{p}_{T} [GeV]");  
    getEff2(5,pt_n6,pt_d6,8,1,"#it{p}_{T} [GeV]");  
    getEff2(5,pt_n7,pt_d7,8,1,"#it{p}_{T} [GeV]");  
    getEff2(5,pt_n8,pt_d8,8,1,"#it{p}_{T} [GeV]");   
    getEff2(0,pt_pi2_1,pt_pi_1,25,4,"#it{p}_{T} [GeV]");  
    getEff2(0,pt_pi2_2,pt_pi_2,25,4,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_pi2_3,pt_pi_3,25,4,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_pi2_4,pt_pi_4,25,4,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_pi2_5,pt_pi_5,25,4,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_pi2_6,pt_pi_6,25,4,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_pi2_7,pt_pi_7,25,4,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_pi2_8,pt_pi_8,25,4,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_e2_1,pt_e_1,22,2,"#it{p}_{T} [GeV]");  
    getEff2(0,pt_e2_2,pt_e_2,22,2,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_e2_3,pt_e_3,22,2,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_e2_4,pt_e_4,22,2,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_e2_5,pt_e_5,22,2,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_e2_6,pt_e_6,22,2,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_e2_7,pt_e_7,22,2,"#it{p}_{T} [GeV]"); 
    getEff2(0,pt_e2_8,pt_e_8,22,2,"#it{p}_{T} [GeV]"); 

    getEff2(5,eta_n1,eta_d1,8,1,"#eta");   
    getEff2(5,eta_n2,eta_d2,8,1,"#eta");  
    getEff2(5,eta_n3,eta_d3,8,1,"#eta");  
    getEff2(5,eta_n4,eta_d4,8,1,"#eta");  
    getEff2(5,eta_n5,eta_d5,8,1,"#eta");  
    getEff2(5,eta_n6,eta_d6,8,1,"#eta");  
    getEff2(5,eta_n7,eta_d7,8,1,"#eta");  
    getEff2(5,eta_n8,eta_d8,8,1,"#eta");    
    getEff2(0,eta_pi2_1,eta_pi_1,25,4,"#eta");  
    getEff2(0,eta_pi2_2,eta_pi_2,25,4,"#eta"); 
    getEff2(0,eta_pi2_3,eta_pi_3,25,4,"#eta"); 
    getEff2(0,eta_pi2_4,eta_pi_4,25,4,"#eta"); 
    getEff2(0,eta_pi2_5,eta_pi_5,25,4,"#eta"); 
    getEff2(0,eta_pi2_6,eta_pi_6,25,4,"#eta"); 
    getEff2(0,eta_pi2_7,eta_pi_7,25,4,"#eta"); 
    getEff2(0,eta_pi2_8,eta_pi_8,25,4,"#eta"); 
    getEff2(0,eta_e2_1,eta_e_1,22,2,"#eta");  
    getEff2(0,eta_e2_2,eta_e_2,22,2,"#eta"); 
    getEff2(0,eta_e2_3,eta_e_3,22,2,"#eta"); 
    getEff2(0,eta_e2_4,eta_e_4,22,2,"#eta"); 
    getEff2(0,eta_e2_5,eta_e_5,22,2,"#eta"); 
    getEff2(0,eta_e2_6,eta_e_6,22,2,"#eta"); 
    getEff2(0,eta_e2_7,eta_e_7,22,2,"#eta"); 
    getEff2(0,eta_e2_8,eta_e_8,22,2,"#eta"); 


    getEff2(20,phi_n1,phi_d1,8,1,"#phi [rad]");   
    getEff2(20,phi_n2,phi_d2,8,1,"#phi [rad]");  
    getEff2(20,phi_n3,phi_d3,8,1,"#phi [rad]");  
    getEff2(20,phi_n4,phi_d4,8,1,"#phi [rad]");  
    getEff2(20,phi_n5,phi_d5,8,1,"#phi [rad]");  
    getEff2(20,phi_n6,phi_d6,8,1,"#phi [rad]");  
    getEff2(20,phi_n7,phi_d7,8,1,"#phi [rad]");  
    getEff2(20,phi_n8,phi_d8,8,1,"#phi [rad]");    
    getEff2(20,phi_n,phi_d,8,1,"#phi");  
    getEff2(2,phi_pi2_1,phi_pi_1,25,4,"#phi");  
    getEff2(2,phi_pi2_2,phi_pi_2,25,4,"#phi"); 
    getEff2(2,phi_pi2_3,phi_pi_3,25,4,"#phi"); 
    getEff2(2,phi_pi2_4,phi_pi_4,25,4,"#phi"); 
    getEff2(2,phi_pi2_5,phi_pi_5,25,4,"#phi"); 
    getEff2(2,phi_pi2_6,phi_pi_6,25,4,"#phi"); 
    getEff2(2,phi_pi2_7,phi_pi_7,25,4,"#phi"); 
    getEff2(2,phi_pi2_8,phi_pi_8,25,4,"#phi"); 
    getEff2(2,phi_e2_1,phi_e_1,22,2,"#phi");  
    getEff2(2,phi_e2_2,phi_e_2,22,2,"#phi"); 
    getEff2(2,phi_e2_3,phi_e_3,22,2,"#phi"); 
    getEff2(2,phi_e2_4,phi_e_4,22,2,"#phi"); 
    getEff2(2,phi_e2_5,phi_e_5,22,2,"#phi"); 
    getEff2(2,phi_e2_6,phi_e_6,22,2,"#phi"); 
    getEff2(2,phi_e2_7,phi_e_7,22,2,"#phi"); 
    getEff2(2,phi_e2_8,phi_e_8,22,2,"#phi"); 

    getEff2(10,z_n1,z_d1,8,1,"Vetex #it{z} [cm]");   
    getEff2(10,z_n2,z_d2,8,1,"Vetex #it{z} [cm]");  
    getEff2(10,z_n3,z_d3,8,1,"Vetex #it{z} [cm]");  
    getEff2(10,z_n4,z_d4,8,1,"Vetex #it{z} [cm]");  
    getEff2(10,z_n5,z_d5,8,1,"Vetex #it{z} [cm]");  
    getEff2(10,z_n6,z_d6,8,1,"Vetex #it{z} [cm]");  
    getEff2(10,z_n7,z_d7,8,1,"Vetex #it{z} [cm]");  
    getEff2(10,z_n8,z_d8,8,1,"Vetex #it{z} [cm]");    
    getEff2(10,z_n,z_d,8,1,"Vetex #it{z} [cm]");  
    getEff2(0,z_pi2_1,z_pi_1,25,4,"Vetex #it{z} [cm]");  
    getEff2(0,z_pi2_2,z_pi_2,25,4,"Vetex #it{z} [cm]"); 
    getEff2(0,z_pi2_3,z_pi_3,25,4,"Vetex #it{z} [cm]"); 
    getEff2(0,z_pi2_4,z_pi_4,25,4,"Vetex #it{z} [cm]"); 
    getEff2(0,z_pi2_5,z_pi_5,25,4,"Vetex #it{z} [cm]"); 
    getEff2(0,z_pi2_6,z_pi_6,25,4,"Vetex #it{z} [cm]"); 
    getEff2(0,z_pi2_7,z_pi_7,25,4,"Vetex #it{z} [cm]"); 
    getEff2(0,z_pi2_8,z_pi_8,25,4,"Vetex #it{z} [cm]"); 
    getEff2(0,z_e2_1,z_e_1,22,2,"Vetex #it{z} [cm]");  
    getEff2(0,z_e2_2,z_e_2,22,2,"Vetex #it{z} [cm]"); 
    getEff2(0,z_e2_3,z_e_3,22,2,"Vetex #it{z} [cm]"); 
    getEff2(0,z_e2_4,z_e_4,22,2,"Vetex #it{z} [cm]"); 
    getEff2(0,z_e2_5,z_e_5,22,2,"Vetex #it{z} [cm]"); 
    getEff2(0,z_e2_6,z_e_6,22,2,"Vetex #it{z} [cm]"); 
    getEff2(0,z_e2_7,z_e_7,22,2,"Vetex #it{z} [cm]"); 
    getEff2(0,z_e2_8,z_e_8,22,2,"Vetex #it{z} [cm]"); 

    TLegend *leg2 = new TLegend(0.2,0.7,0.5,0.9);
    leg2->AddEntry(pt_d1,"Data |n#sigma_{#pi}|<2","PE");
    leg2->AddEntry(pt_pi_1,"Emb. Pion","PE");
    leg2->AddEntry(pt_e_1,"Emb. Electron","PE");

    TLatex lat;

    TCanvas *c6 = new TCanvas("c6","c6",1600,800);
    c6->Divide(4,2);
    c6->cd(1);
    pt_d1->Draw();
    pt_pi_1->Draw("same PE");
    pt_e_1->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(1,0.2,"70-80%");
    c6->cd(2);
    pt_d2->Draw();
    pt_pi_2->Draw("same PE");
    pt_e_2->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(1,0.2,"60-70%");
    c6->cd(3);
    pt_d3->Draw();
    pt_pi_3->Draw("same PE");
    pt_e_3->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(1,0.2,"50-60%");
    c6->cd(4);
    pt_d4->Draw();
    pt_pi_4->Draw("same PE");
    pt_e_4->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(1,0.2,"40-50%");
    c6->cd(5);
    pt_d5->Draw();
    pt_pi_5->Draw("same PE");
    pt_e_5->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(1,0.2,"30-40%");
    c6->cd(6);
    pt_d6->Draw();
    pt_pi_6->Draw("same PE");
    pt_e_6->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(1,0.2,"20-30%");
    c6->cd(7);
    pt_d7->Draw();
    pt_pi_7->Draw("same PE");
    pt_e_7->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(1,0.2,"10-20%");
    c6->cd(8);
    pt_d8->Draw();
    pt_pi_8->Draw("same PE");
    pt_e_8->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(1,0.2,"5-10%");

    TCanvas *c7 = new TCanvas("c7","c7",1600,800);
    c7->Divide(4,2);
    c7->cd(1);
    eta_d1->Draw();
    eta_pi_1->Draw("same PE");
    eta_e_1->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"70-80%");
    c7->cd(2);
    eta_d2->Draw();
    eta_pi_2->Draw("same PE");
    eta_e_2->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"60-70%");
    c7->cd(3);
    eta_d3->Draw();
    eta_pi_3->Draw("same PE");
    eta_e_3->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"50-60%");
    c7->cd(4);
    eta_d4->Draw();
    eta_pi_4->Draw("same PE");
    eta_e_4->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"40-50%");
    c7->cd(5);
    eta_d5->Draw();
    eta_pi_5->Draw("same PE");
    eta_e_5->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"30-40%");
    c7->cd(6);
    eta_d6->Draw();
    eta_pi_6->Draw("same PE");
    eta_e_6->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"20-30%");
    c7->cd(7);
    eta_d7->Draw();
    eta_pi_7->Draw("same PE");
    eta_e_7->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"10-20%");
    c7->cd(8);
    eta_d8->Draw();
    eta_pi_8->Draw("same PE");
    eta_e_8->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"5-10%");

    TCanvas *c8 = new TCanvas("c8","c8",1600,800);
    c8->Divide(4,2);
    c8->cd(1);
    phi_d1->Draw();
    phi_pi_1->Draw("same PE");
    phi_e_1->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"70-80%");
    c8->cd(2);
    phi_d2->Draw();
    phi_pi_2->Draw("same PE");
    phi_e_2->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"60-70%");
    c8->cd(3);
    phi_d3->Draw();
    phi_pi_3->Draw("same PE");
    phi_e_3->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"50-60%");
    c8->cd(4);
    phi_d4->Draw();
    phi_pi_4->Draw("same PE");
    phi_e_4->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"40-50%");
    c8->cd(5);
    phi_d5->Draw();
    phi_pi_5->Draw("same PE");
    phi_e_5->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"30-40%");
    c8->cd(6);
    phi_d6->Draw();
    phi_pi_6->Draw("same PE");
    phi_e_6->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"20-30%");
    c8->cd(7);
    phi_d7->Draw();
    phi_pi_7->Draw("same PE");
    phi_e_7->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"10-20%");
    c8->cd(8);
    phi_d8->Draw();
    phi_pi_8->Draw("same PE");
    phi_e_8->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-0.8,0.2,"5-10%");

    TCanvas *c9 = new TCanvas("c9","c9",1600,800);
    c9->Divide(4,2);
    c9->cd(1);
    z_d1->Draw();
    z_pi_1->Draw("same PE");
    z_e_1->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-5,0.2,"70-80%");
    c9->cd(2);
    z_d2->Draw();
    z_pi_2->Draw("same PE");
    z_e_2->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-5,0.2,"60-70%");
    c9->cd(3);
    z_d3->Draw();
    z_pi_3->Draw("same PE");
    z_e_3->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-5,0.2,"50-60%");
    c9->cd(4);
    z_d4->Draw();
    z_pi_4->Draw("same PE");
    z_e_4->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-5,0.2,"40-50%");
    c9->cd(5);
    z_d5->Draw();
    z_pi_5->Draw("same PE");
    z_e_5->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-5,0.2,"30-40%");
    c9->cd(6);
    z_d6->Draw();
    z_pi_6->Draw("same PE");
    z_e_6->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-5,0.2,"20-30%");
    c9->cd(7);
    z_d7->Draw();
    z_pi_7->Draw("same PE");
    z_e_7->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-5,0.2,"10-20%");
    c9->cd(8);
    z_d8->Draw();
    z_pi_8->Draw("same PE");
    z_e_8->Draw("same PE");leg2->Draw("same");
    lat.DrawLatex(-5,0.2,"5-10%");

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
