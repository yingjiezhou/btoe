#ifndef EmcPointMaker
#define EmcPointMaker
#include "StMaker.h"
#include "StEmcTowerHitsCluster.h"
#include "StEmcEtaHitsCluster.h"
#include "StEmcPhiHitsCluster.h"
#include "StEmcPointMakerPar.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include <vector>
class TCanvas;
class TTimer;
class StEmcGeom;
class StEvent;
class StEmcCollection;
class StEmcRawHit;
class StEmcADCtoEMaker;
//class StBemcData;
//class StBemcTables;
class TH1F;
class TH2F;
class TArrayF;
class TArrayI;
class StSPtrVecEmcRawHit;
class StEmcHitsCluster;
class StEmcEtaHitsCluster;
class StEmcPhiHitsCluster;
class StEmcTowerHitsCluster;
class StEmcDetector;
class StEmcClusterCollection;
class StEmcCluster;
class StEmcModule;
//enum clusterMode {AUTOHIGH, AUTONORMAL, AUTOLOW, HIGH, LOW, FORCE};
//enum clusterReturn {NOPOINTER, NOHITS, STRANGE, OK};
class StEmcPointMaker : public StMaker
{
	/*
	private:
		void makeHistograms();
		*/
	protected:
		bool mPrint;
		bool mPrintMem;
		bool mPrintDetail;
		bool mPlot;
		bool mFillHisto;
		bool mAnalyzeModule;
		bool mAutoThreshold;
		int mMaxSMDSeedDist;
		int mMaxSMDBoundaryDist;
		int mMaxSMDCombinedNHits;
		int mMergeFlavor; //"1" favors 1:2:2 situation
		int mShareFlavor; //"1" divide energy by 2 for 1:2:2 situation
		TMemStat* mMem;
		StEvent* mEvent;
		StEmcCollection* mEmcCol;
		StEmcDetector* mEmcDet[4];
		StEmcClusterCollection* mEmcClCol[4];
		StEmcCluster* mEmcCl[4];
		StEmcADCtoEMaker* mAdc2E;
	//	StBemcData* mBemcData;
	//	StBemcTables *mTables;
		TCanvas *mCanvas;
		TTimer *mTimer;
		StEmcGeom* mGeo[4];
		emcPtMakerPar_st* mPar[4];
		TArrayF* mEnergy[4];
		TArrayI* mEtaBin[4];
		TArrayI* mSub[4];
		TArrayI* mUsed[4];
		TF1  *mFitFunc;
		TH2F *mHitsInMod[4];
		TH1F *mHitsEnergyInMod[4];

		//QA histograms
		TH2F *mModHitsSigma[4]; //for module hits energy spectra 
		TH2F *mModHitsMean[4];  //for module hits energy spectra
		TH2F *mModClusterThr[4];  //mean+3*sigma, the clustering seed energy threshold for SMD
		TH2F *mModNOKHits[4];	//for # of OK hits in module
		TH2F *mModNRange[4]; 	//total hits energy in module
		TH1F *mModChiNDF[4];	//Chi/NDF distribution over all modules 
		TH1F *mAbnormalMod[4];
		TH1F *mEtaPhiClusterFreqByE; //number of EMC points in each energy bin with both eta and phi clusters 
		TH1F *mEtaClusterFreqByE;    //number of EMC points in each energy bin with eta cluster 
		TH1F *mPhiClusterFreqByE;    //number of EMC points in each energy bin with phi cluster
		TH2F *mPointEta_Phi;    //position distribution of reconstructed EMC points
		TH2F *mPointEWeightedEta_Phi;   //weighted by energies
		TH1F *mEtaPhiClusterFreqByMod;  
		TH1F *mPhiClusterFreqByMod;  
		TH1F *mEtaClusterFreqByMod;  
		TH1F *mPointEnergy;
		TH2F *mSigmaEta_Energy;
		TH2F *mSigmaPhi_Energy;
		TH2F *mNTowerHits_Energy;
		TH2F *mNEtaHits_Energy;
		TH2F *mNPhiHits_Energy;
		TH2F *mEtaTowerECorr;
		TH2F *mPhiTowerECorr;
		TH2F *mEtaPhiECorr;
		TH1F *mNEtaStripsBelow;
		TH1F *mNPhiStripsBelow;
		TH1F *mNEtaClustersBelow;
		TH1F *mNPhiClustersBelow;
		TH1F *mEtaClCrossPatchFreq;
		TH1F *mPhiClCrossPatchFreq;
		TH1F *mAssociatedTrack;
		TH1F *mClosePairMass;
		TH1D *mTally;

