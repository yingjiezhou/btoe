#include "TGraphAsymmErrorsBracket.hh"
#include "TPad.h"
#include "TStyle.h"

TGraphAsymmErrorsBracket::TGraphAsymmErrorsBracket()
 : TGraphAsymmErrors()
{
  Init();
}

TGraphAsymmErrorsBracket::TGraphAsymmErrorsBracket(Int_t n)
 : TGraphAsymmErrors(n)
{
  Init();
}

TGraphAsymmErrorsBracket::TGraphAsymmErrorsBracket(Int_t n, const Float_t *x, const Float_t *y, const Float_t *exl, const Float_t *exh, const Float_t *eyl, const Float_t *eyh)
 : TGraphAsymmErrors(n, x, y, exl, exh, eyl, eyh)
{
  Init();
}

TGraphAsymmErrorsBracket::TGraphAsymmErrorsBracket(Int_t n, const Double_t *x, const Double_t *y, const Double_t *exl, const Double_t *exh, const Double_t *eyl, const Double_t *eyh)
 : TGraphAsymmErrors(n, x, y, exl, exh, eyl, eyh)
{
}
TGraphAsymmErrorsBracket::TGraphAsymmErrorsBracket(const TGraphAsymmErrorsBracket &gr)
 : TGraphAsymmErrors(gr)
{
  Init();
}

TGraphAsymmErrorsBracket::TGraphAsymmErrorsBracket(const TGraphAsymmErrors &gr)
 : TGraphAsymmErrors(gr)
{
  Init();
}

void TGraphAsymmErrorsBracket::Init()
{
  useErrorX = false;
  endx = 10;
  endy =  5;
  color_bracket=1;
  style_bracket=1;
  width_bracket=1;
}

TGraphAsymmErrorsBracket::~TGraphAsymmErrorsBracket()
{
}

void TGraphAsymmErrorsBracket::Paint(Option_t *option)
{
  if(gPad == NULL) return;
  //if(gPad->GetLogx() || gPad->GetLogy()) return;
   
  Bool_t axis = kFALSE;
  if (strchr(option,'a')) axis = kTRUE;
  if (strchr(option,'A')) axis = kTRUE;
  if (axis) TGraph::Paint(option);

  Double_t txl = gPad->PixeltoX(endx) - gPad->PixeltoX(0);
  Double_t txh = gPad->PixeltoX(endx) - gPad->PixeltoX(0);
  Double_t ty  =-gPad->PixeltoY(endy) + gPad->PixeltoY(0);
  
  // clip
  gPad->SetBit(kClipFrame, TestBit(kClipFrame));  
  // paint
  if(!gPad->IsBatch()){
    if(color_bracket>0){
      gVirtualX->SetLineColor(color_bracket);
    }
    if(style_bracket>0){
      gVirtualX->SetLineStyle(style_bracket);
    }
    if(width_bracket>0){
      gVirtualX->SetLineStyle(width_bracket);
    }
  }
  gPad->SetAttLinePS(color_bracket, style_bracket, width_bracket);
    
  for(Int_t i=0; i<fNpoints; i++){
    Double_t x = gPad->XtoPad(fX[i]);
    Double_t y = gPad->YtoPad(fY[i]);
    if(x < gPad->GetUxmin()) x = gPad->GetUxmin();
    if(x > gPad->GetUxmax()) x = gPad->GetUxmax();
    if(y < gPad->GetUymin()) y = gPad->GetUymin();
    if(y > gPad->GetUymax()) y = gPad->GetUymax();
    Double_t eyl = fEYlow[i];
    Double_t eyh = fEYhigh[i];

    if(useErrorX){
      txl = fEXlow[i];
      txh = fEXhigh[i];
    }
     
    //----- Draw Error -----//
    // horizontal
    gPad->PaintLine(x-txl, y+eyh, x+txh, y+eyh);
    gPad->PaintLine(x-txl, y-eyl, x+txh, y-eyl);
    
    // vertical upper
    gPad->PaintLine(x-txl, y+eyh, x-txl, y+eyh-ty);
    gPad->PaintLine(x+txh, y+eyh, x+txh, y+eyh-ty);
    // vertical lower 
    gPad->PaintLine(x-txl, y-eyl, x-txl, y-eyl+ty);
    gPad->PaintLine(x+txh, y-eyl, x+txh, y-eyl+ty);
  }
  
  if(!axis) TGraph::Paint(option);
  //gPad->ResetBit(kClipFrame); 
}
