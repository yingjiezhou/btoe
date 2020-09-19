void calc_raa(){
    gROOT->ProcessLine(".x ~/myStyle.C");
    // DUKE                                                                                                                                                                                                            
    TFile *fill1 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_MC/Ana/root/NULLer.root");
    null_hyper = (TH1F*)fill1->Get("null_hyper");
    null_hyper->SetName("null_hyper");
    null_hyp_biner = (TH1F*)fill1->Get("null_hyp_biner");         
    null_hyp_biner->SetName("null_hyp_biner");
    TFile *fill = new TFile("/gpfs01/star/pwg/mkelsey/NPE_MC/Ana/root/NULL.root");
    null_hyp = (TH1F*)fill->Get("null_hyp");
    null_hyp_bin = (TH1F*)fill->Get("null_hyp_bin");                      
    
    for(int i=1;i<null_hyp->GetNbinsX()+1;i++){
	null_hyp->SetBinError(i,fabs(null_hyp->GetBinContent(i)-null_hyper->GetBinContent(i)));

    }
    double yDuke[20];
    double xDukeB[20] = {0.250E+00, 0.750E+00, 0.125E+01, 0.175E+01, 0.225E+01, 0.275E+01, 0.325E+01, 0.375E+01, 0.425E+01, 0.475E+01, 0.525E+01, 0.575E+01, 0.625E+01, 0.675E+01, 0.725E+01, 0.775E+01, 0.825E+01, 0.875E+01, 0.925E+01, 0.975E+01};
    double yDukeB[20] = {0.952E+00, 0.960E+00, 0.943E+00, 0.964E+00, 0.107E+01, 0.112E+01, 0.109E+01, 0.105E+01, 0.982E+00, 0.897E+00, 0.848E+00, 0.815E+00, 0.759E+00, 0.725E+00, 0.721E+00, 0.683E+00, 0.642E+00, 0.637E+00, 0.623E+00, 0.602E+00};
    double yDukeD[20] = {0.740E+00, 0.803E+00, 0.102E+01, 0.850E+00, 0.692E+00, 0.591E+00, 0.535E+00, 0.474E+00, 0.482E+00, 0.471E+00, 0.461E+00, 0.477E+00, 0.459E+00, 0.464E+00, 0.454E+00, 0.450E+00, 0.423E+00, 0.478E+00, 0.445E+00, 0.439E+00};
    TGraphErrors * NColl = new TGraphErrors();        
    NColl->SetPoint(0,8.25,1);
    NColl->SetPointError(0,0.1,0.08);
    NColl->SetFillColor(38);
    NColl->SetLineColor(38);
    TGraph * gDukeB = new TGraph();//20,xDukeB,yDukeB);
    gDukeB->SetLineStyle(3);
    gDukeB->SetLineWidth(2);
    TGraph * gDukeC = new TGraph();//20,xDukeB,yDukeD);
    gDukeC->SetLineColor(kRed);
    gDukeC->SetLineStyle(3);
    gDukeC->SetLineWidth(2);
    TGraph * duke_ratio = new TGraph();
    duke_ratio->SetLineStyle(3);
    getData(gDukeB,"RAA_b2e_cen-00-80.dat");
    getData(gDukeC,"RAA_c2e_cen-00-80.dat");
    for(int i = 0;i<gDukeB->GetN();i++){
	double x;double y;
	double x1;double y1;
	gDukeB->GetPoint(i,x,y);
	gDukeC->GetPoint(i,x1,y1);
	duke_ratio->SetPoint(i,x,y/y1);
    }
    TFile * npeRaa = new TFile("/gpfs01/star/pwg/mkelsey/forYifei/electronRAA/finalBtoERaa.root");
    TGraphErrors * gNpe = (TGraphErrors*)npeRaa->Get("gr_B_Raa_com_sts");
    TGraphErrors * gNpeSys = (TGraphErrors*)npeRaa->Get("gr_B_Raa_com_sys");
    TGraphErrors * gNpeSys2 = (TGraphErrors*)npeRaa->Get("gr_all_B_Npe_Raa_com_sys");
    TGraphErrors * gNpec = (TGraphErrors*)npeRaa->Get("gr_C_Raa_com_sts");
    TGraphErrors * gNpecSys = (TGraphErrors*)npeRaa->Get("gr_C_Raa_com_sys");
    TGraphErrors * gNpecSys2 = (TGraphErrors*)npeRaa->Get("gr_all_C_Npe_Raa_com_sys");



    TFile* fi11 = new TFile("../Run16/DCA_Fit/root/FracB.root");
    fb1 = (TH1F*)fi11->Get("fb");
    fb1->SetName("fb1");
    fb_sys1 = (TH1F*)fi11->Get("fb_sys");
    fb_sys1->SetName("fb_sys1");
    ratio2= (TGraphAsymmErrors *)fi11->Get("ratio");ratio2->SetName("ratio2");
    ratio_sys2= (TGraphAsymmErrors *)fi11->Get("ratio_sys");ratio_sys2->SetName("ratio2");

    gpp = (TGraphAsymmErrors *)fi11->Get("pp");gpp->SetName("gpp");
    gpp_sys= (TGraphAsymmErrors *)fi11->Get("pp_sys");gpp_sys->SetName("gpp_sys");
    TFile* fi = new TFile("../NPE_ANA/DCA_Fit/root/FracB.root");
    fb = (TH1F*)fi->Get("fb");
    fb_sys= (TH1F*)fi->Get("fb_sys");
    fb_sys->SetFillColor(kGray);
    FONLL =(TGraphErrors *)fi->Get("FONLL");
    //pp = (TGraphAsymmErrors *)fi->Get("pp");
    //pp_sys=(TGraphAsymmErrors *)fi->Get("pp_sys");
    ratio1= (TGraphAsymmErrors *)fi->Get("ratio");ratio1->SetName("ratio1");
    ratio_sys1= (TGraphAsymmErrors *)fi->Get("ratio_sys");ratio_sys1->SetName("ratio1");
    //duke_ratio= (TGraph*)fi->Get("duke_ratio");
    //duke_ratio->SetLineStyle(3);
    double binningo[10]={0.6+0.2,1.+0.2,1.2+0.2,1.5+0.15,2.+0.15,2.5+0.15,3.5+0.15,4.5+0.15,5.5+0.15,8.5+0.15};
    double binning[10]={0.6,1.,1.2,1.5,2.,2.5,3.5,4.5,5.5,8.5};
    double binning1[10]={0.5,0.9,1.1,1.4,1.9,2.4,3.4,4.4,5.4,8.4};
    TH1F *errors_2014 = new TH1F("errors_2014","errors_2014",9,binning);
    TH1F *errors_2016 = new TH1F("errors_2016","errors_2016",9,binning);
    TH1F *fb11 = new TH1F("fb11","fb11",9,binning);
    TH1F *fb_sys11 = new TH1F("fb_sys11","fb_sys11",9,binning);
    TH1F *fb22 = new TH1F("fb22","fb22",9,binning1);
    TH1F *fb_sys22 = new TH1F("fb_sys22","fb_sys22",9,binning1);
    TH1F *b = new TH1F("b","b",9,binning);
    TH1F *b_sys = new TH1F("b_sys","fb_sys",9,binning);
    for(int i  =1 ;i<10;i++){
	fb11->SetBinContent(i,fb1->GetBinContent(i));
	fb_sys11->SetBinContent(i,fb1->GetBinContent(i));
	fb11->SetBinError(i,fb1->GetBinError(i));
	fb_sys11->SetBinError(i,fb_sys1->GetBinError(i));
	fb22->SetBinContent(i,fb->GetBinContent(i));
        fb_sys22->SetBinContent(i,fb->GetBinContent(i));
        fb22->SetBinError(i,fb->GetBinError(i));
        fb_sys22->SetBinError(i,fb_sys->GetBinError(i));
	if(i>4)	errors_2016->SetBinContent(i,fb1->GetBinError(i)/fb1->GetBinContent(i));
	if(i>4)errors_2014->SetBinContent(i,fb->GetBinError(i)/fb->GetBinContent(i));

    }
    getAverage(fb11,fb_sys11,fb22,fb_sys22,fb,fb_sys);
/*    for(int i  =5 ;i<10;i++){
	double w1 = fb22->GetBinError(i);
	double w2 = fb11->GetBinError(i);
	double s1 = fb_sys22->GetBinError(i);
	double s2 = fb_sys11->GetBinError(i);
	double cen1 = fb22->GetBinContent(i);
	double cen2 = fb11->GetBinContent(i);
	double w11 = sqrt(w1*w1+s1*s1);
	double w22 = sqrt(w2*w2+s2*s2);
	double val = (cen1/w11/w11+cen2/w22/w22)/(1/w11/w11+1/w22/w22);
	double sys = sqrt(1/(1/w11/w11+1/w22/w22)-1/(1/w1/w1+1/w2/w2));
	fb->SetBinContent(i,val);
	fb->SetBinError(i,1/sqrt(1/w1/w1+1/w2/w2));
	fb_sys->SetBinContent(i,val);
	fb_sys->SetBinError(i,sys);
	cout <<"Bin " << i << " stats (comb,14,16) " << 1/sqrt(1/w1/w1+1/w2/w2) << " " << w1 << " " <<w2 << " sys (c,14,16) " << sys << " " << s1 << " " << s2 << endl;
	}*/
    TGraphErrors* gb_sys = new TGraphErrors();
    for(int i =5;i<10;i++){
	gb_sys->SetPoint(i-5,fb_sys->GetBinCenter(i),fb_sys->GetBinContent(i));
	gb_sys->SetPointError(i-5,0,fb_sys->GetBinError(i));
       
    }



    fb11->SetMarkerColor(kRed);
    fb11->SetLineColor(kRed);
    fb11->SetMarkerStyle(28);  
    fb_sys11->SetMarkerColor(kRed);
    fb_sys11->SetLineColor(kRed);
    fb_sys11->SetMarkerStyle(28);
    fb_sys11->SetFillColor(kRed);
    fb_sys11->SetFillStyle(3004);
    fb22->SetMarkerColor(kGreen-2);
    fb22->SetLineColor(kGreen-2);
    fb22->SetMarkerStyle(25);
    fb_sys22->SetMarkerColor(kGreen-2);
    fb_sys22->SetLineColor(kGreen-2);
    fb_sys22->SetMarkerStyle(26);
    fb_sys22->SetFillColor(kGreen-2);
    fb_sys22->SetFillStyle(3005);
    FONLL->SetLineStyle(7);
    TPaveText *Namer = new TPaveText(0.52,0.23,0.86,0.31,"BRNDC");
    Namer->AddText("STAR Preliminary 0-80%");
    Namer->SetFillColorAlpha(0, 0);
    Namer->SetTextAlign(12);
    Namer->SetBorderSize(0);
    gpp->SetMarkerStyle(23);
    gpp->SetMarkerColor(kBlue);
    gpp->SetLineColor(kBlue);
    gpp_sys->SetMarkerStyle(23);
    gpp_sys->SetMarkerColor(kBlue);
    gpp_sys->SetLineColor(kBlue);
    gpp_sys->SetFillColor(kBlue);
    gpp_sys->SetFillColorAlpha(kBlue,0.5);
    gpp_sys->SetFillStyle(3004);

    TLegend *legr = new TLegend(0.164,0.733,0.55,0.9);
    legr->AddEntry(fb,"Au+Au #sqrt{s_{NN}} = 200 GeV","PE");
    //legr->AddEntry(fb22,"2014 Au+Au #sqrt{s_{NN}} = 200 GeV","PE");
    //legr->AddEntry(fb11,"2016 Au+Au #sqrt{s_{NN}} = 200 GeV","PE");
    legr->AddEntry(gpp,"#it{p}+#it{p} #sqrt{s} = 200 GeV","PE");
    legr->AddEntry(FONLL,"FONLL #it{p}+#it{p} #sqrt{s} = 200 GeV","L");
    TCanvas *errors = new TCanvas("errors","errors");
    errors_2016->SetLineColor(kRed);
    errors_2014->GetXaxis()->SetTitle("p_{T} (GeV/#it{c})");
    errors_2014->GetYaxis()->SetTitle("Relative Statistical Error");
    errors_2014->Draw("hist");
    //..errors_2016->Divide(errors_2014);
    errors_2016->Draw("same hist ");
    TCanvas *ccomp = new TCanvas("ccomp","comp");
    fb->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    fb->GetXaxis()->SetRangeUser(1.5,8);
    fb->Draw("PE X0");
    gb_sys->Draw("same []");
    //fb_sys11->Draw("same E2");
    //fb_sys22->Draw("same E2");
    fb->Draw("same E X0");
    //   fb11->Draw("same E1");
//    fb22->Draw("same E1");
    gpp->Draw("same EP");
    gpp_sys->Draw("same E2");
    FONLL->Draw("same l");
    Namer->Draw("same");
    legr->Draw("same");
    gPad->RedrawAxis();
    TCanvas *ccomp1 = new TCanvas("ccomp1","comp1");
    TFile* fi1 = new TFile("../NPE_ANA/NPE_RAA/NPE_RAA.root");
    raa_stat= (TGraphErrors*)fi1->Get("raa_stat");
    raa_sys= (TGraphErrors*)fi1->Get("raa_sys");
    TFile *input_Total_Raa=new TFile("../NPE_ANA/NPE_RAA/NPEHTRaa080-1.root","READ");
    TH1F *Npe_Raa_sts=(TH1F *) input_Total_Raa->Get("NPERaaStat_AuAu_0")->Clone("Npe_Raa_sts");
    TH1F *Npe_Raa_sys=(TH1F *) input_Total_Raa->Get("NPERaaSys_AuAu_0")->Clone("Npe_Raa_sys");
    /*  double yy[5] =   {0.202692307692308,0.280,
                      0.385,
                      0.514,
                      0.589};
    double ee1[5] =  {0.0492769230769231,0.049,
                      0.051,
                      0.046,
                      0.051};
    double ee2l[5] = {0,0.026,
                      0.026,
                      0.027,
                      0.051};
    double ee2h[5] = {0,0.024,
                      0.040,
                      0.035,
                      0.033};
*/
//Run12 only
    /*
    double yy[5] =   {0,0.20983,
		      0.334,
		      0.5235,
6.0E-01};
    double ee1[5] =  {0.0492769230769231,0.084,
		      0.08133,
		      0.05333,
		      8.1E-02};
    double ee2l[5] = {0,0.01866,
		      0.01733,
		      0.012,
		      1.8E-02};
    double ee2h[5] = {0,0.02534,
		      0.01867,
		      0.01333,
		      1.7E-02};
    */
/*
//Syst weighted average
    double yy[5] = {0,0.278,0.378,
		    0.518,
		    0.592};
    double ee1[5] =  {0.0492769230769231,0.049,
                      0.051,
                      0.046,
                      0.051};
    double ee2l[5] = {0,0.0158619952653678,
		      0.0152515906304403,
		      0.0118489795136407,
		      0.0170691654177216};
    double ee2h[5] = {0,0.0171916756043786,
		      0.0176632910273331,
		      0.0132199164080194,
		      0.0158509466011957};
    
    double xx2[5] =   {2.25,3,4,5,7};
    double xxe[5] =   {0,0,0,0,0};
*/
//proper asym method  

    double yy[5] = {0,0.278118,0.375476,0.516407,0.582087};
    double ee1[5] =  {0,0.0490242,0.0514371,0.0464319,0.0500347};
    double ee2l[5] = {0,0.0191004,0.0260739,0.0199185,0.0316827};
    double ee2h[5] = {0,0.0191004,0.0260739,0.0199185,0.0316827};

    double xx2[5] =   {2.25,3,4,5,7};
    double xxe[5] =   {0,0,0,0,0};


    TGraphAsymmErrors *pp = new TGraphAsymmErrors(5,xx2,yy,xxe,xxe,ee1,ee1);
    TGraphAsymmErrors *pp_sys = new TGraphAsymmErrors(5,xx2,yy,xxe,xxe,ee2l,ee2h);
    double mybin[6]={2.25,2.5,3.5,4.5,5.5,8.5};
    TH1F *check = new TH1F("check","",4,mybin);
    //TH1F *raa_c = new TH1F("raa_c","",4,mybin);

    TH1F *ratio = new TH1F("ratio","ratio",9,binning);
    TGraphAsymmErrors *ratio_sys = new TGraphAsymmErrors();
    TGraphAsymmErrors *ratio_sys_pp = new TGraphAsymmErrors();
    TGraphAsymmErrors *ratio_sys_AA = new TGraphAsymmErrors();
    int cnt = 0;
    double summ=0;
    double arr[4];
    for(int i= 5 ; i<9; i++){
        double tmp1 = fb->GetBinContent(i+1);//+h_ave_sys->GetBinError(i+1);                                                                                                                                                                  
        double err1 =  fb->GetBinError(i+1);
        double err2 =  fb_sys->GetBinError(i+1);
        double tmp2 = yy[i-4];//+ee2h[i];                                                                                                                                                                                                          
        double err3 = ee1[i-4];
        double err4l = ee2l[i-4];
        double err4h = ee2h[i-4];
        double val = (1/tmp2-1)/(1/tmp1-1);
        if(tmp1>0 && tmp2>0){
            double error_st = val*sqrt(err1 * err1 /tmp1/tmp1/(tmp1-1)/(tmp1-1)
				       + err3 * err3/tmp2/tmp2/(tmp2-1)/(tmp2-1));
            double error_sy1 = val*sqrt(err2 * err2 /tmp1/tmp1/(tmp1-1)/(tmp1-1)
					+ err4l * err4l/tmp2/tmp2/(tmp2-1)/(tmp2-1));
            double error_sy2 = val*sqrt(err2 * err2 /tmp1/tmp1/(tmp1-1)/(tmp1-1)
                                        + err4h * err4h/tmp2/tmp2/(tmp2-1)/(tmp2-1));
            double error_sy11 = val*sqrt(err2 * err2 /tmp1/tmp1/(tmp1-1)/(tmp1-1));
            double error_sy21 = val*sqrt(err2 * err2 /tmp1/tmp1/(tmp1-1)/(tmp1-1));
            double error_sy12 = val*sqrt(err4l * err4l /tmp1/tmp1/(tmp1-1)/(tmp1-1));
            double error_sy22 = val*sqrt(err4h * err4h /tmp1/tmp1/(tmp1-1)/(tmp1-1));
            //ratio->SetPoint(cnt,h_ave->GetBinCenter(i+1),val);
            //ratio->SetPointError(cnt,0,0,error_st,error_st);
            if(i<9)ratio->SetBinContent(i+1,val);//-error_sy2);
	    if(i<9)ratio->SetBinError(i+1,error_st);
	    ratio_sys->SetPoint(cnt,fb->GetBinCenter(i+1),val);
            ratio_sys->SetPointError(cnt,0,0,error_sy1,error_sy2);
	    ratio_sys_pp->SetPoint(cnt,fb->GetBinCenter(i+1),val);
            ratio_sys_pp->SetPointError(cnt,0,0,error_sy11,error_sy11);
	    ratio_sys_AA->SetPoint(cnt,fb->GetBinCenter(i+1),val);
            ratio_sys_AA->SetPointError(cnt,0,0,error_sy22,error_sy22);

	    cnt++;
	    
	    double null = 1;//null_hyp_bin->GetBinContent(i+1);
	    double nuller = null_hyp_biner->GetBinContent(i+1);
	    double null_er = 0;//fabs(null-nuller);
	    summ+=(val-null)*(val-null)/(error_st*error_st+null_er*null_er+error_sy2*error_sy2);
	    arr[i-5] = val-null;
	    cout <<"Summing here "<< summ << endl;
	}
    }
    arr[3]=0;
//    arr[2]=0;
    double format3[100];
    cout << "Array values " << arr[0] << " " << arr[1] << " "<< arr[2] << " "<< arr[3] << " " <<endl;
    TVectorD const dat_arr(4,arr);

    for(int i= 0 ; i<4 ;i++){
	for(int j= 0 ; j<=i; j++){
	    double stati = ratio->GetBinError(i+6);
	    double systi = ratio_sys->GetErrorYlow(i);
	    double systj = ratio_sys->GetErrorYlow(j);
	    double null = null_hyp_bin->GetBinContent(i+6);
            double nuller = null_hyp_biner->GetBinContent(i+6);
            double null_er = 0;//fabs(null-nuller);
	    double systi1 = ratio_sys_pp->GetErrorYlow(i);
            double systj1 = ratio_sys_pp->GetErrorYlow(j);
	    double systi2 = ratio_sys_AA->GetErrorYlow(i);
            double systj2 = ratio_sys_AA->GetErrorYlow(j);
	    if(i==j){
		format3[i+j*4]= stati*stati+systi*systi+null_er*null_er;
		cout << "Sanity check << " << stati << " " << systi << " " << null_er << " " << 1/(stati*stati+systi*systi+null_er*null_er) << " " << arr[i] << " " << arr[i]*arr[i] <<  endl;
	    }

	    else if(fabs(i-j)==1) format3[i+j*4]= 0.25*systi1*systj1+0.25*systi2*systj2;
	    else  format3[i+j*4]= 0;//.2*systi*systj;
	}
    }
    dat_arr.Print();
    cout << "Array values1 " << arr[0] << " " << arr[1] << " "<< arr[2] << " "<< arr[3] << " " <<endl;

    TF1 *fit = new TF1("fit","[0]",1,10);
    TH1F * spread1 = new TH1F("spread1","spread1",200,0,5);
    TH1F * spread2 = new TH1F("spread2","spread2",200,0,5);
    ratio->Fit("fit");

    TF1 func("func","gaus(0)",-10,10);
    func.SetParameter(0,1);
    func.SetParameter(1,0);
    func.SetParameter(2,1);
    func.SetParameter(0,1/func.Integral(-100,100));
    double format1[100];
    double format2[100];
    
    cout << "filling matrices " << endl;
    for(int i= 0 ; i<4; i++){
        for(int j= 0 ; j<=i; j++){
            double temp1i = fb_sys->GetBinError(i+1+5);
            double temp1j = fb_sys->GetBinError(j+1+5);
            double temp11i = fb->GetBinError(i+1+5);
            double temp11j = fb->GetBinError(j+1+5);
            if(ee2l[i+1]>=ee2h[i+1])double temp2i =ee2l[i+1];
            else  double temp2i =ee2h[i+1];
            if(ee2l[j+1]>=ee2h[j+1])double temp2j =ee2l[j+1];
            else  double temp2j =ee2h[j+1];
            double temp22i =ee1[i+1];
            double temp22j =ee1[j+1];
            if(i==j){
                format1[i+j*4] = temp1i*temp1j;// + temp11i*temp11j;                                                                                                                       
                format2[i+j*4] = temp2i*temp2j;// + temp22i*temp22j;                                                                                                                                
	    }else if(fabs(i-j)==1){

		format1[i+j*4] = temp1i*temp1j*0.25;
                format2[i+j*4] = temp2i*temp2j*0.25;
	    }
	    else{
		format1[i+j*4] = 0;//temp1i*temp1j*0.5;
                format2[i+j*4] = 0;//temp2i*temp2j*0.5;

	    }
        }
    }
    for(int i=0; i<4; ++i) {
        for(int j=0; j<i; ++j) {
            format1[i*4+j]=format1[i+j*4];
            format2[i*4+j]=format2[i+j*4];
	    format3[i*4+j]=format3[i+j*4];
        }
    }
    TMatrixD const mat1(4,4,format1);
    TMatrixD const mat2(4,4,format2);
    TMatrixD const mat3(4,4,format3);
    mat3.Print();
    double det = mat3.Determinant();
    TMatrixD const inv_mat = mat3.Invert();
    inv_mat.Print();
    cout << " Determinant " << det << endl;
    double chi2 = dat_arr * (inv_mat*dat_arr);
    TDecompChol chol1(mat1);
    TDecompChol chol2(mat2);
    TF1 *fit1 = new TF1("fit1","[0]",1,10);
    TF1 *fit2 = new TF1("fit2","[0]",1,10);

    if(chol1.Decompose()){
        TMatrixD dec11 = chol1.GetU();
        TMatrixD dec1(TMatrix::kTransposed,dec11);
        dec1.Print();
    }
    if(chol2.Decompose()){
        TMatrixD dec22 = chol2.GetU();
        TMatrixD dec2(TMatrix::kTransposed,dec22);
        dec2.Print();
    }
    for(int i = 0; i<1;i++){
        TGraphAsymmErrors *raa1 = new TGraphAsymmErrors();
        TGraphAsymmErrors *raa2 = new TGraphAsymmErrors();
        double sig1 = func.GetRandom();
        double sig2 = func.GetRandom();

        int cnt = 0 ;
        for(int j= 5 ; j<9; j++){
            double tmp1 = fb->GetBinContent(j+1);
            double err1 =  fb->GetBinError(j+1);
            double err2 =  fb_sys->GetBinError(j+1);
            double tmp2 = yy[j-4];
            double err3 = ee1[j-4];
            double err4l = ee2l[j-4];
            double err4h = ee2h[j-4];

            double shift1 = func.GetRandom()*dec1[j-5][0]+func.GetRandom()*dec1[j-5][1]+func.GetRandom()*dec1[j-5][2]+func.GetRandom()*dec1[j-5][3];
            double shift2 = func.GetRandom()*dec2[j-5][0]+func.GetRandom()*dec2[j-5][1]+func.GetRandom()*dec2[j-5][2]+func.GetRandom()*dec2[j-5][3];
            if(tmp1>0 && tmp2>0){
                double pert1 = shift1;//err2*sig1;                                                                                                                                                                                               
                if(sig2>0)double pert2 = shift2;//err4h*sig2;                                                                                                                                                                                    
                if(sig2<0)double pert2 = shift2;//err4l*sig2;                                                                                                                                                                                    
                double valy1 = (1/(tmp2+pert2)-1)/(1/(tmp1+pert1)-1);
                double valy2 = (1/(tmp2+pert2)-1)/(1/(tmp1)-1);
                double stat1 = valy1*sqrt(err1 * err1 /(tmp1+pert1)/(tmp1+pert1)/((tmp1+pert1)-1)/((tmp1+pert1)-1)
                                          + err3 * err3/(tmp2+pert2)/(tmp2+pert2)/((tmp2+pert2)-1)/((tmp2+pert2)-1));
                double stat2 = valy2*sqrt(err1 * err1 /tmp1/tmp1/(tmp1-1)/(tmp1-1)
                                          + err3 * err3/(tmp2+pert2)/(tmp2+pert2)/((tmp2+pert2)-1)/((tmp2+pert2)-1));
                raa1->SetPoint(cnt,fb->GetBinCenter(j+1),valy1);
                raa1->SetPointError(cnt,0,0,stat1,stat1);
                raa2->SetPoint(cnt,fb->GetBinCenter(j+1),valy2);
                raa2->SetPointError(cnt,0,0,stat2,stat2);
                cnt++;
            }
	}
        raa1->Fit(fit1);
        raa2->Fit(fit2);
        spread1->Fill(fit1->GetParameter(0));
        spread2->Fill(fit2->GetParameter(0));
        raa1->Delete();
        raa2->Delete();

    }
    TLegend *legg = new TLegend(0.201,0.754,0.596,0.902);
    double vall = fit->GetParameter(0);
    double errr = fit->GetParError(0);
    double erh = 0.51;
    double erl = 0.48;
    TCanvas *cspread = new TCanvas("cspread","");
    //spread->Fit("gaus");                                                                                                                                                                                                                       
    TF1 func2("func2","gaus(0)",0,vall);
    func2.SetParameter(0,100);
    func2.SetParameter(1,1.86);
    func2.SetParameter(2,0.4);
    TF1 func22("func22","gaus(0)",vall,10);
    func22.SetParameter(0,100);
    func22.SetParameter(1,1.86);
    func22.SetParameter(2,0.4);
    TF1 func1("func1","gaus(0)",0,vall);
    func1.SetParameter(0,100);
    func1.SetParameter(1,1.86);
    func1.SetParameter(2,0.4);
    TF1 func11("func11","gaus(0)",vall,10);
    func11.SetParameter(0,100);
    func11.SetParameter(1,1.86);
    func11.SetParameter(2,0.4);
    spread1->Fit("func2","R");
    spread1->Fit("func22","R");
    spread2->Fit("func1","R");
    spread2->Fit("func11","R");
    spread1->Draw("PE");
    spread2->SetLineColor(kRed);
    func2.SetLineColor(kBlue);
    func22.SetLineColor(kCyan);
    //spread2->Draw("same PE");                                                                                                                                                                                                                  
    func2.Draw("same l");
    func22.Draw("same l");
    erl =sqrt(func2.GetParameter(2)*func2.GetParameter(2));//func1.GetParameter(2)*func1.GetParameter(2) +                                                                                                                                       
    erh =sqrt(func22.GetParameter(2)*func22.GetParameter(2));//                                                                                                                                                                                  
    char label[100];
    sprintf(label,"%1.2f #pm% 1.2f(stat.) ^{+%1.2f}_{-%1.2f}(syst.)",vall,errr,erh,erl);
    cout << "fit result " << label << endl;

    //TGraphAsymmErrors * raa_b = new TGraphAsymmErrors();
    //TGraphAsymmErrors * raa_c =new TGraphAsymmErrors();
    TH1F* raa_c =new TH1F("raa_c","raa_c",9,binning);
    TH1F* raa_b =new TH1F("raa_b","raa_b",9,binning);
    TH1F* raa_c_old =new TH1F("raa_c_old","raa_c_old",9,binningo);
    TH1F* raa_b_old =new TH1F("raa_b_old","raa_b_old",9,binningo);
	
    
    TGraphAsymmErrors * raa_b_s = new TGraphAsymmErrors();
    TGraphAsymmErrors * raa_c_s =new TGraphAsymmErrors();
    TGraphAsymmErrors * raa_b_s2 = new TGraphAsymmErrors();
    TGraphAsymmErrors * raa_c_s2 =new TGraphAsymmErrors();
    double vals[4];
    double total[4];
    double totalsys[4];
    double totalc[4];
    double totalsysc[4];
    for( int i = 2; i<6;i++){
	double temp1 = fb->GetBinContent(i+4);//binning starts low
	double er1 = fb->GetBinError(i+4);//binning starts low     
	double temp2 = 0;double temp3=0;
	pp->GetPoint(i-1,temp3,temp2);
	double er2h = pp->GetErrorYhigh(i-1);
	double er2l = pp->GetErrorYlow(i-1);
	double r = 0 ;double x = 0;
	double r_e;
	//raa_stat->GetPoint(i,x,r);
	//r_e = raa_stat->GetErrorY(i);
	r=Npe_Raa_sts->GetBinContent(i-1);
	r_e = Npe_Raa_sts->GetBinError(i-1);
	cout << "checking bins " << fb->GetBinCenter(i+4) << " " << temp3 << " " << x << " vals " << temp1 << " " << temp2 << " " << r << " " <<endl;
	double bval = temp1/(temp2) * r;
	double cval = (1-temp1)/(1-temp2)*r;
	
//	raa_b->SetPoint(i-2,fb->GetBinCenter(i+4),bval);
	raa_b->SetBinContent(i+4,bval);
	
	raa_b_s->SetPoint(i-2,fb->GetBinCenter(i+4),bval);
	raa_b_s2->SetPoint(i-2,fb->GetBinCenter(i+4),bval);
//	raa_c->SetPoint(i-2,fb->GetBinCenter(i+4),cval);
	raa_c->SetBinContent(i+4,cval);

	raa_c_s->SetPoint(i-2,fb->GetBinCenter(i+4),cval);
	raa_c_s2->SetPoint(i-2,fb->GetBinCenter(i+4),cval);
	vals[i-2] = bval;
	double low1 = bval*sqrt(er1*er1/temp1/temp1 + er2l*er2l/temp2/temp2);// + r_e*r_e/r/r);
	double high1 = bval*sqrt(er1*er1/temp1/temp1 + er2h*er2h/temp2/temp2);// + r_e*r_e/r/r);
	double low2 = cval*sqrt(er1*er1/temp1/temp1 + er2l*er2l/temp2/temp2);// + r_e*r_e/r/r);
	double high2 = cval*sqrt(er1*er1/temp1/temp1 + er2h*er2h/temp2/temp2);// + r_e*r_e/r/r);
	double sss = r_e*r_e/r/r;
	//raa_b->SetPointError(i-2,0,0,low1,high1);
	//raa_c->SetPointError(i-2,0,0,low2,high2);
	raa_b->SetBinError(i+4,low1);
	raa_c->SetBinError(i+4,low2);

	total[i-2]=bval*sqrt(er1*er1/temp1/temp1 + er2h*er2h/temp2/temp2 + r_e*r_e/r/r);

	er1 = fb_sys->GetBinError(i+4);
        er2h = pp_sys->GetErrorYhigh(i-1);
	er2l = pp_sys->GetErrorYlow(i-1);
	//r_e = raa_sys->GetErrorY(i);
	r_e = Npe_Raa_sys->GetBinError(i-1);
	low1 = bval*sqrt(er1*er1/temp1/temp1 + er2l*er2l/temp2/temp2);// + r_e*r_e/r/r);
	high1 = bval*sqrt(er1*er1/temp1/temp1 + er2h*er2h/temp2/temp2);// + r_e*r_e/r/r);
        low2 = cval*sqrt(er1*er1/temp1/temp1 + er2l*er2l/temp2/temp2);// + r_e*r_e/r/r);
        high2 = cval*sqrt(er1*er1/temp1/temp1 + er2h*er2h/temp2/temp2);// + r_e*r_e/r/r);
	raa_b_s->SetPointError(i-2,0,0,low1,high1);
        raa_c_s->SetPointError(i-2,0,0,low2,high2);
        check->SetBinContent(i-1,bval/cval);
	totalsys[i-2] = bval*sqrt(er1*er1/temp1/temp1 + er2h*er2h/temp2/temp2 + r_e*r_e/r/r);
	low1 = bval*sqrt(sss + r_e*r_e/r/r);                                                                                        
        high1 = bval*sqrt(sss + r_e*r_e/r/r);
        low2 = cval*sqrt(sss + r_e*r_e/r/r);
        high2 = cval*sqrt(sss + r_e*r_e/r/r);

	raa_b_s2->SetPointError(i-2,0.05,0.05,low1,high1);
        raa_c_s2->SetPointError(i-2,0.05,0.05,low2,high2);
	check->SetBinContent(i-1,bval/cval);
    }
    gNpe->SetMarkerStyle(25);
    gNpec->SetMarkerStyle(26);
    gNpeSys->SetMarkerStyle(25);
    gNpecSys->SetMarkerStyle(26);
    gNpeSys2->SetMarkerStyle(25);
    gNpecSys2->SetMarkerStyle(26);
    //gNpe->SetMarkerSize(2.2);                                                                                                                                                                        
    //gNpec->SetMarkerSize(2.);                                                                                                                                                                        
    gNpe->SetLineWidth(2);
    gNpec->SetLineWidth(2);
    gNpeSys->SetLineWidth(2);
    gNpecSys->SetLineWidth(2);
//    gNpeSys->SetMarkerSize(2.2);                                                                                                                                                                     
    //  gNpecSys->SetMarkerSize(2.);                                                                                                                                                                   
    gNpeSys2->SetLineColorAlpha(1,0.2);
    gNpecSys2->SetLineColorAlpha(1,0.2);
    gNpeSys2->SetLineWidth(8);
    gNpecSys2->SetLineWidth(8);
    gNpeSys2->SetLineColor(kBlue);
    gNpeSys->SetLineColor(kBlue);
    gNpe->SetLineColor(kBlue);
    gNpeSys2->SetMarkerColor(kBlue);
    gNpeSys2->SetFillColor(kGray);
    gNpeSys->SetFillColor(kBlue);
    gNpeSys->SetFillStyle(3005);

    gNpeSys->SetMarkerColor(kBlue);
    gNpe->SetMarkerColor(kBlue);
    gNpecSys2->SetLineColor(kGreen-2);
    gNpecSys->SetLineColor(kGreen-2);
    gNpec->SetLineColor(kGreen-2);
    gNpecSys2->SetMarkerColor(kGreen-2);
    gNpecSys2->SetFillColor(kGray);
    gNpecSys->SetFillColor(kGreen-2);
    gNpecSys->SetFillStyle(3004);
    gNpecSys->SetMarkerColor(kGreen-2);
    gNpec->SetMarkerColor(kGreen-2);
    raa_c->SetLineColor(kRed);
    raa_c->SetMarkerColor(kRed);
    raa_c->SetMarkerStyle(33);
    raa_c_s->SetLineColor(kRed);
    raa_c_s->SetMarkerColor(kRed);
    raa_c_s->SetMarkerStyle(1);
    raa_c_s->SetFillColor(kRed-3);
    raa_c_s->SetFillStyle(3005);
    raa_b_s->SetFillStyle(3004);
    raa_b_s->SetMarkerStyle(1);
    raa_c_s->SetMarkerSize(3);
    raa_b_s->SetMarkerSize(3);
    raa_c_s2->SetLineColor(kRed);
    raa_c_s2->SetMarkerColor(kRed);
    raa_c_s2->SetMarkerStyle(24);
    raa_c_s2->SetFillColor(kGray);
    raa_c_s2->SetFillStyle(1000);
    raa_b_s2->SetFillColor(kGray);                                                                                                                                              
    raa_b_s2->SetFillStyle(1000);
    ratio->GetXaxis()->SetRangeUser(2,8.5);

    raa_b->GetXaxis()->SetRangeUser(2,8.5);
    raa_b->GetYaxis()->SetRangeUser(0,2);
    raa_b->GetYaxis()->SetTitle("R_{AA}");
    raa_b->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    raa_b->GetYaxis()->SetTitleSize(0.09);
    raa_b->GetYaxis()->SetTitleOffset(0.53);
    TF1 *line = new TF1("line","1",-100,100);
    line->SetLineStyle(7);

    TLegend *leg = new TLegend(0.5,0.55,0.7,0.9);
    leg->SetTextSize(0.04);
    leg->AddEntry(raa_b,"#it{b}#rightarrow#it{e}","PE");
    leg->AddEntry(raa_c,"#it{c}#rightarrow#it{e}","PE");
    TLegend *leg11 = new TLegend(0.77,0.8,0.95,0.93);
    TLegend *leg1 = new TLegend(0.65,0.55,0.9,0.9);
    leg1->SetTextSize(0.04);
    leg11->SetTextSize(0.08);
    leg11->AddEntry(gDukeB,"DUKE","L");
    leg1->AddEntry(gDukeB,"DUKE #it{b}#rightarrow#it{e}","L");
    leg1->AddEntry(gDukeC,"DUKE #it{c}#rightarrow#it{e}","L");
    //leg1->AddEntry(gNpe,"#it{b}#rightarrow#it{e} QM17","PE");
    //leg1->AddEntry(gNpec,"#it{c}#rightarrow#it{e} QM17","PE");    
    TPaveText *Name = new TPaveText(0.17,0.8,0.45,0.9,"BRNDC");
    Name->AddText("STAR Preliminary");
    Name->SetFillColorAlpha(0, 0);
    Name->SetTextAlign(12);
    Name->SetBorderSize(0);
    TPaveText *Name1 = new TPaveText(0.17,0.7,0.45,0.8,"BRNDC");
    Name1->AddText("Au+Au #sqrt{s_{NN}}=200 GeV");
    Name1->SetFillColorAlpha(0, 0);
    Name1->SetTextAlign(12);
    Name1->SetTextSize(0.05);
    Name1->SetBorderSize(0);
    TPaveText *Name2 = new TPaveText(0.17,0.63,0.45,0.7,"BRNDC");
    Name2->AddText("0-80%");
    Name2->SetFillColorAlpha(0, 0);
    Name2->SetTextAlign(12);
    Name2->SetTextSize(0.05);
    Name2->SetBorderSize(0);

    TCanvas *c1 = new TCanvas("c1","RAA",700,600);
    TPad *pad1 = new TPad("pad1","pad1",0.0,0.35,1.0,1.0);
    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.345);
    pad1->Draw();
    pad2->Draw();
    pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.08);
    pad2->SetTopMargin(0.015);
    pad2->SetBottomMargin(0.4);
    //pad2->SetBorderMode(0);
    pad1->SetBorderMode(0);
    pad1->cd();
