#include "StEvent/StContainers.h"
#include "StEvent/StEventTypes.h"
#include "SystemOfUnits.h"
#include "StEmcADCtoEMaker/StBemcData.h"
#include "StEmcADCtoEMaker/StEmcADCtoEMaker.h"
#include "StEmcUtil/projection/StEmcPosition.h"
#include "StEmcUtil/others/StEmcMath.h"
#include "StEmcUtil/others/emcDetectorName.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/database/StBemcTables.h"
#include "StMessMgr.h"
#include "TTableSorter.h"
#include <math.h>
#include "TArrayI.h"
#include "TArrayF.h"
#include "TMatrix.h"
#include "TCanvas.h"
#include "TTimer.h"
#include "TH1F.h"
#include "TFile.h"
#include "TH2F.h"
#include "TF1.h"
#include "TMemStat.h"
#include "StEmcTowerHitsCluster.h"
#include "StEmcEtaHitsCluster.h"
#include "StEmcPhiHitsCluster.h"
#include "StEmcPointMaker.h"
#include "StTpcDedxPidAlgorithm.h"
#include <vector>

#include "StarCallf77.h"
extern "C" {void type_of_call F77_NAME(gufld,GUFLD)(float *x, float *b);}
#define gufld F77_NAME(gufld,GUFLD)
#define assndx F77_NAME(assndx,ASSNDX)
extern "C" {void type_of_call assndx(Int_t &, Float_t *, Int_t &, Int_t &, Int_t &, Int_t *, Float_t &, Int_t *, Int_t &);}

ClassImp(StEmcPointMaker)

//StEmcGeom* StEmcPointMaker::mGeo[4]={0};
	
StEmcPointMaker::StEmcPointMaker(const char* name):StMaker(name)
{
	mPrint = false;
	mPrintMem=false;
	mPrintDetail = false;
	mPlot = false;
	mFillHisto =false;
	mAnalyzeModule=false;
	mAutoThreshold=false;
	mEmcCol=NULL;
	mEvent=NULL;
	mCanvas=NULL;
	mTimer=NULL;
	mMem=NULL;
	for(int i=0;i<4;i++)
	{
		if(i!=1)
		{
			mGeo[i]=NULL;
			mPar[i]=NULL;
			mHitsInMod[i]=NULL;
			mHitsEnergyInMod[i]=NULL;
			mModHitsMean[i]=NULL;
			mModHitsSigma[i]=NULL;
			mModClusterThr[i]=NULL;
			mModNOKHits[i]=NULL;
			mModNRange[i]=NULL;
			mModChiNDF[i]=NULL;
			mAbnormalMod[i]=NULL;
			mEnergy[i]=NULL;
			mEtaBin[i]=NULL;
			mSub[i]=NULL;
			mUsed[i]=NULL;
			mMean[i]=0;
			mSigma[i]=0;
			mChiNDF[i]=0;
			mNOK[i]=0;
			mNRange[i]=0;
			mBin[i]=0;
			mMax[i]=0;
			mEmcDet[i]=0;
			mEmcClCol[i]=0;
			mEmcCl[i]=0;
			mEmcModule[i]=0;

			//new QA histograms
			mFracOfClusteredHits[i]=NULL;
			mFracOfClusteredHitsByMod[i]=NULL;
			mNClusterPerHit[i]=NULL;
			mNMergedvTotalCl[i]=NULL;
		}
	}
	mTowerCluster=NULL;
	mEtaCluster=NULL;
	mPhiCluster=NULL;
	mTCV=NULL;
	mECV=NULL;
	mPCV=NULL;
	mECV_backup=NULL;
	mPCV_backup=NULL;
	mFitFunc=NULL;
	mEtaPhiClusterFreqByE=NULL;
	mEtaClusterFreqByE=NULL;
	mPhiClusterFreqByE=NULL;
	mPointEta_Phi=NULL;
	mPointEWeightedEta_Phi=NULL;
	/*
	mEtaClusterEta_Phi=NULL;
	mPhiClusterEta_Phi=NULL;
	mTowerClusterEta_Phi=NULL;
	*/
	mPointEnergy=NULL;
	mEtaPhiClusterFreqByMod=NULL;
	mPhiClusterFreqByMod=NULL;
	mEtaClusterFreqByMod=NULL;
	mSigmaEta_Energy=NULL;
	mSigmaPhi_Energy=NULL;
	mNTowerHits_Energy=NULL;
	mNEtaHits_Energy=NULL;
	mNPhiHits_Energy=NULL;
	mEtaTowerECorr=NULL;
	mPhiTowerECorr=NULL;
	mNEtaStripsBelow=NULL;
	mNPhiStripsBelow=NULL;
	mEtaClCrossPatchFreq=NULL;
	mPhiClCrossPatchFreq=NULL;
	mAssociatedTrack=NULL;
	mShareFlavor=0;
	mMergeFlavor=0;
	mClosePairMass=0;

	//new QA histograms
	mNClustersBelow=NULL;
	mNDiffPairvNPair=0;	
}

StEmcPointMaker::~StEmcPointMaker()
{
	for(int i=0;i<4;i++)
	{
		if(i!=1)
		{
			//if(mGeo[i]) delete mGeo[i];
			if(mPar[i]) delete mPar[i];
			if(mHitsInMod[i]) delete mHitsInMod[i];
			if(mHitsEnergyInMod[i])	delete mHitsEnergyInMod[i];
			if(mModHitsSigma[i]) delete mModHitsSigma[i];
			if(mModHitsMean[i]) delete mModHitsMean[i];
			if(mModNOKHits[i]) delete mModNOKHits[i];
			if(mModNRange[i]) delete mModNRange[i];
			if(mModChiNDF[i]) delete mModChiNDF[i];
			if(mAbnormalMod[i]) delete mAbnormalMod[i];
			if(mModClusterThr[i]) delete mModClusterThr[i];
			if(mEnergy[i]) delete mEnergy[i];
			if(mEtaBin[i]) delete mEtaBin[i];
			if(mUsed[i]) delete mUsed[i];
			if(mSub[i]) delete mSub[i];

			if(mFracOfClusteredHits[i]) delete mFracOfClusteredHits[i];
			if(mFracOfClusteredHitsByMod[i]) delete mFracOfClusteredHitsByMod[i];
			if(mNClusterPerHit[i]) delete mNClusterPerHit[i];
			if(mNMergedvTotalCl[i]) delete mNMergedvTotalCl[i];
		}
	}
	//if(mEmcCol) delete mEmcCol;
	if(mECV) delete mECV;
	if(mPCV) delete mPCV;
	if(mTCV) delete mTCV;
	if(mTowerCluster) delete mTowerCluster;
	if(mEtaCluster) delete mEtaCluster;
	if(mPhiCluster) delete mPhiCluster;
	if(mMem) delete mMem;
	if(mECV_backup) delete mECV_backup;
	if(mPCV_backup) delete mPCV_backup;
	if(mEtaPhiClusterFreqByE) delete mEtaPhiClusterFreqByE;
	if(mEtaClusterFreqByE) delete mEtaClusterFreqByE;
	if(mPhiClusterFreqByE) delete mPhiClusterFreqByE;
	if(mPointEta_Phi) delete mPointEta_Phi;
	if(mPointEWeightedEta_Phi) delete mPointEWeightedEta_Phi;
	/*
	if(mEtaClusterEta_Phi) delete mEtaClusterEta_Phi;
	if(mPhiClusterEta_Phi) delete mPhiClusterEta_Phi;
	if(mTowerClusterEta_Phi) delete mTowerClusterEta_Phi;
	*/
	if(mEtaPhiClusterFreqByMod) delete mEtaPhiClusterFreqByMod;
	if(mPhiClusterFreqByMod) delete mPhiClusterFreqByMod;
	if(mEtaClusterFreqByMod) delete mEtaClusterFreqByMod;
	if(mSigmaEta_Energy) delete mSigmaEta_Energy;
	if(mSigmaPhi_Energy) delete mSigmaPhi_Energy;
	if(mNTowerHits_Energy) delete mNTowerHits_Energy;
	if(mNEtaHits_Energy) delete mNEtaHits_Energy;
	if(mNPhiHits_Energy) delete mNPhiHits_Energy;
	if(mEtaTowerECorr) delete mEtaTowerECorr;
	if(mPhiTowerECorr) delete mPhiTowerECorr;
	if(mEtaPhiECorr) delete mEtaPhiECorr;
	if(mNEtaStripsBelow) delete mNEtaStripsBelow;
	if(mNPhiStripsBelow) delete mNPhiStripsBelow;
	if(mNEtaClustersBelow) delete mNEtaClustersBelow;
	if(mNPhiClustersBelow) delete mNPhiClustersBelow;
	if(mEtaClCrossPatchFreq) delete mEtaClCrossPatchFreq;
	if(mPhiClCrossPatchFreq) delete mPhiClCrossPatchFreq;
	if(mAssociatedTrack) delete mAssociatedTrack;
	if(mPointEnergy) delete mPointEnergy;
	if(mClosePairMass) delete mClosePairMass;

	if(mCanvas) delete mCanvas;
	if(mTimer) delete mTimer;
	if(mFitFunc) delete mFitFunc;

	//new QA histograms
	if(mNClustersBelow) delete mNClustersBelow;
	if(mNDiffPairvNPair) delete mNDiffPairvNPair;
}

void StEmcPointMaker::setParameters(emcPtMakerPar_st* par,int det)
{
	if(!par) return;
	cout<<"StEmcPointMaker::setParameters(par,det)\n";
	mPar[det]->seedlow=par->seedlow;
	mPar[det]->seedhigh=par->seedhigh;
	mPar[det]->addlow=par->addlow;
	mPar[det]->addhigh=par->addhigh;
	mPar[det]->total=par->total;
}

void StEmcPointMaker::setParameters(emcPtMakerPar_st** par)		//called in macro after Init, to overwrite default parameters
{
	if(!par) return;
	for(int i=0;i<4;i++)
		if(i!=1)
			setParameters(par[i],i);
}

