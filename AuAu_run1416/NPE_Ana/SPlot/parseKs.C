/////////////////////////////////////////////////////////////////////////
// SPlot for NPE analysis
// author: Matthew Kelsey
// date Aug. 7 
/////////////////////////////////////////////////////////////////////////
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
void parseKs()
{

    char dFile[500];
    sprintf(dFile,"../production/NPE_Tuples_TuneB1.root");
    TFile *f_D = new TFile(dFile);
    TTree *t = f_D->Get("Ks");    
 
    TFile out("Ks.root","RECREATE");
    TTree* Ks = t->CopyTree("Entry$<5E6 &&  probe_pt<2");
    
    Ks->SetName("Ks");
    Ks->Write();
    out.Close();
    out.Delete(); 
}



