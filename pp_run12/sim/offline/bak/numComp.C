void numComp(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  gStyle->SetOptStat(0);
  auto fza = new TFile("input/pythia_npe_tree_Feb4.root", "READ"); // zach
  auto fyj = new TFile("input/pythia_npe_tree_Feb26.root", "READ"); // new CR
  
  Float_t lowpt[14] = {2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5};
  Float_t highpt[14] = {3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 18.5};
  
  Double_t hept;
  Double_t hepty;
  auto hcomp = new TH1D("hcomp", "", 20, 0.5, 20.5);

  for(auto i=0; i<9; i++){
    hept = ((TH1D*)fza->Get(Form("hept_%d", i)))->Integral();
    hepty = ((TH1D*)fyj->Get(Form("hept_%d", i)))->Integral();
    hcomp->SetBinContent(i+3, hepty/hept);
    hcomp->SetBinError(i+3, 1e-8);
    cout<<"yj/za ratio is: "<<hepty/hept<<endl;
  }

  auto fc = new TF1("fc", "1", 0.5, 20.5);
  fc->SetLineColor(kRed);
  hcomp->GetXaxis()->SetTitle("p_{T} bin");
  hcomp->GetYaxis()->SetTitle("number of electron ratio yj/zach");
  hcomp->GetYaxis()->SetRangeUser(0, 5);
  auto a = new TCanvas();
  hcomp->Draw("PE");
  fc->Draw("same");
  a->SaveAs("NumE_ratio.pdf");
}
