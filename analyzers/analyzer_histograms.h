
#ifndef analyzer_histograms_h
#define analyzer_histograms_h

#include "TMath.h"

#include "analyzer_scalefactors.h"

class analyzer_histograms : public analyzer_scalefactors {


public :

                  analyzer_histograms();
   virtual        ~analyzer_histograms(); 

 static const int PhoPtBin      = 50;
 static const int MuPtBin       = 33;
 static const int ElePtBin      = 33;
 static const int PhoPtBinMax   = 400;
 static const int MuPtBinMax    = 99;
 static const int ElePtBinMax   = 99;
 static const int PhoPtBinMin   = 0;
 static const int MuPtBinMin    = 0;
 static const int ElePtBinMin   = 0;
 static const int PhoEtaBin     = 30;
 static const int MuEtaBin      = 30;
 static const int EleEtaBin     = 30;
 static const int PhoEtaBinMax  = 5;
 static const int MuEtaBinMax   = 5;
 static const int EleEtaBinMax  = 5;
 static const int PhoEtaBinMin  = -5;
 static const int MuEtaBinMin   = -5;
 static const int EleEtaBinMin  = -5;

 // Histograms

 // make 1D,2D histograms (helper function)
 TH2F          initSingleHistogramTH2F(TString hnamex, TString htitley,
                                   Int_t nbinsx, Float_t xmin, Float_t xmax,
                                   Int_t nbinsy, Float_t ymin, Float_t ymax);
 TH2F          initSingleHistogramTH2F(TString hname, TString htitle,
					int nbinsx, Float_t xbins[],
					int nbinsy, Float_t ybins[]);
 TH1F          initSingleHistogramTH1F(TString hname, TString htitle,
                                   Int_t nbins, Float_t xmin,
                                   Float_t xmax);
 TH1F          initSingleHistogramTH1F(TString hname, TString htitle, 
				      int nbins, Float_t xbins[]);

 // Cutflow histograms
 Bool_t        initCutflowHistograms( TString uncbin );
 Bool_t        fillCutflowHistograms(Float_t weight, int selbin, Int_t localselint, Int_t localselkey);
 Bool_t        writeCutflowHistograms(int selbin);
 Bool_t        deleteCutflowHistograms(int selbin);

 // 2D Histograms 
 Bool_t        init2DHistograms( TString uncbin );
 Bool_t        fill2DHistograms(Float_t weight, int selbin);
 Bool_t        write2DHistograms(int selbin);
 Bool_t        delete2DHistograms(int selbin);
 // Electron Variables
 Bool_t        initEleHistograms( TString uncbin );
 Bool_t        fillEleHistograms(Float_t weight, int selbin );
 Bool_t        writeEleHistograms(int selbin);
 Bool_t        deleteEleHistograms(int selbin);
 // Muon Variables
 Bool_t        initMuHistograms( TString uncbin );
 Bool_t        fillMuHistograms(Float_t weight, int selbin);
 Bool_t        writeMuHistograms(int selbin);
 Bool_t        deleteMuHistograms(int selbin);
 // Lepton Variables
 Bool_t        initLepHistograms( TString uncbin );
 Bool_t        fillLepHistograms(Float_t weight, int selbin);
 Bool_t        writeLepHistograms(int selbin);
 Bool_t        deleteLepHistograms(int selbin);
 // Photon Variables
 Bool_t        initPhoHistograms( TString uncbin );
 Bool_t        fillPhoHistograms(Float_t weight, int selbin);
 Bool_t        writePhoHistograms(int selbin);
 Bool_t        deletePhoHistograms(int selbin);
 // MET/HT Variables
 Bool_t        initMETHTHistograms( TString uncbin );
 Bool_t        fillMETHTHistograms(Float_t weight, int selbin);
 Bool_t        writeMETHTHistograms(int selbin);
 Bool_t        deleteMETHTHistograms(int selbin);
 // Trigger Turn On Curves
 Bool_t        initTTOCHistograms( TString uncbin );
 Bool_t        fillTTOCHistograms(Float_t weight, int selbin);
 Bool_t        writeTTOCHistograms(int selbin);
 Bool_t        deleteTTOCHistograms(int selbin);

