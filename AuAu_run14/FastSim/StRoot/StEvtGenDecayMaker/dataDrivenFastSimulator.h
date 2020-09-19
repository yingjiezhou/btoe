/* *********************************************************************
 *  ROOT macro - Data Driven Monte Carlo Simulation for
 *  Includes Momentum Resolution, DCA, hft ration, TPC efficiency ...
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

#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TFile.h"
#include "TRandom3.h"


TLorentzVector smearMom(int iParticleIndex,TLorentzVector const& b);
TVector3 smearPos(TLorentzVector const& mom, TLorentzVector const& rMom, TVector3 const& pos);
TVector3 smearPosData(int iParticleIndex, double vz, int cent, TLorentzVector const& rMom, TVector3 const& pos);

float dca(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dca1To2(TVector3 const& p1, TVector3 const& pos1, TVector3 const& p2, TVector3 const& pos2, TVector3& v0);
float dcaSigned(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dcaXY(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);
float dcaZ(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex);

TVector3 getVertex(int centrality);
bool matchHft(int iParticleIndex, double vz, int cent, TLorentzVector const& mom);
bool reconstructD0(int const centrality, TLorentzVector const& mom);

int getPtIndexDca(double);
int getEtaIndexDca(double);
int getVzIndexDca(double);
int getPhiIndexDca(double);

int getPtIndexHftRatio(double);
int getEtaIndexHftRatio(double);
int getVzIndexHftRatio(double);
int getPhiIndexHftRatio(double);

TF1* fKaonMomResolution = NULL;
TF1* fPionMomResolution = NULL;
const Int_t nParticles = 2;
const Int_t nCentHftRatio = 9;

// HFT ratio binning
const Int_t nEtasHftRatio = 10;
const Int_t nVzsHftRatio = 6;
const Int_t nPtBinsHftRatio = 50;
const Double_t EtaEdgeHftRatio[nEtasHftRatio + 1] =
{
   -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0
};
const Double_t VzEdgeHftRatio[nVzsHftRatio + 1] =
{
   -6.0e4, -4.0e4, -2.0e4, 0.0, 2.0e4, 4.0e4, 6.0e4
};
const Double_t ptEdgeHftRatio[nPtBinsHftRatio + 1] =
{
   0.2, 0.3, 0.4, 0.5, 0.6 , 0.7 , 0.8 , 0.9 ,
   1. , 1.1 , 1.2 , 1.3 , 1.4 , 1.5 , 1.6 , 1.7 , 1.8 , 1.9 ,
   2. , 2.2 , 2.4 , 2.6 , 2.8 , 3.0 , 3.2 , 3.4 , 3.6 , 3.8 ,
   4. , 4.2 , 4.4 , 4.6 , 4.8 , 5.0 , 5.2 , 5.4 , 5.6 , 5.8 ,
   6. , 6.5 , 7.0 , 7.5 , 8.0 , 8.5 , 9.0 , 9.5 , 10. , 10.5,
   11.0 , 11.5 , 12.0
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
float const VzEdgeDca[nVzsDca + 1] = {   -6.e4, -3.e4, 0, 3.e4, 6.e4};

int const nEtasDca = 5;
float const EtaEdgeDca[nEtasDca + 1] = { -1.0, -0.6, -0.2, 0.2, 0.6, 1.0};

const Int_t nPtBinsDca = 21;
const Double_t ptEdgeDca[nPtBinsDca + 1] =
{
   0.2, 0.3, 0.4, 0.5, 0.6,  0.7 , 0.8 , 0.9 ,
   1. , 1.25 , 1.5 , 1.75 , 2.  , 2.25 , 2.5 , 2.75 , 3.0 , 3.5,
   // 3. , 3.5 , 4.  , 4.5 , 5. , 6. , 8.0 , 10. , 12.0
   4.  , 4.5 , 5. , 12.0
};

TH1D* h1Vz[nCentHftRatio];

TH1D* hHftRatio1[nParticles][nEtasHftRatio][nVzsHftRatio][nPhisHftRatio][nCentHftRatio];

int const nCentDca = 9;
TH2D* h2Dca[nParticles][nEtasDca][nVzsDca][nCentDca][nPtBinsDca];

TH1D* hTpcPiPlus[nCentHftRatio];
TH1D* hTpcPiMinus[nCentHftRatio];
TH1D* hTpcKPlus[nCentHftRatio];
TH1D* hTpcKMinus[nCentHftRatio];

float const gVzCut = 6.0e4;
float const sigmaPos0 = 15.2;
float const pxlLayer1Thickness = 0.00486;

void loadHftRatio()
{
  std::cout << "Loading input HFT ratios ..." <<  std::endl;
  TFile fHftRatio1("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/HFT_Ratio_VsPt_Centrality_Eta_Phi_Vz_Zdcx_16Jun14.root");

  for (int iParticle = 0; iParticle < nParticles; ++iParticle)
  {
    for(int iCent = 0; iCent < nCentHftRatio; ++iCent)
    {
      // HFT ratio
      for (int iEta = 0; iEta < nEtasHftRatio; ++iEta)
      {
        for (int iVz = 0; iVz < nVzsHftRatio; ++iVz)
        {
          for(int iPhi = 0; iPhi < nPhisHftRatio; ++iPhi)
          {
            hHftRatio1[iParticle][iEta][iVz][iPhi][iCent] = (TH1D*)(fHftRatio1.Get(Form("mh1HFT1PtCentPartEtaVzPhiRatio_%i_%i_%i_%i_%i", iParticle, iEta, iVz, iPhi, iCent)));
            hHftRatio1[iParticle][iEta][iVz][iPhi][iCent]->SetDirectory(0);
          }
        }
      }
    }
  }

  fHftRatio1.Close();
  std::cout << "Done with loading all files ..." << std::endl;
}

void loadAllDistributions()
{
   std::cout << "Loading input momentum resolution ..." <<  std::endl;
   TFile f("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/momentum_resolution.root");
   fPionMomResolution = (TF1*)f.Get("fPion")->Clone("fPion");
   fKaonMomResolution = (TF1*)f.Get("fKaon")->Clone("fKaon");
   f.Close();

  TFile fVertex("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/Vz_Cent.root");

   for (int ii = 0; ii < nCentHftRatio; ++ii)
   {
      h1Vz[ii]      = (TH1D*)(fVertex.Get(Form("mh1Vz_%i", ii)));
      h1Vz[ii]->SetDirectory(0);
   }

   fVertex.Close();

   std::cout << "Loading input HFT ratios and DCA ..." <<  std::endl;
   TFile fHftRatio1("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/HFT_Ratio_VsPt_Centrality_Eta_Phi_Vz_Zdcx_16Jun14.root"); // HFT matched effi
   TFile fDca1("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/2DProjection_simCent_NoBinWidth_3D_Dca_VsPt_Centrality_Eta_Phi_Vz_Zdcx_16Jun14.root"); // DCA spatial resolution

   for (int iParticle = 0; iParticle < nParticles; ++iParticle)
   {
     for(int iCent = 0; iCent < nCentHftRatio; ++iCent)
     {
       // HFT ratio
       for (int iEta = 0; iEta < nEtasHftRatio; ++iEta)
       {
         for (int iVz = 0; iVz < nVzsHftRatio; ++iVz)
         {
           for(int iPhi = 0; iPhi < nPhisHftRatio; ++iPhi)
           {
             hHftRatio1[iParticle][iEta][iVz][iPhi][iCent] = (TH1D*)(fHftRatio1.Get(Form("mh1HFT1PtCentPartEtaVzPhiRatio_%i_%i_%i_%i_%i", iParticle, iEta, iVz, iPhi, iCent)));
             hHftRatio1[iParticle][iEta][iVz][iPhi][iCent]->SetDirectory(0);
           }
         }
       }
     }

     for(int iCent = 0; iCent < nCentDca; ++iCent)
     {
       // DCA
       for (int iEta = 0; iEta < nEtasDca; ++iEta)
       {
         for (int iVz = 0; iVz < nVzsDca; ++iVz)
         {
           // for(int iPhi = 0; iPhi < nPhisDca; ++iPhi)
           // {
           for (int iPt = 0; iPt < nPtBinsDca; ++iPt)
           {
             h2Dca[iParticle][iEta][iVz][iCent][iPt] = (TH2D*)((fDca1.Get(Form("mh2DcaPtCentPartEtaVzPhi_%i_%i_%i_%i_%i", iParticle, iEta, iVz, iCent, iPt))));
             h2Dca[iParticle][iEta][iVz][iCent][iPt]->SetDirectory(0);
           }
           // }
         }
       }
       // std::cout<<"Finished loading centrality: " << iCent << std::endl;
     }
   }

   fHftRatio1.Close();
   fDca1.Close();

   std::cout << " Loading TPC tracking efficiencies " << std::endl;

   TFile fTpcPiPlus("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/Eff_PionPlus_embedding_v2.root");
   TFile fTpcPiMinus("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/Eff_PionMinus_embedding_v2.root");
   TFile fTpcKPlus("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/Eff_KaonPlus_embedding_v2.root");
   TFile fTpcKMinus("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/Eff_KaonMinus_embedding_v2.root");

   for(int iCent = 0; iCent< nCentHftRatio; ++iCent)
   {
     hTpcPiPlus[iCent] = (TH1D*)fTpcPiPlus.Get(Form("h1Ratiocent_%i",iCent));
     hTpcPiPlus[iCent]->SetDirectory(0);
     hTpcPiMinus[iCent] = (TH1D*)fTpcPiMinus.Get(Form("h1Ratiocent_%i",iCent));
     hTpcPiMinus[iCent] ->SetDirectory(0);
     hTpcKPlus[iCent] = (TH1D*)fTpcKPlus.Get(Form("h1Ratiocent_%i",iCent));
     hTpcKPlus[iCent]->SetDirectory(0);
     hTpcKMinus[iCent] = (TH1D*)fTpcKMinus.Get(Form("h1Ratiocent_%i",iCent));
     hTpcKMinus[iCent]->SetDirectory(0);
   }

   fTpcPiPlus.Close();
   fTpcPiMinus.Close();
   fTpcKPlus.Close();
   fTpcKMinus.Close();

   std::cout << "Done with loading all files ..." << std::endl;
}

float dca(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex)
{
   TVector3 posDiff = pos - vertex;
   return fabs(p.Cross(posDiff.Cross(p)).Unit().Dot(posDiff));
}

float dcaSigned(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex)
{
  TVector3 posDiff = pos - vertex;
  float sign = posDiff.x()*p.y()-posDiff.y()*p.x() > 0 ? +1 : -1; 
 
  return sign*p.Cross(posDiff.Cross(p)).Unit().Dot(posDiff);
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
  float sign = posDiff.x()*p.y()-posDiff.y()*p.x() > 0 ? +1 : -1; 
  return sign*newP.Cross(posDiff.Cross(newP)).Unit().Dot(posDiff);
}

float dcaZ(TVector3 const& p, TVector3 const& pos, TVector3 const& vertex)
{
  TVector3 posDiff = pos - vertex;
  if(sin(p.Theta())==0) return 0;
  else return (-posDiff.x()*cos(p.Phi())-posDiff.y()*sin(p.Phi()))*cos(p.Theta())/sin(p.Theta())+posDiff.z();
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

TLorentzVector smearMom(int const iParticleIndex,TLorentzVector const& b)
{
   TF1* fMomResolution = iParticleIndex == 1 ? fKaonMomResolution : fPionMomResolution;

   float const pt = b.Perp(); // pt 只是用来做smear，后续只需要smear之后的sPt就好了
   float const sPt = gRandom->Gaus(pt, pt * fMomResolution->Eval(pt));
   //Double_t Gaus(Double_t mean = 0, Double_t sigma = 1)

   TLorentzVector sMom;
   sMom.SetXYZM(sPt * cos(b.Phi()), sPt * sin(b.Phi()), sPt * sinh(b.PseudoRapidity()), b.M());
   return sMom;
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

TVector3 smearPos(TLorentzVector const& mom, TLorentzVector const& rMom, TVector3 const& pos)
{
   float thetaMCS = 13.6 / mom.Beta() / rMom.P() / 1000 * sqrt(pxlLayer1Thickness / fabs(sin(mom.Theta())));
   float sigmaMCS = thetaMCS * 28000 / fabs(sin(mom.Theta()));
   float sigmaPos = sqrt(pow(sigmaMCS, 2) + pow(sigmaPos0, 2));

   return TVector3(gRandom->Gaus(pos.X(), sigmaPos), gRandom->Gaus(pos.Y(), sigmaPos), gRandom->Gaus(pos.Z(), sigmaPos));
}

TVector3 smearPosData(int const iParticleIndex, double const vz, int cent, TLorentzVector const& rMom, TVector3 const& pos)
{
   int const iEtaIndex = getEtaIndexDca(rMom.PseudoRapidity());
   int const iVzIndex = getVzIndexDca(vz);
   // int const iPhiIndex = getPhiIndexDca(rMom.Phi());
   int const iPtIndex = getPtIndexDca(rMom.Perp());

   double sigmaPosZ = 0;
   double sigmaPosXY = 0;

   // if(cent == 8) cent = 7;
   //All the centrality position smear was based on 0-10% centrality input
   // changed to 0-80%

   // h2Dca[iParticleIndex][iEtaIndex][iVzIndex][cent][iPtIndex]->GetRandom2(sigmaPosXY,sigmaPosZ);
   h2Dca[iParticleIndex][iEtaIndex][iVzIndex][cent][iPtIndex]->GetRandom2(sigmaPosXY,sigmaPosZ);// 只是简单的将smear 的DCA的分布去随机数。这个DCA根据不同的centrality,pt,eta,vz(这个vz是指还需要根据另外的一个vz分布随机将原点处的vz 进行加一个数，why)分类
   sigmaPosZ *= 1.e4;
   sigmaPosXY *= 1.e4;

   TVector3 newPos(pos);
   newPos.SetZ(0); // 设为0 是因为下面这个相减的操作，不要让其影响了z 的坐标
   TVector3 momPerp(-rMom.Vect().Y(), rMom.Vect().X(), 0.0);
   newPos -= momPerp.Unit() * sigmaPosXY;

   return TVector3(newPos.X(), newPos.Y(), pos.Z() + sigmaPosZ); //因为上面设为0 了，所以现在直接用原来的pos.z()
}

TVector3 getVertex(int const centrality)
{
   double rdmVz;

   if (h1Vz[centrality]->GetEntries() == 0) rdmVz = 0.;
   else
   {
     do rdmVz = h1Vz[centrality]->GetRandom() * 1e4;
     while ( fabs(rdmVz) > gVzCut);
   }

   return TVector3(0., 0., rdmVz);
}

bool tpcReconstructed(int iParticleIndex, float charge, int cent, TLorentzVector const& mom)
{
  TH1D* h = NULL;

  if(iParticleIndex == 0)
  {
    if(charge>0) h = hTpcPiPlus[cent];
    else h = hTpcPiMinus[cent];
  }
  else
  {
    if(charge>0) h = hTpcKPlus[cent];
    else h = hTpcKMinus[cent];
  }

  int const bin = h->FindBin(mom.Perp());

  return gRandom->Rndm() < h->GetBinContent(bin);
}

bool matchHft(int const iParticleIndex, double const vz, int const cent, float const pt, float const phi, float const eta)
{
   int const iEtaIndex = getEtaIndexHftRatio(eta);
   int const iVzIndex = getVzIndexHftRatio(vz);
   int const iPhiIndex = getPhiIndexHftRatio(phi);

   int const bin = hHftRatio1[iParticleIndex][iEtaIndex][iVzIndex][iPhiIndex][cent]->FindBin(pt);
   return gRandom->Rndm() < hHftRatio1[iParticleIndex][iEtaIndex][iVzIndex][iPhiIndex][cent]->GetBinContent(bin);
}

bool matchHft(int const iParticleIndex, double const vz, int const cent, TLorentzVector const& mom)
{
   return matchHft(iParticleIndex,vz,cent,mom.Perp(),mom.Phi(),mom.PseudoRapidity());
}
