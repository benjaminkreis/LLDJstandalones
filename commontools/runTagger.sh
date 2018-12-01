lifetime="ctauS-10"
mass="MS-40"
ntags=2
name=$lifetime'_nt'$ntags
lifetime2='"'$lifetime'"'
mass2='"'$mass'"'

mkdir -p "${plotdir}"/"${aversion}"/tagger/"taggerResults"
mkdir -p "${plotdir}"/"${aversion}"/tagger/"taggerResults/"$mass
mkdir -p "${plotdir}"/"${aversion}"/tagger/$lifetime
outpath="${plotdir}"/"${aversion}"/tagger/"taggerResults/"$mass
c_al=(0.01 0.025 0.05 0.075 0.1 0.15 0.175 0.2 0.35 0.5 0.75)
c_ip=(0.5 0.75 0.9 1.0 1.15 1.25 1.5 1.75 2.0 2.5 2.75)
c_ta=(-3.0 -2.5 -2.25 -2.10 -2.0 -1.9 -1.75 -1.5 -1.25 -1.0 -0.75)

#remove old files if script was interrupted before completeing
rm -f $name.txt
rm -f temp.txt
rm -f temp2.txt
rm -f temp3.txt
rm -f temp4.txt

touch temp.txt
touch temp2.txt
touch temp4.txt
touch $name.txt
rm $outpath/$name.txt
tail -f temp2.txt &
for i in {0..0}
do
   for j in {0..0}
   do
      for k in {0..0}
      do
         echo ${c_ip[i]} ${c_ta[j]} ${c_al[k]}>>temp2.txt
         root -l -b -q "tagger.C(${c_ip[i]},${c_ta[j]}, ${c_al[k]}, $ntags,  $lifetime2, $mass2 )" >>temp.txt
      done
   done
done
awk '($1 !="Processing"){print}' temp.txt> temp3.txt
sed -i '/^$/d' temp3.txt
paste  temp2.txt temp3.txt >>temp4.txt
awk 'BEGIN {printf("%-9s %-9s %-9s %-13s %-13s %-15s  %-18s %-18s %-18s %-18s\n", \
                   "c_ip", "c_ta", "c_al", "Nsig", "Nbkg", "S/sqrt(S+B)", "S/sqrt(S+B+0.1B)", "S/sqrt(S+B+0.5B)", "S/sqrt(S+B+1.0B)", "S/sqrt(S+B+2.0B)")}
           {printf "%-9.2f %-9.2f %-9.2f %-13.6f %-13.6f", \
                    $1, $2, $3, $5, $7;
           if($5==0 && $7==0) printf "%-15.6f %-18.6f %-18.6f %-18.6f %-18.6f\n", 0, 0, 0, 0, 0; 
           else printf "%-15.6f %-18.6f %-18.6f %-18.6f %-18.6f\n", $5/sqrt($5 +$7), $5/sqrt($5 +$7 +0.1*$7), $5/sqrt($5 +$7 +0.5*$7), $5/sqrt($5 +$7 +1.0*$7), $5/sqrt($5 +$7 +2.0*$7) }' \
           temp4.txt >$name.txt

(head -n 1 $name.txt && tail -n +2 $name.txt | sort -k6 -nr) > $name_s.txt 
mv $name_s.txt $outpath/$name.txt
echo "created" $outpath/$name.txt
rm $name.txt
rm temp.txt
rm temp2.txt
rm temp3.txt
rm temp4.txt
echo "Finished"
