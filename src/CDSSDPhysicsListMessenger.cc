
#include "CDSSDPhysicsListMessenger.hh"
#include "CDSSDPhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4LossTableManager.hh"

//////////////////////////////////////////////////////////////////
/// Constructor with commands definition.
/// Commands included in this AnalysisMessenger:
/// - /CDSSD/phys/setGCut
/// - /CDSSD/phys/setECut
/// - /CDSSD/phys/setPCut
/// - /CDSSD/phys/setProtonCuts
/// - /CDSSD/phys/setCuts
/// - /CDSSD/phys/addPhysics
/// - /CDSSD/phys/RemovePhysics
/// - /CDSSD/phys/verbose
CDSSDPhysicsListMessenger::CDSSDPhysicsListMessenger(CDSSDPhysicsList* pPhys)
  :pPhysicsList(pPhys){

  physDir = new G4UIdirectory("/CDSSD/phys/");
  physDir->SetGuidance("physics list commands");

  gammaCutCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/phys/setGCut",this);
  gammaCutCmd->SetGuidance("Set gamma cut.");
  gammaCutCmd->SetParameterName("Gcut",false);
  gammaCutCmd->SetUnitCategory("Length");
  gammaCutCmd->SetRange("Gcut>0.0");
  gammaCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  electCutCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/phys/setECut",this);
  electCutCmd->SetGuidance("Set electron cut.");
  electCutCmd->SetParameterName("Ecut",false);
  electCutCmd->SetUnitCategory("Length");
  electCutCmd->SetRange("Ecut>0.0");
  electCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  protoCutCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/phys/setPCut",this);
  protoCutCmd->SetGuidance("Set positron cut.");
  protoCutCmd->SetParameterName("Pcut",false);
  protoCutCmd->SetUnitCategory("Length");
  protoCutCmd->SetRange("Pcut>0.0");
  protoCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  pCutCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/phys/setProtonCut",this);
  pCutCmd->SetGuidance("Set proton cut.");
  pCutCmd->SetParameterName("ProtonCut",false);
  pCutCmd->SetUnitCategory("Length");
  pCutCmd->SetRange("Protoncut>0.0");
  pCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  allCutCmd = new G4UIcmdWithADoubleAndUnit("/CDSSD/phys/setCuts",this);
  allCutCmd->SetGuidance("Set cut for all.");
  allCutCmd->SetParameterName("cut",false);
  allCutCmd->SetUnitCategory("Length");
  allCutCmd->SetRange("cut>0.0");
  allCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  pListCmd = new G4UIcmdWithAString("/CDSSD/phys/addPhysics",this);
  pListCmd->SetGuidance("Add modular physics list.");
  pListCmd->SetParameterName("PList",false);
  pListCmd->AvailableForStates(G4State_PreInit);

  RmPListCmd = new G4UIcmdWithAString("/CDSSD/phys/RemovePhysics",this);
  RmPListCmd->SetGuidance("Remove all modular physics list.");
  RmPListCmd->AvailableForStates(G4State_Idle);

  verbCmd = new G4UIcmdWithAnInteger("/CDSSD/phys/verbose",this);
  verbCmd->SetGuidance("Set verbose level for processes");
  verbCmd->SetParameterName("pVerb",false);
  verbCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//////////////////////////////////////////////////////////////////
/// Destructor
CDSSDPhysicsListMessenger::~CDSSDPhysicsListMessenger(){
  delete gammaCutCmd;
  delete pCutCmd;
  delete electCutCmd;
  delete protoCutCmd;
  delete allCutCmd;
  delete pListCmd;
  delete RmPListCmd;
  delete verbCmd;
  delete physDir;
}

//////////////////////////////////////////////////////////////////
/// Setting the values using the CDSSDPhysicsList interface
void CDSSDPhysicsListMessenger::SetNewValue(G4UIcommand* command,
					       G4String newValue) {

  if( command == gammaCutCmd )
    pPhysicsList->SetCutForGamma(gammaCutCmd->GetNewDoubleValue(newValue));

  if( command == electCutCmd )
    pPhysicsList->SetCutForElectron(electCutCmd->GetNewDoubleValue(newValue));


  if( command == protoCutCmd )
    pPhysicsList->SetCutForPositron(protoCutCmd->GetNewDoubleValue(newValue));

  if( command == allCutCmd ) {
    G4double cut = allCutCmd->GetNewDoubleValue(newValue);
    pPhysicsList->SetCutForGamma(cut);
    pPhysicsList->SetCutForElectron(cut);
    pPhysicsList->SetCutForPositron(cut);
  }

  if( command == verbCmd )
    G4LossTableManager::Instance()->SetVerbose(verbCmd->GetNewIntValue(newValue));

  if( command == pListCmd )
    pPhysicsList->AddPhysicsList(newValue);

  if( command == RmPListCmd )
    pPhysicsList->~CDSSDPhysicsList();
}
