/*/-----------------

  \class is for the eventGen decay tree production

  Auther:  Xiaozhi 5/1/2015 xiaozhi@uic.edu

  ----------------*/

/*
  #include "EvtGen/EvtGen.hh"

  #include "EvtGenBase/EvtParticle.hh"
  #include "EvtGenBase/EvtParticleFactory.hh"
  #include "EvtGenBase/EvtPatches.hh"
  #include "EvtGenBase/EvtPDL.hh"
  #include "EvtGenBase/EvtRandom.hh"
  #include "EvtGenBase/EvtReport.hh"
  #include "EvtGenBase/EvtHepMCEvent.hh"
  #include "EvtGenBase/EvtStdlibRandomEngine.hh"
  #include "EvtGenBase/EvtAbsRadCorr.hh"
  #include "EvtGenBase/EvtDecayBase.hh"

  #ifdef EVTGEN_EXTERNAL
  #include "EvtGenExternal/EvtExternalGenList.hh"
  #endif
*/

#ifndef StEvtGenDecayMaker__h
#define StEvtGenDecayMaker__h

#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <vector>
#include <fstream>
#include <TFile.h>
#include <TH1F.h>
#include"TParticle.h"
#include"StLorentzVectorF.hh"
#include"TLorentzVector.h"
#include"TClonesArray.h"
#include "TVirtualMCDecayer.h"
#include "TClonesArray.h"
#include "TString.h"
#include "vector"
#include "TRandom.h"
//#include "StRoot/StarGenerator/StarEvtGenDecayer/StarEvtGenDecayer.h"
#include "TNtuple.h"
#include "TFile.h"
#include "time.h"
#include "TGraph.h"
#include "StMaker.h"

class StarEvtGenDecayer; 

class StEvtGenDecayMaker : public StMaker 
{
 public:
  StEvtGenDecayMaker();
  ~StEvtGenDecayMaker();
  StEvtGenDecayMaker(int,int,TString );
  
  void OpenFile();
  void make();
  void Write();
  void SaveTree();
  
  void get_kinematics(Double_t& pt, Double_t& eta, Double_t& phi, Double_t& px, Double_t& py, Double_t& pz,Double_t &E,Double_t ); 
  void ResolveDecay(StarEvtGenDecayer *Decay_Event,int &Ndaughter,Int_t Parent_pdg,TLorentzVector *p_mom,TLorentzVector *r_pos,Int_t mpdg[ ],double mPx[ ],double mPy[ ],double  mPz[ ], double mE[ ], double mvx[ ], double mvy[ ], double mvz[ ], double mct[ ], Int_t dpdg[ ], Int_t dParent_pdg[ ], double dPx[ ],double dPy[ ], double  dPz[ ],double dE[ ],double dRPx[ ],double dRPy[ ], double  dRPz[ ], double dvx[ ], double dvy[ ], double dvz[ ], double  dct[ ],double  d3Ddca[ ],double  ddcaXY[ ],double  ddcaZ[ ],double  d3DRdca[ ],double  dRdcaXY[ ],double  dRdcaZ[ ],Int_t Ncent[],double Vtx[],double Vty[],double Vtz[]);

  void SaveDaughter(TParticle *Particle,int &Ndaughter,int, TLorentzVector *p_mom, TLorentzVector *r_pos, Int_t mpdg[ ],double mPx[ ],double mPy[ ],double  mPz[ ], double mE[ ], double mvx[ ], double mvy[ ], double mvz[ ], double mct[ ], Int_t dpdg[ ], Int_t dParent_pdg[ ], double dPx[ ],double dPy[ ], double  dPz[ ],double dE[ ],double dRPx[ ],double dRPy[ ], double  dRPz[ ], double dvx[ ], double dvy[ ], double dvz[ ], double  dct[ ],double d3Ddca[],double ddcaXY[],double  ddcaZ[],double d3DRdca[],double dRdcaXY[],double  dRdcaZ[],Int_t Ncent[],double Vtx[],double Vty[],double Vtz[]);
  bool Continue_Decay(int);
 
 private:
  TFile *mfile;
  TTree *Tree;
  TString outfile_name;
  int parent_PDG;
  int NEvet;
  TH1D *Weight_pt;

  TH1F *levy_pythia;
  TH1F *levy_fonll;
  TH1D* D0YVsPty;

  TGraph* fCharm_Spectra;// = NULL;
  TGraph* fBottom_Spectra;//=NULL;


  ClassDef(StEvtGenDecayMaker, 1)
    };

#endif
