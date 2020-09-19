#!/bin/sh
HomeDirectory=/star/u/xiao00/Run14_Analysis/PhotonicElectronSim/Pico_mc

starver SL16d
job=$2
#job=$(($1+$2))
#run=${job: -1}
run=`echo $job | cut -f2 -d"_"`
run=$(($run+$1))
mkdir ./Files_$job
mkdir ./Files_$job/fzd
mkdir ./Files_$job/tpc_reco
mkdir ./Files_$job/hft_reco
mkdir ./Files_$job/pile_up
mkdir ./Files_$job/picodst
mkdir ./Files_$job/tpcRes
# --- Pile up file
at=`perl -e 'srand; print int(rand(99)+1)'`
cp -p /star/institutions/lbl/mlomnitz/mlomnitz_prod/EffStudies/Sti_2015/pileup/pileupSet$at/pile**.root ./Files_$job/pile_up/pile_up$at.root

function doStarSim {
# ---- Producing sim file .fzd
root4star <<EOF
.L starsim.hijing.Lc.C
starsim(4,$run,$RANDOM)
.q
EOF
mv hijing_Lc* ./Files_$job/fzd/.
}

function doTpcReco {
echo "Lomnitz: TPC reco starting"
# ---- TPC reconstruction
inFile=Files_$job/fzd/hijing_Lc_$run.starsim.fzd

chain=y2014a,event,tpc,fzin,geantout,tpcrs,TpcHitMover,TpxClu,evout,-HitFilt

echo $chain

pwd
#env
root4star -b -l <<EOF
.x bfc.C(0,9,"$chain","$inFile");
EOF

mv hijing_Lc* Files_$job/tpc_reco/.
#cp Files_$job/tpc_reco/* $HomeDirectory/files_TPC/
}

function doHftReco {
echo "Lomnitz: HFT Reco starting"
# ---- hft reconstruction
inFile2=$1
inPile=Files_$job/pile_up/pile_up$at.root
#chain2=y2014a,event,McEvent,MuDst,in,sim_T,gen_T,geantout,evout,FieldOn,AgML,usexgeom,MakeEvent,ITTF,Sti,NoSsdIt,NoSvtIt,StiHftC,pxlFastSim,istFastSim,Idst,BAna,l0,Tree,logger,genvtx,tpcDB,bbcSim,btofsim,emcY2,EEfs,evout,-dstout,IdTruth,big,McEvout,MiniMcMk,McAna,ReadAll,clearmem
chain2=y2014a,event,McEvent,MuDst,in,sim_T,gen_T,geantout,evout,FieldOn,AgML,usexgeom,MakeEvent,ITTF,Sti,NoSsdIt,NoSvtIt,StiHftC,pxlFastSim,pxlCluster,pxlHit,istFastSim,Idst,BAna,l0,Tree,logger,genvtx,tpcDB,bbcSim,btofsim,emcY2,EEfs,evout,-dstout,IdTruth,big,McEvout,MiniMcMk,McAna,ReadAll,clearmem
#chain2=y2014a,event,McEvent,MuDst,in,sim_T,gen_T,geantout,evout,FieldOn,usexgeom,MakeEvent,ITTF,Sti,NoSsdIt,NoSvtIt,StiHftC,pxlFastSim,istFastSim,Idst,BAna,l0,Tree,logger,genvtx,tpcDB,bbcSim,btofsim,emcY2,EEfs,evout,-dstout,IdTruth,big,McEvout,MiniMcMk,ReadAll,clearmem

echo $chain2

pwd
#env
root4star -b -l <<EOF
.x bfc.C(-1,"$chain2","$inFile2");
StPxlSimMaker* pxl = chain->GetMaker("pxlSimMaker");
pxl->useIdealGeom(); // ideal geometry
//pxl->useDbGeom();  // survey geometry
pxl->useRandomSeed();
//pxl->setFastSim();
pxl->setFastSimRaw();
pxl->addPileup(); 
pxl->setPileupFile("$inPile");


TString OutputFileName(gSystem->BaseName("$inFile2"));
OutputFileName.ReplaceAll(".event.root",".McAna");
StMcAnalysisMaker* mcAnalysisMaker = (StMcAnalysisMaker*)chain->GetMaker("StMcAnalysisMaker");
mcAnalysisMaker->setOutFileName(OutputFileName);

chain->Init();
chain->EventLoop(0,9);
chain->Finish();

EOF
mv hijing_Lc_$run.tpcRes.root Files_$job/tpcRes/Lc_hijing_sim_production_v0_$job.tpcRes.root
mv *.pxlMon.root $HomeDirectory/files_PxlHits/
mv *.root Files_$job/hft_reco/.
# ---- PicoDst
if [ -s Files_$job/hft_reco/hijing_Lc_$run.MuDst.root ]; then
	root4star -l -b -q makePicoDst.C\($run,\"Files_$job/hft_reco/hijing_Lc_$run.MuDst.root\",\"Files_$job/hft_reco/hijing_Lc_$run.McEvent.root\"\)
	mv *.picoDst.root $HomeDirectory/files_full$3/$job.picoDst.root
	#privilges
	#find . -type f -name "*.picoDst.root" -exec chmod g+rw {} \;
fi

}

#if [ -s $HomeDirectory/files_TPC/hijing_Lc_${run}.event.root  ]; then
#doHftReco $HomeDirectory/files_TPC/hijing_Lc_${run}.event.root 

#else
doStarSim
doTpcReco
doHftReco Files_$job/tpc_reco/hijing_Lc_$run.event.root

#fi

#find Files_$job/ -type d -exec chgrp rhstar {} \;
#find Files_$job/ -type d -exec chmod g+rw {} \;
#find Files_$job/ -type f -exec chgrp rhstar {} \;
#find Files_$job/ -type f -exec chmod g+rw {} \;
# ---- Done bring files back
#tar -cvf Files_$job.tar Files_$job
