void getData(TGraph *g,char file[]);
void getAve(TH1F* h_ave,TH1F* h, TH1F*h_ht);
void getData(TH1F* h,char file[]);
void CalcRCP()
{//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    double binning1[numPtBins+1]={0.6+0.05,1,1.2,1.5,2.0+0.02,2.5+0.02,3.5+0.02,4.5+0.02,5.5+0.02,8.5+0.02};
    double binning2[numPtBins+1]={0.6+0.075,1,1.2,1.5,2.0+0.05,2.5+0.05,3.5+0.05,4.5+0.05,5.5+0.05,8.5+0.05};
    double binning4[numPtBins+1]={0.6-0.15,1,1.2,1.5,2.0-0.15,2.5-0.15,3.5-0.15,4.5-0.15,5.5-0.15,8.5-0.15};
    double binning3[numPtBins+1]={0.6-0.075,1,1.2,1.5,2.0-0.075,2.5-0.075,3.5-0.075,4.5-0.075,5.5-0.075,8.5-0.075};
    TH1F *hrat = new TH1F("hrat","hrat",numPtBins,binning);  
    TH1F *hrat1 = new TH1F("hrat1","hrat1",numPtBins,binning1); 
    TH1F *hrat2 = new TH1F("hrat2","hrat2",numPtBins,binning); 
    TGraphErrors *sys = new TGraphErrors();
    TGraphErrors *sys1 =new TGraphErrors();
    TGraphErrors *sys2 =new TGraphErrors();

    TH1F *fb_0_201 = new TH1F("fb_0_201","fb_0_201",numPtBins,binning4);
    TH1F *fb_20_401 = new TH1F("fb_20_401","fb_20_401",numPtBins,binning3); 
    TH1F *fb_40_801 = new TH1F("fb_40_801","fb_40_801",numPtBins,binning2);
    fb_40_801->SetMarkerSize(1.3);
    TFile *f1 = new TFile("../DCA_Fit/root/FracB.root");
    auto fb1= (TH1F*)f1->Get("fb");
    auto fb_sys= (TH1F*)f1->Get("fb_sys");
    auto FONLL= (TH1F*)f1->Get("FONLL");
    auto pp= (TGraphAsymmErrors*)f1->Get("pp");
    auto pp_sys= (TGraphAsymmErrors*)f1->Get("pp_sys");
    fb_sys->SetFillColor(kGray);
    
    TFile *f2 = new TFile("../DCA_Fit_0_20/root/FracB.root");
    auto fb1_sys= (TH1F*)f2->Get("fb_sys");fb1_sys->SetName("fb1_sys");
    TFile *f3 = new TFile("../DCA_Fit_20_40/root/FracB.root");
    auto fb2_sys= (TH1F*)f3->Get("fb_sys");fb2_sys->SetName("fb2_sys");
    TFile *f4 = new TFile("../DCA_Fit_40_80/root/FracB.root");
    auto fb3_sys= (TH1F*)f4->Get("fb_sys");fb3_sys->SetName("fb3_sys");
    

    TGraphErrors *fb_sys1 = new TGraphErrors();
    TGraphErrors *fb_sys2 =new TGraphErrors();
    TGraphErrors *fb_sys3 =new TGraphErrors();


    TH2F *hsys1 = new TH2F("hsys1","",9,0,9,8,0,8);
    TH2F *hsys2 = new TH2F("hsys2","",9,0,9,8,0,8);
    TH2F *hsys3 = new TH2F("hsys3","",9,0,9,8,0,8);
    for(int i = 1;i<9;i++){
	TH1F *have1 = new TH1F("have1","",numPtBins,binning);
	TH1F *have2 = new TH1F("have2","",numPtBins,binning);
	TH1F *have3 = new TH1F("have3","",numPtBins,binning);
	TH1F *ht1 = new TH1F("ht1","",numPtBins,binning);
	TH1F *ht1_ht = new TH1F("ht1_ht","",numPtBins,binning);
	TH1F *ht2 = new TH1F("ht2","",numPtBins,binning);
	TH1F *ht2_ht = new TH1F("ht2_ht","",numPtBins,binning);
	TH1F *ht3 = new TH1F("ht3","",numPtBins,binning);
	TH1F *ht3_ht = new TH1F("ht3_ht","",numPtBins,binning);
	char data[100];
	
	sprintf(data,"../DCA_Fit_0_20/%i/yields.dat",i);
	getData(ht1,data);
	sprintf(data,"../DCA_Fit_0_20/%i/yields.dat",i+1);
	getData(ht1_ht,data);
	if(i==1)getAve(fb_0_201,ht1,ht1_ht);
	getAve(have1,ht1,ht1_ht);

	sprintf(data,"../DCA_Fit_20_40/%i/yields.dat",i);
        getData(ht2,data);
        sprintf(data,"../DCA_Fit_20_40/%i/yields.dat",i+1);
        getData(ht2_ht,data);
        if(i==1)getAve(fb_20_401,ht2,ht2_ht);
	getAve(have2,ht2,ht2_ht);

	sprintf(data,"../DCA_Fit_40_80/%i/yields.dat",i);
        getData(ht3,data);
        sprintf(data,"../DCA_Fit_40_80/%i/yields.dat",i+1);
        getData(ht3_ht,data);
        if(i==1)getAve(fb_40_801,ht3,ht3_ht);
        getAve(have3,ht3,ht3_ht);

	for (int j = 5;j<10;j++){
	    double temp1 = have1->GetBinContent(j);
	    double temp2 = have2->GetBinContent(j);
	    double temp3 = have3->GetBinContent(j);
	    double temp11 = have1->GetBinError(j);
            double temp22 = have2->GetBinError(j);
            double temp33 = have3->GetBinError(j);
	    if(i==1){//set central values
		if(temp1>0 && temp3>0 && j<8){
		    hrat->SetBinContent(j,(1/temp3-1)/(1/temp1-1));
		    hrat->SetBinError(j, (1/temp3-1)/(1/temp1-1)*sqrt(temp11*temp11/temp1/temp1/(temp1-1)/(temp1-1)+temp33*temp33/temp3/temp3/(temp3-1)/(temp3-1)));

		}
		if(temp2>0 && temp3>0 && j<8){
		    hrat1->SetBinContent(j,(1/temp3-1)/(1/temp2-1));
		    hrat1->SetBinError(j,(1/temp3-1)/(1/temp2-1)*sqrt(temp22*temp22/temp2/temp2/(temp2-1)/(temp2-1)+temp33*temp33/temp3/temp3/(temp3-1)/(temp3-1)));
		}
		if(temp1>0 && temp1>0){
		    hrat2->SetBinContent(j,(1/temp2-1)/(1/temp1-1));
		    hrat2->SetBinError(j,(1/temp2-1)/(1/temp1-1)*sqrt(temp22*temp22/temp2/temp2/(temp2-1)/(temp2-1)+temp11*temp11/temp1/temp1/(temp1-1)/(temp1-1)));
		}
	    }
	    if(temp1>0 && temp3>0 && j<8){
		hsys1->SetBinContent(j,i,(1/temp3-1)/(1/temp1-1));
		
	    }
	    if(temp2>0 && temp3>0 && j<8){
		hsys2->SetBinContent(j,i,(1/temp3-1)/(1/temp2-1));
	    }
	    if(temp1>0 && temp1>0){
		hsys3->SetBinContent(j,i,(1/temp2-1)/(1/temp1-1));
		
	    }
	}
	have1->Delete();
	have2->Delete();
	have3->Delete();
	ht1->Delete();
	ht2->Delete();
	ht3->Delete();
	ht1_ht->Delete();
	ht2_ht->Delete();
	ht3_ht->Delete();
    }
    for(int j =5;j<10;j++){
	double tot;
	double hold;
	double tot1;
	double hold1;
	double tot2;
	double hold2;
	double cen;
	double cen1;
	double cen2;
	for(int i = 1;i<9;i++){
	    if(i==1){
		cen = hsys1->GetBinContent(j,i);
		cen1 = hsys2->GetBinContent(j,i);
		cen2 = hsys3->GetBinContent(j,i);
	    }else{
		if(i==2||i==5||i==7){//first phoe sys
		    hold = fabs(hsys1->GetBinContent(j,i)-cen);
		    hold1 = fabs(hsys2->GetBinContent(j,i)-cen1);
		    hold2 = fabs(hsys3->GetBinContent(j,i)-cen2);
		}
		else if(i==3||i==6||i==8){//first phoe sys
		    if(hold>fabs(hsys1->GetBinContent(j,i)-cen))tot+=hold*hold;
		    else tot+=(hsys1->GetBinContent(j,i)-cen)*(hsys1->GetBinContent(j,i)-cen);
		    if(hold1>fabs(hsys2->GetBinContent(j,i)-cen1))tot1+=hold1*hold1;
                    else tot1+=(hsys2->GetBinContent(j,i)-cen1)*(hsys2->GetBinContent(j,i)-cen1);
		    if(hold2>fabs(hsys3->GetBinContent(j,i)-cen2))tot2+=hold2*hold2;
                    else tot2+=(hsys3->GetBinContent(j,i)-cen2)*(hsys3->GetBinContent(j,i)-cen2);
		    hold=0;hold1=0;hold2=0;
		}
		else if(i==4){//second phoe sys                                                                                                                                                                             
		    tot += (hsys1->GetBinContent(j,i)-cen)*(hsys1->GetBinContent(j,i)-cen);
                    tot1 += (hsys2->GetBinContent(j,i)-cen1)*(hsys2->GetBinContent(j,i)-cen1);
                    tot2 += (hsys3->GetBinContent(j,i)-cen2)*(hsys3->GetBinContent(j,i)-cen2);
		}		
	    }
	    cout <<j << " " << i << " " << hsys1->GetBinContent(j,i) << " " << hsys2->GetBinContent(j,i) << " " << hsys3->GetBinContent(j,i) << endl;
	}
	cout <<j << " " << sqrt(tot) << " " << sqrt(tot1) << " " << sqrt(tot2) << endl;
	if(j<8)sys->SetPoint(j-5,hrat->GetBinCenter(j),cen);
	if(j<8)sys1->SetPoint(j-5,hrat1->GetBinCenter(j),cen1);
	sys2->SetPoint(j-5,hrat2->GetBinCenter(j),cen2);
	if(j<8)sys->SetPointError(j-5,0,sqrt(tot));
	if(j<8)sys1->SetPointError(j-5,0,sqrt(tot1));
	sys2->SetPointError(j-5,0,sqrt(tot2));

    }
    /*
    for(int i =5;i<10;i++){
	double temp = hrat1->GetBinContent(i);
	double temp1 = sys1->GetErrorY(i-5);
	hrat1->SetBinContent(i,temp-temp1);
	}*/
    for(int i = 5;i<10;i++){
	fb_sys1->SetPoint(i-5,fb_0_201->GetBinCenter(i),fb_0_201->GetBinContent(i));
	fb_sys2->SetPoint(i-5,fb_20_401->GetBinCenter(i),fb_20_401->GetBinContent(i));
	if(i<9)fb_sys3->SetPoint(i-5,fb_40_801->GetBinCenter(i),fb_40_801->GetBinContent(i));
	fb_sys1->SetPointError(i-5,0,fb1_sys->GetBinError(i));
	fb_sys2->SetPointError(i-5,0,fb2_sys->GetBinError(i));
	if(i<9)fb_sys3->SetPointError(i-5,0,fb3_sys->GetBinError(i));
    }



    TGraph * g1 = new TGraph();
    TGraph * g2 = new TGraph();
    TGraph * g3 = new TGraph();    
    getData(g1,"DR_RCP_0_20_40_80.dat");
    getData(g2,"DR_RCP_20_40_40_80.dat");
    getData(g3,"DR_RCP_0_20_20_40.dat");
    fb_40_801->SetLineColor(kMagenta);
    fb_40_801->SetMarkerColor(kMagenta);
    fb_40_801->SetMarkerStyle(21);
    fb_sys3->SetLineColor(kMagenta);
    g3->SetLineColor(kGreen-2);
    fb_20_401->SetLineColor(kGreen-2);
    fb_20_401->SetMarkerColor(kGreen-2);
    fb_20_401->SetMarkerStyle(22);
    fb_sys2->SetLineColor(kGreen-2);
    g2->SetLineColor(kRed);
    fb_0_201->SetLineColor(kRed);
    fb_0_201->SetMarkerColor(kRed);
    fb_0_201->SetMarkerStyle(33);
    fb_sys1->SetLineColor(kRed);
    g1->SetLineColor(kBlue);
    g1->SetLineStyle(2);
    g2->SetLineStyle(2);
    g3->SetLineStyle(2);
    
    FONLL->SetLineStyle(7);
    pp->SetLineColor(kBlue);
    pp->SetMarkerColor(kBlue); 
    pp->SetMarkerStyle(23);     
    pp_sys->SetLineColor(kBlue);
    pp_sys->SetFillColor(kBlue);
    pp_sys->SetFillStyle(3004);
    TLegend *leg = new TLegend(0.62,0.20,0.90,0.52);
//    leg->AddEntry(fb1,"Min. Bias","PE");
    leg->AddEntry(fb_0_201,"0-20%","PE");
    leg->AddEntry(fb_20_401,"20-40%","PE");
    leg->AddEntry(fb_40_801,"40-80%","PE");
    leg->AddEntry(pp,"#it{p+p} #sqrt{s}=200 GeV","PE");
    leg->AddEntry(FONLL,"FONLL","L");

 
  
    TF1 *fit = new TF1("fit","[0]",2,10);
    fit->SetLineColor(kBlue);
    fit->SetLineStyle(5);  
    TF1 *fit1 = new TF1("fit1","[0]",2,10);
    fit1->SetLineColor(kRed);
    fit1->SetLineStyle(6); 
    TF1 *fit2 = new TF1("fit2","[0]",2,10);
    fit2->SetLineColor(kGreen-2);
    fit2->SetLineStyle(2); 
    TF1 *line = new TF1("line","[0]",-1,10);
    line->SetLineStyle(7); 
    line->SetParameter(0,1); 
    TLegend *legg = new TLegend(0.15,0.5,0.7,0.7);
    hrat->Fit("fit");
    hrat1->Fit("fit1");
    hrat2->Fit("fit2");
    TLegend *legg1 = new TLegend(0.43,0.78,0.96,0.93);
 
    TLegend *legd1 = new TLegend(0.15,0.17,0.4,0.22);
    TF1 *prox = new TF1("prox","[0]",0,1);
    prox->SetLineStyle(2);
    legd1->AddEntry(prox,"DUKE","l");
    

    char label[100];
    double vall = fit->GetParameter(0);
    double errr = fit->GetParError(0); 
    char label1[100];
    double vall1 = fit1->GetParameter(0);
    double errr1 = fit1->GetParError(0); 
    char label2[100];
    double vall2 = fit2->GetParameter(0);
    double errr2 = fit2->GetParError(0); 
    sprintf(label,"0-20%: %1.2f #pm% 1.2f(stat.) #pm% 1.2f(syst.)",vall,errr,0.12);
    sprintf(label1,"20-40%: %1.2f #pm% 1.2f(stat.) #pm% 1.2f(syst.)",vall1,errr1,0.07);
    sprintf(label2,"0-20%: %1.2f #pm% 1.2f(stat.) #pm% 1.2f(syst.)",vall2,errr2,0.03);
    legg->AddEntry(hrat,label,"PE");
    legg->AddEntry(hrat1,label1,"PE");
    legg1->AddEntry(hrat2,label2,"PE");
    hrat->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    hrat->GetYaxis()->SetTitle("R_{CP}^{#it{b}#rightarrow#it{e}}/R_{CP}^{#it{c}#rightarrow#it{e}} (/40-80%)");    
    hrat->GetXaxis()->SetRangeUser(2,4.5);
    hrat->GetYaxis()->SetRangeUser(0.5,4);  
    hrat->SetLineColor(kBlue);
    hrat->SetMarkerColor(kBlue);  
    sys->SetLineColor(kBlue);
    sys->SetMarkerColor(kBlue);
    sys->SetFillColor(kBlue);
    sys->SetFillStyle(3005);
    hrat2->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    hrat2->GetYaxis()->SetTitle("R_{CP}^{#it{b}#rightarrow#it{e}}(0-20%)/R_{CP}^{#it{c}#rightarrow#it{e}}(20-40%)");    
    hrat2->GetXaxis()->SetRangeUser(2,7.5);
    hrat2->GetYaxis()->SetRangeUser(0.5,4);  
    hrat2->SetLineColor(kGreen-2);
    hrat2->SetMarkerColor(kGreen-2);  
    hrat1->SetLineColor(kRed);
    hrat1->SetMarkerColor(kRed); 
    hrat1->SetMarkerStyle(24);
    sys2->SetLineColor(kGreen-2);
    sys2->SetMarkerColor(kGreen-2);
    sys2->SetFillColor(kGreen-2);
    sys2->SetFillStyle(3005);
    sys1->SetLineColor(kRed);
    sys1->SetMarkerColor(kRed);
    sys2->SetMarkerStyle(1);
    sys1->SetMarkerStyle(1);
    sys->SetMarkerSize(3);
    sys2->SetMarkerSize(3);
    sys1->SetMarkerSize(3);
    sys->SetMarkerSize(3);
    sys1->SetFillColor(kRed);
    sys1->SetFillStyle(3004);
    TCanvas *c11 = new TCanvas ("c11","RCP/RCP",1200,500);
    c11->Divide(2,1);
    c11->cd(1);
    gStyle->SetEndErrorSize(5);
    hrat->GetFunction("fit")->Delete();
    hrat1->GetFunction("fit1")->Delete();
    hrat2->GetFunction("fit2")->Delete();
    hrat->Draw("E X0");
    sys->Draw("[] same");
    hrat1->Draw("E X0 same");
    sys1->Draw("[] same");
    g1->Draw("same l");
    g2->Draw("same l");
    line->Draw("same");
    legd1->Draw("same");
    legg->Draw("same");
    TPaveText *Name = new TPaveText(0.17,0.8,0.45,0.9,"BRNDC");
    Name->AddText("STAR preliminary");
    Name->SetFillColorAlpha(0, 0);
    Name->SetTextAlign(12);
    Name->SetBorderSize(0);
    Name->Draw("same");
    TPaveText *Name1 = new TPaveText(0.17,0.7,0.45,0.8,"BRNDC");
    Name1->AddText("Au+Au #sqrt{s_{NN}} = 200 GeV");
    Name1->SetFillColorAlpha(0, 0);
    Name1->SetTextAlign(12);
    Name1->SetBorderSize(0);
    Name1->SetTextSize(0.05);
    Name1->Draw("same");
    gPad->RedrawAxis();
    c11->cd(2);
    hrat2->Draw("PE X0");
    sys2->Draw("[] same");
    g3->Draw("same l");
    line->Draw("same");
    legg1->Draw("same");
    Name->Draw("same");
    Name1->Draw("same");
    legd1->Draw("same");

    gPad->RedrawAxis();
    
    TCanvas *c1 = new TCanvas ("c1","fbs");
    TPaveText *Name2 = new TPaveText(0.47,0.8,0.95,0.9,"BRNDC");
    Name2->AddText("Au+Au #sqrt{s_{NN}} = 200 GeV");
    Name2->SetFillColorAlpha(0, 0);
    Name2->SetTextAlign(12);
    Name2->SetBorderSize(0);
    Name2->SetTextSize(0.05);
    fb_0_201->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    fb_0_201->GetYaxis()->SetTitle("N(#it{b}#rightarrow#it{e})/N(#it{b+c}#rightarrow#it{e})");
    fb_0_201->GetXaxis()->SetRangeUser(1.5,8.);
    fb_0_201->GetYaxis()->SetRangeUser(0,1);
    fb_0_201->Draw("PE X0 same");
    pp_sys->Draw("E2 same");
    pp->Draw("same PE");
    fb_sys1->Draw("same []");
    fb_sys2->Draw("same []");
    fb_sys3->Draw("same []");
    fb_0_201->Draw("PE X0 same");
    fb_40_801->Draw("PE X0 same");
    fb_20_401->Draw("PE X0 same");
    FONLL->Draw("l same");
    leg->Draw("same");
    Name->Draw("same");
    Name2->Draw("same");
    gPad->RedrawAxis();
    c11->SaveAs("rcp_alone.pdf");
    
}//End
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
void getData(TH1F* h,char file[]) {
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
            double bkgre;double npere;double ere;

            data >> pT >> y1 >> e1 >> fb1 >> fb2 >> y2 >> e2 >> fc1 >> fc2 >> y3 >> e3 >> fe1 >> fe2 >> y4 >> e4 >> fh1 >> fh2 >> br >> bre >> bkgr>>bkgre >> nper >> npere >> er >> ere >> pur >> pure;
            if(pT>4){
                h->SetBinContent(pT,br);
                h->SetBinError(pT,bre);
            }
        }

    }
    else {
        cout <<"Nope " <<file  << "\n";
    }
    data.close();
}
void getAve(TH1F* h_ave,TH1F* h, TH1F*h_ht){

    for(int i =1; i<10;i++){
        double temp1 = h->GetBinContent(i);
        double temp2 = h->GetBinError(i);
        double temp3 = h_ht->GetBinContent(i);
        double temp4 = h_ht->GetBinError(i);
	if(temp1>0 && temp3>0){
            double temp = temp1/temp2/temp2 + temp3/temp4/temp4;
            double er1 = 1/temp2/temp2 + 1/temp4/temp4;
            h_ave->SetBinContent(i,temp/er1);
            h_ave->SetBinError(i,sqrt(1/er1));

        }else if(temp1>0 && temp3==0){
            h_ave->SetBinContent(i,temp1);
	    h_ave->SetBinError(i,temp2);
	}
        else if(temp1==0 && temp3>0){
            h_ave->SetBinContent(i,temp3);
	    h_ave->SetBinError(i,temp4);
	}
    }
}
void getData(TGraph *g,char file[]){
    int cnt=0;
    ifstream data(file);
    if(data.is_open()){
        while(!data.eof()){
            double x;double y;
            data >> x >> y;
            g->SetPoint(cnt,x,y);cnt++;
        }
    }
}
