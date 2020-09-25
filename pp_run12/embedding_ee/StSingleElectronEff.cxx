#include "StSingleElectronEff.h"

#include "StChain.h"
#include "TF1.h"
#include "TRandom.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>
#include <cmath>

#include "PhysicalConstants.h"
#include "SystemOfUnits.h"
#include "StThreeVector.hh"
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"
#include "StLorentzVectorD.hh"
#include "StPhysicalHelixD.hh"

#include "StTriggerIdCollection.h"
#include "StTriggerId.h"
#include "StEvent/StEmcCollection.h"
#include "StEmcClusterCollection.h"
#include "StEvent/StEmcPoint.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/projection/StEmcPosition.h"
#include "StEmcUtil/others/emcDetectorName.h"
#include "StEmcADCtoEMaker/StBemcData.h"
#include "StEmcADCtoEMaker/StEmcADCtoEMaker.h"
#include "StEmcRawMaker/defines.h"
#include "StEmcRawMaker/StBemcRaw.h"
#include "StEmcRawMaker/StBemcTables.h"
#include "StEmcRawMaker/StEmcRawMaker.h"
//#include "StEmcTriggerMaker/StEmcTriggerMaker.h"
//#include "StEmcTriggerMaker/StBemcTrigger.h"
#include "StTriggerUtilities/StTriggerSimuMaker.h"
//#include "StTriggerUtilities/StTriggerSimuResult.h"
#include "StTriggerUtilities/Bemc/StBemcTriggerSimu.h"

#include "StEvent.h"
#include "StEvent/StTrack.h"
#include "StEvent/StGlobalTrack.h"
#include "StEvent/StPrimaryTrack.h"
#include "StEvent/StTriggerIdCollection.h"
#include "StEvent/StTriggerId.h"
#include "StEvent/StPrimaryVertex.h"
#include "StEvent/StBTofCollection.h"
#include "StEvent/StBTofHit.h"
#include "StEvent/StBTofPidTraits.h"

#include "StMcEvent/StMcEvent.hh"
#include "StMcEvent/StMcVertex.hh"
#include "StMcEvent/StMcTrack.hh"
#include "StEventUtilities/StuRefMult.hh"

#include "StAssociationMaker/StAssociationMaker.h"
#include "StAssociationMaker/StTrackPairInfo.hh"
#include "StAssociationMaker/StMcParameterDB.h"

#include <math.h>
#include "TRandom.h"
#include "Random.h"
#include "RanluxEngine.h"
#include "RandGauss.h"
#define DEBUG 1

static RanluxEngine engine;
static RandGauss ranGauss(engine);

/*StGlobalTrack*  partnerTrack(mcTrackMapType* map, StMcTrack* mT) {
	mcTrackMapIter i = map->find(mT);
	StGlobalTrack* rT = 0;
	int nCommon = 0;
	if (i != map->end()) {
		if( (int) ((*i).second->commonTpcHits()) > nCommon ) {
			rT = const_cast<StGlobalTrack*>((*i).second->partnerTrack());
			nCommon = (*i).second->commonTpcHits();
		}
	}
	return rT; 
} 

StMcTrack*  partnerMcTrack(rcTrackMapType* map, StGlobalTrack* rT) {
	rcTrackMapIter i = map->find(rT);
	StMcTrack* mT = 0;
	int nCommon = 0;
	if (i != map->end()) {
		if( (int) ((*i).second->commonTpcHits()) > nCommon ) {
			mT = const_cast<StMcTrack*>((*i).second->partnerMcTrack());
			nCommon = (*i).second->commonTpcHits();
		}
	}
	return mT;
}
*/

ClassImp(StSingleElectronEff)

	//_________________________________________________
