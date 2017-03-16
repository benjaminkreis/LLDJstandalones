#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

#get the release setup and in place
tar -xzf $1.tar.gz
cd $1/
mkdir -p src
cd src
scramv1 build ProjectRename
#scramv1 build
eval `scramv1 runtime -sh` # cmsenv

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD}

printf "ls -lhrt \n"
ls -lhrt

printf "ls -lhrt ../ \n"
ls -lhrt ../

printf "ls -lhrt ../../ \n"
ls -lhrt ../../

../../runanalyzer.exe -s $2 -l $3 -e $4 -j $5 -i "../.." -o "../.." 

printf "ls -lhrt \n"
ls -lhrt

printf "ls -lhrt ../ \n"
ls -lhrt ../

printf "ls -lhrt ../../ \n"
ls -lhrt ../../

