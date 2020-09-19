/* $Id: StIstFastSimMaker.cxx,v 1.31 2015/02/25 21:30:30 jeromel Exp $ */

#include "TGeoManager.h"
#include "TDataSet.h"

#include "StIstSimMaker/StIstFastSimMaker.h"
#include "StEvent/StEvent.h"
#include "StEvent/StEnumerations.h"
#include "StMcEvent/StMcEvent.hh"
#include "StMcEvent/StMcHit.hh"
#include "StMcEvent/StMcIstHit.hh"
#include "StIstUtil/StIstConsts.h"
#include "StEvent/StIstHit.h"
#include "StEvent/StIstHitCollection.h"
#include "StIstDbMaker/StIstDb.h"
#include "StMcEvent/StMcIstHit.hh"
#include "StMcEvent/StMcIstHitCollection.hh"
#include "StThreeVectorF.hh"
#include "tables/St_HitError_Table.h"
// Sensor status
#include "istStat.h"
ClassImp(StIstFastSimMaker)


StIstFastSimMaker::StIstFastSimMaker( const Char_t *name, bool useRandomSeed) : StMaker(name), mIstRot(NULL), mIstDb(NULL), mBuildIdealGeom(kTRUE),
   mRandom(useRandomSeed ? time(0) : 65539), mSmear(kTRUE)
{
}

//____________________________________________________________
Int_t StIstFastSimMaker::Init() {
   LOG_INFO << "StIstFastSimMaker::Init()" << endm;

   return kStOk;
}

//____________________________________________________________
Int_t StIstFastSimMaker::InitRun(int runNo)
{
   LOG_INFO << "StIstFastSimMaker::InitRun" << endm;

   TDataSet *calibDataSet = GetDataBase("Calibrations/tracker");
   St_HitError *istTableSet = (St_HitError *) calibDataSet->Find("ist1HitError");
   HitError_st *istHitError = istTableSet->GetTable();
   mResXIst1 = sqrt(istHitError->coeff[0]);
   mResZIst1 = sqrt(istHitError->coeff[3]);

   TObjectSet *istDbDataSet = (TObjectSet *)GetDataSet("ist_db");

   if (istDbDataSet) {
      mIstDb = (StIstDb *)istDbDataSet->GetObject();
   }
   else {
      LOG_ERROR << "InitRun : no mIstDb" << endm;
      return kStErr;
   }

   // geometry Db tables
   mIstRot = mIstDb->getRotations();

   if (!mIstRot) {
      LOG_FATAL << "InitRun(): mIstRot is not initialized" << endm;
      return kStFatal;
   }
   // Lomnitz: Det effcicienct
   mDetUp = 0.95;
   mDetEff = 0.98;
   istStat thisrun;
   //if(mRandom.Rndm()>mDetUp) mSensorMap[i] = 0;
   for(int i=0;i<144;i++) {
     mSensorMap[i]=0;
     for(int j=0; j<6; j++){ //     mSensorMap[i] = 1;       
       if( thisrun.sensor[6*i+j] == 1) mSensorMap[i]+=1.0/6.;
     }
   }
   float istAcc =0;
   cout << " ==== IST Sensor Status Map ==== "<<endl;
   for(int i=0;i<144;i++) {
     cout << mSensorMap[i] << "\t";
     istAcc+=mSensorMap[i]/144.0;
     if( (i+1) % 6==0 )
       cout<<" "<<endl;    
   }
   cout << endl;
   cout<<"IST Acceptance: "<<istAcc<<endl;
   return kStOk;
}


/**
 * Retrieves GEANT hit information from StMcEvent then fills the StEvent's
 * StIstHitCollection with (possibly smeared) hit positions in either ideal or
 * misaligned geometry. Thus created StIstHitCollection is used in tracking.
 */