int StEmcPointMaker::Init()
{
	cout<<"StEmcPointMaker::Init()"<<endl;
	//these parameters should be tuned
	float seedlow[4]	=	{	0.1,	0.1,	0.05,	0.05	};
	float addlow[4]		=	{	0.05,	0.05,	0.04,	0.04	};
	float seedhigh[4]	=	{	0.4,	0.1,	0.1,	0.1	};
	float addhigh[4]	=	{	0.05,	0.05,	0.05,	0.05	};
	float total[4]		=	{	0.7,	0.05,	0.1,	0.1	};
	mShareFlavor=0;
	mMergeFlavor=0;
	if(mPrintMem) mMem = new TMemStat("makermem");
	mTCV = new vector<StEmcTowerHitsCluster*>;
	mECV = new vector<StEmcEtaHitsCluster*>;
	mPCV = new vector<StEmcPhiHitsCluster*>;
	mECV_backup = new vector<StEmcEtaHitsCluster*>;
	mPCV_backup = new vector<StEmcPhiHitsCluster*>;
	for(int i=0;i<4;i++)
	{
		if(i!=1)
		{
			mPar[i]=new emcPtMakerPar_st;
			mGeo[i]=StEmcGeom::getEmcGeom(detname[i].Data());
			mPar[i]->seedlow=seedlow[i];
			mPar[i]->seedhigh=seedhigh[i];
			mPar[i]->addlow=addlow[i];
			mPar[i]->addhigh=addhigh[i];
			mPar[i]->total=total[i];
			mEnergy[i]=new TArrayF();
			mEtaBin[i]=new TArrayI();
			mUsed[i]=new TArrayI();
			mSub[i]=new TArrayI();

			int netabin=mGeo[i]->NEta();
			int nsub=mGeo[i]->NSub();
			if(mPlot)
			{
				TArrayF EtaB(netabin+1,mGeo[i]->EtaB());
				TArrayF PhiB(nsub+1,mGeo[i]->PhiB());
				TString name;
				name=detname[i]+"HitsInMod";
				mHitsInMod[i]=new TH2F(name,name,netabin,EtaB.GetArray(),nsub,PhiB.GetArray());
			}
			TString name;
			name=detname[i]+"HitsEnergyInMod";
			int nbin;
			if(i==0) nbin=50;
			else nbin=80;
			mHitsEnergyInMod[i]=new TH1F(name,name,nbin,-0.2,0.2);

			if(mFillHisto)
			{
				TString name;
				name=detname[i]+"ModSigma";
				mModHitsSigma[i]=new TH2F(name,name,120, 0.5, 120.5, 200, 0, 0.1);
				//mModHitsSigma[i]->SetBit(TH1::kCanRebin);
				name=detname[i]+"ModMean";
				mModHitsMean[i]=new TH2F(name,name, 120, 0.5, 120.5, 1000,-0.5,0.5);
				//mModHitsMean[i]->SetBit(TH1::kCanRebin);
				name=detname[i]+"ModThrHld";
				mModClusterThr[i]=new TH2F(name,name, 120, 0.5, 120.5, 1000,-0.2,0.8);
				name=detname[i]+"NOKHits";
				mModNOKHits[i] = new TH2F(name,name,120,0.5,120.5,150,0.5,150.5);
				name=detname[i]+"NRange";
				mModNRange[i] = new TH2F(name,name,120,0.5,120.5,1000,0,200);
				name=detname[i]+"ChiNDF";
				mModChiNDF[i] = new TH1F(name,name,100,0,5);
				name=detname[i]+"AbnormalMod";
				mAbnormalMod[i]=new TH1F(name,name,120,0.5,120.5);
				name=detname[i]+"FracOfClusteredHits";
				mFracOfClusteredHits[i] = new TH1F(name,name,40,0,1);
				name=detname[i]+"FracOfClusteredHitsByMod";
				mFracOfClusteredHitsByMod[i] = new TH2F(name,name,120,0.5,120.5,40,0,1);
				name=detname[i]+"NClusterPerHit";
				mNClusterPerHit[i] = new TH1F(name,name,5,-0.5,4.5);
				name=detname[i]+"NMergedvTotalCl";
				mNMergedvTotalCl[i] = new TH2F(name,name,10,0.5,10.5,10,0.5,10.5);
			}
		}
	}
	if(mFillHisto)
	{
		Int_t nEta=mGeo[2]->NEta();
		Int_t nSub=mGeo[3]->NSub();

		TArrayF EtaB(nEta+1,mGeo[2]->EtaB());	//need to double, to account for east side - pk 3/12/07
		TArrayF PhiB(nSub+1,mGeo[3]->PhiB());

		TArrayF EtaBins(2*(nEta+1));

		for(Int_t e=0;e<(nEta+1);e++){
			EtaBins[nEta+1+e] = EtaB[e];
			EtaBins[nEta-e] = -EtaB[e];
		}

		TArrayF PhiBins1(60*(nSub+1));
		TArrayF PhiBins(60*(nSub+1));
		Float_t center;
		Int_t j=0;
		for(Int_t m=1;m<=60;m++)
		{
			mGeo[3]->getPhiModule(m,center);
			for(Int_t s=1;s<=nSub+1;s++)
			{
				PhiBins1[j]=center-PhiB[s-1];
				j++;
			}
		}
		Bool_t again=kTRUE;
		j=0;
		do {						//order array by increasing phi
			again=kFALSE;
			Float_t phitmp=6.4;
			Int_t ktmp=-1;
			for(Int_t k=0;k<60*(nSub+1);k++)
			{
				if(PhiBins1[k]<phitmp)
				{
					phitmp=PhiBins1[k];
					ktmp=k;
				}
			}
			if(ktmp!=-1)				
			{
				PhiBins[j]=phitmp;
				again=kTRUE;
				PhiBins1[ktmp]=999;
				j++;
			}
		} while(again);
		mPointEta_Phi=new TH2F("PointEta_Phi","Eta-Phi distribution of EMC points;Eta;Phi",2*nEta+1,EtaBins.GetArray(),60*(nSub+1)-1,PhiBins.GetArray());
		mPointEWeightedEta_Phi=new TH2F("PointEWeightedEta_Phi","Eta-Phi distribution of EMC points;Eta;Phi",2*nEta+1,EtaBins.GetArray(),60*(nSub+1)-1,PhiBins.GetArray());
		/*
		mEtaClusterEta_Phi = new TH2F("EtaClusterEta_Phi","Eta-Phi distribution of Eta Clusters", 2*nEta+1, EtaBins.GetArray(), 60, -TMath::Pi(), TMath::Pi());
		mPhiClusterEta_Phi = new TH2F("PhiClusterEta_Phi","Eta-Phi distribution of Phi Clusters", 10, 0, 1, 60*(nSub+1)-1, PhiBins.GetArray());
		nTowerClusterEta_Phi = new TH2F("TowerClusterEta_Phi", "Eta-Phi distribution of Tower Clusters", 20, 0, 1, 60, -TMath::Pi(), TMath::Pi());
		*/
		mEtaPhiClusterFreqByE=new TH1F("EtaPhiClusterFreqByE","# of points with both Eta & Phi clusters;PointE (GeV)",100,0.1,10.1);
		mEtaClusterFreqByE=new TH1F("EtaClusterFreqByE","# of points with Eta Cluster;PointE (GeV)",100,0.1,10.1);
		mPhiClusterFreqByE=new TH1F("PhiClusterFreqByE","# of points with Phi Cluster;PointE (GeV)",100,0.1,10.1);
		mEtaPhiClusterFreqByMod=new TH1F("EtaPhiClusterFreqByMod","# of points with both Eta & Phi clusters;Module",120,0.5,120.5);
		mEtaClusterFreqByMod=new TH1F("EtaClusterFreqByMod","# of points with Eta cluster;Module",120,0.5,120.5);
		mPhiClusterFreqByMod=new TH1F("PhiClusterFreqByMod","# of points with Phi cluster;Module",120,0.5,120.5);
		mPointEnergy=new TH1F("PointEnergy","Energy distribution of EMC points;PointE (GeV)",1000,0,10);
		mSigmaEta_Energy=new TH2F("SigmaEta_Energy","Sigma Eta V.S. Energy;PointE (GeV);SigmaEta",100,0.1,10.1,100,0,0.2);
		mSigmaPhi_Energy=new TH2F("SigmaPhi_Energy","Sigma Phi V.S. Energy;PointE (GeV);SigmaPhi",100,0.1,10.1,100,0,0.2);
		mNTowerHits_Energy=new TH2F("NTowerHits_Energy","# of Hits in Tower Cluster V.S. Energy;PointE (GeV);Tower Hits",1000,0.1,10.1,10,0,10);
		mNEtaHits_Energy=new TH2F("NEtaHits_Energy","# of Hits in Eta Cluster V.S. Energy;PointE (GeV);Eta Hits",1000,0.1,10.1,30,0,30);
		mNPhiHits_Energy=new TH2F("NPhiHits_Energy","# of Hits in Phi Cluster V.S. Energy;PointE (GeV);Phi Hits",1000,0.1,10.1,30,0,30);
		mEtaTowerECorr=new TH2F("EtaTowerECorr","Eta cluster energy V.S. tower cluster Energy;EtaE;TowerE",100,0.1,10.1,100,0.1,10.1);
		mPhiTowerECorr=new TH2F("PhiTowerECorr","Phi cluster energy V.S. tower cluster Energy;PhiE;TowerE",100,0.1,10.1,100,0.1,10.1);
		mEtaPhiECorr=new TH2F("EtaPhiECorr","Eta cluster energy V.S. Phi cluster Energy;EtaE;PhiE",100,0.1,10.1,100,0.1,10.1);
		mNEtaStripsBelow=new TH1F("NEtaStripsBelow","# of Eta strips below a tower cluster",150,0,150);
		mNPhiStripsBelow=new TH1F("NPhiStripsBelow","# of Phi strips below a tower cluster",150,0,150);
		mNEtaClustersBelow=new TH1F("NEtaClustersBelow","# of Eta clusters below a tower cluster",10,-0.5,9.5);
		mNPhiClustersBelow=new TH1F("NPhiClustersBelow","# of Phi clusters below a tower cluster",10,-0.5,9.5);
		mAssociatedTrack=new TH1F("AssociatedTrack","tracks associated with EMC point",10,0,1);
		mAssociatedTrack->SetStats(0);
		mAssociatedTrack->SetBit(TH1::kCanRebin);
		mAssociatedTrack->LabelsOption("a","X");
		mClosePairMass=new TH1F("ClosePairMass1","Invariant mass of two EMC points under the same tower cluster",1000,0,1);

		//new QA histograms
		mNClustersBelow = new TH2F("NClustersBelow","# of Eta & Phi clusters below a tower cluster;NEtaCl;NPhiCl",10,-0.5,9.5,10,-0.5,9.5);
		mNDiffPairvNPair = new TH2F("NDiffPairvNPair","# of different eta-phi cluster pairs v total pairs;different pairs;total pairs",10,-0.5,9.5,10,-0.5,9.5);
	}
	mFitFunc=new TF1("GausFit","gaus(0)");
	if(mPlot)
	{
		mTimer=new TTimer("gSystem->ProcessEvents();",50,false);
		mCanvas=new TCanvas("module hits");
		mTimer->TurnOn();
	}
	cout<<"StEmcPointMaker::Init() over"<<endl;
	return StMaker::Init();
}

bool StEmcPointMaker::saveQAHistograms(const char* file)
{
	TFile f(file,"RECREATE");
	f.cd();
	for(int det=0;det<4;det++)
	{
		if(det!=1)
		{
			if(mModHitsSigma[det])
				mModHitsSigma[det]->Write();
			if(mModHitsMean[det])
				mModHitsMean[det]->Write();
			if(mModClusterThr[det])
				mModClusterThr[det]->Write();
			if(mModNOKHits[det]) 
				mModNOKHits[det]->Write();
			if(mModNRange[det])
				mModNRange[det]->Write();
			if(mModChiNDF[det])
				mModChiNDF[det]->Write();
			if(mAbnormalMod[det])
				mAbnormalMod[det]->Write();
			if(mFracOfClusteredHits[det]) 
				mFracOfClusteredHits[det]->Write();
			if(mFracOfClusteredHitsByMod[det]) 
				mFracOfClusteredHitsByMod[det]->Write();
			if(mNClusterPerHit[det])
				mNClusterPerHit[det]->Write();
			if(mNMergedvTotalCl[det])
				mNMergedvTotalCl[det]->Write();
		}
	}
	if(mPointEnergy) mPointEnergy->Write();
	if(mEtaPhiClusterFreqByE) mEtaPhiClusterFreqByE->Write();
	if(mEtaClusterFreqByE) mEtaClusterFreqByE->Write();
	if(mPhiClusterFreqByE) mPhiClusterFreqByE->Write();
	if(mPointEta_Phi) mPointEta_Phi->Write();
	if(mPointEWeightedEta_Phi) mPointEWeightedEta_Phi->Write();
	/*
	if(mEtaClusterEta_Phi) mEtaClusterEta_Phi->Write();
	if(mPhiClusterEta_Phi) mPhiClusterEta_Phi->Write();
	if(mTowerClusterEta_Phi) mTowerClusterEta_Phi->Write();
	*/
	if(mEtaPhiClusterFreqByMod) mEtaPhiClusterFreqByMod->Write();
	if(mPhiClusterFreqByMod) mPhiClusterFreqByMod->Write();
	if(mEtaClusterFreqByMod) mEtaClusterFreqByMod->Write();
	if(mSigmaEta_Energy) mSigmaEta_Energy->Write();
	if(mSigmaPhi_Energy) mSigmaPhi_Energy->Write();
	if(mNTowerHits_Energy) mNTowerHits_Energy->Write();
	if(mNEtaHits_Energy) mNEtaHits_Energy->Write();
	if(mNPhiHits_Energy) mNPhiHits_Energy->Write();
	if(mEtaTowerECorr) mEtaTowerECorr->Write();
	if(mPhiTowerECorr) mPhiTowerECorr->Write();
	if(mEtaPhiECorr) mEtaPhiECorr->Write();
	if(mNEtaStripsBelow) mNEtaStripsBelow->Write();
	if(mNPhiStripsBelow) mNPhiStripsBelow->Write();
	if(mNEtaClustersBelow) mNEtaClustersBelow->Write();
	if(mNPhiClustersBelow) mNPhiClustersBelow->Write();
	if(mEtaClCrossPatchFreq) mEtaClCrossPatchFreq->Write();
	if(mPhiClCrossPatchFreq) mPhiClCrossPatchFreq->Write();
	if(mAssociatedTrack) 
	{
		mAssociatedTrack->LabelsDeflate("X");
		mAssociatedTrack->Write();
	}
	if(mClosePairMass) mClosePairMass->Write();
	if(mNClustersBelow) mNClustersBelow->Write();
	if(mNDiffPairvNPair) mNDiffPairvNPair->Write();
	f.Close();
	return true;
}

