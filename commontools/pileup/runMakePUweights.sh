

runPUweights () {
 root -l -b -q 'makePUweights.C("'$1'")'
}

datasets=( \
 "MuonEG"       \
 "DoubleMu"     \
 "DoubleEG"     \
 "SinglePhoton" \
)

for dataset in ${datasets[@]}
do

 runPUweights ${dataset}
 cp puWeights_${dataset}_69200.root ../../analyzers/

done


