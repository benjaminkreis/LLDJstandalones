#include <iostream>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPad.h"

using namespace std;

void norm(TH1F* h){
  h->Scale(1./h->Integral());
}

void norm(TH2F* h){
  h->Scale(1./h->Integral());
}

void plot_njet_weight(){
  gStyle->SetOptStat(0);

  TFile* fout = TFile::Open("f_njet_weight.root","RECREATE");

  std::vector<TString> lepreg;
  lepreg.push_back("mu_DY");
  lepreg.push_back("mu_OffZ");
  lepreg.push_back("NoLepSel_CRLight");
  lepreg.push_back("NoLepSel_CRHeavy");

  std::vector<TString> reg;
  reg.push_back("DY");
  reg.push_back("OffZ");
  reg.push_back("CRLight");
  reg.push_back("CRHeavy");

  for(int i=0; i<lepreg.size(); i++){

    TFile* f1 = TFile::Open("../plots/wQCD/ZH/GH/mu_ZH_nSelectedAODCaloJet_GH.root", "READ");
    TFile* f2 = TFile::Open("../plots/wQCD/"+reg[i]+"/GH/"+lepreg[i]+"_nSelectedAODCaloJet_GH.root", "READ");
    
    TH1F* h1 = (TH1F*)f1->Get("bkgtotal");
    TH1F* h2 = (TH1F*)f2->Get("bkgtotal");
    
    norm(h1);
    norm(h2);
    
    fout->cd();
    TH1F* hr = (TH1F*)h1->Clone("h_njet_weight_mu_ZH_over_"+lepreg[i]);
    hr->Divide(h2);
    hr->Write();
  
    f1->Close();
    f2->Close();
  }  

  for(int i=0; i<lepreg.size(); i++){

    TFile* f1 = TFile::Open("../plots/wQCD/ZH/GH/mu_ZH_LeadingJet_AODCaloJetPtVar_GH.root", "READ");
    TFile* f2 = TFile::Open("../plots/wQCD/"+reg[i]+"/GH/"+lepreg[i]+"_LeadingJet_AODCaloJetPtVar_GH.root", "READ");
    
    TH1F* h1 = (TH1F*)f1->Get("bkgtotal");
    TH1F* h2 = (TH1F*)f2->Get("bkgtotal");
    
    norm(h1);
    norm(h2);
    
    fout->cd();
    TH1F* hr = (TH1F*)h1->Clone("h_pt_weight_mu_ZH_over_"+lepreg[i]);
    hr->Divide(h2);
    hr->Write();
  
    f1->Close();
    f2->Close();
  }  


  for(int i=0; i<lepreg.size(); i++){

    TFile* f1 = TFile::Open("../plots/wQCD/ZH/GH/mu_ZH_htaodcalojets_njets_GH.root", "READ");
    TFile* f2 = TFile::Open("../plots/wQCD/"+reg[i]+"/GH/"+lepreg[i]+"_htaodcalojets_njets_GH.root", "READ");
    
    TH2F* h1 = (TH2F*)f1->Get("bkgtotal");
    TH2F* h2 = (TH2F*)f2->Get("bkgtotal");
    
    norm(h1);
    norm(h2);
    
    fout->cd();
    TH2F* hr = (TH2F*)h1->Clone("h_htnjets_weight_mu_ZH_over_"+lepreg[i]);
    hr->Divide(h2);
    hr->Write();
  
    f1->Close();
    f2->Close();
  }  

  
  fout->Close();

}
