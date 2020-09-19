/*!
 * \class  StPxlMonMaker
 * \author Shusu Shi, LBNL
 * \date   May 2013
 * \Initial Revision.
 */
/***************************************************************************
 *
 * $Id: StPxlMonMaker.cxx,v 1.29 2014/02/25 04:20:14 sss Exp $
 *
 * Author: Shusu Shi, May 2013
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StPxlMonMaker.cxx,v $
 * Revision 1.29  2014/02/25 04:20:14  sss
 * *** empty log message ***
 *
 * Revision 1.28  2014/02/25 01:09:28  smirnovd
 * Fixed missing brackets
 *
 * Revision 1.27  2014/02/25 01:09:19  smirnovd
 * Remove unused code accessing cluster collection
 *
 * Revision 1.26  2014/02/25 01:09:12  smirnovd
 * Fill derivative histograms when the maker finishes
 *
 * Revision 1.25  2014/02/25 01:09:06  smirnovd
 * Minor fixes not affecting functionality
 *
 * Revision 1.24  2014/02/25 01:08:39  smirnovd
 * Reduced number of bins in event distribution histograms
 *
 * Revision 1.23  2014/02/07 00:15:00  smirnovd
 * Small stylistic improvement + doxygen comments
 *
 * Revision 1.22  2014/02/07 00:14:52  smirnovd
 * Organized output in subdirectories. The change intoduced by Shusu
 *
 * Revision 1.21  2014/02/07 00:14:43  smirnovd
 * Removed temporary constraint on processing only three pixel sectors
 *
 * Revision 1.20  2014/02/07 00:14:32  smirnovd
 * Change histogram type to conserve memory
 *
 * Revision 1.19  2014/02/01 19:03:36  smirnovd
 * Common index for composite sensor id
 *
 * Revision 1.18  2014/02/01 19:03:16  smirnovd
 * Fixed default parameter bug
 *
 * Revision 1.17  2014/02/01 02:37:18  smirnovd
 * This commit is intended to sync with what we had in StRoot/StiRnD
 *
 * Revision 1.9  2014/01/28 19:29:42  qiuh
 * *** empty log message ***
 *
 *
 **************************************************************************/

#include <iostream>
#include <fstream>
#include "StPxlMonMaker.h"
#include "StEventTypes.h"
#include "StMessMgr.h"
#if ROOT_VERSION_CODE < 334081
#include "TArrayL.h"
#else
#include "TArrayL64.h"
#endif
#include "StThreeVectorF.hh"
#include "StDetectorName.h"
#include "StEvent/StPxlHit.h"
#include "StEvent/StPxlHitCollection.h"
#include "StPxlClusterMaker/StPxlCluster.h"
#include "StPxlClusterMaker/StPxlClusterCollection.h"
#include "StPxlRawHitMaker/StPxlRawHit.h"
#include "StPxlRawHitMaker/StPxlRawHitCollection.h"
#include "StIOMaker/StIOMaker.h"

ClassImp(StPxlMonMaker);


StPxlMonMaker::StPxlMonMaker(uint16_t numPixelsPerBin, const Char_t *name) : StMaker(name),
	mNumPixelsPerBin(numPixelsPerBin), mEventCounter(0), mNtupleWrite(0)
{}


Int_t StPxlMonMaker::Init()
{
	LOG_INFO << "StPxlMonMaker::Init()" << endm;

	mEventCounter = 0;
	mNtupleWrite = 0;
	bookHists();
	return kStOk;
}


void StPxlMonMaker::bookHists()
{
	tree = new TTree("T","Raw Hits Tree");
	tree->Branch("nRawhits",&nRawhits,"nRawhits/I");
        tree->Branch("iSensor",&iSensor,"iSensor/I");
        tree->Branch("zdc",&zdc,"zdc/F");
        tree->Branch("eventSize",&eventSize,"eventSize/I");
	tree->Branch("sensorId",&sensorId,"sensorId[nRawhits]/I");
        tree->Branch("iColumn",&iColumn,"iColumn[nRawhits]/I");
        tree->Branch("iRow",&iRow,"iRow[nRawhits]/I");
	tree->Branch("nRawhitsBySensorId",&nRawhitsBySensorId,"nRawhitsBySensorId[iSensor]/I");
	hHitbySensor =  new TH2F("hHitbySensor","hHitbySensor",400,0,400,1000,0,1000);
}


Int_t StPxlMonMaker::Finish()
{
	LOG_INFO << "StPxlMonMaker::Finish()" << endm;
	writeHists();
	gMessMgr->Info() << "StPxlMonMaker::Finish() "
		<< "Processed " << mEventCounter << " events." << endm;
	return kStOK;
}


