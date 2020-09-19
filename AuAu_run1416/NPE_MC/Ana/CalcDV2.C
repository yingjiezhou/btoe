void CalcDV2(int save = 1 , int weight_data=1){ 
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");    
    TGaxis::SetMaxDigits(3);  
//////////////////////////////////////////////////////////////////
    TFile *MyDWeights = new TFile("./root/D_Weights.root","READ");
    TH1F* D_Weights = MyDWeights->Get("D_Weights");
    TFile *f_D6 = new TFile("../root/D0.toyMc0_momreshijing_c0.root");
    ch1 = (TChain*)f_D6->Get("nt");
/////////////////////////////////////////////////////////////////
    double pub_x[9]={0,1.73,2.23,2.72,3.22,3.73,4.4,6.01,15};
    double pub_y[9]={0,0.074-0.034,0.095-0.034,0.130-0.034,0.172-0.035,0.129-0.035,0.091-0.036,0.113-0.038,0};
    double pub_ye[9]={0,0.017,0.015,0.016,0.019,0.025,0.026,0.033,0};
    double pub_xe[9]={0,0,0,0,0,0,0,0,0};                                
    TGraphErrors *gr = new TGraphErrors(9,pub_x,pub_y,pub_xe,pub_ye);
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    double corr[numPtBins]={1e1,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8};
    TH1F *comp = new TH1F("comp","",numPtBins,binning);
   
    TH2F *h2DPtPhi = new TH2F("h2DPtPhi","h2DPtPhi",10,0,10,50,-TMath::Pi(),TMath::Pi());h2DPtPhi->Sumw2();
   TH2F *h2DPtPhi_w = new TH2F("h2DPtPhi_w","h2DPtPhi_w",10,0,10,50,-TMath::Pi(),TMath::Pi());h2DPtPhi_w->Sumw2();

    TH2F *h2DPtDeltaPhi = new TH2F("h2DPtDeltaPhi","h2DPtDeltaPhi",50,0,10,5,0,TMath::Pi()/2);h2DPtDeltaPhi->Sumw2();
    TH2F *h2DPtDeltaPhie = new TH2F("h2DPtDeltaPhie","h2DPtDeltaPhie",50,0,10,5,0,TMath::Pi()/2);h2DPtDeltaPhie->Sumw2();
    TH2F *h2DPtDeltaPhie2 = new TH2F("h2DPtDeltaPhie2","h2DPtDeltaPhie2",50,0,10,5,0,TMath::Pi()/2);h2DPtDeltaPhie2->Sumw2();
    TH2F *h2DPtDeltaPhi_w = new TH2F("h2DPtDeltaPhi_w","h2DPtDeltaPhi_w",50,0,10,5,0,TMath::Pi()/2);h2DPtDeltaPhi_w->Sumw2();
    TH2F *h2DPtDeltaPhie_w = new TH2F("h2DPtDeltaPhie_w","h2DPtDeltaPhie_w",50,0,10,5,0,TMath::Pi()/2);h2DPtDeltaPhie_w->Sumw2();
    TH2F *h2DPtDeltaPhie_w2 = new TH2F("h2DPtDeltaPhie_w2","h2DPtDeltaPhie_w2",50,0,10,5,0,TMath::Pi()/2);h2DPtDeltaPhie_w2->Sumw2();
    TH1F *ParentV2 = new TH1F("ParentV2","ParentV2",50,0,10);   
    TH1F *ElectronV2 = new TH1F("ElectronV2","ElectronV2",50,0,10); 
    TH1F *ElectronV22 = new TH1F("ElectronV22","ElectronV22",9,binning); 
    TH1F *ParentV2_w = new TH1F("ParentV2_w","ParentV2_w",50,0,10); 
    TH1F *ElectronV2_w = new TH1F("ElectronV2_w","ElectronV2_w",50,0,10);  
    TH1F *ElectronV2_w2 = new TH1F("ElectronV2_w2","ElectronV2_w2",9,binning);  
    TH1F *ElectronV2_w2sys = new TH1F("ElectronV2_w2sys","ElectronV2_w2sys",9,binning);  
//////////////////////////////////////////////////////////////////
  float s_eta;float s_pt;float s_id;float s_head;float s_parentid;float s_gparentid;float s_parentphi;
  float s_ggparentid;float s_parentpt;float s_gparentpt;float s_ggparentpt;float s_dcaxy;float s_hft;float s_hft;
  float s_phi;float s_iso;float s_px1;float s_px2;float s_ist;float s_ssd;float s_cen;float s_vz;float s_tpc;
/////////////////////////////////////////////////////////////////
    ch1->SetBranchAddress("phi",&s_parentphi);
    ch1->SetBranchAddress("eRPhi",&s_phi);
    ch1->SetBranchAddress("eRPt",&s_pt);
    ch1->SetBranchAddress("eREta",&s_eta); 
    ch1->SetBranchAddress("eRDca",&s_dcaxy);
    ch1->SetBranchAddress("pid",&s_parentid);
    ch1->SetBranchAddress("eTpc",&s_tpc);
    ch1->SetBranchAddress("eHft",&s_hft);
    ch1->SetBranchAddress("pt",&s_parentpt);
//////////////////////////////////////////////////////////////////
    TF1 f1("f1","1+2*[0]*cos(2*x)",0,TMath::Pi()/2);
    TF1 f2("f2","1",0,TMath::Pi()/2);
    TF1 f3("f3","-0.152728/17.*x+1.81100100880000003e-01",0,TMath::Pi()/2);
/////////////////////////////////////////////////////////////////
    for(int i =0;i<ch1->GetEntries();i++){
	ch1->GetEntry(i);
	if(i%100000==0)cout << "on " << i << " of " << ch1->GetEntries() << endl;
	if(fabs(s_eta)>0.7)continue;
	if(!(fabs(s_parentid)==421))continue;
	if(s_tpc*s_hft==0)continue;	 
	if(s_parentpt<0.315)s_parentpt=0.315;
	double ww = 1;
	//============================================
	//Get Weights
	int bin = D_Weights->FindBin(s_parentpt);
	ww =D_Weights->GetBinContent(bin);

	double EP = f2.GetRandom();//TMath::Pi()/4.;
	double dPhi = s_parentphi-EP;
	if(dPhi<0)dPhi += TMath::Pi()*2;
	if(dPhi>=TMath::Pi())dPhi = TMath::Pi()*2-dPhi;
	if(dPhi>=TMath::Pi()/2.)dPhi = TMath::Pi()-dPhi;

	double dPhie = s_phi-EP;
	if(dPhie<0)dPhie += TMath::Pi()*2;
	if(dPhie>=TMath::Pi())dPhie = TMath::Pi()*2-dPhie;
	if(dPhie>=TMath::Pi()/2.)dPhie = TMath::Pi()-dPhie;

	//if(s_parentpt<6.01)
	double v2 = gr->Eval(s_parentpt);
	//else double v2 = gr->Eval(6.01);
	//else double v2 = f3.Eval(s_parentpt);
	f1.SetParameter(0,v2);
	double v2Weight = 0;
	v2Weight = f1.Eval(dPhi)/(f1.Integral(0,TMath::Pi()/2)/(TMath::Pi()/2));
	//if((s_parentphi-s_phi) > TMath::Pi())s_phi+=TMath::Pi()*2;
	//if((s_parentphi-s_phi) < -TMath::Pi())s_parentphi+=TMath::Pi()*2;
	h2DPtPhi->Fill(s_parentpt,s_parentphi,ww);   
	h2DPtDeltaPhi->Fill(s_parentpt,dPhi,ww);
	h2DPtDeltaPhie->Fill(s_parentpt,dPhie,ww); 
	h2DPtDeltaPhie2->Fill(s_pt,dPhie); 
	h2DPtPhi_w->Fill(s_parentpt,s_parentphi,ww*v2Weight);   
	h2DPtDeltaPhi_w->Fill(s_parentpt,dPhi,ww*v2Weight); 
	h2DPtDeltaPhie_w->Fill(s_parentpt,dPhie,ww*v2Weight); 	
	h2DPtDeltaPhie_w2->Fill(s_pt,dPhie,ww*v2Weight); 		
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
	ParentV2_w->SetBinContent(i,val3);
	ParentV2_w->SetBinError(i,er3);	
	ElectronV2_w->SetBinContent(i,val4);
	ElectronV2_w->SetBinError(i,er4);
		
    }
   for(int i = 1;i<9+1;i++){
	TF1 func22("func22","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	TF1 func44("func44","[0]*(1+2*[1]*cos(2*x))",0,TMath::Pi()/2);
	h2DPtDeltaPhie2->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
	h2DPtDeltaPhie_w2->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
	temp22 = (TH1F*)h2DPtDeltaPhie2->ProjectionY();
	temp44 = (TH1F*)h2DPtDeltaPhie_w2->ProjectionY();	
	temp22->Fit("func22");
	double val22 = func22.GetParameter(1);
	double er22 = func22.GetParError(1);
	temp44->Fit("func44");
	double val44 = func44.GetParameter(1);
	double er44 = func44.GetParError(1);
	ElectronV2_w2->SetBinContent(i,val44);
	ElectronV2_w2->SetBinError(i,er44);
	ElectronV2_w2sys->SetBinContent(i,val44);
	ElectronV2_w2sys->SetBinError(i,val44*0.5);		
    }


/////////////////////////////////////////////////////////////////
    hPt = (TH1F*) h2DPtPhi->ProjectionX();
    hPt_w = (TH1F*) h2DPtPhi_w->ProjectionX();
    h2DPtPhi->GetXaxis()->SetRangeUser(2,3);
    h2DPtPhi_w->GetXaxis()->SetRangeUser(2,3);
    h2DPtDeltaPhi->GetXaxis()->SetRangeUser(2,3);
    h2DPtDeltaPhi_w->GetXaxis()->SetRangeUser(2,3);
    h2DPtDeltaPhie->GetXaxis()->SetRangeUser(2,3);
    h2DPtDeltaPhie_w->GetXaxis()->SetRangeUser(2,3);
    hPhi = (TH1F*) h2DPtPhi->ProjectionY();  
    hPhi_w = (TH1F*) h2DPtPhi_w->ProjectionY();    
    hPt->GetXaxis()->SetTitle("D #it{p}_{T} [GeV]");
    hPt->GetYaxis()->SetTitle("Arb. Units");
    hPhi->GetXaxis()->SetTitle("D #phi [GeV]");
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
    ElectronV2_w2->GetYaxis()->SetTitle("#it{v}_{2}");
    ElectronV2_w2->GetYaxis()->SetRangeUser(0,0.2);
    ElectronV2_w2->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    ParentV2_w->Draw("PE same");
    gr->Draw("PE same");
    ParentV2->SetLineColor(kBlue);
    ParentV2->SetMarkerColor(kBlue); 
    ParentV2_w->SetLineColor(kCyan);
    ParentV2_w->SetMarkerColor(kCyan); 
    ElectronV2->SetLineColor(kRed);
    ElectronV2->SetMarkerColor(kRed); 
    ElectronV2_w->SetLineColor(kGreen-2);
    ElectronV2_w->SetMarkerColor(kGreen-2);  
    ElectronV2_w2->SetLineColor(1);//kGray+1);
    ElectronV2_w2->SetMarkerColor(1);//kGray+1); 
    ElectronV22->SetLineColor(kOrange);
    ElectronV22->SetMarkerColor(kOrange); 
    //ParentV2->Draw("PE same");
    //ElectronV2->Draw("PE same");
    //ElectronV22->Draw("PE same");
    ElectronV2_w->Draw("PE same");
    ElectronV2_w2->Draw("PE same");
    f3.Draw("same");

    TCanvas *c33 = new TCanvas("c33","c33");
    ElectronV2_w2sys->SetFillColor(kGray);
    ElectronV2_w2->Draw("PE same");
    ElectronV2_w2sys->Draw("E2 same");
    ElectronV2_w2->Draw("PE same");
    //TFile fff("v2_hists/D_v2.root","RECREATE");
    //ElectronV2_w2->Write("D0V2");
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
