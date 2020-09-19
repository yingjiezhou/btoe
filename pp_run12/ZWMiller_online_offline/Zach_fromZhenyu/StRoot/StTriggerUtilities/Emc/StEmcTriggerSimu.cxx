//
// Pibero Djawotho <pibero@comp.tamu.edu>
// Texas A&M University Cyclotron Institute
// 12 Jan 2009
//

// STAR
#include "StMaker.h"

// Local
#include "StTriggerUtilities/Bemc/StBemcTriggerSimu.h"
#include "StTriggerUtilities/Eemc/StEemcTriggerSimu.h"
#include "StTriggerUtilities/StDSMUtilities/StDSM2009Utilities.hh"
#include "StEmcTriggerSimu.h"

ClassImp(StEmcTriggerSimu);

StEmcTriggerSimu::StEmcTriggerSimu()
  : mBemc(0)
  , mEemc(0)
  , mEM201(new DSMLayer_EM201_2009)
  , mLD301(new DSMLayer_LD301_2009)
  , mTcu(new TCU)
{
}

StEmcTriggerSimu::~StEmcTriggerSimu()
{
  delete mEM201; mEM201 = 0;
  delete mLD301; mLD301 = 0;
  delete mTcu; mTcu = 0;
}

void StEmcTriggerSimu::setBemc(StBemcTriggerSimu* bemc)
{
  mBemc = bemc;
}

void StEmcTriggerSimu::setEemc(StEemcTriggerSimu* eemc)
{
  mEemc = eemc;
}

void StEmcTriggerSimu::InitRun(int runNumber)
{
  // Get DB timestamp
  StMaker* chain = StMaker::GetChain();
  assert(chain);
  mDBTime = chain->GetDBTime();
  mYear = mDBTime.GetYear();
}

void StEmcTriggerSimu::Make()
{
  if (mYear >= 2009) {
    if (mBemc) mBemc->get2009_DSMLayer1_Result()->write(*mEM201);
    if (mEemc) mEemc->get2009_DSMLayer1_Result()->write(*mEM201);

    TString EM201String = "EM201: ";
    for (int ch = 0; ch < 8; ++ch) EM201String += Form("%04x ",(*mEM201)[0].channels[ch]);
    LOG_DEBUG << EM201String << endm;

    mEM201->run();


    LOG_INFO << Form("EM201: BHT0=%d BHT1=%d BHT2=%d BHT3=%d EHT0=%d EHT1=%d JP1=%d JP2=%d BJP1=%d BJP2=%d EJP1=%d EJP2=%d AJP=%d BAJP=%d EAJP=%d JP0=%d",
		     BHT0(),BHT1(),BHT2(),BHT3(),EHT0(),EHT1(),JP1(),JP2(),BJP1(),BJP2(),EJP1(),EJP2(),AJP(),BAJP(),EAJP(),JP0()) << endm;

    //for year 2009 set EM201 to LD301 then to TCU
    if(mYear == 2009)
      {
	mEM201->write(*mLD301);

	TString LD301String = "LD301: ";

	for (int ch = 0; ch < 8; ++ch) LD301String += Form("%04x ",(*mLD301)[0].channels[ch]);
	LOG_DEBUG << LD301String << endm; //changed this line LOG_INFO

	mLD301->run();

        mTcu->setInput((*mLD301)[0].output); //Run9 TCU setup
      }else if(mYear > 2010)
      {
	mTcu->setInput((*mEM201)[0].output); //Run11 and Run12 TCU EM201 part -- zchang
      }
    LOG_INFO << Form("TCU: %04x",mTcu->input() & 0xffff) << endm; //changed this line to LOG_INFO -- zchang
  }
}

bool StEmcTriggerSimu::isTrigger(int trigId)
{
  return mTcu->isTrigger(trigId);
}

set<int> StEmcTriggerSimu::triggerIds() const
{
  return mTcu->triggerIds();
}

StTriggerSimuDecision StEmcTriggerSimu::triggerDecision(int trigId)
{
  return isTrigger(trigId) ? kYes : kNo;
}
void StEmcTriggerSimu::defineTrigger(TriggerDefinition& trigdef)
{
  mTcu->defineTrigger(trigdef);
}

void StEmcTriggerSimu::defineTrigger(TriggerDefinition& trigdef,int year)
{
   //Run11 and Run12 move EM201 output(onbit1 higher 16 bits) to onbits -- zchang
  if(year > 2010)
    {
      trigdef.onbits = trigdef.onbits1;
      trigdef.onbits = trigdef.onbits >> 16;
    }
  mTcu->defineTrigger(trigdef);
}

void StEmcTriggerSimu::defineTrigger(int triggerIndex, const char* name, int triggerId, unsigned int onbits, unsigned int offbits, unsigned int onbits1, unsigned int onbits2, unsigned int onbits3, unsigned int offbits1, unsigned int offbits2, unsigned int offbits3)
{
  TriggerDefinition triggerDefinition;
  triggerDefinition.triggerIndex = triggerIndex;
  strcpy(triggerDefinition.name,name);
  triggerDefinition.triggerId = triggerId;
  triggerDefinition.onbits = onbits;
  triggerDefinition.offbits = offbits;
  triggerDefinition.onbits0 = onbits;
  triggerDefinition.offbits0 = offbits;
  triggerDefinition.onbits1 = onbits1;
  triggerDefinition.onbits2 = onbits2;
  triggerDefinition.onbits3 = onbits3;
  triggerDefinition.offbits1 = offbits1;
  triggerDefinition.offbits2 = offbits2;
  triggerDefinition.offbits3 = offbits3;
  defineTrigger(triggerDefinition);
}
//Add Functions defineTrigger2012 test for 2011 and 2012 -- zchang
void StEmcTriggerSimu::defineTrigger2012(int triggerIndex, const char* name, int triggerId, unsigned int onbits)
{
  TriggerDefinition triggerDefinition;
  triggerDefinition.triggerIndex = triggerIndex;
  strcpy(triggerDefinition.name,name);
  triggerDefinition.triggerId = triggerId;
  triggerDefinition.onbits = onbits;
  triggerDefinition.offbits = 0;
  triggerDefinition.onbits0 = 0;
  triggerDefinition.onbits1 = 0;
  triggerDefinition.onbits2 = 0;
  triggerDefinition.onbits3 = 0;
  triggerDefinition.offbits0 = 0;
  triggerDefinition.offbits1 = 0;
  triggerDefinition.offbits2 = 0;
  triggerDefinition.offbits3 = 0;
  //Print out new triggerDefinition -- zchang
  LOG_INFO <<"New Defined Trigger: "
           << Form("triggerIndex=%d name=%s triggerId=%d onbits=0x%04x\n",triggerDefinition.triggerIndex,triggerDefinition.name,triggerDefinition.triggerId,triggerDefinition.onbits) << endm;

  defineTrigger(triggerDefinition);
}

int StEmcTriggerSimu::EM201output() const { return (*mEM201)[0].output; }

int StEmcTriggerSimu::overlapJetPatchTh(int i) const { return mEM201->getRegister(i); }

void StEmcTriggerSimu::getOverlapJetPatchAdc(int i, int& jp, int& adc) const
{
  int jp_partial = (*mEM201)[0].channels[6+i] >> 12 & 0x3;
  jp  = (1-i)*3+jp_partial-1;
  adc = (*mEM201)[0].info[i];
}
