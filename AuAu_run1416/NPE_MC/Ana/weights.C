Double_t func(Double_t *x, Double_t *par){
    Double_t arg = 0;
    Double_t val = 0;
    if(par[2]!=0 && par[1]!=1){
	arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
	val = par[0]*sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1]));//exp(arg*(1/(1-par[1])));
    }
    return val;
}
Double_t func3(Double_t *x, Double_t *par){
    Double_t arg = 0;
    Double_t val = 0;
    if(par[2]!=0 && par[1]!=1){
	arg = 1+sqrt(x[0]*x[0]+1864.84*1864.84)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
	val = par[0]*sqrt(x[0]*x[0]+1864.84*1864.84)*TMath::Power(arg,-1/(1-par[1]));//exp(arg*(1/(1-par[1])));
    }
    return val;
}
Double_t func1(Double_t *x, Double_t *par){
    Double_t arg = 0;
    Double_t val = 0;
    if(par[2]!=0 && par[1]!=1){
	arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
	val = par[0]*(sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1])));//exp(arg*(1/(1-par[1])));
    }
    return val;
}
Double_t func2(Double_t *x, Double_t *par){
    Double_t arg = 0;
    Double_t val = 0;
    if(par[2]!=0 && par[1]!=1){
	arg = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[2]*(1-par[1]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
	val = par[0]*(sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg,-1/(1-par[1])));//exp(arg*(1/(1-par[1])));
    }
    Double_t arg1 = 0;
    Double_t val1 = 0;
    if(par[5]!=0 && par[4]!=1){
	arg1 = 1+sqrt(x[0]*x[0]+0.14*0.14)/par[5]*(1-par[4]);//1.+(par[1]-1)*sqrt(x[0]*x[0]+0.149*0.149)/par[2];
	val1 = par[3]*(sqrt(x[0]*x[0]+0.14*0.14)*TMath::Power(arg1,-1/(1-par[4])));//exp(arg*(1/(1-par[1])));
    }
    return val/val1;
}

