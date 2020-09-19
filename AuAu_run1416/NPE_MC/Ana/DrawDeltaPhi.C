void DrawDeltaPhi(){
    gROOT->ProcessLine(".x ~/myStyle.C");  
    TGaxis::SetMaxDigits(3); 
    int const numPtBins=9;
    double binning[numPtBins+1]={0.6,1,1.2,1.5,2.0,2.5,3.5,4.5,5.5,8.5};   
    
    TH1F *Res = new TH1F("Res","B_Res",numPtBins,binning);//
    TH1F *Res_mm = new TH1F("Res_mm","D_Res_mm",numPtBins,binning);//
    char file[50]="resolution/HF.root";//
   TH1F *Cos = new TH1F("Cos","Cos",numPtBins,binning);//
    TFile *f = new TFile("./root/HF_plots.root");
    dr =(TH2F*)f->Get("phipt_d_all");
    h11 = (TH2F*) f->Get("phipt_b_all");
    cos =(TH2F*)f->Get("cosphipt_d_all");
  for(int i =1;i<10;i++){
	cos->GetYaxis()->SetRangeUser(binning[i-1],binning[i]);
	temp = (TH1F*)cos->ProjectionX();
	double mean = temp->GetMean();
	Cos->SetBinContent(i,mean);
    }
    TCanvas *c6 = new TCanvas("c6","c6");
    Cos->GetYaxis()->SetTitle("Resolution");
    Cos->GetXaxis()->SetTitle("#it{p}_{T} GeV");    
    Cos->Draw();



    dr->SetLineColor(kRed);
    dr->SetMarkerColor(kRed);

    //dr->GetXaxis()->SetRangeUser(-0.1,0.1);
    //h11->GetXaxis()->SetRangeUser(-0.1,0.1);
    dr_0 =(TH1F*) dr->ProjectionX();
    dr_0->SetName("dr_0");
    h11_0 =(TH1F*) h11->ProjectionX();
    h11_0->SetName("h11_0"); 
    norm5(dr_0);
    norm5(h11_0);
    TCanvas *c5 = new TCanvas("c5","c5");
    dr_0->Draw("PE");
    h11_0->Draw("same PE");
    TLegend *leg = new TLegend(0.2,0.6,0.5,0.9);
    leg->AddEntry(dr_0,"#it{c}#rightarrow#it{e}","PEL");
    leg->AddEntry(h11_0,"#it{b}#rightarrow#it{e}","PEL");  

    dr->GetYaxis()->SetRangeUser(binning[0],binning[1]);
    h11->GetYaxis()->SetRangeUser(binning[0],binning[1]);
    dr_1 =(TH1F*) dr->ProjectionX();
    dr_1->SetName("dr_1");
    h11_1 =(TH1F*) h11->ProjectionX();
    h11_1->SetName("h11_1"); 
    
    dr->GetYaxis()->SetRangeUser(binning[1],binning[2]);
    h11->GetYaxis()->SetRangeUser(binning[1],binning[2]);
    dr_2 =(TH1F*) dr->ProjectionX();
    dr_2->SetName("dr_2");
    h11_2 =(TH1F*) h11->ProjectionX();
    h11_2->SetName("h11_2"); 

    dr->GetYaxis()->SetRangeUser(binning[2],binning[3]);
    h11->GetYaxis()->SetRangeUser(binning[2],binning[3]);
    dr_3 =(TH1F*) dr->ProjectionX();
    dr_3->SetName("dr_3");
    h11_3 =(TH1F*) h11->ProjectionX();
    h11_3->SetName("h11_3"); 

    dr->GetYaxis()->SetRangeUser(binning[3],binning[4]);
    h11->GetYaxis()->SetRangeUser(binning[3],binning[4]);
    dr_4 =(TH1F*) dr->ProjectionX();
    dr_4->SetName("dr_4");
    h11_4 =(TH1F*) h11->ProjectionX();
    h11_4->SetName("h11_4"); 

    dr->GetYaxis()->SetRangeUser(binning[4],binning[5]);
    h11->GetYaxis()->SetRangeUser(binning[4],binning[5]);
    dr_5 =(TH1F*) dr->ProjectionX();
    dr_5->SetName("dr_5");
    h11_5 =(TH1F*) h11->ProjectionX();
    h11_5->SetName("h11_5"); 

    dr->GetYaxis()->SetRangeUser(binning[5],binning[6]);
    h11->GetYaxis()->SetRangeUser(binning[5],binning[6]);
    dr_6 =(TH1F*) dr->ProjectionX();
    dr_6->SetName("dr_6");
    h11_6 =(TH1F*) h11->ProjectionX();
    h11_6->SetName("h11_6"); 

    dr->GetYaxis()->SetRangeUser(binning[6],binning[7]);
    h11->GetYaxis()->SetRangeUser(binning[6],binning[7]);
    dr_7 =(TH1F*) dr->ProjectionX();
    dr_7->SetName("dr_7");
    h11_7 =(TH1F*) h11->ProjectionX();
    h11_7->SetName("h11_7"); 


    dr->GetYaxis()->SetRangeUser(binning[7],binning[8]);
    h11->GetYaxis()->SetRangeUser(binning[7],binning[8]);
    dr_8 =(TH1F*) dr->ProjectionX();
    dr_8->SetName("dr_8");
    h11_8 =(TH1F*) h11->ProjectionX();
    h11_8->SetName("h11_8"); 

    dr->GetYaxis()->SetRangeUser(binning[8],binning[9]);
    h11->GetYaxis()->SetRangeUser(binning[8],binning[9]);
    dr_9 =(TH1F*) dr->ProjectionX();
    dr_9->SetName("dr_9");
    h11_9 =(TH1F*) h11->ProjectionX();
    h11_9->SetName("h11_9"); 

    norm5(dr_1);
    norm5(h11_1);
    norm5(dr_2);
    norm5(h11_2);
    norm5(dr_3);
    norm5(h11_3);
    norm5(dr_4);
    norm5(h11_4);
    norm5(dr_5);
    norm5(h11_5);
    norm5(dr_6);
    norm5(h11_6);
    norm5(dr_7);
    norm5(h11_7);
    norm5(dr_8);
    norm5(h11_8);
    norm5(dr_9);
    norm5(h11_9);
    TLatex lat;
    double res = 0;
    double res1 = 0;
    char label[100];
    char label1[100];
    TCanvas *c1 = new TCanvas ("c1","",1800,800);
    c1->Divide(5,2);
    c1->cd(1);
    dr_1->Draw("PE");
    h11_1->Draw("same PE");
    leg->Draw("same");

    res=h11_1->GetRMS()*0.57735027;
    res1=dr_1->GetRMS()*0.57735027;
    getRes(res,h11_1);
    getRes(res1,dr_1);
  Res->SetBinContent(1,res);
    Res_mm->SetBinContent(1,res1);
    sprintf(label,"#sigma_{b}=%1.4f",res);
    sprintf(label1,"#sigma_{c}=%1.4f",res1);
    lat.DrawLatex(-0.5.,dr_1->GetMaximum()*0.9.1,"#it{p}_{T}#in[0.6,1.0] [GeV]");
    lat.DrawLatex(1.,dr_1->GetMaximum()*0.7,label);
    lat.DrawLatex(1.,dr_1->GetMaximum()*0.6,label1);
    c1->cd(2);
    dr_2->Draw("PE");
    h11_2->Draw("same PE");
    leg->Draw("same");

    res=h11_2->GetRMS()*0.57735027;
    res1=dr_2->GetRMS()*0.57735027;
    getRes(res,h11_2);
    getRes(res1,dr_2);
   Res->SetBinContent(2,res);
    Res_mm->SetBinContent(2,res1);
    sprintf(label,"#sigma_{b}=%1.4f",res);
    sprintf(label1,"#sigma_{c}=%1.4f",res1);
    lat.DrawLatex(-0.5.,dr_2->GetMaximum()*0.9.1,"#it{p}_{T}#in[1.0,1.2] [GeV]");
    lat.DrawLatex(1.,dr_2->GetMaximum()*0.7,label);
    lat.DrawLatex(1.,dr_2->GetMaximum()*0.6,label1);
    c1->cd(3);
    dr_3->Draw("PE");
    h11_3->Draw("same PE");
    leg->Draw("same");
 
    res=h11_3->GetRMS()*0.57735027;
    res1=dr_3->GetRMS()*0.57735027;
    getRes(res,h11_3);
    getRes(res1,dr_3);
    Res->SetBinContent(3,res);
    Res_mm->SetBinContent(3,res1);
    sprintf(label,"#sigma_{b}=%1.4f",res);
    sprintf(label1,"#sigma_{c}=%1.4f",res1);
    lat.DrawLatex(-0.5.,dr_3->GetMaximum()*0.9.1,"#it{p}_{T}#in[1.2,1.5] [GeV]");
    lat.DrawLatex(1.,dr_3->GetMaximum()*0.7,label);
    lat.DrawLatex(1.,dr_3->GetMaximum()*0.6,label1);

    c1->cd(4);
    dr_4->Draw("PE");
    h11_4->Draw("same PE");
    leg->Draw("same");

    res=h11_4->GetRMS()*0.57735027;
    res1=dr_4->GetRMS()*0.57735027;
    getRes(res,h11_4);
    getRes(res1,dr_4);
    Res->SetBinContent(4,res);
    Res_mm->SetBinContent(4,res1);
    sprintf(label,"#sigma_{b}=%1.4f",res);
    sprintf(label1,"#sigma_{c}=%1.4f",res1);
    lat.DrawLatex(-0.5.,dr_4->GetMaximum()*0.9.1,"#it{p}_{T}#in[1.5,2.0] [GeV]");
    lat.DrawLatex(1.,dr_4->GetMaximum()*0.7,label);
    lat.DrawLatex(1.,dr_4->GetMaximum()*0.6,label1);
    c1->cd(5);
    dr_5->Draw("PE");
    h11_5->Draw("same PE");
    leg->Draw("same");

    res=h11_5->GetRMS()*0.57735027;
    res1=dr_5->GetRMS()*0.57735027;
    getRes(res,h11_5);
    getRes(res1,dr_5);
    Res->SetBinContent(5,res);
    Res_mm->SetBinContent(5,res1);
    sprintf(label,"#sigma_{b}=%1.4f",res);
    sprintf(label1,"#sigma_{c}=%1.4f",res1);
    lat.DrawLatex(-0.5.,dr_5->GetMaximum()*0.9.1,"#it{p}_{T}#in[2.0,2.5] [GeV]");
    lat.DrawLatex(1.,dr_5->GetMaximum()*0.7,label);
    lat.DrawLatex(1.,dr_5->GetMaximum()*0.6,label1);
    c1->cd(6);
    dr_6->Draw("PE");
    h11_6->Draw("same PE");
    leg->Draw("same");

    res=h11_6->GetRMS()*0.57735027;
    res1=dr_6->GetRMS()*0.57735027;
    getRes(res,h11_6);
    getRes(res1,dr_6);
    Res->SetBinContent(6,res);
    Res_mm->SetBinContent(6,res1);
    sprintf(label,"#sigma_{b}=%1.4f",res);
    sprintf(label1,"#sigma_{c}=%1.4f",res1);
    lat.DrawLatex(-0.5.,dr_6->GetMaximum()*0.9.1,"#it{p}_{T}#in[2.5,3.5] [GeV]");
    lat.DrawLatex(1.,dr_6->GetMaximum()*0.7,label);
    lat.DrawLatex(1.,dr_6->GetMaximum()*0.6,label1);
    c1->cd(7);
    dr_7->Draw("PE");
    h11_7->Draw("same PE");
    leg->Draw("same");

    res=h11_7->GetRMS()*0.57735027;
    res1=dr_7->GetRMS()*0.57735027;
    getRes(res,h11_7);
    getRes(res1,dr_7);
    Res->SetBinContent(7,res);
    Res_mm->SetBinContent(7,res1);
    sprintf(label,"#sigma_{b}=%1.4f",res);
    sprintf(label1,"#sigma_{c}=%1.4f",res1);
    lat.DrawLatex(-0.5.,dr_7->GetMaximum()*0.9.1,"#it{p}_{T}#in[3.5,4.5] [GeV]");
    lat.DrawLatex(1.,dr_7->GetMaximum()*0.7,label);
    lat.DrawLatex(1.,dr_7->GetMaximum()*0.6,label1);
    c1->cd(8);
    dr_8->Draw("PE");
    h11_8->Draw("same PE");
    leg->Draw("same");

    res=h11_8->GetRMS()*0.57735027;
    res1=dr_8->GetRMS()*0.57735027;
    getRes(res,h11_8);
    getRes(res1,dr_8);
    Res->SetBinContent(8,res);
    Res_mm->SetBinContent(8,res1);
    sprintf(label,"#sigma_{b}=%1.4f",res);
    sprintf(label1,"#sigma_{c}=%1.4f",res1);
    lat.DrawLatex(-0.5.,dr_8->GetMaximum()*0.9.1,"#it{p}_{T}#in[4.5,5.5] [GeV]");
    lat.DrawLatex(1.,dr_8->GetMaximum()*0.7,label);
    lat.DrawLatex(1.,dr_8->GetMaximum()*0.6,label1);
    c1->cd(9);
    dr_9->Draw("PE");
    h11_9->Draw("same PE");
    leg->Draw("same");

    res=h11_9->GetRMS()*0.57735027;
    res1=dr_9->GetRMS()*0.57735027;
    getRes(res,h11_9);
    getRes(res1,dr_9);
    Res->SetBinContent(9,res);
    Res_mm->SetBinContent(9,res1);
    sprintf(label,"#sigma_{b}=%1.4f",res);
    sprintf(label1,"#sigma_{c}=%1.4f",res1);
    lat.DrawLatex(-0.5.,dr_9->GetMaximum()*0.9.1,"#it{p}_{T}#in[5.5,8.5] [GeV]");
    lat.DrawLatex(1.,dr_9->GetMaximum()*0.7,label);
    lat.DrawLatex(1.,dr_9->GetMaximum()*0.6,label1);
    for(int i=1;i<10;i++){
	Res->SetBinError(i,0.000001);
	Res_mm->SetBinError(i,0.000001);	
    }
   TCanvas *c3 = new TCanvas("c3","res");
    Res->GetXaxis()->SetTitle("#it{p}_{T} [GeV]");
    Res->GetYaxis()->SetTitle("#phi Resolution");   
    Res->GetYaxis()->SetRangeUser(0,2);   
    Res_mm->SetMarkerColor(kRed);
    Res_mm->SetLineColor(kRed);
    Res->Draw("PE");
    Res_mm->Draw("PE same");
    leg->Draw("same");
    TFile fi(file,"RECREATE");
    Res->Write();
    Res_mm->Write();  
    Cos->Write("Cos");
}
void norm5(TH1F *h){
    h->GetXaxis()->SetTitle("#Delta#phi");
    h->GetYaxis()->SetTitle("Arb. Units");
 
    //h->Rebin();
    double norm1 = h->Integral();
    int bins = h->GetNbinsX();
    for(int i=1; i<bins+1;i++){
	double temp = h->GetBinContent(i);
	double width = h->GetBinWidth(i);
	double err = h->GetBinError(i);
	h->SetBinContent(i,temp/norm1);
	h->SetBinError(i,err/norm1);
    }
    h->GetYaxis()->SetRangeUser(0.00001,h->GetMaximum()*1.4);
}
void getRes(double res, TH1F* h){
    TF1 f("f","gaus(0)",-2,2);
    f.SetParameter(0,0.5);
    f.SetParameter(1,0.);   
    f.SetParameter(2,0.02);
    //h->Fit("f","R");
    //res=f.GetParameter(2);
}
