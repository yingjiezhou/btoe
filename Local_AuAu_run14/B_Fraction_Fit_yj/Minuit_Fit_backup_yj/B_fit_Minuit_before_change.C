#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TObjArray.h>
#include <TString.h>
#include <TFractionFitter.h>
#include <TLegend.h>
#include <TLatex.h>
#include "fstream"
#include "iostream"
#include "TH1F.h"
#include "TF1.h"
#include "TMinuit.h"
#include "TGraph.h"
#include "TLine.h"

using namespace std;


bool MB_trg=true;
bool HT_trg=false;

const int mh2Nhist=3;
const int Npt=6;
const int IHIST=1;
const int DRAWING=1;
const Double_t MINDCA=-0.1;
const Double_t MAXDCA=0.1;
int pt_start=-999;
int pt_end=-999;
TH1F *mc1_charm;
TH1F *mc2_bottom;
TH1F *mc3_phe;
TH1F *mc4_hadron;
TH1F *purity;
TH1F *data;

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex);
void chi2(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag);
void B_fit_Minuit_before_change(){
  
  char buf[50];
  char outputname[50];
  char Trg[50];
  
  Float_t ptbin[Npt+1]={1,1.2,1.5,2,3,4,6};
  TH1F *b_fraction_MB=new TH1F("b_fraction_MB","",Npt,ptbin);
  TH1F *b_fraction_HT=new TH1F("b_fraction_HT","",Npt,ptbin);
  
  
  double NMC=1;
  TString PTBIN[Npt]={"1<p_{T}^{e}<1.2 GeV/c","1.2<p_{T}^{e}<1.5 GeV/c","1.5<p_{T}^{e}<2 GeV/c","2<p_{T}^{e}<3 GeV/c","3<p_{T}^{e}<4 GeV/c","4<p_{T}^{e}<6 GeV/c"};

  TFile *Output_file;
  TFile *input_data;
  TFile *input_purity;

  TFile *input_fastsim=new TFile("./Input_12_20/File_fastsim_11_3.root","READ");
  TFile *input_phe_hijing=new TFile("./Input_12_20/Hijing_phe_gamma_pi0_pi.root","READ");
  TFile *input_hadron_data=new TFile("./Input_12_20/Hadron_Dca_11_3.root","READ");

  //   TFile *input_phe_hijing=new TFile("Input/Hijing_phe_gamma_pi0_pi_15c.root","READ");
  if(MB_trg)
    {
      sprintf(Trg,"MB");
      input_data=new TFile("./Input_12_20/Dca_inclusive_photonic_MB_11_3.root","READ");
      Output_file=new TFile("OutPut/Fit_B_fraction_MB.root","RECREATE");
      input_purity=new TFile("Input_12_20/purity_MB.root","READ");
      // hadron purity
      purity=(TH1F *) input_purity->Get("purity_MB");

      pt_start=1;
      pt_end=5;

    }

 
  // purity->Draw();
  // return ;
 

  if(HT_trg)
    {
        
      sprintf(Trg,"HT");
      input_data=new TFile("./Input/Dca_inclusive_photonic_HT_9_5.root","READ");
      Output_file=new TFile("OutPut/Fit_B_fraction_HT.root","RECREATE");
      pt_start=3;
      pt_end=6;

    }

  // fastsim    
  TH1F *mh1Charm_dca[mh2Nhist][Npt];
  TH1F *mh1Bottom_dca[mh2Nhist][Npt];

  // from hijing
  TH1F * mh1Phe_dca[mh2Nhist][Npt];    
  TH1F * mh1pi_dca[mh2Nhist][Npt];    

  // from data
  TH1F * mh1data_inclusive[mh2Nhist][Npt];
  TH1F * mh1data_phe[mh2Nhist][Npt];
  // Hadron from Data
  TH1F *mh1data_hadron[mh2Nhist][Npt];


  
  // from fastsim
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
        
      sprintf(buf,"mh1rDca_hist%ipt%i_D_rebin",ihist,ipt);
      mh1Charm_dca[ihist][ipt]=(TH1F *)  input_fastsim->Get(buf);
      sprintf(buf,"mh1rDca_hist%ipt%i_B_rebin",ihist,ipt);
      mh1Bottom_dca[ihist][ipt]=(TH1F *)  input_fastsim->Get(buf);
      // cout<< " ihst "<<ihist<< " ipt "<< ipt<< " "<< mh1Charm_dca[ihist][ipt]->GetTitle()<<endl;
      // cout<< " ihst "<<ihist<< " ipt "<< ipt<< " "<<mh1Bottom_dca[ihist][ipt]->GetTitle()<<endl;
 
    }
  }

  // from data 
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
      sprintf(buf,"electron_data_Dca_inclusive%i%i_rebin",ihist,ipt);
      mh1data_inclusive[ihist][ipt]=(TH1F *)  input_data->Get(buf);
      sprintf(buf,"electron_data_Dca_Unlike_like%i%i_rebin",ihist,ipt);
      mh1data_phe[ihist][ipt]=(TH1F *)  input_data->Get(buf);

      // cout<< "data  ihst "<<ihist<< " ipt "<< ipt<< " "<< mh1data_inclusive[ihist][ipt]->GetTitle()<<endl;
      // cout<< "data ihst "<<ihist<< " ipt "<< ipt<< " "<<mh1data_phe[ihist][ipt]->GetTitle()<<endl;
    }
  }

  // from hijing
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
      sprintf(buf,"gamma_pi0_Dca%i_ipt%i_rebin",ihist,ipt);
      mh1Phe_dca[ihist][ipt]=(TH1F *)  input_phe_hijing->Get(buf);
      cout<< "hijing  ihst "<<ihist<< " ipt "<< ipt<< " "<< mh1Phe_dca[ihist][ipt]->GetTitle()<<endl;
    }
  }

  // hadron from data, please note 3D dca was not saved, will add it if ..
  for(Int_t ihist=0;ihist<mh2Nhist;ihist++) {
    for(Int_t ipt=0;ipt<Npt;ipt++) {
      if(ihist==0||ihist==1)
	sprintf(buf,"hadron_DcaXy_data_%i_rebin",ipt);
      else
	sprintf(buf,"hadron_DcaZ_data_%i_rebin",ipt);
      mh1data_hadron[ihist][ipt]=(TH1F *)  input_hadron_data->Get(buf);
      cout<< "hadron  "<<ihist<< " ipt "<< ipt<< " "<< mh1data_hadron[ihist][ipt]->GetTitle()<<endl;
    }
  }

    
  

  //  c1->Divide(1,2);
  TCanvas *c1=new TCanvas("c1","",900,1000);
  TCanvas *c2=new TCanvas("c2","",800,1000);
    
  if(DRAWING) {
    gStyle->SetPadLeftMargin(0.06);
    gStyle->SetPadRightMargin(0.04);
    gStyle->SetPadTopMargin(0.09);
    gStyle->SetPadBottomMargin(0.16);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(1);
    gStyle->SetTitleSize(0.1);
    gStyle->SetOptLogy();
    gStyle->SetOptFit(1);
    // c1->Divide(3,1);
  }



  
  
  //  for(Int_t ipt=0;ipt<1;ipt++) {
  for(Int_t ipt=pt_start;ipt<pt_end;ipt++) {
    TString mcname0="mc1", mcname1="mc2", mcname2="mc3",mcname3="mc4",  dataname="data";
    mc1_charm=(TH1F*)mh1Charm_dca[IHIST][ipt]->Clone(mcname0+mh1Charm_dca[IHIST][ipt]->GetName());
    mc2_bottom=(TH1F*)mh1Bottom_dca[IHIST][ipt]->Clone(mcname1+mh1Bottom_dca[IHIST][ipt]->GetName());
    //phe from hijing
    mc3_phe=(TH1F*)mh1Phe_dca[IHIST][ipt]->Clone(mcname2+mh1Phe_dca[IHIST][ipt]->GetName());
    // phe from data
    // mc3_phe=(TH1F*)mh1data_phe[IHIST][ipt]->Clone(mcname2+mh1data_phe[IHIST][ipt]->GetName());
    mc4_hadron=(TH1F*)mh1data_hadron[IHIST][ipt]->Clone(mcname3+mh1data_hadron[IHIST][ipt]->GetName());

    
    data=(TH1F*)mh1data_inclusive[IHIST][ipt]->Clone(dataname+mh1data_inclusive[IHIST][ipt]->GetName());


    cout<<mc1_charm->GetTitle()<<endl;
    cout<<mc2_bottom->GetTitle()<<endl;
    cout<<mc3_phe->GetTitle()<<endl;
    cout<<mc4_hadron->GetTitle()<<endl;

    cout<<data->GetTitle()<<endl;


    // mc1_charm->Scale(data->Integral()/mc1_charm->Integral());
    // mc2_bottom->Scale(data->Integral()/mc2_bottom->Integral());
    // mc3_pheScale(data->Integral()/mc3_phe->mc2Integral());
    
    mc1_charm->Sumw2();
    mc2_bottom->Sumw2();
    mc3_phe->Sumw2();
    mc4_hadron->Sumw2();
    
    
    mc1_charm->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    mc2_bottom->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    mc3_phe->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    mc4_hadron->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    data->GetXaxis()->SetRangeUser(MINDCA,MAXDCA);
    

    mc1_charm->Scale(1./mc1_charm->Integral());
    mc2_bottom->Scale(1./mc2_bottom->Integral());
    mc3_phe->Scale(1./mc3_phe->Integral());
    mc4_hadron->Scale(1./mc4_hadron->Integral());


    TString title="";
    data->SetTitle(title+PTBIN[ipt]);
    data->GetXaxis()->SetTitle("DCA_{XY} (cm)");
    data->GetXaxis()->SetTitleSize(0.04);
    data->GetXaxis()->SetLabelSize(0.04);
    data->GetYaxis()->SetLabelSize(0.05);
    data->GetYaxis()->SetTitleOffset(1);
    data->GetXaxis()->SetTitleOffset(1);
    data->SetMaximum(data->GetMaximum()*1.3);
    gPad->SetLogy();   

    double frac_norm = 0.;
    double fracErr_norm = 0.;
    double frac_btoe = 0.;
    double fracErr_btoe = 0.;
    double frac_ctoe = 0.;
    double fracErr_ctoe = 0.;
    double frac_phe = 0.;
    double fracErr_phe = 0.;
    double frac_hadron = 0.;
    double fracErr_hadron = 0.;
    
    // cout<<"had pT = "<<ptHadLow[j]<<endl;
	
    // +--------------------------+
    // | run MINUIT               |
    // +--------------------------+
    TMinuit *gMinuit=new TMinuit(3); //initialize TMinuit with a maximum of 5 params
    gMinuit->SetMaxIterations(50000);
    gMinuit->SetFCN(chi2);
    gMinuit->SetErrorDef(1);
    
    double arglist[10];int ierflg=0;
    //set err definition to 1-sigma
    //arglist[0]=4; //was to get 2 sigma 
    arglist[0]=1; //error definition: chi^2 change by 1 to get 1 sigma
    gMinuit->mnexcm("SET ERR",arglist,1,ierflg);

    //starting values
    double vstart[4]={1,0.001,0.001,1-purity->GetBinContent(ipt+1)}; //frac
    double step[4]={1,0.0001,0.0001,0.0001}; //starting step
    gMinuit->mnparm(0,"frac 0",vstart[0],step[0],1e1,1e16,ierflg);
    gMinuit->mnparm(1,"frac 1",vstart[1],step[1],0.000,1.,ierflg);
    gMinuit->mnparm(2,"frac 2",vstart[2],step[2],0.000,1,ierflg);
     gMinuit->mnparm(3,"frac 3",vstart[3],step[3],1-purity->GetBinContent(ipt+1)-0.1,1-purity->GetBinContent(ipt+1)+0.1,ierflg);

    // gMinuit->mnparm(3,"frac 3",vstart[3],step[3],0,1,ierflg);

    //      gMinuit->FixParameter(3);
    //gMinuit->SetParLimits(3,1-purity->GetBinContent(ipt+1)-0.1,1-purity->GetBinContent(ipt+1)+0.1);

    //simple scan to get better start values
    gMinuit->mnexcm("SCAN",arglist,1,ierflg); 
    cout<<"done with first scan!"<<endl;
    //minimization
    arglist[0]=50000; //maxcalls
    arglist[1]=0.5; // tolerance = 0.001*[this value]*[error def] //5.0 before
    gMinuit->mnexcm("MIGRAD",arglist,2,ierflg); 
    //gMinuit->mnexcm("MINIMIZE",arglist,2,ierflg); 
    //error analysis

    cout<<"done with fit!"<<endl;
    //fit results
    double dum1,dum2;
    TString *str0 = new TString("norm");
    TString *str1 = new TString("C#rightarrow e frac");
    TString *str2 = new TString("B#rightarrow e  frac");
    TString *str3 = new TString("hadron frac");

    gMinuit->mnpout(0,*str0,frac_norm,fracErr_norm,dum1,dum2,ierflg);
    gMinuit->mnpout(1,*str1,frac_ctoe,fracErr_ctoe,dum1,dum2,ierflg);
    gMinuit->mnpout(2,*str2,frac_btoe,fracErr_btoe,dum1,dum2,ierflg);
    gMinuit->mnpout(3,*str3,frac_hadron,fracErr_hadron,dum1,dum2,ierflg);

    cout<< " frac_btoe"<< frac_btoe<<endl;
    cout<< " frac_ctoe"<< frac_ctoe<<endl;
    
    //get variance/errors
    TGraph *contFrac_1sigma;
    TGraph *contFrac_2sigma;

             
    //Print results
    double amin,edm,errdef;
    int nvpar,nparx,icstat;
    gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
    gMinuit->mnprin(3,amin);

    // float frac0 = frac_ctoe;
    // float frac1 = frac_btoe;
    // float frac2 = frac_hadron;
    // float frac3 = 1-frac0-frac1-frac2;


    //   data->SetMaximum(
    //   data->GetYaxis()->SetRangeUser(1,data->GetMaximum()*1.3);

    //   TPad *pad1 = new TPad("pad1","",0.001,0.3,0.99,0.99);

    // c1->cd(1)->SetPad(0.01,0.1,0.99,0.99);
    // c1->cd(1)->SetBottomMargin(0.0);
    // c1->cd(1)->SetTopMargin(0.1);
    // c1->cd(1)->SetLeftMargin(0.1);


    // gPad->Update();
    // pad1->Draw();
    // pad1->cd();    


    c1->cd();
    c1->SetLogy(1);
    gPad->Update();    
    data->Draw();

    
    TH1F *mc1_charm_cl = (TH1F*)mc1_charm->Clone("mc1_charm_cl");
    mc1_charm_cl->Scale(frac_ctoe*frac_norm);
    mc1_charm_cl->SetLineColor(2);
    
    TH1F *mc2_bottom_cl = (TH1F*)mc2_bottom->Clone("mc2_bottom_cl");
    mc2_bottom_cl->Scale(frac_btoe*frac_norm);
    mc2_bottom_cl->SetLineColor(6);

    TH1F *mc3_phe_cl = (TH1F*)mc3_phe->Clone("mc3_phe_cl");
    mc3_phe_cl->Scale((1-frac_ctoe-frac_btoe-frac_hadron)*frac_norm);
    mc3_phe_cl->SetLineColor(8);
    
    TH1F *mc4_hadron_cl = (TH1F*)mc4_hadron->Clone("mc4_hadron_cl");
    mc4_hadron_cl->Scale(frac_hadron*frac_norm);
    mc4_hadron_cl->SetLineColor(4);

    
    TH1F *mc_all_cl = (TH1F*)mc1_charm_cl->Clone("mc_all_cl");

    mc_all_cl->Add(mc2_bottom_cl);
    mc_all_cl->Add(mc3_phe_cl);
    mc_all_cl->Add(mc4_hadron_cl);

    mc_all_cl->SetLineColor(1);

    mc1_charm_cl->GetYaxis()->SetRangeUser(100,data->GetMaximum()*1.3);
    mc1_charm_cl->DrawClone("histsame");
    mc2_bottom_cl->DrawClone("histsame");
    mc3_phe_cl->DrawClone("histsame");
    mc4_hadron_cl->DrawClone("histsame");
    mc_all_cl->DrawClone("histsame");

    Double_t b_ratio=frac_btoe/(frac_btoe+frac_ctoe);
    Double_t b_ratio_err=1./(frac_btoe+frac_ctoe)/(frac_btoe+frac_ctoe)*sqrt(frac_btoe*fracErr_ctoe*frac_btoe*fracErr_ctoe+frac_ctoe*fracErr_btoe*frac_ctoe*fracErr_btoe);

    cout<< " b_Fr "<<b_ratio<<endl;
    sprintf(buf,"F(D#rightarrow e)^{Fit}=%4.3f#pm%4.3f",frac_ctoe,fracErr_ctoe);
    drawLatex(0.13,0.8,buf,62,0.04,2);
    
    sprintf(buf,"F(B#rightarrow e)^{Fit}=%4.3f#pm%4.3f",frac_btoe,fracErr_btoe);
    drawLatex(0.13,0.75,buf,62,0.04,2);

    sprintf(buf,"F(PHE)^{Fit}=%4.3f",1-frac_ctoe-frac_btoe-frac_hadron);
    drawLatex(0.13,0.7,buf,62,0.04,2);

    sprintf(buf,"F(Hadron)^{Fit}=%4.3f#pm%4.3f",frac_hadron,purity->GetBinError(ipt+1));
    drawLatex(0.13,0.65,buf,62,0.04,2);

    sprintf(buf,"b/(b+c)=%4.3f#pm%4.3f",b_ratio,b_ratio_err);
    drawLatex(0.13,0.6,buf,62,0.04,2);


    TLegend *legend=new TLegend(0.6,0.6,0.94,0.84);
    legend ->SetBorderSize(0);
    legend ->SetTextSize(0.03);
    legend ->SetFillStyle(0);
    legend ->SetTextFont(62);
    legend->AddEntry(data,"Inclusive Electron","lp");
    legend->AddEntry(mc_all_cl,"Template Fit","l");
    legend->AddEntry(mc1_charm_cl,"C #rightarrow e","l");
    legend->AddEntry(mc2_bottom_cl,"B #rightarrow e","l");
    legend->AddEntry(mc3_phe_cl,"PHE","l");
    legend->AddEntry(mc4_hadron_cl,"Hadron","l");

    legend->Draw("same");


    c2->cd();
    c2->Update();
    TH1F *ratio=(TH1F *) data->Clone("ratio");
    c2->SetLogy(0);
    ratio->Divide(mc_all_cl);
    TLine *line_1=new TLine(MINDCA,1.0,MAXDCA,1.0);
    line_1->SetLineColor(4);
    line_1->SetLineStyle(7);
    line_1->SetLineWidth(3);

    // c1->cd(2)->SetTopMargin(0.0);
    // c1->cd(2)->SetBottomMargin(0.14);
    // c1->cd(2)->SetLeftMargin(0.1);
    // gPad->SetLogy(0);
  
    //   c2->cd();
    ratio->SetLineColor(2);
    ratio->SetMarkerColor(2);
    ratio->GetYaxis()->SetRangeUser(0.4,2.6);
    //   TPad *pad2 = new TPad("pad2","",0.001,0.001,0.99,0.3);
    // gPad->Update();
    // pad2->Draw();
    // pad2->cd();
     ratio->Draw("PE");
     line_1->Draw("same");

     if(MB_trg&&abs(b_ratio)<999&&abs(b_ratio_err)<999)
      {
	
	b_fraction_MB->SetBinContent(ipt+1,b_ratio);
	b_fraction_MB->SetBinError(ipt+1,b_ratio_err);
      }
    
    if(DRAWING) {
       c1->SaveAs(Form("OutPut/%i_b_Fraction_%s_Fit.pdf",ipt,Trg));
       c2->SaveAs(Form("OutPut/%i_b_Fraction_Fit_ratio%s.pdf",ipt,Trg));

    }
    
	
  } // end pt

   if(MB_trg)
     {
       Output_file->cd();
       b_fraction_MB->Write();
       Output_file->Close();
     }
  return;
  
}
void chi2(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag){

  if(!mc1_charm || !mc2_bottom|| !mc3_phe|| !mc4_hadron ){cout<<"no template!"<<endl; return ;}

  // if(mc1_charm->GetNbinsX()!=mc2_bottom->GetNbinsX()){
  //   cout<<"Warning: unequal bins! bin1 = "<<mc1_charm->GetNbinsX()<<" bin2 = "<<mc2_bottom->GetNbinsX()<<endl;
  //   return ;
  // }

  double chiSq = 0.;
  int nDof = 0; 
  for(int k=0;k<mc1_charm->GetNbinsX();k++){

    cout<< mc1_charm->GetNbinsX()<<endl;
    // if (57<k&&k<63)
    //   continue;

    double y1 = mc1_charm->GetBinContent(k+1);
    double y2 = mc2_bottom->GetBinContent(k+1);
    double y3 = mc3_phe->GetBinContent(k+1);
    double y4 = mc4_hadron->GetBinContent(k+1);
 
    

    
    // double ey1 = mc1_charm->GetBinError(k+1);
    // double ey2 = mc2_bottom->GetBinError(k+1);
    // double ey3 = mc3_phe->GetBinError(k+1);

    
    
    double y_data = data->GetBinContent(k+1);
    double ey_data = data->GetBinError(k+1);
    //   double eTemp=sqrt(ey1*ey1+ey2*ey2+ey3*ey3); 
    //double y0 = hdPhi_zb[i-2]->GetBinContent(k+1);
    //double ey0 = hdPhi_zb[i-2]->GetBinError(k+1);

    // by bingchu  // double ycomb = par[0]*y2+y1*(1.-par[0]); //
    double ycomb = par[0]*(par[1]*y1+par[2]*y2+ (1-par[1]-par[2]-par[3])*y3 + par[3]*y4); //
       //    double ycomb = par[0]*(par[1]*y0+par[2]*y1+ par[3]*y2 + 0.2*y3); //
    
    double ey1 = par[0]*par[1]*mc1_charm->GetBinError(k+1);
    double ey2 = par[0]*par[2]*mc2_bottom->GetBinError(k+1);
    double ey3 = par[0]*(1-par[1]-par[2]-par[3])*mc3_phe->GetBinError(k+1);
    double ey4 = par[0]*par[3]*mc4_hadron->GetBinError(k+1);
    double eTemp=sqrt(ey1*ey1+ey2*ey2+ey3*ey3+ey4*ey4);
    
    //double ycomb = par[0]*y2+y1*par[1]; // 
    //double delta = (ycomb-y_data)/ey_data;
    double delta = (ycomb-y_data)/sqrt(ey_data*ey_data+eTemp*eTemp);
        
    chiSq += delta*delta;
    nDof++;



  }
  func = chiSq;

}
TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex)
  {
    TLatex *latex = new TLatex(x,y,text); 
    latex->SetNDC();
    // latex->SetTextFont(textFont);
    latex->SetTextSize(textSize);   
    latex->SetTextColor(colorIndex); 
    latex->Draw("same");
    return latex;
                                                                
  }

