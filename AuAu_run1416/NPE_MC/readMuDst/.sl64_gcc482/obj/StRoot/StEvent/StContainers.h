/***************************************************************************
 *
 * $Id: StContainers.h,v 2.40 2015/11/25 16:53:36 perev Exp $
 *
 * Author: Thomas Ullrich, Oct 1999
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StContainers.h,v $
 * Revision 2.40  2015/11/25 16:53:36  perev
 * Backward
 *
 * Revision 2.38  2015/10/02 19:48:53  ullrich
 * Added Rps tracks and points
 *
 * Revision 2.37  2015/09/01 18:29:01  ullrich
 * Changes due to adding StFpsSlat and interconnection between slats and points.
 *
 * Revision 2.36  2015/05/13 17:06:13  ullrich
 * Added hooks and interfaces to Sst detector (part of HFT).
 *
 * Revision 2.35  2015/02/14 18:57:24  ullrich
 * Big upgrade after adding StFmPoint and StFmsCluster.
 *
 * Revision 2.34  2014/04/10 16:00:12  jeromel
 * Changes to inlcude Ist structure (Thomas OK-ed / may revisit some comments)
 *
 * Revision 2.33  2013/07/23 11:21:49  jeromel
 * Undo past week changes
 *
 * Revision 2.31  2013/04/10 19:15:52  jeromel
 * Step back from StEvent changes - previous change recoverable [Thomas OK-ed]
 *
 * Revision 2.29  2013/03/05 14:42:45  ullrich
 * Added StPxl hits and Containers.
 *
 * Revision 2.28  2012/04/16 20:22:16  ullrich
 * Changes necessary to add Fgt package.
 *
 * Revision 2.27  2012/01/24 02:57:05  perev
 * Etr detector added
 *
 * Revision 2.26  2011/04/25 21:24:33  ullrich
 * Added containers for MTD.
 *
 * Revision 2.25  2011/02/01 19:47:36  ullrich
 * Added HLT branch and hooks.
 *
 * Revision 2.24  2010/01/08 22:43:44  ullrich
 * Updates needed to add StFmsCollection and related classes.
 *
 * Revision 2.23  2009/11/23 22:22:25  ullrich
 * Minor cleanup performed and hooks for RPS added.
 *
 * Revision 2.22  2008/12/22 20:36:52  ullrich
 * Added hooks for new ToF (BTof)
 *
 * Revision 2.21  2006/01/19 21:50:40  ullrich
 * Added RnD containers.
 *
 * Revision 2.20  2005/04/11 22:35:25  calderon
 * Tof Classes for Run 5.  Modifications and additions from Xin to
 * take care of new TOF daq and electronics.  Added StTofRawData and
 * modified containers and includes.
 *
 * Revision 2.19  2004/03/01 17:44:37  fisyak
 * Add Print method
 *
 * Revision 2.18  2003/10/25 00:15:02  fisyak
 * remove StPhmdHit and StPhmdCluster added by mistake
 *
 * Revision 2.16  2003/05/21 18:22:46  ullrich
 * Major Revision of ToF classes (F. Geurts)
 *
 * Revision 2.15  2002/12/20 22:34:42  ullrich
 * Added containers for PMD hits and clusters.
 *
 * Revision 2.14  2001/12/01 15:39:19  ullrich
 * Added macros for StDetectorState.
 *
 * Revision 2.13  2001/11/10 23:53:22  ullrich
 * Added calibration vertices.
 *
 * Revision 2.12  2001/10/01 19:40:31  ullrich
 * Added StTofData.
 *
 * Revision 2.11  2001/08/02 01:27:09  ullrich
 * Added containers for StL3AlgorithmInfo.
 *
 * Revision 2.10  2001/04/16 20:29:46  ullrich
 * Added Tof containers.
 *
 * Revision 2.9  2001/03/14 02:29:17  ullrich
 * Added StPsd container.
 *
 * Revision 2.8  2000/11/25 11:52:23  lasiuk
 * addition of Rich Photon Info
 *
 * Revision 2.7  2000/09/28 10:56:35  ullrich
 * Added Rich PID classes.
 *
 * Revision 2.6  2000/06/19 01:32:15  perev
 *  Thomas StEvent branches added
 *
 * Revision 2.5  2000/05/22 21:42:44  ullrich
 * Add RICH related classes.
 *
 * Revision 2.4  2000/03/23 22:24:06  akio
 * Initial version of Emc Point, and Inclusion of track pointers
 *
 * Revision 2.3  2000/02/23 17:35:57  ullrich
 * Changes due to the addition of the EMC to StEvent
 *
 * Revision 2.2  2000/01/05 16:02:23  ullrich
 * SSD hits added to StEvent.
 *
 * Revision 2.1  1999/10/28 22:06:19  ullrich
 * Initial Revision
 *
 **************************************************************************/
#ifndef StContainers_hh
#define StContainers_hh
#include "StArray.h"

class StBTofHit;
class StBTofRawHit;
class StCalibrationVertex;
class StDetectorState;
class StEmcCluster;
class StEmcPoint;
class StEmcRawHit;
class StEtrHit;
class StFgtHit;
class StFgtPoint;
class StFgtStrip;
class StFmsCluster;
class StFmsHit;
class StFmsPoint;
class StFpsSlat;
class StFtpcHit;
class StHit;
class StHltBEmcTowerHit;
class StHltBTofHit;
class StHltDiElectron;
class StHltHeavyFragment;
class StHltHighPt;
class StHltTrack;
class StHltTrackNode;
class StHltTriggerReason;
class StHltVpdHit;
class StIstHit;
class StKinkVertex;
class StL3AlgorithmInfo;
class StMtdHit;
class StMtdRawHit;
class StObject;
class StPhmdCluster;
class StPhmdCluster;
class StPhmdHit;
class StPhmdHit;
class StPrimaryTrack;
class StPrimaryVertex;
class StPsd;
class StPxlHit;
class StRichCluster;
class StRichHit;
class StRichMCInfo;
class StRichPhotonInfo;
class StRichPid;
class StRichPixel;
class StRnDHit;
class StRpsCluster;
class StRpsTrack;
class StRpsTrackPoint;
class StSsdHit;
class StSstHit;
class StSvtHit;
class StTofCell;
class StTofData;
class StTofHit;
class StTofRawData;
class StTofSlat;
class StTpcHit;
class StTrack;
class StTrackDetectorInfo;
class StTrackNode;
class StTrackPidTraits;
class StV0Vertex;
class StXiVertex;

class StBTofHit;
typedef StBTofHit**            StBTofHitIterator;
typedef StBTofHit * const * const_StBTofHitIterator;

class StPtrVecBTofHit : public StRefArray 
{ 
public: 
StPtrVecBTofHit(Int_t sz=0):StRefArray(sz){};
StPtrVecBTofHit(const StPtrVecBTofHit &from):StRefArray(from){};
virtual        ~StPtrVecBTofHit(){};

 StBTofHit * const &at(Int_t idx) const {return (StBTofHit  * const &)fV[idx];}
 StBTofHit *       &at(Int_t idx)       {return (StBTofHit  *       &)fV[idx];}

 StBTofHit * const &front()       const {return (StBTofHit  * const &)fV.front();}
 StBTofHit *       &front()             {return (StBTofHit  *       &)fV.front();}

 StBTofHit * const &back()        const {return (StBTofHit  * const &)fV.back();}
 StBTofHit *       &back()              {return (StBTofHit  *       &)fV.back();}

const_StBTofHitIterator begin() const {return (const_StBTofHitIterator)&(*(fV.begin()));}
      StBTofHitIterator begin()       {return (      StBTofHitIterator)&(*(fV.begin()));}
const_StBTofHitIterator end()   const {return (const_StBTofHitIterator)&(*(fV.end()));}
      StBTofHitIterator end()         {return (      StBTofHitIterator)&(*(fV.end()));}
      StBTofHitIterator erase(StBTofHitIterator  it)
      {return (StBTofHitIterator)Erase((TObject**)it,0);}
      StBTofHitIterator erase(StBTofHitIterator fst,StBTofHitIterator lst)
      {return (StBTofHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StBTofHit *       &operator[](Int_t i)       {return at(i);}
      StBTofHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StBTofHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecBTofHit ,1) 
};


class StSPtrVecBTofHit : public StStrArray 
{ 
public: 
StSPtrVecBTofHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecBTofHit(const StSPtrVecBTofHit &from):StStrArray(from){};

 StBTofHit * const &at(Int_t idx) const {return (StBTofHit  * const &)fV[idx];}
 StBTofHit *       &at(Int_t idx)       {return (StBTofHit  *       &)fV[idx];}

 StBTofHit * const &front()       const {return (StBTofHit  * const &)fV.front();}
 StBTofHit *       &front()             {return (StBTofHit  *       &)fV.front();}

 StBTofHit * const &back()        const {return (StBTofHit  * const &)fV.back();}
 StBTofHit *       &back()              {return (StBTofHit  *       &)fV.back();}

const_StBTofHitIterator begin() const {return (const_StBTofHitIterator)&(*(fV.begin()));}
      StBTofHitIterator begin()       {return (      StBTofHitIterator)&(*(fV.begin()));}
const_StBTofHitIterator end()   const {return (const_StBTofHitIterator)&(*(fV.end()));}
      StBTofHitIterator end()         {return (      StBTofHitIterator)&(*(fV.end()));}
      StBTofHitIterator erase(StBTofHitIterator  it)
      {return (StBTofHitIterator)Erase((TObject**)it,1);}
      StBTofHitIterator erase(StBTofHitIterator fst,StBTofHitIterator lst)
      {return (StBTofHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StBTofHit *       &operator[](Int_t i)       {return at(i);}
      StBTofHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StBTofHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecBTofHit,1) 
};
typedef       StBTofHitIterator  StPtrVecBTofHitIterator;
typedef const_StBTofHitIterator  StPtrVecBTofHitConstIterator;
typedef       StBTofHitIterator  StSPtrVecBTofHitIterator;
typedef const_StBTofHitIterator  StSPtrVecBTofHitConstIterator;

//______________________________________________________________
class StBTofRawHit;
typedef StBTofRawHit**            StBTofRawHitIterator;
typedef StBTofRawHit * const * const_StBTofRawHitIterator;

class StPtrVecBTofRawHit : public StRefArray 
{ 
public: 
StPtrVecBTofRawHit(Int_t sz=0):StRefArray(sz){};
StPtrVecBTofRawHit(const StPtrVecBTofRawHit &from):StRefArray(from){};
virtual        ~StPtrVecBTofRawHit(){};

 StBTofRawHit * const &at(Int_t idx) const {return (StBTofRawHit  * const &)fV[idx];}
 StBTofRawHit *       &at(Int_t idx)       {return (StBTofRawHit  *       &)fV[idx];}

 StBTofRawHit * const &front()       const {return (StBTofRawHit  * const &)fV.front();}
 StBTofRawHit *       &front()             {return (StBTofRawHit  *       &)fV.front();}

 StBTofRawHit * const &back()        const {return (StBTofRawHit  * const &)fV.back();}
 StBTofRawHit *       &back()              {return (StBTofRawHit  *       &)fV.back();}

const_StBTofRawHitIterator begin() const {return (const_StBTofRawHitIterator)&(*(fV.begin()));}
      StBTofRawHitIterator begin()       {return (      StBTofRawHitIterator)&(*(fV.begin()));}
const_StBTofRawHitIterator end()   const {return (const_StBTofRawHitIterator)&(*(fV.end()));}
      StBTofRawHitIterator end()         {return (      StBTofRawHitIterator)&(*(fV.end()));}
      StBTofRawHitIterator erase(StBTofRawHitIterator  it)
      {return (StBTofRawHitIterator)Erase((TObject**)it,0);}
      StBTofRawHitIterator erase(StBTofRawHitIterator fst,StBTofRawHitIterator lst)
      {return (StBTofRawHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StBTofRawHit *       &operator[](Int_t i)       {return at(i);}
      StBTofRawHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StBTofRawHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecBTofRawHit ,1) 
};


class StSPtrVecBTofRawHit : public StStrArray 
{ 
public: 
StSPtrVecBTofRawHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecBTofRawHit(const StSPtrVecBTofRawHit &from):StStrArray(from){};

 StBTofRawHit * const &at(Int_t idx) const {return (StBTofRawHit  * const &)fV[idx];}
 StBTofRawHit *       &at(Int_t idx)       {return (StBTofRawHit  *       &)fV[idx];}

 StBTofRawHit * const &front()       const {return (StBTofRawHit  * const &)fV.front();}
 StBTofRawHit *       &front()             {return (StBTofRawHit  *       &)fV.front();}

 StBTofRawHit * const &back()        const {return (StBTofRawHit  * const &)fV.back();}
 StBTofRawHit *       &back()              {return (StBTofRawHit  *       &)fV.back();}

const_StBTofRawHitIterator begin() const {return (const_StBTofRawHitIterator)&(*(fV.begin()));}
      StBTofRawHitIterator begin()       {return (      StBTofRawHitIterator)&(*(fV.begin()));}
const_StBTofRawHitIterator end()   const {return (const_StBTofRawHitIterator)&(*(fV.end()));}
      StBTofRawHitIterator end()         {return (      StBTofRawHitIterator)&(*(fV.end()));}
      StBTofRawHitIterator erase(StBTofRawHitIterator  it)
      {return (StBTofRawHitIterator)Erase((TObject**)it,1);}
      StBTofRawHitIterator erase(StBTofRawHitIterator fst,StBTofRawHitIterator lst)
      {return (StBTofRawHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StBTofRawHit *       &operator[](Int_t i)       {return at(i);}
      StBTofRawHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StBTofRawHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecBTofRawHit,1) 
};
typedef       StBTofRawHitIterator  StPtrVecBTofRawHitIterator;
typedef const_StBTofRawHitIterator  StPtrVecBTofRawHitConstIterator;
typedef       StBTofRawHitIterator  StSPtrVecBTofRawHitIterator;
typedef const_StBTofRawHitIterator  StSPtrVecBTofRawHitConstIterator;

//______________________________________________________________
class StCalibrationVertex;
typedef StCalibrationVertex**            StCalibrationVertexIterator;
typedef StCalibrationVertex * const * const_StCalibrationVertexIterator;

class StPtrVecCalibrationVertex : public StRefArray 
{ 
public: 
StPtrVecCalibrationVertex(Int_t sz=0):StRefArray(sz){};
StPtrVecCalibrationVertex(const StPtrVecCalibrationVertex &from):StRefArray(from){};
virtual        ~StPtrVecCalibrationVertex(){};

 StCalibrationVertex * const &at(Int_t idx) const {return (StCalibrationVertex  * const &)fV[idx];}
 StCalibrationVertex *       &at(Int_t idx)       {return (StCalibrationVertex  *       &)fV[idx];}

 StCalibrationVertex * const &front()       const {return (StCalibrationVertex  * const &)fV.front();}
 StCalibrationVertex *       &front()             {return (StCalibrationVertex  *       &)fV.front();}

 StCalibrationVertex * const &back()        const {return (StCalibrationVertex  * const &)fV.back();}
 StCalibrationVertex *       &back()              {return (StCalibrationVertex  *       &)fV.back();}

const_StCalibrationVertexIterator begin() const {return (const_StCalibrationVertexIterator)&(*(fV.begin()));}
      StCalibrationVertexIterator begin()       {return (      StCalibrationVertexIterator)&(*(fV.begin()));}
const_StCalibrationVertexIterator end()   const {return (const_StCalibrationVertexIterator)&(*(fV.end()));}
      StCalibrationVertexIterator end()         {return (      StCalibrationVertexIterator)&(*(fV.end()));}
      StCalibrationVertexIterator erase(StCalibrationVertexIterator  it)
      {return (StCalibrationVertexIterator)Erase((TObject**)it,0);}
      StCalibrationVertexIterator erase(StCalibrationVertexIterator fst,StCalibrationVertexIterator lst)
      {return (StCalibrationVertexIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StCalibrationVertex *       &operator[](Int_t i)       {return at(i);}
      StCalibrationVertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StCalibrationVertex * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecCalibrationVertex ,1) 
};


class StSPtrVecCalibrationVertex : public StStrArray 
{ 
public: 
StSPtrVecCalibrationVertex(Int_t sz=0):StStrArray(sz){};
StSPtrVecCalibrationVertex(const StSPtrVecCalibrationVertex &from):StStrArray(from){};

 StCalibrationVertex * const &at(Int_t idx) const {return (StCalibrationVertex  * const &)fV[idx];}
 StCalibrationVertex *       &at(Int_t idx)       {return (StCalibrationVertex  *       &)fV[idx];}

 StCalibrationVertex * const &front()       const {return (StCalibrationVertex  * const &)fV.front();}
 StCalibrationVertex *       &front()             {return (StCalibrationVertex  *       &)fV.front();}

 StCalibrationVertex * const &back()        const {return (StCalibrationVertex  * const &)fV.back();}
 StCalibrationVertex *       &back()              {return (StCalibrationVertex  *       &)fV.back();}

const_StCalibrationVertexIterator begin() const {return (const_StCalibrationVertexIterator)&(*(fV.begin()));}
      StCalibrationVertexIterator begin()       {return (      StCalibrationVertexIterator)&(*(fV.begin()));}
const_StCalibrationVertexIterator end()   const {return (const_StCalibrationVertexIterator)&(*(fV.end()));}
      StCalibrationVertexIterator end()         {return (      StCalibrationVertexIterator)&(*(fV.end()));}
      StCalibrationVertexIterator erase(StCalibrationVertexIterator  it)
      {return (StCalibrationVertexIterator)Erase((TObject**)it,1);}
      StCalibrationVertexIterator erase(StCalibrationVertexIterator fst,StCalibrationVertexIterator lst)
      {return (StCalibrationVertexIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StCalibrationVertex *       &operator[](Int_t i)       {return at(i);}
      StCalibrationVertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StCalibrationVertex *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecCalibrationVertex,1) 
};
typedef       StCalibrationVertexIterator  StPtrVecCalibrationVertexIterator;
typedef const_StCalibrationVertexIterator  StPtrVecCalibrationVertexConstIterator;
typedef       StCalibrationVertexIterator  StSPtrVecCalibrationVertexIterator;
typedef const_StCalibrationVertexIterator  StSPtrVecCalibrationVertexConstIterator;

//______________________________________________________________
class StDetectorState;
typedef StDetectorState**            StDetectorStateIterator;
typedef StDetectorState * const * const_StDetectorStateIterator;

class StPtrVecDetectorState : public StRefArray 
{ 
public: 
StPtrVecDetectorState(Int_t sz=0):StRefArray(sz){};
StPtrVecDetectorState(const StPtrVecDetectorState &from):StRefArray(from){};
virtual        ~StPtrVecDetectorState(){};

 StDetectorState * const &at(Int_t idx) const {return (StDetectorState  * const &)fV[idx];}
 StDetectorState *       &at(Int_t idx)       {return (StDetectorState  *       &)fV[idx];}

 StDetectorState * const &front()       const {return (StDetectorState  * const &)fV.front();}
 StDetectorState *       &front()             {return (StDetectorState  *       &)fV.front();}

 StDetectorState * const &back()        const {return (StDetectorState  * const &)fV.back();}
 StDetectorState *       &back()              {return (StDetectorState  *       &)fV.back();}

const_StDetectorStateIterator begin() const {return (const_StDetectorStateIterator)&(*(fV.begin()));}
      StDetectorStateIterator begin()       {return (      StDetectorStateIterator)&(*(fV.begin()));}
const_StDetectorStateIterator end()   const {return (const_StDetectorStateIterator)&(*(fV.end()));}
      StDetectorStateIterator end()         {return (      StDetectorStateIterator)&(*(fV.end()));}
      StDetectorStateIterator erase(StDetectorStateIterator  it)
      {return (StDetectorStateIterator)Erase((TObject**)it,0);}
      StDetectorStateIterator erase(StDetectorStateIterator fst,StDetectorStateIterator lst)
      {return (StDetectorStateIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StDetectorState *       &operator[](Int_t i)       {return at(i);}
      StDetectorState * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StDetectorState * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecDetectorState ,1) 
};


class StSPtrVecDetectorState : public StStrArray 
{ 
public: 
StSPtrVecDetectorState(Int_t sz=0):StStrArray(sz){};
StSPtrVecDetectorState(const StSPtrVecDetectorState &from):StStrArray(from){};

 StDetectorState * const &at(Int_t idx) const {return (StDetectorState  * const &)fV[idx];}
 StDetectorState *       &at(Int_t idx)       {return (StDetectorState  *       &)fV[idx];}

 StDetectorState * const &front()       const {return (StDetectorState  * const &)fV.front();}
 StDetectorState *       &front()             {return (StDetectorState  *       &)fV.front();}

 StDetectorState * const &back()        const {return (StDetectorState  * const &)fV.back();}
 StDetectorState *       &back()              {return (StDetectorState  *       &)fV.back();}

const_StDetectorStateIterator begin() const {return (const_StDetectorStateIterator)&(*(fV.begin()));}
      StDetectorStateIterator begin()       {return (      StDetectorStateIterator)&(*(fV.begin()));}
const_StDetectorStateIterator end()   const {return (const_StDetectorStateIterator)&(*(fV.end()));}
      StDetectorStateIterator end()         {return (      StDetectorStateIterator)&(*(fV.end()));}
      StDetectorStateIterator erase(StDetectorStateIterator  it)
      {return (StDetectorStateIterator)Erase((TObject**)it,1);}
      StDetectorStateIterator erase(StDetectorStateIterator fst,StDetectorStateIterator lst)
      {return (StDetectorStateIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StDetectorState *       &operator[](Int_t i)       {return at(i);}
      StDetectorState * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StDetectorState *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecDetectorState,1) 
};
typedef       StDetectorStateIterator  StPtrVecDetectorStateIterator;
typedef const_StDetectorStateIterator  StPtrVecDetectorStateConstIterator;
typedef       StDetectorStateIterator  StSPtrVecDetectorStateIterator;
typedef const_StDetectorStateIterator  StSPtrVecDetectorStateConstIterator;

//______________________________________________________________
class StEmcCluster;
typedef StEmcCluster**            StEmcClusterIterator;
typedef StEmcCluster * const * const_StEmcClusterIterator;

class StPtrVecEmcCluster : public StRefArray 
{ 
public: 
StPtrVecEmcCluster(Int_t sz=0):StRefArray(sz){};
StPtrVecEmcCluster(const StPtrVecEmcCluster &from):StRefArray(from){};
virtual        ~StPtrVecEmcCluster(){};

 StEmcCluster * const &at(Int_t idx) const {return (StEmcCluster  * const &)fV[idx];}
 StEmcCluster *       &at(Int_t idx)       {return (StEmcCluster  *       &)fV[idx];}

 StEmcCluster * const &front()       const {return (StEmcCluster  * const &)fV.front();}
 StEmcCluster *       &front()             {return (StEmcCluster  *       &)fV.front();}

 StEmcCluster * const &back()        const {return (StEmcCluster  * const &)fV.back();}
 StEmcCluster *       &back()              {return (StEmcCluster  *       &)fV.back();}

const_StEmcClusterIterator begin() const {return (const_StEmcClusterIterator)&(*(fV.begin()));}
      StEmcClusterIterator begin()       {return (      StEmcClusterIterator)&(*(fV.begin()));}
const_StEmcClusterIterator end()   const {return (const_StEmcClusterIterator)&(*(fV.end()));}
      StEmcClusterIterator end()         {return (      StEmcClusterIterator)&(*(fV.end()));}
      StEmcClusterIterator erase(StEmcClusterIterator  it)
      {return (StEmcClusterIterator)Erase((TObject**)it,0);}
      StEmcClusterIterator erase(StEmcClusterIterator fst,StEmcClusterIterator lst)
      {return (StEmcClusterIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StEmcCluster *       &operator[](Int_t i)       {return at(i);}
      StEmcCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StEmcCluster * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecEmcCluster ,1) 
};


class StSPtrVecEmcCluster : public StStrArray 
{ 
public: 
StSPtrVecEmcCluster(Int_t sz=0):StStrArray(sz){};
StSPtrVecEmcCluster(const StSPtrVecEmcCluster &from):StStrArray(from){};

 StEmcCluster * const &at(Int_t idx) const {return (StEmcCluster  * const &)fV[idx];}
 StEmcCluster *       &at(Int_t idx)       {return (StEmcCluster  *       &)fV[idx];}

 StEmcCluster * const &front()       const {return (StEmcCluster  * const &)fV.front();}
 StEmcCluster *       &front()             {return (StEmcCluster  *       &)fV.front();}

 StEmcCluster * const &back()        const {return (StEmcCluster  * const &)fV.back();}
 StEmcCluster *       &back()              {return (StEmcCluster  *       &)fV.back();}

const_StEmcClusterIterator begin() const {return (const_StEmcClusterIterator)&(*(fV.begin()));}
      StEmcClusterIterator begin()       {return (      StEmcClusterIterator)&(*(fV.begin()));}
const_StEmcClusterIterator end()   const {return (const_StEmcClusterIterator)&(*(fV.end()));}
      StEmcClusterIterator end()         {return (      StEmcClusterIterator)&(*(fV.end()));}
      StEmcClusterIterator erase(StEmcClusterIterator  it)
      {return (StEmcClusterIterator)Erase((TObject**)it,1);}
      StEmcClusterIterator erase(StEmcClusterIterator fst,StEmcClusterIterator lst)
      {return (StEmcClusterIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StEmcCluster *       &operator[](Int_t i)       {return at(i);}
      StEmcCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StEmcCluster *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecEmcCluster,1) 
};
typedef       StEmcClusterIterator  StPtrVecEmcClusterIterator;
typedef const_StEmcClusterIterator  StPtrVecEmcClusterConstIterator;
typedef       StEmcClusterIterator  StSPtrVecEmcClusterIterator;
typedef const_StEmcClusterIterator  StSPtrVecEmcClusterConstIterator;

//______________________________________________________________
class StEmcPoint;
typedef StEmcPoint**            StEmcPointIterator;
typedef StEmcPoint * const * const_StEmcPointIterator;

class StPtrVecEmcPoint : public StRefArray 
{ 
public: 
StPtrVecEmcPoint(Int_t sz=0):StRefArray(sz){};
StPtrVecEmcPoint(const StPtrVecEmcPoint &from):StRefArray(from){};
virtual        ~StPtrVecEmcPoint(){};

 StEmcPoint * const &at(Int_t idx) const {return (StEmcPoint  * const &)fV[idx];}
 StEmcPoint *       &at(Int_t idx)       {return (StEmcPoint  *       &)fV[idx];}

 StEmcPoint * const &front()       const {return (StEmcPoint  * const &)fV.front();}
 StEmcPoint *       &front()             {return (StEmcPoint  *       &)fV.front();}

 StEmcPoint * const &back()        const {return (StEmcPoint  * const &)fV.back();}
 StEmcPoint *       &back()              {return (StEmcPoint  *       &)fV.back();}

const_StEmcPointIterator begin() const {return (const_StEmcPointIterator)&(*(fV.begin()));}
      StEmcPointIterator begin()       {return (      StEmcPointIterator)&(*(fV.begin()));}
const_StEmcPointIterator end()   const {return (const_StEmcPointIterator)&(*(fV.end()));}
      StEmcPointIterator end()         {return (      StEmcPointIterator)&(*(fV.end()));}
      StEmcPointIterator erase(StEmcPointIterator  it)
      {return (StEmcPointIterator)Erase((TObject**)it,0);}
      StEmcPointIterator erase(StEmcPointIterator fst,StEmcPointIterator lst)
      {return (StEmcPointIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StEmcPoint *       &operator[](Int_t i)       {return at(i);}
      StEmcPoint * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StEmcPoint * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecEmcPoint ,1) 
};


class StSPtrVecEmcPoint : public StStrArray 
{ 
public: 
StSPtrVecEmcPoint(Int_t sz=0):StStrArray(sz){};
StSPtrVecEmcPoint(const StSPtrVecEmcPoint &from):StStrArray(from){};

 StEmcPoint * const &at(Int_t idx) const {return (StEmcPoint  * const &)fV[idx];}
 StEmcPoint *       &at(Int_t idx)       {return (StEmcPoint  *       &)fV[idx];}

 StEmcPoint * const &front()       const {return (StEmcPoint  * const &)fV.front();}
 StEmcPoint *       &front()             {return (StEmcPoint  *       &)fV.front();}

 StEmcPoint * const &back()        const {return (StEmcPoint  * const &)fV.back();}
 StEmcPoint *       &back()              {return (StEmcPoint  *       &)fV.back();}

const_StEmcPointIterator begin() const {return (const_StEmcPointIterator)&(*(fV.begin()));}
      StEmcPointIterator begin()       {return (      StEmcPointIterator)&(*(fV.begin()));}
const_StEmcPointIterator end()   const {return (const_StEmcPointIterator)&(*(fV.end()));}
      StEmcPointIterator end()         {return (      StEmcPointIterator)&(*(fV.end()));}
      StEmcPointIterator erase(StEmcPointIterator  it)
      {return (StEmcPointIterator)Erase((TObject**)it,1);}
      StEmcPointIterator erase(StEmcPointIterator fst,StEmcPointIterator lst)
      {return (StEmcPointIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StEmcPoint *       &operator[](Int_t i)       {return at(i);}
      StEmcPoint * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StEmcPoint *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecEmcPoint,1) 
};
typedef       StEmcPointIterator  StPtrVecEmcPointIterator;
typedef const_StEmcPointIterator  StPtrVecEmcPointConstIterator;
typedef       StEmcPointIterator  StSPtrVecEmcPointIterator;
typedef const_StEmcPointIterator  StSPtrVecEmcPointConstIterator;

//______________________________________________________________
class StEmcRawHit;
typedef StEmcRawHit**            StEmcRawHitIterator;
typedef StEmcRawHit * const * const_StEmcRawHitIterator;

class StPtrVecEmcRawHit : public StRefArray 
{ 
public: 
StPtrVecEmcRawHit(Int_t sz=0):StRefArray(sz){};
StPtrVecEmcRawHit(const StPtrVecEmcRawHit &from):StRefArray(from){};
virtual        ~StPtrVecEmcRawHit(){};

 StEmcRawHit * const &at(Int_t idx) const {return (StEmcRawHit  * const &)fV[idx];}
 StEmcRawHit *       &at(Int_t idx)       {return (StEmcRawHit  *       &)fV[idx];}

 StEmcRawHit * const &front()       const {return (StEmcRawHit  * const &)fV.front();}
 StEmcRawHit *       &front()             {return (StEmcRawHit  *       &)fV.front();}

