#define analyzer_loop_cxx
#include "analyzer_loop.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <iomanip>

using namespace std;

analyzer_loop::analyzer_loop()
{
}

analyzer_loop::~analyzer_loop()
{
}

void analyzer_loop::Loop(TString outfilename, 
                       Float_t lumi, Float_t nrEvents,
                       Float_t crossSec, Float_t avgTTSF,
                       Int_t nevts, TFile *optfile, TFile *NM1file, TString uncbin)
{

 if(makelog){
  logfile = fopen( outfilename+".txt", "w"); 
 }

 if (fChain == 0) return;

 Long64_t nentries = fChain->GetEntriesFast();
 if(nevts>0){ 
  nentries = Long64_t(nevts);
 }
 
 clearglobalcounters();

 if(isMC) loadPUWeight();
 if(isMC) loadElectronWeight( eleid );

 std::cout<<"uncbin: "<<uncbin<<std::endl;
 TFile *outfile_bkgest = 0;
 bool doBkgEst = true;
 if( doBkgEst && uncbin.EqualTo("") ){
   std::cout<<"doBkgEst"<<std::endl;
   outfile_bkgest = TFile::Open(outfilename+"_BkgEst.root","RECREATE");
   loadMistagRate();
 }

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {

  cleareventcounters();
  if( uncbin.EqualTo("") ){
   optfile->cd();
   clearOPTtree(); 
   clearOPTCRHeavytree(); 
   clearOPTCRLighttree(); 
   clearOPTMuZHtree(); 
   clearOPTEleZHtree(); 
  }
  if( uncbin.EqualTo("") ){
   NM1file->cd();
   clearNM1tree(); 
   clearNM1CRHeavytree(); 
   clearNM1CRLighttree(); 
   clearNM1MuZHtree(); 
   clearNM1EleZHtree(); 
  }

  //printf(" Event %lld\n", event);
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (jentry%10000 == 0){ std::cout << " entry " << jentry << std::endl; }

  shiftCollections(uncbin);
  n_tot++;

  // get lists of "good" electrons, photons, jets
  // idbit, pt, eta, sysbinname
  electron_list    = electron_passID  ( eleidbit,        ele_minPt1, ele_minPt2, ele_maxEta, "");
  photon_list      = photon_passID    ( phoidbit,        pho_minPt, pho_maxEta, ""); 
  muon_list        = muon_passID      ( muoidbit,        mu_minPt1,  mu_minPt2,  mu_maxEta,  ""); 
  aodcalojet_list  = jet_passID       ( aodcalojetidbit, "calo",  jet_minPt, jet_maxEta, "" ); 
  aodpfjet_list    = jet_passID       ( aodcalojetidbit, "pf",    jet_minPt, jet_maxEta, ""); 
  aodpfchsjet_list = jet_passID       ( aodcalojetidbit, "pfchs", jet_minPt, jet_maxEta, ""); 
  taggedjet_list   = jet_passTagger   ();
  taggedjetSB1_list   = jet_passTaggerSB1   ();
  taggedjetSB2_list   = jet_passTaggerSB2   ();
  taggedjetSB3_list   = jet_passTaggerSB3   ();

  // make calomatchedPF_list PFmatchedCalo_list calomatchedPFchs_list PFchsmatchedCalo_list 
  matchPFCalojets( "PF" );
  matchPFCalojets( "PFchs" );
  n_totalPF          += aodpfjet_list.size()         ; 
  n_totalPFchs       += aodpfchsjet_list.size()      ; 
  n_totalCalo        += aodcalojet_list.size()        ; 
  n_matchedPFCalo    += calomatchedPF_list.size()    ; 
  n_matchedPFchsCalo += calomatchedPFchs_list.size() ; 

  aodcalojet_minDR_list = jet_minDR();
  aodcalojet_matchedCSV_list = jet_matchCSV();
  aodcalojet_matchedPartonFlavour_list = jet_matchPartonFlavour();

  nBPartonFlavour = coutNBPartonFlavour();

  // colisions happen @LHC at a given rate, use event_weight
  // to make the simulation match the rate seen in data
  // = lum * cross-section / nrEvents generated
  event_weight = makeEventWeight(crossSec,lumi,nrEvents);
  // for MC, simulated pileup is different from observed
  // in commontools/pileup we make a ratio for scaling MC
  if(isMC) PUweight_DoubleEG     = makePUWeight("DoubleEG"    ) ;
  if(isMC) PUweight_DoubleMu     = makePUWeight("DoubleMu"    ) ;
  if(isMC) PUweight_MuonEG       = makePUWeight("MuonEG"      ) ;
  if(isMC) PUweight_SinglePhoton = makePUWeight("SinglePhoton") ;
  // electrons also have an associated scale factor for MC 
  if(isMC) event_weight *= makeElectronWeight( electron_list );
  if(isMC) event_weight *= makeTTWeight( avgTTSF );

  getMET();

  calculateHT();

  makeDiLepton();

  // set booleans if pass selections 
  passOSSF = (dilep_mass>20.);
  passOSOF = (OSOF_mass>20.);
  passPTOSOF = (OSOF_pt>100.);
  passZWindow = (dilep_mass>70. && dilep_mass<110.);
  passZWinOSOF= (OSOF_mass>70. && OSOF_mass<110.);
  passPTOSSF  = (dilep_pt>100.);
  passGoodVtx = AODnGoodVtx>0; 
  passOneJet  = false; if (aodcalojet_list.size()>0) passOneJet=true;  
  passOneTag  = false; if (taggedjet_list.size()>0) passOneTag=true;  
  passTwoTag  = false; if (taggedjet_list.size()>1) passTwoTag=true;  
  
  passSingleEle = askPassSingleEle();
  passSingleMu  = askPassSingleMu();
  passDoubleEle = askPassDoubleEle();
  passDoubleMu  = askPassDoubleMu();
  passMuEG      = askPassMuEG();
  passSinglePho = askPassSinglePho();

  // clear then reset selection vectors
  clearSelections();
  setSelections();

  // set bits if pass various selections, increment counters
  bitsPassOneEleSig    = setSelBits( selvecOneEleSig    , n_passOneEleSig    );   
  bitsPassTwoEleSig    = setSelBits( selvecTwoEleSig    , n_passTwoEleSig    );   
  bitsPassOneMuSig     = setSelBits( selvecOneMuSig     , n_passOneMuSig     );   
  bitsPassTwoMuSig     = setSelBits( selvecTwoMuSig     , n_passTwoMuSig     );   
  bitsPassOneEleDY     = setSelBits( selvecOneEleDY     , n_passOneEleDY     );   
  bitsPassTwoEleDY     = setSelBits( selvecTwoEleDY     , n_passTwoEleDY     );   
  bitsPassOneMuDY      = setSelBits( selvecOneMuDY      , n_passOneMuDY      );   
  bitsPassTwoMuDY      = setSelBits( selvecTwoMuDY      , n_passTwoMuDY      );   
  bitsPassOneEleZH     = setSelBits( selvecOneEleZH     , n_passOneEleZH     );   
  bitsPassTwoEleZH     = setSelBits( selvecTwoEleZH     , n_passTwoEleZH     );   
  bitsPassOneMuZH      = setSelBits( selvecOneMuZH      , n_passOneMuZH      );   
  bitsPassTwoMuZH      = setSelBits( selvecTwoMuZH      , n_passTwoMuZH      );   
  bitsPassOneEleOffZ   = setSelBits( selvecOneEleOffZ   , n_passOneEleOffZ   );   
  bitsPassTwoEleOffZ   = setSelBits( selvecTwoEleOffZ   , n_passTwoEleOffZ   );   
  bitsPassOneMuOffZ    = setSelBits( selvecOneMuOffZ    , n_passOneMuOffZ    );   
  bitsPassTwoMuOffZ    = setSelBits( selvecTwoMuOffZ    , n_passTwoMuOffZ    );   
  bitsPassOneEleNoPair = setSelBits( selvecOneEleNoPair , n_passOneEleNoPair ); 
  bitsPassOneMuNoPair  = setSelBits( selvecOneMuNoPair  , n_passOneMuNoPair  );   
  bitsPassEleMuOSOF    = setSelBits( selvecEleMuOSOF    , n_passEleMuOSOF    );   
  bitsPassEleMuOSOFL   = setSelBits( selvecEleMuOSOFL   , n_passEleMuOSOFL   );   
  bitsPassOnePho       = setSelBits( selvecOnePho       , n_passOnePho       );

  keyPassOneEleSig    = setSelKey( selvecOneEleSig    ); 
  keyPassTwoEleSig    = setSelKey( selvecTwoEleSig    ); 
  keyPassOneMuSig     = setSelKey( selvecOneMuSig     ); 
  keyPassTwoMuSig     = setSelKey( selvecTwoMuSig     ); 
  keyPassOneEleDY     = setSelKey( selvecOneEleDY     ); 
  keyPassTwoEleDY     = setSelKey( selvecTwoEleDY     ); 
  keyPassOneMuDY      = setSelKey( selvecOneMuDY      ); 
  keyPassTwoMuDY      = setSelKey( selvecTwoMuDY      ); 
  keyPassOneEleZH     = setSelKey( selvecOneEleZH     ); 
  keyPassTwoEleZH     = setSelKey( selvecTwoEleZH     ); 
  keyPassOneMuZH      = setSelKey( selvecOneMuZH      ); 
  keyPassTwoMuZH      = setSelKey( selvecTwoMuZH      ); 
  keyPassOneEleOffZ   = setSelKey( selvecOneEleOffZ   ); 
  keyPassTwoEleOffZ   = setSelKey( selvecTwoEleOffZ   ); 
  keyPassOneMuOffZ    = setSelKey( selvecOneMuOffZ    ); 
  keyPassTwoMuOffZ    = setSelKey( selvecTwoMuOffZ    ); 
  keyPassOneEleNoPair = setSelKey( selvecOneEleNoPair ); 
  keyPassOneMuNoPair  = setSelKey( selvecOneMuNoPair  ); 
  keyPassEleMuOSOF    = setSelKey( selvecEleMuOSOF    ); 
  keyPassEleMuOSOFL   = setSelKey( selvecEleMuOSOFL   ); 
  keyPassOnePho       = setSelKey( selvecOnePho       ); 

  //debug_printbitset(); // this is a big printout
  //debug_printbitkeys(); // this is a big printout

  // put into array for looping in Cutflow histograms
  selvec[0]  = bitsPassOneEleSig    ; 
  selvec[1]  = bitsPassTwoEleSig    ; 
  selvec[2]  = bitsPassOneMuSig     ; 
  selvec[3]  = bitsPassTwoMuSig     ; 
  selvec[4]  = bitsPassOneEleDY     ; 
  selvec[5]  = bitsPassTwoEleDY     ; 
  selvec[6]  = bitsPassOneMuDY      ; 
  selvec[7]  = bitsPassTwoMuDY      ; 
  selvec[8]  = bitsPassOneEleZH     ; 
  selvec[9]  = bitsPassTwoEleZH     ; 
  selvec[10] = bitsPassOneMuZH      ; 
  selvec[11] = bitsPassTwoMuZH      ; 
  selvec[12] = bitsPassOneEleOffZ   ; 
  selvec[13] = bitsPassTwoEleOffZ   ; 
  selvec[14] = bitsPassOneMuOffZ    ; 
  selvec[15] = bitsPassTwoMuOffZ    ; 
  selvec[16] = bitsPassOneEleNoPair ; 
  selvec[17] = bitsPassOneMuNoPair  ; 
  selvec[18] = bitsPassEleMuOSOF    ; 
  selvec[19] = bitsPassOnePho       ; 
  selvec[20] = bitsPassEleMuOSOFL   ; 

  selkey[0]  = keyPassOneEleSig    ; 
  selkey[1]  = keyPassTwoEleSig    ; 
  selkey[2]  = keyPassOneMuSig     ; 
  selkey[3]  = keyPassTwoMuSig     ; 
  selkey[4]  = keyPassOneEleDY     ; 
  selkey[5]  = keyPassTwoEleDY     ; 
  selkey[6]  = keyPassOneMuDY      ; 
  selkey[7]  = keyPassTwoMuDY      ; 
  selkey[8]  = keyPassOneEleZH     ; 
  selkey[9]  = keyPassTwoEleZH     ; 
  selkey[10] = keyPassOneMuZH      ; 
  selkey[11] = keyPassTwoMuZH      ; 
  selkey[12] = keyPassOneEleOffZ   ; 
  selkey[13] = keyPassTwoEleOffZ   ; 
  selkey[14] = keyPassOneMuOffZ    ; 
  selkey[15] = keyPassTwoMuOffZ    ; 
  selkey[16] = keyPassOneEleNoPair ; 
  selkey[17] = keyPassOneMuNoPair  ; 
  selkey[18] = keyPassEleMuOSOF    ; 
  selkey[19] = keyPassOnePho       ; 
  selkey[20] = keyPassEleMuOSOFL   ; 

  dofillselbin[0]  = ( ( bitsPassOneEleSig    >> 0) &1) ; 
  dofillselbin[1]  = ( ( bitsPassTwoEleSig    >> 0) &1) ; 
  dofillselbin[2]  = ( ( bitsPassOneMuSig     >> 0) &1) ; 
  dofillselbin[3]  = ( ( bitsPassTwoMuSig     >> 0) &1) ; 
  dofillselbin[4]  = ( ( bitsPassOneEleDY     >> 0) &1) ; 
  dofillselbin[5]  = ( ( bitsPassTwoEleDY     >> 0) &1) ; 
  dofillselbin[6]  = ( ( bitsPassOneMuDY      >> 0) &1) ; 
  dofillselbin[7]  = ( ( bitsPassTwoMuDY      >> 0) &1) ; 
  dofillselbin[8]  = ( ( bitsPassOneEleZH     >> 0) &1) ; 
  dofillselbin[9]  = ( ( bitsPassTwoEleZH     >> 0) &1) ; 
  dofillselbin[10] = ( ( bitsPassOneMuZH      >> 0) &1) ; 
  dofillselbin[11] = ( ( bitsPassTwoMuZH      >> 0) &1) ; 
  dofillselbin[12] = ( ( bitsPassOneEleOffZ   >> 0) &1) ; 
  dofillselbin[13] = ( ( bitsPassTwoEleOffZ   >> 0) &1) ; 
  dofillselbin[14] = ( ( bitsPassOneMuOffZ    >> 0) &1) ; 
  dofillselbin[15] = ( ( bitsPassTwoMuOffZ    >> 0) &1) ; 
  dofillselbin[16] = ( ( bitsPassOneEleNoPair >> 0) &1) ; 
  dofillselbin[17] = ( ( bitsPassOneMuNoPair  >> 0) &1) ; 
  dofillselbin[18] = ( ( bitsPassEleMuOSOF    >> 0) &1) ; 
  dofillselbin[19] = ( ( bitsPassOnePho       >> 0) &1) ; 
  dofillselbin[20] = ( ( bitsPassEleMuOSOFL   >> 0) &1) ; 

  // fake rate code
  if(doBkgEst && uncbin.EqualTo("")){
   if( ( ( bitsPassTwoMuZH      >> 0) &1) ){// TwoMuZH
    fillBackgroundEstimateHistograms(event_weight);
   }
  }
  // tagging variable optimization tree
  if( ( (( bitsPassTwoMuZH      >> 0) &1) || (( bitsPassTwoEleZH      >> 0) &1))  && uncbin.EqualTo("") ){// TwoMuZH or TwoEleZH 
   optfile->cd();
   setOPTtree(); 
   OPTtree->Fill();
  }
  // tagging variable NMinus1 tree
  if( ( ( bitsPassTwoMuDY      >> 0) &1) && uncbin.EqualTo("") ){// General Purpose: TwoMuDY
   NM1file->cd();
   setNM1tree(); 
   NM1tree->Fill();
  }
  
  if( ( ( bitsPassEleMuOSOF    >> 0) &1) && uncbin.EqualTo("") ){// CRHeavy
   optfile->cd();          
   setOPTCRHeavytree();    
   OPTCRHeavytree->Fill();
   
   NM1file->cd();
   setNM1CRHeavytree(); 
   NM1CRHeavytree->Fill();
  }
  if( ( ( bitsPassOnePho       >> 0) &1) && uncbin.EqualTo("") ){// CRLight
   optfile->cd(); 
   setOPTCRLighttree();   
   OPTCRLighttree->Fill(); 
   
   NM1file->cd();
   setNM1CRLighttree(); 
   NM1CRLighttree->Fill();
  }
  if( ( ( bitsPassTwoMuZH      >> 0) &1) && uncbin.EqualTo("") ){// TwoMuZH
   optfile->cd();   
   setOPTMuZHtree();   
   OPTMuZHtree->Fill();
   
   NM1file->cd();
   setNM1MuZHtree(); 
   NM1MuZHtree->Fill();
  }
  if( ( ( bitsPassTwoEleZH     >> 0) &1) && uncbin.EqualTo("") ){// TwoEleZH
   optfile->cd(); 
   setOPTEleZHtree(); 
   OPTEleZHtree->Fill();
   
   NM1file->cd();
   setNM1EleZHtree(); 
   NM1EleZHtree->Fill();
  }

  // fill the histograms
  for(unsigned int i=0; i<selbinnames.size(); ++i){

   if(isMC){
     // ok I'm sorry, this is terrible
     if(i==0||i==1||i==4||i==5||i==8||i==9||i==12||i==13||i==15)   fullweight = event_weight * PUweight_DoubleEG;
     if(i==2||i==3||i==6||i==7||i==10||i==11||i==14||i==15||i==17) fullweight = event_weight * PUweight_DoubleMu;
     if(i==18) fullweight = event_weight * PUweight_MuonEG;
     if(i==20) fullweight = event_weight * PUweight_MuonEG;
     if(i==19) fullweight = event_weight * PUweight_SinglePhoton;
   }
   else{
     fullweight = event_weight;
   }

   /// quick hack to only write phase spaces we care about
   if(i==1 || i==3 || i==5 || i==7 || i==9 || i==11 || i==18 || i==19 || i==20  ){
    fillCutflowHistograms( fullweight, i, selvec[i], selkey[i] );
    if( dofillselbin[i] ){
     fillSelectedHistograms( fullweight, i );

     //jets
     for( unsigned int k=0; k<jetmultnames.size(); ++k){
      fillSelectedJetHistograms( fullweight, i, k );
     }  

     //tagged jets
     for( unsigned int k=0; k<tagmultnames.size(); ++k){
      fillSelectedTagHistograms( fullweight, i, k );
     }  
    } // if( dofillselbin[i] ){
   } // if i== one of the phase spaces we want to write
  } // for(unsigned int i=0; i<selbinnames.size(); ++i){

  //debug_printobjects();   // helpful printout (turn off when submitting!!!)

  //Print objects in backgroundMC with >=2 tags
  //if(taggedjet_list.size()>=2 && isMC && !outfilename.Contains("HToSS")) debug_printobjects();


  //printf("make log: %0.i\n",makelog);
  
 } // end loop over entries

 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << " Summary     cleaning dR=" << objcleandRcut << std::endl;

 std::cout << " Total events processed  " << n_tot << std::endl;

 std::cout<<" n_passOneEleSig    " << setw(width) << left << n_passOneEleSig    << setw(width) << left << (float) n_passOneEleSig   / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoEleSig    " << setw(width) << left << n_passTwoEleSig    << setw(width) << left << (float) n_passTwoEleSig   / (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuSig     " << setw(width) << left << n_passOneMuSig     << setw(width) << left << (float) n_passOneMuSig    / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoMuSig     " << setw(width) << left << n_passTwoMuSig     << setw(width) << left << (float) n_passTwoMuSig    / (float) n_tot << std::endl;   
 std::cout<<" n_passOneEleDY     " << setw(width) << left << n_passOneEleDY     << setw(width) << left << (float) n_passOneEleDY    / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoEleDY     " << setw(width) << left << n_passTwoEleDY     << setw(width) << left << (float) n_passTwoEleDY    / (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuDY      " << setw(width) << left << n_passOneMuDY      << setw(width) << left << (float) n_passOneMuDY     / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoMuDY      " << setw(width) << left << n_passTwoMuDY      << setw(width) << left << (float) n_passTwoMuDY     / (float) n_tot << std::endl;   
 std::cout<<" n_passOneEleZH     " << setw(width) << left << n_passOneEleZH     << setw(width) << left << (float) n_passOneEleZH    / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoEleZH     " << setw(width) << left << n_passTwoEleZH     << setw(width) << left << (float) n_passTwoEleZH    / (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuZH      " << setw(width) << left << n_passOneMuZH      << setw(width) << left << (float) n_passOneMuZH     / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoMuZH      " << setw(width) << left << n_passTwoMuZH      << setw(width) << left << (float) n_passTwoMuZH     / (float) n_tot << std::endl;   
 std::cout<<" n_passOneEleOffZ   " << setw(width) << left << n_passOneEleOffZ   << setw(width) << left << (float) n_passOneEleOffZ  / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoEleOffZ   " << setw(width) << left << n_passTwoEleOffZ   << setw(width) << left << (float) n_passTwoEleOffZ  / (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuOffZ    " << setw(width) << left << n_passOneMuOffZ    << setw(width) << left << (float) n_passOneMuOffZ   / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoMuOffZ    " << setw(width) << left << n_passTwoMuOffZ    << setw(width) << left << (float) n_passTwoMuOffZ   / (float) n_tot << std::endl;   
 std::cout<<" n_passOneEleNoPair " << setw(width) << left << n_passOneEleNoPair << setw(width) << left << (float) n_passOneEleNoPair/ (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuNoPair  " << setw(width) << left << n_passOneMuNoPair  << setw(width) << left << (float) n_passOneMuNoPair / (float) n_tot << std::endl;   
 std::cout<<" n_passEleMuOSOF    " << setw(width) << left << n_passEleMuOSOF    << setw(width) << left << (float) n_passEleMuOSOF   / (float) n_tot << std::endl;   
 std::cout<<" n_passEleMuOSOFL   " << setw(width) << left << n_passEleMuOSOFL   << setw(width) << left << (float) n_passEleMuOSOFL  / (float) n_tot << std::endl;   
 std::cout<<" n_passOnePho       " << setw(width) << left << n_passOnePho       << setw(width) << left << (float) n_passOnePho      / (float) n_tot << std::endl;   
 std::cout<<std::endl;

 std::cout<<" Jet Matching "<<std::endl;
 std::cout<<"  n_totalPF          "<< n_totalPF          <<std::endl;
 std::cout<<"  n_totalPFchs       "<< n_totalPFchs       <<std::endl;
 std::cout<<"  n_totalCalo        "<< n_totalCalo        <<std::endl;
 std::cout<<"  n_matchedPFCalo    "<< n_matchedPFCalo    <<std::endl;
 std::cout<<"  n_matchedPFchsCalo "<< n_matchedPFchsCalo <<std::endl;
 std::cout<<"   Percent calo matched to PF: "<<(float)n_matchedPFCalo/(float)n_totalCalo<<std::endl;
 std::cout<<"   Percent calo matched to PFchs: "<<(float)n_matchedPFchsCalo/(float)n_totalCalo<<std::endl;
 std::cout<<std::endl<<std::endl;

 if(doBkgEst && uncbin.EqualTo("")){
   //Can choose more regions here
   outfile_bkgest->cd();
   writeBackgroundEstimateHistograms(outfile_bkgest);
   outfile_bkgest->Close();
 }
 if( uncbin.EqualTo("") ){
  optfile->cd();
  OPTtree->CloneTree()->Write();
  OPTCRHeavytree->CloneTree()->Write();
  OPTCRLighttree->CloneTree()->Write();
  OPTMuZHtree->CloneTree()->Write();
  OPTEleZHtree->CloneTree()->Write();
  optfile->Close();
 }

 if( uncbin.EqualTo("") ){
  NM1file->cd();
  NM1tree->CloneTree()->Write();
  NM1CRHeavytree->CloneTree()->Write();
  NM1CRLighttree->CloneTree()->Write();
  NM1MuZHtree->CloneTree()->Write();
  NM1EleZHtree->CloneTree()->Write();
  NM1file->Close();
 }
 // make outfile and save histograms
 // write the histograms
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  if(i==1 || i==3 || i==5 || i==7 || i==9 || i==11 || i==18 || i==19 || i==20  ){
   TFile *outfile = new TFile(outfilename+"_"+selbinnames[i]+"_histograms.root","UPDATE");
   outfile->cd();

     //Normalize variable binned histograms by bin width
     //Could put this in its own loop for clarity
     scaleVariableBinHistograms( i );
     
     writeSelectedHistograms( i );
     writeCutflowHistograms( i );

     //jet
     for( unsigned int k=0; k<jetmultnames.size(); ++k){
       writeSelectedJetHistograms( i, k );
     }

     //tag
     for( unsigned int k=0; k<tagmultnames.size(); ++k){
       writeSelectedTagHistograms( i, k );
     }

   outfile->Close();
  } 
 } // if i== one of the phase spaces we want to write
} // end analyzer_loop::Loop()


