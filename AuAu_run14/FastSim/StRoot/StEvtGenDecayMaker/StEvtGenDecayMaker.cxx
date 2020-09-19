/*/-----------------

  This class is for the eventGen production
  Auther:  Xiaozhi 5/1/2015 xiaozhi@uic.edu
  version 2 update with new smear peakage,  Tue Oct 27 22:25:54 EDT 2015 by xiaozhi 
  ----------------*/

#include "EvtGen/EvtGen.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtReport.hh"
#include "EvtGenBase/EvtHepMCEvent.hh"
#include "EvtGenBase/EvtStdlibRandomEngine.hh"
#include "EvtGenBase/EvtAbsRadCorr.hh"
#include "EvtGenBase/EvtDecayBase.hh"
#include "EvtGenExternal/EvtExternalGenList.hh"

#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <vector>
#include <fstream>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include"TParticle.h"
#include"TLorentzVector.h"
#include"TClonesArray.h"
#include "TVirtualMCDecayer.h"
#include "TClonesArray.h"
#include "TString.h"
#include "vector"
#include "TRandom.h"
#include "StRoot/StarGenerator/StarEvtGenDecayer/StarEvtGenDecayer.h"
#include "TNtuple.h"
#include "TFile.h"
#include "time.h"
#include "TTimer.h"
#include "TRandom3.h"
#include "StEvtGenDecayMaker.h"
#include "phys_constants.h"                                                 
#include "SystemOfUnits.h"
#include "dataDrivenFastSimulator.h"
 

using namespace std;
const double accp_eta=1.3;
const int MaxDaughter=50;

std::pair<float, float> const momentumRange(0, 12);
float const acceptanceRapidity = 1.3;

static  const float M_B_0 = 5.280; // GeV/c^2
static  const float M_B_PLUS = 5.280; // GeV/c^2   */


