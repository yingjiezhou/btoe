#include <float.h>
#include "StHelixD.h"
#include "PhysicalConstants.h" 
#include "SystemOfUnits.h"

StHelixD::StHelixD()
{
    setParameters(0, 0, 0, TVector3(), -1);
}

StHelixD::StHelixD(double c, double d, double phase,
		   const TVector3& o, int h)
{
    setParameters(c, d, phase, o, h);
}

StHelixD::~StHelixD() { /* nop */ };

void StHelixD::setParameters(double c, double dip, double phase,
			    const TVector3& o, int h)
{
    //
    //  The order in which the parameters are set is important
    //  since setCurvature might have to adjust the others.
    //
    mH = (h>=0) ? 1 : -1;    // Default is: positive particle
                             //             positive field
    mOrigin   = o;
    setDipAngle(dip);
    setPhase(phase);

    //
    // Check for singularity and correct for negative curvature.           
    // May change mH and mPhase. Must therefore be set last.
    //
    setCurvature(c);         

    //
    // For the case B=0, h is ill defined. In the following we
    // always assume h = +1. Since phase = psi - h * pi/2
    // we have to correct the phase in case h = -1.
    // This assumes that the user uses the same h for phase
    // as the one he passed to the constructor.
    //
    if (mSingularity && mH == -1) {
	mH = +1;
	setPhase(mPhase-M_PI);
    }
}

void StHelixD::setCurvature(double val)
{
    if (val < 0) {
	mCurvature = -val;
	mH = -mH;
	setPhase(mPhase+M_PI);
    }
    else
	mCurvature = val;

    if (fabs(mCurvature) <= static_cast<double>(0))    
	mSingularity = 1;		// straight line
    else
	mSingularity = 0;          	// curved
}

void StHelixD::setPhase(double val)
{
    mPhase       = val;
    mCosPhase    = cos(mPhase);
    mSinPhase    = sin(mPhase);
    if (fabs(mPhase) > M_PI)
	mPhase = atan2(mSinPhase, mCosPhase);  // force range [-pi,pi]
}

void StHelixD::setDipAngle(double val)
{
    mDipAngle    = val;
    mCosDipAngle = cos(mDipAngle);
    mSinDipAngle = sin(mDipAngle);
}

double StHelixD::xcenter() const
{
    if (mSingularity)
	return 0;
    else
	return mOrigin.x()-mCosPhase/mCurvature;
}

double StHelixD::ycenter() const
{
    if (mSingularity)
	return 0;
    else
	return mOrigin.y()-mSinPhase/mCurvature;
}

double StHelixD::fudgePathLength(const TVector3& p) const
{
    double s;
    double dx = p.x()-mOrigin.x();
    double dy = p.y()-mOrigin.y();
    
    if (mSingularity) {
	s = (dy*mCosPhase - dx*mSinPhase)/mCosDipAngle;
    }
    else {
	s = atan2(dy*mCosPhase - dx*mSinPhase,
		  1/mCurvature + dx*mCosPhase+dy*mSinPhase)/
	    (mH*mCurvature*mCosDipAngle);
    }
    return s;
}

double StHelixD::distance(const TVector3& p) const
{
    return (this->at(pathLength(p))-p).Mag();
}

