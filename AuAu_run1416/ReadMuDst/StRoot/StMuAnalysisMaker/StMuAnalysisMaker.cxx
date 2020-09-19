/*!
 * \class  StMuAnalysisMaker
 * \brief  A typical Analysis Class for MuDst
 * \author Wei-Ming Zhang, KSU, Mar 2004 
 *
 * This is an example of a maker to perform analysis using MuDst.
 *
 * $Id: StMuAnalysisMaker.cxx,v 1.1 2004/08/10 16:09:11 perev Exp $
 * -------------------------------------------------------------------------
 * $Log: StMuAnalysisMaker.cxx,v $
 * Revision 1.1  2004/08/10 16:09:11  perev
 * new GridCollector stuff
 *
 * -------------------------------------------------------------------------
 */
//
//  Include header files. 
#include "TFile.h"
#include "StMessMgr.h"
#include "TH1.h"
#include "TTree.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuMcTrack.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuDebug.h"
#include "StMuAnalysisMaker.h"
//
//  Prototype 
void muEventInfo(StMuEvent&, const int&);

ClassImp(StMuAnalysisMaker)

// The constructor. Initialize data members here.
StMuAnalysisMaker::StMuAnalysisMaker(const Char_t *name,char const * outfile) : StMaker(name)
{ mEventCounter = 0; mFile = 0; mFileName = outfile;}

