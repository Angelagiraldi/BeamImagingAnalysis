#!/bin/bash
cd $1
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
rm -r web/Fill6016
python makeHtml.py navigation res/hist/Fill6016_first.json noCorr SG DG TG SupG SupDG -b
python makeHtml.py summary res/hist/Fill6016_first.json SG DG TG SupG SupDG -b
python makeHtml.py plots res/hist/Fill6016_first.json noCorr 0 1 2 3 4 -b
python makeHtml.py plots res/hist/Fill6016_first.json SG 0 1 2 3 4 -b
python makeHtml.py plots res/hist/Fill6016_first.json DG 0 1 2 3 4 -b
python makeHtml.py plots res/hist/Fill6016_first.json TG 0 1 2 3 4 -b
python makeHtml.py plots res/hist/Fill6016_first.json SupG 0 1 2 3 4 v2 -b
python makeHtml.py plots res/hist/Fill6016_first.json SupDG 0 1 2 3 4 v3 -b
