#include "iostream"
#include "TString.h"
#include "TChain.h"
void RunEffSelector_list(TString listname="run.list",TString outname="test", int Maximum)
{
    TChain *ch = new TChain("nt","Ds mini Tree ");
    TString output = outname;
    output += " ";
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
    ch->Process("EffSelector.C+",output, Maximum, 0);

}