int StEmcPointMaker::Make()
{
	cout<<"===== StEmcPointMaker::Make() =====\n";
	if(mTally) mTally->Fill("StEmcPointMaker: Begin", 1);
	if(mPrintMem && mMem) mMem->PrintMem("The beginning of the maker\t\t");
	if(mPrintDetail)
	{
		cout<<"---------------StEmcPointMaker::Make()-----------------"<<endl;
		for(int i=0;i<4;i++)
		{
			if(i!=1)
				cout<<detname[i]<<" seed energy: "<<mPar[i]->seedlow<<"(low), "<<mPar[i]->seedhigh<<"(high), "<<"addon energy: "<<mPar[i]->addlow<<"(low), "<<mPar[i]->addhigh<<"(high)"<<endl;
		}
	}
//	cout<<"\t\tgetting StEvent...\n";
	mEvent=(StEvent*)GetInputDS("StEvent");

	mAdc2E = dynamic_cast<StEmcADCtoEMaker*>( GetMaker("ADC2E") );			//need to be created in macro, ahead of StEmcPointMaker
											//wipes clusters, points. keeps hits
	//mAdc2E=(StEmcADCtoEMaker*)GetInputDS("ADC2E");
	
	mBemcData = mAdc2E->getBemcData();
	mTables = mBemcData->getTables();

//	cout<<"\t\tmEvent = "<<mEvent<<endl;
	if(mEvent)
	{
		mEmcCol=mEvent->emcCollection();
		if(mEmcCol)
		{
			bool skip = false;
			for(int det=0;det<4;det++)
			{
				if(det!=1)
				{
					StDetectorId id=static_cast<StDetectorId>(det+kBarrelEmcTowerId);
					mEmcDet[det]=mEmcCol->detector(id);
					if(!mEmcDet[det])
					{
						if(mPrint) cout<<"No "<<detname[det]<<" detector!!!"<<endl;
						char entry[100];
						sprintf(entry,"StEmcPointMaker: No %s", detname[det].Data());                                              
						if(mTally) mTally->Fill(entry, 1);
					//	return kStSkip;
						skip = true;
					}
				}
			}
			if(skip) return kStSkip;
		}
		else
		{
			if(mPrint) cout<<"No StEmcCollection!!!"<<endm;
			if(mTally) mTally->Fill("StEmcPointMaker: No StEmcCollection", 1);
			return kStSkip;
		}
	}
	else
	{
		if(mPrint) cout<<"No StEvent!!!"<<endm;
		if(mTally) mTally->Fill("StEmcPointMaker: No StEvent", 1);
		return kStSkip;
	}
	/*
	if(!mEvent->primaryVertex())
	{
		if(mPrint) cout<<"No primary vertex!!!"<<endl;
		if(mTally) mTally->Fill("StEmcPointMaker: No primary vertex", 1);
		return kStSkip;
	}*/
	if(!clearEmc())
	{
		if(mPrint) cout<<"No Emc Collection or detector"<<endl;
		if(mTally) mTally->Fill("StEmcPointMaker: No StEmcCollection or detector", 1);
		return kStSkip;
	}
	if(mPrintMem && mMem) mMem->PrintMem("Before cluster by module\t\t");
	//for(int mod=1;mod<=120;mod++)
	for(int mod=1;mod<=120;mod++)
	{
		if(mPrintMem && mMem) mMem->PrintMem("The beginning of a module\t\t");
		if(mPrintDetail)
			cout<<endl<<endl<<"Analyzing module "<<mod<<endl;
		bool really_plot=false;


		if(!mEmcCol->detector(StDetectorId(kBarrelEmcTowerId))->module(mod)) 
		{
			if(mPrint) cout<<"No tower module "<<mod<<endl;
			continue;
		}
		mEmcModule[0]=mEmcCol->detector(StDetectorId(kBarrelEmcTowerId))->module(mod);
		StSPtrVecEmcRawHit& towerhits=mEmcModule[0]->hits();
		if(towerhits.size()==0) continue;
		if(mAnalyzeModule)
		{
			if(!analyzeTowerHits(towerhits)) 
			{
				if(mPrint) cout<<"No tower hits in module "<<mod<<endl;
				continue;
			}
			if(mNRange[0]<20)// || mean>0.1 || sigma>0.1 || chindf>3)
			{
				if(mPrintDetail) cout<<"Got a strange tower module: module="<<mod<<", nrange="<<mNRange[0]<<", mean="<<mMean[0]<<", sigma="<<mSigma[0]<<", chindf="<<mChiNDF[0]<<endl;
				//if(mPlot) really_plot=true;
				if(mFillHisto && mAbnormalMod[0]) mAbnormalMod[0]->Fill(mod);
			}
		}
		maskTowers(towerhits);
		mTCV->clear();
		if(mAutoThreshold) {
			if(!clusterTowers(towerhits, mMean[0]+3*mSigma[0], mMean[0]+2*mSigma[0])) continue;
		}
		else { 
			if(!clusterTowers(towerhits, mPar[0]->seedlow, mPar[0]->addlow)) continue;
		}
		if(mTCV->size()==0) continue;
		//mergeTowerClusters();
		/*
		   if(mPrintDetail)
		   {
		   for(unsigned int tci=0;tci<mTCV->size();tci++)
		   {
		   StEmcTowerHitsCluster* mTowerCluster=mTCV->at(tci);
		   if(mTowerCluster->energy()>5)
		   really_plot=true;
		   }
		   }
		 */
		if(mPrintDetail) cout<<"mTCV->size() = "<<mTCV->size()<<endl;
		if(mTCV->size()>0 && mPlot)
			really_plot=true;
		if(mPrintMem && mMem) mMem->PrintMem("The end of TC in a module\t\t");




		
		if(mEmcCol->detector(StDetectorId(kBarrelEmcTowerId+2))->module(mod))
		{
			mEmcModule[2]=mEmcCol->detector(StDetectorId(kBarrelEmcTowerId+2))->module(mod);
			StSPtrVecEmcRawHit& etahits=mEmcModule[2]->hits();
			//if(etahits.size()==0) continue;
			if(mAnalyzeModule)
			{
				if(!analyzeSMDHits(2, etahits)) 
					if(mPrint) cout<<"No hits in "<<detname[2]<<" module "<<mod<<endl;
				if(fabs(mMean[2])>0.036 || fabs(mSigma[2]-0.0175)>0.0072)// || mNRange[2]<=120)// || chindf>3)
				{
					if(mPrintDetail)
						cout<<"something wrong with the eta plane of module "<<mod<<", mean="<<mMean[2]<<" sigma="<<mSigma[2]<<", nrange="<<mNRange[2]<<endl;
					//if(mPlot) really_plot=true;
					if(mFillHisto && mAbnormalMod[2]) mAbnormalMod[2]->Fill(mod);
				}
			}
		}
		else
		{
			if(mPrint) 
				cout<<"No module "<<mod<<" in "<<detname[2]<<endl;
			mEmcModule[2]=NULL;
		}





		if(mEmcCol->detector(StDetectorId(kBarrelEmcTowerId+3))->module(mod))
		{
			mEmcModule[3]=mEmcCol->detector(StDetectorId(kBarrelEmcTowerId+3))->module(mod);
			StSPtrVecEmcRawHit& phihits=mEmcModule[3]->hits();
			//if(phihits.size()==0) continue;
			if(mAnalyzeModule)	
			{
				if(!analyzeSMDHits(3, phihits))
					if(mPrint) cout<<"No hits in "<<detname[3]<<" module "<<mod<<endl;
				if(fabs(mMean[3])>0.036 || fabs(mSigma[3]-0.0162)>0.006)// || mNRange[3]<=120)// || chindf>3)
				{
					if(mPrintDetail)
						cout<<"something wrong with the phi plane of module "<<mod<<", mean="<<mMean[3]<<" sigma="<<mSigma[3]<<", nrange="<<mNRange[3]<<", chindf="<<mChiNDF[3]<<endl;
					//if(mPlot) really_plot=true;
					if(mFillHisto && mAbnormalMod[3]) mAbnormalMod[3]->Fill(mod);
				}
			}
		}
		else
		{
			if(mPrint)
				cout<<"No module "<<mod<<" in "<<detname[3]<<endl;
			mEmcModule[3]=NULL;
		}
			
		//SMD clustering done per tower cluster		
		for(unsigned int tci=0;tci<mTCV->size();tci++)
		{
			if(mPrintMem && mMem) mMem->PrintMem("The beginning of SMDC in a module\t");
			mTowerCluster=mTCV->at(tci);
			/*
			   if(mTowerCluster->energy()>0.4 && mPlot)
				really_plot=true;
				*/
			if(mPrintDetail) 
			{
				cout<<endl<<endl<<"Cluster Eta and Phi strips below tower cluster #"<<tci+1<<": ";
				mTowerCluster->print();
				cout<<endl;
			}
			if(mEmcModule[2])
				if(!maskEtaStrips(mEmcModule[2]->hits())) continue; //no tower cluster
			mECV->clear();
			if(mAutoThreshold)
			{
				if(mEmcModule[2])
					clusterEtaStrips(mEmcModule[2]->hits(), mMean[2]+3*mSigma[2], mMean[2]+2*mSigma[2]);
				for(unsigned int eci=0;eci<mECV->size();eci++)
				{
					mECV->at(eci)->mSeedNSigma=3;
					mECV->at(eci)->mAddonNSigma=2;
				}
			}
			else		//static parameters
			{
				if(mEmcModule[2])
					clusterEtaStrips(mEmcModule[2]->hits(), mPar[2]->seedhigh, mPar[2]->addhigh);
				for(unsigned int eci=0;eci<mECV->size();eci++)
				{
					mECV->at(eci)->mSeedNSigma=33;
					mECV->at(eci)->mAddonNSigma=22;
				}
			}

			bool multi=false;		//for multiple eta divisions in SMDp
			if(mEmcModule[3])
				if(!maskPhiStrips(mEmcModule[3]->hits(), multi)) continue; //no tower cluster
			mPCV->clear();
			if(mAutoThreshold)
			{
				if(mEmcModule[3])
					clusterPhiStrips(mEmcModule[3]->hits(), mMean[3]+3*mSigma[3], mMean[3]+2*mSigma[3], multi);
				for(unsigned int pci=0;pci<mPCV->size();pci++)
				{
					mPCV->at(pci)->mSeedNSigma=3;
					mPCV->at(pci)->mAddonNSigma=2;
				}
			}
			else
			{
				if(mEmcModule[3])
					clusterPhiStrips(mEmcModule[3]->hits(), mPar[3]->seedhigh, mPar[3]->addhigh, multi);
				for(unsigned int pci=0;pci<mPCV->size();pci++)
				{
					mPCV->at(pci)->mSeedNSigma=33;
					mPCV->at(pci)->mAddonNSigma=22;
				}
			}
				

			if(mFillHisto)
			{
				if(mECV->size()>0 && mPCV->size()>0) 
				{
					if(mEtaPhiClusterFreqByE)
						mEtaPhiClusterFreqByE->Fill(mTowerCluster->energy());
					if(mEtaPhiClusterFreqByMod && mTowerCluster->energy()>2)
						mEtaPhiClusterFreqByMod->Fill(mod);
				}
				if(mPCV->size()>0)
				{
					if(mPhiClusterFreqByE)
						mPhiClusterFreqByE->Fill(mTowerCluster->energy());
					if(mPhiClusterFreqByMod && mTowerCluster->energy()>2)
						mPhiClusterFreqByMod->Fill(mod);
				}
				if(mECV->size()>0)
				{
					if(mEtaClusterFreqByE)
						mEtaClusterFreqByE->Fill(mTowerCluster->energy());
					if(mEtaClusterFreqByMod && mTowerCluster->energy()>2)
						mEtaClusterFreqByMod->Fill(mod);
				}
			}

			//if 1 plane has no cluster while the other does, lower clustering thresholds
			if(mECV->size()==0)
			{
				if(mPCV->size()>0)
				{
					if(mAutoThreshold)
					{
						if(mEmcModule[2])
							clusterEtaStrips(mEmcModule[2]->hits(), mMean[2]+2*mSigma[2], mMean[2]+1*mSigma[2]);
						for(unsigned int eci=0;eci<mECV->size();eci++)
						{
							mECV->at(eci)->mSeedNSigma=2;
							mECV->at(eci)->mAddonNSigma=1;
						}
					}
					else
					{
						if(mEmcModule[2])
							clusterEtaStrips(mEmcModule[2]->hits(), mPar[2]->seedlow, mPar[2]->addlow);	
						for(unsigned int eci=0;eci<mECV->size();eci++)
						{
							mECV->at(eci)->mSeedNSigma=22;
							mECV->at(eci)->mAddonNSigma=11;
						}
					}
				}
			}

			if(mPCV->size()==0)
			{
				if(mECV->size()>0)
				{
					if(mAutoThreshold)
					{
						if(mEmcModule[3])
							clusterPhiStrips(mEmcModule[3]->hits(), mMean[3]+2*mSigma[3], mMean[3]+1*mSigma[3], multi);
						for(unsigned int pci=0;pci<mPCV->size();pci++)
						{
							mPCV->at(pci)->mSeedNSigma=2;
							mPCV->at(pci)->mAddonNSigma=1;
						}
					}
					else
					{
						if(mEmcModule[3])
							clusterPhiStrips(mEmcModule[3]->hits(),mPar[3]->seedlow, mPar[3]->addlow, multi);
						for(unsigned int pci=0;pci<mPCV->size();pci++)
						{
							mPCV->at(pci)->mSeedNSigma=22;
							mPCV->at(pci)->mAddonNSigma=11;
						}
					}
				}
			}


			/*
			if(mECV->size()==0)
			{
				if(mPCV->size()>0)
				{
					mergePhiClusters(3,1);
					clusterEtaStrips(etahits, 999, 999);
				}
			}

			if(mPCV->size()==0)
			{
				if(mECV->size()>0)
				{
					mergeEtaClusters(3,1);
					clusterPhiStrips(phihits, 999, 999, multi);
				}
			}
			*/
			/*
			backupSMDClusters();

			for(int k=5;k<=6;k++)
			{
				//for(int j=0;j<=1;j++)
				for(int j=2;j<=3;j++)
				{
					for(int i=j;i<=k-2;i++)
					{
						for(int m=0;m<=1;m++)
						{
							for(int s=0;s<=1;s++)
							{
								if(mPrint) cout<<"In flavor "<<k<<i<<j<<m<<s<<endl;
								recoverSMDClusters();
								mMaxSMDCombinedNHits=k;
								mMaxSMDSeedDist=i;
								mMaxSMDBoundaryDist=j;
								mMergeFlavor=m;
								mShareFlavor=s;
								mergeSMDClusters();
								makePoints();
							}
						}
					}
				}
			}
			*/
			if(mECV->size()!=0 || mPCV->size()!=0)
			{
				backupSMDClusters();
				recoverSMDClusters();		//no point that I see in this
				mMaxSMDCombinedNHits=6;
				mMaxSMDSeedDist=4;
				mMaxSMDBoundaryDist=1;
				mMergeFlavor=0;  //do not favor 1:2:2 situation
				mShareFlavor=0;  //do not split energy simply by 2, instead using the SMD clusters' energy ratio
				mergeSMDClusters();
			}
			makePoints();
			for(unsigned int eci=0;eci<mECV->size();eci++)
				delete mECV->at(eci);
			mECV->clear();
			for(unsigned int pci=0;pci<mPCV->size();pci++)
				delete mPCV->at(pci);
			mPCV->clear();
			for(unsigned int eci=0;eci<mECV_backup->size();eci++)
				delete mECV_backup->at(eci);
			mECV_backup->clear();
			for(unsigned int pci=0;pci<mPCV_backup->size();pci++)
				delete mPCV_backup->at(pci);
			mPCV_backup->clear();
		}
		for(unsigned int tci=0;tci<mTCV->size();tci++)
			delete mTCV->at(tci);
		mTCV->clear();
		if(really_plot)
		{
			mTimer->TurnOff();
			plotHitsByModule(mod);
			mTimer->TurnOn();
			mTimer->Reset();
			mPrintDetail=false;
			cout<<"Please look at the plot. Press \"y\" to continue, \"n\" to end."<<endl;
			char input;
			cin>>input;
			if(input == 'y')
				continue;
			if(input == 'n')
				return kStEOF;
		}
		//check how many hits are clustered 
		for(int idet = 0; idet < 4; idet++){
			if(idet == 1) continue;				//bprs
			StSPtrVecEmcRawHit& hits=mEmcModule[idet]->hits();
			int clusteredhits = 0;
			for(int ihit = 0; ihit < hits.size(); ihit++){
				if(mUsed[idet]->At(ihit) == 1) clusteredhits++;
			}
			if(mFillHisto){
				mFracOfClusteredHits[idet]->Fill((float)clusteredhits/hits.size());
				mFracOfClusteredHitsByMod[idet]->Fill(mod,(float)clusteredhits/hits.size());
			}
		}

	}
	//associateTracksWithEmcPoints();
	if(mPrint)
		cout<<"clustering for this event finished."<<endl<<endl<<endl;
	if(mPrintMem && mMem) mMem->PrintMem("The end of the maker\t\t\t");
	if(mTally) mTally->Fill("StEmcPointMaker: End", 1);
	return kStOk;
}

