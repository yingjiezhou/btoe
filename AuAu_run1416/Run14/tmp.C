
{     
      TFile a("aa.root" , "RECREATE");
      TTree T("T","test list");
      TList *list = new TList();
      TObjArray *a1 = new TObjArray();
      a1->SetName("a1");
      list->Add(a1);
      TH1F *ha1a = new TH1F("ha1a","ha1",100,0,1);
      TH1F *ha1b = new TH1F("ha1b","ha1",100,0,1);
      a1->Add(ha1a);
      a1->Add(ha1b);
      TObjArray *b1 = new TObjArray();
      b1->SetName("b1");
      list->Add(b1);
      TH1F *hb1a = new TH1F("hb1a","hb1",100,0,1);
      TH1F *hb1b = new TH1F("hb1b","hb1",100,0,1);
      b1->Add(hb1a);
      b1->Add(hb1b);
      TObjArray *a2 = new TObjArray();
      a2->SetName("a2");
      list->Add(a2);
      TH1S *ha2a = new TH1S("ha2a","ha2",100,0,1);
      TH1S *ha2b = new TH1S("ha2b","ha2",100,0,1);
      a2->Add(ha2a);
      a2->Add(ha2b);
      T.Branch(list,16000,2);
      T.Fill();
      T.Write();
      T.Print();
      
}
