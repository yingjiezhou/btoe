#include "StEvent/StEventTypes.h"
#include "StEvent/StContainers.h"
#include "StEmcHitsCluster.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/others/StEmcMath.h"
//#include "StEmcPointMaker.h"
ClassImp(StEmcHitsCluster)


StEmcHitsCluster::StEmcHitsCluster()
{
	mSeedNSigma=0;
	mAddonNSigma=0;
}

StEmcHitsCluster::~StEmcHitsCluster()
{
}

bool StEmcHitsCluster::canCluster(StEmcRawHit* hit)
{
	int nsub=abs(hit->sub());
	int neta=hit->eta();
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=abs(hits[i]->sub());
		int eta=hits[i]->eta();
		if((sub==nsub && abs(eta-neta)<=1) || (eta==neta) && abs(sub-nsub)<=1)
			return true;
	}
	return false;
}

bool StEmcHitsCluster::canCluster(StEmcHitsCluster* cl)
{
	for(unsigned int i=0;i<hits.size();i++){
		int sub=abs(hits[i]->sub());
		int eta=hits[i]->eta();
		for(unsigned int j=0;j<cl->getHits()->size();j++)
		{
			int nsub=abs(cl->getHits()->at(j)->sub());
			int neta=cl->getHits()->at(j)->eta();
			if((sub==nsub && abs(eta-neta)<=1) || (eta==neta) && abs(sub-nsub)<=1)
				return true;
		}
	}
	return false;
}

bool StEmcHitsCluster::contain(StEmcRawHit* hit)
{
	int nsub=abs(hit->sub());
	int neta=hit->eta();
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=abs(hits[i]->sub());
		int eta=hits[i]->eta();
		if(sub==nsub && eta==neta)
			return true;
	}
	return false;
}

	

void StEmcHitsCluster::print()
{
	cout.setf(ios_base::left,ios_base::adjustfield);
	for(unsigned int i=0;i<hits.size();i++)
	{
//		float etamin, etamax;
//		etamin = (module()<61) ? absEtaMin() : -absEtaMax();			//for east barrel, -- pk 5/8/07
//		etamax = (module()<61) ? absEtaMax() : -absEtaMin();
		cout<<"SUB="<<setw(2)<<abs(hits[i]->sub())<<" ETA="<<setw(3)<<hits[i]->eta()<<" E="<<setw(6)<<setprecision(3)<<hits[i]->energy()<<" W="<<setw(3)<<setprecision(2)<<weights[i]<<";";
	}
//	cout<<" energy="<<energy()<<", eta="<<eta()<<", "<<absEtaMin()<<"<=abs(eta)<="<<absEtaMax()<<", "<<localPhiMin()<<"<=phi(local)<="<<localPhiMax()<<", phi="<<phi();
	cout<<" energy="<<energy()<<", eta="<<eta()<<", "<<absEtaMin()<<"<=abs(eta)<="<<absEtaMax()<<", "<<localPhiMin()<<"<=phi(local)<="<<localPhiMax()<<", phi(local)="<<localPhi();
}

void StEmcHitsCluster::addHit(StEmcRawHit* hit, float weight)
{
	hits.push_back(hit);
	weights.push_back(weight);
}

void StEmcHitsCluster::addHit(StEmcRawHit* hit)
{
	hits.push_back(hit);
	weights.push_back(1.0);
}

StEmcHitsCluster* StEmcHitsCluster::forceMerge(StEmcHitsCluster* canother)
{
	if(!canother)
		return this;
	vector<StEmcRawHit*>* h=canother->getHits();
	vector<float>* w=canother->getWeights();
	for(unsigned int i=0;i<h->size();i++)
		addHit(h->at(i),w->at(i));
	return this;
}

StEmcHitsCluster* StEmcHitsCluster::merge(StEmcHitsCluster* canother)
{
	bool canmerge=false;
	for(unsigned int i=0;i<hits.size();i++)
	{
		if(canother->canCluster(hits[i]))
		{
			canmerge=true;
			break;
		}
	}
	if(!canmerge)
		return NULL;
	return forceMerge(canother);
}


float StEmcHitsCluster::energy()
{
	float e=0;
	for(unsigned int i=0;i<hits.size();i++)
	{
		e+=hits[i]->energy()*weights[i];
	}
	return e;
}

//clusters limited to single module
int StEmcHitsCluster::module()
{
	int m=hits[0]->module();
	return m;
}

float StEmcHitsCluster::eta()
{
	float eta=0;
	int mod=hits[0]->module();
	float etai;
	for(unsigned int i=0;i<hits.size();i++)
	{
		geo->getEta(mod,hits[i]->eta(),etai);
		eta+=etai*hits[i]->energy()*weights[i];
	}
	eta=eta/energy();
	return eta;
}

