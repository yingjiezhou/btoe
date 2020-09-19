#include <iostream>
#include<iomanip>
#include <fstream>
#include "TLatex.h"
#include "TStyle.h"
#include "TH3F.h"
#include "TF1.h"
#include "TMath.h"
#include "TLine.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TRandom3.h"
#include "TGraphErrors.h"

using namespace std;
const Double_t PI=TMath::Pi();
Int_t gColor08=1;
Int_t gColor08_fill=1;
Int_t gMStyle08=20;


Int_t gColor12HT=2;
Int_t gColor12HT_fill=42;
Int_t gMStyle12HT=20;

Int_t gColor12MB=2;
Int_t gColor12MB_fill=42;
Int_t gMStyle12MB=24;


Int_t lWidth=3;
Int_t lStyle=2;
Int_t lStyle_c=1;
Int_t lColor=4;
TString mh1Title[8]={"1<pT<1.2 (GeV/c)",
                       "1.2<pT<1.5 (GeV/c)", 
                       "1.5<pT<2 (GeV/c)",
                       "2<pT<2.5 (GeV/c)",
                       "2.5<pT<3.5 (GeV/c)",
                       "3.5<pT<4.5 (GeV/c)",
                       "4.5<pT<5.5 (GeV/c)",
                       "5.5<pT<8.5 (GeV/c)"};
TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
char buf[1024];
void Systematic_uncertainty()

