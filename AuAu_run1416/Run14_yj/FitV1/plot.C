void plot(){
   gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3);
//
    int const numEtaBins=4;
    double binning2[numEtaBins+1]={-0.8+0.05,-0.4+0.05,0+0.05,0.4+0.05,0.8+0.05};  
    double binning1[numEtaBins+1]={-0.8-0.02,-0.4-0.02,0-0.02,0.4-0.02,0.8-0.02}; 
    double binning[numEtaBins+1]={-0.8,-0.4,0,0.4,0.8};  
    TH1F *h_p = new TH1F("h_p","",numEtaBins,binning1);
    TH1F *h = new TH1F("h","",numEtaBins,binning);
    TH1F *h_m = new TH1F("h_m","",numEtaBins,binning2);
    TH1F *h_diff = new TH1F("h_diff","",numEtaBins,binning);
    double x1[4]={-0.6+0.02,-0.2+0.02,0.2+0.02,0.6+0.02};
    double y1[4] = {0.069,0.018,-0.03,-0.025};
    double x1e[4] = {0,0,0,0};
    double y1e[4] = {0.016*sqrt(2),0.013*sqrt(2),0.0125*sqrt(2),0.014*sqrt(2)};
    TGraphErrors *g1 = new TGraphErrors(4,x1,y1,x1e,y1e);
    g1->SetMarkerColor(kMagenta);
    g1->SetLineColor(kMagenta);
    g1->SetMarkerStyle(26);
    TF1 *funcd0 = new TF1("funcd0","[0]*x",-0.8,0.8);
    funcd0->SetParameter(0,-0.08);
    funcd0->SetLineStyle(5);
    funcd0->SetLineColor(kMagenta);
    g1->Fit("funcd0");
    funcd0->SetParameter(0,-0.08);
    TF1 *line = new TF1("line","0",-10,10);
    line->SetLineStyle(7);
    getData(h,"./3/yields.dat");
    getData(h_p,"./4/yields.dat");
    getData(h_m,"./5/yields.dat");
    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
    h_p->SetLineColor(kRed);
    h_p->SetMarkerColor(kRed);  
    h_p->SetMarkerStyle(26); 
    h_m->SetLineColor(kBlue);
    h_m->SetMarkerColor(kBlue);  
    h_m->SetMarkerStyle(25); 
    leg->AddEntry(h,"#it{e}^{+}+#it{e^{-}}","PLE");
    //leg->AddEntry(h_p,"#it{e^{+}} (#it{c})","PLE");
    //leg->AddEntry(h,"#it{e}^{#pm} #it{p}_{T}>1.2 GeV","PLE");
    ///leg->AddEntry(h_p,"#it{e}^{#pm} #it{p}_{T}>2.0 GeV","PLE");  
    //leg->AddEntry(h_m,"#it{e^{-}} (#bar{#it{c}})","PEL");
    leg->AddEntry(g1,"D^{0} v_{1}", "PLE");
    TF1 *func = new TF1("func","[0]*x",-0.8,0.8);
    TF1 *func1 = new TF1("func1","[0]*x",-0.8,0.8);
    TF1 *func2 = new TF1("func2","[0]*x",-0.8,0.8);    

    TF1 *fnull = new TF1("fnull","[0]",-0.8,0.8);
    fnull->SetParameter(0,0);
    fnull->SetParLimits(0,0,0);
    TLatex lat;
    TCanvas *c1 = new TCanvas("c1","c1");
    h->GetXaxis()->SetTitle("Rapidity");
    h->GetYaxis()->SetTitle("v_{1}");
    h->GetXaxis()->SetRangeUser(-0.8,0.8);
    h->GetYaxis()->SetRangeUser(-0.15,0.15);
    func->SetLineStyle(5);
    func1->SetLineStyle(2);
    func1->SetLineColor(kRed);
    func2->SetLineStyle(8);
    func2->SetLineColor(kBlue);
    h->Fit("func");
    h_p->Fit("func1");
    h_m->Fit("func2");
    funcd0->Draw("lsame");
    h->Draw("E1X0 ");
    h_p->Draw("same E1X0 ");
    h_m->Draw("same E1X0 ");
    lat.DrawLatex(-0.6,-0.1,"#it{p}_{T}^{e} > 1.2 GeV");
    lat.DrawLatex(-0.6,-0.07,"10-80%");
    TLatex lat;
    char label[100];
    char label1[100];
    char label2[100];
    sprintf(label,"Slope = %1.3f#pm%1.3f",func->GetParameter(0),func->GetParError(0));
    sprintf(label1,"#color[2]{Slope = %1.3f#pm%1.3f}",func1->GetParameter(0),func1->GetParError(0));
    sprintf(label2,"#color[4]{Slope = %1.3f#pm%1.3f}",func2->GetParameter(0),func2->GetParError(0));
    lat.SetTextSize(0.05);    
    lat.DrawLatex(-0.7,0.13,label);
    //lat.DrawLatex(-0.7,0.115,label1);
    //lat.DrawLatex(-0.7,0.10,label2);
    leg->Draw("same");
    g1->Draw("same PE");
    line->Draw("same");
    /*for(int i = 1;i<numEtaBins+1;i++){
	double temp1 = h_p->GetBinContent(i);
	double temp11 = h_p->GetBinError(i);	
	double temp2 = h_m->GetBinContent(i);
	double temp22 = h_m->GetBinError(i);
	h_diff->SetBinContent(i,temp1-temp2);
	h_diff->SetBinError(i,sqrt(temp11*temp11+temp22*temp22));	
    }*/
    for(int i = 1;i<numEtaBins+1;i++){
        double temp1 = h->GetBinContent(i);
        double temp11 = h->GetBinError(i);
        double temp2 = h_p->GetBinContent(i);
        double temp22 = h_p->GetBinError(i);
	
        h_diff->SetBinContent(i,temp1-temp2);
        h_diff->SetBinError(i,sqrt(fabs(temp11*temp11-temp22*temp22)));
    }
    TCanvas *c2 = new TCanvas("c2","diff");
    TF1 *funcd = new TF1("funcd","[0]*x",-0.8,0.8);
    funcd->SetLineStyle(5);
