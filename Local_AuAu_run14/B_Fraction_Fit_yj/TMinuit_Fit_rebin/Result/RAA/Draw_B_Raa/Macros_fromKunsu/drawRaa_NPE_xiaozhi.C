TLatex* drawLatex(Double_t, Double_t, char* , Int_t , Double_t , Int_t);
char buf[1024];

void drawRaa_NPE_xiaozhi(){
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(5);
  double histMax = 5.9;
  double histMin = 0.14;
  const int Npt=4;
  Float_t ptbin[Npt+1]={2.5,3.5,4.5,5.5,8.5};
  TH1F *  ratio_fit=new TH1F("ration_fit","",Npt,ptbin);
  TLegend *leg0;
  
  // DUKE
  double xDukeB[20] = {0.250E+00, 0.750E+00, 0.125E+01, 0.175E+01, 0.225E+01, 0.275E+01, 0.325E+01, 0.375E+01, 0.425E+01, 0.475E+01, 0.525E+01, 0.575E+01, 0.625E+01, 0.675E+01, 0.725E+01, 0.775E+01, 0.825E+01, 0.875E+01, 0.925E+01, 0.975E+01};
  double yDukeB[20] = {0.952E+00, 0.960E+00, 0.943E+00, 0.964E+00, 0.107E+01, 0.112E+01, 0.109E+01, 0.105E+01, 0.982E+00, 0.897E+00, 0.848E+00, 0.815E+00, 0.759E+00, 0.725E+00, 0.721E+00, 0.683E+00, 0.642E+00, 0.637E+00, 0.623E+00, 0.602E+00};
  TGraph * gDukeBtoE = new TGraph(20,xDukeB,yDukeB);
  double yDukeD[20] = {0.740E+00, 0.803E+00, 0.102E+01, 0.850E+00, 0.692E+00, 0.591E+00, 0.535E+00, 0.474E+00, 0.482E+00, 0.471E+00, 0.461E+00, 0.477E+00, 0.459E+00, 0.464E+00, 0.454E+00, 0.450E+00, 0.423E+00, 0.478E+00, 0.445E+00, 0.439E+00};
  TGraph * gDukeDtoE = new TGraph(20,xDukeB,yDukeD);
  
  gDukeBtoE->SetLineColor(2);
  gDukeBtoE->SetLineStyle(4);
  gDukeBtoE->SetLineWidth(2);
  gDukeDtoE->SetLineColor(4);
  gDukeDtoE->SetLineStyle(4);
  gDukeDtoE->SetLineWidth(2);
  
  // STAR
  TFile * npeXiao = new TFile("Raa_B_D.root","READ");
  TGraphErrors * gNpe = (TGraphErrors*)npeXiao->Get("gr_B_Raa_com_sts");
  TGraphErrors * gNpeSys = (TGraphErrors*)npeXiao->Get("gr_B_Raa_com_sys");
  TGraphErrors * gNpeSys2 = (TGraphErrors*)npeXiao->Get("gr_all_B_Npe_Raa_com_sys");
  TGraphErrors * gNpec = (TGraphErrors*)npeXiao->Get("gr_C_Raa_com_sts");
  TGraphErrors * gNpecSys = (TGraphErrors*)npeXiao->Get("gr_C_Raa_com_sys");
  TGraphErrors * gNpecSys2 = (TGraphErrors*)npeXiao->Get("gr_all_C_Npe_Raa_com_sys");
  
  TGraphErrors  *Graph_from_Fb_to_e_sts=(TGraphErrors *) npeXiao->Get("Graph_from_Fb_to_e_sts"); // double ratio RAA zyj
  TGraphErrors  *Graph_from_Fb_to_e_sys=(TGraphErrors *) npeXiao->Get("Graph_from_Fb_to_e_sys");
  
  gNpe->SetMarkerStyle(21);
  gNpe->SetMarkerColor(2);
  gNpe->SetLineColorAlpha(2,1);
  gNpeSys->SetLineColorAlpha(2,1);
  gNpeSys2->SetLineColorAlpha(1,0.25);
  gNpeSys2->SetLineWidth(6);
  
  gNpec->SetMarkerStyle(21); // set again, why??
  gNpec->SetMarkerColor(4);
  gNpec->SetLineColorAlpha(4,1);
  gNpecSys->SetLineColorAlpha(4,1);
  gNpecSys2->SetLineColorAlpha(1,0.25);
  gNpecSys2->SetLineWidth(6);
  
  gNpe->SetMarkerStyle(20);
  gNpec->SetMarkerStyle(24);
  
  gNpe->SetMarkerSize(2.2);
  gNpec->SetMarkerSize(2.);
  
  gNpe->SetLineWidth(2);
  gNpec->SetLineWidth(2);
  gNpeSys->SetLineWidth(2);
  gNpecSys->SetLineWidth(2);
  gNpeSys->SetMarkerSize(2.2);
  gNpecSys->SetMarkerSize(2.);
  gNpeSys2->SetLineColorAlpha(1,0.2);
  gNpecSys2->SetLineColorAlpha(1,0.2);
  gNpeSys2->SetLineWidth(8);
  gNpecSys2->SetLineWidth(8);
  
  gStyle->SetTitleOffset(0.8,"X");
  gStyle->SetTitleOffset(0.8,"Y");
  
  TLine * line = new TLine(0.1,1,8.49,1);
  line->SetLineStyle(2);
  
  
  // Drawing
  TCanvas * ccFinal = new TCanvas("ccFinal","ccFinal",0,0,600,700);
  ccFinal->cd();
  
  TH1F * hdum = new TH1F("hdum","hdum",100,0.1,8.49);
  hdum->SetMaximum(histMax);
  hdum->SetMinimum(histMin);
  hdum->GetYaxis()->SetTitle("R_{AA}");
  hdum->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hdum->SetFillColorAlpha(1,0.25);
  hdum->SetLineColor(0);
  hdum->GetXaxis()->SetLabelSize(0.055);
  hdum->GetYaxis()->SetLabelSize(0.055);
  
  TPad* pad1 = new TPad("pad1","pad1",0.00,0.3,1.00,1.00);pad1->Draw();
  TPad* pad2 = new TPad("pad2","pad2",0.00,0.00,1.00,0.3);pad2->Draw();
  pad1->SetMargin(0.1,0.02,0,0.02);
  pad2->SetMargin(0.1,0.02,0.4,0.0);
  
  pad1->cd();
  gPad->SetLogy(1);
  //    gPad->SetLogy(0);
  
  hdum->Draw();
  
  gDukeBtoE->Draw("same");
  gDukeDtoE->Draw("same");
  
  gNpeSys2->Draw("samez");
  gNpecSys2->Draw("samez");
  
  gNpeSys->Draw("samep[]");
  gNpecSys->Draw("samep[]");
  
  gNpe->Draw("samepz");
  gNpec->Draw("samepz");
  TBox * globalUncerAuAu_0_80 = new TBox(8.2,1-20.46382/291.90194,8.4,1+20.46382/291.90194);
  globalUncerAuAu_0_80->SetFillColor(42);
  globalUncerAuAu_0_80->Draw("same");
  
  line->Draw("same");
  
  leg0 = new TLegend(0.575,0.66,0.808,0.92);
  leg0->SetFillStyle(0);
  leg0->SetFillColor(0);
  leg0->SetTextSize(0.04);
  leg0->SetHeader("  ");
  leg0->AddEntry(gNpe,"#font[32]{B}#rightarrow#font[32]{e}","p");
  leg0->AddEntry(gNpec,"#font[32]{D}#rightarrow#font[32]{e}","p");
  leg0->AddEntry(gDukeBtoE,"DUKE : #font[32]{B}#rightarrow#font[32]{e}","l");
  leg0->AddEntry(gDukeDtoE,"DUKE : #font[32]{D}#rightarrow#font[32]{e}","l");
  leg0->Draw("same");
  
  TLegend * leg5 = new TLegend(0.12,0.03,0.263,0.082);
  leg5->SetFillStyle(0);
  leg5->SetFillColor(0);
  leg5->SetTextSize(0.033*1.3);
  leg5->SetTextFont(132);
  //   leg5->AddEntry(gNpeSys2,"Au+Au R_{AA} uncertainty","L");
  leg5->AddEntry(gNpeSys2,"R_{AA}^{#font[32]{B+D#rightarrowe}} uncertainty","L"); // means b/c/b+c/c+b??
  leg5->Draw("same");
  
  TLatex latex, latex2;
  latex.SetTextSize(0.045);
  latex.SetTextAlign(13);  //align at top
  latex.SetTextColor(2);
  latex2.SetTextSize(0.045);
  latex2.SetTextAlign(13);  //align at top
  latex2.SetTextFont(22);
  
  latex.DrawLatex(5.2,5,"#font[32]{STAR Preliminary}");
  latex2.DrawLatex(0.5,4.5,"Au+Au #sqrt{s_{NN}} = 200 GeV");
  latex2.DrawLatex(0.5,3.5,"0-80%");
  
  
  pad2->cd();
  
  TH2F *h2=new TH2F("h2","",100,0.1,8.49,2,0.,5);
  h2->GetXaxis()->SetTitle("p_{T}^{e} (GeV/c)");
  h2->GetYaxis()->SetTitle("R_{AA}^{b #rightarrow e} / R_{AA}^{c #rightarrow e}");
  h2->GetYaxis()->CenterTitle();
  h2->Draw();
  
  h2->GetYaxis()->SetNdivisions(4);
  h2->GetXaxis()->SetNdivisions(8);
  h2->GetYaxis()->SetTitleSize(0.09);
  h2->GetXaxis()->SetTitleSize(0.14);
  h2->GetYaxis()->SetTitleOffset(0.35);
  h2->GetXaxis()->SetTitleOffset(1.1);
  Graph_from_Fb_to_e_sts->SetMarkerColor(1);
  Graph_from_Fb_to_e_sts->SetLineColor(1);
  Graph_from_Fb_to_e_sts->SetMarkerStyle(20);
  Graph_from_Fb_to_e_sts->SetMarkerSize(2.);
  Graph_from_Fb_to_e_sts->SetLineWidth(2);
  
  Graph_from_Fb_to_e_sys->SetLineWidth(2);
  Graph_from_Fb_to_e_sys->SetLineColor(1);
  
  
  h2->GetYaxis()->SetLabelSize(0.15);
  h2->GetXaxis()->SetLabelSize(0.15);
  
  TF1 *f1=new TF1("f1","pol0",0,8.5);
  f1->SetLineColor(2);
  f1->SetLineStyle(3);
  
  TF1 *f2=new TF1("f2","pol0",0,8.5);
  f2->SetLineColor(2);
  
  TF1 *f3=new TF1("f3","pol0",0,8.5);
  f2->SetLineColor(2);
  
  
  Graph_from_Fb_to_e_sts->Draw("samezP");
  Graph_from_Fb_to_e_sys->Draw("sameP[]");
  
  
  for(int ipt=0;ipt<Npt;ipt++)
  {
    
    Double_t X=-99,Y=-99;
    //Double_t sts_err=-99,sys_err=-99;
    Double_t   sts_err=Graph_from_Fb_to_e_sts->GetErrorY(ipt);
    Double_t   sys_err=Graph_from_Fb_to_e_sys->GetErrorY(ipt);
    
    Graph_from_Fb_to_e_sts->Draw("samezP");
    Graph_from_Fb_to_e_sts->GetPoint(ipt,X,Y);
    ratio_fit->SetBinContent(ipt+1,Y);
    ratio_fit->SetBinError(ipt+1,sqrt(sts_err*sts_err+sys_err*sys_err));
    cout<<sts_err<<" "<<sys_err<< "  "<< Y<<endl;
  }
  
  ratio_fit->Fit(f1,"R0","",2.5,8);

  //ratio_fit->Print("all");
  
 
  Graph_from_Fb_to_e_sts->Fit(f2,"R0",""); // don't need this I think zyj
  Graph_from_Fb_to_e_sys->Fit(f3,"R0" ,"");
  
  //Graph_from_Fb_to_e_sys->Fit();
  
  f1->Draw("same");
  
  Graph_from_Fb_to_e_sts->Fit(f2,"R0","");
  Graph_from_Fb_to_e_sys->Fit(f3,"R0","");
 
  
  sprintf(buf,"%2.1f #pm %2.1f",f1->GetParameter(0),f1->GetParError(0));
  drawLatex(0.15,0.75,buf,62,0.11,2);
  
  // sprintf(buf,"p0 = %2.1f #pm %2.2f sts.",f2->GetParameter(0),f2->GetParError(0));
  // drawLatex(0.15,0.8,buf,62,0.07,2);
  
  // sprintf(buf,"p0 = %2.1f #pm %2.2f sys.",f3->GetParameter(0),f3->GetParError(0));
  // drawLatex(0.15,0.73,buf,62,0.07,2);
  
  
  
  TLine *l1=new TLine(0.1,1,8.5,1); // to add a new line zyj
  l1->SetLineColor(1);
  l1->SetLineWidth(2.5);
  l1->SetLineStyle(7);
  l1->Draw("same");
  ccFinal->cd(0);
  
  ccFinal->SaveAs("btoeRaaFinal_xiaozhi.pdf");
  
  // TFile *file=new TFile("Raa_B_D.root","READ");
  // TGraphErrors *Graph_from_Fb_to_e_stss=( TGraphErrors *) file->Get("Graph_from_Fb_to_e_sts");
  // Graph_from_Fb_to_e_sts->Draw();
}
TLatex* drawLatex(Double_t x, Double_t y, char* text, Int_t textFont, Double_t textSize, Int_t colorIndex)
{
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
}

