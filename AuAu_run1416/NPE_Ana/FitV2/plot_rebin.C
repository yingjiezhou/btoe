void plot_rebin(int pass=2){

    gROOT->ProcessLine(".x ~/myStyle.C");
    char file[50];
    sprintf(file,"./%i/yields.dat",4);

    char file1[50];
    sprintf(file1,"./%i/yields.dat",3);
    ifstream data1(file1);
    int const numPtBins=8;
    double binning[numPtBins+1]={0.,1,1.2,1.5,2.0,2.5,3.5,4.5,8.5};
    double pt_center[numPtBins]={0.8,1.1,1.35,1.75,2.25,2.75,4,6};//,7};
    double binning1[numPtBins+1]={0.,1+0.1,1.2+0.1,1.5+0.1,2.0+0.1,2.5+0.1,3.5+0.1,4.5+0.1,8.5+0.1};
    double binning2[numPtBins+1]={0.,1-0.1,1.2-0.1,1.5-0.1,2.0-0.1,2.5-0.1,3.5-0.1,4.5-0.1,8.5-0.1};
    double b;
    double b_e;
    double c;
    double c_e;
    double pT;
    double pts[9]={3.37281,3.18564,3.18809,3.41617,3.88013,4.73717,6.08789,7.57104};
    double bins3[numPtBins+1]={0,0.492704, 0.443329, 0.443962 ,0.504429 ,0.636248 ,0.906871, 1.38939, 1.97528 };
    double B_M = (5.27929+5.27961)/2;
    for(int i = 0;i<8;i++){
	cout << (sqrt(pts[i]*pts[i]+B_M*B_M)-B_M)/2. << " " ;
    }
    double D_M = 1.86484;
    double pts_d0[8]={1.25,1.73,2.22,2.72,3.22,3.73,4.4,5.99};
    double x_d0[8];
    double xe_d0[8];
    double xe1_d0[8];
    double y_d0[8]={-0.004/2.,0.074/2.,0.095/2.,0.13/2.,0.172/2.,0.129/2.,0.091/2.,0.113/2.};
    double e_d0[8]={0.025,0.019,0.016,0.016,0.019,0.024,0.024,0.031};
    double e1_d0[8]={0.016,0.005,0.004,0.008,0.014,0.015,0.010,0.021};
    for(int i = 0;i<8;i++){
	x_d0[i] = (sqrt(pts_d0[i]*pts_d0[i]+D_M*D_M)-D_M)/2.;
	xe_d0[i]=0;
	xe1_d0[i]=0.02;

    }
    TGraphErrors *g2 = new TGraphErrors(8,x_d0,y_d0,xe_d0,e_d0);
    TGraphErrors *g2_sys = new TGraphErrors(8,x_d0,y_d0,xe1_d0,e1_d0); 
    TH1F *hb = new TH1F("hb","",numPtBins,binning2);
    TH1F *hb1 = new TH1F("hb1","",numPtBins,binning2);
    TH1F *hb2 = new TH1F("hb2","",numPtBins,binning2);
    TH1F *hb3 = new TH1F("hb3","",numPtBins,binning2);
    TH1F *hb4 = new TH1F("hb4","",numPtBins,binning2);
    TH1F *hb_sys = new TH1F("hb_sys","",numPtBins,binning2);
    TH1F *hb_sys1 = new TH1F("hb_sys1","",numPtBins,binning2);
    TH1F *hc = new TH1F("hc","",numPtBins,binning1);
    TH1F *hc1 = new TH1F("hc1","",numPtBins,binning2);
    TH1F *hc2 = new TH1F("hc2","",numPtBins,binning2);
    TH1F *hc3 = new TH1F("hc3","",numPtBins,binning2);
    TH1F *hc4 = new TH1F("hc4","",numPtBins,binning2);
    TH1F *hc_sys = new TH1F("hc_sys","",numPtBins,binning1);
    TH1F *hc_sys1 = new TH1F("hc_sys1","",numPtBins,binning1);
    TH1F *h = new TH1F("h","",numPtBins,binning);
    TH1F *h_sys = new TH1F("h_sys","",numPtBins,binning); 
  
    getData(hb,hb_sys,"./3/yields.dat");
    getData(hc,hc_sys,"./4/yields.dat");
    //getData1(hb,hb1,hb_sys,"./5/yields.dat");//1/2 e
    //getData1(hc,hc1,hc_sys,"./6/yields.dat");//1/2 e
    //getData1(hb,hb1,hb_sys,"./11/yields.dat");//3/2 e
    //getData1(hc,hc1,hc_sys,"./12/yields.dat");//3/2 e
    //getData1(hb,hb2,hb_sys,"./7/yields.dat");//1/2 d
    //getData1(hc,hc2,hc_sys,"./8/yields.dat");//1/2 d
    //getData1(hb,hb3,hb_sys,"./9/yields.dat");//2xd
    //getData1(hc,hc4,hc_sys,"./10/yields.dat");//2xd

    TGraphErrors *g1 = new TGraphErrors(8);
    TGraphErrors *g1_sys = new TGraphErrors(8);   
    TGraphErrors *g3 = new TGraphErrors(8);
    TGraphErrors *g3_sys = new TGraphErrors(8);   

    
    for(int i =5; i<9;i++){
	double temp1 = hb->GetBinContent(i);
	double temp2 = hb->GetBinError(i);
	double temp22 = hb_sys->GetBinError(i);
	double temp3 = hc->GetBinContent(i);       
	double temp4 = hc->GetBinError(i);
	double temp44 = hc_sys->GetBinError(i);
	if(temp1>0 && temp3>0){
	    double temp = temp1/temp2/temp2 + temp3/temp4/temp4;
	    double er = 1/temp2/temp2 + 1/temp4/temp4;
	    double temp_er = temp22/temp2/temp2 + temp44/temp4/temp4;
	    h->SetBinContent(i,temp/er);
	    h_sys->SetBinContent(i,temp/er);
	    h->SetBinError(i,sqrt(1/er));
	    h_sys->SetBinError(i,temp_er/er);	
      
	    g1->SetPoint(i,bins3[i],temp/er/2.);
	    g1_sys->SetPoint(i,bins3[i],temp/er/2.);
	    g1->SetPointError(i,0,sqrt(1/er)/2.);
	    g1_sys->SetPointError(i,0.02,temp_er/er/2.);
	    g3->SetPoint(i,pt_center[i-1],temp/er);
	    g3_sys->SetPoint(i,pt_center[i-1],temp/er);
	    g3->SetPointError(i,0,sqrt(1/er));
	    g3_sys->SetPointError(i,0.1,temp_er/er);

	
	}else if(temp1>0 && temp3==0){
	    h->SetBinContent(i,temp1);
	    h_sys->SetBinContent(i,temp1);
	    h->SetBinError(i,temp2);
	    h_sys->SetBinError(i,temp22);       

	    g1->SetPoint(i,bins3[i],temp1/2.);
	    g1_sys->SetPoint(i,bins3[i],temp1/2.);
	    g1->SetPointError(i,0,temp2/2.);
	    g1_sys->SetPointError(i,0.02,temp22/2.);
	    g3->SetPoint(i,pt_center[i-1],temp1);
	    g3_sys->SetPoint(i,pt_center[i-1],temp1);
	    g3->SetPointError(i,0,temp2);
	    g3_sys->SetPointError(i,0.1,temp22);

	}
	else if(temp1==0 && temp3>0){
	    h->SetBinContent(i,temp3);
	    h_sys->SetBinContent(i,temp3);
	    h->SetBinError(i,temp4);
	    h_sys->SetBinError(i,temp44);
	
	    g1->SetPoint(i,bins3[i],temp3/2.);
	    g1_sys->SetPoint(i,bins3[i],temp3/2.);
	    g1->SetPointError(i,0,temp4/2.);
	    g1_sys->SetPointError(i,0.02,temp44/2.);
	    g3->SetPoint(i,pt_center[i-1],temp3);
	    g3_sys->SetPoint(i,pt_center[i-1],temp3);
	    g3->SetPointError(i,0,temp4);
	    g3_sys->SetPointError(i,0.1,temp44);	    
	}
    }

    TLegend *leg = new TLegend(0.2,0.6,0.4,0.9);
    hc_sys->SetMarkerStyle(25);
    hc_sys->SetLineColor(kBlue);
    hc_sys->SetMarkerColor(kBlue);
    hc_sys->SetFillColor(kBlue);
    hc_sys->SetFillStyle(3004);
    hb_sys->SetMarkerStyle(26);
    hb_sys->SetLineColor(kRed);
    hb_sys->SetMarkerColor(kRed);
    hb_sys->SetFillColor(kRed);
    hb_sys->SetFillStyle(3005);
    hc->SetMarkerStyle(25);
    hc->SetLineColor(kBlue);
    hc->SetMarkerColor(kBlue);
    hb->SetMarkerStyle(26);
    hb->SetLineColor(kRed);
    hb->SetMarkerColor(kRed);

    //leg->AddEntry(hb,"log_{10}n(|DCA|/cm) #in [-1.5,-1]","PLE");
    //leg->AddEntry(hc,"ln(|DCA|/cm) #in [-5,-4]","PEL");
    leg->AddEntry(hb,"Min. Bias","PLE");
    leg->AddEntry(hc,"High Tower","PEL");
    //leg->AddEntry(h,"Weighted Ave.","PEL");
    TCanvas *c1 = new TCanvas("c1","c1");
    hb->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    hb->GetYaxis()->SetTitle("#it{v}_{2}(#it{b}#rightarrow#it{e})");
    hb->GetXaxis()->SetRangeUser(0,8.5);
    hb->GetYaxis()->SetRangeUser(0,0.25);
    hb->Draw();
    hc->Draw("same");
    hc_sys->Draw("same E2");
    hb_sys->Draw("same E2");
    hc->Draw("same E1");
    hb->Draw("same E1");
    leg->Draw("same");
    TCanvas *c2 = new TCanvas("c2","average");
    g3->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    g3->GetYaxis()->SetTitle("#it{v}_{2}(#it{b}#rightarrow#it{e})");
    g3->Draw("APE");
    g3_sys->SetFillColor(kGray);
    g3_sys->Draw("same E2");
    g3->Draw("same p"); 
    gPad->RedrawAxis();
    TCanvas *c3 = new TCanvas("c3","average mt-m0");
    TLegend *leg1 = new TLegend(0.2,0.75,0.55,0.9);
    leg1->AddEntry(g1,"#it{b}#rightarrow#it{e}","PLE");
    leg1->AddEntry(g2,"#it{D}^{0} PhysRevLett.118.212301","PEL");
    g1->GetXaxis()->SetTitle("(m_{T}-m_{0})/n_{q} [GeV]");
    g1->GetYaxis()->SetTitle("#it{v}_{2}(#it{b}#rightarrow#it{e})/n_{q}");
    g1->GetYaxis()->SetRangeUser(0,0.145);
    g1->Draw("APE");
    g1_sys->SetFillColor(kGray);
    g2_sys->SetFillColor(kRed);
    g2_sys->SetFillStyle(3004);   
    g2->SetLineColor(kRed);
    g2->SetMarkerColor(kRed);
    g1_sys->Draw("same E2");
    g2_sys->Draw("same E2");
    g1->Draw("same P");
    g2->Draw("same P");
    leg1->Draw("same");
    gPad->RedrawAxis();
}
void getData(TH1F *hb, TH1F*hb_sys,char file[]){
    ifstream data(file);
    if(data.is_open()){
	while(!data.eof()){
	    char out[50];
	    double b=0;
	    double b_e=0;
	    double pT=0;
	    double c = 0;
	    double c_e= 0 ;	    
	    data >> pT >> b >> b_e >> c;
	    hb->SetBinContent(pT,b);
	    hb->SetBinError(pT,b_e);
	    hb_sys->SetBinContent(pT,b);
	    hb_sys->SetBinError(pT,c);
	}	
    } else {
	cout <<"Nope \n";
    }
    data.close();
}
void getData1(TH1F *hbd,TH1F *hb, TH1F*hb_sys,char file[]){
    ifstream data(file);
    if(data.is_open()){
	while(!data.eof()){
	    char out[50];
	    double b=0;
	    double b_e=0;
	    double pT=0;
	    double c = 0;
	    double c_e= 0 ;	    
	    data >> pT >> b >> b_e >> c;
	    double temp = hb_sys->GetBinError(pT);
	    double temp1 = hbd->GetBinContent(pT);
	    cout << temp1 << " " << b << " " << (temp1-b) << " " << temp << endl;
	    double error = sqrt((temp1-b)*(temp1-b)+temp*temp);
	    hb->SetBinContent(pT,b);
	    hb->SetBinError(pT,b_e);
	    hb_sys->SetBinError(pT,error);
	}	
    } else {
	cout <<"Nope \n";
    }
    data.close();
}
