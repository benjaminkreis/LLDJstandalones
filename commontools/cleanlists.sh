#!/bin/bash

# delete anything in our "list" that doesn't have .root at the end

for sample in $(ls ${listdir}/*.list)

do

 printf "%s\n" ${sample}
 sed -ne '/root/p' ${sample} > ${listdir}/temp && mv ${listdir}/temp ${sample}

done # for sample in DY50
