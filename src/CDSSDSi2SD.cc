#include "CDSSDSi2SD.hh"

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


CDSSDSi2SD::CDSSDSi2SD(const G4String& name,
                  const G4String& hitsCollectionName,
                  CDSSDSi2DetectorConstruction *si2Det):
            G4VSensitiveDetector(name)
            {
    collectionName.insert(hitsCollectionName);
    
    Si2Det = si2Det;
            }

void CDSSDSi2SD::Initialize(G4HCofThisEvent* HCE){

  countTracks=0;
  
  // Create hits collection
  fHitsCollection = new CDSSDSi2GeantHitsCollection(SensitiveDetectorName, collectionName[0]);
  
  // Add this collection in HCE
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  HCE->AddHitsCollection( hcID, fHitsCollection);
   
}


G4bool CDSSDSi2SD::ProcessHits(G4Step* aStep, G4TouchableHistory*){

  //function is directly implemented here:  
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep<=0) return false;
    
  auto touchable = (aStep->GetPreStepPoint()->GetTouchable());
    
  // Get slice id
  auto sliceNumber = touchable->GetReplicaNumber(1);
  
//   // Get hit accounting data
//     if ( ! newHit ) {
//     G4ExceptionDescription msg;
//     msg << "Cannot access newHit " << sliceNumber;
//     G4Exception("CDSSDSi2SD::ProcessHits()",
//       "MyCode0004", FatalException, msg);
//   }
  
  G4int tID = aStep->GetTrack()->GetTrackID(); //unique ID off the track
   
  if(aStep->IsFirstStepInVolume()){
      
     CDSSDSi2GeantHit *tempHit = new CDSSDSi2GeantHit();  
     fHitsCollection->insert(tempHit);   
     countTracks++;
      
     G4ThreeVector inPos = aStep->GetPreStepPoint()->GetPosition();
     //G4cout << inPos[0] << " " << inPos[1] << " " << inPos[2] << G4endl;
            
     G4ThreeVector center = {0,0, Si2Det->GetZPos()+Si2Det->GetThickness()/2.};
     //G4cout << center[0] << " " << center[1] << " " << center[2] << G4endl;
      
     tempHit->SetPos(inPos);
     tempHit->SetDetID(100000+touchable->GetCopyNumber(1));
     tempHit->SetTrackID(aStep->GetTrack()->GetTrackID());
     tempHit->SetParentID(aStep->GetTrack()->GetParentID());
     tempHit->SetParticleCharge(aStep->GetTrack()->GetParticleDefinition()->GetPDGCharge());
     tempHit->SetParticleMass(aStep->GetTrack()->GetParticleDefinition()->GetPDGMass());
      
     tempHit->SetISlice(touchable->GetCopyNumber(1));    
     tempHit->SetEdep(edep);   

     
  }
  else{
      auto tHit = (*fHitsCollection)[countTracks-1];
      if ( ! tHit ) {
            G4ExceptionDescription msg;
            msg << "Cannot access hit " << countTracks-1;
            G4Exception("CDSSDSi2SD::ProcessHits()",
            "MyCode0004", FatalException, msg);
        }

      tHit->AddEnergy(edep);
  }
  
  
  return true;
  

  // newHit cannot be deleted here !
  // It should be deleted after the end of the event  
    
}

void CDSSDSi2SD::EndOfEvent(G4HCofThisEvent*){
            
  if ( verboseLevel>1 ) {
     auto nofHits = fHitsCollection->entries();
     G4cout
       << G4endl
       << "-------->Hits Collection: in this event they are " << nofHits
       << " hits in the Si2 Slices: " << G4endl;
     for ( std::size_t i=0; i<nofHits; ++i ) (*fHitsCollection)[i]->Print();
  }

}
