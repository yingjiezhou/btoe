void norm(TH1F *h);
void weight_B(){
    gROOT->ProcessLine(".x ~/myStyle.C");  
    //gStyle->SetPadLeftMargin(2);
    TGaxis::SetMaxDigits(3);  

    ifstream data_b("BHadron_FONLL.txt");
    vector<double> x;
    vector<double> y;
    x.push_back(0);
    if(data_b.is_open()){
        while(!data_b.eof()){
            double x1;
            double y1;
	    data_b >> x1 >> y1;
	    x.push_back(x1);
	    y.push_back(y1);
	}
    }
    y.pop_back();
    x.pop_back();    
    int const num = x.size();
    double xx[num];
    double yy[num+1];
    for(int i = 1; i<y.size()+1 ;i++){
	yy[i-1]=y[i-1];			     
    }
    for(int i = 1; i<x.size()+1 ;i++){
	xx[i-1]=x[i-1];
	//cout << "Binning " << xx[i-1] << endl;
    }
    TH1F *FONLL = new TH1F("FONLL","FONLL",x.size()-1,xx);
    TH1F *Data = new TH1F("Data","Data",x.size()-1,xx);
    TH1F *Weight = new TH1F("Weight","Weight",x.size()-1,xx);
    TH1F *Check = new TH1F("Check","Check",x.size()-1,xx);
    TH1F *Check1 = new TH1F("Check1","Check1",x.size()-1,xx);
    for(int i = 1; i<x.size()+1 ;i++){
	FONLL->SetBinContent(i,yy[i-1]);
	Data->SetBinContent(i,1);
	Check->SetBinContent(i,1);
	Check1->SetBinContent(i,1);	
    }
    cout<<FONLL->Integral(0, 20)<<endl;
    norm(FONLL);
    norm(Data);
    for(int i = 1; i<x.size()+1 ;i++){
	double temp1=FONLL->GetBinContent(i);
	double temp2=Data->GetBinContent(i);			     
	if(temp2>0)Weight->SetBinContent(i,temp1/temp2);
	else Weight->SetBinContent(i,1);
    }   
    TCanvas *c1 = new  TCanvas("c1","c1");
    FONLL->SetMarkerColor(kBlue);
    FONLL->SetLineColor(kBlue);    
    FONLL->Draw();
    Data->Draw("same");
    TCanvas *c2 = new  TCanvas("c2","c2");
    Weight->Draw();
    Check->Multiply(Weight);
    cout << "Integral w/ no weights " << Check1->Integral() << endl;
    cout << "Integral w/ weights " << Check->Integral() << endl;
    cout <<  "Ratio with / without " << Check->Integral()/Check1->Integral() << endl;
    TFile fi("root/B_Weights.root","RECREATE");
    Weight->Write("B_Weights");

}
void norm(TH1F *h){
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double width = h->GetBinWidth(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1);
	h->SetBinError(i,0);//err/norm1);
    }

}
