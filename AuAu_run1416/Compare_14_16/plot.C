void plot(int pt = 5)
{
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
//////
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};    
	
    TFile *f_D = new TFile("../production/NPE_Tuples_Run16.root");
    TFile *f_D1 = new TFile("../../NPE_ANA/production/NPE_Tuples_TuneB12.root");
    
    h01_2D = (TH2F*)f_D->Get("hDcaLog3D_1");//4 
    h01_2D->SetName("h01_2D");
    h01_2D_pi = (TH2F*)f_D->Get("hDcaLog3D_pi_1");//4
    h01_2D_pi->SetName("h01_2D_pi");
    h01_2D1 = (TH2F*)f_D1->Get("hDcaLog3D_1");//2
    h01_2D_pi1 = (TH2F*)f_D1->Get("hDcaLog3D_pi_1");//0

    hp1 = (TH2F*)h01_2D->Clone("hp1");
    hp2 = (TH2F*)h01_2D->Clone("hp2");
    hp11 = (TH2F*)h01_2D->Clone("hp11");
    hp22 = (TH2F*)h01_2D->Clone("hp22");

    h1 = (TH2F*)h01_2D->Clone("h1");
    h2 = (TH2F*)h01_2D->Clone("h2");
    h3 = (TH2F*)h01_2D->Clone("h3");
    

//    hp1->Add(h01_2D,-1);
    // hp2->Add(h01_2D,-1);
    //hp11->Add(h01_2D,-1);
    //hp22->Add(h01_2D,-1);

    ch1 = (TChain*)f_D->Get("PhoE");
    ch2 = (TChain*)f_D1->Get("PhoE");
    ch1->Project("hp1","log10(abs(probe_dca)+0.000000001):probe_pt","probe_charge*tag_charge<0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3")  ;
    ch1->Project("hp2","log10(abs(probe_dca)+0.000000001):probe_pt","probe_charge*tag_charge>0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3")  ;
    ch2->Project("hp11","log10(abs(probe_dca)+0.000000001):probe_pt","probe_charge*tag_charge<0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3")  ;
    ch2->Project("hp22","log10(abs(probe_dca)+0.000000001):probe_pt","probe_charge*tag_charge>0 && probe_mva>0 && probe_nsige>-1 && probe_nsige<3")  ;
    hp1->Add(hp2,-1);
    hp11->Add(hp22,-1);

    if(pt>0){    
	h01_2D->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	h01_2D1->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	h01_2D_pi->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);	
	h01_2D_pi1->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	hp1->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
	hp11->GetXaxis()->SetRangeUser(binning[pt-1],binning[pt]);
    }

    h01=(TH1F*)h01_2D->ProjectionY();
    h01_1=(TH1F*)h01_2D1->ProjectionY();
    h01_pi=(TH1F*)h01_2D_pi->ProjectionY();
    h01_pi_1=(TH1F*)h01_2D_pi1->ProjectionY();
    hp=(TH1F*)hp1->ProjectionY();
    hp_1=(TH1F*)hp11->ProjectionY();
    hx1=(TH1F*)h1->ProjectionY();
    hx2=(TH1F*)h2->ProjectionY();    
    hx3=(TH1F*)h3->ProjectionY();
//////////////////////////////////////////////////////////////////   
    h01->Rebin(4);
    h01_1->Rebin(4);
    h01_pi->Rebin(4);   
    h01_pi_1->Rebin(4);
    hp->Rebin(8);
    hp_1->Rebin(8);
    hx1->Rebin(4);
    hx2->Rebin(4);
    hx3->Rebin(8);
    
    norm(h01,(1./h01->GetMaximum()));//543
    norm(h01_1,(1./h01_1->GetMaximum()));//887
    norm(h01_pi,(1./h01_pi->GetMaximum()));
    norm(h01_pi_1,(1./h01_pi_1->GetMaximum()));///887));
    norm(hp,(1./hp->GetMaximum()));
    norm(hp_1,(1./hp_1->GetMaximum()));
    
    diff(h01,h01_1,hx1);
    diff(h01_pi,h01_pi_1,hx2);
    diff(hp,hp_1,hx3);
    
    TCanvas *c1 = new TCanvas ("c1","c1");
    h01->Draw("PE");
    h01_1->SetLineColor(kRed);
    h01_1->SetMarkerColor(kRed);
    h01_1->Draw("same PE");
    TCanvas *c11 = new TCanvas ("c11","c11");
    h01_pi->Draw("PE");
    h01_pi_1->SetLineColor(kRed);
    h01_pi_1->SetMarkerColor(kRed);
    h01_pi_1->DrawClone("same PE");
    TCanvas *c111 = new TCanvas ("c111","phoe");
    hp->Draw("PE");
    hp_1->SetLineColor(kRed);
    hp_1->SetMarkerColor(kRed);
    hp_1->DrawClone("same PE");
    
    TCanvas *c1111 = new TCanvas ("c1111","diff");
    hx1->Draw("hist");
    hx2->SetLineColor(kBlue);
    hx2->Draw("same hist");
    hx3->SetLineColor(kRed);
    hx3->Draw("same hist");

}//End
void norm(TH1F *h, double norm1){
    //double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
        double temp = h->GetBinContent(i);
        double width = h->GetBinWidth(i);
        double err = h->GetBinError(i);
        h->SetBinContent(i,temp*norm1);
        h->SetBinError(i,err*norm1);
    }
}

void diff(TH1F *h1,TH1F *h2,TH1F *h3){
    for(int i=1; i<h1->GetNbinsX()+1;i++){
        double temp1 = h1->GetBinContent(i);
        double temp2 = h2->GetBinContent(i);
        double err1 = h1->GetBinError(i);
        double err2 = h2->GetBinError(i);
	h3->SetBinContent(i,temp1-temp2);
        h3->SetBinError(i,sqrt(err1*err1+err2*err2));
    }


}