StSingleElectronEff::StSingleElectronEff(const char *name, const char *file):StMaker(name)
{
	//  StSingleElectronEff Constructor
	// - zero all pointers defined in the header file
	mOutputFile = new TFile(file,"RECREATE");
	mOutputFile->SetCompressionLevel(1);
	int BufSize=(int)pow(2.,16.);
	mTree = new TTree("mcT","mcT",BufSize);
	mTree->SetAutoSave(1000000); // autosave every 1 Mbytes
	mTree->Branch("triggerId",&mParticle.triggerId,"triggerId/I");
	mTree->Branch("vxMc",&mParticle.vxMc,"vxMc/F");
	mTree->Branch("vyMc",&mParticle.vyMc,"vyMc/F");
	mTree->Branch("vzMc",&mParticle.vzMc,"vzMc/F");
	mTree->Branch("vx",&mParticle.vx,"vx/F");
	mTree->Branch("vy",&mParticle.vy,"vy/F");
	mTree->Branch("vz",&mParticle.vz,"vz/F");
	mTree->Branch("ranking",&mParticle.ranking,"ranking/F");
	mTree->Branch("mcId",&mParticle.mcId,"mcId/I");
	mTree->Branch("evtId",&mParticle.evtId,"evtId/I");
	mTree->Branch("MagField",&mParticle.MagField,"MagField/F");
	mTree->Branch("runId",&mParticle.runId,"runId/I");
	mTree->Branch("zdcX",&mParticle.zdcX,"zdcX/F");
	mTree->Branch("vzVpd",&mParticle.vzVpd,"vzVpd/F");
	mTree->Branch("nTracks",&mParticle.nTracks,"nTracks/I");
	mTree->Branch("parentGeantId",mParticle.parentGeantId,"parentGeantId[nTracks]/I");
	mTree->Branch("E_mcPt",mParticle.E_mcPt,"E_mcPt[nTracks]/F");
	mTree->Branch("E_mcEta",mParticle.E_mcEta,"E_mcEta[nTracks]/F");
	mTree->Branch("E_mcPhi",mParticle.E_mcPhi,"E_mcPhi[nTracks]/F");
	mTree->Branch("E_rcPt",mParticle.E_rcPt,"E_rcPt[nTracks]/F");
	mTree->Branch("E_rcEta",mParticle.E_rcEta,"E_rcEta[nTracks]/F");
	mTree->Branch("E_rcPhi",mParticle.E_rcPhi,"E_rcPhi[nTracks]/F");
	mTree->Branch("E_matchTOF",mParticle.E_matchTOF,"E_matchTOF[nTracks]/I");
	mTree->Branch("E_rcProjR",mParticle.E_rcProjR,"E_rcProjR[nTracks]/F");
	mTree->Branch("E_rcProjZ",mParticle.E_rcProjZ,"E_rcProjZ[nTracks]/F");
	mTree->Branch("E_rcProjPhi",mParticle.E_rcProjPhi,"E_rcProjPhi[nTracks]/F");
	mTree->Branch("E_rcgPt",mParticle.E_rcgPt,"E_rcgPt[nTracks]/F");
	mTree->Branch("E_rcgEta",mParticle.E_rcgEta,"E_rcgEta[nTracks]/F");
	mTree->Branch("E_rcgPhi",mParticle.E_rcgPhi,"E_rcgPhi[nTracks]/F");
	mTree->Branch("E_rcFlag",mParticle.E_rcFlag,"E_rcFlag[nTracks]/I");
	mTree->Branch("E_rcNHitsFit",mParticle.E_rcNHitsFit,"E_rcNHitsFit[nTracks]/I");
	mTree->Branch("E_rcNHitsPoss",mParticle.E_rcNHitsPoss,"E_rcNHitsPoss[nTracks]/I");
	mTree->Branch("E_rcNCommonHits",mParticle.E_rcNCommonHits,"E_rcNCommonHits[nTracks]/I");
	mTree->Branch("E_rcstpcx",mParticle.E_rcstpcx,"E_rcstpcx[nTracks]/F");
	mTree->Branch("E_rcstpcy",mParticle.E_rcstpcy,"E_rcstpcy[nTracks]/F");
	mTree->Branch("E_rcstpcz",mParticle.E_rcstpcz,"E_rcstpcz[nTracks]/F");
	mTree->Branch("E_HelixX",mParticle.E_HelixX,"E_HelixX[nTracks]/F");
	mTree->Branch("E_HelixY",mParticle.E_HelixY,"E_HelixY[nTracks]/F");
	mTree->Branch("E_HelixZ",mParticle.E_HelixZ,"E_HelixZ[nTracks]/F");
	mTree->Branch("E_dca",mParticle.E_dca,"E_dca[nTracks]/F");
	mTree->Branch("E_dEdx",mParticle.E_dEdx,"E_dEdx[nTracks]/F");
	mTree->Branch("E_rcNdEdx",mParticle.E_rcNdEdx,"E_rcNdEdx[nTracks]/I");
	mTree->Branch("E_rcEnergy",mParticle.E_rcEnergy,"E_rcEnergy[nTracks]/F");
	mTree->Branch("E_rcnEta",mParticle.E_rcnEta,"E_rcnEta[nTracks]/I");
	mTree->Branch("E_rcnPhi",mParticle.E_rcnPhi,"E_rcnPhi[nTracks]/I");
	mTree->Branch("E_rczDist",mParticle.E_rczDist,"E_rczDist[nTracks]/F");
	mTree->Branch("E_rcphiDist",mParticle.E_rcphiDist,"E_rcphiDist[nTracks]/F");
	mTree->Branch("E_rcminDist",mParticle.E_rcminDist,"E_rcminDist[nTracks]/F");
	mTree->Branch("E_rcadc0",mParticle.E_rcadc0,"E_rcadc0[nTracks]/I");
	mTree->Branch("E_rcdsmadc",mParticle.E_rcdsmadc,"E_rcdsmadc[nTracks]/I");
	mTree->Branch("E_rcEMCEta",mParticle.E_rcEMCEta,"E_rcEMCEta[nTracks]/F");
	mTree->Branch("E_rcEMCPhi",mParticle.E_rcEMCPhi,"E_rcEMCPhi[nTracks]/F");
	mTree->Branch("E_rcEnergy0",mParticle.E_rcEnergy0,"E_rcEnergy0[nTracks]/F");
	mTree->Branch("E_rctowerId",mParticle.E_rctowerId,"E_rctowerId[nTracks]/I");	

	eventNumber=0;
	oldEventRunId=0;
	mRcEvent=0;
	mMcEvent=0;
	mMcVertex.setX(0.); mMcVertex.setY(0.); mMcVertex.setZ(0.);
	mAssocMaker=0;
	mRcTrackMap=0;
	mMcTrackMap=0;

}

