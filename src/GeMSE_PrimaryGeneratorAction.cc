#include "GeMSE_PrimaryGeneratorAction.hh"
#include "GeMSE_ParticleSource.hh"

#include <G4Event.hh>
#include <G4RunManagerKernel.hh>
#include <Randomize.hh>
#include <globals.hh>

GeMSE_PrimaryGeneratorAction::GeMSE_PrimaryGeneratorAction() {
  m_pParticleSource = new GeMSE_ParticleSource();

  m_hParticleTypeOfPrimary = "";
  m_dEnergyOfPrimary = 0.;
  m_hPositionOfPrimary = G4ThreeVector(0., 0., 0.);

  m_lSeeds[0] = -1;
  m_lSeeds[1] = -1;
}

GeMSE_PrimaryGeneratorAction::~GeMSE_PrimaryGeneratorAction() {
  delete m_pParticleSource;
}

void GeMSE_PrimaryGeneratorAction::GeneratePrimaries(G4Event *pEvent) {
  m_lSeeds[0] = *(CLHEP::HepRandom::getTheSeeds());
  m_lSeeds[1] = *(CLHEP::HepRandom::getTheSeeds() + 1);

  G4StackManager *pStackManager =
      (G4RunManagerKernel::GetRunManagerKernel())->GetStackManager();

  //    G4cout << "PrimaryGeneratorAction: track status: "
  //        << pStackManager->GetNUrgentTrack() << " urgent, "
  //        << pStackManager->GetNWaitingTrack() << " waiting, "
  //        << pStackManager->GetNPostponedTrack() << " postponed"
  //        << G4endl;

  if (!pStackManager->GetNPostponedTrack()) {
    m_pParticleSource->GeneratePrimaryVertex(pEvent);
  } else {
    pStackManager->TransferStackedTracks(fPostpone, fUrgent);
    G4VTrajectory *pTrajectory;
    G4Track *pTrack = pStackManager->PopNextTrack(&pTrajectory);

    m_pParticleSource->GeneratePrimaryVertexFromTrack(pTrack, pEvent);

    delete pTrack;
  }
  G4PrimaryVertex *pVertex = pEvent->GetPrimaryVertex();
  G4PrimaryParticle *pPrimaryParticle = pVertex->GetPrimary();

  m_hParticleTypeOfPrimary = pPrimaryParticle->GetG4code()->GetParticleName();

  G4double dP = pPrimaryParticle->GetMomentum().mag();
  G4double dMass = pPrimaryParticle->GetMass();

  m_dEnergyOfPrimary = std::sqrt(dP * dP + dMass * dMass) - dMass;
  m_hPositionOfPrimary = pVertex->GetPosition();
}
