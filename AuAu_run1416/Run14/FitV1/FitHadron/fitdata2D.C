#include "prettycanvasAll.C"
gSystem->Load("libRooFit.so");

using namespace RooFit;

void fitdata2D(TH1F *data,int save,char datfile[],char dir1[],int eta,double ptLow ,double ptHigh,int HT,double frac)
{
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);

/////Minuit Options
    
    bool hesse = true;
    bool minos = true;
   int const numEtaBins=16;
    double binning[numEtaBins+1]={-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1,0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8};   
    const double _start = 0;//-TMath::Pi()*4;  
    const double _end = TMath::Pi();
    RooRealVar *V1 = new RooRealVar("V1","V1",_start,_end);
    RooDataHist *dataHist = new RooDataHist("dataHist","dataHist",RooArgList(*V1),data);
    RooRealVar v1_b("v1_b","v1_b",0.05,-1,1.);
    RooRealVar frac1("frac1","frac1",frac);
    RooGenericPdf pdf_b ("pdf_b","(1+2*(@1*@2)*cos(@0+TMath::Pi()))",RooArgList(*V1,v1_b,frac1));
    RooProdPdf signal("signal","signal",pdf_b);
    RooRealVar signal_yield("signal_yield","signal_yield",1000,0,4e7);
    RooArgList shapeList;
    RooArgList yieldList;
    shapeList.add(signal);
    yieldList.add(signal_yield);
//All together now
    RooAddPdf completePDF("completePDF","completePDF",shapeList,yieldList);  
    RooAbsReal *nllData = completePDF.createNLL(*dataHist,Extended(kTRUE));
    RooAddition * nll = new RooAddition("nll","nll",RooArgSet(*nllData));  
    RooMinuit m (*nll);
    m.setVerbose(kFALSE);
    m.migrad();
    if(hesse)m.hesse();
    if(minos)m.minos();
    // Construct plotables // Don't change anything from hear on unless you want to change how a plot looks or what is output below
    RooPlot *V1Frame = V1->frame();
    dataHist->plotOn(V1Frame,Name("HistM"));
    completePDF.plotOn(V1Frame,Name("V1_Curve"));
    RooArgSet *freeparam = completePDF.getParameters(dataHist);
    int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
    TPaveText* txt = new TPaveText(0.35,0.2,0.55,0.4,"BRNDC");
    txt->SetTextSize(0.05);
    txt->SetTextColor(1);
    txt->SetBorderSize(0.1);
    txt->SetFillColor(0);
    txt->SetFillStyle(0);
  
    char chi2[50];
    char entr[50];
    char etabin[50];    
    char ptbin[50];    
    sprintf(chi2,"%3.4f",V1Frame->chiSquare("V1_Curve","HistM",numfreeparam));
    if(1){  
        sprintf(ptbin,"#it{p}_{T} #in [%1.1f,%1.1f] GeV",ptLow,ptHigh);
	if(eta>0)sprintf(etabin,"y #in [%1.1f,%1.1f] GeV",binning[eta-1],binning[eta]);
	else sprintf(etabin,"y #in [%1.1f,%1.1f] GeV",-0.8,0.8);
        sprintf(entr,"log_{10}(|DCA|/cm) #in [%1.1f,%1.1f] GeV",-2.6,-1);  
	txt->AddText(etabin);
        txt->AddText(ptbin);
	txt->AddText(entr);
	V1Frame->addObject(txt);     
    }    
//Objects for saving yields and so forth
    cout << "====================" << endl;   
    cout << "Chi2 of Mass Fit: " << chi2 << endl;
    cout << "====================" << endl;   
    cout << "V1's: " <<  endl;  
    cout << "HF: "   <<  v1_b.getVal() << " +/- " << v1_b.getError() << endl;  
    if (save==1){
        ofstream output1 (datfile,ios::app);
        if(output1.is_open()){
            output1 << eta << " " << v1_b.getVal() << " " <<v1_b.getError() << " "  << "\n";
            output1.close();
        }else(cout << "Error Opening Output Dat File!");    
    }

    TCanvas *c1 = new TCanvas("c1","full fit");
    //c1->Divide(3,1);
    prettycanvasAll(c1,V1Frame,0,data->GetMaximum());    
 
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


