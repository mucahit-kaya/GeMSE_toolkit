#include "GeMSE_MVHit.hh"

#include "G4Circle.hh"
#include "G4Color.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"

G4Allocator <GeMSE_MVHit> GeMSE_MVHitAllocator;

GeMSE_MVHit::GeMSE_MVHit() {;}

GeMSE_MVHit::~GeMSE_MVHit() {;}

GeMSE_MVHit::GeMSE_MVHit(const GeMSE_MVHit& right) : G4VHit()
{
  edep = right.edep;
  pos = right.pos;
  particleID = right.particleID;
  trackID = right.trackID;
  panelNr = right.panelNr;
  particleEnergy = right.particleEnergy;
  time = right.time;
}

const GeMSE_MVHit& GeMSE_MVHit::operator=(const GeMSE_MVHit& right) {
  edep = right.edep;
  pos = right.pos;
  particleID = right.particleID;
  trackID = right.trackID;
  panelNr = right.panelNr;
  particleEnergy = right.particleEnergy;
  time = right.time;

  return *this;
}

G4int GeMSE_MVHit::operator==(const GeMSE_MVHit& right) const {
  return (this==&right) ? 1 : 0;
}

void GeMSE_MVHit::Draw() {
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager) {
    /*
    G4Circle circle(pos);
    circle.SetScreenSize(5);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,.5);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
    */
  }
}

void GeMSE_MVHit::Print() {
  /*
  G4cout << "  energy deposit: " << G4BestUnit(edep,"Energy")
         << "  time:" <<G4BestUnit(hit_time,"Time")
  */
}
