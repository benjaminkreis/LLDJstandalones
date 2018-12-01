#include <iostream>
#include <fstream>
#include <unistd.h>

#include "analyzer_loop.h"
#include "TROOT.h"
#include <TChain.h>
#include <TString.h>
#include <TStopwatch.h>
 
#include <vector>
#include <map>

int main(int argc, char **argv){

 // start stopwatch
 TStopwatch sw;
 sw.Start();

 // for getting command line options
 // s - sample name
 // l - lumi
 // x - extra name
 // e - nr events to run over
 // j - jet type INCLUSIVETAGGEDCALOJETSAMATCHED
 // i - inpath
 // o - outpath
 // n - nfiles
 // a - start At file 
 // d - dolocal
 char *sample = NULL;
 char *slumi = (char*)"12900";
 char *sxname = (char*)"";
 char *sevts = (char*)"-1";
 char *inpath = (char*)"../lists";
 char *outpath = (char*)"../roots";
 char *nfiles = (char*)"-1";
 char *atfile = (char*)"0";
 bool dolocal = false;
 bool bisMC = false;
 
 int index;
 int s;

 opterr = 0;

 while ((s = getopt (argc, argv, "s:l:x:e:i:o:a:n:dm")) != -1)
  switch (s)
   {
   case 'm':
    bisMC = true;
   case 'd':
    dolocal = true;
    break;
   case 'a':
    atfile = optarg;
    break;
   case 'n':
    nfiles = optarg;
    break;
   case 'o':
    outpath = optarg;
    break;
   case 'i':
    inpath = optarg;
    break;
   case 'e':
    sevts = optarg;
    break;
   case 'x':
    sxname = optarg;
    break;
   case 'l':
    slumi = optarg;
    break;
   case 's':
    sample = optarg;
    break;
   case '?':
    if (optopt == 's' || optopt == 'l')
     fprintf (stderr, "Option -%c requires an argument.\n", optopt);
    else if (isprint (optopt))
     fprintf (stderr, "Unknown option `-%c'.\n", optopt);
    else
     fprintf (stderr,
              "Unknown option character `\\x%x'.\n",
              optopt);
    return 1;
   default:
    abort ();
   }

 for (index = optind; index < argc; index++)
   std::cout << "Non-option argument " << argv[index] << std::endl;

 std::cout << "Running sample: " << sample << std::endl;

 // easiest if we convert char to TString
 TString Tsample  = TString(sample);
 TString Txname   = TString(sxname);
 TString TSlumi   = TString(slumi);
 Float_t lumi     = TSlumi.Atof();
 TString TSevts   = TString(sevts);
 Int_t   TIevts   = TSevts.Atoi();
 TString Tinpath  = TString(inpath);  
 TString Toutpath = TString(outpath); 
 TString TSatfile = TString(atfile);  
 TString TSnfiles = TString(nfiles);
 Int_t   TIatfile = TSatfile.Atoi();
 Int_t   TInfiles = TSnfiles.Atoi();
 // MC vs Data
 Bool_t isMC=bisMC;

 std::cout << "Tsample: " << Tsample << std::endl;
 std::cout << "Txname: " << Txname << std::endl;
 std::cout << "TSlumi: " << TSlumi << std::endl;
 std::cout << "TSevts: " << TSevts << std::endl;
 std::cout << "TIatfile: " << TIatfile << std::endl;
 std::cout << "TInfiles: " << TInfiles << std::endl;

 Bool_t makelog=kFALSE;

 TString outfilename=Toutpath +"/"+Tsample+Txname;
 TString inputListName=Tinpath+"/"+Tsample+".list";
 TString inputInfoName=Tinpath+"/"+Tsample+".info";

 TChain *theChain = new TChain("lldjNtuple/EventTree");
 theChain->Reset();

 std::cout << "Input List Name: " << inputListName << std::endl;
 std::cout << "Output File Name: " << outfilename << std::endl;

 // lines read from file variables
 std::string inputline = "";
 TString Tinputline = "";
 std::vector<TString> inputline_dump;

 // ---- Get list of files to run over and put in TChain
 // open <samplename>.list
 std::ifstream inputfile;
 inputfile.open(inputListName);
 if( !inputfile.good() ) {
   std::cerr << "Cannot open the file: \"" << inputListName+"\""<<std::endl;
   abort();
 }
 
 // For dividing up input list
 Int_t nscanned = 0; // number of files scanned so far
 // we have the file open, start reading lines one by one
 while( std::getline(inputfile, inputline) ) {
  if( inputfile.fail() ) continue;

  // we have a flag to decide which file to start at
  nscanned++;
  if ( nscanned < TIatfile ) continue;
  if ( nscanned >= (TIatfile+TInfiles) ) continue;

  // TChain needs a TString..
  Tinputline = inputline;
  std::cout << "raw inputline: " << Tinputline << std::endl;

  // read input file names
  if( Tinputline.Contains("/home/rhombus") ){
   theChain->Add( Tinputline );
   std::cout << " Inputfile: " << Tinputline << std::endl;
  }

  if( Tinputline.Contains("/uscms/home") ){
   theChain->Add( Tinputline );
   std::cout << " Inputfile: " << Tinputline << std::endl;
  }

  if( Tinputline.Contains("/uscms_data/d3/tmperry") ){
   theChain->Add( Tinputline );
   std::cout << " Inputfile: " << Tinputline << std::endl;
  }

  if( Tinputline.Contains("/store/group") ){
   theChain->Add( "root://cmsxrootd.fnal.gov/"+Tinputline );
   std::cout << " Inputfile: " << Tinputline << std::endl;
  }

  // if( dolocal ){
  //  theChain->Add( "root://cmseos.fnal.gov/"+Tinputline );
  // }


  inputline_dump.push_back(inputline);
 } // while( std::getline(inputfile, inputline) )
 inputfile.close();

 // sample-dependent input variables 
 Float_t nrevents     ;
 Float_t crosssection ;
 Float_t avgTTSF = 1.    ;

 // ---- Get sample information 
 // open <samplename>.info
 inputfile.open(inputInfoName);
 if( !inputfile.good() ) {
   std::cerr << "Cannot open the file: \"" << inputInfoName+"\""<<std::endl;
   abort();
 }
 
 // we have the file open, start reading lines one by one
 while( std::getline(inputfile, inputline) ) {
  if( inputfile.fail() ) continue;

  Tinputline = inputline;

  // read crosssection
  if( Tinputline.Contains("crosssection: ") ){  
   Tinputline.ReplaceAll("crosssection: ","");
   crosssection = Tinputline.Atof();
   std::cout << "  crosssection: " << crosssection << std::endl;
  }

  // read nr events
  if( Tinputline.Contains("nrevents: ") ){  
   Tinputline.ReplaceAll("nrevents: ","");
   nrevents = Tinputline.Atof();
   std::cout << "  nrevents: " << nrevents << std::endl;
  }

  // read tt avg SF
  if( Tinputline.Contains("ttsf: ") ){  
   Tinputline.ReplaceAll("ttsf: ","");
   avgTTSF = Tinputline.Atof();
   std::cout << "  avgTTSF: " << avgTTSF << std::endl;
  }
  inputline_dump.push_back(inputline);
 } //while !inputfile.eof()

 std::cout << "  lumi: " << lumi << std::endl;

 std::vector<TString> unccategories;
 unccategories.push_back("");
if( isMC ){
  unccategories.push_back("_EGSUp");
  unccategories.push_back("_EGSDown");
  unccategories.push_back("_MESUp");
  unccategories.push_back("_MESDown");
  //unccategories.push_back("_JESUp");
  //unccategories.push_back("_JESDown");
  unccategories.push_back("_AMaxUp");
  unccategories.push_back("_AMaxDown");
  unccategories.push_back("_IPSigUp");
  unccategories.push_back("_IPSigDown");
  unccategories.push_back("_TAUp");
  unccategories.push_back("_TADown");
  unccategories.push_back("_TagVarsUp");
  unccategories.push_back("_TagVarsDown");
 }
 
 // make the analyzer, init some stuff
 analyzer_loop analyzer;
 analyzer.Init(theChain, isMC, makelog);
 analyzer.setConfiguration();

 // file to be filled with slimmed tree
 // must be created before TTree, put here to get name aligned
 TFile* optfile = new TFile(outfilename+"_OPTtree.root", "RECREATE");
 TFile* NM1file = new TFile(outfilename+"_NM1tree.root", "RECREATE");

 TString outfilenamebase = outfilename;
 for(unsigned int i=0; i<unccategories.size(); ++i){
  TString unccategory = unccategories.at(i);
  //outfilename = outfilenamebase + unccategory;

  analyzer.initSelectionCategories( );
  analyzer.initEleHistograms( unccategory );
  analyzer.initMuHistograms( unccategory );
  analyzer.initLepHistograms( unccategory );
  analyzer.initPhoHistograms( unccategory );
  analyzer.initMETHTHistograms( unccategory );
  analyzer.initTTOCHistograms( unccategory );
  //analyzer.initExtraHistograms( unccategory );
  analyzer.initAODCaloJetBasicHistograms( unccategory );
  analyzer.initAODCaloJetExtraHistograms( unccategory ); 
  analyzer.initAODCaloJetTagHistograms( unccategory ); 
  analyzer.initAODCaloJetTagMultHistograms( unccategory );
  analyzer.initAODCaloJetMultHistograms( unccategory );
  analyzer.initCutflowHistograms( unccategory );
  analyzer.init2DHistograms( unccategory );
  analyzer.initBackgroundEstimateHistograms();	

  analyzer.Loop(outfilename, lumi, nrevents, crosssection, avgTTSF, TIevts, optfile, NM1file, unccategory);
 }

 // end stopwatch
 sw.Stop();
 std::cout << "Real Time: " << sw.RealTime()/60.0 << std::endl;
 std::cout << "CPU Time: " << sw.CpuTime()/60.0 << std::endl;
 std::cout << "Done with " << Tsample << std::endl;

 return 0;
}