void StEmcPointMaker::Clear(Option_t *opt)
{
	StMaker::Clear();
}

//backup cluster info into mE/PCV_backup
void StEmcPointMaker::backupSMDClusters()
{
	if(mPrint) cout<<"backup the SMD clusters"<<endl;
	for(unsigned int eci=0;eci<mECV_backup->size();eci++)
		delete mECV_backup->at(eci);
	mECV_backup->clear();
	for(unsigned int eci=0;eci<mECV->size();eci++)
	{
		StEmcEtaHitsCluster *c=new StEmcEtaHitsCluster(*(mECV->at(eci)));
		mECV_backup->push_back(c);
	}
	for(unsigned int pci=0;pci<mPCV_backup->size();pci++)
		delete mPCV_backup->at(pci);
	mPCV_backup->clear();
	for(unsigned int pci=0;pci<mPCV->size();pci++)
	{
		StEmcPhiHitsCluster *c=new StEmcPhiHitsCluster(*(mPCV->at(pci)));
		mPCV_backup->push_back(c);
	}
	if(mPrintDetail)
	{
		cout<<"backup the clusters"<<endl;
		cout<<"original size & backup copy size: "<<endl;
		cout<<"eta: "<<mECV->size()<<" & "<<mECV_backup->size()<<endl;
		for(unsigned int eci=0;eci<mECV->size();eci++)
		{
			mECV->at(eci)->print();
			cout<<endl;
			mECV_backup->at(eci)->print();
		}
		cout<<"phi: "<<mPCV->size()<<" & "<<mPCV_backup->size()<<endl;
		for(unsigned int pci=0;pci<mPCV->size();pci++)
		{
			mPCV->at(pci)->print();
			cout<<endl;
			mPCV_backup->at(pci)->print();
		}
	}
}

//clears clusters a& copy from backup
void StEmcPointMaker::recoverSMDClusters()
{
	if(mPrint) cout<<"recover the SMD clusters"<<endl;
	for(unsigned int eci=0;eci<mECV->size();eci++)
		delete mECV->at(eci);
	mECV->clear();
	for(unsigned int eci=0;eci<mECV_backup->size();eci++)
	{
		StEmcEtaHitsCluster *c=new StEmcEtaHitsCluster(*(mECV_backup->at(eci)));
		mECV->push_back(c);
	}
	for(unsigned int pci=0;pci<mPCV->size();pci++)
		delete mPCV->at(pci);
	mPCV->clear();
	for(unsigned int pci=0;pci<mPCV_backup->size();pci++)
	{
		StEmcPhiHitsCluster *c=new StEmcPhiHitsCluster(*(mPCV_backup->at(pci)));
		mPCV->push_back(c);
	}
	if(mPrintDetail)
	{
		cout<<"recover the clusters"<<endl;
		cout<<"backup size & recovered copy size: "<<endl;
		cout<<"eta: "<<mECV_backup->size()<<" & "<<mECV->size()<<endl;
		for(unsigned int eci=0;eci<mECV->size();eci++)
		{
			mECV_backup->at(eci)->print();
			cout<<endl;
			mECV->at(eci)->print();
		}
		cout<<"phi: "<<mPCV_backup->size()<<" & "<<mPCV->size()<<endl;
		for(unsigned int pci=0;pci<mPCV->size();pci++)
		{
			mPCV_backup->at(pci)->print();
			cout<<endl;
			mPCV->at(pci)->print();
		}
	}
}


void StEmcPointMaker::mergeSMDClusters()
{
	if(mPrint) cout<<"Merging SMD clusters..."<<"mMaxSMDSeedDist="<<mMaxSMDSeedDist<<", mMaxSMDBoundaryDist"<<mMaxSMDBoundaryDist<<", mMaxSMDCombinedNHits"<<mMaxSMDCombinedNHits<<endl; 
	bool ready1= (mECV->size()==1 && mPCV->size()==1);
	bool ready2= (mECV->size()==2 && mPCV->size()==2);
	bool ready;
	if(mMergeFlavor==1) ready = (ready1 || ready2);
	else ready = ready1;
	if(ready) return;					//don't merge anything if 1:1:1 or 1:2:2 favored

	if(mECV->size()>1 || mPCV->size()>1) 
	{
		int eta_seed_dist=0; 
		int phi_seed_dist=0; 
		int eta_boundary_dist=0;
		int phi_boundary_dist=0;
		//merge clusters w/ smaller boundary dist first
		while(!ready && (eta_boundary_dist<=mMaxSMDBoundaryDist) && (phi_boundary_dist<=mMaxSMDBoundaryDist))
		{
			eta_seed_dist=eta_boundary_dist;		//seed dist can't be smaller than boundary dist
			phi_seed_dist=phi_boundary_dist;
			bool out_seed_loop=false;
			bool into_seed_loop=false;
			ready1= (mECV->size()==1 && mPCV->size()==1);
			ready2= (mECV->size()==2 && mPCV->size()==2);
			if(mMergeFlavor==1) ready = (ready1 || ready2);
			else ready = ready1;
			//merge clusters w/ closer seeds first
			while(!ready && !out_seed_loop && ((eta_seed_dist<=mMaxSMDSeedDist) || (phi_seed_dist<=mMaxSMDSeedDist)))
			{
				into_seed_loop=true;
				if(mECV->size() > mPCV->size())
				{
					if(eta_seed_dist<=mMaxSMDSeedDist)
					{
						mergeEtaClusters(eta_seed_dist++, eta_boundary_dist, mMaxSMDCombinedNHits);
						ready1= (mECV->size()==1 && mPCV->size()==1);
						ready2= (mECV->size()==2 && mPCV->size()==2);
						if(mMergeFlavor==1) ready = (ready1 || ready2);
						else ready = ready1;
					}
					else
					{
						eta_boundary_dist++;
						out_seed_loop=true;
					}
				}
				else 
				{
					if(phi_seed_dist<=mMaxSMDSeedDist)
					{
						mergePhiClusters(phi_seed_dist++, phi_boundary_dist, mMaxSMDCombinedNHits);
						ready1= (mECV->size()==1 && mPCV->size()==1);
						ready2= (mECV->size()==2 && mPCV->size()==2);
						if(mMergeFlavor==1) ready = (ready1 || ready2);
						else ready = ready1;
					}
					else
					{
						phi_boundary_dist++;
						out_seed_loop=true;
					}
				}
			} //end of seed while
			if(!into_seed_loop)		//true when done w/ seed loop
			{
				eta_boundary_dist++;
				phi_boundary_dist++;
			}
		} // end of boundary while
	}
	return;
}

bool StEmcPointMaker::maskTowers(StSPtrVecEmcRawHit& thits)
{
	unsigned int m=thits.size();
	mEnergy[0]->Set(m);
	mEtaBin[0]->Set(m);
	mSub[0]->Set(m);
	mUsed[0]->Set(m);
	mEnergy[0]->Reset();
	mEtaBin[0]->Reset();
	mSub[0]->Reset();
	mUsed[0]->Reset();
	if(mPrintDetail)
	{
		cout<<endl;
		cout<<setw(160)<<setfill('-')<<"Tower HITS"<<endl;
		cout.fill(' ');
	}
	for(unsigned int i=0;i<m;i++)
	{
		Int_t status;
		Int_t id = thits[i]->softId(1);					//doesn't work for SMD, not using for towers for safety -- pk 5/4/07
	//	int m, e, s, id;
	//	thits[i]->modEtaSub(m,e,s);
	//	mGeo[0]->getId(m,e,s,id);
		mTables->getStatus(1,id,status);
		//if(thits[i]->calibrationType()<128)
		if(fabs(thits[i]->energy())>0.000000001 && (thits[i]->adc()!=0) && status==1) 
			(*mEnergy[0])[i]=thits[i]->energy();
		else
			(*mEnergy[0])[i]=-999;
		(*mEtaBin[0])[i]=thits[i]->eta();
		(*mSub[0])[i]=abs(thits[i]->sub());
		if(mPrintDetail)
		{
			cout<<setw(8)<<setprecision(3)<<mEnergy[0]->At(i);
			if(i==19 || i==39)
				cout<<endl;
		}
	}
	if(mPrintDetail)
	{
		cout<<setw(160)<<setfill('-')<<"Tower HITS"<<endl;
		cout.fill(' ');
		cout<<endl;
	}
	return true;
}

