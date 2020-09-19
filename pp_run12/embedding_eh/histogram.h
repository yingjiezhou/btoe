const int nPtBins = 10;
float ptbin[nPtBins+1]={2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,10.0};
float ptbinfyj[nPtBins]={2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5};
const int nPtBinsAll = 39;
float ptbinAll[nPtBinsAll+1]={0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,10.0,14.0,20.0};
TString FileInPut;
TString FileOutPut;
TString Style[2]={"Pi0","Eta"};
TFile *fout;
TFile * weightFile;
TGraphErrors * gFONLLu;
TGraphErrors * gFONLL;
TH1F *hdNdpTdy;
TH1F *hGammadNdpTdy;
TH1F *hGammaCS;
TF1 *hTpp;
Int_t mNBadRuns;
float mass;
float MassE;
float BR;
int isHotTower(int towId);
double SmearPt(double mcpt);
double CrystalBall2(double* x, double* par);
double ABf(double *x, double *par);
TH3F *mh3DelPhiIncTrig0;
TH3F *mh3DelPhiIncTrig2;

TNtuple *fincCheck;//!<! output ntuple
