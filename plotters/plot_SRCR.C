#include <iostream>

#include "TString.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

using namespace std;



void print_hist(TString name, TH1* h){
  cout << "Printing " << name << endl;
  for(int i=1; i<=h->GetNbinsX(); i++){
    cout << i << " " << h->GetBinContent(i) << " +- " << h->GetBinError(i) << endl;
  }
  cout << endl;
  
}



////////////////////////
////////////////////////
////////////////////////



void compare_tt(TString leptonChan, TString alt = "", bool addST=false){
  
  TString STstring = "";
  if(addST) STstring = "plusST";

  std::vector<TString> vars;
  vars.push_back("nSelectedAODCaloJetTag");
  vars.push_back("htaodcalojets");
  vars.push_back("nSelectedAODCaloJet");
  vars.push_back("nSelectedAODCaloJetTagSB1");
  vars.push_back("nSelectedAODCaloJetTagSB2");
  vars.push_back("nSelectedAODCaloJetTagSB3");
  vars.push_back("LeadingJet_AODCaloJetPt");
  vars.push_back("AllJets_AODCaloJetPt");
  vars.push_back("AOD_dilepton_Mass");
  vars.push_back("AOD_dilepton_Pt");
 
  std::vector<TString> varsEleMu;
  varsEleMu.push_back("nSelectedAODCaloJetTag");
  varsEleMu.push_back("htaodcalojets");
  varsEleMu.push_back("nSelectedAODCaloJet");
  varsEleMu.push_back("nSelectedAODCaloJetTagSB1");
  varsEleMu.push_back("nSelectedAODCaloJetTagSB2");
  varsEleMu.push_back("nSelectedAODCaloJetTagSB3");
  varsEleMu.push_back("LeadingJet_AODCaloJetPt");
  varsEleMu.push_back("AllJets_AODCaloJetPt");
  vars.push_back("AOD_OSOFdilepton_Mass");
  vars.push_back("AOD_OSOFdilepton_Pt");    

  for(unsigned int i=0; i<vars.size(); i++){

    cout << "** COMPARE ** " << vars[i] << " in " << leptonChan << " ZH with " << varsEleMu[i] << " in EleMu" << endl;
    cout << "              alt TTbar: " << alt << ", addST: " << addST << endl;
    
    TFile* f_zh = TFile::Open("../../plots/addTrigFlav/Two"+leptonChan+"ZH/GH/Two"+leptonChan+"ZH_"+vars[i]+"_GH.root");
    TH1F* h_zh1 = (TH1F*)f_zh->Get(alt+"TT");
    print_hist("h_zh1", h_zh1);
    TH1F* h_zh2 = (TH1F*)f_zh->Get("ST");
    print_hist("h_zh2", h_zh2);
    TH1F* h_zh = (TH1F*)h_zh1->Clone("h_zh");
    if(addST) h_zh->Add(h_zh2);
    print_hist("h_zh", h_zh);
    
    TFile* f_cr = TFile::Open("../../plots/addTrigFlav/EleMuOSOF/GH/EleMuOSOF_"+varsEleMu[i]+"_GH.root");
    TH1F* h_cr1 = (TH1F*)f_cr->Get(alt+"TT");
    print_hist("h_cr1", h_cr1);
    TH1F* h_cr2 = (TH1F*)f_cr->Get("ST");
    print_hist("h_cr1", h_cr1);
    TH1F* h_cr = (TH1F*)h_cr1->Clone("h_cr");
    if(addST) h_cr->Add(h_cr2);
    print_hist("h_cr", h_cr);

    //normalize
    h_zh->Scale(1.0/h_zh->Integral());
    h_cr->Scale(1.0/h_cr->Integral());

    h_zh->SetLineColor(kBlue);
    h_zh->SetLineWidth(2);
    h_cr->SetLineColor(kRed);
    h_cr->SetLineWidth(2);

    TH1F* h_r = (TH1F*)h_zh->Clone("h_r");
    h_r->SetTitle("");
    h_r->Divide(h_cr);
    print_hist("h_r", h_r);
    h_r->SetLineColor(kGreen+1);
    
    TCanvas* c = new TCanvas("c", "c", 640, 2*480);
    c->Divide(1,2);
    c->cd(1);
    h_zh->SetMaximum(h_zh->GetMaximum()*1.5);
    h_zh->Draw();
    h_cr->Draw("SAME");
    c->cd(2);
    h_r->Draw();
    TString name = "compare_";
    name += alt; name += "TT";
    name += STstring; name += "_";
    name += vars[i]; name += "_";
    name += leptonChan;
    name += ".pdf";
    c->SaveAs(name);
  
  }//i vars

}



