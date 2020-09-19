void CombineV2(int save = 1){
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};   
    TH1F* Combine = new TH1F("Combine","",numPtBins,binning);
    TH1F* Combine_er = new TH1F("Combine_er","",numPtBins,binning);
    TH1F* Combine1_er = new TH1F("Combine1_er","",numPtBins,binning);
    TH1F* Combine1 = new TH1F("Combine1","",numPtBins,binning);
    TFile *f = new TFile("./root/DCA_plots.root");
    TFile *f1 = new TFile("./root/DCA_plots_tightdca.root");   
    comp1=(TH1F*)f1->Get("Pi0_Comp");
    comp2=(TH1F*)f1->Get("Eta_Comp");
    comp3=(TH1F*)f1->Get("Gamma_Comp");
    comp4=(TH1F*)f1->Get("Pi0Gamma_Comp");
    comp5=(TH1F*)f1->Get("EtaGamma_Comp");
    comp11=(TH1F*)f->Get("Pi0_ee_Comp");
    comp11->SetName("comp11");
    comp22=(TH1F*)f->Get("Eta_ee_Comp");
    comp22->SetName("comp11");
    comp33=(TH1F*)f->Get("Gamma_ee_Comp");
    comp33->SetName("comp11");
    comp44=(TH1F*)f->Get("Pi0Gamma_ee_Comp");
    comp44->SetName("comp11");
    comp55=(TH1F*)f->Get("EtaGamma_ee_Comp");//_ee
    comp55->SetName("comp11");

    TFile *f1= new TFile("v2_hists/pion_v2.root","READ");
    DD = (TH1F*)f1->Get("PhoEV2");
    DD->SetName("DD");
    DDee = (TH1F*)f1->Get("PhoEV2_ee");
    DDee->SetName("DDee");
    TFile *f2= new TFile("v2_hists/pion_v2_hijing.root","READ");
    CE = (TH1F*)f2->Get("PhoEV2");
    CE->SetName("CE");    
    CEee = (TH1F*)f2->Get("PhoEV2_ee");
    CEee->SetName("CEee");  
    for(int i = 1;i<10;i++){
	double temp1 = comp1->GetBinContent(i);
	double temp2 = comp4->GetBinContent(i)+comp3->GetBinContent(i)+comp5->GetBinContent(i);	
	double temp11 = comp11->GetBinContent(i);
	double temp22 = comp44->GetBinContent(i)+comp33->GetBinContent(i)+comp55->GetBinContent(i);	

	double ave = DD->GetBinContent(i)*temp1/(temp1+temp2) + temp2*CE->GetBinContent(i)/(temp1+temp2);
	double ave1 = DDee->GetBinContent(i)*temp11/(temp11+temp22) + temp22*CEee->GetBinContent(i)/(temp11+temp22);
	double ave_er = sqrt(DD->GetBinError(i)*DD->GetBinError(i)*temp1*temp1/(temp1+temp2)/(temp1+temp2) + CE->GetBinError(i)*CE->GetBinError(i)*temp2*temp2/(temp1+temp2)/(temp1+temp2));
        double ave1_er = sqrt(DDee->GetBinError(i)*DDee->GetBinError(i)*temp11*temp11/(temp11+temp22)/(temp11+temp22) + CEee->GetBinError(i)*CEee->GetBinError(i)*temp22*temp22/(temp11+temp22)/(temp11+temp22));
	cout << temp1/(temp1+temp2) << " " << temp2/(temp1+temp2) << endl;
	cout << temp11/(temp11+temp22) << " " << temp22/(temp11+temp22) << endl;
	Combine->SetBinContent(i,ave);
        Combine->SetBinError(i,ave_er);
	Combine_er->SetBinContent(i,ave);
	Combine_er->SetBinError(i,ave*0.5);
	Combine1->SetBinContent(i,ave1);	
	Combine1->SetBinError(i,ave1_er);
	Combine1_er->SetBinContent(i,ave1);	
	Combine1_er->SetBinError(i,ave1*0.5);
    }

    DD->SetLineColor(kBlue);
    DD->SetMarkerColor(kBlue);   
    CE->SetLineColor(kRed);
    CE->SetMarkerColor(kRed);   
    DDee->SetLineColor(kBlue);
    DDee->SetMarkerColor(kBlue);   
    CEee->SetLineColor(kRed);
    CEee->SetMarkerColor(kRed);   
    Combine_er->SetFillColor(kGray);
    Combine1_er->SetFillColor(kGray);
    TLegend *leg = new TLegend(0.4,0.74,0.6,0.9);

    leg->AddEntry(DD,"Dalitz decay","l");
    leg->AddEntry(CE,"Conversion electron","l");
    leg->AddEntry(Combine,"Average","l");
    TCanvas *c1 = new TCanvas ("c1","single e");
    Combine->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    Combine->GetYaxis()->SetTitle("v_{2}");
    Combine->GetYaxis()->SetRangeUser(0,0.3);
    Combine->Draw();
    Combine_er->Draw("same E2");
    DD->Draw("same");
    CE->Draw("same");
    TLegend *leg = new TLegend(0.6,0.6,0.9,0.9);
    leg->AddEntry(DD,"Dalitz decay","PLE");
    leg->AddEntry(CE,"Conversion electron","PLE");  
    leg->AddEntry(Combine,"Combined photonic electron","PLE");   
    leg->Draw("same");

    Combine->Draw("same E1");
    gPad->RedrawAxis();

    TCanvas *c2 = new TCanvas ("c2","ee pairs");
    Combine1->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    Combine1->GetYaxis()->SetTitle("v_{2}");
    Combine1->GetYaxis()->SetRangeUser(0,0.3);
    Combine1->Draw();
    Combine1_er->Draw("same E2");
    DDee->Draw("same");
    CEee->Draw("same");
    Combine1->Draw("same E1");
    leg->Draw("same");
    gPad->RedrawAxis();

    TLatex lat;
    TCanvas *c11 = new TCanvas ("c11","");
    Combine->Draw();
    Combine_er->Draw("same E2");
    Combine->Draw("same E1");
    lat.DrawLatex(4.5,0.23,"Photonic electron");
    gPad->RedrawAxis();
    if(save){
        TFile fff("v2_hists/phoe_v2.root","RECREATE");
        Combine->Write("PhoEV2");
	Combine1->Write("PhoEV2_2");
    }
}
void norm5(TH1F *h){
    h->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    h->GetYaxis()->SetTitle("Arb. Units");
    h->GetYaxis()->SetRangeUser(1e-7,1);
    h->Rebin();
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
