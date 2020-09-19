/*!
 * \class  StPxlMonMaker
 * \author Shusu Shi, LBNL
 * \date   May 2013
 * \Initial Revision.
 */
/***************************************************************************
 *
 * $Id: StPxlMonMaker.h,v 1.17 2014/02/25 01:09:06 smirnovd Exp $
 *
 * Author: Shusu Shi, May 2013
 ***************************************************************************
 *
 * Description:
 * pxl detector QA
 * More information at
 * https://www.star.bnl.gov/protected/heavy/qiuh/HFT/software/PXL_software.pdf
 *
 ***************************************************************************
 *
 * $Log: StPxlMonMaker.h,v $
 * Revision 1.17  2014/02/25 01:09:06  smirnovd
 * Minor fixes not affecting functionality
 *
 * Revision 1.16  2014/02/07 00:15:00  smirnovd
 * Small stylistic improvement + doxygen comments
 *
 * Revision 1.15  2014/02/07 00:14:32  smirnovd
 * Change histogram type to conserve memory
 *
 * Revision 1.14  2014/02/01 19:03:17  smirnovd
 * Fixed default parameter bug
 *
 * Revision 1.13  2014/02/01 02:37:18  smirnovd
 * This commit is intended to sync with what we had in StRoot/StiRnD
 *
 * Revision 1.7  2014/01/28 19:29:42  qiuh
 * *** empty log message ***
 *
 *
 **************************************************************************/

#ifndef StPxlMonMaker_hh
#define StPxlMonMaker_hh

#include <stdint.h>

#include "TString.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TH2F.h"
#include "TH2S.h"
#include "TProfile.h"
#include "TTree.h"
#include "StIOMaker/StIOMaker.h"

class StIOMaker;
class StEvent;
class StTrack;

const Int_t kMaxHits= 5000000;
class StPxlMonMaker : public StMaker
{
public:

   StPxlMonMaker(uint16_t numPixelsPerBin=1, const Char_t *name="pxlMon");
   Int_t  Init();
   Int_t  Make();                      // invoked for every event
   Int_t  Finish();                    // called once at the end
   // virtual const char *GetCVS() const {
   //    static const char cvs[] = "Tag $Name:  $ $Id: StPxlMonMaker.h,v 1.17 2014/02/25 01:09:06 smirnovd Exp $ built "__DATE__" "__TIME__ ;
   //    return cvs;
   // }
   TTree * tree;
   TH2F * hHitbySensor;
   Int_t nRawhits;
   Int_t iRow[kMaxHits];
   Int_t iColumn[kMaxHits];
   Int_t sensorId[kMaxHits];
   Int_t nRawhitsBySensorId[500];
   Int_t iSensor;
   Int_t eventSize;
   Float_t zdc;
   TFile * m_f1;
private:

   void   bookHists();
   void   fillHists();
   void   writeHists();

   uint16_t mNumPixelsPerBin;   //!< Number of rows and columns to group in a bin
   Int_t    mEventCounter;      //!
   Int_t    mNtupleWrite;

   ClassDef(StPxlMonMaker, 0)
};

#endif
