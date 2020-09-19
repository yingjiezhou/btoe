#include "StEvent/StEventTypes.h"
#include "StEvent/StContainers.h"
#include "StEmcTowerHitsCluster.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/others/emcDetectorName.h"
#include "StEmcPointMaker.h"
ClassImp(StEmcTowerHitsCluster)


StEmcTowerHitsCluster::StEmcTowerHitsCluster()
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
	//geo=StEmcPointMaker::mGeo[0];
	//geo=new StEmcGeom(1);
	geo=StEmcGeom::getEmcGeom(detname[0].Data());
}



bool StEmcTowerHitsCluster::canCluster(StEmcRawHit* hit)
{
	int nsub=hit->sub();
	int neta=hit->eta();
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=hits[i]->sub();
		int eta=hits[i]->eta();
		if(((sub==nsub && abs(eta-neta)<=1) || (eta==neta && abs(sub-nsub)<=1)) && abs(neta-etaBinMin())<=1 && abs(neta-etaBinMax())<=1)
			return true;
	}
	return false;
}

bool StEmcTowerHitsCluster::canCluster(StEmcTowerHitsCluster* cl)
{
	for(unsigned int i=0;i<hits.size();i++){
		int sub=abs(hits[i]->sub());
		int eta=hits[i]->eta();
		for(unsigned int j=0;j<cl->getHits()->size();j++)
		{
			int nsub=abs(cl->getHits()->at(j)->sub());
			int neta=cl->getHits()->at(j)->eta();
			if(((sub==nsub && abs(eta-neta)<=1) || (eta==neta && abs(sub-nsub)<=1)) && abs(neta-etaBinMin())<=1 && abs(neta-etaBinMax())<=1)
				return true;
		}
	}
	return false;
}


/*
   StEmcHitsCluster::~StEmcHitsCluster()
   {
   if(geo)
   delete geo;
}
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
