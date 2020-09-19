#ifndef __EHANA_H__
#define __EHANA_H__

//binning for NPE v2 analysis (same as in Au+Au)
const unsigned int npt = 12;
const float pt_xbin[npt+1] = {0., 0.2, 0.5, 0.75, 1.0, 1.25, 1.5,1.75, 2.0, 4.0, 6.0, 8.0, 10.0};

// finer binning for comparision with Npe-hadron p+p data run 5 and 6
//const unsigned int npt = 14;
//const float pt_xbin[npt+1] = {0., 0.2, 0.5, 0.75, 1.0, 1.25, 1.5,1.75, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5};

const float pT_min = 0.0;
const float pT_max = 5.0;
const int neta = 20;
const float eta_min = -1.2;
const float eta_max = 1.2;

class TH1F;
class TH2F;
class TGraph;
class TRandom;
class TParticleHj;

class NpeFlow {
	private:
		TH1F* pt_ele;
	    TH1F* pt_had;
	    TH1F* pt_K;
	    TH1F* pt_pi;
	    TH1F* pt_p;

		TH1F* eta_ele;
	    TH1F* eta_had;
	    TH1F* eta_K;
	    TH1F* eta_pi;
	    TH1F* eta_p;

	    TH1F* ele_parent;
	    TH1F* had_parent;

		TH1F* hEvenCounter;

		float pT_cut; //.. acceptance cuts
		float eta_cut; //
		float eta_ele_cut; //	
		float pTtrigger;
	
	
		const char* outFileName;
		const char* mTrgEffFileName;
		const char* mKaonRecoEffFileName;
		const char* mPionRecoEffFileName;
		const char* mProtonRecoEffFileName;
	
		// v2{2} analysis

		//.. final 2nd moments
	    TH1F* incEle_M2_2part[npt]; //.. inclusive electrons
	    TH1F* refFlow_M2_2part; //.. reference flow
	    TH1F* refFlowTrackMult; //.. reference flow

	    TGraph* mHtTriggerEff;
	    TGraph* mKaonRecoEff;
	    TGraph* mPionRecoEff;
	    TGraph* mProtonRecoEff;
	

	    TRandom* mRandGen;		

	    //.. moments for reference flow
	    float cos2phi_RefFlow;
	    float sin2phi_RefFlow;
	    float multRefFlow;

	    //.. moments for inclusive electrons
	    float inc_ele_cos_2phi_cent_pT_bins[npt];
	    float inc_ele_sin_2phi_cent_pT_bins[npt];
	    float inc_ele_mult_pT_bins[npt];

	    bool anaBottom;
	    bool anaCharm;
	    bool useTriggeredData;
	    bool hasTrigger;


	private:

	    bool acceptedTrack(float pT, float eta, int kf);
	    bool acceptedHtEvent(float elePt);
	    void defineFlowArrays();
	    void deleteFlowArrays();
	    void defineFlowHist();
	    void WriteHist();
	    void Reset();

		void calcRefFlow_M2_2Part();
		void calcEleMoments();
	    int find_pt_bin(float pT);
	    bool isHeavyMesonProd(int kf);

	public:
		NpeFlow();
		~NpeFlow();
		void calculate(int startFile, int endFile, int maxEvent, char *ndstlist);
		void fillPtSpectra(int startFile, int endFile, int maxEvent, char *ndstlist);

		void setTriggerPt(float in);
		void setParentId(int in);
		void setPtCut(float in);
		void setEtaCut(float in);
		void showCuts();
		void setOutFileName(const char* in);
		void setHtTrigEffFileName(const char* in);
		void setKaonRecoEffFileName(const char* in);
		void setPionRecoEffFileName(const char* in);
		void setProtonRecoEffFileName(const char* in);

		void setAnaBottom(bool in);
		void setAnaCharm(bool in);
		bool getAnaBottom();
		bool getAnaCharm();


ClassDef(NpeFlow, 1)
};
#endif /* __EHANA_H__ */
