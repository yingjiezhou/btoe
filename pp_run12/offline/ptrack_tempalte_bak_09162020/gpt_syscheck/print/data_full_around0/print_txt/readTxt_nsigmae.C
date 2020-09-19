 TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t      textAngle=0);
void readTxt_nsigmae(const char* eType="LikeSign", const char* efile="LikeSign", bool bin1  =true, bool gptlow  =true, bool bNINc = true){
  gStyle->SetOptStat(0);
  
  float lowpt = 2.5;
  float highpt = 3.5;
  if(!bin1){
    lowpt = 3.5;
    highpt = 4.5;
  }
  float lowgpt = 0.2;
  float highgpt = 0.3;

  if(!gptlow){
    lowgpt = 0.3;
    highgpt = 0.5;
  }
  
  TTree *tree = new TTree("tree", "tree");
  if(bNINc){
    if(! tree->ReadFile(Form("%s", efile), "deltaEta/F:deltaphi/F:RunNumber/F:EventNumber/F:ElectronCharge/F:pCharge/F:ElectronpT/F:gpt/F:ElectronEta/F:pEta/F:ElectronPhi/F:pPhi/F:HadronCharge/F:HadronpT/F:HadronEta/F:HadronPhi/F:hpion/F:hkaon/F:hproton/F:helectron/F", ' ')){
      std::cerr << "[Error] Failed to read the txtfile." << std::endl;
      return 1;
    }
  }
  else if(!bNINc){
    if(! tree->ReadFile(Form("%s", efile), "deltaEta/F:deltaphi/F:RunNumber/F:EventNumber/F:ElectronCharge/F:ElectronpT/F:ElectronEta/F:ElectronPhi/F:HadronCharge/F:HadronpT/F:HadronEta/F:HadronPhi/F:hpion/F:hkaon/F:hproton/F:helectron/F", ' ')){
      std::cerr << "[Error] Failed to read the inc txtfile." << std::endl;
      return 1;
    }
  }
  
  Float_t ppt = -1;
  Float_t ept  = -1;
  Float_t ne  = -1;
  
  tree->SetBranchAddress("helectron", &ne);
  tree->SetBranchAddress("ElectronpT", &ept);
  if(bNINc)tree->SetBranchAddress("gpt", &ppt);
  
  auto c = new TCanvas();
  c->SetLogy();
  
  auto leg = new TLegend(0.5, 0.5, 0.85, 0.85);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  
  tree->Draw("helectron>>horg");
  tree->Draw("helectron>>hcut", "abs(deltaEta) < 0.05 && abs(deltaphi) < 0.05", "same pe");
  TH1F *horg = (TH1F*)gDirectory->Get("horg");
  TH1F *hcut = (TH1F*)gDirectory->Get("hcut");
  hcut->SetLineColor(kRed);
  hcut->SetTitle("hadron track n#sigma_{e}");
  horg->SetTitle("hadron track n#sigma_{e}");
  
  leg->AddEntry("horg", "no cut on #Delta#eta/#Delta#phi", "l");
  leg->AddEntry("hcut", "|#Delta#eta,#Delta#phi|<0.05", "pe");
  leg->Draw("same");
  drawLatex(0.18, 0.88, Form("%s e-h", eType), 22, 0.04, 1);
  if(bNINc) drawLatex(0.18, 0.8, Form("%.1f<gpt<%.1f, hpt>0.3", lowgpt, highgpt), 22, 0.04, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.3", lowpt, highpt), 22, 0.04, 1);
  c->SaveAs(Form("%s_%d_%d.pdf", eType, bin1, gptlow));
  
  tree->ResetBranchAddresses(); // detach from local variables
  return 1;
}

TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t      textAngle=0)
{
  TLatex *latex = new TLatex(x,y,text.Data());
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->SetTextAngle(textAngle);
  latex->Draw("same");
  return latex;
}
