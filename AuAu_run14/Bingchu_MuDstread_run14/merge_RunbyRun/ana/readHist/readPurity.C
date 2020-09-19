#include "TH2F.h"
#include "THnSparse.h"
#include "TFile.h"
//    double sparseFill[10] = {mpt, nsige, nsigpi,nsigp,nsigk,meta,cent9_grefmult,event->primaryVertex().z(),dcaXY,dcaZ};
//enum { kP=0, kPt, kEta, kPi, kKa, kPr, kN };
//=============================================================================

bool HFT_flag=1;
bool TOF_cut_flag=1;
TH2F *mh2;
THnSparseF *hs;
TH2 *mh2s;
const int mh2Nhist= 3;

TString mh2Name_nsigmaE[mh2Nhist]={"nsigmaPI_pT_diff_","nsigmaP_pT_diff_","nsigmaK_pT_diff_"};
TString mh2Name_HFT_nsigmaE[mh2Nhist]={"nsigmaPI_pT_HFT__diff_","nsigmaP_pT_HFT__diff_",
  "nsigmaK_pT_HFT__diff_"};

void readPurity(TString filename)
{

  TFile *file=TFile::Open(Form("%s",filename.Data()),"READ");
  cout<<filename.Data()<<endl; 
  TString inputFileName = filename;
  Int_t index = inputFileName.Index("physics_");
  TString mInputFileName="";
  for(int i=index;i<(int)inputFileName.Length();i++) {
    mInputFileName.Append(inputFileName(i));
  }
  TString outputFile;
  outputFile=mInputFileName;
  
  TFile *file_purity=new TFile(Form("%s",outputFile.Data()),"RECREATE");
//=============================================================================
// hadron diff
  
  for(int tr=0; tr<1; tr++){
    for(int p=0; p<3; p++){
      mh2 = (TH2F *)(file->Get(Form("%s%d",mh2Name_nsigmaE[p].Data(),tr)));
      mh2->SetName(Form("%s%d",mh2Name_nsigmaE[p].Data(),tr));
      mh2->Write();
      mh2->Clear();
      if(HFT_flag){
        mh2 = (TH2F *)(file->Get(Form("%s%d",mh2Name_HFT_nsigmaE[p].Data(),tr)));
        mh2->SetName(Form("%s%d",mh2Name_HFT_nsigmaE[p].Data(),tr));
        mh2->Write();
        mh2->Clear();
      }
    }
//=============================================================================
    //inclusive e

    if(TOF_cut_flag){
      hs = (static_cast<THnSparseF*>(file->Get(Form("nSigmaE_TOF_%d",tr))));
      mh2s = (hs->Projection(1, 0));
      mh2s->SetName(Form("mnsigmaE_pT_E_TOF%d",tr));
      mh2s->Write();
      mh2s->Clear();
      if(HFT_flag){
        hs = (static_cast<THnSparseF*>(file->Get(Form("nSigmaE_TOF_HFT_%d",tr))));
        mh2s =(TH2*) (hs->Projection(1,0));
        mh2s->SetName(Form("mnsigmaE_pT_HFT_E_TOF%d",tr));
        mh2s->Write();
        mh2s->Clear();
      }
    }
  }// end trigger loop
//=============================================================================
  
  file_purity->Close();

  return;
}