bool StEmcPointMaker::clusterTowers(StSPtrVecEmcRawHit& thits, float seed, float add)
{
	if(!mTCV) mTCV = new vector<StEmcTowerHitsCluster*>;	
	mTCV->clear();
	if(mPrintDetail)
		cout<<"Cluster towers, Seed = "<<seed<<" Add = "<<add<<endl;
	if(add<=0 || seed<=0) return false;
	if(thits.size()!=(unsigned int)mEnergy[0]->GetSize()) return false;
	unsigned int m=thits.size();
	if(m==0) return false;

	int clusteredhits = 0;

	TTableSorter index(mEnergy[0]->GetArray(), m);				//create index of energy in increasing order
	if(mEnergy[0]->At(index.GetIndex(m-1))<seed)
	{
		if(mPrintDetail)
			cout<<"no hit has energy larger than seed energy, nothing to cluster"<<endl;
		return true;
	}
	bool newaction=true;
	while(newaction)
	{
		newaction=false;
		for(int i=m-1;i>=0;i--)
		{
			int j=index.GetIndex(i);
			if(mUsed[0]->At(j))
			{
				if(mPrintDetail)
					cout<<"hit has been used, used="<<mUsed[0]->At(j)<<endl;
				continue;
			}
			if(mEnergy[0]->At(j)<add) break;			//remaining hit energies below threshold
			if(mPrintDetail)
				cout<<"Clustering hit: "<<j+1<<" with E="<<mEnergy[0]->At(j)<<" -> "<<endl;
			for(unsigned int cl=0;cl<mTCV->size();cl++)
			{
				if(mPrintDetail)
				{
					cout<<"Testing it on existed cluster "<<cl+1<<"-> ";
					mTCV->at(cl)->print();
				}
				//hit added to first cluster that contains hit neighboring current hit
				if((mUsed[0]->At(j)==0) && mTCV->at(cl)->canCluster(thits[j]) && !mTCV->at(cl)->contain(thits[j]))
				{
					mTCV->at(cl)->addHit(thits[j],1);
					if(mPrintDetail)
						cout<<"\tCan Cluster! Added"<<endl;
					(*mUsed[0])[j]=1;
					clusteredhits++;
					newaction=true;
					break;
				}
				else
					if(mPrintDetail)
						cout<<"\tCan't Cluster!"<<endl;
			}
			if(mUsed[0]->At(j)==0)		
			{
				if(mEnergy[0]->At(j)>seed && !(*mUsed[0])[j])
				{
					if(mPrintDetail)
						cout<<"Not belonging to any existed cluster, create a new cluster..."<<endl;
					StEmcTowerHitsCluster *c=new StEmcTowerHitsCluster();
					c->addHit(thits[j],1.0);
					mTCV->push_back(c);
					(*mUsed[0])[j]=1;
					clusteredhits++;
					newaction=true;
				}
				else
				{
					if(mPrintDetail)
						cout<<"Lonely hit, but energy less than seed energy"<<endl;
				}
			}
			//cout<<"Tower Cluster Vector Size:"<<mTCV->size()<<endl;
		}
	}

	//if(mFillHisto) mFracOfClusteredHits[0]->Fill(clusteredhits/m);
	/*
	for(unsigned int i=0;i<mTCV->size();i++)
	{
		if(!mTCV->at(i))
			continue;
		if(mTCV->at(i)->energy()<total)
		{
			if(mPrintDetail)
				cout<<mTCV->at(i)->energy()<<" is less than "<<total<<", erase this cluster"<<endl;
			delete mTCV->at(i);
			mTCV->at(i)=NULL;
		}
	}
	purgeTowerClusters(mTCV);
	*/
	if(mPrintDetail)
	{
		cout<<"Tower clustering finished. "<<mTCV->size()<<" cluster(s):"<<endl;
		for(unsigned int cl=0;cl<mTCV->size();cl++)
		{
			mTCV->at(cl)->print();
			cout<<endl;
		}
		cout<<endl<<endl<<endl;
	}
	return true;
}

void StEmcPointMaker::mergeTowerClusters()
{
	if(!mTCV) return;
	if(mTCV->size()<=1) return;
	bool newaction=true;

	int size = mTCV->size();
	int mergecount = 0;
	while(newaction)
	{
		newaction=false;
		for(unsigned int i=0;i<mTCV->size();i++)
		{
			if(!mTCV->at(i))
				continue;
			for(unsigned int j=i+1;j<mTCV->size();j++)
			{
				if(!mTCV->at(j))
					continue;
				if(mTCV->at(i)->canCluster(mTCV->at(j)))
				{
					if(mPrintDetail)
						cout<<"Two tower clusters are neighbors, merge them"<<endl;
					mTCV->at(i)->forceMerge(mTCV->at(j));
					mergecount++;
					if(mFillHisto) mNMergedvTotalCl[0]->Fill(size,mergecount++);
					delete mTCV->at(j);
					mTCV->at(j)=NULL;
					newaction=true;
				}
			}
		}
	}
	purgeTowerClusters();
}

void StEmcPointMaker::purgeTowerClusters()
{
	if(!mTCV) return;
	vector<StEmcTowerHitsCluster*>::iterator iter;
	for(iter=mTCV->begin();iter!=mTCV->end();iter++)
	{
		if(!(*iter))
		{
			mTCV->erase(iter);
			iter--;
		}
	}
}

bool StEmcPointMaker::analyzeTowerHits(StSPtrVecEmcRawHit& thits)
{
	if(mPrintDetail) cout << " Analyzing tower hits"<<endl;
	if(thits.size()==0) return false;
	float ee;
	mHitsEnergyInMod[0]->Reset();
	for(unsigned int i=0;i<thits.size();i++)
	{
		ee=thits[i]->energy();
		if(fabs(ee)>0.000000001)
			mHitsEnergyInMod[0]->Fill(ee);
	}
	mNOK[0]=(unsigned int)(mHitsEnergyInMod[0]->GetEntries());
	mNRange[0]=(unsigned int)(mHitsEnergyInMod[0]->Integral());
	mBin[0]=mHitsEnergyInMod[0]->GetMaximumBin();
	mMean[0]=mHitsEnergyInMod[0]->GetBinCenter(mBin[0]);			//highest bin, not histogram's mean
	mSigma[0]=mHitsEnergyInMod[0]->GetRMS();
	mMax[0]=mHitsEnergyInMod[0]->GetMaximum();
	mFitFunc->SetParameter(0,mMax[0]);
	mFitFunc->SetParameter(1,mMean[0]);
	mFitFunc->SetParameter(2,mSigma[0]);
	mFitFunc->SetParLimits(2,-0.1,0.1);
	float left=mMean[0]-4*mSigma[0];
	float right=mMean[0]+4*mSigma[0];
	mFitFunc->SetRange(left,right);
	if(mPlot)
		mHitsEnergyInMod[0]->Fit(mFitFunc,"RQ");
	else
		mHitsEnergyInMod[0]->Fit(mFitFunc,"RQ0");
	mMean[0]=mFitFunc->GetParameter(1);
	mSigma[0]=fabs(mFitFunc->GetParameter(2));
	mChiNDF[0]=mFitFunc->GetChisquare()/mFitFunc->GetNDF();
	/*
	if(mPrintDetail || mPlot)
		mHitsEnergyInMod[0]->Fit("gaus");
	else
		mHitsEnergyInMod[0]->Fit("gaus","Q0");
	mMean[0]=mHitsEnergyInMod[0]->GetFunction("gaus")->GetParameter(1);
	mSigma[0]=mHitsEnergyInMod[0]->GetFunction("gaus")->GetParameter(2);
	mChiNDF[0]=mHitsEnergyInMod[0]->GetFunction("gaus")->GetChisquare()/mHitsEnergyInMod[0]->GetFunction("gaus")->GetNDF();
	*/
	int mod = thits[0]->module();
	if(mFillHisto){						//3/22/07 -- to find out what's normal
		mModNOKHits[0]->Fill(mod,mNOK[0]);
		mModNRange[0]->Fill(mod,mNRange[0]);
		mModChiNDF[0]->Fill(mChiNDF[0]);
//	}												//eliminate requirements to get Mean, Sigma for all
//	if(mFillHisto && mChiNDF[0]<0.5 && fabs(mMean[0])<0.5 && mSigma[0]<0.05 && mNRange[0]==40)
//	{
		if(mModHitsSigma[0]) mModHitsSigma[0]->Fill(mod, mSigma[0]);
		if(mModHitsMean[0]) mModHitsMean[0]->Fill(mod, mMean[0]);
		if(mModClusterThr[0]) mModClusterThr[0]->Fill(mod, mMean[0]+3*mSigma[0]);
	}
	return true;
}

bool StEmcPointMaker::clearEmc() //after clearEmc(), the emc collection should only have StEmcRawHits
{
	if(!mEmcCol) return false;

	StSPtrVecEmcPoint& pvec = mEmcCol->barrelPoints();
	if(pvec.size()>0) pvec.clear();
	for(int det=0;det<4;det++)
	{
		if(det!=1)
		{
			StDetectorId id=static_cast<StDetectorId>(det+kBarrelEmcTowerId);
			mEmcDet[det]=mEmcCol->detector(id);
			if(mEmcDet[det])
			{
				mEmcClCol[det]=mEmcDet[det]->cluster();
				if(!mEmcClCol[det])
				{
					mEmcClCol[det]=new StEmcClusterCollection();
					mEmcDet[det]->setCluster(mEmcClCol[det]);
				}
				StSPtrVecEmcCluster& clusters=mEmcClCol[det]->clusters();
				if(clusters.size()>0) clusters.clear();
				mEmcClCol[det]->setDetector(id);
				mEmcClCol[det]->setClusterFinderId(9);
				mEmcClCol[det]->setClusterFinderParamVersion(1);
			}
			else return false;
		}
	}
	return true;
}

void StEmcPointMaker::plotHitsByModule(int module)
{
	if(!mCanvas) return;
	mCanvas->Clear();
	mCanvas->Divide(1,4);
	int pad=1;
	for(int det=0;det<4;det++)
	{
		if(det!=1)
		{
			mHitsInMod[det]->Reset();
			if(!mAnalyzeModule) mHitsEnergyInMod[det]->Reset();
			if(mEmcModule[det])
			{
				StSPtrVecEmcRawHit& hits=mEmcModule[det]->hits();	
				for(unsigned int i=0;i<hits.size();i++)
				{
					float abseta;
					float ee=hits[i]->energy();
					mGeo[det]->getEta(module,hits[i]->eta(),abseta);
					abseta=fabs(abseta);
					float phi,localphi,modulephi;
					mGeo[det]->getPhi(module,abs(hits[i]->sub()),phi);
					mGeo[det]->getPhiModule(module,modulephi);
					localphi=phi-modulephi;
					if(module<=60)
						localphi=-localphi;
					if(localphi>TMath::Pi()/60)//module 43 has phi of -pi
						localphi-=TMath::TwoPi();
					if(localphi<-TMath::Pi()/60)
						localphi+=TMath::TwoPi();
					mHitsInMod[det]->Fill(abseta,localphi,ee);
					//cout<<setw(20)<<setprecision(10)<<module<<" "<<localphi<<" "<<phi<<" "<<modulephi<<endl;
					if(!mAnalyzeModule)
						//if(abs(ee)>0.000000001) mHitsEnergyInMod[det]->Fill(ee); error fix 
						if(fabs(ee)>0.000000001) mHitsEnergyInMod[det]->Fill(ee);
				}
			}
			else continue;
			mCanvas->cd(pad++);
			//mHitsInMod[det]->Draw("COLZ");
			mHitsInMod[det]->Draw("LEGO2");
		}
	}
	mCanvas->GetListOfPrimitives();
	TString pname(mCanvas->GetName());
	TPad* pad4=(TPad*)(mCanvas->GetPrimitive(pname+"_4"));
	pad4->Divide(3,1);
	int subpad=1;
	for(int det=0;det<4;det++)
	{
		if(det!=1)
		{
			pad4->cd(subpad++);
			mHitsEnergyInMod[det]->Draw();
			//mHitsEnergyInMod[det]->Fit("gaus");//,"","",-0.1,0.1);
		}
	}
	mCanvas->Update();
}


