#include "fitdata1D.C"
void norm(TH1F *h);
void norm1(TH1F *h);

void runFit(int rs=1,int save=1, int doAllFits=1)
{
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  ///// Electron PID cuts
  float cutLow = -1;
  float cutHigh = 3;
  //////
  //int const numPtBins=5;
  ///double binning[numPtBins+1]={0.6,1,1.5,2.5,3.5,8.5};
  //int const numPtBins=11;
  //double binning[numPtBins+1]={0.6,1.0,1.4,1.8,2.2,2.6,3.0,3.4,3.8,4.2,4.6,5.0};
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  int etaStart=0;//Here

  int ptStart=9;//Here, start from 1
  int etaEnd=etaStart;
  int ptEnd=ptStart;
  if(doAllFits){
    etaStart=0;
    etaEnd=0;
    ptStart=3;  // zyj test  bin
    ptEnd=numPtBins;
  }
  //IF SAVING, root dir to save to here, that is ./<pass>
  //You will need to make this dir. manually and a sub dir. called
  // /fits   ===== example    ./5/fits/
  //////////////////////////////////////////////////////////////////
  int pass=111113; // Matt

  ////////////////////////////////////////////////////////////////
  //Saving Information//////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  for(int pt=ptStart;pt<ptEnd+1;pt++){ // with diff pt bin
    char dir1[150];char dir2[150];char dir3[150];
    char dir4[150];char dir5[150];char dir6[150];
    char file[50];char dat[50];char datc[50];
    sprintf(dir1,"%1.0d/fits/PIDe_Pt_%1.0d.pdf",pass,pt);
    sprintf(file,"%1.0d/log.txt",pass);
    sprintf(dat,"%1.0d/yields.dat",pass);
    sprintf(datc,"%1.0d/chi2.dat",pass);
    //////////////////////////////////////////////////////////////////
    //GETTING HISTOGRAMS TO FIT. Change as needed
    //////////////////////////////////////////////////////////////////
    char dFile[500];
    char dFile1[500];
    char dFile2[500];
    sprintf(dFile,"/Volumes/YJMAC/Matt_production/NPE_Tuples_TuneB10.root"); // I don't have this root file
    //sprintf(dFile,"../production/NPE_Tuples_TuneA10.root"); // so I changed to use this

    // for pion
    //sprintf(dFile1,"../Likelihood/root/Ks_pion.root"); // sWeighted pion, all is from Matt, zyj 1111/
    sprintf(dFile1,"../Likelihood/root_yj/Ks_pion_smooth.root"); // sWeighted pion, all is from Matt, zyj 111/
    //sprintf(dFile1,"../Likelihood/root_yj/Ks_pion.root");
    sprintf(dFile2,"/Volumes/YJMAC/Matt_production/NPE_Tuples_TuneB10.root");
    //sprintf(dFile2,"../production/NPE_Tuples_TuneA10.root"); // should not weight

    TFile *f_D = new TFile(dFile);
    //ch2 = (TChain*)f_D->Get("BKG"); // zyj comment, here is not used, so I commentd
    //=============================================================================
    
    TFile *f_D1 = new TFile(dFile1);
    TFile *f_D2 = new TFile(dFile2);
    auto h01_2D = (TH2F*) f_D->Get("hFit_0");
    auto h01_2D1 = (TH2F*) f_D->Get("hFit_3"); // with MVA>0.45 cut
    auto h01_2D_e = (TH2F*) f_D->Get("hFit_e_0");
    auto h01_2D_e_WS = (TH2F*) f_D->Get("hFit_e_WS_0");
    TH2F* h01_2D_pi;
    TH2F* h01_2D_pi1;
    if(pt<7){ //zyj 7
      h01_2D_pi = (TH2F*) f_D1->Get("hFit_pi_0");
      h01_2D_pi->SetName("h01_2D_pi");
      h01_2D_pi1 = (TH2F*) f_D2->Get("hFit_pi_0");
      h01_2D_pi1->SetName("h01_2D_pi1");
    }else{
      h01_2D_pi = (TH2F*) f_D2->Get("hFit_pi_0"); // 这个就是高pt 统计量少，所以用data 中
      h01_2D_pi->SetName("h01_2D_pi");
      h01_2D_pi1 = (TH2F*) f_D1->Get("hFit_pi_0"); // 按道理，不是应该都取data 的么，是为了下面的对比所以这里取weight 的
      h01_2D_pi1->SetName("h01_2D_pi1");
    }
    
    auto h01_2D_2pi = (TH2F*) f_D2->Get("hFit_2pi_0");
    auto h01_2D_k = (TH2F*) f_D2->Get("hFit_k_0");
    auto h01_2D_p = (TH2F*) f_D2->Get("hFit_p_0");
    
    //Choose correct PT binning and project
    if(pt>0){
      h01_2D->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D1->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      if(pt<8){
        h01_2D_pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
        h01_2D_pi1->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
        h01_2D_k->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
        h01_2D_p->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      }else{
        h01_2D_pi->GetXaxis()->SetRangeUser(binning[7],binning[9]);
        h01_2D_pi1->GetXaxis()->SetRangeUser(binning[7],binning[9]); // 4.5~8.5 pt range
        h01_2D_k->GetXaxis()->SetRangeUser(binning[7],binning[9]);
        h01_2D_p->GetXaxis()->SetRangeUser(binning[7],binning[9]);
        
      }
      
      
      // file: 111/
      if(pt<6)h01_2D_2pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]); // 为什么和上面设置的pt 区间不一样
      if(pt<6)h01_2D_e->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      if(pt<6)h01_2D_e_WS->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      if(pt>5)h01_2D_e->GetXaxis()->SetRangeUser(3.5,8.5);// 因为高pt 统计量低，不管pt bin 之间的差别
      if(pt>5)h01_2D_e_WS->GetXaxis()->SetRangeUser(3.5,8.5);
      
    }
    
    auto h01=(TH1F*)h01_2D->ProjectionY();
    auto h01_1=(TH1F*)h01_2D1->ProjectionY();
    auto h011=(TH1F*)h01_2D1->ProjectionY();
    auto h01_pi=(TH1F*)h01_2D_pi->ProjectionY();
    auto h01_pi1=(TH1F*)h01_2D_pi1->ProjectionY();
    auto h01_2pi=(TH1F*)h01_2D_2pi->ProjectionY();
    auto h01_k=(TH1F*)h01_2D_k->ProjectionY();
    auto h01_p=(TH1F*)h01_2D_p->ProjectionY();
    auto h01_e=(TH1F*)h01_2D_e->ProjectionY();
    auto h01_e_WS=(TH1F*)h01_2D_e_WS->ProjectionY();
    for(int i=1;i<h01_e->GetNbinsX();i++){
      double temp1 = h01_e->GetBinContent(i);
      double temp2 = h01_e_WS->GetBinContent(i);
      double temp3 = h01_e->GetBinError(i);
      double temp4 = h01_e_WS->GetBinError(i);
      if((temp1-temp2)>0){
        h01_e->SetBinContent(i,temp1-temp2);
        h01_e->SetBinError(i,sqrt(temp3*temp3+temp4*temp4));
      }
      else{
        h01_e->SetBinContent(i,0);
        h01_e->SetBinError(i,1);
      }
    }
    
    //////////////////////////////////////////////////////////////////
    //CALLING FITTING SCRIPT TO DO FIT////////////////////////////////
    //////////////////////////////////////////////////////////////////
    if(pt<3){
//     h01->Rebin(2); // 300 bins
//   h01_1->Rebin(2);
//   h01_e->Rebin(2);
//  h01_pi->Rebin(2);
// h01_pi1->Rebin(2);
// h01_2pi->Rebin(2);
//   h01_k->Rebin(2);
//   h01_p->Rebin(2);
    }else{
      h01->Rebin(6); // 300 bins
      h01_1->Rebin(6);
      h01_e->Rebin(6);
      h01_pi->Rebin(6);
      h01_pi1->Rebin(6);
      h01_2pi->Rebin(6);
      h01_k->Rebin(6);
      h01_p->Rebin(6);
    }
    norm1(h01_pi);

    //h01_pi->Draw();
    //h01_pi1->Draw("same");
    //return ;
    if(pt>0)fitdata1D(h01,h01_e,h01_pi,h01_2pi,h01_k,h01_p,h011,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt]);
    //return ;
    if(pt==0)fitdata1D(h01,h01_e,h01_pi,h01_2pi,h01_k,h01_p,h011,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,0.6,8.5);

    int bin1 = h01->FindBin(-1);
    int bin11 = h01->FindBin(-13);
    int bin2 = h01->FindBin(3);
    cout << "Integrals " << h01->Integral(bin1,bin2) << " " << h01_1->Integral(bin1,bin2)<<endl; // zyj comp
    //=============================================================================
    if(!doAllFits){
      TCanvas *comp = new TCanvas("comp","pi norms");
      h01_pi1->SetLineColor(kRed);
      h01_pi1->SetMarkerColor(kRed);
      h01_pi->SetMarkerStyle(21);
      TLegend *leg2 = new TLegend(0.6,0.7,0.87,0.9);
      leg2->AddEntry(h01_pi,"sWeighted K_{s}#rightarrow #pi#pi","ep");
      leg2->AddEntry(h01_pi1,"1/#beta selected #pi","pe");
      norm(h01_pi1);
      norm(h01_pi);
      h01_pi->GetXaxis()->SetTitle("n#sigma_{e}");
      h01_pi->GetYaxis()->SetTitle("A. U.");
      
      h01_pi->DrawNormalized("PE");
      h01_pi1->DrawNormalized("same PE");
      leg2->Draw("same");
      comp->SaveAs(Form("%i/Purity_fit_pi_comp.pdf", pass));
    }
   
    //=============================================================================

    h01->Delete();
    h01_pi->Delete();
    h01_pi1->Delete();
    h01_2pi->Delete();
    h01_k->Delete();
    h01_p->Delete();
    h01_e->Delete();
    h01_e_WS->Delete();
    //End Fit
  }//End PT
  
}//End

void norm(TH1F *h){
  double norm1 = h->Integral();
  int bins = h->GetNbinsX();
  for(int i=1; i<bins+1;i++){
    double temp = h->GetBinContent(i);
    if(temp<0)temp=0;
    double err = h->GetBinError(i);
    h->SetBinContent(i,temp/norm1);
    h->SetBinError(i,err/norm1);
  }
}
void norm1(TH1F *h){
  double norm1 = 1;
  int bins = h->GetNbinsX();
  for(int i=1; i<bins+1;i++){
    double temp = h->GetBinContent(i);
    if(temp<0)temp=0;
    double err = h->GetBinError(i);
    h->SetBinContent(i,temp/norm1);
    h->SetBinError(i,err/norm1);
  }
}

