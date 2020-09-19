#ifndef STEMCETAHITSCLUSTER
#define STEMCETAHITSCLUSTER
#include <vector>
#include "StEmcHitsCluster.h"
using std::vector;

class StEmcGeom;
class StEmcRawHit;
class StEmcEtaHitsCluster:public StEmcHitsCluster
{
	protected:
		/*
		vector<StEmcRawHit*> hits;
		vector<float> weights;
		StEmcGeom* geo;
		int det;
		*/
	public:
		StEmcEtaHitsCluster();
		int distance(StEmcRawHit*);
		int distance(StEmcEtaHitsCluster*);
		int seedDistance(StEmcEtaHitsCluster*);
		float eta();
		/*
		~StEmcEtaHitsCluster();
		bool canCluster(StEmcRawHit*);
		float phi();
		float energy();
		void addHit(StEmcRawHit*, float);
		void print();
		vector<StEmcRawHit*>* getHits() {return &hits;}
		*/

	ClassDef(StEmcEtaHitsCluster,0)  
};
#endif
