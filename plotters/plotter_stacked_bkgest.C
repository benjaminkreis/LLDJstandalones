#include <iostream>

#include "TString.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TText.h"
#include "TFile.h"

#include <stdlib.h>     /* getenv */

using namespace std;

void plotter_stacked_bkest(TString region = "Sig")
{

  //TString region = "NoSel";

 // Draw signal as lines
 Bool_t drawSignal = kFALSE; //kTRUE;
 Bool_t drawRatio = kFALSE;
 // y axis plots as log
 Bool_t dolog = kTRUE;

 // path to root files
 TString inpath  = TString("../roots/");
 TString outpath = TString("../plots/");
 //TString aversion = TString(getenv("aversion"));

 TString aversion = "est" ;
 inpath = inpath+aversion+"/";
 outpath = outpath+aversion+"/";

 TString extraname = "";
 if(dolog){extraname+="_log";}
 if(drawSignal){extraname+="_wsig";}

 // phase space regions to plot
 /*
 std::vector<TString> regions;
 regions.clear();
 regions.push_back("NoSel");
 regions.push_back("Sig");
 regions.push_back("ZH");
 regions.push_back("DY");
 regions.push_back("OffZ");
 regions.push_back("NoPair"); 
 */

 // lepton flavor
 std::vector<TString> leptons;
 leptons.clear();
 leptons.push_back("ele"); 
 leptons.push_back("mu");  
 //leptons.push_back("NoLepSel");

 // variables to plot
 std::vector<TString> variables;
 variables.clear();

 //variables.push_back("nVtx");                   
 // variables.push_back("nGoodVtx");               
 // variables.push_back("nTrksPV");                
//  variables.push_back("rho");                    
  //variables.push_back("pfMET");                  
  //variables.push_back("pfMETPhi");               
//  variables.push_back("pfMETsumEt");             
  //variables.push_back("nPho");                   
//  variables.push_back("phoE");                   
//  variables.push_back("phoEt");                  
//  variables.push_back("phoEta");                 
//  variables.push_back("phoPhi");                 
//  variables.push_back("phoCalibE");              
//  variables.push_back("phoCalibEt");             
//  variables.push_back("phoSCE");                 
//  variables.push_back("phoSCRawE");              
//  variables.push_back("phoSCPhi");               
//  variables.push_back("phoSCEta");               
//  variables.push_back("nEle");                   
 // variables.push_back("elePt");                  
//  variables.push_back("eleEta");                 
//  variables.push_back("elePhi");                 
//  variables.push_back("eleSCEn");                
//  variables.push_back("eleSCEta");               
//  variables.push_back("eleSCPhi");               
//  variables.push_back("eleCalibPt");             
//  variables.push_back("eleCalibEn");             
//  variables.push_back("nMu");                    
//  variables.push_back("muPt");                   
//  variables.push_back("muEn");                   
//  variables.push_back("muEta");                  
//  variables.push_back("muPhi");                  
//  variables.push_back("nJet");                   
//  variables.push_back("htall"); 
//  variables.push_back("htjets");
//  variables.push_back("nSelectedPho");
//  variables.push_back("nSelectedEle");
//  variables.push_back("nSelectedMuo");
//  variables.push_back("nSelectedJet");
//  variables.push_back("LeadingJet_jetPt");                      
//  variables.push_back("LeadingJet_jetEn");                      
//  variables.push_back("LeadingJet_jetEta");                     
//  variables.push_back("LeadingJet_jetPhi");                     
//  variables.push_back("LeadingJet_jetArea");                    
//  variables.push_back("LeadingJet_jetLeadTrackPt");             
//  variables.push_back("LeadingJet_jetLeadTrackEta");            
//  variables.push_back("LeadingJet_jetLeadTrackPhi");            
//  variables.push_back("LeadingJet_jetCSV2BJetTags");            
//  variables.push_back("LeadingJet_jetJetProbabilityBJetTags");  
//  variables.push_back("LeadingJet_jetpfCombinedMVAV2BJetTags"); 
//  variables.push_back("LeadingJet_jetAlphaMax");                
//  variables.push_back("LeadingJet_jetAlphaMax2");               
//  variables.push_back("LeadingJet_jetAlphaMaxP");               
//  variables.push_back("LeadingJet_jetAlphaMaxP2");              
//  variables.push_back("LeadingJet_alphaMax_jetDauVertex_r");    
//  variables.push_back("LeadingJet_jetAlphaMax_PV3onPV2");       
//  variables.push_back("LeadingJet_jetAlphaMax_PV3onNeu");       
//  variables.push_back("LeadingJet_jetAlphaMax_PV3onAll");       
//  variables.push_back("LeadingJet_jetAlphaMax_PV2onNeu");       
//  variables.push_back("LeadingJet_jetAlphaMax_PV2onAll");       
//  variables.push_back("LeadingJet_jetAlpha2Max_PV3onPV2");      
//  variables.push_back("LeadingJet_jetAlpha2Max_PV3onNeu");      
//  variables.push_back("LeadingJet_jetAlpha2Max_PV3onAll");      
//  variables.push_back("LeadingJet_jetAlpha2Max_PV2onNeu");      
//  variables.push_back("LeadingJet_jetAlpha2Max_PV2onAll");      
//  variables.push_back("LeadingJet_jetAlphaD");                  
//  variables.push_back("LeadingJet_jetAlphaMaxD");               
//  variables.push_back("LeadingJet_jetLog10IPSig");              
//  variables.push_back("LeadingJet_jetMedianLog10IPSig");        
//  variables.push_back("LeadingJet_jetSumIP");                   
//  variables.push_back("LeadingJet_jetSumIPSig");                
//  variables.push_back("LeadingJet_jetTrackAngle");              
//  variables.push_back("LeadingJet_jetLogTrackAngle");           
//  variables.push_back("LeadingJet_jetMedianLogTrackAngle");     
//  variables.push_back("LeadingJet_jetTotalTrackAngle");         
//  variables.push_back("LeadingJet_jetNConstituents");           
/*
 variables.push_back("AOD_dilepton_Pt");
 variables.push_back("AllJets_AODCaloJetPtVar");
 variables.push_back("AllTags_AODCaloJetPtVar_Tag0");
 variables.push_back("AllJets_AODCaloJetMinDR");
 variables.push_back("AllTags_AODCaloJetMinDR_Tag0");
 variables.push_back("AllJets_AODCaloJetAbsEta");
 variables.push_back("AllTags_AODCaloJetAbsEta_Tag0");
 variables.push_back("AllJets_AODCaloJetNCleanMatchedTracks");
 variables.push_back("AllTags_AODCaloJetNCleanMatchedTracks_Tag0");
*/
 variables.push_back("bkgest");

 // make canvas and text
 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);
 gStyle->SetPalette(kBird);
 //gStyle->InvertPalette();
 //TColor::InvertPalette();

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.04);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.04);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 //extra->SetTextAlign(13);
 extra->SetTextFont(52);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.03);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 // initialize histogram files 

 TFile* file_SingleElectron                      ; 
 TFile* file_SingleMuon                          ; 
 TFile* file_DY50                                ;
 TFile* file_DY5to50_HT100To200                  ; 
 TFile* file_DY5to50_HT200To400                  ; 
 TFile* file_DY5to50_HT400To600                  ; 
 TFile* file_DY5to50_HT600ToInf                  ; 
 TFile* file_DY5to50_HT70To100                   ; 
 TFile* file_ggZH_HToBB_ZToLL                    ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS0        ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS0p05     ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS1        ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS10       ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS100      ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS1000     ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS10000    ;
 TFile* file_GJets_HT40To100                     ;
 TFile* file_GJets_HT100To200                    ;
 TFile* file_GJets_HT200To400                    ;
 TFile* file_GJets_HT400To600                    ;
 TFile* file_GJets_HT600ToInf                    ;
 TFile* file_ST_s                                ;
 TFile* file_STbar_t                             ;
 TFile* file_ST_t                                ;
 TFile* file_STbar_tW                            ;
 TFile* file_ST_tW                               ;
 TFile* file_TTtoLL                              ;
 TFile* file_TTtoLfromTbar                       ;
 TFile* file_TTtoLfromT                          ;
 TFile* file_WG                                  ;
 TFile* file_WJetsToLNu                          ;
 TFile* file_WWToLNuLNu                          ;
 TFile* file_WWToLNuQQ                           ;
 TFile* file_WZToL3Nu                            ;
 TFile* file_WZTo3LNu                            ;
 TFile* file_WZToLNu2QorQQ2L                     ;
 TFile* file_ZG                                  ;
 TFile* file_ZH_HToBB_ZToLL                      ;
 TFile* file_ZZToLLNuNu                          ;
 TFile* file_ZZToLLQQ                            ;
 TFile* file_ZZToNuNuQQ                          ;
 TFile* file_ZZToLLLL                            ;

 // initialize histos
 TH1F* h_DY50                                ;
 TH1F* h_DY5to50_HT100To200                  ; 
 TH1F* h_DY5to50_HT200To400                  ; 
 TH1F* h_DY5to50_HT400To600                  ; 
 TH1F* h_DY5to50_HT600ToInf                  ; 
 TH1F* h_DY5to50_HT70To100                   ; 
 TH1F* h_ggZH_HToBB_ZToLL                    ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS0        ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS0p05     ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS1        ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS10       ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS100      ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS1000     ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS10000    ;
 TH1F* h_GJets_HT40To100                     ;
 TH1F* h_GJets_HT100To200                    ;
 TH1F* h_GJets_HT200To400                    ;
 TH1F* h_GJets_HT400To600                    ;
 TH1F* h_GJets_HT600ToInf                    ;
 TH1F* h_ST_s                                ;
 TH1F* h_STbar_t                             ;
 TH1F* h_ST_t                                ;
 TH1F* h_STbar_tW                            ;
 TH1F* h_ST_tW                               ;
 TH1F* h_TTtoLL                              ;
 TH1F* h_TTtoLfromTbar                       ;
 TH1F* h_TTtoLfromT                          ;
 TH1F* h_WG                                  ;
 TH1F* h_WJetsToLNu                          ;
 TH1F* h_WWToLNuLNu                          ;
 TH1F* h_WWToLNuQQ                           ;
 TH1F* h_WZToL3Nu                            ;
 TH1F* h_WZTo3LNu                            ;
 TH1F* h_WZToLNu2QorQQ2L                     ;
 TH1F* h_ZG                                  ;
 TH1F* h_ZH_HToBB_ZToLL                      ;
 TH1F* h_ZZToLLNuNu                          ;
 TH1F* h_ZZToLLQQ                            ;
 TH1F* h_ZZToNuNuQQ                          ;
 TH1F* h_ZZToLLLL                            ;
 //TH1F* h_SingleElectron                      ;
 //TH1F* h_SingleMuon                          ;
