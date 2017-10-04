#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/RandGauss.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
//#include "DataFormats/TrackReco/interface/TrackBase.h"
//#include "DataFormats/VertexReco/interface/Vertex.h"
//#include "TrackingTools/Records/interface/TransientTrackRecord.h"
//#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
//#include <CandidateBoostedDoubleSecondaryVertexComputer.h>
#include "RecoTracker/DebugTools/interface/GetTrackTrajInfo.h"
//#include <GetTrackTrajInfo.h>

#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/GeomPropagators/interface/StateOnTrackerBound.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"

#include "PhysicsTools/RecoUtils/interface/CheckHitPattern.h"
#include "RecoVertex/ConfigurableVertexReco/interface/ConfigurableVertexReconstructor.h"
#include "RecoVertex/VertexTools/interface/VertexCompatibleWithBeam.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"

//new
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicParticle.h"
#include "RecoVertex/VertexPrimitives/interface/ConvertToFromReco.h"
#include "RecoVertex/VertexPrimitives/interface/ConvertError.h"



using namespace std;
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

// ak4 jets
Int_t          nJet_;
vector<float>  jetPt_;
vector<float>  jetEn_;
vector<float>  jetEta_;
vector<float>  jetPhi_;
vector<float>  jetRawPt_;
vector<float>  jetRawEn_;
vector<float>  jetMt_;
vector<float>  jetArea_;
vector<float>  jetLeadTrackPt_;
vector<float>  jetLeadTrackEta_;
vector<float>  jetLeadTrackPhi_;
vector<int>    jetLepTrackPID_;
vector<float>  jetLepTrackPt_;
vector<float>  jetLepTrackEta_;
vector<float>  jetLepTrackPhi_;
vector<float>  jetCHF_;
vector<float>  jetNHF_;
vector<float>  jetCEF_;
vector<float>  jetNEF_;
vector<int>    jetNCH_;
vector<int>    jetNNP_;
vector<float>  jetMUF_;
vector<float>  jetHFHAE_;
vector<float>  jetHFEME_;
vector<int>    jetNConstituents_;
vector<float>  jetVtxPt_;
vector<float>  jetVtxMass_;
vector<float>  jetVtxNtrks_;
vector<float>  jetVtx3DVal_;
vector<float>  jetVtx3DSig_;
vector<float>  jetCSV2BJetTags_; // recommended
vector<float>  jetJetProbabilityBJetTags_;
vector<float>  jetpfCombinedMVAV2BJetTags_;
vector<int>    jetPartonID_;
vector<int>    jetHadFlvr_;
vector<bool>   jetPFLooseId_;
vector<int>    jetID_; 
vector<float>  jetPUID_;
vector<int>    jetPUFullID_;
vector<float>  jetJECUnc_;
vector<float>  jetP4Smear_;
vector<float>  jetP4SmearUp_;
vector<float>  jetP4SmearDo_;
vector<UInt_t> jetFiredTrgs_;

// Displaced Jet Variables
vector<float>  jetAlphaD_;
vector<float>  jetAlphaMaxD_;
vector<float>  jetSumIP_;
vector<float>  jetSumIPSig_;
vector<float>  jetLog10IPSig_;
vector<float>  jetMedianLog10IPSig_;
vector<float>  jetTrackAngle_;
vector<float>  jetLogTrackAngle_;
vector<float>  jetMedianLogTrackAngle_;
vector<float>  jetTotalTrackAngle_;
vector<float>  jetAlphaMax_;
vector<float>  jetAlphaMax2_;
vector<float>  jetAlphaMaxP_;
vector<float>  jetAlphaMaxP2_;
vector<float>  jetDauVertex_x_;
vector<float>  jetDauVertex_y_;
vector<float>  jetDauVertex_z_;
vector<float>  jetDauVertex_r_;
vector<float>  alphaMax_jetDauVertex_r_;

// Alpha Maxs
vector<float>  jetAlphaMax_PV3onPV2_ ; 
vector<float>  jetAlphaMax_PV3onNeu_ ; 
vector<float>  jetAlphaMax_PV3onAll_ ; 
vector<float>  jetAlphaMax_PV2onNeu_ ; 
vector<float>  jetAlphaMax_PV2onAll_ ; 

vector<float>  jetAlpha2Max_PV3onPV2_ ; 
vector<float>  jetAlpha2Max_PV3onNeu_ ; 
vector<float>  jetAlpha2Max_PV3onAll_ ; 
vector<float>  jetAlpha2Max_PV2onNeu_ ; 
vector<float>  jetAlpha2Max_PV2onAll_ ; 

// Track Info
vector<vector<float>> jetTrackPt_;
vector<vector<float>> jetTrackEta_;
vector<vector<float>> jetTrackPhi_;
vector<vector<int>>   jetTrackPDGID_;
vector<vector<int>>   jetTrackMomPDGID_;

//gen-info for ak4
vector<float>  jetGenJetEn_;
vector<float>  jetGenJetPt_;
vector<float>  jetGenJetEta_;
vector<float>  jetGenJetPhi_;
vector<int>    jetGenPartonID_;
vector<float>  jetGenEn_;
vector<float>  jetGenPt_;
vector<float>  jetGenEta_;
vector<float>  jetGenPhi_;
vector<int>    jetGenPartonMomID_;

// AOD variables
// Calo Jets
Int_t          AODnCaloJet_;
vector<float>  AODCaloJetPt_;
vector<float>  AODCaloJetEta_;
vector<float>  AODCaloJetPhi_;

vector<float>  AODCaloJetAlphaMax_;
vector<float>  AODCaloJetAlphaMax2_;
vector<float>  AODCaloJetAlphaMaxPrime_;
vector<float>  AODCaloJetAlphaMaxPrime2_;
vector<float>  AODCaloJetBeta_;
vector<float>  AODCaloJetBeta2_;

vector<float>  AODCaloJetSumIP_;
vector<float>  AODCaloJetSumIPSig_;
vector<float>  AODCaloJetLog10IPSig_;
vector<float>  AODCaloJetMedianLog10IPSig_;
vector<float>  AODCaloJetTrackAngle_;
vector<float>  AODCaloJetLogTrackAngle_;
vector<float>  AODCaloJetMedianLogTrackAngle_;
vector<float>  AODCaloJetTotalTrackAngle_;

vector<float>  AODCaloJetAvfVx_;
vector<float>  AODCaloJetAvfVy_;
vector<float>  AODCaloJetAvfVz_;
vector<float>  AODCaloJetAvfVertexTotalChiSquared_;
vector<float>  AODCaloJetAvfVertexDegreesOfFreedom_;
vector<float>  AODCaloJetAvfVertexChi2NDoF_;
vector<float>  AODCaloJetAvfVertexDistanceToBeam_;
vector<float>  AODCaloJetAvfVertexTransverseError_;
vector<float>  AODCaloJetAvfVertexTransverseSig_;
vector<float>  AODCaloJetAvfVertexDeltaEta_;
vector<float>  AODCaloJetAvfVertexDeltaPhi_;
vector<float>  AODCaloJetAvfVertexRecoilPt_;
vector<float>  AODCaloJetAvfVertexTrackMass_;
vector<float>  AODCaloJetAvfVertexTrackEnergy_;
vector<float>  AODCaloJetAvfBeamSpotDeltaPhi_;
vector<float>  AODCaloJetAvfBeamSpotRecoilPt_;
vector<float>  AODCaloJetAvfBeamSpotMedianDeltaPhi_;
vector<float>  AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_;
vector<int>    AODCaloJetNCleanMatchedTracks_;
vector<int>    AODCaloJetSumHitsInFrontOfVert_;
vector<int>    AODCaloJetSumMissHitsAfterVert_;
vector<int>    AODCaloJetHitsInFrontOfVertPerTrack_;
vector<int>    AODCaloJetMissHitsAfterVertPerTrack_;
vector<float>  AODCaloJetAvfDistToPV_;
vector<float>  AODCaloJetAvfVertexDeltaZtoPV_;
vector<float>  AODCaloJetAvfVertexDeltaZtoPV2_;

// PF Jets
Int_t          AODnPFJet_;
vector<float>  AODPFJetPt_;
vector<float>  AODPFJetEta_;
vector<float>  AODPFJetPhi_;
vector<float>  AODPFJetAlphaMax_;
vector<float>  AODPFJetAlphaMax2_;
vector<float>  AODPFJetAlphaMaxPrime_;
vector<float>  AODPFJetAlphaMaxPrime2_;
vector<float>  AODPFJetBeta_;
vector<float>  AODPFJetBeta2_;
vector<float>  AODPFJetSumIP_;
vector<float>  AODPFJetSumIPSig_;
vector<float>  AODPFJetMedianLog10IPSig_;
vector<float>  AODPFJetTrackAngle_;
vector<float>  AODPFJetLogTrackAngle_;
vector<float>  AODPFJetMedianLogTrackAngle_;
vector<float>  AODPFJetTotalTrackAngle_;

// PFchs Jets
Int_t          AODnPFchsJet_;
vector<float>  AODPFchsJetPt_;
vector<float>  AODPFchsJetEta_;
vector<float>  AODPFchsJetPhi_;
vector<float>  AODPFchsJetAlphaMax_;
vector<float>  AODPFchsJetAlphaMax2_;
vector<float>  AODPFchsJetAlphaMaxPrime_;
vector<float>  AODPFchsJetAlphaMaxPrime2_;
vector<float>  AODPFchsJetBeta_;
vector<float>  AODPFchsJetBeta2_;
vector<float>  AODPFchsJetSumIP_;
vector<float>  AODPFchsJetSumIPSig_;
vector<float>  AODPFchsJetMedianLog10IPSig_;
vector<float>  AODPFchsJetTrackAngle_;
vector<float>  AODPFchsJetLogTrackAngle_;
vector<float>  AODPFchsJetMedianLogTrackAngle_;
vector<float>  AODPFchsJetTotalTrackAngle_;

edm::Handle<edm::View<reco::CaloJet> >  AODak4CaloJetsHandle;   
edm::Handle<edm::View<reco::PFJet>   >  AODak4PFJetsHandle;     
edm::Handle<edm::View<reco::PFJet>   >  AODak4PFJetsCHSHandle;  
edm::Handle<edm::View<reco::Vertex>  >  AODVertexHandle;
edm::Handle<edm::View<reco::Track>   >  AODTrackHandle;
edm::Handle<reco::BeamSpot> beamspotHandle_;

