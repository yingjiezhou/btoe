#include "prettycanvasAll.C"
gSystem->Load("libRooFit.so");

using namespace RooFit;

void fitdata1D(TH1F *data,TH1F *data_e,TH1F* data_emis,TH1F *data_pi, TH1F *data_2pi,TH1F *data_k,TH1F *data_p,TH1F* data_D,TH1F* data_jpsi,TH1F* data_B,int daughter,int mag, int save,
	       char outputfile[],char datfile[],char datc[],char dir1[],char dir2[],char dir3[],char dir4[],char dir5[],char dir6[],
	       int pt,int eta, int rs,float cutLow,float cutHigh,double ptLow ,double ptHigh,double eff_b, int pur_dir, int HT, double e_const)
{

    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
    char file_purity[50];
    sprintf(file_purity,"../FitPurity/%i/yields.dat",pur_dir);
    ifstream purData(file_purity);
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};

   

    TH1F *hp1 = new TH1F("hp1","",numPtBins,binning);  
    if(purData.is_open()){
	while(!purData.eof()){
	    char out[50];
	    double y=0;
	    double y_e=0;
	    double pT=0;
	    double p1 = 0;
	    double eff=0;
	    double a1 = 0;
	    double a2=0;	    
	    purData >> pT >> y >> y_e >> p1 >> eff >> a1 >> a2;
	    if(y<.0001)y=0;
	    int a=y;
	    int b=y_e;
	    if(pT!=0){      
		hp1->SetBinContent(pT,p1-0.15);
		hp1->SetBinError(pT,p1*b/a);

	    }
	}

    } else {
	cout <<"Nope \n";
    }
    double purity = hp1->GetBinContent(pt);
    double puritye = hp1->GetBinError(pt);
    cout << "Using hadron purity of "<< purity << endl;

/////Minuit Options
    bool hesse = true;
    bool minos = false;

    const double _start = -4;  
    const double _end = -1;
    bool roodatahist = 1;
    RooRealVar *DCA = new RooRealVar("DCA","DCA",_start,_end);
    RooDataHist *dataHist = new RooDataHist("dataHist","dataHist",RooArgList(*DCA),data);
    RooDataHist *dataHist_D = new RooDataHist("dataHist_D","dataHist_D",RooArgList(*DCA),data_D);
    RooDataHist *dataHist_B = new RooDataHist("dataHist_B","dataHist_B",RooArgList(*DCA),data_B);
    RooDataHist *dataHist_pi = new RooDataHist("dataHist_pi","dataHist_pi",RooArgList(*DCA),data_pi);
    RooDataHist *dataHist_e = new RooDataHist("dataHist_e","dataHist_e",RooArgList(*DCA),data_e);
