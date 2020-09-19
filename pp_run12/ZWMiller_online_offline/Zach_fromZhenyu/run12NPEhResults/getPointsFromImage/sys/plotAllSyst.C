void plotAllSyst(){
  ifstream data_rec("rec.txt");
  ifstream data_pur("purity.txt");
  ifstream data_pil("pileup.txt");
  ifstream data_fit("fit.txt");
  
  ofstream outfile;
  outfile.open("yjplotPoints.txt");
  float rec[11], pur[11], pil[11], fit[11];
  if(data_rec.is_open()){
    int i=0;
    while(!data_rec.eof()){
      double tmp;
      data_rec >> tmp;
      rec[i]=tmp;
      //cout<<i<<"dffffffffffff"<<rec[i]<<endl;
      i++;
    }
  }
  if(data_pur.is_open()){
    int i=0;
    while(!data_pur.eof()){
      double tmp;
      data_pur >> tmp;
      pur[i]=tmp;
      i++;
    }
  }
  if(data_pil.is_open()){
    int i=0;
    while(!data_pil.eof()){
      double tmp;
      data_pil >> tmp;
      pil[i]=tmp;
      i++;
    }
  }
  if(data_fit.is_open()){
    int i=0;
    while(!data_fit.eof()){
      double tmp;
      data_fit >> tmp;
      fit[i]=tmp;
      i++;
    }
  }
  
  float x1, x2, x3, x4, x5, x6;
  float pT[9], Rb[9], dyU[9], dyD[9], dysU[9], dysD[9];
  //float pT[11], Rb[11];
  //float dysU[11], dysD[11];
  string line;
  ifstream infile("../plotPoints.txt");
  if(infile.is_open()){
    int i=0;
    while(getline(infile,line))
    {
      sscanf(line.c_str(),"%f %f %f %f %f %f",&x1, &x2, &x3, &x4, &x5, &x6);
      pT[i] = x1;
      Rb[i] = x2;
      dyU[i] = x3;
      dyD[i] = x4;
      //dysU[i] = x5-x2;
      //dysD[i] = x2-x6;
      //cout<<i<<"adfffffffffffffffffff"<<x1<<endl;
      i++;
    }
  }
  
  double err[9];
  for(int i=0; i<9; i++){
    err[i] = 0;
    dysU[i] = 0;
    err[i] += (rec[i]*rec[i] + pur[i]*pur[i] + pil[i]*pil[i] + fit[i]*fit[i]);
    err[i] = sqrt(err[i]);
    //cout<<err[i]*0.01<<" is the error  iiiiiiiiiii"<<endl;
    dysU[i] = Rb[i] + err[i]*0.01*Rb[i];
    dysD[i] = Rb[i] - err[i]*0.01*Rb[i];
    cout<< dysU[i] << "   " << dysD[i]<<endl;
  }
  for(int i=0; i<9; i++){
    outfile<<pT[i]<<" "<<Rb[i]<<" "<<dyU[i]<<" "<<dyD[i]<<" "<<dysU[i]<<" "<<dysD[i]<<endl;
  }
  outfile.close();
  
  
  return ;
}
