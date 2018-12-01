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
#include <stdio.h>
#include <cstdlib> /* mkdir */

#include <stdlib.h>     /* getenv */

void print_hist(TH1F* h, TString name, FILE* file){

  fprintf(file, "%s", name.Data());
  for(int i=1; i<=h->GetNbinsX(); i++){
    TString toprint = ", ";
    toprint += h->GetBinContent(i);
    fprintf(file, "%s", toprint.Data());
  }
  fprintf(file,"\n");

  name += " err";
  fprintf(file, "%s", name.Data());
  //Error
  for(int i=1; i<=h->GetNbinsX(); i++){
    TString toprint = ", ";
    toprint += h->GetBinError(i);
    fprintf(file, "%s", toprint.Data());
  }
  fprintf(file,"\n");

}

void plotter_stackedRegion(TString region, Bool_t dolog, Bool_t HIP, Bool_t useEOS, TString description)
{

// // Draw signal as lines
// Bool_t drawSignal = kFALSE; //kTRUE;
// Bool_t drawRatio = kTRUE;

 // Setup running configuration: IO, naming, SFs, ..
 /////////////////////////////////////////////////////

 bool drawData = true;
 bool useAlt = false; 

 TString outpath = TString("../plots/");
 TString aversion = TString(getenv("aversion"));
 TString nversion = TString(getenv("nversion"));
 TString depot = TString(getenv("depot2"));
 TString inpath  = TString("../roots/");
 if(useEOS){
  inpath = "root://cmsxrootd.fnal.gov/"+depot+"/"+nversion+"/analyzed/"; 
}

 inpath = inpath+aversion+"/";
 outpath = outpath+aversion+"/"+region+"/";

 TString extraname = "";
 if(HIP){
  extraname+="_BCDEF";
  outpath = outpath+"BCDEF/";
 }
 if(!HIP){
  outpath = outpath+"GH/";
  extraname+="_GH";
 }

 // lumi scaling by era
 Float_t MCSF = 1.;
 Float_t lumiBCDEF = 19691. ;
 Float_t lumiGH = 16226.5 ;

// if(HIP){ MCSF=lumiBCDEF/10000.; }
// else{ MCSF=lumiGH/10000.; }
 
 //TString extraname = "";
 if(dolog){
  extraname+="_log";
  outpath = outpath+"log/";
 }

 TString mdcommand = (TString)"mkdir -p "+outpath.Data();
 const int dir_err = system(mdcommand);
 TString mdcommandtable = (TString)"mkdir -p "+outpath.Data()+"tables/";
 const int dir_err2 = system(mdcommandtable);

 std::vector<TString> uncbins;
 uncbins.clear();
 uncbins.push_back(""             ); 
 uncbins.push_back("_EGSUp"       ); 
 uncbins.push_back("_EGSDown"     );    
 uncbins.push_back("_MESUp"       );    
 uncbins.push_back("_MESDown"     );    
 uncbins.push_back("_AMaxUp"      );    
 uncbins.push_back("_AMaxDown"    );    
 uncbins.push_back("_IPSigUp"     );    
 uncbins.push_back("_IPSigDown"   );    
 uncbins.push_back("_TAUp"        );    
 uncbins.push_back("_TADown"      );    
 uncbins.push_back("_TagVarsUp"   ); 
 uncbins.push_back("_TagVarsDown" );  

 //if(drawSignal){extraname+="_wsig";}
 // variables to plot
 std::vector<TString> variables;
 variables.clear();

 variables.push_back("nSelectedAODCaloJetTag");
 variables.push_back("AllJets_AODCaloJetMedianLog10IPSig");
 variables.push_back("AllJets_AODCaloJetMedianLog10TrackAngle");
 variables.push_back("AllJets_AODCaloJetAlphaMax");

 //variables.push_back("nVtx");                   
 //variables.push_back("nGoodVtx");               
 //variables.push_back("nTrksPV");                
 //variables.push_back("rho");                    
 //variables.push_back("pfMET");                  
 //variables.push_back("pfMETPhi");               
 //variables.push_back("pfMETsumEt");             
 //variables.push_back("nPho");                   
 //variables.push_back("phoE");                   
 //variables.push_back("phoEt");                  
 //variables.push_back("AOD_MET_pt");                 
 //variables.push_back("AOD_MET_phi");                 
 //variables.push_back("AOD_phoPt");                 
 //variables.push_back("AOD_phoEta");                 
 //variables.push_back("AOD_phoPhi");                 
 //variables.push_back("nEle");                   
 //variables.push_back("AOD_elePt");                  
 //variables.push_back("AOD_eleEta");                 
 //variables.push_back("AOD_elePhi");                 
 //variables.push_back("nMu");                    
 //variables.push_back("AOD_muPt");                   
 //variables.push_back("AOD_muEta");                  
 //variables.push_back("AOD_muPhi");                  
 // variables.push_back("nJet");                   
 
 //variables.push_back("htall"); 
 //variables.push_back("htaodcalojets");
 //variables.push_back("AOD_nSelectedPho");
 //variables.push_back("AOD_nSelectedEle");
 //variables.push_back("AOD_nSelectedMu");
 //variables.push_back("nSelectedAODCaloJet");
 //variables.push_back("LeadingJet_AODCaloJetPt");                      
 //variables.push_back("LeadingJet_jetEn");                      
 //variables.push_back("LeadingJet_AODCaloJetEta");                     
 //variables.push_back("LeadingJet_AODCaloJetPhi");                     
 //variables.push_back("AllJets_AODCaloJetPtVar");
 //variables.push_back("AllJets_AODCaloJetPtVar_Tag0");
 //variables.push_back("AllJets_AODCaloJetdR");
 //variables.push_back("AllJets_AODCaloJetdR_Tag0");
 //variables.push_back("AllJets_AODCaloJetNCleanMatchedTracks");
 //variables.push_back("AllJets_AODCaloJetNCleanMatchedTracks_Tag0");
 //variables.push_back("AllJets_AODCaloJetPt");                      
 //variables.push_back("AllJets_AODCaloJetEn");                      
 //variables.push_back("AllJets_AODCaloJetEta");                     
 //variables.push_back("AllJets_AODCaloJetPhi");                     
 //-----all variables after NMinus will have dolog=true, sorry
 //variables.push_back("NMinus");                   
 //variables.push_back("Onecut");                   
 //variables.push_back("Cutflow");                   
 //variables.push_back("RawNMinus");                   
 //variables.push_back("RawOnecut");                   
 //variables.push_back("RawCutflow");                   

 // canvas and text attributes
 int canx = 1100;
 int cany = 1200;
 float lmarg = 0.12;
 float rmarg = 0.05;
 
 TCanvas* canvas = new TCanvas("canvas","canvas",canx,cany); 

 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);
 gStyle->SetPalette(kBird);

 canvas->Clear();
 canvas->cd();

 TPad *plotpad  = new TPad("plotpad", "plotpad", 0, 0.25, 1, 1);
 plotpad->SetBottomMargin(0.04);
 plotpad->SetLeftMargin(lmarg);
 plotpad->SetRightMargin(rmarg);
 plotpad->SetFrameLineWidth(3);
 plotpad->SetLogy(dolog);
 plotpad->Draw();

 canvas->cd();
 TPad *ratiopad = new TPad("ratiopad", "ratiopad", 0, 0, 1, 0.25);
 ratiopad->SetTopMargin(0.04);
 ratiopad->SetBottomMargin(0.4);
 ratiopad->SetFrameLineWidth(3);
 ratiopad->SetLeftMargin(lmarg);
 ratiopad->SetRightMargin(rmarg);
 ratiopad->SetLogy(0);
 ratiopad->SetGrid();
 ratiopad->Draw();
 canvas->cd();

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.06);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.05);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 //extra->SetTextAlign(13);
 extra->SetTextFont(52);
 
 TText* extra2 = new TText(1,1,"") ;
 extra2->SetTextSize(0.03);
 extra2->SetTextColor(kBlack);
 extra2->SetTextAlign(11);
 //extra2->SetTextAlign(13);
 extra2->SetTextFont(62);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.05);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 // initialize histogram files
