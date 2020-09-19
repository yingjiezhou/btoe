#include "ptbin.h"
#include "style.h"
void plotNPEGpTCutSysYjv2()
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
  auto cc=Canvas("cc",0.15,0.03,0.15,0.06,0,1,0);
  TPDF *mypdf = new TPDF("result/NPEGpTCutSys.pdf",111);
  mypdf->Off();
  TFile *f;
  TH1F *hSigma,*hGpT,*hGpTSys,*hReceff,*hReceffSys,*hSys;
  TH2F *htmp;
  TH1F *hGpTDisEta[nPtBins],*hGpTDis[nPtBins],*hGpTDislike[nPtBins],*hGpTDisUK_K[nPtBins],*hGpTDisPi0[nPtBins],*hGpTDisPhoton[nPtBins], *heff[nPtBins];
  TLegend *lg;
  f=new TFile("yj/Pi0Dalitz_hist.root");
  TH1F *InputNumberPi0Dalitz=(TH1F *)f->Get("hnTotalyCut");
  TH1F *EleNumberPi0Dalitz=(TH1F *)f->Get("RcptPosEleSMD");
  TH2F *hGpTvsptPi0  = (TH2F *)f->Get("RcptMeeSMD2");
  
  f=new TFile("yj/EtaDalitz_hist.root");
  TH1F *InputNumberEtaDalitz=(TH1F *)f->Get("hnTotalyCut");
  TH1F *EleNumberEtaDalitz=(TH1F *)f->Get("RcptPosEleSMD");
  TH2F *hGpTvsptEta  = (TH2F *)f->Get("RcptMeeSMD2");
  
  f=new TFile("yj/Gamma_hist.root");
  TH1F *InputNumberGamma=(TH1F *)f->Get("hnTotalyCut");
  TH1F *EleNumberGamma=(TH1F *)f->Get("RcptPosEleSMD");
  TH2F *hGpTvsptPhoton  = (TH2F *)f->Get("RcptMeeSMD2");
  
  f=new TFile("yj/npe_tree_May5_11default_gpt_dist.root");
  TH2F *hGpTvspt0  = (TH2F *)f->Get("hRcptMeeSMD2US_0");
  TH2F *hGpTvsptlike0  = (TH2F *)f->Get("RcptMeeSMD2_0");
  
  f=new TFile("npe_tree_May5_11default_gpt_dist.root");
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
  //  hEtaDalitzCon->GetXaxis()->SetRangeUser(0, 10);
  //
  //  Style(hEtaDalitzCon,1,1,2,22,kRed,1.7,"plsame");
  //  Style(hPi0DalitzCon,1,1,2,8,kGreen+1,1.6,"psame");
  //  Style(hGammaCon,1,1,2,23,kBlue,1.7,"plsame");
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
    
//    cout<<heff[i]->Integral()<<"before "<<endl;
    heff[i]->GetXaxis()->SetRangeUser(0.2, 20);
//    cout<<heff[i]->Integral()<<"after "<<endl;
    heff[i]->Scale(1./heff[i]->Integral());
    
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
    
    cout<<hGpTDislike[i]->GetBinContent(hGpTDislike[i]->FindBin(0.23))<<endl;

    cout<<hGpTDisUK_K[i]->GetBinContent(hGpTDisUK_K[i]->FindBin(0.23))<<endl;

    hGpTDisUK_K[i]->Add(hGpTDislike[i],-1);
    //hGpTDisSys[i] = (TH1F *)hGpTDisUK_K[i]->Clone(Form("GpTDis_%d",i));
//    cout<<hGpTDisUK_K[i]->Integral()<<"   Entrie  "<<hGpTDisUK_K[i]->GetEntries()<<endl;
    
    cout<<hGpTDisUK_K[i]->GetBinContent(hGpTDisUK_K[i]->FindBin(0.2))<<endl;
    hGpTDisUK_K[i]->Scale(1./hGpTDisUK_K[i]->Integral());
    //		hGpTDisUK_K[i]->Rebin(5);
    //		hGpTDisUK_K[i]->Scale(1./5.);
    
    hGpTDisUK_K[1]->Draw();
    return ;
    
    htmp = histo2D("htmp",20,0,10,10,1e-8,1e1,"Gp_{T} (GeV/c)","1/N_{tracks}",0.075,0.83,0.08,0.85);
    htmp->SetNdivisions(505,"x");
    htmp->SetNdivisions(505,"y");
//    heff[i]->GetYaxis()->SetRangeUser(5e-5, 1.);
    
//    Style(hGpTDisEta[i],1,1,3,23,kBlue,2.1,"psame");
//    Style(hGpTDisPi0[i],1,1,3,8,kGreen+1,1.8,"psame");
//    Style(hGpTDisPhoton[i],1,1,3,22,kRed,2.1,"psame");
    Style(heff[i],1,kRed+1,3,20+4,kRed+1,2.1,"psame");
    Style(hGpTDisUK_K[i],1,1,3,20,1,2.1,"psame");
    
    lg= Legend(0.5,0.63,0.84,0.76,0.045);
    lg->AddEntry(hGpTDisUK_K[i],"Photonic electron(data)","pl");