//    raa_b->SetEndErrorSize(0);
    //  raa_c->SetEndErrorSize(0);
    // raa_b_s->SetEndErrorSize(2);
    //raa_c_s->SetEndErrorSize(2);
    
    raa_b->Draw("PE X0");
    raa_c->Draw("PE X0 same");
    raa_b_s2->Draw("same E2");
    raa_c_s2->Draw("same E2");
    raa_b->Draw("EP X0 same");
    raa_c->Draw("EP X0 same");
    line->Draw("same"); 
    gDukeB->Draw("same l ");
    gDukeC->Draw("same l ");
    Name->Draw("same");
    Name1->Draw("same");
    Name2->Draw("same");
    leg->Draw("same");
    leg1->Draw("same");
    gStyle->SetEndErrorSize(5);
    raa_b_s->Draw("same []");
    raa_c_s->Draw("same []");
    NColl->Draw("same 5");
    raa_b_old->SetMarkerStyle(25);
    raa_c_old->SetMarkerStyle(26);
    gNpeSys->SetMarkerStyle(25);
    gNpecSys->SetMarkerStyle(26);
    gNpeSys2->SetMarkerStyle(25);
    gNpecSys2->SetMarkerStyle(26);
    
    gNpeSys2->SetLineColorAlpha(1,0.2);
    gNpecSys2->SetLineColorAlpha(1,0.2);
    gNpeSys2->SetLineWidth(8);
    gNpecSys2->SetLineWidth(8);
    gNpeSys2->SetLineColor(kBlue);
    gNpeSys->SetLineColor(kBlue);
    raa_b_old->SetLineColor(kBlue);
    gNpeSys2->SetMarkerColor(kBlue);
    gNpeSys2->SetFillColor(kGray);
    gNpeSys->SetFillColor(kBlue);
    gNpeSys->SetFillStyle(3005);

    gNpeSys->SetMarkerColor(kBlue);
    raa_b_old->SetMarkerColor(kBlue);
    gNpecSys2->SetLineColor(kGreen-2);
    gNpecSys->SetLineColor(kGreen-2);
    raa_c_old->SetLineColor(kGreen-2);
    gNpecSys2->SetMarkerColor(kGreen-2);
    gNpecSys2->SetFillColor(kGray);
    gNpecSys->SetFillColor(kGreen-2);
    gNpecSys->SetFillStyle(3004);
    gNpecSys->SetMarkerColor(kGreen-2);
    raa_c_old->SetMarkerColor(kGreen-2);
    double totalold[4];
    double valsold[4];
    for (i=0;i<4;i++){
	totalold[i] = sqrt(gNpe->GetErrorY(i)*gNpe->GetErrorY(i)+gNpeSys->GetErrorY(i)*gNpeSys->GetErrorY(i)+gNpeSys2->GetErrorY(i)*gNpeSys2->GetErrorY(i));
        double _x;
	double _y;
	double _x1;
        double _y1;
	gNpe->GetPoint(i,_x,_y);
	gNpec->GetPoint(i,_x1,_y1);

	valsold[i]=_y;
	gNpec->SetPointError(i,0,gNpec->GetErrorY(i));
	gNpeSys2->SetPointError(i,0.07,gNpeSys2->GetErrorY(i));
	gNpecSys2->SetPointError(i,0.07,gNpecSys2->GetErrorY(i));
	gNpeSys->SetPointError(i,0.0,gNpeSys->GetErrorY(i));
	gNpecSys->SetPointError(i,0.0,gNpecSys->GetErrorY(i));
	gNpe->SetPoint(i,_x+0.1,_y);
	gNpec->SetPoint(i,_x+0.1,_y1);
        gNpeSys2->SetPoint(i,_x+0.1,_y);
        gNpecSys2->SetPoint(i,_x+0.1,_y1);
        gNpeSys->SetPoint(i,_x+0.1,_y);
        gNpecSys->SetPoint(i,_x+0.1,_y1);
	
	raa_b_old->SetBinContent(i+6,_y);
	raa_c_old->SetBinContent(i+6,_y1);
	raa_b_old->SetBinError(i+6,gNpe->GetErrorY(i));
	raa_c_old->SetBinError(i+6,gNpec->GetErrorY(i));

    }

    //gNpeSys2->Draw("same E2");
    //gNpecSys2->Draw("same E2");
    //gNpeSys->Draw("same []");
    //gNpecSys->Draw("same []");
    //raa_b_old->Draw("same pe X0");
    //raa_c_old->Draw("samep pe X0");

    gPad->RedrawAxis();
    pad2->cd();
    
    for (i=0;i<4;i++){
	cout <<"Total errors " << sqrt(total[i]*total[i]+totalsys[i]*totalsys[i])/vals[i] << " " << totalold[i]/valsold[i] << " " << fb->GetBinCenter(i+6) << " sigma from model " <<(gDukeB->Eval(fb->GetBinCenter(i+6))-vals[i])/sqrt(total[i]*total [i]+totalsys[i]*totalsys[i])<<" sigma from 1 " <<(1-vals[i])/sqrt(total[i]*total [i]+totalsys[i]*totalsys[i])<<endl;
    }
    null_hyp->SetLineStyle(8);
    null_hyp->SetLineColor(kBlue);
    
    TGraphErrors *nulll = new TGraphErrors();
    for(int i = 0;i<null_hyp->GetNbinsX();i++){

        nulll->SetPoint(i,null_hyp->GetBinCenter(i+1),null_hyp->GetBinContent(i+1));
        nulll->SetPointError(i,0,null_hyp->GetBinError(i+1));
    }
    nulll->SetLineColor(kBlue);
    nulll->SetFillColor(kBlue);
    nulll->SetFillStyle(3013);

    TLegend *legg = new TLegend(0.54,0.815,0.93,0.94);
    char label[100];
    sprintf(label,"Const.= %1.2f #pm% 1.2f(stat.) \#pm %1.2f(syst.)",1.95,0.28,0.24);
    TF1 *prox = new TF1("prox","1.95",-100,100);
    prox->SetLineColor(kBlue);
    prox->SetLineStyle(5);
    legg->AddEntry(prox,label,"l");
    ratio->GetYaxis()->SetTitle("R_{AA}^{b#rightarrow#it{e}}/R_{AA}^{c#rightarrow#it{e}}");
    ratio->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    ratio->GetYaxis()->SetRangeUser(0.5,3.3);
    ratio->SetTitle(0);
    ratio->GetYaxis()->SetTitleSize(0.12);
    ratio->GetYaxis()->SetLabelSize(0.1);
    ratio->GetYaxis()->CenterTitle();
    ratio->GetYaxis()->SetNdivisions(110);
    ratio->GetYaxis()->SetTitleOffset(0.35);
    ratio->GetXaxis()->SetTitleSize(0.15);
    ratio->GetXaxis()->SetLabelSize(0.14);
    ratio->GetXaxis()->SetTitleOffset(0.95);
    ratio_sys->SetFillColor(1);
    ratio_sys->SetFillStyle(3004);
    fit->SetLineColor(kCyan);
    fit->SetLineWidth(2);
    ratio->GetFunction("fit")->Delete();
    ratio->Draw("PE X0");
    nulll->DrawClone("same E3");
    nulll->SetFillStyle(3005);
    nulll->DrawClone("same E3");
    null_hyp->Draw("same hist");
    ratio_sys->Draw("same []");
    ratio->Draw("same PE X0");