 StEmcRawHit * const &back()        const {return (StEmcRawHit  * const &)fV.back();}
 StEmcRawHit *       &back()              {return (StEmcRawHit  *       &)fV.back();}

const_StEmcRawHitIterator begin() const {return (const_StEmcRawHitIterator)&(*(fV.begin()));}
      StEmcRawHitIterator begin()       {return (      StEmcRawHitIterator)&(*(fV.begin()));}
const_StEmcRawHitIterator end()   const {return (const_StEmcRawHitIterator)&(*(fV.end()));}
      StEmcRawHitIterator end()         {return (      StEmcRawHitIterator)&(*(fV.end()));}
      StEmcRawHitIterator erase(StEmcRawHitIterator  it)
      {return (StEmcRawHitIterator)Erase((TObject**)it,0);}
      StEmcRawHitIterator erase(StEmcRawHitIterator fst,StEmcRawHitIterator lst)
      {return (StEmcRawHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StEmcRawHit *       &operator[](Int_t i)       {return at(i);}
      StEmcRawHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StEmcRawHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecEmcRawHit ,1) 
};


class StSPtrVecEmcRawHit : public StStrArray 
{ 
public: 
StSPtrVecEmcRawHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecEmcRawHit(const StSPtrVecEmcRawHit &from):StStrArray(from){};

 StEmcRawHit * const &at(Int_t idx) const {return (StEmcRawHit  * const &)fV[idx];}
 StEmcRawHit *       &at(Int_t idx)       {return (StEmcRawHit  *       &)fV[idx];}

 StEmcRawHit * const &front()       const {return (StEmcRawHit  * const &)fV.front();}
 StEmcRawHit *       &front()             {return (StEmcRawHit  *       &)fV.front();}

 StEmcRawHit * const &back()        const {return (StEmcRawHit  * const &)fV.back();}
 StEmcRawHit *       &back()              {return (StEmcRawHit  *       &)fV.back();}

const_StEmcRawHitIterator begin() const {return (const_StEmcRawHitIterator)&(*(fV.begin()));}
      StEmcRawHitIterator begin()       {return (      StEmcRawHitIterator)&(*(fV.begin()));}
const_StEmcRawHitIterator end()   const {return (const_StEmcRawHitIterator)&(*(fV.end()));}
      StEmcRawHitIterator end()         {return (      StEmcRawHitIterator)&(*(fV.end()));}
      StEmcRawHitIterator erase(StEmcRawHitIterator  it)
      {return (StEmcRawHitIterator)Erase((TObject**)it,1);}
      StEmcRawHitIterator erase(StEmcRawHitIterator fst,StEmcRawHitIterator lst)
      {return (StEmcRawHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StEmcRawHit *       &operator[](Int_t i)       {return at(i);}
      StEmcRawHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StEmcRawHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecEmcRawHit,1) 
};
typedef       StEmcRawHitIterator  StPtrVecEmcRawHitIterator;
typedef const_StEmcRawHitIterator  StPtrVecEmcRawHitConstIterator;
typedef       StEmcRawHitIterator  StSPtrVecEmcRawHitIterator;
typedef const_StEmcRawHitIterator  StSPtrVecEmcRawHitConstIterator;

//______________________________________________________________
class StEtrHit;
typedef StEtrHit**            StEtrHitIterator;
typedef StEtrHit * const * const_StEtrHitIterator;

class StPtrVecEtrHit : public StRefArray 
{ 
public: 
StPtrVecEtrHit(Int_t sz=0):StRefArray(sz){};
StPtrVecEtrHit(const StPtrVecEtrHit &from):StRefArray(from){};
virtual        ~StPtrVecEtrHit(){};

 StEtrHit * const &at(Int_t idx) const {return (StEtrHit  * const &)fV[idx];}
 StEtrHit *       &at(Int_t idx)       {return (StEtrHit  *       &)fV[idx];}

 StEtrHit * const &front()       const {return (StEtrHit  * const &)fV.front();}
 StEtrHit *       &front()             {return (StEtrHit  *       &)fV.front();}

 StEtrHit * const &back()        const {return (StEtrHit  * const &)fV.back();}
 StEtrHit *       &back()              {return (StEtrHit  *       &)fV.back();}

const_StEtrHitIterator begin() const {return (const_StEtrHitIterator)&(*(fV.begin()));}
      StEtrHitIterator begin()       {return (      StEtrHitIterator)&(*(fV.begin()));}
const_StEtrHitIterator end()   const {return (const_StEtrHitIterator)&(*(fV.end()));}
      StEtrHitIterator end()         {return (      StEtrHitIterator)&(*(fV.end()));}
      StEtrHitIterator erase(StEtrHitIterator  it)
      {return (StEtrHitIterator)Erase((TObject**)it,0);}
      StEtrHitIterator erase(StEtrHitIterator fst,StEtrHitIterator lst)
      {return (StEtrHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StEtrHit *       &operator[](Int_t i)       {return at(i);}
      StEtrHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StEtrHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecEtrHit ,1) 
};


class StSPtrVecEtrHit : public StStrArray 
{ 
public: 
StSPtrVecEtrHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecEtrHit(const StSPtrVecEtrHit &from):StStrArray(from){};

 StEtrHit * const &at(Int_t idx) const {return (StEtrHit  * const &)fV[idx];}
 StEtrHit *       &at(Int_t idx)       {return (StEtrHit  *       &)fV[idx];}

 StEtrHit * const &front()       const {return (StEtrHit  * const &)fV.front();}
 StEtrHit *       &front()             {return (StEtrHit  *       &)fV.front();}

 StEtrHit * const &back()        const {return (StEtrHit  * const &)fV.back();}
 StEtrHit *       &back()              {return (StEtrHit  *       &)fV.back();}

const_StEtrHitIterator begin() const {return (const_StEtrHitIterator)&(*(fV.begin()));}
      StEtrHitIterator begin()       {return (      StEtrHitIterator)&(*(fV.begin()));}
const_StEtrHitIterator end()   const {return (const_StEtrHitIterator)&(*(fV.end()));}
      StEtrHitIterator end()         {return (      StEtrHitIterator)&(*(fV.end()));}
      StEtrHitIterator erase(StEtrHitIterator  it)
      {return (StEtrHitIterator)Erase((TObject**)it,1);}
      StEtrHitIterator erase(StEtrHitIterator fst,StEtrHitIterator lst)
      {return (StEtrHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StEtrHit *       &operator[](Int_t i)       {return at(i);}
      StEtrHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StEtrHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecEtrHit,1) 
};
typedef       StEtrHitIterator  StPtrVecEtrHitIterator;
typedef const_StEtrHitIterator  StPtrVecEtrHitConstIterator;
typedef       StEtrHitIterator  StSPtrVecEtrHitIterator;
typedef const_StEtrHitIterator  StSPtrVecEtrHitConstIterator;

//______________________________________________________________
class StFgtHit;
typedef StFgtHit**            StFgtHitIterator;
typedef StFgtHit * const * const_StFgtHitIterator;

class StPtrVecFgtHit : public StRefArray 
{ 
public: 
StPtrVecFgtHit(Int_t sz=0):StRefArray(sz){};
StPtrVecFgtHit(const StPtrVecFgtHit &from):StRefArray(from){};
virtual        ~StPtrVecFgtHit(){};

 StFgtHit * const &at(Int_t idx) const {return (StFgtHit  * const &)fV[idx];}
 StFgtHit *       &at(Int_t idx)       {return (StFgtHit  *       &)fV[idx];}

 StFgtHit * const &front()       const {return (StFgtHit  * const &)fV.front();}
 StFgtHit *       &front()             {return (StFgtHit  *       &)fV.front();}

 StFgtHit * const &back()        const {return (StFgtHit  * const &)fV.back();}
 StFgtHit *       &back()              {return (StFgtHit  *       &)fV.back();}

const_StFgtHitIterator begin() const {return (const_StFgtHitIterator)&(*(fV.begin()));}
      StFgtHitIterator begin()       {return (      StFgtHitIterator)&(*(fV.begin()));}
const_StFgtHitIterator end()   const {return (const_StFgtHitIterator)&(*(fV.end()));}
      StFgtHitIterator end()         {return (      StFgtHitIterator)&(*(fV.end()));}
      StFgtHitIterator erase(StFgtHitIterator  it)
      {return (StFgtHitIterator)Erase((TObject**)it,0);}
      StFgtHitIterator erase(StFgtHitIterator fst,StFgtHitIterator lst)
      {return (StFgtHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StFgtHit *       &operator[](Int_t i)       {return at(i);}
      StFgtHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFgtHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecFgtHit ,1) 
};


class StSPtrVecFgtHit : public StStrArray 
{ 
public: 
StSPtrVecFgtHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecFgtHit(const StSPtrVecFgtHit &from):StStrArray(from){};

 StFgtHit * const &at(Int_t idx) const {return (StFgtHit  * const &)fV[idx];}
 StFgtHit *       &at(Int_t idx)       {return (StFgtHit  *       &)fV[idx];}

 StFgtHit * const &front()       const {return (StFgtHit  * const &)fV.front();}
 StFgtHit *       &front()             {return (StFgtHit  *       &)fV.front();}

 StFgtHit * const &back()        const {return (StFgtHit  * const &)fV.back();}
 StFgtHit *       &back()              {return (StFgtHit  *       &)fV.back();}

const_StFgtHitIterator begin() const {return (const_StFgtHitIterator)&(*(fV.begin()));}
      StFgtHitIterator begin()       {return (      StFgtHitIterator)&(*(fV.begin()));}
const_StFgtHitIterator end()   const {return (const_StFgtHitIterator)&(*(fV.end()));}
      StFgtHitIterator end()         {return (      StFgtHitIterator)&(*(fV.end()));}
      StFgtHitIterator erase(StFgtHitIterator  it)
      {return (StFgtHitIterator)Erase((TObject**)it,1);}
      StFgtHitIterator erase(StFgtHitIterator fst,StFgtHitIterator lst)
      {return (StFgtHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StFgtHit *       &operator[](Int_t i)       {return at(i);}
      StFgtHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFgtHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecFgtHit,1) 
};
typedef       StFgtHitIterator  StPtrVecFgtHitIterator;
typedef const_StFgtHitIterator  StPtrVecFgtHitConstIterator;
typedef       StFgtHitIterator  StSPtrVecFgtHitIterator;
typedef const_StFgtHitIterator  StSPtrVecFgtHitConstIterator;

//______________________________________________________________
class StFgtPoint;
typedef StFgtPoint**            StFgtPointIterator;
typedef StFgtPoint * const * const_StFgtPointIterator;

class StPtrVecFgtPoint : public StRefArray 
{ 
public: 
StPtrVecFgtPoint(Int_t sz=0):StRefArray(sz){};
StPtrVecFgtPoint(const StPtrVecFgtPoint &from):StRefArray(from){};
virtual        ~StPtrVecFgtPoint(){};

 StFgtPoint * const &at(Int_t idx) const {return (StFgtPoint  * const &)fV[idx];}
 StFgtPoint *       &at(Int_t idx)       {return (StFgtPoint  *       &)fV[idx];}

 StFgtPoint * const &front()       const {return (StFgtPoint  * const &)fV.front();}
 StFgtPoint *       &front()             {return (StFgtPoint  *       &)fV.front();}

 StFgtPoint * const &back()        const {return (StFgtPoint  * const &)fV.back();}
 StFgtPoint *       &back()              {return (StFgtPoint  *       &)fV.back();}

const_StFgtPointIterator begin() const {return (const_StFgtPointIterator)&(*(fV.begin()));}
      StFgtPointIterator begin()       {return (      StFgtPointIterator)&(*(fV.begin()));}
const_StFgtPointIterator end()   const {return (const_StFgtPointIterator)&(*(fV.end()));}
      StFgtPointIterator end()         {return (      StFgtPointIterator)&(*(fV.end()));}
      StFgtPointIterator erase(StFgtPointIterator  it)
      {return (StFgtPointIterator)Erase((TObject**)it,0);}
      StFgtPointIterator erase(StFgtPointIterator fst,StFgtPointIterator lst)
      {return (StFgtPointIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StFgtPoint *       &operator[](Int_t i)       {return at(i);}
      StFgtPoint * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFgtPoint * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecFgtPoint ,1) 
};


class StSPtrVecFgtPoint : public StStrArray 
{ 
public: 
StSPtrVecFgtPoint(Int_t sz=0):StStrArray(sz){};
StSPtrVecFgtPoint(const StSPtrVecFgtPoint &from):StStrArray(from){};

 StFgtPoint * const &at(Int_t idx) const {return (StFgtPoint  * const &)fV[idx];}
 StFgtPoint *       &at(Int_t idx)       {return (StFgtPoint  *       &)fV[idx];}

 StFgtPoint * const &front()       const {return (StFgtPoint  * const &)fV.front();}
 StFgtPoint *       &front()             {return (StFgtPoint  *       &)fV.front();}

 StFgtPoint * const &back()        const {return (StFgtPoint  * const &)fV.back();}
 StFgtPoint *       &back()              {return (StFgtPoint  *       &)fV.back();}

const_StFgtPointIterator begin() const {return (const_StFgtPointIterator)&(*(fV.begin()));}
      StFgtPointIterator begin()       {return (      StFgtPointIterator)&(*(fV.begin()));}
const_StFgtPointIterator end()   const {return (const_StFgtPointIterator)&(*(fV.end()));}
      StFgtPointIterator end()         {return (      StFgtPointIterator)&(*(fV.end()));}
      StFgtPointIterator erase(StFgtPointIterator  it)
      {return (StFgtPointIterator)Erase((TObject**)it,1);}
      StFgtPointIterator erase(StFgtPointIterator fst,StFgtPointIterator lst)
      {return (StFgtPointIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StFgtPoint *       &operator[](Int_t i)       {return at(i);}
      StFgtPoint * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFgtPoint *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecFgtPoint,1) 
};
typedef       StFgtPointIterator  StPtrVecFgtPointIterator;
typedef const_StFgtPointIterator  StPtrVecFgtPointConstIterator;
typedef       StFgtPointIterator  StSPtrVecFgtPointIterator;
typedef const_StFgtPointIterator  StSPtrVecFgtPointConstIterator;

//______________________________________________________________
class StFgtStrip;
typedef StFgtStrip**            StFgtStripIterator;
typedef StFgtStrip * const * const_StFgtStripIterator;

class StPtrVecFgtStrip : public StRefArray 
{ 
public: 
StPtrVecFgtStrip(Int_t sz=0):StRefArray(sz){};
StPtrVecFgtStrip(const StPtrVecFgtStrip &from):StRefArray(from){};
virtual        ~StPtrVecFgtStrip(){};

 StFgtStrip * const &at(Int_t idx) const {return (StFgtStrip  * const &)fV[idx];}
 StFgtStrip *       &at(Int_t idx)       {return (StFgtStrip  *       &)fV[idx];}

 StFgtStrip * const &front()       const {return (StFgtStrip  * const &)fV.front();}
 StFgtStrip *       &front()             {return (StFgtStrip  *       &)fV.front();}

 StFgtStrip * const &back()        const {return (StFgtStrip  * const &)fV.back();}
 StFgtStrip *       &back()              {return (StFgtStrip  *       &)fV.back();}

const_StFgtStripIterator begin() const {return (const_StFgtStripIterator)&(*(fV.begin()));}
      StFgtStripIterator begin()       {return (      StFgtStripIterator)&(*(fV.begin()));}
const_StFgtStripIterator end()   const {return (const_StFgtStripIterator)&(*(fV.end()));}
      StFgtStripIterator end()         {return (      StFgtStripIterator)&(*(fV.end()));}
      StFgtStripIterator erase(StFgtStripIterator  it)
      {return (StFgtStripIterator)Erase((TObject**)it,0);}
      StFgtStripIterator erase(StFgtStripIterator fst,StFgtStripIterator lst)
      {return (StFgtStripIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StFgtStrip *       &operator[](Int_t i)       {return at(i);}
      StFgtStrip * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFgtStrip * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecFgtStrip ,1) 
};


class StSPtrVecFgtStrip : public StStrArray 
{ 
public: 
StSPtrVecFgtStrip(Int_t sz=0):StStrArray(sz){};
StSPtrVecFgtStrip(const StSPtrVecFgtStrip &from):StStrArray(from){};

 StFgtStrip * const &at(Int_t idx) const {return (StFgtStrip  * const &)fV[idx];}
 StFgtStrip *       &at(Int_t idx)       {return (StFgtStrip  *       &)fV[idx];}

 StFgtStrip * const &front()       const {return (StFgtStrip  * const &)fV.front();}
 StFgtStrip *       &front()             {return (StFgtStrip  *       &)fV.front();}

 StFgtStrip * const &back()        const {return (StFgtStrip  * const &)fV.back();}
 StFgtStrip *       &back()              {return (StFgtStrip  *       &)fV.back();}

const_StFgtStripIterator begin() const {return (const_StFgtStripIterator)&(*(fV.begin()));}
      StFgtStripIterator begin()       {return (      StFgtStripIterator)&(*(fV.begin()));}
const_StFgtStripIterator end()   const {return (const_StFgtStripIterator)&(*(fV.end()));}
      StFgtStripIterator end()         {return (      StFgtStripIterator)&(*(fV.end()));}
      StFgtStripIterator erase(StFgtStripIterator  it)
      {return (StFgtStripIterator)Erase((TObject**)it,1);}
      StFgtStripIterator erase(StFgtStripIterator fst,StFgtStripIterator lst)
      {return (StFgtStripIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StFgtStrip *       &operator[](Int_t i)       {return at(i);}
      StFgtStrip * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFgtStrip *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecFgtStrip,1) 
};
typedef       StFgtStripIterator  StPtrVecFgtStripIterator;
typedef const_StFgtStripIterator  StPtrVecFgtStripConstIterator;
typedef       StFgtStripIterator  StSPtrVecFgtStripIterator;
typedef const_StFgtStripIterator  StSPtrVecFgtStripConstIterator;

//______________________________________________________________
class StFmsCluster;
typedef StFmsCluster**            StFmsClusterIterator;
typedef StFmsCluster * const * const_StFmsClusterIterator;

class StPtrVecFmsCluster : public StRefArray 
{ 
public: 
StPtrVecFmsCluster(Int_t sz=0):StRefArray(sz){};
StPtrVecFmsCluster(const StPtrVecFmsCluster &from):StRefArray(from){};
virtual        ~StPtrVecFmsCluster(){};

 StFmsCluster * const &at(Int_t idx) const {return (StFmsCluster  * const &)fV[idx];}
 StFmsCluster *       &at(Int_t idx)       {return (StFmsCluster  *       &)fV[idx];}

 StFmsCluster * const &front()       const {return (StFmsCluster  * const &)fV.front();}
 StFmsCluster *       &front()             {return (StFmsCluster  *       &)fV.front();}

 StFmsCluster * const &back()        const {return (StFmsCluster  * const &)fV.back();}
 StFmsCluster *       &back()              {return (StFmsCluster  *       &)fV.back();}

const_StFmsClusterIterator begin() const {return (const_StFmsClusterIterator)&(*(fV.begin()));}
      StFmsClusterIterator begin()       {return (      StFmsClusterIterator)&(*(fV.begin()));}
const_StFmsClusterIterator end()   const {return (const_StFmsClusterIterator)&(*(fV.end()));}
      StFmsClusterIterator end()         {return (      StFmsClusterIterator)&(*(fV.end()));}
      StFmsClusterIterator erase(StFmsClusterIterator  it)
      {return (StFmsClusterIterator)Erase((TObject**)it,0);}
      StFmsClusterIterator erase(StFmsClusterIterator fst,StFmsClusterIterator lst)
      {return (StFmsClusterIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StFmsCluster *       &operator[](Int_t i)       {return at(i);}
      StFmsCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFmsCluster * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecFmsCluster ,1) 
};


class StSPtrVecFmsCluster : public StStrArray 
{ 
public: 
StSPtrVecFmsCluster(Int_t sz=0):StStrArray(sz){};
StSPtrVecFmsCluster(const StSPtrVecFmsCluster &from):StStrArray(from){};

 StFmsCluster * const &at(Int_t idx) const {return (StFmsCluster  * const &)fV[idx];}
 StFmsCluster *       &at(Int_t idx)       {return (StFmsCluster  *       &)fV[idx];}

 StFmsCluster * const &front()       const {return (StFmsCluster  * const &)fV.front();}
 StFmsCluster *       &front()             {return (StFmsCluster  *       &)fV.front();}

 StFmsCluster * const &back()        const {return (StFmsCluster  * const &)fV.back();}
 StFmsCluster *       &back()              {return (StFmsCluster  *       &)fV.back();}

const_StFmsClusterIterator begin() const {return (const_StFmsClusterIterator)&(*(fV.begin()));}
      StFmsClusterIterator begin()       {return (      StFmsClusterIterator)&(*(fV.begin()));}
const_StFmsClusterIterator end()   const {return (const_StFmsClusterIterator)&(*(fV.end()));}
      StFmsClusterIterator end()         {return (      StFmsClusterIterator)&(*(fV.end()));}
      StFmsClusterIterator erase(StFmsClusterIterator  it)
      {return (StFmsClusterIterator)Erase((TObject**)it,1);}
      StFmsClusterIterator erase(StFmsClusterIterator fst,StFmsClusterIterator lst)
      {return (StFmsClusterIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StFmsCluster *       &operator[](Int_t i)       {return at(i);}
      StFmsCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFmsCluster *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecFmsCluster,1) 
};
typedef       StFmsClusterIterator  StPtrVecFmsClusterIterator;
typedef const_StFmsClusterIterator  StPtrVecFmsClusterConstIterator;
typedef       StFmsClusterIterator  StSPtrVecFmsClusterIterator;
typedef const_StFmsClusterIterator  StSPtrVecFmsClusterConstIterator;

//______________________________________________________________
class StFmsHit;
typedef StFmsHit**            StFmsHitIterator;
typedef StFmsHit * const * const_StFmsHitIterator;

class StPtrVecFmsHit : public StRefArray 
{ 
public: 
StPtrVecFmsHit(Int_t sz=0):StRefArray(sz){};
StPtrVecFmsHit(const StPtrVecFmsHit &from):StRefArray(from){};
virtual        ~StPtrVecFmsHit(){};

 StFmsHit * const &at(Int_t idx) const {return (StFmsHit  * const &)fV[idx];}
 StFmsHit *       &at(Int_t idx)       {return (StFmsHit  *       &)fV[idx];}

 StFmsHit * const &front()       const {return (StFmsHit  * const &)fV.front();}
 StFmsHit *       &front()             {return (StFmsHit  *       &)fV.front();}

 StFmsHit * const &back()        const {return (StFmsHit  * const &)fV.back();}
 StFmsHit *       &back()              {return (StFmsHit  *       &)fV.back();}

const_StFmsHitIterator begin() const {return (const_StFmsHitIterator)&(*(fV.begin()));}
      StFmsHitIterator begin()       {return (      StFmsHitIterator)&(*(fV.begin()));}
const_StFmsHitIterator end()   const {return (const_StFmsHitIterator)&(*(fV.end()));}
      StFmsHitIterator end()         {return (      StFmsHitIterator)&(*(fV.end()));}
      StFmsHitIterator erase(StFmsHitIterator  it)
      {return (StFmsHitIterator)Erase((TObject**)it,0);}
      StFmsHitIterator erase(StFmsHitIterator fst,StFmsHitIterator lst)
      {return (StFmsHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StFmsHit *       &operator[](Int_t i)       {return at(i);}
      StFmsHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFmsHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecFmsHit ,1) 
};


class StSPtrVecFmsHit : public StStrArray 
{ 
public: 
StSPtrVecFmsHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecFmsHit(const StSPtrVecFmsHit &from):StStrArray(from){};

 StFmsHit * const &at(Int_t idx) const {return (StFmsHit  * const &)fV[idx];}
 StFmsHit *       &at(Int_t idx)       {return (StFmsHit  *       &)fV[idx];}

 StFmsHit * const &front()       const {return (StFmsHit  * const &)fV.front();}
 StFmsHit *       &front()             {return (StFmsHit  *       &)fV.front();}

 StFmsHit * const &back()        const {return (StFmsHit  * const &)fV.back();}
 StFmsHit *       &back()              {return (StFmsHit  *       &)fV.back();}

const_StFmsHitIterator begin() const {return (const_StFmsHitIterator)&(*(fV.begin()));}
      StFmsHitIterator begin()       {return (      StFmsHitIterator)&(*(fV.begin()));}
const_StFmsHitIterator end()   const {return (const_StFmsHitIterator)&(*(fV.end()));}
      StFmsHitIterator end()         {return (      StFmsHitIterator)&(*(fV.end()));}
      StFmsHitIterator erase(StFmsHitIterator  it)
      {return (StFmsHitIterator)Erase((TObject**)it,1);}
      StFmsHitIterator erase(StFmsHitIterator fst,StFmsHitIterator lst)
      {return (StFmsHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StFmsHit *       &operator[](Int_t i)       {return at(i);}
      StFmsHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFmsHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecFmsHit,1) 
};
typedef       StFmsHitIterator  StPtrVecFmsHitIterator;
typedef const_StFmsHitIterator  StPtrVecFmsHitConstIterator;
typedef       StFmsHitIterator  StSPtrVecFmsHitIterator;
typedef const_StFmsHitIterator  StSPtrVecFmsHitConstIterator;

//______________________________________________________________
class StFmsPoint;
typedef StFmsPoint**            StFmsPointIterator;
typedef StFmsPoint * const * const_StFmsPointIterator;

class StPtrVecFmsPoint : public StRefArray 
{ 
public: 
StPtrVecFmsPoint(Int_t sz=0):StRefArray(sz){};
StPtrVecFmsPoint(const StPtrVecFmsPoint &from):StRefArray(from){};
virtual        ~StPtrVecFmsPoint(){};

 StFmsPoint * const &at(Int_t idx) const {return (StFmsPoint  * const &)fV[idx];}
 StFmsPoint *       &at(Int_t idx)       {return (StFmsPoint  *       &)fV[idx];}

 StFmsPoint * const &front()       const {return (StFmsPoint  * const &)fV.front();}
 StFmsPoint *       &front()             {return (StFmsPoint  *       &)fV.front();}

 StFmsPoint * const &back()        const {return (StFmsPoint  * const &)fV.back();}
 StFmsPoint *       &back()              {return (StFmsPoint  *       &)fV.back();}

const_StFmsPointIterator begin() const {return (const_StFmsPointIterator)&(*(fV.begin()));}
      StFmsPointIterator begin()       {return (      StFmsPointIterator)&(*(fV.begin()));}
const_StFmsPointIterator end()   const {return (const_StFmsPointIterator)&(*(fV.end()));}
      StFmsPointIterator end()         {return (      StFmsPointIterator)&(*(fV.end()));}
      StFmsPointIterator erase(StFmsPointIterator  it)
      {return (StFmsPointIterator)Erase((TObject**)it,0);}
      StFmsPointIterator erase(StFmsPointIterator fst,StFmsPointIterator lst)
      {return (StFmsPointIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StFmsPoint *       &operator[](Int_t i)       {return at(i);}
      StFmsPoint * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFmsPoint * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecFmsPoint ,1) 
};


class StSPtrVecFmsPoint : public StStrArray 
{ 
public: 
StSPtrVecFmsPoint(Int_t sz=0):StStrArray(sz){};
StSPtrVecFmsPoint(const StSPtrVecFmsPoint &from):StStrArray(from){};

 StFmsPoint * const &at(Int_t idx) const {return (StFmsPoint  * const &)fV[idx];}
 StFmsPoint *       &at(Int_t idx)       {return (StFmsPoint  *       &)fV[idx];}

 StFmsPoint * const &front()       const {return (StFmsPoint  * const &)fV.front();}
 StFmsPoint *       &front()             {return (StFmsPoint  *       &)fV.front();}

 StFmsPoint * const &back()        const {return (StFmsPoint  * const &)fV.back();}
 StFmsPoint *       &back()              {return (StFmsPoint  *       &)fV.back();}

const_StFmsPointIterator begin() const {return (const_StFmsPointIterator)&(*(fV.begin()));}
      StFmsPointIterator begin()       {return (      StFmsPointIterator)&(*(fV.begin()));}
const_StFmsPointIterator end()   const {return (const_StFmsPointIterator)&(*(fV.end()));}
      StFmsPointIterator end()         {return (      StFmsPointIterator)&(*(fV.end()));}
      StFmsPointIterator erase(StFmsPointIterator  it)
      {return (StFmsPointIterator)Erase((TObject**)it,1);}
      StFmsPointIterator erase(StFmsPointIterator fst,StFmsPointIterator lst)
      {return (StFmsPointIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StFmsPoint *       &operator[](Int_t i)       {return at(i);}
      StFmsPoint * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFmsPoint *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecFmsPoint,1) 
};
typedef       StFmsPointIterator  StPtrVecFmsPointIterator;
typedef const_StFmsPointIterator  StPtrVecFmsPointConstIterator;
typedef       StFmsPointIterator  StSPtrVecFmsPointIterator;
typedef const_StFmsPointIterator  StSPtrVecFmsPointConstIterator;

//______________________________________________________________
class StFpsSlat;
typedef StFpsSlat**            StFpsSlatIterator;
typedef StFpsSlat * const * const_StFpsSlatIterator;

class StPtrVecFpsSlat : public StRefArray 
{ 
public: 
StPtrVecFpsSlat(Int_t sz=0):StRefArray(sz){};
StPtrVecFpsSlat(const StPtrVecFpsSlat &from):StRefArray(from){};
virtual        ~StPtrVecFpsSlat(){};

 StFpsSlat * const &at(Int_t idx) const {return (StFpsSlat  * const &)fV[idx];}
 StFpsSlat *       &at(Int_t idx)       {return (StFpsSlat  *       &)fV[idx];}

 StFpsSlat * const &front()       const {return (StFpsSlat  * const &)fV.front();}
 StFpsSlat *       &front()             {return (StFpsSlat  *       &)fV.front();}

 StFpsSlat * const &back()        const {return (StFpsSlat  * const &)fV.back();}
 StFpsSlat *       &back()              {return (StFpsSlat  *       &)fV.back();}

const_StFpsSlatIterator begin() const {return (const_StFpsSlatIterator)&(*(fV.begin()));}
      StFpsSlatIterator begin()       {return (      StFpsSlatIterator)&(*(fV.begin()));}
const_StFpsSlatIterator end()   const {return (const_StFpsSlatIterator)&(*(fV.end()));}
      StFpsSlatIterator end()         {return (      StFpsSlatIterator)&(*(fV.end()));}
      StFpsSlatIterator erase(StFpsSlatIterator  it)
      {return (StFpsSlatIterator)Erase((TObject**)it,0);}
      StFpsSlatIterator erase(StFpsSlatIterator fst,StFpsSlatIterator lst)
      {return (StFpsSlatIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StFpsSlat *       &operator[](Int_t i)       {return at(i);}
      StFpsSlat * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFpsSlat * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecFpsSlat ,1) 
};


class StSPtrVecFpsSlat : public StStrArray 
{ 
public: 
StSPtrVecFpsSlat(Int_t sz=0):StStrArray(sz){};
StSPtrVecFpsSlat(const StSPtrVecFpsSlat &from):StStrArray(from){};

 StFpsSlat * const &at(Int_t idx) const {return (StFpsSlat  * const &)fV[idx];}
 StFpsSlat *       &at(Int_t idx)       {return (StFpsSlat  *       &)fV[idx];}

