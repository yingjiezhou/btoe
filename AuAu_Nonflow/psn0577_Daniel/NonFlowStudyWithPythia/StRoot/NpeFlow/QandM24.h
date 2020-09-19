//
//
//
// Li Yi
//
//
//
// 2012.01.12
// Q, Moment2, Moment4
// Qvector() function:
// input:
// 	nharmo:		nharmo's Q vector
// 	n:		number of particles
// 	phi[]:		particle azimuthal phi angle array. legth is n
// 
// output:
//	Qcos:		real part of Q vector
//	Qsin:		imaginary part of Q vector
//	
//
//
// Based on Moment24.h
// 2012.01.09
//
//
//


#include <iostream>
using namespace std;

void Qvector(int nharmo, int n, double phi[],double & Qcos, double & Qsin);

double Moment2(int n, double Qcos, double Qsin);	//<2> two particles from same region

double Moment2(int na, double Qcosa, double Qsina, int nb, double Qcosb, double Qsinb);	//<2'> one particle from one region. the other from another exclusive region

double Moment4(int n, double Qcos, double Qsin, double Qcos2, double Qsin2);	// <4> four particles from the same region

double Moment4_22type(int na, double Qcosa, double Qsina, double Qcosa2, double Qsina2, int nb, double Qcosb, double Qsinb, double Qcosb2, double Qsinb2);	//<4'> two particles from one region. other 2 from another exclusive region

double Moment4_13type(int na, double Qcosa, double Qsina, int nb, double Qcosb, double Qsinb, double Qcosb2, double Qsinb2);	// <4'> one particle from one region. other 3 from another exclusive region







void Qvector(int nharmo, int n, double phi[],double & Qcos, double & Qsin) {
	double Sin = 0, Cos = 0;

	for(int i = 0; i<n ; i++) {
		Sin+=TMath::Sin(phi[i]*nharmo);
		Cos+=TMath::Cos(phi[i]*nharmo);
	}

	Qcos = Cos;
	Qsin = Sin;
}


double Moment2(int n, double Qcos, double Qsin)	{
	double QQstar;
	double Npair;

	QQstar = Qcos*Qcos + Qsin*Qsin;
	Npair = 1.0*n*(n-1);

	double M2;

	M2 = (QQstar-n)/Npair;
	
	return M2;
}

double Moment2(int na, double Qcosa, double Qsina, int nb, double Qcosb, double Qsinb)	{
	double Npair;
	double ReQaQbstar;

	ReQaQbstar = Qcosb*Qcosa + Qsinb*Qsina;
	Npair = 1.0*na*nb;

	double M2;

	M2 = ReQaQbstar/Npair;

	return M2;

}


double Moment4(int n, double Qcos, double Qsin, double Qcos2, double Qsin2)	{
	double QQQstarQstar, Q2Q2star, ReQ2QstarQstar, QQstar;
	double Nquad;

	QQQstarQstar = TMath::Power(Qcos,4) + TMath::Power(Qsin, 4) + 2.0*Qcos*Qcos*Qsin*Qsin;
	Q2Q2star = Qcos2*Qcos2 + Qsin2*Qsin2;
	ReQ2QstarQstar = Qcos2*Qcos*Qcos - Qcos2*Qsin*Qsin + 2.0*Qsin2*Qsin*Qcos;
	QQstar = Qcos*Qcos + Qsin*Qsin;

	Nquad = 1.0*n*(n-1)*(n-2)*(n-3);

	
	double M4;

	M4 = (QQQstarQstar + Q2Q2star - 2.0*ReQ2QstarQstar - 4.0*(n-2)*QQstar + 2.0*n*(n-3))/Nquad;

	return M4;
}

double Moment4_22type(int na, double Qcosa, double Qsina, double Qcosa2, double Qsina2, int nb, double Qcosb, double Qsinb, double Qcosb2, double Qsinb2) {

	double ReQaQaQbstarQbstar, ReQaQaQ2bstar, ReQ2aQbstarQbstar, ReQ2aQ2bstar;
	double Nquad;


	ReQaQaQbstarQbstar = Qsina*Qsina*Qsinb*Qsinb - Qsina*Qsina*Qcosb*Qcosb -Qcosa*Qcosa*Qsinb*Qsinb + Qcosa*Qcosa*Qcosb*Qcosb + 4.0*Qsina*Qcosa*Qsinb*Qcosb;
	ReQaQaQ2bstar = -Qsina*Qsina*Qcosb2 + Qcosa*Qcosa*Qcosb2 +2.0*Qsina*Qcosa*Qsinb2;
	ReQ2aQbstarQbstar = Qcosa2*Qcosb*Qcosb - Qcosa2*Qsinb*Qsinb + 2.0*Qsina2*Qcosb*Qsinb;
	ReQ2aQ2bstar = Qsina2*Qsinb2 + Qcosa2*Qcosb2;

	Nquad = 1.0*na*(na-1)*nb*(nb-1);

	double M4;

	M4 = (ReQaQaQbstarQbstar - ReQaQaQ2bstar - ReQ2aQbstarQbstar + ReQ2aQ2bstar)/Nquad;
	
	return M4;
}


double Moment4_13type(int na, double Qcosa, double Qsina, int nb, double Qcosb, double Qsinb, double Qcosb2, double Qsinb2) {
	double ReQaQbQbstarQbstar, ReQaQbQ2bstar, ReQaQbstar, QbQbstar;
	double Nquad;

	ReQaQbQbstarQbstar = Qcosa*TMath::Power(Qcosb,3) + TMath::Power(Qcosb,2)*Qsina*Qsinb + Qcosa*Qcosb*TMath::Power(Qsinb,2) + Qsina*TMath::Power(Qsinb,3);
	ReQaQbQ2bstar = Qcosa*Qcosb*Qcosb2 - Qcosb2*Qsina*Qsinb + Qcosb*Qsina*Qsinb2 + Qcosa*Qsinb*Qsinb2;
	ReQaQbstar = Qcosa*Qcosb + Qsina*Qsinb;


	Nquad = 1.0*na*nb*(nb-1)*(nb-2);

	double M4;

	M4 = (ReQaQbQbstarQbstar - ReQaQbQ2bstar - 2.0*(nb-1)*ReQaQbstar)/Nquad;


	return M4;
}




