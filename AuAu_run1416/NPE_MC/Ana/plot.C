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
void plot(int save = 0, int weight_data=1){ //weight only for phoE pair comp. and reweight for weight.C, and if doing other comp. integrated over pt
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(4);  
//////////////////////////////////////////////////////////////////
    double offset=400*3.5;
    TF1 *ffit = new TF1("ffit",func2,0.6,8.5,6); 
    TF1 *fgamma = new TF1("fgamma",func1,0,15,3);
    TF1 *fpi = new TF1("fpi",func,0,15,3);
    TF1 *ffitgamma = new TF1("ffitgamma",func1,0,15,3);
    TF1 *ffitpi = new TF1("ffitpi",func,0,15,3);

    fpi->SetParameter(0,1.44381e+04);
    fpi->SetParameter(1,9.18928e-01);
    fpi->SetParameter(2,1.10008e-01);
    fgamma->SetParameter(0,7.38384e+08*1000);
    fgamma->SetParameter(1,8.73512e-01);
    fgamma->SetParameter(2,9.10666e-03);

    ffit->SetParameter(0,1.44381e+04);
    ffit->SetParameter(1,9.18928e-01);
    ffit->SetParameter(2,1.10008e-01);
    ffit->SetParameter(3,7.38384e+08);
    ffit->SetParameter(4,8.73512e-01);
    ffit->SetParameter(5,9.10666e-03);
    ffit->SetParLimits(0,0,1E9);
    ffit->SetParLimits(1,9.18928e-01,9.18928e-01);
    ffit->SetParLimits(2,1.10008e-01,1.10008e-01);
    ffit->SetParLimits(3,1,1E9);
    ffit->SetParLimits(4,8.73512e-01,8.73512e-01);
    ffit->SetParLimits(5,9.10666e-03,9.10666e-03);

    
//////////////////////////////////////////////////////////////////
    TFile *fi = new TFile("root/Pi0_Gamma_Ratio.root");
    ratio = (TH1F*) fi->Get("ratio");
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};

    TH1F *wweight = new TH1F("wweight","",numPtBins,binning);
    for(int i = 1; i < 10;i++){
	wweight->SetBinContent(i,1/fpi->Eval(wweight->GetBinLowEdge(i)));
    }
    TH1F *comp_gamma =  new TH1F("comp_gamma","comp_gamma",numPtBins,binning);
    TH1F *comp_pi0  =new TH1F("comp_pi0","comp_pi0",numPtBins,binning);
    TH1F *comp_eta =  new TH1F("comp_eta","comp_eta",numPtBins,binning);
    TH1F *comp_pi0_gamma  =new TH1F("comp_pi0_gamma","comp_pi0_gamma",numPtBins,binning);
    TH1F *comp_eta_gamma =  new TH1F("comp_eta_gamma","comp_eta_gamma",numPtBins,binning);
    TH1F *phi_pi0 = new TH1F("phi_pi0","phi_pi0",5000,-1,1);
    if(save){	
	TH1F* write_gamma = new TH1F("write_gamma","write_gamma",200,0,20);
	TH1F* write_pi0 = new TH1F("write_pi0","write_pi0",200,0,20);
	TH1F* write_eh_gamma = new TH1F("write_eh_gamma","write_eh_gamma",200,0,20);
	TH1F* write_eh_pi0 = new TH1F("write_eh_pi0","write_eh_pi0",200,0,20);
	char dFile[500];
	char dFile1[500];
	sprintf(dFile,"All_Decays_newiso.root");
	TFile *f_D = new TFile(dFile);
	sprintf(dFile1,"MC.root");
	TFile *f_D1 = new TFile(dFile1);
	TChain *ch1 = f_D->Get("Signal_tree");
	TChain *ch11 = f_D1->Get("EH");
	TChain *ch2 = f_D->Get("Gen_tree");
	char dFile1[500];
	sprintf(dFile1,"../../NPE_Ana/production/NPE_Tuples_TuneA8.root");
	TFile *f_D1 = new TFile(dFile1);
	ch3 = (TChain*)f_D1->Get("PhoE");
	//TChain *ch3 = new TChain("PhoE");                                                                                   
	//for(int i=0;i<3351;i++){                                                                   
	    //sprintf(dFile,"../../NPE_Ana/production/FF2F91F7930C97E22D9CA3C2E86BBE66_%i.root",i); 
	    //ch3->AddFile(dFile);                                                                 
	    //}  

	char dFile2[500];
	sprintf(dFile2,"../root/Bplus_521_kunsu.root");
	TFile *f_D2 = new TFile(dFile2);
	ch4 = (TChain*)f_D2->Get("Tree");


	const int nbinDca = 82;
	const double binDca[nbinDca+1] = {-0.20,-0.15,-0.11,-0.08,-0.07,-0.062,-0.054,-0.046,-0.042,-0.038,-0.034,-0.03,-0.027,-0.024,-0.021,-0.019,-0.017,-0.015,-0.013,-0.012,-0.011,-0.01,-0.0095,-0.009,-0.0085,-0.008,-0.0075,-0.007,-0.0065,-0.006,-0.0055,-0.005,-0.0045,-0.004,-0.0035,-0.003,-0.0025,-0.002,-0.0015,-0.001,-0.0005,0,0.0005,0.001,0.0015,0.002,0.0025,0.003,0.0035,0.004,0.0045,0.005,0.0055,0.006,0.0065,0.007,0.0075,0.008,0.0085,0.009,0.0095,0.01,0.011,0.012,0.013,0.015,0.017,0.019,0.021,0.024,0.027,0.03,0.034,0.038,0.042,0.046,0.054,0.062,0.07,0.08,0.11,0.15,0.2};
	const int nbinPt = 200;
	double binPt[nbinPt+1];
	for(int i=0;i<nbinPt+1;i++){
	    binPt[i]=i*(20./nbinPt);
	}  //nbinDca,binDca,nbinPt,binPt
	TH2F *dcapt_fit = new TH2F("dcapt_fit","dcapt_fit",220,-0.11,0.11,85,0,8.5);dcapt_fit->Sumw2();//nbinDca,binDca,nbinPt,binPt
	TH2F *dcapt_fit_b = new TH2F("dcapt_fit_b","dcapt_fit_b",220,-0.11,0.11,85,0,8.5);dcapt_fit->Sumw2();//nbinDca,binDca,nbinPt,binPt
	TH2F *dcapt_all = new TH2F("dcapt_all","dcapt_all",200,-0.1,0.1,85,0,8.5);dcapt_all->Sumw2();
	TH2F *dcapt_all_iso = new TH2F("dcapt_all_iso","dcapt_all_iso",10,0,10,85,0,8.5);dcapt_all_iso->Sumw2();
	TH2F *dcapt_all_noiso = new TH2F("dcapt_all_noiso","dcapt_all_noiso",10,0,10,85,0,8.5);dcapt_all_noiso->Sumw2();
	TH2F *dcapt = new TH2F("dcapt","dcapt",200,-0.1,0.1,85,0,8.5);dcapt->Sumw2();
	TH2F *dcapt_iso = new TH2F("dcapt_iso","dcapt_iso",10,0,10,85,0,8.5);dcapt_iso->Sumw2();
	TH2F *dcapt_noiso = new TH2F("dcapt_noiso","dcapt_noiso",10,0,10,85,0,8.5);dcapt_noiso->Sumw2();
	TH2F *dcapt_eta = new TH2F("dcapt_eta","dcapt_eta",200,-0.1,0.1,85,0,8.5);dcapt_eta->Sumw2();
	TH2F *dcapt_pi0 = new TH2F("dcapt_pi0","dcapt_pi0",200,-0.1,0.1,85,0,8.5);dcapt_pi0->Sumw2();
	TH2F *dcapt_pi0_gamma = new TH2F("dcapt_pi0_gamma","dcapt_pi0_gamma",200,-0.1,0.1,85,0,8.5);dcapt_pi0_gamma->Sumw2();
	TH2F *dcapt_eta_gamma = new TH2F("dcapt_eta_gamma","dcapt_eta_gamma",200,-0.1,0.1,85,0,8.5);dcapt_eta_gamma->Sumw2();
	TH2F *dcapt_gamma = new TH2F("dcapt_gamma","dcapt_gamma",200,-0.1,0.1,85,0,8.5);dcapt_gamma->Sumw2();
	TH2F *dcapt_eh_gamma = new TH2F("dcapt_eh_gamma","dcapt_eh_gamma",200,-0.1,0.1,85,0,8.5);dcapt_eh_gamma->Sumw2();
	TH2F *dcapt_eh_eta = new TH2F("dcapt_eh_eta","dcapt_eh_eta",200,-0.1,0.1,85,0,8.5);dcapt_eh_eta->Sumw2();
	TH2F *dcapt_eh_pi0 = new TH2F("dcapt_eh_pi0","dcapt_eh_pi0",200,-0.1,0.1,85,0,8.5);dcapt_eh_pi0->Sumw2();
	TH2F *dcapt_eh_eta_gamma = new TH2F("dcapt_eh_eta_gamma","dcapt_eh_eta_gamma",200,-0.1,0.1,85,0,8.5);dcapt_eh_eta_gamma->Sumw2();
	TH2F *dcapt_eh_pi0_gamma = new TH2F("dcapt_eh_pi0_gamma","dcapt_eh_pi0_gamma",200,-0.1,0.1,85,0,8.5);dcapt_eh_pi0_gamma->Sumw2();

	TH2F *dcapt_eh_all = new TH2F("dcapt_eh_all","dcapt_eh_all",200,-0.1,0.1,85,0,8.5);dcapt_eh_all->Sumw2();
	TH2F *decayR = new TH2F("decayR","decayR",200,0,200,1000,1,20);decayR->Sumw2();
	TH2F *h1 = new TH2F("h1","h1",200,-0.1,0.1,85,0,8.5);
	TH2F *h2 = new TH2F("h2","h2",200,-0.1,0.1,85,0,8.5);
	TH2F *h11 = new TH2F("h11","h11",200,-0.1,0.1,1000,1,20);
	TH2F *h22 = new TH2F("h22","h22",200,-0.1,0.1,1000,1,20);
	TH2F *h111 = new TH2F("h111","h111",1000,0,0.3,200,0,20);
	TH2F *h222 = new TH2F("h222","h222",1000,0,0.3,200,0,20);
	TH2F *mass_all = new TH2F("mass_all","mass_all",1000,0,0.3,200,0,20);mass_all->Sumw2();
	TH1F *mass_eta = new TH1F("mass_eta","mass_eta",1000,0,0.3);mass_eta->Sumw2();
	TH1F *mass_pi0 = new TH1F("mass_pi0","mass_pi0",1000,0,0.3);mass_pi0->Sumw2();
	TH1F *mass_eta_gamma = new TH1F("mass_eta_gamma","mass_eta_gamma",1000,0,0.3);mass_eta_gamma->Sumw2();
	TH1F *mass_pi0_gamma = new TH1F("mass_pi0_gamma","mass_pi0_gamma",1000,0,0.3);mass_pi0_gamma->Sumw2();
	TH1F *mass_gamma = new TH1F("mass_gamma","mass_gamma",1000,0,0.3);mass_gamma->Sumw2();
	TH1F *pair_dca = new TH1F("pair_dca","pair_dca",1000,0,1);pair_dca->Sumw2();
	TH1F *pair_dca1 = new TH1F("pair_dca1","pair_dca1",1000,0,1);pair_dca1->Sumw2();
	TH1F *pair_dca2 = new TH1F("pair_dca2","pair_dca2",1000,0,1);pair_dca2->Sumw2();
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
	float s_cen;
	float s_parentphi;
	ch2->SetBranchAddress("gen_eta",&s_eta);	
	ch2->SetBranchAddress("gen_id",&s_id);
	ch2->SetBranchAddress("gen_pt",&s_pt);
	ch2->SetBranchAddress("gen_head",&s_head);
	ch2->SetBranchAddress("gen_parentid",&s_parentid);
	ch2->SetBranchAddress("gen_gparentid",&s_gparentid);
	ch2->SetBranchAddress("gen_ggparentid",&s_ggparentid);
	int num_eta = 349271;//0;//750131;//0;
	int num_pi0 = 596613;//596585;//0;//1279291;//0;
	int num_gamma = 92755;//;//0;//150913;//0;	
	int num_e = 1288444;//0;//1840210;//0;
	
	/*for(int i =0;i<ch2->GetEntries();i++){
	    ch2->GetEntry(i);
	    if(i%1000000==0)cout << "on " << i << " of " << ch2->GetEntries() << endl;
	    //if(!(s_id==2||s_id==3))continue;
	    if((fabs(s_eta)>0.7))continue;
	    if(s_id==17)num_eta++;
	    if(s_id==7)num_pi0++;
	    if(s_id==1 && s_head==1)num_gamma++;
	    if((s_id==2||s_id==3) && s_parentid==0)num_e++;
	    }
	*/
	cout << "Will weight w.r.t. pi0 yield " << endl;
	cout << "Number of pi0s produced " << num_pi0 <<" " <<  endl;
	cout << "Number of etas produced " << num_eta <<" " << endl;
	cout << "Number of direct gammas produced " << num_gamma <<" " << endl;
	cout << "Number of direct electrons produced " << num_e <<" " << endl;
	ch1->SetBranchAddress("sig_pt",&s_pt);
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
	    if(i%1000000==0)cout << "on " << i << " of " << ch1->GetEntries() << endl;
	    if(!(s_id==3 || s_id==2))continue;
	    if(s_pt<0.6)continue;
	    if(s_hft<1)continue;    
	    double ww = 1;
	    double ww2 =1;
	    double prox = 0;
	    if(s_head == 7 && s_gparentid==0){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		prox = s_parentpt;
		if(s_parentpt<0.35)s_parentpt=0.35;	
		if(weight_data)ww = fpi->Eval(s_parentpt);
		if(s_parentpt>0.4)write_pi0->Fill(prox,ww);
		ww2*= offset*0.8*num_gamma/num_pi0 * 1/2.64366201806170466e+02;
		
	    }
	    if(s_head == 17 && s_gparentid==0){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		if(s_parentpt<0.35)s_parentpt=0.35;
		ww = fpi->Eval(s_parentpt);//if(weight_data)
		ww2*= offset*0.2*num_gamma/num_eta*0.45* 0.0069/0.01174 * 1/2.64366201806170466e+02;// * 0.0069/0.0174
		//ww*= num_pi0/num_eta;
	    }
	    if(s_head == 1 && s_gparentid==0){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		prox = s_parentpt;
		if(s_parentpt<1.17606)s_parentpt=1.17606;
		int bin = ratio->FindBin(s_parentpt);
		ww = fgamma->Eval(s_parentpt);
		if(s_parentpt>1.5)write_gamma->Fill(prox,ww);
		ww2*= 1;//num_pi0/num_gamma;   
	    }
	    int binn = wweight->FindBin(s_pt);
	    if(!weight_data)ww2*= wweight->GetBinContent(binn);

	    if(s_parentid==0){
		dcapt->Fill(s_dcaxy,s_pt);
		if(s_iso==1)dcapt_iso->Fill(s_cen+0.3,s_pt);
		dcapt_noiso->Fill(s_cen+0.3,s_pt);
	    }
	   
	    if(s_head==7 && s_parentid==7)dcapt_pi0->Fill(s_dcaxy,s_pt,ww2*ww);
	    phi_pi0->Fill((s_phi-s_parentphi),ww*ww);
	    if(s_head==17 && s_parentid==17)dcapt_eta->Fill(s_dcaxy,s_pt,ww2*ww);
	    if(s_head==7|| s_head==17){
		dcapt_all->Fill(s_dcaxy,s_pt,ww2*ww);
		dcapt_fit->Fill(s_dcaxy,s_pt,ww2);
		if(s_iso==1)dcapt_all_iso->Fill(s_cen+0.3,s_pt);
		dcapt_all_noiso->Fill(s_cen+0.3,s_pt);
	    }
	    if(s_head==1){
		dcapt_gamma->Fill(s_dcaxy,s_pt,ww2*ww);
		dcapt_eta_gamma->Fill(s_dcaxy,s_pt,ww2*ww*0.2*1/(1.21361-1));//if(s_head==17 && s_parentid==1)
		dcapt_pi0_gamma->Fill(s_dcaxy,s_pt,ww2*ww*(1-0.2)*1/(1.21361-1));//if(s_head==7 && s_parentid==1)

		dcapt_all->Fill(s_dcaxy,s_pt,ww2*ww*(1+1/(1.21361-1)));
		dcapt_fit->Fill(s_dcaxy,s_pt,ww2*(1+1/(1.21361-1)));
		if(s_iso==1)dcapt_all_iso->Fill(s_cen+0.3,s_pt,(1+1/(1.21361-1)));
		dcapt_all_noiso->Fill(s_cen+0.3,s_pt,(1+1/(1.21361-1)));
	    }


	}
	float s_dr;
	float s_m;
	float s_c1;	
	float s_c2;
	float s_dca;
	float s_hft2;
	ch11->SetBranchAddress("eh_pt",&s_pt);
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

	    double ww = 1;
	    double ww2 = 1;	    
	    if(s_head == 7){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		if(s_parentpt<0.35)s_parentpt=0.35;
		ww = fpi->Eval(s_parentpt);
		ww2 *= offset*0.8*num_gamma/num_pi0 * 1/2.64366201806170466e+02;//num_gamma/num_pi0;
	    }
	    if(s_head == 17){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;
		if(s_parentpt<0.35)s_parentpt=0.35;
		ww = fpi->Eval(s_parentpt);
		ww2*= offset*0.2*num_gamma/num_eta*0.45* 0.0069/0.01174 * 1/2.64366201806170466e+02;
	    }
	    if(s_head == 1){
		if(s_parentid==s_head)s_parentpt = s_parentpt;
		else if(s_gparentid==s_head)s_parentpt = s_gparentpt;
		else if(s_ggparentid==s_head)s_parentpt = s_ggparentpt;	
		if(s_parentpt<1.17606)s_parentpt=1.17606;
		int bin = ratio->FindBin(s_parentpt);
		ww = fgamma->Eval(s_parentpt); 
  		ww2*= 1;//num_pi0/num_gamma;
		//if(ratio->GetBinContent(bin)>0)ww2*= 1/ratio->GetBinContent(bin);
	    }
	    int binn = wweight->FindBin(s_pt);
	    if(!weight_data)ww2*= wweight->GetBinContent(binn);
	    if(s_head==17||s_head==1 ||s_head==7)pair_dca->Fill(s_dca,ww2);
	    if(s_hft<1)continue;    
	    if(s_head==17||s_head==1 ||s_head==7)pair_dca1->Fill(s_dca,ww2);
	    if(s_hft<1 || s_hft2<1)continue;    
	    if(s_head==17||s_head==7){
		if(s_pt>2 && s_pt<2.5)decayR->Fill(s_head,s_dr,ww2*ww);
		pair_dca2->Fill(s_dca,ww2);
	    }
	    if(s_head==1){
		if(s_pt>3 && s_pt<8.5)decayR->Fill(s_head,s_dr,ww2*ww*(1+1/(1.21361-1)));
		pair_dca2->Fill(s_dca,ww*ww2*(1+1/(1.21361-1)));
	    }
	    if(s_head==1){
		if(s_pt>0.6)mass_gamma->Fill(s_m,ww2*ww);	
		if(s_m<0.015)dcapt_eh_gamma->Fill(s_dcaxy,s_pt,ww2*ww);
		if(s_m<0.015)dcapt_eh_pi0_gamma->Fill(s_dcaxy,s_pt,ww2*ww*(1-0.2)*1/(1.21361-1));
		if(s_pt>0.6)mass_pi0_gamma->Fill(s_m,ww2*ww*(1-0.2)*1/1.21361);	
		if(s_m<0.015)dcapt_eh_eta_gamma->Fill(s_dcaxy,s_pt,ww2*ww*0.2*1/(1.21361-1));
		if(s_pt>0.6)mass_eta_gamma->Fill(s_m,ww2*ww*0.2*1/(1.21361-1));
	    }
	    if(s_head==7){
		if(s_parentid==7 || s_parentid==1){
		    if(s_m<0.015)dcapt_eh_pi0->Fill(s_dcaxy,s_pt,ww2*ww);
		    if(s_pt>0.6)mass_pi0->Fill(s_m,ww2*ww);	
		}
		if(s_parentid==1){
		    //if(s_m<0.015)dcapt_eh_pi0_gamma->Fill(s_dcaxy,s_pt,ww2*ww);
		    //if(s_pt>0.6)mass_pi0_gamma->Fill(s_m,ww2*ww);	
		}
	    }
	    if(s_head==17){
		if(s_parentid==17 || s_parentid==1){
		    if(s_m<0.015)dcapt_eh_eta->Fill(s_dcaxy,s_pt,ww2*ww);
		    if(s_pt>0.6)mass_eta->Fill(s_m,ww2*ww);
		}
		if(s_parentid==1){
		    //if(s_m<0.015)dcapt_eh_eta_gamma->Fill(s_dcaxy,s_pt,ww2*ww);
		    //if(s_pt>0.6)mass_eta_gamma->Fill(s_m,ww2*ww);
		}
	    }
	    if(s_head==17||s_head==7  ){
		if(s_m<0.015)dcapt_eh_all->Fill(s_dcaxy,s_pt,ww2*ww);
		if(s_m<0.015)mass_all->Fill(s_m,s_pt,ww*ww2);
	    }
	    if(s_head==1){
		if(s_m<0.015)dcapt_eh_all->Fill(s_dcaxy,s_pt,ww2*ww*(1+1/(1.21361-1)));
		if(s_m<0.015)mass_all->Fill(s_m,s_pt,ww*ww2*(1+1/(1.21361-1)));
	    }
	}
	double s_px;
	double s_py;
	ch4->SetBranchAddress("dPx",&s_px);
	ch4->SetBranchAddress("dPy",&s_py);
	ch4->SetBranchAddress("ddcaXY",&s_dcaxy);
	for(int i =0;i<ch11->GetEntries();i++){
	    ch11->GetEntry(i);
	    if(i%1000000==0)cout << "on " << i << " of " << ch11->GetEntries() << endl;;
	    dcapt_fit_b->Fill(sqrt(s_px*s_px+s_py*s_py),s_dcaxy);

	}

	ch3->Project("h1","probe_pt:probe_dca","probe_charge*tag_charge<0 && probe_pt>0.6  &&  probe_mva>0")  ;//&& abs(1/tag_beta-1)<0.025
	ch3->Project("h2","probe_pt:probe_dca","probe_charge*tag_charge>0 && probe_pt>0.6  &&  probe_mva>0")  ;
	ch3->Project("h11","pair_decayradius:probe_dca","probe_charge*tag_charge<0 &&probe_pt>2  && probe_pt<2.5  &&probe_mva>0")  ;
	ch3->Project("h22","pair_decayradius:probe_dca","probe_charge*tag_charge>0 && probe_pt>2  && probe_pt<2.5 &&probe_mva>0")  ;//&& probe_pt>2  && probe_pt<2.5  
	ch3->Project("h111","probe_pt:PhoE_M","probe_charge*tag_charge<0 && probe_mva>0");
	ch3->Project("h222","probe_pt:PhoE_M","probe_charge*tag_charge>0 && probe_mva>0");
	h1->Add(h2,-1);
	h11->Add(h22,-1);
	h111->Add(h222,-1);
	TCanvas *cdca = new TCanvas("cdca","");
	pair_dca->GetXaxis()->SetTitle("Pair DCA [cm]");
	pair_dca->GetYaxis()->SetTitle("A. U.");
	norm(pair_dca);
	norm(pair_dca1);
	norm(pair_dca2);
	pair_dca2->SetLineColor(kRed);
	pair_dca1->SetLineColor(kBlue);
	pair_dca->Draw();
	pair_dca1->Draw("same hist");
	pair_dca2->Draw("same hist");	
	TFile f("root/DCA_Shapes.root","RECREATE");
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
	dcapt_all->Write("dcapt_all");
	dcapt_fit->Write("dcapt_fit");
	dcapt_fit_b->Write("dcapt_fit_b");	
	dcapt_all_iso->Write("dcapt_all_iso");
	dcapt_all_noiso->Write("dcapt_all_noiso");	
	dcapt->Write("dcapt");
	dcapt_iso->Write("dcapt_iso");
	dcapt_noiso->Write("dcapt_noiso");
	write_pi0->Write("write_pi0");
	write_gamma->Write("write_gamma");
	h1->Write("h1");
	h11->Write("h11");
	h111->Write("h111");
	decayR->Write("decayR");
	mass_all->Write();
	mass_eta->Write();
	mass_pi0->Write();
	mass_gamma->Write();
	mass_pi0_gamma->Write();
	mass_eta_gamma->Write();
	f.Close();
	
    }
    if(save==0){
	TFile * f= new TFile("root/DCA_Shapes.root");
	dcapt_gamma=(TH2F*)f->Get("dcapt_gamma");
	dcapt_pi0=(TH2F*)f->Get("dcapt_pi0");
	dcapt_eta=(TH2F*)f->Get("dcapt_eta");
	dcapt_iso=(TH2F*)f->Get("dcapt_iso");
	dcapt_all_iso=(TH2F*)f->Get("dcapt_all_iso");
	dcapt_noiso=(TH2F*)f->Get("dcapt_noiso");
	dcapt_all_noiso=(TH2F*)f->Get("dcapt_all_noiso");
	dcapt_pi0_gamma=(TH2F*)f->Get("dcapt_pi0_gamma");
	dcapt_eta_gamma=(TH2F*)f->Get("dcapt_eta_gamma");
	dcapt_all=(TH2F*)f->Get("dcapt_all");
	dcapt=(TH2F*)f->Get("dcapt");
	dcapt_b=(TH2F*)f->Get("dcapt_fit_b");
	dcapt_eh_eta=(TH2F*)f->Get("dcapt_eh_eta");
	dcapt_eh_all=(TH2F*)f->Get("dcapt_eh_all");
	dcapt_eh_pi0=(TH2F*)f->Get("dcapt_eh_pi0");
	dcapt_eh_eta_gamma=(TH2F*)f->Get("dcapt_eh_eta_gamma");
	dcapt_eh_pi0_gamma=(TH2F*)f->Get("dcapt_eh_pi0_gamma");
	dcapt_eh_gamma=(TH2F*)f->Get("dcapt_eh_gamma");
	mass_gamma=(TH1F*)f->Get("mass_gamma");	
	mass_eta_gamma=(TH1F*)f->Get("mass_eta_gamma");	
	mass_pi_gamma=(TH1F*)f->Get("mass_pi0_gamma");	
	mass_eta=(TH1F*)f->Get("mass_eta");	
	mass_pi=(TH1F*)f->Get("mass_pi0");
	mass_all=(TH2F*)f->Get("mass_all");
	h1=(TH2F*)f->Get("h1");
	h11=(TH2F*)f->Get("h11");
	h111=(TH2F*)f->Get("h111");
	decayR=(TH2F*)f->Get("decayR");
    }
    cout << "Total gamma " << dcapt_gamma->Integral() << endl;
    cout << "Total reco gamma " << dcapt_gamma->GetEffectiveEntries() << endl;
    TF1 *fline = new TF1("fline","1",0,10);
    fline->SetLineStyle(7);
    mass_gamma->SetLineColor(kRed);
    mass_pi0->SetLineColor(kBlue);
    mass_eta->SetLineColor(kGreen-2);
    mass_pi0_gamma->SetLineColor(kCyan);
    mass_eta_gamma->SetLineColor(kGray+1);



    write_pi0->SetMarkerColor(kRed);
    write_gamma->SetMarkerColor(kRed); 
    write_pi0->SetMarkerStyle(22);
    write_gamma->SetMarkerStyle(22);   
    write_pi0->SetLineColor(kRed);
    write_gamma->SetLineColor(kRed);    
    mass_all->GetYaxis()->SetRangeUser(3,8.5);
    h111->GetYaxis()->SetRangeUser(3,8.5);    
    mass_all_x = (TH1F*) mass_all->ProjectionX();
    h111_x = (TH1F*) h111->ProjectionX();    
    mass_all_x->GetXaxis()->SetTitle("m(e^{+}e^{-}) [GeV]");
    mass_all_x->GetYaxis()->SetTitle("A. U.");
    mass_gamma->GetXaxis()->SetTitle("m(e^{+}e^{-}) [GeV]");
    mass_gamma->GetYaxis()->SetTitle("A. U.");
    TLatex lat;
    TCanvas *hmass = new TCanvas("hmass","");
    //h111);
    //norm(mass_all);
    norm(mass_pi0);
    norm(mass_eta);
    norm(mass_pi0_gamma);
    norm(mass_eta_gamma);
    norm(mass_gamma);
    h111_x->Rebin();
    mass_all_x->Rebin();
    mass_pi0->Rebin(10);
    mass_eta->Rebin(10);
    mass_pi0_gamma->Rebin(10);
    mass_eta_gamma->Rebin(10);
    mass_gamma->Rebin(10);

    TLegend *leg111 = new TLegend(0.75,0.7,0.9,0.9);
    leg111->AddEntry(mass_pi0,"#pi^{0}#rightarrow e","l");
    leg111->AddEntry(mass_eta,"#eta#rightarrow e","l");
    leg111->AddEntry(mass_pi0_gamma,"#pi^{0}#rightarrow #gamma#rightarrow e","l");
    leg111->AddEntry(mass_eta_gamma,"#eta#rightarrow #gamma#rightarrow e","l");
    leg111->AddEntry(mass_gamma,"#gamma#rightarrow e","l");



    mass_gamma->Draw("hist same");
    mass_pi0_gamma->Draw("hist same");
    mass_eta_gamma->Draw("hist same");
    mass_pi0->Draw("hist same");
    mass_eta->Draw("hist same");
    leg111->Draw("same");
    lat.DrawLatex(12,10e-2,"2.0<#it{p}_{T} [GeV]<8.5");
    TCanvas *hmass1 = new TCanvas("hmass1","");
    mass_all_x->GetXaxis()->SetRangeUser(0,0.015);
    norm(h111_x);
    norm(mass_all_x); 
    mass_all_x->SetMarkerColor(kRed);
    mass_all_x->SetLineColor(kRed);
    TLegend *leg3 = new TLegend(0.65,0.6,0.9,0.8);
    leg3->AddEntry(h111_x,"US-LS Data","PL");
    leg3->AddEntry(mass_all_x,"Weighted Sum","PL");


    mass_all_x->Draw("PE same");
    h111_x->Draw("PE  same");
    leg3->Draw("same");
    lat.DrawLatex(12,10e-2,"2.0<#it{p}_{T} [GeV]<2.5");
    hdr = (TH1F*) h11->ProjectionY();
    TCanvas *Dr = new TCanvas("Dr","");
    dr1 = (TH1F*)decayR->ProjectionY("dr1",1,2);
    dr2 = (TH1F*)decayR->ProjectionY("dr2",5,100);
    dr3 = (TH1F*)decayR->ProjectionY("dr3",1,150);
    dr1->SetLineColor(kRed);
    dr2->SetLineColor(kBlue);
    //dr3->Add(dr1);
    //dr3->Add(dr2);
    dr1->Rebin(10);
    dr2->Rebin(10);
    dr3->Rebin(10);
    hdr->Rebin(10);
  
    //norm(dr1);
    //norm(dr2);
    norm(dr3);
    norm(hdr);
    dr3->GetXaxis()->SetTitle("Decay Radius [cm]");
    dr3->GetYaxis()->SetTitle("A. U.");
    dr3->SetMarkerColor(kRed);
    dr3->SetLineColor(kRed);   
    dr3->Draw("PE same");
    //dr1->Draw("hist same");
    //dr2->Draw("hist same");
    hdr->Draw("PE same"); 
    leg3->Draw("same");
    lat.DrawLatex(12,10e-2,"2.0<#it{p}_{T} [GeV]<8.5");
    h1->SetLineColor(kMagenta);
    h1->SetMarkerColor(kMagenta);

    dcapt_gamma->SetLineColor(kRed);  
    dcapt_gamma->SetMarkerColor(kRed);  
    dcapt_eh_gamma->SetLineColor(kRed);  
    dcapt_eh_gamma->SetMarkerColor(kRed);  
    dcapt_pi0->SetLineColor(kBlue);  
    dcapt_pi0->SetMarkerColor(kBlue);  
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
 
    
    
    dcapt_all_iso->SetLineColor(kRed);
    dcapt_all_iso->SetMarkerColor(kRed);   
    
    // ========== PT plots 


    pt_eh_pi0 =(TH1F*)dcapt_eh_pi0->ProjectionY();
    pt_eh_eta =(TH1F*)dcapt_eh_eta->ProjectionY();
    pt_eh_pi0_gamma =(TH1F*)dcapt_eh_pi0_gamma->ProjectionY();
    pt_eh_eta_gamma =(TH1F*)dcapt_eh_eta_gamma->ProjectionY();
    pt_eh_all =(TH1F*)dcapt_eh_all->ProjectionY();
    pt_eh_gamma =(TH1F*)dcapt_eh_gamma->ProjectionY();
    pt_all =(TH1F*)dcapt_all->ProjectionY();
    pt =(TH1F*)dcapt->ProjectionY();



    pt_all_iso1 =(TH1F*)dcapt_all_iso->ProjectionY("_1",1,3);
    pt_all_iso1->SetName("pt_all_iso1");
    pt_iso1 =(TH1F*)dcapt_iso->ProjectionY("_11",1,3);
    pt_iso1->SetName("pt_iso1");
    pt_all_noiso1 =(TH1F*)dcapt_all_noiso->ProjectionY("_12",1,3);
    pt_all_noiso1->SetName("pt_all_noiso1");
    pt_noiso1 =(TH1F*)dcapt_noiso->ProjectionY("_112",1,3);
    pt_noiso1->SetName("pt_noiso1");

    pt_all_iso2 =(TH1F*)dcapt_all_iso->ProjectionY("_2",4,6);
    pt_all_iso2->SetName("pt_all_iso2");
    pt_iso2 =(TH1F*)dcapt_iso->ProjectionY("_21",4,6);
    pt_iso2->SetName("pt_iso2");
    pt_all_noiso2 =(TH1F*)dcapt_all_noiso->ProjectionY("_22",4,6);
    pt_all_noiso2->SetName("pt_all_noiso2");
    pt_noiso2 =(TH1F*)dcapt_noiso->ProjectionY("_212",4,6);
    pt_noiso2->SetName("pt_noiso2");
    pt_all_iso3 =(TH1F*)dcapt_all_iso->ProjectionY("_3",7,10);
    pt_all_iso3->SetName("pt_all_iso3");
    pt_iso3 =(TH1F*)dcapt_iso->ProjectionY("_31",7,10);
    pt_iso3->SetName("pt_iso3");
    pt_all_noiso3 =(TH1F*)dcapt_all_noiso->ProjectionY("_32",7,10);
    pt_all_noiso3->SetName("pt_all_noiso3");
    pt_noiso3 =(TH1F*)dcapt_noiso->ProjectionY("_312",7,10);
    pt_noiso3->SetName("pt_noiso3");


    pt_eta =(TH1F*)dcapt_eta->ProjectionY();
    pt_pi0 =(TH1F*)dcapt_pi0->ProjectionY();
    pt_eta_gamma =(TH1F*)dcapt_eta_gamma->ProjectionY();
    pt_pi0_gamma =(TH1F*)dcapt_pi0_gamma->ProjectionY();
    pt_gamma =(TH1F*)dcapt_gamma->ProjectionY();

    hy =(TH1F*)h1->ProjectionY();

    TCanvas *c232 = new TCanvas ("c232","iso eff");
    getEff1(pt_iso1,pt_noiso1);
    getEff1(pt_iso2,pt_noiso2);
    getEff1(pt_iso3,pt_noiso3);
    getEff1(pt_all_iso1,pt_all_noiso1);
    getEff1(pt_all_iso2,pt_all_noiso2);    
    getEff1(pt_all_iso3,pt_all_noiso3);
    pt_iso1->SetMarkerStyle(25);
    pt_all_iso1->SetMarkerStyle(25);
    pt_iso2->SetMarkerStyle(24);
    pt_all_iso2->SetMarkerStyle(24);
    pt_iso3->SetMarkerStyle(23);
    pt_all_iso3->SetMarkerStyle(23);
    TLegend *leg2 = new TLegend(0.65,0.7,0.9,0.9);
    leg2->AddEntry(pt_iso1,"Single e 50-80%","PL");
    leg2->AddEntry(pt_all_iso1,"Photonic e 50-80%","PL");
    leg2->AddEntry(pt_iso2,"Single e 20-50%","PL");
    leg2->AddEntry(pt_all_iso2,"Photonic e 20-50%","PL");
    leg2->AddEntry(pt_iso3,"Single e 0-20%","PL");
    leg2->AddEntry(pt_all_iso3,"Photonic e 0-20%","PL");


    pt_iso1->GetYaxis()->SetTitle("Isolation Efficiency");
    pt_iso1->GetXaxis()->SetTitle("#it{p}_{T}");
    pt_iso1->GetXaxis()->SetRangeUser(0.6,8.5);
    pt_iso1->GetYaxis()->SetRangeUser(0,1.6);
    pt_iso1->Draw("PE");
    pt_all_iso1->Draw("PE same");
    pt_iso2->Draw("PE same");
    pt_all_iso2->Draw("PE same");
    pt_iso3->Draw("PE same");
    pt_all_iso3->Draw("PE same");
    fline->Draw("same");
    leg2->Draw("same");
    TCanvas *c22 = new TCanvas ("c22","pt comp");
    for(int i = 1; i<numPtBins+1;i++){
	int loww = pt_all->FindBin(binning[i-1]);
	int highh = pt_all->FindBin(binning[i]);
	double temp1 = pt_all->Integral(loww,highh);
	double temp2 = pt_pi0->Integral(loww,highh);
	double temp3 = pt_eta->Integral(loww,highh);
	double temp22 = pt_pi0_gamma->Integral(loww,highh);
	double temp33 = pt_eta_gamma->Integral(loww,highh);	
	double temp4 = pt_gamma->Integral(loww,highh);
	
	if(temp1>0){
	    comp_pi0->SetBinContent(i,temp2/temp1);
	    comp_gamma->SetBinContent(i,(temp4)/temp1);
	    comp_eta->SetBinContent(i,temp3/temp1);
	    comp_pi0_gamma->SetBinContent(i,temp22/temp1);
	    comp_eta_gamma->SetBinContent(i,temp33/temp1);
	    comp_pi0->SetBinError(i,temp4/temp1*0.01);
	    comp_gamma->SetBinError(i,temp2/temp1*0.01);
	    comp_eta->SetBinError(i,temp3/temp1*0.01);
	    comp_eta_gamma->SetBinError(i,temp33/temp1*0.01);
	    comp_pi0_gamma->SetBinError(i,temp22/temp1*0.01);
	}
    }
    comp_gamma->SetMarkerColor(kRed);    
    comp_pi0->SetMarkerColor(kBlue); 
    comp_pi0_gamma->SetMarkerColor(kCyan); 
    comp_eta->SetMarkerColor(kGreen-2);
    comp_eta_gamma->SetMarkerColor(kGray+1);
    comp_gamma->SetMarkerStyle(8);    
    comp_pi0->SetMarkerStyle(22); 
    comp_pi0_gamma->SetMarkerStyle(23); 
    comp_eta->SetMarkerStyle(24);
    comp_eta_gamma->SetMarkerStyle(25);


    comp_gamma->SetLineColor(kRed);    
    comp_pi0->SetLineColor(kBlue); 
    comp_pi0_gamma->SetLineColor(kCyan); 
    comp_eta->SetLineColor(kGreen-2);
    comp_eta_gamma->SetLineColor(kGray+1);
    TLegend *leg11 = new TLegend(0.75,0.7,0.9,0.9);
    leg11->AddEntry(comp_pi0,"#pi^{0} Dalitz Decay");
    leg11->AddEntry(comp_eta,"#eta Dalitz Decay");
    leg11->AddEntry(comp_pi0_gamma,"#pi^{0}#rightarrow 2#gamma#rightarrow e");
    leg11->AddEntry(comp_eta_gamma,"#eta#rightarrow 2#gamma#rightarrow e");
    leg11->AddEntry(comp_gamma,"Direct #gamma#rightarrow e");
 
    TLegend *leg1 = new TLegend(0.75,0.7,0.9,0.9);
    leg1->AddEntry(hy,"UL-LS Data");
    leg1->AddEntry(comp_pi0,"#pi^{0}#rightarrow e^{+}e^{-}X");
    leg1->AddEntry(comp_eta,"#eta#rightarrow e^{+}e^{-}X");
    leg1->AddEntry(comp_pi0_gamma,"#pi^{0}#rightarrow #gamma#rightarrow e^{+}e^{-}");
    leg1->AddEntry(comp_eta_gamma,"#eta#rightarrow #gamma#rightarrow e^{+}e^{-}");
    leg1->AddEntry(comp_gamma,"#gamma#rightarrow e^{+}e^{-}");
    leg1->AddEntry(pt,"Weighted Sum");
    comp_gamma->GetYaxis()->SetRangeUser(0.,1.5);
    comp_gamma->GetYaxis()->SetTitle("Relative Photonic Electron");
    comp_gamma->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    comp_gamma->Draw("same pe");
    comp_pi0->Draw("same pe");
    comp_eta->Draw("same pe");
    comp_pi0_gamma->Draw("same pe");
    comp_eta_gamma->Draw("same pe");
    leg11->Draw("same");
    fline->Draw("same");
   
    //norm(pt);
    //norm(pt_gamma);
    //norm(pt_eta);
    //norm(pt_pi0_gamma);
    //norm(pt_eta_gamma);
    //norm(pt_pi0);
    //norm(pt_all);
    //norm(hy);
    //norm(pt_eh_gamma);
    //norm(pt_eh_eta);
    //norm(pt_eh_pi0);
    //norm(pt_eh_eta_gamma);
    //norm(pt_eh_pi0_gamma);
    //norm(pt_eh_all);   
    TCanvas *c2 = new TCanvas ("c2","pt single e");
    //pt->Draw("pe");
    pt_gamma->Draw("same pe");
    pt_all->Draw("same pe");
    pt_pi0->Draw("same pe");
    pt_eta->Draw("same pe");
    pt_pi0_gamma->Draw("same pe");
    pt_eta_gamma->Draw("same pe");
    //hy->Draw("same pe");   
    TCanvas *c5 = new TCanvas ("c5","phoe e");
    norm(pt_eh_gamma);
    norm(pt_eh_eta_gamma);
    norm(pt_eh_pi0_gamma);
    norm(pt_eh_pi0);
    norm(pt_eh_eta);   
    norm(pt_eh_all);  
    norm(hy);
    double scale = hy->GetBinContent(35)/pt_eh_all->GetBinContent(35);
    pt_eh_gamma->Scale(scale);
    pt_eh_eta_gamma->Scale(scale);
    pt_eh_pi0_gamma->Scale(scale);
    pt_eh_pi0->Scale(scale);
    pt_eh_eta->Scale(scale);   
    pt_eh_all->Scale(scale); 
    TH1F *ptrat = new TH1F("ptrat","ptrat",85,0,8.5);
    for(int i=1;i<pt_eh_all->GetNbinsX();i++){
	double temp1 = pt_eh_all->GetBinContent(i);
	double temp11 = pt_eh_all->GetBinError(i);
	double temp2 = hy->GetBinContent(i);
	double temp22 = hy->GetBinError(i);
	if(temp1>0 && temp2>0){
	    ptrat->SetBinContent(i,temp1/temp2);
	    ptrat->SetBinError(i,temp1/temp2*sqrt(temp11/temp1+temp22/temp2));	
	}else{
	    ptrat->SetBinContent(i,-1);
	    ptrat->SetBinError(i,0);
	}
    }
    TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
    pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.08);
    pad2->SetTopMargin(0.015);
    pad2->SetBottomMargin(0.5);  
    pad2->SetBorderMode(0);
    pad1->SetBorderMode(0);
    pad1->Draw();
    pad2->Draw(); 
    pad1->cd();  
    pt_eh_gamma->GetYaxis()->SetTitle("A. U.");
    pt_eh_gamma->Draw("same pe");
    pt_eh_all->Draw("same pe");
    pt_eh_pi0->Draw("same pe");
    pt_eh_eta->Draw("same pe");
    pt_eh_pi0_gamma->Draw("same pe");
    pt_eh_eta_gamma->Draw("same pe");
    hy->Draw("same pe");  
    leg1->Draw("same");

    pad2->cd();
    ptrat->GetXaxis()->SetTitle("p_{T} [GeV]");
    ptrat->GetYaxis()->SetTitle("Sum/Data");
    ptrat->SetTitle(0);
    ptrat->GetYaxis()->SetTitleSize(0.15);
    ptrat->GetYaxis()->SetLabelSize(0.1);
    ptrat->GetYaxis()->CenterTitle();
    ptrat->GetYaxis()->SetTitleOffset(0.3);
    ptrat->GetYaxis()->SetNdivisions(505);
    ptrat->GetYaxis()->SetRangeUser(0,3);
    ptrat->GetXaxis()->SetTitleSize(0.3);
    ptrat->GetXaxis()->SetLabelSize(0.15);  
    ptrat->GetXaxis()->SetTitleOffset(0.63);
    ptrat->Draw("PE");
    fline->Draw("same");
 
  // ========== DCA plots 
    double low = 2;
    double high = 2.5;
    h1->GetYaxis()->SetRangeUser(low,high);   
    hx =(TH1F*)h1->ProjectionX();
    dcapt->GetYaxis()->SetRangeUser(low,high);
    dcapt_fit_b->GetYaxis()->SetRangeUser(low,high);
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

    dca_eh_pi0 =(TH1F*)dcapt_eh_pi0->ProjectionX();  
    dca_eh_eta =(TH1F*)dcapt_eh_eta->ProjectionX(); 
    dca_eh_pi0_gamma =(TH1F*)dcapt_eh_pi0_gamma->ProjectionX();  
    dca_eh_eta_gamma =(TH1F*)dcapt_eh_eta_gamma->ProjectionX(); 
    dca_eh_all =(TH1F*)dcapt_eh_all->ProjectionX();  
    dca_eh_gamma =(TH1F*)dcapt_eh_gamma->ProjectionX();  
    dca_all =(TH1F*)dcapt_all->ProjectionX();    
    dca =(TH1F*)dcapt->ProjectionX();  
    dca_b =(TH1F*)dcapt_fit_b->ProjectionX();  
    dca_eta =(TH1F*)dcapt_eta->ProjectionX();     
    dca_pi0 =(TH1F*)dcapt_pi0->ProjectionX(); 
    dca_eta_gamma =(TH1F*)dcapt_eta_gamma->ProjectionX();     
    dca_pi0_gamma =(TH1F*)dcapt_pi0_gamma->ProjectionX();  
    dca_gamma =(TH1F*)dcapt_gamma->ProjectionX();  

    norm(hx);
    norm(dca);
    norm(dca_b);
    norm(dca_eta);
    norm(dca_all);
    norm(dca_pi0);
    norm(dca_pi0_gamma);
    norm(dca_eta_gamma);
    norm(dca_gamma);
    norm(dca_eh_pi0);
    norm(dca_eh_eta);
    norm(dca_eh_pi0_gamma);
    norm(dca_eh_eta_gamma);
    norm(dca_eh_gamma);
    norm(dca_eh_all);
    norm(hx);

    TCanvas *c1 = new TCanvas ("c1","dca single e ");
    dca->Draw("pe");
    dca_all->Draw("same pe");
    dca_b->Draw("same pe");
    dca_gamma->Draw("same pe");
    dca_pi0->Draw("same pe");
    dca_eta->Draw("same pe");
    dca_pi0_gamma->Draw("same pe");
    dca_eta_gamma->Draw("same pe");
    //hx->Draw("same pe"); 


    h1->RebinX();
    dcapt_eh_all->RebinX();
    h1->GetYaxis()->SetTitle("A. U.");
    h1->GetXaxis()->SetTitle("DCA [cm]");   
    h1->SetMarkerColor(1);
    h1->SetLineColor(1);
    dcapt_eh_all->SetMarkerStyle(25);
    dcapt_eh_all->SetMarkerColor(kRed);
    dcapt_eh_all->SetLineColor(kRed);
    h1->GetYaxis()->SetRangeUser(binning[0],binning[1]);   
    hx1 =(TH1F*)h1->ProjectionX("hx1"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[0],binning[1]);   
    dca_eh_all1 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all1"); 
    h1->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    hx2 =(TH1F*)h1->ProjectionX("hx2"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[1],binning[2]);   
    dca_eh_all2 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all2"); 
    h1->GetYaxis()->SetRangeUser(binning[2],binning[3]);   
    hx3 =(TH1F*)h1->ProjectionX("hx3"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[2],binning[3]);   
    dca_eh_all3 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all3"); 
    h1->GetYaxis()->SetRangeUser(binning[3],binning[4]);   
    hx4 =(TH1F*)h1->ProjectionX("hx4"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[3],binning[4]);   
    dca_eh_all4 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all4"); 
    h1->GetYaxis()->SetRangeUser(binning[4],binning[5]);   
    hx5 =(TH1F*)h1->ProjectionX("hx5"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[4],binning[5]);   
    dca_eh_all5 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all5"); 
    h1->GetYaxis()->SetRangeUser(binning[5],binning[6]);   
    hx6 =(TH1F*)h1->ProjectionX("hx6"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[5],binning[6]);   
    dca_eh_all6 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all6"); 
    h1->GetYaxis()->SetRangeUser(binning[6],binning[7]);   
    hx7 =(TH1F*)h1->ProjectionX("hx7");
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[6],binning[7]);   
    dca_eh_all7 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all7"); 
    h1->GetYaxis()->SetRangeUser(binning[7],binning[8]);   
    hx8 =(TH1F*)h1->ProjectionX("hx8"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[7],binning[8]);   
    dca_eh_all8 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all8"); 
    h1->GetYaxis()->SetRangeUser(binning[8],binning[9]);   
    hx9 =(TH1F*)h1->ProjectionX("hx9"); 
    dcapt_eh_all->GetYaxis()->SetRangeUser(binning[8],binning[9]);   
    dca_eh_all9 =(TH1F*)dcapt_eh_all->ProjectionX("dca_eh_all9");  
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
    TLegend *leg2 = new TLegend(0.2,0.3,0.8,0.7);
    leg2->AddEntry(hx1,"Photonic pairs","PE");
    leg2->AddEntry(dca_eh_all1,"Weighted sum","PE");
    TCanvas *c11 = new TCanvas ("c11","dca phoe pairs",1800,800);
    c11->Divide(5,2);
    c11->cd(1);
    hx1->Draw("same PE");   
    dca_eh_all1->Draw("same PE");
    c11->cd(2);
    hx2->Draw("same PE");   
    dca_eh_all2->Draw("same PE");
    c11->cd(3);
    hx3->Draw("same PE");   
    dca_eh_all3->Draw("same PE");
    c11->cd(4);
    hx4->Draw("same PE");   
    dca_eh_all4->Draw("same PE");
    c11->cd(5);
    hx5->Draw("same PE");   
    dca_eh_all5->Draw("same PE");
    c11->cd(6);
    hx6->Draw("same PE");   
    dca_eh_all6->Draw("same PE");
    c11->cd(7);
    hx7->Draw("same PE");   
    dca_eh_all7->Draw("same PE");
    c11->cd(8);
    hx8->Draw("same PE");   
    dca_eh_all8->Draw("same PE");
    c11->cd(9);
    hx9->Draw("same PE");   
    dca_eh_all9->Draw("same PE");
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
