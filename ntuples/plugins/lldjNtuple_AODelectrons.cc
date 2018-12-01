#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "EgammaAnalysis/ElectronTools/interface/EnergyScaleCorrection_class.h"

#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"


using namespace std;
//using namespace reco;


// (local) variables associated with tree branches
Int_t            nAODEle_;
vector<float>    AOD_elePt_;
vector<float>    AOD_eleEn_;
vector<float>    AOD_eleEta_;
vector<float>    AOD_elePhi_;

vector<float>    AOD_eled0_;
vector<float>    AOD_eledz_;

vector<int>      AOD_eleCharge_;
vector<int>      AOD_eleChargeConsistent_;

vector<UShort_t> AOD_eleIDbit_;
vector<int>      AOD_elePassConversionVeto_;

//vector<float>    AOD_eleSCEn_;
//vector<float>    AOD_eleSCEta_;
//vector<float>    AOD_eleSCPhi_;
//vector<float>    AOD_elePFdBetaIsolationRhoEA_ ;
//vector<float>    AOD_elePFdBetaIsolationCHS_   ;
//vector<float>    AOD_elePFdBetaIsolationDiff_  ;

//float AOD_rho;


void lldjNtuple::branchesAODElectrons(TTree* tree) {

 tree->Branch("nAODEle",                     &nAODEle_                     );                           
 tree->Branch("AOD_elePt",                    &AOD_elePt_                    );     
 tree->Branch("AOD_eleEn",                    &AOD_eleEn_                    );     
 tree->Branch("AOD_eleEta",                   &AOD_eleEta_                   );     
 tree->Branch("AOD_elePhi",                   &AOD_elePhi_                   );     

 tree->Branch("AOD_eled0",                   &AOD_eled0_                   );     
 tree->Branch("AOD_eledz",                   &AOD_eledz_                   );     

 tree->Branch("AOD_eleCharge",                &AOD_eleCharge_                );     
 tree->Branch("AOD_eleChargeConsistent",      &AOD_eleChargeConsistent_      );     

 tree->Branch("AOD_eleIDbit",                 &AOD_eleIDbit_                 );     
 tree->Branch("AOD_elePassConversionVeto",    &AOD_elePassConversionVeto_        );

 // tree->Branch("AOD_eleSCEn",                  &AOD_eleSCEn_                  );     
 // tree->Branch("AOD_eleSCEta",                 &AOD_eleSCEta_                 );     
 // tree->Branch("AOD_eleSCPhi",                 &AOD_eleSCPhi_                 );     
 // tree->Branch("AOD_elePFdBetaIsolationRhoEA", &AOD_elePFdBetaIsolationRhoEA_ );     
 // tree->Branch("AOD_elePFdBetaIsolationCHS",   &AOD_elePFdBetaIsolationCHS_   );     
 // tree->Branch("AOD_elePFdBetaIsolationDiff",  &AOD_elePFdBetaIsolationDiff_  );     

}

void lldjNtuple::fillAODElectrons(const edm::Event &e, const edm::EventSetup &es, reco::Vertex vtx) {
    
 // cleanup from previous execution
 nAODEle_                     = 0;

 AOD_elePt_                    .clear();     
 AOD_eleEn_                    .clear();     
 AOD_eleEta_                   .clear();     
 AOD_elePhi_                   .clear();     

 AOD_eled0_                   .clear();     
 AOD_eledz_                   .clear();     

 AOD_eleCharge_                .clear();     
 AOD_eleChargeConsistent_      .clear();     

 AOD_eleIDbit_                 .clear();     
 AOD_elePassConversionVeto_    .clear();

 //AOD_eleSCEn_                  .clear();     
 //AOD_eleSCEta_                 .clear();     
 //AOD_eleSCPhi_                 .clear();     
 //AOD_elePFdBetaIsolationRhoEA_ .clear();     
 //AOD_elePFdBetaIsolationCHS_   .clear();     
 //AOD_elePFdBetaIsolationDiff_  .clear();     


 //https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
 //https://github.com/ikrav/EgammaWork/blob/ntupler_and_VID_demos_8.0.3/ElectronNtupler/plugins/ElectronNtuplerVIDDemo.cc
 //https://github.com/ikrav/EgammaWork/blob/ntupler_and_VID_demos_8.0.3/ElectronNtupler/test/runElectrons_VID_CutBased_Summer16_HLTSafe_demo.py
 
 edm::Handle<edm::View<reco::GsfElectron> > electrons;
 e.getByToken(electronAODToken_, electrons);
 if( !electrons.isValid() ){
   std::cout << "Invalid electron handle" << std::endl;
   edm::LogWarning("lldjNtuple") << "no pat::Electrons in event";
   return;
 }

 //Skip PV for now (for dz)

 // Get the conversions collection
 edm::Handle<reco::ConversionCollection> conversions;
 e.getByToken(conversionsAODToken_, conversions);

 // Beamspot needed for conversion veto
 edm::Handle<reco::BeamSpot> theBeamSpot;
 e.getByToken(beamspotLabel_, theBeamSpot);

 //ID
 edm::Handle<edm::ValueMap<bool> > ele_id_decisions_loose;
 e.getByToken(AOD_eleLooseIdMapToken_ ,ele_id_decisions_loose);
 edm::Handle<edm::ValueMap<bool> > ele_id_decisions_medium;
 e.getByToken(AOD_eleMediumIdMapToken_ ,ele_id_decisions_medium);
 edm::Handle<edm::ValueMap<bool> > ele_id_decisions_tight;
 e.getByToken(AOD_eleTightIdMapToken_ ,ele_id_decisions_tight);
 
 for (size_t i = 0; i < electrons->size(); ++i){
   const auto el = electrons->ptrAt(i);

   if( el->pt() < 5 ) continue;
   if( fabs(el->eta()) > 2.5 ) continue;
   
   AOD_eleEn_  .push_back( el->energy() );
   AOD_elePt_  .push_back( el->pt() );
   AOD_eleEta_ .push_back( el->superCluster()->eta() );
   AOD_elePhi_ .push_back( el->superCluster()->phi() );

   reco::GsfTrackRef theTrack = el->gsfTrack();
   //AOD_eled0_.push_back( theTrack->d0() );
   AOD_eled0_.push_back( (-1) * theTrack->dxy( vtx.position() ) );
   AOD_eledz_.push_back( theTrack->dz( vtx.position() ) );

   //std::cout << "d0 " << theTrack->d0() << ", " << dz << std::endl; 

   AOD_eleCharge_          .push_back(el->charge());
   AOD_eleChargeConsistent_.push_back((Int_t)el->isGsfCtfScPixChargeConsistent());
   
   // Conversion rejection
   bool passConvVeto = !ConversionTools::hasMatchedConversion(*el, 
   							      conversions,
   							      theBeamSpot->position());
   AOD_elePassConversionVeto_.push_back( (int) passConvVeto );
   
   UShort_t tmpeleIDbit = 0;
   bool isPassEleLooseId  = (*ele_id_decisions_loose)[el];
   if(isPassEleLooseId) setbit(tmpeleIDbit, 0);
   bool isPassEleMediumId  = (*ele_id_decisions_medium)[el];
   if(isPassEleMediumId) setbit(tmpeleIDbit, 1);
   bool isPassEleTightId  = (*ele_id_decisions_tight)[el];
   if(isPassEleTightId) setbit(tmpeleIDbit, 2);
   AOD_eleIDbit_.push_back(tmpeleIDbit);

   
   nAODEle_++;
 }   
}
