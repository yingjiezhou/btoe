void plotAssHadPtSpectrum(int startFile = 0, int endFile =1, int maxEvent = 0, char *filelist = "file.lis", char* outFileName = "test_hijing.root" )
{
    gSystem->Load("libcontainer");
    gSystem->Load("libNpeFlow");

    NpeFlow* a = new NpeFlow;
    //a->setPtCut(0.2);
    //a->setEtaCut(1.0);
    //a->setFlavor(flavor);
    a->setTriggerPt(2.5);
    //a->setHtTrigEffFileName("/home/kikola/NpeV2InPythia/HT1_triggeEff_pp200GeV.txt");
    a->setHtTrigEffFileName("/home/kikola/NpeV2InPythia/HT2_triggeEff_pp200GeV.txt");
    //efficiency taken from p+p run 2, |y|<0.1	
    a->setPionRecoEffFileName("/home/kikola/NpeV2InPythia/pionTrackingEff_pp200GeV_run2.dat");
    a->setProtonRecoEffFileName("/home/kikola/NpeV2InPythia/protonTrackingEff_pp200GeV_run2.dat");
    a->setKaonRecoEffFileName("/home/kikola/NpeV2InPythia/kaonTrackingEff_pp200GeV_run2.dat");

    //efficiency taken from Au+Au 200 GeV run 10, |eta|<0.1	
    //a->setPionRecoEffFileName("/home/kikola/NpeV2InPythia/pionTrackingEff_AuAu200GeV_run10.dat");
    //a->setProtonRecoEffFileName("/home/kikola/NpeV2InPythia/kaonTrackingEff_AuAu200GeV_run10.dat"); // for protons, use eff for kaons for now;
    //a->setKaonRecoEffFileName("/home/kikola/NpeV2InPythia/kaonTrackingEff_AuAu200GeV_run10.dat");
	
    a->setAnaBottom(true);
    a->setAnaCharm(true);
    a->setOutFileName(outFileName);
    a->showCuts();
	
    a->fillPtSpectra(startFile, endFile, maxEvent, filelist);
}