// TFile* file_Data_SingleMu_H_3       ; 
// TFile* file_Data_SingleMu_H_2       ; 
// TFile* file_Data_SingleMu_G         ; 
// //TFile* file_Data_SingleMu_F         ; 
// //TFile* file_Data_SingleMu_E         ; 
// //TFile* file_Data_SingleMu_D         ; 
// //TFile* file_Data_SingleMu_C         ; 
// //TFile* file_Data_SingleMu_B_2       ; 
// TFile* file_Data_SingleEle_H_3      ; 
// TFile* file_Data_SingleEle_H_2      ; 
// TFile* file_Data_SingleEle_G        ; 
// //TFile* file_Data_SingleEle_F        ; 
// //TFile* file_Data_SingleEle_E        ; 
// //TFile* file_Data_SingleEle_D        ; 
// //TFile* file_Data_SingleEle_C        ; 
// //TFile* file_Data_SingleEle_B_2      ; 
 TFile* file_Data_MuonEG_H_3         ; 
 TFile* file_Data_MuonEG_H_2         ; 
 TFile* file_Data_MuonEG_G           ; 
 //TFile* file_Data_MuonEG_F           ; 
 //TFile* file_Data_MuonEG_E           ; 
 //TFile* file_Data_MuonEG_D           ; 
 //TFile* file_Data_MuonEG_C           ; 
 //TFile* file_Data_MuonEG_B_2         ; 
 TFile* file_Data_SinglePhoton_H_3   ; 
 TFile* file_Data_SinglePhoton_H_2   ; 
 TFile* file_Data_SinglePhoton_G     ; 
 //TFile* file_Data_SinglePhoton_F     ; 
 //TFile* file_Data_SinglePhoton_E     ; 
 //TFile* file_Data_SinglePhoton_D     ; 
 //TFile* file_Data_SinglePhoton_C     ; 
 //TFile* file_Data_SinglePhoton_B_2   ; 
 TFile* file_Data_DoubleMu_H_3       ; 
 TFile* file_Data_DoubleMu_H_2       ; 
 TFile* file_Data_DoubleMu_G         ; 
 //TFile* file_Data_DoubleMu_F         ; 
 //TFile* file_Data_DoubleMu_E         ; 
 //TFile* file_Data_DoubleMu_D         ; 
 //TFile* file_Data_DoubleMu_C         ; 
 //TFile* file_Data_DoubleMu_B_2       ; 
 TFile* file_Data_DoubleEG_H_3       ; 
 TFile* file_Data_DoubleEG_H_2       ; 
 TFile* file_Data_DoubleEG_G         ; 
 //TFile* file_Data_DoubleEG_F         ; 
 //TFile* file_Data_DoubleEG_E         ; 
 //TFile* file_Data_DoubleEG_D         ; 
 //TFile* file_Data_DoubleEG_C         ; 
 //TFile* file_Data_DoubleEG_B_2       ; 
 TFile* file_DY50                                ;
 TFile* file_DY5to50_HT100To200                  ; 
 TFile* file_DY5to50_HT200To400                  ; 
 TFile* file_DY5to50_HT400To600                  ; 
 TFile* file_DY5to50_HT600ToInf                  ; 
 TFile* file_DY10to50                            ; 
 TFile* file_ggZH_HToBB_ZToLL                    ;
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
 TFile* file_TTJets                              ;
 TFile* file_TTtoLfromTbar                       ;
 TFile* file_TTtoLfromT                          ;
 TFile* file_WG                                  ;
 TFile* file_WJetsToLNu                        ;
 TFile* file_WW                                ;
 TFile* file_WZ                                ;
 TFile* file_WWTo2L2Nu                         ;
 TFile* file_WWToLNuQQ                         ;
 TFile* file_WZTo1L3Nu                         ;
 TFile* file_WZTo3LNu                          ;
 TFile* file_WZToLNu2QorQQ2L                   ;
 TFile* file_ZGTo2LG                           ;
 TFile* file_ZH_HToBB_ZToLL                    ;
 TFile* file_ZZ                                ;
 TFile* file_ZZTo2L2Nu                         ;
 TFile* file_ZZTo2L2Q                          ;
 TFile* file_ZZTo2Q2Nu                         ;
 TFile* file_ZZTo4L                            ;
 TFile* file_QCD_HT100to200                    ;
 TFile* file_QCD_HT200to300                    ;
 TFile* file_QCD_HT300to500                    ;
 TFile* file_QCD_HT500to700                    ;
 TFile* file_QCD_HT700to1000                   ;
 TFile* file_QCD_HT1000to1500                  ;
 TFile* file_QCD_HT1500to2000                  ;
 TFile* file_QCD_HT2000toInf                   ;
 TFile* file_Sig_ZH_MS15ct1000     ;
 TFile* file_Sig_ZH_MS15ct100      ;
 TFile* file_Sig_ZH_MS15ct10       ;
 TFile* file_Sig_ZH_MS15ct1        ;
 TFile* file_Sig_ZH_MS40ct1000     ;
 TFile* file_Sig_ZH_MS40ct100      ;
 TFile* file_Sig_ZH_MS40ct10       ;
 TFile* file_Sig_ZH_MS40ct1        ;
 TFile* file_Sig_ZH_MS55ct1000     ;
 TFile* file_Sig_ZH_MS55ct100      ;
 TFile* file_Sig_ZH_MS55ct10       ;
 TFile* file_Sig_ZH_MS55ct1        ;
 TFile* file_Sig_ggZH_MS15ct1000   ;
 TFile* file_Sig_ggZH_MS15ct100    ;
 TFile* file_Sig_ggZH_MS15ct10     ;
 TFile* file_Sig_ggZH_MS15ct1      ;
 TFile* file_Sig_ggZH_MS40ct1000   ;
 TFile* file_Sig_ggZH_MS40ct100    ;
 TFile* file_Sig_ggZH_MS40ct10     ;
 TFile* file_Sig_ggZH_MS40ct1      ;
 TFile* file_Sig_ggZH_MS55ct1000   ;
 TFile* file_Sig_ggZH_MS55ct100    ;
 TFile* file_Sig_ggZH_MS55ct10     ;
 TFile* file_Sig_ggZH_MS55ct1      ;

 // initialize histos
 TH1F* h_DY50                                ;
 TH1F* h_DY5to50_HT100To200                  ; 
 TH1F* h_DY5to50_HT200To400                  ; 
 TH1F* h_DY5to50_HT400To600                  ; 
 TH1F* h_DY5to50_HT600ToInf                  ; 
 TH1F* h_DY10to50                            ; 
 TH1F* h_ggZH_HToBB_ZToLL                    ;
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
 TH1F* h_TTJets                              ;
 TH1F* h_TTtoLfromTbar                       ;
 TH1F* h_TTtoLfromT                          ;
 TH1F* h_WG                                  ;
 TH1F* h_WJetsToLNu                          ;
 TH1F* h_WW                                  ;
 TH1F* h_WZ                                  ;
 TH1F* h_WWTo2L2Nu                           ;
 TH1F* h_WWToLNuQQ                           ;
 TH1F* h_WZTo1L3Nu                           ;
 TH1F* h_WZTo3LNu                            ;
 TH1F* h_WZToLNu2QorQQ2L                     ;
 TH1F* h_ZG                                  ;
 TH1F* h_ZH_HToBB_ZToLL                      ;
 TH1F* h_ZZ                                  ;
 TH1F* h_ZZTo2L2Nu                           ;
 TH1F* h_ZZTo2L2Q                            ;
 TH1F* h_ZZTo2Q2Nu                           ;
 TH1F* h_ZZTo4L                              ;
 TH1F* h_QCD_HT100to200                      ;
 TH1F* h_QCD_HT200to300                      ;
 TH1F* h_QCD_HT300to500                      ;
 TH1F* h_QCD_HT500to700                      ;
 TH1F* h_QCD_HT700to1000                     ;
 TH1F* h_QCD_HT1000to1500                    ;
 TH1F* h_QCD_HT1500to2000                    ;
 TH1F* h_QCD_HT2000toInf                     ;
 TH1F* h_Sig_ZH_MS15ct1000     ;
 TH1F* h_Sig_ZH_MS15ct100      ;
 TH1F* h_Sig_ZH_MS15ct10       ;
 TH1F* h_Sig_ZH_MS15ct1        ;
 TH1F* h_Sig_ZH_MS40ct1000     ;
 TH1F* h_Sig_ZH_MS40ct100      ;
 TH1F* h_Sig_ZH_MS40ct10       ;
 TH1F* h_Sig_ZH_MS40ct1        ;
 TH1F* h_Sig_ZH_MS55ct1000     ;
 TH1F* h_Sig_ZH_MS55ct100      ;
 TH1F* h_Sig_ZH_MS55ct10       ;
 TH1F* h_Sig_ZH_MS55ct1        ;
 TH1F* h_Sig_ggZH_MS15ct1000   ;
 TH1F* h_Sig_ggZH_MS15ct100    ;
 TH1F* h_Sig_ggZH_MS15ct10     ;
 TH1F* h_Sig_ggZH_MS15ct1      ;
 TH1F* h_Sig_ggZH_MS40ct1000   ;
 TH1F* h_Sig_ggZH_MS40ct100    ;
 TH1F* h_Sig_ggZH_MS40ct10     ;
 TH1F* h_Sig_ggZH_MS40ct1      ;
 TH1F* h_Sig_ggZH_MS55ct1000   ;
 TH1F* h_Sig_ggZH_MS55ct100    ;
 TH1F* h_Sig_ggZH_MS55ct10     ;
 TH1F* h_Sig_ggZH_MS55ct1      ;
 //TH1F* h_Data_SingleMu_H_3     ;
 //TH1F* h_Data_SingleMu_H_2     ;
 //TH1F* h_Data_SingleMu_G       ;
 ////TH1F* h_Data_SingleMu_F       ;
 ////TH1F* h_Data_SingleMu_E       ;
 ////TH1F* h_Data_SingleMu_D       ;
 ////TH1F* h_Data_SingleMu_C       ;
 ////TH1F* h_Data_SingleMu_B_2     ;
 //TH1F* h_Data_SingleEle_H_3    ;
 //TH1F* h_Data_SingleEle_H_2    ;
 //TH1F* h_Data_SingleEle_G      ;
 ////TH1F* h_Data_SingleEle_F      ;
 ////TH1F* h_Data_SingleEle_E      ;
 ////TH1F* h_Data_SingleEle_D      ;
 ////TH1F* h_Data_SingleEle_C      ;
 ////TH1F* h_Data_SingleEle_B_2    ;
 TH1F* h_Data_MuonEG_H_3       ;
 TH1F* h_Data_MuonEG_H_2       ;
 TH1F* h_Data_MuonEG_G         ;
 //TH1F* h_Data_MuonEG_F         ;
 //TH1F* h_Data_MuonEG_E         ;
 //TH1F* h_Data_MuonEG_D         ;
 //TH1F* h_Data_MuonEG_C         ;
 //TH1F* h_Data_MuonEG_B_2       ;
 TH1F* h_Data_SinglePhoton_H_3 ;
 TH1F* h_Data_SinglePhoton_H_2 ;
 TH1F* h_Data_SinglePhoton_G   ;
 //TH1F* h_Data_SinglePhoton_F   ;
 //TH1F* h_Data_SinglePhoton_E   ;
 //TH1F* h_Data_SinglePhoton_D   ;
 //TH1F* h_Data_SinglePhoton_C   ;
 //TH1F* h_Data_SinglePhoton_B_2 ;
 TH1F* h_Data_DoubleMu_H_3     ;
 TH1F* h_Data_DoubleMu_H_2     ;
 TH1F* h_Data_DoubleMu_G       ;
 //TH1F* h_Data_DoubleMu_F       ;
 //TH1F* h_Data_DoubleMu_E       ;
 //TH1F* h_Data_DoubleMu_D       ;
 //TH1F* h_Data_DoubleMu_C       ;
 //TH1F* h_Data_DoubleMu_B_2     ;
 TH1F* h_Data_DoubleEG_H_3     ;
 TH1F* h_Data_DoubleEG_H_2     ;
 TH1F* h_Data_DoubleEG_G       ;
 //TH1F* h_Data_DoubleEG_F       ;
 //TH1F* h_Data_DoubleEG_E       ;
 //TH1F* h_Data_DoubleEG_D       ;
 //TH1F* h_Data_DoubleEG_C       ;
 //TH1F* h_Data_DoubleEG_B_2     ;
 TH1F* h_ratio ;
 TH1F* h_ratiostaterr ;

 // (combined) histos to be made
 TH1F* h_DY     ;
 TH1F* h_GJets  ;
 TH1F* h_ST     ;
 TH1F* h_VV     ;
 TH1F* h_VG     ;
 TH1F* h_ZH     ;
 TH1F* h_TT     ;
 TH1F* h_QCD    ;
 TH1F* h_bkgtotal ;
 TH1F* h_light ;
 TH1F* h_heavy ;
 TH1F* h_other ;
 TH1F* h_light_alt ;
 TH1F* h_heavy_alt ;
 TH1F* h_other_alt ;

 TH1F* h_altDY ;
 TH1F* h_altVV ;
 TH1F* h_altTT ;

 TH1F* h_Sig_MS15ct1000 ;
 TH1F* h_Sig_MS15ct100  ;
 TH1F* h_Sig_MS15ct10   ;
 TH1F* h_Sig_MS15ct1    ;
 TH1F* h_Sig_MS40ct1000 ;
 TH1F* h_Sig_MS40ct100  ;
 TH1F* h_Sig_MS40ct10   ;
 TH1F* h_Sig_MS40ct1    ;
 TH1F* h_Sig_MS55ct1000 ;
 TH1F* h_Sig_MS55ct100  ;
 TH1F* h_Sig_MS55ct10   ;
 TH1F* h_Sig_MS55ct1    ;

 TH1F* h_Data   ;
 // load histogram files
 file_DY5to50_HT100To200      = TFile::Open( inpath + "DYJetsToLL_M-5to50_HT-100to200_"+region+"_histograms.root"  ) ; 
 file_DY5to50_HT200To400      = TFile::Open( inpath + "DYJetsToLL_M-5to50_HT-200to400_"+region+"_histograms.root"  ) ; 
 file_DY5to50_HT400To600      = TFile::Open( inpath + "DYJetsToLL_M-5to50_HT-400to600_"+region+"_histograms.root"  ) ; 
 file_DY5to50_HT600ToInf      = TFile::Open( inpath + "DYJetsToLL_M-5to50_HT-600toInf_"+region+"_histograms.root"  ) ; 
 file_DY10to50                = TFile::Open( inpath + "DYJetsToLL_M-10to50_"+region+"_histograms.root"             ) ; 
 file_DY50                    = TFile::Open( inpath + "DYJetsToLL_M-50_"+region+"_histograms.root"                 ) ;

 file_GJets_HT40To100         = TFile::Open( inpath + "GJets_HT-40To100_"+region+"_histograms.root"    ) ;
 file_GJets_HT100To200        = TFile::Open( inpath + "GJets_HT-100To200_"+region+"_histograms.root"   ) ;
 file_GJets_HT200To400        = TFile::Open( inpath + "GJets_HT-200To400_"+region+"_histograms.root"   ) ;
 file_GJets_HT400To600        = TFile::Open( inpath + "GJets_HT-400To600_"+region+"_histograms.root"   ) ;
 file_GJets_HT600ToInf        = TFile::Open( inpath + "GJets_HT-600ToInf_"+region+"_histograms.root"   ) ;
 file_ST_s                    = TFile::Open( inpath + "ST_s-channel_4f_leptonDecays_"+region+"_histograms.root"               ) ;
 file_STbar_t                 = TFile::Open( inpath + "ST_t-channel_antitop_4f_inclusiveDecays_"+region+"_histograms.root"    ) ;
 file_ST_t                    = TFile::Open( inpath + "ST_t-channel_top_4f_inclusiveDecays_"+region+"_histograms.root"        ) ;
 file_STbar_tW                = TFile::Open( inpath + "ST_tW_antitop_5f_NoFullyHadronicDecays_"+region+"_histograms.root"     ) ;
 file_ST_tW                   = TFile::Open( inpath + "ST_tW_top_5f_NoFullyHadronicDecays_"+region+"_histograms.root"         ) ;
 file_TTJets                  = TFile::Open( inpath + "TTJets_"+region+"_histograms.root"           ) ;
 file_TTtoLL                  = TFile::Open( inpath + "TTtoLL_"+region+"_histograms.root"           ) ;
 file_TTtoLfromTbar           = TFile::Open( inpath + "TTtoLfromTbar_"+region+"_histograms.root"    ) ;
 file_TTtoLfromT              = TFile::Open( inpath + "TTtoLfromT_"+region+"_histograms.root"       ) ;
 file_WJetsToLNu              = TFile::Open( inpath + "WJetsToLNu_"+region+"_histograms.root"       ) ;
 file_WG                      = TFile::Open( inpath + "WGToLNuG_"+region+"_histograms.root"         ) ;
 file_ZGTo2LG                 = TFile::Open( inpath + "ZGTo2LG_"+region+"_histograms.root"          ) ;
 file_WW                      = TFile::Open( inpath + "WW_"+region+"_histograms.root"               ) ;
 file_WZ                      = TFile::Open( inpath + "WZ_"+region+"_histograms.root"               ) ;
 file_ZZ                      = TFile::Open( inpath + "ZZ_"+region+"_histograms.root"               ) ;
 file_WWTo2L2Nu               = TFile::Open( inpath + "WWTo2L2Nu_"+region+"_histograms.root"        ) ;
 file_WWToLNuQQ               = TFile::Open( inpath + "WWToLNuQQ_"+region+"_histograms.root"        ) ;
 file_WZTo1L3Nu               = TFile::Open( inpath + "WZTo1L3Nu_"+region+"_histograms.root"        ) ;
 file_WZTo3LNu                = TFile::Open( inpath + "WZTo3LNu_"+region+"_histograms.root"         ) ;
 file_WZToLNu2QorQQ2L         = TFile::Open( inpath + "WZToLNu2QorQQ2L_"+region+"_histograms.root"  ) ;
 file_ZH_HToBB_ZToLL          = TFile::Open( inpath + "ZH_HToBB_ZToLL_"+region+"_histograms.root"   ) ;
 file_ggZH_HToBB_ZToLL        = TFile::Open( inpath + "ggZH_HToBB_ZToLL_"+region+"_histograms.root" ) ;
 file_ZZTo2L2Nu               = TFile::Open( inpath + "ZZTo2L2Nu_"+region+"_histograms.root"        ) ;
 file_ZZTo2L2Q                = TFile::Open( inpath + "ZZTo2L2Q_"+region+"_histograms.root"         ) ;
 file_ZZTo2Q2Nu               = TFile::Open( inpath + "ZZTo2Q2Nu_"+region+"_histograms.root"        ) ;
 file_ZZTo4L                  = TFile::Open( inpath + "ZZTo4L_"+region+"_histograms.root"           ) ;
  
 file_QCD_HT100to200          = TFile::Open( inpath + "QCD_HT100to200_"+region+"_histograms.root"   ) ;
 file_QCD_HT200to300          = TFile::Open( inpath + "QCD_HT200to300_"+region+"_histograms.root"   ) ;
 file_QCD_HT300to500          = TFile::Open( inpath + "QCD_HT300to500_"+region+"_histograms.root"   ) ;
 file_QCD_HT500to700          = TFile::Open( inpath + "QCD_HT500to700_"+region+"_histograms.root"   ) ;
 file_QCD_HT700to1000         = TFile::Open( inpath + "QCD_HT700to1000_"+region+"_histograms.root"  ) ;
 file_QCD_HT1000to1500        = TFile::Open( inpath + "QCD_HT1000to1500_"+region+"_histograms.root" ) ;
 file_QCD_HT1500to2000        = TFile::Open( inpath + "QCD_HT1500to2000_"+region+"_histograms.root" ) ;
 file_QCD_HT2000toInf         = TFile::Open( inpath + "QCD_HT2000toInf_"+region+"_histograms.root"  ) ;

 file_Sig_ZH_MS15ct1000  = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS15ct100   = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS15ct10    = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS15ct1     = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS40ct1000  = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS40ct100   = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS40ct10    = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS40ct1     = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS55ct1000  = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS55ct100   = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS55ct10    = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10_"+region+"_histograms.root"   ) ; 
 file_Sig_ZH_MS55ct1     = TFile::Open( inpath + "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1_"+region+"_histograms.root"   ) ; 

 file_Sig_ggZH_MS15ct1000  = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS15ct100   = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS15ct10    = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS15ct1     = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS40ct1000  = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS40ct100   = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS40ct10    = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS40ct1     = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS55ct1000  = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS55ct100   = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS55ct10    = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10_"+region+"_histograms.root"   ) ; 
 file_Sig_ggZH_MS55ct1     = TFile::Open( inpath + "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1_"+region+"_histograms.root"   ) ; 

