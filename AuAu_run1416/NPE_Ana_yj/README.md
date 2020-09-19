
# main idea
1. First step:(can only run relative samll sample )
- /gpfs01/star/pwg/mkelsey/Run14/StRoot
since we don't have input likelihood dist. root file, comment any piece of code that need weight root file
// i.e. float TMVADec = mNpeCuts->getDLL(track); ----->  float TMVADec = 1; otherwise code will break

generate Ntuple root file **at least** include( used for likelihood tmva "training"):
  - Ks tree  // i.e saved in NPE_Tuples_TuneB10.root
  - PhoE tree
  - we can also use fillMyHistogram()  to get hist used for purity fit(no mva cut)

2. Second step:
- /gpfs01/star/pwg/mkelsey/NPE_ANA
use the tree we got in first step,
do likelihood to get: likelihood dist. for pion(bkg) and e(signal)
see how to do from below


3. Third step:
- /gpfs01/star/pwg/mkelsey/Run14/StRoot
run total run number,
use generated weight root file to get DCA hist w/ suitable MVA cut(hDcaLog3D_xxx, get more pure inc e(iso e) and hadron sample)
can only save hDcaLog3D_xxx hist, no need tree

hDcaLog3D_xxx: mean DCA hist. for different particle

# get pion(from Ks decay) dist.
- NPE_Ana/SPlot/Kshort/makeWeights.C
  - input:
    **NPE_Tuples_TuneB10.root**, Ks tree
  - output:
    out.root (add one more TBranch: sw(weight), compared with Ks tree)

# Likelihood
Likelihood: take PHE(PhoE tree) and bkg tree(Ks tree with signal weight !!), generate weight root file, use weight to get PHE's response distribution(ROC plots, likelihood efficiency for PHE etc.), choose good cut value.
get likelihood efficiency for PHE, used for purity calculation
no need any histo w/ mva cut, because we will not use them

- NPE_Ana/Likelihood/runFit_sWeight.C // generate lieklihood dist.
  - input:
    - signal: **NPE_Tuples_TuneB10.root**, PhoE tree
    - bkg: SPlot/Kshort/out.root, take **Ks_tree_sw** tree

  - output:  // show plots with likelihood dist for diff variable
    - root/weights_electron.root
    - root/weights_pion.root

- doLikelihood() in the same runFit_sWeight.C // do likelihood for PHE, and Ks_tree_sw , use generated lieklihood dist
  - input: 
    - **NPE_Tuples_TuneB10.root**, **PhoE tree**
    - NPE_Ana/SPlot/Kshort/all.root, Ks_tree_sw tree 
    - root/weights_electron.root
    - root/weights_pion.root

  - output:
    - ROC, response hist, likelihood eff etc.
    - NPE_Ana/Likelihood/root/Ks_pion.root (eg: fill hFit_pi_xx  for purity, w/ or w/o mva cut, but we only use the w/o mva cut one, don't need mva)
    
# fit purity
FitPurity: use inc nsigma_e dist(w/o MVA cut), get purity and N_e(number of e, used for purity calculation w/ MVA cut)
- NPE_Ana/FitPurity/runFit.C
  - Input:
    - **NPE_Tuples_TuneB10.root** (get inc, phe nsigma_e dist **w/o mva cut**)
    - NPE_Tuples_TuneB10.root(used for **unweighted pion when pt>7**, because at high-pt stat is small) and Likelihood/root/Ks_pion.root (sWeighted pion nsigma_e dist)
  - output:
    - N_e and purity fit plots
    - also has pion nsigma_e dist. comparsion, w/ and w/o weight

# fit DCA
FitIP:
- NPE_Ana/FitIP/calcPurity.C  // calculate purity, but this calcPurity.C is not for purity calculation, I write the code by myself
  - p = Ne*eff/N*(inc e with MVA cut, taken from hLog3DCA_0)

- NPE_Ana/FitIP/runFit.C // need DCA dist. for each component
  - input:
    - inc e: **NPE_Tuples_TuneB12.root**
    HT: **w/o mva cut** //hDcaLog3D_5
    MB: **w/ mva cut** //hDcaLog3D_1
    - hadron: NPE_Tuples_TuneB12.root
    - phe:/NPE_MC/Ana/root/DCA_plots.root
    - hf: /NPE_MC/Ana/root/HF_plots_LowDp.root
    - purity: number

  - output:
    - plots with finally DCA fit


# Note
auto ch1 = (TChain*)f_D->Get("Signal"); // Signal tree is not used here, no need to save

