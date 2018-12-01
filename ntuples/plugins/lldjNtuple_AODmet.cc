#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

using namespace std;

 float AOD_CaloMET_pt_  ; 
 float AOD_pfChMET_pt_  ; 
 float AOD_pfMET_pt_    ; 
 float AOD_CaloMET_phi_ ;  
 float AOD_pfChMET_phi_ ;  
 float AOD_pfMET_phi_   ;  
 float AOD_CaloMET_sumEt_ ;  
 float AOD_pfChMET_sumEt_ ;  
 float AOD_pfMET_sumEt_   ;  

 //float  AOD_pfMET_T1JERUp_ ; 
 //float  AOD_pfMET_T1JERDo_ ; 
 //float  AOD_pfMET_T1JESUp_ ; 
 //float  AOD_pfMET_T1JESDo_ ; 
 //float  AOD_pfMET_T1MESUp_ ; 
 //float  AOD_pfMET_T1MESDo_ ; 
 //float  AOD_pfMET_T1EESUp_ ; 
 //float  AOD_pfMET_T1EESDo_ ; 
 //float  AOD_pfMET_T1PESUp_ ; 
 //float  AOD_pfMET_T1PESDo_ ; 
 //float  AOD_pfMET_T1TESUp_ ; 
 //float  AOD_pfMET_T1TESDo_ ; 
 //float  AOD_pfMET_T1UESUp_ ; 
 //float  AOD_pfMET_T1UESDo_ ; 

 //float  AOD_pfMETPhi_T1JESUp_ ; 
 //float  AOD_pfMETPhi_T1JESDo_ ; 
 //float  AOD_pfMETPhi_T1UESUp_ ; 
 //float  AOD_pfMETPhi_T1UESDo_ ; 

void lldjNtuple::branchesAODMET(TTree* tree) {

 //printf(" making AOD MET branches\n");
 tree->Branch("AOD_CaloMET_pt" , &AOD_CaloMET_pt_  ); 
 tree->Branch("AOD_pfChMET_pt" , &AOD_pfChMET_pt_  ); 
 tree->Branch("AOD_pfMET_pt"   , &AOD_pfMET_pt_    ); 
 tree->Branch("AOD_CaloMET_phi", &AOD_CaloMET_phi_ );  
 tree->Branch("AOD_pfChMET_phi", &AOD_pfChMET_phi_ );  
 tree->Branch("AOD_pfMET_phi"  , &AOD_pfMET_phi_   );  

 //tree->Branch("AOD_pfMET_T1JERUp" , &AOD_pfMET_T1JERUp_ ) ; 
 //tree->Branch("AOD_pfMET_T1JERDo" , &AOD_pfMET_T1JERDo_ ) ; 
 //tree->Branch("AOD_pfMET_T1JESUp" , &AOD_pfMET_T1JESUp_ ) ; 
 //tree->Branch("AOD_pfMET_T1JESDo" , &AOD_pfMET_T1JESDo_ ) ; 
 //tree->Branch("AOD_pfMET_T1MESUp" , &AOD_pfMET_T1MESUp_ ) ; 
 //tree->Branch("AOD_pfMET_T1MESDo" , &AOD_pfMET_T1MESDo_ ) ; 
 //tree->Branch("AOD_pfMET_T1EESUp" , &AOD_pfMET_T1EESUp_ ) ; 
 //tree->Branch("AOD_pfMET_T1EESDo" , &AOD_pfMET_T1EESDo_ ) ; 
 //tree->Branch("AOD_pfMET_T1PESUp" , &AOD_pfMET_T1PESUp_ ) ; 
 //tree->Branch("AOD_pfMET_T1PESDo" , &AOD_pfMET_T1PESDo_ ) ; 
 //tree->Branch("AOD_pfMET_T1TESUp" , &AOD_pfMET_T1TESUp_ ) ; 
 //tree->Branch("AOD_pfMET_T1TESDo" , &AOD_pfMET_T1TESDo_ ) ; 
 //tree->Branch("AOD_pfMET_T1UESUp" , &AOD_pfMET_T1UESUp_ ) ; 
 //tree->Branch("AOD_pfMET_T1UESDo" , &AOD_pfMET_T1UESDo_ ) ; 

 //tree->Branch("AOD_pfMETPhi_T1JESUp", &AOD_pfMETPhi_T1JESUp_ ) ; 
 //tree->Branch("AOD_pfMETPhi_T1JESDo", &AOD_pfMETPhi_T1JESDo_ ) ; 
 //tree->Branch("AOD_pfMETPhi_T1UESUp", &AOD_pfMETPhi_T1UESUp_ ) ; 
 //tree->Branch("AOD_pfMETPhi_T1UESDo", &AOD_pfMETPhi_T1UESDo_ ) ; 
}

