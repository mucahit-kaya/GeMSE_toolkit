#ifndef GeMSE_MVHit_h
#define GeMSE_MVHit_h 1

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

class GeMSE_MVHit : public G4VHit {
 public:
  GeMSE_MVHit();
  ~GeMSE_MVHit();
  GeMSE_MVHit(const GeMSE_MVHit&);
  const GeMSE_MVHit& operator=(const GeMSE_MVHit&);
  G4int operator==(const GeMSE_MVHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  void Draw();
  void Print();

 public:
  void SetEdep(G4double de) { edep = de; };
  void SetPos(G4ThreeVector xyz) { pos = xyz; };
  void SetParticle(G4int ID) { particleID = ID; };
  void SetTrack(G4int tID) { trackID = tID; };
  void SetPanelNr(G4int tNr) { panelNr = tNr; };
  void SetParticleEnergy(G4double e) { particleEnergy = e; };
  void SetTime(G4double t) { time = t; };

  G4double GetEdep() { return edep; };
  G4ThreeVector GetPos() { return pos; };
  G4int GetParticle() { return particleID;};
  G4int GetTrack() { return trackID;};
  G4int GetPanelNr() { return panelNr;};
  G4double GetParticleEnergy() { return particleEnergy;};
  G4double GetTime() { return time; };      

  
 private:
  G4double edep;
  G4ThreeVector pos;
  G4double time;
  G4int particleID;
  G4int trackID;
  G4int panelNr;
  G4double particleEnergy;
};

typedef G4THitsCollection <GeMSE_MVHit> GeMSE_MVHitsCollection;

extern G4Allocator<GeMSE_MVHit> GeMSE_MVHitAllocator;


inline void* GeMSE_MVHit::operator new(size_t) {
  void *aHit;
  aHit = (void *) GeMSE_MVHitAllocator.MallocSingle();
  return aHit;
}

inline void GeMSE_MVHit::operator delete(void *aHit) {
  GeMSE_MVHitAllocator.FreeSingle((GeMSE_MVHit*) aHit);
}

#endif