// TH1F* h_DoubleEG                            ;
// TH1F* h_DoubleMuon                          ;
// TH1F* h_MuonEG                              ;

 // (combined) histos to be made
 TH1F* h_DY     ;
 TH1F* h_GJets  ;
 TH1F* h_ST     ;
 TH1F* h_VV     ;
 TH1F* h_VG     ;
 TH1F* h_ZH     ;
 TH1F* h_TT     ;
 TH1F* h_Totbkg ;

 TH1F* h_Data   ;

 // load histogram files
// file_DY5to50_HT100To200                = new TFile( inpath + "DY5to50_HT100To200_"+region+"_histograms.root"               ) ; 
// file_DY5to50_HT200To400                = new TFile( inpath + "DY5to50_HT200To400_"+region+"_histograms.root"               ) ; 
// file_DY5to50_HT400To600                = new TFile( inpath + "DY5to50_HT400To600_"+region+"_histograms.root"               ) ; 
// file_DY5to50_HT600ToInf                = new TFile( inpath + "DY5to50_HT600ToInf_"+region+"_histograms.root"               ) ; 
// file_DY5to50_HT70To100                 = new TFile( inpath + "DY5to50_HT70To100_"+region+"_histograms.root"                ) ; 
 file_DY50                              = new TFile( inpath + "DY50_"+region+"_bkgest.root"                             ) ;


