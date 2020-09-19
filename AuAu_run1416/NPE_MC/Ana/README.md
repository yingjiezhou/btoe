- weights.C // 就是拿到数据，进行拟合，然后与gen 进行比值，得到weight， 里面没有进行gamma/pi 的求ratio, 产生的不是new weight
- runGen.C  // 这个里面是产生newWeight.root，其实有了这个就不需要weights.C， 这里会同时存weight 和 new weight 的结果
  - new weight: 是weight 的一种近似，wiehgt 是用母粒子的pt 作为weight，这样会导致weight 之后统计量减少； new weight 是用weight 对decay e 进行weight，这样得到的weight 
  - 这里面虽然说是用到了root/Pi0_Gamma_Ratio.root， 但其实他没有用，而是自己又重新产生了older weight
- plot_newWeight.C // 这个是拿weights.C 产生的Pi0_Gamma_Ratio.root 里面存的weight，对gen 进行weight 之后，与data 进行对比。并且找出合适的iso cut（根据画出来的分布），得到不同中心度下的iso eff；同时对比data 与weight(包括mass的比值)； 得到PHE 各个分量的fraction；
// save plot in plot_yj/
- DCA_Plots.C // save plots in plots_yj/, 也是拿newWeight.root 里面的root file
// 存了一些iso eff as a funtion of Vz, eta, dca ..
// 也有b fraction
