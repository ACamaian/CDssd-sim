#ifndef CDSSDSi1SD_h
#define CDSSDSi1SD_h 1

#include "G4VSensitiveDetector.hh"
#include "CDSSDSi1GeantHit.hh"
#include "CDSSDSi1DetectorConstruction.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class CDSSDSi1SD : public G4VSensitiveDetector {

public:
    CDSSDSi1SD(const G4String& name,
                  const G4String& hitsCollectionName,
                  CDSSDSi1DetectorConstruction *si1Det);
    
    ~CDSSDSi1SD() override = default;
    
    // methods from base class
    void   Initialize(G4HCofThisEvent* hitCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    void   EndOfEvent(G4HCofThisEvent* hitCollection) override;
    
  private:
    CDSSDSi1GeantHitsCollection* fHitsCollection = nullptr;
    CDSSDSi1DetectorConstruction *Si1Det;
    
    G4int NofSlices;
    G4int NofRadial;
    G4int NofAzimuthal;
    
    G4int countTracks;
    
};
#endif