StEvtGenDecayMaker::StEvtGenDecayMaker()
{

}
StEvtGenDecayMaker::~StEvtGenDecayMaker()
{
  //delete 

}
StEvtGenDecayMaker::StEvtGenDecayMaker(int Parent_pdg,int Number_Event,TString outfile)
{
  loadAllDistributions();
  parent_PDG=Parent_pdg;
  NEvet=Number_Event;
  outfile_name=outfile;
  // TFile *input=new TFile("Decay_table/Weight.root","READ");
  // Weight_pt=(TH1D *) input->Get("Pi"); 
  // TFile *input=new TFile("/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/Charm_pp200_data.root","READ");
  // Weight_pt=(TF1 *) input->Get("levy"); 
  TFile *input=new TFile("/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/Charm_spectra_weight.root","READ");
  //  Weight_pt=(TH1D *) input->Get("D_spectra_levy"); // yifei 
  //  Weight_pt=(TH1D *) input->Get("D_spectra_hf1PowerLaw");// from Mustafa 
  //Weight_ptgr_levy_pythia=(TH1D *) input->Get("gr_levy_pythia");  
  levy_pythia= (TH1F *) input->Get("levy_pythia"); 
  levy_fonll= (TH1F *) input->Get("levy_fonll"); 
  D0YVsPty= (TH1D *) input->Get("D0YVsPty"); 
  std::cout<< "constructor"<<"  "<<outfile<<std::endl;
}
void StEvtGenDecayMaker::OpenFile()
{
  mfile=new TFile(outfile_name,"RECREATE");
  Tree = new TTree("Tree","Tree");
  std::cout<< "file is open "<<"  "<<outfile_name<<std::endl;
}
void StEvtGenDecayMaker::Write()
{
  mfile->cd();
  Tree->Write();
  mfile->Close();
}
void StEvtGenDecayMaker::make()
{ 
  /************************************************ set up the EvetGen *****************************/ 
  TTimer *timer = new TTimer();
  TRandom3  *myRandom = new TRandom3();  
  unsigned  long long tmp = (unsigned long   long)timer->GetAbsTime(); 
  unsigned int stime = fabs(tmp)/myRandom->Rndm() ;
  EvtStdlibRandomEngine * eng = new EvtStdlibRandomEngine();
  eng->setSeed(stime);
  //  eng->setSeed(NULL);
  EvtRandom::setRandomEngine((EvtRandomEngine*)eng);
  EvtAbsRadCorr* radCorrEngine = 0;
  std::list<EvtDecayBase*> extraModels;
  
  //#ifdef EVTGEN_EXTERNAL
  EvtExternalGenList genList;
  radCorrEngine = genList.getPhotosModel(); //
  extraModels = genList.getListOfModels();
  //#endif
  
  //Initialize the generator - read in the decay table and particle properties
  TString Decay_2010_DEC="/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/DECAY_2010.DEC";
  TString Evt_pdl="/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/evt.pdl";
  EvtGen *myGenerator=new EvtGen(Decay_2010_DEC,Evt_pdl,(EvtRandomEngine*)eng,radCorrEngine, &extraModels);
  StarEvtGenDecayer *Decay_Event=new StarEvtGenDecayer(myGenerator); // 用自己配置的产生器产生一个事件！！
  EvtId Parent_EvtGenID=EvtPDL::evtIdFromLundKC(parent_PDG); 
  //    TString Decay_file="/star/u/xiao00/test_EvetGen/Decay_table/Pi0Gamma.DEC";
  //  TString Decay_file="/star/u/xiao00/test_EvetGen/Decay_table/D0.DEC";
  TString Decay_file="/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/B_test.DEC";
  //  TString Decay_file="/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/B_test.DEC";
  //  TString Decay_file="/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/NPE_8_14.DEC";
  //  if(parent_PDG==111||parent_PDG==221) // pi0 and eta
  //  Decay_file="/star/u/xiao00/Run14/work_AuAu200_NPE/Fast_Simulation/Decay_table/NPE_pi0_eta_dalitz.DEC";
  // if(abs(parent_PDG)==421||abs(parent_PDG)==411)//||parent_PDG==111||parent_PDG==221)
  //     Decay_Event->setDecayTable(Decay_file);
  
  //  ************************************************ set up the EvetGen *****************************// 
  Double_t pt=0;
  Double_t eta=0;
  Double_t phi=0;
  Double_t px=0;
  Double_t py=0;
  Double_t pz=0;
  Double_t E=0;

  int Ndaughter=0;    
  Int_t   mpdg[MaxDaughter];
  double  mPx[MaxDaughter];
  double  mPy[MaxDaughter];
  double  mPz[MaxDaughter];
  double  mE[MaxDaughter];  
  double  mvx[MaxDaughter];
  double  mvy[MaxDaughter];
  double  mvz[MaxDaughter];
  double  mct[MaxDaughter];
  Int_t  dpdg[MaxDaughter]; 
  Int_t  dParent_pdg[MaxDaughter]; 
  double  dPx[MaxDaughter];
  double  dPy[MaxDaughter];
  double  dPz[MaxDaughter];
  double  dRPx[MaxDaughter];
  double  dRPy[MaxDaughter];
  double  dRPz[MaxDaughter];
  double  dE[MaxDaughter];  
  double  dvx[MaxDaughter];
  double  dvy[MaxDaughter];
  double  dvz[MaxDaughter];
  double  dct[MaxDaughter];
  double  d3Ddca[MaxDaughter];
  double  ddcaXY[MaxDaughter];
  double  ddcaZ[MaxDaughter];
  double  d3DRdca[MaxDaughter];
  double  dRdcaXY[MaxDaughter];
  double  dRdcaZ[MaxDaughter];
  Int_t Ncent[MaxDaughter];
  double Vtx[MaxDaughter];
  double Vty[MaxDaughter];
  double Vtz[MaxDaughter];
  
  Tree->Branch("Ndaughter",&Ndaughter,"Ndaughter/I");
  Tree->Branch("mpdg",mpdg,"mpdg[Ndaughter]/I");
  Tree->Branch("mPx",mPx,"mPx[Ndaughter]/D");
  Tree->Branch("mPy",mPy,"mPy[Ndaughter]/D");
  Tree->Branch("mPz",mPz,"mPz[Ndaughter]/D");
  Tree->Branch("mE",mE,"mE[Ndaughter]/D");
  Tree->Branch("mvx",mvx,"mvx[Ndaughter]/D");
  Tree->Branch("mvy",mvy,"mvy[Ndaughter]/D");
  Tree->Branch("mvz",mvz,"mvz[Ndaughter]/D");
  Tree->Branch("mct",mct,"mct[Ndaughter]/D");
  Tree->Branch("dpdg",dpdg,"dpdg[Ndaughter]/I");
  Tree->Branch("dParent_pdg",dpdg,"dParent_pdg[Ndaughter]/I");
  Tree->Branch("dPx",dPx,"dPx[Ndaughter]/D");
  Tree->Branch("dPy",dPy,"dPy[Ndaughter]/D");
  Tree->Branch("dPz",dPz,"dPz[Ndaughter]/D");
  Tree->Branch("dRPx",dRPx,"dRPx[Ndaughter]/D");
  Tree->Branch("dRPy",dRPy,"dRPy[Ndaughter]/D");
  Tree->Branch("dRPz",dRPz,"dRPz[Ndaughter]/D");
  Tree->Branch("dE",dE,"dE[Ndaughter]/D");
  Tree->Branch("dvx",dvx,"dvx[Ndaughter]/D");
  Tree->Branch("dvy",dvy,"dvy[Ndaughter]/D");
  Tree->Branch("dvz",dvz,"dvz[Ndaughter]/D");
  Tree->Branch("dct",dct,"dct[Ndaughter]/D");
  Tree->Branch("d3Ddca",d3Ddca,"d3Ddca[Ndaughter]/D");
  Tree->Branch("ddcaXY",ddcaXY,"ddcaXY[Ndaughter]/D");
  Tree->Branch("ddcaZ",ddcaZ,"ddcaZ[Ndaughter]/D");
  Tree->Branch("d3DRdca",d3DRdca,"d3DRdca[Ndaughter]/D");
  Tree->Branch("dRdcaXY",dRdcaXY,"dRdcaXY[Ndaughter]/D");
  Tree->Branch("dRdcaZ",dRdcaZ,"dRdcaZ[Ndaughter]/D");
  Tree->Branch("Ncent",Ncent,"Ncent[Ndaughter]/I");
  Tree->Branch("Vtx",Vtx,"Vtx[Ndaughter]/D");
  Tree->Branch("Vty",Vty,"Vty[Ndaughter]/D");
  Tree->Branch("Vtz",Vtz,"Vtz[Ndaughter]/D");
 
  char buf[1024]; 
  for(Int_t iEvet=0;iEvet<NEvet;iEvet++){  //  Event Loop              
    // cout<< M_D_0<<endl;
    if(iEvet%10000==0)
      cout<< "---------working on Event "<<iEvet<<endl;
    Ndaughter=0;        
    Double_t m0= EvtPDL::getMass(Parent_EvtGenID); //类似于alice 的getpdg之后得到pdgMass
    get_kinematics(pt,eta,phi,px,py,pz,E,m0); //这个函数是为了利用随机数得到打入粒子的各种运动学变量，m0 是已知的，利用uniform随机数得到pt，利用  得到y，然后得到其他变量
    //   Double_t E=sqrt(m0*m0+px*px+py*py+pz*pz);
    TLorentzVector *p_mom=new TLorentzVector(px,py,pz,E);   // 把parent particle 的4个分量存成一个矢量，因为parent particl 也是通过随机数随机打入的，只有m0是已知确定的
    TLorentzVector *r_pos=new TLorentzVector(0,0,0,0); //给定parent 粒子，也就是打入的HF hadron 的初始原点坐标，但是本代码默认是(0,0,0,0)
    ResolveDecay(Decay_Event,Ndaughter,parent_PDG,p_mom,r_pos,mpdg,mPx,mPy, mPz,mE,mvx,mvy,mvz,mct,dpdg,dParent_pdg,dPx,dPy,dPz,dE,dRPx,dRPy,dRPz,dvx,dvy,dvz,dct,d3Ddca,ddcaXY,ddcaZ,d3DRdca,dRdcaXY,dRdcaZ,Ncent,Vtx,Vty,Vtz);   //对daughter 粒子进行smear，存储
    //dParent_pdg,Vtx,Vty,Vtz

    Tree->Fill();
    
    delete p_mom;
    delete r_pos;
    
  }// Evt loop
}
void StEvtGenDecayMaker::ResolveDecay(StarEvtGenDecayer *Decay_Event,int &Ndaughter,Int_t Parent_pdg,TLorentzVector *p_mom,TLorentzVector *r_pos,Int_t mpdg[ ],double mPx[ ],double mPy[ ],double  mPz[ ], double mE[ ], double mvx[ ], double mvy[ ], double mvz[ ], double mct[ ], Int_t dpdg[ ], Int_t dParent_pdg[ ], double dPx[ ],double dPy[ ], double  dPz[ ],double dE[ ],double dRPx[ ],double dRPy[ ], double  dRPz[ ], double dvx[ ], double dvy[ ], double dvz[ ], double  dct[ ],double  d3Ddca[ ],double  ddcaXY[ ],double  ddcaZ[ ],double  d3DRdca[ ],double  dRdcaXY[ ],double  dRdcaZ[ ],Int_t Ncent[],double Vtx[],double Vty[],double Vtz[])
{
  //return;
  int N=0;
  TClonesArray *Array=new TClonesArray("TParticle");
  Decay_Event->Decay(Parent_pdg,p_mom); // 让event 进行decay
  // Decay_Event->setVertex(r_pos); // 设定parent 粒子，也就是打入的HF hadron 的初始原点坐标
  N=Decay_Event->ImportParticles(Array);   // 将event 衰变出来的粒子直接放到array 里面， N现在在这里没什么用
  for(int iDaughter=0;iDaughter<Array->GetEntries();iDaughter++) //对衰变出来的daughter 粒子进行h循环
    {
      TParticle* particle = (TParticle*)Array->At(iDaughter); // decay 出来的粒子
      //    switch (abs(dpdg)==22)
      SaveDaughter(particle,Ndaughter,Parent_pdg,p_mom,r_pos,mpdg,mPx,mPy,mPz,mE,mvx,mvy,mvz,mct,dpdg,dParent_pdg,dPx,dPy,dPz,dE,dRPx,dRPy,dRPz,dvx,dvy,dvz,dct,d3Ddca,ddcaXY,ddcaZ,d3DRdca,dRdcaXY,dRdcaZ,Ncent,Vtx,Vty,Vtz); // To semar daughter particle
      //  continue;
      if(Continue_Decay(particle->GetPdgCode())) // 如果这个daughter粒子不是电子的话，考虑是否让他继续decay
      	{
      	  //cout<< " Resolev third Decay"<< particle->GetPdgCode()<<endl;
	  int Parent_pdg =particle->GetPdgCode(); // 将上级decay 出来的粒子作为母粒子继续进行decay
	  // cout<<Parent_pdg<< "  Decay to"<< dpdg<<endl;
	  TLorentzVector *p_mom=new TLorentzVector(particle->Px(),particle->Py(),particle->Pz(),particle->Energy());
	  TLorentzVector *r_pos=new TLorentzVector(particle->Vx(),particle->Vy(),particle->Vz(),particle->T()); // 这里给的就是这个粒子的初始顶点坐标位置
	  ResolveDecay(Decay_Event,Ndaughter,Parent_pdg,p_mom,r_pos,mpdg,mPx,mPy, mPz,mE,mvx,mvy,mvz,mct,dpdg,dParent_pdg,dPx,dPy,dPz,dE,dRPx,dRPy,dRPz,dvx,dvy,dvz,dct,d3Ddca,ddcaXY,ddcaZ,d3DRdca,dRdcaXY,dRdcaZ,Ncent,Vtx,Vty,Vtz);         
          delete p_mom; 
          delete r_pos;
        } 
      // cout<<" Resolve Decay"<< N<<"  "<<Array<<endl;
    }
  delete Array; //->Delete();
}
void StEvtGenDecayMaker::SaveDaughter(TParticle *particle,int &Ndaughter,Int_t Parent_pdg,TLorentzVector *p_mom,TLorentzVector *r_pos,Int_t mpdg[ ],double mPx[ ],double mPy[ ],double  mPz[ ], double mE[ ], double mvx[ ], double mvy[ ], double mvz[ ], double mct[ ], Int_t dpdg[ ], Int_t dParent_pdg[ ], double dPx[ ],double dPy[ ], double  dPz[ ],double dE[ ], double dRPx[ ],double dRPy[ ], double  dRPz[ ],double dvx[ ], double dvy[ ], double dvz[ ], double  dct[ ],double d3Ddca[],double ddcaXY[],double ddcaZ[],double d3DRdca[],double dRdcaXY[],double dRdcaZ[],Int_t Ncent[],double Vtx[],double Vty[],double Vtz[])
{
  if(!particle||!p_mom) 
    return ;
  if(abs(particle->GetPdgCode())!=11) //直接筛选出e
    return;
  
  TVector3 v00;  
  TLorentzVector eMom;  
  //./dataDrivenFastSimulator.h:const Int_t nCentHftRatio = 9;
  //The Math.floor() function returns the largest integer less than or equal to a given number.
  int const cent = floor(nCentHftRatio* gRandom->Rndm()); //就是Math::floor， 返回的是8
  TVector3 const vertex = getVertex(cent); // return TVector3(0., 0., rdmVz); 从一个root file 中的Vz 随centrality的分布中根据centralit 得到vz的分布，从分布中取随机数给Vz
  // TVector3 getVertex(int const centrality)
  // float const gVzCut = 6.0e4;
  
  //  if(vertex.z()<0||vertex.z()>30000) return; //Xiaozhi comments
  //cout<< cent<<endl;
  v00.SetXYZ(particle->Vx()*1000.,particle->Vy()*1000.,particle->Vz()*1000.);
  // v00.SetXYZ(0.,0.,0.); //test the smear dca  

  //------------dcaXy and DCA Z difference check--------------------------------

  //---------------------------------------------------------------------------
  //  if(abs(Parent_pdg)==421)
  // v00=v00*4;// move the d0 dca  points similar to B+ 
    v00+=vertex; //Vz 变了,x,y 还是原来的坐标， 需要将vz改变，

  //  v00+=vertex; 


  particle-> Momentum(eMom);
  TLorentzVector const eRMom = smearMom(0,eMom);//smear Mom, 很简单的smear，就是pt 的mean 值不变，sigma 取指定的，然后从这个高斯分布中随机取pt 就是
  TVector3 const eRPos = smearPosData(0,vertex.z(),cent, eRMom, v00);  //smear pos 从下面这个root file 里面随机取出来smear 的 本code没有对HFTmatch effi 进行smear 也就是说，直接给个Vz 之后再semar， 和LS4Plus 差不多，因为本身Vz的不行，所以就根据有HFT 的vz 来分类（本来DCA就是根据有HFT的vz进行分类的，所以这里参数给的是vertex.z()， 然后与原来的z相加之后再smear）
  //TFile fDca1("/star/data01/pwg/xiao00/backup/Run14/Fast_temp/Smear_File/                                    2DProjection_simCent_NoBinWidth_3D_Dca_VsPt_Centrality_Eta_Phi_Vz_Zdcx_16Jun14.root"); // DCA spatial         resolution
  
  // TVector3 const vertex(0., 0., 0.);
  float const eDca =  dcaSigned(eMom.Vect(), v00, vertex); //计算DCA的符号
  float const eRDca = dcaSigned(eRMom.Vect(), eRPos, vertex);

  // if(abs(Parent_pdg)==421)
  //   v00=3.991870*v00;

  // if(abs(Parent_pdg)==411)
  //   v00=1.573718*v00;

  // if(abs(Parent_pdg)==4122)
  //   v00=8.183*v00;
   
  // if(abs(Parent_pdg)==521)
  //   v00=1.0697*v00;

  float const eDcaXY = dcaXY(eMom.Vect(), v00, vertex);
  float const eRDcaXY = dcaXY(eRMom.Vect(), eRPos, vertex);
   
  float const eDcaZ = dcaZ(eMom.Vect(), v00, vertex);
  float const eRDcaZ = dcaZ(eRMom.Vect(), eRPos, vertex);


  // float const eDcaXY = dcaXY(eMom.Vect(), v00, vertex);
  // float const eRDcaXY = dcaXY(eRMom.Vect(), eRPos, v00);
   
  // float const eDcaZ = dcaZ(eMom.Vect(), v00, vertex);
  // float const eRDcaZ = dcaZ(eRMom.Vect(), eRPos, v00);
   


  // cout<< cent<<"  "<< eRPos.x()<<"  "<<endl;//particle->Px()<<"  "<<fPionMomResolution->Eval(eMom.Py())<<endl;
  // cout<< cent<<"  "<< eRDca<<"  "<<eDca<<endl;//particle->Px()<<"  "<<fPionMomResolution->Eval(eMom.Py())<<endl;
  
  mpdg[Ndaughter]=Parent_pdg;
  mPx[Ndaughter]=p_mom->Px();
  mPy[Ndaughter]=p_mom->Py();
  mPz[Ndaughter]=p_mom->Pz();
  mE[Ndaughter]=p_mom->E();  
  mvx[Ndaughter]=r_pos->X();
  mvy[Ndaughter]=r_pos->Y(); // 存这些parent 粒子的性质都只是为了看下打入的粒子的QA
  mvz[Ndaughter]=r_pos->Z();
  mct[Ndaughter]=r_pos->T();
  dpdg[Ndaughter]=particle->GetPdgCode();
  dParent_pdg[Ndaughter]=particle->GetFirstMother(); //看下这个电子的parent 粒子的pdg 是什么，应该是 = Parent_pdg 的
  dPx[Ndaughter]=particle->Px();
  dPy[Ndaughter]=particle->Py();
  dPz[Ndaughter]=particle->Pz();
  dRPx[Ndaughter]=eRMom.Px();
  dRPy[Ndaughter]=eRMom.Py();
  dRPz[Ndaughter]=eRMom.Pz();
  dE[Ndaughter]=particle->Energy();  
  dvx[Ndaughter]=particle->Vx();
  dvy[Ndaughter]=particle->Vy();
  dvz[Ndaughter]=particle->Vz();
  dct[Ndaughter]=particle->T();
  d3Ddca[Ndaughter]=eDca;
  ddcaXY[Ndaughter]=eDcaXY;
  ddcaZ[Ndaughter]=eDcaZ;
  d3DRdca[Ndaughter]=eRDca;
  dRdcaXY[Ndaughter]=eRDcaXY;
  dRdcaZ[Ndaughter]=eRDcaZ;
  Ncent[Ndaughter]=cent;
  Vtx[Ndaughter]=vertex.x();   
  Vty[Ndaughter]=vertex.y();
  Vtz[Ndaughter]=vertex.z();

  Ndaughter++;
    
}
// void StEvtGenDecayMaker::get_kinematics(Double_t& pt, Double_t& eta, Double_t& phi, Double_t& px, Double_t& py, Double_t& pz)
// {
//   gRandom->SetSeed();
//   //pt = gRandom->Uniform(0,20);
//       pt = Weight_pt->GetRandom();

