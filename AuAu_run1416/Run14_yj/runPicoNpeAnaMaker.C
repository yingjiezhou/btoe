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

void runPicoNpeAnaMaker(TString list="picoList_small.list", TString outFileName="test.root", TString badRunListFileName = "picoList_bad_MB.list") //badRunListFileName is not used here
{
    //Check STAR Library. Please set SL_version to the original star library used in the production from http://www.star.bnl.gov/devcgi/dbProdOptionRetrv.pl
    string SL_version = "SL19b";
    string env_SL = getenv("STAR");
    if (env_SL.find(SL_version) == string::npos)
    {
        cout << "Environment Star Library does not match the requested library in runPicoNpeEventMaker.C. Exiting..." << endl;
        exit(1);
    }
    
    gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
    loadSharedLibraries();
    TMVA::Tools::Instance(); 
    gSystem->Load("StBTofUtil");
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
    StPicoNpeAnaMaker*  picoNpeAnaMaker = new StPicoNpeAnaMaker("picoNpeAnaMaker", list, outFileName.Data(), picoDstMaker);
    
    StNpeCuts* npeCuts = new StNpeCuts("npeCuts");
    picoNpeAnaMaker->setNpeCuts(npeCuts);

    // -------------- USER variables -------------------------
    
    // -- File name of bad run list
//    npeCuts->setBadRunListFileName(badRunListFileName);

    // Add your cuts here.
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

    npeCuts->setTrigger(450050); // vpdmb-5-p-nobsmd-hlt (production_mid_2014, production_low_2014)                                                                                            
    npeCuts->setTrigger(450060); // vpdmb-5-p-nobsmd-hlt (production_mid_2014, production_low_2014)                                                                                              
    npeCuts->setTrigger(450005); // vpdmb-5-p-nobsmd (production_2014)                                                                                                                           
    npeCuts->setTrigger(450015); // vpdmb-5-p-nobsmd (production_2014, production_mid_2014, production_low_2014)                                                                                 
    npeCuts->setTrigger(450025); // vpdmb-5-p-nobsmd (production_mid_2014, production_low_2014)                                                                                                  
    npeCuts->setTrigger(450201); // BHT1*VPDMB-30 (production_2014, production_mid_2014, production_low_2014)                                                                                    
    npeCuts->setTrigger(450211); // BHT1*VPDMB-30 (production_2014, production_mid_2014, production_low_2014)                                                                                    
    npeCuts->setTrigger(450202); // BHT2*VPDMB-30 (production_2014, production_mid_2014, production_low_2014)                                                                                    
    npeCuts->setTrigger(450212); // BHT2*VPDMB-30 (production_2014, production_mid_2014, production_low_2014)                                                                                    
    npeCuts->setTrigger(450203); // BHT3 (production_2014, production_mid_2014, production_low_2014)                                                                                             
    npeCuts->setTrigger(450213); // BHT3 (production_2014, production_mid_2014, production_low_2014)        

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
    //TFile *f3 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/root/weights_electron_highpt.root");
    //TFile *f4 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/root/weights_pion_highpt.root");
    //TFile *f5 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/HighTower/root/weights_electron_HT.root");
    //TFile *f6 = new TFile("/gpfs01/star/pwg/mkelsey/NPE_ANA/Likelihood/HighTower/root/weights_pion_HT.root");
    npeCuts->setDLLweights(f1,f2);
    //npeCuts->setDLLweights_highPt(f3,f4);
    //npeCuts->setDLLweights_HT(f5,f6);
    cout << "=============Running Init()=============" <<  endl;
    npeChain->Init();
    cout << "=============End Init()=============" <<  endl;
    int nEntries = picoNpeAnaMaker->getEntries();
    cout << " Total entries = " << nEntries << endl;
//    if (list == "picoList_small.list") nEntries =2000;

    for (int iEvent = 0; iEvent < nEntries; ++iEvent)
    {
        if (iEvent%100==0) cout << iEvent << endl;
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
