#ifndef GeMSE_RunMessenger_h
#define GeMSE_RunMessenger_h 1

#include "GeMSE_Analysis.hh"

#include "globals.hh"

#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

class GeMSE_RunAction;
class G4UIcmdWithADouble;

class GeMSE_RunMessenger : public G4UImessenger {
 public:
  GeMSE_RunMessenger(GeMSE_Analysis* RunAnalysis);
  ~GeMSE_RunMessenger();

  void SetNewValue(G4UIcommand*, G4String);

 private:
  // GeMSE_Analysis* fRunAnalysis = new GeMSE_Analysis();
  GeMSE_Analysis* fRunAnalysis;

  G4UIdirectory* runDirectory;

  G4UIcmdWithADouble* energyCmd;
  G4UIcmdWithADouble* G4BRCmd;
  G4UIcmdWithADouble* NuDatBRCmd;
  G4UIcmdWithADouble* SigRegionCmd;
  G4UIcmdWithADouble* BkgRegionCmd;
};

#endif
