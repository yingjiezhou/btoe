//void prettycanvasAll(TCanvas *c1,RooPlot *Frame, TLegend* leg, RooPlot *Pull, int log)
void prettycanvasAll(TCanvas *c1,RooPlot *Frame, RooPlot *Pull, int log)
{
    TPaveText *Name = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
                            0.75 - gStyle->GetPadTopMargin(),
                            gStyle->GetPadLeftMargin() + 0.31,
                            0.95 - gStyle->GetPadTopMargin(),
                                        "BRNDC");

    Name->AddText("");
    //Name->SetFillColorAlpha(0, 0);
    Name->SetTextAlign(12);
    Name->SetBorderSize(0); 
    TPad *pad1 = new TPad("pad1","pad1",0.0,0.,1.0,1.0);
    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
    TGaxis::SetMaxDigits(3);
    //pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.08);
    pad2->SetTopMargin(0.015);
    pad2->SetBottomMargin(0.5);  
    pad2->SetBorderMode(0);
    pad1->SetBorderMode(0);
    c1->SetBorderMode(0);  
    pad1->Draw();
    //pad2->Draw(); 
    pad1->cd(); 
    Frame->GetYaxis()->SetTitleSize(0.1); 
    Frame->GetYaxis()->SetTitleOffset(0.6);
    Frame->SetTitle(""); 
    Frame->GetXaxis()->SetTitle("n#sigma_{e}");
    Pull->GetXaxis()->SetTitle("n#sigma_{e}"); 
    //Frame->GetXaxis()->SetTitleSize(0.3);
    //Frame->GetXaxis()->SetLabelSize(0.1);  
   
    //Frame->GetYaxis()->SetNdivisions(4,0); 
    //TLegend *leg = new TLegend(0.18,0.65,0.35,0.9);
    //leg->AddEntry(Frame->FindObject("PID_Curve"),"", "L");
    Frame->Draw();
    //leg->Draw("same");
    //Name->Draw("SAME");
    if(log)pad1->SetLogy();
    //pad2->cd();
    Pull->SetTitle(0);
    Pull->GetYaxis()->SetTitle("Pull");
    Pull->GetYaxis()->SetTitleSize(0.15);
    Pull->GetYaxis()->SetLabelSize(0.1);
    Pull->GetYaxis()->CenterTitle();
    Pull->GetYaxis()->SetTitleOffset(0.3);
    Pull->GetYaxis()->SetNdivisions(505);
    Pull->GetYaxis()->SetRangeUser(-9.9,9.9);
    Pull->GetXaxis()->SetTitleSize(0.3);
    Pull->GetXaxis()->SetLabelSize(0.15);  
    Pull->GetXaxis()->SetTitleOffset(0.63);
    //Pull->Draw();
}
void prettycanvasAll1(TCanvas *c1,RooPlot *Frame, RooPlot *Pull, int log)
{
    TPaveText *Name = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
                            0.75 - gStyle->GetPadTopMargin(),
                            gStyle->GetPadLeftMargin() + 0.31,
                            0.95 - gStyle->GetPadTopMargin(),
                                        "BRNDC");

    Name->AddText("");
    //Name->SetFillColorAlpha(0, 0);
    Name->SetTextAlign(12);
    Name->SetBorderSize(0); 
    TPad *pad1 = new TPad("pad1","pad1",0.0,0.,1.0,1.0);
    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
    TGaxis::SetMaxDigits(3);
    //pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.08);
    pad2->SetTopMargin(0.015);
    pad2->SetBottomMargin(0.5);  
    pad2->SetBorderMode(0);
    pad1->SetBorderMode(0);
    c1->SetBorderMode(0);  
    pad1->Draw();
    //pad2->Draw(); 
    pad1->cd(); 
    Frame->GetYaxis()->SetTitleSize(0.1); 
    Frame->GetYaxis()->SetTitleOffset(0.6);
    Frame->SetTitle(""); 
    Frame->GetXaxis()->SetTitle("#DeltaLL(e-#pi)");
    Pull->GetXaxis()->SetTitle("#DeltaLL(e-#pi)"); 
    //Frame->GetXaxis()->SetTitleSize(0.3);
    //Frame->GetXaxis()->SetLabelSize(0.1);  
   
    //Frame->GetYaxis()->SetNdivisions(4,0); 
    Frame->Draw();
    //Name->Draw("SAME");
    if(log)pad1->SetLogy();
    //pad2->cd();
    Pull->SetTitle(0);
    Pull->GetYaxis()->SetTitle("Pull");
    Pull->GetYaxis()->SetTitleSize(0.15);
    Pull->GetYaxis()->SetLabelSize(0.1);
    Pull->GetYaxis()->CenterTitle();
    Pull->GetYaxis()->SetTitleOffset(0.3);
    Pull->GetYaxis()->SetNdivisions(505);
    Pull->GetYaxis()->SetRangeUser(-9.9,9.9);
    Pull->GetXaxis()->SetTitleSize(0.3);
    Pull->GetXaxis()->SetLabelSize(0.15);  
    Pull->GetXaxis()->SetTitleOffset(0.63);
    ///Pull->Draw();
}
void prettycanvasAll2(TCanvas *c1,RooPlot *Frame, RooPlot *Pull, int log)
{
    TPaveText *Name = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
                            0.75 - gStyle->GetPadTopMargin(),
                            gStyle->GetPadLeftMargin() + 0.31,
                            0.95 - gStyle->GetPadTopMargin(),
                                        "BRNDC");

    Name->AddText("");
    //Name->SetFillColorAlpha(0, 0);
    Name->SetTextAlign(12);
    Name->SetBorderSize(0); 
    TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
    TGaxis::SetMaxDigits(3);
    pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.08);
    pad2->SetTopMargin(0.015);
    pad2->SetBottomMargin(0.5);  
    pad2->SetBorderMode(0);
    pad1->SetBorderMode(0);
    c1->SetBorderMode(0);  
    pad1->Draw();
    pad2->Draw(); 
    pad1->cd(); 
    Frame->GetYaxis()->SetTitleSize(0.1); 
    Frame->GetYaxis()->SetTitleOffset(0.6);
    Frame->SetTitle(""); 
    Frame->GetXaxis()->SetTitle("n#sigma_{e}");
    Pull->GetXaxis()->SetTitle("n#sigma_{e}"); 
    //Frame->GetXaxis()->SetTitleSize(0.3);
    //Frame->GetXaxis()->SetLabelSize(0.1);  
   
    //Frame->GetYaxis()->SetNdivisions(4,0); 
    Frame->Draw();
    //Name->Draw("SAME");
    if(log)pad1->SetLogy();
    pad2->cd();
    Pull->SetTitle(0);
    Pull->GetYaxis()->SetTitle("Pull");
    Pull->GetYaxis()->SetTitleSize(0.15);
    Pull->GetYaxis()->SetLabelSize(0.1);
    Pull->GetYaxis()->CenterTitle();
    Pull->GetYaxis()->SetTitleOffset(0.3);
    Pull->GetYaxis()->SetNdivisions(505);
    Pull->GetYaxis()->SetRangeUser(-9.9,9.9);
    Pull->GetXaxis()->SetTitleSize(0.3);
    Pull->GetXaxis()->SetLabelSize(0.15);  
    Pull->GetXaxis()->SetTitleOffset(0.63);
    Pull->Draw();
}
void prettycanvasAll_r(TCanvas *c1,RooPlot *Frame, RooPlot *Pull, int log)
{
    TPaveText *Name = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
                            0.75 - gStyle->GetPadTopMargin(),
                            gStyle->GetPadLeftMargin() + 0.31,
                            0.95 - gStyle->GetPadTopMargin(),
                                        "BRNDC");

    Name->AddText("");
    //Name->SetFillColorAlpha(0, 0);
    Name->SetTextAlign(12);
    Name->SetBorderSize(0); 
    TPad *pad1 = new TPad("pad1","pad1",0.0,0.,1.0,1.0);
    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
    TGaxis::SetMaxDigits(3);
    //pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.08);
    pad2->SetTopMargin(0.015);
    pad2->SetBottomMargin(0.5);  
    pad2->SetBorderMode(0);
    pad1->SetBorderMode(0);
    c1->SetBorderMode(0);  
    pad1->Draw();
    //pad2->Draw(); 
    pad1->cd(); 
    Frame->GetYaxis()->SetTitleSize(0.1); 
    Frame->GetYaxis()->SetTitleOffset(0.6);
    Frame->SetTitle(""); 
    Frame->GetXaxis()->SetTitle("Likelihood Response");
    Pull->GetXaxis()->SetTitle("Likelihood Response"); 
    //Frame->GetXaxis()->SetTitleSize(0.3);
    //Frame->GetXaxis()->SetLabelSize(0.1);  
   
    //Frame->GetYaxis()->SetNdivisions(4,0); 
    Frame->Draw();
    //Name->Draw("SAME");
    if(log)pad1->SetLogy();
    //pad2->cd();
    Pull->SetTitle(0);
    Pull->GetYaxis()->SetTitle("Pull");
    Pull->GetYaxis()->SetTitleSize(0.15);
    Pull->GetYaxis()->SetLabelSize(0.1);
    Pull->GetYaxis()->CenterTitle();
    Pull->GetYaxis()->SetTitleOffset(0.3);
    Pull->GetYaxis()->SetNdivisions(505);
    Pull->GetYaxis()->SetRangeUser(-9.9,9.9);
    Pull->GetXaxis()->SetTitleSize(0.3);
    Pull->GetXaxis()->SetLabelSize(0.15);  
    Pull->GetXaxis()->SetTitleOffset(0.63);
    //Pull->Draw();
}
void prettycanvasAll2_r(TCanvas *c1,RooPlot *Frame, RooPlot *Pull, int log)
{
    TPaveText *Name = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
                            0.75 - gStyle->GetPadTopMargin(),
                            gStyle->GetPadLeftMargin() + 0.31,
                            0.95 - gStyle->GetPadTopMargin(),
                                        "BRNDC");

    Name->AddText("");
    //Name->SetFillColorAlpha(0, 0);
    Name->SetTextAlign(12);
    Name->SetBorderSize(0); 
    TPad *pad1 = new TPad("pad1","pad1",0.0,0.25,1.0,1.0);
    TPad *pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.255);
    TGaxis::SetMaxDigits(3);
    pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.08);
    pad2->SetTopMargin(0.015);
    pad2->SetBottomMargin(0.5);  
    pad2->SetBorderMode(0);
    pad1->SetBorderMode(0);
    c1->SetBorderMode(0);  
    pad1->Draw();
    pad2->Draw(); 
    pad1->cd(); 
    Frame->GetYaxis()->SetTitleSize(0.1); 
    Frame->GetYaxis()->SetTitleOffset(0.6);
    Frame->SetTitle(""); 
    Frame->GetXaxis()->SetTitle("Likelihood Response");
    Pull->GetXaxis()->SetTitle("Likelihood Response"); 
    //Frame->GetXaxis()->SetTitleSize(0.3);
    //Frame->GetXaxis()->SetLabelSize(0.1);  
   
    //Frame->GetYaxis()->SetNdivisions(4,0); 
    Frame->Draw();
    //Name->Draw("SAME");
    if(log)pad1->SetLogy();
    pad2->cd();
    Pull->SetTitle(0);
    Pull->GetYaxis()->SetTitle("Pull");
    Pull->GetYaxis()->SetTitleSize(0.15);
    Pull->GetYaxis()->SetLabelSize(0.1);
    Pull->GetYaxis()->CenterTitle();
    Pull->GetYaxis()->SetTitleOffset(0.3);
    Pull->GetYaxis()->SetNdivisions(505);
    Pull->GetYaxis()->SetRangeUser(-9.9,9.9);
    Pull->GetXaxis()->SetTitleSize(0.3);
    Pull->GetXaxis()->SetLabelSize(0.15);  
    Pull->GetXaxis()->SetTitleOffset(0.63);
    Pull->Draw();
}
