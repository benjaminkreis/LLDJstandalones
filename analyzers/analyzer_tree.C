#include "analyzer_tree.h"

//----------------------------analyzer_tree
analyzer_tree::analyzer_tree() 
{
}

//----------------------------~analyzer_tree
analyzer_tree::~analyzer_tree()
{
}


//----------------------------setOPTtree
void analyzer_tree::setOPTtree(){

  OPT_Event.push_back(event);
  OPT_EventWeight.push_back(event_weight);
  OPT_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      OPT_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      OPT_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      OPT_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      OPT_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      OPT_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    OPT_AODCaloJetMedianLog10IPSig      .push_back(-5);
    OPT_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    OPT_AODCaloJetAlphaMax              .push_back(-5);
    OPT_AODCaloJetEta                   .push_back(-99);
    OPT_AODCaloJetPt                    .push_back(-99);
  }

}

//----------------------------clearOPTtree
void analyzer_tree::clearOPTtree(){

  //clear optimization arrays each new event
  OPT_Event                           .clear();
  OPT_EventWeight                     .clear();
  OPT_nJets                           .clear();
  OPT_AODCaloJetMedianLog10IPSig      .clear();
  OPT_AODCaloJetMedianLog10TrackAngle .clear();
  OPT_AODCaloJetAlphaMax              .clear();
  OPT_AODCaloJetEta                   .clear();
  OPT_AODCaloJetPt                    .clear();

}

void analyzer_tree::setOPTCRHeavytree(){

  OPTCRHeavy_Event.push_back(event);
  OPTCRHeavy_EventWeight.push_back(event_weight);
  OPTCRHeavy_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      OPTCRHeavy_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      OPTCRHeavy_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      OPTCRHeavy_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      OPTCRHeavy_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      OPTCRHeavy_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    OPTCRHeavy_AODCaloJetMedianLog10IPSig      .push_back(-5);
    OPTCRHeavy_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    OPTCRHeavy_AODCaloJetAlphaMax              .push_back(-5);
    OPTCRHeavy_AODCaloJetEta                   .push_back(-99);
    OPTCRHeavy_AODCaloJetPt                    .push_back(-99);
  }

}

void analyzer_tree::clearOPTCRHeavytree(){
  OPTCRHeavy_Event                           .clear();
  OPTCRHeavy_EventWeight                     .clear();
  OPTCRHeavy_nJets                           .clear();
  OPTCRHeavy_AODCaloJetMedianLog10IPSig      .clear();
  OPTCRHeavy_AODCaloJetMedianLog10TrackAngle .clear();
  OPTCRHeavy_AODCaloJetAlphaMax              .clear();
  OPTCRHeavy_AODCaloJetEta                   .clear();
  OPTCRHeavy_AODCaloJetPt                    .clear();

}

void analyzer_tree::setOPTCRLighttree(){

  OPTCRLight_Event.push_back(event);
  OPTCRLight_EventWeight.push_back(event_weight);
  OPTCRLight_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      OPTCRLight_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      OPTCRLight_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      OPTCRLight_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      OPTCRLight_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      OPTCRLight_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    OPTCRLight_AODCaloJetMedianLog10IPSig      .push_back(-5);
    OPTCRLight_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    OPTCRLight_AODCaloJetAlphaMax              .push_back(-5);
    OPTCRLight_AODCaloJetEta                   .push_back(-99);
    OPTCRLight_AODCaloJetPt                    .push_back(-99);
  }

}

void analyzer_tree::clearOPTCRLighttree(){

  OPTCRLight_Event                           .clear();
  OPTCRLight_EventWeight                     .clear();
  OPTCRLight_nJets                           .clear();
  OPTCRLight_AODCaloJetMedianLog10IPSig      .clear();
  OPTCRLight_AODCaloJetMedianLog10TrackAngle .clear();
  OPTCRLight_AODCaloJetAlphaMax              .clear();
  OPTCRLight_AODCaloJetEta                   .clear();
  OPTCRLight_AODCaloJetPt                    .clear();

}

