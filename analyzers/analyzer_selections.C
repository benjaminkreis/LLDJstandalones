#include "analyzer_selections.h"

//----------------------------analyzer_selections
analyzer_selections::analyzer_selections() 
{
}

//----------------------------~analyzer_selections
analyzer_selections::~analyzer_selections()
{
}

void analyzer_selections::clearSelections()
{

 selvecBaseSig     .clear() ;   
 selvecBaseZH      .clear() ;   
 selvecBaseDY      .clear() ;   
 selvecBaseOffZ    .clear() ;   
 selvecBaseNoPair  .clear() ;

 selvecOneEleSig   .clear() ;   
 selvecTwoEleSig   .clear() ;   
 selvecOneMuSig    .clear() ;   
 selvecTwoMuSig    .clear() ;   
 selvecOneEleDY    .clear() ;   
 selvecTwoEleDY    .clear() ;   
 selvecOneMuDY     .clear() ;   
 selvecTwoMuDY     .clear() ;   
 selvecOneEleZH    .clear() ;   
 selvecTwoEleZH    .clear() ;   
 selvecOneMuZH     .clear() ;   
 selvecTwoMuZH     .clear() ;   
 selvecOneEleOffZ  .clear() ;   
 selvecTwoEleOffZ  .clear() ;   
 selvecOneMuOffZ   .clear() ;   
 selvecTwoMuOffZ   .clear() ;   
 selvecOneEleNoPair.clear() ; 
 selvecOneMuNoPair .clear() ;   
 selvecEleMuOSOF   .clear() ;   
 selvecEleMuOSOFL  .clear() ;   
 selvecOnePho      .clear() ;

 bitsPassOneEleSig   = 0;
 bitsPassTwoEleSig   = 0;
 bitsPassOneMuSig    = 0;
 bitsPassTwoMuSig    = 0;
 bitsPassOneEleDY    = 0;
 bitsPassTwoEleDY    = 0;
 bitsPassOneMuDY     = 0;
 bitsPassTwoMuDY     = 0;
 bitsPassOneEleZH    = 0;
 bitsPassTwoEleZH    = 0;
 bitsPassOneMuZH     = 0;
 bitsPassTwoMuZH     = 0;
 bitsPassOneEleOffZ  = 0;
 bitsPassTwoEleOffZ  = 0;
 bitsPassOneMuOffZ   = 0;
 bitsPassTwoMuOffZ   = 0;
 bitsPassOneEleNoPair= 0;
 bitsPassOneMuNoPair = 0;
 bitsPassEleMuOSOF   = 0;
 bitsPassEleMuOSOFL  = 0;
 bitsPassOnePho      = 0;

 keyPassOneEleSig   = 0;
 keyPassTwoEleSig   = 0;
 keyPassOneMuSig    = 0;
 keyPassTwoMuSig    = 0;
 keyPassOneEleDY    = 0;
 keyPassTwoEleDY    = 0;
 keyPassOneMuDY     = 0;
 keyPassTwoMuDY     = 0;
 keyPassOneEleZH    = 0;
 keyPassTwoEleZH    = 0;
 keyPassOneMuZH     = 0;
 keyPassTwoMuZH     = 0;
 keyPassOneEleOffZ  = 0;
 keyPassTwoEleOffZ  = 0;
 keyPassOneMuOffZ   = 0;
 keyPassTwoMuOffZ   = 0;
 keyPassOneEleNoPair= 0;
 keyPassOneMuNoPair = 0;
 keyPassEleMuOSOF   = 0;
 keyPassEleMuOSOFL  = 0;
 keyPassOnePho      = 0;


}