void analyzer_loop::debug_printobjects(){

  printf("\n Event %lld\n", event);
  printf(" Pass ossf %d zwind %d ptg50 %d 1jet %d vtx %d \n", passOSSF, passZWindow, passPTOSSF, passOneJet, passGoodVtx);

  //debug_printbitset();
  debug_printphotons();
  debug_printmuons();
  debug_printelectrons();

  printf(" Pass SingleEle: %d SingleMu: %d\n", passSingleEle, passSingleMu);

  debug_printdilep();
  debug_printjets();

  std::cout << endl;
  std::cout << "*******************PRE-ID PRINT******************" << std::endl;
  std::cout << "Electrons pt eta phi charge" << std::endl;
  for(int i=0; i<AOD_eleEta->size(); i++){
    std::cout << AOD_elePt->at(i) << " " << AOD_eleEta->at(i) << " " << AOD_elePhi->at(i) << " " << AOD_eleCharge->at(i) << std::endl;
  }
  std::cout << "Muon pt eta phi" << std::endl;
  for(int i=0; i<AOD_muEta->size(); i++){
    std::cout << AOD_muPt->at(i) << " " << AOD_muEta->at(i) << " " << AOD_muPhi->at(i) << " " << AOD_muCharge->at(i) << std::endl;
  }
  std::cout << "Photon pt eta phi" << std::endl;
  for(int i=0; i<AOD_phoEta->size(); i++){
    std::cout << AOD_phoPt->at(i) << " " << AOD_phoEta->at(i) << " " << AOD_phoPhi->at(i) << std::endl;
  }
  std::cout << "AODCaloJet pt eta phi" << std::endl;
  for(int i=0; i<AODCaloJetEta->size(); i++){
    std::cout << AODCaloJetPt->at(i) << " " << AODCaloJetEta->at(i) << " " << AODCaloJetPhi->at(i) << std::endl;
  }


  return;

 }

