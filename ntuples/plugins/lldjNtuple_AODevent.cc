#include "FWCore/MessageLogger/interface/MessageLogger.h"
//#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
//#include "FWCore/Common/interface/TriggerNames.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"
#include <iomanip>
#include <bitset>
using namespace std;

// (local) variables associated with tree branches
Int_t       AODrun_;
Long64_t    AODevent_;
Int_t       AODlumis_;
Bool_t      AODisData_;

Int_t       AODnTruePU_;
Int_t       AODnVtx_;
Int_t       AODnGoodVtx_;
Int_t       AODnTrksPV_;
Bool_t      AODisPVGood_;


void lldjNtuple::branchesAODEvent(TTree* tree) {

  tree->Branch("run",     	       &AODrun_);
  tree->Branch("event",    	       &AODevent_);
  tree->Branch("lumis",   	       &AODlumis_);
  tree->Branch("isData",  	       &AODisData_);

  tree->Branch("AODnTruePU",              &AODnTruePU_);
  tree->Branch("AODnVtx",                 &AODnVtx_);
  tree->Branch("AODnGoodVtx",             &AODnGoodVtx_);
  tree->Branch("AODnTrksPV",              &AODnTrksPV_);
  tree->Branch("AODisPVGood",             &AODisPVGood_);

}

void lldjNtuple::fillAODEvent(const edm::Event& e, const edm::EventSetup& es) {

  AODrun_    = e.id().run();
  AODevent_  = e.id().event();
  AODlumis_  = e.luminosityBlock();
  AODisData_ = e.isRealData();

  AODnTruePU_ = -1 ;
  if (!e.isRealData()) {
   edm::Handle<vector<PileupSummaryInfo> > AODpuInfoHandle;
   e.getByToken(AODpuCollection_, AODpuInfoHandle);
   if ( AODpuInfoHandle->size() > 0 ){
    AODnTruePU_ = AODpuInfoHandle->at(0).getTrueNumInteractions() ;
    //AODnTruePU_ = AODpuInfoHandle->at(1).getTrueNumInteractions() ;
   }
  }


  edm::Handle<edm::View<reco::Vertex>  >  AODVertexHandle;
  e.getByToken( AODVertexLabel_      ,  AODVertexHandle );

  AODnVtx_     = 0;
  AODnGoodVtx_ = 0;
  for(int k = 0; k < (int)AODVertexHandle->size();k++){        
  if (AODVertexHandle->at(k).isValid())
  {

   if (AODnVtx_ == 0) // assumes leading vtx in collection is PV
   {
    AODnTrksPV_ = AODVertexHandle->at(k).nTracks();
    AODisPVGood_ = false;
    if (!AODVertexHandle->at(k).isFake() &&
         AODVertexHandle->at(k).ndof() > 4. &&
         fabs(AODVertexHandle->at(k).z()) <= 24. &&
         fabs(AODVertexHandle->at(k).position().rho()) <= 2.)  AODisPVGood_ = true;
   } // if AODnVtx_ == 0

   // all vertices
   if (!AODVertexHandle->at(k).isFake() &&
        AODVertexHandle->at(k).ndof() > 4. &&
        fabs(AODVertexHandle->at(k).z()) <= 24. &&
        fabs(AODVertexHandle->at(k).position().rho()) <= 2.)  AODnGoodVtx_++;

   AODnVtx_++;
  } // if AODVertexHandle->at(k).isValid()
  else {edm::LogWarning("lldjNtuple") << "Primary vertices info not unavailable";}

  }
}
