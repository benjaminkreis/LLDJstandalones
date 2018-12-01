#include <iostream>

#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TMath.h"


void plot_a_eff_1d(TH1F* h_num, TH1F* h_den, float max, TString name, TFile* f_out){

  TH1F* h_up = (TH1F*)h_num->Clone();
  h_up->Reset();
  h_up->SetName("h_UpError_"+name);
  TH1F* h_down = (TH1F*)h_num->Clone();
  h_down->Reset();
  h_down->SetName("h_DownError_"+name);

  for(int b=0; b<h_num->GetSize(); b++){

    //if(h_num->IsBinUnderflow(b) || h_num->IsBinOverflow(b)) continue;
    //Want underflow and overflow

    int xbin, ybin, zbin;
    h_num->GetBinXYZ(b, xbin, ybin, zbin);

    //Get errors with dumb trick, using one bin hists and TGraphAsymmErrors
    TH1F h_num_onebin("h_num_onebin", "h_num_onebin", 1, 0, 1);
    h_num_onebin.SetBinContent(1, h_num->GetBinContent(b));
    h_num_onebin.SetBinError(1, h_num->GetBinError(b));
    TH1F h_den_onebin("h_den_onebin", "h_den_onebin", 1, 0, 1);
    h_den_onebin.SetBinContent(1, h_den->GetBinContent(b));
    h_den_onebin.SetBinError(1, h_den->GetBinError(b));
    TGraphAsymmErrors* gr_eff = new TGraphAsymmErrors();
    gr_eff->SetName("gr_eff_"+name);
    gr_eff->Divide(&h_num_onebin, &h_den_onebin, "cl=0.683 b(1,1) mode");

    h_up->SetBinContent(xbin, gr_eff->GetErrorYhigh(0));
    h_down->SetBinContent(xbin, gr_eff->GetErrorYlow(0));
  }
  

  //Histogram of mistag rate
  TH1F* h_eff = (TH1F*)h_num->Clone();
  h_eff->Divide(h_den);
  h_eff->SetName("h_eff_"+name);

  //Graph of mistag rate
  TGraphAsymmErrors* gr_eff = new TGraphAsymmErrors();
  gr_eff->SetName("gr_eff_"+name);
  gr_eff->Divide(h_num, h_den, "cl=0.683 b(1,1) mode");
  int n_gr = gr_eff->GetN();
  //--Style
  gr_eff->SetLineWidth(2);
  gr_eff->SetMarkerSize(1);
  gr_eff->SetMarkerStyle(8);
  gr_eff->SetMarkerColor(kGreen+1);
  gr_eff->SetLineColor(kGreen+1);
  gr_eff->SetTitle("Mistag rate " + name);
  gr_eff->GetXaxis()->SetTitle("");
  gr_eff->GetYaxis()->SetTitle("Mistag rate");
  //--Draw 
  TCanvas* c_eff = new TCanvas("c_eff_"+name, "c_eff_"+name, 640, 480);
  gr_eff->Draw("AP");
  gr_eff->GetYaxis()->SetRangeUser(0, max);
  gPad->Update();
  //h_up->Draw("HIST E");
  c_eff->Print("gr_eff_"+name+".pdf");

  //Write output
  f_out->cd();
  gr_eff->Write();
  h_num->Write();
  h_den->Write();
  h_eff->Write();
  h_up->Write();
  h_down->Write();
}


