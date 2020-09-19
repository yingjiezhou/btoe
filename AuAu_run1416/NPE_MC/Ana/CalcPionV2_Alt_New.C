void CalcPionV2_Alt_New(int save = 1 , int weight_data=1){ 
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");    
    TGaxis::SetMaxDigits(3);  
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
    char dFile3[500];
    sprintf(dFile3,"../root/Hijing_NPE_Full.root");
    TFile *f_D3 = new TFile(dFile3);
    TChain *ch1 = f_D3->Get("Signal_tree");
    TFile *fi = new TFile("root/WeightsHijing.root");
    pi0_weights = (TH1F*) fi->Get("pi0_weights");
    gamma_weights = (TH1F*) fi->Get("gamma_weights");
    eta_weights = (TH1F*) fi->Get("eta_weights");
    //double pub_x[17]={0,0.297447,0.492561,0.690465,0.889393,1.08894,1.28902,1.48963,1.69072,1.89201,2.09311,2.29375,2.49383,2.69337,2.89233,3.15807,0};
    //double pub_y[17]={0,0.0229839,0.0453241,0.0674561,0.086957,0.103475,0.117154,0.128465,0.137378,0.143993,0.148979 ,0.152308,0.153868,0.154476,0.153999,0.152728,0};
    //double pub_ye[17]={0,0.000401,0.000300,0.000208,0.000137,0.000077,0.0000518,0.000054,0.000075,0.0000984,0.000134,0.000177,0.000235,0.000291,0.00037,0.00036,0};
    //double pub_xe[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};                             
    //TGraphErrors *gr = new TGraphErrors(17,pub_x,pub_y,pub_xe,pub_ye);

   double pub_x[17+8]={0,0.297447,0.492561,0.690465,0.889393,1.08894,1.28902,1.4896,1.75,2.25,2.75,3.25,3.75,4.25,4.75,5.5,6.5,7.5,8.5,9.5,11,13,15,17,25};
    double pub_y[17+8]={0,0.0229839,0.0453241,0.0674561,0.086957,0.103475,0.117154,0.128465,0.1504,0.1592,0.1630,0.1589,0.1494,0.1450,0.1370,0.1285,0.1174,0.1011,0.1049,0.1215,0.0895,0.1227,0.0986,0.1249,0};
    double pub_ye[17+8]={0,0.000401,0.000300,0.000208,0.000137,0.000077,0.0000518,0.000054,0.0014,0.0014,0.0018,0.0024,0.0031,0.0042,0.0057,0.0060,0.0102,0.0164,0.0249,0.0362,0.0408,0.0746,0.1350,0.2580,0};
    double pub_xe[17+8]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};                             
    TGraphErrors *gr = new TGraphErrors(17+8,pub_x,pub_y,pub_xe,pub_ye);

    TF1 *func = new TF1("func","[0]+x*[1]",5,40);
    gr->Fit(func,"R","",5,20);
    func->SetLineStyle(7);