void compare(TString crname, TString leptonChan, TString alt = "", bool addExtra=false, bool norm=true){
  
  TString STstring = "";
  if(addExtra) STstring = "plusExtra";

  TString normString = "";
  if(norm) normString = "norm";

  std::vector<TString> vars;
  vars.push_back("nSelectedAODCaloJetTag");
  //vars.push_back("htaodcalojets");
  //vars.push_back("nSelectedAODCaloJet");
  vars.push_back("nSelectedAODCaloJetTagSB1");
  vars.push_back("nSelectedAODCaloJetTagSB2");
  vars.push_back("nSelectedAODCaloJetTagSB3");
  //vars.push_back("LeadingJet_AODCaloJetPt");
  //vars.push_back("AllJets_AODCaloJetPt");

  std::vector<TString> vars_cr;
  vars_cr.push_back("nSelectedAODCaloJetTag");
  //vars_cr.push_back("htaodcalojets");
  //vars_cr.push_back("nSelectedAODCaloJet");
  vars_cr.push_back("nSelectedAODCaloJetTagSB1");
  vars_cr.push_back("nSelectedAODCaloJetTagSB2");
  vars_cr.push_back("nSelectedAODCaloJetTagSB3");
  //vars_cr.push_back("LeadingJet_AODCaloJetPt");
  //vars_cr.push_back("AllJets_AODCaloJetPt");
  if(crname=="EleMu"){
    //vars.push_back("AOD_dilepton_Mass");
    //vars.push_back("AOD_dilepton_Pt");
    
    //vars_cr.push_back("AOD_OSOFdilepton_Mass");
    //vars_cr.push_back("AOD_OSOFdilepton_Pt");    
  }
  else if(crname=="OnePho"){
    //vars.push_back("AOD_dilepton_Pt");
    
    //vars_cr.push_back("AOD_phoPt");    
  }
  else{
    cout << "Wrong crname" << endl;
    return;
  }  
  
  for(unsigned int i=0; i<vars.size(); i++){

    cout << "** COMPARE ** " << vars[i] << " in " << leptonChan << " ZH with " << vars_cr[i] << " in " << crname << endl;
    cout << "              alt TTbar: " << alt << ", addExtra: " << addExtra << endl;

    TFile* f_zh; TFile* f_cr;
    TH1F* h_zh; TH1F* h_cr;
        
    if(crname=="EleMu"){
      f_zh = TFile::Open("../../plots/addTrigFlav/Two"+leptonChan+"ZH/GH/Two"+leptonChan+"ZH_"+vars[i]+"_GH.root");
      TH1F* h_zh1 = (TH1F*)f_zh->Get(alt+"TT");
      print_hist("h_zh1", h_zh1);
      TH1F* h_zh2 = (TH1F*)f_zh->Get("ST");
      if(addExtra) print_hist("h_zh2", h_zh2);

      h_zh = (TH1F*)h_zh1->Clone("h_zh");
      if(addExtra) h_zh->Add(h_zh2);
      print_hist("h_zh", h_zh);
      
      f_cr = TFile::Open("../../plots/addTrigFlav/EleMuOSOF/GH/EleMuOSOF_"+vars_cr[i]+"_GH.root");
      TH1F* h_cr1 = (TH1F*)f_cr->Get(alt+"TT");
      print_hist("h_cr1", h_cr1);
      TH1F* h_cr2 = (TH1F*)f_cr->Get("ST");
      if(addExtra) print_hist("h_cr2", h_cr2);
      
      h_cr = (TH1F*)h_cr1->Clone("h_cr");
      if(addExtra) h_cr->Add(h_cr2);
      print_hist("h_cr", h_cr);
    }
    else if(crname=="OnePho"){
      f_zh = TFile::Open("../../plots/addTrigFlav/Two"+leptonChan+"ZH/GH/Two"+leptonChan+"ZH_"+vars[i]+"_GH.root");
      TH1F* h_zh1 = (TH1F*)f_zh->Get("DY");
      print_hist("h_zh1", h_zh1);
      TH1F* h_zh2 = (TH1F*)f_zh->Get("WJetsToLNu");
      if(addExtra) print_hist("h_zh2", h_zh2);
      TH1F* h_zh3 = (TH1F*)f_zh->Get("VG");
      if(addExtra) print_hist("h_zh3", h_zh3);
      TH1F* h_zh4 = (TH1F*)f_zh->Get("VV");
      if(addExtra) print_hist("h_zh4", h_zh4);
      
      h_zh = (TH1F*)h_zh1->Clone("h_zh");
      if(addExtra) h_zh->Add(h_zh2);
      if(addExtra) h_zh->Add(h_zh3);
      if(addExtra) h_zh->Add(h_zh4);
      print_hist("h_zh", h_zh);

      f_cr = TFile::Open("../../plots/addTrigFlav/OnePho/GH/OnePho_"+vars_cr[i]+"_GH.root");
      TH1F* h_cr1 = (TH1F*)f_cr->Get("GJets");
      print_hist("h_cr1", h_cr1);
      TH1F* h_cr2 = (TH1F*)f_cr->Get("QCD");
      if(addExtra) print_hist("h_cr2", h_cr2);
      
      h_cr = (TH1F*)h_cr1->Clone("h_cr");
      if(addExtra) h_cr->Add(h_cr2);

      print_hist("h_cr", h_cr);
    }
    else{
      cout << "Wrong crname" << endl;
      return;
    }
    
    //normalize
    if(norm) h_zh->Scale(1.0/h_zh->Integral());
    if(norm) h_cr->Scale(1.0/h_cr->Integral());

    h_zh->SetLineColor(kBlue);
    h_zh->SetLineWidth(2);
    h_cr->SetLineColor(kRed);
    h_cr->SetLineWidth(2);

    TH1F* h_r = (TH1F*)h_zh->Clone("h_r");
    h_r->SetTitle("");
    h_r->Divide(h_cr);
    print_hist("h_r", h_r);
    h_r->SetLineColor(kGreen+1);
    
    TCanvas* c = new TCanvas("c", "c", 640, 2*480);
    c->Divide(1,2);
    c->cd(1);
    h_zh->SetMaximum(h_zh->GetMaximum()*1.5);
    h_zh->Draw();
    h_cr->Draw("SAME");
    c->cd(2);
    h_r->Draw();
    TString name = "compare_";
    name += alt; 
    if(crname=="EleMu") name += "TT";
    if(crname=="OnePho") name += "DY";
    name += STstring; name += "_";
    name += vars[i]; name += "_";
    name += leptonChan; name += "_";
    name += normString;
    name += ".pdf";
    c->SaveAs(name);
  
  }//i vars

}


