#!/usr/bin/python
import sys
from ROOT import TFile, TCanvas, TNtuple, TH1F, gDirectory, gPad, TH2F, gStyle, TF1, TGraphErrors, TPaveText
import tpdf_class

dzeroPtBins = [(0,0.7),(0.7,1.2),(1.2,2.0),(2.0,4.0)]
pdf = tpdf_class.pdf_class("dzero_emb_qa")

def histStyle(h,name,title,color,marker=24,xtitle="",ytitle=""):
  h.SetName(name)
  h.SetTitle(title)
  h.SetLineColor(color)
  #h.SetLineWidth(2)
  h.SetMarkerColor(color)
  h.SetMarkerStyle(marker)
  if xtitle != "": h.GetXaxis().SetTitle(xtitle)
  if ytitle != "": h.GetYaxis().SetTitle(ytitle)

def drawHists(dataHist,embHist,variable,particle,symbol,unit=""):
  rHists = []
  eHists = []

  pdf.newPage("%s - %s"%(variable,symbol),2,2)
  for pt in dzeroPtBins:
    dataHist.GetYaxis().SetRangeUser(pt[0],pt[1])
    embHist.GetXaxis().SetRangeUser(pt[0],pt[1])
    rHists.append(dataHist.ProjectionX())
    eHists.append(embHist.ProjectionY())
    
    subname = "%s_%s_%1.2f_%1.2f"%(variable,particle,pt[0],pt[1])
    title = "%1.1f < p_{T}(D^{0}) < %1.1f" % (pt[0],pt[1])
    histStyle(rHists[-1],"r%s"%subname,title,color=4,xtitle="%s(%s)%s"%(variable,symbol,unit))
    histStyle(eHists[-1],"e%s"%subname,title,color=2,xtitle="%s(%s)%s"%(particle,symbol,unit))
    #rHists[-1].Sumw2()
    rHists[-1].Scale(1/float(rHists[-1].Integral()))
    eHists[-1].Scale(1/float(eHists[-1].Integral()))
    
    minY = 0 #min(rHists[-1].GetMinimum(),eHists[-1].GetMinimum())
    maxY = 1.2*max(rHists[-1].GetMaximum(),eHists[-1].GetMaximum())
    rHists[-1].GetYaxis().SetRangeUser(minY,maxY)
    eHists[-1].GetYaxis().SetRangeUser(minY,maxY)
    pdf.draw([rHists[-1],eHists[-1]])

