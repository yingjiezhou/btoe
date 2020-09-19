#include "../Binning_MB.h"
void rebin()
{
  const int mh2Nhist=3;
  const int Npt = 8;
  char buf[1024];
  
  TH1F *mh1hist_Dca_D[mh2Nhist][Npt];
  TH1F *mh1hist_Dca_B[mh2Nhist][Npt];
  
  TH1F *mh1hist_Dca_D_rebin[mh2Nhist][Npt];
  TH1F *mh1hist_Dca_B_rebin[mh2Nhist][Npt];
  
  TFile *file = new TFile("File_fastsim.root", "READ");
  TFile *fl = new TFile("File_fastsim_yj.root", "RECREATE");

  for(Int_t ihist=0;ihist<mh2Nhist;ihist++){
    for(Int_t ipt=0;ipt<Npt;ipt++){
      sprintf(buf,"mh1rDca_hist%ipt%i_D",ihist,ipt);
      mh1hist_Dca_D[ihist][ipt]= (TH1F *) file->Get(buf);
      mh1hist_Dca_D_rebin[ihist][ipt] = (TH1F *)mh1hist_Dca_D[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_D[ihist][ipt]->GetName()+TString("_yj"),DcaEdgeDca);
      
      sprintf(buf,"mh1rDca_hist%ipt%i_B",ihist,ipt);
      mh1hist_Dca_B[ihist][ipt]= (TH1F *) file->Get(buf);
      mh1hist_Dca_B_rebin[ihist][ipt]= ( TH1F * )mh1hist_Dca_B[ihist][ipt]->Rebin(nDcasDca,mh1hist_Dca_B[ihist][ipt]->GetName()+TString("_yj"), DcaEdgeDca);
      fl->cd();
      mh1hist_Dca_D_rebin[ihist][ipt]->Write();
      mh1hist_Dca_B_rebin[ihist][ipt]->Write();
    }
  }
  fl->Close();
  return ;

}

