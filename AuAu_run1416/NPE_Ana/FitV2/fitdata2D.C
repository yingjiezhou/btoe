#include "prettycanvasAll.C"
gSystem->Load("libRooFit.so");

using namespace RooFit;

void fitdata2D(TH1F *data,TH1F *data_1,TH1F *data_2,int daughter,int mag, int save,
	       char outputfile[],char datfile[],char datc[],char dir1[],char dir2[],char dir3[],char dir4[],char dir5[],char dir6[],
	       int pt,int eta, int rs,float cutLow,float cutHigh,double ptLow ,double ptHigh,double eff_b, int pur_dir, double corrb,double corrc,double corrbkg, int doSys, int HT)
{
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);

    TFile *phoe_res = new TFile("../../NPE_MC/Ana/v2_hists/phoe_v2.root");
    PhoEV2 = (TH1F*)phoe_res->Get("PhoEV2");
    TFile *pion_res = new TFile("../../NPE_MC/Ana/v2_hists/pion_v2.root");
    PionV2 = (TH1F*)pion_res->Get("PionV2");
    TFile *d0_res = new TFile("../../NPE_MC/Ana/v2_hists/D_v2.root");
    D0V2 = (TH1F*)d0_res->Get("D0V2");

    RooRealVar frac_b("frac_b","frac_b",0,1);
    RooRealVar frac_c("frac_c","frac_c",0,1);
    RooRealVar frac_e("frac_e","frac_e",0,1);
    RooRealVar frac_h("frac_h","frac_h",0,1);
    RooRealVar frac_b1("frac_b1","frac_b1",0,1);
    RooRealVar frac_c1("frac_c1","frac_c1",0,1);
    RooRealVar frac_e1("frac_e1","frac_e1",0,1);
    RooRealVar frac_h1("frac_h1","frac_h1",0,1);
    RooRealVar frac_b2("frac_b2","frac_b2",0,1);
    RooRealVar frac_c2("frac_c2","frac_c2",0,1);
    RooRealVar frac_e2("frac_e2","frac_e2",0,1);
    RooRealVar frac_h2("frac_h2","frac_h2",0,1);
  
    int const numPtBins=9;//here
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};//here
    TH1F *hp1 = new TH1F("hp1","",numPtBins,binning);
    TH1F *hv2syst1 = new TH1F("hv2syst1","hv2syst1",4000,-0.2.,0.2);
    TH1F *hv2syst2 = new TH1F("hv2syst2","hv2syst2",2000,0,0.2);
    TH1F *hv2syst3 = new TH1F("hv2syst3","hv2syst3",2000,0,0.2);
    TH1F *hv2syst4 = new TH1F("hv2syst4","hv2syst4",2000,0,0.2);
    TFile *fractions = new TFile("../FitIP/root/Fractions.root");//here
    if(!HT){
	bfrac = (TH1F*)fractions->Get("bfrac");
	cfrac = (TH1F*)fractions->Get("cfrac");    
	efrac = (TH1F*)fractions->Get("efrac");          
	hfrac = (TH1F*)fractions->Get("hfrac");
    }else if(HT){
	bfrac = (TH1F*)fractions->Get("bfrac_ht");
        cfrac = (TH1F*)fractions->Get("cfrac_ht");
        efrac = (TH1F*)fractions->Get("efrac_ht");
        hfrac = (TH1F*)fractions->Get("hfrac_ht");
    }
    int binn = bfrac->FindBin(binning[pt-1]);

    frac_h.setVal(hfrac->GetBinContent(binn));
    frac_e.setVal(efrac->GetBinContent(binn));
    frac_c.setVal(cfrac->GetBinContent(binn));
    frac_b.setVal(bfrac->GetBinContent(binn));
    
    TF1 *bgaus = new TF1("bgaus","gaus(0)",0,1);
    bgaus->SetParameter(0,1);
    bgaus->SetParameter(1,bfrac->GetBinContent(binn)); 
    bgaus->SetParameter(2,bfrac->GetBinError(binn));  
    TF1 *cgaus = new TF1("cgaus","gaus(0)",0,1);
    cgaus->SetParameter(0,1);
    cgaus->SetParameter(1,cfrac->GetBinContent(binn)); 
    cgaus->SetParameter(2,cfrac->GetBinError(binn)); 
    TF1 *egaus = new TF1("egaus","gaus(0)",0,1);
    egaus->SetParameter(0,1);
    egaus->SetParameter(1,efrac->GetBinContent(binn)); 
    egaus->SetParameter(2,efrac->GetBinError(binn)); 
    TF1 *hgaus = new TF1("hgaus","gaus(0)",0,1);
    hgaus->SetParameter(0,1);
    hgaus->SetParameter(1,hfrac->GetBinContent(binn)); 
    hgaus->SetParameter(2,hfrac->GetBinError(binn)); 

    frac_h.setConstant(1);
    frac_e.setConstant(1);
    frac_c.setConstant(1);
    frac_b.setConstant(1);
    frac_h1.setConstant(1);
    frac_e1.setConstant(1);
    frac_c1.setConstant(1);
    frac_b1.setConstant(1);
    frac_h2.setConstant(1);
    frac_e2.setConstant(1);
    frac_c2.setConstant(1);
    frac_b2.setConstant(1);