void analyzer_loop::debug_printmuons()
{

 // muon debug
  for(int i=0; i<muon_list.size(); ++i){
   int muindex = muon_list[i];
   printf( " muon %d : pt %.1f eta %.1f phi %.1f\n", i, AOD_muPt->at(muindex), AOD_muEta->at(muindex), AOD_muPhi->at(muindex));

   //printf(" muonid %d    %d %d %d %d %d \n",i
   //      ,muIDbit->at(i) >> 0 & 0x1 
   //      ,muIDbit->at(i) >> 1 & 0x1 
   //      ,muIDbit->at(i) >> 2 & 0x1 
   //      ,muIDbit->at(i) >> 3 & 0x1 
   //      ,muIDbit->at(i) >> 4 & 0x1 
   //      );       
  }
 return;
}

void analyzer_loop::debug_printelectrons()
{
  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   printf( " electron %d : pt %.1f eta %.1f phi %.1f\n", i, AOD_elePt->at(eleindex), AOD_eleEta->at(eleindex), AOD_elePhi->at(eleindex));
  }
 return;
}


void analyzer_loop::debug_printdilep()
{
  if(dilep_mass>0.){
   printf(" DILEP FOUND\n");
   printf("  l1 pt %.1f  eta %.1f  phi %.1f  mass %.1f \n",
     fourVec_l1.Pt(), fourVec_l1.Eta(), fourVec_l1.Phi(), fourVec_l1.M() );
   printf("  l2 pt %.1f  eta %.1f  phi %.1f  mass %.1f \n",
     fourVec_l2.Pt(), fourVec_l2.Eta(), fourVec_l2.Phi(), fourVec_l2.M() );
   printf("  ll pt %.1f  eta %.1f  phi %.1f  mass %.1f \n",
      fourVec_ll.Pt(), fourVec_ll.Eta(), fourVec_ll.Phi(), fourVec_ll.M() );
  }
 return;
}