void StEmcPointMaker::addPoint(float E_ratio)
{
	if(!mTowerCluster) return;
	//if(!mEtaCluster && !mPhiCluster) return;
	StEmcPoint *point=new StEmcPoint();
	//borrow a few bytes for labels//////////////////////
	Float_t label=mMaxSMDCombinedNHits*10000+mMaxSMDSeedDist*1000+mMaxSMDBoundaryDist*100+mMergeFlavor*10+mShareFlavor;
	point->setDeltaU(label);
	Int_t plabel,elabel;
	if(mPhiCluster)
		plabel=10*mPhiCluster->mSeedNSigma+mPhiCluster->mAddonNSigma;
	else plabel=0;
	if(mEtaCluster)
		elabel=10*mEtaCluster->mSeedNSigma+mEtaCluster->mAddonNSigma;
	else elabel=0;
	point->setDeltaV(elabel*100+plabel);
	//borrow a few bytes for labels//////////////////////
	float e=mTowerCluster->energy()*E_ratio;
	float eta, phi;
	if(mEtaCluster) 
		eta=mEtaCluster->eta();			//energy weighted
	else 
		eta=mTowerCluster->eta();
	if(mPhiCluster)
		phi=mPhiCluster->phi();			//energy weighted
	else
		phi=mTowerCluster->phi();
	if(mFillHisto)
	{
		if(mPointEnergy) mPointEnergy->Fill(e);
		if(mPointEta_Phi) mPointEta_Phi->Fill(eta,phi);
		if(mPointEWeightedEta_Phi) mPointEWeightedEta_Phi->Fill(eta,phi,e);
		if(mEtaTowerECorr && mEtaCluster) mEtaTowerECorr->Fill(mEtaCluster->energy(),mTowerCluster->energy());
		if(mPhiTowerECorr && mPhiCluster) mPhiTowerECorr->Fill(mPhiCluster->energy(),mTowerCluster->energy());
		if(mEtaPhiECorr && mEtaCluster && mPhiCluster) mEtaPhiECorr->Fill(mEtaCluster->energy(),mPhiCluster->energy());
	}
	float xp,yp,zp;
	float r_xy, r_z;
	if(mPhiCluster) r_xy=mGeo[3]->Radius();
	else r_xy=mGeo[0]->Radius();
	if(mEtaCluster) r_z=mGeo[2]->Radius();
	else r_z=mGeo[0]->Radius();
	xp=r_xy*cos(phi);
	yp=r_xy*sin(phi);
	zp=r_z*sinh(eta);
	StThreeVectorF ptpos(xp*centimeter,yp*centimeter,zp*centimeter);
	point->setPosition(ptpos);
	point->setEnergy(e);							//point energy is only tower cluster energy
										//tower not split if one or more SMD plane missing
	//position and size of  point
	float sigma_eta;
	float sigma_phi;
	if(mEtaCluster)
		sigma_eta=mEtaCluster->sigmaEta();
	else
		sigma_eta=mTowerCluster->sigmaEta();
	if(mPhiCluster)
		sigma_phi=mPhiCluster->sigmaPhi();
	else
		sigma_phi=mTowerCluster->sigmaPhi();
	StThreeVectorF size(sigma_eta, sigma_phi, 0);
	point->setSize(size);
	/////////////////////////////////////////////place holders////////
	//StThreeVectorF errpos(0,0,0);					//
	//point->setPositionError(errpos);				//
	//float chisquare=0;						//
	//point->setChiSquare(chisquare);				//
	////////////////////////////////////////////place holders/////////
	for(int i=0;i<4;i++)
	{
		if(i!=1)
		{
			StDetectorId id=static_cast<StDetectorId>(i+kBarrelEmcTowerId);
			StEmcHitsCluster* mycl=0;
			switch(i)
			{
				case 0:
					mycl=(StEmcHitsCluster*)mTowerCluster;
					point->setSizeAtDetector(id,mycl->sigmaEta()+mycl->sigmaPhi()); //doesn't make much sense
					if(mFillHisto && mNTowerHits_Energy)
						mNTowerHits_Energy->Fill(e, mycl->nHits());
					break;
				case 2:
					if(mEtaCluster)
					{
						mycl=(StEmcHitsCluster*)mEtaCluster;
						point->setSizeAtDetector(id,mycl->sigmaEta());
						if(mFillHisto)
						{	
							if(mSigmaEta_Energy) mSigmaEta_Energy->Fill(e, mycl->sigmaEta());
							if(mNEtaHits_Energy) mNEtaHits_Energy->Fill(e, mycl->nHits());
						}
					}
					else
						point->setSizeAtDetector(id,0);
					break;
				case 3:
					if(mPhiCluster)
					{
						mycl=(StEmcHitsCluster*)mPhiCluster;
						point->setSizeAtDetector(id,mycl->sigmaPhi());
						if(mFillHisto)
						{
							if(mSigmaPhi_Energy) mSigmaPhi_Energy->Fill(e,mycl->sigmaPhi());
							if(mNPhiHits_Energy) mNPhiHits_Energy->Fill(e,mycl->nHits());
						}
					}
					else
						point->setSizeAtDetector(id,0);
					break;
				default:
					break;
			}
			//fill point cluster info
			if(mycl)
			{
				point->setEnergyInDetector(id,mycl->energy());
				mEmcCl[i]=new StEmcCluster();
				mEmcCl[i]->setEta(mycl->eta());
				mEmcCl[i]->setPhi(mycl->phi());
				mEmcCl[i]->setEnergy(mycl->energy());
				mEmcCl[i]->setSigmaEta(mycl->sigmaEta());
				mEmcCl[i]->setSigmaPhi(mycl->sigmaPhi());
				for(int h=0;h<mycl->nHits();h++)
					mEmcCl[i]->addHit(mycl->getHits()->at(h));
				point->addCluster(id,mEmcCl[i]);
				mEmcClCol[i]->addCluster(mEmcCl[i]);
			}
			else
			{
				point->setEnergyInDetector(id,0);
			}
		}
	}

	mEmcCol->addBarrelPoint(point);
	if(mPrint)
		cout<<"Point added: E="<<e<<", Eta="<<eta<<", Phi="<<phi<<", x="<<xp<<", y="<<yp<<", z="<<zp<<endl;
}

void StEmcPointMaker::makeOnePoint()
{
}


void StEmcPointMaker::makePoints()
{
	if(!mTowerCluster || !mECV || !mPCV) return;
	Int_t neta=mECV->size();
	Int_t nphi=mPCV->size();
	/*
	int category;

	if(neta==0 && nphi==0)
	{
		category=0;
		n=1;
		m=1;
	}
	if(neta>0 && nphi==0)
	{
		category=1;
		n=neta;
		m=1;
	}
	if(neta==0 && nphi>0)
	{
		category=2;
		n=1;
		m=nphi;
	}
	if(neta>0 && nphi>0)
	{
		category=3;
		n=neta;
		m=nphi;
	}
	*/
	if(mPrint)
	{
		cout<<"Now make points with flavor "<<mShareFlavor<<endl;
		cout<<"Tower cluster: ";
		mTowerCluster->print();
		cout<<endl;
		cout<<neta<<" Eta cluster(s): ";
		for(int i=0;i<neta;i++)
		{
			mECV->at(i)->print();
			cout<<endl;
		}
		cout<<nphi<<" Phi cluster(s): ";
		for(int j=0;j<nphi;j++)
		{
			mPCV->at(j)->print();
			cout<<endl;
		}
	}

	if(mFillHisto){
		mNEtaClustersBelow->Fill(neta);
		mNPhiClustersBelow->Fill(nphi);
		mNClustersBelow->Fill(neta,nphi);
	}

	if(neta==0 && nphi==0)			//no hits in clusters
	{
		mEtaCluster=NULL;
		mPhiCluster=NULL;
		addPoint(1.0);
		return;
	}

	if(neta==0 && nphi!=0)			//if either plane missing, takes the first cluster
	{
		mEtaCluster=NULL;
		mPhiCluster=mPCV->at(0);
		addPoint(1.0);
		return;
	}

	if(neta!=0 && nphi==0)
	{
		mEtaCluster=mECV->at(0);
		mPhiCluster=NULL;
		addPoint(1.0);
		return;
	}

	if(neta>=1 && nphi>=1)
	{
		float energydiff=0;
		int etadiff=0;
		Float_t cost[10][10]={{0}};
		Float_t cost2[10][10]={{0}};

                vector<StEmcPhiHitsCluster*>::iterator phiiter;
                vector<StEmcEtaHitsCluster*>::iterator etaiter;
                int etai=0;
                int phii=0;
		//get energy and eta diff between all pairs of eta & phi clusters
                for(etaiter=mECV->begin();etaiter!=mECV->end();etaiter++,etai++)
                {
                        for(phiiter=mPCV->begin();phiiter!=mPCV->end();phiiter++,phii++)
                        {
                                if(!(*etaiter) && !(*phiiter))
                                {
                                        energydiff=fabs((*etaiter)->energy() - (*phiiter)->energy())/((*etaiter)->energy() + (*phiiter)->energy());
                                        etadiff=int(fabs((*etaiter)->eta() - (*phiiter)->eta())/0.05);
                                        cost[phii][etai]=energydiff+etadiff;
					cost2[phii][etai]=energydiff;
                                }
                        }
                }


		/*
		for(int etai=0;etai<neta;etai++)
		{
			for(int phii=0;phii<nphi;phii++)
			{
				energydiff=fabs(mECV->at(etai)->energy() - mPCV->at(phii)->energy())/(mECV->at(etai)->energy() + mPCV->at(phii)->energy());
				etadiff=int(fabs(mECV->at(etai)->eta() - mPCV->at(phii)->eta())/0.05);
				cost[phii][etai]=energydiff+etadiff;
			}
		}*/

		Int_t k[10];
		Int_t k2[10];
		Float_t smin;
		Int_t iw[10][10];
		Int_t mode=1;
		Int_t ida=10;
		Int_t idw=10;

		int ndiffpair = 0;

		//finds pairs of eta & phi clusters 
		assndx(mode,cost[0],neta,nphi,ida,k,smin,iw[0],idw);	//Fortran - "assignment problem"
		assndx(mode,cost2[0],neta,nphi,ida,k2,smin,iw[0],idw);	//Fortran - "assignment problem" - energy difference only
		float totalE=0;
		int npair=0;
		for(int etai=0;etai<neta;etai++)			//etai = index of eta cluster, k[etai] = index of phi cluster + 1
		{
			if(k[etai]>0)
			{
				totalE += mECV->at(etai)->energy()+mPCV->at(k[etai]-1)->energy();
				npair++;

				//count # of different pairs
				if(k[etai] != k2[etai]) ndiffpair++;
			}
		}
		
		if(mFillHisto) mNDiffPairvNPair->Fill(ndiffpair,npair);

		float E_ratio=0;
		for(int etai=0;etai<neta;etai++)			//add point for every eta w/ phi cluster
		{
			if(k[etai]>0)
			{
				if(totalE!=0)
					E_ratio = (mECV->at(etai)->energy()+mPCV->at(k[etai]-1)->energy())/totalE;
				if(mShareFlavor==1 && npair==2) E_ratio=0.5;
				mEtaCluster=mECV->at(etai);
				mPhiCluster=mPCV->at(k[etai]-1);
				addPoint(E_ratio);			//tower energy split by SMD energy ratio
			}
		}
		return;
	}
	return;
}


bool StEmcPointMaker::analyzeSMDHits(int det, const StSPtrVecEmcRawHit& hits)
{
	if(mPrintDetail) cout<<"Analyzing "<<detname[det]<<" hits"<<endl;
	if(hits.size()==0)
		return false;
	float ee;
	mHitsEnergyInMod[det]->Reset();
	for(unsigned int i=0;i<hits.size();i++)
	{
		ee=hits[i]->energy();
		if(fabs(ee)>0.000000001)
			mHitsEnergyInMod[det]->Fill(ee);
	}
	mNOK[det]=(unsigned int)(mHitsEnergyInMod[det]->GetEntries());
	mNRange[det]=(unsigned int)(mHitsEnergyInMod[det]->Integral());

	mBin[det]=mHitsEnergyInMod[det]->GetMaximumBin();
	mMean[det]=mHitsEnergyInMod[det]->GetBinCenter(mBin[det]);
	mSigma[det]=mHitsEnergyInMod[det]->GetRMS();
	mMax[det]=mHitsEnergyInMod[det]->GetMaximum();
	mFitFunc->SetParameter(0,mMax[det]);
	mFitFunc->SetParameter(1,mMean[det]);
	mFitFunc->SetParameter(2,mSigma[det]);
	mFitFunc->SetParLimits(2,-0.1,0.1);
	float left=mMean[det]-4*mSigma[det];
	float right=mMean[det]+4*mSigma[det];
	mFitFunc->SetRange(left,right);
	if(mPlot)
		mHitsEnergyInMod[det]->Fit(mFitFunc,"RQ");
	else
		mHitsEnergyInMod[det]->Fit(mFitFunc,"RQ0");
	mMean[det]=mFitFunc->GetParameter(1);
	mSigma[det]=fabs(mFitFunc->GetParameter(2));
	mChiNDF[det]=mFitFunc->GetChisquare()/mFitFunc->GetNDF();
	/*
	if(mPrintDetail)
		mHitsEnergyInMod[det]->Fit("gaus");
	else
		mHitsEnergyInMod[det]->Fit("gaus","Q0");
	mean=mHitsEnergyInMod[det]->GetFunction("gaus")->GetParameter(1);
	sigma=mHitsEnergyInMod[det]->GetFunction("gaus")->GetParameter(2);
	chindf=mHitsEnergyInMod[det]->GetFunction("gaus")->GetChisquare()/mHitsEnergyInMod[det]->GetFunction("gaus")->GetNDF();
	*/
	int mod = hits[0]->module();
	if(mFillHisto){						//3/22/07 -- to find out what's normal
		mModNOKHits[det]->Fill(mod,mNOK[det]);
		mModNRange[det]->Fill(mod,mNRange[det]);
		mModChiNDF[det]->Fill(mChiNDF[det]);
//	}
//	if(mFillHisto && fabs(mMean[det])<0.5 && mSigma[det]<0.1 && mChiNDF[det]<0.5 && mNRange[det]==150)
//	{
		if(mModHitsSigma[det]) mModHitsSigma[det]->Fill(mod, mSigma[det]);
		if(mModHitsMean[det]) mModHitsMean[det]->Fill(mod, mMean[det]);
		if(mModClusterThr[det]) mModClusterThr[det]->Fill(mod, mMean[det]+2*mSigma[det]);
	}
	if(mPrintDetail) cout<<"mean="<<mMean[det]<<", sigma="<<mSigma[det]<<endl;
	return true;
}

