const int nJpsiPt = 7;
const int nHadPt = 4;

TH1F *hSdPhi_pjpsi[nJpsiPt][nHadPt];
TH1F *hSdPhi_btojpsi[nJpsiPt][nHadPt];
TH1F *hSdPhiLike[nJpsiPt][nHadPt];
TH1F *hdPhi_zb[3];

int curPnti;
int curPntj;

void plot_test3(int pidType = 2, int trgId = 5, char *tag=""){

    int htId = trgId%3;
    gROOT->LoadMacro("~/rootinit.C");
    rootinit();
    gStyle->SetOptFit(1);
    gROOT->LoadMacro("~/funcUtil.C");
    gStyle->SetEndErrorSize(4);

    TFile *fin;
    fin = new TFile(Form("out/jpsi_h_dphiCor_ht%d_trg%d_%dTrkPid.root",htId,trgId,pidType));
    for(int i=0;i<nJpsiPt-1;i++){
        for(int j=0;j<nHadPt-1;j++){
            hSdPhi_pjpsi[i][j] = (TH1F*)fin->Get(Form("hSdPhi_pjpsi_%d_%d",i,j));
            hSdPhi_btojpsi[i][j] = (TH1F*)fin->Get(Form("hSdPhi_btojpsi_%d_%d",i,j));
            hSdPhiLike[i][j] = (TH1F*)fin->Get(Form("hSdPhiLike_%d_%d",i,j));
        }
    }

    ifstream inf("txt/zb_jpsi-h_4-6GeV.txt");
    const int nDphiBins = 20;
    double dphi_zb[3][nDphiBins],dphiErr_zb[3][nDphiBins],yield_zb[3][nDphiBins],yieldErr_zb[3][nDphiBins];
    double dphiWid = 2.*TMath::Pi()/nDphiBins;
    for(int i=0;i<nDphiBins;i++){
        inf>>dphi_zb[0][i]>>yield_zb[0][i]>>yieldErr_zb[0][i];
        double tmp = dphi_zb[0][i];
        dphi_zb[0][i] = -0.5*TMath::Pi()+(i+0.5)*dphiWid;
        dphiErr_zb[0][i] = dphiWid/2.;
    }
    inf.close();
    inf.open("txt/zb_jpsi-h_6-8GeV.txt");
    for(int i=0;i<nDphiBins;i++){
        inf>>dphi_zb[1][i]>>yield_zb[1][i]>>yieldErr_zb[1][i];
        dphi_zb[1][i] = -0.5*TMath::Pi()+(i+0.5)*dphiWid;
        dphiErr_zb[1][i] = dphiWid/2.;
    }
    inf.close();
    inf.open("txt/zb_jpsi-h_8-12GeV.txt");
    for(int i=0;i<nDphiBins;i++){
        inf>>dphi_zb[2][i]>>yield_zb[2][i]>>yieldErr_zb[2][i];
        dphi_zb[2][i] = -0.5*TMath::Pi()+(i+0.5)*dphiWid;
        dphiErr_zb[2][i] = dphiWid/2.;
    }
    inf.close();

    TGraphErrors *gdPhi_zb[3];
    double sumdPhi_zb[3]={0,0,0};
    for(int i=0;i<3;i++){
        gdPhi_zb[i] = new TGraphErrors(nDphiBins,dphi_zb[i],yield_zb[i],dphiErr_zb[i],yieldErr_zb[i]);
        formatGraph(gdPhi_zb[i],29,2,2,2,1,2);
        gdPhi_zb[i]->SetName(Form("gdPhi_zb_%d",i));
        for(int j=0;j<nDphiBins;j++) sumdPhi_zb[i] += yield_zb[i][j];
    }

    for(int i=0;i<3;i++){
        hdPhi_zb[i] = graphToHistogram(gdPhi_zb[i]);
        formatHist(hdPhi_zb[i],29,2,2,2,1,2);
    }

    double ptJpsi[nJpsiPt] = {0,2,4,6,8,12,15};
    double ptHadLow[nHadPt] = {0.2,0.5,1.0,1.5}; // lower limit of hadron pT.
    TCanvas *c1 = new TCanvas("c1","c1");

    TH1F *htest = new TH1F("htest","htest",20,-TMath::Pi()/2.,TMath::Pi()*3/2.);
    TH1F *htest1 = new TH1F("htest1","htest1",20,-TMath::Pi()/2.,TMath::Pi()*3/2.);
    TF1 *f1 = new TF1("f1","cos(x)",-TMath::Pi()/2.,TMath::Pi()*3/2.);
    for(int i=0;i<100000;i++){
        htest->Fill(gRandom->Uniform(-TMath::Pi()/2.,TMath::Pi()*3/2.));
        htest1->Fill(f1->GetRandom());
    }
    htest->Scale(1./10000);
    htest1->Scale(1./10000);

    int nMReb = 6;
    double frac[nHadPt][nJpsiPt];
    double fracErr[nHadPt][nJpsiPt];
    double ptCen[nJpsiPt];
    double ptCenErr[nJpsiPt];
    double frac_zb[3];
    double fracErr_zb[3];
    //for(int i=0;i<nJpsiPt-1;i++)
    for(int i=2;i<3;i++){
        curPnti = i;
        double ptMin = ptJpsi[i];
        double ptMax = ptJpsi[i+1];
        ptCen[i] = (ptMax+ptMin)/2.;
        ptCenErr[i] = (ptMax-ptMin)/2.;
        cout<<"ptMin = "<<ptMin<<" ptMax = "<<ptMax<<endl;
        //for(int j=0;j<nHadPt;j++)
        for(int j=0;j<1;j++){
            curPntj = j;
            double frac_btojpsi = 0.;
            double fracErr_btojpsi = 0.;
            double frac_pjpsi = 0.;
            double fracErr_pjpsi = 0.;
            cout<<"had pT = "<<ptHadLow[j]<<endl;

            // +--------------------------+
            // | run MINUIT               |
            // +--------------------------+
            TMinuit *gMinuit=new TMinuit(1); //initialize TMinuit with a maximum of 3 params
            gMinuit->SetMaxIterations(50000);
            gMinuit->SetFCN(chi2);
            gMinuit->SetErrorDef(1);

            double arglist[10];int ierflg=0;
            //set err definition to 1-sigma
            //arglist[0]=4; //was to get 2 sigma 
            arglist[0]=1; //error definition: chi^2 change by 1 to get 1 sigma
            gMinuit->mnexcm("SET ERR",arglist,1,ierflg);

            //starting values
            double vstart[2]={0.1,0.7}; //frac
            double step[2]={0.01,0.01}; //starting step
            gMinuit->mnparm(0,"B#rightarrowJ/#psi frac",vstart[0],step[0],0.000,2,ierflg);
            //gMinuit->mnparm(1,"prompt J/#psi frac",vstart[1],step[1],0.000,2,ierflg);
            //if(fix_n){
            //    gMinuit->FixParameter(0);
            //    //    gMinuit->FixParameter(1);
            //    //    gMinuit->FixParameter(2);
            //}

            //simple scan to get better start values
            gMinuit->mnexcm("SCAN",arglist,0,ierflg); 
            cout<<"done with first scan!"<<endl;
            //minimization
            arglist[0]=5000; //maxcalls
            arglist[1]=0.5; // tolerance = 0.001*[this value]*[error def] //5.0 before
            //gMinuit->mnexcm("MIGRAD",arglist,1,ierflg); 
            gMinuit->mnexcm("MINIMIZE",arglist,1,ierflg); 
            //error analysis
            //gMinuit->mnexcm("MINOS",arglist,1,ierflg);
            //gMinuit->mnexcm("MINOS",arglist,1,ierflg);

            cout<<"done with fit!"<<endl;
            //fit results
            double dum1,dum2;
            TString *str0 = new TString("B#rightarrowJ/#psi frac");
            TString *str1 = new TString("prompt J/#psi frac");
            gMinuit->mnpout(0,*str0,frac_btojpsi,fracErr_btojpsi,dum1,dum2,ierflg);
            gMinuit->mnpout(0,*str1,frac_pjpsi,fracErr_pjpsi,dum1,dum2,ierflg);

            //get variance/errors
            TGraph *contFrac_1sigma;
            TGraph *contFrac_2sigma;

            /*
               cout<<"Getting contour..."<<endl;
               int getCont=1;
               const unsigned int NPoints=20;
               if(gMinuit->GetStatus()!=0) {
               getCont=0;
               cout<<endl<<endl<<" Could not get nPoints on contour!!!"<<endl;
               } else {
               cout<<" 1 sigma contour..."<<endl;
               cout<<" == T vs. Beta ==="<<endl;
               gMinuit->SetErrorDef(1);
               contFrac_1sigma = (TGraph*) gMinuit->Contour(NPoints,0,1);
               contFrac_1sigma->SetName("contFrac_1sigma");
               gMinuit->SetErrorDef(2);
               contFrac_2sigma = (TGraph*) gMinuit->Contour(NPoints,0,1);
               contFrac_2sigma->SetName("contFrac_2sigma");
               }

               contFrac_1sigma->Draw("alp");
               contFrac_2sigma->SetMarkerColor(2);
               contFrac_2sigma->Draw("lpsame");
             */

            /*
            //get variance/errors
            printf("Getting contour...\n");
            int np1=0,np2=1;
            TGraph *tG=(TGraph*)gMinuit->Contour(NPoints,np1,np2);tG->SetName("tG");
            int getCont=1;
            if (gMinuit->GetStatus()!=0){
            getCont=0;
            printf("\n\n  could not get nPoints on contour!!!\n\n");
            }
            else{
            gMinuit->SetErrorDef(1);
            TGraph *tC1=(TGraph*)gMinuit->Contour(NPoints,np1,np2);
            tC1->SetName("tC1");tC1->SetTitle("tC1");
            gMinuit->SetErrorDef(2);
            TGraph *tC2=(TGraph*)gMinuit->Contour(NPoints,np1,np2);
            tC2->SetName("tC2");tC2->SetTitle("tC2");
            TGraph *tC12=new TGraph();
            tC12->SetName("tC12");tC12->SetTitle("tC12");
            TGraph *tC22=new TGraph();
            tC22->SetName("tC22");tC22->SetTitle("tC22");
            for(int n=0;n<NPart;n++){// get Mean 
            //if(nBins[n]<=0)continue;
            for(int i=1;i<=hTemp->GetNbinsX();i++){
            double val=hTemp->GetBinCenter(i);
            hTemp->SetBinContent(i,getYield(mBeta,mTfo,mN,val,m0[n]));
            }
            for(int k=0;k<nBins[n];k++){
            if(!opt){
            double val=x[n][k];
            f[n][k]=getYield(mBeta,mTfo,mN,val,m0[n]);
            }
            else f[n][k]=getIntegratedYield(mBeta,mTfo,mN,m0[n],x1[n][k],x2[n][k]);
            }
            hTemp->Scale(getAmplitudeOld(n));
            getdNdy(n,1);

            for (int j=0; j<NPoints; j++){
            double tx,ty;
            tG->GetPoint(j,tx,ty);
            for (int k=0; k<nBins[n]; k++){
            if (opt == 0){
            double val = x[n][k];
            f[n][k]=getYield(tx,ty,mN,val,m0[n]);
            }
            else f[n][k]=getIntegratedYield(tx,ty,mN,m0[n],x1[n][k],x2[n][k]);
            }
            for(int i=1;i<=hTemp->GetNbinsX();i++){
            double val=hTemp->GetBinCenter(i);
            hTemp->SetBinContent(i,getYield(tx,ty,mN,val,m0[n]));
            }
            hTemp->Scale(getAmplitudeOld(n));
            getdNdy(n,0);
            if(fabs(dNdyFitSave-dNdyFit[n])>edNdyFit[n])edNdyFit[n]=fabs(dNdyFitSave-dNdyFit[n]);
            if(fabs(meanPtSave-meanPt[n])>emeanPt[n])emeanPt[n]=fabs(meanPtSave-meanPt[n]);
            tC1->GetPoint(j,tx,ty);
            tC12->SetPoint(j,tx*(2./(2+mN)),ty);
            tC2->GetPoint(j,tx,ty);
            tC22->SetPoint(j,tx*(2./(2+mN)),ty);
            }
            //getdNdy(n,0);
            }
            }
            delete gMinuit;
             */
            //Print results
            double amin,edm,errdef;
            int nvpar,nparx,icstat;
            gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
            gMinuit->mnprin(4,amin);

            float frac2 = 0.14;
            //float frac2 = frac_btojpsi;
            float frac1 = 1- frac2;

            hSdPhiLike[i][j]->Draw();
            //if(i-2>=0) hdPhi_zb[i-2]->Draw("psame");
            //hSdPhi_pjpsi[i][j]->Draw("psame");
            //hSdPhi_btojpsi[i][j]->Draw("pe1same");

            TH1D *hSdPhi_pjpsi_cl = (TH1D*)hSdPhi_pjpsi[i][j]->Clone();
            TH1D *hSdPhi_btojpsi_cl = (TH1D*)hSdPhi_btojpsi[i][j]->Clone();
            hSdPhi_pjpsi_cl->Scale(frac1);
            hSdPhi_btojpsi_cl->Scale(frac2);
            hSdPhi_pjpsi_cl->DrawClone("histsame");
            hSdPhi_btojpsi_cl->DrawClone("histsame");

            TH1D *hSdPhi_incjpsi_cl = (TH1D*)hSdPhi_pjpsi_cl->Clone();
            hSdPhi_incjpsi_cl->Add(hSdPhi_btojpsi_cl);
            formatHist(hSdPhi_incjpsi_cl,20,1,1,1,1,2);
            hSdPhi_incjpsi_cl->DrawClone("histsame");
        }
    }
}

