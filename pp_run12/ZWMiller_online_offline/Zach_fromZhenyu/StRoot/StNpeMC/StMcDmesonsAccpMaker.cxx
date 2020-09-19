#include "TFile.h"
#include "TNtuple.h"
#include "TVector2.h"

#include "StParticleDefinition.hh"
#include "StTrack.h"
#include "StPrimaryTrack.h"
#include "StTrackGeometry.h"
#include "StMcEvent/StMcEventTypes.hh"
#include "StMcEvent/StMcPixelHit.hh"
#include "StMcEvent/StMcContainers.hh"
#include "SystemOfUnits.h"
#include "StEvent.h"
#include "StTrackNode.h"
#include "StGlobalTrack.h"
#include "StEmcUtil/projection/StEmcPosition.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/others/emcDetectorName.h"
#include "StEmcRawMaker/defines.h"
#include "StEmcPoint.h"
#include "StEmcCluster.h"
#include "StEmcCollection.h"

#include "StTriggerUtilities/StTriggerSimuMaker.h"
#include "StTriggerUtilities/Bemc/StBemcTriggerSimu.h"

#include "StMcEvent.hh"
#include "StAssociationMaker/StAssociationMaker.h"
#include "StAssociationMaker/StTrackPairInfo.hh"
#include "TVector3.h"
#include "StMcEvent/StMcTpcHit.hh"
#include "StMcDmesonsAccpMaker.h"
#include "StMcTpcHitCollection.hh"


#include "StEventUtilities/StuRefMult.hh"
#include "StEvent/StEventSummary.h"
#include "StEvent/StBTofCollection.h"
#include "StEvent/StBTofHeader.h"
#include "StEvent/StEnumerations.h"
#include "StEvent/StTpcDedxPidAlgorithm.h"
#include "StarClassLibrary/StParticleTypes.hh"

#include "StDetectorDbMaker/StDetectorDbTriggerID.h"

#define D0NTUPLES 0
#define DSTARNTUPLES 1

const int nadc_max = 4;

ClassImp(StMcDmesonsAccpMaker);