void analyzer_tree::setOPTMuZHtree(){

  OPTMuZH_Event.push_back(event);
  OPTMuZH_EventWeight.push_back(event_weight);
  OPTMuZH_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      OPTMuZH_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      OPTMuZH_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      OPTMuZH_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      OPTMuZH_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      OPTMuZH_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    OPTMuZH_AODCaloJetMedianLog10IPSig      .push_back(-5);
    OPTMuZH_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    OPTMuZH_AODCaloJetAlphaMax              .push_back(-5);
    OPTMuZH_AODCaloJetEta                   .push_back(-99);
    OPTMuZH_AODCaloJetPt                    .push_back(-99);
  }

}

void analyzer_tree::clearOPTMuZHtree(){

  OPTMuZH_Event                           .clear();
  OPTMuZH_EventWeight                     .clear();
  OPTMuZH_nJets                           .clear();
  OPTMuZH_AODCaloJetMedianLog10IPSig      .clear();
  OPTMuZH_AODCaloJetMedianLog10TrackAngle .clear();
  OPTMuZH_AODCaloJetAlphaMax              .clear();
  OPTMuZH_AODCaloJetEta                   .clear();
  OPTMuZH_AODCaloJetPt                    .clear();

}

void analyzer_tree::setOPTEleZHtree(){

  OPTEleZH_Event.push_back(event);
  OPTEleZH_EventWeight.push_back(event_weight);
  OPTEleZH_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      OPTEleZH_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      OPTEleZH_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      OPTEleZH_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      OPTEleZH_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      OPTEleZH_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    OPTEleZH_AODCaloJetMedianLog10IPSig      .push_back(-5);
    OPTEleZH_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    OPTEleZH_AODCaloJetAlphaMax              .push_back(-5);
    OPTEleZH_AODCaloJetEta                   .push_back(-99);
    OPTEleZH_AODCaloJetPt                    .push_back(-99);
  }

}

void analyzer_tree::clearOPTEleZHtree(){

  OPTEleZH_Event                           .clear();
  OPTEleZH_EventWeight                     .clear();
  OPTEleZH_nJets                           .clear();
  OPTEleZH_AODCaloJetMedianLog10IPSig      .clear();
  OPTEleZH_AODCaloJetMedianLog10TrackAngle .clear();
  OPTEleZH_AODCaloJetAlphaMax              .clear();
  OPTEleZH_AODCaloJetEta                   .clear();
  OPTEleZH_AODCaloJetPt                    .clear();

}


//-----------------------------NM1 Tree stuff
void analyzer_tree::setNM1tree(){

  NM1_Event.push_back(event);
  NM1_EventWeight.push_back(event_weight);
  NM1_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1_AODCaloJetAlphaMax              .push_back(-5);
    NM1_AODCaloJetEta                   .push_back(-99);
    NM1_AODCaloJetPt                    .push_back(-99);
  }

}

//----------------------------clearNM1tree
void analyzer_tree::clearNM1tree(){

  //clear arrays each new event
  NM1_Event                           .clear();
  NM1_EventWeight                     .clear();
  NM1_nJets                           .clear();
  NM1_AODCaloJetMedianLog10IPSig      .clear();
  NM1_AODCaloJetMedianLog10TrackAngle .clear();
  NM1_AODCaloJetAlphaMax              .clear();
  NM1_AODCaloJetEta                   .clear();
  NM1_AODCaloJetPt                    .clear();

}

void analyzer_tree::setNM1CRHeavytree(){

  NM1CRHeavy_Event.push_back(event);
  NM1CRHeavy_EventWeight.push_back(event_weight);
  NM1CRHeavy_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1CRHeavy_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1CRHeavy_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1CRHeavy_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1CRHeavy_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1CRHeavy_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1CRHeavy_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1CRHeavy_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1CRHeavy_AODCaloJetAlphaMax              .push_back(-5);
    NM1CRHeavy_AODCaloJetEta                   .push_back(-99);
    NM1CRHeavy_AODCaloJetPt                    .push_back(-99);
  }

}