//    fit->Draw("same l");
    duke_ratio->Draw("same");
    leg11->Draw("same");
    line->Draw("same");
    gPad->RedrawAxis();
    

    TLegend *leg111 = new TLegend(0.53,0.8,0.75,0.93);
    leg111->SetTextSize(0.08);
    leg111->AddEntry(nulll,"Null hyp.","lf");
    leg111->Draw("same");
    cout << "chi2 for ratio " << summ << " " << summ/3 << endl;
    cout << "chi2 using TMatrix " << chi2 << endl;
    c1->SaveAs("raa_v2.pdf");
}


void getAverage(TH1F *f1,TH1F *f1_sys, TH1F *f2, TH1F *f2_sys ,TH1F *have, TH1F *hsys){
    for(int i  =5 ;i<10;i++){                                                                                                                                                                                                                                    
        double w1 = f2->GetBinError(i);                                                                                                                                                                                                                         
        double w2 = f1->GetBinError(i);                                                                                                                                                                                                                         
        double s1 = f2_sys->GetBinError(i);                                                                                                                                                                                                                     
        double s2 = f1_sys->GetBinError(i);                                                                                                                                                                                                                     
        double cen1 = f2->GetBinContent(i);                                                                                                                                                                                                                     
        double cen2 = f1->GetBinContent(i);                                                                                                                                                                                                                    	
	double stat1 = sqrt(w1*w1);
        double stat2 = sqrt(w2*w2);

	double w11 = sqrt(w1*w1);                                                                                                                                                                                                                           
        double w22 = sqrt(w2*w2);                                                                                                                                                                                                                         
  
        double val = (cen1/w11/w11+cen2/w22/w22)/(1/w11/w11+1/w22/w22);                                                                                                                                                                                           
        double sys = (s1/w11/w11+s2/w22/w22)/(1/w11/w11+1/w22/w22);
        if(i>5){
	    have->SetBinContent(i,val);                                                                                                                                                                                                                           
	    have->SetBinError(i,1/sqrt(1/w1/w1+1/w2/w2));                                                                                                                                                                                                         
	    hsys->SetBinContent(i,val);                                                                                                                                                                                                                           
	    hsys->SetBinError(i,sys);                                                                                                                                                                                                                            
	}
	else{
	    have->SetBinContent(i,cen1);
            have->SetBinError(i,w1);
            hsys->SetBinContent(i,cen1);
            hsys->SetBinError(i,s1);
	}
        cout <<"Bin " << i << " stats (comb,14,16) " << 1/sqrt(1/w1/w1+1/w2/w2) << " " << w1 << " " <<w2 << " sys (c,14,16) " << sys << " " << s1 << " " << s2 << endl;            
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