//////////////////////////////////////////////////////////////////
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    TH1F* findbin = new TH1F("findbin","",numPtBins,binning);
    TH1F* mean1 = new TH1F("mean1","",numPtBins,binning);
    TH1F* mean2 = new TH1F("mean2","",numPtBins,binning);
    TFile *f_D = new TFile("root/DCA_plots_Hijing_GammaConv.root");
    pt2D_pi0 = (TH2F*)f_D->Get("pt2D_pi0");
    pt2Deh_pi0 = (TH2F*)f_D->Get("pt2D_eh_pi0"); 
    pt2D_pi0->GetYaxis()->SetRangeUser(0.1,100);
    pt2Deh_pi0->GetYaxis()->SetRangeUser(0.1,100);
    pt2D_pi0->GetXaxis()->SetRangeUser(binning[0],binning[1]);
    pi0pt_1 =(TH1F*) pt2D_pi0->ProjectionY();
    pi0pt_1->SetName("pi0pt_1");
    pt2D_pi0->GetXaxis()->SetRangeUser(binning[1],binning[2]);
    pi0pt_2 =(TH1F*) pt2D_pi0->ProjectionY();
    pi0pt_2->SetName("pi0pt_2");
    pt2D_pi0->GetXaxis()->SetRangeUser(binning[2],binning[3]);
    pi0pt_3 =(TH1F*) pt2D_pi0->ProjectionY();
    pi0pt_3->SetName("pi0pt_3");
    pt2D_pi0->GetXaxis()->SetRangeUser(binning[3],binning[4]);
    pi0pt_4 =(TH1F*) pt2D_pi0->ProjectionY();
    pi0pt_4->SetName("pi0pt_4");
    pt2D_pi0->GetXaxis()->SetRangeUser(binning[4],binning[5]);   
    pi0pt_5 =(TH1F*) pt2D_pi0->ProjectionY();
    pi0pt_5->SetName("pi0pt_5");
    pt2D_pi0->GetXaxis()->SetRangeUser(binning[5],binning[6]); 
    pi0pt_6 =(TH1F*) pt2D_pi0->ProjectionY();
    pi0pt_6->SetName("pi0pt_6");
    pt2D_pi0->GetXaxis()->SetRangeUser(binning[6],binning[7]);
    pi0pt_7 =(TH1F*) pt2D_pi0->ProjectionY();
    pi0pt_7->SetName("pi0pt_7");
    pt2D_pi0->GetXaxis()->SetRangeUser(binning[7],binning[8]);
    pi0pt_8 =(TH1F*) pt2D_pi0->ProjectionY();
    pi0pt_8->SetName("pi0pt_8");  
    pt2D_pi0->GetXaxis()->SetRangeUser(binning[8],binning[9]);
    pi0pt_9 =(TH1F*) pt2D_pi0->ProjectionY();
    pi0pt_9->SetName("pi0pt_9");

    pt2Deh_pi0->GetXaxis()->SetRangeUser(binning[0],binning[1]);
    pi0ptee_1 =(TH1F*) pt2Deh_pi0->ProjectionY();
    pi0ptee_1->SetName("pi0ptee_1");
    pt2Deh_pi0->GetXaxis()->SetRangeUser(binning[1],binning[2]);
    pi0ptee_2 =(TH1F*) pt2Deh_pi0->ProjectionY();
    pi0ptee_2->SetName("pi0ptee_2");
    pt2Deh_pi0->GetXaxis()->SetRangeUser(binning[2],binning[3]);
    pi0ptee_3 =(TH1F*) pt2Deh_pi0->ProjectionY();
    pi0ptee_3->SetName("pi0ptee_3");
    pt2Deh_pi0->GetXaxis()->SetRangeUser(binning[3],binning[4]);
    pi0ptee_4 =(TH1F*) pt2Deh_pi0->ProjectionY();
    pi0ptee_4->SetName("pi0ptee_4");
    pt2Deh_pi0->GetXaxis()->SetRangeUser(binning[4],binning[5]);   
    pi0ptee_5 =(TH1F*) pt2Deh_pi0->ProjectionY();
    pi0ptee_5->SetName("pi0ptee_5");
    pt2Deh_pi0->GetXaxis()->SetRangeUser(binning[5],binning[6]); 
    pi0ptee_6 =(TH1F*) pt2Deh_pi0->ProjectionY();
    pi0ptee_6->SetName("pi0ptee_6");
    pt2Deh_pi0->GetXaxis()->SetRangeUser(binning[6],binning[7]);
    pi0ptee_7 =(TH1F*) pt2Deh_pi0->ProjectionY();
    pi0ptee_7->SetName("pi0ptee_7");
    pt2Deh_pi0->GetXaxis()->SetRangeUser(binning[7],binning[8]);
    pi0ptee_8 =(TH1F*) pt2Deh_pi0->ProjectionY();
    pi0ptee_8->SetName("pi0ptee_8");  
    pt2Deh_pi0->GetXaxis()->SetRangeUser(binning[8],binning[9]);
    pi0ptee_9 =(TH1F*) pt2Deh_pi0->ProjectionY();
    pi0ptee_9->SetName("pi0ptee_9");

    findbin->SetBinContent(1,pi0ptee_1->GetMean()-pi0pt_1->GetMean());
    findbin->SetBinContent(2,pi0ptee_2->GetMean()-pi0pt_2->GetMean());
    findbin->SetBinContent(3,pi0ptee_3->GetMean()-pi0pt_3->GetMean());
    findbin->SetBinContent(4,pi0ptee_4->GetMean()-pi0pt_4->GetMean());
    findbin->SetBinContent(5,pi0ptee_5->GetMean()-pi0pt_5->GetMean());
    findbin->SetBinContent(6,pi0ptee_6->GetMean()-pi0pt_6->GetMean());
    findbin->SetBinContent(7,pi0ptee_7->GetMean()-pi0pt_7->GetMean());
    findbin->SetBinContent(8,pi0ptee_8->GetMean()-pi0pt_8->GetMean());
    findbin->SetBinContent(9,pi0ptee_9->GetMean()-pi0pt_9->GetMean());

    mean1->SetBinContent(1,pi0pt_1->GetMean());
    mean1->SetBinContent(2,pi0pt_2->GetMean());
    mean1->SetBinContent(3,pi0pt_3->GetMean());
    mean1->SetBinContent(4,pi0pt_4->GetMean());
    mean1->SetBinContent(5,pi0pt_5->GetMean());
    mean1->SetBinContent(6,pi0pt_6->GetMean());
    mean1->SetBinContent(7,pi0pt_7->GetMean());
    mean1->SetBinContent(8,pi0pt_8->GetMean());
    mean1->SetBinContent(9,pi0pt_9->GetMean());
    mean2->SetBinContent(1,pi0ptee_1->GetMean());
    mean2->SetBinContent(2,pi0ptee_2->GetMean());
    mean2->SetBinContent(3,pi0ptee_3->GetMean());
    mean2->SetBinContent(4,pi0ptee_4->GetMean());
    mean2->SetBinContent(5,pi0ptee_5->GetMean());
    mean2->SetBinContent(6,pi0ptee_6->GetMean());
    mean2->SetBinContent(7,pi0ptee_7->GetMean());
    mean2->SetBinContent(8,pi0ptee_8->GetMean());
    mean2->SetBinContent(9,pi0ptee_9->GetMean());

    TCanvas *cw = new TCanvas("cw","cw",1200,500);
    cw->Divide(3,1);
    cw->cd(1);
    findbin->Draw();
    cw->cd(2);
    mean1->Draw("P");
    mean2->SetMarkerColor(kRed);
    mean2->SetLineColor(kRed);	
    mean2->Draw("P same");
    cw->Update();
    cw->cd(3);
