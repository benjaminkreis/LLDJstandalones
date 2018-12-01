#include "analyzer_globalvalues.h"

//----------------------------analyzer_globalvalues
analyzer_globalvalues::analyzer_globalvalues() 
{
}

//----------------------------~analyzer_globalvalues
analyzer_globalvalues::~analyzer_globalvalues()
{
}

//----------------------------~clearglobalcounters
void analyzer_globalvalues::clearglobalcounters()
{

 n_tot   = 0;

 n_passOneEleSig    = 0;
 n_passTwoEleSig    = 0;
 n_passOneMuSig     = 0;
 n_passTwoMuSig     = 0;
 n_passOneEleDY     = 0;
 n_passTwoEleDY     = 0;
 n_passOneMuDY      = 0;
 n_passTwoMuDY      = 0;
 n_passOneEleZH     = 0;
 n_passTwoEleZH     = 0;
 n_passOneMuZH      = 0;
 n_passTwoMuZH      = 0;
 n_passOneEleOffZ   = 0;
 n_passTwoEleOffZ   = 0;
 n_passOneMuOffZ    = 0;
 n_passTwoMuOffZ    = 0;
 n_passOneEleNoPair = 0;
 n_passOneMuNoPair  = 0;
 n_passEleMuOSOF    = 0;
 n_passEleMuOSOFL   = 0;
 n_passOnePho       = 0;
 n_totalPF          = 0;
 n_totalPFchs       = 0;
 n_totalCalo        = 0;
 n_matchedPFCalo    = 0;
 n_matchedPFchsCalo = 0;

}


//----------------------------~cleareventcounters
void analyzer_globalvalues::cleareventcounters(){

 // clear counters for event variables
 nSelectedPho=0;
 nSelectedEle=0;
 nSelectedMuo=0;
 nSelectedAODCaloJet=0;

 nBPartonFlavour=0;

 electron_list         .clear(); 
 photon_list           .clear(); 
 muon_list             .clear(); 
 aodcalojet_list       .clear(); 
 aodpfjet_list         .clear(); 
 aodpfchsjet_list      .clear(); 
 taggedjet_list        .clear(); 
 taggedjetSB1_list     .clear(); 
 taggedjetSB2_list     .clear(); 
 taggedjetSB3_list     .clear();
 calomatchedPF_list    .clear();
 PFmatchedCalo_list    .clear();
 calomatchedPFchs_list .clear();
 PFchsmatchedCalo_list .clear();

}

