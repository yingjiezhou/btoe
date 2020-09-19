#ifndef StMyAnalysisMaker_h
#define StMyAnalysisMaker_h
#include "StMaker.h"
#include <vector>
#include <map>
#ifndef ST_NO_NAMESPACES
using std::vector;
#endif
class StPicoDst;
class StPicoEvent;
class StPicoDstMaker;
class prescales;

class TString;
class TH1F;
class TH2F;
class TH3F;
class TFile;
class StMyAnalysisMaker : public StMaker {
	public:
		//StMyAnalysisMaker(const char *name, StPicoDstMaker *picoMaker, const char *outName, int trigSelect);
		StMyAnalysisMaker(const char *name, StPicoDstMaker *picoMaker, const char *outName);
		virtual ~StMyAnalysisMaker();

		Bool_t isBBCMB_TOF0(StPicoEvent*);
		Bool_t isHT0_BBCMB_TOF0(StPicoEvent*);
		Bool_t isHT2_BBCMB(StPicoEvent*);
		Bool_t isBBCMB(StPicoEvent*);
		virtual Int_t Init();
		virtual Int_t Make();
		virtual void  Clear(Option_t *opt="");
		virtual Int_t Finish();

		void    DeclareHistograms();
		void    WriteHistograms();



	private:
		StPicoDstMaker *mPicoDstMaker;
		StPicoDst      *mPicoDst;
		prescales *mPrescales ;
		//StPicoPrescales *mPrescales;
		TString    mOutName;
		//Int_t  mTrigSelect;

		Int_t   mNBadRuns_HT;
		//Int_t   mNBadRuns_HT0;
		//Int_t   mNBadRuns_HT2;

		TFile*	   fout;

		TH1F *hnEvent;
		TH1F *hVzBBCMB_TOF0;
		TH1F *hVzHT0_BBCMB_TOF0;
		TH1F *hVzBBCMB;
		TH1F *hVzHT2_BBCMB;
		TH1F *hVzBBCMB_TOF0_R;
		TH1F *hVzHT0_BBCMB_TOF0_R;
		TH1F *hVzBBCMB_R;
		TH1F *hVzHT2_BBCMB_R;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_All;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_scale_All;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_scale;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_All_R;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_scale_All_R;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_R;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_scale_R;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_All;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_All_R;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_R;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_R;
		TH1F *mTotalBBCMB_forBHT2_EventsInRun_All;
		TH1F *mTotalBBCMB_forBHT2_EventsInRun_scale_All;
		TH1F *mTotalBBCMB_forBHT2_EventsInRun;
		TH1F *mTotalBBCMB_forBHT2_EventsInRun_scale;
		TH1F *mTotalBBCMB_forBHT2_EventsInRun_All_R;
		TH1F *mTotalBBCMB_forBHT2_EventsInRun_scale_All_R;
		TH1F *mTotalBBCMB_forBHT2_EventsInRun_R;
		TH1F *mTotalBBCMB_forBHT2_EventsInRun_scale_R;
		TH1F *mTotalBBCMBBHT2_forBHT2_EventsInRun_All;
		TH1F *mTotalBBCMBBHT2_forBHT2_EventsInRun_scale_All;
		TH1F *mTotalBBCMBBHT2_forBHT2_EventsInRun;
		TH1F *mTotalBBCMBBHT2_forBHT2_EventsInRun_All_R;
		TH1F *mTotalBBCMBBHT2_forBHT2_EventsInRun_scale_All_R;
		TH1F *mTotalBBCMBBHT2_forBHT2_EventsInRun_R;

		TH1F *hVzBBCMB_TOF0_BBCMB;
		TH1F *hVzHT0_BBCMB_TOF0_BBCMB;
		TH1F *hVzBBCMB_TOF0_R_BBCMB;
		TH1F *hVzHT0_BBCMB_TOF0_R_BBCMB;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_All_BBCMB;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_scale_All_BBCMB;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_BBCMB;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_scale_BBCMB;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_All_R_BBCMB;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_scale_All_R_BBCMB;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_R_BBCMB;
		TH1F *mTotalBBCMB_forBHT0_EventsInRun_scale_R_BBCMB;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_All_BBCMB;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_BBCMB;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_BBCMB;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_All_R_BBCMB;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_scale_All_R_BBCMB;
		TH1F *mTotalBBCMBBHT0_forBHT0_EventsInRun_R_BBCMB;
		ClassDef(StMyAnalysisMaker, 1)
};
#endif
