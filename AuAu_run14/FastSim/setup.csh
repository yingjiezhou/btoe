#!/bin/tcsh

setenv STAR_BIN /afs/rhic.bnl.gov/star/packages/DEV/.sl64_x8664_gcc482/bin
setenv STAR_LIB /afs/rhic.bnl.gov/star/packages/DEV/.sl64_x8664_gcc482/lib
setenv ROOTSYS /afs/rhic.bnl.gov/star/ROOT/5.34.30/.sl64_x8664_gcc482/rootdeb
setenv CINTSYSDIR /afs/rhic.bnl.gov/star/ROOT/5.34.30/.sl64_x8664_gcc482/rootdeb/cint/cint

setenv PATH /opt/star/sl64_gcc482/bin:/usr/lib/jvm/jre-openjdk/bin:/afs/rhic.bnl.gov/rhstar/group:/afs/rhic.bnl.gov/star/packages/DEV/mgr:/afs/rhic.bnl.gov/star/packages/scripts:/afs/rhic.bnl.gov/star/packages/cgi:.sl64_gcc482/bin:/afs/rhic.bnl.gov/star/packages/DEV/.sl64_x8664_gcc482/bin:/usr/local/bin:/afs/rhic.bnl.gov/star/ROOT/5.34.30/.sl64_x8664_gcc482/rootdeb/bin:/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/libtool/2.2.6b/bin:/opt/star/sl64_gcc482/qt4/bin:/usr/bin:/bin:/usr/sbin:.:/afs/rhic.bnl.gov/i386_redhat50/usr/afsws/bin:/cern/pro/bin:/afs/rhic.bnl.gov/star/ROOT/Xrootd/prod/.sl64_gcc482/bin

setenv LD_LIBRARY_PATH .sl64_gcc482/lib:/afs/rhic.bnl.gov/star/packages/DEV/.sl64_x8664_gcc482/lib:/afs/rhic.bnl.gov/star/ROOT/5.34.30/.sl64_x8664_gcc482/rootdeb/lib:/opt/star/sl64_gcc482/qt4/lib:/opt/star/sl64_gcc482/lib:/afs/rhic.bnl.gov/star/ROOT/Xrootd/prod/.sl64_gcc482/lib

setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/HepMC/2.06.09/lib
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/pythia8/186/lib
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/tauola++/1.1.4/lib
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/photos++/3.56/lib
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/lib

setenv PYTHIA8DATA /star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/pythia8/186/xmldoc
