float pi = 3.1415826;

TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t textAngle=0);
Float_t correct_dPhi(Float_t dP);
void PrintInc_split(){
  gROOT->ProcessLine(".x ~/myStyle.C");
  auto f  = new TFile("rootfile/default_gpt_dist_2d.root", "READ");
  TNtuple *nf = (TNtuple*)f->Get("incCheck");
  Int_t entries = (Int_t)nf->GetEntries();
  char *ptbin = "1";
  char *filename = "zoom_inc_splitcut_tight";
  bool isZoom = kTRUE;
  
  float lowpt = 2.5;
  float highpt = 3.5;
  
  //  int RunNumber,EventNumber;
  float RunNumber,EventNumber;
  //  bool isULS;
  float isULS;
  float gpt,ElectronCharge,ElectronpT,ElectronEta,ElectronPhi,HadronCharge,HadronpT,HadronEta,      HadronPhi,pCharge,pEta,pPhi,hpion,hkaon,hproton,helectron,trig,nsigmae;
  
  nf->SetBranchAddress("RunNumber",&RunNumber);
  nf->SetBranchAddress("EventNumber",&EventNumber);
  //  nf->SetBranchAddress("isULS",&isULS);
  //  nf->SetBranchAddress("gpt",&gpt);
  nf->SetBranchAddress("ElectronCharge",&ElectronCharge);
  nf->SetBranchAddress("ElectronpT",&ElectronpT);
  nf->SetBranchAddress("ElectronEta",&ElectronEta);
  nf->SetBranchAddress("ElectronPhi",&ElectronPhi);
  nf->SetBranchAddress("HadronCharge",&HadronCharge);
  nf->SetBranchAddress("HadronpT",&HadronpT);
  nf->SetBranchAddress("HadronEta",&HadronEta);
  nf->SetBranchAddress("HadronPhi",&HadronPhi);
  //  nf->SetBranchAddress("pCharge",&pCharge);
  //  nf->SetBranchAddress("pEta",&pEta);
  //  nf->SetBranchAddress("pPhi",&pPhi);
  nf->SetBranchAddress("hpion",&hpion);
  nf->SetBranchAddress("hkaon",&hkaon);
  nf->SetBranchAddress("hproton",&hproton);
  nf->SetBranchAddress("helectron",&helectron);
  nf->SetBranchAddress("trig",&trig);
  nf->SetBranchAddress("nsigmae",&nsigmae);
  
  FILE* finc;
  
  finc = fopen(Form("print/inc_%sptbin_%s.txt",ptbin, filename),"w");
  
  auto mh3DelPhiPhotLS = new TH3F("mh3DelPhiPhotLS","",100,-0.1,0.1,80,-0.1,0.1, 200,0,20);
  mh3DelPhiPhotLS->Sumw2();
  auto mh3DelPhiPhotLS2 = new TH3F("mh3DelPhiPhotLS2","",100,-0.1,0.1,80,-0.1,0.1, 200,0,20);
  mh3DelPhiPhotLS2->Sumw2();
  
  auto mh3DelPhiPhotUS = new TH3F("mh3DelPhiPhotUS","",100,-0.1,0.1,80,-0.1,0.1, 200,0,20);
  mh3DelPhiPhotUS->Sumw2();
  auto mh3DelPhiPhotUS2 = new TH3F("mh3DelPhiPhotUS2","",100,-0.1,0.1,80,-0.1,0.1, 200,0,20);
  mh3DelPhiPhotUS2->Sumw2();
  
  //    auto mh3DelPhiPhotLS = new TH3F("mh3DelPhiPhotLS","",600,-3.14,3.14,400,-2,2,200,0,20);
  //    mh3DelPhiPhotLS->Sumw2();
  //    auto mh3DelPhiPhotLS2 = new TH3F("mh3DelPhiPhotLS2","",600,-3.14,3.14,400,-2,2, 200,0,20);
  //    mh3DelPhiPhotLS2->Sumw2();
  //
  //    auto mh3DelPhiPhotUS = new TH3F("mh3DelPhiPhotUS","",600,-3.14,3.14,400,-2,2, 200,0,20);
  //    mh3DelPhiPhotUS->Sumw2();
  //    auto mh3DelPhiPhotUS2 = new TH3F("mh3DelPhiPhotUS2","",600,-3.14,3.14,400,-2,2, 200,0,20);
  //    mh3DelPhiPhotUS2->Sumw2();
  
  
  for (Int_t ki=1;ki<entries;ki++)
  {
    nf->GetEntry(ki);
    if(trig == 2.) continue;
    
    bool isIneta=kFALSE;
    bool isInphi=kFALSE;
    bool ispt1 = kFALSE;
    bool isE = kFALSE;
    bool isHE = kFALSE;
    float cute = -0.1;
    float pcute = 0.1;
    
    if(ElectronpT>lowpt && ElectronpT<highpt) ispt1 = kTRUE;
    if(!ispt1) continue;
    
    if((ElectronEta-HadronEta)>-0.1 && (ElectronEta-HadronEta)<0.1)isIneta = kTRUE;
    if(correct_dPhi(ElectronPhi-HadronPhi)>-0.1 && correct_dPhi(ElectronPhi-HadronPhi)< 0.1)isInphi = kTRUE;
    if((!isInphi || !isIneta)&& isZoom) continue;
    
    if(helectron>-2 && helectron<3) isE = kTRUE;
    if((ElectronEta-HadronEta)>cute && (ElectronEta-HadronEta)<pcute && correct_dPhi(ElectronPhi-HadronPhi)>cute && correct_dPhi(ElectronPhi-HadronPhi)< pcute)isHE = kTRUE;
    if(isE && isHE) continue;
    
    fprintf(finc,"%9.4f %9.4f %.f %8.f %2.f %5.2f %5.2f %5.2f %2.f %5.2f %5.2f %5.2f %8.2f %8.2f %9.2f %8.2f\n", ElectronEta-HadronEta, correct_dPhi(ElectronPhi-HadronPhi),RunNumber,EventNumber,ElectronCharge, ElectronpT,ElectronEta,ElectronPhi,HadronCharge,HadronpT,HadronEta,HadronPhi,hpion, hkaon,hproton,helectron);
    mh3DelPhiPhotUS2->Fill(correct_dPhi(ElectronPhi-HadronPhi), ElectronEta-HadronEta, ElectronpT);
  }
  
  auto r1d =mh3DelPhiPhotUS2->GetZaxis()->FindBin(lowpt);
  auto r1u =mh3DelPhiPhotUS2->GetZaxis()->FindBin(highpt);
  
  mh3DelPhiPhotLS2->GetZaxis()->SetRange(r1d, r1u-1);
  mh3DelPhiPhotUS2->GetZaxis()->SetRange(r1d, r1u-1);
  
  
  auto usgptr = (TH2D*)mh3DelPhiPhotUS2->Project3D("yx_gpt0305_us");
  //  auto usgptl = (TH2D*)mh3DelPhiPhotUS->Project3D("yx_gpt0203_us");
  
  //  auto lsgptr_phi = (TH1D*)lsgptr->ProjectionX("yx_gpt0305_ls_phi");
  //  auto lsgptr_eta = (TH1D*)lsgptr->ProjectionY("yx_gpt0305_ls_eta");
  auto usgptr_phi = (TH1D*)usgptr->ProjectionX("yx_gpt0305_us_phi"); //us
  auto usgptr_eta = (TH1D*)usgptr->ProjectionY("yx_gpt0305_us_eta");
  
  //  auto lsgptl_phi = (TH1D*)lsgptl->ProjectionX("yx_gpt0203_ls_phi");
  //  auto lsgptl_eta = (TH1D*)lsgptl->ProjectionY("yx_gpt0203_ls_eta");
  //  auto usgptl_phi = (TH1D*)usgptl->ProjectionX("yx_gpt0203_us_phi");
  //  auto usgptl_eta = (TH1D*)usgptl->ProjectionY("yx_gpt0203_us_eta");
  
  //=========================================================
  
  usgptr->GetYaxis()->SetTitle("#Delta#eta");
  usgptr->GetXaxis()->SetTitle("#Delta#phi");
  //  usgptl->GetYaxis()->SetTitle("#Delta#eta");
  //  usgptl->GetXaxis()->SetTitle("#Delta#phi");
  //=========================================================
  
  auto c1 = new TCanvas();
  //  c1->Divide(2, 2, 0, 0, 0);
  //  c1->Divide(2);
  //  c1->cd(1);
  usgptr->Draw("colz");
  drawLatex(0.18, 0.88, "Inclusive e-h", 22, 0.06, 1);
  //  drawLatex(0.18, 0.78, "0.2<gpt<0.3", 22, 0.06, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.3", lowpt, highpt), 22, 0.06, 1);
  
  //  c1->cd(2);
  //  usgptr->Draw("colz");
  //  drawLatex(0.18, 0.88, "Inclusive e-h", 22, 0.06, 1);
  //  drawLatex(0.18, 0.78, "0.3<gpt<0.5", 22, 0.06, 1);
  
  c1->SaveAs(Form("print/Print2D_%s_%s.pdf", ptbin, filename));
  //=========================================================
  usgptr_phi->GetXaxis()->SetTitle("#Delta#phi");
  
  auto c2 = new TCanvas(); // phi
  //  c2->Divide(2,1, 0.01, 0.01);
  //  c2->cd(1);
  usgptr_phi->Draw();
  drawLatex(0.18, 0.88, "Inclusive e-h", 22, 0.06, 1);
  //  drawLatex(0.18, 0.78, "0.2<gpt<0.3", 22, 0.06, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.3", lowpt, highpt), 22, 0.06, 1);
  
  //  c2->cd(2);
  //  usgptr_phi->Draw();
  //  drawLatex(0.18, 0.88, "Inclusive e-h", 22, 0.06, 1);
  //  drawLatex(0.18, 0.78, "0.3<gpt<0.5", 22, 0.06, 1);
  c2->SaveAs(Form("print/Print2D_phi_%s_%s.pdf", ptbin, filename));
  
  //=========================================================
  
  usgptr_eta->GetXaxis()->SetTitle("#Delta#eta");
  
  auto c22 = new TCanvas(); // phi
  //  //c22->Divide(2,2, 0, 0, 0);
  //  c22->Divide(2);
  //  c22->cd(1);
  usgptr_eta->Draw();
  drawLatex(0.18, 0.88, "Inclusive e-h", 22, 0.06, 1);
  //  drawLatex(0.18, 0.78, "0.2<gpt<0.3", 22, 0.06, 1);
  drawLatex(0.42, 0.88, Form("%.1f<trig_e<%.1f, hpt>0.3", lowpt, highpt), 22, 0.06, 1);
  
  //  c22->cd(2);
  //  usgptr_eta->Draw();
  //  drawLatex(0.18, 0.88, "Inclusive e-h", 22, 0.06, 1);
  //  drawLatex(0.18, 0.78, "0.3<gpt<0.5", 22, 0.06, 1);
  c22->SaveAs(Form("print/Print2D_eta_%s_%s.pdf", ptbin, filename));
  
  
}
Float_t correct_dPhi(Float_t dP)
{
  //  if(dP > TMath::Pi()) dP = dP - 2*TMath::Pi();
  //  if(dP < -TMath::Pi()) dP = dP + 2*TMath::Pi();
  //  return dP;
  
  if(dP > pi) dP = dP - 2*pi;
  if(dP < -pi) dP = dP + 2*pi;
  return dP;
  
}
TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex, Double_t textAngle=0)
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

