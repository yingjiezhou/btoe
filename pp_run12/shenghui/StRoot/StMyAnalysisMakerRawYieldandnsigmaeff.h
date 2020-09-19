#ifndef StMyAnalysisMaker_h
#define StMyAnalysisMaker_h
#include "StMaker.h"
#include <vector>
#include <map>
#ifndef ST_NO_NAMESPACES
using std::vector;
#endif
class StPicoDst;
class StPicoTrack;
class StPicoEvent;
class StPicoDstMaker;
class StPicoBEmcPidTraits;
class StPicoEmcTrigger;
class StPicoPhysicalHelix;

class TString;
class TH1F;
class TH2F;
class TH3F;
class TVector3;
class TFile;
#if !defined(ST_NO_TEMPLATE_DEF_ARGS) || defined(__CINT__)
typedef vector<int> IntVec;
typedef vector<Double_t> DoubleVec;
#else
typedef vector<int, allocator<int>> IntVec;
typedef vector<Double_t, allocator<Double_t>> DoubleVec;
#endif
class StMyAnalysisMaker : public StMaker {
	public:
		StMyAnalysisMaker(const char *name, StPicoDstMaker *picoMaker, const char *outName, int trigSelect);
		virtual ~StMyAnalysisMaker();

		bool isHT0_BBCMB_TOF0(StPicoEvent*, IntVec);
		bool isHT2_BBCMB(StPicoEvent*, IntVec);
		bool isGoodPartner(StPicoTrack*);
		bool isGoodTrack(StPicoTrack*);
		bool isEMCTrack(StPicoTrack*, StPicoBEmcPidTraits*);
		bool isSMDTrack(StPicoTrack*, StPicoBEmcPidTraits*);
		bool checkHotTower(int);
		void makerealevent();
		virtual int Init();
		virtual int Make();
		virtual int loopTrack();
		virtual void  Clear(Option_t *opt="");
		virtual int Finish();

		void    DeclareHistograms();
		void    WriteHistograms();

	private:
		StPicoDstMaker *mPicoDstMaker;
		StPicoDst      *mPicoDst;
		StPicoEvent    *event;
		TString    mOutName;
		int  mTrigSelect;

		int   mNBadRuns_HT0;
		int   mNBadRuns_HT2;
		IntVec  mTriggerIDs;

		TFile*   fout;
		float mHTth;
		float mHTAdc0th;
		float mEmcPtth;
		float MassE;
		float VzCut;
		float VzDiff;
		int nFPtsCutPart;
		int nFPtsCut;
		int ndEdxPtsCut;
		float PtsRMin;
		float PtsRMax;
		float minPtCut;
		float dcaCut;
		float TPCFR;
		float EtaCut;
		float PoeMin;
		float PoeMax;
		float DistZ;
		float DistPhi;
		int NEta;
		int NPhi;
		float PairDiffMax;
		float PairDiffMin;
		float CurrentEvent_bField;
		int   CurrentEvent_nEs;
		int   CurrentEvent_nEMCE;
		int      CurrentEvent_EId[2000];
		int      CurrentEvent_ECharge[2000];
		//float    CurrentEvent_ENhitsFit[2000];
		//float    CurrentEvent_ENSigE[2000];
		//float    CurrentEvent_ETofBeta[2000];
		//float    CurrentEvent_EGpTPartner[2000];
		//float    CurrentEvent_EPt[2000];
		//float    CurrentEvent_EEta[2000];
		//float    CurrentEvent_EPhi[2000];
		float    CurrentEvent_EHelixPx[2000];
		float    CurrentEvent_EHelixPy[2000];
		float    CurrentEvent_EHelixPz[2000];
		float    CurrentEvent_EHelixX[2000];
		float    CurrentEvent_EHelixY[2000];
		float    CurrentEvent_EHelixZ[2000];
		//float    CurrentEvent_ETOWE[2000];
		//int      CurrentEvent_ETOWId[2000];

		int      CurrentEvent_EMCEId[2000];
		int      CurrentEvent_EMCECharge[2000];
		//float    CurrentEvent_EMCENhitsFit[2000];
		//int      CurrentEvent_EMCENhitsDedx[2000];
		//float    CurrentEvent_EMCEDca[1000];
		//float    CurrentEvent_EMCENSigE[1000];
		//float    CurrentEvent_EMCETofMatchFlag[2000];
		//float    CurrentEvent_EMCETofYLocal[2000];
		float    CurrentEvent_EMCEPt[2000];
		//float    CurrentEvent_EMCEEta[2000];
		//float    CurrentEvent_EMCEPhi[2000];
		float    CurrentEvent_EMCEHelixPx[2000];
		float    CurrentEvent_EMCEHelixPy[2000];
		float    CurrentEvent_EMCEHelixPz[2000];
		float    CurrentEvent_EMCEHelixX[2000];
		float    CurrentEvent_EMCEHelixY[2000];
		float    CurrentEvent_EMCEHelixZ[2000];
		//float    CurrentEvent_EMCETofBeta[2000];
		//float    CurrentEvent_EMCEdEdx[2000];
		//float    CurrentEvent_EMCETOWE[2000];
		float    CurrentEvent_EMCETOWpovere[2000];
		float    CurrentEvent_EMCEDistZ[2000];
		float    CurrentEvent_EMCEDistPhi[2000];
		int      CurrentEvent_EMCESMDNEta[2000];
		int      CurrentEvent_EMCESMDNPhi[2000];
		int      CurrentEvent_EMCEDsmADC[2000];
		int      CurrentEvent_EMCEADC0[2000];
		float    CurrentEvent_EMCENSigE[2000];
		//int      CurrentEvent_EMCETOWId[2000];

		TH1F *hnEvent;
		TH2F *hVpdVz;
		TH2F *hVpdVzcut;
		TH1F *hVzDiff;
		//TH1F *hVzDiffGood;
		//TH2F *hBTOWERid;
		TH1F *hBTOWERid;
		TH2F *hAdc0;
		TH2F *hdsmAdc;
		TH2F *hAdc0vsdsmAdc;
		TH2F *hAdc0Cut;
		TH2F *hdsmAdcCut;
		TH2F *hAdc0vsdsmAdcCut;
		TH2F *hNSigEEMC;
		TH2F *hNSigEPtEMC;
		TH2F *hNSigE;
		TH2F *hNSigEPt;
		TH2F *hnE;
		TH2F *hmvsptEMC;
		TH2F *hmvsptEMClike;
		TH2F *hmvspt;
		TH2F *hmvsptlike;
		TH2F *hNSigEeff;
		TH2F *hNSigEeffCut;
		TH2F *hNSigEeffTight;
		TH2F *hNSigEeffCutTight;
		TH2F *hNSigEeffVeryTight;
		TH2F *hNSigEeffCutVeryTight;
		TH1F *hTPCtracksTrigger;
		TH1F *hSMDtracks;
		TH2F *hAdc0PHE;
		TH2F *hdsmAdcPHE;
		TH2F *hAdc0vsdsmAdcPHE;
		TH2F *hNSigEefflike;
		TH2F *hNSigEeffCutlike;
		TH2F *hNSigEeffTightlike;
		TH2F *hNSigEeffCutTightlike;
		TH2F *hNSigEeffVeryTightlike;
		TH2F *hNSigEeffCutVeryTightlike;
		TH1F *hTPCtracksTriggerlike;
		TH1F *hSMDtrackslike;
		TH2F *hAdc0PHElike;
		TH2F *hdsmAdcPHElike;
		TH2F *hAdc0vsdsmAdcPHElike;

		ClassDef(StMyAnalysisMaker, 1)
};
#endif
