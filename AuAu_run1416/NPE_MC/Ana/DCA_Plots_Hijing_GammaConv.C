void DCA_Plots_Hijing_GammaConv(int save = 1 , int weight_data=1){ 
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");    
    TGaxis::SetMaxDigits(3);  
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
    TF1 *fpi = new TF1("fpi","[0]",0,10);
    TF1 *feta = new TF1("feta","[0]",0,10);
    TF1 *fgamma = new TF1("fgamma","[0]",0,10);
    TFile *fi = new TFile("root/WeightsHijing.root");
    pi0_new_weights = (TH1F*) fi->Get("pi0_new_weights");
    eta_new_weights = (TH1F*) fi->Get("eta_new_weights");
    gamma_new_weights = (TH1F*) fi->Get("gamma_new_weights");
    pi0_new_weights->SetMarkerColor(kBlue);
    eta_new_weights->SetMarkerColor(kGreen-2);
    gamma_new_weights->SetMarkerColor(kRed);
    setErr(pi0_new_weights);
    setErr(eta_new_weights);
    setErr(gamma_new_weights);
    //gamma_weights->Fit(fgamma,"","",0,10);   
    //double _scale_ = fgamma->GetParameter(0);
    //pi0_weights->Scale(1./_scale_);
    //eta_weights->Scale(1./_scale_);
    //gamma_weights->Scale(1./_scale_);
    //pi0_weights->Fit(fpi,"","",0,10);
    //eta_weights->Fit(feta,"","",0,10);   
    //gamma_weights->Fit(fgamma,"","",0,10);   
    TCanvas*cfit = new TCanvas ("cfit","weights");
    pi0_new_weights->Draw("PE");
    eta_new_weights->Draw("same PE");    
    gamma_new_weights->Draw("same PE");

    pi0_weights = (TH1F*) fi->Get("pi0_weights");
    gamma_weights = (TH1F*) fi->Get("gamma_weights");
    eta_weights = (TH1F*) fi->Get("eta_weights");

    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    double corr[numPtBins]={1e1,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8};
    TH1F *comp = new TH1F("comp","",numPtBins,binning);  
    TH1F *comp_pi0 = new TH1F("comp_pi0","",numPtBins,binning);  
    TH1F *comp_eta = new TH1F("comp_eta","",numPtBins,binning); 
    TH1F *comp_gamma = new TH1F("comp_gamma","",numPtBins,binning); 
    TH1F *comp_e = new TH1F("comp_e","",numPtBins,binning); 
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

    if(save){	
	char dFile[500];
	sprintf(dFile,"../root/Hijing_NPE_Full.root");
	TFile *f_D = new TFile(dFile);
	TChain *ch1 = f_D->Get("Signal_tree");
	TChain *ch11 = f_D->Get("EH");
	char dFile1[500];
	sprintf(dFile1,"../../NPE_Ana/production/NPE_Tuples_TuneB11.root");
	TFile *f_D1 = new TFile(dFile1);
	ch3 = (TChain*)f_D1->Get("PhoE");
	ch33 = (TChain*)f_D1->Get("Signal");

	TH2F *dcapt = new TH2F("dcapt","dcapt",600,-6,0,85,0,8.5);dcapt->Sumw2();
	TH2F *dcapt_ni = new TH2F("dcapt_ni","dcapt_ni",600,-6,0,85,0,8.5);dcapt_ni->Sumw2();
	TH2F *phipt = new TH2F("phipt","phipt",20,-3.15,3.15,85,0,8.5);phipt->Sumw2();
	TH2F *phipt_ni = new TH2F("phipt_ni","phipt_ni",20,-3.15,3.15,85,0,8.5);phipt_ni->Sumw2();
	TH2F *etapt = new TH2F("etapt","etapt",50,-1,1,85,0,8.5);etapt->Sumw2();
	TH2F *etapt_ni = new TH2F("etapt_ni","etapt_ni",50,-1,1,85,0,8.5);etapt_ni->Sumw2();
	TH2F *vzpt = new TH2F("vzpt","vzpt",50,-6,6,85,0,8.5);vzpt->Sumw2();
	TH2F *vzpt_ni = new TH2F("vzpt_ni","vzpt_ni",50,-6,6,85,0,8.5);vzpt_ni->Sumw2();


	TH2F *dcapt_all = new TH2F("dcapt_all","dcapt_all",600,-6,0,85,0,8.5);dcapt_all->Sumw2();
	TH2F *dcapt_all_ni = new TH2F("dcapt_all_ni","dcapt_all_ni",600,-6,0,85,0,8.5);dcapt_all_ni->Sumw2();
	TH2F *dcapt_eta = new TH2F("dcapt_eta","dcapt_eta",600,-6,0,85,0,8.5);dcapt_eta->Sumw2();
	TH2F *dcapt_pi0 = new TH2F("dcapt_pi0","dcapt_pi0",600,-6,0,85,0,8.5);dcapt_pi0->Sumw2();
	TH2F *dcapt_pi0_gamma = new TH2F("dcapt_pi0_gamma","dcapt_pi0_gamma",600,-6,0,85,0,8.5);dcapt_pi0_gamma->Sumw2();
	TH2F *dcapt_eta_gamma = new TH2F("dcapt_eta_gamma","dcapt_eta_gamma",600,-6,0,85,0,8.5);dcapt_eta_gamma->Sumw2();
	TH2F *dcapt_gamma = new TH2F("dcapt_gamma","dcapt_gamma",600,-6,0,85,0,8.5);dcapt_gamma->Sumw2();

	TH2F *dcapt_eta_low = new TH2F("dcapt_eta_low","dcapt_eta_low",600,-6,0,85,0,8.5);dcapt_eta_low->Sumw2();
	TH2F *dcapt_pi0_low = new TH2F("dcapt_pi0_low","dcapt_pi0_low",600,-6,0,85,0,8.5);dcapt_pi0_low->Sumw2();
	TH2F *dcapt_gamma_low = new TH2F("dcapt_gamma_low","dcapt_gamma_low",600,-6,0,85,0,8.5);dcapt_gamma_low->Sumw2();
	TH2F *dcapt_eta_high = new TH2F("dcapt_eta_high","dcapt_eta_high",600,-6,0,85,0,8.5);dcapt_eta_high->Sumw2();
	TH2F *dcapt_pi0_high = new TH2F("dcapt_pi0_high","dcapt_pi0_high",600,-6,0,85,0,8.5);dcapt_pi0_high->Sumw2();
	TH2F *dcapt_gamma_high = new TH2F("dcapt_gamma_high","dcapt_gamma_high",600,-6,0,85,0,8.5);dcapt_gamma_high->Sumw2();




	TH2F *pt2D_eta = new TH2F("pt2D_eta","pt2D_eta",100,0,20,100,0,20);pt2D_eta->Sumw2();
	TH2F *pt2D_pi0 = new TH2F("pt2D_pi0","pt2D_pi0",100,0,20,100,0,20);pt2D_pi0->Sumw2();
	TH2F *pt2D_pi01 = new TH2F("pt2D_pi01","pt2D_pi01",100,0,20,100,0,20);pt2D_pi01->Sumw2();
	TH2F *pt2D_pi02 = new TH2F("pt2D_pi02","pt2D_pi02",100,0,20,100,0,20);pt2D_pi02->Sumw2();
	TH2F *pt2D_gamma = new TH2F("pt2D_gamma","pt2D_gamma",100,0,20,100,0,20);pt2D_gamma->Sumw2();
	TH2F *pt2D_eh_eta = new TH2F("pt2D_eh_eta","pt2D_eh_eta",100,0,20,100,0,20);pt2D_eh_eta->Sumw2();
	TH2F *pt2D_eh_pi0 = new TH2F("pt2D_eh_pi0","pt2D_eh_pi0",100,0,20,100,0,20);pt2D_eh_pi0->Sumw2();
	TH2F *pt2D_eh_pi01 = new TH2F("pt2D_eh_pi01","pt2D_eh_pi01",100,0,20,100,0,20);pt2D_eh_pi01->Sumw2();
	TH2F *pt2D_eh_pi02 = new TH2F("pt2D_eh_pi02","pt2D_eh_pi02",100,0,20,100,0,20);pt2D_eh_pi02->Sumw2();
	TH2F *pt2D_eh_gamma = new TH2F("pt2D_eh_gamma","pt2D_eh_gamma",100,0,20,100,0,20);pt2D_eh_gamma->Sumw2();
	TH2F *phirespt_eta = new TH2F("phirespt_eta","phirespt_eta",4000,-4,4,85,0,8.5);phirespt_eta->Sumw2();
	TH2F *phirespt_pi0 = new TH2F("phirespt_pi0","phirespt_pi0",4000,-4,4,85,0,8.5);phirespt_pi0->Sumw2();
	TH2F *phirespt_eta_mm = new TH2F("phirespt_eta_mm","phirespt_eta_mm",4000,-4,4,85,0,8.5);phirespt_eta_mm->Sumw2();
	TH2F *phirespt_pi0_mm = new TH2F("phirespt_pi0_mm","phirespt_pi0_mm",4000,-4,4,85,0,8.5);phirespt_pi0_mm->Sumw2();
	TH2F *phirespt_gamma = new TH2F("phirespt_gamma","phirespt_gamma",4000,-4,4,85,0,8.5);phirespt_gamma->Sumw2();
	TH2F *phirespt_gamma_mm = new TH2F("phirespt_gamma_mm","phirespt_gamma_mm",4000,-4,4,85,0,8.5);phirespt_gamma_mm->Sumw2();
	TH2F *cosphirespt_eta = new TH2F("cosphirespt_eta","cosphirespt_eta",1000,-1,1,85,0,8.5);cosphirespt_eta->Sumw2();
	TH2F *cosphirespt_pi0 = new TH2F("cosphirespt_pi0","cosphirespt_pi0",1000,-1,1,85,0,8.5);cosphirespt_pi0->Sumw2();
	TH2F *cosphirespt_eta_mm = new TH2F("cosphirespt_eta_mm","cosphirespt_eta_mm",1000,-1,1,85,0,8.5);cosphirespt_eta_mm->Sumw2();
	TH2F *cosphirespt_pi0_mm = new TH2F("cosphirespt_pi0_mm","cosphirespt_pi0_mm",1000,-1,1,85,0,8.5);cosphirespt_pi0_mm->Sumw2();
	TH2F *cosphirespt_gamma = new TH2F("cosphirespt_gamma","cosphirespt_gamma",1000,-1,1,85,0,8.5);cosphirespt_gamma->Sumw2();
	TH2F *cosphirespt_gamma_mm = new TH2F("cosphirespt_gamma_mm","cosphirespt_gamma_mm",1000,-1,1,85,0,8.5);cosphirespt_gamma_mm->Sumw2();


	TH2F *phi2D_eta = new TH2F("phi2D_eta","phi2D_eta",100,-3.15,3.15,100,-3.15,3.15);phi2D_eta->Sumw2();
	TH2F *phi2D_pi0 = new TH2F("phi2D_pi0","phi2D_pi0",100,-3.15,3.15,100,-3.15,3.15);phi2D_pi0->Sumw2();
	TH2F *phi2D_gamma = new TH2F("phi2D_gamma","phi2D_gamma",100,-3.15,3.15,100,-3.15,3.15);phi2D_gamma->Sumw2();

	TH2F *phipt_eta_nw = new TH2F("phipt_eta_nw","phipt_eta_nw",20,-3.15,3.15,85,0,8.5);phipt_eta_nw->Sumw2();
	TH2F *phipt_pi0_nw = new TH2F("phipt_pi0_nw","phipt_pi0_nw",20,-3.15,3.15,85,0,8.5);phipt_pi0_nw->Sumw2();
	TH2F *phipt_gamma_nw = new TH2F("phipt_gamma_nw","phipt_gamma_nw",20,-3.15,3.15,85,0,8.5);phipt_gamma_nw->Sumw2();
	TH2F *phipt_eta_nw_ni = new TH2F("phipt_eta_nw_ni","phipt_eta_nw_ni",20,-3.15,3.15,85,0,8.5);phipt_eta_nw_ni->Sumw2();
	TH2F *phipt_pi0_nw_ni = new TH2F("phipt_pi0_nw_ni","phipt_pi0_nw_ni",20,-3.15,3.15,85,0,8.5);phipt_pi0_nw_ni->Sumw2();
	TH2F *phipt_gamma_nw_ni = new TH2F("phipt_gamma_nw_ni","phipt_gamma_nw_ni",20,-3.15,3.15,85,0,8.5);phipt_gamma_nw_ni->Sumw2();

	TH2F *etapt_eta_nw = new TH2F("etapt_eta_nw","etapt_eta_nw",50,-1,1,85,0,8.5);etapt_eta_nw->Sumw2();
	TH2F *etapt_pi0_nw = new TH2F("etapt_pi0_nw","etapt_pi0_nw",50,-1,1,85,0,8.5);etapt_pi0_nw->Sumw2();
	TH2F *etapt_gamma_nw = new TH2F("etapt_gamma_nw","etapt_gamma_nw",50,-1,1,85,0,8.5);etapt_gamma_nw->Sumw2();
	TH2F *etapt_eta_nw_ni = new TH2F("etapt_eta_nw_ni","etapt_eta_nw_ni",50,-1,1,85,0,8.5);etapt_eta_nw_ni->Sumw2();
	TH2F *etapt_pi0_nw_ni = new TH2F("etapt_pi0_nw_ni","etapt_pi0_nw_ni",50,-1,1,85,0,8.5);etapt_pi0_nw_ni->Sumw2();
	TH2F *etapt_gamma_nw_ni = new TH2F("etapt_gamma_nw_ni","etapt_gamma_nw_ni",50,-1,1,85,0,8.5);etapt_gamma_nw_ni->Sumw2();

	TH2F *vzpt_eta_nw = new TH2F("vzpt_eta_nw","vzpt_eta_nw",50,-6,6,85,0,8.5);vzpt_eta_nw->Sumw2();
	TH2F *vzpt_pi0_nw = new TH2F("vzpt_pi0_nw","vzpt_pi0_nw",50,-6,6,85,0,8.5);vzpt_pi0_nw->Sumw2();
	TH2F *vzpt_gamma_nw = new TH2F("vzpt_gamma_nw","vzpt_gamma_nw",50,-6,6,85,0,8.5);vzpt_gamma_nw->Sumw2();
	TH2F *vzpt_eta_nw_ni = new TH2F("vzpt_eta_nw_ni","vzpt_eta_nw_ni",50,-6,6,85,0,8.5);vzpt_eta_nw_ni->Sumw2();
	TH2F *vzpt_pi0_nw_ni = new TH2F("vzpt_pi0_nw_ni","vzpt_pi0_nw_ni",50,-6,6,85,0,8.5);vzpt_pi0_nw_ni->Sumw2();
	TH2F *vzpt_gamma_nw_ni = new TH2F("vzpt_gamma_nw_ni","vzpt_gamma_nw_ni",50,-6,6,85,0,8.5);vzpt_gamma_nw_ni->Sumw2();
	TH2F *dcapt_all_nw1 = new TH2F("dcapt_all_nw1","dcapt_all_nw1",2*260,-12,1,85,0,8.5);dcapt_all_nw1->Sumw2();
	TH2F *dcapt_all_nw = new TH2F("dcapt_all_nw","dcapt_all_nw",600,-6,0,85,0,8.5);dcapt_all_nw->Sumw2();
	TH2F *dcapt_eta_nw = new TH2F("dcapt_eta_nw","dcapt_eta_nw",600,-6,0,85,0,8.5);dcapt_eta_nw->Sumw2();
	TH2F *dcapt_pi0_nw = new TH2F("dcapt_pi0_nw","dcapt_pi0_nw",600,-6,0,85,0,8.5);dcapt_pi0_nw->Sumw2();
	TH2F *dcapt_pi0_gamma_nw = new TH2F("dcapt_pi0_gamma_nw","dcapt_pi0_gamma_nw",600,-6,0,85,0,8.5);dcapt_pi0_gamma_nw->Sumw2();
	TH2F *dcapt_eta_gamma_nw = new TH2F("dcapt_eta_gamma_nw","dcapt_eta_gamma_nw",600,-6,0,85,0,8.5);dcapt_eta_gamma_nw->Sumw2();
	TH2F *dcapt_gamma_nw = new TH2F("dcapt_gamma_nw","dcapt_gamma_nw",600,-6,0,85,0,8.5);dcapt_gamma_nw->Sumw2();

	TH2F *dcapt_all_nw_ni = new TH2F("dcapt_all_nw_ni","dcapt_all_nw_ni",600,-6,0,85,0,8.5);dcapt_all_nw_ni->Sumw2();
	TH2F *dcapt_eta_nw_ni = new TH2F("dcapt_eta_nw_ni","dcapt_eta_nw_ni",600,-6,0,85,0,8.5);dcapt_eta_nw_ni->Sumw2();
	TH2F *dcapt_pi0_nw_ni = new TH2F("dcapt_pi0_nw_ni","dcapt_pi0_nw_ni",600,-6,0,85,0,8.5);dcapt_pi0_nw_ni->Sumw2();
	TH2F *dcapt_pi0_gamma_nw_ni = new TH2F("dcapt_pi0_gamma_nw_ni","dcapt_pi0_gamma_nw_ni",600,-6,0,85,0,8.5);dcapt_pi0_gamma_nw_ni->Sumw2();
	TH2F *dcapt_eta_gamma_nw_ni = new TH2F("dcapt_eta_gamma_nw_ni","dcapt_eta_gamma_nw_ni",600,-6,0,85,0,8.5);dcapt_eta_gamma_nw_ni->Sumw2();
	TH2F *dcapt_gamma_nw_ni = new TH2F("dcapt_gamma_nw_ni","dcapt_gamma_nw_ni",600,-6,0,85,0,8.5);dcapt_gamma_nw_ni->Sumw2();

	TH2F *dcapt_eh_gamma = new TH2F("dcapt_eh_gamma","dcapt_eh_gamma",600,-6,0,85,0,8.5);dcapt_eh_gamma->Sumw2();
	TH2F *dcapt_eh_eta = new TH2F("dcapt_eh_eta","dcapt_eh_eta",600,-6,0,85,0,8.5);dcapt_eh_eta->Sumw2();
	TH2F *dcapt_eh_pi0 = new TH2F("dcapt_eh_pi0","dcapt_eh_pi0",600,-6,0,85,0,8.5);dcapt_eh_pi0->Sumw2();
	TH2F *dcapt_eh_eta_gamma = new TH2F("dcapt_eh_eta_gamma","dcapt_eh_eta_gamma",600,-6,0,85,0,8.5);dcapt_eh_eta_gamma->Sumw2();
	TH2F *dcapt_eh_pi0_gamma = new TH2F("dcapt_eh_pi0_gamma","dcapt_eh_pi0_gamma",600,-6,0,85,0,8.5);dcapt_eh_pi0_gamma->Sumw2();
	TH2F *dcapt_eh_all = new TH2F("dcapt_eh_all","dcapt_eh_all",600,-6,0,85,0,8.5);dcapt_eh_all->Sumw2();
	TH2F *dcapt_eh_all_m1 = new TH2F("dcapt_eh_all_m1","dcapt_eh_all_m1",600,-6,0,85,0,8.5);dcapt_eh_all_m1->Sumw2();
	TH2F *dcapt_eh_all_m2 = new TH2F("dcapt_eh_all_m2","dcapt_eh_all_m2",600,-6,0,85,0,8.5);dcapt_eh_all_m2->Sumw2();
	TH2F *dcapt_eh_all_m3 = new TH2F("dcapt_eh_all_m3","dcapt_eh_all_m3",600,-6,0,85,0,8.5);dcapt_eh_all_m3->Sumw2();
	TH2F *dcapt_eh_all_m4 = new TH2F("dcapt_eh_all_m4","dcapt_eh_all_m4",600,-6,0,85,0,8.5);dcapt_eh_all_m4->Sumw2();
	
        TH2F *dcapt_all_m1 = new TH2F("dcapt_all_m1","dcapt_all_m1",600,-6,0,85,0,8.5);dcapt_all_m1->Sumw2();
        TH2F *dcapt_all_m2 = new TH2F("dcapt_all_m2","dcapt_all_m2",600,-6,0,85,0,8.5);dcapt_all_m2->Sumw2();
        TH2F *dcapt_all_m3 = new TH2F("dcapt_all_m3","dcapt_all_m3",600,-6,0,85,0,8.5);dcapt_all_m3->Sumw2();
        TH2F *dcapt_all_m4 = new TH2F("dcapt_all_m4","dcapt_all_m4",600,-6,0,85,0,8.5);dcapt_all_m4->Sumw2();

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

	TH2F *h1 = new TH2F("h1","h1",600,-6,0,85,0,8.5);
	TH2F *h2 = new TH2F("h2","h2",600,-6,0,85,0,8.5);
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
	float s_gparentphi;
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
	float s_vz;
	float s_parentphi;

	double num_e = 1288444;
	int num_eta = 200e3;//750E3;
	int num_pi0 = 200e3;//1280E3;
	double num_gamma = 16.78E6;
//======================================================================     
	ch3->Project("h1","probe_pt:log10(abs(probe_dca)+0.000000001)","probe_charge*tag_charge<0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && (tag_beta!=0 || probe_beta!=0)")  ;
	ch3->Project("h2","probe_pt:log10(abs(probe_dca)+0.000000001)","probe_charge*tag_charge>0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && (tag_beta!=0 || probe_beta!=0)")  ;
	ch3->Project("h11","pair_decayradius:probe_pt","probe_charge*tag_charge<0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && (tag_beta!=0 || probe_beta!=0)")  ;
	ch3->Project("h22","pair_decayradius:probe_pt","probe_charge*tag_charge>0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && (tag_beta!=0 || probe_beta!=0)")  ;
	ch3->Project("h111","PhoE_M:probe_pt","probe_charge*tag_charge<0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && (tag_beta!=0 || probe_beta!=0)")  ;
	ch3->Project("h222","PhoE_M:probe_pt","probe_charge*tag_charge>0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3 && (tag_beta!=0 || probe_beta!=0)")  ;
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
	ch1->SetBranchAddress("sig_eta",&s_eta);
	ch1->SetBranchAddress("sig_vz",&s_vz);
	ch1->SetBranchAddress("sig_phi",&s_phi);	
	ch1->SetBranchAddress("sig_gparentphi",&s_gparentphi);
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
	    if(fabs(s_dcaxy)>1)continue;
	    if(s_pt<0)continue;	    
	    if(s_hft<1)continue;
	    if(s_head==0){
		dcapt_ni->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt);
		etapt_ni->Fill(s_eta,s_pt);   
		phipt_ni->Fill(s_phi,s_pt); 
		vzpt_ni->Fill(s_vz,s_pt); 
	    }
	    if(s_head==149 && s_gparentid==0){	
		dcapt_pi0_nw_ni->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt);   
 		etapt_pi0_nw_ni->Fill(s_eta,s_pt);   
		phipt_pi0_nw_ni->Fill(s_phi,s_pt); 
		vzpt_pi0_nw_ni->Fill(s_vz,s_pt);      
		if(s_parentpt<3)dcapt_pi0_low->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);  
		if(s_parentpt>4)dcapt_pi0_high->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);  
	    } 
	    if(s_head==147 && s_gparentid==0){    
		dcapt_eta_nw_ni->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt);
		etapt_eta_nw_ni->Fill(s_eta,s_pt);
		phipt_eta_nw_ni->Fill(s_phi,s_pt);
		vzpt_eta_nw_ni->Fill(s_vz,s_pt);
		if(s_parentpt<3)dcapt_eta_low->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);  
		if(s_parentpt>4)dcapt_eta_high->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);  
	    }
	    if(s_head==1 && s_gparentid==0){
		dcapt_gamma_nw_ni->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt);
		etapt_gamma_nw_ni->Fill(s_eta,s_pt);
		phipt_gamma_nw_ni->Fill(s_phi,s_pt);
		vzpt_gamma_nw_ni->Fill(s_vz,s_pt);
		if(s_parentpt<3)dcapt_gamma_low->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);  
		if(s_parentpt>4)dcapt_gamma_high->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);  
	    }
	}

	for(int i =0;i<ch1->GetEntries();i++){
	    ch1->GetEntry(i);
	    if(i%100000==0)cout << "on " << i << " of " << ch1->GetEntries() << endl;
	    if(!(s_id==3 || s_id==2))continue;
	    if(s_pt<0)continue;
	    if(fabs(s_dcaxy)>1)continue;
	    if(s_hft<1)continue;
	    if(s_parentid!=1)continue;
	    //if(TMath::Log10(fabs(s_dcaxy))<-1.5 || TMath::Log10(fabs(s_dcaxy))>-1)continue;
	    double ww = 1;
	    //============================================
            //Get Weights
            //============================================
	    double pt_for_weight = -1;
	    if(s_head==s_parentid)pt_for_weight=s_parentpt;
	    else if(s_head==s_gparentid)pt_for_weight=s_gparentpt;
	    if(s_head!=0){
		if(pt_for_weight/s_pt<0.8)continue;
	    }
	    if(s_head == 149){	   
		//int bin = pi0_new_weights->FindBin(s_pt);
                //ww = pi0_new_weights->GetBinContent(bin)*0.281748*5;
		int bin = pi0_weights->FindBin(pt_for_weight);
                ww = pi0_weights->GetBinContent(bin)*0.281748*5;
		//ww = fpi->Eval(s_pt);    
	    } else if(s_head == 147){	
		//int bin = eta_new_weights->FindBin(s_pt);
                //ww = eta_new_weights->GetBinContent(bin)*0.281748*0.0069/0.0174*0.45*5;
		int bin = eta_weights->FindBin(pt_for_weight);
                ww = eta_weights->GetBinContent(bin)*0.281748*0.0069/0.0174*0.45*5;
		//ww = feta->Eval(s_pt);	            
	    } else if(s_head == 1){
		if(pt_for_weight<1.17)pt_for_weight==1.17;
	        int bin = gamma_weights->FindBin(pt_for_weight);
                //ww = gamma_weights->GetBinContent(bin)/0.0174; 
		//int bin = gamma_new_weights->FindBin(s_pt);
                //ww = gamma_new_weights->GetBinContent(bin)/0.0174; 
		//ww = fgamma->Eval(s_pt)*1.4;
	    }	
	    //int bin_cor = comp->FindBin(s_pt);
	    //ww*=corr[bin_cor-1];
	    //ww=1;
	    //if(s_ist==0)ww*=10;
	    //============================================
	    // Fill
	    //ww*=10e6;
	    //if(fabs(s_parentphi-s_phi)>TMath::Pi()){
	    //	if(s_parentphi<0)s_parentphi+=TMath::Pi()*2;
//		if(s_phi<0)s_phi+=TMath::Pi()*2;
//	    }     
            //============================================
	    if((s_parentphi-s_phi) > TMath::Pi())s_phi+=TMath::Pi()*2;
	    if((s_parentphi-s_phi) < -TMath::Pi())s_parentphi+=TMath::Pi()*2;
	    if((s_head==149)||(s_head==147) && s_gparentid==0){
		dcapt_all_ni->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);
		if(s_iso)dcapt_all->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);
	    }
	    if(s_head==1){
		dcapt_all_ni->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww*(1+1/(1.21361-1)));
		if(s_iso)dcapt_all->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww*(1+1/(1.21361-1)));	
	    }
	    if(s_iso==0)continue;	  
	    if(s_head==0){
		dcapt->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);
		etapt->Fill(s_eta,s_pt);
		phipt->Fill(s_phi,s_pt);
		vzpt->Fill(s_vz,s_pt);
	    }
	    if(s_head==149 && s_gparentid==149 && s_parentid==1){
    
		phipt_pi0_nw->Fill(s_phi,s_pt);
		etapt_pi0_nw->Fill(s_eta,s_pt);
		vzpt_pi0_nw->Fill(s_vz,s_pt);
		phirespt_pi0->Fill((s_gparentphi-s_phi),s_pt);
		cosphirespt_pi0->Fill(cos(2*(s_gparentphi-s_phi)),s_pt);
		if(s_px1*s_px2*s_ist*s_ssd==0)phirespt_pi0_mm->Fill((s_parentphi-s_phi),s_pt);	
		phi2D_pi0->Fill(s_gparentphi,s_phi);

		pt2D_pi0->Fill(s_pt,s_gparentpt,ww);
		pt2D_pi01->Fill(s_pt,s_parentpt,ww);
		pt2D_pi02->Fill(s_parentpt,s_gparentpt,ww);
		dcapt_pi0_nw->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);    
 		dcapt_pi0->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);      
	    } 
	    if(s_head==147 && s_gparentid==147 && s_parentid==1){
		phipt_eta_nw->Fill(s_phi,s_pt);
		etapt_eta_nw->Fill(s_eta,s_pt);
		vzpt_eta_nw->Fill(s_vz,s_pt);
	
		dcapt_eta_nw->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);
		dcapt_eta->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);
		phirespt_eta->Fill((s_gparentphi-s_phi),s_pt);
		cosphirespt_eta->Fill(cos(2*(s_gparentphi-s_phi)),s_pt);
		if(s_px1*s_px2*s_ist*s_ssd==0)phirespt_eta_mm->Fill((s_parentphi-s_phi),s_pt);
		phi2D_eta->Fill(s_gparentphi,s_phi,ww);
		pt2D_eta->Fill(s_pt,s_gparentpt);
	    }
	    if((s_head==149)||(s_head==147) && s_parentid==1){
	

		dcapt_all_nw->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);
		if(s_px1*s_px2*s_ist==0)dcapt_all_m1->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);
		else if(s_ist*s_px2*s_px1>0)dcapt_all_m4->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);		
	    }
	    if(s_head==1 && s_parentid==1 && s_gparentid==0){
		dcapt_gamma->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);
		phipt_gamma_nw->Fill(s_phi,s_pt);
		etapt_gamma_nw->Fill(s_eta,s_pt);
		vzpt_gamma_nw->Fill(s_vz,s_pt);
		cosphirespt_gamma->Fill(cos(2*(s_gparentphi-s_phi)),s_pt);
		phirespt_gamma->Fill((s_gparentphi-s_phi),s_pt);
		if(s_px1*s_px2*s_ist*s_ssd==0)phirespt_gamma_mm->Fill((s_parentphi-s_phi),s_pt);
		phi2D_gamma->Fill(s_gparentphi,s_phi);
		pt2D_gamma->Fill(s_pt,s_gparentpt,ww);
		dcapt_gamma_nw->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);
		dcapt_eta_gamma->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww*0.2*1/(1.21361-1));
		dcapt_pi0_gamma->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww*0.8*1/(1.21361-1));
		dcapt_eta_gamma_nw->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,0.2*1/(1.21361-1));
		dcapt_pi0_gamma_nw->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,0.8*1/(1.21361-1));
	    }
	    if(s_head==1){
	
		dcapt_all_nw->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,(1+1/(1.21361-1)));
		if(s_px1*s_px2*s_ist*s_ssd==0)dcapt_all_m1->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww*(1+1/(1.21361-1)));
		else if(s_ist*s_px2*s_px1>0)dcapt_all_m4->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww*(1+1/(1.21361-1)));		    		
	    }
	}
		
