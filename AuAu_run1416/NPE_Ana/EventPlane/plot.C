void plot(){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
   
//////////////////////////////////////////////////////////////////
    char dFile[500];
    sprintf(dFile,"../production/NPE_Tuples_TuneB11.root");
    TFile *f_D = new TFile(dFile);
    h1 = (TH1F*) f_D->Get("EventPlane");
    h11 = (TH1F*) f_D->Get("h1dEventCentrality");
    cout<< "Fraction in 0-10% " << endl;
    cout << h11->Integral(8,9)/h11->Integral() << endl;
    cout<< "Fraction in 10-20% " << endl;
    cout << h11->Integral(7,7)/h11->Integral() << endl;
     cout<< "Fraction in 20-30% " << endl;
    cout << h11->Integral(6,6)/h11->Integral() << endl;
     cout<< "Fraction in 30-40% " << endl;
    cout << h11->Integral(5,5)/h11->Integral() << endl;
     cout<< "Fraction in 40-50% " << endl;
    cout << h11->Integral(4,4)/h11->Integral() << endl;
     cout<< "Fraction in 50-60% " << endl;
    cout << h11->Integral(3,3)/h11->Integral() << endl;
     cout<< "Fraction in 60-80% " << endl;
    cout << h11->Integral(1,2)/h11->Integral() << endl;

    h2 = (TH1F*) f_D->Get("EventPlane_Corr1");
    h3 = (TH1F*) f_D->Get("EventPlane_Corr2");
    h2D = (TH2F*) f_D->Get("EventPlane_Res");
    h = (TH1F*) h2D->ProjectionX();
    double binns[10] = {0,5,10,20,30,40,50,60,70,80};
    TH1F *h = new TH1F("h","h",9,binns);
    h1->Rebin(4);
    h2->Rebin(4);
    h3->Rebin(4);
    for(int i =1;i<h2D->GetNbinsX()+1;i++){
	h2D->GetXaxis()->SetRangeUser(i-1,i);
	temp = (TH1F*) h2D->ProjectionY();
	double ave = sqrt(temp->GetMean());
	h->SetBinContent(9-i+1,ave);
	h->SetBinError(9-i+1,0.00001);	
    }

    TCanvas *c2 = new TCanvas("c2","");   
    h->GetYaxis()->SetTitle("#sqrt{<cos[2(#Psi^{a}-#Psi^{b})]>}");
    h->GetYaxis()->SetRangeUser(0,1);
    h->GetXaxis()->SetTitle("Centrality [%]");

    h->Draw("pe");
    TCanvas *c1 = new TCanvas("c1","");
    norm(h1);
    norm(h2);
    norm(h3);
    h2->SetLineColor(kRed);
    h3->SetLineColor(kBlue);
    h1->Draw("hist");
    h2->Draw("same hist");
    h3->Draw("same hist");
   
}//End
void center(int save){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    gStyle->SetPalette(56);

//////////////////////////////////////////////////////////////////
    char dFile[500];
    sprintf(dFile,"../production/NPE_Tuples_TuneB11.root");
    TFile *f_D = new TFile(dFile);
    ch1 = (TChain*) f_D->Get("Event");
    TH1F * h = new TH1F("h","",200,0,3.15);
    TH1F * h_corr = new TH1F("h_corr","",200,0,3.15);
    TH2F * h_res = new TH2F("h_res","",9,0,9,200,-1,1);
    TH1F * h1 = new TH1F("h1","",200,0,3.15);
    TH1F * h2 = new TH1F("h2","",200,0,3.15);
    TH1F * h1_corr = new TH1F("h1_corr","",200,0,3.15);
    TH1F * h2_corr = new TH1F("h2_corr","",200,0,3.15);
    TH1F * hx = new TH1F("hx","",201,-100,100);
    TH1F * hy = new TH1F("hy","",201,-100,100);
    TH1F * hx_corr = new TH1F("hx_corr","",201,-100,100);
    TH1F * hy_corr = new TH1F("hy_corr","",201,-100,100);
    TH2F * hxy = new TH2F("hxy","",200,-100,100,200,-100,100);
    TH2F * hxy_corr = new TH2F("hxy_corr","",200,-100,100,200,-100,100);
    TH1F * hrun = new TH1F("hrun","hrun",2E5,0,2E5);   

    float qx;
    float qy;
    float qx1;
    float qy1;
    float qx2;
    float qy2;
    float run_id;
    float centrality;
    ch1 -> SetBranchAddress( "event_qx" , &qx );
    ch1 -> SetBranchAddress( "event_qy" , &qy );
    ch1 -> SetBranchAddress( "event_qx1" , &qx1 );
    ch1 -> SetBranchAddress( "event_qy1" , &qy1 );
    ch1 -> SetBranchAddress( "event_qx2" , &qx2 );
    ch1 -> SetBranchAddress( "event_qy2" , &qy2 );   
    ch1 -> SetBranchAddress( "run_id" , &run_id );  
    ch1 -> SetBranchAddress( "event_centrality" , &centrality );   

    float ref_id=0;
    TH2F* htempx= new TH2F("htempx","htempx",2001,-100,100,9,0,9);
    TH2F* htempy= new TH2F("htempy","htempy",2001,-100,100,9,0,9);
    TH2F* htempx1= new TH2F("htempx1","htempx1",2001,-100,100,9,0,9);
    TH2F* htempy1= new TH2F("htempy1","htempy1",2001,-100,100,9,0,9);
    TH2F* htempx2= new TH2F("htempx2","htempx2",2001,-100,100,9,0,9);
    TH2F* htempy2= new TH2F("htempy2","htempy2",2001,-100,100,9,0,9);
    int loop = ch1->GetEntries();
    if(save==1){
	TH2F * hcorr_x = new TH2F("hcorr_x","hcorr_x",2E5,0,2E5,9,0,9);    
	TH2F * hcorr_y = new TH2F("hcorr_y","hcorr_y",2E5,0,2E5,9,0,9); 
	TH2F * hcorr_x1 = new TH2F("hcorr_x1","hcorr_x1",2E5,0,2E5,9,0,9);    
	TH2F * hcorr_y1 = new TH2F("hcorr_y1","hcorr_y1",2E5,0,2E5,9,0,9); 
	TH2F * hcorr_x2 = new TH2F("hcorr_x2","hcorr_x2",2E5,0,2E5,9,0,9);    
	TH2F * hcorr_y2 = new TH2F("hcorr_y2","hcorr_y2",2E5,0,2E5,9,0,9);  
	for(int i =0;i<loop;i++){
	    ch1->GetEntry(i);
	    run_id = run_id-15E6;
	    if(i%1000000==0)cout << "On event " << i << " out of " << loop << endl;
	    if(ref_id==0){
		ref_id = run_id;
	    }
	    if(ref_id!=run_id || i == loop-1){
		for(int j=1;j<10;j++){
		    htempxx= (TH1D*) htempx->ProjectionX("htempxx",j,j+1);
		    htempyy= (TH1D*) htempy->ProjectionX("htempyy",j,j+1);
		    htempx11= (TH1D*) htempx1->ProjectionX("htempx11",j,j+1);
		    htempy11= (TH1D*) htempy1->ProjectionX("htempy11",j,j+1);
		    htempx22= (TH1D*) htempx2->ProjectionX("htempx22",j,j+1);
		    htempy22= (TH1D*) htempy2->ProjectionX("htempy22",j,j+1);
		    double temp1 = htempx11->GetMean();
		    double temp2 = htempy11->GetMean();
		    double temp3 = htempx22->GetMean();
		    double temp4 = htempy22->GetMean();
		    double temp5 = htempxx->GetMean();
		    double temp6 = htempyy->GetMean();
		    int bin = hcorr_x1->FindBin(ref_id,j-0.5);
		    hcorr_x1->SetBinContent(bin,temp1);
		    hcorr_y1->SetBinContent(bin,temp2);
		    hcorr_x2->SetBinContent(bin,temp3);
		    hcorr_y2->SetBinContent(bin,temp4);
		    hcorr_x->SetBinContent(bin,temp5);
		    hcorr_y->SetBinContent(bin,temp6);
		    htempxx->Delete();
		    htempyy->Delete();
		    htempx11->Delete();
		    htempy11->Delete();
		    htempx22->Delete();
		    htempy22->Delete();
		}
		hrun->Fill(run_id);
		cout << "Found New Run # " << ref_id << endl;
		cout << "Averages " << temp1 << " " << temp2 << " " << temp3 << " " << temp4 << " " << temp5 <<" " << temp6 << endl;
		ref_id=run_id;
		htempx->Delete();
		htempy->Delete();
		htempx1->Delete();
		htempy1->Delete();
		htempx2->Delete();
		htempy2->Delete();
		TH2F* htempx= new TH2F("htempx","htempx",2001,-100,100,9,0,9);
		TH2F* htempy= new TH2F("htempy","htempy",2001,-100,100,9,0,9);
		TH2F* htempx1= new TH2F("htempx1","htempx1",2001,-100,100,9,0,9);
		TH2F* htempy1= new TH2F("htempy1","htempy1",2001,-100,100,9,0,9);
		TH2F* htempx2= new TH2F("htempx2","htempx2",2001,-100,100,9,0,9);
		TH2F* htempy2= new TH2F("htempy2","htempy2",2001,-100,100,9,0,9);
	    }
	    htempx->Fill(qx,centrality);
	    htempy->Fill(qy,centrality);
	    htempx1->Fill(qx1,centrality);
	    htempy1->Fill(qy1,centrality);
	    htempx2->Fill(qx2,centrality);
	    htempy2->Fill(qy2,centrality);	
	}
	if(save==1){
	    TFile f("root/event_corr_new.root","RECREATE");
	    hcorr_x->Write("run_centrality_corrx");
	    hcorr_y->Write("run_centrality_corry");
	    hcorr_x1->Write("run_centrality_corrx1");
	    hcorr_y1->Write("run_centrality_corry1");
	    hcorr_x2->Write("run_centrality_corrx2");
	    hcorr_y2->Write("run_centrality_corry2");
	    f.Close();
	}
    }
    if(save==2){
	char dFile1[500];
	sprintf(dFile1,"./root/event_corr_new.root");
	TFile *f_D1 = new TFile(dFile1);
	hcorr_x=(TH2F*)f_D1->Get("run_centrality_corrx");
	hcorr_y=(TH2F*)f_D1->Get("run_centrality_corry");
	hcorr_x1=(TH2F*)f_D1->Get("run_centrality_corrx1");
	hcorr_y1=(TH2F*)f_D1->Get("run_centrality_corry1");
	hcorr_x2=(TH2F*)f_D1->Get("run_centrality_corrx2");
	hcorr_y2=(TH2F*)f_D1->Get("run_centrality_corry2");   
	int loop = ch1->GetEntries();//10000000;
	for(int i =0;i<loop;i++){
	    ch1->GetEntry(i);
	    if(i%1000000==0)cout << "On event " << i << " out of " << loop<< endl;
	    run_id = run_id-15E6;
	    int bin = hcorr_x->FindBin(run_id,centrality);
	    double corrx = hcorr_x->GetBinContent(bin)/1.;
	    double corry = hcorr_y->GetBinContent(bin)/1.;
	    double corrx1 = hcorr_x1->GetBinContent(bin)/1.;
	    double corry1 = hcorr_y1->GetBinContent(bin)/1.;
	    double corrx2 = hcorr_x2->GetBinContent(bin)/1.;
	    double corry2 = hcorr_y2->GetBinContent(bin)/1.;	
	    h->Fill((TMath::Pi()+TMath::ATan2(-(qy),-(qx))) / 2.);
	    h_corr->Fill((TMath::Pi()+TMath::ATan2(-(qy-corry),-(qx-corrx))) / 2.);
	    h1->Fill((TMath::Pi()+TMath::ATan2(-(qy1),-(qx1))) / 2.);
	    h1_corr->Fill((TMath::Pi()+TMath::ATan2(-(qy1-corry1),-(qx1-corrx1))) / 2.);
	    h2->Fill((TMath::Pi()+TMath::ATan2(-(qy2),-(qx2))) / 2.);
	    h2_corr->Fill((TMath::Pi()+TMath::ATan2(-(qy2-corry2),-(qx2-corrx2))) / 2.);

	    double plane1 = (TMath::Pi()+TMath::ATan2(-(qy1-corry1),-(qx1-corrx1))) / 2.;
	    double plane2 = (TMath::Pi()+TMath::ATan2(-(qy2-corry2),-(qx2-corrx2))) / 2.;
	    h_res->Fill(centrality,TMath::Cos(2.*(plane1-plane2)));
	    hxy->Fill(qx,qy);
	    hxy_corr->Fill(qx-corrx,qy-corry);
	    hx->Fill(qx2);
	    hy->Fill(qy2); 
	    hx_corr->Fill(qx2-corrx2);
	    hy_corr->Fill(qy2-corry2); 
	}
	hres = (TH1F*) h_res->ProjectionX();
	for(int i =1;i<h_res->GetNbinsX()+1;i++){
	    h_res->GetXaxis()->SetRangeUser(i-1,i);
	    temp = (TH1F*) h_res->ProjectionY();
	    double ave = sqrt(temp->GetMean());
	    hres->SetBinContent(i,ave);
	    hres->SetBinError(i,0);	
	}
	TCanvas *c1 = new TCanvas ("c1","",1000,800);
	c1->Divide(2,2);
	c1->cd(1);
	hcorr_x1->Draw("colz");
	c1->cd(2);
	hcorr_y1->Draw("colz");
	c1->cd(3);
	hcorr_x2->Draw("colz");
	c1->cd(4);
	hcorr_y2->Draw("colz");

	TCanvas *cr = new TCanvas ("cr","");
	hres->Draw("P");
	TCanvas *cx = new TCanvas ("cx","",1000,400);
	cx->Divide(2,1);
	cx->cd(1);
	hx->Draw();
	hx_corr->SetLineColor(kRed);
	hx_corr->Draw("same");
	cx->cd(2);
	hy->Draw();
	hy_corr->SetLineColor(kRed);
	hy_corr->Draw("same");
	cout<< "Means " << hx->GetMean() << " " <<  hx_corr->GetMean() << endl;
	cout<< "Means " << hy->GetMean() << " " <<  hy_corr->GetMean() << endl;
	TCanvas *cxy = new TCanvas ("cxy","",1000,400);
	cxy->Divide(2,1);
	cxy->cd(1);
	hxy->Draw("COLZ");
	cxy->cd(2);
	hxy_corr->Draw("COLZ");
	TCanvas *c3 = new TCanvas ("c3","");
	h->Draw();
	h_corr->SetLineColor(kRed);
	h_corr->Draw("same");

	h1->SetLineColor(kBlue);
	h1_corr->SetLineColor(kMagenta);
	//h1->Draw("same");
	//h1_corr->Draw("same");
	h2->SetLineColor(kGreen-2);
	h2_corr->SetLineColor(kCyan);
	//h2->Draw("same");
	//h2_corr->Draw("same");

	TCanvas *c4 = new TCanvas ("c4","");
	hrun->Draw();
  
   
	if(save==2){
	    TFile f1("root/event_res_new.root","RECREATE");
	    hres->Write("centrality_resolution");
	    f1.Close();
	}
    }
}
void norm(TH1F *h){
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1);
	h->SetBinError(i,err/norm1);
    }
}
void clear(TH1F *h){
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	h->SetBinContent(i,0);
	h->SetBinError(i,0);
    }
}
