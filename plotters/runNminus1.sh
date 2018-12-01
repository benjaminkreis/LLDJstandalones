#!/bin/bash

sels=( \ 
 "A"     \
 "B"     \
 "C"     \
 "D"     \
 "E"     \
 "F"     \
 "G"     \
 "H"     \
 "I"     \
 "J"     \
 "K"     \
 "L"     \
) 

dologs=( \
 "kFALSE" \
 "kTRUE"  \
)

for sel in ${sels[@]}
do
 for dolog in ${dologs[@]}
 do
   root -l -b -q  'Nminus1TagVar.C('\""${sel}"\"', '"${dolog}"')'
 done
done
