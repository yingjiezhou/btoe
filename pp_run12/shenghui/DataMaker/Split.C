#include "iostream.h"

void Split(const Int_t NUM = 10, const Int_t istart = 0)
{
  gROOT->Reset();

  ifstream* inputStream = new ifstream;
  inputStream->open("filelistfemto");
  if (!(inputStream)) {
    cout << "can not open list file" << endl;
    return;
  }
  char line[512];
  char outputfile[100];
  //ofstream outDataList;
  //outDataList.open("filelist.list");
  ofstream outData;
  for (int i=0;inputStream->good();i++) {
    inputStream->getline(line,512);
    if  ( inputStream->good() ) {
      if(i%NUM==0) {
	if(outData.is_open()) outData.close();
	sprintf(outputfile,"Listf/%d.list",(i+istart)/NUM);
	outData.open(outputfile);
	//outDataList << outputfile << endl;
      }
      //cout << " read in file " << line << endl;
      outData << line << endl;
    }
  }
  if(outData.is_open()) outData.close();
  //outDataList.close();
}
