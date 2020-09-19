/*

Written by D. Kikola
2009
Edited by Christopher B. Powell
2010
CBPowell@lbl.gov
--------------------------------

Histogram class to initialise, write, 
save and delete histograms. Histos 
are only written if they have entries.

*/

#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TH3.h>
#include <TH2.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TText.h>
#include <TLegend.h>
#include <TLine.h>
#include "Histogram.h"
#include <TProfile.h>
#include <TMath.h>
using namespace std;

Histogram::Histogram() {

  cout <<"\tInitialising Histograms";
  const int  nDcasDca = 54;
  Double_t const  DcaEdgeDca[nDcasDca+1] = {-0.1   , -0.09 ,     -0.08  ,   -0.07    , -0.06    , -0.05 , -0.0475 , -0.045 , -0.0425 , -0.04 , -0.0375 , -0.035 , -0.0325 , -0.03 , -0.0275 , -0.025 , -0.0225 , -0.02,-0.018,-0.016,-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014,0.016,0.018,0.02 ,0.0225 , 0.025 , 0.0275 , 0.03 , 0.0325 , 0.035 , 0.0375 , 0.04 , 0.0425 , 0.045 , 0.0475 , 0.05    , 0.06  ,  0.07    , 0.08    , 0.09   ,0.1};
  cout<< " Number of dca bin " <<sizeof(DcaEdgeDca)/sizeof( DcaEdgeDca[1])<<endl;

  for(int i=0;i<nDcasDca+1;i++)
    {
      cout<< " Dca binning "<< i<< " "<< DcaEdgeDca[i+1]-DcaEdgeDca[i]<<endl;
    }


  for(Int_t iTrg=0;iTrg<nTrg;iTrg++)  
    {
      //Event Histograms
      
      mh1nEvents[iTrg] = new TH1F(Form("mh1nEvents%i",iTrg),"hnEvents",10,0,10);     
      mh2hVzVsVpdVz_noCut[iTrg] = new TH2F(Form("mh2hVzVsVpdVz_noCutTrg%i",iTrg), ";TPC Vz (cm);VPD Vz (cm)", 2000, -100+1e-6, 100+1e-6, 2000, -100+1e-6, 100+1e-6);
      mh2hVzVsDiff_noCut[iTrg] = new TH2F(Form("mh2hVzVsDiff_noCutTrg%i",iTrg), ";TPC Vz (cm); Tpc Vz-VPD Vz (cm)", 200, -10+1e-6, 10+1e-6, 200, -5+1e-6, 5+1e-6); 

      mh2hVzVsVpdVz[iTrg] = new TH2F(Form("mh2hVzVsVpdVzTrg%i",iTrg), ";TPC Vz (cm);VPD Vz (cm)", 2000, -100+1e-6, 100+1e-6, 2000, -100+1e-6, 100+1e-6);
      // inclusive electron
      mh2NsigmaeVsPt[iTrg]= new TH2F(Form("mh2NsigmaeVsPtTrg%i",iTrg), ";n#sigma_{e};pT (GeV/c)", 600, -3+1e-6, 3+1e-6, 400,0,20); 
      mh1inclusive_electron[iTrg]=new TH1F(Form("mh1inclusive_electronTrg%i",iTrg), "Inclusive pT (GeV/c)", 400,0,20); 
      mh1pi_pt[iTrg]=new TH1F(Form("mh1pi_ptTrg%i",iTrg), "", 400,0,20); 

      mh2dcaVsPt[iTrg]=new TH2F(Form("mh2dcaVsPtTrg%i",iTrg),"mh2dcaVsPt",400,-0.1,0.1,400,0,20);
      mh2dcaXYVsPt[iTrg]=new TH2F(Form("mh2dcaXYVsPtTrg%i",iTrg),"mh2dcaXYVsPt",400,-0.1,0.1,400,0,20);
      mh2dcaZVsPt[iTrg]=new TH2F(Form("mh2dcaZVsPtTrg%i",iTrg),"mh2dcaZVsPt",400,-0.1,0.1,400,0,20);



      
      mh2NsigmaeVsPt_HFT[iTrg]= new TH2F(Form("mh2NsigmaeVsPt_HFT_Trg%i",iTrg), ";n#sigma_{e};pT (GeV/c)", 600, -3+1e-6, 3+1e-6, 400,0,20); 
      mh1inclusive_electron_HFT[iTrg]=new TH1F(Form("mh1inclusive_electron_HFT_Trg%i",iTrg), "Inclusive pT (GeV/c)", 400,0,20); 
      mh1pi_pt_HFT[iTrg]=new TH1F(Form("mh1pi_pt_HFT_Trg%i",iTrg), "", 400,0,20); 
      mh2dcaVsPt_HFT[iTrg]=new TH2F(Form("mh2dcaVsPt_HFT_Trg%i",iTrg),"mh2dcaVsPt",400,-0.1,0.1,400,0,20);
      mh2dcaXYVsPt_HFT[iTrg]=new TH2F(Form("mh2dcaXYVsPt_HFT_Trg%i",iTrg),"mh2dcaXYVsPt",400,-0.1,0.1,400,0,20);
      mh2dcaZVsPt_HFT[iTrg]=new TH2F(Form("mh2dcaZVsPt_HFT_Trg%i",iTrg),"mh2dcaZVsPt",400,-0.1,0.1,400,0,20);

      mh3pT_dcaXY_Phi_HFT_EtaPlus[iTrg]=new TH3F(Form("mh3pT_dcaXY_Phi_HFT_EtaPlus_Trg%i",iTrg),"",80,-0.1,0.1,200,0,10,10,-3.14,3.14);
      mh3pT_dcaXY_Phi_HFT_EtaMinus[iTrg]=new TH3F(Form("mh3pT_dcaXY_Phi_HFT_EtaMinus_Trg%i",iTrg),"",80,-0.1,0.1,200,0,10,10,-3.14,3.14);
      mh2dcaXYVsPt_HFT_Positron[iTrg]=new TH2F(Form("mh2dcaXYVsPt_HFT_PositronTrg%i",iTrg),"",80,-0.1,0.1,400,0,20);
      mh2dcaXYVsPt_HFT_Electron[iTrg]=new TH2F(Form("mh2dcaXYVsPt_HFT_ElectronTrg%i",iTrg),"",80,-0.1,0.1,400,0,20);

      
      // Photonic electron
      
      mh3InvMassVsPtVsPairdca_unlike[iTrg]=new TH3F(Form("mh3InvMassVsPtVsPairdca_unlikeTrg%i",iTrg),";mass;pt;Pairdca",60,0,0.3,200,0,20,10,0,1);
      mh3InvMassVsPtVsPairdca_like[iTrg]=new TH3F(Form("mh3InvMassVsPtVsPairdca_likeTrg%i",iTrg),";mass;pt;Pairdca",60,0,0.3,200,0,20,10,0,1);
      
      
      
      mh2InvMassVsPt_unlike[iTrg] =new  TH2F(Form("mh2InvMassVsPt_unlikeTrg%i",iTrg), ";InvMassVsPt_unlike;pT (GeV/c)", 100, 0, 0.2, 400, 0, 20); ;
      mh2InvMassVsPt_like[iTrg]=new  TH2F(Form("mh2InvMassVsPt_likeTrg%i",iTrg), ";InvMassVsPt_like;pT (GeV/c)", 100, 0, 0.2, 400, 0, 20); ;;
      
      mh2PairdcaVsPt_unlike[iTrg] =new  TH2F(Form("mh2PairdcaVsPt_unlikeTrg%i",iTrg), ";PairdcaVsPt_unlike;pT (GeV/c)", 800, 0,1, 400, 0, 20); ;
      mh2PairdcaVsPt_like[iTrg]=new  TH2F(Form("mh2PairdcaVsPt_likeTrg%i",iTrg), ";PairdcaVsPt_like;pT (GeV/c)", 800, 0,1, 400, 0, 20); ;;

      mh2dcaVsPt_unlike[iTrg] =new  TH2F(Form("mh2dcaVsPt_unlikeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;
      mh2dcaVsPt_like[iTrg]=new  TH2F(Form("mh2dcaVsPt_likeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;;

      mh2dcaXYVsPt_unlike[iTrg] =new  TH2F(Form("mh2dcaXYVsPt_unlikeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;
      mh2dcaXYVsPt_like[iTrg]=new  TH2F(Form("mh2dcaXYVsPt_likeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;;

      mh2dcaZVsPt_unlike[iTrg] =new  TH2F(Form("mh2dcaZVsPt_unlikeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;
      mh2dcaZVsPt_like[iTrg]=new  TH2F(Form("mh2dcaZVsPt_likeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;;
      
      mh2ConversionXVsY_unlike[iTrg]=new TH2F(Form("mh2ConversionXVsY_unlikeTrg%i",iTrg),"hPEUSOyOx; Ox (cm); Oy (cm)",600,-30,30,300,-30,30);;
      mh2ConversionXVsY_like[iTrg]=new TH2F(Form("mh2ConversionXVsY_likeTrg%i",iTrg),"hPEUSOyOx; Ox (cm); Oy (cm)",600,-30,30,300,-30,30);;
  
      mh2ConversionRVsZ_unlike[iTrg]=new  TH2F(Form("mh2ConversionRVsZ_unlikeTrg%i",iTrg),"hPEUSOrOz; Oz (cm); Or (cm)",600,-30,30,300,-30,30);;
      mh2ConversionRVsZ_like[iTrg] =new  TH2F(Form("mh2ConversionRVsZ_likeTrg%i",iTrg),"hPEUSOrOz; Oz (cm); Or (cm)",600,-30,30,300,-30,30);;
  
      mh2ConversionRVsPt_unlike[iTrg]=new  TH2F(Form("mh2ConversionRVsPt_unlikeTrg%i",iTrg),"RVsPt",300,0,30,400,0,20);
      mh2ConversionRVsPt_like[iTrg]=new  TH2F(Form("mh2ConversionRVsPt_likeTrg%i",iTrg),"RvsPt",300,0,30,400,0,20);

      mh2partnerNsigmaeVspt_unlike[iTrg]=new TH2F( Form("mh2partnerNsigmaeVspt_unlikeTrg%i",iTrg), ";partner; pT (GeV/c)", 350, -3.5+1e-6, 3.5+1e-6, 400,0,20);
      mh2partnerNsigmaeVspt_like[iTrg]=new TH2F( Form("mh2partnerNsigmaeVspt_likeTrg%i",iTrg), ";partner; pT (GeV/c)", 350, -3.5+1e-6, 3.5+1e-6, 400,0,20);;
      mh2NsigmaeVspt_unlike[iTrg]=new TH2F( Form("mh2NsigmaeVspt_unlikeTrg%i",iTrg), ";; pT (GeV/c)", 300, -3+1e-6, 3+1e-6, 400,0,20);
      mh2NsigmaeVspt_like[iTrg]=new TH2F( Form("mh2NsigmaeVspt_likeTrg%i",iTrg), ";; pT (GeV/c)", 300, -3+1e-6, 3+1e-6, 400,0,20);;

      // EMC

      mh2Dz_unlike[iTrg]=new TH2F(Form("mh2Dz_unlikeTrg%i",iTrg),"",100,-5,5,400 ,0,20.);
      mh2Dz_like[iTrg]=new TH2F(Form("mh2Dz_likeTrg%i",iTrg),"",100,-5,5,400 ,0,20.);

      mh2Dphi_unlike[iTrg]=new TH2F(Form("mh2Dphi_unlikeTrg%i",iTrg),"",100,-0.1,0.1,400 ,0,20.);
      mh2Dphi_like[iTrg]=new TH2F(Form("mh2Dphi_likeTrg%i",iTrg),"",100,-0.1,0.1,400 ,0,20.);

      mh2Poe_unlike[iTrg]=new TH2F(Form("mh2Poe_unlikeTrg%i",iTrg),"",400 ,0,20.,100,0,5);
      mh2Poe_like[iTrg]=new TH2F(Form("mh2Poe_likeTrg%i",iTrg),"",400 ,0,20.,100,0,5);




      // inclusive 
      mh2NsigmaeVsPt[iTrg]->Sumw2();
      mh1inclusive_electron[iTrg]->Sumw2();
      mh2dcaVsPt[iTrg]->Sumw2();
      mh2dcaXYVsPt[iTrg]->Sumw2();
      mh2dcaZVsPt[iTrg]->Sumw2();
      mh1pi_pt[iTrg]->Sumw2();
      mh1pi_pt_HFT[iTrg]->Sumw2();


      mh3pT_dcaXY_Phi_HFT_EtaPlus[iTrg]->Sumw2();
      mh3pT_dcaXY_Phi_HFT_EtaMinus[iTrg]->Sumw2();
      
      mh2dcaXYVsPt_HFT_Positron[iTrg]->Sumw2();
      mh2dcaXYVsPt_HFT_Electron[iTrg]->Sumw2();
      
      mh3InvMassVsPtVsPairdca_unlike[iTrg]->Sumw2();
      mh3InvMassVsPtVsPairdca_like[iTrg]->Sumw2();


      
      mh2InvMassVsPt_unlike[iTrg]->Sumw2();
      mh2InvMassVsPt_like[iTrg]->Sumw2();

      mh2PairdcaVsPt_unlike[iTrg]->Sumw2();
      mh2PairdcaVsPt_like[iTrg]->Sumw2();

      mh2dcaVsPt_unlike[iTrg]->Sumw2();
      mh2dcaVsPt_like[iTrg]->Sumw2();

      mh2dcaXYVsPt_unlike[iTrg]->Sumw2();
      mh2dcaXYVsPt_like[iTrg]->Sumw2();

      mh2dcaZVsPt_unlike[iTrg]->Sumw2();
      mh2dcaZVsPt_like[iTrg]->Sumw2();  
    
      mh2ConversionXVsY_unlike[iTrg]->Sumw2();
      mh2ConversionXVsY_like[iTrg]->Sumw2();
  
      mh2ConversionRVsZ_unlike[iTrg]->Sumw2();
      mh2ConversionRVsZ_like[iTrg]->Sumw2();
  
      mh2ConversionRVsPt_unlike[iTrg]->Sumw2();
      mh2ConversionRVsPt_like[iTrg]->Sumw2();

      mh2partnerNsigmaeVspt_unlike[iTrg]->Sumw2();
      mh2partnerNsigmaeVspt_like[iTrg]->Sumw2();
      mh2NsigmaeVspt_unlike[iTrg]->Sumw2();
      mh2NsigmaeVspt_like[iTrg]->Sumw2();

      // EMC

      mh2Dz_unlike[iTrg]->Sumw2();
      mh2Dz_like[iTrg]->Sumw2();

      mh2Dphi_unlike[iTrg]->Sumw2();
      mh2Dphi_like[iTrg]->Sumw2();

      mh2Poe_unlike[iTrg]->Sumw2();
      mh2Poe_like[iTrg]->Sumw2();
      

       
      // with HFT

      mh3InvMassVsPtVsPairdca_HFT_unlike[iTrg]=new TH3F(Form("mh3InvMassVsPtVsPairdca_HFT_unlikeTrg%i",iTrg),";mass;pt;Pairdca",60,0,0.3,200,0,20,10,0,1);
      mh3InvMassVsPtVsPairdca_HFT_like[iTrg]=new TH3F(Form("mh3InvMassVsPtVsPairdca_HFT_likeTrg%i",iTrg),";mass;pt;Pairdca",60,0,0.3,200,0,20,10,0,1);
						  
      mh2InvMassVsPt_HFT_unlike[iTrg] =new  TH2F(Form("mh2InvMassVsPt_HFT_unlikeTrg%i",iTrg), ";InvMassVsPt_HFT_unlike;pT (GeV/c)", 100, 0, 0.2, 400, 0, 20); ;
      mh2InvMassVsPt_HFT_like[iTrg]=new  TH2F(Form("mh2InvMassVsPt_HFT_likeTrg%i",iTrg), ";InvMassVsPt_HFT_like;pT (GeV/c)", 100, 0, 0.2, 400, 0, 20); ;;

      mh2PairdcaVsPt_HFT_unlike[iTrg] =new  TH2F(Form("mh2PairdcaVsPt_HFT_unlikeTrg%i",iTrg), ";PairdcaVsPt_HFT_unlike;pT (GeV/c)", 800, 0, 1, 400, 0, 20); ;
      mh2PairdcaVsPt_HFT_like[iTrg]=new  TH2F(Form("mh2PairdcaVsPt_HFT_likeTrg%i",iTrg), ";PairdcaVsPt_HFT_like;pT (GeV/c)", 800, 0,1, 400, 0, 20); ;;



      mh2dcaVsPt_HFT_unlike[iTrg] =new  TH2F(Form("mh2dcaVsPt_HFT_unlikeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;
      mh2dcaVsPt_HFT_like[iTrg]=new  TH2F(Form("mh2dcaVsPt_HFT_likeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;;
      
      mh2dcaXYVsPt_HFT_unlike[iTrg] =new  TH2F(Form("mh2dcaXYVsPt_HFT_unlikeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;
      mh2dcaXYVsPt_HFT_like[iTrg]=new  TH2F(Form("mh2dcaXYVsPt_HFT_likeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;;
      
      mh2dcaZVsPt_HFT_unlike[iTrg] =new  TH2F(Form("mh2dcaZVsPt_HFT_unlikeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;
      mh2dcaZVsPt_HFT_like[iTrg]=new  TH2F(Form("mh2dcaZVsPt_HFT_likeTrg%i",iTrg), "", 400,-0.1,0.1, 400, 0, 20); ;;

      
      mh2ConversionXVsY_HFT_unlike[iTrg]=new TH2F(Form("mh2ConversionXVsY_HFT_unlikeTrg%i",iTrg),"hPEUSOyOx; Ox (cm); Oy (cm)",600,-30,30,300,-30,30);;
      mh2ConversionXVsY_HFT_like[iTrg]=new TH2F(Form("mh2ConversionXVsY_HFT_likeTrg%i",iTrg),"hPEUSOyOx; Ox (cm); Oy (cm)",600,-30,30,300,-30,30);;
  
      mh2ConversionRVsZ_HFT_unlike[iTrg]=new  TH2F(Form("mh2ConversionRVsZ_HFT_unlikeTrg%i",iTrg),"hPEUSOrOz; Oz (cm); Or (cm)",600,-30,30,300,-30,30);;
      mh2ConversionRVsZ_HFT_like[iTrg] =new  TH2F(Form("mh2ConversionRVsZ_HFT_likeTrg%i",iTrg),"hPEUSOrOz; Oz (cm); Or (cm)",600,-30,30,300,-30,30);;
  
      mh2ConversionRVsPt_HFT_unlike[iTrg]=new  TH2F(Form("mh2ConversionRVsPt_HFT_unlikeTrg%i",iTrg),"RVsPt",300,0,30,400,0,20);
      mh2ConversionRVsPt_HFT_like[iTrg]=new  TH2F(Form("mh2ConversionRVsPt_HFT_likeTrg%i",iTrg),"RvsPt",300,0,30,400,0,20);

      mh2partnerNsigmaeVspt_HFT_unlike[iTrg]=new TH2F( Form("mh2partnerNsigmaeVspt_HFT_unlikeTrg%i",iTrg), ";partner; pT (GeV/c)", 350, -3.5+1e-6, 3.5+1e-6, 400,0,20);
      mh2partnerNsigmaeVspt_HFT_like[iTrg]=new TH2F( Form("mh2partnerNsigmaeVspt_HFT_likeTrg%i",iTrg), ";partner; pT (GeV/c)", 350, -3.5+1e-6, 3.5+1e-6, 400,0,20);;

      mh2NsigmaeVspt_HFT_unlike[iTrg]=new TH2F( Form("mh2NsigmaeVspt_HFT_unlikeTrg%i",iTrg), ";; pT (GeV/c)", 300, -3+1e-6, 3+1e-6, 400,0,20);
      mh2NsigmaeVspt_HFT_like[iTrg]=new TH2F( Form("mh2NsigmaeVspt_HFT_likeTrg%i",iTrg), ";; pT (GeV/c)", 300, -3+1e-6, 3+1e-6, 400,0,20);;

      mh2Dz_HFT_unlike[iTrg]=new TH2F(Form("mh2Dz_HFT_unlikeTrg%i",iTrg),"",100,-5,5,400 ,0,20.);
      mh2Dz_HFT_like[iTrg]=new TH2F(Form("mh2Dz_HFT_likeTrg%i",iTrg),"",100,-5,5,400 ,0,20.);
      
      mh2Dphi_HFT_unlike[iTrg]=new TH2F(Form("mh2Dphi_HFT_unlikeTrg%i",iTrg),"",100,-0.1,0.1,400 ,0,20.);
      mh2Dphi_HFT_like[iTrg]=new TH2F(Form("mh2Dphi_HFT_likeTrg%i",iTrg),"",100,-0.1,0.1,400 ,0,20.);

      mh2Poe_HFT_unlike[iTrg]=new TH2F(Form("mh2Poe_HFT_unlikeTrg%i",iTrg),"",400 ,0,20.,100,0,5);
      mh2Poe_HFT_like[iTrg]=new TH2F(Form("mh2Poe_HFT_likeTrg%i",iTrg),"",400 ,0,20.,100,0,5);

      // inclusive 
      mh2NsigmaeVsPt_HFT[iTrg]->Sumw2();
      mh1inclusive_electron_HFT[iTrg]->Sumw2();
      mh2dcaVsPt_HFT[iTrg]->Sumw2();
      mh2dcaXYVsPt_HFT[iTrg]->Sumw2();
      mh2dcaZVsPt_HFT[iTrg]->Sumw2();


      mh3InvMassVsPtVsPairdca_HFT_unlike[iTrg]->Sumw2();
      mh3InvMassVsPtVsPairdca_HFT_like[iTrg]->Sumw2();
						  
      mh2InvMassVsPt_HFT_unlike[iTrg]->Sumw2(); 
      mh2InvMassVsPt_HFT_like[iTrg]->Sumw2();

       mh2PairdcaVsPt_HFT_unlike[iTrg]->Sumw2();
      mh2PairdcaVsPt_HFT_like[iTrg]->Sumw2();

      mh2dcaVsPt_HFT_unlike[iTrg]->Sumw2();
      mh2dcaVsPt_HFT_like[iTrg]->Sumw2();
      
      mh2dcaXYVsPt_HFT_unlike[iTrg]->Sumw2();
      mh2dcaXYVsPt_HFT_like[iTrg]->Sumw2();
      
      mh2dcaZVsPt_HFT_unlike[iTrg]->Sumw2();
      mh2dcaZVsPt_HFT_like[iTrg]->Sumw2();
      
      mh2ConversionXVsY_HFT_unlike[iTrg]->Sumw2();
      mh2ConversionXVsY_HFT_like[iTrg]->Sumw2();
  
      mh2ConversionRVsZ_HFT_unlike[iTrg]->Sumw2();
      mh2ConversionRVsZ_HFT_like[iTrg]->Sumw2();
  
      mh2ConversionRVsPt_HFT_unlike[iTrg]->Sumw2();
      mh2ConversionRVsPt_HFT_like[iTrg]->Sumw2();

      mh2partnerNsigmaeVspt_HFT_unlike[iTrg]->Sumw2();
      mh2partnerNsigmaeVspt_HFT_like[iTrg]->Sumw2();

      mh2NsigmaeVspt_HFT_unlike[iTrg]->Sumw2();
      mh2NsigmaeVspt_HFT_like[iTrg]->Sumw2();

      mh2Dz_HFT_unlike[iTrg]->Sumw2();
      mh2Dz_HFT_like[iTrg]->Sumw2();
      
      mh2Dphi_HFT_unlike[iTrg]->Sumw2();
      mh2Dphi_HFT_like[iTrg]->Sumw2();
      

    }

    cout << " ...done with Histogram Init()!" << endl;
}

void Histogram::writeData(TFile *outputFile) const {

	outputFile->cd();

	cout<<"\nWriting histos..."<<endl;

	for(Int_t iTrg=0;iTrg<nTrg;iTrg++)
	  {
	    // Event 
	    if(mh1nEvents[iTrg]->GetEntries()) mh1nEvents[iTrg]->Write();
	    if(mh2hVzVsVpdVz_noCut[iTrg]->GetEntries())mh2hVzVsVpdVz_noCut[iTrg]->Write();
	    if(mh2hVzVsDiff_noCut[iTrg]->GetEntries()) mh2hVzVsDiff_noCut[iTrg]->Write();
	if(mh2hVzVsVpdVz[iTrg]->GetEntries())mh2hVzVsVpdVz[iTrg]->Write();
	// Inclusive electron 
	if(mh1inclusive_electron[iTrg]->GetEntries())mh1inclusive_electron[iTrg]->Write();
	if(mh2NsigmaeVsPt[iTrg]->GetEntries())mh2NsigmaeVsPt[iTrg]->Write();
	if(mh2dcaVsPt[iTrg]->GetEntries())mh2dcaVsPt[iTrg]->Write();
	if(mh2dcaXYVsPt[iTrg]->GetEntries())mh2dcaXYVsPt[iTrg]->Write();
	if(mh2dcaZVsPt[iTrg]->GetEntries())mh2dcaZVsPt[iTrg]->Write();

	if(mh3pT_dcaXY_Phi_HFT_EtaPlus[iTrg]->GetEntries()) mh3pT_dcaXY_Phi_HFT_EtaPlus[iTrg]->Write();
	if(mh3pT_dcaXY_Phi_HFT_EtaMinus[iTrg]->GetEntries()) mh3pT_dcaXY_Phi_HFT_EtaMinus[iTrg]->Write();

	if(mh2dcaXYVsPt_HFT_Positron[iTrg]->GetEntries()) mh2dcaXYVsPt_HFT_Positron[iTrg]->Write();
	if(mh2dcaXYVsPt_HFT_Electron[iTrg]->GetEntries()) mh2dcaXYVsPt_HFT_Electron[iTrg]->Write();



	if(mh1inclusive_electron_HFT[iTrg]->GetEntries())mh1inclusive_electron_HFT[iTrg]->Write();
	if(mh1pi_pt[iTrg]->GetEntries())mh1pi_pt[iTrg]->Write();
	if(mh1pi_pt_HFT[iTrg]->GetEntries())mh1pi_pt_HFT[iTrg]->Write();
	if(mh2NsigmaeVsPt_HFT[iTrg]->GetEntries())mh2NsigmaeVsPt_HFT[iTrg]->Write();


	if(mh2dcaVsPt_HFT[iTrg]->GetEntries())mh2dcaVsPt_HFT[iTrg]->Write();
	if(mh2dcaXYVsPt_HFT[iTrg]->GetEntries())mh2dcaXYVsPt_HFT[iTrg]->Write();
	if(mh2dcaZVsPt_HFT[iTrg]->GetEntries())mh2dcaZVsPt_HFT[iTrg]->Write();



	// Photonic electron 
	// if(mh3InvMassVsPtVsPairdca_unlike[iTrg]->GetEntries()) mh3InvMassVsPtVsPairdca_unlike[iTrg]->Write();
	// if(mh3InvMassVsPtVsPairdca_like[iTrg]->GetEntries()) mh3InvMassVsPtVsPairdca_like[iTrg]->Write();

	if(mh2InvMassVsPt_unlike[iTrg]->GetEntries())mh2InvMassVsPt_unlike[iTrg]->Write();
	if(mh2PairdcaVsPt_unlike[iTrg]->GetEntries())mh2PairdcaVsPt_unlike[iTrg]->Write();
	if(mh2dcaVsPt_unlike[iTrg]->GetEntries())mh2dcaVsPt_unlike[iTrg]->Write();
        if(mh2dcaVsPt_like[iTrg]->GetEntries())mh2dcaVsPt_like[iTrg]->Write();

        if(mh2dcaXYVsPt_unlike[iTrg]->GetEntries())mh2dcaXYVsPt_unlike[iTrg]->Write();
        if(mh2dcaXYVsPt_like[iTrg]->GetEntries())mh2dcaXYVsPt_like[iTrg]->Write();

        if(mh2dcaZVsPt_unlike[iTrg]->GetEntries())mh2dcaZVsPt_unlike[iTrg]->Write();
        if(mh2dcaZVsPt_like[iTrg]->GetEntries())mh2dcaZVsPt_like[iTrg]->Write();

	
	if(mh2ConversionXVsY_unlike[iTrg]->GetEntries())mh2ConversionXVsY_unlike[iTrg]->Write();
	
	if(mh2ConversionRVsZ_unlike[iTrg]->GetEntries())mh2ConversionRVsZ_unlike[iTrg]->Write();
	if(mh2ConversionRVsPt_unlike[iTrg]->GetEntries())mh2ConversionRVsPt_unlike[iTrg]->Write();
	
	if(mh2InvMassVsPt_like[iTrg]->GetEntries())mh2InvMassVsPt_like[iTrg]->Write();
	if(mh2PairdcaVsPt_like[iTrg]->GetEntries())mh2PairdcaVsPt_like[iTrg]->Write();
	
	if(mh2ConversionXVsY_like[iTrg]->GetEntries())mh2ConversionXVsY_like[iTrg]->Write();
	if(mh2ConversionRVsZ_like[iTrg]->GetEntries())mh2ConversionRVsZ_like[iTrg]->Write();
	if(mh2ConversionRVsPt_like[iTrg]->GetEntries())mh2ConversionRVsPt_like[iTrg]->Write();
	if(mh2partnerNsigmaeVspt_unlike[iTrg]->GetEntries()) mh2partnerNsigmaeVspt_unlike[iTrg]->Write();
	if(mh2partnerNsigmaeVspt_like[iTrg]->GetEntries()) mh2partnerNsigmaeVspt_like[iTrg]->Write();
	
	if(mh2NsigmaeVspt_unlike[iTrg]->GetEntries()) mh2NsigmaeVspt_unlike[iTrg]->Write();
	if(mh2NsigmaeVspt_like[iTrg]->GetEntries()) mh2NsigmaeVspt_like[iTrg]->Write();

	if(mh2Dz_unlike[iTrg]->GetEntries()) mh2Dz_unlike[iTrg]->Write();
	if(mh2Dz_like[iTrg]->GetEntries()) mh2Dz_like[iTrg]->Write();

	if(mh2Dphi_unlike[iTrg]->GetEntries()) mh2Dphi_unlike[iTrg]->Write();
	if(mh2Dphi_like[iTrg]->GetEntries()) mh2Dphi_like[iTrg]->Write();

	if(mh2Poe_unlike[iTrg]->GetEntries()) mh2Poe_unlike[iTrg]->Write();
	if(mh2Poe_like[iTrg]->GetEntries()) mh2Poe_like[iTrg]->Write();
	
	
	// with HFT
	// if(mh3InvMassVsPtVsPairdca_HFT_unlike[iTrg]->GetEntries()) mh3InvMassVsPtVsPairdca_HFT_unlike[iTrg]->Write();
	// if(mh3InvMassVsPtVsPairdca_HFT_like[iTrg]->GetEntries()) mh3InvMassVsPtVsPairdca_HFT_like[iTrg]->Write();
	
	if(mh2InvMassVsPt_HFT_unlike[iTrg]->GetEntries())mh2InvMassVsPt_HFT_unlike[iTrg]->Write();
	if(mh2PairdcaVsPt_HFT_unlike[iTrg]->GetEntries())mh2PairdcaVsPt_HFT_unlike[iTrg]->Write();
	if(mh2dcaVsPt_HFT_unlike[iTrg]->GetEntries())mh2dcaVsPt_HFT_unlike[iTrg]->Write();
        if(mh2dcaVsPt_HFT_like[iTrg]->GetEntries())mh2dcaVsPt_HFT_like[iTrg]->Write();

        if(mh2dcaXYVsPt_HFT_unlike[iTrg]->GetEntries())mh2dcaXYVsPt_HFT_unlike[iTrg]->Write();
        if(mh2dcaXYVsPt_HFT_like[iTrg]->GetEntries())mh2dcaXYVsPt_HFT_like[iTrg]->Write();

        if(mh2dcaZVsPt_HFT_unlike[iTrg]->GetEntries())mh2dcaZVsPt_HFT_unlike[iTrg]->Write();
        if(mh2dcaZVsPt_HFT_like[iTrg]->GetEntries())mh2dcaZVsPt_HFT_like[iTrg]->Write();

	
	if(mh2ConversionXVsY_HFT_unlike[iTrg]->GetEntries())mh2ConversionXVsY_HFT_unlike[iTrg]->Write();
	if(mh2ConversionRVsZ_HFT_unlike[iTrg]->GetEntries())mh2ConversionRVsZ_HFT_unlike[iTrg]->Write();
	if(mh2ConversionRVsPt_HFT_unlike[iTrg]->GetEntries())mh2ConversionRVsPt_HFT_unlike[iTrg]->Write();
	
	if(mh2InvMassVsPt_HFT_like[iTrg]->GetEntries())mh2InvMassVsPt_HFT_like[iTrg]->Write();
	if(mh2PairdcaVsPt_HFT_like[iTrg]->GetEntries())mh2PairdcaVsPt_HFT_like[iTrg]->Write();
	
	if(mh2ConversionXVsY_HFT_like[iTrg]->GetEntries())mh2ConversionXVsY_HFT_like[iTrg]->Write();
	if(mh2ConversionRVsZ_HFT_like[iTrg]->GetEntries())mh2ConversionRVsZ_HFT_like[iTrg]->Write();
	if(mh2ConversionRVsPt_HFT_like[iTrg]->GetEntries())mh2ConversionRVsPt_HFT_like[iTrg]->Write();
	if(mh2partnerNsigmaeVspt_HFT_unlike[iTrg]->GetEntries()) mh2partnerNsigmaeVspt_HFT_unlike[iTrg]->Write();
	if(mh2partnerNsigmaeVspt_HFT_like[iTrg]->GetEntries()) mh2partnerNsigmaeVspt_HFT_like[iTrg]->Write();

	if(mh2NsigmaeVspt_HFT_unlike[iTrg]->GetEntries()) mh2NsigmaeVspt_HFT_unlike[iTrg]->Write();
	if(mh2NsigmaeVspt_HFT_like[iTrg]->GetEntries()) mh2NsigmaeVspt_HFT_like[iTrg]->Write();

	
	if(mh2Dz_HFT_unlike[iTrg]->GetEntries()) mh2Dz_HFT_unlike[iTrg]->Write();
	if(mh2Dz_HFT_like[iTrg]->GetEntries()) mh2Dz_HFT_like[iTrg]->Write();

	if(mh2Dphi_HFT_unlike[iTrg]->GetEntries()) mh2Dphi_HFT_unlike[iTrg]->Write();
	if(mh2Dphi_HFT_like[iTrg]->GetEntries()) mh2Dphi_HFT_like[iTrg]->Write();

	  }


	cout<<"Histos saved!\n"<<endl;

}


Histogram::~Histogram() {
	
  cout<<"Deleting histos"<<endl;
  for(Int_t iTrg=0;iTrg<nTrg;iTrg++){
    //event
    delete mh1nEvents[iTrg];
    delete mh2hVzVsVpdVz_noCut[iTrg];
    delete mh2hVzVsDiff_noCut[iTrg];
    delete mh2hVzVsVpdVz[iTrg];
    //inclusive

    delete mh2NsigmaeVsPt[iTrg];
    delete mh1inclusive_electron[iTrg];
    delete mh2dcaVsPt[iTrg];
    delete mh2dcaXYVsPt[iTrg];
    delete mh2dcaZVsPt[iTrg];

    delete mh2NsigmaeVsPt_HFT[iTrg];
    delete mh1inclusive_electron_HFT[iTrg];
    delete mh2dcaVsPt_HFT[iTrg];
    delete mh2dcaXYVsPt_HFT[iTrg];
    delete mh2dcaZVsPt_HFT[iTrg];

    //photonic
    delete mh3InvMassVsPtVsPairdca_unlike[iTrg];
    delete mh3InvMassVsPtVsPairdca_like[iTrg];
    
    delete mh2InvMassVsPt_unlike[iTrg];
    delete mh2PairdcaVsPt_unlike[iTrg];

    delete mh2dcaVsPt_unlike[iTrg];
    delete mh2dcaVsPt_like[iTrg];

    delete mh2dcaXYVsPt_unlike[iTrg];
    delete mh2dcaXYVsPt_like[iTrg];

    delete mh2dcaZVsPt_unlike[iTrg];
    delete mh2dcaZVsPt_like[iTrg];


    delete mh2ConversionXVsY_unlike[iTrg];
    delete mh2ConversionRVsZ_unlike[iTrg];
    delete mh2ConversionRVsPt_unlike[iTrg];
    
    delete mh2InvMassVsPt_like[iTrg];
    delete mh2PairdcaVsPt_like[iTrg];

    delete mh2ConversionXVsY_like[iTrg];
    delete mh2ConversionRVsZ_like[iTrg];
    delete mh2ConversionRVsPt_like[iTrg];

    delete mh2partnerNsigmaeVspt_unlike[iTrg];
    delete mh2partnerNsigmaeVspt_like[iTrg];

    delete mh2NsigmaeVspt_unlike[iTrg];
    delete mh2NsigmaeVspt_like[iTrg];

    delete  mh2Dz_unlike[iTrg];
    delete  mh2Dz_like[iTrg];

    delete  mh2Dphi_unlike[iTrg];
    delete  mh2Dphi_like[iTrg];

    delete  mh2Poe_unlike[iTrg];
    delete  mh2Poe_like[iTrg];

    // with HFT

    delete mh3InvMassVsPtVsPairdca_HFT_unlike[iTrg];
    delete mh3InvMassVsPtVsPairdca_HFT_like[iTrg];
    
    delete mh2InvMassVsPt_HFT_unlike[iTrg];
    delete mh2PairdcaVsPt_HFT_unlike[iTrg];

    delete mh2dcaVsPt_HFT_unlike[iTrg];
    delete mh2dcaVsPt_HFT_like[iTrg];

    delete mh2dcaXYVsPt_HFT_unlike[iTrg];
    delete mh2dcaXYVsPt_HFT_like[iTrg];

    delete mh2dcaZVsPt_HFT_unlike[iTrg];
    delete mh2dcaZVsPt_HFT_like[iTrg];


    delete mh2ConversionXVsY_HFT_unlike[iTrg];
    delete mh2ConversionRVsZ_HFT_unlike[iTrg];
    delete mh2ConversionRVsPt_HFT_unlike[iTrg];
    
    delete mh2InvMassVsPt_HFT_like[iTrg];
    delete mh2PairdcaVsPt_HFT_like[iTrg];
    delete mh2ConversionXVsY_HFT_like[iTrg];
    delete mh2ConversionRVsZ_HFT_like[iTrg];
    delete mh2ConversionRVsPt_HFT_like[iTrg];

    delete mh2partnerNsigmaeVspt_HFT_unlike[iTrg];
    delete mh2partnerNsigmaeVspt_HFT_like[iTrg];

    delete mh2NsigmaeVspt_HFT_unlike[iTrg];
    delete mh2NsigmaeVspt_HFT_like[iTrg];

    delete  mh2Dz_HFT_unlike[iTrg];
    delete  mh2Dz_HFT_like[iTrg];

    delete  mh2Dphi_HFT_unlike[iTrg];
    delete  mh2Dphi_HFT_like[iTrg];

    
  }

    cout<<"Histos deleted!"<<endl;

}

