void  run_StEvtGen_Ana(TString filelist="Ana/D0_test.list",TString outfile="Ana/D0_test.root")
{
  // TString filelist="/star/u/xiao00/test_EvetGen/Production/dca_check.list";
  // TString outfile="dca_check.root";
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  gSystem->Load(".sl64_gcc482/lib/libStEvtGenDecayMaker.so");
  gSystem->Load(".sl64_gcc482/lib/libStEvtGen_Ana.so");
  StEvtGen_Ana * EvtGen_QA=new StEvtGen_Ana(outfile);
  EvtGen_QA->bookHistogram();  
  cout<< " booked the histogram"<<endl;
  char filename[1000];
  ifstream fstream(filelist.Data());
  int ifile = 0;
  while (fstream >> filename)
    {
      ++ifile;
      cout <<"sngl_file: "<<ifile<<" : "<<filename<<endl;
      EvtGen_QA->read(filename);
    }
  cout<< "this is for QA"<<endl;
  EvtGen_QA->WriteHistogram();
}
