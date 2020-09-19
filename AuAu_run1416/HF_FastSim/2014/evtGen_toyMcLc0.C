/* *********************************************************************
 *  ROOT macro - Toy Monte Carlo Simulation for D0 decay
 *  Includes Momentum Resolution, DCA, hft ration, TPC efficiency ...
 *  Example for D0 --> Kpi
 *
 *  Authors:
 *            Guannan Xie (guannanxie@lbl.gov)
 *            **Mustafa Mustafa (mmustafa@lbl.gov)
 *            Hao Qiu (hqiu@lbl.gov)
 *
 *  ** Code Maintainer
 *
 * *********************************************************************
 */

#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TGraph.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TF1.h"
#include "TClonesArray.h"
#include "TPythia6.h"
#include "TPythia6Decayer.h"
#include "TRandom3.h"
#include "TParticle.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TGraph.h"
#include "TMath.h"
#include "phys_constants.h"
#include "SystemOfUnits.h"
#include "TStopwatch.h"
// #include "TSystem.h"
// #include "TMemStat.h"
#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TTimer.h"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGen/EvtGen.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtParticle.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtParticleFactory.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtPatches.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtPDL.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtRandom.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtReport.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtHepMCEvent.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtSimpleRandomEngine.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtAbsRadCorr.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenBase/EvtDecayBase.hh"
#include "StRoot/StarGenerator/EvtGen1_06_00/EvtGenExternal/EvtExternalGenList.hh"
#include "StarEvtGenDecayer.h"

using namespace std;

