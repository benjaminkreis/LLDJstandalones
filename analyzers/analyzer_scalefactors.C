#include "analyzer_scalefactors.h"
#include <iostream>

//----------------------------analyzer_scalefactors
analyzer_scalefactors::analyzer_scalefactors() 
{
}

//----------------------------~analyzer_scalefactors
analyzer_scalefactors::~analyzer_scalefactors()
{
}

//----------------------------makeEventWeight
Float_t analyzer_scalefactors::makeEventWeight(Float_t crossSec,
                                        Float_t lumi,
                                        Float_t nrEvents)
{
  // 1.0 for real data
  event_weight=1.0;
  Float_t crossSecScl = crossSec;
  if(isMC){ event_weight=lumi*crossSecScl/nrEvents; }
  //printf("isMC: %i lumi: %0.9f crossSec: %0.9f nrEvents: %0.9f",isMC,lumi,crossSecScl,nrEvents);
  //printf("  event_weight: %0.9f\n",event_weight);

  return event_weight;
}

//----------------------------makePUWeight
Float_t analyzer_scalefactors::makePUWeight( TString dataset ){
 Int_t tmpbin;
 Float_t tmpweight;
 if( dataset.EqualTo("DoubleEG") ){
  tmpbin    = PUWeights_DoubleEG->GetBin(AODnTruePU);
  tmpweight = PUWeights_DoubleEG->GetBinContent(tmpbin);
 }
 else if( dataset.EqualTo("DoubleMu") ){
  tmpbin    = PUWeights_DoubleMu->GetBin(AODnTruePU);
  tmpweight = PUWeights_DoubleMu->GetBinContent(tmpbin);
 }
 else if( dataset.EqualTo("MuonEG") ){
  tmpbin    = PUWeights_MuonEG->GetBin(AODnTruePU);
  tmpweight = PUWeights_MuonEG->GetBinContent(tmpbin);
 }
 else if( dataset.EqualTo("SinglePhoton") ){
  tmpbin    = PUWeights_SinglePhoton->GetBin(AODnTruePU);
  tmpweight = PUWeights_SinglePhoton->GetBinContent(tmpbin);
 }
 //printf("making PU weight for %i , %i, %f \n", AODnTruePU,tmpbin,tmpweight);
 return tmpweight;
}

//----------------------------makeElectronWeight
Float_t analyzer_scalefactors::makeElectronWeight( std::vector<int> &electron_list ){

 Float_t tmpsf;
 tmpsf = 1.;

 //check overlap with electrons
 if(electron_list.size()>0){
  //printf(" esize: %lu\n",electron_list.size());
  //printf(" esceta: %lu\n",eleSCEta->size());
  //printf(" ept: %lu\n",AOD_elePt->size());
  for(int d=0; d<electron_list.size(); ++d){
   //printf(" brgin looping over electrons\n");
   int eleindex = electron_list[d];
   //printf(" d: %i eleindex: %i\n",d,eleindex);
   //printf(" ele sceta %f pt %f \n",eleSCEta->at(eleindex),AOD_elePt->at(eleindex));
   Float_t eeta = AOD_eleEta->at(eleindex);//<------changed; don't have SCEta right now
   Float_t ept  = AOD_elePt->at(eleindex);
   Int_t tmpbinx       = EleWeights->GetXaxis()->FindBin( eeta );
   Int_t tmpbiny       = EleWeights->GetYaxis()->FindBin( ept  );
   //printf(" bins %i %i\n",tmpbinx,tmpbiny);
   Int_t tmpbin        = EleWeights->GetBin( tmpbinx, tmpbiny );
   Float_t tmpweight = EleWeights->GetBinContent(tmpbin);
   tmpsf *= tmpweight;
  }//end electrons
 } // if electrons

 //printf(" done making Electron weight\n");

 return tmpsf;
}

