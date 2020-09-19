#include "fitdata1D.C"
//#include "fit_tfraction.C"
void runFit(int rs=1,int save=1, int doAllFits=1, int HT=1)
{
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
///// Electron PID cuts 
    float cutLow = 0;
    float cutHigh = 0;
//////
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};    
    if(doAllFits){
        int etaStart=0;
        int etaEnd=0; 
        int ptStart=4;
        int ptEnd=9;//numPtBins;
	if(HT)ptStart=5;
    } else {
        int etaStart=0;//Here
        int ptStart=9;//Here  
        int etaEnd=etaStart; 
        int ptEnd=ptStart;
    }
 
//IF SAVING, root dir to save to here, that is ./<pass>
//You will need to make this dir. manually and a sub dir. called 
// /fits   ===== example    ./5/fits/
//////////////////////////////////////////////////////////////////
    int pass=1;
    if(HT)pass++;
////////////////////////////////////////////////////////////////
//Saving Information//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
    for(int pt=ptStart;pt<ptEnd+1;pt++){
	char dir1[150];char dir2[150];char dir3[150];
	char dir4[150];char dir5[150];char dir6[150]; 
	char file[50];char dat[50];char datc[50];        
	sprintf(dir1,"%1.0f/fits/DCAFit_Pt_%1.0f.pdf",pass,pt);
	sprintf(file,"%1.0f/log.txt",pass);
	sprintf(dat,"%1.0f/yields.dat",pass);
	sprintf(datc,"%1.0f/chi2.dat",pass);
//////////////////////////////////////////////////////////////////
//GETTING HISTOGRAMS TO FIT. Change as needed 
//////////////////////////////////////////////////////////////////
	char dFile[500];
	char dFile1[500];
	char dFile2[500];
	char dFile3[500];
	char dFile4[500];
	char dFile5[500];

	sprintf(dFile,"../production/NPE_Tuples_TuneB12.root");
        //sprintf(dFile,"../TestArea/test.root");
	TFile *f_D = new TFile(dFile);
	sprintf(dFile3,"./hist/histograms.root");
        //sprintf(dFile,"../TestArea/test.root");
	TFile *f_Dn = new TFile(dFile3);
	sprintf(dFile1,"../../NPE_MC/Ana/root/DCA_plots.root");
	TFile *f_D1 = new TFile(dFile1);
        sprintf(dFile2,"../../NPE_MC/Ana/root/HF_plots.root");
        TFile *f_D2 = new TFile(dFile2);
	ch1 = (TChain*)f_D->Get("Signal");
	//TH2F *h01_2D1 =new TH2F("h01_2D1","h01_2D1",200,0,20,600,-6,0);
	//ch1->Project("h01_2D1","TMath::Log10(abs(sig_dca)+1e-9):sig_pt","(sig_triggercat==5)");
	if(HT){
	    double constraint[numPtBins]={0,0,0,0,0.422,   0.286,   0.229,   0.199,   0.169};
 
	    int pur_val=11;
	    h01_2D = (TH2F*)f_Dn->Get("hDcaLog3D_5");
	    h01_2D_pi = (TH2F*)f_D->Get("hDcaLog3D_pi_3");//isPion 5
	}else{
	    double constraint[numPtBins]={0.362,0.304,0.283,0.240,0.207,0.173,0.141,0.128,0.123};
	    int pur_val=10;
	    h01_2D = (TH2F*)f_Dn->Get("hDcaLog3D_1");
	  
	    h01_2D_pi = (TH2F*)f_D->Get("hDcaLog3D_pi_1");//isPion 4
	}
	double e_const = constraint[pt-1];
	h01_2D_emc = (TH2F*)f_D1->Get("dcapt_all");
	h01_2D_emc->SetName("h01_2D_emc");
	h01_2D_e = (TH2F*)f_D1->Get("dcapt");	
	h01_2D_e_WS = (TH2F*)f_D->Get("hDcaLog3D_e_WS_1");
	h01_2D_2pi = (TH2F*)f_D->Get("hDcaLog3D_2pi_1");
	h01_2D_k = (TH2F*)f_D->Get("hDcaLog3D_k_1");
	h01_2D_p = (TH2F*)f_D->Get("hDcaLog3D_p_1");	
	h01_2D_D = (TH2F*)f_D2->Get("dcapt_d_all");
	h01_2D_B = (TH2F*)f_D2->Get("dcapt_b_all");
	h01_2D1 = (TH2F*)f_D->Get("hDcaLog3D_5");
	h01_2D1->SetName("h01_2D1");
	h01_2D2 = (TH2F*)f_D->Get("hDcaLog3D_4");
	if(pt>0){
	    h01_2D_D->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]); 
	    h01_2D_B->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);      
	    h01_B=(TH1F*)h01_2D_B->ProjectionX();
	    int bin1 = h01_B->FindBin(-1);
	    double eff = h01_B->Integral(-1,bin1)/h01_B->Integral();
	    h01_B->Delete();
	}
	if(pt==0){
	    double eff=1;
	}
	h01_2D_D->GetXaxis()->SetRangeUser(-4,-1);
	h01_2D_B->GetXaxis()->SetRangeUser(-4,-1);   
	h01_D=(TH1F*)h01_2D_D->ProjectionX();
	h01_B=(TH1F*)h01_2D_B->ProjectionX();

	cout << "Eff. here " << eff  << endl;
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
	    h01_2D->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
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
	h01=(TH1F*)h01_2D->ProjectionY();
	h01_1=(TH1F*)h01_2D1->ProjectionY();
	h01_2=(TH1F*)h01_2D2->ProjectionY();
	//h011=(TH1F*)h01_2D->ProjectionY();
	h01_pi=(TH1F*)h01_2D_pi->ProjectionY();
	h01_2pi=(TH1F*)h01_2D_2pi->ProjectionY();
	h01_k=(TH1F*)h01_2D_k->ProjectionY();
	h01_p=(TH1F*)h01_2D_p->ProjectionY();
	h01_e=(TH1F*)h01_2D_e->ProjectionX();
	h01_e_WS=(TH1F*)h01_2D_e_WS->ProjectionY();
	h01_emc=(TH1F*)h01_2D_emc->ProjectionX();
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
	if(0){//HT && pt==9){
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
	if(0){
	    h01->Rebin();
	    h01_1->Rebin();
	    cout << "Delta " << h01_1->Integral()-h01->Integral()<<endl;
	    cout << "Check " << h01_2->Integral()<<endl;
	    TCanvas *c1 = new TCanvas ("c1","c1");
	    //h01->Divide(h01_1);
	    //norm(h01);
	    //norm(h01_1);
	    //norm(h01_2);
	    h01_1->SetLineColor(kRed);
	    h01_2->SetLineColor(kBlue);
	    h01_1->DrawClone("same hist");
	    //h01_2->DrawClone("same hist");
	    h01->DrawClone("same PE");
	    h01->Divide(h01_1);		
	    TCanvas *c11 = new TCanvas ("c11","c11");
	    h01->Draw("hist");
	}
//////////////////////////////////////////////////////////////////    
	else if(1){
	    cout <<"Bin Widths " << h01->GetBinWidth(5) << endl;
	    cout <<"Bin low " << h01->GetBinLowEdge(1) << endl;
	    cout <<"Bin high " << h01->GetBinLowEdge(h01->GetNbinsX())+h01->GetBinWidth(5) << endl;
	    cout <<"Bins " << h01->GetNbinsX() << endl;	
	    cout << "Integrals " << h01->Integral() << " " << h01_1->Integral()<<endl;
	    if(pt>0)fitdata1D(h01,h01_emc,h01_emc,h01_pi,h01_2pi,h01_k,h01_p,h01_D,h01_e,h01_B,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt],eff,pur_val,HT,e_const);
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


/*	ch1 = (TChain*)f_D->Get("Signal");
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
