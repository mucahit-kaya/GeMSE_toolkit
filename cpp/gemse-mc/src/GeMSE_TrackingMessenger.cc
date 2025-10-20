#include "GeMSE_TrackingMessenger.hh"
#include "GeMSE_TrackingAction.hh"

#include "G4UIcmdWithABool.hh"

GeMSE_TrackingMessenger::GeMSE_TrackingMessenger(GeMSE_TrackingAction* tracking)
:Action(tracking)
{
  selectActionCmd = new G4UIcmdWithABool("writePrimaries",this);  
  selectActionCmd->SetDefaultValue(false);
}

GeMSE_TrackingMessenger::~GeMSE_TrackingMessenger()
{
  delete selectActionCmd;
}

void GeMSE_TrackingMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{ 
  if (command == selectActionCmd)
    Action->SelectAction(selectActionCmd->GetNewBoolValue(newValue));      
}
