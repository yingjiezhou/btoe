// macro to instantiate the Geant3 from within
// STAR  C++  framework and get the starsim prompt
// Modified from Jason 's macro
// Added real distributions for pT, y

#include "timestamp.h"

class St_geant_Maker;
St_geant_Maker *geant_maker = 0;

class StarGenEvent;
StarGenEvent   *event       = 0;

class StarPrimaryMaker;
StarPrimaryMaker *_primary = 0;

//class StarKinematics;
//StarKinematics *kinematics = 0;
//class StarFilterMaker;
class StNPEFilter;
StNPEFilter *filter = 0;

//TF1 *ptDist  = 0;
//TF1 *yDist = 0;

//Initialize the settings:
//Float_t ptHatMin = 0;
Float_t ptHatMin = 6;
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
void trig( float vz)//, Int_t Index = 1)
{
  //for ( Int_t i=0; i<n; i++ ) {
  chain->Clear();
  _primary->SetVertex( 0.0, 0.0, vz);
  // Throw 5 D0 flat in -1 to 1 w/ momentum btwn 0.1 and 5 GeV
  //if(kinematics) kinematics->Kine( 5, "D0", minPt, maxPt, minY, maxY );
  
  // Generate 5 D0 according to a PT and Y distribution
  //if(kinematics) kinematics->Dist(5, "D0", ptDist, yDist );
  chain->Make();
  _primary->event()->Print();
  command("gprint kine");
  //}
}
// ----------------------------------------------------------------------------
void Pythia8( TString config="pp:NPE" )
{
  
  gSystem->Load( "/star/u/huangbc/package/local/pythia8/LHAPDF-6.1.4/lib/libLHAPDF.so" );// should load before pythia8.so
  gSystem->Load( "Pythia8_1_62.so"  );
  //
  // Create the pythia 8 event generator and add it to
  // the primary generator
  //
  StarPythia8 *pythia8 = new StarPythia8();
  if ( config=="pp:NPE" )
  {
    pythia8->SetFrame("CMS", 200.0);
    pythia8->SetBlue("proton");
    pythia8->SetYell("proton");
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Random-Number Seed
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //pythia8->Set("Random:setSeed = on");
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //PDF Selection
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("PDF:useLHAPDF = on");
    pythia8->Set("PDF:LHAPDFset = MRSTMCal.LHgrid");
    pythia8->Set("PDF:extrapolateLHAPDF = on");//pick the parton distribution set for protons, including from LHAPDF, to be used for all proton and antiproton beams.
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Master Switches:PartonLevel
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("PartonLevel:MPI = on");//Master switch for multiparton interactions
    pythia8->Set("PartonLevel:ISR = on");//Master switch for initial-state radiation
    pythia8->Set("PartonLevel:FSR = on");//Master switch for final-state radiation;
    
    //pythia8->Set("HardQCD:all = on");
    pythia8->Set("HardQCD:gg2ccbar = on");
    pythia8->Set("HardQCD:qqbar2ccbar = on");//pythia8->Set("HardQCD:hardccbar = on");
    pythia8->Set("HardQCD:gg2bbbar = on");
    pythia8->Set("HardQCD:qqbar2bbbar = on");//pythia8->Set("HardQCD:hardbbbar = on");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Phase Space Cuts :PhaseSpace is base class for all hard-process phase-space generators, either generic 2 → 1 or 2 → 2 ones, or specialized ones like for elastic and diffractive scattering.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set(Form("PhaseSpace:pTHatMin = %f",ptHatMin));
    pythia8->Set(Form("PhaseSpace:pTHatMax = %f",ptHatMax));//PhaseSpace is base class for all hard-process phase-space generators, either generic 2 → 1 or 2 → 2 ones, or specialized ones like for elastic and diffractive scattering.
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Couplings and Scales
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("SigmaProcess:renormScale2 = 3");//The Q^2 renormalization scale for 2 → 2 processes. 3:the arithmetic mean of the squared transverse masses of the two outgoing particles, i.e. (mT_3^2 + mT_4^2) / 2 = pT^2 + 0.5 * (m_3^2 + m_4^2).
    pythia8->Set("SigmaProcess:factorScale2 = 3");//The Q^2 factorization scale for 2 → 2 processes. 3: the arithmetic mean of the squared transverse masses of the two outgoing particles.
    pythia8->Set("SigmaProcess:renormMultFac = 2"); //2mT//?//The Q^2 renormalization scale for 2 → 1, 2 → 2 and 2 → 3 processes is multiplied by this factor relative to the scale described above (except for the options with a fix scale).
    pythia8->Set("SigmaProcess:factorMultFac = 2");//The Q^2 factorization scale for 2 → 1, 2 → 2 and 2 → 3 processes is multiplied by this factor relative to the scale described above (except for the options with a fix scale).
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Beam Remnants:Primordial kT
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("BeamRemnants:primordialKT = on");//The primordial kT of initiators of hard-scattering subsystems are selected according to Gaussian distributions in p_x and p_y separately. The widths of these distributions are chosen to be dependent on the hard scale of the central process and on the mass of the whole subsystem defined by the two initiators: sigma = (sigma_soft * Q_half + sigma_hard * Q) / (Q_half + Q) * m / (m_half + m)
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Flavour Selection
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("StringFlav:mesonCvector = 1.5");//the relative production ratio vector/pseudoscalar for charm mesons.
    pythia8->Set("StringFlav:mesonBvector = 3");//the relative production ratio vector/pseudoscalar for bottom mesons.
    
    pythia8->Set("4:m0 = 1.43");//c-quark mass D=1.43
    pythia8->Set("5:m0 = 4.30");//b-quark mass D=4.30//according to star/phenix result tune parameter
    
    //close charmonium
    pythia8->Set("Charmonium:all = on");
    pythia8->Set("Bottomonium:all = on");//contribution is low. can be on.
    
    //pythia8->Set("443:onMode=0"); // switch off J/psi decays
    //pythia8->Set("443:onIfAny=11 -11"); // switch on for decays to ee and mumu
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
  }
  else if ( config=="pp:NPETune" )
  {
    pythia8->SetFrame("CMS", 200.0);
    pythia8->SetBlue("proton");
    pythia8->SetYell("proton");
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Random-Number Seed
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //pythia8->Set("Random:setSeed = on");
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //PDF Selection
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("PDF:useLHAPDF = on");
    pythia8->Set("PDF:LHAPDFset = MRSTMCal.LHgrid");
    pythia8->Set("PDF:extrapolateLHAPDF = on");//pick the parton distribution set for protons, including from LHAPDF, to be used for all proton and antiproton beams.
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Master Switches:PartonLevel
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("PartonLevel:MPI = on");//Master switch for multiparton interactions
    pythia8->Set("PartonLevel:ISR = on");//Master switch for initial-state radiation
    pythia8->Set("PartonLevel:FSR = on");//Master switch for final-state radiation;
    
    //pythia8->Set("HardQCD:all = on");
    pythia8->Set("HardQCD:gg2ccbar = on");
    pythia8->Set("HardQCD:qqbar2ccbar = on");//pythia8->Set("HardQCD:hardccbar = on");
    pythia8->Set("HardQCD:gg2bbbar = on");
    pythia8->Set("HardQCD:qqbar2bbbar = on");//pythia8->Set("HardQCD:hardbbbar = on");
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Phase Space Cuts :PhaseSpace is base class for all hard-process phase-space generators, either generic 2 → 1 or 2 → 2 ones, or specialized ones like for elastic and diffractive scattering.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set(Form("PhaseSpace:pTHatMin = %f",ptHatMin));
    pythia8->Set(Form("PhaseSpace:pTHatMax = %f",ptHatMax));//PhaseSpace is base class for all hard-process phase-space generators, either generic 2 → 1 or 2 → 2 ones, or specialized ones like for elastic and diffractive scattering.
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Couplings and Scales
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("SigmaProcess:renormScale2 = 3");//The Q^2 renormalization scale for 2 → 2 processes. 3:the arithmetic mean of the squared transverse masses of the two outgoing particles, i.e. (mT_3^2 + mT_4^2) / 2 = pT^2 + 0.5 * (m_3^2 + m_4^2).
    pythia8->Set("SigmaProcess:factorScale2 = 3");//The Q^2 factorization scale for 2 → 2 processes. 3: the arithmetic mean of the squared transverse masses of the two outgoing particles.
    pythia8->Set("SigmaProcess:renormMultFac = 2"); //2mT//?//The Q^2 renormalization scale for 2 → 1, 2 → 2 and 2 → 3 processes is multiplied by this factor relative to the scale described above (except for the options with a fix scale).
    pythia8->Set("SigmaProcess:factorMultFac = 2");//The Q^2 factorization scale for 2 → 1, 2 → 2 and 2 → 3 processes is multiplied by this factor relative to the scale described above (except for the options with a fix scale).
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Beam Remnants:Primordial kT
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("BeamRemnants:primordialKT = on");//The primordial kT of initiators of hard-scattering subsystems are selected according to Gaussian distributions in p_x and p_y separately. The widths of these distributions are chosen to be dependent on the hard scale of the central process and on the mass of the whole subsystem defined by the two initiators: sigma = (sigma_soft * Q_half + sigma_hard * Q) / (Q_half + Q) * m / (m_half + m)
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Flavour Selection
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pythia8->Set("StringFlav:mesonCvector = 1.5");//the relative production ratio vector/pseudoscalar for charm mesons.
    pythia8->Set("StringFlav:mesonBvector = 3");//the relative production ratio vector/pseudoscalar for bottom mesons.
    
    pythia8->Set("4:m0 = 1.43");//c-quark mass D=1.43
    pythia8->Set("5:m0 = 4.30");//b-quark mass D=4.30//according to star/phenix result tune parameter
    
    //close charmonium
    pythia8->Set("Charmonium:all = on");
    pythia8->Set("Bottomonium:all = on");//contribution is low. can be on.
    
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
  }
  else if ( config=="pp:btoNPE" )
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
    
    //pythia8->Set("443:onMode=0"); // switch off J/psi decays
    //pythia8->Set("443:onIfAny=11 -11"); // switch on for decays to ee and mumu
    
  }
  
  _primary -> AddGenerator( pythia8 );
  
}

