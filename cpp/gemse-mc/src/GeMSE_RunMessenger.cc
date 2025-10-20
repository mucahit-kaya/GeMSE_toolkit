#include "GeMSE_RunMessenger.hh"
#include "GeMSE_RunAction.hh"

#include "G4UIcmdWithADouble.hh"
#include "G4UIdirectory.hh"

#include "G4Run.hh"


GeMSE_RunMessenger::GeMSE_RunMessenger(GeMSE_Analysis* RunAnalysis)
    : fRunAnalysis(RunAnalysis) {
  runDirectory = new G4UIdirectory("/gammaline/");

  energyCmd = new G4UIcmdWithADouble("/gammaline/energy", this);
  G4BRCmd = new G4UIcmdWithADouble("/gammaline/G4BR", this);
  NuDatBRCmd = new G4UIcmdWithADouble("/gammaline/NuDatBR", this);
  SigRegionCmd = new G4UIcmdWithADouble("/gammaline/SigRegion", this);
  BkgRegionCmd = new G4UIcmdWithADouble("/gammaline/BkgRegion", this);
  energyCmd->SetDefaultValue(0.);
  G4BRCmd->SetDefaultValue(1.);
  NuDatBRCmd->SetDefaultValue(1.);
  SigRegionCmd->SetDefaultValue(0.4);
  BkgRegionCmd->SetDefaultValue(10.);
}

GeMSE_RunMessenger::~GeMSE_RunMessenger() {
  delete energyCmd;
  delete G4BRCmd;
  delete NuDatBRCmd;
  delete SigRegionCmd;
  delete BkgRegionCmd;
}

void GeMSE_RunMessenger::SetNewValue(G4UIcommand* command, G4String newValues) {
  if (command == energyCmd) {
    fRunAnalysis->AddEnergy(energyCmd->GetNewDoubleValue(newValues));
  } else if (command == G4BRCmd) {
    fRunAnalysis->AddG4BR(G4BRCmd->GetNewDoubleValue(newValues));
  } else if (command == NuDatBRCmd) {
    fRunAnalysis->AddNuDatBR(NuDatBRCmd->GetNewDoubleValue(newValues));
  } else if (command == SigRegionCmd) {
    fRunAnalysis->AddSigRegion(SigRegionCmd->GetNewDoubleValue(newValues));
  } else if (command == BkgRegionCmd) {
    fRunAnalysis->AddBkgRegion(BkgRegionCmd->GetNewDoubleValue(newValues));
  }
}
