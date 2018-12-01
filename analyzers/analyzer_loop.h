#ifndef analyzer_loop_h
#define analyzer_loop_h

#include "analyzer_tree.h"
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TMath.h>
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include <stdlib.h> 
class analyzer_loop : public analyzer_tree {

public :
 // basic functions
               analyzer_loop();
 virtual       ~analyzer_loop();
 virtual void  Loop(TString outfilename, 
                    Float_t lumi, Float_t nrEvents,
                    Float_t crossSec, Float_t avgTTSF, Int_t nevts, 
                    TFile *optfile, TFile *NM1file, TString uncbin);
 static const int  width = 8;
 // debug options, printouts
 virtual void debug_printobjects();
 virtual void debug_printdilep();
 virtual void debug_printmuons();
 virtual void debug_printelectrons();
 virtual void debug_printphotons();
 virtual void debug_printjets();
 virtual void debug_printtriggers();
 virtual void debug_printbitset();
 virtual void debug_printbitkeys();
};

#endif
