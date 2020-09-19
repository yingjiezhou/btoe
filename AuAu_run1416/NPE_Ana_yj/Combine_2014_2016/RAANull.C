#include "hfProdTree.h"
void RAANull(){
    gROOT->ProcessLine(".x ~/myStyle.C");
    TGaxis::SetMaxDigits(3);
    
    TFile *MyBWeights = new TFile("../NPE_MC/Ana/root/B_Weights.root","READ");
    //TH1F* D_Weights = MyBWeights->Get("B_Weights");D_Weights->SetName("D_Weights");                                                                                                                         
    TH1F* B_Weights = MyBWeights->Get("B_Weights");
    TFile *MyDWeights = new TFile("../NPE_MC/Ana/D_Weights_FONLL.root","READ");
    TH1F* D_Weights = MyDWeights->Get("D_Weights");
    TFile *D0RAA = new TFile("D0RAA_Run14HFT.root");
    D0_RAA_pperr_0_80 = (TGraphAsymmErrors *)D0RAA->Get("D0_RAA_pperr_0_80");
    
    double lc_x[14]={0.11344,0.49159,0.99579,1.5,2.0042,2.5084, 3,3.5042,3.9958,4.5,5.0042,5.5084,6,6.30252};
    double lc_y[14]={1.06143,1.10996,1.25051,1.44071,1.59913,1.62314,1.4843,1.21379,0.942128,0.725841,0.580436,0.511373,0.481779,0.464159};
    TGraph *gr_lc = new TGraph(14,lc_x,lc_y);
    
    double lb_x[14]={4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,15,17,19,22.5};
    double lb_y[14]={0.324,0.281,0.257,0.245,0.210,0.194,0.191,0.172,0.159,0.165,0.136,0.126,0.109};
    TGraph *gr_lb = new TGraph(14,lb_x,lb_y);

    TH2F *pt2D_b_all = new TH2F("pt2D_b_all","pt2D_b_all",200,0,20,200,0,20);pt2D_b_all->Sumw2();
    TH2F *pt2D_d_all = new TH2F("pt2D_d_all","pt2D_d_all",200,0,20,200,0,20);pt2D_d_all->Sumw2();
    TH2F *pt2D_d0 = new TH2F("pt2D_d0","pt2D_d0",200,0,20,200,0,20);pt2D_d0->Sumw2();
    TH2F *pt2D_dp = new TH2F("pt2D_dp","pt2D_dp",200,0,20,200,0,20);pt2D_dp->Sumw2();
    TH2F *pt2D_ds = new TH2F("pt2D_ds","pt2D_ds",200,0,20,200,0,20);pt2D_ds->Sumw2();
    TH2F *pt2D_lc = new TH2F("pt2D_lc","pt2D_lc",200,0,20,200,0,20);pt2D_lc->Sumw2();
    TH2F *pt2D_b0 = new TH2F("pt2D_b0","pt2D_b0",200,0,20,200,0,20);pt2D_b0->Sumw2();
    TH2F *pt2D_bp = new TH2F("pt2D_bp","pt2D_bp",200,0,20,200,0,20);pt2D_bp->Sumw2();
    TH2F *pt2D_bs = new TH2F("pt2D_bs","pt2D_bs",200,0,20,200,0,20);pt2D_bs->Sumw2();
    TH2F *pt2D_lb = new TH2F("pt2D_lb","pt2D_lb",200,0,20,200,0,20);pt2D_lb->Sumw2();
    TH2F *pt2D_b_all_raa = new TH2F("pt2D_b_all_raa","pt2D_b_all_raa",200,0,20,200,0,20);pt2D_b_all_raa->Sumw2();
    TH2F *pt2D_d_all_raa = new TH2F("pt2D_d_all_raa","pt2D_d_all_raa",200,0,20,200,0,20);pt2D_d_all_raa->Sumw2();
    TH2F *pt2D_d0_raa = new TH2F("pt2D_d0_raa","pt2D_d0_raa",200,0,20,200,0,20);pt2D_d0_raa->Sumw2();
    TH2F *pt2D_dp_raa = new TH2F("pt2D_dp_raa","pt2D_dp_raa",200,0,20,200,0,20);pt2D_dp_raa->Sumw2();
    TH2F *pt2D_ds_raa = new TH2F("pt2D_ds_raa","pt2D_ds_raa",200,0,20,200,0,20);pt2D_ds_raa->Sumw2();
    TH2F *pt2D_lc_raa = new TH2F("pt2D_lc_raa","pt2D_lc_raa",200,0,20,200,0,20);pt2D_lc_raa->Sumw2();
    TH2F *pt2D_b0_raa = new TH2F("pt2D_b0_raa","pt2D_b0_raa",200,0,20,200,0,20);pt2D_b0_raa->Sumw2();
    TH2F *pt2D_bp_raa = new TH2F("pt2D_bp_raa","pt2D_bp_raa",200,0,20,200,0,20);pt2D_bp_raa->Sumw2();
    TH2F *pt2D_bs_raa = new TH2F("pt2D_bs_raa","pt2D_bs_raa",200,0,20,200,0,20);pt2D_bs_raa->Sumw2();
    TH2F *pt2D_lb_raa = new TH2F("pt2D_lb_raa","pt2D_lb_raa",200,0,20,200,0,20);pt2D_lb_raa->Sumw2();


    TFile *f = new TFile("/star/data01/pwg/yjzhou19/Non-flow/npeHadronPhiCorr_rcf_charm/output/NpeCHcorr_r808pT1_100.root");
    TTree *tree;
    tree = (TTree*)f->Get("hfProdTree");
    hfProdTree *hfSimTree = new hfProdTree(tree);

    int nevents = (int)tree->GetEntries();
    cout << "== Total Events : " << nevents << endl;

    //loop event                                                                                                                                                                                                  
    for(int iEvent=0; iEvent<nevents; iEvent++) {
	if(!(iEvent%100))cout << "Begin " << iEvent << "th entry...." << endl;
	hfSimTree->GetEntry(iEvent);
	int numOfHadrons = hfSimTree->Hadrons_;
	for(int iBH=0; iBH<numOfHadrons; iBH++) {

	    int pdgCode = hfSimTree->Hadrons_idSave[iBH];
	    int mID = pdgCode;
	    if(mID==411 || mID==511 || mID==421 || mID==521 || mID==431)cout << "here " << endl;
	    if(fabs(pdgCode)!=11)continue;
	    TVector3 pSave(hfSimTree->Hadrons_pSave_xx[iBH], hfSimTree->Hadrons_pSave_yy[iBH], hfSimTree->Hadrons_pSave_zz[iBH]);
	    if( fabs(pSave.Eta())>0.7) continue;
	    int mindx = hfSimTree->Hadrons_mother1Save[iBH];
	    int mindx2 = hfSimTree->Hadrons_mother2Save[iBH];
	    if(mindx2>0)continue;
	    if(numOfHadrons<mindx)continue;
	    int mID = fabs(hfSimTree->Hadrons_idSave[mindx]);
	    if(mID!=411 && mID!=511 && mID!=421 && mID!=521 && mID!=431 && mID!=531 && mID!=4122 && mID!=5122) continue;
	    cout << "Made it "<<endl;
	    TVector3 mSave(hfSimTree->Hadrons_pSave_xx[mindx], hfSimTree->Hadrons_pSave_yy[mindx], hfSimTree->Hadrons_pSave_zz[mindx]);
	   
	    double ww = D0_RAA_pperr_0_80->Eval(mSave.Perp());
	    
	    if(mID==411){
		pt2D_dp->Fill(pSave.Perp(),mSave.Perp());
		pt2D_dp_raa->Fill(pSave.Perp(),mSave.Perp(),ww);
	    }
	    else if(mID==421){
                pt2D_d0->Fill(pSave.Perp(),mSave.Perp());
		pt2D_d0_raa->Fill(pSave.Perp(),mSave.Perp(),ww);
            }
	    else if(mID==431){
                pt2D_ds->Fill(pSave.Perp(),mSave.Perp());
		pt2D_ds_raa->Fill(pSave.Perp(),mSave.Perp(),ww);
            }
	    else if(mID==4122){
		if(s_parentpt<6.3)ww*=gr_lc->Eval(mSave.Perp(),0,"S");
		else ww*=gr_lc->Eval(6.3,0,"S");
                pt2D_lc->Fill(pSave.Perp(),mSave.Perp());
		pt2D_lc_raa->Fill(pSave.Perp(),mSave.Perp(),ww);
            }
	    else if(mID==511){
                pt2D_b0->Fill(pSave.Perp(),mSave.Perp());
		pt2D_b0_raa->Fill(pSave.Perp(),mSave.Perp(),ww);
            }
            else if(mID==521){
		pt2D_bp->Fill(pSave.Perp(),mSave.Perp());
		pt2D_bp_raa->Fill(pSave.Perp(),mSave.Perp(),ww);
            }
            else if(mID==531){
		pt2D_ds->Fill(pSave.Perp(),mSave.Perp());
		pt2D_ds_raa->Fill(pSave.Perp(),mSave.Perp(),ww);
            }
            else if(mID==5122){
		if(s_parentpt<6.3)ww*=gr_lc->Eval(mSave.Perp(),0,"S");
		else ww*=gr_lc->Eval(6.3,0,"S");
		pt2D_lb->Fill(pSave.Perp(),mSave.Perp());
		pt2D_lb_raa->Fill(pSave.Perp(),mSave.Perp(),ww);
            }
	}
    }
    TFile * f= new TFile("root/HF_RAA.root","RECREATE");
    pt2D_d_all->Write("pt2D_d_all");
    pt2D_b_all->Write("pt2D_b_all");
    pt2D_d_all_raa->Write("pt2D_d_all_raa");
    pt2D_b_all_raa->Write("pt2D_b_all_raa");
    pt2D_b0->Write();
    pt2D_bp->Write();
    pt2D_bs->Write();
    pt2D_lb->Write();
    pt2D_d0->Write();
    pt2D_dp->Write();
    pt2D_ds->Write();
    pt2D_lc->Write();
    pt2D_b0_raa->Write();
    pt2D_bp_raa->Write();
    pt2D_bs_raa->Write();
    pt2D_lb_raa->Write();
    pt2D_d0_raa->Write();
    pt2D_dp_raa->Write();
    pt2D_ds_raa->Write();
    pt2D_lc_raa->Write();
    f->Close();

}