 // AODCaloJet Basic Variables
 Bool_t        initAODCaloJetBasicHistograms( TString uncbin );
 Bool_t        fillAODCaloJetBasicHistograms(Float_t weight, int selbin, int jetbin);
 Bool_t        writeAODCaloJetBasicHistograms(int selbin, int jetbin);
 Bool_t        deleteAODCaloJetBasicHistograms(int selbin);
 Bool_t        deleteAODCaloJetBasicHistograms(int selbin, int jetbin);
 // AODCaloJet Extra Variables
 Bool_t        initAODCaloJetExtraHistograms( TString uncbin );
 Bool_t        fillAODCaloJetExtraHistograms(Float_t weight, int selbin, int jetbin);
 Bool_t        writeAODCaloJetExtraHistograms(int selbin, int jetbin);
 Bool_t        deleteAODCaloJetExtraHistograms(int selbin, int jetbin);
 // AODCaloJetTag Basic Variables
 Bool_t        initAODCaloJetTagHistograms( TString uncbin );
 Bool_t        fillAODCaloJetTagHistograms(Float_t weight, int selbin, int tagbin);
 Bool_t        writeAODCaloJetTagHistograms(int selbin, int tagbin);
 Bool_t        deleteAODCaloJetTagHistograms(int selbin, int tagbin);
 // Jet Multiplicity
 Bool_t        initAODCaloJetMultHistograms( TString uncbin );
 Bool_t        fillAODCaloJetMultHistograms(Float_t weight, int selbin);
 Bool_t        writeAODCaloJetMultHistograms(int selbin);
 Bool_t        deleteAODCaloJetMultHistograms(int selbin);
 Bool_t        initAODCaloJetTagMultHistograms( TString uncbin );
 Bool_t        fillAODCaloJetTagMultHistograms(Float_t weight, int selbin);
 Bool_t        writeAODCaloJetTagMultHistograms(int selbin);
 Bool_t        deleteAODCaloJetTagMultHistograms(int selbin);
 
 // Extra histograms
 Bool_t        initExtraHistograms( TString uncbin );
 Bool_t        fillExtraHistograms(Float_t weight, int selbin);
 Bool_t        writeExtraHistograms(int selbin);
 Bool_t        deleteExtraHistograms(int selbin);

 //For variable binning
 Bool_t        scaleVariableBinHistograms(int selbin);

 // Set up which histograms to fill 
 Bool_t        fillSelectedHistograms(Float_t weight, int selbin);
 Bool_t        fillSelectedJetHistograms(Float_t weight, int selbin, int jetbin);
 Bool_t        fillSelectedTagHistograms(Float_t weight, int selbin, int tagbin);
 Bool_t        writeSelectedHistograms(int selbin);
 Bool_t        writeSelectedJetHistograms(int selbin, int jetbin);
 Bool_t        writeSelectedTagHistograms(int selbin, int tagbin);

 Bool_t dofillselbin    [SELBINNAMESIZE];

 // initialize histograms as global
 TH1F histoTH1F;
 TH2F histoTH2F;

 // Cutflow histograms
 TH1F h_Cutflow                       [SELBINNAMESIZE];
 TH1F h_Onecut                        [SELBINNAMESIZE];
 TH1F h_NMinus                        [SELBINNAMESIZE];
 TH1F h_RawCutflow                    [SELBINNAMESIZE];
 TH1F h_RawOnecut                     [SELBINNAMESIZE];
 TH1F h_RawNMinus                     [SELBINNAMESIZE];

 // Electron
 TH1F  h_AOD_nEle                     [SELBINNAMESIZE]; //;
 TH1F  h_AOD_nSelectedEle             [SELBINNAMESIZE]; //;
 TH1F  h_AOD_elePt                    [SELBINNAMESIZE]; //;
 TH1F  h_AOD_eleEn                    [SELBINNAMESIZE]; //;
 TH1F  h_AOD_eleEta                   [SELBINNAMESIZE]; //;
 TH1F  h_AOD_elePhi                   [SELBINNAMESIZE]; //;
 TH1F  h_AOD_eleCharge                [SELBINNAMESIZE]; //;

