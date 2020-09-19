//Analysis trees from embedding
//Author ShenghuiZhang
//09/2016
///////////////////////////////////////////////////////////

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class PlotFile;
#endif

#ifndef __CINT__
//#include <stdio.h>
#include <stdlib.h>
//#include "iostream.h"
//#include "iomanip.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "math.h"
#include "string.h"

#include "TROOT.h"
#include "TFile.h"

#include "TChain.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TPaletteAxis.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TVector2.h"
#include "TVector3.h"
//#include "StThreeVectorF.hh"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TUnixSystem.h"
#include "TRandom3.h"
#include "TGraphErrors.h"
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "mcT.h"
#include "histogram.h"
#include "mBadRunList.h"

using namespace std;

int main(int argc, char **argv)
{
  if(argc != 3) exit(1);
  FileOutPut = "output/Eff_";
  FileOutPut += argv[1];
  FileOutPut += ".root";
  FileInPut = "out/";
  FileInPut += argv[1];
  FileInPut += ".root";
  cout << "Reading "  << FileInPut  << endl;
  cout << "Creating " << FileOutPut << endl;
  
  TH1F:: SetDefaultSumw2();
  TH2F:: SetDefaultSumw2();
  TH3F:: SetDefaultSumw2();
  
  mh3DelPhiIncTrig0       = new TH3F("mh3DelPhiIncTrig0","",600,-3.14,3.14,400,-2,2,200,0,20);
  mh3DelPhiIncTrig2       = new TH3F("mh3DelPhiIncTrig2","",600,-3.14,3.14,400,-2,2,200,0,20);
  
  fincCheck = new TNtuple("incCheck", "single e for gpt sys", "ElectronpT:ElectronEta:ElectronPhi:HadronpT:HadronEta:HadronPhi:trig:dphi:deta:hpid:mcpt:hmcpt:mceta:hmceta:mcphi:hmcphi:mcdeta:mcdphi:mcy:hmcy:tagEeta:tagEphi:tagHeta:tagHphi");
  
  //--------------------
  // loop the chain
  //--------------------
  TChain *chain = new TChain("mcT");
  chain->Add(FileInPut.Data());
  
  int nevents = (int)chain->GetEntries();
  cout << "== total entries : " << nevents << endl;
  
  mcT *t = new mcT(chain);
  mNBadRuns = sizeof(mBadRuns_HT)/sizeof(int);
  
  //TRandom *gRandom = new TRandom3();
  gRandom->SetSeed(atoi(argv[2]));
  cout<<"argv[2] "<<gRandom->GetSeed()<<" "<<argv[2]<<" "<<atoi(argv[2])<<endl;
  for(int i=0;i<nevents;i++){
    if(i%10000==0) cout << "begin " << i << "th entry...." << endl;
    t->GetEntry(i);
    if(t->vx==-999.&&t->vy==-999.&&t->vz==-999.) continue;
    float Vr = sqrt(pow(t->vx,2.)+pow(t->vy,2.));
    if(Vr>=2) continue;
    int realRunId=1;
    for(int k=0;k<mNBadRuns;k++){
      if(t->runId==mBadRuns_HT[k]) {
        cout<<"mBadRuns"<<mBadRuns_HT[k]<<endl;
        realRunId=0; break;
      }
    }
    if(realRunId==0) continue;
    if(fabs(t->vz)>35.) continue;
    
    int nTracks   = t->nTracks;
    for(int j=0;j<nTracks;j++) {
      
      //===========================
      if(t->parentGeantId[j]!=0)continue;
      float mcpt  = t->E_mcPt[j];
      float mceta = t->E_mcEta[j];
      float mcphi = t->E_mcPhi[j];
      TLorentzVector Mc(0.,0.,0.,0.);
      Mc.SetPtEtaPhiM(mcpt,mceta,mcphi,MassE);
      bool tag = kFALSE;
      for(int g=0;g<nTracks;g++){
        if(g==j) continue;
        if(t->parentGeantId[g]!=0)continue;
        float mcptk  = t->E_mcPt[g];
        float mcetak = t->E_mcEta[g];
        float mcphik = t->E_mcPhi[g];
        TLorentzVector Mck(0.,0.,0.,0.);
        Mck.SetPtEtaPhiM(mcptk,mcetak,mcphik,MassE);
        
        Double_t deta = Mc.Rapidity() - Mck.Rapidity();
        Double_t dphi = mcphi - mcphik;
        while(dphi>2*TMath::Pi()) dphi -= 2.*TMath::Pi();
        while(dphi<0) dphi += 2.*TMath::Pi();
        while(dphi>TMath::Pi()) dphi = dphi -2*TMath::Pi();
        if(TMath::Abs(deta)<0.1 && TMath::Abs(dphi)<0.5) tag = kTRUE;
//        if(tag){
//          tmp[22] = Mc.Rapidity();
//          tmp[23] = Mck.Rapidity();
//          tmp[22] = mcphi;
//          tmp[23] = mcphik;
//        }
      }
      if(tag) continue;
      
      if(fabs(mceta)>0.7)continue;
      if(mcpt<0.2)continue;
      
      if(isHotTower(t->E_rctowerId[j])) continue;
      if(t->E_rcNCommonHits[j]<10) continue;
      
      
      float pt = t->E_rcPt[j];
      if(pt!=-999) pt = SmearPt(mcpt);
      float eta = t->E_rcEta[j];
      float phi = t->E_rcPhi[j];
      float dca = t->E_dca[j];
      int  nHitsFit = t->E_rcNHitsFit[j];
      int  nMaxPts = t->E_rcNHitsPoss[j];
      int  nDedxPts = t->E_rcNdEdx[j];
      float Rx = t->E_HelixX[j];
      float Ry = t->E_HelixY[j];
      float FirstTpcR = sqrt(Rx*Rx+Ry*Ry);
      float e = t->E_rcEnergy0[j];
      int   adc0 = t->E_rcadc0[j];
      int   dsmAdc = t->E_rcdsmadc[j];
      TLorentzVector Rc(0.,0.,0.,0.);
      Rc.SetPtEtaPhiM(pt,eta,phi,MassE);
      float p = Rc.P();//sqrt(pow(Rc.Px(),2)+pow(Rc.Py(),2)+pow(Rc.Pz(),2));
      float pe = (e>0)? p/e:9999;
      int  nEta = t->E_rcnEta[j];
      int  nPhi = t->E_rcnPhi[j];
      if(nEta<0)nEta=0;
      if(nPhi<0)nPhi=0;
      float zDist = t->E_rczDist[j];
      float phiDist = t->E_rcphiDist[j];
      bool cutOK =
      fabs(eta)<0.7 &&
      nMaxPts>0   &&
      fabs(1.0*nHitsFit)/nMaxPts>0.52;// &&
      
      Int_t trig = 0;
      Float_t tmp[30];
      tmp[0] = pt;
      tmp[1] = eta;
      tmp[2] = phi;
      ////////////////////////////////////////////
      if(cutOK && nHitsFit>20 && nDedxPts>15 && dca<1.5 && FirstTpcR<73 && e>0)
      {
        if(pe>0.3&&pe<1.5 && nEta>1&&nPhi>1&&fabs(zDist)<3&&fabs(phiDist)<0.015){
          if(dsmAdc>11&&adc0>180){
            for(int g=0;g<nTracks;g++){
              if(g==j) continue;
              //              if(t->parentGeantId[g]!=0)continue;
              float mcptk  = t->E_mcPt[g];
              float mcetak = t->E_mcEta[g];
              float mcphik = t->E_mcPhi[g];
              TLorentzVector Mck(0.,0.,0.,0.);
              Mck.SetPtEtaPhiM(mcptk,mcetak,mcphik,MassE);
              
              Double_t mcdeta = Mc.Rapidity() - Mck.Rapidity();
              Double_t mcdphi = mcphi - mcphik;
              while(mcdphi>2*TMath::Pi()) mcdphi -= 2.*TMath::Pi();
              while(mcdphi<0) mcdphi += 2.*TMath::Pi();
              while(mcdphi>TMath::Pi()) mcdphi = mcdphi -2*TMath::Pi();
              
              float hpt = t->E_rcPt[g];
              if(hpt!=-999) hpt = SmearPt(mcptk);
              float heta = t->E_rcEta[g];
              float hphi = t->E_rcPhi[g];
              float hdca = t->E_dca[g];
              int  hnHitsFit = t->E_rcNHitsFit[g];
              int  hnMaxPts = t->E_rcNHitsPoss[g];
              int  hnDedxPts = t->E_rcNdEdx[g];
              
              bool cutOK =
              fabs(heta)<1. &&
              hnDedxPts >= 10 &&
              hnMaxPts>0   &&
              nHitsFit>=15 &&
              fabs(1.0*hnHitsFit)/hnMaxPts>0.52 &&
              hdca < 1. && hdca > 0;
              
              Float_t dEta  = eta - heta; // zyj
              Float_t dphi = phi - hphi;
              while(dphi>TMath::Pi()) dphi -= 2.*TMath::Pi();
              while(dphi<-TMath::Pi()) dphi = dphi + 2.*TMath::Pi();
              
              float hRx = t->E_HelixX[g];
              float hRy = t->E_HelixY[g];
              float hFirstTpcR = sqrt(Rx*Rx+Ry*Ry);
              float he = t->E_rcEnergy0[g];
              int   hadc0 = t->E_rcadc0[g];
              int   hdsmAdc = t->E_rcdsmadc[g];
              TLorentzVector hRc(0.,0.,0.,0.);
              hRc.SetPtEtaPhiM(hpt,heta,hphi,MassE);
              float hp = hRc.P();//sqrt(pow(Rc.Px(),2)+pow(Rc.Py(),2)+pow(Rc.Pz(),2));
              float hpe = (e>0)? hp/he:9999;
              int  hnEta = t->E_rcnEta[g];
              int  hnPhi = t->E_rcnPhi[g];
              if(hnEta<0)hnEta=0;
              if(hnPhi<0)hnPhi=0;
              float hzDist = t->E_rczDist[g];
              float hphiDist = t->E_rcphiDist[g];
              if(hdca<1.5 && hFirstTpcR<73 && he>0 && hpe>0.3&&hpe<1.5 && hnEta>1&&hnPhi>1&&fabs(hzDist)<3&&fabs(hphiDist)<0.015){
                
                tmp[3] = hpt;
                tmp[4] = heta;
                tmp[5] = hphi;
                tmp[6] = trig;
                tmp[7] = dphi;
                tmp[8] = dEta;
                tmp[9] = t->parentGeantId[g];
                tmp[11] = mcpt;
                tmp[10] = mcptk;
                tmp[12] = mceta;
                tmp[13] = mcetak;
                tmp[14] = mcphi;
                tmp[15] = mcphik;
                tmp[16] = mcdeta;
                tmp[17] = mcdphi;
                tmp[18] = Mc.Rapidity();
                tmp[19] = Mck.Rapidity();
                //                tmp[19] = dsmAdc;
                //                tmp[19] = adc0;
                
                if(cutOK && abs(dEta) < 10.5) {
                  mh3DelPhiIncTrig0 -> Fill(dphi,dEta,pt);
                  fincCheck->Fill(tmp);
                  
                }
              }
            }
          }
          if(dsmAdc>18&&adc0>300){
            trig =2;
            for(int g=0;g<nTracks;g++){
              if(g==j) continue;
              //              if(t->parentGeantId[g]!=0)continue;
              float mcptk  = t->E_mcPt[g];
              float mcetak = t->E_mcEta[g];
              float mcphik = t->E_mcPhi[g];
              TLorentzVector Mck(0.,0.,0.,0.);
              Mck.SetPtEtaPhiM(mcptk,mcetak,mcphik,MassE);
              
              Double_t mcdeta = Mc.Rapidity() - Mck.Rapidity();
              Double_t mcdphi = mcphi - mcphik;
              while(mcdphi>2*TMath::Pi()) mcdphi -= 2.*TMath::Pi();
              while(mcdphi<0) mcdphi += 2.*TMath::Pi();
              while(mcdphi>TMath::Pi()) mcdphi = mcdphi -2*TMath::Pi();
              
              float hpt = t->E_rcPt[g];
              if(hpt!=-999) hpt = SmearPt(mcptk);
              float heta = t->E_rcEta[g];
              float hphi = t->E_rcPhi[g];
              float hdca = t->E_dca[g];
              int  hnHitsFit = t->E_rcNHitsFit[g];
              int  hnMaxPts = t->E_rcNHitsPoss[g];
              int  hnDedxPts = t->E_rcNdEdx[g];
              
              bool cutOK =
              fabs(heta)<1. &&
              hnDedxPts >= 10 &&
              hnMaxPts>0   &&
              nHitsFit>=15 &&
              fabs(1.0*hnHitsFit)/hnMaxPts>0.52 &&
              hdca < 1. && hdca > 0;
              
              Float_t dEta  = eta - heta; // zyj
              Float_t dphi = phi - hphi;
              while(dphi>TMath::Pi()) dphi -= 2.*TMath::Pi();
              while(dphi<-TMath::Pi()) dphi = dphi + 2.*TMath::Pi();
              
              float hRx = t->E_HelixX[g];
              float hRy = t->E_HelixY[g];
              float hFirstTpcR = sqrt(Rx*Rx+Ry*Ry);
              float he = t->E_rcEnergy0[g];
              int   hadc0 = t->E_rcadc0[g];
              int   hdsmAdc = t->E_rcdsmadc[g];
              TLorentzVector hRc(0.,0.,0.,0.);
              hRc.SetPtEtaPhiM(hpt,heta,hphi,MassE);
              float hp = hRc.P();//sqrt(pow(Rc.Px(),2)+pow(Rc.Py(),2)+pow(Rc.Pz(),2));
              float hpe = (e>0)? hp/he:9999;
              int  hnEta = t->E_rcnEta[g];
              int  hnPhi = t->E_rcnPhi[g];
              if(hnEta<0)hnEta=0;
              if(hnPhi<0)hnPhi=0;
              float hzDist = t->E_rczDist[g];
              float hphiDist = t->E_rcphiDist[g];
              if(hdca<1.5 && hFirstTpcR<73 && he>0 && hpe>0.3&&hpe<1.5 && hnEta>1&&hnPhi>1&&fabs(hzDist)<3&&fabs(hphiDist)<0.015){
                
                tmp[3] = hpt;
                tmp[4] = heta;
                tmp[5] = hphi;
                tmp[6] = trig;
                tmp[7] = dphi;
                tmp[8] = dEta;
                tmp[9] = t->parentGeantId[g];
                tmp[11] = mcpt;
                tmp[10] = mcptk;
                tmp[12] = mceta;
                tmp[13] = mcetak;
                tmp[14] = mcphi;
                tmp[15] = mcphik;
                tmp[16] = mcdeta;
                tmp[17] = mcdphi;
                tmp[18] = Mc.Rapidity();
                tmp[19] = Mck.Rapidity();
                
                if(cutOK && abs(dEta) < 10.5) {
                  mh3DelPhiIncTrig2 -> Fill(dphi,dEta,pt);
                  fincCheck->Fill(tmp);
                }
              }
            }
          }
        }
      }
    } //track loop
  } // end event looping
  TFile *fout = new TFile(FileOutPut,"recreate");
  fout->cd();
  mh3DelPhiIncTrig0->Write();
  mh3DelPhiIncTrig2->Write();
  fincCheck->Write();
  fout->Close();
  
  cout<<"end of program"<<endl;
  return(0);
  exit(0);
}

