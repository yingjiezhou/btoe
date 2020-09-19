//#define __tpc__afterburn
#include <cmath>
#include <bitset>

#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TF1.h"
#include "TFile.h"
#include "TMath.h"
#include "TString.h"
//
#include "StThreeVector.hh"
#include "../StPicoDstMaker/StPicoEvent.h"
#include "../StPicoDstMaker/StPicoTrack.h"
#include "../StPicoDstMaker/StPicoMcTrack.h"
#include "StarClassLibrary/StRandom.hh"

#include "StMcConstants.h"
#include "StyleUtilities.h"
//#include "StAnaCuts.h"

#include "StPicoMcAnaHists.h"

ClassImp(StPicoMcAnaHists)

StPicoMcAnaHists::StPicoMcAnaHists(const char * fileBaseName) : 
  mHftRatioDenom(NULL), mHftRatioNum(NULL),
  mHftMatchedRatioDenom(NULL), mHftMatchedRatioNum(NULL), mHftMatchedRatioNum_idTruth(NULL), 
  mHftRatioDenom_tight(NULL), mHftRatioNum_tight(NULL), 
  mVtx(NULL), mTpcFitPoints(NULL), mHFTFitPoints(NULL),
  mHftTracksEtaPhi(NULL), mTpcTracksEtaPhi(NULL), 
  mDCAxy_pT(NULL), mDCAz_pT(NULL),
  mDCAxy_pT_idTruth(NULL), mDCAz_pT_idTruth(NULL), tpcProb(NULL)
{
  int nyBins = 25;
  float yBins[nyBins+1];
  for(int ii=0; ii<nyBins+1; ++ii){
    yBins[ii] = -1.0*TMath::Pi() + ii*(2.0*TMath::Pi())/nyBins;
  }
  float phiBins[mcConst::nphibins+1];
  for(int ii=0; ii<mcConst::nphibins+1; ++ii){
    phiBins[ii] = -TMath::Pi()+ii*(2.0*TMath::Pi())/mcConst::nphibins;
  }
  float etaBins[mcConst::netabins+1];
  for(int ii =0; ii<mcConst::netabins+1;++ii){
    etaBins[ii] = -1.0+(ii*2.0/mcConst::netabins);
  }
  mOutFile = new TFile(Form("%s.hfteff.root",fileBaseName),"RECREATE");
  mOutFile -> cd();
  //
  mHftRatioDenom = new TH2F("mHftRatioDenom","mHftRatioDenom",mcConst::nPtBins,mcConst::ptBins,mcConst::nphibins,phiBins);
  mHftRatioNum = new TH2F("mHftRatioNum","mHftRatioNum",mcConst::nPtBins,mcConst::ptBins,mcConst::nphibins,phiBins);
  mHftMatchedRatioDenom = new TH2F("mHftMatchedRatioDenom","mHftMatchedRatioDenom",mcConst::nPtBins,mcConst::ptBins,mcConst::nphibins,phiBins);
  mHftMatchedRatioNum = new TH2F("mHftMatchedRatioNum","mHftMatchedRatioNum",mcConst::nPtBins,mcConst::ptBins,mcConst::nphibins,phiBins);
  mHftMatchedRatioNum_idTruth = new TH2F("mHftMatchedRatioNum_idTruth","mHftMatchedRatioNum_idTruth",mcConst::nPtBins,mcConst::ptBins,mcConst::nphibins,phiBins);
  //
  mHftRatioDenom_tight = new TH2F("mHftRatioDenom_tight","mHftRatioDenom_tight",mcConst::nPtBins,mcConst::ptBins,mcConst::nphibins,phiBins);
  mHftRatioNum_tight = new TH2F("mHftRatioNum_tight","mHftRatioNum_tight",mcConst::nPtBins,mcConst::ptBins,mcConst::nphibins,phiBins);
  //Vertex Position
  mVtx = new TH3F("mVx","Primary vertrex x position",300,-1.5,1.5,300,-1.5,1.5,600,-6,6);
  //
  mTpcFitPoints=new TH1I("mTpcFitPoints","mTpcFitPoints",25,20,45);
  mHFTFitPoints=new TH1I("mHFTFitPoints","mHFTFitPoints",25,20,45);
  mHftTracksEtaPhi=new TH2F("mHftTracksEtaPhi","mHftTracksEtaPhi",mcConst::netabins, etaBins, mcConst::nphibins, phiBins);
  mTpcTracksEtaPhi=new TH2F("mTpcTracksEtaPhi","mTpcTracksEtaPhi",mcConst::netabins, etaBins, mcConst::nphibins, phiBins);
  //
  mDCAxy_pT=new TH2F("mDCAxy_pT","mDCAxy_pT",mcConst::nDcas,mcConst::DcaEdge, mcConst::nPtBins,mcConst::ptBins);
  mDCAz_pT=new TH2F("mDCAz_pT","mDCAz_pT",mcConst::nDcas,mcConst::DcaEdge, mcConst::nPtBins,mcConst::ptBins);
  //
  mDCAxy_pT_idTruth=new TH2F("mDCAxy_pT_idTruth","mDCAxy_pT_idTruth",mcConst::nDcas,mcConst::DcaEdge, mcConst::nPtBins,mcConst::ptBins);
  mDCAz_pT_idTruth=new TH2F("mDCAz_pT_idTruth","mDCAz_pT_idTruth",mcConst::nDcas,mcConst::DcaEdge, mcConst::nPtBins,mcConst::ptBins);
  //
  TFile *tpcDist = new TFile("./StRoot/StPicoMcAnaMaker/tpcDist.root","OPEN");
  tpcProb=(TH2*)tpcDist->Get("h");
  mRandom = new StRandom();
  int seed = time(NULL);
  mRandom->setSeed(seed);
}
void StPicoMcAnaHists::addEvent(StPicoEvent const * const event)
{
  StThreeVectorF rcVtx = event->primaryVertex();
  mVtx->Fill(rcVtx.x(),rcVtx.y(),rcVtx.z());
  //
  nPxlInnerHits.push_back(event->numberOfPxlInnerHits());
  nPxlOuterHits.push_back(event->numberOfPxlOuterHits());
  nIstHits.push_back(event->numberOfIstHits());
}
void StPicoMcAnaHists::addMatchedVertex(StThreeVectorF rcVtx, StThreeVectorF mcVtx){
  mVtx->Fill(rcVtx.x(),rcVtx.y(),rcVtx.z());
}
void StPicoMcAnaHists::addMatchedTrack(StPicoEvent const * const event, StPicoMcTrack const * const mctrk, StPicoTrack const * const trk){
  //For numerator only
  StThreeVectorF pVtx = event->primaryVertex();
  StPhysicalHelixD helix = trk->dcaGeometry().helix();
  double dcaXy = helix.geometricSignedDistance(pVtx.x(), pVtx.y());
  StThreeVectorF dcaPoint = helix.at(helix.pathLength(pVtx.x(), pVtx.y()));
  double dcaZ = dcaPoint.z() - pVtx.z();
  bool is_num = TMath::Abs(dcaXy)<1.0 && TMath::Abs(dcaZ)<1.0;
  //
  StThreeVectorF mom = trk->gMom(pVtx, event->bField());
  float const pt = mom.perp();
  float const phi = trk->gMom(trk->dcaGeometry().origin(), event->bField()).phi(); 
  float const eta  = trk->gMom(trk->dcaGeometry().origin(), event->bField()).pseudoRapidity(); 
  //
  mHftMatchedRatioDenom->Fill(pt,phi);
  // mTpcTracksEtaPhi->Fill(eta,phi);
  //
  short map = trk->map0();
  std::bitset<16> x(map), a(2), b(4);
  //0000010
  bool pxl1 = ( (map&0x2) != 0);
  //0001100
  bool pxl2 = ( (map&0xC) != 0); 
  //0011000
  bool ist = ( (map&0x30) != 0);
  //1100000
  bool ssd = ( (map&0xC0) != 0);
  if( !pxl1 || !pxl2 || !ist)  return;
  if( !is_num ) return;
  
  bool pxlTruth = mctrk->Pxl1Truth() != 0 && mctrk->Pxl2Truth() != 0;
  bool istTruth = mctrk->IstTruth() != 0 ;
  mHftMatchedRatioNum->Fill(pt,phi);
  if( pxlTruth && istTruth){
    mHftMatchedRatioNum_idTruth->Fill(pt,phi);
    mDCAxy_pT_idTruth->Fill(dcaXy,pt);
    mDCAz_pT_idTruth->Fill(dcaZ,pt);
  }
  return;
}
void StPicoMcAnaHists::addRcTrack(StPicoEvent const * const event, StPicoTrack const * const trk){
  //For numerator only
  StThreeVectorF pVtx = event->primaryVertex();
  StPhysicalHelixD helix = trk->dcaGeometry().helix();
  double dcaXy = helix.geometricSignedDistance(pVtx.x(), pVtx.y());
  StThreeVectorF dcaPoint = helix.at(helix.pathLength(pVtx.x(), pVtx.y()));
  double dcaZ = dcaPoint.z() - pVtx.z();
  bool is_num = TMath::Abs(dcaXy)<1.0 && TMath::Abs(dcaZ)<1.0;
  //
  StThreeVectorF mom = trk->gMom(pVtx, event->bField());
  float const pt = mom.perp();
  float const phi = trk->gMom(trk->dcaGeometry().origin(), event->bField()).phi(); 
  float const eta  = trk->gMom(trk->dcaGeometry().origin(), event->bField()).pseudoRapidity(); 
#ifdef __tpc__afterburn
  if( !keepTPCTrack(eta,phi) )
    return;
#endif
  //
  //cout<<"Here "<<trk->nHitsFit()<<" "<<pt<<" "<<eta<<" "<<phi<<endl;
  mTpcFitPoints->Fill(trk->nHitsFit());
  mHftRatioDenom->Fill(pt,phi);
  mTpcTracksEtaPhi->Fill(eta,phi);
  //
  short map = trk->map0();
  std::bitset<16> x(map), a(2), b(4);
  //0000010
  bool pxl1 = ( (map&0x2) != 0);
  //0001100
  bool pxl2 = ( (map&0xC) != 0); 
  //0011000
  bool ist = ( (map&0x30) != 0);
  //1100000
  bool ssd = ( (map&0xC0) != 0);
  if( !pxl1 || !pxl2 || !ist)  return;
  mDCAxy_pT->Fill(dcaXy,pt);
  mDCAz_pT->Fill(dcaZ,pt);
  if( !is_num ) return;
  mHFTFitPoints->Fill(trk->nHitsFit());
  mHftRatioNum->Fill(pt,phi);
  mHftTracksEtaPhi->Fill(eta,phi);
  //
  //bool pxlTruth = mctrk->Pxl1Truth() != 0 && mctrk->Pxl2Truth() != 0;
  //bool istTruth = mctrk->IstTruth() != 0 ;
  //if( pxlTruth && istTruth)
  //  mHftRatioNum_idTruth->Fill(pt,phi);

  return;
}
void StPicoMcAnaHists::addRcTrack_Tight(StPicoEvent const * const event, StPicoTrack const * const trk){
  //For numerator only
  StThreeVectorF pVtx = event->primaryVertex();
  StPhysicalHelixD helix = trk->dcaGeometry().helix();
  double dcaXy = helix.geometricSignedDistance(pVtx.x(), pVtx.y());
  StThreeVectorF dcaPoint = helix.at(helix.pathLength(pVtx.x(), pVtx.y()));
  double dcaZ = dcaPoint.z() - pVtx.z();
  bool is_num = TMath::Abs(dcaXy)<1.0 && TMath::Abs(dcaZ)<1.0;
  //float const pt = mctrk->Mom().perp();
  //float const phi = mctrk->Mom().phi();
  //float const pt = trk->gPt();
  StThreeVectorF mom = trk->gMom(pVtx, event->bField());
  float const pt = mom.perp();
  //cout<<"Lomnitz!!!! "<<pt<<" vs "<<mom.perp()<<endl; 
  float const phi = trk->gMom(trk->dcaGeometry().origin(), event->bField()).phi(); 
  //
  mHftRatioDenom_tight->Fill(pt,phi);
  //
  short map = trk->map0();
  std::bitset<16> x(map), a(2), b(4);
  //0000010
  bool pxl1 = ( (map&0x2) != 0);
  //0001100
  bool pxl2 = ( (map&0xC) != 0); 
  //0011000
  bool ist = ( (map&0x30) != 0);
  //1100000
  bool ssd = ( (map&0xC0) != 0);
  if( !pxl1 || !pxl2 || !ist || !is_num) return;
  mHftRatioNum_tight->Fill(pt,phi);

  return;
}
void StPicoMcAnaHists::addMatchedTrack_Tight(StPicoEvent const * const event, StPicoMcTrack const * const mctrk, StPicoTrack const * const trk){

  //float const pt = mctrk->Mom().perp();
  //float const phi = mctrk->Mom().phi();
  float const pt = trk->gPt();
  float const phi = trk->gMom(trk->dcaGeometry().origin(), event->bField()).phi(); 
  //
  mHftRatioDenom_tight->Fill(pt,phi);
  //
  short map = trk->map0();
  std::bitset<16> x(map), a(2), b(4);
  //0000010
  bool pxl1 = ( (map&0x2) != 0);
  //0001100
  bool pxl2 = ( (map&0xC) != 0); 
  //0011000
  bool ist = ( (map&0x30) != 0);
  //1100000
  bool ssd = ( (map&0xC0) != 0);
  //Tru hit association
  bool pxlTruth = mctrk->Pxl1Truth() != 0 && mctrk->Pxl2Truth() != 0;
  bool istTruth = mctrk->IstTruth() != 0 ; 
  bool ssdTruth = mctrk->SsdTruth() != 0 ; 

  if( !pxl1 || !pxl2 || !ist) return;
  mHftRatioNum_tight->Fill(pt,phi);

  return;
}
//
void StPicoMcAnaHists::closeFile()
{
  mOutFile->cd();
  //
  mHftRatioDenom->Write();
  mHftRatioNum->Write();
  mHftMatchedRatioDenom->Write();
  mHftMatchedRatioNum->Write();
  mHftMatchedRatioNum_idTruth->Write();
  //
  mHftRatioDenom_tight->Write();
  mHftRatioNum_tight->Write();
  //
  mTpcFitPoints->Write();
  mHFTFitPoints->Write();
  //
  mHftTracksEtaPhi->Write();
  mTpcTracksEtaPhi->Write();
  //
  int nEvents = nPxlInnerHits.size();
  TH1* mPxlHitsInner = new TH1I("mPxlHitsInner","No. hits in PXL inner vs event",4000, 0,20000);
  TH1* mPxlHitsOuter = new TH1I("mPxlHitsOuter","No. hits in PXL outer vs event",4000, 0,20000);
  TH1* mIstHits = new TH1I("mIstHits","No. hits in IST vs event",100,0,5000);
  for(int iEvent =0; iEvent<nPxlInnerHits.size(); ++iEvent ){
    mPxlHitsInner->Fill(nPxlInnerHits[iEvent]);
    mPxlHitsOuter->Fill(nPxlOuterHits[iEvent]);
    mIstHits->Fill(nIstHits[iEvent]);
  }
  mPxlHitsInner->Write();
  mPxlHitsOuter->Write();
  mIstHits->Write();
  mVtx->Write();
  mDCAxy_pT->Write();
  mDCAz_pT->Write();
  mDCAxy_pT_idTruth->Write();
  mDCAz_pT_idTruth->Write();
  mOutFile->Close();
}
bool StPicoMcAnaHists::keepTPCTrack(float eta, float phi)
{
  int etaBin = tpcProb->GetXaxis()->FindBin(eta);
  int phiBin = tpcProb->GetYaxis()->FindBin(phi);
  if(mRandom->flat() > tpcProb->GetBinContent(etaBin,phiBin))
    return false;
  return true;
}
