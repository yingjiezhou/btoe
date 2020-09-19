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

#include "StMcEvent.hh"
#include "StAssociationMaker/StAssociationMaker.h"
#include "StAssociationMaker/StTrackPairInfo.hh"
#include "TVector3.h"
#include "StMcEvent/StMcTpcHit.hh"
#include "StMcTpcHitCollection.hh"

#include "StEvent/StEventTypes.h"
#include "StEventUtilities/StuRefMult.hh"
#include "StEvent/StEventSummary.h"
#include "StEvent/StBTofCollection.h"
#include "StEvent/StBTofHeader.h"
#include "StEvent/StEnumerations.h"
#include "StEvent/StTpcDedxPidAlgorithm.h"
#include "StarClassLibrary/StParticleTypes.hh"

#include "StDetectorDbMaker/StDetectorDbTriggerID.h"

#include "StEmcUtil/projection/StEmcPosition.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/others/emcDetectorName.h"
#include "StEmcRawMaker/defines.h"
#include "StEmcPoint.h"
#include "StEmcCluster.h"
#include "StEmcCollection.h"
#include "StMcVertex.hh"

#include "StPheRecoEff.h"
const int nadc_max = 4;
Double_t massElec = 0.00051099906;

ClassImp(StPheRecoEff);

//__________________________________
StPheRecoEff::StPheRecoEff(char* in, int parentGeantId, const int energy, const std::vector<unsigned int> triggers)
{
    outfile = in;
    parent = parentGeantId; //.. default
    collisionEnergy = energy;
    interesting_triggers = triggers;

    for(int i=0;i<6;i++) {firedTriggersIndices.push_back(-1);};
}
//__________________________________
int StPheRecoEff::Init()
{
    initEmc();

    mFile = new TFile(outfile, "recreate");
    assert(mFile && !mFile->IsZombie());
    mAssoc = (StAssociationMaker*)GetMaker("StAssociationMaker");

    const char* var_sngl = 
        "geantId:p:pt:svx:svy:svz:pgeantId:pp:ppt:"
        "phi:pphi:y:py:eta:peta:label:plabel:gplabel:"
        "rp:rpt:reta:rphi:nfit:ncom:"
        "nmax:vx:vy:vz:dca:chi2:"
        "nDedxPts:dedx:dedx_2:nSigPi:nSigK:nSigP:nSigE:"
	"bemcId:btowAdc0:btowE0:btowE:bemcDistZ:bemcDistPhi:bsmdNEta:bsmdNPhi:btowId:"
        "pr_rp:pr_rpT:stpcx:stpcy:stpcz:gpgeantId:gppt";

    nt_sngl= new TNtuple("nt_sngl", "tracks", var_sngl);

    const char* var_pair = 
        "p1geantId:p1p:p1pt:p1svx:p1svy:p1svz:p1pgeantId:"
        "p1pp:p1ppt:p1eta:p1peta:p1label:p1rp:p1rpt:p1reta:"
        "p1rphi:p1ndedx:p1nfit:p1ncom:p1nmax:p1dca:p1chi2:"
        "p2geantId:p2p:p2pt:p2svx:p2svy:p2svz:p2pgeantId:"
        "p2pp:p2ppt:p2eta:p2peta:p2label:p2rp:p2rpt:p2reta:"
        "p2rphi:p2nfit:p2ncom:p2nmax:p2dca:p2chi2:"
        "vx:vy:vz:massDCA:mcMassPair:pairDCA:pairPT:theta:xpair:ypair:zpair:mult:dist:"
	"p1bemcId:p1btowAdc0:p1btowE0:p1btowE:p1bemcDistZ:p1bemcDistPhi:p1bsmdNEta:p1bsmdNPhi:p1btowId:"
	"p2bemcId:p2btowAdc0:p2btowE0:p2btowE:p2bemcDistZ:p2bemcDistPhi:p2bsmdNEta:p2bsmdNPhi:p2btowId:"
        "p1pr_rp:p1pr_rpT:p2pr_rp:p2pr_rpT:"
        "p1stpcx:p1stpcy:p1stpcz:"
        "p1gpgeantId:p1gppt:"
        "p2gpgeantId:p2gppt";

    nt_pair= new TNtuple("nt_pair", "pairs", var_pair);

    const char* var_mc = "pt:y:eta:geantId:svx:svy:svz:stvx:stvy:stvz:eventGenLabel:pgeantId:ppt:py:peta";
    nt_mc = new TNtuple("nt_mc","mc",var_mc);

    const char* evtVarList = "runId:eventId:mcVx:mcVy:mcVz:vx:vy:vz:vzVpd:posRefMult:negRefMult:"
    "zdc:bbc:nMcTracks:nRTracks:magField:"
    "t0:t1:t2:t3:t4:t5";

    mEventCount = new TNtuple("eventCount", "eventCount", evtVarList);

    return StMaker::Init();
}

