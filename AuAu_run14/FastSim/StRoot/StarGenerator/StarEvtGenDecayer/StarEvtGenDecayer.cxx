#include <list>

#include "TParticle.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"

#include "EvtGenBase/EvtStdlibRandomEngine.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtAbsRadCorr.hh"
#include "EvtGenExternal/EvtExternalGenList.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtId.hh"
#include "EvtGenBase/EvtDecayBase.hh"
#include "EvtGenBase/EvtHepMCEvent.hh" 
#include "StMessMgr.h"
#include "StarEvtGenDecayer.h"
#include <iostream>

StarEvtGenDecayer::StarEvtGenDecayer(EvtGen* evtGen): mEvtGenRandomEngine(NULL), mEvtGen(evtGen), mParticle(NULL), mOwner(false)
{
  if(mEvtGen) return; // trust that mEvtGen is properly initialized by the user

  mOwner = true;

  mEvtGenRandomEngine = new EvtStdlibRandomEngine();
  EvtRandom::setRandomEngine((EvtRandomEngine*)mEvtGenRandomEngine);
  EvtExternalGenList genList;

  EvtAbsRadCorr* radCorrEngine = genList.getPhotosModel();
  std::list<EvtDecayBase*> extraModels = genList.getListOfModels();
  
  // the hardcoded paths are temporary
  mEvtGen = new EvtGen("../../DECAY_2010.DEC","../../evt.pdl", (EvtRandomEngine*)mEvtGenRandomEngine,radCorrEngine, &extraModels);

}

StarEvtGenDecayer::~StarEvtGenDecayer()
{
  if(mOwner)
  {
    delete mEvtGen;
    delete mEvtGenRandomEngine;
  }

  mParticle->deleteTree();
}

void StarEvtGenDecayer::Init()
{
   LOG_INFO << " Init Done" << endm;
}
void StarEvtGenDecayer::Decay(int pdgId, TLorentzVector*_p)
{
   EvtVector4R p_init(_p->E(), _p->Px(), _p->Py(), _p->Pz());
   r_init.set(0,0,0,0);// Reset the postion for mother particle,Default is(0,0,0,0) 

   EvtId parentID = EvtPDL::evtIdFromLundKC(pdgId);

   if(mParticle) mParticle->deleteTree(); // this deletes the daughter and mParticle itself (the object commits suicide)
   mParticle = EvtParticleFactory::particleFactory(parentID, p_init);
   mParticle->setDiagonalSpinDensity();
   mEvtGen->generateDecay(mParticle);
}

Int_t StarEvtGenDecayer::ImportParticles(TClonesArray* particles)
{
   if(!particles)
   {
     LOG_FATAL << "particles TClonesArray doesn't exist" <<endm;
     return -1;
   }
   
   TClonesArray &array = *particles;
   array.Clear();

   Int_t nparts = 0;
   for (size_t i = 0; i < mParticle->getNDaug(); i++)
   {
     // Need to check with Jason what units to return for the position. 
     // also the status and mothers codes
      new(array[nparts++]) TParticle(
         EvtPDL::getLundKC(mParticle->getDaug(i)->getId()), // PDG ID
         -999,
         -999,
         -999,
         -999,
         -999,
         mParticle->getDaug(i)->getP4Lab().get(1), // GeV/c
         mParticle->getDaug(i)->getP4Lab().get(2),
         mParticle->getDaug(i)->getP4Lab().get(3),
         mParticle->getDaug(i)->getP4Lab().get(0),
         r_init.get(1)+mParticle->getDaug(i)->get4Pos().get(1), // mm
         r_init.get(2)+mParticle->getDaug(i)->get4Pos().get(2),
         r_init.get(3)+mParticle->getDaug(i)->get4Pos().get(3),
         r_init.get(0)+mParticle->getDaug(i)->get4Pos().get(0));
   }

   return nparts;
}
void StarEvtGenDecayer::SetForceDecay(Int_t type)
{
   LOG_ERROR << "StarEvtGenDecayer::SetForceDecay method is not implemented in this class" <<endm;
}

void StarEvtGenDecayer::ForceDecay()
{
   LOG_ERROR << "StarEvtGenDecayer::ForceDecay method is not implemented in this class" <<endm;
}
Float_t StarEvtGenDecayer::GetPartialBranchingRatio(Int_t ipart)
{
   LOG_ERROR << "StarEvtGenDecayer::GetPartialBranchingRatio method is not implemented in this class" <<endm;
   return 1.0;
}
void StarEvtGenDecayer::ReadDecayTable()
{
   LOG_ERROR << "StarEvtGenDecayer::ReadDecayTable method is not implemented in this class" <<endm;
}
Float_t StarEvtGenDecayer::GetLifetime(Int_t pdg)
{
   LOG_ERROR << "StarEvtGenDecayer::GetLifetime method is not implemented in this class" <<endm;
   return 1.0;
}