void lldjNtuple::branchesJets(TTree* tree) {

  //link the variable in c++ code to variable in branch
  tree->Branch("nJet",                       &nJet_);                       
  tree->Branch("jetPt",                      &jetPt_);                      
  tree->Branch("jetEn",                      &jetEn_);                      
  tree->Branch("jetEta",                     &jetEta_);                     
  tree->Branch("jetPhi",                     &jetPhi_);                     
  tree->Branch("jetRawPt",                   &jetRawPt_);                   
  tree->Branch("jetRawEn",                   &jetRawEn_);                   
  tree->Branch("jetMt",                      &jetMt_);                      
  tree->Branch("jetArea",                    &jetArea_);                    
  tree->Branch("jetLeadTrackPt",             &jetLeadTrackPt_);             
  tree->Branch("jetLeadTrackEta",            &jetLeadTrackEta_);            
  tree->Branch("jetLeadTrackPhi",            &jetLeadTrackPhi_);            
  tree->Branch("jetLepTrackPID",             &jetLepTrackPID_);             
  tree->Branch("jetLepTrackPt",              &jetLepTrackPt_);              
  tree->Branch("jetLepTrackEta",             &jetLepTrackEta_);             
  tree->Branch("jetLepTrackPhi",             &jetLepTrackPhi_);             
  tree->Branch("jetCHF",                     &jetCHF_);                     
  tree->Branch("jetNHF",                     &jetNHF_);                     
  tree->Branch("jetCEF",                     &jetCEF_);                     
  tree->Branch("jetNEF",                     &jetNEF_);                     
  tree->Branch("jetNCH",                     &jetNCH_);                     
  tree->Branch("jetNNP",                     &jetNNP_);                     
  tree->Branch("jetMUF",                     &jetMUF_);                     
  tree->Branch("jetHFHAE",                   &jetHFHAE_);                   
  tree->Branch("jetHFEME",                   &jetHFEME_);                   
  tree->Branch("jetNConstituents",           &jetNConstituents_);           
  tree->Branch("jetVtxPt",                   &jetVtxPt_);                   
  tree->Branch("jetVtxMass",                 &jetVtxMass_);                 
  tree->Branch("jetVtxNtrks",                &jetVtxNtrks_);                
  tree->Branch("jetVtx3DVal",                &jetVtx3DVal_);                
  tree->Branch("jetVtx3DSig",                &jetVtx3DSig_);                
  tree->Branch("jetCSV2BJetTags",            &jetCSV2BJetTags_);            
  tree->Branch("jetJetProbabilityBJetTags",  &jetJetProbabilityBJetTags_);  
  tree->Branch("jetpfCombinedMVAV2BJetTags", &jetpfCombinedMVAV2BJetTags_); 
  tree->Branch("jetPartonID",                &jetPartonID_);                
  tree->Branch("jetHadFlvr",                 &jetHadFlvr_);                 
  tree->Branch("jetPFLooseId",               &jetPFLooseId_);               
  tree->Branch("jetID",                      &jetID_);                      
  tree->Branch("jetPUID",                    &jetPUID_);                    
  tree->Branch("jetPUFullID",                &jetPUFullID_);                
  tree->Branch("jetJECUnc",                  &jetJECUnc_);                  
  tree->Branch("jetP4Smear",                 &jetP4Smear_);                 
  tree->Branch("jetP4SmearUp",               &jetP4SmearUp_);               
  tree->Branch("jetP4SmearDo",               &jetP4SmearDo_);               
  tree->Branch("jetFiredTrgs",               &jetFiredTrgs_);               
 
  tree->Branch("jetAlphaD",                  &jetAlphaD_);                  
  tree->Branch("jetAlphaMaxD",               &jetAlphaMaxD_);               
  tree->Branch("jetSumIP",                   &jetSumIP_);                   
  tree->Branch("jetSumIPSig",                &jetSumIPSig_);                
  tree->Branch("jetLog10IPSig",              &jetLog10IPSig_);              
  tree->Branch("jetMedianLog10IPSig",        &jetMedianLog10IPSig_);        
  tree->Branch("jetTrackAngle",              &jetTrackAngle_);              
  tree->Branch("jetLogTrackAngle",           &jetLogTrackAngle_);           
  tree->Branch("jetMedianLogTrackAngle",     &jetMedianLogTrackAngle_);     
  tree->Branch("jetTotalTrackAngle",         &jetTotalTrackAngle_);         
  tree->Branch("jetAlphaMax",                &jetAlphaMax_);                
  tree->Branch("jetAlphaMax2",               &jetAlphaMax2_);               
  tree->Branch("jetAlphaMaxP",               &jetAlphaMaxP_);               
  tree->Branch("jetAlphaMaxP2",              &jetAlphaMaxP2_);              
  tree->Branch("jetDauVertex_x",             &jetDauVertex_x_);             
  tree->Branch("jetDauVertex_y",             &jetDauVertex_y_);             
  tree->Branch("jetDauVertex_z",             &jetDauVertex_z_);             
  tree->Branch("jetDauVertex_r",             &jetDauVertex_r_);             
  tree->Branch("alphaMax_jetDauVertex_r",    &alphaMax_jetDauVertex_r_);    
 
  tree->Branch("jetAlphaMax_PV3onPV2",       &jetAlphaMax_PV3onPV2_);       
  tree->Branch("jetAlphaMax_PV3onNeu",       &jetAlphaMax_PV3onNeu_);       
  tree->Branch("jetAlphaMax_PV3onAll",       &jetAlphaMax_PV3onAll_);       
  tree->Branch("jetAlphaMax_PV2onNeu",       &jetAlphaMax_PV2onNeu_);       
  tree->Branch("jetAlphaMax_PV2onAll",       &jetAlphaMax_PV2onAll_);       
 
  tree->Branch("jetAlpha2Max_PV3onPV2",      &jetAlpha2Max_PV3onPV2_);      
  tree->Branch("jetAlpha2Max_PV3onNeu",      &jetAlpha2Max_PV3onNeu_);      
  tree->Branch("jetAlpha2Max_PV3onAll",      &jetAlpha2Max_PV3onAll_);      
  tree->Branch("jetAlpha2Max_PV2onNeu",      &jetAlpha2Max_PV2onNeu_);      
  tree->Branch("jetAlpha2Max_PV2onAll",      &jetAlpha2Max_PV2onAll_);      
 
  tree->Branch("jetTrackPt",                 &jetTrackPt_);                 
  tree->Branch("jetTrackEta",                &jetTrackEta_);                
  tree->Branch("jetTrackPhi",                &jetTrackPhi_);                
  tree->Branch("jetTrackPDGID",              &jetTrackPDGID_);              
  tree->Branch("jetTrackMomPDGID",           &jetTrackMomPDGID_);           
 
  tree->Branch("jetGenJetEn",                &jetGenJetEn_);                
  tree->Branch("jetGenJetPt",                &jetGenJetPt_);                
  tree->Branch("jetGenJetEta",               &jetGenJetEta_);               
  tree->Branch("jetGenJetPhi",               &jetGenJetPhi_);               
  tree->Branch("jetGenPartonID",             &jetGenPartonID_);             
  tree->Branch("jetGenEn",                   &jetGenEn_);                   
  tree->Branch("jetGenPt",                   &jetGenPt_);                   
  tree->Branch("jetGenEta",                  &jetGenEta_);                  
  tree->Branch("jetGenPhi",                  &jetGenPhi_);                  
  tree->Branch("jetGenPartonMomID",          &jetGenPartonMomID_);          


  tree->Branch("AODnCaloJet"                   , &AODnCaloJet_);
  tree->Branch("AODCaloJetPt"                  , &AODCaloJetPt_);
  tree->Branch("AODCaloJetEta"                 , &AODCaloJetEta_);
  tree->Branch("AODCaloJetPhi"                 , &AODCaloJetPhi_);

  tree->Branch("AODCaloJetAlphaMax"            , &AODCaloJetAlphaMax_);                               
  tree->Branch("AODCaloJetAlphaMax2"           , &AODCaloJetAlphaMax2_);                               
  tree->Branch("AODCaloJetAlphaMaxPrime"       , &AODCaloJetAlphaMaxPrime_);                               
  tree->Branch("AODCaloJetAlphaMaxPrime2"      , &AODCaloJetAlphaMaxPrime2_);                               
  tree->Branch("AODCaloJetBeta"                , &AODCaloJetBeta_);                               
  tree->Branch("AODCaloJetBeta2"               , &AODCaloJetBeta2_);                               

  tree->Branch("AODCaloJetSumIP"               , &AODCaloJetSumIP_);
  tree->Branch("AODCaloJetSumIPSig"            , &AODCaloJetSumIPSig_);
  tree->Branch("AODCaloJetMedianLog10IPSig"    , &AODCaloJetMedianLog10IPSig_);
  tree->Branch("AODCaloJetTrackAngle"          , &AODCaloJetTrackAngle_);
  tree->Branch("AODCaloJetLogTrackAngle"       , &AODCaloJetLogTrackAngle_);
  tree->Branch("AODCaloJetMedianLogTrackAngle" , &AODCaloJetMedianLogTrackAngle_);
  tree->Branch("AODCaloJetTotalTrackAngle"     , &AODCaloJetTotalTrackAngle_);
                          
  tree->Branch("AODCaloJetAvfVx", &AODCaloJetAvfVx_);
  tree->Branch("AODCaloJetAvfVy", &AODCaloJetAvfVy_);
  tree->Branch("AODCaloJetAvfVz", &AODCaloJetAvfVz_);
  tree->Branch("AODCaloJetAvfVertexTotalChiSquared", &AODCaloJetAvfVertexTotalChiSquared_);
  tree->Branch("AODCaloJetAvfVertexDegreesOfFreedom", &AODCaloJetAvfVertexDegreesOfFreedom_);
  tree->Branch("AODCaloJetAvfVertexChi2NDoF", &AODCaloJetAvfVertexChi2NDoF_);
  tree->Branch("AODCaloJetAvfVertexDistanceToBeam", &AODCaloJetAvfVertexDistanceToBeam_);
  tree->Branch("AODCaloJetAvfVertexTransverseError", &AODCaloJetAvfVertexTransverseError_);
  tree->Branch("AODCaloJetAvfVertexTransverseSig", &AODCaloJetAvfVertexTransverseSig_);
  tree->Branch("AODCaloJetAvfVertexDeltaEta", &AODCaloJetAvfVertexDeltaEta_);
  tree->Branch("AODCaloJetAvfVertexDeltaPhi", &AODCaloJetAvfVertexDeltaPhi_);
  tree->Branch("AODCaloJetAvfVertexRecoilPt", &AODCaloJetAvfVertexRecoilPt_);
  tree->Branch("AODCaloJetAvfVertexTrackMass", &AODCaloJetAvfVertexTrackMass_);
  tree->Branch("AODCaloJetAvfVertexTrackEnergy", &AODCaloJetAvfVertexTrackEnergy_);
  tree->Branch("AODCaloJetAvfBeamSpotDeltaPhi", &AODCaloJetAvfBeamSpotDeltaPhi_);
  tree->Branch("AODCaloJetAvfBeamSpotRecoilPt", &AODCaloJetAvfBeamSpotRecoilPt_);
  tree->Branch("AODCaloJetAvfBeamSpotMedianDeltaPhi", &AODCaloJetAvfBeamSpotMedianDeltaPhi_);
  tree->Branch("AODCaloJetAvfBeamSpotLog10MedianDeltaPhi", &AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_);
  tree->Branch("AODCaloJetNCleanMatchedTracks", &AODCaloJetNCleanMatchedTracks_);
  tree->Branch("AODCaloJetSumHitsInFrontOfVert", &AODCaloJetSumHitsInFrontOfVert_);
  tree->Branch("AODCaloJetSumMissHitsAfterVert", &AODCaloJetSumMissHitsAfterVert_);
  tree->Branch("AODCaloJetHitsInFrontOfVertPerTrack", &AODCaloJetHitsInFrontOfVertPerTrack_);
  tree->Branch("AODCaloJetMissHitsAfterVertPerTrack", &AODCaloJetMissHitsAfterVertPerTrack_);
  tree->Branch("AODCaloJetAvfDistToPV", &AODCaloJetAvfDistToPV_);
  tree->Branch("AODCaloJetAvfVertexDeltaZtoPV", &AODCaloJetAvfVertexDeltaZtoPV_);
  tree->Branch("AODCaloJetAvfVertexDeltaZtoPV2", &AODCaloJetAvfVertexDeltaZtoPV2_);

                       
  tree->Branch("AODnPFJet"                     , &AODnPFJet_);
  tree->Branch("AODPFJetPt"                    , &AODPFJetPt_);
  tree->Branch("AODPFJetEta"                   , &AODPFJetEta_);
  tree->Branch("AODPFJetPhi"                   , &AODPFJetPhi_);
  tree->Branch("AODPFJetAlphaMax"              , &AODPFJetAlphaMax_);
  tree->Branch("AODPFJetAlphaMax2_"            , &AODPFJetAlphaMax2_);
  tree->Branch("AODPFJetAlphaMaxPrime_"        , &AODPFJetAlphaMaxPrime_);
  tree->Branch("AODPFJetAlphaMaxPrime2_"       , &AODPFJetAlphaMaxPrime2_);
  tree->Branch("AODPFJetBeta_"                 , &AODPFJetBeta_);
  tree->Branch("AODPFJetBeta2_"                , &AODPFJetBeta2_);
  tree->Branch("AODPFJetSumIP"                 , &AODPFJetSumIP_);
  tree->Branch("AODPFJetSumIPSig"              , &AODPFJetSumIPSig_);
  tree->Branch("AODPFJetMedianLog10IPSig"      , &AODPFJetMedianLog10IPSig_);
  tree->Branch("AODPFJetTrackAngle"            , &AODPFJetTrackAngle_);
  tree->Branch("AODPFJetLogTrackAngle"         , &AODPFJetLogTrackAngle_);
  tree->Branch("AODPFJetMedianLogTrackAngle"   , &AODPFJetMedianLogTrackAngle_);
  tree->Branch("AODPFJetTotalTrackAngle"       , &AODPFJetTotalTrackAngle_);
                                                
  tree->Branch("AODnPFchsJet"                  , &AODnPFchsJet_);
  tree->Branch("AODPFchsJetPt"                 , &AODPFchsJetPt_);
  tree->Branch("AODPFchsJetEta"                , &AODPFchsJetEta_);
  tree->Branch("AODPFchsJetPhi"                , &AODPFchsJetPhi_);
  tree->Branch("AODPFchsJetAlphaMax"           , &AODPFchsJetAlphaMax_);
  tree->Branch("AODPFchsJetAlphaMax2_"         , &AODPFchsJetAlphaMax2_);
  tree->Branch("AODPFchsJetAlphaMaxPrime_"     , &AODPFchsJetAlphaMaxPrime_);
  tree->Branch("AODPFchsJetAlphaMaxPrime2_"    , &AODPFchsJetAlphaMaxPrime2_);
  tree->Branch("AODPFchsJetBeta_"              , &AODPFchsJetBeta_);
  tree->Branch("AODPFchsJetBeta2_"             , &AODPFchsJetBeta2_);
  tree->Branch("AODPFchsJetSumIP"              , &AODPFchsJetSumIP_);
  tree->Branch("AODPFchsJetSumIPSig"           , &AODPFchsJetSumIPSig_);
  tree->Branch("AODPFchsJetMedianLog10IPSig"   , &AODPFchsJetMedianLog10IPSig_);
  tree->Branch("AODPFchsJetTrackAngle"         , &AODPFchsJetTrackAngle_);
  tree->Branch("AODPFchsJetLogTrackAngle"      , &AODPFchsJetLogTrackAngle_);
  tree->Branch("AODPFchsJetMedianLogTrackAngle", &AODPFchsJetMedianLogTrackAngle_);
  tree->Branch("AODPFchsJetTotalTrackAngle"    , &AODPFchsJetTotalTrackAngle_);
  
}