void weights(){
    gROOT->ProcessLine(".x ~/myStyle.C");  
    //gStyle->SetPadLeftMargin(2);
    TGaxis::SetMaxDigits(3);  
double xx[31] = {3.50E-01,
		     4.50E-01,
		     5.50E-01,
		     6.50E-01,
		     7.50E-01,
		     8.50E-01,
		     9.50E-01,
		     1.05E+00,
		     1.15E+00,
		     1.30E+00,
		     1.50E+00,
		     1.70E+00,
		     1.90E+00,
		     2.10E+00,
		     2.35E+00,
		     2.63E+00,
		     2.75E+00,
		     2.88E+00,
		     3.13E+00,
		     3.38E+00,
		     3.50E+00,
		     3.63E+00,
		     3.88E+00,
		     4.25E+00,
		     4.75E+00,
		     5.25E+00,
		     5.75E+00,
		     6.50E+00,
		     7.50E+00,
		     9.00E+00,
		     1.10E+01};
    double xxe[31] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double yy[31] = {4.26E+01,
		     2.56E+01,
		     1.56783E+01,
		     9.86E+00,
		     6.31E+00,
		     4.06E+00,
		     2.65955E+00,
		     1.7719099999999999E+00,
		     1.17E+00,
		     6.57E-01,
		     3.1908E-01,
		     1.56E-01,
		     7.9025E-02,
		     4.78E-02,
		     2.13E-02,
		     1.06E-02,
		     7.48E-03,
		     5.46E-03,
		     2.8341999999999994E-03,
		     1.55E-03,
		     1.30E-03,
		     8.70E-04,
		     5.02E-04,
		     2.41E-04,
		     9.53E-05,
		     4.10355E-05,
		     1.79E-05,
		     7.2813999999999994E-06,
		     2.2174999999999995E-06,
		     6.40E-07,
1.10E-07};
    double yye[31] = {10.1257582925922,6.16275449454219,3.81753930693582,
		      2.40996433998514,
		      1.54802814250904,
		      1.39443326480689,
		      0.916378595341467,
		      0.609412815749718,
		      0.332821598457792,
		      0.196180555611406,
		      0.0864041347390274,
		      0.0421343731411777,
		      0.0217992660426905,
		      0.0223785889635607,
		      0.0102306500770968,
		      0.00343786998008942,
		      0.000585375921951014,
		      0.00319489407336143,
		      0.00160680456807914,
		      0.00082073041134102,
		      0.000433909716991911,
		      0.000238846121174282,
		      0.000135396632897572,
		      0.0000634586526803083,
		      0.0000252087365807967,
		      0.0000107202119382035,
		      0.00000488209391552436,
		      0.00000195091645131205,
		      0.00000066760167764918,
		      0.000000285457562520246,
		      0.0000000854622934398557};
    double xx2[24]={1.17606,1.68542,2.19144,2.69754,3.33822,4.36991,4.25,4.75,5.25,5.75,6.25,6.75,7.25,7.75,8.5,9.5,11,13};
    double yy2[24]={0.141133,0.0162162,0.00231514,0.000530275,0.00015278,2.00909E-05,1.533E-05,9.707E-06,4.981E-06,3.263E-06,1.547E-06,1.216E-06,8.215E-07,5.139E-07,2.494E-07,1.346E-07,4.688E-08,1.887E-08};
    double xx2e[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    double yy2e[24]={0.033677,0.003804,0.000732,0.000202,0.000049,0.000009,1.063E-05,4.635E-06,2.265E-06,1.16E-06,5.959E-07,3.855E-07,2.507E-07,1.579E-07,7.485E-08,4.15E-08,1.456E-08,6.394E-09};

    double xx3[11]={0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.25,3,4.25};
    double yy3[11]={1.229721,1.145734,1.172174,1.172357,1.211729,1.201061,1.234643,1.223676,1.225788,1.307334,1.363853};
    double xx3e[11]={0,0,0,0,0,0,0,0,0,0,0};
    double yy3e[11]={0.0825,0.0732,0.0737,0.0727,0.0759,0.0769,0.0797,0.0826,0.0804,0.0883,0.1258};
    double pully[31];
    double pully2[24];   
    double pullye[31];
    double pullye2[24];   

    double xx4[7]={3.15e-01,9.68e-01,1.35,1.89,2.56,3.75,5.88};
    double yy4[7]={4.16e-02*2*TMath::Pi()*3.15e-01
		   ,3.59e-02*2*TMath::Pi()*9.68e-01
		   ,2.48e-02*2*TMath::Pi()*1.35
		   ,9.50e-03*2*TMath::Pi()*1.89
		   ,2.00e-03*2*TMath::Pi()*2.56
		   ,2.32e-04*2*TMath::Pi()*3.75
		   ,6.65e-06*2*TMath::Pi()*5.88};
    double xx4e[7]={0,0,0,0,0,0,0};
    double yy4e[7]={0.010026464980241,0.0081608,0.0047634,0.00194612,0.00048301,0.00005131,0.00000186};
    

    TGraphErrors *gpi = new TGraphErrors(31,xx,yy,xxe,yye);
    TGraphErrors *ggamma = new TGraphErrors(24,xx2,yy2,xx2e,yy2e);
    TGraphErrors *gd0 = new TGraphErrors(7,xx4,yy4,xx4e,yy4e);
    TGraphErrors *grat = new TGraphErrors(11,xx3,yy3,xx3e,yy3e);    
    //int const numPtBins=10;
    //double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5,20};
    int const numPtBins=200;
    double binning[numPtBins+1];
    for(int i =0 ;i<numPtBins+1;i++){
	binning[i]=i*20./200.;
    }
    TH1F* ratio =  new TH1F("ratio","ratio",numPtBins,binning); 
    
    TFile * f= new TFile("root/Gen_full.root");
    write_gamma=(TH1F*)f->Get("write_gamma");
    write_pi0=(TH1F*)f->Get("write_pi0");  

    write_pi0->SetMarkerColor(kRed);
    write_gamma->SetMarkerColor(kRed); 
    write_pi0->SetMarkerStyle(22);
    write_gamma->SetMarkerStyle(22);   
    write_pi0->SetLineColor(kRed);
    write_gamma->SetLineColor(kRed); 

    gen_gamma=(TH1F*)f->Get("gen_gamma");
    gen_pi0=(TH1F*)f->Get("gen_pi0");  
    //gen_gamma->Rebin();
    //gen_pi0->Rebin();
    
    TH1F * pi0_weights = new TH1F("pi0_weights","pi0_weights",200,0,20);
    TH1F * D0_weights = new TH1F("D0_weights","D0_weights",200,0,20);
    TH1F * gamma_weights = new TH1F("gamma_weights","gamma_weights",200,0,20);
    for(int i = 1; i< gen_gamma->GetNbinsX()+1;i++){
	double temp1 = gen_gamma->GetBinContent(i);
	double temp11 = gen_gamma->GetBinError(i);
	double temp2 = gen_gamma->GetBinCenter(i);
        double temp3 = gen_pi0->GetBinContent(i);
	double temp33 = gen_pi0->GetBinError(i);
	double temp4 = gen_pi0->GetBinCenter(i);
	gen_gamma->SetBinContent(i,1./2./3.14*temp1/temp2/127442/1.4/gen_gamma->GetBinWidth(i));
	gen_gamma->SetBinError(i,1./2./3.14*temp11/temp2/127442/1.4/gen_gamma->GetBinWidth(i));
        gen_pi0->SetBinContent(i,1./2./3.14*temp3/temp4/(204654-127442)/1.4/gen_pi0->GetBinWidth(i));
	gen_pi0->SetBinError(i,1./2./3.14*temp33/temp4/(2046540-127442)/1.4/gen_pi0->GetBinWidth(i));
	
    }
    for(int i = 1; i< write_gamma->GetNbinsX()+1;i++){
        double temp1 = write_gamma->GetBinContent(i);
        double temp11 = write_gamma->GetBinError(i);
        double temp2 = write_gamma->GetBinCenter(i);
        double temp3 = write_pi0->GetBinContent(i);
        double temp33 = write_pi0->GetBinError(i);
        double temp4 = write_pi0->GetBinCenter(i);
        write_gamma->SetBinContent(i,1./2./3.14*temp1/temp2/127442/1.4/write_gamma->GetBinWidth(i));
        write_gamma->SetBinError(i,0);//1./2./3.14*temp11/temp2/127442/1.4/write_gamma->GetBinWidth(i));
        write_pi0->SetBinContent(i,1./2./3.14*temp3/temp4/(204654-127442)/1.4/write_pi0->GetBinWidth(i));
        write_pi0->SetBinError(i,0);//1./2./3.14*temp33/temp4/(2046540-127442)/1.4/write_pi0->GetBinWidth(i));

    }
    //write_pi0->Scale(1./(204654-127442));
    // write_gamma->Scale(1./127442);
    //norm(gen_gamma);
    // norm(gen_pi0);

    //TF1 *fpi = new TF1("fpi","[0]*exp(([1]+x)*([2]+x))",0,20);
    TF1 *fpi = new TF1("fpi",func,0.1,20,3);
    fpi->SetParameter(0,1.44381e+04);
    fpi->SetParameter(1,9.18928e-01);
    fpi->SetParameter(2,1.10008e-01);
    TF1 *fd0 = new TF1("fd0",func,0.1,20,3);
    //fd0->SetParameter(0,1.44381e+04);
    //fd0->SetParameter(1,9.18928e-01);
    fd0->SetParameter(2,1.10008e-01);
    TF1 *fgamma = new TF1("fgamma",func1,1,20,3);
    fgamma->SetParameter(0,7.38384e+08);
    fgamma->SetParameter(1,8.73512e-01);
    fgamma->SetParameter(2,9.10666e-03);
    TF1 *fpimc = new TF1("fpimc",func,0.1,20,3);
    fpimc->SetParameter(0,1.44381e+04);
    fpimc->SetParameter(1,9.18928e-01);
    fpimc->SetParameter(2,1.10008e-01);
    TF1 *fgammamc = new TF1("fgammamc",func1,1,20,3);
    fgammamc->SetParameter(0,7.38384e+08);
    fgammamc->SetParameter(1,8.73512e-01);
    fgammamc->SetParameter(2,9.10666e-03);


    TF1 *fratio = new TF1("fratio",func2,0.1,20,6);
    fratio->SetParameter(0,1.44381e+04);
    fratio->SetParameter(1,9.18928e-01);
    fratio->SetParameter(2,1.10008e-01);
    fratio->SetParameter(3,7.38384e+08);
    fratio->SetParameter(4,8.73512e-01);
    fratio->SetParameter(5,9.10666e-03);  
    TCanvas *c1w = new TCanvas("c1w","c1w");
    TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
    pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.08);
    pad2->SetTopMargin(0.015);
    pad2->SetBottomMargin(0.5);  
    pad2->SetBorderMode(0);
    pad1->SetBorderMode(0);
    pad1->Draw();
    pad2->Draw(); 
    pad1->cd(); 
    gpi->GetYaxis()->SetRangeUser(10e-9,1000);
    gpi->Fit(fpi,"r");
    int bin = gen_pi0->FindBin(0.4);
    //gen_pi0->Scale(fpi->Eval(gen_pi0->GetBinCenter(bin))/gen_pi0->GetMaximum());

    fpi->SetLineColor(kBlue);
    gpi->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}} #frac{d^{2}N}{dydp_{T}} [#frac{c^{2}}{GeV^{2}}]");
    gpi->GetYaxis()->SetTitleOffset(0.85);
    gpi->Draw("APE");
    write_pi0->Draw("same PE");
    fpi->Draw("l same");
    pad2->cd();
    for(int i = 0; i<31;i++){
	pully[i] = (fpi->Eval(xx[i])/yy[i]);
	pullye[i] = (fpi->Eval(xx[i])/yy[i])*sqrt(yye[i]/yy[i]);
    }
    TGraphErrors *gpi_p = new TGraphErrors(31,xx,pully,xxe,pullye);	    
    gpi_p->GetXaxis()->SetTitle("p_{T} [GeV]");
    gpi_p->GetYaxis()->SetTitle("Fit/Data");
    gpi_p->SetTitle(0);
    gpi_p->GetYaxis()->SetTitleSize(0.15);
    gpi_p->GetYaxis()->SetLabelSize(0.1);
    gpi_p->GetYaxis()->CenterTitle();
    gpi_p->GetYaxis()->SetTitleOffset(0.3);
    gpi_p->GetYaxis()->SetNdivisions(505);
    gpi_p->GetYaxis()->SetRangeUser(0,1.7);
    gpi_p->GetXaxis()->SetTitleSize(0.3);
    gpi_p->GetXaxis()->SetLabelSize(0.15);  
    gpi_p->GetXaxis()->SetTitleOffset(0.63);
    gpi_p->Draw("APE");
    TF1 *fline = new TF1("fline","1",0,20);
    fline->SetLineStyle(7);
    fline->Draw("same");
  //================================================================================
    TCanvas *c2w = new TCanvas("c2w","c2w");
    TPad *pad12 = new TPad("pad12","pad12",0.0,0.25,1.0,1.0);
    TPad *pad22 = new TPad("pad22","pad22",0.0,0.0,1.0,0.255);
    pad12->SetBottomMargin(0.02);
    pad12->SetTopMargin(0.08);
    pad22->SetTopMargin(0.015);
    pad22->SetBottomMargin(0.5);  
    pad22->SetBorderMode(0);
    pad12->SetBorderMode(0);
    pad12->Draw();
    pad22->Draw(); 
    pad12->cd(); 
    fgamma->SetParameter(0,2);
    fgamma->SetParLimits(0,0,1e9);
    fgamma->SetParameter(1,0.5);
    fgamma->SetParameter(2,0.23);
    ggamma->GetYaxis()->SetRangeUser(10e-9,1);
    ggamma->Fit(fgamma,"r");
    bin = gen_pi0->FindBin(1.5);
    //gen_gamma->Scale(fgamma->Eval(gen_gamma->GetBinCenter(bin))/gen_gamma->GetMaximum());
    fgamma->SetLineColor(kBlue);
    //ggamma->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dydp_{T} [c^{2}/GeV^{2}]");
    ggamma->GetYaxis()->SetTitle("#frac{1}{2#pip_{T}} #frac{d^{2}N}{dydp_{T}} [#frac{c^{2}}{GeV^{2}}]");  
    ggamma->GetYaxis()->SetTitleOffset(0.85);
