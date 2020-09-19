void run_StNpeMaker(const Char_t *inputFile="test.list",TString outFileName="testMaker.root")
{
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  gSystem->Load("StPicoDstMaker");
  gSystem->Load("StDmesonMaker");
  gSystem->Load("StNpeMaker");

  TString inputFileName = inputFile;
  Int_t index = inputFileName.Index("st_");
  TString mInputFileName="";
  for(int i=index;i<(int)inputFileName.Length();i++) {
    mInputFileName.Append(inputFileName(i));
  }

  outFileName=mInputFileName;
  outFileName.ReplaceAll("anaTree.root","anaMaker.root");

  StNpeMaker* NpeMaker = new StNpeMaker(outFileName.Data());
  NpeMaker->bookObjects();
  NpeMaker->read(inputFile);
  //char filename[1000];
  //ifstream fstream(filelist.Data());
  //int ifile = 0;
  //while (fstream >> filename)
  //  {
  //    ++ifile;
  //    //      cout <<"sngl_file: "<<ifile<<" : "<<filename<<endl;
  //    NpeMaker->read(filename);
  //  }
  NpeMaker->writeObjects();
}
