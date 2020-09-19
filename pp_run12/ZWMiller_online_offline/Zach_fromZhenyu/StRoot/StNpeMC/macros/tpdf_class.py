#!/usr/bin/python
from ROOT import TCanvas, gStyle, TPaveText, TPDF, TPad, TLegend

class pdf_class:
  def __init__(self,filename):
    self._canvas = TCanvas("canvas","canvas",800,450)
    self._canvas.cd()
    self._pad = TPad("pad","",0,0,1,0.95)
    self._pdf = TPDF("%s.pdf"%filename)

    self._subCanvas = 0
    self._nCanvasPerPage = 0
    self._nx = 1
    self._ny = 1

  def newPage(self,headerText="",nx=1,ny=1,sameHeader=False):
    if self._subCanvas != 0:
      self._pad.Draw()
      self._canvas.cd()
      self._canvas.Update()
      self._pdf.NewPage()

    self._pad.Clear()
    self._canvas.cd()
    if not sameHeader:
      self._nx = nx
      self._ny = ny
      self._header = TPaveText(0,0.95,1,1)
      self._header.SetFillColor(0)
      self._header.SetTextColor(1)
      self._header.SetTextFont(22)
      self._header.AddText(headerText)
      self._header.AddLine(0.0,0.95,1.0,0.95)
    self._header.Draw()
    self._pad.cd()
    self._pad.Divide(self._nx,self._ny)
    self._pad.SetGrid(0,0)
    self._nCanvasPerPage = self._nx*self._ny
    self._subCanvas = 0

  def newLegend(self,header="",lx=0.8,ly=0.8,ux=0.9,uy=0.88):
    self._legend = TLegend(lx,ly,ux,uy)
    self._legend.SetFillColor(0)
    self._legend.SetBorderSize(0)
    self._legend.SetTextFont(132)
    self._legend.SetTextSize(0.035)
    if header != "": self._legend.SetHeader(header)
    
  def draw(self,hists,legend=False,drawOpt="",logx=False,logy=False,logz=False):
    if self._subCanvas+1 > self._nCanvasPerPage:
      self.newPage(sameHeader=True)

    self._subCanvas +=1 
    self._pad.cd(self._subCanvas)
    first = 1
    for h in hists:
      if first == 1:
        first = 0
        h.Draw(drawOpt)
      else:
        h.Draw("same%s"%drawOpt)
      if legend: self._legend.AddEntry(h,h.GetTitle(),"LP")

    if legend: self._legend.Draw()
    if logx: self._pad.cd(self._subCanvas).SetLogx()
    if logy: self._pad.cd(self._subCanvas).SetLogy()
    if logz: self._pad.cd(self._subCanvas).SetLogz()

    self._canvas.cd()
    self._canvas.Update()
    self._pad.Draw()

  def close(self):
    self._pad.Draw()
    self._canvas.cd()
    self._canvas.Update()
    self._pdf.Close()
