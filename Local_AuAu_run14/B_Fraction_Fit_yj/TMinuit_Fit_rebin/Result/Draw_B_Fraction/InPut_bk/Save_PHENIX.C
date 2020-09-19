
void Save_PHENIX()
{
  const int Npt=21;
  float pt_bin[Npt+1]={1,1.2,1.4,1.6,1.8,2,2.2,2.4,2.6,2.8,3,3.2,3.4,3.6,3.8,4,4.5,5,6,7,8,9};
  TH1D *PHENIX_AuAu_200=new TH1D("PHENIX_AuAu_200","",Npt,pt_bin);
  TH1D *PHENIX_AuAu_200_up=new TH1D("PHENIX_AuAu_200_up","",Npt,pt_bin);
  TH1D *PHENIX_AuAu_200_down=new TH1D("PHENIX_AuAu_200_down","",Npt,pt_bin);
ifstream file;
  file.open("PHENIX.dat",ios::in);
  TGraphAsymmErrors *gr_PHENIX_AuAu_200=new TGraphAsymmErrors( Npt);
  // file.open("phenixresult.dat",ios::in);
  Double_t a=0,b=0,c=0,d=0,e=0;
  int ipt=0;
  while(!file.eof())
    {
      gr_PHENIX_AuAu_200->SetPoint(ipt,0.5*(a+b),c);
      gr_PHENIX_AuAu_200->SetPointError(ipt,0,0,e,d);
      
      
      file>>a>>b>>c>>d>>e;

      cout<<a<<",";// "  "<<b<<"  "<<c<<endl;
      ipt++;
      PHENIX_AuAu_200->SetBinContent(ipt,c);
      PHENIX_AuAu_200_up->SetBinContent(ipt,d);
      PHENIX_AuAu_200_down->SetBinContent(ipt,e);
      
      // run12MB_sts->SetBinContent(run12MB_sts->FindBin(a),b);
      // run12MB_sts->SetBinError(run12MB_sts->FindBin(a),c);
      
      // run12MB_sys->SetBinContent(run12MB_sts->FindBin(a),b);
      // run12MB_sys->SetBinError(run12MB_sts->FindBin(a),d);
    }

  TH2F *hh=new TH2F("hh","",100,0,10,100,0,1);

  
  

   gr_PHENIX_AuAu_200->SetFillStyle(3001);
  hh->Draw();
  gr_PHENIX_AuAu_200->SetFillColor(2);
  gr_PHENIX_AuAu_200->SetLineColor(2);
  gr_PHENIX_AuAu_200->Draw("a3same");
  PHENIX_AuAu_200->SetLineColor(2);
  PHENIX_AuAu_200->SetLineWidth(3);;
  PHENIX_AuAu_200->Draw("sameL");;

  TFile *File=new TFile("PHENIX.root","RECREATE");
  PHENIX_AuAu_200->Write();
  PHENIX_AuAu_200_up->Write();
  PHENIX_AuAu_200_down->Write();
  gr_PHENIX_AuAu_200->Write();
  File->Close();
  
  
}