void plot_a_eff_2d(TH2F* h_num, TH2F* h_den, float max, TString name, TFile* f_out){
  
  TH1F* h_up = (TH1F*)h_num->Clone();
  h_up->Reset();
  h_up->SetName("h_UpError_"+name);
  TH1F* h_down = (TH1F*)h_num->Clone();
  h_down->Reset();
  h_down->SetName("h_DownError_"+name);

  for(int b=0; b<h_num->GetSize(); b++){

    //if(h_num->IsBinUnderflow(b) || h_num->IsBinOverflow(b)) continue;
    //Want underflow and overflow

    int xbin, ybin, zbin;
    h_num->GetBinXYZ(b, xbin, ybin, zbin);

    //Get errors with dumb trick, using one bin hists and TGraphAsymmErrors
    TH1F h_num_onebin("h_num_onebin", "h_num_onebin", 1, 0, 1);
    h_num_onebin.SetBinContent(1, h_num->GetBinContent(b));
    h_num_onebin.SetBinError(1, h_num->GetBinError(b));
    TH1F h_den_onebin("h_den_onebin", "h_den_onebin", 1, 0, 1);
    h_den_onebin.SetBinContent(1, h_den->GetBinContent(b));
    h_den_onebin.SetBinError(1, h_den->GetBinError(b));
    TGraphAsymmErrors* gr_eff = new TGraphAsymmErrors();
    gr_eff->SetName("gr_eff_"+name);
    gr_eff->Divide(&h_num_onebin, &h_den_onebin, "cl=0.683 b(1,1) mode");

    h_up->SetBinContent(xbin, ybin, gr_eff->GetErrorYhigh(0));
    h_down->SetBinContent(xbin, ybin, gr_eff->GetErrorYlow(0));
  }

  //Histogram of mistag rate
  TH1F* h_eff = (TH1F*)h_num->Clone();
  h_eff->Divide(h_den);
  h_eff->SetName("h_eff_"+name);

  //Draw graph
  TCanvas* c_eff = new TCanvas("c_eff_"+name, "c_eff_"+name, 640, 480);
  h_eff->Draw("COLZ");
  c_eff->Print("gr_eff_"+name+".pdf");

  //Write output
  f_out->cd();
  h_num->Write();
  h_den->Write();
  h_eff->Write();
  h_up->Write();
  h_down->Write();

}


void plot_eff(TString region){

  //Note: this needs to be generalized to multidimensional histograms

  TFile* f_in  = TFile::Open("fout_"+region+".root", "READ");
  TFile* f_out = TFile::Open("feff_"+region+".root", "RECREATE");

  std::vector<TString> num_name;
  std::vector<TString> den_name;
  std::vector<TString> name;
  std::vector<float> max;


  //Pt
  num_name.push_back("h_mu_"+region+"_AllTags_AODCaloJetPtVar_Tag0");
  den_name.push_back("h_mu_"+region+"_AllJets_AODCaloJetPtVar");
  name.push_back("mu_"+region+"_AllJets_AODCaloJetPtVar");
  max.push_back(0.006);


  /*
  //dR
  num_name.push_back("h_Totbkg_mu_"+region+"_AllTags_AODCaloJetMinDR_Tag0");
  den_name.push_back("h_Totbkg_mu_"+region+"_AllJets_AODCaloJetMinDR");
  name.push_back("mu_"+region+"_AllJets_AODCaloJetMinDR");
  max.push_back(0.01);
  */

  /*
  //Eta
  num_name.push_back("h_Totbkg_mu_"+region+"_AllTags_AODCaloJetAbsEta_Tag0");
  den_name.push_back("h_Totbkg_mu_"+region+"_AllJets_AODCaloJetAbsEta");
  name.push_back("mu_"+region+"_AllJets_AODCaloJetAbsEta");
  max.push_back(0.01);
  */

  /*
  //Nt
  num_name.push_back("h_Totbkg_mu_"+region+"_AllTags_AODCaloJetNCleanMatchedTracks_Tag0");
  den_name.push_back("h_Totbkg_mu_"+region+"_AllJets_AODCaloJetNCleanMatchedTracks");
  name.push_back("mu_"+region+"_AllJets_AODCaloJetNCleanMatchedTracks");
  max.push_back(0.04);
  */

  for(unsigned int i=0; i<num_name.size(); i++){
    
    TH1F* h_num = (TH1F*)f_in->Get(num_name.at(i));
    TH1F* h_den = (TH1F*)f_in->Get(den_name.at(i));
    
    plot_a_eff_1d(h_num, h_den, max.at(i), name.at(i), f_out);

  }
  

  //////////////
  // 2D
  //////////////
  num_name.clear();
  den_name.clear();
  name.clear();
  max.clear();

  
  num_name.push_back("h_mu_"+region+"_AllTags_AODCaloJetPtVarAbsEtaVar_Tag0");
  den_name.push_back("h_mu_"+region+"_AllJets_AODCaloJetPtVarAbsEtaVar");
  name.push_back("mu_"+region+"_AllJets_AODCaloJetPtVarAbsEtaVar");
  max.push_back(0.006);

  for(unsigned int i=0; i<num_name.size(); i++){
    
    TH2F* h_num = (TH2F*)f_in->Get(num_name.at(i));
    TH2F* h_den = (TH2F*)f_in->Get(den_name.at(i));
    
    plot_a_eff_2d(h_num, h_den, max.at(i), name.at(i), f_out);

  }

  f_in->Close();
  f_out->Close();

}
