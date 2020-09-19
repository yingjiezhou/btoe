#include "fitdata1D.C"
void Iso_Efficiency(TH1F *comp__5);
//#include "fit_tfraction.C"
void runFit(int rs=1,int save=1, int doAllFits=1, int HT=0)
{
  /////////////////////////////////////////////////////////////////////////////////////////
  gROOT->ProcessLine(".x ~/myStyle.C");
  TGaxis::SetMaxDigits(3);
  ///// Electron PID cuts
  float cutLow = 0;
  float cutHigh = 0;
  bool iso_eff =0;
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
  int pass=111333; // default
  //int pass = 714;
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
    //sprintf(dFile,"/Volumes/YJMAC/Matt_production/NPE_Tuples_TuneB12.root"); //zyj
    sprintf(dFile,"/Volumes/YJMAC/Matt_production/NPE_Tuples_Central5.root"); //zyj

    //sprintf(dFile,"../TestArea/test.root");
    TFile *f_D = new TFile(dFile);
    //sprintf(dFile1,"../../NPE_MC/Ana/root/DCA_plots.root"); // zyj PHE
    //sprintf(dFile1,"../../NPE_MC/Ana/root_yj/DCA_plots_yj_central5.root"); // zyj PHE
    //sprintf(dFile1,"../../NPE_MC/Ana/root_yj/DCA_plots_yj_central5_v3.root"); // updated pion spectrum
    //sprintf(dFile1,"../../NPE_MC/Ana/root_yj/DCA_plots_yj_central5_v3_2.root"); // updated pion spectrum, change scale, default
    sprintf(dFile1,"../../NPE_MC/Ana/root_yj/DCA_plots_yj_central5_v3_2.root"); // updated pion spectrum, change scale, default
    //sprintf(dFile1,"../../NPE_MC/Ana/root_yj/DCA_plots_yj_central5_v3_2_moreGamma.root"); // updated pion spectrum, change scale, default
    TFile *f_D1 = new TFile(dFile1);
    
    sprintf(dFile2,"../../NPE_MC/Ana/root_yj/HF_plots_C5_yj.root"); // updated D and Lc/D0 ratio
    //sprintf(dFile2,"../../NPE_MC/Ana/root_yj/HF_plots_C5_yj_lowDp.root"); // updated D and Lc/D0 ratio
    //sprintf(dFile2,"../../NPE_MC/Ana/root/root/HF_plots.root");
    //sprintf(dFile2,"../../NPE_MC/Ana/root/HF_plots_LowDp.root");
    TFile *f_D2 = new TFile(dFile2);
    
    auto ch1 = (TChain*)f_D->Get("Signal"); // not used here, we can get DCAxy from here, but since we already have 3DDCA hist, we can take hist directly zyj
    //TH2F *h01_2D1 =new TH2F("h01_2D1","h01_2D1",200,0,20,600,-6,0);
    //ch1->Project("h01_2D1","TMath::Log10(abs(sig_dca)+1e-9):sig_pt","(sig_triggercat==5)");
    TH2F *h01_2D;
    TH2F *h01_2D_pi;
    //double constraint[numPtBins]={0,0,0,0,0.422,0.286,0.229,0.199,0.169};
    double constraint[numPtBins]={0,0,0,0,0.345052, 0.230658, 0.186633, 0.166221, 0.133711};
    int pur_val;
    if(HT){
      pur_val=555; // zyj directory for purity fit result
      h01_2D = (TH2F*)f_D->Get("hDcaLog3D_5"); // ht, zyj iso, nsigma, 没加mvacut，
      h01_2D_pi = (TH2F*)f_D->Get("hDcaLog3D_pi_3");//isPion 5
    }else{ 
      double constraint_v2[numPtBins]={0.362,0.304,0.283,0.378125, 0.311862, 0.22964, 0.225388, 0.217199, 0.176918}; // default
      //double constraint_v2[numPtBins]={0.362,0.304,0.283,0.405401, 0.319827, 0.229526, 0.233134, 0.226814, 0.183715}; // more pion
      //double constraint_v2[numPtBins]={0.362,0.304,0.283,0.497317, 0.346233, 0.22918, 0.255818, 0.2512, 0.198877}; // more gamma
      //double constraint_v2[numPtBins]={0.362,0.304,0.283,0.240,0.207,0.173,0.141,0.128,0.123}; // MB
      for(auto i=0; i<numPtBins; i++){
        constraint[i]=constraint_v2[i];
      }
      pur_val=55;
      h01_2D = (TH2F*)f_D->Get("hDcaLog3D_1"); // zyj  iso, mb,mva!!!!
      h01_2D_pi = (TH2F*)f_D->Get("hDcaLog3D_pi_1");//isPion 4
    }
    double e_const = constraint[pt-1]; // zyj 0830 constrain for PHE
    auto h01_2D_emc = (TH2F*)f_D1->Get("dcapt_all"); // PHE hijing combine
    h01_2D_emc->SetName("h01_2D_emc");
    auto h01_2D_e = (TH2F*)f_D1->Get("dcapt"); // j/psi e
    auto h01_2D_e_WS = (TH2F*)f_D->Get("hDcaLog3D_e_WS_1");
    //auto h01_2D_2pi = (TH2F*)f_D->Get("hDcaLog3D_2pi_1");
    
    auto h01_2D_D = (TH2F*)f_D2->Get("dcapt_d_all");
    auto h01_2D_B = (TH2F*)f_D2->Get("dcapt_b_all");
    
    // zyj more loose cut, will not be used
    auto h01_2D1 = (TH2F*)f_D->Get("hDcaLog3D_7"); // zyj 奇数项（除了1）都是ht 的，no iso
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
    //h01_2D_2pi->GetYaxis()->SetRangeUser(-4,-1);
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
      //h01_2D_2pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_e->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_e_WS->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
      h01_2D_emc->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
    }
    auto h01=(TH1F*)h01_2D->ProjectionY(); // mb or ht
    auto h01_1=(TH1F*)h01_2D1->ProjectionY(); // mb/ht looser cut
    auto h01_2=(TH1F*)h01_2D2->ProjectionY();
    //h011=(TH1F*)h01_2D->ProjectionY();
    auto h01_pi=(TH1F*)h01_2D_pi->ProjectionY();
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
    //if((HT && pt==9) ){
    if(pt==9 || pt==8){
      h01->Rebin(5);
      h01_1->Rebin(5);
      h01_2->Rebin(5);
      h01_B->Rebin(5);
      h01_emc->Rebin(5);//only for hijing
      h01_D->Rebin(5);
      h01_pi->Rebin(5);
      //h01_e->Rebin(5);
    }
    //h01_1->Draw();
    //return ;
     
    
    
    //CALLING FITTING SCRIPT TO DO FIT////////////////////////////////
    if(iso_eff){
        if(HT)cout << "Delta " << h01_1->Integral()-h01->Integral()<<endl; //
      if(!HT) cout << "Delta " << h01_2->Integral()-h01->Integral()<<endl;
      float constrin;
      float isoeff = heff_iso->GetBinContent(pt);
      cout<<"iso eff is<<<<<<<     " <<isoeff<<endl;
      if(HT) constrin = (h01_1->Integral()-h01->Integral())/(1.-isoeff)*isoeff/h01->Integral();
      if(!HT) constrin = (h01_2->Integral()-h01->Integral())/(1.-isoeff)*isoeff/h01->Integral();
      cout<<"e constrin is :  "<< constrin<<endl;

      //TCanvas *c11 = new TCanvas ("c11","c11");
      //h01_1->SetLineColor(kRed); // loose ht  zyj
      //h01_2->SetLineColor(kBlue); // loose mb zyj
      //h01_1->DrawClone("hist");
      //h01_2->DrawClone("same hist");
      //h01->DrawClone("same PE"); // zyj tight ht
    }
    //////////////////////////////////////////////////////////////////
    else if(!iso_eff){
      cout <<"Bin Widths " << h01->GetBinWidth(5) << endl;
      cout <<"Bin low " << h01->GetBinLowEdge(1) << endl; // zyj dca min. value
      cout <<"Bin high " << h01->GetBinLowEdge(h01->GetNbinsX())+h01->GetBinWidth(5) << endl;
      cout <<"Bins " << h01->GetNbinsX() << endl;
      cout << "Integrals " << h01->Integral() << " ht:" << h01_1->Integral()<<" mb : "<<  h01_2->Integral()<<endl;
      //if(pt>0)fitdata1D(h01,h01_emc,h01_emc,h01_pi,h01_2pi,h01_k,h01_p,h01_D,h01_e,h01_B,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt],eff,pur_val,HT,e_const); // zyj 2nd h01_emc is not used
      if(pt>0)fitdata1D(h01,h01_emc,h01_emc,h01_pi,h01_D,h01_e,h01_B,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt],eff,pur_val,HT,e_const); // zyj 2nd h01_emc is not used
      //if(pt>0)fitdata1D(h01,h01_emc,h01_emc,h01_pi,h01_2pi,h01_k,h01_p,h01_D,h01_e,h01_B,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt],eff,pur_val,HT); // zyj 2nd h01_emc is not used
    }//End Fit
  }//End PT
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


