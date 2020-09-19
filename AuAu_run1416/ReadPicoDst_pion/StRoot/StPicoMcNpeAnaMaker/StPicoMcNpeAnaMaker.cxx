#include <vector>
#include <cmath>

#include "TVector3.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "StThreeVectorF.hh"
#include "StLorentzVectorF.hh"
#include "StLorentzVectorD.hh"
#include "../StPicoDstMaker/StPicoDst.h"
#include "../StPicoDstMaker/StPicoDstMaker.h"
#include "../StPicoDstMaker/StPicoEvent.h"
#include "../StPicoDstMaker/StPicoTrack.h"
#include "../StPicoDstMaker/StPicoMcEvent.h"
#include "../StPicoDstMaker/StPicoMcTrack.h"
#include "../StPicoDstMaker/StPicoEmcPidTraits.h"
#include "../StPicoDstMaker/StPicoMtdPidTraits.h"
#include "../StPicoDstMaker/StPicoBTofPidTraits.h"	
#include "StPicoMcNpeAnaMaker.h"
#include "StElectronPair.h"
#include "StCuts.h"
#include "StRefMultCorr/StRefMultCorr.h"
#include "StRefMultCorr/CentralityMaker.h"

ClassImp(StPicoMcNpeAnaMaker)

//-----------------------------------------------------------------------------
StPicoMcNpeAnaMaker::StPicoMcNpeAnaMaker(char const* makerName, StPicoDstMaker* picoMaker, char const* fileBaseName)
: StMaker(makerName), mPicoDstMaker(picoMaker), mPicoEvent(NULL),
mOutputFile(NULL)
{
    
    TString baseName(fileBaseName);
    mOutputFile = new TFile(Form("%s.root",fileBaseName), "RECREATE");
}

//-----------------------------------------------------------------------------
StPicoMcNpeAnaMaker::~StPicoMcNpeAnaMaker()
{
    /* mTree is owned by mOutputFile directory, it will be destructed once
     * the file is closed in ::Finish() */
}

