/*
* **************************************************
 *  A macro to run StPicoNpeAnaMaker
 *
 *  Authors:  **Kunsu OH (kunsu OH)
 *  Authors:  Mustafa Mustafa (mmustafa@lbl.gov)
 *
 *  **Code Maintainer
 *
 * **************************************************
 */
     
#include <TSystem>
class StMaker;
class StChain;
class StPicoDstMaker;

StChain * npeChain;

void runPicoNpeAnaMaker(TString list="test.list", TString outFileName="test.root", TString badRunListFileName = "goodruns2016_wpxl_grefhftrcut.txt")
{
    //Check STAR Library. Please set SL_version to the original star library used in the production from http://www.star.bnl.gov/devcgi/dbProdOptionRetrv.pl
    string SL_version = "SL19b";
    string env_SL = getenv("STAR");
    if (env_SL.find(SL_version) == string::npos)
    {
        cout << "Environment Star Library does not match the requested library in runPicoNpeEventMaker.C. Exiting..." << endl;
        exit(1);
    }
    gSystem->Load("StarRoot");
    gSystem->Load("St_base");
    gSystem->Load("StarClassLibrary"); //problem with vector<double>                                                                                               
    gSystem->Load("StUtilities");
    gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
    loadSharedLibraries();
    TMVA::Tools::Instance(); 
    gROOT->Macro("LoadLogger.C");
    gSystem->Load("StTpcDb");
    gSystem->Load("StDetectorDbMaker");
    gSystem->Load("StDbUtilities");
    gSystem->Load("StDaqLib");
    gSystem->Load("StDbBroker");
    gSystem->Load("St_db_Maker");
    gSystem->Load("StBTofUtil");
    gSystem->Load("StTriggerUtilities");

    gSystem->Load("StFmsUtil");
    gSystem->Load("StFmsDbMaker");
    gSystem->Load("StFmsHitMaker");
    gSystem->Load("StFmsPointMaker");

    gSystem->Load("StPicoEvent");
    gSystem->Load("StPicoDstMaker");
    gSystem->Load("StPicoPrescales");
    gSystem->Load("StPicoCutsBase");
    gSystem->Load("StPicoNpeEventMaker");
    gSystem->Load("StPicoNpeAnaMaker");
    gSystem->Load("StRefMultCorr");
    cout << "Libraries Loaded" << endl;

    npeChain = new StChain();

    StPicoDstMaker* picoDstMaker = new StPicoDstMaker(2, list, "picoDstMaker");
    
    St_db_Maker* dbMk = new St_db_Maker("db","MySQL:StarDb","$STAR/StarDb");
    dbMk->SetDateTime(20160101,0); //for run16 picoDst                                                                                                                                                                                         
    StFmsDbMaker* fmsdb = new StFmsDbMaker("fmsDb");
    fmsdb->SetDateTime(20160101,0);
  
    StPicoNpeAnaMaker*  picoNpeAnaMaker = new StPicoNpeAnaMaker("picoNpeAnaMaker", list, outFileName.Data(), picoDstMaker);

    StNpeCuts* npeCuts = new StNpeCuts("npeCuts");
    picoNpeAnaMaker->setNpeCuts(npeCuts);

    // -------------- USER variables -------------------------
    // -- File name of bad run list // but really good runs
    npeCuts->setBadRunListFileName("goodruns2016_wpxl_grefhftrcut.txt"); //zyj if not in this list, return
    // Add your cuts here.
    // trees and hists to save
    npeCuts->setMyHist(1);// Regular histograms
    npeCuts->setPhoEHist(1);// conv. electrons histograms
    npeCuts->setSignalTree(1);// signal tree
    npeCuts->setPhoETree(1);// conv. electrons tre
    npeCuts->setBKGTree(0);// BKG tree
    npeCuts->setKsTree(1);// Kshort tree
    npeCuts->setEPTree(1);// event plane tree     
    // Event cuts
    npeCuts->setCutVzMax(6.);
    npeCuts->setCutVzVpdVzMax(3.);

    npeCuts->setTrigger(520001); // 
    npeCuts->setTrigger(520011); // 
    npeCuts->setTrigger(520021); // 
    npeCuts->setTrigger(520031); // 
    npeCuts->setTrigger(520041); // 
    npeCuts->setTrigger(520051); // 
    npeCuts->setTrigger(570001); //sst 
    npeCuts->setTrigger(570805); //sst 
    npeCuts->setTrigger(570002); //nosst 
    npeCuts->setTrigger(570812); //nosst      

    npeCuts->setTrigger(520201);//BHT1*VPDMB-10
    npeCuts->setTrigger(520211);//BHT1*VPDMB-10
    npeCuts->setTrigger(520221);//BHT1*VPDMB-10  
    npeCuts->setTrigger(520231);//BHT1*VPDMB-10
    npeCuts->setTrigger(520241);//BHT1*VPDMB-10
    npeCuts->setTrigger(520251);//BHT1*VPDMB-10
    npeCuts->setTrigger(520261);//BHT1*VPDMB-10
    npeCuts->setTrigger(530201);//BHT1-VPD-10 
    npeCuts->setTrigger(540201);//BHT1-VPD-30
    npeCuts->setTrigger(550201);//BHT1 
    npeCuts->setTrigger(560201);//BHT1    
    npeCuts->setTrigger(530202);//BHT2-VPD-30
    npeCuts->setTrigger(540203);//BHT2   
    npeCuts->setTrigger(520203);//BHT3
    npeCuts->setTrigger(530213);//BHT3
    npeCuts->setTrigger(570203);//BHT3    

    // Final PID Cuts
    npeCuts->setElectronPID(-1,3); 

    // Tagged electron cuts
    npeCuts->setCutElectronNHitsFitMax(20); // 15
    npeCuts->setCutElectronNHitsdEdxMax(15);
    npeCuts->setCutElectronNHitsRatio(0.52);
    npeCuts->setCutDcaXY(1.);
    npeCuts->setCutDca(1.); //1.5
   
    npeCuts->setCutPt(0.6, 20); //0.6,20
    npeCuts->setCutEta(-0.7, 0.7);
    npeCuts->setCutElectronRequireHFT(true);
    npeCuts->setCutTPCNSigmaElectron(-3.0, 3.0);
    //Probe electron cuts
    npeCuts->setCutPartnerElectronNHitsFitMax(20); // 15
    npeCuts->setCutPartnerElectronNHitsdEdxMax(15);
    npeCuts->setCutPartnerPt(0.6, 20); //0.6,20
    npeCuts->setCutPartnerEta(-0.7, 0.7);
    npeCuts->setCutPartnerTPCNSigmaElectron(-13.0, 13.0);   
    npeCuts->setCutPartnerElectronRequireHFT(true);
    //electron pair cuts
    float const pair_dca = 1.;           //cm
    float const pair_mass_min = 0.;      //GeV
    float const pair_mass_max = 0.015;     //GeV
    float const pair_angle = 0.15;       //rad
    float const pair_theta_angle = 0.05; //rad    
    float const pair_phi = 0.1;          //rad
    float const M_JPsi_Min = 2.5;          //JPsiMass
    float const M_JPsi_Max = 3.5;          //JPsiMass                
    npeCuts->setCutElectronPair(pair_dca,pair_mass_min,pair_mass_max,pair_angle,pair_theta_angle,pair_phi);
    npeCuts->setCutJPsi(1.0,1,5.0,2.5,3.5);//DCA, abs(eta) range,JPsi Decay R,  mass_min, mass_max
    
    // BEMC PID
    bool const bemc = true;
    float const minEoverP   = 0.3; //really p/E
    float const maxEoverP   = 1.5; //really p/E
    float const phiDist     = 0.015;
    float const zDist       = 0.3;
    float const assDist     = 100.;
    npeCuts->setCutBemcPid(bemc, minEoverP, maxEoverP, phiDist, zDist, assDist);

    // BSMD PID
    bool const bsmd = true;
    int const nEta     = 2;
    int const nPhi     = 2;
    npeCuts->setCutBsmdPid(bsmd, nEta, nPhi);
    
    // TOF PID
    bool const tof = true;
    float const tofBeta     = 0.025;
    float const tofYLocal = 1.8;
    int const tofFlag = 0;
    npeCuts->setCutTofPid(tof, tofBeta, tofYLocal, tofFlag);

    //TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );  
    //TMVA::Reader *reader2 = new TMVA::Reader( "!Color:!Silent" );
    //npeCuts->setReader(reader);
    //npeCuts->bookMVA("Likelihood", "./MVA/LowPT/weights/TMVAClassification_Likelihood.weights.xml" );
    //npeCuts->setReader2(reader2);
    //npeCuts->bookMVA2("Likelihood", "./MVA/BKGHyp/weights/TMVAClassification_Likelihood.weights.xml" );
    //npeCuts->setMethod("Likelihood");
    npeCuts->setMVACut(0.45);//Lower bound on MVA cut to reduce large pion background right away
    TFile *f1 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/root/weights_electron.root");
    TFile *f2 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/root/weights_pion.root");
    TFile *f3 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/root/weights_electron_highpt.root");
    TFile *f4 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/root/weights_pion_highpt.root");
    TFile *f5 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/HighTower/root/weights_electron_HT.root");
    TFile *f6 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/HighTower/root/weights_pion_HT.root");
    npeCuts->setDLLweights(f1,f2);
    npeCuts->setDLLweights_highPt(f3,f4);
    npeCuts->setDLLweights_HT(f5,f6);
    cout << "=============Running Init()=============" <<  endl;
    npeChain->Init();
    cout << "=============End Init()=============" <<  endl;
    int nEntries = picoNpeAnaMaker->getEntries();
    cout << " Total entries = " << nEntries << endl;
    if (list == "picoList_small.list") nEntries =100;
    for (int iEvent = 0; iEvent < nEntries; ++iEvent)
    {
        if (iEvent%10==0) cout << iEvent << endl;
        npeChain->Clear();
        int iret = npeChain->Make();
        if (iret)
        {
            cout << "Bad return code!" << iret << endl;
            break;
        }
    }
    
    npeChain->Finish();
    delete npeChain;
    
}
