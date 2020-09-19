//==============================================================================
//  pmainjpsi.cpp
//
//  This is an example program to study J/psi production via the
//  J/psi -> e+ e- channel in 200 GeV pp collisions with Pythia8.
//  Feeddown from B decays is not considered here.
//
//  The decays are stored in a ROOT tree and written to file.
//
//  Once written most things can be controlled through the runcard,
//  so there's no need to recompile.
//
//  Usage: pmainjpsi  runcard  rootfile
//
//  Author: Thomas Ullrich
//  Last update: November 25, 2009
//==============================================================================
#include "Pythia.h"
#include "TTree.h"
#include "TFile.h"
#define PR(x) std::cout << #x << " = " << (x) << std::endl;
using namespace Pythia8;

//
//  Forward declarations
//
double costhetastar(int, int, const Event&);
bool isInAcceptance(int, const Event&);  // acceptance filter
int myEvent(Pythia&, double);            // event handler (analyze event and
// stores data in tuple)

//
// jpsiDecay_t structure contains all the info we
// collect. This info is later stored in a tree.
// This is our own business and has nothing to do
// with Pythia directly.
//
struct jpsiDecay_t {
  int orig_id;         // grandmother
  int orig_status;
  
  int jpsi_id;         // mother (J/psi)
  int jpsi_status;
  float jpsi_pt;
  float jpsi_pz;
  float jpsi_phi;
  float jpsi_eta;
  float jpsi_y;
  
  int e_id;            // electron
  int e_status;
  float e_pt;
  float e_pz;
  float e_phi;
  float e_eta;
  float e_y;
  
  int p_id;            // positron
  int p_status;
  float p_pt;
  float p_pz;
  float p_phi;
  float p_eta;
  float p_y;
  
  float openingAngle;  // hard process & decay specifics
  float mass;
  float costs;         // cos(theta*)
  int   q1_id;
  float q1_x;
  int   q2_id;
  float q2_x;
  float Q2fac;
  float alphas;
  float ptHat;
  int   nFinal;
  float pdf1;
  float pdf2;
  int   code;
  float sigmaGen;
  float weight;   // for obtaining x-section
  float sqrts;
};

jpsiDecay_t jpsiDecay;