// file_ggZH_HToBB_ZToLL                  = new TFile( inpath + "ggZH_HToBB_ZToLL_"+region+"_bkgest.root"                 ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS0      = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS0_"+region+"_bkgest.root"     ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS0p05   = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS0p05_"+region+"_bkgest.root"  ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS1      = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS1_"+region+"_bkgest.root"     ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS10     = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS10_"+region+"_bkgest.root"    ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS100    = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS100_"+region+"_bkgest.root"   ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS1000   = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS1000_"+region+"_bkgest.root"  ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS10000  = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS10000_"+region+"_bkgest.root" ) ;
// file_GJets_HT40To100                   = new TFile( inpath + "GJets_HT40To100_"+region+"_bkgest.root"                  ) ;
// file_GJets_HT100To200                  = new TFile( inpath + "GJets_HT100To200_"+region+"_bkgest.root"                 ) ;
// file_GJets_HT200To400                  = new TFile( inpath + "GJets_HT200To400_"+region+"_bkgest.root"                 ) ;
// file_GJets_HT400To600                  = new TFile( inpath + "GJets_HT400To600_"+region+"_bkgest.root"                 ) ;
// file_GJets_HT600ToInf                  = new TFile( inpath + "GJets_HT600ToInf_"+region+"_bkgest.root"                 ) ;
 file_ST_s                              = new TFile( inpath + "ST_s_"+region+"_bkgest.root"                             ) ;
 file_STbar_t                           = new TFile( inpath + "STbar_t_"+region+"_bkgest.root"                          ) ;
 file_ST_t                              = new TFile( inpath + "ST_t_"+region+"_bkgest.root"                             ) ;
 file_STbar_tW                          = new TFile( inpath + "STbar_tW_"+region+"_bkgest.root"                         ) ;
 file_ST_tW                             = new TFile( inpath + "ST_tW_"+region+"_bkgest.root"                            ) ;
 file_TTtoLL                            = new TFile( inpath + "TTtoLL_"+region+"_bkgest.root"                           ) ;
 file_TTtoLfromTbar                     = new TFile( inpath + "TTtoLfromTbar_"+region+"_bkgest.root"                    ) ;
 file_TTtoLfromT                        = new TFile( inpath + "TTtoLfromT_"+region+"_bkgest.root"                       ) ;
 //file_WG                                = new TFile( inpath + "WG_"+region+"_bkgest.root"                               ) ;
 file_WJetsToLNu                        = new TFile( inpath + "WJetsToLNu_"+region+"_bkgest.root"                       ) ;
 file_WWToLNuLNu                        = new TFile( inpath + "WWToLNuLNu_"+region+"_bkgest.root"                       ) ;
 file_WWToLNuQQ                         = new TFile( inpath + "WWToLNuQQ_"+region+"_bkgest.root"                        ) ;
 file_WZToL3Nu                          = new TFile( inpath + "WZToL3Nu_"+region+"_bkgest.root"                         ) ;
 file_WZTo3LNu                          = new TFile( inpath + "WZTo3LNu_"+region+"_bkgest.root"                         ) ;
 file_WZToLNu2QorQQ2L                   = new TFile( inpath + "WZToLNu2QorQQ2L_"+region+"_bkgest.root"                  ) ;
 //file_ZG                                = new TFile( inpath + "ZG_"+region+"_bkgest.root"                               ) ;
 //file_ZH_HToBB_ZToLL                    = new TFile( inpath + "ZH_HToBB_ZToLL_"+region+"_bkgest.root"                   ) ;
 file_ZZToLLNuNu                        = new TFile( inpath + "ZZToLLNuNu_"+region+"_bkgest.root"                       ) ;
 file_ZZToLLQQ                          = new TFile( inpath + "ZZToLLQQ_"+region+"_bkgest.root"                         ) ;
 file_ZZToNuNuQQ                        = new TFile( inpath + "ZZToNuNuQQ_"+region+"_bkgest.root"                       ) ;
 file_ZZToLLLL                          = new TFile( inpath + "ZZToLLLL_"+region+"_bkgest.root"                         ) ;
 //file_SingleElectron                    = new TFile( inpath + "SingleElectron_"+region+"_bkgest.root"                   ) ;
 //file_SingleMuon                        = new TFile( inpath + "SingleMuon_"+region+"_bkgest.root"                       ) ;