//-----------------------------------------------------------------------------
Int_t StPicoMcNpeAnaMaker::Init()
{
    mRefMultCorr = new StRefMultCorr("grefmult_P16id");
    mRefMultCorr->setVzForWeight(6, -6.0, 6.0);
    mRefMultCorr->readScaleForWeight("StRoot/StRefMultCorr/macros/weight_grefmult_vpd30_vpd5_Run14_P16id.txt");


    TFile *f1 = new TFile("./weights_electron.root");
    TFile *f2 = new TFile("./weights_pion.root");
    
    if(!(f1->IsOpen()&&f2->IsOpen())){
	cout << "\n\n\n\n\nError in opening DLL weights!!!! \n\n\n\n\n " << endl;
    }
    mElectronWeights[0] = (TH1F*)f1->Get("electron_weight_povere");
    mElectronWeights[1] = (TH1F*)f1->Get("electron_weight_nsige");
    mElectronWeights[2] = (TH1F*)f1->Get("electron_weight_deltabeta");
    mElectronWeights[3] = (TH1F*)f1->Get("electron_weight_zdist");
    mElectronWeights[4] = (TH1F*)f1->Get("electron_weight_phidist");
    mPionWeights[0] = (TH1F*)f2->Get("pion_weight_povere");
    mPionWeights[1] = (TH1F*)f2->Get("pion_weight_nsigpi");
    mPionWeights[2] = (TH1F*)f2->Get("pion_weight_deltabeta");
    mPionWeights[3] = (TH1F*)f2->Get("pion_weight_zdist");
    mPionWeights[4] = (TH1F*)f2->Get("pion_weight_phidist"); 
   
    mOutputFile->cd();

    //TH1F* mranMass = new TH1F("mranMass","ranMass",1000,0,1);mranMass->Sumw2();
    //TH1F* mranDca = new TH1F("mranDca","ranDca",1000,0,1);mranDca->Sumw2();
    //TH1F* mranDP = new TH1F("mranDP","ranDP",2000,0,20);mranDP->Sumw2();
    //TH1F* mranDR = new TH1F("mranDR","ranDR",2000,0,20);mranDR->Sumw2();
    
    Signal_tree = new TTree("Signal_tree","Signal Tree");
    Signal_tree->Branch("sig_Pxl1Truth",&sig_Pxl1Truth,"sig_Pxl1Truth/F");
    Signal_tree->Branch("sig_Pxl2Truth",&sig_Pxl2Truth,"sig_Pxl2Truth/F");
    Signal_tree->Branch("sig_IstTruth",&sig_IstTruth,"sig_IstTruth/F");
    Signal_tree->Branch("sig_SsdTruth",&sig_SsdTruth,"sig_SsdTruth/F");
    Signal_tree->Branch("sig_p",&sig_p,"sig_p/F");
    Signal_tree->Branch("sig_triggercat",&sig_triggercat,"sig_triggercat/F");
    Signal_tree->Branch("sig_pt",&sig_pt,"sig_pt/F");
    Signal_tree->Branch("sig_dcaxy",&sig_dcaxy,"sig_dcaxy/F");
    Signal_tree->Branch("sig_dca",&sig_dca,"sig_dca/F");
    Signal_tree->Branch("sig_dcaz",&sig_dcaz,"sig_dcaz/F");
    Signal_tree->Branch("sig_nsige",&sig_nsige,"sig_nsige/F");
    Signal_tree->Branch("sig_nsigpi",&sig_nsigpi,"sig_nsigpi/F");
    Signal_tree->Branch("sig_nsigk",&sig_nsigk,"sig_nsigk/F");
    Signal_tree->Branch("sig_nsigp",&sig_nsigp,"sig_nsigp/F");
    Signal_tree->Branch("sig_beta",&sig_beta,"sig_beta/F");
    //Signal_tree->Branch("sig_emc0",&sig_emc0,"sig_emc0/F");
    Signal_tree->Branch("sig_eta",&sig_eta,"sig_eta/F");
    Signal_tree->Branch("sig_isiso",&sig_isiso,"sig_isiso/F");
    Signal_tree->Branch("sig_phi",&sig_phi,"sig_phi/F");
    Signal_tree->Branch("sig_hft",&sig_hft,"sig_hft/F");
    Signal_tree->Branch("sig_phi2",&sig_phi2,"sig_phi2/F");
    //Signal_tree->Branch("sig_neta",&sig_neta,"sig_neta/F");
    //Signal_tree->Branch("sig_nphi",&sig_nphi,"sig_nphi/F");
    Signal_tree->Branch("sig_charge",&sig_charge,"sig_charge/F");
    //Signal_tree->Branch("sig_phidist",&sig_phidist,"sig_phidist/F");
    //Signal_tree->Branch("sig_zdist",&sig_zdist,"sig_zdist/F");    
    //Signal_tree->Branch("sig_mva",&sig_mva,"sig_mva/F");  
    Signal_tree->Branch("sig_id",&sig_id,"sig_id/F");  
    Signal_tree->Branch("sig_yloc",&sig_yloc,"sig_yloc/F");  
    Signal_tree->Branch("event_centrality",&event_centrality,"event_centrality/F"); 
    //Signal_tree->Branch("event_qx1",&event_qx1,"event_qx1/F"); 
    //Signal_tree->Branch("event_qx2",&event_qx2,"event_qx2/F"); 
    //Signal_tree->Branch("event_qx",&event_qx,"event_qx/F"); 
    //Signal_tree->Branch("event_qy1",&event_qy1,"event_qy1/F"); 
    //Signal_tree->Branch("event_qy2",&event_qy2,"event_qy2/F"); 
    //Signal_tree->Branch("event_qy",&event_qy,"event_qy/F");  
    //Signal_tree->Branch("run_id",&run_id,"run_id/F");  
    Signal_tree->Branch("sig_vx",&sig_vx,"sig_vx/F");   
    Signal_tree->Branch("sig_vy",&sig_vy,"sig_vy/F");   
    Signal_tree->Branch("sig_vz",&sig_vz,"sig_vz/F");   
    Signal_tree->Branch("sig_ox",&sig_ox,"sig_ox/F");   
    Signal_tree->Branch("sig_oy",&sig_oy,"sig_oy/F");   
    Signal_tree->Branch("sig_oz",&sig_oz,"sig_oz/F");       
    Signal_tree->Branch("sig_head",&sig_head,"sig_head/F");    
    //Signal_tree->Branch("sig_refmult",&sig_refmult,"sig_refmult/F");  
    //Signal_tree->Branch("sig_grefmult",&sig_grefmult,"sig_grefmult/F");  
    Signal_tree->Branch("sig_parentid",&sig_parentid,"sig_parentid/F"); 
    Signal_tree->Branch("sig_gparentid",&sig_gparentid,"sig_gparentid/F");  
    Signal_tree->Branch("sig_ggparentid",&sig_ggparentid,"sig_ggparentid/F");
    Signal_tree->Branch("sig_parentpt",&sig_parentpt,"sig_parentpt/F");
    Signal_tree->Branch("sig_gparentpt",&sig_gparentpt,"sig_gparentpt/F");
    Signal_tree->Branch("sig_ggparentpt",&sig_ggparentpt,"sig_ggparentpt/F");  
    Signal_tree->Branch("sig_parentphi",&sig_parentphi,"sig_parentphi/F");
    Gen_tree = new TTree("Gen_tree","Gen Tree");
    Gen_tree->Branch("gen_p",&gen_p,"gen_p/F");
    Gen_tree->Branch("gen_pt",&gen_pt,"gen_pt/F");
    Gen_tree->Branch("gen_dcaxy",&gen_dcaxy,"gen_dcaxy/F");
    Gen_tree->Branch("gen_dca",&gen_dca,"gen_dca/F");
    Gen_tree->Branch("gen_eta",&gen_eta,"gen_eta/F");
    Gen_tree->Branch("gen_phi",&gen_phi,"gen_phi/F");
    Gen_tree->Branch("gen_phi2",&gen_phi2,"gen_phi2/F");
    Gen_tree->Branch("gen_id",&gen_id,"gen_id/F"); 
    //Gen_tree->Branch("gen_orig",&gen_orig,"gen_orig/F"); 
    //Gen_tree->Branch("gen_origxy",&gen_origxy,"gen_origxy/F"); 
    Gen_tree->Branch("event_centrality",&gen_event_centrality,"event_centrality/F"); 
//    Gen_tree->Branch("event_qx1",&gen_event_qx1,"event_qx1/F"); 
//    Gen_tree->Branch("event_qx2",&gen_event_qx2,"event_qx2/F"); 
    //Gen_tree->Branch("event_qx",&gen_event_qx,"event_qx/F"); 
//    Gen_tree->Branch("event_qy1",&gen_event_qy1,"event_qy1/F"); 
//    Gen_tree->Branch("event_qy2",&gen_event_qy2,"event_qy2/F"); 
    //Gen_tree->Branch("event_qy",&gen_event_qy,"event_qy/F");  
    //Gen_tree->Branch("run_id",&gen_run_id,"run_id/F");  
    Gen_tree->Branch("gen_vx",&gen_vx,"gen_vx/F");   
    Gen_tree->Branch("gen_vy",&gen_vy,"gen_vy/F");   
    Gen_tree->Branch("gen_vz",&gen_vz,"gen_vz/F");    
    Gen_tree->Branch("gen_ox",&gen_ox,"gen_ox/F");
    Gen_tree->Branch("gen_oy",&gen_oy,"gen_oy/F");    
    Gen_tree->Branch("gen_head",&gen_head,"gen_head/F");    
//    Gen_tree->Branch("gen_refmult",&gen_refmult,"gen_refmult/F");  
    //Gen_tree->Branch("gen_grefmult",&gen_grefmult,"gen_grefmult/F");  
    Gen_tree->Branch("gen_parentid",&gen_parentid,"gen_parentid/F"); 
    Gen_tree->Branch("gen_gparentid",&gen_gparentid,"gen_gparentid/F");  
    Gen_tree->Branch("gen_ggparentid",&gen_ggparentid,"gen_ggparentid/F");
    Gen_tree->Branch("gen_parentpt",&gen_parentpt,"gen_parentpt/F");
    Gen_tree->Branch("gen_gparentpt",&gen_gparentpt,"gen_gparentpt/F");
    Gen_tree->Branch("gen_ggparentpt",&gen_ggparentpt,"gen_ggparentpt/F");


    EH_tree = new TTree("EH","EH Tree");
    EH_tree->Branch("eh_pair_decayr",&eh_pair_decayr,"eh_pair_decayr/F");
    EH_tree->Branch("eh_pair_decaypos",&eh_pair_decaypos,"eh_pair_decaypos/F");
    EH_tree->Branch("eh_dca",&eh_dca,"eh_dca/F");
    EH_tree->Branch("eh_p",&eh_p,"eh_p/F");
    EH_tree->Branch("eh_isiso",&eh_isiso,"eh_isiso/F");
    EH_tree->Branch("eh_id",&eh_id,"eh_id/F");
    EH_tree->Branch("eh_Pxl1Truth",&eh_Pxl1Truth,"eh_Pxl1Truth/F");
    EH_tree->Branch("eh_Pxl2Truth",&eh_Pxl2Truth,"eh_Pxl2Truth/F");
    EH_tree->Branch("eh_IstTruth",&eh_IstTruth,"eh_IstTruth/F");
    EH_tree->Branch("eh_SsdTruth",&eh_SsdTruth,"eh_SsdTruth/F");
    EH_tree->Branch("eh_h_Pxl1Truth",&eh_h_Pxl1Truth,"eh_h_Pxl1Truth/F");
    EH_tree->Branch("eh_h_Pxl2Truth",&eh_h_Pxl2Truth,"eh_h_Pxl2Truth/F");
    EH_tree->Branch("eh_h_IstTruth",&eh_h_IstTruth,"eh_h_IstTruth/F");
    EH_tree->Branch("eh_h_SsdTruth",&eh_h_SsdTruth,"eh_h_SsdTruth/F");
    EH_tree->Branch("eh_head",&eh_head,"eh_head/F");
    EH_tree->Branch("eh_pair_dca",&eh_pair_dca,"eh_pair_dca/F");
    //EH_tree->Branch("eh_pair_sib",&eh_pair_sib,"eh_pair_sib/F");
    EH_tree->Branch("eh_h_dca",&eh_h_dca,"eh_h_dca/F");
    EH_tree->Branch("eh_dcaz",&eh_dcaz,"eh_dcaz/F");
    EH_tree->Branch("eh_h_dcaxy",&eh_h_dcaxy,"eh_h_dcaxy/F");
    EH_tree->Branch("eh_comb_eta",&eh_comb_eta,"eh_comb_eta/F");
    EH_tree->Branch("eh_comb_phi",&eh_comb_phi,"eh_comb_phi/F");
    EH_tree->Branch("eh_comb_mass",&eh_comb_mass,"eh_comb_mass/F");
    EH_tree->Branch("eh_comb_dcaxy",&eh_comb_dcaxy,"eh_comb_dcaxy/F");
    EH_tree->Branch("eh_comb_dca",&eh_comb_dca,"eh_comb_dca/F");
    EH_tree->Branch("eh_h_p",&eh_h_p,"eh_h_p/F");
    //EH_tree->Branch("eh_triggercat",&eh_triggercat,"eh_triggercat/F");
    EH_tree->Branch("eh_pt",&eh_pt,"eh_pt/F");
    EH_tree->Branch("eh_h_pt",&eh_h_pt,"eh_h_pt/F");
    EH_tree->Branch("eh_dcaxy",&eh_dcaxy,"eh_dcaxy/F");
    EH_tree->Branch("eh_dca",&eh_dca,"eh_dca/F");
    EH_tree->Branch("eh_nsige",&eh_nsige,"eh_nsige/F");
    EH_tree->Branch("eh_nsigpi",&eh_nsigpi,"eh_nsigpi/F");
    EH_tree->Branch("eh_nsigk",&eh_nsigk,"eh_nsigk/F");
    EH_tree->Branch("eh_nsigp",&eh_nsigp,"eh_nsigp/F");
    //EH_tree->Branch("eh_h_ismc",&eh_h_ismc,"eh_h_ismc/F");
    EH_tree->Branch("eh_h_nsige",&eh_h_nsige,"eh_h_nsige/F");
    EH_tree->Branch("eh_h_nsigpi",&eh_h_nsigpi,"eh_h_nsigpi/F");
    EH_tree->Branch("eh_h_nsigk",&eh_h_nsigk,"eh_h_nsigk/F");
    EH_tree->Branch("eh_h_nsigp",&eh_h_nsigp,"eh_h_nsigp/F");
    EH_tree->Branch("eh_beta",&eh_beta,"eh_beta/F");
    //EH_tree->Branch("eh_emc0",&eh_emc0,"eh_emc0/F");
    EH_tree->Branch("eh_eta",&eh_eta,"eh_eta/F");
    EH_tree->Branch("eh_phi",&eh_phi,"eh_phi/F");
    //EH_tree->Branch("eh_phi2",&eh_phi2,"eh_phi2/F");
    //EH_tree->Branch("eh_neta",&eh_neta,"eh_neta/F");
    //EH_tree->Branch("eh_nphi",&eh_nphi,"eh_nphi/F");
    EH_tree->Branch("eh_charge",&eh_charge,"eh_charge/F");
    EH_tree->Branch("eh_h_charge",&eh_h_charge,"eh_h_charge/F");
    //EH_tree->Branch("eh_phidist",&eh_phidist,"eh_phidist/F");
    //EH_tree->Branch("eh_zdist",&eh_zdist,"eh_zdist/F");    
    //EH_tree->Branch("eh_mva",&eh_mva,"eh_mva/F");  
    //EH_tree->Branch("eh_yloc",&eh_yloc,"eh_yloc/F");  
    EH_tree->Branch("event_centrality",&eh_event_centrality,"event_centrality/F"); 
    //EH_tree->Branch("event_qx1",&eh_event_qx1,"event_qx1/F"); 
    //EH_tree->Branch("event_qx2",&eh_event_qx2,"event_qx2/F"); 
    //EH_tree->Branch("event_qx",&eh_event_qx,"event_qx/F"); 
    //EH_tree->Branch("event_qy1",&eh_event_qy1,"event_qy1/F"); 
    //EH_tree->Branch("event_qy2",&eh_event_qy2,"event_qy2/F"); 
    //EH_tree->Branch("event_qy",&eh_event_qy,"event_qy/F");  
    //EH_tree->Branch("run_id",&eh_run_id,"run_id/F");  
    //EH_tree->Branch("eh_vx",&eh_vx,"eh_vx/F");   
    //EH_tree->Branch("eh_vy",&eh_vy,"eh_vy/F");   
    //EH_tree->Branch("eh_vz",&eh_vz,"eh_vz/F");    
    //EH_tree->Branch("eh_refmult",&eh_refmult,"eh_refmult/F");  
    //EH_tree->Branch("eh_grefmult",&eh_grefmult,"eh_grefmult/F");  
    EH_tree->Branch("eh_parentid",&eh_parentid,"eh_parentid/F"); 
    EH_tree->Branch("eh_gparentid",&eh_gparentid,"eh_gparentid/F");  
    EH_tree->Branch("eh_ggparentid",&eh_ggparentid,"eh_ggparentid/F");
    EH_tree->Branch("eh_parentpt",&eh_parentpt,"eh_parentpt/F");
    EH_tree->Branch("eh_gparentpt",&eh_gparentpt,"eh_gparentpt/F");
    EH_tree->Branch("eh_ggparentpt",&eh_ggparentpt,"eh_ggparentpt/F");
    return kStOK;
}

