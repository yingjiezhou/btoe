void run_StMakeDataQA(TString filelist,TString outFileName)
{
	gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();

	//	gSystem->Load("StPicoDstMaker");
	//	gSystem->Load("StDmesonMaker");
	//	gSystem->Load("StNpeRead");
	gSystem->Load("StMakeDataQA");

	StMakeDataQA* MC = new StMakeDataQA(outFileName.Data());
	MC->bookHistogram();

	char filename[1000];
	ifstream fstream(filelist.Data());
	int ifile = 0;
	while (fstream >> filename)
	{
		++ifile;
		cout <<"sngl_file: "<<ifile<<" : "<<filename<<endl;
		MC->read(filename);
	}

	MC->WriteHistogram();
}
