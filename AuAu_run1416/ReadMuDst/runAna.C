/* **************************************************
 * **************************************************
 */

#include <TSystem>

class StMaker;
class StChain;
class StMuDstMaker;


void runAna(const Char_t *inputFileList ="ee_sst.list", TString outFileName="test_sst.root")
{
    
    string SL_version = "SL19b";
    string env_SL = getenv("STAR");
    if (env_SL.find(SL_version) == string::npos)
    {
        cout << "Environment Star Library does not match the requested library in runAna.C. Exiting..." << endl;
        exit(1);
    }
    gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
    loadSharedLibraries();
    gSystem->Load("StMuDSTMaker");
    gSystem->Load("StMuAnalysisMaker");
    gSystem->Load("StRefMultCorr");

    npeChain = new StChain();  
    StMuDstMaker *dstMaker = new StMuDstMaker(0, 0, "", inputFileList, "MuDst", 100);
    StMuAnalysisMaker*  ana = new StMuAnalysisMaker("ana",outFileName.Data());
    
    // -------------- USER variables -------------------------
    
    npeChain->Init();
    int nEntries = dstMaker->chain()->GetEntries();
    cout << " Total entries = " << nEntries << endl;
    
    for (int iEvent = 0; iEvent < nEntries; ++iEvent)
    {
        if(iEvent%100==0) cout << "Working on eventNumber " << iEvent << endl;
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
