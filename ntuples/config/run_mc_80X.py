import FWCore.ParameterSet.Config as cms

##########################################################################################
# Setup

# this is the process run by cmsRun
process = cms.Process('LLDJ')
#process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load("RecoTracker.TkNavigation.NavigationSchoolESProducer_cfi")

# log output
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )  ## number of events -1 does all
process.MessageLogger.cerr.FwkReport.reportEvery = 100
#process.Tracer = cms.Service('Tracer')

# input files
process.source = cms.Source('PoolSource',
                            fileNames = cms.untracked.vstring(
 #'/store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/100000/00099D43-77ED-E611-8889-5065F381E1A1.root',

  #/ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM
   #'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/08BA365D-40E5-E611-955F-00266CF89498.root'


  #'/store/mc/RunIISummer16MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/08BA365D-40E5-E611-955F-00266CF89498.root'
  #'/store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/00000/004A0552-3929-E611-BD44-0025905A48F0.root'
  #'/store/mc/RunIISummer16MiniAODv2/WWTo2L2Nu_13TeV-powheg/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/08E155A9-FAB6-E611-92BF-00259073E45E.root'

   #'file:/afs/hep.wisc.edu/cms/tperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_787B82F9-0ECB-E611-A5CD-1866DAEA7EA8.root',
   #'file:/afs/hep.wisc.edu/cms/tperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_EA59D0D0-5CCB-E611-B501-002590207C28.root',


#  # MS40-CT1,0p05
   #'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-0p05_52134309-19CF-E611-AD86-0CC47A4D7604.root',
#   'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_2CA15029-73CB-E611-8315-02163E019C53.root',
   #'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_62211E56-2EC9-E611-95F3-02163E019C8F.root'

#  # MS40-CT100
  #'/store/mc/RunIISummer16MiniAODv2/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/54C6A127-05CA-E611-AAD2-0CC47A1DF1A4.root',
  #'/store/mc/RunIISummer16MiniAODv2/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/70576F21-CDC9-E611-BC72-001E675047A5.root',
  #'/store/mc/RunIISummer16MiniAODv2/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/EA59D0D0-5CCB-E611-B501-002590207C28.root'

  'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_54C6A127-05CA-E611-AAD2-0CC47A1DF1A4.root'
 ),
   secondaryFileNames= cms.untracked.vstring(
  #'/store/mc/RunIISummer16DR80Premix/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/D6822833-FEC8-E611-8CD1-002590E7D7DE.root',
  'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/AOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_D6822833-FEC8-E611-8CD1-002590E7D7DE.root'
 ),
)


# output name
process.TFileService = cms.Service('TFileService', fileName = cms.string('lldjntuple_mc.root'));

#process.out = cms.OutputModule(
#'PoolOutputModule',
#     fileName = cms.untracked.string('output6.root'),
#     outputCommands = cms.untracked.vstring( 
#      'keep *', )  
#)

# cms geometry
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')

# global tag
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'

##########################################################################################
# Jet Energy Corrections
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#CorrPatJets
# just take from global tag, no need to update collections

##########################################################################################
# Electron / Photon Corrections
# https://twiki.cern.ch/twiki/bin/view/CMS/EGMRegression

### EGM 80X regression
from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
process = regressionWeights(process)

# Some proesses need random numbers, calculate using TRandom3 - Mersenne Twister
process.RandomNumberGeneratorService = cms.Service('RandomNumberGeneratorService',
 calibratedPatElectrons  = cms.PSet( initialSeed = cms.untracked.uint32(8675389),
                                     engineName = cms.untracked.string('TRandom3'),
                                     ),
 calibratedPatPhotons    = cms.PSet( initialSeed = cms.untracked.uint32(8675389),
                                     engineName = cms.untracked.string('TRandom3'),
                                     ),
 lldjNtuple              = cms.PSet( initialSeed = cms.untracked.uint32(67890),
                                     engineName = cms.untracked.string('TRandom3')
                                     )
)
process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')
process.load('EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi')
process.load('EgammaAnalysis.ElectronTools.calibratedPatPhotonsRun2_cfi')

