#!/usr/bin/python
import sys
from collections import Counter
from ROOT import TFile, TCanvas, TNtuple, TH1F, gDirectory, gPad, TH2F, gStyle, TF1, TGraphErrors

class daughterHists:
  def __init__(self,name,symbol,maxMcPt):
    ptBins = int(20*maxMcPt)
    self.hMcPtRpt = TH2F("h%sMcPtRpt"%name,"h;mcP_{T}(%s)(GeV/c);rP_{T}(%s)(GeV/c)"%(symbol,symbol),ptBins,0,maxMcPt,ptBins,0,maxMcPt)
    self.hPtResolution = TH2F("h%sPtResolution"%name,";mcP_{T}(%s)(GeV/c);#Deltap_{T}/p_{T}"%symbol,ptBins,0,maxMcPt,120,-0.06,0.06)
    self.hD0RptRpt = TH2F("hD0Rpt%sRpt"%name,";rP_{T}(D^{0})(GeV/c);rP_{T}(%s)(GeV/c)"%symbol,ptBins,0,maxMcPt,ptBins,0,maxMcPt)
    self.hD0RptRphi = TH2F("hD0Rpt%sRphi"%name,";rP_{T}(D^{0})(GeV/c);r#phi(%s)"%symbol,ptBins,0,maxMcPt,64,-3.2,3.2)
    self.hD0RptReta = TH2F("hD0Rpt%sReta"%name,";rP_{T}(D^{0})(GeV/c);r#eta(%s)"%symbol,ptBins,0,maxMcPt,48,-1.2,1.2)
    self.hD0RptNfit = TH2F("hD0Rpt%sNfit"%name,";rP_{T}(D^{0})(GeV/c);nHitsFit(%s)"%symbol,ptBins,0,maxMcPt,50,0,50)
    self.hD0RptNSigmaDedx = TH2F("hD0RptNSigma%s"%name,";rP_{T}(D^{0})(GeV/c);n#sigma_{%s}"%symbol,ptBins,0,maxMcPt,80,-4,4)
    self.hD0RptDedx = TH2F("hD0Rpt%sDedx"%name,";rP_{T}(D^{0})(GeV/c);dedx(%s)"%symbol,ptBins,0,maxMcPt,80,1,5)
    self.hD0RptNhitsDedx = TH2F("hD0Rpt%sNhitsDedx"%name,";rP_{T}(D^{0})(GeV/c);nHitsDedx(%s)"%symbol,ptBins,0,maxMcPt,50,0,50)
    self.hD0RptDca = TH2F("hD0Rpt%sDca"%name,";rP_{T}(D^{0})(GeV/c);dca(%s)(cm)"%symbol,ptBins,0,maxMcPt,50,0,2.5)
    # for efficiency
    self.hMcPt = TH1F("h%sMcPt"%name,"",ptBins,0,maxMcPt) # within acceptance
    self.hMcPtRecoEff = TH1F("h%sMcPtRecoEff"%name,";mcP_{T}(%s);Reco. Eff(%s)"%(symbol,symbol),ptBins,0,maxMcPt)
    self.hMcPt.Sumw2()
    self.hMcPtRecoEff.Sumw2()

  def write(self,outfile):
    outfile.cd()
    self.hMcPtRpt.Write()
    self.hPtResolution.Write()
    self.hD0RptRpt.Write()
    self.hD0RptRphi.Write()
    self.hD0RptReta.Write()
    self.hD0RptDedx.Write()
    self.hD0RptNSigmaDedx.Write()
    self.hD0RptNfit.Write()
    self.hD0RptNhitsDedx.Write()
    self.hD0RptDca.Write()

    self.hMcPtRecoEff.Divide(self.hMcPt)
    self.hMcPtRecoEff.Write()
    