float StEmcHitsCluster::sigmaEta()
{
	float sigmaeta=0;
	int mod=hits[0]->module();
	float etai;
	for(unsigned int i=0;i<hits.size();i++)
	{
		geo->getEta(mod,hits[i]->eta(),etai);
		sigmaeta+=etai*etai*hits[i]->energy()*weights[i];
	}
	sigmaeta=sigmaeta/energy()-eta()*eta();
	if(sigmaeta<0)
		sigmaeta=0;
	else
		sigmaeta=sqrt(sigmaeta);
	return sigmaeta;
}
	

float StEmcHitsCluster::phi()					//global phi
{
	float phi=0;
	int mod=hits[0]->module();
	float phi0;
	geo->getPhi(mod,abs(hits[0]->sub()),phi0);		
	float phii;
	for(unsigned int i=0;i<hits.size();i++)
	{
		geo->getPhi(mod,abs(hits[i]->sub()),phii);
		phii -= phi0;
		phii = StEmcMath::getPhiPlusMinusPi(phii);
		phi += phii*hits[i]->energy()*weights[i];
	}
	phi=phi/energy();
	phi += phi0;
	phi = StEmcMath::getPhiPlusMinusPi(phi);
	return phi;
}

float StEmcHitsCluster::sigmaPhi()
{
	float sigmaphi=0;
	int mod=hits[0]->module();
	float phi0;
	geo->getPhi(mod,abs(hits[0]->sub()),phi0);
	float phii;
	for(unsigned int i=0;i<hits.size();i++)
	{
		geo->getPhi(mod,abs(hits[i]->sub()),phii);
		phii -= phi0;
		phii = StEmcMath::getPhiPlusMinusPi(phii);
		sigmaphi += phii*phii*hits[i]->energy()*weights[i];
	}
	sigmaphi=sigmaphi/energy()-phi()*phi();
	if(sigmaphi<0)
		sigmaphi=0;
	else
		sigmaphi=sqrt(sigmaphi);
	return sigmaphi;
}


float StEmcHitsCluster::absEtaMin()
{
	float min;
//	if(module()<61) min = geo->EtaB()[etaBinMin()-1];
//	else min = -geo->EtaB()[etaBinMax()];
	min = geo->EtaB()[etaBinMin()-1];			//only used by patchMin, need positive values
	return min;
}

int StEmcHitsCluster::etaBinMin()
{
	int etabinmin=1000;
	for(unsigned int i=0;i<hits.size();i++)
	{
		int etabin=hits[i]->eta();
		if(etabin<etabinmin)
			etabinmin=etabin;
	}
	return etabinmin;
}

float StEmcHitsCluster::absEtaMax()
{
	float max;
//	if(module()<61) max = geo->EtaB()[etaBinMax()];
//	else max = -geo->EtaB()[etaBinMin()-1];
	max = geo->EtaB()[etaBinMax()];				//only used by patchMax, need positive values
	return max;
}

int StEmcHitsCluster::etaBinMax()
{
	int etabinmax=-1000;
	for(unsigned int i=0;i<hits.size();i++)
	{
		int etabin=hits[i]->eta();
		if(etabin>etabinmax)
			etabinmax=etabin;
	}
	return etabinmax;
}

float StEmcHitsCluster::localPhi()
{
	float localphi = 0;
	float modulephi = 0;
	geo->getPhiModule(module(),modulephi);
	if(module()<61)	localphi = modulephi - phi();
	else localphi = phi() - modulephi;
	
	return localphi;
}

float StEmcHitsCluster::localPhiMin()
{
	//phi bin min -> local phi min
	int phibinmin=1000;
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=abs(hits[i]->sub());
		if(sub<phibinmin)
			phibinmin=sub;
	}
	float min=geo->PhiB()[phibinmin-1];
	return min;
}

int StEmcHitsCluster::patchMin()				//don't understand what this is for --pk 3/12/07
{
//	return int((fabs(absEtaMin())+0.001)*10)+1; 		//doesn't quite work with east side --pk 12/11/07
	for(int i = 1; i <= 10; i++){
		if(absEtaMin()>0.1*(i-1) && absEtaMin()<0.1*i) return i;
	}
}

int StEmcHitsCluster::patchMax()
{
//	return int((fabs(absEtaMax())-0.001)*10)+1;		//doesn't quite work with east side --pk 12/11/07
	for(int i = 1; i <= 10; i++){
		if(absEtaMax()>0.1*(i-1) && absEtaMax()<0.1*i) return i;
	}	
}

float StEmcHitsCluster::localPhiMax()
{
	//phi bin max -> local phi max
	int phibinmax=-1000;
	for(unsigned int i=0;i<hits.size();i++)
	{
		int sub=abs(hits[i]->sub());
		if(sub>phibinmax)
			phibinmax=sub;
	}
	float max=geo->PhiB()[phibinmax];
	return max;
}
