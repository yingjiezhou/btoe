
//const int mh2Nhist=4;
const int Npt=8;
Double_t  ptbin[Npt+1]={1,1.2,1.5,2,2.5,3.5,4.5,5.5,8.5};


/* TString mh1Title[Npt]={"1<p_{T} < 1.2 (GeV/c)", */
/* 		       "1.2<p_{T} < 1.5 (GeV/c)",  */
/* 		       "1.5<p_{T} < 2 (GeV/c)", */
/* 		       "2<p_{T} < 3 (GeV/c)", */
/* 		       "3<p_{T} < 4 (GeV/c)", */
/* 		       "4<p_{T} < 6 (GeV/c)", */
/* 		       "6<p_{T} < 9 (GeV/c)"}; */

TString mh1Title[Npt]={"1<p_{T} < 1.2 (GeV/c)",
		       "1.2<p_{T} < 1.5 (GeV/c)",
		       "1.5<p_{T} < 2 (GeV/c)",
		       "2<p_{T} < 2.5 (GeV/c)",
		       "2.5<p_{T} < 3.5 (GeV/c)",
		       "3.5<p_{T} < 4.5 (GeV/c)",
		       "4.5<p_{T} < 5.5 (GeV/c)",
		       "5.5<p_{T} < 8.5 (GeV/c)"};



/* Int_t Xbin_ptlow[Npt]= {11,13,17,21,31,41};//,51,61,80}; */
/* Int_t Xbin_pthigh[Npt]={12,16,20,30,40,80};//;50,60,80,120}; */

Int_t Xbin_ptlow[Npt]= {21,25,31,41,51,71,91,111};
Int_t Xbin_pthigh[Npt]={24,30,40,50,70,90,110,170};

/* Int_t Xbin_ptlow[Npt]= {31,41,51,71,91,111}; */
/* Int_t Xbin_pthigh[Npt]={40,50,70,90,110,170}; */



//belwow bingning only for pi
Int_t Xbin_ptlow_data[Npt]= {13,17,21};
Int_t Xbin_pthigh_data[Npt]={12,16,20,23};

const Double_t DcaEdgeDca[] = {-0.1, -0.09,-0.08,-0.07, -0.06, -0.05 , -0.045 , -0.04 , -0.035 , -0.03,  -0.025 , -0.02,-0.018,-0.016,-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014,0.016,0.018,0.02 ,0.025  , 0.03 , 0.035  , 0.04 , 0.045 , 0.05, 0.06 ,  0.07, 0.08, 0.09,0.1};
const int  nDcasDca = sizeof(DcaEdgeDca) / sizeof(Double_t) - 1;
/*
const int  nDcasDca = 54;
Double_t const  DcaEdgeDca[nDcasDca+1] = {-0.1   , -0.09 ,     -0.08  ,   -0.07    , -0.06    , -0.05 , -0.0475 , -0.045 , -0.0425 , -0.04 , -0.0375 , -0.035 , -0.0325 , -0.03 , -0.0275 , -0.025 , -0.0225 , -0.02,-0.018,-0.016,-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014,0.016,0.018,0.02 ,0.0225 , 0.025 , 0.0275 , 0.03 , 0.0325 , 0.035 , 0.0375 , 0.04 , 0.0425 , 0.045 , 0.0475 , 0.05    , 0.06  ,  0.07    , 0.08    , 0.09   ,0.1}; 
*/

/*
const int  nDcasDca = 52;
Double_t const  DcaEdgeDca[nDcasDca+1] = {-0.1,-0.095,-0.09,-0.085,-0.08,-0.075,-0.07,-0.065,-0.06,-0.055,-0.05,-0.045,-0.04,-0.035,-0.03,-0.025,-0.02,-0.018,-0.016,-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014,0.016,0.018,0.02,0.025,0.03,0.035,0.04,0.045,0.05,0.055,0.06,0.065,0.07,0.075,0.08,0.085,0.09,0.095,0.1};
*/
