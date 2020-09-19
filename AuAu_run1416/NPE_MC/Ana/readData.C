void readData(){
char file[50];
sprintf(file, "/Users/zhouyingjie/Desktop/pi_read_ct.txt");
ifstream fdata(file);
int count=0;
if(fdata.is_open()){
while(!fdata.eof()){
    count++;
double y=0;
       double y_e=0;
       double pT=0;
       double p1 = 0;
       double eff=0;
       double a1 = 0;
       fdata >> pT >> y >> y_e >> p1 >> eff >> a1;
if(pT!=0){
cout<<pT<<", ";
}
}

}
else{
cout <<"Nope \n";
}

cout<<endl;
cout<<"count number is ::::   "<<count<<endl;
return ;
}