//======================================================================
//======================================================================
//======================================================================
	h1->SetMarkerStyle(8);
	h1->SetLineColor(1);
	h1->SetMarkerColor(1);
	h1->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
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
	etapt_pi0_nw_ni->SetLineColor(kBlue);  
	etapt_pi0_nw_ni->SetMarkerColor(kBlue); 
	etapt_eta_nw_ni->SetLineColor(kGreen-2);
	etapt_eta_nw_ni->SetMarkerColor(kGreen-2); 
	etapt_gamma_nw_ni->SetLineColor(kRed);  
	etapt_gamma_nw_ni->SetMarkerColor(kRed);  
	phipt_pi0_nw_ni->SetLineColor(kBlue);  
	phipt_pi0_nw_ni->SetMarkerColor(kBlue); 
	phipt_eta_nw_ni->SetLineColor(kGreen-2);
	phipt_eta_nw_ni->SetMarkerColor(kGreen-2); 
	phipt_gamma_nw_ni->SetLineColor(kRed);  
	phipt_gamma_nw_ni->SetMarkerColor(kRed);  
	vzpt_pi0_nw_ni->SetLineColor(kBlue);  
	vzpt_pi0_nw_ni->SetMarkerColor(kBlue); 
	vzpt_eta_nw_ni->SetLineColor(kGreen-2);
	vzpt_eta_nw_ni->SetMarkerColor(kGreen-2); 
	vzpt_gamma_nw_ni->SetLineColor(kRed);  
	vzpt_gamma_nw_ni->SetMarkerColor(kRed);  
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

	double low_dca = 5.5;
	double high_dca = 8.5;
	char label[100];
	sprintf(label,"#it{p}_{T}#in [%1.1f,%1.1f] GeV",low_dca,high_dca);

	int bin1 = dcapt_ni->GetYaxis()->FindBin(low_dca);
	int bin2 = dcapt_ni->GetYaxis()->FindBin(high_dca);

	pt= (TH1F*)dcapt->ProjectionY();
	pt_ni= (TH1F*)dcapt_ni->ProjectionY();  
	dca= (TH1F*)dcapt->ProjectionX("dcapt_x",bin1,bin2);
	dca_ni= (TH1F*)dcapt_ni->ProjectionX("dcapt_ni_x",bin1,bin2);   
	eta= (TH1F*)etapt->ProjectionX();
	eta_ni= (TH1F*)etapt_ni->ProjectionX();   
	phi= (TH1F*)phipt->ProjectionX();
	phi_ni= (TH1F*)phipt_ni->ProjectionX();   
	vz= (TH1F*)vzpt->ProjectionX();
	vz_ni= (TH1F*)vzpt_ni->ProjectionX();    
	pt_all =(TH1F*)dcapt_all->ProjectionY();     
	pt_all_ni =(TH1F*)dcapt_all_ni->ProjectionY();   
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
	eta_eta_nw =(TH1F*)etapt_eta_nw->ProjectionX();     
	eta_pi0_nw =(TH1F*)etapt_pi0_nw->ProjectionX(); 
	eta_gamma_nw =(TH1F*)etapt_gamma_nw->ProjectionX(); 
	phi_eta_nw =(TH1F*)phipt_eta_nw->ProjectionX();     
	phi_pi0_nw =(TH1F*)phipt_pi0_nw->ProjectionX(); 
	phi_gamma_nw =(TH1F*)phipt_gamma_nw->ProjectionX(); 
	vz_eta_nw =(TH1F*)vzpt_eta_nw->ProjectionX();     
	vz_pi0_nw =(TH1F*)vzpt_pi0_nw->ProjectionX(); 
	vz_gamma_nw =(TH1F*)vzpt_gamma_nw->ProjectionX(); 
	pt_eta_nw_ni =(TH1F*)dcapt_eta_nw_ni->ProjectionY();     
	pt_pi0_nw_ni =(TH1F*)dcapt_pi0_nw_ni->ProjectionY(); 
	pt_gamma_nw_ni =(TH1F*)dcapt_gamma_nw_ni->ProjectionY(); 
	phi_eta_nw_ni =(TH1F*)phipt_eta_nw_ni->ProjectionX();     
	phi_pi0_nw_ni =(TH1F*)phipt_pi0_nw_ni->ProjectionX(); 
	phi_gamma_nw_ni =(TH1F*)phipt_gamma_nw_ni->ProjectionX(); 
	eta_eta_nw_ni =(TH1F*)etapt_eta_nw_ni->ProjectionX();     
	eta_pi0_nw_ni =(TH1F*)etapt_pi0_nw_ni->ProjectionX(); 
	eta_gamma_nw_ni =(TH1F*)etapt_gamma_nw_ni->ProjectionX(); 
	vz_eta_nw_ni =(TH1F*)vzpt_eta_nw_ni->ProjectionX();     
	vz_pi0_nw_ni =(TH1F*)vzpt_pi0_nw_ni->ProjectionX(); 
	vz_gamma_nw_ni =(TH1F*)vzpt_gamma_nw_ni->ProjectionX(); 

	
	dca_gamma_nw =(TH1F*)dcapt_gamma_nw->ProjectionX("dcaptdcapt_gamma_nw_x",bin1,bin2);  
	dca_eta_nw =(TH1F*)dcapt_eta_nw->ProjectionX("dcaptdcapt_eta_nw_x",bin1,bin2);     
	dca_pi0_nw =(TH1F*)dcapt_pi0_nw->ProjectionX("dcapt_pi0_nw_x",bin1,bin2); 
	dca_gamma_nw_ni =(TH1F*)dcapt_gamma_nw_ni->ProjectionX("dcapt_gamma_nw_ni_x",bin1,bin2);  
	dca_eta_nw_ni =(TH1F*)dcapt_eta_nw_ni->ProjectionX("dcapt_eta_nw_ni_x",bin1,bin2);     
	dca_pi0_nw_ni =(TH1F*)dcapt_pi0_nw_ni->ProjectionX("dcapt_pi0_nw_ni_x",bin1,bin2); 

