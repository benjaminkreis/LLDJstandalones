#include <iostream>

#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TMath.h"

float error_on_int(TH1F* h, int min, int max){
  
  float error = 0; 
  for(int i=min; i<=max; i++){
    float bin_error  = h->GetBinError(i);
    error += bin_error * bin_error;
  }

  error = TMath::Sqrt(error);
  return error;
}

void plot_a_ROC(TH1F* h_sig, TH1F* h_bkg, TString name){

  //Unit norm shape plot
  //////////////////////////////

  TCanvas * c_shape = new TCanvas("c_shape", "c_shape", 640, 480);
  h_sig->SetLineWidth(2);
  h_sig->SetLineColor(kRed);
  h_bkg->SetLineWidth(2);
  h_bkg->SetLineColor(kBlue);
  h_bkg->SetTitle(name);
  h_bkg->GetXaxis()->SetTitle("Pt OSSF");
  h_bkg->GetYaxis()->SetTitle("A.U.");
  h_bkg->DrawNormalized("HIST E");
  h_sig->DrawNormalized("HIST E SAME");
  c_shape->Print("c_shape_"+name+".pdf");

  
  // ROC and Sensitivity plots
  ///////////////////////////////

  const int nbins = h_sig->GetNbinsX();

  double sig_tot = h_sig->Integral(1, nbins+1);
  //double sig_tot_err = error_on_int(h_sig, 1, nbins+1);

  double bkg_tot = h_bkg->Integral(1, nbins+1);
  //double bkg_tot_err = error_on_int(h_bkg, 1, nbins+1);

  double sig_eff[nbins];
  double bkg_eff[nbins];
  double pt_cut[nbins];
  double sensitivity[nbins];
  for(int i=1; i<=nbins; i++){

    pt_cut[i] = h_sig->GetBinLowEdge(i);
    
    double sig = h_sig->Integral(i, nbins+1);
    double bkg = h_bkg->Integral(i, nbins+1);

    sig_eff[i] = sig / sig_tot; 
    bkg_eff[i] = bkg / bkg_tot; 
    sensitivity[i] = sig / TMath::Sqrt(sig+2*bkg);

  }

  TGraph* gr_roc = new TGraph(nbins, sig_eff, bkg_eff);
  gr_roc->SetLineWidth(2);
  gr_roc->SetMarkerSize(1);
  gr_roc->SetMarkerStyle(8);
  gr_roc->SetMarkerColor(kGreen+1);
  gr_roc->SetTitle("ROC " + name);
  gr_roc->GetXaxis()->SetTitle("sig eff");
  gr_roc->GetYaxis()->SetTitle("bkg eff");
  TCanvas* c_roc = new TCanvas("c_roc", "c_roc", 640, 480);
  gr_roc->Draw("AP");
  c_roc->Print("gr_roc_"+name+".pdf");

  TGraph* gr_sen = new TGraph(nbins, pt_cut, sensitivity);
  gr_sen->SetLineWidth(2);
  gr_sen->SetLineColor(kGreen+1);
  gr_sen->SetTitle("Sensitivity " + name);
  gr_sen->GetXaxis()->SetTitle("Pt OSSF Threshold");
  gr_sen->GetYaxis()->SetTitle("S/sqrt(S+2*B)");
  TCanvas* c_sen = new TCanvas("c_sen", "c_sen", 640, 480);
  gr_sen->Draw("ACP");
  c_sen->Print("gr_sen_"+name+".pdf");

}


void plot_roc(TString region = "ZH"){

  std::vector<TString> sig_f_names;
  sig_f_names.push_back("ZH_HToSSTobbbb_MS15_ctauS10_"+region+"_histograms");
  sig_f_names.push_back("ZH_HToSSTobbbb_MS55_ctauS10_"+region+"_histograms");

  TFile* f_bkg = TFile::Open("fout_"+region+".root", "READ");
  TH1F* h_bkg = (TH1F*)f_bkg->Get("h_Totbkg_mu_"+region+"_AOD_dilepton_Pt");

  for(unsigned int i=0; i<sig_f_names.size(); i++){
    
    TFile* f_sig = TFile::Open("../roots/may7/"+sig_f_names.at(i)+".root", "READ");
    TH1F* h_sig = (TH1F*)f_sig->Get("h_mu_"+region+"_AOD_dilepton_Pt");
    
    plot_a_ROC(h_sig, h_bkg, sig_f_names.at(i));

    f_sig->Close();
  }
  
  f_bkg->Close();

}
