#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

using namespace std;

// (local) variables associated with tree branches
Int_t            nAODMu_                              ; 
vector<float>    AOD_muPt_                            ; 
vector<float>    AOD_muEn_                            ; 
vector<float>    AOD_muEta_                           ; 
vector<float>    AOD_muPhi_                           ; 
vector<int>      AOD_muCharge_                        ; 
vector<int>      AOD_muType_                          ; 
vector<bool>     AOD_muIsGlobalMuon_                  ; 
vector<bool>     AOD_muIsPFMuon_                      ; 
vector<bool>     AOD_muPassLooseID_                   ;
vector<bool>     AOD_muPassMediumBCDEFID_             ;
vector<bool>     AOD_muPassMediumGHID_                ;
vector<bool>     AOD_muPassTightID_                   ;
vector<float>    AOD_muPFdBetaIsolation_              ; 
vector<float>    AOD_muDxy_                           ;
vector<float>    AOD_muDxyErr_                        ;
vector<float>    AOD_muDB_BS2D_                       ;
vector<float>    AOD_muDB_PV2D_                       ;

//https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Short_Term_Instructions_for_Mori
bool lldjNtuple::isMediumMuonBCDEF(const reco::Muon & recoMu) 
{
  bool goodGlob = recoMu.isGlobalMuon() && 
    recoMu.globalTrack()->normalizedChi2() < 3 && 
    recoMu.combinedQuality().chi2LocalPosition < 12 && 
    recoMu.combinedQuality().trkKink < 20; 
  bool isMedium = muon::isLooseMuon(recoMu) && 
    recoMu.innerTrack()->validFraction() > 0.49 && 
    muon::segmentCompatibility(recoMu) > (goodGlob ? 0.303 : 0.451); 
  return isMedium; 
}


//https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Short_Term_Instructions_for_Mori
bool lldjNtuple::isMediumMuonGH(const reco::Muon & recoMu) 
{
  bool goodGlob = recoMu.isGlobalMuon() && 
    recoMu.globalTrack()->normalizedChi2() < 3 && 
    recoMu.combinedQuality().chi2LocalPosition < 12 && 
    recoMu.combinedQuality().trkKink < 20; 
  bool isMedium = muon::isLooseMuon(recoMu) && 
    recoMu.innerTrack()->validFraction() > 0.8 && 
    muon::segmentCompatibility(recoMu) > (goodGlob ? 0.303 : 0.451); 
  return isMedium; 
}


void lldjNtuple::branchesAODMuons(TTree* tree) {
 tree->Branch("nAODMu",                             &nAODMu_                             ) ; 
 tree->Branch("AOD_muPt",                           &AOD_muPt_                           ) ; 
 tree->Branch("AOD_muEn",                           &AOD_muEn_                           ) ; 
 tree->Branch("AOD_muEta",                          &AOD_muEta_                          ) ; 
 tree->Branch("AOD_muPhi",                          &AOD_muPhi_                          ) ; 
 tree->Branch("AOD_muCharge",                       &AOD_muCharge_                       ) ; 
 tree->Branch("AOD_muType",                         &AOD_muType_                         ) ; 
 tree->Branch("AOD_muIsGlobalMuon",                 &AOD_muIsGlobalMuon_                 ) ; 
 tree->Branch("AOD_muIsPFMuon",                     &AOD_muIsPFMuon_                     ) ; 
 tree->Branch("AOD_muPassLooseID",                  &AOD_muPassLooseID_                  ) ; 
 tree->Branch("AOD_muPassMediumBCDEFID",            &AOD_muPassMediumBCDEFID_            ) ; 
 tree->Branch("AOD_muPassMediumGHID",               &AOD_muPassMediumGHID_               ) ; 
 tree->Branch("AOD_muPassTightID",                  &AOD_muPassTightID_                  ) ; 
 tree->Branch("AOD_muPFdBetaIsolation",             &AOD_muPFdBetaIsolation_             ) ; 
 tree->Branch("AOD_muDxy",                          &AOD_muDxy_                          ) ; 
 tree->Branch("AOD_muDxyErr",                       &AOD_muDxyErr_                       ) ; 
 tree->Branch("AOD_muDB_BS2D",                      &AOD_muDB_BS2D_                       ) ; 
 tree->Branch("AOD_muDB_PV2D",                      &AOD_muDB_PV2D_                       ) ; 
}