double StHelixD::pathLength(const TVector3& p) const 
{
    //
    //  Returns the path length at the distance of closest 
    //  approach between the helix and point p. 
    //  For the case of B=0 (straight line) the path length
    //  can be calculated analytically. For B>0 there is
    //  unfortunately no easy solution to the problem.
    //  Here we use the Newton method to find the root of the
    //  referring equation. The 'fudgePathLength' serves
    //  as a starting value.
    //
    double s;
    double dx = p.x()-mOrigin.x();
    double dy = p.y()-mOrigin.y();
    double dz = p.z()-mOrigin.z();

    if (mSingularity) {
	s = mCosDipAngle*(mCosPhase*dy-mSinPhase*dx) +
	    mSinDipAngle*dz;
    }
    else { //
#ifndef ST_NO_NAMESPACES
      {
	using namespace units;
#endif
      const double MaxPrecisionNeeded = micrometer;
      const int    MaxIterations      = 100;
      
      //
      // The math is taken from Maple with C(expr,optimized) and
      // some hand-editing. It is not very nice but efficient.
      //
      double t34 = mCurvature*mCosDipAngle*mCosDipAngle;
      double t41 = mSinDipAngle*mSinDipAngle;
      double t6, t7, t11, t12, t19;
      
      //
      // Get a first guess by using the dca in 2D. Since
      // in some extreme cases we might be off by n periods
      // we add (subtract) periods in case we get any closer.
      // 
      s = fudgePathLength(p);
      
      double ds = period();
      int    j, jmin = 0;
      double d, dmin = (at(s) - p).Mag();
      for(j=1; j<MaxIterations; j++) {
	if ((d = (at(s+j*ds) - p).Mag()) < dmin) {
	  dmin = d;
	  jmin = j;
	}
	else
	  break;
      }
      for(j=-1; -j<MaxIterations; j--) {
	if ((d = (at(s+j*ds) - p).Mag()) < dmin) {
	  dmin = d;
	  jmin = j;
	}
	else
	  break;
	    }
      if (jmin) s += jmin*ds;
      
      //
      // Newtons method:
      // Stops after MaxIterations iterations or if the required
      // precision is obtained. Whatever comes first.
      //
      double sOld = s;
      for (int i=0; i<MaxIterations; i++) {
	t6  = mPhase+s*mH*mCurvature*mCosDipAngle;
	t7  = cos(t6);
	t11 = dx-(1/mCurvature)*(t7-mCosPhase);
	t12 = sin(t6);
	t19 = dy-(1/mCurvature)*(t12-mSinPhase);
	s  -= (t11*t12*mH*mCosDipAngle-t19*t7*mH*mCosDipAngle -
	       (dz-s*mSinDipAngle)*mSinDipAngle)/
	  (t12*t12*mCosDipAngle*mCosDipAngle+t11*t7*t34 +
	   t7*t7*mCosDipAngle*mCosDipAngle +
	   t19*t12*t34+t41);
	if (fabs(sOld-s) < MaxPrecisionNeeded) break;
	sOld = s;
      }
#ifndef ST_NO_NAMESPACES
      }
#endif
    }
    return s;
}

double StHelixD::period() const
{
  if (mSingularity)
    return 3.e+33;
  else	
    return fabs(2*M_PI/(mH*mCurvature*mCosDipAngle)); 
}

pairD StHelixD::pathLength(double r) const
{
  pairD value;
  pairD VALUE(999999999.,999999999.);
  //
  // The math is taken from Maple with C(expr,optimized) and
  // some hand-editing. It is not very nice but efficient.
  // 'first' is the smallest of the two solutions (may be negative)
  // 'second' is the other.
  //
  if (mSingularity) {
    double t1 = mCosDipAngle*(mOrigin.x()*mSinPhase-mOrigin.y()*mCosPhase);
    double t12 = mOrigin.y()*mOrigin.y();
    double t13 = mCosPhase*mCosPhase;
    double t15 = r*r;
    double t16 = mOrigin.x()*mOrigin.x();
    double t20 = (-mCosDipAngle*mCosDipAngle*(2.0*mOrigin.x()*mSinPhase*mOrigin.y()*mCosPhase +
					      t12-t12*t13-t15+t13*t16));
    if(t20<0.) return VALUE;
    t20 = ::sqrt(t20);
    value.first  = (t1-t20)/(mCosDipAngle*mCosDipAngle);
    value.second = (t1+t20)/(mCosDipAngle*mCosDipAngle);
    }
  else {
    double t1 = mOrigin.y()*mCurvature;
    double t2 = mSinPhase;
    double t3 = mCurvature*mCurvature;
    double t4 = mOrigin.y()*t2;
    double t5 = mCosPhase;
    double t6 = mOrigin.x()*t5;
    double t8 = mOrigin.x()*mOrigin.x();
    double t11 = mOrigin.y()*mOrigin.y();
    double t14 = r*r;
    double t15 = t14*mCurvature;
    double t17 = t8*t8;
    double t19 = t11*t11;
    double t21 = t11*t3;
    double t23 = t5*t5;
    double t32 = t14*t14;
    double t35 = t14*t3;
    double t38 = 8.0*t4*t6 - 4.0*t1*t2*t8 - 4.0*t11*mCurvature*t6 +
      4.0*t15*t6 + t17*t3 + t19*t3 + 2.0*t21*t8 + 4.0*t8*t23 -
      4.0*t8*mOrigin.x()*mCurvature*t5 - 4.0*t11*t23 -
      4.0*t11*mOrigin.y()*mCurvature*t2 + 4.0*t11 - 4.0*t14 +
      t32*t3 + 4.0*t15*t4 - 2.0*t35*t11 - 2.0*t35*t8;
    double t40 = (-t3*t38);
    if (t40<0.0) return VALUE;
    t40 = ::sqrt(t40);
    double t43 = mOrigin.x()*mCurvature;
    double t45 = 2.0*t5 - t35 + t21 + 2.0 - 2.0*t1*t2 -2.0*t43 - 2.0*t43*t5 + t8*t3;
    double t46 = mH*mCosDipAngle*mCurvature;
    
    value.first = (-mPhase + 2.0*atan((-2.0*t1 + 2.0*t2 + t40)/t45))/t46;
    value.second = -(mPhase + 2.0*atan((2.0*t1 - 2.0*t2 + t40)/t45))/t46;
    
    //
    //   Solution can be off by +/- one period, select smallest
    //
    double p = period();
    if (!isnan(value.first)) {
      if (fabs(value.first-p) < fabs(value.first)) value.first = value.first-p;
      else if (fabs(value.first+p) < fabs(value.first)) value.first = value.first+p;
    }
    if (!isnan(value.second)) {
      if (fabs(value.second-p) < fabs(value.second)) value.second = value.second-p;
      else if (fabs(value.second+p) < fabs(value.second)) value.second = value.second+p;
    }
  }
  if (value.first > value.second) {
    double tmp = value.first;
    value.first = value.second;
    value.second = tmp;
  }
  return(value);
}

