#ifndef GeMSE_Hit_h
#define GeMSE_Hit_h 1

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

class GeMSE_Hit : public G4VHit {
 public:
  GeMSE_Hit();
  ~GeMSE_Hit();
  GeMSE_Hit(const GeMSE_Hit&);
  const GeMSE_Hit& operator=(const GeMSE_Hit&);
  G4int operator==(const GeMSE_Hit&) const;

  inline void* operator new(size_t);
  inline void operator delete(void*);

  void Draw();
  void Print();

 public:
  void SetEdep(G4double de) { edep = de; };
  void SetPos(G4ThreeVector xyz) { pos = xyz; };
  void SetParticle(G4int ID) { particleID = ID; };
  void SetTrack(G4int tID) { trackID = tID; };
  void SetParticleEnergy(G4double e) { particleEnergy = e; };
  void SetTime(G4double t) { time = t; };

  G4double GetEdep() { return edep; };
  G4ThreeVector GetPos() { return pos; };
  G4int GetParticle() { return particleID;};
  G4int GetTrack() { return trackID;};
  G4double GetParticleEnergy() { return particleEnergy;};
  G4double GetTime() { return time; };

 private:
  G4double edep;
  G4ThreeVector pos;
  G4double time;
  G4int particleID;
  G4int trackID;
  G4double particleEnergy;
};

typedef G4THitsCollection<GeMSE_Hit> GeMSE_HitsCollection;

extern G4Allocator<GeMSE_Hit> GeMSE_HitAllocator;

inline void* GeMSE_Hit::operator new(size_t) {
  void* aHit;
  aHit = (void*)GeMSE_HitAllocator.MallocSingle();
  return aHit;
}

inline void GeMSE_Hit::operator delete(void* aHit) {
  GeMSE_HitAllocator.FreeSingle((GeMSE_Hit*)aHit);
}

#endif
