void run_StEvtGenDecayMaker(int parent_pdg=411,int NEvent=1e7,TString outfile="/star/data01/pwg/xiao00/Fast_simulation/FastSim_Charm/Charm_Dplus.root")
//void run_StEvtGenDecayMaker(int parent_pdg=421,int NEvent=1e4,TString outfile="test.root")
{
  //D0 421
  //D+ 411
  // 111 pi0
  // B+ 521
  // 221 eta
  cout<< "PDG: "<<parent_pdg<<"  Output File"<<outfile<<endl;
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  gSystem->Load(".sl64_gcc482/lib/libStEvtGenDecayMaker.so");
  gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/lib/libEvtGen.so");
  gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/lib/libEvtGenExternal.so");
  gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/pythia8/186/lib/libpythia8.so");
  gSystem->Load(".sl64_gcc482/lib/libStarEvtGenDecayer.so");

  char buf[1024];
  // for(int iFile=0;iFile<3;iFile++){
  // sprintf(buf,"File%i",iFile);
  //  outfile+=buf;
  // cout<<outfile<<endl;
  // TString outFile=buf+outfile;
  // cout<< outFile<<endl;
     
  StEvtGenDecayMaker* MC = new StEvtGenDecayMaker(parent_pdg,NEvent,outfile);
  MC->OpenFile();
  MC->make();
  MC->SaveTree();

  return ;   
}