void analyzer_tree::clearNM1CRHeavytree(){

  NM1CRHeavy_Event                           .clear();
  NM1CRHeavy_EventWeight                     .clear();
  NM1CRHeavy_nJets                           .clear();
  NM1CRHeavy_AODCaloJetMedianLog10IPSig      .clear();
  NM1CRHeavy_AODCaloJetMedianLog10TrackAngle .clear();
  NM1CRHeavy_AODCaloJetAlphaMax              .clear();
  NM1CRHeavy_AODCaloJetEta                   .clear();
  NM1CRHeavy_AODCaloJetPt                    .clear();

}

void analyzer_tree::setNM1CRLighttree(){

  NM1CRLight_Event.push_back(event);
  NM1CRLight_EventWeight.push_back(event_weight);
  NM1CRLight_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1CRLight_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1CRLight_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1CRLight_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1CRLight_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1CRLight_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1CRLight_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1CRLight_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1CRLight_AODCaloJetAlphaMax              .push_back(-5);
    NM1CRLight_AODCaloJetEta                   .push_back(-99);
    NM1CRLight_AODCaloJetPt                    .push_back(-99);
  }

}

void analyzer_tree::clearNM1CRLighttree(){

  NM1CRLight_Event                           .clear();
  NM1CRLight_EventWeight                     .clear();
  NM1CRLight_nJets                           .clear();
  NM1CRLight_AODCaloJetMedianLog10IPSig      .clear();
  NM1CRLight_AODCaloJetMedianLog10TrackAngle .clear();
  NM1CRLight_AODCaloJetAlphaMax              .clear();
  NM1CRLight_AODCaloJetEta                   .clear();
  NM1CRLight_AODCaloJetPt                    .clear();

}

void analyzer_tree::setNM1MuZHtree(){

  NM1MuZH_Event.push_back(event);
  NM1MuZH_EventWeight.push_back(event_weight);
  NM1MuZH_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1MuZH_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1MuZH_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1MuZH_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1MuZH_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1MuZH_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1MuZH_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1MuZH_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1MuZH_AODCaloJetAlphaMax              .push_back(-5);
    NM1MuZH_AODCaloJetEta                   .push_back(-99);
    NM1MuZH_AODCaloJetPt                    .push_back(-99);
  }

}

void analyzer_tree::clearNM1MuZHtree(){

  NM1MuZH_Event                           .clear();
  NM1MuZH_EventWeight                     .clear();
  NM1MuZH_nJets                           .clear();
  NM1MuZH_AODCaloJetMedianLog10IPSig      .clear();
  NM1MuZH_AODCaloJetMedianLog10TrackAngle .clear();
  NM1MuZH_AODCaloJetAlphaMax              .clear();
  NM1MuZH_AODCaloJetEta                   .clear();
  NM1MuZH_AODCaloJetPt                    .clear();

}

void analyzer_tree::setNM1EleZHtree(){

  NM1EleZH_Event.push_back(event);
  NM1EleZH_EventWeight.push_back(event_weight);
  NM1EleZH_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1EleZH_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1EleZH_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1EleZH_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1EleZH_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1EleZH_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1EleZH_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1EleZH_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1EleZH_AODCaloJetAlphaMax              .push_back(-5);
    NM1EleZH_AODCaloJetEta                   .push_back(-99);
    NM1EleZH_AODCaloJetPt                    .push_back(-99);
  }

}

void analyzer_tree::clearNM1EleZHtree(){

  NM1EleZH_Event                           .clear();
  NM1EleZH_EventWeight                     .clear();
  NM1EleZH_nJets                           .clear();
  NM1EleZH_AODCaloJetMedianLog10IPSig      .clear();
  NM1EleZH_AODCaloJetMedianLog10TrackAngle .clear();
  NM1EleZH_AODCaloJetAlphaMax              .clear();
  NM1EleZH_AODCaloJetEta                   .clear();
  NM1EleZH_AODCaloJetPt                    .clear();

}

