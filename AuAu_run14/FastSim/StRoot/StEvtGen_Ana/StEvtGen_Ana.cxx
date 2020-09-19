#include <iostream>
#include "TFile.h"
#include "TNtuple.h"
#include "cmath"
#include "TGraphErrors.h"
#include "StEvtGen_Ana.h"
#include "StEvtGen_Daughter.h"
#include "TLorentzVector.h"
using namespace std;
  
StEvtGen_Ana::StEvtGen_Ana(const char* outName)
{
  mOutputFile=new TFile(outName,"RECREATE");
  TFile *input_pi0=new TFile("/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/Weight.root","READ");
  Weight_pt_pi=(TH1D *) input_pi0->Get("Pi"); 
  Weight_pt_eta=(TH1D *) input_pi0->Get("Eta"); 
   
  gr_Weight_pt_pi=new TGraph(Weight_pt_pi); // 这是为了看下smear 之后的和data 对比，再次进行确认smear 过程是对的
  gr_Weight_pt_eta=new TGraph(Weight_pt_eta);
   
   
  TFile *weight_Charm_data=new TFile("/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/Charm_pp200_data.root","READ"); // not used
  TFile *weight_Charm_fonll=new TFile("/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/D0_pp200_FONALL.root","READ"); // not used
  TFile *weight_bottom_fonll=new TFile("/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/B_pp200_FONALL.root","READ");
 

  //  TFile *weight_Charm_Data = new TFile("/star/u/xiao00/Run14_Analysis/FastSim/StRoot/StEvtGen_Ana/weight_charm_Fit_data.root","READ"); // from xiaolong;
  TFile *weight_Charm_Data = new TFile("/star/u/xiao00/Run14_Analysis/FastSim/StRoot/StEvtGen_Ana/weight_charm_Fit_data_0_80.root","READ"); // from xiaolong;



  // Weight_pt=(TH1D *) input->Get("hFit0"); 

  //D_pp200_data=(TF1 *) weight_Charm_data->Get("levy"); //not usedi, zyj comm
  B_pp200_fonll=(TGraph *) weight_bottom_fonll->Get("B_Spectra_pp200");
  D_pp200_fonll=(TGraph *) weight_Charm_fonll->Get("D0_Spectra_pp200"); //not used

  Graph_from_F_levy_D0_0_80=(TGraph *) weight_Charm_Data->Get("Graph_from_F_levy_D0_0_80"); //D0 pt sepctrum i.e. Levy 也就是这个pt 对应多少个D0，一块加起来，就是这个pt 下，每种粒子各产生了多少个，这样就是权重,那你说，模拟的时候input HF hadron pt 是uniform 的，之后weight 就是了
  Graph_from_F_levy_Dpm_0_80=(TGraph *) weight_Charm_Data->Get("Graph_from_F_levy_Dpm_0_80");
  Graph_from_F_levy_Ds_0_80=(TGraph *) weight_Charm_Data->Get("Graph_from_F_levy_Ds_0_80");
  Graph_from_F_levy_Lc_0_80=(TGraph *) weight_Charm_Data->Get("Graph_from_F_levy_Lc_0_80");




  TFile *weight_Charm_data_fonll=new TFile("/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/Charm_dsigma_dpt_dy.root","READ");  
  gr_pp_specatra= (TGraphErrors *)weight_Charm_data_fonll->Get("gr_pp_specatra"); // not used

  cout<<" load the weight function"<<endl;
}
StEvtGen_Ana::~StEvtGen_Ana()
{
  //..
  //
}
void StEvtGen_Ana::bookHistogram()
{
  const int  nDcasDca = 54;
  Double_t const  DcaEdgeDca[nDcasDca+1] = {-0.1   , -0.09 ,     -0.08  ,   -0.07    , -0.06    , -0.05 , -0.0475 , -0.045 , -0.0425 , -0.04 , -0.0375 , -0.035 , -0.0325 , -0.03 , -0.0275 , -0.025 , -0.0225 , -0.02,-0.018,-0.016,-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014,0.016,0.018,0.02 ,0.0225 , 0.025 , 0.0275 , 0.03 , 0.0325 , 0.035 , 0.0375 , 0.04 , 0.0425 , 0.045 , 0.0475 , 0.05    , 0.06  ,  0.07    , 0.08    , 0.09   ,0.1};



  cout<< " Number of dca bin " <<sizeof(DcaEdgeDca)/sizeof( DcaEdgeDca[1])<<endl;

  for(int i=0;i<nDcasDca+1;i++)
    {
      cout<< " Dca binning "<< i<< " "<< DcaEdgeDca[i+1]-DcaEdgeDca[i]<<endl;
    }



  for(Int_t ihist=0;ihist<3;ihist++){
    mh2D0DcaVspt[ihist]=new TH2F(Form("mh2D0DcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2DplusDcaVspt[ihist]=new TH2F(Form("mh2DplusDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    
    mh2D0rDcaVspt[ihist]=new TH2F(Form("mh2D0rDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2LcrDcaVspt[ihist]=new TH2F(Form("mh2LcrDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2DplusrDcaVspt[ihist]=new TH2F(Form("mh2DplusrDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2DsplusrDcaVspt[ihist]=new TH2F(Form("mh2DsplusrDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    
    mh2B0DcaVspt[ihist]=new TH2F(Form("mh2B0DcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2BplusDcaVspt[ihist]=new TH2F(Form("mh2BplusDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);

    mh2B0rDcaVspt[ihist]=new TH2F(Form("mh2B0rDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2BplusrDcaVspt[ihist]=new TH2F(Form("mh2BplusrDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    
    mh2pi0DcaVspt[ihist]=new TH2F(Form("mh2pi0DcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2pi0rDcaVspt[ihist]=new TH2F(Form("mh2pi0rDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);

    mh2etaDcaVspt[ihist]=new TH2F(Form("mh2etaDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);
    mh2etarDcaVspt[ihist]=new TH2F(Form("mh2etarDcaVspt%i",ihist),"",400,0,20,400,-0.1,0.1);

    mh2D0DcaVspt[ihist]->Sumw2();
    mh2DplusDcaVspt[ihist]->Sumw2();

    mh2D0rDcaVspt[ihist]->Sumw2();
    mh2DplusrDcaVspt[ihist]->Sumw2();
    mh2DsplusrDcaVspt[ihist]->Sumw2();
    mh2LcrDcaVspt[ihist]->Sumw2();

    mh2B0DcaVspt[ihist]->Sumw2(); 
    mh2BplusDcaVspt[ihist]->Sumw2();

    mh2B0rDcaVspt[ihist]->Sumw2();
    mh2BplusrDcaVspt[ihist]->Sumw2();
    
    mh2pi0DcaVspt[ihist]->Sumw2();
    mh2pi0rDcaVspt[ihist]->Sumw2();

    mh2etaDcaVspt[ihist]->Sumw2();
    mh2etarDcaVspt[ihist]->Sumw2();
  }

  // // D0 NPE consistent check
  // mh1rpt_D_e=new TH1F("mh1rpt_D_e","",400,0,20);
  // mh1pt_D_e=new TH1F("mh1pt_D_e","",400,0,20);
  
  mh2McptVsEta=new TH2F("mh2McptVsEta","",400,0,20,60,-1.5,1.5);
  mh2McptVsPhi=new TH2F("mh2McptVsPhi","",400,0,20,100,-3.2,3.2);
  mh2EtaVsPhi=new TH2F("mh2EtaVsPhi","",60,-1.5,1.5,100,-3.2,3.2);
  mh1NCounts=new TH1F("mh1NCounts","",5,0,5);
  mh1NCounts_after_weight=new TH1F("mh1NCounts_after_weight","",5,0,5);
 
  //
  mh2D0cTao=new TH1F("mh2D0cTao","",2000,0,10);
  mh2B0cTao=new TH1F("mh2B0cTao","",2000,0,10);
  mh2DpluscTao=new TH1F("mh2DpluscTao","",2000,0,10);
  mh2BpluscTao=new TH1F("mh2BpluscTao","",2000,0,10);

  mh2D0barcTao=new TH1F("mh2D0barcTao","",2000,0,10);
  mh2B0barcTao=new TH1F("mh2B0barcTao","",2000,0,10);
  mh2DminuscTao=new TH1F("mh2DminuscTao","",2000,0,10);
  mh2BminuscTao=new TH1F("mh2BminuscTao","",2000,0,10);
  // Ocilation
  mh2OcB0cTao=new TH1F("mh2OcB0cTao","",2000,0,10);
  mh2OcB0barcTao=new TH1F("mh2OcB0barcTao","",2000,0,10);

  mh2D0_electron_delta_CosPhi =new TH2F("mh2D0_electron_delta_CosPhi","",100,0,10,100,-1.2,1.2);
  mh2Dplus_electron_delta_CosPhi =new TH2F("mh2Dplus_electron_delta_CosPhi","",100,0,10,100,-1.2,1.2);
  mh2B0_electron_delta_CosPhi =new TH2F("mh2B0_electron_delta_CosPhi","",100,0,10,100,-1.2,1.2);
  mh2Bplus_electron_delta_CosPhi =new TH2F("mh2Bplus_electron_delta_CosPhi","",100,0,10,100,-1.2,1.2);

  mh2Lcplus_pT_Eta =new TH2F("mh2Lcplus_pT_Eta","",400,0,20,100,-1.5,1.5);
  mh2D0_pT_Eta =new TH2F("mh2D0_pT_Eta","",400,0,20,100,-1.5,1.5);
  mh2Bplus_pT_Eta =new TH2F("mh2Bplus_pT_Eta","",400,0,20,100,-1.5,1.5);


  // mh2B0cTao=new TH1F("mh2B0cTao","",2000,0,10);
  // mh2DpluscTao=new TH1F("mh2DpluscTao","",2000,0,10);
  // mh2BpluscTao=new TH1F("mh2BpluscTao","",2000,0,10);

  mh2D0_electron_delta_CosPhi->Sumw2();
  mh2Dplus_electron_delta_CosPhi ->Sumw2();
  mh2B0_electron_delta_CosPhi ->Sumw2();
  mh2Bplus_electron_delta_CosPhi->Sumw2();

  // call sumw2


  mh2McptVsEta->Sumw2();
  mh2McptVsPhi->Sumw2();
  mh2EtaVsPhi->Sumw2();



  mh2D0cTao->Sumw2(); 
  mh2B0cTao->Sumw2(); 
  mh2DpluscTao->Sumw2(); 
  mh2BpluscTao->Sumw2(); 

  mh2D0barcTao->Sumw2(); 
  mh2B0barcTao->Sumw2(); 
  mh2DminuscTao->Sumw2(); 
  mh2BminuscTao->Sumw2(); 
  // Ocilation
  mh2OcB0cTao->Sumw2(); 
  mh2OcB0barcTao->Sumw2(); 


  mh2Lcplus_pT_Eta->Sumw2(); 
  mh2D0_pT_Eta->Sumw2(); 
  mh2Bplus_pT_Eta->Sumw2(); 

  cout<<" book histogram done !"<<endl;
}
void StEvtGen_Ana::read(TString fileName)
{
  cout<<"!!!!!!!!!!!!!!!!!read"<<fileName<<endl;
  TFile * infile=new TFile(fileName.Data());
  TTree* Tree=(TTree*) infile->Get("Tree");
  StEvtGen_Daughter * Daughter=new StEvtGen_Daughter();
  Daughter->Init(Tree); // 就是专门为上一步产生的tree 配的一个类，专门用于读取tree

  for(Int_t iEvent=0;iEvent<Tree->GetEntries();iEvent++)//
    //for(Int_t iEvent=0;iEvent<1e6;iEvent++)//
    {
      if(iEvent%10000==0)
	cout<<"working on Event  "<<iEvent<<endl;
      Daughter->GetEntry(iEvent);
     
      TLorentzVector vP;
      TLorentzVector vM;
      
      for(Int_t iDaughter=0;iDaughter<Daughter->Ndaughter;iDaughter++)
	{
	  // daughter particle four momentum  
	  TLorentzVector dMom(Daughter->dPx[iDaughter],Daughter->dPy[iDaughter],Daughter->dPz[iDaughter],Daughter->dE[iDaughter]);
	  TLorentzVector drMom(Daughter->dRPx[iDaughter],Daughter->dRPy[iDaughter],Daughter->dRPz[iDaughter],Daughter->dE[iDaughter]); //是通过void StEvtGenDecayMaker::SaveDaughter 拿到这个变量
	  // parent particle four momentum  
	  TLorentzVector mMom(Daughter->mPx[iDaughter],Daughter->mPy[iDaughter],Daughter->mPz[iDaughter],Daughter->mE[iDaughter]);
	  double pathlenth= sqrt(Daughter->dvx[iDaughter]*Daughter->dvx[iDaughter]+Daughter->dvy[iDaughter]*Daughter->dvy[iDaughter]+Daughter->dvz[iDaughter]*Daughter->dvz[iDaughter]);
	  double g_ma=Daughter->mE[iDaughter]/sqrt(Daughter->mE[iDaughter]*Daughter->mE[iDaughter] - (Daughter->mPx[iDaughter]*Daughter->mPx[iDaughter]+Daughter->mPy[iDaughter]*Daughter->mPy[iDaughter]+Daughter->mPz[iDaughter]*Daughter->mPz[iDaughter]));

	  // if(Daughter->mpdg[iDaughter]==511)
	  //   {
	  //     if(Daughter->dpdg[iDaughter]!=-511)
	  // 	mh2B0cTao->Fill(Daughter->dct[iDaughter]/g_ma);
	  //     if(Daughter->dpdg[iDaughter]==-511)
	  // 	mh2OcB0barcTao->Fill(Daughter->dct[iDaughter]/g_ma);
	  //   }
  	  
	  if(abs(Daughter->dpdg[iDaughter])==11&&fabs(dMom.PseudoRapidity())<0.7)
	    {
	      //cout<< " D-"<<endl;
	      double weight_factor=Weight(mMom.Pt(),(int)Daughter->mpdg[iDaughter]);
	      if(abs(Daughter->mpdg[iDaughter])==421)
		{
		  //  cout<<" this is D0"<<endl;

		  // cout<< "electron phi"<< dMom.Phi()<< " D0 Phi"<< mMom.Phi()<<" Cos(Phi_e-parent_e)"<< TMath::Cos(dMom.Phi()-mMom.Phi())<<endl;
		  // mh2D0_electron_delta_CosPhi->Fill(dMom.Pt(),TMath::Cos(dMom.Phi()-mMom.Phi()),weight_factor);

		  mh2D0rDcaVspt[0]->Fill(drMom.Pt(),Daughter->d3DRdca[iDaughter]/10000.,weight_factor);
		  mh2D0rDcaVspt[1]->Fill(drMom.Pt(),Daughter->dRdcaXY[iDaughter]/10000.,weight_factor);
		  mh2D0rDcaVspt[2]->Fill(drMom.Pt(),Daughter->dRdcaZ[iDaughter]/10000.,weight_factor);

		  mh2D0_pT_Eta->Fill(drMom.Pt(),dMom.Eta(),weight_factor);
		}
	      //Dplus
	      if(abs(Daughter->mpdg[iDaughter])==411)
		{
		  // mh2Dplus_electron_delta_CosPhi->Fill(drMom.Pt(),TMath::Cos(dMom.Phi()-mMom.Phi()),weight_factor);

		  mh2DplusrDcaVspt[0]->Fill(drMom.Pt(),Daughter->d3DRdca[iDaughter]/10000.,weight_factor);
		  mh2DplusrDcaVspt[1]->Fill(drMom.Pt(),Daughter->dRdcaXY[iDaughter]/10000.,weight_factor);
		  mh2DplusrDcaVspt[2]->Fill(drMom.Pt(),Daughter->dRdcaZ[iDaughter]/10000.,weight_factor);

		}
	      //Ds_plus
	      if(abs(Daughter->mpdg[iDaughter])==431)
		{
		  mh2DsplusrDcaVspt[0]->Fill(drMom.Pt(),Daughter->d3DRdca[iDaughter]/10000.,weight_factor);
		  mh2DsplusrDcaVspt[1]->Fill(drMom.Pt(),Daughter->dRdcaXY[iDaughter]/10000.,weight_factor);
		  mh2DsplusrDcaVspt[2]->Fill(drMom.Pt(),Daughter->dRdcaZ[iDaughter]/10000.,weight_factor);
		}
	      //Lc_plus
	      if(abs(Daughter->mpdg[iDaughter])==4122)
		{
		  mh2LcrDcaVspt[0]->Fill(drMom.Pt(),Daughter->d3DRdca[iDaughter]/10000.,weight_factor);
		  mh2LcrDcaVspt[1]->Fill(drMom.Pt(),Daughter->dRdcaXY[iDaughter]/10000.,weight_factor);
		  mh2LcrDcaVspt[2]->Fill(drMom.Pt(),Daughter->dRdcaZ[iDaughter]/10000.,weight_factor);
		  mh2Lcplus_pT_Eta->Fill(drMom.Pt(),dMom.Eta(),weight_factor);
		}
	      //B0 
	      if(abs(Daughter->mpdg[iDaughter])==511)
		{
		  // cout<< " this is B0 "<< endl;
		  // cout<< Daughter->dvx[iDaughter]<<endl;
		  // mh2B0_electron_delta_CosPhi->Fill(drMom.Pt(),TMath::Cos(dMom.Phi()-mMom.Phi()),weight_factor);
		  mh2B0rDcaVspt[0]->Fill(drMom.Pt(),Daughter->d3DRdca[iDaughter]/10000.,weight_factor);
		  mh2B0rDcaVspt[1]->Fill(drMom.Pt(),Daughter->dRdcaXY[iDaughter]/10000.,weight_factor);
		  mh2B0rDcaVspt[2]->Fill(drMom.Pt(),Daughter->dRdcaZ[iDaughter]/10000.,weight_factor);
		}
	      //Bplus
	      if(abs(Daughter->mpdg[iDaughter])==521)
		{
		  // mh2Bplus_electron_delta_CosPhi->Fill(drMom.Pt(),TMath::Cos(dMom.Phi()-mMom.Phi()),weight_factor);

		  mh2BplusrDcaVspt[0]->Fill(drMom.Pt(),Daughter->d3DRdca[iDaughter]/10000.,weight_factor);
		  mh2BplusrDcaVspt[1]->Fill(drMom.Pt(),Daughter->dRdcaXY[iDaughter]/10000.,weight_factor);
		  mh2BplusrDcaVspt[2]->Fill(drMom.Pt(),Daughter->dRdcaZ[iDaughter]/10000.,weight_factor);
		  mh2Bplus_pT_Eta->Fill(drMom.Pt(),dMom.Eta(),weight_factor);
		}


	      if(abs(Daughter->mpdg[iDaughter])==111)
		{
		  mh2pi0rDcaVspt[0]->Fill(drMom.Pt(),Daughter->d3DRdca[iDaughter]/10000.,weight_factor); 
		  mh2pi0rDcaVspt[1]->Fill(drMom.Pt(),Daughter->dRdcaXY[iDaughter]/10000.,weight_factor); 
		  mh2pi0rDcaVspt[2]->Fill(drMom.Pt(),Daughter->dRdcaZ[iDaughter]/10000.,weight_factor); 
		}

	      if(abs(Daughter->mpdg[iDaughter])==221)
		{
		  mh2etarDcaVspt[0]->Fill(drMom.Pt(),Daughter->d3DRdca[iDaughter]/10000.,weight_factor); 
		  mh2etarDcaVspt[1]->Fill(drMom.Pt(),Daughter->dRdcaXY[iDaughter]/10000.,weight_factor); 
		  mh2etarDcaVspt[2]->Fill(drMom.Pt(),Daughter->dRdcaZ[iDaughter]/10000.,weight_factor); 
		}

	      if(Daughter->mpdg[iDaughter]==421)
		mh2D0cTao->Fill(Daughter->dct[iDaughter]/g_ma);

	      if(Daughter->mpdg[iDaughter]==-421)
		mh2D0barcTao->Fill(Daughter->dct[iDaughter]/g_ma);

  
	      if(Daughter->mpdg[iDaughter]==411)
		mh2DpluscTao->Fill(Daughter->dct[iDaughter]/g_ma);

	      if(Daughter->mpdg[iDaughter]==-411)
		mh2DminuscTao->Fill(Daughter->dct[iDaughter]/g_ma);


	      if(Daughter->mpdg[iDaughter]==521)
		mh2BpluscTao->Fill(Daughter->dct[iDaughter]/g_ma);

	      if(Daughter->mpdg[iDaughter]==-521)
		mh2BminuscTao->Fill(Daughter->dct[iDaughter]/g_ma);

	    }
	  if(Daughter->mpdg[iDaughter]==-511)
	    {
	      if(Daughter->dpdg[iDaughter]!=511)	
		mh2B0barcTao->Fill(Daughter->dct[iDaughter]/g_ma);
	      if(Daughter->dpdg[iDaughter]==511)
		mh2OcB0cTao->Fill(Daughter->dct[iDaughter]/g_ma);
	    }
	  
	}
      
      
    }
}
void StEvtGen_Ana::WriteHistogram()
{
  cout<<"  write"<<endl;
  // mOutputFile->cd();

  mOutputFile->cd();
  
  mh2Lcplus_pT_Eta->Write(); 
  mh2D0_pT_Eta->Write(); 
  mh2Bplus_pT_Eta->Write(); 


  for(Int_t ihist=0;ihist<3;ihist++){

    if( mh2D0DcaVspt[ihist]->GetEntries()!=0)
      mh2D0DcaVspt[ihist]->Write();

    if( mh2DplusDcaVspt[ihist]->GetEntries()!=0)
      mh2DplusDcaVspt[ihist]->Write();
    
    if( mh2D0rDcaVspt[ihist]->GetEntries()!=0)
      {
	mh2D0rDcaVspt[ihist]->Write();
      }
    if(mh2LcrDcaVspt[ihist]->GetEntries()!=0)
      {
	mh2LcrDcaVspt[ihist]->Write();
      }

    if( mh2DplusrDcaVspt[ihist]->GetEntries()!=0)
      mh2DplusrDcaVspt[ihist]->Write();

    if( mh2DsplusrDcaVspt[ihist]->GetEntries()!=0)
      mh2DsplusrDcaVspt[ihist]->Write();
    
    if( mh2B0DcaVspt[ihist]->GetEntries()!=0)
      mh2B0DcaVspt[ihist]->Write();
    
    if( mh2BplusDcaVspt[ihist]->GetEntries()!=0)
      mh2BplusDcaVspt[ihist]->Write();
    
    if( mh2B0rDcaVspt[ihist]->GetEntries()!=0)
      mh2B0rDcaVspt[ihist]->Write();
    
    if( mh2DplusrDcaVspt[ihist]->GetEntries()!=0)
      mh2BplusrDcaVspt[ihist]->Write();

    if(mh2pi0DcaVspt[ihist]->GetEntries()!=0)
      {
	mh2pi0DcaVspt[ihist]->Write();
      }

    if(mh2pi0rDcaVspt[ihist]->GetEntries()!=0)
      {
	mh2pi0rDcaVspt[ihist]->Write();
      }

    if(mh2etaDcaVspt[ihist]->GetEntries()!=0)
      {
	mh2etaDcaVspt[ihist]->Write();
      }

    if(mh2etarDcaVspt[ihist]->GetEntries()!=0)
      {
	mh2etarDcaVspt[ihist]->Write();
      }


    
  }
  if( mh2D0cTao->GetEntries()!=0)
    mh2D0cTao->Write();
  if( mh2B0cTao->GetEntries()!=0)
    mh2B0cTao->Write();

  if( mh2DpluscTao->GetEntries()!=0)
    mh2DpluscTao->Write();
  if( mh2BpluscTao->GetEntries()!=0)
    mh2BpluscTao->Write();
  //
  if( mh2D0barcTao->GetEntries()!=0)
    mh2D0barcTao->Write();
  if( mh2B0barcTao->GetEntries()!=0)
    mh2B0barcTao->Write();

  if( mh2DminuscTao->GetEntries()!=0)
    mh2DminuscTao->Write();
  if( mh2BminuscTao->GetEntries()!=0)
    mh2BminuscTao->Write();
  if(mh2OcB0cTao->GetEntries()!=0)
    mh2OcB0cTao->Write();
  if(mh2OcB0barcTao->GetEntries()!=0)
    mh2OcB0barcTao->Write();

  if(mh2McptVsEta->GetEntries()!=0)
    mh2McptVsPhi->Write();
  if(mh2EtaVsPhi->GetEntries()!=0)
    mh2EtaVsPhi->Write();  
  if(mh1NCounts->GetEntries()!=0)
    mh1NCounts->Write();
  if(mh1NCounts_after_weight->GetEntries()!=0)
    mh1NCounts_after_weight->Write();

  if(mh2D0_electron_delta_CosPhi->GetEntries()!=0)
    mh2D0_electron_delta_CosPhi->Write();

  if(mh2Dplus_electron_delta_CosPhi->GetEntries()!=0)
    mh2Dplus_electron_delta_CosPhi->Write();

  if(mh2B0_electron_delta_CosPhi->GetEntries()!=0)
    mh2B0_electron_delta_CosPhi->Write();

  if(mh2Bplus_electron_delta_CosPhi->GetEntries()!=0)
    mh2Bplus_electron_delta_CosPhi->Write();


  mOutputFile->Close();

}

Double_t StEvtGen_Ana::Weight(Float_t pt,Int_t pid)
{
  // B_pp200_fonll;
  // D_pp200_fonll;

  Double_t weight=0; 
  // if(abs(pid)==421||abs(pid)==411||abs(pid)==431||abs(pid)==4122)
  //  g weight=  D_pp200_data->Eval(pt);
  //   weight=D_pp200_fonll->Eval(pt);
  //  weight=gr_pp_specatra->Eval(pt);
  //    weight=Graph_from_F_levy_D0_0_80->Eval(pt);


  if(abs(pid)==421&&pt<20)
    weight=Graph_from_F_levy_D0_0_80->Eval(pt);
  
  if(abs(pid)==411&&pt<20)
    weight=Graph_from_F_levy_Dpm_0_80->Eval(pt);
  
  if(abs(pid)==431&&pt<20)
    weight=Graph_from_F_levy_Ds_0_80->Eval(pt);

  if(abs(pid)==4122&&pt<20)
    weight=Graph_from_F_levy_Lc_0_80->Eval(pt);

  

  if(abs(pid)==521||abs(pid)==511)
    weight=B_pp200_fonll->Eval(pt);

  // if(abs(pid)==421)
  //   weight=Graph_from_F_levy_D0_10_40->Eval(pt);
  



  if(abs(pid)==111)
    weight=gr_Weight_pt_pi->Eval(pt);
  if(abs(pid)==221)
    weight=gr_Weight_pt_eta->Eval(pt);
  return weight;
  //      return 1;  
}
