void Draw_Fig4()
{
  gSystem->Load("libGraphic.so");
  Graphic *Gp = new Graphic();
  Gp->SetPallet(); 
  gStyle->SetOptFit(1);
 
  gSystem->Load("libBracket.so");

 
 // Raa
 
 TGraphErrors *GRaa = new TGraphErrors("STAR_Raa.dat");
 Gp->SetGraphStyles(GRaa,20,1);
 GRaa->SetName("nonp");

 TGraphErrors *GRaa_ch = new TGraphErrors("STAR_Raa_ch.dat");
 Gp->SetGraphStyles(GRaa_ch,25,1);
 GRaa_ch->SetLineColor(1);
 GRaa_ch->SetName("ch");

 TBox *GRaa_ch_Box = new TBox(6,0.205,10,0.254);

 //TGraph *GRaa_th0 = new TGraph("Raa_theory0.dat");
 //TGraph *GRaa_th1 = new TGraph("Raa_theory1.dat");
 
 TGraph *GRaa_th0 = new TGraph("RAA_Dis_up.dat");
 TGraph *GRaa_th1 = new TGraph("RAA_Dis_dw.dat");
 TGraph *GRaa_th2 = new TGraph("RAA_DGVL.dat");
 TGraph *GRaa_th3 = new TGraph("raa-centr-wong-bc.dat");

 GRaa_th0->SetLineStyle(9);
 GRaa_th0->SetLineColor(4);
 GRaa_th0->SetFillColor(1);
 GRaa_th0->SetLineWidth(1.5);
 GRaa_th0->SetName("th0");

 GRaa_th1->SetLineStyle(9);
 GRaa_th1->SetLineColor(4);
 GRaa_th1->SetLineWidth(1.5);
 GRaa_th1->SetName("th1");

 GRaa_th2->SetLineStyle(8);
 GRaa_th2->SetLineColor(2);
 GRaa_th2->SetLineWidth(2);
 GRaa_th2->SetName("th2");

 GRaa_th3->SetLineStyle(1);
 GRaa_th3->SetLineColor(6);
 GRaa_th3->SetLineWidth(2);
 GRaa_th3->SetName("th3");

 // Draw

 TCanvas *c1 = new TCanvas("c1","c1",900,600);

 TPad *c1_1 = new TPad("c1_1", "c1_1",0.02,0.45,0.55,0.99);
 c1_1-> SetBottomMargin(0);
 TPad *c1_1_in = new TPad("c1_1_in", "c1_1_in",0.51,0.1,0.99,0.8);
 TPad *c1_2 = new TPad("c1_2", "c1_2",0.02,0.01,0.55,0.46);
 c1_2-> SetTopMargin(0);
 c1_1->Draw();
 c1_2->Draw();
 c1_1_in->Draw();

 

 // ----------Raa -------------//  L63
 c1_2->cd();
 c1_2->SetLeftMargin(0.15);
 c1_2->SetBottomMargin(0.15);
 TH1D *Gwaku1 = new TH1D("Gwaku1","",99,0,9.9);
 //Gp->SetWaku(Gwaku1,0,2.39,"p_{T} (GeV/c)","R_{AA}");
 //Gp->SetWaku(Gwaku1,0,2.00,"p_{T} (GeV/c)","R_{AA}");
 Gp->SetWaku(Gwaku1,0,1.49,"p_{T} (GeV/c)","R_{AA}");
 Gwaku1->GetYaxis()->SetTitleSize(0.08);
 Gwaku1->GetYaxis()->SetTitleOffset(0.75);
 Gwaku1->GetYaxis()->SetLabelSize(0.08);
 Gwaku1->GetXaxis()->SetTitleSize(0.07);
 Gwaku1->GetXaxis()->SetTitleOffset(0.99);
 Gwaku1->GetXaxis()->SetLabelSize(0.08);
 TAxis *axisY0 = Gwaku1->GetYaxis();
 axisY0->SetNdivisions(508); 
 Gwaku1->Draw();
 GRaa_ch->Draw("P");
 GRaa->Draw("P");
 GRaa_th0->Draw("L");
 GRaa_th1->Draw("L");
 GRaa_th2->Draw("L");
 GRaa_th3->Draw("L");

 TLine *tt = new TLine(0,1,10,1);

 TLegend *leg = new TLegend(0.2,0.6,0.49,0.89);
 leg->SetBorderSize(0);
 leg->SetTextSize(0.06);
 leg->AddEntry(nonp,"data ; non-#gamma e","P");
 leg->AddEntry(ch,"data ; hadron","P");
 leg->AddEntry(th2,"I:DVGL R","L");
 leg->AddEntry(th0,"II:GLV Dis","L");
 leg->AddEntry(th3,"III:Reso","L");
 leg->Draw(); 
 
 TText *tc1_2 = new TText(0.6,1.3,"(b)");
 tc1_2->SetTextSize(0.07);
 tc1_2->Draw(); 

 TText *tc1_Au = new TText(0.6,0.18,"AuAu@200GeV");
 tc1_Au->SetTextSize(0.06);
 tc1_Au->Draw(); 


 //-------------- BD -------------------//  L106
 c1_1->cd();
 c1_1->SetLeftMargin(0.15);

 TH1D *Gwaku = new TH1D("Gwaku","",99,0.0,9.9);
 //Gp->SetWaku(Gwaku,0.001,1.35,"p_{T} (GeV/c)","e_{B}/(e_{B}+e_{D})");
 Gp->SetWaku(Gwaku,0.001,1.059,"p_{T} (GeV/c)","e_{B}/(e_{B}+e_{D})");
 /* 
 Gwaku->GetXaxis()->SetLabelSize(0.05);
 Gwaku->GetXaxis()->SetTitleSize(0.05);
 Gwaku->GetXaxis()->SetTitleOffset(1.0);
 Gwaku->GetYaxis()->SetTitleSize(0.07);
 Gwaku->GetYaxis()->SetTitleOffset(0.6);
 Gwaku->GetYaxis()->SetLabelSize(0.04);
 */
 Gwaku->GetYaxis()->SetTitleSize(0.073);
 Gwaku->GetYaxis()->SetTitleOffset(0.7);
 Gwaku->GetYaxis()->SetLabelSize(0.065);
 Gwaku->GetXaxis()->SetTitleSize(0.06);
 Gwaku->GetXaxis()->SetTitleOffset(0.8);
 Gwaku->GetXaxis()->SetLabelSize(0.06);
 TAxis *axisY1 = Gwaku->GetXaxis();
 axisY1->SetTickLength(0.05);

 Gwaku->Draw();

 TGraph *FONLL[2];
 FONLL[0] = new TGraph("FONLL_BAND_UP.dat");
 FONLL[1] = new TGraph("FONLL_BAND_DW.dat");
 FONLL[0]->SetLineStyle(2);
 FONLL[1]->SetLineStyle(2);
 FONLL[0]->Draw("L");
 FONLL[1]->Draw("L");
 FONLL[1]->SetName("FONLL_BD");

 TGraphErrors *GRB = new TGraphErrors(7);
 TGraphAsymmErrors *GRB_tmp = new TGraphAsymmErrors(7);


 ifstream fin("BD_Run5_Run6.dat");
 //ifstream fin("ttt.dat");
 for(int i=0; i<7; i++)
     {
      double x,y,ex,ey,syd,syu;
      fin >> x >> y >> ey >> syd >> syu; 
      ex = 0.0;
      GRB->SetPoint(i,x,y);
      GRB->SetPointError(i,ex,ey);

      syu = syu - y;
      syd = y - syd;

      GRB_tmp->SetPoint(i,x,y); 
      GRB_tmp->SetPointError(i,ex,ex,syd,syu); 

     } 

  Gp->SetGraphStyles(GRB,20,1);
  GRB->Draw("P");
  GRB->SetName("eh");

  TGraphErrors *Ge_D0 = new TGraphErrors("e_D0.dat");
  TGraphAsymmErrors *Ge_D0_tmp = new TGraphAsymmErrors(1);
  Ge_D0_tmp->SetPoint(0,5.55,0.439); 
  double sysdw_eD0 = 0.1481;
  double sysup_eD0 = 0.1725;

  cout << sysdw_eD0 << " : " << sysup_eD0 << endl;
  
  Ge_D0_tmp->SetPointError(0,0,0,sysdw_eD0,sysup_eD0); // data get from Andre (10/02/08) 


  Gp->SetGraphStyles(Ge_D0,21,1);

  Ge_D0->Draw("P");
  //Ge_D_1->Draw("P");

  Ge_D0->SetName("eD0");

  /* 
  leg0 = new TLegend(0.4,0.5,0.7,0.89);
  leg->SetTextSize(0.1);
  leg0->AddEntry(eh,"data ; e-h (PYTHIA fit)","p");
  leg0->AddEntry(eD0,"data ; e-D (PYTHIA fit)","p");
  leg0->AddEntry(eD1,"data ; e-D (MC@NLO fit)","p");
  leg0->AddEntry(FONLL_BD,"FONLL","L");
  leg0->Draw();
  */

  leg0 = new TLegend(0.4,0.65,0.65,0.89);
  leg0->SetTextSize(0.05);
  leg0->AddEntry(eh,"from  e-h correlation","p");
  leg0->AddEntry(eD0,"from  e-D correlation","p");
  leg0->AddEntry(FONLL_BD,"FONLL","L");
  leg0->Draw();


  TGraphAsymmErrorsBracket *GRB_sys = new TGraphAsymmErrorsBracket(*GRB_tmp);
  GRB_sys->SetBracketSize(5, 5);
  GRB_sys->SetBracketColor(1);
  GRB_sys->Draw("P");

  TGraphAsymmErrorsBracket *Ge_D0_sys = new TGraphAsymmErrorsBracket(*Ge_D0_tmp);
  Ge_D0_sys->SetBracketSize(5, 5);
  Ge_D0_sys->SetBracketColor(1);
  Ge_D0_sys->Draw("P");


  TText *tc1_1 = new TText(0.6,0.9,"(a)");
  tc1_1->SetTextSize(0.065);
  tc1_1->Draw(); 

 TText *tc1_p = new TText(0.6,0.08,"pp@200GeV");
 tc1_p->SetTextSize(0.05);
 tc1_p->Draw(); 

 // RAA cont.
 c1_1_in->cd();
 //c1_1_in->SetBottomMargin(0.15);
 c1_1_in->SetBottomMargin(0.2);
// //c1_1_in->SetLeftMargin(0.25);
 c1_1_in->SetLeftMargin(0.2);
 c1_1_in->SetTopMargin(0.05);
 //TCanvas *c2 = new TCanvas("c2","c2",300,300);
 TFile *file = TFile::Open("RAA_cont_sig2.root");
 
 TAxis *axisX = histGraph->GetXaxis();
 axisX->SetNdivisions(5); 
 TAxis *axisY = histGraph->GetYaxis();
 axisY->SetNdivisions(5); 
 histGraph->GetYaxis()->SetTitleOffset(0.9);
 histGraph->GetXaxis()->SetTitle("R_{AA}^{e_{D}}");
 histGraph->GetYaxis()->SetTitle("R_{AA}^{e_{B}}");
 histGraph->Draw();
 //box_c->Draw();
 //box_b->Draw();
 //light_point->Draw(); 
 light_box->Draw(); 
 //line->SetLineStyle(2);
 //line0->SetLineStyle(2);
 line->Draw();
 line0->Draw();
 Raa_pro->SetLineColor(1);
 //Raa_pro->Draw("same,c");
 contour_sig1_below->SetLineColor(46);
 contour_sig1_above->SetLineColor(46);
 contour_sig1_below->Draw("c");
 contour_sig1_above->Draw("c");

 Raa_pro->SetName("mim");
 contour_sig1_below->SetName("sig2");

 double raac[10],raab[10];
 raac[0] = 0.01;
 raab[0] = contour_sig1_below->Eval(raac[0]); 
 raac[1] = 0.01;
 raab[1] = contour_sig1_above->Eval(raac[1]); 

 for(int j=2; j<8; j++) 
   {
    double xx = (double)j/10.0;
    raac[j] = xx;
    raab[j] = contour_sig1_above->Eval(xx); 
   }

 raac[8] = 0.99;
 raab[8] = contour_sig1_above->Eval(raac[8]); 
 raac[9] = 0.99;
 raab[9] = contour_sig1_below->Eval(raac[9]); 
 
 TGraph *Gcl = new TGraph(10);
 for(int i=0; i<10; i++)Gcl->SetPoint(i,raac[i],raab[i]);
 Gcl->SetFillColor(46);
 Gcl->SetFillStyle(3002);
 Gcl->Draw("F");

 Raa_pro->Draw("same,c");

 light_box->Draw(); 


 // get models
 
 TFile *file2 = TFile::Open("RAA_Ivan.root");
 Raa_Ivan->Draw("cont,same");
 Raa_Ivan->SetName("theo2");

 TFile *file3 = TFile::Open("RAA_Ralf.root");
 Raa_Ralf->Draw("cont,same");
 Raa_Ralf->SetName("res");

 TFile *file4 = TFile::Open("RAA_Rad.root");
 Raa_Rad->Draw("cont,same");;
 Raa_Rad->SetName("rad");


   TLatex *   tex1 = new TLatex(0.34,0.8,"(I)");
   tex1->SetTextSize(0.06);
   tex1->SetLineWidth(2);
   tex1->Draw();

   TLatex *   tex2 = new TLatex(0.15,0.48,"(II)");
   tex2->SetTextSize(0.06);
   tex2->SetLineWidth(2);
   tex2->Draw();

   TLatex *   tex3 = new TLatex(0.43,0.36,"(III)");
   tex3->SetTextSize(0.06);
   tex3->SetLineWidth(2);
   tex3->Draw();


   TLatex *   tex4 = new TLatex(0.18,0.14,"R_{AA}^{u}");
   tex4->SetTextSize(0.05);
   tex4->SetLineWidth(2);
   tex4->Draw();


 TText *tc1_1_in = new TText(0.1,0.9,"(c)");
 tc1_1_in->SetTextSize(0.065);
 tc1_1_in->Draw(); 

 TLegend *leg2 = new TLegend(0.6,0.6,0.89,0.89);
 leg2->SetBorderSize(4);
 leg2->SetTextSize(0.055);
 leg2->AddEntry(sig2,"1-#alpha<90%","L");
 leg2->Draw(); 

}
