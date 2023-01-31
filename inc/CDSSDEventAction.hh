#ifndef CDSSDEventAction_h
#define CDSSDEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4SDManager.hh"
#include "globals.hh"

#include "CDSSDSi1GeantHit.hh"
#include "CDSSDSi2GeantHit.hh"

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

  std::vector<G4int>& GetEventID(){return EventID;};
  std::vector<G4int>& GetTID(){return TrackID;};
  std::vector<G4int>& GetPID(){return ParentID;};
  std::vector<G4int>& GetPDG(){return ParticleID;}
  std::vector<G4int>& GetDetID(){return DetID;};

  std::vector<G4double>& GetCharge(){return Charge;};
  std::vector<G4double>& GetMass(){return Mass;};
  
  std::vector<G4double>& GetXin(){return Xin;};
  std::vector<G4double>& GetYin(){return Yin;};
  std::vector<G4double>& GetZin(){return Zin;};
  
  std::vector<G4int>& GetISec(){return ISec;};
  std::vector<G4int>& GetIRadius(){return IRadius;};
  std::vector<G4int>& GetIAzimuth(){return IAzimuth;};
  
  std::vector<G4double>& GetEDep(){return Edep;};
 
  
private:
    
  CDSSDSi1GeantHitsCollection* GetHitsCollectionSi1(G4int hcID,    const G4Event* event) const;
  G4int fsi1HCID=-1; 
  
  CDSSDSi2GeantHitsCollection* GetHitsCollectionSi2(G4int hcID,    const G4Event* event) const;
  G4int fsi2HCID=-1; 
    
  std::vector<G4int> EventID;
  std::vector<G4int> TrackID;
  std::vector<G4int> ParentID;
  std::vector<G4int> ParticleID;
  std::vector<G4int> DetID;
  
  std::vector<G4double> Charge;
  std::vector<G4double> Mass;

  std::vector<G4double> Xin;
  std::vector<G4double> Yin;
  std::vector<G4double> Zin;
  
  std::vector<G4int> ISec;
  std::vector<G4int> IRadius;
  std::vector<G4int> IAzimuth;
  
  std::vector<G4double> Edep;  
      
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