/*  ch1 = (TChain*)f_D->Get("Signal");
 ch2 = (TChain*)f_D->Get("BKG");
 ch3 = (TChain*)f_D->Get("PhoE");
 TH2F *h01_2D = new TH2F("h01_2D","",200,0,20,100,-0.1,0.1);
 TH2F *h01_2D_e = new TH2F("h01_2D_e","",200,0,20,100,-0.1,0.1);
 TH2F *h01_2D_e_WS = new TH2F("h01_2D_e_WS","",200,0,20,100,-0.1,0.1);
 TH2F *h01_2D_pi = new TH2F("h01_2D_pi","",200,0,20,100,-0.1,0.1);
 TH2F *h01_2D_2pi = new TH2F("h01_2D_2pi","",200,0,20,100,-0.1,0.1);
 TH2F *h01_2D_k = new TH2F("h01_2D_k","",200,0,20,100,-0.1,0.1);
 TH2F *h01_2D_p = new TH2F("h01_2D_p","",200,0,20,100,-0.1,0.1);
 
 char cuts_e[500];
 char cuts_e_WS[500];
 char cuts_pi[500];
 char cuts_k[500];
 char cuts_p[500];
 if(pt<6){
 sprintf(cuts_e,"probe_mva>0 && probe_charge*tag_charge<0 &&probe_nsige>-1 && probe_nsige<3  && abs(1/probe_beta-1)<0.025 && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 sprintf(cuts_e_WS,"probe_mva>0 && probe_charge*tag_charge>0 &&probe_nsige>-1 && probe_nsige<3  && abs(1/probe_beta-1)<0.025 && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 sprintf(cuts_k,"probe_mva>0 && probe_bkgcat==3 && probe_nsige>-1 && probe_nsige<3 && abs(1/probe_beta-1)<0.025 && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 sprintf(cuts_pi,"probe_mva>0 && probe_bkgcat==1 && probe_nsige>-1 && probe_nsige<3 && abs(1/probe_beta-1)<0.025 && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 sprintf(cuts_p,"probe_mva>0 && probe_bkgcat==4 && probe_nsige>-1 && probe_nsige<3 && abs(1/probe_beta-1)<0.025 && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 }
 if(pt>5){
 sprintf(cuts_e,"probe_mva>0 && probe_charge*tag_charge<0 &&probe_nsige>-1 && probe_nsige<3  && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 sprintf(cuts_e_WS,"probe_mva>0 && probe_charge*tag_charge>0 &&probe_nsige>-1 && probe_nsige<3 && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 sprintf(cuts_pi,"probe_mva>0 && probe_bkgcat==1 && probe_nsige>-1 && probe_nsige<3 && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 sprintf(cuts_k,"probe_mva>0 && probe_bkgcat==3 && probe_nsige>-1 && probe_nsige<3 && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 sprintf(cuts_p,"probe_mva>0 && probe_bkgcat==4 && probe_nsige>-1 && probe_nsige<3 && probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
 }
 cout << "Doing signal projection" << endl;
 ch1->Project("h01_2D","sig_dcaxy:sig_pt","sig_nsige>-1 && sig_nsige<3");
 cout << "Doing photonic electron projection" << endl;
 ch3->Project("h01_2D_e","probe_dcaxy:probe_pt",cuts_e);
 ch3->Project("h01_2D_e_WS","probe_dcaxy:probe_pt",cuts_e_WS);
 cout << "Doing pion projection" << endl;
 ch2->Project("h01_2D_pi","probe_dcaxy:probe_pt",cuts_pi);//,"",50000000);
 cout << "Doing kaon projection" << endl;
 ch2->Project("h01_2D_k","probe_dcaxy:probe_pt",cuts_k,"",2000000);
 cout << "Doing proton projection" << endl;
 ch2->Project("h01_2D_p","probe_dcaxy:probe_pt",cuts_p,"",2000000);
 */