pairD StHelixD::pathLength(double r, double x, double y) 
{   
  double x0 = mOrigin.x();
  double y0 = mOrigin.y();
  mOrigin.SetX(x0-x);
  mOrigin.SetY(y0-y);
  pairD result = this->pathLength(r);
  mOrigin.SetX(x0);
  mOrigin.SetY(y0);
  return result;
}

double StHelixD::pathLength(const TVector3& r,
			    const TVector3& n) const
{
  //
  // Vector 'r' defines the position of the center and
  // vector 'n' the normal vector of the plane.
  // For a straight line there is a simple analytical
  // solution. For curvatures > 0 the root is determined
  // by Newton method. In case no valid s can be found
  // the max. largest value for s is returned.
  //
  double s;
  const double NoSolution = 3.e+33;
  
  if (mSingularity) {
    double t = n.z()*mSinDipAngle +
      n.y()*mCosDipAngle*mCosPhase -
      n.x()*mCosDipAngle*mSinPhase;
    if (t == 0)
      s = NoSolution;
    else
      s = (r*n - mOrigin*n)/t;
  }
  else {
    const double MaxPrecisionNeeded = micrometer;
    const int    MaxIterations      = 20;
    
    double A = mCurvature*(mOrigin*n - r*n) -
      n.x()*mCosPhase - 
      n.y()*mSinPhase;
    double t = mH*mCurvature*mCosDipAngle;
    
    double a, f, fp;
    double sOld = s = 0;  
    //		(cos(angMax)-1)/angMax = 0.1
    const double angMax = 0.21;
    int maxSteps = int((6.28/angMax)*1.1);
    double deltas = fabs(angMax/mCurvature/mCosDipAngle);
    
    for (int i=0; i<MaxIterations; i++) {
      if (i == MaxIterations) return NoSolution;
      a  = t*s+mPhase;
      f  = A +
	n.x()*cos(a) +
	n.y()*sin(a) +
	n.z()*mCurvature*mSinDipAngle*s;
      fp = -n.x()*sin(a)*t +
	n.y()*cos(a)*t +
	n.z()*mCurvature*mSinDipAngle;
      if ( fabs(fp)*deltas <= fabs(f) ) { //too big step
	i--;if ((maxSteps--)<0) return NoSolution;
	int sgn = 1;
	if (fp<0.) sgn = -sgn;
	if (f <0.) sgn = -sgn;
	s -= sgn*deltas;
      } else {
	s -= f/fp;
      }
      if (fabs(sOld-s) < MaxPrecisionNeeded) break;
      sOld = s;
    }
  }
  return s;
}

