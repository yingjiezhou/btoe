#include <cmath>
#include <bitset>

#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TMath.h"
#include "TString.h"
#include "../StPicoDstMaker/StPicoEvent.h"
#include "../StPicoDstMaker/StPicoTrack.h"
#include "../StPicoDstMaker/StPicoMcTrack.h"

#include "StMcConstants.h"
//#include "StAnaCuts.h"

#include "StPicoMcAnaHists.h"

ClassImp(StPicoMcAnaHists)

StPicoMcAnaHists::StPicoMcAnaHists(const char * fileBaseName) : 
  mMcAllTracks_pt_phi(NULL), mMcIstTracks_pt_phi(NULL), mMcSsdTracks_pt_phi(NULL),
  mMcPxl2Tracks_pt_phi(NULL), mMcPxl1Tracks_pt_phi(NULL),
  mRcAllTracks_pt_phi(NULL), mRcIstTracks_pt_phi(NULL), mRcSsdTracks_pt_phi(NULL),
  mRcPxl2Tracks_pt_phi(NULL), mRcPxl1Tracks_pt_phi(NULL),
  mRcTruthIstTracks_pt_phi(NULL), mRcTruthSsdTracks_pt_phi(NULL),
  mRcTruthPxl2Tracks_pt_phi(NULL), mRcTruthPxl1Tracks_pt_phi(NULL)
{
  mOutFile = new TFile(Form("%s.hfteff.root",fileBaseName),"RECREATE");
  mOutFile -> cd();
  //Mc Track info
  mMcAllTracks_pt_phi = new TH2F("mMcAllTracks_pt_phi","AllMcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mMcIstTracks_pt_phi = new TH2F("mMcIstTracks_pt_phi","IstMcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mMcSsdTracks_pt_phi = new TH2F("mMcSsdTracks_pt_phi","SsdMcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mMcPxl2Tracks_pt_phi = new TH2F("mMcPxl2Tracks_pt_phi","Pxl2McTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mMcPxl1Tracks_pt_phi = new TH2F("mMcPxl1Tracks_pt_phi","Pxl1McTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  //Rc Track info
  mRcAllTracks_pt_phi = new TH2F("mRcAllTracks_pt_phi","AllRcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mRcIstTracks_pt_phi = new TH2F("mRcIstTracks_pt_phi","IstRcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mRcSsdTracks_pt_phi = new TH2F("mRcSsdTracks_pt_phi","SsdRcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mRcPxl2Tracks_pt_phi = new TH2F("mRcPxl2Tracks_pt_phi","Pxl2RcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mRcPxl1Tracks_pt_phi = new TH2F("mRcPxl1Tracks_pt_phi","Pxl1RcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  //Truth
  mRcTruthIstTracks_pt_phi = new TH2F("mRcTruthIstTracks_pt_phi","IstRcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mRcTruthSsdTracks_pt_phi = new TH2F("mRcTruthSsdTracks_pt_phi","SsdRcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mRcTruthPxl2Tracks_pt_phi = new TH2F("mRcTruthPxl2Tracks_pt_phi","Pxl2RcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());
  mRcTruthPxl1Tracks_pt_phi = new TH2F("mRcTruthPxl1Tracks_pt_phi","Pxl1RcTracks;pt;phi",mcConst::pTbins,0,2.0,100,-1.0*TMath::Pi(), TMath::Pi());

}
void StPicoMcAnaHists::addMcTrack(StPicoMcTrack const * const trk){
  float const pt = trk->Mom().perp();
  float const phi = trk->Mom().phi();
  if( trk->hitsTpc() < 15) return;
  mMcAllTracks_pt_phi->Fill(pt, phi);
  if( trk->hitsIst() < 1) return;
  mMcIstTracks_pt_phi->Fill(pt, phi);
  //Not including SSD just yet
  if( trk->hitsPxl2() < 1) return;
  mMcPxl2Tracks_pt_phi->Fill(pt, phi);
  if( trk->hitsPxl1() < 1) return;
  mMcPxl1Tracks_pt_phi->Fill(pt, phi);
  return;
}
void StPicoMcAnaHists::addMatchedTrack(StPicoMcTrack const * const mctrk, StPicoTrack const * const trk){

  float const pt = mctrk->Mom().perp();
  float const phi = mctrk->Mom().phi();

  mRcAllTracks_pt_phi->Fill(pt, phi);
  
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

  if( !ist ) return;
  mRcIstTracks_pt_phi->Fill(pt, phi);
  if ( mctrk->IstTruth() != 0 )
    mRcTruthIstTracks_pt_phi->Fill(pt, phi);;

  if( !pxl2 ) return;
  mRcPxl2Tracks_pt_phi->Fill(pt, phi);
  if( mctrk->Pxl2Truth() != 0 )
    mRcTruthPxl2Tracks_pt_phi->Fill(pt, phi);

  if( !pxl1 ) return;
  mRcPxl1Tracks_pt_phi->Fill(pt, phi);
  if( mctrk->Pxl1Truth() != 0 )
    mRcTruthPxl1Tracks_pt_phi->Fill(pt, phi);

  return;
}
void StPicoMcAnaHists::closeFile()
{
  mOutFile->cd();
  // MC track information
  mMcAllTracks_pt_phi->Write();
  mMcIstTracks_pt_phi->Write();
  mMcSsdTracks_pt_phi->Write();
  mMcPxl2Tracks_pt_phi->Write();
  mMcPxl1Tracks_pt_phi->Write();
  // RC track information
  mRcAllTracks_pt_phi->Write();
  mRcIstTracks_pt_phi->Write();
  mRcSsdTracks_pt_phi->Write();
  mRcPxl2Tracks_pt_phi->Write();
  mRcPxl1Tracks_pt_phi->Write();
  // RC track information with truth
  mRcTruthIstTracks_pt_phi->Write();
  mRcTruthSsdTracks_pt_phi->Write();
  mRcTruthPxl2Tracks_pt_phi->Write();
  mRcTruthPxl1Tracks_pt_phi->Write();
  mOutFile->Close();
}
