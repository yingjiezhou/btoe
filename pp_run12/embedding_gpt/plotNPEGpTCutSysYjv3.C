#include "ptbin.h"
#include "style.h"
void plotNPEGpTCutSysYjv3()
{
  setstyle();
  TLatex tx;
  tx.SetTextSize(0.07);
  tx.SetNDC();
  tx.SetTextFont(42);
  TLatex tx1;
  tx1.SetTextSize(0.06);
  tx1.SetNDC();
  tx1.SetTextFont(42);
  auto cc=Canvas("cc",0.15,0.03,0.15,0.06,0,0,0);
  TPDF *mypdf = new TPDF("result/NPEGpTCutSys.pdf",111);
  mypdf->Off();
  TFile *f;
  TH1F *hSigma,*hGpT,*hGpTSys,*hReceff,*hReceffSys,*hSys;
  TH2F *htmp;
  TH1F *hGpTDisEta[nPtBins],*hGpTDis[nPtBins],*hGpTDislike[nPtBins],*hGpTDisUK_K[nPtBins],*hGpTDisPi0[nPtBins],*hGpTDisPhoton[nPtBins], *heff[nPtBins];
  TLegend *lg;
  f=new TFile("rebin/Pi0Dalitz_hist.root");
  TH1F *InputNumberPi0Dalitz=(TH1F *)f->Get("hnTotalyCut");
  TH1F *EleNumberPi0Dalitz=(TH1F *)((TH2F *)f->Get("RcptPosEleSMD"))->ProjectionX("EleNumberPi0Dalitz");
  TH2F *hGpTvsptPi0  = (TH2F *)f->Get("RcptMeeSMD2");
  
  f=new TFile("rebin/EtaDalitz_hist.root");
  TH1F *InputNumberEtaDalitz=(TH1F *)f->Get("hnTotalyCut");
  TH1F *EleNumberEtaDalitz=(TH1F *)((TH2F *)f->Get("RcptPosEleSMD"))->ProjectionX("EleNumberEtaDalitz");
  TH2F *hGpTvsptEta  = (TH2F *)f->Get("RcptMeeSMD2");
  
  f=new TFile("rebin/Gamma_hist.root");
  TH1F *InputNumberGamma=(TH1F *)f->Get("hnTotalyCut");
  TH1F *EleNumberGamma=(TH1F *)((TH2F *)f->Get("RcptPosEleSMD"))->ProjectionX("EleNumberGamma");
  TH2F *hGpTvsptPhoton  = (TH2F *)f->Get("RcptMeeSMD2");
  
//  f=new TFile("shenghuiv2/NPE_HT0_forYingjie.root");
//  TH2F *hGpTvspt0  = (TH2F *)f->Get("hGpTPart");
//  TH2F *hGpTvsptlike0  = (TH2F *)f->Get("hGpTPartlike");
//
//  f=new TFile("shenghuiv2/NPE_HT2_forYingjie.root");
//  TH2F *hGpTvspt2  = (TH2F *)f->Get("hGpTPart");
//  TH2F *hGpTvsptlike2  = (TH2F *)f->Get("hGpTPartlike");

  f=new TFile("npe_tree_May5_11default_gpt_dist7.root"); // -7 is the right one, with perp(), mass 0.1 cut, and no trig weight
  TH2F *hGpTvspt0  = (TH2F *)f->Get("hRcptMeeSMD2US_0");
  TH2F *hGpTvsptlike0  = (TH2F *)f->Get("RcptMeeSMD2_0");

  f=new TFile("npe_tree_May5_11default_gpt_dist7.root");
  TH2F *hGpTvspt2  = (TH2F *)f->Get("hRcptMeeSMD2US_2");
  TH2F *hGpTvsptlike2  = (TH2F *)f->Get("RcptMeeSMD2_2");
  
  //	hGpT= new TH1F("hGpT",";p_{T} (GeV/c); yield",nPtBins,ptbin);
  //	hGpTSys= new TH1F("hGpTSys",";p_{T} (GeV/c); yield",nPtBins,ptbin);
  //for(int i=3; i<4; i++) {
  
  ////////////////////////////////////////////////////////////////////
  //Rec. eff. Con
  ///////////////////////////////////////////////////////////////////
  EleNumberPi0Dalitz->Sumw2();
  EleNumberEtaDalitz->Sumw2();
  EleNumberGamma->Sumw2();
  EleNumberPi0Dalitz->Scale(1.0/InputNumberPi0Dalitz->GetEntries());
  EleNumberEtaDalitz->Scale(1.0/InputNumberEtaDalitz->GetEntries());
  EleNumberGamma->Scale(1.0/InputNumberGamma->GetEntries());
  
  TH1F *EleNumber=(TH1F *)EleNumberPi0Dalitz->Clone();
  EleNumber->Sumw2();
  EleNumber->Add(EleNumberEtaDalitz,1);
  EleNumber->Add(EleNumberGamma,1);
  //  EleNumberGamma->Print("ALL");
  //  EleNumber->Print("ALL");
  auto hEleNumberPi0Dalitz = (TH1F*)EleNumberPi0Dalitz->Rebin(10, "hEleNumberPi0Dalitz", ptbin);
  auto hEleNumberEtaDalitz = (TH1F*)EleNumberEtaDalitz->Rebin(10, "hEleNumberEtaDalitz", ptbin);
  auto hEleNumberGamma = (TH1F*)EleNumberGamma->Rebin(10, "hEleNumberGamma", ptbin);
  auto hEleNumber = (TH1F*)EleNumber->Rebin(10, "hEleNumber", ptbin);
  
  //  hEleNumberPi0Dalitz->Draw();
  
  TH1F *hPi0DalitzCon = (TH1F*) hEleNumberPi0Dalitz->Clone("hPi0DalitzCon");
  hPi0DalitzCon->Divide(hEleNumber);
  TH1F *hEtaDalitzCon = (TH1F*) hEleNumberEtaDalitz->Clone("hEtaDalitzCon");
  hEtaDalitzCon->Divide(hEleNumber);
  TH1F *hGammaCon = (TH1F*) hEleNumberGamma->Clone("hGammaCon");
  hGammaCon->Divide(hEleNumber);
  
  
  
//  TCanvas *cd=Canvas("c",0.15,0.03,0.15,0.06,0,0,0);
//  cd->SetGrid(1,1);
//  hEtaDalitzCon->GetYaxis()->SetRangeUser(0, 1);
//  hEtaDalitzCon->GetXaxis()->SetRangeUser(2.5, 10);
//  hPi0DalitzCon->GetXaxis()->SetRangeUser(2.5, 10);
//  hGammaCon->GetXaxis()->SetRangeUser(2.5, 10);

//  htmp = histo2D("htmp1",20,2,10.2,10,0,1,"p_{T} (GeV/c)","Relative Contribution",0.075,0.83,0.08,0.85);
//  htmp->SetNdivisions(510,"x");
//  htmp->SetNdivisions(505,"y");
//
//  Style(hEtaDalitzCon,1,1,2,23,kBlue,2.,"plsame");
//  Style(hPi0DalitzCon,1,1,2,8,kGreen+1,2.,"psame");
//  Style(hGammaCon,1,1,2,22,kRed,2.,"plsame");
//  cd->SaveAs("relative_con.pdf");
  //  return ;
  
  for(int i=1; i<9; i++) {
    int ptlw = (int)hGpTvsptPi0->GetXaxis()->FindBin(ptbin[i]+1e-6);
    int ptup = (int)hGpTvsptPi0->GetXaxis()->FindBin(ptbin[i+1]-1e-6);
    
    hGpTDisPi0[i] = (TH1F *)hGpTvsptPi0->ProjectionY(Form("GpTDisPi0_%d",i),ptlw,ptup);
    hGpTDisPi0[i]->Sumw2();
    hGpTDisEta[i] = (TH1F *)hGpTvsptEta->ProjectionY(Form("GpTDisEta_%d",i),ptlw,ptup);
    hGpTDisEta[i]->Sumw2();
    hGpTDisPhoton[i] = (TH1F *)hGpTvsptPhoton->ProjectionY(Form("GpTDisPhoton_%d",i),ptlw,ptup);
    hGpTDisPhoton[i]->Sumw2();
    
    heff[i] = (TH1F *)hGpTDisPhoton[i]->Clone(Form("heff_%d", i));
    for(int j=0;j<200;j++){
      heff[i]->SetBinContent(j+1,hGpTDisPhoton[i]->GetBinContent(j+1)*hGammaCon->GetBinContent(i+1)+hGpTDisPi0[i]->GetBinContent(j+1)*hPi0DalitzCon->GetBinContent(i+1)+hGpTDisEta[i]->GetBinContent(j+1)*hEtaDalitzCon->GetBinContent(i+1));
      heff[i]->SetBinError(j+1,1e-10);
      //        heff[i]->SetBinError(i+1,sqrt(pow(hGpTDisPhoton[i]->GetBinError(j+1)*hGammaCon->GetBinError(i+1),2)+pow(hGpTDisPi0[i]->GetBinError(j+1)*hPi0DalitzCon->GetBinError(i+1),2)+pow(hGpTDisEta[i]->GetBinError(j+1)*hEtaDalitzCon->GetBinError(i+1),2)));
    }
    
    hGpTDisPi0[i]->Scale(1./hGpTDisPi0[i]->Integral());
    hGpTDisEta[i]->Scale(1./hGpTDisEta[i]->Integral());
    hGpTDisPhoton[i]->Scale(1./hGpTDisPhoton[i]->Integral());
    hGpTDisPi0[i]->Rebin(5);
    hGpTDisPi0[i]->Scale(1./5.);
    hGpTDisEta[i]->Rebin(5);
    hGpTDisEta[i]->Scale(1./5.);
    hGpTDisPhoton[i]->Rebin(5);
    hGpTDisPhoton[i]->Scale(1./5.);
    
//    cout<<heff[i]->Integral()<<"before "<<endl;
    heff[i]->GetXaxis()->SetRangeUser(0.2, 20);
//    cout<<heff[i]->Integral()<<"after "<<endl;
    heff[i]->Scale(1./heff[i]->Integral());
    heff[i]->Rebin(5);
    heff[i]->Scale(1./5.);

    
//    ptlw = (int)hGpTvspt0->GetXaxis()->FindBin(ptbin[i]+1e-6);
//    ptup = (int)hGpTvspt0->GetXaxis()->FindBin(ptbin[i+1]-1e-6);
    
    if(i<3){
      hGpTDis[i] = (TH1F *)hGpTvspt0->ProjectionY(Form("GpTDisEE_%d",i),ptlw,ptup);
      hGpTDislike[i] = (TH1F *)hGpTvsptlike0->ProjectionY(Form("GpTDisEElike_%d",i),ptlw,ptup);
    }
    else{
      hGpTDis[i] = (TH1F *)hGpTvspt2->ProjectionY(Form("GpTDisEE_%d",i),ptlw,ptup);
      hGpTDislike[i] = (TH1F *)hGpTvsptlike2->ProjectionY(Form("GpTDisEElike_%d",i),ptlw,ptup);
    }
    hGpTDisUK_K[i] = (TH1F *)hGpTDis[i]->Clone(Form("GpTDisUK_K_%d",i));
    hGpTDisUK_K[i]->Sumw2();
    
//    cout<<hGpTDislike[i]->GetBinContent(hGpTDislike[i]->FindBin(0.23))<<endl;

//    cout<<hGpTDisUK_K[i]->GetBinContent(hGpTDisUK_K[i]->FindBin(0.23))<<endl;

    hGpTDisUK_K[i]->Add(hGpTDislike[i],-1);
    //hGpTDisSys[i] = (TH1F *)hGpTDisUK_K[i]->Clone(Form("GpTDis_%d",i));
//    cout<<hGpTDisUK_K[i]->Integral()<<"   Entrie  "<<hGpTDisUK_K[i]->GetEntries()<<endl;
    
//    cout<<hGpTDisUK_K[i]->GetBinContent(hGpTDisUK_K[i]->FindBin(0.2))<<endl;
    

    
//    cout<<hGpTDisUK_K[i]->Integral()<<endl;
//    hGpTDisUK_K[i]->GetXaxis()->SetRangeUser(0.2, 20);
//    cout<<hGpTDisUK_K[i]->Integral()<<endl;
//    auto tmp = hGpTDisUK_K[i]->Integral();
    
    hGpTDisUK_K[i]->Scale(1./hGpTDisUK_K[i]->Integral());
    hGpTDisUK_K[i]->Rebin(5);
    hGpTDisUK_K[i]->Scale(1./5.);
    
    auto htmpc = (TH1F*)hGpTDisUK_K[i]->Clone("htmpc");



//    cout<<hGpTDisUK_K[i]->GetBinContent(hGpTDisUK_K[i]->FindBin(0.2))<<endl;
    
    htmp = histo2D("htmp",20,0,5,10,5e-5,0.06,"Gp_{T} (GeV/c)","1/N_{partner electrons}",0.075,0.83,0.08,0.85);
    htmp->SetNdivisions(505,"x");
    htmp->SetNdivisions(505,"y");
    
//
//    Style(hGpTDisEta[i],1,1,3,23,kBlue,2.1,"psame");
//    Style(hGpTDisPi0[i],1,1,3,8,kGreen+1,1.8,"psame");
//    Style(hGpTDisPhoton[i],1,1,3,22,kRed,2.1,"psame");
    
    Style(heff[i],1,1,3,20+4,1,2.1,"psame");
//    Style(hGpTDisUK_K[i],1,1,3,20,1,2.1,"psame");
    Style(hGpTDisUK_K[i],1,1,3,20,1,2.1,"psame");

//    Style(hGpTDisUK_K[i],1,1,3,20,1,2.1,"psame");
//
    lg= Legend(0.5,0.53,0.84,0.76,0.045);
//    lg->AddEntry(hGpTDisPhoton[i],"#gamma Conversion Embedding","pl");
//    lg->AddEntry(hGpTDisPi0[i],"#pi^{0} Dalitz Decay Embedding","pl");
//    lg->AddEntry(hGpTDisEta[i],"#eta Dalitz Decay Embedding","pl");
    lg->AddEntry(hGpTDisUK_K[i],"Partner electron Data","pl");
    lg->AddEntry(heff[i],"Combined Embedding","pl");
//
    tx.DrawLatex(0.5,0.85,"p+p @ #sqrt{s} = 200 GeV");
    tx1.DrawLatex(0.52,0.78,Form("%4.2f < p_{T} < %4.2f GeV/c",ptbin[i],ptbin[i+1]));
    
    
//    auto cr=Canvas("cr",0.15,0.03,0.15,0.06,0,0,0);
//    htmp = histo2D("htmp",20,0.2,4,40,0.2,1.8,"Gp_{T} (GeV/c)","data/embedding",0.075,0.83,0.08,0.85);
//    htmpc->Divide(heff[i]);
//    Style(htmpc,1,1,3,20+4,1,2.1,"psame");
//    tx.DrawLatex(0.5,0.85,"p+p @ #sqrt{s} = 200 GeV");
//    tx1.DrawLatex(0.52,0.78,Form("%4.2f < p_{T} < %4.2f GeV/c",ptbin[i],ptbin[i+1]));
//    cr->Update();
//    cr->Modified();
//    cr->SaveAs(Form("./pic/ratio_rebin_NPEGpTCutSys_%d.pdf",i));

    
    mypdf->On();
    
    cc->Update();
    if(i<nPtBins-1)mypdf->NewPage();
    cc->Modified();

    mypdf->Off();
    cc->SaveAs(Form("./pic/combine_NPEGpTCutSys_%d.pdf",i));

  }
  mypdf->On();
  mypdf->Close();

}
