#!/bin/bash

hadd $rootdir/$aversion/Data_DoubleEG_HIP_DY_histograms.root\
 $rootdir/$aversion/Data_DoubleEG_B_2_DY_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_C_DY_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_D_DY_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_E_DY_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_F_DY_histograms.root \

echo "done with DY"
echo " "

hadd $rootdir/$aversion/Data_DoubleEG_HIP_NoSel_histograms.root\
 $rootdir/$aversion/Data_DoubleEG_B_2_NoSel_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_C_NoSel_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_D_NoSel_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_E_NoSel_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_F_NoSel_histograms.root \

echo "done with NoSel"
echo " "

hadd $rootdir/$aversion/Data_DoubleEG_HIP_NoPair_histograms.root\
 $rootdir/$aversion/Data_DoubleEG_B_2_NoPair_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_C_NoPair_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_D_NoPair_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_E_NoPair_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_F_NoPair_histograms.root \

echo "done with NoPair"
echo " "

hadd $rootdir/$aversion/Data_DoubleEG_HIP_OffZ_histograms.root\
 $rootdir/$aversion/Data_DoubleEG_B_2_OffZ_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_C_OffZ_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_D_OffZ_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_E_OffZ_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_F_OffZ_histograms.root \

echo "done with OffZ"
echo " "

hadd $rootdir/$aversion/Data_DoubleEG_HIP_CRHeavy_histograms.root\
 $rootdir/$aversion/Data_DoubleEG_B_2_CRHeavy_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_C_CRHeavy_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_D_CRHeavy_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_E_CRHeavy_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_F_CRHeavy_histograms.root \

echo "done with CRHeavy"
echo " "

hadd $rootdir/$aversion/Data_DoubleEG_HIP_CRLight_histograms.root\
 $rootdir/$aversion/Data_DoubleEG_B_2_CRLight_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_C_CRLight_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_D_CRLight_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_E_CRLight_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_F_CRLight_histograms.root \

echo "done with CRLight"
echo " "

hadd $rootdir/$aversion/Data_DoubleEG_HIP_ZH_histograms.root\
 $rootdir/$aversion/Data_DoubleEG_B_2_ZH_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_C_ZH_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_D_ZH_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_E_ZH_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_F_ZH_histograms.root \

echo "done with ZH"
echo " "

hadd $rootdir/$aversion/Data_DoubleEG_HIP_Sig_histograms.root\
 $rootdir/$aversion/Data_DoubleEG_B_2_Sig_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_C_Sig_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_D_Sig_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_E_Sig_histograms.root \
 $rootdir/$aversion/Data_DoubleEG_F_Sig_histograms.root \

echo "done with Sig"
echo " "