/////////////////////////////////////////////////////////////////
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    double corr[numPtBins]={1e1,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8};
    TH1F *comp = new TH1F("comp","",numPtBins,binning);
   
    TH2F *h2DPtPhi = new TH2F("h2DPtPhi","h2DPtPhi",20,0,20,50,-TMath::Pi(),TMath::Pi());h2DPtPhi->Sumw2();
    TH2F *h2DPtPhi_w = new TH2F("h2DPtPhi_w","h2DPtPhi_w",20,0,20,50,-TMath::Pi(),TMath::Pi());h2DPtPhi_w->Sumw2();
   
    TH2F *h2DPtDeltaPhi = new TH2F("h2DPtDeltaPhi","h2DPtDeltaPhi",40,0,20,10,0,TMath::Pi()/2);h2DPtDeltaPhi->Sumw2();
    TH2F *h2DPtDeltaPhie = new TH2F("h2DPtDeltaPhie","h2DPtDeltaPhie",40,0,20,10,0,TMath::Pi()/2);h2DPtDeltaPhie->Sumw2();
    TH2F *h2DPtDeltaPhie2 = new TH2F("h2DPtDeltaPhie2","h2DPtDeltaPhie2",40,0,20,10,0,TMath::Pi()/2);h2DPtDeltaPhie2->Sumw2();
    TH2F *h2DPtDeltaPhie3 = new TH2F("h2DPtDeltaPhie3","h2DPtDeltaPhie3",40,0,20,10,0,TMath::Pi()/2);h2DPtDeltaPhie3->Sumw2();
    TH2F *h2DPtDeltaPhi_w = new TH2F("h2DPtDeltaPhi_w","h2DPtDeltaPhi_w",40,0,20,10,0,TMath::Pi()/2);h2DPtDeltaPhi_w->Sumw2();
    TH2F *h2DPtDeltaPhie_w = new TH2F("h2DPtDeltaPhie_w","h2DPtDeltaPhie_w",40,0,20,10,0,TMath::Pi()/2);h2DPtDeltaPhie_w->Sumw2();
    TH2F *h2DPtDeltaPhie_w2 = new TH2F("h2DPtDeltaPhie_w2","h2DPtDeltaPhie_w2",40,0,20,10,0,TMath::Pi()/2);h2DPtDeltaPhie_w2->Sumw2();
    TH2F *h2DPtDeltaPhie_w3 = new TH2F("h2DPtDeltaPhie_w3","h2DPtDeltaPhie_w3",40,0,20,10,0,TMath::Pi()/2);h2DPtDeltaPhie_w3->Sumw2();
    TH1F *ParentV2 = new TH1F("ParentV2","ParentV2",40,0,20);   
    TH1F *ElectronV2 = new TH1F("ElectronV2","ElectronV2",40,0,20); 
    TH1F *ElectronV22 = new TH1F("ElectronV22","ElectronV22",9,binning); 
    TH1F *ParentV2_w = new TH1F("ParentV2_w","ParentV2_w",40,0,20); 
    TH1F *ElectronV2_w = new TH1F("ElectronV2_w","ElectronV2_w",40,0,20);  
    TH1F *ElectronV2_w2 = new TH1F("ElectronV2_w2","ElectronV2_w2",9,binning);  
    TH1F *ElectronV2_w3 = new TH1F("ElectronV2_w3","ElectronV2_w3",9,binning); 
    TH1F *ParentV2_w2 = new TH1F("ParentV2_w2","ParentV2_w2",9,binning);  
    TH1F *GammaPt = new TH1F("GammaPt","GammaPt",50,0,20);   GammaPt->Sumw2();
    TH1F *GammaPt1 = new TH1F("GammaPt1","GammaPt1",50,0,20); GammaPt1->Sumw2();
    TH1F *Pi0Pt = new TH1F("Pi0Pt","Pi0Pt",50,0,20);   Pi0Pt->Sumw2();
    TH1F *Pi0Pt1 = new TH1F("Pi0Pt1","Pi0Pt1",50,0,20); Pi0Pt1->Sumw2();
    TH1F *WeightPt = new TH1F("WeightPt","WeightPt",50,0,20);   WeightPt->Sumw2();
    TH2F *Pt2D = new TH2F("Pt2D","Pt2D",500,0,20,500,0,20); Pt2D->Sumw2();
    TH2F *Pt2D1 = new TH2F("Pt2D1","Pt2D1",500,0,20,500,0,20); Pt2D1->Sumw2();
