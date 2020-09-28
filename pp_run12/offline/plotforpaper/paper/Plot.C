void norm(TH1F *h,double n);
void Plot(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  gStyle->SetPalette(51);
  // old pytiha + Yingjie's pythia
  TFile *f1 = new TFile("PYTHIA_dndphi_ppy06.root","READ");
  auto phy_pyhia_D_0 = (TH1F*) f1->Get("phy_pyhia_D_0");
  auto phy_pyhia_D_1 = (TH1F*) f1->Get("phy_pyhia_D_1");
  auto phy_pyhia_D_2 = (TH1F*) f1->Get("phy_pyhia_D_2");
  auto phy_pyhia_D_3 = (TH1F*) f1->Get("phy_pyhia_D_3");
  auto phy_pyhia_B_0 = (TH1F*) f1->Get("phy_pyhia_B_0");
  auto phy_pyhia_B_1 = (TH1F*) f1->Get("phy_pyhia_B_1");
  auto phy_pyhia_B_2 = (TH1F*) f1->Get("phy_pyhia_B_2");
  auto phy_pyhia_B_3 = (TH1F*) f1->Get("phy_pyhia_B_3");
  phy_pyhia_D_0->SetLineColor(kMagenta);
  phy_pyhia_D_1->SetLineColor(kMagenta);
  phy_pyhia_D_2->SetLineColor(kMagenta);
  phy_pyhia_D_3->SetLineColor(kMagenta);
  phy_pyhia_B_0->SetLineColor(kCyan);
  phy_pyhia_B_1->SetLineColor(kCyan);
  phy_pyhia_B_2->SetLineColor(kCyan);
  phy_pyhia_B_3->SetLineColor(kCyan);
  TH1D *hNC[9];
  TH1D *hNB[9];
  TH1D *hB[9];
  TH1D *hC[9];
  TFile *f2 = new TFile("pythia_npe_tree_May18.root","READ");
  hC[0] = (TH1D*) f2->Get("hdPhiRawce_0");
  hC[1] = (TH1D*) f2->Get("hdPhiRawce_1");
  hC[2] = (TH1D*) f2->Get("hdPhiRawce_2");
  hC[3] = (TH1D*) f2->Get("hdPhiRawce_3");
  hC[4] = (TH1D*) f2->Get("hdPhiRawce_4");
  hC[5] = (TH1D*) f2->Get("hdPhiRawce_5");
  hC[6] = (TH1D*) f2->Get("hdPhiRawce_6");
  hC[7] = (TH1D*) f2->Get("hdPhiRawce_7");
  hNC[0] =(TH1D*)f2->Get("ceEventTally_0");
  hNC[1] =(TH1D*)f2->Get("ceEventTally_1");
  hNC[2] =(TH1D*)f2->Get("ceEventTally_2");
  hNC[3] =(TH1D*)f2->Get("ceEventTally_3");
  hNC[4] =(TH1D*)f2->Get("ceEventTally_4");
  hNC[5] =(TH1D*)f2->Get("ceEventTally_5");
  hNC[6] =(TH1D*)f2->Get("ceEventTally_6");
  hNC[7] =(TH1D*)f2->Get("ceEventTally_7");
  
  hB[0] = (TH1D*) f2->Get("hdPhiRawbe_0");
  hB[1] = (TH1D*) f2->Get("hdPhiRawbe_1");
  hB[2] = (TH1D*) f2->Get("hdPhiRawbe_2");
  hB[3] = (TH1D*) f2->Get("hdPhiRawbe_3");
  hB[4] = (TH1D*) f2->Get("hdPhiRawbe_4");
  hB[5] = (TH1D*) f2->Get("hdPhiRawbe_5");
  hB[6] = (TH1D*) f2->Get("hdPhiRawbe_6");
  hB[7] = (TH1D*) f2->Get("hdPhiRawbe_7");
  hNB[0] =(TH1D*)f2->Get("beEventTally_0");
  hNB[1] =(TH1D*)f2->Get("beEventTally_1");
  hNB[2] =(TH1D*)f2->Get("beEventTally_2");
  hNB[3] =(TH1D*)f2->Get("beEventTally_3");
  hNB[4] =(TH1D*)f2->Get("beEventTally_4");
  hNB[5] =(TH1D*)f2->Get("beEventTally_5");
  hNB[6] =(TH1D*)f2->Get("beEventTally_6");
  hNB[7] =(TH1D*)f2->Get("beEventTally_7");
  for(int i = 0; i<7;i++){
    hB[i]->Scale(1./hNB[i]->GetBinContent(1));
    hC[i]->Scale(1./hNC[i]->GetBinContent(1));
  }
  //////
  
  
  TFile *f = new TFile("out.root","READ");
  auto hJpsi_PT = (TH1F*) f->Get("hJpsi_PT");
  auto hHF_PT = (TH1F*) f->Get("hHF_PT");
  auto hNPE_PT = (TH1F*) f->Get("hNPE_PT");
  auto hHFB_PT = (TH1F*) f->Get("hHFB_PT");
  auto hHFC_PT = (TH1F*) f->Get("hHFC_PT");
  auto hJpsi = (TH2F*) f->Get("hJpsi");
  auto hHF = (TH2F*) f->Get("hHF");
  auto hNPE = (TH2F*) f->Get("hNPE");
  auto hHFB = (TH2F*) f->Get("hHFB");
  auto hHFC = (TH2F*) f->Get("hHFC");
  TCanvas *c1 = new TCanvas("c1","c1");
  hHF_PT->Draw("PE");
  hHFC_PT->SetLineColor(kRed);
  hHFB_PT->SetLineColor(kBlue);
  hHFB_PT->Draw("hist same");
  hHFC_PT->Draw("hist same");
  hJpsi_PT->DrawClone("hist same");
//  TCanvas *c11 = new TCanvas("c11","c11");
//  hJpsi_PT->Divide(hNPE_PT);
//  hJpsi_PT->DrawClone("hist same");
  int const nbin =7;
  double binning[nbin+1]={2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5};
  
  TH1F *hNPE_Corr[nbin];
  TH1F *hHF_Corr[nbin];
  TH1F *hHFC_Corr[nbin];
  TH1F *hHFB_Corr[nbin];
  TH1F *hJpsi_Corr[nbin];
  TCanvas *c2 = new TCanvas("c2","c2",1200,800);
  c2->Divide(3,2);
//  TCanvas *c22 = new TCanvas("c22","c22",1200,800);
//  c22->Divide(3,2);
  
  for(int i = 2; i< nbin+1; i++){
    hNPE->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    int bin1= hNPE_PT->GetXaxis()->FindBin(binning[i-1]);
    int bin2= hNPE_PT->GetXaxis()->FindBin(binning[i]);
    char name[100];
    sprintf(name,"hNPE_Corr_%i",i);
    hNPE_Corr[i-1] = (TH1F*)hNPE->ProjectionY();hNPE_Corr[i-1]->SetName(name);
    norm( hNPE_Corr[i-1],hNPE_PT->Integral(bin1,bin2));
    
    hHF->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    sprintf(name,"hHF_Corr_%i",i);
    hHF_Corr[i-1] = (TH1F*)hHF->ProjectionY();hHF_Corr[i-1]->SetName(name);
    norm( hHF_Corr[i-1],hHF_PT->Integral(bin1,bin2));
    
    hHFB->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    bin1= hHF_PT->GetXaxis()->FindBin(binning[i-1]);
    bin2= hHF_PT->GetXaxis()->FindBin(binning[i]);
    sprintf(name,"hHFB_Corr_%i",i);
    hHFB_Corr[i-1] = (TH1F*)hHFB->ProjectionY();hHFB_Corr[i-1]->SetName(name);
    norm(hHFB_Corr[i-1],hHFB_PT->Integral(bin1,bin2));
    hHFB_Corr[i-1]->SetLineColor(kBlue);
    hHFB_Corr[i-1]->SetMarkerColor(kBlue);
    hHFC->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    sprintf(name,"hHFC_Corr_%i",i);
    hHFC_Corr[i-1] = (TH1F*)hHFC->ProjectionY();hHFC_Corr[i-1]->SetName(name);
    norm(hHFC_Corr[i-1],hHFC_PT->Integral(bin1,bin2));
    hHFC_Corr[i-1]->SetLineColor(kRed);
    hHFC_Corr[i-1]->SetMarkerColor(kRed);
    hJpsi->GetXaxis()->SetRangeUser(binning[i-1],binning[i]);
    sprintf(name,"hJpsi_Corr_%i",i);
    hJpsi_Corr[i-1] = (TH1F*)hJpsi->ProjectionY();hJpsi_Corr[i-1]->SetName(name);
    norm(hJpsi_Corr[i-1],hJpsi_PT->Integral(bin1,bin2));
    hJpsi_Corr[i-1]->SetLineColor(1);
    
    
    
    c2->cd(i-1);//change to i
    //	hHF_Corr[i-1]->Rebin();
    //	hHFB_Corr[i-1]->Rebin();
    //	hHFC_Corr[i-1]->Rebin();
    
    hHF_Corr[i-1]->GetXaxis()->SetTitle("#Delta#phi");
    hHF_Corr[i-1]->GetYaxis()->SetTitle("(1/N) dN/d#Delta#phi");
    hHF_Corr[i-1]->GetYaxis()->SetRangeUser(0, hHF_Corr[i-1]->GetMaximum()*1.3);
    hHF_Corr[i-1]->Draw("PE");
//    hHFC_Corr[i-1]->DrawClone("PE same");
    hHFB_Corr[i-1]->Draw("PE same");
    //hJpsi_Corr[i-1]->DrawClone("hist same");
    
    /*	if(i==4)phy_pyhia_B_0->Draw("hist same");
     if(i==4)phy_pyhia_D_0->Draw("hist same");
     if(i==5)phy_pyhia_B_1->Draw("hist same");
     if(i==5)phy_pyhia_D_1->Draw("hist same");
     if(i==6)phy_pyhia_B_2->Draw("hist same");
     if(i==6)phy_pyhia_D_2->Draw("hist same");
     if(i==7)phy_pyhia_B_3->Draw("hist same");
     if(i==7)phy_pyhia_D_3->Draw("hist same");
     
     */
//    hB[i]->SetLineColor(kCyan);
//    hB[i]->DrawClone("same hist");
//    hC[i]->SetLineColor(kMagenta);
//    hC[i]->DrawClone("same hist");
    
//    if(i>3){
//      c22->cd(i-1);
//      /*if(i==4)hHFB_Corr[i-1]->Divide(phy_pyhia_B_0);
//       if(i==5)hHFB_Corr[i-1]->Divide(phy_pyhia_B_1);
//       if(i==6)hHFB_Corr[i-1]->Divide(phy_pyhia_B_2);
//       if(i==7)hHFB_Corr[i-1]->Divide(phy_pyhia_B_3);
//       if(i==4)hHFC_Corr[i-1]->Divide(phy_pyhia_D_0);
//       if(i==5)hHFC_Corr[i-1]->Divide(phy_pyhia_D_1);
//       if(i==6)hHFC_Corr[i-1]->Divide(phy_pyhia_D_2);
//       if(i==7)hHFC_Corr[i-1]->Divide(phy_pyhia_D_3);
//       */
//      hHFB_Corr[i-1]->Divide(hB[i-1]);
//      hHFC_Corr[i-1]->Divide(hC[i-1]);
//      hHFC_Corr[i-1]->Draw("hist same");
//      hHFB_Corr[i-1]->Draw("hist same");
//    }
  }
}
void norm(TH1F *h,double n){
  //h->Rebin();
  for(int i = 1; i <h->GetNbinsX()+1;i++){
    double val = h->GetBinContent(i);
    h->SetBinContent(i,val/n);
    h->SetBinError(i,sqrt(val)/n);
  }
}