 StFpsSlat * const &front()       const {return (StFpsSlat  * const &)fV.front();}
 StFpsSlat *       &front()             {return (StFpsSlat  *       &)fV.front();}

 StFpsSlat * const &back()        const {return (StFpsSlat  * const &)fV.back();}
 StFpsSlat *       &back()              {return (StFpsSlat  *       &)fV.back();}

const_StFpsSlatIterator begin() const {return (const_StFpsSlatIterator)&(*(fV.begin()));}
      StFpsSlatIterator begin()       {return (      StFpsSlatIterator)&(*(fV.begin()));}
const_StFpsSlatIterator end()   const {return (const_StFpsSlatIterator)&(*(fV.end()));}
      StFpsSlatIterator end()         {return (      StFpsSlatIterator)&(*(fV.end()));}
      StFpsSlatIterator erase(StFpsSlatIterator  it)
      {return (StFpsSlatIterator)Erase((TObject**)it,1);}
      StFpsSlatIterator erase(StFpsSlatIterator fst,StFpsSlatIterator lst)
      {return (StFpsSlatIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StFpsSlat *       &operator[](Int_t i)       {return at(i);}
      StFpsSlat * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFpsSlat *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecFpsSlat,1) 
};
typedef       StFpsSlatIterator  StPtrVecFpsSlatIterator;
typedef const_StFpsSlatIterator  StPtrVecFpsSlatConstIterator;
typedef       StFpsSlatIterator  StSPtrVecFpsSlatIterator;
typedef const_StFpsSlatIterator  StSPtrVecFpsSlatConstIterator;

//______________________________________________________________
class StFtpcHit;
typedef StFtpcHit**            StFtpcHitIterator;
typedef StFtpcHit * const * const_StFtpcHitIterator;

class StPtrVecFtpcHit : public StRefArray 
{ 
public: 
StPtrVecFtpcHit(Int_t sz=0):StRefArray(sz){};
StPtrVecFtpcHit(const StPtrVecFtpcHit &from):StRefArray(from){};
virtual        ~StPtrVecFtpcHit(){};

 StFtpcHit * const &at(Int_t idx) const {return (StFtpcHit  * const &)fV[idx];}
 StFtpcHit *       &at(Int_t idx)       {return (StFtpcHit  *       &)fV[idx];}

 StFtpcHit * const &front()       const {return (StFtpcHit  * const &)fV.front();}
 StFtpcHit *       &front()             {return (StFtpcHit  *       &)fV.front();}

 StFtpcHit * const &back()        const {return (StFtpcHit  * const &)fV.back();}
 StFtpcHit *       &back()              {return (StFtpcHit  *       &)fV.back();}

const_StFtpcHitIterator begin() const {return (const_StFtpcHitIterator)&(*(fV.begin()));}
      StFtpcHitIterator begin()       {return (      StFtpcHitIterator)&(*(fV.begin()));}
const_StFtpcHitIterator end()   const {return (const_StFtpcHitIterator)&(*(fV.end()));}
      StFtpcHitIterator end()         {return (      StFtpcHitIterator)&(*(fV.end()));}
      StFtpcHitIterator erase(StFtpcHitIterator  it)
      {return (StFtpcHitIterator)Erase((TObject**)it,0);}
      StFtpcHitIterator erase(StFtpcHitIterator fst,StFtpcHitIterator lst)
      {return (StFtpcHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StFtpcHit *       &operator[](Int_t i)       {return at(i);}
      StFtpcHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFtpcHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecFtpcHit ,1) 
};


class StSPtrVecFtpcHit : public StStrArray 
{ 
public: 
StSPtrVecFtpcHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecFtpcHit(const StSPtrVecFtpcHit &from):StStrArray(from){};

 StFtpcHit * const &at(Int_t idx) const {return (StFtpcHit  * const &)fV[idx];}
 StFtpcHit *       &at(Int_t idx)       {return (StFtpcHit  *       &)fV[idx];}

 StFtpcHit * const &front()       const {return (StFtpcHit  * const &)fV.front();}
 StFtpcHit *       &front()             {return (StFtpcHit  *       &)fV.front();}

 StFtpcHit * const &back()        const {return (StFtpcHit  * const &)fV.back();}
 StFtpcHit *       &back()              {return (StFtpcHit  *       &)fV.back();}

const_StFtpcHitIterator begin() const {return (const_StFtpcHitIterator)&(*(fV.begin()));}
      StFtpcHitIterator begin()       {return (      StFtpcHitIterator)&(*(fV.begin()));}
const_StFtpcHitIterator end()   const {return (const_StFtpcHitIterator)&(*(fV.end()));}
      StFtpcHitIterator end()         {return (      StFtpcHitIterator)&(*(fV.end()));}
      StFtpcHitIterator erase(StFtpcHitIterator  it)
      {return (StFtpcHitIterator)Erase((TObject**)it,1);}
      StFtpcHitIterator erase(StFtpcHitIterator fst,StFtpcHitIterator lst)
      {return (StFtpcHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StFtpcHit *       &operator[](Int_t i)       {return at(i);}
      StFtpcHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StFtpcHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecFtpcHit,1) 
};
typedef       StFtpcHitIterator  StPtrVecFtpcHitIterator;
typedef const_StFtpcHitIterator  StPtrVecFtpcHitConstIterator;
typedef       StFtpcHitIterator  StSPtrVecFtpcHitIterator;
typedef const_StFtpcHitIterator  StSPtrVecFtpcHitConstIterator;

//______________________________________________________________
class StHit;
typedef StHit**            StHitIterator;
typedef StHit * const * const_StHitIterator;

class StPtrVecHit : public StRefArray 
{ 
public: 
StPtrVecHit(Int_t sz=0):StRefArray(sz){};
StPtrVecHit(const StPtrVecHit &from):StRefArray(from){};
virtual        ~StPtrVecHit(){};

 StHit * const &at(Int_t idx) const {return (StHit  * const &)fV[idx];}
 StHit *       &at(Int_t idx)       {return (StHit  *       &)fV[idx];}

 StHit * const &front()       const {return (StHit  * const &)fV.front();}
 StHit *       &front()             {return (StHit  *       &)fV.front();}

 StHit * const &back()        const {return (StHit  * const &)fV.back();}
 StHit *       &back()              {return (StHit  *       &)fV.back();}

const_StHitIterator begin() const {return (const_StHitIterator)&(*(fV.begin()));}
      StHitIterator begin()       {return (      StHitIterator)&(*(fV.begin()));}
const_StHitIterator end()   const {return (const_StHitIterator)&(*(fV.end()));}
      StHitIterator end()         {return (      StHitIterator)&(*(fV.end()));}
      StHitIterator erase(StHitIterator  it)
      {return (StHitIterator)Erase((TObject**)it,0);}
      StHitIterator erase(StHitIterator fst,StHitIterator lst)
      {return (StHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHit *       &operator[](Int_t i)       {return at(i);}
      StHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHit ,1) 
};


class StSPtrVecHit : public StStrArray 
{ 
public: 
StSPtrVecHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecHit(const StSPtrVecHit &from):StStrArray(from){};

 StHit * const &at(Int_t idx) const {return (StHit  * const &)fV[idx];}
 StHit *       &at(Int_t idx)       {return (StHit  *       &)fV[idx];}

 StHit * const &front()       const {return (StHit  * const &)fV.front();}
 StHit *       &front()             {return (StHit  *       &)fV.front();}

 StHit * const &back()        const {return (StHit  * const &)fV.back();}
 StHit *       &back()              {return (StHit  *       &)fV.back();}

const_StHitIterator begin() const {return (const_StHitIterator)&(*(fV.begin()));}
      StHitIterator begin()       {return (      StHitIterator)&(*(fV.begin()));}
const_StHitIterator end()   const {return (const_StHitIterator)&(*(fV.end()));}
      StHitIterator end()         {return (      StHitIterator)&(*(fV.end()));}
      StHitIterator erase(StHitIterator  it)
      {return (StHitIterator)Erase((TObject**)it,1);}
      StHitIterator erase(StHitIterator fst,StHitIterator lst)
      {return (StHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHit *       &operator[](Int_t i)       {return at(i);}
      StHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHit,1) 
};
typedef       StHitIterator  StPtrVecHitIterator;
typedef const_StHitIterator  StPtrVecHitConstIterator;
typedef       StHitIterator  StSPtrVecHitIterator;
typedef const_StHitIterator  StSPtrVecHitConstIterator;

//______________________________________________________________
class StHltBEmcTowerHit;
typedef StHltBEmcTowerHit**            StHltBEmcTowerHitIterator;
typedef StHltBEmcTowerHit * const * const_StHltBEmcTowerHitIterator;

class StPtrVecHltBEmcTowerHit : public StRefArray 
{ 
public: 
StPtrVecHltBEmcTowerHit(Int_t sz=0):StRefArray(sz){};
StPtrVecHltBEmcTowerHit(const StPtrVecHltBEmcTowerHit &from):StRefArray(from){};
virtual        ~StPtrVecHltBEmcTowerHit(){};

 StHltBEmcTowerHit * const &at(Int_t idx) const {return (StHltBEmcTowerHit  * const &)fV[idx];}
 StHltBEmcTowerHit *       &at(Int_t idx)       {return (StHltBEmcTowerHit  *       &)fV[idx];}

 StHltBEmcTowerHit * const &front()       const {return (StHltBEmcTowerHit  * const &)fV.front();}
 StHltBEmcTowerHit *       &front()             {return (StHltBEmcTowerHit  *       &)fV.front();}

 StHltBEmcTowerHit * const &back()        const {return (StHltBEmcTowerHit  * const &)fV.back();}
 StHltBEmcTowerHit *       &back()              {return (StHltBEmcTowerHit  *       &)fV.back();}

const_StHltBEmcTowerHitIterator begin() const {return (const_StHltBEmcTowerHitIterator)&(*(fV.begin()));}
      StHltBEmcTowerHitIterator begin()       {return (      StHltBEmcTowerHitIterator)&(*(fV.begin()));}
const_StHltBEmcTowerHitIterator end()   const {return (const_StHltBEmcTowerHitIterator)&(*(fV.end()));}
      StHltBEmcTowerHitIterator end()         {return (      StHltBEmcTowerHitIterator)&(*(fV.end()));}
      StHltBEmcTowerHitIterator erase(StHltBEmcTowerHitIterator  it)
      {return (StHltBEmcTowerHitIterator)Erase((TObject**)it,0);}
      StHltBEmcTowerHitIterator erase(StHltBEmcTowerHitIterator fst,StHltBEmcTowerHitIterator lst)
      {return (StHltBEmcTowerHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHltBEmcTowerHit *       &operator[](Int_t i)       {return at(i);}
      StHltBEmcTowerHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltBEmcTowerHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHltBEmcTowerHit ,1) 
};


class StSPtrVecHltBEmcTowerHit : public StStrArray 
{ 
public: 
StSPtrVecHltBEmcTowerHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecHltBEmcTowerHit(const StSPtrVecHltBEmcTowerHit &from):StStrArray(from){};

 StHltBEmcTowerHit * const &at(Int_t idx) const {return (StHltBEmcTowerHit  * const &)fV[idx];}
 StHltBEmcTowerHit *       &at(Int_t idx)       {return (StHltBEmcTowerHit  *       &)fV[idx];}

 StHltBEmcTowerHit * const &front()       const {return (StHltBEmcTowerHit  * const &)fV.front();}
 StHltBEmcTowerHit *       &front()             {return (StHltBEmcTowerHit  *       &)fV.front();}

 StHltBEmcTowerHit * const &back()        const {return (StHltBEmcTowerHit  * const &)fV.back();}
 StHltBEmcTowerHit *       &back()              {return (StHltBEmcTowerHit  *       &)fV.back();}

const_StHltBEmcTowerHitIterator begin() const {return (const_StHltBEmcTowerHitIterator)&(*(fV.begin()));}
      StHltBEmcTowerHitIterator begin()       {return (      StHltBEmcTowerHitIterator)&(*(fV.begin()));}
const_StHltBEmcTowerHitIterator end()   const {return (const_StHltBEmcTowerHitIterator)&(*(fV.end()));}
      StHltBEmcTowerHitIterator end()         {return (      StHltBEmcTowerHitIterator)&(*(fV.end()));}
      StHltBEmcTowerHitIterator erase(StHltBEmcTowerHitIterator  it)
      {return (StHltBEmcTowerHitIterator)Erase((TObject**)it,1);}
      StHltBEmcTowerHitIterator erase(StHltBEmcTowerHitIterator fst,StHltBEmcTowerHitIterator lst)
      {return (StHltBEmcTowerHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHltBEmcTowerHit *       &operator[](Int_t i)       {return at(i);}
      StHltBEmcTowerHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltBEmcTowerHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHltBEmcTowerHit,1) 
};
typedef       StHltBEmcTowerHitIterator  StPtrVecHltBEmcTowerHitIterator;
typedef const_StHltBEmcTowerHitIterator  StPtrVecHltBEmcTowerHitConstIterator;
typedef       StHltBEmcTowerHitIterator  StSPtrVecHltBEmcTowerHitIterator;
typedef const_StHltBEmcTowerHitIterator  StSPtrVecHltBEmcTowerHitConstIterator;

//______________________________________________________________
class StHltBTofHit;
typedef StHltBTofHit**            StHltBTofHitIterator;
typedef StHltBTofHit * const * const_StHltBTofHitIterator;

class StPtrVecHltBTofHit : public StRefArray 
{ 
public: 
StPtrVecHltBTofHit(Int_t sz=0):StRefArray(sz){};
StPtrVecHltBTofHit(const StPtrVecHltBTofHit &from):StRefArray(from){};
virtual        ~StPtrVecHltBTofHit(){};

 StHltBTofHit * const &at(Int_t idx) const {return (StHltBTofHit  * const &)fV[idx];}
 StHltBTofHit *       &at(Int_t idx)       {return (StHltBTofHit  *       &)fV[idx];}

 StHltBTofHit * const &front()       const {return (StHltBTofHit  * const &)fV.front();}
 StHltBTofHit *       &front()             {return (StHltBTofHit  *       &)fV.front();}

 StHltBTofHit * const &back()        const {return (StHltBTofHit  * const &)fV.back();}
 StHltBTofHit *       &back()              {return (StHltBTofHit  *       &)fV.back();}

const_StHltBTofHitIterator begin() const {return (const_StHltBTofHitIterator)&(*(fV.begin()));}
      StHltBTofHitIterator begin()       {return (      StHltBTofHitIterator)&(*(fV.begin()));}
const_StHltBTofHitIterator end()   const {return (const_StHltBTofHitIterator)&(*(fV.end()));}
      StHltBTofHitIterator end()         {return (      StHltBTofHitIterator)&(*(fV.end()));}
      StHltBTofHitIterator erase(StHltBTofHitIterator  it)
      {return (StHltBTofHitIterator)Erase((TObject**)it,0);}
      StHltBTofHitIterator erase(StHltBTofHitIterator fst,StHltBTofHitIterator lst)
      {return (StHltBTofHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHltBTofHit *       &operator[](Int_t i)       {return at(i);}
      StHltBTofHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltBTofHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHltBTofHit ,1) 
};


class StSPtrVecHltBTofHit : public StStrArray 
{ 
public: 
StSPtrVecHltBTofHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecHltBTofHit(const StSPtrVecHltBTofHit &from):StStrArray(from){};

 StHltBTofHit * const &at(Int_t idx) const {return (StHltBTofHit  * const &)fV[idx];}
 StHltBTofHit *       &at(Int_t idx)       {return (StHltBTofHit  *       &)fV[idx];}

 StHltBTofHit * const &front()       const {return (StHltBTofHit  * const &)fV.front();}
 StHltBTofHit *       &front()             {return (StHltBTofHit  *       &)fV.front();}

 StHltBTofHit * const &back()        const {return (StHltBTofHit  * const &)fV.back();}
 StHltBTofHit *       &back()              {return (StHltBTofHit  *       &)fV.back();}

const_StHltBTofHitIterator begin() const {return (const_StHltBTofHitIterator)&(*(fV.begin()));}
      StHltBTofHitIterator begin()       {return (      StHltBTofHitIterator)&(*(fV.begin()));}
const_StHltBTofHitIterator end()   const {return (const_StHltBTofHitIterator)&(*(fV.end()));}
      StHltBTofHitIterator end()         {return (      StHltBTofHitIterator)&(*(fV.end()));}
      StHltBTofHitIterator erase(StHltBTofHitIterator  it)
      {return (StHltBTofHitIterator)Erase((TObject**)it,1);}
      StHltBTofHitIterator erase(StHltBTofHitIterator fst,StHltBTofHitIterator lst)
      {return (StHltBTofHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHltBTofHit *       &operator[](Int_t i)       {return at(i);}
      StHltBTofHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltBTofHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHltBTofHit,1) 
};
typedef       StHltBTofHitIterator  StPtrVecHltBTofHitIterator;
typedef const_StHltBTofHitIterator  StPtrVecHltBTofHitConstIterator;
typedef       StHltBTofHitIterator  StSPtrVecHltBTofHitIterator;
typedef const_StHltBTofHitIterator  StSPtrVecHltBTofHitConstIterator;

//______________________________________________________________
class StHltDiElectron;
typedef StHltDiElectron**            StHltDiElectronIterator;
typedef StHltDiElectron * const * const_StHltDiElectronIterator;

class StPtrVecHltDiElectron : public StRefArray 
{ 
public: 
StPtrVecHltDiElectron(Int_t sz=0):StRefArray(sz){};
StPtrVecHltDiElectron(const StPtrVecHltDiElectron &from):StRefArray(from){};
virtual        ~StPtrVecHltDiElectron(){};

 StHltDiElectron * const &at(Int_t idx) const {return (StHltDiElectron  * const &)fV[idx];}
 StHltDiElectron *       &at(Int_t idx)       {return (StHltDiElectron  *       &)fV[idx];}

 StHltDiElectron * const &front()       const {return (StHltDiElectron  * const &)fV.front();}
 StHltDiElectron *       &front()             {return (StHltDiElectron  *       &)fV.front();}

 StHltDiElectron * const &back()        const {return (StHltDiElectron  * const &)fV.back();}
 StHltDiElectron *       &back()              {return (StHltDiElectron  *       &)fV.back();}

const_StHltDiElectronIterator begin() const {return (const_StHltDiElectronIterator)&(*(fV.begin()));}
      StHltDiElectronIterator begin()       {return (      StHltDiElectronIterator)&(*(fV.begin()));}
const_StHltDiElectronIterator end()   const {return (const_StHltDiElectronIterator)&(*(fV.end()));}
      StHltDiElectronIterator end()         {return (      StHltDiElectronIterator)&(*(fV.end()));}
      StHltDiElectronIterator erase(StHltDiElectronIterator  it)
      {return (StHltDiElectronIterator)Erase((TObject**)it,0);}
      StHltDiElectronIterator erase(StHltDiElectronIterator fst,StHltDiElectronIterator lst)
      {return (StHltDiElectronIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHltDiElectron *       &operator[](Int_t i)       {return at(i);}
      StHltDiElectron * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltDiElectron * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHltDiElectron ,1) 
};


class StSPtrVecHltDiElectron : public StStrArray 
{ 
public: 
StSPtrVecHltDiElectron(Int_t sz=0):StStrArray(sz){};
StSPtrVecHltDiElectron(const StSPtrVecHltDiElectron &from):StStrArray(from){};

 StHltDiElectron * const &at(Int_t idx) const {return (StHltDiElectron  * const &)fV[idx];}
 StHltDiElectron *       &at(Int_t idx)       {return (StHltDiElectron  *       &)fV[idx];}

 StHltDiElectron * const &front()       const {return (StHltDiElectron  * const &)fV.front();}
 StHltDiElectron *       &front()             {return (StHltDiElectron  *       &)fV.front();}

 StHltDiElectron * const &back()        const {return (StHltDiElectron  * const &)fV.back();}
 StHltDiElectron *       &back()              {return (StHltDiElectron  *       &)fV.back();}

const_StHltDiElectronIterator begin() const {return (const_StHltDiElectronIterator)&(*(fV.begin()));}
      StHltDiElectronIterator begin()       {return (      StHltDiElectronIterator)&(*(fV.begin()));}
const_StHltDiElectronIterator end()   const {return (const_StHltDiElectronIterator)&(*(fV.end()));}
      StHltDiElectronIterator end()         {return (      StHltDiElectronIterator)&(*(fV.end()));}
      StHltDiElectronIterator erase(StHltDiElectronIterator  it)
      {return (StHltDiElectronIterator)Erase((TObject**)it,1);}
      StHltDiElectronIterator erase(StHltDiElectronIterator fst,StHltDiElectronIterator lst)
      {return (StHltDiElectronIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHltDiElectron *       &operator[](Int_t i)       {return at(i);}
      StHltDiElectron * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltDiElectron *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHltDiElectron,1) 
};
typedef       StHltDiElectronIterator  StPtrVecHltDiElectronIterator;
typedef const_StHltDiElectronIterator  StPtrVecHltDiElectronConstIterator;
typedef       StHltDiElectronIterator  StSPtrVecHltDiElectronIterator;
typedef const_StHltDiElectronIterator  StSPtrVecHltDiElectronConstIterator;

//______________________________________________________________
class StHltHeavyFragment;
typedef StHltHeavyFragment**            StHltHeavyFragmentIterator;
typedef StHltHeavyFragment * const * const_StHltHeavyFragmentIterator;

class StPtrVecHltHeavyFragment : public StRefArray 
{ 
public: 
StPtrVecHltHeavyFragment(Int_t sz=0):StRefArray(sz){};
StPtrVecHltHeavyFragment(const StPtrVecHltHeavyFragment &from):StRefArray(from){};
virtual        ~StPtrVecHltHeavyFragment(){};

 StHltHeavyFragment * const &at(Int_t idx) const {return (StHltHeavyFragment  * const &)fV[idx];}
 StHltHeavyFragment *       &at(Int_t idx)       {return (StHltHeavyFragment  *       &)fV[idx];}

 StHltHeavyFragment * const &front()       const {return (StHltHeavyFragment  * const &)fV.front();}
 StHltHeavyFragment *       &front()             {return (StHltHeavyFragment  *       &)fV.front();}

 StHltHeavyFragment * const &back()        const {return (StHltHeavyFragment  * const &)fV.back();}
 StHltHeavyFragment *       &back()              {return (StHltHeavyFragment  *       &)fV.back();}

const_StHltHeavyFragmentIterator begin() const {return (const_StHltHeavyFragmentIterator)&(*(fV.begin()));}
      StHltHeavyFragmentIterator begin()       {return (      StHltHeavyFragmentIterator)&(*(fV.begin()));}
const_StHltHeavyFragmentIterator end()   const {return (const_StHltHeavyFragmentIterator)&(*(fV.end()));}
      StHltHeavyFragmentIterator end()         {return (      StHltHeavyFragmentIterator)&(*(fV.end()));}
      StHltHeavyFragmentIterator erase(StHltHeavyFragmentIterator  it)
      {return (StHltHeavyFragmentIterator)Erase((TObject**)it,0);}
      StHltHeavyFragmentIterator erase(StHltHeavyFragmentIterator fst,StHltHeavyFragmentIterator lst)
      {return (StHltHeavyFragmentIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHltHeavyFragment *       &operator[](Int_t i)       {return at(i);}
      StHltHeavyFragment * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltHeavyFragment * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHltHeavyFragment ,1) 
};


class StSPtrVecHltHeavyFragment : public StStrArray 
{ 
public: 
StSPtrVecHltHeavyFragment(Int_t sz=0):StStrArray(sz){};
StSPtrVecHltHeavyFragment(const StSPtrVecHltHeavyFragment &from):StStrArray(from){};

 StHltHeavyFragment * const &at(Int_t idx) const {return (StHltHeavyFragment  * const &)fV[idx];}
 StHltHeavyFragment *       &at(Int_t idx)       {return (StHltHeavyFragment  *       &)fV[idx];}

 StHltHeavyFragment * const &front()       const {return (StHltHeavyFragment  * const &)fV.front();}
 StHltHeavyFragment *       &front()             {return (StHltHeavyFragment  *       &)fV.front();}

 StHltHeavyFragment * const &back()        const {return (StHltHeavyFragment  * const &)fV.back();}
 StHltHeavyFragment *       &back()              {return (StHltHeavyFragment  *       &)fV.back();}

const_StHltHeavyFragmentIterator begin() const {return (const_StHltHeavyFragmentIterator)&(*(fV.begin()));}
      StHltHeavyFragmentIterator begin()       {return (      StHltHeavyFragmentIterator)&(*(fV.begin()));}
const_StHltHeavyFragmentIterator end()   const {return (const_StHltHeavyFragmentIterator)&(*(fV.end()));}
      StHltHeavyFragmentIterator end()         {return (      StHltHeavyFragmentIterator)&(*(fV.end()));}
      StHltHeavyFragmentIterator erase(StHltHeavyFragmentIterator  it)
      {return (StHltHeavyFragmentIterator)Erase((TObject**)it,1);}
      StHltHeavyFragmentIterator erase(StHltHeavyFragmentIterator fst,StHltHeavyFragmentIterator lst)
      {return (StHltHeavyFragmentIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHltHeavyFragment *       &operator[](Int_t i)       {return at(i);}
      StHltHeavyFragment * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltHeavyFragment *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHltHeavyFragment,1) 
};
typedef       StHltHeavyFragmentIterator  StPtrVecHltHeavyFragmentIterator;
typedef const_StHltHeavyFragmentIterator  StPtrVecHltHeavyFragmentConstIterator;
typedef       StHltHeavyFragmentIterator  StSPtrVecHltHeavyFragmentIterator;
typedef const_StHltHeavyFragmentIterator  StSPtrVecHltHeavyFragmentConstIterator;

//______________________________________________________________
class StHltHighPt;
typedef StHltHighPt**            StHltHighPtIterator;
typedef StHltHighPt * const * const_StHltHighPtIterator;

class StPtrVecHltHighPt : public StRefArray 
{ 
public: 
StPtrVecHltHighPt(Int_t sz=0):StRefArray(sz){};
StPtrVecHltHighPt(const StPtrVecHltHighPt &from):StRefArray(from){};
virtual        ~StPtrVecHltHighPt(){};

 StHltHighPt * const &at(Int_t idx) const {return (StHltHighPt  * const &)fV[idx];}
 StHltHighPt *       &at(Int_t idx)       {return (StHltHighPt  *       &)fV[idx];}

 StHltHighPt * const &front()       const {return (StHltHighPt  * const &)fV.front();}
 StHltHighPt *       &front()             {return (StHltHighPt  *       &)fV.front();}

 StHltHighPt * const &back()        const {return (StHltHighPt  * const &)fV.back();}
 StHltHighPt *       &back()              {return (StHltHighPt  *       &)fV.back();}

const_StHltHighPtIterator begin() const {return (const_StHltHighPtIterator)&(*(fV.begin()));}
      StHltHighPtIterator begin()       {return (      StHltHighPtIterator)&(*(fV.begin()));}
const_StHltHighPtIterator end()   const {return (const_StHltHighPtIterator)&(*(fV.end()));}
      StHltHighPtIterator end()         {return (      StHltHighPtIterator)&(*(fV.end()));}
      StHltHighPtIterator erase(StHltHighPtIterator  it)
      {return (StHltHighPtIterator)Erase((TObject**)it,0);}
      StHltHighPtIterator erase(StHltHighPtIterator fst,StHltHighPtIterator lst)
      {return (StHltHighPtIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHltHighPt *       &operator[](Int_t i)       {return at(i);}
      StHltHighPt * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltHighPt * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHltHighPt ,1) 
};


class StSPtrVecHltHighPt : public StStrArray 
{ 
public: 
StSPtrVecHltHighPt(Int_t sz=0):StStrArray(sz){};
StSPtrVecHltHighPt(const StSPtrVecHltHighPt &from):StStrArray(from){};

 StHltHighPt * const &at(Int_t idx) const {return (StHltHighPt  * const &)fV[idx];}
 StHltHighPt *       &at(Int_t idx)       {return (StHltHighPt  *       &)fV[idx];}

 StHltHighPt * const &front()       const {return (StHltHighPt  * const &)fV.front();}
 StHltHighPt *       &front()             {return (StHltHighPt  *       &)fV.front();}

 StHltHighPt * const &back()        const {return (StHltHighPt  * const &)fV.back();}
 StHltHighPt *       &back()              {return (StHltHighPt  *       &)fV.back();}

const_StHltHighPtIterator begin() const {return (const_StHltHighPtIterator)&(*(fV.begin()));}
      StHltHighPtIterator begin()       {return (      StHltHighPtIterator)&(*(fV.begin()));}
const_StHltHighPtIterator end()   const {return (const_StHltHighPtIterator)&(*(fV.end()));}
      StHltHighPtIterator end()         {return (      StHltHighPtIterator)&(*(fV.end()));}
      StHltHighPtIterator erase(StHltHighPtIterator  it)
      {return (StHltHighPtIterator)Erase((TObject**)it,1);}
      StHltHighPtIterator erase(StHltHighPtIterator fst,StHltHighPtIterator lst)
      {return (StHltHighPtIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHltHighPt *       &operator[](Int_t i)       {return at(i);}
      StHltHighPt * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltHighPt *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHltHighPt,1) 
};
typedef       StHltHighPtIterator  StPtrVecHltHighPtIterator;
typedef const_StHltHighPtIterator  StPtrVecHltHighPtConstIterator;
typedef       StHltHighPtIterator  StSPtrVecHltHighPtIterator;
typedef const_StHltHighPtIterator  StSPtrVecHltHighPtConstIterator;

//______________________________________________________________
class StHltTrack;
typedef StHltTrack**            StHltTrackIterator;
typedef StHltTrack * const * const_StHltTrackIterator;

class StPtrVecHltTrack : public StRefArray 
{ 
public: 
StPtrVecHltTrack(Int_t sz=0):StRefArray(sz){};
StPtrVecHltTrack(const StPtrVecHltTrack &from):StRefArray(from){};
virtual        ~StPtrVecHltTrack(){};

 StHltTrack * const &at(Int_t idx) const {return (StHltTrack  * const &)fV[idx];}
 StHltTrack *       &at(Int_t idx)       {return (StHltTrack  *       &)fV[idx];}

 StHltTrack * const &front()       const {return (StHltTrack  * const &)fV.front();}
 StHltTrack *       &front()             {return (StHltTrack  *       &)fV.front();}

 StHltTrack * const &back()        const {return (StHltTrack  * const &)fV.back();}
 StHltTrack *       &back()              {return (StHltTrack  *       &)fV.back();}

const_StHltTrackIterator begin() const {return (const_StHltTrackIterator)&(*(fV.begin()));}
      StHltTrackIterator begin()       {return (      StHltTrackIterator)&(*(fV.begin()));}
const_StHltTrackIterator end()   const {return (const_StHltTrackIterator)&(*(fV.end()));}
      StHltTrackIterator end()         {return (      StHltTrackIterator)&(*(fV.end()));}
      StHltTrackIterator erase(StHltTrackIterator  it)
      {return (StHltTrackIterator)Erase((TObject**)it,0);}
      StHltTrackIterator erase(StHltTrackIterator fst,StHltTrackIterator lst)
      {return (StHltTrackIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHltTrack *       &operator[](Int_t i)       {return at(i);}
      StHltTrack * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltTrack * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHltTrack ,1) 
};


class StSPtrVecHltTrack : public StStrArray 
{ 
public: 
StSPtrVecHltTrack(Int_t sz=0):StStrArray(sz){};
StSPtrVecHltTrack(const StSPtrVecHltTrack &from):StStrArray(from){};