//    lg->AddEntry(hGpTDisPhoton[i],"#gamma Conversion Embedding","pl");
//    lg->AddEntry(hGpTDisPi0[i],"#pi^{0} Dalitz Decay Embedding","pl");
//    lg->AddEntry(hGpTDisEta[i],"#eta Dalitz Decay Embedding","pl");
    lg->AddEntry(heff[i],"Combined(embedding)","pl");
    
    tx.DrawLatex(0.5,0.85,"p+p @ #sqrt{s} = 200 GeV");
    tx1.DrawLatex(0.52,0.78,Form("%4.2f < p_{T} < %4.2f GeV/c",ptbin[i],ptbin[i+1]));
    
    mypdf->On();
    
    cc->Update();
    if(i<nPtBins-1)mypdf->NewPage();
    cc->Modified();

    mypdf->Off();
    cc->SaveAs(Form("./pic/newcombine_NPEGpTCutSys_%d.pdf",i));
    
    //		float Nes   = hGpTDis[i]->Integral(hGpTDis[i]->FindBin(0.3+1e-6),hGpTDis[i]->GetNbinsX());
    //		float Nebg   = hGpTDislike[i]->Integral(hGpTDislike[i]->FindBin(0.3+1e-6),hGpTDislike[i]->GetNbinsX());
    //		float Ne   = Nes-Nebg;//hGpTDisSys[i]->Integral(1,hGpTDisSys[i]->FindBin(0.15-1e-6));
    //		hGpT->SetBinContent(i+1,Ne);
    //		hGpT->SetBinError(i+1,sqrt(Nes+Nebg));
    //		//cout<<"Ne"<<sqrt(Ne)<<" "<<sqrt(Nes+Nebg)<<" "<<sqrt(hGpTDis[i]->Integral(1,hGpTDis[i]->FindBin(0.15-1e-6))+hGpTDislike[i]->Integral(1,hGpTDis[i]->FindBin(0.15-1e-6)))<<endl;
    //		float NesSys = hGpTDis[i]->Integral(hGpTDis[i]->FindBin(0.2+1e-6),hGpTDis[i]->GetNbinsX());
    //		float NebgSys = hGpTDislike[i]->Integral(hGpTDislike[i]->FindBin(0.2+1e-6),hGpTDislike[i]->GetNbinsX());
    //		float NeSys   = NesSys-NebgSys;//hGpTDisSys[i]->Integral(1,hGpTDisSys[i]->FindBin(0.15-1e-6));
    //		hGpTSys->SetBinContent(i+1,NeSys);
    //		hGpTSys->SetBinError(i+1,sqrt(NesSys+NebgSys));
  }
  mypdf->On();
  mypdf->Close();
  /*hGpT->Print("ALL");
   hGpTSys->Print("ALL");
   
   
   hSys= new TH1F("hSysGpTCut",";p_{T} (GeV/c); #frac{1}{2#pip_{T}}#frac{d^{2}N}{dp_{T}dy} [(GeV/c)^{-2}]",nPtBins,ptbin);
   //////////////////////////////////////////////////////////////////////
   //TPC tracking eff
   /////////////////////////////////////////////////////////////////////
   f=new TFile("../Efficiency/embedding/effroot/PHEReceffSysGpt.root");
   hReceffSys=(TH1F *)f->Get("hefffun");//heffGpTCut
   f=new TFile("../Efficiency/embedding/effroot/PHEReceff.root");
   hReceff=(TH1F *)f->Get("hefffun");
   hGpTSys->Sumw2();
   hGpT->Sumw2();
   hGpTSys->Divide(hReceffSys);
   hGpT->Divide(hReceff);
   hSigma=(TH1F *)hGpTSys->Clone("hSigmaGpTCut");
   hSigma->Sumw2();
   hSigma->Divide(hGpT);
   hSigma->Print("ALL");
   for(int i=0;i<nPtBins;i++){
   hSys->SetBinContent(i+1,1-hSigma->GetBinContent(i+1));
   hSys->SetBinError(i+1,hSigma->GetBinError(i+1));
   }
   hSigmabg=(TH1F *)hSigma->Clone();
   cc->Clear();
   cc->SetLogy(0);
   cc->SetGrid(1,1);
   htmp = histo2D("htmp",20,PtMinhtmp[0],PtMaxhtmp[0],10,0.5,1.5,"p_{T} (GeV/c)","#sigma_{Gp_{T}}",0.075,0.83,0.08,0.7);
   htmp->SetNdivisions(505,"y");
   Style(hSigmabg,1,1,1,8,1,1.9,"psame");
   Style(hSigma,1,1,3,8,kGreen+1,1.7,"psame");
   TF1 *fun = new TF1("funSysGpTCut","pol0",2.5,10);
   fun->SetParameter(0,1.0);
   hSigma->Fit(fun,"N0IR","",2.5,10);
   StyleFun(fun,1,1,5,23,11,1.2,"E4same");
   drawLatex(0.65,0.37,Form("%3.3f #pm %3.3f",fun->GetParameter(0), fun->GetParError(0)),42,0.06,1);
   tx.DrawLatex(0.5,0.85,"p+p @ #sqrt{s} = 200 GeV");
   cc->SaveAs("./figure/NPEGpTCutSys.png");
   cc->SaveAs("./figure/NPEGpTCutSys.eps");
   file = new TFile("rootfile/NPESys.root","UPDATE");
   //file = new TFile("rootfile/NPESysHT0.root","UPDATE");
   //file = new TFile("rootfile/NPESysHT2.root","UPDATE");
   file->cd();
   hSys->Write();
   fun->Write();
   file->Close();*/
}
