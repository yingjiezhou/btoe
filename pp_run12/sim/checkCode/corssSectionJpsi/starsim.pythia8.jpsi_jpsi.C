// macro to instantiate the Geant3 from within
// STAR  C++  framework and get the starsim prompt
// Modified from Jason 's macro
// Added real distributions for pT, y


class St_geant_Maker;
St_geant_Maker *geant_maker = 0;

class StarGenEvent;
StarGenEvent   *event       = 0;

class StarPrimaryMaker;
StarPrimaryMaker *_primary = 0;

//class StarFilterMaker;
class StJpsiFilter;
StJpsiFilter *filter = 0;

class StarKinematics;
StarKinematics *kinematics = 0;

TF1 *ptDist  = 0;
TF1 *yDist = 0;

//Initialize the settings:
Float_t vx     = 0.;
Float_t vy     = 0.;
Float_t vz     = 0.;
Float_t vx_sig = 0.01;
Float_t vy_sig = 0.01;
Float_t vz_sig = 2.0;
//Float_t minVz  = -5.0;
//Float_t maxVz  = +5.0;
Float_t minPt  = +0.1;
Float_t maxPt  = +5.0;
Float_t minY   = -1.0;
Float_t maxY   = +1.0;
Float_t ptHatMin = 0;
Float_t ptHatMax = 128;