 StHltTrack * const &at(Int_t idx) const {return (StHltTrack  * const &)fV[idx];}
 StHltTrack *       &at(Int_t idx)       {return (StHltTrack  *       &)fV[idx];}

 StHltTrack * const &front()       const {return (StHltTrack  * const &)fV.front();}
 StHltTrack *       &front()             {return (StHltTrack  *       &)fV.front();}

 StHltTrack * const &back()        const {return (StHltTrack  * const &)fV.back();}
 StHltTrack *       &back()              {return (StHltTrack  *       &)fV.back();}

const_StHltTrackIterator begin() const {return (const_StHltTrackIterator)&(*(fV.begin()));}
      StHltTrackIterator begin()       {return (      StHltTrackIterator)&(*(fV.begin()));}
const_StHltTrackIterator end()   const {return (const_StHltTrackIterator)&(*(fV.end()));}
      StHltTrackIterator end()         {return (      StHltTrackIterator)&(*(fV.end()));}
      StHltTrackIterator erase(StHltTrackIterator  it)
      {return (StHltTrackIterator)Erase((TObject**)it,1);}
      StHltTrackIterator erase(StHltTrackIterator fst,StHltTrackIterator lst)
      {return (StHltTrackIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHltTrack *       &operator[](Int_t i)       {return at(i);}
      StHltTrack * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltTrack *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHltTrack,1) 
};
typedef       StHltTrackIterator  StPtrVecHltTrackIterator;
typedef const_StHltTrackIterator  StPtrVecHltTrackConstIterator;
typedef       StHltTrackIterator  StSPtrVecHltTrackIterator;
typedef const_StHltTrackIterator  StSPtrVecHltTrackConstIterator;

//______________________________________________________________
class StHltTrackNode;
typedef StHltTrackNode**            StHltTrackNodeIterator;
typedef StHltTrackNode * const * const_StHltTrackNodeIterator;

class StPtrVecHltTrackNode : public StRefArray 
{ 
public: 
StPtrVecHltTrackNode(Int_t sz=0):StRefArray(sz){};
StPtrVecHltTrackNode(const StPtrVecHltTrackNode &from):StRefArray(from){};
virtual        ~StPtrVecHltTrackNode(){};

 StHltTrackNode * const &at(Int_t idx) const {return (StHltTrackNode  * const &)fV[idx];}
 StHltTrackNode *       &at(Int_t idx)       {return (StHltTrackNode  *       &)fV[idx];}

 StHltTrackNode * const &front()       const {return (StHltTrackNode  * const &)fV.front();}
 StHltTrackNode *       &front()             {return (StHltTrackNode  *       &)fV.front();}

 StHltTrackNode * const &back()        const {return (StHltTrackNode  * const &)fV.back();}
 StHltTrackNode *       &back()              {return (StHltTrackNode  *       &)fV.back();}

const_StHltTrackNodeIterator begin() const {return (const_StHltTrackNodeIterator)&(*(fV.begin()));}
      StHltTrackNodeIterator begin()       {return (      StHltTrackNodeIterator)&(*(fV.begin()));}
const_StHltTrackNodeIterator end()   const {return (const_StHltTrackNodeIterator)&(*(fV.end()));}
      StHltTrackNodeIterator end()         {return (      StHltTrackNodeIterator)&(*(fV.end()));}
      StHltTrackNodeIterator erase(StHltTrackNodeIterator  it)
      {return (StHltTrackNodeIterator)Erase((TObject**)it,0);}
      StHltTrackNodeIterator erase(StHltTrackNodeIterator fst,StHltTrackNodeIterator lst)
      {return (StHltTrackNodeIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHltTrackNode *       &operator[](Int_t i)       {return at(i);}
      StHltTrackNode * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltTrackNode * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHltTrackNode ,1) 
};


class StSPtrVecHltTrackNode : public StStrArray 
{ 
public: 
StSPtrVecHltTrackNode(Int_t sz=0):StStrArray(sz){};
StSPtrVecHltTrackNode(const StSPtrVecHltTrackNode &from):StStrArray(from){};

 StHltTrackNode * const &at(Int_t idx) const {return (StHltTrackNode  * const &)fV[idx];}
 StHltTrackNode *       &at(Int_t idx)       {return (StHltTrackNode  *       &)fV[idx];}

 StHltTrackNode * const &front()       const {return (StHltTrackNode  * const &)fV.front();}
 StHltTrackNode *       &front()             {return (StHltTrackNode  *       &)fV.front();}

 StHltTrackNode * const &back()        const {return (StHltTrackNode  * const &)fV.back();}
 StHltTrackNode *       &back()              {return (StHltTrackNode  *       &)fV.back();}

const_StHltTrackNodeIterator begin() const {return (const_StHltTrackNodeIterator)&(*(fV.begin()));}
      StHltTrackNodeIterator begin()       {return (      StHltTrackNodeIterator)&(*(fV.begin()));}
const_StHltTrackNodeIterator end()   const {return (const_StHltTrackNodeIterator)&(*(fV.end()));}
      StHltTrackNodeIterator end()         {return (      StHltTrackNodeIterator)&(*(fV.end()));}
      StHltTrackNodeIterator erase(StHltTrackNodeIterator  it)
      {return (StHltTrackNodeIterator)Erase((TObject**)it,1);}
      StHltTrackNodeIterator erase(StHltTrackNodeIterator fst,StHltTrackNodeIterator lst)
      {return (StHltTrackNodeIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHltTrackNode *       &operator[](Int_t i)       {return at(i);}
      StHltTrackNode * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltTrackNode *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHltTrackNode,1) 
};
typedef       StHltTrackNodeIterator  StPtrVecHltTrackNodeIterator;
typedef const_StHltTrackNodeIterator  StPtrVecHltTrackNodeConstIterator;
typedef       StHltTrackNodeIterator  StSPtrVecHltTrackNodeIterator;
typedef const_StHltTrackNodeIterator  StSPtrVecHltTrackNodeConstIterator;

//______________________________________________________________
class StHltTriggerReason;
typedef StHltTriggerReason**            StHltTriggerReasonIterator;
typedef StHltTriggerReason * const * const_StHltTriggerReasonIterator;

class StPtrVecHltTriggerReason : public StRefArray 
{ 
public: 
StPtrVecHltTriggerReason(Int_t sz=0):StRefArray(sz){};
StPtrVecHltTriggerReason(const StPtrVecHltTriggerReason &from):StRefArray(from){};
virtual        ~StPtrVecHltTriggerReason(){};

 StHltTriggerReason * const &at(Int_t idx) const {return (StHltTriggerReason  * const &)fV[idx];}
 StHltTriggerReason *       &at(Int_t idx)       {return (StHltTriggerReason  *       &)fV[idx];}

 StHltTriggerReason * const &front()       const {return (StHltTriggerReason  * const &)fV.front();}
 StHltTriggerReason *       &front()             {return (StHltTriggerReason  *       &)fV.front();}

 StHltTriggerReason * const &back()        const {return (StHltTriggerReason  * const &)fV.back();}
 StHltTriggerReason *       &back()              {return (StHltTriggerReason  *       &)fV.back();}

const_StHltTriggerReasonIterator begin() const {return (const_StHltTriggerReasonIterator)&(*(fV.begin()));}
      StHltTriggerReasonIterator begin()       {return (      StHltTriggerReasonIterator)&(*(fV.begin()));}
const_StHltTriggerReasonIterator end()   const {return (const_StHltTriggerReasonIterator)&(*(fV.end()));}
      StHltTriggerReasonIterator end()         {return (      StHltTriggerReasonIterator)&(*(fV.end()));}
      StHltTriggerReasonIterator erase(StHltTriggerReasonIterator  it)
      {return (StHltTriggerReasonIterator)Erase((TObject**)it,0);}
      StHltTriggerReasonIterator erase(StHltTriggerReasonIterator fst,StHltTriggerReasonIterator lst)
      {return (StHltTriggerReasonIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHltTriggerReason *       &operator[](Int_t i)       {return at(i);}
      StHltTriggerReason * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltTriggerReason * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHltTriggerReason ,1) 
};


class StSPtrVecHltTriggerReason : public StStrArray 
{ 
public: 
StSPtrVecHltTriggerReason(Int_t sz=0):StStrArray(sz){};
StSPtrVecHltTriggerReason(const StSPtrVecHltTriggerReason &from):StStrArray(from){};

 StHltTriggerReason * const &at(Int_t idx) const {return (StHltTriggerReason  * const &)fV[idx];}
 StHltTriggerReason *       &at(Int_t idx)       {return (StHltTriggerReason  *       &)fV[idx];}

 StHltTriggerReason * const &front()       const {return (StHltTriggerReason  * const &)fV.front();}
 StHltTriggerReason *       &front()             {return (StHltTriggerReason  *       &)fV.front();}

 StHltTriggerReason * const &back()        const {return (StHltTriggerReason  * const &)fV.back();}
 StHltTriggerReason *       &back()              {return (StHltTriggerReason  *       &)fV.back();}

const_StHltTriggerReasonIterator begin() const {return (const_StHltTriggerReasonIterator)&(*(fV.begin()));}
      StHltTriggerReasonIterator begin()       {return (      StHltTriggerReasonIterator)&(*(fV.begin()));}
const_StHltTriggerReasonIterator end()   const {return (const_StHltTriggerReasonIterator)&(*(fV.end()));}
      StHltTriggerReasonIterator end()         {return (      StHltTriggerReasonIterator)&(*(fV.end()));}
      StHltTriggerReasonIterator erase(StHltTriggerReasonIterator  it)
      {return (StHltTriggerReasonIterator)Erase((TObject**)it,1);}
      StHltTriggerReasonIterator erase(StHltTriggerReasonIterator fst,StHltTriggerReasonIterator lst)
      {return (StHltTriggerReasonIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHltTriggerReason *       &operator[](Int_t i)       {return at(i);}
      StHltTriggerReason * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltTriggerReason *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHltTriggerReason,1) 
};
typedef       StHltTriggerReasonIterator  StPtrVecHltTriggerReasonIterator;
typedef const_StHltTriggerReasonIterator  StPtrVecHltTriggerReasonConstIterator;
typedef       StHltTriggerReasonIterator  StSPtrVecHltTriggerReasonIterator;
typedef const_StHltTriggerReasonIterator  StSPtrVecHltTriggerReasonConstIterator;

//______________________________________________________________
class StHltVpdHit;
typedef StHltVpdHit**            StHltVpdHitIterator;
typedef StHltVpdHit * const * const_StHltVpdHitIterator;

class StPtrVecHltVpdHit : public StRefArray 
{ 
public: 
StPtrVecHltVpdHit(Int_t sz=0):StRefArray(sz){};
StPtrVecHltVpdHit(const StPtrVecHltVpdHit &from):StRefArray(from){};
virtual        ~StPtrVecHltVpdHit(){};

 StHltVpdHit * const &at(Int_t idx) const {return (StHltVpdHit  * const &)fV[idx];}
 StHltVpdHit *       &at(Int_t idx)       {return (StHltVpdHit  *       &)fV[idx];}

 StHltVpdHit * const &front()       const {return (StHltVpdHit  * const &)fV.front();}
 StHltVpdHit *       &front()             {return (StHltVpdHit  *       &)fV.front();}

 StHltVpdHit * const &back()        const {return (StHltVpdHit  * const &)fV.back();}
 StHltVpdHit *       &back()              {return (StHltVpdHit  *       &)fV.back();}

const_StHltVpdHitIterator begin() const {return (const_StHltVpdHitIterator)&(*(fV.begin()));}
      StHltVpdHitIterator begin()       {return (      StHltVpdHitIterator)&(*(fV.begin()));}
const_StHltVpdHitIterator end()   const {return (const_StHltVpdHitIterator)&(*(fV.end()));}
      StHltVpdHitIterator end()         {return (      StHltVpdHitIterator)&(*(fV.end()));}
      StHltVpdHitIterator erase(StHltVpdHitIterator  it)
      {return (StHltVpdHitIterator)Erase((TObject**)it,0);}
      StHltVpdHitIterator erase(StHltVpdHitIterator fst,StHltVpdHitIterator lst)
      {return (StHltVpdHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StHltVpdHit *       &operator[](Int_t i)       {return at(i);}
      StHltVpdHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltVpdHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecHltVpdHit ,1) 
};


class StSPtrVecHltVpdHit : public StStrArray 
{ 
public: 
StSPtrVecHltVpdHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecHltVpdHit(const StSPtrVecHltVpdHit &from):StStrArray(from){};

 StHltVpdHit * const &at(Int_t idx) const {return (StHltVpdHit  * const &)fV[idx];}
 StHltVpdHit *       &at(Int_t idx)       {return (StHltVpdHit  *       &)fV[idx];}

 StHltVpdHit * const &front()       const {return (StHltVpdHit  * const &)fV.front();}
 StHltVpdHit *       &front()             {return (StHltVpdHit  *       &)fV.front();}

 StHltVpdHit * const &back()        const {return (StHltVpdHit  * const &)fV.back();}
 StHltVpdHit *       &back()              {return (StHltVpdHit  *       &)fV.back();}

const_StHltVpdHitIterator begin() const {return (const_StHltVpdHitIterator)&(*(fV.begin()));}
      StHltVpdHitIterator begin()       {return (      StHltVpdHitIterator)&(*(fV.begin()));}
const_StHltVpdHitIterator end()   const {return (const_StHltVpdHitIterator)&(*(fV.end()));}
      StHltVpdHitIterator end()         {return (      StHltVpdHitIterator)&(*(fV.end()));}
      StHltVpdHitIterator erase(StHltVpdHitIterator  it)
      {return (StHltVpdHitIterator)Erase((TObject**)it,1);}
      StHltVpdHitIterator erase(StHltVpdHitIterator fst,StHltVpdHitIterator lst)
      {return (StHltVpdHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StHltVpdHit *       &operator[](Int_t i)       {return at(i);}
      StHltVpdHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StHltVpdHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecHltVpdHit,1) 
};
typedef       StHltVpdHitIterator  StPtrVecHltVpdHitIterator;
typedef const_StHltVpdHitIterator  StPtrVecHltVpdHitConstIterator;
typedef       StHltVpdHitIterator  StSPtrVecHltVpdHitIterator;
typedef const_StHltVpdHitIterator  StSPtrVecHltVpdHitConstIterator;

//______________________________________________________________
class StIstHit;
typedef StIstHit**            StIstHitIterator;
typedef StIstHit * const * const_StIstHitIterator;

class StPtrVecIstHit : public StRefArray 
{ 
public: 
StPtrVecIstHit(Int_t sz=0):StRefArray(sz){};
StPtrVecIstHit(const StPtrVecIstHit &from):StRefArray(from){};
virtual        ~StPtrVecIstHit(){};

 StIstHit * const &at(Int_t idx) const {return (StIstHit  * const &)fV[idx];}
 StIstHit *       &at(Int_t idx)       {return (StIstHit  *       &)fV[idx];}

 StIstHit * const &front()       const {return (StIstHit  * const &)fV.front();}
 StIstHit *       &front()             {return (StIstHit  *       &)fV.front();}

 StIstHit * const &back()        const {return (StIstHit  * const &)fV.back();}
 StIstHit *       &back()              {return (StIstHit  *       &)fV.back();}

const_StIstHitIterator begin() const {return (const_StIstHitIterator)&(*(fV.begin()));}
      StIstHitIterator begin()       {return (      StIstHitIterator)&(*(fV.begin()));}
const_StIstHitIterator end()   const {return (const_StIstHitIterator)&(*(fV.end()));}
      StIstHitIterator end()         {return (      StIstHitIterator)&(*(fV.end()));}
      StIstHitIterator erase(StIstHitIterator  it)
      {return (StIstHitIterator)Erase((TObject**)it,0);}
      StIstHitIterator erase(StIstHitIterator fst,StIstHitIterator lst)
      {return (StIstHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StIstHit *       &operator[](Int_t i)       {return at(i);}
      StIstHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StIstHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecIstHit ,1) 
};


class StSPtrVecIstHit : public StStrArray 
{ 
public: 
StSPtrVecIstHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecIstHit(const StSPtrVecIstHit &from):StStrArray(from){};

 StIstHit * const &at(Int_t idx) const {return (StIstHit  * const &)fV[idx];}
 StIstHit *       &at(Int_t idx)       {return (StIstHit  *       &)fV[idx];}

 StIstHit * const &front()       const {return (StIstHit  * const &)fV.front();}
 StIstHit *       &front()             {return (StIstHit  *       &)fV.front();}

 StIstHit * const &back()        const {return (StIstHit  * const &)fV.back();}
 StIstHit *       &back()              {return (StIstHit  *       &)fV.back();}

const_StIstHitIterator begin() const {return (const_StIstHitIterator)&(*(fV.begin()));}
      StIstHitIterator begin()       {return (      StIstHitIterator)&(*(fV.begin()));}
const_StIstHitIterator end()   const {return (const_StIstHitIterator)&(*(fV.end()));}
      StIstHitIterator end()         {return (      StIstHitIterator)&(*(fV.end()));}
      StIstHitIterator erase(StIstHitIterator  it)
      {return (StIstHitIterator)Erase((TObject**)it,1);}
      StIstHitIterator erase(StIstHitIterator fst,StIstHitIterator lst)
      {return (StIstHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StIstHit *       &operator[](Int_t i)       {return at(i);}
      StIstHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StIstHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecIstHit,1) 
};
typedef       StIstHitIterator  StPtrVecIstHitIterator;
typedef const_StIstHitIterator  StPtrVecIstHitConstIterator;
typedef       StIstHitIterator  StSPtrVecIstHitIterator;
typedef const_StIstHitIterator  StSPtrVecIstHitConstIterator;

//______________________________________________________________
class StKinkVertex;
typedef StKinkVertex**            StKinkVertexIterator;
typedef StKinkVertex * const * const_StKinkVertexIterator;

class StPtrVecKinkVertex : public StRefArray 
{ 
public: 
StPtrVecKinkVertex(Int_t sz=0):StRefArray(sz){};
StPtrVecKinkVertex(const StPtrVecKinkVertex &from):StRefArray(from){};
virtual        ~StPtrVecKinkVertex(){};

 StKinkVertex * const &at(Int_t idx) const {return (StKinkVertex  * const &)fV[idx];}
 StKinkVertex *       &at(Int_t idx)       {return (StKinkVertex  *       &)fV[idx];}

 StKinkVertex * const &front()       const {return (StKinkVertex  * const &)fV.front();}
 StKinkVertex *       &front()             {return (StKinkVertex  *       &)fV.front();}

 StKinkVertex * const &back()        const {return (StKinkVertex  * const &)fV.back();}
 StKinkVertex *       &back()              {return (StKinkVertex  *       &)fV.back();}

const_StKinkVertexIterator begin() const {return (const_StKinkVertexIterator)&(*(fV.begin()));}
      StKinkVertexIterator begin()       {return (      StKinkVertexIterator)&(*(fV.begin()));}
const_StKinkVertexIterator end()   const {return (const_StKinkVertexIterator)&(*(fV.end()));}
      StKinkVertexIterator end()         {return (      StKinkVertexIterator)&(*(fV.end()));}
      StKinkVertexIterator erase(StKinkVertexIterator  it)
      {return (StKinkVertexIterator)Erase((TObject**)it,0);}
      StKinkVertexIterator erase(StKinkVertexIterator fst,StKinkVertexIterator lst)
      {return (StKinkVertexIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StKinkVertex *       &operator[](Int_t i)       {return at(i);}
      StKinkVertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StKinkVertex * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecKinkVertex ,1) 
};


class StSPtrVecKinkVertex : public StStrArray 
{ 
public: 
StSPtrVecKinkVertex(Int_t sz=0):StStrArray(sz){};
StSPtrVecKinkVertex(const StSPtrVecKinkVertex &from):StStrArray(from){};

 StKinkVertex * const &at(Int_t idx) const {return (StKinkVertex  * const &)fV[idx];}
 StKinkVertex *       &at(Int_t idx)       {return (StKinkVertex  *       &)fV[idx];}

 StKinkVertex * const &front()       const {return (StKinkVertex  * const &)fV.front();}
 StKinkVertex *       &front()             {return (StKinkVertex  *       &)fV.front();}

 StKinkVertex * const &back()        const {return (StKinkVertex  * const &)fV.back();}
 StKinkVertex *       &back()              {return (StKinkVertex  *       &)fV.back();}

const_StKinkVertexIterator begin() const {return (const_StKinkVertexIterator)&(*(fV.begin()));}
      StKinkVertexIterator begin()       {return (      StKinkVertexIterator)&(*(fV.begin()));}
const_StKinkVertexIterator end()   const {return (const_StKinkVertexIterator)&(*(fV.end()));}
      StKinkVertexIterator end()         {return (      StKinkVertexIterator)&(*(fV.end()));}
      StKinkVertexIterator erase(StKinkVertexIterator  it)
      {return (StKinkVertexIterator)Erase((TObject**)it,1);}
      StKinkVertexIterator erase(StKinkVertexIterator fst,StKinkVertexIterator lst)
      {return (StKinkVertexIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StKinkVertex *       &operator[](Int_t i)       {return at(i);}
      StKinkVertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StKinkVertex *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecKinkVertex,1) 
};
typedef       StKinkVertexIterator  StPtrVecKinkVertexIterator;
typedef const_StKinkVertexIterator  StPtrVecKinkVertexConstIterator;
typedef       StKinkVertexIterator  StSPtrVecKinkVertexIterator;
typedef const_StKinkVertexIterator  StSPtrVecKinkVertexConstIterator;

//______________________________________________________________
class StL3AlgorithmInfo;
typedef StL3AlgorithmInfo**            StL3AlgorithmInfoIterator;
typedef StL3AlgorithmInfo * const * const_StL3AlgorithmInfoIterator;

class StPtrVecL3AlgorithmInfo : public StRefArray 
{ 
public: 
StPtrVecL3AlgorithmInfo(Int_t sz=0):StRefArray(sz){};
StPtrVecL3AlgorithmInfo(const StPtrVecL3AlgorithmInfo &from):StRefArray(from){};
virtual        ~StPtrVecL3AlgorithmInfo(){};

 StL3AlgorithmInfo * const &at(Int_t idx) const {return (StL3AlgorithmInfo  * const &)fV[idx];}
 StL3AlgorithmInfo *       &at(Int_t idx)       {return (StL3AlgorithmInfo  *       &)fV[idx];}

 StL3AlgorithmInfo * const &front()       const {return (StL3AlgorithmInfo  * const &)fV.front();}
 StL3AlgorithmInfo *       &front()             {return (StL3AlgorithmInfo  *       &)fV.front();}

 StL3AlgorithmInfo * const &back()        const {return (StL3AlgorithmInfo  * const &)fV.back();}
 StL3AlgorithmInfo *       &back()              {return (StL3AlgorithmInfo  *       &)fV.back();}

const_StL3AlgorithmInfoIterator begin() const {return (const_StL3AlgorithmInfoIterator)&(*(fV.begin()));}
      StL3AlgorithmInfoIterator begin()       {return (      StL3AlgorithmInfoIterator)&(*(fV.begin()));}
const_StL3AlgorithmInfoIterator end()   const {return (const_StL3AlgorithmInfoIterator)&(*(fV.end()));}
      StL3AlgorithmInfoIterator end()         {return (      StL3AlgorithmInfoIterator)&(*(fV.end()));}
      StL3AlgorithmInfoIterator erase(StL3AlgorithmInfoIterator  it)
      {return (StL3AlgorithmInfoIterator)Erase((TObject**)it,0);}
      StL3AlgorithmInfoIterator erase(StL3AlgorithmInfoIterator fst,StL3AlgorithmInfoIterator lst)
      {return (StL3AlgorithmInfoIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StL3AlgorithmInfo *       &operator[](Int_t i)       {return at(i);}
      StL3AlgorithmInfo * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StL3AlgorithmInfo * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecL3AlgorithmInfo ,1) 
};


class StSPtrVecL3AlgorithmInfo : public StStrArray 
{ 
public: 
StSPtrVecL3AlgorithmInfo(Int_t sz=0):StStrArray(sz){};
StSPtrVecL3AlgorithmInfo(const StSPtrVecL3AlgorithmInfo &from):StStrArray(from){};

 StL3AlgorithmInfo * const &at(Int_t idx) const {return (StL3AlgorithmInfo  * const &)fV[idx];}
 StL3AlgorithmInfo *       &at(Int_t idx)       {return (StL3AlgorithmInfo  *       &)fV[idx];}

 StL3AlgorithmInfo * const &front()       const {return (StL3AlgorithmInfo  * const &)fV.front();}
 StL3AlgorithmInfo *       &front()             {return (StL3AlgorithmInfo  *       &)fV.front();}

 StL3AlgorithmInfo * const &back()        const {return (StL3AlgorithmInfo  * const &)fV.back();}
 StL3AlgorithmInfo *       &back()              {return (StL3AlgorithmInfo  *       &)fV.back();}

const_StL3AlgorithmInfoIterator begin() const {return (const_StL3AlgorithmInfoIterator)&(*(fV.begin()));}
      StL3AlgorithmInfoIterator begin()       {return (      StL3AlgorithmInfoIterator)&(*(fV.begin()));}
const_StL3AlgorithmInfoIterator end()   const {return (const_StL3AlgorithmInfoIterator)&(*(fV.end()));}
      StL3AlgorithmInfoIterator end()         {return (      StL3AlgorithmInfoIterator)&(*(fV.end()));}
      StL3AlgorithmInfoIterator erase(StL3AlgorithmInfoIterator  it)
      {return (StL3AlgorithmInfoIterator)Erase((TObject**)it,1);}
      StL3AlgorithmInfoIterator erase(StL3AlgorithmInfoIterator fst,StL3AlgorithmInfoIterator lst)
      {return (StL3AlgorithmInfoIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StL3AlgorithmInfo *       &operator[](Int_t i)       {return at(i);}
      StL3AlgorithmInfo * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StL3AlgorithmInfo *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecL3AlgorithmInfo,1) 
};
typedef       StL3AlgorithmInfoIterator  StPtrVecL3AlgorithmInfoIterator;
typedef const_StL3AlgorithmInfoIterator  StPtrVecL3AlgorithmInfoConstIterator;
typedef       StL3AlgorithmInfoIterator  StSPtrVecL3AlgorithmInfoIterator;
typedef const_StL3AlgorithmInfoIterator  StSPtrVecL3AlgorithmInfoConstIterator;

//______________________________________________________________
class StMtdHit;
typedef StMtdHit**            StMtdHitIterator;
typedef StMtdHit * const * const_StMtdHitIterator;

class StPtrVecMtdHit : public StRefArray 
{ 
public: 
StPtrVecMtdHit(Int_t sz=0):StRefArray(sz){};
StPtrVecMtdHit(const StPtrVecMtdHit &from):StRefArray(from){};
virtual        ~StPtrVecMtdHit(){};

 StMtdHit * const &at(Int_t idx) const {return (StMtdHit  * const &)fV[idx];}
 StMtdHit *       &at(Int_t idx)       {return (StMtdHit  *       &)fV[idx];}

 StMtdHit * const &front()       const {return (StMtdHit  * const &)fV.front();}
 StMtdHit *       &front()             {return (StMtdHit  *       &)fV.front();}

 StMtdHit * const &back()        const {return (StMtdHit  * const &)fV.back();}
 StMtdHit *       &back()              {return (StMtdHit  *       &)fV.back();}

const_StMtdHitIterator begin() const {return (const_StMtdHitIterator)&(*(fV.begin()));}
      StMtdHitIterator begin()       {return (      StMtdHitIterator)&(*(fV.begin()));}
const_StMtdHitIterator end()   const {return (const_StMtdHitIterator)&(*(fV.end()));}
      StMtdHitIterator end()         {return (      StMtdHitIterator)&(*(fV.end()));}
      StMtdHitIterator erase(StMtdHitIterator  it)
      {return (StMtdHitIterator)Erase((TObject**)it,0);}
      StMtdHitIterator erase(StMtdHitIterator fst,StMtdHitIterator lst)
      {return (StMtdHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StMtdHit *       &operator[](Int_t i)       {return at(i);}
      StMtdHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StMtdHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecMtdHit ,1) 
};


class StSPtrVecMtdHit : public StStrArray 
{ 
public: 
StSPtrVecMtdHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecMtdHit(const StSPtrVecMtdHit &from):StStrArray(from){};

 StMtdHit * const &at(Int_t idx) const {return (StMtdHit  * const &)fV[idx];}
 StMtdHit *       &at(Int_t idx)       {return (StMtdHit  *       &)fV[idx];}

 StMtdHit * const &front()       const {return (StMtdHit  * const &)fV.front();}
 StMtdHit *       &front()             {return (StMtdHit  *       &)fV.front();}

 StMtdHit * const &back()        const {return (StMtdHit  * const &)fV.back();}
 StMtdHit *       &back()              {return (StMtdHit  *       &)fV.back();}

const_StMtdHitIterator begin() const {return (const_StMtdHitIterator)&(*(fV.begin()));}
      StMtdHitIterator begin()       {return (      StMtdHitIterator)&(*(fV.begin()));}
const_StMtdHitIterator end()   const {return (const_StMtdHitIterator)&(*(fV.end()));}
      StMtdHitIterator end()         {return (      StMtdHitIterator)&(*(fV.end()));}
      StMtdHitIterator erase(StMtdHitIterator  it)
      {return (StMtdHitIterator)Erase((TObject**)it,1);}
      StMtdHitIterator erase(StMtdHitIterator fst,StMtdHitIterator lst)
      {return (StMtdHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StMtdHit *       &operator[](Int_t i)       {return at(i);}
      StMtdHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StMtdHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecMtdHit,1) 
};
typedef       StMtdHitIterator  StPtrVecMtdHitIterator;
typedef const_StMtdHitIterator  StPtrVecMtdHitConstIterator;
typedef       StMtdHitIterator  StSPtrVecMtdHitIterator;
typedef const_StMtdHitIterator  StSPtrVecMtdHitConstIterator;

//______________________________________________________________
class StMtdRawHit;
typedef StMtdRawHit**            StMtdRawHitIterator;
typedef StMtdRawHit * const * const_StMtdRawHitIterator;

class StPtrVecMtdRawHit : public StRefArray 
{ 
public: 
StPtrVecMtdRawHit(Int_t sz=0):StRefArray(sz){};
StPtrVecMtdRawHit(const StPtrVecMtdRawHit &from):StRefArray(from){};
virtual        ~StPtrVecMtdRawHit(){};