//__________________________________
int StPheRecoEff::Make()
{
    StMcEvent* mcEvent = (StMcEvent*)GetDataSet("StMcEvent");
    if (!mcEvent) {
        LOG_WARN << "No StMcEvent" << endm;
        return kStWarn;
    }

    StEvent* event = (StEvent*)GetDataSet("StEvent");
    if (!event) {
        LOG_WARN << "No StEvent" << endm;
        return kStWarn;
    }

    cout<<" parent = "<<parent<<endl;
    if(parent==1) 
        cout<<" .....gamma conversion..... "<<endl;
    else if(parent==149)
        cout<<" .....pi0 dalitz..... "<<endl;
    else if(parent==10017)
        cout<<" .....eta dalitz..... "<<endl;
    else {
        cout<<" ... no such parent as "<<parent<<endl;
        exit(0);
    }

    mField = (float)event->summary()->magneticField();

    mEmcCollection = event->emcCollection();
    if(mEmcCollection) buildEmcIndex();

    // Check if event fired any interesting triggers
    bool event_fired_interesting_triggers = pass_trigger(event);

   // Fill
    int nMcTracks = -1;
    if(event_fired_interesting_triggers)
    {
        cout<<"Good event."<<endl;
        fill_mTuple_MC(mcEvent,nMcTracks);
    }
    else
    {
        cout<<"No interesting triggers. Counting event then skipping."<<endl;
    }
    
    fill_eventCount(mcEvent,event,(float)nMcTracks); 


    return kStOk;
}