Int_t StIstFastSimMaker::Make()
{
   using namespace StIstConsts;

   if (mBuildIdealGeom && !gGeoManager) {

      GetDataBase("VmcGeometry");

      if (!gGeoManager) {
         LOG_ERROR << "Init() - "
            "Cannot initialize StIstFastSimMaker due to missing global object of TGeoManager class. "
            "Make sure STAR geometry is properly loaded with BFC AgML option" << endm;
         return kFatal;
      }
   }

   // Get the input data structures from StEvent and StMcEvent
   StEvent *rcEvent =  (StEvent *) GetInputDS("StEvent");

   if (! rcEvent) {LOG_WARN << "Make() - StEvent not found" << endl; return kStWarn;}

   StMcEvent *mcEvent = (StMcEvent *) GetInputDS("StMcEvent");

   if (! mcEvent) {LOG_WARN << "Make() - StMcEvent not found" << endl; return kStWarn;}

   // Store hits into Ist Hit Collection
   StIstHitCollection *istHitCollection = rcEvent->istHitCollection();

   if (!istHitCollection) {
      istHitCollection = new StIstHitCollection;
      rcEvent->setIstHitCollection(istHitCollection);
      LOG_WARN << "Make() - Added new StIstHitCollection to StEvent" << endm;
   }

   StThreeVectorF mHitError(0., 0., 0.);

   //Get MC Ist hit collection. This contains all ist hits.
   const StMcIstHitCollection *istMcHitCol = mcEvent->istHitCollection();

   if (!istMcHitCol) {
      LOG_FATAL << "No Ist MC hits found." << endm;
      return kStFatal;
   }

   //new simulator for new 1-layer design

   Int_t nIsthits = istMcHitCol->numberOfHits();

   if (istMcHitCol->layer(0)) {
      for (UInt_t kk = 0; kk < istMcHitCol->layer(0)->hits().size(); kk++) {
         StMcHit *mcH = istMcHitCol->layer(0)->hits()[kk];
         StMcIstHit *mcI = dynamic_cast<StMcIstHit *>(mcH);

         Int_t matIst = 1000 + (mcI->ladder() - 1) * kIstNumSensorsPerLadder + mcI->wafer();
         LOG_DEBUG << " matIst : " << matIst << endm;

         Int_t index = (mcI->ladder() - 1) * kIstNumSensorsPerLadder + (mcI->wafer() - 1);
         //if(!mSensorMap[index]) continue;  // sensor status determined in the whole run

         if(mRandom.Rndm()>mSensorMap[index]) continue;  //Sensor acceptance
	 if(mRandom.Rndm()>mDetEff) continue;   // detection efficiency, determined hit-by-hit
         TGeoHMatrix *combI = NULL;
         //Access VMC geometry once no IST geometry Db tables available or using ideal geoemtry is set
         if (mBuildIdealGeom) {
  	  TString path("HALL_1/CAVE_1/TpcRefSys_1/IDSM_1/IBMO_1");
  	  path += Form("/IBAM_%ld/IBLM_%ld/IBSS_1", mcI->ladder(), mcI->wafer());
  	  gGeoManager->RestoreMasterVolume();
  	  gGeoManager->CdTop();
  	  gGeoManager->cd(path);
  	  combI = (TGeoHMatrix *)gGeoManager->GetCurrentMatrix();
         }
         else { //using mis-aligned gemetry from IST geometry DB tables
  	  combI = (TGeoHMatrix *)mIstRot->FindObject(Form("R%04i", matIst));  
         }

         //YPWANG: McIstHit stored local position
         Double_t globalIstHitPos[3] = {mcI->position().x(), mcI->position().y(), mcI->position().z()};
         Double_t localIstHitPos[3] = {mcI->position().x(), mcI->position().y(), mcI->position().z()};

         if (mSmear) { // smearing on
            localIstHitPos[0] = distortHit(localIstHitPos[0], mResXIst1, kIstSensorActiveSizeRPhi / 2.0);
            localIstHitPos[2] = distortHit(localIstHitPos[2], mResZIst1, kIstSensorActiveSizeZ / 2.0);
         }
         else { //smearing off
            //discrete hit local position (2D structure of IST sensor pads)
            Float_t rPhiPos   = kIstSensorActiveSizeRPhi / 2.0 - localIstHitPos[0];
            Float_t zPos      = localIstHitPos[2] + kIstSensorActiveSizeZ / 2.0;
            Short_t meanColumn  = (Short_t)floor( zPos / kIstPadPitchColumn ) + 1;
            Short_t meanRow     = (Short_t)floor( rPhiPos / kIstPadPitchRow ) + 1;
            rPhiPos = (meanRow - 1) * kIstPadPitchRow + 0.5 * kIstPadPitchRow; //unit: cm
            zPos    = (meanColumn - 1) * kIstPadPitchColumn + 0.5 * kIstPadPitchColumn; //unit: cm
            localIstHitPos[0] = kIstSensorActiveSizeRPhi / 2.0 - rPhiPos;
            localIstHitPos[2] = zPos - kIstSensorActiveSizeZ / 2.0;
         }

         //YPWANG: do local-->global transform with geometry table
         combI->LocalToMaster(localIstHitPos, globalIstHitPos);
         StThreeVectorF gistpos(globalIstHitPos);

         UInt_t hw =  ( mcI->ladder() - 1 ) * kIstNumSensorsPerLadder + mcI->wafer();
         StIstHit *tempHit = new StIstHit(gistpos, mHitError, hw, mcI->dE(), 0);
         tempHit->setDetectorId(kIstId);
         tempHit->setId(mcI->key());
         mcI->parentTrack()? tempHit->setIdTruth(mcI->parentTrack()->key(), 100): tempHit->setIdTruth(-999);
         tempHit->setLocalPosition(localIstHitPos[0], localIstHitPos[1], localIstHitPos[2]);
         istHitCollection->addHit(tempHit);
      }//MC hits loop over
   }//end layer=0 cut

   LOG_DEBUG << "StIstFastSimMaker::Make() -I- Loaded " << nIsthits << " ist hits. \n";

   LOG_INFO << " Total number of McIstHitCollection = " << istMcHitCol->numberOfHits() << endm;
   LOG_INFO << " Total number of IstHitCollection = " << istHitCollection->numberOfHits() << endm;

   return kStOK;
}


/**
 * Calculates and returns new value for the local coordinate x by smearing it
 * acccording to a normal distribution N(mean, sigma) = N(x, res). The returned
 * value is constrained to be within the characteristic dimension detLength
 * provided by the user.
 */
Double_t StIstFastSimMaker::distortHit(const Double_t x, const Double_t res, const Double_t detLength)
{
   // Do not smear x when it is outside the physical limits. Issue a warning instead
   if (fabs(x) > detLength) {
      LOG_WARN << "distortHit() - Generated hit is outside detector sensor plane" << endm;
      return x;
   }

   Double_t smeared_x;

   do {
      smeared_x = mRandom.Gaus(x, res);
   } while ( fabs(smeared_x) > detLength);

   return smeared_x;
}