//////////////////////////////////////////////////////////////////

    float s_eta;float s_pt;float s_id;float s_head;float s_parentid;float s_gparentid;float s_parentphi;float s_gparentphi;
    float s_ggparentid;float s_parentpt;float s_gparentpt;float s_ggparentpt;float s_dcaxy;float s_hft;
    float s_phi;float s_iso;float s_px1;float s_px2;float s_ist;float s_ssd;float s_cen;float s_vz;
/////////////////////////////////////////////////////////////////
    TFile *f_D3 = new TFile("../root/Pi0.toyMc0_momreshijing_c0_job3.root");
    ch5 = (TChain*)f_D3->Get("nt");
    TFile *f_D4 = new TFile("../root/Pi0.toyMc0_momreshijing_c0_job2.root");
    ch6 = (TChain*)f_D4->Get("nt");
    ch5->SetBranchAddress("ePt",&s_pt);
    ch5->SetBranchAddress("eEta",&s_eta); 
    ch5->SetBranchAddress("eDca",&s_dcaxy);
    ch5->SetBranchAddress("pid",&s_parentid);
    ch5->SetBranchAddress("pt",&s_parentpt);
    for(int i =0;i<ch5->GetEntries();i++){
	ch5->GetEntry(i);
	if(i%100000==0)cout << "on " << i << " of " << ch5->GetEntries() << endl;
	if(!(s_parentid==111))continue;
	if(fabs(s_dcaxy)>1)continue;
	if(s_eta>1)continue;
	int bin = pi0_weights->FindBin(s_parentpt);
	double ww = pi0_weights->GetBinContent(bin);   
	GammaPt->Fill(s_pt,ww);
	Pi0Pt->Fill(s_parentpt,ww);
	Pt2D->Fill(s_parentpt,s_pt,ww);
    }
    ch6->SetBranchAddress("ePt",&s_pt);
    ch6->SetBranchAddress("eEta",&s_eta); 
    ch6->SetBranchAddress("eDca",&s_dcaxy);
    ch6->SetBranchAddress("pid",&s_parentid);
    ch6->SetBranchAddress("pt",&s_parentpt);
    for(int i =0;i<ch6->GetEntries();i++){
	ch6->GetEntry(i);
	if(i%100000==0)cout << "on " << i << " of " << ch6->GetEntries() << endl;
	if(!(s_parentid==111))continue;
	if(fabs(s_dcaxy)>1)continue;
	if(s_eta>1)continue;
	int bin = pi0_weights->FindBin(s_parentpt);
	double ww = pi0_weights->GetBinContent(bin);   
	GammaPt1->Fill(s_pt,ww);
	Pi0Pt1->Fill(s_parentpt,ww);
	Pt2D1->Fill(s_parentpt,s_pt,ww);
    }
    norm(GammaPt);
    norm(GammaPt1);
    GammaPt1->SetLineColor(kRed);
    GammaPt1->SetMarkerColor(kRed);
    norm(Pi0Pt);
    norm(Pi0Pt1);
    Pi0Pt1->SetLineColor(kRed);
    Pi0Pt1->SetMarkerColor(kRed);
  
   
    TCanvas *cnorm = new  TCanvas("cnorm","Nomrs",1000,500);
    cnorm->Divide(2,1);
    cnorm->cd(1);
    GammaPt->Draw();
    GammaPt1->Draw("same");
    cnorm->cd(2);
    Pi0Pt->Draw();
    Pi0Pt1->Draw("same");
    
    for(int i = 1; i<GammaPt->GetNbinsX()+1;i++){
	double tempp1 = GammaPt->GetBinContent(i);
	double tempp2 = GammaPt1->GetBinContent(i);	
	if(tempp2>0)WeightPt->SetBinContent(i,tempp1/tempp2);
	else WeightPt->SetBinContent(i,0);
	
    }
    TCanvas *cnorm1 = new  TCanvas("cnorm1","weights");
    WeightPt->Draw();
    TF1 *line = new TF1("line","x",0,20);
    line->SetLineStyle(7);
    TCanvas *cnorm2 = new  TCanvas("cnorm2","Nomrs2D",1000,500);
    cnorm2->Divide(2,1);
    cnorm2->cd(1);
    Pt2D->Draw("COLZ");
    line->Draw("same");
    cnorm2->cd(2);
    Pt2D1->Draw("COLZ"); 
    line->Draw("same");
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
    ch1->SetBranchAddress("sig_parentphi",&s_parentphi);
    ch1->SetBranchAddress("sig_gparentphi",&s_gparentphi);
    ch1->SetBranchAddress("sig_head",&s_head);
    ch1->SetBranchAddress("sig_isiso",&s_iso);
    ch1->SetBranchAddress("sig_parentid",&s_parentid);
    ch1->SetBranchAddress("sig_gparentid",&s_gparentid);
    ch1->SetBranchAddress("sig_ggparentid",&s_ggparentid);
    ch1->SetBranchAddress("sig_parentpt",&s_parentpt);
    ch1->SetBranchAddress("sig_gparentpt",&s_gparentpt);
    ch1->SetBranchAddress("sig_ggparentpt",&s_ggparentpt);
