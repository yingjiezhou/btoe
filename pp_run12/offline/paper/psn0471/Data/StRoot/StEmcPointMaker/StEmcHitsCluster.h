#ifndef STEMCHITSCLUSTER
#define STEMCHITSCLUSTER
#include <vector>
using std::vector;

class StEmcGeom;
class StEmcRawHit;
class StEmcHitsCluster
{
	protected:
		vector<StEmcRawHit*> hits;
		vector<float> weights;
		StEmcGeom* geo;							//initialized by each detector's cluster constructor
		int mSeedNSigma;//in the unit of sigma above mean
		int mAddonNSigma;//in the unit of sigma above mean
		//Int_t flags; 
		/*
		 * 0xXXXX
		 * 0-3 for max number of combined hits for merging process
		 * 4-7 for max boundary distance for merging process 
		 * 8-11 for max seed distance for merging process 
		 * 12-19 for add on threshold in MeV
		 * 20-27 for seed threshold in MeV
		 * 28-29 for add on threshold in unit of sigma above mean
		 * 30-31 for seed threshold in unit of sigma above mean
		 */ 
		//int det;
	public:
		StEmcHitsCluster();
		virtual ~StEmcHitsCluster();
		virtual bool canCluster(StEmcRawHit*);
		virtual bool canCluster(StEmcHitsCluster*);
		virtual bool contain(StEmcRawHit*);
		virtual float eta();
		virtual float sigmaEta();
		virtual float phi();
		virtual float sigmaPhi();
		virtual float energy();
		int module();
		virtual int patchMin();
		virtual int patchMax();
		virtual int nHits() {return hits.size();}
		virtual float absEtaMin();
		virtual float absEtaMax();
		virtual int etaBinMin();
		virtual int etaBinMax();
		virtual float localPhi();
		virtual float localPhiMin();
		virtual float localPhiMax();
		virtual void addHit(StEmcRawHit*, float);
		virtual void addHit(StEmcRawHit*);
		virtual void print();
		vector<StEmcRawHit*>* getHits() {return &hits;}
		vector<float>* getWeights() {return &weights;}
		StEmcHitsCluster* merge(StEmcHitsCluster*);	
		StEmcHitsCluster* forceMerge(StEmcHitsCluster*);	

		friend class StEmcPointMaker;

	ClassDef(StEmcHitsCluster,0)  
};
#endif
