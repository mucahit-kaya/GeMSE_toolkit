#ifndef __GeMSE_PrimaryGeneratorAction_H__
#define __GeMSE_PrimaryGeneratorAction_H__

#include <globals.hh>

#include <G4ThreeVector.hh>
#include <G4VUserPrimaryGeneratorAction.hh>

class GeMSE_ParticleSource;

class G4Event;

class GeMSE_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
 public:
  GeMSE_PrimaryGeneratorAction();
  ~GeMSE_PrimaryGeneratorAction();

 public:
  const long *GetEventSeeds() { return m_lSeeds; };
  const G4String &GetParticleTypeOfPrimary() {
    return m_hParticleTypeOfPrimary;
  };
  G4double GetEnergyOfPrimary() { return m_dEnergyOfPrimary; };
  G4ThreeVector GetPositionOfPrimary() { return m_hPositionOfPrimary; };

  const G4double &GetEnergyPrimary() {
    return m_dEnergyOfPrimary;
  };  // This is like the GetParticleTypeOfPrimary() but is used for version 1.0
      // and 1.1 compatibility

  void GeneratePrimaries(G4Event *pEvent);

 private:
  long m_lSeeds[2];
  G4String m_hParticleTypeOfPrimary;
  G4double m_dEnergyOfPrimary;
  G4ThreeVector m_hPositionOfPrimary;

  GeMSE_ParticleSource *m_pParticleSource;
};

#endif
