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

void plotter_tagvarUnc(TString region, TString varname, Bool_t dolog, Bool_t HIP )
{

 // Setup running configuration: IO, naming, SFs, ..
 /////////////////////////////////////////////////////

 TString inpath  = TString("../plots/");
 TString outpath = TString("../plots/");
 TString aversion = TString(getenv("aversion"));

 inpath = inpath+aversion+"/"+region+"/";
 outpath = outpath+aversion+"/"+region+"/";

 Float_t lumiBCDEF = 19691. ;
 Float_t lumiGH = 16226.5 ;

 Int_t rebin=1;

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

 TString extraname = "";
 if(dolog){
  extraname+="_log";
 }

 TString infilename = region+"_"+varname+eraname;
 // std::cout<<"name: "<<inpath<<" "<<infilename<<std::endl;

 // canvas and text attributes
 int canx = 1100;
 int cany = 1200;
 float lmarg = 0.12;
 float rmarg = 0.05;
 
 TCanvas* canvas = new TCanvas("canvas","canvas",canx,cany); 
 TCanvas* canva2 = new TCanvas("canva2","canva2",canx,cany); 

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
 TH1F* h_QCD    ;
 TH1F* h_ZH     ;
 TH1F* h_TT     ;
 TH1F* h_WJetsToLNu;
 TH1F* h_bkgtotal ;
 TH1F* h_altDY ;
 TH1F* h_altVV ;
 TH1F* h_altTT ;
 TH1F* h_Sig ;
 TH1F* h_Sig40 ;
 //TH1F* h_Sig_MS15ct1000 ;
 //TH1F* h_Sig_MS15ct100  ;
 //TH1F* h_Sig_MS15ct10   ;
 //TH1F* h_Sig_MS15ct1    ;
 //TH1F* h_Sig_MS40ct1000 ;
 //TH1F* h_Sig_MS40ct100  ;
 //TH1F* h_Sig_MS40ct10   ;
 //TH1F* h_Sig_MS40ct1    ;
 //TH1F* h_Sig_MS55ct1000 ;
 //TH1F* h_Sig_MS55ct100  ;
 //TH1F* h_Sig_MS55ct10   ;
 //TH1F* h_Sig_MS55ct1    ;
 TH1F* h_Data   ;
 THStack* bgstack;

 TH1F* h_DataInt;
 TH1F* h_MCInt;

 TH1F* h_NormDataInt;
 TH1F* h_NormMCInt;

 // load common histogram files / histograms
 file_input = new TFile( inpath + infilename + ".root"               ) ; 
 h_DY             = (TH1F*)file_input->Get("DY"            )->Clone("DY"            )  ;
 h_GJets          = (TH1F*)file_input->Get("GJets"         )->Clone("GJets"         )  ;
 h_WJetsToLNu     = (TH1F*)file_input->Get("WJetsToLNu"    )->Clone("WJetsToLNu"    )  ;
 h_ST             = (TH1F*)file_input->Get("ST"            )->Clone("ST"            )  ;
 h_VV             = (TH1F*)file_input->Get("VV"            )->Clone("VV"            )  ;
 h_VG             = (TH1F*)file_input->Get("VG"            )->Clone("VG"            )  ;
 h_QCD            = (TH1F*)file_input->Get("QCD"           )->Clone("QCD"           )  ;
 h_ZH             = (TH1F*)file_input->Get("ZH"            )->Clone("ZH"            )  ;
 h_TT             = (TH1F*)file_input->Get("TT"            )->Clone("TT"            )  ;
 h_altDY          = (TH1F*)file_input->Get("altDY"         )->Clone("altDY"         )  ;
 h_altVV          = (TH1F*)file_input->Get("altVV"         )->Clone("altVV"         )  ;
 h_altTT          = (TH1F*)file_input->Get("altTT"         )->Clone("altTT"         )  ;
 h_Data           = (TH1F*)file_input->Get("Data"          )->Clone("Data"          )  ;

 h_DY         ->Rebin(rebin); 
 h_GJets      ->Rebin(rebin); 
 h_WJetsToLNu ->Rebin(rebin); 
 h_ST         ->Rebin(rebin); 
 h_VV         ->Rebin(rebin); 
 h_VG         ->Rebin(rebin); 
 h_QCD        ->Rebin(rebin);
 h_ZH         ->Rebin(rebin); 
 h_TT         ->Rebin(rebin); 
 h_altDY      ->Rebin(rebin); 
 h_altVV      ->Rebin(rebin); 
 h_altTT      ->Rebin(rebin); 
 h_Data       ->Rebin(rebin); 

 std::vector<TString> MSs;
 std::vector<TString> cts;
 //MSs.push_back("15");
 MSs.push_back("40");
 //MSs.push_back("55");
 //cts.push_back("1");
 cts.push_back("10");
 //cts.push_back("100");
 //cts.push_back("1000");

 for(unsigned int i=0; i<MSs.size(); ++i){
  TString MS = MSs.at(i);
  //std::cout<<MS<<std::endl;
  for(unsigned int i=0; i<cts.size(); ++i){
   TString ct = cts.at(i);
   //std::cout<<ct<<std::endl;

   //TString outname = "tvuMS"+MS+"ct"+ct+"_"+lepname+"_"+region+"_"+varname+eraname;
   TString outname = "tvuMS"+MS+"ct"+ct+"_"+region+"_"+varname+eraname+extraname;
   //TString infilename = region+"_"+varname+eraname;
   outname = outpath + outname;
   //std::cout<<outname<<std::endl;

   TString signame = "Sig_MS"+MS+"ct"+ct;
   //TString signame = (TString)"Sig_MS"+MS.Data()+(TString)"ct"+ct.Data();
   //std::cout<<signame<<std::endl;
   h_Sig = (TH1F*)file_input->Get(signame.Data())->Clone("h_Sig")  ;
   h_Sig->SetFillColor(kOrange+8);
   h_Sig->SetLineWidth(2);
   h_Sig->SetLineColor(kBlack);
   h_Sig40 = (TH1F*)h_Sig->Clone("h_Sig40"); 
   h_Sig40->Scale(40000);
   h_Sig40->SetFillStyle(0);
   h_Sig40->SetLineColor(kOrange+8);
   //bgstack          = (THStack*)file_input->Get("bgstack"    )->Clone("bgstack"       )  ;

   h_bkgtotal       = (TH1F*)file_input->Get("bkgtotal"      )->Clone("bkgtotal"      )  ;
   h_bkgtotal->Add(h_Sig);

   h_Sig     -> Rebin(rebin); 
   h_Sig40   -> Rebin(rebin);  
   //bgstack   -> Rebin(rebin);    
   h_bkgtotal-> Rebin(rebin);       

   //THStack *bgstack = new THStack("bgstack","");
   bgstack = new THStack("bgstack","");
   bgstack->Add(h_DY         );
   bgstack->Add(h_GJets      );   
   bgstack->Add(h_ST         );
   bgstack->Add(h_TT         );
   bgstack->Add(h_WJetsToLNu ); 
   bgstack->Add(h_VV         );
   bgstack->Add(h_VG         );
   bgstack->Add(h_QCD        );
   bgstack->Add(h_ZH         );
   bgstack->Add(h_Sig); 

   //h_bkgtotal->SetFillColorAlpha(kYellow+1, 0.7);
   //h_bkgtotal->SetFillStyle(1001);

//   printf(" size %10.10f %10.10f \n ", h_Sig->Integral(0,-1), h_bkgtotal->Integral(0,-1));

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
   leg->AddEntry(h_QCD          , "QCD", "f");
   leg->AddEntry(h_ZH           , "ZH#rightarrowLLbb", "f");
   //leg->AddEntry(h_bkgtotal     , "MC bkg. stat. err.", "f");
   leg->AddEntry(h_Sig, "Signal M_{S}"+MS+" c#tau"+ct,"f");
   leg->AddEntry(h_Sig40, "Signal x 40k","l");
  
   // set max and draw
   Double_t ymax;
   ymax = std::max(h_Data->GetMaximum(), h_bkgtotal->GetMaximum() );
   
   if(dolog){
    bgstack->SetMaximum(500*ymax); 
    bgstack->SetMinimum(1.0);
   } 
   else {
    bgstack->SetMaximum(ymax*1.4);
   }
    
   plotpad->cd();
   bgstack->Draw("hist");
   //bgstack->Draw("hist e");
   bgstack->GetYaxis()->SetTitle("Events");
   bgstack->GetYaxis()->SetTitleSize(40);
   bgstack->GetYaxis()->SetTitleFont(43);
   bgstack->GetYaxis()->SetTitleOffset(1.55);
   h_bkgtotal->Draw("e2 sames");
   // renormalize signal to show scale
//   printf( " scale: %10.10f \n", h_bkgtotal->Integral(0,-1) / h_Sig->Integral(0,-1) );
//   h_Sig->Scale( h_bkgtotal->Integral(0,-1) / h_Sig->Integral(0,-1) );
   h_Sig40->Draw("sames hist");
   h_Data->Draw("sames E"); 
   leg->Draw();
  
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
  
   // second pad
   ratiopad->cd();

   h_DataInt  = (TH1F*)h_Data->Clone("h_DataInt"     );
   h_MCInt    = (TH1F*)h_bkgtotal->Clone("h_MCInt" );

   int nbins = h_DataInt->GetNbinsX();
   //std::cout<<" nbins data "<<nbins<<" mc"<<h_MCInt->GetNbinsX()<<std::endl;
   float datasum=0.;
   float mcsum=0.;
   for( int j=1; j<nbins+1; ++j){
    int databinint = h_Data->GetBinContent(j);
    int mcbinint = h_bkgtotal->GetBinContent(j);
    //std::cout<<"  datasum "<<datasum<<" binint "<<binint<<std::endl;
    datasum = datasum + databinint;
    mcsum = mcsum + mcbinint;
    h_DataInt->SetBinContent(j,datasum);
    h_MCInt->SetBinContent(j,mcsum);
   }

   h_DataInt->Scale( 1.0/h_Data->Integral(0,-1));
   h_MCInt->Scale( 1.0/h_bkgtotal->Integral(0,-1));

   h_DataInt->SetLineColor(kBlack);
   h_MCInt->SetLineColor(kOrange+8);
   h_DataInt->SetLineWidth(2);
   h_MCInt->SetLineWidth(2);
   h_DataInt->SetFillStyle(0);
   h_MCInt->SetFillStyle(0);

   // make leg2end
   TLegend *leg2;
   leg2 = new TLegend(0.2,0.6,0.4,0.88);
   leg2->SetBorderSize(2);
   leg2->SetFillColor(kWhite);
   leg2->AddEntry(h_DataInt , "Data", "l"); 
   leg2->AddEntry(h_MCInt   , "MC", "l"); 

   // Y axis ratio plot settings
   h_DataInt->GetYaxis()->SetTitleSize(40);
   h_DataInt->GetYaxis()->SetTitleFont(43);
   h_DataInt->GetYaxis()->SetTitleOffset(1.55);
   h_DataInt->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h_DataInt->GetYaxis()->SetLabelSize(20);
   //h_DataInt->GetYaxis()->SetNdivisions(-106);
   h_DataInt->GetYaxis()->SetTitle("Integral");
   // X axis ratio plot settings
   h_DataInt->GetXaxis()->SetTitleSize(40);
   h_DataInt->GetXaxis()->SetTitleFont(43);
   h_DataInt->GetXaxis()->SetTitle(h_DataInt->GetTitle());
   h_DataInt->GetXaxis()->SetTitleOffset(4.0);
   h_DataInt->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
   h_DataInt->GetXaxis()->SetLabelSize(20);//20
   h_DataInt->GetYaxis()->SetRangeUser(0,1.1);
   h_DataInt->SetTitle(" ");
   h_DataInt->Draw("ep");  // draw first to get ranges set internally inside root
  
   ratiopad->Update();       // need to update pad to get X min/max
   TLine *line = new TLine(ratiopad->GetUxmin(),1,ratiopad->GetUxmax(),1);
   line->SetLineColor(kBlue);
   line->SetLineWidth(3);
   line->SetLineStyle(9);
   line->Draw();
   leg2->Draw();
   h_MCInt->Draw("hist same");
   h_DataInt->Draw("hist same"); // draw points above line
  
   // save canvas
   canvas->SaveAs(outname+".png");
   canvas->SaveAs(outname+".pdf");


   //// For tagging variables - calculate the shift
   if( varname.Contains("AllJets_AODCaloJetMedianLog10IPSig"     ) ||      
       varname.Contains("AllJets_AODCaloJetMedianLog10TrackAngle") ||         
       varname.Contains("AllJets_AODCaloJetAlphaMax"             ) )
   {

    // Orignal cut value
    float origcutval=-99;
    if( varname.Contains("AllJets_AODCaloJetMedianLog10IPSig"     ) ) { 
     origcutval = 1.15;
    }   
    if( varname.Contains("AllJets_AODCaloJetMedianLog10TrackAngle") ) {    
     origcutval = -1.75;
    }   
    if( varname.Contains("AllJets_AODCaloJetAlphaMax"             ) ) { 
     origcutval = 0.75;
    }   

//    h_NormDataInt = (TH1F*)h_DataInt->Clone("h_NormDataInt");
//    h_NormDataInt->Scale(1.0 / h_DataInt->Integral() );
//    h_NormMCInt = (TH1F*)h_MCInt->Clone("h_NormMCInt");
//    h_NormMCInt->Scale(1.0 / h_MCInt->Integral() );
    int binAtOrigCut = h_DataInt->GetXaxis()->FindBin(origcutval);
    float dataIntToCut = h_DataInt->GetBinContent(binAtOrigCut);
    //float dataIntToCut = h_DataInt->Integral(0,binAtOrigCut);

    TLine *lineOCV = new TLine(origcutval,0,origcutval,1);
    lineOCV->SetLineColor(kBlue);
    lineOCV->SetLineWidth(2);

    int nbins = h_DataInt->GetNbinsX();
    int binAtNewCut = 0;
    for( int j=1; j<nbins+1; ++j){
     binAtNewCut++;
     if(h_MCInt->GetBinContent(j)>dataIntToCut) break;
     //if(h_MCInt->Integral(0,j)>dataIntToCut) break;
    }

    float newcutval;
    newcutval = h_MCInt->GetXaxis()->GetBinCenter( binAtNewCut );
    TLine *lineNCV = new TLine(newcutval,0,newcutval,1);
    lineNCV->SetLineColor(kRed);
    lineNCV->SetLineWidth(2);

    //std::cout<<"OCV: "<<origcutval<<" BAC: "<<binAtOrigCut<<" ITC: "<<dataIntToCut<<" BNC: "<<binAtNewCut<<" MIC: "<<h_MCInt->Integral(0,binAtNewCut)<<std::endl;
    printf(" Original cut: %1.3f \n",origcutval); 
    printf(" New cut:      %1.3f \n",newcutval ); 

    canva2->cd();
    h_MCInt->Draw("hist");
    h_DataInt->Draw("hist same");
    h_DataInt->GetYaxis()->SetTitle("Integral");
    leg2->Draw();
    lineOCV->Draw();
    lineNCV->Draw();
    canva2->SaveAs(outname+"_int.pdf");

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
    //h_bkgtotal    ->Write();
    //h_ratio       ->Write();
    //h_ratiostaterr->Write();
    //bgstack       ->Write();
    //outfile->Close();
  
   }   

  }
 }
}