//_________________________________________________
StSingleElectronEff::~StSingleElectronEff()
{
}

//_____________________________________________________________________________

void StSingleElectronEff::Clear(const char*)
{
	StMaker::Clear();
}

//_________________________________________________
Int_t StSingleElectronEff::Finish()
{
	mOutputFile->Write();
	mOutputFile->Close();
	return StMaker::Finish();
}


//___________________________________________________
Bool_t StSingleElectronEff::projTrack(StThreeVectorD *atFinal, StThreeVectorD *momentumAtFinal, StTrack* track, double magField, double radius, int option) {
	StThreeVectorD Zero(0,0,0);
	*atFinal=Zero;
	*momentumAtFinal=Zero;

	const StThreeVectorF& origin = track->geometry()->origin();
	const StThreeVectorF& momentum = track->geometry()->momentum();
	double charge = track->geometry()->charge();
	StPhysicalHelixD helix(momentum, origin, magField*kilogauss, charge);
	pairD pathLength = helix.pathLength(radius);

	double s,s1,s2;
	s=0;
	s1 = pathLength.first;
	s2 = pathLength.second;

	Bool_t goProj;
	goProj = kFALSE;

	if (finite(s1) == 0 && finite(s2) == 0) { return kFALSE;} // Track couldn't be projected!

	if (option == 1)  // Selects positive path lenght to project track forwards along its helix relative to
		// first point of track. The smaller solution is taken when both are positive
	{
		if (s1 >= 0 && s2 >= 0) {s = s1; goProj = kTRUE; }
		if (s1 >= 0 && s2 < 0) { s = s1; goProj = kTRUE; }
		if (s1 < 0 && s2 >= 0) { s = s2; goProj = kTRUE; }
	}

	if (option == -1) // Selects negative path lenght to project track backwards along its helix relative to
		// first point of track. The smaller absolute solution is taken when both are negative 
	{
		if (s1 <= 0 && s2 <= 0) { s = s2; goProj = kTRUE; }
		if (s1 <= 0 && s2 > 0) { s = s1; goProj = kTRUE; }
		if (s1 > 0 && s2 <= 0) { s = s2; goProj = kTRUE; }
	}
	{
		*atFinal = helix.at( s );
		*momentumAtFinal = helix.momentumAt( s, magField*tesla );
		if (charge == 0) *momentumAtFinal = momentum;
	}
	return goProj;
}