void chi2(Int_t &npar,Double_t *gin,Double_t &func,Double_t *par,Int_t iflag){
    int   i = curPnti;
    int   j = curPntj;

    if(!hSdPhi_pjpsi[i][j] || !hSdPhi_btojpsi[i][j]){cout<<"no template!"<<endl; return 0;}
    if(hSdPhi_pjpsi[i][j]->GetNbinsX()!=hSdPhi_btojpsi[i][j]->GetNbinsX()){
        cout<<"Warning: unequal bins! bin1 = "<<hSdPhi_pjpsi[i][j]->GetNbinsX()<<" bin2 = "<<btojpsi[i][j]->GetNbinsX()<<endl;
        return 0;
    }

    double chiSq = 0.;
    int nDof = 0; 
    for(int k=0;k<hSdPhi_pjpsi[i][j]->GetNbinsX();k++){
        double y1 = hSdPhi_pjpsi[i][j]->GetBinContent(k+1);
        double y2 = hSdPhi_btojpsi[i][j]->GetBinContent(k+1);
        double y0 = hSdPhiLike[i][j]->GetBinContent(k+1);
        double ey0 = hSdPhiLike[i][j]->GetBinError(k+1);
        //double y0 = hdPhi_zb[i-2]->GetBinContent(k+1);
        //double ey0 = hdPhi_zb[i-2]->GetBinError(k+1);

        double ycomb = par[0]*y2+y1*(1.-par[0]); // 
        //double ycomb = par[0]*y2+y1*par[1]; // 
        double delta = (ycomb-y0)/ey0;
        
        chiSq += delta*delta;
        nDof++;

        /*
        double xlo = 0.;
        double xhi = 0.;
        int bin1 = 0;
        int bin2 = 0;
        if(hSdPhi_pjpsi[i][j]->GetBinCenter(bin)>x[0]){
            bin1 = bin-1;
            bin2 = bin;
        }else{
            bin1 = bin;
            bin2 = bin+1;
        }

        double xlo = hSdPhi_pjpsi[i][j]->GetBinCenter(bin1);
        double xhi = hSdPhi_pjpsi[i][j]->GetBinCenter(bin2);
        double a1 = hSdPhi_pjpsi[i][j]->GetBinContent(bin1);
        double a2 = hSdPhi_pjpsi[i][j]->GetBinContent(bin2);
        double p0 = (a1-a2)/(xlo-xhi);
        double p1 = (a2*xlo-a1*xhi)/(xlo-xhi);
        double y1 = p0*x[0]+p1;

        double b1 = hSdPhi_btojpsi[i][j]->GetBinContent(bin1);
        double b2 = hSdPhi_btojpsi[i][j]->GetBinContent(bin2);
        double q0 = (b1-b2)/(xlo-xhi);
        double q1 = (b2*xlo-b1*xhi)/(xlo-xhi);
        double y2 = q0*x[0]+q1;
        //return pars[2]*(y2*pars[3]+y1*(1.-pars[3])); //
        //return pars[2]*y1+y2*pars[3]; //
        double ycomb = pars[0]*y2+y1*(1.-pars[0]); //
        //double ycomb = pars[1]*pars[0]*y2+pars[1]*y1*(1.-pars[0]); //
        double delta = (ycomb-y0)/ey0;
        
        chiSq += delta*delta;
        nDof++;
        */



    }
    func = chiSq;

}

