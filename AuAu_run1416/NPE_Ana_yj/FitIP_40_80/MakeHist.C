void MakeHist(int save=1){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    gStyle->SetPalette(56);
//////////////////////////////////////////////////////////////////
    char dFile[500];
    sprintf(dFile,"/Volumes/YJMAC/matt_production/NPE_Tuples_TuneB12.root");
    TFile *f_D = new TFile(dFile);
    auto ch2 = (TChain*) f_D->Get("Signal");

    float centrality;
    float dca;
    float phi;
    float triggercat;
    float mva;
    float pt;
    float p;
    float eta;
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  
    auto hDcaLog3D_5  = new TH2F ("hDcaLog3D_5","hDcaLog3D_5",200,0,20,600,-6,0);
    auto hDcaLog3D_1  = new TH2F ("hDcaLog3D_1","hDcaLog3D_1",200,0,20,600,-6,0);
    int loop = 0;
    float px;
    float py;
    float iso;
    ch2 -> SetBranchAddress( "sig_mva" , &mva );
    ch2 -> SetBranchAddress( "sig_eta" , &eta );
    ch2 -> SetBranchAddress( "sig_pt" , &pt );
    ch2 -> SetBranchAddress( "sig_dca" , &dca );
    ch2 -> SetBranchAddress( "sig_phi" , &phi );
    ch2 -> SetBranchAddress( "sig_triggercat" , &triggercat );
    ch2 -> SetBranchAddress( "sig_isiso" , &iso );
    ch2 -> SetBranchAddress( "event_centrality" , &centrality );
    loop = ch2->GetEntries();

    for(int i =0;i<loop;i++){
	ch2->GetEntry(i);      
	if(i%100000==0)cout << "On event " << i << " out of " << loop << endl;
	if(!iso)continue;	
	if(!(centrality<4))continue;
	if(triggercat==8){
	    hDcaLog3D_5->Fill(pt,TMath::Log10(fabs(dca+0.000000001)));       			  
	}
	else if(triggercat==5){
	    hDcaLog3D_1->Fill(pt,TMath::Log10(fabs(dca+0.000000001)));
	}
    }
    TFile f("hist/histograms_yj.root","RECREATE");
    hDcaLog3D_5->Write();
    hDcaLog3D_1->Write();
    f.Close();
}

   
