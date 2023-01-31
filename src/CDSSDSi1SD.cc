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

#include "G4RunManager.hh"

#include "globals.hh"

CDSSDSi1SD::CDSSDSi1SD(const G4String& name,
                  const G4String& hitsCollectionName,
                  CDSSDSi1DetectorConstruction *si1Det):
            G4VSensitiveDetector(name) 
        {
    collectionName.insert(hitsCollectionName);
    
    Si1Det = si1Det;
    
    NofSlices = Si1Det->GetNSlices();
    NofRadial = Si1Det->GetNRadialStrips();
    NofAzimuthal = Si1Det->GetNAzimuthalStrips();
    
            }

void CDSSDSi1SD::Initialize(G4HCofThisEvent* HCE){

  // Create hits collection
  fHitsCollection = new CDSSDSi1GeantHitsCollection(SensitiveDetectorName, collectionName[0]);
  
  // Add this collection in HCE
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  HCE->AddHitsCollection( hcID, fHitsCollection);
  
  //creating the hit
  newHit = new CDSSDSi1GeantHit(); //(*fHitsCollection)[sliceNumber];
 
}


G4bool CDSSDSi1SD::ProcessHits(G4Step* aStep, G4TouchableHistory*){
   
  //function is directly implemented here:  
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  // step length
  G4double stepLength = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge()!= 0.) {
    stepLength = aStep->GetStepLength();
  }

  if (edep==0. && stepLength ==0.) return false;
  
  auto touchable = (aStep->GetPreStepPoint()->GetTouchable());
    
  // Get calorimeter cell id
  auto sliceNumber = touchable->GetReplicaNumber(1);
  
  // Get hit accounting data
    if ( ! newHit ) {
    G4ExceptionDescription msg;
    msg << "Cannot access newHit " << sliceNumber;
    G4Exception("CDSSDSi1SD::ProcessHits()",
      "MyCode0004", FatalException, msg);
  }
  
  
  if(aStep->IsFirstStepInVolume()){
      newHit->Reset();
      
      G4ThreeVector inPos = aStep->GetPreStepPoint()->GetPosition();
      //G4cout << inPos[0] << " " << inPos[1] << " " << inPos[2] << G4endl;
            
      G4ThreeVector center = {0,0, Si1Det->GetZPos()+Si1Det->GetThickness()/2.};
      //G4cout << center[0] << " " << center[1] << " " << center[2] << G4endl;
      
      G4ThreeVector xx = {1,0.,0};
      
      G4double radius = abs((inPos-center).mag());
      G4double phi = acos((inPos - center).dot(xx)/radius);
      if(inPos[1]<0) phi= 2*M_PI - phi; 
      
      //G4cout << radius << " " << phi/deg << G4endl;
      
      G4double phimin = (M_PI/2.)*touchable->GetCopyNumber(1) + Si1Det->GetDPhiGap(); 
      G4double dphi = Si1Det->GetDPhiSi()/Si1Det->GetNAzimuthalStrips();
      G4int iphi = (phi-phimin)/dphi;
      
      G4double rmin = Si1Det->GetRminActive();
      G4double rmax = Si1Det->GetRmaxActive();
      G4double dr =(rmax - rmin)/Si1Det->GetNRadialStrips();
      G4int ir=radius/dr;
      
      //G4cout << dr << " " << touchable->GetCopyNumber(1) << " " << dphi/deg << G4endl;
      
      //G4cout << ir << " " << iphi << G4endl;
      
      newHit->SetPos(inPos);
      newHit->SetDetID(touchable->GetCopyNumber(1)*10000+iphi*100+ir);
      newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
      newHit->SetParentID(aStep->GetTrack()->GetParentID());
      newHit->SetParticleCharge(aStep->GetTrack()->GetParticleDefinition()->GetPDGCharge());
      newHit->SetParticleMass(aStep->GetTrack()->GetParticleDefinition()->GetPDGMass());
      
      newHit->SetISlice(touchable->GetCopyNumber(1));
      newHit->SetIRadius(ir);
      newHit->SetIPhi(iphi);
      newHit->SetEdep(edep);      
      
      //filling the hit

      fHitsCollection->insert(newHit);      
  }
  else {
      newHit->AddEnergy(edep);
  }

  
  
  return true;
  
  

  // newHit cannot be deleted here !
  // It should be deleted after the end of the event  
    
}

void CDSSDSi1SD::EndOfEvent(G4HCofThisEvent*){
      
  if ( verboseLevel>1 ) {
     auto nofHits = fHitsCollection->entries();
     G4cout
       << G4endl
       << "-------->Hits Collection: in this event they are " << nofHits
       << " hits in the Si1 Slices: " << G4endl;
     for ( std::size_t i=0; i<nofHits; ++i ) (*fHitsCollection)[i]->Print();
  }

}
