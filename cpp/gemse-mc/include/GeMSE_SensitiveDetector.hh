#ifndef GeMSE_SensitiveDetector_h
#define GeMSE_SensitiveDetector_h 1

#include "GeMSE_Hit.hh"

#include "G4VSensitiveDetector.hh"

#include <TH1D.h>
#include "TTree.h"
#include <vector>
#include <string>

class G4Step;
class G4HCofThisEvent;

class GeMSE_SensitiveDetector : public G4VSensitiveDetector {
 public:
  GeMSE_SensitiveDetector(G4String);
  ~GeMSE_SensitiveDetector();

  //! create an instance of GeMSE_HitsCollection and add a new hits collection
  //! to the G4HCofThisEvent instance
  void Initialize(G4HCofThisEvent*);

  G4bool ProcessHits(G4Step*, G4TouchableHistory*);

  void EndOfEvent(G4HCofThisEvent*);

 private:
  GeMSE_HitsCollection* HitsCollection;
  TTree* GeHitTree;

  G4int EventID;
  G4int NHits;
  G4double TotEdep;

  int HCID;
  TH1D* fhTotEdep;
};

#endif
