#include "CDSSDSi1DetectorMessenger.hh"

#include "G4RunManager.hh"

#include "CDSSDDetectorConstruction.hh"
#include "CDSSDSi1DetectorConstruction.hh"
//#include "CDSSDPrimaryGeneratorAction.hh"

#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4Tokenizer.hh"


//////////////////////////////////////////////////////////////////
/// Constructor
/// command included in this AnalysisMessenger:
/// - /CDSSD/si1/setRmin;
/// - /CDSSD/si1/setRmax;
/// - /CDSSD/si1/setRminActive;
/// - /CDSSD/si1/setRmaxActive;
/// - /CDSSD/si1/setThickness;
/// - /CDSSD/si1/setAlThickness;
/// - /CDSSD/si1/setZPos
/// - /CDSSD/si1/setNSlices;
/// - /CDSSD/si1/setDPhiSi;
/// - /CDSSD/si1/setDPhiGap;

CDSSDSi1DetectorMessenger:: CDSSDSi1DetectorMessenger(CDSSDSi1DetectorConstruction* CDSSDSi1Det)
  :CDSSDSi1Detector(CDSSDSi1Det){

  si1Dir = new G4UIdirectory("/CDSSD/si1/");
  si1Dir->SetGuidance("si1 control");
  
  RminCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si1/setRmin",this);
  RminCmd->SetGuidance("Select the si1 minimum radius");
  RminCmd->SetParameterName("si1Rmin",false);
  RminCmd->SetUnitCategory("Length");
  RminCmd->SetDefaultUnit("mm");
  RminCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  RmaxCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si1/setRmax",this);
  RmaxCmd->SetGuidance("Select the si1 maximum radius");
  RmaxCmd->SetParameterName("si1Rmax",false);
  RmaxCmd->SetUnitCategory("Length");
  RmaxCmd->SetDefaultUnit("mm");
  RmaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  RminActiveCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si1/setRminActive",this);
  RminActiveCmd->SetGuidance("Select the si1 minimum active radius");
  RminActiveCmd->SetParameterName("si1RminActive",false);
  RminActiveCmd->SetUnitCategory("Length");
  RminActiveCmd->SetDefaultUnit("mm");
  RminActiveCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  RmaxActiveCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si1/setRmaxActive",this);
  RmaxActiveCmd->SetGuidance("Select the si1 maximum active radius");
  RmaxActiveCmd->SetParameterName("si1RmaxActive",false);
  RmaxActiveCmd->SetUnitCategory("Length");
  RmaxActiveCmd->SetDefaultUnit("mm");
  RmaxActiveCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  thickCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si1/setThickness",this);
  thickCmd->SetGuidance("Select the si1 thickness");
  thickCmd->SetParameterName("si1Thickness",false);
  thickCmd->SetUnitCategory("Length");
  thickCmd->SetDefaultUnit("mm");
  thickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  thickAlCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si1/setAlThickness",this);
  thickAlCmd->SetGuidance("Select the si1 thickAlness");
  thickAlCmd->SetParameterName("si1Thickness",false);
  thickAlCmd->SetUnitCategory("Length");
  thickAlCmd->SetDefaultUnit("mm");
  thickAlCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  zPosCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si1/setZPos",this);
  zPosCmd->SetGuidance("Select the si1 z position");
  zPosCmd->SetParameterName("si1ZPos",false);
  zPosCmd->SetUnitCategory("Length");
  zPosCmd->SetDefaultUnit("mm");
  zPosCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  dPhiGapCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si1/setDPhiGap",this);
  dPhiGapCmd->SetGuidance("Select the si1 gap dPhi");
  dPhiGapCmd->SetParameterName("si1DPhi_gap",false);
  dPhiGapCmd->SetUnitCategory("Angle");
  dPhiGapCmd->SetDefaultUnit("deg");
  dPhiGapCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  dPhiSiCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si1/setDPhiSi",this);
  dPhiSiCmd->SetGuidance("Select the si1 active dPhi");
  dPhiSiCmd->SetParameterName("si1DPhi_si",false);
  dPhiSiCmd->SetUnitCategory("Angle");
  dPhiSiCmd->SetDefaultUnit("deg");
  dPhiSiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
  nSlicesCmd = new G4UIcmdWithADouble("/CDSSD/si1/setNSlices",this);
  nSlicesCmd->SetParameterName("si1SliceDPhi",false);
  nSlicesCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
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
    
    if(command == RminCmd)
        CDSSDSi1Detector->SetRmin(RminCmd->GetNewDoubleValue(newValue));
    
     if(command == RmaxCmd)
        CDSSDSi1Detector->SetRmax(RmaxCmd->GetNewDoubleValue(newValue));
     
      if(command == RminActiveCmd)
        CDSSDSi1Detector->SetRminActive(RminActiveCmd->GetNewDoubleValue(newValue));
    
     if(command == RmaxActiveCmd)
        CDSSDSi1Detector->SetRmaxActive(RmaxActiveCmd->GetNewDoubleValue(newValue));
    
     if(command == thickCmd)
        CDSSDSi1Detector->SetThickness(thickCmd->GetNewDoubleValue(newValue));
     
      if(command == thickAlCmd)
        CDSSDSi1Detector->SetAlThickness(thickAlCmd->GetNewDoubleValue(newValue));
     
      if(command == zPosCmd)
        CDSSDSi1Detector->SetZPos(zPosCmd->GetNewDoubleValue(newValue));
     
    
      if(command == dPhiGapCmd)
        CDSSDSi1Detector->SetDPhiGap(dPhiGapCmd->GetNewDoubleValue(newValue));
      
      if(command == dPhiSiCmd)
        CDSSDSi1Detector->SetDPhiSi(dPhiSiCmd->GetNewDoubleValue(newValue));
      
      if(command == nSlicesCmd)
        CDSSDSi1Detector->SetNSlices(nSlicesCmd->GetNewDoubleValue(newValue));
      
      
     
}

