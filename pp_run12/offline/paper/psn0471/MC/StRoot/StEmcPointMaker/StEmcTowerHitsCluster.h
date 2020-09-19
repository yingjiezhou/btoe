#ifndef STEMCTOWERHITSCLUSTER
#define STEMCTOWERHITSCLUSTER
#include <vector>
#include "StEmcHitsCluster.h"
using std::vector;

class StEmcGeom;
class StEmcRawHit;
class StEmcTowerHitsCluster:public StEmcHitsCluster
{
	protected:
		/*
		vector<StEmcRawHit*> hits;
		vector<float> weights;
		StEmcGeom* geo;
		int det;
		*/
	public:
		StEmcTowerHitsCluster();
		bool canCluster(StEmcRawHit*);
		bool canCluster(StEmcTowerHitsCluster*);
		/*
		~StEmcTowerHitsCluster();
		float eta();
		float phi();
		float energy();
		void addHit(StEmcRawHit*, float);
		void print();
		vector<StEmcRawHit*>* getHits() {return &hits;}
		*/

	ClassDef(StEmcTowerHitsCluster,0)  
};
#endif