//Signals
    if(roodatahist){

	RooRealVar mean1("mean1","mean1",-2,-3,-1);
	RooRealVar mean11("mean11","mean11",-2,-3,-1);
	RooRealVar sigma1("sigma1","sigma1",1,0.1,15);  
	RooRealVar sigma11("sigma11","sigma11",1,0.1,15); 
 	RooRealVar sigma111("sigma111","sigma111",10,0.1,15);
	RooRealVar frac1("frac1","frac1",0.3,0.0,1);
	if(pt<9){
	    RooBifurGauss g11_2("g11_2","g11_2",*DCA,mean1,sigma1,sigma11);
	    RooGaussian g11_1("g11_1","g11_1",*DCA,mean11,sigma111);
	}
	else if(pt==9){
	    RooBifurGauss g11_2("g11_2","g11_2",*DCA,mean1,sigma1,sigma11);
	    RooGaussian g11_1("g11_1","g11_1",*DCA,mean1,sigma111);
	}
	RooAddPdf g11("g11","g11",g11_1,g11_2,frac1);
	RooProdPdf e1_signal("e1_signal","e1_signal",g11);
	RooRealVar e_signal_yield_cont("e_signal_yield_cont","e_signal_yield_cont",1000,0,1000000000);
	RooArgList shapeList_e;
	RooArgList yieldList_e;    
	shapeList_e.add(e1_signal);  
	yieldList_e.add(e_signal_yield_cont);
        RooAddPdf completePDF_e("completePDF_e","completePDF_e",shapeList_e,yieldList_e);
	RooAbsReal *nllData_e  = completePDF_e.createNLL(*dataHist_e,Extended(kTRUE));
        RooAddition * nll_e = new RooAddition("nll_e","nll_e",RooArgSet(*nllData_e));
        RooMinuit m_e (*nll_e);
        m_e.setVerbose(kFALSE);
        m_e.migrad();
	RooDataSet *d1e = (RooDataSet*)g11.generate(*DCA,100000);
	TH1F* h1e = (TH1F*)d1e->createHistogram("h1e",*DCA,Binning(data->GetNbinsX(),data->GetBinLowEdge(1),data->GetBinLowEdge(data->GetNbinsX())+data->GetBinWidth(5)));
	RooDataHist *dataHist_e1 = new RooDataHist("dataHist_e1","dataHist_e1",RooArgList(*DCA),h1e);
	//RooDataHist *dataHist_e1 =d1e->binnedClone();
	//RooHistPdf g1("g1","g1",RooArgSet(*DCA),*dataHist_e1);
	RooHistPdf g1("g1","g1",RooArgSet(*DCA),*dataHist_e);
	RooHistPdf gb("gb","gb",RooArgSet(*DCA),*dataHist_B);
	RooHistPdf gc("gc","gc",RooArgSet(*DCA),*dataHist_D);
	RooHistPdf g2("g2","g2",RooArgSet(*DCA),*dataHist_pi);
    }   
    RooProdPdf b_signal("b_signal","b_signal",gb);
    RooProdPdf c_signal("c_signal","c_signal",gc); 
    RooProdPdf e_signal("e_signal","e_signal",g1);
    RooProdPdf pi_signal("pi_signal","pi_signal",g2); 

    RooRealVar signal_yield("signal_yield","signal_yield",10000,0,4e9);
    signal_yield.setVal(data->GetEntries());
    signal_yield.setConstant(1);

    RooRealVar npe_ratio("npe_ratio","npe_ratio",0.7,0,1);
    RooRealVar b_ratio("b_ratio","b_ratio",0.6,0,1);
    RooRealVar bkg_ratio("bkg_ratio","bkg_ratio",0.3,0,0.8);    
    RooRealVar e_ratio("e_ratio","e_ratio",0.3,0,0.8); 
    e_ratio.setVal(e_const);
    //if(!HT&&pt==7)e_ratio.setRange(0,1);
    //else 
    e_ratio.setRange(e_const-0.01,e_const+0.01);
    //e_ratio.setConstant(1);
    RooFormulaVar b_signal_yield("b_signal_yield","@0*@1*@2",RooArgList(b_ratio,signal_yield,npe_ratio));
    RooFormulaVar c_signal_yield("c_signal_yield","(1-@0)*@1*@2",RooArgList(b_ratio,signal_yield,npe_ratio));
    //RooFormulaVar pi_signal_yield("pi_signal_yield","@0*@1*(1-@2)",RooArgList(bkg_ratio,signal_yield,npe_ratio));
    RooFormulaVar e_signal_yield("e_signal_yield","@0*@1",RooArgList(e_ratio,signal_yield));

    RooRealVar PurVal("PurVal","PurVal",0.6,-1,1);
    PurVal.setVal(purity);
    //PurVal.setRange(0.2,1);
    //PurVal.setConstant(1);
    //RooFormulaVar pi_signal_yield("pi_signal_yield","(1-@0)*(@1+@2+@3)",RooArgList(PurVal,b_signal_yield,c_signal_yield,e_signal_yield));
    RooFormulaVar pi_signal_yield("pi_signal_yield","(1-@0)*(@1)",RooArgList(PurVal,signal_yield));
    //RooRealVar b_signal_yield("pi_signal_yield","pi_signal_yield",1000,0,1e6); 
    RooArgList shapeList;
    RooArgList yieldList;

    shapeList.add(b_signal);
    shapeList.add(c_signal);
    shapeList.add(e_signal);
    shapeList.add(pi_signal);
    
    yieldList.add(b_signal_yield);
    yieldList.add(c_signal_yield);
    yieldList.add(e_signal_yield);
    yieldList.add(pi_signal_yield);

//All together now
    RooAddPdf completePDF("completePDF","completePDF",shapeList,yieldList);
   
