
#ifndef analyzer_selections_h
#define analyzer_selections_h

#include "analyzer_createobjects.h"

class analyzer_selections : public analyzer_createobjects {


public :

                  analyzer_selections();
   virtual        ~analyzer_selections(); 

   virtual void  clearSelections();
   virtual void  setSelections();

   // Selection functions
   Int_t         setSelBits( std::vector<Bool_t> selvec, int &counter );
   Int_t         setSelKey ( std::vector<Bool_t> selvec );
   Bool_t        askPassSingleEle();
   Bool_t        askPassSingleMu();
   Bool_t        askPassDoubleEle();
   Bool_t        askPassDoubleMu();
   Bool_t        askPassMuEG();
   Bool_t        askPassSinglePho();

   std::vector<Bool_t> selvecBaseSig    ;
   std::vector<Bool_t> selvecBaseZH     ;
   std::vector<Bool_t> selvecBaseDY     ;
   std::vector<Bool_t> selvecBaseOffZ   ;
   std::vector<Bool_t> selvecBaseNoPair ;

   std::vector<Bool_t> selvecOneEleSig    ; 
   std::vector<Bool_t> selvecTwoEleSig    ; 
   std::vector<Bool_t> selvecOneMuSig     ; 
   std::vector<Bool_t> selvecTwoMuSig     ; 
   std::vector<Bool_t> selvecOneEleDY     ; 
   std::vector<Bool_t> selvecTwoEleDY     ; 
   std::vector<Bool_t> selvecOneMuDY      ; 
   std::vector<Bool_t> selvecTwoMuDY      ; 
   std::vector<Bool_t> selvecOneEleZH     ; 
   std::vector<Bool_t> selvecTwoEleZH     ; 
   std::vector<Bool_t> selvecOneMuZH      ; 
   std::vector<Bool_t> selvecTwoMuZH      ; 
   std::vector<Bool_t> selvecOneEleOffZ   ; 
   std::vector<Bool_t> selvecTwoEleOffZ   ; 
   std::vector<Bool_t> selvecOneMuOffZ    ; 
   std::vector<Bool_t> selvecTwoMuOffZ    ; 
   std::vector<Bool_t> selvecOneEleNoPair ; 
   std::vector<Bool_t> selvecOneMuNoPair  ; 
   std::vector<Bool_t> selvecEleMuOSOF    ; 
   std::vector<Bool_t> selvecEleMuOSOFL   ; 
   std::vector<Bool_t> selvecOnePho       ; 
   Int_t selvec[SELBINNAMESIZE];
   Int_t selkey[SELBINNAMESIZE];


   // selection booleans
   Bool_t passSingleEle ;
   Bool_t passSingleMu  ;
   Bool_t passDoubleEle ;
   Bool_t passDoubleMu  ;
   Bool_t passSinglePho ;
   Bool_t passMuEG ;
   Bool_t passOSSF      ;   
   Bool_t passOSOF      ;   
   Bool_t passZWindow   ;   
   Bool_t passZWinOSOF  ;
   Bool_t passGoodVtx   ;   
   Bool_t passPTOSSF    ; 
   Bool_t passPTOSOF    ;   
   Bool_t passOneJet    ; 
   Bool_t passOneTag    ;
   Bool_t passTwoTag    ;

};

#endif