 StMtdRawHit * const &at(Int_t idx) const {return (StMtdRawHit  * const &)fV[idx];}
 StMtdRawHit *       &at(Int_t idx)       {return (StMtdRawHit  *       &)fV[idx];}

 StMtdRawHit * const &front()       const {return (StMtdRawHit  * const &)fV.front();}
 StMtdRawHit *       &front()             {return (StMtdRawHit  *       &)fV.front();}

 StMtdRawHit * const &back()        const {return (StMtdRawHit  * const &)fV.back();}
 StMtdRawHit *       &back()              {return (StMtdRawHit  *       &)fV.back();}

const_StMtdRawHitIterator begin() const {return (const_StMtdRawHitIterator)&(*(fV.begin()));}
      StMtdRawHitIterator begin()       {return (      StMtdRawHitIterator)&(*(fV.begin()));}
const_StMtdRawHitIterator end()   const {return (const_StMtdRawHitIterator)&(*(fV.end()));}
      StMtdRawHitIterator end()         {return (      StMtdRawHitIterator)&(*(fV.end()));}
      StMtdRawHitIterator erase(StMtdRawHitIterator  it)
      {return (StMtdRawHitIterator)Erase((TObject**)it,0);}
      StMtdRawHitIterator erase(StMtdRawHitIterator fst,StMtdRawHitIterator lst)
      {return (StMtdRawHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StMtdRawHit *       &operator[](Int_t i)       {return at(i);}
      StMtdRawHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StMtdRawHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecMtdRawHit ,1) 
};


class StSPtrVecMtdRawHit : public StStrArray 
{ 
public: 
StSPtrVecMtdRawHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecMtdRawHit(const StSPtrVecMtdRawHit &from):StStrArray(from){};

 StMtdRawHit * const &at(Int_t idx) const {return (StMtdRawHit  * const &)fV[idx];}
 StMtdRawHit *       &at(Int_t idx)       {return (StMtdRawHit  *       &)fV[idx];}

 StMtdRawHit * const &front()       const {return (StMtdRawHit  * const &)fV.front();}
 StMtdRawHit *       &front()             {return (StMtdRawHit  *       &)fV.front();}

 StMtdRawHit * const &back()        const {return (StMtdRawHit  * const &)fV.back();}
 StMtdRawHit *       &back()              {return (StMtdRawHit  *       &)fV.back();}

const_StMtdRawHitIterator begin() const {return (const_StMtdRawHitIterator)&(*(fV.begin()));}
      StMtdRawHitIterator begin()       {return (      StMtdRawHitIterator)&(*(fV.begin()));}
const_StMtdRawHitIterator end()   const {return (const_StMtdRawHitIterator)&(*(fV.end()));}
      StMtdRawHitIterator end()         {return (      StMtdRawHitIterator)&(*(fV.end()));}
      StMtdRawHitIterator erase(StMtdRawHitIterator  it)
      {return (StMtdRawHitIterator)Erase((TObject**)it,1);}
      StMtdRawHitIterator erase(StMtdRawHitIterator fst,StMtdRawHitIterator lst)
      {return (StMtdRawHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StMtdRawHit *       &operator[](Int_t i)       {return at(i);}
      StMtdRawHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StMtdRawHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecMtdRawHit,1) 
};
typedef       StMtdRawHitIterator  StPtrVecMtdRawHitIterator;
typedef const_StMtdRawHitIterator  StPtrVecMtdRawHitConstIterator;
typedef       StMtdRawHitIterator  StSPtrVecMtdRawHitIterator;
typedef const_StMtdRawHitIterator  StSPtrVecMtdRawHitConstIterator;

//______________________________________________________________
class StObject;
typedef StObject**            StObjectIterator;
typedef StObject * const * const_StObjectIterator;

class StPtrVecObject : public StRefArray 
{ 
public: 
StPtrVecObject(Int_t sz=0):StRefArray(sz){};
StPtrVecObject(const StPtrVecObject &from):StRefArray(from){};
virtual        ~StPtrVecObject(){};

 StObject * const &at(Int_t idx) const {return (StObject  * const &)fV[idx];}
 StObject *       &at(Int_t idx)       {return (StObject  *       &)fV[idx];}

 StObject * const &front()       const {return (StObject  * const &)fV.front();}
 StObject *       &front()             {return (StObject  *       &)fV.front();}

 StObject * const &back()        const {return (StObject  * const &)fV.back();}
 StObject *       &back()              {return (StObject  *       &)fV.back();}

const_StObjectIterator begin() const {return (const_StObjectIterator)&(*(fV.begin()));}
      StObjectIterator begin()       {return (      StObjectIterator)&(*(fV.begin()));}
const_StObjectIterator end()   const {return (const_StObjectIterator)&(*(fV.end()));}
      StObjectIterator end()         {return (      StObjectIterator)&(*(fV.end()));}
      StObjectIterator erase(StObjectIterator  it)
      {return (StObjectIterator)Erase((TObject**)it,0);}
      StObjectIterator erase(StObjectIterator fst,StObjectIterator lst)
      {return (StObjectIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StObject *       &operator[](Int_t i)       {return at(i);}
      StObject * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StObject * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecObject ,1) 
};


class StSPtrVecObject : public StStrArray 
{ 
public: 
StSPtrVecObject(Int_t sz=0):StStrArray(sz){};
StSPtrVecObject(const StSPtrVecObject &from):StStrArray(from){};

 StObject * const &at(Int_t idx) const {return (StObject  * const &)fV[idx];}
 StObject *       &at(Int_t idx)       {return (StObject  *       &)fV[idx];}

 StObject * const &front()       const {return (StObject  * const &)fV.front();}
 StObject *       &front()             {return (StObject  *       &)fV.front();}

 StObject * const &back()        const {return (StObject  * const &)fV.back();}
 StObject *       &back()              {return (StObject  *       &)fV.back();}

const_StObjectIterator begin() const {return (const_StObjectIterator)&(*(fV.begin()));}
      StObjectIterator begin()       {return (      StObjectIterator)&(*(fV.begin()));}
const_StObjectIterator end()   const {return (const_StObjectIterator)&(*(fV.end()));}
      StObjectIterator end()         {return (      StObjectIterator)&(*(fV.end()));}
      StObjectIterator erase(StObjectIterator  it)
      {return (StObjectIterator)Erase((TObject**)it,1);}
      StObjectIterator erase(StObjectIterator fst,StObjectIterator lst)
      {return (StObjectIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StObject *       &operator[](Int_t i)       {return at(i);}
      StObject * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StObject *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecObject,1) 
};
typedef       StObjectIterator  StPtrVecObjectIterator;
typedef const_StObjectIterator  StPtrVecObjectConstIterator;
typedef       StObjectIterator  StSPtrVecObjectIterator;
typedef const_StObjectIterator  StSPtrVecObjectConstIterator;

//______________________________________________________________
class StPhmdCluster;
typedef StPhmdCluster**            StPhmdClusterIterator;
typedef StPhmdCluster * const * const_StPhmdClusterIterator;

class StPtrVecPhmdCluster : public StRefArray 
{ 
public: 
StPtrVecPhmdCluster(Int_t sz=0):StRefArray(sz){};
StPtrVecPhmdCluster(const StPtrVecPhmdCluster &from):StRefArray(from){};
virtual        ~StPtrVecPhmdCluster(){};

 StPhmdCluster * const &at(Int_t idx) const {return (StPhmdCluster  * const &)fV[idx];}
 StPhmdCluster *       &at(Int_t idx)       {return (StPhmdCluster  *       &)fV[idx];}

 StPhmdCluster * const &front()       const {return (StPhmdCluster  * const &)fV.front();}
 StPhmdCluster *       &front()             {return (StPhmdCluster  *       &)fV.front();}

 StPhmdCluster * const &back()        const {return (StPhmdCluster  * const &)fV.back();}
 StPhmdCluster *       &back()              {return (StPhmdCluster  *       &)fV.back();}

const_StPhmdClusterIterator begin() const {return (const_StPhmdClusterIterator)&(*(fV.begin()));}
      StPhmdClusterIterator begin()       {return (      StPhmdClusterIterator)&(*(fV.begin()));}
const_StPhmdClusterIterator end()   const {return (const_StPhmdClusterIterator)&(*(fV.end()));}
      StPhmdClusterIterator end()         {return (      StPhmdClusterIterator)&(*(fV.end()));}
      StPhmdClusterIterator erase(StPhmdClusterIterator  it)
      {return (StPhmdClusterIterator)Erase((TObject**)it,0);}
      StPhmdClusterIterator erase(StPhmdClusterIterator fst,StPhmdClusterIterator lst)
      {return (StPhmdClusterIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StPhmdCluster *       &operator[](Int_t i)       {return at(i);}
      StPhmdCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPhmdCluster * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecPhmdCluster ,1) 
};


class StSPtrVecPhmdCluster : public StStrArray 
{ 
public: 
StSPtrVecPhmdCluster(Int_t sz=0):StStrArray(sz){};
StSPtrVecPhmdCluster(const StSPtrVecPhmdCluster &from):StStrArray(from){};

 StPhmdCluster * const &at(Int_t idx) const {return (StPhmdCluster  * const &)fV[idx];}
 StPhmdCluster *       &at(Int_t idx)       {return (StPhmdCluster  *       &)fV[idx];}

 StPhmdCluster * const &front()       const {return (StPhmdCluster  * const &)fV.front();}
 StPhmdCluster *       &front()             {return (StPhmdCluster  *       &)fV.front();}

 StPhmdCluster * const &back()        const {return (StPhmdCluster  * const &)fV.back();}
 StPhmdCluster *       &back()              {return (StPhmdCluster  *       &)fV.back();}

const_StPhmdClusterIterator begin() const {return (const_StPhmdClusterIterator)&(*(fV.begin()));}
      StPhmdClusterIterator begin()       {return (      StPhmdClusterIterator)&(*(fV.begin()));}
const_StPhmdClusterIterator end()   const {return (const_StPhmdClusterIterator)&(*(fV.end()));}
      StPhmdClusterIterator end()         {return (      StPhmdClusterIterator)&(*(fV.end()));}
      StPhmdClusterIterator erase(StPhmdClusterIterator  it)
      {return (StPhmdClusterIterator)Erase((TObject**)it,1);}
      StPhmdClusterIterator erase(StPhmdClusterIterator fst,StPhmdClusterIterator lst)
      {return (StPhmdClusterIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StPhmdCluster *       &operator[](Int_t i)       {return at(i);}
      StPhmdCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPhmdCluster *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecPhmdCluster,1) 
};
typedef       StPhmdClusterIterator  StPtrVecPhmdClusterIterator;
typedef const_StPhmdClusterIterator  StPtrVecPhmdClusterConstIterator;
typedef       StPhmdClusterIterator  StSPtrVecPhmdClusterIterator;
typedef const_StPhmdClusterIterator  StSPtrVecPhmdClusterConstIterator;

//______________________________________________________________
class StPhmdHit;
typedef StPhmdHit**            StPhmdHitIterator;
typedef StPhmdHit * const * const_StPhmdHitIterator;

class StPtrVecPhmdHit : public StRefArray 
{ 
public: 
StPtrVecPhmdHit(Int_t sz=0):StRefArray(sz){};
StPtrVecPhmdHit(const StPtrVecPhmdHit &from):StRefArray(from){};
virtual        ~StPtrVecPhmdHit(){};

 StPhmdHit * const &at(Int_t idx) const {return (StPhmdHit  * const &)fV[idx];}
 StPhmdHit *       &at(Int_t idx)       {return (StPhmdHit  *       &)fV[idx];}

 StPhmdHit * const &front()       const {return (StPhmdHit  * const &)fV.front();}
 StPhmdHit *       &front()             {return (StPhmdHit  *       &)fV.front();}

 StPhmdHit * const &back()        const {return (StPhmdHit  * const &)fV.back();}
 StPhmdHit *       &back()              {return (StPhmdHit  *       &)fV.back();}

const_StPhmdHitIterator begin() const {return (const_StPhmdHitIterator)&(*(fV.begin()));}
      StPhmdHitIterator begin()       {return (      StPhmdHitIterator)&(*(fV.begin()));}
const_StPhmdHitIterator end()   const {return (const_StPhmdHitIterator)&(*(fV.end()));}
      StPhmdHitIterator end()         {return (      StPhmdHitIterator)&(*(fV.end()));}
      StPhmdHitIterator erase(StPhmdHitIterator  it)
      {return (StPhmdHitIterator)Erase((TObject**)it,0);}
      StPhmdHitIterator erase(StPhmdHitIterator fst,StPhmdHitIterator lst)
      {return (StPhmdHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StPhmdHit *       &operator[](Int_t i)       {return at(i);}
      StPhmdHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPhmdHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecPhmdHit ,1) 
};


class StSPtrVecPhmdHit : public StStrArray 
{ 
public: 
StSPtrVecPhmdHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecPhmdHit(const StSPtrVecPhmdHit &from):StStrArray(from){};

 StPhmdHit * const &at(Int_t idx) const {return (StPhmdHit  * const &)fV[idx];}
 StPhmdHit *       &at(Int_t idx)       {return (StPhmdHit  *       &)fV[idx];}

 StPhmdHit * const &front()       const {return (StPhmdHit  * const &)fV.front();}
 StPhmdHit *       &front()             {return (StPhmdHit  *       &)fV.front();}

 StPhmdHit * const &back()        const {return (StPhmdHit  * const &)fV.back();}
 StPhmdHit *       &back()              {return (StPhmdHit  *       &)fV.back();}

const_StPhmdHitIterator begin() const {return (const_StPhmdHitIterator)&(*(fV.begin()));}
      StPhmdHitIterator begin()       {return (      StPhmdHitIterator)&(*(fV.begin()));}
const_StPhmdHitIterator end()   const {return (const_StPhmdHitIterator)&(*(fV.end()));}
      StPhmdHitIterator end()         {return (      StPhmdHitIterator)&(*(fV.end()));}
      StPhmdHitIterator erase(StPhmdHitIterator  it)
      {return (StPhmdHitIterator)Erase((TObject**)it,1);}
      StPhmdHitIterator erase(StPhmdHitIterator fst,StPhmdHitIterator lst)
      {return (StPhmdHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StPhmdHit *       &operator[](Int_t i)       {return at(i);}
      StPhmdHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPhmdHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecPhmdHit,1) 
};
typedef       StPhmdHitIterator  StPtrVecPhmdHitIterator;
typedef const_StPhmdHitIterator  StPtrVecPhmdHitConstIterator;
typedef       StPhmdHitIterator  StSPtrVecPhmdHitIterator;
typedef const_StPhmdHitIterator  StSPtrVecPhmdHitConstIterator;

//______________________________________________________________
class StPrimaryTrack;
typedef StPrimaryTrack**            StPrimaryTrackIterator;
typedef StPrimaryTrack * const * const_StPrimaryTrackIterator;

class StPtrVecPrimaryTrack : public StRefArray 
{ 
public: 
StPtrVecPrimaryTrack(Int_t sz=0):StRefArray(sz){};
StPtrVecPrimaryTrack(const StPtrVecPrimaryTrack &from):StRefArray(from){};
virtual        ~StPtrVecPrimaryTrack(){};

 StPrimaryTrack * const &at(Int_t idx) const {return (StPrimaryTrack  * const &)fV[idx];}
 StPrimaryTrack *       &at(Int_t idx)       {return (StPrimaryTrack  *       &)fV[idx];}

 StPrimaryTrack * const &front()       const {return (StPrimaryTrack  * const &)fV.front();}
 StPrimaryTrack *       &front()             {return (StPrimaryTrack  *       &)fV.front();}

 StPrimaryTrack * const &back()        const {return (StPrimaryTrack  * const &)fV.back();}
 StPrimaryTrack *       &back()              {return (StPrimaryTrack  *       &)fV.back();}

const_StPrimaryTrackIterator begin() const {return (const_StPrimaryTrackIterator)&(*(fV.begin()));}
      StPrimaryTrackIterator begin()       {return (      StPrimaryTrackIterator)&(*(fV.begin()));}
const_StPrimaryTrackIterator end()   const {return (const_StPrimaryTrackIterator)&(*(fV.end()));}
      StPrimaryTrackIterator end()         {return (      StPrimaryTrackIterator)&(*(fV.end()));}
      StPrimaryTrackIterator erase(StPrimaryTrackIterator  it)
      {return (StPrimaryTrackIterator)Erase((TObject**)it,0);}
      StPrimaryTrackIterator erase(StPrimaryTrackIterator fst,StPrimaryTrackIterator lst)
      {return (StPrimaryTrackIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StPrimaryTrack *       &operator[](Int_t i)       {return at(i);}
      StPrimaryTrack * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPrimaryTrack * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecPrimaryTrack ,1) 
};


class StSPtrVecPrimaryTrack : public StStrArray 
{ 
public: 
StSPtrVecPrimaryTrack(Int_t sz=0):StStrArray(sz){};
StSPtrVecPrimaryTrack(const StSPtrVecPrimaryTrack &from):StStrArray(from){};

 StPrimaryTrack * const &at(Int_t idx) const {return (StPrimaryTrack  * const &)fV[idx];}
 StPrimaryTrack *       &at(Int_t idx)       {return (StPrimaryTrack  *       &)fV[idx];}

 StPrimaryTrack * const &front()       const {return (StPrimaryTrack  * const &)fV.front();}
 StPrimaryTrack *       &front()             {return (StPrimaryTrack  *       &)fV.front();}

 StPrimaryTrack * const &back()        const {return (StPrimaryTrack  * const &)fV.back();}
 StPrimaryTrack *       &back()              {return (StPrimaryTrack  *       &)fV.back();}

const_StPrimaryTrackIterator begin() const {return (const_StPrimaryTrackIterator)&(*(fV.begin()));}
      StPrimaryTrackIterator begin()       {return (      StPrimaryTrackIterator)&(*(fV.begin()));}
const_StPrimaryTrackIterator end()   const {return (const_StPrimaryTrackIterator)&(*(fV.end()));}
      StPrimaryTrackIterator end()         {return (      StPrimaryTrackIterator)&(*(fV.end()));}
      StPrimaryTrackIterator erase(StPrimaryTrackIterator  it)
      {return (StPrimaryTrackIterator)Erase((TObject**)it,1);}
      StPrimaryTrackIterator erase(StPrimaryTrackIterator fst,StPrimaryTrackIterator lst)
      {return (StPrimaryTrackIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StPrimaryTrack *       &operator[](Int_t i)       {return at(i);}
      StPrimaryTrack * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPrimaryTrack *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecPrimaryTrack,1) 
};
typedef       StPrimaryTrackIterator  StPtrVecPrimaryTrackIterator;
typedef const_StPrimaryTrackIterator  StPtrVecPrimaryTrackConstIterator;
typedef       StPrimaryTrackIterator  StSPtrVecPrimaryTrackIterator;
typedef const_StPrimaryTrackIterator  StSPtrVecPrimaryTrackConstIterator;

//______________________________________________________________
class StPrimaryVertex;
typedef StPrimaryVertex**            StPrimaryVertexIterator;
typedef StPrimaryVertex * const * const_StPrimaryVertexIterator;

class StPtrVecPrimaryVertex : public StRefArray 
{ 
public: 
StPtrVecPrimaryVertex(Int_t sz=0):StRefArray(sz){};
StPtrVecPrimaryVertex(const StPtrVecPrimaryVertex &from):StRefArray(from){};
virtual        ~StPtrVecPrimaryVertex(){};

 StPrimaryVertex * const &at(Int_t idx) const {return (StPrimaryVertex  * const &)fV[idx];}
 StPrimaryVertex *       &at(Int_t idx)       {return (StPrimaryVertex  *       &)fV[idx];}

 StPrimaryVertex * const &front()       const {return (StPrimaryVertex  * const &)fV.front();}
 StPrimaryVertex *       &front()             {return (StPrimaryVertex  *       &)fV.front();}

 StPrimaryVertex * const &back()        const {return (StPrimaryVertex  * const &)fV.back();}
 StPrimaryVertex *       &back()              {return (StPrimaryVertex  *       &)fV.back();}

const_StPrimaryVertexIterator begin() const {return (const_StPrimaryVertexIterator)&(*(fV.begin()));}
      StPrimaryVertexIterator begin()       {return (      StPrimaryVertexIterator)&(*(fV.begin()));}
const_StPrimaryVertexIterator end()   const {return (const_StPrimaryVertexIterator)&(*(fV.end()));}
      StPrimaryVertexIterator end()         {return (      StPrimaryVertexIterator)&(*(fV.end()));}
      StPrimaryVertexIterator erase(StPrimaryVertexIterator  it)
      {return (StPrimaryVertexIterator)Erase((TObject**)it,0);}
      StPrimaryVertexIterator erase(StPrimaryVertexIterator fst,StPrimaryVertexIterator lst)
      {return (StPrimaryVertexIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StPrimaryVertex *       &operator[](Int_t i)       {return at(i);}
      StPrimaryVertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPrimaryVertex * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecPrimaryVertex ,1) 
};


class StSPtrVecPrimaryVertex : public StStrArray 
{ 
public: 
StSPtrVecPrimaryVertex(Int_t sz=0):StStrArray(sz){};
StSPtrVecPrimaryVertex(const StSPtrVecPrimaryVertex &from):StStrArray(from){};

 StPrimaryVertex * const &at(Int_t idx) const {return (StPrimaryVertex  * const &)fV[idx];}
 StPrimaryVertex *       &at(Int_t idx)       {return (StPrimaryVertex  *       &)fV[idx];}

 StPrimaryVertex * const &front()       const {return (StPrimaryVertex  * const &)fV.front();}
 StPrimaryVertex *       &front()             {return (StPrimaryVertex  *       &)fV.front();}

 StPrimaryVertex * const &back()        const {return (StPrimaryVertex  * const &)fV.back();}
 StPrimaryVertex *       &back()              {return (StPrimaryVertex  *       &)fV.back();}

const_StPrimaryVertexIterator begin() const {return (const_StPrimaryVertexIterator)&(*(fV.begin()));}
      StPrimaryVertexIterator begin()       {return (      StPrimaryVertexIterator)&(*(fV.begin()));}
const_StPrimaryVertexIterator end()   const {return (const_StPrimaryVertexIterator)&(*(fV.end()));}
      StPrimaryVertexIterator end()         {return (      StPrimaryVertexIterator)&(*(fV.end()));}
      StPrimaryVertexIterator erase(StPrimaryVertexIterator  it)
      {return (StPrimaryVertexIterator)Erase((TObject**)it,1);}
      StPrimaryVertexIterator erase(StPrimaryVertexIterator fst,StPrimaryVertexIterator lst)
      {return (StPrimaryVertexIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StPrimaryVertex *       &operator[](Int_t i)       {return at(i);}
      StPrimaryVertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPrimaryVertex *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecPrimaryVertex,1) 
};
typedef       StPrimaryVertexIterator  StPtrVecPrimaryVertexIterator;
typedef const_StPrimaryVertexIterator  StPtrVecPrimaryVertexConstIterator;
typedef       StPrimaryVertexIterator  StSPtrVecPrimaryVertexIterator;
typedef const_StPrimaryVertexIterator  StSPtrVecPrimaryVertexConstIterator;

//______________________________________________________________
class StPsd;
typedef StPsd**            StPsdIterator;
typedef StPsd * const * const_StPsdIterator;

class StPtrVecPsd : public StRefArray 
{ 
public: 
StPtrVecPsd(Int_t sz=0):StRefArray(sz){};
StPtrVecPsd(const StPtrVecPsd &from):StRefArray(from){};
virtual        ~StPtrVecPsd(){};

 StPsd * const &at(Int_t idx) const {return (StPsd  * const &)fV[idx];}
 StPsd *       &at(Int_t idx)       {return (StPsd  *       &)fV[idx];}

 StPsd * const &front()       const {return (StPsd  * const &)fV.front();}
 StPsd *       &front()             {return (StPsd  *       &)fV.front();}

 StPsd * const &back()        const {return (StPsd  * const &)fV.back();}
 StPsd *       &back()              {return (StPsd  *       &)fV.back();}

const_StPsdIterator begin() const {return (const_StPsdIterator)&(*(fV.begin()));}
      StPsdIterator begin()       {return (      StPsdIterator)&(*(fV.begin()));}
const_StPsdIterator end()   const {return (const_StPsdIterator)&(*(fV.end()));}
      StPsdIterator end()         {return (      StPsdIterator)&(*(fV.end()));}
      StPsdIterator erase(StPsdIterator  it)
      {return (StPsdIterator)Erase((TObject**)it,0);}
      StPsdIterator erase(StPsdIterator fst,StPsdIterator lst)
      {return (StPsdIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StPsd *       &operator[](Int_t i)       {return at(i);}
      StPsd * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPsd * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecPsd ,1) 
};


class StSPtrVecPsd : public StStrArray 
{ 
public: 
StSPtrVecPsd(Int_t sz=0):StStrArray(sz){};
StSPtrVecPsd(const StSPtrVecPsd &from):StStrArray(from){};

 StPsd * const &at(Int_t idx) const {return (StPsd  * const &)fV[idx];}
 StPsd *       &at(Int_t idx)       {return (StPsd  *       &)fV[idx];}

 StPsd * const &front()       const {return (StPsd  * const &)fV.front();}
 StPsd *       &front()             {return (StPsd  *       &)fV.front();}

 StPsd * const &back()        const {return (StPsd  * const &)fV.back();}
 StPsd *       &back()              {return (StPsd  *       &)fV.back();}

const_StPsdIterator begin() const {return (const_StPsdIterator)&(*(fV.begin()));}
      StPsdIterator begin()       {return (      StPsdIterator)&(*(fV.begin()));}
const_StPsdIterator end()   const {return (const_StPsdIterator)&(*(fV.end()));}
      StPsdIterator end()         {return (      StPsdIterator)&(*(fV.end()));}
      StPsdIterator erase(StPsdIterator  it)
      {return (StPsdIterator)Erase((TObject**)it,1);}
      StPsdIterator erase(StPsdIterator fst,StPsdIterator lst)
      {return (StPsdIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StPsd *       &operator[](Int_t i)       {return at(i);}
      StPsd * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPsd *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecPsd,1) 
};
typedef       StPsdIterator  StPtrVecPsdIterator;
typedef const_StPsdIterator  StPtrVecPsdConstIterator;
typedef       StPsdIterator  StSPtrVecPsdIterator;
typedef const_StPsdIterator  StSPtrVecPsdConstIterator;

//______________________________________________________________
class StPxlHit;
typedef StPxlHit**            StPxlHitIterator;
typedef StPxlHit * const * const_StPxlHitIterator;

class StPtrVecPxlHit : public StRefArray 
{ 
public: 
StPtrVecPxlHit(Int_t sz=0):StRefArray(sz){};
StPtrVecPxlHit(const StPtrVecPxlHit &from):StRefArray(from){};
virtual        ~StPtrVecPxlHit(){};

 StPxlHit * const &at(Int_t idx) const {return (StPxlHit  * const &)fV[idx];}
 StPxlHit *       &at(Int_t idx)       {return (StPxlHit  *       &)fV[idx];}

 StPxlHit * const &front()       const {return (StPxlHit  * const &)fV.front();}
 StPxlHit *       &front()             {return (StPxlHit  *       &)fV.front();}

 StPxlHit * const &back()        const {return (StPxlHit  * const &)fV.back();}
 StPxlHit *       &back()              {return (StPxlHit  *       &)fV.back();}

const_StPxlHitIterator begin() const {return (const_StPxlHitIterator)&(*(fV.begin()));}
      StPxlHitIterator begin()       {return (      StPxlHitIterator)&(*(fV.begin()));}
const_StPxlHitIterator end()   const {return (const_StPxlHitIterator)&(*(fV.end()));}
      StPxlHitIterator end()         {return (      StPxlHitIterator)&(*(fV.end()));}
      StPxlHitIterator erase(StPxlHitIterator  it)
      {return (StPxlHitIterator)Erase((TObject**)it,0);}
      StPxlHitIterator erase(StPxlHitIterator fst,StPxlHitIterator lst)
      {return (StPxlHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StPxlHit *       &operator[](Int_t i)       {return at(i);}
      StPxlHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPxlHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecPxlHit ,1) 
};


class StSPtrVecPxlHit : public StStrArray 
{ 
public: 
StSPtrVecPxlHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecPxlHit(const StSPtrVecPxlHit &from):StStrArray(from){};

 StPxlHit * const &at(Int_t idx) const {return (StPxlHit  * const &)fV[idx];}
 StPxlHit *       &at(Int_t idx)       {return (StPxlHit  *       &)fV[idx];}

 StPxlHit * const &front()       const {return (StPxlHit  * const &)fV.front();}
 StPxlHit *       &front()             {return (StPxlHit  *       &)fV.front();}

 StPxlHit * const &back()        const {return (StPxlHit  * const &)fV.back();}
 StPxlHit *       &back()              {return (StPxlHit  *       &)fV.back();}

const_StPxlHitIterator begin() const {return (const_StPxlHitIterator)&(*(fV.begin()));}
      StPxlHitIterator begin()       {return (      StPxlHitIterator)&(*(fV.begin()));}
const_StPxlHitIterator end()   const {return (const_StPxlHitIterator)&(*(fV.end()));}
      StPxlHitIterator end()         {return (      StPxlHitIterator)&(*(fV.end()));}
      StPxlHitIterator erase(StPxlHitIterator  it)
      {return (StPxlHitIterator)Erase((TObject**)it,1);}
      StPxlHitIterator erase(StPxlHitIterator fst,StPxlHitIterator lst)
      {return (StPxlHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StPxlHit *       &operator[](Int_t i)       {return at(i);}
      StPxlHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StPxlHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecPxlHit,1) 
};
typedef       StPxlHitIterator  StPtrVecPxlHitIterator;
typedef const_StPxlHitIterator  StPtrVecPxlHitConstIterator;
typedef       StPxlHitIterator  StSPtrVecPxlHitIterator;
typedef const_StPxlHitIterator  StSPtrVecPxlHitConstIterator;

//______________________________________________________________
class StRichCluster;
typedef StRichCluster**            StRichClusterIterator;
typedef StRichCluster * const * const_StRichClusterIterator;

class StPtrVecRichCluster : public StRefArray 
{ 
public: 
StPtrVecRichCluster(Int_t sz=0):StRefArray(sz){};
StPtrVecRichCluster(const StPtrVecRichCluster &from):StRefArray(from){};
virtual        ~StPtrVecRichCluster(){};

 StRichCluster * const &at(Int_t idx) const {return (StRichCluster  * const &)fV[idx];}
 StRichCluster *       &at(Int_t idx)       {return (StRichCluster  *       &)fV[idx];}

 StRichCluster * const &front()       const {return (StRichCluster  * const &)fV.front();}
 StRichCluster *       &front()             {return (StRichCluster  *       &)fV.front();}