//Now fit All Data
    RooAbsReal *nllData = completePDF.createNLL(*dataHist,Extended(kTRUE));
    RooAddition * nll = new RooAddition("nll","nll",RooArgSet(*nllData));  
    RooMinuit m (*nll);
    m.setVerbose(kFALSE);
    m.migrad();
    if(hesse)m.hesse();
    if(minos)m.minos();
    // Construct plotables // Don't change anything from hear on unless you want to change how a plot looks or what is output below
    if(1){//!roodatahist){
	RooPlot *DCAFrame_e = DCA->frame();
	dataHist_e->plotOn(DCAFrame_e,Name("HistM_e"));
	completePDF_e.plotOn(DCAFrame_e,Name("e_Curve_e"));

    }
    RooPlot *DCAFrame = DCA->frame();
    dataHist->plotOn(DCAFrame,Name("HistM"));
    completePDF.plotOn(DCAFrame,Name("DCA_Curve"));
    completePDF.plotOn(DCAFrame,Components(RooArgSet(e_signal)),LineStyle(6),LineColor(kOrange-3),Name("pe"));    
    completePDF.plotOn(DCAFrame,Components(RooArgSet(pi_signal)),LineStyle(8),LineColor(kRed),Name("pi"));
    completePDF.plotOn(DCAFrame,Components(RooArgSet(b_signal)),LineStyle(7),LineColor(kGreen-2),FillStyle(1000),FillColor(kGreen-1),Name("b"));
    completePDF.plotOn(DCAFrame,Components(RooArgSet(c_signal)),LineStyle(9),LineColor(kMagenta),FillColor(kGreen-2),Name("c"));
        
    dataHist->plotOn(DCAFrame,Name("HistM"));
    RooPlot *DCAFrame11 = DCA->frame();
    dataHist->plotOn(DCAFrame11,Name("HistMM"));
    completePDF.plotOn(DCAFrame,Name("DCA_Curve"));   
    RooHist* pullHisto = DCAFrame->pullHist("HistM","DCA_Curve");
    RooPlot* pullPlot = DCA->frame();
    pullHisto->SetFillColor(1);
    pullHisto->SetLineColor(0);
    pullPlot->addPlotable(pullHisto,"B");
    if(1){//!roodatahist){
	RooHist* pullHisto_e = DCAFrame_e->pullHist("HistM_e","e_Curve_e");
	RooPlot* pullPlot_e = DCA->frame();
	pullHisto_e->SetFillColor(1);
	pullHisto_e->SetLineColor(0);
	pullPlot_e->addPlotable(pullHisto_e,"B");
    }

    RooArgSet *freeparam = completePDF.getParameters(dataHist);
    int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
    TPaveText* txt = new TPaveText(0.2,0.75,0.47,0.85,"BRNDC");
    txt->SetTextSize(0.07);
    txt->SetTextColor(1);
    txt->SetBorderSize(0.1);
    txt->SetFillColor(0);
    txt->SetFillStyle(0);
   TPaveText* txt1 = new TPaveText(0.56,0.55,0.9,0.71,"BRNDC");
    txt1->SetTextSize(0.07);
    txt1->SetTextColor(1);
    txt1->SetBorderSize(0.1);
    txt1->SetFillColor(0);
    txt1->SetFillStyle(0);
    char chi2[50];
    char entr[50];
    char ptbin[50];    
    sprintf(chi2,"#chi^{2}/NDF=%1.2f",DCAFrame->chiSquare("DCA_Curve","HistM",numfreeparam));
    //sprintf(entr,"Signal Yield: %i #pm %i",(int)e_signal_yield.getVal(),(int)TMath::Max(fabs(e_signal_yield.getErrorLo()),e_signal_yield.getErrorHi()));
    if(1){  
        sprintf(ptbin,"#it{p}_{T} #in [%1.1f,%1.1f] GeV",ptLow,ptHigh);
	if(HT)sprintf(entr,"High Tower");
	if(!HT)sprintf(entr,"Min. Bias");
        txt->AddText(ptbin);
	txt1->AddText(entr);
	txt1->AddText(chi2);

	DCAFrame->addObject(txt1);	
        DCAFrame->addObject(txt);
	DCAFrame11->addObject(txt);
    }    
