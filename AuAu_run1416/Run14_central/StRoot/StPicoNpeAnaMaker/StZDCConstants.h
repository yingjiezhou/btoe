#ifndef StZDCConstants_H
#define StZDCConstants_H

#include "Rtypes.h"
#include <string>

namespace zdcconst
{

   float const PI = std::acos(-1.0);

   Double_t zdcsmdGainFac[2][2][8] = {
      { { 1,1.16948,1.18915,1.14788,0.928795,0.959144,1.12426,1} ,
         { 1,1.3213,1.48021,1.54456,1.27161,1.40803,1.4158,1.56435} } ,
      { { 1,1.23165,1.35675,1.21217,1.16167,1.0704,1.14237,1} ,
         { 1,0.940106,1.0791,0.890919,0.999546,1.16881,0.996674,0.96814} }
   };

   /*Double_t zdcsmdGainFac[2][2][8] = {
      { { 1,1,1,1,1,1,1,1} ,
         { 1,1,1,1,1,1,1,1} } ,
      { { 1,1,1,1,1,1,1,1} ,
         { 1,1,1,1,1,1,1,1} }
   };*/

   Double_t zdcsmdPedstal[2][2][8] = {{{0,},{0,}},{{0,},{0,}}}; // automatic ped subtraction after Feb 2011!!!

   Float_t zdcsmd_x[7] = {0.5,2,3.5,5,6.5,8,9.5};
   Float_t zdcsmd_y[8] = {1.25,3.25,5.25,7.25,9.25,11.25,13.25,15.25};

   Double_t zdcsmd_wx0 = 4.76183; //run10 200 GeV
   Double_t zdcsmd_ex0 = 4.92438;
   Double_t zdcsmd_wy0 = 5.51617;
   Double_t zdcsmd_ey0 = 5.84382;
}
#endif