StMcDmesonsAccpMaker::StMcDmesonsAccpMaker(StTriggerSimuMaker* trgSim, char* outFileName,const std::vector<unsigned int> triggers) : mMcEvent(0) , mEvent(0)
{
    mTrgSimMaker = trgSim;

    outfile = outFileName;
    interesting_triggers = triggers;
    
    for(int i=0;i<6;i++) {firedTriggersIndices.push_back(-1);};
    
    cout<<"StMcDmesonsAccpMaker::StMcDmesonsAccpMaker - DONE"<<endl;
}
//__________________________________
int StMcDmesonsAccpMaker::Init()
{
    initEmc();

    mFile = new TFile(outfile, "recreate");
    assert(mFile && !mFile->IsZombie());
        
#if D0NTUPLES == 1
    const char* varlist = "pt:p:eta:y:phi:label:" // MC D0
	    "piPt:piEta:piPhi:" // MC pion
	    "piRpt:piReta:piRphi:piNfit:piNmax:piNcom:piNdedx:piDedx:piNsigPi:piNsigK:piDca:" // primary RC pion
	    "piBemcId:piBtowId0:piBtowAdc0:piBtowE0:piBtowE:piBemcDistZ:piBemcDistPhi:piBsmdNEta:piBsmdNPhi:piBtowId:" // pion BEMC info
	    "piBtowDsmAdcProj:piBtowDsmAdcNext:piBtowIdNext:piBtowDsmAdc0:" // dsm adc of projection tower, dsm adc of next highest tower in the nearby 8 towers, 
	                                                                    // id of next tower, dsm ADC of btowId0 (highest tower in cluster)
	    "kPt:kEta:kPhi:" // MC kaon
	    "kRpt:kReta:kRphi:kNfit:kNmax:kNcom:kNdedx:kDedx:kNsigPi:kNsigK:kDca:" // primary RC kaon
	    "kBemcId:kBtowId0:kBtowAdc0:kBtowE0:kBtowE:kBemcDistZ:kBemcDistPhi:kBsmdNEta:kBsmdNPhi:kBtowId:" // kaon BEMC info
	    "kBtowDsmAdcProj:kBtowDsmAdcNext:kBtowIdNext:kBtowDsmAdc0:"

	    "invMass:rPt:rEta:rphi"; // reconstructed D0

#elif DSTARNTUPLES == 1
    const char* varlist = "pt:p:eta:y:phi:label:" // MC D*
	    "d0pt:d0p:d0eta:d0y:d0phi:d0label:"  //  MC D0

	    "piPt:piEta:piPhi:" // MC pion
	    "piRpt:piReta:piRphi:piNfit:piNmax:piNcom:piNdedx:piDedx:piNsigPi:piNsigK:piDca:" // primary RC pion
	    "piBemcId:piBtowId0:piBtowAdc0:piBtowE0:piBtowE:piBemcDistZ:piBemcDistPhi:piBsmdNEta:piBsmdNPhi:piBtowId:" // pion BEMC info
	    "piBtowDsmAdcProj:piBtowDsmAdcNext:piBtowIdNext:piBtowDsmAdc0:" // dsm adc of projection tower, dsm adc of next highest tower in the nearby 8 towers, 
	                                                                    // id of next tower, dsm ADC of btowId0 (highest tower in cluster)
	    "kPt:kEta:kPhi:" // MC kaon
	    "kRpt:kReta:kRphi:kNfit:kNmax:kNcom:kNdedx:kDedx:kNsigPi:kNsigK:kDca:" // primary RC kaon
	    "kBemcId:kBtowId0:kBtowAdc0:kBtowE0:kBtowE:kBemcDistZ:kBemcDistPhi:kBsmdNEta:kBsmdNPhi:kBtowId:" // kaon BEMC info
	    "kBtowDsmAdcProj:kBtowDsmAdcNext:kBtowIdNext:kBtowDsmAdc0:"

	    "d0invMass:d0rPt:d0rEta:d0rphi:" // reconstructed D0

	    "spiPt:spiEta:spiPhi:" // MC soft pion
	    "spiRpt:spiReta:spiRphi:spiNfit:spiNmax:spiNcom:spiNdedx:spiDedx:spiNsigPi:spiNsigK:spiDca:" // primary RC pion
	    "spiBemcId:spiBtowId0:spiBtowAdc0:spiBtowE0:spiBtowE:spiBemcDistZ:spiBemcDistPhi:spiBsmdNEta:spiBsmdNPhi:spiBtowId:" // pion BEMC info
	    "spiBtowDsmAdcProj:spiBtowDsmAdcNext:spiBtowIdNext:spiBtowDsmAdc0:" // dsm adc of projection tower, dsm adc of next highest tower in the nearby 8 towers, 
	                                                                    // id of next tower, dsm ADC of btowId0 (highest tower in cluster)
									    
	    "invMass:rPt:rEta:rphi"; // reconstructed D*
#endif
   
    const char* evtVarList = "runId:eventId:mcVx:mcVy:mcVz:vx:vy:vz:vzVpd:posRefMult:negRefMult:"
    "zdc:bbc:nMcTracks:nRTracks:magField:"
    "t0:t1:t2:t3:t4:t5";

#if D0NTUPLES == 1
    mD = new TNtuple("dzero", "dzero", varlist);
#elif DSTARNTUPLES == 1
    mD = new TNtuple("dstar", "dstar", varlist);
#endif
    mEventCount = new TNtuple("eventCount", "eventCount", evtVarList);

    mAssoc = (StAssociationMaker*)GetMaker("StAssociationMaker");

    cout<<"StMcDmesonsAccpMaker::Init - DONE"<<endl;
    return StMaker::Init();
}

