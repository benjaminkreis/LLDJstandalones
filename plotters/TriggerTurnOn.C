#include <iostream>
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TText.h"
#include "TFile.h"
#include <string>

#include <stdlib.h>     /* getenv */

//using namespace std;

void TriggerTurnOn( )
{
 // path to_"+region+"histograms.root files
 TString inpath  = TString("../roots/");
 TString outpath = TString("../plots/");
 //TString sample = "DY50";
 
 std::vector<TString> sample;
 sample.push_back("DYJetsToLL_M-50");
 /*sample.push_back("DY5to50_HT100To200");
 sample.push_back("DY5to50_HT200To400");
 sample.push_back("DY5to50_HT400To600");
 sample.push_back("DY5to50_HT600ToInf");
 sample.push_back("GJets_HT100To200");
 sample.push_back("GJets_HT200To400");
 sample.push_back("GJets_HT400To600");
 sample.push_back("GJets_HT600ToInf");
 sample.push_back("ST_s");
 sample.push_back("ST_t");
 sample.push_back("ST_tW");
 sample.push_back("STbar_t");
 sample.push_back("STbar_tW");
 sample.push_back("TTJets");
 sample.push_back("WG");
 sample.push_back("WJetsToLNu");
 sample.push_back("ZG");
 sample.push_back("ZZ");
 sample.push_back("ggZH_HToBB_ZToLL");
 sample.push_back("ZH_HToBB_ZToLL");
*/
 TString region = "DY";

 //1D histograms to make
 std::vector<TString> Nname;
 std::vector<TString> Dname;
 //twoD histograms to make
 std::vector<TString> twoD_Nname;
 std::vector<TString> twoD_Dname;
 TString lepton;
 // lepton flavor
 std::vector<TString> lep;
 lep.clear();
 lep.push_back("ele"); 
 lep.push_back("mu");  
 
 TString aversion = TString(getenv("aversion"));
 //TString aversion = "TTOCfixed" ;
 inpath = inpath+aversion+"/";
 outpath = outpath+aversion+"/";

 
 TGraphAsymmErrors* gr_TTOC = new TGraphAsymmErrors();
 TH1F* TTOCDenom;
 TH1F* TTOCNum;
 TH2F* twoD_TTOCDenom;
 TH2F* twoD_TTOCNum;
 TH2F* twoD_Divide;
 TString unit;
 TString name;
 TString twoD_name;
 
 for (int k = 0; k<sample.size(); k++){
 TFile *_file0 = TFile::Open(inpath+sample[k]+"_"+region+"_histograms.root");
  for(int i = 0; i<lep.size(); i++){ 
  Nname.clear();
  Dname.clear();
  if(i ==1){
   lepton = "Mu";
   Nname.push_back("DMu1Pt");
   Dname.push_back("Mu1Pt");
   Nname.push_back("DMu2Pt");
   Dname.push_back("Mu2Pt");
   Nname.push_back("DMu1Eta");
   Dname.push_back("Mu1Eta");
   Nname.push_back("DMu2Eta");
   Dname.push_back("Mu2Eta");
  }
 else{
  lepton = "Ele"; 
  Nname.push_back("23DEle1Pt");
  Dname.push_back("Ele1Pt");
  Nname.push_back("23DEle2Pt");
  Dname.push_back("Ele2Pt");
  Nname.push_back("23DEle1Eta");
  Dname.push_back("Ele1Eta");
  Nname.push_back("23DEle2Eta");
  Dname.push_back("Ele2Eta");
 }
 for (int j=0; j<Nname.size(); j++){
   if (i==1)name = sample[k]+": DoubleMu Turn on vs "    +Dname[j]+": "+region+" Region ";
   else     name = sample[k]+": DoubleEle Turn on vs "+Dname[j]+": "+region+" Region ";
   cout << "Plotting: "<<name<<endl;
   if( Dname[j].Contains("Eta") )  {unit = "";         }
   else                            {unit = "  [GeV]";  }
   TString outname = outpath+region+"_"+sample[k]+"_TTOC"+Dname[j];
   TTOCNum    = (TH1F*)_file0->Get("h_"+lep[i]+"_"+region+"_TTOC"+lepton+"Trigger"+Nname[j])->Clone("TTOCNum");
   TTOCDenom  = (TH1F*)_file0->Get("h_"+lep[i]+"_"+region+"_TTOC"+Dname[j])->Clone("TTOCDenom");

   // make canvas and text
   TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
   canvas->Clear();
   canvas->cd();
   TPad *pad1  = new TPad("pad1", "pad1", 0, 0, 1, 1);
   pad1->SetTickx();
   pad1->SetTicky();
   pad1->SetGrid();
   pad1->Draw();
   pad1->cd();
   gStyle->SetLineWidth(3);
   gStyle->SetPalette(kBird);

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
 
   TText* extra2 = new TText(1,1,"") ;
   extra2->SetTextSize(0.04);
   extra2->SetTextColor(kBlack);
   extra2->SetTextAlign(11);
   extra2->SetTextFont(62);
 
   TText* lumi = new TText(1,1,"") ;
   lumi->SetTextSize(0.03);
   lumi->SetTextColor(kBlack);
   lumi->SetTextAlign(31);
   lumi->SetTextFont(42);

  gr_TTOC->Divide(TTOCNum, TTOCDenom, "cl=0.683 b(1,1) mode");
  gr_TTOC->Draw();
  /*
  //checking divide
  for(int i = 0; i <=TTOCNum->GetXaxis()->GetNbins()+1; i++){
  cout<<"*********************** Position: "  << TTOCNum->GetXaxis()->GetBinCenter(i)  <<endl;
  cout<<"Numerator: "  << TTOCNum->GetBinContent(i)  <<endl;
  cout<<"Denominator: "<< TTOCDenom->GetBinContent(i)<<endl;
  cout<<"Ratio: "      << gr_TTOC->Eval(TTOCNum->GetXaxis()->GetBinCenter(i))<< ",  Numerator/Denominator: "<<TTOCNum->GetBinContent(i)/TTOCDenom->GetBinContent(i)  <<endl;
  //cout<<endl;
  }
  */
  
  //--Style
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(1.2);
  gr_TTOC->SetLineWidth(2);
  gr_TTOC->SetMarkerSize(1);
  gr_TTOC->SetMarkerStyle(8);
  gr_TTOC->SetMarkerColor(kAzure-2);
  gr_TTOC->SetLineColor(kAzure-2);
  gr_TTOC->SetTitle(name);
  gr_TTOC->GetYaxis()->SetTitleOffset(1.95);
  gr_TTOC->GetXaxis()->SetTitle(TTOCDenom->GetTitle()+unit);
  gr_TTOC->GetYaxis()->SetTitle("Trigger Efficiency");
  gStyle->SetOptStat(0);
  gPad->Update();
  gPad->RedrawAxis();

  // save canvas
  canvas->SaveAs(outname+".png");
  canvas->SaveAs(outname+".pdf");
 }
}//1D end

for(int i = 0; i<lep.size(); i++){ 
 twoD_Nname.clear();
 twoD_Dname.clear();
 if(i ==1){
  lepton = "Mu";
  twoD_Nname.push_back("DMuPt");
  twoD_Dname.push_back("MuPt");
  twoD_Nname.push_back("DMuEta");
  twoD_Dname.push_back("MuEta");
 }
 else{
  lepton = "Ele"; 
  twoD_Nname.push_back("23DElePt");
  twoD_Dname.push_back("ElePt");
  twoD_Nname.push_back("23DEleEta");
  twoD_Dname.push_back("EleEta");
 }
 for (int j=0; j<twoD_Nname.size(); j++){
   if (i==1)twoD_name = sample[k]+": Trigger efficiency Mu2 vs. Mu1  "    +twoD_Nname[j]+": "+region+" Region ";
   else     twoD_name = sample[k]+": Trigger efficiency Ele2 vs. Ele1 "   +twoD_Nname[j]+": "+region+" Region ";
   cout << "Plotting: "<<twoD_name<<endl;
   if( twoD_Dname[j].Contains("Eta") )  {unit = "";         }
   else                               {unit = "  [GeV]";  }
   TString outname2 = outpath+region+"_"+sample[k]+"_twoD_TTOC"+twoD_Dname[j];
   twoD_TTOCNum    = (TH2F*)_file0->Get("h_"+lep[i]+"_"+region+"_TTOC"+lepton+"Trigger"+twoD_Nname[j])->Clone("twoD_TTOCNum");
   twoD_TTOCDenom  = (TH2F*)_file0->Get("h_"+lep[i]+"_"+region+"_TTOC"+twoD_Dname[j])->Clone("twoD_TTOCDenom");
   twoD_TTOCNum->Divide(twoD_TTOCDenom);
   // make canvas and text
   TCanvas* canvas2 = new TCanvas("canvas2","canvas2",900,100,500,500); 
   canvas2->Clear();
   canvas2->cd();
   TPad *pad2  = new TPad("pad2", "pad2", 0, 0, 1, 1);
   pad2->SetTickx();
   pad2->SetTicky();
   pad2->SetGrid();
   pad2->Draw();
   pad2->cd();
   gStyle->SetLineWidth(3);
   gStyle->SetPalette(kBird);
  
  //--twoD Style
  //h2_TTOC->SetLineWidth(2);
  //h2_TTOC->SetMarkerSize(1);
  //h2_TTOC->SetMarkerStyle(8);
  //h2_TTOC->SetMarkerColor(kAzure-2);
  //h2_TTOC->SetLineColor(kAzure-2);
   twoD_TTOCNum->SetTitle(twoD_name);
   twoD_TTOCNum->GetYaxis()->SetTitleOffset(1.25);
   twoD_TTOCNum->GetYaxis()->SetTitle(lepton+"2: "+twoD_TTOCDenom->GetTitle()+unit);
   twoD_TTOCNum->GetXaxis()->SetTitle(lepton+"1: "+twoD_TTOCDenom->GetTitle()+unit);
  //h2_TTOC->GetZaxis()->SetTitle("Trigger Efficiency");
   twoD_TTOCNum->Draw("COLZ");
    gPad->Update();
    gPad->RedrawAxis();


    // save canvas
    canvas2->SaveAs(outname2+".png");
    //canvas2->SaveAs(outname2+".pdf");
 }
}//2D end
_file0->Close();
}//end sample loop
}