 // Muon
 TH1F  h_AOD_nMu                     [SELBINNAMESIZE];
 TH1F  h_AOD_nSelectedMu             [SELBINNAMESIZE];
 TH1F  h_AOD_muPt                    [SELBINNAMESIZE];
 TH1F  h_AOD_muEn                    [SELBINNAMESIZE];
 TH1F  h_AOD_muEta                   [SELBINNAMESIZE];
 TH1F  h_AOD_muPhi                   [SELBINNAMESIZE];
 TH1F  h_AOD_muCharge                [SELBINNAMESIZE];
 TH1F  h_AOD_muPFdBetaIsolation      [SELBINNAMESIZE];
 
 // Generic Lepton
 TH1F  h_AOD_dilepton_Mass           [SELBINNAMESIZE];
 TH1F  h_AOD_dilepton_Pt             [SELBINNAMESIZE];
 TH1F  h_AOD_OSOFdilepton_Mass       [SELBINNAMESIZE];
 TH1F  h_AOD_OSOFdilepton_Pt         [SELBINNAMESIZE];

 // Photon
 TH1F  h_AOD_nPho                     [SELBINNAMESIZE];
 TH1F  h_AOD_nSelectedPho             [SELBINNAMESIZE];
 TH1F  h_AOD_phoEn                    [SELBINNAMESIZE];
 TH1F  h_AOD_phoPt                    [SELBINNAMESIZE];
 TH1F  h_AOD_phoEta                   [SELBINNAMESIZE];
 TH1F  h_AOD_phoPhi                   [SELBINNAMESIZE];

 // MET / HT
 TH1F  h_AOD_MET_phi              [SELBINNAMESIZE];
 TH1F  h_AOD_MET_pt               [SELBINNAMESIZE];
 TH1F  h_htall                    [SELBINNAMESIZE];
 TH1F  h_htaodcalojets            [SELBINNAMESIZE];

