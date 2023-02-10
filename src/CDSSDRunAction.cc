/// \file CDSSDRunAction.cc
/// \brief Implementation of the CDSSDRunAction class


#include "G4RunManager.hh"
#include "CDSSDRunAction.hh"
#include "CDSSDEventAction.hh"
#include "G4Run.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDRunAction::CDSSDRunAction(CDSSDEventAction *event)
  : G4UserRunAction(), fEventAction(event)
{ 

  
    
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
  
  // Create analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Creating ntuple
  //
  analysisManager->CreateNtuple("CDSSDevents","CDSSDevents");
  analysisManager->CreateNtupleIColumn("EventID", fEventAction->GetEventID());
  analysisManager->CreateNtupleIColumn("TrackID", fEventAction->GetTID());
  analysisManager->CreateNtupleIColumn("ParentID", fEventAction->GetPID());
  analysisManager->CreateNtupleIColumn("ParticleID", fEventAction->GetPDG());

  analysisManager->CreateNtupleDColumn("ThetaCMPrim", fEventAction->GetThetaCM());
  analysisManager->CreateNtupleDColumn("PhiCMPrim", fEventAction->GetPhiCM());
  
  analysisManager->CreateNtupleDColumn("ELabPrim", fEventAction->GetELab());
  analysisManager->CreateNtupleDColumn("EstarPrim", fEventAction->GetEstar());
  analysisManager->CreateNtupleDColumn("ThetaLabPrim", fEventAction->GetThetaLab());
  analysisManager->CreateNtupleDColumn("PhiLabPrim", fEventAction->GetPhiLab());
  
  analysisManager->CreateNtupleIColumn("DetID", fEventAction->GetDetID());
  
  analysisManager->CreateNtupleDColumn("Zpart", fEventAction->GetCharge());
  analysisManager->CreateNtupleDColumn("Apart", fEventAction->GetMass());
  
  analysisManager->CreateNtupleDColumn("Xin", fEventAction->GetXin());
  analysisManager->CreateNtupleDColumn("Yin", fEventAction->GetYin());
  analysisManager->CreateNtupleDColumn("Zin", fEventAction->GetZin());
 
  analysisManager->CreateNtupleIColumn("ISec", fEventAction->GetISec());
  analysisManager->CreateNtupleIColumn("IRadius", fEventAction->GetIRadius());
  analysisManager->CreateNtupleIColumn("IAzimuth", fEventAction->GetIAzimuth());
  
  analysisManager->CreateNtupleDColumn("ThetaRiv", fEventAction->GetThetaRiv());
  analysisManager->CreateNtupleDColumn("PhiRiv", fEventAction->GetPhiRiv());
  analysisManager->CreateNtupleDColumn("EdepSi1", fEventAction->GetEDepSi1());
  analysisManager->CreateNtupleDColumn("EdepSi2", fEventAction->GetEDepSi2());
    
  
  analysisManager->FinishNtuple();
  
  runMessenger = new CDSSDRunActionMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDRunAction::~CDSSDRunAction()
{
//   G4cout << "Deleting Run Action" << G4endl;
// 
//   delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDRunAction::BeginOfRunAction(const G4Run* aRun)
{ 

   auto analysisManager = G4AnalysisManager::Instance();
   const G4int verboseLevel = G4RunManager::GetRunManager()->GetVerboseLevel();
   
   if(verboseLevel>=2){
    G4cout << "##################################################################"
	   << G4endl
	   << "###########   CDSSDRunAction::BeginOfRunAction()  ##############"
	   << G4endl
	   << "###    Run " << aRun->GetRunID() << " start." << G4endl;
    G4cout << "##################################################################"
	   << G4endl;
  }
  
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
  // Open an output file
  G4String fileName = GetOutputFileName();
  analysisManager->OpenFile(fileName);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDRunAction::EndOfRunAction(const G4Run* aRun)
{
  const G4int verboseLevel = G4RunManager::GetRunManager()->GetVerboseLevel();


  if(verboseLevel>=2){
      G4cout << "##################################################################"<< G4endl
       << "###########   CDSSDRunAction::EndOfRunAction()  ##############"<< G4endl
       << "###    Run " << aRun->GetRunID() << " ends." << G4endl;
       G4cout << "##################################################################"<< G4endl;
      
    if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }


      
      
      
  }
    
    
    
    
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  
  // save histograms & ntuple
  //

   analysisManager->Write();
   analysisManager->CloseFile();
   
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