// ----------------------------------------------------------------------------
void geometry( TString tag, Bool_t agml=true )
{
  TString cmd = "DETP GEOM "; cmd += tag;
  if ( !geant_maker ) geant_maker = (St_geant_Maker *)chain->GetMaker("geant");
  geant_maker -> LoadGeometry(cmd);
  //  if ( agml ) command("gexec $STAR_LIB/libxgeometry.so");
}
// ----------------------------------------------------------------------------
void command( TString cmd )
{
  if ( !geant_maker ) geant_maker = (St_geant_Maker *)chain->GetMaker("geant");
  geant_maker -> Do( cmd );
}
// ----------------------------------------------------------------------------
void trig( Int_t n=0, Int_t Index = 1)
{
  for ( Int_t i=0; i<n; i++ ) {
    chain->Clear();
    // Throw 5 D0 flat in -1 to 1 w/ momentum btwn 0.1 and 5 GeV
    //if(kinematics) kinematics->Kine( 5, "D0", minPt, maxPt, minY, maxY );
    
    // Generate 5 D0 according to a PT and Y distribution
    //if(kinematics) kinematics->Dist(5, "D0", ptDist, yDist );
    
    chain->Make();
    _primary->event()->Print();
    command("gprint kine");
  }
}
// ----------------------------------------------------------------------------
void Pythia8( TString config="pp:jpsi" )
{
  
  //
  // Create the pythia 8 event generator and add it to
  // the primary generator
  //
  StarPythia8 *pythia8 = new StarPythia8();
  if ( config=="pp:promptjpsi" )
  {
    pythia8->SetFrame("CMS", 200.0);
    pythia8->SetBlue("proton");
    pythia8->SetYell("proton");
    //charmonium
    pythia8->Set("Charmonium:all = on");
    
    //singlet
    //pythia8->Set("Charmonium:gg2QQbar[3S1(1)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[3P0(1)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[3P1(1)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[3S2(1)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3P0(1)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3P1(1)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3P2(1)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3P0(1)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3P1(1)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3P2(1)]g = on");
    
    //octett
    //pythia8->Set("Charmonium:gg2QQbar[3S1(8)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[1P0(8)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[3PJ(8)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3S1(8)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[1S0(8)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3PJ(8)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3S1(8)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[1S0(8)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3PJ(8)]g = on");
    pythia8->Set("SigmaProcess:renormScale2 = 3");
    pythia8->Set("SigmaProcess:factorScale2 = 3");
    pythia8->Set("SigmaProcess:renormMultFac = 2"); //2mT
    pythia8->Set("SigmaProcess:factorMultFac = 2");
    pythia8->Set(Form("PhaseSpace:pTHatMin = %f",ptHatMin));
    pythia8->Set(Form("PhaseSpace:pTHatMax = %f",ptHatMax));
    
    pythia8->Set("PDF:useLHAPDF = on");
    pythia8->Set("PDF:LHAPDFset = MRSTMCal.LHgrid");
    pythia8->Set("PDF:extrapolateLHAPDF = on");
    pythia8->Set("PartonLevel:MI = on");
    pythia8->Set("PartonLevel:ISR = on");
    pythia8->Set("BeamRemnants:primordialKT = on");
    pythia8->Set("PartonLevel:FSR = on");
    pythia8->Set("StringFlav:mesonCvector = 1.5");
    pythia8->Set("StringFlav:mesonBvector = 3");
    pythia8->Set("4:m0 = 1.43");
    pythia8->Set("5:m0 = 4.30");
    //pythia8->Set("HardQCD:all = on");
    
    pythia8->Set("HardQCD:gg2ccbar = on");
    pythia8->Set("HardQCD:qqbar2ccbar = on");
    //pythia8->Set("HardQCD:gg2bbbar = on");
    //pythia8->Set("HardQCD:qqbar2bbbar = on");
    
    pythia8->Set("443:onMode=0"); // switch off J/psi decays
    pythia8->Set("443:onIfAny=11 -11"); // switch on for decays to ee and mumu
  }
  if ( config=="pp:promptjpsiTune" )
  {
    pythia8->SetFrame("CMS", 200.0);
    pythia8->SetBlue("proton");
    pythia8->SetYell("proton");
    //charmonium
    pythia8->Set("Charmonium:all = on");
    pythia8->Set("Tune:pp = 6");

    //singlet
    //pythia8->Set("Charmonium:gg2QQbar[3S1(1)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[3P0(1)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[3P1(1)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[3S2(1)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3P0(1)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3P1(1)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3P2(1)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3P0(1)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3P1(1)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3P2(1)]g = on");
    
    //octett
    //pythia8->Set("Charmonium:gg2QQbar[3S1(8)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[1P0(8)]g = on");
    //pythia8->Set("Charmonium:gg2QQbar[3PJ(8)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3S1(8)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[1S0(8)]g = on");
    //pythia8->Set("Charmonium:qg2QQbar[3PJ(8)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3S1(8)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[1S0(8)]g = on");
    //pythia8->Set("Charmonium:qqbar2QQbar[3PJ(8)]g = on");
    pythia8->Set("SigmaProcess:renormScale2 = 3");
    pythia8->Set("SigmaProcess:factorScale2 = 3");
    pythia8->Set("SigmaProcess:renormMultFac = 2"); //2mT
    pythia8->Set("SigmaProcess:factorMultFac = 2");
    pythia8->Set(Form("PhaseSpace:pTHatMin = %f",ptHatMin));
    pythia8->Set(Form("PhaseSpace:pTHatMax = %f",ptHatMax));
    
    pythia8->Set("PDF:useLHAPDF = on");
    pythia8->Set("PDF:LHAPDFset = MRSTMCal.LHgrid");
    pythia8->Set("PDF:extrapolateLHAPDF = on");
    pythia8->Set("PartonLevel:MI = on");
    pythia8->Set("PartonLevel:ISR = on");
    pythia8->Set("BeamRemnants:primordialKT = on");
    pythia8->Set("PartonLevel:FSR = on");
    pythia8->Set("StringFlav:mesonCvector = 1.5");
    pythia8->Set("StringFlav:mesonBvector = 3");
    pythia8->Set("4:m0 = 1.43");
    pythia8->Set("5:m0 = 4.30");
    //pythia8->Set("HardQCD:all = on");
    
    pythia8->Set("HardQCD:gg2ccbar = on");
    pythia8->Set("HardQCD:qqbar2ccbar = on");
    //pythia8->Set("HardQCD:gg2bbbar = on");
    //pythia8->Set("HardQCD:qqbar2bbbar = on");
    
    pythia8->Set("443:onMode=0"); // switch off J/psi decays
    pythia8->Set("443:onIfAny=11 -11"); // switch on for decays to ee and mumu
  }
  
  if ( config=="pp:btojpsi" )
  {
    pythia8->SetFrame("CMS", 200.0);
    pythia8->SetBlue("proton");
    pythia8->SetYell("proton");
    pythia8->Set("SigmaProcess:renormScale2 = 3");
    pythia8->Set("SigmaProcess:factorScale2 = 3");
    pythia8->Set("SigmaProcess:renormMultFac = 2"); //2mT
    pythia8->Set("SigmaProcess:factorMultFac = 2");
    //charmonium
    //pythia8->Set("Charmonium:all = on");
    pythia8->Set(Form("PhaseSpace:pTHatMin = %f",ptHatMin));
    pythia8->Set(Form("PhaseSpace:pTHatMax = %f",ptHatMax));
    
    pythia8->Set("PDF:useLHAPDF = on");
    pythia8->Set("PDF:LHAPDFset = MRSTMCal.LHgrid");
    pythia8->Set("PDF:extrapolateLHAPDF = on");
    pythia8->Set("PartonLevel:MI = on");
    pythia8->Set("PartonLevel:ISR = on");
    pythia8->Set("BeamRemnants:primordialKT = on");
    pythia8->Set("PartonLevel:FSR = on");
    pythia8->Set("StringFlav:mesonCvector = 1.5");
    pythia8->Set("StringFlav:mesonBvector = 3");
    pythia8->Set("4:m0 = 1.43");
    pythia8->Set("5:m0 = 4.30");
    //pythia8->Set("HardQCD:all = on");
    
    //pythia8->Set("HardQCD:gg2ccbar = on");
    //pythia8->Set("HardQCD:qqbar2ccbar = on");
    pythia8->Set("HardQCD:gg2bbbar = on");
    pythia8->Set("HardQCD:qqbar2bbbar = on");
    
    pythia8->Set("443:onMode=0"); // switch off J/psi decays
    pythia8->Set("443:onIfAny=11 -11"); // switch on for decays to ee and mumu
    
  }
  
  _primary -> AddGenerator( pythia8 );
  
}

