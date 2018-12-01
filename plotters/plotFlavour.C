#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TH1F.h"
#include "TString.h"
#include "TStyle.h"
#include "TPad.h"

#include <iostream>

void one_plotFlavour(TString varname, TString region, TString path){
  
  bool blind=false;
  if(region.Contains("ZH")) blind=true;
  
  TFile* f_data = TFile::Open(path+"/"+region+"/GH/"+region+"_"+varname+"_GH.root","READ");
  TH1F* h_data = (TH1F*)f_data->Get("Data");
  TH1F* h_totalmc = (TH1F*)f_data->Get("bkgtotal");

  TFile* f_mc_0b = TFile::Open(path+"/"+region+"/GH/"+region+"_"+varname+"_0b_GH.root","READ");
  TH1F* h_mc_0b = (TH1F*)f_mc_0b->Get("bkgtotal");

  TFile* f_mc_1b = TFile::Open(path+"/"+region+"/GH/"+region+"_"+varname+"_1b_GH.root","READ");
  TH1F* h_mc_1b = (TH1F*)f_mc_1b->Get("bkgtotal");

  TFile* f_mc_2b = TFile::Open(path+"/"+region+"/GH/"+region+"_"+varname+"_2b_GH.root","READ");
  TH1F* h_mc_2b = (TH1F*)f_mc_2b->Get("bkgtotal");
  
  //cross check
  TH1F* h_add = (TH1F*)h_mc_0b->Clone("h_add");
  h_add->Add(h_mc_1b);
  h_add->Add(h_mc_2b);
  for(int i=1; i<=h_add->GetNbinsX(); i++){
    std::cout << "Bin " << i << " 0b: " << h_mc_0b->GetBinContent(i) << " 1b: " << h_mc_1b->GetBinContent(i) << " 2b: " << h_mc_2b->GetBinContent(i) << " Total: " << h_totalmc->GetBinContent(i) << ", Added: " << h_add->GetBinContent(i) << std::endl;
  }

  
  //Style
  h_data  -> SetLineColor(kBlack);
  h_data  -> SetMarkerStyle(8);
  h_data  -> SetMarkerSize(1);
  h_data  -> SetLineWidth(3);
  h_mc_0b->SetFillColor(kAzure+1);
  h_mc_0b->SetFillStyle(1001);
  h_mc_1b->SetFillColor(kViolet+1);
  h_mc_1b->SetFillStyle(1001);
  h_mc_2b->SetFillColor(kPink+7);
  h_mc_2b->SetFillStyle(1001);

  TCanvas c("c", "c", 640, 480);
  gStyle->SetOptStat(0);
  gPad->SetLogy(1);
  THStack *bgstack = new THStack("bgstack","");
  bgstack->Add(h_mc_0b);
  bgstack->Add(h_mc_1b);
  bgstack->Add(h_mc_2b);
  bgstack->SetMinimum(0.1);
  bgstack->Draw("hist");
  if(!blind) h_data->Draw("same E");
  c.SaveAs("c_flavor_"+region+"_"+varname+".pdf");

}


void plotFlavour(){

  TString varname = "nSelectedAODCaloJetTag";
  TString path = "../plots/PhoPT170_k1p26/";

  one_plotFlavour(varname, "OnePho", path);
  one_plotFlavour(varname, "EleMuOSOF", path);
  one_plotFlavour(varname, "TwoMuZH", path);
  one_plotFlavour(varname, "TwoEleZH", path);


}