 StRichCluster * const &back()        const {return (StRichCluster  * const &)fV.back();}
 StRichCluster *       &back()              {return (StRichCluster  *       &)fV.back();}

const_StRichClusterIterator begin() const {return (const_StRichClusterIterator)&(*(fV.begin()));}
      StRichClusterIterator begin()       {return (      StRichClusterIterator)&(*(fV.begin()));}
const_StRichClusterIterator end()   const {return (const_StRichClusterIterator)&(*(fV.end()));}
      StRichClusterIterator end()         {return (      StRichClusterIterator)&(*(fV.end()));}
      StRichClusterIterator erase(StRichClusterIterator  it)
      {return (StRichClusterIterator)Erase((TObject**)it,0);}
      StRichClusterIterator erase(StRichClusterIterator fst,StRichClusterIterator lst)
      {return (StRichClusterIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRichCluster *       &operator[](Int_t i)       {return at(i);}
      StRichCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichCluster * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRichCluster ,1) 
};


class StSPtrVecRichCluster : public StStrArray 
{ 
public: 
StSPtrVecRichCluster(Int_t sz=0):StStrArray(sz){};
StSPtrVecRichCluster(const StSPtrVecRichCluster &from):StStrArray(from){};

 StRichCluster * const &at(Int_t idx) const {return (StRichCluster  * const &)fV[idx];}
 StRichCluster *       &at(Int_t idx)       {return (StRichCluster  *       &)fV[idx];}

 StRichCluster * const &front()       const {return (StRichCluster  * const &)fV.front();}
 StRichCluster *       &front()             {return (StRichCluster  *       &)fV.front();}

 StRichCluster * const &back()        const {return (StRichCluster  * const &)fV.back();}
 StRichCluster *       &back()              {return (StRichCluster  *       &)fV.back();}

const_StRichClusterIterator begin() const {return (const_StRichClusterIterator)&(*(fV.begin()));}
      StRichClusterIterator begin()       {return (      StRichClusterIterator)&(*(fV.begin()));}
const_StRichClusterIterator end()   const {return (const_StRichClusterIterator)&(*(fV.end()));}
      StRichClusterIterator end()         {return (      StRichClusterIterator)&(*(fV.end()));}
      StRichClusterIterator erase(StRichClusterIterator  it)
      {return (StRichClusterIterator)Erase((TObject**)it,1);}
      StRichClusterIterator erase(StRichClusterIterator fst,StRichClusterIterator lst)
      {return (StRichClusterIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRichCluster *       &operator[](Int_t i)       {return at(i);}
      StRichCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichCluster *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRichCluster,1) 
};
typedef       StRichClusterIterator  StPtrVecRichClusterIterator;
typedef const_StRichClusterIterator  StPtrVecRichClusterConstIterator;
typedef       StRichClusterIterator  StSPtrVecRichClusterIterator;
typedef const_StRichClusterIterator  StSPtrVecRichClusterConstIterator;

//______________________________________________________________
class StRichHit;
typedef StRichHit**            StRichHitIterator;
typedef StRichHit * const * const_StRichHitIterator;

class StPtrVecRichHit : public StRefArray 
{ 
public: 
StPtrVecRichHit(Int_t sz=0):StRefArray(sz){};
StPtrVecRichHit(const StPtrVecRichHit &from):StRefArray(from){};
virtual        ~StPtrVecRichHit(){};

 StRichHit * const &at(Int_t idx) const {return (StRichHit  * const &)fV[idx];}
 StRichHit *       &at(Int_t idx)       {return (StRichHit  *       &)fV[idx];}

 StRichHit * const &front()       const {return (StRichHit  * const &)fV.front();}
 StRichHit *       &front()             {return (StRichHit  *       &)fV.front();}

 StRichHit * const &back()        const {return (StRichHit  * const &)fV.back();}
 StRichHit *       &back()              {return (StRichHit  *       &)fV.back();}

const_StRichHitIterator begin() const {return (const_StRichHitIterator)&(*(fV.begin()));}
      StRichHitIterator begin()       {return (      StRichHitIterator)&(*(fV.begin()));}
const_StRichHitIterator end()   const {return (const_StRichHitIterator)&(*(fV.end()));}
      StRichHitIterator end()         {return (      StRichHitIterator)&(*(fV.end()));}
      StRichHitIterator erase(StRichHitIterator  it)
      {return (StRichHitIterator)Erase((TObject**)it,0);}
      StRichHitIterator erase(StRichHitIterator fst,StRichHitIterator lst)
      {return (StRichHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRichHit *       &operator[](Int_t i)       {return at(i);}
      StRichHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRichHit ,1) 
};


class StSPtrVecRichHit : public StStrArray 
{ 
public: 
StSPtrVecRichHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecRichHit(const StSPtrVecRichHit &from):StStrArray(from){};

 StRichHit * const &at(Int_t idx) const {return (StRichHit  * const &)fV[idx];}
 StRichHit *       &at(Int_t idx)       {return (StRichHit  *       &)fV[idx];}

 StRichHit * const &front()       const {return (StRichHit  * const &)fV.front();}
 StRichHit *       &front()             {return (StRichHit  *       &)fV.front();}

 StRichHit * const &back()        const {return (StRichHit  * const &)fV.back();}
 StRichHit *       &back()              {return (StRichHit  *       &)fV.back();}

const_StRichHitIterator begin() const {return (const_StRichHitIterator)&(*(fV.begin()));}
      StRichHitIterator begin()       {return (      StRichHitIterator)&(*(fV.begin()));}
const_StRichHitIterator end()   const {return (const_StRichHitIterator)&(*(fV.end()));}
      StRichHitIterator end()         {return (      StRichHitIterator)&(*(fV.end()));}
      StRichHitIterator erase(StRichHitIterator  it)
      {return (StRichHitIterator)Erase((TObject**)it,1);}
      StRichHitIterator erase(StRichHitIterator fst,StRichHitIterator lst)
      {return (StRichHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRichHit *       &operator[](Int_t i)       {return at(i);}
      StRichHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRichHit,1) 
};
typedef       StRichHitIterator  StPtrVecRichHitIterator;
typedef const_StRichHitIterator  StPtrVecRichHitConstIterator;
typedef       StRichHitIterator  StSPtrVecRichHitIterator;
typedef const_StRichHitIterator  StSPtrVecRichHitConstIterator;

//______________________________________________________________
class StRichMCInfo;
typedef StRichMCInfo**            StRichMCInfoIterator;
typedef StRichMCInfo * const * const_StRichMCInfoIterator;

class StPtrVecRichMCInfo : public StRefArray 
{ 
public: 
StPtrVecRichMCInfo(Int_t sz=0):StRefArray(sz){};
StPtrVecRichMCInfo(const StPtrVecRichMCInfo &from):StRefArray(from){};
virtual        ~StPtrVecRichMCInfo(){};

 StRichMCInfo * const &at(Int_t idx) const {return (StRichMCInfo  * const &)fV[idx];}
 StRichMCInfo *       &at(Int_t idx)       {return (StRichMCInfo  *       &)fV[idx];}

 StRichMCInfo * const &front()       const {return (StRichMCInfo  * const &)fV.front();}
 StRichMCInfo *       &front()             {return (StRichMCInfo  *       &)fV.front();}

 StRichMCInfo * const &back()        const {return (StRichMCInfo  * const &)fV.back();}
 StRichMCInfo *       &back()              {return (StRichMCInfo  *       &)fV.back();}

const_StRichMCInfoIterator begin() const {return (const_StRichMCInfoIterator)&(*(fV.begin()));}
      StRichMCInfoIterator begin()       {return (      StRichMCInfoIterator)&(*(fV.begin()));}
const_StRichMCInfoIterator end()   const {return (const_StRichMCInfoIterator)&(*(fV.end()));}
      StRichMCInfoIterator end()         {return (      StRichMCInfoIterator)&(*(fV.end()));}
      StRichMCInfoIterator erase(StRichMCInfoIterator  it)
      {return (StRichMCInfoIterator)Erase((TObject**)it,0);}
      StRichMCInfoIterator erase(StRichMCInfoIterator fst,StRichMCInfoIterator lst)
      {return (StRichMCInfoIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRichMCInfo *       &operator[](Int_t i)       {return at(i);}
      StRichMCInfo * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichMCInfo * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRichMCInfo ,1) 
};


class StSPtrVecRichMCInfo : public StStrArray 
{ 
public: 
StSPtrVecRichMCInfo(Int_t sz=0):StStrArray(sz){};
StSPtrVecRichMCInfo(const StSPtrVecRichMCInfo &from):StStrArray(from){};

 StRichMCInfo * const &at(Int_t idx) const {return (StRichMCInfo  * const &)fV[idx];}
 StRichMCInfo *       &at(Int_t idx)       {return (StRichMCInfo  *       &)fV[idx];}

 StRichMCInfo * const &front()       const {return (StRichMCInfo  * const &)fV.front();}
 StRichMCInfo *       &front()             {return (StRichMCInfo  *       &)fV.front();}

 StRichMCInfo * const &back()        const {return (StRichMCInfo  * const &)fV.back();}
 StRichMCInfo *       &back()              {return (StRichMCInfo  *       &)fV.back();}

const_StRichMCInfoIterator begin() const {return (const_StRichMCInfoIterator)&(*(fV.begin()));}
      StRichMCInfoIterator begin()       {return (      StRichMCInfoIterator)&(*(fV.begin()));}
const_StRichMCInfoIterator end()   const {return (const_StRichMCInfoIterator)&(*(fV.end()));}
      StRichMCInfoIterator end()         {return (      StRichMCInfoIterator)&(*(fV.end()));}
      StRichMCInfoIterator erase(StRichMCInfoIterator  it)
      {return (StRichMCInfoIterator)Erase((TObject**)it,1);}
      StRichMCInfoIterator erase(StRichMCInfoIterator fst,StRichMCInfoIterator lst)
      {return (StRichMCInfoIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRichMCInfo *       &operator[](Int_t i)       {return at(i);}
      StRichMCInfo * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichMCInfo *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRichMCInfo,1) 
};
typedef       StRichMCInfoIterator  StPtrVecRichMCInfoIterator;
typedef const_StRichMCInfoIterator  StPtrVecRichMCInfoConstIterator;
typedef       StRichMCInfoIterator  StSPtrVecRichMCInfoIterator;
typedef const_StRichMCInfoIterator  StSPtrVecRichMCInfoConstIterator;

//______________________________________________________________
class StRichPhotonInfo;
typedef StRichPhotonInfo**            StRichPhotonInfoIterator;
typedef StRichPhotonInfo * const * const_StRichPhotonInfoIterator;

class StPtrVecRichPhotonInfo : public StRefArray 
{ 
public: 
StPtrVecRichPhotonInfo(Int_t sz=0):StRefArray(sz){};
StPtrVecRichPhotonInfo(const StPtrVecRichPhotonInfo &from):StRefArray(from){};
virtual        ~StPtrVecRichPhotonInfo(){};

 StRichPhotonInfo * const &at(Int_t idx) const {return (StRichPhotonInfo  * const &)fV[idx];}
 StRichPhotonInfo *       &at(Int_t idx)       {return (StRichPhotonInfo  *       &)fV[idx];}

 StRichPhotonInfo * const &front()       const {return (StRichPhotonInfo  * const &)fV.front();}
 StRichPhotonInfo *       &front()             {return (StRichPhotonInfo  *       &)fV.front();}

 StRichPhotonInfo * const &back()        const {return (StRichPhotonInfo  * const &)fV.back();}
 StRichPhotonInfo *       &back()              {return (StRichPhotonInfo  *       &)fV.back();}

const_StRichPhotonInfoIterator begin() const {return (const_StRichPhotonInfoIterator)&(*(fV.begin()));}
      StRichPhotonInfoIterator begin()       {return (      StRichPhotonInfoIterator)&(*(fV.begin()));}
const_StRichPhotonInfoIterator end()   const {return (const_StRichPhotonInfoIterator)&(*(fV.end()));}
      StRichPhotonInfoIterator end()         {return (      StRichPhotonInfoIterator)&(*(fV.end()));}
      StRichPhotonInfoIterator erase(StRichPhotonInfoIterator  it)
      {return (StRichPhotonInfoIterator)Erase((TObject**)it,0);}
      StRichPhotonInfoIterator erase(StRichPhotonInfoIterator fst,StRichPhotonInfoIterator lst)
      {return (StRichPhotonInfoIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRichPhotonInfo *       &operator[](Int_t i)       {return at(i);}
      StRichPhotonInfo * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichPhotonInfo * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRichPhotonInfo ,1) 
};


class StSPtrVecRichPhotonInfo : public StStrArray 
{ 
public: 
StSPtrVecRichPhotonInfo(Int_t sz=0):StStrArray(sz){};
StSPtrVecRichPhotonInfo(const StSPtrVecRichPhotonInfo &from):StStrArray(from){};

 StRichPhotonInfo * const &at(Int_t idx) const {return (StRichPhotonInfo  * const &)fV[idx];}
 StRichPhotonInfo *       &at(Int_t idx)       {return (StRichPhotonInfo  *       &)fV[idx];}

 StRichPhotonInfo * const &front()       const {return (StRichPhotonInfo  * const &)fV.front();}
 StRichPhotonInfo *       &front()             {return (StRichPhotonInfo  *       &)fV.front();}

 StRichPhotonInfo * const &back()        const {return (StRichPhotonInfo  * const &)fV.back();}
 StRichPhotonInfo *       &back()              {return (StRichPhotonInfo  *       &)fV.back();}

const_StRichPhotonInfoIterator begin() const {return (const_StRichPhotonInfoIterator)&(*(fV.begin()));}
      StRichPhotonInfoIterator begin()       {return (      StRichPhotonInfoIterator)&(*(fV.begin()));}
const_StRichPhotonInfoIterator end()   const {return (const_StRichPhotonInfoIterator)&(*(fV.end()));}
      StRichPhotonInfoIterator end()         {return (      StRichPhotonInfoIterator)&(*(fV.end()));}
      StRichPhotonInfoIterator erase(StRichPhotonInfoIterator  it)
      {return (StRichPhotonInfoIterator)Erase((TObject**)it,1);}
      StRichPhotonInfoIterator erase(StRichPhotonInfoIterator fst,StRichPhotonInfoIterator lst)
      {return (StRichPhotonInfoIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRichPhotonInfo *       &operator[](Int_t i)       {return at(i);}
      StRichPhotonInfo * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichPhotonInfo *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRichPhotonInfo,1) 
};
typedef       StRichPhotonInfoIterator  StPtrVecRichPhotonInfoIterator;
typedef const_StRichPhotonInfoIterator  StPtrVecRichPhotonInfoConstIterator;
typedef       StRichPhotonInfoIterator  StSPtrVecRichPhotonInfoIterator;
typedef const_StRichPhotonInfoIterator  StSPtrVecRichPhotonInfoConstIterator;

//______________________________________________________________
class StRichPid;
typedef StRichPid**            StRichPidIterator;
typedef StRichPid * const * const_StRichPidIterator;

class StPtrVecRichPid : public StRefArray 
{ 
public: 
StPtrVecRichPid(Int_t sz=0):StRefArray(sz){};
StPtrVecRichPid(const StPtrVecRichPid &from):StRefArray(from){};
virtual        ~StPtrVecRichPid(){};

 StRichPid * const &at(Int_t idx) const {return (StRichPid  * const &)fV[idx];}
 StRichPid *       &at(Int_t idx)       {return (StRichPid  *       &)fV[idx];}

 StRichPid * const &front()       const {return (StRichPid  * const &)fV.front();}
 StRichPid *       &front()             {return (StRichPid  *       &)fV.front();}

 StRichPid * const &back()        const {return (StRichPid  * const &)fV.back();}
 StRichPid *       &back()              {return (StRichPid  *       &)fV.back();}

const_StRichPidIterator begin() const {return (const_StRichPidIterator)&(*(fV.begin()));}
      StRichPidIterator begin()       {return (      StRichPidIterator)&(*(fV.begin()));}
const_StRichPidIterator end()   const {return (const_StRichPidIterator)&(*(fV.end()));}
      StRichPidIterator end()         {return (      StRichPidIterator)&(*(fV.end()));}
      StRichPidIterator erase(StRichPidIterator  it)
      {return (StRichPidIterator)Erase((TObject**)it,0);}
      StRichPidIterator erase(StRichPidIterator fst,StRichPidIterator lst)
      {return (StRichPidIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRichPid *       &operator[](Int_t i)       {return at(i);}
      StRichPid * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichPid * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRichPid ,1) 
};


class StSPtrVecRichPid : public StStrArray 
{ 
public: 
StSPtrVecRichPid(Int_t sz=0):StStrArray(sz){};
StSPtrVecRichPid(const StSPtrVecRichPid &from):StStrArray(from){};

 StRichPid * const &at(Int_t idx) const {return (StRichPid  * const &)fV[idx];}
 StRichPid *       &at(Int_t idx)       {return (StRichPid  *       &)fV[idx];}

 StRichPid * const &front()       const {return (StRichPid  * const &)fV.front();}
 StRichPid *       &front()             {return (StRichPid  *       &)fV.front();}

 StRichPid * const &back()        const {return (StRichPid  * const &)fV.back();}
 StRichPid *       &back()              {return (StRichPid  *       &)fV.back();}

const_StRichPidIterator begin() const {return (const_StRichPidIterator)&(*(fV.begin()));}
      StRichPidIterator begin()       {return (      StRichPidIterator)&(*(fV.begin()));}
const_StRichPidIterator end()   const {return (const_StRichPidIterator)&(*(fV.end()));}
      StRichPidIterator end()         {return (      StRichPidIterator)&(*(fV.end()));}
      StRichPidIterator erase(StRichPidIterator  it)
      {return (StRichPidIterator)Erase((TObject**)it,1);}
      StRichPidIterator erase(StRichPidIterator fst,StRichPidIterator lst)
      {return (StRichPidIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRichPid *       &operator[](Int_t i)       {return at(i);}
      StRichPid * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichPid *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRichPid,1) 
};
typedef       StRichPidIterator  StPtrVecRichPidIterator;
typedef const_StRichPidIterator  StPtrVecRichPidConstIterator;
typedef       StRichPidIterator  StSPtrVecRichPidIterator;
typedef const_StRichPidIterator  StSPtrVecRichPidConstIterator;

//______________________________________________________________
class StRichPixel;
typedef StRichPixel**            StRichPixelIterator;
typedef StRichPixel * const * const_StRichPixelIterator;

class StPtrVecRichPixel : public StRefArray 
{ 
public: 
StPtrVecRichPixel(Int_t sz=0):StRefArray(sz){};
StPtrVecRichPixel(const StPtrVecRichPixel &from):StRefArray(from){};
virtual        ~StPtrVecRichPixel(){};

 StRichPixel * const &at(Int_t idx) const {return (StRichPixel  * const &)fV[idx];}
 StRichPixel *       &at(Int_t idx)       {return (StRichPixel  *       &)fV[idx];}

 StRichPixel * const &front()       const {return (StRichPixel  * const &)fV.front();}
 StRichPixel *       &front()             {return (StRichPixel  *       &)fV.front();}

 StRichPixel * const &back()        const {return (StRichPixel  * const &)fV.back();}
 StRichPixel *       &back()              {return (StRichPixel  *       &)fV.back();}

const_StRichPixelIterator begin() const {return (const_StRichPixelIterator)&(*(fV.begin()));}
      StRichPixelIterator begin()       {return (      StRichPixelIterator)&(*(fV.begin()));}
const_StRichPixelIterator end()   const {return (const_StRichPixelIterator)&(*(fV.end()));}
      StRichPixelIterator end()         {return (      StRichPixelIterator)&(*(fV.end()));}
      StRichPixelIterator erase(StRichPixelIterator  it)
      {return (StRichPixelIterator)Erase((TObject**)it,0);}
      StRichPixelIterator erase(StRichPixelIterator fst,StRichPixelIterator lst)
      {return (StRichPixelIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRichPixel *       &operator[](Int_t i)       {return at(i);}
      StRichPixel * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichPixel * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRichPixel ,1) 
};


class StSPtrVecRichPixel : public StStrArray 
{ 
public: 
StSPtrVecRichPixel(Int_t sz=0):StStrArray(sz){};
StSPtrVecRichPixel(const StSPtrVecRichPixel &from):StStrArray(from){};

 StRichPixel * const &at(Int_t idx) const {return (StRichPixel  * const &)fV[idx];}
 StRichPixel *       &at(Int_t idx)       {return (StRichPixel  *       &)fV[idx];}

 StRichPixel * const &front()       const {return (StRichPixel  * const &)fV.front();}
 StRichPixel *       &front()             {return (StRichPixel  *       &)fV.front();}

 StRichPixel * const &back()        const {return (StRichPixel  * const &)fV.back();}
 StRichPixel *       &back()              {return (StRichPixel  *       &)fV.back();}

const_StRichPixelIterator begin() const {return (const_StRichPixelIterator)&(*(fV.begin()));}
      StRichPixelIterator begin()       {return (      StRichPixelIterator)&(*(fV.begin()));}
const_StRichPixelIterator end()   const {return (const_StRichPixelIterator)&(*(fV.end()));}
      StRichPixelIterator end()         {return (      StRichPixelIterator)&(*(fV.end()));}
      StRichPixelIterator erase(StRichPixelIterator  it)
      {return (StRichPixelIterator)Erase((TObject**)it,1);}
      StRichPixelIterator erase(StRichPixelIterator fst,StRichPixelIterator lst)
      {return (StRichPixelIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRichPixel *       &operator[](Int_t i)       {return at(i);}
      StRichPixel * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRichPixel *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRichPixel,1) 
};
typedef       StRichPixelIterator  StPtrVecRichPixelIterator;
typedef const_StRichPixelIterator  StPtrVecRichPixelConstIterator;
typedef       StRichPixelIterator  StSPtrVecRichPixelIterator;
typedef const_StRichPixelIterator  StSPtrVecRichPixelConstIterator;

//______________________________________________________________
class StRnDHit;
typedef StRnDHit**            StRnDHitIterator;
typedef StRnDHit * const * const_StRnDHitIterator;

class StPtrVecRnDHit : public StRefArray 
{ 
public: 
StPtrVecRnDHit(Int_t sz=0):StRefArray(sz){};
StPtrVecRnDHit(const StPtrVecRnDHit &from):StRefArray(from){};
virtual        ~StPtrVecRnDHit(){};

 StRnDHit * const &at(Int_t idx) const {return (StRnDHit  * const &)fV[idx];}
 StRnDHit *       &at(Int_t idx)       {return (StRnDHit  *       &)fV[idx];}

 StRnDHit * const &front()       const {return (StRnDHit  * const &)fV.front();}
 StRnDHit *       &front()             {return (StRnDHit  *       &)fV.front();}

 StRnDHit * const &back()        const {return (StRnDHit  * const &)fV.back();}
 StRnDHit *       &back()              {return (StRnDHit  *       &)fV.back();}

const_StRnDHitIterator begin() const {return (const_StRnDHitIterator)&(*(fV.begin()));}
      StRnDHitIterator begin()       {return (      StRnDHitIterator)&(*(fV.begin()));}
const_StRnDHitIterator end()   const {return (const_StRnDHitIterator)&(*(fV.end()));}
      StRnDHitIterator end()         {return (      StRnDHitIterator)&(*(fV.end()));}
      StRnDHitIterator erase(StRnDHitIterator  it)
      {return (StRnDHitIterator)Erase((TObject**)it,0);}
      StRnDHitIterator erase(StRnDHitIterator fst,StRnDHitIterator lst)
      {return (StRnDHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRnDHit *       &operator[](Int_t i)       {return at(i);}
      StRnDHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRnDHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRnDHit ,1) 
};


class StSPtrVecRnDHit : public StStrArray 
{ 
public: 
StSPtrVecRnDHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecRnDHit(const StSPtrVecRnDHit &from):StStrArray(from){};

 StRnDHit * const &at(Int_t idx) const {return (StRnDHit  * const &)fV[idx];}
 StRnDHit *       &at(Int_t idx)       {return (StRnDHit  *       &)fV[idx];}

 StRnDHit * const &front()       const {return (StRnDHit  * const &)fV.front();}
 StRnDHit *       &front()             {return (StRnDHit  *       &)fV.front();}

 StRnDHit * const &back()        const {return (StRnDHit  * const &)fV.back();}
 StRnDHit *       &back()              {return (StRnDHit  *       &)fV.back();}

const_StRnDHitIterator begin() const {return (const_StRnDHitIterator)&(*(fV.begin()));}
      StRnDHitIterator begin()       {return (      StRnDHitIterator)&(*(fV.begin()));}
const_StRnDHitIterator end()   const {return (const_StRnDHitIterator)&(*(fV.end()));}
      StRnDHitIterator end()         {return (      StRnDHitIterator)&(*(fV.end()));}
      StRnDHitIterator erase(StRnDHitIterator  it)
      {return (StRnDHitIterator)Erase((TObject**)it,1);}
      StRnDHitIterator erase(StRnDHitIterator fst,StRnDHitIterator lst)
      {return (StRnDHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRnDHit *       &operator[](Int_t i)       {return at(i);}
      StRnDHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRnDHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRnDHit,1) 
};
typedef       StRnDHitIterator  StPtrVecRnDHitIterator;
typedef const_StRnDHitIterator  StPtrVecRnDHitConstIterator;
typedef       StRnDHitIterator  StSPtrVecRnDHitIterator;
typedef const_StRnDHitIterator  StSPtrVecRnDHitConstIterator;

//______________________________________________________________
class StRpsCluster;
typedef StRpsCluster**            StRpsClusterIterator;
typedef StRpsCluster * const * const_StRpsClusterIterator;

class StPtrVecRpsCluster : public StRefArray 
{ 
public: 
StPtrVecRpsCluster(Int_t sz=0):StRefArray(sz){};
StPtrVecRpsCluster(const StPtrVecRpsCluster &from):StRefArray(from){};
virtual        ~StPtrVecRpsCluster(){};

 StRpsCluster * const &at(Int_t idx) const {return (StRpsCluster  * const &)fV[idx];}
 StRpsCluster *       &at(Int_t idx)       {return (StRpsCluster  *       &)fV[idx];}

 StRpsCluster * const &front()       const {return (StRpsCluster  * const &)fV.front();}
 StRpsCluster *       &front()             {return (StRpsCluster  *       &)fV.front();}

 StRpsCluster * const &back()        const {return (StRpsCluster  * const &)fV.back();}
 StRpsCluster *       &back()              {return (StRpsCluster  *       &)fV.back();}

const_StRpsClusterIterator begin() const {return (const_StRpsClusterIterator)&(*(fV.begin()));}
      StRpsClusterIterator begin()       {return (      StRpsClusterIterator)&(*(fV.begin()));}
const_StRpsClusterIterator end()   const {return (const_StRpsClusterIterator)&(*(fV.end()));}
      StRpsClusterIterator end()         {return (      StRpsClusterIterator)&(*(fV.end()));}
      StRpsClusterIterator erase(StRpsClusterIterator  it)
      {return (StRpsClusterIterator)Erase((TObject**)it,0);}
      StRpsClusterIterator erase(StRpsClusterIterator fst,StRpsClusterIterator lst)
      {return (StRpsClusterIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRpsCluster *       &operator[](Int_t i)       {return at(i);}
      StRpsCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRpsCluster * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRpsCluster ,1) 
};


class StSPtrVecRpsCluster : public StStrArray 
{ 
public: 
StSPtrVecRpsCluster(Int_t sz=0):StStrArray(sz){};
StSPtrVecRpsCluster(const StSPtrVecRpsCluster &from):StStrArray(from){};

 StRpsCluster * const &at(Int_t idx) const {return (StRpsCluster  * const &)fV[idx];}
 StRpsCluster *       &at(Int_t idx)       {return (StRpsCluster  *       &)fV[idx];}

 StRpsCluster * const &front()       const {return (StRpsCluster  * const &)fV.front();}
 StRpsCluster *       &front()             {return (StRpsCluster  *       &)fV.front();}

 StRpsCluster * const &back()        const {return (StRpsCluster  * const &)fV.back();}
 StRpsCluster *       &back()              {return (StRpsCluster  *       &)fV.back();}

const_StRpsClusterIterator begin() const {return (const_StRpsClusterIterator)&(*(fV.begin()));}
      StRpsClusterIterator begin()       {return (      StRpsClusterIterator)&(*(fV.begin()));}
const_StRpsClusterIterator end()   const {return (const_StRpsClusterIterator)&(*(fV.end()));}
      StRpsClusterIterator end()         {return (      StRpsClusterIterator)&(*(fV.end()));}
      StRpsClusterIterator erase(StRpsClusterIterator  it)
      {return (StRpsClusterIterator)Erase((TObject**)it,1);}
      StRpsClusterIterator erase(StRpsClusterIterator fst,StRpsClusterIterator lst)
      {return (StRpsClusterIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRpsCluster *       &operator[](Int_t i)       {return at(i);}
      StRpsCluster * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRpsCluster *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRpsCluster,1) 
};
typedef       StRpsClusterIterator  StPtrVecRpsClusterIterator;
typedef const_StRpsClusterIterator  StPtrVecRpsClusterConstIterator;
typedef       StRpsClusterIterator  StSPtrVecRpsClusterIterator;
typedef const_StRpsClusterIterator  StSPtrVecRpsClusterConstIterator;

//______________________________________________________________
class StRpsTrack;
typedef StRpsTrack**            StRpsTrackIterator;
typedef StRpsTrack * const * const_StRpsTrackIterator;

class StPtrVecRpsTrack : public StRefArray 
{ 
public: 
StPtrVecRpsTrack(Int_t sz=0):StRefArray(sz){};
StPtrVecRpsTrack(const StPtrVecRpsTrack &from):StRefArray(from){};
virtual        ~StPtrVecRpsTrack(){};

 StRpsTrack * const &at(Int_t idx) const {return (StRpsTrack  * const &)fV[idx];}
 StRpsTrack *       &at(Int_t idx)       {return (StRpsTrack  *       &)fV[idx];}

 StRpsTrack * const &front()       const {return (StRpsTrack  * const &)fV.front();}
 StRpsTrack *       &front()             {return (StRpsTrack  *       &)fV.front();}

 StRpsTrack * const &back()        const {return (StRpsTrack  * const &)fV.back();}
 StRpsTrack *       &back()              {return (StRpsTrack  *       &)fV.back();}

const_StRpsTrackIterator begin() const {return (const_StRpsTrackIterator)&(*(fV.begin()));}
      StRpsTrackIterator begin()       {return (      StRpsTrackIterator)&(*(fV.begin()));}
const_StRpsTrackIterator end()   const {return (const_StRpsTrackIterator)&(*(fV.end()));}
      StRpsTrackIterator end()         {return (      StRpsTrackIterator)&(*(fV.end()));}
      StRpsTrackIterator erase(StRpsTrackIterator  it)
      {return (StRpsTrackIterator)Erase((TObject**)it,0);}
      StRpsTrackIterator erase(StRpsTrackIterator fst,StRpsTrackIterator lst)
      {return (StRpsTrackIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRpsTrack *       &operator[](Int_t i)       {return at(i);}
      StRpsTrack * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRpsTrack * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRpsTrack ,1) 
};


class StSPtrVecRpsTrack : public StStrArray 
{ 
public: 
StSPtrVecRpsTrack(Int_t sz=0):StStrArray(sz){};
StSPtrVecRpsTrack(const StSPtrVecRpsTrack &from):StStrArray(from){};