//__________________________________
int StMcDmesonsAccpMaker::Make()
{
    mMcEvent = (StMcEvent*)GetDataSet("StMcEvent");
    
    if (!mMcEvent) 
    {
        LOG_WARN << "No StMcEvent" << endm;
        return kStWarn;
    }

    mEvent = (StEvent*)GetDataSet("StEvent");
    if (!mEvent) {
        LOG_WARN << "No StEvent" << endm;
        return kStWarn;
    }
    
    mEmcCollection = mEvent->emcCollection();
    if(mEmcCollection) buildEmcIndex();

    mField = (float)mEvent->summary()->magneticField();

    // Fill
    int nRTracks = -1;
    int nMcTracks = -1;
    if(pass_trigger())
    {
        fill_mTuple_MC(nRTracks,nMcTracks);
    }
    else
    {
        cout<<"No interesting triggers. Counting event then skipping."<<endl;
    }
    
    fill_eventCount((float)nRTracks,(float)nMcTracks);

    return kStOk;
}
//____________________________________
int StMcDmesonsAccpMaker::fill_eventCount(float nRTracks,float nMcTracks)
{   
    cout<<"Taking event counts..."<<endl;
    float vars[30];
    
    float vpdVz = -999;
    StBTofHeader* tofheader = 0;
    if(mEvent->btofCollection())  tofheader = mEvent->btofCollection()->tofHeader();
    if(tofheader) vpdVz = tofheader->vpdVz();
    
    int i = 0;
    vars[i++] = (float)mEvent->runId();
    vars[i++] = (float)mEvent->id();
    vars[i++] = (float)mMcEvent->primaryVertex()->position().x();
    vars[i++] = (float)mMcEvent->primaryVertex()->position().y();
    vars[i++] = (float)mMcEvent->primaryVertex()->position().z();
    vars[i++] = (float)mEvent->primaryVertex()->position().x();
    vars[i++] = (float)mEvent->primaryVertex()->position().y();
    vars[i++] = (float)mEvent->primaryVertex()->position().z();
    vars[i++] = vpdVz;
    vars[i++] = (float)uncorrectedNumberOfPositivePrimaries(*mEvent);
    vars[i++] = (float)uncorrectedNumberOfNegativePrimaries(*mEvent);
    vars[i++] = (float)mEvent->runInfo()->zdcCoincidenceRate();
    vars[i++] = (float)mEvent->runInfo()->bbcCoincidenceRate();
    vars[i++] = nMcTracks; 
    vars[i++] = nRTracks;
    vars[i++] = (float)mEvent->summary()->magneticField()/10;
    vars[i++] = firedTriggersIndices.at(0);
    vars[i++] = firedTriggersIndices.at(1);
    vars[i++] = firedTriggersIndices.at(2);
    vars[i++] = firedTriggersIndices.at(3);
    vars[i++] = firedTriggersIndices.at(4);
    vars[i++] = firedTriggersIndices.at(5);
    
    mEventCount->Fill(vars);
    
    return kStOk;
}
//____________________________________
bool StMcDmesonsAccpMaker::pass_trigger()
{
    cout<<"Checking triggers..."<<endl;
    bool interesting_event = false;
    
    const StTriggerId* st_trgid = mEvent->triggerIdCollection()->nominal();
    
    for(unsigned int i=0; i<firedTriggersIndices.size(); i++){firedTriggersIndices[i]=-1;}
    
    // Fill interesting triggers
    cout<<"Interesting fired triggers: ";
    for(unsigned int i = 0; i<st_trgid->maxTriggerIds(); i++) 
    {
        unsigned int id = st_trgid->triggerId(i);
        
        int trgIndex = -1;
        
        for (unsigned int j = 0; j < interesting_triggers.size(); j++) 
        {
            if (interesting_triggers[j] == id) 
            {
                trgIndex = j;
                interesting_event = true;
                cout<<id<<" ";
                break;
            }
        }
        
        if(trgIndex!=-1) firedTriggersIndices[trgIndex] = 1.0;
    }
    
    return interesting_event;
}
//____________________________________
int StMcDmesonsAccpMaker::fill_mTuple_MC(int& nRTracks, int& nMcTracks)
{
    StSPtrVecMcTrack& trks = mMcEvent->tracks();
    
    nRTracks = 0;
    nMcTracks = 0;

    for (unsigned int i = 0;  i<trks.size(); i++) 
    {
        StMcTrack* pTrk = trks[i];

#if D0NTUPLES == 1
        if(pTrk->geantId()!=37 && pTrk->geantId()!=38) continue;
#elif DSTARNTUPLES == 1
        if(pTrk->geantId()!=10060 && pTrk->geantId()!=10061) continue;
#endif

	// reject decays away from vertex (beyond what can be reconstructed with primary tracks).
        float pTrkSvx, pTrkSvy;
        if(pTrk->startVertex()) 
        {
            pTrkSvx = pTrk->startVertex()->position().x();
            pTrkSvy = pTrk->startVertex()->position().y();
        }
        if(sqrt(pTrkSvx*pTrkSvx + pTrkSvy*pTrkSvy)>3) continue;
	++nMcTracks;

	StMcTrack* d0_mcTrk = 0;
	StMcTrack* pi_mcTrk = 0; // D0 daughter
	StMcTrack* k_mcTrk = 0;
#if D0NTUPLES == 1
	if(!getDaughters(pTrk,&pi_mcTrk,&k_mcTrk)) continue;
	d0_mcTrk = pTrk;
#elif DSTARNTUPLES == 1
	StMcTrack* spi_mcTrk = 0; // soft pion for D*
	if(!getDaughters(pTrk,&spi_mcTrk,&d0_mcTrk)) continue;
	if(!getDaughters(d0_mcTrk,&pi_mcTrk,&k_mcTrk)) continue;
#endif
	
	// get reconstructed tracks
	int piNcom = -9999;
	int kNcom = -9999;
        const StTrack* pi_gTrk = findPartner(pi_mcTrk, piNcom);
        const StTrack* k_gTrk = findPartner(k_mcTrk, kNcom);
	StPrimaryTrack* pi_pTrk = 0;
	StPrimaryTrack* k_pTrk = 0;
	if(pi_gTrk) pi_pTrk = (StPrimaryTrack*)pi_gTrk->node()->track(primary);
	if(k_gTrk) k_pTrk = (StPrimaryTrack*)k_gTrk->node()->track(primary);
#if DSTARNTUPLES == 1
	int spiNcom = -9999;
	const StTrack* spi_gTrk = findPartner(spi_mcTrk,spiNcom);
	StPrimaryTrack* spi_pTrk = 0;
	if(spi_gTrk) spi_pTrk = (StPrimaryTrack*)spi_gTrk->node()->track(primary);
#endif

	
	// if pi_pTrk and k_pTrk exists, reconstruct D0
	StLorentzVectorF* recoD0 = 0;
	if(pi_pTrk && k_pTrk) 
	{
		recoD0 = getRecoDzero(pi_pTrk,k_pTrk);
#if D0NTUPLES == 1
		++nRTracks;
#endif
	}

	// if D0 is reconstructed and spi_pTrk exists, reconstruct D*
#if DSTARNTUPLES == 1
	StLorentzVectorF* recoDstar = 0;
	if(recoD0 && spi_pTrk)
	{
		recoDstar = getRecoDstar(recoD0,spi_pTrk);
		++nRTracks;
	}
#endif


	// fill ntuple
	float array[200];
	int idx = 0;
#if DSTARNTUPLES == 1
	// MC DStar
	array[idx++] = pTrk->pt();
	array[idx++] = pTrk->momentum().mag();
	array[idx++] = pTrk->pseudoRapidity();
	array[idx++] = pTrk->rapidity();
	array[idx++] = pTrk->momentum().phi();
	array[idx++] = pTrk->eventGenLabel();
#endif
	// MC D0
	array[idx++] = d0_mcTrk->pt();
	array[idx++] = d0_mcTrk->momentum().mag();
	array[idx++] = d0_mcTrk->pseudoRapidity();
	array[idx++] = d0_mcTrk->rapidity();
	array[idx++] = d0_mcTrk->momentum().phi();
	array[idx++] = d0_mcTrk->eventGenLabel();
	// MC pion
	array[idx++] = pi_mcTrk->pt();
	array[idx++] = pi_mcTrk->pseudoRapidity();
	array[idx++] = pi_mcTrk->momentum().phi();
	// RC pion
	fill_rcTrack(array,idx,pi_gTrk,pi_pTrk,piNcom);
	// MC kaon
	array[idx++] = k_mcTrk->pt();
	array[idx++] = k_mcTrk->pseudoRapidity();
	array[idx++] = k_mcTrk->momentum().phi();
	// RC kaon
	fill_rcTrack(array,idx,k_gTrk,k_pTrk,kNcom);
	// reconstructed D0
	array[idx++] = recoD0 ? recoD0->m() : -9999.;
	array[idx++] = recoD0 ? recoD0->perp() : -9999.;
	array[idx++] = recoD0 ? recoD0->pseudoRapidity() : -9999.;
	array[idx++] = recoD0 ? recoD0->phi() : -9999.;
#if DSTARNTUPLES == 1
	// MC soft pion
	array[idx++] = spi_mcTrk->pt();
	array[idx++] = spi_mcTrk->pseudoRapidity();
	array[idx++] = spi_mcTrk->momentum().phi();
	// RC soft pion
	fill_rcTrack(array,idx,spi_gTrk,spi_pTrk,spiNcom);
	// reconstructed D*
	array[idx++] = recoDstar ? recoDstar->m() : -9999.;
	array[idx++] = recoDstar ? recoDstar->perp() : -9999.;
	array[idx++] = recoDstar ? recoDstar->pseudoRapidity() : -9999.;
	array[idx++] = recoDstar ? recoDstar->phi() : -9999.;
#endif
	mD->Fill(array);
    }

    return kStOk;
}
//---------------------------
void StMcDmesonsAccpMaker::fill_rcTrack(float* array,int& idx,const StTrack* gTrk,StPrimaryTrack* pTrk,int ncom)
{
	array[idx++] = pTrk ? pTrk->geometry()->momentum().perp() : -9999.;
	array[idx++] = pTrk ? pTrk->geometry()->momentum().pseudoRapidity() : -9999.;
	array[idx++] = pTrk ? pTrk->geometry()->momentum().phi() : -9999.;
	array[idx++] = pTrk ? pTrk->fitTraits().numberOfFitPoints(kTpcId) : -9999.;
	array[idx++] = pTrk ? pTrk->numberOfPossiblePoints(kTpcId) : -9999.;
	array[idx++] = pTrk ? ncom : -9999.; 

	// dedx info
	float nDedxPts = -9999;
	float dedx = -9999;
	float nSigPi = -9999;
	float nSigK = -9999;
	static StTpcDedxPidAlgorithm aplus;
	static StPionPlus* Pion = StPionPlus::instance();
	static StKaonPlus* Kaon = StKaonPlus::instance();
	const StParticleDefinition* prtcl = 0;
	if(gTrk) prtcl = gTrk->pidTraits(aplus);
	if (prtcl) 
	{
		nDedxPts = aplus.traits()->numberOfPoints();
		dedx = aplus.traits()->mean();
		nSigPi = aplus.numberOfSigma(Pion);
		nSigK = aplus.numberOfSigma(Kaon);
	}

	array[idx++] = nDedxPts;
	array[idx++] = dedx;
	array[idx++] = nSigPi;
	array[idx++] = nSigK;

	// dca
	array[idx++] = gTrk ? gTrk->geometry()->helix().distance(mEvent->primaryVertex()->position()): -9999.;

	// bemc 
	int bemcId = -1; 
	int adc0 = -9999; 
	int id0 = -9999;
	float e[5]; 
	float dist[4]; 
	int nhit[2]; 
	int ntow[3];
	for(int i=0;i<5;i++) { e[i] = 0.; }
	for(int i=0;i<4;i++) { dist[i] = 1.e9; }
	for(int i=0;i<2;i++) { nhit[i] = 0; }
	for(int i=0;i<3;i++) { ntow[i] = -1; }
	if(gTrk) getBEMC(gTrk, &bemcId, &adc0, e, &id0, dist, nhit, ntow);
	float btowId = (ntow[0]<=0 || ntow[0]>4800) ? -1 : (float)ntow[0];

	array[idx++] = bemcId;
	array[idx++] = id0;
	array[idx++] = adc0;
	array[idx++] = e[0];
	array[idx++] = e[1];
	array[idx++] = dist[0];
	array[idx++] = dist[1];
	array[idx++] = nhit[0];
	array[idx++] = nhit[1];
	array[idx++] = btowId;

        // dsm adc info
	int dsmAdc[3] = {-9999,-9999,-9999};
	int id1 = -9999;
	getBtowDSMAdc((int)btowId,id0,dsmAdc,&id1);
	array[idx++] = (float)dsmAdc[0];
	array[idx++] = (float)dsmAdc[2];
	array[idx++] = (float)id1;
	array[idx++] = (float)dsmAdc[1];
}
//---------------------------
StLorentzVectorF* StMcDmesonsAccpMaker::getRecoDzero(StPrimaryTrack* piTrk,StPrimaryTrack* kTrk)
{
  if (!piTrk || !kTrk) return 0;

  StLorentzVectorF kFourMom(kTrk->geometry()->momentum(),kTrk->geometry()->momentum().massHypothesis(.493677));
  StLorentzVectorF pFourMom(piTrk->geometry()->momentum(),piTrk->geometry()->momentum().massHypothesis(.13957));

  StLorentzVectorF* kpFourMom = new StLorentzVectorF();
  *kpFourMom = kFourMom + pFourMom;

  return kpFourMom;
 
  //StLorentzVectorF kpFourMomReverse(-kpFourMom.px(), -kpFourMom.py(), -kpFourMom.pz(), kpFourMom.e());
  //StLorentzVectorF kMomStar = kFourMom.boost(kpFourMomReverse);

  //StThreeVectorF kRotMom(-1.*kaon->pMom().x(),-1.*kaon->pMom().y(),kaon->pMom().z());
  //StLorentzVectorF kRotFourMom(kRotMom,kRotMom.massHypothesis(.493677));
  //StLorentzVectorF kpRotFourMom = kRotFourMom + pFourMom;

  //mOpenAngle = (Short_t)(TMath::Nint(kaon->pMom().angle(pion->pMom()) * 1000.));
  //mCosThetaStar = (Char_t)(TMath::Nint(TMath::Cos(kMomStar.vect().angle(kpFourMom.vect())) * 100. ));
}
//---------------------------
StLorentzVectorF* StMcDmesonsAccpMaker::getRecoDstar(StLorentzVectorF* kpFourMom,StPrimaryTrack* piTrk)
{
	if(!kpFourMom || !piTrk) return 0;
	StLorentzVectorF pFourMom(piTrk->geometry()->momentum(),piTrk->geometry()->momentum().massHypothesis(.13957));

	StLorentzVectorF* kppFourMom = new StLorentzVectorF();
	*kppFourMom = *kpFourMom + pFourMom;

	return kppFourMom;
}
//---------------------------
bool StMcDmesonsAccpMaker::getDaughters(StMcTrack* pTrk,StMcTrack** piTrk,StMcTrack** sTrk)
{
	if(!pTrk->stopVertex()) return false;

	int ndaughter = pTrk->stopVertex()->numberOfDaughters();

	if(ndaughter!=2) return false;

	for(int i=0;i<ndaughter;i++)
	{
		StMcTrack* trk = pTrk->stopVertex()->daughter(i);
		
		// D0 , D0bar
		if(pTrk->geantId()==37 && trk->geantId()==8) *piTrk=trk;
		if(pTrk->geantId()==38 && trk->geantId()==9) *piTrk=trk;

		if(pTrk->geantId()==37 && trk->geantId()==12) *sTrk=trk; // kaon
		if(pTrk->geantId()==38 && trk->geantId()==11) *sTrk=trk; // kaon

		// D* , D*bar
		if(pTrk->geantId()==10060 && trk->geantId()==8) *piTrk=trk;
		if(pTrk->geantId()==10061 && trk->geantId()==9) *piTrk=trk;

		if(pTrk->geantId()==10060 && trk->geantId()==37) *sTrk=trk; // D0
		if(pTrk->geantId()==10061 && trk->geantId()==38) *sTrk=trk;
	}

	if(!*piTrk || !*sTrk) return false;

	return true;
}
		
