#include "StEvent/StEventTypes.h"
#include "StEvent/StContainers.h"
#include "StEmcPhiHitsCluster.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/others/StEmcMath.h"
#include "StEmcUtil/others/emcDetectorName.h"
//#include "StEmcPointMaker.h"
ClassImp(StEmcPhiHitsCluster)
StEmcPhiHitsCluster::StEmcPhiHitsCluster()
{
	/*
	int i;
	if(!strcmp(cdet,"bemc")) 
		i=1;
	else if(!strcmp(cdet,"bsmde"))
		i=3;
	else if(!strcmp(cdet,"bsmdp"))
		i=4;
	else
		cout<<"No such a thing"<<endl;
	det=i;
	*/
	//geo=StEmcPointMaker::mGeo[3];
	//geo=new StEmcGeom(4);
	mSeedNSigma=0;
	mAddonNSigma=0;
	geo=StEmcGeom::getEmcGeom(detname[3].Data());
}

/*
StEmcHitsCluster::~StEmcHitsCluster()
{
	if(geo)
		delete geo;
}*/

//can cluster if hit is adjacent in phi to a cluster hit; hits have to be in the same eta segment of smdp module
bool StEmcPhiHitsCluster::canCluster(StEmcRawHit* hit)
{
	if(!hit)
		return false;
	int nsub=hit->sub();
	int neta=hit->eta();
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=hits[i]->sub();
		int eta=hits[i]->eta();
		if(eta==neta && abs(sub-nsub)<=1)
			return true;
	}
	return false;
}

//can cluster if cl has a hit adjacent in phi to a cluster hit; hits have to be in the same eta segment of smdp module
bool StEmcPhiHitsCluster::canCluster(StEmcPhiHitsCluster* cl)
{
	if(!cl)
		return false;
	for(unsigned int i=0;i<hits.size();i++){
		int sub=hits[i]->sub();
		int eta=hits[i]->eta();
		for(unsigned int j=0;j<cl->getHits()->size();j++)
		{
			int nsub=cl->getHits()->at(j)->sub();
			int neta=cl->getHits()->at(j)->eta();
			if(eta==neta && abs(sub-nsub)<=1)
				return true;
		}
	}
	return false;
}

//only returns distance in phi; 999 if different eta bins on smdp
int StEmcPhiHitsCluster::seedDistance(StEmcPhiHitsCluster* cl)
{
	if(!cl)
		return false;
	int d=999;
	int etabin1=cl->getHits()->at(0)->eta();
	int etabin2=hits[0]->eta();
	int sub1=cl->getHits()->at(0)->sub();
	int sub2=hits[0]->sub();
	if(etabin1!=etabin2)
		return 999;
	d=abs(sub1-sub2)-1;
	return d;
}

//only returns distance in phi; 999 if different eta bins on smdp
int StEmcPhiHitsCluster::distance(StEmcPhiHitsCluster* cl)
{
	if(!cl)
		return false;
	int d=999;
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=hits[i]->sub();
		int eta=hits[i]->eta();
		for(unsigned int j=0;j<cl->getHits()->size();j++)
		{
			int nsub=cl->getHits()->at(j)->sub();
			int neta=cl->getHits()->at(j)->eta();
			if(eta!=neta)
				return 999;
			if(abs(nsub-sub)-1<d)
				d=abs(nsub-sub)-1;
		}
	}
	return d;
}


//only returns distance in phi; 999 if different eta bins on smdp
int StEmcPhiHitsCluster::distance(StEmcRawHit* hit)
{
	if(!hit)
		return false;
	int d=999;
	int nsub=hit->sub();
	int neta=hit->eta();
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=hits[i]->sub();
		int eta=hits[i]->eta();
		if(eta!=neta)
			return 999;
		if(abs(nsub-sub)-1<d)
			d=abs(nsub-sub)-1;
	}
	return d;
}

//calculates energy weighted cluster's phi, using seed phi as temporary 'origin'
float StEmcPhiHitsCluster::phi()
{
	float phi=0;
	float sumw=0;
	int mod=hits[0]->module();
	float phi0;
	geo->getPhi(mod,abs(hits[0]->sub()),phi0);
	float phii;
	float wi;
	for(unsigned int i=0;i<hits.size();i++)
	{
		geo->getPhi(mod,abs(hits[i]->sub()),phii);
		phii -= phi0;
		phii = StEmcMath::getPhiPlusMinusPi(phii);
		wi=2+log(hits[i]->energy()*weights[i]/energy());
		if(wi<0) wi=0;
		sumw+=wi;
		phi+=phii*wi;
	}
	phi=phi/sumw;
	phi += phi0;
	phi = StEmcMath::getPhiPlusMinusPi(phi);
	return phi;
}

/*
   void StEmcHitsCluster::print()
   {
   for(unsigned int i=0;i<hits.size();i++)
   {
   cout<<"SUB:"<<setw(2)<<hits[i]->sub()<<" ETA:"<<setw(3)<<hits[i]->eta()<<" E:"<<setw(8)<<setprecision(3)<<hits[i]->energy()<<" W:"<<setw(8)<<setprecision(3)<<weights[i]<<endl;
	}
}
		
void StEmcHitsCluster::addHit(StEmcRawHit* hit, float weight)
{
	hits.push_back(hit);
	weights.push_back(weight);
}

float StEmcHitsCluster::energy()
{
	float e;
	for(unsigned int i=0;i<hits.size();i++)
	{
		e+=hits[i]->energy()*weights[i];
	}
	return e;
}

float StEmcHitsCluster::eta()
{
	float eta;
	int mod=hits[0]->module();
	for(unsigned int i=0;i<hits.size();i++)
	{
		float etai;
		geo->getEta(mod,hits[i]->eta(),etai);
		eta+=etai*hits[i]->energy()*weights[i];
	}
	eta=eta/energy();
	return eta;
}


float StEmcHitsCluster::etaMin()
{
	float min=100.0;
	int mod=hits[0]->module();
	for(unsigned int i=0;i<hits.size();i++)
	{
		float etai;
		geo->getEta(mod,hits[i]->eta(),etai);
		if(etai<min)
			min=etai;
	}
	return min;
}

float StEmcHitsCluster::etaMax()
{
	float max=-100.0;
	int mod=hits[0]->module();
	for(unsigned int i=0;i<hits.size();i++)
	{
		float etai;
		geo->getEta(mod,hits[i]->eta(),etai);
		if(etai>max)
			max=etai;
	}
	return max;
}
*/

