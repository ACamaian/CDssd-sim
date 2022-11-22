#ifndef CDSSDSi1GeantHit_h
#define CDSSDSi1GeantHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"

class CDSSDSi1GeantHit : public G4VHit {
private:

  G4double      edep;             ///< Energy deposited

public:
  CDSSDSi1GeantHit();
  ~CDSSDSi1GeantHit();
  CDSSDSi1GeantHit(const CDSSDSi1GeantHit&);
  const CDSSDSi1GeantHit& operator=(const CDSSDSi1GeantHit&);
  G4int operator==(const CDSSDSi1GeantHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  void SetEdep(G4double de){ edep = de; }
 
  G4double  GetEdep(){ return edep; }
};

typedef G4THitsCollection<CDSSDSi1GeantHit> CDSSDSi1GeantHitsCollection;

extern G4Allocator<CDSSDSi1GeantHit>* CDSSDSi1GeantHitAllocator;

inline void* CDSSDSi1GeantHit::operator new(size_t) {

  if(!CDSSDSi1GeantHitAllocator) CDSSDSi1GeantHitAllocator = new G4Allocator<CDSSDSi1GeantHit>;
  return (void*) CDSSDSi1GeantHitAllocator->MallocSingle();
}

inline void CDSSDSi1GeantHit::operator delete(void *aHit) {
  CDSSDSi1GeantHitAllocator->FreeSingle((CDSSDSi1GeantHit*) aHit);
}
#endif