//________________________________________________
const StTrack* StMcDmesonsAccpMaker::findPartner(StMcTrack* mcTrack, int& maxCommonTpcHits) 
{//..StMcTrack find partner from the StTracks
    if(!mAssoc) {
        cout<<" empty StAssociateMaker, stop!!"<<endl;
        exit(1);
    }
    pair<mcTrackMapIter, mcTrackMapIter> p = mAssoc->mcTrackMap()->equal_range(mcTrack);

    const StTrack* maxTrack = 0;
    maxCommonTpcHits = 0;
    for (mcTrackMapIter k = p.first; k != p.second; ++k) {
        int commonTpcHits = k->second->commonTpcHits();
        const StTrack* track = k->second->partnerTrack()->node()->track(global);//should be global
        if (track && commonTpcHits > maxCommonTpcHits) {
            maxTrack = track;
            maxCommonTpcHits = commonTpcHits;
        }
    }
    return maxTrack;
}


//________________________________________________
const StMcTrack* StMcDmesonsAccpMaker::findPartner(StGlobalTrack* rcTrack, int& maxCommonTpcHits) 
{//.. StGlobalTracks find partner from StMcTracks. 
    //.. See example from StRoot/StMcAnalysisMaker

    if(!mAssoc) {
        cout<<" empty StAssociateMaker, stop!!"<<endl;
        exit(1);
    }

    pair<rcTrackMapIter,rcTrackMapIter> p = mAssoc->rcTrackMap()->equal_range(rcTrack);

    const StMcTrack* maxTrack = 0;
    maxCommonTpcHits = 0;
    for (rcTrackMapIter k = p.first; k != p.second; ++k) {
        int commonTpcHits = k->second->commonTpcHits();

        const StMcTrack* track = k->second->partnerMcTrack();

        if (track && commonTpcHits > maxCommonTpcHits) {
            maxTrack = track;
            maxCommonTpcHits = commonTpcHits;
        }
    }
    return maxTrack;
}
//______________________________________________________________________________
StDedxPidTraits* StMcDmesonsAccpMaker::findDedxPidTraits(const StTrack* track)
{
  StDedxPidTraits* pid=0;
  StPtrVecTrackPidTraits traits = track->pidTraits(kTpcId);
  
  for (UInt_t i = 0; i < traits.size(); i++) {
    pid = dynamic_cast<StDedxPidTraits*>(traits[i]);
    if (pid && pid->method() == kTruncatedMeanId) break;
  }
  return pid;
} 
//______________________________________________________
int StMcDmesonsAccpMaker::Finish()
{
    mFile->Write();
    mFile->Close();
    return kStOk;
}
//___________________________________________
int StMcDmesonsAccpMaker::get_ndedx(const StTrack* t)
{
    int ndedx = -1;
    StPtrVecTrackPidTraits pidTraits = t->pidTraits(kTpcId);   // t is defined as StPrimaryTrack* t
    if(pidTraits.size()){
        StDedxPidTraits* pid;
        for(unsigned int i = 0; i < pidTraits.size(); i++){
            pid = dynamic_cast<StDedxPidTraits*>(pidTraits[i]);
            if(pid && (pid->method() == kTruncatedMeanId)){
                //this->dEdx  = pid->mean();                        //dedx
                ndedx = pid->numberOfPoints();            //number of dedx hits
                break;
            }
        }
    }

    return ndedx;
}
//-----------------------------------------------------------------------
bool StMcDmesonsAccpMaker::getBEMC(const StTrack *t, int *id, int *adc, float *ene, int *id0,float *d, int *nep, int *towid)
{
  *id = -1; *adc = 0;
  for(int i=0;i<5;i++) { ene[i] = 0.; }
  for(int i=0;i<4;i++) { d[i] = 1.e9; }
  for(int i=0;i<2;i++) { nep[i] = 0; }
  for(int i=0;i<3;i++) { towid[i] = -1; }

  if(!mEmcCollection) {
    LOG_WARN << " No Emc Collection for this event " << endm;
    return kFALSE;
  }

  StThreeVectorD position, momentum;
  StThreeVectorD positionBSMDE, momentumBSMDE;
  StThreeVectorD positionBSMDP, momentumBSMDP;
  Double_t bFld = mField*kilogauss/tesla; // bFld in Tesla
  bool ok       = false;
  bool okBSMDE  = false;
  bool okBSMDP  = false;
  if(mEmcPosition) {
    ok      = mEmcPosition->projTrack(&position, &momentum, t, bFld, mEmcGeom[0]->Radius());
    okBSMDE = mEmcPosition->projTrack(&positionBSMDE, &momentumBSMDE, t, bFld, mEmcGeom[2]->Radius());
    okBSMDP = mEmcPosition->projTrack(&positionBSMDP, &momentumBSMDP, t, bFld, mEmcGeom[3]->Radius());
  }
//  if(!ok || !okBSMDE || !okBSMDP) {
  if(!ok) {
    LOG_WARN << " Projection failed for this track ... " << endm;
    return kFALSE;
  }

  if(ok && okBSMDE && okBSMDP) {

  Int_t mod, eta, sub;
  StSPtrVecEmcPoint& bEmcPoints = mEmcCollection->barrelPoints();
  int index=0;
  float mindist=1.e9;
  mEmcGeom[0]->getBin(positionBSMDP.phi(), positionBSMDE.pseudoRapidity(), mod, eta, sub); //project on SMD plan
  for(StSPtrVecEmcPointIterator it = bEmcPoints.begin(); it != bEmcPoints.end(); it++, index++) {
    bool associated=false;
    StPtrVecEmcCluster& bEmcClusters = (*it)->cluster(kBarrelEmcTowerId);
    if(bEmcClusters.size()==0 ) continue;
    if(bEmcClusters[0]==NULL) continue;
    for(StPtrVecEmcClusterIterator cIter = bEmcClusters.begin(); cIter != bEmcClusters.end(); cIter++) {
      StPtrVecEmcRawHit& bEmcHits = (*cIter)->hit();
      for(StPtrVecEmcRawHitIterator hIter = bEmcHits.begin(); hIter != bEmcHits.end(); hIter++) {
        if(mod == (Int_t)(*hIter)->module() && eta == (Int_t)(*hIter)->eta() && sub == (Int_t)(*hIter)->sub()) {
          associated=true;
          break;
        }
      }
      if(associated) {
        for(StPtrVecEmcRawHitIterator hitit=bEmcHits.begin(); hitit!=bEmcHits.end();hitit++) {
          if((*hitit)->energy()>ene[0]) ene[0]=(*hitit)->energy();
          if((int)(*hitit)->adc()>(*adc)) 
	  {
		  *adc=(*hitit)->adc();
		  *id0=(*hitit)->softId(1);
	  }
        }
      }
    }

    StPtrVecEmcCluster& smdeClusters = (*it)->cluster(kBarrelSmdEtaStripId);
    StPtrVecEmcCluster& smdpClusters = (*it)->cluster(kBarrelSmdPhiStripId);

    if(associated) {
      *id = index;
      ene[1] = ene[1] + (*it)->energy(); //use point's energy, not tower cluster's energy

      float deltaphi=(*it)->position().phi()-positionBSMDP.phi();
      if(deltaphi>=TMath::Pi()) deltaphi=deltaphi-TMath::TwoPi();
      if(deltaphi<-TMath::Pi()) deltaphi=deltaphi+TMath::TwoPi();

      float rsmdp=mEmcGeom[3]->Radius();
      float pointz=(*it)->position().z();
      float deltaz=pointz-positionBSMDE.z();
      if(sqrt(deltaphi*deltaphi*rsmdp*rsmdp+deltaz*deltaz)<mindist) {
        d[1]=deltaphi;
        d[0]=deltaz;
        if(smdeClusters.size()>=1) nep[0]=smdeClusters[0]->nHits();
        if(smdpClusters.size()>=1) nep[1]=smdpClusters[0]->nHits();
        mindist=sqrt(deltaphi*deltaphi*rsmdp*rsmdp+deltaz*deltaz);
      }
    }//associated
  }

  } // end if (ok && okBSMDE && okBSMDP)

  //Get BEMC tower energy from matched tower + 2 nearest towers

  int towerId;
  int localTowerId = -1;
  int localId1 = -1;
  int localId2 = -1;
  double energy1 = 0, energy2 = 0;
  double energyTemp;
  double dist1 = 1000, dist2 = 1000;
  double distTemp;
  Float_t etaTemp, phiTemp;

  mEmcGeom[0]->getId(position.phi(),position.pseudoRapidity(),towerId);
  for(int ieta=-1;ieta<2;ieta++){
    for(int iphi=-1;iphi<2;iphi++){
      localTowerId++;//loops from 0 to 8
      int nextTowerId = mEmcPosition->getNextTowerId(towerId, ieta, iphi);
      if(nextTowerId < 1 || nextTowerId > 4800) continue;
      StEmcRawHit* emcHit = mEmcIndex[nextTowerId-1];
      if (emcHit==0) continue;
      if (emcHit->energy()<0.2) continue; // don't include any noise tower
      if(ieta==0&&iphi==0) {
        mEmcGeom[0]->getEta(nextTowerId, etaTemp);
        mEmcGeom[0]->getPhi(nextTowerId, phiTemp);
        ene[2] = emcHit->energy();
        d[2] = position.pseudoRapidity() - etaTemp; 
        d[3] = position.phi() - phiTemp; 
      }
      else {
        energyTemp = emcHit->energy();
        mEmcGeom[0]->getEta(nextTowerId, etaTemp);
        mEmcGeom[0]->getPhi(nextTowerId, phiTemp);
        distTemp = sqrt((etaTemp-position.pseudoRapidity())*(etaTemp-position.pseudoRapidity()) + (phiTemp-position.phi())*(phiTemp-position.phi()));
        if(distTemp < dist1) {
          dist2 = dist1;
          dist1 = distTemp;
	  energy2 = energy1;
          energy1 = energyTemp;
          localId1 = localTowerId;
        }
        else if(distTemp < dist2){
          dist2 = distTemp;
          energy2 = energyTemp;
          localId2 = localTowerId;
        }
      }
    }
  }
  towid[0] = towerId;
  ene[3] = energy1;//closest tower
  towid[1] = localId1;
  ene[4] = energy2;//2nd closest tower
  towid[2] = localId2;

  if(Debug()) {
//  if(1) {
    cout << " ====== BEMC results ====== " << endl;
    cout << " Energy = " << ene[0] << " " << ene[1] << " " << ene[2] << " " << ene[3] << " " << ene[4] << endl;
    cout << " BSMD = " << nep[0] << " " << nep[1] << endl;
    cout << " TowerId = " << towid[0] << " " << towid[1] << " " << towid[2] << endl;
  }

  return kTRUE;
}
//-----------------------------------------------------------------------
bool StMcDmesonsAccpMaker::getBtowDSMAdc(int btowId,int btowId0,int* adc,int* id1)
{
	if(!mTrgSimMaker || !mEmcPosition) return kFALSE;

	adc[0] = -9999;
	adc[1] = -9999;
	adc[2] = -9999;
	*id1 = -9999;

	if(btowId>0 && btowId<=4800) adc[0] = mTrgSimMaker->bemc->barrelHighTowerAdc(btowId); // dsm adc of track projection tower
	if(btowId0>=1 && btowId0<=4800) adc[1] = mTrgSimMaker->bemc->barrelHighTowerAdc(btowId0);

	if(btowId<0 || btowId>4800) return false;

	for(int ieta=-1;ieta<2;ieta++)
	{
		for(int iphi=-1;iphi<2;iphi++)
		{
			if(ieta==0 && iphi==0) continue;

			int nextTowerId = mEmcPosition->getNextTowerId(btowId, ieta, iphi);
			if(nextTowerId < 1 || nextTowerId > 4800) continue;
			int tmpAdc = mTrgSimMaker->bemc->barrelHighTowerAdc(nextTowerId);

			if(tmpAdc >adc[2])
			{
				// adc and id of the highest tower in the nearby eight towers
				adc[2] = tmpAdc; 
				*id1 = nextTowerId;
			}
		}
	}

	return kTRUE;
}
//-----------------------------------------------------------------------
void StMcDmesonsAccpMaker::initEmc() {
  mEmcPosition = new StEmcPosition();
  for(int i=0;i<4;i++) {
    mEmcGeom[i] = StEmcGeom::getEmcGeom(detname[i].Data());
  }
}
//-----------------------------------------------------------------------
void StMcDmesonsAccpMaker::buildEmcIndex() {
  StEmcDetector *mEmcDet = mEmcCollection->detector(kBarrelEmcTowerId);
  memset(mEmcIndex, 0, sizeof(mEmcIndex));
  if(!mEmcDet) return;
  for (size_t iMod=1; iMod<=mEmcDet->numberOfModules(); ++iMod) {
    StSPtrVecEmcRawHit& modHits = mEmcDet->module(iMod)->hits();
    for (size_t iHit=0; iHit<modHits.size(); ++iHit) {
      StEmcRawHit* rawHit = modHits[iHit];
      if(!rawHit) continue;
      unsigned int softId = rawHit->softId(1); 
      if (mEmcGeom[0]->checkId(softId)==0) { // OK
        mEmcIndex[softId-1] = rawHit;
      }
    }
  }
}
