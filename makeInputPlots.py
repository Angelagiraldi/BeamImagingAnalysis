import ROOT
from lib.plot.plot import ColorBase
ColorBase.kBird()
tfile = ROOT.TFile.Open("/afs/cern.ch/user/a/angirald/workspace/CMSSW_10_3_2/src/BeamImagingAnalysis/beamimaging/Fill4954_rereco_1X.root")
ttree = tfile.Get("Beam1MoveX_bunch872Add")
text = ROOT.TLatex()
text.SetNDC()
text.SetTextFont(62)
text.SetTextSize(0.0375)
text.SetTextAlign(13)
for i in range(19):
    hist = ROOT.TH2F('hist{}'.format(i), '', 50, 0.0, 0.12, 50, 0.04, 0.16)
    hist.GetZaxis().SetRangeUser(1.0, 400.0)
    ttree.Draw('vtx_y:vtx_x>>hist{}'.format(i), 'vtx_nTrk>14 && scanstep=={}'.format(i+1), 'goff')
    plot = ColorBase(hist)
    plot._xtitle = 'x [cm]'
    plot._ytitle = 'y [cm]'
    plot.draw()
    plot.SetLogz()
    text.DrawLatex(0.15, 0.88, 'Scan 1X, step {}'.format(i))
    plot.Update()
    plot.SaveAs('Fill4954_rereco_1X_bcid872_step{}.png'.format(i))
    plot.Close()
print 'convert -delay 20 -loop 0 Fill4954_rereco_1X_bcid872_step{0..18}.png Fill4954_rereco_1X_bcid872_allsteps.gif'