//-----------------------------------------------------------------------------
Int_t StPicoMcNpeAnaMaker::Finish()
{
    mOutputFile->cd();
    //mranMass->Write();
    //mranDca->Write();
    //mranDR->Write();
    //mranDP->Write();
    Signal_tree->Write();
    Gen_tree->Write();
    EH_tree->Write();
    //mOutputFile->Write();
    mOutputFile->Close();
    return kStOK;
}
//-----------------------------------------------------------------------------
void StPicoMcNpeAnaMaker::Clear(Option_t *opt)
{
}

//-----------------------------------------------------------------------------
Int_t StPicoMcNpeAnaMaker::Make()
{
    
    if (!mPicoDstMaker)
    {
        LOG_WARN << " No PicoDstMaker! Skip! " << endm;
        return kStWarn;
    }
    
    StPicoDst const * picoDst = mPicoDstMaker->picoDst();
    if (!picoDst)
    {
        LOG_WARN << " No PicoDst! Skip! " << endm;
        return kStWarn;
    }
    
    mPicoEvent = picoDst->event();
    std::vector<unsigned short> idxPicoTaggedEs;
    std::vector<unsigned short> idxPicoTaggedPs;
    std::vector<unsigned short> idxPicoTaggedEsMC;
    mRefMultCorr->init(15107005);//picoDst->event()->runId());
    mRefMultCorr->initEvent(picoDst->event()->grefMult(),picoDst->event()->vzVpd(),picoDst->event()->ZDCx());

    mIsoEs.clear();
    if (isGoodEvent()){
	StThreeVectorF pVtx = mPicoEvent->primaryVertex(); 
	int nMcTracks = picoDst->numberOfMcTracks();
	int trigId = 0;
	bool isHLT1 = false;
	bool isHLT2 = false;
	bool isHLT3 = false;
	bool isMB = false;
	centrality = mRefMultCorr->getCentralityBin9();

        //Fill array of track IDs to speed up find associated rec. MC tracks
	vector <int> rTracks;  	

	double Q_X=0;
	double Q_Y=0;
	double Q1_X=0;
	double Q1_Y=0;
	double Q2_X=0;
	double Q2_Y=0;
	int iTrack=0;
	while (1)//Needed if below block is not used                                                                                                                                                   
        {
            StPicoTrack* track = (StPicoTrack*)mPicoDstMaker->picoDst()->track(iTrack);
            if(!track)break;
	    if(fabs(track->nSigmaElectron())<3){//mNpeCuts->getDLL(track)> mNpeCuts->cutMVA()){                                                                                                                       
		//if(track->gPt()<2.5){
		//    if(mNpeCuts->isTOFElectron(track))mIsoEs.push_back(iTrack);
		//	}
		//else{
		mIsoEs.push_back(iTrack);
		//}
	    }

            rTracks.push_back(track->id());
	    if(isPass(track,pVtx) && track->isHFTTrack())idxPicoTaggedPs.push_back(iTrack);
	    iTrack++;
	}
	iTrack=0;
	while (0)//turn off for speed 
	{
	    StPicoTrack* track = (StPicoTrack*)mPicoDstMaker->picoDst()->track(iTrack);
	    if(!track)break;
	    rTracks.push_back(track->id()); 
	    if(isPass(track,pVtx) && track->isHFTTrack())idxPicoTaggedPs.push_back(iTrack);
	    if(track->gPt()>0.15 && track->gPt()<2.  && !(track->nSigmaElectron()>-1 && track->nSigmaElectron()<3) && !isMcTrack(track,picoDst)){
		double ww = 0;
		if(track->gPt()<=2.)ww = track->gPt();
		if(track->gPt()>2.)ww = 2;
		if(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity()>0.05 && track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity()<1. ){
		    Q1_X += ww*TMath::Cos(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).phi());
		    Q1_Y += ww*TMath::Sin(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).phi());
		}
		if(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity()<-0.05 && track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity()>-1. ){
		    Q2_X += ww*TMath::Cos(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).phi());
		    Q2_Y += ww*TMath::Sin(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).phi());
		}
		if(track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity()<1. && track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity()>-1. ){
		    Q_X += ww*TMath::Cos(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).phi());
		    Q_Y += ww*TMath::Sin(2.*track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).phi());
		}
	    }
	    iTrack++;
	}

	int* arr = &rTracks[0];
	//cout << "Number of MC tracks " << nMcTracks << endl;
	for(int iTrack=0;iTrack<nMcTracks;iTrack++){                                                  
	    StPicoMcTrack *mctrack = (StPicoMcTrack*)picoDst->mctrack(iTrack);
	    if(mctrack)fillGenTree(mctrack,pVtx,Q_X,Q_Y,Q1_X,Q1_Y,Q2_X,Q2_Y); // Filling trees
	    if(mctrack->assoId()==Pico::USHORTMAX)continue;
	    Int_t geid = mctrack->GePid();
	    Int_t idTrack = -999;
	    isRcTrack(mctrack,picoDst,idTrack, arr);
	    if(idTrack!=-999){
		StPicoTrack *track = (StPicoTrack*)picoDst->track(idTrack); 
		double MVADec = getDLL(track);         
		if(isPass(track,pVtx)){
		    if((mctrack->GePid()==8 || mctrack->GePid()==9))idxPicoTaggedEs.push_back(iTrack);
		    if(track->isHFTTrack())idxPicoTaggedEsMC.push_back(iTrack);
		    //fillTree(track,mctrack,pVtx,isMB,isHLT1,isHLT2,isHLT3,MVADec,Q_X,Q_Y,Q1_X,Q1_Y,Q2_X,Q2_Y); // Filling trees
		}
	    }
	}	    
	for(int i = 0; i<idxPicoTaggedEs.size();i++){
	    //if(nMcTracks>20000)continue;
	    StPicoMcTrack *mctrack = (StPicoMcTrack*)picoDst->mctrack(idxPicoTaggedEs[i]);
	    if(!mctrack)continue;
	    Int_t idTrack = -999;
            isRcTrack(mctrack,picoDst,idTrack, arr);
	    StPicoTrack* track = (StPicoTrack*) picoDst->track(idTrack);
	    if(!track)continue;
	    double MVADec = getDLL(track);
	    fillTree(track,mctrack,pVtx,isMB,isHLT1,isHLT2,isHLT3,MVADec,Q_X,Q_Y,Q1_X,Q1_Y,Q2_X,Q2_Y); // Filling trees  
	    for(int j = 0; j<idxPicoTaggedEs.size();j++){
		if(j==i)continue;
		StPicoMcTrack *mctrack1 = (StPicoMcTrack*)picoDst->mctrack(idxPicoTaggedEs[j]);
		if(!mctrack1)continue;
		//if(!isMcSibling(mctrack,mctrack1,picoDst))continue;
		if(mctrack->parentId()!=Pico::USHORTMAX&& mctrack1->parentId()!=Pico::USHORTMAX && mctrack->parentId() == mctrack1->parentId() && mctrack->parentId() != mctrack->mcId() &&  mctrack1->parentId() != mctrack1->mcId()){
		    Int_t idTrack1 = -999;
		    isRcTrack(mctrack1,picoDst,idTrack1, arr);
		    StPicoTrack* tp = (StPicoTrack*) picoDst->track(idTrack1);
		    if(!tp)continue;
		    StPhysicalHelixD electronHelix = track->dcaGeometry().helix();
		    StPhysicalHelixD partnerHelix = tp->dcaGeometry().helix();
		    pair<double,double> ss = electronHelix.pathLengths(partnerHelix);
		    StThreeVectorD kAtDcaToPartner = electronHelix.at(ss.first);
		    StThreeVectorD pAtDcaToElectron = partnerHelix.at(ss.second);
		    StThreeVectorD VectorDca = kAtDcaToPartner - pAtDcaToElectron;
		    double dca_can = static_cast<float>(VectorDca.mag());
		    if(dca_can<1)fillEHTree(track,mctrack,tp,mctrack1,pVtx,isMB,isHLT1,isHLT2,isHLT3,Q_X,Q_Y,Q1_X,Q1_Y,Q2_X,Q2_Y);
		}
		else{
		    if(0){//mctrack->parentId() == mctrack->mcId() || mctrack->parentId()==37 || mctrack->parentId()==38 ){
			Int_t idTrack1 = -999;
			isRcTrack(mctrack1,picoDst,idTrack1, arr);
			StPicoTrack* tp = (StPicoTrack*) picoDst->track(idTrack1);
			if(!tp)continue;
			StPhysicalHelixD electronHelix = track->dcaGeometry().helix();
			StPhysicalHelixD partnerHelix = tp->dcaGeometry().helix();
			pair<double,double> ss = electronHelix.pathLengths(partnerHelix);
			StThreeVectorD kAtDcaToPartner = electronHelix.at(ss.first);
			StThreeVectorD pAtDcaToElectron = partnerHelix.at(ss.second);
			StThreeVectorD VectorDca = kAtDcaToPartner - pAtDcaToElectron;
			double dca_can = static_cast<float>(VectorDca.mag());
			fillRanHist(track,mctrack,tp,mctrack1,pVtx,isMB,isHLT1,isHLT2,isHLT3,Q_X,Q_Y,Q1_X,Q1_Y,Q2_X,Q2_Y);
		    }
		}
	    }
	}       
	//Ntrack end first loop 
