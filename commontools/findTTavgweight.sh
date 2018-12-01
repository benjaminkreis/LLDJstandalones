#!/bin/bash

findweight () {
 printf "Making %s\n" $1
 if [[ $1 == "TT"* ]]
 then
  root -l -b -q 'findTTavgweight.cxx("'$1'")'
 fi
}

# TTbar
findweight "TTJets"         
findweight "TTtoLL"         
findweight "TTtoLfromTbar"  
findweight "TTtoLfromT"     