// ----------------------------------------------------------------------------
void Pythia6( TString config="pp:promptjpsi" )
{
  
  //
  // Create the pythia 6 event generator and add it to
  // the primary generator
  //
  gSystem->Load( "libPythia6_4_28.so");
  
  StarPythia6 *pythia6 = new StarPythia6("pythia6");
  if ( config=="pp:promptjpsi" )
  {
    cout<<"energy = 200"<<endl;
    pythia6->SetFrame("CMS", 200.0 );
    pythia6->SetBlue("proton");
    pythia6->SetYell("proton");
    
    // Setup pythia process
    PySubs_t &pysubs = pythia6->pysubs();
    //pysubs.msel = 4; //ccbar
    pysubs.msel = 61; //charmonium
    //int &msub81 = pysubs.msub(81);
    //int &msub82 = pysubs.msub(82);
    //msub81 = 1;
    //msub82 = 1;
    //pysubs.ckin(3) = 4;
    
    /*
     PyPars_t &pypars = pythia6->pypars();
     pypars.mstp(51) = 7;
     pypars.mstp(82) = 4;
     pypars.parp(82) = 2.0;
     pypars.parp(83) = 0.5;
     pypars.parp(84) = 0.4;
     pypars.parp(85) = 0.9;
     pypars.parp(86) = 0.95;
     pypars.parp(89) = 1800;
     pypars.parp(90) = 0.05;
     pypars.parp(91) = 1.0;
     pypars.parp(67) = 4.0;
     
     */
    PyDat3_t &pydat3 = pythia6->pydat3();
    //pydat3.mdcy(102,1) = 0;
    //pydat3.mdcy(106,1) = 0;
    //pydat3.mdcy(109,1) = 0;
    //pydat3.mdcy(116,1) = 0;
    //pydat3.mdcy(112,1) = 0;
    //pydat3.mdcy(105,1) = 0;
    //pydat3.mdcy(164,1) = 0;
    //pydat3.mdcy(167,1) = 0;
    //pydat3.mdcy(162,1) = 0;
    //pydat3.mdcy(169,1) = 0;
    //pydat3.mdcy(172,1) = 0;
    //pydat3.mdcy(174,1) = 0;
    //pydat3.mdcy(176,1) = 0;
    //pydat3.mdcy(122,1) = 0;
    //pydat3.mdcy(125,1) = 0;
    //pydat3.mdcy(128,1) = 0;
    //pydat3.mdcy(181,1) = 0;
    //pydat3.mdcy(123,1) = 0;
    //pydat3.mdcy(126,1) = 0;
    
    for(int i=858;i<=860;i++) {
      if (i==858) continue; //Jpsi->ee
      pydat3.mdme(i,1) = 0;
    }
  }
  _primary -> AddGenerator( pythia6 );
  
}