//==================== Electron-hadron tree
/*	for(int i = 0;i<idxPicoTaggedEs.size();i++){
	    int ncan=0;
	    double win=1000;
	    int trackwin = -1;
	    StPicoTrack* tt = (StPicoTrack*) picoDst->track(idxPicoTaggedEs[i]);
	    StPicoMcTrack* tmc = (StPicoMcTrack*) picoDst->mctrack(idxPicoTaggedEsMC[i]);
	    for(int j = 0; j<idxPicoTaggedPs.size();j++){
		StPicoTrack* tp = (StPicoTrack*) picoDst->track(idxPicoTaggedPs[j]);
		StPhysicalHelixD electronHelix = tt->dcaGeometry().helix();
		StPhysicalHelixD partnerHelix = tp->dcaGeometry().helix();
		pair<double,double> ss = electronHelix.pathLengths(partnerHelix);
		StThreeVectorD kAtDcaToPartner = electronHelix.at(ss.first);
		StThreeVectorD pAtDcaToElectron = partnerHelix.at(ss.second);
		// calculate DCA of partner to electron at their DCA
		StThreeVectorD VectorDca = kAtDcaToPartner - pAtDcaToElectron;
		StThreeVectorD DecayPoint = (kAtDcaToPartner/2 + pAtDcaToElectron/2) - pVtx;
		double DR = (sqrt(DecayPoint.x()*DecayPoint.x()+DecayPoint.y()*DecayPoint.y()+DecayPoint.z()*DecayPoint.z()));

		double dca_can = static_cast<float>(VectorDca.mag());
		double displace = partnerHelix.geometricSignedDistance(pVtx);
		if(fabs(displace)<0.01 || DR>2)continue;
		if(dca_can<win){
		    win = dca_can;
		    trackwin = j;
		}
		if(dca_can<1){
		    ncan++;
		}	  	       
	    }
	    if(win<1){
		StPicoTrack* tpp = (StPicoTrack*) picoDst->track(idxPicoTaggedPs[trackwin]);	   
		if(tpp)fillEHTree(tt,tmc,tpp,pVtx,isMB,isHLT1,isHLT2,isHLT3); // Filling trees
	    }
	}
*/
    } //.. end of good event
    return kStOK;
}

//-----------------------------------------------------------------------------
bool StPicoMcNpeAnaMaker::isGoodEvent()
{
    float vZ = mPicoEvent->primaryVertex().z();
    return fabs(vZ) < cuts::vz ;  
}
//-----------------------------------------------------------------------------
bool StPicoMcNpeAnaMaker::isGoodTrack(StPicoTrack const * const trk) const
{
    return
    trk->gPt() > cuts::ptMin &&
    trk->gPt() < cuts::ptMax ;
    trk->nHitsFit() >= cuts::nHitsFit &&
    (float)trk->nHitsFit()/(float)trk->nHitsMax() > cuts::nHitsMax &&
    trk->isHFTTrack();
}
//-----------------------------------------------------------------------------
bool StPicoMcNpeAnaMaker::isHftTrack(StPicoTrack const * const trk) const
{
    return trk->nHitsMapHFT()>>1 & 0x3;
    // return !(trk->nHitsMapHFT()>>0 & 0x1) && (trk->nHitsMapHFT()>>1 & 0x3) && (trk->nHitsMapHFT()>>3 & 0x3);
}
//-----------------------------------------------------------------------------

bool StPicoMcNpeAnaMaker::isRcTrack(StPicoMcTrack const * const PicoMcTrack, StPicoDst const * const  PicoDst,int &id, int arr[])
    {
	if(PicoMcTrack->assoId() == Pico::USHORTMAX )
	    return false;
	int temp = Pico::USHORTMAX ;
	for(int i_Rc =0; i_Rc<PicoDst->numberOfTracks(); ++i_Rc){
	    //StPicoTrack *Trk = (StPicoTrack*)PicoDst->track(i_Rc);
	    if(PicoMcTrack->assoId() == arr[i_Rc] ) {
		temp = i_Rc;
		break;
	    }
	}
	if (temp == Pico::USHORTMAX) return false;
	id=temp;
	return true;
    }
bool StPicoMcNpeAnaMaker::isMcTrack(StPicoTrack const * const PicoTrack, StPicoDst const * const  PicoDst)
    {
	for(int i_Rc =0; i_Rc<PicoDst->numberOfMcTracks(); ++i_Rc){
	    StPicoMcTrack *Trk = (StPicoMcTrack*)PicoDst->mctrack(i_Rc);
	    if(Trk->assoId() == PicoTrack->id())return true;  
	}
	return false;	
    }