# correct scale (data) or smear resolution (MC) 
process.calibratedPatElectrons.isMC = cms.bool(True)
process.calibratedPatPhotons.isMC = cms.bool(True)

##########################################################################################
# Electron / Photon Versioned ID

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
switchOnVIDPhotonIdProducer(process, dataFormat)

# define which IDs we want to produce
eleid_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff']
                 #'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff',
                 #'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_HZZ_V1_cff']
    
phoid_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff']
                 #'RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Spring16_nonTrig_V1_cff']

#add them to the VID producer
for idmod in eleid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

for idmod in phoid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)

# hack recommended by https://twiki.cern.ch/twiki/bin/view/CMS/EGMRegression#VIDAnchor
process.selectedElectrons = cms.EDFilter('PATElectronSelector',
    src = cms.InputTag('calibratedPatElectrons','','LLDJ'),
    cut = cms.string('pt>5 && abs(superCluster.eta)<2.5')
)

process.selectedPhotons = cms.EDFilter('PATPhotonSelector',
    src = cms.InputTag('calibratedPatPhotons','','LLDJ'),
    cut = cms.string('pt>5 && abs(superCluster.eta)<2.5')
)

# load electron/photon ID configurations
# we've modified this from the standard ID producer
# to manually specify AOD/miniAOD
process.load('RecoEgamma.ElectronIdentification.ElectronIDValueMapProducer_cfi')
process.load('RecoEgamma.PhotonIdentification.PhotonIDValueMapProducer_cfi')

# Set up EGamma IDs
process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('selectedElectrons','','LLDJ')
process.egmPhotonIDs.physicsObjectSrc = cms.InputTag('selectedPhotons','','LLDJ')
process.egmGsfElectronIDs.isAOD=cms.bool(False)
process.egmPhotonIDs.isAOD=cms.bool(False)

# Electron ID 
process.electronIDValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons','','LLDJ')
process.electronIDValueMapProducer.src = cms.InputTag('') # make it give error if misconfigured
process.electronIDValueMapProducer.isAOD=cms.bool(False)

# Photon ID 
process.photonIDValueMapProducer.srcMiniAOD = cms.InputTag('selectedPhotons','','LLDJ')
process.photonIDValueMapProducer.src = cms.InputTag('')
process.photonIDValueMapProducer.isAOD=cms.bool(False)

# we don't use MVA ID now, but maybe some time 
# process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons','','LLDJ')
# process.photonMVAValueMapProducer.srcMiniAOD = cms.InputTag('selectedPhotons','','LLDJ')
# process.electronMVAValueMapProducer.src = cms.InputTag('selectedElectrons','','LLDJ')
# process.photonMVAValueMapProducer.src = cms.InputTag('selectedPhotons','','LLDJ')

# Photon Isolation
process.egmPhotonIsolation.srcToIsolate = cms.InputTag('selectedPhotons','','LLDJ')

##########################################################################################
# Now update MET
# 

from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD(process,
                           isData=False
                           )

#######################  BadPFMuonFilter
process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = cms.InputTag('slimmedMuons', '', 'PAT')
process.BadPFMuonFilter.PFCandidates = cms.InputTag('packedPFCandidates', '', 'PAT')

#######################  BadChargedCandidateFilter             
process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag('slimmedMuons', '', 'PAT')
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag('packedPFCandidates', '', 'PAT')

process.lldjMETFiltersSequence = cms.Sequence(
     process.BadPFMuonFilter *
     process.BadChargedCandidateFilter 
)

