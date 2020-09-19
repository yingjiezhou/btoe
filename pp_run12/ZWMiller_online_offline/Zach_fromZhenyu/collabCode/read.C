void read(){
  TF1 *fEff[20];
  double effPars[20][3];
  ifstream inf("bingchu_comb_eff_fit.txt", std::ifstream::in);
  if(!inf.good()){
     cout<<"No input efficiency tables!"<<endl;
     return -1;
   }
  for(int i=0;i<20;i++){
     for(int j=0;j<3;j++) inf>>effPars[i][j];
  }
  
  for(int i =0; i< 20; i++){
  fEff[i] = new TF1(Form("fEff_%i", i),"[0]*exp(-pow([1]/x,[2]))",0.2,15);
  fEff[i]->SetParameters(effPars[i]);
  cout<<effPars[i][0]<<effPars[i][1]<<effPars[i][2]<<endl;
  fEff[i]->SetLineColor(kBlue+i);
  if(i==0){
      fEff[i]->GetYaxis()->SetRangeUser(0.55, 0.95);
      fEff[i]->GetXaxis()->SetRangeUser(0, 2);
      fEff[i]->Draw();
  }
  else fEff[i]->Draw("same");
  }


}
