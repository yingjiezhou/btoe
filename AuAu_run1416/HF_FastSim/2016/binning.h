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

const Int_t nParticles = 3;
const Int_t nCentHftRatio = 9;

TF1* fKaonMomResolution = NULL;
TF1* fPionMomResolution = NULL;
TF1* fProtonMomResolution = NULL;

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

TH1D* h1Vz[nCentHftRatio];

TH1D* hHftRatioCorrect[nParticles][nEtasHftRatio][nVzsHftRatio][nPhisHftRatio][1];
TH1F* hHftRatio1[nParticles][nEtasHftRatio][nVzsHftRatio][nPhisHftRatio][nCentHftRatio];
int const nCentDca = 9;
TH2F* h2Dca[nParticles][nEtasDca][nVzsDca][nCentDca][nPtBinsDca];

TH1D* hTpcPiPlus[nCentHftRatio];
TH1D* hTpcPiMinus[nCentHftRatio];
TH1D* hTpcKPlus[nCentHftRatio];
TH1D* hTpcKMinus[nCentHftRatio];
TH1D* hTpcProton[nCentHftRatio];
TH1D* hTpcAntiProton[nCentHftRatio];

//___________
void bookObjects()
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
      h1Vz[ii]      = (TH1D*)(fVertex.Get(Form("mh1Vz_%i", ii)));
      h1Vz[ii]->SetDirectory(0);
   }

   fVertex.Close();

   cout << "Loading input HFT ratios and DCA ..." << endl;
   TFile fHftRatio1("Lc_HFT.root");
   TFile fDca1("Lc_2DProjection.root");

   for (int iParticle = 0; iParticle < nParticles; ++iParticle)
   {
      for (int iCent = 0; iCent < nCentHftRatio; ++iCent)
      {
         // HFT ratio
         for (int iEta = 0; iEta < nEtasHftRatio; ++iEta)
         {
            for (int iVz = 0; iVz < nVzsHftRatio; ++iVz)
            {
               for (int iPhi = 0; iPhi < nPhisHftRatio; ++iPhi)
               {
                  hHftRatio1[iParticle][iEta][iVz][iPhi][iCent] = (TH1F*)(fHftRatio1.Get(Form("mh1HFT1PtCentPartEtaVzPhiRatio_%i_%i_%i_%i_%i", iParticle, iEta, iVz, iPhi, iCent)));
                  hHftRatio1[iParticle][iEta][iVz][iPhi][iCent]->SetDirectory(0);
               }
            }
         }
      }
      cout << "Finished loading HFT Ratio: " <<  endl;

      for (int iCent = 0; iCent < nCentDca; ++iCent)// only load one centrality when the memory is an issue
      {
         // DCA
         for (int iEta = 0; iEta < nEtasDca; ++iEta)
         {
            for (int iVz = 0; iVz < nVzsDca; ++iVz)
            {
               // for (int iPhi = 0; iPhi < nPhisDca; ++iPhi)// no phi differencial
               for (int iPt = 0; iPt < nPtBinsDca; ++iPt)
               {
                  h2Dca[iParticle][iEta][iVz][iCent][iPt] = (TH2F*)((fDca1.Get(Form("mh2DcaPtCentPartEtaVzPhi_%i_%i_%i_%i_%i", iParticle, iEta, iVz, iCent, iPt))));
                  h2Dca[iParticle][iEta][iVz][iCent][iPt]->SetDirectory(0);
               }
            }
         }
         cout << "Finished loading centrality: " << iCent << endl;
      }
   }
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

   fTpcPiPlus.Close();
   fTpcPiMinus.Close();
   fTpcKPlus.Close();
   fTpcKMinus.Close();
   fTpcProton.Close();
   fTpcAntiProton.Close();

   cout << "Done with loading all files ..." << endl;

}
