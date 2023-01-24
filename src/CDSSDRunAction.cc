/// \file CDSSDRunAction.cc
/// \brief Implementation of the CDSSDRunAction class

#include "CDSSDRunAction.hh"
#include "CDSSDEventAction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDRunAction::CDSSDRunAction(CDSSDEventAction *event)
  : G4UserRunAction(), fEventAction(event)
{ 

  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
  
  // Create analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;


  // Creating ntuple
  //
  analysisManager->CreateNtuple("CDSSDevents","CDSSDevents");
  //analysisManager->CreateNtupleDColumn("Edephit", fEventAction->GetEtothit());
  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDSSDRunAction::~CDSSDRunAction()
{
  G4cout << "Deleting Run Action" << G4endl;

  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDRunAction::BeginOfRunAction(const G4Run* aRun)
{ 

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

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
  G4String fileName = "output/CDSSD.root";
  analysisManager->OpenFile(fileName);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDSSDRunAction::EndOfRunAction(const G4Run* aRun)
{
  
  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  // save histograms & ntuple
  //

  analysisManager->Write();
  analysisManager->CloseFile();
  
  delete analysisManager;

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