def main():
  inFileName = sys.argv[1]
  inFile = TFile(inFileName)
  outFile = TFile(inFileName.replace(".root","_hists.root"),"RECREATE")

  #  ------------------ event histograms ------------------------------
  minRunId = 1.30385000000000000e+07
  maxRunId = 1.30750000000000000e+07
  hEventVsRun = TH1F("eventVsRun", ";runIndex;N_{evts}", 1000,minRunId, maxRunId)
  hDeltaVx = TH1F("deltaVx", ";mcVx-Vx(cm)", 40, -2, 2); 
  hDeltaVy = TH1F("deltaVy", ";mcVy-Vy(cm)", 40, -2, 2); 
  hDeltaVz = TH1F("deltaVz", ";mcVz-Vz(cm)", 40, -2, 2); 
  hVz = TH1F("Vz", ";Vz(cm)", 100, -120, 120);
  hDeltaVzVzVpd = TH1F("deltaVzVsVzVpd", ";Vz-VpdVz(cm)", 80, -8, 8); 

  eventCount = inFile.Get("eventCount")

  for event in eventCount:
    hEventVsRun.Fill(event.runId)
    hDeltaVx.Fill(event.mcVx-event.vx)
    hDeltaVy.Fill(event.mcVy-event.vy)
    hDeltaVz.Fill(event.mcVz-event.vz)
    hVz.Fill(event.vz)
    hDeltaVzVzVpd.Fill(event.vz-event.vzVpd)

  hVz.Sumw2()
  hDeltaVzVzVpd.Sumw2()

  outFile.cd()
  hEventVsRun.Write()
  hDeltaVx.Write()
  hDeltaVy.Write()
  hDeltaVz.Write()
  hVz.Write()
  hDeltaVzVzVpd.Write()

  #------------------ dzero histograms ------------------------------
  maxMcPt = 6.0
  ptBins = int(20*maxMcPt)
  cuts = {'nFitsOverNmax':0.52,'nFit':15,'dca':2.,'eta':1.,'pt':0.2}
  # D0
  hD0McPtMcY = TH2F("hD0McPtMcY",";mcP_{T}(D^{0})(GeV/c);mcRapidity(D^{0})",ptBins,0,maxMcPt,48,-1.2,1.2)
  hD0McPtMcPhi = TH2F("hD0McPtMcPhi",";mcP_{T}(D^{0})(GeV/c);mc#phi(D^{0})",ptBins,0,maxMcPt,128,-3.2,3.2)
  hD0PtResolution = TH2F("hD0PtResolution",";mcP_{T}(D^{0})(GeV/c);#DeltaP_{T}/mcP_{T}",ptBins,0,maxMcPt,120,-0.06,0.06)
  hD0RptInvMass = TH2F("hD0RptInvMass",";rP_{T}(D^{0})(GeV/c);invMass(GeV/c^2)",ptBins,0,maxMcPt,40,1.7,2.1)
  hKRptPiRpt = TH2F("hKRptPiRpt",";rP_{T}(K)(GeV/c);rP_{T}(#pi)(GeV/c)",ptBins,0,maxMcPt,ptBins,0,maxMcPt)
  # kaons and pions
  kaonsHists = daughterHists("K","K",maxMcPt)
  pionsHists = daughterHists("Pi","#pi",maxMcPt)

  ntDzero = inFile.Get("dzero")
  for dzero in ntDzero:
    hD0McPtMcY.Fill(dzero.pt,dzero.y)
    hD0McPtMcPhi.Fill(dzero.pt,dzero.phi)

    # mc within acceptance
    if abs(dzero.kEta)<cuts['eta']:
      kaonsHists.hMcPt.Fill(dzero.kPt)
    if abs(dzero.piEta)<cuts['eta']:
      pionsHists.hMcPt.Fill(dzero.piPt)

    #check if kaon/pion is reconstructed within acceptance
    rKaon = dzero.kNfit>=cuts['nFit'] and dzero.kRpt>cuts['pt'] and abs(dzero.kReta)<cuts['eta'] and dzero.kDca<cuts['dca'] and dzero.kNfit/dzero.kNmax>cuts['nFitsOverNmax']
    rPion = dzero.piNfit>=cuts['nFit'] and dzero.piRpt>cuts['pt'] and abs(dzero.piReta)<cuts['eta'] and dzero.piDca<cuts['dca'] and dzero.piNfit/dzero.piNmax>cuts['nFitsOverNmax']

    if rKaon:
      kaonsHists.hMcPtRpt.Fill(dzero.kPt,dzero.kRpt)
      kaonsHists.hPtResolution.Fill(dzero.kPt,(dzero.kPt-dzero.kRpt)/dzero.kPt)
      kaonsHists.hMcPtRecoEff.Fill(dzero.kPt)
      kaonsHists.hD0RptDedx.Fill(dzero.kRpt,dzero.kDedx*1e6)
    if rPion:
      pionsHists.hMcPtRpt.Fill(dzero.piPt,dzero.piRpt)
      pionsHists.hPtResolution.Fill(dzero.piPt,(dzero.piPt-dzero.piRpt)/dzero.piPt)
      pionsHists.hMcPtRecoEff.Fill(dzero.piPt)
      pionsHists.hD0RptDedx.Fill(dzero.piRpt,dzero.piDedx*1e6)

    #if dzero is reconstructed
    if dzero.rPt>0 and rKaon and rPion:
      kaonsHists.hD0RptRpt.Fill(dzero.rPt,dzero.kRpt)
      kaonsHists.hD0RptRphi.Fill(dzero.rPt,dzero.kRphi)
      kaonsHists.hD0RptReta.Fill(dzero.rPt,dzero.kReta)
      kaonsHists.hD0RptNfit.Fill(dzero.rPt,dzero.kNfit)
      kaonsHists.hD0RptNSigmaDedx.Fill(dzero.rPt,dzero.kNsigK)
      kaonsHists.hD0RptNhitsDedx.Fill(dzero.rPt,dzero.kNdedx)
      kaonsHists.hD0RptDca.Fill(dzero.rPt,dzero.kDca)

      pionsHists.hD0RptRpt.Fill(dzero.rPt,dzero.piRpt)
      pionsHists.hD0RptRphi.Fill(dzero.rPt,dzero.piRphi)
      pionsHists.hD0RptReta.Fill(dzero.rPt,dzero.piReta)
      pionsHists.hD0RptNfit.Fill(dzero.rPt,dzero.piNfit)
      pionsHists.hD0RptNSigmaDedx.Fill(dzero.rPt,dzero.kNsigPi)
      pionsHists.hD0RptNhitsDedx.Fill(dzero.rPt,dzero.piNdedx)
      pionsHists.hD0RptDca.Fill(dzero.rPt,dzero.piDca)
      
      hD0PtResolution.Fill(dzero.pt,(dzero.pt-dzero.rPt)/dzero.pt)
      hD0RptInvMass.Fill(dzero.rPt,dzero.invMass)
      hKRptPiRpt.Fill(dzero.kRpt,dzero.piRpt)

  # dzero efficiency
  hD0RecoEff = hD0PtResolution.ProjectionX()
  hD0RecoEff.Sumw2()
  hD0RecoEff.Divide(hD0McPtMcPhi.ProjectionX())
  hD0RecoEff.SetName("hD0RecoEff")
  hD0RecoEff.SetTitle(";mcP_{T}(D^{0})(GeV/c);D^{0} Reco. Eff.")

  # write hists
  outFile.cd()
  hD0McPtMcY.Write()
  hD0McPtMcPhi.Write()
  hD0PtResolution.Write()
  hD0RecoEff.Write()
  hD0RptInvMass.Write()
  hKRptPiRpt.Write()

  kaonsHists.write(outFile)
  pionsHists.write(outFile)
  
  outFile.Close()

if __name__ == '__main__':
	main()
