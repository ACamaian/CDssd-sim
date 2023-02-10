#include <time.h>

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4String.hh"
#include "G4UIQt.hh"

#include "Randomize.hh"

#include "G4VisManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "CDSSDDetectorConstruction.hh"
#include "CDSSDActionInitialization.hh"
#include "CDSSDPrimaryGeneratorAction.hh"
#include "CDSSDRunAction.hh"
#include "CDSSDEventAction.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "CDSSDPhysicsList.hh"

int main(int argc,char** argv)
{
    
 // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed=time(0); //returns time in seconds as an integer
  CLHEP::HepRandom::setTheSeed(seed);//changes the seed of the random engine

  
  // Construct the default run manager
  //
  auto* runManager =    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
   
  //Analysys toolkit
  // CDSSDROOTAnalysis *analysis = new CDSSDROOTAnalysis();

  // Detector construction
  CDSSDDetectorConstruction *detector = new CDSSDDetectorConstruction();
  runManager->SetUserInitialization(detector);
  
  // Physics List
  CDSSDPhysicsList *phys_list = new CDSSDPhysicsList();
  runManager->SetUserInitialization(phys_list);
  
  G4cout << "Init Actions " << G4endl;
  // Set mandatory and user action class
  runManager->SetUserInitialization(new CDSSDActionInitialization(detector));
  
  

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  G4cout << "Deleting Vis Manager" << G4endl;
  delete visManager;
  G4cout << "Deleting Run Manager" << G4endl;
  delete runManager;
  G4cout << "Done" << G4endl;
}
