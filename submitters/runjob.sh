#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

#get the release setup and in place
#CMSSW_RELEASE_BASE="/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw-patch/CMSSW_8_0_26_patch1"

export SCRAM_ARCH=slc6_amd64_gcc530
scramv1 project CMSSW CMSSW_8_0_26_patch1

cd CMSSW_8_0_26_patch1
cd src
printf "pwd\n"
pwd

cp ../../puWeights_69200_24jan2017.root         .
cp ../../puWeights_DoubleEG_69200.root          .
cp ../../puWeights_DoubleMu_69200.root          .
cp ../../puWeights_MuonEG_69200.root            .
cp ../../puWeights_SinglePhoton_69200.root      .
cp ../../egammaEffi_MoriondBH_eleTight.root     .
cp ../../egammaEffi_MoriondBH_eleMedium.root    .
cp ../../egammaEffi_MoriondBH_eleLoose.root     .
cp ../../feff_ZH.root                           .


scramv1 build -j 10
eval `scramv1 runtime -sh` # cmsenv

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD}

printf "ls -lhrt \n"
ls -lhrt

printf "ls -lhrt ../ \n"
ls -lhrt ../

printf "ls -lhrt ../../ \n"
ls -lhrt ../../

../../runanalyzer.exe -s $1 -l $2 -e $3  -i "../.." -o "../.." -n $4 -a $5 -x $6 $7

printf "ls -lhrt \n"
ls -lhrt

printf "ls -lhrt ../ \n"
ls -lhrt ../

printf "ls -lhrt ../../ \n"
ls -lhrt ../../