/////Minuit Options
    bool hesse = true;
    bool minos = false;//true;

    const double _start = 0;  
    const double _end = TMath::Pi()/2;
    RooRealVar *V2 = new RooRealVar("V2","V2",_start,_end);
    RooDataHist *dataHist = new RooDataHist("dataHist","dataHist",RooArgList(*V2),data);
    RooDataHist *dataHist1 = new RooDataHist("dataHist1","dataHist1",RooArgList(*V2),data_1);
    RooDataHist *dataHist2 = new RooDataHist("dataHist2","dataHist2",RooArgList(*V2),data_2);
  
    double d0v2 = D0V2->GetBinContent(pt);
    double phoev2 = PhoEV2->GetBinContent(pt);
    double pionv2 = PionV2->GetBinContent(pt);
    double pionv2er = PionV2->GetBinError(pt);
    RooRealVar v2_b("v2_b","v2_b",0.05,-1,1.);
    RooRealVar v2_c("v2_c","v2_c",d0v2/corrb);
    //RooRealVar v2_c("v2_c","v2_c",0.1,0.5,1.);
    RooRealVar v2_e("v2_e","v2_e",phoev2/corrb);
    RooRealVar v2_h("v2_h","v2_h",pionv2/corrb);
       
  
    TF1 *cgaus1 = new TF1("cgaus","gaus(0)",0,1);
    cgaus1->SetParameter(0,1);
    cgaus1->SetParameter(1,d0v2/corrb);
    cgaus1->SetParameter(2,d0v2/corrb*0.5); 
    TF1 *egaus1 = new TF1("egaus","gaus(0)",0,1);
    egaus1->SetParameter(0,1);
    egaus1->SetParameter(1,phoev2/corrb); 
    egaus1->SetParameter(2,phoev2/corrb*0.5); 
    TF1 *hgaus1 = new TF1("hgaus","gaus(0)",0,1);
    hgaus1->SetParameter(0,1);
    hgaus1->SetParameter(1,pionv2/corrb); 
    hgaus1->SetParameter(2,pionv2er/corrb); 





    RooGenericPdf pdf_b ("pdf_b","(1+2*(@1*@2 + @3*@4 + @5*@6 + @7*@8)*cos(2*@0))",RooArgList(*V2,v2_b,frac_b,v2_c,frac_c,v2_h,frac_h,v2_e,frac_e));//,v2_h,frac_h
    RooGenericPdf pdf_c ("pdf_c","(1+2*(@1*@2 + @3*@4 + @5*@6 + @7*@8)*cos(2*@0))",RooArgList(*V2,v2_b,frac_b1,v2_c,frac_c1,v2_e,frac_e1, v2_h,frac_h1));//,v2_h,frac_h1
    RooGenericPdf pdf_bkg ("pdf_bkg","(1+2*(@1*@2 + @3*@4)*cos(2*@0))",RooArgList(*V2,v2_h,frac_h2,v2_e,frac_e2));//,v2_h,frac_h  
    //RooGenericPdf pdf_b ("pdf_b","(1+2*(@1)*cos(2*@0))",RooArgList(*V2,v2_b));
    //RooGenericPdf pdf_c ("pdf_c","(1+2*(@1)*cos(2*@0))",RooArgList(*V2,v2_c));

    RooProdPdf signal("signal","signal",pdf_b);
    RooProdPdf signal1("signal1","signal1",pdf_c);
    RooProdPdf signal2("signal2","signal2",pdf_bkg);
    RooRealVar signal_yield("signal_yield","signal_yield",1000,0,4e7);
    RooRealVar signal_yield1("signal_yield1","signal_yield1",1000,0,4e7);
    RooRealVar signal_yield2("signal_yield2","signal_yield2",1000,0,4e7);
    RooArgList shapeList;
    RooArgList yieldList;
    RooArgList shapeList1;
    RooArgList yieldList1; 
    RooArgList shapeList2;
    RooArgList yieldList2; 
    shapeList.add(signal);
    yieldList.add(signal_yield);
    shapeList1.add(signal1);
    yieldList1.add(signal_yield1);
    shapeList2.add(signal2);
    yieldList2.add(signal_yield2); 
