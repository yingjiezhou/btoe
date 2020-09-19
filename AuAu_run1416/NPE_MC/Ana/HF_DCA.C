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

void HF_DCA(int save = 0, int weight_data=0){
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  //////////////////////////////////////////////////////////////////
  TFile *weight_Charm_fonll=new TFile("../root/D0_pp200_FONALL.root","READ");
  TFile *weight_bottom_fonll=new TFile("../root/B_pp200_FONALL.root","READ");
  B_pp200_fonll=(TGraph *) weight_bottom_fonll->Get("B_Spectra_pp200");
  D_pp200_fonll=(TGraph *) weight_Charm_fonll->Get("D0_Spectra_pp200"); // not used here zyj
  TFile *MyBWeights = new TFile("./root/B_Weights.root","READ");
  TH1F* B_Weights = MyBWeights->Get("B_Weights");
  TFile *MyDWeights = new TFile("./root/D_Weights_FONLL.root","READ");
  TH1F* D_Weights = MyDWeights->Get("D_Weights");
  
  double lc_x[14]={0.11344,0.49159,0.99579,1.5,2.0042,2.5084, 3,3.5042,3.9958,4.5,5.0042,5.5084,6,6.30252};
  double lc_y[14]={1.06143,1.10996,1.25051,1.44071,1.59913,1.62314,1.4843,1.21379,0.942128,0.725841,0.580436,0.511373,0.481779,0.464159};
  TGraph *gr_lc = new TGraph(14,lc_x,lc_y);
  
  
  TCanvas *clc = new TCanvas("clc","clc");
  gr_lc->Draw("APEL");
  
  double lb_x[14]={4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,15,17,19,22.5};
  double lb_y[14]={0.324,0.281,0.257,0.245,0.210,0.194,0.191,0.172,0.159,0.165,0.136,0.126,0.109};
  TGraph *gr_lb = new TGraph(14,lb_x,lb_y);
  
  //////////////////////////////////////////////////////////////////
  TFile *f_D3 = new TFile("../root/B0.toyMc0_momreshijing_c0.root");
  ch5 = (TChain*)f_D3->Get("nt");
  TFile *f_D4 = new TFile("../root/Bp.toyMc0_momreshijing_c0.root");
  ch6 = (TChain*)f_D4->Get("nt");
  TFile *f_D33 = new TFile("../root/Bs.toyMc0_momreshijing_c0.root");
  ch55 = (TChain*)f_D33->Get("nt");
  TFile *f_D44 = new TFile("../root/Lb.toyMc0_momreshijing_c0.root");
  ch66 = (TChain*)f_D44->Get("nt");
  TFile *f_D5 = new TFile("../root/Dp.toyMc0_momreshijing_c0.root");
  ch7 = (TChain*)f_D5->Get("nt");
  TFile *f_D6 = new TFile("../root/D0.toyMc0_momreshijing_c0.root");
  ch8 = (TChain*)f_D6->Get("nt");
  TFile *f_D55 = new TFile("../root/Ds.toyMc0_momreshijing_c0.root");
  ch77 = (TChain*)f_D55->Get("nt");
  TFile *f_D66 = new TFile("../root/Lc.toyMc0_momreshijing_c0.root");
  ch88 = (TChain*)f_D66->Get("nt");
  double num_d0 = ch8->GetEntries();
  double num_dp = ch7->GetEntries();
  double num_ds = ch77->GetEntries();
  double num_lc = ch88->GetEntries();
  double num_b0 = ch5->GetEntries();
  double num_bp = ch6->GetEntries();
  double num_bs = ch55->GetEntries();
  double num_lb = ch66->GetEntries();
  if(save){
    TH2F *phipt_d_all = new TH2F("phipt_d_all","phipt_d_all",1000,-4,4,85,0,8.5);phipt_d_all->Sumw2();
    TH2F *phipt_d0 = new TH2F("phipt_d0","phipt_d0",1000,-4,4,85,0,8.5);phipt_d0->Sumw2();
    TH2F *phipt_dp = new TH2F("phipt_dp","phipt_dp",1000,-4,4,85,0,8.5);phipt_dp->Sumw2();
    TH2F *phipt_ds = new TH2F("phipt_ds","phipt_ds",1000,-4,4,85,0,8.5);phipt_ds->Sumw2();
    TH2F *phipt_lc = new TH2F("phipt_lc","phipt_lc",1000,-4,4,85,0,8.5);phipt_lc->Sumw2();
    TH2F *phipt_b_all = new TH2F("phipt_b_all","phipt_b_all",1000,-4,4,85,0,8.5);phipt_b_all->Sumw2();
    TH2F *phipt_b0 = new TH2F("phipt_b0","phipt_b0",1000,-4,4,85,0,8.5);phipt_b0->Sumw2();
    TH2F *phipt_bp = new TH2F("phipt_bp","phipt_bp",1000,-4,4,85,0,8.5);phipt_bp->Sumw2();
    TH2F *phipt_bs = new TH2F("phipt_bs","phipt_bs",1000,-4,4,85,0,8.5);phipt_bs->Sumw2();
    TH2F *phipt_lb = new TH2F("phipt_lb","phipt_lb",1000,-4,4,85,0,8.5);phipt_lb->Sumw2();
    
    TH2F *cosphipt_d_all = new TH2F("cosphipt_d_all","cosphipt_d_all",1000,-1,1,85,0,8.5);cosphipt_d_all->Sumw2();
    TH2F *cosphipt_d0 = new TH2F("cosphipt_d0","cosphipt_d0",1000,-1,1,85,0,8.5);cosphipt_d0->Sumw2();
    TH2F *cosphipt_dp = new TH2F("cosphipt_dp","cosphipt_dp",1000,-1,1,85,0,8.5);cosphipt_dp->Sumw2();
    TH2F *cosphipt_ds = new TH2F("cosphipt_ds","cosphipt_ds",1000,-1,1,85,0,8.5);cosphipt_ds->Sumw2();
    TH2F *cosphipt_lc = new TH2F("cosphipt_lc","cosphipt_lc",1000,-1,1,85,0,8.5);cosphipt_lc->Sumw2();
    TH2F *cosphipt_b_all = new TH2F("cosphipt_b_all","cosphipt_b_all",1000,-1,1,85,0,8.5);cosphipt_b_all->Sumw2();
    TH2F *cosphipt_b0 = new TH2F("cosphipt_b0","cosphipt_b0",1000,-1,1,85,0,8.5);cosphipt_b0->Sumw2();
    TH2F *cosphipt_bp = new TH2F("cosphipt_bp","cosphipt_bp",1000,-1,1,85,0,8.5);cosphipt_bp->Sumw2();
    TH2F *cosphipt_bs = new TH2F("cosphipt_bs","cosphipt_bs",1000,-1,1,85,0,8.5);cosphipt_bs->Sumw2();
    TH2F *cosphipt_lb = new TH2F("cosphipt_lb","cosphipt_lb",1000,-1,1,85,0,8.5);cosphipt_lb->Sumw2();
    
    
    
    TH2F *dcapt_d_all = new TH2F("dcapt_d_all","dcapt_d_all",600,-6,0,85,0,8.5);dcapt_d_all->Sumw2();
    TH2F *dcapt_d0 = new TH2F("dcapt_d0","dcapt_d0",600,-6,0,85,0,8.5);dcapt_d0->Sumw2();
    TH2F *dcapt_dp = new TH2F("dcapt_dp","dcapt_dp",600,-6,0,85,0,8.5);dcapt_dp->Sumw2();
    TH2F *dcapt_ds = new TH2F("dcapt_ds","dcapt_ds",600,-6,0,85,0,8.5);dcapt_ds->Sumw2();
    TH2F *dcapt_lc = new TH2F("dcapt_lc","dcapt_lc",600,-6,0,85,0,8.5);dcapt_lc->Sumw2();
    TH2F *dcapt_b_all = new TH2F("dcapt_b_all","dcapt_b_all",600,-6,0,85,0,8.5);dcapt_b_all->Sumw2();
    TH2F *dcapt_b0 = new TH2F("dcapt_b0","dcapt_b0",600,-6,0,85,0,8.5);dcapt_b0->Sumw2();
    TH2F *dcapt_bp = new TH2F("dcapt_bp","dcapt_bp",600,-6,0,85,0,8.5);dcapt_bp->Sumw2();
    TH2F *dcapt_bs = new TH2F("dcapt_bs","dcapt_bs",600,-6,0,85,0,8.5);dcapt_bs->Sumw2();
    TH2F *dcapt_lb = new TH2F("dcapt_lb","dcapt_lb",600,-6,0,85,0,8.5);dcapt_lb->Sumw2();
    
    TH2F *dcapt_lin_d_all = new TH2F("dcapt_lin_d_all","dcapt_lin_d_all",500,0,0.5,85,0,8.5);dcapt_lin_d_all->Sumw2();
    TH2F *dcapt_lin_d0 = new TH2F("dcapt_lin_d0","dcapt_lin_d0",500,0,0.5,85,0,8.5);dcapt_lin_d0->Sumw2();
    TH2F *dcapt_lin_dp = new TH2F("dcapt_lin_dp","dcapt_lin_dp",500,0,0.5,85,0,8.5);dcapt_lin_dp->Sumw2();
    TH2F *dcapt_lin_ds = new TH2F("dcapt_lin_ds","dcapt_lin_ds",500,0,0.5,85,0,8.5);dcapt_lin_ds->Sumw2();
    TH2F *dcapt_lin_lc = new TH2F("dcapt_lin_lc","dcapt_lin_lc",500,0,0.5,85,0,8.5);dcapt_lin_lc->Sumw2();
    TH2F *dcapt_lin_b_all = new TH2F("dcapt_lin_b_all","dcapt_lin_b_all",500,0,0.5,85,0,8.5);dcapt_lin_b_all->Sumw2();
    TH2F *dcapt_lin_b0 = new TH2F("dcapt_lin_b0","dcapt_lin_b0",500,0,0.5,85,0,8.5);dcapt_lin_b0->Sumw2();
    TH2F *dcapt_lin_bp = new TH2F("dcapt_lin_bp","dcapt_lin_bp",500,0,0.5,85,0,8.5);dcapt_lin_bp->Sumw2();
    TH2F *dcapt_lin_bs = new TH2F("dcapt_lin_bs","dcapt_lin_bs",500,0,0.5,85,0,8.5);dcapt_lin_bs->Sumw2();
    TH2F *dcapt_lin_lb = new TH2F("dcapt_lin_lb","dcapt_lin_lb",500,0,0.5,85,0,8.5);dcapt_lin_lb->Sumw2();
    
    
    TH2F *pt2D_d0 = new TH2F("pt2D_d0","pt2D_d0",200,0,20,200,0,20);pt2D_d0->Sumw2();
    TH2F *pt2D_dp = new TH2F("pt2D_dp","pt2D_dp",200,0,20,200,0,20);pt2D_dp->Sumw2();
    TH2F *pt2D_ds = new TH2F("pt2D_ds","pt2D_ds",200,0,20,200,0,20);pt2D_ds->Sumw2();
    TH2F *pt2D_lc = new TH2F("pt2D_lc","pt2D_lc",200,0,20,200,0,20);pt2D_lc->Sumw2();
    TH2F *pt2D_b0 = new TH2F("pt2D_b0","pt2D_b0",200,0,20,200,0,20);pt2D_b0->Sumw2();
    TH2F *pt2D_bp = new TH2F("pt2D_bp","pt2D_bp",200,0,20,200,0,20);pt2D_bp->Sumw2();
    TH2F *pt2D_bs = new TH2F("pt2D_bs","pt2D_bs",200,0,20,200,0,20);pt2D_bs->Sumw2();
    TH2F *pt2D_lb = new TH2F("pt2D_lb","pt2D_lb",200,0,20,200,0,20);pt2D_lb->Sumw2();
    
    
    
    
    float s_eta;float s_pt;float s_id;float s_head;
    float s_parentid;float s_gparentid;float s_ggparentid;float s_parentpt;
    float s_gparentpt;float s_ggparentpt;float s_dcaxy;
    float s_hft;float s_tpc;float s_phi;float s_iso;float s_px1;float s_px2;float s_ist;
    float s_ssd;float s_cen;float s_parentphi;double s_vz;
    double s_px;double s_py;double s_pz;double s_dcaxy1;double m_px;double m_py;float m_pt;float m_phi;
    int s_parentid1;
    
    ch5->SetBranchAddress("phi",&m_phi);
    ch5->SetBranchAddress("eRPhi",&s_phi);
    ch5->SetBranchAddress("eRPt",&s_pt);
    ch5->SetBranchAddress("eREta",&s_eta);
    ch5->SetBranchAddress("eRDca",&s_dcaxy);
    ch5->SetBranchAddress("pid",&s_parentid);
    ch5->SetBranchAddress("eTpc",&s_tpc);
    ch5->SetBranchAddress("eHft",&s_hft);
    ch5->SetBranchAddress("pt",&s_parentpt);
    for(int i=0;i<ch5->GetEntries();i++){
      ch5->GetEntry(i);
      if(i%1000000==0)cout << "on " << i << " of " << ch5->GetEntries() << endl;
      if(fabs(s_eta)>0.7)continue;
      if(!(fabs(s_parentid)==511))continue;
      if(s_tpc*s_hft==0)continue;
      if(fabs(m_phi-s_phi)>TMath::Pi()){
        if(m_phi<0)m_phi+=2*TMath::Pi();
        if(s_phi<0)s_phi+=2*TMath::Pi();
      }
      int bin = B_Weights->FindBin(s_parentpt);
      double weight =B_Weights->GetBinContent(bin);
      //double weight =  B_pp200_fonll->Eval(s_pt);///B_pp200_fonll->Integral(0,100);
      dcapt_b0->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt,weight);
      dcapt_lin_b0->Fill(fabs(s_dcaxy),s_pt,weight);
      phipt_b0->Fill((m_phi-s_phi),s_pt,weight);
      cosphipt_b0->Fill(cos(2*(m_phi-s_phi)),s_pt,weight);
      pt2D_b0->Fill(s_pt,s_parentpt,weight);
    }
    ch6->SetBranchAddress("phi",&m_phi);
    ch6->SetBranchAddress("eRPhi",&s_phi);
    ch6->SetBranchAddress("eRPt",&s_pt);
    ch6->SetBranchAddress("eREta",&s_eta);
    ch6->SetBranchAddress("eRDca",&s_dcaxy);
    ch6->SetBranchAddress("pid",&s_parentid);
    ch6->SetBranchAddress("eTpc",&s_tpc);
    ch6->SetBranchAddress("eHft",&s_hft);
    ch6->SetBranchAddress("pt",&s_parentpt);
    for(int i=0;i<ch6->GetEntries();i++){
      ch6->GetEntry(i);
      if(i%1000000==0)cout << "on " << i << " of " << ch6->GetEntries() << endl;
      if(fabs(s_eta)>0.7)continue;
      if(!(fabs(s_parentid)==521))continue;
      if(s_tpc*s_hft==0)continue;
      if(fabs(m_phi-s_phi)>TMath::Pi()){
        if(m_phi<0)m_phi+=2*TMath::Pi();
        if(s_phi<0)s_phi+=2*TMath::Pi();
      }
      int bin = B_Weights->FindBin(s_parentpt);
      double weight =B_Weights->GetBinContent(bin);
      //double weight = B_pp200_fonll->Eval(s_pt);///B_pp200_fonll->Integral(0,100);
      dcapt_bp->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt,weight);
      dcapt_lin_bp->Fill(fabs(s_dcaxy),s_pt,weight);
      phipt_bp->Fill((m_phi-s_phi),s_pt,weight);
      cosphipt_bp->Fill(cos(2*(m_phi-s_phi)),s_pt,weight);
      pt2D_bp->Fill(s_pt,s_parentpt,weight);
    }
    ch55->SetBranchAddress("phi",&m_phi);
    ch55->SetBranchAddress("eRPhi",&s_phi);
    ch55->SetBranchAddress("eRPt",&s_pt);
    ch55->SetBranchAddress("eREta",&s_eta);
    ch55->SetBranchAddress("eRDca",&s_dcaxy);
    ch55->SetBranchAddress("pid",&s_parentid);
    ch55->SetBranchAddress("eTpc",&s_tpc);
    ch55->SetBranchAddress("eHft",&s_hft);
    ch55->SetBranchAddress("pt",&s_parentpt);
    for(int i=0;i<ch55->GetEntries();i++){
      ch55->GetEntry(i);
      if(i%1000000==0)cout << "on " << i << " of " << ch55->GetEntries() << endl;
      if(fabs(s_eta)>0.7)continue;
      if(!(fabs(s_parentid)==531))continue;
      if(s_tpc*s_hft==0)continue;
      if(fabs(m_phi-s_phi)>TMath::Pi()){
        if(m_phi<0)m_phi+=2*TMath::Pi();
        if(s_phi<0)s_phi+=2*TMath::Pi();
      }
      int bin = B_Weights->FindBin(s_parentpt);
      double weight =B_Weights->GetBinContent(bin);
      //double weight =  B_pp200_fonll->Eval(s_pt);///B_pp200_fonll->Integral(0,100);
      dcapt_bs->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt,weight);
      dcapt_lin_bs->Fill(fabs(s_dcaxy),s_pt,weight);
      phipt_bs->Fill((m_phi-s_phi),s_pt,weight);
      cosphipt_bs->Fill(cos(2*(m_phi-s_phi)),s_pt,weight);
      pt2D_bs->Fill(s_pt,s_parentpt,weight);
    }
    ch66->SetBranchAddress("phi",&m_phi);
    ch66->SetBranchAddress("eRPhi",&s_phi);
    ch66->SetBranchAddress("eRPt",&s_pt);
    ch66->SetBranchAddress("eREta",&s_eta);
    ch66->SetBranchAddress("eRDca",&s_dcaxy);
    ch66->SetBranchAddress("pid",&s_parentid);
    ch66->SetBranchAddress("eTpc",&s_tpc);
    ch66->SetBranchAddress("eHft",&s_hft);
    ch66->SetBranchAddress("pt",&s_parentpt);
    for(int i=0;i<ch66->GetEntries();i++){
      ch66->GetEntry(i);
      if(i%1000000==0)cout << "on " << i << " of " << ch66->GetEntries() << endl;
      if(fabs(s_eta)>0.7)continue;
      if(!(fabs(s_parentid)==5122))continue;
      if(s_tpc*s_hft==0)continue;
      if(fabs(m_phi-s_phi)>TMath::Pi()){
        if(m_phi<0)m_phi+=2*TMath::Pi();
        if(s_phi<0)s_phi+=2*TMath::Pi();
      }
      int bin = B_Weights->FindBin(s_parentpt);
      if(s_parentpt>=4)double weight = B_Weights->GetBinContent(bin)*gr_lb->Eval(s_parentpt,0,"S")*2.;
      if(s_parentpt<4)double weight = B_Weights->GetBinContent(bin)*gr_lb->Eval(4,0,"S")*2.;
      //double weight = B_pp200_fonll->Eval(s_pt);///B_pp200_fonll->Integral(0,100);
      dcapt_lb->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt,weight);
      dcapt_lin_lb->Fill(fabs(s_dcaxy),s_pt,weight);
      phipt_lb->Fill((m_phi-s_phi),s_pt,weight);
      cosphipt_lb->Fill(cos(2*(m_phi-s_phi)),s_pt,weight);
      pt2D_lb->Fill(s_pt,s_parentpt,weight);
    }
    ch7->SetBranchAddress("phi",&m_phi);
    ch7->SetBranchAddress("eRPhi",&s_phi);
    ch7->SetBranchAddress("eRPt",&s_pt);
    ch7->SetBranchAddress("eREta",&s_eta);
    ch7->SetBranchAddress("eRDca",&s_dcaxy);
    ch7->SetBranchAddress("pid",&s_parentid);
    ch7->SetBranchAddress("eTpc",&s_tpc);
    ch7->SetBranchAddress("eHft",&s_hft);
    ch7->SetBranchAddress("pt",&s_parentpt);
    for(int i=0;i<ch7->GetEntries();i++){
      ch7->GetEntry(i);
      if(i%1000000==0)cout << "on " << i << " of " << ch7->GetEntries() << endl;
      if(fabs(s_eta)>0.7)continue;
      if(!(fabs(s_parentid)==411))continue;
      if(s_tpc*s_hft==0)continue;
      if(s_parentpt<0.315)s_parentpt=0.315;
      if(fabs(m_phi-s_phi)>TMath::Pi()){
        if(m_phi<0)m_phi+=2*TMath::Pi();
        if(s_phi<0)s_phi+=2*TMath::Pi();
      }
      int bin = D_Weights->FindBin(s_parentpt);
      double weight =D_Weights->GetBinContent(bin);
      //weight*=10E6;
      //double weight =  D_pp200_fonll->Eval(s_pt);///D_pp200_fonll->Integral(0,100);
      dcapt_dp->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt,weight);
      dcapt_lin_dp->Fill(fabs(s_dcaxy),s_pt,weight);
      phipt_dp->Fill((m_phi-s_phi),s_pt,weight);
      cosphipt_dp->Fill(cos(2*(m_phi-s_phi)),s_pt,weight);
      pt2D_dp->Fill(s_pt,s_parentpt,weight);
    }
    ch8->SetBranchAddress("phi",&m_phi);
    ch8->SetBranchAddress("eRPhi",&s_phi);
    ch8->SetBranchAddress("eRPt",&s_pt);
    ch8->SetBranchAddress("eREta",&s_eta);
    ch8->SetBranchAddress("eRDca",&s_dcaxy);
    ch8->SetBranchAddress("pid",&s_parentid);
    ch8->SetBranchAddress("eTpc",&s_tpc);
    ch8->SetBranchAddress("eHft",&s_hft);
    ch8->SetBranchAddress("pt",&s_parentpt);
    for(int i=0;i<ch8->GetEntries();i++){
      ch8->GetEntry(i);
      if(i%1000000==0)cout << "on " << i << " of " << ch8->GetEntries() << endl;
      if(fabs(s_eta)>0.7)continue;
      if(!(fabs(s_parentid)==421))continue;
      if(s_tpc*s_hft==0)continue;
      if(s_parentpt<0.315)s_parentpt=0.315;
      if(fabs(m_phi-s_phi)>TMath::Pi()){
        if(m_phi<0)m_phi+=2*TMath::Pi();
        if(s_phi<0)s_phi+=2*TMath::Pi();
      }
      int bin = D_Weights->FindBin(s_parentpt);
      double weight =D_Weights->GetBinContent(bin);
      //weight*=10E6;
      //double weight =  D_pp200_fonll->Eval(s_pt);///D_pp200_fonll->Integral(0,100);
      dcapt_d0->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt,weight);
      dcapt_lin_d0->Fill(fabs(s_dcaxy),s_pt,weight);
      phipt_d0->Fill((m_phi-s_phi),s_pt,weight);
      cosphipt_d0->Fill(cos(2*(m_phi-s_phi)),s_pt,weight);
      pt2D_d0->Fill(s_pt,s_parentpt,weight);
    }
    ch77->SetBranchAddress("phi",&m_phi);
    ch77->SetBranchAddress("eRPhi",&s_phi);
    ch77->SetBranchAddress("eRPt",&s_pt);
    ch77->SetBranchAddress("eREta",&s_eta);
    ch77->SetBranchAddress("eRDca",&s_dcaxy);
    ch77->SetBranchAddress("pid",&s_parentid);
    ch77->SetBranchAddress("eTpc",&s_tpc);
    ch77->SetBranchAddress("eHft",&s_hft);
    ch77->SetBranchAddress("pt",&s_parentpt);
    for(int i=0;i<ch77->GetEntries();i++){
      ch77->GetEntry(i);
      if(i%1000000==0)cout << "on " << i << " of " << ch77->GetEntries() << endl;
      if(fabs(s_eta)>0.7)continue;
      if(!(fabs(s_parentid)==431))continue;
      if(s_tpc*s_hft==0)continue;
      if(s_parentpt<0.315)s_parentpt=0.315;
      if(fabs(m_phi-s_phi)>TMath::Pi()){
        if(m_phi<0)m_phi+=2*TMath::Pi();
        if(s_phi<0)s_phi+=2*TMath::Pi();
      }
      int bin = D_Weights->FindBin(s_parentpt);
      double weight =D_Weights->GetBinContent(bin);
      //weight*=10E6;
      //double weight =  D_pp200_fonll->Eval(s_pt);///D_pp200_fonll->Integral(0,100);
      dcapt_ds->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt,weight);
      dcapt_lin_ds->Fill(fabs(s_dcaxy),s_pt,weight);
      phipt_ds->Fill((m_phi-s_phi),s_pt,weight);
      cosphipt_ds->Fill(cos(2*(m_phi-s_phi)),s_pt,weight);
      pt2D_ds->Fill(s_pt,s_parentpt,weight);
    }
    ch88->SetBranchAddress("phi",&m_phi);
    ch88->SetBranchAddress("eRPhi",&s_phi);
    ch88->SetBranchAddress("eRPt",&s_pt);
    ch88->SetBranchAddress("pt",&m_pt);
    ch88->SetBranchAddress("eREta",&s_eta);
    ch88->SetBranchAddress("eRDca",&s_dcaxy);
    ch88->SetBranchAddress("pid",&s_parentid);
    ch88->SetBranchAddress("eTpc",&s_tpc);
    ch88->SetBranchAddress("eHft",&s_hft);
    ch88->SetBranchAddress("pt",&s_parentpt);
    for(int i=0;i<ch88->GetEntries();i++){
      ch88->GetEntry(i);
      if(i%1000000==0)cout << "on " << i << " of " << ch88->GetEntries() << endl;
      if(fabs(s_eta)>0.7)continue;
      if(!(fabs(s_parentid)==4122))continue;
      if(s_tpc*s_hft==0)continue;
      if(s_parentpt<0.315)s_parentpt=0.315;
      if(fabs(m_phi-s_phi)>TMath::Pi()){
        if(m_phi<0)m_phi+=2*TMath::Pi();
        if(s_phi<0)s_phi+=2*TMath::Pi();
      }
      int bin = D_Weights->FindBin(s_parentpt);
      if(s_parentpt<=6.3)double weight =D_Weights->GetBinContent(bin)*gr_lc->Eval(s_parentpt,0,"S");
      if(s_parentpt>6.3)double weight =D_Weights->GetBinContent(bin)*gr_lc->Eval(6.3,0,"S");
      //weight*=10E6;
      //double weight =  D_pp200_fonll->Eval(s_pt)*gr_lc->Eval(m_pt,0,"S");///D_pp200_fonll->Integral(0,100);
      dcapt_lc->Fill(log10(fabs(s_dcaxy)+0.000000001),s_pt,weight);
      dcapt_lin_lc->Fill(fabs(s_dcaxy),s_pt,weight);
      phipt_lc->Fill((m_phi-s_phi),s_pt,weight);
      cosphipt_lc->Fill(cos(2*(m_phi-s_phi)),s_pt,weight);
      pt2D_lc->Fill(s_pt,s_parentpt,weight);
    }
    
    /*num_d0 = dcapt_d0->Integral();
     num_dp = dcapt_dp->Integral();
     num_ds = dcapt_ds->Integral();
     num_lc = dcapt_lc->Integral();
     num_b0 = dcapt_b0->Integral();
     num_bp = dcapt_bp->Integral();
     num_bs = dcapt_bs->Integral();
     num_lb = dcapt_lb->Integral();  */
    
    double d0_sl = 0.0649;
    double dp_sl = 0.1607 * num_d0/num_dp;
    double ds_sl = 0.065 * num_d0/num_ds;
    double lc_sl = 0.045 * num_d0/num_lc;
    
    double d0_cs = 41;
    double dp_cs = 18-3.1;//41.*0.35.;//18;
    double ds_cs = 15;//0.4*41;//15;
    double lc_cs = 69; //Already has fraction relataive to  d0
    
    double b0_sl = 0.1030;
    double bp_sl = 0.1108 * num_b0/num_bp;
    double bs_sl = 0.1024 * num_b0/num_bs;
    double lb_sl = 0.1026 * num_b0/num_lb;
    
    double b0_cs = 1;
    double bp_cs = 1;
    double bs_cs = 0.122*2;
    double lb_cs = 1;//0.255;//Already has fraction relataive to  b0
    
    dcapt_d_all->Add(dcapt_d0,1);
    dcapt_d_all->Add(dcapt_dp,dp_sl/d0_sl * dp_cs/d0_cs); // 不需要把D0 和B0 相加的时候，就不需要管两个之间的比值
    dcapt_d_all->Add(dcapt_ds,ds_sl/d0_sl * ds_cs/d0_cs);
    dcapt_d_all->Add(dcapt_lc,lc_sl/d0_sl * lc_cs/d0_cs);
    
    dcapt_b_all->Add(dcapt_b0,1);
    dcapt_b_all->Add(dcapt_bp,bp_sl/b0_sl * bp_cs/b0_cs);
    dcapt_b_all->Add(dcapt_bs,bs_sl/b0_sl * bs_cs/b0_cs);
    dcapt_b_all->Add(dcapt_lb,lb_sl/b0_sl * lb_cs/b0_cs);
    
    phipt_d_all->Add(phipt_d0,1);
    phipt_d_all->Add(phipt_dp,dp_sl/d0_sl * dp_cs/d0_cs);
    phipt_d_all->Add(phipt_ds,ds_sl/d0_sl * ds_cs/d0_cs);
    phipt_d_all->Add(phipt_lc,lc_sl/d0_sl * lc_cs/d0_cs);
    
    phipt_b_all->Add(phipt_b0,1);
    phipt_b_all->Add(phipt_bp,bp_sl/b0_sl * bp_cs/b0_cs);
    phipt_b_all->Add(phipt_bs,bs_sl/b0_sl * bs_cs/b0_cs);
    phipt_b_all->Add(phipt_lb,lb_sl/b0_sl * lb_cs/b0_cs);
    
    cosphipt_d_all->Add(cosphipt_d0,1);
    cosphipt_d_all->Add(cosphipt_dp,dp_sl/d0_sl * dp_cs/d0_cs);
    cosphipt_d_all->Add(cosphipt_ds,ds_sl/d0_sl * ds_cs/d0_cs);
    cosphipt_d_all->Add(cosphipt_lc,lc_sl/d0_sl * lc_cs/d0_cs);
    
    cosphipt_b_all->Add(cosphipt_b0,1);
    cosphipt_b_all->Add(cosphipt_bp,bp_sl/b0_sl * bp_cs/b0_cs);
    cosphipt_b_all->Add(cosphipt_bs,bs_sl/b0_sl * bs_cs/b0_cs);
    cosphipt_b_all->Add(cosphipt_lb,lb_sl/b0_sl * lb_cs/b0_cs);
    
    
    
    dcapt_lin_d_all->Add(dcapt_lin_d0,1);
    dcapt_lin_d_all->Add(dcapt_lin_dp,dp_sl/d0_sl * dp_cs/d0_cs);
    dcapt_lin_d_all->Add(dcapt_lin_ds,ds_sl/d0_sl * ds_cs/d0_cs);
    dcapt_lin_d_all->Add(dcapt_lin_lc,lc_sl/d0_sl * lc_cs/d0_cs);
    
    dcapt_lin_b_all->Add(dcapt_lin_b0,1);
    dcapt_lin_b_all->Add(dcapt_lin_bp,bp_sl/b0_sl * bp_cs/b0_cs);
    dcapt_lin_b_all->Add(dcapt_lin_bs,bs_sl/b0_sl * bs_cs/b0_cs);
    dcapt_lin_b_all->Add(dcapt_lin_lb,lb_sl/b0_sl * lb_cs/b0_cs);
    
    TFile * f= new TFile("root/HF_plots_LowDp.root","RECREATE");
    dcapt_d_all->Write("dcapt_d_all");
    dcapt_b_all->Write("dcapt_b_all");
    
    pt2D_d0->Write("pt2D_d0");
    pt2D_b0->Write("pt2D_b0");
    pt2D_dp->Write("pt2D_dp");
    pt2D_bp->Write("pt2D_bp");
    pt2D_ds->Write("pt2D_ds");
    pt2D_bs->Write("pt2D_bs");
    pt2D_lc->Write("pt2D_lc");
    pt2D_lb->Write("pt2D_lb");
    
    dcapt_d0->Write("dcapt_d0");
    dcapt_b0->Write("dcapt_b0");
    dcapt_dp->Write("dcapt_dp");
    dcapt_bp->Write("dcapt_bp");
    dcapt_ds->Write("dcapt_ds");
    dcapt_bs->Write("dcapt_bs");
    dcapt_lc->Write("dcapt_lc");
    dcapt_lb->Write("dcapt_lb");
    
    phipt_d_all->Write("phipt_d_all");
    phipt_b_all->Write("phipt_b_all");
    phipt_d0->Write("phipt_d0");
    phipt_b0->Write("phipt_b0");
    phipt_dp->Write("phipt_dp");
    phipt_bp->Write("phipt_bp");
    phipt_ds->Write("phipt_ds");
    phipt_bs->Write("phipt_bs");
    phipt_lc->Write("phipt_lc");
    phipt_lb->Write("phipt_lb");
    cosphipt_d_all->Write("cosphipt_d_all");
    cosphipt_b_all->Write("cosphipt_b_all");
    cosphipt_d0->Write("cosphipt_d0");
    cosphipt_b0->Write("cosphipt_b0");
    cosphipt_dp->Write("cosphipt_dp");
    cosphipt_bp->Write("cosphipt_bp");
    cosphipt_ds->Write("cosphipt_ds");
    cosphipt_bs->Write("cosphipt_bs");
    cosphipt_lc->Write("cosphipt_lc");
    cosphipt_lb->Write("cosphipt_lb");
    
    dcapt_lin_d_all->Write("dcapt_lin_d_all");
    dcapt_lin_b_all->Write("dcapt_lin_b_all");
    dcapt_lin_d0->Write("dcapt_lin_d0");
    dcapt_lin_b0->Write("dcapt_lin_b0");
    dcapt_lin_dp->Write("dcapt_lin_dp");
    dcapt_lin_bp->Write("dcapt_lin_bp");
    dcapt_lin_ds->Write("dcapt_lin_ds");
    dcapt_lin_bs->Write("dcapt_lin_bs");
    dcapt_lin_lc->Write("dcapt_lin_lc");
    dcapt_lin_lb->Write("dcapt_lin_lb");
    f->Close();
  }
  else{
    TFile * f= new TFile("root/HF_plots.root");
    dcapt_d_all=(TH2F*)f->Get("dcapt_d_all");
    dcapt_b_all=(TH2F*)f->Get("dcapt_b_all");
    dcapt_d0=(TH2F*)f->Get("dcapt_d0");
    dcapt_b0=(TH2F*)f->Get("dcapt_b0");
    dcapt_dp=(TH2F*)f->Get("dcapt_dp");
    dcapt_bp=(TH2F*)f->Get("dcapt_bp");
    dcapt_ds=(TH2F*)f->Get("dcapt_ds");
    dcapt_bs=(TH2F*)f->Get("dcapt_bs");
    dcapt_lc=(TH2F*)f->Get("dcapt_lc");
    dcapt_lb=(TH2F*)f->Get("dcapt_lb");
    
    phipt_d_all=(TH2F*)f->Get("phipt_d_all");
    phipt_b_all=(TH2F*)f->Get("phipt_b_all");
    phipt_d0=(TH2F*)f->Get("phipt_d0");
    phipt_b0=(TH2F*)f->Get("phipt_b0");
    phipt_dp=(TH2F*)f->Get("phipt_dp");
    phipt_bp=(TH2F*)f->Get("phipt_bp");
    phipt_ds=(TH2F*)f->Get("phipt_ds");
    phipt_bs=(TH2F*)f->Get("phipt_bs");
    phipt_lc=(TH2F*)f->Get("phipt_lc");
    phipt_lb=(TH2F*)f->Get("phipt_lb");
    
    dcapt_lin_d_all=(TH2F*)f->Get("dcapt_lin_d_all");
    dcapt_lin_b_all=(TH2F*)f->Get("dcapt_lin_b_all");
    dcapt_lin_d0=(TH2F*)f->Get("dcapt_lin_d0");
    dcapt_lin_b0=(TH2F*)f->Get("dcapt_lin_b0");
    dcapt_lin_dp=(TH2F*)f->Get("dcapt_lin_dp");
    dcapt_lin_bp=(TH2F*)f->Get("dcapt_lin_bp");
    dcapt_lin_ds=(TH2F*)f->Get("dcapt_lin_ds");
    dcapt_lin_bs=(TH2F*)f->Get("dcapt_lin_bs");
    dcapt_lin_lc=(TH2F*)f->Get("dcapt_lin_lc");
    dcapt_lin_lb=(TH2F*)f->Get("dcapt_lin_lb");
    
    dcapt_d_all->SetLineColor(kRed);
    dcapt_d_all->SetFillColor(kRed);
    dcapt_d_all->SetFillStyle(3007);
    dcapt_d_all->SetMarkerColor(kRed);
    dcapt_b_all->SetLineColor(kBlue);
    dcapt_b_all->SetFillColor(kBlue);
    dcapt_b_all->SetFillStyle(3006);
    dcapt_b_all->SetMarkerColor(kBlue);
    dcapt_d0->SetLineColor(kMagenta);
    dcapt_d0->SetMarkerColor(kMagenta);
    dcapt_dp->SetLineColor(kRed);
    dcapt_dp->SetMarkerColor(kRed);
    dcapt_ds->SetLineColor(kOrange);
    dcapt_ds->SetMarkerColor(kOrange);
    dcapt_lc->SetLineColor(1);
    dcapt_lc->SetMarkerColor(1);
    dcapt_b0->SetLineColor(kGreen-2);
    dcapt_b0->SetMarkerColor(kGreen-2);
    dcapt_bp->SetLineColor(kBlue);
    dcapt_bp->SetMarkerColor(kBlue);
    dcapt_bs->SetLineColor(kCyan+1);
    dcapt_bs->SetMarkerColor(kCyan+1);
    dcapt_lb->SetLineColor(51);
    dcapt_lb->SetMarkerColor(51);
    dcapt_lin_d_all->SetLineColor(kRed);
    dcapt_lin_d_all->SetMarkerColor(kRed);
    dcapt_lin_b_all->SetLineColor(kBlue);
    dcapt_lin_b_all->SetMarkerColor(kBlue);
    dcapt_lin_d0->SetLineColor(kMagenta);
    dcapt_lin_d0->SetMarkerColor(kMagenta);
    dcapt_lin_dp->SetLineColor(kRed);
    dcapt_lin_dp->SetMarkerColor(kRed);
    dcapt_lin_ds->SetLineColor(kOrange);
    dcapt_lin_ds->SetMarkerColor(kOrange);
    dcapt_lin_lc->SetLineColor(1);
    dcapt_lin_lc->SetMarkerColor(1);
    dcapt_lin_b0->SetLineColor(kGreen-2);
    dcapt_lin_b0->SetMarkerColor(kGreen-2);
    dcapt_lin_bp->SetLineColor(kBlue);
    dcapt_lin_bp->SetMarkerColor(kBlue);
    dcapt_lin_bs->SetLineColor(kCyan+1);
    dcapt_lin_bs->SetMarkerColor(kCyan+1);
    dcapt_lin_lb->SetLineColor(51);
    dcapt_lin_lb->SetMarkerColor(51);
    
    phipt_d_all->SetLineColor(kRed);
    phipt_d_all->SetMarkerColor(kRed);
    phipt_b_all->SetLineColor(kBlue);
    phipt_b_all->SetMarkerColor(kBlue);
    
    // ========== DCA plots
    double low = 2;
    double high = 2.5;
    phipt_d_all->GetYaxis()->SetRangeUser(low,high);
    phipt_b_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_d_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_b_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_d0->GetYaxis()->SetRangeUser(low,high);
    dcapt_b0->GetYaxis()->SetRangeUser(low,high);
    dcapt_dp->GetYaxis()->SetRangeUser(low,high);
    dcapt_bp->GetYaxis()->SetRangeUser(low,high);
    dcapt_ds->GetYaxis()->SetRangeUser(low,high);
    dcapt_bs->GetYaxis()->SetRangeUser(low,high);
    dcapt_lc->GetYaxis()->SetRangeUser(low,high);
    dcapt_lb->GetYaxis()->SetRangeUser(low,high);
    dca_d_all =(TH1F*)dcapt_d_all->ProjectionX();
    dca_b_all =(TH1F*)dcapt_b_all->ProjectionX();
    
    dca_d0 =(TH1F*)dcapt_d0->ProjectionX();
    dca_b0 =(TH1F*)dcapt_b0->ProjectionX();
    dca_dp =(TH1F*)dcapt_dp->ProjectionX();
    dca_bp =(TH1F*)dcapt_bp->ProjectionX();
    dca_ds =(TH1F*)dcapt_ds->ProjectionX();
    dca_bs =(TH1F*)dcapt_bs->ProjectionX();
    dca_lb =(TH1F*)dcapt_lb->ProjectionX();
    dca_lc =(TH1F*)dcapt_lc->ProjectionX();
    
    pt_d0 =(TH1F*)dcapt_d0->ProjectionY();
    pt_b0 =(TH1F*)dcapt_b0->ProjectionY();
    pt_dp =(TH1F*)dcapt_dp->ProjectionY();
    pt_bp =(TH1F*)dcapt_bp->ProjectionY();
    pt_ds =(TH1F*)dcapt_ds->ProjectionY();
    pt_bs =(TH1F*)dcapt_bs->ProjectionY();
    pt_lb =(TH1F*)dcapt_lb->ProjectionY();
    pt_lc =(TH1F*)dcapt_lc->ProjectionY();
    
    
    dcapt_lin_d_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_b_all->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_d0->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_b0->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_dp->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_bp->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_ds->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_bs->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_lc->GetYaxis()->SetRangeUser(low,high);
    dcapt_lin_lb->GetYaxis()->SetRangeUser(low,high);
    dca_lin_d_all =(TH1F*)dcapt_lin_d_all->ProjectionX();
    dca_lin_b_all =(TH1F*)dcapt_lin_b_all->ProjectionX();
    dca_lin_d0 =(TH1F*)dcapt_lin_d0->ProjectionX();
    dca_lin_b0 =(TH1F*)dcapt_lin_b0->ProjectionX();
    dca_lin_dp =(TH1F*)dcapt_lin_dp->ProjectionX();
    dca_lin_bp =(TH1F*)dcapt_lin_bp->ProjectionX();
    dca_lin_ds =(TH1F*)dcapt_lin_ds->ProjectionX();
    dca_lin_bs =(TH1F*)dcapt_lin_bs->ProjectionX();
    dca_lin_lb =(TH1F*)dcapt_lin_lb->ProjectionX();
    dca_lin_lc =(TH1F*)dcapt_lin_lc->ProjectionX();
    phi_d_all =(TH1F*)phipt_d_all->ProjectionX();
    phi_b_all =(TH1F*)phipt_b_all->ProjectionX();
    
    norm(phi_d_all);
    norm(phi_b_all);
    norm(dca_d_all);
    norm(dca_b_all);
    norm(dca_d0);
    norm(dca_b0);
    norm(dca_dp);
    norm(dca_bp);
    norm(dca_ds);
    norm(dca_bs);
    norm(dca_lc);
    norm(dca_lb);
    
    norm(dca_lin_d_all);
    norm(dca_lin_b_all);
    norm(dca_lin_d0);
    norm(dca_lin_b0);
    norm(dca_lin_dp);
    norm(dca_lin_bp);
    norm(dca_lin_ds);
    norm(dca_lin_bs);
    norm(dca_lin_lc);
    norm(dca_lin_lb);
    TLegend *leg1 = new TLegend(0.2,0.5,0.4,0.9);
    
    leg1->AddEntry(dca_d0,"#it{D}^{0}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_dp,"#it{D}^{+}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_ds,"#it{D}^{+}_{s}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_lc,"#it{#Lambda}^{+}_{c}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_b0,"#it{B}^{0}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_bp,"#it{B}^{+}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_bs,"#it{B}^{0}_{s}#rightarrow #it{e}X","l");
    leg1->AddEntry(dca_lb,"#it{#Lambda}^{0}_{b}#rightarrow #it{e}X","l");
    
    TCanvas *c1 = new TCanvas("c1","DCA Shapes");
    dca_d0->GetYaxis()->SetTitle("Arb. Units");
    dca_d0->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    dca_d0->GetXaxis()->SetRangeUser(-6,0);
    dca_b0->GetYaxis()->SetTitle("Arb. Units");
    dca_b0->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    dca_b0->GetXaxis()->SetRangeUser(-6,0);
    dca_d0->Draw("hist");
    dca_dp->Draw("same hist");
    dca_b0->Draw("same hist");
    dca_bp->Draw("same hist");
    dca_ds->Draw("same hist");
    dca_bs->Draw("same hist");
    dca_lc->Draw("same hist");
    dca_lb->Draw("same hist");
    leg1->Draw("same");
    //leg->Draw("same");
    //}
    c1->SaveAs("plots_HF/All_DCA_Shapes.pdf");
    
    TCanvas *c11 = new TCanvas("c11","charm Shapes");
    dca_d0->Draw("hist");
    dca_dp->Draw("same hist");
    dca_ds->Draw("same hist");
    dca_lc->Draw("same hist");
    c11->SaveAs("plots_HF/charm_Shapes.pdf");

    
    TCanvas *c111 = new TCanvas("c111","b Shapes");
    dca_b0->Draw("hist");
    dca_bp->Draw("same hist");
    dca_bs->Draw("same hist");
    dca_lb->Draw("same hist");
    c111->SaveAs("plots_HF/bottom_Shapes.pdf");

    
    TCanvas *c1111 = new TCanvas("c1111","Comb. Shapes");
    TLegend *leg = new TLegend(0.2,0.5,0.4,0.9);
    dca_b_all->SetFillStyle(3004);
    dca_d_all->SetFillStyle(3005);
    leg->AddEntry(dca_d_all,"#it{c}#rightarrow#it{e}X","l");
    leg->AddEntry(dca_b_all,"#it{b}#rightarrow#it{e}X","l");
    dca_d_all->GetYaxis()->SetTitle("Arb. Units");
    dca_d_all->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    dca_d_all->GetXaxis()->SetRangeUser(-6,0);
    dca_d_all->Draw("hist");
    dca_b_all->Draw("same hist");
    leg->Draw("same");
    c1111->SaveAs("plots_HF/Comb_Shapes.pdf");

    
    TCanvas *c2 = new TCanvas("c2","all lin Shapes");
    dca_lin_d_all->GetYaxis()->SetTitle("Arb. Units");
    dca_lin_d_all->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
    dca_lin_d_all->GetXaxis()->SetRangeUser(-6,0);
    dca_lin_d_all->Draw("hist");
    dca_lin_b_all->Draw("same hist");
    leg->Draw("same");
    c2->SaveAs("plots_HF/all_lin.pdf");

    
    TCanvas *c3 = new TCanvas("c3","phi res");
    phi_d_all->GetYaxis()->SetTitle("Arb. Units");
    phi_d_all->GetXaxis()->SetTitle("#Delta#phi");
    phi_d_all->GetXaxis()->SetRangeUser(-1,1);
    phi_d_all->Draw("hist");
    phi_b_all->Draw("same hist");
    leg->Draw("same");
    c3->SaveAs("plots_HF/delta_phi.pdf");

    
    double low = 0;
    double high = 8.5;
    dcapt_d0->GetYaxis()->SetRangeUser(low,high);
    dcapt_b0->GetYaxis()->SetRangeUser(low,high);
    dcapt_dp->GetYaxis()->SetRangeUser(low,high);
    dcapt_bp->GetYaxis()->SetRangeUser(low,high);
    dcapt_ds->GetYaxis()->SetRangeUser(low,high);
    dcapt_bs->GetYaxis()->SetRangeUser(low,high);
    dcapt_lc->GetYaxis()->SetRangeUser(low,high);
    dcapt_lb->GetYaxis()->SetRangeUser(low,high);
    pt_d0 =(TH1F*)dcapt_d0->ProjectionY();
    pt_b0 =(TH1F*)dcapt_b0->ProjectionY();
    pt_dp =(TH1F*)dcapt_dp->ProjectionY();
    pt_bp =(TH1F*)dcapt_bp->ProjectionY();
    pt_ds =(TH1F*)dcapt_ds->ProjectionY();
    pt_bs =(TH1F*)dcapt_bs->ProjectionY();
    pt_lb =(TH1F*)dcapt_lb->ProjectionY();
    pt_lc =(TH1F*)dcapt_lc->ProjectionY();
    
    
    TH1F *dpt_d_all = new TH1F("pt_d_all","pt_d_all",pt_d0->GetNbinsX(),0,8.5);pt_d_all->Sumw2();
    TH1F *dpt_b_all = new TH1F("pt_b_all","pt_b_all",pt_d0->GetNbinsX(),0,8.5);pt_b_all->Sumw2();
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    TH1F * charm_1 = new TH1F("charm_1","charm_1", numPtBins,binning);
    TH1F * bottom_1 = new TH1F("bottom_1","bottom_1", numPtBins,binning);
    TH1F * charm_2 = new TH1F("charm_2","charm_2", numPtBins,binning);
    TH1F * bottom_2 = new TH1F("bottom_2","bottom_2", numPtBins,binning);
    TH1F * charm_3 = new TH1F("charm_3","charm_3", numPtBins,binning);
    TH1F * bottom_3 = new TH1F("bottom_3","bottom_3", numPtBins,binning);
    TH1F * charm_4 = new TH1F("charm_4","charm_4", numPtBins,binning);
    TH1F * bottom_4 = new TH1F("bottom_4","bottom_4", numPtBins,binning);
    TH1F * charm_yield = new TH1F("charm_yield","charm_yield", numPtBins,binning);
    TH1F * bottom_yield = new TH1F("bottom_yield","bottom_yield", numPtBins,binning);
    
    double d0_sl = 0.0649;
    double dp_sl = 0.1607;
    double ds_sl = 0.065;
    double lc_sl = 0.045;
    double d0_cs = 41;
    double dp_cs = 18;//41./2.;//18;
    double ds_cs = 15;//0.4*41;//15;
    double lc_cs = 69;//41;
    
    double b0_sl = 0.1030;
    double bp_sl = 0.1108;
    double bs_sl = 0.1024;
    double lb_sl = 0.1026;
    double b0_cs = 1;
    double bp_cs = 1;
    double bs_cs = 0.122*2;
    double lb_cs = 1;
    double scale = 2.83609e+08/num_d0; // zyj???
    pt_d0->Scale(scale*d0_sl);
    pt_dp->Scale(dp_sl*dp_cs/d0_cs * num_d0/num_dp * scale); // pt spectrue for e decay channel???
    pt_ds->Scale(ds_sl*ds_cs/d0_cs * num_d0/num_ds * scale);
    pt_lc->Scale(lc_sl*lc_cs/d0_cs * num_d0/num_lc * scale);
    pt_d_all->Add(pt_d0);
    pt_d_all->Add(pt_dp);
    pt_d_all->Add(pt_ds);
    pt_d_all->Add(pt_lc);
    double forscale = 0.29;//num_d0*(1+num_dp/num_d0*0.5+num_ds/num_d0*0.4+num_lc/num_d0*69./41.) / (num_b0*(1+num_bp/num_b0+num_bs/num_d0*0.122+num_lb/num_b0*0.259)); // zyj charm and bottom hadron number??
    double scale1 = 2.83609e+08/forscale/137/num_b0*0.36; // zyj 137 *0.36????
    cout << "Scaling factors " << scale << " " << scale1 << endl;
    
    pt_b0->Scale(scale1*b0_sl);
    pt_bp->Scale(bp_sl*bp_cs/b0_cs * num_b0/num_bp * scale1);
    pt_bs->Scale(bs_sl*bs_cs/b0_cs * num_b0/num_bs * scale1);
    pt_lb->Scale(lb_sl*lb_cs/b0_cs * num_b0/num_lb * scale1);
    
    pt_b_all->Add(pt_b0);
    pt_b_all->Add(pt_bp);
    pt_b_all->Add(pt_bs);
    pt_b_all->Add(pt_lb);
    
    double finalScale = 1;//0.15;//pt_b_all->Integral()/pt_d_all->Integral();
    cout << "c/b scaling " << finalScale << endl;
    pt_b_all->Scale(finalScale);
    pt_b0->Scale(finalScale);
    pt_bp->Scale(finalScale);
    pt_bs->Scale(finalScale);
    pt_lb->Scale(finalScale);
    //=====================================================================================
    // frac. dist.
    
    double eff[9]={0.633673698548,  0.666336412584,  0.67659412964,   0.71909796477,   0.702890272245,  0.69985391904,   0.729281142186,  0.7624432562,    0.68022809943}; // HFT eff? how about TPC?
    for(int i =0;i<10;i++){
      int bin1 = pt_d0->FindBin(binning[i]);
      int bin2 = pt_d0->FindBin(binning[i+1]);
      double temp1 = pt_d0->Integral(bin1,bin2);
      double temp2 = pt_dp->Integral(bin1,bin2);
      double temp3 = pt_ds->Integral(bin1,bin2);
      double temp4 = pt_lc->Integral(bin1,bin2);
      double temp = (temp1+temp2+temp3+temp4);//zyj = pt_d_all->Integral(bin1,bin2);??
      charm_yield->SetBinContent(i+1,temp*eff[i]);
      if(temp>0)charm_yield->SetBinError(i+1,sqrt(1/(temp*eff[i]))); // zyj = pt_d_all* eff??
      charm_1->SetBinContent(i+1,temp1/temp);
      charm_2->SetBinContent(i+1,temp2/temp);
      charm_3->SetBinContent(i+1,temp3/temp);
      charm_4->SetBinContent(i+1,temp4/temp);
      temp1 = pt_b0->Integral(bin1,bin2);
      temp2 = pt_bp->Integral(bin1,bin2);
      temp3 = pt_bs->Integral(bin1,bin2);
      temp4 = pt_lb->Integral(bin1,bin2);
      temp = temp1+temp2+temp3+temp4;
      bottom_1->SetBinContent(i+1,temp1/temp);
      bottom_2->SetBinContent(i+1,temp2/temp);
      bottom_3->SetBinContent(i+1,temp3/temp);
      bottom_4->SetBinContent(i+1,temp4/temp);
      bottom_yield->SetBinContent(i+1,temp*eff[i]);
      if(temp>0)bottom_yield->SetBinError(i+1,sqrt(1/(temp*eff[i])));
    }
    TLegend *leg5 = new TLegend(0.6,0.7,0.9,0.9);
    leg5->AddEntry(charm_1,"D^{0}#rightarrow eX","l");
    leg5->AddEntry(charm_2,"D^{+}#rightarrow eX","l");
    leg5->AddEntry(charm_3,"D_{s}#rightarrow eX","l");
    leg5->AddEntry(charm_4,"#Lambda_{c}#rightarrow eX","l");
    TLegend *leg55 = new TLegend(0.6,0.7,0.9,0.9);
    leg55->AddEntry(bottom_1,"B^{0}#rightarrow eX","l");
    leg55->AddEntry(bottom_2,"B^{+}#rightarrow eX","l");
    leg55->AddEntry(bottom_3,"B_{s}#rightarrow eX","l");
    leg55->AddEntry(bottom_4,"#Lambda_{b}#rightarrow eX","l");
    
    charm_1->SetLineColor(kMagenta);
    charm_1->SetMarkerColor(kMagenta);
    charm_2->SetLineColor(kRed);
    charm_2->SetMarkerColor(kRed);
    charm_3->SetLineColor(kOrange);
    charm_3->SetMarkerColor(kOrange);
    charm_4->SetLineColor(1);
    charm_4->SetMarkerColor(1);
    bottom_1->SetLineColor(kGreen-2);
    bottom_1->SetMarkerColor(kGreen-2);
    bottom_2->SetLineColor(kBlue);
    bottom_2->SetMarkerColor(kBlue);
    bottom_3->SetLineColor(kCyan+1);
    bottom_3->SetMarkerColor(kCyan+1);
    bottom_4->SetLineColor(51);
    bottom_4->SetMarkerColor(51);
    TCanvas *c_c = new TCanvas("c_c","fracs",1000,500);
    c_c->Divide(2,1);
    c_c->cd(1);
    charm_1->GetYaxis()->SetRangeUser(0,1);
    charm_1->GetYaxis()->SetTitle("Relative Fraction");
    charm_1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    bottom_1->GetYaxis()->SetRangeUser(0,1);
    bottom_1->GetYaxis()->SetTitle("Relative Fraction");
    bottom_1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    charm_1->Draw("hist");
    charm_2->Draw("hist same");
    charm_3->Draw("hist same");
    charm_4->Draw("hist same");
    leg5->Draw("same");
    c_c->cd(2);
    bottom_1->Draw("hist");
    bottom_2->Draw("hist same");
    bottom_3->Draw("hist same");
    bottom_4->Draw("hist same");
    leg55->Draw("same");
    c_c->SaveAs("plots_HF/frac_pt.pdf");

    //=====================================================================================
    // pt dist.
    TCanvas *c_pt = new TCanvas("c_pt","pts",1000,500);
    c_pt->Divide(2,1);
    c_pt->cd(1);
    //pt_d0->GetYaxis()->SetRangeUser(0.001,2);
    pt_d0->GetYaxis()->SetTitle("Normalized dN/dp_{T}");
    pt_b0->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    //pt_b0->GetYaxis()->SetRangeUser(0.001,2);
    pt_b0->GetYaxis()->SetTitle("Normalized dN/dp_{T}");
    pt_b0->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    pt_d_all->SetLineColor(kGray+1);
    pt_d_all->SetLineStyle(7);
    pt_b_all->SetLineColor(kGray+1);
    pt_b_all->SetLineStyle(7);
    pt_d0->Draw("hist");
    pt_dp->Draw("hist same");
    pt_ds->Draw("hist same");
    pt_lc->Draw("hist same");
    pt_d_all->DrawClone("hist same");
    leg5->Draw("same");
    c_pt->cd(2);
    pt_b0->Draw("hist");
    pt_bp->Draw("hist same");
    pt_bs->Draw("hist same");
    pt_lb->Draw("hist same");
    pt_b_all->DrawClone("hist same");
    leg55->Draw("same");
    c_pt->SaveAs("plots_HF/pt.pdf");

    //=====================================================================================
    // all pt dist.
    TCanvas *c22 = new TCanvas("c22","all pt Shapes");
    //norm(pt_b_all);
    //norm(pt_d_all);
    pt_d_all->SetLineColor(kRed);
    pt_b_all->SetLineColor(kBlue);
    pt_d_all->Draw("hist");
    pt_b_all->DrawClone("same hist");
    c22->SaveAs("plots_HF/all_pt.pdf");

    //=====================================================================================
    // b frac. dist.
    for(int i = 1 ;i<pt_b_all->GetNbinsX()+1;i++){
      double temp1 = pt_b_all->GetBinContent(i);
      double temp2 = pt_d_all->GetBinContent(i);
      if(temp1>0)pt_b_all->SetBinContent(i,temp1/(temp1+temp2));
      else pt_b_all->SetBinContent(i,0);
      pt_b_all->SetBinError(i,0);
    }
    TCanvas *c222 = new TCanvas("c222","pt ratio Shapes");
    pt_b_all->Draw("PE");
    c222->SaveAs("plots_HF/b_c_ratio.pdf");

    
    //=====================================================================================
    // yield * eff. dist.
    TCanvas *cy = new TCanvas("cy","expected yield");
    charm_yield->GetXaxis()->SetTitle("p_{T} [GeV]");
    charm_yield->GetYaxis()->SetTitle("Raw Yield");
    charm_yield->SetLineColor(kRed);
    charm_yield->SetMarkerColor(kRed);
    bottom_yield->SetLineColor(kBlue);
    bottom_yield->SetMarkerColor(kBlue);
    charm_yield->Draw("same");
    bottom_yield->Draw("same");
    cy->SaveAs("plots_HF/yield.pdf");
  }
}

void norm(TH1F *h){
  h->Rebin(4);
  double norm1 = h->Integral();
  int bins = h->GetNbinsX();
  for(int i=1; i<bins+1;i++){
    double temp = h->GetBinContent(i);
    double err = h->GetBinError(i);
    h->SetBinContent(i,temp/norm1);
    h->SetBinError(i,err/norm1);
  }
}