bool StEmcPointMaker::maskEtaStrips(StSPtrVecEmcRawHit& ehits)
{
	if(!mTowerCluster)
		return false;
	if(mTowerCluster->nHits()==0)
		return false;
	unsigned int m=ehits.size();
	int ebinmin=200;
	int ebinmax=-200;
	for(unsigned int h=0;h<mTowerCluster->getHits()->size();h++)
	{
		int ebin=mTowerCluster->getHits()->at(h)->eta();
		if(ebin<ebinmin) ebinmin=ebin;
		if(ebin>ebinmax) ebinmax=ebin;
	}
	float etamin = mGeo[0]->EtaB()[ebinmin-1];
	float etamax = mGeo[0]->EtaB()[ebinmax];
	int mod=mTowerCluster->module();
	if(mod > 60){
		float temp = etamin;
		etamin = -etamax;
		etamax = -temp;
	}
	if(mPrintDetail)
	{
		cout<<"\t"<<"The tower cluster has "<<etamin<<"<eta<"<<etamax<<endl;
		cout<<"\t"<<m<<" eta hit(s) in module "<<mod<<endl;
	}
	mEnergy[2]->Set(m);
	mEtaBin[2]->Set(m);
	mSub[2]->Set(m);
	mUsed[2]->Set(m);
	mEnergy[2]->Reset();
	mEtaBin[2]->Reset();
	mSub[2]->Reset();
	mUsed[2]->Reset();

	int nehits = 0;
	for(unsigned int i=0;i<m;i++)
	{
		Int_t statuscode;
		Int_t id = ehits[i]->softId(3);					//doesn't work for some reason -- pk 5/4/07
	//	int m, e, s, id;
	//	ehits[i]->modEtaSub(m,e,s);
	//	mGeo[2]->getId(m,e,s,id);
		mTables->getStatus(3,id,statuscode);
		Bool_t status = statuscode==1 || statuscode==3 || statuscode==0 || statuscode==7 || statuscode==8;

		(*mEtaBin[2])[i]=ehits[i]->eta();
		(*mSub[2])[i]=abs(ehits[i]->sub());
		if(mPrintDetail)
			cout<<"\t"<<"eta bin "<<setw(3)<<mEtaBin[2]->At(i)<<" :: phi bin "<<setw(2)<<mSub[2]->At(i)<<" :: id "<<setw(6)<<id;
		float globaleta;
		mGeo[2]->getEta(mod, mEtaBin[2]->At(i), globaleta);
		if(mPrintDetail)
			cout<<" :: eta "<<setw(6)<<globaleta<<" :: energy "<<setw(5)<<ehits[i]->energy()<<" :: status "<<setw(3)<<statuscode<<endl;
		if(etamin<=globaleta && globaleta<=etamax && fabs(ehits[i]->energy())>0.000000001 && ehits[i]->calibrationType()<128 && status)
		{
			(*mEnergy[2])[i]=ehits[i]->energy();
			nehits++;
		}
		else
			(*mEnergy[2])[i]=-999;
	}
	if(mPrintDetail)
		cout<<"\t"<<nehits<<" Eta hit(s) below the tower cluster"<<endl;
	if(mFillHisto && mNEtaStripsBelow)
		mNEtaStripsBelow->Fill(nehits);
	return true;
}

bool StEmcPointMaker::clusterEtaStrips(StSPtrVecEmcRawHit& ehits, float seed, float add)
{
	if(mPrintDetail)
		cout<<"\tCluster Eta strips, Seed = "<<seed<<" Add = "<<add<<endl;
	if(add<0 || seed<0) return false;
	if(!mECV) mECV=new vector<StEmcEtaHitsCluster*>; 
	mECV->clear();
	if((unsigned int)mEnergy[2]->GetSize()!=ehits.size()) return false;
	int n=mEnergy[2]->GetSize();
	if(n==0) return false;

	int clusteredhits = 0;
	vector<int> dist;
	dist.clear();
	TTableSorter index(mEnergy[2]->GetArray(),n);
	if(seed==999 && add==999)
	{
		int j=index.GetIndex(n-1);
		if(mECV->size()==0 && mEnergy[2]->At(j))
		{
			StEmcEtaHitsCluster *c=new StEmcEtaHitsCluster();
			c->addHit(ehits[j],1.0);
			mECV->push_back(c);
			return true;
		}
	}
		
	if(mEnergy[2]->At(index.GetIndex(n-1))<seed)
	{
		if(mPrintDetail)
			cout<<"\tno hit has energy larger than seed energy, nothing to cluster"<<endl;
		return true;
	}
	for(int i=n-1;i>=0;i--)
	{
		int ncluster = 0;
		int j=index.GetIndex(i);
		if(mEnergy[2]->At(j)<add) break;	//no hits w/ energy above threshold. stop
		if(mPrintDetail)
			cout<<"\t"<<"Clustering hit: "<<j+1<<" with E="<<mEnergy[2]->At(j)<<" -> "<<endl;
		float etot=0;
		bool cancluster=false;
		dist.resize(mECV->size());		//array to keep track of distance of cluster to all other clusters
		for(unsigned int cl=0;cl<mECV->size();cl++)
		{
			if(mPrintDetail)
			{
				cout<<"\t"<<"Testing it on existed cluster(s):";
				mECV->at(cl)->print();
			}
			dist[cl]=mECV->at(cl)->distance(ehits[j]);
			if(dist[cl]==0)			//hit is adjacent to a hit in cluster
			{
				if(mPrintDetail)
					cout<<"\t"<<"Can Cluster!"<<endl;
				etot+=mECV->at(cl)->energy();
				cancluster=true;
			}
			else
				if(mPrintDetail)
					cout<<"\t"<<"Can't Cluster!"<<endl;
		}
		if(cancluster)
		{
			for(unsigned int cl=0;cl<mECV->size();cl++)
			{
				if(dist[cl]==0){
					mECV->at(cl)->addHit(ehits[j],mECV->at(cl)->energy()/etot);	//hit is split using cluster energy ratio
					clusteredhits++;
					ncluster++;
				}
			}
		}
		else
		{
			if(mEnergy[2]->At(j)>seed && !mUsed[2]->At(j))
			{
				if(mPrintDetail)
					cout<<"\t"<<"Not belonging to any existed cluster, create a new cluster..."<<endl;
				StEmcEtaHitsCluster *c=new StEmcEtaHitsCluster();
				c->addHit(ehits[j],1.0);
				(*mUsed[2])[j]=1;
				clusteredhits++;
				ncluster++;
				mECV->push_back(c);
			}
			/*
			   else
			   for(unsigned int cl=0;cl<mECV->size();cl++)
			   {
			   if(dist[cl]==1)//allow holes
			   {
			   mECV->at(cl)->addHit(ehits[j],1.0);
			   break;
			   }
			   }
			 */
		}
		//cout<<"Tower Cluster Vector Size:"<<mTCV->size()<<endl;
		if(mFillHisto) mNClusterPerHit[2]->Fill(ncluster);
	}

	//if(mFillHisto) mFracOfClusteredHits[2]->Fill((float)clusteredhits/n);

	if(mPrintDetail)
	{
		cout<<"\tEta clustering finished"<<endl;
		for(unsigned int eci=0;eci<mECV->size();eci++)
		{
			cout<<"\t";
			mECV->at(eci)->print();
			cout<<endl;
		}
		cout<<endl<<endl<<endl;
	}
	return true;
}

void StEmcPointMaker::mergeEtaClusters(int seeddist, int bounddist, int nhits)
{
	if(!mECV)
		return;
	if(mECV->size()<=1)
		return;
	int size = mECV->size();
	int mergecount = 0;

	bool newaction=true;
	while(newaction)
	{
		newaction=false;
		for(unsigned int i=0;i<mECV->size();i++)
		{
			if(!mECV->at(i))
				continue;
			for(unsigned int j=i+1;j<mECV->size();j++)
			{
				if(!mECV->at(j))
					continue;
				bool cond1=(mECV->at(i)->seedDistance(mECV->at(j))<=seeddist);
				bool cond2=(mECV->at(i)->distance(mECV->at(j))<=bounddist);
				bool cond3=((mECV->at(i)->nHits() + mECV->at(j)->nHits() + mECV->at(i)->distance(mECV->at(j)))<=nhits);
				if(cond1 && cond2 && cond3)
				{
					if(mPrintDetail)
						cout<<"Two eta clusters are too close, merge them"<<endl;
					mECV->at(i)->forceMerge(mECV->at(j));
					mergecount++;
					if(mFillHisto) mNMergedvTotalCl[2]->Fill(size,mergecount);
					delete mECV->at(j);
					mECV->at(j)=NULL;
					newaction=true;
				}
			}
		}
	}
	purgeEtaClusters();
}

void StEmcPointMaker::purgeEtaClusters()
{
	if(!mECV)
		return;
	vector<StEmcEtaHitsCluster*>::iterator iter;
	for(iter=mECV->begin();iter!=mECV->end();iter++)
	{
		if(!(*iter))
		{
			mECV->erase(iter);
			iter--;
		}
	}
}

void StEmcPointMaker::mergePhiClusters(int seeddist, int bounddist, int nhits)
{
	if(!mPCV)
		return;
	if(mPCV->size()<=1)
		return;
	bool newaction=true;
	int size = mPCV->size();
	int mergecount = 0;

	while(newaction)
	{
		newaction=false;
		for(unsigned int i=0;i<mPCV->size();i++)
		{
			if(!mPCV->at(i))
				continue;
			for(unsigned int j=i+1;j<mPCV->size();j++)
			{
				if(!mPCV->at(j))
					continue;
				bool cond1=(mPCV->at(i)->seedDistance(mPCV->at(j))<=seeddist);
				bool cond2=(mPCV->at(i)->distance(mPCV->at(j))<=bounddist);
				bool cond3=((mPCV->at(i)->nHits() + mPCV->at(j)->nHits() + mPCV->at(i)->distance(mPCV->at(j)))<=nhits);
				if(cond1 && cond2 && cond3)
				{
					if(mPrintDetail)
						cout<<"Two phi clusters are too close, merge them"<<endl;
					mPCV->at(i)->forceMerge(mPCV->at(j));
					mergecount++;
					if(mFillHisto) mNMergedvTotalCl[3]->Fill(size,mergecount);
					delete mPCV->at(j);
					mPCV->at(j)=NULL;
					newaction=true;
				}
			}
		}
	}
	purgePhiClusters();
}

void StEmcPointMaker::purgePhiClusters()
{
	if(!mPCV)
		return;
	vector<StEmcPhiHitsCluster*>::iterator iter;
	for(iter=mPCV->begin();iter!=mPCV->end();iter++)
	{
		if(!(*iter))
		{
			mPCV->erase(iter);
			iter--;
		}
	}
}

