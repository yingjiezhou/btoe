#ifndef __GRAPHIC_H_
#define __GRAPHIC_H_

#include <fstream>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TH2.h"
#include "TF1.h"

class Graphic{

 public:
  void Graphic::SetPallet();
  void Graphic::SetGraphStyles (TAttMarker * Gtmp, int sty, int col);
  void Graphic::SetWaku(TH1D *Gtmp, double mim, double max, 
	char name0[100], char name1[100]);
  void Graphic::SetFill(TH1D *Gtmp, int col);

};

#endif
