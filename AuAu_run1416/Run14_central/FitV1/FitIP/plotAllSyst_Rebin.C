double eff[9]={0,0,0,0.952039,0.964109,0.974269,0.983159,0.988961,0.994107};
void plotAllSyst_Rebin(){
    gROOT->ProcessLine(".x ~/myStyle.C");
    TFile *fk = new TFile("/project/projectdirs/starprod/rnc/mkelsey/forYifei/electronFraction/finalBtoEFraction.root");
    kunsu = (TH1F*) fk->Get("run14_bF_sts");
    kunsu1 = (TH1F*) fk->Get("run14_bF_sys");
    kunsu->SetMarkerColor(kRed);
    kunsu->SetMarkerStyle(25);
    kunsu->SetLineColor(kRed);
    kunsu->GetXaxis()->SetRangeUser(2,8.5);
    kunsu1->GetXaxis()->SetRangeUser(2,8.5);
    ifstream data_b("b_pp200.txt");
    ifstream data_c("c_pp200.txt");
    vector<double> x;
    vector<double> xu;
    vector<double> yb; 
    vector<double> yc; 
    vector<double> eub; 
    vector<double> euc;  
    vector<double> edb; 
    vector<double> edc;    
    TH1F *hb_t = new TH1F("hb_t","",100,0,10);
    TH1F *hc_t = new TH1F("hc_t","",100,0,10);
    TH1F *hr_t = new TH1F("hr_t","",100,0,10);
    TH1F *hb_et = new TH1F("hb_et","",100,0,10);
    TH1F *hc_et = new TH1F("hc_et","",100,0,10);
    double lumi = 1;//500e-6;
    if(data_b.is_open()){
	while(!data_b.eof()){
	    double x1;
	    double y1;
	    double eu;
	    double ed;
	    double p1;
	    double p2;
	    double p3;
	    double p4;
	    double eff;
	    data_b >> x1 >> y1 >> eu >> ed >> p1 >> p2 >> p3 >> p4;
	    x.push_back(x1);
	    xu.push_back(x1-10/100);
	    yb.push_back(y1);
	    eub.push_back(eu-y1);	    
	    edb.push_back(y1-ed);
	    int bin = hb_t->FindBin(x1);
	    hb_t->SetBinContent(bin,y1*lumi);
	    hb_t->SetBinError(bin,(y1-ed)*lumi);
	}
    }
    if(data_c.is_open()){
	while(!data_c.eof()){
	    double x1;
	    double y1;
	    double eu;
	    double ed;
	    double p1;
	    double p2;
	    double p3;
	    double p4;
	    data_c >> x1 >> y1 >> eu >> ed >> p1 >> p2 >> p3 >> p4;	 
	    yc.push_back(y1);
	    euc.push_back(eu-y1);	    
	    edc.push_back(y1-ed);
	    int bin = hc_t->FindBin(x1);
	    hc_t->SetBinContent(bin,y1*lumi);
	    hc_t->SetBinError(bin,(y1-ed)*lumi);
	}
    }

    TFile * f= new TFile("../../NPE_MC/Ana/root/HF_plots.root");
    dcapt_d_all=(TH2F*)f->Get("dcapt_d_all");
    dcapt_b_all=(TH2F*)f->Get("dcapt_b_all");
    pt_d_all =(TH1F*)dcapt_d_all->ProjectionY();
    pt_b_all =(TH1F*)dcapt_b_all->ProjectionY();
    norm(pt_b_all);
    norm(pt_d_all);

    double x_b[100];double xe_b[100];
    double y_bc[100];double e_bc[100];
    double y_c[100];
    pt_d_all->Scale(hc_t->Integral()/pt_d_all->Integral());
    for(int i = 0;i<100;i++){
	x_b[i] = x[i];
	xe_b[i] = 0;     
	double temp = pt_d_all->GetBinContent(pt_d_all->FindBin(x_b[i]));
	y_bc[i] = yb[i]/(yb[i]+yc[i]);
	y_c[i] = yc[i];
	e_bc[i] = 0;
    }
    y_bc[0]=0;
    TGraphErrors *gb = new TGraphErrors(100,x_b,y_bc,xe_b,e_bc);
    TGraphErrors *gc = new TGraphErrors(100,x_b,y_c,xe_b,e_bc);
    TCanvas *ccharm = new TCanvas("ccharm","charm");
    gc->Draw("APE");
    pt_d_all->Draw("hist same");
    int const numPtBins=8;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,8.5};
    int const numSysBins=10;    
    double binning1[numSysBins+1]={0,1,2,3,4,5,6,7,8,9,10};

    TH2F *h1 = new TH2F("h1","h1",numPtBins,binning,numSysBins,binning1); 
    TH2F *h1_ht = new TH2F("h1_ht","h1_ht",numPtBins,binning,numSysBins,binning1); 

    TH2F *frac = new TH2F("frac","frac",numPtBins,binning,numSysBins,binning1); 
    TH2F *frac_ht = new TH2F("frac_ht","frac_ht",numPtBins,binning,numSysBins,binning1); 

    TH2F *frac1 = new TH2F("frac1","frac1",numPtBins,binning,numSysBins,binning1); 
    TH2F *frac1_ht = new TH2F("frac1_ht","frac1_ht",numPtBins,binning,numSysBins,binning1); 
    TH2F *frac2 = new TH2F("frac2","frac2",numPtBins,binning,numSysBins,binning1); 
    TH2F *frac2_ht = new TH2F("frac2_ht","frac2_ht",numPtBins,binning,numSysBins,binning1); 
    TH2F *frac3 = new TH2F("frac3","frac3",numPtBins,binning,numSysBins,binning1); 
    TH2F *frac3_ht = new TH2F("frac3_ht","frac3_ht",numPtBins,binning,numSysBins,binning1); 
    TH1F *frb = new TH1F("frb","frb",numPtBins,binning); 
    TH1F *frb_ht = new TH1F("frb_ht","frb_ht",numPtBins,binning); 
    TH1F *frc = new TH1F("frc","frc",numPtBins,binning); 
    TH1F *frc_ht = new TH1F("frc_ht","frc_ht",numPtBins,binning); 
    TH1F *fre = new TH1F("fre","fre",numPtBins,binning); 
    TH1F *fre_ht = new TH1F("fre_ht","fre_ht",numPtBins,binning); 
    TH1F *frh = new TH1F("frh","frh",numPtBins,binning); 
    TH1F *frh_ht = new TH1F("frh_ht","frh_ht",numPtBins,binning); 


    TH1F *h_ave = new TH1F("h_ave","h_ave",numPtBins,binning); 
    TH1F *h_ave_sys = new TH1F("h_ave_sys","h_ave_sys",numPtBins,binning); 
    TH1F *h_rel_er1 = new TH1F("h_rel_er1","h_rel_er1",numPtBins,binning); 
    TH1F *kunsu_rel_er1 = new TH1F("kunsu_rel_er1","kunsu_rel_er1",numPtBins,binning); 
    TH1F *h_rel_er = new TH1F("h_rel_er","h_rel_er",numPtBins,binning); 
    TH1F *kunsu_rel_er = new TH1F("kunsu_rel_er","kunsu_rel_er",numPtBins,binning); 
    TH1F *h = new TH1F("h","h",numPtBins,binning); 
    TH1F *h_ht = new TH1F("h_ht","h_ht",numPtBins,binning); 
    TH1F *h_sys = new TH1F("h_sys","h_sys",numPtBins,binning); 
    TH1F *h_sys_ht = new TH1F("h_sys_ht","h_sys_ht",numPtBins,binning); 
    TH1F *er = new TH1F("er","er",numPtBins,binning); 
    TH1F *er_ht = new TH1F("er_ht","er_ht",numPtBins,binning); 

    getData(h1,frac,frac1,frac2,frac3,1,"./200/yields.dat");//Central
    getData(h1,frac,frac1,frac2,frac3,2,"./202/yields.dat");//phoe 1-pion
    getData(h1,frac,frac1,frac2,frac3,3,"./204/yields.dat");//phoe 1-gamma
    getData(h1,frac,frac1,frac2,frac3,4,"./206/yields.dat");// phoe 2
    getData(h1,frac,frac1,frac2,frac3,5,"./208/yields.dat");// pt spectra
    getData(h1,frac,frac1,frac2,frac3,6,"./210/yields.dat");// fragmetation
    getData(h1,frac,frac1,frac2,frac3,7,"./212/yields.dat");// fragmetation
    getData(h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,1,"./201/yields.dat");
    getData(h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,2,"./203/yields.dat");
    getData(h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,3,"./205/yields.dat");
    getData(h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,4,"./207/yields.dat");
    getData(h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,5,"./209/yields.dat");
    getData(h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,6,"./211/yields.dat");
    getData(h1_ht,frac_ht,frac1_ht,frac2_ht,frac3_ht,7,"./213/yields.dat");
    cout << "B fractions "<<endl;
    getErrors(frac,frb);
    getErrors(frac_ht,frb_ht);
    cout << "C fractions "<<endl;
    getErrors(frac1,frc);
    getErrors(frac1_ht,frc_ht);
    cout << "E fractions "<<endl;
    getErrors(frac2,fre);
    getErrors(frac2_ht,fre_ht);
    cout << "H fractions "<<endl;
    getErrors(frac3,frh);
    getErrors(frac3_ht,frh_ht);

    cout << "Doing Min. bias errors " << endl;
    cout << "Errors are phoe1-pion - phoe1-gamma - phoe2 const - pt spectra - fragmentaion" <<  endl;
    for(int i = 5; i<numPtBins+1; i++){
	cout << "on pT bin " << i << " " << endl;	
	double cen = 0;
	double phoe = 0;
	double frag = 0;
	double err = 0;
	for(int j = 1; j<numSysBins+1; j++){	
	    double val = h1->GetBinContent(i,j);
	    double val_e = h1->GetBinError(i,j);
	    if(val>0){
		if(j==1){
		    h->SetBinContent(i,val);
		    h_sys->SetBinContent(i,val);
		    h->SetBinError(i,val_e);
		    cen = val;
		}else{
		    if(j==2 || j==3 || j==6 || j == 7){
			if(j==2)phoe = val;
			if(j==3)if(fabs(cen-val)>fabs(cen-phoe))phoe = val;		
			if(j==3)err+= (cen-phoe)*(cen-phoe);
			if(j==6)frag = val;
			if(j==7)if(fabs(cen-val)>fabs(cen-frag))frag = val;		
			if(j==7)err+= (cen-frag)*(cen-frag);
		    }else{
			err+= (cen-val)*(cen-val);
		    }
		    cout << j << " " << cen << " " << val << " " << fabs(cen-val)/cen << " ";
		}
		cout << endl;
	    }
	}
	if(err>0){
	    er->SetBinContent(i,sqrt(err));
	    cout << "Total error " << sqrt(err) << " " << sqrt(err)/cen << endl;
	    h_sys->SetBinError(i,sqrt(err));
	}
    }


    cout << "DoingHT errors " << endl;
    cout << "Errors are phoe1-pion - phoe1-gamma - phoe2 const - pt spectra - fragmentaion" <<  endl;
    for(int i = 6; i<numPtBins+1; i++){
	cout << "on pT bin " << i << " " << endl;	
	double cen = 0;
	double phoe = 0;
	double frag = 0;
	double err = 0;
	for(int j = 1; j<numSysBins+1; j++){	
	    double val = h1_ht->GetBinContent(i,j);
	    double val_e = h1_ht->GetBinError(i,j);
	    if(val>0){
		if(j==1){
		    h_ht->SetBinContent(i,val);
		    h_sys_ht->SetBinContent(i,val);
		    h_ht->SetBinError(i,val_e);
		    cen = val;
		}else{
		    if(j==2 || j==3 || j==6 || j == 7){
			if(j==2)phoe = val;
			if(j==3)if(fabs(cen-val)>fabs(cen-phoe))phoe = val;		
			if(j==3)err+= (cen-phoe)*(cen-phoe);
			if(j==6)frag = val;
			if(j==7)if(fabs(cen-val)>fabs(cen-frag))frag = val;		
			if(j==7)err+= (cen-frag)*(cen-frag);
		    }else{
			err+= (cen-val)*(cen-val);
		    }
		 
		    cout << j << " " << cen << " " << val << " " << fabs(cen-val)/cen << " "; 
		}
		cout << endl;
	    }	
	}
	if(err>0){
	    er_ht->SetBinContent(i,sqrt(err));
	    cout << "Total error " << sqrt(err) << " " << sqrt(err)/cen << endl;
	    h_sys_ht->SetBinError(i,sqrt(err));
	}
    }

    for(int i =1; i<10;i++){
	double temp1 = h->GetBinContent(i);
	double temp2 = h->GetBinError(i);
	double temp22 = h_sys->GetBinError(i);
	double temp3 = h_ht->GetBinContent(i);       
	double temp4 = h_ht->GetBinError(i);
	double temp44 = h_sys_ht->GetBinError(i);
	if(temp1>0 && temp3>0){
	    double temp = temp1/temp2/temp2 + temp3/temp4/temp4;
	    double er1 = 1/temp2/temp2 + 1/temp4/temp4;
	    h_ave->SetBinContent(i,temp/er1);
	    h_ave_sys->SetBinContent(i,temp/er1);
	    h_ave->SetBinError(i,sqrt(1/er1));	
	    double temp_er = temp22/temp2/temp2 + temp44/temp4/temp4;  
	    h_ave_sys->SetBinError(i,temp_er/er1);

	}else if(temp1>0 && temp3==0){
	    h_ave->SetBinContent(i,temp1);
	    h_ave_sys->SetBinContent(i,temp1);
	    h_ave->SetBinError(i,temp2);
	    h_ave_sys->SetBinError(i,temp22);
	}
	else if(temp1==0 && temp3>0){
	    h_ave->SetBinContent(i,temp3);
	    h_ave_sys->SetBinContent(i,temp3);
	    h_ave->SetBinError(i,temp4);
	    h_ave_sys->SetBinError(i,temp44);
	}
    }
    h->SetMarkerStyle(24);
    h_sys->SetMarkerStyle(24);  
    h->SetLineColor(kBlue);
    h_sys->SetLineColor(kBlue); 
    h->SetMarkerColor(kBlue);
    h_sys->SetMarkerColor(kBlue); 
    h_sys->SetFillColor(kBlue); 
    h_sys->SetFillStyle(3004); 
    h_ht->SetMarkerStyle(25);
    h_sys_ht->SetMarkerStyle(25);  
    h_ht->SetLineColor(kRed);
    h_sys_ht->SetLineColor(kRed); 
    h_ht->SetMarkerColor(kRed);
    h_sys_ht->SetMarkerColor(kRed); 
    h_sys_ht->SetFillColor(kRed); 
    h_sys_ht->SetFillStyle(3005); 
    TCanvas *c1 = new TCanvas("c1","Final");
    TLegend *leg3 = new TLegend(0.5,0.2,0.9,0.45);
    leg3->AddEntry(h,"Min. Bias","PLE");
    leg3->AddEntry(h_ht,"High Tower","PLE");    
    h->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
    h->GetYaxis()->SetRangeUser(0,1);
    h->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    h->Draw("E1");
    h_sys->Draw("same E2");
    h_ht->Draw("same E1");
    h_sys_ht->Draw("same E2");
    h_ht->Draw("same E1");
    h->Draw("same E1");
    leg3->Draw("same");
    TCanvas *c2 = new TCanvas("c2","Rel. Errors");
    er_ht->SetLineColor(kRed);
    er->Draw();
    er_ht->Draw("same");

    gb->SetLineStyle(7); 
    kunsu1->SetLineColor(kBlue);
    kunsu1->SetFillColor(kBlue);
    kunsu1->SetFillColorAlpha(kBlue,0.5);
    kunsu1->SetFillStyle(3004);
    h_ave_sys->SetFillColor(kGray);
    TLegend *leg = new TLegend(0.5,0.2,0.9,0.45);
    leg->AddEntry(h_ave,"New Results","PLE");
    leg->AddEntry(kunsu,"Old Results","PLE");
    leg->AddEntry(gb,"FONLL pp 200 GeV","L");

    TCanvas *c3 = new TCanvas("c3","Weighted Ave");
    h_ave->GetYaxis()->SetTitle("N(#it{b}#rightarrow #it{e})/N(#it{b}+#it{c}#rightarrow #it{e})");
    h_ave->GetYaxis()->SetRangeUser(0,1);
    h_ave->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    h_ave->Draw("PE"); 
    h_ave_sys->Draw("same E2");
    kunsu1->Draw("same E2");
    h_ave->Draw("same E1");
    kunsu->Draw("same");

    kunsu->Draw("same");
    gb->Draw("same");
    leg->Draw("same");
    gPad->RedrawAxis();

    for(int i = 5; i<10; i++){
	double temp1 = h_ave->GetBinContent(i);
	double temp2 = h_ave->GetBinError(i);	
	double temp11 = kunsu->GetBinContent(i-1);
	double temp22 = kunsu->GetBinError(i-1);
	double temp3 = h_ave_sys->GetBinContent(i);
	double temp4 = h_ave_sys->GetBinError(i);	
	double temp33 = kunsu1->GetBinContent(i-1);
	double temp44 = kunsu1->GetBinError(i-1);
	if(temp1>0)h_rel_er->SetBinContent(i,temp2/temp1);
	if(temp11>0)kunsu_rel_er->SetBinContent(i,temp22/temp11);
	if(temp4>0)h_rel_er1->SetBinContent(i,temp4/temp3);
	if(temp44>0)kunsu_rel_er1->SetBinContent(i,temp44/temp33);
    }
    TLegend *leg11 = new TLegend(0.2,0.7,0.9,0.9);
    kunsu_rel_er->SetLineColor(kRed);
    kunsu_rel_er1->SetLineColor(kRed);
    kunsu_rel_er1->SetLineStyle(7);
    h_rel_er1->SetLineStyle(7);
    leg11->AddEntry(h_rel_er,"New Results Stat.","l");
    leg11->AddEntry(h_rel_er1,"New Results Syst.","l");
    leg11->AddEntry(kunsu_rel_er,"Old Results Stat.","l");
    leg11->AddEntry(kunsu_rel_er1,"Old Results Syst.","l");

    TCanvas *c34 = new TCanvas("c34","Rel. er");
    h_rel_er->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    h_rel_er->GetYaxis()->SetTitle("Relative Uncertainty");
    h_rel_er->GetYaxis()->SetRangeUser(0,0.5);
    h_rel_er->Draw("hist");
    kunsu_rel_er->Draw("SAME hist");   
    h_rel_er1->Draw("same hist");
   kunsu_rel_er1->Draw("SAME hist");    
   leg11->Draw("same");
    TLegend *leg1 = new TLegend(0.2,0.7,0.9,0.9);
    frb->SetLineColor(kGreen-2);
    frb->SetMarkerColor(kGreen-2);    
    frc->SetLineColor(kMagenta);
    frc->SetMarkerColor(kMagenta);    
    frh->SetLineColor(kRed);
    frh->SetMarkerColor(kRed);    
    fre->SetLineColor(kOrange);
    fre->SetMarkerColor(kOrange);    
    frb_ht->SetLineColor(kGreen-2);
    frb_ht->SetMarkerColor(kGreen-2);    
    frc_ht->SetLineColor(kMagenta);
    frc_ht->SetMarkerColor(kMagenta);    
    frh_ht->SetLineColor(kRed);
    frh_ht->SetMarkerColor(kRed);    
    fre_ht->SetLineColor(kOrange);
    fre_ht->SetMarkerColor(kOrange); 
    leg1->SetHeader("log_{10}(|DCA|/cm)#in[-1.5,1.0]");
    leg1->AddEntry(frb,"#it{b}#rightarrow#it{c}","PLE");
    leg1->AddEntry(frc,"#it{c}#rightarrow#it{c}","PLE");
    leg1->AddEntry(frh,"Hadrons","PLE");
    leg1->AddEntry(fre,"Photonic #it{e}","PLE");
    TLatex lat;
    
    TF1 *line = new TF1("line","1",0,100);
    line->SetLineStyle(7);

    TCanvas *c4 = new TCanvas("c4","Frac errors",1000,500);
    c4->Divide(2,1);
    c4->cd(1);
    frb->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    frb->GetYaxis()->SetTitle("Relative Fraction");    
    frb->GetYaxis()->SetRangeUser(0,1.5); 
    frb_ht->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    frb_ht->GetYaxis()->SetTitle("Relative Fraction");  
    frb_ht->GetYaxis()->SetRangeUser(0,1.5); 
    frb->Draw("PE");
    frc->Draw("same PE");
    fre->Draw("same PE");
    frh->Draw("same PE");
    line->Draw("same");
    leg1->Draw("same");

    lat.DrawLatex(5.7,1.2,"Min. Bias");
    c4->cd(2);  
    frb_ht->Draw("PE");
    frc_ht->Draw("same PE");
    fre_ht->Draw("same PE");
    frh_ht->Draw("same PE");
    line->Draw("same");
    leg1->Draw("same");
    //lat.DrawLatex(5,1.2,"log_{10}(|DCA|/cm)#in[-1.5,1.0]");
    lat.DrawLatex(5.7,1.2,"High Tower");
    TFile save("root/Fractions_Rebin.root","RECREATE");
    frb->Write("bfrac");
    frc->Write("cfrac");
    frh->Write("hfrac");   
    fre->Write("efrac");
    frb_ht->Write("bfrac_ht");
    frc_ht->Write("cfrac_ht");
    frh_ht->Write("hfrac_ht");   
    fre_ht->Write("efrac_ht");
  
}
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
void getData(TH2F* h,TH2F* f,TH2F* f1,TH2F* f2,TH2F* f3, int bin,char file[]) {
    ifstream data(file);
    if(data.is_open()){
	while(!data.eof()){
	    int pT;
	    double y1;double e1;double y2;double e2;
	    double y3;double e3;double y4;double e4;
	    double pur;double pure;double eff;double er;
	    double fb1;double fb2;double fc1;double fc2;
	    double fe1;double fe2;double fh1;double fh2;
	    double br;double bkgr;double nper;double bre;
	    double bkgre;double npere;double bkgre;double ere;

	    data >> pT >> y1 >> e1 >> fb1 >> fb2 >> y2 >> e2 >> fc1 >> fc2 >> y3 >> e3 >> fe1 >> fe2 >> y4 >> e4 >> fh1 >> fh2 >> br >> bre >> bkgr>>bkgre >> nper >> npere >> er >> ere >> pur >> pure;
	    if(pT!=0){
		h->SetBinContent(pT,bin,br);
		h->SetBinError(pT,bin,bre);
		f->SetBinContent(pT,bin,fb1);
		f1->SetBinContent(pT,bin,fc1);	
		f2->SetBinContent(pT,bin,fe1);
		f3->SetBinContent(pT,bin,fh1);
	    }
	}

    }
    else {
	cout <<"Nope " <<file  << "\n";
    }
    data.close();
}
void getErrors(TH2F* frac, TH1F* fr){
    //cout << "Doing frac errors " << endl;
    //cout << "Errors are phoe1-pion - phoe1-gamma - phoe2 const - pt spectra - fragmentaion" <<  endl;
    for(int i = 5; i<fr->GetNbinsX()+1; i++){
	//cout << "on pT bin " << i << " " << endl;	
	double cen = 0;
	double phoe = 0;
	double frag = 0;
	double err = 0;
	for(int j = 1; j<frac->GetNbinsY()+1; j++){	
	    double val = frac->GetBinContent(i,j);
	    double val_e = frac->GetBinError(i,j);
	    if(val>0){
		if(j==1){
		    fr->SetBinContent(i,val);		 

		    cen = val;
		}else{
		    if(j==2 || j==3 || j==6 || j == 7){
			if(j==2)phoe = val;
			if(j==3)if(fabs(cen-val)>fabs(cen-phoe))phoe = val;		
			if(j==3)err+= (cen-phoe)*(cen-phoe);
			if(j==6)frag = val;
			if(j==7)if(fabs(cen-val)>fabs(cen-frag))frag = val;		
			if(j==7)err+= (cen-frag)*(cen-frag);
		    }else{
			err+= (cen-val)*(cen-val);
		    }
		    //cout << j << " " << cen << " " << val << " " << fabs(cen-val)/cen << " ";
		}
		//cout << endl;
	    }
	}
	if(err>0 && cen>0){
	    //cout << "Total error " << sqrt(err) << " " << sqrt(err)/cen << endl;
	    fr->SetBinError(i,sqrt(err));
	}
    }
}