 // nJets
 TH1F  h_nSelectedAODCaloJet            [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTag         [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB1      [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB2      [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB3      [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTag_0b      [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB1_0b   [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB2_0b   [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB3_0b   [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTag_1b      [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB1_1b   [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB2_1b   [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB3_1b   [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTag_2b      [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB1_2b   [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB2_2b   [SELBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTagSB3_2b   [SELBINNAMESIZE];
 TH1F  h_nCaloJet                       [SELBINNAMESIZE]; // AODnCaloJet; 
 TH1F  h_nPFJet                         [SELBINNAMESIZE]; // AODnPFJet; 
 TH1F  h_nPFchsJet                      [SELBINNAMESIZE]; // AODnPFchsJet; 

 // AODCaloJetBasicHistograms
 TH1F  h_AODCaloJetPt                             [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetPtVar                          [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetEta                            [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetPhi                            [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAlphaMax                       [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAlphaMax2                      [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAlphaMaxPrime                  [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAlphaMaxPrime2                 [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetBeta                           [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetBeta2                          [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetSumIP                          [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetSumIPSig                       [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetMedianIP                       [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetMedianLog10IPSig               [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetTrackAngle                     [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetLogTrackAngle                  [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetMedianLog10TrackAngle          [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetTotalTrackAngle                [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetMinDR                          [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetCSV                            [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetPartonFlavour                  [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAbsEta                         [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH2F  h_AODCaloJetPtVarAbsEtaVar                 [SELBINNAMESIZE][JETMULTNAMESIZE];

 // AODCaloJetExtraHistograms
 TH1F  h_AODCaloJetAvfVx                          [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVy                          [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVz                          [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTotalChiSquared       [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDegreesOfFreedom      [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexChi2NDoF              [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDistanceToBeam        [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTransverseError       [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTransverseSig         [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDeltaEta              [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDeltaPhi              [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexRecoilPt              [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTrackMass             [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTrackEnergy           [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfBeamSpotDeltaPhi            [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfBeamSpotRecoilPt            [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetNCleanMatchedTracks            [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetSumHitsInFrontOfVert           [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetSumMissHitsAfterVert           [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetHitsInFrontOfVertPerTrack      [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetMissHitsAfterVertPerTrack      [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfDistToPV                    [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDeltaZtoPV            [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDeltaZtoPV2           [SELBINNAMESIZE][JETMULTNAMESIZE];

 // AODCaloJetTagHistograms
 TH1F  h_AODCaloJetPt_Tag0                       [SELBINNAMESIZE][TAGMULTNAMESIZE];
 TH1F  h_AODCaloJetPtVar_Tag0                    [SELBINNAMESIZE][TAGMULTNAMESIZE];
 TH1F  h_AODCaloJetMinDR_Tag0                    [SELBINNAMESIZE][TAGMULTNAMESIZE];
 TH1F  h_AODCaloJetCSV_Tag0                      [SELBINNAMESIZE][TAGMULTNAMESIZE];
 TH1F  h_AODCaloJetPartonFlavour_Tag0            [SELBINNAMESIZE][TAGMULTNAMESIZE];
 TH1F  h_AODCaloJetAbsEta_Tag0                   [SELBINNAMESIZE][TAGMULTNAMESIZE];
 TH1F  h_AODCaloJetNCleanMatchedTracks_Tag0      [SELBINNAMESIZE][TAGMULTNAMESIZE];
 TH2F  h_AODCaloJetPtVarAbsEtaVar_Tag0           [SELBINNAMESIZE][TAGMULTNAMESIZE];
 
 //------------------Trigger turn on curve
 //basic histograms
 TH1F  h_TTOCMu1Pt                [SELBINNAMESIZE];
 TH1F  h_TTOCMu2Pt                [SELBINNAMESIZE];
 TH2F  h_TTOCMuPt                 [SELBINNAMESIZE];
 TH1F  h_TTOCMu1Eta               [SELBINNAMESIZE];
 TH1F  h_TTOCMu2Eta               [SELBINNAMESIZE];
 TH2F  h_TTOCMuEta                [SELBINNAMESIZE];
 TH1F  h_TTOCEle1Pt               [SELBINNAMESIZE];
 TH1F  h_TTOCEle2Pt               [SELBINNAMESIZE];
 TH2F  h_TTOCElePt                [SELBINNAMESIZE];
 TH1F  h_TTOCEle1Eta              [SELBINNAMESIZE];
 TH1F  h_TTOCEle2Eta              [SELBINNAMESIZE];
 TH2F  h_TTOCEleEta               [SELBINNAMESIZE];
 //EMu->leadElectronPt>leadMuonPt, MuE->leadMuonPt>leadElectronPt
 TH1F  h_TTOCEMu_ElePt            [SELBINNAMESIZE];
 TH1F  h_TTOCEMu_MuPt             [SELBINNAMESIZE];
 TH2F  h_TTOCEMuPt                [SELBINNAMESIZE];
 TH1F  h_TTOCEMu_EleEta           [SELBINNAMESIZE];
 TH1F  h_TTOCEMu_MuEta            [SELBINNAMESIZE];
 TH2F  h_TTOCEMuEta               [SELBINNAMESIZE];
 TH1F  h_TTOCMuE_ElePt            [SELBINNAMESIZE];
 TH1F  h_TTOCMuE_MuPt             [SELBINNAMESIZE];
 TH2F  h_TTOCMuEPt                [SELBINNAMESIZE];
 TH1F  h_TTOCMuE_EleEta           [SELBINNAMESIZE];
 TH1F  h_TTOCMuE_MuEta            [SELBINNAMESIZE];
 TH2F  h_TTOCMuEEta               [SELBINNAMESIZE];
 TH1F  h_TTOCPhoPt                [SELBINNAMESIZE];
 TH1F  h_TTOCPhoEta               [SELBINNAMESIZE];
 //--Double Muon
 TH1F  h_TTOCTriggerDMu1Pt        [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerDMu2Pt        [SELBINNAMESIZE];
 TH2F  h_TTOCTriggerDMuPt         [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerDMu1Eta       [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerDMu2Eta       [SELBINNAMESIZE];
 TH2F  h_TTOCTriggerDMuEta        [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerDTkMu1Eta     [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerDTkMu2Eta     [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerDTkMu1Pt      [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerDTkMu2Pt      [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerNoDZMu1Eta    [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerNoDZMu2Eta    [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerNoDZMu1Pt     [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerNoDZMu2Pt     [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerNoDZTkMu1Eta  [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerNoDZTkMu2Eta  [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerNoDZTkMu1Pt   [SELBINNAMESIZE];
 //TH1F  h_TTOCTriggerNoDZTkMu2Pt   [SELBINNAMESIZE];
 //--Single Muon
 TH1F  h_TTOCTrigger22MuEta       [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger22MuPt        [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger22TkMuEta     [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger22TkMuPt      [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger24MuEta       [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger24MuPt        [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger24TkMuEta     [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger24TkMuPt      [SELBINNAMESIZE];
 //Double Electron
 TH1F  h_TTOCTrigger23DEle1Eta       [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger23DEle2Eta       [SELBINNAMESIZE];
 TH2F  h_TTOCTrigger23DEleEta        [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger23DEle1Pt        [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger23DEle2Pt        [SELBINNAMESIZE];
 TH2F  h_TTOCTrigger23DElePt         [SELBINNAMESIZE];
 //TH1F  h_TTOCTrigger17DEle1Eta       [SELBINNAMESIZE];
 //TH1F  h_TTOCTrigger17DEle2Eta       [SELBINNAMESIZE];
 //TH1F  h_TTOCTrigger17DEle1Pt        [SELBINNAMESIZE];
 //TH1F  h_TTOCTrigger17DEle2Pt        [SELBINNAMESIZE];
 //Single Electron
 TH1F  h_TTOCTrigger23EleEta      [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger23ElePt       [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger27EleEta      [SELBINNAMESIZE];
 TH1F  h_TTOCTrigger27ElePt       [SELBINNAMESIZE];
 //Single Photon
 TH1F  h_TTOCTriggerPhoEta        [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerPhoPt         [SELBINNAMESIZE];
 //--EMu
 TH1F  h_TTOCTriggerEMu_ElePt     [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerEMu_MuPt      [SELBINNAMESIZE];
 TH2F  h_TTOCTriggerEMuPt         [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerEMu_EleEta    [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerEMu_MuEta     [SELBINNAMESIZE];
 TH2F  h_TTOCTriggerEMuEta        [SELBINNAMESIZE];
 //--MuE
 TH1F  h_TTOCTriggerMuE_ElePt     [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerMuE_MuPt      [SELBINNAMESIZE];
 TH2F  h_TTOCTriggerMuEPt         [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerMuE_EleEta    [SELBINNAMESIZE];
 TH1F  h_TTOCTriggerMuE_MuEta     [SELBINNAMESIZE];
 TH2F  h_TTOCTriggerMuEEta        [SELBINNAMESIZE];
 
 // // 2D
 TH2F h_IpVAlpha                  [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH2F h_IpVjetPt                  [SELBINNAMESIZE][JETMULTNAMESIZE];
 TH2F h_AlphaVjetPt               [SELBINNAMESIZE][JETMULTNAMESIZE];

 // Background Estimate
 int getMistagRateBin(int j, TString mistag_name);
 float getMistagRateByBin(int j, TString mistag_name);
 float getMistagRate(int j, TString mistag_name);
 float computeTerm(int b, std::vector<int> mistagBins_tagged, std::vector<int> mistagBins_untagged, TString mistag_name);
 void comb(int n, int r, int *arr, int sz, Float_t weight, TString mistag_name);
 TH1F h_bkgest_pt;
 TH1F h_bkgest_pteta;
 Bool_t initBackgroundEstimateHistograms();
 Bool_t fillBackgroundEstimateHistograms(Float_t weight);
 Bool_t writeBackgroundEstimateHistograms(TFile* outfile);

};

#endif
