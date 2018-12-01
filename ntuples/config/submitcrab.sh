#voms-proxy-init --voms cms --valid 100:00

# do we submit or just generate submit scripts
dosubmit=true
doAOD=true
dominiAOD=false
domakeMiniAOD=false

# start the timer
START=$(date +%s);
printf "Started at ${START}\n\n"

if [ ${dominiAOD} = true ]
then
 nversion="${nversion}MiniAOD"
elif [ ${domakeMiniAOD} = true ]
then
 nversion="${nversion}MakeMiniAOD"
fi

printf "nversion is ${nversion} \n"
printf "configured as \n"
printf " doAOD=${doAOD}, dominiAOD=${dominiAOD}, domakeMiniAOD=${domakeMiniAOD}\n"

# make the directory where we'll submit from
thesubdir="${subdir}/gitignore/${nversion}"
mkdir -p ${thesubdir} 
printf "Making submit configurations in\n ${thesubdir}\n\n"

# copy necessary files into submit directory
if [ ${doAOD} = true ]
then
 dsubmitconfig="run_data_80XAOD.py"
 msubmitconfig="run_mc_80XAOD.py"
 thedasmap="${listdir}/ntuple/dasmapAOD.list"
elif [ ${dominiAOD} = true ]
then
 dsubmitconfig="run_data_80X.py"
 msubmitconfig="run_mc_80X.py"
 thedasmap="${listdir}/ntuple/dasmap.list"
elif [ ${domakeMiniAOD} = true ]
then
 dsubmitconfig="EXO-RunIISummer16MiniAODv2-DATA_cfg.py"
 msubmitconfig="EXO-RunIISummer16MiniAODv2-MC_cfg.py"
 thedasmap="${listdir}/ntuple/dasmapAOD.list"
else
 printf "SOMETHING'S UP --- YOU HAVE doAOD=${doAOD}, dominiAOD=${dominiAOD}, domakeMiniAOD=${domakeMiniAOD}\n"
fi

# copy cmsRun configuration to submit directory
cp "${subdir}/${dsubmitconfig}"  ${thesubdir}
cp "${subdir}/${msubmitconfig}"  ${thesubdir}


# sample names to run over
samples=( \
# put your samples here, copy from below
)

# Signal Samples
#  "ZH_HToSSTobbbb_MS-55_ctauS-1"      \
#  "ZH_HToSSTobbbb_MS-55_ctauS-10"     \
#  "ZH_HToSSTobbbb_MS-55_ctauS-100"    \
#  "ZH_HToSSTobbbb_MS-55_ctauS-1000"   \
#  "ZH_HToSSTobbbb_MS-40_ctauS-1"      \
#  "ZH_HToSSTobbbb_MS-40_ctauS-10"     \
#  "ZH_HToSSTobbbb_MS-40_ctauS-100"    \
#  "ZH_HToSSTobbbb_MS-40_ctauS-1000"   \
#  "ZH_HToSSTobbbb_MS-15_ctauS-1"      \
#  "ZH_HToSSTobbbb_MS-15_ctauS-10"     \
#  "ZH_HToSSTobbbb_MS-15_ctauS-100"    \
#  "ZH_HToSSTobbbb_MS-15_ctauS-1000"   \
#  "ggZH_HToSSTobbbb_MS-55_ctauS-1"    \
#  "ggZH_HToSSTobbbb_MS-55_ctauS-10"   \
#  "ggZH_HToSSTobbbb_MS-55_ctauS-100"  \
#  "ggZH_HToSSTobbbb_MS-55_ctauS-1000" \
#  "ggZH_HToSSTobbbb_MS-40_ctauS-1"    \
#  "ggZH_HToSSTobbbb_MS-40_ctauS-10"   \
#  "ggZH_HToSSTobbbb_MS-40_ctauS-100"  \
#  "ggZH_HToSSTobbbb_MS-40_ctauS-1000" \
#  "ggZH_HToSSTobbbb_MS-15_ctauS-1"    \
#  "ggZH_HToSSTobbbb_MS-15_ctauS-10"   \
#  "ggZH_HToSSTobbbb_MS-15_ctauS-100"  \
#  "ggZH_HToSSTobbbb_MS-15_ctauS-1000" \

# Datasets
#  "Data_SingleEle_H_3"   \
#  "Data_SingleEle_H_2"   \
#  "Data_SingleEle_G"     \
#  "Data_SingleEle_F"     \
#  "Data_SingleEle_E"     \
#  "Data_SingleEle_D"     \
#  "Data_SingleEle_C"     \
#  "Data_SingleEle_B_2"   \

