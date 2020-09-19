//==============================================================================
//  pmainHF2e.cpp
//    
//  This is an example program to study c -> e and b -> e decays
//  in 200 GeV pp collisions with Pythia8.
//
//  The decays are stored in a ROOT tree and written to file.
//
//  Once written most things can be controlled through the runcard,
//  so there's no need to recompile.
//
//  Usage: pmainHF2e  runcard  rootfile
// 
//  Author: Thomas Ullrich  
//  Last update: September 9, 2008
//==============================================================================
#include <cmath>
#include "Pythia8/Pythia.h"
#include "TTree.h"
#include "TFile.h"
#include <string>
#include <fstream>
#include <TChain.h>
#include "TLeaf.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#define PR(x) std::cout << #x << " = " << (x) << std::endl;
using namespace Pythia8; 

//
//  Forward declarations
//
//int myEvent(Pythia&, double,int);            // event handler (analyze event and

// stores data in tuple)
//
// This structure contains all the info we 
// collect. This info is later stored in a tree.
// This is our own business and has nothing to do
// with Pythia directly.
//
struct hf2eDecay_t {
  int Event_id;
  int numberofcElectrons;
  int numberofbElectrons;
  int numberofbcElectrons;
  int numberofHadrons;
  int noTracks;
  
  //float b_pt[10];
  //float c_pt[10];
  
  int ce_id[3];            // c to electron
  int ce_status[3];
  float ce_pt[3];
  float ce_pz[3];
  float ce_phi[3];
  float ce_eta[3];
  float ce_y[3];
  int ceMom_id[3];
  
  int be_id[3];            // b  to electron
  int be_status[3];
  float be_pt[3];
  float be_pz[3];
  float be_phi[3];
  float be_eta[3];
  float be_y[3];
  int beMom_id[3];

  
  int bce_id[3];            // b to c to electron
  int bce_status[3];
  float bce_pt[3];
  float bce_pz[3];
  float bce_phi[3];
  float bce_eta[3];
  float bce_y[3];
  int bceMom_id[3];

  
  int hadron_id[800];            // hadron
  int hadron_status[800];
  float hadron_pt[800];
  float hadron_pz[800];
  float hadron_phi[800];
//  float hadron_eta[800];
  float hadron_y[800];
  
  float sigmaGen;
  float weight;   // useful for normalization/x-section
  
};

hf2eDecay_t hf2eDecay;

int main(int argc, char* argv[]) {
  
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " runcard  rootfile" << endl;
    return 2;
  }
  char* runcard  = argv[1];
  char* rootfile = argv[2];
  const char* xmlDB    = "/gpfs01/star/pwg/dongx/zmiller/pdsfhome/zamiller/simu/myPythia/pythia8240/xmldoc";
  
  //--------------------------------------------------------------
  //  Initialization
  //--------------------------------------------------------------
  
  //
  //  ROOT
  //
  TFile *hfile  = new TFile(rootfile,"RECREATE");
  TTree tree("tree","b->e c->e and b->c->e decays pp at 500 GeV");
