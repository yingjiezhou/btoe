#include "StPicoMcAnaMaker.h"
#include "StPicoMcAnaHists.h"
#include <assert.h>

#include <map>
#include <iostream>

#include <utility>
#include "Riostream.h"
#include "Rtypes.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TF1.h"
#include "TProfile.h"
#include "TProfile3D.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TClassTable.h"
#include "StLorentzVectorF.hh"


#include "TVector3.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TStyle.h"
#include "SystemOfUnits.h"
#include "StarRoot/TPolynomial.h"
#include "StDcaGeometry.h"
#include "TRSymMatrix.h"
#include "THelixTrack.h"
#include "StBichsel/Bichsel.h"

#include "StPicoDstMaker/StPicoDst.h"
#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StPicoDstMaker/StPicoTrack.h"
#include "StPicoDstMaker/StPicoEvent.h"
#include "StPicoDstMaker/StPicoMcEvent.h"

#include "StPicoDstMaker/StPicoMcTrack.h"
#include "StAssociationMaker/StTrackPairInfo.hh"   
#include "StAssociationMaker/StAssociationMaker.h" 
#include "TLorentzVector.h"
double massElec=0.00051099906;


ClassImp(StPicoMcAnaMaker)

//-----------------------------------------------------------------------------
StPicoMcAnaMaker::StPicoMcAnaMaker(int parentGeantId,TString  name,   TString outname, StPicoDstMaker *picoMaker)
: StMaker(name), mHists(NULL)
{
  mPicoDstMaker = picoMaker;
  mPicoDst = 0;
  outfile=outname;
  parent= parentGeantId;
}
//-----------------------------------------------------------------------------
Int_t StPicoMcAnaMaker::Init(){
  outfile+=TString(".root");
  mFile = new TFile(outfile, "recreate");  
  
  const char* var_sngl = 
    "geantId:p:pt:svx:svy:svz:pgeantId:pp:ppt:"
    "phi:pphi:y:py:eta:peta:label:plabel:gplabel:"
    "rp:rpt:reta:rphi:nfit:ncom:"
    "nmax:vx:vy:vz:dca:dcaxy:dcaz:dcazLine:isHFT:mcHFT:trueHFT:chi2:"
    "nDedxPts:dedx:dedx_2:nSigPi:nSigK:nSigP:nSigE:"
    "bemcId:btowAdc0:btowE0:btowE:bemcDistZ:bemcDistPhi:bsmdNEta:bsmdNPhi:btowId:"
    "pr_rp:pr_rpT:stpcx:stpcy:stpcz:gpgeantId:gppt";
  
  nt_sngl= new TNtuple("nt_sngl", "nt_sngl", var_sngl);

  const char* var_Pair = 
    "p1geantId:p1p:p1pt:p1svx:p1svy:p1svz:p1pgeantId:"
    "p1pp:p1ppt:p1eta:p1peta:p1label:p1rp:p1rpt:p1reta:"
    "p1rphi:p1ndedx:p1nfit:p1ncom:p1nmax:p1dca:p1dcaxy:p1dcaz:p1dcazLine:t1isHFT:t1mcHFT:t1trueHFT:p1chi2:"
    "p2geantId:p2p:p2pt:p2svx:p2svy:p2svz:p2pgeantId:"
    "p2pp:p2ppt:p2eta:p2peta:p2label:p2rp:p2rpt:p2reta:"
    "p2rphi:p2nfit:p2ndedx:p2ncom:p2nmax:p2dca:p2dcaxy:p2dcaz:p2dcazLine:t2isHFT:t2mcHFT:t2trueHFT:p2chi2:"
    "vx:vy:vz:massDCA:mcMassPair:pairDCA:pairPT:theta:xpair:ypair:zpair:mult:dist:"
    "p1bemcId:p1btowAdc0:p1btowE0:p1btowE:p1bemcDistZ:p1bemcDistPhi:p1bsmdNEta:p1bsmdNPhi:p1btowId:"
    "p2bemcId:p2btowAdc0:p2btowE0:p2btowE:p2bemcDistZ:p2bemcDistPhi:p2bsmdNEta:p2bsmdNPhi:p2btowId:"
    "p1pr_rp:p1pr_rpT:p2pr_rp:p2pr_rpT:"
    "p1stpcx:p1stpcy:p1stpcz:"
    "p1gpgeantId:p1gppt:"
    "p2gpgeantId:p2gppt";

    nt_pair= new TNtuple("nt_pair", "nt_pairs", var_Pair);

    const char* var_mc = "pt:y:eta:geantId:svx:svy:svz:stvx:stvy:stvz:eventGenLabel:pgeantId:ppt:py:peta";
    nt_mc = new TNtuple("nt_mc","mc",var_mc);
    
    const char* evtVarList = "runId:mcVx:mcVy:mcVz:vx:vy:vz";
    mEventCount = new TNtuple("eventCount", "eventCount", evtVarList);
    return StMaker::Init();
}
//-----------------------------------------------------------------------------
Int_t StPicoMcAnaMaker::Make(){
  if(!mPicoDstMaker) {
    LOG_WARN << " No PicoDstMaker! Skip! " << endm;
    return kStWarn;
  }
  mPicoDst = mPicoDstMaker->picoDst();
  if(!mPicoDst) {
    LOG_WARN << " No PicoDst! Skip! " << endm;
    return kStWarn;
  }
  //  MC Event
  StPicoMcEvent *mcEvent = (StPicoMcEvent *)mPicoDst->mcevent();
  if (!mcEvent) {
    LOG_WARN << "No StMcEvent" << endm;
    return kStWarn;
  }

  // Evet
  StPicoEvent *event = (StPicoEvent *)mPicoDst->event();
  
  if (!event) {
    LOG_WARN << "No StEvent" << endm;
    return kStWarn;
  }
  
  StThreeVectorF pVtx(-999.,-999.,-999.);
  StThreeVectorF pVtxErr(0.,0.,0.);
  if(event) {
    pVtx = event->primaryVertex();
    pVtxErr = event->primaryVertexError();
  }
  
  // cout<<" parent = "<<parent<<endl;                                       
  // if(parent==1)                                                           
  //   cout<<" .....gamma conversion..... "<<endl;                         
  // else if(parent==7)                                                    
  //   cout<<" .....pi0 dalitz..... "<<endl;                               
  // // else if(parent==10017)                                                  
  // //   cout<<" .....eta dalitz..... "<<endl;                               
  // else {                                                                  
  //   cout<<" ... no such parent as "<<parent<<endl;                      
  //   // exit(0);                                                            
  //  }    
  

  int nMCTracks = -1;
  // if(isGoodMcEvent(mcEvent))
  //   {
  //     cout<<".......good Mc Event"<<endl;
  //   fill_mTuple_MC(event,nMCTracks);
  //   }
  
  fill_mTuple_MC(mcEvent,event,mPicoDst,nMCTracks);
  fill_eventCount(mcEvent,event); 
  return kStOk;
}
Int_t StPicoMcAnaMaker::Finish()
{
  mFile->cd();
  nt_sngl->Write();
  nt_pair->Write();
  nt_mc->Write();
  mEventCount->Write();


  // mh3mcHFTVsEtaVspt_pi->Sumw2();
  // mh3mcHFTVsEtaVspt_pi0_e->Sumw2();
  // mh3mcHFTVsEtaVspt_gamma_e->Sumw2();

  // mh3mcHFTVsEtaVspt_pi->Write();
  // mh3mcHFTVsEtaVspt_pi0_e->Write();
  // mh3mcHFTVsEtaVspt_gamma_e->Write();
  mFile->Close();

  return kStOk;
}
bool StPicoMcAnaMaker::isRcTrack(StPicoMcTrack const * const PicoMcTrack,StPicoDst const * const  PicoDst,int &id)
{
  float  Ndecay=0;
  int nMcTracks =  PicoDst->numberOfMcTracks();  
    if(PicoMcTrack->assoId() == Pico::USHORTMAX )
      return false; 
     int temp = Pico::USHORTMAX ;
     for(int i_Rc =0; i_Rc<PicoDst->numberOfTracks(); ++i_Rc){
    StPicoTrack *Trk = (StPicoTrack*)PicoDst->track(i_Rc);
       if(PicoMcTrack->assoId() == Trk->id() ) {
	  temp = i_Rc;
	    break;
       }
     }
     if (temp == Pico::USHORTMAX) return false;;
     id=temp;
  return true;
}
int StPicoMcAnaMaker::fill_mTuple_MC(StPicoMcEvent* mcEvent, StPicoEvent *Event,StPicoDst *PicoDst, int& nMcTracks)
{
   nMcTracks = 0;
  Int_t Ndecay=0;

  float s_nt_nt[100];
  float p_nt_nt[100];

  nMcTracks =  mPicoDst->numberOfMcTracks();
  cout<<" number of MC tracks is: "<<nMcTracks<<endl; 
  int ncommonhits = 0;
  // float vtx = mcEvent->primaryVertex()->position().x();
  // float vty = mcEvent->primaryVertex()->position().y();
  // float vtz = mcEvent->primaryVertex()->position().z();

  float vtx = mcEvent->pVertex().x();
  float vty = mcEvent->pVertex().y();
  float vtz = mcEvent->pVertex().z();


  StThreeVectorF coll_vtx(vtx,vty,vtz);
  float mField=(float) Event->bField();
  
  StThreeVectorF pVtx(-999.,-999.,-999.);
  StThreeVectorF pVtxErr(0.,0.,0.);
  if(Event) {
    pVtx = Event->primaryVertex();
    pVtxErr = Event->primaryVertexError();
  }
    
  Float_t mc_nt_array[16];
  StPicoMcTrack *mcTrk1=0;

  // return 0;
  for (unsigned int iTrkMc = 0;  iTrkMc<nMcTracks; iTrkMc++) 
    {
      Reset_t1(); //初始化各个变量而已
      
      mcTrk1 = (StPicoMcTrack*)mPicoDst->mctrack(iTrkMc);
     
      // cout<< "geant ID "<<      mcTrk1->GePid()<<endl;; 
      if(!mcTrk1) 
	
 	{
 	  LOG_WARN << " No McTrack! Skip! " << endm;	 
 	  continue;     
	    
	}     

      float t1svx = -9999;
      float t1svy = -9999;
      float t1svz = -9999;
      if(mcTrk1) 
 	{
 	  t1svx = mcTrk1->Origin().x();
 	  t1svy = mcTrk1->Origin().y();
 	  t1svz = mcTrk1->Origin().z();
	}
      // if(mcTrk1->GePid()==2||mcTrk1->GePid()==3)
      // 	{
 	  float mcpgId =-999;
 	  float mcppt = -999;
 	  float mcpy = -999;
 	  float mcpeta = -999;
 	  float mcstvx = -999;
 	  float mcstvy = -999;
 	  float mcstvz = -999;
	  StPicoMcTrack *mcTrk_P1=0;  	 
	  StPicoMcTrack *mcTrk_gP1=0;  	 
	  if(mcTrk1->parentId() != Pico::USHORTMAX) //说明他有parent
 	    {
	      
	      for(int i_McP=0; i_McP<nMcTracks; i_McP++){
		if(((StPicoMcTrack*)(mPicoDst->mctrack(i_McP)))->mcId()==mcTrk1->parentId()) { // 找到了这条track 的parent track
		  mcTrk_P1 = (StPicoMcTrack*)mPicoDst->mctrack(i_McP); 
		  break;;
		}   
	      } 
	      mcpgId = mcTrk_P1 ->GePid();
 	      mcppt = mcTrk_P1->Mom().perp();
 	      mcpy = mcTrk_P1->Mom().y();
 	      mcpeta = mcTrk_P1->pseudorapidity();

	     
	      if(mcTrk_P1->parentId() != Pico::USHORTMAX)
		{
		  for(int i_McP=0; i_McP<nMcTracks; i_McP++){
		    if(((StPicoMcTrack*)(mPicoDst->mctrack(i_McP)))->mcId()==mcTrk_P1->parentId()) {
		      mcTrk_gP1 = (StPicoMcTrack*)mPicoDst->mctrack(i_McP); //grandMParent
		      break;;
		    }   
		  } 
		  // 	  if(mcTrk_gP1 ->GePid()==7) cout<< " "<<mcpgId<< "  "<<mcTrk1->GePid()<<" "<<mcTrk_gP1->Mom().perp()<<endl;
		}	
	    }    
	  // 	  continue;
 	  //stop vertex
	  // cout<< "mcpgId"<<mcTrk1->GePid()<<endl;
	  // if()	

	   if(mcTrk1->GePid()!=1&&mcTrk1->GePid()!=2&&mcTrk1->GePid()!=3
	      &&mcTrk1->GePid()!=7&&mcTrk1->GePid()!=8&&mcTrk1->GePid()!=9
	      &&mcTrk1->GePid()!=147
	      &&mcTrk1->GePid()!=149
	      &&mcTrk1->GePid()!=10008&&mcTrk1->GePid()!=10009
	      &&mcTrk1->GePid()!=37&&mcTrk1->GePid()!=38) continue;//排除掉除了pi，etam，和gamma decay 出来的粒子之外的粒子

	   //   pi0_daliz.SetPxPyPzE(0.,0.,0.,0.);

	   // //------ check rapidity------------------------
	   // if(mcTrk1->GePid()==147)
	   //   {
	   //     pi0_daliz.SetPxPyPzE(mcTrk1->Mom().x(),mcTrk1->Mom().y(),mcTrk1->Mom().z(),sqrt(mcTrk1->Mom().mag2()+0.1349*0.1349));
	   //   }
	   // cout<< pi0_daliz.Rapidity()<<endl;

	   // //---------------------------------------------

	  
	   Int_t i=0;
 	  mc_nt_array[i++] = mcTrk1->Mom().perp();
 	  mc_nt_array[i++] = (Float_t) -9999.0; // add later 
 	  mc_nt_array[i++] = mcTrk1->pseudorapidity();
 	  mc_nt_array[i++] = (Float_t)mcTrk1->GePid();
 	  mc_nt_array[i++] = t1svx;
 	  mc_nt_array[i++] = t1svy;
 	  mc_nt_array[i++] = t1svz;
 	  mc_nt_array[i++] = mcstvx;
 	  mc_nt_array[i++] = mcstvy;
 	  mc_nt_array[i++] = mcstvz;
 	  mc_nt_array[i++] = (Float_t) -999.; // add later 
 	  mc_nt_array[i++] = mcpgId;
 	  mc_nt_array[i++] = mcppt;
 	  mc_nt_array[i++] = mcpy;
 	  mc_nt_array[i++] = mcpeta;
	  nt_mc->Fill(mc_nt_array);
	 	 
      
	  //  if((mcTrk1->GePid()==2||mcTrk1->GePid()==3)&&mcpgId==parent) Ndecay++;
	  //     if(mcpgId!=parent) continue;
	  
	  int t1geantId = mcTrk1->GePid();
	  float t1phi =(float) mcTrk1->Mom().phi();
	  float t1y = (float)mcTrk1->Mom().y();
	  float t1eta = (float )mcTrk1->pseudorapidity();
	  float t1label = -999.;
	  float t1p = (float) mcTrk1->Mom().mag();
	  
	  float t1pgeantId = -9999;
	  float t1pmom = -9999;
	  float t1ppt= -9999;
	  float t1pphi = -9999;
	  float t1parenty = -9999;
	  float t1peta = -9999;
	  float t1plabel = -9999;
	  
	  if(mcTrk_P1)  //这条track对应的parent 的track
	    {
	      t1pgeantId = mcTrk_P1 ->GePid();  
	      t1pmom = mcTrk_P1->Mom().mag();
	      t1ppt= mcTrk_P1->Mom().perp();
	      t1pphi = mcTrk_P1->Mom().phi();
	      t1parenty = -999;//mcTrk_P1->Mom().y();
	      t1peta = mcTrk_P1->pseudorapidity();
	      t1plabel = -999;
	    }


	  //       cout<< " t1pgeantId  "<< t1pgeantId <<endl;
	  // cout<< "   "<< t1p <<endl;
	  
	  float t1px = mcTrk1->Mom().x();
	  float t1py = mcTrk1->Mom().y(); 
	  
	  float t1pt = sqrt(t1px*t1px+t1py*t1py);
	  
	  float t1gpgeantId = -9999;
	  float t1gppt= -9999;
	  float t1gplabel = -9999;
	  float t1mcHFT=isHftTrack(mcTrk1);
	  float t1trueHFT=trueHftTrack(mcTrk1);

	  // add grand parent
	  if(mcTrk_gP1)
	    {
	      t1gpgeantId=mcTrk_gP1 ->GePid();
	      t1gppt=mcTrk_gP1->Mom().perp();
	    }
	  // if(t1pgeantId!=-9999&&t1geantId==8&&t1pt<1) cout<< "grand parent: "<<t1gpgeantId<<" parent: "<< t1pgeantId<<"geant id "<<t1geantId<<endl; 
	  // if(t1pgeantId!=-9999&&t1geantId==8&&t1pt<1) cout<<  t1pgeantId<<"geant id "<<t1geantId<<endl; 

	  // continue;
	  //.........
	  float t1ndedx = -9999;
	  float dedx = -9999;
	  float dedx_2 = -9999;
	  float nSigPi = -9999;
	  float nSigK = -9999;
	  float nSigP = -9999;
	  float nSigE = -9999;
	  
	  StPicoTrack *Trk1=0;
	  Int_t id1=-999;
	  isRcTrack(mcTrk1,mPicoDst,id1);// 前面填的都是MC track 的信息，下面开始填real track
	  if(id1!=-999)
	    Trk1 = (StPicoTrack*)mPicoDst->track(id1);
	  if(Trk1) //mcTrk1-> Trk1
	    {
	      t1rp = Trk1-> gMom(pVtx,mField).mag(); //   t1rcTrack->geometry()->momentum().mag();
	      t1rpt = Trk1->gMom(pVtx,mField).perp();
	      t1rpx = Trk1->gMom(pVtx,mField).x();
	      t1rpy = Trk1->gMom(pVtx,mField).y();
	      t1rpz = Trk1->gMom(pVtx,mField).z();
	      
	      t1reta = Trk1->gMom(pVtx,mField).pseudoRapidity();
	      t1rphi = Trk1->gMom(pVtx,mField).phi();
	      t1nfit = Trk1->nHitsFit();
	      t1ndedx= Trk1->nHitsDedx();
	
	      t1nmax =Trk1->nHitsMax(); 
	      t1ncom =mcTrk1->tpcCommon(); 
	      t1key = Trk1->id();
	      // t1_stpcx =Trk1->Origin().x();
	      // t1_stpcy =Trk1->Origin().y();
	      // t1_stpcz = Trk1->Origin().z();
	      StPhysicalHelixD helix = Trk1->helix();
	      t1dca = float(helix.geometricSignedDistance(pVtx));
	      StThreeVectorF dcaPoint = helix.at(helix.pathLength(pVtx.x(), pVtx.y()));
	      t1dcaZ = dcaPoint.z() - pVtx.z();
	      t1dcaXY=(float) helix.geometricSignedDistance(pVtx.x(), pVtx.y()); 
	      t1dcaZ = dcaPoint.z() - pVtx.z();


	      double thePath = helix.pathLength(pVtx);
	      StThreeVectorF dcaPos = helix.at(thePath); 

	      StThreeVectorF posDiff = dcaPos - pVtx; 
	      StThreeVectorF mGMom = helix.momentumAt(thePath,mField);   
	      if(sin(mGMom.theta())==0) t1dcaZLine = -9999;  
	      else
		t1dcaZLine = ((-posDiff.x()*cos(mGMom.phi())-posDiff.y()*sin(mGMom.phi()))*cos(mGMom.theta())/sin(mGMom.theta())+posDiff.z());
	      t1isHFT=Trk1->isHFTTrack();
	      
	      // cout<< t1dcaZLine<<endl;

	      dedx =Trk1->nHitsDedx();
	      nSigPi =Trk1->nSigmaPion();
	      nSigK =Trk1->nSigmaKaon();
	      nSigP =Trk1->nSigmaProton();
	      nSigE =Trk1->nSigmaElectron();
	      
	      t1pr_rp =  Trk1->pMom().mag();
	      t1pr_rpT = Trk1->pMom().perp();
	      // t1chi2 = -999.;
	      int nhitmap= Trk1->nHitsMapHFT();
	      
	      // if((Trk1->nHitsMapHFT()>>5 & 0x3))
	      // cout<< " SST "<< (Trk1->nHitsMapHFT()>>5 & 0x3)<<endl;
	    }
	  

      float rc = sqrt(t1svx*t1svx + t1svy*t1svy);//   t1svx = mcTrk1->Origin().x();

      //   if(fabs(vtz)>50 || fabs(t1eta)>1.0 || rc>200) continue;
      // if(t1isHFT==0) continue;
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
      s_nt_nt[ii++] = -999;
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
      s_nt_nt[ii++] = t1dcaXY;
      s_nt_nt[ii++] = t1dcaZ;
      s_nt_nt[ii++] = t1dcaZLine;
      s_nt_nt[ii++] = t1isHFT;
      s_nt_nt[ii++] = t1mcHFT;
      s_nt_nt[ii++] = t1trueHFT;
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

      //      if(t1pgeantId==-9999&&t1geantId==8) cout<< "grand parent: "<<t1gpgeantId<<" parent: "<< t1pgeantId<<"geant id "<<t1geantId<<endl; 
    

      //     continue ;
       // TH3F *mh3mcHFTVsEtaVspt_pi=new TH3F("mh3mcHFTVsEtaVspt_pi","",400,0,20.,100,-1,1,50,0,50);
       // TH3F *mh3mcHFTVsEtaVspt_pi0_e=new TH3F("mh3mcHFTVsEtaVspt_pi0_e","",400,0,20.,100,-1,1,50,0,50);
       // TH3F *mh3mcHFTVsEtaVspt_gamma_e=new TH3F("mh3mcHFTVsEtaVspt_gamma_e","",400,0,20.,100,-1,1,50,0,50);

       // int isPixl1=mcTrk1->hitsPxl1()!=0?1:0;
       // int isPixl2=mcTrk1->hitsPxl2()!=0?1:0;
       // int isist=mcTrk1->hitsIst()!=0?1:0;
       // int isSSD=mcTrk1->hitsSst()!=0?1:0;


       //       cout<< mcTrk1->hitsPxl1()<<" "<<isPixl1<<endl;
      //       int mcHFT=4*isPixl1+2*isPixl2+isist+8*isSSD;



	 // mcpgId!=7&&mcTrk1->GePid()!=8&&mcTrk1->GePid()!=9)  continue;
       // if(mcTrk1->GePid()==8||mcTrk1->GePid()==9) 
       // 	 mh3mcHFTVsEtaVspt_pi->Fill(t1pt,t1eta,mcHFT);
       // if(mcpgId==7&&(mcTrk1->GePid()==2||mcTrk1->GePid()==3)) 
       // 	 mh3mcHFTVsEtaVspt_pi0_e->Fill(t1pt,t1eta,mcHFT);
       // if(mcpgId==1&&(mcTrk1->GePid()==2||mcTrk1->GePid()==3)) 
       // 	 mh3mcHFTVsEtaVspt_gamma_e->Fill(t1pt,t1eta,mcHFT);
       


      if(t1geantId!=2&&t1geantId!=3)  continue; //    int t1geantId = mcTrk1->GePid();
       //     if(t1pgeantId!=147&&t1pgeantId!=149&&t1pgeantId!=7&&t1pgeantId!=1)  continue;
      if(t1pgeantId!=149&&t1pgeantId!=147&&t1pgeantId!=1)  continue;
      // if(t1reta==-9999) continue;

      //     if(t1pgeantId!=149) continue;
      StPicoMcTrack *mcTrk2=0;
      //     for(unsigned int iTrkMc2 =iTrkMc+1;  iTrkMc2<nMcTracks; iTrkMc2++) 
      for(unsigned int iTrkMc2 =0;  iTrkMc2<nMcTracks; iTrkMc2++) 
	{
	  if(iTrkMc==iTrkMc2) continue;

	  Reset_t2();
	  mcTrk2 = (StPicoMcTrack*)mPicoDst->mctrack(iTrkMc2);
	  if(!mcTrk2) 
	    {
	      LOG_WARN << " No McTrack! Skip! " << endm;	 
	      continue;     
	    }

	  if(mcTrk2->GePid()!=2&&mcTrk2->GePid()!=3)  continue;
	  if(mcTrk1->Origin().x()!=mcTrk2->Origin().x()) continue;
	  if (mcTrk1->parentId() != mcTrk2->parentId()) continue;

	  StPicoMcTrack *mcTrk_P2=0;
	  if(mcTrk2->parentId()!= Pico::USHORTMAX)
	    {
	      for(int i_McP=0; i_McP<nMcTracks; i_McP++){
		if(((StPicoMcTrack*)(mPicoDst->mctrack(i_McP)))->mcId()==mcTrk2->parentId()) {
		  mcTrk_P2 = (StPicoMcTrack*)mPicoDst->mctrack(i_McP);  //不需要再次网上判断parent 了
		  break;;
		}   
	      }
	    }


	   float t2svx = -9999;
	   float t2svy = -9999;
	   float t2svz = -9999;
       

      if(mcTrk2) 
 	{
 	  t2svx = mcTrk2->Origin().x();
 	  t2svy = mcTrk2->Origin().y();
 	  t2svz = mcTrk2->Origin().z();
 	 
   
 	}
      
      //        if(mcTrk_P2->GePid()!=parent) continue;
      // if(!(mcTrk1->startVertex() == mcTrk2->startVertex() &&  embedding need this 
      // 	   mcTrk1->parent()->geantId()==t2->parent()->geantId())) continue;


      StLorentzVectorF lVecTemp(mcTrk1->Mom(),mcTrk1->Mom().massHypothesis(massElec));// 计算不变质量的方法和LS4+ 中用到的一样
      StLorentzVectorF lVecTemp2(mcTrk2->Mom(),mcTrk1->Mom().massHypothesis(massElec));
      lVecTemp+=lVecTemp2;
      mcMassPair = lVecTemp.m();
      
      int t2geantId = mcTrk2->GePid();

      float t2eta = mcTrk2->pseudorapidity();

      float t2p = mcTrk2->Mom().mag();

      float t2pgeantId = -9999;
      float t2pmom = -9999;
      float t2ppt= -9999;
      float t2peta = -9999;
         

      if(mcTrk_P2) 
        {
 	  t2pgeantId = mcTrk_P2 ->GePid();  
 	  t2pmom = mcTrk_P2->Mom().mag();
 	  t2ppt= mcTrk_P2->Mom().perp();
	  t2peta = mcTrk_P2->pseudorapidity();
	}
      //     if(t2pgeantId!=149&&t2pgeantId!=7&&t2pgeantId!=147&&t2pgeantId!=1)  continue;	  
      //  if(t1svx!=t2svx) continue;
      if(t2pgeantId!=149&&t2pgeantId!=147&&t2pgeantId!=1) continue;
     
      //     if(t2geantId!=1&&t2geantId!=2&&t2geantId!=3&&t2geantId!=7&&t2geantId!=8&&t2geantId!=9) continue;
      // if(t2pgeantId!=1&&t2pgeantId!=7)  continue;
      // if(t2geantId!=2&&t2geantId!=3)  continue;

      //     cout<< " track id"<< t2geantId<<endl;      
      float t2gpgeantId = -9999;
      float t2gppt= -9999;
      float t2plabel = -9999;

      float t2px = mcTrk2->Mom().x();
      float t2py = mcTrk2->Mom().y();
      float t2mcHFT=isHftTrack(mcTrk2);
      float t2trueHFT=trueHftTrack(mcTrk2);
      
      float t2pt = sqrt(t2px*t2px+t2py*t2py);


      StThreeVectorF posDCA(-9999, -9999, -9999);

      // StPicoTrack *Trk2=0;
      // Int_t id2=-999;
      // isRcTrack(mcTrk2,mPicoDst,id2);
      // //   if(id==-999) continue;
      // if(id2!=-999)
      // 	Trk2 = (StPicoTrack*)mPicoDst->track(id2);

      StPicoTrack *Trk2=0;
      Int_t id2=-999;
      isRcTrack(mcTrk2,mPicoDst,id2);

      if(id2!=-999)
 	Trk2 = (StPicoTrack*)mPicoDst->track(id2);

      if(Trk2)
	{
 	  t2rp = Trk2-> gMom(pVtx,mField).mag(); //   t1rcTrack->geometry()->momentum().mag();
 	  t2rpt = Trk2->gMom(pVtx,mField).perp();
 	  t2rpx = Trk2->gMom(pVtx,mField).x();
 	  t2rpy = Trk2->gMom(pVtx,mField).y();
 	  t2rpz = Trk2->gMom(pVtx,mField).z();

 	  t2reta = Trk2->gMom(pVtx,mField).pseudoRapidity();
 	  t2rphi = Trk2->gMom(pVtx,mField).phi();
 	  t2nfit = Trk2->nHitsFit();
	  t2ndedx= Trk2->nHitsDedx();
 	  t2nmax =Trk2->nHitsMax(); 
	  t2ncom =mcTrk2->tpcCommon(); 
 	  t2key = Trk2->id();

 	  StPhysicalHelixD helix = Trk2->helix();
 	  t2dca = float(helix.geometricSignedDistance(pVtx));
 	  StThreeVectorF dcaPoint = helix.at(helix.pathLength(pVtx.x(), pVtx.y()));
 	  t2dcaZ = dcaPoint.z() - pVtx.z();
 	  t2dcaXY=(float) helix.geometricSignedDistance(pVtx.x(), pVtx.y()); 

	  double thePath = helix.pathLength(pVtx);
	  StThreeVectorF dcaPos = helix.at(thePath);
	  StThreeVectorF mGMom = helix.momentumAt(thePath,mField);   
	  StThreeVectorF posDiff = dcaPos - pVtx; 
	  if(sin(mGMom.theta())==0) t2dcaZLine = -9999;
	  else
	    t2dcaZLine=	 (-posDiff.x()*cos(mGMom.phi())-posDiff.y()*sin(mGMom.phi()))*cos(mGMom.theta())/sin(mGMom.theta())+posDiff.z();

	  t2isHFT=Trk2->isHFTTrack();
 	  t2pr_rp =  Trk2->pMom().mag();
 	  t2pr_rpT = Trk2->pMom().perp();

	  // cout<< " t2pr_rpT "<<t2pr_rpT<<endl; 
	  if(Trk1)
	    {
	      //.. calculate mass, pairDCA, eta  两条track配对的变量，e+e- pair mass and DCA...
	      StPhysicalHelixD helix1 = Trk1->helix();
	      StPhysicalHelixD helix2 = Trk2->helix();
	      //      pair<double,double> pathLength = helix1.pathLengths(helix2,0.01*micrometer,10);
	      pair<double,double> pathLength = helix1.pathLengths(helix2);
	      pairDCA = (helix1.at(pathLength.first) - helix2.at(pathLength.second)).mag();
	      // Get the momentum of each track at the point of closest approach
	      StThreeVectorF p1DCA = helix1.momentumAt(pathLength.first, mField*kilogauss);
	      StThreeVectorF p2DCA = helix2.momentumAt(pathLength.second, mField*kilogauss);
	      thetaDCA = acos(p1DCA.dot(p2DCA)/p1DCA.mag()/p2DCA.mag());
	      StThreeVectorF v1(helix1.at(pathLength.first).x(),
				helix1.at(pathLength.first).y(),
				helix1.at(pathLength.first).z());
	      // v2 is a vector from origin to the point of closest approach on track 2
	      StThreeVectorF v2(helix2.at(pathLength.second).x(),
				helix2.at(pathLength.second).y(),
				helix2.at(pathLength.second).z());

	      posDCA = (v1 + ((v2-v1)*0.5));

	      //  cout<< (v1 + ((v2-v1)*0.5)).x() << " "<<(v2 + ((v1-v2)*0.5)).x()<<" "<<((v1+v2)*0.5).x()<<endl;
	      StLorentzVectorF pathOne;
	      StLorentzVectorF pathTwo;
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

	    }

	}
      //     if(fabs(massPair)>0.24||fabs(pairDCA)>1) continue;
      // if(massPair!=-9999&&(t1svx==t2svx)) 
      //   cout<< " mass"<< massPair<<" "<<t1geantId<< "  "<<t2geantId<<"  "<<t1svx <<"  "<<t2svx<<endl;
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
      p_nt_nt[ii++] = t1dcaXY;
      p_nt_nt[ii++] = t1dcaZ;
      p_nt_nt[ii++] = t1dcaZLine;
      p_nt_nt[ii++] = t1isHFT;
      p_nt_nt[ii++] = t1mcHFT;
      p_nt_nt[ii++] = t1trueHFT;

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
      p_nt_nt[ii++] = t2ndedx;
      p_nt_nt[ii++] = t2ncom;
      p_nt_nt[ii++] = t2nmax;
      p_nt_nt[ii++] = t2dca;
      p_nt_nt[ii++] = t2dcaXY;
      p_nt_nt[ii++] = t2dcaZ;
      p_nt_nt[ii++] = t2dcaZLine;
      p_nt_nt[ii++] = t2isHFT;
      p_nt_nt[ii++] = t2mcHFT;
      p_nt_nt[ii++] = t2trueHFT;

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
      p_nt_nt[ii++] = nMcTracks;
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
      p_nt_nt[ii++] = t1gpgeantId;
      p_nt_nt[ii++] = t1gppt;
      p_nt_nt[ii++] = t2gpgeantId;
      p_nt_nt[ii++] = t2gppt;
      nt_pair->Fill(p_nt_nt);
      //   if(t1gpgeantId==7) cout<< " " << t1pgeantId<< "  "<< t1geantId<<endl;
	}
    }
  return 0;
}
int StPicoMcAnaMaker::fill_eventCount(StPicoMcEvent* mcEvt, StPicoEvent* evt)
{   
  cout<<"Taking event counts..."<<endl;
  float vars[30];
    
    
  // float vpdVz = -999;
  
  // StBTofHeader* tofheader = 0;
  // if(evt->btofCollection())  tofheader = evt->btofCollection()->tofHeader();
  // if(tofheader) vpdVz = tofheader->vpdVz();
    
  int i = 0;
  vars[i++] = (float)evt->runId();
  //  vars[i++] = (float)evt->id();

  vars[i++] = (float)mcEvt->pVertex().x();
  vars[i++] = (float)mcEvt->pVertex().y();
  vars[i++] = (float)mcEvt->pVertex().z();

  vars[i++] = (float)evt->primaryVertex().x(); 
  vars[i++] = (float)evt->primaryVertex().y();  
  vars[i++] = (float)evt->primaryVertex().z();  
  // vars[i++] = vpdVz;
  // vars[i++] = (float)uncorrectedNumberOfPositivePrimaries(*evt);
  // vars[i++] = (float)uncorrectedNumberOfNegativePrimaries(*evt);
  // vars[i++] = (float)evt->runInfo()->zdcCoincidenceRate();
  // vars[i++] = (float)evt->runInfo()->bbcCoincidenceRate();

  // vars[i++] = (float)nMcTracks;
  // vars[i++] = -1.0;
  // vars[i++] = (float)evt->summary()->magneticField()/10;
  // vars[i++] = firedTriggersIndices.at(0);
  // vars[i++] = firedTriggersIndices.at(1);
  // vars[i++] = firedTriggersIndices.at(2);
  // vars[i++] = firedTriggersIndices.at(3);
  // vars[i++] = firedTriggersIndices.at(4);
  // vars[i++] = firedTriggersIndices.at(5);
    
  mEventCount->Fill(vars);
  return kStOk;

}
bool StPicoMcAnaMaker::is_correct_decay(StPicoMcTrack* t)
{
  if(!t) 
    {
    LOG_WARN << " No PicoDstMaker! Skip! " << endm;
    return kFALSE;
    }

  //.. check to make sure it's the right decay ....
  if(t->GePid()!=2 && t->GePid()!=3) return false;
  int    ParentID=-999;
  if(t->parentId() != Pico::USHORTMAX) 
    ParentID = ((StPicoMcTrack *)(mPicoDst->mctrack(t->parentId()))) ->GePid();
  
  if(ParentID!=parent ) return false;
  //  int ndaughter = t->parent()->stopVertex()->numberOfDaughters();

  int corr_daughter = 0;

  // for(int i = 0; i<ndaughter; i++) 
  //   {
  //     StMcTrack* trk = t->parent()->stopVertex()->daughter(i);
  //     int gid = trk->geantId();
      
  //     if((parent==149 || parent==10017) && (gid==2 || gid==3 || gid==1))  
  // 	corr_daughter++; //.. dalitz

  //     if(parent==1 && (gid==2 || gid==3))  //.. conversion
  // 	corr_daughter++;
  //   }

  Bool_t correct_deacy = kFALSE;

  // if(parent==1 && corr_daughter==2 && ndaughter==2) correct_deacy = kTRUE;
  // else if((parent==149 || parent==10017) && (corr_daughter==3 && ndaughter==3)) correct_deacy = kTRUE; // pi0->\gamma e+ e-
  // else if((parent==149 || parent==10017) && (corr_daughter==2 && ndaughter==2)) correct_deacy = kTRUE; // pi0-> \gamma \gamma

  if (ParentID==parent) correct_deacy = kTRUE;   

  return correct_deacy;
}
//_________________________
void StPicoMcAnaMaker:: Reset_t1()
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
  t1dcaZ=-9999;
  t1dcaZLine=-9999;
  t1dcaXY=-9999;
  t1isHFT=-9999;
  t1mcHFT=-9999;
  t1trueHFT=-9999;

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
void StPicoMcAnaMaker:: Reset_t2()
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
  t2ndedx = -9999;
  t2nmax = -9999;
  t2ncom = -9999;
  t2key = -9999;
  t2dca = -9999;
  t2dcaZ=-9999;
  t2dcaZLine=-9999;
  t2dcaXY=-9999;
  t2isHFT=-9999;
  t2mcHFT=-9999;
  t2trueHFT=-9999;
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