bool StPicoMcNpeAnaMaker::isMcSibling(StPicoMcTrack const * const mctrack, StPicoMcTrack const * const track,StPicoDst const * const  PicoDst)
    {
	
	int tr1=0;
	int tr2=0;
	int temp1;
	float temp2;

	getParent(PicoDst,mctrack,tr1,temp1,temp2,true);
	getParent(PicoDst,track,tr2,temp1,temp2,true);	

	if(tr1==tr2)return true;
	else{   
	    return false;
	}	
    }
//------------------------------------------------------------------------------
void StPicoMcNpeAnaMaker::getParent(StPicoDst const * const picoDst, StPicoMcTrack const * const mcTrk, int & parentid, int & parentGid, float & parentMcPt, bool isMore = true)
{

	if(mcTrk->parentId() == mcTrk->mcId()){
	    parentGid  = mcTrk->GePid();
	    parentid  = mcTrk->parentId();
	    parentMcPt = mcTrk->Mom().perp();
	}
	else if(mcTrk->parentId() != Pico::USHORTMAX && mcTrk->parentId() != mcTrk->mcId()) 
	{
		StPicoMcTrack *mcParentTrk = (StPicoMcTrack*)picoDst->mctrack(mcTrk->parentId()-1);
		parentGid  = mcParentTrk->GePid();
		parentid  = mcParentTrk->parentId();
		parentMcPt = mcParentTrk->Mom().perp();
		if (mcTrk->parentId() != mcParentTrk->parentId() && isMore ) getParent(picoDst,mcParentTrk,parentid,parentGid,parentMcPt,true);
		//delete mcParentTrk;
	}
}

bool StPicoMcNpeAnaMaker::isMCElectron(StPicoMcTrack const *trk){
    if(trk->GePid()==8 || trk->GePid()==9)return true;
    return false;
}

