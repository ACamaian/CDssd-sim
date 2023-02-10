#ifndef CDSSDSi2GeantHit_h
#define CDSSDSi2GeantHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"
#include "G4Step.hh"

class CDSSDSi2GeantHit : public G4VHit {
private:
 G4int         trackID;          ///< ID for each track
  G4int         parentID;         ///< ID for the parent track

   G4double      edep=0;             ///< Energy deposited
   G4double      particleCharge;   ///< Charge of the particle
   G4double      particleMass;     ///< Mass of the particle
   G4int         particleID;       ///< Particle ID according to the GDP-coding
   G4ThreeVector pos;          ///< Position of the hit in absolute coordinates
   G4String      detName;          ///< Detector name where energy is deposited
   G4int         detID;            ///< Detector ID
   G4int islice;


public:
  CDSSDSi2GeantHit() = default;
  CDSSDSi2GeantHit(const CDSSDSi2GeantHit&) = default;
  ~CDSSDSi2GeantHit() override = default;
  
  //operators
  CDSSDSi2GeantHit& operator=(const CDSSDSi2GeantHit&)=default;
  G4bool operator==(const CDSSDSi2GeantHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  void Reset();
  void Print();

   void SetTrackID(G4int track){ trackID = track; }
   void SetParentID(G4int track){ parentID = track; }
   void SetEdep(G4double de){ edep = de; }
   void SetParticleCharge(G4double pc){particleCharge=pc;}
   void SetParticleMass(G4double pm){particleMass=pm;}
   void SetParticleID(G4int pi){particleID=pi;}
   void SetPos(G4ThreeVector xyz){ pos = xyz; }
   void SetDetName(G4String Name){ detName = Name; }
   void SetDetID(G4int id){ detID = id; }
   void SetISlice(G4int val){islice = val;}
      
   void AddEnergy(G4double val){edep += val;}

   G4int         GetTrackID(){ return trackID; }
   G4int         GetParentID(){ return parentID; }
  G4double      GetEdep(){ return edep; }
   G4double      GetParticleCharge(){return particleCharge;}
   G4double      GetParticleMass(){return particleMass;}
   G4int         GetParticleID(){return particleID;}
   G4ThreeVector GetPos(){ return pos; }
   G4String      GetDetName(){ return detName; }
   G4int         GetDetID(){ return detID; }
   G4int GetISlice(){return islice;}
};

using CDSSDSi2GeantHitsCollection =  G4THitsCollection<CDSSDSi2GeantHit> ;

extern G4ThreadLocal G4Allocator<CDSSDSi2GeantHit>* CDSSDSi2GeantHitAllocator;

inline void* CDSSDSi2GeantHit::operator new(size_t) {

   if (!CDSSDSi2GeantHitAllocator) {
    CDSSDSi2GeantHitAllocator = new G4Allocator<CDSSDSi2GeantHit>;
  }
  void *hit;
  hit = (void *) CDSSDSi2GeantHitAllocator->MallocSingle();
  return hit;

}

inline void CDSSDSi2GeantHit::operator delete(void *hit)
{
  if (!CDSSDSi2GeantHitAllocator) {
    CDSSDSi2GeantHitAllocator = new G4Allocator<CDSSDSi2GeantHit>;
  }
  CDSSDSi2GeantHitAllocator->FreeSingle((CDSSDSi2GeantHit*) hit);
}

#endif