//All together now
    RooAddPdf completePDF("completePDF","completePDF",shapeList,yieldList);
    RooAddPdf completePDF1("completePDF1","completePDF1",shapeList1,yieldList1);
    RooAddPdf completePDF2("completePDF2","completePDF2",shapeList2,yieldList2);  
//Now fit All Data
    RooAbsReal *nllData = completePDF.createNLL(*dataHist,Extended(kTRUE));
    RooAbsReal *nllData1 = completePDF1.createNLL(*dataHist1,Extended(kTRUE));
    RooAbsReal *nllData2 = completePDF1.createNLL(*dataHist2,Extended(kTRUE));
    RooAddition * nll = new RooAddition("nll","nll",RooArgSet(*nllData));  
    RooMinuit m (*nll);
    m.setVerbose(kFALSE);
    m.migrad();
    if(hesse)m.hesse();
    if(minos)m.minos();
    // Construct plotables // Don't change anything from hear on unless you want to change how a plot looks or what is output below
    RooPlot *V2Frame = V2->frame();
    dataHist->plotOn(V2Frame,Name("HistM"));
    completePDF.plotOn(V2Frame,Name("V2_Curve"));
    RooPlot *V2Frame1 = V2->frame();
    dataHist1->plotOn(V2Frame1,Name("HistM1"));
    completePDF1.plotOn(V2Frame1,Name("V2_Curve1"));
    RooPlot *V2Frame2 = V2->frame();
    dataHist2->plotOn(V2Frame2,Name("HistM1"));
    completePDF2.plotOn(V2Frame2,Name("V2_Curve1"));
    //completePDF.plotOn(V2Frame,Components(RooArgSet(pdf_e)),LineStyle(6),LineColor(kOrange-3),Name("pe"));    
    //completePDF.plotOn(V2Frame,Components(RooArgSet(pdf_h)),LineStyle(8),LineColor(kRed),Name("pi"));
    //completePDF.plotOn(V2Frame,Components(RooArgSet(pdf_b)),LineStyle(7),LineColor(kGreen-2),FillStyle(1000),FillColor(kGreen-1),Name("b"));
    //completePDF.plotOn(V2Frame,Components(RooArgSet(pdf_c)),LineStyle(9),LineColor(kMagenta),FillColor(kGreen-2),Name("c"));
  

    RooArgSet *freeparam = completePDF.getParameters(dataHist);
    int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
    TPaveText* txt = new TPaveText(0.35,0.2,0.55,0.4,"BRNDC");
    txt->SetTextSize(0.05);
    txt->SetTextColor(1);
    txt->SetBorderSize(0.1);
    txt->SetFillColor(0);
    txt->SetFillStyle(0);
    TPaveText* txt1 = new TPaveText(0.35,0.2,0.55,0.4,"BRNDC");
    txt1->SetTextSize(0.05);
    txt1->SetTextColor(1);
    txt1->SetBorderSize(0.1);
    txt1->SetFillColor(0);
    txt1->SetFillStyle(0);
   TPaveText* txt2 = new TPaveText(0.35,0.2,0.55,0.4,"BRNDC");
    txt2->SetTextSize(0.05);
    txt2->SetTextColor(1);
    txt2->SetBorderSize(0.1);
    txt2->SetFillColor(0);
    txt2->SetFillStyle(0);
    char chi2[50];
    char entr[50];
    char entr1[50];
    char entr2[50];
    char ptbin[50];    
    sprintf(chi2,"%3.4f",V2Frame->chiSquare("V2_Curve","HistM",numfreeparam));
    if(1){  
        sprintf(ptbin,"#it{p}_{T} #in [%1.1f,%1.1f] GeV",ptLow,ptHigh);
        sprintf(entr,"log_{10}(|DCA|/cm) #in [%1.1f,%1.1f] GeV",-2,-1);
        sprintf(entr1,"ln(|DCA|/cm) #in [%1.f,%1.f] GeV",-5,-4);
        sprintf(entr2,"ln(|DCA|/cm) #in [-10,-2] GeV");
        txt->AddText(ptbin);
	txt1->AddText(ptbin);
	txt2->AddText(ptbin);
	txt->AddText(entr);
	txt1->AddText(entr1);
	txt2->AddText(entr2);
        V2Frame->addObject(txt);
        V2Frame1->addObject(txt1);
	V2Frame2->addObject(txt2);
    }    
