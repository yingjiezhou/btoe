void ConvertHisttoGraph(){
  
  auto f = new TFile("TriggereffforYingjie.root", "READ");
  auto he0 = (TH1F*)f->Get("hTriggereffforYingjieHT0");
  auto he2 = (TH1F*)f->Get("hTriggereffforYingjieHT2");
  auto he0s = (TH1F*)f->Get("hTriggereffforYingjieSysHT0");
  auto he2s = (TH1F*)f->Get("hTriggereffforYingjieSysHT2");
  double x[1000], y[1000], ex[1000], ey[1000];
  //
  int num=0;
  for(auto i=0; i<he0->GetNbinsX(); i++){
    x[i] = he0->GetBinCenter(i+1);
    y[i] = he0->GetBinContent(i+1);
    ex[i] = 0;
    ey[i] = he0->GetBinError(i+1);
    num++;
  }
  //
  auto gTrig0 = new TGraph(num, x, y);
  num = 0;
  for(auto i=0; i<he2->GetNbinsX(); i++){
    x[i] = he2->GetBinCenter(i+1);
    y[i] = he2->GetBinContent(i+1);
    ex[i] = 0;
    ey[i] = he2->GetBinError(i+1);
    num++;
  }
  auto gTrig2 = new TGraph(num, x, y);
  //
  num = 0;
  for(auto i=0; i<he2s->GetNbinsX(); i++){
    x[i] = he2s->GetBinCenter(i+1);
    y[i] = he2s->GetBinContent(i+1);
    ex[i] = 0;
    ey[i] = he2s->GetBinError(i+1);
    num++;
  }
  auto gTrig2Sys = new TGraph(num, x, y);
  //
  num = 0;
  for(auto i=0; i<he0s->GetNbinsX(); i++){
    x[i] = he0s->GetBinCenter(i+1);
    y[i] = he0s->GetBinContent(i+1);
    ex[i] = 0;
    ey[i] = he0s->GetBinError(i+1);
    num++;
  }
  auto gTrig0Sys = new TGraph(num, x, y);
//  auto gTrig0Sys = new TGraphErrors(num, x, y, ex, ey);

//
//  gTrig0->SetLineColor(3);
//  gTrig0->SetMarkerColor(3);
  
//  gTrig0Sys->Draw("ALP");
//  cout<<gTrig0Sys->Eval(2.6)<<"  "<<gTrig0->Eval(2.6)<<endl;
//  gTrig2Sys->Draw();
  //  gTrig2->Draw("same");
//  he2s->Draw("same");
  auto fw = new TFile("TrigEffGraph.root", "RECREATE");
  fw->cd();
  gTrig0->Write("hTrigEffHT0");
  gTrig2->Write("hTrigEffHT2");
  gTrig0Sys->Write("hTrigEffHT0Sys");
  gTrig2Sys->Write("hTrigEffHT2Sys");

  fw->Close();
}