void analyzer_loop::debug_printphotons()
{
  for(int i=0; i<photon_list.size(); ++i){
   int phoindex = photon_list[i];
   printf( " photon %d : pt %.1f eta %.1f phi %.1f\n", i, AOD_phoPt->at(phoindex), AOD_phoEta->at(phoindex), AOD_phoPhi->at(phoindex));
  }
 return;
}

void analyzer_loop::debug_printjets()
{
  for(int i=0; i<aodcalojet_list.size(); ++i){
   int jetindex = aodcalojet_list[i];
   printf( " jet %d : pt %.1f eta %.1f phi %.1f\n", i, AODCaloJetPt->at(jetindex), AODCaloJetEta->at(jetindex), AODCaloJetPhi->at(jetindex));
   printf( "  tagvars amax %.1f TA %.1f IP %.1f\n",  AODCaloJetAlphaMax->at(jetindex), AODCaloJetMedianLog10TrackAngle->at(jetindex), AODCaloJetMedianLog10IPSig->at(jetindex));
  }

  for(int i=0; i<taggedjet_list.size(); ++i){
   int jetindex = taggedjet_list[i];
   printf( " TAGGED JET\n");
   printf( " jet %d : pt %.1f eta %.1f phi %.1f\n", i, AODCaloJetPt->at(jetindex), AODCaloJetEta->at(jetindex), AODCaloJetPhi->at(jetindex));
   printf( "  tagvars amax %.1f TA %.1f IP %.1f\n", AODCaloJetAlphaMax->at(jetindex), AODCaloJetMedianLog10TrackAngle->at(jetindex), AODCaloJetMedianLog10IPSig->at(jetindex));
  }


// matching
//  for(unsigned int k=0; k< aodcalojet_list.size(); ++k){
//   std::cout<<" calojet "<<k<<"  "<<AODCaloJetPt->at(aodcalojet_list[k])<<std::endl;
//  }
//  std::cout<<"\n"<<std::endl;
//  for(unsigned int k=0; k< aodpfjet_list.size(); ++k){
//   std::cout<<" pfjet "<<k<<"  "<<AODPFJetPt->at(aodpfjet_list[k])<<std::endl;
//  }
//  std::cout<<"\n"<<std::endl;
//  for(unsigned int k=0; k< aodpfchsjet_list.size(); ++k){
//   std::cout<<" pfchsjet "<<k<<"  "<<AODPFchsJetPt->at(aodpfchsjet_list[k])<<std::endl;
//  }
//  std::cout<<"\n"<<std::endl;
//  std::cout<<"\n"<<std::endl;
// 
//   // check to make sure both lists are always the same size
//   if( calomatchedPF_list.size()!=PFmatchedCalo_list.size() ){
//   std::cout<<" sizes: calo: "<<calomatchedPF_list.size()<<" pf: "<<PFmatchedCalo_list.size()<<std::endl;
//   }
//   if( calomatchedPFchs_list.size()!=PFchsmatchedCalo_list.size() ){
//   std::cout<<" sizes: calo: "<<calomatchedPFchs_list.size()<<" pfchs: "<<PFchsmatchedCalo_list.size()<<std::endl;
//   
//   }
// for(unsigned int k=0; k< calomatchedPF_list.size(); ++k){
//  std::cout<<" calomatchdedPF "<<k<<"  "<<calomatchedPF_list[k]<<" Pt "<<AODCaloJetPt->at(calomatchedPF_list[k])<<"  "<<AODCaloJetEta->at(calomatchedPF_list[k])<<"  "<<AODCaloJetPhi->at(calomatchedPF_list[k])<<std::endl;
// }
// for(unsigned int k=0; k< PFmatchedCalo_list.size(); ++k){
//  std::cout<<" PFmatchedCalo "<<k<<"  "<<PFmatchedCalo_list[k]<<" Pt "<<AODPFJetPt->at(PFmatchedCalo_list[k])<<"  "<<AODPFJetEta->at(PFmatchedCalo_list[k])<<"  "<<AODPFJetPhi->at(PFmatchedCalo_list[k])<<std::endl;
// }
// for(unsigned int k=0; k< calomatchedPFchs_list.size(); ++k){
//  std::cout<<" calomatchedPFchs "<<k<<calomatchedPFchs_list[k]<<" Pt "<<"  "<<AODCaloJetPt->at(calomatchedPFchs_list[k])<<AODCaloJetEta->at(calomatchedPFchs_list[k])<<AODCaloJetPhi->at(calomatchedPFchs_list[k])<<std::endl;
// }
// for(unsigned int k=0; k< PFchsmatchedCalo_list.size(); ++k){
//  std::cout<<" PFchsmatchedCalo "<<k<<PFchsmatchedCalo_list[k]<<" Pt "<<"  "<<AODPFchsJetPt->at(PFchsmatchedCalo_list[k])<<"  "<<AODPFchsJetEta->at(PFchsmatchedCalo_list[k])<<"  "<<AODPFchsJetPhi->at(PFchsmatchedCalo_list[k])<<std::endl;
// }
//
//
//  std::cout<<" calosize "<<aodcalojet_list.size()<<std::endl;
//  std::cout<<" calomatchedPF ";
//  for(unsigned int k=0; k< calomatchedPF_list.size(); ++k){
//   std::cout<<k<<" "<<calomatchedPF_list[k]<<"  ";
//  }
//  std::cout<<std::endl;
//
//  std::cout<<"\n"<<std::endl;
//  std::cout<<"\n"<<std::endl;




 return;
}


