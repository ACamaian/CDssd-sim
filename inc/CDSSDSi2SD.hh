#ifndef CDSSDSi2SD_h
#define CDSSDSi2SD_h 1

#include "G4VSensitiveDetector.hh"
#include "CDSSDSi2GeantHit.hh"
#include "CDSSDSi2DetectorConstruction.hh"

class G4Step;
class G4HCofThisEvent;

class CDSSDSi2SD : public G4VSensitiveDetector {

public:
    CDSSDSi2SD(const G4String& name,
                  const G4String& hitsCollectionName,
                  CDSSDSi2DetectorConstruction *si2Det);
    
    ~CDSSDSi2SD() override = default;
    
    // methods from base class
    void   Initialize(G4HCofThisEvent* hitCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    void   EndOfEvent(G4HCofThisEvent* hitCollection) override;

  private:
    CDSSDSi2GeantHitsCollection* fHitsCollection = nullptr;
    G4int NofSlices;
    
    CDSSDSi2DetectorConstruction *Si2Det;
    
    CDSSDSi2GeantHit *newHit;
};
#endif
