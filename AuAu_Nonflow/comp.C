{
    gROOT->ProcessLine(".x ~/myStyle.C");
    TGaxis::SetMaxDigits(3);
    auto *fb = new TFile("ypw20190607_fms_b/fullRange/NpeBHcorr_FMS_full.root", "READ");
    auto *fc = new TFile("ypw20190607_fms_c/fullRange/NpeCHcorr_FMS_allpT.root", "READ");
    auto *hb = (TH1F *)fb->Get("hPTTrkE_gen");
    auto *hc = (TH1F *)fc->Get("hPTTrkE_gen");
    TCanvas *c11 = new TCanvas ("c11","c11");
    c11->SetLogy();
    hb->SetLineColor(kRed+2);
    hb->SetMarkerColor(kRed+2);
    hc->SetLineColor(kBlue+2);
    hc->SetMarkerColor(kBlue+2);
    TLegend *leg = new TLegend(0.5,0.5,0.9,0.9);
    leg->AddEntry(hc,"#it{c}#rightarrow#it{e}X","lp");
    leg->AddEntry(hb,"#it{b}#rightarrow#it{e}X","lp");

    hc->Scale(1./hc->Integral());
    hb->Scale(1./hb->Integral());
    hc->Draw();
    hb->Draw("same");
    leg->Draw("same");

}
