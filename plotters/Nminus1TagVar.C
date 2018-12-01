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

void Nminus1TagVar(TString sel, Bool_t dolog){
vector<TString> FileList;

//TString sel = "L";

TString treeName;
//treeName= "NM1";        // TwoMuDY
treeName= "NM1CRHeavy"; // CRHeavy
//treeName= "NM1CRLight"; // CRLight
//treeName= "NM1MuZH";    // MuZH
//treeName= "NM1EleZH";   // EleZH

TString DataName ;
if     (treeName == "NM1"       ) DataName= "DoubleMu";
else if(treeName == "NM1CRHeavy") DataName= "MuonEG";
else if(treeName == "NM1CRLight") DataName= "SinglePhoton";
else if(treeName == "NM1MuZH"   ) DataName= "DoubleMu";
else if(treeName == "NM1EleZH"  ) DataName= "DoubleEG";
else{}

TString regionName ;
if     (treeName == "NM1"       ) regionName= "Drell-Yan";
else if(treeName == "NM1CRHeavy") regionName= "CRHeavy";
else if(treeName == "NM1CRLight") regionName= "CRLight";
else if(treeName == "NM1MuZH"   ) regionName= "MuZH";
else if(treeName == "NM1EleZH"  ) regionName= "EleZH";
else{}

TString plots = TString(getenv("plotdir"));
TString aversion = TString(getenv("aversion"));
TString outpath = plots+"/";
TString inpath  = "../roots/";
inpath = inpath+aversion+"/";
outpath = outpath+aversion+"/";
float c_ip =  1.15;
float c_ta = -1.75;
float c_al =  0.75;

//-----------------------------------------Canvas stuff
 // make canvas and text
 //TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 TCanvas* canvas = new TCanvas("canvas","canvas",1100,1200);//1280,1024);
 canvas->Clear();
 canvas->cd();
 canvas->SetGrid();
 TPad *pad  = new TPad("pad", "pad", 0, 0.25, 1, 1);
 gStyle->SetOptStat(0);
 pad->SetLogy(dolog);
 pad->SetTickx();
 pad->SetTicky();
 pad->Draw();
 pad->SetGrid();
 pad->cd();
 //gStyle->SetLineWidth(3);
 //gStyle->SetPalette(kBird);
 canvas->cd();
 TPad *rpad = new TPad("ratiopad","ratiopad", 0, 0 ,1, 0.25);
 rpad->SetGrid();
 rpad->Draw(); 
 canvas->cd();

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.04);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.04);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 extra->SetTextFont(52);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.03);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);
//-----------------------------------------End Canvas stuff

