#ifndef __GeMSE_PRIMARYGENERATORMESSENGER_H__
#define __GeMSE_PRIMARYGENERATORMESSENGER_H__

#include <globals.hh>

#include <G4UImessenger.hh>

class GeMSE_PrimaryGeneratorAction;

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class GeMSE_PrimaryGeneratorMessenger : public G4UImessenger {
 public:
  GeMSE_PrimaryGeneratorMessenger(
      GeMSE_PrimaryGeneratorAction *pPrimaryGeneratorAction);
  ~GeMSE_PrimaryGeneratorMessenger();

  void SetNewValue(G4UIcommand *pCommand, G4String hNewValues);

 private:
  GeMSE_PrimaryGeneratorAction *m_pPrimaryGeneratorAction;
  G4UIdirectory *m_pDirectory;
  G4UIcmdWithABool *m_pVarianceReductionCmd;
  G4UIcmdWithABool *m_pWriteEmptyCmd;
  G4UIcmdWithAnInteger *m_pVarianceReductionModeCmd;
  G4UIcmdWithADouble *p_survival_cutCmd;
  G4UIcmdWith3VectorAndUnit *ft_positionCmd;
  G4UIcmdWithADoubleAndUnit *ft_lengthCmd;
  G4UIcmdWithADoubleAndUnit *ft_radiusCmd;
};

#endif