bool StPicoMcNpeAnaMaker::isPass(StPicoTrack const *trk, StThreeVectorF pVtx){
    float vZ = mPicoEvent->primaryVertex().z();
    float temp1 = trk->nHitsFit();
    float temp2 = trk->nHitsMax();
    StPhysicalHelixD rcHelix = trk->dcaGeometry().helix();
    double dca = rcHelix.geometricSignedDistance(pVtx.x(),pVtx.y());
    double dca3d = rcHelix.geometricSignedDistance(pVtx);
    bool taggedElectronCut = 
	trk->nHitsFit() >= 20 && (temp1/temp2) >= 0.52 && 
	fabs(vZ)<6.  &&  //trk->nHitsDedx() >= 15 &&
        trk->gPt() >= 0.6 && trk->gPt() < 20 && trk->gMom(pVtx,mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity() > -0.7 && 
	trk->gMom(pVtx,mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity() < 0.7 &&
        fabs(dca) < 1 && dca3d < 1;
    return taggedElectronCut;

}

void StPicoMcNpeAnaMaker::fillTree(StPicoTrack* tp,StPicoMcTrack *tmc,StThreeVectorF pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3,double MVADec,double Q_X,double Q_Y,double Q1_X,double Q1_Y,double Q2_X,double Q2_Y){
    float pt = tp->gPt();
    StThreeVectorF const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());   
    StThreeVectorF orig = tmc->Origin();   
    double xx = orig.x();//-pVtx.x();
    double yy = orig.y();//-pVtx.y();
    double zz = orig.z();//-pVtx.z();
    StThreeVectorF path(xx,yy,zz);    
    float ptot = pMom.mag();
    float beta = 0;
    float adc0 = 0;
    float mass = 0;
    float YLoc = 0;
    int index2tof = tp->bTofPidTraitsIndex();
    if(index2tof>=0) {
	StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
	if(tofPid){
	    beta = tofPid->btofBeta();
	    YLoc = tofPid->btofYLocal();
	    mass = ptot*ptot*(1/beta/beta-1);
	}
    }
    float eoverp = 0;
    float emc0 = 0;
    int nPhi=0;
    int nEta=0;
    float zDist=0;
    float phiDist=0;
    if (tp->emcPidTraitsIndex() >= 0) {
	StPicoEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->emcPidTraits(tp->emcPidTraitsIndex());
	adc0 = Emc->adc0();
	eoverp = ptot/Emc->e0();
	emc0 = Emc->e0();
	nPhi = Emc->nPhi();
	nEta = Emc->nEta();
	phiDist = Emc->phiDist();
	zDist = Emc->zDist();
    }
    StPhysicalHelixD eHelix = tp->dcaGeometry().helix();
    StThreeVectorF dcaPoint = eHelix.at(eHelix.pathLength(pVtx.x(), pVtx.y()));
    StThreeVectorF dcaPoint3d = eHelix.at(eHelix.pathLength(pVtx));
    float dca = 0;
    dca = eHelix.geometricSignedDistance(pVtx.x(),pVtx.y());
    float dca3d = 0;
    dca3d = eHelix.geometricSignedDistance(pVtx);
    float nsige = tp->nSigmaElectron();
    float nsigpi = tp->nSigmaPion();
    float nsigk = tp->nSigmaKaon();
    float nsigp = tp->nSigmaProton();
    float adcCut[4] = {-999, 256, 304, 416};
    int trigCat = 0;
    if(isMB)trigCat = 1;
    if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
    if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2]))trigCat = 3;
    if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2] && isHLT3 && adc0>=adcCut[3]))trigCat = 4;
    if(isMB && !((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 5;
    //if(trigCat==0)return;

    float vZ = mPicoEvent->primaryVertex().z();
    float vX = mPicoEvent->primaryVertex().x();
    float vY = mPicoEvent->primaryVertex().y();
    int refMult = mPicoEvent->refMult();
    int gRefMult= mPicoEvent->grefMult();
    float dcaz = dcaPoint.z()-pVtx.z();
    sig_dcaz = dcaz;
    sig_vz = vZ;
    sig_vy = vY;   
    sig_vx = vX;
    sig_hft = tp->isHFTTrack();
    sig_oz = zz;
    sig_oy = yy;   
    sig_ox = xx;
    sig_refmult = refMult;
    sig_grefmult = gRefMult;    
    sig_pt = pt;
    sig_p = ptot;
    sig_isiso = isIso(tp,tmc);
    event_qx = Q_X;//qx;
    event_qx1 = Q1_X;//qx1;
    event_qx2 = Q2_X;//qx2;
    event_qy = Q_Y;//qy;
    event_qy1 = Q1_Y;//qy1;
    event_qy2 = Q2_Y;//qy2;
    sig_triggercat = trigCat;
    sig_nsige = nsige;
    sig_nsigpi = nsigpi;
    sig_nsigk = nsigk;
    sig_nsigp = nsigp;
    sig_beta = beta;
    sig_phidist = phiDist;
    sig_zdist = zDist;
    sig_dcaxy = dca;
    sig_dca = dca3d;
    sig_eta = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity();
    sig_phi = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).phi();
    
    sig_phi2 = path.phi();//TMath::Pi()+TMath::ATan2(-pMom.y(),-pMom.x());
    sig_neta = nEta;
    sig_nphi = nPhi;
    sig_emc0 = emc0;
    sig_yloc = YLoc;
    sig_charge = tp->charge();  
    sig_mva = MVADec;
    sig_id = tmc->GePid();
    int tempp1;
    float tempp2;
    int tempp3=0;
    getParent(mPicoDstMaker->picoDst(),tmc,tempp1,tempp3,tempp2,true);
    event_centrality = centrality;
    sig_head=tempp3;
    int parentGid=0;
    int gparentGid=0;
    int ggparentGid=0;
    float parentPt=0;
    float gparentPt=0;
    float ggparentPt=0;
    double parentphi=0;
    if(tmc->parentId() == tmc->mcId()){
	parentGid  = tmc->GePid();
    }
    else if(tmc->parentId() != Pico::USHORTMAX){ 
	StPicoMcTrack *mcParentTrk = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(tmc->parentId());
	parentGid  = mcParentTrk->GePid();
	parentphi = mcParentTrk->Mom().phi();
	parentPt  = mcParentTrk->Mom().perp();
	if(mcParentTrk->parentId() != Pico::USHORTMAX && mcParentTrk->parentId() != mcParentTrk->mcId()){ 
	    StPicoMcTrack *mcgParentTrk = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(mcParentTrk->parentId());
	    gparentGid  = mcgParentTrk->GePid();
	    gparentPt  = mcParentTrk->Mom().perp();
	    if(mcgParentTrk->parentId() != Pico::USHORTMAX && mcgParentTrk->parentId() != mcgParentTrk->mcId()){ 
		StPicoMcTrack *mcggParentTrk = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(mcgParentTrk->parentId());
		ggparentGid  = mcggParentTrk->GePid();
		ggparentPt  = mcParentTrk->Mom().perp();
	    }
	}
    }
    sig_Pxl1Truth = tmc->Pxl1Truth();
    sig_Pxl2Truth = tmc->Pxl2Truth();
    sig_IstTruth = tmc->IstTruth();
    sig_SsdTruth = tmc->SsdTruth();
    sig_parentphi = parentphi;
    sig_parentid = parentGid;
    sig_gparentid = gparentGid;
    sig_ggparentid = ggparentGid;
    sig_parentpt = parentPt;
    sig_gparentpt = gparentPt;
    sig_ggparentpt = ggparentPt;
    run_id = mPicoDstMaker->picoDst()->event()->runId();
    Signal_tree->Fill();
}
void StPicoMcNpeAnaMaker::fillGenTree(StPicoMcTrack *tmc,StThreeVectorF pVtx,double Q_X,double Q_Y,double Q1_X,double Q1_Y,double Q2_X,double Q2_Y){
 
    StThreeVectorF const pMom = tmc->Mom();
    StThreeVectorF const orig = tmc->Origin();
    double xx = orig.x();//-pVtx.x();                                                                                                                                                                                            
    double yy = orig.y();//-pVtx.y();     
    gen_ox = xx;
    gen_oy = yy;
    float pt = pMom.perp();
    float ptot = pMom.mag();
    int charge=0;
    gen_id = tmc->GePid();
    if(gen_id==9)charge=-1;
    else if(gen_id==8)charge=1;   
    else charge=0;
    StPhysicalHelixD pHelix(pMom,orig,mPicoDstMaker->picoDst()->event()->bField(),charge);
   
    float dca = pHelix.geometricSignedDistance(pVtx.x(),pVtx.y());  
    float dca3d = pHelix.geometricSignedDistance(pVtx);

   
    float origxy = sqrt(orig.x()*orig.x()+orig.y()*orig.y());  
    float orig_mag = orig.mag();
    gen_orig = orig_mag;
    gen_origxy = origxy;
 
    float vZ = mPicoEvent->primaryVertex().z();
    float vX = mPicoEvent->primaryVertex().x();
    float vY = mPicoEvent->primaryVertex().y();
    int refMult = mPicoEvent->refMult();
    int gRefMult= mPicoEvent->grefMult();

    gen_vz = vZ;
    gen_vy = vY;   
    gen_vx = vX;
    gen_refmult = refMult;
    gen_grefmult = gRefMult;    
    gen_pt = pt;
    gen_p = ptot;
    gen_event_qx = Q_X;//qx;
    gen_event_qx1 = Q1_X;//qx1;
    gen_event_qx2 = Q2_X;//qx2;
    gen_event_qy = Q_Y;//qy;
    gen_event_qy1 = Q1_Y;//qy1;
    gen_event_qy2 = Q2_Y;//qy2;
 
    gen_dcaxy = dca;
    gen_dca = dca3d;
    gen_eta = pMom.pseudoRapidity();
    gen_phi = pMom.phi();
    gen_phi2 = TMath::Pi()+TMath::ATan2(-pMom.y(),-pMom.x());
 
    int tempp1;
    float tempp2;
    int tempp3=0;
    getParent(mPicoDstMaker->picoDst(),tmc,tempp1,tempp3,tempp2,true);
    gen_event_centrality = centrality;
    gen_head=tempp3;
    int parentGid=0;
    int gparentGid=0;
    int ggparentGid=0;
    float parentPt=0;
    float gparentPt=0;
    float ggparentPt=0;
    if(tmc->parentId() == tmc->mcId()){
	parentGid  = tmc->GePid();
    }
    else if(tmc->parentId() != Pico::USHORTMAX){ 
	StPicoMcTrack *mcParentTrk = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(tmc->parentId());
	parentGid  = mcParentTrk->GePid();
	parentPt  = mcParentTrk->Mom().perp();
	if(mcParentTrk->parentId() != Pico::USHORTMAX && mcParentTrk->parentId() != mcParentTrk->mcId()){ 
	    StPicoMcTrack *mcgParentTrk = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(mcParentTrk->parentId());
	    gparentGid  = mcgParentTrk->GePid();
	    gparentPt  = mcgParentTrk->Mom().perp();
	    if(mcgParentTrk->parentId() != Pico::USHORTMAX && mcgParentTrk->parentId() != mcgParentTrk->mcId()){ 
		StPicoMcTrack *mcggParentTrk = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(mcgParentTrk->parentId());
		ggparentGid  = mcggParentTrk->GePid();
		ggparentPt  = mcggParentTrk->Mom().perp();

	    }
	}
    }
    gen_parentpt = parentPt;
    gen_gparentpt = gparentPt;
    gen_ggparentpt = ggparentPt;
    gen_parentid = parentGid;
    gen_gparentid = gparentGid;
    gen_ggparentid = ggparentGid;
    gen_run_id = mPicoDstMaker->picoDst()->event()->runId();
    Gen_tree->Fill();
}


void StPicoMcNpeAnaMaker::fillRanHist(StPicoTrack* tp,StPicoMcTrack *tmc,StPicoTrack* th,StPicoMcTrack *tmc1,StThreeVectorF pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3,double Q_X,double Q_Y,double Q1_X,double Q1_Y,double Q2_X,double Q2_Y){
    float pt = tp->gPt();
    StThreeVectorF const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());
    float ptot = pMom.mag();
    StPhysicalHelixD eHelix = tp->dcaGeometry().helix();
    StThreeVectorF dcaPoint = eHelix.at(eHelix.pathLength(pVtx.x(), pVtx.y()));
    StThreeVectorF dcaPoint3d = eHelix.at(eHelix.pathLength(pVtx));
    float dca = 0;
    dca = eHelix.geometricSignedDistance(pVtx.x(),pVtx.y());
    float dca3d = 0;
    dca3d = eHelix.geometricSignedDistance(pVtx);
    StPhysicalHelixD electronHelix = tp->dcaGeometry().helix();
    StPhysicalHelixD partnerHelix = th->dcaGeometry().helix();
    pair<double,double> ss = electronHelix.pathLengths(partnerHelix);
    StThreeVectorD kAtDcaToPartner = electronHelix.at(ss.first);
    StThreeVectorD pAtDcaToElectron = partnerHelix.at(ss.second);
    // calculate DCA of partner to electron at their DCA                                                                                                                                                                               
    StThreeVectorD VectorDca = kAtDcaToPartner - pAtDcaToElectron;
    double dca_can = static_cast<float>(VectorDca.mag());
    double displace = partnerHelix.geometricSignedDistance(pVtx);

    StThreeVectorD DecayPoint = (kAtDcaToPartner/2 + pAtDcaToElectron/2) - pVtx;
    StThreeVectorD DecayPos = (kAtDcaToPartner/2 + pAtDcaToElectron/2);
    //mPairDecayR = static_cast<float>(DecayPoint.mag());                                                                                                                                                                              
    mranDR->Fill(sqrt(DecayPoint.x()*DecayPoint.x()+DecayPoint.y()*DecayPoint.y()+DecayPoint.z()*DecayPoint.z()));
    mranDP->Fill(sqrt(DecayPos.x()*DecayPos.x()+DecayPos.y()*DecayPos.y()));

    StThreeVectorD const electronMomAtDca = electronHelix.momentumAt(ss.first, mPicoDstMaker->picoDst()->event()->bField() * kilogauss);
    StThreeVectorD const partnerMomAtDca = partnerHelix.momentumAt(ss.second,mPicoDstMaker->picoDst()->event()->bField()  * kilogauss);

    StLorentzVectorD electronFourMom(0,0,0,0);
    StLorentzVectorD partnerFourMom(0,0,0,0);

    electronFourMom.setPx(electronMomAtDca.x());
    electronFourMom.setPy(electronMomAtDca.y());
    electronFourMom.setPz(electronMomAtDca.z());
    electronFourMom.setE(sqrt(electronMomAtDca.x()*electronMomAtDca.x()
                              + electronMomAtDca.y()*electronMomAtDca.y()
                              + electronMomAtDca.z()*electronMomAtDca.z() + 0.00051099907*0.00051099907));

    partnerFourMom.setPx(partnerMomAtDca.x());
    partnerFourMom.setPy(partnerMomAtDca.y());
    partnerFourMom.setPz(partnerMomAtDca.z());
    partnerFourMom.setE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
                             + partnerMomAtDca.y()*partnerMomAtDca.y()
                             + partnerMomAtDca.z()*partnerMomAtDca.z()
                             +  + 0.00051099907*0.00051099907));

    StLorentzVectorF const epairFourMom = electronFourMom + partnerFourMom;

    mranMass->Fill(epairFourMom.m());
    mranDca->Fill(dca_can);

}

