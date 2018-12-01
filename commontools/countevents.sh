#!/bin/bash

outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"

xcDY10to50="18610.0"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z
#Other ref: https://cms-pdmv.cern.ch/mcm/requests?prepid=*GS*&dataset_name=DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8&page=0&shown=524415
#Other ref: https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DDYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

xcDY50="6100.8" #5765.4 * 1.05
#xcDY50="5765.4"
#Ref: https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DDYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV FEWZ 3.1.b2 1921.8*3

xcDY5to50_HT70To100="301.2"  # +-0.8  
xcDY5to50_HT100To200="224.2" # +- 5.7
xcDY5to50_HT200To400="37.2"  # +- 1.1
xcDY5to50_HT400To600="3.581" # +-0.118 
xcDY5to50_HT600ToInf="1.124" # +-0.038 
#Ref: LO https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z             

xcGJets_HT40To100="26195.4"    # 1.26*20790+-9                 
xcGJets_HT100To200="11639.88"  # 1.26*9238+-4              
xcGJets_HT200To400="2904.3"    # 1.26*2305+-0.7               
xcGJets_HT400To600="345.744"   # 1.26*274.4+-0.2               
xcGJets_HT600ToInf="117.7596"  # 1.26*93.46+-0.06            
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z
#1.26 from http://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2015_224_v23.pdf

xcST_s="3.36"       #+0.13 -0.12 NLO
xcSTbar_t="26.38"   # +1.32-1.18
xcST_t="44.33"      # +1.76-1.49
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcSTbar_tW="19.56"
xcST_tW="35.6"
#Ref for other value (35.85 +-0.9, +-1.7 NNLO): https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns 

xcTTJets="831.76"   #NNLO
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcTTtoLL="87.31"  #NNLO        
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcTTtoLfromT="182.7"      
xcTTtoLfromTbar="182.7"   
#NEED PRIMARY REFERENCE
#Other ref: 114 https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DTTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
#Other ref: https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO

xcWW="118.7"      
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive
#Old value: xcWW="10.32"      

xcZZ="16.523"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
#Old value: xcZZ="63.0"

xcWZ="47.13"                  
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
#Old value: xcWZ="118.7"                  

xcWWToLNuQQ="49.997"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns 

xcWWToLNuLNu="12.178"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcWZToL3Nu="3.03"                         
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcWZTo3LNu="4.42965"                         
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcWZToLNu2QorQQ2L="9.82423165827" 
#Ref: https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DWZToLNu2QorQQ2L_aTGC_13TeV-madgraph-pythia8

xcZZToNuNuQQ="4.04"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcZZToLLQQ="3.22"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcZZToLLNuNu="0.5644"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
#Ref: https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DZZTo2L2Nu_13TeV_powheg_pythia8

xcZZToLLLL="1.256"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcWG="405.271"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcZG="117.864"
#Ref: ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8

xcZH_HToBB_ZToLL="0.044333"
xcggZH_HToBB_ZToLL="0.0071462"
xcggZH_HToSSTobbbb="0.0024783"      
xcZH_HToSSTobbbb="0.015374718"      
#https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt13TeV#ZH_Process
#BR(HToSSTobbbb)~20%, BR(ZToll)~10.099%, BR(HToBB)~0.5767

xcWJetsToLNu="74447.3"   
#xcWJetsToLNu="61526.7" * 1.21  
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets                  

#xcQCD_HT50to100 can't find value on McM or SummaryTable1G25ns twiki
xcQCD_HT100to200="35267400" #1.26*27990000
xcQCD_HT200to300="2157120" #1.26*1712000
xcQCD_HT300to500="438102" #1.26*347700
xcQCD_HT500to700="40446" #1.26*32100
xcQCD_HT700to1000="8607.06" #1.26*6831
xcQCD_HT1000to1500="1520.82" #1.26*1207
xcQCD_HT1500to2000="151.074" #1.26*119.9
xcQCD_HT2000toInf="31.8024" #1.26*25.24
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD
#1.26 from http://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2015_224_v23.pdf

countalist () {
 printf "Making %s\n" $1
 if [[ $1 == "Data"* ]]
 then
  printf "nrevents: 1.0\n"  > ${listdir}/$1.info
  printf "crosssection: 1.0" >> ${listdir}/$1.info
 else
  root -l -b -q 'countevents.cxx("'$1'")'
  printf "crosssection: %s\n" $2 >> ${listdir}/$1.info
 fi
}



## Data
countalist "Data_SingleMu_H_3"      
countalist "Data_SingleMu_H_2"      
countalist "Data_SingleMu_G"        
#countalist "Data_SingleMu_F"        
#countalist "Data_SingleMu_E"        
#countalist "Data_SingleMu_D"        
#countalist "Data_SingleMu_C"        
#countalist "Data_SingleMu_B_2"      

countalist "Data_SingleEle_H_3"     
countalist "Data_SingleEle_H_2"     
countalist "Data_SingleEle_G"       
#countalist "Data_SingleEle_F"       
#countalist "Data_SingleEle_E"       
#countalist "Data_SingleEle_D"       
#countalist "Data_SingleEle_C"       
#countalist "Data_SingleEle_B_2"     

countalist "Data_DoubleMu_H_3"      
countalist "Data_DoubleMu_H_2"      
countalist "Data_DoubleMu_G"        
#countalist "Data_DoubleMu_F"        
#countalist "Data_DoubleMu_E"        
#countalist "Data_DoubleMu_D"        
#countalist "Data_DoubleMu_C"        
#countalist "Data_DoubleMu_B_2"      

