#ifndef STEMCPHIHITSCLUSTER
#define STEMCPHIHITSCLUSTER
#include <vector>
#include "StEmcHitsCluster.h"
using std::vector;

class StEmcGeom;
class StEmcRawHit;
class StEmcPhiHitsCluster:public StEmcHitsCluster
{
	protected:
		/*
		vector<StEmcRawHit*> hits;
		vector<float> weights;
		StEmcGeom* geo;
		int det;
		*/
	public:
		StEmcPhiHitsCluster();
		//~StEmcPhiHitsCluster();
		bool canCluster(StEmcRawHit*);
		bool canCluster(StEmcPhiHitsCluster*);
		int distance(StEmcRawHit*);
		int distance(StEmcPhiHitsCluster*);
		int seedDistance(StEmcPhiHitsCluster*);
		float phi();
		/*
		float eta();
		float energy();
		void addHit(StEmcRawHit*, float);
		void print();
		vector<StEmcRawHit*>* getHits() {return &hits;}
		*/

	ClassDef(StEmcPhiHitsCluster,0)  
};
#endif
