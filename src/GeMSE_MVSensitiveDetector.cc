#include "GeMSE_MVSensitiveDetector.hh"
#include "GeMSE_MVHit.hh"
#include "GeMSE_DetectorConstruction.hh"
#include "GeMSE_RunAction.hh"
#include "GeMSE_PrimaryGeneratorAction.hh"

#include "TROOT.h"
#include "TFile.h"
#include "TBranch.h"
using namespace std;

#include "G4HCofThisEvent.hh"
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4THitsCollection.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

GeMSE_MVSensitiveDetector::GeMSE_MVSensitiveDetector(G4String name)
:G4VSensitiveDetector(name), HCID(-1) {
  collectionName.insert("GeMSE_MVHitsCollection");
}

GeMSE_MVSensitiveDetector::~GeMSE_MVSensitiveDetector(){}

void GeMSE_MVSensitiveDetector::Initialize(G4HCofThisEvent* ) {
  HitsCollection =
      new GeMSE_MVHitsCollection(SensitiveDetectorName,collectionName[0]);

  GeMSE_RunAction* runAction =
    (GeMSE_RunAction*) G4RunManager::GetRunManager()->GetUserRunAction();
    //get pointer to RunAction

  MuonHitTree = runAction->GetMuonHitTree(); //get name of results tree
}

G4bool GeMSE_MVSensitiveDetector::ProcessHits(G4Step* aStep,
                                              G4TouchableHistory* ROhist){
  G4double edep = aStep->GetTotalEnergyDeposit();
  G4ParticleDefinition* particleType = aStep->GetTrack()->GetDefinition();
  G4String PanelName = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
  G4int panelNr=-1;

  if(edep==0.) return false;

  if (PanelName=="muonveto_panel_top")
    panelNr=0;
  else if (PanelName=="muonveto_panel_back")
    panelNr=1;
  else
    G4cout << "WARNING: Hit in unknown volume named " << PanelName << G4endl;

  GeMSE_MVHit* newHit = new GeMSE_MVHit();
  newHit->SetTrack(aStep->GetTrack()->GetTrackID());
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  newHit->SetTime(aStep->GetPreStepPoint()->GetGlobalTime());
  newHit->SetParticle(particleType->GetPDGEncoding());
  newHit->SetParticleEnergy(aStep->GetPreStepPoint()->GetKineticEnergy() );
  newHit->SetPanelNr(panelNr);

  HitsCollection->insert( newHit );

  return true;
}

void GeMSE_MVSensitiveDetector::EndOfEvent(G4HCofThisEvent* HCE) {
  if (HCID<0)
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

  HCE->AddHitsCollection(HCID, HitsCollection);

  G4double totalEdep = 0.;
  EventID =
      G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
  G4int n_hits = HitsCollection->entries();

  vector<double>* Edep = new vector<double>;
  vector<double>* Ekin = new vector<double>;
  vector<double>* Time = new vector<double>;
  vector<double>* xPos = new vector<double>;
  vector<double>* yPos = new vector<double>;
  vector<double>* zPos = new vector<double>;
  vector<int>* ParticleID = new vector<int>;
  vector<int>* TrackID = new vector<int>;
  vector<int>* PanelNr = new vector<int>;
    
  // gather info on hits 
  for(int i=0; i<n_hits; i++){ 
    G4double edep=(*HitsCollection)[i]->GetEdep()/keV;
    G4ThreeVector Pos=(*HitsCollection)[i]->GetPos()/mm;
    Edep->push_back(edep);
    xPos->push_back(Pos[0]);
    yPos->push_back(Pos[1]);
    zPos->push_back(Pos[2]);
    Time->push_back((*HitsCollection)[i]->GetTime()/ns);
    ParticleID->push_back((*HitsCollection)[i]->GetParticle());
    TrackID->push_back((*HitsCollection)[i]->GetTrack());
    PanelNr->push_back((*HitsCollection)[i]->GetPanelNr());
    Ekin->push_back((*HitsCollection)[i]->GetParticleEnergy()/keV);

    totalEdep+=edep; //sum up the edep
   }

  if (totalEdep>0) {
    MuonHitTree->SetBranchAddress("EventID", &EventID);
    MuonHitTree->SetBranchAddress("NHits", &n_hits);
    MuonHitTree->SetBranchAddress("TotEdep", &totalEdep);
    
    MuonHitTree->SetBranchAddress("Edep", &Edep);
    MuonHitTree->SetBranchAddress("xPos", &xPos);
    MuonHitTree->SetBranchAddress("yPos", &yPos);
    MuonHitTree->SetBranchAddress("zPos", &zPos);
    MuonHitTree->SetBranchAddress("Time", &Time);
    MuonHitTree->SetBranchAddress("ParticleID", &ParticleID);
    MuonHitTree->SetBranchAddress("TrackID", &TrackID);
    MuonHitTree->SetBranchAddress("PanelNr", &PanelNr);
    MuonHitTree->SetBranchAddress("Ekin", &Ekin);
    
    MuonHitTree->Fill();
  }

  delete Edep;
  delete Ekin;
  delete Time;
  delete xPos;
  delete yPos;
  delete zPos;
  delete ParticleID;
  delete TrackID;
  delete PanelNr;
}
