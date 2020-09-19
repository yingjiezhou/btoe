#include "prettycanvasAll.C"
gSystem->Load("libRooFit.so");

using namespace RooFit;

void fitdata1D(TH1F *data,TH1F *data_e,TH1F* data_emis,TH1F *data_pi, TH1F *data_2pi,TH1F *data_k,TH1F *data_p,TH1F* data_D0,TH1F* data_jpsi,TH1F* data_B,int daughter,int mag, int save, 
                 char outputfile[],char datfile[],char datc[],char dir1[],char dir2[],char dir3[],char dir4[],char dir5[],char dir6[],
	       int pt,int eta, int rs,float cutLow,float cutHigh,double ptLow ,double ptHigh,double eff_b, int pur_dir, int HT)
{
    bool do_scan=false;
    char file_purity[50];
    sprintf(file_purity,"../FitPurity/%i/yields.dat",pur_dir);
    ifstream purData(file_purity);
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};
    //double errors[9]={0.01,0.01,0.01,0.01,0.01,0.02,0.03,0.1,0.09};
    double errors[9]={0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01};
    double corr[9]={1.,0.96,0.95,0.87,0.92,0.95,0.97,0.99,0.97};
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
		if(pur_dir==3)p1*=corr[int(pT)-1];
		hp1->SetBinContent(pT,p1);
		hp1->SetBinError(pT,errors[int(pT)-1]);

	    }
	}

    } else {
	cout <<"Nope \n";
    }
    double purity = hp1->GetBinContent(pt);
    double purity_error = hp1->GetBinError(pt);
    cout << "Using hadron purity of "<< purity << endl;

    TObjArray *mc = new TObjArray(5); 
    mc->Add(data_B);
    mc->Add(data_D0);
    mc->Add(data_e);
    mc->Add(data_pi);
    //mc->Add(data_jpsi);
    TFractionFitter* fit = new TFractionFitter(data, mc,"V");
    fit->Constrain(1,0.0,1);
    fit->Constrain(2,0.0,1);  // leave lower at 0.05 for MB
    fit->Constrain(3,0.0,1);
    fit->Constrain(4,0.0,1);
    //fit->Constrain(4,1-purity-1e-3+0.1,1-purity+1e-3+0.1);
    

    //if(pt==9||pt==8)fit->Constrain(4,0.,1);
    //if(pt==9||pt==8)fit->Constrain(3,0.,0.45);

    int bin1 = data->FindBin(-4);
    int bin2 = data->FindBin(-1);    
    fit->SetRangeX(bin1,bin2);
    Int_t status = fit->Fit(); 
 
    cout << "fit status: " << status << endl;
    if (status == 0) { 
	TH1F* result = (TH1F*) fit->GetPlot();
	data->GetXaxis()->SetTitle("ln(|DCA|/cm)");
	data->GetYaxis()->SetTitle("Candidates / 0.2");
	result->SetLineColor(kBlue);
	TH1F* mc1 = fit->GetMCPrediction(0);
	TH1F* mc2 = fit->GetMCPrediction(1);
	TH1F* mc3 = fit->GetMCPrediction(2);
	TH1F* mc4 = fit->GetMCPrediction(3);
	//TH1F* mc5 = fit->GetMCPrediction(4);
	mc1->SetLineColor(kGreen-2);
	mc2->SetLineColor(kMagenta);
	mc3->SetLineColor(kOrange-1);
	mc4->SetLineColor(kRed);
	//mc5->SetLineColor(kGray);
	mc1->SetLineStyle(7);
	mc2->SetLineStyle(2);
	mc3->SetLineStyle(5);
	mc4->SetLineStyle(8);
	//mc5->SetLineStyle(9);
	double y1 =0;
	double e1 =0;
	double y2 =0;
	double e2 =0;
	double y3 =0;
	double e3 =0;
	double y4 =0;
	double e4 =0;
	double y5 =0;
	double e5 =0;
	fit->GetResult(0,y1,e1);
	fit->GetResult(1,y2,e2);
	fit->GetResult(2,y3,e3);
	fit->GetResult(3,y4,e4);
	//fit->GetResult(4,y5,e5);
	mc1->Scale(data->Integral(bin1,bin2)/mc1->Integral(bin1,bin2)*y1);	
	mc2->Scale(data->Integral(bin1,bin2)/mc2->Integral(bin1,bin2)*y2);	
	mc3->Scale(data->Integral(bin1,bin2)/mc3->Integral(bin1,bin2)*y3);	
	mc4->Scale(data->Integral(bin1,bin2)/mc4->Integral(bin1,bin2)*y4);
	//mc5->Scale(data->Integral(bin1,bin2)/mc5->Integral(bin1,bin2)*y5);	
	y1*=data->Integral(bin1,bin2);
	y2*=data->Integral(bin1,bin2);
	y3*=data->Integral(bin1,bin2);
	y4*=data->Integral(bin1,bin2);	
	y5*=data->Integral(bin1,bin2);	
	e1*=data->Integral(bin1,bin2);
	e2*=data->Integral(bin1,bin2);
	e3*=data->Integral(bin1,bin2);
	e4*=data->Integral(bin1,bin2);	
	e5*=data->Integral(bin1,bin2);	

	TPaveText *Name = new TPaveText(gStyle->GetPadLeftMargin() + 0.4,
					0.77 - gStyle->GetPadTopMargin(),
					gStyle->GetPadLeftMargin() + 0.8,
					0.95 - gStyle->GetPadTopMargin(),
                                        "BRNDC");

	Name->AddText("STAR Au+Au 200 GeV");
	Name->SetFillColorAlpha(0, 0);
	Name->SetTextAlign(12);
	Name->SetBorderSize(0);
	TCanvas *c1 = new TCanvas("c1","c1");// check on fit status
	TPad *pad1 = new TPad("pad1","pad1",0.0,0.257,1.0,1.0);
	TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
	TGaxis::SetMaxDigits(3);
	pad1->SetBottomMargin(0.02);
	pad1->SetTopMargin(0.08);
	pad2->SetTopMargin(0.015);
	pad2->SetBottomMargin(0.5);
	pad2->SetBorderMode(0);
	pad1->SetBorderMode(0);
	c1->SetBorderMode(0);
	pad1->Draw();
	pad2->Draw();
	pad1->cd();
	data->GetYaxis()->SetRangeUser(0,data->GetMaximum()*1.3);
	data->GetYaxis()->SetTitleSize(0.1);
	data->GetYaxis()->SetTitleOffset(0.6);
	data->GetXaxis()->SetRangeUser(-4,-1);
	data->SetTitle("");
	data->Draw("Ep");
	result->Draw("same");
	TLegend *leg = new TLegend(0.2,0.4,0.45,0.8);
	leg->AddEntry(result,"Total fit","l");
	leg->AddEntry(mc3,"Photonic #it{e}","l");
	leg->AddEntry(mc4,"Hadrons","l");
	//leg->AddEntry(mc5,"J/#psi#rightarrow#it{e}X ","l");
	leg->AddEntry(mc2,"#it{c}#rightarrow#it{e}X","l");
	leg->AddEntry(mc1,"#it{b}#rightarrow#it{e}X","l");
	mc1->Draw("same hist");
	mc2->Draw("same hist");
	mc3->Draw("same hist");
	mc4->Draw("same hist");
	//mc5->Draw("same hist");
	Name->Draw("SAME");
	leg->Draw("same");
	TLatex lat;
	char label[30];
	sprintf(label,"#it{p}_{T}#in [%1.1f,%1.1f] GeV",ptLow,ptHigh);
	lat.SetTextSize(0.08);
	lat.DrawLatex(-2.23,data->GetMaximum()*0.7,label);
	pad2->cd();
	Pull = new TH1F("Pull","Pull",mc1->GetNbinsX(),-4,-1);
	Pull->GetXaxis()->SetTitle("log_{10}(|DCA|/cm)");
	for(int i = 1; i<mc1->GetNbinsX()+1;i++){
	    int push = data->FindBin(-4);
	    double check1 = data->GetBinCenter(i);
	    double check2 = result->GetBinCenter(i);	
	    double temp1 = data->GetBinContent(i);
	    double temp2 = result->GetBinContent(i);     
	    if(data->GetBinError(i)>0)  double den = sqrt(data->GetBinError(i)*data->GetBinError(i));
	    else double den = 1;
			      
	    Pull->SetBinContent(i,(temp2-temp1)/den);
	}
	Pull->SetTitle(0);
	Pull->GetYaxis()->SetTitle("Pull");
	Pull->GetYaxis()->SetTitleSize(0.15);
	Pull->GetYaxis()->SetLabelSize(0.1);
	Pull->GetYaxis()->CenterTitle();
	Pull->GetYaxis()->SetTitleOffset(0.3);
	Pull->GetYaxis()->SetNdivisions(505);
	Pull->GetYaxis()->SetRangeUser(-5.9,5.9);
	Pull->GetXaxis()->SetTitleSize(0.3);
	Pull->GetXaxis()->SetLabelSize(0.15);
	Pull->GetXaxis()->SetTitleOffset(0.63);
	Pull->SetFillColor(1);
	Pull->SetFillStyle(1000);	
	Pull->Draw("hist");

        cout << "Bottom eff. "     << eff_b <<endl;
        if(fit->GetNDF()>0)cout << "Fit #chi^{2} "     << fit->GetChisquare() << " " << fit->GetNDF()<< " " << fit->GetChisquare()/fit->GetNDF() <<endl;
	if(eff_b==0) eff_b=1;
	cout << "Bottom yield "     << y1 << "+/- " << e1 << endl;
	cout << "Charm yield "      << y2 << "+/- " << e2 << endl;
	cout << "Photonic e yield " << y3 << "+/- " << e3 << endl;
	cout << "Hadron yield "     << y4 << "+/- " << e4 << endl;
	cout << "============" << endl;
	double error = sqrt(y2/(y1/eff_b+y2)/(y1/eff_b+y2)*y2/(y1/eff_b+y2)/(y1/eff_b+y2)*e1*e1  + y1/eff_b/(y1/eff_b+y2)/(y1/eff_b+y2)*y1/eff_b/(y1/eff_b+y2)/(y1/eff_b+y2)*e2*e2); 
	cout << "b/(b+c) " << y1/eff_b/(y1/eff_b+y2) << "+/- " << error << endl;
	cout << "============" << endl;
	
	int bin1 = mc1->FindBin(-1.5);
	int bin2 = mc1->FindBin(-1);	
	double frac1 = mc1->Integral(bin1,bin2);
	double frac2 = mc2->Integral(bin1,bin2);
	double frac3 = mc3->Integral(bin1,bin2);
	double frac4 = mc4->Integral(bin1,bin2);
	double sum = frac1+frac2+frac3+frac4;
	bin1 = mc1->FindBin(-2);
	bin2 = mc1->FindBin(-1.5);	
	double frac11 = mc1->Integral(bin1,bin2);
	double frac22 = mc2->Integral(bin1,bin2);
	double frac33 = mc3->Integral(bin1,bin2);
	double frac44 = mc4->Integral(bin1,bin2);
	double sum1 = frac11+frac22+frac33+frac44;
	cout << "Fractions"<< "============" <<endl;
	cout <<"log(DCA) in [-1.5,-1]" << endl;
	cout << "B      " << frac1/sum << endl;
	cout << "D      " << frac2/sum << endl;
	cout << "Pho e  " << frac3/sum << endl;
	cout << "Hadron " << frac4/sum << endl;
	cout <<"log(DCA) in [-2,-1.5]"  << endl;
	cout << "B      " << frac11/sum1 << endl;
	cout << "D      " << frac22/sum1 << endl;
	cout << "Pho e  " << frac33/sum1 << endl;
	cout << "Hadron " << frac44/sum1 << endl;
	cout << "End Fractions"<< "============" <<endl;

	if(do_scan){
	    int num_scan =30;
	    cout << "============"<< "Doing scan"<< "============" <<endl;
	    cout << "============"<< "N points" << num_scan << "============" <<endl;
	    double opt1_l = -1;
	    double opt1_h = -1;
	    double best1=0;
	    double best_fb=0;
	    double opt2_l = -1;
	    double opt2_h = -1;
	    double best2=0;
	    double best_fc=0;
	    for(int i=0;i<num_scan+1;i++){
		int bin_1 = mc1->FindBin(-5.+float(i)*3./float(num_scan));
		for(int j=0;j<num_scan+1;j++){
		    if(j<=i)continue;
		    int bin_2 = mc1->FindBin(-5.+float(j)*3./float(num_scan));
		    double temp1 = mc1->Integral(bin_1,bin_2);
		    double temp2 = mc2->Integral(bin_1,bin_2);
		    double temp3 = mc3->Integral(bin_1,bin_2);
		    double temp4 = mc4->Integral(bin_1,bin_2);
		    double temp5 = temp1+temp2+temp3+temp4;
		    double sig1 = temp1*temp1/mc1->Integral()/(temp2+temp3+temp4);
		    double sig2 = temp2*temp2/mc2->Integral()/(temp2+temp3+temp4);
		    double frac_b = temp1/(temp1+temp2+temp3+temp4);
		    double frac_c = temp2/(temp1+temp2+temp3+temp4);
		    cout << "low/high bin:sigb:sigc " << -10.+i*8./num_scan << " " << -10.+j*8./num_scan << " " << sig1 << " " << sig2 << endl;	
		    if(sig1>best1){
			opt1_l = -5.+float(i)*3./float(num_scan);
			opt1_h = -5.+float(j)*3./float(num_scan);
			best1 = sig1;
			best_fb = frac_b;
		    }
		    if(sig2>best2){
			opt2_l = -5.+float(i)*3./float(num_scan);
			opt2_h = -5.+float(j)*3./float(num_scan);
			best2 = sig2;
			best_fc = frac_c;
		    }
		}
	    }
	    cout << "============"<< "End scan"<< "============" <<endl;
	    cout << "============"<< "Optimum values for b->e"<< "============" <<endl;	
	    cout << "Significance " << best1 << endl;
	    cout << "Fraction " << best_fb << endl;
	    cout << "low bin " << opt1_l << endl;
	    cout << "high bin " << opt1_h << endl;
	    cout << "============"<< "Optimum values for c->e"<< "============" <<endl;	
	    cout << "Significance " << best2 << endl;
	    cout << "Fraction " << best_fc << endl;
	    cout << "low bin " << opt2_l << endl;
	    cout << "high bin " << opt2_h << endl;		
	}
	if (save==1){
	    ofstream output1 (datfile,ios::app);
	    if(output1.is_open()){
		output1 <<  pt <<" " << y1 << " " << e1 << " " << frac1/sum << " " << frac11/sum1<< " " << 
		                        y2 << " " << e2 << " " << frac2/sum << " " << frac22/sum1<< " " << 
		                        y3 << " " << e3 << " " << frac3/sum << " " << frac33/sum1<< " " << 
		    y4 << " " << e4 << " " << frac4/sum << " " << frac44/sum1<< " " << eff_b << " " << purity<< "\n";
		output1.close();
	    }else(cout << "Error Opening Output Dat File!");
	    c1->SaveAs(dir1);
	}

    }
}



 

  



