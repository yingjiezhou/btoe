#ifndef StPicoMcAnaMaker_h
#define StPicoMcAnaMaker_h

#include "StMaker.h"
#include "TNtuple.h"

#include "StarClassLibrary/StThreeVectorF.hh"
#include "StEvent/StDcaGeometry.h"

#include "StPicoDstMaker/StPicoEvent.h"
#include "StPicoDstMaker/StPicoMcEvent.h"

#include "StPicoDstMaker/StPicoTrack.h"
#include "StPicoDstMaker/StPicoMcTrack.h"

#include "StPicoMcAnaMaker/StPicoMcAnaHists.h"
//class StThreeVectorF;
class StPicoDst;
class StPicoDstMaker;
class StPicoEvent;
class StPicoTrack;
class StPicoMcTrack;
class TString;
class TH1F;
class TH2F;
class TTree;
class StDcaGeometry;
class StPicoMcAnaHists;

class StPicoMcAnaMaker : public StMaker
{
 public: 
  StPicoMcAnaMaker(int  parentGeantId, TString  name,   TString outname, StPicoDstMaker *picoMaker);
  virtual ~StPicoMcAnaMaker(){;};  
  virtual Int_t Init();
  virtual Int_t Make();
  //virtual Int_t Clear(Option_t *opt=""){;};
  virtual Int_t Finish();

  bool isGoodEvent(StPicoEvent *event);
  bool isGoodMcEvent(StPicoMcEvent *mcEvent);

  int  fill_mTuple_MC(StPicoMcEvent *mcEvent, StPicoEvent *Event,StPicoDst * PicoDst, int &nMcTracks);
  int fill_eventCount(StPicoMcEvent* mcEvt, StPicoEvent* evt);

  bool is_correct_decay(StPicoMcTrack* t);
  void Reset_t1();
  void Reset_t2();

  bool isGoodTrack(StPicoMcTrack const * const trk);
  bool isPrimaryTrack(StPicoMcTrack const * const trk);
  bool isHftTrack(StPicoMcTrack const * const trk);
  bool isGoodTrack(StPicoTrack const * const trk, StPicoEvent const * const evt);
  bool isRcTrack(StPicoMcTrack const * const trk ,StPicoDst const * const PicoDst, int &id);

  //  bool isPrimaryTrack(StPicoMcTrack const * const trk);
 private:
  StPicoDstMaker   *mPicoDstMaker;
  StPicoDst        *mPicoDst;
  StPicoMcAnaHists *mHists;	   

  TNtuple* nt_Single;
  // TNtuple* nt_pair;
  // TNtuple* nt_mc;

  TNtuple* nt_sngl; //.. single track
  TNtuple* nt_pair; //.. pair
  TNtuple* nt_mc; //.. this should contain mc gamma, pi0 and eta (not only embedded)
  TNtuple* mEventCount; //.. For counting purposes

  TFile* mFile;
  TString outfile;
  int parent;


  float t1rp;
  float t1rpt;
  float t1rpx;
  float t1rpy;
  float t1rpz;
  float t1reta;
  float t1rphi;
  float t1nfit;
  float t1ndedx;
  float t1nmax;
  float t1ncom;
  float t1key;
  float t1dca;
  float  t1dcaZ;
  float t1dcaXY;
  float t1isHFT;	  
  float t1chi2;
  float t2rp;
  float t2rpt;
  float t2rpx;
  float t2rpy;
  float t2rpz;
  float t2reta;
  float t2rphi;
  float t2nfit;
  float t2nmax;

  float t2ncom;
  float t2key;
  float t2dca;
  float  t2dcaZ;
  float t2dcaXY;
  float t2isHFT;
  float t2chi2;
  float p1bemcId;
  float p1btowAdc0;
  float p1btowE0;
  float p1btowE;
  float p1bemcDistZ;
  float p1bemcDistPhi;
  float p1bsmdNEta;
  float p1bsmdNPhi;
  float p1btowId;

  float p2bemcId;
  float p2btowAdc0;
  float p2btowE0;
  float p2btowE;
  float p2bemcDistZ;
  float p2bemcDistPhi;
  float p2bsmdNEta;
  float p2bsmdNPhi;
  float p2btowId;
  float t1pr_rp;
  float t1pr_rpT;
  float t2pr_rp;
  float t2pr_rpT;
  float t1_stpcx; //.. first TPC point x
  float t1_stpcy; //.. first TPC point y
  float t1_stpcz; //.. first TPC point z

  float pairDCA;
  float thetaDCA;
  float massPair;
  float mcMassPair;
  float pairPT;
  float dist;

  unsigned int mRefMultPos;
  unsigned int mRefMultNeg;


  ClassDef(StPicoMcAnaMaker, 1)
};
inline bool StPicoMcAnaMaker::isGoodEvent(StPicoEvent *event)
{
  return( fabs(event->primaryVertex().z())<5.0 );   
}
inline bool StPicoMcAnaMaker::isGoodMcEvent(StPicoMcEvent *mcEvent)
{
  return( fabs(mcEvent->pVertex().z())<5.0 );   
}


inline bool StPicoMcAnaMaker::isGoodTrack(StPicoMcTrack const * const trk)
{
  // bool id = trk->GePid()==8 || trk->GePid()==9 ;
  return ( trk->hitsTpc()>15 && fabs(trk->Mom().pseudoRapidity())<1  &&
	   //   trk->Mom().perp() > 0.2 && id );
	   trk->Mom().perp() > 0.2  );
}
inline bool StPicoMcAnaMaker::isGoodTrack(StPicoTrack const * const trk, StPicoEvent const * const evt)
{
  StThreeVectorF pVtx = evt->primaryVertex();
  float B = evt->bField();
  StThreeVectorF mom = trk->gMom(pVtx,B);
  return( trk->nHitsMax()>15 && std::fabs(mom.pseudoRapidity()) &&
	  mom.perp()>0.2);
}
inline bool StPicoMcAnaMaker::isPrimaryTrack(StPicoMcTrack const * const trk)
{
  if ( trk->GePid() == std::numeric_limits<ushort>::max() ) return false;
  return true;

}
inline bool StPicoMcAnaMaker::isHftTrack(StPicoMcTrack const * const trk)
{
  if( trk->hitsPxl1() == 0 ||  trk->hitsPxl2() == 0 || trk->hitsIst() == 0 ) 
    return false;
  return true;
}
#endif
