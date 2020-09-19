void CharmV1(){
    gROOT->ProcessLine(".x ~/myStyle.C");
    gStyle->SetEndErrorSize(6);
    gStyle->SetMarkerSize(1.2);

    const int numEtaBins =4;
    double binning2[numEtaBins+1]={-0.8-0.03,-0.45-0.03,0,0.45+0.03,0.8+0.03};
    double binning1[numEtaBins+1]={-0.8,-0.35+0.03,0,0.35-0.03,0.8};
    double binning22[numEtaBins+1]={-0.8-0.01,-0.4-0.01,0,0.4+0.01,0.8+0.01};
    double binning11[numEtaBins+1]={-0.8+0.01,-0.4+0.01,0,0.4-0.01,0.8-0.01};
    double binningd0[numEtaBins+1]={-0.8+0.02,-0.4+0.02,0+0.02,0.4+0.02,0.8+0.02};

    double xt[6]  = {-1.25,-0.74,-0.25,0.25,0.75,1.25};
    double yd[6]  = {0.0199,0.0127,0.0054,-0.0056,-0.0128,-0.0200};
    double ydb[6]  = {0.0124,0.0099,0.0034,-0.0037,-0.0101,-0.0127};
    double ya[6]  = {0.0161,0.0113,0.0044,-0.0046,-0.0115,-0.0163};
    double ydi[6] ={0.0075,0.0029,0.0020,-0.0019,-0.0028,-0.0073};
    
    double xt1[8] = {-1.740,-1.248,-0.752,-0.251,0.251,0.747,1.243,1.759};
    double ya1[8] = {0.03871,0.03953,0.03041,0.01369,-0.00938,-0.02950,-0.03523,-0.02701};
    TGraph *gta = new TGraph(8,xt1,ya1);
    gta->SetLineColor(kMagenta);
    gta->SetLineWidth(2);
    TGraph *gtd = new TGraph(6,xt,yd);
    gtd->SetLineColor(kMagenta);
    //  gtd->SetLineStyle(8);
    TGraph *gtdb = new TGraph(6,xt,ydb);
    gtdb->SetLineColor(kCyan);
//    gtdb->SetLineStyle(9);
    TGraph *gtdif = new TGraph(6,xt,ydi);
    gtdif->SetLineColor(kMagenta);
    gtdif->SetLineWidth(2);
    TH1F *g1 = new TH1F("g1","g1",4,binningd0);
    double x1[4]={g1->GetBinCenter(1),g1->GetBinCenter(2),g1->GetBinCenter(3),g1->GetBinCenter(4)};
    double y1[4] = {0.069,0.018,-0.03,-0.025};
    double x1e[4] = {0,0,0,0};
    double x2e[4] = {0.0,0.0,0.0,0.0};
    double y1e[4] = {0.017,0.014,0.013,0.015};
    double y2e[4] = {0.015,0.012,0.012,0.013};
    //TGraphErrors *g1 = new TGraphErrors(4,x1,y1,x1e,y1e);
    TGraphErrors *g1_sys = new TGraphErrors(4,x1,y1,x2e,y2e);
    
    for(int i = 0;i<4;i++){
	g1->SetBinContent(i+1,y1[i]);
	g1->SetBinError(i+1,y1e[i]);
    }
    g1_sys->SetMarkerColor(kBlue);
    g1_sys->SetLineColor(kBlue);
    g1_sys->SetMarkerStyle(26);
    g1_sys->SetFillColor(kBlue);
    g1_sys->SetFillStyle(3004);
    g1->SetMarkerColor(kBlue);
    g1->SetLineColor(kBlue);
    g1->SetMarkerStyle(26);

    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};    
    TFile *fi1 = new TFile("../NPE_ANA/FitV1/2014_CharmV1.root");
    g14 = (TH1F *)fi1->Get("v1_2014");
    g14_p = (TH1F *)fi1->Get("v1_p_2014");
    g14_m = (TH1F *)fi1->Get("v1_m_2014");
    TFile *fi11 = new TFile("../NPE_ANA/FitV1/2014_CharmV1_Sys.root");
    g14_sys = (TH1F *)fi11->Get("v1_2014_sys");

    TFile *fi2 = new TFile("../Run16/FitV1/2016_CharmV1.root");
    g16 = (TH1F *)fi2->Get("v1_2016");
    g16_p = (TH1F *)fi2->Get("v1_p_2016");
    g16_m = (TH1F *)fi2->Get("v1_m_2016");
    TFile *fi22 = new TFile("../Run16/FitV1/2016_CharmV1_Sys.root");
    g16_sys = (TH1F *)fi22->Get("v1_2016_sys");

    double binning[numEtaBins+1]={-0.8,-0.4,0,0.4,0.8};
    TH1F *h14 = new TH1F("h14","h14",4,binning1);
    TH1F *h16 =new TH1F("h16","h16",4,binning2);
    TH1F *h14_p = new TH1F("h14_p","h14_p",4,binning1);
    TH1F *h16_p =new TH1F("h16_p","h16_p",4,binning2);
    TH1F *h14_m = new TH1F("h14_m","h14_m",4,binning11);
    TH1F *h16_m =new TH1F("h16_m","h16_m",4,binning22);
    TH1F *have =new TH1F("have","have",4,binning);
    TH1F *have1 =new TH1F("have1","have1",4,binning);
    TH1F *have2 =new TH1F("have2","have2",4,binning);
    TH1F *hdif =new TH1F("dif","hdif",4,binning);
    TH1F *have_p =new TH1F("have_p","have_p",4,binning2);
    TH1F *have_m =new TH1F("have_m","have_m",4,binning1);
    TH1F *have_p1 =new TH1F("have_p1","have_p1",4,binning);
    TH1F *have_m1 =new TH1F("have_m1","have_m1",4,binning);

    TGraphErrors *h14_sys = new TGraphErrors();
    TGraphErrors *h16_sys = new TGraphErrors();
    TGraphErrors *have_sys = new TGraphErrors();
    TGraphErrors *have_p_sys = new TGraphErrors();
    TGraphErrors *have_m_sys = new TGraphErrors();
    TGraphErrors *hdif_sys = new TGraphErrors();
    TGraphErrors *hdif_g = new TGraphErrors();
    TGraphErrors *hdif_g1 = new TGraphErrors();
    for(int i =1;i<4+1;i++){

	double c1 = g14->GetBinContent(i);
	double c2 = g16->GetBinContent(i);
	double e1 = g14->GetBinError(i);
        double e2 = g16->GetBinError(i);

	double s1 = g14_sys->GetBinContent(i);
	double s2 = g16_sys->GetBinContent(i);
	h14->SetBinContent(i,c1);
	h14->SetBinError(i,e1);
	h16->SetBinContent(i,c2);
	h16->SetBinError(i,e2);
	h14_sys->SetPoint(i-1,h14->GetBinCenter(i),c1);
	h16_sys->SetPoint(i-1,h16->GetBinCenter(i),c2);
	h14_sys->SetPointError(i-1,0.03,sqrt(s1*s1) );
	h16_sys->SetPointError(i-1,0.03,sqrt(s2*s2) );
    
	double val = (c1/e1/e1+c2/e2/e2)/(1/e1/e1+1/e2/e2);
	double err = sqrt(1/(1/e1/e1+1/e2/e2));
        double sys = (0.13*fabs(c1)/e1/e1+0.13*fabs(c2)/e2/e2)/(1/e1/e1+1/e2/e2);
	double sys2 = (s1/e1/e1+s2/e2/e2)/(1/e1/e1+1/e2/e2);

	have->SetBinContent(i,val);
	have->SetBinError(i,err);
	have_sys->SetPoint(i-1,have->GetBinCenter(i),val);
        have_sys->SetPointError(i-1,0.0,sqrt(sys*sys+sys2*sys2));	
	if(i<3){have1->SetBinContent(i,val+sqrt(sys*sys+sys2*sys2));
	    have1->SetBinError(i,err);
	    have2->SetBinContent(i,val-sqrt(sys*sys+sys2*sys2));
	    have2->SetBinError(i,err);
	}else{
	    have1->SetBinContent(i,val-sqrt(sys*sys+sys2*sys2));
            have1->SetBinError(i,err);
            have2->SetBinContent(i,val+sqrt(sys*sys+sys2*sys2));
            have2->SetBinError(i,err);
	}
    
    }
    for(int i =1;i<4+1;i++){

        double c1 = g14_m->GetBinContent(i);
        double c2 = g16_m->GetBinContent(i);
        double e1 = g14_m->GetBinError(i);
        double e2 = g16_m->GetBinError(i);
        double s1 = g14_sys->GetBinContent(i);
	double s2 = g16_sys->GetBinContent(i);
        h14_m->SetBinContent(i,c1);
        h14_m->SetBinError(i,e1);
        h16_m->SetBinContent(i,c2);
        h16_m->SetBinError(i,e2);

        double val = (c1/e1/e1+c2/e2/e2)/(1/e1/e1+1/e2/e2);
        double err = sqrt(1/(1/e1/e1+1/e2/e2));
        double sys = (0.13*fabs(c1)/e1/e1+0.13*fabs(c2)/e2/e2)/(1/e1/e1+1/e2/e2);
        double sys2 = (s1/e1/e1+s2/e2/e2)/(1/e1/e1+1/e2/e2);
	have_m->SetBinContent(i,val);
        have_m->SetBinError(i,err);
	have_m1->SetBinContent(i,val);
        have_m1->SetBinError(i,err);
	have_m_sys->SetPoint(i-1,have_m->GetBinCenter(i),val);
        have_m_sys->SetPointError(i-1,0.0,sqrt(sys*sys+sys2*sys2));
	cout << " e minus " << sys << endl;

    }
    for(int i =1;i<4+1;i++){
        double c1 = g14_p->GetBinContent(i);
        double c2 = g16_p->GetBinContent(i);
        double e1 = g14_p->GetBinError(i);
        double e2 = g16_p->GetBinError(i);
        double s1 = g14_sys->GetBinContent(i);
	double s2 = g16_sys->GetBinContent(i);
        h14_p->SetBinContent(i,c1);
        h14_p->SetBinError(i,e1);
        h16_p->SetBinContent(i,c2);
        h16_p->SetBinError(i,e2);

        double val = (c1/e1/e1+c2/e2/e2)/(1/e1/e1+1/e2/e2);
        double err = sqrt(1/(1/e1/e1+1/e2/e2));
        double sys = (0.13*fabs(c1)/e1/e1+0.13*fabs(c2)/e2/e2)/(1/e1/e1+1/e2/e2);
        double sys2 = (s1/e1/e1+s2/e2/e2)/(1/e1/e1+1/e2/e2);
	have_p->SetBinContent(i,val);
        have_p->SetBinError(i,err);
	have_p1->SetBinContent(i,val);
        have_p1->SetBinError(i,err);

	have_p_sys->SetPoint(i-1,have_p->GetBinCenter(i),val);
        have_p_sys->SetPointError(i-1,0.0,sqrt(sys*sys+sys2*sys2));
	cout <<" e plus " << 0.13*fabs(c1) << " " << 0.13*fabs(c2) << " " << sys << endl;

    }
    for(int i =1;i<4+1;i++){
	double cp = have_p->GetBinContent(i);
	double ep = have_p->GetBinError(i);
	double cm = have_m->GetBinContent(i);
	double em = have_m->GetBinError(i);
	double sp = have_p_sys->GetErrorY(i-1);
	double sm = have_m_sys->GetErrorY(i-1);

	hdif->SetBinContent(i,cp-cm);
	hdif->SetBinError(i,sqrt(ep*ep+em*em));
	hdif_sys->SetPoint(i-1,hdif->GetBinCenter(i),cp-cm);
        hdif_sys->SetPointError(i-1,0.03,sqrt(sp*sp-0.13*0.13*cp*cp+sm*sm-0.13*0.13*cm*cm));
	hdif_g->SetPoint(i-1,hdif->GetBinCenter(i),cp-cm);
        hdif_g->SetPointError(i-1,0.0,sqrt(ep*ep+em*em));
	if(i<3){
	    hdif_g1->SetPoint(i-1,hdif->GetBinCenter(i),cp-cm);//-sqrt(sp*sp-0.13*0.13*cp*cp+sm*sm-0.13*0.13*cm*cm));
	    hdif_g1->SetPointError(i-1,0.0,sqrt(sp*sp-0.13*0.13*cp*cp+sm*sm-0.13*0.13*cm*cm));//sqrt(ep*ep+em*em));

	}else{
	    hdif_g1->SetPoint(i-1,hdif->GetBinCenter(i),cp-cm);//+sqrt(sp*sp-0.13*0.13*cp*cp+sm*sm-0.13*0.13*cm*cm));
            hdif_g1->SetPointError(i-1,0.0,sqrt(sp*sp-0.13*0.13*cp*cp+sm*sm-0.13*0.13*cm*cm));//sqrt(ep*ep+em*em));

	}
    }

    h14->SetMarkerColor(kRed);
    h14->SetLineColor(kRed);
    h14->SetMarkerStyle(25);
    h16->SetMarkerColor(kBlue);
    h16->SetLineColor(kBlue);
    h16->SetMarkerStyle(26);
    h14_sys->SetMarkerColor(kRed);
    h14_sys->SetLineColor(kRed);
    h14_sys->SetMarkerStyle(25);
    h14_sys->SetFillColor(kRed);
    h14_sys->SetFillStyle(3004);
    h16_sys->SetMarkerColor(kBlue);
    h16_sys->SetLineColor(kBlue);
    h16_sys->SetMarkerStyle(26);
    h16_sys->SetFillColor(kBlue);
    h16_sys->SetFillStyle(3005);
    have_sys->SetFillColor(kGray);
    have_sys->SetFillStyle(1000);
    hdif_sys->SetFillColor(kGray);
    hdif_sys->SetFillStyle(1000);


    h14_m->SetMarkerColor(kRed);
    h14_m->SetLineColor(kRed);
    h14_m->SetMarkerStyle(25);
    h16_m->SetMarkerColor(kBlue);
    h16_m->SetLineColor(kBlue);
    h16_m->SetMarkerStyle(26);


    h14_p->SetMarkerColor(kMagenta);
    h14_p->SetLineColor(kMagenta);
    h14_p->SetMarkerStyle(27);
    h16_p->SetMarkerColor(kGreen-2);
    h16_p->SetLineColor(kGreen-2);
    h16_p->SetMarkerStyle(28);


    have_m->SetMarkerColor(kRed);
    have_m->SetLineColor(kRed);
    have_m->SetMarkerStyle(8);
    have_p->SetMarkerColor(kBlue);
    have_p->SetLineColor(kBlue);
    have_p->SetMarkerStyle(22);
    
    have_m_sys->SetMarkerColor(kRed);
    have_m_sys->SetLineColor(kRed);
    have_m_sys->SetMarkerStyle(8);
    have_m_sys->SetFillColor(kRed);
    have_m_sys->SetFillStyle(3005);
    have_p_sys->SetMarkerColor(kBlue);
    have_p_sys->SetLineColor(kBlue);
    have_p_sys->SetMarkerStyle(22);
    have_p_sys->SetFillColor(kBlue);
    have_p_sys->SetFillStyle(3004);
    
    TLegend *legt = new TLegend(0.67,0.19,0.93,0.24);
    legt->AddEntry(gta,"Hydro #it{D}^{0}","L");
    TLegend *legt1 = new TLegend(0.15,0.84,0.31,0.97);
    legt1->AddEntry(gtdif,"Hydro+EM #it{D}^{0}","L");
    //   legt1->AddEntry(gtdb,"Hydro.+EM #it{#bar{D}}^{0}","L");

    TF1 *line = new TF1("line","0",-100,100);
    line->SetLineStyle(7);
    TLegend *leg = new TLegend(0.6,0.7,0.9,0.9);
    leg->AddEntry(h14,"2014","PLE");
    leg->AddEntry(h16,"2016","PLE");
    TCanvas *c11 = new TCanvas("c11","c11");
    h14->GetYaxis()->SetRangeUser(-0.1,0.1);
    h14->GetYaxis()->SetTitle("<v_{1}>");
    h14->GetXaxis()->SetTitle("Rapidity");
    h14->Draw("PE X0");
    h14_sys->Draw("same E2");
    h16_sys->Draw("same E2");
    h14->Draw("same E1 X0");
    h16->Draw("same E1 X0");
    leg->Draw("same");
    line->Draw("same");
    gPad->RedrawAxis();
    TLegend *leg1 = new TLegend(0.7,0.65,0.9,0.8);
    leg1->AddEntry(have,"#it{c}#rightarrow #it{e}","PLE");
    leg1->AddEntry(g1,"STAR #it{D}^{0}","PLE");
    TCanvas *c22 = new TCanvas("c22","c22");
    
    TF1 *funcd0 = new TF1("funcd0","[0]*x",-0.8,0.8);
    funcd0->SetParameter(0,-0.08);
    funcd0->SetLineStyle(6);
    funcd0->SetLineColor(kBlue);
    g1->Fit("funcd0");
    funcd0->SetParameter(0,-0.08);
    TF1 *func = new TF1("func","[0]*x",-0.8,0.8);
    func->SetLineStyle(5);
    TF1 *func1 = new TF1("func1","[0]*x",-0.8,0.8);
    TF1 *func2 = new TF1("func2","[0]*x",-0.8,0.8);
    TF1 *func3 = new TF1("func3","[0]*x",-0.8,0.8);
    TF1 *func33 = new TF1("func33","[0]*x",-0.8,0.8);
    have->Fit("func");
    have1->Fit("func1");
    have2->Fit("func2");
    TLatex lat;
    have->GetYaxis()->SetRangeUser(-0.1,0.1);
    have->GetYaxis()->SetTitle("<v_{1}>");
    have->GetXaxis()->SetTitle("Rapidity");
    have->Draw("PE X0");
    gta->Draw("same l"); 
    have_sys->Draw("same ||");
    have->Draw("same PE X0");
    g1_sys->Draw("same []");
    g1->Draw("same PE X0");
    leg1->Draw("same");
    line->Draw("same");
    legt->Draw("same");

    lat.SetTextSize(0.04);
    lat.DrawLatex(-0.75,-0.063,"#it{p}_{T}^{e} > 1.2 GeV/#it{c}, <#it{p}_{T}^{e}> = 1.5 GeV/#it{c}");
    lat.DrawLatex(-0.75,-0.041,"10-80%");
    char label[100];
    char label1[100];
    char label2[100]="STAR Preliminary";;
    sprintf(label,"#it{e} dv_{1}/dy = %1.3f#pm%1.3f(stat.)#pm%1.3f(syst.)",func->GetParameter(0),func->GetParError(0),fabs(func->GetParameter(0)-func1->GetParameter(0)));
    sprintf(label1,"#it{D}^{0} dv_{1}/dy = -%1.3f#pm%1.3f(stat.)#pm%1.3f(syst.)",0.08,0.017,0.016);
    lat.SetTextSize(0.06); lat.DrawLatex(-0.75,0.-0.09,label2); lat.SetTextSize(0.04);
    lat.SetTextSize(0.04);
    lat.DrawLatex(-0.2,0.085,label);
    lat.DrawLatex(-0.2,0.075,label1);   
    
    gPad->RedrawAxis();


    TCanvas *c33 = new TCanvas("c33","c33");
    TLegend *leg2 = new TLegend(0.6,0.6,0.9,0.9);
    leg2->AddEntry(h14_m,"2014 e^{-}","PLE");
    leg2->AddEntry(h14_p,"2014 e^{+}","PLE");
    leg2->AddEntry(h16_m,"2016 e^{-}","PLE");
    leg2->AddEntry(h16_p,"2016 e^{+}","PLE");
    h14_m->GetYaxis()->SetRangeUser(-0.1,0.1);
    h14_m->GetYaxis()->SetTitle("<v_{1}>");
    h14_m->GetXaxis()->SetTitle("Rapidity");
    h14_m->Draw("PE X0");
    h16_m->Draw("same PE X0");
    h14_p->Draw("same PE X0");
    h16_p->Draw("same PE X0");
    leg2->Draw("same");
    line->Draw("same");


    func1->SetLineColor(kBlue);
    func1->SetLineStyle(3);
    func2->SetLineColor(kRed);
    func2->SetLineStyle(4);


    TCanvas *c44 = new TCanvas("c44","c44",700,600);
    TPad *pad1 = new TPad("pad1","pad1",0.0,0.35,1.0,1.0);
    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.35);
    pad1->Draw();
    pad2->Draw();
    pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.08);
    pad2->SetTopMargin(0.015);
    pad2->SetBottomMargin(0.4);
    //pad2->SetBorderMode(0);                                                                                                                                                                                                                    
    pad1->SetBorderMode(0);
    pad1->cd();

    TLegend *leg3 = new TLegend(0.7,0.65,0.9,0.8);
    have_p1->Fit("func1");
    have_m1->Fit("func2");

    leg3->AddEntry(have_p,"#it{c}#rightarrow#it{e^{+}}","PLE");
    leg3->AddEntry(have_m,"#bar{#it{c}}#rightarrow#it{e^{-}}","PLE");
    have_m->GetYaxis()->SetRangeUser(-0.09,0.09);
    
    have_m->GetXaxis()->SetRangeUser(-0.8,0.8);
    have_m->GetYaxis()->SetTitle("<v_{1}>");
    have_m->GetXaxis()->SetTitle("Rapidity");
    have_m->GetXaxis()->SetTitleOffset(0.53);
    have_m->GetXaxis()->SetLabelSize(0);
    have_m->Draw("PE X0");
    have_m_sys->Draw("same ||");
    have_m->Draw("same PE X0");
    have_p_sys->Draw("same ||");
    have_p->Draw("same PE X0");
    func1->Draw("same");func2->Draw("same");
    //gtd->Draw("same l");
    //gtdb->Draw("same l");
    line->Draw("same");
    leg3->Draw("same");
    lat.SetTextSize(0.06);
    lat.DrawLatex(-0.75,-0.057,"#it{p}_{T}^{e} > 1.2 GeV, <#it{p}_{T}^{e}> = 1.5 GeV/#it{c}");
    lat.DrawLatex(-0.75,-0.036,"10-80%");
    lat.SetTextSize(0.08); lat.DrawLatex(-0.75,0.-0.08,label2); lat.SetTextSize(0.06);
    sprintf(label,"#it{e^{+}} d<v_{1}>/dy = %1.3f#pm%1.3f(stat.)",func1->GetParameter(0),func1->GetParError(0));
    sprintf(label1,"#it{e^{-}} d<v_{1}>/dy = %1.3f#pm%1.3f(stat.)",func2->GetParameter(0),func2->GetParError(0));
    lat.SetTextSize(0.06);
    lat.DrawLatex(-0.75,0.075,label);
    lat.DrawLatex(-0.75,0.065,label1);
    gPad->RedrawAxis();
    func3->SetLineStyle(5);
    pad2->cd();
    hdif->Fit("func3");
    hdif_g1->Fit("func33");
    //legt1->Draw("same");
