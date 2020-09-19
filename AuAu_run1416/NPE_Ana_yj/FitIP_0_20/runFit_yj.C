#include "fitdata1D.C"
//#include "fit_tfraction.C"
void Iso_Efficiency(TH1F *comp__5);
void runFit_yj(int rs=1,int save=1, int doAllFits=1, int HT=0)
{
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  ///// Electron PID cuts
  float cutLow = 0;
  float cutHigh = 0;
  bool iso_eff = 0;
  //////
  int const numPtBins=9;
  double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
  int etaStart=0;//Here
  int etaEnd=etaStart;
  int ptStart=9;//Here
  int ptEnd=ptStart;
  TH1F* heff_iso = new TH1F("","",numPtBins,binning);
  Iso_Efficiency(heff_iso);
  
  if(doAllFits){
    etaStart=0;
    etaEnd=0;
    ptStart=4;// zyj mb
    ptEnd=9;//numPtBins;
    if(HT)ptStart=5;
  }
  
  //IF SAVING, root dir to save to here, that is ./<pass>
  //You will need to make this dir. manually and a sub dir. called
  // /fits   ===== example    ./5/fits/
  //////////////////////////////////////////////////////////////////
  int pass=115; // 1111133
  if(HT)pass++;
  ////////////////////////////////////////////////////////////////
  //Saving Information//////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  for(int pt=ptStart;pt<ptEnd+1;pt++){
  //for(int pt=ptStart;pt<ptStart+1;pt++){ //zyj test

    char dir1[150];char dir2[150];char dir3[150];
    char dir4[150];char dir5[150];char dir6[150];
    char file[50];char dat[50];char datc[50];
    sprintf(dir1,"%d/fits/DCAFit_Pt_%d",pass,pt); // if %1.0f, will become 0!!!!!
    //cout<<dir1<<"zyjjjjjjjjjjjjjjjjjjjjjjjjjjjjj"<<endl;
    //return ;
    sprintf(file,"%d/log.txt",pass);
    sprintf(dat,"%d/yields.dat",pass);
    //sprintf(dat,"%1.0f/yields.dat",pass);
    sprintf(datc,"%d/chi2.dat",pass);
    //////////////////////////////////////////////////////////////////
    //GETTING HISTOGRAMS TO FIT. Change as needed
    //////////////////////////////////////////////////////////////////
    char dFile[500];
    char dFile1[500];
    char dFile2[500];
    char dFile3[500];
    char dFile4[500];
    char dFile5[500];
    
    //sprintf(dFile,"../production/NPE_Tuples_TuneB12.root");
    sprintf(dFile,"/Volumes/YJMAC/Matt_production/NPE_Tuples_TuneB12.root"); //zyj

    //sprintf(dFile,"../TestArea/test.root");
    TFile *f_D = new TFile(dFile);
    //sprintf(dFile1,"../../NPE_MC/Ana/root/root/DCA_plots.root"); // matt PHE
    sprintf(dFile1,"../../NPE_MC/Ana/root_yj/DCA_plots_yj_full.root"); // zyj PHE
    //sprintf(dFile1,"../../NPE_MC/Ana/root_yj/DCA_plots_yj_full_morepi0.root"); // zyj PHE
    //sprintf(dFile1,"../../NPE_MC/Ana/root_yj/DCA_plots_yj_full_moregamma.root"); // zyj PHE
    TFile *f_D1 = new TFile(dFile1);
    
    sprintf(dFile3,"./hist/histograms.root");
    TFile *f_Dn = new TFile(dFile3);

    //sprintf(dFile2,"../../NPE_MC/Ana/root/root/HF_plots.root");
    //sprintf(dFile2,"../../NPE_MC/Ana/root_yj/HF_plots.root"); // D0 spectrum
    sprintf(dFile2,"../../NPE_MC/Ana/root_yj/HF_plots_HighDp.root");
    TFile *f_D2 = new TFile(dFile2);
    
    auto ch1 = (TChain*)f_D->Get("Signal"); // not used here, we can get DCAxy from here, but since we already have 3DDCA hist, we can take hist directly zyj
    //TH2F *h01_2D1 =new TH2F("h01_2D1","h01_2D1",200,0,20,600,-6,0);
    //ch1->Project("h01_2D1","TMath::Log10(abs(sig_dca)+1e-9):sig_pt","(sig_triggercat==5)");
    TH2F *h01_2D;
    TH2F *h01_2D_pi;
    double constraint[numPtBins]={0,0,0,0,0.422,0.286,0.229,0.199,0.169};
    //double constraint[numPtBins]={0,0,0,0,0.345052, 0.230658, 0.186633, 0.166221, 0.133711};
    int pur_val;
    if(HT){
      pur_val=11; // zyj directory for purity fit result
      h01_2D = (TH2F*)f_Dn->Get("hDcaLog3D_5"); // ht, zyj iso, nsigma, 没加mvacut，
      h01_2D_pi = (TH2F*)f_D->Get("hDcaLog3D_pi_3");//isPion 5
    }else{ 
      double constraint_v2[numPtBins]={0.362,0.304,0.283,0.275528, 0.203909, 0.174318, 0.146396, 0.156036, 0.147285}; // default
      //double constraint_v2[numPtBins]={0.362,0.304,0.283,0.261501, 0.201304, 0.170272, 0.142954, 0.148996, 0.142954}; // more pion
      //double constraint_v2[numPtBins]={0.362,0.304,0.283,0.293253, 0.207177, 0.17915, 0.150271, 0.163226, 0.151121}; // more gamma
      for(auto i=0; i<numPtBins; i++){
        constraint[i]=constraint_v2[i];
      }
      pur_val=111113;
      //pur_val=10;
      h01_2D = (TH2F*)f_Dn->Get("hDcaLog3D_1"); // zyj  iso, mb,mva!!!!
      h01_2D_pi = (TH2F*)f_D->Get("hDcaLog3D_pi_1");//isPion 4
    }

    double e_const = constraint[pt-1]; // zyj 0830 constrain for PHE
    auto h01_2D_emc = (TH2F*)f_D1->Get("dcapt_all"); // PHE hijing combine
    h01_2D_emc->SetName("h01_2D_emc");
    auto h01_2D_e = (TH2F*)f_D1->Get("dcapt"); // j/psi e
    auto h01_2D_e_WS = (TH2F*)f_D->Get("hDcaLog3D_e_WS_1");
    auto h01_2D_2pi = (TH2F*)f_D->Get("hDcaLog3D_2pi_1");
    auto h01_2D_k = (TH2F*)f_D->Get("hDcaLog3D_k_1");
    auto h01_2D_p = (TH2F*)f_D->Get("hDcaLog3D_p_1");
    
    auto h01_2D_D = (TH2F*)f_D2->Get("dcapt_d_all");
    auto h01_2D_B = (TH2F*)f_D2->Get("dcapt_b_all");
    
    // zyj more loose cut, will not be used
    auto h01_2D1 = (TH2F*)f_D->Get("hDcaLog3D_7"); // zyj 奇数项（除了1）都是ht 的，no iso
    h01_2D1->SetName("h01_2D1");
    //auto h01_2D2 = (TH2F*)f_D->Get("hDcaLog3D_4"); //  iso, mb, no mva, matt
    auto h01_2D2 = (TH2F*)f_D->Get("hDcaLog3D_6"); //  no iso, mb,  mva, I changed, but will not use
    double eff;
    if(pt>0){
      h01_2D_D->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_B->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      auto h01_B=(TH1F*)h01_2D_B->ProjectionX();
      int bin1 = h01_B->FindBin(-1);
      cout<<"bin is      "<<bin1<<endl;
      eff = h01_B->Integral(-1,bin1)/h01_B->Integral(); // zyj ?? for waht?
      h01_B->Delete();
    }
    if(pt==0){
      eff=1;
    }
    h01_2D_D->GetXaxis()->SetRangeUser(-4,-1);
    h01_2D_B->GetXaxis()->SetRangeUser(-4,-1);
    auto h01_D=(TH1F*)h01_2D_D->ProjectionX();
    auto h01_B=(TH1F*)h01_2D_B->ProjectionX();
    
    //cout << "Eff. here " << eff  << endl; // eff for b, not be used??
    //Choose correct PT binning and project
    h01_2D_pi->GetYaxis()->SetRangeUser(-4,-1);
    h01_2D_2pi->GetYaxis()->SetRangeUser(-4,-1);
    h01_2D_k->GetYaxis()->SetRangeUser(-4,-1);
    h01_2D_p->GetYaxis()->SetRangeUser(-4,-1);
    h01_2D_e->GetXaxis()->SetRangeUser(-4,-1);
    h01_2D_e_WS->GetYaxis()->SetRangeUser(-4,-1);
    h01_2D_emc->GetXaxis()->SetRangeUser(-4,-1);
    h01_2D->GetYaxis()->SetRangeUser(-4,-1);
    h01_2D1->GetYaxis()->SetRangeUser(-4,-1);
    h01_2D2->GetYaxis()->SetRangeUser(-4,-1);
    
    if(pt>0){
      h01_2D->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]); // zyj 分不同的pt 区间
      h01_2D1->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D2->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_2pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_k->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_p->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_e->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_e_WS->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_emc->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
    }
    auto h01=(TH1F*)h01_2D->ProjectionY(); // mb or ht
    auto h01_1=(TH1F*)h01_2D1->ProjectionY(); // mb/ht looser cut
    auto h01_2=(TH1F*)h01_2D2->ProjectionY();
    //h011=(TH1F*)h01_2D->ProjectionY();
    auto h01_pi=(TH1F*)h01_2D_pi->ProjectionY();
    auto h01_2pi=(TH1F*)h01_2D_2pi->ProjectionY();
    auto h01_k=(TH1F*)h01_2D_k->ProjectionY();
    auto h01_p=(TH1F*)h01_2D_p->ProjectionY();
    auto h01_e=(TH1F*)h01_2D_e->ProjectionX();
    auto h01_e_WS=(TH1F*)h01_2D_e_WS->ProjectionY();
    auto h01_emc=(TH1F*)h01_2D_emc->ProjectionX();
    //if(pt>5)h01_pi=(TH1F*)h01_2D_pi->ProjectionX();
    //////////////////////////////////////////////////////////////////
    
    h01->Rebin(4);
    h01_1->Rebin(4);
    h01_2->Rebin(4);
    h01_B->Rebin(4);
    h01_emc->Rebin(4);
    h01_D->Rebin(4);
    h01_pi->Rebin(4);
    h01_e->Rebin(4);
    if(HT && pt==9){
      h01->Rebin(5);
      h01_1->Rebin(5);
      h01_2->Rebin(5);
      h01_B->Rebin(5);
      h01_emc->Rebin(5);//only for hijing
      h01_D->Rebin(5);
      h01_pi->Rebin(5);
      //h01_e->Rebin(5);
    }
    
    //CALLING FITTING SCRIPT TO DO FIT////////////////////////////////
    if(iso_eff){
      if(HT)cout << "Delta " << h01_1->Integral()-h01->Integral()<<endl; //
      if(!HT) cout << "Delta " << h01_2->Integral()-h01->Integral()<<endl;
      float constrin;
      float isoeff = heff_iso->GetBinContent(pt);
      cout<<"iso eff is<<<<<<<" <<isoeff<<endl;
      if(HT) constrin = (h01_1->Integral()-h01->Integral())/(1.-isoeff)*isoeff/h01->Integral();
      if(!HT) constrin = (h01_2->Integral()-h01->Integral())/(1.-isoeff)*isoeff/h01->Integral();
      cout<<"e constrin is :  "<< constrin<<endl;

      TCanvas *c11 = new TCanvas ("c11","c11");
      h01_1->SetLineColor(kRed); // loose ht  zyj
      h01_2->SetLineColor(kBlue); // loose mb zyj
      h01_1->DrawClone("hist");
      h01_2->DrawClone("same hist");
      h01->DrawClone("same PE"); // zyj tight ht
    }
    //////////////////////////////////////////////////////////////////
    else if(!iso_eff){
      cout <<"Bin Widths " << h01->GetBinWidth(5) << endl;
      cout <<"Bin low " << h01->GetBinLowEdge(1) << endl; // zyj dca min. value
      cout <<"Bin high " << h01->GetBinLowEdge(h01->GetNbinsX())+h01->GetBinWidth(5) << endl;
      cout <<"Bins " << h01->GetNbinsX() << endl;
      cout << "Integrals " << h01->Integral() << " " << h01_1->Integral()<<endl;
      if(pt>0)fitdata1D(h01,h01_emc,h01_emc,h01_pi,h01_2pi,h01_k,h01_p,h01_D,h01_e,h01_B,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt],eff,pur_val,HT,e_const); // zyj 2nd h01_emc is not used
      //if(pt>0)fitdata1D(h01,h01_emc,h01_emc,h01_pi,h01_2pi,h01_k,h01_p,h01_D,h01_e,h01_B,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt],eff,pur_val,HT); // zyj 2nd h01_emc is not used
    }//End Fit
  }//End PT
}//End
//=================================================================================
void Iso_Efficiency(TH1F *comp__5){
  
  // default
   comp__5->SetBinContent(1,0.3869989);
   comp__5->SetBinContent(2,0.3890149);
   comp__5->SetBinContent(3,0.3455656);
   comp__5->SetBinContent(4,0.3276464);
   comp__5->SetBinContent(5,0.3141471);
   comp__5->SetBinContent(6,0.3312605);
   comp__5->SetBinContent(7,0.3513761);
   comp__5->SetBinContent(8,0.3917124);
   comp__5->SetBinContent(9,0.3962521);
   comp__5->SetBinError(1,0.004205462);
   comp__5->SetBinError(2,0.01274007);
   comp__5->SetBinError(3,0.007349816);
   comp__5->SetBinError(4,0.004895982);
   comp__5->SetBinError(5,0.003701858);
   comp__5->SetBinError(6,0.002687474);
   comp__5->SetBinError(7,0.002779526);
   comp__5->SetBinError(8,0.0023058);
   comp__5->SetBinError(9,0.001579538);
}
//=================================================================================

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