// file_DoubleEG                          = new TFile( inpath + "DoubleEG_"+region+"_bkgest.root"                         ) ;
// file_DoubleMuon                        = new TFile( inpath + "DoubleMuon_"+region+"_bkgest.root"                       ) ;
// file_MuonEG                            = new TFile( inpath + "MuonEG_"+region+"_bkgest.root"                           ) ;


 TFile* fout = TFile::Open("fout_"+region+"_bkgest.root", "RECREATE");
 


  for(unsigned int j=0; j<variables.size(); ++j){
   TString variable = variables[j];
   for(unsigned int k=0; k<leptons.size(); ++k){
    TString lepton = leptons[k];

    //TString varname = lepton+"_"+region+"_"+variable;
    TString varname = variable;

    printf("plotting  h_%s \n",varname.Data());
    TString outname = outpath+varname+extraname; 
    TString logname = outpath+"logs/"+varname+extraname; 
    cout << "logname: " << logname << endl;

    // get histograms from files
    //h_DY10to50                          = (TH1F*)file_DY10to50                         ->Get("h_"+varname)->Clone( "DY10to50"                         ) ;
//    h_DY5to50_HT100To200                = (TH1F*)file_DY5to50_HT100To200               ->Get("h_"+varname)->Clone( "DY5to50_HT100To200"               ) ; 
//    h_DY5to50_HT200To400                = (TH1F*)file_DY5to50_HT200To400               ->Get("h_"+varname)->Clone( "DY5to50_HT200To400"               ) ; 
//    h_DY5to50_HT400To600                = (TH1F*)file_DY5to50_HT400To600               ->Get("h_"+varname)->Clone( "DY5to50_HT400To600"               ) ; 
//    h_DY5to50_HT600ToInf                = (TH1F*)file_DY5to50_HT600ToInf               ->Get("h_"+varname)->Clone( "DY5to50_HT600ToInf"               ) ; 
//    h_DY5to50_HT70To100                 = (TH1F*)file_DY5to50_HT70To100                ->Get("h_"+varname)->Clone( "DY5to50_HT70To100"                ) ; 
    h_DY50                              = (TH1F*)file_DY50                             ->Get("h_"+varname)->Clone( "DY50"                             ) ;
//    h_ggZH_HToBB_ZToLL                  = (TH1F*)file_ggZH_HToBB_ZToLL                 ->Get("h_"+varname)->Clone( "ggZH_HToBB_ZToLL"                 ) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS0      = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS0     ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS0"     ) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS0p05   = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS0p05"  ) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS1      = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS1     ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS1"     ) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS10     = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS10    ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS10"    ) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS100    = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS100   ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS100"   ) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS1000   = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS1000"  ) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS10000  = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS10000" ) ;
//    h_GJets_HT40To100                   = (TH1F*)file_GJets_HT40To100                  ->Get("h_"+varname)->Clone( "GJets_HT40To100"                  ) ;
//    h_GJets_HT100To200                  = (TH1F*)file_GJets_HT100To200                 ->Get("h_"+varname)->Clone( "GJets_HT100To200"                 ) ;
//    h_GJets_HT200To400                  = (TH1F*)file_GJets_HT200To400                 ->Get("h_"+varname)->Clone( "GJets_HT200To400"                 ) ;
//    h_GJets_HT400To600                  = (TH1F*)file_GJets_HT400To600                 ->Get("h_"+varname)->Clone( "GJets_HT400To600"                 ) ;
//    h_GJets_HT600ToInf                  = (TH1F*)file_GJets_HT600ToInf                 ->Get("h_"+varname)->Clone( "GJets_HT600ToInf"                 ) ;
    h_ST_s                              = (TH1F*)file_ST_s                             ->Get("h_"+varname)->Clone( "ST_s"                             ) ;

    h_STbar_t                           = (TH1F*)file_STbar_t                          ->Get("h_"+varname)->Clone( "STbar_t"                          ) ;
    h_ST_t                              = (TH1F*)file_ST_t                             ->Get("h_"+varname)->Clone( "ST_t"                             ) ;
    h_STbar_tW                          = (TH1F*)file_STbar_tW                         ->Get("h_"+varname)->Clone( "STbar_tW"                         ) ;

    h_ST_tW                             = (TH1F*)file_ST_tW                            ->Get("h_"+varname)->Clone( "ST_tW"                            ) ;



    h_TTtoLL                            = (TH1F*)file_TTtoLL                           ->Get("h_"+varname)->Clone( "TTtoLL"                           ) ;
    h_TTtoLfromTbar                     = (TH1F*)file_TTtoLfromTbar                    ->Get("h_"+varname)->Clone( "TTtoLfromTbar"                    ) ;
    h_TTtoLfromT                        = (TH1F*)file_TTtoLfromT                       ->Get("h_"+varname)->Clone( "TTtoLfromT"                       ) ;
    //h_WG                                = (TH1F*)file_WG                               ->Get("h_"+varname)->Clone( "WG"                               ) ;

    h_WJetsToLNu                        = (TH1F*)file_WJetsToLNu                       ->Get("h_"+varname)->Clone( "WJetsToLNu"                       ) ;
    h_WWToLNuLNu                        = (TH1F*)file_WWToLNuLNu                       ->Get("h_"+varname)->Clone( "WWToLNuLNu"                       ) ;
    h_WWToLNuQQ                         = (TH1F*)file_WWToLNuQQ                        ->Get("h_"+varname)->Clone( "WWToLNuQQ"                        ) ;
    h_WZToL3Nu                          = (TH1F*)file_WZToL3Nu                         ->Get("h_"+varname)->Clone( "WZToL3Nu"                         ) ;

    h_WZTo3LNu                          = (TH1F*)file_WZTo3LNu                         ->Get("h_"+varname)->Clone( "WZTo3LNu"                         ) ;
    h_WZToLNu2QorQQ2L                   = (TH1F*)file_WZToLNu2QorQQ2L                  ->Get("h_"+varname)->Clone( "WZToLNu2QorQQ2L"                  ) ;
    //h_ZG                                = (TH1F*)file_ZG                               ->Get("h_"+varname)->Clone( "ZG"                               ) ;
    //h_ZH_HToBB_ZToLL                    = (TH1F*)file_ZH_HToBB_ZToLL                   ->Get("h_"+varname)->Clone( "ZH_HToBB_ZToLL"                   ) ;
    h_ZZToLLNuNu                        = (TH1F*)file_ZZToLLNuNu                       ->Get("h_"+varname)->Clone( "ZZToLLNuNu"                       ) ;
    h_ZZToLLQQ                          = (TH1F*)file_ZZToLLQQ                         ->Get("h_"+varname)->Clone( "ZZToLLQQ"                         ) ;
    h_ZZToNuNuQQ                        = (TH1F*)file_ZZToNuNuQQ                       ->Get("h_"+varname)->Clone( "ZZToNuNuQQ"                       ) ;
    h_ZZToLLLL                          = (TH1F*)file_ZZToLLLL                         ->Get("h_"+varname)->Clone( "ZZToLLLL"                         ) ;
    //h_SingleElectron                    = (TH1F*)file_SingleElectron                   ->Get("h_"+varname)->Clone( "SingleElectron"                   ) ;
    //h_SingleMuon                        = (TH1F*)file_SingleMuon                       ->Get("h_"+varname)->Clone( "SingleMuon"                       ) ;
    //h_DoubleEG                          = (TH1F*)file_DoubleEG                         ->Get("h_"+varname)->Clone( "DoubleEG"                         ) ;
    //h_DoubleMuon                        = (TH1F*)file_DoubleMuon                       ->Get("h_"+varname)->Clone( "DoubleMuon"                       ) ;
    //h_MuonEG                            = (TH1F*)file_MuonEG                           ->Get("h_"+varname)->Clone( "MuonEG"                           ) ;

    //// tmp remove next run !!! screwed up XCs for VG
    //h_WG->Scale(405.271/9405.271);
    //h_ZG->Scale(117.864/9117.864);

    // integrals of histograms
//    Double_t int_DY5to50_HT100To200                = h_DY5to50_HT100To200               ->Integral(0,-1) ; 
//    Double_t int_DY5to50_HT200To400                = h_DY5to50_HT200To400               ->Integral(0,-1) ; 
//    Double_t int_DY5to50_HT400To600                = h_DY5to50_HT400To600               ->Integral(0,-1) ; 
//    Double_t int_DY5to50_HT600ToInf                = h_DY5to50_HT600ToInf               ->Integral(0,-1) ; 
//    Double_t int_DY5to50_HT70To100                 = h_DY5to50_HT70To100                ->Integral(0,-1) ; 
    Double_t int_DY50                              = h_DY50                             ->Integral(0,-1) ;
//    Double_t int_ggZH_HToBB_ZToLL                  = h_ggZH_HToBB_ZToLL                 ->Integral(0,-1) ;
//    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS0      = h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1) ;
//    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS0p05   = h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1) ;
//    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS1      = h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1) ;
//    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS10     = h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1) ;
//    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS100    = h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1) ;
//    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS1000   = h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1) ;
//    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS10000  = h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) ;
//    Double_t int_GJets_HT40To100                   = h_GJets_HT40To100                  ->Integral(0,-1) ;
//    Double_t int_GJets_HT100To200                  = h_GJets_HT100To200                 ->Integral(0,-1) ;
//    Double_t int_GJets_HT200To400                  = h_GJets_HT200To400                 ->Integral(0,-1) ;
//    Double_t int_GJets_HT400To600                  = h_GJets_HT400To600                 ->Integral(0,-1) ;
//    Double_t int_GJets_HT600ToInf                  = h_GJets_HT600ToInf                 ->Integral(0,-1) ;
    Double_t int_ST_s                              = h_ST_s                             ->Integral(0,-1) ;
    Double_t int_STbar_t                           = h_STbar_t                          ->Integral(0,-1) ;
    Double_t int_ST_t                              = h_ST_t                             ->Integral(0,-1) ;
    Double_t int_STbar_tW                          = h_STbar_tW                         ->Integral(0,-1) ;
    Double_t int_ST_tW                             = h_ST_tW                            ->Integral(0,-1) ;
    Double_t int_TTtoLL                            = h_TTtoLL                           ->Integral(0,-1) ;
    Double_t int_TTtoLfromTbar                     = h_TTtoLfromTbar                    ->Integral(0,-1) ;
    Double_t int_TTtoLfromT                        = h_TTtoLfromT                       ->Integral(0,-1) ;
    //Double_t int_WG                                = h_WG                               ->Integral(0,-1) ;
    Double_t int_WJetsToLNu                        = h_WJetsToLNu                       ->Integral(0,-1) ;
    Double_t int_WWToLNuLNu                        = h_WWToLNuLNu                       ->Integral(0,-1) ;
    Double_t int_WWToLNuQQ                         = h_WWToLNuQQ                        ->Integral(0,-1) ;
    Double_t int_WZToL3Nu                          = h_WZToL3Nu                         ->Integral(0,-1) ;
    Double_t int_WZTo3LNu                          = h_WZTo3LNu                         ->Integral(0,-1) ;
    Double_t int_WZToLNu2QorQQ2L                   = h_WZToLNu2QorQQ2L                  ->Integral(0,-1) ;
    //Double_t int_ZG                                = h_ZG                               ->Integral(0,-1) ;
    //Double_t int_ZH_HToBB_ZToLL                    = h_ZH_HToBB_ZToLL                   ->Integral(0,-1) ;
    Double_t int_ZZToLLNuNu                        = h_ZZToLLNuNu                       ->Integral(0,-1) ;
    Double_t int_ZZToLLQQ                          = h_ZZToLLQQ                         ->Integral(0,-1) ;
    Double_t int_ZZToNuNuQQ                        = h_ZZToNuNuQQ                       ->Integral(0,-1) ;
    Double_t int_ZZToLLLL                          = h_ZZToLLLL                         ->Integral(0,-1) ;
    //Double_t int_SingleElectron                    = h_SingleElectron                   ->Integral(0,-1) ;
    //Double_t int_SingleMuon                        = h_SingleMuon                       ->Integral(0,-1) ;
    //Double_t int_DoubleEG                          = h_DoubleEG                         ->Integral(0,-1) ;
    //Double_t int_DoubleMuon                        = h_DoubleMuon                       ->Integral(0,-1) ;
    //Double_t int_MuonEG                            = h_MuonEG                           ->Integral(0,-1) ;

    FILE * outtable;
    outtable = fopen (logname+".tex","w");
     fprintf (outtable, "\\documentclass{standalone}\n\n");
     fprintf (outtable, "\\begin{document}\n\n");
     fprintf (outtable, "\\begin{tabular}{rl}\n\n");
     fprintf (outtable, " \\Huge %s & \\Huge %s   \\\\\n", lepton.Data(), region.Data()); 
     fprintf (outtable, " \\hline \n");
     fprintf (outtable, "\\Large  Backgrounds \\\\\n");
     fprintf (outtable, " \\hline \n");
     //fprintf (outtable, "DY10to50                          & %3.1f  \\\\\n", int_DY10to50                         ) ;
//     fprintf (outtable, "DY5to50_HT100To200                & %3.1f  \\\\\n", int_DY5to50_HT100To200               ) ; 
//     fprintf (outtable, "DY5to50_HT200To400                & %3.1f  \\\\\n", int_DY5to50_HT200To400               ) ; 
//     fprintf (outtable, "DY5to50_HT400To600                & %3.1f  \\\\\n", int_DY5to50_HT400To600               ) ; 
//     fprintf (outtable, "DY5to50_HT600ToInf                & %3.1f  \\\\\n", int_DY5to50_HT600ToInf               ) ; 
//     fprintf (outtable, "DY5to50_HT70To100                 & %3.1f  \\\\\n", int_DY5to50_HT70To100                ) ; 

     fprintf (outtable, "DY50                              & %3.1f  \\\\\n", int_DY50                             ) ;

//     fprintf (outtable, "ggZH\\_HToBB\\_ZToLL              & %3.1f  \\\\\n", int_ggZH_HToBB_ZToLL                 ) ;
//     fprintf (outtable, "GJets\\_HT40To100                 & %3.1f  \\\\\n", int_GJets_HT40To100                  ) ;
//     fprintf (outtable, "GJets\\_HT100To200                & %3.1f  \\\\\n", int_GJets_HT100To200                 ) ;
//     fprintf (outtable, "GJets\\_HT200To400                & %3.1f  \\\\\n", int_GJets_HT200To400                 ) ;
//     fprintf (outtable, "GJets\\_HT400To600                & %3.1f  \\\\\n", int_GJets_HT400To600                 ) ;
//     fprintf (outtable, "GJets\\_HT600ToInf                & %3.1f  \\\\\n", int_GJets_HT600ToInf                 ) ;
     fprintf (outtable, "ST\\_s                            & %3.1f  \\\\\n", int_ST_s                             ) ;
     fprintf (outtable, "STbar\\_t                         & %3.1f  \\\\\n", int_STbar_t                          ) ;
     fprintf (outtable, "ST\\_t                            & %3.1f  \\\\\n", int_ST_t                             ) ;
     fprintf (outtable, "STbar\\_tW                        & %3.1f  \\\\\n", int_STbar_tW                         ) ;
     fprintf (outtable, "ST\\_tW                           & %3.1f  \\\\\n", int_ST_tW                            ) ;
     fprintf (outtable, "TTtoLL                            & %3.1f  \\\\\n", int_TTtoLL                           ) ;
     fprintf (outtable, "TTtoLfromTbar                     & %3.1f  \\\\\n", int_TTtoLfromTbar                    ) ;
     fprintf (outtable, "TTtoLfromT                        & %3.1f  \\\\\n", int_TTtoLfromT                       ) ;
     //fprintf (outtable, "WG                                & %3.1f  \\\\\n", int_WG                               ) ;
     fprintf (outtable, "WJetsToLNu                        & %3.1f  \\\\\n", int_WJetsToLNu                       ) ;
     fprintf (outtable, "WWToLNuLNu                        & %3.1f  \\\\\n", int_WWToLNuLNu                       ) ;
     fprintf (outtable, "WWToLNuQQ                         & %3.1f  \\\\\n", int_WWToLNuQQ                        ) ;
     fprintf (outtable, "WZToL3Nu                          & %3.1f  \\\\\n", int_WZToL3Nu                         ) ;
     fprintf (outtable, "WZTo3LNu                          & %3.1f  \\\\\n", int_WZTo3LNu                         ) ;
     fprintf (outtable, "WZToLNu2QorQQ2L                   & %3.1f  \\\\\n", int_WZToLNu2QorQQ2L                  ) ;
     //fprintf (outtable, "ZG                                & %3.1f  \\\\\n", int_ZG                               ) ;
//     fprintf (outtable, "ZH\\_HToBB\\_ZToLL                    & %3.1f  \\\\\n", int_ZH_HToBB_ZToLL                   ) ;
     fprintf (outtable, "ZZToLLNuNu                        & %3.1f  \\\\\n", int_ZZToLLNuNu                       ) ;
     fprintf (outtable, "ZZToLLQQ                          & %3.1f  \\\\\n", int_ZZToLLQQ                         ) ;
     fprintf (outtable, "ZZToNuNuQQ                        & %3.1f  \\\\\n", int_ZZToNuNuQQ                       ) ;
     fprintf (outtable, "ZZToLLLL                          & %3.1f  \\\\\n", int_ZZToLLLL                         ) ;
     fprintf (outtable, " \\hline \n");
     fprintf (outtable, " \\Large Data \\\\\n");
     fprintf (outtable, " \\hline \n");
     //fprintf (outtable, "SingleElectron                    & %3.1f  \\\\\n", int_SingleElectron                   ) ;
     //fprintf (outtable, "SingleMuon                        & %3.1f  \\\\\n", int_SingleMuon                       ) ;
     //fprintf (outtable, "DoubleEG                          & %3.1f  \\\\\n", int_DoubleEG                         ) ;
     //fprintf (outtable, "DoubleMuon                        & %3.1f  \\\\\n", int_DoubleMuon                       ) ;
     //fprintf (outtable, "MuonEG                            & %3.1f  \\\\\n", int_MuonEG                           ) ;
     fprintf (outtable, " \\hline \n");
//     fprintf (outtable, "Signel (only relative matters (xc = 1 ) \\\\\n");
//     fprintf (outtable, " \\hline \n");
//     fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS0      & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS0     ) ;
//     fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS0p05   & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS0p05  ) ;
//     fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS1      & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS1     ) ;
//     fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS10     & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS10    ) ;
//     fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS100    & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS100   ) ;
//     fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS1000   & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS1000  ) ;
//     fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS10000  & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS10000 ) ;
     fprintf (outtable, "\\end{tabular}\n\n");
     fprintf (outtable, "\\end{document}\n\n");
    fclose (outtable);



    // merge some histograms
    h_DY = (TH1F*)h_DY50->Clone("h_DY");
//     h_DY->Add(h_DY5to50_HT100To200); 
//     h_DY->Add(h_DY5to50_HT200To400); 
//     h_DY->Add(h_DY5to50_HT400To600); 
//     h_DY->Add(h_DY5to50_HT600ToInf); 
//     h_DY->Add(h_DY5to50_HT70To100 ); 

//    h_GJets = (TH1F*)h_GJets_HT40To100->Clone("h_GJets");
//     h_GJets->Add(h_GJets_HT100To200);
//     h_GJets->Add(h_GJets_HT200To400);
//     h_GJets->Add(h_GJets_HT400To600);
//     h_GJets->Add(h_GJets_HT600ToInf);

    h_ST = (TH1F*)h_ST_s->Clone("h_ST");
    h_ST->Add(h_STbar_t);
    h_ST->Add(h_ST_t);
    h_ST->Add(h_STbar_tW);
    h_ST->Add(h_ST_tW);

//    h_ZH = (TH1F*)h_ZH_HToBB_ZToLL->Clone("h_ZH");
//     h_ZH->Add(h_ggZH_HToBB_ZToLL);

    h_VV = (TH1F*)h_WWToLNuLNu->Clone("h_VV");
     h_VV->Add(h_WWToLNuQQ      ) ;
     h_VV->Add(h_WZToL3Nu       ) ;
     h_VV->Add(h_WZTo3LNu       ) ;
     h_VV->Add(h_WZToLNu2QorQQ2L) ;
     h_VV->Add(h_ZZToLLNuNu     ) ;
     h_VV->Add(h_ZZToLLQQ       ) ;
     h_VV->Add(h_ZZToNuNuQQ     ) ;
     h_VV->Add(h_ZZToLLLL       ) ;


    h_TT = (TH1F*)h_TTtoLL->Clone("h_TT");
     h_TT->Add(h_TTtoLfromTbar );
     h_TT->Add(h_TTtoLfromT    );

     //h_VG = (TH1F*)h_WG->Clone("h_VG");
     //h_VG->Add(h_ZG);

    h_Totbkg= (TH1F*)h_DY50->Clone("h_Totbkg_"+varname);
//     h_Totbkg->Add(h_DY5to50_HT100To200) ; 
//     h_Totbkg->Add(h_DY5to50_HT200To400) ; 
//     h_Totbkg->Add(h_DY5to50_HT400To600) ; 
//     h_Totbkg->Add(h_DY5to50_HT600ToInf) ; 
//     h_Totbkg->Add(h_DY5to50_HT70To100 ) ; 
//     h_Totbkg->Add(h_ggZH_HToBB_ZToLL) ;
//     h_Totbkg->Add(h_GJets_HT40To100 ) ;
//     h_Totbkg->Add(h_GJets_HT100To200) ;
//     h_Totbkg->Add(h_GJets_HT200To400) ;
//     h_Totbkg->Add(h_GJets_HT400To600) ;
//     h_Totbkg->Add(h_GJets_HT600ToInf) ;
     h_Totbkg->Add(h_ST_s            ) ;
     h_Totbkg->Add(h_STbar_t         ) ;
     h_Totbkg->Add(h_ST_t            ) ;
     h_Totbkg->Add(h_STbar_tW        ) ;
     h_Totbkg->Add(h_ST_tW           ) ;
     h_Totbkg->Add(h_TTtoLL          ) ;
     h_Totbkg->Add(h_TTtoLfromTbar   ) ;
     h_Totbkg->Add(h_TTtoLfromT      ) ;
     //h_Totbkg->Add(h_WG              ) ;
     h_Totbkg->Add(h_WJetsToLNu      ) ;
     h_Totbkg->Add(h_WWToLNuLNu      ) ;
     h_Totbkg->Add(h_WWToLNuQQ       ) ;
     h_Totbkg->Add(h_WZToL3Nu        ) ;
     h_Totbkg->Add(h_WZTo3LNu        ) ;
     h_Totbkg->Add(h_WZToLNu2QorQQ2L ) ;
     //h_Totbkg->Add(h_ZG              ) ;
     //h_Totbkg->Add(h_ZH_HToBB_ZToLL  ) ;
     h_Totbkg->Add(h_ZZToLLNuNu      ) ;
     h_Totbkg->Add(h_ZZToLLQQ        ) ;
     h_Totbkg->Add(h_ZZToNuNuQQ      ) ;
     h_Totbkg->Add(h_ZZToLLLL        ) ;

     fout->cd();
     h_Totbkg->Write();


     h_Data = (TH1F*)h_DY50->Clone("h_Data");
     h_Data->Reset();

    // set data set(s) to use
    if( lepton=="ele"){
      //h_Data = (TH1F*)h_SingleElectron->Clone("h_Data");
    }
    else if( lepton=="mu"){
      //h_Data = (TH1F*)h_SingleMuon->Clone("h_Data");
    }
    else{
      //h_Data = (TH1F*)h_SingleElectron->Clone("h_Data");
      //h_Data->Add(h_SingleMuon);
    }

    // count + ratio
    Double_t int_DY     = h_DY     ->Integral(0,-1) ; 
//    Double_t int_GJets  = h_GJets  ->Integral(0,-1) ; 
    Double_t int_ST     = h_ST     ->Integral(0,-1) ; 
//    Double_t int_ZH     = h_ZH     ->Integral(0,-1) ; 
    Double_t int_VV     = h_VV     ->Integral(0,-1) ; 
    Double_t int_TT     = h_TT     ->Integral(0,-1) ; 
    //Double_t int_VG     = h_VG     ->Integral(0,-1) ; 
    Double_t int_Totbkg = h_Totbkg ->Integral(0,-1) ; 
    Double_t int_Data   = h_Data   ->Integral(0,-1);

    Double_t int_bkgOnData = int_Totbkg/int_Data;

    FILE * summarytable;
    summarytable = fopen (logname+"_summary.tex","w");
     fprintf (summarytable, "\\documentclass{standalone}\n\n");
     fprintf (summarytable, "\\begin{document}\n\n");
     fprintf (summarytable, "\\begin{tabular}{rl}\n\n");
     fprintf (summarytable, " \\Huge %s & \\Huge %s   \\\\\n", lepton.Data(), region.Data()); 
     fprintf (summarytable, " \\hline \n");
     fprintf (summarytable, "\\Large  Backgrounds \\\\\n");
     fprintf (summarytable, " \\hline \n");
     fprintf (summarytable, "DY      & %3.1f \\\\\n", int_DY     ) ; 
//     fprintf (summarytable, "GJets   & %3.1f \\\\\n", int_GJets  ) ; 
     fprintf (summarytable, "ST      & %3.1f \\\\\n", int_ST     ) ; 
//     fprintf (summarytable, "ZH      & %3.1f \\\\\n", int_ZH     ) ; 
     fprintf (summarytable, "VV      & %3.1f \\\\\n", int_VV     ) ; 
     fprintf (summarytable, "TT      & %3.1f \\\\\n", int_TT     ) ; 
     //fprintf (summarytable, "VG      & %3.1f \\\\\n", int_VG     ) ; 
     fprintf (summarytable, "WJetsToLNu                        & %3.1f  \\\\\n", int_WJetsToLNu                       ) ;
     fprintf (summarytable, " \\hline \n");
     fprintf (summarytable, "Total Backgrouns     & %3.1f \\\\\n", int_Totbkg ) ; 
     fprintf (summarytable, " \\hline \n");
     fprintf (summarytable, "Data                 & %3.1f  \\\\\n", int_Data   ) ;
     fprintf (summarytable, " \\hline \n");
     fprintf (summarytable, "Backgrounds / Data   & %3.1f  \\\\\n", int_bkgOnData   ) ;
     fprintf (summarytable, "\\end{tabular}\n\n");
     fprintf (summarytable, "\\end{document}\n\n");
    fclose (summarytable);

    // set attributes
    h_DY         -> SetLineColor(kBlack); 
//    h_GJets      -> SetLineColor(kBlack);
    h_ST         -> SetLineColor(kBlack); 
    h_TT         -> SetLineColor(kBlack); 
    h_WJetsToLNu -> SetLineColor(kBlack); 
    h_VV         -> SetLineColor(kBlack); 
    //h_VG         -> SetLineColor(kBlack); 
//    h_ZH         -> SetLineColor(kBlack);

//    h_ggZH_HToSSTobbbb_MS40_ctauS0     -> SetLineColor(632) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS0p05  -> SetLineColor(807) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS1     -> SetLineColor(798) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS10    -> SetLineColor(418) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS100   -> SetLineColor(601) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS1000  -> SetLineColor(599) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS10000 -> SetLineColor(618) ;
//
//    h_ggZH_HToSSTobbbb_MS40_ctauS0     -> SetLineWidth(2) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS0p05  -> SetLineWidth(2) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS1     -> SetLineWidth(2) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS10    -> SetLineWidth(2) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS100   -> SetLineWidth(2) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS1000  -> SetLineWidth(2) ;
//    h_ggZH_HToSSTobbbb_MS40_ctauS10000 -> SetLineWidth(2) ;

    h_Data  -> SetLineColor(kBlack);
    h_Data  -> SetMarkerStyle(8);
    h_Data  -> SetMarkerSize(1);
    h_Data  -> SetLineWidth(3);

    //h_VG->SetFillStyle(1001);
    h_WJetsToLNu->SetFillStyle(1001);
    h_TT->SetFillStyle(1001);
    h_ST->SetFillStyle(1001);
    h_VV->SetFillStyle(1001);
    h_DY->SetFillStyle(1001);

    //h_VG->SetFillColor(kPink+9);
    h_WJetsToLNu->SetFillColor(kViolet-3);
    h_TT->SetFillColor(kGreen+1);
    h_ST->SetFillColor(kOrange+8);
    h_VV->SetFillColor(kMagenta+1);
    h_DY->SetFillColor(kAzure-3);


    // make stack
    THStack *bgstack = new THStack("bgstack","");
//    bgstack->Add(h_ZH         );
//    bgstack->Add(h_GJets      );
//    bgstack->Add(h_VG         );
    bgstack->Add(h_WJetsToLNu ); 
    bgstack->Add(h_VV         ); 
    bgstack->Add(h_ST         ); 
    bgstack->Add(h_TT         ); 
    bgstack->Add(h_DY         ); 

    if(dolog) bgstack->SetMinimum(1e-3);

//    if( h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS0      ->Scale( int_Totbkg / h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1));
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS0p05   ->Scale( int_Totbkg / h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1));  
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS1      ->Scale( int_Totbkg / h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1)); 
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS10     ->Scale( int_Totbkg / h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1)); 
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS100    ->Scale( int_Totbkg / h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1));   
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS1000   ->Scale( int_Totbkg / h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1));  
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS10000  ->Scale( int_Totbkg / h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) ); 
//    }

    // make legend
    TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
    leg->SetBorderSize(0);
    leg->SetFillColor(kWhite);
    if( lepton=="ele"){
      //leg->AddEntry(h_Data      , "Data SingleEle", "lpe"); 
    }
    else if( lepton=="mu"){
      //leg->AddEntry(h_Data      , "Data SingleMu", "lpe"); 
    }
    else{
      //leg->AddEntry(h_Data      , "Data Single Ele+Mu", "lpe");
    }
    leg->AddEntry(h_DY           , "Drell-Yan", "f"); 
    leg->AddEntry(h_TT           , "t#bar{t}+Jets", "f"); 
    leg->AddEntry(h_ST           , "Single Top", "f"); 
    leg->AddEntry(h_VV           , "Diboson", "f"); 
    leg->AddEntry(h_WJetsToLNu   , "W+Jets", "f"); 
