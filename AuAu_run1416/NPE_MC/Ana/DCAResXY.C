int const num=22;
double bin[num+1]={0.6,0.8,1,1.2,1.4,1.6,1.8,2,2.2,2.4,2.6,2.8,3,3.2,3.4,3.6,3.8,4,4.5,5,6,8,10};

void DCAResXY(int save = 0, int weight_data=0){ //weight only for phoE pair comp. and reweight for weight.C, and if doing other comp. integrated over pt
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    //gStyle->SetPadLeftMargin(3);
    TGaxis::SetMaxDigits(3);  
//////////////////////////////////////////////////////////////////
    TFile *f1 = new TFile("../../NPE_Ana/production/NPE_Tuples_TuneA10.root");
    ratio1 = (TH2F*) f1->Get("hQaDcaXY1");
    ratio2 = (TH2F*) f1->Get("hQaDcaXY2");
    ratio3 = (TH2F*) f1->Get("hQaDcaXY3");
    ratio4 = (TH2F*) f1->Get("hQaDcaXY4");
    ratio5 = (TH2F*) f1->Get("hQaDcaXY5");
    ratio6 = (TH2F*) f1->Get("hQaDcaXY6");
    ratio7 = (TH2F*) f1->Get("hQaDcaXY7");
    ratio8 = (TH2F*) f1->Get("hQaDcaXY8");

    char dFile[500];
    sprintf(dFile,"All_Decays.root");
    TFile *f_D = new TFile(dFile);
    TChain *ch1 = f_D->Get("Signal_tree");

    TH2F *dcapt_1 = new TH2F("dcapt_1","dcapt_1",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_1_p = new TH2F("dcapt_1_p","dcapt_1_p",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_2 = new TH2F("dcapt_2","dcapt_2",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_2_p = new TH2F("dcapt_2_p","dcapt_2_p",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_3 = new TH2F("dcapt_3","dcapt_3",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_3_p = new TH2F("dcapt_3_p","dcapt_3_p",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_4 = new TH2F("dcapt_4","dcapt_4",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_4_p = new TH2F("dcapt_4_p","dcapt_4_p",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_5 = new TH2F("dcapt_5","dcapt_5",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_5_p = new TH2F("dcapt_5_p","dcapt_5_p",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_6 = new TH2F("dcapt_6","dcapt_6",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_6_p = new TH2F("dcapt_6_p","dcapt_6_p",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_7 = new TH2F("dcapt_7","dcapt_7",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_7_p = new TH2F("dcapt_7_p","dcapt_7_p",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_8 = new TH2F("dcapt_8","dcapt_8",200,-0.02,0.02,200,0,20);
    TH2F *dcapt_8_p = new TH2F("dcapt_8_p","dcapt_8_p",200,-0.02,0.02,200,0,20);


    TH1F *res_1 = new TH1F("res_1","res_1",num,bin);
    TH1F *res_2 = new TH1F("res_2","res_2",num,bin);
    TH1F *res_3 = new TH1F("res_3","res_3",num,bin);
    TH1F *res_4 = new TH1F("res_4","res_4",num,bin);
    TH1F *res_5 = new TH1F("res_5","res_5",num,bin);
    TH1F *res_6 = new TH1F("res_6","res_6",num,bin);
    TH1F *res_7 = new TH1F("res_7","res_7",num,bin);
    TH1F *res_8 = new TH1F("res_8","res_8",num,bin);
    TH1F *res_1_p = new TH1F("res_1_p","res_1_p",num,bin);
    TH1F *res_2_p = new TH1F("res_2_p","res_2_p",num,bin);
    TH1F *res_3_p = new TH1F("res_3_p","res_3_p",num,bin);
    TH1F *res_4_p = new TH1F("res_4_p","res_4_p",num,bin);
    TH1F *res_5_p = new TH1F("res_5_p","res_5_p",num,bin);
    TH1F *res_6_p = new TH1F("res_6_p","res_6_p",num,bin);
    TH1F *res_7_p = new TH1F("res_7_p","res_7_p",num,bin);
    TH1F *res_8_p = new TH1F("res_8_p","res_8_p",num,bin);
    TH1F *res_data_1 = new TH1F("res_data_1","res_data_1",num,bin);
    TH1F *res_data_2 = new TH1F("res_data_2","res_data_2",num,bin);
    TH1F *res_data_3 = new TH1F("res_data_3","res_data_3",num,bin);
    TH1F *res_data_4 = new TH1F("res_data_4","res_data_4",num,bin);
    TH1F *res_data_5 = new TH1F("res_data_5","res_data_5",num,bin);
    TH1F *res_data_6 = new TH1F("res_data_6","res_data_6",num,bin);
    TH1F *res_data_7 = new TH1F("res_data_7","res_data_7",num,bin);
    TH1F *res_data_8 = new TH1F("res_data_8","res_data_8",num,bin);

    float s_eta;
    float s_pt;
    float s_id;
    float s_head;
    float s_parentid;
    float s_gparentid;
    float s_ggparentid;
    float s_parentpt;
    float s_gparentpt;
    float s_ggparentpt;
    float s_dcaxy;
    float s_hft;
    float s_phi;
    float s_iso;
    float s_cen;
    float s_parentphi;
//======================================================================
    ch1->SetBranchAddress("sig_pt",&s_pt);
    ch1->SetBranchAddress("event_centrality",&s_cen);
    ch1->SetBranchAddress("sig_dcaxy",&s_dcaxy);
    ch1->SetBranchAddress("sig_hft",&s_hft);
    ch1->SetBranchAddress("sig_id",&s_id);
    ch1->SetBranchAddress("sig_phi",&s_phi);
    ch1->SetBranchAddress("sig_phi2",&s_parentphi);
    ch1->SetBranchAddress("sig_head",&s_head);
    ch1->SetBranchAddress("sig_isiso",&s_iso);
    ch1->SetBranchAddress("sig_parentid",&s_parentid);
    ch1->SetBranchAddress("sig_gparentid",&s_gparentid);
    ch1->SetBranchAddress("sig_ggparentid",&s_ggparentid);
    ch1->SetBranchAddress("sig_parentpt",&s_parentpt);
    ch1->SetBranchAddress("sig_gparentpt",&s_gparentpt);
    ch1->SetBranchAddress("sig_ggparentpt",&s_ggparentpt);
    for(int i =0;i<ch1->GetEntries();i++){
	ch1->GetEntry(i);
	if(i%1000000==0)cout << "on " << i << " of " << ch1->GetEntries() << endl;
	if(s_pt<0.6)continue;
	if(s_hft<1)continue;	    
	if(s_parentid==0 && (s_id==3 || s_id==2)){
	    if(s_cen==0)dcapt_1->Fill((s_dcaxy),s_pt);
	    if(s_cen==1)dcapt_2->Fill((s_dcaxy),s_pt);
	    if(s_cen==2)dcapt_3->Fill((s_dcaxy),s_pt);
	    if(s_cen==3)dcapt_4->Fill((s_dcaxy),s_pt);
	    if(s_cen==4)dcapt_5->Fill((s_dcaxy),s_pt);
	    if(s_cen==5)dcapt_6->Fill((s_dcaxy),s_pt);
	    if(s_cen==6)dcapt_7->Fill((s_dcaxy),s_pt);
	    if(s_cen==7)dcapt_8->Fill((s_dcaxy),s_pt);
	}
	if(s_parentid==0 && (s_id==8 || s_id==9)){
	    if(s_cen==0)dcapt_1_p->Fill((s_dcaxy),s_pt);
	    if(s_cen==1)dcapt_2_p->Fill((s_dcaxy),s_pt);
	    if(s_cen==2)dcapt_3_p->Fill((s_dcaxy),s_pt);
	    if(s_cen==3)dcapt_4_p->Fill((s_dcaxy),s_pt);
	    if(s_cen==4)dcapt_5_p->Fill((s_dcaxy),s_pt);
	    if(s_cen==5)dcapt_6_p->Fill((s_dcaxy),s_pt);
	    if(s_cen==6)dcapt_7_p->Fill((s_dcaxy),s_pt);
	    if(s_cen==7)dcapt_8_p->Fill((s_dcaxy),s_pt);
	}   
    }

//======================================================================
    getRes(dcapt_1,res_1,22,2);
    getRes(dcapt_1_p,res_1_p,25,4);
    getRes(dcapt_2,res_2,22,2);
    getRes(dcapt_2_p,res_2_p,25,4);
    getRes(dcapt_3,res_3,22,2);
    getRes(dcapt_3_p,res_3_p,25,4);
    getRes(dcapt_4,res_4,22,2);
    getRes(dcapt_4_p,res_4_p,25,4);
    getRes(dcapt_5,res_5,22,2);
    getRes(dcapt_5_p,res_5_p,25,4);
    getRes(dcapt_6,res_6,22,2);
    getRes(dcapt_6_p,res_6_p,25,4);
    getRes(dcapt_7,res_7,22,2);
    getRes(dcapt_7_p,res_7_p,25,4);
    getRes(dcapt_8,res_8,22,2);
    getRes(dcapt_8_p,res_8_p,25,4);
    
    getRes1(ratio1,res_data_1,8,1);
    getRes1(ratio2,res_data_2,8,1);
    getRes1(ratio3,res_data_3,8,1);
    getRes1(ratio4,res_data_4,8,1);
    getRes1(ratio5,res_data_5,8,1);
    getRes1(ratio6,res_data_6,8,1);
    getRes1(ratio7,res_data_7,8,1);
    getRes1(ratio8,res_data_8,8,1);

    TLegend *leg2 = new TLegend(0.5,0.7,0.8,0.9);
    leg2->AddEntry(res_data_1,"Data |n#sigma_{#pi}|<2","PE");
    leg2->AddEntry(res_1_p,"Emb. Pion","PE");
    leg2->AddEntry(res_1,"Emb. Electron","PE");


    TLatex lat;
    TCanvas *c9 = new TCanvas("c9","c9",1600,800);
    c9->Divide(4,2);
    c9->cd(1);
    res_1->Draw("PE");
    res_1_p->Draw("same PE");
    res_data_1->Draw("same PE");
    leg2->Draw("same");
    lat.DrawLatex(2,5,"70-80%");
    c9->cd(2);
    res_2->Draw("PE");
    res_2_p->Draw("same PE");
    res_data_2->Draw("same PE");
    leg2->Draw("same");
    lat.DrawLatex(2,5,"60-70%");
    c9->cd(3);
    res_3->Draw("PE");
    res_3_p->Draw("same PE");
    res_data_3->Draw("same PE");
    leg2->Draw("same");    
    lat.DrawLatex(2,5,"50-60%");
    c9->cd(4);
    res_4->Draw("PE");
    res_4_p->Draw("same PE");
    res_data_4->Draw("same PE");
    leg2->Draw("same");
    lat.DrawLatex(2,5,"40-50%");
    c9->cd(5);
    res_5->Draw("PE");
    res_5_p->Draw("same PE");
    res_data_5->Draw("same PE");
    leg2->Draw("same");
    lat.DrawLatex(2,5,"30-40%");
    c9->cd(6);
    res_6->Draw("PE");
    res_6_p->Draw("same PE");
    res_data_6->Draw("same PE");
    leg2->Draw("same");
    lat.DrawLatex(2,5,"20-30%");
    c9->cd(7);
    res_7->Draw("PE");
    res_7_p->Draw("same PE");
    res_data_7->Draw("same PE");
    leg2->Draw("same");
    lat.DrawLatex(2,5,"10-20%");
    c9->cd(8);
    res_8->Draw("PE");
    res_8_p->Draw("same PE");
    res_data_8->Draw("same PE");
    leg2->Draw("same");
    lat.DrawLatex(2,5,"5-10%");

  

}//End

void getEff(TH1F *h,TH1F *g,TH1F *e){
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	if(temp1>0 && temp>0){
	    e->SetBinContent(i,temp/temp1);
	    e->SetBinError(i,temp/temp1*sqrt(1/temp + 1/temp1));
	}else{
	    e->SetBinContent(i,0);
	    e->SetBinError(i,0);
	}
    }
}
void getEff1(TH1F *h,TH1F *g){
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double temp1 = g->GetBinContent(i);
	if(temp1>0 && temp>0){
	    h->SetBinContent(i,temp/temp1);
	    h->SetBinError(i,temp/temp1*sqrt(1/temp1));
	}else{
	    h->SetBinContent(i,0);
	    h->SetBinError(i,0);
	}
    }
}

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
void normW(TH1F *h){
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double width = h->GetBinWidth(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1*h->GetBinCenter(i)*2*TMath::Pi()*width);
	h->SetBinError(i,err/norm1*h->GetBinCenter(i)*2*TMath::Pi()*width);
    }
    cout << " Nomalization " << h->Integral() << endl;


}
void getRes(TH2F * dcapt,TH1F * res,int mar,int col){
    for(int i =0;i<num;i++){
        dcapt->GetYaxis()->SetRangeUser(bin[i],bin[i+1]);
	temp = (TH1F*) dcapt->ProjectionX();
	if(temp->GetEntries()>10){
	    temp->Fit("gaus");
	    res->SetBinContent(i+1,temp->GetFunction("gaus")->GetParameter(2)*10000);
	    res->SetBinError(i+1,temp->GetFunction("gaus")->GetParError(2)*10000);
	}
	temp->Delete();
    }
    res->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    res->GetYaxis()->SetTitle("#sigma_{XY} [#mum]");
    res->GetYaxis()->SetRangeUser(0,80);
    res->GetXaxis()->SetRangeUser(0,10);
    res->SetMarkerStyle(mar);
    res->SetMarkerColor(col);
    res->SetLineColor(col);
}
void getRes1(TH2F * dcapt,TH1F * res,int mar,int col){
    for(int i =0;i<num;i++){
	dcapt->GetXaxis()->SetRangeUser(-0.01,0.01);
        dcapt->GetYaxis()->SetRangeUser(bin[i],bin[i+1]);
	temp = (TH1F*) dcapt->ProjectionX();
	if(temp->GetEntries()>10){
	    temp->Fit("gaus");
	    res->SetBinContent(i+1,temp->GetFunction("gaus")->GetParameter(2)*10000);
	    res->SetBinError(i+1,temp->GetFunction("gaus")->GetParError(2)*10000);
	}
	temp->Delete();
    }
    res->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    res->GetYaxis()->SetTitle("DCA_{XY} Resoltuion [#mum]");
    res->GetYaxis()->SetRangeUser(0,80);
    res->SetMarkerStyle(mar);
    res->SetMarkerColor(col);
    res->SetLineColor(col);
}