// ----------------------------------------------------------------------------
void Pythia6( TString config="pp:NPE" )
{
  
  //
  // Create the pythia 6 event generator and add it to
  // the primary generator
  //
  gSystem->Load( "libPythia6_4_28.so");
  
  StarPythia6 *pythia6 = new StarPythia6("pythia6");
  if ( config=="pp:NPE" )
  {
    cout<<"energy = 200"<<endl;
    pythia6->SetFrame("CMS", 200.0 );
    pythia6->SetBlue("proton");
    pythia6->SetYell("proton");
    
    // Setup pythia process
    PySubs_t &pysubs = pythia6->pysubs();
    pysubs.msel = 4; //ccbar
    pysubs.msel = 5; //bbbar
    //pysubs.msel = 61; //charmonium
    //int &msub81 = pysubs.msub(81);
    //int &msub82 = pysubs.msub(82);
    //msub81 = 1;
    //msub82 = 1;
    //pysubs.ckin(3) = 4;
    
    //	   PyPars_t &pypars = pythia6->pypars();
    //	   pypars.mstp(51) = 7;
    //	   pypars.mstp(82) = 4;
    //	   pypars.parp(82) = 2.0;
    //	   pypars.parp(83) = 0.5;
    //	   pypars.parp(84) = 0.4;
    //	   pypars.parp(85) = 0.9;
    //	   pypars.parp(86) = 0.95;
    //	   pypars.parp(89) = 1800;
    //	   pypars.parp(90) = 0.05;
    //	   pypars.parp(91) = 1.0;
    //	   pypars.parp(67) = 4.0;
    
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
    
    /*for(int i=858;i<=860;i++) {
     if (i==858) continue; //NPE->ee
     pydat3.mdme(i,1) = 0;
     }*/
  }
  _primary -> AddGenerator( pythia6 );
  
}



