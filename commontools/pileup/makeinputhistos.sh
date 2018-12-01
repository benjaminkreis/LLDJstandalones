#!/bin/bash

# data json from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGoodLumiSectionsJSONFile gives
# https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt

# makes 

xcs=( \
 "69200" \
 "66017" \
 "72383" \
)

datasets=( \
 "MuonEG"       \
 "DoubleMu"     \
 "DoubleEG"     \
 "SinglePhoton" \
)

for xc in ${xcs[@]}
do
 for dataset in ${datasets[@]}
 do

  echo "working on ${dataset}  ${xc}\n"
 
  pileupCalc.py -i ./${dataset}.json --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec ${xc} --maxPileupBin 75 --numPileupBins 75 ./PU_${dataset}_${xc}.root
  #pileupCalc.py -i ./Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec ${xc} --maxPileupBin 75 --numPileupBins 75 ./data_${xc}.root

 done
done