//----------------------------makeTTWeight
Float_t analyzer_scalefactors::makeTTWeight( Float_t TTavgweight){
  Float_t TTSF = 1.; 
  if(toppts->size() == 2){ 
   TTSF =  ( exp( 0.0615 - 0.0005*toppts->at(0)) * exp( 0.0615 - 0.0005*toppts->at(1)) ) / TTavgweight ;
   //std::cout<<" doing TTSF: "<<TTSF<<std::endl;
  }
 return TTSF;
}


//----------------------------loadPUWeight
void analyzer_scalefactors::loadPUWeight(){
 std::cout << "loading PU weight" << std::endl;
 TString filename_DoubleEG     = "puWeights_DoubleEG_69200.root" ;
 TString filename_DoubleMu     = "puWeights_DoubleMu_69200.root" ;
 TString filename_MuonEG       = "puWeights_MuonEG_69200.root" ;
 TString filename_SinglePhoton = "puWeights_SinglePhoton_69200.root" ;
 TFile* file_puweights_DoubleEG     = new TFile( filename_DoubleEG     ) ;
 TFile* file_puweights_DoubleMu     = new TFile( filename_DoubleMu     ) ;
 TFile* file_puweights_MuonEG       = new TFile( filename_MuonEG       ) ;
 TFile* file_puweights_SinglePhoton = new TFile( filename_SinglePhoton ) ;
 //std::cout <<" filename: " << filename << std::endl;
 PUWeights_DoubleEG     = (TH1F*)file_puweights_DoubleEG    ->Get("h_PUweight")->Clone("PUWeights_DoubleEG"    );
 PUWeights_DoubleMu     = (TH1F*)file_puweights_DoubleMu    ->Get("h_PUweight")->Clone("PUWeights_DoubleMu"    );
 PUWeights_MuonEG       = (TH1F*)file_puweights_MuonEG      ->Get("h_PUweight")->Clone("PUWeights_MuonEG"      );
 PUWeights_SinglePhoton = (TH1F*)file_puweights_SinglePhoton->Get("h_PUweight")->Clone("PUWeights_SinglePhoton");
 return ;
}

//----------------------------loadElectronWeight
void analyzer_scalefactors::loadElectronWeight(TString eleid){
 std::cout << "loading Electron weight" << std::endl;
 TString filename = "egammaEffi_MoriondBH_ele"+eleid+".root" ;
 TFile* file_eleweights = new TFile( filename ) ;
 std::cout << " filename: " << filename << std::endl;
 EleWeights = (TH2F*)file_eleweights->Get("EGamma_SF2D")->Clone("EleWeights");
 return ;
}


//----------------------------loadMistagRate
void analyzer_scalefactors::loadMistagRate(){

  TFile* fMistagRate = TFile::Open("feff_ZH.root", "READ");

  h_MistagRate_pt = (TH1F*)fMistagRate->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVar");
  //Systematics
  for(int i=0; i<6; i++){
    TString num = ""; num+= i;
    TString name = h_MistagRate_pt->GetName(); name+= "_sys_"; name += num;
    TH1F* temp = (TH1F*)h_MistagRate_pt->Clone();
    temp->SetName( name );
    temp->Reset();
    h_MistagRate_pt_sys.push_back( temp );
  }

  h_MistagRate_pteta = (TH2F*)fMistagRate->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar");
  //Systematics
  for(int i=0; i<6; i++){
    TString num = ""; num+= i;
    TString name = h_MistagRate_pteta->GetName(); name+= "_sys_"; name += num;

    //TH2F* temp = (TH2F*)h_MistagRate_pteta->Clone();
    //temp->SetName( name );
    //temp->Reset();

    //For some reason the normal way leads to bizarre seg faults.  
    //Recreate from scratch:
    const int Pt_n_xbins = 10;
    float Pt_xbins[Pt_n_xbins+1] = {0, 10, 20, 30, 40, 50, 75, 100, 150, 250, 500};
    const int AbsEta_n_bins = 2;
    float AbsEta_bins[AbsEta_n_bins+1] = {0, 1.5, 2.4};
    TH2F* temp = new TH2F(name, name, Pt_n_xbins, Pt_xbins, AbsEta_n_bins, AbsEta_bins);

    h_MistagRate_pteta_sys.push_back( temp );
  }
  return;
}


