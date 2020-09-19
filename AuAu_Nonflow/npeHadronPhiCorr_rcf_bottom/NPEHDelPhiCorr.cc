//==============================================================================
//  pmainHF2e.cpp
//
//  This is an example program to study c -> e and b -> e decays
//  in 200 GeV pp collisions with Pythia8.
//
//  Creates templated for deltaPhi in b or c, depending on input cards.
//
//  Usage: pmainHF2e  runcard  rootfile
//
//  Author: Thomas Ullrich
//  Last update: September 9, 2008
//  Modified: Z.W. Miller Aug 17, 2015
//==============================================================================
#include <ctime>
#include <cmath>
#include <vector>
#include "Pythia8/Pythia.h"
//#include "Pythia.h"
#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"
#include "TH3D.h"
#define PR(x) std::cout << #x << " = " << (x) << std::endl;
using namespace std;
using namespace Pythia8;

//
//  Forward declarations
//
bool isInAcceptanceE(int, const Event&);  // acceptance filter electron candidate
bool isInAcceptanceH(int, const Event&);  // acceptance filter hadron candidate
int myEvent(Pythia&, vector<TH2D*> &, vector<TH3D*>&, double); // event handler (analyze event)
double deltaPhi(double, double);
double deltaEta(double, double);

int randomSeed = 0;
float min_pTHat = 16.0;
float max_pTHat = 32.0;

const Int_t kNumOfElectrons = 10;

