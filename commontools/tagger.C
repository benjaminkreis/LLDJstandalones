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
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <cstdlib> /* mkdir */
#include <stdlib.h>     /* getenv */

//std::cout <<"Test"<<std::endl;
///can do variable cuts or specified cuts
void tagger(Double_t c_ip, Double_t c_ta, Double_t c_al, Int_t ntags, TString lifetime, TString mass){

bool variable_cut = true;
bool plot         = true; //plots scanning result/ntags
bool prntTable    = false;
TString plots = TString(getenv("plotdir"));
//TString aversion = TString(getenv("aversion"));
TString aversion = "CRTriggers";
//TString aversion = "CRHeavyOPT";
TString DataName = "MuonEG";
//TString DataName = "SinglePhoton";
//TString outpath = "/uscms/home/ddiaz/nobackup/LLDJ_slc6_530_CMSSW_8_0_26_patch1/src/LLDJstandalones/plots/tagger/BarrelVEndcap/"+lifetime;
TString outpath = plots+"/"+aversion+"/tagger/"+lifetime;
TString inpath  = "../roots/";
inpath = inpath+aversion+"/";
//1=IP, 2=TA, 3/default=Alpha
int  sel          = 3;
const float x     = 0.0; //for sys uncertainty

TString var;
if     (sel ==1){var = "MedianLog10IPSig";}
else if(sel ==2){var = "MedianLog10TrackAngle";}
else            {var = "AlphaMax";}

vector<TString> SigFileList;
vector<TString> BkgFileList;
//Big-hitters
SigFileList.push_back  ( inpath+"ggZH_HToSSTobbbb_ZToLL_MH-125_"+mass+"_"+lifetime+"_OPTtree.root");
SigFileList.push_back  ( inpath+"ZH_HToSSTobbbb_ZToLL_MH-125_"+mass+"_"  +lifetime+"_OPTtree.root");

BkgFileList.push_back( inpath+"DYJetsToLL_M-50_OPTtree.root"                        ); //kk=0
BkgFileList.push_back( inpath+"DYJetsToLL_M-10to50_OPTtree.root"                    ); //kk=1
BkgFileList.push_back( inpath+"TTJets_OPTtree.root"                                 ); //kk=2
BkgFileList.push_back( inpath+"WJetsToLNu_OPTtree.root"                             ); //kk=3
//single-top
BkgFileList.push_back( inpath+"ST_s-channel_4f_leptonDecays_OPTtree.root"           ); //kk=4
BkgFileList.push_back( inpath+"ST_tW_top_5f_NoFullyHadronicDecays_OPTtree.root"     ); //kk=5
BkgFileList.push_back( inpath+"ST_t-channel_top_4f_inclusiveDecays_OPTtree.root"    ); //kk=6
BkgFileList.push_back( inpath+"ST_tW_antitop_5f_NoFullyHadronicDecays_OPTtree.root" ); //kk=7
BkgFileList.push_back( inpath+"ST_t-channel_antitop_4f_inclusiveDecays_OPTtree.root"); //kk=8
//diboson
BkgFileList.push_back( inpath+"WW_OPTtree.root"                                     );//kk=9
BkgFileList.push_back( inpath+"WZ_OPTtree.root"                                     ); //kk=10
BkgFileList.push_back( inpath+"ZZ_OPTtree.root"                                     ); //kk=11
//VG
BkgFileList.push_back( inpath+"WGToLNuG_OPTtree.root"                               ); //kk=12
BkgFileList.push_back( inpath+"ZGTo2LG_OPTtree.root"                                ); //kk=13
//SM Higgs decays
BkgFileList.push_back( inpath+"ggZH_HToBB_ZToLL_OPTtree.root"                       ); //kk=14
BkgFileList.push_back( inpath+"ZH_HToBB_ZToLL_OPTtree.root"                         ); //kk=15
//CRLight
BkgFileList.push_back( inpath+"GJets_HT-40To100_OPTtree.root"                       ); //kk=16
BkgFileList.push_back( inpath+"GJets_HT-100To200_OPTtree.root"                      ); //kk=17
BkgFileList.push_back( inpath+"GJets_HT-200To400_OPTtree.root"                      ); //kk=18
BkgFileList.push_back( inpath+"GJets_HT-400To600_OPTtree.root"                      ); //kk=19
BkgFileList.push_back( inpath+"GJets_HT-600ToInf_OPTtree.root"                      ); //kk=20
//QCD
//BkgFileList.push_back( inpath+"QCD_HT100to200_OPTtree.root"                         ); //kk=21
//BkgFileList.push_back( inpath+"QCD_HT200to300_OPTtree.root"                         ); //kk=22
//BkgFileList.push_back( inpath+"QCD_HT300to500_OPTtree.root"                         ); //kk=23
//BkgFileList.push_back( inpath+"QCD_HT500to700_OPTtree.root"                         ); //kk=24
//BkgFileList.push_back( inpath+"QCD_HT700to1000_OPTtree.root"                        ); //kk=25
//BkgFileList.push_back( inpath+"QCD_HT1000to1500_OPTtree.root"                       ); //kk=26
//BkgFileList.push_back( inpath+"QCD_HT1500to2000_OPTtree.root"                       ); //kk=27


//Data
BkgFileList.push_back( inpath+"Data_"+DataName+"_G_OPTtree.root"                    ); //kk=28
BkgFileList.push_back( inpath+"Data_"+DataName+"_H_2_OPTtree.root"                  ); //kk=29
BkgFileList.push_back( inpath+"Data_"+DataName+"_H_3_OPTtree.root"                  ); //kk=30
int nData = 3; //number of data files to avoind counting as background
TString nt, s_c_ip, s_c_ta, s_c_al, xx;
nt    .Form("%1d",ntags);
s_c_ip.Form("%1.2f",c_ip);
s_c_ta.Form("%1.2f",c_ta);
s_c_al.Form("%1.2f",c_al);
xx    .Form("%1.2f",x);

bool prnt         = false;
bool prnt2        = false;
ofstream slides;
slides.open (outpath+"/tags"+"_"+mass+"_"+lifetime+"__cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+".txt");
//slides.open ("testSlides.txt");
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
if(variable_cut){
const int NC = 100;
float MAX;
float MIN;
if(sel==1){
 MIN = -3.0;
 MAX = 3.0;
}
else if(sel==2){
 MIN = -3.0;
 MAX = 3.0;
}
else{
 MIN = 0.0;
 MAX = 1.0;
}
const float STEP = (MAX-MIN)/((NC)*1.0);

vector<int>   tags_s(NC+1,0);
vector<int>   tags_b(NC+1,0);
vector<float> num_sig_(NC+1,0.0);// = 0.0;
vector<float> num_bkg_(NC+1,0.0);
vector<float> cut_val_(NC,0.0);
float cv[NC];

float ss=0.0;
float max_ss = 0.0;
float max_pos = 0.0;
float significance_[NC];

//loop cuts
for(int hh = 0; hh<=NC; hh++){
cut_val_[hh] = (MIN + (float)hh*STEP);
//loop over sig files
for(int ii = 0; ii <SigFileList.size(); ii++){
tags_s.clear();
TFile file(SigFileList[ii]);
			if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
///cout <<"Processing file: "<< SigFileList[i]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  Pt(reader, "OPT_AODCaloJetPt");
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");
TTreeReaderValue<vector<float>>  Eta(reader, "OPT_AODCaloJetEta");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    //set initial #tags to 0
    tags_s[hh] =0;
    			if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    			if(prnt)cout<<"IP: ";
    
    //apply cut increment #tags
    if(sel ==1){
    			if(prnt)cout<<"IP: ";
      for (int j=0; j<IP->size(); j++){
     			if(prnt)cout<<IP->at(j)<<",   ";
        if(IP->at(j)>=cut_val_[hh]){
        tags_s[hh] = tags_s[hh] + 1;
        }
      }
    }
    else if(sel ==2){
    			if(prnt)cout<<"TA: ";
      for (int j=0; j<TA->size(); j++){
        		if(prnt)cout<<TA->at(j)<<",   ";
        if(TA->at(j)>=cut_val_[hh]){
        tags_s[hh] = tags_s[hh] + 1;
        }
      }
    }
    else{
    			if(prnt)cout<<"Alpha: ";
      for (int j=0; j<Alpha->size(); j++){
        		if(prnt)cout<<Alpha->at(j)<<",   ";
        if(Alpha->at(j)<=cut_val_[hh] && Alpha->at(j)>=0.0 /*&& IP->at(j)>=1.00 && TA->at(j)>=-1.75*/){
        tags_s[hh] = tags_s[hh] + 1;
        }
      }
    }
    if(tags_s[hh] >=ntags){num_sig_[hh] = num_sig_[hh] + EventWeight->at(i);}
    			if(prnt)cout<<endl;
  }
			if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
			if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
			if(prnt)cout<<"Num_sig: "             <<num_sig_[hh]<<"        tags: "             <<tags_s[hh]<<endl;
if(sel ==1){
  			if(prnt)cout<<"IP Size: "                <<IP->size()<<endl;
}
else if(sel ==2){
  			if(prnt)cout<<"TA Size: "                <<TA->size()<<endl;
}
else{
  			if(prnt)cout<<"Alpha Size: "             <<Alpha->size()<<endl;
}
			if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//Loop over sig files
//loop over bkg files avoid the data files
for(int jj = 0; jj <BkgFileList.size()-nData; jj++){
tags_b.clear();
TFile file(BkgFileList[jj]);
			if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
///cout <<"Processing file: "<< BkgFileList[j]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  Pt(reader, "OPT_AODCaloJetPt");
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");
TTreeReaderValue<vector<float>>  Eta(reader, "OPT_AODCaloJetEta");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags_b[hh] =0;
    			if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    if(sel ==1){
    			if(prnt)cout<<"IP: ";
      for (int j=0; j<IP->size(); j++){
        		if(prnt)cout<<IP->at(j)<<",   ";
        if(IP->at(j)>=cut_val_[hh]){
        tags_b[hh] = tags_b[hh] + 1;
        }
      }
    }
    else if(sel ==2){
    			if(prnt)cout<<"TA: ";
      for (int j=0; j<TA->size(); j++){
        		if(prnt)cout<<TA->at(j)<<",   ";
        if(TA->at(j)>=cut_val_[hh]){
        tags_b[hh] = tags_b[hh] + 1;
        }
      }
    }
    else{
    			if(prnt)cout<<"Alpha: ";
      for (int j=0; j<Alpha->size(); j++){
        		if(prnt)cout<<Alpha->at(j)<<",   ";
        if(Alpha->at(j)<=cut_val_[hh] && Alpha->at(j)>=0.0 /*&& IP->at(j)>=1.00 && TA->at(j)>=-1.75*/){
        tags_b[hh] = tags_b[hh] + 1;
        }
      }
    }
    if(tags_b[hh] >=ntags){num_bkg_[hh] = num_bkg_[hh] + EventWeight->at(i);}
    			if(prnt)cout<<endl;
  }
			if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
			if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
			if(prnt)cout<<"Num_bkg: "             <<num_bkg_[hh]<<"        tags: "             <<tags_b[hh]<<endl;
if(sel ==1){
  			if(prnt)cout<<"IP Size: "                <<IP->size()<<endl;
}
else if(sel ==2){
  			if(prnt)cout<<"TA Size: "                <<TA->size()<<endl;
}
else{
  			if(prnt)cout<<"Alpha Size: "             <<Alpha->size()<<endl;
}
			if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//Loop over bkg files
			if(prnt2)cout<<"cut_val: "<<cut_val_[hh]<<"   N_sig: "<<num_sig_[hh] <<"   N_bkg: "<<num_bkg_[hh]<<endl;
cv[hh] = cut_val_[hh];
if((num_sig_[hh] + num_bkg_[hh]) >0) ss = (num_sig_[hh]/( sqrt(num_sig_[hh] + num_bkg_[hh]+ x*num_bkg_[hh])  ) );
else ss=0.0;
if(ss> max_ss){ max_ss = ss; max_pos = cut_val_[hh];}
significance_[hh] = ss;
}//loop cuts
//for(int zzz=0; zzz<=NC+10; zzz++)
//{
//cout <<"iterator: "<<zzz<<"       alpha: "<<cv[zzz] <<"              significance: "<< significance_[zzz]<<endl;
//}
TGraph *eff = new TGraph(NC,cv, significance_);
eff->Draw();
cout<<"MaxSignificance: "<<max_ss<<"    CutValue: "<<max_pos<<endl;
// ######## Print out #######
if(plot){
  TCanvas* canvas = new TCanvas("canvas","canvas",1280,1024);
  canvas->Clear();
  canvas->cd();
  canvas->SetGrid();
  TPad *pad1  = new TPad("pad1", "pad1", 0, 0.0, 1, 1);
  gStyle->SetOptStat(0);
  //pad1->SetLogy(dolog);
  pad1->SetTickx();
  pad1->SetTicky(); 
  pad1->Draw();
  pad1->SetGrid();
  pad1->SetFillStyle(4000);
  pad1->cd();
  gStyle->SetLineWidth(2);
  gStyle->SetPalette(71);

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

  canvas->SetGrid();
  //pad1->SetGrid();
  canvas->Update(); 
  eff->SetMaximum( max_ss + 0.1*max_ss ); 
  eff->GetXaxis()->SetLimits(cv[0],cv[NC-1]);
  eff->GetYaxis()->SetTitle("#frac{S}{#sqrt{S+B+"+xx+"*B}}");
  eff->GetXaxis()->SetTitle("Cut Value");
  //gPad->SetLeftMargin(0.15);
  //gPad->SetLeftMargin(0.15);
  pad1->SetLeftMargin(0.15);
  pad1->SetLeftMargin(0.15);
  eff->GetYaxis()->SetTitleOffset(2.0);
  eff->GetXaxis()->CenterTitle();
  eff->GetYaxis()->CenterTitle();
  eff->SetLineWidth(2);
  eff->Draw   ("AL"/*"*"*/);
  eff->SetTitle("gte"+nt+"_tags;"+var+"_"+lifetime);
  title->DrawTextNDC(0.06,0.91,"CMS");
  extra->DrawTextNDC(0.23,0.91,"Preliminary");
  lumi->DrawTextNDC(0.9,0.91,"xx /fb (13 TeV)");
  //gPad->Update();
  //gPad->RedrawAxis();
  pad1->Update();
  pad1->RedrawAxis();
  //canvas->SaveAs(outpath+"/Ntags_"+nt+"_"+var+"_"+lifetime+"_sys"+xx+".png");
  canvas->SaveAs("test.jpg");
//  canvas->Clear();
}

}//end variable cut

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@










//non variable cut
else{

//float tags; 
//ntDY, ntTTL_T, ntTTL_Tbar, ntWJ, ntTTtoLL, ntDiboson, ntST;
//float nt
float tags, ntDY, ntTTJets, ntWJ, ntST, ntVV, ntVG, ntZH, ntGJets, ntQCD, ntData;
float num_sig = 0.0;
float num_bkg = 0.0;

int Nbins = 6;
TH1F* h_ntags      = new TH1F("h_ntags"      , "ags"      , Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntDY       = new TH1F("h_ntDY"       , "DY"       , Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntTTJets   = new TH1F("h_ntTTJets"   , "TTJets"   , Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntWJ       = new TH1F("h_ntWJ"       , "WJ"       , Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntST       = new TH1F("h_ntSingleTop", "SingleTop", Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntVV       = new TH1F("h_ntDiboson"  , "Diboson"  , Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntVG       = new TH1F("h_ntVG"       , "VG"       , Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntZH       = new TH1F("h_ntZH"       , "ZH"       , Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntGJets    = new TH1F("h_ntGJets"    , "GJets"    , Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntQCD      = new TH1F("h_ntQCD"      , "QCD"      , Nbins, -0.5, (float)(Nbins)-0.5);
TH1F* h_ntData     = new TH1F("h_ntData"     , "Data"     , Nbins, -0.5, (float)(Nbins)-0.5);

TH1F* h_Test       = new TH1F("h_Test", "h_Test", 50, 0, 500);
std::vector<TH1F *> v = {h_ntDY, h_ntTTJets, h_ntWJ, h_ntST, h_ntVV, h_ntVG, h_ntZH, h_ntGJets, h_ntQCD};
for (int p =0; p<v.size(); p++){ v[p]->Sumw2();}
h_ntags->Sumw2();
h_ntData->Sumw2();
//loop over sig files
for(int jj = 0; jj <SigFileList.size(); jj++){
TFile file(SigFileList[jj]);
			if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< SigFileList[jj]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader,       "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  Pt(reader,          "OPT_AODCaloJetPt");
TTreeReaderValue<vector<float>>  IP(reader,          "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader,          "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader,       "OPT_AODCaloJetAlphaMax");
TTreeReaderValue<vector<float>>  Eta(reader,         "OPT_AODCaloJetEta");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags =0;
    			if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    			if(prnt)cout<<"IP,TA,Alpha: "<<endl;
    for (int j=0; j<TA->size(); j++){
      			if(prnt)cout<<IP->at(j)<<"     "<<TA->at(j)<<"     "<<Alpha->at(j)<<endl;
      if(Alpha->at(j)<=c_al && IP->at(j)>=c_ip && TA->at(j)>=c_ta && Alpha->at(j)>=0.0 /*&& fabs(Eta->at(j))<=1.5 */){
      tags = tags + 1;
      }
    }
    if(tags >=ntags){num_sig = num_sig + EventWeight->at(i);}
    			if(prnt)cout<<endl;
    h_ntags->Fill(tags, EventWeight->at(i)); if(prnt){cout<<"File: " <<SigFileList[jj]<<" weight: " <<EventWeight->at(i)<<endl;}
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_sig: "             <<num_sig<<"        tags: "             <<tags<<endl;
if(prnt)cout<<"IP Size: "             <<IP->size()<<endl;
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//Loop over sig files
//loop over bkg files
for(int kk = 0; kk <BkgFileList.size(); kk++){
TFile file(BkgFileList[kk]);
			if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< BkgFileList[kk]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader,       "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  Pt(reader,          "OPT_AODCaloJetPt");
TTreeReaderValue<vector<float>>  IP(reader,          "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader,          "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader,       "OPT_AODCaloJetAlphaMax");
TTreeReaderValue<vector<float>>  Eta(reader,         "OPT_AODCaloJetEta");
while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags       = 0;
    ntDY       = 0;
    ntTTJets   = 0;
    ntWJ       = 0;
    ntST       = 0;
    ntVV       = 0;
    ntVG       = 0;
    ntZH       = 0;
    ntGJets    = 0;
    ntQCD      = 0;
    ntData     = 0;
    			if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    			if(prnt)cout<<"IP,TA,Alpha: "<<endl;
    for (int j=0; j<TA->size(); j++){
      			if(prnt)cout<<IP->at(j)<<"     "<<TA->at(j)<<"     "<<Alpha->at(j)<<endl;
      h_Test->Fill(Pt->at(j));
      if(Alpha->at(j)<=c_al && IP->at(j)>=c_ip && TA->at(j)>=c_ta && Alpha->at(j)>=0.0 /*&&fabs(Eta->at(j))<=1.5 */ ){
      tags = tags + 1;
      if        (kk>=0 && kk <=1) {ntDY     = ntDY     + 1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: "<< ntDY<<endl;*/}
      else if   (kk==2)           {ntTTJets = ntTTJets + 1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: "<< ntTTL_T<<endl;*/}
      else if   (kk==3)           {ntWJ     = ntWJ     + 1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: "<< ntTTL_Tbar<<endl;*/}
      else if   (kk>=4  && kk<=8) {ntST     = ntST     + 1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: " <<ntWJ<<endl;*/}
      else if   (kk>=9  && kk<=11){ntVV     = ntVV     + 1;}
      else if   (kk>=12 && kk<=13){ntVG     = ntVG     + 1;}
      else if   (kk>=14 && kk<=15){ntZH     = ntZH     + 1;}
      else if   (kk>=16 && kk<=20){ntGJets  = ntGJets  + 1;}
      else if   (kk>=21 && kk<=27){ntQCD    = ntQCD    + 1;}
      else if   (kk>=28 && kk<=30){ntData   = ntData   + 1;}
      else      {i=i;}
      }
    }
    if(tags >=ntags && kk<21){num_bkg = num_bkg + EventWeight->at(i);}
    			if(prnt)cout<<endl;

    if     (kk>=0 && kk<=1)  {h_ntDY    ->Fill(ntDY    , EventWeight->at(i)); if(prnt){cout <<"File: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
    else if(kk==2)           {h_ntTTJets->Fill(ntTTJets, EventWeight->at(i)); if(prnt){cout <<"File: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
    else if(kk==3)           {h_ntWJ    ->Fill(ntWJ    , EventWeight->at(i)); if(prnt){cout <<"File: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
    else if(kk>=4  && kk<=8) {h_ntST    ->Fill(ntST    , EventWeight->at(i)); if(prnt){cout <<"File: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
    else if(kk>=9  && kk<=11){h_ntVV    ->Fill(ntVV    , EventWeight->at(i)); }
    else if(kk>=12 && kk<=13){h_ntVG    ->Fill(ntVG    , EventWeight->at(i)); }
    else if(kk>=14 && kk<=15){h_ntZH    ->Fill(ntZH    , EventWeight->at(i)); }
    else if(kk>=16 && kk<=20){h_ntGJets ->Fill(ntGJets , EventWeight->at(i)); }
    else if(kk>=21 && kk<=27){h_ntQCD   ->Fill(ntQCD   , EventWeight->at(i)); }
    else if(kk>=28 && kk<=30){h_ntData  ->Fill(ntData  , EventWeight->at(i)); }
    else {h_ntDY->Fill(-3);if(prnt){cout <<"ErrorFile: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_bkg: "             <<num_bkg<<"        tags: "             <<tags<<endl;
if(prnt)cout<<"IP Size: "             <<IP->size()<<endl;
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//End Loop over bkg files
cout <<"Num_sig: "<<num_sig<<"         Num_bkg: " <<num_bkg<<endl;
if(plot){
  //canvas stuff
  //Bool_t dolog = kFALSE;
  Bool_t dolog = kTRUE;
  //TString extraname = "";
  //if(dolog){extraname+="_log";}
  TCanvas* canvas2 = new TCanvas("canvas2","canvas2",1100,1200);//1280,1024);
  canvas2->Clear();
  canvas2->cd();
  canvas2->SetGrid();
  //TPad *pad2  = new TPad("pad2", "pad2", 0, 0.25, 1, 1);
  TPad *pad2  = new TPad("pad2", "pad2", 0, 0, 1, 1);
  gStyle->SetOptStat(0);
  pad2->SetLogy(dolog);
  pad2->SetTickx();
  pad2->SetTicky(); 
  pad2->Draw();
  pad2->SetGrid();
  //pad2->SetFillStyle(4000);
  pad2->cd();
  //gStyle->SetLineWidth(2);
  //gStyle->SetPalette(71);
  
  canvas2->cd();
  TPad *rpad = new TPad("ratiopad","ratiopad", 0, 0 ,1, 0.25);
  rpad->SetGrid();
  //rpad->Draw(); 
  canvas2->cd();
 
  TText* title2 = new TText(1,1,"") ; 
  title2->SetTextSize(0.04);
  title2->SetTextColor(kBlack);
  title2->SetTextAlign(11);
  title2->SetTextFont(62);

  TText* extra2 = new TText(1,1,"") ;
  extra2->SetTextSize(0.04);
  extra2->SetTextColor(kBlack);
  extra2->SetTextAlign(11);
  extra2->SetTextFont(52);

  TText* lumi2 = new TText(1,1,"") ;
  lumi2->SetTextSize(0.03);
  lumi2->SetTextColor(kBlack);
  lumi2->SetTextAlign(31);
  lumi2->SetTextFont(42);

  canvas2->Update(); 
  h_ntags->GetXaxis()->SetTitle("Number of tags");
  gPad   ->SetLeftMargin(0.15);
  h_ntags->GetYaxis()->SetTitleOffset(2.0);
  h_ntags->GetXaxis()->CenterTitle();
  h_ntags->GetYaxis()->CenterTitle();
  h_ntags->SetLineWidth(3);
  h_ntags->SetLineColor(1);
  THStack *hs = new THStack("hs","Number of tags");
  
  std::sort(v.begin(), v.end(),
              [](TH1F *a, TH1F *b) { return a->Integral() < b->Integral(); });
  //hs.Add(h_ntags);
  for(int zz=0; zz<v.size(); zz++)
  {
  hs->Add(v[zz]);
  }
  //h_ntDY      ->Draw   ("hist same");
  //h_ntTTL_T   ->Draw   ("hist same");
  //h_ntTTL_Tbar->Draw   ("hist same");
  //h_ntWJ      ->Draw   ("hist same");
  TH1F* h_ntTotBkg;
  //h_ntTotBkg->Sumw2();
  h_ntTotBkg = (TH1F*) v[0]->Clone("h_ntTotBkg");
  for(int l=1; l<v.size(); l++){
  h_ntTotBkg->Add(v[l]);
  }

  h_ntData    -> SetLineColor(kBlack);
  h_ntData    -> SetMarkerStyle(8);
  h_ntData    -> SetMarkerSize(2);
  h_ntData    -> SetLineWidth(3);

  h_ntDY      ->SetFillStyle(1001);
  h_ntTTJets  ->SetFillStyle(1001);
  h_ntWJ      ->SetFillStyle(1001);
  h_ntST      ->SetFillStyle(1001);
  h_ntVV      ->SetFillStyle(1001);
  h_ntVG      ->SetFillStyle(1001);
  h_ntZH      ->SetFillStyle(1001);
  h_ntGJets   ->SetFillStyle(1001);
  h_ntQCD     ->SetFillStyle(1001);
  
  h_ntDY      ->SetFillColor(kAzure-3);
  h_ntTTJets  ->SetFillColor(kGreen+1);
  h_ntWJ      ->SetFillColor(kViolet-3);
  h_ntST      ->SetFillColor(kOrange+1);
  h_ntVV      ->SetFillColor(kRed);
  h_ntVG      ->SetFillColor(kPink+9);
  h_ntZH      ->SetFillColor(kCyan);
  h_ntGJets   ->SetFillColor(kViolet+3);
  h_ntQCD     ->SetFillColor(kGray+1);
  //h_ntData    ->SetFillColor(1);

  h_ntDY      ->SetLineColor(kAzure-3);
  h_ntTTJets  ->SetLineColor(kGreen+1);
  h_ntWJ      ->SetLineColor(kViolet-3);
  h_ntST      ->SetLineColor(kOrange+1);
  h_ntVV      ->SetLineColor(kRed);
  h_ntVG      ->SetLineColor(kPink+9);
  h_ntZH      ->SetLineColor(kCyan);
  h_ntGJets   ->SetLineColor(kViolet+3);
  h_ntQCD     ->SetLineColor(kGray+1);
  //h_ntData    ->SetLineColor(1);

  h_ntDY      ->SetLineWidth(3);
  h_ntTTJets  ->SetLineWidth(3);
  h_ntWJ      ->SetLineWidth(3);
  h_ntST      ->SetLineWidth(3);
  h_ntVV      ->SetLineWidth(3);
  h_ntVG      ->SetLineWidth(3);
  h_ntZH      ->SetLineWidth(3);
  h_ntGJets   ->SetLineWidth(3);
  h_ntQCD     ->SetLineWidth(3);
  //h_ntData    ->SetLineWidth(4);
  h_ntDY      ->SetLineColor(kBlack);
  h_ntTTJets  ->SetLineColor(kBlack);
  h_ntWJ      ->SetLineColor(kBlack);
  h_ntST      ->SetLineColor(kBlack);
  h_ntVV      ->SetLineColor(kBlack);
  h_ntVG      ->SetLineColor(kBlack);
  h_ntZH      ->SetLineColor(kBlack);
  h_ntGJets   ->SetLineColor(kBlack);
  h_ntQCD     ->SetLineColor(kBlack);
 
  h_ntTotBkg->SetFillColorAlpha(kYellow, 0.99);
  h_ntTotBkg->SetFillStyle(3690);

  //h_ntTotBkg->SetBinError(2, 100000);
  //h_ntTotBkg->SetBinError(3, 1000);
  /*
  for(int o = 1; o <7; o++){ 
  cout <<"Ntags: "<<o-1<<endl;
  cout<<"Histogram: "<<h_ntData->GetTitle()<<"   Entries: "<<h_ntData->GetBinContent(o)<<"     "<<endl;
  cout<<"Histogram: "<<"ntTotBkg"<<"   Entries: "<<h_ntags->GetBinContent(o)<<"     "<<endl;
  cout<<"Histogram: "<<h_ntTotBkg->GetTitle()<<"   Entries: "<<h_ntTotBkg->GetBinContent(o)<<"     "<<endl;
  for(int p = 0; p<v.size(); p++ ){
  cout<<"Histogram: "<<v[p]->GetTitle()<<"   Entries: "<<v[p]->GetBinContent(o)<<"     "<<endl;}}
  int ntest = 4;
  if(h_ntTotBkg->GetBinContent(ntest)>0 || h_ntData->GetBinContent(ntest)>0 || h_ntags->GetBinContent(ntest)>0) {cout<< "Passed" <<endl;}
  */  
 if(prntTable){
 slides<<"\\begin{wframe}{Ntags    cip: " +s_c_ip+ ",  cta: " +s_c_ta+",  cal: "+s_c_al+"}"<<endl;
 slides<<"    \\begin{minipage}{0.5\\textwidth}"<<endl; 
 slides<<"        \\begin{figure}"<<endl;
 slides<<"            \\centering"<<endl;
 slides<<"            \\includegraphics[width=\\textwidth]{{tags_" +mass+ "_"+lifetime+"__cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+"}.png}"<<endl;
 slides<<"        \\end{figure}"<<endl;
 slides<<"    \\end{minipage}%"<<endl;
 slides<<"    \\begin{minipage}{0.5\\textwidth}"<<endl;
 slides<<"    \\begin{minipage}{\\textwidth}"<<endl;
 slides<<"    \\begin{itemize}"<<endl;
 slides<<"        \\item MS: Scalar Particle Mass"<<endl;
 slides<<"        \\item ctauS: Proper lifetime"<<endl;
 slides<<"        \\item cip: ImpactParameter cut"<<endl;
 slides<<"        \\item cta: TrackAngle var. cut"<<endl;
 slides<<"        \\item cal: alphaMax var. cut"<<endl;
 slides<<"        \\end{itemize}"<<endl;
 slides<<"        \\vspace{0.5em}"<<endl;
 slides<<"    \\end{minipage}"<<endl;
 slides<<"    \\begin{minipage}{\\textwidth}"<<endl;
 slides<<"        \\begin{table}"<<endl;
 slides<<"            \\centering"<<endl;
 slides<<"            \\resizebox{\\textwidth}{!}{ "<<endl;
 slides<<"            \\begin{tabular}{c|c|c|c|c|c|c}"<<endl;
  for(int o = 0; o < v.size()+1 ; o++){
    if(o==0){slides<<"Name  & ";}
    //if(o==1){slides<<"Signal  & ";}
    //if(o==2){slides<<"Data  & ";}
    else{
    slides<<v[o-1]->GetTitle()<<" &    ";}
    for(int p =1 ; p <5 ; p++){
      if(o==0){
        slides<<p-1;
        if(p<4){
          slides<<" &     ";
        }
        else{
          slides<<" \\\\  \\hline";
        }
      }
      /*else if(o==1){
        slides<< std::setprecision(5)<<h_ntags->GetBinContent(p);
        if(p<4){
          slides<<" &   ";
        }
        else{
          slides<<" \\\\";
        }
      }
      else if(o==2){
        slides<< std::setprecision(5)<<h_ntData->GetBinContent(p);
        if(p<4){
          slides<<" &   ";
        }
        else{
          slides<<" \\\\";
        }
      }
      */
      else{
        slides<< std::setprecision(5)<<v[o-1]->GetBinContent(p);
        if(p<4){
          slides<<" &   ";
        }
        else{
          slides<<" \\\\";
        }
      }


    }
    slides <<endl;
  }
  
 slides<<"            \\end{tabular}"<<endl;
 slides<<"            }"<<endl;
 slides<<"        \\end{table}"<<endl;
 slides<<"    \\end{minipage}"<<endl;
 slides<<"    \\end{minipage}"<<endl;
 slides<<"\\end{wframe}"<<endl;
 slides<<endl;
 }
/*
  cout <<"Ntags: ";
  for(int o = 1; o <7; o++){ 
  cout<<o-1<<endl;
  cout<<"Histogram: "<<h_ntData->GetTitle()<<"   Entries: "<<h_ntData->GetBinContent(o)<<"     "<<endl;
  cout<<"Histogram: "<<"ntTotBkg"<<"   Entries: "<<h_ntags->GetBinContent(o)<<"     "<<endl;
  cout<<"Histogram: "<<h_ntTotBkg->GetTitle()<<"   Entries: "<<h_ntTotBkg->GetBinContent(o)<<"     "<<endl;
  for(int p = 0; p<v.size(); p++ ){
  cout<<"Histogram: "<<v[p]->GetTitle()<<"   Entries: "<<v[p]->GetBinContent(o)<<"     "<<endl;}}
*/
  pad2->cd();
  //h_Test->Draw("hist");
  hs->SetMinimum(0.001);
  //hs->SetMaximum(1000000);//0.001);
  hs          ->Draw("hist");
  h_ntTotBkg  ->Draw("E2 same");
//  h_ntData    ->Draw("E same");
  h_ntags     ->Draw("hist same");
  hs->SetTitle("N tags   cip:"+s_c_ip+" cta:"+s_c_ta+" cal:"+s_c_al+", "+lifetime+", "+mass);
  hs->GetXaxis()->SetTitle("Number of Tags");
  //hs->GetXaxis()->SetTitleSize(20);
  hs->GetYaxis()->SetTitle("Entries    ");
  hs->GetYaxis()->SetTitleOffset(1.5);
  
  title2->DrawTextNDC(0.06,0.91,"CMS");
  extra2->DrawTextNDC(0.23,0.91,"Preliminary");
  lumi2->DrawTextNDC(0.9,0.91,"16.23/fb (13 TeV)");
  
  TLegend *leg2 = new TLegend(0.4,0.6,0.88,0.85);
  leg2->SetNColumns(2);
  leg2->SetBorderSize(1);
  leg2->SetTextSize(.03);
  TString entries;
  entries.Form("%1.0f",h_ntags->GetEntries());
  //leg2->AddEntry(h_ntags,   entries+" entries", "l");
  leg2->AddEntry(h_ntags,   "Signal"           , "l");
  leg2->AddEntry(h_ntDY,    "Drell-Yan"        , "f");
  leg2->AddEntry(h_ntTTJets,"t#bar{t}+Jets"    , "f");
  leg2->AddEntry(h_ntWJ,    "W+Jets"           , "f");
  leg2->AddEntry(h_ntST,    "Single Top"       , "f");
  leg2->AddEntry(h_ntVV,    "Diboson"          , "f");
  leg2->AddEntry(h_ntVG,    "V#gamma"          , "f");
  leg2->AddEntry(h_ntZH,    "ZH#rightarrowLLbb", "f");
  leg2->AddEntry(h_ntGJets, "#gamma+Jets"      , "f");
  //leg2->AddEntry(h_ntQCD,   "QCD"              , "f");
 // leg2->AddEntry(h_ntData,  DataName           , "lpe");
  leg2->AddEntry(h_ntTotBkg, "MC bkg. stat. err." , "f" );
  leg2->Draw();
  //gStyle->SetOptStat(11);
  gPad->Update();
  gPad->RedrawAxis();
  
  rpad->cd();

  TH1F* h_ntRatio;
  TH1F* h_ntRatiostaterr;
  //h_ntRatio->Sumw2();
  //h_ntRatiostaterr->Sumw2();
  h_ntRatio = (TH1F*) h_ntData->Clone("h_ntRatio");
  h_ntRatio->Divide(h_ntTotBkg);
  h_ntRatio->SetTitle(" ");
  h_ntRatio->SetTitle(" ");
  // Y axis ratio plot settings
  h_ntRatio->GetYaxis()->SetTitleSize(35);
  h_ntRatio->GetYaxis()->SetTitleFont(43);
  h_ntRatio->GetYaxis()->SetTitleOffset(1.55);
  h_ntRatio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ntRatio->GetYaxis()->SetLabelSize(20);
  //h_ntRatio->GetYaxis()->SetNdivisions(-105);
  h_ntRatio->GetYaxis()->SetTitle("Data/MC");
  // X axis ratio plot settings
  h_ntRatio->GetXaxis()->SetTitleSize(40);
  h_ntRatio->GetXaxis()->SetTitleFont(43);
  h_ntRatio->GetXaxis()->SetTitle(h_ntData->GetTitle());
  h_ntRatio->GetXaxis()->SetTitleOffset(4.0);
  h_ntRatio->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
  h_ntRatio->GetXaxis()->SetLabelSize(20);//20
  h_ntRatio->SetMarkerStyle(20);
  h_ntRatio->SetMarkerColor(kRed);
  h_ntRatio->SetMarkerSize(1);
  h_ntRatio->GetYaxis()->SetRangeUser(0,2);

  h_ntRatiostaterr = (TH1F*)h_ntTotBkg->Clone("ntRatiostaterr");
  h_ntRatiostaterr->Divide(h_ntTotBkg);
//  h_ntRatio->Draw("ep"); 
  rpad->Update();
  TLine *line = new TLine(rpad->GetUxmin(), 1, rpad->GetUxmax(), 1);
  line->SetLineWidth(3);
  line->SetLineStyle(9);
  line->SetLineColor(kBlue);
//  line->Draw("sames");
//  h_ntRatiostaterr->Draw("e2 same");
  
  rpad->Update();
  //canvas2->SaveAs(outpath+"h_Test.pdf"); 
 //canvas2->SaveAs(outpath+"/"+nt+"tags"+"_"+lifetime+"_cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+"_sys"+xx+".pdf");
  canvas2->SaveAs(outpath+"/tags"+"_"+mass+"_"+lifetime+"__cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+".png");
}// canvas2->SaveAs(outpath+"/"+nt+"tags"+"_"+lifetime+"_cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+"_sys"+xx+".pdf");
}//bkg non-var
  slides.close();

}

