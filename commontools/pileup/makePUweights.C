
#include <stdlib.h>  

void makePUweights(TString Tsample)
{

 char* cinpath;
 cinpath = getenv ("CMSSW_BASE");
 TString tinpath = (TString)cinpath;
 tinpath.Append("/src/LLDJstandalones/commontools/pileup/");

 // set up names
 TString inname_mc = "mix_2016_25ns_Moriond17MC_PoissonOOTPU.txt";
 TString inname_data66017 = "PU_"+Tsample+"_66017.root";
 TString inname_data69200 = "PU_"+Tsample+"_69200.root";
 TString inname_data72383 = "PU_"+Tsample+"_72383.root";
 TString oname_base = "puWeights_"+Tsample+"_69200" ;

 TFile* file_data66017 ;
 TFile* file_data69200 ;
 TFile* file_data72383 ;

 // histos to be made
 TH1F* h_data66017      ; 
 TH1F* h_data69200      ; 
 TH1F* h_data72383      ; 
 TH1F* h_mc             ;
 TH1F* h_PUweight       ;
 TH1F* h_PUweight_Up    ;
 TH1F* h_PUweight_Down  ;

 // make mc histogram from txt file
 std::fstream infile_mc(tinpath+inname_mc, std::ios_base::in);

 // first fill values into a vector
 std::vector<float> mc_values;
 mc_values.clear();

 float a;
 while (infile_mc >> a)
 {
  //printf("%f \n", a);
  mc_values.push_back(a);   
 }

 Int_t mc_size = mc_values.size();
 // initialize histogram with correct dimensions
 h_mc = new TH1F("h_mc","h_mc",mc_size,0.,mc_size);
 h_mc ->Sumw2(); 
 for(unsigned int i=0; i<mc_values.size(); ++i){
  //printf("%i %f\n",i,mc_values.at(i));
  h_mc->SetBinContent(i+1,mc_values.at(i));
 }

 // already normalized
 //printf("%f\n",h_mc->Integral(-1,-1));
 

 // load data histogram files
 file_data66017 = new TFile( tinpath + inname_data66017 ) ;
 file_data69200 = new TFile( tinpath + inname_data69200 ) ;
 file_data72383 = new TFile( tinpath + inname_data72383 ) ;

 // load data histograms
 h_data66017 = (TH1F*)file_data66017 -> Get("pileup")->Clone("h_data66017") ; 
 h_data69200 = (TH1F*)file_data69200 -> Get("pileup")->Clone("h_data69200") ; 
 h_data72383 = (TH1F*)file_data72383 -> Get("pileup")->Clone("h_data72383") ; 
 //h_data66017 ->Sumw2(); 
 //h_data69200 ->Sumw2(); 
 //h_data72383 ->Sumw2(); 

 // normalize data histograms
 h_data66017 -> Scale( 1. / h_data66017->Integral(-1,-1) ); 
 h_data69200 -> Scale( 1. / h_data69200->Integral(-1,-1) ); 
 h_data72383 -> Scale( 1. / h_data72383->Integral(-1,-1) ); 


 // make ratios ( factor applied to MC, so weight = data / mc )
 h_PUweight      = (TH1F*)h_data69200->Clone("h_PUweight     ") ;
 h_PUweight_Down = (TH1F*)h_data66017->Clone("h_PUweight_Down") ;
 h_PUweight_Up   = (TH1F*)h_data72383->Clone("h_PUweight_Up  ") ;
 h_PUweight      ->Divide(h_mc); 
 h_PUweight_Up   ->Divide(h_mc); 
 h_PUweight_Down ->Divide(h_mc); 

 h_data66017    -> SetDirectory(0); 
 h_data69200    -> SetDirectory(0); 
 h_data72383    -> SetDirectory(0); 
 h_mc           -> SetDirectory(0);
 h_PUweight     -> SetDirectory(0);  
 h_PUweight_Up  -> SetDirectory(0);  
 h_PUweight_Down-> SetDirectory(0);  


 // ------- Draw -----------
 // make canvas and text
 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 gStyle->SetOptStat(0);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);
 gStyle->SetPalette(kDarkRainBow);
 //gStyle->SetPalette(kBird);

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.04);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.04);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 //extra->SetTextAlign(13);
 extra->SetTextFont(52);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.03);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);


 // set attributes
 h_data66017 -> SetLineWidth(2); 
 h_data69200 -> SetLineWidth(2); 
 h_data72383 -> SetLineWidth(2); 
 h_mc        -> SetLineWidth(2);
 h_mc        -> SetLineColor(kBlack);
 h_PUweight      ->SetLineWidth(2); 
 h_PUweight_Up   ->SetLineWidth(2); 
 h_PUweight_Down ->SetLineWidth(2); 

 // make legend
 TLegend *leg = new TLegend(0.5,0.6,0.85,0.85);
 leg->SetBorderSize(0);
 leg->SetFillColor(kWhite);
 leg->AddEntry(h_data66017 , "Data, xc=66017","l"); 
 leg->AddEntry(h_data69200 , "Data, xc=69200","l"); 
 leg->AddEntry(h_data72383 , "Data, xc=72383","l"); 
 leg->AddEntry(h_mc        , "MC"            ,"l");


 //Double_t ymax = h_data66017->GetMaximum();
 h_data66017->SetMaximum(0.1);

 h_data66017 -> Draw("hist PLC"); 
 h_data69200 -> Draw("hist PLC sames"); 
 h_data72383 -> Draw("hist PLC sames"); 
 h_mc        -> Draw("hist sames");
 leg->Draw();

 // add titles
 title->DrawTextNDC(0.13,0.91,"CMS");
 extra->DrawTextNDC(0.23,0.91,"Preliminary");
 lumi->DrawTextNDC(0.9,0.91,"35.9 /fb (13 TeV)");
 h_data66017->GetXaxis()->SetTitle("Pileup");
 h_data66017->GetYaxis()->SetTitle("Events (unit normalized)");
 h_data66017->GetYaxis()->SetTitleOffset(1.5);
 h_data66017->SetTitle("");

 gPad->Update();
 gPad->RedrawAxis();

 // save canvas
 canvas->SaveAs(tinpath + oname_base+"_inputs.pdf");

 // now plot ratios

 // make legend
 TLegend *leg2 = new TLegend(0.5,0.6,0.85,0.85);
 leg2->SetBorderSize(0);
 leg2->SetFillColor(kWhite);
 leg2->AddEntry(h_PUweight     ,"SF","l")  ;
 leg2->AddEntry(h_PUweight_Up  ,"SF Up","l")  ;
 leg2->AddEntry(h_PUweight_Down,"SF Down","l")  ;

 h_PUweight->SetMaximum(2);
 h_PUweight     -> Draw("hist PLC"); 
 h_PUweight_Up  -> Draw("hist PLC sames"); 
 h_PUweight_Down-> Draw("hist PLC sames"); 
 leg2->Draw();

 // add titles
 title->DrawTextNDC(0.13,0.91,"CMS");
 extra->DrawTextNDC(0.23,0.91,"Preliminary");
 lumi->DrawTextNDC(0.9,0.91,"35.9 /fb (13 TeV)");
 h_PUweight->GetXaxis()->SetTitle("Pileup");
 h_PUweight->GetYaxis()->SetTitle("Weight Factor (data/mc)");
 h_PUweight->GetYaxis()->SetTitleOffset(1.5);
 h_PUweight->SetTitle("");

 gPad->Update();
 gPad->RedrawAxis();

 // save canvas
 canvas->SaveAs(tinpath + oname_base+"_weights.pdf");

 TFile *outfile = new TFile(tinpath + oname_base + ".root","RECREATE");

 h_data66017    -> SetLineColor(kBlack); 
 h_data69200    -> SetLineColor(kBlack); 
 h_data72383    -> SetLineColor(kBlack); 
 h_mc           -> SetLineColor(kBlack);
 h_PUweight     -> SetLineColor(kBlack);  
 h_PUweight_Up  -> SetLineColor(kBlack);  
 h_PUweight_Down-> SetLineColor(kBlack);  

 h_data66017 -> Write(); 
 h_data69200 -> Write(); 
 h_data72383 -> Write(); 
 h_mc        -> Write();
 h_PUweight     -> Write();  
 h_PUweight_Up  -> Write();  
 h_PUweight_Down-> Write();  

 outfile->Close();
}