//____________________________________
int StPheRecoEff::fill_mTuple_MC(StMcEvent* mcEvent,int& nMcTracks)
{
    nMcTracks = 0;

    float s_nt_nt[100];
    float p_nt_nt[100];
    StSPtrVecMcTrack& trks = mcEvent->tracks();

    cout<<" number of MC tracks is: "<<trks.size()<<endl; 

    int ncommonhits = 0;
    float vtx = mcEvent->primaryVertex()->position().x();
    float vty = mcEvent->primaryVertex()->position().y();
    float vtz = mcEvent->primaryVertex()->position().z();
    StThreeVectorF coll_vtx(vtx,vty,vtz);

    Float_t mc_nt_array[16];

    for (unsigned int i = 0;  i<trks.size(); i++) 
    {

        Reset_t1();
	StMcTrack* t1 = trks[i];

        float t1svx = -9999;
	float t1svy = -9999;
	float t1svz = -9999;
        
	if(t1->startVertex()) 
	{
            t1svx = t1->startVertex()->position().x();
            t1svy = t1->startVertex()->position().y();
            t1svz = t1->startVertex()->position().z();
        }


	// fill mc 
	if(t1->geantId()==1 || t1->geantId()==149 || t1->geantId()==10017)
	{
		float mcpgId =-9999;
		float mcppt = -9999;
		float mcpy = -9999;
		float mcpeta = -9999;
		float mcstvx = -9999;
		float mcstvy = -9999;
		float mcstvz = -9999;

		if(t1->parent())
		{
			mcpgId = t1->parent()->geantId();
			mcppt = t1->parent()->pt();
			mcpy = t1->parent()->rapidity();
			mcpeta = t1->parent()->pseudoRapidity();
		}

		if(t1->stopVertex())
		{
			mcstvx = t1->stopVertex()->position().x();
			mcstvy = t1->stopVertex()->position().y();
			mcstvz = t1->stopVertex()->position().z();
		}

		Int_t i=0;
		mc_nt_array[i++] = t1->pt();
		mc_nt_array[i++] = t1->rapidity();
		mc_nt_array[i++] = t1->pseudoRapidity();
		mc_nt_array[i++] = (Float_t)t1->geantId();
		mc_nt_array[i++] = t1svx;
		mc_nt_array[i++] = t1svy;
		mc_nt_array[i++] = t1svz;
		mc_nt_array[i++] = mcstvx;
		mc_nt_array[i++] = mcstvy;
		mc_nt_array[i++] = mcstvz;
		mc_nt_array[i++] = (Float_t)t1->eventGenLabel();
		mc_nt_array[i++] = mcpgId;
		mc_nt_array[i++] = mcppt;
		mc_nt_array[i++] = mcpy;
		mc_nt_array[i++] = mcpeta;

		nt_mc->Fill(mc_nt_array);
	}


	if(t1->geantId()==parent && t1->eventGenLabel()>1) ++nMcTracks;

        if(!is_correct_decay(t1)) continue;

        int t1geantId = t1->geantId();

	float t1phi = t1->momentum().phi();
	float t1y = t1->momentum().y();
        float t1eta = t1->pseudoRapidity();
	float t1label = t1->eventGenLabel();

        float t1p = t1->momentum().mag();

        float t1pgeantId = -9999;
        float t1pmom = -9999;
        float t1ppt= -9999;
	float t1pphi = -9999;
	float t1parenty = -9999;
        float t1peta = -9999;
        float t1plabel = -9999;

        if(t1->parent()) 
	{
            t1pgeantId = t1->parent()->geantId();
            t1pmom = t1->parent()->momentum().mag();
            t1ppt= t1->parent()->pt();
	    t1pphi = t1->parent()->momentum().phi();
	    t1parenty = t1->parent()->momentum().y();
            t1peta = t1->parent()->pseudoRapidity();
            t1plabel = t1->parent()->eventGenLabel();
        }

        float t1px = t1->momentum().x();
        float t1py = t1->momentum().y();

        float t1pt = sqrt(t1px*t1px+t1py*t1py);

        float t1gpgeantId = -9999;
        float t1gppt= -9999;
        float t1gplabel = -9999;

        if(t1->parent()->parent()) 
	{
            t1gpgeantId = t1->parent()->parent()->geantId();
            t1gppt= t1->parent()->parent()->pt();
            t1gplabel = t1->parent()->parent()->eventGenLabel();
        }

	float t1ndedx = -9999;
        float dedx = -9999;
	float dedx_2 = -9999;
        float nSigPi = -9999;
        float nSigK = -9999;
        float nSigP = -9999;
        float nSigE = -9999;

        const StTrack* t1rcTrack = findPartner(t1, ncommonhits);

        if(t1rcTrack) 
	{
            t1rp = t1rcTrack->geometry()->momentum().mag();
            t1rpt = t1rcTrack->geometry()->momentum().perp();
            t1rpx = t1rcTrack->geometry()->momentum().x();
            t1rpy = t1rcTrack->geometry()->momentum().y();
            t1rpz = t1rcTrack->geometry()->momentum().z();
            t1reta = t1rcTrack->geometry()->momentum().pseudoRapidity();
            t1rphi = t1rcTrack->geometry()->momentum().phi();
            t1nfit = t1rcTrack->fitTraits().numberOfFitPoints(kTpcId);
            t1nmax = t1rcTrack->numberOfPossiblePoints(kTpcId);
            t1ncom =ncommonhits; 
            t1key = t1rcTrack->key();
            t1_stpcx = t1rcTrack->detectorInfo()->firstPoint().x();
            t1_stpcy = t1rcTrack->detectorInfo()->firstPoint().y();
            t1_stpcz = t1rcTrack->detectorInfo()->firstPoint().z();

            //...find the DCA of the track w.r.t. the zvtx 
            t1dca = t1rcTrack->geometry()->helix().distance(coll_vtx);
            t1chi2 = t1rcTrack->fitTraits().chi2(0);

	    // dedx info
            static StTpcDedxPidAlgorithm aplus;
            static StPionPlus* Pion = StPionPlus::instance();
            static StKaonPlus* Kaon = StKaonPlus::instance();
            static StProton* Proton = StProton::instance();
            static StElectron* Electron = StElectron::instance();
            const StParticleDefinition* prtcl = t1rcTrack->pidTraits(aplus);
            if (prtcl) 
            {
                t1ndedx = aplus.traits()->numberOfPoints();
                dedx = aplus.traits()->mean();
                nSigPi = aplus.numberOfSigma(Pion);
                nSigK = aplus.numberOfSigma(Kaon);
                nSigP = aplus.numberOfSigma(Proton);
                nSigE = aplus.numberOfSigma(Electron);
            }

	    StDedxPidTraits* tpc_pid = findDedxPidTraits(t1rcTrack);
	    if(tpc_pid) dedx_2 = tpc_pid->mean();

	    // .. emc
	    int bemcId = -1; 
	    int adc0 = -9999; 
	    float e[5]; 
	    float dist[4]; 
	    int nhit[2]; 
	    int ntow[3];
	    for(int i=0;i<5;i++) { e[i] = 0.; }
	    for(int i=0;i<4;i++) { dist[i] = 1.e9; }
	    for(int i=0;i<2;i++) { nhit[i] = 0; }
	    for(int i=0;i<3;i++) { ntow[i] = -1; }

	    getBEMC(t1rcTrack, &bemcId, &adc0, e, dist, nhit, ntow);

	    p1bemcId = (float)bemcId;
	    p1btowAdc0 = (float)adc0;
	    p1btowE0 = e[0];
	    p1btowE = e[1];
	    p1bemcDistZ = dist[0];
	    p1bemcDistPhi = dist[1];
	    p1bsmdNEta = nhit[0];
	    p1bsmdNPhi = nhit[1];
	    p1btowId = (ntow[0]<=0 || ntow[0]>4800) ? -1 : (float)ntow[0];
	    // .. end emc

            StPrimaryTrack* t1_pr_trk = (StPrimaryTrack*)(t1rcTrack->node()->track(primary));
            if(t1_pr_trk){
                t1pr_rp = t1_pr_trk->geometry()->momentum().mag();
                t1pr_rpT = t1_pr_trk->geometry()->momentum().perp();
            }
        }

        float rc = sqrt(t1svx*t1svx + t1svy*t1svy);
        if(fabs(vtz)>50 || fabs(t1eta)>1.0 || rc>200) continue;

        int ii = 0;
        s_nt_nt[ii++] = t1geantId;
        s_nt_nt[ii++] = t1p;
        s_nt_nt[ii++] = t1pt;
        s_nt_nt[ii++] = t1svx;
        s_nt_nt[ii++] = t1svy;
        s_nt_nt[ii++] = t1svz;
        s_nt_nt[ii++] = t1pgeantId;
        s_nt_nt[ii++] = t1pmom;
        s_nt_nt[ii++] = t1ppt;
	s_nt_nt[ii++] = t1phi;
	s_nt_nt[ii++] = t1pphi;
	s_nt_nt[ii++] = t1y;
	s_nt_nt[ii++] = t1parenty;
        s_nt_nt[ii++] = t1eta;
        s_nt_nt[ii++] = t1peta;
        s_nt_nt[ii++] = t1label;
        s_nt_nt[ii++] = t1plabel;
        s_nt_nt[ii++] = t1gplabel;
        s_nt_nt[ii++] = t1rp;
        s_nt_nt[ii++] = t1rpt;
        s_nt_nt[ii++] = t1reta;
        s_nt_nt[ii++] = t1rphi;
        s_nt_nt[ii++] = t1nfit;
        s_nt_nt[ii++] = t1ncom;
        s_nt_nt[ii++] = t1nmax;
        s_nt_nt[ii++] = vtx;
        s_nt_nt[ii++] = vty;
        s_nt_nt[ii++] = vtz;
        s_nt_nt[ii++] = t1dca;
        s_nt_nt[ii++] = t1chi2;
	s_nt_nt[ii++] = t1ndedx;
	s_nt_nt[ii++] = dedx;
	s_nt_nt[ii++] = dedx_2;
	s_nt_nt[ii++] = nSigPi;
	s_nt_nt[ii++] = nSigK;
	s_nt_nt[ii++] = nSigP;
	s_nt_nt[ii++] = nSigE;
	s_nt_nt[ii++] = p1bemcId;
	s_nt_nt[ii++] = p1btowAdc0;
	s_nt_nt[ii++] = p1btowE0;
	s_nt_nt[ii++] = p1btowE;
	s_nt_nt[ii++] = p1bemcDistZ;
	s_nt_nt[ii++] = p1bemcDistPhi;
	s_nt_nt[ii++] = p1bsmdNEta;
	s_nt_nt[ii++] = p1bsmdNPhi;
	s_nt_nt[ii++] = p1btowId;
        s_nt_nt[ii++] = t1pr_rp;
        s_nt_nt[ii++] = t1pr_rpT;
        s_nt_nt[ii++] = t1_stpcx;
        s_nt_nt[ii++] = t1_stpcy;
        s_nt_nt[ii++] = t1_stpcz;
        s_nt_nt[ii++] = t1gpgeantId;
        s_nt_nt[ii++] = t1gppt;

        nt_sngl->Fill(s_nt_nt);


        //.. now start pairing ...

        for(unsigned int j = 0; j<trks.size(); j++) {
            if(i==j) continue; //.. same track

            Reset_t2();

            StMcTrack* t2 = trks[j];

            float t2svx, t2svy, t2svz;
            if(t2->startVertex()) {
                t2svx = t2->startVertex()->position().x();
                t2svy = t2->startVertex()->position().y();
                t2svz = t2->startVertex()->position().z();
            }

            if(!is_correct_decay(t2)) continue;

            if(!(t1->startVertex() == t2->startVertex() && 
                        t1->parent()->geantId()==t2->parent()->geantId())) continue;


	    StLorentzVectorD lVecTemp(t1->fourMomentum());
	    lVecTemp += t2->fourMomentum();

	    mcMassPair = lVecTemp.m();

            int t2geantId = t2->geantId();

            float t2eta = t2->pseudoRapidity();

            float t2p = t2->momentum().mag();

            float t2pgeantId = -9999;
            float t2pmom = -9999;
            float t2ppt= -9999;
            float t2peta = -9999;
            if(t2->parent()) {
                t2pgeantId = t2->parent()->geantId();
                t2pmom = t2->parent()->momentum().mag();
                t2ppt= t2->parent()->pt();
                t2peta = t2->parent()->pseudoRapidity();
            }

            float t2gpgeantId = -9999;
            float t2gppt= -9999;
            float t2plabel = -9999;
            if(t2->parent()->parent()) {
                t2gpgeantId = t2->parent()->parent()->geantId();
                t2gppt= t2->parent()->parent()->pt();
                t2plabel = t2->parent()->parent()->eventGenLabel();
            }

            float t2px = t2->momentum().x();
            float t2py = t2->momentum().y();

            float t2pt = sqrt(t2px*t2px+t2py*t2py);

            const StTrack* t2rcTrack = findPartner(t2, ncommonhits);

            StThreeVectorF posDCA(-9999, -9999, -9999);
            if(t2rcTrack) {
                t2rp = t2rcTrack->geometry()->momentum().mag();
                t2rpt = t2rcTrack->geometry()->momentum().perp();
                t2rpx = t2rcTrack->geometry()->momentum().x();
                t2rpy = t2rcTrack->geometry()->momentum().y();
                t2rpz = t2rcTrack->geometry()->momentum().z();
                t2reta = t2rcTrack->geometry()->momentum().pseudoRapidity();
                t2rphi = t2rcTrack->geometry()->momentum().phi();
                t2nfit = t2rcTrack->fitTraits().numberOfFitPoints(kTpcId);
                t2nmax = t2rcTrack->numberOfPossiblePoints(kTpcId);
                t2ncom =ncommonhits; 
                t2key = t2rcTrack->key();

                //...find the DCA of the track w.r.t. the zvtx 
                t2dca = t2rcTrack->geometry()->helix().distance(coll_vtx);
                t2chi2 = t2rcTrack->fitTraits().chi2(0);

                StPrimaryTrack* t2_pr_trk = (StPrimaryTrack*)(t2rcTrack->node()->track(primary));
                if(t2_pr_trk){
                    t2pr_rp = t2_pr_trk->geometry()->momentum().mag();
                    t2pr_rpT = t2_pr_trk->geometry()->momentum().perp();
                }

                if(t1rcTrack) {
                    //.. calculate mass, pairDCA, eta
                    StPhysicalHelixD helix1 = t1rcTrack->geometry()->helix();
                    StPhysicalHelixD helix2 = t2rcTrack->geometry()->helix();
                    pair<double,double> pathLength = helix1.pathLengths(helix2);

                    pairDCA = (helix1.at(pathLength.first) - helix2.at(pathLength.second)).mag();
                    // Get the momentum of each track at the point of closest approach
                    StThreeVectorD p1DCA = helix1.momentumAt(pathLength.first, (mField/10.)*tesla);
                    StThreeVectorD p2DCA = helix2.momentumAt(pathLength.second, (mField/10.)*tesla);
                    thetaDCA = acos(p1DCA.dot(p2DCA)/p1DCA.mag()/p2DCA.mag());


                    StThreeVectorF v1(helix1.at(pathLength.first).x(),
                            helix1.at(pathLength.first).y(),
                            helix1.at(pathLength.first).z());
                    // v2 is a vector from origin to the point of closest approach on track 2
                    StThreeVectorF v2(helix2.at(pathLength.second).x(),
                            helix2.at(pathLength.second).y(),
                            helix2.at(pathLength.second).z());

                    posDCA = (v1 + ((v2-v1)*0.5));

                    StLorentzVectorD pathOne;
                    StLorentzVectorD pathTwo;
                    pathOne.setPx(p1DCA.x());
                    pathOne.setPy(p1DCA.y());
                    pathOne.setPz(p1DCA.z());
                    pathOne.setE(p1DCA.massHypothesis(massElec));

                    pathTwo.setPx(p2DCA.x());
                    pathTwo.setPy(p2DCA.y());
                    pathTwo.setPz(p2DCA.z());
                    pathTwo.setE(p2DCA.massHypothesis(massElec));

                    massPair = (pathOne + pathTwo).m();
                    pairPT = (pathOne + pathTwo).perp();

                    //.. calculate the distance between the last hits of the two tracks ..
                    StPtrVecMcTpcHit hits1 = t1->tpcHits();
                    StPtrVecMcTpcHit hits2 = t2->tpcHits();

                    int n1 = hits1.size();
                    int n2 = hits2.size();
                    StThreeVectorF lastHits_1 = hits1[n1-1]->position();
                    StThreeVectorF lastHits_2 = hits2[n2-1]->position();

                    dist = (lastHits_1-lastHits_2).mag();

		    // .. emc
		    int bemcId = -1; 
		    int adc0 = -9999; 
		    float e[5]; 
		    float dist[4]; 
		    int nhit[2]; 
		    int ntow[3];
		    for(int i=0;i<5;i++) { e[i] = 0.; }
		    for(int i=0;i<4;i++) { dist[i] = 1.e9; }
		    for(int i=0;i<2;i++) { nhit[i] = 0; }
		    for(int i=0;i<3;i++) { ntow[i] = -1; }

		    getBEMC(t2rcTrack, &bemcId, &adc0, e, dist, nhit, ntow);

		    p2bemcId = bemcId;
		    p2btowAdc0 = adc0;
		    p2btowE0 = e[0];
		    p2btowE = e[1];
		    p2bemcDistZ = dist[0];
		    p2bemcDistPhi = dist[1];
		    p2bsmdNEta = nhit[0];
		    p2bsmdNPhi = nhit[1];
		    p2btowId = (ntow[0]<=0 || ntow[0]>4800) ? -1 : (float)ntow[0];
		    // .. end emc

                }
            }

            //.. t2 should be reconstructed ...
            //if(!(t2nfit>20 && t2nfit/t2nmax>0.52 && t2ncom>15)) continue;

            int ii = 0;
            p_nt_nt[ii++] = t1geantId;
            p_nt_nt[ii++] = t1p;
            p_nt_nt[ii++] = t1pt;
            p_nt_nt[ii++] = t1svx;
            p_nt_nt[ii++] = t1svy;
            p_nt_nt[ii++] = t1svz;
            p_nt_nt[ii++] = t1pgeantId;
            p_nt_nt[ii++] = t1pmom;
            p_nt_nt[ii++] = t1ppt;
            p_nt_nt[ii++] = t1eta;
            p_nt_nt[ii++] = t1peta;
            p_nt_nt[ii++] = t1gplabel;
            p_nt_nt[ii++] = t1rp;
            p_nt_nt[ii++] = t1rpt;
            p_nt_nt[ii++] = t1reta;
            p_nt_nt[ii++] = t1rphi;
            p_nt_nt[ii++] = t1ndedx;
            p_nt_nt[ii++] = t1nfit;
            p_nt_nt[ii++] = t1ncom;
            p_nt_nt[ii++] = t1nmax;
            p_nt_nt[ii++] = t1dca;
            p_nt_nt[ii++] = t1chi2;
            p_nt_nt[ii++] = t2geantId;
            p_nt_nt[ii++] = t2p;
            p_nt_nt[ii++] = t2pt;
            p_nt_nt[ii++] = t2svx;
            p_nt_nt[ii++] = t2svy;
            p_nt_nt[ii++] = t2svz;
            p_nt_nt[ii++] = t2pgeantId;
            p_nt_nt[ii++] = t2pmom;
            p_nt_nt[ii++] = t2ppt;
            p_nt_nt[ii++] = t2eta;
            p_nt_nt[ii++] = t2peta;
            p_nt_nt[ii++] = t2plabel;
            p_nt_nt[ii++] = t2rp;
            p_nt_nt[ii++] = t2rpt;
            p_nt_nt[ii++] = t2reta;
            p_nt_nt[ii++] = t2rphi;
            p_nt_nt[ii++] = t2nfit;
            p_nt_nt[ii++] = t2ncom;
            p_nt_nt[ii++] = t2nmax;
            p_nt_nt[ii++] = t2dca;
            p_nt_nt[ii++] = t2chi2;
            p_nt_nt[ii++] = vtx;
            p_nt_nt[ii++] = vty;
            p_nt_nt[ii++] = vtz;
            p_nt_nt[ii++] = massPair;
	    p_nt_nt[ii++] = mcMassPair;
            p_nt_nt[ii++] = pairDCA;
            p_nt_nt[ii++] = pairPT;
            p_nt_nt[ii++] = thetaDCA;
            p_nt_nt[ii++] = posDCA.x();
            p_nt_nt[ii++] = posDCA.y();
            p_nt_nt[ii++] = posDCA.z();
	    p_nt_nt[ii++] = trks.size();
	    p_nt_nt[ii++] = dist;
	    p_nt_nt[ii++] = p1bemcId;
	    p_nt_nt[ii++] = p1btowAdc0;
	    p_nt_nt[ii++] = p1btowE0;
	    p_nt_nt[ii++] = p1btowE;
	    p_nt_nt[ii++] = p1bemcDistZ;
	    p_nt_nt[ii++] = p1bemcDistPhi;
	    p_nt_nt[ii++] = p1bsmdNEta;
	    p_nt_nt[ii++] = p1bsmdNPhi;
	    p_nt_nt[ii++] = p1btowId;
	    p_nt_nt[ii++] = p2bemcId;
	    p_nt_nt[ii++] = p2btowAdc0;
	    p_nt_nt[ii++] = p2btowE0;
	    p_nt_nt[ii++] = p2btowE;
	    p_nt_nt[ii++] = p2bemcDistZ;
	    p_nt_nt[ii++] = p2bemcDistPhi;
	    p_nt_nt[ii++] = p2bsmdNEta;
	    p_nt_nt[ii++] = p2bsmdNPhi;
	    p_nt_nt[ii++] = p2btowId;
	    p_nt_nt[ii++] = t1pr_rp;
	    p_nt_nt[ii++] = t1pr_rpT;
            p_nt_nt[ii++] = t2pr_rp;
            p_nt_nt[ii++] = t2pr_rpT;
            p_nt_nt[ii++] = t1_stpcx;
            p_nt_nt[ii++] = t1_stpcy;
            p_nt_nt[ii++] = t1_stpcz;
            p_nt_nt[ii++] = t1pgeantId;
            p_nt_nt[ii++] = t1gppt;
            p_nt_nt[ii++] = t2pgeantId;
            p_nt_nt[ii++] = t2gppt;

            nt_pair->Fill(p_nt_nt);
        }
    }

    return kStOk;
}
//____________________________________
int StPheRecoEff::fill_eventCount(StMcEvent* mcEvt, StEvent* evt,float nMcTracks)
{   
    cout<<"Taking event counts..."<<endl;
    float vars[30];
    
//    if(!evt->btofCollection()) cout<<"No btofCollection."<<endl;
//    if(evt->btofCollection() && !evt->btofCollection()->tofHeader()) cout<<"No tofHeader."<<endl;
//    if(!mcEvt->primaryVertex()) cout<<"No mcPrimaryVertex."<<endl;
//    if(!evt->runInfo()) cout<<"No runInfo."<<endl;
//    if(!evt->summary()) cout<<"No event summary."<<endl;
    
    float vpdVz = -999;
    StBTofHeader* tofheader = 0;
    if(evt->btofCollection())  tofheader = evt->btofCollection()->tofHeader();
    if(tofheader) vpdVz = tofheader->vpdVz();
    
    int i = 0;
    vars[i++] = (float)evt->runId();
    vars[i++] = (float)evt->id();
    vars[i++] = (float)mcEvt->primaryVertex()->position().x();
    vars[i++] = (float)mcEvt->primaryVertex()->position().y();
    vars[i++] = (float)mcEvt->primaryVertex()->position().z();
    vars[i++] = (float)evt->primaryVertex()->position().x();
    vars[i++] = (float)evt->primaryVertex()->position().y();
    vars[i++] = (float)evt->primaryVertex()->position().z();
    vars[i++] = vpdVz;
    vars[i++] = (float)uncorrectedNumberOfPositivePrimaries(*evt);
    vars[i++] = (float)uncorrectedNumberOfNegativePrimaries(*evt);
    vars[i++] = (float)evt->runInfo()->zdcCoincidenceRate();
    vars[i++] = (float)evt->runInfo()->bbcCoincidenceRate();
    vars[i++] = (float)nMcTracks;
    vars[i++] = -1.0;
    vars[i++] = (float)evt->summary()->magneticField()/10;
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
bool StPheRecoEff::pass_trigger(StEvent* evt)
{
    cout<<"Checking triggers..."<<endl;
    bool interesting_event = false;
    
    const StTriggerId* st_trgid = evt->triggerIdCollection()->nominal();
    
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
//________________________________________________
const StTrack* StPheRecoEff::findPartner(StMcTrack* mcTrack, int& maxCommonTpcHits) 
{//..StMcTrack find partner from the StTracks
    maxCommonTpcHits = 0;

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

//______________________________________________________
int StPheRecoEff::Finish()
{
    mFile->Write();
    mFile->Close();
    return kStOk;
}
//______________________________________________________
StDedxPidTraits* StPheRecoEff::findDedxPidTraits(const StTrack* track)
{
  StDedxPidTraits* pid=0;
  StPtrVecTrackPidTraits traits = track->pidTraits(kTpcId);
  
  for (UInt_t i = 0; i < traits.size(); i++) {
    pid = dynamic_cast<StDedxPidTraits*>(traits[i]);
    if (pid && pid->method() == kTruncatedMeanId) break;
  }
  return pid;
} 

//______________________________
bool StPheRecoEff::is_correct_decay(StMcTrack* t)
{
    //.. check to make sure it's the right decay ....
    if(t->geantId()!=2 && t->geantId()!=3) return false;
    if(!t->parent() || !t->parent()->stopVertex()) return false;
    if(t->parent()->geantId()!=parent && (t->parent()->parent() && t->parent()->parent()->geantId()!=parent)) return false;
    int ndaughter = t->parent()->stopVertex()->numberOfDaughters();

    int corr_daughter = 0;

    for(int i = 0; i<ndaughter; i++) 
    {
        StMcTrack* trk = t->parent()->stopVertex()->daughter(i);
        int gid = trk->geantId();

        if((parent==149 || parent==10017) && (gid==2 || gid==3 || gid==1))  
            corr_daughter++; //.. dalitz

        if(parent==1 && (gid==2 || gid==3))  //.. conversion
            corr_daughter++;
    }

    Bool_t correct_deacy = kFALSE;

    if(parent==1 && corr_daughter==2 && ndaughter==2) correct_deacy = kTRUE;
    else if((parent==149 || parent==10017) && (corr_daughter==3 && ndaughter==3)) correct_deacy = kTRUE; // pi0->\gamma e+ e-
    else if((parent==149 || parent==10017) && (corr_daughter==2 && ndaughter==2)) correct_deacy = kTRUE; // pi0-> \gamma \gamma 

    return correct_deacy;
}

//-----------------------------------------------------------------------
bool StPheRecoEff::getBEMC(const StTrack *t, int *id, int *adc, float *ene, float *d, int *nep, int *towid) {
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
          if((int)(*hitit)->adc()>(*adc)) *adc=(*hitit)->adc();
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
void StPheRecoEff::initEmc() {
  mEmcPosition = new StEmcPosition();
  for(int i=0;i<4;i++) {
    mEmcGeom[i] = StEmcGeom::getEmcGeom(detname[i].Data());
  }
}
//-----------------------------------------------------------------------
void StPheRecoEff::buildEmcIndex() {
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
//_________________________
void StPheRecoEff:: Reset_t1()
{
    t1_stpcx = -9999;
    t1_stpcy = -9999;
    t1_stpcz = -9999;
    t1rp = -9999;
    t1pr_rp = -9999;
    t1pr_rpT = -9999;
    t1rpt = -9999;
    t1rpx = -9999;
    t1rpy = -9999;
    t1rpz = -9999;
    t1reta = -9999;
    t1rphi = -9999;
    t1nfit = -9999;
    t1ndedx = -9999;
    t1nmax = -9999;
    t1ncom = -9999;
    t1key = -9999;
    t1dca = -9999;
    t1chi2 = -9999;
    p1bemcId = -9999;
    p1btowAdc0 = -9999;
    p1btowE0 = -9999;
    p1btowE = -9999;
    p1bemcDistZ = -9999;
    p1bemcDistPhi = -9999;
    p1bsmdNEta = -9999;
    p1bsmdNPhi = -9999;
    p1btowId = -9999;
}
//______
void StPheRecoEff:: Reset_t2()
{
    t2pr_rp = -9999;
    t2pr_rpT = -9999;	
    t2rp = -9999;
    t2rpt = -9999;
    t2rpx = -9999;
    t2rpy = -9999;
    t2rpz = -9999;
    t2reta = -9999;
    t2rphi = -9999;
    t2nfit = -9999;
    t2nmax = -9999;
    t2ncom = -9999;
    t2key = -9999;
    t2dca = -9999;
    t2chi2 = -9999;
    p2bemcId = -9999;
    p2btowAdc0 = -9999;
    p2btowE0 = -9999;
    p2btowE = -9999;
    p2bemcDistZ = -9999;
    p2bemcDistPhi = -9999;
    p2bsmdNEta = -9999;
    p2bsmdNPhi = -9999;
    p2btowId = -9999;
    pairDCA = -9999;
    thetaDCA = -9999;
    massPair = -9999;
    mcMassPair = -9999;
    pairPT = -9999;
    dist = -9999;
}

//___________________________________________