int main(int argc, char* argv[]) {
  
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " runcard  rootfile" << endl;
    return 2;
  }
  char* runcard  = argv[1];
  char* rootfile = argv[2];
  const char* xmlDB    = "/gpfs01/star/pwg/dongx/zmiller/pdsfhome/zamiller/simu/myPythia/pythia8135/xmldoc";
  
  //--------------------------------------------------------------
  //  Initialization
  //--------------------------------------------------------------
  
  //
  //  ROOT
  //
  TFile *hfile  = new TFile(rootfile,"RECREATE");
  TTree tree("tree","J/psi decays pp at 200 GeV");
  tree.Branch("jpsiDecay",&jpsiDecay.orig_id,
              "orig_id/I:orig_status/I:"
              "jpsi_id/I:jpsi_status/I:jpsi_pt/F:jpsi_pz/F:jpsi_phi/F:jpsi_eta/F:jpsi_y/F:"
              "e_id/I:e_status/I:e_pt/F:e_pz/F:e_phi/F:e_eta/F:e_y/F:"
              "p_id/I:p_status/I:p_pt/F:p_pz/F:p_phi/F:p_eta/F:p_y/F:"
              "openingAngle/F:mass/F:costs/F:q1_id/I:q1_x/F:q2_id/I:q2_x/F:"
              "Q2fac/F:alphas/F:ptHat/F:nFinal/I:pdf1/F:pdf2/F:code/I:sigmaGen/F:weight/F:sqrts/F");
  
  //
  //  Create instance of Pythia
  //
  Pythia pythia(xmlDB); // the default parameters are read from xml files
  // stored in the xmldoc directory. This includes
  // particle data and decay definitions.
  
  //
  // Shorthand for (static) settings
  //
  Settings& settings = pythia.settings;
  
  //
  //  Read in runcard (should be star_hf_tune_v1.0.cmd)
  //
  pythia.readFile(runcard);
  cout << "Runcard '" << runcard << "' loaded." << endl;
  
  //
  //  Retrieve number of events and other parameters from the runcard.
  //  We need to deal with those settings ourself. Getting
  //  them through the runcard just avoids recompiling.
  //
  int  maxNumberOfEvents = settings.mode("Main:numberOfEvents");
  int  nList     = settings.mode("Main:numberToList");
  int  nShow     = settings.mode("Main:timesToShow");
  int  maxErrors = settings.mode("Main:timesAllowErrors");
  bool showCS    = settings.flag("Main:showChangedSettings");
  bool showAS    = settings.flag("Main:showAllSettings");
  int  pace = maxNumberOfEvents/nShow;
  
  //
  //  Decays: J/psi -> e+ e- only
  //  Here we make only the J/psi goes 100% into e+e-
  //  The psi' and the chi_c etc have the
  //  correct BR, i.e. the feeddown into J/psi is not skewed.
  //  This program is only to study J/psi.
  //
  pythia.readString("443:onMode = off");
  pythia.readString("443:onIfMatch = 11 -11");
  
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
  int numberOfJpsi = 0;
  int iErrors = 0;
  int n;
  
  while (ievent < maxNumberOfEvents) {
    
    if (!pythia.next()) {
      if (++iErrors < maxErrors) continue;
      cout << "Error: too many errors in event generation - check your settings & code" << endl;
      break;
    }
    n = myEvent(pythia, maxNumberOfEvents);  // in myEvent we deal with the whole event and return
    // the number of jpsi recorded for book keeping
    numberOfJpsi += n;
    //cout<<"jpsi numner per event: "<<n<<endl;
    if (n) tree.Fill();
    ievent++;
    if (ievent%pace == 0) {
      cout << "# of events generated = " << ievent
      << ", # of J/psi generated so far = " << numberOfJpsi << endl;
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
  pythia.statistics();
  cout << "Writing File" << endl;
  hfile->Write();
  
  return 0;
}

//
//  Event analysis
//
int myEvent(Pythia& pythia, double nMaxEvt)
{
  Event &event = pythia.event;
  
  int njpsi = 0;
  for (int i = 0; i < event.size(); i++) {
    if (event[i].id() == 443) {
      //
      //  Get daughters
      //
      vector<int> daughters = event.daughterList(i);
      
      if (daughters.size() != 2) continue;
      int ielectron = daughters[0];
      int ipositron = daughters[1];
      
      if (abs(event[ielectron].id()) != 11) continue;
      if (abs(event[ipositron].id()) != 11) continue;
      
      if (event[ielectron].id() == -11) {
        int k = ielectron;
        ielectron = ipositron;
        ipositron = k;
      }
      
      if (!(isInAcceptance(ielectron, event) && isInAcceptance(ipositron, event))) continue;
      
      njpsi++;
      int ijpsi = i;
      
      //
      // Get grandmother (origin of J/psi)
      //
      vector<int> mothers = event.motherList(ijpsi);
      int iorig = -1;
      switch(mothers.size()) {
        case 0:
          iorig = -1;
          break;
        case 1:
          iorig = mothers[0];
          break;
        default:
          iorig = -2;
          break;
      }
      
      //
      //  Store in tuple
      //
      
      // If no origin or more than 1 than id == 0
      // and the status identifies what happens: -1 no mother,
      // -2 more than 1. This should not happen at all, but ...
      jpsiDecay.orig_id     = iorig >= 0 ? event[iorig].id() : 0;
      jpsiDecay.orig_status = iorig >= 0 ? event[iorig].status() : iorig;
      
      int ic_id = abs(event[iorig].id());
      int flavor_mother = static_cast<int>(ic_id/pow(10.,static_cast<int>(log10(ic_id))));
      if(flavor_mother == 5) continue;
      cout<<"jpsi mother particle id :  "<<ic_id<<" and flavor is: "<<flavor_mother<<endl;
      
      vector<int> grandmothers = event.motherList(iorig);
      if(grandmothers.size()==1){
        
        int orig = grandmothers[0];
        int gorig_id = abs(event[orig].id());     //need absolute value here?
        int flavor_grandmon = static_cast<int>(gorig_id/pow(10.,static_cast<int>(log10(gorig_id))));
        cout<<"jpsi grandmother particle id :  "<<gorig_id<<" and flavor is: "<<flavor_grandmon<<endl;
        
        vector<int> ggrandmothers = event.motherList(orig);
        int origg = ggrandmothers[0];
        int ggorig_id = abs(event[origg].id());
        cout<<"jpsi ggrandmothers particle id :  "<< ggorig_id <<endl;
        
        vector<int> gggrandmothers = event.motherList(origg);
        int origgg = gggrandmothers[0];
        int gggorig_id = abs(event[origgg].id());
        cout<<"jpsi gggrandmothers particle id :  "<< gggorig_id <<endl;
        
        
        vector<int> ggggrandmothers = event.motherList(origgg);
        int origggg = ggggrandmothers[0];
        int ggggorig_id = abs(event[origggg].id());
        cout<<"jpsi ggggrandmothers particle id :  "<< ggggorig_id <<endl;
        
      }
        
      jpsiDecay.jpsi_id     = event[ijpsi].id();
      jpsiDecay.jpsi_status = event[ijpsi].status();
      jpsiDecay.jpsi_pt     = event[ijpsi].pT();
      jpsiDecay.jpsi_pz     = event[ijpsi].pz();
      jpsiDecay.jpsi_phi    = event[ijpsi].phi();
      jpsiDecay.jpsi_eta    = event[ijpsi].eta();
      jpsiDecay.jpsi_y      = event[ijpsi].y();
      
      jpsiDecay.e_id        = event[ielectron].id();
      jpsiDecay.e_status    = event[ielectron].status();
      jpsiDecay.e_pt       = event[ielectron].pT();
      jpsiDecay.e_pz       = event[ielectron].pz();
      jpsiDecay.e_phi       = event[ielectron].phi();
      jpsiDecay.e_eta       = event[ielectron].eta();
      jpsiDecay.e_y       = event[ielectron].y();
      
      jpsiDecay.p_id        = event[ipositron].id();
      jpsiDecay.p_status    = event[ipositron].status();
      jpsiDecay.p_pt        = event[ipositron].pT();
      jpsiDecay.p_pz        = event[ipositron].pz();
      jpsiDecay.p_phi       = event[ipositron].phi();
      jpsiDecay.p_eta       = event[ipositron].eta();
      jpsiDecay.p_y         = event[ipositron].y();
      
      jpsiDecay.openingAngle = costheta(event[ielectron].p(), event[ipositron].p());
      jpsiDecay.mass         = m(event[ielectron].p(), event[ipositron].p());
      jpsiDecay.costs        = costhetastar(ijpsi, ielectron, event);
      jpsiDecay.q1_id        = pythia.info.id1();
      jpsiDecay.q1_x         = pythia.info.x1();
      jpsiDecay.q2_id        = pythia.info.id2();
      jpsiDecay.q2_x         = pythia.info.x2();
      jpsiDecay.Q2fac        = pythia.info.Q2Fac();
      jpsiDecay.alphas       = pythia.info.alphaS();
      jpsiDecay.ptHat        = pythia.info.pTHat();
      jpsiDecay.nFinal       = pythia.info.nFinal();
      jpsiDecay.pdf1         = pythia.info.pdf1();
      jpsiDecay.pdf2         = pythia.info.pdf2();
      jpsiDecay.code         = pythia.info.code();
      jpsiDecay.sigmaGen     = pythia.info.sigmaGen();
      jpsiDecay.weight       = pythia.info.sigmaGen()/nMaxEvt; // useful for obtaining x-section
      jpsiDecay.sqrts        = pythia.info.eCM();
      //if(jpsiDecay.sigmaGen > 0.)cout<< jpsiDecay.sigmaGen<<endl;
    }
  }
  return njpsi;
}

//
//  Acceptance filter
//
bool isInAcceptance(int i, const Event& event)
{
  // accept all (useful for many studies)
  // return true;
  
  // limit to STAR TPC/BEMC/ToF acceptance
  double eta = event[i].eta();
  if (fabs(eta) < 1)
    return true;
  else
    return false;
}

//
// Cosine of angle of electron daughter in J/Psi rest frame
// i.e, cos(theta)* of decay
//
// Reference frame: recoil
//
// Returns in range [0,1]
//
// Polarization: dN/dcost* = 1+alpha*cost*^2
// alpha = +1 means tranverse (helicity = +-1)
//       = -1 means long. (helicity 0)
//       = 0  unpolarized

double costhetastar(int im, int ie, const Event& event)
{
  double gammaFrame = event[im].e()/event[im].m(); // gamma = E/m
  double gammabetaFrame = event[im].pAbs()/event[im].m();  // gamma*beta = p/m
  
  double costheta = (event[im].px()*event[ie].px()+
                     event[im].py()*event[ie].py()+
                     event[im].pz()*event[ie].pz())/(event[im].pAbs()*event[ie].pAbs());
  double pl = event[ie].pAbs()*costheta;    // wrt J/Psi axis
  double pt = sin(acos(costheta))*event[ie].pAbs();   // wrt J/Psi axis
  double pzstar = -gammabetaFrame*event[ie].e()+gammaFrame*pl;
  double tanThetaStar = pt/pzstar;
  double thetaStar = atan(tanThetaStar);
  return cos(thetaStar);
}