//  tree.Branch("hf2eDecay",&hf2eDecay.Event_id,
//              "Event_id/I:numberofcElectrons/I:numberofbElectrons/I:numberofbcElectrons/I:numberofHadrons/I:noTracks/I:"//b_pt[10]/F:c_pt[10]/F:"
//              "ce_id[3]/I:ce_status[3]/I:ce_pt[3]/F:ce_pz[3]/F:ce_phi[3]/F:ce_eta[3]/F:ce_y[3]/F:ceMom_id[3]/I:"
//              "be_id[3]/I:be_status[3]/I:be_pt[3]/F:be_pz[3]/F:be_phi[3]/F:be_eta[3]/F:be_y[3]/F:beMom_id[3]/I:"
//              "bce_id[3]/I:bce_status[3]/I:bce_pt[3]/F:bce_pz[3]/F:bce_phi[3]/F:bce_eta[3]/F:bce_y[3]/F:bceMom_id[3]/I:"
//              "hadron_id[800]/I:hadron_status[800]/I:hadron_pt[800]/F:hadron_pz[800]/F:hadron_phi[800]/F:hadron_eta[800]/F:hadron_y[800]/F:sigmaGen/F:weight/F");
//  tree.Branch("hf2eDecay",&hf2eDecay.Event_id,
//   "Event_id/I:numberofcElectrons/I:numberofbElectrons/I:numberofbcElectrons/I:numberofHadrons/I:noTracks/I:"
//   "ce_id[3]/I:ce_status[3]/I:ce_pt[3]/F:ce_pz[3]/F:ce_phi[3]/F:ce_eta[3]/F:ceMom_id[3]/I:"
//   "be_id[3]/I:be_status[3]/I:be_pt[3]/F:be_pz[3]/F:be_phi[3]/F:be_eta[3]/F:beMom_id[3]/I:"
//   "bce_id[3]/I:bce_status[3]/I:bce_pt[3]/F:bce_pz[3]/F:bce_phi[3]/F:bce_eta[3]/F:bceMom_id[3]/I:"
//   "hadron_id[800]/I:hadron_status[800]/I:hadron_pt[800]/F:hadron_pz[800]/F:hadron_phi[800]/F:sigmaGen/F:weight/F");
  tree.Branch("hf2eDecay",&hf2eDecay.Event_id,
  "Event_id/I:numberofcElectrons/I:numberofbElectrons/I:numberofbcElectrons/I:numberofHadrons/I:noTracks/I:"
  "ce_id[3]/I:ce_status[3]/I:ce_pt[3]/F:ce_pz[3]/F:ce_phi[3]/F:ce_eta[3]/F:ce_y[3]/F:ceMom_id[3]/I:"
  "be_id[3]/I:be_status[3]/I:be_pt[3]/F:be_pz[3]/F:be_phi[3]/F:be_eta[3]/F:be_y[3]/F:beMom_id[3]/I:"
  "bce_id[3]/I:bce_status[3]/I:bce_pt[3]/F:bce_pz[3]/F:bce_phi[3]/F:bce_eta[3]/F:bce_y[3]/F:bceMom_id[3]/I:"
  "hadron_id[800]/I:hadron_status[800]/I:hadron_pt[800]/F:hadron_pz[800]/F:hadron_phi[800]/F:hadron_y[800]/F:sigmaGen/F:weight/F");
  
  //  Create instance of Pythia
  //
  Pythia pythia(xmlDB); // the init parameters are read from xml files
  Settings& settings = pythia.settings;
  
  //
  //  Read in runcard
  //
  pythia.readFile(runcard);
  cout << "Runcard '" << runcard << "' loaded." << endl;
  
  //
  //  Retrieve number of events and other parameters from the runcard.
  //  We need to deal with those settings ourself. Getting
  //  them through the runcard just avoids recompiling.
  //
  
  int  maxNumberOfEvents = settings.mode("Main:numberOfEvents");
  //int  nList     = settings.mode("Main:numberToList");
  int nList = 0;
  bool showCS = true;
  //int  nShow     = settings.mode("Main:timesToShow");
  int  maxErrors = settings.mode("Main:timesAllowErrors");
  //bool showCS    = settings.flag("Main:showChangedSettings");
  //bool showAS    = settings.flag("Main:showAllSettings");
  bool showAS =  true;
  
  
  //
  //  Remark: in this example we do NOT alter the
  //  BRs since they are different for the various charm
  //  hadrons making the normalization at the end rather
  //  cumbersome. In a production version this is what
  //  one probably would implement to save processing time.
  //
  
  //
  //  Initialize Pythia, ready to go
  //
  pythia.init();
  
  //
  // List changed or all data
  //
  if (showCS) settings.listChanged();
  if (showAS) settings.listAll();
  
  //--------------------------------------------------------------
  //  Event loop
  //--------------------------------------------------------------
  int ievent = 0;
  int numberOfElectrons = 0;
  int iErrors = 0;
  while (ievent < maxNumberOfEvents) {
    
    if (!pythia.next()) {
      if (++iErrors < maxErrors) continue;
      cout << "Error: too many errors in event generation - check your settings & code" << endl;
      break;
    }
    
    Event &event = pythia.event;
    int eventId=ievent+maxNumberOfEvents;
    hf2eDecay.Event_id   = eventId;
    int ic =0;
    int e_number=0;
    int nce=0,nbe=0,nbce=0;
    int nc=0, nb=0;
    int hadron_number=0;
    int nh=0;
    //-------------------------------------------------------------------------------------------------
    for (int i = 0; i < event.size(); i++) {   //event.size means total track number
      if(event[i].isHadron()&&event[i].isFinal()&&event[i].isCharged())    //select hadron
      {
        hf2eDecay.hadron_id[nh] = event[i].id();
        hf2eDecay.hadron_status[nh] = event[i].status();
        hf2eDecay.hadron_pt[nh] = event[i].pT();
        hf2eDecay.hadron_pz[nh] = event[i].pz();
        hf2eDecay.hadron_phi[nh] = event[i].phi();
//        hf2eDecay.hadron_eta[nh] = event[i].eta();
        hf2eDecay.hadron_y[nh] = event[i].y();
        nh++;
      }
      
      //if(event[i].id() == 5) {
      //  hf2eDecay.b_pt[nb] = event[i].pT();
      //  nb++;
      //}
      //if(event[i].id() == 4) {
      //  hf2eDecay.c_pt[nc] = event[i].pT();
      //  nc++;
      //}
      
      if (abs(event[i].id()) == 11) {
        
        //
        //  Check if mother is a c/b hadron
        //
        vector<int> mothers = event[i].motherList();
        if (mothers.size() != 1) {
          cout << "Error: electron has more than one mother. Stop." << endl;
          continue;
        }
        ic = mothers[0];
        int ic_id = abs(event[ic].id());
        int flavor = static_cast<int>(ic_id/pow(10.,static_cast<int>(log10(ic_id)))); //this will miss excited states like D0*
        if (flavor != 4 && flavor != 5) continue; // c (b) hadrons start with 4(5)
        if(flavor == 4)
        {
          vector<int> grandmothers = event[ic].motherList();
          if(grandmothers.size()==1)
          {
            int orig = grandmothers[0];
            int orig_id = abs(event[orig].id());     //need absolute value here?
            int flavor_grandmon = static_cast<int>(orig_id/pow(10.,static_cast<int>(log10(orig_id)))); //this will miss excited states like D0*
            
            if(flavor_grandmon == 5)
            {
              hf2eDecay.bce_id[nbce] = event[i].id();
              hf2eDecay.bce_status[nbce] = event[i].status();
              hf2eDecay.bce_pt[nbce] = event[i].pT();
              hf2eDecay.bce_pz[nbce] = event[i].pz();
              hf2eDecay.bce_phi[nbce] = event[i].phi();
              hf2eDecay.bce_eta[nbce] = event[i].eta();
              hf2eDecay.bce_y[nbce] = event[i].y();
              hf2eDecay.bceMom_id[nbce] = ic_id;
              nbce++;
            }
            else
            {
              hf2eDecay.ce_id[nce] = event[i].id();
              hf2eDecay.ce_status[nce] = event[i].status();
              hf2eDecay.ce_pt[nce] = event[i].pT();
              hf2eDecay.ce_pz[nce] = event[i].pz();
              hf2eDecay.ce_phi[nce] = event[i].phi();
              hf2eDecay.ce_eta[nce] = event[i].eta();
              hf2eDecay.ce_y[nce] = event[i].y();
              hf2eDecay.ceMom_id[nce] = ic_id;
              nce++;
            }
          }
        }
        if(flavor == 5)
        {
          hf2eDecay.be_id[nbe] = event[i].id();
          hf2eDecay.be_status[nbe] = event[i].status();
          hf2eDecay.be_pt[nbe] = event[i].pT();
          hf2eDecay.be_pz[nbe] = event[i].pz();
          hf2eDecay.be_phi[nbe] = event[i].phi();
          hf2eDecay.be_eta[nbe] = event[i].eta();
          hf2eDecay.be_y[nbe] = event[i].y();
          hf2eDecay.beMom_id[nbe] = ic_id;
          nbe++;
        }
      }
      
    }              //end of this track loop
    
    e_number=nbe+nce+nbce;
    hadron_number=nh;
    hf2eDecay.numberofcElectrons =nce;
    hf2eDecay.numberofbElectrons =nbe;
    hf2eDecay.numberofbcElectrons =nbce;
    hf2eDecay.numberofHadrons = hadron_number;
    hf2eDecay.noTracks = e_number+hadron_number;    //event.size();
    
    hf2eDecay.sigmaGen = pythia.info.sigmaGen();
    hf2eDecay.weight = pythia.info.sigmaGen()/(double )maxNumberOfEvents;
    if(e_number > 0) tree.Fill();
    
    for(int i=0;i<nh;i++)
    {
      hf2eDecay.hadron_id[i] = 0;
      hf2eDecay.hadron_status[i] = 0;
      hf2eDecay.hadron_pt[i] = 0.;
      hf2eDecay.hadron_pz[i] = 0.;
      hf2eDecay.hadron_phi[i] = 0.;
//      hf2eDecay.hadron_eta[i] = 0.;
      hf2eDecay.hadron_y[i] = 0.;
    }
    for(int i=0;i<nce;i++)
    {
      hf2eDecay.ce_id[i] = 0;
      hf2eDecay.ce_status[i] = 0;
      hf2eDecay.ce_pt[i] = 0.;
      hf2eDecay.ce_pz[i] = 0.;
      hf2eDecay.ce_phi[i] = 0.;
      hf2eDecay.ce_eta[i] = 0.;
      hf2eDecay.ce_y[i] = 0.;
      hf2eDecay.ceMom_id[i] = 0;
    }
    for(int i=0;i<nbe;i++)
    {
      hf2eDecay.be_id[i] = 0;
      hf2eDecay.be_status[i] = 0;
      hf2eDecay.be_pt[i] = 0.;
      hf2eDecay.be_pz[i] = 0.;
      hf2eDecay.be_phi[i] = 0.;
      hf2eDecay.be_eta[i] = 0.;
      hf2eDecay.be_y[i] = 0.;
      hf2eDecay.beMom_id[i] = 0;
    }
    for(int i=0;i<nbce;i++)
    {
      hf2eDecay.bce_id[i] = 0;
      hf2eDecay.bce_status[i] = 0;
      hf2eDecay.bce_pt[i] = 0.;
      hf2eDecay.bce_pz[i] = 0.;
      hf2eDecay.bce_phi[i] = 0.;
      hf2eDecay.bce_eta[i] = 0.;
      hf2eDecay.bce_y[i] = 0.;
      hf2eDecay.bceMom_id[i] = 0;
    }
    //for(int i=0;i<nb;i++)
    //{
    //  hf2eDecay.b_pt[i] = 0;
    //}
    //
    //for(int i=0;i<nc;i++)
    //{
    //  hf2eDecay.c_pt[i] = 0;
    //}
    
    ievent++;
    numberOfElectrons = numberOfElectrons+e_number;
    if (ievent%1000 == 0) {
      cout << "# of events generated = " << ievent
      << ", # of electrons from c or b hadron decays generated so far = " <<  numberOfElectrons << endl;
    }
    
    // List first few events.
    if (ievent < nList) {
      pythia.info.list();
      pythia.process.list();
      pythia.event.list();
    }
  }
  
  //--------------------------------------------------------------
  //  Finish up
  //--------------------------------------------------------------
  //pythia.statistics();
  cout << "Writing File" << endl;
  hfile->Write();
  return 0;
} 
