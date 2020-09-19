# Measurements of open bottom and charm hadron production in Au+Au collisions at STAR experiment

###### In this analysis, the primary goal is to measure the open bottom and charm production in in Au+Au collisions, which is studied by the measurement the electrons from the open heavy flavor hadrons via semi-leptonic decays. This is the fist time at STAR measured the charm andbottom quark production separately in heavy-ion collisions by the track impact parameter method.

#### The details can be found in the [Ph.D thesis chapter 4. ](https://drupal.star.bnl.gov/STAR/files/PhDthesis_0.pdf).

## How to run the analysis
---------------------------
### 1. Produce the heavy flavor decay electron DCA template from data daiven fast simulation.
```
cd FastSim
starver SL16d
source setup.csh
cons.csh
./run_EvtGenDecay.csh  %% To run the EvtGen Production and saved the intrestiong variable in the tree
./runAna.csh	       %% Analysis the produce tree      
```
### 2. Photonic electron background DCA can be produced by the Hijing+Geant4 full detector simulation. 
#### 2.1 Produce the Hijing and Geant sample
```
cd PhotonicElectronSim/Pico_mc
starver SL16d	
cons
./submit_full.sh start#  #nRuns  
```
#### Notes 
submit the job to make the mass production, it will be spend 3-4h per job, the full production can be found at /star/u/kunsu/auau200GeVRun14/simulation_RealDetector_RealParticle_SL16d_Pixelisation/files_full/* 

#### 2.2 Saved all the intrestiong variable in the analysis tree based on the produced PicoTree.
```
cd PhotonicElectronSim/Ana_mc
starver SL16d
 cons  
./run_Test.sh  %% To run a few test files.
star-submit submit.xml
```
#### Notes
 submit the job to analysis the full production, clean all the output directory before submit the job.
#### 2.3 Analysis the McPico tree. fill the histogram
```        
cd /PhotonicElectronSim/Histogram_mc
starver SL16d
cons
./run_test.sh %%to run a few test files 
 star-submit submit.xml 
```
submit.xml is submit the job to analysis the full production, clean all the output directory before submit the job.  
 ### 3. Hadron background extracted from data.
#### The code can be found at https://github.com/XiaozhiBai/Run14_PicoReader. Notes, we Saved only the laptons candidate in the analysis tree on the RCF, so the hadron background templte and purity study are still based on the PicoDst, which is on the PDSF.
```       
cd /global/homes/x/xiao00/pwg_disk/AuAu14/Run14_PicoReader
starver SL16d
cons
cd Submit_Job
./submitAnaTreePDSF.sh mb 0 107 167 %% submit the job from day 107 to 167
cd ../Merge_files 
./run_hadd.sh 0 100   %% submit the job to merge the root files.
```
### 4. Inclusive electron and Photonic electron pair reconstructed from data.
```
 cd Data
 starver SL16d
 cons	  
 ./runTest.sh %% To run the Analysis tree, saved the Inclusive electron and Photonic electron pairs.
 cd submit    %% Directory for the job submission.
 star-submit submit_16d.xml
 ./hadd.sh  0 production temp 20 %% Merge the output as a single file for the analysis  
```
#### Notes 
 Please notes, the default input file list is Minimum-Bias Trigger, for the BEMC trigger, you must replace the file list from Ana_mb_16d.list to Ana_ht_16d.list 
  
## How to run the macros in the user's local computer
#### Down load the Analysis_Macros directory into the local machine from this repo. or scp from RCF  /star/u/xiao00/Run14_Analysis/Analysis_Macros
  
--------------------------------------------------------------------------

### 1. Produce the heavy flavor decay electron DCA template from data daiven fast simulation.
The different heavy flavor  electrons DCA Vs pT histogram was produced from RCF, which is described in the previous, then one need to projection the DCA in the different pT intervals, and combined charm and bottom electrons as two individual component. The measued NPE are those electrons that  dominated by the semi-leptonic decays of open heavy flavor D- and B-mesons. Since the EvtGen has many benefits to make the heavy flavor study, particular for B physics. In this simulation, the D- and B-meson (D0,D+,Ds,Lc,B0,B+) are inclueded, but the preliminary results are with out Ds and Lc. The input heavy flavor hadron pT spectrum for B mesons are  from the FONLL calculations, while the D-mesons pT spectra was from measurement, the rapidty distribution was from Pythia. The default decay table was used in the simulation, so you don't need to scale the D- and B-mesons decay electrons brach ratios, sine  all the decay channel (both simi-leptonic and hadronic) are switched on, and the decay branch ratio is kept as default, so only fragmentation-fraction should be take into account during the total charm and  and bottom decay electrons normalization and combination. The fragmentation fraction for different charm mesons are from pp for the prelimenary results, but the current results was from Au+Au 200 GeV data measurement for D0, scaled D0 by pp fragmentation-fraction into D+, Ds from data, Lc rely on the Model calculations and data measurementd. The total charm decayed electron is combined from the electrons from D0,D+.Ds,(take the difference between with and without Lc as one of the  the systematic uncertainty source), for the B-mesons decay electrons, we used 50% as the scale factor for the B0 and B+ evergare which can be found form PDG. 

### Run the code 
```
cd Template_EvtGen_Fastsim
root -l Charm_Bottom_Decay_electrons_EvtGen.C  
```
### Please Note,
 There is a flag in the code,(bool Lc_Flag=true) true means including Lc, one can switch it off to exclude the Lc contribution.

### 2. Photonic electron background DCA can be produced by the Hijing+Geant4 full detector simulation.
The photonic electrons from gamma conversions in the detector materials and $\pi0$ and $\eta$ mesons Dalitz decays. The photonic electron was reconstructed by the photonic pairs via $e^{+}e^{-}$ invariant mass and pair DCA method. We applied the ee pair mass < 0.06 GeV, ee pair dca <$ 0.6 cm) for the pair selection. There is no HFT embedding, we used Hijing+Geant simulation to extarct the DCA distribution from the photonic electrons. The simulation method is We input additional 500 photons,100 neutral pions and 100 eta mesons injected per Hijing event with flat pT , the Hijing event was reconstructed by the Geant with STAR full detector geometry, the reconstruction chain are same with data production, and same STAR software library SL16d. in order to reproduce the data, there are a few more effect was take into account in the Hijing simulation setup which is listed in the below lines. most of the this effects are extracted from data.

### Run the  code
```
cd Template_Photonic_Electron
root -l -b -q Correct_hijing_and_data.C
```  

### Notes:
#### The Flag "add_HT_trigger=true", the default is included the HT trigger from data, if you intrested in the MB trigger only, just switch the the flag from true to false.  
#### Here is the main input root files, 
- "Input/hist_MB_20170920.root" is the data from MB trigger,
- "Input/hist_ht_20170921.root" is the data from HT trigger,
- "Input/hijing_20170920.root" is hijing+geant simulation,
- "Phe_relative_combine_1_30.root" is relative contribution from different photonic electrons source. 
#### The output  root files
- "Data_inclusive_photonic.root" which contains the inclusive electrons from data, 
- "Photonic_electron_template.root" for the photonic electron template from Hijing+Geant Simulation.   

### 3. Hadron background extracted from data.
The mis-identified hadrons DCAXY template extracted from data. we applied the track quality cuts but withoutany particles identification cuts for the inclusive hadron sample, which include the π, kaon and protons. The  individual hadron template from pi, kaon, proton from TPC dE/dx selection.  
### Run the code 
```
cd Template_Hadron
root -l Hadron_Dca_from_pico.C
```
### Please Note
 There are  four flag in the code, Bool_t Hadron_from_pi=true; Bool_t Hadron_from_kaon=false; //default Bool_t Hadron_from_proton=false;  Bool_t Hadron_from_hadron=false; this is the default
 setup, The pi DCA used as the hadron template, if you want to switch to the other hadron template, just switch off the pi, and switch on the other particles flag.     

### 4. Fraction fit to the data inclusive electrons based on the template
The Minut is one of important package which acts on a multi-parameter which was developed by Fortran. however, it has been implemented into the ROOT with a C++ interface, User can define the chi-square function FCN is defined via the MINUIT SetFCN member function. It is the task of MINUIT to find those values of the parameters which give the lowest value of chis-quare。

### Run the code 
```
cd B_Fraction_Fit/TMinuit_Fit
root -l -b -q B_fit_Minuit.C 
cd Draw_Result
root -l -b -q Draw_B_fraction.C
```
### Please Note
- Before you start the templa fit, Make sure you have all the template ready, we well as the inclusive electron from data. put those root file under Input/ 
- There is one flag for the DCA_XY and DCA_Z fraction fit, 'const int IHIST=0' for DCA_XY fit, 'const int IHIST=1' for DCA_Z fit。
- Currently the hadron fraction is higher than expected, the reason is still unclear, might be the Jpsi constribution.
- Tere is a litle bump around the DCA_Z ~ -0.02 cm, the reason need to be checked, apply vertex X and Y, one can skip the little bump via switch on/off the skip_Little_bump_with_DCAZ in the fit macros.  
   

