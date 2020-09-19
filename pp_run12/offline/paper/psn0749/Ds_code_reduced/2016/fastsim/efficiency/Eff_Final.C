void Eff_Final(TString f1, TString f2, TString f3 )
{
	TH1::SetDefaultSumw2();
	TH1F *AllCounts[10];
	TH1F  *PassAcc[10];
	TH1F  *PassAccTpc[10];
	TH1F    *PassAccTpcHft[10];
	TH1F    *PassAccTpcHftPid[10];
	TH1F      *PassAccTpcHftPidIniTopo[10];
	TH1F     *PassAccTpcHftPidIniTopoBDT[10];
	TH1F  *PassOnlyAccEff[10];
	TH1F  *PassOnlyTpcEff[10];
	TH1F    *PassOnlyHftEff[10];
	TH1F    *PassOnlyPidEff[10];
	TH1F      *PassOnlyIniTopoEff[10];
	TH1F     *PassOnlyBDTEff[10];


	TH1F    *AllCounts_46;
	TH1F   *PassAcc_46;
	TH1F   *PassAccTpc_46;
	TH1F   *PassAccTpcHft_46;
	TH1F   *PassAccTpcHftPid_46;
	TH1F   *PassAccTpcHftPidIniTopo_46;
	TH1F   *PassAccTpcHftPidIniTopoBDT_46;
	TH1F  *PassOnlyAccEff_46;
	TH1F  *PassOnlyTpcEff_46;
	TH1F    *PassOnlyHftEff_46;
	TH1F    *PassOnlyPidEff_46;
	TH1F      *PassOnlyIniTopoEff_46;
	TH1F     *PassOnlyBDTEff_46;

	TH1F    *AllCounts_68;
	TH1F   *PassAcc_68;
	TH1F   *PassAccTpc_68;
	TH1F   *PassAccTpcHft_68;
	TH1F   *PassAccTpcHftPid_68;
	TH1F   *PassAccTpcHftPidIniTopo_68;
	TH1F   *PassAccTpcHftPidIniTopoBDT_68;
	TH1F  *PassOnlyAccEff_68;
	TH1F  *PassOnlyTpcEff_68;
	TH1F    *PassOnlyHftEff_68;
	TH1F    *PassOnlyPidEff_68;
	TH1F      *PassOnlyIniTopoEff_68;
	TH1F     *PassOnlyBDTEff_68;

	TH1F    *AllCounts_1040_1525;
	TH1F   *PassAcc_1040_1525;
	TH1F   *PassAccTpc_1040_1525;
	TH1F   *PassAccTpcHft_1040_1525;
	TH1F   *PassAccTpcHftPid_1040_1525;
	TH1F   *PassAccTpcHftPidIniTopo_1040_1525;
	TH1F   *PassAccTpcHftPidIniTopoBDT_1040_1525;
	TH1F  *PassOnlyAccEff_1040_1525;
	TH1F  *PassOnlyTpcEff_1040_1525;
	TH1F    *PassOnlyHftEff_1040_1525;
	TH1F    *PassOnlyPidEff_1040_1525;
	TH1F      *PassOnlyIniTopoEff_1040_1525;
	TH1F     *PassOnlyBDTEff_1040_1525;

	TH1F     *PassAllEff[10];
	TH1F     *PassAllEff_46;
	TH1F     *PassAllEff_68;
	TH1F     *PassAllEff_1040_1525;

	TFile *File_Eff = TFile::Open(f1);
	TFile *File_Eff_BDT = TFile::Open(f2);
	TFile *File_output = new TFile(f3, "RECREATE");
TH1::SetDefaultSumw2();

	TString const mCent[3] = {"010", "1040", "4080"};
	TString const HistName_All[5] = {"AllCouts_010_Ds", "AllCouts_1040_Ds", "AllCouts_4080_Ds", "AllCouts_1020_Ds", "AllCouts_2040_Ds"};
	TString const HistName_Acc[5] = {"PassAcc_010_Ds", "PassAcc_1040_Ds", "PassAcc_4080_Ds", "PassAcc_1020_Ds", "PassAcc_2040_Ds"};
	TString const HistName_AccTpc[5] = {"PassTpc_010_Ds", "PassTpc_1040_Ds", "PassTpc_4080_Ds", "PassTpc_1020_Ds", "PassTpc_2040_Ds"};
	TString const HistName_AccTpcHft[5] = {"PassTpcHft_010_Ds", "PassTpcHft_1040_Ds", "PassTpcHft_4080_Ds", "PassTpcHft_1020_Ds", "PassTpcHft_2040_Ds"};
	TString const HistName_AccTpcHftPid[5] = {"PassTpcHftPid_010_Ds", "PassTpcHftPid_1040_Ds", "PassTpcHftPid_4080_Ds", "PassTpcHftPid_1020_Ds", "PassTpcHftPid_2040_Ds"};
	TString const HistName_AccTpcHftPidTopo[5] = {"PassTpcHftPidTopo_010_Ds", "PassTpcHftPidTopo_1040_Ds", "PassTpcHftPidTopo_4080_Ds", "PassTpcHftPidTopo_1020_Ds", "PassTpcHftPidTopo_2040_Ds"};
	TString const HistName_AccTpcHftPidTopoBDT[5] = {"PassTpcHftPidTopoBDT_010_Ds", "PassTpcHftPidTopoBDT_1040_Ds", "PassTpcHftPidTopoBDT_4080_Ds", "PassTpcHftPidTopoBDT_1020_Ds", "PassTpcHftPidTopoBDT_2040_Ds"};
	for ( int i = 0; i < =4; i++)
	{
		AllCounts[i] = (TH1F*)File_Eff->Get(HistName_All[i].Data());
		PassAcc[i] = (TH1F*)File_Eff->Get(HistName_Acc[i].Data());
		PassAccTpc[i] = (TH1F*)File_Eff->Get(HistName_AccTpc[i].Data());
		PassAccTpcHft[i] = (TH1F*)File_Eff->Get(HistName_AccTpcHft[i].Data());
		PassAccTpcHftPid[i] = (TH1F*)File_Eff->Get(HistName_AccTpcHftPid[i].Data());
		PassAccTpcHftPidIniTopo[i] = (TH1F*)File_Eff->Get(HistName_AccTpcHftPidTopo[i].Data());
		PassAccTpcHftPidIniTopoBDT[i] = (TH1F*)File_Eff_BDT->Get(HistName_AccTpcHftPidTopoBDT[i].Data());

		PassOnlyAccEff[i] = new TH1F(*PassAcc[i]);
		PassOnlyAccEff[i]->SetName(Form("PassOnlyAccEff_%i", i));
		PassOnlyAccEff[i]->Divide(PassAcc[i],AllCounts[i],1, 1);
		PassOnlyTpcEff[i] = new TH1F(*PassAccTpc[i]);
		PassOnlyTpcEff[i]->SetName(Form("PassOnlyTpcEff_%i", i));
		PassOnlyTpcEff[i]->Divide(PassAccTpc[i],PassAcc[i],1,1);
		PassOnlyHftEff[i] = new TH1F(*PassAccTpcHft[i]);
		PassOnlyHftEff[i]->SetName(Form("PassOnlyHftEff_%i", i));
		PassOnlyHftEff[i]->Divide(PassAccTpcHft[i],PassAccTpc[i],1,1);
		PassOnlyPidEff[i] = new TH1F(*PassAccTpcHftPid[i]);
		PassOnlyPidEff[i]->SetName(Form("PassOnlyPidEff_%i", i));
		PassOnlyPidEff[i]->Divide(PassAccTpcHftPid[i],PassAccTpcHft[i],1,1);
		PassOnlyIniTopoEff[i] = new TH1F(*PassAccTpcHftPidIniTopo[i]);
		PassOnlyIniTopoEff[i]->SetName(Form("PassOnlyIniTopoEff_%i", i));
		PassOnlyIniTopoEff[i]->Divide(PassAccTpcHftPidIniTopo[i],PassAccTpcHftPid[i],1,1);
		PassOnlyBDTEff[i] = new TH1F(*PassAccTpcHftPidIniTopoBDT[i]);
		PassOnlyBDTEff[i]->SetName(Form("PassOnlyBDTEff_%i", i));
		PassOnlyBDTEff[i]->Divide(PassAccTpcHftPidIniTopoBDT[i],PassAccTpcHftPidIniTopo[i],1,1);
		PassAllEff[i] = new TH1F(*PassAccTpcHftPidIniTopoBDT[i]);
		PassAllEff[i]->SetName(Form("PassAllEff_%i", i));
		PassAllEff[i]->Divide(PassAccTpcHftPidIniTopoBDT[i],AllCounts[i],1, 1);

	}
cout <<"flag1" << endl;
		AllCounts_46 = (TH1F*)File_Eff->Get("AllCouts_46_Ds");
		PassAcc_46 = (TH1F*)File_Eff->Get("PassAcc_46_Ds");
		PassAccTpc_46 = (TH1F*)File_Eff->Get("PassTpc_46_Ds");
		PassAccTpcHft_46 = (TH1F*)File_Eff->Get("PassTpcHft_46_Ds");
		PassAccTpcHftPid_46 = (TH1F*)File_Eff->Get("PassTpcHftPid_46_Ds");
		PassAccTpcHftPidIniTopo_46 = (TH1F*)File_Eff->Get("PassTpcHftPidTopo_46_Ds");
		PassAccTpcHftPidIniTopoBDT_46 = (TH1F*)File_Eff_BDT->Get("PassTpcHftPidTopoBDT_46_Ds");

		PassOnlyAccEff_46 = new TH1F(*PassAcc_46);
		PassOnlyAccEff_46->SetName("PassOnlyAccEff_46");
		PassOnlyAccEff_46->Divide(PassAcc_46,AllCounts_46,1, 1);
		PassOnlyTpcEff_46 = new TH1F(*PassAccTpc_46);
		PassOnlyTpcEff_46->SetName("PassOnlyTpcEff_46");
		PassOnlyTpcEff_46->Divide(PassAccTpc_46,PassAcc_46,1,1);
		PassOnlyHftEff_46 = new TH1F(*PassAccTpcHft_46);
		PassOnlyHftEff_46->SetName("PassOnlyHftEff_46");
		PassOnlyHftEff_46->Divide(PassAccTpcHft_46,PassAccTpc_46,1,1);
		PassOnlyPidEff_46 = new TH1F(*PassAccTpcHftPid_46);
		PassOnlyPidEff_46->SetName("PassOnlyPidEff_46");
		PassOnlyPidEff_46->Divide(PassAccTpcHftPid_46,PassAccTpcHft_46,1,1);
		PassOnlyIniTopoEff_46 = new TH1F(*PassAccTpcHftPidIniTopo_46);
		PassOnlyIniTopoEff_46->SetName("PassOnlyIniTopoEff_46");
		PassOnlyIniTopoEff_46->Divide(PassAccTpcHftPidIniTopo_46,PassAccTpcHftPid_46,1,1);
		PassOnlyBDTEff_46 = new TH1F(*PassAccTpcHftPidIniTopoBDT_46);
		PassOnlyBDTEff_46->SetName("PassOnlyBDTEff_46");
		PassOnlyBDTEff_46->Divide(PassAccTpcHftPidIniTopoBDT_46,PassAccTpcHftPidIniTopo_46,1,1);
		PassAllEff_46 = new TH1F(*PassAccTpcHftPidIniTopoBDT_46);
		PassAllEff_46->SetName("PassAllEff_46");
		PassAllEff_46->Divide(PassAccTpcHftPidIniTopoBDT_46,AllCounts_46,1, 1);

		AllCounts_68 = (TH1F*)File_Eff->Get("AllCouts_68_Ds");
		PassAcc_68 = (TH1F*)File_Eff->Get("PassAcc_68_Ds");
		PassAccTpc_68 = (TH1F*)File_Eff->Get("PassTpc_68_Ds");
		PassAccTpcHft_68 = (TH1F*)File_Eff->Get("PassTpcHft_68_Ds");
		PassAccTpcHftPid_68 = (TH1F*)File_Eff->Get("PassTpcHftPid_68_Ds");
		PassAccTpcHftPidIniTopo_68 = (TH1F*)File_Eff->Get("PassTpcHftPidTopo_68_Ds");
		PassAccTpcHftPidIniTopoBDT_68 = (TH1F*)File_Eff_BDT->Get("PassTpcHftPidTopoBDT_68_Ds");

cout <<"flag2" << endl;
		PassOnlyAccEff_68 = new TH1F(*PassAcc_68);
		PassOnlyAccEff_68->SetName("PassOnlyAccEff_68");
		PassOnlyAccEff_68->Divide(PassAcc_68,AllCounts_68,1, 1);
		PassOnlyTpcEff_68 = new TH1F(*PassAccTpc_68);
		PassOnlyTpcEff_68->SetName("PassOnlyTpcEff_68");
		PassOnlyTpcEff_68->Divide(PassAccTpc_68,PassAcc_68,1,1);
		PassOnlyHftEff_68 = new TH1F(*PassAccTpcHft_68);
		PassOnlyHftEff_68->SetName("PassOnlyHftEff_68");
		PassOnlyHftEff_68->Divide(PassAccTpcHft_68,PassAccTpc_68,1,1);
		PassOnlyPidEff_68 = new TH1F(*PassAccTpcHftPid_68);
		PassOnlyPidEff_68->SetName("PassOnlyPidEff_68");
		PassOnlyPidEff_68->Divide(PassAccTpcHftPid_68,PassAccTpcHft_68,1,1);
		PassOnlyIniTopoEff_68 = new TH1F(*PassAccTpcHftPidIniTopo_68);
		PassOnlyIniTopoEff_68->SetName("PassOnlyIniTopoEff_68");
		PassOnlyIniTopoEff_68->Divide(PassAccTpcHftPidIniTopo_68,PassAccTpcHftPid_68,1,1);
		PassOnlyBDTEff_68 = new TH1F(*PassAccTpcHftPidIniTopoBDT_68);
		PassOnlyBDTEff_68->SetName("PassOnlyBDTEff_68");
		PassOnlyBDTEff_68->Divide(PassAccTpcHftPidIniTopoBDT_68,PassAccTpcHftPidIniTopo_68,1,1);
		PassAllEff_68 = new TH1F(*PassAccTpcHftPidIniTopoBDT_68);
		PassAllEff_68->SetName("PassAllEff_68");
		PassAllEff_68->Divide(PassAccTpcHftPidIniTopoBDT_68,AllCounts_68,1, 1);

cout <<"flag3" << endl;
		AllCounts_1040_1525 = (TH1F*)File_Eff->Get("AllCouts_1040_1525_Ds");
		PassAcc_1040_1525 = (TH1F*)File_Eff->Get("PassAcc_1040_1525_Ds");
		PassAccTpc_1040_1525 = (TH1F*)File_Eff->Get("PassTpc_1040_1525_Ds");
		PassAccTpcHft_1040_1525 = (TH1F*)File_Eff->Get("PassTpcHft_1040_1525_Ds");
		PassAccTpcHftPid_1040_1525 = (TH1F*)File_Eff->Get("PassTpcHftPid_1040_1525_Ds");
		PassAccTpcHftPidIniTopo_1040_1525 = (TH1F*)File_Eff->Get("PassTpcHftPidTopo_1040_1525_Ds");
		PassAccTpcHftPidIniTopoBDT_1040_1525 = (TH1F*)File_Eff_BDT->Get("PassTpcHftPidTopoBDT_1040_1525_Ds");

		PassOnlyAccEff_1040_1525 = new TH1F(*PassAcc_1040_1525);
		PassOnlyAccEff_1040_1525->SetName("PassOnlyAccEff_1040_1525");
		PassOnlyAccEff_1040_1525->Divide(PassAcc_1040_1525,AllCounts_1040_1525,1, 1);
		PassOnlyTpcEff_1040_1525 = new TH1F(*PassAccTpc_1040_1525);
		PassOnlyTpcEff_1040_1525->SetName("PassOnlyTpcEff_1040_1525");
		PassOnlyTpcEff_1040_1525->Divide(PassAccTpc_1040_1525,PassAcc_1040_1525,1,1);
		PassOnlyHftEff_1040_1525 = new TH1F(*PassAccTpcHft_1040_1525);
		PassOnlyHftEff_1040_1525->SetName("PassOnlyHftEff_1040_1525");
		PassOnlyHftEff_1040_1525->Divide(PassAccTpcHft_1040_1525,PassAccTpc_1040_1525,1,1);
		PassOnlyPidEff_1040_1525 = new TH1F(*PassAccTpcHftPid_1040_1525);
		PassOnlyPidEff_1040_1525->SetName("PassOnlyPidEff_1040_1525");
		PassOnlyPidEff_1040_1525->Divide(PassAccTpcHftPid_1040_1525,PassAccTpcHft_1040_1525,1,1);
		PassOnlyIniTopoEff_1040_1525 = new TH1F(*PassAccTpcHftPidIniTopo_1040_1525);
		PassOnlyIniTopoEff_1040_1525->SetName("PassOnlyIniTopoEff_1040_1525");
		PassOnlyIniTopoEff_1040_1525->Divide(PassAccTpcHftPidIniTopo_1040_1525,PassAccTpcHftPid_1040_1525,1,1);
		PassOnlyBDTEff_1040_1525 = new TH1F(*PassAccTpcHftPidIniTopoBDT_1040_1525);
		PassOnlyBDTEff_1040_1525->SetName("PassOnlyBDTEff_1040_1525");
		PassOnlyBDTEff_1040_1525->Divide(PassAccTpcHftPidIniTopoBDT_1040_1525,PassAccTpcHftPidIniTopo_1040_1525,1,1);
		PassAllEff_1040_1525 = new TH1F(*PassAccTpcHftPidIniTopoBDT_1040_1525);
		PassAllEff_1040_1525->SetName("PassAllEff_1040_1525");
		PassAllEff_1040_1525->Divide(PassAccTpcHftPidIniTopoBDT_1040_1525,AllCounts_1040_1525,1, 1);

	File_output->cd();
	for ( int i = 0; i < =4; i++)
	{
		PassOnlyAccEff[i]->Write();
		PassOnlyTpcEff[i]->Write();
		PassOnlyHftEff[i]->Write();
		PassOnlyPidEff[i]->Write();
		PassOnlyIniTopoEff[i]->Write();
		PassOnlyBDTEff[i]->Write();
		PassAllEff[i]->Write();
	}

		PassOnlyAccEff_46->Write();
		PassOnlyTpcEff_46->Write();
		PassOnlyHftEff_46->Write();
		PassOnlyPidEff_46->Write();
		PassOnlyIniTopoEff_46->Write();
		PassOnlyBDTEff_46->Write();
		PassAllEff_46->Write();

		PassOnlyAccEff_68->Write();
		PassOnlyTpcEff_68->Write();
		PassOnlyHftEff_68->Write();
		PassOnlyPidEff_68->Write();
		PassOnlyIniTopoEff_68->Write();
		PassOnlyBDTEff_68->Write();
		PassAllEff_68->Write();

		PassOnlyAccEff_1040_1525->Write();
		PassOnlyTpcEff_1040_1525->Write();
		PassOnlyHftEff_1040_1525->Write();
		PassOnlyPidEff_1040_1525->Write();
		PassOnlyIniTopoEff_1040_1525->Write();
		PassOnlyBDTEff_1040_1525->Write();
		PassAllEff_1040_1525->Write();




}
