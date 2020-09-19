#include "iostream"
#include "TString.h"
#include "TChain.h"
void RunMySelector_list(TString listname="BDTcut.list",TString outname="Ds_18_4080")
{
  TChain *ch = new TChain("DsBg","Ds mini Tree ");
  TString output = outname;
//  output += "_ScanVar3_reweight.root";
// output += "_Ds_BDTScanVar3.root";
  cout<<"Output file name is :"<<output<<endl;

  Int_t fileNumber = 0;
  ifstream inlist(listname);
  if (!(inlist)) {
    cout << "can not open list file" << endl;
    return;
  }

  cout << "reading filelist: " << listname << endl;

  TFileCollection *fc = new TFileCollection("mylist", "my input file list", listname);
  ch->AddFileInfoList((TCollection *)fc->GetList());
  std::cout << "#---->Read in " << fc->GetNFiles() << " , Total number of entries in chain (after all the files)" << ch->GetEntries() << std::endl;
  ch->Process("Selector.C++",output,5e9,0);
  // ch->Process("mySelector.C+",output,5e9,0);
}