#  "Data_SingleMu_H_3"    \
#  "Data_SingleMu_H_2"    \
#  "Data_SingleMu_G"      \
#  "Data_SingleMu_F"      \
#  "Data_SingleMu_E"      \
#  "Data_SingleMu_D"      \
#  "Data_SingleMu_C"      \
#  "Data_SingleMu_B_2"    \

#  "Data_DoubleMu_H_3"    \
#  "Data_DoubleMu_H_2"    \
#  "Data_DoubleMu_G"      \
#  "Data_DoubleMu_F"      \
#  "Data_DoubleMu_E"      \
#  "Data_DoubleMu_D"      \
#  "Data_DoubleMu_C"      \
#  "Data_DoubleMu_B_2"    \

#  "Data_DoubleEG_H_3"    \
#  "Data_DoubleEG_H_2"    \
#  "Data_DoubleEG_G"      \
#  "Data_DoubleEG_F"      \
#  "Data_DoubleEG_E"      \
#  "Data_DoubleEG_D"      \
#  "Data_DoubleEG_C"      \
#  "Data_DoubleEG_B_2"    \

#  "Data_SinglePhoton_H_3"    \
#  "Data_SinglePhoton_H_2"    \
#  "Data_SinglePhoton_G"      \
#  "Data_SinglePhoton_F"      \
#  "Data_SinglePhoton_E"      \
#  "Data_SinglePhoton_D"      \
#  "Data_SinglePhoton_C"      \
#  "Data_SinglePhoton_B_2"    \

# Main Backgrounds
#  "DY50_1"               \
#  "DY50_2"               \
#  "TTtoLL_1"             \
#  "TTtoLL_2"             \
#  "WJets_1"              \
#  "WJets_2"              \

# Other Backgrounds
#  "TTtoLfromT_1"         \
#  "TTtoLfromT_2"         \
#  "TTtoLfromTbar_1"      \
#  "TTtoLfromTbar_2"      \
#  "STs"                  \
#  "STtbar"               \
#  "STt"                  \
#  "STtbarW_1"            \
#  "STtbarW_2"            \
#  "STtW_1"               \
#  "STtW_2"               \
#  "WWToLNuLNu"           \
#  "WWToLNuQQ_1"          \
#  "WWToLNuQQ_2"          \
#  "WZToLNu2QorQQ2L"      \
#  "WZToLNuNuNu"          \
#  "WZToLLLNu"            \
#  "ZZToNuNuQQ"           \
#  "ZZToLLQQ"             \
#  "ZZToLLNuNu"           \
#  "ZZToLLLL"             \
#  "WG"                   \
#  "ZG"                   \
#  "ZH_Hbb_1"             \
#  "ZH_Hbb_2"             \
#  "ggZH_Hbb_1"           \
#  "ggZH_Hbb_2"           \
#  "ggZH_Hbb_3"           \
#  "GJets_HT40to100_1"    \
#  "GJets_HT40to100_2"    \
#  "GJets_HT100to200_1"   \
#  "GJets_HT100to200_2"   \
#  "GJets_HT200to400_1"   \
#  "GJets_HT200to400_2"   \
#  "GJets_HT400to600_1"   \
#  "GJets_HT400to600_2"   \
#  "GJets_HT600toInf_1"   \
#  "GJets_HT600toInf_2"   \
#  "DY5to50_HT70to100"    \
#  "DY5to50_HT100to200_1" \
#  "DY5to50_HT100to200_2" \
#  "DY5to50_HT200to400_1" \
#  "DY5to50_HT200to400_2" \
#  "DY5to50_HT400to600_1" \
#  "DY5to50_HT400to600_2" \
#  "DY5to50_HT600toInf_1" \
#  "DY5to50_HT600toInf_2" \

# print which samples we're running over
printf "For:\n"
for samplename in ${samples[@]} 
do
 printf " ${samplename}\n"
done

