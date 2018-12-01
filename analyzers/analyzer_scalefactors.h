
#ifndef analyzer_scalefactors_h
#define analyzer_scalefactors_h

#include "analyzer_selections.h"

class analyzer_scalefactors : public analyzer_selections {


public :

                  analyzer_scalefactors();
   virtual        ~analyzer_scalefactors(); 

 // event based weights
 Float_t         makeEventWeight(Float_t crossSec, Float_t lumi,
                                  Float_t nrEvents);
 void            loadPUWeight();
 Float_t         makePUWeight( TString dataset );
 TH1F*           PUWeights_DoubleEG     ;
 TH1F*           PUWeights_DoubleMu     ;
 TH1F*           PUWeights_MuonEG       ;
 TH1F*           PUWeights_SinglePhoton ;
 void            loadElectronWeight( TString eleid );
 Float_t         makeElectronWeight( std::vector<int> &electron_list );
 TH2F*           EleWeights;
 Float_t         makeTTWeight( Float_t TTavgweight );

 void               loadMistagRate();
 TH1F*              h_MistagRate_pt;
 std::vector<TH1F*> h_MistagRate_pt_sys;
 TH2F*              h_MistagRate_pteta;
 std::vector<TH2F*> h_MistagRate_pteta_sys;

};

#endif
