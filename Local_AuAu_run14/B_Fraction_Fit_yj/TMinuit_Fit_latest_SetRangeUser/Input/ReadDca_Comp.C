#include "/Users/zhouyingjie/Local/PWG/PWGRH/Script/include/TAliFigs.h"
#include "/Users/zhouyingjie/Local/PWG/PWGRH/Script/include/TPlotStd.h"
#include "/Users/zhouyingjie/Local/PWG/PWGRH/Script/include/TUtilHisto.h"

void ReadDca_Comp(){
  gStyle->SetOptFit(1111);
  SetStyle();
  //=============================================================================

  //=============================================================================
  const int Npt=8;
  char buf[1024];
  TH1F *mh1data_hadron[Npt];
  TH1F *mh1data_hadron1[Npt];
  
  auto file(TFile::Open("Dca_hadron.root","READ")); // xz's
  auto file1(TFile::Open("Dca_hadron_qa_HFT_more_xzbin_v2.root","READ")); // yj
  TString outfileName="ReadDca_Comp_DCAxy_qa_v2";
  //auto file1(TFile::Open("Dca_hadron_misIDH.root","READ")); // yj
  //TString outfileName="ReadDca_Comp_DCAxy_misIDH";
  TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex);
  
  TString PTBIN[Npt]={"1<p_{T}^{e}<1.2 GeV/c","1.2<p_{T}^{e}<1.5 GeV/c","1.5<p_{T}^{e}<2 GeV/c", "2<p_{T}^{e}<2.5 GeV/c","2.5<p_{T}^{e}<3.5 GeV/c","3.5<p_{T}^{e}<4.5 GeV/c","4.5<p_{T}^{e}<5.5 GeV/c",  "5.5<p_{T}^{e}<8.5 GeV/c"};
  
  //=============================================================================
  // hadron from data, please note 3D dca was not saved, will add it if ..
  TCanvas *cc=new TCanvas("cc","",1200,1000);
  cc->Divide(4,2);
  
  TLegend *legend=new TLegend(0.6,0.6,0.80,0.85);
  legend ->SetBorderSize(0);
  legend ->SetTextSize(0.04);
  legend ->SetFillStyle(0);
  legend ->SetTextFont(62);
  
  
  for(Int_t ipt=0;ipt<Npt;ipt++) {
    sprintf(buf,"Hadron_dcaXY_%i_rebin",ipt);
    cout<< " "<<buf<<"\n";
    mh1data_hadron[ipt]=(TH1F *)  file->Get(buf);
    mh1data_hadron[ipt]->Scale(1./mh1data_hadron[ipt]->Integral());

    mh1data_hadron1[ipt]=(TH1F *)  file1->Get(buf);
    mh1data_hadron1[ipt]->Scale(1,"width");  // zyj added
    mh1data_hadron1[ipt]->Scale(1./mh1data_hadron1[ipt]->Integral());
    //mh1data_hadron1[ipt]->Scale(1,"width");  // zyj added
    cc->cd(ipt+1);
    gPad->SetLogy(1);
    mh1data_hadron[ipt]->SetLineColor(2);
    mh1data_hadron1[ipt]->SetLineColor(4);

    mh1data_hadron[ipt]->SetLineWidth(2);
    mh1data_hadron1[ipt]->SetLineWidth(2);

    mh1data_hadron[ipt]->Draw();
    mh1data_hadron1[ipt]->Draw("same");
    if(ipt==0){
      legend->AddEntry(mh1data_hadron[ipt],"Hadron XZ","lp");
      legend->AddEntry(mh1data_hadron1[ipt],"Hadron YJ","l");
    }
    legend->Draw("same");
    sprintf(buf,PTBIN[ipt]);
    drawLatex(0.25,0.75,buf,62,0.04,1);
    //sprintf(buf,"Corrected by using same pt bin");
    //drawLatex(0.25,0.55,buf,62,0.04,1);
    
  }
  cc->SaveAs(Form("%s.pdf", outfileName.Data()));

}

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex)
{
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
  
}