//void Iso_Efficiency(TH1F *comp__5){
//comp__5->SetBinContent(1,0.3847622);
//    comp__5->SetBinContent(2,0.4517242);
//    comp__5->SetBinContent(3,0.4366887);
//    comp__5->SetBinContent(4,0.4473724);
//    comp__5->SetBinContent(5,0.439934);
//    comp__5->SetBinContent(6,0.4043061);
//    comp__5->SetBinContent(7,0.4481145);
//    comp__5->SetBinContent(8,0.5118096);
//    comp__5->SetBinContent(9,0.5164205);
//    comp__5->SetBinError(1,0.007471006);
//    comp__5->SetBinError(2,0.03018183);
//    comp__5->SetBinError(3,0.01913216);
//    comp__5->SetBinError(4,0.01386368);
//    comp__5->SetBinError(5,0.01108483);
//    comp__5->SetBinError(6,0.00773451);
//    comp__5->SetBinError(7,0.008283464);
//    comp__5->SetBinError(8,0.006713114);
//    comp__5->SetBinError(9,0.004765384);
//} // for MB template, iso effi
void Iso_Efficiency(TH1F *comp__5){
   comp__5->SetBinContent(1,0.3036515);
   comp__5->SetBinContent(2,0.3821695);
   comp__5->SetBinContent(3,0.3688267);
   comp__5->SetBinContent(4,0.394627);
   comp__5->SetBinContent(5,0.3844927);
   comp__5->SetBinContent(6,0.3669196);
   comp__5->SetBinContent(7,0.4313995);
   comp__5->SetBinContent(8,0.4619291);
   comp__5->SetBinContent(9,0.4794814);
   comp__5->SetBinError(1,0.008447614);
   comp__5->SetBinError(2,0.03322882);
   comp__5->SetBinError(3,0.02086264);
   comp__5->SetBinError(4,0.01532617);
   comp__5->SetBinError(5,0.01203282);
   comp__5->SetBinError(6,0.008366134);
   comp__5->SetBinError(7,0.009084918);
   comp__5->SetBinError(8,0.007202795);
   comp__5->SetBinError(9,0.005116464);
}
