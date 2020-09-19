void run_StMakeDataQA_Gamma(TString filelist,TString outFileName)
{   
        cout<<"11"<<endl;
	cout<<outFileName<<endl;

	gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();

	cout<<"22"<<endl;
	gSystem->Load("StPicoDstMaker");
	gSystem->Load("StDmesonMaker");
	gSystem->Load("StNpeRead");
	gSystem->Load("StMakeDataQA");
	cout<<outFileName<<endl;
	cout<<"dd"<<endl;
	StMakeDataQA_Gamma* MC = new StMakeDataQA_Gamma(outFileName.Data());
	cout<<"bb"<<endl;	
	MC->bookHistogram();
	//	cout<<"aa"<<endl;
	//	throw (-1);
	cout<<outFileName<<endl;
	char filename[1000];
	ifstream fstream(filelist.Data());
	int ifile = 0;
	while (fstream >> filename)
	{
		++ifile;
		cout <<"sngl_file: "<<ifile<<" : "<<filename<<endl;

		MC->read(filename);
		cout<<"read "<<endl;
	}

	MC->WriteHistogram();
}
