#include "CDSSDSi1DetectorMessenger.hh"

#include "G4RunManager.hh"

#include "CDSSDDetectorConstruction.hh"
#include "CDSSDSi1DetectorConstruction.hh"
//#include "CDSSDPrimaryGeneratorAction.hh"

#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4Tokenizer.hh"


//////////////////////////////////////////////////////////////////
/// Constructor
/// command included in this AnalysisMessenger:
/// - /CDSSD/si1/

CDSSDSi1DetectorMessenger:: CDSSDSi1DetectorMessenger(CDSSDSi1DetectorConstruction* CDSSDSi1Det)
  :CDSSDSi1Detector(CDSSDSi1Det){

  //if(CDSSDDetector)    ; //avoid compiler warning message 

  si1Dir = new G4UIdirectory("/CDSSD/si1/");
  si1Dir->SetGuidance("si1 control");

}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDSi1DetectorMessenger::~CDSSDSi1DetectorMessenger() {
  delete si1Dir;
 
}




//////////////////////////////////////////////////////////////////
/// Setting the new values and connecting to actions
void CDSSDSi1DetectorMessenger::SetNewValue(G4UIcommand* command,
                                               G4String newValue) {  
}

