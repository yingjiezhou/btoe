{
   int pur_dir = 111113;
   char file_purity[50];
   sprintf(file_purity,"../FitPurity/%i/yields.dat",pur_dir);
      ifstream purData(file_purity);
       if(purData.is_open()){
     while(!purData.eof()){
       char out[50];
       double y=0;
       double y_e=0;
       double pT=0;
       double p1 = 0;
       double eff=0;
       double a1 = 0;
       double a2 = 0;
       //double a3 = 0; // zyj add, for new purity cal
       //purData >> pT >> y >> y_e >> p1 >> eff >> a1 >> a2 >>a3;
       purData >> pT >> y >> y_e >> p1 >> eff >> a1 >> a2;
       if(y<.0001)y=0;
       int a=y;
       int b=y_e;
       if(pT!=0){
           cout<<p1<<" is the purity"<<endl;
       }
     }

   } else {
     cout <<"Nope \n";
   }


}