//======================================================================
	for(int i=0;i<9;i++){
	    int bin1 = pt_pi0->FindBin(binning[i]);
	    int bin2 = pt_pi0->FindBin(binning[i+1]);
	    double temp1 = pt_pi0->Integral(bin1,bin2);
	    double temp2 = pt_eta->Integral(bin1,bin2);
	    double temp3 = pt_gamma->Integral(bin1,bin2);
	    double temp4 = pt_pi0_gamma->Integral(bin1,bin2);
	    double temp5 = pt_eta_gamma->Integral(bin1,bin2);
	    double temp6 = temp1+temp2+temp3+temp4+temp5;
	    if(temp6>0){
		comp1->SetBinContent(i+1,temp1/temp6);
		comp2->SetBinContent(i+1,temp2/temp6);
		comp3->SetBinContent(i+1,temp3/temp6);
		comp4->SetBinContent(i+1,temp4/temp6);
		comp5->SetBinContent(i+1,temp5/temp6);
	    }
	    /*double temp7 = pt_all->Integral(bin1,bin2);
	      double temp8 = pt_all_ni->Integral(bin1,bin2);

	    double tempp1 = pt_pi0_nw->Integral(bin1,bin2);
	    double tempp = pt_pi0_nw_ni->Integral(bin1,bin2);
	    double tempe1 = pt_eta_nw->Integral(bin1,bin2);
	    double tempe = pt_eta_nw_ni->Integral(bin1,bin2);
	    double tempg1 = pt_gamma_nw->Integral(bin1,bin2);
	    double tempg = pt_gamma_nw_ni->Integral(bin1,bin2);
	    double tempse1 = pt->Integral(bin1,bin2);
	    double tempse = pt_ni->Integral(bin1,bin2);
	    cout << "Eff for bin " << i << " " << temp7/temp8 << endl;
	    comp->SetBinContent(i+1,temp7/temp8);
	    comp->SetBinError(i+1,temp7/temp8*sqrt(1/temp7));
	    comp_pi0->SetBinContent(i+1,tempp1/tempp);
	    comp_pi0->SetBinError(i+1,tempp1/tempp*sqrt(1/tempp1));
	    comp_eta->SetBinContent(i+1,tempe1/tempe);
	    comp_eta->SetBinError(i+1,tempe1/tempe*sqrt(1/tempe1));
	    comp_gamma->SetBinContent(i+1,tempg1/tempg);
	    comp_gamma->SetBinError(i+1,tempg1/tempg*sqrt(1/tempg1));
	    comp_e->SetBinContent(i+1,tempse1/tempse);
	    comp_e->SetBinError(i+1,tempse1/tempse*sqrt(1/tempse1));*/
	}


	comp1->SetLineColor(kBlue);
	comp1->SetMarkerColor(kBlue);   
	comp2->SetLineColor(kGreen-2);
	comp2->SetMarkerColor(kGreen-2);
	comp3->SetLineColor(kRed);
	comp3->SetMarkerColor(kRed); 

	comp_pi0->SetLineColor(kBlue);
	comp_pi0->SetMarkerColor(kBlue);   
	comp_eta->SetLineColor(kGreen-2);
	comp_eta->SetMarkerColor(kGreen-2);
	comp_gamma->SetLineColor(kRed);
	comp_gamma->SetMarkerColor(kRed); 

	comp4->SetLineColor(kCyan);
	comp4->SetMarkerColor(kCyan);
	comp5->SetLineColor(kGray);
	comp5->SetMarkerColor(kGray);
	comp->SetLineColor(kGray+2);
	comp->SetMarkerColor(kGray+2);

	TLegend *leg = new TLegend(0.2,0.6,0.5,0.9);
	leg->AddEntry(comp1,"#pi^{0} Dalitz Decay","PE");
	leg->AddEntry(comp2,"#eta Dalitz Decay","PE");	
	leg->AddEntry(comp3,"Direct #gamma","PE");
	leg->AddEntry(comp4,"#pi^{0}#rightarrow #gamma#gamma","PE");
	leg->AddEntry(comp5,"#eta#rightarrow #gamma#gamma","PE");


	TCanvas *ccomp = new TCanvas("ccomp","ccomp");
	comp1->GetYaxis()->SetRangeUser(0,1);
	comp1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
	comp1->GetYaxis()->SetTitle("Relative Fraction");
	comp1->Draw("same");
	comp2->Draw("same");
	comp3->Draw("same");
	comp4->Draw("same");
	comp5->Draw("same");
	
	leg->Draw("same");


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
	    if(fabs(s_dcaxy)>1)continue;
	    double ww = 1;    
	    double pt_for_weight = -1;
	    if(s_parentid!=1)continue;
	    if(s_head==s_parentid)pt_for_weight=s_parentpt;
	    else if(s_head==s_gparentid)pt_for_weight=s_gparentpt;
	    if(pt_for_weight/s_pt<0.8)continue;
	    if(s_head == 149){	    
		int bin = pi0_weights->FindBin(pt_for_weight);
                ww = pi0_weights->GetBinContent(bin)*0.281748*5;//0.0666488
		//int bin = pi0_new_weights->FindBin(s_pt);
                //ww = pi0_new_weights->GetBinContent(bin)*0.0174/80;
		//ww = fpi->Eval(s_pt);    
	    } else if(s_head == 147){	
		int bin = pi0_weights->FindBin(pt_for_weight);
                ww = eta_weights->GetBinContent(bin)*0.281748*0.0069/0.0174*0.45*5;
		//int bin = pi0_new_weights->FindBin(s_pt);
                //ww = pi0_new_weights->GetBinContent(bin)*0.0174/80;
		//ww = feta->Eval(s_pt);	            
	    } else if(s_head == 1){
		//if(pt_for_weight<1.17)pt_for_weight==1.17;
	        int bin = gamma_weights->FindBin(pt_for_weight);
                ww = gamma_weights->GetBinContent(bin)/0.0174; 
	        //int bin = gamma_new_weights->FindBin(s_pt);
                //ww = gamma_new_weights->GetBinContent(bin)*20; 
		//ww = fgamma->Eval(s_pt)*1.4;
	    }
	    //int bin_cor = comp->FindBin(s_pt);
	    //ww*=corr[bin_cor-1];
	    //if(s_ist==0)ww*=10;
	    //ww=1;
	    if(s_head==1 && s_gparentid==0){
		dcapt_eh_gamma->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);
	    	dr_eh_gamma->Fill(s_pt,s_dr,ww);
	    	mass_eh_gamma->Fill(s_pt,s_m,ww);
		pt2D_eh_gamma->Fill(s_pt,s_gparentpt,ww);
	    }
	    if(s_head===149 && s_parentid==1&& s_gparentid==149){
		pt2D_eh_pi0->Fill(s_pt,s_gparentpt,ww);
		pt2D_eh_pi01->Fill(s_pt,s_parentpt,ww);
		pt2D_eh_pi02->Fill(s_parentpt,s_gparentpt,ww);
		if(s_parentid==7)dcapt_eh_pi0->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);		 
		if(s_parentid==7)dr_eh_pi0->Fill(s_pt,s_dr,ww);
		if(s_parentid==7)mass_eh_pi0->Fill(s_pt,s_m,ww);		 	
	    }
	    if(s_head==147 && s_parentid==1){
		pt2D_eh_eta->Fill(s_pt,s_gparentpt,ww);
		if(s_parentid==17)dcapt_eh_eta->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);       	
		if(s_parentid==17)dr_eh_eta->Fill(s_pt,s_dr,ww);
		if(s_parentid==17)mass_eh_eta->Fill(s_pt,s_m,ww);	 
	    }
	    if((s_head==147||s_head==149) && s_parentid==1){
		dcapt_eh_all->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);
		if(s_px1*s_px2*s_ist==0)dcapt_eh_all_m1->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);
		if(s_px2==0)dcapt_eh_all_m2->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);
		dcapt_eh_all_m3->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);
		if(s_ist*s_px2*s_px1>0)dcapt_eh_all_m4->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt);
	    }
	    if((s_head==147||s_head==149) && s_parentid==1){
		dr_eh_all->Fill(s_pt,s_dr,ww);
		mass_eh_all->Fill(s_pt,s_m,ww);
	    }
	    if(s_head==1 && s_gparentid==0){
		dcapt_eh_all->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww*(1+1/(1.21361-1)));
		if(s_px1*s_px2*s_ist==0)dcapt_eh_all_m1->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,(1+1/(1.21361-1)));
		if(s_px2==0)dcapt_eh_all_m2->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,(1+1/(1.21361-1)));
		dcapt_eh_all_m3->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww);
		if(s_ist*s_px2*s_px1>0)dcapt_eh_all_m4->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,(1+1/(1.21361-1)));
		dr_eh_all->Fill(s_pt,s_dr,ww*(1+1/(1.21361-1)));
		mass_eh_all->Fill(s_pt,s_m,ww*(1+1/(1.21361-1)));

		dr_eh_eta_gamma->Fill(s_pt,s_dr,ww*0.2*1/(1.21361-1));
		mass_eh_eta_gamma->Fill(s_pt,s_m,ww*0.2*1/(1.21361-1));
		dcapt_eh_eta_gamma->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww*0.2*1/(1.21361-1));
		dr_eh_pi0_gamma->Fill(s_pt,s_dr,ww*0.8*1/(1.21361-1));
		mass_eh_pi0_gamma->Fill(s_pt,s_m,ww*0.8*1/(1.21361-1));
		dcapt_eh_pi0_gamma->Fill(TMath::Log10(fabs(s_dcaxy)+0.000000001),s_pt,ww*0.8*1/(1.21361-1));
	    }
	}