 StRpsTrack * const &at(Int_t idx) const {return (StRpsTrack  * const &)fV[idx];}
 StRpsTrack *       &at(Int_t idx)       {return (StRpsTrack  *       &)fV[idx];}

 StRpsTrack * const &front()       const {return (StRpsTrack  * const &)fV.front();}
 StRpsTrack *       &front()             {return (StRpsTrack  *       &)fV.front();}

 StRpsTrack * const &back()        const {return (StRpsTrack  * const &)fV.back();}
 StRpsTrack *       &back()              {return (StRpsTrack  *       &)fV.back();}

const_StRpsTrackIterator begin() const {return (const_StRpsTrackIterator)&(*(fV.begin()));}
      StRpsTrackIterator begin()       {return (      StRpsTrackIterator)&(*(fV.begin()));}
const_StRpsTrackIterator end()   const {return (const_StRpsTrackIterator)&(*(fV.end()));}
      StRpsTrackIterator end()         {return (      StRpsTrackIterator)&(*(fV.end()));}
      StRpsTrackIterator erase(StRpsTrackIterator  it)
      {return (StRpsTrackIterator)Erase((TObject**)it,1);}
      StRpsTrackIterator erase(StRpsTrackIterator fst,StRpsTrackIterator lst)
      {return (StRpsTrackIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRpsTrack *       &operator[](Int_t i)       {return at(i);}
      StRpsTrack * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRpsTrack *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRpsTrack,1) 
};
typedef       StRpsTrackIterator  StPtrVecRpsTrackIterator;
typedef const_StRpsTrackIterator  StPtrVecRpsTrackConstIterator;
typedef       StRpsTrackIterator  StSPtrVecRpsTrackIterator;
typedef const_StRpsTrackIterator  StSPtrVecRpsTrackConstIterator;

//______________________________________________________________
class StRpsTrackPoint;
typedef StRpsTrackPoint**            StRpsTrackPointIterator;
typedef StRpsTrackPoint * const * const_StRpsTrackPointIterator;

class StPtrVecRpsTrackPoint : public StRefArray 
{ 
public: 
StPtrVecRpsTrackPoint(Int_t sz=0):StRefArray(sz){};
StPtrVecRpsTrackPoint(const StPtrVecRpsTrackPoint &from):StRefArray(from){};
virtual        ~StPtrVecRpsTrackPoint(){};

 StRpsTrackPoint * const &at(Int_t idx) const {return (StRpsTrackPoint  * const &)fV[idx];}
 StRpsTrackPoint *       &at(Int_t idx)       {return (StRpsTrackPoint  *       &)fV[idx];}

 StRpsTrackPoint * const &front()       const {return (StRpsTrackPoint  * const &)fV.front();}
 StRpsTrackPoint *       &front()             {return (StRpsTrackPoint  *       &)fV.front();}

 StRpsTrackPoint * const &back()        const {return (StRpsTrackPoint  * const &)fV.back();}
 StRpsTrackPoint *       &back()              {return (StRpsTrackPoint  *       &)fV.back();}

const_StRpsTrackPointIterator begin() const {return (const_StRpsTrackPointIterator)&(*(fV.begin()));}
      StRpsTrackPointIterator begin()       {return (      StRpsTrackPointIterator)&(*(fV.begin()));}
const_StRpsTrackPointIterator end()   const {return (const_StRpsTrackPointIterator)&(*(fV.end()));}
      StRpsTrackPointIterator end()         {return (      StRpsTrackPointIterator)&(*(fV.end()));}
      StRpsTrackPointIterator erase(StRpsTrackPointIterator  it)
      {return (StRpsTrackPointIterator)Erase((TObject**)it,0);}
      StRpsTrackPointIterator erase(StRpsTrackPointIterator fst,StRpsTrackPointIterator lst)
      {return (StRpsTrackPointIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StRpsTrackPoint *       &operator[](Int_t i)       {return at(i);}
      StRpsTrackPoint * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRpsTrackPoint * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecRpsTrackPoint ,1) 
};


class StSPtrVecRpsTrackPoint : public StStrArray 
{ 
public: 
StSPtrVecRpsTrackPoint(Int_t sz=0):StStrArray(sz){};
StSPtrVecRpsTrackPoint(const StSPtrVecRpsTrackPoint &from):StStrArray(from){};

 StRpsTrackPoint * const &at(Int_t idx) const {return (StRpsTrackPoint  * const &)fV[idx];}
 StRpsTrackPoint *       &at(Int_t idx)       {return (StRpsTrackPoint  *       &)fV[idx];}

 StRpsTrackPoint * const &front()       const {return (StRpsTrackPoint  * const &)fV.front();}
 StRpsTrackPoint *       &front()             {return (StRpsTrackPoint  *       &)fV.front();}

 StRpsTrackPoint * const &back()        const {return (StRpsTrackPoint  * const &)fV.back();}
 StRpsTrackPoint *       &back()              {return (StRpsTrackPoint  *       &)fV.back();}

const_StRpsTrackPointIterator begin() const {return (const_StRpsTrackPointIterator)&(*(fV.begin()));}
      StRpsTrackPointIterator begin()       {return (      StRpsTrackPointIterator)&(*(fV.begin()));}
const_StRpsTrackPointIterator end()   const {return (const_StRpsTrackPointIterator)&(*(fV.end()));}
      StRpsTrackPointIterator end()         {return (      StRpsTrackPointIterator)&(*(fV.end()));}
      StRpsTrackPointIterator erase(StRpsTrackPointIterator  it)
      {return (StRpsTrackPointIterator)Erase((TObject**)it,1);}
      StRpsTrackPointIterator erase(StRpsTrackPointIterator fst,StRpsTrackPointIterator lst)
      {return (StRpsTrackPointIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StRpsTrackPoint *       &operator[](Int_t i)       {return at(i);}
      StRpsTrackPoint * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StRpsTrackPoint *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecRpsTrackPoint,1) 
};
typedef       StRpsTrackPointIterator  StPtrVecRpsTrackPointIterator;
typedef const_StRpsTrackPointIterator  StPtrVecRpsTrackPointConstIterator;
typedef       StRpsTrackPointIterator  StSPtrVecRpsTrackPointIterator;
typedef const_StRpsTrackPointIterator  StSPtrVecRpsTrackPointConstIterator;

//______________________________________________________________
class StSsdHit;
typedef StSsdHit**            StSsdHitIterator;
typedef StSsdHit * const * const_StSsdHitIterator;

class StPtrVecSsdHit : public StRefArray 
{ 
public: 
StPtrVecSsdHit(Int_t sz=0):StRefArray(sz){};
StPtrVecSsdHit(const StPtrVecSsdHit &from):StRefArray(from){};
virtual        ~StPtrVecSsdHit(){};

 StSsdHit * const &at(Int_t idx) const {return (StSsdHit  * const &)fV[idx];}
 StSsdHit *       &at(Int_t idx)       {return (StSsdHit  *       &)fV[idx];}

 StSsdHit * const &front()       const {return (StSsdHit  * const &)fV.front();}
 StSsdHit *       &front()             {return (StSsdHit  *       &)fV.front();}

 StSsdHit * const &back()        const {return (StSsdHit  * const &)fV.back();}
 StSsdHit *       &back()              {return (StSsdHit  *       &)fV.back();}

const_StSsdHitIterator begin() const {return (const_StSsdHitIterator)&(*(fV.begin()));}
      StSsdHitIterator begin()       {return (      StSsdHitIterator)&(*(fV.begin()));}
const_StSsdHitIterator end()   const {return (const_StSsdHitIterator)&(*(fV.end()));}
      StSsdHitIterator end()         {return (      StSsdHitIterator)&(*(fV.end()));}
      StSsdHitIterator erase(StSsdHitIterator  it)
      {return (StSsdHitIterator)Erase((TObject**)it,0);}
      StSsdHitIterator erase(StSsdHitIterator fst,StSsdHitIterator lst)
      {return (StSsdHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StSsdHit *       &operator[](Int_t i)       {return at(i);}
      StSsdHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StSsdHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecSsdHit ,1) 
};


class StSPtrVecSsdHit : public StStrArray 
{ 
public: 
StSPtrVecSsdHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecSsdHit(const StSPtrVecSsdHit &from):StStrArray(from){};

 StSsdHit * const &at(Int_t idx) const {return (StSsdHit  * const &)fV[idx];}
 StSsdHit *       &at(Int_t idx)       {return (StSsdHit  *       &)fV[idx];}

 StSsdHit * const &front()       const {return (StSsdHit  * const &)fV.front();}
 StSsdHit *       &front()             {return (StSsdHit  *       &)fV.front();}

 StSsdHit * const &back()        const {return (StSsdHit  * const &)fV.back();}
 StSsdHit *       &back()              {return (StSsdHit  *       &)fV.back();}

const_StSsdHitIterator begin() const {return (const_StSsdHitIterator)&(*(fV.begin()));}
      StSsdHitIterator begin()       {return (      StSsdHitIterator)&(*(fV.begin()));}
const_StSsdHitIterator end()   const {return (const_StSsdHitIterator)&(*(fV.end()));}
      StSsdHitIterator end()         {return (      StSsdHitIterator)&(*(fV.end()));}
      StSsdHitIterator erase(StSsdHitIterator  it)
      {return (StSsdHitIterator)Erase((TObject**)it,1);}
      StSsdHitIterator erase(StSsdHitIterator fst,StSsdHitIterator lst)
      {return (StSsdHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StSsdHit *       &operator[](Int_t i)       {return at(i);}
      StSsdHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StSsdHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecSsdHit,1) 
};
typedef       StSsdHitIterator  StPtrVecSsdHitIterator;
typedef const_StSsdHitIterator  StPtrVecSsdHitConstIterator;
typedef       StSsdHitIterator  StSPtrVecSsdHitIterator;
typedef const_StSsdHitIterator  StSPtrVecSsdHitConstIterator;

//______________________________________________________________
class StSstHit;
typedef StSstHit**            StSstHitIterator;
typedef StSstHit * const * const_StSstHitIterator;

class StPtrVecSstHit : public StRefArray 
{ 
public: 
StPtrVecSstHit(Int_t sz=0):StRefArray(sz){};
StPtrVecSstHit(const StPtrVecSstHit &from):StRefArray(from){};
virtual        ~StPtrVecSstHit(){};

 StSstHit * const &at(Int_t idx) const {return (StSstHit  * const &)fV[idx];}
 StSstHit *       &at(Int_t idx)       {return (StSstHit  *       &)fV[idx];}

 StSstHit * const &front()       const {return (StSstHit  * const &)fV.front();}
 StSstHit *       &front()             {return (StSstHit  *       &)fV.front();}

 StSstHit * const &back()        const {return (StSstHit  * const &)fV.back();}
 StSstHit *       &back()              {return (StSstHit  *       &)fV.back();}

const_StSstHitIterator begin() const {return (const_StSstHitIterator)&(*(fV.begin()));}
      StSstHitIterator begin()       {return (      StSstHitIterator)&(*(fV.begin()));}
const_StSstHitIterator end()   const {return (const_StSstHitIterator)&(*(fV.end()));}
      StSstHitIterator end()         {return (      StSstHitIterator)&(*(fV.end()));}
      StSstHitIterator erase(StSstHitIterator  it)
      {return (StSstHitIterator)Erase((TObject**)it,0);}
      StSstHitIterator erase(StSstHitIterator fst,StSstHitIterator lst)
      {return (StSstHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StSstHit *       &operator[](Int_t i)       {return at(i);}
      StSstHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StSstHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecSstHit ,1) 
};


class StSPtrVecSstHit : public StStrArray 
{ 
public: 
StSPtrVecSstHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecSstHit(const StSPtrVecSstHit &from):StStrArray(from){};

 StSstHit * const &at(Int_t idx) const {return (StSstHit  * const &)fV[idx];}
 StSstHit *       &at(Int_t idx)       {return (StSstHit  *       &)fV[idx];}

 StSstHit * const &front()       const {return (StSstHit  * const &)fV.front();}
 StSstHit *       &front()             {return (StSstHit  *       &)fV.front();}

 StSstHit * const &back()        const {return (StSstHit  * const &)fV.back();}
 StSstHit *       &back()              {return (StSstHit  *       &)fV.back();}

const_StSstHitIterator begin() const {return (const_StSstHitIterator)&(*(fV.begin()));}
      StSstHitIterator begin()       {return (      StSstHitIterator)&(*(fV.begin()));}
const_StSstHitIterator end()   const {return (const_StSstHitIterator)&(*(fV.end()));}
      StSstHitIterator end()         {return (      StSstHitIterator)&(*(fV.end()));}
      StSstHitIterator erase(StSstHitIterator  it)
      {return (StSstHitIterator)Erase((TObject**)it,1);}
      StSstHitIterator erase(StSstHitIterator fst,StSstHitIterator lst)
      {return (StSstHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StSstHit *       &operator[](Int_t i)       {return at(i);}
      StSstHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StSstHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecSstHit,1) 
};
typedef       StSstHitIterator  StPtrVecSstHitIterator;
typedef const_StSstHitIterator  StPtrVecSstHitConstIterator;
typedef       StSstHitIterator  StSPtrVecSstHitIterator;
typedef const_StSstHitIterator  StSPtrVecSstHitConstIterator;

//______________________________________________________________
class StSvtHit;
typedef StSvtHit**            StSvtHitIterator;
typedef StSvtHit * const * const_StSvtHitIterator;

class StPtrVecSvtHit : public StRefArray 
{ 
public: 
StPtrVecSvtHit(Int_t sz=0):StRefArray(sz){};
StPtrVecSvtHit(const StPtrVecSvtHit &from):StRefArray(from){};
virtual        ~StPtrVecSvtHit(){};

 StSvtHit * const &at(Int_t idx) const {return (StSvtHit  * const &)fV[idx];}
 StSvtHit *       &at(Int_t idx)       {return (StSvtHit  *       &)fV[idx];}

 StSvtHit * const &front()       const {return (StSvtHit  * const &)fV.front();}
 StSvtHit *       &front()             {return (StSvtHit  *       &)fV.front();}

 StSvtHit * const &back()        const {return (StSvtHit  * const &)fV.back();}
 StSvtHit *       &back()              {return (StSvtHit  *       &)fV.back();}

const_StSvtHitIterator begin() const {return (const_StSvtHitIterator)&(*(fV.begin()));}
      StSvtHitIterator begin()       {return (      StSvtHitIterator)&(*(fV.begin()));}
const_StSvtHitIterator end()   const {return (const_StSvtHitIterator)&(*(fV.end()));}
      StSvtHitIterator end()         {return (      StSvtHitIterator)&(*(fV.end()));}
      StSvtHitIterator erase(StSvtHitIterator  it)
      {return (StSvtHitIterator)Erase((TObject**)it,0);}
      StSvtHitIterator erase(StSvtHitIterator fst,StSvtHitIterator lst)
      {return (StSvtHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StSvtHit *       &operator[](Int_t i)       {return at(i);}
      StSvtHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StSvtHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecSvtHit ,1) 
};


class StSPtrVecSvtHit : public StStrArray 
{ 
public: 
StSPtrVecSvtHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecSvtHit(const StSPtrVecSvtHit &from):StStrArray(from){};

 StSvtHit * const &at(Int_t idx) const {return (StSvtHit  * const &)fV[idx];}
 StSvtHit *       &at(Int_t idx)       {return (StSvtHit  *       &)fV[idx];}

 StSvtHit * const &front()       const {return (StSvtHit  * const &)fV.front();}
 StSvtHit *       &front()             {return (StSvtHit  *       &)fV.front();}

 StSvtHit * const &back()        const {return (StSvtHit  * const &)fV.back();}
 StSvtHit *       &back()              {return (StSvtHit  *       &)fV.back();}

const_StSvtHitIterator begin() const {return (const_StSvtHitIterator)&(*(fV.begin()));}
      StSvtHitIterator begin()       {return (      StSvtHitIterator)&(*(fV.begin()));}
const_StSvtHitIterator end()   const {return (const_StSvtHitIterator)&(*(fV.end()));}
      StSvtHitIterator end()         {return (      StSvtHitIterator)&(*(fV.end()));}
      StSvtHitIterator erase(StSvtHitIterator  it)
      {return (StSvtHitIterator)Erase((TObject**)it,1);}
      StSvtHitIterator erase(StSvtHitIterator fst,StSvtHitIterator lst)
      {return (StSvtHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StSvtHit *       &operator[](Int_t i)       {return at(i);}
      StSvtHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StSvtHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecSvtHit,1) 
};
typedef       StSvtHitIterator  StPtrVecSvtHitIterator;
typedef const_StSvtHitIterator  StPtrVecSvtHitConstIterator;
typedef       StSvtHitIterator  StSPtrVecSvtHitIterator;
typedef const_StSvtHitIterator  StSPtrVecSvtHitConstIterator;

//______________________________________________________________
class StTofCell;
typedef StTofCell**            StTofCellIterator;
typedef StTofCell * const * const_StTofCellIterator;

class StPtrVecTofCell : public StRefArray 
{ 
public: 
StPtrVecTofCell(Int_t sz=0):StRefArray(sz){};
StPtrVecTofCell(const StPtrVecTofCell &from):StRefArray(from){};
virtual        ~StPtrVecTofCell(){};

 StTofCell * const &at(Int_t idx) const {return (StTofCell  * const &)fV[idx];}
 StTofCell *       &at(Int_t idx)       {return (StTofCell  *       &)fV[idx];}

 StTofCell * const &front()       const {return (StTofCell  * const &)fV.front();}
 StTofCell *       &front()             {return (StTofCell  *       &)fV.front();}

 StTofCell * const &back()        const {return (StTofCell  * const &)fV.back();}
 StTofCell *       &back()              {return (StTofCell  *       &)fV.back();}

const_StTofCellIterator begin() const {return (const_StTofCellIterator)&(*(fV.begin()));}
      StTofCellIterator begin()       {return (      StTofCellIterator)&(*(fV.begin()));}
const_StTofCellIterator end()   const {return (const_StTofCellIterator)&(*(fV.end()));}
      StTofCellIterator end()         {return (      StTofCellIterator)&(*(fV.end()));}
      StTofCellIterator erase(StTofCellIterator  it)
      {return (StTofCellIterator)Erase((TObject**)it,0);}
      StTofCellIterator erase(StTofCellIterator fst,StTofCellIterator lst)
      {return (StTofCellIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTofCell *       &operator[](Int_t i)       {return at(i);}
      StTofCell * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofCell * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTofCell ,1) 
};


class StSPtrVecTofCell : public StStrArray 
{ 
public: 
StSPtrVecTofCell(Int_t sz=0):StStrArray(sz){};
StSPtrVecTofCell(const StSPtrVecTofCell &from):StStrArray(from){};

 StTofCell * const &at(Int_t idx) const {return (StTofCell  * const &)fV[idx];}
 StTofCell *       &at(Int_t idx)       {return (StTofCell  *       &)fV[idx];}

 StTofCell * const &front()       const {return (StTofCell  * const &)fV.front();}
 StTofCell *       &front()             {return (StTofCell  *       &)fV.front();}

 StTofCell * const &back()        const {return (StTofCell  * const &)fV.back();}
 StTofCell *       &back()              {return (StTofCell  *       &)fV.back();}

const_StTofCellIterator begin() const {return (const_StTofCellIterator)&(*(fV.begin()));}
      StTofCellIterator begin()       {return (      StTofCellIterator)&(*(fV.begin()));}
const_StTofCellIterator end()   const {return (const_StTofCellIterator)&(*(fV.end()));}
      StTofCellIterator end()         {return (      StTofCellIterator)&(*(fV.end()));}
      StTofCellIterator erase(StTofCellIterator  it)
      {return (StTofCellIterator)Erase((TObject**)it,1);}
      StTofCellIterator erase(StTofCellIterator fst,StTofCellIterator lst)
      {return (StTofCellIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTofCell *       &operator[](Int_t i)       {return at(i);}
      StTofCell * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofCell *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTofCell,1) 
};
typedef       StTofCellIterator  StPtrVecTofCellIterator;
typedef const_StTofCellIterator  StPtrVecTofCellConstIterator;
typedef       StTofCellIterator  StSPtrVecTofCellIterator;
typedef const_StTofCellIterator  StSPtrVecTofCellConstIterator;

//______________________________________________________________
class StTofData;
typedef StTofData**            StTofDataIterator;
typedef StTofData * const * const_StTofDataIterator;

class StPtrVecTofData : public StRefArray 
{ 
public: 
StPtrVecTofData(Int_t sz=0):StRefArray(sz){};
StPtrVecTofData(const StPtrVecTofData &from):StRefArray(from){};
virtual        ~StPtrVecTofData(){};

 StTofData * const &at(Int_t idx) const {return (StTofData  * const &)fV[idx];}
 StTofData *       &at(Int_t idx)       {return (StTofData  *       &)fV[idx];}

 StTofData * const &front()       const {return (StTofData  * const &)fV.front();}
 StTofData *       &front()             {return (StTofData  *       &)fV.front();}

 StTofData * const &back()        const {return (StTofData  * const &)fV.back();}
 StTofData *       &back()              {return (StTofData  *       &)fV.back();}

const_StTofDataIterator begin() const {return (const_StTofDataIterator)&(*(fV.begin()));}
      StTofDataIterator begin()       {return (      StTofDataIterator)&(*(fV.begin()));}
const_StTofDataIterator end()   const {return (const_StTofDataIterator)&(*(fV.end()));}
      StTofDataIterator end()         {return (      StTofDataIterator)&(*(fV.end()));}
      StTofDataIterator erase(StTofDataIterator  it)
      {return (StTofDataIterator)Erase((TObject**)it,0);}
      StTofDataIterator erase(StTofDataIterator fst,StTofDataIterator lst)
      {return (StTofDataIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTofData *       &operator[](Int_t i)       {return at(i);}
      StTofData * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofData * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTofData ,1) 
};


class StSPtrVecTofData : public StStrArray 
{ 
public: 
StSPtrVecTofData(Int_t sz=0):StStrArray(sz){};
StSPtrVecTofData(const StSPtrVecTofData &from):StStrArray(from){};

 StTofData * const &at(Int_t idx) const {return (StTofData  * const &)fV[idx];}
 StTofData *       &at(Int_t idx)       {return (StTofData  *       &)fV[idx];}

 StTofData * const &front()       const {return (StTofData  * const &)fV.front();}
 StTofData *       &front()             {return (StTofData  *       &)fV.front();}

 StTofData * const &back()        const {return (StTofData  * const &)fV.back();}
 StTofData *       &back()              {return (StTofData  *       &)fV.back();}

const_StTofDataIterator begin() const {return (const_StTofDataIterator)&(*(fV.begin()));}
      StTofDataIterator begin()       {return (      StTofDataIterator)&(*(fV.begin()));}
const_StTofDataIterator end()   const {return (const_StTofDataIterator)&(*(fV.end()));}
      StTofDataIterator end()         {return (      StTofDataIterator)&(*(fV.end()));}
      StTofDataIterator erase(StTofDataIterator  it)
      {return (StTofDataIterator)Erase((TObject**)it,1);}
      StTofDataIterator erase(StTofDataIterator fst,StTofDataIterator lst)
      {return (StTofDataIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTofData *       &operator[](Int_t i)       {return at(i);}
      StTofData * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofData *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTofData,1) 
};
typedef       StTofDataIterator  StPtrVecTofDataIterator;
typedef const_StTofDataIterator  StPtrVecTofDataConstIterator;
typedef       StTofDataIterator  StSPtrVecTofDataIterator;
typedef const_StTofDataIterator  StSPtrVecTofDataConstIterator;

//______________________________________________________________
class StTofHit;
typedef StTofHit**            StTofHitIterator;
typedef StTofHit * const * const_StTofHitIterator;

class StPtrVecTofHit : public StRefArray 
{ 
public: 
StPtrVecTofHit(Int_t sz=0):StRefArray(sz){};
StPtrVecTofHit(const StPtrVecTofHit &from):StRefArray(from){};
virtual        ~StPtrVecTofHit(){};

 StTofHit * const &at(Int_t idx) const {return (StTofHit  * const &)fV[idx];}
 StTofHit *       &at(Int_t idx)       {return (StTofHit  *       &)fV[idx];}

 StTofHit * const &front()       const {return (StTofHit  * const &)fV.front();}
 StTofHit *       &front()             {return (StTofHit  *       &)fV.front();}

 StTofHit * const &back()        const {return (StTofHit  * const &)fV.back();}
 StTofHit *       &back()              {return (StTofHit  *       &)fV.back();}

const_StTofHitIterator begin() const {return (const_StTofHitIterator)&(*(fV.begin()));}
      StTofHitIterator begin()       {return (      StTofHitIterator)&(*(fV.begin()));}
const_StTofHitIterator end()   const {return (const_StTofHitIterator)&(*(fV.end()));}
      StTofHitIterator end()         {return (      StTofHitIterator)&(*(fV.end()));}
      StTofHitIterator erase(StTofHitIterator  it)
      {return (StTofHitIterator)Erase((TObject**)it,0);}
      StTofHitIterator erase(StTofHitIterator fst,StTofHitIterator lst)
      {return (StTofHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTofHit *       &operator[](Int_t i)       {return at(i);}
      StTofHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTofHit ,1) 
};


class StSPtrVecTofHit : public StStrArray 
{ 
public: 
StSPtrVecTofHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecTofHit(const StSPtrVecTofHit &from):StStrArray(from){};

 StTofHit * const &at(Int_t idx) const {return (StTofHit  * const &)fV[idx];}
 StTofHit *       &at(Int_t idx)       {return (StTofHit  *       &)fV[idx];}

 StTofHit * const &front()       const {return (StTofHit  * const &)fV.front();}
 StTofHit *       &front()             {return (StTofHit  *       &)fV.front();}

 StTofHit * const &back()        const {return (StTofHit  * const &)fV.back();}
 StTofHit *       &back()              {return (StTofHit  *       &)fV.back();}

const_StTofHitIterator begin() const {return (const_StTofHitIterator)&(*(fV.begin()));}
      StTofHitIterator begin()       {return (      StTofHitIterator)&(*(fV.begin()));}
const_StTofHitIterator end()   const {return (const_StTofHitIterator)&(*(fV.end()));}
      StTofHitIterator end()         {return (      StTofHitIterator)&(*(fV.end()));}
      StTofHitIterator erase(StTofHitIterator  it)
      {return (StTofHitIterator)Erase((TObject**)it,1);}
      StTofHitIterator erase(StTofHitIterator fst,StTofHitIterator lst)
      {return (StTofHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTofHit *       &operator[](Int_t i)       {return at(i);}
      StTofHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTofHit,1) 
};
typedef       StTofHitIterator  StPtrVecTofHitIterator;
typedef const_StTofHitIterator  StPtrVecTofHitConstIterator;
typedef       StTofHitIterator  StSPtrVecTofHitIterator;
typedef const_StTofHitIterator  StSPtrVecTofHitConstIterator;

//______________________________________________________________
class StTofRawData;
typedef StTofRawData**            StTofRawDataIterator;
typedef StTofRawData * const * const_StTofRawDataIterator;

class StPtrVecTofRawData : public StRefArray 
{ 
public: 
StPtrVecTofRawData(Int_t sz=0):StRefArray(sz){};
StPtrVecTofRawData(const StPtrVecTofRawData &from):StRefArray(from){};
virtual        ~StPtrVecTofRawData(){};

 StTofRawData * const &at(Int_t idx) const {return (StTofRawData  * const &)fV[idx];}
 StTofRawData *       &at(Int_t idx)       {return (StTofRawData  *       &)fV[idx];}

 StTofRawData * const &front()       const {return (StTofRawData  * const &)fV.front();}
 StTofRawData *       &front()             {return (StTofRawData  *       &)fV.front();}

 StTofRawData * const &back()        const {return (StTofRawData  * const &)fV.back();}
 StTofRawData *       &back()              {return (StTofRawData  *       &)fV.back();}

const_StTofRawDataIterator begin() const {return (const_StTofRawDataIterator)&(*(fV.begin()));}
      StTofRawDataIterator begin()       {return (      StTofRawDataIterator)&(*(fV.begin()));}
const_StTofRawDataIterator end()   const {return (const_StTofRawDataIterator)&(*(fV.end()));}
      StTofRawDataIterator end()         {return (      StTofRawDataIterator)&(*(fV.end()));}
      StTofRawDataIterator erase(StTofRawDataIterator  it)
      {return (StTofRawDataIterator)Erase((TObject**)it,0);}
      StTofRawDataIterator erase(StTofRawDataIterator fst,StTofRawDataIterator lst)
      {return (StTofRawDataIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTofRawData *       &operator[](Int_t i)       {return at(i);}
      StTofRawData * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofRawData * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTofRawData ,1) 
};


class StSPtrVecTofRawData : public StStrArray 
{ 
public: 
StSPtrVecTofRawData(Int_t sz=0):StStrArray(sz){};
StSPtrVecTofRawData(const StSPtrVecTofRawData &from):StStrArray(from){};

 StTofRawData * const &at(Int_t idx) const {return (StTofRawData  * const &)fV[idx];}
 StTofRawData *       &at(Int_t idx)       {return (StTofRawData  *       &)fV[idx];}

 StTofRawData * const &front()       const {return (StTofRawData  * const &)fV.front();}
 StTofRawData *       &front()             {return (StTofRawData  *       &)fV.front();}

 StTofRawData * const &back()        const {return (StTofRawData  * const &)fV.back();}
 StTofRawData *       &back()              {return (StTofRawData  *       &)fV.back();}

const_StTofRawDataIterator begin() const {return (const_StTofRawDataIterator)&(*(fV.begin()));}
      StTofRawDataIterator begin()       {return (      StTofRawDataIterator)&(*(fV.begin()));}
const_StTofRawDataIterator end()   const {return (const_StTofRawDataIterator)&(*(fV.end()));}
      StTofRawDataIterator end()         {return (      StTofRawDataIterator)&(*(fV.end()));}
      StTofRawDataIterator erase(StTofRawDataIterator  it)
      {return (StTofRawDataIterator)Erase((TObject**)it,1);}
      StTofRawDataIterator erase(StTofRawDataIterator fst,StTofRawDataIterator lst)
      {return (StTofRawDataIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTofRawData *       &operator[](Int_t i)       {return at(i);}
      StTofRawData * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofRawData *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTofRawData,1) 
};
typedef       StTofRawDataIterator  StPtrVecTofRawDataIterator;
typedef const_StTofRawDataIterator  StPtrVecTofRawDataConstIterator;
typedef       StTofRawDataIterator  StSPtrVecTofRawDataIterator;
typedef const_StTofRawDataIterator  StSPtrVecTofRawDataConstIterator;

//______________________________________________________________
class StTofSlat;
typedef StTofSlat**            StTofSlatIterator;
typedef StTofSlat * const * const_StTofSlatIterator;

class StPtrVecTofSlat : public StRefArray 
{ 
public: 
StPtrVecTofSlat(Int_t sz=0):StRefArray(sz){};
StPtrVecTofSlat(const StPtrVecTofSlat &from):StRefArray(from){};
virtual        ~StPtrVecTofSlat(){};