// ----------------------------------------------------------------------------
/*void myKine()
 {
 kinematics = new StarKinematics("D0");
 _primary -> AddGenerator(kinematics);
 }*/
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

TString getTimeStamp(const Char_t *daqfile="")
{
  // Get Time Stamp from Run# and Gene's script
  TString RunNum(gSystem->BaseName(daqfile));
  cout<<"ccccccccccccc"<<gSystem->BaseName(daqfile)<<" "<<RunNum.Index("13")<<endl;
  RunNum=RunNum(RunNum.Index("13"),8);
  cout<<"Retrieveing time stamp from runnumber"<<RunNum.Data()<<endl;
  cout<<"ccccccccccccc"<<" "<<RunNum.Atoi()<<endl;
  FILE *fp = gSystem->OpenPipe(Form("./run2Date.csh %d",RunNum.Atoi()),"r");
  TString timestamp="";
  timestamp.Gets(fp);
  timestamp.ReplaceAll("	","."); // replace tab with .
  if(timestamp.Length()==11){      // YYYYMMDD.HHMMSS should be >=15
    timestamp.ReplaceAll(".",".0000");
  }
  else if(timestamp.Length()==12){      // YYYYMMDD.HHMMSS should be >=15
    timestamp.ReplaceAll(".",".000");
  }
  else if(timestamp.Length()==13){      // YYYYMMDD.HHMMSS should be >=15
    timestamp.ReplaceAll(".",".00");
  }
  else if(timestamp.Length()==14){      // YYYYMMDD.HHMMSS should be >=15
    timestamp.ReplaceAll(".",".0");
  }
  cout<<timestamp.Data()<<endl;
  gSystem->ClosePipe(fp);
  //for double check
  //cout<<timestamp.Data()<<endl;
  //TString timestamp2 = RunToTimeStamp(RunNum.Atoi());
  //cout<<"another way to get the timestamp: "<<timestamp2<<endl;
  return timestamp;
}
// ----------------------------------------------------------------------------
//void starsim( Int_t nevents=10, Int_t jobindex =1, Int_t rngSeed=1234, Int_t mode=1, const Char_t * daqfile = "/star/u/huangbc/data01/simu/run12/mbVtxEff_pileup/daq/st_zerobias_adc_13039132_raw_0570001.daq",Int_t daqfileIndex=1,Double_t ptHatMinInput=0, Double_t ptHatMaxInput=128)
void starsim( Int_t nevents=10, Int_t jobindex =1, Int_t rngSeed=1234, Int_t mode=1, const Char_t * daqfile = "/star/u/huangbc/data01/simu/run12/mbVtxEff_pileup/daq/st_zerobias_adc_13039132_raw_0570001.daq",Int_t daqfileIndex=1,Double_t ptHatMinInput=6, Double_t ptHatMaxInput=128)
{ 
  
  /*gROOT->ProcessLine(".L bfc.C");
   {
   TString simple = "y2012a geant gstar usexgeom agml ";
   bfc(0, simple );
   }*/
  TString timestamp = getTimeStamp(daqfile);
  cout<<timestamp.Data()<<endl;
  gROOT->ProcessLine(".L bfc.C");
  {
    //TString simple = "y2012a geant gstar usexgeom agml ";
    TString simEnvironment = Form("y2012a geant gstar agml usexgeom sdt%s",timestamp.Data());
    cout<<"-----------------------------------------------------------------------------"<<endl;
    cout<<"the geometry used for this simulation production are:  "<<simEnvironment<<endl;
    //bfc(0, simple );
    bfc(0, simEnvironment);
  }
  
  gSystem->Load( "libVMC.so");
  gSystem->Load( "StarGeneratorUtil.so" );
  gSystem->Load( "StarGeneratorEvent.so" );
  gSystem->Load( "StarGeneratorBase.so" );
  gSystem->Load( "libMathMore.so" );
  //gSystem->Load( "libHijing1_383.so");
  //gSystem->Load( "libKinematics.so");
  gSystem->Load( "xgeometry.so" );
  
  //gSystem->Load( "/star/u/huangbc/package/local/pythia8/LHAPDF-6.1.4/lib/libLHAPDF.so"  );
  //gSystem->Load( "Pythia8_1_62.so" );
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
  modeName="pNPE";
  
  char rootname[100],fzname[100];
  if(mode<4){
    sprintf(rootname,"pythia8_%s_jobIndex%d_daqIndex%d.starsim.root",modeName.Data(), jobindex, daqfileIndex);
    sprintf(fzname,"gfile o pythia8_%s_jobIndex%d_daqIndex%d.starsim.fzd",modeName.Data(),jobindex, daqfileIndex);
  }else{
    sprintf(rootname,"pythia6_%s_jobIndex%d_daqIndex%d.starsim.root",modeName.Data(), jobindex, daqfileIndex);
    sprintf(fzname,"gfile o pythia6_%s_jobIndex%d_daqIndex%d.starsim.fzd",modeName.Data(),jobindex, daqfileIndex);
  }
  
  ptHatMin = ptHatMinInput;
  ptHatMax = ptHatMaxInput;
  //
  // Create the primary event generator and insert it
  // before the geant maker
  //
  TFile *fvz = new TFile("vz_bbcmb.root");
  TH1F *hVz = (TH1F*)fvz->Get("hBBCMBVz");
  //TFile *fvz = new TFile("TPCVz.root");
  //TH1F *hVz = (TH1F*)fvz->Get("TPCVz");
  _primary = new StarPrimaryMaker();
  {
    _primary -> SetFileName(rootname);
    //_primary -> SetVertex( 0.1, -0.1, 0.0 );
    //_primary -> SetSigma ( 0.1,  0.1, 45.0 );
    chain -> AddBefore( "geant", _primary );
  }
  
  //
  // These should be adjusted to your best vertex estimates
  //
  
  // Setup an event generator
  //
  
  if(mode==1){
    cout<<"Running NPE process!"<<endl;
    Pythia8("pp:NPE");
  }
  if(mode==2){
    Pythia8("pp:NPETune");
  }
  if(mode==3){
    Pythia8("pp:NPE");
  }
  if(mode>=4){
    Pythia6("pp:NPE");
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
  
  filter = new StNPEFilter();
  filter->SetDauKine(0.2,1e5,-0.7,0.7,-3.1415927,3.1415927);
  _primary -> AddFilter( filter );
  
  _primary->SetAttr("FilterKeepAll",    int(0));
  _primary->SetAttr("FilterKeepHeader", int(0));
  
  _primary->SetSigma( 0., 0., 0.0 );
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
  for ( Int_t i=0;i<nevents;i++ ){
    float vz = hVz->GetRandom();
    trig(vz);
  }
  //trig( nevents );
  
  chain->Finish();
  //  command("gprint kine");
  
  command("call agexit");  // Make sure that STARSIM exits properly
  
}
// ----------------------------------------------------------------------------

