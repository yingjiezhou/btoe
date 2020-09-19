void plot(){
/////////////////////////////////////////////////////////////////////////////////////////
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
//////////////////////////////////////////////////////////////////
    char dFile[500];
    sprintf(dFile,"../../production/NPE.root");
    TFile *f_D = new TFile(dFile);
    //TTree *tree = (TTree*)f_D->Get("JPsi_tree_sw");
    TTree *tree = (TTree*)f_D->Get("JPsi");
    TH1F *hJPsi_M = new TH1F("hJPsi_M","",40,2.5,3.5);
    TH1F *hJPsi_M1 = new TH1F("hJPsi_M1","",40,2.5,3.5);
    TH1F *hJPsi_Mws11 = new TH1F("hJPsi_Mws11","",40,2.5,3.5);
    TH1F *hJPsi_Mws = new TH1F("hJPsi_Mws","",40,2.5,3.5);
    TH1F *hJPsi_Mws1 = new TH1F("hJPsi_Mws1","",40,2.5,3.5);
    TH1F *hJPsi_Mws2 = new TH1F("hJPsi_Mws2","",40,2.5,3.5);
    TH1F *hsW = new TH1F("hsW","",40,-1,2);
    TH1F *hpt = new TH1F("hpt","",20,0,20);
    TH1F *hsige = new TH1F("hnsige","",20,-5,5);
    TH1F *hbeta = new TH1F("hbeta","",50,0,3);
    //tree->Project("JPsi_M","JPsi_M", " sWeight");
    tree->Draw("JPsi_M >> hJPsi_M", "probe_charge*tag_charge<0 &&  tag_mva>0.15 && probe_mva>0.15 && pair_dca<0.005&& abs(1/probe_beta-1)<0.025 && abs(1/tag_beta-1)<0.025&&  probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5 ");

    tree->Draw("JPsi_M >> hJPsi_M1", "probe_charge*tag_charge<0 && pair_dca<0.005 && probe_nsige<2 && probe_nsige>-1 && abs(1/probe_beta-1)<0.025 && abs(1/tag_beta-1)<0.025 &&  probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
    tree->Draw("JPsi_M >> hJPsi_Mws11", "probe_charge*tag_charge>0 && pair_dca<0.005 && probe_nsige<2 && probe_nsige>-1 && abs(1/probe_beta-1)<0.025 && abs(1/tag_beta-1)<0.025  &&  probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5");
    tree->Draw("JPsi_M >> hJPsi_Mws1", "probe_charge>0 && tag_charge>0 &&  tag_mva>0.15 && probe_mva>0.15  && pair_dca<0.005 && abs(1/probe_beta-1)<0.025 && abs(1/tag_beta-1)<0.025&&  probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5 ");
    tree->Draw("JPsi_M >> hJPsi_Mws2", "probe_charge<0 && tag_charge<0 &&  tag_mva>0.15  && probe_mva>0.15 && pair_dca<0.005 && abs(1/probe_beta-1)<0.025 && abs(1/tag_beta-1)<0.025&&  probe_p/probe_emc0>0.3 && probe_p/probe_emc0<1.5 ");
    for(int i = 1;i<hJPsi_Mws1->GetNbinsX()+1;i++){
	double temp1 = hJPsi_Mws1->GetBinContent(i);
	double temp2 = hJPsi_Mws2->GetBinContent(i);
	double temp11 = hJPsi_Mws1->GetBinError(i);
	double temp22 = hJPsi_Mws2->GetBinError(i);
	hJPsi_Mws->SetBinContent(i,2*sqrt(temp1*temp2));
	hJPsi_Mws->SetBinError(i,sqrt(temp11*temp11+temp22*temp22));
	}
    //tree->Draw("sWeight >> hsW");
    //tree->Draw("probe_pt >> hpt", " sWeight");
    //tree->Draw("probe_nsige >> hnsige", "probe_charge*tag_charge<0&& probe_nsige>-1 && probe_nsige<3");
    //tree->Draw("probe_beta >> hbeta", " sWeight");
    hJPsi_Mws->SetLineColor(kRed);
    hJPsi_Mws11->SetLineColor(kRed);
    hJPsi_M1->SetLineColor(kBlue);
    hJPsi_M1->SetMarkerColor(kBlue);
    TCanvas *c1 =new TCanvas("c1","M");
    //hJPsi_M->Add(hJPsi_Mws,-1);
    //hJPsi_M1->Add(hJPsi_Mws11,-1);
    hJPsi_M->Draw("PE");
    hJPsi_M1->Draw("PE same");    
    hJPsi_Mws->Draw("hist same"); 
    hJPsi_Mws11->Draw("hist same");   
    /*TCanvas *c2 =new TCanvas("c2","sW");
    hsW->Draw();
    TCanvas *c3 =new TCanvas("c3","hpt");
    hpt->Draw();
    TCanvas *c4 =new TCanvas("c4","hnsige");
    hnsige->Draw();
    TCanvas *c5 =new TCanvas("c5","hbeta");
    hbeta->Draw();*/
}
void norm(TH1D *h){
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1);
	h->SetBinError(i,err/norm1);
    }
}
