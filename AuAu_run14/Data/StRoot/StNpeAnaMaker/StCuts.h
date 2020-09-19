/*
 *
 *
Wed Dec  2 09:31:44 PST 2015
by xiaozhi Bai xiaozhi@uic.edu
*
*
*/


#ifndef CUTS_H
#define CUTS_H
namespace cuts
{
  // Trigger cuts
  const Int_t adc0_HT1=256; //  
  const Int_t adc0_HT2=304; //  
  const Int_t adc0_HT3=416; //  

  const Int_t DSMadc_HT1=15; //  
  const Int_t DSMadc_HT2=18; //  
  const Int_t DSMadc_HT3=25; //  

  //event
  const Float_t TpcVz_MB = 6.0; 
  const Float_t diff_vzVpdVz_MB = 3.0;

  const Float_t TpcVz_HT1 = 6.0; 
  const Float_t diff_vzVpdVz_HT1 = 3.0;

  const Float_t TpcVz_HT2 = 6.0; 
  const Float_t diff_vzVpdVz_HT2 = 3.0;

  const Float_t TpcVz_HT3 = 6.0; 
  // const Float_t diff_vzVpdVz_HT3 = 3.0;

  
  
  //track
  const Float_t eta_max=0.7;
  const Float_t pt_min=0.2;
  const Int_t nhitsFit = 20;
  const Float_t nHitsRatio = 0.52;
  const Int_t nhitDedx=15;
  const Float_t gDca = 1.5;
  const Float_t tofbeta=0.025; 
  const Float_t tof_Y=1.8;
  const Float_t  Nsigama_electron_low=-1;
  const Float_t  Nsigama_electron_high=3;
  const Float_t min_pT_cut_BEMC=1;
  const Float_t max_pT_cut_Tof=4;
  
  const Float_t Dphi =0.05;
  const Float_t Dz=3;
  const Float_t poe_low=0.3;
  const Float_t poe_high=1.5;
  const Int_t NEta =1;
  const Int_t NPhi=1;


  // ee pair cuts
  const Float_t InvMass=0.06;
  const Float_t pairDca=0.6;

  /* const Float_t InvMass_HT=0.24; */
  /* const Float_t pairDca_HT=1; */

  // photonic electron partner cuts;
  const Float_t nsigmaE_partner_low=-1.5;
  const Float_t nsigmaE_partner_high=3;
  const Float_t  pt_min_partner=0.2;
  const Float_t eta_partner=1;
  const Float_t nhits_partner=15; // anatree
  const Float_t Ratio_partner_low=0.52; // anasTree
  const Float_t Ratio_Partner_high=1.02; // anaTree
  const Float_t gDca_parner=3; // anaTree

}
#endif