//    h_diff->Fit(funcd);
    h_diff->GetXaxis()->SetTitle("Rapidity");
//    h_diff->GetYaxis()->SetTitle("v_{1}^{e+}-v_{1}^{e-}");
    h_diff->GetYaxis()->SetTitle("v_{1}^{>1.2 GeV}-v_{1}^{>2 GeV}");
    h_diff->GetXaxis()->SetRangeUser(-0.8,0.8);
    h_diff->GetYaxis()->SetRangeUser(-0.1,0.1);
    h_diff->Draw("PE");
    line->Draw("same");
    sprintf(label,"Slope = %1.3f#pm%1.3f",funcd->GetParameter(0),funcd->GetParError(0));
    //  lat.DrawLatex(-0.7,0.11,label);
//    lat.DrawLatex(-0.6,-0.1,"#it{p}_{T}^{e} > 1.2 GeV");
    double chi2=0;
    for(int i = 1;i<5;i++){
	cout << h->GetBinContent(i) << " " << h->GetBinError(i) << " " << chi2 << endl;
	chi2 += (h->GetBinContent(i)*h->GetBinContent(i))/(h->GetBinError(i)*h->GetBinError(i));
    }
    cout << "chi2 " << chi2 << endl;
//    h->Fit("fnull");
}
void getData(TH1F *hb,char file[]){
    ifstream data(file);
    if(data.is_open()){
	while(!data.eof()){	
	    double b=0;
	    double b_e=0;
	    double pT=0;
	    data >> pT >> b >> b_e;	
	    hb->SetBinContent(pT,b);
	    hb->SetBinError(pT,b_e);	  
	}	
    } else {
	cout <<"Nope \n";
    }
    data.close();
}
void getData1(TH1F *hb,char file[]){
    ifstream data(file);
    if(data.is_open()){
	while(!data.eof()){	
	    double b=0;
	    double b_e=0;
	    double pT=0;
	    data >> pT >> b >> b_e;	
	    hb->SetBinContent(5-pT,b);
	    hb->SetBinError(5-pT,b_e);	  
	}	
    } else {
	cout <<"Nope \n";
    }
    data.close();
}
