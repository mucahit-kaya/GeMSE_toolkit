#include "GeMSE_DetectorConstruction.hh"
#include "GeMSE_PhysicsList.hh"
#include "GeMSE_PrimaryGeneratorAction.hh"
#include "GeMSE_RunAction.hh"
#include "GeMSE_TrackingAction.hh"
//#include "GeMSE_SensitiveDetector.hh"

//#include <Randomize.hh>
#include <TCanvas.h>
#include <TFile.h>
#include <TString.h>
#include <TSystem.h>
#include <TTree.h>
#include <getopt.h>
#include <time.h>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UItcsh.hh"
#include "G4UIterminal.hh"
#include "G4VisExecutive.hh"
#include "G4ios.hh"


int main(int argc, char** argv)
{
  std::string git_tag = "2.0.0";
  G4cout << G4endl << "Welcome to GeMSE_MC version " << git_tag.c_str()
         << G4endl;

  // User Verbose output class
  //
  /*G4VSteppingVerbose* verbosity = new GeMSE_SteppingVerbose;
  G4VSteppingVerbose::SetInstance(verbosity);*/
  //-----------------------------

  int c = 0;
  bool Macro = false;
  G4String MacroFilename;
  G4String GeometryFilename = "src/worldVolume.txt";
  G4String OutputFolder = "";

  while ((c = getopt(argc, argv, "m:o:g:")) != -1) {
    switch (c) {
      case 'm':
        Macro = true;
        MacroFilename = optarg;
        break;

      case 'g':
        GeometryFilename = optarg;
        break;

      case 'o':
        OutputFolder = optarg;
        break;
    }
  }
  
  // Check if output folder was specified
  if (OutputFolder == "") {
    G4cout << "\n######"
           << "\n###### WARNING: no folder specified, no output will be written "
           << "\n######" << G4endl;
    sleep(1.5);
  }

  // Run manager
  G4RunManager* runManager = new G4RunManager;

  // UserInitialization classes - mandatory
  G4VUserDetectorConstruction* detector =
      new GeMSE_DetectorConstruction(GeometryFilename);
  runManager->SetUserInitialization(detector);

  G4VUserPhysicsList* physics = new GeMSE_PhysicsList;
  runManager->SetUserInitialization(physics);

  // Visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // UserAction classes
  GeMSE_RunAction* run_action = new GeMSE_RunAction(OutputFolder);
  runManager->SetUserAction(run_action);
  run_action->SetVersionTag(git_tag);

  GeMSE_PrimaryGeneratorAction* gen_action = new GeMSE_PrimaryGeneratorAction;
  runManager->SetUserAction(gen_action);
  
  G4UserTrackingAction* track_action = new GeMSE_TrackingAction;
    runManager->SetUserAction(track_action);

  // Initialize G4 kernel
  runManager->Initialize();

  // Shell & Visualization
  if (!Macro) {
    // Define UI session for interactive mode
    G4UIsession* session = new G4UIterminal();
    session->SessionStart();
    delete session;
  }
  else {
    // Get the pointer to the User Interface manager
    G4UImanager* UI = G4UImanager::GetUIpointer();
    G4String command = "/control/execute " + MacroFilename;
    UI->ApplyCommand(command);
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  G4cout << "\n";
  delete visManager;
  delete runManager;
  //delete verbosity;

  return 0;
}