////////////////////////////////
////////////////////////////////


void tt(){
  
  TString sample = "altTT";

  TFile* f_zh = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_zh = (TH1F*)f_zh->Get(sample);

  TFile* f_cr = TFile::Open("../../plots/addTrigFlav/EleMuOSOF/GH/EleMuOSOF_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_cr = (TH1F*)f_cr->Get(sample);

  TH1F* h_r = (TH1F*)h_zh->Clone("h_r");
  h_r->SetTitle("");
  h_r->Divide(h_cr);

  TCanvas* c = new TCanvas("c", "c", 640, 480);
  h_r->Draw();

}



void heavy(){
  
  TString alt = "alt";

  TFile* f_zh = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_zh1 = (TH1F*)f_zh->Get(alt+"TT");
  TH1F* h_zh2 = (TH1F*)f_zh->Get("ST");
  TH1F* h_zh = (TH1F*)h_zh1->Clone("h_zh");
  h_zh->Add(h_zh2);

  TFile* f_cr = TFile::Open("../../plots/addTrigFlav/EleMuOSOF/GH/EleMuOSOF_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_cr1 = (TH1F*)f_cr->Get(alt+"TT");
  TH1F* h_cr2 = (TH1F*)f_cr->Get("ST");
  TH1F* h_cr = (TH1F*)h_cr1->Clone("h_cr");
  h_cr->Add(h_cr2);

  TH1F* h_r = (TH1F*)h_zh->Clone("h_r");
  h_r->SetTitle("");
  h_r->Divide(h_cr);

  TCanvas* c = new TCanvas("c", "c", 640, 480);
  h_r->Draw();

}


void heavy_sb(){
  
  TString alt = "alt";

  //SIG
  TFile* f_zh = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_zh1 = (TH1F*)f_zh->Get(alt+"TT");
  TH1F* h_zh2 = (TH1F*)f_zh->Get("ST");
  TH1F* h_zh = (TH1F*)h_zh1->Clone("h_zh");
  //h_zh->Add(h_zh2);

  TFile* f_cr = TFile::Open("../../plots/addTrigFlav/EleMuOSOF/GH/EleMuOSOF_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_cr1 = (TH1F*)f_cr->Get(alt+"TT");
  TH1F* h_cr2 = (TH1F*)f_cr->Get("ST");
  TH1F* h_cr = (TH1F*)h_cr1->Clone("h_cr");
  //h_cr->Add(h_cr2);

  TH1F* h_r = (TH1F*)h_zh->Clone("h_r");
  h_r->SetTitle("");
  h_r->Divide(h_cr);

  //SB1
  TFile* f_zh_sb1 = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTagSB1_GH.root");
  TH1F* h_zh1_sb1 = (TH1F*)f_zh_sb1->Get(alt+"TT");
  TH1F* h_zh2_sb1 = (TH1F*)f_zh_sb1->Get("ST");
  TH1F* h_zh_sb1 = (TH1F*)h_zh1_sb1->Clone("h_zh_sb1");
  h_zh_sb1->Add(h_zh2_sb1);

  TFile* f_cr_sb1 = TFile::Open("../../plots/addTrigFlav/EleMuOSOF/GH/EleMuOSOF_nSelectedAODCaloJetTagSB1_GH.root");
  TH1F* h_cr1_sb1 = (TH1F*)f_cr_sb1->Get(alt+"TT");
  TH1F* h_cr2_sb1 = (TH1F*)f_cr_sb1->Get("ST");
  TH1F* h_cr_sb1 = (TH1F*)h_cr1_sb1->Clone("h_cr_sb1");
  h_cr_sb1->Add(h_cr2_sb1);

  TH1F* h_r_sb1 = (TH1F*)h_zh_sb1->Clone("h_r_sb1");
  h_r_sb1->SetTitle("");
  h_r_sb1->Divide(h_cr_sb1);

  //SB2
  TFile* f_zh_sb2 = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTagSB2_GH.root");
  TH1F* h_zh1_sb2 = (TH1F*)f_zh_sb2->Get(alt+"TT");
  TH1F* h_zh2_sb2 = (TH1F*)f_zh_sb2->Get("ST");
  TH1F* h_zh_sb2 = (TH1F*)h_zh1_sb2->Clone("h_zh_sb2");
  h_zh_sb2->Add(h_zh2_sb2);

  TFile* f_cr_sb2 = TFile::Open("../../plots/addTrigFlav/EleMuOSOF/GH/EleMuOSOF_nSelectedAODCaloJetTagSB2_GH.root");
  TH1F* h_cr1_sb2 = (TH1F*)f_cr_sb2->Get(alt+"TT");
  TH1F* h_cr2_sb2 = (TH1F*)f_cr_sb2->Get("ST");
  TH1F* h_cr_sb2 = (TH1F*)h_cr1_sb2->Clone("h_cr_sb2");
  h_cr_sb2->Add(h_cr2_sb2);

  TH1F* h_r_sb2 = (TH1F*)h_zh_sb2->Clone("h_r_sb2");
  h_r_sb2->SetTitle("");
  h_r_sb2->Divide(h_cr_sb2);

  //SB3
  TFile* f_zh_sb3 = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTagSB3_GH.root");
  TH1F* h_zh1_sb3 = (TH1F*)f_zh_sb3->Get(alt+"TT");
  TH1F* h_zh2_sb3 = (TH1F*)f_zh_sb3->Get("ST");
  TH1F* h_zh_sb3 = (TH1F*)h_zh1_sb3->Clone("h_zh_sb3");
  h_zh_sb3->Add(h_zh2_sb3);

  TFile* f_cr_sb3 = TFile::Open("../../plots/addTrigFlav/EleMuOSOF/GH/EleMuOSOF_nSelectedAODCaloJetTagSB3_GH.root");
  TH1F* h_cr1_sb3 = (TH1F*)f_cr_sb3->Get(alt+"TT");
  TH1F* h_cr2_sb3 = (TH1F*)f_cr_sb3->Get("ST");
  TH1F* h_cr_sb3 = (TH1F*)h_cr1_sb3->Clone("h_cr_sb3");
  h_cr_sb3->Add(h_cr2_sb3);

  TH1F* h_r_sb3 = (TH1F*)h_zh_sb3->Clone("h_r_sb3");
  h_r_sb3->SetTitle("");
  h_r_sb3->Divide(h_cr_sb3);


  TH1F* h_all_r = new TH1F("h_all_r", "h_all_r", 4, 0, 4);
  h_all_r->SetBinContent(1,h_r->GetBinContent(3));
  h_all_r->SetBinError(1,h_r->GetBinError(3));
  h_all_r->SetBinContent(2,h_r_sb1->GetBinContent(3));
  h_all_r->SetBinError(2,h_r_sb1->GetBinError(3));
  h_all_r->SetBinContent(3,h_r_sb2->GetBinContent(3));
  h_all_r->SetBinError(3,h_r_sb2->GetBinError(3));
  h_all_r->SetBinContent(4,h_r_sb3->GetBinContent(3));
  h_all_r->SetBinError(4,h_r_sb3->GetBinError(3));

  TCanvas* c = new TCanvas("c", "c", 640, 480);
  h_all_r->Draw();

}



void light(){
  
  //TString alt = "alt";

  TFile* f_zh = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_zh1 = (TH1F*)f_zh->Get("DY");
  TH1F* h_zh2 = (TH1F*)f_zh->Get("WJetsToLNu");
  TH1F* h_zh3 = (TH1F*)f_zh->Get("VG");
  TH1F* h_zh4 = (TH1F*)f_zh->Get("VV");
  TH1F* h_zh = (TH1F*)h_zh1->Clone("h_zh");
  h_zh->Add(h_zh2);
  h_zh->Add(h_zh3);
  h_zh->Add(h_zh4);

  TFile* f_cr = TFile::Open("../../plots/addTrigFlav/OnePho/GH/OnePho_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_cr1 = (TH1F*)f_cr->Get("GJets");
  TH1F* h_cr2 = (TH1F*)f_cr->Get("QCD");
  TH1F* h_cr = (TH1F*)h_cr1->Clone("h_cr");
  h_cr->Add(h_cr2);

  TH1F* h_r = (TH1F*)h_zh->Clone("h_r");
  h_r->SetTitle("");
  h_r->Divide(h_cr);

  TCanvas* c = new TCanvas("c", "c", 640, 480);
  h_r->Draw();

}



void dy(){
  
  TString alt = "alt";

  TFile* f_zh = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_zh = (TH1F*)f_zh->Get(alt+"DY");

  TFile* f_cr = TFile::Open("../../plots/addTrigFlav/OnePho/GH/OnePho_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_cr = (TH1F*)f_cr->Get("GJets");

  TH1F* h_r = (TH1F*)h_zh->Clone("h_r");
  h_r->SetTitle("");
  h_r->Divide(h_cr);

  TCanvas* c = new TCanvas("c", "c", 640, 480);
  h_r->Draw();

}



void dy_sb(){
  
  TString alt = "";

  TFile* f_zh = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_zh = (TH1F*)f_zh->Get(alt+"DY");
  TFile* f_cr = TFile::Open("../../plots/addTrigFlav/OnePho/GH/OnePho_nSelectedAODCaloJetTag_GH.root");
  TH1F* h_cr = (TH1F*)f_cr->Get("GJets");

  TH1F* h_r = (TH1F*)h_zh->Clone("h_r");
  h_r->SetTitle("");
  h_r->Divide(h_cr);

  TFile* f_zh_sb1 = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTagSB1_GH.root");
  TH1F* h_zh_sb1 = (TH1F*)f_zh_sb1->Get(alt+"DY");
  TFile* f_cr_sb1 = TFile::Open("../../plots/addTrigFlav/OnePho/GH/OnePho_nSelectedAODCaloJetTagSB1_GH.root");
  TH1F* h_cr_sb1 = (TH1F*)f_cr_sb1->Get("GJets");
  TH1F* h_r_sb1 = (TH1F*)h_zh_sb1->Clone("h_r_sb1");
  h_r_sb1->SetTitle("");
  h_r_sb1->Divide(h_cr_sb1);

  TFile* f_zh_sb2 = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTagSB2_GH.root");
  TH1F* h_zh_sb2 = (TH1F*)f_zh_sb2->Get(alt+"DY");
  TFile* f_cr_sb2 = TFile::Open("../../plots/addTrigFlav/OnePho/GH/OnePho_nSelectedAODCaloJetTagSB2_GH.root");
  TH1F* h_cr_sb2 = (TH1F*)f_cr_sb2->Get("GJets");
  TH1F* h_r_sb2 = (TH1F*)h_zh_sb2->Clone("h_r_sb2");
  h_r_sb2->SetTitle("");
  h_r_sb2->Divide(h_cr_sb2);

  TFile* f_zh_sb3 = TFile::Open("../../plots/addTrigFlav/TwoMuZH/GH/TwoMuZH_nSelectedAODCaloJetTagSB3_GH.root");
  TH1F* h_zh_sb3 = (TH1F*)f_zh_sb3->Get(alt+"DY");
  TFile* f_cr_sb3 = TFile::Open("../../plots/addTrigFlav/OnePho/GH/OnePho_nSelectedAODCaloJetTagSB3_GH.root");
  TH1F* h_cr_sb3 = (TH1F*)f_cr_sb3->Get("GJets");
  TH1F* h_r_sb3 = (TH1F*)h_zh_sb3->Clone("h_r_sb3");
  h_r_sb3->SetTitle("");
  h_r_sb3->Divide(h_cr_sb3);

  TH1F* h_all_r = new TH1F("h_all_r", "h_all_r", 4, 0, 4);
  h_all_r->SetBinContent(1,h_r->GetBinContent(3));
  h_all_r->SetBinError(1,h_r->GetBinError(3));
  h_all_r->SetBinContent(2,h_r_sb1->GetBinContent(3));
  h_all_r->SetBinError(2,h_r_sb1->GetBinError(3));
  h_all_r->SetBinContent(3,h_r_sb2->GetBinContent(3));
  h_all_r->SetBinError(3,h_r_sb2->GetBinError(3));
  h_all_r->SetBinContent(4,h_r_sb3->GetBinContent(3));
  h_all_r->SetBinError(4,h_r_sb3->GetBinError(3));

  TCanvas* c = new TCanvas("c", "c", 640, 480);
  h_all_r->Draw();

  //TCanvas* c = new TCanvas("c", "c", 640, 480);
  //h_r->Draw();
  
}



void plot_SRCR(){

  //tt();
  //dy();
  //heavy();
  //light();
  // heavy_sb();
  //dy_sb();

  /*
  compare_tt("Ele","alt",0);
  compare_tt("Ele","alt",1);
  compare_tt("Mu","alt",0);
  compare_tt("Mu","alt",1);
  */

  bool norm = false;
  compare("EleMu","Ele","alt",0, norm);
  compare("EleMu","Ele","alt",1, norm);
  compare("EleMu","Mu","alt",0, norm);
  compare("EleMu","Mu","alt",1, norm);

  compare("OnePho","Ele","",0, norm);
  compare("OnePho","Ele","",1, norm);
  compare("OnePho","Mu","",0, norm);
  compare("OnePho","Mu","",1, norm);

}