Int_t StPxlMonMaker::Make()
{
	mEventCounter++;

	StEvent *event;
	event = (StEvent *) GetInputDS("StEvent");
	if (!event) {
		gMessMgr->Warning() << "StPxlMonMaker::Make : No StEvent" << endm;
		//return kStOK;        // if no event, we're done
	}
/*
	if (event->id() == 0 ||
event->id() == 710 ||
event->id() == 1306 ||
event->id() == 12728 ||
event->id() == 17424 ||
event->id() == 21613 ||
event->id() == 25828 ||
event->id() == 31677 ||
event->id() == 34304 ||
event->id() == 37385 ||
event->id() == 40736 ||
event->id() == 43804 ||
event->id() == 45588 ||
event->id() == 52290 ||
event->id() == 59331 ||
event->id() == 59360 ||
event->id() == 60106 ||
event->id() == 66502 ||
event->id() == 68015 ||
event->id() == 71960 ||
event->id() == 72758 ||
event->id() == 74119 ||
event->id() == 79192 ||
event->id() == 84400 ||
event->id() == 85495 ||
event->id() == 91499 ||
event->id() == 103862 ||
event->id() == 109530 ||
event->id() == 110009 ||
event->id() == 112255 ||
event->id() == 118444 ||
event->id() == 122432 ||
event->id() == 127339 ||
event->id() == 135083 ||
event->id() == 138573 ||
event->id() == 139091 ||
event->id() == 150271 ||
event->id() == 149635 ||
event->id() == 152077 ||
event->id() == 162015 ||
event->id() == 163330 ||
event->id() == 164264 ||
event->id() == 168173 ||
event->id() == 173695 ||
event->id() == 174102 ||
event->id() == 174829 ||
event->id() == 176344 ||
event->id() == 179973 ||
event->id() == 180913 ||
event->id() == 185179 ||
event->id() == 186707 ||
event->id() == 188082 ||
event->id() == 190998 ||
event->id() == 193986 ||
event->id() == 198422 ||
event->id() == 199875 ||
event->id() == 203388 ||
event->id() == 204357 ||
event->id() == 208496 ||
event->id() == 211835 ||
event->id() == 227214 ||
event->id() == 234125 ||
event->id() == 235989 ||
event->id() == 240139 ||
event->id() == 241098 ||
event->id() == 243751 ||
event->id() == 254190 ||
event->id() == 257194 ||
event->id() == 260445 ||
event->id() == 262696 ||
event->id() == 263171 ||
event->id() == 268416 ||
event->id() == 268908 ||
event->id() == 278467 ||
event->id() == 281096 ||
event->id() == 281706 ||
event->id() == 281899 ||
event->id() == 291001 ||
event->id() == 294672 ||
event->id() == 299732 ||
event->id() == 304190 ||
event->id() == 318858 ||
event->id() == 321534 ||
event->id() == 100 ||
event->id() == 323960 ||
event->id() == 328942 ||
event->id() == 334270 ||
event->id() == 333922 ||
event->id() == 341689 ||
event->id() == 343902 ||
event->id() == 344400 ||
event->id() == 346966 ||
event->id() == 349140 ||
event->id() == 349645 ||
event->id() == 357936 ||
event->id() == 360375 ||
event->id() == 368890 ||
event->id() == 371855 ||
event->id() == 372068 ||
event->id() == 379800 ||
event->id() == 381424 ||
event->id() == 387274 ||
event->id() == 390028 ||
event->id() == 390469 ||
event->id() == 391714 ||
event->id() == 396252 ||
event->id() == 401610 ||
event->id() == 406119 ||
event->id() == 407598 ||
event->id() == 411471) cout << " " << endl;
*/
        zdc=event->runInfo()->zdcCoincidenceRate();
	eventSize=event->info()->eventSize();

	StPxlHitCollection *pxlHitCollection = (StPxlHitCollection *)event->pxlHitCollection();
	if (!pxlHitCollection) {
		LOG_WARN << "StPxlMonMaker::Make() no pxlHitCollection." << endm;
		return kStWarn;
	}
	int rawhit_in_a_event = 0;
        rawhit_in_a_event += pxlHitCollection->numberOfHits();
        if(rawhit_in_a_event<1)  return kStOk;
	nRawhits = 0;
	for (int i=0;i<500;i++) nRawhitsBySensorId[i]=0;
	for (int i = 0; i < kNumberOfPxlSectors; i++)
	{
		StPxlSectorHitCollection * sector = pxlHitCollection->sector(i);

		for (int j = 0; j < kNumberOfPxlLaddersPerSector; j++)
		{
			StPxlLadderHitCollection * ladder = sector->ladder(j);
			for (int k = 0; k < kNumberOfPxlSensorsPerLadder; k++)
			{
				StPxlSensorHitCollection * sensor = ladder->sensor(k);
				StSPtrVecPxlHit hits = sensor->hits();
				hHitbySensor->Fill(i * 40 + j * 10 + k, hits.size());
			}
		}

	}
	//tree->Fill();
	return kStOK;
}


void StPxlMonMaker::writeHists()
{
	StIOMaker *ioMaker = (StIOMaker*) GetMaker("inputStream");
	if (!ioMaker) {
		gMessMgr->Warning() << "StPxlMonMaker::writeHists(): No StIOMaker found" << endm;
	}

	TString filename = TString(ioMaker->GetFile());
	int slash_index = filename.Last('/');

	if(slash_index >= 0){
		filename.Replace(0, slash_index+1/*-8*/, "");
	}

	slash_index = filename.First(".");
	if (slash_index == 0) slash_index = filename.Length();

	filename.Replace(slash_index, filename.Length() - slash_index, ".pxlMon.root");
	LOG_INFO << "StPxlMonMaker::writeHists(): filename: " << filename << endm;

	m_f1 = new TFile(filename.Data(), "RECREATE");
	//tree->Write();
	hHitbySensor->Write();
	m_f1->Close();
}
