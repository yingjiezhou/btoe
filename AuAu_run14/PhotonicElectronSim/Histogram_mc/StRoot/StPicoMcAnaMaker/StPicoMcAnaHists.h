#ifndef StPicoMcAnaHists__h
#define StPicoMcAnaHists__h

/* **************************************************
 *  A class to create and save my D0 analysis histograms.
 *
 *  Authors: Mustafa Mustafa (mmustafa@lbl.gov)
 *
 * **************************************************
 */

#include "TObject.h"
#include "StLorentzVectorF.hh"
#include "TH2.h"

class TH1F;
class TH2F;
class TH3F;
class TFile;
class TString;
class StPicoPrescales;
class StPicoEvent;
class StPicoMcTrack;
class StPicoTrack;
class StKaonPion;


class StPicoMcAnaHists: public TObject
{
  public:
   StPicoMcAnaHists(const char * fileBaseName);
   virtual ~StPicoMcAnaHists(){;};
   void closeFile();
   void addMcTrack(StPicoMcTrack const * const);
   void addRcTrack(StPicoTrack const * const);
   void addMatchedTrack(StPicoMcTrack const * const, StPicoTrack const * const);
  private:
   //StPicoMcAnaHists();
   TFile* mOutFile;
   // MC track information
   TH2*   mMcAllTracks_pt_phi;
   TH2*   mMcIstTracks_pt_phi;
   TH2*   mMcSsdTracks_pt_phi;
   TH2*   mMcPxl2Tracks_pt_phi;
   TH2*   mMcPxl1Tracks_pt_phi;
   // RC track information
   TH2*   mRcAllTracks_pt_phi;
   TH2*   mRcIstTracks_pt_phi;
   TH2*   mRcSsdTracks_pt_phi;
   TH2*   mRcPxl2Tracks_pt_phi;
   TH2*   mRcPxl1Tracks_pt_phi;
   // RC track information with truth
   TH2*   mRcTruthIstTracks_pt_phi;
   TH2*   mRcTruthSsdTracks_pt_phi;
   TH2*   mRcTruthPxl2Tracks_pt_phi;
   TH2*   mRcTruthPxl1Tracks_pt_phi;

   ClassDef(StPicoMcAnaHists, 1)
};
#endif
