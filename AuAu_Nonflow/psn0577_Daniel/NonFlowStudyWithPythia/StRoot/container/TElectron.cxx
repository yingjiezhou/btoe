#include "TElectron.h"
#include <iostream>

using namespace std;

ClassImp(TElectron);

//..
TElectron::TElectron(const float px_in, 
                     const float py_in, 
                     const float pz_in, 
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
                     const int pid_in, 
                     const int aKF_in, 
                     const bool accp_in) 
{
    px = px_in;
    py = py_in;
    pz = pz_in;
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
    pid = pid_in;
    aKF = aKF_in;
    accp = accp_in;
}

//________
TElectron::TElectron(const TElectron& in) 
{
    px = in.px; 
    py = in.py ;
    pz = in.pz ;
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
    pid = in.pid ;
    aKF = in.aKF ;
    accp = in.accp ;

}
