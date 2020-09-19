void  run_Read_Ana(TString filelist="test.list",TString outfile="test.root")
{
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  gSystem->Load("StReadAna");

  TStopwatch *time =new  TStopwatch ();
   time->Start();
   StReadAna *ReadAna=new StReadAna(outfile);
   
   ReadAna->bookHistogram();  
  
   char filename[1000];
   ifstream fstream(filelist.Data());
   int ifile = 0;
   while (fstream >> filename)
     {
       ++ifile;
       ReadAna->read(filename);
       cout<< filename<<endl; 
       //    ReadAna->WriteHistogram();  
  }
   
   ReadAna->WriteHistogram();  
   time->Stop();
   cout<< "  ****************Done*************"<<endl;
   cout<<  "*********** The totol time is "<< time->Print() <<"********"<<endl;
}

