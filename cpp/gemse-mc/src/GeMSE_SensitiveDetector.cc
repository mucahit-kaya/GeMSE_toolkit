#include "GeMSE_SensitiveDetector.hh"
#include "GeMSE_DetectorConstruction.hh"
#include "GeMSE_Hit.hh"
#include "GeMSE_RunAction.hh"
#include "GeMSE_PrimaryGeneratorAction.hh"

#include "TROOT.h"
#include "TFile.h"
#include "TBranch.h"
using namespace std;

#include "G4HCofThisEvent.hh"
#include "G4ThreeVector.hh"
#include "G4EventManager.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4THitsCollection.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4ios.hh"

GeMSE_SensitiveDetector::GeMSE_SensitiveDetector(G4String name)
    : G4VSensitiveDetector(name), HCID(-1) {
  collectionName.insert("GeHitsCollection");
}

GeMSE_SensitiveDetector::~GeMSE_SensitiveDetector() {}

void GeMSE_SensitiveDetector::Initialize(G4HCofThisEvent*) {
  HitsCollection =
      new GeMSE_HitsCollection(SensitiveDetectorName, collectionName[0]);

  GeMSE_RunAction* runAction =
      (GeMSE_RunAction*)G4RunManager::GetRunManager()
          ->GetUserRunAction();  // get pointer to RunAction

  fhTotEdep =
      runAction->GetRunAnalysis()->GetHisto();  // get pointer to histogram

  GeHitTree = runAction->GetGeHitTree(); //get name of results tree
}

G4bool GeMSE_SensitiveDetector::ProcessHits(G4Step* aStep,
                                            G4TouchableHistory* ROhist) {
  G4double edep = aStep->GetTotalEnergyDeposit();
  G4ParticleDefinition* particleType = aStep->GetTrack()->GetDefinition();  

  if (edep == 0.) return false;

  GeMSE_Hit* newHit = new GeMSE_Hit();
  newHit->SetTrack(aStep->GetTrack()->GetTrackID());
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  newHit->SetTime(aStep->GetPreStepPoint()->GetGlobalTime());
  newHit->SetParticle(particleType->GetPDGEncoding());
  newHit->SetParticleEnergy(aStep->GetPreStepPoint()->GetKineticEnergy());

  HitsCollection->insert(newHit);

  return true;
}

void GeMSE_SensitiveDetector::EndOfEvent(G4HCofThisEvent* HCE) {
  if (HCID < 0)
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

  // gather info on hits
  for (int i=0; i<n_hits; i++) {
    G4double edep = (*HitsCollection)[i]->GetEdep() / keV;
    G4ThreeVector Pos=(*HitsCollection)[i]->GetPos()/mm;
    Edep->push_back(edep);
    xPos->push_back(Pos[0]);
    yPos->push_back(Pos[1]);
    zPos->push_back(Pos[2]);
    Time->push_back((*HitsCollection)[i]->GetTime()/ns);
    ParticleID->push_back((*HitsCollection)[i]->GetParticle());
    TrackID->push_back((*HitsCollection)[i]->GetTrack());
    Ekin->push_back((*HitsCollection)[i]->GetParticleEnergy()/keV);
    
    totalEdep += edep;  // sum up the edep
  }

  // fill histogram
  if (totalEdep > 0) {    
    GeHitTree->SetBranchAddress("EventID", &EventID);
    GeHitTree->SetBranchAddress("NHits", &n_hits);
    GeHitTree->SetBranchAddress("TotEdep", &totalEdep);
    GeHitTree->SetBranchAddress("Edep", &Edep);
    GeHitTree->SetBranchAddress("xPos", &xPos);
    GeHitTree->SetBranchAddress("yPos", &yPos);
    GeHitTree->SetBranchAddress("zPos", &zPos);
    GeHitTree->SetBranchAddress("Time", &Time);
    GeHitTree->SetBranchAddress("ParticleID", &ParticleID);
    GeHitTree->SetBranchAddress("TrackID", &TrackID);
    GeHitTree->SetBranchAddress("Ekin", &Ekin);

    GeHitTree->Fill();

    fhTotEdep->Fill(totalEdep);
  }

  if (EventID % 1000 == 0)
    G4cout << "\rSimulating Event Nr.: " << EventID << std::flush;

  delete Edep;
  delete Ekin;
  delete Time;
  delete xPos;
  delete yPos;
  delete zPos;
  delete ParticleID;
  delete TrackID;
}