//Add files
//SigFileList.push_back  ( inpath+"ggZH_HToSSTobbbb_ZToLL_MH-125_"+mass+"_"+lifetime+"_NM1tree.root");
/*SigFileList.push_back  ( inpath+"ZH_HToSSTobbbb_ZToLL_MH-125_"+mass+"_"  +lifetime+"_OPTtree.root");
*/
FileList.push_back( inpath+"DYJetsToLL_M-50_NM1tree.root"                        ); //i=0
FileList.push_back( inpath+"DYJetsToLL_M-5to50_HT-100to200_NM1tree.root"         ); //i=1
FileList.push_back( inpath+"DYJetsToLL_M-5to50_HT-200to400_NM1tree.root"         ); //i=2
FileList.push_back( inpath+"DYJetsToLL_M-5to50_HT-400to600_NM1tree.root"         ); //i=3
FileList.push_back( inpath+"DYJetsToLL_M-5to50_HT-600toInf_NM1tree.root"         ); //i=4
//ttbar
FileList.push_back( inpath+"TTJets_NM1tree.root"                                 ); //i=5
//W+Jets
FileList.push_back( inpath+"WJetsToLNu_NM1tree.root"                             ); //i=6
//single-top
FileList.push_back( inpath+"ST_s-channel_4f_leptonDecays_NM1tree.root"           ); //i=7
FileList.push_back( inpath+"ST_t-channel_antitop_4f_inclusiveDecays_NM1tree.root"); //i=8
FileList.push_back( inpath+"ST_t-channel_top_4f_inclusiveDecays_NM1tree.root"    ); //i=9
FileList.push_back( inpath+"ST_tW_antitop_5f_NoFullyHadronicDecays_NM1tree.root" ); //i=10
FileList.push_back( inpath+"ST_tW_top_5f_NoFullyHadronicDecays_NM1tree.root"     ); //i=11
//CRLight
FileList.push_back( inpath+"GJets_HT-40To100_NM1tree.root"                       ); //i=12
FileList.push_back( inpath+"GJets_HT-100To200_NM1tree.root"                      ); //i=13
FileList.push_back( inpath+"GJets_HT-200To400_NM1tree.root"                      ); //i=14
FileList.push_back( inpath+"GJets_HT-400To600_NM1tree.root"                      ); //i=15
FileList.push_back( inpath+"GJets_HT-600ToInf_NM1tree.root"                      ); //i=16
//diboson
FileList.push_back( inpath+"WW_NM1tree.root"                                     ); //i=17
FileList.push_back( inpath+"WZ_NM1tree.root"                                     ); //i=18
FileList.push_back( inpath+"ZZ_NM1tree.root"                                     ); //i=19
//VG
FileList.push_back( inpath+"WGToLNuG_NM1tree.root"                               ); //i=20
FileList.push_back( inpath+"ZGTo2LG_NM1tree.root"                                ); //i=21
//SM Higgs decays
FileList.push_back( inpath+"ggZH_HToBB_ZToLL_NM1tree.root"                       ); //i=22
FileList.push_back( inpath+"ZH_HToBB_ZToLL_NM1tree.root"                         ); //i=23

FileList.push_back( inpath+"QCD_HT100to200_NM1tree.root"                         ); //i=24
FileList.push_back( inpath+"QCD_HT200to300_NM1tree.root"                         ); //i=25
FileList.push_back( inpath+"QCD_HT300to500_NM1tree.root"                         ); //i=26
FileList.push_back( inpath+"QCD_HT500to700_NM1tree.root"                         ); //i=27
FileList.push_back( inpath+"QCD_HT700to1000_NM1tree.root"                        ); //i=28
FileList.push_back( inpath+"QCD_HT1000to1500_NM1tree.root"                       ); //i=29
FileList.push_back( inpath+"QCD_HT1500to2000_NM1tree.root"                       ); //i=30
FileList.push_back( inpath+"QCD_HT2000toInf_NM1tree.root"                        ); //i=31

//Data
FileList.push_back( inpath+"Data_"+DataName+"_G_NM1tree.root"                    ); //i=32
FileList.push_back( inpath+"Data_"+DataName+"_H_2_NM1tree.root"                  ); //i=33
FileList.push_back( inpath+"Data_"+DataName+"_H_3_NM1tree.root"                  ); //i=34

//AlphaMax Histos
TH1F* h_BareAlpha  = new TH1F("h_BareAlpha"      , "h_BareAlpha"  , 50, 0, 1); // A
TH1F* h_AlphaNM1TA = new TH1F("h_AlphaNM1TA"     , "h_AlphaNM1TA" , 50, 0, 1); // B
TH1F* h_AlphaNM1IP = new TH1F("h_AlphaNM1IP"     , "h_AlphaNM1IP" , 50, 0, 1); // C
TH1F* h_Alpha      = new TH1F("h_Alpha"          , "h_Alpha"      , 50, 0, 1); // D

//TrackAngle Histos
TH1F* h_BareTA     = new TH1F("h_BareTA"         , "h_BareTA"     , 30, -5, 1); //E
TH1F* h_TANM1Alpha = new TH1F("h_TANM1Alpha"     , "h_TANM1Alpha" , 30, -5, 1); //F
TH1F* h_TANM1IP    = new TH1F("h_TANM1IP"        , "h_TANM1IP"    , 30, -5, 1); //G
TH1F* h_TA         = new TH1F("h_TA"             , "h_TA"         , 30, -5, 1); //H

