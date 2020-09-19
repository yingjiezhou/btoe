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
#include "TString.h"
#include "phys_constants.h"
#include "SystemOfUnits.h"
#include "TStopwatch.h"
// #include "TSystem.h"
// #include "TMemStat.h"
/*#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TTimer.h"
#include "EvtGen/EvtGen.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtReport.hh"
#include "EvtGenBase/EvtHepMCEvent.hh"
#include "EvtGenBase/EvtSimpleRandomEngine.hh"
#include "EvtGenBase/EvtAbsRadCorr.hh"
#include "EvtGenBase/EvtDecayBase.hh"
#include "EvtGenExternal/EvtExternalGenList.hh"
#include "StarEvtGenDecayer.h"
*/
using namespace std;
float const M_DS = 1.96830;
//void initEvtGen();
void setDecayChannels(int const mdme);
void decayAndFill(int const centrality_low, int const kf, TLorentzVector* b, double const weight, TClonesArray& daughters);
void fill(int const centrality_low, int const kf, TLorentzVector* b, double weight, TLorentzVector const& kMom, TLorentzVector const& p1Mom, TLorentzVector const& p2Mom, TVector3 v00);
void getKinematics(TLorentzVector& b, double const mass);
TLorentzVector smearMom(TLorentzVector const& b, TF1 const * const fMomResolution);
TVector3 smearPos(TLorentzVector const& mom, TLorentzVector const& rMom, TVector3 const& pos);
TVector3 smearPosData(int iParticleIndex, double vz, TLorentzVector const& rMom, TVector3 const& pos);
float dca(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dcaSigned(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dcaXY(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dcaZ(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dca1To2(TVector3 const& p1, TVector3 const& pos1, TVector3 const& p2, TVector3 const& pos2, TVector3& v0);
TVector3 getVertex();
bool matchHft(int iParticleIndex, double vz, TLorentzVector const& mom);
float tpcReconstructed(int iParticleIndex, float charge, TLorentzVector const& mom);
void bookObjects(TString outFileName, int const centrality_low, int const centrality_high);
void write();
int getPtIndexDca(double);
int getEtaIndexDca(double);
int getVzIndexDca(double);
int getPhiIndexDca(double);
TF1*          fpionNsig_eff = NULL;
TF1*          fpionNsigTof_eff = NULL; //divided 0.013
TF1*          fkaonNsig_eff = NULL;
TF1*          fkaonNsigTof_eff    = NULL;//divided 0.013
TF1* ftofpi[9];
TF1* ftofk[9];
TF1* ftofp[9];
int getPtIndexHftRatio(double);
int getEtaIndexHftRatio(double);
int getVzIndexHftRatio(double);
int getPhiIndexHftRatio(double);
TPythia6Decayer* pydecay;
//StarEvtGenDecayer* starEvtGenDecayer = NULL;
TNtuple* nt;
TFile* result;

TF1* fWeightFunction = NULL;
const Int_t nParticles = 2;
const Int_t nCentHftRatio = 1;
int num_lamda1520 = 0;
int num_kbar0 = 0;
int num_delta = 0;
int anti_num_lamda1520 = 0;
int num_k0 = 0;
int anti_num_delta = 0;
int KPlus_num =0;
int KMinus_num = 0;
int flag = 2 ;
TF1* fKaonMomResolution = NULL;
TF1* fPionMomResolution = NULL;
//TF1* fProtonMomResolution = NULL;

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

TH1D* h1Vz;

//TH1D* hHftRatioCorrect[nParticles][nEtasHftRatio][nVzsHftRatio][nPhisHftRatio];
TH1F* hHftRatio1[nParticles][nEtasHftRatio][nVzsHftRatio][nPhisHftRatio];
// int const nCentDca = 9;
//int const nCentDca = 1;// run fastsimu one by one for centrality
TH2F* h2Dca[nParticles][nEtasDca][nVzsDca][nPtBinsDca];

TH1D* hTpcPiPlus;
TH1D* hTpcPiMinus;
TH1D* hTpcKPlus;
TH1D* hTpcKMinus;
//TH1D* hTpcProton;
//TH1D* hTpcAntiProton;

//string outFileName = "Lc.toyMc0.root";
std::pair<float, float> const momentumRange(0, 10);
std::pair<int, int> const decayChannels(818, 850);
float const gVzCut = 6.0e4;
float const acceptanceRapidity = 1.0;
float const sigmaPos0 = 15.2;
float const pxlLayer1Thickness = 0.00486;
//float const sigmaVertexCent[nCentHftRatio] = {31., 18.1, 12.8, 9.3, 7.2, 5.9, 5., 4.6, 4.};

//============== main  program ==================
//int const CentralityDca = 0;// NEED to change every time//centrality
void Pythia_toyMcDs_right_Eff(TString outFileName, int npart, int const centrality_low, int const centrality_high)
{
  // initEvtGen();
   // TMemStat mem;
   // mem.Enable();
   TStopwatch*   stopWatch = new TStopwatch();
   stopWatch->Start();
   gRandom->SetSeed();
   bookObjects( outFileName, centrality_low, centrality_high);
  // TString name = "Lambda(1520)0";
   //TDatabasePDG::Instance()->AddParticle(name, "B038", 1.5195, kFALSE, 1.56e-02, 0., "Baryon", 3124);
pydecay = TPythia6Decayer::Instance();
pydecay->Init();
setDecayChannels(831); // 719 - D+ --> K- pi+ pi+ , 715 - D+->phi+pi
for(int idc=656; idc<667; idc++)  TPythia6::Instance()->SetMDME(idc,1,0); // phi decay
TPythia6::Instance()->SetMDME(656,1,1); // phi-> k + k

TLorentzVector* b_d = new TLorentzVector;
   TClonesArray ptl("TParticle", 10);
   Int_t per = npart/100;
   for (int ipart = 0; ipart < npart; ipart++)
   {
      if(ipart%per==0) cout<<"PROCESSING "<<int(float(ipart)/npart*100)<<"%...."<<endl;
      getKinematics(*b_d, M_DS);

      decayAndFill(centrality_low, 431, b_d, fWeightFunction->Eval(b_d->Perp()), ptl);
       decayAndFill(centrality_low, -431, b_d, fWeightFunction->Eval(b_d->Perp()), ptl);
      if (ipart % 100000 == 1) nt->AutoSave("SaveSelf");
   }
 /*  cout <<"num_lamda1520=" << num_lamda1520 <<"lamda1520_ratio = " << float(num_lamda1520)/npart << endl;
   cout << "num_kbar0="<< num_kbar0 << "kbar0_ratio = " << float(num_kbar0)/npart << endl;
   cout << "num_delta=" << num_delta <<"delta_ratio = " << float(num_delta)/npart << endl;
   cout <<"anti_num_lamda1520=" << anti_num_lamda1520 <<"anti_lamda1520_ratio = " << float(anti_num_lamda1520)/npart << endl;
   cout << "num_k0="<< num_k0 << "k0_ratio = " << float(num_k0)/npart << endl;
   cout << "anti_num_delta=" << anti_num_delta <<"delta_ratio = " << float(anti_num_delta)/npart << endl;
   */
//   cout << "K+ number is " << KPlus_num << "; K- number is" << KMinus_num << endl;
   write();
   // mem.Show();
   stopWatch->Stop();
   stopWatch->Print();
}

void setDecayChannels(int const mdme)
     {
            for (int idc = decayChannels.first; idc < decayChannels.second + 1; idc++) TPythia6::Instance()->SetMDME(idc, 1, 0);
            TPythia6::Instance()->SetMDME(mdme, 1, 1);
         }

void decayAndFill(int const centrality_low, int const kf, TLorentzVector* b, double const weight, TClonesArray& daughters)
{  
/*   if (  kf > 0)
     flag = 2;
   else 
      flag = -2; */
   pydecay->Decay(kf, b);
   pydecay->ImportParticles(&daughters);
   TLorentzVector kMom;
   TLorentzVector piMom;
   TLorentzVector pMom;
   TVector3 v00;

   //starEvtGenDecayer->Decay(kf, b);
   //starEvtGenDecayer->ImportParticles(&daughters);

   int nTrk = daughters.GetEntriesFast();
    //cout <<  "   nTrk = " << nTrk << endl;
   for (int iTrk = 0; iTrk < nTrk; ++iTrk)
   {
      TParticle* ptl0 = (TParticle*)daughters.At(iTrk);

     //  cout << "iTrk = " << iTrk << " , " << ptl0->GetPdgCode() << endl;
      switch ( ptl0->GetPdgCode()) 
       {    
        case 321:  num_lamda1520++;
        break;
        case -321:  num_kbar0++;
        break;          
	case 211:  num_delta++;
        break;

        
        case -211:  anti_num_lamda1520++;
        break;
        case 313:  num_k0++;
        break;
        case -2224:  anti_num_delta++;
        break; 
        default:
        break;
       }
   //  cout << "pdgCode = " << ptl0->GetPdgCode() << endl;
      switch (abs(ptl0->GetPdgCode()))
      {
         case 211:
            ptl0->Momentum(piMom);
       //     cout << "k-" << endl;
           //cout << "piMom PID is" << ptl0->GetPdgCode() << endl;
            // v00.SetXYZ(0,0,0);
            v00.SetXYZ(ptl0->Vx() * 1000., ptl0->Vy() * 1000., ptl0->Vz() * 1000.); // converted to μm
     //      cout<< v00.X()<<endl;
            break;
         case  321:
           if(!kMom.P()) {
               ptl0->Momentum(kMom);
              if(ptl0->GetPdgCode() >0) KPlus_num++; 
            if(ptl0->GetPdgCode() <0) KMinus_num++;
           }
          // cout << "flag 1" << endl;    
           else { 
                   ptl0->Momentum(pMom); 
            //       if(ptl0->GetPdgCode() >0) KPlus_num++; 
              //     if(ptl0->GetPdgCode() <0) KMinus_num++;
               }
                   //cout << "pi+PID = " << ptl0->GetPdgCode() << endl;
            break;
         default:
            break;
      }
   }
 //  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
   daughters.Clear();

   fill(centrality_low, kf, b, weight, kMom, piMom, pMom, v00);
}

void fill(int const centrality_low, int const kf, TLorentzVector* b, double weight, TLorentzVector const& kMom, TLorentzVector const& piMom, TLorentzVector const& pMom, TVector3 v00)
{
   // int const centrality = floor(nCentHftRatio * gRandom->Rndm());
   //if(kMom.Perp()<0.5 || piMom.Perp()<0.5 || pMom.Perp()<0.5) return;
   // if(fabs(kMom.PseudoRapidity())>1 || fabs(piMom.PseudoRapidity())>1 || fabs(pMom.PseudoRapidity())>1) return;
   //int const centrality = floor(nCentHftRatio * gRandom->Rndm());
  // int const centrality = 5;
  // cout << "centality=" << centrality << endl;

   TVector3 const vertex = getVertex();
   // smear primary vertex
   // float const sigmaVertex = sigmaVertexCent[cent];
   // TVector3 const vertex(gRandom->Gaus(0, sigmaVertex), gRandom->Gaus(0, sigmaVertex), gRandom->Gaus(0, sigmaVertex));

   v00 += vertex;

   // smear momentum
   TLorentzVector const kRMom  = smearMom(kMom,  fKaonMomResolution);
   TLorentzVector const piRMom = smearMom(piMom, fPionMomResolution);
   TLorentzVector const pRMom = smearMom(pMom, fKaonMomResolution);

   // smear position
   // TVector3 const kRPos  = smearPosData(1, vertex.z(), centrality, kRMom,  v00);
   // TVector3 const piRPos = smearPosData(0, vertex.z(), centrality, piRMom, v00);
   // TVector3 const pRPos = smearPosData(2, vertex.z(), centrality, pRMom, v00);
   TVector3 const kRPos  = smearPosData(1, vertex.z(),  kRMom,  v00);
   TVector3 const piRPos = smearPosData(0, vertex.z(),  piRMom, v00);
   TVector3 const pRPos = smearPosData(1, vertex.z(),  pRMom, v00);
   // TVector3 const kRPos = smearPos(kMom, kRMom, v00);
   // TVector3 const piRPos = smearPos(piMom, piRMom, v00);
   // TVector3 const pRPos = smearPos(pMom, pRMom, v00);

   // reconstruct
   TLorentzVector const rMom = kRMom + piRMom + pRMom;
   TLorentzVector const secMom  = kRMom + pRMom; //  phi -> K + K
   float const kDca = dca(kMom.Vect(), v00, vertex);
   float const piDca = dca(piMom.Vect(), v00, vertex);
   float const pDca = dca(pMom.Vect(), v00, vertex);
   float const kRDca = dca(kRMom.Vect(), kRPos, vertex);
   float const kRSDca = dcaSigned(kRMom.Vect(), kRPos, vertex);
   float const kRDcaXY = dcaXY(kRMom.Vect(), kRPos, vertex);
   float const kRDcaZ = dcaZ(kRMom.Vect(), kRPos, vertex);
   float const piRDca = dca(piRMom.Vect(), piRPos, vertex);
   float const piRSDca = dcaSigned(piRMom.Vect(), piRPos, vertex);
   float const piRDcaXY = dcaXY(piRMom.Vect(), piRPos, vertex);
   float const piRDcaZ = dcaZ(piRMom.Vect(), piRPos, vertex);
   float const pRDca = dca(pRMom.Vect(), pRPos, vertex);
   float const pRSDca = dcaSigned(pRMom.Vect(), pRPos, vertex);
   float const pRDcaXY = dcaXY(pRMom.Vect(), pRPos, vertex);
   float const pRDcaZ = dcaZ(pRMom.Vect(), pRPos, vertex);

   TVector3 v12, v23, v31, v0;
   float const dca12 = dca1To2(kRMom.Vect(), kRPos, piRMom.Vect(), piRPos, v12);
   float const dca23 = dca1To2(piRMom.Vect(), piRPos, pRMom.Vect(), pRPos, v23);
   float const dca31 = dca1To2(pRMom.Vect(), pRPos, kRMom.Vect(), kRPos, v31);
   float dcaDaughters = dca12 > dca31 ? dca12 : dca31;
   dcaDaughters = dcaDaughters > dca23 ? dcaDaughters : dca23;
   v0 = (v12 + v23 + v31) * 0.3333333;
   float const decayLength = (v0 - vertex).Mag();
   float const dcaLcToPv = dca(rMom.Vect(), v0, vertex);
   float const cosTheta = (v0 - vertex).Unit().Dot(rMom.Vect().Unit());
   float const anglekpi = kRMom.Vect().Angle(piRMom.Vect());
   
   /* costheta_star_pik --> For k*bar0 -> pi + k channel
  TLorentzVector pionMom   = p1RMom;
  TLorentzVector kaonMom   = p2RMom;
  kaonMom.Boost(-1*secMom.BoostVector());
  pionMom.Boost(-1*secMom.BoostVector());
  Float_t const costheta_star_pik = kaonMom.Vect().Unit().Dot(pionMom.Vect().Unit());
  // CosTheta_star_K*bar0p ---> For Lc+ -> p + K*bar0 decay channel
  TLorentzVector kstar_bar0Mom   = secMom;
  TLorentzVector protonMom   = p3RMom;
  kstar_bar0Mom.Boost(-1*rMom.BoostVector());
  protonMom.Boost(-1*rMom.BoostVector());
  Float_t const CosTheta_star_kbar0p = kstar_bar0Mom.Vect().Unit().Dot(protonMom.Vect().Unit());
  */

   TLorentzVector kRMomRest = kRMom;
   TVector3 beta;
   beta.SetMagThetaPhi(rMom.Beta(), rMom.Theta(), rMom.Phi());
   kRMomRest.Boost(-beta);
   float const cosThetaStar = rMom.Vect().Unit().Dot(kRMomRest.Vect().Unit());

   int const charge = kf > 0 ? 1 : -1;

  bool const piHft = matchHft(0, vertex.z(),  piRMom);
  bool const kHft = matchHft(1, vertex.z(),  kRMom);
  bool const pHft = matchHft(1, vertex.z(),  pRMom);

  float const piTpc = tpcReconstructed(0, charge, piRMom);
  float const kTpc = tpcReconstructed(1, 1, kRMom);
  float const pTpc = tpcReconstructed(1, -1, pRMom);
/*  cout << "piHft = " << piHft << endl;
  cout << "kHft = " << kHft << endl;
  cout << "pHft = " << pHft << endl;
  cout << "piTpc = " << piTpc << endl;
  cout << "kTpc = " << kTpc << endl;
  cout << "pTpc = " << pTpc << endl;*/
  float RDca12 = TMath::Min(kRDca/1.0e4,pRDca/1.0e4);
  float massDiff = fabs(secMom.M() - 1.019);
  float Phimass = secMom.M();
  float massDiff2 = fabs(secMom.M() - 1.019445);
   float rPt12 = TMath::Min(kRMom.Perp(),pRMom.Perp());
  float piontpcpid = fpionNsig_eff->Eval(piRMom.Perp());
  float kaon1tpcpid = fkaonNsig_eff->Eval(kRMom.Perp());
    float kaon2tpcpid = fkaonNsig_eff->Eval(pRMom.Perp());
    float piontofpid = fpionNsigTof_eff->Eval(piRMom.Perp());
    float kaon1tofpid = fkaonNsigTof_eff->Eval(kRMom.Perp());
   float kaon2tofpid = fkaonNsigTof_eff->Eval(pRMom.Perp());
 float piontofmatch = ftofpi[centrality_low]->Eval(piRMom.Perp());
       float kaon1tofmatch = ftofk[centrality_low]->Eval(kRMom.Perp());
float kaon2tofmatch = ftofk[centrality_low]->Eval(pRMom.Perp());

float PIDweight =  (piontofmatch * piontofpid * piontpcpid + (1 - piontofmatch) * piontpcpid)*(kaon1tofmatch * kaon1tofpid * kaon1tpcpid + (1 - kaon1tofmatch) * kaon1tpcpid)*(kaon2tofmatch * kaon2tofpid *kaon2tpcpid + (1 - kaon2tofmatch) * kaon2tpcpid);
// save
   float arr[120];
   int iArr = 0;
   // Event info 
   arr[iArr++] = centrality_low;
   arr[iArr++] = vertex.X();
   arr[iArr++] = vertex.Y();
   arr[iArr++] = vertex.Z();
   arr[iArr++] = getVzIndexDca(vertex.Z());
   arr[iArr++] = RDca12;
   arr[iArr++] = massDiff;
   arr[iArr++] = Phimass;
   arr[iArr++] = massDiff2;
   arr[iArr++] = rPt12;
   arr[iArr++] = secMom.Perp();
   arr[iArr++] = secMom.M();
   // MC Lc
   arr[iArr++] = kf;
   arr[iArr++] = weight;
   arr[iArr++] = PIDweight;
   arr[iArr++] = b->M();
   arr[iArr++] = b->Perp();
   arr[iArr++] = b->PseudoRapidity();
   arr[iArr++] = b->Rapidity();
   arr[iArr++] = b->Phi();
   arr[iArr++] = v00.X();
   arr[iArr++] = v00.Y();
   arr[iArr++] = v00.Z();
   //RC Lc
   arr[iArr++] = rMom.M();
   arr[iArr++] = rMom.Perp();
   arr[iArr++] = rMom.PseudoRapidity();
   arr[iArr++] = rMom.Rapidity();
   arr[iArr++] = rMom.Phi();
   arr[iArr++] = v0.X();
   arr[iArr++] = v0.Y();
   arr[iArr++] = v0.Z();
   arr[iArr++] = v12.X();
   arr[iArr++] = v12.Y();
   arr[iArr++] = v12.Z();
   arr[iArr++] = v23.X();
   arr[iArr++] = v23.Y();
   arr[iArr++] = v23.Z();
   arr[iArr++] = v31.X();
   arr[iArr++] = v31.Y();
   arr[iArr++] = v31.Z();

   arr[iArr++] = dcaDaughters/1.0e4;
   arr[iArr++] = decayLength/1.0e4;
   arr[iArr++] = dcaLcToPv/1.0e4;
   arr[iArr++] = cosTheta;
   arr[iArr++] = anglekpi;
   arr[iArr++] = cosThetaStar;
   arr[iArr++] = dca12/1.0e4;
   arr[iArr++] = dca23/1.0e4;
   arr[iArr++] = dca31/1.0e4;
  //kaon
   arr[iArr++] = kMom.M();
   arr[iArr++] = kMom.Perp();
   arr[iArr++] = kMom.PseudoRapidity();
   arr[iArr++] = kMom.Rapidity();
   arr[iArr++] = kMom.Phi();
   arr[iArr++] = kDca/1.0e4;

   arr[iArr++] = kRMom.M();
   arr[iArr++] = kRMom.Perp();
   arr[iArr++] = kRMom.PseudoRapidity();
   arr[iArr++] = kRMom.Rapidity();
   arr[iArr++] = kRMom.Phi();
   arr[iArr++] = kRPos.X();
   arr[iArr++] = kRPos.Y();
   arr[iArr++] = kRPos.Z();
   arr[iArr++] = kRDca/1.0e4;
   arr[iArr++] = kRSDca;
   arr[iArr++] = kRDcaXY;
   arr[iArr++] = kRDcaZ;
   arr[iArr++] = getEtaIndexDca(kRMom.PseudoRapidity());
   arr[iArr++] = getPtIndexDca(kRMom.Perp());
  // arr[iArr++] = tpcReconstructed(1, -1 * charge, centrality, kRMom);
    arr[iArr++] = kTpc;  
  //pion
   arr[iArr++] = piMom.M();
   arr[iArr++] = piMom.Perp();
   arr[iArr++] = piMom.PseudoRapidity();
   arr[iArr++] = piMom.Rapidity();
   arr[iArr++] = piMom.Phi();
   arr[iArr++] = piDca/1.0e4;

   arr[iArr++] = piRMom.M();
   arr[iArr++] = piRMom.Perp();
   arr[iArr++] = piRMom.PseudoRapidity();
   arr[iArr++] = piRMom.Rapidity();
   arr[iArr++] = piRMom.Phi();
   arr[iArr++] = piRPos.X();
   arr[iArr++] = piRPos.Y();
   arr[iArr++] = piRPos.Z();
   arr[iArr++] = piRDca/1.0e4;
   arr[iArr++] = piRSDca;
   arr[iArr++] = piRDcaXY;
   arr[iArr++] = piRDcaZ;
   arr[iArr++] = getEtaIndexDca(piRMom.PseudoRapidity());
   arr[iArr++] = getPtIndexDca(piRMom.Perp());
   //arr[iArr++] = tpcReconstructed(0, charge, centrality, piRMom);
   arr[iArr++] = piTpc; 
//proton
   arr[iArr++] = pMom.M();
   arr[iArr++] = pMom.Perp();
   arr[iArr++] = pMom.PseudoRapidity();
   arr[iArr++] = pMom.Rapidity();
   arr[iArr++] = pMom.Phi();
   arr[iArr++] = pDca/1.0e4;

   arr[iArr++] = pRMom.M();
   arr[iArr++] = pRMom.Perp();
   arr[iArr++] = pRMom.PseudoRapidity();
   arr[iArr++] = pRMom.Rapidity();
   arr[iArr++] = pRMom.Phi();
   arr[iArr++] = pRPos.X();
   arr[iArr++] = pRPos.Y();
   arr[iArr++] = pRPos.Z();
   arr[iArr++] = pRDca/1.0e4;
   arr[iArr++] = pRSDca;
   arr[iArr++] = pRDcaXY;
   arr[iArr++] = pRDcaZ;
   arr[iArr++] = getEtaIndexDca(pRMom.PseudoRapidity());
   arr[iArr++] = getPtIndexDca(pRMom.Perp());
  // arr[iArr++] = tpcReconstructed(2, charge, centrality, pRMom);
   arr[iArr++] = pTpc;
  /* arr[iArr++] = matchHft(1, vertex.z(), centrality, kRMom);
   arr[iArr++] = matchHft(0, vertex.z(), centrality, piRMom);
   arr[iArr++] = matchHft(2, vertex.z(), centrality, pRMom);
   */
   arr[iArr++] = kHft;
   arr[iArr++] = piHft;
   arr[iArr++] = pHft;
   arr[iArr++] = flag;   
 //  if(piRMom.Perp()<0.5 || kRMom.Perp()<0.5 || pRMom.Perp()<0.5) return;
   //if(fabs(kRMom.PseudoRapidity())>1 || fabs(piRMom.PseudoRapidity())>1 || fabs(pRMom.PseudoRapidity())>1) return;
  
//cout << "iArr = " << iArr << endl; 
  // if(piHft&&kHft&&pHft&&piTpc&&kTpc&&pTpc)
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
   int const iVzIndex = getVzIndexDca(vz);
   // int const iPhiIndex = getPhiIndexDca(rMom.Phi());
   int const iPtIndex = getPtIndexDca(rMom.Perp());

   double sigmaPosZ = 0;
   double sigmaPosXY = 0;

   // if (cent == 8) cent = 7;
   // All the centrality position smear was based on 0-10% centrality input
   // changed to 0-80%

   h2Dca[iParticleIndex][iEtaIndex][iVzIndex][iPtIndex]->GetRandom2(sigmaPosXY, sigmaPosZ);
   sigmaPosZ *= 1.e4;
   sigmaPosXY *= 1.e4;
   /*if (h1DcaZ1[iParticleIndex][iEtaIndex][iVzIndex][cent][iPtIndex]->ComputeIntegral())
   {
     do sigmaPosZ = h1DcaZ1[iParticleIndex][iEtaIndex][iVzIndex][cent][iPtIndex]->GetRandom() * 1e4;
     while (fabs(sigmaPosZ) > 1.e3);
   }

   if (h1DcaXY1[iParticleIndex][iEtaIndex][iVzIndex][cent][iPtIndex]->ComputeIntegral())
   {
     do sigmaPosXY = h1DcaXY1[iParticleIndex][iEtaIndex][iVzIndex][cent][iPtIndex]->GetRandom() * 1e4;
     while (fabs(sigmaPosXY) > 1.e3);
   }
   */

   TVector3 newPos(pos);
   newPos.SetZ(0);
   TVector3 momPerp(-rMom.Vect().Y(), rMom.Vect().X(), 0.0);
   newPos -= momPerp.Unit() * sigmaPosXY;

   return TVector3(newPos.X(), newPos.Y(), pos.Z() + sigmaPosZ);
}

TVector3 getVertex()
{
   double rdmVz;

   if (h1Vz->GetEntries() == 0) rdmVz = 0.;
   else
   {
      do rdmVz = h1Vz->GetRandom() * 1e4;
      while (fabs(rdmVz) > gVzCut);
   }

   return TVector3(0., 0., rdmVz);
}

float tpcReconstructed(int iParticleIndex, float charge, TLorentzVector const& mom)
{
   TH1D* h = NULL;

   if (iParticleIndex == 0)
   {
      if (charge > 0) h = hTpcPiPlus;
      else h = hTpcPiMinus;
   }
   else if(iParticleIndex == 1)
   {
      if (charge > 0) h = hTpcKPlus;
      else h = hTpcKMinus;
   }
 /*  else 
   {
      if (charge > 0) h = hTpcProton;
      else h = hTpcAntiProton;
   }*/

   // int const bin = h->FindBin(mom.Perp());
   int bin = h->FindBin(mom.Perp());
   // if (iParticleIndex == 2 && mom.Perp() >= 5.0) bin = h->FindBin(4.5); //for proton and antiproton, pT range is 5Gev
   return h->GetBinContent(bin);
   
   //return gRandom->Rndm() < h->GetBinContent(bin);
}

bool matchHft(int const iParticleIndex, double const vz, TLorentzVector const& mom)
{
   int const iEtaIndex = getEtaIndexHftRatio(mom.PseudoRapidity());
   int const iVzIndex = getVzIndexHftRatio(vz);
   int const iPhiIndex = getPhiIndexHftRatio(mom.Phi());

   int const bin = hHftRatio1[iParticleIndex][iEtaIndex][iVzIndex][iPhiIndex]->FindBin(mom.Perp());
   return gRandom->Rndm() < hHftRatio1[iParticleIndex][iEtaIndex][iVzIndex][iPhiIndex]->GetBinContent(bin);
}
//___________
void bookObjects(TString outFileName, int const centrality_low, int const centrality_high)
{
   cout << "Loading input momentum resolution ..." << endl;
   TFile f("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/Momentum_resolution_SL16_requireHFT.root");
   fPionMomResolution = (TF1*)f.Get(Form("fPion_2014_%i", centrality_low));
   fKaonMomResolution = (TF1*)f.Get(Form("fKaon_2014_%i", centrality_low));
 //  fProtonMomResolution = (TF1*)f.Get("fProton")->Clone("fProton");
//  fPionMomResolution = (TF1*)f.Get("fPion")->Clone("fPion");
  //fKaonMomResolution = (TF1*)f.Get("fKaon")->Clone("fKaon");
   f.Close();
   cout << "Loading PID efficiency ..." << endl; 
   TFile* fpionPid = new TFile("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/pion_PidEff_FromXiaolong.root");
      fpionNsig_eff = (TF1*)fpionPid->Get("fNsig_eff")->Clone("fpionNsig_eff");
      fpionNsigTof_eff = (TF1*)fpionPid->Get("fNsigTof_eff")->Clone("fpionNsigTof_eff");
      TFile* fkaonPid = new TFile("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/kaon_PidEff_FromXiaolong.root");
         fkaonNsig_eff = (TF1*)fkaonPid->Get("fNsig_eff")->Clone("fkaonNsig_eff");
         fkaonNsigTof_eff = (TF1*)fkaonPid->Get("fNsigTof_eff")->Clone("fkaonNsigTof_eff");
  fpionPid->Close();
  fkaonPid->Close();
 
  cout << "Loading tof matching efficiency ..." << endl;
  TFile* fTofMatchFile = new TFile("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/tofMatch_fit_Run14.root");
      for (int i = 0; i < 9; i++)
           {
                   ftofpi[i] = (TF1*)fTofMatchFile->Get(Form("funpi_%d", i))->Clone(Form("funpi_%d", i));
                              ftofk[i] = (TF1*)fTofMatchFile->Get(Form("funk_%d", i))->Clone(Form("funk_%d", i));
                          ftofp[i] = (TF1*)fTofMatchFile->Get(Form("funp_%d", i))->Clone(Form("funp_%d", i));
                         }
                       
  cout << "Loading input spectra ..." << endl;
   TFile fPP("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/pp200_spectra.root");
   fWeightFunction = (TF1*)fPP.Get("run12/f1Levy")->Clone("f1Levy");
   fPP.Close();

   TFile fVertex("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/Vz_Cent.root");

   for (int iCent = centrality_low; iCent < centrality_high; ++iCent)
   {
      h1Vz      = (TH1D*)(fVertex.Get(Form("mh1Vz_%i", iCent)));
      h1Vz->SetDirectory(0);
   }

   fVertex.Close();

/*   std::cout << "Loading HFT ratios Correction factor for inclusive and primary..." << std::endl;
   TFile fHftRatioCorrect("HFT_Ratio_Correction_Hijing_QM.root");
   for (int iParticle = 0; iParticle < nParticles; ++iParticle)
   {
      for (int iCent = 0; iCent < 1 ; ++iCent)
      {
         // HFT ratio
         for (int iEta = 0; iEta < nEtasHftRatio; ++iEta)
         {
            for (int iVz = 0; iVz < nVzsHftRatio; ++iVz)
            {
               for (int iPhi = 0; iPhi < nPhisHftRatio; ++iPhi)
               {
                  hHftRatioCorrect[iParticle][iEta][iVz][iPhi]  = (TH1D*)(fHftRatioCorrect.Get(Form("mhHFTRatio_%i_%i_%i_%i_%i", iParticle, iEta, iVz, iPhi, iCent)));
                  hHftRatioCorrect[iParticle][iEta][iVz][iPhi] ->SetDirectory(0);
               }
            }
         }
      }
   }
   fHftRatioCorrect.Close();*/

   cout << "Loading input HFT ratios and DCA ..." << endl;
   TFile fHftRatio1("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/HFT_Ratio_VsPt_Centrality_Eta_Phi_Vz_Zdcx_16Nov2.root");
   TFile fDca1("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/2DProjection_simCent_NoBinWidth_3D_Dca_VsPt_Centrality_Eta_Phi_Vz_Zdcx_16Nov2.root");

   for (int iParticle = 0; iParticle < nParticles; ++iParticle)
   {
      for (int iCent = centrality_low; iCent < centrality_high; ++iCent)
      {
         // HFT ratio
         for (int iEta = 0; iEta < nEtasHftRatio; ++iEta)
         {
            for (int iVz = 0; iVz < nVzsHftRatio; ++iVz)
            {
               for (int iPhi = 0; iPhi < nPhisHftRatio; ++iPhi)
               {
                  hHftRatio1[iParticle][iEta][iVz][iPhi] = (TH1F*)(fHftRatio1.Get(Form("mh1HFT1PtCentPartEtaVzPhiRatio_%i_%i_%i_%i_%i", iParticle, iEta, iVz, iPhi, iCent)));
                  hHftRatio1[iParticle][iEta][iVz][iPhi]->SetDirectory(0);
               }
            }
         }
      }
      cout << "Finished loading HFT Ratio: " <<  endl;

      for (int iCent = centrality_low; iCent < centrality_high; ++iCent)// only load one centrality
      {
         // DCA
         for (int iEta = 0; iEta < nEtasDca; ++iEta)
         {
            for (int iVz = 0; iVz < nVzsDca; ++iVz)
            {
               // for (int iPhi = 0; iPhi < nPhisDca; ++iPhi)
               for (int iPt = 0; iPt < nPtBinsDca; ++iPt)
               {
                  h2Dca[iParticle][iEta][iVz][iPt] = (TH2F*)((fDca1.Get(Form("mh2DcaPtCentPartEtaVzPhi_%i_%i_%i_%i_%i", iParticle, iEta, iVz, iCent, iPt))));
                  h2Dca[iParticle][iEta][iVz][iPt]->SetDirectory(0);
                  // h2Dca[iParticle][iEta][iVz][iPt] = (TH2F*)((fDca1.Get(Form("mh2DcaPtCentPartEtaVzPhi_%i_%i_%i_%i", iParticle, iEta, iVz, iPt))));
                  // h2Dca[iParticle][iEta][iVz][iPt]->SetDirectory(0);
               }
            }
         }
       //  cout << "Finished loading centrality: " << iCent << endl;
      }
   }
   cout << "Finished loading Dca: " <<  endl;

   fHftRatio1.Close();
   fDca1.Close();

   cout << " Loading TPC tracking efficiencies " << endl;

   TFile fTpcPiPlus("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/Eff_PionPlus_embedding.root");
   TFile fTpcPiMinus("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/Eff_PionMinus_embedding.root");
   TFile fTpcKPlus("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/Eff_KaonPlus_embedding.root");
   TFile fTpcKMinus("/star/u/fuchuan/data02/Ds/Ds_code_GPC/2014/fastsim/runfastsim/Input_FastSimu/Eff_KaonMinus_embedding.root");
  // TFile fTpcProton("Eff_Proton_embedding.root");
  // TFile fTpcAntiProton("Eff_AntiProton_embedding.root");

   for (int iCent = centrality_low; iCent < centrality_high; ++iCent)
   {
      hTpcPiPlus = (TH1D*)fTpcPiPlus.Get(Form("h1Ratiocent_%i", iCent));
      hTpcPiPlus->SetDirectory(0);
      hTpcPiMinus = (TH1D*)fTpcPiMinus.Get(Form("h1Ratiocent_%i", iCent));
      hTpcPiMinus->SetDirectory(0);
      hTpcKPlus = (TH1D*)fTpcKPlus.Get(Form("h1Ratiocent_%i", iCent));
      hTpcKPlus->SetDirectory(0);
      hTpcKMinus = (TH1D*)fTpcKMinus.Get(Form("h1Ratiocent_%i", iCent));
      hTpcKMinus->SetDirectory(0);
     /* hTpcProton = (TH1D*)fTpcProton.Get(Form("h1Ratiocent_%i", iCent));
      hTpcProton->SetDirectory(0);
      hTpcAntiProton = (TH1D*)fTpcAntiProton.Get(Form("h1Ratiocent_%i", iCent));
      hTpcAntiProton->SetDirectory(0);*/
   }

   fTpcPiPlus.Close();
   fTpcPiMinus.Close();
   fTpcKPlus.Close();
   fTpcKMinus.Close();
  // fTpcProton.Close();
  // fTpcAntiProton.Close();

   cout << "Done with loading all files ..." << endl;

   result = new TFile(outFileName.Data(), "recreate");
   result->SetCompressionLevel(1);
   result->cd();

   int BufSize = (int)pow(2., 16.);
   // int Split = 1;
   nt = new TNtuple("nt", "", "cent:vx:vy:vz:vzIdx:RDca12:massDiff:Phimass:massDiff2:rPt12:rPt_Phi:Mass_Phi:"
                    "pid:w:PIDweight:m:pt:eta:y:phi:v00x:v00y:v00z:" // MC Lc+
                    "rM:rPt:rEta:rY:rPhi:rV0x:rV0y:rV0z:rV12x:rV12y:rV12z:rV23x:rV23y:rV23z:rV31x:rV31y:rV31z:" // Rc Lc+
                    "dcaDaughters:decayLength:dcaLcToPv:cosTheta:anglekpi:cosThetaStar:Dcakpi:Dcapip:Dcapk:" // Rc pair
                    "kM:kPt:kEta:kY:kPhi:kDca:" // MC Kaon
                    "kRM:rPtk1:kREta:kRY:kRPhi:kRV00x:kRV00y:kRV00z:k1RDca:kRSDca:kRDcaXY:kRDcaZ:kEtaIdx:kPtIdx:kTpc:" // Rc Kaon
                    "piM:piPt:piEta:piY:piPhi:piDca:" // MC Pion
                    "piRM:rPtpi:piREta:piRY:piRPhi:piRV00x:piRV00y:piRV00z:piRDca:piRSDca:piRDcaXY:piRDcaZ:piEtaIdx:piPtIdx:piTpc:" // Rc Pion
                    "pM:pPt:pEta:pY:pPhi:pDca:" // MC Proton
                    "pRM:rPtk2:pREta:pRY:pRPhi:pRV00x:pRV00y:pRV00z:k2RDca:pRSDca:pRDcaXY:pRDcaZ:pEtaIdx:pPtIdx:pTpc:" // Rc Proton
                    "kHft:piHft:pHft:flag", BufSize);
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
/*void initEvtGen()
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
   //starEvtGenDecayer = new StarEvtGenDecayer(myGenerator);
   // starEvtGenDecayer->SetDecayTable("Lc.Mypythia.DEC");
  // starEvtGenDecayer->SetDecayTable("Lc.MypythiaCombine.DEC");
   // starEvtGenDecayer->SetDebug(1);
}*/
