#include "fitdata2D.C"
void runFit_IP(int rs=1,int save=1, int doAllFits=1, int q=1, int HT=0)
{
///////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
///////////////////////////////////
    int const numEtaBins=4;
    double binning[numEtaBins+1]={-0.7,-0.35,0,0.35,0.7};   
    if(doAllFits){
        int etaStart=1;
        int etaEnd=numEtaBins;
	int qqStart=-1;
	int qqEnd=1;       
    } else {
        int etaStart=1;//Here  
        int etaEnd=etaStart; 
	int qqStart=q;
	int qqEnd=q;
    }
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
    for(int qq =qqStart;qq<qqEnd+1;qq+=1){
	if(qq>0)int pass=5;
	if(qq<0)int pass=4;
	if(qq==0)int pass=3;
	for(int eta=etaStart;eta<etaEnd+1;eta++){
	    char dir1[150];char dir2[150];char dir3[150];
	    char file[50];char dat[50];char datc[50];        
	    sprintf(dir1,"%1.0f/fits/v1_Eta_%1.0f",pass,eta);
	    sprintf(file,"%1.0f/yields.dat",pass);
//////////////////////////////////////////////////////////////////
	    TFile *f_D = new TFile("./root/histograms.root");
	    Res = (TH1F*)f_D->Get("Res");
	    Weight = (TH1F*)f_D->Get("Weight");		 
	    double res=0;
	    for(int i = 1;i<10;i++){
		res+=(Res->GetBinContent(i)*Weight->GetBinContent(i)/Weight->Integral());
	    }
	    //double res = 1/res_inv;
	    cout << "Resolution " << res << endl;
	    double frac = res; //pt>1.5
	    //double frac = 0.60 * res; //pt>1.5 no dca cut
	    TH1F *h01 = new TH1F("h01","h01",5,0,TMath::Pi());
	  
	    getData(h01,eta,qq,"FitIP/1/yields.dat");
	    

	    cout << " Yield  " << h01->Integral() << endl;	
	    fitdata2D(h01,save,file,dir1,eta,1.5,8.5,HT,frac);
	}//End eta
    }
}//End

void getData(TH1F* h,int eta,int q,char file[]){
 ifstream data(file);
    if(data.is_open()){
        while(!data.eof()){
	    int e;
	    int p;
	    int qq;
	    double y;
	    double ye;
	    double y1;
            double ye1;
	    data >> qq >> e >> p >> y >> ye >> y1 >> ye1;
	    if(e==eta && q==qq){
		h->SetBinContent(p,y);
		h->SetBinError(p,ye);
	    }
	}
    } 
    else{
	cout << "NOPE!!!"<<endl;
	break;
    }
}