//     eta = gRandom->Uniform(-accp_eta,accp_eta);

  

//   phi = TMath::TwoPi() * gRandom->Rndm();
//   px = pt * cos(phi);
//   py = pt * sin(phi);
//   pz = pt / tan(2 * atan(exp(-eta)));
// }  // input eta 
void StEvtGenDecayMaker::get_kinematics(Double_t& pt, Double_t& y, Double_t& phi, Double_t& px, Double_t& py, Double_t& pz,Double_t& E,Double_t mass )
{
  gRandom->SetSeed();
  pt = gRandom->Uniform(0,20);
  //  pt = Weight_pt->GetRandom();
  y=D0YVsPty->GetRandom(); // rapidity
  // y = gRandom->Uniform(-accp_eta,accp_eta);
  phi = TMath::TwoPi() * gRandom->Rndm();
  Double_t mT=sqrt(mass*mass+pt*pt);
  
  px = pt * cos(phi);
  py = pt * sin(phi);
  pz=mT*sinh(y);
  E=mT*cosh(y);
  
  // pz = pt / tan(2 * atan(exp(-eta)));
}

void StEvtGenDecayMaker::SaveTree()
{
  mfile->cd();
  Tree->Write();
  mfile->Close();
  
  // Tree->Delete();
  // delete Tree;
}
bool StEvtGenDecayMaker::Continue_Decay(int pdg)
{
  bool bContinue=false;
  if(abs(pdg)%1000/100==4||abs(pdg)%1000/100==5)
    bContinue=true; 
  else  if(abs(pdg)%10000/1000==4||abs(pdg)%10000/1000==5)
    bContinue=true; 
  // bool bContinue=false;
  // if(fabs(pdg)==511) // B0
  //   bContinue=true;
  // if(fabs(pdg)==421) // D0
  //   bContinue=true;
  // if(fabs(pdg)==413) // D*
  //   bContinue=true;
  // if(fabs(pdg)==411) // D+
  //   bContinue=true;
  return bContinue;
}

