#include "CDSSDDetectorMessenger.hh"
#include "CDSSDDetectorConstruction.hh"
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
/// - /CDSSD/det/setTargetMat
/// - /CDSSD/det/setTargetThickness
CDSSDDetectorMessenger::
CDSSDDetectorMessenger(CDSSDDetectorConstruction* CDSSDDet)
  :CDSSDDetector(CDSSDDet) {

  CDSSDDir = new G4UIdirectory("/CDSSD/");
  CDSSDDir->SetGuidance("UI commands of CDSSD program");

  detDir = new G4UIdirectory("/CDSSD/det/");
  detDir->SetGuidance("Detector control");

  targetThicknessCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/det/setTargetThickness",this);
  targetThicknessCmd->SetGuidance("Select the Target thickness");
  targetThicknessCmd->SetParameterName("targetThickness",false);
  targetThicknessCmd->SetUnitCategory("Length");
  targetThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  targetMaterialCmd = new G4UIcmdWithAString("/CDSSD/det/setTargetMat",this);
  targetMaterialCmd->SetGuidance("Select Material outside the Chamber.");
  targetMaterialCmd->SetParameterName("targetMat",false);
  targetMaterialCmd->SetDefaultValue("G4_C");
  targetMaterialCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDDetectorMessenger::~CDSSDDetectorMessenger() {
  delete CDSSDDir;
  delete detDir;

  delete targetMaterialCmd;
  delete targetThicknessCmd;
  
}


//////////////////////////////////////////////////////////////////
/// Setting the values using the CDSSDDetectorConstruction interface
void CDSSDDetectorMessenger::SetNewValue(G4UIcommand* command,
					    G4String newValue) {
  
  if(command == targetThicknessCmd)
    CDSSDDetector->SetTargetThickness(targetThicknessCmd->GetNewDoubleValue(newValue));

  if(command == targetMaterialCmd)
    CDSSDDetector->SetTargetMaterial(newValue);

}