// ----------------------------------------------------------------------------
void myKine()
{ 
  kinematics = new StarKinematics("D0");
  _primary -> AddGenerator(kinematics);
}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void starsim( Int_t nevents=1, Int_t Index = 0, Int_t rngSeed=4321, Double_t ptHatMinInput=0, Double_t ptHatMaxInput=128 , int mode = 1)
{ 
  
  gROOT->ProcessLine(".L bfc.C");
  {
    TString simple = "y2012a geant gstar usexgeom agml ";
    bfc(0, simple );
  }
  
  gSystem->Load( "libVMC.so");
  
  gSystem->Load( "StarGeneratorUtil.so" );
  gSystem->Load( "StarGeneratorEvent.so" );
  gSystem->Load( "StarGeneratorBase.so" );
  gSystem->Load( "libMathMore.so"   );
  //gSystem->Load( "libHijing1_383.so");
  //gSystem->Load( "libKinematics.so");
  gSystem->Load( "xgeometry.so"     );
  
  gSystem->Load( "/star/u/huangbc/package/local/pythia8/LHAPDF-6.1.4/lib/libLHAPDF.so"  );
  gSystem->Load( "Pythia8_1_62.so" );
  gSystem->Load( "StarGeneratorFilt.so" );
  
  // force gstar load/call
  //gSystem->Load( "gstar.so" );
  //command("call gstar");
  
  // Setup RNG seed and map all ROOT TRandom here
  StarRandom::seed( rngSeed );
  cout<<"1"<<endl;
  StarRandom::capture();
  cout<<"2"<<endl;
  
  TString modeName;
  modeName="pjpsi";
  
  char rootname[100],fzname[100];
  if(mode<4){
    sprintf(rootname,"pythia8_%s_%d.starsim.root",modeName.Data(),Index);
    sprintf(fzname,"gfile o pythia8_%s_%d.starsim.fzd",modeName.Data(),Index);
  }else{
    sprintf(rootname,"pythia6_%s_%d.starsim.root",modeName.Data(),Index);
    sprintf(fzname,"gfile o pythia6_%s_%d.starsim.fzd",modeName.Data(),Index);
  }
  
  ptHatMin = ptHatMinInput;
  ptHatMax = ptHatMaxInput;
  //
  // Create the primary event generator and insert it
  // before the geant maker
  //
  _primary = new StarPrimaryMaker();
  {
    _primary -> SetFileName(rootname);
    _primary -> SetVertex( 0.1, -0.1, 0.0 );
    _primary -> SetSigma ( 0.1,  0.1, 45.0 );
    chain -> AddBefore( "geant", _primary );
  }
  
  //
  // These should be adjusted to your best vertex estimates
  //
  
  // Setup an event generator
  //
  
  if(mode==1){
    cout<<"Running prompt J/psi process!"<<endl;
    Pythia8("pp:promptjpsi");
  }
  if(mode==2){
    Pythia8("pp:promptjpsiTune");
  }
  if(mode==3){
    Pythia8("pp:promptjpsi");
  }
  if(mode>=4){
    Pythia6("pp:promptjpsi");
  }
  
  //
  // Setup cuts on which particles get passed to geant for
  //   simulation.  (To run generator in standalone mode,
  //   set ptmin=1.0E9.)
  //                    ptmin  ptmax
  _primary->SetPtRange  (0,  1000.0);         // GeV
  //                    etamin etamax
  _primary->SetEtaRange ( -100.0, +100.0 );
  //                    phimin phimax
  _primary->SetPhiRange ( 0., TMath::TwoPi() );
  
  filter = new StJpsiFilter();
  filter->SetDauKine(0.2,1e5,-1,1,-3.1415927,3.1415927,0.2,1e5,-1,1,-3.1415927,3.1415927);
  filter->SetParentRapidity(-1,1);
  filter->SetMode(mode); //1 for prompt j/psi, 2 for b->J/psi
  _primary -> AddFilter( filter );
  
  _primary->SetAttr("FilterKeepAll",    int(0));
  _primary->SetAttr("FilterKeepHeader", int(0));
  
  //
  // Initialize primary event generator and all sub makers
  //
  _primary -> Init();
  
  //
  // Setup geometry and set starsim to use agusread for input
  //
  //geometry("y2014");
  command("gkine -4 0");
  command(fzname);
  
  
  
  //Double_t pt0 = 3.0;
  //ptDist = new TF1("ptDist","(x/[0])/(1+(x/[0])^2)^6",0.0,10.0);
  //ptDist->SetParameter(0, pt0);
  //ptDist->Draw();
  //ptDist = new TF1("ptDist","[0]*x*TMath::Exp(-x/[1])",minPt,maxPt); //dN/pT/dpT is exp
  //ptDist->SetParameters(1.,1.);//slope = 1.;
  
  //yDist = new TF1("yDist","-TMath::Erf(x+2.6)*TMath::Erf(x-2.6)",minY,maxY);
  //yDist = new TF1("yDist","pol0",minY,maxY);
  //yDist->SetParameter(0,1.);
  
  //phi, default 0 ~ TMath::TwoPi() flat
  
  //
  // Trigger on nevents
  //
  trig( nevents );
  
  chain->Finish();
  //  command("gprint kine");
  
  command("call agexit");  // Make sure that STARSIM exits properly
  
}
// ----------------------------------------------------------------------------

