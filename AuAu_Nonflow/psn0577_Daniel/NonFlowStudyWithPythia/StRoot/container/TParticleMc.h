#include <TObject.h>

class TParticleMc:public TObject
{
    private: 
        float px;  
        float py; 
        float pz; 
        float pt;
        float eta;
        float x;  //.. origin 
        float y; 
        float z; 
        float energy; 
        float KF; 
        float KS; 
        //.. the following is for parent
        float ppx; //. parent px
        float ppy; 
        float ppz; 
        float xp;  //.. parent origin
        float yp; 
        float zp; 
        float penergy; //
        float pKF; 
        float pKS;
	float parentId;
	float phi;


    public:
        TParticleMc();
	//virtual ~TParticleMc(){};
        TParticleMc(const TParticleMc& in);

        TParticleMc(
                const float px_in, 
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
		const int parentId_in);

        float get_px() const  {return px;} 
        float get_py()  const {return py;} 
        float get_pz()  const {return pz;} 
        float get_pt()  const {return pt;}
        float get_eta()  const {return eta;}
        float get_x()  const {return x;} 
        float get_y()  const {return y;} 
        float get_z()  const {return z;} 
        float get_energy()  const {return energy;} 
        int get_KF()  const {return KF;} 
        int get_KS()  const {return KS;} 
        float get_ppx()  const {return ppx;} 
        float get_ppy()  const {return ppy;} 
        float get_ppz()  const {return ppz;} 
        float get_xp()  const {return xp;} 
        float get_yp()  const {return yp;} 
        float get_zp()  const {return zp;} 
        float get_penergy()  const {return penergy;} 
	float get_phi();
        int get_pKF()  const {return pKF;} 
        int get_pKS()  const {return  pKS;}
        int get_parentId()  const {return  parentId;}

	void set_phi(float a){ phi = a;};


        ClassDef(TParticleMc, 2)
};
