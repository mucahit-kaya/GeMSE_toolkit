#include "GeMSE_TrackingAction.hh"
#include "GeMSE_TrackingMessenger.hh"
#include "GeMSE_RunAction.hh"

#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"


GeMSE_TrackingAction::GeMSE_TrackingAction()
{
  //create a messenger for this class
  trackingMessenger = new GeMSE_TrackingMessenger(this); 
}

GeMSE_TrackingAction::~GeMSE_TrackingAction()
{
  delete trackingMessenger;
}

void GeMSE_TrackingAction::PreUserTrackingAction(const G4Track* theTrack)
{
  //G4cout << "Tracking active!!!!!" << G4endl;
  // Get pointer to the current RunAction instance
  run_action = (GeMSE_RunAction*)G4RunManager::GetRunManager()->GetUserRunAction();
  PrimariesTree = run_action->GetPrimariesTree();
}

void GeMSE_TrackingAction::PostUserTrackingAction(const G4Track* theTrack){
  const G4ParticleDefinition* particleDefinition =  theTrack->GetDefinition();
  
  if (theTrack->GetTrackID()==2
      && theTrack->GetCreatorProcess()->GetProcessName().find("RadioactiveDecay") != std::string::npos) {
    run_action->AddDecay();
  }

  //if(particleDefinition->GetParticleName() == "gamma")
  //  G4cout << "Gamma produced!!!!!" << G4endl;
  
  if(savePrimaries==true){
    //save the particle only after it has been tracked
    if(theTrack->GetTrackStatus()==fStopAndKill)
    {
      EventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
      TrackID = theTrack->GetTrackID();
      ParentID = theTrack->GetParentID();
      Ekin = theTrack->GetVertexKineticEnergy()/keV;
      G4ThreeVector VPos = theTrack->GetVertexPosition();
      xPriPos=VPos[0];
      yPriPos=VPos[1];
      zPriPos=VPos[2];
      G4ThreeVector VDir = theTrack->GetVertexMomentumDirection();
      xDir=VDir[0];
      yDir=VDir[1];
      zDir=VDir[2];
      ParticleID = new G4String(particleDefinition->GetParticleName());
      
      if(theTrack->GetCreatorProcess()!=0)
        CreatorProcess = new G4String(theTrack->GetCreatorProcess()->GetProcessName());
      else
        CreatorProcess = new G4String;
        
      PrimariesTree->SetBranchAddress("EventID", &EventID);
      PrimariesTree->SetBranchAddress("TrackID", &TrackID);
      PrimariesTree->SetBranchAddress("ParentID", &ParentID);
      PrimariesTree->SetBranchAddress("xPriPos", &xPriPos);
      PrimariesTree->SetBranchAddress("yPriPos", &yPriPos);
      PrimariesTree->SetBranchAddress("zPriPos", &zPriPos);
      PrimariesTree->SetBranchAddress("Ekin", &Ekin);
      PrimariesTree->SetBranchAddress("xDir", &xDir);
      PrimariesTree->SetBranchAddress("yDir", &yDir);
      PrimariesTree->SetBranchAddress("zDir", &zDir);
      PrimariesTree->SetBranchAddress("ParticleID", &ParticleID);
      PrimariesTree->SetBranchAddress("CreatorProcess", &CreatorProcess);
        
      PrimariesTree->Fill();
    }
  }
}
