/// \file CDSSDEventAction.cc
/// \brief Implementation of the CDSSDEventAction class

#include "CDSSDEventAction.hh"
#include "CDSSDSi1SD.hh"
#include "CDSSDSi1GeantHit.hh"

//#include "CDSSDDSSDSi1Hit.hh"
#include "G4RunManager.hh"

#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDEventAction::CDSSDEventAction()
: G4UserEventAction()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDEventAction::~CDSSDEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDEventAction::BeginOfEventAction(const G4Event* evt)
{    
 G4int evtNb = evt->GetEventID();


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDEventAction::EndOfEventAction(const G4Event* evt)
{   
   // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  
  //-----------
  //Si1
  //-----------

  // Get hits collections IDs (only once)
  if (fsi1HCID == -1) {
    fsi1HCID = G4SDManager::GetSDMpointer()->GetCollectionID("gasCollection");
  }
  // Get hits collections and loop on it
  auto si1HC = GetHitsCollectionGas(fsi1HCID, evt);
  G4int si1Nentries = si1HC->entries();   


  for(int ii=0; ii<si1Nentries; ii++){
    auto si1Hit = (*si1HC)[ii];    //how access hit from a hit collection

  }
      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


CDSSDSi1GeantHitsCollection* CDSSDEventAction::GetHitsCollectionGas(G4int hcID, const G4Event* event) const {
  
  auto hitsCollection  = static_cast<CDSSDSi1GeantHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}