//Objects for saving yields and so forth
    double yields[5];
    double yields_errors[5];
    yields[0]=(int)e_signal_yield.getVal();
    yields[1]=(int)pi_signal_yield.getVal();
    yields[2]=(int)b_signal_yield.getVal();
    yields[3]=(int)c_signal_yield.getVal();
    yields_errors[0]=yields[0]*sqrt(e_ratio.getError()*e_ratio.getError()/e_ratio.getVal()/e_ratio.getVal());//(int)TMath::Max(fabs(e_signal_yield.getErrorLo()),e_signal_yield.getErrorHi());
    yields_errors[1]=yields[1]*sqrt(PurVal.getError()*PurVal.getError()/PurVal.getVal()/PurVal.getVal());
    yields_errors[2]=yields[2]*sqrt(npe_ratio.getError()*npe_ratio.getError()/npe_ratio.getVal()/npe_ratio.getVal()+b_ratio.getError()*b_ratio.getError()/b_ratio.getVal()/b_ratio.getVal());
    yields_errors[3]=yields[3]*sqrt(npe_ratio.getError()*npe_ratio.getError()/npe_ratio.getVal()/npe_ratio.getVal()+b_ratio.getError()*b_ratio.getError()/b_ratio.getVal()/b_ratio.getVal());
    yields_errors[4]=0;//(int)TMath::Max(fabs(c_signal_yield.getErrorLo()),c_signal_yield.getErrorHi())/yields[3] * yields[4];
 
    DCA->setRange("range1",-1.5,-1);
    RooAbsReal* e1_1 = g1.createIntegral(*DCA,*DCA,"range1");
    RooAbsReal* had1_1 = g2.createIntegral(*DCA,*DCA,"range1");
    RooAbsReal* b_1 = gb.createIntegral(*DCA,*DCA,"range1");
    RooAbsReal* c_1 = gc.createIntegral(*DCA,*DCA,"range1");
    double b_int = b_1->getVal();
    double c_int = c_1->getVal();
    double e_int = e1_1->getVal();
    double h_int = had1_1->getVal();    

    double pur1 = b_int*yields[2] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
    double pur2 = c_int*yields[3] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);  
    double pur3 = e_int*yields[0] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
    double pur4 = h_int*yields[1] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);  

    DCA->setRange("range3",-2,-1);
    RooAbsReal* e1_3 = g1.createIntegral(*DCA,*DCA,"range3");
    RooAbsReal* had1_3 = g2.createIntegral(*DCA,*DCA,"range3");
    RooAbsReal* b_3 = gb.createIntegral(*DCA,*DCA,"range3");
    RooAbsReal* c_3 = gc.createIntegral(*DCA,*DCA,"range3");
    double b_int1 = b_3->getVal();
    double c_int1 = c_3->getVal();
    double e_int1 = e1_3->getVal();
    double h_int1 = had1_3->getVal();    
  
    double pur1 = b_int*yields[2] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
    double pur2 = c_int*yields[3] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);  
    double pur3 = e_int*yields[0] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]);
    double pur4 = h_int*yields[1] / (e_int*yields[0]+ h_int*yields[1] + b_int*yields[2] + c_int*yields[3]); 
    double pur11 = b_int1*yields[2] / (e_int1*yields[0]+ h_int1*yields[1] + b_int1*yields[2] + c_int1*yields[3]);
    double pur22 = c_int1*yields[3] / (e_int1*yields[0]+ h_int1*yields[1] + b_int1*yields[2] + c_int1*yields[3]);  
    double pur33 = e_int1*yields[0] / (e_int1*yields[0]+ h_int1*yields[1] + b_int1*yields[2] + c_int1*yields[3]);
    double pur44 = h_int1*yields[1] / (e_int1*yields[0]+ h_int1*yields[1] + b_int1*yields[2] + c_int1*yields[3]); 

    if (save==1){
        ofstream output1 (datfile,ios::app);
        if(output1.is_open()){
            output1 <<  pt <<" " <<  yields[2] << " " << yields_errors[2] << " " << pur1 << " " << pur11 << " " << 
		                     yields[3] << " " << yields_errors[3] << " " << pur2 << " " << pur22 << " " << 
		                     yields[0] << " " << yields_errors[0] << " " << pur3 << " " << pur33 << " " << 
	                             yields[1] << " " << yields_errors[1] << " " << pur4 << " " << pur44 << " " <<  
		                     b_ratio.getVal()  << " " <<  b_ratio.getError()<< " " <<	
		                     PurVal.getVal()<< " " <<  PurVal.getError()<< " " <<
		npe_ratio.getVal()  << " " <<  npe_ratio.getError() << " " << e_ratio.getVal()  << " " <<  e_ratio.getError() << " " << purity << " " << puritye << 	"\n";
            output1.close();
        }else(cout << "Error Opening Output Dat File!");    
    }
    cout << "====================" << endl;   
    cout << "Chi2 of Mass Fit: " << chi2 << endl;
    cout << "====================" << endl;   
    cout<< "Yields: \n";
    cout << "====================" << endl;   
    cout<<"photonic electrons: "<< yields[0] <<" +/- " << yields_errors[0] << " " << endl;
    cout<<"pions: "    << yields[1] <<" +/- " << yields_errors[1] << " " << endl;
    cout<<"b->e: "     << yields[2] <<" +/- " << yields_errors[2] << " " << endl;
    cout<<"D->e: "     << yields[3] <<" +/- " << yields_errors[3] << " " << endl;
    cout<<"Purity: "     <<  purity << endl;
    cout<<"Purity in fit: "     << (yields[2]+ yields[3]+ yields[4]+yields[0])/(yields[4]+yields[1]+ yields[2]+ yields[3]+ yields[0])  << endl;
    cout << "====================" << endl;   
    cout<< "Ratio of b/c: \n";
    cout << "====================" << endl; 
    double temp1 = (yields[3])/(yields[3]+yields[2])/(yields[3]+yields[2])*yields_errors[2];
    double temp2 = (yields[2])/(yields[3]+yields[2])/(yields[3]+yields[2])*yields_errors[3];   
 

    cout<<  b_ratio.getVal() << " #pm " << b_ratio.getError()  <<  endl;
    cout << "====================" << endl;    
    cout<< "Fraction in b-rich region (-1.5,-1): \n";
    cout << "====================" << endl;   
    cout<<"photonic electrons: "<< pur3 << endl;
    cout<<"pions: "    << pur4 << endl;
    cout<<"b->e: "     << pur1 << endl;
    cout<<"c->e: "     << pur2 << endl; 
    cout << "====================" << endl;   
    cout<< "Fraction in c-rich region (-2,-1.5): \n";
    cout << "====================" << endl;   
    cout<<"photonic electrons: "<< pur33 <<endl;
    cout<<"pions: "    << pur44 << endl;
    cout<<"b->e: "     << pur11 <<endl;
    cout<<"c->e: "     << pur22 <<endl;   
    cout << "====================" << endl;

     
    TCanvas *c1 = new TCanvas("c1","full fit");
    prettycanvasAllleg(c1,DCAFrame,pullPlot,0,data->GetMaximum()/7); 
    TCanvas *c5 = new TCanvas("c5","electron");
    prettycanvasAll(c5,DCAFrame_e,pullPlot_e,0,data_e->GetMaximum()/7);
    if(!roodatahist){
	TCanvas *c2 = new TCanvas("c2","pion");
	prettycanvasAll(c2,DCAFrame_pi,pullPlot_pi,0,data_pi->GetMaximum()/7);
	TCanvas *c7 = new TCanvas("c7","D");
	prettycanvasAll(c7,DCAFrame_D,pullPlot_D,0,data_D->GetMaximum()/7);
	TCanvas *c8 = new TCanvas("c8","B");
	prettycanvasAll(c8,DCAFrame_B,pullPlot_B,0,data_B->GetMaximum()/7);
	}
    if(save==1){
        char mass_c[150];
        char mass_pdf[150];    
        char mass_png[150];
        char mass_eps[150];   
        sprintf(mass_c,"%s.C",dir1);
        sprintf(mass_pdf,"%s.pdf",dir1);
        sprintf(mass_png,"%s.png",dir1);
        sprintf(mass_eps,"%s.eps",dir1);
        //c1->SaveAs(Form(mass_c));
        c1->SaveAs(Form(mass_pdf));
        //c1->SaveAs(Form(mass_png));
        //c1->SaveAs(Form(mass_eps));
    }
}

