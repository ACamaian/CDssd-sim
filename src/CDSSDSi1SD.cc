#include "CDSSDSi1SD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"

#include "G4VPhysicalVolume.hh"
#include "G4TouchableHistory.hh"
#include "G4VTouchable.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


CDSSDSi1SD::CDSSDSi1SD(G4String name):G4VSensitiveDetector(name){

  G4cout << "Creating SD with name: " << name << G4endl;
  G4String HCname;
  collectionName.insert(HCname="gasCollection");
}


CDSSDSi1SD::~CDSSDSi1SD(){
}


void CDSSDSi1SD::Initialize(G4HCofThisEvent* HCE){

  
  hitsCollection = new CDSSDSi1GeantHitsCollection (SensitiveDetectorName,collectionName[0]);
  static G4int HCID = -1;
  if(HCID<0) HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  
 
  HCE->AddHitsCollection(HCID, hitsCollection );
}


G4bool CDSSDSi1SD::ProcessHits(G4Step* aStep,G4TouchableHistory*){

  //function is directly implemented here:
  G4double edep = -(aStep->GetPostStepPoint()->GetKineticEnergy() - aStep->GetPreStepPoint()->GetKineticEnergy())/MeV;
    
  if(edep==0.) return false;

  CDSSDSi1GeantHit* newHit = new CDSSDSi1GeantHit();
  newHit->SetEdep(edep);
  
  hitsCollection->insert(newHit);

  // newHit cannot be deleted here !
  // It should be deleted after the end of the event

  return true;
}

void CDSSDSi1SD::EndOfEvent(G4HCofThisEvent*){

  G4int NbHits = hitsCollection->entries();
  if (verboseLevel>0) {
    G4cout << "Hits Collection: in this event they are " << NbHits
	   << " (GEANT-like) hits in the gas volume: " << G4endl;
    for (G4int i=0;i<NbHits;i++) (*hitsCollection)[i]->Print();
  }
}
