#ifndef CDSSDSi2SD_h
#define CDSSDSi2SD_h 1

#include "G4VSensitiveDetector.hh"
#include "CDSSDSi2GeantHit.hh"

class G4Step;
class G4HCofThisEvent;

class CDSSDSi2SD : public G4VSensitiveDetector {
private:
  CDSSDSi2GeantHitsCollection* hitsCollection = nullptr; ///< Geant step-like hits collect.

public:
  CDSSDSi2SD(G4String);
  ~CDSSDSi2SD();
  
  void Initialize(G4HCofThisEvent*) override;
  G4bool ProcessHits(G4Step*,G4TouchableHistory*) override;
  void EndOfEvent(G4HCofThisEvent*) override;
};
#endif