countalist "Data_DoubleEG_H_3"      
countalist "Data_DoubleEG_H_2"      
countalist "Data_DoubleEG_G"        
#countalist "Data_DoubleEG_F"        
#countalist "Data_DoubleEG_E"        
#countalist "Data_DoubleEG_D"        
#countalist "Data_DoubleEG_C"        
#countalist "Data_DoubleEG_B_2"      

countalist "Data_MuonEG_H_3"        
countalist "Data_MuonEG_H_2"        
countalist "Data_MuonEG_G"          
#countalist "Data_MuonEG_F"          
#countalist "Data_MuonEG_E"          
#countalist "Data_MuonEG_D"          
#countalist "Data_MuonEG_C"          
#countalist "Data_MuonEG_B_2"        

countalist "Data_SinglePhoton_H_3"  
countalist "Data_SinglePhoton_H_2"  
countalist "Data_SinglePhoton_G"    
#countalist "Data_SinglePhoton_F"    
#countalist "Data_SinglePhoton_E"    
#countalist "Data_SinglePhoton_D"    
#countalist "Data_SinglePhoton_C"    
#countalist "Data_SinglePhoton_B_2"  

## MC backgrounds

# DY
countalist "DYJetsToLL_M-5to50_HT-70to100"     ${xcDY5to50_HT70To100}   
countalist "DYJetsToLL_M-5to50_HT-100to200"    ${xcDY5to50_HT100To200}  
countalist "DYJetsToLL_M-5to50_HT-200to400"    ${xcDY5to50_HT200To400}  
countalist "DYJetsToLL_M-5to50_HT-400to600"    ${xcDY5to50_HT400To600}  
countalist "DYJetsToLL_M-5to50_HT-600toInf"    ${xcDY5to50_HT600ToInf}  
countalist "DYJetsToLL_M-10to50"               ${xcDY10to50}            
countalist "DYJetsToLL_M-50"                   ${xcDY50}                

# WJets
countalist "WJetsToLNu"     ${xcWJetsToLNu}                      

# TTbar
countalist "TTJets"         ${xcTTJets}
countalist "TTtoLL"         ${xcTTtoLL}        
countalist "TTtoLfromTbar"  ${xcTTtoLfromTbar} 
countalist "TTtoLfromT"     ${xcTTtoLfromT}    

# Single Top
countalist  "ST_s-channel_4f_leptonDecays"             ${xcST_s}
countalist  "ST_t-channel_antitop_4f_inclusiveDecays"  ${xcSTbar_t}
countalist  "ST_t-channel_top_4f_inclusiveDecays"      ${xcST_t}
countalist  "ST_tW_antitop_5f_NoFullyHadronicDecays"   ${xcSTbar_tW}
countalist  "ST_tW_top_5f_NoFullyHadronicDecays"       ${xcST_tW}

# GJets
countalist "GJets_HT-40To100"      ${xcGJets_HT40To100}  
countalist "GJets_HT-100To200"     ${xcGJets_HT100To200} 
countalist "GJets_HT-200To400"     ${xcGJets_HT200To400} 
countalist "GJets_HT-400To600"     ${xcGJets_HT400To600} 
countalist "GJets_HT-600ToInf"     ${xcGJets_HT600ToInf} 

# Diboson
countalist "WW"                 ${xcWW} 
countalist "WZ"                 ${xcWZ} 
countalist "ZZ"                 ${xcZZ} 
countalist "WWTo2L2Nu"          ${xcWWToLNuLNu}     
countalist "WWToLNuQQ"          ${xcWWToLNuQQ}      
countalist "WZTo1L3Nu"          ${xcWZToL3Nu}       
countalist "WZTo3LNu"           ${xcWZTo3LNu}       
countalist "WZToLNu2QorQQ2L"    ${xcWZToLNu2QorQQ2L}
countalist "ZZTo2L2Nu"          ${xcZZToLLNuNu}     
countalist "ZZTo2L2Q"           ${xcZZToLLQQ}       
countalist "ZZTo2Q2Nu"          ${xcZZToNuNuQQ}     
countalist "ZZTo4L"             ${xcZZToLLLL}       

# VGamma
countalist "ZGTo2LG"              ${xcZG} 
countalist "WGToLNuG"             ${xcWG} 

# ZH
countalist "ggZH_HToBB_ZToLL"      ${xcggZH_HToBB_ZToLL} 
countalist "ZH_HToBB_ZToLL"        ${xcZH_HToBB_ZToLL}   

# QCD
countalist "QCD_HT100to200"       ${xcQCD_HT100to200}
countalist "QCD_HT200to300"       ${xcQCD_HT200to300}
countalist "QCD_HT300to500"       ${xcQCD_HT300to500}
countalist "QCD_HT500to700"       ${xcQCD_HT500to700}
countalist "QCD_HT700to1000"      ${xcQCD_HT700to1000}
countalist "QCD_HT1000to1500"     ${xcQCD_HT1000to1500}
countalist "QCD_HT1500to2000"     ${xcQCD_HT1500to2000}
countalist "QCD_HT2000toInf"      ${xcQCD_HT2000toInf}

# Signal Samples
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1"     ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10"    ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100"   ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000"  ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1"     ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10"    ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100"   ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000"  ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1"     ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10"    ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100"   ${xcZH_HToSSTobbbb}
countalist "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000"  ${xcZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1"      ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10"     ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100"    ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000"   ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1"      ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10"     ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100"    ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000"   ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1"      ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10"     ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100"    ${xcggZH_HToSSTobbbb}
countalist "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000"   ${xcggZH_HToSSTobbbb}

