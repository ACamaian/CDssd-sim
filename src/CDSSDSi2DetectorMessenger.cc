#include "CDSSDSi2DetectorMessenger.hh"

#include "G4RunManager.hh"

#include "CDSSDDetectorConstruction.hh"
#include "CDSSDSi2DetectorConstruction.hh"
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
/// - /CDSSD/si2/setRmin;
/// - /CDSSD/si2/setRmax;
/// - /CDSSD/si2/setRminActive;
/// - /CDSSD/si2/setRmaxActive;
/// - /CDSSD/si2/setThickness;
/// - /CDSSD/si2/setZPos
/// - /CDSSD/si2/setNSlices;
/// - /CDSSD/si2/setDPhiSi;
/// - /CDSSD/si2/setDPhiGap;

CDSSDSi2DetectorMessenger:: CDSSDSi2DetectorMessenger(CDSSDSi2DetectorConstruction* CDSSDSi2Det)
  :CDSSDSi2Detector(CDSSDSi2Det){

  si2Dir = new G4UIdirectory("/CDSSD/si2/");
  si2Dir->SetGuidance("si2 control");
  
  RminCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si2/setRmin",this);
  RminCmd->SetGuidance("Select the si2 minimum radius");
  RminCmd->SetParameterName("si2Rmin",false);
  RminCmd->SetUnitCategory("Length");
  RminCmd->SetDefaultUnit("mm");
  RminCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  RmaxCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si2/setRmax",this);
  RmaxCmd->SetGuidance("Select the si2 maximum radius");
  RmaxCmd->SetParameterName("si2Rmax",false);
  RmaxCmd->SetUnitCategory("Length");
  RmaxCmd->SetDefaultUnit("mm");
  RmaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  RminActiveCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si2/setRminActive",this);
  RminActiveCmd->SetGuidance("Select the si2 minimum active radius");
  RminActiveCmd->SetParameterName("si2RminActive",false);
  RminActiveCmd->SetUnitCategory("Length");
  RminActiveCmd->SetDefaultUnit("mm");
  RminActiveCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  RmaxActiveCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si2/setRmaxActive",this);
  RmaxActiveCmd->SetGuidance("Select the si2 maximum active radius");
  RmaxActiveCmd->SetParameterName("si2RmaxActive",false);
  RmaxActiveCmd->SetUnitCategory("Length");
  RmaxActiveCmd->SetDefaultUnit("mm");
  RmaxActiveCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  thickCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si2/setThickness",this);
  thickCmd->SetGuidance("Select the si2 thickness");
  thickCmd->SetParameterName("si2Thickness",false);
  thickCmd->SetUnitCategory("Length");
  thickCmd->SetDefaultUnit("mm");
  thickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  thickAlCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si2/setAlThickness",this);
  thickAlCmd->SetGuidance("Select the si2 Al thickness");
  thickAlCmd->SetParameterName("si2AlThickness",false);
  thickAlCmd->SetUnitCategory("Length");
  thickAlCmd->SetDefaultUnit("mm");
  thickAlCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  zPosCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si2/setZPos",this);
  zPosCmd->SetGuidance("Select the si2 z position");
  zPosCmd->SetParameterName("si2ZPos",false);
  zPosCmd->SetUnitCategory("Length");
  zPosCmd->SetDefaultUnit("mm");
  zPosCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  dPhiGapCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si2/setDPhiGap",this);
  dPhiGapCmd->SetGuidance("Select the si2 gap dPhi");
  dPhiGapCmd->SetParameterName("si2DPhi_gap",false);
  dPhiGapCmd->SetUnitCategory("Angle");
  dPhiGapCmd->SetDefaultUnit("deg");
  dPhiGapCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  dPhiSiCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/si2/setDPhiSi",this);
  dPhiSiCmd->SetGuidance("Select the si2 active dPhi");
  dPhiSiCmd->SetParameterName("si2DPhi_si",false);
  dPhiSiCmd->SetUnitCategory("Angle");
  dPhiSiCmd->SetDefaultUnit("deg");
  dPhiSiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
  nSlicesCmd = new G4UIcmdWithADouble("/CDSSD/si2/setNSlices",this);
  nSlicesCmd->SetParameterName("si2SliceDPhi",false);
  nSlicesCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  resCmd = new G4UIcmdWithADouble("/CDSSD/si2/resolution",this);
  resCmd->SetParameterName("si2Resolution",false);
  resCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDSi2DetectorMessenger::~CDSSDSi2DetectorMessenger() {
  delete si2Dir;
 
}




//////////////////////////////////////////////////////////////////
/// Setting the new values and connecting to actions
void CDSSDSi2DetectorMessenger::SetNewValue(G4UIcommand* command,
                                               G4String newValue) {  
    
    if(command == RminCmd)
        CDSSDSi2Detector->SetRmin(RminCmd->GetNewDoubleValue(newValue));
    
     if(command == RmaxCmd)
        CDSSDSi2Detector->SetRmax(RmaxCmd->GetNewDoubleValue(newValue));
     
      if(command == RminActiveCmd)
        CDSSDSi2Detector->SetRminActive(RminActiveCmd->GetNewDoubleValue(newValue));
    
     if(command == RmaxActiveCmd)
        CDSSDSi2Detector->SetRmaxActive(RmaxActiveCmd->GetNewDoubleValue(newValue));
    
     if(command == thickCmd)
        CDSSDSi2Detector->SetThickness(thickCmd->GetNewDoubleValue(newValue));
     
       if(command == thickAlCmd)
        CDSSDSi2Detector->SetAlThickness(thickAlCmd->GetNewDoubleValue(newValue));
     
     
      if(command == zPosCmd)
        CDSSDSi2Detector->SetZPos(zPosCmd->GetNewDoubleValue(newValue));
     
    
      if(command == dPhiGapCmd)
        CDSSDSi2Detector->SetDPhiGap(dPhiGapCmd->GetNewDoubleValue(newValue));
      
      if(command == dPhiSiCmd)
        CDSSDSi2Detector->SetDPhiSi(dPhiSiCmd->GetNewDoubleValue(newValue));
      
      if(command == nSlicesCmd)
        CDSSDSi2Detector->SetNSlices(nSlicesCmd->GetNewDoubleValue(newValue));
      
      if(command == resCmd)
        CDSSDSi2Detector->SetResolution(resCmd->GetNewDoubleValue(newValue));
      
     
}