void lldjNtuple::fillAODMET(const edm::Event& e, const edm::EventSetup& es) {

 //printf(" filling AOD MET branches\n");

 edm::Handle<edm::View<reco::CaloMET> > AODCaloMETHandle;
 edm::Handle<edm::View<reco::PFMET> >   AODpfChMETHandle;
 edm::Handle<edm::View<reco::PFMET> >   AODpfMETHandle;

 e.getByToken(AODCaloMETlabel_, AODCaloMETHandle); 
 e.getByToken(AODpfChMETlabel_, AODpfChMETHandle); 
 e.getByToken(AODpfMETlabel_  , AODpfMETHandle);   

 if (AODCaloMETHandle.isValid()) {
   const reco::CaloMET *AODCaloMET = 0;
   AODCaloMET = &(AODCaloMETHandle->front());
   //printf("AODCaloMETHandle is valid\n");
   AOD_CaloMET_pt_   = AODCaloMET->pt() ; 
   AOD_CaloMET_phi_  = AODCaloMET->phi() ;  
   AOD_CaloMET_sumEt_= AODCaloMET->sumEt() ;  
 }

 if (AODpfChMETHandle.isValid()) {
   const reco::PFMET *AODpfChMET = 0;
   AODpfChMET = &(AODpfChMETHandle->at(0));
   //printf("AODpfChMETHandle is valid\n");
   AOD_pfChMET_pt_    = AODpfChMET->pt() ; 
   AOD_pfChMET_phi_   = AODpfChMET->phi() ;  
   AOD_pfChMET_sumEt_ = AODpfChMET->sumEt() ;  
 }

 if (AODpfMETHandle.isValid()) {
   const reco::PFMET *AODpfMET = 0;
   AODpfMET = &(AODpfMETHandle->at(0));
   //printf("AODpfMETHandle is valid\n");
   AOD_pfMET_pt_     = AODpfMET->pt() ; 
   AOD_pfMET_phi_    = AODpfMET->phi() ;  
   AOD_pfMET_sumEt_  = AODpfMET->sumEt() ;  

   // shifts
   //const pat::MET *patAODpfMET = 0;
   //patAODpfMET = &(AODpfMETHandle->at(0));
   //const pat::MET &patAODpfMET = dynamic_cast<const pat::MET &>(*AODpfMET);
   //
   //std::cout<<" "<<patAODpfMET.shiftedPt(pat::MET::JetResUp)<<" "<<std::endl;
   //AOD_pfMET_T1JERUp_ = patAODpfMET.shiftedPt(pat::MET::JetResUp);
   //AOD_pfMET_T1JERDo_ = patAODpfMET.shiftedPt(pat::MET::JetResDown);
   //AOD_pfMET_T1JESUp_ = patAODpfMET.shiftedPt(pat::MET::JetEnUp);
   //AOD_pfMET_T1JESDo_ = patAODpfMET.shiftedPt(pat::MET::JetEnDown);
   //AOD_pfMET_T1MESUp_ = patAODpfMET.shiftedPt(pat::MET::MuonEnUp);
   //AOD_pfMET_T1MESDo_ = patAODpfMET.shiftedPt(pat::MET::MuonEnDown);
   //AOD_pfMET_T1EESUp_ = patAODpfMET.shiftedPt(pat::MET::ElectronEnUp);
   //AOD_pfMET_T1EESDo_ = patAODpfMET.shiftedPt(pat::MET::ElectronEnDown);
   //AOD_pfMET_T1PESUp_ = patAODpfMET.shiftedPt(pat::MET::PhotonEnUp);
   //AOD_pfMET_T1PESDo_ = patAODpfMET.shiftedPt(pat::MET::PhotonEnDown);
   //AOD_pfMET_T1TESUp_ = patAODpfMET.shiftedPt(pat::MET::TauEnUp);
   //AOD_pfMET_T1TESDo_ = patAODpfMET.shiftedPt(pat::MET::TauEnDown);
   //AOD_pfMET_T1UESUp_ = patAODpfMET.shiftedPt(pat::MET::UnclusteredEnUp);
   //AOD_pfMET_T1UESDo_ = patAODpfMET.shiftedPt(pat::MET::UnclusteredEnDown);

   //AOD_pfMETPhi_T1JESUp_ = patAODpfMET.shiftedPhi(pat::MET::JetEnUp);
   //AOD_pfMETPhi_T1JESDo_ = patAODpfMET.shiftedPhi(pat::MET::JetEnDown);
   //AOD_pfMETPhi_T1UESUp_ = patAODpfMET.shiftedPhi(pat::MET::UnclusteredEnUp);
   //AOD_pfMETPhi_T1UESDo_ = patAODpfMET.shiftedPhi(pat::MET::UnclusteredEnDown);
 }

}