//IP Histos
TH1F* h_BareIP     = new TH1F("h_BareIP"         , "h_BareIP"     , 30, -3, 3); //I
TH1F* h_IPNM1TA    = new TH1F("h_IPNM1TA"        , "h_IPNM1TA"    , 30, -3, 3); //J
TH1F* h_IPNM1Alpha = new TH1F("h_IPNM1Alpha"     , "h_IPNM1Alpha" , 30, -3, 3); //K
TH1F* h_IP         = new TH1F("h_IP"             , "h_IP"         , 30, -3, 3); //L

TString titleText;
if     (sel =="A") titleText = "BareAlpha" ;
else if(sel =="B") titleText = "AlphaNM1TA";
else if(sel =="C") titleText = "AlphaNM1IP";
else if(sel =="D") titleText = "Alpha"     ;
else if(sel =="E") titleText = "BareTA"    ;
else if(sel =="F") titleText = "TANM1Alpha";
else if(sel =="G") titleText = "TANM1IP"   ;
else if(sel =="H") titleText = "TA"        ;
else if(sel =="I") titleText = "BareIP"    ;
else if(sel =="J") titleText = "IPNM1TA"   ;
else if(sel =="K") titleText = "IPNM1Alpha";
else if(sel =="L") titleText = "IP"        ;


TH1F* h_DY;
TH1F* h_TTJets;
TH1F* h_WJ;
TH1F* h_ST;
TH1F* h_VV;
TH1F* h_VG;
TH1F* h_ZH;
TH1F* h_GJets;
TH1F* h_QCD;
TH1F* h_Data;

if(sel =="A" || sel =="B" || sel =="C" || sel =="D"){
h_DY       = new TH1F("h_DY"       , "h_DY"       , 50, 0, 1);
h_TTJets   = new TH1F("h_TTJets"   , "h_TTJets"   , 50, 0, 1);
h_WJ       = new TH1F("h_WJ"       , "h_WJ"       , 50, 0, 1);
h_ST       = new TH1F("h_SingleTop", "h_SingleTop", 50, 0, 1);
h_VV       = new TH1F("h_Diboson"  , "h_Diboson"  , 50, 0, 1);
h_VG       = new TH1F("h_VG"       , "h_VG"       , 50, 0, 1);
h_ZH       = new TH1F("h_ZH"       , "h_ZH"       , 50, 0, 1);
h_GJets    = new TH1F("h_GJets"    , "h_GJets"    , 50, 0, 1);
h_QCD      = new TH1F("h_QCD"      , "h_QCD"      , 50, 0, 1);
h_Data     = new TH1F("h_Data"     , "h_Data"     , 50, 0, 1);
}
else if(sel =="E" || sel =="F" || sel =="G" || sel =="H"){
h_DY       = new TH1F("h_DY"       , "h_DY"       , 30, -5, 1);
h_TTJets   = new TH1F("h_TTJets"   , "h_TTJets"   , 30, -5, 1);
h_WJ       = new TH1F("h_WJ"       , "h_WJ"       , 30, -5, 1);
h_ST       = new TH1F("h_SingleTop", "h_SingleTop", 30, -5, 1);
h_VV       = new TH1F("h_Diboson"  , "h_Diboson"  , 30, -5, 1);
h_VG       = new TH1F("h_VG"       , "h_VG"       , 30, -5, 1);
h_ZH       = new TH1F("h_ZH"       , "h_ZH"       , 30, -5, 1);
h_GJets    = new TH1F("h_GJets"    , "h_GJets"    , 30, -5, 1);
h_QCD      = new TH1F("h_QCD"      , "h_QCD"      , 30, -5, 1);
h_Data     = new TH1F("h_Data"     , "h_Data"     , 30, -5, 1);
}
else if(sel =="I" || sel =="J" || sel =="K" || sel =="L"){
h_DY       = new TH1F("h_DY"       , "h_DY"       , 30, -3, 3);
h_TTJets   = new TH1F("h_TTJets"   , "h_TTJets"   , 30, -3, 3);
h_WJ       = new TH1F("h_WJ"       , "h_WJ"       , 30, -3, 3);
h_ST       = new TH1F("h_SingleTop", "h_SingleTop", 30, -3, 3);
h_VV       = new TH1F("h_Diboson"  , "h_Diboson"  , 30, -3, 3);
h_VG       = new TH1F("h_VG"       , "h_VG"       , 30, -3, 3);
h_ZH       = new TH1F("h_ZH"       , "h_ZH"       , 30, -3, 3);
h_GJets    = new TH1F("h_GJets"    , "h_GJets"    , 30, -3, 3);
h_QCD      = new TH1F("h_QCD"      , "h_QCD"      , 30, -3, 3);
h_Data     = new TH1F("h_Data"     , "h_Data"     , 30, -3, 3);
}
else cout<<"Error"<<endl;

