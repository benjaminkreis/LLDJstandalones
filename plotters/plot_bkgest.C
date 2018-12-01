#include <iostream>
#include <cmath>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"

void print(TH1F* h){

  cout << h->GetName() << endl;
  for(int i=1; i<=h->GetNbinsX(); i++){
    cout << h->GetBinContent(i) << endl;
  }

}


void make_plot(TString bkg_est_name, TH1F* h_Totbkg, TH1F* h_Totbkg_bkgest, TH1F* h_pull, 
	       std::vector<float> x, std::vector<float> bkgest, std::vector<float> xl, std::vector<float> xr, 
	       std::vector<float> bkgest_DownError, std::vector<float> bkgest_UpError){

  //Build TGraphAsymmErrors
  TGraphAsymmErrors* gr_est = new TGraphAsymmErrors(x.size(), &(x[0]), &(bkgest[0]), &(xl[0]), &(xr[0]), &(bkgest_DownError[0]), &(bkgest_UpError[0]));
  
  print(h_Totbkg);
  print(h_Totbkg_bkgest);

  //Style
  h_Totbkg->SetTitle("");
  h_Totbkg->GetYaxis()->SetTitle("Events");
  h_Totbkg->SetLineWidth(2);
  h_Totbkg_bkgest->SetLineWidth(2);
  h_Totbkg->SetLineColor(kBlack);
  h_Totbkg_bkgest->SetLineColor(kRed);

  h_Totbkg->GetYaxis()->SetRangeUser(1e-5, 1e7);

  gr_est->SetMarkerColor(kRed);
  gr_est->SetLineWidth(2);
  gr_est->SetMarkerSize(1);
  gr_est->SetMarkerStyle(8);
  gr_est->SetLineColor(kRed);

  h_pull->SetTitle("");
  h_pull->SetStats(0);
  h_pull->SetMarkerColor(kBlack);
  h_pull->SetLineWidth(2);
  h_pull->SetMarkerSize(1);
  h_pull->SetMarkerStyle(8);

  // Y axis ratio plot settings
  h_pull->GetYaxis()->SetTitle("pull");
  h_pull->GetYaxis()->SetNdivisions(505);
  h_pull->GetYaxis()->SetTitleSize(20);
  h_pull->GetYaxis()->SetTitleFont(43);
  h_pull->GetYaxis()->SetTitleOffset(1.55);
  h_pull->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_pull->GetYaxis()->SetLabelSize(20);
  h_pull->GetYaxis()->SetRangeUser(-1, 1.2);

  // X axis ratio plot settings
  h_pull->GetXaxis()->SetTitleSize(20);
  h_pull->GetXaxis()->SetTitleFont(43);
  h_pull->GetXaxis()->SetTitleOffset(4.);
  h_pull->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_pull->GetXaxis()->SetLabelSize(20);
  h_pull->GetXaxis()->SetTitle("Tag Multiplicity");
  

  TCanvas c("c", "c", 800, 800);
  TPad *pad1 = new TPad("pd1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();       // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  h_Totbkg->SetStats(0);    // No statistics on upper plot
  gPad->SetLogy();
  h_Totbkg->Draw("HIST E1");
  gr_est->Draw("P");

  //Legend
  TLegend *leg = new TLegend(0.6,0.65,0.85,0.8);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->AddEntry(h_Totbkg, "True", "le");
  leg->AddEntry(gr_est, "Estimated", "pe");
  leg->Draw();

  gPad->Update();
  c.cd();
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();         // pad2 becomes the current pad
  h_pull->Draw("p");

  c.SaveAs("rp_"+bkg_est_name+".pdf");  

}



///////////////
//    1D
///////////////

void plot_bkgest_1d(){

  TString bkg_est_name = "h_bkgest_pt";
 
  TString filename_eff    = "feff_ZH.root";
  TString filename_bkgest = "fout_ZH_bkgest.root";
  TString filename_bkg    = "fout_ZH.root";

  TFile* file_eff    = TFile::Open(filename_eff, "READ");
  TFile* file_bkg    = TFile::Open(filename_bkg, "READ");
  TFile* file_bkgest = TFile::Open(filename_bkgest, "READ");

  TH1F* h_UpError   = (TH1F*)file_eff->Get("h_UpError_mu_ZH_AllJets_AODCaloJetPtVar");
  TH1F* h_DownError = (TH1F*)file_eff->Get("h_DownError_mu_ZH_AllJets_AODCaloJetPtVar");

  TH1F* h_Totbkg = (TH1F*)file_bkg->Get("h_mu_ZH_nSelectedAODCaloJetTag");

  TH1F* h_Totbkg_bkgest = (TH1F*)file_bkgest->Get(bkg_est_name);
  std::vector<TH1F*> h_sys;
  h_sys.push_back( (TH1F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_0") );
  h_sys.push_back( (TH1F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_1") );
  h_sys.push_back( (TH1F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_2") );
  h_sys.push_back( (TH1F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_3") );
  h_sys.push_back( (TH1F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_4") );
  h_sys.push_back( (TH1F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVar_sys_5") ); 

  //Vectors for TGraphAsymmErrors
  std::vector<float> x, xl, xr;
  std::vector<float> bkgest;
  std::vector<float> bkgest_UpError;
  std::vector<float> bkgest_DownError;
  
  TH1F* h_pull = new TH1F("h_pull", "h_pull", 6, -0.5, 5.5);

  //Compute and fill errors
  for(int i=0; i<6; i++){

    double sum_up=0;
    double sum_down=0;
    for(int b=0; b<=h_UpError->GetNbinsX()+1; b++){//include underflow overflow
      double term_to_square_up = h_UpError->GetBinContent(b)*h_sys.at(i)->GetBinContent(b);
      sum_up += term_to_square_up*term_to_square_up;
      double term_to_square_down = h_DownError->GetBinContent(b)*h_sys.at(i)->GetBinContent(b);
      sum_down += term_to_square_down*term_to_square_down;
      //std::cout << "1D -- sum_up: " << sum_up << ", sum_down: " << sum_down << std::endl;
    }
    x.push_back(i);
    xl.push_back(0);
    xr.push_back(0);
    bkgest.push_back(h_Totbkg_bkgest->GetBinContent(i+1));
    bkgest_UpError.push_back(sqrt(sum_up));
    bkgest_DownError.push_back(sqrt(sum_down));
    
    float pull = 0;
    float est = h_Totbkg_bkgest->GetBinContent(i+1);
    float truev =  h_Totbkg->GetBinContent(i+1);
    if( est < truev ){
      pull = (est-truev)/sqrt( sum_up + h_Totbkg->GetBinError(i+1)*h_Totbkg->GetBinError(i+1) );
    }
    else{
      pull = (est-truev)/sqrt( sum_down + h_Totbkg->GetBinError(i+1)*h_Totbkg->GetBinError(i+1) );
    }
    cout << "pull : " << pull << endl;
    if(i==0) pull = -999;
    h_pull->SetBinContent(i+1, pull);
  }
  
  make_plot(bkg_est_name, h_Totbkg, h_Totbkg_bkgest, h_pull, 
	       x, bkgest, xl, xr, 
	       bkgest_DownError, bkgest_UpError);

  file_eff->Close();
  file_bkg->Close();
  file_bkgest->Close();
}


///////////////
//    2D
///////////////

void plot_bkgest_2d(){

  TString bkg_est_name = "h_bkgest_pteta";
 
  TString filename_eff    = "feff_ZH.root";
  TString filename_bkgest = "fout_ZH_bkgest.root";
  TString filename_bkg    = "fout_ZH.root";

  TFile* file_eff    = TFile::Open(filename_eff, "READ");
  TFile* file_bkg    = TFile::Open(filename_bkg, "READ");
  TFile* file_bkgest = TFile::Open(filename_bkgest, "READ");

  TH2F* h_UpError   = (TH2F*)file_eff->Get("h_UpError_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar");
  TH2F* h_DownError = (TH2F*)file_eff->Get("h_DownError_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar");

  TH1F* h_Totbkg = (TH1F*)file_bkg->Get("h_mu_ZH_nSelectedAODCaloJetTag");

  TH1F* h_Totbkg_bkgest = (TH1F*)file_bkgest->Get(bkg_est_name);
  std::vector<TH2F*> h_sys;
  h_sys.push_back( (TH2F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_0") );
  h_sys.push_back( (TH2F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_1") );
  h_sys.push_back( (TH2F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_2") );
  h_sys.push_back( (TH2F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_3") );
  h_sys.push_back( (TH2F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_4") );
  h_sys.push_back( (TH2F*)file_bkgest->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar_sys_5") ); 

  //Vectors for TGraphAsymmErrors
  std::vector<float> x, xl, xr;
  std::vector<float> bkgest;
  std::vector<float> bkgest_UpError;
  std::vector<float> bkgest_DownError;
  
  TH1F* h_pull = new TH1F("h_pull", "h_pull", 6, -0.5, 5.5);

  //Compute and fill errors
  for(int i=0; i<6; i++){

    double sum_up=0;
    double sum_down=0;
    for(int b=0; b<h_UpError->GetSize(); b++){
      
      //if(h_UpError->IsBinUnderflow(b) || h_UpError->IsBinOverflow(b)) continue;
      //include underflow/overflow

      double term_to_square_up = h_UpError->GetBinContent(b)*h_sys.at(i)->GetBinContent(b);
      sum_up += term_to_square_up*term_to_square_up;
      double term_to_square_down = h_DownError->GetBinContent(b)*h_sys.at(i)->GetBinContent(b);
      sum_down += term_to_square_down*term_to_square_down;
      //std::cout << "2D -- " << sum_up << " " << sum_down << std::endl;
    }
    x.push_back(i);
    xl.push_back(0);
    xr.push_back(0);
    bkgest.push_back(h_Totbkg_bkgest->GetBinContent(i+1));
    bkgest_UpError.push_back(sqrt(sum_up));
    bkgest_DownError.push_back(sqrt(sum_down));
    
    float pull = 0;
    float est = h_Totbkg_bkgest->GetBinContent(i+1);
    float truev =  h_Totbkg->GetBinContent(i+1);
    if( est < truev ){
      pull = (est-truev)/sqrt( sum_up + h_Totbkg->GetBinError(i+1)*h_Totbkg->GetBinError(i+1) );
    }
    else{
      pull = (est-truev)/sqrt( sum_down + h_Totbkg->GetBinError(i+1)*h_Totbkg->GetBinError(i+1) );
    }
    cout << "pull : " << pull << endl;
    if(i==0) pull = -999;
    h_pull->SetBinContent(i+1, pull);
  }
  
  make_plot(bkg_est_name, h_Totbkg, h_Totbkg_bkgest, h_pull, 
	       x, bkgest, xl, xr, 
	       bkgest_DownError, bkgest_UpError);

  file_eff->Close();
  file_bkg->Close();
  file_bkgest->Close();
}




void plot_bkgest(){
  
  plot_bkgest_1d();
  plot_bkgest_2d();
  
}
