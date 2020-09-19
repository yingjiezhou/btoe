void run_evtGent_toyMc0(int nEvents=10000, int jobId=0)
{
  gROOT->ProcessLine(".L bfc.C");
  {
    TString simple = "y2014 geant gstar usexgeom agml ";
    bfc(0, simple );
  }

  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();

  gSystem->Load( "libVMC.so" );
  gSystem->Load( "libSt_g2t.so" );
//gSystem->Load( "libSt_geant_Maker.so" );
  gSystem->Load( "StarGeneratorUtil.so" );
  gSystem->Load( "StarGeneratorEvent.so" );
  gSystem->Load( "StarGeneratorBase.so" );
  gSystem->Load( "libMathMore.so"   );  
  gSystem->Load( "libHijing1_383.so");
  gSystem->Load( "libKinematics.so");
  gSystem->Load( "xgeometry.so"     );
  gSystem->Load("libHepMC2_06_09.so");
  gSystem->Load("libPythia8_1_86.so");
  gSystem->Load("libPhotos3_61.so");
  gSystem->Load("libTauola1_1_5.so");
  gSystem->Load(".sl73_gcc485/lib/libEvtGen1_06_00.so");

  gInterpreter->AddIncludePath("StRoot/StarGenerator/EvtGen1_06_00");
  gInterpreter->AddIncludePath("$STAR/StRoot/StarGenerator/HepMC2_06_09");

  gROOT->ProcessLine(Form(".x evtGen_toyMcLc0.C++(%i,%i)",nEvents,jobId));
}
