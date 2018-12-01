#!\bin\bash

destination="/store/group/lpchbb/LLDJntuples/${nversion}/analyzed/${aversion}/"
eos root://cmseos.fnal.gov mkdir -p  ${destination} 

source="${CMSSW_BASE}/src/LLDJstandalones/roots/${aversion}"

## copy root files over 

# copy over the directory - buggy?
#xrdcp -r ${source}  root://cmseos.fnal.gov/${destination}

# copy over file by file
ls $source > tmp.txt

cptoeos() {
 xrdcp ${source}/$1  root://cmseos.fnal.gov/${destination}
 #echo "${source}/$1" 
}

while IFS='' read -r line || [[ -n "$line" ]]; do
 cptoeos $line
done < tmp.txt

# copy info file over
aboutsource="${CMSSW_BASE}/src/LLDJstandalones/submitters/gitignore/${aversion}"
xrdcp ${aboutsource}/about.txt  root://cmseos.fnal.gov/${destination}
