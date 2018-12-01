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
#include <stdio.h>
#include <cstdlib> /* mkdir */

#include <stdlib.h>     /* getenv */

//using namespace std;

void plotter_singleMerged(TString region, TString varname, Bool_t dolog, Bool_t HIP )
{

// // Draw signal as lines
// Bool_t drawSignal = kFALSE; //kTRUE;
// Bool_t drawRatio = kTRUE;

 // Setup running configuration: IO, naming, SFs, ..
 /////////////////////////////////////////////////////

 Bool_t drawuncs = kFALSE;  //kTRUE;

 TString inpath  = TString("../plots/");
 TString outpath = TString("../plots/");
 TString aversion = TString(getenv("aversion"));

 inpath = inpath+aversion+"/"+region+"/";
 outpath = outpath+aversion+"/"+region+"/";

 Float_t lumiBCDEF = 19691. ;
 Float_t lumiGH = 16226.5 ;

 Int_t rebin = 1;  //5; //25; //10; //

 TString eraname = "";
 if(HIP){
  eraname+="_BCDEF";
  outpath = outpath+"BCDEF/";
  inpath = inpath+"BCDEF/";
 }
 if(!HIP){
  outpath = outpath+"GH/";
  inpath = inpath+"GH/";
  eraname+="_GH";
 }
 TString TSrebin;
 TSrebin.Form("_r%d",rebin);

 TString infilename = region+"_"+varname+eraname;
 TString outname = "sp_"+region+"_"+varname+eraname;
 outname += TSrebin;
 outname = outpath + outname;
 //outname.Form("%s_r%d",outname.Data(),rebin);

 if(dolog){
  outname+="_log";
  //outpath = outpath+"log/";
 }
 // std::cout<<"name: "<<inpath<<" "<<infilename<<std::endl;

 // canvas and text attributes
 int canx = 1100;
 int cany = 1200;
 float lmarg = 0.12;
 float rmarg = 0.05;
 
 TCanvas* canvas = new TCanvas("canvas","canvas",canx,cany); 

 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);
 gStyle->SetPalette(kBird);

 canvas->Clear();
 canvas->cd();

 TPad *plotpad  = new TPad("plotpad", "plotpad", 0, 0.25, 1, 1);
 plotpad->SetBottomMargin(0.04);
 plotpad->SetLeftMargin(lmarg);
 plotpad->SetRightMargin(rmarg);
 plotpad->SetFrameLineWidth(3);
 plotpad->SetLogy(dolog);
 plotpad->Draw();

 canvas->cd();
 TPad *ratiopad = new TPad("ratiopad", "ratiopad", 0, 0, 1, 0.25);
 ratiopad->SetTopMargin(0.04);
 ratiopad->SetBottomMargin(0.4);
 ratiopad->SetFrameLineWidth(3);
 ratiopad->SetLeftMargin(lmarg);
 ratiopad->SetRightMargin(rmarg);
 ratiopad->SetLogy(0);
 ratiopad->SetGrid();
 ratiopad->Draw();
 canvas->cd();

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.06);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.05);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 //extra->SetTextAlign(13);
 extra->SetTextFont(52);
 
 TText* extra2 = new TText(1,1,"") ;
 extra2->SetTextSize(0.03);
 extra2->SetTextColor(kBlack);
 extra2->SetTextAlign(11);
 //extra2->SetTextAlign(13);
 extra2->SetTextFont(62);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.05);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 // initialize histogram file / histograms
 TFile* file_input       ; 
 TH1F* h_DY     ;
 TH1F* h_GJets  ;
 TH1F* h_ST     ;
 TH1F* h_VV     ;
 TH1F* h_VG     ;
 TH1F* h_ZH     ;
 TH1F* h_TT     ;
 TH1F* h_WJetsToLNu;
 TH1F* h_QCD;
 TH1F* h_mctotal ;
 TH1F* h_mctotal_line ;
 TH1F* h_ratio ;
 TH1F* h_ratiostaterr ;
 TH1F* h_altDY ;
 TH1F* h_altVV ;
 TH1F* h_altTT ;
 TH1F* h_Sig_MS15ct1000 ;
 TH1F* h_Sig_MS15ct100  ;
 TH1F* h_Sig_MS15ct10   ;
 TH1F* h_Sig_MS15ct1    ;
 TH1F* h_Sig_MS40ct1000 ;
 TH1F* h_Sig_MS40ct100  ;
 TH1F* h_Sig_MS40ct10   ;
 TH1F* h_Sig_MS40ct1    ;
 TH1F* h_Sig_MS55ct1000 ;
 TH1F* h_Sig_MS55ct100  ;
 TH1F* h_Sig_MS55ct10   ;
 TH1F* h_Sig_MS55ct1    ;
 TH1F* h_Data   ;
 THStack* bgstack;

 TH1F* h_mctotal_EGSUp      ;
 TH1F* h_mctotal_EGSDown    ;
 TH1F* h_mctotal_MESUp      ;
 TH1F* h_mctotal_MESDown    ;
 TH1F* h_mctotal_AMaxUp     ;
 TH1F* h_mctotal_AMaxDown   ;
 TH1F* h_mctotal_IPSigUp    ;
 TH1F* h_mctotal_IPSigDown  ;
 TH1F* h_mctotal_TAUp       ;
 TH1F* h_mctotal_TADown     ;
 TH1F* h_mctotal_TagVarsUp  ;
 TH1F* h_mctotal_TagVarsDown;
 TH1F* h_Sig_MS40ct10_EGSUp       ;
 TH1F* h_Sig_MS40ct10_EGSDown     ;   
 TH1F* h_Sig_MS40ct10_MESUp       ;
 TH1F* h_Sig_MS40ct10_MESDown     ;   
 TH1F* h_Sig_MS40ct10_AMaxUp      ;   
 TH1F* h_Sig_MS40ct10_AMaxDown    ;   
 TH1F* h_Sig_MS40ct10_IPSigUp     ;   
 TH1F* h_Sig_MS40ct10_IPSigDown   ;   
 TH1F* h_Sig_MS40ct10_TAUp        ;
 TH1F* h_Sig_MS40ct10_TADown      ;   
 TH1F* h_Sig_MS40ct10_TagVarsUp   ;   
 TH1F* h_Sig_MS40ct10_TagVarsDown ;


 // load histogram file / histograms
 file_input = new TFile( inpath + infilename + ".root"               ) ; 
 h_DY             = (TH1F*)file_input->Get("DY"            )->Clone("DY"            )  ;
 h_GJets          = (TH1F*)file_input->Get("GJets"         )->Clone("GJets"         )  ;
 h_WJetsToLNu     = (TH1F*)file_input->Get("WJetsToLNu"    )->Clone("WJetsToLNu"    )  ;
 h_ST             = (TH1F*)file_input->Get("ST"            )->Clone("ST"            )  ;
 h_VV             = (TH1F*)file_input->Get("VV"            )->Clone("VV"            )  ;
 h_VG             = (TH1F*)file_input->Get("VG"            )->Clone("VG"            )  ;
 h_ZH             = (TH1F*)file_input->Get("ZH"            )->Clone("ZH"            )  ;
 h_TT             = (TH1F*)file_input->Get("TT"            )->Clone("TT"            )  ;
 h_QCD            = (TH1F*)file_input->Get("QCD"           )->Clone("QCD"           )  ;
 bgstack          = (THStack*)file_input->Get("bgstack"    )->Clone("bgstack"       )  ;
 h_ratio          = (TH1F*)file_input->Get("ratio"         )->Clone("ratio"         )  ;
 h_ratiostaterr   = (TH1F*)file_input->Get("ratiostaterr"  )->Clone("ratiostaterr"  )  ;
 h_altDY          = (TH1F*)file_input->Get("altDY"         )->Clone("altDY"         )  ;
 h_altVV          = (TH1F*)file_input->Get("altVV"         )->Clone("altVV"         )  ;
 h_altTT          = (TH1F*)file_input->Get("altTT"         )->Clone("altTT"         )  ;
 h_Sig_MS15ct1000 = (TH1F*)file_input->Get("Sig_MS15ct1000")->Clone("Sig_MS15ct1000")  ;
 h_Sig_MS15ct100  = (TH1F*)file_input->Get("Sig_MS15ct100" )->Clone("Sig_MS15ct100" )  ;
 h_Sig_MS15ct10   = (TH1F*)file_input->Get("Sig_MS15ct10"  )->Clone("Sig_MS15ct10"  )  ;
 h_Sig_MS15ct1    = (TH1F*)file_input->Get("Sig_MS15ct1"   )->Clone("Sig_MS15ct1"   )  ;
 h_Sig_MS40ct1000 = (TH1F*)file_input->Get("Sig_MS40ct1000")->Clone("Sig_MS40ct1000")  ;
 h_Sig_MS40ct100  = (TH1F*)file_input->Get("Sig_MS40ct100" )->Clone("Sig_MS40ct100" )  ;
 h_Sig_MS40ct10   = (TH1F*)file_input->Get("Sig_MS40ct10"  )->Clone("Sig_MS40ct10"  )  ;
 h_Sig_MS40ct1    = (TH1F*)file_input->Get("Sig_MS40ct1"   )->Clone("Sig_MS40ct1"   )  ;
 h_Sig_MS55ct1000 = (TH1F*)file_input->Get("Sig_MS55ct1000")->Clone("Sig_MS55ct1000")  ;
 h_Sig_MS55ct100  = (TH1F*)file_input->Get("Sig_MS55ct100" )->Clone("Sig_MS55ct100" )  ;
 h_Sig_MS55ct10   = (TH1F*)file_input->Get("Sig_MS55ct10"  )->Clone("Sig_MS55ct10"  )  ;
 h_Sig_MS55ct1    = (TH1F*)file_input->Get("Sig_MS55ct1"   )->Clone("Sig_MS55ct1"   )  ;
 h_Data           = (TH1F*)file_input->Get("Data"          )->Clone("Data"          )  ;

 file_input_EGSUp       = new TFile( inpath + infilename + "_EGSUp.root"      ) ; 
 file_input_EGSDown     = new TFile( inpath + infilename + "_EGSDown.root"    ) ; 
 file_input_MESUp       = new TFile( inpath + infilename + "_MESUp.root"      ) ; 
 file_input_MESDown     = new TFile( inpath + infilename + "_MESDown.root"    ) ; 
 file_input_AMaxUp      = new TFile( inpath + infilename + "_AMaxUp.root"     ) ; 
 file_input_AMaxDown    = new TFile( inpath + infilename + "_AMaxDown.root"   ) ; 
 file_input_IPSigUp     = new TFile( inpath + infilename + "_IPSigUp.root"    ) ; 
 file_input_IPSigDown   = new TFile( inpath + infilename + "_IPSigDown.root"  ) ; 
 file_input_TAUp        = new TFile( inpath + infilename + "_TAUp.root"       ) ; 
 file_input_TADown      = new TFile( inpath + infilename + "_TADown.root"     ) ; 
 file_input_TagVarsUp   = new TFile( inpath + infilename + "_TagVarsUp.root"  ) ; 
 file_input_TagVarsDown = new TFile( inpath + infilename + "_TagVarsDown.root") ; 
 h_mctotal        = (TH1F*)file_input->Get("bkgtotal"      )->Clone("bkgtotal"      )  ;
 h_mctotal_EGSUp       = (TH1F*)file_input_EGSUp      ->Get("bkgtotal")->Clone("bkgtotal_EGSUp      " )  ;
 h_mctotal_EGSDown     = (TH1F*)file_input_EGSDown    ->Get("bkgtotal")->Clone("bkgtotal_EGSDown    " )  ;
 h_mctotal_MESUp       = (TH1F*)file_input_MESUp      ->Get("bkgtotal")->Clone("bkgtotal_MESUp      " )  ;
 h_mctotal_MESDown     = (TH1F*)file_input_MESDown    ->Get("bkgtotal")->Clone("bkgtotal_MESDown    " )  ;
 h_mctotal_AMaxUp      = (TH1F*)file_input_AMaxUp     ->Get("bkgtotal")->Clone("bkgtotal_AMaxUp     " )  ;
 h_mctotal_AMaxDown    = (TH1F*)file_input_AMaxDown   ->Get("bkgtotal")->Clone("bkgtotal_AMaxDown   " )  ;
 h_mctotal_IPSigUp     = (TH1F*)file_input_IPSigUp    ->Get("bkgtotal")->Clone("bkgtotal_IPSigUp    " )  ;
 h_mctotal_IPSigDown   = (TH1F*)file_input_IPSigDown  ->Get("bkgtotal")->Clone("bkgtotal_IPSigDown  " )  ;
 h_mctotal_TAUp        = (TH1F*)file_input_TAUp       ->Get("bkgtotal")->Clone("bkgtotal_TAUp       " )  ;
 h_mctotal_TADown      = (TH1F*)file_input_TADown     ->Get("bkgtotal")->Clone("bkgtotal_TADown     " )  ;
 h_mctotal_TagVarsUp   = (TH1F*)file_input_TagVarsUp  ->Get("bkgtotal")->Clone("bkgtotal_TagVarsUp  " )  ;
 h_mctotal_TagVarsDown = (TH1F*)file_input_TagVarsDown->Get("bkgtotal")->Clone("bkgtotal_TagVarsDown" )  ;
 h_Sig_MS40ct10_EGSUp      = (TH1F*)file_input_EGSUp      ->Get("Sig_MS40ct10")->Clone("Sig_EGSUp      " ) ;
 h_Sig_MS40ct10_EGSDown    = (TH1F*)file_input_EGSDown    ->Get("Sig_MS40ct10")->Clone("Sig_EGSDown    " ) ;
 h_Sig_MS40ct10_MESUp      = (TH1F*)file_input_MESUp      ->Get("Sig_MS40ct10")->Clone("Sig_MESUp      " ) ;
 h_Sig_MS40ct10_MESDown    = (TH1F*)file_input_MESDown    ->Get("Sig_MS40ct10")->Clone("Sig_MESDown    " ) ;
 h_Sig_MS40ct10_AMaxUp     = (TH1F*)file_input_AMaxUp     ->Get("Sig_MS40ct10")->Clone("Sig_AMaxUp     " ) ;
 h_Sig_MS40ct10_AMaxDown   = (TH1F*)file_input_AMaxDown   ->Get("Sig_MS40ct10")->Clone("Sig_AMaxDown   " ) ;
 h_Sig_MS40ct10_IPSigUp    = (TH1F*)file_input_IPSigUp    ->Get("Sig_MS40ct10")->Clone("Sig_IPSigUp    " ) ;
 h_Sig_MS40ct10_IPSigDown  = (TH1F*)file_input_IPSigDown  ->Get("Sig_MS40ct10")->Clone("Sig_IPSigDown  " ) ;
 h_Sig_MS40ct10_TAUp       = (TH1F*)file_input_TAUp       ->Get("Sig_MS40ct10")->Clone("Sig_TAUp       " ) ;
 h_Sig_MS40ct10_TADown     = (TH1F*)file_input_TADown     ->Get("Sig_MS40ct10")->Clone("Sig_TADown     " ) ;
 h_Sig_MS40ct10_TagVarsUp  = (TH1F*)file_input_TagVarsUp  ->Get("Sig_MS40ct10")->Clone("Sig_TagVarsUp  " ) ;
 h_Sig_MS40ct10_TagVarsDown= (TH1F*)file_input_TagVarsDown->Get("Sig_MS40ct10")->Clone("Sig_TagVarsDown" ) ;

 h_mctotal_EGSUp      -> Add( h_Sig_MS40ct10_EGSUp       )  ;
 h_mctotal_EGSDown    -> Add( h_Sig_MS40ct10_EGSDown     )  ;
 h_mctotal_MESUp      -> Add( h_Sig_MS40ct10_MESUp       )  ;
 h_mctotal_MESDown    -> Add( h_Sig_MS40ct10_MESDown     )  ;
 h_mctotal_AMaxUp     -> Add( h_Sig_MS40ct10_AMaxUp      )  ;
 h_mctotal_AMaxDown   -> Add( h_Sig_MS40ct10_AMaxDown    )  ;
 h_mctotal_IPSigUp    -> Add( h_Sig_MS40ct10_IPSigUp     )  ;
 h_mctotal_IPSigDown  -> Add( h_Sig_MS40ct10_IPSigDown   )  ;
 h_mctotal_TAUp       -> Add( h_Sig_MS40ct10_TAUp        )  ;
 h_mctotal_TADown     -> Add( h_Sig_MS40ct10_TADown      )  ;
 h_mctotal_TagVarsUp  -> Add( h_Sig_MS40ct10_TagVarsUp   )  ;
 h_mctotal_TagVarsDown-> Add( h_Sig_MS40ct10_TagVarsDown )  ;

 // rebin
 h_DY             ->Rebin(rebin); 
 h_GJets          ->Rebin(rebin); 
 h_WJetsToLNu     ->Rebin(rebin); 
 h_ST             ->Rebin(rebin); 
 h_VV             ->Rebin(rebin); 
 h_VG             ->Rebin(rebin); 
 h_ZH             ->Rebin(rebin); 
 h_TT             ->Rebin(rebin); 
 h_QCD            ->Rebin(rebin); 
 h_ratio          ->Rebin(rebin); 
 h_ratiostaterr   ->Rebin(rebin); 
 h_altDY          ->Rebin(rebin); 
 h_altVV          ->Rebin(rebin); 
 h_altTT          ->Rebin(rebin); 
 h_Sig_MS15ct1000 ->Rebin(rebin); 
 h_Sig_MS15ct100  ->Rebin(rebin); 
 h_Sig_MS15ct10   ->Rebin(rebin); 
 h_Sig_MS15ct1    ->Rebin(rebin); 
 h_Sig_MS40ct1000 ->Rebin(rebin); 
 h_Sig_MS40ct100  ->Rebin(rebin); 
 h_Sig_MS40ct10   ->Rebin(rebin); 
 h_Sig_MS40ct1    ->Rebin(rebin); 
 h_Sig_MS55ct1000 ->Rebin(rebin); 
 h_Sig_MS55ct100  ->Rebin(rebin); 
 h_Sig_MS55ct10   ->Rebin(rebin); 
 h_Sig_MS55ct1    ->Rebin(rebin); 
 h_Data           ->Rebin(rebin); 

 h_mctotal                  ->Rebin(rebin); 
 h_mctotal_EGSUp            ->Rebin(rebin); 
 h_mctotal_EGSDown          ->Rebin(rebin); 
 h_mctotal_MESUp            ->Rebin(rebin); 
 h_mctotal_MESDown          ->Rebin(rebin); 
 h_mctotal_AMaxUp           ->Rebin(rebin); 
 h_mctotal_AMaxDown         ->Rebin(rebin); 
 h_mctotal_IPSigUp          ->Rebin(rebin); 
 h_mctotal_IPSigDown        ->Rebin(rebin); 
 h_mctotal_TAUp             ->Rebin(rebin); 
 h_mctotal_TADown           ->Rebin(rebin); 
 h_mctotal_TagVarsUp        ->Rebin(rebin); 
 h_mctotal_TagVarsDown      ->Rebin(rebin); 
 h_Sig_MS40ct10_EGSUp       ->Rebin(rebin); 
 h_Sig_MS40ct10_EGSDown     ->Rebin(rebin); 
 h_Sig_MS40ct10_MESUp       ->Rebin(rebin); 
 h_Sig_MS40ct10_MESDown     ->Rebin(rebin); 
 h_Sig_MS40ct10_AMaxUp      ->Rebin(rebin); 
 h_Sig_MS40ct10_AMaxDown    ->Rebin(rebin); 
 h_Sig_MS40ct10_IPSigUp     ->Rebin(rebin); 
 h_Sig_MS40ct10_IPSigDown   ->Rebin(rebin); 
 h_Sig_MS40ct10_TAUp        ->Rebin(rebin); 
 h_Sig_MS40ct10_TADown      ->Rebin(rebin); 
 h_Sig_MS40ct10_TagVarsUp   ->Rebin(rebin); 
 h_Sig_MS40ct10_TagVarsDown ->Rebin(rebin); 

 // make stack
 std::vector<TH1F *> v;
 v.push_back(h_DY);
 v.push_back(h_GJets);
 v.push_back(h_ST);
 v.push_back(h_TT);
 v.push_back(h_WJetsToLNu);
 v.push_back(h_VV);
 v.push_back(h_VG);
 v.push_back(h_QCD);
 v.push_back(h_ZH);
 v.push_back(h_Sig_MS40ct10);

 THStack *mcstack = new THStack("mcstack","");
 if(dolog){
  std::sort(v.begin(), v.end(),
            [](TH1F *a, TH1F *b) { return a->Integral() < b->Integral(); });
  for(int zz=0; zz<v.size(); zz++)
  {
   mcstack->Add(v[zz]);
   //cout <<v[zz]->Integral()<<std::endl;
  }
 }
 else{
  mcstack->Add(h_DY         );
  mcstack->Add(h_GJets      );
  mcstack->Add(h_ST         );
  mcstack->Add(h_TT         );
  mcstack->Add(h_WJetsToLNu );
  mcstack->Add(h_VV         );
  mcstack->Add(h_VG         );
  mcstack->Add(h_QCD        );
  mcstack->Add(h_ZH         );
  mcstack->Add(h_Sig_MS40ct10         );
 }


 // set attributes

 h_mctotal_EGSUp       ->SetLineColor(632);
 h_mctotal_EGSDown     ->SetLineColor(632);
 h_mctotal_MESUp       ->SetLineColor(807);
 h_mctotal_MESDown     ->SetLineColor(807);
 h_mctotal_AMaxUp      ->SetLineColor(798);
 h_mctotal_AMaxDown    ->SetLineColor(798);
 h_mctotal_IPSigUp     ->SetLineColor(418);
 h_mctotal_IPSigDown   ->SetLineColor(418);
 h_mctotal_TAUp        ->SetLineColor(601);
 h_mctotal_TADown      ->SetLineColor(601);
 h_mctotal_TagVarsUp   ->SetLineColor(599);
 h_mctotal_TagVarsDown ->SetLineColor(599);

 h_mctotal_EGSUp       ->SetLineWidth(2);
 h_mctotal_EGSDown     ->SetLineWidth(2);
 h_mctotal_MESUp       ->SetLineWidth(2);
 h_mctotal_MESDown     ->SetLineWidth(2);
 h_mctotal_AMaxUp      ->SetLineWidth(2);
 h_mctotal_AMaxDown    ->SetLineWidth(2);
 h_mctotal_IPSigUp     ->SetLineWidth(2);
 h_mctotal_IPSigDown   ->SetLineWidth(2);
 h_mctotal_TAUp        ->SetLineWidth(2);
 h_mctotal_TADown      ->SetLineWidth(2);
 h_mctotal_TagVarsUp   ->SetLineWidth(2);
 h_mctotal_TagVarsDown ->SetLineWidth(2);

 h_mctotal_EGSUp       ->SetFillStyle(0);
 h_mctotal_EGSDown     ->SetFillStyle(0);
 h_mctotal_MESUp       ->SetFillStyle(0);
 h_mctotal_MESDown     ->SetFillStyle(0);
 h_mctotal_AMaxUp      ->SetFillStyle(0);
 h_mctotal_AMaxDown    ->SetFillStyle(0);
 h_mctotal_IPSigUp     ->SetFillStyle(0);
 h_mctotal_IPSigDown   ->SetFillStyle(0);
 h_mctotal_TAUp        ->SetFillStyle(0);
 h_mctotal_TADown      ->SetFillStyle(0);
 h_mctotal_TagVarsUp   ->SetFillStyle(0);
 h_mctotal_TagVarsDown ->SetFillStyle(0);

 //h_ggZH_HToSSTobbbb_MS40_ctauS0     -> SetLineColor(632) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS0p05  -> SetLineColor(807) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS1     -> SetLineColor(798) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS10    -> SetLineColor(418) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS100   -> SetLineColor(601) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS1000  -> SetLineColor(599) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS10000 -> SetLineColor(618) ;

 //h_ggZH_HToSSTobbbb_MS40_ctauS0     -> SetLineWidth(2) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS0p05  -> SetLineWidth(2) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS1     -> SetLineWidth(2) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS10    -> SetLineWidth(2) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS100   -> SetLineWidth(2) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS1000  -> SetLineWidth(2) ;
 //h_ggZH_HToSSTobbbb_MS40_ctauS10000 -> SetLineWidth(2) ;

 h_Data  -> SetLineColor(kBlack);
 h_Data  -> SetMarkerStyle(8);
 h_Data  -> SetMarkerSize(1);
 h_Data  -> SetLineWidth(3);

 h_DY           ->SetFillStyle(1001);
 h_GJets        ->SetFillStyle(1001);
 h_ST           ->SetFillStyle(1001);
 h_TT           ->SetFillStyle(1001);
 h_WJetsToLNu   ->SetFillStyle(1001);
 h_VV           ->SetFillStyle(1001);
 h_VG           ->SetFillStyle(1001);
 h_ZH           ->SetFillStyle(1001);
 h_QCD          ->SetFillStyle(1001);
 h_Sig_MS40ct10 ->SetFillStyle(1001);

 h_DY           ->SetFillColor(kAzure-3);
 h_GJets        ->SetFillColor(kViolet+3);
 h_ST           ->SetFillColor(kOrange+8);
 h_TT           ->SetFillColor(kGreen+1);
 h_WJetsToLNu   ->SetFillColor(kViolet-3);
 h_VV           ->SetFillColor(kRed);
 h_VG           ->SetFillColor(kPink+9);
 h_ZH           ->SetFillColor(kCyan);
 h_QCD          ->SetFillColor(kGray+1);
 h_Sig_MS40ct10 ->SetFillColor(kGreen);

 h_DY           ->SetLineColor(kBlack); 
 h_GJets        ->SetLineColor(kBlack); 
 h_ST           ->SetLineColor(kBlack); 
 h_TT           ->SetLineColor(kBlack); 
 h_WJetsToLNu   ->SetLineColor(kBlack); 
 h_VV           ->SetLineColor(kBlack); 
 h_VG           ->SetLineColor(kBlack); 
 h_ZH           ->SetLineColor(kBlack); 
 h_Sig_MS40ct10 ->SetLineColor(kBlack); 
 h_QCD          ->SetLineColor(kBlack); 
 h_mctotal      ->SetLineColor(kBlack);

 h_DY           ->SetLineWidth(2);
 h_GJets        ->SetLineWidth(2);
 h_ST           ->SetLineWidth(2);
 h_TT           ->SetLineWidth(2);
 h_WJetsToLNu   ->SetLineWidth(2);
 h_VV           ->SetLineWidth(2);
 h_VG           ->SetLineWidth(2);
 h_ZH           ->SetLineWidth(2);
 h_Sig_MS40ct10 ->SetLineWidth(2);
 h_QCD          ->SetLineWidth(2);
 h_mctotal      ->SetLineWidth(2);

 h_mctotal->SetFillColorAlpha(kYellow+1, 0.7);
 h_mctotal->SetFillStyle(1001);

 // make legend
 TLegend *leg;
 leg = new TLegend(0.2,0.7,0.88,0.88);
 leg->SetBorderSize(0);
 leg->SetNColumns(2);
 leg->SetFillColor(kWhite);
 leg->AddEntry(h_Data         , "Data", "lpe"); 
 leg->AddEntry(h_DY           , "Drell-Yan", "f"); 
 leg->AddEntry(h_GJets        , "#gamma+Jets", "f"); 
 leg->AddEntry(h_ST           , "Single Top", "f"); 
 leg->AddEntry(h_TT           , "t#bar{t}+Jets", "f"); 
 leg->AddEntry(h_WJetsToLNu   , "W+Jets", "f"); 
 leg->AddEntry(h_VV           , "Diboson", "f"); 
 leg->AddEntry(h_VG           , "V#gamma", "f");
 leg->AddEntry(h_ZH           , "ZH#rightarrowLLbb", "f");
 leg->AddEntry(h_QCD          , "QCD", "f"); 
 leg->AddEntry(h_Sig_MS40ct10 , "Signal M_{S}40 c#tau 10", "f");
 leg->AddEntry(h_mctotal      , "MC bkg. stat. err.", "f");

 TLegend *sigleg = new TLegend(0.15,0.6,0.65,0.85);
 //if(drawSignal){
 //  //sigleg->SetBorderSize(0);
 //  //sigleg->SetFillColor(kWhite);
 //  //sigleg->SetHeader("Z(H#rightarrow SS#rightarrow bbbb)","C");
 //  //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0     , "M_{S}=40 c#tau_{S}=0    ", "l" ) ;
 //  //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0p05  , "M_{S}=40 c#tau_{S}=0p05 ", "l" ) ;
 //  //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1     , "M_{S}=40 c#tau_{S}=1    ", "l" ) ;
 //  //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10    , "M_{S}=40 c#tau_{S}=10   ", "l" ) ;
 //  //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS100   , "M_{S}=40 c#tau_{S}=100  ", "l" ) ;
 //  //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1000  , "M_{S}=40 c#tau_{S}=1000 ", "l" ) ;
 //  //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10000 , "M_{S}=40 c#tau_{S}=10000", "l" ) ;
 // }

 TLegend *uncleg = new TLegend(0.5,0.3,0.85,0.65);
  uncleg->SetBorderSize(0);
  uncleg->SetFillColor(kWhite);
  //uncleg->AddEntry(h_mctotal_EGSUp      , "EGSUp      " , "l" ); 
  //uncleg->AddEntry(h_mctotal_EGSDown    , "EGSDown    " , "l" ); 
  //uncleg->AddEntry(h_mctotal_MESUp      , "MESUp      " , "l" ); 
  //uncleg->AddEntry(h_mctotal_MESDown    , "MESDown    " , "l" ); 
  //uncleg->AddEntry(h_mctotal_AMaxUp     , "AMaxUp     " , "l" ); 
  //uncleg->AddEntry(h_mctotal_AMaxDown   , "AMaxDown   " , "l" ); 
  //uncleg->AddEntry(h_mctotal_IPSigUp    , "IPSigUp    " , "l" ); 
  //uncleg->AddEntry(h_mctotal_IPSigDown  , "IPSigDown  " , "l" ); 
  //uncleg->AddEntry(h_mctotal_TAUp       , "TAUp       " , "l" ); 
  //uncleg->AddEntry(h_mctotal_TADown     , "TADown     " , "l" ); 
  //uncleg->AddEntry(h_mctotal_TagVarsUp  , "TagVarsUp  " , "l" ); 
  //uncleg->AddEntry(h_mctotal_TagVarsDown, "TagVarsDown" , "l" ); 
  uncleg->AddEntry(h_mctotal_EGSUp      , "E/#gamma energy scale" , "l" ); 
  uncleg->AddEntry(h_mctotal_MESUp      , "muon energy scale   " , "l" ); 
  uncleg->AddEntry(h_mctotal_AMaxUp     , "Alpha Max            " , "l" ); 
  uncleg->AddEntry(h_mctotal_IPSigUp    , "IPSig                " , "l" ); 
  uncleg->AddEntry(h_mctotal_TAUp       , "Track Angle          " , "l" ); 
  //uncleg->AddEntry(h_mctotal_TagVarsUp  , "All TagVars          " , "l" ); 

  // set max and draw
  Double_t ymax;
  ymax = std::max(h_Data->GetMaximum(), h_mctotal->GetMaximum() );
  
  if(dolog){
   mcstack->SetMaximum(500*ymax); 
   mcstack->SetMinimum(1.0);
  } 
  else {
   mcstack->SetMaximum(ymax*1.4);
  }
   
  plotpad->cd();
  mcstack->Draw("hist");
  //mcstack->Draw("hist e");
  mcstack->GetYaxis()->SetTitle("Events");
  mcstack->GetYaxis()->SetTitleSize(40);
  mcstack->GetYaxis()->SetTitleFont(43);
  mcstack->GetYaxis()->SetTitleOffset(1.55);
  if(drawuncs){
   h_mctotal_EGSUp       ->Draw("hist sames");
   h_mctotal_EGSDown     ->Draw("hist sames");
   h_mctotal_MESUp       ->Draw("hist sames");
   h_mctotal_MESDown     ->Draw("hist sames");
   h_mctotal_AMaxUp      ->Draw("hist sames");
   h_mctotal_AMaxDown    ->Draw("hist sames");
   h_mctotal_IPSigUp     ->Draw("hist sames");
   h_mctotal_IPSigDown   ->Draw("hist sames");
   h_mctotal_TAUp        ->Draw("hist sames");
   h_mctotal_TADown      ->Draw("hist sames");
   //h_mctotal_TagVarsUp   ->Draw("hist sames");
   //h_mctotal_TagVarsDown ->Draw("hist sames");
  }
  h_mctotal->Draw("e2 sames");
  h_Data->Draw("sames E"); 

