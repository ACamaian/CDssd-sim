//////////////////////////////////////////////////////////////////
/// \class CDSSDPhysicsList
/// Physics List
/////////////////////////////////////////////////////////////////

#include "CDSSDPhysicsList.hh"
#include "CDSSDPhysicsListMessenger.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"

#include "PhysListEmStandard.hh"
#include "PhysListEmStandardWVI.hh"
#include "PhysListEmStandardSS.hh"
#include "PhysListEmStandardGS.hh"
#include "HadrontherapyIonStandard.hh"

//TESTING PAI MODELS (as in test_em8)
#include "G4PAIModel.hh"
#include "G4PAIPhotModel.hh"

//#include "CDSSDParticlesBuilder.hh"
#include "CDSSDStepLimiterBuilder.hh"

#include "G4UnitsTable.hh"
#include "G4LossTableManager.hh"
#include "G4EmParameters.hh"
#include "G4EmProcessOptions.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4EmConfigurator.hh"

#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4UniversalFluctuation.hh"

#include "G4BraggIonGasModel.hh"
#include "G4BetheBlochIonGasModel.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4IonPhysics.hh"

#include "G4EmParameters.hh"

//////////////////////////////////////////////////////////////////
/// Constructor. Initializing values
CDSSDPhysicsList::CDSSDPhysicsList():  G4VModularPhysicsList(){

  emBuilderIsRegisted = false;
  stepLimiterIsRegisted = false;
  helIsRegisted = false;
  bicIsRegisted = false;
  ionIsRegisted = false;
  gnucIsRegisted = false;

  stopIsRegisted = false;
  verbose = 0;

  G4LossTableManager::Instance()->SetVerbose(verbose);
  defaultCutValue = 1.*mm;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue; 
  cutForProton  = defaultCutValue;

  //Particles
  particleList = new CDSSDPhysListParticles("particles");

  //Decay Physics //the rest is registered via Messenger
  RegisterPhysics(new G4DecayPhysics());

  pMessenger = new CDSSDPhysicsListMessenger(this);

  // Add Physics builders
  
  stepLimiter = new CDSSDStepLimiterBuilder();
  
  
}

//////////////////////////////////////////////////////////////////
/// Destructor. Nothing to do
CDSSDPhysicsList::~CDSSDPhysicsList() {


  if (pMessenger!=NULL) delete pMessenger;

  
}

//////////////////////////////////////////////////////////////////
/// Registering the physics processes
void CDSSDPhysicsList::AddPhysicsList(const G4String& name){
 
  if(verbose>0){
    G4cout << "Add Physics <" << name
           << "> emBuilderIsRegisted= " << emBuilderIsRegisted
           << G4endl;
  }

  if (name == "emstandard" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics());
    emBuilderIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  }
  else if (name == "emstandard_opt1" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics_option1());
    emBuilderIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  } 
  else if (name == "emstandard_opt2" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics_option2());
    emBuilderIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  }
  else if (name == "emstandard_opt3" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics_option3());
    emBuilderIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  } 
  else if (name == "emstandard_opt4" && !emBuilderIsRegisted) {
    RegisterPhysics(new G4EmStandardPhysics_option4());
    emBuilderIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "elastic" && !helIsRegisted && emBuilderIsRegisted) {
    RegisterPhysics(new G4HadronElasticPhysics());
    helIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "binary" && !bicIsRegisted && emBuilderIsRegisted) {
    RegisterPhysics(new G4HadronInelasticQBBC());
    bicIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "binary_ion" && !ionIsRegisted && emBuilderIsRegisted) {
    RegisterPhysics(new G4IonBinaryCascadePhysics());
    ionIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "gamma_nuc" && !gnucIsRegisted && emBuilderIsRegisted) {
    RegisterPhysics(new G4EmExtraPhysics());
    gnucIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  } else if (name == "stopping" && !stopIsRegisted && emBuilderIsRegisted) {
    RegisterPhysics(new G4StoppingPhysics());
    stopIsRegisted = true;
    G4cout << "CDSSDPhysicsList::AddPhysicsList <" << name << ">" << G4endl;
  } else if(!emBuilderIsRegisted) {
    G4cout << "PhysicsList::AddPhysicsList <" << name << ">"
           << " fail - EM physics should be registered first " << G4endl;
  } 
}

//////////////////////////////////////////////////////////////////
/// Construct Particles
void CDSSDPhysicsList::ConstructParticle() {

  particleList->ConstructParticle();

}



//////////////////////////////////////////////////////////////////
/// Construct Processes
void CDSSDPhysicsList::ConstructProcess() {

  if(verbose > 0)
    G4cout << "Construct Processes" << G4endl;

  if(!emBuilderIsRegisted) { AddPhysicsList("standard"); }
  G4VModularPhysicsList::ConstructProcess(); 
  
  
  // Define energy interval for loss processes
  G4EmParameters::Instance()->SetMinEnergy(2*eV);
  G4EmParameters::Instance()->SetMaxEnergy(2.*GeV);
  G4EmParameters::Instance()->SetNumberOfBins(10000);
  
  SetCuts();
}

//////////////////////////////////////////////////////////////////
/// Sets the cut on the physics interaction calculations.
///  "G4VUserPhysicsList::SetCutsWithDefault" method sets
///  the default cut value for all particle types
void CDSSDPhysicsList::SetCuts() {
  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");
  SetCutValue(cutForProton, "proton");

 if (verbose>0)  DumpCutValuesTable();
}

//////////////////////////////////////////////////////////////////
/// Selecting verbosity
void CDSSDPhysicsList::SetVerbose(G4int val){
  verbose = val;
}

//////////////////////////////////////////////////////////////////
/// Setting cut value for the gammas
void CDSSDPhysicsList::SetCutForGamma(G4double cut){
  cutForGamma = cut;
  SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

//////////////////////////////////////////////////////////////////
/// Setting cut value for the electron
void CDSSDPhysicsList::SetCutForElectron(G4double cut){
  cutForElectron = cut;
  SetParticleCuts(cutForElectron, G4Electron::Electron());
}

//////////////////////////////////////////////////////////////////
/// Setting cut value for the positron
void CDSSDPhysicsList::SetCutForPositron(G4double cut) {
  cutForPositron = cut;
  SetParticleCuts(cutForPositron, G4Positron::Positron());
}

//////////////////////////////////////////////////////////////////
/// Setting cut value for the positron
void CDSSDPhysicsList::SetCutForProton(G4double cut) {
  cutForProton = cut;
  SetParticleCuts(cutForProton, G4Proton::Proton());
}



