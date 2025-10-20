#ifndef __GeMSE_ParticleSource_H__
#define __GeMSE_ParticleSource_H__

#include "GeMSE_ParticleSourceMessenger.hh"

#include <set>
#include "TH1.h"

#include <G4Navigator.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleMomentum.hh>
#include <G4Track.hh>
#include <G4VPrimaryGenerator.hh>

using std::set;

class GeMSE_ParticleSource : public G4VPrimaryGenerator {
 public:
  GeMSE_ParticleSource();
  ~GeMSE_ParticleSource();

 public:
  void GeneratePrimaryVertex(G4Event *pEvent);
  void GeneratePrimaryVertexFromTrack(G4Track *pTrack, G4Event *pEvent);

  void SetGeneratorType(G4String hGenerator) {
    m_hGenerator = hGenerator;
  }
  void SetPosDisType(G4String hSourcePosType) {
    m_hSourcePosType = hSourcePosType;
  }
  void SetPosDisShape(G4String hShape) { m_hShape = hShape; }
  void SetCenterCoords(G4ThreeVector hCenterCoords) {
    m_hCenterCoords = hCenterCoords;
  }
  void SetHalfX(G4double dHalfx) { m_dHalfx = dHalfx; }
  void SetHalfY(G4double dHalfy) { m_dHalfy = dHalfy; }
  void SetHalfZ(G4double dHalfz) { m_dHalfz = dHalfz; }
  void SetRadius(G4double dRadius) { m_dRadius = dRadius; }

  void SetAngDistType(G4String hAngDistType) { m_hAngDistType = hAngDistType; }
  void SetParticleMomentumDirection(G4ParticleMomentum hMomentum) {
    m_hParticleMomentumDirection = hMomentum.unit();
  }

  void SetEnergyDisType(G4String hEnergyDisType) {
    m_hEnergyDisType = hEnergyDisType;
  }
  void SetEnergyFile(G4String hEnergyFile);
  void SetMonoEnergy(G4double dMonoEnergy) { m_dMonoEnergy = dMonoEnergy; }

  void SetParticleDefinition(G4ParticleDefinition *pParticleDefinition);
  inline void SetParticleCharge(G4double dCharge) {
    m_dParticleCharge = dCharge;
  }

  void SetVerbosity(G4int iVerbosityLevel) {
    m_iVerbosityLevel = iVerbosityLevel;
  }

  const G4String &GetParticleType() {
    return m_pParticleDefinition->GetParticleName();
  }
  G4double GetParticleEnergy() { return m_dParticleEnergy; }
  const G4ThreeVector &GetParticlePosition() { return m_hParticlePosition; }

  G4bool ReadEnergySpectrum();
  void GeneratePointSource();
  void GeneratePointsInVolume();
  G4bool IsSourceConfined();
  void ConfineSourceToVolume(G4String);

  void GenerateIsotropicFlux();

  void GenerateMonoEnergetic();
  void GenerateEnergyFromSpectrum();

  void SetRandomSpherePos();

 private:
  G4String m_hGenerator; 
  G4String m_hSourcePosType;
  G4String m_hShape;
  G4ThreeVector m_hCenterCoords;
  G4double m_dHalfx;
  G4double m_dHalfy;
  G4double m_dHalfz;
  G4double m_dRadius;
  G4bool m_bConfine;
  set<G4String> m_hVolumeNames;
  G4String m_hAngDistType;
  G4double m_dMinTheta, m_dMaxTheta, m_dMinPhi, m_dMaxPhi;
  G4double m_dTheta, m_dPhi;
  G4String m_hEnergyDisType;
  G4String m_hEnergyFile;
  G4double m_dMonoEnergy;

  G4int m_iNumberOfParticlesToBeGenerated;
  G4ParticleDefinition *m_pParticleDefinition;
  G4ParticleMomentum m_hParticleMomentumDirection;
  G4double m_dParticleEnergy;
  G4double m_dParticleCharge;
  G4ThreeVector m_hParticlePosition;
  G4double m_dParticleTime;
  G4ThreeVector m_hParticlePolarization;

  G4int m_iVerbosityLevel;
  TH1D m_hEnergySpectrum;

  GeMSE_ParticleSourceMessenger *m_pMessenger;
  G4Navigator *m_pNavigator;

  G4double pi = 3.1415926;
  G4double twopi = 2 * pi;
};

#endif
