void readTxt(bool bin1  =true){
  gStyle->SetOptStat(0);
  
  float lowpt = 2.5;
  float highpt = 3.5;
  if(!bin1){
    lowpt = 3.5;
    highpt = 4.5;
  }
  
  TTree *tree = new TTree("tree", "tree");
  //deltaeta/F
  if(! tree->ReadFile("inc_1ptbin_zoom_inc_emb_moreInfo.txt", "deta/F:dphi/F:ElectronpT/F:ElectronEta/F:ElectronPhi/F:HadronpT/F:HadronEta/F:HadronPhi/F:hpid/F:mcpt/F:hmcpt/F:mceta/F:hmceta/F:mcphi/F:hmcphi/F:mcdeta/F:mcdphi/F:mcy/F:hmcy/F", ' ')){
    std::cerr << "[Error] Failed to read the txtfile." << std::endl;
    return 1;
  }
  
  
  
  Float_t deltaeta  = -999;
  Float_t HadronEta  = -999;
  Float_t hmcy  = -999;
  Float_t mcy  = -999;

  
  //tree->SetBranchAddress("deltaeta", &deltaeta);
  tree->SetBranchAddress("HadronEta", &HadronEta);
  tree->SetBranchAddress("hmcy", &hmcy);
  tree->SetBranchAddress("mcy", &mcy);


  
  cout<<"Event : "<<tree->GetEntriesFast()<<endl;
  for (UInt_t i = 0; i < tree->GetEntriesFast(); i++){
      tree->GetEntry(i);
        //if(deltaeta > 0.00) cout<<deltaeta<<endl;
        if(abs(HadronEta - hmcy) > 0.1) cout<<abs(HadronEta - hmcy)<<endl;
        //cout<<HadronEta<<"        "<<mcy<<" "<<hmcy<<endl;
        //cout<<deltaeta<<endl;
  }
  return 0;
}