void StPicoMcNpeAnaMaker::fillEHTree(StPicoTrack* tp,StPicoMcTrack *tmc,StPicoTrack* th,StPicoMcTrack *tmc1,StThreeVectorF pVtx,bool isMB,bool isHLT1, bool isHLT2, bool isHLT3,double Q_X,double Q_Y,double Q1_X,double Q1_Y,double Q2_X,double Q2_Y){
    float pt = tp->gPt();
    StThreeVectorF const pMom = tp->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField());   
    float ptot = pMom.mag();
    float beta = 0;
    float adc0 = 0;
    float mass = 0;
    float YLoc = 0;
    int index2tof = tp->bTofPidTraitsIndex();
    if(index2tof>=0) {
	StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
	if(tofPid){
	    beta = tofPid->btofBeta();
	    YLoc = tofPid->btofYLocal();
	    mass = ptot*ptot*(1/beta/beta-1);
	}
    }
    float eoverp = 0;
    float emc0 = 0;
    int nPhi=0;
    int nEta=0;
    float zDist=0;
    float phiDist=0;
    if (tp->emcPidTraitsIndex() >= 0) {
	StPicoEmcPidTraits * Emc =  mPicoDstMaker->picoDst()->emcPidTraits(tp->emcPidTraitsIndex());
	adc0 = Emc->adc0();
	eoverp = ptot/Emc->e0();
	emc0 = Emc->e0();
	nPhi = Emc->nPhi();
	nEta = Emc->nEta();
	phiDist = Emc->phiDist();
	zDist = Emc->zDist();
    }
    StPhysicalHelixD eHelix = tp->dcaGeometry().helix();
    StThreeVectorF dcaPoint = eHelix.at(eHelix.pathLength(pVtx.x(), pVtx.y()));
    StThreeVectorF dcaPoint3d = eHelix.at(eHelix.pathLength(pVtx));
    float dca = 0;
    dca = eHelix.geometricSignedDistance(pVtx.x(),pVtx.y());
    float dca3d = 0;
    dca3d = eHelix.geometricSignedDistance(pVtx);
    float nsige = tp->nSigmaElectron();
    float nsigpi = tp->nSigmaPion();
    float nsigk = tp->nSigmaKaon();
    float nsigp = tp->nSigmaProton();
    float adcCut[4] = {-999, 256, 304, 416};
    int trigCat = 0;
    if(isMB)trigCat = 1;
    if(isMB && (isHLT1 && adc0>=adcCut[1]))trigCat = 2;
    if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2]))trigCat = 3;
    if(isMB && (isHLT1 && adc0>=adcCut[1] && isHLT2 && adc0>=adcCut[2] && isHLT3 && adc0>=adcCut[3]))trigCat = 4;
    if(isMB && !((isHLT1 && adc0>=adcCut[1]) || (isHLT2 && adc0>=adcCut[2]) ||( isHLT3 && adc0>=adcCut[3])))trigCat = 5;
    //if(trigCat==0)return;

    float vZ = mPicoEvent->primaryVertex().z();
    float vX = mPicoEvent->primaryVertex().x();
    float vY = mPicoEvent->primaryVertex().y();
    int refMult = mPicoEvent->refMult();
    int gRefMult= mPicoEvent->grefMult();
    float dcaz = dcaPoint.z()-pVtx.z();
    eh_dcaz = dcaz;
    eh_vz = vZ;
    eh_vy = vY;   
    eh_vx = vX;
    eh_Pxl1Truth = tmc->Pxl1Truth();
    eh_Pxl2Truth = tmc->Pxl2Truth();
    eh_IstTruth = tmc->IstTruth();
    eh_SsdTruth = tmc->SsdTruth();
    eh_h_Pxl1Truth = tmc1->Pxl1Truth();
    eh_h_Pxl2Truth = tmc1->Pxl2Truth();
    eh_h_IstTruth = tmc1->IstTruth();
    eh_h_SsdTruth = tmc1->SsdTruth();
    eh_refmult = refMult;
    eh_grefmult = gRefMult;    
    eh_pt = pt;
    eh_p = ptot;
    eh_h_pt = th->gPt();;
    eh_h_p = th->gMom(pVtx, mPicoDstMaker->picoDst()->event()->bField()).mag();
    eh_event_qx = Q_X;//qx;
    eh_event_qx1 = Q1_X;//qx1;
    eh_event_qx2 = Q2_X;//qx2;
    eh_event_qy = Q_Y;//qy;
    eh_event_qy1 = Q1_Y;//qy1;
    eh_event_qy2 = Q2_Y;//qy2;
    eh_triggercat = trigCat;
    eh_nsige = nsige;
    eh_nsigpi = nsigpi;
    eh_nsigk = nsigk;
    eh_nsigp = nsigp;
    eh_pair_sib = isMcSibling(tmc,tmc1,mPicoDstMaker->picoDst());
    eh_h_nsige = th->nSigmaElectron();
    eh_h_nsigpi = th->nSigmaPion();
    eh_h_nsigk = th->nSigmaKaon();
    eh_h_nsigp = th->nSigmaProton();
    eh_h_ismc =isMcTrack(th,mPicoDstMaker->picoDst());
    eh_beta = beta;
    eh_phidist = phiDist;
    eh_zdist = zDist;
    eh_dcaxy = dca;
    eh_dca = dca3d;
    eh_eta = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).pseudoRapidity();
    eh_phi = tp->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField()).phi();
    eh_phi2 = TMath::Pi()+TMath::ATan2(-pMom.y(),-pMom.x());
    eh_neta = nEta;
    eh_nphi = nPhi;
    eh_emc0 = emc0;
    eh_yloc = YLoc;
    eh_charge = tp->charge();
    eh_h_charge = th->charge();
    eh_mva = 1;//MVADec;
    eh_event_centrality = centrality;//cen;

    StPhysicalHelixD electronHelix = tp->dcaGeometry().helix();
    StPhysicalHelixD partnerHelix = th->dcaGeometry().helix();
    pair<double,double> ss = electronHelix.pathLengths(partnerHelix);
    StThreeVectorD kAtDcaToPartner = electronHelix.at(ss.first);
    StThreeVectorD pAtDcaToElectron = partnerHelix.at(ss.second);
    // calculate DCA of partner to electron at their DCA
    StThreeVectorD VectorDca = kAtDcaToPartner - pAtDcaToElectron;
    double dca_can = static_cast<float>(VectorDca.mag());
    double displace = partnerHelix.geometricSignedDistance(pVtx);

    eh_pair_dca  = dca_can;
    eh_h_dca = displace;
    eh_h_dcaxy = partnerHelix.geometricSignedDistance(pVtx.x(),pVtx.y());
    StThreeVectorD DecayPoint = (kAtDcaToPartner/2 + pAtDcaToElectron/2) - pVtx;
    StThreeVectorD DecayPos = (kAtDcaToPartner/2 + pAtDcaToElectron/2);
    //mPairDecayR = static_cast<float>(DecayPoint.mag());
    eh_pair_decayr = (sqrt(DecayPoint.x()*DecayPoint.x()+DecayPoint.y()*DecayPoint.y()+DecayPoint.z()*DecayPoint.z())); 
    eh_pair_decaypos = (sqrt(DecayPos.x()*DecayPos.x()+DecayPos.y()*DecayPos.y())); 

    StThreeVectorD const electronMomAtDca = electronHelix.momentumAt(ss.first, mPicoDstMaker->picoDst()->event()->bField() * kilogauss);
    StThreeVectorD const partnerMomAtDca = partnerHelix.momentumAt(ss.second,mPicoDstMaker->picoDst()->event()->bField()  * kilogauss);
   
    StLorentzVectorD electronFourMom(0,0,0,0);
    StLorentzVectorD partnerFourMom(0,0,0,0);

    electronFourMom.setPx(electronMomAtDca.x());
    electronFourMom.setPy(electronMomAtDca.y());
    electronFourMom.setPz(electronMomAtDca.z());
    electronFourMom.setE(sqrt(electronMomAtDca.x()*electronMomAtDca.x()
			      + electronMomAtDca.y()*electronMomAtDca.y()
			      + electronMomAtDca.z()*electronMomAtDca.z() + 0.00051099907*0.00051099907));

    partnerFourMom.setPx(partnerMomAtDca.x());
    partnerFourMom.setPy(partnerMomAtDca.y());
    partnerFourMom.setPz(partnerMomAtDca.z());
    partnerFourMom.setE(sqrt(partnerMomAtDca.x()*partnerMomAtDca.x()
			     + partnerMomAtDca.y()*partnerMomAtDca.y()
			     + partnerMomAtDca.z()*partnerMomAtDca.z()
			     +  + 0.00051099907*0.00051099907));

    StLorentzVectorF const epairFourMom = electronFourMom + partnerFourMom;

    eh_comb_eta = epairFourMom.pseudoRapidity();
    eh_comb_phi = epairFourMom.phi();
    eh_comb_mass = epairFourMom.m();

    StThreeVectorD pair_mom(epairFourMom.x(),epairFourMom.y(),epairFourMom.z());
    StThreeVectorD Position = (kAtDcaToPartner + pAtDcaToElectron)/2.0; 
    StPhysicalHelixD pHelix(pair_mom,Position,0,0);
   
    eh_comb_dcaxy = pHelix.geometricSignedDistance(pVtx.x(),pVtx.y());  
    eh_comb_dca = pHelix.geometricSignedDistance(pVtx);
    int tempp1;
    float tempp2;
    int tempp3=0;
    getParent(mPicoDstMaker->picoDst(),tmc,tempp1,tempp3,tempp2,true);
    eh_head=tempp3;
    int parentGid=0;
    int gparentGid=0;
    int ggparentGid=0;
    float parentPt=0;
    float gparentPt=0;
    float ggparentPt=0;
    eh_id = tmc->GePid();
    if(tmc->parentId() == tmc->mcId()){
	parentGid  = tmc->GePid();
    }
    else if(tmc->parentId() != Pico::USHORTMAX){ 
	StPicoMcTrack *mcParentTrk = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(tmc->parentId()-1);
	parentGid  = mcParentTrk->GePid();
	parentPt  = mcParentTrk->Mom().perp();
	if(mcParentTrk->parentId() != Pico::USHORTMAX && mcParentTrk->parentId() != mcParentTrk->mcId()){ 
	    StPicoMcTrack *mcgParentTrk = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(mcParentTrk->parentId()-1);
	    gparentGid  = mcgParentTrk->GePid();
	    gparentPt  = mcParentTrk->Mom().perp();
	    if(mcgParentTrk->parentId() != Pico::USHORTMAX && mcgParentTrk->parentId() != mcgParentTrk->mcId()){ 
		StPicoMcTrack *mcggParentTrk = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(mcgParentTrk->parentId()-1);
		ggparentGid  = mcggParentTrk->GePid();
		ggparentPt  = mcParentTrk->Mom().perp();
	    }
	}
    }

    eh_parentid = parentGid;
    eh_gparentid = gparentGid;
    eh_ggparentid = ggparentGid;    
    eh_parentpt = parentPt;
    eh_gparentpt = gparentPt;
    eh_ggparentpt = ggparentPt;
    eh_run_id = mPicoDstMaker->picoDst()->event()->runId();
    EH_tree->Fill();
}
float StPicoMcNpeAnaMaker::getDLL(StPicoTrack const *track){
    float pt = track->gPt();
    float nsige = track->nSigmaElectron();
    float nsigpi = track->nSigmaPion();
    StThreeVectorF const pMom = track->gMom(mPicoDstMaker->picoDst()->event()->primaryVertex(), mPicoDstMaker->picoDst()->event()->bField());   
    float ptot = pMom.mag();
    float eoverp = 0;
    float phiDist = 0;
    float zDist = 0;
    float emc0=0;
    float beta = 0;
    float adc0 = 0;
    float mass = 0;
    float nPhi = 0;
    float nEta = 0;
    int index2tof = track->bTofPidTraitsIndex();
    if(index2tof>=0) {
	StPicoBTofPidTraits *tofPid = mPicoDstMaker->picoDst()->btofPidTraits(index2tof);
	if(tofPid){
	    beta = tofPid->btofBeta();
	}
    }
    if (track->emcPidTraitsIndex() >= 0) {
	StPicoEmcPidTraits * Emc = mPicoDstMaker->picoDst()->emcPidTraits(track->emcPidTraitsIndex());
	eoverp = ptot/Emc->e0();
	emc0 = Emc->e0();
	phiDist = Emc->phiDist();
	zDist = Emc->zDist();
	nPhi = Emc->nPhi();
	nEta = Emc->nEta();
    }
    int bin1 = mElectronWeights[0]->FindBin(ptot/emc0);
    int bin2 = mElectronWeights[1]->FindBin(nsige);
    int bin3 = mElectronWeights[2]->FindBin((1/beta - 1/(ptot / TMath::Sqrt(ptot*ptot+0.00051099907*0.00051099907)))/ (1/beta));
    int bin4 = mElectronWeights[3]->FindBin(zDist);
    int bin5 = mElectronWeights[4]->FindBin(phiDist);
    int bin11 = mPionWeights[0]->FindBin(ptot/emc0);
    int bin22 = mPionWeights[1]->FindBin(nsigpi);
    int bin33 = mPionWeights[2]->FindBin((1/beta - 1/(ptot / TMath::Sqrt(ptot*ptot+0.13957018*0.13957018)))/ (1/beta));
    int bin44 = mPionWeights[3]->FindBin(zDist);
    int bin55 = mPionWeights[4]->FindBin(phiDist);
    double weight1 = mElectronWeights[0]->GetBinContent(bin1);
    double weight2 = mElectronWeights[1]->GetBinContent(bin2);
    double weight3 = mElectronWeights[2]->GetBinContent(bin3);
    double weight4 = mElectronWeights[3]->GetBinContent(bin4);
    double weight5 = mElectronWeights[4]->GetBinContent(bin5);
    double weight11 = mPionWeights[0]->GetBinContent(bin11);
    double weight22 = mPionWeights[1]->GetBinContent(bin22);
    double weight33 = mPionWeights[2]->GetBinContent(bin33);
    double weight44 = mPionWeights[3]->GetBinContent(bin44);
    double weight55 = mPionWeights[4]->GetBinContent(bin55);
    //if(weight2==0)weight2=1e-7;
    //if(weight22==0)weight22=1e-7;
    if((TMath::Log(0.8*weight1+2.1*weight2+5.3*weight3+0.3*weight4+0.5*weight5) - TMath::Log(0.8*weight11+2.1*weight22+5.3*weight33+0.3*weight44+0.5*weight55))>3000)return 3;
    if((TMath::Log(0.8*weight1+2.1*weight2+5.3*weight3+0.3*weight4+0.5*weight5) - TMath::Log(0.8*weight11+2.1*weight22+5.3*weight33+0.3*weight44+0.5*weight55))<-3000)return -3;
    return TMath::Log(0.7*weight1+3.4*weight2+1.3*weight3+0.8*weight4+1.3*weight5) - TMath::Log(0.7*weight11+3.4*weight22+1.3*weight33+0.8*weight44+1.3*weight55);
}
bool StPicoMcNpeAnaMaker::isIso(StPicoTrack* tp, StPicoMcTrack* tmc){
    //cout << " Iso track size " << mIsoEs.size() << endl;                                                                                                                 
    bool dec = true;
    for(int i=0;i<mIsoEs.size();i++){
        if(mIsoEs[i] == tp->id()-1)continue;
        StPicoTrack* track1 = (StPicoTrack*) mPicoDstMaker->picoDst()->track(mIsoEs[i]);
        StElectronPair *elecPair = new StElectronPair(track1,tp,mIsoEs[i],tp->id()-1,mPicoDstMaker->picoDst()->event()->bField(),mPicoDstMaker->picoDst()->event()->primaryVertex());
        double mass = elecPair->pairMass();
        double dca = elecPair->pairDca();
        double decayr = elecPair->pairDecayR();
        double prod = track1->charge()*tp->charge();
        if(mass<0.15 && dca<0.2 && prod<0 && decayr<9){
            if(!isMcTrack(track1,mPicoDstMaker->picoDst()))dec = false;
            else{
                StPicoMcTrack *tmc1 = (StPicoMcTrack*)mPicoDstMaker->picoDst()->mctrack(getMcTrack(track1,mPicoDstMaker->picoDst()));
                if(isMcSibling(tmc,tmc1,mPicoDstMaker->picoDst())) dec = false;
            }
	}
    }
    return dec;
}
