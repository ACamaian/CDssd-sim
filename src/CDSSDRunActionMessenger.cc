#include "CDSSDRunActionMessenger.hh"
#include "CDSSDRunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithoutParameter.hh"

//////////////////////////////////////////////////////////////////
/// Constructor
/// command included in this AnalysisMessenger:
/// - /CDSSD/action/setOutputFileName
CDSSDRunActionMessenger::
CDSSDRunActionMessenger(CDSSDRunAction* run)
  :runAction(run) {

  actionDir = new G4UIdirectory("/CDSSD/action/");
  actionDir->SetGuidance("RunAction control");

  
  outputFileNameCmd = new G4UIcmdWithAString("/CDSSD/action/setOutputFileName",this);
  outputFileNameCmd->SetGuidance("Select the output ROOT file name");
  outputFileNameCmd->SetParameterName("output",false);
  outputFileNameCmd->SetDefaultValue("output.root");
  outputFileNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDRunActionMessenger::~CDSSDRunActionMessenger() {
  delete actionDir;

  delete outputFileNameCmd;;
  
}


//////////////////////////////////////////////////////////////////
/// Setting the values using the CDSSDRunAction interface
void CDSSDRunActionMessenger::SetNewValue(G4UIcommand* command,
					    G4String newValue) {
  if(command == outputFileNameCmd)
    runAction->SetOutputFileName(newValue);

}
