#include "TParticleMc.h"
#include <iostream>
#include <TMath.h>


using namespace std;

ClassImp(TParticleMc);

//..
TParticleMc::TParticleMc(){;}


//..
TParticleMc::TParticleMc(const float px_in,
                     const float py_in, 
                     const float pz_in, 
                     const float pt_in,
                     const float eta_in,
                     const float x_in, 
                     const float y_in, 
                     const float z_in, 
                     const float energy_in, 
                     const int KF_in, 
                     const int KS_in, 
                     const float ppx_in, 
                     const float ppy_in, 
                     const float ppz_in, 
                     const float xp_in, 
                     const float yp_in, 
                     const float zp_in, 
                     const float penergy_in, 
                     const int pKF_in, 
                     const int pKS_in,
		     const int parentId_in)
{
    px = px_in;
    py = py_in;
    pz = pz_in;
    pt = pt_in;
    eta = eta_in;
    x = x_in;
    y = y_in;
    z = z_in;
    energy = energy_in;
    KF = KF_in;
    KS = KS_in;
    ppx = ppx_in;
    ppy = ppy_in;
    ppz = ppz_in;
    xp = xp_in;
    yp = yp_in;
    zp = zp_in;
    penergy = penergy_in;
    pKF = pKF_in;
    pKS = pKS_in;
    parentId = parentId_in;
}

//________
TParticleMc::TParticleMc(const TParticleMc& in)
{
    px = in.px; 
    py = in.py ;
    pz = in.pz ;
    pt = in.pt;
    eta = in.eta;
    x = in.x  ;
    y = in.y  ;
    z = in.z ;
    energy = in.energy ;
    KF = in.KF ;
    KS = in.KS ;
    ppx = in.ppx ;
    ppy = in.ppy ;
    ppz = in.ppz ;
    xp = in.xp ;
    yp = in.yp ;
    zp = in.zp ;
    penergy = in.penergy ;
    pKF = in.pKF ;
    pKS = in.pKS ;
    parentId = in.parentId; 
    phi = in.phi;	
}

//________
float TParticleMc::get_phi()
{
	if (px==0.0 && py== 0.0)return 0;
	else return TMath::ATan2(py,px) + TMath::Pi(); 
}
