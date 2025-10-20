#ifndef GeMSE_MVSensitiveDetector_h
#define GeMSE_MVSensitiveDetector_h 1

#include "GeMSE_MVHit.hh"

#include "G4VSensitiveDetector.hh"

#include "TTree.h"
#include <vector>
#include <string>

class G4Step;
class G4HCofThisEvent;

class GeMSE_MVSensitiveDetector : public G4VSensitiveDetector {
  public:
   GeMSE_MVSensitiveDetector(G4String);
   ~GeMSE_MVSensitiveDetector();

   //! create an instance of GeMSE_MVHitsCollection and add a new hits collection
   //! to the G4HCofThisEvent instance
   void Initialize(G4HCofThisEvent*);

   G4bool ProcessHits(G4Step*, G4TouchableHistory*);

   void EndOfEvent(G4HCofThisEvent*);

   //! Return the number of Hits
   G4int getEntries();

  private:
   GeMSE_MVHitsCollection* HitsCollection;
   TTree* MuonHitTree;

   G4int EventID;
   G4int NHits;
   G4double TotEdep;

   int HCID;
};

#endif
