void run_StDmesonRead(TString filelist,TString outFileName)
{
	gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();

	gSystem->Load("StPicoDstMaker");
	gSystem->Load("StDmesonMaker");
	gSystem->Load("StDmesonAna");

	StDmesonRead* dMesonRead = new StDmesonRead(outFileName.Data());
	dMesonRead->bookObjects();

	char filename[1000];
	ifstream fstream(filelist.Data());
	int ifile = 0;
	while (fstream >> filename)
	{
		++ifile;
		cout <<"sngl_file: "<<ifile<<" : "<<filename<<endl;
		dMesonRead->read(filename);
	}

	dMesonRead->writeObjects();
}