Int_t StSingleElectronEff::Init()
{
	Clear("C");
	///////
	//refmultcorr = new StRefMultCorr();
	///////
	return kStOK;
}
//_________________________________________________
Int_t StSingleElectronEff::Make()
{
	Clear("C");
	mMcEvent = (StMcEvent*) GetDataSet("StMcEvent");
	if(!mMcEvent) return kStErr;

	mRcEvent=(StEvent *) GetInputDS("StEvent");
	if (!mRcEvent){
		LOG_WARN << " No StEvent! " << endm;
		return kStOK;        // if no event, we're done
	}

	mAssocMaker = (StAssociationMaker*) GetMaker("StAssociationMaker");
	if (mAssocMaker) {
		mRcTrackMap = mAssocMaker->rcTrackMap();
		mMcTrackMap = mAssocMaker->mcTrackMap();
	}

	StTriggerIdCollection *trgIdColl = mRcEvent->triggerIdCollection();
	if(trgIdColl && trgIdColl->nominal() && 
			(trgIdColl->nominal()->isTrigger(370542) || 
			 trgIdColl->nominal()->isTrigger(370522) ) ) {
	} else {
		cout << " Not a HT trigger" << endl;
		return kStOK;
	}


	double magnet = mRcEvent->summary()->magneticField();
	double radius = 210;
	if(DEBUG){
		cout<<"MagnetField: "<<magnet<<endl;
		cout<<"ProjectRadius: "<<radius<<"cm"<<endl;
	}
	mMcVertex = mMcEvent->primaryVertex()->position();

	//////////////////////////////////////////////////////
	// Filling the event header
	//////////////////////////////////////////////////////
	mParticle.triggerId = -999;
	if(trgIdColl->nominal()->isTrigger(370542)) mParticle.triggerId +=1<<1;
	if(trgIdColl->nominal()->isTrigger(370522)) mParticle.triggerId +=1<<2;

	mParticle.vxMc  = mMcVertex.x();
	mParticle.vyMc  = mMcVertex.y();
	mParticle.vzMc  = mMcVertex.z();

	StThreeVectorF rcVertex = mRcEvent->summary()->primaryVertexPosition();

	if(fabs(rcVertex.x())<1.e-5 && fabs(rcVertex.y())<1.e-5 && fabs(rcVertex.z())<1.e-5) {
		mParticle.vx = -999.;
		mParticle.vy = -999.;
		mParticle.vz = -999.;
	} else {
		mParticle.vx = rcVertex.x();
		mParticle.vy = rcVertex.y();
		mParticle.vz = rcVertex.z();
	}

	StPrimaryVertex  *pVtx = mRcEvent->primaryVertex();
	if(pVtx) {
		mParticle.ranking = pVtx->ranking();
	} else {
		mParticle.ranking = -1.e9;
	}
	mParticle.mcId = mMcEvent->eventNumber();
	mParticle.evtId = mRcEvent->info()->id();
	mParticle.MagField = mRcEvent->runInfo()->magneticField();
	mParticle.runId = mRcEvent->info()->runId();
	mParticle.zdcX = mRcEvent->runInfo()->zdcCoincidenceRate();
	//mParticle.recVz = mRcEvent->primaryVertex(0)->position().z();

	mParticle.vzVpd = -999.;
	if(mRcEvent->btofCollection()) {
		StBTofHeader *btofHeader = mRcEvent->btofCollection()->tofHeader();
		if(btofHeader) {
			mParticle.vzVpd = btofHeader->vpdVz();
		}
	}
	StTriggerSimuMaker* mTriggerSimuMaker = (StTriggerSimuMaker*) GetMaker("StarTrigSimu");
	assert(mTriggerSimuMaker);
	mBemcTriggerSimu = (StBemcTriggerSimu*) mTriggerSimuMaker->bemc;
	for(int i=1;i<=4800;i++) {
		if(Debug()>0&&mBemcTriggerSimu->getHT6bitAdc(i)>11) cout<<i<<"  "<<mBemcTriggerSimu->getHT6bitAdc(i)<<endl;
	}
	//////////////////////////////////////////////////////
	// Looking for Dstar
	//////////////////////////////////////////////////////
	cout<<"Fill TrackEvent object"<<endl;

	LOG_DEBUG<<"about to fill track object"<<endm;

	cout << "Event variables filled" << endl;

	StSPtrVecMcTrack mctracks = mMcEvent->tracks();
	cout<<"number of MC tracks: "<<mctracks.size()<<endl;

	int nTracks = 0;
	for(int i=0;i<(int) mctracks.size();i++) {
		StMcTrack *mcE = 0;

		StMcTrack *mcElectron = dynamic_cast<StMcTrack *>(mctracks[i]);
		if(!mcElectron) continue;
		if(mcElectron->key()==0 && mcElectron->geantId()==0) continue; // not geant tracks

		if((mcElectron->geantId()!=2)&&(mcElectron->geantId()!=3)) continue; // not e+ or e- track
		mcE = mcElectron;
		if(DEBUG) cout << " " << mcElectron->geantId()<<endl;
		if(!mcElectron->startVertex() || (mcElectron->startVertex()->position()-mMcVertex).mag()>1.e-5 ) continue;
		//if(DEBUG) cout << endl;
    
		if(fabs(mcE->momentum().pseudoRapidity())>1.5) continue;
		StPrimaryTrack *rcE = 0;
		StGlobalTrack *grcE = 0;

		int nCommonHits ;
		// find the associate track
		if(mAssocMaker){
			if(mMcTrackMap) {
				StTrackPairInfo* matchedTrackPairInfoE = findBestMatchedGlobal(mcE);
				if(matchedTrackPairInfoE) {
					grcE = const_cast<StGlobalTrack*>(matchedTrackPairInfoE->partnerTrack());
					if(grcE) rcE = dynamic_cast<StPrimaryTrack *>(grcE->node()->track(primary));
				}
			}
		}
		const StMcTrack *mcParent = mcElectron->parent();
		if(mcParent) mParticle.parentGeantId[nTracks] =  mcParent->geantId();
		else mParticle.parentGeantId[nTracks] = 0;
		mParticle.E_mcPt[nTracks] = mcE->momentum().perp(); 
		mParticle.E_mcEta[nTracks] = mcE->momentum().pseudoRapidity(); 
		mParticle.E_mcPhi[nTracks] = mcE->momentum().phi(); 
		if(rcE){
			mParticle.E_rcPt[nTracks]  = rcE->geometry()->momentum().perp(); 
			mParticle.E_rcEta[nTracks] = rcE->geometry()->momentum().pseudoRapidity(); 
			mParticle.E_rcPhi[nTracks] = rcE->geometry()->momentum().phi(); 
			mParticle.E_matchTOF[nTracks] = -1;
			StPtrVecTrackPidTraits traits = rcE->pidTraits(kTofId);
			StBTofPidTraits *btofPidTraits = 0;
			unsigned int size  = traits.size();
			for(unsigned int i=0; i<size; i++) {
				if(btofPidTraits = dynamic_cast<StBTofPidTraits *>(traits[i])) {
					mParticle.E_matchTOF[nTracks] = btofPidTraits->matchFlag(); 
				}
			}
			StThreeVectorD position, momentum;
			if(projTrack(&position,&momentum,rcE,magnet,radius)){
				mParticle.E_rcProjR[nTracks] = position.perp();
				mParticle.E_rcProjZ[nTracks] = position.z();
				mParticle.E_rcProjPhi[nTracks] = position.phi();
			} else {
				mParticle.E_rcProjR[nTracks]   = -999;
				mParticle.E_rcProjZ[nTracks]   = -999;
				mParticle.E_rcProjPhi[nTracks] = -999;
			}

		} else {
			mParticle.E_rcPt[nTracks]      = -999;
			mParticle.E_rcEta[nTracks]     = -999;
			mParticle.E_rcPhi[nTracks]     = -999;
			mParticle.E_rcProjR[nTracks]   = -999;
			mParticle.E_rcProjZ[nTracks]   = -999;
			mParticle.E_rcProjPhi[nTracks] = -999;
			mParticle.E_matchTOF[nTracks]  = -999;
		}

		mParticle.E_rcgPt[nTracks]         = -999;
		mParticle.E_rcgEta[nTracks]        = -999;
		mParticle.E_rcgPhi[nTracks]        = -999;
		mParticle.E_rcFlag[nTracks]        = -999;
		mParticle.E_rcNHitsFit[nTracks]    = -999;
		mParticle.E_rcNHitsPoss[nTracks]   = -999;
		mParticle.E_rcNCommonHits[nTracks] = -999;
		mParticle.E_rcstpcx[nTracks]       = -999;
		mParticle.E_rcstpcy[nTracks]       = -999;
		mParticle.E_rcstpcz[nTracks]       = -999;
		mParticle.E_HelixX[nTracks]        = -999;
		mParticle.E_HelixY[nTracks]        = -999;
		mParticle.E_HelixZ[nTracks]        = -999;
		mParticle.E_dca[nTracks]           = -999;
		mParticle.E_dEdx[nTracks]          = -999;
		mParticle.E_rcNdEdx[nTracks]       = -999;

		mParticle.E_rcEnergy[nTracks]      = -999;
		mParticle.E_rcnEta[nTracks]        = -999;
		mParticle.E_rcnPhi[nTracks]        = -999;
		mParticle.E_rczDist[nTracks]       = -999;
		mParticle.E_rcphiDist[nTracks]     = -999;
		mParticle.E_rcminDist[nTracks]     = -999;
		mParticle.E_rcadc0[nTracks]        = -999;
		mParticle.E_rcdsmadc[nTracks]      = -999;
		mParticle.E_rcEMCEta[nTracks]      = -999;
		mParticle.E_rcEMCPhi[nTracks]      = -999;
		mParticle.E_rcEnergy0[nTracks]     = -999;
		mParticle.E_rctowerId[nTracks]     = -999;

		if(grcE){
			mParticle.E_rcgPt[nTracks]  = grcE->geometry()->momentum().perp();
			mParticle.E_rcgEta[nTracks] = grcE->geometry()->momentum().pseudoRapidity();
			mParticle.E_rcgPhi[nTracks] = grcE->geometry()->momentum().phi();

			if(grcE->flag()<0||grcE->flag()>1000) continue;
			mParticle.E_rcFlag[nTracks] = grcE->flag();
			if(grcE->flag()/100<7) { // TPC tracks
				mParticle.E_rcNHitsFit[nTracks]    = grcE->fitTraits().numberOfFitPoints(kTpcId); 
				mParticle.E_rcNHitsPoss[nTracks]   = grcE->numberOfPossiblePoints(kTpcId); 
			} else { // FTPC tracks
				if(grcE->geometry()->momentum().pseudoRapidity()>0.) {
					mParticle.E_rcNHitsFit[nTracks]    = grcE->fitTraits().numberOfFitPoints(kFtpcWestId); 
					mParticle.E_rcNHitsPoss[nTracks]   = grcE->numberOfPossiblePoints(kFtpcWestId); 
				} else {
					mParticle.E_rcNHitsFit[nTracks]    = grcE->fitTraits().numberOfFitPoints(kFtpcEastId); 
					mParticle.E_rcNHitsPoss[nTracks]   = grcE->numberOfPossiblePoints(kFtpcEastId); 
				}
			}

			mParticle.E_rcNCommonHits[nTracks] = (*mMcTrackMap->find(mcE)).second->commonTpcHits();
			if (nCommonHits==1)cout<<"RRR"<<nCommonHits<<endl;
			mParticle.E_rcstpcx[nTracks]=grcE->detectorInfo()->firstPoint().x();
			mParticle.E_rcstpcy[nTracks]=grcE->detectorInfo()->firstPoint().y();
			mParticle.E_rcstpcz[nTracks]=grcE->detectorInfo()->firstPoint().z();
			StPhysicalHelixD helixE = grcE->geometry()->helix();
			mParticle.E_HelixX[nTracks]     = helixE.origin().x();
			mParticle.E_HelixY[nTracks]     = helixE.origin().y();
			mParticle.E_HelixZ[nTracks]     = helixE.origin().z();
			if(!(fabs(rcVertex.x())<1.e-5 && fabs(rcVertex.y())<1.e-5 && fabs(rcVertex.z())<1.e-5)) 
				mParticle.E_dca[nTracks]           = grcE->geometry()->helix().distance(rcVertex); 

			static StTpcDedxPidAlgorithm Ededx;
			grcE->pidTraits(Ededx);
			if(Ededx.traits()) {
				mParticle.E_dEdx[nTracks] = Ededx.traits()->mean()*1e6;
				mParticle.E_rcNdEdx[nTracks] = Ededx.traits()->numberOfPoints();
			}

			StEmcCollection* pEmcCol = mRcEvent->emcCollection();
			Int_t mod, eta, sub;
			StThreeVectorD position, momentum;
			StThreeVectorD positionBSMDE, momentumBSMDE;
			StThreeVectorD positionBSMDP, momentumBSMDP;
			Double_t bFld;
			bFld = mRcEvent->summary()->magneticField()/10.; // bFld in Tesla
			bool ok = false;
			bool okBSMDE = false;
			bool okBSMDP = false;


			StEmcPosition* pEmcPosition = new StEmcPosition();
			StEmcGeom* pGeo[4];
			for(int i=0;i<4;i++) {
				if(i!=1) pGeo[i] = StEmcGeom::getEmcGeom(detname[i].Data());
			}
			if(pEmcPosition){
				ok      = pEmcPosition->projTrack(&position, &momentum, grcE, bFld, pGeo[0]->Radius());
				okBSMDE = pEmcPosition->projTrack(&positionBSMDE, &momentumBSMDE, grcE, bFld, pGeo[2]->Radius());
				okBSMDP = pEmcPosition->projTrack(&positionBSMDP, &momentumBSMDP, grcE, bFld, pGeo[3]->Radius());  
			}

			if(ok && okBSMDE && okBSMDP) {
				//cout<<" projection ok"<<endl;
				StSPtrVecEmcPoint& bEmcPoints = pEmcCol->barrelPoints();
				float EmcE = 0.;
				float maxtowerE = -999.;
				float phiDist = -999.;
				float zDist = -999.;
				int nEta = -999;
				int nPhi = -999;
				float minDist = 999.;
				unsigned int maxadc = 0;
				unsigned int maxdsmadc = 0;
				unsigned int softId = -1;

				if(!pGeo[0]) pGeo[0]=StEmcGeom::getEmcGeom(detname[0].Data());
				pGeo[0]->getBin(positionBSMDP.phi(), positionBSMDE.pseudoRapidity(), mod, eta, sub);
				for(StSPtrVecEmcPointIterator it = bEmcPoints.begin(); it!= bEmcPoints.end(); it++) {
					bool associated = false;
					StPtrVecEmcCluster& bEmcClusters = (*it)->cluster(kBarrelEmcTowerId);
					StPtrVecEmcCluster& smdeClusters = (*it)->cluster(kBarrelSmdEtaStripId);
					StPtrVecEmcCluster& smdpClusters = (*it)->cluster(kBarrelSmdPhiStripId);
					if( bEmcClusters.size()==0 || bEmcClusters[0]==NULL) continue;
					for(StPtrVecEmcClusterIterator cIter = bEmcClusters.begin(); cIter != bEmcClusters.end(); cIter++) {
						StPtrVecEmcRawHit& bEmcHits = (*cIter)->hit();
						for(StPtrVecEmcRawHitIterator hIter = bEmcHits.begin(); hIter != bEmcHits.end(); hIter++) {
							if(mod == (Int_t) (*hIter)->module() && eta == (Int_t) (*hIter)->eta() && sub == (Int_t) (*hIter)->sub()) {
								associated = true;
								break;
							}
						}//end of raw hits loop
						if(associated) {
							for(StPtrVecEmcRawHitIterator hitit = bEmcHits.begin(); hitit != bEmcHits.end(); hitit++) {
								if((*hitit)->energy()>maxtowerE) maxtowerE = (*hitit)->energy();
								if((*hitit)->adc()>maxadc) maxadc = (*hitit)->adc();
								softId = (*hitit)->softId(1);
								//cout<<" softId = "<<softId<<endl;
								if(mBemcTriggerSimu->barrelHighTowerAdc(softId)>maxdsmadc) maxdsmadc = mBemcTriggerSimu->barrelHighTowerAdc(softId);
							}
						}
					}//end of cluster loop
					if(associated) {
						EmcE += (*it)->energy();
						float deltaphi = (*it)->position().phi()-positionBSMDP.phi();
						if(deltaphi>=TMath::Pi()) deltaphi -= TMath::TwoPi();
						if(deltaphi<-TMath::Pi()) deltaphi += TMath::TwoPi();
						float rsmdp = pGeo[3]->Radius();
						float pointz = (*it)->position().z();
						float deltaz = pointz - positionBSMDE.z();
						if(sqrt(deltaphi*deltaphi*rsmdp*rsmdp + deltaz*deltaz)<minDist) {
							phiDist = deltaphi;
							zDist = deltaz;
							if(smdeClusters.size()>=1) nEta = smdeClusters[0]->nHits();
							if(smdpClusters.size()>=1) nPhi = smdpClusters[0]->nHits();
							minDist = sqrt(deltaphi*deltaphi*rsmdp*rsmdp + deltaz*deltaz);
						}
					}//end of if
				}//end of bEmcPoints loop
				mParticle.E_rcEnergy[nTracks]      = EmcE;
				mParticle.E_rcnEta[nTracks]        = nEta;
				mParticle.E_rcnPhi[nTracks]        = nPhi;
				mParticle.E_rczDist[nTracks]       = zDist;
				mParticle.E_rcphiDist[nTracks]     = phiDist;
				mParticle.E_rcminDist[nTracks]     = minDist;
				mParticle.E_rcadc0[nTracks]        = maxadc;
				mParticle.E_rcdsmadc[nTracks]      = maxdsmadc;
				mParticle.E_rcEMCEta[nTracks]      = positionBSMDE.pseudoRapidity();
				mParticle.E_rcEMCPhi[nTracks]      = positionBSMDP.phi();
				mParticle.E_rcEnergy0[nTracks]     = maxtowerE;
				mParticle.E_rctowerId[nTracks]     = softId;
			}
		}
		nTracks++;
	}
	mParticle.nTracks = nTracks;
	mTree->Fill();

	return kStOK;
}