//fills jets .clear() to empty vector of old data
void lldjNtuple::fillJets(const edm::Event& e, const edm::EventSetup& es) {

 bool dodebug = false;
 // cleanup from previous execution
 nJet_=0;
 jetPt_.clear();
 jetEn_.clear();
 jetEta_.clear();
 jetPhi_.clear();
 jetRawPt_.clear();
 jetRawEn_.clear();
 jetMt_.clear();
 jetArea_.clear();
 jetLeadTrackPt_.clear();
 jetLeadTrackEta_.clear();
 jetLeadTrackPhi_.clear();
 jetLepTrackPID_.clear();
 jetLepTrackPt_.clear();
 jetLepTrackEta_.clear();
 jetLepTrackPhi_.clear();
 jetCHF_.clear();
 jetNHF_.clear();
 jetCEF_.clear();
 jetNEF_.clear();
 jetNCH_.clear();
 jetNNP_.clear();
 jetMUF_.clear();
 jetHFHAE_.clear();
 jetHFEME_.clear();
 jetNConstituents_.clear();
 jetVtxPt_.clear();
 jetVtxMass_.clear();
 jetVtxNtrks_.clear();
 jetVtx3DVal_.clear();
 jetVtx3DSig_.clear();
 jetCSV2BJetTags_.clear();
 jetJetProbabilityBJetTags_.clear();
 jetpfCombinedMVAV2BJetTags_.clear();
 jetPartonID_.clear();
 jetHadFlvr_.clear();
 jetPFLooseId_.clear();
 jetID_.clear(); 
 jetPUID_.clear();
 jetPUFullID_.clear();
 jetJECUnc_.clear();
 jetP4Smear_.clear();
 jetP4SmearUp_.clear();
 jetP4SmearDo_.clear();
 jetFiredTrgs_.clear();
 
 jetAlphaD_.clear();
 jetAlphaMaxD_.clear();
 jetSumIP_.clear();
 jetSumIPSig_.clear();
 jetLog10IPSig_.clear();
 jetMedianLog10IPSig_.clear();
 jetTrackAngle_.clear();
 jetLogTrackAngle_.clear();
 jetMedianLogTrackAngle_.clear();
 jetTotalTrackAngle_.clear();
 jetAlphaMax_.clear();
 jetAlphaMax2_.clear();
 jetAlphaMaxP_.clear();
 jetAlphaMaxP2_.clear();
 jetDauVertex_x_.clear();
 jetDauVertex_y_.clear();
 jetDauVertex_z_.clear();
 jetDauVertex_r_.clear();
 alphaMax_jetDauVertex_r_.clear();
 
 jetAlphaMax_PV3onPV2_.clear(); 
 jetAlphaMax_PV3onNeu_.clear(); 
 jetAlphaMax_PV3onAll_.clear(); 
 jetAlphaMax_PV2onNeu_.clear(); 
 jetAlphaMax_PV2onAll_.clear(); 
 
 jetAlpha2Max_PV3onPV2_.clear(); 
 jetAlpha2Max_PV3onNeu_.clear(); 
 jetAlpha2Max_PV3onAll_.clear(); 
 jetAlpha2Max_PV2onNeu_.clear(); 
 jetAlpha2Max_PV2onAll_.clear(); 
 
 jetTrackPt_.clear();
 jetTrackEta_.clear();
 jetTrackPhi_.clear();
 jetTrackPDGID_.clear();
 jetTrackMomPDGID_.clear();
 
 jetGenJetEn_.clear();
 jetGenJetPt_.clear();
 jetGenJetEta_.clear();
 jetGenJetPhi_.clear();
 jetGenPartonID_.clear();
 jetGenEn_.clear();
 jetGenPt_.clear();
 jetGenEta_.clear();
 jetGenPhi_.clear();
 jetGenPartonMomID_.clear();

 AODnCaloJet_=0;
 AODCaloJetPt_.clear();
 AODCaloJetEta_.clear();
 AODCaloJetPhi_.clear();

 AODCaloJetAlphaMax_.clear();                               
 AODCaloJetAlphaMax2_.clear();                               
 AODCaloJetAlphaMaxPrime_.clear();                               
 AODCaloJetAlphaMaxPrime2_.clear();                               
 AODCaloJetBeta_.clear();                               
 AODCaloJetBeta2_.clear();                               

 AODCaloJetSumIP_.clear();
 AODCaloJetSumIPSig_.clear();
 AODCaloJetMedianLog10IPSig_.clear();
 AODCaloJetTrackAngle_.clear();
 AODCaloJetLogTrackAngle_.clear();
 AODCaloJetMedianLogTrackAngle_.clear();
 AODCaloJetTotalTrackAngle_.clear();

 AODCaloJetAvfVx_.clear();
 AODCaloJetAvfVy_.clear();
 AODCaloJetAvfVz_.clear();
 AODCaloJetAvfVertexTotalChiSquared_.clear();
 AODCaloJetAvfVertexDegreesOfFreedom_.clear();
 AODCaloJetAvfVertexChi2NDoF_.clear();
 AODCaloJetAvfVertexDistanceToBeam_.clear();
 AODCaloJetAvfVertexTransverseError_.clear();
 AODCaloJetAvfVertexTransverseSig_.clear();
 AODCaloJetAvfVertexDeltaEta_.clear();
 AODCaloJetAvfVertexDeltaPhi_.clear();
 AODCaloJetAvfVertexRecoilPt_.clear();
 AODCaloJetAvfVertexTrackMass_.clear();
 AODCaloJetAvfVertexTrackEnergy_.clear();
 AODCaloJetAvfBeamSpotDeltaPhi_.clear();
 AODCaloJetAvfBeamSpotRecoilPt_.clear();
 AODCaloJetAvfBeamSpotMedianDeltaPhi_.clear();
 AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_.clear();
 AODCaloJetNCleanMatchedTracks_.clear();
 AODCaloJetSumHitsInFrontOfVert_.clear();
 AODCaloJetSumMissHitsAfterVert_.clear();
 AODCaloJetHitsInFrontOfVertPerTrack_.clear();
 AODCaloJetMissHitsAfterVertPerTrack_.clear();
 AODCaloJetAvfDistToPV_.clear();
 AODCaloJetAvfVertexDeltaZtoPV_.clear();
 AODCaloJetAvfVertexDeltaZtoPV2_.clear();

 AODnPFJet_=0;
 AODPFJetPt_.clear();
 AODPFJetEta_.clear();
 AODPFJetPhi_.clear();
 AODPFJetAlphaMax_.clear();
 AODPFJetAlphaMax2_.clear();
 AODPFJetAlphaMaxPrime_.clear();
 AODPFJetAlphaMaxPrime2_.clear();
 AODPFJetBeta_.clear();
 AODPFJetBeta2_.clear();
 AODPFJetSumIP_.clear();
 AODPFJetSumIPSig_.clear();
 AODPFJetMedianLog10IPSig_.clear();
 AODPFJetTrackAngle_.clear();
 AODPFJetLogTrackAngle_.clear();
 AODPFJetMedianLogTrackAngle_.clear();
 AODPFJetTotalTrackAngle_.clear();

 AODnPFchsJet_=0;
 AODPFchsJetPt_.clear();
 AODPFchsJetEta_.clear();
 AODPFchsJetPhi_.clear();
 AODPFchsJetAlphaMax_.clear();
 AODPFchsJetAlphaMax2_.clear();
 AODPFchsJetAlphaMaxPrime_.clear();
 AODPFchsJetAlphaMaxPrime2_.clear();
 AODPFchsJetBeta_.clear();
 AODPFchsJetBeta2_.clear();
 AODPFchsJetSumIP_.clear();
 AODPFchsJetSumIPSig_.clear();
 AODPFchsJetMedianLog10IPSig_.clear();
 AODPFchsJetTrackAngle_.clear();
 AODPFchsJetLogTrackAngle_.clear();
 AODPFchsJetMedianLogTrackAngle_.clear();
 AODPFchsJetTotalTrackAngle_.clear();


  edm::Handle<edm::View<pat::Jet> > jetHandle;
  e.getByToken(jetsAK4Label_, jetHandle);

  if (!jetHandle.isValid()) {
    edm::LogWarning("lldjNtuple") << "no pat::Jets (AK4) in event";
    return;
  }

  ConfigurableVertexReconstructor* vtxfitter_ = new ConfigurableVertexReconstructor(lldj_pset_.getParameter<edm::ParameterSet>("vertexFitterConfig"));
  VertexDistanceXY vertexDistanceXY_;
  VertexCompatibleWithBeam* vertexBeam_ = new VertexCompatibleWithBeam(vertexDistanceXY_,100);

  //edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
  //if(doGenParticles_)e.getByToken(genParticlesCollection_, genParticlesHandle);
  
  edm::Handle<double> rhoHandle;
  e.getByToken(rhoLabel_, rhoHandle);
  float rho = *(rhoHandle.product());
  
  edm::Handle<reco::VertexCollection> vtxHandle;
  e.getByToken(vtxLabel_, vtxHandle);
  if (!vtxHandle.isValid()) edm::LogWarning("lldjNtuple") << "Primary vertices info not unavailable";

  // Accessing the JEC uncertainties 
  //ak4  
  edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
  es.get<JetCorrectionsRecord>().get("AK4PFchs",JetCorParColl); 
  JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
  JetCorrectionUncertainty *jecUnc=0;
  jecUnc = new JetCorrectionUncertainty(JetCorPar);
  // //ak8
  // edm::ESHandle<JetCorrectorParametersCollection> AK8JetCorParColl;
  // es.get<JetCorrectionsRecord>().get("AK8PFchs",AK8JetCorParColl);
  // JetCorrectorParameters const & AK8JetCorPar = (*AK8JetCorParColl)["Uncertainty"];
  // JetCorrectionUncertainty *AK8jecUnc=0;
  // AK8jecUnc = new JetCorrectionUncertainty(AK8JetCorPar);
  
  //start jets Lvdp
  int nrjet = 0;
  int IP0Sum = 0;
  int TA0Sum = 0;

  if(dodebug){ printf("Starting loop over jets\n"); }
  unsigned int tmp_jetnr = 0; 

  // miniAOD Jets -------------------------------------------
  for (edm::View<pat::Jet>::const_iterator iJet = jetHandle->begin(); iJet != jetHandle->end(); ++iJet) {
    tmp_jetnr++;
    if(dodebug){ printf(" Jet Nr: %u \n",tmp_jetnr); }

    //get jet axis for track angle
    TVector3 JetAxis(iJet->px(),iJet->py(),iJet->pz());
 
    //declare new vars    
    float dxy;
    float dxyerr;
    float SumIP = 0.0;
    float SumIPSig = 0.0;
    float MedianLog10IPSig = 0.0;
    float TotalTrackAngle = 0.0;
    float MedianLogTrackAngle = 0.0;
   
    // start with ID so we skip early
    float NHF      = iJet->neutralHadronEnergyFraction();
    float NEMF     = iJet->neutralEmEnergyFraction();
    float NumConst = iJet->chargedMultiplicity()+iJet->neutralMultiplicity();
    float CHF      = iJet->chargedHadronEnergyFraction();
    float CHM      = iJet->chargedMultiplicity();
    float CEMF     = iJet->chargedEmEnergyFraction();
    float NNP      = iJet->neutralMultiplicity();

    bool looseJetID        = false;    
    bool tightJetID        = false;
    if (fabs(iJet->eta()) <= 2.7) {
      looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
      tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
    } else if (fabs(iJet->eta()) <= 3.0) {
      looseJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
      tightJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
    } else {
      looseJetID = (NEMF<0.90 && NNP>10); 
      tightJetID = (NEMF<0.90 && NNP>10);
    }
    Int_t jetIDdecision = 0;
    if (looseJetID) jetIDdecision += pow(2, 1);
    if (tightJetID) jetIDdecision += pow(2, 2);

    // place selection on jets making it into collection
    if (iJet->pt() < 20 || fabs(iJet->eta()) > 2.4 || jetIDdecision==0 ) continue; 

    nrjet++;

    jetID_.push_back(jetIDdecision);    

    // PUJet ID from slimmedJets
    jetPUID_.push_back(iJet->userFloat("pileupJetId:fullDiscriminant"));
    jetPUFullID_.push_back(iJet->userInt("pileupJetId:fullId"));

    
    if(dodebug){printf(" pt: %f\n",iJet->pt()); }
    jetPt_.push_back(    iJet->pt());
    //cout << endl<< iJet->pt()<<" *****jet constituents: "<<iJet->getJetConstituents().size() <<endl;
    //cout<<endl<<"JetPT: "<<iJet->pt() <<"Event "<<e.id().event()<<endl;
    jetEn_.push_back(    iJet->energy());
    jetEta_.push_back(   iJet->eta());
    jetPhi_.push_back(   iJet->phi());
    jetRawPt_.push_back( (*iJet).correctedJet("Uncorrected").pt());
    jetRawEn_.push_back( (*iJet).correctedJet("Uncorrected").energy());
    jetMt_.push_back(    iJet->mt());
    jetArea_.push_back(  iJet->jetArea());
    jetCEF_.push_back(   iJet->chargedEmEnergyFraction());
    jetNEF_.push_back(   iJet->neutralEmEnergyFraction());
    jetCHF_.push_back(   iJet->chargedHadronEnergyFraction());
    jetNHF_.push_back(   iJet->neutralHadronEnergyFraction());
    jetNCH_.push_back(   iJet->chargedMultiplicity());
    jetNNP_.push_back(   iJet->neutralMultiplicity());
    jetMUF_.push_back(   iJet->muonEnergyFraction());
    //jetNConstituents_.push_back(iJet->numberOfDaughters());
    jetNConstituents_.push_back(iJet->getJetConstituents().size());
    //if (development_) {
    //  jetHFHAE_.push_back( iJet->HFHadronEnergy());
    //  jetHFEME_.push_back( iJet->HFEMEnergy());
    //}

    if (fabs(iJet->eta()) < 5.2) {
      jecUnc->setJetEta(iJet->eta());
      jecUnc->setJetPt(iJet->pt()); // here you must use the CORRECTED jet pt
      jetJECUnc_.push_back(jecUnc->getUncertainty(true));
    } else {
      jetJECUnc_.push_back(-1.);
    }

    //jetFiredTrgs_.push_back(matchJetTriggerFilters(iJet->pt(), iJet->eta(), iJet->phi()));    

    //Searching for leading track and lepton
    float leadTrkPt  = -99;
    float leadTrkEta = -99;
    float leadTrkPhi = -99;
    int   lepTrkPID  = -99;
    float lepTrkPt   = -99;
    float lepTrkEta  = -99;
    float lepTrkPhi  = -99;

    vector<float> sumtracksfPV2(vtxHandle->size(),  0.);
    vector<float> sum2tracksfPV2(vtxHandle->size(), 0.);
    vector<float> sumtracksfPV3(vtxHandle->size(),  0.);
    vector<float> sum2tracksfPV3(vtxHandle->size(), 0.);
    vector<float> sumtracksMinDzVtx(vtxHandle->size() ,  0.);
    vector<float> sum2tracksMinDzVtx(vtxHandle->size() , 0.);
    float sumneutraltracks   = 0. ;
    float sum2neutraltracks  = 0. ;
    float sumalltracks       = 0. ;
    float sum2alltracks      = 0. ;

    //IP stuff
    bool IPtest = false;
    float dxySig = -1.;

    float daughterPt = -1.;
    float daughterEta = -99.;
    float daughterPhi = -99.;
    float promptTotal   = 0. ;
    float promptTotal2  = 0. ;
    int   daughterPDGID = 0;

    if(dodebug){ printf("  Looping over Tracks\n"); }
    unsigned int tmp_tracknr = 0; 

    vector<float> tmpTrackPt;
    vector<float> tmpTrackEta;
    vector<float> tmpTrackPhi;
    vector<int>   tmpTrackPDGID;
    vector<int>   tmpTrackMomPDGID;

    // looping over tracks
    for (unsigned id = 0; id < iJet->getJetConstituents().size(); id++) {

      // daughter of iJet is reco::Candidate
      const edm::Ptr<reco::Candidate> daughter = iJet->getJetConstituents().at(id);

      //cast daughter as (pat::PackedCandidate)daughter2 to access member functions
      const pat::PackedCandidate &daughter2 = dynamic_cast<const pat::PackedCandidate &>(*iJet->getJetConstituents().at(id));

      const reco::VertexRef vref = daughter2.vertexRef();

      if (daughter.isNonnull() && daughter.isAvailable()) 
      {
        tmp_tracknr++;
        if(dodebug){ printf("   Track Nr: %u \n",tmp_tracknr); }

        // set common variables
        daughterPt = daughter->pt(); 
        daughterEta = daughter->eta();
        daughterPhi = daughter->phi();
        daughterPDGID = daughter2.pdgId();
        if(dodebug){ printf("   pt %f, eta %f, phi %f PDGID %i\n", daughterPt,daughterEta,daughterPhi,daughterPDGID); }
        if(dodebug){
         cout<<"*************** Daughter Loop Details ************"<<endl;
                 cout <<"VertexRefIndex: "<<vref.index()<<" Pt: "<<daughter->pt()
                      <<" Charge: "<<daughter->charge()<<" daughterPDGID: "<<daughter2.pdgId()
                      <<" fromPv(): "<<daughter2.fromPV()
                      << " pvAssociationQuality(): " <<daughter2.pvAssociationQuality()
		      << endl;
		   //<<"motherRef"<<iJet->genParton()->motherRef()->pdgId()<<endl;
         cout<<"*************** Daughter Loop Details end*********"<<endl;
        }

        tmpTrackPt    .push_back( daughterPt    );
        tmpTrackEta   .push_back( daughterEta   );
        tmpTrackPhi   .push_back( daughterPhi   );
        tmpTrackPDGID .push_back( daughterPDGID );

        //jetTrackPDGID_.push_back(daughter2.pdgId());

        // r = transverse vertex distance
        math::XYZPoint jetDauVertex = daughter2.vertex();
        float jetDauVertex_r = sqrt(pow(jetDauVertex.x(),2)+pow(jetDauVertex.y(),2));
	jetDauVertex_x_.push_back(jetDauVertex.x());
	jetDauVertex_y_.push_back(jetDauVertex.y());
	jetDauVertex_z_.push_back(jetDauVertex.z());
	jetDauVertex_r_.push_back(jetDauVertex_r);

        // set lead soft lepton (track) variables
	if (abs(daughter->pdgId()) == 11 || abs(daughter->pdgId()) == 13) {
	  if (daughterPt > lepTrkPt) {
	    lepTrkPID = daughter->pdgId();
	    lepTrkPt  = daughterPt;
	    lepTrkEta = daughterEta;
	    lepTrkPhi = daughterPhi;
	  }
	}  

        // set lead (neutral) track variables
	if (daughter->charge() != 0 && daughterPt > leadTrkPt) {
	  leadTrkPt  = daughterPt;
	  leadTrkEta = daughterEta;
	  leadTrkPhi = daughterPhi;
	}

        // Displaced Jet Variables
        // restrict to neutral tracks 
        // should we include cut : daughter2.fromPV() > 1
        if (daughter->charge() != 0)
        {

          // Impact Parameter
          dxy = fabs(daughter2.dxy()); 
          dxyerr = daughter2.dxyError();
          if(dxyerr>0){ dxySig = dxy/dxyerr; IPtest = true; }
	  if (IPtest ==true){
	    SumIP += dxy;
	    SumIPSig +=dxySig;
	    //cout <<"************dxy: " <<dxy<< " dxyerr: "<<dxyerr<< " dxySig: "<<dxySig<<" log10dxySig: "<< log10(dxySig) <<endl; 
	    jetLog10IPSig_.push_back( log10(dxySig) );
	  }     

	  // Alpha----------------------
          int vtxIDminTrackDz=-1;
          float minPvDz = 10000.0; 

          // loop over vertices (already looping over tracks and jets)
          if(dodebug){ printf("   Looping over vertices\n"); }
	  for(unsigned int k = 0; k < vtxHandle->size(); ++k){

            // variation with fromPV > 1
	    if(daughter2.fromPV(k) >1){
              if(dodebug){ printf("      (2+) associated with vtx %u\n",k); }

	      sumtracksfPV2[k]  += daughterPt;
	      sum2tracksfPV2[k] += daughterPt*daughterPt;
	    }

            // variation with fromPV > 2
	    if(daughter2.fromPV(k) >2){
              if(dodebug){ printf("      -(3+) associated with vtx %u\n",k); }
              // what is this beta about? 
	      promptTotal   += daughterPt;
	      promptTotal2  += daughterPt*daughterPt;

	      sumtracksfPV3[k]  += daughterPt;
	      sum2tracksfPV3[k] += daughterPt*daughterPt;
	    }

            // vtxIDminTrackDz is the ID of the vtx with smallest dZ to this specific jet daughter
            // will need two loops
            //  first find the vtx id for min dz with track (must go through all vtxs)
            //  then (still looping over tracks) add track pt to sumtracksMinDZ[ vtx id w/ min dz to track ]
                 //std::cout<<"  vtx trk DZ = "<<daughter2.dz(vtxHandle->at(k).position())<<std::endl;
            if(fabs(daughter2.dz(vtxHandle->at(k).position())) < minPvDz) {
             minPvDz = fabs(daughter2.dz(vtxHandle->at(k).position()));
             vtxIDminTrackDz = k;
            }
	  }  // end looping over vertices
                 //printf(" end of vertices, minPVDz was %f at id %i \n", minPvDz,vtxIDminTrackDz); 

          // vtxIDminTrackDz is ID of the best vtx for this track, add track pt to alpha numerator for this vtx
          sumtracksMinDzVtx[vtxIDminTrackDz]  += daughterPt;
          sum2tracksMinDzVtx[vtxIDminTrackDz] += daughterPt*daughterPt;

          sumneutraltracks += daughterPt;
          sum2neutraltracks += daughterPt*daughterPt;

	  //track angle stuff  ----- FIXME
	  //get point of closest approach
	  math::XYZPoint CA = daughter2.vertex();
	  TVector3 Tang(CA.x(),CA.y(),CA.z());
	  //jetTrackPhi_.push_back(daughter2.phiAtVtx());
	  jetTrackAngle_.push_back(Tang.Angle(JetAxis)); //acos(Tang*JetAxis/(MagTang*MagJetAxis)));
	  jetLogTrackAngle_.push_back( log(fabs(Tang.Angle(JetAxis))) );//not sure if log or log10
	  TotalTrackAngle += Tang.Angle(JetAxis);
	  // reco::TransientTrack tt(trackHandle->at(id),magneticField_); 

        //printf(" end of track, minPVDz was at id %i \n", vtxIDminTrackDz); 
        } // if (daughter->charge!=0)

        sumalltracks += daughterPt;
        sum2alltracks += daughterPt*daughterPt;

      } // if daughter exists, nonnull
    } // loop over tracks

    // if you want to save this to the ntuple, it should be vector< vector< float > > 
    //  don't forget that we have multiple jets
    jetAlphaD_.clear();

    //save alpha = sum over tracks associated with vtx / all tracks
    if(sumalltracks>0){
     for(unsigned z =0; z <sumtracksMinDzVtx.size(); z++){
      //std::cout<<"sum["<<z<<"] = "<<sumtracksMinDzVtx[z]<<" sumalltracks = "<<sumalltracks<<" div = "<<sumtracksMinDzVtx[z]/sumalltracks<<std::endl;
      jetAlphaD_.push_back(sumtracksMinDzVtx[z]/sumalltracks);
     }
    }
    else { jetAlphaD_.push_back(-99.9); }

    //set alphaMax variable out of range of true alpha max
    float alphaM = -99.9;
    //find the maximum 
    for (unsigned y = 0; y<jetAlphaD_.size(); y++){
     if(jetAlphaD_[y]>alphaM){ alphaM = jetAlphaD_[y];}
    }	
    // std::cout<<"  max = "<<alphaM<<std::endl;
    jetAlphaMaxD_.push_back(alphaM);



    //if(alphaM<0){
    // for(unsigned z =0; z <sumtracksMinDzVtx.size(); z++)
    // {
    //  std::cout<<sumtracksMinDzVtx[z]/sumalltracks<<" "<<sumtracksMinDzVtx[z]<<" "<<sumalltracks<<std::endl;
    // }
    //}

    //      vector<float> alphaNum_ = vector<float>(vtxHandle->size(),0.0);
    //alphaNum_.clear();
    // push back vector of track variables for this specific jet
    jetTrackPt_    .push_back( tmpTrackPt    );
    jetTrackEta_   .push_back( tmpTrackEta   );
    jetTrackPhi_   .push_back( tmpTrackPhi   );
    jetTrackPDGID_ .push_back( tmpTrackPDGID );

    //if(dodebug){ 
    // printf("   Done Loopong over tracks\n"); 
    // //for(unsigned int k = 0; k < sumtracksfPV2->size(); ++k){
    // for(unsigned int k = 0; k < sumtracksfPV2.size(); ++k){
    //    printf("    sum trackpt vtx %u  pt %f / %f \n", k,  sumtracksfPV2[k], sumalltracks );
    //  }
    // }

    float alphaMax = -1;
    float alphaMax2 = -1;
    float apMax =-1;
    float apMax2 = -1;
    float beta = 1.0 - promptTotal/sumalltracks;
    float beta2 = 1.0 - promptTotal2/sum2alltracks;
    for(int i = 0; i < (int)sumtracksfPV2.size(); i++){
      //if(sumtracksfPV2[i] = 0)continue;
      if(sumtracksfPV2[i] > alphaMax) alphaMax = sumtracksfPV2[i];
      if(sum2tracksfPV2[i] > alphaMax2) alphaMax2 = sum2tracksfPV2[i];
      float ap = sumtracksfPV2[i] / (sumtracksfPV2[i] + beta);
      float ap2 = sum2tracksfPV2[i] / (sum2tracksfPV2[i] + beta2);
      if(ap > apMax) apMax = ap;
      if(ap2 > apMax2) apMax2 = ap2;
    }

    float jetAlphaMax_PV3onPV2 = -1;
    float jetAlphaMax_PV3onNeu = -1;
    float jetAlphaMax_PV3onAll = -1;
    float jetAlphaMax_PV2onNeu = -1;
    float jetAlphaMax_PV2onAll = -1;

    float jetAlpha_PV3onPV2 = -1;
    float jetAlpha_PV3onNeu = -1;
    float jetAlpha_PV3onAll = -1;
    float jetAlpha_PV2onNeu = -1;
    float jetAlpha_PV2onAll = -1;

    float jetAlpha2Max_PV3onPV2 = -1;
    float jetAlpha2Max_PV3onNeu = -1;
    float jetAlpha2Max_PV3onAll = -1;
    float jetAlpha2Max_PV2onNeu = -1;
    float jetAlpha2Max_PV2onAll = -1;

    float jetAlpha2_PV3onPV2 = -1;
    float jetAlpha2_PV3onNeu = -1;
    float jetAlpha2_PV3onAll = -1;
    float jetAlpha2_PV2onNeu = -1;
    float jetAlpha2_PV2onAll = -1;

    for(unsigned int q = 0; q < sumtracksfPV3.size(); q++){
      jetAlpha_PV3onPV2  = sumtracksfPV3[q]  / sumtracksfPV2[q] ;
      jetAlpha2_PV3onPV2 = sum2tracksfPV3[q] / sum2tracksfPV2[q];
      if(jetAlpha_PV3onPV2  > jetAlphaMax_PV3onPV2 ){ jetAlphaMax_PV3onPV2  = jetAlpha_PV3onPV2; }
      if(jetAlpha2_PV3onPV2 > jetAlpha2Max_PV3onPV2){ jetAlpha2Max_PV3onPV2 = jetAlpha2_PV3onPV2; }
    }

    for(unsigned int q = 0; q < sumtracksfPV3.size(); q++){
      jetAlpha_PV3onNeu  = sumtracksfPV3[q]  / sumneutraltracks ;
      jetAlpha2_PV3onNeu = sum2tracksfPV3[q] / sum2neutraltracks;
      if(jetAlpha_PV3onNeu  > jetAlphaMax_PV3onNeu ){ jetAlphaMax_PV3onNeu  = jetAlpha_PV3onNeu; }
      if(jetAlpha2_PV3onNeu > jetAlpha2Max_PV3onNeu){ jetAlpha2Max_PV3onNeu = jetAlpha2_PV3onNeu; }
    }

    for(unsigned int q = 0; q < sumtracksfPV3.size(); q++){
      jetAlpha_PV3onAll  = sumtracksfPV3[q]  / sumalltracks ;
      jetAlpha2_PV3onAll = sum2tracksfPV3[q] / sum2alltracks;
      if(jetAlpha_PV3onAll  > jetAlphaMax_PV3onAll ){ jetAlphaMax_PV3onAll  = jetAlpha_PV3onAll; }
      if(jetAlpha2_PV3onAll > jetAlpha2Max_PV3onAll){ jetAlpha2Max_PV3onAll = jetAlpha2_PV3onAll; }
    }

    for(unsigned int q = 0; q < sumtracksfPV2.size(); q++){
      jetAlpha_PV2onNeu  = sumtracksfPV2[q]  / sumneutraltracks ;
      jetAlpha2_PV2onNeu = sum2tracksfPV2[q] / sum2neutraltracks;
      if(jetAlpha_PV2onNeu  > jetAlphaMax_PV2onNeu ){ jetAlphaMax_PV2onNeu  = jetAlpha_PV2onNeu; }
      if(jetAlpha2_PV2onNeu > jetAlpha2Max_PV2onNeu){ jetAlpha2Max_PV2onNeu = jetAlpha2_PV2onNeu; }
    }

    for(unsigned int q = 0; q < sumtracksfPV2.size(); q++){
      jetAlpha_PV2onAll  = sumtracksfPV2[q]  / sumalltracks ;
      jetAlpha2_PV2onAll = sum2tracksfPV2[q] / sum2alltracks;
      if(jetAlpha_PV2onAll  > jetAlphaMax_PV2onAll ){ jetAlphaMax_PV2onAll  = jetAlpha_PV2onAll; }
      if(jetAlpha2_PV2onAll > jetAlpha2Max_PV2onAll){ jetAlpha2Max_PV2onAll = jetAlpha2_PV2onAll; }
    }


//        sumalltracks += daughterPt;
//        sum2alltracks += daughterPt*daughterPt;
//        sumneutraltracks += daughterPt;
//        sum2neutraltracks += daughterPt*daughterPt;
//	sumtracksfPV2[k]  += daughterPt;
//	sum2tracksfPV2[k] += daughterPt*daughterPt;
//	sumtracksfPV3[k]  += daughterPt;
//	sum2tracksfPV3[k] += daughterPt*daughterPt;


    jetAlphaMax_PV3onPV2_ .push_back(jetAlphaMax_PV3onPV2); 
    jetAlphaMax_PV3onNeu_ .push_back(jetAlphaMax_PV3onNeu); 
    jetAlphaMax_PV3onAll_ .push_back(jetAlphaMax_PV3onAll); 
    jetAlphaMax_PV2onNeu_ .push_back(jetAlphaMax_PV2onNeu); 
    jetAlphaMax_PV2onAll_ .push_back(jetAlphaMax_PV2onAll); 

    jetAlpha2Max_PV3onPV2_ .push_back(jetAlpha2Max_PV3onPV2);
    jetAlpha2Max_PV3onNeu_ .push_back(jetAlpha2Max_PV3onNeu);
    jetAlpha2Max_PV3onAll_ .push_back(jetAlpha2Max_PV3onAll);
    jetAlpha2Max_PV2onNeu_ .push_back(jetAlpha2Max_PV2onNeu);
    jetAlpha2Max_PV2onAll_ .push_back(jetAlpha2Max_PV2onAll);


    jetAlphaMax_.push_back(alphaMax / sumalltracks);
    jetAlphaMax2_.push_back(alphaMax2 / sum2alltracks);
    jetAlphaMaxP_.push_back(apMax);
    jetAlphaMaxP2_.push_back(apMax2);
	 
    jetLeadTrackPt_ .push_back(leadTrkPt);
    jetLeadTrackEta_.push_back(leadTrkEta);
    jetLeadTrackPhi_.push_back(leadTrkPhi);
    jetLepTrackPID_ .push_back(lepTrkPID);
    jetLepTrackPt_  .push_back(lepTrkPt);
    jetLepTrackEta_ .push_back(lepTrkEta);
    jetLepTrackPhi_ .push_back(lepTrkPhi);    
    jetVtxPt_       .push_back(sqrt(pow(iJet->userFloat("vtxPx"),2)+pow(iJet->userFloat("vtxPy"),2)));
    jetVtxMass_     .push_back(iJet->userFloat("vtxMass"));
    jetVtxNtrks_    .push_back(iJet->userFloat("vtxNtracks"));
    jetVtx3DVal_    .push_back(iJet->userFloat("vtx3DVal"));
    jetVtx3DSig_    .push_back(iJet->userFloat("vtx3DSig"));
    
    //b-tagging
    jetCSV2BJetTags_           .push_back(iJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
    jetJetProbabilityBJetTags_ .push_back(iJet->bDiscriminator("pfJetProbabilityBJetTags"));
    jetpfCombinedMVAV2BJetTags_.push_back(iJet->bDiscriminator("pfCombinedMVAV2BJetTags"));
  
    //parton id
    jetPartonID_.push_back(iJet->partonFlavour());
    jetHadFlvr_.push_back(iJet->hadronFlavour());

    // Displaced Jet Variable : median jet log IP significance
    //
    //cout<<endl;
    //cout<<endl;
    //cout<<"***********"<<" Event: "<<e.id().event()<<" Jet: "<<nrjet<<", "<<nJet_<<"**************" <<endl;
    //cout<<"Un-Sorted("<<jetLog10IPSig_.size()<<"): ";
    //for (i=0; i<jetLog10IPSig_.size(); i++)
    //{
    //cout<<jetLog10IPSig_[i]<<", ";
    //}
    //cout<<endl;

    // must sort IPsig to be able to find median
    sort(jetLog10IPSig_.begin(), jetLog10IPSig_.end());
    sort(jetLogTrackAngle_.begin(), jetLogTrackAngle_.end());

    //bool skim = false
    //for(i=0; i<jetLog10IPSig_.begin();i++){
    //
    //cout<<endl;
    //cout<<"Last element(b): "<<jetLog10IPSig_[jetLog10IPSig_.size()-1]<<endl;
    //if(jetLog10IPSig_.size()>1 && jetLog10IPSig_[jetLog10IPSig_.size()-1] >=9999999.0) jetLog10IPSig_.pop_back();
    //cout<<endl;
    //cout<<"Last element(a): "<<jetLog10IPSig_[jetLog10IPSig_.size()-1]<<endl;
    //
    //cout<<"Sorted("<<jetLog10IPSig_.size()<<"): ";
    //for (i=0; i<jetLog10IPSig_.size(); i++)
    //{
    //cout<<jetLog10IPSig_[i]<<", "; 
    //}

    //Now find median
    //Note .at() threw error
    if(jetLog10IPSig_.size() == 0){
      IP0Sum+=1;
      jetMedianLog10IPSig_.push_back(-99.9); 
     // if(fabs(MedianLog10IPSig)>99.0){cout<<"IF "<<MedianLog10IPSig<<" "<<jetLog10IPSig_.size()<<endl;}
    }
    else if(jetLog10IPSig_.size()%2 ==0){
      //cout<<"elseif"<<" "<<jetLog10IPSig_.size()<<endl;
      //cout<<"jetLog10IPSig_.size()/2) -1"<< jetLog10IPSig_.size()/2) -1 <<endl;
      //cout<<"
      MedianLog10IPSig = 0.5*( jetLog10IPSig_.at( (jetLog10IPSig_.size()/2) -1 ) 
                             + jetLog10IPSig_.at(  jetLog10IPSig_.size()/2     ));
      jetMedianLog10IPSig_.push_back(MedianLog10IPSig);
      //if(fabs(MedianLog10IPSig)>99.0){cout<<"elseif"<<MedianLog10IPSig<<" "<<jetLog10IPSig_.size()<<endl;}
    }
    else{
     // cout<<"ELSE"<<" "<<jetLog10IPSig_.size()<<endl;
      MedianLog10IPSig =       jetLog10IPSig_.at( (jetLog10IPSig_.size()-1)/2 );
      jetMedianLog10IPSig_.push_back(MedianLog10IPSig);
     // if(fabs(MedianLog10IPSig)>99.0){cout<<"ELSE"<<MedianLog10IPSig<<" "<<jetLog10IPSig_.size()<<endl;}
    }
    

    // Track Angle still broken FIXME
    //cout <<" TotalTA: " << TotalTrackAngle<<endl;
    //TrackAngle_Median
    if(jetLogTrackAngle_.size() == 0){
    TA0Sum+=1;
    //cout<<" IF_TA "<<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    }
    else if(jetLogTrackAngle_.size()%2 ==0)
    {
    MedianLogTrackAngle = 0.5*( jetLogTrackAngle_[(jetLogTrackAngle_.size()/2) -1]
                              + jetLogTrackAngle_[ jetLogTrackAngle_.size()/2    ]);
    //if(MedianLogTrackAngle>10000.0 || MedianLogTrackAngle<-10000.0)cout <<"**************"<<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    jetMedianLogTrackAngle_.push_back(MedianLogTrackAngle);
    //cout<<" elseif_TA: "<<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    }
    else
    {
    MedianLogTrackAngle =       jetLogTrackAngle_[(jetLogTrackAngle_.size()-1)/2];
    //if(MedianLogTrackAngle>10000.0 || MedianLogTrackAngle<-10000.0)cout<<"**************" <<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    jetMedianLogTrackAngle_.push_back(MedianLogTrackAngle);
    //cout<<" ELSE_TA: "<<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    }    

    //jetMedianLog10IPSig_.push_back(MedianLog10IPSig);
    jetSumIP_.push_back(SumIP);
    jetSumIPSig_.push_back(SumIPSig);

    if(jetLogTrackAngle_.size()>0)jetTotalTrackAngle_.push_back(TotalTrackAngle);


    // gen jet and parton
    int jetGenPartonID    = -99;
    int jetGenPartonMomID = -99;
    float jetGenEn        = -999.;
    float jetGenPt        = -999.;
    float jetGenEta       = -999.;
    float jetGenPhi       = -999.;      
     
    float jetGenJetEn  = -999.;
    float jetGenJetPt  = -999.;
    float jetGenJetEta = -999.;
    float jetGenJetPhi = -999.;
    if( ! e.isRealData() ){
     if ((*iJet).genParton()) {
      jetGenPartonID = (*iJet).genParton()->pdgId();
      jetGenEn = (*iJet).genParton()->energy();
      jetGenPt = (*iJet).genParton()->pt();
      jetGenEta = (*iJet).genParton()->eta();
      jetGenPhi = (*iJet).genParton()->phi();
      if ((*iJet).genParton()->mother()) {
       jetGenPartonMomID = (*iJet).genParton()->mother()->pdgId();
      }
     }
      
    jetGenPartonID_.push_back(jetGenPartonID);
    jetGenPartonMomID_.push_back(jetGenPartonMomID);
    jetGenEn_ .push_back(jetGenEn);
    jetGenPt_ .push_back(jetGenPt);
    jetGenEta_ .push_back(jetGenEta);
    jetGenPhi_ .push_back(jetGenPhi);
    if ((*iJet).genJet()) {
     jetGenJetEn = (*iJet).genJet()->energy();
     jetGenJetPt = (*iJet).genJet()->pt();
     jetGenJetEta = (*iJet).genJet()->eta();
     jetGenJetPhi = (*iJet).genJet()->phi();
    }
    jetGenJetEn_.push_back(jetGenJetEn);
    jetGenJetPt_.push_back(jetGenJetPt);
    jetGenJetEta_.push_back(jetGenJetEta);
    jetGenJetPhi_.push_back(jetGenJetPhi);
    
    // access jet resolution       
    JME::JetParameters parameters;
    parameters.setJetPt(iJet->pt()).setJetEta(iJet->eta()).setRho(rho);
    float jetResolution = jetResolution_.getResolution(parameters);

     edm::Service<edm::RandomNumberGenerator> rng;
     if (!rng.isAvailable()) edm::LogError("JET : random number generator is missing !");
     CLHEP::HepRandomEngine & engine = rng->getEngine( e.streamID() );
     float rnd = CLHEP::RandGauss::shoot(&engine, 0., jetResolution);

     float jetResolutionSF   = jetResolutionSF_.getScaleFactor(parameters);
     float jetResolutionSFUp = jetResolutionSF_.getScaleFactor(parameters, Variation::UP);
     float jetResolutionSFDo = jetResolutionSF_.getScaleFactor(parameters, Variation::DOWN);

     float jetP4Smear   = -1.;
     float jetP4SmearUp = -1.;
     float jetP4SmearDo = -1.;
     if (jetGenJetPt > 0 && reco::deltaR(iJet->eta(), iJet->phi(), jetGenJetEta, jetGenJetPhi) < 0.2 && fabs(iJet->pt()-jetGenJetPt) < 3*jetResolution*iJet->pt()) {
       jetP4Smear   = 1. + (jetResolutionSF   - 1.)*(iJet->pt() - jetGenJetPt)/iJet->pt();
       jetP4SmearUp = 1. + (jetResolutionSFUp - 1.)*(iJet->pt() - jetGenJetPt)/iJet->pt();
       jetP4SmearDo = 1. + (jetResolutionSFDo - 1.)*(iJet->pt() - jetGenJetPt)/iJet->pt();
     } else {
       jetP4Smear   = 1. + rnd*sqrt(max(pow(jetResolutionSF,   2)-1, 0.));
       jetP4SmearUp = 1. + rnd*sqrt(max(pow(jetResolutionSFUp, 2)-1, 0.));
       jetP4SmearDo = 1. + rnd*sqrt(max(pow(jetResolutionSFDo, 2)-1, 0.));
     }
     jetP4Smear_  .push_back(jetP4Smear);
     jetP4SmearUp_.push_back(jetP4SmearUp);
     jetP4SmearDo_.push_back(jetP4SmearDo);
    }
    
    nJet_++;
  }/// End Jets Loop
  
  if(dodebug){
    printf("    After jet loop, check all track vars\n");
    for(unsigned int k = 0; k < jetTrackPt_.size(); ++k){
      for(unsigned int l = 0; l < jetTrackPt_.at(k).size(); ++l){
	printf("    pt %f, eta %f, phi %f PDGID %i\n",
	       jetTrackPt_.at(k).at(l), jetTrackEta_.at(k).at(l),
	       jetTrackPhi_.at(k).at(l), jetTrackPDGID_.at(k).at(l) );
      }
    }
  }
  delete jecUnc;
  

  // AOD Section ----------------------------------------------
  
  bool verbose_AOD = false;
  
  // AOD Jet Handles
  e.getByToken( AODak4CaloJetsLabel_ ,  AODak4CaloJetsHandle  );   
  e.getByToken( AODak4PFJetsLabel_   ,  AODak4PFJetsHandle    );     
  e.getByToken( AODak4PFJetsCHSLabel_,  AODak4PFJetsCHSHandle );  
  e.getByToken( AODVertexLabel_      ,  AODVertexHandle );
  e.getByToken( AODTrackLabel_       ,  AODTrackHandle );

  edm::ESHandle<MagneticField> magneticField;
  es.get<IdealMagneticFieldRecord>().get(magneticField);
  magneticField_ = &*magneticField;

  //edm::InputTag beamspotLabel_ = pset.getParameter<InputTag>("beamSpotInputTag");
  //edm::EDGetTokenT<reco::BeamSpot> beamspotToken_;
  //beamspotToken_ = consumes<reco::BeamSpot>(beamspotLabel_);
  //edm::Handle<reco::BeamSpot> beamspotHandle_;
  //e.getByToken(beamspotToken_, beamspotHandle_);

  e.getByToken(beamspotLabel_, beamspotHandle_);

  vertexBeam_->setBeamSpot(*beamspotHandle_);

  //original stateontracker location

  es.get<TransientTrackRecord>().get("TransientTrackBuilder",theBuilder_);
  
  //Debug printing
  if(verbose_AOD){
    for(int j = 0; j < (int)AODTrackHandle->size(); j++){
      reco::TrackBaseRef tref(AODTrackHandle,j);
      printf("AOD track pt eta phi: %f %f %f\n",tref->pt(),tref->eta(),tref->phi());
    }
  }
  
  // Vertex
  std::vector<int> trackToCaloJetMap_;
  trackToCaloJetMap_.clear();
  trackToCaloJetMap_ = vector<int>(AODTrackHandle->size(),-1);
  std::vector<int> whichVertex_;
  whichVertex_.clear();
  whichVertex_ = vector<int>(AODTrackHandle->size(),-1);
  for(int i = 0; i < (int)AODTrackHandle->size(); i++){
    double maxWeight = 0; 
    int jj = -1;
    reco::TrackBaseRef tref(AODTrackHandle,i);
    for(int j = 0; j < (int)AODVertexHandle->size();j++){            //
      if(AODVertexHandle->at(j).trackWeight(tref) > maxWeight){      //
        maxWeight = AODVertexHandle->at(j).trackWeight(tref);        //
        jj = j;                                                      //
      }                                                              //
    }                                                                //
    whichVertex_[i] = jj;
  }
  
    
  // AOD Calo Jets -------------------------------------------
  for (edm::View<reco::CaloJet>::const_iterator iJet = AODak4CaloJetsHandle->begin(); iJet != AODak4CaloJetsHandle->end(); ++iJet) {

    if(verbose_AOD) printf("Calo %f \n",iJet->pt());
    
    float jetpt  = iJet->pt();
    float jeteta = iJet->eta();
    float jetphi = iJet->phi();

    bool fill_tracksIPLog10Sig_median=true, fill_trackAngles_median=true;
    float tracksIPLog10Sig_median=0, trackAngles_median=0;
    float sumIP=0, sumIPSig=0, totalTrackAngle=0;
    std::vector<reco::TransientTrack> transientTracks;
    std::vector<int> vertexVector;

    aod_jet_track_calculations(e, es,
			       jeteta, jetphi, whichVertex_, 
			       fill_tracksIPLog10Sig_median, tracksIPLog10Sig_median, fill_trackAngles_median, trackAngles_median, 
			       sumIP, sumIPSig, totalTrackAngle, transientTracks, vertexVector);
    
    double alphaMax,alphaMaxPrime,beta,alphaMax2,alphaMaxPrime2,beta2;
    calculateAlphaMax(transientTracks,vertexVector,alphaMax,alphaMaxPrime,beta,alphaMax2,alphaMaxPrime2,beta2);
    
    
    //////////////////////////////////////////////////
    //Displaced Vertices
    //////////////////////////////////////////////////
    if(transientTracks.size() > 1){
      
      //skip refit of jet vertex for now
      
      vector<TransientVertex> avfVerts = vtxfitter_->vertices(transientTracks);
      if(avfVerts.size() > 0 && avfVerts[0].isValid()){
        GlobalPoint vertPos = avfVerts[0].position();
        GlobalError vertErr = avfVerts[0].positionError();
	
	AODCaloJetAvfVx_.push_back( vertPos.x() );
	AODCaloJetAvfVy_.push_back( vertPos.y() );
	AODCaloJetAvfVz_.push_back( vertPos.z() );

        float vertBeamXY = vertexBeam_->distanceToBeam(reco::Vertex(RecoVertex::convertPos(vertPos),RecoVertex::convertError(vertErr)));
	
	AODCaloJetAvfVertexTotalChiSquared_.push_back( avfVerts[0].totalChiSquared() );
	AODCaloJetAvfVertexDegreesOfFreedom_.push_back( avfVerts[0].degreesOfFreedom() );
	if(avfVerts[0].degreesOfFreedom() > 0) AODCaloJetAvfVertexChi2NDoF_.push_back( avfVerts[0].totalChiSquared()/avfVerts[0].degreesOfFreedom() );
	AODCaloJetAvfVertexDistanceToBeam_.push_back( vertBeamXY );
        double rerr = vertErr.rerr(vertPos);
	AODCaloJetAvfVertexTransverseError_.push_back( rerr );
        if(rerr > 0) AODCaloJetAvfVertexTransverseSig_.push_back( vertBeamXY/rerr );



	vector<reco::TransientTrack> cleanTrackColl = cleanTracks(avfVerts[0].refittedTracks(),vertPos);
	
        double d3deta = 0, d3dphi = 0, d3dpt = 0, d3m = 0, d3en;
        deltaVertex3D(vertPos, cleanTrackColl,d3deta,d3dphi,d3dpt,d3m,d3en);
        AODCaloJetAvfVertexDeltaEta_.push_back( d3deta );
        AODCaloJetAvfVertexDeltaPhi_.push_back( d3dphi );
        AODCaloJetAvfVertexRecoilPt_.push_back( d3dpt );
        AODCaloJetAvfVertexTrackMass_.push_back( d3m );
        AODCaloJetAvfVertexTrackEnergy_.push_back( d3en );
        double d2dphi = 0,d2dpt = 0,d2dphiMed=1e-6;
        deltaVertex2D(vertPos,cleanTrackColl,d2dphi,d2dpt,d2dphiMed);
        AODCaloJetAvfBeamSpotDeltaPhi_.push_back( d2dphi );
        AODCaloJetAvfBeamSpotRecoilPt_.push_back( d2dpt );
        AODCaloJetAvfBeamSpotMedianDeltaPhi_.push_back( d2dphiMed );
        AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_.push_back( log10(d2dphiMed) );
        AODCaloJetNCleanMatchedTracks_.push_back( (int)cleanTrackColl.size() );
	
        int nHitsInFront = 0;
        int nMissingAfter = 0;
	CheckHitPattern checkHitPattern_;
	for(int j = 0; j < (int)cleanTrackColl.size(); j++){
	  CheckHitPattern::Result res = checkHitPattern_.analyze(es,cleanTrackColl[j].track(),avfVerts[0].vertexState(),false);
          nHitsInFront += res.hitsInFrontOfVert;
          nMissingAfter += res.missHitsAfterVert;
        }
        AODCaloJetSumHitsInFrontOfVert_.push_back( nHitsInFront );
        AODCaloJetSumMissHitsAfterVert_.push_back( nMissingAfter );
        AODCaloJetHitsInFrontOfVertPerTrack_.push_back( double(nHitsInFront)/double(transientTracks.size()) );
        AODCaloJetMissHitsAfterVertPerTrack_.push_back( double(nMissingAfter)/double(transientTracks.size()) );
	
        AODCaloJetAvfDistToPV_.push_back( 
	  sqrt(pow((AODVertexHandle->at(0).x() - avfVerts[0].position().x())/AODVertexHandle->at(0).x(),2)
	       +pow((AODVertexHandle->at(0).y() - avfVerts[0].position().y())/AODVertexHandle->at(0).y(),2)
	       +pow((AODVertexHandle->at(0).z() - avfVerts[0].position().z())/AODVertexHandle->at(0).z(),2)) );
	if(AODVertexHandle->size() > 0)AODCaloJetAvfVertexDeltaZtoPV_.push_back( AODVertexHandle->at(0).z() - avfVerts[0].position().z() );
	if(AODVertexHandle->size() > 1)AODCaloJetAvfVertexDeltaZtoPV2_.push_back( AODVertexHandle->at(1).z() - avfVerts[0].position().z() );
	
      
      }//end valid avf vertex
      
    }//end if transientTracks
    
    
    // ID
    bool passID = false;
    if(transientTracks.size()>=1 && iJet->emEnergyFraction()>=0.0 && iJet->emEnergyFraction()<=0.9 && iJet->energyFractionHadronic()>=0.0 && iJet->energyFractionHadronic()<=0.9) passID = true; 
    if(iJet->pt()<20.0 || fabs(iJet->eta())>2.4 || !passID) continue;
    
    ////////////////////////
    // Fill tree
    /////////////////////////
    AODnCaloJet_++;
    
    //Pt, Eta, Phi
    AODCaloJetPt_.push_back(jetpt);
    AODCaloJetEta_.push_back(jeteta);
    AODCaloJetPhi_.push_back(jetphi);
    
    //AlphaMax-type variables
    AODCaloJetAlphaMax_       .push_back(alphaMax      ) ; 
    AODCaloJetAlphaMax2_      .push_back(alphaMax2     ) ; 
    AODCaloJetAlphaMaxPrime_  .push_back(alphaMaxPrime ) ; 
    AODCaloJetAlphaMaxPrime2_ .push_back(alphaMaxPrime2) ; 
    AODCaloJetBeta_           .push_back(beta          ) ; 
    AODCaloJetBeta2_          .push_back(beta2         ) ; 
    
    //Totals
    AODCaloJetSumIP_.push_back(sumIP);
    AODCaloJetSumIPSig_.push_back(sumIPSig);
    AODCaloJetTotalTrackAngle_.push_back(totalTrackAngle);    
    
    //Medians
    if(fill_tracksIPLog10Sig_median) AODCaloJetMedianLog10IPSig_.push_back(tracksIPLog10Sig_median);
    if(fill_trackAngles_median) AODCaloJetMedianLogTrackAngle_.push_back(trackAngles_median);
    
    //Vectors currently not saved
    //AODCaloJetLog10IPSig_; //tracksIPLogSig;
    //AODCaloJetLogTrackAngle_; //trackAngles; 
    //AODCaloJetTrackAngle_;
    
    //Other variables to do: refit vertex, avf vertex, hit info, boost variables
    
  }
  

  // AOD PF Jets -------------------------------------------
  for (edm::View<reco::PFJet>::const_iterator iJet = AODak4PFJetsHandle->begin(); iJet != AODak4PFJetsHandle->end(); ++iJet) {
    
    float jetpt  = iJet->pt();
    float jeteta = iJet->eta();
    float jetphi = iJet->phi();
    
    bool fill_tracksIPLog10Sig_median=true, fill_trackAngles_median=true;
    float tracksIPLog10Sig_median=0, trackAngles_median=0;
    float sumIP=0, sumIPSig=0, totalTrackAngle=0;
    std::vector<reco::TransientTrack> transientTracks;
    std::vector<int> vertexVector;

    aod_jet_track_calculations(e, es,
			       jeteta, jetphi, whichVertex_, 
			       fill_tracksIPLog10Sig_median, tracksIPLog10Sig_median, fill_trackAngles_median, trackAngles_median, 
			       sumIP, sumIPSig, totalTrackAngle, transientTracks, vertexVector);

    double alphaMax,alphaMaxPrime,beta,alphaMax2,alphaMaxPrime2,beta2;
    calculateAlphaMax(transientTracks,vertexVector,alphaMax,alphaMaxPrime,beta,alphaMax2,alphaMaxPrime2,beta2);

    
    // ID
    bool passID = false;
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_13_TeV_2016
    double NHF = iJet->neutralHadronEnergyFraction();
    double NEMF = iJet->neutralEmEnergyFraction();
    double CHF = iJet->chargedHadronEnergyFraction();
    //double MUF = iJet->muonEnergyFraction();
    double CEMF = iJet->chargedEmEnergyFraction();
    int NumConst = iJet->chargedMultiplicity()+iJet->neutralMultiplicity();
    //int NumNeutralParticles =iJet->neutralMultiplicity();
    int CHM = iJet->chargedMultiplicity();
    bool looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((fabs(jeteta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(jeteta)>2.4) && fabs(jeteta)<=2.7;
    if(transientTracks.size()>=1 && looseJetID) passID = true;
    if(iJet->pt()<20.0 || fabs(jeteta)>2.4 || !passID) continue;

    ////////////////////////
    // Fill tree
    /////////////////////////
    AODnPFJet_++;
    
    //Pt, Eta, Phi
    AODPFJetPt_.push_back(jetpt);
    AODPFJetEta_.push_back(jeteta);
    AODPFJetPhi_.push_back(jetphi);
    
    //AlphaMax-type variables
    AODPFJetAlphaMax_       .push_back(alphaMax      ) ; 
    AODPFJetAlphaMax2_      .push_back(alphaMax2     ) ; 
    AODPFJetAlphaMaxPrime_  .push_back(alphaMaxPrime ) ; 
    AODPFJetAlphaMaxPrime2_ .push_back(alphaMaxPrime2) ; 
    AODPFJetBeta_           .push_back(beta          ) ; 
    AODPFJetBeta2_          .push_back(beta2         ) ; 

    //Totals
    AODPFJetSumIP_.push_back(sumIP);
    AODPFJetSumIPSig_.push_back(sumIPSig);
    AODPFJetTotalTrackAngle_.push_back(totalTrackAngle);    

    //Medians
    if(fill_tracksIPLog10Sig_median) AODPFJetMedianLog10IPSig_.push_back(tracksIPLog10Sig_median);
    if(fill_trackAngles_median) AODPFJetMedianLogTrackAngle_.push_back(trackAngles_median);

  }

  // AOD PFchs Jets -------------------------------------------
  for (edm::View<reco::PFJet>::const_iterator iJet = AODak4PFJetsCHSHandle->begin(); iJet != AODak4PFJetsCHSHandle->end(); ++iJet) {

    float jetpt  = iJet->pt();
    float jeteta = iJet->eta();
    float jetphi = iJet->phi();
    
    bool fill_tracksIPLog10Sig_median=true, fill_trackAngles_median=true;
    float tracksIPLog10Sig_median=0, trackAngles_median=0;
    float sumIP=0, sumIPSig=0, totalTrackAngle=0;
    std::vector<reco::TransientTrack> transientTracks;
    std::vector<int> vertexVector;

    aod_jet_track_calculations(e, es,
			       jeteta, jetphi, whichVertex_, 
			       fill_tracksIPLog10Sig_median, tracksIPLog10Sig_median, fill_trackAngles_median, trackAngles_median, 
			       sumIP, sumIPSig, totalTrackAngle, transientTracks, vertexVector);

    double alphaMax,alphaMaxPrime,beta,alphaMax2,alphaMaxPrime2,beta2;
    calculateAlphaMax(transientTracks,vertexVector,alphaMax,alphaMaxPrime,beta,alphaMax2,alphaMaxPrime2,beta2);

    // ID
    bool passID = false;
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_13_TeV_2016
    double NHF = iJet->neutralHadronEnergyFraction();
    double NEMF = iJet->neutralEmEnergyFraction();
    double CHF = iJet->chargedHadronEnergyFraction();
    //double MUF = iJet->muonEnergyFraction();
    double CEMF = iJet->chargedEmEnergyFraction();
    int NumConst = iJet->chargedMultiplicity()+iJet->neutralMultiplicity();
    //int NumNeutralParticles =iJet->neutralMultiplicity();
    int CHM = iJet->chargedMultiplicity();
    bool looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((fabs(jeteta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(jeteta)>2.4) && fabs(jeteta)<=2.7;
    if(transientTracks.size()>=1 && looseJetID) passID = true;
    if(iJet->pt()<20.0 || fabs(jeteta)>2.4 || !passID) continue;

    ////////////////////////
    // Fill tree
    /////////////////////////
    AODnPFchsJet_++;
    
    //Pt, Eta, Phi
    AODPFchsJetPt_.push_back(jetpt);
    AODPFchsJetEta_.push_back(jeteta);
    AODPFchsJetPhi_.push_back(jetphi);
    
    //AlphaMax-type variables
    AODPFchsJetAlphaMax_       .push_back(alphaMax      ) ; 
    AODPFchsJetAlphaMax2_      .push_back(alphaMax2     ) ; 
    AODPFchsJetAlphaMaxPrime_  .push_back(alphaMaxPrime ) ; 
    AODPFchsJetAlphaMaxPrime2_ .push_back(alphaMaxPrime2) ; 
    AODPFchsJetBeta_           .push_back(beta          ) ; 
    AODPFchsJetBeta2_          .push_back(beta2         ) ; 

    //Totals
    AODPFchsJetSumIP_.push_back(sumIP);
    AODPFchsJetSumIPSig_.push_back(sumIPSig);
    AODPFchsJetTotalTrackAngle_.push_back(totalTrackAngle);    

    //Medians
    if(fill_tracksIPLog10Sig_median) AODPFchsJetMedianLog10IPSig_.push_back(tracksIPLog10Sig_median);
    if(fill_trackAngles_median) AODPFchsJetMedianLogTrackAngle_.push_back(trackAngles_median);

  }//end pfchs loop
  
}//end fill jets


void lldjNtuple::deltaVertex3D(GlobalPoint secVert, std::vector<reco::TransientTrack> tracks, double& dEta, double& dPhi, double& pt, double& m, double& energy)
{
  TVector3 pv(AODVertexHandle->at(0).x(),AODVertexHandle->at(0).y(),AODVertexHandle->at(0).z());
  TVector3 sv(secVert.x(),secVert.y(),secVert.z());
  TVector3 diff = (sv-pv);
  TVector3 trackPt(0,0,0);
  TLorentzVector trackP4(0,0,0,0);
  for(int i = 0; i < (int)tracks.size(); i++){
    TVector3 tt;
    tt.SetPtEtaPhi(tracks[i].trajectoryStateClosestToPoint(secVert).momentum().transverse(),tracks[i].trajectoryStateClosestToPoint(secVert).momentum().eta(),tracks[i].trajectoryStateClosestToPoint(secVert).momentum().phi());
    trackPt += tt;
    trackP4 += TLorentzVector(tt,tracks[i].trajectoryStateClosestToPoint(secVert).momentum().mag());
  }
  dEta = diff.Eta()-trackPt.Eta();
  dPhi = diff.DeltaPhi(trackPt);
  pt = (trackPt - ((trackPt * diff)/(diff * diff) * diff)).Mag();
  m = trackP4.M();
  energy = trackP4.E();
}

void lldjNtuple::deltaVertex2D(GlobalPoint secVert, std::vector<reco::TransientTrack> tracks, double& dPhi, double& pt, double& mediandPhi)
{

  //edm::Handle<reco::BeamSpot> beamspotHandle_;//make this global??? BENTODO
  //e.getByToken(beamspotLabel_, beamspotHandle_);

  const reco::BeamSpot& pat_beamspot = (*beamspotHandle_);
  TVector2 bmspot(pat_beamspot.x0(),pat_beamspot.y0());
  TVector2 sv(secVert.x(),secVert.y());
  TVector2 diff = (sv-bmspot);
  TVector2 trackPt(0,0);
  vector<double> trackAngles;
  for(int i = 0; i < (int)tracks.size(); i++){
    TVector2 tt;
    tt.SetMagPhi(tracks[i].trajectoryStateClosestToPoint(secVert).momentum().transverse(),tracks[i].trajectoryStateClosestToPoint(secVert).momentum().phi());
    trackPt += tt;
    trackAngles.push_back(fabs(diff.DeltaPhi(tt)));
  }
  sort(trackAngles.begin(), trackAngles.end());

  if(trackAngles.size() == 0){
    //do nothing
  }else if((trackAngles.size()%2 == 0)){
    mediandPhi = trackAngles.at(trackAngles.size()/2-1);
  }else{
    mediandPhi = trackAngles.at((trackAngles.size()-1)/2);
  }

  dPhi = diff.DeltaPhi(trackPt);
  pt = (trackPt - ((trackPt * diff)/(diff * diff) * diff)).Mod();

}


vector<reco::TransientTrack> lldjNtuple::cleanTracks(vector<reco::TransientTrack> tracks, GlobalPoint vertPos)
{
  vector<reco::TransientTrack> cleanTracks;
  for(int i = 0; i < (int)tracks.size(); i++){
    if(tracks[i].trajectoryStateClosestToPoint(vertPos).perigeeError().transverseImpactParameterError() > 0 && tracks[i].trajectoryStateClosestToPoint(vertPos).perigeeParameters().transverseImpactParameter() / tracks[i].trajectoryStateClosestToPoint(vertPos).perigeeError().transverseImpactParameterError() > 3.0)continue;
    cleanTracks.push_back(tracks[i]);
  }
  return cleanTracks;
}


void lldjNtuple::aod_jet_track_calculations(const edm::Event& e, const edm::EventSetup& es, 
					    float jeteta, float jetphi,  std::vector<int> whichVertex_, 
					    bool& fill_tracksIPLog10Sig_median, float &tracksIPLog10Sig_median, 
					    bool& fill_trackAngles_median, float &trackAngles_median, 
					    float& sumIP, float& sumIPSig, float &totalTrackAngle,
					    std::vector<reco::TransientTrack>& transientTracks, std::vector<int>& vertexVector
					    ){
  const double minTrackPt_ = 1.0;
  const double maxDRtrackJet_ = 0.4;
  
  //edm::Handle<reco::BeamSpot> beamspotHandle_;
  //e.getByToken(beamspotLabel_, beamspotHandle_);

  //slow to do this for every jet??
  std::string thePropagatorName_ = "PropagatorWithMaterial";
  es.get<TrackingComponentsRecord>().get(thePropagatorName_,thePropagator_);
  StateOnTrackerBound stateOnTracker(thePropagator_.product());

  float sumIPPt = 0;
  float sumIPLogSig = 0;
  float IVFScore = 0; 
  int nTracksIPlt0p05 = 0;
  int nTracksIPSiggt10 = 0;
  int nTracksIPSiglt5 = 0;
  
  map<reco::TransientTrack,reco::TrackBaseRef> refMap;
  vector<TrajectoryStateOnSurface> tsosList;
  vector<float> tracksIPLogSig;
  vector<float> tracksIPLog10Sig;
  vector<float> trackAngles;
  
  double totalTrackPt = 0;
  double totalTrackAnglePt = 0;
  double minR = 10000;
  //double minPt = 0; //unused
  
  TLorentzVector sumVector(0,0,0,0);
  vector<TLorentzVector> trackVectors;
  
  int nMissingInner = 0;
  int nMissingOuter = 0;

  for(int j = 0; j < (int)AODTrackHandle->size(); j++){

    reco::TrackBaseRef tref(AODTrackHandle,j);
    if (tref->pt() < minTrackPt_)continue;  // minimum pT for track
    if (!tref->quality(reco::TrackBase::highPurity)) continue; // track must be highPurity
    FreeTrajectoryState fts = trajectoryStateTransform::initialFreeState(AODTrackHandle->at(j),magneticField_);
    TrajectoryStateOnSurface outer = stateOnTracker(fts);
    if(!outer.isValid())continue;
    GlobalPoint outerPos = outer.globalPosition();
    TVector3 trackPos(outerPos.x(),outerPos.y(),outerPos.z());

    //Old DR
    //float tracketa = tref->eta();
    //float trackphi = tref->phi();
    //if(verbose_AOD) printf(" jeteta, jetphi, tracketa, trackphi %f %f %f %f dr %f \n",jeteta, jetphi, tracketa, trackphi, deltaR( jeteta, jetphi, tracketa, trackphi));
    //if ( deltaR( jeteta, jetphi, tracketa, trackphi ) > maxDRtrackJet_ ) continue; // match track to jet (different from rutgers!)
    //if(verbose_AOD) printf("  found a track - \n");
    
    //Rutgers DR
    double drt = deltaR( jeteta, jetphi, trackPos.Eta(), trackPos.Phi() );
    if(drt > maxDRtrackJet_) continue; 
    //if(trackToCaloJetMap_[j] < 0) trackToCaloJetMap_[j] = 0; //not used
    if(drt < minR){
      minR = drt;
      //minPt = tref->pt();
    }
    reco::TransientTrack tt(AODTrackHandle->at(j),magneticField_);
    if(!tt.isValid())continue;
    transientTracks.push_back(tt);
    vertexVector.push_back(whichVertex_[j]);
    
    nMissingInner += tref->hitPattern().numberOfLostTrackerHits(reco::HitPattern::MISSING_INNER_HITS);
    nMissingOuter += tref->hitPattern().numberOfLostTrackerHits(reco::HitPattern::MISSING_OUTER_HITS);

    static GetTrackTrajInfo getTrackTrajInfo; 
    vector<GetTrackTrajInfo::Result> trajInfo = getTrackTrajInfo.analyze(es, (*tref));
    if ( trajInfo.size() > 0 && trajInfo[0].valid) {
      const TrajectoryStateOnSurface& tsosInnerHit = trajInfo[0].detTSOS;
      double ta = fabs(trackAngle(e, tt,tsosInnerHit));
      totalTrackAngle += ta;
      totalTrackAnglePt += ta*tref->pt();
      totalTrackPt += tref->pt();
      trackAngles.push_back(log10(ta));
      tsosList.push_back(tsosInnerHit);
    }
    double dxy = fabs(tref->dxy(*beamspotHandle_));
    double dxyerr = tref->dxyError();
    double dxySig = 0;
    if (dxyerr > 0)dxySig = dxy/dxyerr;
    sumIP += dxy;
    sumIPPt += dxy * AODTrackHandle->at(j).pt();
    sumIPSig += dxySig;
    sumIPLogSig += log(dxySig);
    tracksIPLogSig.push_back(log(dxySig));
    tracksIPLog10Sig.push_back(log10(dxySig));
    IVFScore += 1.0/drt;
    nTracksIPlt0p05 += dxy < 0.05 ? 1 : 0;
    nTracksIPSiggt10 += dxySig > 10.0 ? 1 : 0;
    nTracksIPSiglt5 += dxySig < 5.0 ? 1 : 0;
    
  }//end track loop
  sort(tracksIPLogSig.begin(), tracksIPLogSig.end());
  sort(tracksIPLog10Sig.begin(), tracksIPLog10Sig.end());
  sort(trackAngles.begin(), trackAngles.end());
  
  //Medians
  if(tracksIPLog10Sig.size() == 0){
    fill_tracksIPLog10Sig_median = false;
  }else if((tracksIPLog10Sig.size()%2 == 0)){
    tracksIPLog10Sig_median = (tracksIPLog10Sig.at(tracksIPLog10Sig.size()/2-1)+tracksIPLog10Sig.at((tracksIPLog10Sig.size()/2)))/2 ;
  }else{
    tracksIPLog10Sig_median = tracksIPLog10Sig.at((tracksIPLog10Sig.size()-1)/2);
  }
  if(trackAngles.size() == 0){
    fill_trackAngles_median = false;
  }else if(trackAngles.size() % 2 == 0){
    trackAngles_median = trackAngles.at(trackAngles.size()/2 - 1);
  }else{
    trackAngles_median = trackAngles.at((trackAngles.size() - 1)/2);
  }
  
}

void lldjNtuple::calculateAlphaMax(vector<reco::TransientTrack>tracks, vector<int> whichVertex, double& aMax, double& aMaxP, double& beta, double& aMax2, double& aMaxP2, double& beta2)
{
  double total = 0; 
  double total2 = 0; 
  double promptTotal = 0; 
  double promptTotal2 = 0; 
  vector<double> alphas(AODVertexHandle->size(),0);
  vector<double> alphas2(AODVertexHandle->size(),0);

  //printf("(int)tracks.size() %i\n", (int)tracks.size() );
  for(int i = 0; i < (int)tracks.size(); i++){
    double pt = tracks[i].initialFreeState().momentum().transverse();
    total += pt;
    total2 += pt*pt;
    //printf("trackpt = %f\n",pt);
    if(whichVertex[i] < 0)continue;
    //printf(" we have a whichVertex\n");
    promptTotal += pt;
    promptTotal2 += pt*pt;
    alphas[whichVertex[i]] += pt;
    alphas2[whichVertex[i]] += pt*pt;
  }
  
  //for(int i = 0; i < (int)alphas.size(); i++){
  //  printf("alpha[%i] = %f \n",i,alphas[i]);
  //}


  double alphaMax = 0; 
  double alphaMax2 = 0; 
  double apMax =0;
  double apMax2 = 0; 
  beta = 1.0 - promptTotal/total;
  beta2 = 1.0 - promptTotal2 / total2;
  for(int i = 0; i < (int)alphas.size(); i++){
    if(alphas[i] > alphaMax) alphaMax = alphas[i];
    if(alphas2[i] > alphaMax2) alphaMax2 = alphas2[i];
    double ap = alphas[i] / (alphas[i] + beta);
    double ap2 = alphas2[i] / (alphas2[i] + beta2);
    if(ap > apMax) apMax = ap;
    if(ap2 > apMax2) apMax2 = ap2; 
  }
  aMax = alphaMax / total;
  aMax2 = alphaMax2 / total2;
  aMaxP = apMax;
  aMaxP2 = apMax2;
  return;
}


double lldjNtuple::trackAngle(const edm::Event& e, reco::TransientTrack track, TrajectoryStateOnSurface tsosInnerHit)
{
  
  //edm::Handle<reco::BeamSpot> beamspotHandle_;
  //e.getByToken(beamspotLabel_, beamspotHandle_);

  const reco::BeamSpot& pat_beamspot = (*beamspotHandle_);
  TVector2 bmspot(pat_beamspot.x0(),pat_beamspot.y0());
  GlobalPoint   innerPos  = tsosInnerHit.globalPosition();
  GlobalVector innerMom = tsosInnerHit.globalMomentum();
  TVector2 sv(innerPos.x(),innerPos.y());
  TVector2 diff = (sv-bmspot);
  //cout<<"bs x: "<<bmspot.X()<<" y: "<<bmspot.Y()<<endl;
  //cout<<" sv x: "<<sv.X()<<" y: "<<sv.Y()<<endl;
  //cout<<" diff phi: "<<diff.Phi()<<endl;
  TVector2 momentum(innerMom.x(),innerMom.y());
  //cout<<" p x: "<<momentum.X()<<" y: "<<momentum.Y()<<endl;
  //cout<<" p phi: "<<momentum.Phi()<<endl;
  //cout<<" dPhi: "<<diff.DeltaPhi(momentum)<<endl;
  return diff.DeltaPhi(momentum);
}