StMuAnalysisMaker::~StMuAnalysisMaker() { /* noop */ }
//
//  Called once at the beginning.
Int_t StMuAnalysisMaker::Init()
{
    //  Output file and histogram booking
//    mFileName = outfile;
    mFile =  new TFile(mFileName.Data(), "RECREATE");
    mFile->cd();
    Signal_tree = new TTree("Signal_tree","Signal Tree");
    Signal_tree->Branch("sig_p",&sig_p,"sig_p/F");
    Signal_tree->Branch("sig_vz",&sig_vz,"sig_vz/F");
    Signal_tree->Branch("sig_pt",&sig_pt,"sig_pt/F");
    Signal_tree->Branch("sig_dcaxy",&sig_dcaxy,"sig_dcaxy/F");
    Signal_tree->Branch("sig_dca",&sig_dca,"sig_dca/F");
    Signal_tree->Branch("sig_dcaz",&sig_dcaz,"sig_dcaz/F");
    Signal_tree->Branch("sig_eta",&sig_eta,"sig_eta/F");
    Signal_tree->Branch("sig_phi",&sig_phi,"sig_phi/F");
    Signal_tree->Branch("sig_hft",&sig_hft,"sig_hft/F");
    Signal_tree->Branch("sig_phi2",&sig_phi2,"sig_phi2/F");
    Signal_tree->Branch("sig_charge",&sig_charge,"sig_charge/F");
    Signal_tree->Branch("sig_id",&sig_id,"sig_id/F");
    Signal_tree->Branch("sig_isiso",&sig_isiso,"sig_isiso/F");
    Signal_tree->Branch("event_centrality",&event_centrality,"event_centrality/F");
    Signal_tree->Branch("sig_yloc",&sig_yloc,"sig_yloc/F");
    Signal_tree->Branch("event_centrality",&event_centrality,"event_centrality/F");
    Signal_tree->Branch("sig_head",&sig_head,"sig_head/F");
    Signal_tree->Branch("sig_parentid",&sig_parentid,"sig_parentid/F");
    Signal_tree->Branch("sig_gparentid",&sig_gparentid,"sig_gparentid/F");
    Signal_tree->Branch("sig_ggparentid",&sig_ggparentid,"sig_ggparentid/F");
    Signal_tree->Branch("sig_parentpt",&sig_parentpt,"sig_parentpt/F");
    Signal_tree->Branch("sig_gparentpt",&sig_gparentpt,"sig_gparentpt/F");
    Signal_tree->Branch("sig_ggparentpt",&sig_ggparentpt,"sig_ggparentpt/F");
    Signal_tree->Branch("sig_parentphi",&sig_parentphi,"sig_parentphi/F");
    Signal_tree->Branch("sig_gparentphi",&sig_gparentphi,"sig_gparentphi/F");
    Gen_tree = new TTree("Gen_tree","Gen Tree");
    Gen_tree->Branch("gen_p",&gen_p,"gen_p/F");
    Gen_tree->Branch("gen_pt",&gen_pt,"gen_pt/F");
    Gen_tree->Branch("gen_dcaxy",&gen_dcaxy,"gen_dcaxy/F");
    Gen_tree->Branch("gen_dca",&gen_dca,"gen_dca/F");
    Gen_tree->Branch("gen_eta",&gen_eta,"gen_eta/F");
    Gen_tree->Branch("gen_phi",&gen_phi,"gen_phi/F");
    Gen_tree->Branch("gen_phi2",&gen_phi2,"gen_phi2/F");
    Gen_tree->Branch("gen_id",&gen_id,"gen_id/F");
    Gen_tree->Branch("event_centrality",&gen_event_centrality,"event_centrality/F");
    Gen_tree->Branch("gen_vx",&gen_vx,"gen_vx/F");
    Gen_tree->Branch("gen_vy",&gen_vy,"gen_vy/F");
    Gen_tree->Branch("gen_vz",&gen_vz,"gen_vz/F");
    Gen_tree->Branch("gen_head",&gen_head,"gen_head/F");
    Gen_tree->Branch("gen_parentid",&gen_parentid,"gen_parentid/F");
    Gen_tree->Branch("gen_gparentid",&gen_gparentid,"gen_gparentid/F");
    Gen_tree->Branch("gen_ggparentid",&gen_ggparentid,"gen_ggparentid/F");
    Gen_tree->Branch("gen_parentpt",&gen_parentpt,"gen_parentpt/F");
    Gen_tree->Branch("gen_gparentpt",&gen_gparentpt,"gen_gparentpt/F");
    Gen_tree->Branch("gen_ggparentpt",&gen_ggparentpt,"gen_ggparentpt/F");
    
    return StMaker::Init();
}
//
//  Called every event after Make(). 
void StMuAnalysisMaker::Clear(Option_t *opt)
{
    StMaker::Clear();
}
//
//  Called once at the end.
Int_t StMuAnalysisMaker::Finish()
{
//  Summarize the run.
    cout << "StMuAnalysisMaker::Finish()\n";
    cout << "\tProcessed " << mEventCounter << " events." << endl;
//
//  Output histograms
//    mFile =  new TFile(mFileName.Data(), "RECREATE");
    mFile->cd();

    cout << "\tHistograms will be stored in file '"
	 <<  mFileName.Data() << "'" << endl;
    Signal_tree->Write();
    Gen_tree->Write();
//  Write histos to file and close it.
    if( mFile){
	mFile->Write();  
	mFile->Close();
    }

    return kStOK;
}
//
//  This method is called every event.
Int_t StMuAnalysisMaker::Make()
{
    mEventCounter++;  // increase counter

    DEBUGVALUE2(mEventCounter);
//  Get MuDst
    StMuDst* mu; 
    mu =  (StMuDst*) GetInputDS("MuDst"); 
    DEBUGVALUE2(mu);
    if (!mu){
	  gMessMgr->Warning() << "StMuAnalysisMaker::Make : No MuDst" << endm;
          return kStOK;        // if no event, we're done
    }
//  Check StMuEvent branch
    StMuEvent* muEvent;
    muEvent = (StMuEvent*) mu->event();

    int refMult = muEvent->grefmult();
    int centrality = get_centrality(refMult);
    if (centrality<0 || centrality>8) return kStOK;

    StThreeVectorF pVtx = muEvent->primaryVertexPosition();
    if (fabs(pVtx.z()) > 6.0) return kStOK;
    int index2McTrack       [100000];
    for(int i=0;i<100000;i++) index2McTrack[i] = -1;

// 
//  Check track branches
    StMuTrack* muTrack; 
    int nTracks;
    nTracks= mu->globalTracks()->GetEntries();
    TClonesArray *mcTracks = mu->mcArray(MCTrack);
    int nMcTracks = mcTracks->GetEntriesFast();

    for(int i=0;i<nMcTracks;i++) {
	StMuMcTrack *mcT = (StMuMcTrack *)mcTracks->UncheckedAt(i);
	if(!mcT) continue;
	int id = mcT->Id();
	int gId = mcT->GePid();
	if(!(gId==3 || gId==2))continue;
	index2McTrack[id] = i;
	fillGenTree(mcT,pVtx);
    }
    for (int l=0; l<nTracks; l++) {
	muTrack =  (StMuTrack*) mu->globalTracks(l);
	if(!muTrack) continue;
	const StThreeVectorF mom = muTrack->momentum();
	const float pt = mom.perp();
	const float eta = mom.pseudoRapidity();
	const float phi = mom.phi();
	if(pt<0.2 || fabs(eta)>1.0) continue;
	if(!accept(muTrack)) continue;
	int idTruth = muTrack->idTruth();
	if(idTruth<0) {std::cout << "id = " << idTruth << ": pt = " << pt << ": eta = " << eta << std::endl; continue;}
	int qTruth = muTrack->qaTruth();
	int index2Mc = index2McTrack[idTruth];
	if(index2Mc>=0) {
	    StMuMcTrack *mcT = (StMuMcTrack *)mcTracks->UncheckedAt(index2Mc);
	    if(mcT) {
		int idVtx = mcT->IdVx();
		if (idVtx!=1) continue;
		int gId = mcT->GePid();
		if(!(gId==2 || gId==3))continue;
		fillTree(muTrack,mcT,pVtx,centrality);
	    }
	}
    }



    return kStOK;
}
//
//  A simple track filter
bool StMuAnalysisMaker::accept(StMuTrack* track)
{
//  check for positive flags.
    return track->dcaGlobal().mag()<1.5 && (int)track->nHitsFit()>20;
}
void StMuAnalysisMaker::fillGenTree(StMuMcTrack* tmc,StThreeVectorF pVtx){
    StThreeVectorF const pMom = tmc->Pxyz();
    float pt = pMom.perp();
    float ptot = pMom.mag();
    int charge=0;
    gen_id = tmc->GePid();
    if(gen_id==3)charge=-1;
    else if(gen_id==2)charge=1;
    else charge=0;
    gen_pt = pt;
    gen_p = ptot;
    gen_eta = pMom.pseudoRapidity();
    gen_phi = pMom.phi();
    gen_phi2 = TMath::Pi()+TMath::ATan2(-pMom.y(),-pMom.x());
    int parentGid=0;
    int gparentGid=0;
    int ggparentGid=0;
    float parentPt=0;
    float gparentPt=0;
    float ggparentPt=0;
    /*if(tmc->parentId() == tmc->Id()){
        parentGid  = tmc->GePid();
    }
    else if(tmc->parentId() != Pico::USHORTMAX){
        StMuMcTrack *mcParentTrk = (StMuMcTrack*)mcTracks->UncheckedAt(tmc->parentId()-1);
        parentGid  = mcParentTrk->GePid();
        parentPt  = mcParentTrk->Mom().perp();
        if(mcParentTrk->parentId() != Pico::USHORTMAX && mcParentTrk->parentId() != mcParentTrk->Id()){
            StMuMcTrack *mcgParentTrk = (StMuMcTrack*)mcTracks->UncheckedAt(mcParentTrk->parentId()-1);
            gparentGid  = mcgParentTrk->GePid();
            gparentPt  = mcgParentTrk->Mom().perp();
            if(mcgParentTrk->parentId() != Pico::USHORTMAX && mcgParentTrk->parentId() != mcgParentTrk->Id()){
                StMuMcTrack *mcggParentTrk = (StMuMcTrack*)mcTracks->UncheckedAt(mcgParentTrk->parentId()-1);
                ggparentGid  = mcggParentTrk->GePid();
                ggparentPt  = mcggParentTrk->Mom().perp();

            }
        }
	}*/
    gen_parentpt = parentPt;
    gen_gparentpt = gparentPt;
    gen_ggparentpt = ggparentPt;
    gen_parentid = parentGid;
    gen_gparentid = gparentGid;
    gen_ggparentid = ggparentGid;
    Gen_tree->Fill();
}
void StMuAnalysisMaker::fillTree(StMuTrack* tp,StMuMcTrack *tmc,StThreeVectorF pVtx, int centrality){
    StThreeVectorF const pMom = tp->p();
    float pt  = pMom.perp();
    float ptot = pMom.mag();
    sig_dcaxy = tp->dcaD();//tp->idParentVx());
    sig_dca = tp->dca().mag();//tp->idParentVx()).mag();//dca3d;                                                                                                                                                                                               
    sig_dcaz = tp->dcaZ();//tp->idParentVx());
    event_centrality = centrality;
    sig_p = ptot;         
    sig_vz = pVtx.z();
    sig_pt = pt;
    sig_eta = pMom.pseudoRapidity();
    sig_phi = pMom.phi();
    sig_charge = tp->charge();
    sig_id = tmc->GePid();
    int parentGid=0;
    int gparentGid=0;
    int ggparentGid=0;
    float parentPt=0;
    float gparentPt=0;
    float ggparentPt=0;
    /*if(tmc->parentId() == tmc->Id()){
        parentGid  = tmc->GePid();
    }
    else if(tmc->parentId() != Pico::USHORTMAX){
        StMuMcTrack *mcParentTrk = (StMuMcTrack*)mcTracks->UncheckedAt(tmc->parentId()-1);
        parentGid  = mcParentTrk->GePid();
        parentPt  = mcParentTrk->Mom().perp();
        if(mcParentTrk->parentId() != Pico::USHORTMAX && mcParentTrk->parentId() != mcParentTrk->Id()){
            StMuMcTrack *mcgParentTrk = (StMuMcTrack*)mcTracks->UncheckedAt(mcParentTrk->parentId()-1);
            gparentGid  = mcgParentTrk->GePid();
            gparentPt  = mcgParentTrk->Mom().perp();
            if(mcgParentTrk->parentId() != Pico::USHORTMAX && mcgParentTrk->parentId() != mcgParentTrk->Id()){
                StMuMcTrack *mcggParentTrk = (StMuMcTrack*)mcTracks->UncheckedAt(mcgParentTrk->parentId()-1);
                ggparentGid  = mcggParentTrk->GePid();
                ggparentPt  = mcggParentTrk->Mom().perp();

            }
        }
	}*/
    unsigned int map0 = tp->topologyMap().data(0);
    sig_hft = ((map0>>1) & 0x1) && ((map0>>2) & 0x3) && ((map0>>4) & 0x3);;
    sig_parentphi = 0;//parentphi;
    sig_gparentphi = 0;//gparentphi;
    sig_parentid = parentGid;
    sig_gparentid = gparentGid;
    sig_ggparentid = ggparentGid;
    sig_parentpt = parentPt;
    sig_gparentpt = gparentPt;
    sig_ggparentpt = ggparentPt;
    Signal_tree->Fill();
}
int StMuAnalysisMaker::get_centrality(float mul) {

    static float centcuts[] = {10, 21, 40, 71, 116, 179, 263, 373, 441, 1000};
    int centbin=-1;
    for (int ic=0;ic<9;ic++) {
	if (mul>=centcuts[ic] && mul<centcuts[ic+1]) {centbin = ic; break;}
    }

    return centbin;
}
