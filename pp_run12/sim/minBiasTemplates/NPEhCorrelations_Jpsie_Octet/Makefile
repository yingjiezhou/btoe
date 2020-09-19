
#===============================================================================
#   File: Makefile
#
#   Example Makefile for Pythia8 written for HF in STAR
#   Author: Thomas Ullrich
#   Last modified: September 9, 2008
#
#   This needs 3 packages installed: Pythia8, LHAPDF, and ROOT
#
#   This is setup for Mac OS X 10.5.4 but should be easy to 
#   adapt for other (Unix) platforms. In principle changing the
#   program name (PROGRAM), the location of PYTHIA (PYTHIAPATH),
#   and the LHAPDF libraries (LHAPDFPATH) should do the job.
#   Note that the environment variable ROOTSYS needs to be set.
#   Otherwise define it here in the makefile.
#===============================================================================
#PROGRAM  =  pmainHF2e
#PYTHIAPATH   = /global/u1/l/liwei/minepythia/PYTHIA/pythia8135
#LHAPDFPATH   = /global/u1/l/liwei/minepythia/LHAPDF_back/lhapdf/lib

PROGRAM  = pmainHF2e
PYTHIAPATH   = /gpfs01/star/pwg/dongx/zmiller/pdsfhome/zamiller/simu/myPythia/pythia8135
LHAPDFPATH   = /star/data01/pwg/yjzhou19/Software/lhapdf-5.9.1/lhapdf-install/lib
#LHAPDFPATH   = /star/data01/pwg/yjzhou19/Software/lhapdf5.8.1/lib


CXX      =  g++
CXXFLAGS = -O -W -Wall
CPPFLAGS =  -I$(PYTHIAPATH)/include -I$(ROOTSYS)/include 
LDFLAGS  = -L$(PYTHIAPATH)/lib/archive -L$(ROOTSYS)/lib -L$(LHAPDFPATH) -lLHAPDF -lpythia8 -llhapdfdummy -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lfreetype -lpthread -lm -ldl -rdynamic -lThread -lMathCore

all:    $(PROGRAM)


$(PROGRAM):	$(PROGRAM).cpp Makefile
		$(CXX) $(CXXFLAGS) $(PROGRAM).cpp $(CPPFLAGS) $(LDFLAGS) -o $(PROGRAM)

clean:
		rm -f $(PROGRAM) core *.o
	