##########################################################################################
# For AOD Track variables
# 
process.MaterialPropagator = cms.ESProducer('PropagatorWithMaterialESProducer',
    ComponentName = cms.string('PropagatorWithMaterial'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string(''),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)

process.TransientTrackBuilderESProducer = cms.ESProducer('TransientTrackBuilderESProducer',
    ComponentName = cms.string('TransientTrackBuilder')
)

#NTuplizer
process.lldjNtuple = cms.EDAnalyzer('lldjNtuple',
  vertexFitterConfig = cms.PSet(
        finder = cms.string('avf'),
        sigmacut = cms.double(10.),
        Tini = cms.double(256.),
        ratio = cms.double(0.25),
        ),
 electronSrc               = cms.InputTag('selectedElectrons','','LLDJ'),
 rhoLabel                  = cms.InputTag('fixedGridRhoFastjetAll'),
 eleVetoIdMap              = cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-veto'),
 eleLooseIdMap             = cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose'),
 eleMediumIdMap            = cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium'),
 eleTightIdMap             = cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight'),
 eleHLTIdMap               = cms.InputTag('egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1'),
 #eleMVAValuesMap           = cms.InputTag('electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values'),
 #eleMVAHZZValuesMap        = cms.InputTag('electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16HZZV1Values'),
 #elePFClusEcalIsoProducer  = cms.InputTag('electronEcalPFClusterIsolationProducer'),
 #elePFClusHcalIsoProducer  = cms.InputTag('electronHcalPFClusterIsolationProducer'),

 rhoCentralLabel           = cms.InputTag('fixedGridRhoFastjetCentralNeutral'),
 pileupCollection          = cms.InputTag('slimmedAddPileupInfo'),
 VtxLabel                  = cms.InputTag('offlineSlimmedPrimaryVertices'),
 triggerResults            = cms.InputTag('TriggerResults', '', 'HLT'),

 beamspotLabel_            = cms.InputTag('offlineBeamSpot'),                                    

 ak4JetSrc                 = cms.InputTag('slimmedJets'),
 AODak4CaloJetsSrc         = cms.InputTag('ak4CaloJets' , '', 'RECO'),
 AODak4PFJetsSrc           = cms.InputTag('ak4PFJets'   , '', 'RECO'),
 AODak4PFJetsCHSSrc        = cms.InputTag('ak4PFJetsCHS', '', 'RECO'),
 AODVertexSrc              = cms.InputTag('offlinePrimaryVertices', '', 'RECO'),
 AODTrackSrc               = cms.InputTag('generalTracks', '', 'RECO'),

 patTriggerResults         = cms.InputTag('TriggerResults', '', 'PAT'),
 BadChargedCandidateFilter = cms.InputTag('BadChargedCandidateFilter'),
 BadPFMuonFilter           = cms.InputTag('BadPFMuonFilter'),
 pfMETLabel                = cms.InputTag('slimmedMETs'),

 muonSrc                   = cms.InputTag('slimmedMuons'),

 photonSrc                 = cms.InputTag('selectedPhotons','','LLDJ'),
 phoLooseIdMap = cms.InputTag('egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-loose'),
 phoMediumIdMap = cms.InputTag('egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-medium'),
 phoTightIdMap = cms.InputTag('egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-tight'),
 phoChargedIsolation       = cms.InputTag('photonIDValueMapProducer:phoChargedIsolation'),
 phoNeutralHadronIsolation = cms.InputTag('photonIDValueMapProducer:phoNeutralHadronIsolation'),
 phoPhotonIsolation        = cms.InputTag('photonIDValueMapProducer:phoPhotonIsolation'),
 phoWorstChargedIsolation = cms.InputTag('photonIDValueMapProducer:phoWorstChargedIsolation'),

 genParticleSrc    = cms.InputTag("genParticles"),

 bits = cms.InputTag("TriggerResults","","HLT"),
 prescales = cms.InputTag("patTrigger"),
 objects = cms.InputTag("selectedPatTrigger"),

)

#builds Ntuple
process.p = cms.Path(
    process.regressionApplication*  # e/gamma energy correction/resolution regression
    process.calibratedPatElectrons*
    process.calibratedPatPhotons*
    process.selectedElectrons*
    process.selectedPhotons*
    process.egmGsfElectronIDSequence*
    process.egmPhotonIDSequence*
    process.lldjMETFiltersSequence*
    process.lldjNtuple
    )

#process.ep = cms.EndPath(process.out)
#print process.dumpPython()
#print process.egmGsfElectronIDSequence.dumpPython()