//    leg->AddEntry(h_GJets        , "#gamma+Jets", "f"); 
    //    leg->AddEntry(h_VG           , "V#gamma", "f");
//    leg->AddEntry(h_ZH           , "ZH#rightarrowLLbb", "f");

     TLegend *sigleg = new TLegend(0.15,0.6,0.65,0.85);
//    if(drawSignal){
//     sigleg->SetBorderSize(0);
//     sigleg->SetFillColor(kWhite);
//     sigleg->SetHeader("Z(H#rightarrow SS#rightarrow bbbb)","C");
//     sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0     , "M_{S}=40 c#tau_{S}=0    ", "l" ) ;
//     sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0p05  , "M_{S}=40 c#tau_{S}=0p05 ", "l" ) ;
//     sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1     , "M_{S}=40 c#tau_{S}=1    ", "l" ) ;
//     sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10    , "M_{S}=40 c#tau_{S}=10   ", "l" ) ;
//     sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS100   , "M_{S}=40 c#tau_{S}=100  ", "l" ) ;
//     sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1000  , "M_{S}=40 c#tau_{S}=1000 ", "l" ) ;
//     sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10000 , "M_{S}=40 c#tau_{S}=10000", "l" ) ;
//    }

    // set max and draw
     /*
    Double_t ymax = h_Data->GetMaximum();
    if(dolog){
     h_Data->SetMaximum(50000*ymax);
    } else {
     h_Data->SetMaximum(5*ymax);
    }
    h_Data->Draw("E");
     */


     //bgstack->Draw("sames hist PFC ");
     
    bgstack->Draw("hist e");
    bgstack->GetXaxis()->SetTitle(varname);
    //h_DY->Draw("sames hist e");

 //h_Data->Draw("sames E");


//    if(drawSignal){
//     h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Draw("hist sames") ;
//     sigleg->Draw();
//    }
    leg->Draw();

    // add titles
    title->DrawTextNDC(0.23,0.91,"CMS");
    extra->DrawTextNDC(0.33,0.91,"Preliminary");
    lumi->DrawTextNDC(0.9,0.91,"35.9 /fb (13 TeV)");
    //lumi->DrawTextNDC(0.9,0.91,"20 /fb (13 TeV)");
    /*
   h_Data->GetXaxis()->SetTitle(h_Data->GetTitle());
    h_Data->GetYaxis()->SetTitle("Events / bin");
    h_Data->GetYaxis()->SetTitleOffset(1.5);
    h_Data->SetTitle("");
    */

    gPad->Update();
    gPad->RedrawAxis();

    // save canvas
    //canvas->SaveAs(outname+".pdf");
    canvas->SaveAs(outname+".png");
    canvas->SaveAs(outname+".pdf");
    //canvas->SaveAs(outpath+jettype+"_"+varname+extraname+".pdf");
    
   } 
  }
  fout->Close();
  
}