//gen_gamma->Scale(ggamma->GetMaximum()/gen_gamma->GetMaximum());
    ggamma->Draw("APE");
    fgamma->Draw("l same");
    write_gamma->Draw("same PE");
    pad22->cd(); 
    for(int i = 0; i<24;i++){
	pully2[i] = (fgamma->Eval(xx2[i])/yy2[i]);
	pullye2[i] = (fgamma->Eval(xx2[i])/yy2[i])*sqrt(yy2e[i]/yy2[i]);
    }
    TGraphErrors *ggamma_p = new TGraphErrors(24,xx2,pully2,xx2e,pullye2);
    ggamma_p->GetXaxis()->SetTitle("p_{T} [GeV]");
    ggamma_p->GetYaxis()->SetTitle("Fit/Data");
    ggamma_p->SetTitle(0);
    ggamma_p->GetYaxis()->SetTitleSize(0.15);
    ggamma_p->GetYaxis()->SetLabelSize(0.1);
    ggamma_p->GetYaxis()->CenterTitle();
    ggamma_p->GetYaxis()->SetTitleOffset(0.3);
    ggamma_p->GetYaxis()->SetNdivisions(505);
    ggamma_p->GetYaxis()->SetRangeUser(0,1.7);
    ggamma_p->GetXaxis()->SetTitleSize(0.3);
    ggamma_p->GetXaxis()->SetLabelSize(0.15);  
    ggamma_p->GetXaxis()->SetTitleOffset(0.63);
    ggamma_p->Draw("APE"); 
    fline->Draw("same");

    TCanvas *c3w =  new TCanvas ("c3w","");
    fratio->GetXaxis()->SetTitle("p_{T} [GeV]");
    fratio->GetXaxis()->SetRangeUser(0,20);
    fratio->GetYaxis()->SetTitle("#pi^{0}/#gamma");
    for(int i=0;i<numPtBins;i++){
	int bin  = pi0_weights->FindBin(binning[i]);
	double temp1 = pi0_weights->GetBinContent(bin);//fpi->Integral(binning[i],binning[i+1]);
	double temp2 = gamma_weights->GetBinContent(bin);//fgamma->Integral(binning[i],binning[i+1]);
	ratio->SetBinContent(i+1,temp1/temp2);
	ratio->SetBinError(i+1,temp1/temp2*0.1);	
    }
    fratio->Draw("L");
    ratio->Draw("same");
    TCanvas *c4w =  new TCanvas ("c4w","");
    grat->GetYaxis()->SetRangeUser(0,2);
    grat->GetYaxis()->SetTitle("#gamma^{inclusive}/#gamma^{hadron}");    
    grat->Fit("pol0");
    grat->Draw("APE");

    TCanvas *c4 = new TCanvas("c4","");
    gen_gamma->Fit(fgammamc);
    gen_gamma->Draw("PE");
    fgammamc->Draw("l same");
    TCanvas *c44 = new TCanvas("c44","");
    gen_pi0->Fit(fpimc);
    gen_pi0->Draw("PE same");
    fpimc->Draw("l same");
    TCanvas *c6 = new TCanvas("c6","D0 weights");
    gd0->Fit(fd0); 
    gd0->Draw("APE");
    for(int i =1;i<pi0_weights->GetNbinsX();i++){
	double val = fpi->Eval(pi0_weights->GetBinCenter(i))/fpimc->Eval(pi0_weights->GetBinCenter(i));
	double val1 = fgamma->Eval(gamma_weights->GetBinCenter(i))/fgammamc->Eval(gamma_weights->GetBinCenter(i));
	double val2 = fd0->Eval(D0_weights->GetBinCenter(i));
	pi0_weights->SetBinContent(i,val);
	gamma_weights->SetBinContent(i,val1);
	D0_weights->SetBinContent(i,val2);
    }
    TCanvas *c444 = new TCanvas("c444","gamma weights");
    gamma_weights->Draw();
    TCanvas *c4444 = new TCanvas("c4444","pi0 weights");
    pi0_weights->Draw();

