void fitScalefactor() {
    double pT_HT0[] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5};
    double A0_HT0[] = {1.061, 1.010, 1.043, 1.041, 0.847};
    double A0ErrU_HT0[] = {0.034, 0.030, 0.034, 0.057, 0.083};
    double A0ErrD_HT0[] = {0.034, 0.030, 0.034, 0.057, 0.083};
    
    
    TH1F *hA0_HT0 = new TH1F("hA0_HT0", "", 5, pT_HT0);
    for(int i=0; i<5; i++) {
        hA0_HT0->SetBinContent(i+1, A0_HT0[i]);
        hA0_HT0->SetBinError(i+1, A0ErrU_HT0[i]);
    }
    
    hA0_HT0->Draw("E1");
    hA0_HT0->GetYaxis()->SetRangeUser(0, 1.2);
    hA0_HT0->Fit("pol0", "", "R", 2.5, 7.5);
    //A0 of fitting value (HT0): 1.02777 +- 0.0174232
    
    
    
    double pT_HT2[] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5};
    double A0_HT2[] = {1.036, 1.067, 1.079, 1.036, 0.932, 0.713, 0.783, 1.129};
    double A0ErrU_HT2[] = {0.041, 0.021, 0.022, 0.030, 0.049, 0.060, 0.121, 0.159};
    double A0ErrD_HT2[] = {0.041, 0.021, 0.022, 0.030, 0.049, 0.055, 0.121, 0.159};
    
    TH1F *hA0_HT2 = new TH1F("hA0_HT2", "", 8, pT_HT2);
    for(int i=0; i<8; i++) {
        hA0_HT2->SetBinContent(i+1, A0_HT2[i]);
        hA0_HT2->SetBinError(i+1, A0ErrU_HT2[i]);
    }
    
    hA0_HT2->Draw("E1");
    hA0_HT2->GetYaxis()->SetRangeUser(0, 1.2);
    hA0_HT2->Fit("pol0", "", "R", 3.5, 9.5);
    //A0 of fitting value (HT2): 1.03988 +- 0.0121861
    
    
    
}