//======================================================================
	TFile f("root/DCA_plots_Hijing_GammaConv.root","RECREATE");
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
	dcapt_all_ni->Write("dcapt_all_ni");
        dcapt_all_m2->Write("dcapt_all_m2");
        dcapt_all_m3->Write("dcapt_all_m3");
        dcapt_all_m4->Write("dcapt_all_m4");
	dr_eh_gamma->Write("dr_eh_gamma");
	dr_eh_pi0->Write("dr_eh_pi0");
	dr_eh_eta->Write("dr_eh_eta");
	dr_eh_pi0_gamma->Write("dr_eh_pi0_gamma");
	dr_eh_eta_gamma->Write("dr_eh_eta_gamma");
	dr_eh_all->Write("dr_eh_all");
	mass_eh_all->Write("mass_eh_all");
	dcapt_all->Write("dcapt_all");
	dcapt_all_nw->Write("dcapt_all_nw");
	dcapt_eta_nw->Write("dcapt_eta_nw");
	dcapt_pi0_nw->Write("dcapt_pi0_nw");
	dcapt_gamma_nw->Write("dcapt_gamma_nw");

	dcapt_eta_low->Write("dcapt_eta_low");
	dcapt_pi0_low->Write("dcapt_pi0_low");
	dcapt_gamma_low->Write("dcapt_gamma_low");
	dcapt_eta_high->Write("dcapt_eta_high");
	dcapt_pi0_high->Write("dcapt_pi0_high");
	dcapt_gamma_high->Write("dcapt_gamma_high");
	dcapt->Write("dcapt");
	dcapt_ni->Write("dcapt_ni");
	h1->Write("h1");
	h11->Write("h11");
	h111->Write("h111");
	phirespt_pi0->Write();
	phirespt_eta->Write();
	phirespt_gamma->Write();
	phirespt_gamma_mm->Write();
	phirespt_eta_mm->Write();
	phirespt_pi0_mm->Write();
	cosphirespt_pi0->Write();
	cosphirespt_eta->Write();
	cosphirespt_gamma->Write();
	cosphirespt_gamma_mm->Write();
	cosphirespt_eta_mm->Write();
	cosphirespt_pi0_mm->Write();
	phi2D_pi0->Write();
	phi2D_eta->Write();
	phi2D_gamma->Write();
	pt2D_pi0->Write();
	pt2D_pi01->Write();
	pt2D_pi02->Write();
	pt2D_eta->Write();
	pt2D_gamma->Write();
	pt2D_eh_pi0->Write();
	pt2D_eh_pi01->Write();
	pt2D_eh_pi02->Write();
	pt2D_eh_eta->Write();
	pt2D_eh_gamma->Write();
	comp1->Write("Pi0_Comp");
	comp2->Write("Eta_Comp");
	comp3->Write("Gamma_Comp");
	comp4->Write("Pi0Gamma_Comp");
	comp5->Write("EtaGamma_Comp");
	f.Close();
    }

    calcEff(pt_ni,pt);
    calcEff(pt_pi0_nw_ni,pt_pi0_nw);
    calcEff(pt_eta_nw_ni,pt_eta_nw);
    calcEff(pt_gamma_nw_ni,pt_gamma_nw);

    calcEff1(dca_ni,dca);
    calcEff1(dca_pi0_nw_ni,dca_pi0_nw);
    calcEff1(dca_eta_nw_ni,dca_eta_nw);
    calcEff1(dca_gamma_nw_ni,dca_gamma_nw);
   
    calcEff(phi_ni,phi);
    calcEff(phi_pi0_nw_ni,phi_pi0_nw);
    calcEff(phi_eta_nw_ni,phi_eta_nw);
    calcEff(phi_gamma_nw_ni,phi_gamma_nw);

    calcEff(eta_ni,eta);
    calcEff(eta_pi0_nw_ni,eta_pi0_nw);
    calcEff(eta_eta_nw_ni,eta_eta_nw);
    calcEff(eta_gamma_nw_ni,eta_gamma_nw);

    calcEff(vz_ni,vz);
    calcEff(vz_pi0_nw_ni,vz_pi0_nw);
    calcEff(vz_eta_nw_ni,vz_eta_nw);
    calcEff(vz_gamma_nw_ni,vz_gamma_nw);
 


    pt_ni->GetYaxis()->SetRangeUser(0,1);
    pt_ni->GetYaxis()->SetTitle("Isolation Efficiency"); 
    pt_ni->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");  
    comp_e->GetYaxis()->SetTitle("Isolation Efficiency"); 
    comp_e->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");  
    pt_ni->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");  
    dca_ni->GetYaxis()->SetRangeUser(0,1.4);
    dca_ni->GetXaxis()->SetRangeUser(-4,-1);
    dca_ni->GetYaxis()->SetTitle("Isolation Efficiency"); 
    dca_ni->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");  

    phi_ni->GetYaxis()->SetRangeUser(0,1);
    phi_ni->GetYaxis()->SetTitle("Isolation Efficiency"); 
    phi_ni->GetXaxis()->SetTitle("#phi [rad]");  
    eta_ni->GetYaxis()->SetRangeUser(0,1);
    eta_ni->GetYaxis()->SetTitle("Isolation Efficiency"); 
    eta_ni->GetXaxis()->SetTitle("#eta");  
    vz_ni->GetYaxis()->SetRangeUser(0,1);
    vz_ni->GetYaxis()->SetTitle("Isolation Efficiency"); 
    vz_ni->GetXaxis()->SetTitle("Vertex #it{z} [cm]");  
  
    TLegend *leg5 = new TLegend(0.2,0.75,0.5,0.92);
    leg5->AddEntry(pt_ni,"Single Electron","PE");
    leg5->AddEntry(pt_pi0_nw_ni,"#pi^{0} Dalitz Decay","PE");
    leg5->AddEntry(pt_eta_nw_ni,"#eta Dalitz Decay","PE");	
    leg5->AddEntry(pt_gamma_nw_ni,"#gamma","PE");
    //leg5->AddEntry(comp,"Photonic Weighted Ave. ","PE");

    TCanvas *ciso = new TCanvas("ciso","iso eff.");
    //pt_ni->GetYaxis()->SetRangeUser(0,1.5);
    //pt_ni->Draw("PE");
    //pt_pi0_nw_ni->Draw("same PE");
    //pt_eta_nw_ni->Draw("same PE");
    //pt_gamma_nw_ni->Draw("same PE");
    comp_e->GetYaxis()->SetRangeUser(0,1.5);
    comp_e->Draw("PE");
    comp_pi0->Draw("same PE");
    comp_eta->Draw("same PE");
    comp_gamma->Draw("same PE");
    comp->Draw("same PE");
    leg5->Draw("same");
    TF1 *line = new TF1("line","1",0,100);
    line->SetLineStyle(7);
    line->Draw("same");
    TCanvas *ciso1 = new TCanvas("ciso1","iso eff.1");
    phi_ni->Draw("PE");
    phi_pi0_nw_ni->Draw("same PE");
    phi_eta_nw_ni->Draw("same PE");
    phi_gamma_nw_ni->Draw("same PE");   
    TCanvas *ciso2 = new TCanvas("ciso2","iso eff.2");
    eta_ni->Draw("PE");
    eta_pi0_nw_ni->Draw("same PE");
    eta_eta_nw_ni->Draw("same PE");
    eta_gamma_nw_ni->Draw("same PE");   
    TCanvas *ciso3 = new TCanvas("ciso3","iso eff.3");
    vz_ni->Draw("PE");
    vz_pi0_nw_ni->Draw("same PE");
    vz_eta_nw_ni->Draw("same PE");
    vz_gamma_nw_ni->Draw("same PE");   
    TLatex lat1; 
    TCanvas *ciso33 = new TCanvas("ciso33","iso eff.4");
    dca_ni->Draw("PE");
    dca_pi0_nw_ni->Draw("same PE");
    dca_eta_nw_ni->Draw("same PE");
    dca_gamma_nw_ni->Draw("same PE");   
    leg5->Draw("same");
    lat1.DrawLatex(-2.6,1.18,label);
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
    double low = 2.0;
    double high = 2.5;
    h1->GetYaxis()->SetRangeUser(low,high);   
    hx =(TH1F*)h1->ProjectionX();


    pt_eh_pi0 =(TH1F*)dcapt_eh_pi0->ProjectionY();  
    pt_eh_eta =(TH1F*)dcapt_eh_eta->ProjectionY(); 
    pt_eh_pi0_gamma =(TH1F*)dcapt_eh_pi0_gamma->ProjectionY();  
    pt_eh_eta_gamma =(TH1F*)dcapt_eh_eta_gamma->ProjectionY(); 
    pt_eh_gamma =(TH1F*)dcapt_eh_gamma->ProjectionY(); 