/*    TFile fi("root/Pi0_Gamma_Ratio.root","RECREATE");
    ratio->Write("ratio");
    pi0_weights->Write();
    D0_weights->Write();
    gamma_weights->Write();
*/

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
    /*double xx[31] = {3.50E-01,
		     4.50E-01,
		     5.50E-01,
		     6.50E-01,
		     7.50E-01,
		     8.50E-01,
		     9.50E-01,
		     1.05E+00,
		     1.15E+00,
		     1.30E+00,
		     1.50E+00,
		     1.70E+00,
		     1.90E+00,
		     2.10E+00,
		     2.35E+00,
		     2.63E+00,
		     2.75E+00,
		     2.88E+00,
		     3.13E+00,
		     3.38E+00,
		     3.50E+00,
		     3.63E+00,
		     3.88E+00,
		     4.25E+00,
		     4.75E+00,
		     5.25E+00,
		     5.75E+00,
		     6.50E+00,
		     7.50E+00,
		     9.00E+00,
		     1.10E+01};
    double xxe[31] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double yy[31] = {2.84E+02,
		     1.73E+02,
		     1.0648E+02,
		     6.72E+01,
		     4.30E+01,
		     2.78E+01,
		     1.8195E+01,
 		     1.2126000000000001E+01,
		     8.25E+00,
		     4.64E+00,
		     2.234E+00,
		     1.09E+00,
		     5.52E-01,
		     3.08E-01,
		     1.39E-01,
		     6.60E-02,
		     4.80E-02,
		     3.34E-02,
		     1.706E-02,
		     9.10E-03,
		     7.92E-03,
		     5.01E-03,
		     2.85E-03,
		     1.34E-03,
		     5.19E-04,
		     2.2504999999999997E-04,
		     9.795E-05,
		     3.8939999999999996E-05,
		     1.227E-05,
		     3.54E-06,
		     6.25E-07};
    double yye[31] = {10.1257582925922,6.16275449454219,3.81753930693582,
		      2.40996433998514,
		      1.54802814250904,
		      1.39443326480689,
		      0.916378595341467,
		      0.609412815749718,
		      0.332821598457792,
		      0.196180555611406,
		      0.0864041347390274,
		      0.0421343731411777,
		      0.0217992660426905,
		      0.0223785889635607,
		      0.0102306500770968,
		      0.00343786998008942,
		      0.000585375921951014,
		      0.00319489407336143,
		      0.00160680456807914,
		      0.00082073041134102,
		      0.000433909716991911,
		      0.000238846121174282,
		      0.000135396632897572,
		      0.0000634586526803083,
		      0.0000252087365807967,
		      0.0000107202119382035,
		      0.00000488209391552436,
		      0.00000195091645131205,
		      0.00000066760167764918,
		      0.000000285457562520246,
		      0.0000000854622934398557};
    */