void lldjNtuple::fillAODMuons(const edm::Event& e, reco::Vertex vtx) {

 // cleanup from previous execution
 nAODMu_ = 0;
 AOD_muPt_                          .clear() ; 
 AOD_muEn_                          .clear() ; 
 AOD_muEta_                         .clear() ; 
 AOD_muPhi_                         .clear() ; 
 AOD_muCharge_                      .clear() ; 
 AOD_muType_                        .clear() ; 
 AOD_muIsGlobalMuon_                .clear() ; 
 AOD_muIsPFMuon_                    .clear() ; 
 AOD_muPassLooseID_                 .clear() ;
 AOD_muPassMediumBCDEFID_           .clear() ;
 AOD_muPassMediumGHID_              .clear() ;
 AOD_muPassTightID_                 .clear() ;
 AOD_muPFdBetaIsolation_            .clear() ; 
 AOD_muDxy_                         .clear() ; 
 AOD_muDxyErr_                      .clear() ; 
 AOD_muDB_BS2D_                     .clear() ; 
 AOD_muDB_PV2D_                     .clear() ; 

 edm::Handle<edm::View<pat::Muon> > muonHandle;
 e.getByToken(muonAODCollection_, muonHandle);
 
 if (!muonHandle.isValid()) {
   edm::LogWarning("lldjNtuple") << " missing AOD muon collection";
  return;
 }

 //Beamspot for impact parameter
 edm::Handle<reco::BeamSpot> beamspotHandle_;
 e.getByToken(beamspotLabel_, beamspotHandle_);

 for (edm::View<pat::Muon>::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu) {

  Float_t pt = iMu->pt();
  Float_t eta = iMu->eta();

  if (pt < 2) continue;
  if (fabs(eta) > 2.4) continue;
  if (! (iMu->isPFMuon() || iMu->isGlobalMuon() || iMu->isTrackerMuon())) continue;

  nAODMu_++;

  const reco::Muon &recoMu = dynamic_cast<const reco::Muon &>(*iMu);

  //Basic info
  AOD_muPt_           .push_back(pt);
  AOD_muEn_           .push_back(iMu->energy());
  AOD_muEta_          .push_back(iMu->eta());
  AOD_muPhi_          .push_back(iMu->phi());
  AOD_muCharge_       .push_back(iMu->charge());
  AOD_muType_         .push_back(iMu->type());
  AOD_muIsGlobalMuon_ .push_back(iMu->isGlobalMuon () ) ; 
  AOD_muIsPFMuon_     .push_back(iMu->isPFMuon     () ) ; 

  //ID
  AOD_muPassLooseID_       .push_back( iMu->isLooseMuon() );
  AOD_muPassMediumBCDEFID_ .push_back( isMediumMuonBCDEF(recoMu) );
  AOD_muPassMediumGHID_    .push_back( isMediumMuonGH(recoMu) );
  AOD_muPassTightID_       .push_back( iMu->isTightMuon(vtx) );

  //Isolation
  Float_t muPFChIso      = iMu->pfIsolationR04().sumChargedHadronPt ;
  Float_t muPFPhoIso     = iMu->pfIsolationR04().sumPhotonEt        ;
  Float_t muPFNeuIso     = iMu->pfIsolationR04().sumNeutralHadronEt ;
  Float_t muPFPUIso      = iMu->pfIsolationR04().sumPUPt            ;
  Float_t pfdBetaIso     = ( muPFChIso + max(0.0,muPFNeuIso + muPFPhoIso - 0.5*muPFPUIso ) ) / pt ;
  AOD_muPFdBetaIsolation_.push_back( pfdBetaIso     ) ;   

  //Impact parameter
  AOD_muDB_BS2D_.push_back (iMu->dB(pat::Muon::BS2D));
  AOD_muDB_PV2D_.push_back (iMu->dB(pat::Muon::PV2D));
  if(iMu->innerTrack().isNonnull()){
    float dxy = fabs(iMu->innerTrack()->dxy(*beamspotHandle_));
    float dxyErr = fabs(iMu->innerTrack()->dxyError());
    AOD_muDxy_.push_back( dxy );
    AOD_muDxyErr_.push_back( dxyErr );
  }
  else{
   AOD_muDxy_.push_back( -1 ) ;
   AOD_muDxyErr_.push_back( -1 ) ;
  }
 }//End muon collection loop

}//End fillAODMuons
