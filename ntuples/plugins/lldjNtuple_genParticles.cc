#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"
#include "LLDJstandalones/ntuples/interface/GenParticleParentage.h"

using namespace std;


//Variables for branches
vector<int>   llpId;
vector<int>   llpStatus;
vector<float> llpPt;
vector<float> llpEta;
vector<float> llpPhi;
vector<float> llpMass;
vector<int>   llpDaughterId;
vector<int>   llpDaughterStatus;
vector<float> llpDaughterPt;
vector<float> llpDaughterEta;
vector<float> llpDaughterPhi;
vector<float> llpDaughterMass;
vector<float> toppts;


void lldjNtuple::branchesGenPart(TTree* tree) {

  tree->Branch("llpId",             &llpId);
  tree->Branch("llpStatus",         &llpStatus);
  tree->Branch("llpPt",             &llpPt);
  tree->Branch("llpEta",            &llpEta);
  tree->Branch("llpPhi",            &llpPhi);
  tree->Branch("llpMass",           &llpMass);
  tree->Branch("llpDaughterId",     &llpDaughterId);
  tree->Branch("llpDaughterStatus", &llpDaughterStatus);
  tree->Branch("llpDaughterPt",     &llpDaughterPt);
  tree->Branch("llpDaughterEta",    &llpDaughterEta);
  tree->Branch("llpDaughterPhi",    &llpDaughterPhi);
  tree->Branch("llpDaughterMass",   &llpDaughterMass);
  tree->Branch("toppts",            &toppts);

}

void lldjNtuple::fillGenPart(const edm::Event& e) {

  //Initialize -- set numbers to e.g. 0 and clear vectors 
  llpId.clear();
  llpStatus.clear();
  llpPt.clear();
  llpEta.clear();
  llpPhi.clear();
  llpMass.clear();
  llpDaughterId.clear();
  llpDaughterStatus.clear();
  llpDaughterPt.clear();
  llpDaughterEta.clear();
  llpDaughterPhi.clear();
  llpDaughterMass.clear();
  toppts.clear();

  //Gen particles handle
  edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
  e.getByToken(genParticlesCollection_, genParticlesHandle);

  //Loop over gen particles
  for (vector<reco::GenParticle>::const_iterator ip = genParticlesHandle->begin(); ip != genParticlesHandle->end(); ++ip) {
  
    reco::GenParticleRef partRef = reco::GenParticleRef(genParticlesHandle,
							ip-genParticlesHandle->begin());
    genpartparentage::GenParticleParentage particleHistory(partRef);
    
    //Save top particles
    if( abs(ip->pdgId()) == 6 && ip->isLastCopy() ){
     toppts.push_back( ip->pt() );
    }

    //Save long lived BSM particles
    if( abs(ip->pdgId()) == 9000006 ){
      llpId.push_back(      ip->pdgId() );
      llpStatus.push_back(  ip->status() );
      llpPt.push_back(      ip->pt()    );
      llpEta.push_back(     ip->eta()   );
      llpPhi.push_back(     ip->phi()   );
      llpMass.push_back(    ip->mass()  );
    }
    else if ( particleHistory.hasRealParent() ) {
      reco::GenParticleRef momRef = particleHistory.parent();
      if ( momRef.isNonnull() && momRef.isAvailable() ) {
	if( abs(momRef->pdgId()) == 9000006 ){
	  llpDaughterId.push_back(     ip->pdgId() );
	  llpDaughterStatus.push_back( ip->status() );
	  llpDaughterPt.push_back(     ip->pt()    );
	  llpDaughterEta.push_back(    ip->eta()   );
	  llpDaughterPhi.push_back(    ip->phi()   );
	  llpDaughterMass.push_back(   ip->mass()  );
	}
      }
    }

  }//end gen loop
  float TTSF = 1.;
  if(toppts.size() == 2){
   TTSF = TTSF * exp( 0.0615 - 0.0005*toppts.at(0)) * exp( 0.0615 - 0.0005*toppts.at(1));
  }
  hTTSF_->Fill( TTSF );
  //std::cout<<"TTSF   "<<TTSF<<std::endl;

}