void analyzer_selections::setSelections()
{

 // base selections (no trigger)
 selvecBaseSig  .push_back( passGoodVtx );
 selvecBaseSig  .push_back( passZWindow );
 selvecBaseSig  .push_back( passPTOSSF  );
 selvecBaseSig  .push_back( passOneTag  );

 selvecBaseZH   .push_back( passGoodVtx );
 selvecBaseZH   .push_back( passZWindow );
 selvecBaseZH   .push_back( passPTOSSF  );
 selvecBaseZH   .push_back( passOneJet  );

 selvecBaseDY      .push_back( passGoodVtx );
 selvecBaseDY      .push_back( passZWindow );
 selvecBaseDY      .push_back( !passPTOSSF );
 selvecBaseDY      .push_back( passOneJet  );

 selvecBaseOffZ    .push_back( passGoodVtx  );
 selvecBaseOffZ    .push_back( !passZWindow );
 selvecBaseOffZ    .push_back( passOSSF     );
 selvecBaseOffZ    .push_back( passOneJet   );

 selvecBaseNoPair  .push_back( passGoodVtx  );
 selvecBaseNoPair  .push_back( !passZWindow );
 selvecBaseNoPair  .push_back( !passOSSF    );
 selvecBaseNoPair  .push_back( passOneJet   );

 // full selections
 // signal
 selvecOneEleSig   .push_back( passSingleEle  ) ;   
 selvecTwoEleSig   .push_back( passDoubleEle  ) ;   
 selvecOneMuSig    .push_back( passSingleMu   ) ;   
 selvecTwoMuSig    .push_back( passDoubleMu   ) ;   
 for(unsigned int b=0; b<selvecBaseSig.size(); ++b)
 {
  selvecOneEleSig   .push_back( selvecBaseSig.at(b) ) ;   
  selvecTwoEleSig   .push_back( selvecBaseSig.at(b) ) ;   
  selvecOneMuSig    .push_back( selvecBaseSig.at(b) ) ;   
  selvecTwoMuSig    .push_back( selvecBaseSig.at(b) ) ;   
 }
 // DY
 selvecOneEleDY    .push_back( passSingleEle  ) ;   
 selvecTwoEleDY    .push_back( passDoubleEle  ) ;   
 selvecOneMuDY     .push_back( passSingleMu   ) ;   
 selvecTwoMuDY     .push_back( passDoubleMu   ) ;   
 for(unsigned int b=0; b<selvecBaseDY.size(); ++b)
 {
  selvecOneEleDY   .push_back( selvecBaseDY.at(b) ) ;   
  selvecTwoEleDY   .push_back( selvecBaseDY.at(b) ) ;   
  selvecOneMuDY    .push_back( selvecBaseDY.at(b) ) ;   
  selvecTwoMuDY    .push_back( selvecBaseDY.at(b) ) ;   
 }
 // ZH
 selvecOneEleZH    .push_back( passSingleEle  ) ;   
 selvecTwoEleZH    .push_back( passDoubleEle  ) ;   
 selvecOneMuZH     .push_back( passSingleMu   ) ;   
 selvecTwoMuZH     .push_back( passDoubleMu   ) ;   
 for(unsigned int b=0; b<selvecBaseZH.size(); ++b)
 {
  selvecOneEleZH   .push_back( selvecBaseZH.at(b) ) ;   
  selvecTwoEleZH   .push_back( selvecBaseZH.at(b) ) ;   
  selvecOneMuZH    .push_back( selvecBaseZH.at(b) ) ;   
  selvecTwoMuZH    .push_back( selvecBaseZH.at(b) ) ;   
 }
 // OffZ
 selvecOneEleOffZ  .push_back( passSingleEle  ) ;   
 selvecTwoEleOffZ  .push_back( passDoubleEle  ) ;   
 selvecOneMuOffZ   .push_back( passSingleMu   ) ;   
 selvecTwoMuOffZ   .push_back( passDoubleMu   ) ;   
 for(unsigned int b=0; b<selvecBaseOffZ.size(); ++b)
 {
  selvecOneEleOffZ   .push_back( selvecBaseOffZ.at(b) ) ;   
  selvecTwoEleOffZ   .push_back( selvecBaseOffZ.at(b) ) ;   
  selvecOneMuOffZ    .push_back( selvecBaseOffZ.at(b) ) ;   
  selvecTwoMuOffZ    .push_back( selvecBaseOffZ.at(b) ) ;   
 }
 // NoPair
 selvecOneEleNoPair.push_back( passSingleEle  ) ; 
 selvecOneMuNoPair .push_back( passSingleMu   ) ;   
 for(unsigned int b=0; b<selvecBaseNoPair.size(); ++b)
 {
  selvecOneEleNoPair   .push_back( selvecBaseNoPair.at(b) ) ;   
  selvecOneMuNoPair    .push_back( selvecBaseNoPair.at(b) ) ;   
 }
 // EleMu OSOF
 selvecEleMuOSOF .push_back( passMuEG     );
 selvecEleMuOSOF .push_back( passGoodVtx  );
 selvecEleMuOSOF .push_back( passOneJet   );
 selvecEleMuOSOF .push_back( passPTOSOF  && passZWinOSOF );
 // EleMu OSOF LowPt
 selvecEleMuOSOFL .push_back( passMuEG     );
 selvecEleMuOSOFL .push_back( passGoodVtx  );
 selvecEleMuOSOFL .push_back( passOneJet   );
 selvecEleMuOSOFL .push_back( (!passPTOSOF)  && passZWinOSOF );
 // One Photon
 selvecOnePho .push_back( passSinglePho);
 selvecOnePho .push_back( passGoodVtx  );
 selvecOnePho .push_back( passOneJet && muon_list.size()==0 && electron_list.size()==0 );
}

Int_t analyzer_selections::setSelKey( std::vector<Bool_t> selvec ) 
{

 Int_t bitset = 0;
 // individual selections
 for(unsigned int i=0; i<selvec.size(); ++i){
  bitset |= (1 << i+1); 
 }
 // set first bit for pass all selections
 bitset |= 1 << 0 ;
 
 return bitset;

}

