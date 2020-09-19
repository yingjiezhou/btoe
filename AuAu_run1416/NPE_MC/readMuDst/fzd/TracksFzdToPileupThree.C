//#include "stdio.h"
//#include "Riostream.h"

#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"


const int MAXHIT = 200000;

int nhits;
float x[MAXHIT];
float y[MAXHIT];
float z[MAXHIT];
float xLoc[MAXHIT];
float yLoc[MAXHIT];
float zLoc[MAXHIT];
float px[MAXHIT];
float py[MAXHIT];
float pz[MAXHIT];
float de[MAXHIT];
float ds[MAXHIT];
long key[MAXHIT];
long vid[MAXHIT];
int layer[MAXHIT];


void ResetDataTables(){

	nhits = 0;
	for (int i = 0; i < MAXHIT; ++i) {
		xLoc[i] = 0.;
		yLoc[i] = 0.;
		zLoc[i] = 0.;
                x[i] = 0.;
                y[i] = 0.;
                z[i] = 0.;
		px[i] = 0.;
		py[i] = 0.;
		pz[i] = 0.;
		de[i] = 0.;
		ds[i] = 0.;
		key[i] = 0;
		vid[i] = 0;
		layer[i] = 0;
	}
}



void TracksFzdToPileupThree(Int_t Nevents=1, TString fzfile  ="outpup.10.test.fzd", TString outFileName = "upcElePileupTree.root")
{
	const Int_t _debug = 0;

	const Float_t pi = TMath::Pi();
	const Float_t rad2deg = 180.0 / TMath::Pi();

	TFile* outFile = new TFile(outFileName, "recreate");



	TTree* mctree = new TTree("mctree", "mctree");		// PXL hit tree used for pileup simulation
	mctree->Branch("nhits", &nhits, "nhits/I"); 		// number of hits at PIXEL
        mctree->Branch("xLoc", xLoc, "xLoc[nhits]/F");                           // local hit position: x, y, z
        mctree->Branch("yLoc", yLoc, "yLoc[nhits]/F");
        mctree->Branch("zLoc", zLoc, "zLoc[nhits]/F");
	mctree->Branch("x", x, "x[nhits]/F");				// hit position: x, y, z
	mctree->Branch("y", y, "y[nhits]/F");
	mctree->Branch("z", z, "z[nhits]/F");
 	mctree->Branch("px", px, "px[nhits]/F");			// hit momentum: x, y, z
	mctree->Branch("py", py, "py[nhits]/F");
	mctree->Branch("pz", pz, "pz[nhits]/F");
	mctree->Branch("de", de, "de[nhits]/F");
	mctree->Branch("ds", ds, "ds[nhits]/F");
	mctree->Branch("key", key, "key[nhits]/L");
	mctree->Branch("vid", vid, "vid[nhits]/L");			// volumeId
	mctree->Branch("layer", layer, "layer[nhits]/I");	// ladder

  int eventCounter = 0;

  TH2F *TpcHist = new TH2F("TpcHist","TpcHist",400,-200.0,+200.0,400,-200.0,+200.0);
  TH2F *PixHist = new TH2F("PixHist","PixHist for tracks with n>2",200,-10.0,+10.0,200,-10.0,+10.0);
  TH1D *TrRap   = new TH1D("TrRap","Rapidity of e+e-",100,-5.,5.);
  TH1D *TrEta   = new TH1D("TrEta","Pseudorapidity of e+e-",100,-5.,5.);
  TH1D *NoPix   = new TH1D("NoPix","no Pixel hits",100,0,.5);
  TH1D *zVert   = new TH1D("zVert","Vertex z-position",100,-50.,50.);
  
  // Run BFC chain
  gROOT->LoadMacro("bfc.C");
  bfc(0,"fzin y2016a sim_T globT gen_T PxlDb",fzfile);
  //bfc(0,"fzin sim_T globT gen_T PxlDb",fzfile);

  TObjectSet *pxlDbDataSet = (TObjectSet *)chain->GetDataSet("pxl_db");
  if(!pxlDbDataSet) return;
  StPxlDb * mPxlDb = (StPxlDb *)pxlDbDataSet->GetObject();
  if(!mPxlDb) return;
                                   

  // Loop over all events
  for (Int_t i =1; i <= Nevents; i++)
    {
	  int imc = 0;
	  ResetDataTables(); 	// reset data tables


	  chain->Clear();
      if (chain->Make(i)>=kStEOF)  printf("====>EOF found..........\n");
      printf("=====> Event No. %d\n",i); 

      // for Local -> Global trasnformation
//      THashList *PxlRot = new THashList(400,0);
//      PxlRot = gStPxlDbMaker->GetRotations();

      // Find vertices
      St_g2t_vertex *g2t_vertP = (St_g2t_vertex *) chain->FindObject("g2t_vertex");
      if(g2t_vertP)
	{
	  g2t_vertex_st *vertT = g2t_vertP->GetTable();
	  Int_t Nvert          = g2t_vertP->GetNRows();
          zVert->Fill(vertT->ge_x[2]);
	  for(Int_t ii=0;ii<Nvert;ii++)
	    {
	     // zVert->Fill(vertT[ii].ge_x[2]);
		}
	}


      // Find tracks
      St_g2t_track  *g2t_trackTablePointer   = (St_g2t_track *) chain->FindObject("g2t_track");     
      if(g2t_trackTablePointer)
	{
	  g2t_track_st *trackTable = g2t_trackTablePointer->GetTable();
	  Int_t NTracks            = g2t_trackTablePointer->GetNRows();
	  cout << " NoTracks in this event = " << NTracks << endl;
	  
	  if (g2t_trackTablePointer) {
		for (Int_t ii = 0; ii < NTracks; ii++) {
			TrRap->Fill(trackTable[ii].rapidity);
			TrEta->Fill(trackTable[ii].eta);

			if (trackTable[ii].n_pix_hit == 0) {
				NoPix->Fill(trackTable[ii].pt);
			}
		}
	}
	  // Find pixel hits
	  St_g2t_pix_hit *pix_hit = (St_g2t_pix_hit *) chain->FindObject("g2t_pix_hit");
	  if(!pix_hit) cerr << "no g2t_pix_hit collection" << endl;	
	  if( pix_hit)  
	    { 
	      //cout << " found St_g2t_pix_hit" << endl;
	      g2t_pix_hit_st *pixhit = pix_hit->GetTable();
	      
	      printf("=====> In HFT........\n");
	      //cout<< " test HFT , # of hits : " <<pix_hit->GetNRows()<<endl;
	      
	      for (Int_t j = 0; j < pix_hit->GetNRows(); j++) 
		{


		int sensorId=0;
	        UChar_t sector =  pixhit[j].volume_id/1000000;
        	UChar_t ladd =  (pixhit[j].volume_id%1000000)/10000;
	        UChar_t sensor =  (pixhit[j].volume_id - sector*1000000 - ladd*10000)/100;


        	sensorId=(sector-1)*40+(ladd-1)*10+(sensor);
	        TGeoHMatrix *combP=(TGeoHMatrix *)mPxlDb->geoHMatrixSensorOnGlobal(sector,ladd,sensor);
        	if(!combP)cout << "Cannot laod TGeoHMatrix for sensorId: "<< sensorId << endl;
	        Double_t globalPixHitPos[3] = {0, 0, 0};
        	Double_t localPixHitPos[3] = {pixhit[j].x[0],pixhit[j].x[1],pixhit[j].x[2]};
	        combP->LocalToMaster(localPixHitPos, globalPixHitPos);

		//cout << "Position: (" << globalPixHitPos[0] << "," << globalPixHitPos[1] << "," << globalPixHitPos[2] << ")" << endl;

                xLoc[imc] = localPixHitPos[0];
                yLoc[imc] = localPixHitPos[1];
                zLoc[imc] = localPixHitPos[2];

	        x[imc] = globalPixHitPos[0];
	        y[imc] = globalPixHitPos[1];
		z[imc] =globalPixHitPos[2];

		px[imc] = pixhit[j].p[0];
		py[imc] = pixhit[j].p[1];
		pz[imc] = pixhit[j].p[2];

		de[imc] = pixhit[j].de;
		ds[imc] = pixhit[j].ds;

		key[imc] = trackTable[pixhit[j].track_p-1].id;
		vid[imc] = pixhit[j].volume_id;

		Int_t ladder  = (pixhit[j].volume_id%1000000)/10000;
		layer[imc] = (ladder == 1) ? 1 : 2;
		
		 imc++;
		}
	    }
	}
      nhits=imc;
      mctree->Fill();
    }
  outFile->Write();
}