def main():
  dataFile = TFile(sys.argv[1])
  embFile = TFile(sys.argv[2])

  # mc quantities
  pdf.newPage("events",3,2)
  pdf.draw([embFile.Get("eventVsRun")])
  pdf.draw([embFile.Get("Vz")])
  pdf.draw([embFile.Get("deltaVzVsVzVpd")])
  pdf.draw([embFile.Get("deltaVx")],drawOpt="h")
  pdf.draw([embFile.Get("deltaVy")],drawOpt="h")
  pdf.draw([embFile.Get("deltaVz")],drawOpt="h")

  gStyle.SetOptStat(0)
  pdf.newPage("embedding",2,1)
  pdf.draw([embFile.Get("hD0McPtMcPhi")],drawOpt="colz",logz=True)
  pdf.draw([embFile.Get("hD0McPtMcY")],drawOpt="colz",logz=True)

  pdf.newPage("Decay kinematics",3,1)
  pdf.draw([embFile.Get("hD0RptKRpt")],drawOpt="colz",logz=True)
  pdf.draw([embFile.Get("hD0RptPiRpt")],drawOpt="colz",logz=True)
  pdf.draw([embFile.Get("hKRptPiRpt")],drawOpt="colz",logz=True)

  pdf.newPage("D^{0} reconstruction",2,2)
  hD0PtResolution = embFile.Get("hD0PtResolution")
  hD0PtResolution.FitSlicesY()
  hD0PtRes = gDirectory.Get("hD0PtResolution_2")
  hD0PtRes.GetYaxis().SetRangeUser(0,0.03)
  histStyle(hD0PtRes,"hD0PtRes","",color=3,ytitle="#DeltaP_{T}/mcP_{T}")
  pdf.draw([hD0PtRes])
  hD0RptInvMass = embFile.Get("hD0RptInvMass")
  hD0RptInvMass.FitSlicesY()
  hD0InvMassMean = gDirectory.Get("hD0RptInvMass_1")
  hD0InvMassRMS = gDirectory.Get("hD0RptInvMass_2")
  hD0InvMassMean.GetYaxis().SetRangeUser(1.8,1.9)
  hD0InvMassRMS.GetYaxis().SetRangeUser(0,0.02)
  histStyle(hD0InvMassMean,"hD0InvMassMean","",color=3,ytitle="mean(D^{0})(GeV/c^{2})")
  histStyle(hD0InvMassRMS,"hD0InvMassRMS","",color=3,ytitle="width(D^{0})(GeV/c^{2})")
  pdf.draw([hD0RptInvMass],drawOpt="colz",logz=True)
  pdf.draw([hD0InvMassMean])
  pdf.draw([hD0InvMassRMS])

  drawHists(dataFile.Get("embQA/h2_kaon_pt_vs_d0_pt"),embFile.Get("hD0RptKRpt"),"rP_{T}","kaon","K","(GeV/c)")
  drawHists(dataFile.Get("embQA/h2_pion_pt_vs_d0_pt"),embFile.Get("hD0RptPiRpt"),"rP_{T}","pion","#pi","(GeV/c)")
  drawHists(dataFile.Get("embQA/h2_kaon_phi_vs_d0_pt"),embFile.Get("hD0RptKRphi"),"r#phi","kaon","K")
  drawHists(dataFile.Get("embQA/h2_pion_phi_vs_d0_pt"),embFile.Get("hD0RptPiRphi"),"r#phi","pion","#pi")
  drawHists(dataFile.Get("embQA/h2_kaon_eta_vs_d0_pt"),embFile.Get("hD0RptKReta"),"r#eta","kaon","K")
  drawHists(dataFile.Get("embQA/h2_pion_eta_vs_d0_pt"),embFile.Get("hD0RptPiReta"),"r#eta","pion","#pi")
  drawHists(dataFile.Get("embQA/h2_kaon_nfit_vs_d0_pt"),embFile.Get("hD0RptKNfit"),"nHitsFit","kaon","K")
  drawHists(dataFile.Get("embQA/h2_pion_nfit_vs_d0_pt"),embFile.Get("hD0RptPiNfit"),"nHitsFit","pion","#pi")
  #drawHists(dataFile.Get("embQA/h2_kaon_nSigmaDedx_vs_d0_pt"),embFile.Get("hD0RptNSigmaK"),"nSigma","Kaon","K")
  #drawHists(dataFile.Get("embQA/h2_pion_nSigmaDedx_vs_d0_pt"),embFile.Get("hD0RptNSigmaPi"),"nSigma","pion","#pi")
  drawHists(dataFile.Get("embQA/h2_kaon_nHitsDedx_vs_d0_pt"),embFile.Get("hD0RptKNhitsDedx"),"nHitsDedx","kaon","K")
  drawHists(dataFile.Get("embQA/h2_pion_nHitsDedx_vs_d0_pt"),embFile.Get("hD0RptPiNhitsDedx"),"nHitsDedx","pion","#pi")
  drawHists(dataFile.Get("embQA/h2_kaon_dca_vs_d0_pt"),embFile.Get("hD0RptKDca"),"dca","kaon","K","(cm)")
  drawHists(dataFile.Get("embQA/h2_pion_dca_vs_d0_pt"),embFile.Get("hD0RptPiDca"),"dca","pion","#pi","(cm)")

  # draw singleTrack-tracking efficiency
  pdf.newPage("single-tracks tracking efficiency(nfit,nfit/nmax,dca)")
  hKaonEff = embFile.Get("hKMcPtRecoEff")
  hPionEff = embFile.Get("hPiMcPtRecoEff")
  gStyle.SetOptTitle(0)
  pdf.newLegend(lx=0.2,ux=0.3)
  histStyle(hKaonEff,"hKaonEff","K",color=3,xtitle="mcP_{T}(GeV/c)",ytitle="Reco. Eff.")
  histStyle(hPionEff,"hPionEff","#pi",color=4,xtitle="mcP_{T}(GeV/c)",ytitle="Reco. Eff.")
  pdf.draw([hKaonEff,hPionEff],legend=True)

  # D0 efficiency
  pdf.newPage("D^{0} accpetance #times tracking efficiency")
  hD0Eff = embFile.Get("hD0RecoEff")
  histStyle(hD0Eff,"hD0Eff","",color=3,xtitle="mcP_{T}(D^{0})(GeV/c)")
  pdf.draw([hD0Eff])

  pdf.close()


if __name__ == '__main__':
	main()