 StTofSlat * const &at(Int_t idx) const {return (StTofSlat  * const &)fV[idx];}
 StTofSlat *       &at(Int_t idx)       {return (StTofSlat  *       &)fV[idx];}

 StTofSlat * const &front()       const {return (StTofSlat  * const &)fV.front();}
 StTofSlat *       &front()             {return (StTofSlat  *       &)fV.front();}

 StTofSlat * const &back()        const {return (StTofSlat  * const &)fV.back();}
 StTofSlat *       &back()              {return (StTofSlat  *       &)fV.back();}

const_StTofSlatIterator begin() const {return (const_StTofSlatIterator)&(*(fV.begin()));}
      StTofSlatIterator begin()       {return (      StTofSlatIterator)&(*(fV.begin()));}
const_StTofSlatIterator end()   const {return (const_StTofSlatIterator)&(*(fV.end()));}
      StTofSlatIterator end()         {return (      StTofSlatIterator)&(*(fV.end()));}
      StTofSlatIterator erase(StTofSlatIterator  it)
      {return (StTofSlatIterator)Erase((TObject**)it,0);}
      StTofSlatIterator erase(StTofSlatIterator fst,StTofSlatIterator lst)
      {return (StTofSlatIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTofSlat *       &operator[](Int_t i)       {return at(i);}
      StTofSlat * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofSlat * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTofSlat ,1) 
};


class StSPtrVecTofSlat : public StStrArray 
{ 
public: 
StSPtrVecTofSlat(Int_t sz=0):StStrArray(sz){};
StSPtrVecTofSlat(const StSPtrVecTofSlat &from):StStrArray(from){};

 StTofSlat * const &at(Int_t idx) const {return (StTofSlat  * const &)fV[idx];}
 StTofSlat *       &at(Int_t idx)       {return (StTofSlat  *       &)fV[idx];}

 StTofSlat * const &front()       const {return (StTofSlat  * const &)fV.front();}
 StTofSlat *       &front()             {return (StTofSlat  *       &)fV.front();}

 StTofSlat * const &back()        const {return (StTofSlat  * const &)fV.back();}
 StTofSlat *       &back()              {return (StTofSlat  *       &)fV.back();}

const_StTofSlatIterator begin() const {return (const_StTofSlatIterator)&(*(fV.begin()));}
      StTofSlatIterator begin()       {return (      StTofSlatIterator)&(*(fV.begin()));}
const_StTofSlatIterator end()   const {return (const_StTofSlatIterator)&(*(fV.end()));}
      StTofSlatIterator end()         {return (      StTofSlatIterator)&(*(fV.end()));}
      StTofSlatIterator erase(StTofSlatIterator  it)
      {return (StTofSlatIterator)Erase((TObject**)it,1);}
      StTofSlatIterator erase(StTofSlatIterator fst,StTofSlatIterator lst)
      {return (StTofSlatIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTofSlat *       &operator[](Int_t i)       {return at(i);}
      StTofSlat * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTofSlat *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTofSlat,1) 
};
typedef       StTofSlatIterator  StPtrVecTofSlatIterator;
typedef const_StTofSlatIterator  StPtrVecTofSlatConstIterator;
typedef       StTofSlatIterator  StSPtrVecTofSlatIterator;
typedef const_StTofSlatIterator  StSPtrVecTofSlatConstIterator;

//______________________________________________________________
class StTpcHit;
typedef StTpcHit**            StTpcHitIterator;
typedef StTpcHit * const * const_StTpcHitIterator;

class StPtrVecTpcHit : public StRefArray 
{ 
public: 
StPtrVecTpcHit(Int_t sz=0):StRefArray(sz){};
StPtrVecTpcHit(const StPtrVecTpcHit &from):StRefArray(from){};
virtual        ~StPtrVecTpcHit(){};

 StTpcHit * const &at(Int_t idx) const {return (StTpcHit  * const &)fV[idx];}
 StTpcHit *       &at(Int_t idx)       {return (StTpcHit  *       &)fV[idx];}

 StTpcHit * const &front()       const {return (StTpcHit  * const &)fV.front();}
 StTpcHit *       &front()             {return (StTpcHit  *       &)fV.front();}

 StTpcHit * const &back()        const {return (StTpcHit  * const &)fV.back();}
 StTpcHit *       &back()              {return (StTpcHit  *       &)fV.back();}

const_StTpcHitIterator begin() const {return (const_StTpcHitIterator)&(*(fV.begin()));}
      StTpcHitIterator begin()       {return (      StTpcHitIterator)&(*(fV.begin()));}
const_StTpcHitIterator end()   const {return (const_StTpcHitIterator)&(*(fV.end()));}
      StTpcHitIterator end()         {return (      StTpcHitIterator)&(*(fV.end()));}
      StTpcHitIterator erase(StTpcHitIterator  it)
      {return (StTpcHitIterator)Erase((TObject**)it,0);}
      StTpcHitIterator erase(StTpcHitIterator fst,StTpcHitIterator lst)
      {return (StTpcHitIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTpcHit *       &operator[](Int_t i)       {return at(i);}
      StTpcHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTpcHit * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTpcHit ,1) 
};


class StSPtrVecTpcHit : public StStrArray 
{ 
public: 
StSPtrVecTpcHit(Int_t sz=0):StStrArray(sz){};
StSPtrVecTpcHit(const StSPtrVecTpcHit &from):StStrArray(from){};

 StTpcHit * const &at(Int_t idx) const {return (StTpcHit  * const &)fV[idx];}
 StTpcHit *       &at(Int_t idx)       {return (StTpcHit  *       &)fV[idx];}

 StTpcHit * const &front()       const {return (StTpcHit  * const &)fV.front();}
 StTpcHit *       &front()             {return (StTpcHit  *       &)fV.front();}

 StTpcHit * const &back()        const {return (StTpcHit  * const &)fV.back();}
 StTpcHit *       &back()              {return (StTpcHit  *       &)fV.back();}

const_StTpcHitIterator begin() const {return (const_StTpcHitIterator)&(*(fV.begin()));}
      StTpcHitIterator begin()       {return (      StTpcHitIterator)&(*(fV.begin()));}
const_StTpcHitIterator end()   const {return (const_StTpcHitIterator)&(*(fV.end()));}
      StTpcHitIterator end()         {return (      StTpcHitIterator)&(*(fV.end()));}
      StTpcHitIterator erase(StTpcHitIterator  it)
      {return (StTpcHitIterator)Erase((TObject**)it,1);}
      StTpcHitIterator erase(StTpcHitIterator fst,StTpcHitIterator lst)
      {return (StTpcHitIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTpcHit *       &operator[](Int_t i)       {return at(i);}
      StTpcHit * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTpcHit *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTpcHit,1) 
};
typedef       StTpcHitIterator  StPtrVecTpcHitIterator;
typedef const_StTpcHitIterator  StPtrVecTpcHitConstIterator;
typedef       StTpcHitIterator  StSPtrVecTpcHitIterator;
typedef const_StTpcHitIterator  StSPtrVecTpcHitConstIterator;

//______________________________________________________________
class StTrack;
typedef StTrack**            StTrackIterator;
typedef StTrack * const * const_StTrackIterator;

class StPtrVecTrack : public StRefArray 
{ 
public: 
StPtrVecTrack(Int_t sz=0):StRefArray(sz){};
StPtrVecTrack(const StPtrVecTrack &from):StRefArray(from){};
virtual        ~StPtrVecTrack(){};

 StTrack * const &at(Int_t idx) const {return (StTrack  * const &)fV[idx];}
 StTrack *       &at(Int_t idx)       {return (StTrack  *       &)fV[idx];}

 StTrack * const &front()       const {return (StTrack  * const &)fV.front();}
 StTrack *       &front()             {return (StTrack  *       &)fV.front();}

 StTrack * const &back()        const {return (StTrack  * const &)fV.back();}
 StTrack *       &back()              {return (StTrack  *       &)fV.back();}

const_StTrackIterator begin() const {return (const_StTrackIterator)&(*(fV.begin()));}
      StTrackIterator begin()       {return (      StTrackIterator)&(*(fV.begin()));}
const_StTrackIterator end()   const {return (const_StTrackIterator)&(*(fV.end()));}
      StTrackIterator end()         {return (      StTrackIterator)&(*(fV.end()));}
      StTrackIterator erase(StTrackIterator  it)
      {return (StTrackIterator)Erase((TObject**)it,0);}
      StTrackIterator erase(StTrackIterator fst,StTrackIterator lst)
      {return (StTrackIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTrack *       &operator[](Int_t i)       {return at(i);}
      StTrack * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTrack * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTrack ,1) 
};


class StSPtrVecTrack : public StStrArray 
{ 
public: 
StSPtrVecTrack(Int_t sz=0):StStrArray(sz){};
StSPtrVecTrack(const StSPtrVecTrack &from):StStrArray(from){};

 StTrack * const &at(Int_t idx) const {return (StTrack  * const &)fV[idx];}
 StTrack *       &at(Int_t idx)       {return (StTrack  *       &)fV[idx];}

 StTrack * const &front()       const {return (StTrack  * const &)fV.front();}
 StTrack *       &front()             {return (StTrack  *       &)fV.front();}

 StTrack * const &back()        const {return (StTrack  * const &)fV.back();}
 StTrack *       &back()              {return (StTrack  *       &)fV.back();}

const_StTrackIterator begin() const {return (const_StTrackIterator)&(*(fV.begin()));}
      StTrackIterator begin()       {return (      StTrackIterator)&(*(fV.begin()));}
const_StTrackIterator end()   const {return (const_StTrackIterator)&(*(fV.end()));}
      StTrackIterator end()         {return (      StTrackIterator)&(*(fV.end()));}
      StTrackIterator erase(StTrackIterator  it)
      {return (StTrackIterator)Erase((TObject**)it,1);}
      StTrackIterator erase(StTrackIterator fst,StTrackIterator lst)
      {return (StTrackIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTrack *       &operator[](Int_t i)       {return at(i);}
      StTrack * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTrack *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTrack,1) 
};
typedef       StTrackIterator  StPtrVecTrackIterator;
typedef const_StTrackIterator  StPtrVecTrackConstIterator;
typedef       StTrackIterator  StSPtrVecTrackIterator;
typedef const_StTrackIterator  StSPtrVecTrackConstIterator;

//______________________________________________________________
class StTrackDetectorInfo;
typedef StTrackDetectorInfo**            StTrackDetectorInfoIterator;
typedef StTrackDetectorInfo * const * const_StTrackDetectorInfoIterator;

class StPtrVecTrackDetectorInfo : public StRefArray 
{ 
public: 
StPtrVecTrackDetectorInfo(Int_t sz=0):StRefArray(sz){};
StPtrVecTrackDetectorInfo(const StPtrVecTrackDetectorInfo &from):StRefArray(from){};
virtual        ~StPtrVecTrackDetectorInfo(){};

 StTrackDetectorInfo * const &at(Int_t idx) const {return (StTrackDetectorInfo  * const &)fV[idx];}
 StTrackDetectorInfo *       &at(Int_t idx)       {return (StTrackDetectorInfo  *       &)fV[idx];}

 StTrackDetectorInfo * const &front()       const {return (StTrackDetectorInfo  * const &)fV.front();}
 StTrackDetectorInfo *       &front()             {return (StTrackDetectorInfo  *       &)fV.front();}

 StTrackDetectorInfo * const &back()        const {return (StTrackDetectorInfo  * const &)fV.back();}
 StTrackDetectorInfo *       &back()              {return (StTrackDetectorInfo  *       &)fV.back();}

const_StTrackDetectorInfoIterator begin() const {return (const_StTrackDetectorInfoIterator)&(*(fV.begin()));}
      StTrackDetectorInfoIterator begin()       {return (      StTrackDetectorInfoIterator)&(*(fV.begin()));}
const_StTrackDetectorInfoIterator end()   const {return (const_StTrackDetectorInfoIterator)&(*(fV.end()));}
      StTrackDetectorInfoIterator end()         {return (      StTrackDetectorInfoIterator)&(*(fV.end()));}
      StTrackDetectorInfoIterator erase(StTrackDetectorInfoIterator  it)
      {return (StTrackDetectorInfoIterator)Erase((TObject**)it,0);}
      StTrackDetectorInfoIterator erase(StTrackDetectorInfoIterator fst,StTrackDetectorInfoIterator lst)
      {return (StTrackDetectorInfoIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTrackDetectorInfo *       &operator[](Int_t i)       {return at(i);}
      StTrackDetectorInfo * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTrackDetectorInfo * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTrackDetectorInfo ,1) 
};


class StSPtrVecTrackDetectorInfo : public StStrArray 
{ 
public: 
StSPtrVecTrackDetectorInfo(Int_t sz=0):StStrArray(sz){};
StSPtrVecTrackDetectorInfo(const StSPtrVecTrackDetectorInfo &from):StStrArray(from){};

 StTrackDetectorInfo * const &at(Int_t idx) const {return (StTrackDetectorInfo  * const &)fV[idx];}
 StTrackDetectorInfo *       &at(Int_t idx)       {return (StTrackDetectorInfo  *       &)fV[idx];}

 StTrackDetectorInfo * const &front()       const {return (StTrackDetectorInfo  * const &)fV.front();}
 StTrackDetectorInfo *       &front()             {return (StTrackDetectorInfo  *       &)fV.front();}

 StTrackDetectorInfo * const &back()        const {return (StTrackDetectorInfo  * const &)fV.back();}
 StTrackDetectorInfo *       &back()              {return (StTrackDetectorInfo  *       &)fV.back();}

const_StTrackDetectorInfoIterator begin() const {return (const_StTrackDetectorInfoIterator)&(*(fV.begin()));}
      StTrackDetectorInfoIterator begin()       {return (      StTrackDetectorInfoIterator)&(*(fV.begin()));}
const_StTrackDetectorInfoIterator end()   const {return (const_StTrackDetectorInfoIterator)&(*(fV.end()));}
      StTrackDetectorInfoIterator end()         {return (      StTrackDetectorInfoIterator)&(*(fV.end()));}
      StTrackDetectorInfoIterator erase(StTrackDetectorInfoIterator  it)
      {return (StTrackDetectorInfoIterator)Erase((TObject**)it,1);}
      StTrackDetectorInfoIterator erase(StTrackDetectorInfoIterator fst,StTrackDetectorInfoIterator lst)
      {return (StTrackDetectorInfoIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTrackDetectorInfo *       &operator[](Int_t i)       {return at(i);}
      StTrackDetectorInfo * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTrackDetectorInfo *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTrackDetectorInfo,1) 
};
typedef       StTrackDetectorInfoIterator  StPtrVecTrackDetectorInfoIterator;
typedef const_StTrackDetectorInfoIterator  StPtrVecTrackDetectorInfoConstIterator;
typedef       StTrackDetectorInfoIterator  StSPtrVecTrackDetectorInfoIterator;
typedef const_StTrackDetectorInfoIterator  StSPtrVecTrackDetectorInfoConstIterator;

//______________________________________________________________
class StTrackNode;
typedef StTrackNode**            StTrackNodeIterator;
typedef StTrackNode * const * const_StTrackNodeIterator;

class StPtrVecTrackNode : public StRefArray 
{ 
public: 
StPtrVecTrackNode(Int_t sz=0):StRefArray(sz){};
StPtrVecTrackNode(const StPtrVecTrackNode &from):StRefArray(from){};
virtual        ~StPtrVecTrackNode(){};

 StTrackNode * const &at(Int_t idx) const {return (StTrackNode  * const &)fV[idx];}
 StTrackNode *       &at(Int_t idx)       {return (StTrackNode  *       &)fV[idx];}

 StTrackNode * const &front()       const {return (StTrackNode  * const &)fV.front();}
 StTrackNode *       &front()             {return (StTrackNode  *       &)fV.front();}

 StTrackNode * const &back()        const {return (StTrackNode  * const &)fV.back();}
 StTrackNode *       &back()              {return (StTrackNode  *       &)fV.back();}

const_StTrackNodeIterator begin() const {return (const_StTrackNodeIterator)&(*(fV.begin()));}
      StTrackNodeIterator begin()       {return (      StTrackNodeIterator)&(*(fV.begin()));}
const_StTrackNodeIterator end()   const {return (const_StTrackNodeIterator)&(*(fV.end()));}
      StTrackNodeIterator end()         {return (      StTrackNodeIterator)&(*(fV.end()));}
      StTrackNodeIterator erase(StTrackNodeIterator  it)
      {return (StTrackNodeIterator)Erase((TObject**)it,0);}
      StTrackNodeIterator erase(StTrackNodeIterator fst,StTrackNodeIterator lst)
      {return (StTrackNodeIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTrackNode *       &operator[](Int_t i)       {return at(i);}
      StTrackNode * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTrackNode * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTrackNode ,1) 
};


class StSPtrVecTrackNode : public StStrArray 
{ 
public: 
StSPtrVecTrackNode(Int_t sz=0):StStrArray(sz){};
StSPtrVecTrackNode(const StSPtrVecTrackNode &from):StStrArray(from){};

 StTrackNode * const &at(Int_t idx) const {return (StTrackNode  * const &)fV[idx];}
 StTrackNode *       &at(Int_t idx)       {return (StTrackNode  *       &)fV[idx];}

 StTrackNode * const &front()       const {return (StTrackNode  * const &)fV.front();}
 StTrackNode *       &front()             {return (StTrackNode  *       &)fV.front();}

 StTrackNode * const &back()        const {return (StTrackNode  * const &)fV.back();}
 StTrackNode *       &back()              {return (StTrackNode  *       &)fV.back();}

const_StTrackNodeIterator begin() const {return (const_StTrackNodeIterator)&(*(fV.begin()));}
      StTrackNodeIterator begin()       {return (      StTrackNodeIterator)&(*(fV.begin()));}
const_StTrackNodeIterator end()   const {return (const_StTrackNodeIterator)&(*(fV.end()));}
      StTrackNodeIterator end()         {return (      StTrackNodeIterator)&(*(fV.end()));}
      StTrackNodeIterator erase(StTrackNodeIterator  it)
      {return (StTrackNodeIterator)Erase((TObject**)it,1);}
      StTrackNodeIterator erase(StTrackNodeIterator fst,StTrackNodeIterator lst)
      {return (StTrackNodeIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTrackNode *       &operator[](Int_t i)       {return at(i);}
      StTrackNode * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTrackNode *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTrackNode,1) 
};
typedef       StTrackNodeIterator  StPtrVecTrackNodeIterator;
typedef const_StTrackNodeIterator  StPtrVecTrackNodeConstIterator;
typedef       StTrackNodeIterator  StSPtrVecTrackNodeIterator;
typedef const_StTrackNodeIterator  StSPtrVecTrackNodeConstIterator;

//______________________________________________________________
class StTrackPidTraits;
typedef StTrackPidTraits**            StTrackPidTraitsIterator;
typedef StTrackPidTraits * const * const_StTrackPidTraitsIterator;

class StPtrVecTrackPidTraits : public StRefArray 
{ 
public: 
StPtrVecTrackPidTraits(Int_t sz=0):StRefArray(sz){};
StPtrVecTrackPidTraits(const StPtrVecTrackPidTraits &from):StRefArray(from){};
virtual        ~StPtrVecTrackPidTraits(){};

 StTrackPidTraits * const &at(Int_t idx) const {return (StTrackPidTraits  * const &)fV[idx];}
 StTrackPidTraits *       &at(Int_t idx)       {return (StTrackPidTraits  *       &)fV[idx];}

 StTrackPidTraits * const &front()       const {return (StTrackPidTraits  * const &)fV.front();}
 StTrackPidTraits *       &front()             {return (StTrackPidTraits  *       &)fV.front();}

 StTrackPidTraits * const &back()        const {return (StTrackPidTraits  * const &)fV.back();}
 StTrackPidTraits *       &back()              {return (StTrackPidTraits  *       &)fV.back();}

const_StTrackPidTraitsIterator begin() const {return (const_StTrackPidTraitsIterator)&(*(fV.begin()));}
      StTrackPidTraitsIterator begin()       {return (      StTrackPidTraitsIterator)&(*(fV.begin()));}
const_StTrackPidTraitsIterator end()   const {return (const_StTrackPidTraitsIterator)&(*(fV.end()));}
      StTrackPidTraitsIterator end()         {return (      StTrackPidTraitsIterator)&(*(fV.end()));}
      StTrackPidTraitsIterator erase(StTrackPidTraitsIterator  it)
      {return (StTrackPidTraitsIterator)Erase((TObject**)it,0);}
      StTrackPidTraitsIterator erase(StTrackPidTraitsIterator fst,StTrackPidTraitsIterator lst)
      {return (StTrackPidTraitsIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StTrackPidTraits *       &operator[](Int_t i)       {return at(i);}
      StTrackPidTraits * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTrackPidTraits * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecTrackPidTraits ,1) 
};


class StSPtrVecTrackPidTraits : public StStrArray 
{ 
public: 
StSPtrVecTrackPidTraits(Int_t sz=0):StStrArray(sz){};
StSPtrVecTrackPidTraits(const StSPtrVecTrackPidTraits &from):StStrArray(from){};

 StTrackPidTraits * const &at(Int_t idx) const {return (StTrackPidTraits  * const &)fV[idx];}
 StTrackPidTraits *       &at(Int_t idx)       {return (StTrackPidTraits  *       &)fV[idx];}

 StTrackPidTraits * const &front()       const {return (StTrackPidTraits  * const &)fV.front();}
 StTrackPidTraits *       &front()             {return (StTrackPidTraits  *       &)fV.front();}

 StTrackPidTraits * const &back()        const {return (StTrackPidTraits  * const &)fV.back();}
 StTrackPidTraits *       &back()              {return (StTrackPidTraits  *       &)fV.back();}

const_StTrackPidTraitsIterator begin() const {return (const_StTrackPidTraitsIterator)&(*(fV.begin()));}
      StTrackPidTraitsIterator begin()       {return (      StTrackPidTraitsIterator)&(*(fV.begin()));}
const_StTrackPidTraitsIterator end()   const {return (const_StTrackPidTraitsIterator)&(*(fV.end()));}
      StTrackPidTraitsIterator end()         {return (      StTrackPidTraitsIterator)&(*(fV.end()));}
      StTrackPidTraitsIterator erase(StTrackPidTraitsIterator  it)
      {return (StTrackPidTraitsIterator)Erase((TObject**)it,1);}
      StTrackPidTraitsIterator erase(StTrackPidTraitsIterator fst,StTrackPidTraitsIterator lst)
      {return (StTrackPidTraitsIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StTrackPidTraits *       &operator[](Int_t i)       {return at(i);}
      StTrackPidTraits * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StTrackPidTraits *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecTrackPidTraits,1) 
};
typedef       StTrackPidTraitsIterator  StPtrVecTrackPidTraitsIterator;
typedef const_StTrackPidTraitsIterator  StPtrVecTrackPidTraitsConstIterator;
typedef       StTrackPidTraitsIterator  StSPtrVecTrackPidTraitsIterator;
typedef const_StTrackPidTraitsIterator  StSPtrVecTrackPidTraitsConstIterator;

//______________________________________________________________
class StV0Vertex;
typedef StV0Vertex**            StV0VertexIterator;
typedef StV0Vertex * const * const_StV0VertexIterator;

class StPtrVecV0Vertex : public StRefArray 
{ 
public: 
StPtrVecV0Vertex(Int_t sz=0):StRefArray(sz){};
StPtrVecV0Vertex(const StPtrVecV0Vertex &from):StRefArray(from){};
virtual        ~StPtrVecV0Vertex(){};

 StV0Vertex * const &at(Int_t idx) const {return (StV0Vertex  * const &)fV[idx];}
 StV0Vertex *       &at(Int_t idx)       {return (StV0Vertex  *       &)fV[idx];}

 StV0Vertex * const &front()       const {return (StV0Vertex  * const &)fV.front();}
 StV0Vertex *       &front()             {return (StV0Vertex  *       &)fV.front();}

 StV0Vertex * const &back()        const {return (StV0Vertex  * const &)fV.back();}
 StV0Vertex *       &back()              {return (StV0Vertex  *       &)fV.back();}

const_StV0VertexIterator begin() const {return (const_StV0VertexIterator)&(*(fV.begin()));}
      StV0VertexIterator begin()       {return (      StV0VertexIterator)&(*(fV.begin()));}
const_StV0VertexIterator end()   const {return (const_StV0VertexIterator)&(*(fV.end()));}
      StV0VertexIterator end()         {return (      StV0VertexIterator)&(*(fV.end()));}
      StV0VertexIterator erase(StV0VertexIterator  it)
      {return (StV0VertexIterator)Erase((TObject**)it,0);}
      StV0VertexIterator erase(StV0VertexIterator fst,StV0VertexIterator lst)
      {return (StV0VertexIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StV0Vertex *       &operator[](Int_t i)       {return at(i);}
      StV0Vertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StV0Vertex * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecV0Vertex ,1) 
};


class StSPtrVecV0Vertex : public StStrArray 
{ 
public: 
StSPtrVecV0Vertex(Int_t sz=0):StStrArray(sz){};
StSPtrVecV0Vertex(const StSPtrVecV0Vertex &from):StStrArray(from){};

 StV0Vertex * const &at(Int_t idx) const {return (StV0Vertex  * const &)fV[idx];}
 StV0Vertex *       &at(Int_t idx)       {return (StV0Vertex  *       &)fV[idx];}

 StV0Vertex * const &front()       const {return (StV0Vertex  * const &)fV.front();}
 StV0Vertex *       &front()             {return (StV0Vertex  *       &)fV.front();}

 StV0Vertex * const &back()        const {return (StV0Vertex  * const &)fV.back();}
 StV0Vertex *       &back()              {return (StV0Vertex  *       &)fV.back();}

const_StV0VertexIterator begin() const {return (const_StV0VertexIterator)&(*(fV.begin()));}
      StV0VertexIterator begin()       {return (      StV0VertexIterator)&(*(fV.begin()));}
const_StV0VertexIterator end()   const {return (const_StV0VertexIterator)&(*(fV.end()));}
      StV0VertexIterator end()         {return (      StV0VertexIterator)&(*(fV.end()));}
      StV0VertexIterator erase(StV0VertexIterator  it)
      {return (StV0VertexIterator)Erase((TObject**)it,1);}
      StV0VertexIterator erase(StV0VertexIterator fst,StV0VertexIterator lst)
      {return (StV0VertexIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StV0Vertex *       &operator[](Int_t i)       {return at(i);}
      StV0Vertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StV0Vertex *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecV0Vertex,1) 
};
typedef       StV0VertexIterator  StPtrVecV0VertexIterator;
typedef const_StV0VertexIterator  StPtrVecV0VertexConstIterator;
typedef       StV0VertexIterator  StSPtrVecV0VertexIterator;
typedef const_StV0VertexIterator  StSPtrVecV0VertexConstIterator;

//______________________________________________________________
class StXiVertex;
typedef StXiVertex**            StXiVertexIterator;
typedef StXiVertex * const * const_StXiVertexIterator;

class StPtrVecXiVertex : public StRefArray 
{ 
public: 
StPtrVecXiVertex(Int_t sz=0):StRefArray(sz){};
StPtrVecXiVertex(const StPtrVecXiVertex &from):StRefArray(from){};
virtual        ~StPtrVecXiVertex(){};

 StXiVertex * const &at(Int_t idx) const {return (StXiVertex  * const &)fV[idx];}
 StXiVertex *       &at(Int_t idx)       {return (StXiVertex  *       &)fV[idx];}

 StXiVertex * const &front()       const {return (StXiVertex  * const &)fV.front();}
 StXiVertex *       &front()             {return (StXiVertex  *       &)fV.front();}

 StXiVertex * const &back()        const {return (StXiVertex  * const &)fV.back();}
 StXiVertex *       &back()              {return (StXiVertex  *       &)fV.back();}

const_StXiVertexIterator begin() const {return (const_StXiVertexIterator)&(*(fV.begin()));}
      StXiVertexIterator begin()       {return (      StXiVertexIterator)&(*(fV.begin()));}
const_StXiVertexIterator end()   const {return (const_StXiVertexIterator)&(*(fV.end()));}
      StXiVertexIterator end()         {return (      StXiVertexIterator)&(*(fV.end()));}
      StXiVertexIterator erase(StXiVertexIterator  it)
      {return (StXiVertexIterator)Erase((TObject**)it,0);}
      StXiVertexIterator erase(StXiVertexIterator fst,StXiVertexIterator lst)
      {return (StXiVertexIterator)Erase((TObject**)fst,(TObject**)lst,0);}
      StXiVertex *       &operator[](Int_t i)       {return at(i);}
      StXiVertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StXiVertex * const to){fV.push_back((TObject*const)to);}

ClassDef(StPtrVecXiVertex ,1) 
};


class StSPtrVecXiVertex : public StStrArray 
{ 
public: 
StSPtrVecXiVertex(Int_t sz=0):StStrArray(sz){};
StSPtrVecXiVertex(const StSPtrVecXiVertex &from):StStrArray(from){};

 StXiVertex * const &at(Int_t idx) const {return (StXiVertex  * const &)fV[idx];}
 StXiVertex *       &at(Int_t idx)       {return (StXiVertex  *       &)fV[idx];}

 StXiVertex * const &front()       const {return (StXiVertex  * const &)fV.front();}
 StXiVertex *       &front()             {return (StXiVertex  *       &)fV.front();}

 StXiVertex * const &back()        const {return (StXiVertex  * const &)fV.back();}
 StXiVertex *       &back()              {return (StXiVertex  *       &)fV.back();}

const_StXiVertexIterator begin() const {return (const_StXiVertexIterator)&(*(fV.begin()));}
      StXiVertexIterator begin()       {return (      StXiVertexIterator)&(*(fV.begin()));}
const_StXiVertexIterator end()   const {return (const_StXiVertexIterator)&(*(fV.end()));}
      StXiVertexIterator end()         {return (      StXiVertexIterator)&(*(fV.end()));}
      StXiVertexIterator erase(StXiVertexIterator  it)
      {return (StXiVertexIterator)Erase((TObject**)it,1);}
      StXiVertexIterator erase(StXiVertexIterator fst,StXiVertexIterator lst)
      {return (StXiVertexIterator)Erase((TObject**)fst,(TObject**)lst,1);}
      StXiVertex *       &operator[](Int_t i)       {return at(i);}
      StXiVertex * const &operator[](Int_t i) const {return at(i);}
void  push_back(const StXiVertex *to){StStrArray::push_back((TObject*)to);}

ClassDef(StSPtrVecXiVertex,1) 
};
typedef       StXiVertexIterator  StPtrVecXiVertexIterator;
typedef const_StXiVertexIterator  StPtrVecXiVertexConstIterator;
typedef       StXiVertexIterator  StSPtrVecXiVertexIterator;
typedef const_StXiVertexIterator  StSPtrVecXiVertexConstIterator;

//______________________________________________________________

#endif
