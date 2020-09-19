#include "fitMVAdata2D.C"
void run2DMVAFit(int rs=1,int save=0, int doAllFits=0)
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
        int ptStart=2;
        int ptEnd=numPtBins;
    } else {
        int etaStart=0;//Here
        int ptStart=0;//Here  
        int etaEnd=etaStart; 
        int ptEnd=ptStart;
    }
//IF SAVING, root dir to save to here, that is ./<pass>
//You will need to make this dir. manually and a sub dir. called 
// /fits   ===== example    ./5/fits/
//////////////////////////////////////////////////////////////////
    int pass=7;

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
	sprintf(dFile,"../production/NPE_Tuples_TuneB2_Small.root");
	sprintf(dFile1,"../test1.root");
	TFile *f_D = new TFile(dFile);
	TFile *f_D1 = new TFile(dFile1);
	h01_2D = (TH2F*) f_D->Get("hFit_3");
	h01_2D1 = (TH2F*) f_D->Get("hFit_0");
	h01_2D_e = (TH2F*) f_D->Get("hFit_e_3");
	h01_2D_e_WS = (TH2F*) f_D->Get("hFit_e_WS_3"); 
	h01_2D_pi = (TH2F*) f_D->Get("hFit_pi_3");
	h01_2D_2pi = (TH2F*) f_D->Get("hFit_2pi_3");
	h01_2D_k = (TH2F*) f_D->Get("hFit_k_3");
	h01_2D_p = (TH2F*) f_D->Get("hFit_p_3");

	h01_2D_mva = (TH2F*) f_D->Get("hFit2D_0");
	h01_2D_e_mva  = (TH2F*) f_D->Get("hFit2D_0");
	h01_2D_e_WS_mva  = (TH2F*) f_D->Get("hFit2D_0"); 
	h01_2D_pi_mva = (TH2F*) f_D->Get("hFit2D_0");
	h01_2D_2pi_mva = (TH2F*) f_D->Get("hFit2D_0");
	h01_2D_k_mva = (TH2F*) f_D->Get("hFit2D_0");
	h01_2D_p_mva = (TH2F*) f_D->Get("hFit2D_0");
	if(pt>0){
	    h01_2D->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D1->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt<10)h01_2D_pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt<3)h01_2D_2pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D_k->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D_p->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt<5)h01_2D_e->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt<5)h01_2D_e_WS->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt>4)h01_2D_e->GetXaxis()->SetRangeUser(2.5,8.5);
	    if(pt>4)h01_2D_e_WS->GetXaxis()->SetRangeUser(2.5,8.5);

	    h01_2D_mva->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]); 
	    if(pt<10)h01_2D_pi_mva->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(pt<3)h01_2D_2pi_mva->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D_k_mva->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D_p_mva->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(0)h01_2D_e_mva->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(0)h01_2D_e_WS_mva->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    if(1)h01_2D_e_mva->GetXaxis()->SetRangeUser(0,8.5);
	    if(1)h01_2D_e_WS_mva->GetXaxis()->SetRangeUser(0,8.5);
	}//if(pt<4)

	h01=(TH1F*)h01_2D->ProjectionY();
	h011=(TH1F*)h01_2D1->ProjectionY();
	h01_pi=(TH1F*)h01_2D_pi->ProjectionY();
	h01_2pi=(TH1F*)h01_2D_2pi->ProjectionY();
	h01_k=(TH1F*)h01_2D_k->ProjectionY();
	h01_p=(TH1F*)h01_2D_p->ProjectionY();
	h01_e=(TH1F*)h01_2D_e->ProjectionY();
	h01_e_WS=(TH1F*)h01_2D_e_WS->ProjectionY();

	h01_mva=(TH1F*)h01_2D_mva->ProjectionY();
	h01_pi_mva=(TH1F*)h01_2D_pi_mva->ProjectionY();
	h01_2pi_mva=(TH1F*)h01_2D_2pi_mva->ProjectionY();
	h01_k_mva=(TH1F*)h01_2D_k_mva->ProjectionY();
	h01_p_mva=(TH1F*)h01_2D_p_mva->ProjectionY();
	h01_e_mva=(TH1F*)h01_2D_e_mva->ProjectionY();
	h01_e_WS_mva=(TH1F*)h01_2D_e_WS_mva->ProjectionY();

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
	for(int i=1;i<h01_e_mva->GetNbinsX();i++){
	    double temp1 = h01_e_mva->GetBinContent(i);
	    double temp2 = h01_e_WS_mva->GetBinContent(i);	    
	    double temp3 = h01_e_mva->GetBinError(i);
	    double temp4 = h01_e_WS_mva->GetBinError(i);
	    if((temp1-temp2)>0){
		h01_e_mva->SetBinContent(i,temp1-temp2);
		h01_e_mva->SetBinError(i,sqrt(temp3*temp3+temp4*temp4));
	    }
	    else{
		h01_e_mva->SetBinContent(i,0);
		h01_e_mva->SetBinError(i,1);
	    }	
	}
//////////////////////////////////////////////////////////////////         
//CALLING FITTING SCRIPT TO DO FIT////////////////////////////////
//////////////////////////////////////////////////////////////////     

	h01->Rebin(35);
	h011->Rebin(35);
	h01_e->Rebin(35);
	h01_pi->Rebin(35);
	h01_2pi->Rebin(35);	
	h01_k->Rebin(35);
	h01_p->Rebin(35);

	/*h01_mva->Rebin(2);
	h01_e_mva->Rebin(2);
	h01_pi_mva->Rebin(2);
	h01_2pi_mva->Rebin(2);	
	h01_k_mva->Rebin(2);
	h01_p_mva->Rebin(2);*/
	
	if(pt>0)fitdata2D(h01,h01_e,h01_pi,h01_2pi,h01_k,h01_p,h011,h01_mva,h01_e_mva,h01_pi_mva,h01_2pi_mva,h01_k_mva,h01_p_mva,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt]);
	if(pt==0)fitdata2D(h01,h01_e,h01_pi,h01_2pi,h01_k,h01_p,h011,h01_mva,h01_e_mva,h01_pi_mva,h01_2pi_mva,h01_k_mva,h01_p_mva,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,0.6,8.5);
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

