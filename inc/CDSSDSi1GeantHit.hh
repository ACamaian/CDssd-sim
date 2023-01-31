#ifndef CDSSDSi1GeantHit_h
#define CDSSDSi1GeantHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"
#include "G4Step.hh"

class CDSSDSi1GeantHit : public G4VHit {
private:
  G4int         trackID;          ///< ID for each track
  G4int         parentID;         ///< ID for the parent track

   G4double      edep;             ///< Energy deposited
   G4double      particleCharge;   ///< Charge of the particle
   G4double      particleMass;     ///< Mass of the particle
   G4int         particleID;       ///< Particle ID according to the GDP-coding
   G4ThreeVector pos;          ///< Position of the hit in absolute coordinates
   G4String      detName;          ///< Detector name where energy is deposited
   G4int         detID;            ///< Detector ID
   G4int islice;
   G4int iradius;
   G4int iphi;


public:
  CDSSDSi1GeantHit() = default;
  CDSSDSi1GeantHit(const CDSSDSi1GeantHit&) = default;
  ~CDSSDSi1GeantHit() override = default;
  
  //operators
  CDSSDSi1GeantHit& operator=(const CDSSDSi1GeantHit&)=default;
  G4bool operator==(const CDSSDSi1GeantHit&) const;

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
   void SetIRadius(G4int val){iradius=val;};
   void SetIPhi(G4int val) {iphi = val;}
   
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
   G4int GetIRadius(){return iradius;}
   G4int GetIPhi() {return iphi;}
   

};

using CDSSDSi1GeantHitsCollection =  G4THitsCollection<CDSSDSi1GeantHit> ;

extern G4ThreadLocal G4Allocator<CDSSDSi1GeantHit>* CDSSDSi1GeantHitAllocator;

inline void* CDSSDSi1GeantHit::operator new(size_t) {

   if (!CDSSDSi1GeantHitAllocator) {
    CDSSDSi1GeantHitAllocator = new G4Allocator<CDSSDSi1GeantHit>;
  }
  void *hit;
  hit = (void *) CDSSDSi1GeantHitAllocator->MallocSingle();
  return hit;

}

inline void CDSSDSi1GeantHit::operator delete(void *hit)
{
  if (!CDSSDSi1GeantHitAllocator) {
    CDSSDSi1GeantHitAllocator = new G4Allocator<CDSSDSi1GeantHit>;
  }
  CDSSDSi1GeantHitAllocator->FreeSingle((CDSSDSi1GeantHit*) hit);
}

#endif