void initEvtGen();
void decayAndFill(int const kf, TLorentzVector* b, double const weight, TClonesArray& daughters);
void fill(int const kf, TLorentzVector* b, double weight, TLorentzVector const& eMom, TVector3 v00);
void getKinematics(TLorentzVector& b, double const mass);
TLorentzVector smearMom(TLorentzVector const& b, TF1 const * const fMomResolution);
TVector3 smearPos(TLorentzVector const& mom, TLorentzVector const& rMom, TVector3 const& pos);
TVector3 smearPosData(int iParticleIndex, double vz, TLorentzVector const& rMom, TVector3 const& pos);
TVector3 smearPosData_XY(int iParticleIndex, double vz, TLorentzVector const& rMom, TVector3 const& pos);
TVector3 smearPosData_Z(int iParticleIndex, double vz, TLorentzVector const& rMom, TVector3 const& pos);
float dca(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dcaSigned(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dcaXY(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dcaZ(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dca1To2(TVector3 const& p1, TVector3 const& pos1, TVector3 const& p2, TVector3 const& pos2, TVector3& v0);
TVector3 getVertex(int centrality);
TVector3 getPUVertex(int centrality);
int getZdcBin(int const centrality);
bool matchHft(int iParticleIndex, double vz, TLorentzVector const& mom);
bool tpcReconstructed(int iParticleIndex, float charge, int cent, TLorentzVector const& mom);
void bookObjects(std::string outFileName);
void write();
int getPtIndexDca(double);
int getEtaIndexDca(double);
int getVzIndexDca(double);
int getPhiIndexDca(double);

int getPtIndexHftRatio(double);
int getEtaIndexHftRatio(double);
int getVzIndexHftRatio(double);
int getPhiIndexHftRatio(double);

StarEvtGenDecayer* starEvtGenDecayer = NULL;
TNtuple* nt;
TFile* result;

TF1* fWeightFunction = NULL;
const Int_t nParticles = 3;
const Int_t nCentHftRatio = 9;
int num_lamda1520 = 0;
int num_kbar0 = 0;
int num_delta = 0;
int num=0;
int num_e=0;
TF1* fKaonMomResolution = NULL;
TF1* fPionMomResolution = NULL;
TF1* fProtonMomResolution = NULL;
int centralityDca = 0;
const Int_t nZdcX = 5;
const Double_t zdcxBins[] = {0,40,50,60,70,200};

// HFT ratio binning
// HFT ratio binning
const Int_t nEtasHftRatio = 10;
const Int_t nVzsHftRatio = 6;
const Int_t nPtBinsHftRatio = 36;
const Double_t EtaEdgeHftRatio[nEtasHftRatio + 1] =
{
  -1.0, -0.8, -0.6, -0.4, -0.2, 0,  0.2, 0.4, 0.6, 0.8, 1.0
};
const Double_t VzEdgeHftRatio[nVzsHftRatio + 1] =
{
  -6.0e4, -4.0e4, -2.0e4, 0.0, 2.0e4, 4.0e4, 6.0e4
};
const Double_t ptEdgeHftRatio[nPtBinsHftRatio + 1] =
{
  0.3, 0.4, 0.5, 0.6 , 0.7 , 0.8 , 0.9 ,
  1. , 1.1 , 1.2 , 1.3 , 1.4 , 1.5 , 1.6 , 1.7 , 1.8 , 1.9 ,
  2. , 2.2 , 2.4 , 2.6 , 2.8 , 3.0 ,
  3.4 , 3.8 , 4.2 , 4.6 , 5.0 ,  5.5 ,
  6. , 6.5 , 7.0 , 8.0 , 9.0 , 10. , 11,  12.0
};
const Int_t nPhisHftRatio = 11;
const Double_t PhiEdgeHftRatio[nPhisHftRatio + 1] =
{
  -3.14159 , -2.80359 , -2.17527 , -1.54696 , -0.918637 , -0.290319 , 0.338 , 0.966319 , 1.59464 , 2.22296 , 2.85127 , 3.14159 //Sector by Sector  // sector number 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3
};

const Int_t nPhisDca = 11;
const Double_t PhiEdgeDca[nPhisDca + 1] =
{
  -3.14159 , -2.80359 , -2.17527 , -1.54696 , -0.918637 , -0.290319 , 0.338 , 0.966319 , 1.59464 , 2.22296 , 2.85127 , 3.14159 //Sector by Sector  // sector number 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3
};

// DCA binning
int const nVzsDca = 4;
float const VzEdgeDca[nVzsDca + 1] = { -6.e4, -3.e4, 0, 3.e4, 6.e4};

int const nEtasDca = 5;
float const EtaEdgeDca[nEtasDca + 1] = { -1.0, -0.6, -0.2, 0.2, 0.6, 1.0};

const Int_t nPtBinsDca = 19;
const Double_t ptEdgeDca[nPtBinsDca + 1] =
{
  0.3, 0.4, 0.5,
  0.6,  0.7 , 0.8 , 0.9 ,
  1. , 1.25 , 1.5 , 1.75 , 2.  , 2.25 , 2.5 , 2.75 , 3.0 , 3.5,
  4.  , 6. , 12.0
};


TH1F* h1Vz[nCentHftRatio];
TH1F* h1ZdcX[nCentHftRatio];

TH1D* hHftRatio1[nParticles][nEtasHftRatio][nVzsHftRatio][nPhisHftRatio];
int const nCentDca = 9;
TH2F* h2Dca[nParticles][nEtasDca][nVzsDca][nPtBinsDca];
TH2F* h2Dca_all;
TH1D* hHftRatioCorrect[nParticles][nEtasHftRatio][nVzsHftRatio][nPhisHftRatio][1];

TH1D* hTpcPiPlus[nCentHftRatio];
TH1D* hTpcPiMinus[nCentHftRatio];
TH1D* hTpcKPlus[nCentHftRatio];
TH1D* hTpcKMinus[nCentHftRatio];
TH1D* hTpcProton[nCentHftRatio];
TH1D* hTpcAntiProton[nCentHftRatio];
std::string DECFILE;
int pidcode;
double mass;
std::string outFileName;


std::pair<float, float> const momentumRange(0, 15);

float const gVzCut = 6.0e4;
float const acceptanceRapidity = 1.0;
float const sigmaPos0 = 15.2;
float const pxlLayer1Thickness = 0.00486;
//float const sigmaVertexCent[nCentHftRatio] = {31., 18.1, 12.8, 9.3, 7.2, 5.9, 5., 4.6, 4.};

int centralitySelect=0;
int const CentralityDca = 0;

//============== main  program ==================
//int const CentralityDca = 0;// NEED to change every time//centrality
int jobindx;
void evtGen_toyMcLc0(int npart=10e6, int jobId=0, int mode=1) {
  
  //jobindx = jobId/9;
  //centralitySelect = jobId%9;
  //========================================
  // Bottom hadron decays
  //========================================
  if(mode==11){
    DECFILE = "BottomSemileptonicDecay.DEC";
    pidcode =511; //B0
    mass = 5.27929;//
    outFileName = "B0.toyMc0";
  }
  if(mode==22){
    DECFILE = "BottomSemileptonicDecay.DEC";
    pidcode =521; //B+
    mass = 5.2796;
    outFileName = "Bp.toyMc0";
  }
  if(mode==33){
    DECFILE = "BottomSemileptonicDecay.DEC";
    pidcode =531; //Bs
    mass = 5.36679;//
    outFileName = "Bs.toyMc0";
  }
  if(mode==44){
    DECFILE = "BottomSemileptonicDecay.DEC";
    pidcode =5122; //Lb
    mass = 5.6202;
    outFileName = "Lb.toyMc0";
  }
  //JPis
  if(mode==5){
    DECFILE = "JPsi.DEC";
    pidcode = 211;//311; //J/psi
    mass = 0.139;//3.096916;
    outFileName = "Jpsi.toyMc0";
  }
  
  if(mode==6){
    DECFILE = "Pi0Dalitz.DEC";
    pidcode = 111;//111;//311; //J/psi
    mass = 0.1349766;//3.096916;
    outFileName = "Pi0.toyMc0";
  }
  if(mode==7){
    DECFILE = "Kaon.DEC";
    pidcode =310;//111;//311; //J/psi
    mass = 0.4976;//3.096916;
    outFileName = "KSe3.toyMc0";
  }
  //========================================
  // Charm hadron decays
  //========================================
  if(mode==1){
    DECFILE = "CharmSemileptonicDecay.DEC";
    pidcode =421; //D0
    mass = 1.86484;
    outFileName = "D0.toyMc0";
  }
  if(mode==2){
    DECFILE = "CharmSemileptonicDecay.DEC";
    pidcode =411; //D+
    mass = 1.86962;
    outFileName = "Dp.toyMc0";
  }
  if(mode==3){
    DECFILE = "CharmSemileptonicDecay.DEC";
    pidcode =431; //Ds
    mass = 1.96847;
    outFileName = "Ds.toyMc0";
  }
  if(mode==4){
    DECFILE = "CharmSemileptonicDecay.DEC";
    pidcode =4122; //Lc
    mass = 2.28646;
    outFileName = "Lc.toyMc0";
  }
  
  jobindx = jobId;
  centralitySelect = 0;
  
  initEvtGen();
  // TMemStat mem;
  // mem.Enable();
  TStopwatch*   stopWatch = new TStopwatch();
  stopWatch->Start();
  gRandom->SetSeed();
  bookObjects( outFileName);
  TString name = "B0";
  //TDatabasePDG::Instance()->AddParticle(name, "B038", 5.2796, kFALSE, , 1.5, "Meson", 511);
  
  TLorentzVector* b_d = new TLorentzVector;
  TClonesArray ptl("TParticle", 10);
  Int_t per = npart/100;
  for (int ipart = 0; ipart < npart; ipart++)
  {
    if(ipart%per==0) cout<<"PROCESSING "<<int(float(ipart)/npart*100)<<"%...."<<endl;
    
    getKinematics(*b_d,mass);
    
    decayAndFill(pidcode,  b_d, fWeightFunction->Eval(b_d->Perp()), ptl); // 这里weight 虽然填了，但没什么用
    if(!mode==6 && !mode==7)decayAndFill(-1*pidcode, b_d, fWeightFunction->Eval(b_d->Perp()), ptl);
    
    
    if (ipart % 1000 == 1) nt->AutoSave("SaveSelf");
  }
  cout << "Number of electrons = " << float(num_e) << endl;
  
  write();
  // mem.Show();
  stopWatch->Stop();
  stopWatch->Print();
}

void decayAndFill(int const kf, TLorentzVector* b, double const weight, TClonesArray& daughters)
{
  TLorentzVector eMom;
  TVector3 v00;
  
  starEvtGenDecayer->Decay(kf, b);
  starEvtGenDecayer->ImportParticles(&daughters);
  int nTrk = daughters.GetEntriesFast();
  num++;
  for (int iTrk = 0; iTrk < nTrk; ++iTrk)
  {
    TParticle* ptl0 = (TParticle*)daughters.At(iTrk);
    
    switch (abs(ptl0->GetPdgCode()))
    {
      case 11:
        num_e++;
        ptl0->Momentum(eMom);
        v00.SetXYZ(ptl0->Vx() * 1000., ptl0->Vy() * 1000., ptl0->Vz() * 1000.); // converted to μm
        fill(kf, b, weight, eMom, v00);
        break;
      case 22: // gamma
        num_e++;
        ptl0->Momentum(eMom);
        v00.SetXYZ(ptl0->Vx() * 1000., ptl0->Vy() * 1000., ptl0->Vz() * 1000.); // converted to μm
        //fill(kf, b, weight, eMom, v00);
        break;
        //          case 211:
        //num_e++;
        //ptl0->Momentum(eMom);
        //v00.SetXYZ(ptl0->Vx() * 1000., ptl0->Vy() * 1000., ptl0->Vz() * 1000.); // converted to μm
        //fill(kf, b, weight, eMom, v00);
        //break;
      default:
        break;
    }
  }
  daughters.Clear();
}

void fill(int const kf, TLorentzVector* b, double weight,TLorentzVector const& eMom, TVector3 v00)
{
  
  
  int const centrality = centralitySelect;
  TVector3  vertex = getVertex(centrality);
  v00 += vertex;
  TVector3 const vertex_pu = getPUVertex(centrality);
  //v00 += vertex_pu;
  // smear momentum
  TLorentzVector const eRMom = smearMom(eMom, fPionMomResolution);
  
  // smear position
  int kch,pch,pich;
  if (1) {kch = 0; pch = 0; pich = 0;}
  
  TVector3 const eRPos = smearPosData(pich, vertex.z(), eRMom, v00);
  TVector3 const eRPos_XY = smearPosData_XY(pich, vertex.z(), eRMom, v00);
  TVector3 const eRPos_Z = smearPosData_Z(pich, vertex.z(), eRMom, v00);
  float const eDca = dcaSigned(eMom.Vect(), v00, vertex);
  float const eRDca = dcaSigned(eRMom.Vect(), eRPos, vertex);
  float eRDca_pu = dcaSigned(eRMom.Vect(), eRPos, vertex_pu);
  float const eRDca_XY = dcaXY(eRMom.Vect(), eRPos, vertex_pu);
  float const eRDca_Z = dcaZ(eRMom.Vect(), eRPos, vertex_pu);
  float const eRSDca = dcaSigned(eRMom.Vect(), eRPos, vertex);
  float const eRDcaXY = dcaXY(eRMom.Vect(), eRPos, vertex);
  float const eRDcaZ = dcaZ(eRMom.Vect(), eRPos, vertex);
  
  if(fabs(vertex.z()-vertex_pu.z())>30000)eRDca_pu=1E5;
  
  int const charge = kf > 0 ? 1 : -1;
  
  bool const eHft = matchHft(pich, vertex.z(), eRMom);
  bool const eTpc = tpcReconstructed(0,charge,centrality,eRMom);
  
  
  // save
  float arr[110];
  int iArr = 0;
  // Event info
  arr[iArr++] = centrality;
  arr[iArr++] = vertex.X();
  arr[iArr++] = vertex.Y();
  arr[iArr++] = vertex.Z();
  
  arr[iArr++] = kf;
  arr[iArr++] = weight;
  arr[iArr++] = b->M();
  arr[iArr++] = b->Perp();
  arr[iArr++] = b->PseudoRapidity();
  arr[iArr++] = b->Rapidity();
  arr[iArr++] = b->Phi();
  arr[iArr++] = v00.X();
  arr[iArr++] = v00.Y();
  arr[iArr++] = v00.Z();
  
  //arr[iArr++] = rMom.M();
  //arr[iArr++] = rMom.Perp();
  //arr[iArr++] = rMom.PseudoRapidity();
  //arr[iArr++] = rMom.Rapidity();
  //arr[iArr++] = rMom.Phi();
  //arr[iArr++] = v0.X();
  //arr[iArr++] = v0.Y();
  //arr[iArr++] = v0.Z();
  
  //arr[iArr++] = decayLength/1.0e4;
  
  arr[iArr++] = eMom.Perp();
  arr[iArr++] = eMom.PseudoRapidity();
  arr[iArr++] = eMom.Phi();
  arr[iArr++] = eRMom.Perp();
  arr[iArr++] = eRMom.PseudoRapidity();
  arr[iArr++] = eRMom.Phi();
  arr[iArr++] = eDca/1.0e4;
  arr[iArr++] = eRDca/1.0e4;
  arr[iArr++] = eRDca_pu/1.0e4;
  arr[iArr++] = eRDca_XY/1.0e4;
  arr[iArr++] = eRDca_Z/1.0e4;
  arr[iArr++] = eRDcaXY/1.0e4;
  arr[iArr++] = eRDcaZ/1.0e4;
  arr[iArr++] = eTpc;
  arr[iArr++] = eHft;
  
  nt->Fill(arr);
}

void getKinematics(TLorentzVector& b, double const mass)
{
  float const pt = gRandom->Uniform(momentumRange.first, momentumRange.second);
  // cout<<"pt = "<<pt<<endl;
  float const y = gRandom->Uniform(-acceptanceRapidity, acceptanceRapidity);
  float const phi = TMath::TwoPi() * gRandom->Rndm();
  
  float const mT = sqrt(mass * mass + pt * pt);
  float const pz = mT * sinh(y);
  float const E = mT * cosh(y);
  
  b.SetPxPyPzE(pt * cos(phi), pt * sin(phi) , pz, E);
}

float dca(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex)
{
  TVector3 posDiff = pos - vertex;
  return fabs(p.Cross(posDiff.Cross(p)).Unit().Dot(posDiff));
}

float dcaSigned(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex)
{
  TVector3 posDiff = pos - vertex;
  float sign = posDiff.x() * p.y() - posDiff.y() * p.x() > 0 ? +1 : -1;
  
  return sign * p.Cross(posDiff.Cross(p)).Unit().Dot(posDiff);
}

float dcaXY(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex)
{
  TVector3 newPos(pos);
  newPos.SetZ(0);
  
  TVector3 newP(p);
  newP.SetZ(0);
  
  TVector3 newVertex(vertex);
  newVertex.SetZ(0);
  
  TVector3 posDiff = newPos - newVertex;
  float sign = posDiff.x() * p.y() - posDiff.y() * p.x() > 0 ? +1 : -1;
  return sign * newP.Cross(posDiff.Cross(newP)).Unit().Dot(posDiff);
}

float dcaZ(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex)
{
  TVector3 posDiff = pos - vertex;
  if (sin(p.Theta()) == 0) return 0;
  else return (-posDiff.x() * cos(p.Phi()) - posDiff.y() * sin(p.Phi())) * cos(p.Theta()) / sin(p.Theta()) + posDiff.z();
}

float dca1To2(TVector3 const& p1, TVector3 const& pos1, TVector3 const& p2, TVector3 const& pos2, TVector3& v0)
{
  TVector3 posDiff = pos2 - pos1;
  TVector3 pu1 = p1.Unit();
  TVector3 pu2 = p2.Unit();
  double pu1Pu2 = pu1.Dot(pu2);
  double g = posDiff.Dot(pu1);
  double k = posDiff.Dot(pu2);
  double s2 = (k - pu1Pu2 * g) / (pu1Pu2 * pu1Pu2 - 1.);
  double s1 = g + s2 * pu1Pu2;
  TVector3 posDca1 = pos1 + pu1 * s1;
  TVector3 posDca2 = pos2 + pu2 * s2;
  v0 = 0.5 * (posDca1 + posDca2);
  return (posDca1 - posDca2).Mag();
}

TLorentzVector smearMom(TLorentzVector const& b, TF1 const * const fMomResolution)
{
  float const pt = b.Perp();
  float const sPt = gRandom->Gaus(pt, pt * fMomResolution->Eval(pt));
  
  TLorentzVector sMom;
  sMom.SetXYZM(sPt * cos(b.Phi()), sPt * sin(b.Phi()), sPt * sinh(b.PseudoRapidity()), b.M());
  return sMom;
}

TVector3 smearPos(TLorentzVector const& mom, TLorentzVector const& rMom, TVector3 const& pos)
{
  float thetaMCS = 13.6 / mom.Beta() / rMom.P() / 1000 * sqrt(pxlLayer1Thickness / fabs(sin(mom.Theta())));
  float sigmaMCS = thetaMCS * 28000 / fabs(sin(mom.Theta()));
  float sigmaPos = sqrt(pow(sigmaMCS, 2) + pow(sigmaPos0, 2));
  
  return TVector3(gRandom->Gaus(pos.X(), sigmaPos), gRandom->Gaus(pos.Y(), sigmaPos), gRandom->Gaus(pos.Z(), sigmaPos));
}

int getPtIndexDca(double pT)
{
  for (int i = 0; i < nPtBinsDca; i++)
  {
    if ((pT >= ptEdgeDca[i]) && (pT < ptEdgeDca[i + 1]))
      return i;
  }
  if (pT < ptEdgeDca[0]) return 0;
  return nPtBinsDca - 1 ;
}

int getEtaIndexDca(double Eta)
{
  for (int i = 0; i < nEtasDca; i++)
  {
    if ((Eta >= EtaEdgeDca[i]) && (Eta < EtaEdgeDca[i + 1]))
      return i;
  }
  return nEtasDca - 1 ;
}

int getVzIndexDca(double Vz)
{
  for (int i = 0; i < nVzsDca; i++)
  {
    if ((Vz >= VzEdgeDca[i]) && (Vz < VzEdgeDca[i + 1]))
      return i;
  }
  return nVzsDca - 1 ;
}

int getPhiIndexDca(double Phi)
{
  for (int i = 0; i < nPhisDca; i++)
  {
    if ((Phi >= PhiEdgeDca[i]) && (Phi < PhiEdgeDca[i + 1]))
      return i;
  }
  return nPhisDca - 1 ;
}

int getPtIndexHftRatio(double pT)
{
  for (int i = 0; i < nPtBinsHftRatio; i++)
  {
    if ((pT >= ptEdgeHftRatio[i]) && (pT < ptEdgeHftRatio[i + 1]))
      return i;
  }
  if (pT<ptEdgeHftRatio[0]) return 0;
  return nPtBinsHftRatio - 1 ;
}

int getEtaIndexHftRatio(double Eta)
{
  for (int i = 0; i < nEtasHftRatio; i++)
  {
    if ((Eta >= EtaEdgeHftRatio[i]) && (Eta < EtaEdgeHftRatio[i + 1]))
      return i;
  }
  return nEtasHftRatio - 1 ;
}

int getVzIndexHftRatio(double Vz)
{
  for (int i = 0; i < nVzsHftRatio; i++)
  {
    if ((Vz >= VzEdgeHftRatio[i]) && (Vz < VzEdgeHftRatio[i + 1]))
      return i;
  }
  return nVzsHftRatio - 1 ;
}

int getPhiIndexHftRatio(double Phi)
{
  for (int i = 0; i < nPhisHftRatio; i++)
  {
    if ((Phi >= PhiEdgeHftRatio[i]) && (Phi < PhiEdgeHftRatio[i + 1]))
      return i;
  }
  return nPhisHftRatio - 1 ;
}

TVector3 smearPosData(int const iParticleIndex, double const vz, TLorentzVector const& rMom, TVector3 const& pos)
{
  int const iEtaIndex = getEtaIndexDca(rMom.PseudoRapidity());
  int const iVzIndex  = getVzIndexDca(vz);
  // int const iPhiIndex = getPhiIndexDca(rMom.Phi());
  int const iPtIndex  = getPtIndexDca(rMom.Perp());
  
  double sigmaPosZ = 0;
  double sigmaPosXY = 0;
  
  // if (cent == 8) cent = 7;
  // All the centrality position smear was based on 0-10% centrality input
  // changed to 0-80%
  
  //if(h2Dca[iParticleIndex][iEtaIndex][iVzIndex][iPtIndex]->Integral()>0)
  //h2Dca[iParticleIndex][iEtaIndex][iVzIndex][iPtIndex]->GetRandom2(sigmaPosXY, sigmaPosZ);
  //else
  //h2Dca_all->GetRandom2(sigmaPosXY, sigmaPosZ);
  //sigmaPosZ *= 1.e4;
  //sigmaPosXY *= 1.e4;
  if (h2Dca[iParticleIndex][iEtaIndex][iVzIndex][iPtIndex]->ComputeIntegral())
  {
    do {
      h2Dca[iParticleIndex][iEtaIndex][iVzIndex][iPtIndex]->GetRandom2(sigmaPosXY, sigmaPosZ);
      sigmaPosZ *= 1.e4;
      sigmaPosXY *= 1.e4;
    }
    while (fabs(sigmaPosZ) > 1.e3 || fabs(sigmaPosXY) > 1.e3);
  }
  
  
  
  TVector3 newPos(pos);
  newPos.SetZ(0);
  TVector3 momPerp(-rMom.Vect().Y(), rMom.Vect().X(), 0.0);
  newPos -= momPerp.Unit() * sigmaPosXY;
  
  return TVector3(newPos.X(), newPos.Y(), pos.Z() + sigmaPosZ);
}TVector3 smearPosData_XY(int const iParticleIndex, double const vz, TLorentzVector const& rMom, TVector3 const& pos)
{
  int const iEtaIndex = getEtaIndexDca(rMom.PseudoRapidity());
  int const iVzIndex  = getVzIndexDca(vz);
  // int const iPhiIndex = getPhiIndexDca(rMom.Phi());
  int const iPtIndex  = getPtIndexDca(rMom.Perp());
  
  double sigmaPosZ = 0;
  double sigmaPosXY = 0;
  
  h2Dca[iParticleIndex][iEtaIndex][iVzIndex][iPtIndex]->GetRandom2(sigmaPosXY, sigmaPosZ);
  sigmaPosZ *= 1.e4;
  sigmaPosXY *= 1.e4;
  
  TVector3 newPos(pos);
  newPos.SetZ(0);
  TVector3 momPerp(-rMom.Vect().Y(), rMom.Vect().X(), 0.0);
  newPos -= momPerp.Unit() * sigmaPosXY;
  
  return TVector3(newPos.X(), newPos.Y(), pos.Z());
}
TVector3 smearPosData_Z(int const iParticleIndex, double const vz, TLorentzVector const& rMom, TVector3 const& pos)
{
  int const iEtaIndex = getEtaIndexDca(rMom.PseudoRapidity());
  int const iVzIndex  = getVzIndexDca(vz);
  // int const iPhiIndex = getPhiIndexDca(rMom.Phi());
  int const iPtIndex  = getPtIndexDca(rMom.Perp());
  
  double sigmaPosZ = 0;
  double sigmaPosXY = 0;
  
  
  h2Dca[iParticleIndex][iEtaIndex][iVzIndex][iPtIndex]->GetRandom2(sigmaPosXY, sigmaPosZ);
  sigmaPosZ *= 1.e4;
  sigmaPosXY *= 1.e4;
  
  TVector3 newPos(pos);
  newPos.SetZ(0);
  TVector3 momPerp(-rMom.Vect().Y(), rMom.Vect().X(), 0.0);
  newPos -= momPerp.Unit() * sigmaPosXY;
  
  return TVector3(pos.X(), pos.Y(), pos.Z() + sigmaPosZ);
}



TVector3 getVertex(int const centrality)
{
  double rdmVz;
  
  if (h1Vz[centrality]->GetEntries() == 0) rdmVz = 0.;
  else
  {
    do rdmVz = h1Vz[centrality]->GetRandom() * 1e4;
    while (fabs(rdmVz) > gVzCut);
  }
  
  return TVector3(0.,0., rdmVz);
}
TVector3 getPUVertex(int const centrality)
{
  double rdmVz;
  
  if (h1Vz[centrality]->GetEntries() == 0) rdmVz = 0.;
  else
  {
    rdmVz = h1Vz[centrality]->GetRandom() * 1e4;
    //while (fabs(rdmVz) > gVzCut);
  }
  
  return TVector3(0.,0., rdmVz);
}

int getZdcBin(int const centrality)
{
  return 0;
}

bool tpcReconstructed(int iParticleIndex, float charge, int cent, TLorentzVector const& mom)
{
  TH1D* h = NULL;
  
  if (iParticleIndex == 0)
  {
    if (charge > 0) h = hTpcPiPlus[cent];
    else h = hTpcPiMinus[cent];
  }
  else if(iParticleIndex == 1)
  {
    if (charge > 0) h = hTpcKPlus[cent];
    else h = hTpcKMinus[cent];
  }
  else
  {
    if (charge > 0) h = hTpcProton[cent];
    else h = hTpcAntiProton[cent];
  }
  
  // int const bin = h->FindBin(mom.Perp());
  int bin = h->FindBin(mom.Perp());
  // if (iParticleIndex == 2 && mom.Perp() >= 5.0) bin = h->FindBin(4.5); //for proton and antiproton, pT range is 5Gev
  
  return gRandom->Rndm() < h->GetBinContent(bin);
}

bool matchHft(int const iParticleIndex, double const vz, TLorentzVector const& mom) {
  int const iEtaIndex = getEtaIndexHftRatio(mom.PseudoRapidity());
  int const iVzIndex = getVzIndexHftRatio(vz);
  int const iPhiIndex = getPhiIndexHftRatio(mom.Phi());
  
  int const bin = hHftRatio1[iParticleIndex][iEtaIndex][iVzIndex][iPhiIndex]->FindBin(mom.Perp());
  return gRandom->Rndm() < hHftRatio1[iParticleIndex][iEtaIndex][iVzIndex][iPhiIndex]->GetBinContent(bin);
}

//___________
void bookObjects(std::string outFileName)
{
  cout << "Loading input momentum resolution ..." << endl;
  TFile f("Momentum_resolution_SL16d.root");
  fPionMomResolution = (TF1*)f.Get("fPion")->Clone("fPion");
  fKaonMomResolution = (TF1*)f.Get("fKaon")->Clone("fKaon");
  fProtonMomResolution = (TF1*)f.Get("fProton")->Clone("fProton");
  f.Close();
  
  cout << "Loading input spectra ..." << endl;
  TFile fPP("pp200_spectra.root");
  fWeightFunction = (TF1*)fPP.Get("run12/f1Levy")->Clone("f1Levy");
  fPP.Close();
  
  
  TFile fVertex("Vz_Cent.root");
  
  for (int ii = 0; ii < nCentHftRatio; ++ii)
  {
    h1Vz[ii]      = (TH1F*)(fVertex.Get(Form("mh1Vz_%i", ii)));
    h1Vz[ii]->SetDirectory(0);
  }
  
  fVertex.Close();
  
  
  
  cout << "Loading input HFT ratios and DCA ..." << endl;
  TFile fHftRatio1("Lc_HFT.root");
  TFile fDca1("Lc_2DProjection.root");
  TFile fDca2("DCAResolutions.root");//Lc_2DProjection.root");
  for (int iParticle = 0; iParticle < nParticles; ++iParticle)
  {
    for (int iCent = 0; iCent < 1; ++iCent)
    {
      // HFT ratio
      for (int iEta = 0; iEta < nEtasHftRatio; ++iEta)
      {
        for (int iVz = 0; iVz < nVzsHftRatio; ++iVz)
        {
          for (int iPhi = 0; iPhi < nPhisHftRatio; ++iPhi)
          {
            hHftRatio1[iParticle][iEta][iVz][iPhi] = (TH1D*)(fHftRatio1.Get(Form("mh1HFT1PtCentPartEtaVzPhiRatio_%i_%i_%i_%i_%i", iParticle, iEta, iVz, iPhi, centralityDca)));
            hHftRatio1[iParticle][iEta][iVz][iPhi]->SetDirectory(0);
          }
        }
      }
    }
    cout << "Finished loading HFT Ratio: " <<  endl;
    
    // DCA
    for (int iEta = 0; iEta < nEtasDca; ++iEta)
    {
      for (int iVz = 0; iVz < nVzsDca; ++iVz)
      {
        for (int iPt = 0; iPt < nPtBinsDca; ++iPt)
        {
          h2Dca[iParticle][iEta][iVz][iPt] = (TH2F*)((fDca1.Get(Form("mh2DcaPtCentPartEtaVzPhi_%i_%i_%i_%i_%i", iParticle, iEta, iVz, centralityDca, iPt))));
          h2Dca[iParticle][iEta][iVz][iPt]->SetDirectory(0);
        }
      }
    }
    cout << "Fished loading DCA for particle " << iParticle <<  endl;
  }
  h2Dca_all = (TH2F*)((fDca2.Get("h1")));
  h2Dca_all->SetDirectory(0);
  
  cout << "Finished loading Dca: " <<  endl;
  
  fHftRatio1.Close();
  fDca1.Close();
  
  
  cout << " Loading TPC tracking efficiencies " << endl;
  
  
  TFile fTpcPiPlus("Eff_PionPlus_embedding.root");
  TFile fTpcPiMinus("Eff_PionMinus_embedding.root");
  TFile fTpcKPlus("Eff_KaonPlus_embedding.root");
  TFile fTpcKMinus("Eff_KaonMinus_embedding.root");
  TFile fTpcProton("Eff_Proton_embedding.root");
  TFile fTpcAntiProton("Eff_AntiProton_embedding.root");
  
  for (int iCent = 0; iCent < nCentHftRatio; ++iCent)
  {
    hTpcPiPlus[iCent] = (TH1D*)fTpcPiPlus.Get(Form("h1Ratiocent_%i", iCent));
    hTpcPiPlus[iCent]->SetDirectory(0);
    hTpcPiMinus[iCent] = (TH1D*)fTpcPiMinus.Get(Form("h1Ratiocent_%i", iCent));
    hTpcPiMinus[iCent] ->SetDirectory(0);
    hTpcKPlus[iCent] = (TH1D*)fTpcKPlus.Get(Form("h1Ratiocent_%i", iCent));
    hTpcKPlus[iCent]->SetDirectory(0);
    hTpcKMinus[iCent] = (TH1D*)fTpcKMinus.Get(Form("h1Ratiocent_%i", iCent));
    hTpcKMinus[iCent]->SetDirectory(0);
    hTpcProton[iCent] = (TH1D*)fTpcProton.Get(Form("h1Ratiocent_%i", iCent));
    hTpcProton[iCent]->SetDirectory(0);
    hTpcAntiProton[iCent] = (TH1D*)fTpcAntiProton.Get(Form("h1Ratiocent_%i", iCent));
    hTpcAntiProton[iCent]->SetDirectory(0);
  }
  
  cout << "Done with loading all files ..." << endl;
  
  char fname[500];
  sprintf(fname,"%s_momreshijing_c%d_job%d.root",outFileName.c_str(),centralitySelect,jobindx);
  result = new TFile(fname, "recreate");
  result->SetCompressionLevel(1);
  result->cd();
  
  int BufSize = (int)pow(2., 16.);
  // int Split = 1;
  
  nt = new TNtuple("nt", "", "cent:vx:vy:vz:"
                   "pid:w:m:pt:eta:y:phi:v00x:v00y:v00z:" // MC Lc+
                   //"rM:rPt:rEta:rY:rPhi:rV0x:rV0y:rV0z:" // Rc Lc+
                   //"dcaDaughters:decayLength:dcaLcToPv:cosTheta:kpidca:pipdca:kpdca:" // Rc pair
                   //"kPt:kEta:" // MC Kaon
                   //"kRPt:kREta:kRDca:kTpc:kHft:" // Rc Kaon
                   "ePt:eEta:ePhi:" // e Pion
                   "eRPt:eREta:eRPhi:eDca:eRDca:eRDca_pu:eRDca_XY:eRDca_Z:eRDcaXY:eRDcaZ:eTpc:eHft" // e Pion
                   //"pPt:pEta:" // MC Proton
                   //"pRPt:pREta:pRDca:pTpc:pHft" // Rc Proton
                   , BufSize);
  // nt->SetAutoSave(-500000); // autosave every 1 Mbytes
  cout << "checking where is the abort..." << endl;
}
//___________
void write()
{
  result->cd();
  nt->Write();
  result->Close();
}
//___________
void initEvtGen()
{
  EvtRandomEngine* eng = 0;
  eng = new EvtSimpleRandomEngine();
  EvtRandom::setRandomEngine((EvtRandomEngine*)eng);
  EvtAbsRadCorr* radCorrEngine = 0;
  std::list<EvtDecayBase*> extraModels;
  
  EvtExternalGenList genList;
  radCorrEngine = genList.getPhotosModel();
  extraModels = genList.getListOfModels();
  
  TString Decay_DEC = "StRoot/StarGenerator/EvtGen1_06_00/DECAY.DEC";
  TString Evt_pdl = "StRoot/StarGenerator/EvtGen1_06_00/evt.pdl";
  EvtGen *myGenerator = new EvtGen(Decay_DEC, Evt_pdl, (EvtRandomEngine*)eng, radCorrEngine, &extraModels);
  starEvtGenDecayer = new StarEvtGenDecayer(myGenerator);
  // starEvtGenDecayer->SetDecayTable("Lc.Mypythia.DEC");
  starEvtGenDecayer->SetDecayTable(DECFILE);
  // starEvtGenDecayer->SetDebug(1);
}