void analyzer_loop::debug_printtriggers()
{

 printf("AOD_HLT_Ele23Loose %llu \n", AOD_HLT_Ele23Loose) ;
 printf("AOD_HLT_Ele27Tight %llu \n", AOD_HLT_Ele27Tight) ;
 printf("AOD_HLT_Ele17Ele12 %llu \n", AOD_HLT_Ele17Ele12) ;
 printf("AOD_HLT_Ele23Ele12 %llu \n", AOD_HLT_Ele23Ele12) ;
 printf("AOD_HLT_IsoMu22    %llu \n", AOD_HLT_IsoMu22   ) ;
 printf("AOD_HLT_IsoTkMu22  %llu \n", AOD_HLT_IsoTkMu22 ) ;
 printf("AOD_HLT_Mu17Mu8    %llu \n", AOD_HLT_Mu17Mu8   ) ;
 printf("AOD_HLT_Mu17TkMu8  %llu \n", AOD_HLT_Mu17TkMu8 ) ;
 //printf("AOD_HLT_Photon90 %llu \n", AOD_HLT_Photon90) ;
 //printf("AOD_HLT_Photon120 %llu \n", AOD_HLT_Photon120) ;
 //printf("AOD_HLT_Photon175 %llu \n", AOD_HLT_Photon175) ;
 //printf("AOD_HLT_Photon165_HE10 %llu \n", AOD_HLT_Photon165_HE10) ;
 //printf("AOD_HLT_Mu8Ele23 %llu \n", AOD_HLT_Mu8Ele23) ;
 //printf("AOD_HLT_Mu23Ele12 %llu \n", AOD_HLT_Mu23Ele12) ;
 //printf("AOD_HLT_Mu12Ele23_DZ %llu \n", AOD_HLT_Mu12Ele23_DZ) ;
 //printf("AOD_HLT_Mu23Ele12_DZ %llu \n", AOD_HLT_Mu23Ele12_DZ) ;
 return;

}

