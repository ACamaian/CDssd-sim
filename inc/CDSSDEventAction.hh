#ifndef CDSSDEventAction_h
#define CDSSDEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4SDManager.hh"
#include "globals.hh"

#include "CDSSDSi1GeantHit.hh"

class CDSSDRunAction;

/// Event action class
///

class CDSSDEventAction : public G4UserEventAction
{      
public:
  CDSSDEventAction();
  ~CDSSDEventAction() override;
  
  void BeginOfEventAction(const G4Event* event) override;
  void EndOfEventAction(const G4Event* event) override;
  
private:
  
  CDSSDSi1GeantHitsCollection* GetHitsCollectionSi1(G4int hcID,    const G4Event* event) const;
 

  G4int fsi1HCID=-1; 
      
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