//Objects for saving yields and so forth
    cout << "====================" << endl;  
    cout << "Using hadron fraction of (c-region)  "<< frac_h1.getVal() << endl;
    cout << "Using phoe e fraction of (c-region)  "<< frac_e1.getVal() << endl;
    cout << "Using c fraction of (c-region)  "     << frac_c1.getVal() << endl;
    cout << "Using b fraction of (c-region)  "     << frac_b1.getVal() << endl;
    cout << "====================" << endl;  
    cout << "Using hadron fraction of (b-region)  "<< frac_h.getVal() << endl;
    cout << "Using phoe e fraction of (b-region)  "<< frac_e.getVal() << endl;
    cout << "Using c fraction of (b-region)  "     << frac_c.getVal() << endl;
    cout << "Using b fraction of (b-region)  "     << frac_b.getVal() << endl;
    cout << "====================" << endl;   
    cout << "Chi2 of Mass Fit: " << chi2 << endl;
    cout << "====================" << endl;   
    cout << "V2's: " <<  endl;  
    cout << "Using 1/res corr (b-rich, c-rich, bkg-rich) " << corrb << " " << corrc<< " " << corrbkg << endl; 
    cout << "b: "   <<  v2_b.getVal()*corrb << " +/- " << v2_b.getError()*corrb << endl;  
    cout << "c: "   <<  v2_c.getVal()*corrb << " +/- " << v2_c.getError()*corrb << endl;     
    cout << "e: "      <<  v2_e.getVal()*corrb << " +/- " << v2_e.getError()*corrb << endl;  
    cout << "hadron: " <<  v2_h.getVal()*corrb << " +/- " << v2_h.getError()*corrb << endl;  


    double sys = 0;
    double central = v2_b.getVal()*corrb;
    double error = v2_b.getError()*corrb;
    if(doSys){
	m.setVerbose(0);
	for(int iloop = 0;iloop<10000;iloop++){
	
	    double shift22 = cgaus1->GetRandom();
	    double shift33 = hgaus1->GetRandom();
	    double shift44 = egaus1->GetRandom();
	    v2_c->setVal(shift22);
	    v2_h->setVal(shift33);
	    v2_e->setVal(shift44);
	    v2_c.setConstant(1);
	    v2_e.setConstant(1);
	    v2_h.setConstant(1);
	    double shift1 = 0;
	    double shift2 = 0 ;
	    double shift3 = 0 ;
	    double shift4 = 0 ;
	    do{
		shift1 = bgaus->GetRandom();
		shift2 = cgaus->GetRandom();
		shift3 = hgaus->GetRandom();
		shift4 = egaus->GetRandom();
	    }
	    while(shift1+shift2+shift3+shift4>1)
	  
		frac_b.setVal(shift1);
	    frac_c.setVal(shift2);	
	    frac_h.setVal(shift3);
	    frac_e.setVal(shift4);
	    frac_b.setConstant(1);
	    frac_c.setConstant(1);
	    frac_e.setConstant(1);
	    frac_h.setConstant(1);
	    m.migrad();
	    hv2syst1->Fill(v2_b.getVal()*corrb);
	    /*double shift2 = cgaus->GetRandom();
	    frac_b.setVal(bfrac->GetBinContent(binn));
	    frac_c.setVal(cfrac->GetBinContent(binn)+shift2);
	    frac_b.setConstant(1);
	    frac_c.setConstant(1);	
	    m.migrad();
	    hv2syst2->Fill(v2_b.getVal()*corrb);
	    double shift3 = egaus->GetRandom();	
	    frac_c.setVal(cfrac->GetBinContent(binn));
	    frac_e.setVal(efrac->GetBinContent(binn)+shift3);
	    frac_c.setConstant(1);
	    frac_e.setConstant(1);
	    m.migrad();
	    hv2syst3->Fill(v2_b.getVal()*corrb);
	    double shift4 = hgaus->GetRandom();
	    frac_e.setVal(efrac->GetBinContent(binn));
	    frac_h.setVal(hfrac->GetBinContent(binn)+shift4);
	    frac_e.setConstant(1);
	    frac_h.setConstant(1);
	    m.migrad();
	    hv2syst4->Fill(v2_b.getVal()*corrb);*/	    	    
	}
	TCanvas *c77 = new TCanvas("c77","");
	hv2syst1->Fit("gaus","R");
	//hv2syst2->Fit("gaus","R");
	//hv2syst3->Fit("gaus","R");
	//hv2syst4->Fit("gaus","R");
	double temp1 = hv2syst1->GetFunction("gaus")->GetParameter(2)*hv2syst1->GetFunction("gaus")->GetParameter(2);
	//double temp2 = hv2syst2->GetFunction("gaus")->GetParameter(2)*hv2syst2->GetFunction("gaus")->GetParameter(2);
	//double temp3 = hv2syst3->GetFunction("gaus")->GetParameter(2)*hv2syst3->GetFunction("gaus")->GetParameter(2);
	//double temp4 = hv2syst4->GetFunction("gaus")->GetParameter(2)*hv2syst4->GetFunction("gaus")->GetParameter(2);	
	sys = sqrt(temp1);
	hv2syst1->GetFunction("gaus")->SetLineColor(kRed);
	hv2syst1->GetXaxis()->SetTitle("v_{2}");
	hv2syst1->GetYaxis()->SetTitle("Arb. Units");
	hv2syst1->GetYaxis()->SetRangeUser(0,100);
	hv2syst1->Draw();
	//hv2syst2->Draw("same");
	//hv2syst3->Draw("same");
	//hv2syst4->Draw("same");
	char n_c[150];
	sprintf(n_c,"%s.pdf",dir2);
	if (save==1)c77->SaveAs(Form(n_c));
    }
 
    
    if (save==1){
        ofstream output1 (datfile,ios::app);
        if(output1.is_open()){
            output1 << pt << " " << central << " " <<error << " " << sys << " "  << "\n";
            output1.close();
        }else(cout << "Error Opening Output Dat File!");    
    }

    TCanvas *c1 = new TCanvas("c1","full fit");
    //c1->Divide(3,1);
    prettycanvasAll(c1,V2Frame,V2Frame1,V2Frame2,0,data->GetMaximum(),data_1->GetMaximum(),data_2->GetMaximum());    
 
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
	//      c1->SaveAs(Form(mass_png));
//        c1->SaveAs(Form(mass_eps));
    }
}


