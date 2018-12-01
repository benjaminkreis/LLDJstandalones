#include <iostream>
#include <stdlib.h>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"

using namespace std;


// Global
std::vector<TString> samples;
std::vector<TFile*> files;
bool debug = false;
TFile* fout;


void print_hist_1d(TH1F* h){
  
  for(int i=1; i<=h->GetNbinsX(); i++){
    std::cout << h->GetBinContent(i) << " ";
  }
  std::cout << std::endl;

}


void plot_added_1d(TString variable){

  std::cout << "plot_added_1d:: adding " << variable << std::endl;

  //Histograms
  std::vector<TH1F*> histograms;
  for(unsigned int s=0; s<samples.size(); s++){
    TH1F* h = (TH1F*) files[s]->Get(variable);
    if(debug) std::cout << "  get " << samples[s] << ": " << h << std::endl;
    histograms.push_back(h);
  }
  
  //Add
  TH1F* hadd = histograms[0];
  for(unsigned int s=1; s<samples.size(); s++){
    hadd->Add(histograms[s]);
  }

  //Output
  fout->cd();
  hadd->Write();

}//plot_added_1d


void plot_stacked_1d(TString variable){
  
  //for this, should make samples vector a vector of classes with color, group name, human name, etc.

  //Histograms
  std::vector<TH1F*> histograms;
  for(unsigned int s=0; s<samples.size(); s++){
    TH1F* h = (TH1F*) files[s]->Get(variable);
    histograms.push_back(h);
  }

  //Make groups

  //Stack
  THStack *bgstack = new THStack("bgstack","");
  for(unsigned int s=0; s<samples.size(); s++){
  }
}


void plot_added_2d(TString variable){

  std::cout << "plot_added_2d:: adding " << variable << std::endl;

  //Histograms
  std::vector<TH2F*> histograms;
  for(unsigned int s=0; s<samples.size(); s++){
    TH2F* h = (TH2F*) files[s]->Get(variable);
    if(debug) std::cout << "  get " << samples[s] << ": " << h << std::endl;
    histograms.push_back(h);
  }
  
  //Add
  TH2F* hadd = histograms[0];
  for(unsigned int s=1; s<samples.size(); s++){
    hadd->Add(histograms[s]);
  }

  //Output
  fout->cd();
  hadd->Write();

}//plot_added_2d


void plot_added(bool drawBkgEst = false){

  TString aversion = TString(getenv("aversion"));
  
  //Samples
  samples.push_back("DYJetsToLL_M-50");
  samples.push_back("ST_s-channel_4f_leptonDecays");
  samples.push_back("ST_t-channel_antitop_4f_inclusiveDecays");
  samples.push_back("ST_t-channel_top_4f_inclusiveDecays");
  samples.push_back("ST_tW_antitop_5f_NoFullyHadronicDecays");
  samples.push_back("ST_tW_top_5f_NoFullyHadronicDecays");
  samples.push_back("TTtoLL");
  samples.push_back("TTtoLfromTbar");
  samples.push_back("TTtoLfromT");
  samples.push_back("WJetsToLNu");
  samples.push_back("WWTo2L2Nu");
  samples.push_back("WWToLNuQQ");
  samples.push_back("WZTo1L3Nu");
  samples.push_back("WZTo3LNu");
  samples.push_back("WZToLNu2QorQQ2L");
  samples.push_back("ZZTo2L2Nu");
  samples.push_back("ZZTo2L2Q");
  samples.push_back("ZZTo2Q2Nu");
  samples.push_back("ZZTo4L");
  samples.push_back("ZGTo2LG");
  samples.push_back("WGToLNuG");
  samples.push_back("ggZH_HToBB_ZToLL");
  samples.push_back("ZH_HToBB_ZToLL");
  
  //Open files
  if(drawBkgEst){
    fout = TFile::Open("fout_ZH_bkgest.root", "RECREATE");
  }
  else{
    fout = TFile::Open("fout_ZH.root", "RECREATE");
  }
  for(unsigned int s=0; s< samples.size(); s++){
    TFile* f;
    if(drawBkgEst){
      f = TFile::Open("../roots/"+aversion+"/"+samples[s]+"_BkgEst.root", "READ");
    }
    else{
      f = TFile::Open("../roots/"+aversion+"/"+samples[s]+"_ZH_histograms.root", "READ");
    }
    files.push_back(f);
  }
  
  //1D
  std::vector<TString> variables;
  if(drawBkgEst){
    variables.push_back("h_bkgest_pt");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_0");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_1");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_2");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_3");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_4");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_5");
    variables.push_back("h_bkgest_pteta");
  }  
  else{
    variables.push_back("h_mu_ZH_AllTags_AODCaloJetPtVar_Tag0");
    variables.push_back("h_mu_ZH_AllJets_AODCaloJetPtVar");
    variables.push_back("h_mu_ZH_nSelectedAODCaloJetTag");
  }
  for(unsigned int v=0; v<variables.size(); v++){
    plot_added_1d(variables[v]);
  }

  //2D
  variables.clear();
  if(drawBkgEst){
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_0");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_1");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_2");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_3");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_4");
    variables.push_back("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_5");
  }
  else{
    variables.push_back("h_mu_ZH_AllTags_AODCaloJetPtVarAbsEtaVar_Tag0");
    variables.push_back("h_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar");
  }
  for(unsigned int v=0; v<variables.size(); v++){
    plot_added_2d(variables[v]);
  }

  //Close
  for(unsigned int s=0; s< samples.size(); s++){
    files[s]->Close();
  }
  fout->Close();

}