std::vector<TH1F *> v = {h_DY, h_TTJets, h_WJ, h_ST, h_VV, h_VG, h_ZH,  h_GJets, h_QCD};
for (int p =0; p<v.size(); p++){ v[p]->Sumw2();}
h_Data->Sumw2();

for(int i = 0; i <FileList.size(); i++){
TFile file(FileList[i]);
cout <<"Processing file: "<< FileList[i]<<endl;

TTreeReader reader(treeName+"tree", &file);
TTreeReaderValue<vector<int>>    Event(reader,       treeName+"_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, treeName+"_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  Pt(reader,          treeName+"_AODCaloJetPt");
TTreeReaderValue<vector<float>>  IP(reader,          treeName+"_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader,          treeName+"_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader,       treeName+"_AODCaloJetAlphaMax");
TTreeReaderValue<vector<float>>  Eta(reader,         treeName+"_AODCaloJetEta");


while (reader.Next()) {
  for(int j = 0; j<EventWeight->size(); j++){//loop over # of events
    for (int k=0; k<TA->size(); k++){//loop over # of jets
      //Bare Histograms
      h_BareAlpha->Fill(Alpha->at(k), EventWeight->at(j));
      h_BareIP   ->Fill(IP   ->at(k), EventWeight->at(j));
      h_BareTA   ->Fill(TA   ->at(k), EventWeight->at(j));
      // A, E, I groups
      if(sel == "A"){
      if        (i>=0  && i <=4) {h_DY     ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else if   (i==5)           {h_TTJets ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else if   (i==6)           {h_WJ     ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else if   (i>=7  && i<=11) {h_ST     ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else if   (i>=12 && i<=16) {h_GJets  ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else if   (i>=17 && i<=19) {h_VV     ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else if   (i>=20 && i<=21) {h_VG     ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else if   (i>=22 && i<=23) {h_ZH     ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else if   (i>=24 && i<=31) {h_QCD    ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else if   (i>=32 && i<=34) {h_Data   ->Fill(Alpha->at(k), EventWeight->at(j)); }
      else      {cout<<i<<endl;}
      }
      if(sel =="E"){
      if        (i>=0  && i <=4) {h_DY     ->Fill(TA->at(k), EventWeight->at(j)); }
      else if   (i==5)           {h_TTJets ->Fill(TA->at(k), EventWeight->at(j)); }
      else if   (i==6)           {h_WJ     ->Fill(TA->at(k), EventWeight->at(j)); }
      else if   (i>=7  && i<=11) {h_ST     ->Fill(TA->at(k), EventWeight->at(j)); }
      else if   (i>=12 && i<=16) {h_GJets  ->Fill(TA->at(k), EventWeight->at(j)); }
      else if   (i>=17 && i<=19) {h_VV     ->Fill(TA->at(k), EventWeight->at(j)); }
      else if   (i>=20 && i<=21) {h_VG     ->Fill(TA->at(k), EventWeight->at(j)); }
      else if   (i>=22 && i<=23) {h_ZH     ->Fill(TA->at(k), EventWeight->at(j)); }
      else if   (i>=24 && i<=31) {h_QCD    ->Fill(TA->at(k), EventWeight->at(j)); }
      else if   (i>=32 && i<=34) {h_Data   ->Fill(TA->at(k), EventWeight->at(j)); }
      else      {cout<<i<<endl;}
      }
      if(sel =="I"){
      if        (i>=0  && i <=4) {h_DY     ->Fill(IP->at(k), EventWeight->at(j)); }
      else if   (i==5)           {h_TTJets ->Fill(IP->at(k), EventWeight->at(j)); }
      else if   (i==6)           {h_WJ     ->Fill(IP->at(k), EventWeight->at(j)); }
      else if   (i>=7  && i<=11) {h_ST     ->Fill(IP->at(k), EventWeight->at(j)); }
      else if   (i>=12 && i<=16) {h_GJets  ->Fill(IP->at(k), EventWeight->at(j)); }
      else if   (i>=17 && i<=19) {h_VV     ->Fill(IP->at(k), EventWeight->at(j)); }
      else if   (i>=20 && i<=21) {h_VG     ->Fill(IP->at(k), EventWeight->at(j)); }
      else if   (i>=22 && i<=23) {h_ZH     ->Fill(IP->at(k), EventWeight->at(j)); }
      else if   (i>=24 && i<=31) {h_QCD    ->Fill(IP->at(k), EventWeight->at(j)); }
      else if   (i>=32 && i<=34) {h_Data   ->Fill(IP->at(k), EventWeight->at(j)); }
      else      {cout<<i<<endl;}
      }
      //IP has cut
      if( IP->at(j)>=c_ip && Alpha->at(j)>=0.0){
         h_AlphaNM1IP->Fill(Alpha->at(k), EventWeight->at(j)); 
         h_TANM1IP   ->Fill(TA   ->at(k), EventWeight->at(j)); 
         // C, G groups
         if(sel == "C"){
         if        (i>=0  && i <=4) {h_DY     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i==5)           {h_TTJets ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i==6)           {h_WJ     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=7  && i<=11) {h_ST     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=12 && i<=16) {h_GJets  ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=17 && i<=19) {h_VV     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=20 && i<=21) {h_VG     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=22 && i<=23) {h_ZH     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=24 && i<=31) {h_QCD    ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=32 && i<=34) {h_Data   ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else      {cout<<i<<endl;}
         }
         if(sel =="G"){
         if        (i>=0  && i <=4) {h_DY     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i==5)           {h_TTJets ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i==6)           {h_WJ     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=7  && i<=11) {h_ST     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=12 && i<=16) {h_GJets  ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=17 && i<=19) {h_VV     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=20 && i<=21) {h_VG     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=22 && i<=23) {h_ZH     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=24 && i<=31) {h_QCD    ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=32 && i<=34) {h_Data   ->Fill(TA->at(k), EventWeight->at(j)); }
         else      {cout<<i<<endl;}
         }
      }
      //TA has cut
      if( TA->at(j)>=c_ta && Alpha->at(j)>=0.0){
         h_AlphaNM1TA->Fill(Alpha->at(k), EventWeight->at(j)); 
         h_IPNM1TA   ->Fill(IP   ->at(k), EventWeight->at(j)); 
         // B, J groups
         if(sel == "B"){
         if        (i>=0  && i <=4) {h_DY     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i==5)           {h_TTJets ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i==6)           {h_WJ     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=7  && i<=11) {h_ST     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=12 && i<=16) {h_GJets  ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=17 && i<=19) {h_VV     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=20 && i<=21) {h_VG     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=22 && i<=23) {h_ZH     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=24 && i<=31) {h_QCD    ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=32 && i<=34) {h_Data   ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else      {cout<<i<<endl;}
         }
         if(sel =="J"){
         if        (i>=0  && i <=4) {h_DY     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i==5)           {h_TTJets ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i==6)           {h_WJ     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=7  && i<=11) {h_ST     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=12 && i<=16) {h_GJets  ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=17 && i<=19) {h_VV     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=20 && i<=21) {h_VG     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=22 && i<=23) {h_ZH     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=24 && i<=31) {h_QCD    ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=32 && i<=34) {h_Data   ->Fill(IP->at(k), EventWeight->at(j)); }
         else      {cout<<i<<endl;}
         }
      }
      //Alpha has cut
      if( Alpha->at(j)<=c_al && Alpha->at(j)>=0.0){
         h_IPNM1Alpha   ->Fill(IP->at(k), EventWeight->at(j)); 
         h_TANM1Alpha   ->Fill(TA->at(k), EventWeight->at(j)); 
         // K, F groups
         if(sel == "F"){
         if        (i>=0  && i <=4) {h_DY     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i==5)           {h_TTJets ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i==6)           {h_WJ     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=7  && i<=11) {h_ST     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=12 && i<=16) {h_GJets  ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=17 && i<=19) {h_VV     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=20 && i<=21) {h_VG     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=22 && i<=23) {h_ZH     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=24 && i<=31) {h_QCD    ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=32 && i<=34) {h_Data   ->Fill(TA->at(k), EventWeight->at(j)); }
         else      {cout<<i<<endl;}
         }
         if(sel =="K"){
         if        (i>=0  && i <=4) {h_DY     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i==5)           {h_TTJets ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i==6)           {h_WJ     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=7  && i<=11) {h_ST     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=12 && i<=16) {h_GJets  ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=17 && i<=19) {h_VV     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=20 && i<=21) {h_VG     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=22 && i<=23) {h_ZH     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=24 && i<=31) {h_QCD    ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=32 && i<=34) {h_Data   ->Fill(IP->at(k), EventWeight->at(j)); }
         else      {cout<<i<<endl;}
         }
      }
      //Alpha and IP has cut
      if( Alpha->at(j)<=c_al && IP->at(j)>=c_ip && Alpha->at(j)>=0.0){
         h_TA   ->Fill(TA->at(k), EventWeight->at(j)); 
         // H group
         if(sel == "H"){
         if        (i>=0  && i <=4) {h_DY     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i==5)           {h_TTJets ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i==6)           {h_WJ     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=7  && i<=11) {h_ST     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=12 && i<=16) {h_GJets  ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=17 && i<=19) {h_VV     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=20 && i<=21) {h_VG     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=22 && i<=23) {h_ZH     ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=24 && i<=31) {h_QCD    ->Fill(TA->at(k), EventWeight->at(j)); }
         else if   (i>=32 && i<=34) {h_Data   ->Fill(TA->at(k), EventWeight->at(j)); }
         else      {cout<<i<<endl;}
         }
      }
      //Alpha and TA has cut
      if( Alpha->at(j)<=c_al && TA->at(j)>=c_ta && Alpha->at(j)>=0.0){
         h_IP   ->Fill(IP->at(k), EventWeight->at(j)); 
         // L group
         if(sel == "L"){
         if        (i>=0  && i <=4) {h_DY     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i==5)           {h_TTJets ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i==6)           {h_WJ     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=7  && i<=11) {h_ST     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=12 && i<=16) {h_GJets  ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=17 && i<=19) {h_VV     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=20 && i<=21) {h_VG     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=22 && i<=23) {h_ZH     ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=24 && i<=31) {h_QCD    ->Fill(IP->at(k), EventWeight->at(j)); }
         else if   (i>=32 && i<=34) {h_Data   ->Fill(IP->at(k), EventWeight->at(j)); }
         else      {cout<<i<<endl;}
         }
      }
      //IP and TA has cut
      if( IP->at(j)>=c_ip && TA->at(j)>=c_ta && Alpha->at(j)>=0.0){
         h_Alpha   ->Fill(IP->at(k), EventWeight->at(j)); 
         // D group
         if(sel == "D"){
         if        (i>=0  && i <=4) {h_DY     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i==5)           {h_TTJets ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i==6)           {h_WJ     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=7  && i<=11) {h_ST     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=12 && i<=16) {h_GJets  ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=17 && i<=19) {h_VV     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=20 && i<=21) {h_VG     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=22 && i<=23) {h_ZH     ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=24 && i<=31) {h_QCD    ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else if   (i>=32 && i<=34) {h_Data   ->Fill(Alpha->at(k), EventWeight->at(j)); }
         else      {cout<<i<<endl;}
         }
      }

    }//--------------------for jets
  }//----------------------for events
}//------------------------while reader
}//------------------------for files
  std::sort(v.begin(), v.end(),
              [](TH1F *a, TH1F *b) { return a->Integral() < b->Integral(); });
  THStack *hs = new THStack("hs","Combined Backgrounds");
  for(int zz=0; zz<v.size(); zz++)
  {
  hs->Add(v[zz]);
  }
  
  TH1F* h_TotBkg;
  h_TotBkg = (TH1F*) v[0]->Clone("h_TotBkg");
  for(int l=1; l<v.size(); l++){
  h_TotBkg->Add(v[l]);
  }
  h_Data   -> SetLineColor(kBlack);
  h_Data   -> SetMarkerStyle(8);
  h_Data   -> SetMarkerSize(1);
  h_Data   -> SetLineWidth(3);

  h_DY      ->SetFillStyle(1001);
  h_TTJets  ->SetFillStyle(1001);
  h_WJ      ->SetFillStyle(1001);
  h_ST      ->SetFillStyle(1001);
  h_VV      ->SetFillStyle(1001);
  h_VG      ->SetFillStyle(1001);
  h_ZH      ->SetFillStyle(1001);
  h_GJets   ->SetFillStyle(1001);
  h_QCD     ->SetFillStyle(1001);
  
  h_DY      ->SetFillColor(kAzure-3);
  h_TTJets  ->SetFillColor(kGreen+1);
  h_WJ      ->SetFillColor(kViolet-3);
  h_ST      ->SetFillColor(kOrange+1);
  h_VV      ->SetFillColor(kRed);
  h_VG      ->SetFillColor(kPink+9);
  h_ZH      ->SetFillColor(kCyan);
  h_GJets   ->SetFillColor(kViolet+3);
  h_QCD     ->SetFillColor(kGray+1);

  h_DY      ->SetLineColor(kAzure-3);
  h_TTJets  ->SetLineColor(kGreen+1);
  h_WJ      ->SetLineColor(kViolet-3);
  h_ST      ->SetLineColor(kOrange+1);
  h_VV      ->SetLineColor(kRed);
  h_VG      ->SetLineColor(kPink+9);
  h_ZH      ->SetLineColor(kCyan);
  h_GJets   ->SetLineColor(kViolet+3);
  h_QCD     ->SetLineWidth(3);

  h_DY      ->SetLineWidth(3);
  h_TTJets  ->SetLineWidth(3);
  h_WJ      ->SetLineWidth(3);
  h_ST      ->SetLineWidth(3);
  h_VV      ->SetLineWidth(3);
  h_VG      ->SetLineWidth(3);
  h_ZH      ->SetLineWidth(3);
  h_GJets   ->SetLineWidth(3);
  h_QCD     ->SetLineWidth(3);
  
  h_DY      ->SetLineColor(kBlack);
  h_TTJets  ->SetLineColor(kBlack);
  h_WJ      ->SetLineColor(kBlack);
  h_ST      ->SetLineColor(kBlack);
  h_VV      ->SetLineColor(kBlack);
  h_VG      ->SetLineColor(kBlack);
  h_ZH      ->SetLineColor(kBlack);
  h_GJets   ->SetLineColor(kBlack);
  h_QCD     ->SetLineColor(kBlack);
 
  h_TotBkg->SetFillColorAlpha(kYellow, 0.99);
  h_TotBkg->SetFillStyle(3001);


  if(dolog){ 
  hs->SetMaximum(hs->GetMaximum()*4000.0);  
  hs->SetMinimum(1.0e-2);
  }
  else
  hs->SetMaximum(hs->GetMaximum()*2.0);  
  
  hs->SetTitle(regionName+": "+titleText);
  //hs_A->GetXaxis()->SetTitle(h_BareAlpha->GetTitle());
  //hs->GetXaxis()->SetTitleSize(20);
  //hs->GetYaxis()->SetTitle("Entries    ");
  //hs->GetYaxis()->SetTitleOffset(1.5);
  
  pad->cd(); 

  //TLegend *leg = new TLegend(0.48,0.6,0.88,0.85);
  TLegend *leg = new TLegend(0.15,0.6,0.65,0.85);
  leg->SetNColumns(2);
  leg->SetBorderSize(1);
  leg->SetTextSize(.03);
  leg->AddEntry(h_DY,    "Drell-Yan"        , "f");
  leg->AddEntry(h_TTJets,"t#bar{t}+Jets"    , "f");
  leg->AddEntry(h_WJ,    "W+Jets"           , "f");
  leg->AddEntry(h_ST,    "Single Top"       , "f");
  leg->AddEntry(h_VV,    "Diboson"          , "f");
  leg->AddEntry(h_VG,    "V#gamma"          , "f");
  leg->AddEntry(h_ZH,    "ZH#rightarrowLLbb", "f");
  leg->AddEntry(h_GJets, "#gamma+Jets"      , "f");
  leg->AddEntry(h_QCD,   "QCD"              , "f");
  if(treeName != "NM1MuZH" || treeName != "NM1EleZH") leg->AddEntry(h_Data,  DataName           , "lpe");
  leg->AddEntry(h_TotBkg, "MC bkg. stat. err." , "f" );
  
  hs        ->Draw("hist");
  h_TotBkg  ->Draw("E2 same");
  if(treeName != "NM1MuZH" || treeName != "NM1EleZH") h_Data    ->Draw("E same");
  leg->Draw();
  title->DrawTextNDC(0.06,0.91,"CMS");
  extra->DrawTextNDC(0.23,0.91,"Preliminary");
  lumi->DrawTextNDC(0.9,0.91,"16.23/fb (13 TeV)");
  gPad->Update();
  gPad->RedrawAxis();
  
  rpad->cd();

  TH1F* h_Ratio;
  TH1F* h_Ratiostaterr;
  //h_ntRatio->Sumw2();
  //h_ntRatiostaterr->Sumw2();
  h_Ratio = (TH1F*) h_Data->Clone("h_Ratio");
  h_Ratio->Divide(h_TotBkg);
  h_Ratio->SetTitle(" ");
  h_Ratio->SetTitle(" ");
  // Y axis ratio plot settings
  h_Ratio->GetYaxis()->SetTitleSize(35);
  h_Ratio->GetYaxis()->SetTitleFont(43);
  h_Ratio->GetYaxis()->SetTitleOffset(1.55);
  h_Ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_Ratio->GetYaxis()->SetLabelSize(20);
  //h_Ratio->GetYaxis()->SetNdivisions(-105);
  h_Ratio->GetYaxis()->SetTitle("Data/MC");
  // X axis ratio plot settings
  h_Ratio->GetXaxis()->SetTitleSize(40);
  h_Ratio->GetXaxis()->SetTitleFont(43);
  h_Ratio->GetXaxis()->SetTitle(h_Data->GetTitle());
  h_Ratio->GetXaxis()->SetTitleOffset(4.0);
  h_Ratio->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
  h_Ratio->GetXaxis()->SetLabelSize(20);//20
  h_Ratio->SetMarkerStyle(20);
  h_Ratio->SetMarkerColor(kRed);
  h_Ratio->SetMarkerSize(1);
  h_Ratio->GetYaxis()->SetRangeUser(0,2);

  h_Ratiostaterr = (TH1F*)h_TotBkg->Clone("Ratiostaterr");
  h_Ratiostaterr->Divide(h_TotBkg);
  h_Ratio->Draw("ep"); 
  rpad->Update();
  TLine *line = new TLine(rpad->GetUxmin(), 1, rpad->GetUxmax(), 1);
  line->SetLineWidth(3);
  line->SetLineStyle(9);
  line->SetLineColor(kBlue);
  line->Draw("sames");
  h_Ratiostaterr->Draw("e2 same");
  
  rpad->Update();

  TString outname = outpath+titleText;
  if(dolog) canvas->SaveAs(outname+regionName+"_log.pdf");
  else      canvas->SaveAs(outname+regionName+".pdf");
}