int isHotTower(int towId)
{
  //Int_t  Hot_towerlist[]={31, 51, 114, 275, 293, 479, 509, 533, 555, 561, 639, 681, 740, 743, 749, 772, 779, 799, 840, 860, 880, 893, 897, 982, 986, 993, 1063, 1142, 1160, 1200, 1224, 1232, 1237, 1241, 1256, 1263, 1280, 1284, 1306, 1313, 1318, 1337, 1438, 1486, 1537, 1592, 1709, 1713, 1732, 1823, 1850, 1856, 1879, 1945, 1976, 1984, 2043, 2145, 2162, 2164, 2190, 2202, 2290, 2299, 2300, 2313, 2339, 2414, 2439, 2459, 2529, 2580, 2633, 2652, 2834, 2863, 2865, 2874, 3005, 3020, 3061, 3137, 3154, 3420, 3515, 3532, 3692, 3720, 3737, 3838, 3861, 3925, 3948, 4013, 4130, 4169, 4262, 4316, 4430, 4458, 4534, 4560, 4595, 4684, 4766, 4781,};//from Bingchu note about event activity
  Int_t Hot_towerlist[]={31, 51, 114, 275, 293, 479, 509, 533, 555, 561, 639, 681, 740, 743, 749, 772, 779, 799, 840, 860, 880, 893, 897, 982, 986, 993, 1063, 1142, 1160, 1200, 1224, 1232, 1237, 1241, 1256, 1263, 1280, 1284, 1306, 1313, 1318, 1337, 1438, 1486, 1537, 1592, 1709, 1713, 1732, 1823, 1850, 1856, 1879, 1945, 1976, 1984, 2043, 2145, 2162, 2164, 2190, 2202, 2290, 2299, 2300, 2313, 2339, 2414, 2439, 2459, 2529, 2580, 2633, 2652, 2834, 2863, 2865, 2874, 3005, 3020, 3061, 3137, 3154, 3420, 3515, 3532, 3692, 3720, 3737, 3838, 3861, 3925, 3948, 4013, 4130, 4169, 4262, 4316, 4430, 4458, 4534, 4560, 4595, 4684, 4766, 4781,50,245,251,385,405,682,691,775,1042,1304,1422,1443,1892,1906,2021,2022,2047,2051,2063,2083,2109,2146,2171,2267,2303,2368,2445,2493,2504,2521,2750,2861,3063,3171,3241,3292,3451,3453,3544,3726,3749,4050,4122,4230,4232,4353,4453,4469,4546,4646,4722,4727};//from Bingchu note about event activity
  Int_t   mNHotTower;
  mNHotTower = sizeof(Hot_towerlist)/sizeof(int);
  for(Int_t i=0;i<mNHotTower;i++ )
  {
    if(Hot_towerlist[i]==towId)
      
      return kTRUE;
  }
  return kFALSE;
}
Double_t CrystalBall2(Double_t *x, Double_t *par)
{
  Double_t N = par[0];
  Double_t mu = par[1];
  Double_t s = par[2];
  Double_t n1 = par[3];
  Double_t alpha1 = par[4];
  Double_t n2 = par[5];
  Double_t alpha2 = par[6];
  
  Double_t A = TMath::Power(n1/fabs(alpha1), n1) * TMath::Exp(-alpha1*alpha1/2.);
  Double_t B = n1/fabs(alpha1) - fabs(alpha1);
  
  Double_t C = TMath::Power(n2/fabs(alpha2), n2) * TMath::Exp(-alpha2*alpha2/2.);
  Double_t D = n2/fabs(alpha2) - fabs(alpha2);
  
  Double_t norm = (x[0]-mu)/s;
  
  if(norm < -alpha1) {
    return N * A * TMath::Power(B-norm, -n1);
  } else if(norm < alpha2) {
    return N * TMath::Exp(-0.5*norm*norm);
  } else {
    return N * C * TMath::Power(D+norm, -n2);
  }
}
//-------------------------------------------------------------------------------
Double_t ABf(double *x, double *par)
{
  double a = par[0];
  double b = par[1];
  //double f = (a*a*x[0]*x[0] + b*b);
  double f = sqrt(a*a*x[0]*x[0] + b*b);
  
  return f;
}

Double_t SmearPt(double mcpt)
{
  
  TF1 *f_AB = new TF1("f_AB", &ABf, 0, 20, 2 );
  f_AB->SetParameters(0.005580,0.008293);////from bingchu's event activities note
  double sigmaptoverpt = (double)f_AB->Eval(mcpt);
  
  TF1 *f_CB2 = new TF1("f_CB2", &CrystalBall2, -0.5, 0.5, 7 );
  
  f_CB2->SetParameters(2.893e4,-0.001152,0.01034,1.305,1.659,3.432,1.75);
  //f_CB2->SetParErrors(47.65,0.000015,0.00002,0.008,0.005,0.042,0.01);
  
  double deltaPtovermcPt_RDM = f_CB2->GetRandom();
  
  double smrpt = mcpt + mcpt*(deltaPtovermcPt_RDM/0.01)*sigmaptoverpt;//sigmaptoverpt: real resolution from data and emebeding Jpsi signal matching;deltaPtovermcPt_RDM/0.01: rc pt possibility in this MC pt, using 0.01 is due to all resolution is normalized to 0.01.
  
  return smrpt;
}