{
  
  char buf[1024];
  TH1::SetDefaultSumw2();
  gStyle->SetTitleSize(0.06,"XY");
  gStyle->SetTitleFontSize(0.1);
  gStyle->SetTitleOffset(1.,"X");
  gStyle->SetTitleOffset(1.,"Y");

  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadRightMargin(0.06);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.16);
    //  gStyle->SetEndErrorSize(6);
  gStyle->SetOptStat(000);

  //  TFile *input_Fit=new TFile("InPut/Fit_B_fraction_MB.root","READ");
  TFile *input_Fit=new TFile("InPut/Fit_B_fraction_MB_default_2.root","READ");
  TFile *input_Fit_kaon=new TFile("InPut/Fit_B_fraction_MB_kaon.root","READ");
  TFile *input_Fit_hadron=new TFile("InPut/Fit_B_fraction_MB_hadron.root","READ");

  TFile *input_Fit_range_008=new TFile("InPut/Fit_B_fraction_MB_0.08.root","READ");
  TFile *input_Fit_range_006=new TFile("InPut/Fit_B_fraction_MB_0.06.root","READ");
  TFile *input_Fit_DF=new TFile("InPut/Fit_B_fraction_MB_DF.root","READ");
  TFile *input_Fit_BF=new TFile("InPut/Fit_B_fraction_MB_BF.root","READ");
  TFile *input_Fit_weight_D=new TFile("InPut/Fit_B_fraction_MB_weight_data.root","READ");
  // TFile *input_Fit_tight_nsigmaE=new TFile("InPut/Fit_B_fraction_MB_0_5nsigmae_.root","READ");
  TFile *input_Fit_tight_nsigmaE=new TFile("InPut_2/Fit_B_fraction_MB_hadron_noconstrain.root","READ");

  TFile *input_Fit_Extro=new TFile("InPut/Fit_B_fraction_MB_Extra_highpT.root","READ");

  
  
  TH1F *b_Fraction_fitRange_008=(TH1F *) input_Fit_range_008->Get("b_fraction_MB")->Clone("input_Fit_range_008");
  TH1F *b_Fraction_fitRange_006=(TH1F *) input_Fit_range_006->Get("b_fraction_MB")->Clone("input_Fit_range_006");

  TH1F *b_Fraction=(TH1F *) input_Fit->Get("b_fraction_MB")->Clone("input_Fit");
  TH1F *b_Fraction_kaon=(TH1F *) input_Fit_kaon->Get("b_fraction_MB")->Clone("input_Fit_kaon");
  TH1F *b_Fraction_hadron=(TH1F *) input_Fit_hadron->Get("b_fraction_MB")->Clone("input_Fit_hadron");
  TH1F *b_Fraction_DF=(TH1F *) input_Fit_DF->Get("b_fraction_MB")->Clone("input_Fit_DF");
  TH1F *b_Fraction_BF=(TH1F *) input_Fit_BF->Get("b_fraction_MB")->Clone("input_Fit_BF");
  TH1F *b_Fraction_D_weight=(TH1F *) input_Fit_BF->Get("b_fraction_MB")->Clone("input_Fit_D_weight");
  TH1F *b_Fractio_tight_nsigma_E=(TH1F *) input_Fit_tight_nsigmaE->Get("b_fraction_MB")->Clone("input_Fit_tight_nsigmaE");
  TH1F *b_Fractio_extrop=(TH1F *) input_Fit_Extro->Get("b_fraction_MB")->Clone("input_Fit_Extra");
  

  b_Fraction->SetMarkerColor(2);
  b_Fraction->SetLineColor(2);
  b_Fraction->SetMarkerStyle(20);

  
  b_Fraction_fitRange_008->SetMarkerColor(1);
  b_Fraction_fitRange_008->SetLineColor(1);
  b_Fraction_fitRange_008->SetMarkerStyle(20);

  b_Fraction_fitRange_006->SetMarkerColor(1);
  b_Fraction_fitRange_006->SetLineColor(1);
  b_Fraction_fitRange_006->SetMarkerStyle(24);

  
  b_Fraction_kaon->SetMarkerColor(3);
  b_Fraction_kaon->SetLineColor(3);
  b_Fraction_kaon->SetMarkerStyle(20);

  b_Fraction_hadron->SetMarkerColor(3);
  b_Fraction_hadron->SetLineColor(3);
  b_Fraction_hadron->SetMarkerStyle(24);

  b_Fraction_DF->SetMarkerColor(4);
  b_Fraction_DF->SetLineColor(4);
  b_Fraction_DF->SetMarkerStyle(20);

  b_Fraction_BF->SetMarkerColor(4);
  b_Fraction_BF->SetLineColor(4);
  b_Fraction_BF->SetMarkerStyle(24);

  b_Fraction_D_weight->SetMarkerColor(7);
  b_Fraction_D_weight->SetLineColor(7);
  b_Fraction_D_weight->SetMarkerStyle(24);

  b_Fractio_tight_nsigma_E->SetMarkerColor(9);
  b_Fractio_tight_nsigma_E->SetMarkerStyle(21);
  b_Fractio_tight_nsigma_E->SetMarkerColor(9);

  b_Fractio_extrop->SetMarkerColor(11);
  b_Fractio_extrop->SetMarkerStyle(21);
  b_Fractio_extrop->SetMarkerColor(11);
  
  
  
  TH2F *h6=new TH2F("h6","",100,1,8.5,100,0,1.5);
    h6->GetXaxis()->SetTitle("p_{T}^{e} (GeV/c)");
    h6->GetYaxis()->SetTitle("B#rightarrow NPE / inclusive#rightarrow NPE");
    //      h6->GetXaxis()->SetTitleSize(0.04);
    h6->GetXaxis()->SetLabelSize(0.05);
    h6->GetYaxis()->SetLabelSize(0.05);
    // h6->GetYaxis()->SetTitleOffset(1);
    // h6->GetXaxis()->SetTitleOffset(1);
    
    h6->GetXaxis()->CenterTitle(true);
    h6->GetYaxis()->CenterTitle(true);

    TLegend *legend  = new TLegend(0.15,0.6,0.55,0.9);
    legend ->AddEntry(b_Fraction,"Default","p");
    // legend ->AddEntry(b_Fraction_fitRange_008,"Change fit range(0.1 #rightarrow 0.08cm)","p");
    // legend ->AddEntry(b_Fraction_fitRange_006,"Change fit range(0.1 #rightarrow 0.06cm)","p");
    // legend ->AddEntry(b_Fraction_kaon,"Change hadron template (#pi #rightarrow kaon)","p");
    // legend ->AddEntry(b_Fraction_hadron," Change hadron template (#pi #rightarrow hadron)","p");
    // legend ->AddEntry(b_Fraction_DF,"Change Charm frg.","P");
    // legend ->AddEntry(b_Fraction_BF,"Change Bottom frg.","P");
    // legend ->AddEntry(b_Fraction_D_weight,"change charm pt weight (FONLL #rightarrow Data)","p");
    // //   legend ->AddEntry(b_Fractio_tight_nsigma_E,"Tight n#sigma_{e} to (-0.5,3)","p");
    legend ->AddEntry(b_Fractio_tight_nsigma_E,"No constrain on hadron","p");

    //  legend ->AddEntry(b_Fractio_extrop,"Correct data shape at low statistcis. bin","p");
    
    legend ->SetBorderSize(0);
    legend ->SetTextSize(0.03);
    legend ->SetFillStyle(0);
    legend->SetTextFont(62);

    for(int i=0;i< b_Fraction->GetNbinsX();i++)
      {
    
    	if(i<=4)

	  b_Fractio_extrop->SetBinContent(i+1,b_Fraction->GetBinContent(i+1));
      }
    
  TCanvas *c2=new TCanvas("c2","",1000,1200);
    c2->cd();
    h6->Draw();


    b_Fraction_fitRange_008->Draw("same");
    b_Fraction_fitRange_006->Draw("same");


    b_Fraction_kaon->Draw("same");
    b_Fraction_hadron->Draw("same");
    b_Fraction_DF->Draw("same");
    b_Fraction_BF->Draw("same");
    b_Fraction_D_weight->Draw("same");

    b_Fractio_tight_nsigma_E->Draw("samePE");
    b_Fractio_extrop->Draw("samePE");
    b_Fraction->Draw("same");
    b_Fractio_tight_nsigma_E->Draw("samePE");
    legend->Draw();

    TH1F *diff=(TH1F *) b_Fractio_tight_nsigma_E->Clone("diff");

    
    for(int i=0;i< b_Fraction->GetNbinsX();i++)
      {

    	diff->SetBinContent(i+1,abs(b_Fractio_tight_nsigma_E->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1)));
      }
    diff->Draw("samehist");
    //    return ;

    // pp_sts->GetYaxis()->SetRangeUser(0,1);
    // pp_sts->Draw("");
    // b_fraction_pp_sts->Draw("samePE");
    // Npe_AuAuRaa_sts->Draw("samePE");
    // b_fraction_AuAu_sts->Draw("samePE");

    c2->SaveAs("check.pdf");


    TH1F * b_Fraction_sys= (TH1F *) b_Fraction->Clone("b_Fraction_sys");



    for(int i=0;i< b_Fraction->GetNbinsX();i++)
      {

	Float_t minus_all=0.;
	Float_t plus_all=0.;
	Float_t sys_all=0.;
	Float_t sys_all_2=0.;

	    
       cout<<setiosflags(ios::fixed)<<setiosflags(ios::right)<<setprecision(6)<<setw(4);
       cout<<"\t"<<mh1Title[i];
	cout<<"\t"<<(b_Fraction_fitRange_006->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	cout<<"\t"<<(b_Fraction_kaon->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	cout<<"\t"<<(b_Fraction_DF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	cout<<"\t"<<(b_Fraction_BF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	cout<<"\t"<<(b_Fraction_D_weight->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	cout<<"\t"<<(b_Fractio_tight_nsigma_E->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	// if(i<=4)
	  
	// cout<<"\t"<<0.0;
	// else
	  cout<<"\t"<<(b_Fractio_extrop->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	

	if((b_Fraction_fitRange_006->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1)<=0)
	  {
	    
	    minus_all+=(b_Fraction_fitRange_006->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);

	  }
	else
	  {
	    plus_all+=(b_Fraction_fitRange_006->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	  }


	if((b_Fraction_kaon->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1)<=0)
	  {
	    minus_all+=(b_Fraction_kaon->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	  }
	else
	  {
	    plus_all+=(b_Fraction_kaon->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	  }

	if((b_Fraction_DF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1)<=0)
	  {
	    minus_all+=(b_Fraction_DF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	  }
	else
	  {
	    plus_all+=(b_Fraction_DF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	  }

	if((b_Fraction_BF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1)<=0)
	  {
	    minus_all+=(b_Fraction_BF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	  }
	else
	  {
	    plus_all+=(b_Fraction_BF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	  }

	if((b_Fraction_D_weight->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1)<=0)
	  {
	    minus_all+=(b_Fraction_D_weight->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	  }
	else
	  {
	    plus_all+=(b_Fraction_D_weight->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1);
	  }


	
	if(abs(minus_all)>plus_all)
	  sys_all=abs(minus_all);
	  else
	    sys_all=plus_all;


	sys_all_2=sqrt(
		       ((b_Fraction_fitRange_006->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))*((b_Fraction_fitRange_006->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))
		       +((b_Fraction_kaon->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1)*(b_Fraction_kaon->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))
		       +((b_Fraction_DF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))*((b_Fraction_DF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))
		       +((b_Fraction_BF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))*((b_Fraction_BF->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))
		       +((b_Fractio_tight_nsigma_E->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1)*(b_Fractio_tight_nsigma_E->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))
			 +((b_Fractio_extrop->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))*((b_Fractio_extrop->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))
		       

			 +((b_Fraction_D_weight->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1))*((b_Fraction_D_weight->GetBinContent(i+1)-b_Fraction->GetBinContent(i+1))/b_Fraction->GetBinContent(i+1)));

	
	b_Fraction_sys->SetBinError(i+1,b_Fraction_sys->GetBinContent(i+1)*sys_all_2);
	// cout<<"\t"<<minus_all;
	// cout<<"\t"<<plus_all;
	cout<<"\t"<<sys_all_2;


	cout<<endl;

      }

    TFile *B_fraction_sys=new TFile("B_fraction_sys.root","RECREATE");
    b_Fraction_sys->Write();
    B_fraction_sys->Close();
  return ;

    
    
    
    
    
    
    

    
  
  return ;

}

TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex)
{
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
}
