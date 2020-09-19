void Compare_Bfrac_v2()
{
  bool DRAWING = true;
  if(DRAWING) {
    gStyle->SetPadLeftMargin(0.14);
    gStyle->SetPadRightMargin(0.04);
    gStyle->SetPadTopMargin(0.09);
    gStyle->SetPadBottomMargin(0.12);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(1);
    gStyle->SetTitleSize(0.1);
    //gStyle->SetOptLogy();
    gStyle->SetOptFit(1);

  }
  cout<< "draw previous and new "<<endl;
  Int_t colz[] = {kRed, kViolet, kOrange, kSpring, kBlue, kCyan, kRed+2, kViolet+2, kOrange+2, kYellow+1};

  const int nk=9;
  TString nkName[]={"Output_tunePtBin_xz_noLc", "Output_tunePtBin_xz","Output_tunePtBin_yj_fastSimChange","Output_tunePtBin_yj_purityChange","Output_tunePtBin_yj_purityChange_InitChange",
    "Output_tunePtBin_yj_hadronChange_moreStat_v2","Output_tunePtBin_yj_allChange_moreStat_v2_InitChange",
    "Output_tunePtBin_yj_hadron_fastSimChange",
    "Output_tunePtBin_yj_hadron_purityChange",  "Output_tunePtBin_yj_allChange_woPurity"};
  TString nLName[]={"STAR Au+Au HFT QM17", "xz", "yj_HF","yj_Purity","yj_Purity_InitChange",
    "yj_Hadron", "yj_Hadron_HF_Purity_moreStat_InitChange","yj_Hadron_HF_Purity_InitChange",
    "yj_Hadron_HF", "yj_Hadron_Purity","yj_Hadron_HF_Purity(2bin)"
  };
  TFile * file[nk];
  TH1F *hist[nk];
  /*
  TFile * file_xz = new TFile("Output_tunePtBin_xz/Fit_B_fraction_DCA_0.root","READ");
  TFile * file_yj_allH = new TFile("Output_tunePtBin_yj_allH/Fit_B_fraction_DCA_0.root","READ");
  TFile * file_yj_fastSimChange = new TFile("Output_tunePtBin_yj_fastSimChange/Fit_B_fraction_DCA_0.root","READ");
  TFile * file_yj_purityChange = new TFile("Output_tunePtBin_yj_purityChange/Fit_B_fraction_DCA_0.root","READ");
  TFile * file_yj_allChange_woPurity = new TFile("Output_tunePtBin_yj_allChange_woPurity/Fit_B_fraction_DCA_0.root","READ");
  TFile * file_yj_allChange = new TFile("Output_tunePtBin_yj_allChange/Fit_B_fraction_DCA_0.root","READ");
  */
  
  TLegend *legend=new TLegend(0.15,0.7,0.37,0.88);
  legend ->SetBorderSize(0);
  legend ->SetTextSize(0.025);
  legend ->SetFillStyle(0);
  legend ->SetTextFont(62);
  TCanvas *c1=new TCanvas("c1","",500,500);
  
  for(auto i =0; i<7; i++){
    file[i] = new TFile(Form("%s/Fit_B_fraction_DCA_0.root", nkName[i].Data()), "READ");
    if(i==0) hist[i] = ( TH1F *)file[i]->Get("b_Fraction")->Clone(Form("bF_%s", nkName[i].Data()));
    else hist[i] = ( TH1F *)file[i]->Get("b_fraction_MB")->Clone(Form("bF_%s", nkName[i].Data()));
    hist[i]->SetMarkerColor(colz[i]);
    hist[i]->SetLineColor(colz[i]);
    hist[i]->SetMarkerStyle(24+i);
    legend->AddEntry(hist[i],Form("bF_%s", nLName[i].Data()),"lp");
    if(i==0){
      hist[i]->GetXaxis()->SetTitle("p_{T}");
      hist[i]->GetYaxis()->SetTitle("N_{Be}/(N_{Be}+N_{De})");
      hist[i]->GetYaxis()->SetRangeUser(1e-4,1.2);
      hist[i]->Draw();
    }
    
    hist[i]->Draw("same");
  }
  legend->Draw("same");
  
  c1->SaveAs("Compare_Bfrac_v9.pdf");
  /*
  TH1F *xz_b_frac=( TH1F *) file_xz->Get("b_fraction_MB")->Clone("b_fraction_MB_xz");
  TH1F *yj_allH=( TH1F *) file_yj_allH->Get("b_fraction_MB")->Clone("b_fraction_MB_yj_allH");
  TH1F *yj_fastSimChange=( TH1F *) file_yj_fastSimChange->Get("b_fraction_MB")->Clone("b_fraction_MB_yj_fastSimChange");
  TH1F *yj_purityChange=( TH1F *) file_yj_purityChange->Get("b_fraction_MB")->Clone("b_fraction_MB_yj_purityChange");
  TH1F *yj_allChange_woPurity=( TH1F *) file_yj_allChange_woPurity->Get("b_fraction_MB")->Clone("b_fraction_MB_yj_allChange_woPurity");
  TH1F *yj_allChange=( TH1F *) file_yj_allChange->Get("b_fraction_MB")->Clone("b_fraction_MB_yj_allChange");
*/
  
  /*
  
  xz_b_frac->SetMarkerColor(1);
  xz_b_frac->SetMarkerStyle(24);
  xz_b_frac->SetLineColor(1);

  yjallH_b_frac->SetMarkerColor(2);
  yjallH_b_frac->SetMarkerStyle(25);
  yjallH_b_frac->SetLineColor(2);

  yjallChange_b_frac->SetMarkerColor(4);
  yjallChange_b_frac->SetMarkerStyle(26);
  yjallChange_b_frac->SetLineColor(4);

  xz_b_frac->GetXaxis()->SetTitle("p_{T}");
  xz_b_frac->GetYaxis()->SetTitle("N_{Be}/(N_{Be}+N_{De})");
  xz_b_frac->GetYaxis()->SetRangeUser(1e-4,1);

  TLegend *legend=new TLegend(0.15,0.7,0.37,0.88);
  legend ->SetBorderSize(0);
  legend ->SetTextSize(0.04);
  legend ->SetFillStyle(0);
  legend ->SetTextFont(62);
  legend->AddEntry(xz_b_frac,"xz","lp");
  legend->AddEntry(yjallH_b_frac,"yj_hadron_changed","lp");
  legend->AddEntry(yjallChange_b_frac,"yj_all_changed","lp");

  TCanvas *c1=new TCanvas("c1","",500,500);
  xz_b_frac->Draw(); // blue
  yjallH_b_frac->Draw("same"); // black
  yjallChange_b_frac->Draw("same");
  legend->Draw("same");
  c1->SaveAs("Compare_Bfrac.pdf");*/
   
  return ;

}

