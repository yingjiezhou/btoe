#ifndef CUTS_H
#define CUTS_H

#include "StCuts.h"

/* **************************************************
 *  Cuts namespace.
 *
 *  Authors:  **Mustafa Mustafa (mmustafa@lbl.gov)
 *
 *  **Code Maintainer
 *
 * **************************************************
 */

#include <array>

namespace cuts
{
// Mass
const Float_t  piMass       = 0.13957;
const Float_t  kMass        = 0.493677;
const Float_t  phiMass      = 1.019461;
const Float_t  kstarMass    = 0.89581;
const Float_t  protonmass   = 0.938;
const Float_t  Pi           = 3.14159;
const Float_t  twoPi        = 6.28318;

// path to lists of triggers prescales
// lists are obtained from http://www.star.bnl.gov/protected/common/common2014/trigger2014/plots_au200gev/
std::string const prescalesFilesDirectoryName = "./run14AuAu200GeVPrescales";

//event
int const centrality = 3; // StRefMultCorr::getCentralityBin9() < centrality; 0-3 bins are for 40-80%
std::array<unsigned int, 6> const triggers = {
   520001,
                520011,
                520021,
                520031,
                520041,
                520051
 
};    // vpdmb-5-p-nobsmd

/* Event Leve Cuts  */
float const vz = 6.0;// cm.
float const vzVpdVz = 3.0; // 3 cm.

// vertex refit track quality
float const vtxDca = 3.0;
size_t const vtxNumberOfFitPoints = 20;

//Signal Track Pre-Selection
int   const nHitsFit   = 20;
bool  const requireHFT = true;
float const trkDca     = 0.0060; /* >70 um */
float const trkPt      = 0.2;	 /* >0.5 GeV */
float const eta        = 1.0;

//PID Cuts
float const nSigmaPion   = 3.0;
float const nSigmaKaon   = 2.0;
float const nSigmaProton = 3.0;

// tree kaonPion pair cuts
float const cosTheta     = 0.95;	   /* minimum cos(theta) */
float const dcaDaughters = 0.01; /* Maximum dca daughters */
float const secSigma     = 0.0300; /* Maximum secSigma */
float const decayLength  = 0.0120; /* Minimum decay Length */
float const minMass 	 = 1.8;	   /* Mass low */
float const maxMass 	 = 2.1;	   /* Mass high */
float const absEta       = 1.0;	   /* Eta cut */
float const absKKMass    = 0.015;   /* phi meson mass cuts */

/* TOF match eff cut */
const Float_t nSigmaCut    = 2.5;
const Float_t nSigCutTight = 0.1;

// histograms kaonPion pair cuts
int   const nPtBins = 5;
float const PtBinsEdge[nPtBins + 1] = {0., 1., 2., 3., 5., 15.}; //this is for optimaized cut
float const qaPt = 1.2;
float const qaNHitsFit = 20;
float const qaNSigmaKaon = 2.0;
float const qaRapidityCut = 1.0;
float const qaDcaV0ToPv[nPtBins] = {0.0061, 0.0049, 0.0038, 0.0038, 0.0040};
float const qaDecayLength[nPtBins] = {0.0145, 0.0181, 0.0212, 0.0247, 0.0259};
float const qaCosTheta[nPtBins] = {0.0000, 0.0000, 0.0000, 0.0000, 0.0000};//0.995
float const qaDcaDaughters[nPtBins] = {0.0084, 0.0066, 0.0057, 0.0050, 0.0060}; //0.0050;
float const qaKDca[nPtBins] = {0.0103, 0.0091, 0.0095, 0.0079, 0.0058};//0.008, // minimum
float const qaPDca[nPtBins] = {0.0110, 0.0111, 0.0086, 0.0081, 0.0062};//0.008
}
#endif
