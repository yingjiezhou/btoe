#include "Graphic.h"

void Graphic::SetPallet()
{
  gStyle->SetOptStat (0);
  gStyle->SetPadBorderMode (0);
  gStyle->SetPadColor (kWhite);
  gStyle->SetCanvasColor (kWhite);
  gStyle->SetFrameBorderMode (0);
  gStyle->SetCanvasBorderMode (0);
  gStyle->SetPalette (1);
  gStyle->SetTitleBorderSize (0);
}

void Graphic::SetGraphStyles (TAttMarker * Gtmp, int sty, int col)
{
  Gtmp->SetMarkerStyle (sty);
  Gtmp->SetMarkerColor (col);
  Gtmp->SetMarkerSize (1.3);
}

void Graphic::SetWaku(TH1D *Gtmp, double mim, double max, 
	char name0[100], char name1[100])
{
 Gtmp->SetMinimum(mim);
 Gtmp->SetMaximum(max); 
 Gtmp->GetXaxis()->SetTitle(name0);
 Gtmp->GetYaxis()->SetTitle(name1);
}

void Graphic::SetFill(TH1D* Gtmp, int col)
{
  Gtmp->SetFillStyle(3002);
  Gtmp->SetFillColor(col);
}