void analyzer_loop::debug_printbitset()
{

 std::cout<<" bitsPassOneEleSig    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleSig    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoEleSig    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoEleSig    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuSig     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuSig     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoMuSig     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoMuSig     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneEleDY     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleDY     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoEleDY     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoEleDY     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuDY      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuDY      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoMuDY      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoMuDY      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneEleZH     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleZH     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoEleZH     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoEleZH     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuZH      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuZH      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoMuZH      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoMuZH      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneEleOffZ   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleOffZ   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoEleOffZ   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoEleOffZ   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuOffZ    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuOffZ    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoMuOffZ    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoMuOffZ    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneEleNoPair "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleNoPair >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuNoPair  "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuNoPair  >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassEleMuOSOF    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassEleMuOSOF    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassEleMuOSOFL   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassEleMuOSOFL   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOnePho       "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOnePho       >>i)&1 ); } 
 std::cout<<std::endl;

 return;

}


void analyzer_loop::debug_printbitkeys()
{

 std::cout<<" keyPassOneEleSig    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleSig    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoEleSig    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoEleSig    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuSig     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuSig     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoMuSig     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoMuSig     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneEleDY     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleDY     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoEleDY     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoEleDY     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuDY      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuDY      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoMuDY      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoMuDY      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneEleZH     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleZH     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoEleZH     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoEleZH     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuZH      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuZH      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoMuZH      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoMuZH      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneEleOffZ   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleOffZ   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoEleOffZ   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoEleOffZ   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuOffZ    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuOffZ    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoMuOffZ    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoMuOffZ    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneEleNoPair "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleNoPair >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuNoPair  "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuNoPair  >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassEleMuOSOF    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassEleMuOSOF    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassEleMuOSOFL   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassEleMuOSOFL   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOnePho       "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOnePho       >>i)&1 ); } 
 std::cout<<std::endl;
 return;

}

