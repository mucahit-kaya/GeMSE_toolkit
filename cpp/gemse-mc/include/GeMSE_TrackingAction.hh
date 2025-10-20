#ifndef GeMSE_TrackingAction_h
#define GeMSE_TrackingAction_h 1

#include "GeMSE_RunAction.hh"

#include "G4UserTrackingAction.hh"
#include "G4ThreeVector.hh"

#include "globals.hh"
#include "TTree.h"
#include <string>

using std::string;

class GeMSE_TrackingMessenger;

class GeMSE_TrackingAction : public G4UserTrackingAction
{
  public:
    GeMSE_TrackingAction();
    virtual ~GeMSE_TrackingAction();
    
    virtual void PreUserTrackingAction(const G4Track* theTrack);
    virtual void PostUserTrackingAction(const G4Track*);
    
    void SelectAction(G4bool boolean) { savePrimaries = boolean; };
    G4bool GetSelectedAction() { return savePrimaries; }; 

  private:
    G4int EventID;
    G4int TrackID;
    G4int ParentID;
    G4double xPriPos;
    G4double yPriPos;
    G4double zPriPos;
    G4double Ekin;
    G4double xDir;
    G4double yDir;
    G4double zDir;
    string* ParticleID;
    string* CreatorProcess;

    TTree* PrimariesTree;

    G4bool savePrimaries;
    GeMSE_TrackingMessenger* trackingMessenger;
    GeMSE_RunAction* run_action;
};

#endif 
