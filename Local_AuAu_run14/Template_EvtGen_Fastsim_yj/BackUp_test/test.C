void test()
{

  // TFile * inFile_new=  new TFile("input_new_20170910/TypeID_Ana_421.root","READ");
  TFile * inFile_new=  new TFile("input_new_20170910/TypeID_Ana_421.root","READ");
  TFile * inFile_old=  new TFile("input/D0.root","READ");


  TH2F * mh2Hist_old=(TH2F *) inFile_old->Get("mh2D0rDcaVspt1");
  TH2F *mh2Hist_new=(TH2F*) inFile_new->Get("mh2D0rDcaVspt1");
  
  TH1F *  mh1Hist_old= (TH1F *)mh2Hist_old->ProjectionY("h1_xiaozhi");
  TH1F *  mh1Hist_new= (TH1F *)mh2Hist_new->ProjectionY("h1_kunsu");


  mh1Hist_old->Rebin(10);
  mh1Hist_new->Rebin(10);
  
   //   mh1Hist_old->Draw();
   
   mh1Hist_new->Divide(mh1Hist_old);
   mh1Hist_new->Fit("pol0");



}