bool StEmcPointMaker::clusterPhiStrips(StSPtrVecEmcRawHit& phits, float seed, float add, bool multi)
{
	if(mPrintDetail) 
	{
		cout<<"\t\tCluster Phi strips, Seed = "<<seed<<" Add = "<<add<<endl;
	}
	if(add<0 || seed<0) return false;
	if(!mPCV) mPCV=new vector<StEmcPhiHitsCluster*>;
	mPCV->clear();
	if((unsigned int)mEnergy[3]->GetSize()!=phits.size()) return false;
	int n=mEnergy[3]->GetSize();
	if(n==0) return false;

	int clusteredhits = 0;
	vector<int> dist;
	dist.clear();
	TTableSorter index(mEnergy[3]->GetArray(),n);
	if(seed==999 && add==999)
	{
		int j=index.GetIndex(n-1);
		if(mPCV->size()==0 && mEnergy[3]->At(j))
		{
			StEmcPhiHitsCluster *c=new StEmcPhiHitsCluster();
			c->addHit(phits[j],1.0);
			mPCV->push_back(c);
			return true; 
		}
	}
	for(int i=n-1;i>=0;i--)
	{
		int ncluster = 0;
		int j=index.GetIndex(i);
		if(mEnergy[3]->At(j)<add) break;
		if(mPrintDetail)
			cout<<"\t\t"<<"Clustering hit: "<<j+1<<" with E="<<mEnergy[3]->At(j)<<" -> "<<endl;
		float etot=0;
		bool cancluster=false;
		dist.resize(mPCV->size());
		for(unsigned int cl=0;cl<mPCV->size();cl++)
		{
			if(mPrintDetail)
			{
				cout<<"\t\t"<<"Testing it on existed cluster(s):";
				mPCV->at(cl)->print();
			}
			dist[cl]=mPCV->at(cl)->distance(phits[j]);
			if(dist[cl]==0)
			{
				if(mPrintDetail)
					cout<<"\t\t"<<"Can Cluster!"<<endl;
				etot+=mPCV->at(cl)->energy();
				cancluster=true;
			}
			else
				if(mPrintDetail)
					cout<<"\t\t"<<"Can't Cluster!"<<endl;
		}
		if(cancluster)
		{
			for(unsigned int cl=0;cl<mPCV->size();cl++)
			{
				if(dist[cl]==0)
				{
					mPCV->at(cl)->addHit(phits[j],mPCV->at(cl)->energy()/etot);
					(*mUsed[3])[j]=1;
					clusteredhits++;
					ncluster++;
				}
			}
		}
		else
		{
			if(mEnergy[3]->At(j)>seed && !mUsed[3]->At(j))
			{
				if(mPrintDetail)
					cout<<"\t\t"<<"Not belonging to any existed cluster, create a new cluster..."<<endl;
				StEmcPhiHitsCluster *c=new StEmcPhiHitsCluster();
				c->addHit(phits[j],1.0);
				(*mUsed[3])[j]=1;
				clusteredhits++;
				ncluster++;
				mPCV->push_back(c);
			}
			/*
			else
				for(unsigned int cl=0;cl<mPCV->size();cl++)
				{
					if(dist[cl]==1)
					{
						mPCV->at(cl)->addHit(phits[j],1.0);
						used[j]=1;
						break;
					}
				}
				*/
		}
		if(mFillHisto) mNClusterPerHit[3]->Fill(ncluster);
	}
	//if(mFillHisto) mFracOfClusteredHits[3]->Fill((float)clusteredhits/n);
	if(multi)
	{
		bool coin=false;
		for(unsigned int i=0;i<mPCV->size();i++)
		{
			if(!mPCV->at(i))
				continue;
			for(unsigned int j=i+1;j<mPCV->size();j++)
			{
				if(!mPCV->at(j))
					continue;
				bool etacond=fabs(mPCV->at(i)->eta() - mPCV->at(j)->eta())<0.15;
				bool phicond=fabs(mPCV->at(i)->phi() - mPCV->at(j)->phi())<(2*TMath::Pi()/60/15);
				if(etacond && phicond)
				{
					if(mPrintDetail)
						cout<<"\t\tTwo phi clusters have close phi, merge them"<<endl;
					mPCV->at(i)->forceMerge(mPCV->at(j));
					delete mPCV->at(j);
					mPCV->at(j)=NULL;
					coin=true;
				}
			}
		}
		purgePhiClusters();

		if(!coin && mECV)
		{
			for(unsigned int eci=0;eci<mECV->size();eci++)
			{
				int sp=mECV->at(eci)->patchMin();
				int bp=mECV->at(eci)->patchMax();
				if(sp==bp)
					continue;
				TArrayF etemp;
				etemp.Set(15);
				etemp.Reset();
				for(int i=0;i<n;i++)
				{
					if((mEtaBin[3]->At(i)==sp || mEtaBin[3]->At(i)==bp) && !mUsed[3]->At(i))
						etemp[mSub[3]->At(i)-1]+=mEnergy[3]->At(i);
				}
				TTableSorter index(etemp.GetArray(),15);	
				if(etemp[index.GetIndex(14)]<seed) continue;
				StEmcPhiHitsCluster* boundary=new StEmcPhiHitsCluster();
				for(int j=index.GetIndex(14);j>=0;j--)
				{
					if(etemp[j]<add) break;
					for(int k=0;k<n;k++)
						if((mEtaBin[3]->At(k)==sp || mEtaBin[3]->At(k)==bp) && !mUsed[3]->At(k) && mSub[3]->At(k)==j+1)
						{
							boundary->addHit(phits[k],1.0);
							(*mUsed[3])[k]=1;
						}
				}
				for(int j=index.GetIndex(14);j<15;j++)
				{
					if(etemp[j]<add) break;
					for(int k=0;k<n;k++)
						if((mEtaBin[3]->At(k)==sp || mEtaBin[3]->At(k)==bp) && !mUsed[3]->At(k) && mSub[3]->At(k)==j+1)
						{
							boundary->addHit(phits[k],1.0);
							(*mUsed[3])[k]=1;
						}
				}
				mPCV->push_back(boundary);
			}
		}
	}

	if(mPrintDetail)
	{
		cout<<"\t\tPhi clustering finished"<<endl;
		for(unsigned int pci=0;pci<mPCV->size();pci++)
		{
			cout<<"\t\t";
			mPCV->at(pci)->print();
			cout<<endl;
		}
		cout<<endl<<endl<<endl;
	}
	return true;
}

bool StEmcPointMaker::maskPhiStrips(StSPtrVecEmcRawHit& phits, bool& multi)
{
	if(!mTowerCluster) return false;
	if(mTowerCluster->nHits()==0) return false;
	unsigned int m=phits.size();
	int mod=mTowerCluster->module();
	float phimin=mTowerCluster->localPhiMin();
	float phimax=mTowerCluster->localPhiMax();

	int patchmin=1000;
	int patchmax=-1000;
	if(mECV && mECV->size()>0)
	{
		for(unsigned int eci=0;eci<mECV->size();eci++)
		{
			patchmin=min(mECV->at(eci)->patchMin(),patchmin);
			patchmax=max(mECV->at(eci)->patchMax(),patchmax);
		}
	}
	else
	{
		patchmin=mTowerCluster->patchMin();
		patchmax=mTowerCluster->patchMax();
	}
	if(patchmin!=patchmax)
		multi=true;
	if(mPrintDetail)
	{
		cout<<"\t\tTower cluster and Eta cluster(s) require "<<phimin<<"<=phi(local)<="<<phimax<<" and "<<patchmin<<"<=patch<="<<patchmax<<endl;
		cout<<"\t\t"<<m<<" phi hit(s) in module "<<mod<<endl;
	}
	mEnergy[3]->Set(m);
	mEtaBin[3]->Set(m);
	mSub[3]->Set(m);
	mUsed[3]->Set(m);
	mEnergy[3]->Reset();
	mEtaBin[3]->Reset();
	mSub[3]->Reset();
	mUsed[3]->Reset();

	int nphits = 0;
	for(unsigned int i=0;i<m;i++)
	{
		Int_t statuscode;
		Int_t id = phits[i]->softId(4);
	//	int m, e, s, id;
	//	phits[i]->modEtaSub(m,e,s);
	//	mGeo[3]->getId(m,e,s,id);
		mTables->getStatus(4,id,statuscode);
		Bool_t status = statuscode==1 || statuscode==3 || statuscode==0 || statuscode==7 || statuscode==8;

		(*mEtaBin[3])[i]=phits[i]->eta();
		(*mSub[3])[i]=abs(phits[i]->sub());
		if(mPrintDetail)
			cout<<"\t\t"<<"eta bin "<<setw(2)<<mEtaBin[3]->At(i)<<" :: phi bin "<<setw(2)<<mSub[3]->At(i)<<" :: id "<<setw(6)<<id;
		float phi,localphi,modulephi;
		mGeo[3]->getPhi(mod,mSub[3]->At(i),phi);
		mGeo[3]->getPhiModule(mod,modulephi);
		localphi=phi-modulephi;
		if(mod<=60)
			localphi=-localphi;
		if(mPrintDetail)
			cout<<" :: phi(local) "<<setw(6)<<localphi<<" :: energy "<<setw(6)<<phits[i]->energy()<<" :: status " <<setw(3)<<statuscode<<endl;
		if(phimin<=localphi && localphi<=phimax && patchmin<=mEtaBin[3]->At(i) && mEtaBin[3]->At(i)<=patchmax && fabs(phits[i]->energy())>0.000000001 && phits[i]->calibrationType()<128 && status)
		{
			(*mEnergy[3])[i]=phits[i]->energy();
			nphits++;
		}
		else
			(*mEnergy[3])[i]=-999;
	}
	if(mPrintDetail)
		cout<<"\t\t"<<nphits<<" Phi hit(s) below the tower and eta clusters"<<endl;
	if(mFillHisto && mNPhiStripsBelow)
		mNPhiStripsBelow->Fill(nphits);

	return true;
}


int StEmcPointMaker::associateTracksWithEmcPoints()
{
	//    What it does:
	// 1. Runs through all "good" global tracks. Each track is projected on BEMC using
	//    StEmcPosition::trackOnEmc(&pos, &mom, track, BFIELD);
	// 2. Finds corresponding emc point
	// 3. If such point exists, adds pointer to this track to the
	//    vector of tracks StPtrVecTrack (data member of StEmcPoint)

	if(!mEmcCol) return kStWarn;
	StSPtrVecEmcPoint& bEmcPoints = mEmcCol->barrelPoints();
	if(bEmcPoints.size() == 0)
	{
		if(mPrint) cout << "***** No BEMC points found" << endl;
		return kStOk;
	}
	Double_t bFld;
	StEventSummary* summary = mEvent->summary();
	if(summary)
	{
		bFld = summary->magneticField()/10.; // bFld in Tesla
		if(mPrint) cout << "StEvent::summary()->magneticField() = "
		<< bFld << "(Tesla)" << endl;
	}
	if(fabs(bFld) < 0.01)
	{
		return kStWarn;
	}
	Int_t mod=0, eta=0, sub=0;
	StEmcPosition* pos = new StEmcPosition();
	StThreeVectorD position, momentum;
	StSPtrVecTrackNode& trackNodes = mEvent->trackNodes();
	StTrack* track;
	StEmcGeom* emcGeom = StEmcGeom::getEmcGeom("bemc");
	int ntrks=0;
	int associated=0;
	for (size_t nodeIndex = 0; nodeIndex < trackNodes.size(); nodeIndex++)
	{
		size_t numberOfTracksInNode =  trackNodes[nodeIndex]->entries(global);
		for (size_t trackIndex = 0; trackIndex < numberOfTracksInNode; trackIndex++)
		{
			ntrks++;
			track = trackNodes[nodeIndex]->track(global,trackIndex);
			if (track && track->flag() >= 0)
			{
				Bool_t ok = pos->trackOnEmc(&position, &momentum, track, bFld); // bFld in Tesla
				if(!ok) continue;
				if(emcGeom->getBin(position.phi(), position.pseudoRapidity(), mod, eta, sub)==0 && sub!=-1)
				{
					for(StSPtrVecEmcPointIterator it = bEmcPoints.begin(); it != bEmcPoints.end(); it++)
					{
						StPtrVecEmcCluster bEmcClusters = (*it)->cluster(kBarrelEmcTowerId);
						for(StPtrVecEmcClusterIterator cIter = bEmcClusters.begin(); cIter != bEmcClusters.end(); cIter++)
						{
							StPtrVecEmcRawHit& bEmcHits = (*cIter)->hit();
							for(StPtrVecEmcRawHitIterator hIter = bEmcHits.begin(); hIter != bEmcHits.end(); hIter++)
							{
								if(mod == (Int_t)(*hIter)->module() && eta == (Int_t)(*hIter)->eta() && sub == (Int_t)(*hIter)->sub())
								{
									(*it)->addTrack(track);
									StTpcDedxPidAlgorithm mypid;
									const StParticleDefinition* par=track->pidTraits(mypid);
									if(par) 
									{
										if(mPrint) cout<<par->name()<<" track associated."<<endl;
										if(mAssociatedTrack) mAssociatedTrack->Fill(par->name().c_str(),1);
									}
									else 
									{
										if(mPrint) cout<<"UNKOWN track associated"<<endl;
										if(mAssociatedTrack) mAssociatedTrack->Fill("UNKNOWN",1);
									}
									associated++;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	if(mPrint) cout<<ntrks<<" possible TPC primary tracks, "<<associated<<" of them associate with EMC points"<<endl; 
	delete pos;
	return kStOk;
}
