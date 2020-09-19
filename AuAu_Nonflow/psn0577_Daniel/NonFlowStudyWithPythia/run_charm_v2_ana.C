void run_charm_v2_ana(int startFile = 0, int endFile =1, int maxEvent = 0, char *filelist = "file.lis", char* outFileName = "test_hijing.root" )
{
    gSystem->Load("libcontainer");
    gSystem->Load("libNpeFlow");

    NpeFlow* a = new NpeFlow;
    //a->setPtCut(0.2);
    //a->setEtaCut(1.0);
    //a->setFlavor(flavor);
    a->setAnaCharm(true);
    a->setOutFileName(outFileName);
    a->showCuts();
	
    a->calculate(startFile, endFile, maxEvent, filelist);
}

