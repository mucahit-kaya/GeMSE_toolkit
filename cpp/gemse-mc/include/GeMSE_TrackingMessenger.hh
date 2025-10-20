#ifndef GeMSE_TrackingMessenger_h
#define GeMSE_TrackingMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class GeMSE_TrackingAction;
class G4UIcmdWithABool;

class GeMSE_TrackingMessenger: public G4UImessenger
{
  public:
    GeMSE_TrackingMessenger(GeMSE_TrackingAction*);
    ~GeMSE_TrackingMessenger();

    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    GeMSE_TrackingAction* Action;
    
    G4UIcmdWithABool* selectActionCmd;
};

#endif