StTrackPairInfo* StSingleElectronEff::findBestMatchedGlobal(StMcTrack* mcTrack)
{
	pair<mcTrackMapIter,mcTrackMapIter> mcBounds= mMcTrackMap->equal_range(mcTrack);
	StTrackPairInfo* candTrackPair = 0;  // used for finding the best matched track
	StGlobalTrack* candTrack = 0;
	mcTrackMapIter mcMapIter = mcBounds.first;
	for ( ; mcMapIter != mcBounds.second; ++mcMapIter){
		StTrackPairInfo* assocPair = (*mcMapIter).second;
		StGlobalTrack* globTrack =(StGlobalTrack*) assocPair->partnerTrack();
		if (Debug() > 1) {
			cout << * assocPair << endl;
			cout << "globTrack FitPoints Tpc/FtpcE/W = " << globTrack->fitTraits().numberOfFitPoints(kTpcId) 
				<< "/" << globTrack->fitTraits().numberOfFitPoints(kFtpcEastId)
				<< "/" << globTrack->fitTraits().numberOfFitPoints(kFtpcWestId) << endl;
		}
		if (!globTrack || globTrack->flag()<=0) continue;
		if (globTrack->fitTraits().numberOfFitPoints(kTpcId)>=10 ||
				globTrack->fitTraits().numberOfFitPoints(kFtpcEastId)>=5 ||
				globTrack->fitTraits().numberOfFitPoints(kFtpcWestId)>=5) {
			if (!candTrackPair) {
				candTrackPair = assocPair;
				candTrack = globTrack;
			}
			else if (globTrack->fitTraits().numberOfFitPoints(kTpcId) > candTrack->fitTraits().numberOfFitPoints(kTpcId)) {
				candTrackPair = assocPair;
				candTrack = globTrack;
			}
			else if (globTrack->fitTraits().numberOfFitPoints(kFtpcEastId) > candTrack->fitTraits().numberOfFitPoints(kFtpcEastId)) {
				candTrackPair = assocPair;
				candTrack = globTrack;
			}
			else if (globTrack->fitTraits().numberOfFitPoints(kFtpcWestId) > candTrack->fitTraits().numberOfFitPoints(kFtpcWestId)) {
				candTrackPair = assocPair;
				candTrack = globTrack;
			}

		} // fit points requirement
	}// bounds loop
	return candTrackPair; // Note that candTrack might be zero, for example if only one track is matched and has 9 tpc fit pts.
}
