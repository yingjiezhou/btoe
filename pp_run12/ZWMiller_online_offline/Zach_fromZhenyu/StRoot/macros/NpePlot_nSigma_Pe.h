
NpePlot_nSigma_Pe{

  TH3F* mh3nSigEUnlike[3];
  TH3F* mh3nSigElike[3];
  //  TH3F* mh2InvMasslike[3];
  // TH3F* mh2InvMassUnlike[3];

  TH1F* mh1nSigElike[3];
  TH1F* mh1nSigEUnlike[3];
  // TH1F* mhInvMasslike[3];
  // TH1F* mhInvMassUnlike[3];
  // TH1F* mhInvMass[3];

  TH1F* mh1nSigE[3];
  TH1F* mh1num_no_cut=new TH1F("mh1num_no_cut","Number no cuts",20,0,20);
  TH1F* mh1num_cut=new TH1F("mh1num_cut","Number  cuts",20,0,20);
  TH1F* mh1mean=new TH1F("mh1mean","Number  cuts",20,0,20);
  TH1F* mh1sigma=new TH1F("mh1sigma","Number  cuts",20,0,20);
 
  TH1F * mh1efff;
}