//    TCanvas *c55 = new TCanvas("c55","c55");
    hdif->SetTitle(0);
    hdif->GetYaxis()->SetTitleSize(0.15);
    hdif->GetYaxis()->SetLabelSize(0.07);
    hdif->GetYaxis()->CenterTitle();
    hdif->GetYaxis()->SetNdivisions(506);                                                                                                                                                                                                     
    hdif->GetYaxis()->SetTitleOffset(0.33);
    hdif->GetXaxis()->SetTitleSize(0.16);
    hdif->GetXaxis()->SetLabelSize(0.12);
    hdif->GetXaxis()->SetTitleOffset(0.8);
    //hdif->GetXaxis()->SetRangeUser(-0.8,0.8);
    hdif->GetYaxis()->SetRangeUser(-0.047,0.047);
    hdif->GetYaxis()->SetTitle("#Delta<v_{1}>");//^{#it{e^{+}}}> - <v_{1}^{#it{e^{-}}}>");
    hdif->GetXaxis()->SetTitle("Rapidity");
    hdif->Draw("PE X0");
    gtdif->Draw("same l");
//    hdif_sys->Draw("same 5");
    //hdif_g->Draw("same PE");
     sprintf(label,"d#Delta <v_{1}>/dy = %1.3f#pm%1.3f(stat.)",func3->GetParameter(0),func3->GetParError(0));//,fabs(func3->GetParameter(0)-func33->GetParameter(0)));
    line->Draw("same");
    lat.SetTextSize(0.09);
    lat.DrawLatex(0.,0.025,label);
    line->Draw("same");
    legt1->Draw("same");
    gPad->RedrawAxis();

}