Int_t analyzer_selections::setSelBits( std::vector<Bool_t> selvec, int &counter)
{
 
 Int_t bitset = 0;
 Bool_t passall=kTRUE;
 // individual selections
 for(unsigned int i=0; i<selvec.size(); ++i){
  if(selvec[i]==0) passall=kFALSE;
  bitset |= (selvec[i] << i+1); 
 }
 // set first bit for pass all selections
 bitset |= passall << 0 ;

 // increment counters
 if( passall ) counter++;

 return bitset;
}

// trigger ------------------------
Bool_t analyzer_selections::askPassSingleEle()
{
 Bool_t doespass = kFALSE;
 if(electron_list.size()>0){ 
   //if(isMC) doespass = kTRUE;
   //else doespass = (Bool_t)( (AOD_HLT_Ele23Loose > 0) || (AOD_HLT_Ele27Tight > 0) );
   doespass = (Bool_t)( (AOD_HLT_Ele23Loose > 0) || (AOD_HLT_Ele27Tight > 0) );
 } 
 return doespass;
}

Bool_t analyzer_selections::askPassDoubleEle()
{
 Bool_t doespass = kFALSE;
 if(electron_list.size()>1){ 
  //if(isMC) doespass = kTRUE;
  //else doespass = (Bool_t)((AOD_HLT_Ele23Ele12 > 0) );
  doespass = (Bool_t)( (AOD_HLT_Ele23Ele12 > 0) ); 
 } 
 return doespass;
}

Bool_t analyzer_selections::askPassSingleMu()
{
 Bool_t doespass = kFALSE;
 if(muon_list.size()>0){ 
  //if(isMC) doespass = kTRUE;
  //else doespass =(Bool_t)( (AOD_HLT_IsoMu22 > 0) || (AOD_HLT_IsoTkMu22 > 0) || (AOD_HLT_IsoMu24 > 0) || (AOD_HLT_IsoTkMu24 > 0) );
  doespass = (Bool_t)( (AOD_HLT_IsoMu22 > 0) || (AOD_HLT_IsoTkMu22 > 0) || (AOD_HLT_IsoMu24 > 0) || (AOD_HLT_IsoTkMu24 > 0) );
 } 
 return doespass;
}

Bool_t analyzer_selections::askPassDoubleMu()
{
 Bool_t doespass = kFALSE;
 if(muon_list.size()>1){ 
  //if(isMC) doespass = kTRUE;
  //else doespass = (Bool_t)( (AOD_HLT_Mu17Mu8 > 0) || (AOD_HLT_Mu17TkMu8 > 0) || (AOD_HLT_Mu17Mu8_noDZ > 0) || (AOD_HLT_Mu17TkMu8_noDZ > 0)) ; 
  doespass = (Bool_t)( (AOD_HLT_Mu17Mu8 > 0) || (AOD_HLT_Mu17TkMu8 > 0) || (AOD_HLT_Mu17Mu8_noDZ > 0) || (AOD_HLT_Mu17TkMu8_noDZ > 0)) ; 
 } 
 return doespass;
}

Bool_t analyzer_selections::askPassSinglePho()
{
 Bool_t doespass = kFALSE;
 if(photon_list.size()>0){ 
  //doespass = kTRUE;
  //if(isMC) doespass = kTRUE;
  //else doespass = (Bool_t)( (AOD_HLT_Photon165_HE10) );
  doespass = (Bool_t)(AOD_HLT_Photon165_HE10 > 0);
 } 
 return doespass;
}

Bool_t analyzer_selections::askPassMuEG()
{
 Bool_t doespass = kFALSE;
 if(muon_list.size()>0 && electron_list.size()>0){ 
  //doespass = kTRUE;
  //if(isMC) doespass = kTRUE;
  //else doespass = (Bool_t)( (AOD_HLT_Mu8Ele23 > 0) || (AOD_HLT_Mu23Ele12)  || (AOD_HLT_Mu12Ele23_DZ)  || (AOD_HLT_Mu23Ele12_DZ) );

  ///based on http://cms.cern.ch/iCMS/jsp/analysis/admin/analysismanagement.jsp?ancode=HIG-16-042
  //should double check
   if( isMC ){
    doespass =  (Bool_t)( (AOD_HLT_Mu12Ele23_DZ > 0) || (AOD_HLT_Mu23Ele12_DZ > 0) );
   }
   if(run>=273158 && run<=278272){
    doespass =  (Bool_t)( (AOD_HLT_Mu8Ele23 > 0) || (AOD_HLT_Mu23Ele12 > 0) );
   }
   else if(run>=278273 && run<=284044){
    doespass = (Bool_t)( (AOD_HLT_Mu12Ele23_DZ > 0) || (AOD_HLT_Mu23Ele12_DZ > 0) );
   }
   
 } 
 return doespass;
}