//////////////////////////////////////////////////////////////////
    TF1 f1("f1","1+2*[0]*cos(2*x)",0,TMath::Pi()/2);
    TF1 f11("f11","1+2*[0]*cos(2*x)",0,TMath::Pi()/2);
    TF1 f2("f2","1",0,TMath::Pi()/2);
    TF1 f3("f3","-0.152728/17.*x+1.81100100880000003e-01",0,TMath::Pi()/2);
/////////////////////////////////////////////////////////////////
    if(0){
	for(int i =0;i<ch1->GetEntries();i++){
	    ch1->GetEntry(i);
	    if(i%100000==0)cout << "on " << i << " of " << ch1->GetEntries() << endl;
	    if(!(s_id==3 || s_id==2))continue;
	    if(fabs(s_dcaxy)>1)continue;
	    if(!(s_head==149 && s_gparentid==149 && s_parentid==1))continue;
	    double ww = 1;
	    //============================================
	    //Get Weights
	    double pt_for_weight = -1;
	    //if(s_head==s_parentid)pt_for_weight=s_parentpt;
	    //else if(s_head==s_gparentid)
	    //s_gparentphi = s_parentphi;
	    //s_gparentpt= s_gparentpt*2;
	    //s_gparentpt=s_pt*4;
	    pt_for_weight=s_gparentpt;
	    if(s_head!=0){
		if(pt_for_weight/s_pt<0.7)continue;
	    }
	    //============================================	
   
	    if(s_head == 149){	    
		int bin = pi0_weights->FindBin(pt_for_weight);
		ww = pi0_weights->GetBinContent(bin);   
	    } else if(s_head == 147){	
		int bin = pi0_weights->FindBin(pt_for_weight);
		ww = eta_weights->GetBinContent(bin);
	    } else if(s_head == 1){      
		int bin = gamma_weights->FindBin(pt_for_weight);
		ww = gamma_weights->GetBinContent(bin); 
	    }
	    //int bin1 = WeightPt->FindBin(s_parentpt);
	    //ww*= WeightPt->GetBinContent(bin1);
	    int ptbin = findbin->FindBin(s_pt);
	    double wpt = findbin->GetBinContent(ptbin);
	    //if(ww>10)ww=1;
	    double EP = f2.GetRandom();//TMath::Pi()/4.;
	    double dPhi = s_gparentphi-EP;
	    if(dPhi<0)dPhi += TMath::Pi()*2;
	    if(dPhi>=TMath::Pi())dPhi = TMath::Pi()*2-dPhi;
	    if(dPhi>=TMath::Pi()/2.)dPhi = TMath::Pi()-dPhi;

	    double dPhie = s_phi-EP;
	    if(dPhie<0)dPhie += TMath::Pi()*2;
	    if(dPhie>=TMath::Pi())dPhie = TMath::Pi()*2-dPhie;
	    if(dPhie>=TMath::Pi()/2.)dPhie = TMath::Pi()-dPhie;

	    //if(s_parentpt<3.15807)
	    if(s_gparentpt<7.6)double v2 = gr->Eval(s_gparentpt);
	    else double v2 = func->Eval(s_gparentpt);
	    //else double v2 = f3.Eval(s_parentpt);
	    f1.SetParameter(0,v2);
	    double v2Weight = 0;
	    v2Weight = f1.Eval(dPhi)/(f1.Integral(0,TMath::Pi()/2)/(TMath::Pi()/2));
	    if(wpt<0)wpt=0;
	    if(s_gparentpt+wpt<7.6)double v2ee = gr->Eval(s_gparentpt+wpt);
	    else double v2ee = func->Eval(s_gparentpt+wpt);
	    f11.SetParameter(0,v2ee);
	    double v2Weightee = 0;
	    v2Weightee = f11.Eval(dPhi)/(f11.Integral(0,TMath::Pi()/2)/(TMath::Pi()/2));

	    //if((s_parentphi-s_phi) > TMath::Pi())s_phi+=TMath::Pi()*2;
	    //if((s_parentphi-s_phi) < -TMath::Pi())s_parentphi+=TMath::Pi()*2;
	    h2DPtPhi->Fill(s_gparentpt,s_gparentphi,ww);   
	    h2DPtDeltaPhi->Fill(s_gparentpt,dPhi,ww);
	    h2DPtDeltaPhie->Fill(s_gparentpt,dPhie,ww); 
	    h2DPtDeltaPhie2->Fill(s_pt,dPhie);
	    h2DPtPhi_w->Fill(s_gparentpt,s_gparentphi,ww*v2Weight);   
	    h2DPtDeltaPhi_w->Fill(s_gparentpt,dPhi,ww*v2Weight); 
	    h2DPtDeltaPhie_w->Fill(s_gparentpt,dPhie,ww*v2Weight); 	
	    h2DPtDeltaPhie_w2->Fill(s_pt,dPhie,v2Weight*ww); 	
	    h2DPtDeltaPhie_w3->Fill(s_pt,dPhie,v2Weightee*ww); 

	}
//////////////////////////////////////////////////////////////////
	for(int i = 1;i<ParentV2->GetNbinsX()+1;i++){
	    TF1 func1("func1","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	    TF1 func2("func2","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	    TF1 func3("func3","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	    TF1 func4("func4","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	    double low = ParentV2->GetBinLowEdge(i);
	    double high = ParentV2->GetBinLowEdge(i)+ParentV2->GetBinWidth(i);    
	    h2DPtDeltaPhi->GetXaxis()->SetRangeUser(low,high);
	    h2DPtDeltaPhi_w->GetXaxis()->SetRangeUser(low,high);
	    h2DPtDeltaPhie->GetXaxis()->SetRangeUser(low,high);
	    h2DPtDeltaPhie_w->GetXaxis()->SetRangeUser(low,high);
	    temp1 = (TH1F*)h2DPtDeltaPhi->ProjectionY();
	    temp2 = (TH1F*)h2DPtDeltaPhie->ProjectionY();
	    temp3 = (TH1F*)h2DPtDeltaPhi_w->ProjectionY();
	    temp4 = (TH1F*)h2DPtDeltaPhie_w->ProjectionY();		
	    temp1->Fit("func1");
	    double val1 = func1.GetParameter(1);
	    double er1 = func1.GetParError(1);
	    temp2->Fit("func2");
	    double val2 = func2.GetParameter(1);
	    double er2 = func2.GetParError(1);
	    temp3->Fit("func3");
	    double val3 = func3.GetParameter(1);
	    double er3 = func3.GetParError(1);
	    temp4->Fit("func4");
	    double val4 = func4.GetParameter(1);
	    double er4 = func4.GetParError(1);
	    ParentV2->SetBinContent(i,val1);
	    ParentV2->SetBinError(i,er1);
	    ElectronV2->SetBinContent(i,val2);
	    ElectronV2->SetBinError(i,er2);
	    ParentV2_w->SetBinContent(i,val3);//-val1
	    ParentV2_w->SetBinError(i,er3);	
	    ElectronV2_w->SetBinContent(i,val4);//-val2
	    ElectronV2_w->SetBinError(i,er4);		
	}
	for(int i = 1;i<9+1;i++){
	    TF1 func22("func22","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	    TF1 func44("func44","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	    TF1 func55("func55","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	    TF1 func66("func66","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	    h2DPtDeltaPhie2->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
	    h2DPtDeltaPhie_w2->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
	    h2DPtDeltaPhie_w3->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
	    h2DPtDeltaPhi_w->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
	    temp22 = (TH1F*)h2DPtDeltaPhie2->ProjectionY();
	    temp44 = (TH1F*)h2DPtDeltaPhie_w2->ProjectionY();
	    temp66 = (TH1F*)h2DPtDeltaPhie_w3->ProjectionY();
	    temp55 = (TH1F*)h2DPtDeltaPhi_w->ProjectionY();	
	    temp22->Fit("func22");
	    double val22 = func22.GetParameter(1);
	    double er22 = func22.GetParError(1);
	    temp44->Fit("func44");
	    double val44 = func44.GetParameter(1);
	    double er44 = func44.GetParError(1);
	    ElectronV2_w2->SetBinContent(i,val44);
	    ElectronV2_w2->SetBinError(i,er44);
	    temp55->Fit("func55");
	    double val55 = func55.GetParameter(1);
	    double er55 = func55.GetParError(1);
	    ParentV2_w2->SetBinContent(i,val55);
	    ParentV2_w2->SetBinError(i,er55);
	    temp66->Fit("func66");
	    double val66 = func66.GetParameter(1);
	    double er66 = func66.GetParError(1);
	    ElectronV2_w3->SetBinContent(i,val66);
	    ElectronV2_w3->SetBinError(i,er66);	
	    cout << i << " " << val22 << " " << val44 << " " << val66<<endl;
	}

/////////////////////////////////////////////////////////////////
	hPt = (TH1F*) h2DPtPhi->ProjectionX();
	hPt_w = (TH1F*) h2DPtPhi_w->ProjectionX();
	h2DPtPhi->GetXaxis()->SetRangeUser(2.5,3.5);
	h2DPtPhi_w->GetXaxis()->SetRangeUser(2.5,3.5);
	h2DPtDeltaPhi->GetXaxis()->SetRangeUser(2.5,3.5);
	h2DPtDeltaPhi_w->GetXaxis()->SetRangeUser(2.5,3.5);
	h2DPtDeltaPhie->GetXaxis()->SetRangeUser(2.5,3.5);
	h2DPtDeltaPhie_w->GetXaxis()->SetRangeUser(2.5,3.5);
	hPhi = (TH1F*) h2DPtPhi->ProjectionY();  
	hPhi_w = (TH1F*) h2DPtPhi_w->ProjectionY();    
	hPt->GetXaxis()->SetTitle("Pion #it{p}_{T} [GeV]");
	hPt->GetYaxis()->SetTitle("Arb. Units");
	hPhi->GetXaxis()->SetTitle("Pion #phi [GeV]");
	hPhi->GetYaxis()->SetTitle("Arb. Units");
	hDeltaPhi = (TH1F*) h2DPtDeltaPhi->ProjectionY();    
	hDeltaPhi->GetXaxis()->SetTitle("#Delta#phi [GeV]");
	hDeltaPhi->GetYaxis()->SetTitle("Arb. Units");
	hDeltaPhie = (TH1F*) h2DPtDeltaPhie->ProjectionY();   
	hDeltaPhi_w = (TH1F*) h2DPtDeltaPhi_w->ProjectionY(); 
	hDeltaPhie_w = (TH1F*) h2DPtDeltaPhie_w->ProjectionY(); 
	hPt_w->SetLineColor(kRed);
	hPhi_w->SetLineColor(kRed);    
	hDeltaPhi_w->SetLineColor(kRed); 
	hDeltaPhie_w->SetLineColor(kBlue);
	hDeltaPhie_w->SetMarkerColor(kBlue);
	hDeltaPhie->SetLineColor(kBlue);  
	TCanvas *c1 = new TCanvas("c1","c1",1000,500);
	c1->Divide(2,1);
	c1->cd(1);
	hPt->Draw();
	hPt_w->Draw("same hist");
	c1->cd(2);
	hPhi->Draw();
	hPhi_w->Draw("same hist");
	TCanvas *c2 = new TCanvas("c2","c2");
	TF1 func1("func1","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	hDeltaPhi_w->Fit("func1");
	hDeltaPhi->Draw();
	hDeltaPhi_w->Draw("same hist");
	hDeltaPhie->Draw("same hist");
	hDeltaPhie_w->Draw("same PE");
	TCanvas *c3 = new TCanvas("c3","c3");
	ParentV2_w->GetYaxis()->SetTitle("#it{v}_{2}");
	ParentV2_w->GetYaxis()->SetRangeUser(0,0.2);
	ParentV2_w->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
	ParentV2_w->Draw("PE same");
	ParentV2_w2->Draw("PE same");
	gr->Draw("PE same");
	ParentV2_w2->SetLineColor(kBlue);
	ParentV2_w2->SetMarkerColor(kBlue); 
	ParentV2_w->SetLineColor(kCyan);
	ParentV2_w->SetMarkerColor(kCyan); 
	ElectronV2->SetLineColor(kRed);
	ElectronV2->SetMarkerColor(kRed); 
	ElectronV2_w->SetLineColor(kGreen-2);
	ElectronV2_w->SetMarkerColor(kGreen-2);  
	ElectronV2_w2->SetLineColor(kGray+1);
	ElectronV2_w2->SetMarkerColor(kGray+1); 
	ElectronV2_w3->SetLineColor(kMagenta);
	ElectronV2_w3->SetMarkerColor(kMagenta); 
	ElectronV22->SetLineColor(kOrange);
	ElectronV22->SetMarkerColor(kOrange); 

	//ElectronV2->Draw("PE same");
	//ElectronV22->Draw("PE same");
	ElectronV2_w->Draw("PE same");
	ElectronV2_w2->Draw("PE same");
	ElectronV2_w3->Draw("PE same");
	f3.Draw("same");
	if(save){
	    TFile fff("v2_hists/pion_v2_hijing_new.root","RECREATE");
	    ParentV2_w2->Write("PionV2");
	    ElectronV2_w2->Write("PhoEV2");
	    ElectronV2_w3->Write("PhoEV2_ee");
	}
    }
//======================================================================
//======================================================================
//======================================================================
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