pairD
StHelixD::pathLengths(const StHelixD& h) const
{
  const double NoSolution = 3.e+33;
  
  //
  //	Cannot handle case where one is a helix
  //  and the other one is a straight line.
  //
  if (mSingularity != h.mSingularity) 
    return pairD(NoSolution, NoSolution);
  
  double s1, s2;
  
  if (mSingularity) {
    //
    //  Analytic solution
    //
    TVector3 dv = h.mOrigin - mOrigin;
    TVector3 a(-mCosDipAngle*mSinPhase,
	       mCosDipAngle*mCosPhase,
	       mSinDipAngle);
    TVector3 b(-h.mCosDipAngle*h.mSinPhase,
	       h.mCosDipAngle*h.mCosPhase,
	       h.mSinDipAngle);	
    double ab = a*b;
    double g  = dv*a;
    double k  = dv*b;
    s2 = (k-ab*g)/(ab*ab-1.);
    s1 = g+s2*ab;
    return pairD(s1, s2);
  }
  else {	
    //
    //  First step: get dca in the xy-plane as start value
    //
    double dx = h.xcenter() - xcenter();
    double dy = h.ycenter() - ycenter();
    double dd = ::sqrt(dx*dx + dy*dy);
    double r1 = 1/curvature();
    double r2 = 1/h.curvature();
    
    double cosAlpha = (r1*r1 + dd*dd - r2*r2)/(2*r1*dd);
    
    double s;
    double x, y;
    if (fabs(cosAlpha) < 1) {           // two solutions
      double sinAlpha = sin(acos(cosAlpha));
      x = xcenter() + r1*(cosAlpha*dx - sinAlpha*dy)/dd;
      y = ycenter() + r1*(sinAlpha*dx + cosAlpha*dy)/dd;
      s = pathLength(x, y);
      x = xcenter() + r1*(cosAlpha*dx + sinAlpha*dy)/dd;
      y = ycenter() + r1*(cosAlpha*dy - sinAlpha*dx)/dd;
      double a = pathLength(x, y);
      if (h.distance(at(a)) < h.distance(at(s))) s = a;
    }
    else {                              // no intersection (or exactly one)
      x = xcenter() + r1*dx/dd;
      y = ycenter() + r1*dy/dd;
      s = pathLength(x, y);
    }

    //
    //   Second step: scan in decreasing intervals around seed 's'
    // 
    const double MinStepSize = 10*micrometer;
    const double MinRange    = 10*centimeter;    
    double dmin              = h.distance(at(s));
    double range             = 2*dmin > MinRange ? 2*dmin : MinRange;
    s1                       = s - range/2.;
    s2                       = s + range/2.;
    double ds                = range/10;
    double slast=999999, ss, d;
    
    while (ds > MinStepSize && ds < 1.e+10) {
      for (ss=s1; ss<s2+ds; ss+=ds) {
	d = h.distance(at(ss));
	if (d < dmin) {
	  dmin = d;
	  s = ss;
	}
	slast = ss;
      }
      //
      //  In the rare cases where the minimum is at the
      //  the border of the current range we shift the range
      //  and start all over, i.e we do not decrease 'ds'.
      //  Else we decrease the search intervall around the
      //  current minimum and redo the scan in smaller steps.
      //
      if (s == s1) {
	d = 0.8*(s2-s1);
	s1 -= d;
	s2 -= d;
      }
      else if (s == slast) {
	d = 0.8*(s2-s1);
	s1 += d;
	s2 += d;
      }
      else {           
	s1 = s-ds;
	s2 = s+ds;
	ds /= 10;
      }
    }
    if(ds > 1.e+10) return pairD(NoSolution, NoSolution);
    return pairD(s, h.pathLength(at(s)));
  }
}

int StHelixD::valid(double WorldSize) const
{
  
  if (!::finite(mDipAngle    )) 	return 0;
  if (!::finite(mH           )) 	return 0;
  if (!::finite(mCurvature   )) 	return 0;
  if (::fabs(mCurvature) > WorldSize)	return 0;
  
  //  if (!mOrigin.valid(WorldSize))      return 0;
  for(int i=0;i<3;i++) {
    if(!::finite(mOrigin[i])) return 0;
    if(::fabs(mOrigin[i])>WorldSize) return 0;
  }
  double qwe = ::fabs(::fabs(mDipAngle)-M_PI/2);
  if (qwe < 1./WorldSize      ) 	return 0; 
  if (fabs(mH) != 1            )       return 0; 
  if (mCurvature < 0          )	return 0;
  
  return 1;
}

void StHelixD::moveOrigin(double s)
{
  if (mSingularity)
    mOrigin	= at(s);
  else {
    TVector3 newOrigin = at(s);
    double newPhase = atan2(newOrigin.y() - ycenter(),
			    newOrigin.x() - xcenter());
    mOrigin = newOrigin;
    setPhase(newPhase);	        
  }
}

int operator== (const StHelixD& a, const StHelixD& b)
{
  //
  // Checks for numerical identity only !
  //
  return (a.origin()    == b.origin()    &&
	  a.dipAngle()  == b.dipAngle()  &&
	  a.curvature() == b.curvature() &&
	  a.phase()     == b.phase()     &&
	  a.h()         == b.h());
}

int operator!= (const StHelixD& a, const StHelixD& b) {return !(a == b);}

ostream& operator<<(ostream& os, const StHelixD& h)
{
  return os << " helix : -- ";
  /*
	    << "curvature = "  << h.curvature() << ", " 
	    << "dip angle = "  << h.dipAngle()  << ", "
	    << "phase = "      << h.phase()     << ", "  
	    << "h = "          << h.h()         << ", "    
	    << "origin = "     << h.origin()    << endl;
  */
}

