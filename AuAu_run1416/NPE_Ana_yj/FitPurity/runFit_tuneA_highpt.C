#include "fitMVAdata1D_tuneA_highpt.C"
void runFit_tuneA_highpt(int rs=1,int save=0, int doAllFits=0)
{
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
///// Electron PID cuts 
    float cutLow = -1;
    float cutHigh = 3;
//////
    //int const numPtBins=5;
    //double binning[numPtBins+1]={0.6,1,1.5,2.5,3.5,8.5};
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    //int const numPtBins=11;
    //double binning[numPtBins+1]={0.6,1.0,1.4,1.8,2.2,2.6,3.0,3.4,3.8,4.2,4.6,5.0};

    if(doAllFits){
        int etaStart=0;
        int etaEnd=0; 
        int ptStart=1;
        int ptEnd=numPtBins;
    } else {
        int etaStart=0;//Here
        int ptStart=2;//Here  
        int etaEnd=etaStart; 
        int ptEnd=ptStart;
    }
//IF SAVING, root dir to save to here, that is ./<pass>
//You will need to make this dir. manually and a sub dir. called 
// /fits   ===== example    ./5/fits/
//////////////////////////////////////////////////////////////////
    int pass=6;

////////////////////////////////////////////////////////////////
//Saving Information//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
    for(int pt=ptStart;pt<ptEnd+1;pt++){
	char dir1[150];char dir2[150];char dir3[150];
	char dir4[150];char dir5[150];char dir6[150]; 
	char file[50];char dat[50];char datc[50];        
	sprintf(dir1,"%1.0f/fits/PIDe_Pt_%1.0f.pdf",pass,pt);
	sprintf(file,"%1.0f/log.txt",pass);
	sprintf(dat,"%1.0f/yields.dat",pass);
	sprintf(datc,"%1.0f/chi2.dat",pass);
//////////////////////////////////////////////////////////////////
//GETTING HISTOGRAMS TO FIT. Change as needed 
//////////////////////////////////////////////////////////////////
	char dFile[500];
	char dFile1[500];
	sprintf(dFile,"../production/NPE_Tuples_TuneA1.root");
	sprintf(dFile1,"../test.root");
	TFile *f_D = new TFile(dFile);
	TFile *f_D1 = new TFile(dFile1);

	h01_2D = (TH2F*) f_D->Get("hFit_10");
	h01_2D1 = (TH2F*) f_D->Get("hFit_0");
	h01_2D_e = (TH2F*) f_D->Get("hFit_e_10");
	h01_2D_e_WS = (TH2F*) f_D->Get("hFit_e_WS_10"); 
	h01_2D_pi = (TH2F*) f_D->Get("hFit_pi_10");
	h01_2D_2pi = (TH2F*) f_D->Get("hFit_2pi_10");
	h01_2D_k = (TH2F*) f_D->Get("hFit_k_10");
	h01_2D_p = (TH2F*) f_D->Get("hFit_p_10");
	
	if(pt>0){
	    h01_2D->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D1->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt<10)h01_2D_pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt<3)h01_2D_2pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D_k->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D_p->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt<4)h01_2D_e->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt<4)h01_2D_e_WS->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt>3)h01_2D_e->GetXaxis()->SetRangeUser(2.5,8.5);
	    if(pt>3)h01_2D_e_WS->GetXaxis()->SetRangeUser(2.5,8.5);
	}//if(pt<4)

	h01=(TH1F*)h01_2D->ProjectionY();
	h011=(TH1F*)h01_2D1->ProjectionY();
	h01_pi=(TH1F*)h01_2D_pi->ProjectionY();
	h01_2pi=(TH1F*)h01_2D_2pi->ProjectionY();
	h01_k=(TH1F*)h01_2D_k->ProjectionY();
	h01_p=(TH1F*)h01_2D_p->ProjectionY();
	h01_e=(TH1F*)h01_2D_e->ProjectionY();
	h01_e_WS=(TH1F*)h01_2D_e_WS->ProjectionY();
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
	h01->Rebin(4);
	h011->Rebin(4);
	h01_e->Rebin(4);
	h01_pi->Rebin(4);
	h01_2pi->Rebin(4);	
	h01_k->Rebin(4);
	h01_p->Rebin(4);

	if(pt>0)fitdata1D(h01,h01_e,h01_pi,h01_2pi,h01_k,h01_p,h011,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt]);
	if(pt==0)fitdata1D(h01,h01_e,h01_pi,h01_2pi,h01_k,h01_p,h011,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,0.6,8.5);
	h01->Delete();
	h01_pi->Delete();
	h01_2pi->Delete();
	h01_k->Delete();
	h01_p->Delete();
	h01_e->Delete();
	h01_e_WS->Delete();
	//End Fit
    }//End PT

}//End

