/// \file CDSSDEventAction.cc
/// \brief Implementation of the CDSSDEventAction class

#include "CDSSDEventAction.hh"
#include "CDSSDSi1SD.hh"
#include "CDSSDSi2SD.hh"
#include "CDSSDSi1GeantHit.hh"

#include "G4EventManager.hh"
#include "G4AnalysisManager.hh"

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
    
 const G4int verboseLevel = G4EventManager::GetEventManager()->GetVerboseLevel();   
 if(verboseLevel>=2){
       G4cout << "##################################################################"<< G4endl
       << "###########   CDSSDEventAction::BeginningOfEventAction()  ##############"<< G4endl
       << "###    Event " << evt->GetEventID() << " ends." << G4endl;
       G4cout << "##################################################################"<< G4endl;
  }   
    

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDEventAction::EndOfEventAction(const G4Event* evt)
{   
    
  const G4int verboseLevel = G4EventManager::GetEventManager()->GetVerboseLevel();  
  if(verboseLevel>=2){
       G4cout << "##################################################################"<< G4endl
       << "###########   CDSSDEventAction::EndOfEventAction()  ##############"<< G4endl
       << "###    Event " << evt->GetEventID() << " ends." << G4endl;
       G4cout << "##################################################################"<< G4endl;
       
       G4cout << "\n Looping on Hits Collection and storing results---" << G4endl;
       
  }    
    
    
   // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  EventID.clear();
  TrackID.clear();
  ParentID.clear();
  ParticleID.clear();
  DetID.clear();
  Charge.clear();
  Mass.clear();
  Xin.clear();
  Yin.clear();
  Zin.clear();
  ISec.clear();
  IRadius.clear();
  IAzimuth.clear();
  Edep.clear();    
  
  EventID.push_back(evt->GetEventID());
  
  G4int temp_tID=-99;
  G4double edep=0;
  G4double xin=0;
  G4double yin=0;
  G4double zin=0;
  G4double charge=0, mass=0, etot_dep=0;
  G4int trackID=-1, particleID=-1, parentID=-1, detID=-1, isec=-1, iradius=-1, iazimuth=-1;
  G4String detName;
  
  //-----------
  //Si1
  //-----------

  // Get hits collections IDs (only once)
  if (fsi1HCID == -1) {
    fsi1HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Si1HitsCollection");
  }
  // Get hits collections and loop on it
  auto si1HC = GetHitsCollectionSi1(fsi1HCID, evt);
  G4int si1Nentries = si1HC->entries();   
    
  for(int ii=0; ii<si1Nentries; ii++){
    auto si1Hit = (*si1HC)[ii];    //how access hit from a hit collection
                  
       edep = si1Hit->GetEdep();
       xin = si1Hit->GetPos().x();
       yin = si1Hit->GetPos().y();
       zin = si1Hit->GetPos().z();
       particleID = si1Hit->GetParticleID();
       charge = si1Hit->GetParticleCharge();
       mass = si1Hit->GetParticleMass();
       trackID = si1Hit->GetTrackID();
       parentID = si1Hit->GetParentID();
       detID = si1Hit->GetDetID();
       isec = si1Hit->GetISlice();
       iradius = si1Hit->GetIRadius();
       iazimuth = si1Hit->GetIPhi();
       detName = si1Hit->GetDetName();
      
      
       TrackID.push_back(trackID);
       ParentID.push_back(parentID);
       ParticleID.push_back(particleID);
       DetID.push_back(detID);
       Charge.push_back(charge);
       Mass.push_back(mass);
       Xin.push_back(xin);
       Yin.push_back(yin);
       Zin.push_back(zin);
       Edep.push_back(edep);  
       ISec.push_back(isec);
       IRadius.push_back(iradius);
       IAzimuth.push_back(iazimuth);
      
    } //end loop on Si1Hit entries
    
    
    
    
  //-----------
  //Si2
  //-----------

  // Get hits collections IDs (only once)
  if (fsi2HCID == -1) {
    fsi2HCID = G4SDManager::GetSDMpointer()->GetCollectionID("Si2HitsCollection");
  }
  // Get hits collections and loop on it
  auto si2HC = GetHitsCollectionSi2(fsi2HCID, evt);
  G4int si2Nentries = si2HC->entries();   
  
  for(int ii=0; ii<si2Nentries; ii++){
    auto si2Hit = (*si2HC)[ii];    //how access hit from a hit collection
                        
      edep = si2Hit->GetEdep();
       xin = si2Hit->GetPos().x();
       yin = si2Hit->GetPos().y();
       zin = si2Hit->GetPos().z();
       particleID = si2Hit->GetParticleID();
       charge = si2Hit->GetParticleCharge();
       mass = si2Hit->GetParticleMass();
       trackID = si2Hit->GetTrackID();
       parentID = si2Hit->GetParentID();
       detID = si2Hit->GetDetID();
       isec = si2Hit->GetISlice();
       detName = si2Hit->GetDetName();
      
      
       TrackID.push_back(trackID);
       ParentID.push_back(parentID);
       ParticleID.push_back(particleID);
       DetID.push_back(detID);
       Charge.push_back(charge);
       Mass.push_back(mass);
       Xin.push_back(xin);
       Yin.push_back(yin);
       Zin.push_back(zin);
       Edep.push_back(edep);  
       ISec.push_back(isec);
       
       
   } //end loop on Si2Hit entries
 
 
  analysisManager->AddNtupleRow(0);
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


CDSSDSi1GeantHitsCollection* CDSSDEventAction::GetHitsCollectionSi1(G4int hcID, const G4Event* event) const {
  
  auto hitsCollection  = static_cast<CDSSDSi1GeantHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

CDSSDSi2GeantHitsCollection* CDSSDEventAction::GetHitsCollectionSi2(G4int hcID, const G4Event* event) const {
  
  auto hitsCollection  = static_cast<CDSSDSi2GeantHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

