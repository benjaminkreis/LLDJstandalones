#include <iostream>

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPad.h"

using namespace std;

void print_hist(TH1F* h, TString name, FILE* file){

  fprintf(file, name);
  for(int i=1; i<=h->GetNbinsX(); i++){
    TString toprint = ", ";
    toprint += h->GetBinContent(i);
    fprintf(file, toprint);
  }
  fprintf(file,"\n");

}


void norm(TH1F* h){
  h->Scale(1./h->Integral());
}


void plot_overlay( bool skipZeroTags=false ){
  gStyle->SetOptStat(0);

  TString extra = "";
  if(skipZeroTags) extra = "_skipZeroTags";

  std::vector<TString> leptons;
  //leptons.push_back("ele");
  leptons.push_back("mu");

  std::vector<TString> vars;

  
  vars.push_back("nSelectedAODCaloJet");
  vars.push_back("nSelectedAODCaloJetRW");
  vars.push_back("nSelectedAODCaloJetPTRW");
  //
  vars.push_back("LeadingJet_AODCaloJetPtVar");  
  vars.push_back("LeadingJet_AODCaloJetPtVarRW");  
  vars.push_back("LeadingJet_AODCaloJetPtVarPTRW");
  //
  vars.push_back("nSelectedAODCaloJetTag");
  vars.push_back("nSelectedAODCaloJetTagRW");
  vars.push_back("nSelectedAODCaloJetTagPTRW");
  vars.push_back("nSelectedAODCaloJetTag2DRW");




  for(int l=0; l<leptons.size(); l++){
    for(int v=0; v<vars.size(); v++){

      TFile* f1 = TFile::Open("../plots/wQCD/ZH/GH/"+leptons[l]+"_ZH_"+vars[v]+"_GH.root", "READ");
      TFile* f2 = TFile::Open("../plots/wQCD/DY/GH/"+leptons[l]+"_DY_"+vars[v]+"_GH.root", "READ");
      TFile* f3 = TFile::Open("../plots/wQCD/OffZ/GH/"+leptons[l]+"_OffZ_"+vars[v]+"_GH.root", "READ");
      TFile* f4 = TFile::Open("../plots/wQCD/CRHeavy/GH/NoLepSel_CRHeavy_"+vars[v]+"_GH.root", "READ");
      TFile* f5 = TFile::Open("../plots/wQCD/CRLight/GH/NoLepSel_CRLight_"+vars[v]+"_GH.root", "READ");

      TH1F* h1 = (TH1F*)f1->Get("bkgtotal");
      TH1F* h2 = (TH1F*)f2->Get("bkgtotal");
      TH1F* h3 = (TH1F*)f3->Get("bkgtotal");
      TH1F* h4 = (TH1F*)f4->Get("bkgtotal");
      TH1F* h5 = (TH1F*)f5->Get("bkgtotal");
      //TH1F* h1 = (TH1F*)f1->Get("DY");
      //TH1F* h2 = (TH1F*)f2->Get("DY");
      //TH1F* h3 = (TH1F*)f3->Get("DY");

      if(skipZeroTags){
	h1->SetBinContent(1,0);
	h2->SetBinContent(1,0);
	h3->SetBinContent(1,0);
	h4->SetBinContent(1,0);
	h5->SetBinContent(1,0);
      }
      
      norm(h1);
      norm(h2);
      norm(h3);
      norm(h4);
      norm(h5);

      if(vars[v].Contains("nSelectedAODCaloJetTag")){
	TString fname = "forTed_overlay"; fname+=extra; fname+="_"; fname+=vars[v]; fname+=".csv";
	std::cout << "Writing " << fname<< std::endl;
	FILE *f = fopen (fname, "w");
	print_hist(h1, leptons[l]+"_ZH", f);
	print_hist(h2, leptons[l]+"_DY", f);
	print_hist(h3, leptons[l]+"_OffZ", f);
	print_hist(h4, "CRHeavy", f);
	print_hist(h5, "CRLight", f);
	fclose(f);
      }

      double max=h1->GetMaximum();
      if(h2->GetMaximum()>max)max=h2->GetMaximum();
      if(h3->GetMaximum()>max)max=h3->GetMaximum();
      if(h4->GetMaximum()>max)max=h4->GetMaximum();
      if(h5->GetMaximum()>max)max=h5->GetMaximum();
      h1->SetMaximum(max*1.25);
      h1->SetMinimum(1e-10);

      h1->SetLineWidth(2);
      h2->SetLineWidth(2);
      h3->SetLineWidth(2);
      h4->SetLineWidth(2);
      h5->SetLineWidth(2);
      h1->SetLineColor(kRed);
      h2->SetLineColor(kBlue);
      h3->SetLineColor(kGreen);
      h4->SetLineColor(kOrange);
      h5->SetLineColor(kViolet);
      
      TCanvas* c = new TCanvas("c", "c", 640, 480);
      h1->Draw();
      h2->Draw("SAME");
      h3->Draw("SAME");
      h4->Draw("SAME");
      h5->Draw("SAME");

      TLegend *leg;
      leg = new TLegend(0.6,0.7,0.88,0.88);
      leg->SetBorderSize(0);
      leg->SetFillColor(kWhite);
      leg->AddEntry(h1, "ZH");
      leg->AddEntry(h2, "DY");
      leg->AddEntry(h3, "OffZ");
      leg->AddEntry(h4, "CRHeavy");
      leg->AddEntry(h5, "CRLight");
      leg->Draw();
      c->SaveAs("overlay_"+leptons[l]+"_"+vars[v]+extra+".pdf");

      gPad->SetLogy();
      c->SaveAs("overlay_"+leptons[l]+"_"+vars[v]+extra+"_log.pdf");

    }//v
  }//l
  
}
