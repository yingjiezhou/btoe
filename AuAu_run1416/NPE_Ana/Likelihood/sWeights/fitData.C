#include "prettycanvasAll.C"
gSystem->Load("libRooFit.so");

using namespace RooFit;

void fitdata1D(TH1F* hpovere,TH1F* hnsige,TH1F* hdeltabeta,TH1F* hzdist, TH1F* hphidist,int save,char outputfile[],int pt,double ptLow ,double ptHigh)
{
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
/////Minuit Options
    bool hesse = true;
    bool minos = false;
    char ptbin[50];
    sprintf(ptbin,"#it{p}_{T} #in [%1.1f,%1.1f] GeV",ptLow,ptHigh);
    TPaveText* txt = new TPaveText(0.6,0.67,0.9,0.85,"BRNDC");
    txt->AddText(ptbin);
    txt->SetTextSize(0.07);
    txt->SetTextColor(1);
    txt->SetBorderSize(0.1);
    txt->SetFillColor(0);
    txt->SetFillStyle(0);

    RooRealVar *povere = new RooRealVar("povere","povere",hpovere->GetXaxis()->GetXmin(),hpovere->GetXaxis()->GetXmax());
    RooRealVar *nsige = new RooRealVar("nsige","nsige",hnsige->GetXaxis()->GetXmin(),hnsige->GetXaxis()->GetXmax());
    RooRealVar *deltabeta = new RooRealVar("deltabeta","deltabeta",hdeltabeta->GetXaxis()->GetXmin(),hdeltabeta->GetXaxis()->GetXmax());
    RooRealVar *zdist = new RooRealVar("zdist","",hzdist->GetXaxis()->GetXmin(),hzdist->GetXaxis()->GetXmax());
    RooRealVar *phidist = new RooRealVar("phidist","phidist",hphidist->GetXaxis()->GetXmin(),hphidist->GetXaxis()->GetXmax());

    RooDataHist *dataHist_povere = new RooDataHist("dataHist_povere","dataHist_povere",RooArgList(*povere),hpovere);
    RooDataHist *dataHist_nsige = new RooDataHist("dataHist_nsige","dataHist_nsige",RooArgList(*nsige),hnsige);
    RooDataHist *dataHist_deltabeta = new RooDataHist("dataHist_deltabeta","dataHist_deltabeta",RooArgList(*deltabeta),hdeltabeta); 
    RooDataHist *dataHist_zdist = new RooDataHist("dataHist_zdist","dataHist_zdist",RooArgList(*zdist),hzdist); 
    RooDataHist *dataHist_phidist = new RooDataHist("dataHist_phidist","dataHist_phidist",RooArgList(*phidist),hphidist); 
//Signals var1  ////////////////
    RooRealVar mean1_povere("mean1_povere","mean1_povere",0.3,0,2);
    RooRealVar mean2_povere("mean2_povere","mean2_povere",0.3,0,2);
    RooRealVar sigma1_povere("sigma1_povere","sigma1_povere",1,0.1,1.2);
    RooRealVar sigma2_povere("sigma2_povere","sigma2_povere",1,0,1.2); 
    RooRealVar alpha1("alpha1","alpha1",-1,-10,10); 
    RooRealVar n1("n1","n1",1); 
    RooRealVar frac1("frac1","frac1",0.5,0,1);  
    RooGaussian g1_g("g1_g","g1_g",*povere,mean2_povere,sigma2_povere);
    RooCBShape g1_cb("g1_cb","g1_cb",*povere,mean1_povere,sigma1_povere,alpha1,n1);
    RooAddPdf g1_povere("g1_povere","g1_povere",g1_cb,g1_g,frac1);
    RooProdPdf povere_signal("povere_signal","povere_signal",g1_povere); 
    RooRealVar povere_signal_yield("povere_signal_yield","povere_signal_yield",100,0,1000000000);
    RooArgList shapeList_povere;
    RooArgList yieldList_povere;
    shapeList_povere.add(povere_signal); 
    yieldList_povere.add(povere_signal_yield);
    RooAddPdf completePDF_povere("completePDF_povere","completePDF_povere",shapeList_povere,yieldList_povere);
    RooAbsReal *nllData_povere  = completePDF_povere.createNLL(*dataHist_povere,Extended(kTRUE));
    RooAddition * nll_povere = new RooAddition("nll_povere","nll_povere",RooArgSet(*nllData_povere));  
    RooMinuit m_povere (*nll_povere);
    m_povere.setVerbose(kFALSE);
    m_povere.migrad();
    RooPlot *Frame_povere = povere->frame();
    dataHist_povere->plotOn(Frame_povere,Name("Hist_povere"));
    completePDF_povere.plotOn(Frame_povere,Name("Curve_povere"));
    RooHist* pullHisto_povere = Frame_povere->pullHist("Hist_povere","Curve_povere");
    RooPlot* pullPlot_povere= povere->frame();
    pullHisto_povere->SetFillColor(1);
    pullHisto_povere->SetLineColor(0);
    pullPlot_povere->addPlotable(pullHisto_povere,"B");
    RooArgSet *freeparam = completePDF_povere.getParameters(dataHist_povere);
    int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
    Frame_povere->addObject(txt);       
    TCanvas *c_povere = new TCanvas("c_povere","povere");
    prettycanvasAll(c_povere,Frame_povere,pullPlot_povere,0,"#it{p}/E");    
//Signals var2  ////////////////
    RooRealVar mean1_nsige("mean1_nsige","mean1_nsige",0.,-2,2);
    RooRealVar sigma1_nsige("sigma1_nsige","sigma1_nsige",1,0.1,2.2);
    RooRealVar sigma2_nsige("sigma2_nsige","sigma2_nsige",1,0,1.2);
    RooRealVar frac_nsige("frac_nsige","frac_nsige",0.9,0,1);
    RooGaussian g1_1nsige("g1_1nsige","g1_1nsige",*nsige,mean1_nsige,sigma1_nsige);
    RooGaussian g1_2nsige("g1_2nsige","g1_2nsige",*nsige,mean1_nsige,sigma2_nsige);
    RooAddPdf g1_nsige("g1_nsige","g1_nsige",g1_1nsige,g1_2nsige,frac_nsige);
    RooProdPdf nsige_signal("nsige_signal","nsige_signal",g1_nsige); 
    RooRealVar nsige_signal_yield("nsige_signal_yield","nsige_signal_yield",100,0,1000000000);
    RooArgList shapeList_nsige;
    RooArgList yieldList_nsige;
    shapeList_nsige.add(nsige_signal); 
    yieldList_nsige.add(nsige_signal_yield);
    RooAddPdf completePDF_nsige("completePDF_nsige","completePDF_nsige",shapeList_nsige,yieldList_nsige);
    RooAbsReal *nllData_nsige  = completePDF_nsige.createNLL(*dataHist_nsige,Extended(kTRUE));
    RooAddition * nll_nsige = new RooAddition("nll_nsige","nll_nsige",RooArgSet(*nllData_nsige));  
    RooMinuit m_nsige (*nll_nsige);
    m_nsige.setVerbose(kFALSE);
    m_nsige.migrad();
    RooPlot *Frame_nsige = nsige->frame();
    dataHist_nsige->plotOn(Frame_nsige,Name("Hist_nsige"));
    completePDF_nsige.plotOn(Frame_nsige,Name("Curve_nsige"));
    RooHist* pullHisto_nsige = Frame_nsige->pullHist("Hist_nsige","Curve_nsige");
    RooPlot* pullPlot_nsige= nsige->frame();
    pullHisto_nsige->SetFillColor(1);
    pullHisto_nsige->SetLineColor(0);
    pullPlot_nsige->addPlotable(pullHisto_nsige,"B");
    RooArgSet *freeparam = completePDF_nsige.getParameters(dataHist_nsige);
    int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
    Frame_nsige->addObject(txt);       
    TCanvas *c_nsige = new TCanvas("c_nsige","nsige");
    prettycanvasAll(c_nsige,Frame_nsige,pullPlot_nsige,0,"n#sigma_{e}");     
//Signals var3  ////////////////
    RooRealVar mean1_deltabeta("mean1_deltabeta","mean1_deltabeta",0.,-.02,0.02);
    RooRealVar mean2_deltabeta("mean2_deltabeta","mean2_deltabeta",0.,-.02,0.02);
    RooRealVar sigma1_deltabeta("sigma1_deltabeta","sigma1_deltabeta",0.001,0.0001,1);
    RooRealVar sigma2_deltabeta("sigma2_deltabeta","sigma2_deltabeta",0.001,0.0001,0.1); 
    RooGaussian g1_1_deltabeta("g1_1_deltabeta","g1_1_deltabeta",*deltabeta,mean1_deltabeta,sigma1_deltabeta);
    RooGaussian g1_2_deltabeta("g1_2_deltabeta","g1_2_deltabeta",*deltabeta,mean2_deltabeta,sigma2_deltabeta);
    RooRealVar frac1_deltabeta("frac1_deltabeta","frac1_deltabeta",0.5,0,1);  
    RooAddPdf g1_deltabeta("g1_deltabeta","g1_deltabeta",g1_1_deltabeta,g1_2_deltabeta,frac1_deltabeta);
    RooProdPdf deltabeta_signal("deltabeta_signal","deltabeta_signal",g1_deltabeta); 
    RooRealVar deltabeta_signal_yield("deltabeta_signal_yield","deltabeta_signal_yield",100,0,1000000000);
    RooArgList shapeList_deltabeta;
    RooArgList yieldList_deltabeta;
    shapeList_deltabeta.add(deltabeta_signal); 
    yieldList_deltabeta.add(deltabeta_signal_yield);
    RooAddPdf completePDF_deltabeta("completePDF_deltabeta","completePDF_deltabeta",shapeList_deltabeta,yieldList_deltabeta);
    RooAbsReal *nllData_deltabeta  = completePDF_deltabeta.createNLL(*dataHist_deltabeta,Extended(kTRUE));
    RooAddition * nll_deltabeta = new RooAddition("nll_deltabeta","nll_deltabeta",RooArgSet(*nllData_deltabeta));  
    RooMinuit m_deltabeta (*nll_deltabeta);
    m_deltabeta.setVerbose(kFALSE);
    m_deltabeta.migrad();
    RooPlot *Frame_deltabeta = deltabeta->frame();
    dataHist_deltabeta->plotOn(Frame_deltabeta,Name("Hist_deltabeta"));
    completePDF_deltabeta.plotOn(Frame_deltabeta,Name("Curve_deltabeta"));
    RooHist* pullHisto_deltabeta = Frame_deltabeta->pullHist("Hist_deltabeta","Curve_deltabeta");
    RooPlot* pullPlot_deltabeta= deltabeta->frame();
    pullHisto_deltabeta->SetFillColor(1);
    pullHisto_deltabeta->SetLineColor(0);
    pullPlot_deltabeta->addPlotable(pullHisto_deltabeta,"B");
    RooArgSet *freeparam = completePDF_deltabeta.getParameters(dataHist_deltabeta);
    int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
    Frame_deltabeta->addObject(txt);       
    TCanvas *c_deltabeta = new TCanvas("c_deltabeta","deltabeta");
    prettycanvasAll(c_deltabeta,Frame_deltabeta,pullPlot_deltabeta,0,"(1/#beta-1/#beta_{exp})/(1/#beta)");  

//Signals var4  ////////////////
    RooRealVar mean1_zdist("mean1_zdist","mean1_zdist",0.,-10,10);
    RooRealVar mean2_zdist("mean2_zdist","mean2_zdist",0.,-10,10);
    RooRealVar mean3_zdist("mean3_zdist","mean3_zdist",0.,-10,10);
    RooRealVar sigma1_zdist("sigma1_zdist","sigma1_zdist",5,0,15);
    RooRealVar sigma2_zdist("sigma2_zdist","sigma2_zdist",5,0,15);
    RooRealVar sigma3_zdist("sigma3_zdist","sigma3_zdist",5,0,15);
    RooGaussian g1_1_zdist("g1_1_zdist","g1_1_zdist",*zdist,mean1_zdist,sigma1_zdist);
    RooGaussian g1_2_zdist("g1_2_zdist","g1_2_zdist",*zdist,mean1_zdist,sigma2_zdist);
    RooGaussian g1_3_zdist("g1_3_zdist","g1_3_zdist",*zdist,mean1_zdist,sigma3_zdist);
    RooRealVar frac1_zdist("frac1_zdist","frac1_zdist",0.9,0,1);  
    RooRealVar frac2_zdist("frac2_zdist","frac2_zdist",0.9,0,1);  
    if(pt==0){
	RooAddPdf g2_1_zdist("g2_1_zdist","g2_1_zdist",g1_1_zdist,g1_2_zdist,frac1_zdist);
	RooAddPdf g1_zdist("g1_zdist","g1_zdist",g2_1_zdist,g1_3_zdist,frac2_zdist);
    }
    if(pt!=0)RooAddPdf g1_zdist("g1_zdist","g1_zdist",g1_1_zdist,g1_2_zdist,frac1_zdist);
    //RooAddPdf g2_1_zdist("g2_1_zdist","g2_1_zdist",g1_1_zdist,g1_2_zdist,frac1_zdist);
    //RooAddPdf g1_zdist("g1_zdist","g1_zdist",g2_1_zdist,g1_2_zdist,frac2_zdist);
    RooProdPdf zdist_signal("zdist_signal","zdist_signal",g1_zdist); 
    RooRealVar zdist_signal_yield("zdist_signal_yield","zdist_signal_yield",100,0,1000000000);
    RooArgList shapeList_zdist;
    RooArgList yieldList_zdist;
    shapeList_zdist.add(zdist_signal); 
    yieldList_zdist.add(zdist_signal_yield);
    RooAddPdf completePDF_zdist("completePDF_zdist","completePDF_zdist",shapeList_zdist,yieldList_zdist);
    RooAbsReal *nllData_zdist  = completePDF_zdist.createNLL(*dataHist_zdist,Extended(kTRUE));
    RooAddition * nll_zdist = new RooAddition("nll_zdist","nll_zdist",RooArgSet(*nllData_zdist));  
    RooMinuit m_zdist (*nll_zdist);
    m_zdist.setVerbose(kFALSE);
    m_zdist.migrad();
    RooPlot *Frame_zdist = zdist->frame();
    dataHist_zdist->plotOn(Frame_zdist,Name("Hist_zdist"));
    completePDF_zdist.plotOn(Frame_zdist,Name("Curve_zdist"));
    RooHist* pullHisto_zdist = Frame_zdist->pullHist("Hist_zdist","Curve_zdist");
    RooPlot* pullPlot_zdist= zdist->frame();
    pullHisto_zdist->SetFillColor(1);
    pullHisto_zdist->SetLineColor(0);
    pullPlot_zdist->addPlotable(pullHisto_zdist,"B");
    RooArgSet *freeparam = completePDF_zdist.getParameters(dataHist_zdist);
    int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
    Frame_zdist->addObject(txt);       
    TCanvas *c_zdist = new TCanvas("c_zdist","zdist");
    prettycanvasAll(c_zdist,Frame_zdist,pullPlot_zdist,0,"#Delta#it{z}");  
//Signals var5  ////////////////
    RooRealVar mean1_phidist("mean1_phidist","mean1_phidist",0.,-0.1,0.1);
    RooRealVar mean2_phidist("mean2_phidist","mean2_phidist",0.,-0.1,0.1);
    RooRealVar mean3_phidist("mean3_phidist","mean3_phidist",0.,-0.1,0.1);
    RooRealVar sigma1_phidist("sigma1_phidist","sigma1_phidist",0.01,0.0001,0.1);
    RooRealVar sigma2_phidist("sigma2_phidist","sigma2_phidist",0.01,0.0001,0.1);
    RooRealVar sigma3_phidist("sigma3_phidist","sigma3_phidist",0.01,0,0.1); 
    RooGaussian g1_1_phidist("g1_1_phidist","g1_1_phidist",*phidist,mean1_phidist,sigma1_phidist);
    RooGaussian g1_2_phidist("g1_2_phidist","g1_2_phidist",*phidist,mean1_phidist,sigma2_phidist);
    RooGaussian g1_3_phidist("g1_3_phidist","g1_3_phidist",*phidist,mean1_phidist,sigma3_phidist);
    RooRealVar frac1_phidist("frac1_phidist","frac1_phidist",0.9,0,1);  
    RooRealVar frac2_phidist("frac2_phidist","frac2_phidist",0.5,0,1);  
    if(pt==0||pt==1){
	RooAddPdf g2_1_phidist("g2_1_phidist","g2_1_phidist",g1_1_phidist,g1_2_phidist,frac1_phidist);
	RooAddPdf g1_phidist("g1_phidist","g1_phidist",g2_1_phidist,g1_3_phidist,frac2_phidist);
    }
    if(pt==2)RooAddPdf g1_phidist("g1_phidist","g1_phidist",g1_1_phidist,g1_2_phidist,frac1_phidist);
    RooProdPdf phidist_signal("phidist_signal","phidist_signal",g1_phidist); 
    RooRealVar phidist_signal_yield("phidist_signal_yield","phidist_signal_yield",100,0,1000000000);
    RooArgList shapeList_phidist;
    RooArgList yieldList_phidist;
    shapeList_phidist.add(phidist_signal); 
    yieldList_phidist.add(phidist_signal_yield);
    RooAddPdf completePDF_phidist("completePDF_phidist","completePDF_phidist",shapeList_phidist,yieldList_phidist);
    RooAbsReal *nllData_phidist  = completePDF_phidist.createNLL(*dataHist_phidist,Extended(kTRUE));
    RooAddition * nll_phidist = new RooAddition("nll_phidist","nll_phidist",RooArgSet(*nllData_phidist));  
    RooMinuit m_phidist (*nll_phidist);
    m_phidist.setVerbose(kFALSE);
    m_phidist.migrad();
    RooPlot *Frame_phidist = phidist->frame();
    dataHist_phidist->plotOn(Frame_phidist,Name("Hist_phidist"));
    completePDF_phidist.plotOn(Frame_phidist,Name("Curve_phidist"));
    RooHist* pullHisto_phidist = Frame_phidist->pullHist("Hist_phidist","Curve_phidist");
    RooPlot* pullPlot_phidist= phidist->frame();
    pullHisto_phidist->SetFillColor(1);
    pullHisto_phidist->SetLineColor(0);
    pullPlot_phidist->addPlotable(pullHisto_phidist,"B");
    RooArgSet *freeparam = completePDF_phidist.getParameters(dataHist_phidist);
    int numfreeparam = (freeparam->selectByAttrib("Constant",kFALSE))->getSize();
    Frame_phidist->addObject(txt);       
    TCanvas *c_phidist = new TCanvas("c_phidist","phidist");
    prettycanvasAll(c_phidist,Frame_phidist,pullPlot_phidist,0,"#Delta#phi");  










///Done Fitting 
    RooDataSet *h1povere = (RooDataSet*)g1_povere.generateBinned(*povere,10000000);
    TH1F* weight_povere = (TH1F*)h1povere->createHistogram("weight_povere",*povere);
    weight_povere->Scale(1/weight_povere->Integral());///weight_povere->GetBinWidth(5));//GetMaximum());
    weight_povere->GetYaxis()->SetTitle("Likelihood");
    weight_povere->GetXaxis()->SetTitle("#it{p}/E");
    RooDataSet *h1nsige = (RooDataSet*)g1_nsige.generateBinned(*nsige,1000000);
    TH1F* weight_nsige = (TH1F*)h1nsige->createHistogram("weight_nsige",*nsige);
    weight_nsige->Scale(1/weight_nsige->Integral());///weight_nsige->GetBinWidth(5));//GetMaximum());
    weight_nsige->GetYaxis()->SetTitle("Likelihood");
    weight_nsige->GetXaxis()->SetTitle("n#sigma_{e}");
    RooDataSet *h1deltabeta = (RooDataSet*)g1_deltabeta.generateBinned(*deltabeta,10000000);
    TH1F* weight_deltabeta = (TH1F*)h1deltabeta->createHistogram("weight_deltabeta",*deltabeta);
    weight_deltabeta->Scale(1/weight_deltabeta->Integral());///weight_deltabeta->GetBinWidth(5));//GetMaximum());
    weight_deltabeta->GetYaxis()->SetTitle("Likelihood");
    weight_deltabeta->GetXaxis()->SetTitle("(1/#beta-1/#beta_{exp})/(1/#beta)");
    RooDataSet *h1zdist = (RooDataSet*)g1_zdist.generateBinned(*zdist,10000000);
    TH1F* weight_zdist = (TH1F*)h1zdist->createHistogram("weight_zdist",*zdist);
    weight_zdist->Scale(1/weight_zdist->Integral());///weight_zdist->GetBinWidth(5));//GetMaximum());
    weight_zdist->GetYaxis()->SetTitle("Likelihood");
    weight_zdist->GetXaxis()->SetTitle("#Delta#it{z}");
    RooDataSet *h1phidist = (RooDataSet*)g1_phidist.generateBinned(*phidist,10000000);
    TH1F* weight_phidist = (TH1F*)h1phidist->createHistogram("weight_phidist",*phidist);
    weight_phidist->Scale(1/weight_phidist->Integral());///weight_phidist->GetBinWidth(5));//GetMaximum());
    weight_phidist->GetYaxis()->SetTitle("Likelihood");
    weight_phidist->GetXaxis()->SetTitle("#Delta#phi");
    TCanvas *call = new TCanvas("call","call",1200,800);
    call->Divide(3,2);
    call->cd(1);
    weight_povere->Draw("hist");
    call->cd(2);
    weight_nsige->Draw("hist");
    call->cd(3);
    weight_deltabeta->Draw("hist");
    call->cd(4);
    weight_zdist->Draw("hist");
    call->cd(5);
    weight_phidist->Draw("hist");

    if(save && pt==0){
	c_povere->SaveAs("plots/Electron_POverE_Fit.pdf");
	c_nsige->SaveAs("plots/Electron_NSigmae_Fit.pdf");
	c_deltabeta->SaveAs("plots/Electron_DeltaBeta_Fit.pdf");
	c_zdist->SaveAs("plots/Electron_ZDist_Fit.pdf");
	c_phidist->SaveAs("plots/Electron_PhiDist_Fit.pdf");
	TFile f(outputfile,"RECREATE");
	weight_povere->Write("electron_weight_povere");
	weight_nsige->Write("electron_weight_nsige");
	weight_deltabeta->Write("electron_weight_deltabeta");
	weight_zdist->Write("electron_weight_zdist");
	weight_phidist->Write("electron_weight_phidist");
    }
    if(save && pt==1){
	c_povere->SaveAs("plots/Electron_POverE_Fit_lowPt.pdf");
	c_nsige->SaveAs("plots/Electron_NSigmae_Fit_lowPt.pdf");
	c_deltabeta->SaveAs("plots/Electron_DeltaBeta_Fit_lowPt.pdf");
	c_zdist->SaveAs("plots/Electron_ZDist_Fit_lowPt.pdf");
	c_phidist->SaveAs("plots/Electron_PhiDist_Fit_lowPt.pdf");
	TFile f(outputfile,"RECREATE");
	weight_povere->Write("electron_weight_povere");
	weight_nsige->Write("electron_weight_nsige");
	weight_deltabeta->Write("electron_weight_deltabeta");
	weight_zdist->Write("electron_weight_zdist");
	weight_phidist->Write("electron_weight_phidist");
    }
    if(save && pt==2){
	c_povere->SaveAs("plots/Electron_POverE_Fit.pdf");
	c_nsige->SaveAs("plots/Electron_NSigmae_Fit.pdf");
	c_deltabeta->SaveAs("plots/Electron_DeltaBeta_Fit.pdf");
	c_zdist->SaveAs("plots/Electron_ZDist_Fit.pdf");
	c_phidist->SaveAs("plots/Electron_PhiDist_Fit.pdf");
	TFile f(outputfile,"RECREATE");
	weight_povere->Write("electron_weight_povere");
	weight_nsige->Write("electron_weight_nsige");
	weight_deltabeta->Write("electron_weight_deltabeta");
	weight_zdist->Write("electron_weight_zdist");
	weight_phidist->Write("electron_weight_phidist");
    }

}