//================Set Ragne
    dcapt_eh_pi0->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_eta->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_pi0_gamma->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_eta_gamma->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_eh_gamma->GetYaxis()->SetRangeUser(low,high);
    dcapt_all->GetYaxis()->SetRangeUser(low,high);
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
    dca_all_m1 =(TH1F*)dcapt_all_m1->ProjectionX();
    dca_all_m4 =(TH1F*)dcapt_all_m4->ProjectionX();  
    dca_eta =(TH1F*)dcapt_eta->ProjectionX();     
    dca_pi0 =(TH1F*)dcapt_pi0->ProjectionX(); 
    dca_eta_gamma =(TH1F*)dcapt_eta_gamma->ProjectionX();     
    dca_pi0_gamma =(TH1F*)dcapt_pi0_gamma->ProjectionX();  
    dca_gamma =(TH1F*)dcapt_gamma->ProjectionX();  
 
    dca_eta_nw =(TH1F*)dcapt_eta_nw->ProjectionX();     
    dca_pi0_nw =(TH1F*)dcapt_pi0_nw->ProjectionX(); 
    dca_eta_gamma_nw =(TH1F*)dcapt_eta_gamma_nw->ProjectionX();     
    dca_pi0_gamma_nw =(TH1F*)dcapt_pi0_gamma_nw->ProjectionX();  
    dca_gamma_nw =(TH1F*)dcapt_gamma_nw->ProjectionX();     
  
    norm6(dca_all);
    norm6(dca_all_nw);
    norm6(dca_all_m1);
    norm6(dca_all_m4);
    norm6(dca_pi0);
    norm6(dca_eta);
    norm6(dca_pi0_gamma);
    norm6(dca_eta_gamma);
    norm6(dca_gamma);
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
  
    
    TCanvas *c2D1 = new TCanvas ("c2D1","pi0 2D ",1200,500);
    c2D1->Divide(2,1);
    norm2D(dcapt_pi0_low);
    norm2D(dcapt_pi0_high);
    c2D1->cd(1);
    dcapt_pi0_low->DrawClone("COLZ");
    c2D1->cd(2);
    dcapt_pi0_high->DrawClone("COLZ");
    TCanvas *c2D2 = new TCanvas ("c2D2","eta 2D ",1200,500);
    c2D2->Divide(2,1);
    norm2D(dcapt_eta_low);
    norm2D(dcapt_eta_high);      
    c2D2->cd(1);
    dcapt_eta_low->DrawClone("COLZ");
    c2D2->cd(2);
    dcapt_eta_high->DrawClone("COLZ");
    TCanvas *c2D3 = new TCanvas ("c2D3","gamma 2D ",1200,500);
    c2D3->Divide(2,1);
    norm2D(dcapt_gamma_low);
    norm2D(dcapt_gamma_high);      
    c2D3->cd(1);
    dcapt_gamma_low->DrawClone("COLZ");
    c2D3->cd(2);
    dcapt_gamma_high->DrawClone("COLZ");
    dcapt_pi0_low->GetYaxis()->SetRangeUser(0,1);
    dcapt_pi0_high->GetYaxis()->SetRangeUser(0,1);
    dcapt_eta_low->GetYaxis()->SetRangeUser(0,1);
    dcapt_eta_high->GetYaxis()->SetRangeUser(0,1);
    dcapt_gamma_low->GetYaxis()->SetRangeUser(0,1);
    dcapt_gamma_high->GetYaxis()->SetRangeUser(0,1);
    dcapt_pi0_low_x = (TH1F*)dcapt_pi0_low->ProjectionX();
    dcapt_pi0_high_x = (TH1F*)dcapt_pi0_high->ProjectionX();
    dcapt_eta_low_x = (TH1F*)dcapt_eta_low->ProjectionX();
    dcapt_eta_high_x = (TH1F*)dcapt_eta_high->ProjectionX();
    dcapt_gamma_low_x = (TH1F*)dcapt_gamma_low->ProjectionX();
    dcapt_gamma_high_x = (TH1F*)dcapt_gamma_high->ProjectionX();
    dcapt_pi0_high_x->SetLineColor(kRed);
    dcapt_pi0_high_x->SetMarkerColor(kRed);
    dcapt_eta_high_x->SetLineColor(kRed);
    dcapt_eta_high_x->SetMarkerColor(kRed);
    dcapt_gamma_high_x->SetLineColor(kRed);
    dcapt_gamma_high_x->SetMarkerColor(kRed);
    norm5(dcapt_pi0_low_x);
    norm5(dcapt_pi0_high_x);
    norm5(dcapt_eta_low_x);
    norm5(dcapt_eta_high_x);
    norm5(dcapt_gamma_low_x);
    norm5(dcapt_gamma_high_x);

    TCanvas *c2D4 = new TCanvas ("c2D4","all project ",1600,500);
    c2D4->Divide(3,1);
    c2D4->cd(1);
    dcapt_pi0_low_x->Draw("same PE");
    dcapt_pi0_high_x->Draw("same PE");
    c2D4->cd(2);
    dcapt_eta_low_x->Draw("same PE");
    dcapt_eta_high_x->Draw("same PE");
    c2D4->cd(3);
    dcapt_gamma_low_x->Draw("same PE");
    dcapt_gamma_high_x->Draw("same PE");

    TCanvas *c1 = new TCanvas ("c1","dca single e ");

    dca_gamma->Draw("pe");
    dca_pi0->Draw("same pe");
    dca_eta->Draw("same pe");
    dca_gamma_nw->Draw("same hist");
    dca_pi0_nw->Draw("same hist");
    dca_eta_nw->Draw("same hist");
    TCanvas *c12 = new TCanvas ("c12","all dca single e ");
    dca_all->Draw("same pe");
    dca_all_nw->Draw("same hist");
 

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
    double high1=2.5;
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
    mass_1_x->SetMarkerColor(kRed);    
    mass_1_x->Rebin(5);
    h111_1_x->Rebin(5);
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
    h->Rebin(20);
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
    h->Rebin(20);
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
    h->Rebin(20);
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
	if(norm1>0)h->SetBinContent(i,temp/norm1*h->GetBinCenter(i)*2*TMath::Pi()*width);
	if(norm1>0)h->SetBinError(i,err/norm1*h->GetBinCenter(i)*2*TMath::Pi()*width);
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
void calcEff(TH1F* h_ni,TH1F* h){
    for(int i=1; i<h_ni->GetNbinsX()+1;i++){
	double temp2 = h->GetBinContent(i);
	double temp1 = h_ni->GetBinContent(i);
	if(temp1>0 && temp2>0){
	    h_ni->SetBinContent(i,temp2/temp1);
	    double temp = temp1-temp2;
	    h_ni->SetBinError(i,sqrt(temp/temp1/temp1*temp/temp1/temp1*temp2 + temp2/temp1/temp1*temp2/temp1/temp1*temp));
	}else{
	    h_ni->SetBinContent(i,0);	
	    h_ni->SetBinError(i,0);
	}
    }
}
void calcEff1(TH1F* h_ni,TH1F* h){
    h_ni->Rebin(20);
    h->Rebin(20);
    for(int i=1; i<h_ni->GetNbinsX()+1;i++){
	double temp2 = h->GetBinContent(i);
	double temp1 = h_ni->GetBinContent(i);
	if(temp1>0 && temp2>0){
	    h_ni->SetBinContent(i,temp2/temp1);
	    double temp = temp1-temp2;
	    h_ni->SetBinError(i,sqrt(temp/temp1/temp1*temp/temp1/temp1*temp2 + temp2/temp1/temp1*temp2/temp1/temp1*temp));
	}else{
	    h_ni->SetBinContent(i,0);	
	    h_ni->SetBinError(i,0);
	}
    }
}
void setErr(TH1F* h){
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	h->SetBinError(i,0.00000001);
    }
}
