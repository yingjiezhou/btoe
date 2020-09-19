#include "fitdata2D.C"
void runFit(int rs=1,int save=1, int doAllFits=1, int HT=1)
{
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
///// Electron PID cuts 
    float cutLow = 0;
    float cutHigh = 0;
//////
    int doSys=0;
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};   
    double widths[numPtBins]={0.2,0.1,0.15,0.25,0.25,1,1,1,1.5};    
    if(doAllFits){
        int etaStart=0;
        int etaEnd=0; 
        int ptStart=5;//5
        int ptEnd=numPtBins;
	if(HT)ptStart=6;
	if(!HT)ptEnd=9;
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
    int pass=202;
    if(HT)pass=203;
////////////////////////////////////////////////////////////////
//Saving Information//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
    for(int pt=ptStart;pt<ptEnd+1;pt++){
	char dir1[150];char dir2[150];char dir3[150];
	char dir4[150];char dir5[150];char dir6[150]; 
	char file[50];char dat[50];char datc[50];        
	sprintf(dir1,"%1.0f/fits/v2_Pt_%1.0f.pdf",pass,pt);
	sprintf(dir2,"%1.0f/fits/Toy_Pt_%1.0f.pdf",pass,pt);
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
	int pur_val=5;
	if(HT)pur_val=6;
	sprintf(dFile,"../EventPlane/root/histograms_ops_hem_test.root");
	TFile *f_D = new TFile(dFile);
	if(!HT){// hec is loose and he is tight
	    h01_2D = (TH2F*)f_D->Get("hec");
	    h01_2D1 = (TH2F*)f_D->Get("he");
	    h01_2D2 = (TH2F*)f_D->Get("hebkg");
            ave_2D = (TH2F*)f_D->Get("avec");
            ave_2D1 = (TH2F*)f_D->Get("ave");
            ave_2D2 = (TH2F*)f_D->Get("avebkg");
	}
	if(HT){
	    h01_2D = (TH2F*)f_D->Get("hec_ht");
	    h01_2D1 = (TH2F*)f_D->Get("he_ht");
	    h01_2D2 = (TH2F*)f_D->Get("hebkg_ht");
            ave_2D = (TH2F*)f_D->Get("avec_ht");
            ave_2D1 = (TH2F*)f_D->Get("ave_ht");
	    ave_2D2 = (TH2F*)f_D->Get("avebkg_ht");
	}
	if(pt>0){
	    h01_2D->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D1->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    h01_2D2->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    ave_2D->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
            ave_2D1->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	    ave_2D2->GetYaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	}		
	h01 = (TH1F*)h01_2D->ProjectionX();
	h011 = (TH1F*)h01_2D1->ProjectionX();
	h0111 = (TH1F*)h01_2D2->ProjectionX();
	ave01 = (TH1F*)ave_2D->ProjectionX();
        ave011 = (TH1F*)ave_2D1->ProjectionX();
	ave0111 = (TH1F*)ave_2D2->ProjectionX();
	double corr_b = ave01->GetMean();
	double corr_c =ave011->GetMean();
	double corr_bkg =ave0111->GetMean();
	cout << " Yield in b-rich " << h01->Integral() << endl;
	cout << " Yield in c-rich " << h011->Integral() << endl;
	cout << " b-rich <1/res> " << corr_b <<endl;
	cout << " c-rich <1/res> " << corr_c <<endl;
	cout << " bkg-rich <1/res> " << corr_bkg <<endl;
	h01->Rebin(8);
	h011->Rebin(8);
	h0111->Rebin(8);
	if(1)fitdata2D(h01,h011,h0111,0,0,save,file,dat,datc,dir1,dir2,dir3,dir4,dir5,dir6,pt,0,rs,cutLow,cutHigh,binning[pt-1],binning[pt],1,pur_val,corr_b,corr_c,corr_bkg,doSys,HT);
	else{
	    he = (TH2F*)f_D->Get("he");
            he_ht = (TH2F*)f_D->Get("he_ht");
	    TH1F* dca1  = new TH1F("dca1","dca1",9,binning);
	    TH1F* dca2  = new TH1F("dca2","dca2",9,binning);
	    TH1F* dca11  = new TH1F("dca11","dca11",9,binning);
            TH1F* dca22  = new TH1F("dca22","dca22",9,binning);
            for(int i =4;i<9;i++){
                he->GetYaxis()->SetRangeUser(binning[i],binning[i+1]);
                he_ht->GetYaxis()->SetRangeUser(binning[i],binning[i+1]);
                h01 = (TH1F*)he->ProjectionX();
                h011 = (TH1F*)he_ht->ProjectionX();
		double width = widths[i];
		dca11->SetBinContent(i+1,h01->Integral()/width);
                dca11->SetBinError(i+1,sqrt(h01->Integral())/width);
                if(i>4)dca22->SetBinContent(i+1,h011->Integral()/width);
                if(i>4)dca22->SetBinError(i+1,sqrt(h011->Integral())/width);
            }
	    dca2->SetMarkerColor(kRed);
	    dca2->SetLineColor(kRed);
            //dca22->SetMarkerColor(kRed);
            //dca22->SetLineColor(kRed);
	    dca22->SetMarkerStyle(25);
	    //dca11->SetMarkerStyle(25);
	    dca11->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
	    dca11->GetYaxis()->SetTitle("dN/d#it{p}_{T}");//Candidates");
	    TLegend *leg = new TLegend(0.55,0.6,0.9,0.9);
	    leg->AddEntry(dca11,"Min. Bias log_{10}(|DCA|/cm) #in [-2,-1]","PEL");
            //leg->AddEntry(dca2,"MB ln(|DCA|/cm) #in [-5,-4]","PEL");
	    leg->AddEntry(dca22,"High Tower log_{10}(|DCA|/cm) #in [-2,-1]","PEL");
            //leg->AddEntry(dca22,"HT ln(|DCA|/cm) #in [-5,-4]","PEL");
	    TCanvas *c2 = new TCanvas("c2","c2");
	    //dca1->Draw("PE");
	    //dca2->Draw("same PE");
	    dca11->Draw("PE same");
	    dca22->Draw("PE same");
	    leg->Draw("same");
	}
	
    }//End PT
}//End
