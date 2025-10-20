#ifndef __GeMSE_ParticleSourceMESSENGER_H__
#define __GeMSE_ParticleSourceMESSENGER_H__

#include <globals.hh>
#include <G4UImessenger.hh>

class GeMSE_ParticleSource;

class G4ParticleTable;
class G4IonTable;
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

class GeMSE_ParticleSourceMessenger : public G4UImessenger {
 public:
  GeMSE_ParticleSourceMessenger(GeMSE_ParticleSource *pParticleSource);
  ~GeMSE_ParticleSourceMessenger();

  void SetNewValue(G4UIcommand *pCommand, G4String hNewValues);

 private:
  GeMSE_ParticleSource *m_pParticleSource;
  G4ParticleTable *m_pParticleTable;
  G4IonTable *m_pIonTable;
  G4UIdirectory *m_pDirectory;

  G4UIcmdWithAString *m_pGeneratorCmd;
  G4UIcmdWithAString *m_pTypeCmd;
  G4UIcmdWithAString *m_pShapeCmd;
  G4UIcmdWith3VectorAndUnit *m_pCenterCmd;
  G4UIcmdWithADoubleAndUnit *m_pHalfxCmd;
  G4UIcmdWithADoubleAndUnit *m_pHalfyCmd;
  G4UIcmdWithADoubleAndUnit *m_pHalfzCmd;
  G4UIcmdWithADoubleAndUnit *m_pRadiusCmd;
  G4UIcmdWithAString *m_pConfineCmd;
  G4UIcmdWithAString *m_pAngTypeCmd;
  G4UIcmdWithAString *m_pEnergyTypeCmd;
  G4UIcmdWithAString *m_pEnergyFileCmd;
  G4UIcmdWithAnInteger *m_pVerbosityCmd;
  G4UIcommand *m_pIonCmd;
  G4UIcmdWithAString *m_pParticleCmd;
  G4UIcmdWith3VectorAndUnit *m_pPositionCmd;
  G4UIcmdWith3Vector *m_pDirectionCmd;
  G4UIcmdWithADoubleAndUnit *m_pEnergyCmd;
  G4UIcmdWithoutParameter *m_pListCmd;

  G4bool m_bShootIon;
  G4int m_iAtomicNumber;
  G4int m_iAtomicMass;
  G4int m_iIonCharge;
  G4double m_dIonExciteEnergy;
};

#endif
