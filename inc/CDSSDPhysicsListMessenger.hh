#ifndef CDSSDPhysicsListMessenger_h
#define CDSSDPhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class CDSSDPhysicsList;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

class CDSSDPhysicsListMessenger: public G4UImessenger {
private:
  CDSSDPhysicsList*       pPhysicsList;  ///< Pointer to the Physic List

  G4UIdirectory*             physDir;       ///< Directory
  G4UIcmdWithADoubleAndUnit* gammaCutCmd;   ///< Set gamma cut
  G4UIcmdWithADoubleAndUnit* electCutCmd;   ///< Set electron cut
  G4UIcmdWithADoubleAndUnit* protoCutCmd;   ///< Set positron cut
  G4UIcmdWithADoubleAndUnit* pCutCmd;   ///< Set proton cut
  G4UIcmdWithADoubleAndUnit* allCutCmd;     ///< Set cut for all
  G4UIcmdWithAnInteger*      verbCmd;       ///< Set verbose level for processes
  G4UIcmdWithAString*        pListCmd;      ///< Add modula physics list
  G4UIcmdWithAString*        RmPListCmd;    ///< Remove all modula physics list

public:
  CDSSDPhysicsListMessenger(CDSSDPhysicsList* );
  ~CDSSDPhysicsListMessenger();

  void SetNewValue(G4UIcommand*, G4String);
};
#endif
