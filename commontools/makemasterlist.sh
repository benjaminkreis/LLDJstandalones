#!/bin/bash

# define output directory where lists will end up
outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"

# read first layer of storage directory save output to temp file
xrdfs root://cmseos.fnal.gov ls ${depot}/${nversion} > templayer1.out

# initialize outfile as empty (overwrite if exists)
echo "" > ${outdir}/allfiles.masterlist

# read subsequent layers into temp files until arrive at root file
for lineone in $(cat templayer1.out);
do
 
 xrdfs root://cmseos.fnal.gov ls ${lineone} > templayer2.out  
 echo "Text read from file: ${lineone}"
 for linetwo in $(cat templayer2.out)
 do
 
  xrdfs root://cmseos.fnal.gov ls ${linetwo} > templayer3.out
  for linethree in $(cat templayer3.out)
  do
  
   xrdfs root://cmseos.fnal.gov ls ${linethree} > templayer4.out
   for linefour in $(cat templayer4.out)
   do 
   
   xrdfs root://cmseos.fnal.gov ls ${linefour} >> ${outdir}/allfiles.masterlist 
   done
  done
 done
done

#remove bad entries from masterlist
sed -i '/log/d' ${outdir}/allfiles.masterlist
sed -i '/failed/d' ${outdir}/allfiles.masterlist
#save master list and remove junk files
mv templayer1.out ${outdir}/dir.out
rm templayer2.out
rm templayer3.out
rm templayer4.out
