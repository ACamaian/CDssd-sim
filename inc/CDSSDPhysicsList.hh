#ifndef CDSSDPhysicsList_h
#define CDSSDPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "G4EmConfigurator.hh"
#include "G4EmParameters.hh"

#include "CDSSDPhysListParticles.hh"

class CDSSDPhysicsListMessenger;
class G4VPhysicsConstructor;

class CDSSDPhysicsList: public G4VModularPhysicsList {
private:

  G4double cutForGamma;            ///< Cut energy parameter for gammas
  G4double cutForElectron;         ///< Cut energy parameter for gammas
  G4double cutForPositron;         ///< Cut energy parameter for gammas
  G4double cutForProton;         ///< Cut energy parameter for proton and Ion
  
  G4int    verbose;                ///< Verbose control
  G4bool   emBuilderIsRegisted;    ///< Register control parameter for library
  G4bool   helIsRegisted;          ///< Register control parameter for library
  G4bool   bicIsRegisted;          ///< Register control parameter for library
  G4bool   ionIsRegisted;          ///< Register control parameter for library
  G4bool   gnucIsRegisted;         ///< Register control parameter for library
  G4bool   stopIsRegisted;         ///< Register control parameter for library

  CDSSDPhysicsListMessenger* pMessenger;  ///< Pointer to messenger
  CDSSDPhysListParticles *particleList; ///< List of particles
 
  

public:
  CDSSDPhysicsList();
  ~CDSSDPhysicsList();

  // SetCuts()
  void ConstructParticle();
  void ConstructProcess();
  void SetCuts();

  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);
  void SetCutForProton(G4double);

  void AddPhysicsList(const G4String&);

  void SetVerbose(G4int val);
};
#endif