/*
 if(!roodatahist){ 
	//RooHistPdf gb("gb","gb",RooArgSet(*DCA),*dataHist_B,2);
        //RooHistPdf gc("gc","gc",RooArgSet(*DCA),*dataHist_D,2);
	RooRealVar meanb("meanb","meanb",-4,-5,-3);
	RooRealVar meanbb("meanbb","meanbb",-4,-5,-3);
	RooRealVar sigmab("sigmab","sigmab",1,0.0.07,5);  
	RooRealVar sigmabb("sigmabb","sigmabb",1,0.07,5);  
	RooRealVar sigmabbb("sigmabbb","sigmabbb",1,0.1,5);  
	RooRealVar sigmabbbb("sigmabbbb","sigmabbbb",1,0.05,5);  
	RooRealVar fracb("fracb","fracb",0.5,0,1);
	RooRealVar alphaLb("alphaLb","alphaLb",2.7,-0.1,10);
	RooRealVar nLb("nLb","nLb",1,0,4);
	RooRealVar alphaRb("alphaRb","alphaRb",3.2,0.1,10);
	RooRealVar nRb("nRb","nRb",1);
	//RooDSCBShape gb_1("gb_1","gb_1",*DCA,meanb,sigmab,alphaLb,nLb,alphaLb,nLb);
	RooBifurGauss gb_1("gb_1","gb_1",*DCA,meanb,sigmab,sigmabbb);
	RooGaussian gb_2("gb_2","gb_2",*DCA,meanbb,sigmabb);
	//RooAddPdf gb("gb","gb",gb_1,gb_2,fracb);
	RooBifurGauss gb("gb","gb",*DCA,meanb,sigmab,sigmabb);
	RooRealVar meanc1("meanc1","meanc1",-6,-10,0);
	RooRealVar meanc2("meanc2","meanc2",-3,-10,0);
	RooRealVar meanc3("meanc3","meanc3",-3,-10,0);
	RooRealVar meanc4("meanc4","meanc4",-3,-10,0);
	RooRealVar sigmac1("sigmac1","sigmac1",1,0.3,8);  
	RooRealVar sigmac2("sigmac2","sigmac2",1,0.3,8);  
	RooRealVar sigmac3("sigmac3","sigmac3",1,0.3,8); 
	RooRealVar sigmac4("sigmac4","sigmac4",1,0.3,8);  
	RooRealVar sigmac5("sigmac5","sigmac5",1,0.3,8);  
	RooRealVar sigmac6("sigmac6","sigmac6",1,0.3,8);  
	RooRealVar sigmac7("sigmac7","sigmac7",1,0.3,8);  
	RooRealVar sigmac8("sigmac8","sigmac8",1,0.3,8);  


	RooRealVar alphaLc("alphaLc","alphaLc",2.7,-10,10);
	RooRealVar nLc("nLc","nLc",1,0,5);
	RooRealVar alphaRc("alphaRc","alphaRc",3.2,-10,10);
	RooRealVar nRc("nRc","nRc",1,0,5);
	//RooDSCBShape gc("gc","gc",*DCA,meanc,sigmac,alphaLc,nLc,alphaLc,nLc); 
	RooRealVar fracc("fracc","fracc",0.5,0.0,1);
	RooRealVar fraccc("fraccc","fraccc",0.5,0.1,1);
	RooBifurGauss gc_1("gc_1","gc_1",*DCA,meanc1,sigmac1,sigmac2);
	RooBifurGauss gcc_1("gcc_1","gcc_1",*DCA,meanc2,sigmac3,sigmac4);
	RooBifurGauss gc_2("gc_2","gc_2",*DCA,meanc3,sigmac5,sigmac6);
	RooBifurGauss gcc_2("gcc_2","gcc_2",*DCA,meanc4,sigmac7,sigmac8);
	RooAddPdf gcp("gcp","gcp",gc_1,gc_2,fracc);
	RooAddPdf gc("gc","gc",gcc_1,gcp,fraccc);
	RooAddPdf gcc("gcc","gcc",gcc_1,gcc_2,fraccc);


	RooRealVar mean1("mean1","mean1",-7,-9,-1);
	RooRealVar mean11("mean11","mean11",-7,-9,-6);
	RooRealVar mean111("mean111","mean111",-7,-10,0);
	RooRealVar mean1111("mean1111","mean1111",-4,-5,0);
	RooRealVar sigma1("sigma1","sigma1",1,0.1,15);  
	RooRealVar sigma11("sigma11","sigma11",1,0.1,15); 
 	RooRealVar sigma111("sigma111","sigma111",10,0.1,15);
	RooRealVar sigma1111("sigma1111","sigma1111",10,0.1,15);
	RooRealVar sigma11111("sigma11111","sigma11111",10,0.1,15);
	RooRealVar frac1("frac1","frac1",0.3,0.0,1);
	RooRealVar frac11("frac11","frac11",0.1,0.1,1);
	RooRealVar frac111("frac111","frac111",0.1,0.1,1);
	//RooBifurGauss g1("g1","g1",*DCA,mean1,sigma1,sigma11);
	RooBifurGauss g1_2("g1_2","g1_2",*DCA,mean1,sigma1,sigma11);
	RooGaussian g1_1("g1_1","g1_1",*DCA,mean1,sigma111);

	RooGaussian g1_3("g1_3","g1_3",*DCA,mean111,sigma1111);
	RooGaussian g1_4("g1_4","g1_4",*DCA,mean1111,sigma11111);
	RooRealVar alphaL1("alphaL1","alphaL1",2.7,0.1,10);
	RooRealVar nL1("nL1","nL1",1,1,5);
	RooRealVar alphaR1("alphaR1","alphaR1",3.2,0.1,10);
	RooRealVar nR1("nR1","nR1",1,1,5);
	//RooDSCBShape g1_1("g1_1","g1_1",*DCA,mean11,sigma111,alphaL1,nL1,alphaR1,nR1);

	if(1)RooAddPdf g1("g1","g1",g1_1,g1_2,frac1);//pt>4
	RooAddPdf g1_p("g1_p","g1_p",g1_1,g1_2,frac1);
        if(0)RooAddPdf g1_p1("g1_p1","g1_p1",g1_p,g1_3,frac11);
	if(0)RooAddPdf g1("g1","g1",g1_p1,g1_4,frac111);
	RooRealVar mean2("mean2","mean2",-7,-10,-3);
	RooRealVar mean22("mean22","mean22",-7,-10,-3);
	RooRealVar sigma2("sigma2","sigma2",1,0.1,14);    
	RooRealVar sigma22("sigma22","sigma22",1,0.1,14);
	RooRealVar sigma222("sigma222","sigma222",4,0.1,40);
	RooRealVar frac2("frac2","frac2",0.8,0,1);
	RooBifurGauss g2_2("g2_2","g2_2",*DCA,mean2,sigma2,sigma22);
	RooGaussian g2_1("g2_1","g2_1",*DCA,mean22,sigma222);
	RooRealVar alphaL2("alphaL2","alphaL2",2.7,0,10);
	RooRealVar nL2("nL2","nL2",1,0,5);
	RooRealVar alphaR2("alphaR2","alphaR2",3.2,0,10);
	RooRealVar nR2("nR2","nR2",1,0,5);
	//RooDSCBShape g2_2("g2_2","g2_2",*DCA,mean2,sigma222,alphaL2,nL2,alphaL2,nL2);
	RooAddPdf g2("g2","g2",g2_1,g2_2,frac2);

	RooRealVar mean3("mean3","mean3",-4,-6,-2);
	RooRealVar sigma3("sigma3","sigma3",1,0.2,5.);  
	RooRealVar sigma33("sigma33","sigma33",1,0.2,5.);
        RooRealVar sigma333("sigma333","sigma333",1,0.2,5.);    
	RooRealVar frac3("frac3","frac3",0.4,0.1,1);
	RooBifurGauss g3_1("g3_1","g3_1",*DCA,mean3,sigma3,sigma33);  
	RooGaussian g3_2("g3_2","g3_2",*DCA,mean3,sigma333);    
	RooAddPdf g3("g3","g3",g3_1,g3_2,frac3);

	RooRealVar mean4("mean4","mean4",-4,-7,-0);
	RooRealVar sigma4("sigma4","sigma4",1,0,5.); 
	RooRealVar sigma44("sigma44","sigma44",1,0,3.);    
	RooBifurGauss g4("g4","g4",*DCA,mean4,sigma4,sigma44); 

	RooRealVar mean5("mean5","mean5",5,3,10);
	RooRealVar sigma5("sigma5","sigma5",1,0,5.);  
	RooRealVar sigma55("sigma55","sigma55",1,0,5.);  
	RooGaussian g5("g5","g5",*DCA,mean5,sigma5); 
    } */
