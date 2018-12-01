#include "analyzer_base.h"

//----------------------------analyzer_base
analyzer_base::analyzer_base() 
{
}

//----------------------------~analyzer_base
analyzer_base::~analyzer_base()
{
}

//----------------------------LoadTree
Long64_t analyzer_base::LoadTree(Long64_t entry)
{
 // Set the environment to read one entry
 if (!fChain) return -5;
 Long64_t centry = fChain->LoadTree(entry);
 if (centry < 0) return centry;
 if (fChain->GetTreeNumber() != fCurrent) {
  fCurrent = fChain->GetTreeNumber();
 }
 return centry;
}

//----------------------------Init
void analyzer_base::Init(TChain *tree, Bool_t isitMC, Bool_t domakelog)
{

   isMC = isitMC;
   makelog = domakelog;

   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // MC and Data
   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // set object pointers
   llpId = 0;
   llpStatus = 0;
   llpPt = 0;
   llpEta = 0;
   llpPhi = 0;
   llpMass = 0;
   llpDaughterId = 0;
   llpDaughterStatus = 0;
   llpDaughterPt = 0;
   llpDaughterEta = 0;
   llpDaughterPhi = 0;
   llpDaughterMass = 0;
   toppts = 0;
   AODPATJetPartonFlavour = 0;
   AODPATJetPt = 0;
   AODPATJetEta = 0;
   AODPATJetPhi = 0;
   AODPATJetCSV = 0;
   AODPATJetMVA = 0;
   AODCaloJetPt = 0;
   AODCaloJetEta = 0;
   AODCaloJetPhi = 0;
   AODCaloJetAlphaMax = 0;
   AODCaloJetAlphaMax2 = 0;
   AODCaloJetAlphaMaxPrime = 0;
   AODCaloJetAlphaMaxPrime2 = 0;
   AODCaloJetBeta = 0;
   AODCaloJetBeta2 = 0;
   AODCaloJetSumIP = 0;
   AODCaloJetSumIPSig = 0;
   AODCaloJetMedianIP = 0;
   AODCaloJetMedianLog10IPSig = 0;
   AODCaloJetTrackAngle = 0;
   AODCaloJetLogTrackAngle = 0;
   AODCaloJetMedianLog10TrackAngle = 0;
   AODCaloJetTotalTrackAngle = 0;
   AODCaloJetAvfVx = 0;
   AODCaloJetAvfVy = 0;
   AODCaloJetAvfVz = 0;
   AODCaloJetAvfVertexTotalChiSquared = 0;
   AODCaloJetAvfVertexDegreesOfFreedom = 0;
   AODCaloJetAvfVertexChi2NDoF = 0;
   AODCaloJetAvfVertexDistanceToBeam = 0;
   AODCaloJetAvfVertexTransverseError = 0;
   AODCaloJetAvfVertexTransverseSig = 0;
   AODCaloJetAvfVertexDeltaEta = 0;
   AODCaloJetAvfVertexDeltaPhi = 0;
   AODCaloJetAvfVertexRecoilPt = 0;
   AODCaloJetAvfVertexTrackMass = 0;
   AODCaloJetAvfVertexTrackEnergy = 0;
   AODCaloJetAvfBeamSpotDeltaPhi = 0;
   AODCaloJetAvfBeamSpotRecoilPt = 0;
   AODCaloJetAvfBeamSpotMedianDeltaPhi = 0;
   AODCaloJetAvfBeamSpotLog10MedianDeltaPhi = 0;
   AODCaloJetNCleanMatchedTracks = 0;
   AODCaloJetNMatchedTracks = 0;
   AODCaloJetSumHitsInFrontOfVert = 0;
   AODCaloJetSumMissHitsAfterVert = 0;
   AODCaloJetHitsInFrontOfVertPerTrack = 0;
   AODCaloJetMissHitsAfterVertPerTrack = 0;
   AODCaloJetAvfDistToPV = 0;
   AODCaloJetAvfVertexDeltaZtoPV = 0;
   AODCaloJetAvfVertexDeltaZtoPV2 = 0;
   AODPFJetID = 0;
   AODPFJetPt = 0;
   AODPFJetEta = 0;
   AODPFJetPhi = 0;
   AODPFJetAlphaMax = 0;
   AODPFJetAlphaMax2 = 0;
   AODPFJetAlphaMaxPrime = 0;
   AODPFJetAlphaMaxPrime2 = 0;
   AODPFJetBeta = 0;
   AODPFJetBeta2 = 0;
   AODPFJetSumIP = 0;
   AODPFJetSumIPSig = 0;
   AODPFJetMedianIP = 0;
   AODPFJetMedianLog10IPSig = 0;
   AODPFJetTrackAngle = 0;
   AODPFJetLogTrackAngle = 0;
   AODPFJetMedianLog10TrackAngle = 0;
   AODPFJetTotalTrackAngle = 0;
   AODPFchsJetID = 0;
   AODPFchsJetPt = 0;
   AODPFchsJetEta = 0;
   AODPFchsJetPhi = 0;
   AODPFchsJetAlphaMax = 0;
   AODPFchsJetAlphaMax2 = 0;
   AODPFchsJetAlphaMaxPrime = 0;
   AODPFchsJetAlphaMaxPrime2 = 0;
   AODPFchsJetBeta = 0;
   AODPFchsJetBeta2 = 0;
   AODPFchsJetSumIP = 0;
   AODPFchsJetSumIPSig = 0;
   AODPFchsJetMedianIP = 0;
   AODPFchsJetMedianLog10IPSig = 0;
   AODPFchsJetTrackAngle = 0;
   AODPFchsJetLogTrackAngle = 0;
   AODPFchsJetMedianLog10TrackAngle = 0;
   AODPFchsJetTotalTrackAngle = 0;
   AOD_muPt = 0;
   AOD_muEn = 0;
   AOD_muEta = 0;
   AOD_muPhi = 0;
   AOD_muCharge = 0;
   AOD_muType = 0;
   AOD_muIsGlobalMuon = 0;
   AOD_muIsPFMuon = 0;
   AOD_muPassLooseID = 0;
   AOD_muPassMediumBCDEFID = 0;
   AOD_muPassMediumGHID = 0;
   AOD_muPassTightID = 0;
   AOD_muPFdBetaIsolation = 0;
   AOD_muDxy = 0;
   AOD_muDxyErr = 0;
   AOD_muDB_BS2D = 0;
   AOD_muDB_PV2D = 0;
   AOD_phoPt = 0;
   AOD_phoEn = 0;
   AOD_phoEta = 0;
   AOD_phoPhi = 0;
   AOD_phoSCEn = 0;
   AOD_phoSCEta = 0;
   AOD_phoSCPhi = 0;
   AOD_phoPassElectronVeto = 0;
   AOD_phoHasPixelSeed = 0;
   AOD_phoIDbit = 0;
   AOD_phoObjPFChIso = 0;
   AOD_phoObjPFPhoIso = 0;
   AOD_phoObjPFNeuIso = 0;
   AOD_phoObjPFChWorstIso = 0;
   AOD_phoMapPFChIso = 0;
   AOD_phoMapPFPhoIso = 0;
   AOD_phoMapPFNeuIso = 0;
   AOD_phoMapPFChWorstIso = 0;
   AOD_elePt = 0;
   AOD_eleEn = 0;
   AOD_eleEta = 0;
   AOD_elePhi = 0;
   AOD_eleCharge = 0;
   AOD_eleChargeConsistent = 0;
   AOD_eleIDbit = 0;
   AOD_elePassConversionVeto = 0;
   AOD_eled0 = 0;
   AOD_eledz = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("AODnTruePU", &AODnTruePU, &b_AODnTruePU);
   fChain->SetBranchAddress("AODnVtx", &AODnVtx, &b_AODnVtx);
   fChain->SetBranchAddress("AODnGoodVtx", &AODnGoodVtx, &b_AODnGoodVtx);
   fChain->SetBranchAddress("AODnTrksPV", &AODnTrksPV, &b_AODnTrksPV);
   fChain->SetBranchAddress("AODisPVGood", &AODisPVGood, &b_AODisPVGood);
   fChain->SetBranchAddress("llpId", &llpId, &b_llpId);
   fChain->SetBranchAddress("llpStatus", &llpStatus, &b_llpStatus);
   fChain->SetBranchAddress("llpPt", &llpPt, &b_llpPt);
   fChain->SetBranchAddress("llpEta", &llpEta, &b_llpEta);
   fChain->SetBranchAddress("llpPhi", &llpPhi, &b_llpPhi);
   fChain->SetBranchAddress("llpMass", &llpMass, &b_llpMass);
   fChain->SetBranchAddress("llpDaughterId", &llpDaughterId, &b_llpDaughterId);
   fChain->SetBranchAddress("llpDaughterStatus", &llpDaughterStatus, &b_llpDaughterStatus);
   fChain->SetBranchAddress("llpDaughterPt", &llpDaughterPt, &b_llpDaughterPt);
   fChain->SetBranchAddress("llpDaughterEta", &llpDaughterEta, &b_llpDaughterEta);
   fChain->SetBranchAddress("llpDaughterPhi", &llpDaughterPhi, &b_llpDaughterPhi);
   fChain->SetBranchAddress("llpDaughterMass", &llpDaughterMass, &b_llpDaughterMass);
   fChain->SetBranchAddress("toppts", &toppts, &b_toppts);
   //single ele
   fChain->SetBranchAddress("AOD_HLT_Ele23Loose", &AOD_HLT_Ele23Loose, &b_AOD_HLT_Ele23Loose);
   fChain->SetBranchAddress("AOD_HLT_Ele27Tight", &AOD_HLT_Ele27Tight, &b_AOD_HLT_Ele27Tight);
   fChain->SetBranchAddress("AOD_HLT_Ele23Loose_isPS", &AOD_HLT_Ele23Loose_isPS, &b_AOD_HLT_Ele23Loose_isPS);
   fChain->SetBranchAddress("AOD_HLT_Ele27Tight_isPS", &AOD_HLT_Ele27Tight_isPS, &b_AOD_HLT_Ele27Tight_isPS);
   //ele ele
   fChain->SetBranchAddress("AOD_HLT_Ele17Ele12", &AOD_HLT_Ele17Ele12, &b_AOD_HLT_Ele17Ele12);
   fChain->SetBranchAddress("AOD_HLT_Ele23Ele12", &AOD_HLT_Ele23Ele12, &b_AOD_HLT_Ele23Ele12);
   fChain->SetBranchAddress("AOD_HLT_Ele17Ele12_isPS", &AOD_HLT_Ele17Ele12_isPS, &b_AOD_HLT_Ele17Ele12_isPS);
   fChain->SetBranchAddress("AOD_HLT_Ele23Ele12_isPS", &AOD_HLT_Ele23Ele12_isPS, &b_AOD_HLT_Ele23Ele12_isPS);
   //single mu
   fChain->SetBranchAddress("AOD_HLT_IsoMu22", &AOD_HLT_IsoMu22, &b_AOD_HLT_IsoMu22);
   fChain->SetBranchAddress("AOD_HLT_IsoTkMu22", &AOD_HLT_IsoTkMu22, &b_AOD_HLT_IsoTkMu22);
   fChain->SetBranchAddress("AOD_HLT_IsoMu24", &AOD_HLT_IsoMu24, &b_AOD_HLT_IsoMu24);
   fChain->SetBranchAddress("AOD_HLT_IsoTkMu24", &AOD_HLT_IsoTkMu24, &b_AOD_HLT_IsoTkMu24);
   fChain->SetBranchAddress("AOD_HLT_IsoMu22_isPS", &AOD_HLT_IsoMu22_isPS, &b_AOD_HLT_IsoMu22_isPS);
   fChain->SetBranchAddress("AOD_HLT_IsoTkMu22_isPS", &AOD_HLT_IsoTkMu22_isPS, &b_AOD_HLT_IsoTkMu22_isPS);
   fChain->SetBranchAddress("AOD_HLT_IsoMu24_isPS", &AOD_HLT_IsoMu24_isPS, &b_AOD_HLT_IsoMu24_isPS);
   fChain->SetBranchAddress("AOD_HLT_IsoTkMu24_isPS", &AOD_HLT_IsoTkMu24_isPS, &b_AOD_HLT_IsoTkMu24_isPS);
   //mu mu
   fChain->SetBranchAddress("AOD_HLT_Mu17Mu8", &AOD_HLT_Mu17Mu8, &b_AOD_HLT_Mu17Mu8);
   fChain->SetBranchAddress("AOD_HLT_Mu17TkMu8", &AOD_HLT_Mu17TkMu8, &b_AOD_HLT_Mu17TkMu8);
   fChain->SetBranchAddress("AOD_HLT_Mu17Mu8_noDZ", &AOD_HLT_Mu17Mu8_noDZ, &b_AOD_HLT_Mu17Mu8_noDZ);
   fChain->SetBranchAddress("AOD_HLT_Mu17TkMu8_noDZ", &AOD_HLT_Mu17TkMu8_noDZ, &b_AOD_HLT_Mu17TkMu8_noDZ);
   fChain->SetBranchAddress("AOD_HLT_Mu17Mu8_isPS", &AOD_HLT_Mu17Mu8_isPS, &b_AOD_HLT_Mu17Mu8_isPS);
   fChain->SetBranchAddress("AOD_HLT_Mu17TkMu8_isPS", &AOD_HLT_Mu17TkMu8_isPS, &b_AOD_HLT_Mu17TkMu8_isPS);
   fChain->SetBranchAddress("AOD_HLT_Mu17Mu8_noDZ_isPS", &AOD_HLT_Mu17Mu8_noDZ_isPS, &b_AOD_HLT_Mu17Mu8_noDZ_isPS);
   fChain->SetBranchAddress("AOD_HLT_Mu17TkMu8_noDZ_isPS", &AOD_HLT_Mu17TkMu8_noDZ_isPS, &b_AOD_HLT_Mu17TkMu8_noDZ_isPS);
   //mu ele
   fChain->SetBranchAddress("AOD_HLT_Mu8Ele23", &AOD_HLT_Mu8Ele23, &b_AOD_HLT_Mu8Ele23);
   fChain->SetBranchAddress("AOD_HLT_Mu23Ele12", &AOD_HLT_Mu23Ele12, &b_AOD_HLT_Mu23Ele12);
   fChain->SetBranchAddress("AOD_HLT_Mu12Ele23_DZ", &AOD_HLT_Mu12Ele23_DZ, &b_AOD_HLT_Mu12Ele23_DZ);
   fChain->SetBranchAddress("AOD_HLT_Mu23Ele12_DZ", &AOD_HLT_Mu23Ele12_DZ, &b_AOD_HLT_Mu23Ele12_DZ);
   fChain->SetBranchAddress("AOD_HLT_Mu8Ele23_isPS", &AOD_HLT_Mu8Ele23_isPS, &b_AOD_HLT_Mu8Ele23_isPS);
   fChain->SetBranchAddress("AOD_HLT_Mu23Ele12_isPS", &AOD_HLT_Mu23Ele12_isPS, &b_AOD_HLT_Mu23Ele12_isPS);
   fChain->SetBranchAddress("AOD_HLT_Mu12Ele23_DZ_isPS", &AOD_HLT_Mu12Ele23_DZ_isPS, &b_AOD_HLT_Mu12Ele23_DZ_isPS);
   fChain->SetBranchAddress("AOD_HLT_Mu23Ele12_DZ_isPS", &AOD_HLT_Mu23Ele12_DZ_isPS, &b_AOD_HLT_Mu23Ele12_DZ_isPS);
   //photon
   fChain->SetBranchAddress("AOD_HLT_Photon90", &AOD_HLT_Photon90, &b_AOD_HLT_Photon90);
   fChain->SetBranchAddress("AOD_HLT_Photon120", &AOD_HLT_Photon120, &b_AOD_HLT_Photon120);
   fChain->SetBranchAddress("AOD_HLT_Photon175", &AOD_HLT_Photon175, &b_AOD_HLT_Photon175);
   fChain->SetBranchAddress("AOD_HLT_Photon165_HE10", &AOD_HLT_Photon165_HE10, &b_AOD_HLT_Photon165_HE10);
   fChain->SetBranchAddress("AOD_HLT_Photon90_isPS", &AOD_HLT_Photon90_isPS, &b_AOD_HLT_Photon90_isPS);
   fChain->SetBranchAddress("AOD_HLT_Photon120_isPS", &AOD_HLT_Photon120_isPS, &b_AOD_HLT_Photon120_isPS);
   fChain->SetBranchAddress("AOD_HLT_Photon175_isPS", &AOD_HLT_Photon175_isPS, &b_AOD_HLT_Photon175_isPS);
   fChain->SetBranchAddress("AOD_HLT_Photon165_HE10_isPS", &AOD_HLT_Photon165_HE10_isPS, &b_AOD_HLT_Photon165_HE10_isPS);
   //
   fChain->SetBranchAddress("AODnPATJet", &AODnPATJet, &b_AODnPATJet);
   fChain->SetBranchAddress("AODPATJetPartonFlavour", &AODPATJetPartonFlavour, &b_AODPATJetPartonFlavour);
   fChain->SetBranchAddress("AODPATJetPt", &AODPATJetPt, &b_AODPATJetPt);
   fChain->SetBranchAddress("AODPATJetEta", &AODPATJetEta, &b_AODPATJetEta);
   fChain->SetBranchAddress("AODPATJetPhi", &AODPATJetPhi, &b_AODPATJetPhi);
   fChain->SetBranchAddress("AODPATJetCSV", &AODPATJetCSV, &b_AODPATJetCSV);
   fChain->SetBranchAddress("AODPATJetMVA", &AODPATJetMVA, &b_AODPATJetMVA);
   fChain->SetBranchAddress("AODnCaloJet", &AODnCaloJet, &b_AODnCaloJet);
   fChain->SetBranchAddress("AODCaloJetPt", &AODCaloJetPt, &b_AODCaloJetPt);
   fChain->SetBranchAddress("AODCaloJetEta", &AODCaloJetEta, &b_AODCaloJetEta);
   fChain->SetBranchAddress("AODCaloJetPhi", &AODCaloJetPhi, &b_AODCaloJetPhi);
   fChain->SetBranchAddress("AODCaloJetAlphaMax", &AODCaloJetAlphaMax, &b_AODCaloJetAlphaMax);
   fChain->SetBranchAddress("AODCaloJetAlphaMax2", &AODCaloJetAlphaMax2, &b_AODCaloJetAlphaMax2);
   fChain->SetBranchAddress("AODCaloJetAlphaMaxPrime", &AODCaloJetAlphaMaxPrime, &b_AODCaloJetAlphaMaxPrime);
   fChain->SetBranchAddress("AODCaloJetAlphaMaxPrime2", &AODCaloJetAlphaMaxPrime2, &b_AODCaloJetAlphaMaxPrime2);
   fChain->SetBranchAddress("AODCaloJetBeta", &AODCaloJetBeta, &b_AODCaloJetBeta);
   fChain->SetBranchAddress("AODCaloJetBeta2", &AODCaloJetBeta2, &b_AODCaloJetBeta2);
   fChain->SetBranchAddress("AODCaloJetSumIP", &AODCaloJetSumIP, &b_AODCaloJetSumIP);
   fChain->SetBranchAddress("AODCaloJetSumIPSig", &AODCaloJetSumIPSig, &b_AODCaloJetSumIPSig);
   fChain->SetBranchAddress("AODCaloJetMedianIP", &AODCaloJetMedianIP, &b_AODCaloJetMedianIP);
   fChain->SetBranchAddress("AODCaloJetMedianLog10IPSig", &AODCaloJetMedianLog10IPSig, &b_AODCaloJetMedianLog10IPSig);
   fChain->SetBranchAddress("AODCaloJetTrackAngle", &AODCaloJetTrackAngle, &b_AODCaloJetTrackAngle);
   fChain->SetBranchAddress("AODCaloJetLogTrackAngle", &AODCaloJetLogTrackAngle, &b_AODCaloJetLogTrackAngle);
   fChain->SetBranchAddress("AODCaloJetMedianLog10TrackAngle", &AODCaloJetMedianLog10TrackAngle, &b_AODCaloJetMedianLog10TrackAngle);
   fChain->SetBranchAddress("AODCaloJetTotalTrackAngle", &AODCaloJetTotalTrackAngle, &b_AODCaloJetTotalTrackAngle);
   fChain->SetBranchAddress("AODCaloJetAvfVx", &AODCaloJetAvfVx, &b_AODCaloJetAvfVx);
   fChain->SetBranchAddress("AODCaloJetAvfVy", &AODCaloJetAvfVy, &b_AODCaloJetAvfVy);
   fChain->SetBranchAddress("AODCaloJetAvfVz", &AODCaloJetAvfVz, &b_AODCaloJetAvfVz);
   fChain->SetBranchAddress("AODCaloJetAvfVertexTotalChiSquared", &AODCaloJetAvfVertexTotalChiSquared, &b_AODCaloJetAvfVertexTotalChiSquared);
   fChain->SetBranchAddress("AODCaloJetAvfVertexDegreesOfFreedom", &AODCaloJetAvfVertexDegreesOfFreedom, &b_AODCaloJetAvfVertexDegreesOfFreedom);
   fChain->SetBranchAddress("AODCaloJetAvfVertexChi2NDoF", &AODCaloJetAvfVertexChi2NDoF, &b_AODCaloJetAvfVertexChi2NDoF);
   fChain->SetBranchAddress("AODCaloJetAvfVertexDistanceToBeam", &AODCaloJetAvfVertexDistanceToBeam, &b_AODCaloJetAvfVertexDistanceToBeam);
   fChain->SetBranchAddress("AODCaloJetAvfVertexTransverseError", &AODCaloJetAvfVertexTransverseError, &b_AODCaloJetAvfVertexTransverseError);
   fChain->SetBranchAddress("AODCaloJetAvfVertexTransverseSig", &AODCaloJetAvfVertexTransverseSig, &b_AODCaloJetAvfVertexTransverseSig);
   fChain->SetBranchAddress("AODCaloJetAvfVertexDeltaEta", &AODCaloJetAvfVertexDeltaEta, &b_AODCaloJetAvfVertexDeltaEta);
   fChain->SetBranchAddress("AODCaloJetAvfVertexDeltaPhi", &AODCaloJetAvfVertexDeltaPhi, &b_AODCaloJetAvfVertexDeltaPhi);
   fChain->SetBranchAddress("AODCaloJetAvfVertexRecoilPt", &AODCaloJetAvfVertexRecoilPt, &b_AODCaloJetAvfVertexRecoilPt);
   fChain->SetBranchAddress("AODCaloJetAvfVertexTrackMass", &AODCaloJetAvfVertexTrackMass, &b_AODCaloJetAvfVertexTrackMass);
   fChain->SetBranchAddress("AODCaloJetAvfVertexTrackEnergy", &AODCaloJetAvfVertexTrackEnergy, &b_AODCaloJetAvfVertexTrackEnergy);
   fChain->SetBranchAddress("AODCaloJetAvfBeamSpotDeltaPhi", &AODCaloJetAvfBeamSpotDeltaPhi, &b_AODCaloJetAvfBeamSpotDeltaPhi);
   fChain->SetBranchAddress("AODCaloJetAvfBeamSpotRecoilPt", &AODCaloJetAvfBeamSpotRecoilPt, &b_AODCaloJetAvfBeamSpotRecoilPt);
   fChain->SetBranchAddress("AODCaloJetAvfBeamSpotMedianDeltaPhi", &AODCaloJetAvfBeamSpotMedianDeltaPhi, &b_AODCaloJetAvfBeamSpotMedianDeltaPhi);
   fChain->SetBranchAddress("AODCaloJetAvfBeamSpotLog10MedianDeltaPhi", &AODCaloJetAvfBeamSpotLog10MedianDeltaPhi, &b_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi);
   fChain->SetBranchAddress("AODCaloJetNCleanMatchedTracks", &AODCaloJetNCleanMatchedTracks, &b_AODCaloJetNCleanMatchedTracks);
   fChain->SetBranchAddress("AODCaloJetNMatchedTracks", &AODCaloJetNMatchedTracks, &b_AODCaloJetNMatchedTracks);
   fChain->SetBranchAddress("AODCaloJetSumHitsInFrontOfVert", &AODCaloJetSumHitsInFrontOfVert, &b_AODCaloJetSumHitsInFrontOfVert);
   fChain->SetBranchAddress("AODCaloJetSumMissHitsAfterVert", &AODCaloJetSumMissHitsAfterVert, &b_AODCaloJetSumMissHitsAfterVert);
   fChain->SetBranchAddress("AODCaloJetHitsInFrontOfVertPerTrack", &AODCaloJetHitsInFrontOfVertPerTrack, &b_AODCaloJetHitsInFrontOfVertPerTrack);
   fChain->SetBranchAddress("AODCaloJetMissHitsAfterVertPerTrack", &AODCaloJetMissHitsAfterVertPerTrack, &b_AODCaloJetMissHitsAfterVertPerTrack);
   fChain->SetBranchAddress("AODCaloJetAvfDistToPV", &AODCaloJetAvfDistToPV, &b_AODCaloJetAvfDistToPV);
   fChain->SetBranchAddress("AODCaloJetAvfVertexDeltaZtoPV", &AODCaloJetAvfVertexDeltaZtoPV, &b_AODCaloJetAvfVertexDeltaZtoPV);
   fChain->SetBranchAddress("AODCaloJetAvfVertexDeltaZtoPV2", &AODCaloJetAvfVertexDeltaZtoPV2, &b_AODCaloJetAvfVertexDeltaZtoPV2);
   fChain->SetBranchAddress("AODnPFJet", &AODnPFJet, &b_AODnPFJet);
   fChain->SetBranchAddress("AODPFJetID", &AODPFJetID, &b_AODPFJetID);
   fChain->SetBranchAddress("AODPFJetPt", &AODPFJetPt, &b_AODPFJetPt);
   fChain->SetBranchAddress("AODPFJetEta", &AODPFJetEta, &b_AODPFJetEta);
   fChain->SetBranchAddress("AODPFJetPhi", &AODPFJetPhi, &b_AODPFJetPhi);
   fChain->SetBranchAddress("AODPFJetAlphaMax", &AODPFJetAlphaMax, &b_AODPFJetAlphaMax);
   fChain->SetBranchAddress("AODPFJetAlphaMax2", &AODPFJetAlphaMax2, &b_AODPFJetAlphaMax2);
   fChain->SetBranchAddress("AODPFJetAlphaMaxPrime", &AODPFJetAlphaMaxPrime, &b_AODPFJetAlphaMaxPrime);
   fChain->SetBranchAddress("AODPFJetAlphaMaxPrime2", &AODPFJetAlphaMaxPrime2, &b_AODPFJetAlphaMaxPrime2);
   fChain->SetBranchAddress("AODPFJetBeta", &AODPFJetBeta, &b_AODPFJetBeta);
   fChain->SetBranchAddress("AODPFJetBeta2", &AODPFJetBeta2, &b_AODPFJetBeta2);
   fChain->SetBranchAddress("AODPFJetSumIP", &AODPFJetSumIP, &b_AODPFJetSumIP);
   fChain->SetBranchAddress("AODPFJetSumIPSig", &AODPFJetSumIPSig, &b_AODPFJetSumIPSig);
   fChain->SetBranchAddress("AODPFJetMedianIP", &AODPFJetMedianIP, &b_AODPFJetMedianIP);
   fChain->SetBranchAddress("AODPFJetMedianLog10IPSig", &AODPFJetMedianLog10IPSig, &b_AODPFJetMedianLog10IPSig);
   fChain->SetBranchAddress("AODPFJetTrackAngle", &AODPFJetTrackAngle, &b_AODPFJetTrackAngle);
   fChain->SetBranchAddress("AODPFJetLogTrackAngle", &AODPFJetLogTrackAngle, &b_AODPFJetLogTrackAngle);
   fChain->SetBranchAddress("AODPFJetMedianLog10TrackAngle", &AODPFJetMedianLog10TrackAngle, &b_AODPFJetMedianLog10TrackAngle);
   fChain->SetBranchAddress("AODPFJetTotalTrackAngle", &AODPFJetTotalTrackAngle, &b_AODPFJetTotalTrackAngle);
   fChain->SetBranchAddress("AODnPFchsJet", &AODnPFchsJet, &b_AODnPFchsJet);
   fChain->SetBranchAddress("AODPFchsJetID", &AODPFchsJetID, &b_AODPFchsJetID);
   fChain->SetBranchAddress("AODPFchsJetPt", &AODPFchsJetPt, &b_AODPFchsJetPt);
   fChain->SetBranchAddress("AODPFchsJetEta", &AODPFchsJetEta, &b_AODPFchsJetEta);
   fChain->SetBranchAddress("AODPFchsJetPhi", &AODPFchsJetPhi, &b_AODPFchsJetPhi);
   fChain->SetBranchAddress("AODPFchsJetAlphaMax", &AODPFchsJetAlphaMax, &b_AODPFchsJetAlphaMax);
   fChain->SetBranchAddress("AODPFchsJetAlphaMax2", &AODPFchsJetAlphaMax2, &b_AODPFchsJetAlphaMax2);
   fChain->SetBranchAddress("AODPFchsJetAlphaMaxPrime", &AODPFchsJetAlphaMaxPrime, &b_AODPFchsJetAlphaMaxPrime);
   fChain->SetBranchAddress("AODPFchsJetAlphaMaxPrime2", &AODPFchsJetAlphaMaxPrime2, &b_AODPFchsJetAlphaMaxPrime2);
   fChain->SetBranchAddress("AODPFchsJetBeta", &AODPFchsJetBeta, &b_AODPFchsJetBeta);
   fChain->SetBranchAddress("AODPFchsJetBeta2", &AODPFchsJetBeta2, &b_AODPFchsJetBeta2);
   fChain->SetBranchAddress("AODPFchsJetSumIP", &AODPFchsJetSumIP, &b_AODPFchsJetSumIP);
   fChain->SetBranchAddress("AODPFchsJetSumIPSig", &AODPFchsJetSumIPSig, &b_AODPFchsJetSumIPSig);
   fChain->SetBranchAddress("AODPFchsJetMedianIP", &AODPFchsJetMedianIP, &b_AODPFchsJetMedianIP);
   fChain->SetBranchAddress("AODPFchsJetMedianLog10IPSig", &AODPFchsJetMedianLog10IPSig, &b_AODPFchsJetMedianLog10IPSig);
   fChain->SetBranchAddress("AODPFchsJetTrackAngle", &AODPFchsJetTrackAngle, &b_AODPFchsJetTrackAngle);
   fChain->SetBranchAddress("AODPFchsJetLogTrackAngle", &AODPFchsJetLogTrackAngle, &b_AODPFchsJetLogTrackAngle);
   fChain->SetBranchAddress("AODPFchsJetMedianLog10TrackAngle", &AODPFchsJetMedianLog10TrackAngle, &b_AODPFchsJetMedianLog10TrackAngle);
   fChain->SetBranchAddress("AODPFchsJetTotalTrackAngle", &AODPFchsJetTotalTrackAngle, &b_AODPFchsJetTotalTrackAngle);
   fChain->SetBranchAddress("nAODMu", &nAODMu, &b_nAODMu);
   fChain->SetBranchAddress("AOD_muPt", &AOD_muPt, &b_AOD_muPt);
   fChain->SetBranchAddress("AOD_muEn", &AOD_muEn, &b_AOD_muEn);
   fChain->SetBranchAddress("AOD_muEta", &AOD_muEta, &b_AOD_muEta);
   fChain->SetBranchAddress("AOD_muPhi", &AOD_muPhi, &b_AOD_muPhi);
   fChain->SetBranchAddress("AOD_muCharge", &AOD_muCharge, &b_AOD_muCharge);
   fChain->SetBranchAddress("AOD_muType", &AOD_muType, &b_AOD_muType);
   fChain->SetBranchAddress("AOD_muIsGlobalMuon", &AOD_muIsGlobalMuon, &b_AOD_muIsGlobalMuon);
   fChain->SetBranchAddress("AOD_muIsPFMuon", &AOD_muIsPFMuon, &b_AOD_muIsPFMuon);
   fChain->SetBranchAddress("AOD_muPassLooseID", &AOD_muPassLooseID, &b_AOD_muPassLooseID);
   fChain->SetBranchAddress("AOD_muPassMediumBCDEFID", &AOD_muPassMediumBCDEFID, &b_AOD_muPassMediumBCDEFID);
   fChain->SetBranchAddress("AOD_muPassMediumGHID", &AOD_muPassMediumGHID, &b_AOD_muPassMediumGHID);
   fChain->SetBranchAddress("AOD_muPassTightID", &AOD_muPassTightID, &b_AOD_muPassTightID);
   fChain->SetBranchAddress("AOD_muPFdBetaIsolation", &AOD_muPFdBetaIsolation, &b_AOD_muPFdBetaIsolation);
   fChain->SetBranchAddress("AOD_muDxy", &AOD_muDxy, &b_AOD_muDxy);
   fChain->SetBranchAddress("AOD_muDxyErr", &AOD_muDxyErr, &b_AOD_muDxyErr);
   fChain->SetBranchAddress("AOD_muDB_BS2D", &AOD_muDB_BS2D, &b_AOD_muDB_BS2D);
   fChain->SetBranchAddress("AOD_muDB_PV2D", &AOD_muDB_PV2D, &b_AOD_muDB_PV2D);
   fChain->SetBranchAddress("nAODPho", &nAODPho, &b_nAODPho);
   fChain->SetBranchAddress("AOD_phoPt", &AOD_phoPt, &b_AOD_phoPt);
   fChain->SetBranchAddress("AOD_phoEn", &AOD_phoEn, &b_AOD_phoEn);
   fChain->SetBranchAddress("AOD_phoEta", &AOD_phoEta, &b_AOD_phoEta);
   fChain->SetBranchAddress("AOD_phoPhi", &AOD_phoPhi, &b_AOD_phoPhi);
   fChain->SetBranchAddress("AOD_phoSCEn", &AOD_phoSCEn, &b_AOD_phoSCEn);
   fChain->SetBranchAddress("AOD_phoSCEta", &AOD_phoSCEta, &b_AOD_phoSCEta);
   fChain->SetBranchAddress("AOD_phoSCPhi", &AOD_phoSCPhi, &b_AOD_phoSCPhi);
   fChain->SetBranchAddress("AOD_phoPassElectronVeto", &AOD_phoPassElectronVeto, &b_AOD_phoPassElectronVeto);
   fChain->SetBranchAddress("AOD_phoHasPixelSeed", &AOD_phoHasPixelSeed, &b_AOD_phoHasPixelSeed);
   fChain->SetBranchAddress("AOD_phoIDbit", &AOD_phoIDbit, &b_AOD_phoIDbit);
   fChain->SetBranchAddress("AOD_phoObjPFChIso", &AOD_phoObjPFChIso, &b_AOD_phoObjPFChIso);
   fChain->SetBranchAddress("AOD_phoObjPFPhoIso", &AOD_phoObjPFPhoIso, &b_AOD_phoObjPFPhoIso);
   fChain->SetBranchAddress("AOD_phoObjPFNeuIso", &AOD_phoObjPFNeuIso, &b_AOD_phoObjPFNeuIso);
   fChain->SetBranchAddress("AOD_phoObjPFChWorstIso", &AOD_phoObjPFChWorstIso, &b_AOD_phoObjPFChWorstIso);
   fChain->SetBranchAddress("AOD_phoMapPFChIso", &AOD_phoMapPFChIso, &b_AOD_phoMapPFChIso);
   fChain->SetBranchAddress("AOD_phoMapPFPhoIso", &AOD_phoMapPFPhoIso, &b_AOD_phoMapPFPhoIso);
   fChain->SetBranchAddress("AOD_phoMapPFNeuIso", &AOD_phoMapPFNeuIso, &b_AOD_phoMapPFNeuIso);
   fChain->SetBranchAddress("AOD_phoMapPFChWorstIso", &AOD_phoMapPFChWorstIso, &b_AOD_phoMapPFChWorstIso);
   fChain->SetBranchAddress("nAODEle", &nAODEle, &b_nAODEle);
   fChain->SetBranchAddress("AOD_elePt", &AOD_elePt, &b_AOD_elePt);
   fChain->SetBranchAddress("AOD_eleEn", &AOD_eleEn, &b_AOD_eleEn);
   fChain->SetBranchAddress("AOD_eleEta", &AOD_eleEta, &b_AOD_eleEta);
   fChain->SetBranchAddress("AOD_elePhi", &AOD_elePhi, &b_AOD_elePhi);
   fChain->SetBranchAddress("AOD_eleCharge", &AOD_eleCharge, &b_AOD_eleCharge);
   fChain->SetBranchAddress("AOD_eleChargeConsistent", &AOD_eleChargeConsistent, &b_AOD_eleChargeConsistent);
   fChain->SetBranchAddress("AOD_eleIDbit", &AOD_eleIDbit, &b_AOD_eleIDbit);
   fChain->SetBranchAddress("AOD_elePassConversionVeto", &AOD_elePassConversionVeto, &b_AOD_elePassConversionVeto);
   fChain->SetBranchAddress("AOD_eled0", &AOD_eled0, &b_AOD_eled0);
   fChain->SetBranchAddress("AOD_eledz", &AOD_eledz, &b_AOD_eledz);
   fChain->SetBranchAddress("AOD_CaloMET_pt", &AOD_CaloMET_pt, &b_AOD_CaloMET_pt);
   fChain->SetBranchAddress("AOD_pfChMET_pt", &AOD_pfChMET_pt, &b_AOD_pfChMET_pt);
   fChain->SetBranchAddress("AOD_pfMET_pt", &AOD_pfMET_pt, &b_AOD_pfMET_pt);
   fChain->SetBranchAddress("AOD_CaloMET_phi", &AOD_CaloMET_phi, &b_AOD_CaloMET_phi);
   fChain->SetBranchAddress("AOD_pfChMET_phi", &AOD_pfChMET_phi, &b_AOD_pfChMET_phi);
   fChain->SetBranchAddress("AOD_pfMET_phi", &AOD_pfMET_phi, &b_AOD_pfMET_phi);

}
