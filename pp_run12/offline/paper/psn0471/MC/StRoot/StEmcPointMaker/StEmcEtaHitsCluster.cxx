#include "StEvent/StEventTypes.h"
#include "StEvent/StContainers.h"
#include "StEmcEtaHitsCluster.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/others/emcDetectorName.h"
//#include "StEmcPointMaker.h"
ClassImp(StEmcEtaHitsCluster)


StEmcEtaHitsCluster::StEmcEtaHitsCluster()
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
	//geo=new StEmcGeom(3);
	//geo=StEmcPointMaker::mGeo[2];
	mSeedNSigma=0;
	mAddonNSigma=0;
	geo=StEmcGeom::getEmcGeom(detname[2].Data());
}

//returns smallest eta distance; 0 if adjacent to hit in cluster
int StEmcEtaHitsCluster::distance(StEmcRawHit* hit)
{
	int d=999;
	int nsub=hit->sub();
	int neta=hit->eta();
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=hits[i]->sub();
		int eta=hits[i]->eta();
		if(sub!=nsub)
			return 999;
		if(abs(neta-eta)-1<d)
			d=abs(neta-eta)-1;
	}
	return d;
}

//returns smallest distance between eta strips of clusters' hits
int StEmcEtaHitsCluster::distance(StEmcEtaHitsCluster* cl)
{
	int d=999;
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=hits[i]->sub();
		int eta=hits[i]->eta();
		for(unsigned int j=0;j<cl->getHits()->size();j++)
		{
			int nsub=cl->getHits()->at(j)->sub();
			int neta=cl->getHits()->at(j)->eta();
			if(sub!=nsub)
				return 999;
			if(abs(neta-eta)-1<d)
				d=abs(neta-eta)-1;
		}
	}
	return d;
}

int StEmcEtaHitsCluster::seedDistance(StEmcEtaHitsCluster* cl)
{
	int d=999;
	int etabin1=cl->getHits()->at(0)->eta();		//first hit is always seed
	int etabin2=hits[0]->eta();
	int sub1=cl->getHits()->at(0)->sub();
	int sub2=hits[0]->sub();
	if(sub1!=sub2)
		return 999;
	d=abs(etabin1-etabin2)-1;
	return d;
}

float StEmcEtaHitsCluster::eta()				//calculate cluster's eta, weighted by E
{
	float eta=0;
	float sumw=0;
	int mod=hits[0]->module();
	float etai;
	float wi;
	for(unsigned int i=0;i<hits.size();i++)
	{
		geo->getEta(mod,hits[i]->eta(),etai);
		wi=2+log(hits[i]->energy()*weights[i]/energy());
		if(wi<0) wi=0;
		sumw+=wi;
		eta+=etai*wi;
	}
	eta=eta/sumw;
	return eta;
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

float StEmcHitsCluster::phi()
{
	float phi;
	int mod=hits[0]->module();
	for(unsigned int i=0;i<hits.size();i++)
	{
		float phii;
		geo->getPhi(mod,hits[i]->sub(),phii);
		phi+=phii*hits[i]->energy()*weights[i];
	}
	phi=phi/energy();
	return phi;
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