int main(int argc, char* argv[]) {
  
  if (argc != 7) {
    cout << "Usage: " << argv[0] << " randomSeed min_pTHat max_pTHat runcard rootfile histName" << endl;
    return 2;
  }
  randomSeed = atoi ( argv[1] );
  min_pTHat = atoi ( argv[2] );
  max_pTHat = atoi ( argv[3] );
  char* runcard  = argv[4];
  char* rootfile = argv[5];
  char* histname = argv[6];
  //const char* xmlDB    = "/DATA/data01/wyp/software/pythia8186/xmldoc";
  const char* xmlDB    = "/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/pythia8/186/xmldoc";
  
  //--------------------------------------------------------------
  //  Initialization
  //--------------------------------------------------------------
  
  time_t now = time(0);
  cout << "============================================================================" \
  << endl;
  cout << "Executing program '" << argv[0] << "', start at: " << ctime(&now);
  cout << "Arguments: " << randomSeed << " " << min_pTHat << " " << max_pTHat << " " << runcard << " " << rootfile << " " << histname << endl;
  cout << "============================================================================" \
  << endl;
  
  //
  //  ROOT
  //
  char text[64];
  
  TString outputFileName = Form(rootfile);
  outputFileName+="_r";
  outputFileName+=randomSeed;
  outputFileName+="pT";
  outputFileName+=(int)min_pTHat;
  outputFileName+="_";
  outputFileName+=(int)max_pTHat;
  outputFileName+=".root";
  cout << rootfile << " " << outputFileName << endl;
  
  TFile *hfile  = new TFile(outputFileName,"RECREATE");
  
  TH1F *hStatistics=new TH1F("hStatistics","Production Statistics",2,0,10);
  TH1F *hPTHat = new TH1F("hPTHat", "pTHat Distribution", 200, 0, 100.);
  
  // zyj
  TTree *hfProdTree = new TTree("hfProdTree", "E and hadron tree");
  Int_t nElec;
  Double_t pTTrkE[kNumOfElectrons];
  Double_t etaE[kNumOfElectrons];
  Double_t phiE[kNumOfElectrons];
  Double_t idE[kNumOfElectrons];
    
  std::vector<Pythia8::Particle> Hadrons;
  hfProdTree->Branch("nElec", &nElec, "nElec/I");
  hfProdTree->Branch("pTTrkE", pTTrkE, "pTTrkE[nElec]/D");
  hfProdTree->Branch("etaE", etaE, "etaE[nElec]/D");
  hfProdTree->Branch("phiE", phiE, "phiE[nElec]/D");
  hfProdTree->Branch("idE", idE, "idE[nElec]/D");
  
  hfProdTree->Branch("Hadrons","std::vector<Pythia8::Particle>",&Hadrons);

  //
  //  Create instance of Pythia
  //
  Pythia pythia(xmlDB); // the init parameters are read from xml files
  // stored in the xmldoc directory. This includes
  // particle data and decay definitions.
  
  //
  // Shorthand for (static) settings
  //
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
  int  nList     = settings.mode("Main:numberToList");
  int  nShow     = settings.mode("Main:timesToShow");
  int  maxErrors = settings.mode("Main:timesAllowErrors");
  bool showCS    = settings.flag("Main:showChangedSettings");
  bool showAS    = settings.flag("Main:showAllSettings");
  int  pace = maxNumberOfEvents/nShow;
  
  // random seed setting
  pythia.readString("Random:setSeed = on");
  TString randomSeedSetting="Random:Seed = ";
  randomSeedSetting+=randomSeed;
  pythia.readString(randomSeedSetting.Data());
  
  // pTHat setting
  TString minpTHatSetting="PhaseSpace:pTHatMin = ";
  minpTHatSetting+=min_pTHat;
  pythia.readString(minpTHatSetting.Data());
  
  TString maxpTHatSetting="PhaseSpace:pTHatMax = ";
  maxpTHatSetting+=max_pTHat;
  pythia.readString(maxpTHatSetting.Data());
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
  int n;
  
  while (ievent < maxNumberOfEvents) {
    if (!pythia.next()) {
      if (++iErrors < maxErrors) continue;
      cout << "Error: too many errors in event generation - check your settings & code" << endl;
      break;
    }
    // zyj
    Event &event = pythia.event;
    
    int nelectrons = 0;
    int ic = 0;
    int ie = 0;
      
    for (int i = 0; i < event.size(); i++) {
      if (event[i].isFinal() && abs(event[i].id()) == 11) { // event is electron
        //
        //  Check if mother is a c/b hadron
        //
        vector<int> mothers = event.motherList(i);
        if (mothers.size() > 1) {
          cout << "Error: electron has more than one mother. Stop." << endl;
          //abort();
          return 0;
        }
        ic = mothers[0];
        ie = i;
        int ic_id = abs(event[ic].id());
        int flavor = static_cast<int>(ic_id/pow(10.,static_cast<int>(log10(ic_id))));
        if (flavor != 4 && flavor != 5) continue; // c (b) hadrons start with 4(5)
        
        //
        //  Acceptance filter
        //
        if (!(isInAcceptanceE(i, event))) continue;
        
        //
        // Get grandmother (origin of c/b hadron)
        //
        vector<int> grandmothers = event.motherList(ic);
        int iorig = -1;
        switch(grandmothers.size()) {
          case 0:
            iorig = -1;
            break;
          case 1:
            iorig = grandmothers[0];
            break;
          default:
            iorig = -2;
            break;
        }
        //zyj
        pTTrkE[nelectrons]  = event[ie].pT();
        etaE[nelectrons]    = event[ie].y();
        phiE[nelectrons]    = event[ie].phi();
        idE[nelectrons]     = event[ie].id();
          
        nelectrons++;
      }
    }
      
    nElec = nelectrons;
    if(nElec == 0) continue;
    
    Hadrons.clear();
    for (int i = 0; i < event.size(); i++) {
          if (event[i].isFinal()) {
            Hadrons.push_back(event[i]); //zyj
          }
    }
    hfProdTree->Fill(); //zyj
    
    //
    numberOfElectrons += nElec;
      
    ievent++;
    if (ievent%pace == 0) {
      cout << "# of events generated = " << ievent
      << ", # of electrons from c/b hadron decays generated so far = " << numberOfElectrons << endl;
    }
    
    // List first few events.
    if (ievent < nList) {
      pythia.info.list();
      pythia.process.list();
      pythia.event.list();
    }
    
    hPTHat->Fill(pythia.info.pTHat());
  }
  
  //--------------------------------------------------------------
  //  Finish up
  //--------------------------------------------------------------
  pythia.statistics();
  hStatistics->SetBinContent(1,pythia.info.sigmaGen());
  hStatistics->SetBinContent(2,pythia.info.nAccepted());
  
  cout << "Writing File" << endl;
  hfile->Write();
  hStatistics->Write();
  hfProdTree->Write();
  hPTHat->Write();
  hfile->Close();
  
  now = time(0);
  cout << "============================================================================\
  " << endl;
  cout << "Program finished at: " << ctime(&now);
  cout << "============================================================================\
  " << endl;
  
  return 0;
}


bool isInAcceptanceE(int i, const Event& event)
{
  // accept all (useful for many studies)
  //  return true;
  
  // limit to STAR TPC/BEMC/ToF acceptance
  double eta = event[i].eta();
  if (fabs(eta) < 1.0)
    return true;
  else
    return false;
}

bool isInAcceptanceH(int i, const Event& event)
{
  // limit to STAR TPC/BEMC/ToF acceptance
  double eta = event[i].eta();
  if (fabs(eta) < 1.0)
    return true;
  else
    return false;
}

double deltaPhi(double phi1, double phi2)
{
  // move to range [0, 2pi]
  //if (phi1<0) phi1 += 2*M_PI;
  //if (phi2<0) phi2 += 2*M_PI;
  
  // correct difference
  double delta = phi2-phi1;
  if (delta < -M_PI) delta += 2*M_PI;
  if (delta > M_PI) delta -= 2*M_PI;
  
  return delta;
}

double deltaEta(double e1, double e2)
{
  double delta = e2-e1;
  return delta;
}