		//new QA histograms, added March 2007 --pk 3/13/07
		TH1F *mFracOfClusteredHits[4];
		TH2F *mFracOfClusteredHitsByMod[4];
		TH1F *mNClusterPerHit[4];
		TH2F *mNClustersBelow;
		TH2F *mNDiffPairvNPair;
		TH2F *mNMergedvTotalCl[4];

		StEmcTowerHitsCluster* mTowerCluster;
		StEmcEtaHitsCluster* mEtaCluster;
		StEmcPhiHitsCluster* mPhiCluster;
		vector<StEmcTowerHitsCluster*>* mTCV;
		vector<StEmcEtaHitsCluster*>* mECV;
		vector<StEmcPhiHitsCluster*>* mPCV;
		vector<StEmcEtaHitsCluster*>* mECV_backup;
		vector<StEmcPhiHitsCluster*>* mPCV_backup;
		StEmcModule* mEmcModule[4];

		float mSigma[4];
		float mMean[4];
		float mChiNDF[4];
		float mMax[4];
		int mBin[4];
		unsigned int mNOK[4];
		unsigned int mNRange[4];

	public:
		StEmcPointMaker(const char *name="StEmcPointMaker");
		~StEmcPointMaker();
		int Init();
		int Make();
		void Clear(Option_t *option="");
		bool saveQAHistograms(const char* file);
		//void Clear(const char* opt="");  //not needed default is used
		bool maskTowers(StSPtrVecEmcRawHit&);
		bool maskEtaStrips(StSPtrVecEmcRawHit&);
		bool maskPhiStrips(StSPtrVecEmcRawHit&, bool& multi);
		bool clusterTowers(StSPtrVecEmcRawHit&, float seed, float add);
		bool analyzeTowerHits(StSPtrVecEmcRawHit&);
		void mergeTowerClusters();
		void purgeTowerClusters();
		void backupSMDClusters();
		void recoverSMDClusters();
		bool clusterEtaStrips(StSPtrVecEmcRawHit&, float seed, float add);
		bool analyzeSMDHits(int det, const StSPtrVecEmcRawHit& hits);
		bool clusterPhiStrips(StSPtrVecEmcRawHit&, float seed, float add, bool multi);
		void mergeEtaClusters(int seeddist, int bounddist, int nhits);
		void purgeEtaClusters();
		void mergePhiClusters(int seeddist, int bounddist, int nhits);
		void purgePhiClusters();
		void setTallyHist(TH1D* h)
		{
			mTally=h;
		}
		void setPrint(bool print)
		{
			mPrint=print;
		}
		void setPrintMem(bool print)
		{
			mPrintMem=print;
		}
		void setFillHisto(bool fill)
		{
			mFillHisto=fill;
		}
		void setPrintDetail(bool print)
		{
			mPrintDetail=print;
		}
		void setPlot(bool plot)
		{
			mPlot=plot;
		}
		void setAnalyzeModule(bool a)
		{
			mAnalyzeModule=a;
		}
		void setAutoThreshold(bool a)
		{
			mAutoThreshold=a;
		}
		void setParameters(emcPtMakerPar_st* par,int det);
		void setParameters(emcPtMakerPar_st** par);
		void makePoints();
		void makeOnePoint();
		void mergeSMDClusters();
		void addPoint(float E_ratio);
		void plotHitsByModule(int module);
		bool clearEmc();
		int associateTracksWithEmcPoints();
		friend class StEmcHitsCluster;
		friend class StEmcTowerHitsCluster;
		friend class StEmcEtaHitsCluster;
		friend class StEmcPhiHitsCluster;
		
	ClassDef(StEmcPointMaker,0)
};

#endif