# loop over mc samples
for samplename in ${samples[@]}
do
 printf "\n******************************************************\n"
 if [ ${dosubmit} = true ]
 then
  printf "** \n"
  printf "** --- SUBMITTING --- \n"
  printf "** \n"
 fi
 printf "** Sample: ${samplename} \n"
 printf "******************************************************\n"
 printf "******************************************************\n\n"

 datasetname="$(grep -P ${samplename} ${thedasmap} | sed -n -e "s@ ${samplename}    @@p")"

 submitname="submit_${samplename}"
 submitfile="${thesubdir}/${submitname}.py"

 # set variables for submitting this specific sample
 WORKAREA="'crabsubmits_${nversion}'"

 # check if running data or MC
 if [[ "${samplename:0:4}" == "Data" ]]
 then
  dodata=true
 else
  dodata=false
 fi
 printf "dodata = ${dodata}\n"

 # lumi mask
 LUMIMASK=""
 if [ ${dodata} = true ]
 then
     LUMIMASK="'${PWD}/jsons/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'"
 fi

 # choose correct config parameters
 if [ ${dodata} = true ]
 then 
  if [ ${doAOD} = true ]
  then
   # DATA AOD
   CMSRUNCONFIG="'${dsubmitconfig}'" 
   UPERJOB="50"
  elif [ ${dominiAOD} = true ]
  then
   # DATA miniAOD
   CMSRUNCONFIG="'${dsubmitconfig}'" 
   UPERJOB="100"
  elif [ ${domakeMiniAOD} = true ]
  then
   # DATA makeMiniAOD
   CMSRUNCONFIG="'${dsubmitconfig}'" 
   UPERJOB="100"
  fi
  SPLITTING="'LumiBased'"
 else #if [ ${dodata} = true ]
  if [ ${doAOD} = true ]
  then
   # MC AOD
   CMSRUNCONFIG="'${msubmitconfig}'" 
   UPERJOB="1"
  elif [ ${dominiAOD} = true ]
  then
   # MC miniAOD
   CMSRUNCONFIG="'${msubmitconfig}'" 
   UPERJOB="1"
  elif [ ${domakeMiniAOD} = true ]
  then
   # MC makeMiniAOD
   CMSRUNCONFIG="'${msubmitconfig}'" 
   UPERJOB="1"
  fi
  SPLITTING="'FileBased'"
 fi

 NUNITS="-1"
 REQUESTNAME="'${samplename}'"
 DATASET="'${datasetname}'"
 STORESITE="'T3_US_FNALLPC'"
 OUTLFNBASE="'/store/group/lpchbb/LLDJntuples/${nversion}'"
 MAXMEM="4000"

 printf "WORKAREA      ${WORKAREA}     \n" 
 printf "CMSRUNCONFIG  ${CMSRUNCONFIG} \n" 
 printf "NUNITS        ${NUNITS}       \n" 
 printf "UPERJOB       ${UPERJOB}      \n" 
 printf "SPLITTING     ${SPLITTING}    \n" 
 printf "REQUESTNAME   ${REQUESTNAME}  \n" 
 printf "DATASET       ${DATASET}      \n" 
 printf "LUMIMASK      ${LUMIMASK}     \n" 
 printf "STORESITE     ${STORESITE}    \n" 
 printf "OUTLFNBASE    ${OUTLFNBASE}   \n" 
 printf "MAXMEM        ${MAXMEM}       \n" 

 # copy and then fill template for crab submits
 cp ${subdir}/crab_template.py             "${submitfile}"
 sed -i "s@WORKAREA@${WORKAREA}@g"         "${submitfile}"
 sed -i "s@CMSRUNCONFIG@${CMSRUNCONFIG}@g" "${submitfile}" 
 sed -i "s@NUNITS@${NUNITS}@g"             "${submitfile}" 
 sed -i "s@UPERJOB@${UPERJOB}@g"           "${submitfile}" 
 sed -i "s@SPLITTING@${SPLITTING}@g"       "${submitfile}" 
 sed -i "s@REQUESTNAME@${REQUESTNAME}@g"   "${submitfile}" 
 sed -i "s@DATASET@${DATASET}@g"           "${submitfile}" 
 sed -i "s@LUMIMASK@${LUMIMASK}@g"         "${submitfile}" 
 sed -i "s@STORESITE@${STORESITE}@g"       "${submitfile}" 
 sed -i "s@OUTLFNBASE@${OUTLFNBASE}@g"     "${submitfile}" 
 sed -i "s@MAXMEM@${MAXMEM}@g"             "${submitfile}" 

 # remove lumi mask for mc
 if [ ${dodata} = false ]
 then
     sed -i "/config.Data.lumiMask/d" "${submitfile}"
 fi

 # submit the jobs
 if [ ${dosubmit} = true ]
 then
  pushd ${thesubdir} > /dev/null
  python ${submitfile}
  popd > /dev/null
 fi

done

# end the timer
END=$(date +%s);
printf "\nStarted at ${START}\n"
printf "Ended at   ${END}\n\n"