//    if(drawSignal){
//     h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Draw("hist sames") ;
//     sigleg->Draw();
//    }
    leg->Draw();
  if(drawuncs){
   uncleg->Draw();
  }

    char lumistring [50];
    int dummy; 

    // add titles
    title->DrawTextNDC(0.2,0.91,"CMS");
    extra->DrawTextNDC(0.3,0.91,"Preliminary");
    if(HIP){
     extra2->DrawTextNDC(0.51,0.91,"Eras B-F");
     dummy=sprintf (lumistring, "%0.1f", lumiBCDEF/1000.);
    }
    else{
     extra2->DrawTextNDC(0.51,0.91,"Eras GH");
     dummy=sprintf (lumistring, "%0.1f", lumiGH/1000.);
    }
    //lumi->DrawTextNDC(0.9,0.91,"35.9 /fb (13 TeV)");
    lumi->DrawTextNDC(0.9,0.91,(TString)lumistring+" /fb (13 TeV)");


     ratiopad->cd();
     h_ratio = (TH1F*)h_Data->Clone("h_ratio");
     if(h_Data->Integral(-1,-1)>0){
      h_ratio->Divide(h_mctotal);
     }
     h_ratio->SetTitle(" ");
     // Y axis ratio plot settings
     h_ratio->GetYaxis()->SetTitleSize(40);
     h_ratio->GetYaxis()->SetTitleFont(43);
     h_ratio->GetYaxis()->SetTitleOffset(1.55);
     h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
     h_ratio->GetYaxis()->SetLabelSize(20);
     h_ratio->GetYaxis()->SetNdivisions(-105);
     h_ratio->GetYaxis()->SetTitle("Data/MC");
     // X axis ratio plot settings
     h_ratio->GetXaxis()->SetTitleSize(40);
     h_ratio->GetXaxis()->SetTitleFont(43);
     h_ratio->GetXaxis()->SetTitle(h_Data->GetTitle());
     h_ratio->GetXaxis()->SetTitleOffset(4.0);
     h_ratio->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
     h_ratio->GetXaxis()->SetLabelSize(20);//20
     h_ratio->SetMarkerStyle(20);
     h_ratio->SetMarkerColor(kRed);
     h_ratio->SetMarkerSize(1);
     h_ratio->GetYaxis()->SetRangeUser(0,2);
     h_ratio->Draw("ep");  // draw first to get ranges set internally inside root

     h_ratiostaterr = (TH1F*)h_mctotal->Clone("h_ratiostaterr");
     h_ratiostaterr->Divide(h_mctotal);

     ratiopad->Update();       // need to update pad to get X min/max
     TLine *line = new TLine(ratiopad->GetUxmin(),1,ratiopad->GetUxmax(),1);
     line->SetLineColor(kBlue);
     line->SetLineWidth(3);
     line->SetLineStyle(9);
     h_ratiostaterr->Draw("e2 same");
     line->Draw();
     h_ratio->Draw("ep same"); // draw points above line
 
     // save canvas
     canvas->SaveAs(outname+".png");
     canvas->SaveAs(outname+".pdf");


     // Uncertainties and central value only
     canvas->Clear(); 

     h_mctotal_line = (TH1F*)h_mctotal->Clone("h_mctotal_line");
     h_mctotal_line->SetFillColor(0);
     h_mctotal_line->SetLineWidth(4);
     h_mctotal_line->SetLineColor(kBlack);

     h_mctotal_EGSUp       ->SetLineColor(632);
     h_mctotal_EGSDown     ->SetLineColor(632);
     h_mctotal_MESUp       ->SetLineColor(807);
     h_mctotal_MESDown     ->SetLineColor(807);
     h_mctotal_AMaxUp      ->SetLineColor(798);
     h_mctotal_AMaxDown    ->SetLineColor(798);
     h_mctotal_IPSigUp     ->SetLineColor(418);
     h_mctotal_IPSigDown   ->SetLineColor(418);
     h_mctotal_TAUp        ->SetLineColor(601);
     h_mctotal_TADown      ->SetLineColor(601);
     h_mctotal_TagVarsUp   ->SetLineColor(599);
     h_mctotal_TagVarsDown ->SetLineColor(599);

     TLegend *uncleg2 = new TLegend(0.12,0.7,0.80,0.85);
     uncleg2->SetBorderSize(0);
     uncleg2->SetFillColor(kWhite);
     uncleg2->SetNColumns(2);
     uncleg2->AddEntry(h_Data               , "data" , "lpe" );
     uncleg2->AddEntry(h_mctotal_line       , "Total MC"              , "l" );
     uncleg2->AddEntry(h_mctotal_EGSUp      , "E/#gamma energy scale" , "l" ); 
     uncleg2->AddEntry(h_mctotal_MESUp      , "muon energy scale    " , "l" ); 
     uncleg2->AddEntry(h_mctotal_AMaxUp     , "Alpha Max            " , "l" ); 
     uncleg2->AddEntry(h_mctotal_IPSigUp    , "IPSig                " , "l" ); 
     uncleg2->AddEntry(h_mctotal_TAUp       , "Track Angle          " , "l" ); 
     uncleg2->AddEntry(h_mctotal_TagVarsUp  , "All TagVars          " , "l" ); 

     h_mctotal_line->Draw("hist");
     h_mctotal_line->SetMaximum(h_mctotal_line->GetMaximum()*1.4);
     //mcstack->Draw("hist e");
     h_mctotal_line->GetYaxis()->SetTitle("Events");
     h_mctotal_line->GetYaxis()->SetTitleSize(40);
     h_mctotal_line->GetYaxis()->SetTitleFont(43);
     h_mctotal_line->GetYaxis()->SetTitleOffset(1.55);
     h_mctotal_line->Draw("hist");
     h_mctotal_EGSUp       ->Draw("hist sames");
     h_mctotal_EGSDown     ->Draw("hist sames");
     h_mctotal_MESUp       ->Draw("hist sames");
     h_mctotal_MESDown     ->Draw("hist sames");
     h_mctotal_AMaxUp      ->Draw("hist sames");
     h_mctotal_AMaxDown    ->Draw("hist sames");
     h_mctotal_IPSigUp     ->Draw("hist sames");
     h_mctotal_IPSigDown   ->Draw("hist sames");
     h_mctotal_TAUp        ->Draw("hist sames");
     h_mctotal_TADown      ->Draw("hist sames");
     h_mctotal_TagVarsUp   ->Draw("hist sames");
     h_mctotal_TagVarsDown ->Draw("hist sames");
     h_mctotal->Draw("e2 sames");
     h_Data->Draw("sames E"); 
     uncleg2->Draw();

     // save canvas
     canvas->SaveAs(outname+"_unconly.png");
     canvas->SaveAs(outname+"_unconly.pdf");
     


     //// save histograms into single root file
     //TFile *outfile = TFile::Open(outname+".root","RECREATE");
     //h_Data        ->Write();
     //h_DY          ->Write();
     //h_GJets       ->Write();
     //h_ST          ->Write();
     //h_TT          ->Write();
     //h_WJetsToLNu  ->Write();
     //h_VV          ->Write();
     //h_VG          ->Write();
     //h_ZH          ->Write();
     //h_mctotal    ->Write();
     //h_ratio       ->Write();
     //h_ratiostaterr->Write();
     //mcstack       ->Write();
     //outfile->Close();
  
}
