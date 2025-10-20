#ifndef __GeMSE_PHYSICSLIST_H__
#define __GeMSE_PHYSICSLIST_H__

#include "G4VModularPhysicsList.hh"

#include "globals.hh"

#include <vector>
using namespace std;

class GeMSE_PhysicsList : public G4VModularPhysicsList {
 public:
  GeMSE_PhysicsList();
  virtual ~GeMSE_PhysicsList();

 public:
  void SetCuts();

 private:
  G4VPhysicsConstructor *GeG4OpticalPhysics;

  G4double defaultCutValue;
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForProton;
  G4double cutForAlpha;
  G4double cutForGenericIon;

  G4int VerboseLevel;
  // G4String physRootFile;
};
#endif
