/* 
 * File:   prescalelivetime.cxx
 * Author: shenghui
 * 
 * Created on Feb. 4, 2020, 00:59 AM
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "TH1F.h"

#include "StTRIGGERS.h"
#include "prescales.h"
typedef std::vector<float> vecPrescales;
std::map<int,vecPrescales> mTable;
std::map<int,vecPrescales>::iterator mLastQuery;
typedef std::vector<float> vecLivetimes;
std::map<int,vecLivetimes> mTableLv;
std::map<int,vecLivetimes>::iterator mLastQueryLv;

using namespace std;

ClassImp(prescales);

prescales* prescales::mInstance = 0;

//int triggerArray[] = {370011,370022,370501,370511,370531,370542,370546,370522,370301};
int triggerArray[] = {370011,370001,370022,370501,370511,370531,370542,370546,370522,370601,370611,370621,370641,370301,370361,370341};
std::vector<int> triggers(triggerArray,triggerArray+sizeof(triggerArray)/sizeof(int));

prescales::prescales()
{
	//cout<<"Please make sure the first trg ID is MB, this is assumed through out this analysis."<<endl;
	for(unsigned int iTrg=0;iTrg<triggers.size();iTrg++)
	{
		ReadList(iTrg);
	}
	mLastQuery = mTable.end();
	mLastQueryLv = mTableLv.end();
}
//___________________________________
prescales* prescales::Instance()
{
	if(!mInstance) mInstance = new prescales;

	return mInstance;
}
//___________________________________
prescales::~prescales()
{
}

//___________________________________________
void prescales::ReadList(int trg)
{
	stringstream st;
	st << triggers[trg];
	string listFileName = "/star/u/shenghui/shenghui/lbl/Run12/NPE/analysiscode/notecode/HT/RawYield/DataMaker/MBequivalent/StRoot/run12pp200GeVPrescales/lum_perrun_" + st.str() + ".txt";
	cout<<"Reading prescale values for trigger "<<triggers[trg]<<endl;
	//cout<<"From list "<<listFileName<<endl;

	//Open list
	ifstream runs(listFileName.c_str());
	while(!runs.eof())
	{
		string line;
		int run;
		float prescale,livetime;
		getline(runs,line);
		if(line=="\0" || line=="\n") continue;
		size_t firstSpace = line.find(" ");
		size_t lastSpace = line.rfind(" ");

		istringstream runBuffer(line.substr(0,firstSpace));
		istringstream prescaleBuffer(line.substr(firstSpace+1,lastSpace));
		istringstream livetimeBuffer(line.substr(lastSpace+1));
		runBuffer >> run;
		prescaleBuffer >> prescale;
		livetimeBuffer >> livetime;
		//cout<<run<<" "<<prescale<<" "<<livetime<<endl;
		map<int,vecPrescales>::iterator it = mTable.find(run);
		map<int,vecLivetimes>::iterator itLv = mTableLv.find(run);

		if(it==mTable.end())
		{
			vecPrescales vec(triggers.size(),-1);
			vec[trg] = prescale;
			mTable.insert(pair<int,vecPrescales>(run,vec));
		}
		else
		{ 
			if(it->second.at(trg) == -1) it->second.at(trg) = prescale;
			else
			{
				cout<<"Two prescale values for same run and same trigger."<<endl;
				cout<<"Run= "<<run<<" Trigger= "<<triggers[trg]<<" prescales= "<<it->second.at(trg)<<" "<<prescale<<endl;
			}
		}
		if(itLv==mTableLv.end())
		{
			vecLivetimes vecLv(triggers.size(),-1);
			vecLv[trg] = livetime;
			mTableLv.insert(pair<int,vecLivetimes>(run,vecLv));
		}
		else
		{ 
			if(itLv->second.at(trg) == -1) itLv->second.at(trg) = livetime;
			else
			{
				cout<<"Two livetime values for same run and same trigger."<<endl;
				cout<<"Run= "<<run<<" Trigger= "<<triggers[trg]<<" livetimes= "<<it->second.at(trg)<<" "<<livetime<<endl;
			}
		}
	}

	runs.close();
}

//__________________________________
float prescales::GetPrescale(int run, int trg)
{
	if(mLastQuery!=mTable.end() && run==mLastQuery->first) return mLastQuery->second.at(trg);
	else
	{
		map<int, vecPrescales>::iterator it = mTable.find(run);

		if (it != mTable.end())
		{
			mLastQuery = it;
			return it->second.at(trg);
		}
		else
		{
			cout << "prescales::GetPrescale: No prescale values available for run "<<run<<". Skip it." << endl;
			return -1;
		}
	}
}

//__________________________________
float prescales::GetLivetime(int run, int trg)
{
	if(mLastQueryLv!=mTableLv.end() && run==mLastQueryLv->first) return mLastQueryLv->second.at(trg);
	else
	{
		map<int, vecLivetimes>::iterator itLv = mTableLv.find(run);

		if (itLv != mTableLv.end())
		{
			mLastQueryLv = itLv;
			return itLv->second.at(trg);
		}
		else
		{
			cout << "livetimes::GetLivetime: No livetime values available for run "<<run<<". Skip it." << endl;
			return -1;
		}
	}
}

//__________________________________
int prescales::GetNumberOfRuns()
{
	return mTable.size();
}

//__________________________________
int* prescales::GetListOfRuns()
{
	int* array = new int[mTable.size()];

	map<int,vecPrescales>::iterator it;

	int c=0;
	for (it=mTable.begin(); it != mTable.end(); it++)
	{
		*(array+c) =(int)it->first;
		c++;
	}

	return array;
}
//__________________________________
void prescales::FillPrescalesHist(TH1F* hist,int trg)
{
	map<int,vecPrescales>::iterator it;

	for (it=mTable.begin(); it != mTable.end(); it++)
	{
		hist->Fill(std::distance(mTable.begin(),it),it->second.at(trg));
	}
}
//___________________________________
int prescales::RunIndex(int run)
{
	if(mLastQuery!=mTable.end() && run==mLastQuery->first) return std::distance(mTable.begin(),mLastQuery);
	else
	{
		map<int,vecPrescales>::iterator it = mTable.find(run);
		mLastQuery = it;
		return std::distance(mTable.begin(),it);
	}
}

//___________________________________
bool prescales::RunExists(int run)
{
	if(mLastQuery!=mTable.end() && run==mLastQuery->first) return true;
	else
	{
		map<int, vecPrescales>::iterator it = mTable.find(run);

		if (it != mTable.end())
		{
			mLastQuery = it;
			return true;
		}
		else return false;
	}
}