// file_Data_SingleMu_H_3             =  TFile::Open( inpath + "Data_SingleMu_H_3_"+region+"_histograms.root"     ) ; 
// file_Data_SingleMu_H_2             =  TFile::Open( inpath + "Data_SingleMu_H_2_"+region+"_histograms.root"     ) ; 
// file_Data_SingleMu_G               =  TFile::Open( inpath + "Data_SingleMu_G_"+region+"_histograms.root"       ) ; 
//// file_Data_SingleMu_F               =  TFile::Open( inpath + "Data_SingleMu_F_"+region+"_histograms.root"       ) ; 
//// file_Data_SingleMu_E               =  TFile::Open( inpath + "Data_SingleMu_E_"+region+"_histograms.root"       ) ; 
//// file_Data_SingleMu_D               =  TFile::Open( inpath + "Data_SingleMu_D_"+region+"_histograms.root"       ) ; 
//// file_Data_SingleMu_C               =  TFile::Open( inpath + "Data_SingleMu_C_"+region+"_histograms.root"       ) ; 
//// file_Data_SingleMu_B_2             =  TFile::Open( inpath + "Data_SingleMu_B_2_"+region+"_histograms.root"     ) ; 
// file_Data_SingleEle_H_3            =  TFile::Open( inpath + "Data_SingleEle_H_3_"+region+"_histograms.root"    ) ; 
// file_Data_SingleEle_H_2            =  TFile::Open( inpath + "Data_SingleEle_H_2_"+region+"_histograms.root"    ) ; 
// file_Data_SingleEle_G            =  TFile::Open( inpath + "Data_SingleEle_G_"+region+"_histograms.root"    ) ; 
//// file_Data_SingleEle_F              =  TFile::Open( inpath + "Data_SingleEle_F_"+region+"_histograms.root"      ) ; 
//// file_Data_SingleEle_E              =  TFile::Open( inpath + "Data_SingleEle_E_"+region+"_histograms.root"      ) ; 
//// file_Data_SingleEle_D              =  TFile::Open( inpath + "Data_SingleEle_D_"+region+"_histograms.root"      ) ; 
//// file_Data_SingleEle_C              =  TFile::Open( inpath + "Data_SingleEle_C_"+region+"_histograms.root"      ) ; 
//// file_Data_SingleEle_B_2            =  TFile::Open( inpath + "Data_SingleEle_B_2_"+region+"_histograms.root"    ) ; 
 file_Data_SinglePhoton_H_3         =  TFile::Open( inpath + "Data_SinglePhoton_H_3_"+region+"_histograms.root" ) ; 
 file_Data_SinglePhoton_H_2         =  TFile::Open( inpath + "Data_SinglePhoton_H_2_"+region+"_histograms.root" ) ; 
 file_Data_SinglePhoton_G           =  TFile::Open( inpath + "Data_SinglePhoton_G_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_F           =  TFile::Open( inpath + "Data_SinglePhoton_F_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_E           =  TFile::Open( inpath + "Data_SinglePhoton_E_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_D           =  TFile::Open( inpath + "Data_SinglePhoton_D_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_C           =  TFile::Open( inpath + "Data_SinglePhoton_C_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_B_2         =  TFile::Open( inpath + "Data_SinglePhoton_B_2_"+region+"_histograms.root" ) ; 
 file_Data_DoubleMu_H_3             =  TFile::Open( inpath + "Data_DoubleMu_H_3_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleMu_H_2             =  TFile::Open( inpath + "Data_DoubleMu_H_2_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleMu_G               =  TFile::Open( inpath + "Data_DoubleMu_G_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_F               =  TFile::Open( inpath + "Data_DoubleMu_F_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_E               =  TFile::Open( inpath + "Data_DoubleMu_E_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_D               =  TFile::Open( inpath + "Data_DoubleMu_D_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_C               =  TFile::Open( inpath + "Data_DoubleMu_C_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_B_2             =  TFile::Open( inpath + "Data_DoubleMu_B_2_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleEG_H_3             =  TFile::Open( inpath + "Data_DoubleEG_H_3_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleEG_H_2             =  TFile::Open( inpath + "Data_DoubleEG_H_2_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleEG_G               =  TFile::Open( inpath + "Data_DoubleEG_G_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_F               =  TFile::Open( inpath + "Data_DoubleEG_F_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_E               =  TFile::Open( inpath + "Data_DoubleEG_E_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_D               =  TFile::Open( inpath + "Data_DoubleEG_D_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_C               =  TFile::Open( inpath + "Data_DoubleEG_C_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_B_2             =  TFile::Open( inpath + "Data_DoubleEG_B_2_"+region+"_histograms.root"     ) ; 
 file_Data_MuonEG_H_3             =  TFile::Open( inpath + "Data_MuonEG_H_3_"+region+"_histograms.root"     ) ; 
 file_Data_MuonEG_H_2             =  TFile::Open( inpath + "Data_MuonEG_H_2_"+region+"_histograms.root"     ) ; 
 file_Data_MuonEG_G               =  TFile::Open( inpath + "Data_MuonEG_G_"+region+"_histograms.root"       ) ; 
// file_Data_MuonEG_F               =  TFile::Open( inpath + "Data_MuonEG_F_"+region+"_histograms.root"       ) ; 
// file_Data_MuonEG_E               =  TFile::Open( inpath + "Data_MuonEG_E_"+region+"_histograms.root"       ) ; 
// file_Data_MuonEG_D               =  TFile::Open( inpath + "Data_MuonEG_D_"+region+"_histograms.root"       ) ; 
// file_Data_MuonEG_C               =  TFile::Open( inpath + "Data_MuonEG_C_"+region+"_histograms.root"       ) ; 
// file_Data_MuonEG_B_2             =  TFile::Open( inpath + "Data_MuonEG_B_2_"+region+"_histograms.root"     ) ; 

 // Start looping over variables, systematic uncertainty bins, make plots / tables / root files
  for(unsigned int j=0; j<variables.size(); ++j){
   TString variable = variables[j];

   for(unsigned int j=0; j<uncbins.size(); ++j){
    TString uncbin = uncbins[j];

    //Blind
    drawData=true;
    if(region.Contains("ZH") && 
       (variable=="nSelectedAODCaloJetTag" || 
        variable.Contains("Log10IPSig") || 
        variable.Contains("Log10TrackAngle") || 
        variable.Contains("AlphaMax")) ) {
      drawData=false;
    }
    if(variable.Contains("Raw")){
     drawData=false;
    }
    if( variable.Contains("NMinus")   ||
        variable.Contains("Onecut")   ||               
        variable.Contains("Cutflow") ) {
     dolog=true;
    }

    Bool_t domaketable = kFALSE;
    if(j==0){
     domaketable = kTRUE;
    }
//    for(unsigned int k=0; k<leptons.size(); ++k){
//     TString lepton = leptons[k];

//     TString varname = lepton+"_"+region+"_"+variable;
     TString varname = region+"_"+variable;

     printf("plotting  h_%s \n",varname.Data());

     TString outname = outpath+varname+extraname+uncbin; 
     TString fulllogname = outpath+"tables/full_"+varname+extraname+uncbin; 
     TString smalllogname = outpath+"tables/small_"+varname+extraname+uncbin; 
     TString tinylogname = outpath+"tables/tiny_"+varname+extraname+uncbin; 
     //cout << "logname: " << logname << endl;

     // get histograms from files
     //h_DY5to50_HT70To100               = (TH1F*)file_DY5to50_HT70To100                ->Get("h_"+varname)->Clone( "h_DY5to50_HT70To100"           +uncbin     ) ; 
     h_DY5to50_HT100To200              = (TH1F*)file_DY5to50_HT100To200               ->Get("h_"+varname+uncbin)->Clone( "DY5to50_HT100To200"              +uncbin ) ; 
     h_DY5to50_HT200To400              = (TH1F*)file_DY5to50_HT200To400               ->Get("h_"+varname+uncbin)->Clone( "DY5to50_HT200To400"              +uncbin ) ; 
     h_DY5to50_HT400To600              = (TH1F*)file_DY5to50_HT400To600               ->Get("h_"+varname+uncbin)->Clone( "DY5to50_HT400To600"              +uncbin ) ; 
     h_DY5to50_HT600ToInf              = (TH1F*)file_DY5to50_HT600ToInf               ->Get("h_"+varname+uncbin)->Clone( "DY5to50_HT600ToInf"              +uncbin ) ; 
     h_DY10to50                        = (TH1F*)file_DY10to50                         ->Get("h_"+varname+uncbin)->Clone( "DY10to50"                        +uncbin ) ;
     h_DY50                            = (TH1F*)file_DY50                             ->Get("h_"+varname+uncbin)->Clone( "DY50"                            +uncbin ) ;

     h_ggZH_HToBB_ZToLL                = (TH1F*)file_ggZH_HToBB_ZToLL                 ->Get("h_"+varname+uncbin)->Clone( "ggZH_HToBB_ZToLL"                +uncbin ) ;
     h_ZH_HToBB_ZToLL                  = (TH1F*)file_ZH_HToBB_ZToLL                   ->Get("h_"+varname+uncbin)->Clone( "ZH_HToBB_ZToLL"                  +uncbin ) ;

     h_GJets_HT40To100                 = (TH1F*)file_GJets_HT40To100                  ->Get("h_"+varname+uncbin)->Clone( "GJets_HT40To100"                 +uncbin ) ;
     h_GJets_HT100To200                = (TH1F*)file_GJets_HT100To200                 ->Get("h_"+varname+uncbin)->Clone( "GJets_HT100To200"                +uncbin ) ;
     h_GJets_HT200To400                = (TH1F*)file_GJets_HT200To400                 ->Get("h_"+varname+uncbin)->Clone( "GJets_HT200To400"                +uncbin ) ;
     h_GJets_HT400To600                = (TH1F*)file_GJets_HT400To600                 ->Get("h_"+varname+uncbin)->Clone( "GJets_HT400To600"                +uncbin ) ;
     h_GJets_HT600ToInf                = (TH1F*)file_GJets_HT600ToInf                 ->Get("h_"+varname+uncbin)->Clone( "GJets_HT600ToInf"                +uncbin ) ;

     h_ST_s                            = (TH1F*)file_ST_s                             ->Get("h_"+varname+uncbin)->Clone( "ST_s"                            +uncbin ) ;
     h_STbar_t                         = (TH1F*)file_STbar_t                          ->Get("h_"+varname+uncbin)->Clone( "STbar_t"                         +uncbin ) ;
     h_ST_t                            = (TH1F*)file_ST_t                             ->Get("h_"+varname+uncbin)->Clone( "ST_t"                            +uncbin ) ;
     h_STbar_tW                        = (TH1F*)file_STbar_tW                         ->Get("h_"+varname+uncbin)->Clone( "STbar_tW"                        +uncbin ) ;
     h_ST_tW                           = (TH1F*)file_ST_tW                            ->Get("h_"+varname+uncbin)->Clone( "ST_tW"                           +uncbin ) ;

     h_TTJets                          = (TH1F*)file_TTJets                           ->Get("h_"+varname+uncbin)->Clone( "TTJets"                          +uncbin ) ;
     h_TTtoLL                          = (TH1F*)file_TTtoLL                           ->Get("h_"+varname+uncbin)->Clone( "TTtoLL"                          +uncbin ) ;
     h_TTtoLfromTbar                   = (TH1F*)file_TTtoLfromTbar                    ->Get("h_"+varname+uncbin)->Clone( "TTtoLfromTbar"                   +uncbin ) ;
     h_TTtoLfromT                      = (TH1F*)file_TTtoLfromT                       ->Get("h_"+varname+uncbin)->Clone( "TTtoLfromT"                      +uncbin ) ;
     h_WJetsToLNu                      = (TH1F*)file_WJetsToLNu                       ->Get("h_"+varname+uncbin)->Clone( "WJetsToLNu"                      +uncbin ) ;
     h_WG                              = (TH1F*)file_WG                               ->Get("h_"+varname+uncbin)->Clone( "WG"                              +uncbin ) ;
     h_ZG                              = (TH1F*)file_ZGTo2LG                          ->Get("h_"+varname+uncbin)->Clone( "ZG"                              +uncbin ) ;
     h_WW                              = (TH1F*)file_WW                               ->Get("h_"+varname+uncbin)->Clone( "WW"                              +uncbin ) ;
     h_WZ                              = (TH1F*)file_WZ                               ->Get("h_"+varname+uncbin)->Clone( "WZ"                              +uncbin ) ;
     h_ZZ                              = (TH1F*)file_ZZ                               ->Get("h_"+varname+uncbin)->Clone( "ZZ"                              +uncbin ) ;
     h_WWTo2L2Nu                       = (TH1F*)file_WWTo2L2Nu                        ->Get("h_"+varname+uncbin)->Clone( "WWTo2L2Nu"                       +uncbin ) ;
     h_WWToLNuQQ                       = (TH1F*)file_WWToLNuQQ                        ->Get("h_"+varname+uncbin)->Clone( "WWToLNuQQ"                       +uncbin ) ;
     h_WZTo1L3Nu                       = (TH1F*)file_WZTo1L3Nu                        ->Get("h_"+varname+uncbin)->Clone( "WZTo1L3Nu"                       +uncbin ) ;
     h_WZTo3LNu                        = (TH1F*)file_WZTo3LNu                         ->Get("h_"+varname+uncbin)->Clone( "WZTo3LNu"                        +uncbin ) ;
     h_WZToLNu2QorQQ2L                 = (TH1F*)file_WZToLNu2QorQQ2L                  ->Get("h_"+varname+uncbin)->Clone( "WZToLNu2QorQQ2L"                 +uncbin ) ;
     h_ZZTo2L2Nu                       = (TH1F*)file_ZZTo2L2Nu                        ->Get("h_"+varname+uncbin)->Clone( "ZZTo2L2Nu"                       +uncbin ) ;
     h_ZZTo2L2Q                        = (TH1F*)file_ZZTo2L2Q                         ->Get("h_"+varname+uncbin)->Clone( "ZZTo2L2Q"                        +uncbin ) ;
     h_ZZTo2Q2Nu                       = (TH1F*)file_ZZTo2Q2Nu                        ->Get("h_"+varname+uncbin)->Clone( "ZZTo2Q2Nu"                       +uncbin ) ;
     h_ZZTo4L                          = (TH1F*)file_ZZTo4L                           ->Get("h_"+varname+uncbin)->Clone( "ZZTo4L"                          +uncbin ) ;
     h_QCD_HT100to200                  = (TH1F*)file_QCD_HT100to200                   ->Get("h_"+varname+uncbin)->Clone( "QCD_HT100to200"                +uncbin   ) ;
     h_QCD_HT200to300                  = (TH1F*)file_QCD_HT200to300                   ->Get("h_"+varname+uncbin)->Clone( "QCD_HT200to300"                +uncbin   ) ;
     h_QCD_HT300to500                  = (TH1F*)file_QCD_HT300to500                   ->Get("h_"+varname+uncbin)->Clone( "QCD_HT300to500"                +uncbin   ) ;
     h_QCD_HT500to700                  = (TH1F*)file_QCD_HT500to700                   ->Get("h_"+varname+uncbin)->Clone( "QCD_HT500to700"                +uncbin   ) ;
     h_QCD_HT700to1000                 = (TH1F*)file_QCD_HT700to1000                  ->Get("h_"+varname+uncbin)->Clone( "QCD_HT700to1000"               +uncbin   ) ;
     h_QCD_HT1000to1500                = (TH1F*)file_QCD_HT1000to1500                 ->Get("h_"+varname+uncbin)->Clone( "QCD_HT1000to1500"              +uncbin   ) ;
     h_QCD_HT1500to2000                = (TH1F*)file_QCD_HT1500to2000                 ->Get("h_"+varname+uncbin)->Clone( "QCD_HT1500to2000"              +uncbin   ) ;
     h_QCD_HT2000toInf                 = (TH1F*)file_QCD_HT2000toInf                  ->Get("h_"+varname+uncbin)->Clone( "QCD_HT2000toInf"               +uncbin   ) ;

     h_Sig_ZH_MS15ct1000   = (TH1F*)file_Sig_ZH_MS15ct1000   ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS15ct1000"+uncbin ) ;
     h_Sig_ZH_MS15ct100    = (TH1F*)file_Sig_ZH_MS15ct100    ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS15ct100" +uncbin ) ;
     h_Sig_ZH_MS15ct10     = (TH1F*)file_Sig_ZH_MS15ct10     ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS15ct10"  +uncbin ) ;
     h_Sig_ZH_MS15ct1      = (TH1F*)file_Sig_ZH_MS15ct1      ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS15ct1"   +uncbin ) ;
     h_Sig_ZH_MS40ct1000   = (TH1F*)file_Sig_ZH_MS40ct1000   ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS40ct1000"+uncbin ) ;
     h_Sig_ZH_MS40ct100    = (TH1F*)file_Sig_ZH_MS40ct100    ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS40ct100" +uncbin ) ;
     h_Sig_ZH_MS40ct10     = (TH1F*)file_Sig_ZH_MS40ct10     ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS40ct10"  +uncbin ) ;
     h_Sig_ZH_MS40ct1      = (TH1F*)file_Sig_ZH_MS40ct1      ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS40ct1"   +uncbin ) ;
     h_Sig_ZH_MS55ct1000   = (TH1F*)file_Sig_ZH_MS55ct1000   ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS55ct1000"+uncbin ) ;
     h_Sig_ZH_MS55ct100    = (TH1F*)file_Sig_ZH_MS55ct100    ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS55ct100" +uncbin ) ;
     h_Sig_ZH_MS55ct10     = (TH1F*)file_Sig_ZH_MS55ct10     ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS55ct10"  +uncbin ) ;
     h_Sig_ZH_MS55ct1      = (TH1F*)file_Sig_ZH_MS55ct1      ->Get("h_"+varname+uncbin )->Clone( "Sig_ZH_MS55ct1"   +uncbin ) ;
                                                                                                                      
     h_Sig_ggZH_MS15ct1000 = (TH1F*)file_Sig_ggZH_MS15ct1000 ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS15ct1000"+uncbin ) ;
     h_Sig_ggZH_MS15ct100  = (TH1F*)file_Sig_ggZH_MS15ct100  ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS15ct100" +uncbin ) ;
     h_Sig_ggZH_MS15ct10   = (TH1F*)file_Sig_ggZH_MS15ct10   ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS15ct10"  +uncbin ) ;
     h_Sig_ggZH_MS15ct1    = (TH1F*)file_Sig_ggZH_MS15ct1    ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS15ct1"   +uncbin ) ;
     h_Sig_ggZH_MS40ct1000 = (TH1F*)file_Sig_ggZH_MS40ct1000 ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS40ct1000"+uncbin ) ;
     h_Sig_ggZH_MS40ct100  = (TH1F*)file_Sig_ggZH_MS40ct100  ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS40ct100" +uncbin ) ;
     h_Sig_ggZH_MS40ct10   = (TH1F*)file_Sig_ggZH_MS40ct10   ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS40ct10"  +uncbin ) ;
     h_Sig_ggZH_MS40ct1    = (TH1F*)file_Sig_ggZH_MS40ct1    ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS40ct1"   +uncbin ) ;
     h_Sig_ggZH_MS55ct1000 = (TH1F*)file_Sig_ggZH_MS55ct1000 ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS55ct1000"+uncbin ) ;
     h_Sig_ggZH_MS55ct100  = (TH1F*)file_Sig_ggZH_MS55ct100  ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS55ct100" +uncbin ) ;
     h_Sig_ggZH_MS55ct10   = (TH1F*)file_Sig_ggZH_MS55ct10   ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS55ct10"  +uncbin ) ;
     h_Sig_ggZH_MS55ct1    = (TH1F*)file_Sig_ggZH_MS55ct1    ->Get("h_"+varname+uncbin )->Clone( "Sig_ggZH_MS55ct1"   +uncbin ) ;

     /*
     h_Data_SingleMu_H_3     = (TH1F*) file_Data_SingleMu_H_3     -> Get("h_"+varname)->Clone( "Data_SingleMu_H_3"      ) ; 
     h_Data_SingleMu_H_2     = (TH1F*) file_Data_SingleMu_H_2     -> Get("h_"+varname)->Clone( "Data_SingleMu_H_2"      ) ; 
     h_Data_SingleMu_G       = (TH1F*) file_Data_SingleMu_G       -> Get("h_"+varname)->Clone( "Data_SingleMu_G"        ) ; 
     //h_Data_SingleMu_F       = (TH1F*) file_Data_SingleMu_F       -> Get("h_"+varname)->Clone( "Data_SingleMu_F"        ) ; 
     //h_Data_SingleMu_E       = (TH1F*) file_Data_SingleMu_E       -> Get("h_"+varname)->Clone( "Data_SingleMu_E"        ) ; 
     //h_Data_SingleMu_D       = (TH1F*) file_Data_SingleMu_D       -> Get("h_"+varname)->Clone( "Data_SingleMu_D"        ) ; 
     //h_Data_SingleMu_C       = (TH1F*) file_Data_SingleMu_C       -> Get("h_"+varname)->Clone( "Data_SingleMu_C"        ) ; 
     //h_Data_SingleMu_B_2     = (TH1F*) file_Data_SingleMu_B_2     -> Get("h_"+varname)->Clone( "Data_SingleMu_B_2"      ) ; 
     h_Data_SingleEle_H_3    = (TH1F*) file_Data_SingleEle_H_3    -> Get("h_"+varname)->Clone( "Data_SingleEle_H_3"     ) ; 
     h_Data_SingleEle_H_2    = (TH1F*) file_Data_SingleEle_H_2    -> Get("h_"+varname)->Clone( "Data_SingleEle_H_2"     ) ; 
     h_Data_SingleEle_G      = (TH1F*) file_Data_SingleEle_G    -> Get("h_"+varname)->Clone( "Data_SingleEle_G"     ) ; 
     //h_Data_SingleEle_F      = (TH1F*) file_Data_SingleEle_F      -> Get("h_"+varname)->Clone( "Data_SingleEle_F"       ) ; 
     //h_Data_SingleEle_E      = (TH1F*) file_Data_SingleEle_E      -> Get("h_"+varname)->Clone( "Data_SingleEle_E"       ) ; 
     //h_Data_SingleEle_D      = (TH1F*) file_Data_SingleEle_D      -> Get("h_"+varname)->Clone( "Data_SingleEle_D"       ) ; 
     //h_Data_SingleEle_C      = (TH1F*) file_Data_SingleEle_C      -> Get("h_"+varname)->Clone( "Data_SingleEle_C"       ) ; 
     //h_Data_SingleEle_B_2    = (TH1F*) file_Data_SingleEle_B_2    -> Get("h_"+varname)->Clone( "Data_SingleEle_B_2"     ) ; 
     */
     h_Data_SinglePhoton_H_3 = (TH1F*) file_Data_SinglePhoton_H_3 -> Get("h_"+varname)->Clone( "Data_SinglePhoton_H_3"  ) ; 
     h_Data_SinglePhoton_H_2 = (TH1F*) file_Data_SinglePhoton_H_2 -> Get("h_"+varname)->Clone( "Data_SinglePhoton_H_2"  ) ; 
     h_Data_SinglePhoton_G   = (TH1F*) file_Data_SinglePhoton_G   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_G"    ) ; 
     //h_Data_SinglePhoton_F   = (TH1F*) file_Data_SinglePhoton_F   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_F"    ) ; 
     //h_Data_SinglePhoton_E   = (TH1F*) file_Data_SinglePhoton_E   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_E"    ) ; 
     //h_Data_SinglePhoton_D   = (TH1F*) file_Data_SinglePhoton_D   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_D"    ) ; 
     //h_Data_SinglePhoton_C   = (TH1F*) file_Data_SinglePhoton_C   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_C"    ) ; 
     //h_Data_SinglePhoton_B_2 = (TH1F*) file_Data_SinglePhoton_B_2 -> Get("h_"+varname)->Clone( "Data_SinglePhoton_B_2"  ) ; 
     h_Data_DoubleMu_H_3     = (TH1F*) file_Data_DoubleMu_H_3     -> Get("h_"+varname)->Clone( "Data_DoubleMu_H_3"      ) ; 
     h_Data_DoubleMu_H_2     = (TH1F*) file_Data_DoubleMu_H_2     -> Get("h_"+varname)->Clone( "Data_DoubleMu_H_2"      ) ; 
     h_Data_DoubleMu_G       = (TH1F*) file_Data_DoubleMu_G       -> Get("h_"+varname)->Clone( "Data_DoubleMu_G"        ) ; 
     //h_Data_DoubleMu_F       = (TH1F*) file_Data_DoubleMu_F       -> Get("h_"+varname)->Clone( "Data_DoubleMu_F"        ) ; 
     //h_Data_DoubleMu_E       = (TH1F*) file_Data_DoubleMu_E       -> Get("h_"+varname)->Clone( "Data_DoubleMu_E"        ) ; 
     //h_Data_DoubleMu_D       = (TH1F*) file_Data_DoubleMu_D       -> Get("h_"+varname)->Clone( "Data_DoubleMu_D"        ) ; 
     //h_Data_DoubleMu_C       = (TH1F*) file_Data_DoubleMu_C       -> Get("h_"+varname)->Clone( "Data_DoubleMu_C"        ) ; 
     //h_Data_DoubleMu_B_2     = (TH1F*) file_Data_DoubleMu_B_2     -> Get("h_"+varname)->Clone( "Data_DoubleMu_B_2"      ) ; 
     h_Data_DoubleEG_H_3     = (TH1F*) file_Data_DoubleEG_H_3     -> Get("h_"+varname)->Clone( "Data_DoubleEG_H_3"      ) ; 
     h_Data_DoubleEG_H_2     = (TH1F*) file_Data_DoubleEG_H_2     -> Get("h_"+varname)->Clone( "Data_DoubleEG_H_2"      ) ; 
     h_Data_DoubleEG_G       = (TH1F*) file_Data_DoubleEG_G       -> Get("h_"+varname)->Clone( "Data_DoubleEG_G"        ) ; 
     //h_Data_DoubleEG_F       = (TH1F*) file_Data_DoubleEG_F       -> Get("h_"+varname)->Clone( "Data_DoubleEG_F"        ) ; 
     //h_Data_DoubleEG_E       = (TH1F*) file_Data_DoubleEG_E       -> Get("h_"+varname)->Clone( "Data_DoubleEG_E"        ) ; 
     //h_Data_DoubleEG_D       = (TH1F*) file_Data_DoubleEG_D       -> Get("h_"+varname)->Clone( "Data_DoubleEG_D"        ) ; 
     //h_Data_DoubleEG_C       = (TH1F*) file_Data_DoubleEG_C       -> Get("h_"+varname)->Clone( "Data_DoubleEG_C"        ) ; 
     //h_Data_DoubleEG_B_2     = (TH1F*) file_Data_DoubleEG_B_2     -> Get("h_"+varname)->Clone( "Data_DoubleEG_B_2"      ) ; 
     h_Data_MuonEG_H_3     = (TH1F*) file_Data_MuonEG_H_3     -> Get("h_"+varname)->Clone( "Data_MuonEG_H_3"      ) ; 
     h_Data_MuonEG_H_2     = (TH1F*) file_Data_MuonEG_H_2     -> Get("h_"+varname)->Clone( "Data_MuonEG_H_2"      ) ; 
     h_Data_MuonEG_G       = (TH1F*) file_Data_MuonEG_G       -> Get("h_"+varname)->Clone( "Data_MuonEG_G"        ) ; 
     //h_Data_MuonEG_F       = (TH1F*) file_Data_MuonEG_F       -> Get("h_"+varname)->Clone( "Data_MuonEG_F"        ) ; 
     //h_Data_MuonEG_E       = (TH1F*) file_Data_MuonEG_E       -> Get("h_"+varname)->Clone( "Data_MuonEG_E"        ) ; 
     //h_Data_MuonEG_D       = (TH1F*) file_Data_MuonEG_D       -> Get("h_"+varname)->Clone( "Data_MuonEG_D"        ) ; 
     //h_Data_MuonEG_C       = (TH1F*) file_Data_MuonEG_C       -> Get("h_"+varname)->Clone( "Data_MuonEG_C"        ) ; 
     //h_Data_MuonEG_B_2     = (TH1F*) file_Data_MuonEG_B_2     -> Get("h_"+varname)->Clone( "Data_MuonEG_B_2"      ) ; 

     // merge histograms
     h_DY = (TH1F*)h_DY50->Clone("DY");
      h_DY->Add(h_DY10to50           ); 

     h_altDY = (TH1F*)h_DY50->Clone("altDY");
      h_altDY->Add(h_DY5to50_HT100To200); 
      h_altDY->Add(h_DY5to50_HT200To400); 
      h_altDY->Add(h_DY5to50_HT400To600); 
      h_altDY->Add(h_DY5to50_HT600ToInf); 

     h_GJets = (TH1F*)h_GJets_HT40To100->Clone("GJets");
      h_GJets->Add(h_GJets_HT100To200);
      h_GJets->Add(h_GJets_HT200To400);
      h_GJets->Add(h_GJets_HT400To600);
      h_GJets->Add(h_GJets_HT600ToInf);

     h_ST = (TH1F*)h_ST_s->Clone("ST");
      h_ST->Add(h_STbar_t);
      h_ST->Add(h_ST_t);
      h_ST->Add(h_STbar_tW);
      h_ST->Add(h_ST_tW);

     h_ZH = (TH1F*)h_ZH_HToBB_ZToLL->Clone("ZH");
      h_ZH->Add(h_ggZH_HToBB_ZToLL);

     h_VV = (TH1F*)h_WW->Clone("VV");
      h_VV->Add(h_WZ             ) ;
      h_VV->Add(h_ZZ             ) ;

     h_altVV = (TH1F*)h_WWTo2L2Nu->Clone("altVV");
      h_altVV->Add(h_WWToLNuQQ       ) ;
      h_altVV->Add(h_WZTo1L3Nu       ) ;
      h_altVV->Add(h_WZTo3LNu        ) ;
      h_altVV->Add(h_WZToLNu2QorQQ2L ) ;
      h_altVV->Add(h_ZZTo2L2Nu       ) ;
      h_altVV->Add(h_ZZTo2L2Q        ) ;
      h_altVV->Add(h_ZZTo2Q2Nu       ) ;
      h_altVV->Add(h_ZZTo4L          ) ;

     h_TT = (TH1F*)h_TTJets->Clone("TT");

     h_altTT = (TH1F*)h_TTtoLfromTbar->Clone("altTT");
      h_altTT->Add(h_TTtoLfromT    );
      h_altTT->Add(h_TTtoLL        );
    
     h_VG = (TH1F*)h_WG->Clone("VG");
      h_VG->Add(h_ZG);

     h_QCD = (TH1F*)h_QCD_HT100to200->Clone("QCD");
      h_QCD->Add(h_QCD_HT200to300   );
      h_QCD->Add(h_QCD_HT300to500   );
      h_QCD->Add(h_QCD_HT500to700   );
      h_QCD->Add(h_QCD_HT700to1000  );
      h_QCD->Add(h_QCD_HT1000to1500 );
      h_QCD->Add(h_QCD_HT1500to2000 );
      h_QCD->Add(h_QCD_HT2000toInf  );

     h_Sig_MS15ct1000  = (TH1F*) h_Sig_ZH_MS15ct1000   ->Clone( "Sig_MS15ct1000" ) ;
     h_Sig_MS15ct100   = (TH1F*) h_Sig_ZH_MS15ct100    ->Clone( "Sig_MS15ct100 " ) ;
     h_Sig_MS15ct10    = (TH1F*) h_Sig_ZH_MS15ct10     ->Clone( "Sig_MS15ct10  " ) ;
     h_Sig_MS15ct1     = (TH1F*) h_Sig_ZH_MS15ct1      ->Clone( "Sig_MS15ct1   " ) ;
     h_Sig_MS40ct1000  = (TH1F*) h_Sig_ZH_MS40ct1000   ->Clone( "Sig_MS40ct1000" ) ;
     h_Sig_MS40ct100   = (TH1F*) h_Sig_ZH_MS40ct100    ->Clone( "Sig_MS40ct100 " ) ;
     h_Sig_MS40ct10    = (TH1F*) h_Sig_ZH_MS40ct10     ->Clone( "Sig_MS40ct10  " ) ;
     h_Sig_MS40ct1     = (TH1F*) h_Sig_ZH_MS40ct1      ->Clone( "Sig_MS40ct1   " ) ;
     h_Sig_MS55ct1000  = (TH1F*) h_Sig_ZH_MS55ct1000   ->Clone( "Sig_MS55ct1000" ) ;
     h_Sig_MS55ct100   = (TH1F*) h_Sig_ZH_MS55ct100    ->Clone( "Sig_MS55ct100 " ) ;
     h_Sig_MS55ct10    = (TH1F*) h_Sig_ZH_MS55ct10     ->Clone( "Sig_MS55ct10  " ) ;
     h_Sig_MS55ct1     = (TH1F*) h_Sig_ZH_MS55ct1      ->Clone( "Sig_MS55ct1   " ) ;

     h_Sig_MS15ct1000 ->Add( h_Sig_ggZH_MS15ct1000 ) ;
     h_Sig_MS15ct100  ->Add( h_Sig_ggZH_MS15ct100  ) ;
     h_Sig_MS15ct10   ->Add( h_Sig_ggZH_MS15ct10   ) ;
     h_Sig_MS15ct1    ->Add( h_Sig_ggZH_MS15ct1    ) ;
     h_Sig_MS40ct1000 ->Add( h_Sig_ggZH_MS40ct1000 ) ;
     h_Sig_MS40ct100  ->Add( h_Sig_ggZH_MS40ct100  ) ;
     h_Sig_MS40ct10   ->Add( h_Sig_ggZH_MS40ct10   ) ;
     h_Sig_MS40ct1    ->Add( h_Sig_ggZH_MS40ct1    ) ;
     h_Sig_MS55ct1000 ->Add( h_Sig_ggZH_MS55ct1000 ) ;
     h_Sig_MS55ct100  ->Add( h_Sig_ggZH_MS55ct100  ) ;
     h_Sig_MS55ct10   ->Add( h_Sig_ggZH_MS55ct10   ) ;
     h_Sig_MS55ct1    ->Add( h_Sig_ggZH_MS55ct1    ) ;

     // rescale MC to match eras used
     h_DY         ->Scale(MCSF); 
     h_GJets      ->Scale(MCSF); 
     h_ST         ->Scale(MCSF); 
     h_ZH         ->Scale(MCSF); 
     h_VV         ->Scale(MCSF); 
     h_TT         ->Scale(MCSF); 
     h_VG         ->Scale(MCSF); 
     h_QCD        ->Scale(MCSF); 
     h_WJetsToLNu ->Scale(MCSF); 
     h_altDY      ->Scale(MCSF);
     h_altVV      ->Scale(MCSF);
     h_altTT      ->Scale(MCSF);
     h_Sig_MS15ct1000 ->Scale(MCSF);
     h_Sig_MS15ct100  ->Scale(MCSF);
     h_Sig_MS15ct10   ->Scale(MCSF);
     h_Sig_MS15ct1    ->Scale(MCSF);
     h_Sig_MS40ct1000 ->Scale(MCSF);
     h_Sig_MS40ct100  ->Scale(MCSF);
     h_Sig_MS40ct10   ->Scale(MCSF);
     h_Sig_MS40ct1    ->Scale(MCSF);
     h_Sig_MS55ct1000 ->Scale(MCSF);
     h_Sig_MS55ct100  ->Scale(MCSF);
     h_Sig_MS55ct10   ->Scale(MCSF);
     h_Sig_MS55ct1    ->Scale(MCSF);


     h_bkgtotal= (TH1F*)h_DY->Clone("bkgtotal");
      h_bkgtotal->Add(h_GJets ) ;
      h_bkgtotal->Add(h_ST    ) ;
      h_bkgtotal->Add(h_ZH    ) ;
      h_bkgtotal->Add(h_VV    ) ;
      h_bkgtotal->Add(h_TT    ) ;
      h_bkgtotal->Add(h_VG    ) ;
      h_bkgtotal->Add(h_QCD   ) ;
      h_bkgtotal->Add(h_WJetsToLNu      ) ;

     h_light= (TH1F*)h_DY->Clone("light");
      h_light->Add(h_GJets ) ;

     h_light_alt= (TH1F*)h_DY->Clone("light_alt");
      h_light_alt->Add(h_GJets ) ;

     h_other=(TH1F*)h_VV->Clone("other");
      h_other->Add(h_VG);
      h_other->Add(h_QCD);
      h_other->Add(h_WJetsToLNu);
      h_other->Add(h_ZH    ) ;

     h_other_alt=(TH1F*)h_altVV->Clone("other_alt");
      h_other_alt->Add(h_VG);
      h_other_alt->Add(h_QCD);
      h_other_alt->Add(h_WJetsToLNu);
      h_other_alt->Add(h_ZH    ) ;

     h_heavy= (TH1F*)h_TT->Clone("heavy");
      h_heavy->Add(h_ST    ) ;

     h_heavy_alt= (TH1F*)h_altTT->Clone("heavy_alt");
      h_heavy_alt->Add(h_ST    ) ;

     //if( region.Contains("OneEle") ){
     //  //if(HIP){
     //  // h_Data = (TH1F*)h_Data_DoubleEG_B_2->Clone("Data");
     //  // h_Data->Add( h_Data_DoubleEG_F   )     ; 
     //  // h_Data->Add( h_Data_DoubleEG_E   )     ; 
     //  // h_Data->Add( h_Data_DoubleEG_D   )     ; 
     //  // h_Data->Add( h_Data_DoubleEG_C   )     ; 
     //  //}
     //  //else{
     //   h_Data = (TH1F*)h_Data_SingleEle_G->Clone("Data");
     //   h_Data->Add( h_Data_SingleEle_H_2 )     ; 
     //   h_Data->Add( h_Data_SingleEle_H_3 )     ; 
     //  //}
     //}
     if( region.Contains("TwoEle") ){
        h_Data = (TH1F*)h_Data_DoubleEG_G->Clone("Data");
        h_Data->Add( h_Data_DoubleEG_H_2 )     ; 
        h_Data->Add( h_Data_DoubleEG_H_3 )     ; 
     }
     //if( region.Contains("OneMu") ){
     //   h_Data = (TH1F*)h_Data_SingleMu_G->Clone("Data");
     //   h_Data->Add( h_Data_SingleMu_H_2 )     ; 
     //   h_Data->Add( h_Data_SingleMu_H_3 )     ; 
     //}
     if( region.Contains("TwoMu") ){
        h_Data = (TH1F*)h_Data_DoubleMu_G->Clone("Data");
        h_Data->Add( h_Data_DoubleMu_H_2 )     ; 
        h_Data->Add( h_Data_DoubleMu_H_3 )     ; 
     }
     if( region.Contains("OnePho") ){
        h_Data = (TH1F*)h_Data_SinglePhoton_G->Clone("Data");
        h_Data->Add( h_Data_SinglePhoton_H_2 )     ; 
        h_Data->Add( h_Data_SinglePhoton_H_3 )     ; 
     }
     if( region.Contains("EleMu") ){
        h_Data = (TH1F*)h_Data_MuonEG_G->Clone("Data");
        h_Data->Add( h_Data_MuonEG_H_2 )     ; 
        h_Data->Add( h_Data_MuonEG_H_3 )     ; 
     }
     
     //CSV-style printout for Ted
     if(varname.Contains("nSelectedAODCaloJetTag") && !extraname.Contains("log") && uncbin==""){
       TString fname = "forTed_"; fname+=varname; fname+=".csv";
       std::cout << "Writing " << fname<< std::endl;
       FILE *f = fopen (fname, "w");
       if(!region.Contains("ZH")) print_hist(h_Data, "Data", f);
       print_hist(h_DY, "DY", f);
       print_hist(h_GJets, "GJets", f);
       print_hist(h_ST, "SingleTop", f);
       print_hist(h_ZH, "ZH", f);
       print_hist(h_VV, "VV", f);
       print_hist(h_TT, "TT", f);
       print_hist(h_VG, "VG", f);
       print_hist(h_QCD, "QCD", f);
       print_hist(h_WJetsToLNu, "WJets", f);
       print_hist(h_bkgtotal, "Total", f);
       print_hist(h_altTT, "altTT", f);
       print_hist(h_altVV, "altVV", f);
       print_hist(h_altDY, "altDY", f);
       print_hist(h_light, "light", f);
       print_hist(h_light_alt, "light_alt", f);
       print_hist(h_heavy, "heavy", f);
       print_hist(h_heavy_alt, "heavy_alt", f);
       print_hist(h_other, "other", f);
       print_hist(h_other_alt, "other_alt", f);
       print_hist(h_ZZ, "ZZ", f);
       print_hist(h_WZ, "WZ", f);
       print_hist(h_WW, "WW", f);
       //sig                                                                                                                                      //print_hist(h_Sig_ZH_MS15ct1000, "h_Sig_ZH_MS15ct1000", f);
       print_hist(h_Sig_ZH_MS15ct100      ,"h_Sig_ZH_MS15ct100", f);
       print_hist(h_Sig_ZH_MS15ct10       ,"h_Sig_ZH_MS15ct10", f);
       //print_hist(h_Sig_ZH_MS15ct1        ,"h_Sig_ZH_MS15ct1", f);
       //print_hist(h_Sig_ZH_MS40ct1000     ,"h_Sig_ZH_MS40ct1000", f);
       print_hist(h_Sig_ZH_MS40ct100      ,"h_Sig_ZH_MS40ct100", f);
       print_hist(h_Sig_ZH_MS40ct10       ,"h_Sig_ZH_MS40ct10", f);
       //print_hist(h_Sig_ZH_MS40ct1        ,"h_Sig_ZH_MS40ct1", f);
       //print_hist(h_Sig_ZH_MS55ct1000     ,"h_Sig_ZH_MS55ct1000", f);
       print_hist(h_Sig_ZH_MS55ct100      ,"h_Sig_ZH_MS55ct100", f);
       print_hist(h_Sig_ZH_MS55ct10       ,"h_Sig_ZH_MS55ct10", f);
       //print_hist(h_Sig_ZH_MS55ct1        ,"h_Sig_ZH_MS55ct1", f);
       //print_hist(h_Sig_ggZH_MS15ct1000   ,"h_Sig_ggZH_MS15ct1000", f);
       print_hist(h_Sig_ggZH_MS15ct100    ,"h_Sig_ggZH_MS15ct100", f);
       print_hist(h_Sig_ggZH_MS15ct10     ,"h_Sig_ggZH_MS15ct10", f);
       //print_hist(h_Sig_ggZH_MS15ct1      ,"h_Sig_ggZH_MS15ct1", f);
       //print_hist(h_Sig_ggZH_MS40ct1000   ,"h_Sig_ggZH_MS40ct1000", f);
       print_hist(h_Sig_ggZH_MS40ct100    ,"h_Sig_ggZH_MS40ct100", f);
       print_hist(h_Sig_ggZH_MS40ct10     ,"h_Sig_ggZH_MS40ct10", f);
       //print_hist(h_Sig_ggZH_MS40ct1      ,"h_Sig_ggZH_MS40ct1", f);
       //print_hist(h_Sig_ggZH_MS55ct1000   ,"h_Sig_ggZH_MS55ct1000", f);
       print_hist(h_Sig_ggZH_MS55ct100    ,"h_Sig_ggZH_MS55ct100", f);
       print_hist(h_Sig_ggZH_MS55ct10     ,"h_Sig_ggZH_MS55ct10", f);
       //print_hist(h_Sig_ggZH_MS55ct1      ,"h_Sig_ggZH_MS55ct1", f);
       fclose(f);
     }


     // Integrals
     Float_t  int_DY5to50_HT100To200       = h_DY5to50_HT100To200              ->Integral(0,-1); 
     Float_t  int_DY5to50_HT200To400       = h_DY5to50_HT200To400              ->Integral(0,-1); 
     Float_t  int_DY5to50_HT400To600       = h_DY5to50_HT400To600              ->Integral(0,-1); 
     Float_t  int_DY5to50_HT600ToInf       = h_DY5to50_HT600ToInf              ->Integral(0,-1); 
     Float_t  int_DY10to50                 = h_DY10to50                        ->Integral(0,-1); 
     Float_t  int_DY50                     = h_DY50                            ->Integral(0,-1); 

     Float_t  int_ggZH_HToBB_ZToLL         = h_ggZH_HToBB_ZToLL                ->Integral(0,-1); 
     Float_t  int_ZH_HToBB_ZToLL           = h_ZH_HToBB_ZToLL                  ->Integral(0,-1); 

     Float_t  int_GJets_HT40To100          = h_GJets_HT40To100                 ->Integral(0,-1); 
     Float_t  int_GJets_HT100To200         = h_GJets_HT100To200                ->Integral(0,-1); 
     Float_t  int_GJets_HT200To400         = h_GJets_HT200To400                ->Integral(0,-1); 
     Float_t  int_GJets_HT400To600         = h_GJets_HT400To600                ->Integral(0,-1); 
     Float_t  int_GJets_HT600ToInf         = h_GJets_HT600ToInf                ->Integral(0,-1); 

     Float_t  int_ST_s                     = h_ST_s                            ->Integral(0,-1); 
     Float_t  int_STbar_t                  = h_STbar_t                         ->Integral(0,-1); 
     Float_t  int_ST_t                     = h_ST_t                            ->Integral(0,-1); 
     Float_t  int_STbar_tW                 = h_STbar_tW                        ->Integral(0,-1); 
     Float_t  int_ST_tW                    = h_ST_tW                           ->Integral(0,-1); 

     Float_t  int_TTJets                   = h_TTJets                          ->Integral(0,-1); 
     Float_t  int_TTtoLL                   = h_TTtoLL                          ->Integral(0,-1); 
     Float_t  int_TTtoLfromTbar            = h_TTtoLfromTbar                   ->Integral(0,-1); 
     Float_t  int_TTtoLfromT               = h_TTtoLfromT                      ->Integral(0,-1); 
     Float_t  int_WJetsToLNu               = h_WJetsToLNu                      ->Integral(0,-1); 
     Float_t  int_WG                       = h_WG                              ->Integral(0,-1); 
     Float_t  int_ZG                       = h_ZG                              ->Integral(0,-1); 
     Float_t  int_WW                       = h_WW                              ->Integral(0,-1); 
     Float_t  int_WZ                       = h_WZ                              ->Integral(0,-1); 
     Float_t  int_ZZ                       = h_ZZ                              ->Integral(0,-1); 
     Float_t  int_WWTo2L2Nu                = h_WWTo2L2Nu                       ->Integral(0,-1); 
     Float_t  int_WWToLNuQQ                = h_WWToLNuQQ                       ->Integral(0,-1); 
     Float_t  int_WZTo1L3Nu                = h_WZTo1L3Nu                       ->Integral(0,-1); 
     Float_t  int_WZTo3LNu                 = h_WZTo3LNu                        ->Integral(0,-1); 
     Float_t  int_WZToLNu2QorQQ2L          = h_WZToLNu2QorQQ2L                 ->Integral(0,-1); 
     Float_t  int_ZZTo2L2Nu                = h_ZZTo2L2Nu                       ->Integral(0,-1); 
     Float_t  int_ZZTo2L2Q                 = h_ZZTo2L2Q                        ->Integral(0,-1); 
     Float_t  int_ZZTo2Q2Nu                = h_ZZTo2Q2Nu                       ->Integral(0,-1); 
     Float_t  int_ZZTo4L                   = h_ZZTo4L                          ->Integral(0,-1); 
                               
     Float_t  int_Sig_ZH_MS15ct1000        = h_Sig_ZH_MS15ct1000               ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS15ct100         = h_Sig_ZH_MS15ct100                ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS15ct10          = h_Sig_ZH_MS15ct10                 ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS15ct1           = h_Sig_ZH_MS15ct1                  ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS40ct1000        = h_Sig_ZH_MS40ct1000               ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS40ct100         = h_Sig_ZH_MS40ct100                ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS40ct10          = h_Sig_ZH_MS40ct10                 ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS40ct1           = h_Sig_ZH_MS40ct1                  ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS55ct1000        = h_Sig_ZH_MS55ct1000               ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS55ct100         = h_Sig_ZH_MS55ct100                ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS55ct10          = h_Sig_ZH_MS55ct10                 ->Integral(0,-1);                   
     Float_t  int_Sig_ZH_MS55ct1           = h_Sig_ZH_MS55ct1                  ->Integral(0,-1);                     

     Float_t  int_Sig_ggZH_MS15ct1000      = h_Sig_ggZH_MS15ct1000             ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS15ct100       = h_Sig_ggZH_MS15ct100              ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS15ct10        = h_Sig_ggZH_MS15ct10               ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS15ct1         = h_Sig_ggZH_MS15ct1                ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS40ct1000      = h_Sig_ggZH_MS40ct1000             ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS40ct100       = h_Sig_ggZH_MS40ct100              ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS40ct10        = h_Sig_ggZH_MS40ct10               ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS40ct1         = h_Sig_ggZH_MS40ct1                ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS55ct1000      = h_Sig_ggZH_MS55ct1000             ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS55ct100       = h_Sig_ggZH_MS55ct100              ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS55ct10        = h_Sig_ggZH_MS55ct10               ->Integral(0,-1);                   
     Float_t  int_Sig_ggZH_MS55ct1         = h_Sig_ggZH_MS55ct1                ->Integral(0,-1);                   

     // integrals of summed histograms
     Float_t int_DY        = h_DY       ->Integral(0,-1); 
     Float_t int_altDY     = h_altDY    ->Integral(0,-1); 
     Float_t int_GJets     = h_GJets    ->Integral(0,-1); 
     Float_t int_ST        = h_ST       ->Integral(0,-1); 
     Float_t int_ZH        = h_ZH       ->Integral(0,-1); 
     Float_t int_VV        = h_VV       ->Integral(0,-1); 
     Float_t int_altVV     = h_altVV    ->Integral(0,-1); 
     Float_t int_TT        = h_TT       ->Integral(0,-1); 
     Float_t int_altTT     = h_altTT    ->Integral(0,-1); 
     Float_t int_VG        = h_VG       ->Integral(0,-1); 
     Float_t int_QCD       = h_QCD      ->Integral(0,-1); 
     Float_t int_bkgtotal  = h_bkgtotal ->Integral(0,-1); 
     Float_t int_Data      = h_Data     ->Integral(0,-1); 
     Float_t int_bkgOnData = (double)int_bkgtotal / int_Data ;
     Float_t int_Sig_MS15ct1000 = h_Sig_MS15ct1000 ->Integral(0,-1);
     Float_t int_Sig_MS15ct100  = h_Sig_MS15ct100  ->Integral(0,-1);
     Float_t int_Sig_MS15ct10   = h_Sig_MS15ct10   ->Integral(0,-1);
     Float_t int_Sig_MS15ct1    = h_Sig_MS15ct1    ->Integral(0,-1);
     Float_t int_Sig_MS40ct1000 = h_Sig_MS40ct1000 ->Integral(0,-1);
     Float_t int_Sig_MS40ct100  = h_Sig_MS40ct100  ->Integral(0,-1);
     Float_t int_Sig_MS40ct10   = h_Sig_MS40ct10   ->Integral(0,-1);
     Float_t int_Sig_MS40ct1    = h_Sig_MS40ct1    ->Integral(0,-1);
     Float_t int_Sig_MS55ct1000 = h_Sig_MS55ct1000 ->Integral(0,-1);
     Float_t int_Sig_MS55ct100  = h_Sig_MS55ct100  ->Integral(0,-1);
     Float_t int_Sig_MS55ct10   = h_Sig_MS55ct10   ->Integral(0,-1);
     Float_t int_Sig_MS55ct1    = h_Sig_MS55ct1    ->Integral(0,-1);
     /*
     Float_t  int_Data_SingleMu_H_3        = h_Data_SingleMu_H_3               ->Integral(0,-1);                   
     Float_t  int_Data_SingleMu_H_2        = h_Data_SingleMu_H_2               ->Integral(0,-1);                   
     Float_t  int_Data_SingleMu_G          = h_Data_SingleMu_G                 ->Integral(0,-1);                   
     // Float_t  int_Data_SingleMu_F          = h_Data_SingleMu_F                 ->Integral(0,-1);                   
     // Float_t  int_Data_SingleMu_E          = h_Data_SingleMu_E                 ->Integral(0,-1);                   
     // Float_t  int_Data_SingleMu_D          = h_Data_SingleMu_D                 ->Integral(0,-1);                   
     // Float_t  int_Data_SingleMu_C          = h_Data_SingleMu_C                 ->Integral(0,-1);                   
     // Float_t  int_Data_SingleMu_B_2        = h_Data_SingleMu_B_2               ->Integral(0,-1);                   
     Float_t  int_Data_SingleEle_H_3       = h_Data_SingleEle_H_3              ->Integral(0,-1);                   
     Float_t  int_Data_SingleEle_H_2       = h_Data_SingleEle_H_2              ->Integral(0,-1);                   
     Float_t  int_Data_SingleEle_G         = h_Data_SingleEle_G                ->Integral(0,-1);                   
     */
     // Float_t  int_Data_SingleEle_F         = h_Data_SingleEle_F                ->Integral(0,-1);                   
     // Float_t  int_Data_SingleEle_E         = h_Data_SingleEle_E                ->Integral(0,-1);                   
     // Float_t  int_Data_SingleEle_D         = h_Data_SingleEle_D                ->Integral(0,-1);                   
     // Float_t  int_Data_SingleEle_C         = h_Data_SingleEle_C                ->Integral(0,-1);                   
     // Float_t  int_Data_SingleEle_B_2       = h_Data_SingleEle_B_2              ->Integral(0,-1);                   
     Float_t  int_Data_SinglePhoton_H_3    = h_Data_SinglePhoton_H_3           ->Integral(0,-1);                     
     Float_t  int_Data_SinglePhoton_H_2    = h_Data_SinglePhoton_H_2           ->Integral(0,-1);                     
     Float_t  int_Data_SinglePhoton_G      = h_Data_SinglePhoton_G             ->Integral(0,-1);                     
     // Float_t  int_Data_SinglePhoton_F      = h_Data_SinglePhoton_F             ->Integral(0,-1);                     
     // Float_t  int_Data_SinglePhoton_E      = h_Data_SinglePhoton_E             ->Integral(0,-1);                     
     // Float_t  int_Data_SinglePhoton_D      = h_Data_SinglePhoton_D             ->Integral(0,-1);                     
     // Float_t  int_Data_SinglePhoton_C      = h_Data_SinglePhoton_C             ->Integral(0,-1);                     
     // Float_t  int_Data_SinglePhoton_B_2    = h_Data_SinglePhoton_B_2           ->Integral(0,-1);                     
     Float_t  int_Data_DoubleMu_H_3        = h_Data_DoubleMu_H_3               ->Integral(0,-1);                     
     Float_t  int_Data_DoubleMu_H_2        = h_Data_DoubleMu_H_2               ->Integral(0,-1);                     
     Float_t  int_Data_DoubleMu_G          = h_Data_DoubleMu_G                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleMu_F          = h_Data_DoubleMu_F                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleMu_E          = h_Data_DoubleMu_E                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleMu_D          = h_Data_DoubleMu_D                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleMu_C          = h_Data_DoubleMu_C                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleMu_B_2        = h_Data_DoubleMu_B_2               ->Integral(0,-1);                     
     Float_t  int_Data_DoubleEG_H_3        = h_Data_DoubleEG_H_3               ->Integral(0,-1);                     
     Float_t  int_Data_DoubleEG_H_2        = h_Data_DoubleEG_H_2               ->Integral(0,-1);                     
     Float_t  int_Data_DoubleEG_G          = h_Data_DoubleEG_G                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleEG_F          = h_Data_DoubleEG_F                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleEG_E          = h_Data_DoubleEG_E                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleEG_D          = h_Data_DoubleEG_D                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleEG_C          = h_Data_DoubleEG_C                 ->Integral(0,-1);                     
     //Float_t  int_Data_DoubleEG_B_2        = h_Data_DoubleEG_B_2               ->Integral(0,-1);                 
     
     // Math

     // Float_t int_Data_SingleEleBCDEF =
     //          int_Data_SingleEle_B_2 +
     //          int_Data_SingleEle_C   +
     //          int_Data_SingleEle_D   +
     //          int_Data_SingleEle_E   +
     //          int_Data_SingleEle_F   ;

     // Float_t int_Data_SingleMuBCDEF =
     //          int_Data_SingleMu_B_2 +
     //          int_Data_SingleMu_C   +
     //          int_Data_SingleMu_D   +
     //          int_Data_SingleMu_E   +
     //          int_Data_SingleMu_F   ;
     /*
     Float_t int_Data_SingleEleGH =
              int_Data_SingleEle_G   +
              int_Data_SingleEle_H_2 +
              int_Data_SingleEle_H_3 ;

     Float_t int_Data_SingleMuGH =
              int_Data_SingleMu_G   +
              int_Data_SingleMu_H_2 +
              int_Data_SingleMu_H_3 ;
     */
     //Float_t int_Data_DoubleEGBCDEF =
     //         int_Data_DoubleEG_B_2 +
     //         int_Data_DoubleEG_C   +
     //         int_Data_DoubleEG_D   +
     //         int_Data_DoubleEG_E   +
     //         int_Data_DoubleEG_F   ;

     //Float_t int_Data_DoubleMuBCDEF =
     //         int_Data_DoubleMu_B_2 +
     //         int_Data_DoubleMu_C   +
     //         int_Data_DoubleMu_D   +
     //         int_Data_DoubleMu_E   +
     //         int_Data_DoubleMu_F   ;

     Float_t int_Data_DoubleEGGH =
              int_Data_DoubleEG_G   +
              int_Data_DoubleEG_H_2 +
              int_Data_DoubleEG_H_3 ;

     Float_t int_Data_DoubleMuGH =
              int_Data_DoubleMu_G   +
              int_Data_DoubleMu_H_2 +
              int_Data_DoubleMu_H_3 ;


     // output tables
     if(domaketable){
      FILE * outfulltable;
      outfulltable = fopen (fulllogname+".tex","w");
       fprintf (outfulltable, "\\documentclass{standalone}\n\n");
       fprintf (outfulltable, "\\begin{document}\n\n");
       fprintf (outfulltable, "\\begin{tabular}{rl}\n\n");
       //fprintf (outfulltable, " \\Huge %s & \\Huge %s   \\\\\n", lepton.Data(), region.Data()); 
       fprintf (outfulltable, " \\Huge %s   \\\\\n", region.Data()); 
       fprintf (outfulltable, " \\hline \n");
       fprintf (outfulltable, "\\Large  Backgrounds \\\\\n");
       fprintf (outfulltable, " \\hline \n");

       fprintf (outfulltable, "DY5to50 HT100To200      & %3.1f \\\\\n", int_DY5to50_HT100To200     ) ; 
       fprintf (outfulltable, "DY5to50 HT200To400      & %3.1f \\\\\n", int_DY5to50_HT200To400     ) ; 
       fprintf (outfulltable, "DY5to50 HT400To600      & %3.1f \\\\\n", int_DY5to50_HT400To600     ) ; 
       fprintf (outfulltable, "DY5to50 HT600ToInf      & %3.1f \\\\\n", int_DY5to50_HT600ToInf     ) ; 
       fprintf (outfulltable, "DY10to50                & %3.1f \\\\\n", int_DY10to50               ) ; 
       fprintf (outfulltable, "DY50                    & %3.1f \\\\\n", int_DY50                   ) ; 

       fprintf (outfulltable, " \\hline \n");
       fprintf (outfulltable, "ggZH HToBB ZToLL        & %3.1f \\\\\n", int_ggZH_HToBB_ZToLL       ) ; 
       fprintf (outfulltable, "ZH HToBB ZToLL          & %3.1f \\\\\n", int_ZH_HToBB_ZToLL         ) ; 
       fprintf (outfulltable, " \\hline \n");

       fprintf (outfulltable, "GJets HT40To100         & %3.1f \\\\\n", int_GJets_HT40To100        ) ; 
       fprintf (outfulltable, "GJets HT100To200        & %3.1f \\\\\n", int_GJets_HT100To200       ) ; 
       fprintf (outfulltable, "GJets HT200To400        & %3.1f \\\\\n", int_GJets_HT200To400       ) ; 
       fprintf (outfulltable, "GJets HT400To600        & %3.1f \\\\\n", int_GJets_HT400To600       ) ; 
       fprintf (outfulltable, "GJets HT600ToInf        & %3.1f \\\\\n", int_GJets_HT600ToInf       ) ; 
       fprintf (outfulltable, " \\hline \n");

       fprintf (outfulltable, "ST s                    & %3.1f \\\\\n", int_ST_s                   ) ; 
       fprintf (outfulltable, "STbar t                 & %3.1f \\\\\n", int_STbar_t                ) ; 
       fprintf (outfulltable, "ST t                    & %3.1f \\\\\n", int_ST_t                   ) ; 
       fprintf (outfulltable, "STbar tW                & %3.1f \\\\\n", int_STbar_tW               ) ; 
       fprintf (outfulltable, "ST tW                   & %3.1f \\\\\n", int_ST_tW                  ) ; 
       fprintf (outfulltable, " \\hline \n");

       fprintf (outfulltable, "TTJets                  & %3.1f \\\\\n", int_TTJets                 ) ; 
       fprintf (outfulltable, "TTtoLL                  & %3.1f \\\\\n", int_TTtoLL                 ) ; 
       fprintf (outfulltable, "TTtoLfromTbar           & %3.1f \\\\\n", int_TTtoLfromTbar          ) ; 
       fprintf (outfulltable, "TTtoLfromT              & %3.1f \\\\\n", int_TTtoLfromT             ) ; 
       fprintf (outfulltable, " \\hline \n");
       fprintf (outfulltable, "WJetsToLNu              & %3.1f \\\\\n", int_WJetsToLNu             ) ; 
       fprintf (outfulltable, " \\hline \n");
       fprintf (outfulltable, "WG                      & %3.1f \\\\\n", int_WG                     ) ; 
       fprintf (outfulltable, "ZG                      & %3.1f \\\\\n", int_ZG                     ) ; 
       fprintf (outfulltable, " \\hline \n");
       fprintf (outfulltable, "WW                      & %3.1f \\\\\n", int_WW                     ) ; 
       fprintf (outfulltable, "WZ                      & %3.1f \\\\\n", int_WZ                     ) ; 
       fprintf (outfulltable, "ZZ                      & %3.1f \\\\\n", int_ZZ                     ) ; 
       fprintf (outfulltable, " \\hline \n");
       fprintf (outfulltable, "WWTo2L2Nu               & %3.1f \\\\\n", int_WWTo2L2Nu              ) ; 
       fprintf (outfulltable, "WWToLNuQQ               & %3.1f \\\\\n", int_WWToLNuQQ              ) ; 
       fprintf (outfulltable, "WZTo1L3Nu               & %3.1f \\\\\n", int_WZTo1L3Nu              ) ; 
       fprintf (outfulltable, "WZTo3LNu                & %3.1f \\\\\n", int_WZTo3LNu               ) ; 
       fprintf (outfulltable, "WZToLNu2QorQQ2L         & %3.1f \\\\\n", int_WZToLNu2QorQQ2L        ) ; 
       fprintf (outfulltable, "ZZTo2L2Nu               & %3.1f \\\\\n", int_ZZTo2L2Nu              ) ; 
       fprintf (outfulltable, "ZZTo2L2Q                & %3.1f \\\\\n", int_ZZTo2L2Q               ) ; 
       fprintf (outfulltable, "ZZTo2Q2Nu               & %3.1f \\\\\n", int_ZZTo2Q2Nu              ) ; 
       fprintf (outfulltable, "ZZTo4L                  & %3.1f \\\\\n", int_ZZTo4L                 ) ; 
       fprintf (outfulltable, " \\hline \n");

       fprintf (outfulltable, "Sig ZH MS15ct1000       & %3.1f \\\\\n", int_Sig_ZH_MS15ct1000      ) ; 
       fprintf (outfulltable, "Sig ZH MS15ct100        & %3.1f \\\\\n", int_Sig_ZH_MS15ct100       ) ; 
       fprintf (outfulltable, "Sig ZH MS15ct10         & %3.1f \\\\\n", int_Sig_ZH_MS15ct10        ) ; 
       fprintf (outfulltable, "Sig ZH MS15ct1          & %3.1f \\\\\n", int_Sig_ZH_MS15ct1         ) ; 
       fprintf (outfulltable, "Sig ZH MS40ct1000       & %3.1f \\\\\n", int_Sig_ZH_MS40ct1000      ) ; 
       fprintf (outfulltable, "Sig ZH MS40ct100        & %3.1f \\\\\n", int_Sig_ZH_MS40ct100       ) ; 
       fprintf (outfulltable, "Sig ZH MS40ct10         & %3.1f \\\\\n", int_Sig_ZH_MS40ct10        ) ; 
       fprintf (outfulltable, "Sig ZH MS40ct1          & %3.1f \\\\\n", int_Sig_ZH_MS40ct1         ) ; 
       fprintf (outfulltable, "Sig ZH MS55ct1000       & %3.1f \\\\\n", int_Sig_ZH_MS55ct1000      ) ; 
       fprintf (outfulltable, "Sig ZH MS55ct100        & %3.1f \\\\\n", int_Sig_ZH_MS55ct100       ) ; 
       fprintf (outfulltable, "Sig ZH MS55ct10         & %3.1f \\\\\n", int_Sig_ZH_MS55ct10        ) ; 
       fprintf (outfulltable, "Sig ZH MS55ct1          & %3.1f \\\\\n", int_Sig_ZH_MS55ct1         ) ; 
       fprintf (outfulltable, " \\hline \n");

       fprintf (outfulltable, "Sig ggZH MS15ct1000     & %3.1f \\\\\n", int_Sig_ggZH_MS15ct1000    ) ; 
       fprintf (outfulltable, "Sig ggZH MS15ct100      & %3.1f \\\\\n", int_Sig_ggZH_MS15ct100     ) ; 
       fprintf (outfulltable, "Sig ggZH MS15ct10       & %3.1f \\\\\n", int_Sig_ggZH_MS15ct10      ) ; 
       fprintf (outfulltable, "Sig ggZH MS15ct1        & %3.1f \\\\\n", int_Sig_ggZH_MS15ct1       ) ; 
       fprintf (outfulltable, "Sig ggZH MS40ct1000     & %3.1f \\\\\n", int_Sig_ggZH_MS40ct1000    ) ; 
       fprintf (outfulltable, "Sig ggZH MS40ct100      & %3.1f \\\\\n", int_Sig_ggZH_MS40ct100     ) ; 
       fprintf (outfulltable, "Sig ggZH MS40ct10       & %3.1f \\\\\n", int_Sig_ggZH_MS40ct10      ) ; 
       fprintf (outfulltable, "Sig ggZH MS40ct1        & %3.1f \\\\\n", int_Sig_ggZH_MS40ct1       ) ; 
       fprintf (outfulltable, "Sig ggZH MS55ct1000     & %3.1f \\\\\n", int_Sig_ggZH_MS55ct1000    ) ; 
       fprintf (outfulltable, "Sig ggZH MS55ct100      & %3.1f \\\\\n", int_Sig_ggZH_MS55ct100     ) ; 
       fprintf (outfulltable, "Sig ggZH MS55ct10       & %3.1f \\\\\n", int_Sig_ggZH_MS55ct10      ) ; 
       fprintf (outfulltable, "Sig ggZH MS55ct1        & %3.1f \\\\\n", int_Sig_ggZH_MS55ct1       ) ; 
       fprintf (outfulltable, " \\hline \n");
       /*
       fprintf (outfulltable, "Data SingleMu H 3       & %3.1f \\\\\n", int_Data_SingleMu_H_3      ) ; 
       fprintf (outfulltable, "Data SingleMu H 2       & %3.1f \\\\\n", int_Data_SingleMu_H_2      ) ; 
       fprintf (outfulltable, "Data SingleMu G         & %3.1f \\\\\n", int_Data_SingleMu_G        ) ; 
  //   fprintf (outfulltable, "Data SingleMu F         & %3.1f \\\\\n", int_Data_SingleMu_F        ) ; 
  //   fprintf (outfulltable, "Data SingleMu E         & %3.1f \\\\\n", int_Data_SingleMu_E        ) ; 
  //   fprintf (outfulltable, "Data SingleMu D         & %3.1f \\\\\n", int_Data_SingleMu_D        ) ; 
  //   fprintf (outfulltable, "Data SingleMu C         & %3.1f \\\\\n", int_Data_SingleMu_C        ) ; 
  //   fprintf (outfulltable, "Data SingleMu B 2       & %3.1f \\\\\n", int_Data_SingleMu_B_2      ) ; 
       fprintf (outfulltable, "Data SingleEle H 3      & %3.1f \\\\\n", int_Data_SingleEle_H_3     ) ; 
       fprintf (outfulltable, "Data SingleEle H 2      & %3.1f \\\\\n", int_Data_SingleEle_H_2     ) ; 
       fprintf (outfulltable, "Data SingleEle G        & %3.1f \\\\\n", int_Data_SingleEle_G       ) ; 
  //   fprintf (outfulltable, "Data SingleEle F        & %3.1f \\\\\n", int_Data_SingleEle_F       ) ; 
  //   fprintf (outfulltable, "Data SingleEle E        & %3.1f \\\\\n", int_Data_SingleEle_E       ) ; 
  //   fprintf (outfulltable, "Data SingleEle D        & %3.1f \\\\\n", int_Data_SingleEle_D       ) ; 
  //   fprintf (outfulltable, "Data SingleEle C        & %3.1f \\\\\n", int_Data_SingleEle_C       ) ; 
  //   fprintf (outfulltable, "Data SingleEle B 2      & %3.1f \\\\\n", int_Data_SingleEle_B_2     ) ; 
  */
       fprintf (outfulltable, "Data SinglePhoton H 3   & %3.1f \\\\\n", int_Data_SinglePhoton_H_3  ) ; 
       fprintf (outfulltable, "Data SinglePhoton H 2   & %3.1f \\\\\n", int_Data_SinglePhoton_H_2  ) ; 
       fprintf (outfulltable, "Data SinglePhoton G     & %3.1f \\\\\n", int_Data_SinglePhoton_G    ) ; 
  //   fprintf (outfulltable, "Data SinglePhoton F     & %3.1f \\\\\n", int_Data_SinglePhoton_F    ) ; 
  //   fprintf (outfulltable, "Data SinglePhoton E     & %3.1f \\\\\n", int_Data_SinglePhoton_E    ) ; 
  //   fprintf (outfulltable, "Data SinglePhoton D     & %3.1f \\\\\n", int_Data_SinglePhoton_D    ) ; 
  //   fprintf (outfulltable, "Data SinglePhoton C     & %3.1f \\\\\n", int_Data_SinglePhoton_C    ) ; 
  //   fprintf (outfulltable, "Data SinglePhoton B 2   & %3.1f \\\\\n", int_Data_SinglePhoton_B_2  ) ; 
       fprintf (outfulltable, "Data DoubleMu H 3       & %3.1f \\\\\n", int_Data_DoubleMu_H_3      ) ; 
       fprintf (outfulltable, "Data DoubleMu H 2       & %3.1f \\\\\n", int_Data_DoubleMu_H_2      ) ; 
       fprintf (outfulltable, "Data DoubleMu G         & %3.1f \\\\\n", int_Data_DoubleMu_G        ) ; 
//     fprintf (outfulltable, "Data DoubleMu F         & %3.1f \\\\\n", int_Data_DoubleMu_F        ) ; 
//     fprintf (outfulltable, "Data DoubleMu E         & %3.1f \\\\\n", int_Data_DoubleMu_E        ) ; 
//     fprintf (outfulltable, "Data DoubleMu D         & %3.1f \\\\\n", int_Data_DoubleMu_D        ) ; 
//     fprintf (outfulltable, "Data DoubleMu C         & %3.1f \\\\\n", int_Data_DoubleMu_C        ) ; 
//     fprintf (outfulltable, "Data DoubleMu B 2       & %3.1f \\\\\n", int_Data_DoubleMu_B_2      ) ; 
       fprintf (outfulltable, " \\hline \n");
       fprintf (outfulltable, "Data DoubleEG H 3       & %3.1f \\\\\n", int_Data_DoubleEG_H_3      ) ; 
       fprintf (outfulltable, "Data DoubleEG H 2       & %3.1f \\\\\n", int_Data_DoubleEG_H_2      ) ; 
       fprintf (outfulltable, "Data DoubleEG G         & %3.1f \\\\\n", int_Data_DoubleEG_G        ) ; 
//     fprintf (outfulltable, "Data DoubleEG F         & %3.1f \\\\\n", int_Data_DoubleEG_F        ) ; 
//     fprintf (outfulltable, "Data DoubleEG E         & %3.1f \\\\\n", int_Data_DoubleEG_E        ) ; 
//     fprintf (outfulltable, "Data DoubleEG D         & %3.1f \\\\\n", int_Data_DoubleEG_D        ) ; 
//     fprintf (outfulltable, "Data DoubleEG C         & %3.1f \\\\\n", int_Data_DoubleEG_C        ) ; 
//     fprintf (outfulltable, "Data DoubleEG B 2       & %3.1f \\\\\n", int_Data_DoubleEG_B_2      ) ; 
       fprintf (outfulltable, " \\hline \n");

       //fprintf (outfulltable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS10000  & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS10000 ) ;
       fprintf (outfulltable, "\\end{tabular}\n\n");
       fprintf (outfulltable, "\\end{document}\n\n");
      fclose (outfulltable);

      FILE * summarytable;
      summarytable = fopen (smalllogname+".tex","w");
       fprintf (summarytable, "\\documentclass{standalone}\n\n");
       fprintf (summarytable, "\\begin{document}\n\n");
       fprintf (summarytable, "\\begin{tabular}{rl}\n\n");
       //fprintf (summarytable, " \\Huge %s & \\Huge %s   \\\\\n", lepton.Data(), region.Data()); 
       fprintf (summarytable, " \\Huge %s   \\\\\n", region.Data()); 
       fprintf (summarytable, " \\hline \n");
       fprintf (summarytable, "\\Large  Backgrounds \\\\\n");
       fprintf (summarytable, " \\hline \n");
       fprintf (summarytable, "DY              & %3.1f \\\\\n", int_DY             ) ; 
       fprintf (summarytable, "altDY           & %3.1f \\\\\n", int_altDY          ) ; 
       fprintf (summarytable, "GJets           & %3.1f \\\\\n", int_GJets          ) ; 
       fprintf (summarytable, "ST              & %3.1f \\\\\n", int_ST             ) ; 
       fprintf (summarytable, "ZH              & %3.1f \\\\\n", int_ZH             ) ; 
       fprintf (summarytable, "VV              & %3.1f \\\\\n", int_VV             ) ; 
       fprintf (summarytable, "altVV           & %3.1f \\\\\n", int_altVV          ) ; 
       fprintf (summarytable, "TT              & %3.1f \\\\\n", int_TT             ) ; 
       fprintf (summarytable, "altTT           & %3.1f \\\\\n", int_altTT          ) ; 
       fprintf (summarytable, "VG              & %3.1f \\\\\n", int_VG             ) ; 
       fprintf (summarytable, "QCD             & %3.1f \\\\\n", int_QCD            ) ; 
       fprintf (summarytable, " \\hline \n");
       fprintf (summarytable, "Sig MS15ct1000  & %3.1f \\\\\n", int_Sig_MS15ct1000 ) ; 
       fprintf (summarytable, "Sig MS15ct100   & %3.1f \\\\\n", int_Sig_MS15ct100  ) ; 
       fprintf (summarytable, "Sig MS15ct10    & %3.1f \\\\\n", int_Sig_MS15ct10   ) ; 
       fprintf (summarytable, "Sig MS15ct1     & %3.1f \\\\\n", int_Sig_MS15ct1    ) ; 
       fprintf (summarytable, "Sig MS40ct1000  & %3.1f \\\\\n", int_Sig_MS40ct1000 ) ; 
       fprintf (summarytable, "Sig MS40ct100   & %3.1f \\\\\n", int_Sig_MS40ct100  ) ; 
       fprintf (summarytable, "Sig MS40ct10    & %3.1f \\\\\n", int_Sig_MS40ct10   ) ; 
       fprintf (summarytable, "Sig MS40ct1     & %3.1f \\\\\n", int_Sig_MS40ct1    ) ; 
       fprintf (summarytable, "Sig MS55ct1000  & %3.1f \\\\\n", int_Sig_MS55ct1000 ) ; 
       fprintf (summarytable, "Sig MS55ct100   & %3.1f \\\\\n", int_Sig_MS55ct100  ) ; 
       fprintf (summarytable, "Sig MS55ct10    & %3.1f \\\\\n", int_Sig_MS55ct10   ) ; 
       fprintf (summarytable, "Sig MS55ct1     & %3.1f \\\\\n", int_Sig_MS55ct1    ) ; 
       fprintf (summarytable, "Total Backgrounds    & %3.1f \\\\\n", int_bkgtotal ) ; 
       fprintf (summarytable, " \\hline \n");
       fprintf (summarytable, "Data                 & %3.1f  \\\\\n", int_Data   ) ;
       fprintf (summarytable, " \\hline \n");
       fprintf (summarytable, "Backgrounds / Data   & %3.4f  \\\\\n", int_bkgOnData   ) ;
       fprintf (summarytable, "\\end{tabular}\n\n");
       fprintf (summarytable, "\\end{document}\n\n");
      fclose (summarytable);

      FILE * tinytable;
      tinytable = fopen (tinylogname+".tex","w");
       fprintf (tinytable, "\\documentclass{standalone}\n\n");
       fprintf (tinytable, "\\begin{document}\n\n");
       fprintf (tinytable, "\\begin{tabular}{rl}\n\n");
       //fprintf (tinytable, " \\Huge %s & \\Huge %s   \\\\\n", lepton.Data(), region.Data()); 
       fprintf (tinytable, " \\Huge %s   \\\\\n", region.Data()); 
       fprintf (tinytable, " \\hline \n");
       fprintf (tinytable, "\\Large  Backgrounds \\\\\n");
       fprintf (tinytable, " \\hline \n");
       fprintf (tinytable, "Drell-Yan       & %3.1f \\\\\n", int_DY             ) ; 
       fprintf (tinytable, "$\\gamma$+jets     & %3.1f \\\\\n", int_GJets          ) ; 
       fprintf (tinytable, "single top      & %3.1f \\\\\n", int_ST             ) ; 
       fprintf (tinytable, "ZH(bb)          & %3.1f \\\\\n", int_ZH             ) ; 
       fprintf (tinytable, "WW,WZ,ZZ & %3.1f \\\\\n", int_VV             ) ; 
       fprintf (tinytable, "$t\\bar{t}$      & %3.1f \\\\\n", int_TT             ) ; 
       fprintf (tinytable, "V$\\gamma$              & %3.1f \\\\\n", int_VG             ) ; 
       fprintf (tinytable, "QCD              & %3.1f \\\\\n", int_QCD             ) ; 
       fprintf (tinytable, " \\hline \n");
       fprintf (tinytable, "Total Backgrounds    & %3.1f \\\\\n", int_bkgtotal ) ; 
       fprintf (tinytable, " \\hline \n");
       fprintf (tinytable, "Data                 & %3.1f  \\\\\n", int_Data   ) ;
       fprintf (tinytable, " \\hline \n");
       fprintf (tinytable, "Backgrounds / Data   & %3.4f  \\\\\n", int_bkgOnData   ) ;
       fprintf (tinytable, "\\end{tabular}\n\n");
       fprintf (tinytable, "\\end{document}\n\n");
      fclose (tinytable);
     }

     // set attributes
     h_DY         -> SetLineColor(kBlack); 
     h_altDY      -> SetLineColor(kBlack); 
     h_GJets      -> SetLineColor(kBlack);
     h_ST         -> SetLineColor(kBlack); 
     h_TT         -> SetLineColor(kBlack); 
     h_altTT      -> SetLineColor(kBlack); 
     h_WJetsToLNu -> SetLineColor(kBlack); 
     h_VV         -> SetLineColor(kBlack); 
     h_altVV      -> SetLineColor(kBlack); 
     h_VG         -> SetLineColor(kBlack); 
     h_QCD        -> SetLineColor(kBlack); 
     h_ZH         -> SetLineColor(kBlack);

     h_Data  -> SetLineColor(kBlack);
     h_Data  -> SetMarkerStyle(8);
     h_Data  -> SetMarkerSize(1);
     h_Data  -> SetLineWidth(3);

     h_DY        ->SetFillStyle(1001);
     h_altDY     ->SetFillStyle(1001);
     h_GJets     ->SetFillStyle(1001);
     h_ST        ->SetFillStyle(1001);
     h_TT        ->SetFillStyle(1001);
     h_altTT     ->SetFillStyle(1001);
     h_WJetsToLNu->SetFillStyle(1001);
     h_VV        ->SetFillStyle(1001);
     h_altVV     ->SetFillStyle(1001);
     h_VG        ->SetFillStyle(1001);
     h_QCD       ->SetFillStyle(1001);
     h_ZH        ->SetFillStyle(1001);

     h_DY        ->SetFillColor(kAzure-3);
     h_altDY     ->SetFillColor(kAzure-3);
     h_GJets     ->SetFillColor(kViolet+3);
     h_ST        ->SetFillColor(kOrange+8);
     h_TT        ->SetFillColor(kGreen+1);
     h_altTT     ->SetFillColor(kGreen+1);
     h_WJetsToLNu->SetFillColor(kViolet-3);
     h_VV        ->SetFillColor(kRed);
     h_altVV     ->SetFillColor(kRed);
     h_VG        ->SetFillColor(kPink+9);
     h_QCD       ->SetFillColor(kGray+1);
     h_ZH        ->SetFillColor(kCyan);

     h_DY        ->SetLineColor(kBlack); 
     h_altDY     ->SetLineColor(kBlack); 
     h_GJets     ->SetLineColor(kBlack); 
     h_ST        ->SetLineColor(kBlack); 
     h_TT        ->SetLineColor(kBlack); 
     h_altTT     ->SetLineColor(kBlack); 
     h_WJetsToLNu->SetLineColor(kBlack); 
     h_VV        ->SetLineColor(kBlack); 
     h_altVV     ->SetLineColor(kBlack); 
     h_VG        ->SetLineColor(kBlack); 
     h_QCD       ->SetLineColor(kBlack); 
     h_ZH        ->SetLineColor(kBlack); 

     h_DY        ->SetLineWidth(2);
     h_altDY     ->SetLineWidth(2);
     h_GJets     ->SetLineWidth(2);
     h_ST        ->SetLineWidth(2);
     h_TT        ->SetLineWidth(2);
     h_altTT     ->SetLineWidth(2);
     h_WJetsToLNu->SetLineWidth(2);
     h_VV        ->SetLineWidth(2);
     h_altVV     ->SetLineWidth(2);
     h_VG        ->SetLineWidth(2);
     h_QCD       ->SetLineWidth(2);
     h_ZH        ->SetLineWidth(2);

     h_bkgtotal->SetFillColorAlpha(kYellow+1, 0.7);
     h_bkgtotal->SetFillStyle(1001);

     std::vector<TH1F *> v;
     if(useAlt){
       v.push_back(h_altDY);
       v.push_back(h_GJets);
       v.push_back(h_ST);
       v.push_back(h_altTT);
       v.push_back(h_WJetsToLNu);
       v.push_back(h_altVV);
       v.push_back(h_VG); 
       v.push_back(h_QCD); 
       v.push_back(h_ZH);
     }
     else {
       v.push_back(h_DY);
       v.push_back(h_GJets);
       v.push_back(h_ST);
       v.push_back(h_TT);
       v.push_back(h_WJetsToLNu);
       v.push_back(h_VV);
       v.push_back(h_VG); 
       v.push_back(h_QCD); 
       v.push_back(h_ZH);
     }

     // make stack
     THStack *bgstack = new THStack("bgstack","");
     if(dolog){
      std::sort(v.begin(), v.end(),
                [](TH1F *a, TH1F *b) { return a->Integral() < b->Integral(); });
      for(int zz=0; zz<v.size(); zz++)
      {
       bgstack->Add(v[zz]);
       //cout <<v[zz]->Integral()<<std::endl;
      }
     }
     else{
       if(useAlt){
         bgstack->Add(h_altDY      ); 
         bgstack->Add(h_GJets      );
         bgstack->Add(h_ST         ); 
         bgstack->Add(h_altTT      ); 
         bgstack->Add(h_WJetsToLNu ); 
         bgstack->Add(h_altVV      ); 
         bgstack->Add(h_VG         );
         bgstack->Add(h_QCD        );
         bgstack->Add(h_ZH         );
       }
       else {
         bgstack->Add(h_DY         ); 
         bgstack->Add(h_GJets      );
         bgstack->Add(h_ST         ); 
         bgstack->Add(h_TT         ); 
         bgstack->Add(h_WJetsToLNu ); 
         bgstack->Add(h_VV         ); 
         bgstack->Add(h_VG         );
         bgstack->Add(h_QCD        );
         bgstack->Add(h_ZH         );
       }
     }

//     if( h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1) > 0.1){ ;
//        h_ggZH_HToSSTobbbb_MS40_ctauS0      ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1));
//     }                                     
//     if( h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1) > 0.1){ ;
//        h_ggZH_HToSSTobbbb_MS40_ctauS0p05   ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1));  
//     }                                     
//     if( h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1) > 0.1){ ;
//        h_ggZH_HToSSTobbbb_MS40_ctauS1      ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1)); 
//     }                                     
//     if( h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1) > 0.1){ ;
//        h_ggZH_HToSSTobbbb_MS40_ctauS10     ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1)); 
//     }                                     
//     if( h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1) > 0.1){ ;
//        h_ggZH_HToSSTobbbb_MS40_ctauS100    ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1));   
//     }                                     
//     if( h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1) > 0.1){ ;
//        h_ggZH_HToSSTobbbb_MS40_ctauS1000   ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1));  
//     }                                     
//     if( h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) > 0.1){ ;
//        h_ggZH_HToSSTobbbb_MS40_ctauS10000  ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) ); 
//     }

     // make legend
     TLegend *leg;
     leg = new TLegend(0.2,0.7,0.88,0.88);
     leg->SetBorderSize(0);
     leg->SetNColumns(2);
     leg->SetFillColor(kWhite);
     if(useAlt){
       leg->AddEntry(h_Data         , "Data", "lpe"); 
       leg->AddEntry(h_altDY        , "(Alt.) Drell-Yan", "f"); 
       leg->AddEntry(h_GJets        , "#gamma+Jets", "f"); 
       leg->AddEntry(h_ST           , "Single Top", "f"); 
       leg->AddEntry(h_altTT        , "(Alt.) t#bar{t}+Jets", "f"); 
       leg->AddEntry(h_WJetsToLNu   , "W+Jets", "f"); 
       leg->AddEntry(h_altVV        , "(Alt.) Diboson", "f"); 
       leg->AddEntry(h_VG           , "V#gamma", "f");
       leg->AddEntry(h_QCD          , "QCD", "f");
       leg->AddEntry(h_ZH           , "ZH#rightarrowLLbb", "f");
       leg->AddEntry(h_bkgtotal     , "MC bkg. stat. err.", "f");
     }
     else {
       leg->AddEntry(h_Data         , "Data", "lpe"); 
       leg->AddEntry(h_DY           , "Drell-Yan", "f"); 
       leg->AddEntry(h_GJets        , "#gamma+Jets", "f"); 
       leg->AddEntry(h_ST           , "Single Top", "f"); 
       leg->AddEntry(h_TT           , "t#bar{t}+Jets", "f"); 
       leg->AddEntry(h_WJetsToLNu   , "W+Jets", "f"); 
       leg->AddEntry(h_VV           , "Diboson", "f"); 
       leg->AddEntry(h_VG           , "V#gamma", "f");
       leg->AddEntry(h_QCD          , "QCD", "f");
       leg->AddEntry(h_ZH           , "ZH#rightarrowLLbb", "f");
       leg->AddEntry(h_bkgtotal     , "MC bkg. stat. err.", "f");
     }

      TLegend *sigleg = new TLegend(0.15,0.6,0.65,0.85);
    //if(drawSignal){
      //sigleg->SetBorderSize(0);
      //sigleg->SetFillColor(kWhite);
      //sigleg->SetHeader("Z(H#rightarrow SS#rightarrow bbbb)","C");
      //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0     , "M_{S}=40 c#tau_{S}=0    ", "l" ) ;
      //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0p05  , "M_{S}=40 c#tau_{S}=0p05 ", "l" ) ;
      //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1     , "M_{S}=40 c#tau_{S}=1    ", "l" ) ;
      //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10    , "M_{S}=40 c#tau_{S}=10   ", "l" ) ;
      //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS100   , "M_{S}=40 c#tau_{S}=100  ", "l" ) ;
      //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1000  , "M_{S}=40 c#tau_{S}=1000 ", "l" ) ;
      //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10000 , "M_{S}=40 c#tau_{S}=10000", "l" ) ;
     //}

     // set max and draw
     Double_t ymax;
     ymax = std::max(h_Data->GetMaximum(), h_bkgtotal->GetMaximum() );
     
     if(dolog){
      bgstack->SetMaximum(500*ymax); 
      bgstack->SetMinimum(1.0e-6);
     } 
     else {
      bgstack->SetMaximum(ymax*1.4);
     }
      
     plotpad->cd();
     bgstack->Draw("hist");
     //bgstack->Draw("hist e");
     bgstack->GetYaxis()->SetTitle("Events");
     //bgstack->GetYaxis()->SetTitleOffset(1.85);
     bgstack->GetYaxis()->SetTitleSize(40);
     bgstack->GetYaxis()->SetTitleFont(43);
     bgstack->GetYaxis()->SetTitleOffset(1.75);
     bgstack->GetXaxis()->SetTitle(varname + "    "+description);
     if(!drawData){
       bgstack->GetXaxis()->SetTitleSize(40);
       bgstack->GetXaxis()->SetTitleFont(43);
       bgstack->GetXaxis()->SetTitle(varname + "    "+description);
       bgstack->GetXaxis()->SetTitleOffset(4.0);
       bgstack->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
       bgstack->GetXaxis()->SetLabelSize(20);//20
     }
     //h_bkgtotal->Draw("e2 sames");
     if(drawData){
       h_Data->Draw("sames E"); 
     }

//     if(drawSignal){
//      h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Draw("hist sames") ;
//      h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Draw("hist sames") ;
//      h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Draw("hist sames") ;
//      h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Draw("hist sames") ;
//      h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Draw("hist sames") ;
//      h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Draw("hist sames") ;
//      h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Draw("hist sames") ;
//      sigleg->Draw();
//     }
     leg->Draw();

     char lumistring [50];
     int dummy; 

     // add titles
     title->DrawTextNDC(0.2,0.91,"CMS");
     extra->DrawTextNDC(0.3,0.91,"Preliminary");
     if(HIP){
      extra2->DrawTextNDC(0.51,0.91,"Eras B-F");
      dummy=sprintf (lumistring, "%0.1f", lumiBCDEF/1000.);
     }
     else{
      extra2->DrawTextNDC(0.51,0.91,"Eras GH");
      dummy=sprintf (lumistring, "%0.1f", lumiGH/1000.);
     }
     //lumi->DrawTextNDC(0.9,0.91,"35.9 /fb (13 TeV)");
     lumi->DrawTextNDC(0.9,0.91,(TString)lumistring+" /fb (13 TeV)");
     
     if(drawData){
       ratiopad->cd();
       h_ratio = (TH1F*)h_Data->Clone("ratio");
       if(h_Data->Integral(-1,-1)>0){
	 h_ratio->Divide(h_bkgtotal);
       }
       h_ratio->SetTitle(" ");
       // Y axis ratio plot settings
       h_ratio->GetYaxis()->SetTitleSize(40);
       h_ratio->GetYaxis()->SetTitleFont(43);
       h_ratio->GetYaxis()->SetTitleOffset(1.55);
       h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
       h_ratio->GetYaxis()->SetLabelSize(20);
       h_ratio->GetYaxis()->SetNdivisions(-105);
       h_ratio->GetYaxis()->SetTitle("Data/MC");
       // X axis ratio plot settings
       h_ratio->GetXaxis()->SetTitleSize(40);
       h_ratio->GetXaxis()->SetTitleFont(43);
       h_ratio->GetXaxis()->SetTitle((TString)h_Data->GetTitle()+description);
       h_ratio->GetXaxis()->SetTitleOffset(4.0);
       h_ratio->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
       h_ratio->GetXaxis()->SetLabelSize(20);//20
       h_ratio->SetMarkerStyle(20);
       h_ratio->SetMarkerColor(kRed);
       h_ratio->SetMarkerSize(1);
       h_ratio->GetYaxis()->SetRangeUser(0.4,1.6);
       h_ratio->Draw("ep");  // draw first to get ranges set internally inside root
              
       h_ratiostaterr = (TH1F*)h_bkgtotal->Clone("ratiostaterr");
       h_ratiostaterr->Divide(h_bkgtotal);
       
       ratiopad->Update();       // need to update pad to get X min/max
       TLine *line = new TLine(ratiopad->GetUxmin(),1,ratiopad->GetUxmax(),1);
       line->SetLineColor(kBlue);
       line->SetLineWidth(3);
       line->SetLineStyle(9);
       h_ratiostaterr->Draw("e2 same");

       line->Draw();
       h_ratio->Draw("ep same"); // draw points above line
     }
     else{
       ratiopad->Clear();
     }

     // save canvas
     canvas->SaveAs(outname+description+".png");
     canvas->SaveAs(outname+description+".pdf");
  
     // save histograms into single root file
     TFile *outfile = TFile::Open(outname+".root","RECREATE");
     h_Data        ->Write();
     h_DY          ->Write();
     h_GJets       ->Write();
     h_ST          ->Write();
     h_TT          ->Write();
     h_WJetsToLNu  ->Write();
     h_VV          ->Write();
     h_VG          ->Write();
     h_QCD         ->Write();
     h_ZH          ->Write();
     h_bkgtotal    ->Write();
     h_light       ->Write();
     h_light_alt   ->Write();
     h_heavy       ->Write();
     h_heavy_alt   ->Write();
     h_other       ->Write();
     h_other_alt   ->Write();
     if( drawData ){
      h_ratio       ->Write();
      h_ratiostaterr->Write();
     }
     bgstack       ->Write();
     
     h_altDY          ->Write(); 
     h_altVV          ->Write(); 
     h_altTT          ->Write(); 
     h_Sig_MS15ct1000 ->Write(); 
     h_Sig_MS15ct100  ->Write(); 
     h_Sig_MS15ct10   ->Write(); 
     h_Sig_MS15ct1    ->Write(); 
     h_Sig_MS40ct1000 ->Write(); 
     h_Sig_MS40ct100  ->Write(); 
     h_Sig_MS40ct10   ->Write(); 
     h_Sig_MS40ct1    ->Write(); 
     h_Sig_MS55ct1000 ->Write(); 
     h_Sig_MS55ct100  ->Write(); 
     h_Sig_MS55ct10   ->Write(); 
     h_Sig_MS55ct1    ->Write(); 
     
     outfile->Close();
     std::cout<<" closed writing:\n  "<<outname<<std::endl;
     
   } 
  }
  
}
