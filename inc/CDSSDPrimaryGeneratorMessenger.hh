#ifndef CDSSDPrimaryGeneratorMessenger_h
#define CDSSDPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class CDSSDPrimaryGeneratorAction;
class G4ParticleTable;
class G4IonTable;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithoutParameter;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class CDSSDPrimaryGeneratorMessenger: public G4UImessenger {
private:
  
  CDSSDPrimaryGeneratorAction* CDSSDActionGun; ///< Pointer to main primary generator class

  G4ParticleTable* particleTable;                    ///< Pointer to the global particle table
  G4IonTable* ionTable;                              ///< Pointer to the global particle table

  G4UIdirectory*               gunDir;                 ///< Directory for gun commands

  G4UIcmdWithoutParameter*     listCmd;                ///< List available particles.
  G4UIcmdWithAString*          particleCmd;            ///< Select the incident particle.
 
  G4UIcmdWithAString*          randomThetaCmd;      ///< Sets the limits in the Theta angle for the scattered particle.
  G4UIcommand*                 randomThetaValCmd;      ///< Sets the limits in the Theta angle for the scattered particle.
  G4UIcommand*                 randomPhiValCmd;        ///< Sets the limits in the Phi angle for the scattered particle.

    
  //Kine Parameter
  G4UIdirectory*               KineDir;                ///< Directory for CINE commands
  G4UIcommand*                 KineIncidentIonCmd;     ///< Set properties of incident ion to be generated.
  G4UIcommand*                 KineTargetIonCmd;       ///< Set properties of target ion to be generated.
  G4UIcommand*                 KineScatteredIonCmd;    ///< Set properties of scattered ion to be generated.
  G4UIcommand*                 KineRecoilIonCmd;       ///< Set properties of recoil ion to be generated.
  G4UIcmdWithADoubleAndUnit*   KineLabEnergyCmd;       ///< Sets the laboratory energy.
  G4UIcmdWithADoubleAndUnit*   KineUserThetaCMCmd;     ///< Sets theta CM angle for scattered particle (in degrees)
  G4UIcmdWithADoubleAndUnit*   KineUserPhiAngleCmd;    ///< User set phi angle for outgoing particle in the Lab system (in degrees)

  //Reaction parameter
  G4UIcommand* scatteredIonCmd;              ///< Set properties of scattered ion to be generated.
  G4UIcommand* recoilIonCmd;                 ///< Set properties of recoil ion to be generated.
  G4UIcmdWithADoubleAndUnit* reactionQCmd;       ///< Sets the reaction Q

  G4UIcmdWithADoubleAndUnit* labEnergyCmd;       ///< Sets the laboratory energy
  G4UIcmdWithADoubleAndUnit* thetaLabAngleCmd;   ///< Sets theta lab angle for the scattered particle (degrees)

  // for ion shooting
  G4bool   fShootIon;                 ///< Internal variables for ion creation
  G4int    fAtomicNumber;             ///< Internal variables for ion creation: atomic number
  G4int    fAtomicMass;               ///< Internal variables for ion creation: atomic mass
  G4int    fIonCharge;                ///< Internal variables for ion creation: ion charge
  G4double fIonExciteEnergy;          ///< Internal variables for ion creation: ion excitation energy

  // for Kine command
  G4double fIonMass;                 ///< Internal variables for ion creation: ion mass in atomic mass unit u
  void KineIncidentIonCommand(G4String newValues);
  void KineTargetIonCommand(G4String newValues);
  void KineScatteredIonCommand(G4String newValues);
  void KineRecoilIonCommand(G4String newValues);

public:
  CDSSDPrimaryGeneratorMessenger(CDSSDPrimaryGeneratorAction*);
  ~CDSSDPrimaryGeneratorMessenger();

  void SetNewValue(G4UIcommand*, G4String);
};
#endif
