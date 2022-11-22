#ifndef CDSSDSi1SD_h
#define CDSSDSi1SD_h 1

#include "G4VSensitiveDetector.hh"
#include "CDSSDSi1GeantHit.hh"

class G4Step;
class G4HCofThisEvent;

class CDSSDSi1SD : public G4VSensitiveDetector {
private:
  CDSSDSi1GeantHitsCollection* hitsCollection = nullptr; ///< Geant step-like hits collect.

public:
  CDSSDSi1SD(G4String);
  ~CDSSDSi1SD();
  
  void Initialize(G4HCofThisEvent*) override;
  G4bool ProcessHits(G4Step*,G4TouchableHistory*) override;
  void EndOfEvent(G4HCofThisEvent*) override;
};
#endif
